# Wordclock FrontPanel Library

<p align="center">
  <p align="center">
    <img alt="license" src="https://img.shields.io/badge/license-MIT-blue">
    <img alt="gitter" src="https://img.shields.io/badge/Arduino-blue">
    <img alt="gitter" src="https://img.shields.io/badge/PlatformIO-blue">
  </p>
</p>
<br>

## About

This librarys allows you do show the current time within the format `hh:mm` quite simple on a word front panel with a granularity of five minutes.

## Basic principle

The current framework is based on five minutes granulartiy and only available within english. 

Each part of the current time is defined within a `fpanel_word_` word and all words together compose the `fpanel_layout_` struct.

A word consists of a start point and the length of pixels/leds used for lighting.


## How can I use FrontPanel in my project?

Because the class `FrontPanel_` is abstract, you need to create a subclass based on the led type you want to use.
In this sketch, we will use [NeoPixels](https://www.adafruit.com/product/4684).

First we need to define your layout, please simply initiate the `fpanel_layout_` struct:
```C
const fpanel_layout_ LAYOUT = {
    // prefix words
    {0, 2}, // PRE IT
    {2, 2}, // PRE IS

    // minutes words
    {17, 4}, // MIN FIVE
    {23, 3}, // MIN TEN
    {4, 7},  // MIN QUARTER
    {11, 6}, // MIN TWENTY
    {11, 9}, // MIN TWENTYFIVE
    {26, 4}, // MIN HALF

    // type words
    {30, 4}, // TYPE PAST
    {21, 2}, // TYPE TO

    // hours words
    {46, 3}, // HOUR ONE
    {57, 3}, // HOUR TWO
    {38, 4}, // HOUR THREE
    {49, 4}, // HOUR FOUR
    {53, 4}, // HOUR FIVE
    {43, 3}, // HOUR SIX
    {71, 4}, // HOUR SEVEN
    {70, 5}, // HOUR EIGHT
    {34, 4}, // HOUR NINE
    {88, 3}, // HOUR TEN
    {60, 6}, // HOUR ELEVEN
    {76, 6}, // HOUR TWELVE

    // full clock word
    {82, 6} // FULL OCLOCK

};
```

Next we create a NeoPixelFrontPanel_ class and pass as parameter the layout and color to use.
```C++
#include "frontpanel.h"
#include "neopixelfrontpanel.h"

// NeoPixelFrontPanel
NeoPixelFrontPanel_ FrontPanel(
    LAYOUT,
    Adafruit_NeoPixel::Color(PIXEL_DEF_POWER, PIXEL_DEF_POWER, PIXEL_DEF_POWER));


void setup() {
    // init some stuff
    FrontPanel.init();
}

void loop() {
    // ... do some stuff and retrieve the date time
    FrontPanel.update(hh, mm, ss);
}
```
## Limitations

This Software is provided as-is!

Please feel free to adapt it to your needs and contribute to the project. I would be very grateful to include your improvements. Thanks for your support!

**WARNING:** Everyone is responsible for what he/she is doing! I am not responsible if you hurt yourself, torch your house or anything that kind trying to do build something new! You are doing everything at your own risk!
