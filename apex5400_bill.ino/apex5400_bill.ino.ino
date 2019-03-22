#include <Keypad.h>
#include <Wire.h>
#include <String.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

const byte interruptPin = 2;
boolean displayMe = true;

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {22, 24, 26, 28}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {30, 32, 34, 36}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//A = 1 B = 5 = C 10

int pulses = 0;
void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(0, countPulses, CHANGE);
  lcd.setCursor(5, 0);
  lcd.print("RRJD-A");
  lcd.setCursor(0, 1);
  lcd.print("");
  delay(1000);
  lcd.clear();



}
int value = 0;

boolean display_condition = false;
void countPulses() {
  lcd.clear();
  int val = digitalRead(2);
  display_condition = true;
  if (val == LOW) {
    lcd.clear();
    pulses += 1;
    displayMe = true;
  }

  lcd.setCursor(0, 0);
  lcd.print("Credits");
  lcd.setCursor(0, 1);
  lcd.print("Php: " + String(pulses));

}
boolean state = true;
void loop() {

  char customKey = customKeypad.getKey();
  if (customKey != NO_KEY) {
    Serial.println(customKey);
    getDisplayABC();
    if ( customKey == 'A' && state == true) {
      state = false;
      if (customKeypad.waitForKey() == 'D') {
        Serial.println("You've press letter A");
        lcd.clear();
        delay(100);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Insert Money");
        lcd.setCursor(0, 1);
        lcd.print("Credits: " + String(pulses));
        delay(100);
        for (int i = pulses ; i > 0; i--) {
          pulses = pulses - 1;
          delay(500);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Insert Money");
          lcd.setCursor(0, 1);
          lcd.print("Credits: " + String(pulses));
          if (pulses == 0) {
            state = true;
          }
        }
        Serial.print("Pulse update: "); Serial.println(pulses);
      }
    } else if (customKeypad.waitForKey() == 'B' || customKeypad.waitForKey() == 'C') {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("Error");
      lcd.setCursor(5, 1);
      lcd.print("Error");
      delay(3000);
      getDisplayABC();
      state = true;
      return;
    }else{
      return;
    }



    if (customKey == 'B' && state == true) {
      state = false;
      if (customKeypad.waitForKey() == 'D') {
        Serial.println("You've press letter B");
        lcd.clear();
        delay(100);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Insert Money");
        lcd.setCursor(0, 1);
        lcd.print("Credits: " + String(pulses));
        delay(100);
        for (int i = pulses ; i > 0; i -= 5) {
          pulses = pulses - 5;
          delay(500);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Insert Money");
          lcd.setCursor(0, 1);
          lcd.print("Credits: " + String(pulses));
          if (pulses == 0) {
            state = true;
          }
        }
      }
      Serial.print("Pulse update: "); Serial.println(pulses);
    } else if (customKeypad.waitForKey() == 'A' || customKeypad.waitForKey() == 'C') {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("Error");
      lcd.setCursor(5, 1);
      lcd.print("Error");
      delay(3000);
      getDisplayABC();
      state = true;
      return;
    }else{
      return;
    }

    if (customKey == 'C' && state == true) {
      state = false;
      if (customKeypad.waitForKey() == 'D') {
        Serial.println("You've press letter C");
        lcd.clear();
        delay(100);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Insert Money");
        lcd.setCursor(0, 1);
        lcd.print("Credits: " + String(pulses));
        delay(100);
        for (int i = pulses ; i > 0; i -= 10) {
          pulses = pulses - 10;
          delay(500);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Insert Money");
          lcd.setCursor(0, 1);
          lcd.print("Credits: " + String(pulses));
          if (pulses == 0) {
            state = true;
          }
        }
      }
      Serial.print("Pulse update: "); Serial.println(pulses);
    } else if (customKeypad.waitForKey() == 'A' || customKeypad.waitForKey() == 'B') {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("Error");
      lcd.setCursor(5, 1);
      lcd.print("Error");
      delay(3000);
      getDisplayABC();
      state = true;
      return;
    }else{
      return;
    }

  }


  if (!display_condition) {
    lcd.setCursor(0, 0);
    lcd.print("Insert money");
    lcd.setCursor(0, 1);
    lcd.print("");
    display_condition = true;
    lcd.blink();
  }

  if (displayMe) {
    if (pulses <= 0) {
      pulses = 0;
    }
    Serial.print("displayMe: ");
    Serial.println(pulses);
    displayMe = false;
  }






}


void getDisplayABC() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("A=1, B=5, C=10");
  lcd.setCursor(0, 1);
  lcd.print("D=ENTER");

}

