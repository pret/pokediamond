#ifndef POKEDIAMOND_STRING16_H
#define POKEDIAMOND_STRING16_H

struct String
{
    u16 len;
    u16 pos;
    u32 magic;
    u16 unk8;
    u16 data[1];
};

struct String * FUN_020219F4(u32 count, u32 heap_id);
int FUN_02021CE0(struct String *, struct String *);
int FUN_0206AE00(int x);
void FUN_02021E8C(struct String *, u16 *, u32); // copy
void FUN_02021A4C(struct String *); // set empty

#endif //POKEDIAMOND_STRING16_H
