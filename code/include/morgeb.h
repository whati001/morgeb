
#include "fp.h"

/*
 * Morgeb - english front panel powered via neopixels
 */

/*
 * Morgeb english front panel layout
 *  <char>/<index>-<pin>
 * I/000    T/001   L/002   I/003   S/004   A/005   S/006   A/007   M/008   P/009   M/010
 * A/011    C/012   Q/013   U/014   A/015   R/016   T/017   E/018   R/019   D/020   C/021
 * T/022    W/023   E/024   N/025   T/026   Y/027   F/028   I/029   V/030   E/031   X/032
 * H/033    A/034   L/035   F/036   S/037   T/038   E/039   N/040   F/041   T/042   O/043
 * P/044    A/045   S/046   T/047   E/048   R/049   U/050   N/051   I/052   N/053   E/054
 * O/055    N/056   E/057   S/058   I/059   X/060   T/061   H/062   R/063   E/064   E/065
 * F/066    O/067   U/068   R/069   F/070   I/071   V/072   E/073   T/074   W/075   O/076
 * E/077    I/078   G/079   H/080   T/081   E/082   L/083   E/084   V/085   E/086   N/087
 * S/088    E/089   V/090   E/091   N/092   T/093   W/094   E/095   L/096   V/097   E/098
 * T/099    E/100   N/101   S/102   E/103   O/104   C/105   L/106   O/107   C/108   K/109
 */

const fp_layout_ LAYOUT = {
    // prefix words
    {0, 2}, // PRE IT
    {3, 2}, // PRE IS

    // minutes words
    {28, 4}, // MIN FIVE
    {38, 3}, // MIN TEN
    {13, 7}, // MIN QUARTER
    {22, 6}, // MIN TWENTY
    {22, 9}, // MIN TWENTYFIVE
    {33, 4}, // MIN HALF

    // type words
    {44, 4}, // TYPE PAST
    {42, 2}, // TYPE TO

    // hours words
    {55, 3}, // HOUR ONE
    {74, 3}, // HOUR TWO
    {61, 4}, // HOUR THREE
    {66, 4}, // HOUR FOUR
    {70, 4}, // HOUR FIVE
    {58, 3}, // HOUR SIX
    {88, 4}, // HOUR SEVEN
    {77, 5}, // HOUR EIGHT
    {51, 4}, // HOUR NINE
    {99, 3}, // HOUR TEN
    {82, 6}, // HOUR ELEVEN
    {93, 6}, // HOUR TWELVE

    // full clock word
    {104, 6} // FULL OCLOCK

};

// define how many pixels are used to light up each character
const uint8_t LAYOUT_PIN_ORDER[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
#define PIXEL_PER_CHAR 8
#define PIXEL_DEF_POWER 5

#define RTC_WAKEUP_PIN 12
#define RTC_SLEEP_TIME 5