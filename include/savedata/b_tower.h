/**
 *	@file	b_tower.h
 *	@brief	バトルタワー関連　セーブデータ
 *	@author	Miyuki Iwasawa
 *	@date	06.04.14
 */

#ifndef __H_B_TOWER_H__
#define __H_B_TOWER_H__

#include "b_tower_def.h"

/**
 * @brief	バトルタワー　プレイデータ構造体への不完全型ポインタ
 *
 * 中身は見えませんがポインタ経由で参照できます
 */
typedef struct _BTLTOWER_PLAYWORK	BTLTOWER_PLAYWORK;

/**
 * @brief	バトルタワー　スコアデータ構造体への不完全型ポインタ
 *
 * 中身は見えませんがポインタ経由で参照できます
 */
typedef struct _BTLTOWER_SCOREWORK	BTLTOWER_SCOREWORK;

/**
 * @brief	バトルタワー　プレイヤーメッセージデータ構造体への不完全型ポインタ
 *
 * 中身は見えませんがポインタ経由で参照できます
 */
typedef struct _BTLTOWER_PLAYER_MSG	BTLTOWER_PLAYER_MSG;

/**
 * @brief	バトルタワー　WIFIポケモンデータ構造体への不完全型ポインタ
 *
 * 中身は見えませんがポインタ経由で参照できます
 */
//typedef struct _BTLTOWER_POKE	BTLTOWER_POKE;
/**
 * @brief	バトルタワー　WIFIプレイヤーデータ構造体への不完全型ポインタ
 *
 * 中身は見えませんがポインタ経由で参照できます
 */
typedef struct _BTLTOWER_WIFI_PLAYER	BTLTOWER_WIFI_PLAYER;
/**
 * @brief	バトルタワー　WIFIリーダーデータ構造体への不完全型ポインタ
 *
 * 中身は見えませんがポインタ経由で参照できます
 */
//typedef struct _BTLTOWER_WIFI_LEADER	BTLTOWER_WIFI_LEADER;


/**
 * @brief	バトルタワー　WIFIデータ構造体への不完全型ポインタ
 *
 * 中身は見えませんがポインタ経由で参照できます
 */
typedef struct _BTLTOWER_WIFI_DATA	BTLTOWER_WIFI_DATA;


/**
 *	@brief	バトルタワー　ブロックデータ構造体への不完全型ポインタ
 *
 * 中身は見えませんがポインタ経由で参照できます
 */
typedef struct _BTLTOWER_SAVEWORK	BTLTOWER_SAVEWORK;

/**
 * タワーポケモンデータ型
 * 　battle/b_tower_data.hを必要な箇所以外では
 *	includeしないで済むように定義しておく
 */
typedef struct _B_TOWER_POKEMON	B_TOWER_POKEMON;

/**
 * タワーパートナーデータ型
 * 　battle/b_tower_data.hを必要な箇所以外では
 *	includeしないで済むように定義しておく
 */
typedef struct _B_TOWER_PARTNER_DATA	B_TOWER_PARTNER_DATA;

/**
 * @brief	バトルタワー　WIFIリーダーデータ構造体への不完全型ポインタ
 *  battle/b_tower_data.hを必要な箇所以外では
 *	includeしないで済むように定義しておく
 *
 * 中身は見えませんがポインタ経由で参照できます
 */
typedef struct _B_TOWER_LEADER_DATA	B_TOWER_LEADER_DATA;

/**
 *	@biref	タワーAIマルチペアの保存が必要なポケモンパラメータ
 *	
 *  battle/b_tower_data.hを必要な箇所以外では
 *	includeしないで済むように定義しておく
 */
typedef struct _B_TOWER_PAREPOKE_PARAM B_TOWER_PAREPOKE_PARAM;


/**
 *	@brief	バトルタワー WIFIライブラリ構造体への不完全ポインタ
 *	Wifiライブラリヘッダを外部に非公開にしておくために定義
 */
typedef struct Dpw_Bt_PokemonData	DPW_BT_POKEMON_DATA;
typedef struct Dpw_Bt_Player	DPW_BT_PLAYER;
typedef struct Dpw_Bt_Leader	DPW_BT_LEADER;
typedef struct Dpw_Bt_Room		DPW_BT_ROOM;

/**
 *	@biref	バトルタワー WIFIルームデータID(rankとroomno)
 *
 *	ランクとルームナンバーを取得したいときようの公開構造体データ型
 */
typedef struct{
	u8	rank;	//ルームランク(1-10)
	u8	no;		//ルームNo(1-200)
}BTOWER_ROOMID;

//========================================================
//セーブデータアクセス
//========================================================

#ifdef GLOBAL
#undef GLOBAL
#endif

#ifdef _B_TOWER_H_GLOBAL
#define GLOBAL	/***/
#else
#define GLOBAL	extern
#endif

///ワークサイズ取得＆クリア
//////////////////////////////////
/**
 *	@brief	タワー　プレイデータサイズ
 */
GLOBAL int TowerPlayData_GetWorkSize(void);

/**
 *	@brief	タワー　プレイヤースコアデータサイズ
 */
GLOBAL int	TowerSocreData_GetWorkSize(void);

/**
 *	@brief	タワー　ポケモンデータサイズ
 */
GLOBAL int TowerWifiPoke_GetWorkSize(void);

/**
 *	@brief	タワー　Wifiデータサイズ
 */
GLOBAL int	TowerWifiData_GetWorkSize(void);
/**
 *	@brief　タワー Wifi/トレーナーロードプレイヤーデータ構造体データサイズ
 */
GLOBAL int TowerDpwBtPlayer_GetWorkSize(void);

/**
 *	@brief	タワー　プレイデータクリア
 */
GLOBAL void TowerPlayData_Clear(BTLTOWER_PLAYWORK* dat);

/**
 *	@brief	タワー	スコアデータクリア
 */
GLOBAL void TowerScoreData_Clear(BTLTOWER_SCOREWORK* dat);

/**
 *	@brief	タワー　プレイヤーメッセージデータクリア
 */
GLOBAL void TowerPlayerMsg_Clear(BTLTOWER_PLAYER_MSG* dat);

/**
 *	@brief	タワー　Wifiデータクリア
 */
GLOBAL void TowerWifiData_Clear(BTLTOWER_WIFI_DATA* dat);

///ブロックデータアクセス系
/////////////////////////////////
/**
 *	@brief	タワー　セーブデータブロックサイズを取得
 */
GLOBAL int TowerData_GetWorkSize(void);

/**
 *	@brief	タワー　セーブデータブロック初期化
 */
GLOBAL void TowerData_Init(BTLTOWER_SAVEWORK* save);

/**
 *	@brief	タワー　プレイデータへのポインタを取得
 */
GLOBAL BTLTOWER_PLAYWORK* SaveData_GetTowerPlayData(SAVEDATA* sv);

/**
 *	@brief	タワー　スコアデータへのポインタを取得
 */
GLOBAL BTLTOWER_SCOREWORK* SaveData_GetTowerScoreData(SAVEDATA* sv);

/**
 *	@brief	タワー Wifiデータへのポインタを取得	
 */
GLOBAL BTLTOWER_WIFI_DATA*	SaveData_GetTowerWifiData(SAVEDATA* sv);

////////////////////////////////////////////////////////////
//プレイデータ取得系
////////////////////////////////////////////////////////////
/**
 *	@brief	プレイデータ　取得
 *
 *	@param	dat	BTLTOWRE_PLAYWORK*
 *	@param	id	取得するデータID BTOWER_PSD_ID型
 *	@param	buf	void*:データ取得ポインタ
 */
GLOBAL u32	TowerPlayData_Get(BTLTOWER_PLAYWORK* dat,BTWR_PSD_ID id,void* buf);

/**
 *	@brief	プレイデータ　セット
 *	
 *	@param	dat	BTLTOWRE_PLAYWORK*
 *	@param	id	取得するデータID BTOWER_PSD_ID型
 *	@param	buf	void*:データを格納したバッファへのポインタ
 */
GLOBAL void TowerPlayData_Put(BTLTOWER_PLAYWORK* dat,BTWR_PSD_ID id,const void* buf);

/**
 *	@brief プレイデータ　WifiレコードデータAdd	
 *
 *	@param	down	倒されたポケモン追加数
 *	@param	turn	かかったターン追加数
 *	@param	damage	受けたダメージ追加値
 */
GLOBAL void TowerPlayData_WifiRecordAdd(BTLTOWER_PLAYWORK* dat,u8 down,u16 turn,u16 damage);

/**
 *	@brief	プレイデータ　正しくセーブ済みかどうか？
 *
 *	@retval	TRUE	正しくセーブされている
 *	@retval FALSE	セーブされていない
 */
GLOBAL BOOL TowerPlayData_GetSaveFlag(BTLTOWER_PLAYWORK* dat);
/**
 *	@brief	プレイデータ　セーブ状態フラグをセット
 */
GLOBAL void TowerPlayData_SetSaveFlag(BTLTOWER_PLAYWORK* dat,BOOL flag);


///スコアデータ取得系
/////////////////////////////////////////////////

/**
 *	@brief	スコアデータ バトルポイントセット
 *
 *	有効コマンド set/get/add/sub
 */
GLOBAL u16 TowerScoreData_SetBattlePoint(BTLTOWER_SCOREWORK* dat,u16 num,BTWR_DATA_SETID mode);

/**
 *	@brief	SAVEDATAからバトルポイントをGet
 */
static inline u16 BattlePoint_Get(SAVEDATA* sv)
{
	return TowerScoreData_SetBattlePoint(SaveData_GetTowerScoreData(sv),0,BTWR_DATA_get);
}
/**
 *	@brief	SAVEDATAからバトルポイントをSet
 */
static inline u16 BattlePoint_Set(SAVEDATA* sv,u16 num)
{
	return TowerScoreData_SetBattlePoint(SaveData_GetTowerScoreData(sv),num,BTWR_DATA_set);
}
/**
 *	@brief	SAVEDATAからバトルポイントをAdd
 */
static inline u16	BattlePoint_Add(SAVEDATA* sv,u16 num)
{
	return TowerScoreData_SetBattlePoint(SaveData_GetTowerScoreData(sv),num,BTWR_DATA_add);
}
/**
 *	@brief	SAVEDATAからバトルポイントをSub
 */
static inline u16	BattlePoint_Sub(SAVEDATA* sv,u16 num)
{
	return TowerScoreData_SetBattlePoint(SaveData_GetTowerScoreData(sv),num,BTWR_DATA_sub);
}

/**
 *	@brief	スコアデータ　Wifi連続敗戦カウント操作
 *
 *	有効コマンド get/reset/inc
 *
 *	@return	操作後のカウント
 */
GLOBAL u8 TowerScoreData_SetWifiLoseCount(BTLTOWER_SCOREWORK* dat,BTWR_DATA_SETID mode);

/**
 *	@brief	スコアデータ　Wifiランク操作
 *
 *	有効コマンド get/reset/inc/dec
 */
GLOBAL u8	TowerScoreData_SetWifiRank(BTLTOWER_SCOREWORK* dat,BTWR_DATA_SETID mode);

/**
 *	@brief	使用ポケモンデータ保存
 */
GLOBAL void TowerScoreData_SetUsePokeData(BTLTOWER_SCOREWORK* dat,
				BTWR_SCORE_POKE_DATA mode,B_TOWER_POKEMON* poke);
/**
 *	@brief	使用ポケモンデータをバッファにコピーして取得(WiFi構造体データ型)
 */
GLOBAL void TowerScoreData_GetUsePokeDataDpw(BTLTOWER_SCOREWORK* dat,
			BTWR_SCORE_POKE_DATA mode,DPW_BT_POKEMON_DATA* poke);

/**
 *	@brief	使用ポケモンデータをバッファにコピーして取得
 */
GLOBAL void TowerScoreData_GetUsePokeData(BTLTOWER_SCOREWORK* dat,
			BTWR_SCORE_POKE_DATA mode,B_TOWER_POKEMON* poke);


/**
 *	@brief	スコアデータ　周回数操作
 */
GLOBAL u16 TowerScoreData_SetStage(BTLTOWER_SCOREWORK* dat,u16 id,BTWR_DATA_SETID mode);

#ifdef PM_DEBUG
/**
 *	@brief	デバッグ限定　現在のステージ値を直接セットする
 */
GLOBAL u16 TowerScoreData_DebugSetStageValue(BTLTOWER_SCOREWORK* dat,u16 id,u16 value);
#endif	//PM_DEBUG
/**
 *	@brief	スコアデータ Wifi成績操作
 */
GLOBAL u16	TowerScoreData_SetWifiScore(BTLTOWER_SCOREWORK* dat,BTLTOWER_PLAYWORK *playdata);

/**
 *	@brief	スコアデータ　Wifi成績0クリア
 */
GLOBAL void TowerScoreData_ClearWifiScore(BTLTOWER_SCOREWORK* dat);

/**
 *	@brief	スコアデータ　Wifi成績取得
 */
GLOBAL u16	TowerScoreData_GetWifiScore(BTLTOWER_SCOREWORK* dat);

/**
 *	@brief	スコアデータから勝ち抜いた数を取得
 */
GLOBAL u8	TowerScoreData_GetWifiWinNum(BTLTOWER_SCOREWORK* dat);

/**
 *	@brief	スコアデータ フラグエリアセット
 *
 *	有効コマンド：reset/set/get
 */
GLOBAL BOOL TowerScoreData_SetFlags(BTLTOWER_SCOREWORK* dat,u16 id,BTWR_DATA_SETID mode);

/**
 *	@brief	タワー用日付変化ランダムシード保存
 */
GLOBAL void TowerScoreData_SetDayRndSeed(BTLTOWER_SCOREWORK* dat,u32 rnd_seed);

/**
 *	@brief	タワー用日付変化ランダムシード取得
 */
GLOBAL u32 TowerScoreData_GetDayRndSeed(BTLTOWER_SCOREWORK* dat);


//=======================================================
//　タワー　プレイヤーメッセージデータアクセス系
//=======================================================
/**
 *	@brief	簡易会話データをセット
 */
GLOBAL void TowerPlayerMsg_Set(SAVEDATA* sv,BTWR_PLAYER_MSG_ID id,PMS_DATA* src);

/**
 *	@brief	簡易会話データを取得
 */
GLOBAL PMS_DATA* TowerPlayerMsg_Get(SAVEDATA* sv,BTWR_PLAYER_MSG_ID id);

//=======================================================
//　タワー　Wifiデータアクセス系
//=======================================================
/**
 *	@brief	指定したルームデータの取得フラグを立てる
 *
 *	@param	rank	1オリジンなので注意
 *	@param	roomno	1オリジンなので注意
 */
GLOBAL void TowerWifiData_SetRoomDataFlag(BTLTOWER_WIFI_DATA* dat,
		u8 rank,u8 roomno,RTCDate *day);

/**
 *	@brief	ルームデータ取得フラグをクリアする
 */
GLOBAL void TowerWifiData_ClearRoomDataFlag(BTLTOWER_WIFI_DATA* dat);

/**
 *	@brief	指定したルームのDLフラグが立っているかチェック
 *
 *	@param	rank	1オリジンなので注意
 *	@param	roomno	1オリジンなので注意
 */
GLOBAL BOOL TowerWifiData_CheckRoomDataFlag(BTLTOWER_WIFI_DATA* dat,u8 rank,u8 roomno,RTCDate* day);


/**
 *	@brief	プレイヤーデータが存在するかチェック
 */
GLOBAL BOOL TowerWifiData_IsPlayerDataEnable(BTLTOWER_WIFI_DATA* dat);

/**
 *	@brief	リーダーデータがあるかどうかチェック
 */
GLOBAL BOOL TowerWifiData_IsLeaderDataEnable(BTLTOWER_WIFI_DATA* dat);

/**
 *	@brief	プレイヤーデータをセーブ
 *	
 *	@param	rank	1オリジンなので注意
 *	@param	roomno	1オリジンなので注意
 */
GLOBAL void TowerWifiData_SetPlayerData(BTLTOWER_WIFI_DATA* dat,DPW_BT_PLAYER* src,u8 rank,u8 roomno);

/**
 *	@brief	プレイヤーデータをクリア
 */
GLOBAL void TowerWifiData_ClearPlayerData(BTLTOWER_WIFI_DATA* dat);

/**
 *	@brief	プレイヤーデータのRoomID(ランクとroomNo)を取得
 *
 *	@param	roomid	BTOWER_ROOMID型(b_tower.hで公開)
 */
GLOBAL void TowerWifiData_GetPlayerDataRoomID(BTLTOWER_WIFI_DATA* dat,BTOWER_ROOMID *roomid);

/**
 *	@brief	プレイヤーデータをタワー戦闘用に解凍
 */
GLOBAL void TowerWifiData_GetBtlPlayerData(BTLTOWER_WIFI_DATA* dat,
		B_TOWER_PARTNER_DATA* player,const u8 round);

/**
 *	@brief	リーダーデータをセーブ
 *	
 *	@param	rank	1オリジンなので注意
 *	@param	roomno	1オリジンなので注意
 */
GLOBAL void TowerWifiData_SetLeaderData(BTLTOWER_WIFI_DATA* dat,DPW_BT_LEADER* src,u8 rank,u8 roomno);

/**
 *	@brief	リーダーデータをクリア
 */
GLOBAL void TowerWifiData_ClearLeaderData(BTLTOWER_WIFI_DATA* dat);

/**
 *	@brief	リーダーデータのRoomID(ランクとroomNo)を取得
 *
 *	@param	roomid	BTOWER_ROOMID型(b_tower.hで公開)
 */
GLOBAL void TowerWifiData_GetLeaderDataRoomID(BTLTOWER_WIFI_DATA* dat,BTOWER_ROOMID *roomid);

/**
 *	@brief	リーダーデータをAllocしたメモリにコピーして取得する
 *
 *	＊内部でAllocしたメモリ領域を返すので、呼び出し側が明示的に解放すること！
 */
GLOBAL B_TOWER_LEADER_DATA* TowerWifiData_GetLeaderDataAlloc(BTLTOWER_WIFI_DATA* dat,int heapID) ;




#endif	//__H_B_TOWER_H__
