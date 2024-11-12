#include "unk_020337E8.h"

#include "global.h"

#include "heap.h"

extern struct DWC_Struct *sub_020286EC(struct SaveData *save);
extern struct DWC_Struct *sub_02028228(struct DWC_Struct *);

// DWC_init
extern s32 DWC_Init(s32);

// DWC_account
extern void DWC_CreateExchangeToken(struct DWC_Struct *, struct DWC_token *);
extern void DWC_CreateUserData(struct DWC_Struct *, s32);
extern void DWC_ClearDirtyFlag(struct DWC_Struct *);
extern BOOL DWC_CheckHasProfile(struct DWC_Struct *);
extern BOOL DWC_CheckValidConsole(struct DWC_Struct *);
extern BOOL DWC_CheckUserData(struct DWC_Struct *);
extern s32 DWC_GetGsProfileId(struct DWC_Struct *, struct DWC_token *);

s32 sub_020337E8(HeapID heapId) {
    s32 ret = (s32)AllocFromHeap(heapId, 0x720);
    s32 ret1 = DWC_Init((ret + 0x1F) & ~0x1F);
    FreeToHeap((void *)ret);
    return ret1;
}

void sub_0203380C(struct DWC_Struct *dwc) {
    struct DWC_Struct *dwc1 = sub_02028228(dwc);
    if (!DWC_CheckUserData(dwc1)) {
        DWC_CreateUserData(dwc1, 0x4144414A);
        DWC_ClearDirtyFlag(dwc1);
    }
}

s32 sub_02033830(struct DWC_Struct *dwc) {
    struct DWC_token token;

    struct DWC_Struct *dwc1 = sub_02028228(dwc);
    DWC_CreateExchangeToken(dwc1, &token);
    return DWC_GetGsProfileId(dwc1, &token);
}

BOOL sub_0203384C(struct SaveData *save) {
    struct DWC_Struct *dwc = sub_02028228(sub_020286EC(save));
    return DWC_CheckHasProfile(dwc) && DWC_CheckValidConsole(dwc);
}
