
#include "frontpanel.h"

/*
 * Morgeb - english front panel powered via neopixels
 */

/*
 * Morgeb english front panel layout
 *  <char>/<index>
 * I/00    T/01   L/--   I/02   S/03   A/--   S/--   A/--   M/--   P/--   M/--
 * A/--    C/--   Q/10   U/09   A/08   R/07   T/06   E/05   R/04   D/--   C/--
 * T/11    W/12   E/13   N/14   T/15   Y/16   F/17   I/18   V/19   E/20   X/--
 * H/29    A/28   L/27   F/26   S/--   T/25   E/24   N/23   F/--   T/22   O/21
 * P/30    A/31   S/32   T/33   E/--   R/--   U/--   N/34   I/35   N/36   E/37
 * O/48    N/47   E/46   S/45   I/44   X/43   T/42   H/41   R/40   E/39   E/38
 * F/49    O/50   U/51   R/52   F/53   I/54   V/55   E/56   T/57   W/58   O/59
 * E/70    I/69   G/68   H/67   T/66   E/65   L/64   E/63   V/62   E/61   N/60
 * S/71    E/72   V/73   E/74   N/75   T/76   W/77   E/78   L/79   V/80   E/81
 * T/90    E/89   N/88   S/--   E/--   O/87   C/86   L/85   O/84   C/83   K/82
 */

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

// define how many pixels are used to light up each character
#define PIXEL_PIN 6
#define PIXEL_PER_CHAR 2
#define PIXEL_DEF_POWER 125

#define RTC_WAKEUP_PIN 2
#define RTC_SLEEP_TIME 5