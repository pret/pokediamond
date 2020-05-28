//==============================================================================
/**
 * @file	wsp.h
 * @brief	技サポート関数郡
 * @author	goto
 * @date	2005.12.16(金)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#ifndef	_WE_WES_H_
#define _WE_WES_H_

#include "include/battle/battle_tcb_pri.h"

// -----------------------------------------
//
//	技エフェクト
//
// -----------------------------------------
extern void WestSp_WE_070(WE_SYS_PTR we_sys);
extern void WestSp_WE_339(WE_SYS_PTR we_sys);
extern void WestSp_WE_104(WE_SYS_PTR we_sys);
extern void WestSp_WE_098(WE_SYS_PTR we_sys);
extern void WestSp_WE_065(WE_SYS_PTR we_sys);
extern void WestSp_WE_066(WE_SYS_PTR we_sys);
extern void WestSp_WE_093(WE_SYS_PTR we_sys);
extern void WestSp_WE_151(WE_SYS_PTR we_sys);
extern void WestSp_WE_074(WE_SYS_PTR we_sys);
extern void WestSp_WE_096(WE_SYS_PTR we_sys);
extern void WestSp_WE_100(WE_SYS_PTR we_sys);
extern void WestSp_WE_148(WE_SYS_PTR we_sys);
extern void WestSp_WE_101AT(WE_SYS_PTR we_sys);
extern void WestSp_WE_101DF(WE_SYS_PTR we_sys);
extern void WestSp_WE_150(WE_SYS_PTR we_sys);
extern void WestSp_WE_180(WE_SYS_PTR we_sys);
extern void WestSp_WE_106(WE_SYS_PTR we_sys);
extern void WestSp_WE_107(WE_SYS_PTR we_sys);
extern void WestSp_WE_185(WE_SYS_PTR we_sys);
extern void WestSp_WE_089(WE_SYS_PTR we_sys);
extern void WestSp_WE_204(WE_SYS_PTR we_sys);
extern void WestSp_WE_171(WE_SYS_PTR we_sys);
extern void WestSp_WE_175(WE_SYS_PTR we_sys);
extern void WestSp_WE_222(WE_SYS_PTR we_sys);
extern void WestSp_WE_216(WE_SYS_PTR we_sys);
extern void WestSp_WE_233(WE_SYS_PTR we_sys);
extern void WestSp_WE_207_MAIN(WE_SYS_PTR we_sys);
extern void WestSp_WE_262(WE_SYS_PTR we_sys);
extern void WestSp_WE_326DF(WE_SYS_PTR we_sys);
extern void WestSp_WE_316(WE_SYS_PTR we_sys);
extern void WestSp_WE_252Back(WE_SYS_PTR we_sys);
extern void WestSp_WE_252SSPPoke(WE_SYS_PTR we_sys);
extern void WestSp_WE_224(WE_SYS_PTR we_sys);	// メガホーン
extern void WestSp_WE_224AT(WE_SYS_PTR we_sys);
extern void WestSp_WE_224DF(WE_SYS_PTR we_sys);
extern void WestSp_WE_057(WE_SYS_PTR we_sys);
extern void WestSp_WE_293(WE_SYS_PTR we_sys);
extern void WestSp_WE_253(WE_SYS_PTR we_sys);
extern void WestSp_WE_102(WE_SYS_PTR we_sys);
extern void WestSp_WE_325(WE_SYS_PTR we_sys);
extern void WestSp_WE_Kaiten(WE_SYS_PTR we_sys);
extern void WestSp_WE_DispOut(WE_SYS_PTR we_sys);
extern void WestSp_WE_DispDef(WE_SYS_PTR we_sys);
extern void WestSp_WE_OAM_PalFade(WE_SYS_PTR we_sys);
extern void WestSp_WE_VisibleSet(WE_SYS_PTR we_sys);
extern void WestSp_WE_BgShake(WE_SYS_PTR we_sys);
extern void WSP_Mosaic(WE_SYS_PTR we_sys);
extern void WSP_272(WE_SYS_PTR we_sys);
extern void WSP_272(WE_SYS_PTR we_sys);
extern void WSP_289(WE_SYS_PTR we_sys);
extern void WSP_PalColChange(WE_SYS_PTR we_sys);
extern void WestSp_WE_Laster(WE_SYS_PTR we_sys);
extern void WestSp_WE_DispMove(WE_SYS_PTR we_sys);
extern void WSP_166(WE_SYS_PTR we_sys);

extern void WestSp_WE_425(WE_SYS_PTR we_sys);

//-------------------------------------
//	
//	ノーマル
//		汎用サポート関数
//	
//=====================================
extern void WestSp_EffectTCBPokeRota00(WE_SYS_PTR we_sys);	// ポケモン回転
extern void WestSp_WE_HaikeiPalFade(WE_SYS_PTR we_sys);
extern void WestSp_WE_SSPPokePalFade(WE_SYS_PTR we_sys);
extern void WestSp_WE_CAPPokeScaleUpDown(WE_SYS_PTR we_sys);
extern void WestSp_WE_CAP_NormalAlphaFade(WE_SYS_PTR we_sys);
extern void WestSp_WE_SSP_PokeVanish(WE_SYS_PTR we_sys);

extern void WestSp_WE_T01(WE_SYS_PTR we_sys);				///< 揺らしステム
extern void WestSp_WE_T02(WE_SYS_PTR we_sys);				///< 背景動かしステム
extern void WestSp_WE_T22(WE_SYS_PTR we_sys);
extern void WestSp_WE_SSPPokeScaleUpDown(WE_SYS_PTR we_sys);	/// SSPポケを伸ばして元に戻す

extern void WestSp_WE_T03(WE_SYS_PTR we_sys);				///< ポケモンブリンク
extern void WestSp_WE_T04(WE_SYS_PTR we_sys);				///< 背後攻撃
extern void WestSp_WE_T05(WE_SYS_PTR we_sys);				///< 元の位置に戻る
extern void WestSp_WE_T06(WE_SYS_PTR we_sys);				///< 元の位置に戻る
extern void WestSp_WE_T07(WE_SYS_PTR we_sys);				///< 元の位置に戻る
extern void WestSp_WE_T08(WE_SYS_PTR we_sys);				///< オーラ
extern void WestSp_WE_T10(WE_SYS_PTR we_sys);				///< オーラ

extern void WSP_Emitter_Straight(WE_SYS_PTR we_sys);		///< 直線移動
extern void WSP_Emitter_Parabolic(WE_SYS_PTR we_sys);		///< 放物線移動
extern void WSP_Emitter_Rotation(WE_SYS_PTR we_sys);		///< 回転移動
extern void WSP_Emitter_SimpleUD(WE_SYS_PTR we_sys);		///< 単純な上昇下降

extern void WSP_RectView(WE_SYS_PTR we_sys);				///< 矩形範囲可視
extern void WSP_PokeOAM_View(WE_SYS_PTR we_sys);			///< OAM表示
extern void WSP_AllPokeDrop(WE_SYS_PTR we_sys);				///< 場のポケモンOAM表示

// -----------------------------------------
//
//	OAM利用
//
// -----------------------------------------
extern void WestSp_CAT_WE_081(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_134(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_271(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_106(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_107(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_118(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_132(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_155(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_184(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_193(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_199(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_212(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_259(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_226(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_286(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_288(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_320(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_333(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_252_DrawCap(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap); // Defenseの位置にオートアニメOAMを出す
extern void WestSp_CAT_WE_269(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_270(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_274(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_232(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_275(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_WE_338(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_Free(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_266(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_090(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_Item(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);

// ----------------------------------------
//
//	ステータスエフェクト
//
// ----------------------------------------
extern void WestSp_CAT_ST_001(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_ST_003(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_ST_004(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void WestSp_CAT_ST_006(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);
extern void StatusEffect_Up(WE_SYS_PTR we_sys);
extern void StatusEffect_Down(WE_SYS_PTR we_sys);
extern void StatusEffect_Recover(WE_SYS_PTR we_sys);
extern void StatusEffect_Metal(WE_SYS_PTR we_sys);

//-------------------------------------
//	
//	OAM利用
//		汎用サポート関数
//	
//=====================================
extern void WestSp_CAT_WE_207_SUB(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);	// いちゃもん　いばる　などで出るむかつきマーク


///

extern void EnableCheckAnime(CATS_ACT_PTR cap);

#endif


