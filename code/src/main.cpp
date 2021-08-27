#include <Arduino.h>
#include <avr/sleep.h>

#include "morgeb.h"
#include "RTClib.h"
#include "neopixelfrontpanel.h"

// NeoPixelFrontPanel
NeoPixelFrontPanel_ FrontPanel(
    LAYOUT,
    PIXEL_PIN,
    Adafruit_NeoPixel::Color(PIXEL_DEF_POWER, PIXEL_DEF_POWER, PIXEL_DEF_POWER),
    PIXEL_PER_CHAR);

// RealTimeClock
RTC_DS3231 rtc;

uint8_t initRtc()
{
  pinMode(RTC_WAKEUP_PIN, INPUT_PULLUP);

  if (!rtc.begin())
  {
    Serial.println("Failed to start RTC, please validated if all the conections are solid");
    Serial.flush();
    return 0;
  }
  if (rtc.lostPower())
  {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  rtc.disableAlarm(1);
  rtc.disableAlarm(2);
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);

  rtc.writeSqwPinMode(DS3231_OFF);

  return 1;
}

uint8_t initFrontPanel()
{
  FrontPanel.init();
  FrontPanel.testMe();

  return 1;
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Start loading Morgeb clock");

  if (!initRtc())
  {
    Serial.println("Failed to load RTC instance");
    abort();
  }
  if (!initFrontPanel())
  {
    Serial.println("Failed to load FrontPanel instance");
    abort();
  }

  Serial.println("Initialized Morgeb clock properly");
}

void wakeupISR()
{
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(RTC_WAKEUP_PIN));
}

void goSleep()
{
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  noInterrupts();
  attachInterrupt(digitalPinToInterrupt(RTC_WAKEUP_PIN), wakeupISR, LOW);

  Serial.println("Sleep for five minutes");
  Serial.flush();

  interrupts();
  sleep_cpu();

  //---------------------------------------------------------------------------
  /* The program will continue from here when it wakes */
  //---------------------------------------------------------------------------

  rtc.disableAlarm(1);
  rtc.clearAlarm(1);

  Serial.println("Woke up, update front panel"); // Print message to show we're back
}

void loop()
{
  DateTime now = rtc.now();
  // compute next wakeup, which is a multiple of 5 and has 0 seconds
  // hence, we substract the current seconds and compute the next smooth minute value
  DateTime nextWakeup = now -
                        TimeSpan(0, 0, now.minute(), now.second()) +
                        TimeSpan(0, 0, ((now.minute() + RTC_SLEEP_TIME) / RTC_SLEEP_TIME) * RTC_SLEEP_TIME, 0);
  rtc.setAlarm1(nextWakeup, DS3231_A1_Minute);

  Serial.print("Set next wakeup to:");
  Serial.print(nextWakeup.hour());
  Serial.print(":");
  Serial.print(nextWakeup.minute());
  Serial.print(".");
  Serial.println(nextWakeup.second());

  FrontPanel.update(now.hour(), now.minute(), now.second());

  // sleep until we need to update the clock again
  goSleep();
}