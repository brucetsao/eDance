/*

Simon Game (Genius, for Brazilian users)
Author: Alex Porto

For more information, please check http://dalpix.com/blog

Notes: This game uses PS2XLib to integrate PlayStation 2 with Arduino. 
       This library is was developed by Bill Porter

*/

#include <PS2X_lib.h>

#define MAX_LEDS          4      // Maximum number of leds to play
#define DELAY_PLAY_START  1000   // Initial delay during playtime
#define DELAY_PLAY_MIN    100    // Minimum delay during playtime. Delay will decay down to this value
#define DELAY_PLAY_DECAY  50     // Delay decreasing step.
#define BUTTON_START      255
#define BUTTON_1          0
#define BUTTON_2          1  
#define BUTTON_3          2
#define BUTTON_4          3
#define NO_BUTTON         -1

#define PIN_SPEAKER      3
#define PIN_LED_1        31
#define PIN_LED_2        33
#define PIN_LED_3        35
#define PIN_LED_4        37

#define GAMEPAD_CLK      8
#define GAMEPAD_CMD      9
#define GAMEPAD_ATT      10
#define GAMEPAD_DAT      11 

#define MAX_SEQUENCE     256

#define TONE_ERROR          956

PS2X ps2x;
byte pin[MAX_LEDS] = {PIN_LED_1, PIN_LED_2, PIN_LED_3, PIN_LED_4};
int play_tones[MAX_LEDS] = {10, 30, 75, 110};
byte sequence[MAX_SEQUENCE];
byte stage;
int wait;

void shuffle()
{    
  for (int i=0; i<stage; i++) {
    sequence[i] = random(MAX_LEDS);
  }
}

void play_tone(int tone)
{
  analogWrite(PIN_SPEAKER, tone);
}

void set_all_leds(int state)
{
  for (int i=0; i<MAX_LEDS; i++) {    
    digitalWrite(pin[i], state); 
  }    
}

void blink_all(int count, int time)
{
  for (int i=0; i<count; i++) {    
    for (int j=0; j<MAX_LEDS; j++) {    
      digitalWrite(pin[j], HIGH); 
    }
    delay(time);
    for (int j=0; j<MAX_LEDS; j++) {    
      digitalWrite(pin[j], LOW); 
    }
    delay(time/2);
  }    
}

void blink_one(byte pin_number, int count, int time)
{
  for (int i=0; i<count; i++) {    
    digitalWrite(pin[pin_number], HIGH); 
    delay(time);
    digitalWrite(pin[pin_number], LOW); 
    delay(time/2);
  }    
}

void play_sequence()
{
  for (int i=0; i<stage; i++) {
    Serial.print("Play ");
    Serial.print (sequence[i], DEC);
    Serial.println();
    digitalWrite(pin[sequence[i]], HIGH);
    play_tone(play_tones[sequence[i]]);
    delay(wait);
    play_tone(0);
    digitalWrite(pin[sequence[i]], LOW);
    delay(100);
  }   
  delay(200);
  blink_all(5, 50); 
}

int read_buttons()
{
  ps2x.read_gamepad(false, 0);

  if (ps2x.Button(PSB_START)) return BUTTON_START; 
  if (ps2x.Button(PSB_PAD_UP)) return BUTTON_1;
  if (ps2x.Button(PSB_PAD_RIGHT)) return BUTTON_2;
  if (ps2x.Button(PSB_PAD_LEFT)) return BUTTON_3;
  if (ps2x.Button(PSB_PAD_DOWN)) return BUTTON_4;

  return NO_BUTTON;
}

void blink_error(byte pin)
{
  play_tone(255);
  blink_one(pin, 20, 50);
  play_tone(0);
}

boolean get_players_commands()
{
  int seqidx = 0;
  boolean error = false;
  int button;
  do {
    int expected = sequence[seqidx];
    seqidx++;

    unsigned long time = millis() + wait * 2;
    int pressed = 0;
    button = NO_BUTTON;
    Serial.print("Waiting button ");
    Serial.print (expected, DEC);
    Serial.println();
    do { 
      if (button == NO_BUTTON) {
        button = read_buttons();
        if (button != NO_BUTTON) {
          if (button == BUTTON_START) {
            Serial.println("restart");
            return false;
          } 
          else {
            if (button == expected) {
              play_tone(play_tones[expected]);
              digitalWrite(pin[button], HIGH); 
              Serial.println("Correct button");
              time = time - wait; // Doesn't need to wait for player action, so let's just spend the regular time with led lit and sound "sounding" :)
            } 
            else {
              Serial.println("Wrong button");
              blink_error(button);
              return false;
            }
          } 
        } 
      } 
      else {
        delay(50);
      }      
      Serial.print("time:");
      Serial.print(time, DEC);
      Serial.print(" - ");
      Serial.println(millis(), DEC);
    } 
    while (millis() < time);

    if (button == NO_BUTTON) {
      Serial.println("Nobody played.");
      blink_error(expected);
      return false;
    }

    play_tone(0);    
    set_all_leds(LOW);    
  } 
  while (seqidx < stage);

  return true;
}

void initialize()
{
  stage = 1;
  wait = DELAY_PLAY_START;  
  randomSeed(millis());
  Serial.println("Starting game...");
  blink_all(1, 1000);
}

void blink_success()
{
  set_all_leds(LOW);
  delay(100);
  for (int i=0; i<3; i++) {
    for (int j=0; j<MAX_LEDS;j++) {
      blink_one(j, 1, 50);
    }
  }
  set_all_leds(LOW);
  delay(500);
}

void show_demo()
{
  boolean light = true;
  int light_counter = 0;
  do {
    if (light) {
      digitalWrite(pin[0], LOW); 
      digitalWrite(pin[1], HIGH); 
      digitalWrite(pin[2], HIGH);       
      digitalWrite(pin[3], LOW); 
      //set_all_leds(HIGH);
    } else {
      digitalWrite(pin[0], HIGH);       
      digitalWrite(pin[1], LOW); 
      digitalWrite(pin[2], LOW); 
      digitalWrite(pin[3], HIGH); 
      //set_all_leds(LOW);
    }      
    delay(20);
    light_counter++;
    if (light_counter == 50) {
      light_counter = 0;
      light = !light;
    }
  } while (read_buttons() != BUTTON_START);
  set_all_leds(LOW);
  delay(500);
}

void setup() {                
  Serial.begin(9600);

  for (int i=0; i<MAX_LEDS; i++) {    
    pinMode(pin[i], OUTPUT);     
  }
  pinMode(PIN_SPEAKER, OUTPUT);     

  initialize();
  stage=0;

  int error = ps2x.config_gamepad(GAMEPAD_CLK, GAMEPAD_CMD, GAMEPAD_ATT, GAMEPAD_DAT,false,false);   
  Serial.print("ps2 joystick = ");
  Serial.println(error);
  
}

void loop() {
  stage++;
  if (stage == (MAX_SEQUENCE)-1) {
    initialize();
  }

  set_all_leds(0);
  shuffle();
  play_sequence();
  if (get_players_commands()) {
    blink_success();
    wait -= DELAY_PLAY_DECAY;
    if (wait < DELAY_PLAY_MIN) {
      wait = DELAY_PLAY_MIN;
    } 
  } 
  else {
    show_demo();
    stage = (MAX_SEQUENCE)-2;
  }
} 

