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

void FUN_02031734(struct SaveData *save, u8 param1);
void FUN_020317C0();
BOOL FUN_02031810();
void FUN_02031824(struct SaveData *save);
void FUN_02031860();
void FUN_02031880();
void FUN_020318A4(u8 param0);
void FUN_020318B4();
BOOL FUN_020318C4();
void FUN_02031914();
void FUN_02031924();
void FUN_02031934();
void FUN_02031948(struct SaveData *save, u8 param1, u8 param2, u32 param3);
void FUN_02031990(struct SaveData *save, u8 param1, u8 param2, u32 param3);
void FUN_020319D8(u8 param0);
void FUN_020319F4();
void FUN_02031A08();
void FUN_02031A24();
BOOL FUN_02031A2C();
void FUN_02031A7C(struct SaveData *save);
void FUN_02031AC8(u8 param0);
s32 FUN_02031AF4();
BOOL FUN_02031B2C();
void FUN_02031B50();
u32 FUN_02031BD0();
void FUN_02031BF4();
void FUN_02031C10();
void FUN_02031C2C();
void FUN_02031C54();
void FUN_02031C64();
void FUN_02031C74(struct SaveData *save, u8 param1);
void FUN_02031CA8(struct SaveData *save, u8 param1);
void FUN_02031CDC();
void FUN_02031D20(void (*param0)(), u32 param1);
void FUN_02031D30();
void FUN_02031E08();
void FUN_02031E8C();
void FUN_02031EE0();
void FUN_02031F60();
void FUN_02031FC8();
void FUN_02032028();
void FUN_02032040();
void FUN_02032058();
void FUN_020320C4();
void FUN_02032118();
void FUN_02032138();
void FUN_0203213C();
void FUN_02032140();
void FUN_02032178();
void FUN_02032194();
void FUN_020321B8();
void FUN_020321D0();
void FUN_02032218();
void FUN_02032234();
void FUN_0203224C();
void FUN_02032290();
void FUN_02032298();
void FUN_020322C0();
void FUN_020322F8();
void FUN_0203230C();
void FUN_0203234C();
void FUN_02032364();
void FUN_02032378();
void FUN_020323B8();
void FUN_020323BC();
void FUN_020323CC();
void FUN_020323DC();
void FUN_02032424();
void FUN_02032440();
void FUN_02032478();
void FUN_020324C8();
void FUN_020324F8();
void FUN_02032510();
void FUN_02032578();
void FUN_020325D0();
void FUN_02032628();
void FUN_02032640();
void FUN_0203266C();
void FUN_020326D0();
void FUN_02032738();
void FUN_0203279C();
void FUN_020327B4();
void FUN_020327B8();
void FUN_020327FC();
void FUN_02032850();
void FUN_02032888();
void FUN_020328C0(u8 param0);
void FUN_020328E4();
void FUN_020328F4(u8 param0);
void FUN_02032924();
void FUN_0203293C();
void FUN_02032978();
void FUN_020329F4();
void FUN_02032A8C(u8 param0, u32 param1, u8 *param2);
void FUN_02032AEC(u32 param0, u32 param1, u8 *param2);
u32 FUN_02032B68();
void FUN_02032B6C(u8 param0);
void FUN_02032B84();
void FUN_02032B8C();
void FUN_02032BD0(struct SaveData *save);
void FUN_02032C0C();
u32 FUN_02032C28();
void FUN_02032C6C(u32 param0, u32 param1);
void FUN_02032CF4();
void FUN_02032D44(struct SaveData *save);
void FUN_02032D80();
u8 FUN_02032D9C();
BOOL FUN_02032DAC();
void FUN_02032E00();
void FUN_02032E48();
void FUN_02032E8C();
void FUN_02032E90();
void FUN_02032EA8();
void FUN_02032EAC();
void FUN_02032EB0();
void FUN_02032F20(u32 param0);
void FUN_02032F34();
void FUN_02032F98();
u32 FUN_02032FDC(u8 param0);
u32 FUN_0203300C();
void FUN_02033060();
void FUN_020330A0();
void FUN_020330E4();
u8 FUN_02033128();
u32 FUN_02033138();
u32 FUN_02033154();
u32 FUN_02033180();
void FUN_0203318C();
void FUN_020331C4();
void FUN_020331E8();
void FUN_02033208();
void FUN_0203323C();
u32 FUN_02033250();
void FUN_02033288(struct SaveData *save);
void FUN_020332DC();
void FUN_02033310(struct SaveData *save);
void FUN_02033364();
u32 FUN_02033398();
void FUN_020333F0();
void FUN_0203341C();
void *FUN_0203346C(struct SaveData *save, u32 param1);
void *FUN_020334DC();
void FUN_020334E8(u8 param0, u8 param1);
u8 FUN_02033510();
s32 FUN_02033534();
u8 FUN_0203354C();
void FUN_02033564(void *src);
void FUN_02033578(void *dst);
u32 FUN_02033590();
void FUN_020335A4(u8 param0);
u8 FUN_020335B8();
void FUN_020335D0(s32 param0);
void FUN_020335E0();
void FUN_020335F0();
void FUN_020335F4();
BOOL FUN_02033678();
u32 FUN_020336A0(u8 param0);

#endif // POKEDIAMOND_UNK_0202F150_H
