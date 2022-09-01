#include "stats.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int
    TIME_PLAYED,
    SCORE = 1,
    SHOT,
    MISSED,
    ROUND_ID,
    FRAME_COUNT;

long int time_started;

int getDigitCount(int number){
    int i = 0;
    number = abs(number);
    while(number > 0){
        number /= 10;
        i ++;
    }
    return i;
}

void Stats_init(){
    time_t t;
    time_started = time(&t);
    
    long _r = 0;  // 16-bit system support!
    while(_r      < 999999) _r  = rand() ^ (rand() << 16);
    while(_r / 10 > 99999 ) _r /= 10;
    _r |= 0b1110;
    ROUND_ID = _r;

}

void calcTimePast(){
    time_t t;
    TIME_PLAYED = (int) (time(&t) - time_started);
    // printf("TIME_PLAYED_UNFORMATED: %d", TIME_PLAYED);
}

char *format_string_time(int a, int b){
    char *buf = malloc(16);
    snprintf(buf, 16, "%02d:%02d", a, b); // ! this only works for formatTime()
    return buf;
} // from: https://codereview.stackexchange.com/questions/226505/format-and-return-a-string-from-a-function-in-c

char* formatTime(int time){
    int
        sec = (int) (time % 60),
        min = (int) (time / 60 % 60);

    return format_string_time(min, sec);
}
extern bool gameLost;
void Stats_update(){
    if(gameLost) return;
    SCORE ++;

    calcTimePast();
}

extern bool debug;
void Stats_draw(){
    if(gameLost || !debug) return;
    system("cls");
    printf(
        "Time played: %s\nScore: %d\nShot: %d\nMissed: %d\nFrameCount: %d\nRoundID: %d\n\n", 
        formatTime(TIME_PLAYED), SCORE, SHOT, MISSED, FRAME_COUNT, ROUND_ID
    );

}