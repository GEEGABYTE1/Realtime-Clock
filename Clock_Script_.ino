


/*
keyestudio Maker learning kit
Project 31
DS1302 Real Time Clock Module
http//www.keyestudio.com
*/
#include <stdio.h>
#include <string.h>
#include <DS1302.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
/* Set the appropriate digital I/O pin connections */
uint8_t CE_PIN   = 5;    // RST
uint8_t IO_PIN   = 6;   // DAT 
uint8_t SCLK_PIN = 7;  // CLK 

/* Create buffers */
char buf[50];
char bf[50];
char bu[50];
char uf[50];
char day[10];

/* Create a DS1302 object */
DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);

void print_time()
{
  /* Get the current time and date from the chip */
  Time t = rtc.time();

  /* Name the day of the week */
  memset(day, 0, sizeof(day));  /* clear day buffer */
  switch (t.day) {
    case 1:
      strcpy(day, "Sunday   ");
      break;
    case 2:
      strcpy(day, "Monday   ");
      break;
    case 3:
      strcpy(day, "Tuesday  ");
      break;
    case 4:
      strcpy(day, "Wednesday");
      break;
    case 5:
      strcpy(day, "Thursday ");
      break;
    case 6:
      strcpy(day, "Friday   ");
      break;
    case 7:
      strcpy(day, "Saturday ");
      break;
  }

  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
           day,
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);
           Serial.println(buf);
  snprintf(bf, sizeof(bf), "%s  %04d",
          day, t.yr);
  lcd.setCursor(0,0);
  lcd.print(bf);
  snprintf(bu, sizeof(bu),"%02d:%02d:%02d",
           t.hr, t.min, t.sec);
  /* Print the formatted string to serial so we can see the time */
  lcd.setCursor(0,1);
  lcd.print(bu);
  snprintf(uf, sizeof(uf), "%02d-%02d",
         t.mon, t.date);
  lcd.setCursor(11,1);
  lcd.print(uf);
}
void setup()
{
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  rtc.writeProtect(false);
  rtc.halt(false);

  Time t(2016,10,12,12,11,22,4);
  rtc.time(t);
}

void loop()
{
  print_time();
  delay(1000);
}
////////////////////////////////////////////////////////////////
