// This program compiles the Playstation controller button statuses into a 6 byte string.
// The first 2 bytes contain button status and the last 4 contain the thumbstick positions.
// by Adam Kemp, 2012 http://code.google.com/p/smduino/

#include <PS2X_lib.h>  //for v1.6 (Thanks to Bill Porter for a wicked library http://www.billporter.info/playstation-2-controller-arduino-library-v1-0/)

PS2X ps2x; // create PS2 Controller Class

int battLow = 801;  //Batt low value determined from 22k/100k voltage divider. Represents ~3.3V
boolean lowBattWarning = false; //flag for a low battery condition
boolean ledState = false; //used for flashing LED during a low power condition
unsigned long currentTime = 0;

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
  byte buttons = 0;
  byte dPads = 0;
  ps2x.read_gamepad();
  bitWrite(buttons, 0, ps2x.Button(PSB_SELECT)); //byte 1, bit 0
  bitWrite(buttons, 1, ps2x.Button(PSB_START)); //byte , bit 1
  bitWrite(buttons, 2, ps2x.Button(PSB_L1)); //byte 1, bit 2
  bitWrite(buttons, 3, ps2x.Button(PSB_R1)); //byte 1, bit 3
  bitWrite(buttons, 4, ps2x.Button(PSB_L2)); //byte 1, bit 4
  bitWrite(buttons, 5, ps2x.Button(PSB_R2)); //byte 1, bit 5
  bitWrite(buttons, 6, ps2x.Button(PSB_L3)); //byte 1, bit 6
  bitWrite(buttons, 7, ps2x.Button(PSB_R3)); //byte 1, bit 7
  bitWrite(dPads, 0, ps2x.Button(PSB_PAD_UP)); //byte 2, bit 0
  bitWrite(dPads, 1, ps2x.Button(PSB_PAD_DOWN)); //byte 2, bit 1
  bitWrite(dPads, 2, ps2x.Button(PSB_PAD_LEFT)); //byte 2, bit 2
  bitWrite(dPads, 3, ps2x.Button(PSB_PAD_RIGHT)); //byte 2, bit 3
  bitWrite(dPads, 4, ps2x.Button(PSB_GREEN)); //byte 2, bit 4
  bitWrite(dPads, 5, ps2x.Button(PSB_BLUE)); //byte 2, bit 5
  bitWrite(dPads, 6, ps2x.Button(PSB_PINK)); //byte 2, bit 6
  bitWrite(dPads, 7, ps2x.Button(PSB_RED)); //byte 2, bit 7
  Serial.print(buttons); //prints byte 1
  Serial.print(dPads); //prints byte 2
  Serial.print(ps2x.Analog(PSS_LY)); //prints left y thumbstick value
  Serial.print(ps2x.Analog(PSS_LX)); //prints left x thumbstick value
  Serial.print(ps2x.Analog(PSS_RY)); //prints right y thumbstick value
  Serial.print(ps2x.Analog(PSS_RX)); //prints right x thumbstick value
  byte battStat = map(analogRead(0), 801, 1024, 0, 100); //reads batt voltage and calculates a percentage. 3.3v = 0%
  if (battStat <= 10) { //not tested, but checks if the battery is below 10%
    lowBattWarning = true;
  }
  if (lowBattWarning) { //if battery is below 10% start flashing the LED
    if (millis() > currentTime + 1000) {
      currentTime = millis();
      digitalWrite(13, !ledState);
    }
  } 
 delay(100); //rinse, wash, repeat
}
