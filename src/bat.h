#ifndef BAT_H
#define BAT_H

#include <gb/gb.h>
#include <string.h>
#include "../res/bat_spr.h"
#include "global.h"

typedef struct Bat
{
    UINT8 sprIds[12];
    UINT8 tileIds[12];
    UINT8 collision[12];
    UINT8 x;
    UINT8 y;
    UINT8 w;
    UINT8 h;
    UINT8 dirY; // 0 = up, 1 = down
    UINT8 forceY;
    UINT8 isBatL;
};

extern void Bat_Setup(struct Bat *bat, UINT8 sprStartIndex, UINT8 tileStartIndex, UINT8 isBatL);
extern UINT8 Bat_GetVY(struct Bat *bat);
extern void Bat_Move(struct Bat *bat);
extern void Bat_Draw(struct Bat *bat);
extern void Bat_Up(struct Bat *bat);
extern void Bat_Down(struct Bat *bat);
extern void Bat_Stop(struct Bat *bat);
extern void Bat_Hit(struct Bat *bat, INT8 yTop);
extern UINT8 Bat_CheckCollision(struct Bat *bat, INT8 yTop);

#endif