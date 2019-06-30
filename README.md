# Apex5400 Bill Acceptor
* A simple repository for project purposes only.
* Tested on php paper bill as validator.

# Hardware
* Apex5400 Bill Acceptor
* Arduino Mega
* Lcd Screen
* 4x4 matrix keypad
* x3 Servo sg90
* PVC pipe that fits any coin
* Plastic coin (coz i'm using servo sg90)

# Getting started
* Copy this source code to test out your apex5400 bill acceptor
#### Source code
<code>volatile int pulses = 0;</code><br/>
<code>const byte interruptPin = 2;</code><br/>
<code>boolean displayMe = true;</code></br>

<code>void setup() {</code><br/>
&nbsp;&nbsp;&nbsp; <code>Serial.begin(9600);</code><br/>
&nbsp;&nbsp;&nbsp; <code>pinMode(interruptPin,INPUT_PULLUP);</code><br/>
&nbsp;&nbsp;&nbsp; <code>attachInterrupt(0,countPulses,CHANGE);</code><br/>
<code>}</code><br/>
<code>void countPulses(){ </code><br/>
&nbsp;&nbsp;&nbsp; <code>int val = digitalRead(2); </code><br/>
&nbsp;&nbsp;&nbsp; <code>if(val == LOW){ </code><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <code>pulses++; </code><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <code>displayMe = true;</code><br/>
&nbsp;&nbsp;&nbsp; <code>}</code> <br/>
<code>}</code> <br/>
<code>void loop() {</code> <br/>
&nbsp;&nbsp;&nbsp;<code>if(displayMe == true){ </code><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<code>Serial.println(pulses);</code><br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<code>displayMe = false; </code><br/>
&nbsp;&nbsp;&nbsp; <code>}</code> <br/>
<code>}</code></br>
