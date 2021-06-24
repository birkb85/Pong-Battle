#include <gb/gb.h>
#include <stdio.h>
#include <string.h>
#include "../res/bat_spr.h"
#include "../res/ball_spr.h"
#include "bat.h"
#include "ball.h"

UINT8 tempSpr[16];

struct Bat batL;
struct Bat batR;

struct Ball ball;

UINT8 controls;

void main(void)
{
    memset(tempSpr, 0, 16);

    set_sprite_data(0, 24, batSpr);
    set_sprite_data(24, 1, ballSpr);

    Bat_Setup(&batL, 8, 24, 0, 0, TRUE);
    Bat_Setup(&batR, 144, 24, 12, 12, FALSE);

    Ball_Setup(&ball, 24, 24);

    SHOW_SPRITES;
    DISPLAY_ON;

    while (1)
    {
        controls = joypad();
        if (controls & J_UP)
            Bat_MoveUp(&batL);
        if (controls & J_DOWN)
            Bat_MoveDown(&batL);
        if (controls & J_A)
            Bat_MoveUp(&batR);
        if (controls & J_B)
            Bat_MoveDown(&batR);

        // Tester at kopiere sprite til ram, modificere den og sætte den ind i stedet for en anden.
        if (controls & J_START)
        {
            for (UINT8 i = 0; i < 24; i++)
            {
                memcpy(&tempSpr, &ballSpr, 16);
                memset(&tempSpr + 4, 0, 4);
                set_sprite_data(i, 1, tempSpr);
            }
        }

        Ball_Move(&ball);
        Ball_CheckCollision(&ball, &batL);
        Ball_CheckCollision(&ball, &batR);

        wait_vbl_done();
    }
}
