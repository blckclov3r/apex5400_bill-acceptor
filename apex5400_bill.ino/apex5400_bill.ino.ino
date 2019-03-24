/*
 * source code: bitbucket.com/blckclov3r
 * Apex5400
 * lcd 16x2
 * led 3x
 * servo 3x
 * keypad 4x4
 */

#include <Wire.h>
#include <String.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

#define led1 44
#define led2 48
#define led3 52

#define servo1 10
#define servo5 11
#define servo10 12

#include <Servo.h>
Servo myservo1;  // create servo object to control a servo
Servo myservo5;
Servo myservo10;
// twelve servo objects can be created on most boards
int pos = 0;    // variable to store the servo position

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

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  myservo1.attach(servo1);
  myservo5.attach(servo5);
  myservo10.attach(servo10);
  myservo1.write(0);
  myservo5.write(0);
  myservo10.write(0);


  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(0, countPulses, CHANGE);
  lcd.setCursor(5, 0);
  lcd.print("RRJD-A");
  lcd.setCursor(0, 1);
  lcd.print("");
  delay(1000);
  lcd.clear();
}


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
  credits();

}
boolean state = true;
void loop() {

  myservo1.write(0);
  myservo5.write(0);
  myservo10.write(0);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  if (!display_condition) {
    insertBill();
    display_condition = true;
    //    lcd.blink();
  }

  char customKey = customKeypad.getKey();
  if (customKey != NO_KEY && pulses != 0) {
    Serial.println(customKey);
    getDisplayABC();
    switch (customKey) {
        lcd.clear();
      case 'A':
        digitalWrite(led1, HIGH);
        if (state == true) {
          Serial.println("You've press letter A");
          state = false;
          if (customKeypad.waitForKey() == 'D') {
            Serial.println("You've press letter D");
            insertBill();
            delay(100);
            for (int i = pulses ; i > 0; i--) {
              pulses = pulses - 1;
              delay(500);
              for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
                // in steps of 1 degree
                myservo1.write(pos);              // tell servo to go to position in variable 'pos'
                delay(1);                       // waits 15ms for the servo to reach the position
              }
              for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
                myservo1.write(pos);              // tell servo to go to position in variable 'pos'
                delay(1);                       // waits 15ms for the servo to reach the position
              }
              insertBill();
              if (pulses == 0 || pulses == -1) {
                pulses = 0;
                display_condition = false;
                break;
              }
            }
          } else {
            displayError();
            lcd.clear();
            credits();
            state = true;
            break;
          }
        } else {
          break;
        }
        break;
      case 'B':
        digitalWrite(led2, HIGH);
        if (state == true) {
          state = false;
          Serial.println("You've press letter B");
          if (customKeypad.waitForKey() == 'D') {
            Serial.println("You've press letter D");
            insertBill();
            for (int i = pulses ; i > 0; i -= 5) {
              pulses = pulses - 5;
              delay(500);
              for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
                // in steps of 1 degree
                myservo5.write(pos);              // tell servo to go to position in variable 'pos'
                delay(1);                       // waits 15ms for the servo to reach the position
              }
              for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
                myservo5.write(pos);              // tell servo to go to position in variable 'pos'
                delay(1);                       // waits 15ms for the servo to reach the position
              }
              insertBill();
              if (pulses == 0 || pulses == -1) {
                pulses = 0;
                state = true;
                display_condition = false;
                break;
              }
            }
          } else {
            displayError();
            break;
          }
        } else {
          break;
        }
        break;
      case 'C':
        digitalWrite(led3, HIGH);
        if (state == true) {
          state = false;
          Serial.println("You've press letter C");
          if (customKeypad.waitForKey() == 'D') {
            Serial.println("You've press letter D");
            insertBill();
            delay(100);
            for (int i = pulses ; i > 0; i -= 10) {
              pulses = pulses - 10;
              delay(500);
              for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
                // in steps of 1 degree
                myservo10.write(pos);              // tell servo to go to position in variable 'pos'
                delay(1);                       // waits 15ms for the servo to reach the position
              }
              for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
                myservo10.write(pos);              // tell servo to go to position in variable 'pos'
                delay(1);                       // waits 15ms for the servo to reach the position
              }
              insertBill();
              if (pulses == 0 || pulses == -1) {
                pulses = 0;
                state = true;
                display_condition = false;
                break;
              }
            }
          } else {
            displayError();
            break;
          }
        } else {
          break;
        }
        break;
      default:
        Serial.println("switch default invoked");
        displayError();
        delay(1000);
        lcd.clear();
        credits();
        display_condition = false;
        break;
    }
  }

  if (displayMe) {
    if (pulses <= 0 || pulses == -1) {
      pulses = 0;
      insertBill();
      display_condition = false;
      state = true;
    }
    display_condition = true;
    Serial.print("displayMe: ");
    Serial.println(pulses);
    displayMe = false;
  }
}

void getDisplayABC() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("[A]=1, [B]=5");
  lcd.setCursor(0, 1);
  lcd.print("[C]=10, [D]=OK");
}

void insertBill() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Insert Bill");
  lcd.setCursor(0, 1);
  lcd.print("Credits: " + String(pulses));
}

void credits() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Credits");
  lcd.setCursor(0, 1);
  lcd.print("Php: " + String(pulses));
}
void displayError() {
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("Error");
  lcd.setCursor(5, 1);
  lcd.print("Error");
  delay(1000);
  getDisplayABC();
  state = true;
}
