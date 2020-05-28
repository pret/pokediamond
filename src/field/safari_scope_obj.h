//===========================================================================
/**
 * @file	safari_scope_obj.h
 * @brief	ƒTƒtƒ@ƒŠ–]‰“‹¾OBJ
 * @author	Nozomu Saito
 * @date	2006.04.24
 * 
 */
//===========================================================================
#ifndef __SAFARI_SCOPE_OBJ_H__
#define __SAFARI_SCOPE_OBJ_H__

typedef struct SAFARI_SCOPE_OBJ_tag * SSO_PTR;

extern SSO_PTR SSO_AllocMemory(const int inHeapID);
extern void SSO_FreeMemory(SSO_PTR ptr);
extern void SSO_SetupSafariScopeCLACT(SSO_PTR ptr, const int inMonsNo);
extern void SSO_DrawStartCellAct(SSO_PTR ptr);
extern void SSO_DrawEndCellAct(SSO_PTR ptr);
extern BOOL SSO_WaitDrawCellTask(SSO_PTR ptr);
extern void SSO_RereaseSSCellObject(SSO_PTR ptr);

#endif //__SAFARI_SCOPE_OBJ_H__
