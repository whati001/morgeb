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

This librarys allows you do show the current time within the format `hh:mm` quite simple on a word front panel with a granularity of five minutes. The current library only supports SK6812 (RGBW) controled leds, where each row is connected to a separate I/O pin, to minimize strip lenght if multiple leds per characters are used.

## Basic principle

The current framework is based on five minutes granulartiy and does only support single line words.

Each part of the current time is defined within a `fpanel_word_` word and all words together compose the `fpanel_layout_` struct. The `fpanel_word_` struct consists of three properties, first the start index, second the length and last the I/O pin of the certain row. For example, the code `fpanel_word_ IT = {0, 2, 3}`, would represent the word IT, which is the first and two character long in a certain row controlled by I/O pin three. 

## How can I use FrontPanel in my project?

Simply import the frontpanel library and start using it. The library does not depend on anything else, except the `Arduino.h`.
At first, you need to define the dimension of your frontpanel via the `fp_dimension_` struct, which is needed to allocate memory properly. By passing the dimension, you can keep characters in case you do not want to power them at all. 

```C
const fp_dimension_ LAYOUT_DIMENSION = {
    10, // heigth
    11  // width
};
```
Next, we need to define the layout, which holds the information how and where each word is located on the frontpanel_ by defining the struct `fp_layout_`. This lib was created for the project [morgeb](https://github.com/whati001/morgeb), where the frontpanel look like the original from [QLockTwo](https://qlocktwo.com/de/?___from_store=de&___from_store=eu_de):
```markdown
/*
 * Morgeb english front panel layout
 *  <char>/<index>-<pin>
 * Pin03: I/000    T/001   L/002   I/003   S/004   A/005   S/006   A/007   M/008   P/009   M/010
 * Pin04: A/011    C/012   Q/013   U/014   A/015   R/016   T/017   E/018   R/019   D/020   C/021
 * Pin05: T/022    W/023   E/024   N/025   T/026   Y/027   F/028   I/029   V/030   E/031   X/032
 * Pin06: H/033    A/034   L/035   F/036   S/037   T/038   E/039   N/040   F/041   T/042   O/043
 * Pin07: P/044    A/045   S/046   T/047   E/048   R/049   U/050   N/051   I/052   N/053   E/054
 * Pin08: O/055    N/056   E/057   S/058   I/059   X/060   T/061   H/062   R/063   E/064   E/065
 * Pin09: F/066    O/067   U/068   R/069   F/070   I/071   V/072   E/073   T/074   W/075   O/076
 * Pin10: E/077    I/078   G/079   H/080   T/081   E/082   L/083   E/084   V/085   E/086   N/087
 * Pin11: S/088    E/089   V/090   E/091   N/092   T/093   W/094   E/095   L/096   V/097   E/098
 * Pin12: T/099    E/100   N/101   S/102   E/103   O/104   C/105   L/106   O/107   C/108   K/109
 */
```

This frontpanel will compile to the following layout struct:
```C
const fp_layout_ LAYOUT = {
    // prefix words
    {0, 2, 3}, // PRE IT
    {3, 2, 3}, // PRE IS

    // minutes words
    {28, 4, 5}, // MIN FIVE
    {38, 3, 6}, // MIN TEN
    {13, 7, 4}, // MIN QUARTER
    {22, 6, 5}, // MIN TWENTY
    {22, 10, 5}, // MIN TWENTYFIVE
    {33, 4, 6}, // MIN HALF

    // type words
    {44, 4, 7}, // TYPE PAST
    {42, 2, 6}, // TYPE TO

    // hours words
    {55, 3, 8},  // HOUR ONE
    {74, 3, 9},  // HOUR TWO
    {61, 5, 8},  // HOUR THREE
    {66, 4, 9},  // HOUR FOUR
    {70, 4, 9},  // HOUR FIVE
    {58, 3, 8},  // HOUR SIX
    {88, 5, 11}, // HOUR SEVEN
    {77, 5, 10},  // HOUR EIGHT
    {51, 4, 7},  // HOUR NINE
    {99, 3, 12}, // HOUR TEN
    {82, 6, 10},  // HOUR ELEVEN
    {93, 6, 11}, // HOUR TWELVE

    // full clock word
    {104, 6, 12} // FULL OCLOCK
};
```

Finally, we are able to initiate in instance and use it in our code:
```C++
#include "fp-sk6812.h"

#define PIXEL_PER_CHAR 8   /* pixels per char */
#define PIXEL_DEF_POWER 50 /* value between 0-255*/
const fp_dimension_ LAYOUT_DIMENSION = {10, 11}; /* dimension */
const fp_layout_ LAYOUT = {...}; /* word layout */

/* define color {g,r,b,w} */
fp_color_ color = {0, 0, 0, PIXEL_DEF_POWER};
/* create SK6812FronPanel_ instance */
SK6812FrontPanel_ frontpanel(LAYOUT_DIMENSION, LAYOUT, PIXEL_PER_CHAR, color);

void setup() {
    // init some stuff
    frontpanel.init();
}

void loop() {
    // ... do some stuff and retrieve the date time
    /* seconds are not needed yet, but we pass it anyway */
    /* you can also pass always 0 */
    frontpanel.update(hh, mm, ss);
}
```
## Limitations

This Software is provided as-is!

As already stated indirect, the lib does not tested with other driver driven leds than SK6812. To minimize the footprint, we have included the driver code in the file `SK6812_io.cpp`, which is taken from [Github_Electry_Arduino_SK6812](https://github.com/Electry/Arduino_SK6812). However, this code faces some servere issues and does not seems to maintained anymore. Hence, I have forked it and addressed them [here](https://github.com/whati001/Arduino_SK6812). 

Please feel free to adapt it to your needs and contribute to the project. I would be very grateful to include your improvements. Thanks for your support! 

**WARNING:** Everyone is responsible for what he/she is doing! I am not responsible if you hurt yourself, torch your house or anything that kind trying to do build something new! You are doing everything at your own risk!

## ToDos:
Please find here all the open tasks, which are not needed by nice to have

* use row multipliexing to reduce power consumption