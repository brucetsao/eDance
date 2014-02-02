// This program compiles the Playstation controller button statuses into a 6 byte string.
// The first 2 bytes contain button status and the last 4 contain the thumbstick positions.
// by Adam Kemp, 2012 http://code.google.com/p/smduino/

#include <LiquidCrystal.h>

/* LiquidCrystal display with:
LCD 4 (RS) to arduino pin 12
LCD 5 (R/W) to ground (non-existent pin 14 okay?)
LCD 6 (E) to arduino pin 11
d4, d5, d6, d7 on arduino pins 7, 8, 9, 10
*/


#include <PS2X_lib.h>  //for v1.6 (Thanks to Bill Porter for a wicked library http://www.billporter.info/playstation-2-controller-arduino-library-v1-0/)
LiquidCrystal lcd(5,6,7,38,40,42,44);   //ok

PS2X ps2x; // create PS2 Controller Class


void setup(){
  lcd.begin(20, 4);
  lcd.setCursor(0,0);
// Print a message to the LCD.
  lcd.print("PS Dancing Pad");

  Serial.begin(9600);
  ps2x.config_gamepad(10,11,12,13, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
}

void loop(){
  byte buttons = 0x00;
  byte dPads = 0x00;
  ps2x.read_gamepad();
    
/*
  bitWrite(buttons, 0, ps2x.Button(PSB_SELECT)); //byte 1, bit 0
  bitWrite(buttons, 1, ps2x.Button(PSB_START)); //byte , bit 1
  bitWrite(buttons, 2, ps2x.Button(PSB_L1)); //byte 1, bit 2
  bitWrite(buttons, 3, ps2x.Button(PSB_L2)); //byte 1, bit 3
  bitWrite(buttons, 4, ps2x.Button(PSB_R1)); //byte 1, bit 4
  bitWrite(buttons, 5, ps2x.Button(PSB_R2)); //byte 1, bit 5
//  bitWrite(buttons, 6, ps2x.Button(PSB_L3)); //byte 1, bit 6
//  bitWrite(buttons, 7, ps2x.Button(PSB_R3)); //byte 1, bit 7
  bitWrite(dPads, 0, ps2x.Button(PSB_PAD_UP)); //byte 2, bit 0
  bitWrite(dPads, 1, ps2x.Button(PSB_PAD_DOWN)); //byte 2, bit 1
  bitWrite(dPads, 2, ps2x.Button(PSB_PAD_LEFT)); //byte 2, bit 2
  bitWrite(dPads, 3, ps2x.Button(PSB_PAD_RIGHT)); //byte 2, bit 3
  bitWrite(dPads, 4, ps2x.Button(PSB_TRIANGLE)); //byte 2, bit 4
  bitWrite(dPads, 5, ps2x.Button(PSB_CIRCLE)); //byte 2, bit 5
  bitWrite(dPads, 6, ps2x.Button(PSB_CROSS)); //byte 2, bit 6
  bitWrite(dPads, 7, ps2x.Button(PSB_SQUARE)); //byte 2, bit 7
  */
    lcd.clear();
    lcd.print("PS Dancing Pad");

   if (ps2x.Button(PSB_PAD_LEFT))
  {                          
     Serial.println("LEFT pressed")  ;  // the button data
    lcd.setCursor(1,1);
    // Print a message to the LCD.
    lcd.print("LEFT");
  }
  if (ps2x.Button(PSB_PAD_DOWN))
  {                          
     Serial.println("down pressed")   ; // the button data
    lcd.setCursor(8,1);
    // Print a message to the LCD.
    lcd.print("DOWN");
  }
  if (ps2x.Button(PSB_PAD_RIGHT))
  {                          
     Serial.println("RIGHT pressed")  ;  // the button data
    lcd.setCursor(1,2);
    // Print a message to the LCD.
    lcd.print("RIGHT");
  }
  if (ps2x.Button(PSB_PAD_UP))
  {                          
     Serial.println("up pressed")  ;  // the button data
    lcd.setCursor(10,2);
    // Print a message to the LCD.
    lcd.print("UP");
  }
  
  
 delay(200); //rinse, wash, repeat
}

