
#include "fp.h"

/*
 * Morgeb - english front panel powered via neopixels
 */

/*
 * Morgeb english front panel layout
 *  <char>/<index>-<pin>
 * Pin02: I/000    T/001   L/002   I/003   S/004   A/005   S/006   A/007   M/008   P/009   M/010
 * Pin03: A/011    C/012   Q/013   U/014   A/015   R/016   T/017   E/018   R/019   D/020   C/021
 * Pin04: T/022    W/023   E/024   N/025   T/026   Y/027   F/028   I/029   V/030   E/031   X/032
 * Pin05: H/033    A/034   L/035   F/036   S/037   T/038   E/039   N/040   F/041   T/042   O/043
 * Pin06: P/044    A/045   S/046   T/047   E/048   R/049   U/050   N/051   I/052   N/053   E/054
 * Pin07: O/055    N/056   E/057   S/058   I/059   X/060   T/061   H/062   R/063   E/064   E/065
 * Pin08: F/066    O/067   U/068   R/069   F/070   I/071   V/072   E/073   T/074   W/075   O/076
 * Pin09: E/077    I/078   G/079   H/080   T/081   E/082   L/083   E/084   V/085   E/086   N/087
 * Pin10: S/088    E/089   V/090   E/091   N/092   T/093   W/094   E/095   L/096   V/097   E/098
 * Pin11: T/099    E/100   N/101   S/102   E/103   O/104   C/105   L/106   O/107   C/108   K/109
 */

const fp_layout_ LAYOUT = {
    // prefix words
    {0, 2, 2}, // PRE IT
    {3, 2, 2}, // PRE IS

    // minutes words
    {28, 4, 4}, // MIN FIVE
    {38, 3, 5}, // MIN TEN
    {13, 7, 3}, // MIN QUARTER
    {22, 6, 4}, // MIN TWENTY
    {22, 9, 4}, // MIN TWENTYFIVE
    {33, 4, 5}, // MIN HALF

    // type words
    {44, 4, 6}, // TYPE PAST
    {42, 2, 5}, // TYPE TO

    // hours words
    {55, 3, 7},  // HOUR ONE
    {74, 3, 8},  // HOUR TWO
    {61, 4, 7},  // HOUR THREE
    {66, 4, 8},  // HOUR FOUR
    {70, 4, 8},  // HOUR FIVE
    {58, 3, 7},  // HOUR SIX
    {88, 4, 10}, // HOUR SEVEN
    {77, 5, 9},  // HOUR EIGHT
    {51, 4, 6},  // HOUR NINE
    {99, 3, 11}, // HOUR TEN
    {82, 6, 9},  // HOUR ELEVEN
    {93, 6, 10}, // HOUR TWELVE

    // full clock word
    {104, 6, 11} // FULL OCLOCK

};

const fp_dimension_ LAYOUT_DIMENSION = {
    10, // heigth
    11  // width
};

// define how many pixels are used to light up each character
#define PIXEL_PER_CHAR 8
#define PIXEL_DEF_POWER 5

#define RTC_WAKEUP_PIN 12
#define RTC_SLEEP_TIME 5