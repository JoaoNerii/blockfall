#include "txt.h"
#include "screen.h"
#include "keyboard.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const char* RANKING_FILE = "ranking.txt";

void initRankingSystem() {
    FILE* file = fopen(RANKING_FILE, "a");
    if (file) fclose(file);
}

void saveScore(const char* playerName, int score) {
    PlayerScore scores[MAX_SCORES + 1];
    int count = 0;
    
    FILE* file = fopen(RANKING_FILE, "r");
    if (file) {
        while (count < MAX_SCORES && 
               fscanf(file, "%49s %d", scores[count].name, &scores[count].score) == 2) {
            count++;
        }
        fclose(file);
    }
    
    strncpy(scores[count].name, playerName, MAX_NAME_LENGTH-1);
    scores[count].name[MAX_NAME_LENGTH-1] = '\0';
    scores[count].score = score;
    count++;
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (scores[i].score < scores[j].score) {
                PlayerScore temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }
    
    if (count > MAX_SCORES) {
        count = MAX_SCORES;
    }
    
    file = fopen(RANKING_FILE, "w");
    if (file) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%s %d\n", scores[i].name, scores[i].score);
        }
        fclose(file);
    }
}

void displayRanking() {
    PlayerScore scores[MAX_SCORES];
    int count = 0;
    
    FILE* file = fopen(RANKING_FILE, "r");
    if (file) {
        while (count < MAX_SCORES && 
               fscanf(file, "%49s %d", scores[count].name, &scores[count].score) == 2) {
            count++;
        }
        fclose(file);
    }
    
    screenSetColor(WHITE, BLACK);
    screenClear();
    screenGotoxy(10, 2);
    printf("=== TOP 10 MELHORES PONTUACOES ===");
    
    for (int i = 0; i < count; i++) {
        screenGotoxy(10, 4 + i);
        printf("%2d. %-20s %5d", i+1, scores[i].name, scores[i].score);
    }
    
    if (count == 0) {
        screenGotoxy(10, 4);
        printf("Nenhuma pontuacao registrada ainda!");
    }
    
    screenUpdate();
}