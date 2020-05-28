//=============================================================================
/**
 * @file	communication.h
 * @brief	通信関連で外部参照が必要な基本的なものを定義
 * @author	Katsumi Ohno
 * @date    2005.11.14
 */
//=============================================================================
#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include "comm_def.h"
#include "system/pms_data.h"


//ggid定義はwh.hに移動しました

// 自分だけデバッグプリントする仕組み  いったん全員に変更
#ifndef OHNO_PRINT
#if 1 //(defined(DEBUG_ONLY_FOR_ohno) | defined(DEBUG_ONLY_FOR_tomoya_takahashi) | defined(DEBUG_ONLY_FOR_mituhara))
//#ifdef  SDK_DEBUG

#if 1
#define OHNO_SP_PRINT(...) \
  (void) ((OS_Printf(__VA_ARGS__)))
#define OHNO_PRINT(...)           ((void) 0)

#else
#define OHNO_PRINT(...) \
  (void) ((OS_Printf(__VA_ARGS__)))
#define OHNO_SP_PRINT(...)           ((void) 0)
#endif

#else   //DEBUG_ONLY_FOR_ohno

#define OHNO_PRINT(...)           ((void) 0)
#define OHNO_SP_PRINT(...)           ((void) 0)

#endif  // DEBUG_ONLY_FOR_ohno
#endif  //OHNO_PRINT

#define MYSTERY_BEACON_DATA_SIZE   (84)

// WMBssDescのgameInfo.userGameInfoを使用している状況の構造体
// WM_SIZE_USER_GAMEINFO  最大 112byte
// 今後の会議で変更になる予定
// 仮でここに引越し
typedef struct{
  u32 		pokeID;     	// ID												8
  u8  		serviceNo;   	// 通信サービス番号									9
  u8  		regulationNo;  	// 戦闘レギュレーション＆コンテストタイプの識別		10
  u8  		connectNum;    	// つながっている台数  --> 本親かどうか識別			11
  u8 		soloDebugNo;  	// 他の人と通信しないようにするための番号			12
  PMS_DATA	pmsData;									// 簡易会話データ		20
  u8  		myStatusBuff[COMM_SEND_MYSTATUS_SIZE];  	// 実際のmystatusの大きさは実行時でないとわからないので上に切ってある
  u8  		regulationBuff[COMM_SEND_REGULATION_SIZE];  // 実際のregの大きさは実行時でないとわからないので上に切ってある
  // 戦闘の時以外は空いてるので、ユニオンルームの子機IDも入れる事にする
  u32		UnionRoomTime;								// ユニオンルームに入っている時間を書き換える
  u8        pause;   // 接続を禁止したい時に使用する
} _GF_BSS_DATA_INFO;

// 共用体に変えたかったがあまりにUNIONのソース変更が多いので、別構造体
typedef struct{
  u32 		pokeID;     	// ID												8
  u8  		serviceNo;   	// 通信サービス番号									9
  u8  		regulationNo;  	// 戦闘レギュレーション＆コンテストタイプの識別		10
  u8  		connectNum;    	// つながっている台数  --> 本親かどうか識別			11
  u8 		soloDebugNo;  	// 他の人と通信しないようにするための番号			12
  u8 mysteryData[MYSTERY_BEACON_DATA_SIZE];
} _GF_BSS_MYSTERY;


#include "communication/comm_command.h"
#include "communication/comm_info.h"
#include "communication/comm_mp.h"
#include "communication/comm_system.h"
#include "communication/comm_recv.h"
#include "communication/comm_message.h"
#include "communication/comm_tool.h"
#include "communication/wm_icon.h"
#include "communication/comm_state.h"

// 他の人と通信接続しないようにするための番号
#ifdef PM_DEBUG		//DebugROM
#if (defined(DEBUG_ONLY_FOR_ohno) | defined(DEBUG_ONLY_FOR_mituhara))
#define   SOLO_DEBUG_NO   (0)
#else
#define   SOLO_DEBUG_NO   (0)
#endif
#endif //PM_DEBUG

// ダイレクトデバッグ通信が他のものと混線しないように
#define COMMDIRECT_DEBUG_NO  (2)


// データダンプ
#ifdef PM_DEBUG
extern void CommDump_Debug(u8* adr, int length, char* pInfoStr);
#define DEBUG_DUMP(a,l,s)  CommDump_Debug(a,l,s)
#else
#define DEBUG_DUMP(a,l,s)       ((void) 0)
#endif

#endif //_COMMUNICATION_H_
