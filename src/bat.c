#include "bat.h"

UINT8 bat_i;
const UINT8 bat_forceMax = 6;

void Bat_Setup(struct Bat *bat, UINT8 sprStartIndex, UINT8 tileStartIndex, UINT8 isBatL)
{
    bat->w = 4;
    bat->h = sizeof(bat->sprIds) << 3;
    if (isBatL)
        bat->x = 8;
    else
        bat->x = 144 + (8 - bat->w);
    bat->y = 24;
    bat->dirY = 0;
    bat->forceY = 0;
    bat->isBatL = isBatL;
    
    for (bat_i = 0; bat_i < sizeof(bat->sprIds); bat_i++)
    {
        set_sprite_tile(sprStartIndex + bat_i, tileStartIndex + bat_i);
        bat->sprIds[bat_i] = sprStartIndex + bat_i;
        bat->tileIds[bat_i] = tileStartIndex + bat_i;

        if (!isBatL)
            set_sprite_prop(sprStartIndex + bat_i, S_FLIPX);
    }

    memset(&bat->collision[0], 0xFF, sizeof(bat->collision));

    Bat_Draw(bat);
}

UINT8 Bat_GetVY(struct Bat *bat)
{
    return bat->forceY >> 1;
}

void Bat_Move(struct Bat *bat)
{
    if (bat->dirY == 0)
        bat->y -= Bat_GetVY(bat);
    else if (bat->dirY == 1)
        bat->y += Bat_GetVY(bat);

    Bat_Draw(bat);
}

void Bat_Draw(struct Bat *bat)
{
    for (bat_i = 0; bat_i < sizeof(bat->sprIds); bat_i++)
    {
        if (bat->isBatL)
            move_sprite(bat->sprIds[bat_i], bat->x + sprOffsetX, bat->y + sprOffsetY + (bat_i << 3));
        else
            move_sprite(bat->sprIds[bat_i], (bat->x + sprOffsetX) - (8 - bat->w), bat->y + sprOffsetY + (bat_i << 3));
    }
}

void Bat_Up(struct Bat *bat)
{
    if (bat->forceY == 0)
        bat->dirY = 0;

    if (bat->dirY == 0)
    {
        if (bat->forceY < bat_forceMax)
            bat->forceY++;
    }
    else if (bat->dirY == 1)
        bat->forceY --;    
}

void Bat_Down(struct Bat *bat)
{
    if (bat->forceY == 0)
        bat->dirY = 1;

    if (bat->dirY == 1)
    {
        if (bat->forceY < bat_forceMax)
            bat->forceY++;
    }
    else if (bat->dirY == 0)
        bat->forceY --;   
}

void Bat_Stop(struct Bat *bat)
{
    if (bat->forceY > 0)
        bat->forceY --;
}

UINT8 bat_sprTemp[16];
UINT8 bat_sprNb;
UINT8 bat_sprNbHit;
INT8 bat_yBot;

void Bat_Hit(struct Bat *bat, INT8 yTop)
{
    bat_yBot = yTop + 8;

    if (yTop >= 0 && yTop < (INT8)bat->h)
    {
        bat_sprNb = yTop >> 3;
        bat_sprNbHit = yTop - (bat_sprNb << 3);

        bat->collision[bat_sprNb] &= 0xFF << (8 - bat_sprNbHit);
        for (bat_i = 0; bat_i < 8; bat_i++)
            if ((bat->collision[bat_sprNb] >> bat_i) & 0x01)
                memcpy(&bat_sprTemp[(7 - bat_i) << 1], &batSpr[(bat_sprNb << 4) + ((7 - bat_i) << 1)], 2);
            else
                memset(&bat_sprTemp[(7 - bat_i) << 1], 0x00, 2);
        set_sprite_data(bat->tileIds[0] + bat_sprNb, 1, bat_sprTemp);
    }

    if (bat_yBot >= 0 && bat_yBot < (INT8)bat->h)
    {
        bat_sprNb = bat_yBot >> 3;
        bat_sprNbHit = bat_yBot - (bat_sprNb << 3);

        if (bat_sprNbHit > 0)
        {
            bat->collision[bat_sprNb] &= 0xFF >> bat_sprNbHit;
            for (bat_i = 0; bat_i < 8; bat_i++)
                if ((bat->collision[bat_sprNb] >> bat_i) & 0x01)
                    memcpy(&bat_sprTemp[(7 - bat_i) << 1], &batSpr[(bat_sprNb << 4) + ((7 - bat_i) << 1)], 2);
                else
                    memset(&bat_sprTemp[(7 - bat_i) << 1], 0x00, 2);
            set_sprite_data(bat->tileIds[0] + bat_sprNb, 1, bat_sprTemp);
        }
    }
}

UINT8 bat_isHit;

UINT8 Bat_CheckCollision(struct Bat *bat, INT8 yTop)
{
    bat_isHit = FALSE;
    bat_yBot = yTop + 8;

    if (yTop >= 0 && yTop < (INT8)bat->h)
    {
        bat_sprNb = yTop >> 3;
        bat_sprNbHit = yTop - (bat_sprNb << 3);

        for (bat_i = 0; bat_i < (8 - bat_sprNbHit); bat_i++)
            if ((bat->collision[bat_sprNb] >> bat_i) & 0x01)
                bat_isHit = TRUE;
    }

    if (bat_yBot >= 0 && bat_yBot < (INT8)bat->h)
    {
        bat_sprNb = bat_yBot >> 3;
        bat_sprNbHit = bat_yBot - (bat_sprNb << 3);

        if (bat_sprNbHit > 0)
        {
            for (bat_i = (8 - bat_sprNbHit); bat_i < 8; bat_i++)
                if ((bat->collision[bat_sprNb] >> bat_i) & 0x01)
                    bat_isHit = TRUE;
        }
    }

    return bat_isHit; 
}