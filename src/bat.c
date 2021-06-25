#include "bat.h"

void Bat_Setup(struct Bat *bat, UINT8 x, UINT8 y, UINT8 sprStartIndex, UINT8 tileStartIndex, UINT8 isBatL)
{
    bat->x = x;
    bat->y = y;
    bat->w = 8;
    bat->h = sizeof(bat->sprIds) * 8;
    bat->isBatL = isBatL;
    
    for (UINT8 i = 0; i < sizeof(bat->sprIds); i++)
    {
        set_sprite_tile(sprStartIndex + i, tileStartIndex + i);
        bat->sprIds[i] = sprStartIndex + i;

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
        move_sprite(bat->sprIds[i], bat->x + sprOffsetX, bat->y + sprOffsetY + i * 8);
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
UINT8 bat_sprTop;
UINT8 bat_sprTopHit;

void Bat_Hit(struct Bat *bat, UINT8 yTop)
{
    if (yTop < bat->h)
    {
        bat_sprTop = yTop >> 3;
        bat_sprTopHit = yTop - (bat_sprTop << 3);

        bat->collision[bat_sprTop] &= 0xFF << (8 - bat_sprTopHit);
        for (UINT8 i = 0; i < 8; i++)
            if ((bat->collision[bat_sprTop] >> i) & 0x01)
                memcpy(&bat_sprTemp[(7 - i) << 1], &batSpr[(bat_sprTop << 4) + ((7 - i) << 1)], 2);
            else
                memset(&bat_sprTemp[(7 - i) << 1], 0x00, 2);
        set_sprite_data(bat_sprTop, 1, bat_sprTemp);

        if (bat_sprTopHit > 0 && bat_sprTop < (sizeof(bat->collision) - 1))
        {
            bat->collision[bat_sprTop + 1] &= 0xFF >> bat_sprTopHit;
            for (UINT8 i = 0; i < 8; i++)
                if ((bat->collision[bat_sprTop + 1] >> i) & 0x01)
                    memcpy(&bat_sprTemp[(7 - i) << 1], &batSpr[((bat_sprTop + 1) << 4) + ((7 - i) << 1)], 2);
                else
                    memset(&bat_sprTemp[(7 - i) << 1], 0x00, 2);
            set_sprite_data(bat_sprTop + 1, 1, bat_sprTemp);
        }
    }
}