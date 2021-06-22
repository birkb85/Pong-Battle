# Pong-Battle
A 2-player Pong battling game for the Game Boy<br/>

## Newest release
Find newest release here:<br/>
https://github.com/birkb85/Pong-Battle/releases<br/>

## Want to compile the project yourself?
Get GBDK from here:<br/>
https://gbdk-2020.github.io/gbdk-2020/<br/>
Unzip the file and place the gbdk folder here:<br/>
*C:\Gameboy\gbdk*<br/>

Then get the source code for Pong Battle from this repository.<br/>
Run the file:<br/>
*make.bat*<br/>
This will compile the game.<br/>
Now go to the *build* folder, here you will find the rom file:<br/>
*PongBattle.gb*<br/>

## Want to work on the game yourself?
It is set up to be able to use the Emulicious emulator for debugging.<br/>
Get Emulicious from here:<br/>
https://emulicious.net/<br/>
Start the emulator then go to *Tools* -> *Remote Debugging* and click *Enabled*.<br/>

Get Visual Studio Code (VSCode) from here:<br/>
https://code.visualstudio.com/<br/>
Install it together with the *Emulicious Debugger* extension.<br/>

Then you are able to run the game from VSCode.<br/>
The project is set up in VSCode to automatically compile the game before running it in the emulator.<br/>
(remember that the Emulicious emulator has to be running for VSCode to use it)<br/>
