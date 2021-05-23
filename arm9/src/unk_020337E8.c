#include "unk_020337E8.h"
#include "heap.h"

extern struct DWC_Struct *FUN_020286EC(struct SaveBlock2 *sav2);
extern struct DWC_Struct *FUN_02028228(struct DWC_Struct *);

// DWC_init
extern int DWC_Init(int);

// DWC_account
extern void DWC_CreateExchangeToken(struct DWC_Struct *, struct DWC_token *);
extern void DWC_CreateUserData(struct DWC_Struct *, int);
extern void DWC_ClearDirtyFlag(struct DWC_Struct *);
extern BOOL DWC_CheckHasProfile(struct DWC_Struct *);
extern BOOL DWC_CheckValidConsole(struct DWC_Struct *);
extern BOOL DWC_CheckUserData(struct DWC_Struct *);
extern int DWC_GetGsProfileId(struct DWC_Struct *, struct DWC_token *);

THUMB_FUNC int FUN_020337E8(u32 heap_id)
{
    u32 ret = (u32)AllocFromHeap(heap_id, 0x720);
    int ret1 = DWC_Init((ret + 0x1F) & ~0x1F);
    FreeToHeap((void*)ret);
    return ret1;
}

THUMB_FUNC void FUN_0203380C(struct DWC_Struct *dwc)
{
    struct DWC_Struct * dwc1 = FUN_02028228(dwc);
    if(!DWC_CheckUserData(dwc1))
    {
        DWC_CreateUserData(dwc1, 0x4144414A);
        DWC_ClearDirtyFlag(dwc1);
    }
}

THUMB_FUNC int FUN_02033830(struct DWC_Struct *dwc)
{
    struct DWC_token token;

    struct DWC_Struct * dwc1 = FUN_02028228(dwc);
    DWC_CreateExchangeToken(dwc1, &token);
    return DWC_GetGsProfileId(dwc1, &token);
}

THUMB_FUNC BOOL FUN_0203384C(struct SaveBlock2 *sav2)
{
    struct DWC_Struct * dwc = FUN_02028228(FUN_020286EC(sav2));
    return (DWC_CheckHasProfile(dwc) && DWC_CheckValidConsole(dwc));
}
