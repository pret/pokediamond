#ifndef POKEDIAMOND_UNK_02031734_H
#define POKEDIAMOND_UNK_02031734_H

#include "global.h"
#include "player_data.h"

struct UnkStruct_02031734_const1
{
    u32 unk00[3];
};

struct UnkStruct_02031734_const2
{
    u32 unk00[2];
};

struct UnkStruct_02031734
{
    void *unk00;
    u8 unk04[6];
    s64 unk0C[3];
    void (*unk24)();
    struct SaveData *unk28;
    PlayerProfile *unk2C;
    u32 unk30;
    u32 unk34;
    u16 unk38;
    u16 unk3A;
    u8 unk3C;
    u8 unk3D;
    u8 unk3E;
    u8 unk3F;
    u8 unk40;
    u8 unk41;
    u8 unk42;
    u8 unk43;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48;
    u8 unk49;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
};

inline u32 compute(s64 *param0, u32 param1)
{
    param0[0] = param0[1] * param0[0] + param0[2];

    return (u32)(((s64)((u64)(param0[0]) >> 32) * param1) >> 32);
}

void sub_02031734(struct SaveData *save, u8 param1);
void sub_020317C0();
BOOL sub_02031810();
void sub_02031824(struct SaveData *save);
void sub_02031860();
void sub_02031880();
void sub_020318A4(u8 param0);
void sub_020318B4();
BOOL sub_020318C4();
void sub_02031914();
void sub_02031924();
void sub_02031934();
void sub_02031948(struct SaveData *save, u8 param1, u8 param2, u32 param3);
void sub_02031990(struct SaveData *save, u8 param1, u8 param2, u32 param3);
void sub_020319D8(u8 param0);
void sub_020319F4();
void sub_02031A08();
void sub_02031A24();
BOOL sub_02031A2C();
void sub_02031A7C(struct SaveData *save);
void sub_02031AC8(u8 param0);
s32 sub_02031AF4();
BOOL sub_02031B2C();
void sub_02031B50();
u32 sub_02031BD0();
void sub_02031BF4();
void sub_02031C10();
void sub_02031C2C();
void sub_02031C54();
void sub_02031C64();
void sub_02031C74(struct SaveData *save, u8 param1);
void sub_02031CA8(struct SaveData *save, u8 param1);
void sub_02031CDC();
void sub_02031D20(void (*param0)(), u32 param1);
void sub_02031D30();
void sub_02031E08();
void sub_02031E8C();
void sub_02031EE0();
void sub_02031F60();
void sub_02031FC8();
void sub_02032028();
void sub_02032040();
void sub_02032058();
void sub_020320C4();
void sub_02032118();
void sub_02032138();
void sub_0203213C();
void sub_02032140();
void sub_02032178();
void sub_02032194();
void sub_020321B8();
void sub_020321D0();
void sub_02032218();
void sub_02032234();
void sub_0203224C();
void sub_02032290();
void sub_02032298();
void sub_020322C0();
void sub_020322F8();
void sub_0203230C();
void sub_0203234C();
void sub_02032364();
void sub_02032378();
void sub_020323B8();
void sub_020323BC();
void sub_020323CC();
void sub_020323DC();
void sub_02032424();
void sub_02032440();
void sub_02032478();
void sub_020324C8();
void sub_020324F8();
void sub_02032510();
void sub_02032578();
void sub_020325D0();
void sub_02032628();
void sub_02032640();
void sub_0203266C();
void sub_020326D0();
void sub_02032738();
void sub_0203279C();
void sub_020327B4();
void sub_020327B8();
void sub_020327FC();
void sub_02032850();
void sub_02032888();
void sub_020328C0(u8 param0);
void sub_020328E4();
void sub_020328F4(u8 param0);
void sub_02032924();
void sub_0203293C();
void sub_02032978();
void sub_020329F4();
void sub_02032A8C(u8 param0, u32 param1, u8 *param2);
void sub_02032AEC(u32 param0, u32 param1, u8 *param2);
u32 sub_02032B68();
void sub_02032B6C(u8 param0);
void sub_02032B84();
void sub_02032B8C();
void sub_02032BD0(struct SaveData *save);
void sub_02032C0C();
u32 sub_02032C28();
void sub_02032C6C(u32 param0, u32 param1);
void sub_02032CF4();
void sub_02032D44(struct SaveData *save);
void sub_02032D80();
u8 sub_02032D9C();
BOOL sub_02032DAC();
void sub_02032E00();
void sub_02032E48();
void sub_02032E8C();
void sub_02032E90();
void sub_02032EA8();
void sub_02032EAC();
void sub_02032EB0();
void sub_02032F20(u32 param0);
void sub_02032F34();
void sub_02032F98();
u32 sub_02032FDC(u8 param0);
u32 sub_0203300C();
void sub_02033060();
void sub_020330A0();
void sub_020330E4();
u8 sub_02033128();
u32 sub_02033138();
u32 sub_02033154();
u32 sub_02033180();
void sub_0203318C();
void sub_020331C4();
void sub_020331E8();
void sub_02033208();
void sub_0203323C();
u32 sub_02033250();
void sub_02033288(struct SaveData *save);
void sub_020332DC();
void sub_02033310(struct SaveData *save);
void sub_02033364();
u32 sub_02033398();
void sub_020333F0();
void sub_0203341C();
void *sub_0203346C(struct SaveData *save, u32 param1);
void *sub_020334DC();
void sub_020334E8(u8 param0, u8 param1);
u8 sub_02033510();
s32 sub_02033534();
u8 sub_0203354C();
void sub_02033564(void *src);
void sub_02033578(void *dst);
u32 sub_02033590();
void sub_020335A4(u8 param0);
u8 sub_020335B8();
void sub_020335D0(s32 param0);
void sub_020335E0();
void sub_020335F0();
void sub_020335F4();
BOOL sub_02033678();
u32 sub_020336A0(u8 param0);

#endif // POKEDIAMOND_UNK_0202F150_H
