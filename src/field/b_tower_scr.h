/**
 *	@file	btower_scr.h
 *	@brief	バトルタワー　スクリプト系
 *	@author	Miyuki Iwasawa
 *	@date	06.04.17
 */

#ifndef __H_B_TOWER_SCR_H__
#define __H_B_TOWER_SCR_H__

#ifdef GLOBAL
#undef GLOBAL
#endif

#ifdef __B_TOWER_SCR_H_GLOBAL
#define GLOBAL	/***/
#else
#define GLOBAL	extern
#endif

#include "b_tower_scr_def.h"
#include "battle/battle_common.h"
#include "battle/b_tower_data.h"

///バトルタワー　スクリプトワーク
typedef struct _BTOWER_SCRWORK{
	int	magicNo;	///<マジックナンバー
	int	heapID;	///<ヒープ
	u32	play_rnd_seed;	///<プレイ用ランダムシード
	u8	now_round;	///<現在何人目？
	u8	now_win;	///<現在何人に勝った？
	u8	member_num;	///<メンバー数
	u8	play_mode;	///<プレイデータ

	u8	clear_f:1;	///<クリアフラグ
	u8	leader_f:2;	///<タイクーン2
	u8	retire_f:1;	///<リタイアフラグ
	u8	prize_f:1;	///<ご褒美フラグ
	u8	partner:3;	///<パートナーNo

	u8	my_sex;			///<自分の性別
	u8	pare_sex;		///<自分とパートナーの性別
	u16	pare_stage;		///<通信マルチパートナーの周回数
	u16	pare_poke[2];	///<通信マルチパートナーが持つポケモンNo
	
	u16	renshou;	///<現在の連勝数
	u16	stage;		///<現在の周回数
	u32	win_cnt;	///<現在までの総勝利数

	u16	rec_turn;	///<かかったターン数
	u16	rec_damage;	///<食らったダメージ
	u16	rec_down;	///<ポケモンのダウン数

	u8	member[BTOWER_STOCK_MEMBER_MAX];	///<選んだポケモンの手持ちNo
	u16	mem_poke[BTOWER_STOCK_MEMBER_MAX];	///<選んだポケモンのmonsno
	u16	mem_item[BTOWER_STOCK_MEMBER_MAX];	///<選んだポケモンのアイテムno
	u16	trainer[BTOWER_STOCK_TRAINER_MAX];	///<対戦トレーナーNo

	//現在のロケーションを記憶しておく
	LOCATION_WORK	now_location;

	BTLTOWER_PLAYWORK*	playSave;	///<セーブデータへのポインタ
	BTLTOWER_SCOREWORK*	scoreSave;	///<セーブデータへのポインタ

	//対戦相手データ格納場所
	B_TOWER_PARTNER_DATA	tr_data[2];
	
	//5人衆抽選データ格納場所
	B_TOWER_PARTNER_DATA	five_data[BTWR_FIVE_NUM];

	//5人衆抽選ポケモンパラメータ格納場所
	B_TOWER_PAREPOKE_PARAM	five_poke[BTWR_FIVE_NUM];

	//5人衆抽選ポケモンアイテムfixフラグ
	u8						five_item[BTWR_FIVE_NUM];

	//通信用データバッファ
	u16	send_buf[35];
	u16	recv_buf[35];
}BTOWER_SCRWORK;


///スクリプトコマンドから呼び出すルーチン群
///////////////////////////////////////////////////////
/**
 *	@brief	プレイモード別のメンバー数を取得する
 */
GLOBAL u16	TowerScrTools_GetMemberNum(u16 mode);

/**
 *	@brief	バトルタワー　参加可能なポケモン数のチェック
 *
 *	@param	num		参加に必要なポケモン数
 *
 *	@retval	true	参加可能
 *	@retval	false	参加不可
 */
GLOBAL BOOL TowerScrTools_CheckEntryPokeNum(u16 num,SAVEDATA *savedata);

/**
 *	@brief	リセットしてタイトルに戻る
 */
GLOBAL void TowerScrTools_SystemReset(void);

/**
 *	@brief	new game時にプレイデータをクリアする
 */
GLOBAL void TowerScrTools_ClearPlaySaveData(BTLTOWER_PLAYWORK* playSave);

/**
 * @brief	セーブデータが有効かどうか返す
 */
GLOBAL BOOL TowerScrTools_IsSaveDataEnable(BTLTOWER_PLAYWORK* playSave);

/**
 *	@brief	脱出用に現在のロケーションを記憶する
 */
GLOBAL void TowerScrTools_PushNowLocation(FIELDSYS_WORK* fsys);

/**
 *	@brief	ゲートから出る時に特殊接続先を元に戻す
 */
GLOBAL void TowerScrTools_PopNowLocation(FIELDSYS_WORK* fsys);

/**
 *	@brief	入ったゲートの位置を取得する
 */
GLOBAL void TowerScrTools_GetGateLocation(FIELDSYS_WORK* fsys,u16* x,u16* y);

/**
 *	@brief	プレイモード別レコードセーブデータ連勝数を返す
 */
GLOBAL u16	TowerScrTools_GetRenshouRecord(SAVEDATA* sv,u16 play_mode);

/**
 *	@brief	スコアデータのフラグを返す
 */
GLOBAL u16 TowerScrTools_GetScoreFlags(SAVEDATA* sv,BTWR_SFLAG_ID flagid);

/**
 *	@brief	Wifi成績の未アップロードフラグを制御する
 */
GLOBAL void TowerScrTools_SetWifiUploadFlag(SAVEDATA* sv,u8 flag);

/**
 *	@brief	WiFiプレイ成績の未アップロードフラグを取得する
 */
GLOBAL u16 TowerScrTools_GetWifiUploadFlag(SAVEDATA* sv);

/**
 *	@brief	セーブせずに止めたときのエラー処理
 *
 *	@return	プレイしていたモードを返す
 */
GLOBAL u16 TowerScrTools_SetNGScore(SAVEDATA* savedata);

/**
 *	@brief	WIFIのプレイヤーDLデータがあるかどうかチェック
 */
GLOBAL u16	TowerScrTools_IsPlayerDataEnable(SAVEDATA* sv);


//*****************************************************
//=====================================================
//ワークの初期化と解放
//=====================================================
//*****************************************************
/**
 *	@brief	fsys内のバトルタワー制御ワークポインタを初期化する
 *			バトルタワー開始時に必ず呼び出す
 */
GLOBAL void TowerScr_WorkClear(BTOWER_SCRWORK** pp);

/**
 *	@brief	ワークエリアを取得して初期化する
 *
 *	@param	savedata	セーブデータへのポインタ
 *	@param	init		初期化モード BTWR_PLAY_NEW:初めから、BTWR_PLAY_CONTINE:続きから
 *	@param	playmode	プレイモード指定 BTWR_MODE_～
 *	
 *	＊かならず TowerScr_WorkRelease()で領域を開放すること
 */
GLOBAL BTOWER_SCRWORK* TowerScr_WorkInit(SAVEDATA* savedata,u16 init,u16 playmode);

/**
 *	@brief	ワークエリアを開放する
 */
GLOBAL void TowerScr_WorkRelease(BTOWER_SCRWORK* wk);


/**
 *	@brief	バトルタワー用ポケモン選択呼出し
 */
GLOBAL void TowerScr_SelectPoke(BTOWER_SCRWORK* wk,
				GMEVENT_CONTROL *ev_work,void** proc_wk);

/**
 *	@brief	選択したポケモンを取得
 *	
 *	@retval	TRUE	選択した
 *	@retval	FALSE	選択せずにやめた
 */
GLOBAL BOOL TowerScr_GetEntryPoke(BTOWER_SCRWORK* wk,void** app_work,SAVEDATA* sv);

/**
 *	@brief	参加指定した手持ちポケモンの条件チェック
 *
 *	@retval	0	参加OK
 *	@retval	1	同じポケモンがいる
 *	@retval 2	同じアイテムを持っている
 */
GLOBAL int TowerScr_CheckEntryPoke(BTOWER_SCRWORK* wk,SAVEDATA* savedata);

/**
 *	@brief　対戦トレーナーNo抽選
 */
GLOBAL void TowerScr_BtlTrainerNoSet(BTOWER_SCRWORK* wk,SAVEDATA* sv);

/**
 *	@brief	現在のラウンド数をスクリプトワークに取得する
 */
GLOBAL u16	TowerScr_GetNowRound(BTOWER_SCRWORK* wk);

/**
 *	@brief	ラウンド数をインクリメント
 */
GLOBAL u16	TowerScr_IncRound(BTOWER_SCRWORK* wk);

/**
 *	@brief	7連勝しているかどうかチェック
 */
GLOBAL BOOL TowerScr_IsClear(BTOWER_SCRWORK* wk);

/**
 *	@brief	現在の連勝数を取得する
 */
GLOBAL u16 TowerScr_GetRenshouCount(BTOWER_SCRWORK* wk);

/**
 *	@brief	敗戦処理	
 */
GLOBAL void TowerScr_SetLoseScore(BTOWER_SCRWORK* wk,FIELDSYS_WORK* fsys);

/**
 *	@brief	クリア処理
 */
GLOBAL void TowerScr_SetClearScore(BTOWER_SCRWORK* wk,FIELDSYS_WORK* fsys);


/**
 *	@brief	休むときに現在のプレイ状況をセーブに書き出す
 */
GLOBAL void TowerScr_SaveRestPlayData(BTOWER_SCRWORK* wk);


/**
 *	@brief	対戦トレーナー抽選
 */
GLOBAL void TowerScr_ChoiceBtlPartner(BTOWER_SCRWORK* wk,SAVEDATA* sv);
/**
 *	@brief	AIマルチペアポケモン抽選
 */
GLOBAL void TowerScr_ChoiceBtlSeven(BTOWER_SCRWORK* wk);

/**
 *	@brief	対戦トレーナーOBJコード取得
 */
GLOBAL u16 TowerScr_GetEnemyObj(BTOWER_SCRWORK* wk,u16 idx);

/**
 *	@brief	戦闘呼び出し
 */
GLOBAL void TowerScr_LocalBattleCall(GMEVENT_CONTROL* event,BTOWER_SCRWORK* wk,BOOL* win_flag);

/**
 *	@brief	現在のプレイモードを返す
 */
GLOBAL u16	TowerScr_GetPlayMode(BTOWER_SCRWORK* wk);

/**
 *	@brief	リーダークリアフラグを立てる
 */
GLOBAL void TowerScr_SetLeaderClearFlag(BTOWER_SCRWORK* wk,u16 mode);

/**
 *	@brief	リーダークリアフラグを取得する
 */
GLOBAL	u16	TowerScr_GetLeaderClearFlag(BTOWER_SCRWORK* wk);

/**
 *	@brief	タワークリア時にバトルポイントを加算する
 *
 *	@return	新たに取得したバトルポイント
 */
GLOBAL u16	TowerScr_AddBtlPoint(BTOWER_SCRWORK* wk);

/**
 *	@brief	シングルで連勝した時のご褒美のトロフィーをあげるフラグを立てておく
 */
GLOBAL	u16	TowerScr_GoodsFlagSet(BTOWER_SCRWORK* wk,SAVEDATA* sv);

/**
 *	@brief	現在のWIFIランクを操作して返す
 */
GLOBAL u16	TowerScr_SetWifiRank(BTOWER_SCRWORK* wk,SAVEDATA* sv,u8 mode);


/**
 *	@brief	リーダーを倒したご褒美リボンをあげる
 */
GLOBAL u16 TowerScr_LeaderRibbonSet(BTOWER_SCRWORK* wk,SAVEDATA* sv);

/**
 *	@brief	連勝のご褒美リボンをあげる	
 */
GLOBAL u16 TowerScr_RenshouRibbonSet(BTOWER_SCRWORK* wk,SAVEDATA* sv);

/**
 *	@biref	プレイランダムシードを更新する
 */
GLOBAL u16 TowerScr_PlayRandUpdate(BTOWER_SCRWORK* wk,SAVEDATA* sv);



#endif	//__H_BTOWER_SCR_H__

