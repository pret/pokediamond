//============================================================================================
/**
 * @file	record.c
 * @brief	ゲーム内カウント処理関連
 * @author	tamada
 * @date	2006.03.28
 */
//============================================================================================

#include "savedata/savedata_def.h"	//SAVEDATA参照のため

#include "savedata/savedata.h"

#include "savedata/record.h"


#include "gflib/assert.h"

//============================================================================================
//============================================================================================
struct RECORD{
	u32 large_rec[LARGE_REC_NUM];
	u16 small_rec[SMALL_REC_NUM];
};
#ifdef _NITRO
// 構造体が想定のサイズとなっているかチェック
SDK_COMPILER_ASSERT(sizeof(RECORD) == 332);
#endif

//============================================================================================
//
//	セーブデータシステムが依存する関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	ワークサイズ取得
 * @return	int		サイズ（バイト単位）
 */
//----------------------------------------------------------
int RECORD_GetWorkSize(void)
{
	return sizeof(RECORD);
}

//----------------------------------------------------------
/**
 * @brief	レコード初期化
 * @param	rec		レコードデータへのポインタ
 */
//----------------------------------------------------------
void RECORD_Init(RECORD * rec)
{
	MI_CpuClear32(rec, sizeof(RECORD));
}

//----------------------------------------------------------
/**
 * @brief
 * @param	sv
 * @return	RECORDへのポインタ
 */
//----------------------------------------------------------
RECORD * SaveData_GetRecord(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_RECORD);
}

//============================================================================================
//
//
//			内部関数
//
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	値の取得
 * @param	rec		RECORDへのポインタ
 * @param	id		レコード項目指定ID
 * @return	u32		現在の値
 */
//----------------------------------------------------------
static u32 get_value(const RECORD * rec, int id)
{
	if (id < LARGE_REC_MAX) {
		return rec->large_rec[id];
	} else if (id < SMALL_REC_MAX) {
		return rec->small_rec[id - LARGE_REC_MAX];
	}
	GF_ASSERT_MSG(0, "record: id error\n");
	return 0;
}

//----------------------------------------------------------
/**
 * @brief	値をセットする
 * @param	rec		RECORDへのポインタ
 * @param	id		レコード項目指定ID
 * @param	value	セットする値
 * @return	u32		現在の値
 */
//----------------------------------------------------------
static u32 set_value(RECORD * rec, int id, u32 value)
{
	if (id < LARGE_REC_MAX) {
		rec->large_rec[id] = value;
	} else if (id < SMALL_REC_MAX) {
		rec->small_rec[id - LARGE_REC_MAX] = value;
	} else {
		GF_ASSERT_MSG(0, "record: id error\n");
	}
	return get_value(rec, id);
}

//----------------------------------------------------------
/**
 * @brief	レコード項目ごとの上限を取得する
 * @param	id		レコード項目指定ID
 * @return	u32		上限の値
 */
//----------------------------------------------------------
static u32 get_limit(int id)
{
	static u8 limit[SMALL_REC_MAX] = {
		1,	//RECID_SCORE
		//4byte
		1,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,	//1-16
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	//17-32
		1,1,1,1,1,1,1,1,0,0,0,	//33-43
		//2byte
		1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,	//44-59
		0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,	//60-75
		0,0,0,0,0,0,0,0,0,1,	//76-85
	};

	if (id < LARGE_REC_MAX) {
		if(limit[id]){
			return 999999999;
		}else{
			return 999999;
		}
	} else if (id < SMALL_REC_MAX) {
		if(limit[id]){
			return 0xffff;
		}else{
			return 9999;
		}
	}
	GF_ASSERT_MSG(0, "record: id error\n");
	return 0;
}

//----------------------------------------------------------
//----------------------------------------------------------
static int get_score_number(int score_id)
{
	static const u16 num[SCOREID_MAX] = { 
		1,		//SCORE_ID_GET_NUTS					スコア：きのみを取った
		1,		//SCORE_ID_HONEY_TREE				スコア：木に蜜を塗った
		1,		//SCORE_ID_WRITE_MAIL				スコア：メールを書いた
		1,		//SCORE_ID_INTERVIEW				スコア：テレビインタビューに答えた
		1,		//SCORE_ID_WRITE_SIGN				スコア：サイン書いた
		1,		//SCORE_ID_PLAY_SLOT				スコア：スロット始めた
		2,		//SCORE_ID_CUSTOM_CAPSULE			スコア：カスタムカプセル作った
		2,		//SCORE_ID_MAKE_CLIP				スコア：クリップ作った
		2,		//SCORE_ID_WILD_BATTLE_WIN			スコア：野生エンカウント勝利
		2,		//SCORE_ID_POKE_GET_SINOU			スコア：ポケモンゲット（シンオウずかん）
		3,		//SCORE_ID_POKE_GET_WORLD			スコア：ポケモンゲット（シンオウずかん外）
		3,		//SCORE_ID_TRAINER_BATTLE_WIN		スコア：トレーナー戦勝利
		3,		//SCORE_ID_MINIGAME_NUTS			スコア：木の実料理(1人)
		7,		//SCORE_ID_CONTEST_GRANDPRIX		スコア：コンテスト優勝
		7,		//SCORE_ID_BTOWER_7WIN				スコア：バトルタワー7人勝ち抜き
		7,		//SCORE_ID_EGG_HATCHING				スコア：タマゴが孵った
		10,		//SCORE_ID_COMM_TRADE_POKE			スコア：通信交換(Wifi/ダイレクト)
		10,		//SCORE_ID_CLEAR_POKEPARK			スコア：ポケパーククリア
		11,		//SCORE_ID_COMM_MINIGAME_NUTS		スコア：木の実料理（通信）
		11,		//SCORE_ID_COMM_CONTEST_GRANDPRIX	スコア：コンテスト優勝（通信）
		11,		//SCORE_ID_COMM_RECORD_CORNER		スコア：レコードコーナー
		11,		//SCORE_ID_COMM_BATTLE_COUNT		スコア：通信対戦(Wifi/ダイレクト/ユニオン)
		20,		//SCORE_ID_ZUKAN_ENTRY				スコア：ずかん登録
		30,		//SCORE_ID_GYM_LEADER_WIN			スコア：ジムリーダーに勝った
		35,		//SCORE_ID_DENDOU					スコア：殿堂入りした
		40,		//SCORE_ID_WORLD_TRADE				スコア：世界通信交換をした
		500,	//SCORE_ID_COMMENDATION_A			スコア：表彰状Aをもらった
		10000,	//SCORE_ID_COMMENDATION_B			スコア：表彰状Bをもらった

		30,		//SCORE_ID_NEW_FLAG_TAKE_OUT		スコア：炭鉱 新しい旗持ち帰り
		30,		//SCORE_ID_FLAG_TAKE_OUT			スコア：炭鉱 旗持ち帰り
		2,		//SCORE_ID_GET_FOSSIL				スコア：炭鉱 化石発掘
		5,		//SCORE_ID_ITEM_DEPOSIT				スコア：炭鉱 相手に道具預ける
		1,		//SCORE_ID_HELLO					スコア：炭鉱 あいさつする
		1,		//SCORE_ID_QUESTION					スコア：炭鉱 質問する
		5,		//SCORE_ID_RESCUE					スコア：炭鉱 罠から助けた
		3,		//SCORE_ID_MAKE_BASE				スコア：炭鉱 基地作る
		1,		//SCORE_ID_MINE_IN					スコア：炭鉱 地下に来る
		1,		//SCORE_ID_WLAK_100					スコア：炭鉱 100歩あるく
	};
	return num[score_id];
}

//============================================================================================
//
//
//				操作関数
//
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	レコードをセットする
 * @param	rec		RECORDへのポインタ
 * @param	id		項目を指定するID
 * @param	value	セットする値
 * @return	u32		その項目の値
 */
//----------------------------------------------------------
u32 RECORD_Set(RECORD * rec, int id, u32 value)
{
	u32	limit = get_limit(id);
	
	if (value < limit) {
		return set_value(rec, id, value);
	} else {
		return set_value(rec, id, limit);
	}
}

//----------------------------------------------------------
/**
 * @brief	大きければレコードを更新する
 * @param	rec		RECORDへのポインタ
 * @param	id		項目を指定するID
 * @param	value	セットする値
 * @return	u32		その項目の値
 */
//----------------------------------------------------------
u32 RECORD_SetIfLarge(RECORD * rec, int id, u32 value)
{
	u32	limit = get_limit(id);
	u32 now = get_value(rec, id);

	if(value > limit){
		value = limit;	//上限チェック
	}
	if (now < value) {
		return set_value(rec, id, value);
	} else {
		if(now > limit){
			return set_value(rec, id, limit);
		}
		return now;
	}
}

//----------------------------------------------------------
/**
 * @brief	レコードをインクリメントする
 * @param	rec		RECORDへのポインタ
 * @param	id		項目を指定するID
 * @param	value	セットする値
 * @return	u32		その項目の値
 */
//----------------------------------------------------------
u32 RECORD_Inc(RECORD * rec, int id)
{
	u32	limit = get_limit(id);
	u32 now = get_value(rec, id);
	if (now + 1 < limit) {
		return set_value(rec, id, now + 1);
	} else {
		return set_value(rec, id, limit);
	}
}

//----------------------------------------------------------
/**
 * @brief	レコードに値を加える
 * @param	rec		RECORDへのポインタ
 * @param	id		項目を指定するID
 * @param	value	加える値
 * @return	u32		その項目の値
 */
//----------------------------------------------------------
u32 RECORD_Add(RECORD * rec, int id, u32 add_value)
{
	u32	limit = get_limit(id);
	u32 now = get_value(rec, id);
	if (now + add_value < limit) {
		return set_value(rec, id, now + add_value);
	} else {
		return set_value(rec, id, limit);
	}
}

//----------------------------------------------------------
/**
 * @brief	レコードを取得する
 * @param	rec		RECORDへのポインタ
 * @param	id		項目を指定するID
 * @return	u32		その項目の値
 */
//----------------------------------------------------------
u32 RECORD_Get(const RECORD * rec, int id)
{
	u32	limit = get_limit(id);
	u32	value = get_value(rec, id);

	if(value > limit){
		return limit;
	}else{
		return value;
	}
}

//----------------------------------------------------------
/**
 * @brief	スコアの加算
 * @param	rec		RECORDへのポインタ
 * @param	id		スコア指定のID
 */
//----------------------------------------------------------
void RECORD_Score_Add(RECORD * rec, int id)
{
	u32 score;
	
	GF_ASSERT(id < SCOREID_MAX);
	
	//カンストチェックする
	score = RECORD_Get(rec, RECID_SCORE);
	if ( score+get_score_number(id) > SCORE_MAX ){
		RECORD_Set(rec, RECID_SCORE, SCORE_MAX);
	}else{
		RECORD_Add(rec, RECID_SCORE, get_score_number(id));
	}
}


//----------------------------------------------------------
/**
 * @brief	スコアの取得
 * @param	rec		RECORDへのポインタ
 * @return	u32		現在のスコア
 */
//----------------------------------------------------------
u32 RECORD_Score_Get(const RECORD * rec)
{
	return RECORD_Get(rec, RECID_SCORE);
}

//----------------------------------------------------------
/**
 * @brief	図鑑スコアの加算
 * @param	rec		RECORDへのポインタ
 * @param	zw		ずかんワークへのポインタ
 * @param	monsno	ポケモンナンバー
 */
//----------------------------------------------------------
void RECORD_Score_AddZukanScore(RECORD * rec, const ZUKAN_WORK * zw, u16 const inMonsno)
{
	if ( !ZukanWork_GetPokeGetFlag(zw, inMonsno) ){
		RECORD_Score_Add(rec, SCORE_ID_ZUKAN_ENTRY);
	}
}

#ifdef PM_DEBUG
//----------------------------------------------------------
/**
 * @brief	スコアのセット
 * @param	rec		RECORDへのポインタ
 * @param	inScore	セットするスコア
 */
//----------------------------------------------------------
void RECORD_Score_DebugSet(RECORD * rec, const u32 inScore)
{
	u32 score;

	score = inScore;
	
	//カンストチェックする
	if ( score > SCORE_MAX ){
		score = SCORE_MAX;
	}

	RECORD_Set(rec, RECID_SCORE, score);
}

#endif	//PM_DEBUG


