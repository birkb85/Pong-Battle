#include "ball.h"

void Ball_Setup(struct Ball *ball, UINT8 sprStartIndex, UINT8 tileStartIndex)
{
    set_sprite_tile(sprStartIndex, tileStartIndex);
    ball->sprId = sprStartIndex;

    ball->x = 0;
    ball->y = 0;
    ball->w = 8;
    ball->h = 8;
    ball->dirX = 1; // TODO BB 2021-06-21. Make random.
    ball->speedX = 0;
    ball->vy = 0;

    Ball_Reset(ball);
}

void Ball_Reset(struct Ball *ball)
{
    ball->x = 76; //(SCREENWIDTH >> 1) - 4;
    ball->y = 68; //(SCREENHEIGHT >> 1) - 4;

    ball->speedX = 1;
    ball->vy = 0;
}

void Ball_Move(struct Ball *ball)
{
    ball->x += ball->dirX * ball->speedX;

    if (ball->vy < 0 && ball->y + ball->vy >= SCREENHEIGHT - ball->h)
    {
        ball->y = 0;
        ball->vy = -ball->vy;
    }
    else if (ball->vy > 0 && ball->y + ball->vy >= SCREENHEIGHT - ball->h)
    {
        ball->y = SCREENHEIGHT - ball->h;
        ball->vy = -ball->vy;
    }
    else
        ball->y += ball->vy;

    move_sprite(ball->sprId, ball->x + sprOffsetX, ball->y + sprOffsetY);
}

UINT8 ball_batYBot;
UINT8 ball_yDiff;
INT8 ball_yTop;

void Ball_CheckCollision(struct Ball *ball, struct Bat *bat)
{
    if (bat->isBatL && ball->dirX > 0) return;
    if (!bat->isBatL && ball->dirX < 0) return;

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
                    ball->dirX = -ball->dirX;
                    ball->vy = Bat_GetVY(bat);
                    if (ball->vy == 0)
                        ball->speedX = 2;
                    else
                        ball->speedX = 1;
                    Bat_Hit(bat, ball_yTop);
                }
            }
        }
    }
}

void Ball_CheckGoal(struct Ball *ball)
{
    if (ball->x >= SCREENWIDTH && ball->x < 0xFF - ball->w)
        Ball_Reset(ball);
}