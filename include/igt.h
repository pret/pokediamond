#ifndef POKEDIAMOND_IGT_H
#define POKEDIAMOND_IGT_H

struct IGT
{
    u16 hours;
    u8 minutes;
    u8 seconds;
};

void InitIGT(struct IGT * igt);
void AddIGTSeconds(struct IGT * igt, u32 seconds);
u16 GetIGTHours(struct IGT * igt);
u8 GetIGTMinutes(struct IGT * igt);

#endif //POKEDIAMOND_IGT_H
