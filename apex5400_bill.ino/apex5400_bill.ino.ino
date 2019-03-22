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
char pass[5];
boolean display_condition = false;
void countPulses() {
  int val = digitalRead(2);
  display_condition = true;
  if (val == LOW) {
    lcd.clear();
    pulses += 1;
    displayMe = true;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Credits");
  lcd.setCursor(0, 1);
  lcd.print("Php: " + String(pulses));

}

void loop() {

  char customKey = customKeypad.getKey();
  if (customKey != NO_KEY) {
    Serial.println(customKey);
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
    Serial.print("displayMe: ");
    Serial.println(pulses);
    displayMe = false;
  }

  if (pulses == 20) {
    Serial.println("Pulses == 20");
    delay(1000);
    getDisplayABC();
    if (customKeypad.waitForKey() == 'A') {
      Serial.println("You've press letter A");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Select Amount");
      lcd.setCursor(0, 1);
      pass[0] = customKeypad.waitForKey();
      pass[1] = customKeypad.waitForKey();
      pass[2] = customKeypad.waitForKey();
      lcd.print(pass);
      pass[3] = '\0';
      if (pass[3] == '\0') {
        Serial.println("pass[3] == null");
        Serial.println(pass);
        if (customKeypad.waitForKey() == 'D') {
          Serial.println("Keypad pressed D");
          if (pass[0] == '0' && pass[1] == '1' && pass[2] == '0') {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Insert Money");
            lcd.setCursor(0, 1);
            lcd.print("Credits: " + String(pulses));
            delay(100);
            for (int i = pulses ; i > 10; i--) {
              pulses = pulses - 1;
              delay(500);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Insert Money");
              lcd.setCursor(0, 1);
              lcd.print("Credits: " + String(pulses));
            }

            Serial.print("Pulse update: ");
            Serial.println(pulses);



          } else if (pass[0] == '0' && pass[1] == '2' && pass[2] == '0') {
            pulses = pulses - 20;
            lcd.clear();
            Serial.print("[1]Pulses: ");
            Serial.println(pulses);
            lcd.setCursor(0, 0);
            lcd.print("Insert Money");
            lcd.setCursor(0, 1);
            lcd.print("Credits: " + String(pulses));
            Serial.print("Pulse update: ");
            Serial.println(pulses);
          } else {
            lcd.clear();
            lcd.setCursor(2, 0);
            lcd.print("Try Again");
            lcd.setCursor(5, 1);
            lcd.print("Error");
          }
        }
      }
    }
  } else if (pulses == 40) {
    getDisplayABC();
  } else if (pulses == 50) {
    getDisplayABC();
  } else if (pulses == 60) {
    getDisplayABC();
  } else if (pulses == 70) {
    getDisplayABC();
  } else if (pulses == 80) {
    getDisplayABC();
  } else if (pulses == 90) {
    getDisplayABC();
  } else if (pulses == 100) {
    getDisplayABC();
  } else if (pulses == 120) {
    getDisplayABC();
  } else if (pulses == 150) {
    getDisplayABC();
  }



}





void getDisplayABC() {
  delay(5000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("A=1,B=5,C=10");
  lcd.setCursor(0, 1);
  lcd.print("D=ENTER");

}

