rmdir /s /q obj
rmdir /s /q build

mkdir obj
mkdir build

C:\Gameboy\gbdk\bin\lcc -debug -c -o obj\main.o src\main.c
C:\Gameboy\gbdk\bin\lcc -debug -c -o obj\bat.o src\bat.c
C:\Gameboy\gbdk\bin\lcc -debug -c -o obj\ball.o src\ball.c
C:\Gameboy\gbdk\bin\lcc -debug -c -o obj\global.o src\global.c

C:\Gameboy\gbdk\bin\lcc -debug -c -o obj\bat_spr.o res\bat_spr.c
C:\Gameboy\gbdk\bin\lcc -debug -c -o obj\bat_col_spr.o res\bat_col_spr.c
C:\Gameboy\gbdk\bin\lcc -debug -c -o obj\ball_spr.o res\ball_spr.c

C:\Gameboy\gbdk\bin\lcc -debug -o build\PongBattle.gb^
 obj\main.o^
 obj\bat.o^
 obj\ball.o^
 obj\global.o^
 obj\bat_spr.o^
 obj\bat_col_spr.o^
 obj\ball_spr.o
