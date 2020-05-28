//=============================================================================
/**
 * @file	ug_record.h
 * @bfief	記録を管理するクラス
 * @author	k.ohno
 * @date	06/01/31
 */
//=============================================================================

#ifndef __UG_RECORD_H__
#define __UG_RECORD_H__

#include "savedata/undergrounddata.h"

//==============================================================================
//	enum
//==============================================================================


/*
typedef enum{
  UNDER_FLAG_POINT_DELIVERY = 30,     //ハタを基地にもちかえる	＋30
  UNDER_FLAG_POINT_DELIVERY_SECOND = 15, //（一度とった事のあるハタ）	＋15
  UNDER_FLAG_POINT_DIG_FOSSIL = 2, // 化石を発掘する	＋２
  UNDER_FLAG_POINT_SEND_GOODS = 5,  // 道具をあげる
  UNDER_FLAG_POINT_TALK = 1,       // 会話する
  UNDER_FLAG_POINT_QUESTION = 1,     // 会話の質問を行う
  UNDER_FLAG_POINT_RESQUE = 5,     // 助ける
  UNDER_FLAG_POINT_CREATE_BASE = 3,  // 基地を作る
  UNDER_FLAG_POINT_ENTER_UG = 1,   // 地下に入る
  UNDER_FLAG_POINT_WALK100 = 1,    // 地下を１００歩く

} UnderFlagPoint_e;
*/

typedef enum{
  UNDER_FLAG_DEL,             // 旗を捨てた
  UNDER_FLAG_TARGET_GET,      // 相手の基地のハタをとる	＋１０
  UNDER_FLAG_MYFLAG_LOSE,     // 自分の基地のハタをとられる	ー１０
  UNDER_FLAG_DELIVERY,        // ハタを基地にもちかえる	＋５０
  UNDER_FLAG_DELIVERY_SECOND, //（一度とった事のあるハタ）	＋２０
  UNDER_FLAG_RIP_OFF,    // 人のハタをうばう	＋１０
  UNDER_FLAG_RECAPTURE,  // 人のハタをとりかえす	＋１０
  UNDER_FLAG_STOLEN,     // もってたハタをとられる	ー１０
  UNDER_FLAG_TRICK,      // 相手を罠にはめる	＋３
  UNDER_FLAG_DECOY,      // 罠にはめられる	ー１
  UNDER_FLAG_DIG_FOSSIL, // 化石を発掘する	＋２
  UNDER_FLAG_NOTALK,    // 話しかけられない
  UNDER_FLAG_NODIG,    // 拾えない
} UnderFlagState_e;



//==============================================================================
//	typedef
//==============================================================================

typedef struct _UNDER_RECORD  UNDER_RECORD;




//==============================================================================
//	extern
//==============================================================================

extern void UnderRecordInitialize(UNDER_RECORD* pRecord, SB_RECORD_DATA* pMyRec, SAVEDATA* pSaveData);
extern int UnderRecordGetWorkSize(void);
extern void UnderRecordFinalize(void);
extern void UnderRecordReset(void);
extern void UnderRecordReboot(void);


typedef void(*UgRecordEndCallBack)(void* pWork);

// ステータス画面
extern void UgRecordStatusListStart(GF_BGL_INI* bgl, MYSTATUS* pMyStatus,
                                    UgRecordEndCallBack pFunc,void* pWork, BOOL bMyData);
extern void UgRecordUpdateMyData(void);

extern int UgRecordGetTargetDataSize(void);
extern void UgRecordSendMyData(int targetID);
extern void UgRecordRecvTargetData(int netID, int size, void* pData, void* pWork);
extern void UgRecordRecvTargetDataCall(int netID, int size, void* pData, void* pWork);
extern BOOL UgRecordIsTargetRecord(void);
extern void UgRecordResetTargetRecord(void);
extern void UgRecordGoodsMessage(SB_RECORD_DATA* pRec, int message);
// 旗を獲った履歴
extern void* UgRecordFlagListStart(GF_BGL_INI* bgl, MYSTATUS* pMyStatus,UNDERGROUNDDATA* pUGData,
                                  UgRecordEndCallBack pFunc,void* pWork);
extern void UgRecordFlagListEnd(void* work);


#endif //__UG_RECORD_H__


