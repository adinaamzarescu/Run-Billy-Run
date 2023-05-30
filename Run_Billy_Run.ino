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
ProtoStax_MmlMusicPlayer music; // Object for playing music using MML format

const int alert_buzzer = 10;   // Pin number for the alert buzzer
const int music_buzzer = 7;     // Pin number for the music buzzer

// MML music data stored in program memory
const char song[] PROGMEM =  {"T160 O4 E4A3 E3A4 G4D3 G3D4 A4E3 A3E4 C4G3 C3G4 E4A3 E3A4 G4D3 G3D4 A4E3 A3E4 C4G3 C3G4 E4A3 E3A4 G4D3 G3D4 A4E3 A3E4 E5B3 E4B4 F5C3 F4C4 G5D3 G4D4 E5B3 E4B4 F5C3 F4C4 G5D3 G4D4 E5B3 E4B4 F5C3 F4C4 G5D3 G4D4 E5B3 E4B4 G5D3 G4D4 C6G2 C5G3 E6C3 E5C4 A5E3 A4E4 C6G2 C5G3 E6C3 E5C4 A5E3 A4E4 G6D2 G5D3 C6G2 C5G3 E6C3 E5C4 G6D2 G5D3 D6A2 D5A3 F6D3 F5D4 A#5F3 A#4F4 D6A2 D5A3 F6D3 F5D4 A#5F3 A#4F4 C6G2 C5G3 E6C3 E5C4 G6D2 G5D3 C6G2 C5G3 E6C3 E5C4 G6D2 G5D3 D6A2 D5A3 F6D3 F5D4 A#5F3 A#4F4 G6. D#6. D6. A#5. C6. G2. <G2.> <F#2.> <G2.> <D#2.> D#6F6 G6A#6 A#6C7 D6G6 D#6F6 G6A#6 A#6C7 D6G6 D#6F6 G6A#6 A#6C7 D6G6 D#6F6 G6A#6 A#6C7 r4 G6A#6 A#6C7 D6G6 D#6F6 G6A#6 A#6C7 D6G6 D#6F6 G6A#6 A#6C7 D6G6 D#6F6 G6A#6 A#6C7 r4 r2 r2 r2 r2 r2 r2 r2"};

// LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
// Object for controlling an LCD display using I2C communication.
// Arguments: (0x27) I2C address of the LCD module,
//            (2, 1, 0, 4, 5, 6, 7) Pin numbers for the I2C communication,
//            (3) Number of columns in the LCD display,
//            (POSITIVE) Type of LCD display (can be either POSITIVE or NEGATIVE)

// LED Pins
#define RED_PIN 13         // Pin number for the red LED
#define YELLOW_PIN 12      // Pin number for the yellow LED
#define GREEN_PIN 8        // Pin number for the green LED

// Terrain Sprites
#define SPRITE_TERRAIN_EMPTY ' '             // Sprite representation for empty terrain
#define SPRITE_TERRAIN_SOLID 5               // Sprite representation for solid terrain
#define SPRITE_TERRAIN_SOLID_RIGHT 6         // Sprite representation for solid terrain on the right side
#define SPRITE_TERRAIN_SOLID_LEFT 7          // Sprite representation for solid terrain on the left side

// Joystick
#define Joy_X_axis 2                         // Pin number for the X-axis of the joystick

#define Autostartpin 1                        // Pin number for autostart

#define PIN_READWRITE 10                      // Pin number for read/write

#define PIN_CONTRAST 12                       // Pin number for contrast control

// Player Movement Sprites
#define SPRITE_RUN1 1                         // Sprite representation for running state 1
#define SPRITE_RUN2 2                         // Sprite representation for running state 2
#define SPRITE_JUMP 3                         // Sprite representation for jumping state
#define SPRITE_JUMP_UPPER '.'                 // Sprite representation for upper part of the jump
#define SPRITE_JUMP_LOWER 4                   // Sprite representation for lower part of the jump

// Player Constants
#define PLAYER_HORIZONTAL_POSITION 1         // Horizontal position of the player

// Terrain Constants
#define TERRAIN_WIDTH 16                      // Width of the terrain
#define TERRAIN_EMPTY 0                       // Constant representing empty terrain
#define TERRAIN_LOWER_BLOCK 1                 // Constant representing lower block terrain
#define TERRAIN_UPPER_BLOCK 2                 // Constant representing upper block terrain

// Player Position Constants
#define PLAYER_POSITION_OFF 0                 // Player position when off
#define PLAYER_POSITION_RUN_LOWER_1 1         // Player position when running in the lower part (state 1)
#define PLAYER_POSITION_RUN_LOWER_2 2         // Player position when running in the lower part (state 2)
#define PLAYER_POSITION_JUMP_1 3              // Player position during jump (state 1)
#define PLAYER_POSITION_JUMP_2 4              // Player position during jump (state 2)
#define PLAYER_POSITION_JUMP_3 5              // Player position during jump (state 3)
#define PLAYER_POSITION_JUMP_4 6              // Player position during jump (state 4)
#define PLAYER_POSITION_JUMP_5 7              // Player position during jump (state 5)
#define PLAYER_POSITION_JUMP_6 8              // Player position during jump (state 6)
#define PLAYER_POSITION_JUMP_7 9              // Player position during jump (state 7)
#define PLAYER_POSITION_JUMP_8 10             // Player position during jump (state 8)
#define PLAYER_POSITION_RUN_UPPER_1 11        // Player position when running in the upper part (state 1)
#define PLAYER_POSITION_RUN_UPPER_2 12        // Player position when running in the upper part (state 2)


static char terrainUpper[TERRAIN_WIDTH + 1];  // Array to store the upper terrain characters
static char terrainLower[TERRAIN_WIDTH + 1];  // Array to store the lower terrain characters
static bool buttonPushed = false;             // Flag to indicate if the button has been pushed

void initializeGraphics(){
  static byte graphics[] = {
    // Run position 1
    B11100,
    B11100,
    B10001,
    B01110,
    B11100,
    B01100,
    B11010,
    B10011,
    // Run position 2
    B11100,
    B11100,
    B10001,
    B01110,
    B01100,
    B01100,
    B01100,
    B01110,
    // Jump
    B11100,
    B11100,
    B10000,
    B01100,
    B11110,
    B01101,
    B11111,
    B10000,
    // Jump lower
    B11110,
    B01101,
    B11111,
    B10000,
    B00000,
    B00000,
    B00000,
    B00000,
    // Enemy
    B11111,
    B11111,
    B10101,
    B11111,
    B11111,
    B01110,
    B01010,
    B11011,
    // Enemy right
    B11100,
    B11100,
    B10100,
    B11100,
    B11100,
    B11000,
    B01000,
    B01100,
    // Enemy left
    B00111,
    B00111,
    B00101,
    B00111,
    B00111,
    B00011,
    B00010,
    B00110
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
void advanceTerrain(char* terrain, byte newTerrain) {
  for (int i = 0; i < TERRAIN_WIDTH; ++i) {
    // Retrieve the current character at index i
    char current = terrain[i];

    // Retrieve the next character at index i+1,
    // or use newTerrain if i is at the last index
    char next = (i == TERRAIN_WIDTH-1) ? newTerrain : terrain[i+1];

    // Determine the behavior based on the current character
    switch (current) {
      case SPRITE_TERRAIN_EMPTY:
        // If the next character is a solid terrain,
        // set the current character to solid terrain moving to the right,
        // otherwise, set it to an empty terrain.
        terrain[i] = (next == SPRITE_TERRAIN_SOLID) ? SPRITE_TERRAIN_SOLID_RIGHT : SPRITE_TERRAIN_EMPTY;
        break;
      case SPRITE_TERRAIN_SOLID:
        // If the next character is an empty terrain,
        // set the current character to solid terrain moving to the left,
        // otherwise, keep it as a solid terrain.
        terrain[i] = (next == SPRITE_TERRAIN_EMPTY) ? SPRITE_TERRAIN_SOLID_LEFT : SPRITE_TERRAIN_SOLID;
        break;
      case SPRITE_TERRAIN_SOLID_RIGHT:
        // If the current character is a solid terrain moving to the right,
        // set it back to a solid terrain.
        terrain[i] = SPRITE_TERRAIN_SOLID;
        break;
      case SPRITE_TERRAIN_SOLID_LEFT:
        // If the current character is a solid terrain moving to the left,
        // set it to an empty terrain.
        terrain[i] = SPRITE_TERRAIN_EMPTY;
        break;
    }
  }
}

bool drawPlayer(byte position, char* terrainUpper, char* terrainLower, unsigned int score) {
  bool collide = false;

  // Save the original characters at the player's position
  char upper_save = terrainUpper[PLAYER_HORIZONTAL_POSITION];
  char lower_save = terrainLower[PLAYER_HORIZONTAL_POSITION];

  // Variables to store the updated characters for the upper and lower terrain
  byte upper, lower;

  // Determine the characters based on the player's position
  switch (position) {
    case PLAYER_POSITION_OFF:
      // Player is off the screen, both upper and lower terrain are empty
      upper = lower = SPRITE_TERRAIN_EMPTY;
      break;
    case PLAYER_POSITION_RUN_LOWER_1:
      // Player is running on the lower terrain, use SPRITE_RUN1 for lower
      upper = SPRITE_TERRAIN_EMPTY;
      lower = SPRITE_RUN1;
      break;
    case PLAYER_POSITION_RUN_LOWER_2:
      // Player is running on the lower terrain, use SPRITE_RUN2 for lower
      upper = SPRITE_TERRAIN_EMPTY;
      lower = SPRITE_RUN2;
      break;
    case PLAYER_POSITION_JUMP_1:
    case PLAYER_POSITION_JUMP_8:
      // Player is jumping, use SPRITE_JUMP for both upper and lower
      upper = SPRITE_TERRAIN_EMPTY;
      lower = SPRITE_JUMP;
      break;
    case PLAYER_POSITION_JUMP_2:
    case PLAYER_POSITION_JUMP_7:
      // Player is jumping, use SPRITE_JUMP_UPPER for upper and SPRITE_JUMP_LOWER for lower
      upper = SPRITE_JUMP_UPPER;
      lower = SPRITE_JUMP_LOWER;
      break;
    case PLAYER_POSITION_JUMP_3:
    case PLAYER_POSITION_JUMP_4:
    case PLAYER_POSITION_JUMP_5:
    case PLAYER_POSITION_JUMP_6:
      // Player is jumping, use SPRITE_JUMP for upper and empty for lower
      upper = SPRITE_JUMP;
      lower = SPRITE_TERRAIN_EMPTY;
      break;
    case PLAYER_POSITION_RUN_UPPER_1:
      // Player is running on the upper terrain, use SPRITE_RUN1 for upper
      upper = SPRITE_RUN1;
      lower = SPRITE_TERRAIN_EMPTY;
      break;
    case PLAYER_POSITION_RUN_UPPER_2:
      // Player is running on the upper terrain, use SPRITE_RUN2 for upper
      upper = SPRITE_RUN2;
      lower = SPRITE_TERRAIN_EMPTY;
      break;
  }

  // Update terrain characters and check for collision
  if (upper != ' ') {
    terrainUpper[PLAYER_HORIZONTAL_POSITION] = upper;
    collide = (upper_save == SPRITE_TERRAIN_EMPTY) ? false : true;
  }
  if (lower != ' ') {
    terrainLower[PLAYER_HORIZONTAL_POSITION] = lower;
    collide |= (lower_save == SPRITE_TERRAIN_EMPTY) ? false : true;
  }

  // Calculate the number of digits in the score
  byte digits = (score > 9999) ? 5 : (score > 999) ? 4 : (score > 99) ? 3 : (score > 9) ? 2 : 1;

  // Draw the scene on the LCD display
  // Null-terminate terrainUpper and terrainLower strings
  terrainUpper[TERRAIN_WIDTH] = '\0';
  terrainLower[TERRAIN_WIDTH] = '\0';
  // Store the character at index (16 - digits) in terrainUpper in a temporary variable
  char temp = terrainUpper[16 - digits];
  // Remove the character at index (16 - digits) in terrainUpper by null-terminating the string
  terrainUpper[16 - digits] = '\0';
  // Set the cursor position on the LCD to the first row, first column
  lcd.setCursor(0, 0);
  // Print the terrainUpper string on the LCD
  lcd.print(terrainUpper);
  // Restore the temporarily removed character in terrainUpper
  terrainUpper[16 - digits] = temp;
  // Set the cursor position on the LCD to the second row, first column
  lcd.setCursor(0, 1);
  // Print the terrainLower string on the LCD
  lcd.print(terrainLower);

  // Print the score on the LCD display
  lcd.setCursor(16 - digits,0);
  lcd.print(score);

  // Restore the original characters at the player's position
  terrainUpper[PLAYER_HORIZONTAL_POSITION] = upper_save;
  terrainLower[PLAYER_HORIZONTAL_POSITION] = lower_save;

  // Return the collision status
  return collide;
}

// Handle the button push as an interrupt
void buttonPush() {
  buttonPushed = true;
}

static bool playing = false;

void setup(){
  // Initialize serial communication at a baud rate of 9600
  Serial.begin(9600);

  // Set the pin modes for various pins
  pinMode(PIN_READWRITE, OUTPUT);
  digitalWrite(PIN_READWRITE, LOW);
  pinMode(PIN_CONTRAST, OUTPUT);
  digitalWrite(PIN_CONTRAST, LOW);
  pinMode(Joy_X_axis, INPUT);
  digitalWrite(Joy_X_axis, HIGH);
  pinMode(Autostartpin, OUTPUT);
  digitalWrite(Autostartpin, HIGH);

  // Attach an interrupt to interrupt 0 (Digital pin 2) to detect button push
  attachInterrupt(0, buttonPush, FALLING);

  // Initialize graphics
  initializeGraphics();

  // Initialize the LCD display with 16 columns and 2 rows
  lcd.begin(16, 2);

  // Set the pin modes for LEDs
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);

  // Set the pin mode for the alert buzzer
  pinMode(alert_buzzer, OUTPUT);

  // Begin the buzzer for playing music
  music.begin(music_buzzer);

  Serial.println("Setup complete");
}

void loop() {
  // Game variables
  static byte player_position = PLAYER_POSITION_RUN_LOWER_1;
  static byte newTerrainType = TERRAIN_EMPTY;
  static byte newTerrainDuration = 1;
  static bool playing = false;
  static bool blink = false;
  static unsigned int distance = 0;

  // Turn off the buzzer that announces the jump
  digitalWrite(alert_buzzer, 0);

  // If not currently playing the game
  if (!playing) {
    // Display the player or blinking cursor depending on the blink flag
    drawPlayer((blink) ? PLAYER_POSITION_OFF : player_position, terrainUpper, terrainLower, distance >> 3);

    // Blink "Push to Start" message
    if (blink) {
      lcd.setCursor(0, 0);
      lcd.print("Push to  Start");
    }

    // Delay for 250 milliseconds
    delay(250);

    // Toggle the blink flag
    blink = !blink;

    // If the button is pushed, start the game
    if (buttonPushed) {
      // Display countdown on LCD and blink LEDs
      // RED
      lcd.setCursor(0,0);
      lcd.print("Start in 3    ");
      for (int intensity = 0; intensity <= 255; intensity++) {
        analogWrite(RED_PIN, intensity);
        delay(5);
      }
      for (int intensity = 255; intensity >= 0; intensity--) {
        analogWrite(RED_PIN, intensity);
        delay(5);
      }
      Serial.print("RED LED DONE");
      // YELLOW
      lcd.setCursor(0,0);
      lcd.print("Start in 2    ");
      for (int intensity = 0; intensity <= 255; intensity++) {
        analogWrite(YELLOW_PIN, intensity);
        delay(5);
      }
      for (int intensity = 255; intensity >= 0; intensity--) {
        analogWrite(YELLOW_PIN, intensity);
        delay(5);
      }
      Serial.print("YELLOW LED DONE");
      // GREEN
      lcd.setCursor(0,0);
      lcd.print("Start in 1    ");
      for (int intensity = 0; intensity <= 255; intensity++) {
        analogWrite(GREEN_PIN, intensity);
        delay(5);
      }
      for (int intensity = 255; intensity >= 0; intensity--) {
        analogWrite(GREEN_PIN, intensity);
        delay(5);
      }
      delay(5);
      Serial.print("GREEN LED DONE");

      // Clear the LCD display
      lcd.setCursor(0,0);
      lcd.print("      GO      ");
      delay(250);
      lcd.setCursor(0,0);
      lcd.print("              ");

      // Initialize game graphics and variables
      initializeGraphics();
      player_position = PLAYER_POSITION_RUN_LOWER_1;
      playing = true;
      buttonPushed = false;
      distance = 0;

      // Start playing the game music
      if (!music.isPlaying()) {
        music.play_P(song);
      }
    }
    return;
  }

  // Game logic
  {
    // Shift the terrain to the left
    advanceTerrain(terrainLower, newTerrainType == TERRAIN_LOWER_BLOCK ? SPRITE_TERRAIN_SOLID : SPRITE_TERRAIN_EMPTY);
    advanceTerrain(terrainUpper, newTerrainType == TERRAIN_UPPER_BLOCK ? SPRITE_TERRAIN_SOLID : SPRITE_TERRAIN_EMPTY);
    
    // Generate new terrain to enter on the right
    if (--newTerrainDuration == 0) {
      if (newTerrainType == TERRAIN_EMPTY) {
        newTerrainType = (random(3) == 0) ? TERRAIN_UPPER_BLOCK : TERRAIN_LOWER_BLOCK;
        newTerrainDuration = 2 + random(10);
      } else {
        newTerrainType = TERRAIN_EMPTY;
        newTerrainDuration = 10 + random(10);
      }
    }

    // When the button is pushed, play a sound to announce the jump
    if (buttonPushed) {
        digitalWrite(alert_buzzer, 1);
        delay(100);
        digitalWrite(alert_buzzer, 0);
    }
      
    if (buttonPushed) {
      if (player_position <= PLAYER_POSITION_RUN_LOWER_2) player_position = PLAYER_POSITION_JUMP_1;
      buttonPushed = false;
    }  

    // Update player position and distance
    if (drawPlayer(player_position, terrainUpper, terrainLower, distance >> 3)) {
      // Collision occurred
      playing = false;
      music.stop();
    } else {
      if (player_position == PLAYER_POSITION_RUN_LOWER_2 || player_position == PLAYER_POSITION_JUMP_8) {
        player_position = PLAYER_POSITION_RUN_LOWER_1;
      } else if ((player_position >= PLAYER_POSITION_JUMP_3 && player_position <= PLAYER_POSITION_JUMP_5) && terrainLower[PLAYER_HORIZONTAL_POSITION] != SPRITE_TERRAIN_EMPTY) {
        player_position = PLAYER_POSITION_RUN_UPPER_1;
      } else if (player_position >= PLAYER_POSITION_RUN_UPPER_1 && terrainLower[PLAYER_HORIZONTAL_POSITION] == SPRITE_TERRAIN_EMPTY) {
        player_position = PLAYER_POSITION_JUMP_5;
      } else if (player_position == PLAYER_POSITION_RUN_UPPER_2) {
        player_position = PLAYER_POSITION_RUN_UPPER_1;
      } else {
        ++player_position;
      }
      ++distance;

      // Adjust Autostartpin based on terrain
      digitalWrite(Autostartpin, terrainLower[PLAYER_HORIZONTAL_POSITION + 2] == SPRITE_TERRAIN_EMPTY ? HIGH : LOW);
    }
    delay(100);
  }

  // Print debug information
  Serial.print("Character Position: ");
  Serial.println(player_position);
  Serial.print("Distance: ");
  Serial.println(distance);
}
