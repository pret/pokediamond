#ifndef __SP_FISHING_ENC_H__
#define __SP_FISHING_ENC_H__

#include "field_common.h"

extern BOOL SpFishing_CheckPoint(	FIELDSYS_WORK *fsys);
extern void SpFishing_GetMaxMinLv(u8 *outMaxLv, u8 *outMinLv);
extern void SpFishing_GetMonsNo(int *outMonsNo);

#ifdef PM_DEBUG

extern void DEBUGSpFishing_GetPoint(FIELDSYS_WORK *fsys, int *outPos, u32 *outRand);

#endif //PM_DEBUG

#endif	//__SP_FISHING_ENC_H__

