#include <Arduino.h>
#include <SimpleSerialShell.h>
#include <avr/sleep.h>
#include <RTClib.h>
#include <EEPROM.h>

#include "morgeb.h"
#include "fp-sk6812.h"

RTC_DS3231 rtc;
fp_color_ color = {0, 0, 0, PIXEL_DEF_POWER};
SK6812FrontPanel_ frontpanel(LAYOUT_DIMENSION, LAYOUT, PIXEL_PER_CHAR, color);

/*
 * Small helper function to read persistent color value from EEPROM
 */
fp_color_ read_stored_color()
{
  uint8_t g = EEPROM.read(EEPROM_ADDR_COLOR_G);
  uint8_t b = EEPROM.read(EEPROM_ADDR_COLOR_B);
  uint8_t r = EEPROM.read(EEPROM_ADDR_COLOR_R);
  uint8_t w = EEPROM.read(EEPROM_ADDR_COLOR_W);
  return {g, r, b, w};
}

/*
 * Small helper function to store color value persistent on EEPROM
 */
void store_color(fp_color_ color)
{
  EEPROM.update(EEPROM_ADDR_COLOR_G, color.g);
  EEPROM.update(EEPROM_ADDR_COLOR_B, color.b);
  EEPROM.update(EEPROM_ADDR_COLOR_R, color.r);
  EEPROM.update(EEPROM_ADDR_COLOR_W, color.w);
}

/*
 * Initiate the Real-Time-Clock (RTC)
 * This function will clear and disable both alarm instances
 */
int init_rtc()
{
  pinMode(RTC_WAKEUP_PIN, INPUT_PULLUP);

  if (false == rtc.begin())
  {
    return RET_ERROR_RTC;
  }
  if (rtc.lostPower())
  {
    Serial.println(F("RTC has lost power, let's reset the time to the compile time"));
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  rtc.disableAlarm(1);
  rtc.disableAlarm(2);
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);

  rtc.writeSqwPinMode(DS3231_OFF);

  return RET_SUCCESS;
}

/*
 * Initiate Frontpanel library object
 */
int init_frontpanel()
{
  fp_color_ color = read_stored_color();
  Serial.print(F("Set frontpanel to "));
  SK6812FrontPanel_::print_color(color);

  frontpanel.init();
  frontpanel.update_color(color);
  // frontpanel.test_me();

  return RET_SUCCESS;
}

/*
 * Handel error message properly. If
 */
void handle_error(int err)
{
  switch (err)
  {
  case RET_SUCCESS:
    return; // avoid running into abort
  case RET_ERROR_RTC:
    Serial.println(F("RTC has lost power, let's reset the time to the compile time"));
    break;
  case RET_ERROR_FRONTPANEL:
    Serial.println(F("Failed to initialize the Frontpanel, please verify previous raised errors"));
    break;
  case RET_ERROR_SERIAL_CONSOLE:
    Serial.println(F("Failed to initialize the serial console, please verify previous raised errors"));
    break;
  default:
    Serial.print(F("Something unexpected occurred during the initialization, please read the code and investigate where the err-code: "));
    Serial.print(err);
    Serial.println(F(" comes from in the setup function"));
    break;
  }

  Serial.flush();
  abort();
}

/*
 * Initiate Morgeb application
 * This includes initiating the RTC, Frontpanel and Serial monitor
 */
int init_application()
{
  int err = RET_SUCCESS;

  // TODO: remove before fly
  // err = init_rtc();
  handle_error(err);
  Serial.println(F("Initiated Real-Time-Clock (RTC) properly"));

  err = init_frontpanel();
  handle_error(err);
  Serial.println(F("Initiated Frontpanel properly"));

  return err;
}

void update_var_help()
{
  Serial.println(F("Incorrect amount of parameters passed to updateVar command."));
  Serial.println(F("Please pass the variable name and value, as shown below"));
  Serial.println(F("Available variables are: color(g r b w)"));
  Serial.println(F("  > updateVar color 10 20 30 100"));
}

int update_var(int argc, char **argv)
{
  Serial.println(F("## Update Morgeb-Clock variable"));
  Serial.println(argc);
  if (argc < 2)
  {
    update_var_help();
    return RET_ERROR_COMMAND;
  }

  char *varname = argv[1];
  if (strncmp(varname, "color", strlen("color")) == 0)
  {
    if (argc != 6)
    {
      update_var_help();
      return RET_ERROR_COMMAND;
    }

    // TODO: this is not save, we neither check for overflows during the conversion nor during the cast
    uint8_t g = atoi(argv[2]);
    uint8_t r = atoi(argv[3]);
    uint8_t b = atoi(argv[4]);
    uint8_t w = atoi(argv[5]);

    fp_color_ color = {g, r, b, w};
    store_color(color);

    frontpanel.update_color(color);
    Serial.print("Successfully updated color to: ");
    SK6812FrontPanel_::print_color(color);
  }
  else
  {
    update_var_help();
    return RET_ERROR_COMMAND;
  }

  return RET_SUCCESS;
}

int print_vars(int argc, char **argv)
{
  Serial.println(F("## Print Morgeb-Clock variables"));
  fp_color_ color = read_stored_color();
  Serial.print(F("  * "));
  SK6812FrontPanel_::print_color(color);

  return RET_SUCCESS;
}

/*
 * Handle user interaction, which allows to update
 * application related information such as color, brightness, etc.
 */
int handle_user_interaction()
{
  uint32_t timeout = 0;

  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println(F("Welcome to the Serial output of the Morgeb-Clock"));
  Serial.println(F("User configuration phase started, this allows you to persistently change values of the clock"));
  Serial.print(F("If no Serial input is read for "));
  Serial.print(USER_CONFIG_SEC_TIMEOUT);
  Serial.println(" seconds, the clock will start");

  shell.attach(Serial);
  shell.addCommand(F("updateVar <update variable value>..."), update_var);
  shell.addCommand(F("printVars <print all variable values>..."), print_vars);
  shell.printHelp(0, NULL);
  Serial.print(F("> "));

  while (timeout < USER_CONFIG_MS_TIMEOUT)
  {
    if (shell.executeIfInput())
    {
      timeout = 0;
    }
    delay(USER_CONFIG_POLL_MS_TIMEOUT);
    timeout += USER_CONFIG_POLL_MS_TIMEOUT;
  }

  return RET_SUCCESS;
}

/*
 * Setup all cock components and provide
 * the user to configure the clock accordantly
 */
void setup()
{
  int err = handle_user_interaction();
  handle_error(err);
  Serial.println(F("Setup phase done, clock will start showing the time"));

  err = init_application();
  handle_error(err);
  Serial.println(F("Initiated Morgeb-Clock components properly"));

  Serial.flush();
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

  Serial.print("Sleep for ");
  Serial.print(RTC_SLEEP_TIME);
  Serial.println(" minute");
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

/*
 * Update the time every five minutes
 * Let the microcontroller sleep with in the Power Down mode to save energy
 */
void loop()
{
  Serial.println("LOOP");
  delay(1000);
  return;

  DateTime now = rtc.now();
  // compute next wakeup, which is a multiple of 5 and has 0 seconds
  // hence, we substract the current seconds and compute the next smooth minute value
  DateTime next_wakeup = now -
                         TimeSpan(0, 0, now.minute(), now.second()) +
                         TimeSpan(0, 0, ((now.minute() + RTC_SLEEP_TIME) / RTC_SLEEP_TIME) * RTC_SLEEP_TIME, 0);
  rtc.setAlarm1(next_wakeup, DS3231_A1_Minute);

  // #TODO: find a better logic
  DateTime now_five_base = now -
                           TimeSpan(0, 0, now.minute(), now.second()) +
                           TimeSpan(0, 0, ((now.minute()) / RTC_SLEEP_TIME) * RTC_SLEEP_TIME, 0);

  Serial.print("Set next wakeup to:");
  Serial.print(next_wakeup.hour());
  Serial.print(":");
  Serial.print(next_wakeup.minute());
  Serial.print(".");
  Serial.println(next_wakeup.second());

  frontpanel.update(now_five_base.hour(), now_five_base.minute(), now_five_base.second());

  // sleep until we need to update the clock again
  goSleep();
}