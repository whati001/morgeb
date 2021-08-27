# Morgeb Code

<p align="center">
  <p align="center">
    <img alt="license" src="https://img.shields.io/badge/license-MIT-blue">
    <img alt="gitter" src="https://img.shields.io/badge/Arduino-blue">
    <img alt="gitter" src="https://img.shields.io/badge/PlatformIO-blue">
  </p>
</p>
<br>

## About

This Project holds the source code for the project `Morgeb, the friendly clock for eachdays morning`.

## Software

The project is powered by an [AtMega382p](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf) in combination with a [DS3231](https://datasheets.maximintegrated.com/en/ds/DS3231.pdf) RTC.

### Used libraries
- [NeoPixelBus](https://github.com/adafruit/Adafruit_NeoPixel): Handle NeoPixels 2020 leds
- [FrontPanel(private)](https://github.com/whati001/morgeb/tree/main/code/lib/frontpanel): FrontPanel wrapper lib
- [RTClib](https://github.com/adafruit/RTClib): Handle DS3231 RTC

### Code architecture

We have tried to keep the code as simple as possible.
So there is no wifi or similar available, it is a analog clock.

**!!! POC: Version !!!**

Currently, the code is still in POC, further we will add some buttons and brightness control.

During the setup phase, we initiate the RTC and FrontPanel.
Most of the time, the mc is sleeping, it get's woke up by the RTC every five minutes.
After wakeup, it fetches the current time and does the Frontpanel update.
```C++
void loop()
{
  DateTime now = rtc.now();
  // compute next wakeup, which is a multiple of 5 and has 0 seconds
  // hence, we substract the current seconds and compute the next smooth minute value
  DateTime nextWakeup = now -
                        TimeSpan(0, 0, now.minute(), now.second()) +
                        TimeSpan(0, 0, ((now.minute() + RTC_SLEEP_TIME) / RTC_SLEEP_TIME) * RTC_SLEEP_TIME, 0);
  rtc.setAlarm1(nextWakeup, DS3231_A1_Minute);

  FrontPanel.update(now.hour(), now.minute(), now.second());

  // sleep until we need to update the clock again
  goSleep();
}
```