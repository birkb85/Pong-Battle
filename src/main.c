#include <gb/gb.h>
#include "../res/bat_spr.h"
#include "../res/ball_spr.h"
#include "bat.h"
#include "ball.h"

struct Bat batL;
struct Bat batR;

struct Ball ball;

UINT8 controls;

void main(void)
{
    set_sprite_data(0, 24, batSpr);
    set_sprite_data(24, 1, ballSpr);

    Bat_Setup(&batL, 8, 24, 0, 0);
    Bat_Setup(&batR, 144, 24, 12, 12);

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

        Ball_Move(&ball);
        Ball_CheckCollision(&ball, &batL, TRUE);
        Ball_CheckCollision(&ball, &batR, FALSE);

        wait_vbl_done();
    }
}
