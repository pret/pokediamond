//============================================================================================
/**
 * @file	wifihistory.h
 * @brief
 * @date	2006.03.25
 */
//============================================================================================

#ifndef	__WIFIHISTORY_H__
#define	__WIFIHISTORY_H__

#include "savedata/savedata_def.h"

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	WiFi通信履歴データの不完全型宣言
 */
//----------------------------------------------------------
typedef struct _WIFI_HISTORY WIFI_HISTORY;

///WiFi通信履歴を残す国の数
#define	WIFI_NATION_MAX		(256)

///WiFi通信履歴を残す国のそれぞれの地域コードの最大数
#define	WIFI_AREA_MAX		(64)


///日本の地球儀定義(本当はcountry103なんだけ参照できないので）
#define WIFI_NATION_JAPAN	( 103 ) 


//----------------------------------------------------------
/**
 * @brief	WiFi通信履歴データの状態定義
 */
//----------------------------------------------------------
typedef enum {
	WIFIHIST_STAT_NODATA = 0,	///<まだ通信したことがない
	WIFIHIST_STAT_NEW = 1,		///<本日初めて通信した
	WIFIHIST_STAT_EXIST = 2,	///<通信したことがある
	WIFIHIST_STAT_MINE = 3,		///<自分の場所

	WIFIHIST_STAT_MAX,
}WIFIHIST_STAT;

//----------------------------------------------------------
//----------------------------------------------------------
//ワークサイズ取得（セーブシステムから呼ばれる）
extern int WIFIHISTORY_GetWorkSize(void);
//初期化（セーブシステムから呼ばれる）
extern void WIFIHISTORY_Init(WIFI_HISTORY * hist);
//セーブデータ取得（使う箇所で呼ぶ）
extern WIFI_HISTORY * SaveData_GetWifiHistory(SAVEDATA * sv);

//↓動作確認していません。
extern void WIFIHISTORY_SetMyNationArea(WIFI_HISTORY * wh, int nation, int area);
extern int WIFIHISTORY_GetMyNation(const WIFI_HISTORY * wh);
extern int WIFIHISTORY_GetMyArea(const WIFI_HISTORY * wh);
extern void WIFIHISTORY_SetStat(WIFI_HISTORY * wh, int nation, int area, WIFIHIST_STAT stat);
extern WIFIHIST_STAT WIFIHISTORY_GetStat(const WIFI_HISTORY * wh, int nation, int area);

extern BOOL WIFIHISTORY_GetWorldFlag(const WIFI_HISTORY * wh);
extern void WIFIHISTORY_SetWorldFlag(WIFI_HISTORY * wh, BOOL flag);

//日付による更新処理
extern void WIFIHISTORY_Update(WIFI_HISTORY * wh);

#endif	/* __WIFIHISTORY_H__ */

