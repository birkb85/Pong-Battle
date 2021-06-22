#ifndef BAT_H
#define BAT_H

#include <gb/gb.h>
#include "global.h"

typedef struct Bat
{
    UINT8 sprIds[12];
    UINT8 collision[12];
    UINT8 x;
    UINT8 y;
    UINT8 w;
    UINT8 h;
};

extern void Bat_Setup(struct Bat *bat, UINT8 x, UINT8 y, UINT8 sprStartIndex, UINT8 tileStartIndex);
extern void Bat_Move(struct Bat *bat);
extern void Bat_MoveUp(struct Bat *bat);
extern void Bat_MoveDown(struct Bat *bat);

#endif