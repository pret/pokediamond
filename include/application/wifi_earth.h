//============================================================================================
/**
 * @file	wifi_earth.h
 * @brief
 * @date	
 */
//============================================================================================

#ifndef	__WIFIEARTH_H__
#define	__WIFIEARTH_H__

//============================================================================================
/**
 * @brief	Proc 呼び出しの際に引き渡されるワーク構造体
 */
//============================================================================================
#if 0
typedef struct WIFI_EARTH_PARAM_tag
{
	SAVEDATA* savedata;
}WIFI_EARTH_PARAM;
#endif

extern PROC_RESULT Earth_Demo_Init(PROC * proc, int * seq);
extern PROC_RESULT Earth_Demo_Main(PROC * proc, int * seq);
extern PROC_RESULT Earth_Demo_Exit(PROC * proc, int * seq);
//============================================================================================
/**
 * @brief	Proc 呼び出し用テーブル
 */
//============================================================================================
extern const PROC_DATA Earth_Demo_proc_data;

//============================================================================================
/**
 *	地域データ初期化（セーブワークの初期化）
 *
 * @param[in]	savedata	セーブデータへのポインタ	
 * @retval
 */
//============================================================================================
extern void	WIFI_RegistratonInit(SAVEDATA* savedata);

//============================================================================================
/**
 *	国名取得
 *
 * @param[in]	nationID	国ＩＤ
 * @param[in]	areaID		地域ＩＤ
 * @param[in]	nation_str	国名格納バッファポインタ
 * @param[in]	area_str	地域名格納バッファポインタ
 * @param[in]	heapID		テンポラリヒープＩＤ
 *
 * @retval	FALSE:地域がない国　TRUE:地域がある国
 */
//============================================================================================
extern BOOL	WIFI_NationAreaNameGet
			(int nationID,int areaID,STRBUF* nation_str,STRBUF* area_str,int heapID);

//============================================================================================
/**
 *	ローカルエリア存在チェック
 *
 * @param[in]	nationID	国ＩＤ
 *
 * @retval	FALSE:地域なし　TRUE:地域あり
 */
//============================================================================================
extern BOOL	WIFI_LocalAreaExistCheck(int nationID);

#endif
