/**
 *	@file	b_tower_fld.h
 *	@brief	バトルタワー　スクリプト関連　サブルーチン群
 *	@author	Miyuki Iwasawa
 *	@date	06.04.17
 */

#ifndef __H_B_TOWER_FLD_H__
#define __H_B_TOWER_FLD_H__

#ifdef GLOBAL
#undef GLOBAL
#endif

#ifdef __B_TOWER_FLD_H_GLOBAL
#define GLOBAL	/***/
#else
#define GLOBAL	extern
#endif

/**
 *	@brief	参加できないポケモン名をタグ展開
 */
GLOBAL WORDSET* BtlTower_SetNgPokeName(SAVEDATA* sv,u16 pokenum,u16 sex,u8 flag,u8* num);

/**
 *	@brief	トレーナータイプから人物OBJコードを返す
 */
GLOBAL u16 BtlTower_TrType2ObjCode(u8 tr_type);

/**
 *	@brief	バトルタワー用　バトルパラメータ生成
 */
GLOBAL BATTLE_PARAM* BtlTower_CreateBattleParam(BTOWER_SCRWORK* wk,FIELDSYS_WORK* fsys);


/**
 *	@brief	バトルタワー　送られてきたプレイヤーデータを受け取る
 */
GLOBAL u16 BTowerComm_RecvPlayerData(FIELDSYS_WORK* fsys,const u16* recv_buf);

/**
 *	@brief	バトルタワー　送られてきたトレーナーデータを受け取る
 */
GLOBAL u16	BTowerComm_RecvTrainerData(FIELDSYS_WORK* fsys,const u16* recv_buf);

/**
 *	@brief	バトルタワー　送られてきたリタイアするかどうかの結果を受け取る
 *
 *	@retval	0	リタイアしない
 *	@retval	1	リタイアする
 */
GLOBAL u16	BTowerComm_RecvRetireSelect(FIELDSYS_WORK* fsys,const u16* recv_buf);

/**
 *	@brief	バトルタワー　自機性別とモンスターNoを送信
 */
GLOBAL void BTowerComm_SendPlayerData(BTOWER_SCRWORK* wk,SAVEDATA *sv);

/**
 *	@brief	バトルタワー　通信マルチ　抽選したトレーナーNoを子機に送信
 */
GLOBAL void BTowerComm_SendTrainerData(BTOWER_SCRWORK* wk);

/**
 *	@brief	バトルタワー　通信マルチ　リタイアするかどうかを互いに送信
 *
 *	@param	retire	TRUEならリタイア
 */
GLOBAL void BTowerComm_SendRetireSelect(BTOWER_SCRWORK* wk,u16 retire);

/**
 *	@brief	トレーナーナンバー抽選
 */
GLOBAL u16	BattleTowerTrainerNoGet(BTOWER_SCRWORK* wk,u8 stage,u8 round,int play_mode);

/**
 *	@brief	Wifi トレーナー抽選
 */
GLOBAL void btltower_BtlPartnerSelectWifi(SAVEDATA* sv,B_TOWER_PARTNER_DATA* wk,
		const u8 round);

//============================================================================================
/**
 *	バトルタワートレーナーデータ生成（ロムデータをB_TOWER_PARTNER_DATA構造体に展開）
 *
 * @param[in/out]	tr_data		生成するB_TOWER_PARTNAER_DATA構造体
 * @param[in]		tr_no		生成元になるトレーナーID
 * @param[in]		cnt			トレーナーに持たせるポケモンの数
 * @param[in]		set_poke_no	ペアを組んでいるトレーナーの持ちポケモン（NULLだとチェックなし）
 * @param[in]		set_item_no	ペアを組んでいるトレーナーの持ちポケモンの装備アイテム（NULLだとチェックなし）
 * @param[in/out]	poke		抽選されたポケモンの二体のパラメータを格納して返す構造体型データへのポインタ(NULLだとチェックなし）
 * @param[in]		heapID		ヒープID
 *
 * @retval	FALSE	抽選ループが50回以内で終わった
 * @retval	TRUE	抽選ループが50回以内で終わらなかった
 */
//============================================================================================
GLOBAL BOOL	RomBattleTowerTrainerDataMake(BTOWER_SCRWORK* wk,B_TOWER_PARTNER_DATA *tr_data,u16 tr_no,int cnt,
							  u16 *set_poke_no,u16 *set_item_no,B_TOWER_PAREPOKE_PARAM* poke,int heapID);

//============================================================================================
/**
 *	バトルタワー ペアトレーナーデータ再生成
 *	（セーブされたAIマルチパートナーのデータをB_TOWER_PARTNER_DATA構造体に展開）
 *
 * @param[in/out]	tr_data		生成するB_TOWER_PARTNAER_DATA構造体
 * @param[in]		tr_no		生成元になるトレーナーID
 * @param[in]		fixitem		TUREなら固定アイテムを、FALSEならromアイテムをセットする
 * @param[in]		poke		ポケモンデータ再生成に必要な構造体型データへのポインタ
 * @param[in]		heapID		ヒープID
 */
//============================================================================================
GLOBAL void RomBattleTowerPartnerDataMake(BTOWER_SCRWORK* wk,B_TOWER_PARTNER_DATA *tr_data,u16 tr_no,BOOL itemfix,
		const B_TOWER_PAREPOKE_PARAM* poke,int heapID);


#endif	//__H_B_TOWER_FLD_H__
