#ifndef POKEDIAMOND_UNK_0202ABBC_H
#define POKEDIAMOND_UNK_0202ABBC_H

struct Unk0202ABBC
{
    /* 0x000 */ u32 filler[59]; 
    /* 0x0ec */ u16 unk_EC;
    /* 0x0ee */ u16 unk_EE;
    /* 0x0f0 */ u32 unk_F0;
}; // size: 0xF4

void *sub_0202ABBC(struct SaveData* save);
u32 sub_0202ABC8();
void sub_0202ABCC(struct Unk0202ABBC* unk);
u16 sub_0202ABDC(struct Unk0202ABBC* unk);
void sub_0202ABE4(struct Unk0202ABBC* unk, u16 data);
void sub_0202ABEC(void *srcp, void *destp);
void sub_0202ABF8(void *destp, void *srcp);
u32 sub_0202AC08(struct Unk0202ABBC* unk);
void sub_0202AC10(struct Unk0202ABBC* unk, u32 data);
u16 sub_0202AC18(struct Unk0202ABBC* unk);

#endif //POKEDIAMOND_UNK_0202ABBC_H
