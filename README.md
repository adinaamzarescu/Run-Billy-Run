# RUN BILLY RUN
![example](https://github.com/adinaamzarescu/Run-Billy-Run/blob/main/Video_run_billy_run.gif)
## Purpose
The purpose of this code is to control a game on an LCD display using an Arduino board. The game involves a player character running and jumping over terrain obstacles. The code utilizes various libraries and defines constants and variables to control the game logic and display.

## Dependencies
The code requires the following libraries to be included:

- `FastIO.h`
- `I2CIO.h`
- `LCD.h`
- `LiquidCrystal.h`
- `LiquidCrystal_I2C.h`
- `LiquidCrystal_I2C_ByVac.h`
- `LiquidCrystal_SI2C.h`
- `LiquidCrystal_SR.h`
- `LiquidCrystal_SR1W.h`
- `LiquidCrystal_SR2W.h`
- `LiquidCrystal_SR3W.h`
- `ProtoStax_MmlMusicPlayer.h`

Make sure these libraries are properly installed and accessible to the Arduino environment.

## Functionality
The code provides functionality for the following components and features:

1. Music playback using MML (Music Macro Language) format.
2. LCD control using I2C communication.
3. Control of LEDs connected to specific pins (`RED_PIN`, `YELLOW_PIN`, `GREEN_PIN`).
4. Terrain sprites for representing different terrain types.
5. Joystick control with an X-axis pin (`Joy_X_axis`).
6. Autostart pin (`Autostartpin`) for triggering the game.
7. Read/write pin (`PIN_READWRITE`) for reading and writing data.
8. Contrast control pin (`PIN_CONTRAST`) for adjusting LCD contrast.
9. Player movement sprites for different player positions.
10. Constants and arrays for defining terrain types and player positions.

The code includes functions for initializing graphics, advancing the terrain, drawing the player, and calculating the score. It uses predefined sprites for the player and terrain, updating their positions and detecting collisions. The LCD display is used to show the game scene, including the terrain and player.

## Getting Started
To use this code, follow these steps:

1. Install the required libraries (`NewliquidCrystal`, `ProtoStax_Mml_Music_Player`) in your Arduino environment.
2. Connect the necessary hardware components (LCD, LEDs, joystick, etc.) to the Arduino board according to the pin definitions in the code.
3. Upload the code to your Arduino board.
4. Interact with the game using the joystick and observe the gameplay on the LCD display.

## Acknowledgements

[1] https://www.arduino.cc/

[2] https://github.com/fmalpartida/New-LiquidCrystal

[3] https://maxpromer.github.io/LCD-Character-Creator/

[4] https://musescore.com/

[5] https://github.com/protostax/ProtoStax_MmlMusicPlayer

[6] https://www.youtube.com/watch?v=NbXp7luU9NU&t=78s
