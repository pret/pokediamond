//=============================================================================
/**
 * @file	comm_dig_stone.h
 * @brief	êŒÇå@ÇÈÉNÉâÉX
 * @author	Katsumi Ohno
 * @date    2005.10.26
 */
//=============================================================================

#ifndef __UG_DIG_STONE_H__
#define __UG_DIG_STONE_H__

extern void CommDigStoneInitialize(void* pWork, FIELDSYS_WORK* pFSys);
extern int CommDigStoneManagerGetWorkSize(void);
extern void CommDigStoneManagerReset(void);
extern void CommDigStoneManagerReboot(void);
extern void CommDigStoneFinalize(void);
extern void CommDigStoneStep(void);
extern BOOL CommDigStoneRecvTouch(int netID, Grid* pTouch);
extern void CommDigRecvStoneTouch(int netID, int size, void* pData, void* pWork);
extern BOOL CommDigStoneCheck(int netID, Grid* pTouch);
extern int CommDigStoneRecvPickUpSize(void);
extern void CommDigStoneRecvPickUp(int netID, int size, void* pData, void* pWork);
extern int UgDigStoneSetOneFossil(MATHRandContext16* pRand);

extern void UgStonePcRadarStart(void);
extern void UgStonePcRadarEnd(void);
extern int UgStoneGetRadarStoneX(int index);
extern int UgStoneGetRadarStoneZ(int index);


#include "field/ug_itemtype.h"


typedef struct{
  u16 iterater;
  u16 maxDist;
} NearHexWork;

typedef struct{
  s16 xpos;
  s16 zpos;
} NearHex;


extern void NearHexInitialize(NearHexWork* pWork, int maxDist);
extern BOOL NearHexGetHex(NearHexWork* pWork, NearHex* pHex);


extern void CommDigRecvStoneData(int netID, int size, void* pData, void* pWork);
extern int CommDigGetStoneDataSize(void);

extern BOOL CommDigGetActionMessage(STRBUF* pStrBuf);

extern void CommStoneChildSendStart(void);

extern void CommStoneRecvArrayStart(int netID, int size, void* pData, void* pWork);
extern void CommStoneRecvArrayData(int netID, int size, void* pData, void* pWork);
extern void CommStoneRecvArrayEnd(int netID, int size, void* pData, void* pWork);
extern void CommStoneRecvResult(int netID, int size, void* pData, void* pWork);
extern int CommStoneGetResultSize(void);
extern BOOL CommStoneIsParentRecv(void);
extern void CommStoneResetParentRecv(void);
extern int CommStoneGetDataSize(void);
extern void CommDigStoneAddStone( int type, int carat ,int x,int z);
extern int CommDigStoneDataResultSize(void);
extern BOOL CommDigIsStone(int type);
extern BOOL UgStoneCheck(int x, int z);

extern int UgStoneGetMyStoneX(int index);
extern int UgStoneGetMyStoneZ(int index);
extern BOOL UgDigStoneGetActionMessage(STRBUF* pStrBuf);

extern void Debug_UgDigStoneAdd( int type, int carat ,int x,int z);

#endif //__UG_DIG_STONE_H__


