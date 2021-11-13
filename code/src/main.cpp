#include <Arduino.h>
#include <avr/sleep.h>

#include "morgeb.h"
#include "RTClib.h"

#include "fp-sk6812.h"

fp_color_ color = {0, 0, 0, PIXEL_DEF_POWER};
SK6812FrontPanel_ frontpanel(LAYOUT_DIMENSION, LAYOUT, PIXEL_PER_CHAR, color);

// RealTimeClock
RTC_DS3231 rtc;

uint8_t init_rtc()
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

uint8_t init_frontpanel()
{
  frontpanel.init();
  // frontpanel.set_output(2);
  return 1;
}

void setup()
{
  Serial.begin(9600);
  delay(100);
  Serial.println("Start loading Morgeb clock");

  if (!init_rtc())
  {
    Serial.println("Failed to load RTC instance");
    abort();
  }
  if (!init_frontpanel())
  {
    Serial.println("Failed to load FrontPanel instance");
    abort();
  }

  Serial.println("Initialized Morgeb clock properly");
}

void loop()
{
  delay(1000);
  frontpanel.clear_row(0);
  frontpanel.draw_word((fp_word_ *)&LAYOUT.PRE_IT);
  frontpanel.sync_row_data(0);
  delay(1000);
  frontpanel.clear_row(0);
  frontpanel.draw_word((fp_word_ *)&LAYOUT.PRE_IS);
  frontpanel.sync_row_data(0);
  frontpanel.clear_row(0);
  frontpanel.sync_row_data(0);
  Serial.println("LOOP DONE");

  // set_all_leds({0, 0, 0, 10});
  // set_all_leds({0, 10, 0, 0});

  //   set_all_leds({0, 0, 0, 0});
  // for (uint8_t i = 0; i < 88; i++) {
  //   LED.set_rgbw(i, {0, 0, 0, 5});
  //   LED.sync();
  //   delay(300);
  // }

  //     for (uint16_t idx = 0; idx <= LED_COUNT; idx++) {

  //   LED.set_rgbw(idx, {100, 0, 0, 0}); // Set second LED to white (using only W channel)
  //   }
  // LED.sync();

  // delay(1000);

  //     for (uint16_t idx = 0; idx <= LED_COUNT; idx++) {

  //   LED.set_rgbw(idx, {0, 100, 0, 0}); // Set second LED to white (using only W channel)
  //   }
  // LED.sync();

  // delay(1000);

  //     for (uint16_t idx = 0; idx <= LED_COUNT; idx++) {

  //   LED.set_rgbw(idx, {0, 0, 100, 0}); // Set second LED to white (using only W channel)
  //   }
  // LED.sync();

  // delay(1000);
}

// // NeoPixelFrontPanel
// NeoPixelFrontPanel_ FrontPanel(
//     LAYOUT,
//     PIXEL_PIN,
//     Adafruit_NeoPixel::Color(PIXEL_DEF_POWER, PIXEL_DEF_POWER, PIXEL_DEF_POWER),
//     PIXEL_PER_CHAR);

// void wakeupISR()
// {
//   sleep_disable();
//   detachInterrupt(digitalPinToInterrupt(RTC_WAKEUP_PIN));
// }

// void goSleep()
// {
//   sleep_enable();
//   set_sleep_mode(SLEEP_MODE_PWR_DOWN);

//   noInterrupts();
//   attachInterrupt(digitalPinToInterrupt(RTC_WAKEUP_PIN), wakeupISR, LOW);

//   Serial.println("Sleep for five minutes");
//   Serial.flush();

//   interrupts();
//   sleep_cpu();

//   //---------------------------------------------------------------------------
//   /* The program will continue from here when it wakes */
//   //---------------------------------------------------------------------------

//   rtc.disableAlarm(1);
//   rtc.clearAlarm(1);

//   Serial.println("Woke up, update front panel"); // Print message to show we're back
// }

// void loop()
// {
//   DateTime now = rtc.now();
//   // compute next wakeup, which is a multiple of 5 and has 0 seconds
//   // hence, we substract the current seconds and compute the next smooth minute value
//   DateTime nextWakeup = now -
//                         TimeSpan(0, 0, now.minute(), now.second()) +
//                         TimeSpan(0, 0, ((now.minute() + RTC_SLEEP_TIME) / RTC_SLEEP_TIME) * RTC_SLEEP_TIME, 0);
//   rtc.setAlarm1(nextWakeup, DS3231_A1_Minute);

//   Serial.print("Set next wakeup to:");
//   Serial.print(nextWakeup.hour());
//   Serial.print(":");
//   Serial.print(nextWakeup.minute());
//   Serial.print(".");
//   Serial.println(nextWakeup.second());

//   FrontPanel.update(now.hour(), now.minute(), now.second());

//   // sleep until we need to update the clock again
//   goSleep();
// }