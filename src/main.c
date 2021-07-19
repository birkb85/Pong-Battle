#include <gb/gb.h>
#include <stdio.h>
#include <string.h>
#include <rand.h>
#include "../res/bat_spr.h"
#include "../res/ball_spr.h"
#include "../res/splash_data.c"
#include "../res/splash_map.c"
#include "../res/score_spr.h"
#include "../res/score0_map.h"
#include "../res/score1_map.h"
#include "../res/score2_map.h"
#include "../res/score3_map.h"
#include "bat.h"
#include "ball.h"

struct Bat batL;
struct Bat batR;

struct Ball ball;

UINT8 controls;

UINT8 scoreVisible;
UINT8 score;

void ShowTitleScreen()
{
    set_bkg_data(0, 244, splash_data);
    set_bkg_tiles(0, 0, 20, 18, splash_map);
    SHOW_BKG;
    DISPLAY_ON;
    waitpad(0xFF);
    waitpadup();
    HIDE_BKG;
    for (UINT8 x = 0; x < 20; x++)
        for (UINT8 y = 0; y < 18; y++)
            set_bkg_tile_xy(x, y, 0xFF);
}

void InitScore()
{
    scoreVisible = 0;
    score = 0;
    set_bkg_data(0, 160, scoreSpr);
}

void ResetGame(UINT8 isInit)
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

    ResetGame(TRUE);

    SHOW_SPRITES;    

    waitpad(0xFF);
    waitpadup();

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
            ResetGame(FALSE);
        }

        scoreVisible--;
        if (scoreVisible == 255)
        {
            switch (score)
            {
            case 0:
                set_bkg_tiles(3, 5, 5, 8, score0Map);
                break;

            case 1:
                set_bkg_tiles(3, 5, 5, 8, score1Map);
                break;

            case 2:
                set_bkg_tiles(3, 5, 5, 8, score2Map);
                break;

            case 3:
                set_bkg_tiles(3, 5, 5, 8, score3Map);
                break;
            
            default:
                break;
            }
            SHOW_BKG;

            score++;
            if (score > 3)
                score = 0;
        }
        else if (scoreVisible == 31)
            HIDE_BKG;

        wait_vbl_done();
    }
}
