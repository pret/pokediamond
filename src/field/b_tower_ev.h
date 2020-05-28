/**
 *	@file	b_tower_ev.h
 *	@brief	バトルタワー　常駐イベントコントローラ
 *	@author	Miyuki Iwasawa
 *	@date	06.04.26
 */

#ifndef __H_B_TOWER_EV_H__
#define __H_B_TOWER_EV_H__

#ifdef GLOBAL
#undef GLOBAL
#endif

#ifdef _B_TOWER_EV_H_GLOBAL
#define GLOBAL	/***/
#else
#define GLOBAL	extern
#endif

//--------------------------------------------------------------
/**
 * @brief	ポケモン選択　サブイベント呼び出し
 * @param	event	GMEVENT_CONTROL*
 * @retval	nothing
 */
//--------------------------------------------------------------
GLOBAL void EventCmd_BTowerPokeSelectCall(GMEVENT_CONTROL *event,void** buf,
	u8 plmode,u8 psmode,u8 min,u8 max,u8 level,u8 pos);

//--------------------------------------------------------------
/**
 * @brief	WiFi接続　サブイベント呼び出し
 * @param	event	GMEVENT_CONTROL*
 * @param	mode	接続モード
 * @param	ret_wk_no	返り値を返すワークID
 * @param	dpw_code	DPW_INIT_PROCが返した返り値
 * @retval	nothing
 */
//--------------------------------------------------------------
GLOBAL void EventCmd_BTowerWifiCall(GMEVENT_CONTROL *event,u16 mode,u16 ret_wk_no,u16 dpw_code);

//--------------------------------------------------------------
/**
 * @brief	通信マルチ　データ受信サブイベント
 * @param	event	GMEVENT_CONTROL*
 * @param	mode	受信モード
 * @param	ret_wk_no	返り値取得用ワークID
 * @retval	nothing
 */
//--------------------------------------------------------------
GLOBAL void EventCmd_BTowerSioRecvBuf(GMEVENT_CONTROL *event,u16 mode,u16 ret_wk_no);

/**
 *	@brief	プライズをもらえるかどうかチェックする
 *
 *	@retval	0	もらえない
 */
GLOBAL u16 BtlTower_IsPrizeGet(SAVEDATA* sv);

/**
 *	@brief	プライズをくれるヒトの表示状態を返す
 *
 *	@retval	0	非表示
 *	@retval	1	
 */
GLOBAL u16 BtlTower_IsPrizemanSet(SAVEDATA* sv);

/**
 *	@brief	タワー対戦結果　アップデート処理
 */
GLOBAL void BtlTower_BattleRecordUpdate(FIELDSYS_WORK* fsys,const BATTLE_TOWER_RECORD* rec);

/**
 *	@brief	タワープレイ更新ランダム計算
 *
 *	＊バトルタワー以外からは呼んではいけません
 *	　さもないと、データにズレが発生します
 */
GLOBAL u32	BtlTower_PlayFixRand(u32 seed);

/**
 *	@brief	タワー日付更新ランダム計算
 *
 *	＊バトルタワー以外からは呼んではいけません
 *	　さもないと、データにズレが発生します
 */
GLOBAL u32	BtlTower_DayFixRand(u32 seed);

/**
 *	@brief	タワー日付更新ランダムシード　一日一回の更新処理新
 *　2923037603
 *	＊日付更新処理&new game時に一度だけ呼べます
 *	　それ以外で呼ぶと、データにズレが発生します
 */
GLOBAL u32 BtlTower_UpdateDayRndSeed(SAVEDATA* sv);

/**
 *	@brief	タワー日付/プレイ更新ランダムシード　挑戦開始時の更新処理
 *
 *	＊タワーnew game開始時に一度だけ呼べます
 *	　それ以外で呼ぶと、データにズレが発生します
 */
GLOBAL u32	BtlTower_UpdatePlayRndSeed(SAVEDATA* sv);

/**
 *	@brief	タワー日付/プレイ更新ランダムシード取得　継続挑戦開始時の取得処理
 */
GLOBAL u32	BtlTower_GetContinuePlayRndSeed(SAVEDATA* sv);

/**
 *	@brief	バトルタワーサロン判定
 *
 *	@retval	TRUE	サロン
 *	@retval	FALSE	サロンじゃない
 */
GLOBAL BOOL BtlTower_IsSalon(FIELDSYS_WORK* fsys);

#endif	//__H_B_TOWER_EV_H__
