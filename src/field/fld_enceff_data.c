//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		fld_encount_data.c
 *	@brief		フィールドエンカウントデータ
 *	@author		tomoya takahashi
 *	@data		2006.06.08
 *	
 *	バトルパラメータから
 *	エンカウントエフェクト　BGMをけっていするルーチン
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"

#include "fieldsys.h"

#include "encount_effect.h"
#include "ev_pokemon.h"
#include "poketool/poke_tool.h"
#include "poketool/tr_tool.h"
#include "poketool/monsno.h"

#include "battle/trtype_def.h"

#include "system/snd_tool.h"
#include "field/fld_bgm.h"

#define __FIELD_ENCEFF_DATA_H_GLOBAL
#include "fld_enceff_data.h"

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
//-------------------------------------
//	特殊エンカウントタイプ定数
//
//	通常エンカウント
//		フィールド、トレーナー以外の
//		独自のエフェクト音を使用するエフェクト
//=====================================
enum{
	// GYM
	FLD_ENCEFF_SP_GYM_KUROGANE,			// クロガネジム
	FLD_ENCEFF_SP_GYM_HAKUTAI,			// ハクタイジム
	FLD_ENCEFF_SP_GYM_NOMOSE,			// ノモセジム
	FLD_ENCEFF_SP_GYM_TOBARI,			// トバリジム
	FLD_ENCEFF_SP_GYM_YOSUGA,			// ヨスガトジム
	FLD_ENCEFF_SP_GYM_KISSAKI,			// キッサキジム
	FLD_ENCEFF_SP_GYM_MIO,				// ミオジム
	FLD_ENCEFF_SP_GYM_NAGISA,			// ナギサジム
	// 四天王
	FLD_ENCEFF_SP_BIGFOUR_00,
	FLD_ENCEFF_SP_BIGFOUR_01,
	FLD_ENCEFF_SP_BIGFOUR_02,
	FLD_ENCEFF_SP_BIGFOUR_03,
	// チャンピオン
	FLD_ENCEFF_SP_CHANPION,
	// ライバル
	FLD_ENCEFF_SP_RIVAL,
	// 特殊ポケモン
	FLD_ENCEFF_SP_LEGEND_POKE00,	// シェイミ
	FLD_ENCEFF_SP_PACKAGE_POKE00,	// イア、エア
	FLD_ENCEFF_SP_REIHAI_POKE00,	// レイ　ハイ
	FLD_ENCEFF_SP_AI_POKE00,		// アイ
	FLD_ENCEFF_SP_ARUSEUSU,			// アルセウス
	FLD_ENCEFF_SP_LEGEND_POKE01,	// ﾚｼﾞｷﾞｶﾞｽ、ヒードラン、キマイラン、ダーくらい
	FLD_ENCEFF_SP_LEGEND_POKE02,	// クレセリア
	
	// 銀河団
	FLD_ENCEFF_SP_GINGA_NORMAL,		// 通常メンバー
	FLD_ENCEFF_SP_GINGA_SPECIAL,	// 幹部クラス
	FLD_ENCEFF_SP_GINGA_BOSU,	// ボス
	// その他特殊バトル
	FLD_ENCEFF_SP_BATTLE_TOWER,		// バトルタワー
	FLD_ENCEFF_SP_BATTLE_COMMU,		// 通信バトル
	FLD_ENCEFF_SP_BATTLE_DOUBLE,		// ダブルバトルトレーナー
	FLD_ENCEFF_SP_BATTLE_DOUBLE_YASEI,	// ダブルバトルやせい
	FLD_ENCEFF_SP_BATTLE_TOWER_TAIKUUN,	// タワータイクーン

	// ノーマル	
	FLD_ENCEFF_SP_NORMAL_TRAINER,	// トレーナー
	FLD_ENCEFF_SP_NORMAL_FIELD,		// 野生

	FLD_ENCEFF_SP_MAX,	// 特殊エンカウント数
};



//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	特殊エンカウントデータワーク
//=====================================
typedef struct {
	u16 effect_no;
	u16 bgm_no;
} FLD_ENCEFF_SP_DATA;


//-----------------------------------------------------------------------------
/**
 *		特殊エンカウントエフェクトテーブル
 *			【特殊エンカウントタイプ定数】のならびに
 *			あわせる必要があります。
*/
//-----------------------------------------------------------------------------
// エンカウントエフェクトをバトルパラメータからSEARCHする
#define ENCOUNT_EFFECT_SEARCH	( 0xffff )


static const FLD_ENCEFF_SP_DATA FLD_EncEffSpData[ FLD_ENCEFF_SP_MAX ] = {
	// GYM
	{ ENCOUNT_SPTR_KUROGANE_GYM,	SEQ_BA_GYM },	// クロガネジム
	{ ENCOUNT_SPTR_HAKUTAI_GYM,		SEQ_BA_GYM },	// ハクタイジム
	{ ENCOUNT_SPTR_NOMOSE_GYM,		SEQ_BA_GYM },	// ノモセジム
	{ ENCOUNT_SPTR_TOBARI_GYM,		SEQ_BA_GYM },	// トバリジム
	{ ENCOUNT_SPTR_YOSUGA_GYM,		SEQ_BA_GYM },	// ヨスガトジム
	{ ENCOUNT_SPTR_KISSAKI_GYM,		SEQ_BA_GYM },	// キッサキジム
	{ ENCOUNT_SPTR_MIO_GYM,			SEQ_BA_GYM },	// ミオジム
	{ ENCOUNT_SPTR_NAGISA_GYM,		SEQ_BA_GYM },	// ナギサジム
	// 四天王
	{ ENCOUNT_SPTR_SITEN_00,	SEQ_BA_TENNO },
	{ ENCOUNT_SPTR_SITEN_01,	SEQ_BA_TENNO },
	{ ENCOUNT_SPTR_SITEN_02,	SEQ_BA_TENNO },
	{ ENCOUNT_SPTR_SITEN_03,	SEQ_BA_TENNO },
	// チャンピオン
	{ ENCOUNT_SPTR_CHANPION,	SEQ_BA_CHANP },
	// ライバル
	{ ENCOUNT_EFFECT_SEARCH,	SEQ_BA_RIVAL },
	// 特殊ポケモン
	{ ENCOUNT_LEGEND_NORMAL,	SEQ_BA_POKE },	// シェイミ
	{ ENCOUNT_LEGEND_PACKAGE,	SEQ_BA_DPOKE2 },	// イア、エア
	{ ENCOUNT_LEGEND_PACKAGE,	SEQ_BA_DPOKE1 },	// レイ　ハイ　
	{ ENCOUNT_EFFECT_SEARCH,	SEQ_BA_DPOKE1 },	// アイ
	{ ENCOUNT_LEGEND_PACKAGE,	SEQ_BA_SECRET1 },	// アルセウス
	{ ENCOUNT_LEGEND_NORMAL,	SEQ_BA_SECRET2 },	// レジギガス、ヒードラン、キマイラン
	{ ENCOUNT_EFFECT_SEARCH,	SEQ_BA_POKE },	// クレセリア

	// 銀河団
	{ ENCOUNT_GINGA_NORMAL,		SEQ_BA_GINGA },	// 通常メンバー
	{ ENCOUNT_GINGA_SPECIAL,	SEQ_BA_GINGA3},	// 幹部クラス
	{ ENCOUNT_GINGA_SPECIAL,	SEQ_BA_AKAGI },	// ボス
	// その他特殊バトル
	{ ENCOUNT_SPECIAL_TOWER,	SEQ_BA_TRAIN },	// バトルタワー
	{ ENCOUNT_SPECIAL_TOWER,	SEQ_BA_TRAIN },	// 通信バトル
	{ ENCOUNT_SPECIAL_DOUBLE,	SEQ_BA_TRAIN },	// ダブルバトル
	{ ENCOUNT_SPECIAL_DOUBLE,	SEQ_BA_POKE },	// ダブルバトルやせい
	{ ENCOUNT_SPECIAL_TOWER,	SEQ_BA_CHANP },	// バトルタワータイクーン
	// ノーマル
	{ ENCOUNT_EFFECT_SEARCH,	SEQ_BA_TRAIN },	// トレーナー
	{ ENCOUNT_EFFECT_SEARCH,	SEQ_BA_POKE },	// 野生

//	{ エフェクト,BGM },	
};


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static u32 FLD_EncEffSpDataTypeGetTrainer( u32 tr_type );
static u32 FLD_EncEffSpDataTypeGetPokemon( POKEPARTY* p_poke_party );

static u32 FLD_EncEffSpDataTypeGet( const BATTLE_PARAM* p_bp );
static u32 FLD_EncEffSpDataEffectNoGet( u32 type, const BATTLE_PARAM* p_bp );
static u32 FLD_EncEffSpDataBgmNoGet( u32 type, const BATTLE_PARAM* p_bp );




//----------------------------------------------------------------------------
/**
 *	@brief	特殊エンカウントタイプ　取得
 *	
 *	@param	BATTLE_PARAM* p_bp 
 *	@retval	特殊エンカウントテーブル
 *	@retval	FLD_ENCEFF_SP_MAX	特殊テーブルにない
 *
 *	* 優先順位
 *		特殊トレーナー
 *		特殊ポケモンは　バトルタワー　通信　ダブルでは
 *		出てこないと考えて作成
 */
//-----------------------------------------------------------------------------
static u32 FLD_EncEffSpDataTypeGet( const BATTLE_PARAM* p_bp )
{
	u32 fight_type = p_bp->fight_type;
	u32 trainer_sp;
	u32 mons_sp;
	

	// トレーナー戦チェック
	if( (fight_type & FIGHT_TYPE_TRAINER) ){

		// トレーナーチェック
		trainer_sp = FLD_EncEffSpDataTypeGetTrainer( p_bp->trainer_data[ CLIENT_NO_ENEMY ].tr_type );

		// バトルタワーは、特殊トレーナーIDなので
		// 先に判断する
		if( fight_type & FIGHT_TYPE_TOWER ){

			// タワータイクーンを最優先
			if( trainer_sp == FLD_ENCEFF_SP_BATTLE_TOWER_TAIKUUN ){
				return trainer_sp;
			}

			// ダブルバトルチェック
			if( fight_type & FIGHT_TYPE_2vs2 ){
				return FLD_ENCEFF_SP_BATTLE_DOUBLE;
			}
			return FLD_ENCEFF_SP_BATTLE_TOWER;
		}

		// 銀河団を優先する
		if( (trainer_sp == FLD_ENCEFF_SP_GINGA_NORMAL) || 
			(trainer_sp == FLD_ENCEFF_SP_GINGA_SPECIAL) ||
			(trainer_sp == FLD_ENCEFF_SP_GINGA_BOSU) ){
			return trainer_sp;
		}

		// ダブルバトルチェック
		if( fight_type & FIGHT_TYPE_2vs2 ){
			return FLD_ENCEFF_SP_BATTLE_DOUBLE;
		}

		// 通信バトルチェック
		if( fight_type & FIGHT_TYPE_SIO ){
			return FLD_ENCEFF_SP_BATTLE_COMMU;
		}

		return trainer_sp;
	}

	// 特殊ポケモンチェック
	mons_sp = FLD_EncEffSpDataTypeGetPokemon( p_bp->poke_party[ CLIENT_NO_ENEMY ] );

	// フィールド以下の特殊ポケモンなら返す
	if( mons_sp < FLD_ENCEFF_SP_NORMAL_FIELD ){
		return mons_sp;
	}

	// ダブルバトルチェック
	if( fight_type & FIGHT_TYPE_2vs2 ){
		return FLD_ENCEFF_SP_BATTLE_DOUBLE_YASEI;
	}

	// 野生
	return mons_sp;
}


//----------------------------------------------------------------------------
/**
 *	@brief	エンカウントエフェクトナンバーの取得
 *	@param	type	【特殊エンカウントタイプ定数】
 *	@param	p_bp	バトルパラメータ
 *	@return	エンカウントエフェクトナンバー
 */
//-----------------------------------------------------------------------------
static u32 FLD_EncEffSpDataEffectNoGet( u32 type, const BATTLE_PARAM* p_bp )
{
	GF_ASSERT( type < FLD_ENCEFF_SP_MAX );
	
	if( FLD_EncEffSpData[ type ].effect_no == ENCOUNT_EFFECT_SEARCH ){
		// レベル差などを見て決める
		return ENCEFF_GetEffectNo( p_bp );
	}else{

		return FLD_EncEffSpData[ type ].effect_no;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	BGMナンバーの取得
 *	@param	type	【特殊エンカウントタイプ定数】
 *	@param	p_bp	バトルパラメータ
 *	@return	BGMナンバー
 */
//-----------------------------------------------------------------------------
static u32 FLD_EncEffSpDataBgmNoGet( u32 type, const BATTLE_PARAM* p_bp )
{
	GF_ASSERT( type < FLD_ENCEFF_SP_MAX );
	return FLD_EncEffSpData[ type ].bgm_no;
}

//----------------------------------------------------------------------------
/**
 *	[type の取得は内部で行う]
 *	@brief	エンカウントエフェクトナンバーの取得
 *	@param	p_bp	バトルパラメータ
 *	@return	エンカウントエフェクトナンバー
 */
//-----------------------------------------------------------------------------
u32 FLD_EncEffSpDataEffectNoPackGet( const BATTLE_PARAM* p_bp )
{
	u32 type;
	type = FLD_EncEffSpDataTypeGet( p_bp );
	return FLD_EncEffSpDataEffectNoGet( type, p_bp );
}

//----------------------------------------------------------------------------
/**
 *	[type の取得は内部で行う]
 *	@brief	BGMナンバーの取得
 *	@param	p_bp	バトルパラメータ
 *	@return	BGMナンバー
 */
//-----------------------------------------------------------------------------
u32 FLD_EncEffSpDataBgmNoPackGet( const BATTLE_PARAM* p_bp )
{
	u32 type;
	type = FLD_EncEffSpDataTypeGet( p_bp );
	return FLD_EncEffSpDataBgmNoGet( type, p_bp );
}



//-----------------------------------------------------------------------------
/**
 *			プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	エンカウントエフェクトデータ取得
 *
 *	@param	p_data		データ格納先
 *	@param	type		【特殊エンカウントタイプ定数】
 */
//-----------------------------------------------------------------------------
static void FLD_EncEffSpDataGet( FLD_ENCEFF_SP_DATA* p_data, u32 type )
{
	// タイプが不正
	GF_ASSERT( type < FLD_ENCEFF_SP_MAX );
	*p_data = FLD_EncEffSpData[ type ];
}


//----------------------------------------------------------------------------
/**
 *	@brief	特殊トレーナーからエンカウントタイプ選出
 *
 *	@param	tr_type	トレーナーTYPE
 *
 *	@retval	特殊エンカウントテーブル
 *	@retval	FLD_ENCEFF_SP_MAX	特殊テーブルにない
 */
//-----------------------------------------------------------------------------
static u32 FLD_EncEffSpDataTypeGetTrainer( u32 tr_type )
{
	u32 retval = FLD_ENCEFF_SP_NORMAL_TRAINER;
	
	
	// tr_typeがきちんと連番で並んでいないので
	// 全部caseでとる必要がある
	switch( tr_type ){
	// GYM
	case TRTYPE_LEADER1:		// クロガネジム
		retval = FLD_ENCEFF_SP_GYM_KUROGANE;
		break;
	case TRTYPE_LEADER2:		// ハクタイジム
		retval = FLD_ENCEFF_SP_GYM_HAKUTAI;
		break;
	case TRTYPE_LEADER3:		// ノモセジム
		retval = FLD_ENCEFF_SP_GYM_NOMOSE;
		break;
	case TRTYPE_LEADER4:		// トバリジム
		retval = FLD_ENCEFF_SP_GYM_TOBARI;
		break;
	case TRTYPE_LEADER5:		// ヨスガトジム
		retval = FLD_ENCEFF_SP_GYM_YOSUGA;
		break;
	case TRTYPE_LEADER6:		// キッサキジム
		retval = FLD_ENCEFF_SP_GYM_KISSAKI;
		break;
	case TRTYPE_LEADER7:		// ミオジム
		retval = FLD_ENCEFF_SP_GYM_MIO;
		break;
	case TRTYPE_LEADER8:		// ナギサジム
		retval = FLD_ENCEFF_SP_GYM_NAGISA;
		break;
		
	// 四天王
	case TRTYPE_BIGFOUR1:
		retval = FLD_ENCEFF_SP_BIGFOUR_00;
		break;
	case TRTYPE_BIGFOUR2:
		retval = FLD_ENCEFF_SP_BIGFOUR_01;
		break;
	case TRTYPE_BIGFOUR3:
		retval = FLD_ENCEFF_SP_BIGFOUR_02;
		break;
	case TRTYPE_BIGFOUR4:
		retval = FLD_ENCEFF_SP_BIGFOUR_03;
		break;
		
	// チャンピオン
	case TRTYPE_CHAMPION:
		retval = FLD_ENCEFF_SP_CHANPION;
		break;

	// ライバル
	case TRTYPE_RIVAL:
		retval = FLD_ENCEFF_SP_RIVAL;
		break;
		
	// 銀河団
	case TRTYPE_GINGALBOSS:
		retval = FLD_ENCEFF_SP_GINGA_BOSU;
		break;
		
	case TRTYPE_GINGALEADER1:
	case TRTYPE_GINGALEADER2:
	case TRTYPE_GINGALEADER3:
		retval = FLD_ENCEFF_SP_GINGA_SPECIAL;
		break;
	case TRTYPE_GINGAM:
	case TRTYPE_GINGAW:
		retval = FLD_ENCEFF_SP_GINGA_NORMAL;
		break;

	// バトルタワー
	case TRTYPE_KUROTUGU:
		retval = FLD_ENCEFF_SP_BATTLE_TOWER_TAIKUUN;
		break;

	default:
		break;
	}

	return retval;
}

//----------------------------------------------------------------------------
/**
 *	@brief	特殊ポケモン　チェック
 *
 *	@param	p_poke_party	ポケモンパーティ
 *
 *	@retval	特殊エンカウントテーブル
 *	@retval	FLD_ENCEFF_SP_MAX	特殊テーブルにない
 */
//-----------------------------------------------------------------------------
static u32 FLD_EncEffSpDataTypeGetPokemon( POKEPARTY* p_poke_party )
{
	POKEMON_PARAM* p_enemy_poke;
	u32 monsno;
	u32 retval = FLD_ENCEFF_SP_NORMAL_FIELD;

	// ポケモンパラメータ取得
	p_enemy_poke = EvPoke_GetLivingPokemonTop( p_poke_party );
	monsno = PokeParaGet( p_enemy_poke, ID_PARA_monsno, NULL );

	switch( monsno ){
	case MONSNO_EURISU:	// シェイミ、
		retval = FLD_ENCEFF_SP_LEGEND_POKE00;
		break;

	case MONSNO_MUUBASU:	// クレセリア
		retval = FLD_ENCEFF_SP_LEGEND_POKE02;
		break;

		
	case MONSNO_REZIKINGU:	// レジギガス　ヒードラン　キマイラン　ダークライ
	case MONSNO_KIMAIRAN:
	case MONSNO_HIIDORAN:
	case MONSNO_DAAKU:
	case MONSNO_PURAZUMA:
		retval = FLD_ENCEFF_SP_LEGEND_POKE01;
		break;
		
	case MONSNO_AI:	// アイ
		retval = FLD_ENCEFF_SP_AI_POKE00;
		break;

	case MONSNO_REI:	// レイ　ハイ
	case MONSNO_HAI:
		retval = FLD_ENCEFF_SP_REIHAI_POKE00;
		break;
		
	case MONSNO_IA:	// イア、エア、アウス
	case MONSNO_EA:
		retval = FLD_ENCEFF_SP_PACKAGE_POKE00;
		break;

	case MONSNO_AUSU:	// アルセウス
		retval = FLD_ENCEFF_SP_ARUSEUSU;
		break;

	default:
		break;
	}
	return retval;
}
