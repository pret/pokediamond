//==============================================================================
/**
 * @file	west_sp.c
 * @brief	サポート関数用ファイル
 * @author	goto
 * @date	2005.07.14(木)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#include "common.h"
#include "system/lib_pack.h"

#include "west_sp.h"

// -----------------------------------------
//
//	■サポート関数用のヘッダー記述
//		サポート関数はこのソースには記述しないでください
//
// -----------------------------------------

#include "wsp_sample.h"

#include "wsp.h"


// -----------------------------------------
//
//	■関数テーブル
//		このテーブルにサポート関数を追加してください。
//
// -----------------------------------------
static const pWeFunc WeSysSP_FuncTable[] = {

	WestSp_Sample,					///< サンプル
	WestSp_SampleEffectTCB,			///< エフェクトTCBサンプル
	WestSp_SampleSoundTCB,			///< サウンドTCBサンプル
	WestSp_SampleTCB,				///< 従来のTCBサンプル
	
	WestSp_EffectTCBPokeRota00,		///< つつくで使用します。ポケモンを少し回転させるタスクです。
	WestSp_WE_070,					///< we_070
	WestSp_WE_339,					///< we_339
	WestSp_WE_104,					///< we_104
	WestSp_WE_098,					///< we_098
	WestSp_WE_065,					///< we_065
	WestSp_WE_066,					///< we_066
	WestSp_WE_093,					///< we_093
	WestSp_WE_151,					///< we_151
	WestSp_WE_074,					///< we_074
	WestSp_WE_096,					///< we_096
	WestSp_WE_100,					///< we_100
	WestSp_WE_148,					///< we_148
	WestSp_WE_101AT,				///< we_101AT
	WestSp_WE_101DF,				///< we_101DF
	WestSp_WE_150,					///< we_150
	WestSp_WE_180,					///< we_180
	WestSp_WE_106,					///< we_106
	WestSp_WE_107,					///< we_107
	WestSp_WE_185,					///< we_185
	WestSp_WE_089,					///< we_089
	WestSp_WE_204,					///< we_204
	WestSp_WE_171,					///< we_171
	WestSp_WE_175,					///< we_175
	WestSp_WE_222,					///< we_222
	WestSp_WE_216,					///< we_216
	WestSp_WE_233,					///< we_233
	WestSp_WE_207_MAIN,				///< we_207_MAIN
	WestSp_WE_262,					///< we_262
	WestSp_WE_HaikeiPalFade,		///< 背景パレットフェード
	WestSp_WE_SSPPokePalFade,		///< ソフトウェアスプライトポケモンをパレットフェード
	WestSp_WE_CAPPokeScaleUpDown,	///< ポケモンスケールアップダウン
	WestSp_WE_T01,					///< tool 揺らし
	WestSp_WE_326DF,				///< 326　防御側動作
	WestSp_WE_CAP_NormalAlphaFade,	///< 
	WestSp_WE_316,					///< we_316
	WestSp_WE_SSP_PokeVanish,		///< ソフトウェアスプライトのポケモンのバニッシュを設定
	WestSp_WE_252Back,				///< we_252
	WestSp_WE_SSPPokeScaleUpDown,	///< sspポケを伸ばして元に戻す
	WestSp_WE_252SSPPoke,
	WestSp_WE_T02,					///< tool スクロール
	WestSp_WE_T22,					///< tool スクロール
	WestSp_WE_224,					///< メガホーン
	WestSp_WE_224AT,				///< メガホーン
	WestSp_WE_224DF,				///< メガホーン
	WestSp_WE_057,					///< なみのり
	WestSp_WE_T03,					///< tool
	WestSp_WE_T04,					///< tool
	WestSp_WE_T05,					///< tool
	WestSp_WE_T06,					///< tool
	WestSp_WE_T07,					///< tool
	WestSp_WE_293,					///< ほごしょく
	WestSp_WE_T08,					///< tool
	WestSp_WE_T10,					///< tool
	WestSp_WE_102,					///< ものまね
	WestSp_WE_325,					///< シャドーパンチ
	WestSp_WE_Kaiten,				///< 回転
	WestSp_WE_DispOut,				///< 画面外へ
	WestSp_WE_DispDef,				///< 規定位置へ
	WestSp_WE_OAM_PalFade,			///< OAMのパレットフェード
	WestSp_WE_VisibleSet,			///< 可変表示システム
	WSP_Emitter_Straight,			///< エミッターの直線移動
	WSP_Emitter_Parabolic,			///< エミッターの放物線移動
	WSP_RectView,					///< 矩形可視
	WestSp_WE_BgShake,				///< BG揺らし
	WSP_Mosaic,						///< モザイク
	WSP_272,						///< なりきり
	WSP_289,						///< よこどり
	WSP_Emitter_Rotation,			///< エミッターの回転
	WSP_Emitter_SimpleUD,			///< 簡単な上昇下降
	WSP_PalColChange,				///< パレット変更
	WSP_PokeOAM_View,				///< OAMView
	WestSp_WE_Laster,				///< ラスター
	WestSp_WE_DispMove,				///< 画面内外移動
	WSP_AllPokeDrop,				///< 全ポケモンOAM化
	WSP_166,						///< スケッチ
	
	// ---- ステータスエフェクト
	StatusEffect_Up,				///< 能力上昇
	StatusEffect_Down,				///< 能力下降
	StatusEffect_Recover,			///< 回復
	StatusEffect_Metal,				///< メタル系
};

#define WEST_SP_FUNC_MAX (NELEMS(WeSysSP_FuncTable))


// ----------------------------------------
//
//	■OBJ登録用
//
// ----------------------------------------
static const pWeClactFunc WeSysSP_ClactFuncTable[] = {

	WestSp_CAT_SampleTCB,
	WestSp_CAT_WE_081,				///< we_081
	WestSp_CAT_WE_134,				///< we_134
	WestSp_CAT_WE_271,				///< we_271
	WestSp_CAT_WE_118,				///< we_118
	WestSp_CAT_WE_132,				///< we_132
	WestSp_CAT_WE_155,				///< we_155
	WestSp_CAT_WE_184,				///< we_184
	WestSp_CAT_WE_193,				///< we_193
	WestSp_CAT_WE_199,				///< we_199
	WestSp_CAT_WE_207_SUB,			///< we_207_SUB	きれまーく
	WestSp_CAT_WE_212,				///< we_212
	WestSp_CAT_WE_259,				///< we_259
	WestSp_CAT_WE_226,				///< we_226
	WestSp_CAT_WE_286,				///< we_286
	WestSp_CAT_WE_288,				///< we_288
	WestSp_CAT_WE_320,				///< we_320
	WestSp_CAT_WE_333,				///< we_333
	WestSp_CAT_WE_252_DrawCap,		///< we_252 cap draw
	WestSp_CAT_WE_269,				///< we_269
	WestSp_CAT_WE_270,				///< we_270
	WestSp_CAT_WE_274,				///< we_270
	WestSp_CAT_WE_232,				///< めたるくろー
	WestSp_CAT_WE_275,				///< ねをはる
	WestSp_CAT_WE_338,				///< ハードプラント
	WestSp_Free,					///< ただ絵が出てアニメが終わる
	WestSp_266,						///< この指
	WestSp_090,						///< じわれ
	WestSp_Item,					///< アイテム

	/**** ステータスエフェクト ****/
	WestSp_CAT_ST_001,
	WestSp_CAT_ST_003,
	WestSp_CAT_ST_004,
	WestSp_CAT_ST_006,
};

#define WEST_SP_CATS_FUNC_MAX (NELEMS(WeSysSP_ClactFuncTable))



// ----------------------------------------
//
//	■旧アクター登録用
//
// ----------------------------------------
static const pWeOldActFunc WeSysSP_OldActFuncTable[] = {

	NULL,//SeqWazaIaigiriInit,

};

#define WEST_SP_OLDACT_FUNC_MAX (NELEMS(WeSysSP_OldActFuncTable))


// =============================================================================
//
//
//	■外部参照
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	サポート関数を取得する
 *
 * @param	id			取得する関数のID
 *
 * @retval	pWeFunc		サポート関数のポインタ
 *
 */
//--------------------------------------------------------------
pWeFunc WazaEffectSupportFuncGet(u32 id)
{
	pWeFunc func;
	
	if (id >= WEST_SP_FUNC_MAX){
		SDK_ASSERT(id < WEST_SP_FUNC_MAX);
		return NULL;
	}
	
	func = WeSysSP_FuncTable[id];
	
	return func;
}


//--------------------------------------------------------------
/**
 * @brief	セルアクター用 サポート関数呼び出し
 *
 * @param	id				取得する関数のID
 *
 * @retval	pWeClactFunc	サポート関数のポインタ
 *
 */
//--------------------------------------------------------------
pWeClactFunc WazaEffectSupportFuncGet_CATS(u32 id)
{
	pWeClactFunc func;
	
	if (id >= WEST_SP_CATS_FUNC_MAX){
		SDK_ASSERT(id < WEST_SP_CATS_FUNC_MAX);
		return NULL;
	}
	
	func = WeSysSP_ClactFuncTable[id];
	
	return func;
}


//--------------------------------------------------------------
/**
 * @brief	サポート関数を取得する
 *
 * @param	id			取得する関数のID
 *
 * @retval	pWeCatFunc	サポート関数のポインタ
 *
 */
//--------------------------------------------------------------
pWeOldActFunc WazaEffectSupportFuncGet_OLDACT(u32 id)
{
	pWeOldActFunc func;
	
	if (id >= WEST_SP_OLDACT_FUNC_MAX){
		return NULL;
	}
	
	func = WeSysSP_OldActFuncTable[id];
	
	return func;
}

