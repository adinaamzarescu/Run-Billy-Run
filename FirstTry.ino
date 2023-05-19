//i2C library
#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_I2C_ByVac.h>
#include <LiquidCrystal_SI2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR1W.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>
#include <ProtoStax_MmlMusicPlayer.h>

// Music
ProtoStax_MmlMusicPlayer music;

const int buzzer = 10;
const int music_buzzer = 7;

const char song[] PROGMEM =  {"T160 O4 E4A3 E3A4 G4D3 G3D4 A4E3 A3E4 C4G3 C3G4 E4A3 E3A4 G4D3 G3D4 A4E3 A3E4 C4G3 C3G4 E4A3 E3A4 G4D3 G3D4 A4E3 A3E4 E5B3 E4B4 F5C3 F4C4 G5D3 G4D4 E5B3 E4B4 F5C3 F4C4 G5D3 G4D4 E5B3 E4B4 F5C3 F4C4 G5D3 G4D4 E5B3 E4B4 G5D3 G4D4 C6G2 C5G3 E6C3 E5C4 A5E3 A4E4 C6G2 C5G3 E6C3 E5C4 A5E3 A4E4 G6D2 G5D3 C6G2 C5G3 E6C3 E5C4 G6D2 G5D3 D6A2 D5A3 F6D3 F5D4 A#5F3 A#4F4 D6A2 D5A3 F6D3 F5D4 A#5F3 A#4F4 C6G2 C5G3 E6C3 E5C4 G6D2 G5D3 C6G2 C5G3 E6C3 E5C4 G6D2 G5D3 D6A2 D5A3 F6D3 F5D4 A#5F3 A#4F4 G6. D#6. D6. A#5. C6. G2. <G2.> <F#2.> <G2.> <D#2.> D#6F6 G6A#6 A#6C7 D6G6 D#6F6 G6A#6 A#6C7 D6G6 D#6F6 G6A#6 A#6C7 D6G6 D#6F6 G6A#6 A#6C7 r4 G6A#6 A#6C7 D6G6 D#6F6 G6A#6 A#6C7 D6G6 D#6F6 G6A#6 A#6C7 D6G6 D#6F6 G6A#6 A#6C7 r4 r2 r2 r2 r2 r2 r2 r2"};

// LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

// LEDS
#define RED_BUTTON 13
#define YELLOW_BUTTON 12
#define GREEN_BUTTON 8

#define SPRITE_TERRAIN_EMPTY ' '      

#define SPRITE_TERRAIN_SOLID 5

#define SPRITE_TERRAIN_SOLID_RIGHT 6

#define SPRITE_TERRAIN_SOLID_LEFT 7

#define Joy_X_axis 2

#define Autostartpin 1

#define PIN_READWRITE 10

#define PIN_CONTRAST 12


#define SPRITE_RUN1 1

#define SPRITE_RUN2 2

#define SPRITE_JUMP 3

#define SPRITE_JUMP_UPPER '.'        
#define SPRITE_JUMP_LOWER 4


#define BOY_HORIZONTAL_POSITION 1   

#define TERRAIN_WIDTH 16
#define TERRAIN_EMPTY 0
#define TERRAIN_LOWER_BLOCK 1
#define TERRAIN_UPPER_BLOCK 2

#define BOY_POSITION_OFF 0          // boy is invisible
#define BOY_POSITION_RUN_LOWER_1 1  // boy is running on lower row (pose 1)
#define BOY_POSITION_RUN_LOWER_2 2  //                              (pose 2)

#define BOY_POSITION_JUMP_1 3       // Starting a jump
#define BOY_POSITION_JUMP_2 4       // Half-way up
#define BOY_POSITION_JUMP_3 5       // Jump is on upper row
#define BOY_POSITION_JUMP_4 6       // Jump is on upper row
#define BOY_POSITION_JUMP_5 7       // Jump is on upper row
#define BOY_POSITION_JUMP_6 8       // Jump is on upper row
#define BOY_POSITION_JUMP_7 9       // Half-way down
#define BOY_POSITION_JUMP_8 10      // About to land

#define BOY_POSITION_RUN_UPPER_1 11 // boy is running on upper row (pose 1)
#define BOY_POSITION_RUN_UPPER_2 12 //                              (pose 2)

static char terrainUpper[TERRAIN_WIDTH + 1];
static char terrainLower[TERRAIN_WIDTH + 1];
static bool buttonPushed = false;

void initializeGraphics(){
  static byte graphics[] = {
    // Run position 1
    B01100,
    B01100,
    B00000,
    B01110,
    B11100,
    B01100,
    B11010,
    B10011,
    // Run position 2
    B01100,
    B01100,
    B00000,
    B01100,
    B01100,
    B01100,
    B01100,
    B01110,
    // Jump
    B01100,
    B01100,
    B00000,
    B11110,
    B01101,
    B11111,
    B10000,
    B00000,
    // Jump lower
    B11110,
    B01101,
    B11111,
    B10000,
    B00000,
    B00000,
    B00000,
    B00000,
    // Tree
    B00100,
    B01110,
    B11111,
    B00100,
    B01110,
    B11111,
    B00100,
    B00100,
    // Tree right
    B00001,
    B00011,
    B00111,
    B00001,
    B00011,
    B00111,
    B00001,
    B00001,
    // Tree left
    B10000,
    B11000,
    B11100,
    B10000,
    B11000,
    B11100,
    B10000,
    B10000,
  };
  int i;
  // Skip using character 0, this allows lcd.print() to be used to
  // quickly draw multiple characters
  for (i = 0; i < 7; ++i) {
    lcd.createChar(i + 1, &graphics[i * 8]);
  }
  for (i = 0; i < TERRAIN_WIDTH; ++i) {
    terrainUpper[i] = SPRITE_TERRAIN_EMPTY;
    terrainLower[i] = SPRITE_TERRAIN_EMPTY;
  }
}

// Slide the terrain to the left in half-character increments
//
void advanceTerrain(char* terrain, byte newTerrain) {
  for (int i = 0; i < TERRAIN_WIDTH; ++i) {
    char current = terrain[i];
    char next = (i == TERRAIN_WIDTH-1) ? newTerrain : terrain[i+1];
    switch (current){
      case SPRITE_TERRAIN_EMPTY:
        terrain[i] = (next == SPRITE_TERRAIN_SOLID) ? SPRITE_TERRAIN_SOLID_RIGHT : SPRITE_TERRAIN_EMPTY;
        break;
      case SPRITE_TERRAIN_SOLID:
        terrain[i] = (next == SPRITE_TERRAIN_EMPTY) ? SPRITE_TERRAIN_SOLID_LEFT : SPRITE_TERRAIN_SOLID;
        break;
      case SPRITE_TERRAIN_SOLID_RIGHT:
        terrain[i] = SPRITE_TERRAIN_SOLID;
        break;
      case SPRITE_TERRAIN_SOLID_LEFT:
        terrain[i] = SPRITE_TERRAIN_EMPTY;
        break;
    }
  }
}

bool drawBoy(byte position, char* terrainUpper, char* terrainLower, unsigned int score) {
  bool collide = false;
  char upperSave = terrainUpper[BOY_HORIZONTAL_POSITION];
  char lowerSave = terrainLower[BOY_HORIZONTAL_POSITION];
  byte upper, lower;
  switch (position) {
    case BOY_POSITION_OFF:
      upper = lower = SPRITE_TERRAIN_EMPTY;
      break;
    case BOY_POSITION_RUN_LOWER_1:
      upper = SPRITE_TERRAIN_EMPTY;
      lower = SPRITE_RUN1;
      break;
    case BOY_POSITION_RUN_LOWER_2:
      upper = SPRITE_TERRAIN_EMPTY;
      lower = SPRITE_RUN2;
      break;
    case BOY_POSITION_JUMP_1:
    case BOY_POSITION_JUMP_8:
      upper = SPRITE_TERRAIN_EMPTY;
      lower = SPRITE_JUMP;
      break;
    case BOY_POSITION_JUMP_2:
    case BOY_POSITION_JUMP_7:
      upper = SPRITE_JUMP_UPPER;
      lower = SPRITE_JUMP_LOWER;
      break;
    case BOY_POSITION_JUMP_3:
    case BOY_POSITION_JUMP_4:
    case BOY_POSITION_JUMP_5:
    case BOY_POSITION_JUMP_6:
      upper = SPRITE_JUMP;
      lower = SPRITE_TERRAIN_EMPTY;
      break;
    case BOY_POSITION_RUN_UPPER_1:
      upper = SPRITE_RUN1;
      lower = SPRITE_TERRAIN_EMPTY;
      break;
    case BOY_POSITION_RUN_UPPER_2:
      upper = SPRITE_RUN2;
      lower = SPRITE_TERRAIN_EMPTY;
      break;
  }
  if (upper != ' ') {
    terrainUpper[BOY_HORIZONTAL_POSITION] = upper;
    collide = (upperSave == SPRITE_TERRAIN_EMPTY) ? false : true;
  }
  if (lower != ' ') {
    terrainLower[BOY_HORIZONTAL_POSITION] = lower;
    collide |= (lowerSave == SPRITE_TERRAIN_EMPTY) ? false : true;
  }
  
  byte digits = (score > 9999) ? 5 : (score > 999) ? 4 : (score > 99) ? 3 : (score > 9) ? 2 : 1;
  
  // Draw the scene
  terrainUpper[TERRAIN_WIDTH] = '\0';
  terrainLower[TERRAIN_WIDTH] = '\0';
  char temp = terrainUpper[16-digits];
  terrainUpper[16-digits] = '\0';
  lcd.setCursor(0,0);
  lcd.print(terrainUpper);
  terrainUpper[16-digits] = temp;  
  lcd.setCursor(0,1);
  lcd.print(terrainLower);
  
  lcd.setCursor(16 - digits,0);
  lcd.print(score);

  terrainUpper[BOY_HORIZONTAL_POSITION] = upperSave;
  terrainLower[BOY_HORIZONTAL_POSITION] = lowerSave;
  return collide;
}

// Handle the button push as an interrupt
void buttonPush() {
  buttonPushed = true;
}

static bool playing = false;

void setup(){
  Serial.begin(9600);
  pinMode(PIN_READWRITE, OUTPUT);
  digitalWrite(PIN_READWRITE, LOW);
  pinMode(PIN_CONTRAST, OUTPUT);
  digitalWrite(PIN_CONTRAST, LOW);
  pinMode(Joy_X_axis, INPUT);
  digitalWrite(Joy_X_axis, HIGH);
  pinMode(Autostartpin, OUTPUT);
  digitalWrite(Autostartpin, HIGH);
  
  // Digital pin 2 maps to interrupt 0
  attachInterrupt(0/*PIN_BUTTON*/, buttonPush, FALLING);
  
  initializeGraphics();
  
  lcd.begin(16, 2);

  pinMode(buzzer, OUTPUT);
  pinMode(GREEN_BUTTON, OUTPUT);
  pinMode(YELLOW_BUTTON, OUTPUT);
  pinMode(RED_BUTTON, OUTPUT);

  music.begin(music_buzzer);
  delay(100);

}

void loop() {

  // Game
  static byte boyPos = BOY_POSITION_RUN_LOWER_1;
  static byte newTerrainType = TERRAIN_EMPTY;
  static byte newTerrainDuration = 1;
  static bool playing = false;
  static bool blink = false;
  static unsigned int distance = 0;
  digitalWrite(buzzer, 0);
  
  if (!playing) {
    drawBoy((blink) ? BOY_POSITION_OFF : boyPos, terrainUpper, terrainLower, distance >> 3);
    if (blink) {
      lcd.setCursor(0,0);
      lcd.print("Push to  Start");
    }
    delay(250);
    blink = !blink;
    if (buttonPushed) {
      // RED
      lcd.setCursor(0,0);
      lcd.print("Start in 3    ");
      // Turn the LED on
      for (int intensity = 0; intensity <= 255; intensity++) {
        analogWrite(RED_BUTTON, intensity);
        delay(10); // Delay between intensity changes
      }
      // Turn the LED off
      for (int intensity = 255; intensity >= 0; intensity--) {
        analogWrite(RED_BUTTON, intensity);
        delay(10); // Delay between intensity changes
      }
      // YELLOW
      lcd.setCursor(0,0);
      lcd.print("Start in 2    ");
      // Turn the LED on
      for (int intensity = 0; intensity <= 255; intensity++) {
        analogWrite(YELLOW_BUTTON, intensity);
        delay(10); // Delay between intensity changes
      }
      // Turn the LED off
      for (int intensity = 255; intensity >= 0; intensity--) {
        analogWrite(YELLOW_BUTTON, intensity);
        delay(10); // Delay between intensity changes
      }
      // GREEN
      lcd.setCursor(0,0);
      lcd.print("Start in 1    ");
      // Turn the LED on
      for (int intensity = 0; intensity <= 255; intensity++) {
        analogWrite(GREEN_BUTTON, intensity);
        delay(10); // Delay between intensity changes
      }
      // Turn the LED off
      for (int intensity = 255; intensity >= 0; intensity--) {
        analogWrite(GREEN_BUTTON, intensity);
        delay(10); // Delay between intensity changes
      }
      delay(10);
      lcd.setCursor(0,0);
      lcd.print("      GO      ");
      delay(10);
      lcd.setCursor(0,0);
      lcd.print("              ");

      initializeGraphics();
      boyPos = BOY_POSITION_RUN_LOWER_1;
      playing = true;
      buttonPushed = false;
      distance = 0;

      if (!music.isPlaying()) {
        music.play_P(song);
      }

    }
    return;
  }

  {
    // Shift the terrain to the left
    advanceTerrain(terrainLower, newTerrainType == TERRAIN_LOWER_BLOCK ? SPRITE_TERRAIN_SOLID : SPRITE_TERRAIN_EMPTY);
    advanceTerrain(terrainUpper, newTerrainType == TERRAIN_UPPER_BLOCK ? SPRITE_TERRAIN_SOLID : SPRITE_TERRAIN_EMPTY);
    
    // Make new terrain to enter on the right
    if (--newTerrainDuration == 0) {
      if (newTerrainType == TERRAIN_EMPTY) {
        newTerrainType = (random(3) == 0) ? TERRAIN_UPPER_BLOCK : TERRAIN_LOWER_BLOCK;
        newTerrainDuration = 2 + random(10);
      } else {
        newTerrainType = TERRAIN_EMPTY;
        newTerrainDuration = 10 + random(10);
      }
    }

    if(buttonPushed) {
        digitalWrite(buzzer, 1);
        delay(100);
        digitalWrite(buzzer, 0);
    }
      
    if (buttonPushed) {
      if (boyPos <= BOY_POSITION_RUN_LOWER_2) boyPos = BOY_POSITION_JUMP_1;
      buttonPushed = false;
    }  

    if (drawBoy(boyPos, terrainUpper, terrainLower, distance >> 3)) {
      playing = false; // The boy collided with something. Too bad.
      music.stop();
    } else {
      if (boyPos == BOY_POSITION_RUN_LOWER_2 || boyPos == BOY_POSITION_JUMP_8) {
        boyPos = BOY_POSITION_RUN_LOWER_1;
      } else if ((boyPos >= BOY_POSITION_JUMP_3 && boyPos <= BOY_POSITION_JUMP_5) && terrainLower[BOY_HORIZONTAL_POSITION] != SPRITE_TERRAIN_EMPTY) {
        boyPos = BOY_POSITION_RUN_UPPER_1;
      } else if (boyPos >= BOY_POSITION_RUN_UPPER_1 && terrainLower[BOY_HORIZONTAL_POSITION] == SPRITE_TERRAIN_EMPTY) {
        boyPos = BOY_POSITION_JUMP_5;
      } else if (boyPos == BOY_POSITION_RUN_UPPER_2) {
        boyPos = BOY_POSITION_RUN_UPPER_1;
      } else {
        ++boyPos;
      }
      ++distance;
      
      digitalWrite(Autostartpin, terrainLower[BOY_HORIZONTAL_POSITION + 2] == SPRITE_TERRAIN_EMPTY ? HIGH : LOW);
    }
    delay(100);
  }

  // Print debug information
  Serial.print("Character Position: ");
  Serial.println(boyPos);
  Serial.print("Distance: ");
  Serial.println(distance);
}
