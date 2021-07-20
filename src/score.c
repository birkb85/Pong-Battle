#include "score.h"

void Score_Setup(struct Score *score, UINT8 isScoreL)
{
    if (isScoreL)
        score->x = 3;
    else
        score->x = 12;
    score->score = 0;

    Score_Draw(score);
}

void Score_Add(struct Score *score)
{
    score->score++;
}

void Score_Reset(struct Score *score)
{
    score->score = 0;
}

void Score_Draw(struct Score *score)
{
    switch (score->score)
    {
    case 0:
        set_bkg_tiles(score->x, 5, 5, 8, score0Map);
        break;

    case 1:
        set_bkg_tiles(score->x, 5, 5, 8, score1Map);
        break;

    case 2:
        set_bkg_tiles(score->x, 5, 5, 8, score2Map);
        break;

    case 3:
        set_bkg_tiles(score->x, 5, 5, 8, score3Map);
        break;
    
    default:
        break;
    }
}