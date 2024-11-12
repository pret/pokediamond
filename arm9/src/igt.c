#include "igt.h"

#include "global.h"

void InitIGT(struct IGT *igt) {
    igt->hours = 0;
    igt->minutes = 0;
    igt->seconds = 0;
}

void AddIGTSeconds(struct IGT *igt, u32 to_add) {
    u32 hours, minutes, seconds;
    if (igt->hours == 999 && igt->minutes == 59 && igt->seconds == 59) {
        return;
    }
    seconds = (u32)(igt->seconds + to_add);
    minutes = (u32)igt->minutes;
    hours = (u32)igt->hours;
    if (seconds > 59) {
        minutes += seconds / 60;
        seconds %= 60;
        if (minutes > 59) {
            hours += minutes / 60;
            minutes %= 60;
            if (hours >= 999) {
                hours = 999;
                minutes = 59;
                seconds = 59;
            }
        }
    }
    igt->hours = (u16)hours;
    igt->minutes = (u8)minutes;
    igt->seconds = (u8)seconds;
}

u16 GetIGTHours(struct IGT *igt) {
    return igt->hours;
}

u8 GetIGTMinutes(struct IGT *igt) {
    return igt->minutes;
}
