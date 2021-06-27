#ifndef BALL_H
#define BALL_H

#include <gb/gb.h>
#include "global.h"
#include "bat.h"

struct Ball
{
    UINT8 sprId;
    UINT8 x;
    UINT8 y;
    UINT8 w;
    UINT8 h;
    INT8 forceX;
    INT8 forceY;
};

extern void Ball_Setup(struct Ball *ball, UINT8 sprStartIndex, UINT8 tileStartIndex);
extern INT8 Ball_GetVX(struct Ball *ball);
extern INT8 Ball_GetVY(struct Ball *ball);
extern void Ball_Move(struct Ball *ball);
extern void Ball_CheckCollision(struct Ball *ball, struct Bat *bat);
extern UINT8 Ball_CheckGoal(struct Ball *ball);

#endif