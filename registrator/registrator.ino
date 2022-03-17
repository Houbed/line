/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to*/
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int Sensor = 10;
const int range = 0;
long timeStart;
long LastCircle;
long BestCircle = -1;
bool Flag = false;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("byHoubed_CO&RO");
  lcd.setCursor(0, 1);
  lcd.print("NT:");
  lcd.setCursor(0, 2);
  lcd.print("LC:");
  lcd.setCursor(0, 3);
  lcd.print("BC:");

  Serial.begin(9600);
  pinMode(Sensor, INPUT);
}

void loop() {
  if (!digitalRead(Sensor) and !Flag){
    while(!digitalRead(Sensor)){}
    Flag = true;
    timeStart = millis();
    }
  else if(!digitalRead(Sensor) and (millis() - timeStart) > 500 and Flag){
    LastCircle = millis() - timeStart;
    Flag = false;
    
    lcd.setCursor(4, 2);
    lcd.print("                ");
    lcd.setCursor(4, 2);
    timer(LastCircle);
    lcd.setCursor(4, 1);
    lcd.print("                ");
   
    if (LastCircle < BestCircle or BestCircle == -1){
      BestCircle = LastCircle;
      lcd.setCursor(3, 3);
      lcd.print("                ");
      lcd.setCursor(4, 3);
      timer(BestCircle);
      }
    }
    else if(Flag){
      lcd.setCursor(4, 1);
      timer(millis()-timeStart);
    }
}
void timer(long time){
      lcd.print(time / 60000);
      lcd.print('.');
      if (time / 1000 % 60 / 10 < 1){
        lcd.print(0);
        lcd.print(time / 1000 % 60);
        }
      else{lcd.print(time / 1000 % 60);}
      lcd.print('.');
      lcd.print(time % 1000);
  }
