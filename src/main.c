#include <gb/gb.h>
#include <stdio.h>
#include <string.h>
#include <rand.h>
#include "../res/bat_spr.h"
#include "../res/bat_col_spr.h"
#include "../res/ball_spr.h"
#include "bat.h"
#include "ball.h"

UINT8 tempSpr[16];

struct Bat batL;
struct Bat batR;

struct Ball ball;

UINT8 controls;

UINT8 yTop;
UINT8 sprNbStart;
UINT8 sprNbStartBitsHit;

void main(void)
{
    memset(tempSpr, 0, 16);

    set_sprite_data(0, 12, batSpr);
    set_sprite_data(12, 12, batSpr);
    set_sprite_data(24, 12, batColSpr);
    set_sprite_data(36, 1, ballSpr);

    Bat_Setup(&batL, 8, 24, 0, 0, TRUE);
    Bat_Setup(&batR, 144, 24, 12, 12, FALSE);

    Ball_Setup(&ball, 24, 36);

    SHOW_SPRITES;
    DISPLAY_ON;

    waitpad(0xFF);

    initarand(DIV_REG);

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

        // TODO BB Tester at kopiere sprite til ram, modificere den og sætte den ind i stedet for en anden.. Slet efter test.
        if (controls & J_SELECT)
        {
            memcpy(&tempSpr, &ballSpr, 16);
            memset(&tempSpr[4], 0, 4);
            set_sprite_data(0, 1, tempSpr);
        }

        // TODO BB 2021-06-24. Testing making a hole in the left bat.
        if (controls & J_START)
        {
            yTop = arand();
            if (yTop < batL.h)
            {
                sprNbStart = yTop >> 3;
                sprNbStartBitsHit = yTop - (sprNbStart << 3);

                batL.collision[sprNbStart] &= 0xFF << (8 - sprNbStartBitsHit);
                for (UINT8 i = 0; i < 8; i++)
                    if ((batL.collision[sprNbStart] >> i) & 0x01)
                        memcpy(&tempSpr[(7 - i) << 1], &batSpr[(sprNbStart << 4) + ((7 - i) << 1)], 2);
                    else
                        memset(&tempSpr[(7 - i) << 1], 0x00, 2);
                set_sprite_data(sprNbStart, 1, tempSpr);

                if (sprNbStartBitsHit > 0 && sprNbStart < (sizeof(batL.collision) - 1))
                {
                    batL.collision[sprNbStart + 1] &= 0xFF >> sprNbStartBitsHit;
                    for (UINT8 i = 0; i < 8; i++)
                        if ((batL.collision[sprNbStart + 1] >> i) & 0x01)
                            memcpy(&tempSpr[(7 - i) << 1], &batSpr[((sprNbStart + 1) << 4) + ((7 - i) << 1)], 2);
                        else
                            memset(&tempSpr[(7 - i) << 1], 0x00, 2);
                    set_sprite_data(sprNbStart + 1, 1, tempSpr);
                }
            }
        }

        Ball_Move(&ball);
        Ball_CheckCollision(&ball, &batL);
        Ball_CheckCollision(&ball, &batR);

        wait_vbl_done();
    }
}
