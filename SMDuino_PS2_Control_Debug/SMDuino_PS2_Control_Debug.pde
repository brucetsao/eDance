// This program displays the raw button and thumbstick information back to your XBee host.
// It is intended for debug purposes, but can be used as is for control.
// by Adam Kemp, 2012 http://code.google.com/p/smduino/

#include <PS2X_lib.h>  //for v1.6 (Thanks to Bill Porter for a wicked library http://www.billporter.info/playstation-2-controller-arduino-library-v1-0/)

PS2X ps2x; // create PS2 Controller Class

int battLow = 801; //Batt low value determined from 22k/100k voltage divider. Represents ~3.3V

void setup(){
 Serial.begin(57600);
  pinMode(13, OUTPUT);
  for (int i = 0; i < 4; i++) { //check status LED
    digitalWrite(13, LOW);
    delay(50);
    digitalWrite(13, HIGH);
    delay(50);
  }
  digitalWrite(13, HIGH);
  ps2x.config_gamepad(3,5,6,4, false, false);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
}

void loop(){
  ps2x.read_gamepad();
  Serial.print(ps2x.Button(PSB_SELECT)); //byte 1, bit 0
  Serial.print(" ");
  Serial.print(ps2x.Button(PSB_START)); //byte 1, bit 1
  Serial.print(" ");
  Serial.print(ps2x.Button(PSB_L1)); //byte 1, bit 2
  Serial.print(" ");
  Serial.print(ps2x.Button(PSB_R1)); //byte 1, bit 3
  Serial.print(" ");
  Serial.print(ps2x.Button(PSB_L2)); //byte 1, bit 4
  Serial.print(" ");
  Serial.print(ps2x.Button(PSB_R2)); //byte 1, bit 5
  Serial.print(" ");
  Serial.print(ps2x.Button(PSB_L3)); //byte 1, bit 6
  Serial.print(" ");
  Serial.print(ps2x.Button(PSB_R3)); //byte 1, bit 7
  Serial.print(" ");
  Serial.print(ps2x.Button(PSB_PAD_UP)); //byte 2, bit 0
  Serial.print(" ");
  Serial.print(ps2x.Button(PSB_PAD_DOWN)); //byte 2, bit 1
  Serial.print(" ");
  Serial.print(ps2x.Button(PSB_PAD_LEFT)); //byte 2, bit 2
  Serial.print(" ");
  Serial.print(ps2x.Button(PSB_PAD_RIGHT)); //byte 2, bit 3
  Serial.print(" ");
  Serial.print(ps2x.Button(PSB_GREEN)); //byte 2, bit 4
  Serial.print(" ");
  Serial.print(ps2x.Button(PSB_BLUE)); //byte 2, bit 5
  Serial.print(" ");
  Serial.print(ps2x.Button(PSB_PINK)); //byte 2, bit 6
  Serial.print(" ");
  Serial.print(ps2x.Button(PSB_RED)); //byte 2, bit 7
  Serial.print(" ");
  Serial.print(ps2x.Analog(PSS_LY)); //byte 3
  Serial.print(" ");
  Serial.print(ps2x.Analog(PSS_LX)); //byte 4
  Serial.print(" ");
  Serial.print(ps2x.Analog(PSS_RY)); //byte 5
  Serial.print(" ");
  Serial.print(ps2x.Analog(PSS_RX)); //byte 6
  Serial.print(" ");
  Serial.print(analogRead(0), battLow, 1024, 0, 100)); //displays battery level as a percentage.
  delay(100);
}
