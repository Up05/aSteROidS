#pragma once

extern int
    TIME_PLAYED,
    SCORE,
    SHOT,
    MISSED,
    ROUND_ID,
    FRAME_COUNT;

void Stats_init();
void Stats_update();
void Stats_draw();
