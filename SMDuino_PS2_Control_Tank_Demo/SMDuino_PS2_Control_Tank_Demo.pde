// This program is intended as a simple test that data is being properly recieved from the controller.
// Data is recieved as a 6 byte packet. Bytes 3 & 5 are read and used to drive a 2 servo tank robot.
// by Adam Kemp, 2012 http://code.google.com/p/smduino/

#include <Servo.h>

Servo lServo; //init servos
Servo rServo;
byte lServoPos; //servo position var
byte rServoPos;
byte buttons = 0; //button byte
byte dPads = 0; //dpads byte
byte LY = 128; //neutral value for servo position (in byte form)
byte LX = 128;
byte RY = 128;
byte RX = 128;

byte LYOffset = 0; //offset is designed to account for thumbstick wiggle
byte RYOffset = 0;

void setup() {
  Serial.begin(57600);
  pinMode(13, OUTPUT);
  lServo.attach(8);
  rServo.attach(9);
  calibrate(); //read neutral thumbstick positions
}

void loop() {
  if (Serial.available() >= 6) { //waits until the 6 bytes are read into buffer
    buttons = Serial.read(); //reads byte 1
    dPads = Serial.read(); //reads byte 2
    LY = Serial.read(); //reads byte 3
    LX = Serial.read(); //reads byte 4
    RY = Serial.read(); //reads byte 5
    RX = Serial.read(); //reads byte 6
    Serial.flush(); //clears buffer
    LY = 255 - LY; //inverts LY value
    if (LY <= LYOffset) { //attaches LY offset to inverted value
      LY == LYOffset;
    }      
    lServoPos = map(LY-LYOffset, 0, 255, 0, 180); //converts the thumbstick byte value to a 0 - 180 value for the servos
    rServoPos = map(RY+RYOffset, 0, 255, 0, 180);
    if (lServoPos >= 70 && lServoPos <= 110) { //if value is within a NULL range, turn off the servo
      lServoPos = 90;
    }
    if (rServoPos >= 70 && rServoPos <= 110) {
      rServoPos = 90;
    }
    lServo.write(lServoPos); //drives the servos
    rServo.write(rServoPos);
    delay(15);
  }
}

void calibrate() {
  for (int i = 0; i < 5; i++) { //loop for 5 seconds
    digitalWrite(13, HIGH);
    if (Serial.available() >= 6) {
      buttons = Serial.read();
      dPads = Serial.read();
      LY = Serial.read();
      LX = Serial.read();
      RY = Serial.read();
      RX = Serial.read();
      LYOffset = 128 - LY; //determines the value away from 128 that the thumbsticks see as neutral
      RYOffset = 128 - RY;
      Serial.flush(); //clears serial buffer
      break;
    }
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
  }
}
