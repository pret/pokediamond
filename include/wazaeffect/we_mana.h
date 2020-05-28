//==============================================================================
/**
 * @file	we_mana.h
 * @brief	技エフェクト用システム
 * @author	goto
 * @date	2005.06.22(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#ifndef	_WE_MANA_H_
#define _WE_MANA_H_

#include "battle/battle_common.h"
#include "battle/scio.h"
#include "system/clact_tool.h"
#include "system/palanm.h"
#include "system/softsprite.h"

#include "system/gra_tool.h"

// =============================================================================
//
//
//	■検索用
//	
//		[ _WE-SYS_ ]		WE-SYS
//
//
// =============================================================================

// -----------------------------------------
//
//	WE_SYSの構造体*
//
// -----------------------------------------
typedef struct _TWE_SYS  *	WE_SYS_PTR;


// -----------------------------------------
//
//	BTL_SYSの構造体*
//
// -----------------------------------------
typedef struct _TBTL_SYS *	BTL_SYS_PTR;


// -----------------------------------------
//
//	SE_SYSの構造体*
//
// -----------------------------------------
typedef struct _TSE_SYS  *	SE_SYS_PTR;


// -----------------------------------------
//
//	HC_SYSの構造体*
//
// -----------------------------------------
typedef struct _THC_SYS  *	HC_SYS_PTR;


// -----------------------------------------
//
//	HC_SCROLL_SYSの構造体*
//
// -----------------------------------------
typedef struct _HC_SUB_SYS * HC_SUB_PTR;


// -----------------------------------------
//
//	技エフェクトの背景アークデータ
//
// -----------------------------------------
typedef struct {

	int arc_index;		///< アークID
	int	chr_id;			///< キャラID
	int pal_id;			///< パレットID
	int scr_id;			///< スクリーンID
	
	int pal_start;		///< 背景に使用するパレット開始位置
	int pal_num;		///< 背景に使用するパレット本数

} TWES_HAIKEI_ARC;

// -----------------------------------------
//
//	技エフェクトコール時にバトルから受け渡されるメンバ
//
// -----------------------------------------
typedef struct {

	CATS_SYS_PTR		csp;						///< CSP
	GF_BGL_INI*			bgl;						///< BGL*
	PALETTE_FADE_PTR	pfd;						///< PFD*
	EXCHR_PARAM*		excp[CLIENT_MAX];			///< キャラバッファ
	u8 			 		client_type[ CLIENT_MAX ];	///< クライアントType
	SOFT_SPRITE*		ss[ CLIENT_MAX ];			///< ソフトスプライト
	u32					fight_type;					///< ファイトタイプ
	u16					mons_no[CLIENT_MAX];		///< ポケモンNO
	u8 			 		sex[ CLIENT_MAX ];			///< 性別
	u8					rare[ CLIENT_MAX ];			///< レアフラグ
	u8					form_no[CLIENT_MAX];		///< ポケモンフォルムNO
	u32					personal_rnd[CLIENT_MAX];	///< ポケモン個性乱数
	u32					waza_kouka[CLIENT_MAX];		///< 技効果フラグ
	
	int					eff_arc_id;					///< エフェクトの種類(アーカイブID)
	TWES_HAIKEI_ARC		haikei_data;				///< 背景データ
	
	PERAPVOICE*			perap_voice;				///< ペラップ
	u8*					bg_area;					///< バトルの背景
	u16*				pal_area;					///< バトルのパレット
	
} WES_CALL_BTL_EX_PARAM;


// ---------------------------
//
//	変身とかよう
//
// ---------------------------
typedef struct {
	
	int					at_client_no;				///< 変身する側
	int					df_client_no;				///< 変身される側 at == df なら向き反転	
	
	EXCHR_PARAM*		excp[CLIENT_MAX];			///< キャラバッファ
	SOFT_SPRITE*		ss[ CLIENT_MAX ];			///< ソフトスプライト
	u16					mons_no[CLIENT_MAX];		///< ポケモンNO
	u8					sex[CLIENT_MAX];			///< ポケモン性別
	u8					rare[CLIENT_MAX];			///< ポケモンレアフラグ
	u8					form_no[CLIENT_MAX];		///< ポケモンフォルムNo
	u32					personal_rnd[CLIENT_MAX];	///< ポケモン個性乱数
	u8 			 		client_type[ CLIENT_MAX ];	///< クライアントType
	
} WAZA_POKE_CHANGE_PARAM;

// =========================================
//
//
//	■外部参照：WE-SYS本体	[ _WE-SYS_ ]
//
//
// =========================================

// -----------------------------------------
//
//	WE-SYS 作成
//
// -----------------------------------------
extern WE_SYS_PTR WES_Create(int heap_area);


// -----------------------------------------
//
//	WE-SYS コンテスト用フラグ操作関数
//
// -----------------------------------------
extern void WES_ContestFlag_Set(WE_SYS_PTR we_sys, BOOL flag);
extern BOOL WES_ContestFlag_Get(WE_SYS_PTR we_sys);


// -----------------------------------------
//
//	WE-SYS 破棄
//
// -----------------------------------------
extern BOOL	WES_Delete(WE_SYS_PTR we_sys);


// -----------------------------------------
//
//	技呼び出し
//
// -----------------------------------------
extern BOOL WES_Call(WE_SYS_PTR we_sys, WAZA_EFFECT_PARAM* btl_sys, u16 waza_no);
extern BOOL WES_Call_Ex(WE_SYS_PTR we_sys, WAZA_EFFECT_PARAM* btl_sys, u16 waza_no,
						WES_CALL_BTL_EX_PARAM* wcbep);


// -----------------------------------------
//
//	実行
//	
// -----------------------------------------
extern BOOL	WES_Executed(WE_SYS_PTR we_sys);


// -----------------------------------------
//
//	エフェクト終了チェック
//
// -----------------------------------------
extern BOOL IsWES_Executed(WE_SYS_PTR we_sys);


// -----------------------------------------
//
//	エフェクトの初期化
//
// -----------------------------------------
extern BOOL WES_Reset(WE_SYS_PTR we_sys);


// -----------------------------------------
//
//	WE-SYS 動作チェック
//
// -----------------------------------------
extern BOOL IsWES(WE_SYS_PTR we_sys);


#endif
