#include <LiquidCrystal.h>

/* LiquidCrystal display with:
LCD 4 (RS) to arduino pin 12
LCD 5 (R/W) to ground (non-existent pin 14 okay?)
LCD 6 (E) to arduino pin 11
d4, d5, d6, d7 on arduino pins 7, 8, 9, 10
*/


/*  PSX Controller Decoder Library (Psx.pde)
	Written by: Kevin Ahrendt June 22nd, 2008
	
	Controller protocol implemented using Andrew J McCubbin's analysis.
	http://www.gamesx.com/controldata/psxcont/psxcont.htm
	
	Shift command is based on tutorial examples for ShiftIn and ShiftOut
	functions both written by Carlyn Maw and Tom Igoe
	http://www.arduino.cc/en/Tutorial/ShiftIn
	http://www.arduino.cc/en/Tutorial/ShiftOut

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Psx.h>                                          // Includes the Psx Library 
                                                          // Any pins can be used since it is done in software
#define dataPin 13
#define cmndPin 11
#define attPin 12
#define clockPin 10


LiquidCrystal lcd(5,6,7,38,40,42,44);   //ok

Psx Psx;                                                  // Initializes the library

unsigned int data = 0;                                    // data stores the controller response
unsigned int upkey = 0x0008 ;
unsigned int downkey = 0x0002 ;
unsigned int leftkey = 0x0001 ;
unsigned int rightkey = 0x0004 ;


void setup()
{
  lcd.begin(20, 4);
  lcd.setCursor(0,0);
// Print a message to the LCD.
lcd.print("PS Controller");

  Psx.setupPins(dataPin, cmndPin, attPin, clockPin, 10);  // Defines what each pin is used
//                 11            9    10       8                        // (Data Pin #, Cmnd Pin #, Att Pin #, Clk Pin #, Delay)
  Serial.begin(9600);
 Serial1.begin(9600);

}

void loop()
{
  data = Psx.read();                                      // Psx.read() initiates the PSX controller and returns
  Serial.println(data,HEX);                                   // Display the returned numeric value
  lcd.setCursor(1,1);
  lcd.print("         ");
// Print a message to the LCD.
  lcd.setCursor(1,1);
  lcd.print(data);
  if (data >0)
  {
 
  
    Serial.println(data, DEC) ;
     Serial.print("up(") ;
     Serial.print(data & upkey) ;
     Serial.print(")down(") ;
     Serial.print(data & downkey) ;
     Serial.print(")left(") ;
     Serial.print(data & leftkey) ;
     Serial.print(")right(") ;
     Serial.print(data & rightkey) ;
     Serial.print(")\n") ;
    if   ((data & upkey) == 8)
        Serial1.write("1");
    if   ((data & downkey) == 2)
        Serial1.write("2");
    if   ((data & leftkey) == 1)
        Serial1.write("3");
    if   ((data & rightkey) == 4)
        Serial1.write("4");
        
}

    
  delay(200);
}
