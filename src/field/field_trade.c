//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_trade.c
 *	@brief		ゲーム内交換
 *	@author		tomoya takahashi
 *	@data		2006.05.15
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "system/arc_util.h"
#include "include/msgdata/msg_fld_trade.h"
#include "include/msgdata/msg.naix"
#include "include/gflib/strbuf_family.h"
#include "fieldsys.h"
#include "field_event.h"
#include "ev_mapchange.h"
#include "ev_time.h"
#include "savedata/zukanwork.h"
#include "savedata/get_poke.h"
#include "include/poketool/poke_memo.h"
#include "zonedata.h"

#define  __FIELD_TRADE_H_GLOBAL
#include "field_trade.h"

//-----------------------------------------------------------------------------
/**
 *					コーディング規約
 *		●関数名
 *				１文字目は大文字それ以降は小文字にする
 *		●変数名
 *				・変数共通
 *						constには c_ を付ける
 *						staticには s_ を付ける
 *						ポインタには p_ を付ける
 *						全て合わさると csp_ となる
 *				・グローバル変数
 *						１文字目は大文字
 *				・関数内変数
 *						小文字と”＿”と数字を使用する 関数の引数もこれと同じ
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define FLD_TRADE_GET_POKE_GMM(x)	(x)
#define FLD_TRADE_GET_OYA_GMM(x)	(TRADE_OYA_00+x)


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	交換ポケモンデータ
//=====================================
typedef struct {
	u32 monsno;			// モンスターナンバー
	u32 hp_rnd;			// HP乱数
	u32 at_rnd;			// 攻撃乱数
	u32 df_rnd;			// 防御乱数
	u32 sp_rnd;			// 速さ乱数
	u32 sa_rnd;			// 特攻乱数
	u32 sd_rnd;			// 特防乱数
	u32 speabino;		// 特殊能力
	u32	mons_id;		// ID
	u32 style;			// かっこよさ
	u32 beautiful;		// うつくしさ
	u32 cute;			// かわいさ
	u32 clever;			// かしこさ
	u32 strong;			// たくましさ
	u32 mons_rnd;		// 固体乱数
	u32 item;			// アイテム
	u32 oya_sex;		// 親性別
	u32 fur;			// 毛艶
	u32 world_code;		// 親の国コード
	u32 change_monsno;	// 交換するモンスターナンバー
} FLD_TRADE_POKEDATA;


typedef struct _FLD_TRADE_WORK {
	FLD_TRADE_POKEDATA* p_pokedata;		// 交換ポケモンデータ

	POKEMON_PARAM*		p_pp;			// 交換ポケモン
	MYSTATUS*			p_myste;		// 交換相手パラメータ
	u32 trade_no;						// 交換ナンバー
	u32 heapID;
};

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static STRBUF* FLD_TradeGetGmm( u32 heapID, u32 idx );
static void FLD_TradeSetPokeParam( POKEMON_PARAM* p_pp, FLD_TRADE_POKEDATA* p_data, u32 lev, u32 trade_no, u32 heapID, u32 zone_id );



//----------------------------------------------------------------------------
/**
 *	@brief	ワーク確保
 *
 *	@param	heapID		ヒープID
 *	@param	trade_no	交換番号
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
FLD_TRADE_WORK* FLD_TradeAlloc( u32 heapID, u32 trade_no )
{
	FLD_TRADE_WORK* p_work;
	STRBUF* str;
	STRCODE str_arry[ 128 ];

	GF_ASSERT( trade_no < FLD_TRADE_NUM );
	
	p_work = sys_AllocMemory( heapID, sizeof(FLD_TRADE_WORK) );
	memset( p_work, 0, sizeof(FLD_TRADE_WORK) );

	// 交換データ読み込み
	p_work->p_pokedata = ArcUtil_Load( ARC_FIELD_TRADE_POKE, trade_no, FALSE, heapID, ALLOC_TOP );

	
	p_work->heapID = heapID;
	p_work->trade_no = trade_no;

	// 交換ポケモンデータ作成
	p_work->p_pp = PokemonParam_AllocWork( heapID );

	// 親データ作成
	p_work->p_myste = MyStatus_AllocWork( heapID );
	MyStatus_Init( p_work->p_myste );
	str = FLD_TradeGetGmm( heapID, FLD_TRADE_GET_OYA_GMM( trade_no ) );
	STRBUF_GetStringCode( str, str_arry, 128 );
	STRBUF_Delete(str);
	MyStatus_SetMyName( p_work->p_myste, str_arry );
	MyStatus_SetMySex( p_work->p_myste, p_work->p_pokedata->oya_sex );
	
	return p_work;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワーク破棄
 *
 *	@param	p_work		
 */
//-----------------------------------------------------------------------------
void FLD_TradeDelete( FLD_TRADE_WORK* p_work )
{
	sys_FreeMemoryEz( p_work->p_pokedata );
	sys_FreeMemoryEz( p_work->p_pp );
	sys_FreeMemoryEz( p_work->p_myste );
	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *	@brief	交換するポケモンナンバー取得
 *
 *	@param	cp_work		ワーク
 *
 *	@return	ポケモンナンバー
 */
//-----------------------------------------------------------------------------
u32 FLD_TradeMonsno( const FLD_TRADE_WORK* cp_work )
{
	return cp_work->p_pokedata->monsno;
}

//----------------------------------------------------------------------------
/**
 *	@brief	交換に必要なポケモンナンバー取得
 *
 *	@param	cp_work		ワーク
 *
 *	@return	ポケモンナンバー
 */
//-----------------------------------------------------------------------------
u32 FLD_TradeChangeMonsno( const FLD_TRADE_WORK* cp_work )
{
	return cp_work->p_pokedata->change_monsno;
}

//----------------------------------------------------------------------------
/**
 *	@brief	親性別　取得
 *
 *	@param	cp_work		ワーク
 *
 *	@return	性別
 */
//-----------------------------------------------------------------------------
u32 FLD_TradeOyaSex( const FLD_TRADE_WORK* cp_work )
{
	return cp_work->p_pokedata->oya_sex;
}

//----------------------------------------------------------------------------
/**
 *	@brief	交換
 *
 *	@param	p_fsys		フィールドシステム
 *	@param	p_work		交換ワーク
 *	@param	party_pos	パーティーポジション
 */
//-----------------------------------------------------------------------------
void FLD_Trade( FIELDSYS_WORK * p_fsys, FLD_TRADE_WORK* p_work, int party_pos )
{
	POKEPARTY * party = SaveData_GetTemotiPokemon( p_fsys->savedata );

	// 交換実行
	PokeParty_SetMemberData( party, party_pos, p_work->p_pp );

	// 図鑑に登録
	SaveData_GetPokeRegister( p_fsys->savedata, p_work->p_pp );
}

void FLD_TradeDemoDataMake( FIELDSYS_WORK * p_fsys, FLD_TRADE_WORK* p_work, int party_pos, DEMO_TRADE_PARAM* p_demo, POKEMON_PARAM* sendPoke, POKEMON_PARAM* recvPoke )
{
	POKEPARTY * party = SaveData_GetTemotiPokemon( p_fsys->savedata );
	POKEMON_PARAM* p_chg_poke;
	STRBUF* str;
	u32 lev;		// レベル
	int time_zone;

	// 交換するポケモン
	p_chg_poke = PokeParty_GetMemberPointer( party, party_pos );
	lev = PokeParaGet( p_chg_poke, ID_PARA_level, NULL );
	
	// 交換ポケモンの作成
	FLD_TradeSetPokeParam( p_work->p_pp, p_work->p_pokedata, lev, p_work->trade_no, p_work->heapID, p_fsys->location->zone_id );

	// デモ用のポケモンパラメータに格納
	PokeCopyPPtoPP( p_chg_poke, sendPoke );
	PokeCopyPPtoPP( p_work->p_pp, recvPoke );

	// デモデータ作成
	p_demo->sendPoke	= PPPPointerGet( sendPoke );
	p_demo->recvPoke	= PPPPointerGet( recvPoke );
	p_demo->partner	= p_work->p_myste;
	p_demo->seqFlag	= DEMO_TRADE_SEQ_FULL;
	p_demo->config		= SaveData_GetConfig( p_fsys->savedata );
	time_zone = EVTIME_GetTimeZone( p_fsys );
	if( (time_zone == TIMEZONE_MORNING) || 
		(time_zone == TIMEZONE_NOON) ){
		p_demo->bgType		= DEMO_TRADE_BGTYPE_MORNING;
	}else if( time_zone == TIMEZONE_EVENING ){
		p_demo->bgType		= DEMO_TRADE_BGTYPE_EVENING;
	}else{
		p_demo->bgType		= DEMO_TRADE_BGTYPE_NIGHT;
	}
}




//----------------------------------------------------------------------------
/**
 *	@brief	メッセージ取得
 *	破棄が必要
 */
//-----------------------------------------------------------------------------
static STRBUF* FLD_TradeGetGmm( u32 heapID, u32 idx )
{
	STRBUF* str;
	
	MSGDATA_MANAGER* msg_data = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_fld_trade_dat, heapID);
	str = MSGMAN_AllocString(msg_data, idx);
	MSGMAN_Delete(msg_data);
	return str;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンパラムにデータの設定
 *
 *	@param	p_pp		ポケモンパラム
 *	@param	p_data		データ
 *	@param	lev			レベル
 *	@param	trade_no	tradeナンバー
 */
//-----------------------------------------------------------------------------
static void FLD_TradeSetPokeParam( POKEMON_PARAM* p_pp, FLD_TRADE_POKEDATA* p_data, u32 lev, u32 trade_no, u32 heapID, u32 zone_id )
{
	STRBUF* str;
	u8 nickname_flg;
	u32 placeid;

	
	// モンスターナンバー　レベル　固体乱数　ID設定
	PokeParaSet( p_pp, 
			p_data->monsno,
			lev, POW_RND, 
			RND_SET, p_data->mons_rnd,
			ID_SET, p_data->mons_id );

	// ニックネーム
	str = FLD_TradeGetGmm( heapID, FLD_TRADE_GET_POKE_GMM(trade_no) );
	PokeParaPut( p_pp, ID_PARA_nickname_buf, str );
	STRBUF_Delete(str);

	// ニックネームフラグ
	nickname_flg = 1;
	PokeParaPut( p_pp, ID_PARA_nickname_flag, &nickname_flg );

	// 各種乱数設定
	PokeParaPut( p_pp, ID_PARA_hp_rnd, &p_data->hp_rnd );
	PokeParaPut( p_pp, ID_PARA_pow_rnd, &p_data->at_rnd );
	PokeParaPut( p_pp, ID_PARA_def_rnd, &p_data->df_rnd );
	PokeParaPut( p_pp, ID_PARA_agi_rnd, &p_data->sp_rnd );
	PokeParaPut( p_pp, ID_PARA_spepow_rnd, &p_data->sa_rnd );
	PokeParaPut( p_pp, ID_PARA_spedef_rnd, &p_data->sd_rnd );

	// 特性
//	PokeParaPut( p_pp, ID_PARA_speabino, &p_data->speabino );

	// かっこよさなど
	PokeParaPut( p_pp, ID_PARA_style, &p_data->style );
	PokeParaPut( p_pp, ID_PARA_beautiful, &p_data->beautiful );
	PokeParaPut( p_pp, ID_PARA_cute, &p_data->cute );
	PokeParaPut( p_pp, ID_PARA_clever, &p_data->clever );
	PokeParaPut( p_pp, ID_PARA_strong, &p_data->strong );
	
	// アイテム
	PokeParaPut( p_pp, ID_PARA_item, &p_data->item );

	// 親の名前
	str = FLD_TradeGetGmm( heapID, FLD_TRADE_GET_OYA_GMM(trade_no) );
	PokeParaPut( p_pp, ID_PARA_oyaname_buf, str );
	STRBUF_Delete(str);

	// 親の性別	
	PokeParaPut( p_pp, ID_PARA_oyasex, &p_data->oya_sex );

	// 国コード
	PokeParaPut( p_pp, ID_PARA_country_code, &p_data->world_code );

	// トレーナーメモ設定
	placeid = ZoneData_GetPlaceNameID( zone_id );
	TrainerMemoSetPP( p_pp, NULL, TRMEMO_OFFTRADE_PLACESET, placeid, heapID );

	// 計算しなおし
	PokeParaCalc( p_pp );

	// レアにならないようにする
	GF_ASSERT( PokeRareGet( p_pp ) == FALSE );
}
