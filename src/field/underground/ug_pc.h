//=============================================================================
/**
 * @file	ug_pc.h
 * @brief	地下パソコンを管理するクラス
 * @author	k.ohno
 * @date    2006.02.02
 */
//=============================================================================

#ifndef _UG_PC_H_
#define _UG_PC_H_

extern void CommUnderPCInitialize(void);
extern void CommUnderPCFinalize(void);

extern int CommUnderPCCheck(Grid* pPos,int dir);
extern int UgPCGetPosX(int roomNo);
extern int UgPCGetPosZ(int roomNo);

extern BOOL CommUnderPCCheckAndMessage(int netID, Grid* pTouch);

extern void CommUnderPCRecvAccess(int netID, int size, void* pData, void* pWork);
extern int CommUnderPCGetAccessSize(void);

extern void UgPcRecvFlagGet(int netID, int size, void* pData, void* pWork);
extern void UgPcRecvFlagGetRet(int netID, int size, void* pData, void* pWork);

#ifdef PM_DEBUG
extern void Debug_UgFlagGet(void);
#endif

#endif // _UG_PC_H_






