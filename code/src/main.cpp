#include <Arduino.h>
#include <Wire.h>
#include <ds3231.h>
#include <Adafruit_NeoPixel.h>
#include "neopixelfrontpanel.h"
#include "morgeb.h"

// NeoPixelFrontPanel
NeoPixelFrontPanel_ FrontPanel(
    LAYOUT,
    PIXEL_PIN,
    Adafruit_NeoPixel::Color(PIXEL_DEF_POWER, PIXEL_DEF_POWER, PIXEL_DEF_POWER),
    PIXEL_PER_CHAR);

struct ts Timestamp;

void setup()
{
  // init serial monitor
  Serial.begin(9600);

  // init real time clock
  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);

  // init front panel
  FrontPanel.init();
  FrontPanel.testMe();

  Serial.println("Done initiating everything");
}

void readRts(ts *time)
{
  DS3231_get(time);
  // #DEBUG: remove before fly
  Serial.print("Date : ");
  Serial.print(time->mday);
  Serial.print("/");
  Serial.print(time->mon);
  Serial.print("/");
  Serial.print(time->year);
  Serial.print("\t Hour : ");
  Serial.print(time->hour);
  Serial.print(":");
  Serial.print(time->min);
  Serial.print(".");
  Serial.println(time->sec);
}

void loop()
{
  ts *curTime = new ts;
  readRts(curTime);
  delete curTime;

  FrontPanel.clear();
  FrontPanel.show();
  delay(5000);

  FrontPanel.drawPreIt();
  FrontPanel.show();
  delay(5000);
}