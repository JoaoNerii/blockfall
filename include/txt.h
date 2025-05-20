#ifndef __TXT_H__
#define __TXT_H__

#include <stdio.h>

#define MAX_NAME_LENGTH 50
#define MAX_SCORES 10

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
} PlayerScore;

void saveScore(const char* playerName, int score);
void loadScores(PlayerScore scores[], int* count);
void displayRanking();
void initRankingSystem();

#endif /* __TXT_H__ */