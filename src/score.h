#ifndef SCORE_H
#define SCORE_H

#include <gb/gb.h>
#include "../res/score0_map.h"
#include "../res/score1_map.h"
#include "../res/score2_map.h"
#include "../res/score3_map.h"

struct Score
{
    UINT8 x;
    UINT8 score;
};

extern void Score_Setup(struct Score *score, UINT8 isScoreL);
extern void Score_Add(struct Score *score);
extern void Score_Reset(struct Score *score);
extern void Score_Draw(struct Score *score);

#endif