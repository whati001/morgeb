
#include "neopixelfrontpanel.h"

/*
 * Morgeb - english front panel powered via neopixels
 */

/*
 * Morgeb english front panel layout
 *  <char>/<index>
 * I/00    T/01   L/--   I/02   S/03   A/--   S/--   A/--   M/--   P/--   M/--
 * A/--    C/--   Q/04   U/05   A/06   R/07   T/08   E/09   R/10   D/--   C/--
 * T/11    W/12   E/13   N/14   T/15   Y/16   F/20   I/21   V/22   E/23   X/--
 * H/24    A/25   L/26   F/27   S/--   T/28   E/29   N/30   F/--   T/31   O/32
 * P/33    A/34   S/35   T/36   E/--   R/--   U/--   N/37   I/38   N/38   E/39
 * O/40    N/41   E/42   S/43   I/44   X/45   T/46   H/47   R/48   E/49   E/50
 * F/51    O/52   U/53   R/54   F/55   I/56   V/57   E/58   T/59   W/60   O/61
 * E/62    I/63   G/64   H/65   T/66   E/67   L/68   E/69   V/70   E/71   N/72
 * S/73    E/74   V/75   E/76   N/77   T/78   W/79   E/80   L/81   V/82   E/83
 * T/84    E/85   N/86   S/--   E/--   O/87   C/88   L/89   O/90   C/91   K/92
 */

const neopixel_fpanel_layout_ LAYOUT = {
    // prefix words
    {0, 2}, // PRE IT
    {2, 2}, // PRE IS

    // minutes words
    {20, 4}, // MIN FIVE
    {28, 3}, // MIN TEN
    {13, 7}, // MIN QUARTER
    {11, 6}, // MIN TWENTY
    {23, 9}, // MIN TWENTYFIVE
    {24, 4}, // MIN HALF

    // type words
    {33, 4}, // TYPE PAST
    {31, 2}, // TYPE TO

    // hours words
    {40, 3}, // HOUR ONE
    {59, 3}, // HOUR TWO
    {46, 4}, // HOUR THREE
    {51, 4}, // HOUR FOUR
    {55, 4}, // HOUR FIVE
    {43, 3}, // HOUR SIX
    {73, 4}, // HOUR SEVEN
    {62, 5}, // HOUR EIGHT
    {37, 4}, // HOUR NINE
    {84, 3}, // HOUR TEN
    {67, 6}, // HOUR ELEVEN
    {78, 6}, // HOUR TWELVE

    // full clock word
    {87, 6} // FULL OCLOCK

};

// define how many pixels are used to light up each character
#define PIXEL_PIN 6
#define PIXEL_PER_CHAR 2
#define PIXEL_DEF_POWER 125

#define RTC_WAKEUP_PIN 2
#define RTC_SLEEP_TIME 5