//=============================================================================
/**
 * @file	ug_trap.h
 * @brief	地下の罠情報を保存するクラス
             １６×１６しか存在しないので、その分だけ確保してあります
 * @author	Katsumi Ohno
 * @date    2005.09.28
 */
//=============================================================================

#ifndef __UG_TRAP_H__
#define __UG_TRAP_H__


#include "gflib/bg_system.h"
#include "savedata/undergrounddata.h"

#define TRAP_NUM_SINGLE_MAX (UG_TRAP_PLACE_NUM_MAX)      ///< 一人の場合のトラップ最大数

#include "field/ug_itemtype.h"

extern void CommTrapInfoInitialize(void* pWork, FIELDSYS_WORK* pFSys);
extern void CommTrapInfoReset(void);
extern void CommTrapInfoReboot(void);
extern void CommTrapInfoFinalize(void);
extern void CommTrapInfoReInit(FIELDSYS_WORK* pFSys);
extern void CommTrapDeletePlayer_Server(int netID);

extern int CommTrapInfoGetWorkSize(void);
extern int CommTrapInfoGetTrapDataSize(void);
extern void CommTrapInfoAddTrap(u8 trapType);
extern void CommTrapInfoRemoveTrap(int netID, int trapIndex);
extern int CommTrapInfoGetTrapPosSize(void);
extern void CommTrapInfoProcess(void);
extern void CommTrapInfoChildSendStart(void);
extern void CommTrapInfoRecvTrapDefuse(int netID, int size, void* pData, void* pWork);
extern void CommTrapInfoRecvTrapData(int netID, int size, void* pData, void* pWork);
extern int CommTrapInfoGetTrapDataResultSize(void);
extern void CommTrapInfoRecvTrapDataResult(int netID, int size, void* pData, void* pWork);
extern void CommTrapInfoRecvTrapDataDel(int netID, int size, void* pData, void* pWork);
extern int CommTrapInfoGetTrapDataDelSize(void);
extern void CommTrapInfoRecvArrayStart(int netID, int size, void* pData, void* pWork);
extern void CommTrapInfoRecvArrayData(int netID, int size, void* pData, void* pWork);
extern void CommTrapInfoRecvServerPosData(int netID, int size, void* pData, void* pWork);
extern void CommTrapInfoRecvArrayEnd(int netID, int size, void* pData, void* pWork);

extern void CommTrapInfoRecvResult(int netID, int size, void* pData, void* pWork);
extern int CommTrapInfoGetResultSize(void);
extern BOOL CommTrapInfoIsParentRecv(void);
extern void CommTrapInfoResetParentRecv(void);
extern int CommTrapInfoGetTouchSize(void);
extern void CommTrapInfoRecvTouch(int netID, int size, void* pData, void* pWork);
extern void CommTrapInfoRecvTouchResult(int netID, int size, void* pData, void* pWork);

extern void UgTrapGoodsBind(int netID,int assailantNetID,int trapType,int xpos,int zpos,int dir);

extern BOOL CommTrapIsGoodsTrap(int netID);
extern void UgTrapForceExit(int victimNetID, BOOL bMove);
extern BOOL CommTrapCheck(int x,int z);
extern int CommTrapGetStartSize(void);
extern BOOL CommTrapCheckAndSendMessage(int netID);
extern void CommTrapRecvStart(int netID, int size, void* pData, void* pWork);
extern void CommTrapRecvSecondStart(int netID, int size, void* pData, void* pWork);
extern void CommTrapRecvSecondStartRet(int netID, int size, void* pData, void* pWork);


extern BOOL CommTrapGetActionMessage(STRBUF* pStrBuf);
extern BOOL CommTrapSetActionMessage(STRBUF* pStrBuf);

extern BOOL CommTrapFrontTrapDefuse(int netID, Grid* pTouch, u8 bTrapFull);
extern void CommTrapTouch(int netID, Grid* pTouch);
extern int CommTrapInfoRecvTrapDefuseSize(void);

extern void CommTrapDirBreak(int netID);  // 障害物で中断した
extern void CommTrapRecvDirBreak(int netID, int size, void* pData, void* pWork);

/// タッチパネルをタッチしている場合のすす払い消し処理
extern void CommTrapSmogTouch(Grid* pGrid, GF_BGL_INI * bgl);

extern void CommTrapSendRelease(int netID, int targetID);
extern void CommTrapSendTrapingArray(void);
extern void CommTrapRecvTrapingArray(int netID, int size, void* pData, void* pWork);
extern int CommTrapGetEndResultSize(void);
extern void CommTrapRecvEnd(int netID, int size, void* pData, void* pWork);
extern void CommTrapRecvForceEnd(int netID, int size, void* pData, void* pWork);
extern void CommTrapRecvEndResult(int netID, int size, void* pData, void* pWork);
extern void CommTrapRecvRelease(int netID, int size, void* pData, void* pWork);
extern int CommTrapGetReleaseSize(void);

/// 自分の罠の場所を得る
extern int CommTrapGetMyTrapX(int index);
extern int CommTrapGetMyTrapZ(int index);
extern int UgTrapGetNatureTrapX(int index);
extern int UgTrapGetNatureTrapZ(int index);

extern void UgTrapRecvNatureRadarStart(void);
extern void UgTrapRecvNatureRadarEnd(void);
extern int UgTrapAddNatureTrap(int gx,int gy,MATHRandContext16* pRand, int index);
extern void UgTrapNatureReload(void);

extern void UgTrapRecvNatureRadar(int netID, int size, void* pData, void* pWork);
extern void UgTrapRecvNatureRadarPos(int netID, int size, void* pData, void* pWork);
extern int UgTrapGetNatureTrapRadarSize(void);


// 罠実行関数
extern void UgTrapProcess(GF_BGL_INI* bgl);
extern void CommTrapRecvPriEnd(int netID, int size, void* pData, void* pWork);
extern void UgTrapTurnDispEnd(int netID);

extern void UgTouchRadarStart(FIELDSYS_WORK* pFSys,int xpos,int zpos,int scrxpos,int scrzpos,
                              u8* touchBuff1,int size1,u8* touchBuff2,int size2,u8* touchBuff3,int size3);


#endif // __UG_TRAP_H__

