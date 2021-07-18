#include <gb/gb.h>
#include <stdio.h>
#include <string.h>
#include <rand.h>
#include "../res/bat_spr.h"
#include "../res/ball_spr.h"
#include "bat.h"
#include "ball.h"
#include "../res/splash_data.c"
#include "../res/splash_map.c"

struct Bat batL;
struct Bat batR;

struct Ball ball;

UINT8 controls;
UINT8 isInitialized;

void ResetGame()
{
    set_sprite_data(0, 12, batSpr);
    set_sprite_data(12, 12, batSpr);
    set_sprite_data(24, 1, ballSpr);

    Bat_Setup(&batL, 0, 0, TRUE);
    Bat_Setup(&batR, 12, 12, FALSE);

    Ball_Setup(&ball, 24, 24, isInitialized);
}

void main(void)
{
    isInitialized = FALSE;

    set_bkg_data(0, 244, splash_data);
    set_bkg_tiles(0, 0, 20, 18, splash_map);
    SHOW_BKG;
    DISPLAY_ON;
    waitpad(0xFF);
    waitpadup();
    HIDE_BKG;

    ResetGame();

    SHOW_SPRITES;    

    waitpad(0xFF);
    waitpadup();

    initarand(DIV_REG);

    isInitialized = TRUE;

    while (1)
    {
        controls = joypad();
        if (controls & J_UP)
            Bat_Up(&batL);
        else if (controls & J_DOWN)
            Bat_Down(&batL);
        else
            Bat_Stop(&batL);

        if (controls & J_A)
            Bat_Up(&batR);
        else if (controls & J_B)
            Bat_Down(&batR);
        else
            Bat_Stop(&batR);

        // TODO BB 2021-06-24. Testing making a hole in the left bat.
        if (controls & J_START)
        {
            // Bat_Hit(&batL, 2 /*arand()*/);
            // Bat_CheckCollision(&batL, 2);
        }

        // TODO BB 2021-06-24. Testing making a hole in the right bat.
        if (controls & J_SELECT)
        {
            // Bat_Hit(&batR, arand());
        }

        Bat_Move(&batL);
        Bat_Move(&batR);
        Ball_Move(&ball);        
        Ball_CheckCollision(&ball, &batL);
        Ball_CheckCollision(&ball, &batR);

        if (Ball_CheckGoal(&ball))
        {
            ResetGame();
        }

        wait_vbl_done();
    }
}
