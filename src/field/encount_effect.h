//=============================================================================
/**
 * @file	encount.h	
 * @brief	エンカウントエフェクト
 * @author	GAME FREAK inc.
 */
//=============================================================================

#ifndef	__ENCOUNT_EFFECT_H__
#define	__ENCOUNT_EFFECT_H__

#include "battle/battle_common.h"

#undef GLOBAL
#ifdef __ENCOUNT_EFFECT_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif

//-------------------------------------
//	
//	エンカウントエフェクトNo
//
//	計算式で野生戦とトレーナー戦は、
//	エンカウントを決めているため、
//	野生と、トレーナーのエフェクト順番を変えることは禁止
//=====================================
enum{
	// フィールド
	ENCOUNT_FIELD_GRASS_LEVEL_LOW,	// 草　レベル低い
	ENCOUNT_FIELD_GRASS_LEVEL_HIGH,	// 草　レベル高い
	ENCOUNT_FIELD_WATER_LEVEL_LOW,	// 水　レベル低い
	ENCOUNT_FIELD_WATER_LEVEL_HIGH,	// 水　レベル高い
	ENCOUNT_FIELD_DAN_LEVEL_LOW,	// ダンジョン　レベル低い
	ENCOUNT_FIELD_DAN_LEVEL_HIGH,	// ダンジョン　レベル高い

	// トレーナー
	ENCOUNT_TRAINER_GRASS_LEVEL_LOW,	// 草　レベル低い
	ENCOUNT_TRAINER_GRASS_LEVEL_HIGH,	// 草　レベル高い
	ENCOUNT_TRAINER_WATER_LEVEL_LOW,	// 水　レベル低
	ENCOUNT_TRAINER_WATER_LEVEL_HIGH,	// 水　レベル高い
	ENCOUNT_TRAINER_DAN_LEVEL_LOW,		// ダン　レベル低
	ENCOUNT_TRAINER_DAN_LEVEL_HIGH,		// ダン　レベル高い

	// ジム　
	ENCOUNT_SPTR_KUROGANE_GYM,		// クロガネジム
	ENCOUNT_SPTR_HAKUTAI_GYM,		// ハクタイジム
	ENCOUNT_SPTR_NOMOSE_GYM,		// ノモセジム
	ENCOUNT_SPTR_TOBARI_GYM,		// トバリジム
	ENCOUNT_SPTR_YOSUGA_GYM,		// ヨスガトジム
	ENCOUNT_SPTR_KISSAKI_GYM,		// キッサキジム
	ENCOUNT_SPTR_MIO_GYM,			// ミオジム
	ENCOUNT_SPTR_NAGISA_GYM,		// ナギサジム
	
	// 四天王
	ENCOUNT_SPTR_SITEN_00,
	ENCOUNT_SPTR_SITEN_01,
	ENCOUNT_SPTR_SITEN_02,
	ENCOUNT_SPTR_SITEN_03,
	
	// チャンピオン
	ENCOUNT_SPTR_CHANPION,
	
	// 伝説　パッケージ
	ENCOUNT_LEGEND_NORMAL,		// 伝説ポケモン
	ENCOUNT_LEGEND_PACKAGE,		// PACKAGEポケモン
	
	// 銀河団
	ENCOUNT_GINGA_NORMAL,		// 銀河団通常
	ENCOUNT_GINGA_SPECIAL,		// 銀河団幹部

	// 特殊
	ENCOUNT_SPECIAL_TOWER,		// バトルタワー　フロント
	ENCOUNT_SPECIAL_DOUBLE,		// ダブルバトル

/*	ENCOUNT_MOTIONBL00,		// モーションブラーエフェクト回転
	ENCOUNT_MOTIONBL01,		// モーションブラーエフェクト横揺れ//*/
	ENCOUNT_NUM

};
#define ENCOUNT_MAIN_NONE	(ENCOUNT_NUM)	// 引き継ぐエンカウントがないときに指定


//----------------------------------------------------------------------------
/**
 *
 *@brief	エンカウントエフェクト開始
 *
 *@param	No		エンカウントエフェクトNO
 *@param	*fsw	フィールドシステムワークのポインタ
 *@param	end		終了チェック用　TRUE：終了した 
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void EncountEffectStart(int No, FIELDSYS_WORK *fsw, BOOL* end );


//-----------------------------------------------------------------------------
/**
 *		バトルパラメータから
 *		対応するエンカウントエフェクトナンバーを返す
 */
//-----------------------------------------------------------------------------
GLOBAL u32 ENCEFF_GetEffectNo( const BATTLE_PARAM * p_battleparam );

#undef GLOBAL

#endif	/* __ENCOUNT_H__ */
