#include "global.h"
#include "script.h"
#include "main.h"
#include "unk_0204639C.h"
#include "heap.h"
#include "event_data.h"

/*  Note to future reader, there might be some errors
    in the return type / parameters. They are right for this code
    but they might not be for every code, please do not blindly
    trust these prototypes if you are decompiling these functions. */
extern THUMB_FUNC u32   MOD06_02244DB0(u32);
extern THUMB_FUNC void  MOD06_02244DBC(void*);
extern THUMB_FUNC void  MOD06_02244DC4(void*, void*);
extern THUMB_FUNC void  MOD06_02244EF8(void*);
extern THUMB_FUNC void  MOD06_02244F18(void*);
extern THUMB_FUNC BOOL  MOD06_02244F24(void*);
extern THUMB_FUNC void  MOD06_02244F2C(void*);
extern THUMB_FUNC void* MOD06_02245088(struct UnkSavStruct80 * savStruct);
extern THUMB_FUNC u32   MOD06_02245114(u32, struct UnkSavStruct80*);
extern THUMB_FUNC void  MOD06_02245190(u32);
extern THUMB_FUNC void  MOD06_02245198(u8, u32);
extern THUMB_FUNC u32   MOD06_022451F0(u32);

extern THUMB_FUNC void  FUN_020054C8(u32);
extern THUMB_FUNC void  FUN_02049160(struct UnkStruct_0204639C*, u32);
extern THUMB_FUNC void  FUN_0204AF84(struct UnkStruct_0204639C*);
extern THUMB_FUNC void  FUN_0204AF3C(struct UnkStruct_0204639C *);
extern THUMB_FUNC void  FUN_0204AFC8(struct UnkStruct_0204639C *);
extern THUMB_FUNC void  FUN_0204B00C(struct UnkStruct_0204639C *);
extern THUMB_FUNC void  FUN_0204C1B4(struct UnkStruct_0204639C*, u32,u32,u32,u32,u32,u32,u32);
extern THUMB_FUNC u32   FUN_020553A0(u32);
extern THUMB_FUNC void  FUN_0205889C(u32, u32);
extern THUMB_FUNC void  FUN_0205F1C4(struct ScriptState *);
extern THUMB_FUNC void  FUN_0205F1D4(struct ScriptState *);
extern THUMB_FUNC void  FUN_0206367C(struct UnkSavStruct80 *, u32);


struct UnkStruct_0206015C
{
    u32   unk0;
    u32   unk4;
    u32   unk8;
    u8    unkC;
    u8    unkD;
};

struct UnkStruct_0204652C
{
    void* unk0;
    u32   unk4;
    u32   unk8;
    u8    action;
    u8    unkD; // some kind of counter?
    u8    unkE; // some kind of counter?
};

THUMB_FUNC void FUN_0206015C(struct UnkSavStruct80* savStruct);
THUMB_FUNC BOOL FUN_02060194(struct UnkStruct_0204639C * unkStruct0);

