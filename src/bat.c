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

    for (UINT8 i = 0; i < sizeof(bat->collision); i++)
    {
        bat->collision[i] = 0xFF;
    }

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