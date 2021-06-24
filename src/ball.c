#include "ball.h"

void Ball_Setup(struct Ball *ball, UINT8 sprStartIndex, UINT8 tileStartIndex)
{
    set_sprite_tile(sprStartIndex, tileStartIndex);
    ball->sprId = sprStartIndex;

    ball->x = 0;
    ball->y = 0;
    ball->w = 8;
    ball->h = 8;
    ball->vx = 0;
    ball->vy = 0;

    Ball_Reset(ball);
}

void Ball_Reset(struct Ball *ball)
{
    ball->x = 76; // 160 / 2 - 4
    ball->y = 68; // 144 / 2 - 4

    ball->vx = 1; // TODO BB 2021-06-21. Make random.
    ball->vy = 0; // TODO BB 2021-06-21. Make random.
}

void Ball_Move(struct Ball *ball)
{
    ball->x += ball->vx;

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

void Ball_CheckCollision(struct Ball *ball, struct Bat *bat)
{
    // if (ball->x + ball->w > bat->x && ball->x < bat->x + bat->w)
    // {
    //     UINT8 yBot = ball->y - (bat->y + bat->h); // TODO BB Regn ud hvordan jeg finder hvor de rammer hinanden.
    // }

    if (ball->x + ball->w >= bat->x && ball->x < bat->x + bat->w)
        if (bat->y < (UINT8)(bat->y + bat->h))
        {
            if (ball->y + ball->h >= bat->y && ball->y < bat->y + bat->h)
            {
                if ((bat->isBatL && ball->vx < 0) || (!bat->isBatL && ball->vx > 0))
                    ball->vx = -ball->vx;
            }
        }
        else
        {
            if (ball->y < (UINT8)(bat->y + bat->h))
            {
                if ((bat->isBatL && ball->vx < 0) || (!bat->isBatL && ball->vx > 0))
                    ball->vx = -ball->vx;
            }
        }
}