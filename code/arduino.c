; arduino

#include <Wire.h>
#include "paj7620.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define GES_REACTION_TIME   300       // You can adjust the reaction time according to the actual circumstance.
#define GES_ENTRY_TIME      500       // When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
#define GES_QUIT_TIME     1000

void setup()
{
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  Serial.println("\nPAJ7620U2 TEST DEMO: Recognize 9 gestures.");

  lcd.setCursor(0, 0);
  lcd.print("    Gesture    ");
  lcd.setCursor(0, 1);
  lcd.print("  Recognition  ");
  delay(4000);

  uint8_t error = 0;

  error = paj7620Init();      // initialize Paj7620 registers
  if (error)
  {
    Serial.print("INIT ERROR,CODE:");
    Serial.println(error);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("INIT ERROR,CODE:");
    lcd.setCursor(0, 1);
    lcd.print(error);
    delay(3000);
  }
  else
  {
    Serial.println("INIT OK");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("INIT OK");
    delay(3000);
  }
  Serial.println("Please input your gestures:\n");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Input Your");
  lcd.setCursor(0, 1);
  lcd.print("Gestures");
  delay(3000);
}

void loop()
{
  uint8_t data = 0, data1 = 0, error;

  error = paj7620ReadReg(0x43, 1, &data);       // Read Bank_0_Reg_0x43/0x44 for gesture result.
  if (!error)
  {
    switch (data)
    { // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).
      case GES_RIGHT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if (data == GES_FORWARD_FLAG)
        {
          Serial.println("Forward");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Forward");
          delay(GES_QUIT_TIME);
        }
        else if (data == GES_BACKWARD_FLAG)
        {
          Serial.println("Backward");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Right");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Right");
        }
        break;

      case GES_LEFT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if (data == GES_FORWARD_FLAG)
        {
          Serial.println("Forward");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Forward");
          delay(GES_QUIT_TIME);
        }
        else if (data == GES_BACKWARD_FLAG)
        {
          Serial.println("Backward");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Left");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Left");
        }
        break;

      case GES_UP_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if (data == GES_FORWARD_FLAG)
        {
          Serial.println("Forward");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Forward");
          delay(GES_QUIT_TIME);
        }
        else if (data == GES_BACKWARD_FLAG)
        {
          Serial.println("Backward");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Up");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Up");
        }
        break;

      case GES_DOWN_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if (data == GES_FORWARD_FLAG)
        {
          Serial.println("Forward");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Forward");
          delay(GES_QUIT_TIME);
        }
        else if (data == GES_BACKWARD_FLAG)
        {
          Serial.println("Backward");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Down");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Down");
        }
        break;

      case GES_FORWARD_FLAG:
        Serial.println("Forward");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Forward");
        delay(GES_QUIT_TIME);
        break;

      case GES_BACKWARD_FLAG:
        Serial.println("Backward");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Backward");
        delay(GES_QUIT_TIME);
        break;

      case GES_CLOCKWISE_FLAG:
        Serial.println("Clockwise");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Clockwise");
        break;

      case GES_COUNT_CLOCKWISE_FLAG:
        Serial.println("anti-clockwise");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Anti-Clockwise");
        break;

      default:
        paj7620ReadReg(0x44, 1, &data1);
        if (data1 == GES_WAVE_FLAG)
        {
          Serial.println("wave");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Wave");
        }
        break;
    }
  }
  delay(100);
}