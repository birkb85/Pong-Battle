#include "bat.h"

void Bat_Setup(struct Bat *bat, UINT8 x, UINT8 y, UINT8 sprStartIndex, UINT8 tileStartIndex, UINT8 isBatL)
{
    bat->x = x;
    bat->y = y;
    bat->w = 8;
    bat->h = sizeof(bat->sprIds) << 3;
    bat->isBatL = isBatL;
    
    for (UINT8 i = 0; i < sizeof(bat->sprIds); i++)
    {
        set_sprite_tile(sprStartIndex + i, tileStartIndex + i);
        bat->sprIds[i] = sprStartIndex + i;
        bat->tileIds[i] = tileStartIndex + i;

        if (!isBatL)
            set_sprite_prop(sprStartIndex + i, S_FLIPX);
    }

    memset(&bat->collision[0], 0xFF, sizeof(bat->collision));

    Bat_Move(bat);
}

void Bat_Move(struct Bat *bat)
{
    for (UINT8 i = 0; i < sizeof(bat->sprIds); i++)
    {
        move_sprite(bat->sprIds[i], bat->x + sprOffsetX, bat->y + sprOffsetY + (i << 3));
    }
}

void Bat_MoveUp(struct Bat *bat)
{
    bat->y -= 2;
    Bat_Move(bat);
}

void Bat_MoveDown(struct Bat *bat)
{
    bat->y += 2;
    Bat_Move(bat);
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
        for (UINT8 i = 0; i < 8; i++)
            if ((bat->collision[bat_sprNb] >> i) & 0x01)
                memcpy(&bat_sprTemp[(7 - i) << 1], &batSpr[(bat_sprNb << 4) + ((7 - i) << 1)], 2);
            else
                memset(&bat_sprTemp[(7 - i) << 1], 0x00, 2);
        set_sprite_data(bat->tileIds[0] + bat_sprNb, 1, bat_sprTemp);
    }

    if (bat_yBot >= 0 && bat_yBot < (INT8)bat->h)
    {
        bat_sprNb = bat_yBot >> 3;
        bat_sprNbHit = bat_yBot - (bat_sprNb << 3);

        if (bat_sprNbHit > 0)
        {
            bat->collision[bat_sprNb] &= 0xFF >> bat_sprNbHit;
            for (UINT8 i = 0; i < 8; i++)
                if ((bat->collision[bat_sprNb] >> i) & 0x01)
                    memcpy(&bat_sprTemp[(7 - i) << 1], &batSpr[(bat_sprNb << 4) + ((7 - i) << 1)], 2);
                else
                    memset(&bat_sprTemp[(7 - i) << 1], 0x00, 2);
            set_sprite_data(bat->tileIds[0] + bat_sprNb, 1, bat_sprTemp);
        }
    }
}