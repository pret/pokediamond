#ifndef POKEDIAMOND_STRING16_H
#define POKEDIAMOND_STRING16_H

struct String
{
    u16 maxsize;
    u16 size;
    u32 magic;
    u16 data[1];
    u8 padding[2];
};

struct String * String_ctor(u32 count, u32 heap_id);
int FUN_02021CE0(struct String *, struct String *);
int FUN_0206AE00(int x);
void FUN_02021E8C(struct String *, u16 *, u32); // copy
void StringSetEmpty(struct String *); // set empty
struct String * StringDup(struct String *, u32 heap_id);

#endif //POKEDIAMOND_STRING16_H
