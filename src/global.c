#include "global.h"

const UINT8 sprOffsetX = 8;
const UINT8 sprOffsetY = 16;

void Global_ClearBKG()
{
    for (UINT8 x = 0; x < 20; x++)
        for (UINT8 y = 0; y < 18; y++)
            set_bkg_tile_xy(x, y, 0xFF);
}