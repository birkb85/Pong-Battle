#include "ball.h"

const UINT8 ball_forceXMin = 16;

void Ball_Setup(struct Ball *ball, UINT8 sprStartIndex, UINT8 tileStartIndex, UINT8 isInit)
{
    set_sprite_tile(sprStartIndex, tileStartIndex);
    ball->sprId = sprStartIndex;

    ball->x = 76; //(SCREENWIDTH >> 1) - 4;
    ball->y = 68; //(SCREENHEIGHT >> 1) - 4;
    ball->w = 8;
    ball->h = 8;
    if (isInit)
        ball->dirX = 0; // TODO BB 2021-06-21. Make random.
    ball->dirY = 0;
    ball->forceX = ball_forceXMin;
    ball->forceY = 0;
}

UINT8 Ball_GetVX(struct Ball *ball)
{
    return ball->forceX >> 4;
}

UINT8 Ball_GetVY(struct Ball *ball)
{
    return ball->forceY >> 2;
}

void Ball_StopX(struct Ball *ball)
{
    if (ball->forceX > ball_forceXMin)
        ball->forceX --;
}

void Ball_StopY(struct Ball *ball)
{
    if (ball->forceY > 0)
        ball->forceY --;
}

void Ball_Move(struct Ball *ball)
{
    Ball_StopX(ball);
    Ball_StopY(ball);

    if (ball->dirX == 0)
        ball->x -= Ball_GetVX(ball);
    else if (ball->dirX == 1)
        ball->x += Ball_GetVX(ball);

    if (ball->dirY == 0 && ball->y - Ball_GetVY(ball) >= SCREENHEIGHT - ball->h)
    {
        ball->y = 0;
        ball->dirY = 1;
    }
    else if (ball->dirY == 1 && ball->y + Ball_GetVY(ball) >= SCREENHEIGHT - ball->h)
    {
        ball->y = SCREENHEIGHT - ball->h;
        ball->dirY = 0;
    }
    else if (ball->dirY == 0)
        ball->y -= Ball_GetVY(ball);
    else if (ball->dirY == 1)
        ball->y += Ball_GetVY(ball);

    move_sprite(ball->sprId, ball->x + sprOffsetX, ball->y + sprOffsetY);
}

UINT8 ball_batYBot;
UINT8 ball_yDiff;
INT8 ball_yTop;

void Ball_CheckCollision(struct Ball *ball, struct Bat *bat)
{
    if (bat->isBatL && ball->dirX == 1) return;
    if (!bat->isBatL && ball->dirX == 0) return;

    if (ball->x + ball->w >= bat->x && ball->x < bat->x + bat->w)
    {
        ball_batYBot = (UINT8)(bat->y + bat->h);
        if (ball->y < ball_batYBot)
        {
            ball_yDiff = ball_batYBot - ball->y;
            if (ball_yDiff > 0 && ball_yDiff < bat->h + ball->h)
            {
                ball_yTop = bat->h - ball_yDiff;
                if (Bat_CheckCollision(bat, ball_yTop))
                {
                    if (ball->dirX == 1)
                        ball->dirX = 0;
                    else
                        ball->dirX = 1;
                    ball->forceX = 64;
                    ball->dirY = bat->dirY;
                    ball->forceY = Bat_GetVY(bat) << 3;
                    Bat_Hit(bat, ball_yTop);
                }
            }
        }
    }
}

UINT8 Ball_CheckGoal(struct Ball *ball)
{
    if (ball->x >= SCREENWIDTH && ball->x < 0xFF - ball->w)
        return TRUE;
    else
        return FALSE;
}