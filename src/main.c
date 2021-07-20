#include <gb/gb.h>
#include <stdio.h>
#include <string.h>
#include <rand.h>
#include "ball.h"
#include "bat.h"
#include "score.h"
#include "../res/ball_spr.h"
#include "../res/bat_spr.h"
#include "../res/score_spr.h"
#include "../res/splash_data.c"
#include "../res/splash_map.c"

struct Bat batL;
struct Bat batR;

struct Ball ball;

UINT8 controls;

struct Score scoreL;
struct Score scoreR;

void ShowTitleScreen()
{
    set_bkg_data(0, 244, splash_data);
    set_bkg_tiles(0, 0, 20, 18, splash_map);
    SHOW_BKG;
    DISPLAY_ON;
    waitpad(J_START | J_SELECT);
    waitpadup();
    HIDE_BKG;
    Global_ClearBKG();
}

void InitScore()
{
    set_bkg_data(0, 160, scoreSpr);
    Score_Setup(&scoreL, TRUE);
    Score_Setup(&scoreR, FALSE);
}

void ResetRound(UINT8 isInit)
{
    set_sprite_data(0, 12, batSpr);
    set_sprite_data(12, 12, batSpr);
    set_sprite_data(24, 1, ballSpr);

    Bat_Setup(&batL, 0, 0, TRUE);
    Bat_Setup(&batR, 12, 12, FALSE);

    Ball_Setup(&ball, 24, 24, isInit);
}

void main(void)
{
    ShowTitleScreen();

    InitScore();

    ResetRound(TRUE);

    SHOW_SPRITES;

    SHOW_BKG;
    waitpad(J_START | J_SELECT);
    waitpadup();
    HIDE_BKG;

    initarand(DIV_REG);

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

        // if (controls & J_START)
        // {
        // }

        // if (controls & J_SELECT)
        // {
        // }

        Bat_Move(&batL);
        Bat_Move(&batR);
        Ball_Move(&ball);        
        Ball_CheckCollision(&ball, &batL);
        Ball_CheckCollision(&ball, &batR);

        if (Ball_CheckGoal(&ball))
        {
            if (ball.dirX == 0)
                Score_Add(&scoreR);
            else if (ball.dirX == 1)
                Score_Add(&scoreL);

            Score_Draw(&scoreL);
            Score_Draw(&scoreR);

            ResetRound(FALSE);

            SHOW_BKG;
            Global_Wait(120);
            HIDE_BKG;

            if (scoreL.score == 3 || scoreR.score == 3)
            {
                Score_Reset(&scoreL);
                Score_Reset(&scoreR);
                Score_Draw(&scoreL);
                Score_Draw(&scoreR);

                Global_Wait(30);
                SHOW_BKG;
                waitpad(J_START | J_SELECT);
                waitpadup();
                HIDE_BKG;
            }
        }

        wait_vbl_done();
    }
}
