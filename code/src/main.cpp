#include <Arduino.h>
#include <SimpleSerialShell.h>
#include <avr/sleep.h>
#include <RTClib.h>
#include <EEPROM.h>

#include "morgeb.h"
#include "fp-sk6812.h"

uint8_t cshell_running, timer_int_count;
RTC_DS3231 rtc;
SK6812FrontPanel_ frontpanel(LAYOUT_DIMENSION, LAYOUT, PIXEL_PER_CHAR);

uint8_t interrupt_rec;
enum INTERRUPTS
{
  NONE = 0,
  TIMER_INTERRUPT = 1,
  RTC_INTERRUPT,
  ADC_INTERRUPT
};

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
 * Small helper function to print time nicely
 */
void print_time(DateTime time)
{
  Serial.print("Time: ");
  Serial.print(time.hour());
  Serial.print(":");
  Serial.print(time.minute());
  Serial.print(".");
  Serial.println(time.second());
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

// https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
// https://ww1.microchip.com/downloads/en/Appnotes/Atmel-2505-Setup-and-Use-of-AVR-Timers_ApplicationNote_AVR130.pdf
int init_timer()
{
  Serial.println("Start to initialize the timer instance for periodic ADC readings");

  // use the timer in Normal mode -> count from 0 to 0xff
  TCCR2A &= ~(1 << WGM20);
  TCCR2A &= ~(1 << WGM21);
  TCCR2B &= ~(1 << WGM22);

  // reset the counter register
  TCNT2 = 0;

  // clear interrupt flag register
  TIFR2 &= ~(1 << TOV2);

  // enable interrupts
  TIMSK2 |= (1 << TOIE2);

  // use the highest prescaler 1024
  TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22);

  Serial.println("Finished to initialize the timer for periodic ADC readings");

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

  interrupt_rec = INTERRUPTS::NONE;
  timer_int_count = 0;

  Serial.begin(9600);
  while (!Serial)
    ;

  // #TODO: remove before fly
  err = init_timer();
  handle_error(err);
  Serial.println(F("Initiated Timer properly"));
  return 0;

  err = init_rtc();
  handle_error(err);
  Serial.println(F("Initiated Real-Time-Clock (RTC) properly"));

  err = init_frontpanel();
  handle_error(err);
  Serial.println(F("Initiated Frontpanel properly"));

  err = init_timer();
  handle_error(err);
  Serial.println(F("Initiated Timer properly"));
  return err;
}

/*
 * Helper function to print help information for updateVar command
 */
void update_var_help()
{
  Serial.println(F("Incorrect amount of parameters passed to updateVar command."));
  Serial.println(F("Please pass the variable name and value, as shown below"));
  Serial.println(F("Available variables are: color(g r b w), time hh mm ss"));
  Serial.println(F("  > updateVar color 10 20 30 100"));
  Serial.println(F("  > updateVar time 14 45 48"));
}

/*
 * Serial console command to update variables
 */
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
  else if (strncmp(varname, "time", strlen("time")) == 0)
  {
    if (argc != 5)
    {
      update_var_help();
      return RET_ERROR_COMMAND;
    }

    // TODO: this is not save, we neither check for overflows during the conversion nor during the cast
    uint8_t h = atoi(argv[2]);
    uint8_t m = atoi(argv[3]);
    uint8_t s = atoi(argv[4]);

    // year, month, day does not matter, so let's use dummy value
    DateTime time = DateTime(2022, 01, 01, h, m, s);
    rtc.adjust(time);

    Serial.print("Successfully updated time to: ");
    print_time(time);
  }
  else
  {
    update_var_help();
    return RET_ERROR_COMMAND;
  }

  return RET_SUCCESS;
}

/*
 * Serial console command to print all variables
 */
int print_vars(int argc, char **argv)
{
  Serial.println(F("## Print Morgeb-Clock variables"));
  fp_color_ color = read_stored_color();
  Serial.print(F("  * "));
  SK6812FrontPanel_::print_color(color);
  Serial.print(F("  * "));
  print_time(rtc.now());

  return RET_SUCCESS;
}

int exit(int argc, char **argv)
{
  Serial.println(F("## Exit configuration shell"));
  cshell_running = 0;
  return RET_SUCCESS;
}

void flush_serial_input()
{
  while (Serial.available() > 0)
  {
    Serial.read();
  }
}

int config_shell_requests()
{
  uint32_t timeout = 0;
  while (timeout < USER_CONFIG_MS_TIMEOUT)
  {
    if (Serial.available())
    {
      if (' ' == Serial.read())
      {
        return 1;
      }
      flush_serial_input();
    }
    delay(USER_CONFIG_POLL_MS_TIMEOUT);
    timeout += USER_CONFIG_POLL_MS_TIMEOUT;
  }
  return 0;
}

/*
 * Handler to allow the user to adjust clock specific variables
 * like the color and so forth
 */
int handle_user_interaction()
{
  Serial.println(F("Welcome to the Serial output of the Morgeb-Clock"));
  Serial.println(F("User configuration phase started, this allows you to persistently change values of the clock"));
  Serial.print(F("If no SPACE key is read for "));
  Serial.print(USER_CONFIG_SEC_TIMEOUT);
  Serial.println(F(" seconds, the clock will start"));
  Serial.println(F("Please press SPACE to start configuration shell"));
  Serial.flush();

  cshell_running = config_shell_requests();
  if (cshell_running)
  {
    shell.attach(Serial);
    shell.addCommand(F("updateVar <update variable value>..."), update_var);
    shell.addCommand(F("printVars <print all variable values>..."), print_vars);
    shell.addCommand(F("exit <exit configuration shell>..."), exit);
    shell.printHelp(0, NULL);
    Serial.print(F("> "));

    while (1 == cshell_running)
    {
      shell.executeIfInput();
    }
  }

  return RET_SUCCESS;
}

/*
 * Setup all cock components and provide
 * the user to configure the clock accordantly
 */
void setup()
{
  int err = init_application();
  handle_error(err);
  Serial.println(F("Initiated Morgeb-Clock components properly"));

  err = handle_user_interaction();
  handle_error(err);
  Serial.println(F("Setup phase done, clock will start showing the time"));

  Serial.flush();
}

/*
 * ISR called when the RTC injects an external interrupt
 */
void wakeupISR()
{
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(RTC_WAKEUP_PIN));
  interrupt_rec = INTERRUPTS::RTC_INTERRUPT;
}

/*
 * ISR called when the timer2 overflows
 */
ISR(TIMER2_OVF_vect)
{
  sleep_disable();
  interrupt_rec = INTERRUPTS::TIMER_INTERRUPT;
}

void update_clock_time()
{
  // compute next wakeup, which is a multiple of 5 and has 0 seconds
  // hence, we substract the current seconds and compute the next smooth minute value
  DateTime now = rtc.now();
  DateTime next_wakeup = now -
                         TimeSpan(0, 0, now.minute(), now.second()) +
                         TimeSpan(0, 0, ((now.minute() + RTC_SLEEP_TIME) / RTC_SLEEP_TIME) * RTC_SLEEP_TIME, 0);
  if (false == rtc.setAlarm1(next_wakeup, DS3231_A1_Minute))
  {
    Serial.println("Failed to set wakeup alarm, microcontroller maybe starve now");
  }

  Serial.print(F("Microcontroller will sleep until "));
  print_time(next_wakeup);

  // #TODO: find a better logic
  DateTime now_five_base = now -
                           TimeSpan(0, 0, now.minute(), now.second()) +
                           TimeSpan(0, 0, ((now.minute()) / RTC_SLEEP_TIME) * RTC_SLEEP_TIME, 0);

  frontpanel.update(now_five_base.hour(), now_five_base.minute(), now_five_base.second());
}

/*
 * Send the mic to POWER DOWN mode to save energy
 * He will be woken up by external interrupts, triggered by the RTC on D2 (nano)
 */
void goSleep()
{
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_IDLE);

  noInterrupts();
  // TODO: remove before fly
  // attachInterrupt(digitalPinToInterrupt(RTC_WAKEUP_PIN), wakeupISR, LOW);
  interrupts();

  sleep_cpu();

  //---------------------------------------------------------------------------
  /* The program will continue from here when it wakes */
  //---------------------------------------------------------------------------

  // TODO: uncomment before fly
  // rtc.disableAlarm(1);
  // rtc.clearAlarm(1);
}

/*
 * Update the time every five minutes
 * Let the microcontroller sleep with in the Power Down mode to save energy
 */
void loop()
{
  // init some timer to wakeup every 16ms
  switch (interrupt_rec)
  {
  case INTERRUPTS::TIMER_INTERRUPT:
  {
    timer_int_count++;
    if (timer_int_count >= 30)
    {
      timer_int_count = 0;
      Serial.println("Received 30 timer interrupts, start a new ADC conversion");
      // TODO: add some ADC conversion
    }
    break;
  }
  case INTERRUPTS::RTC_INTERRUPT:
  {
    Serial.println("Received RTC interrupt, update the clock time");
    update_clock_time();
    break;
  }
  case INTERRUPTS::ADC_INTERRUPT:
  {
    Serial.println("Received ADC interrupt, update clock color");
    break;
  }
  default:
    break;
  }

  interrupt_rec = INTERRUPTS::NONE;
  goSleep();
}