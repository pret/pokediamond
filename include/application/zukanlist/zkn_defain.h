//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_defain.h
 *	@brief		図鑑定数定義
 *	@author		tomoya takahashi
 *	@data		2006.01.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_DEFAIN_H__
#define __ZKN_DEFAIN_H__


//-----------------------------------------------------------------------------
/**
 *			BG 定義
 */
//-----------------------------------------------------------------------------
#define ZKN_BG_FRM_FONT_M		( GF_BGL_FRAME1_M )	// 文字列
#define ZKN_BG_FRM_UTIL_M		( GF_BGL_FRAME2_M )	// ユーティリティ
#define ZKN_BG_FRM_BACK_M		( GF_BGL_FRAME3_M )	// 背景
#define ZKN_BG_FRM_UTIL_S		( GF_BGL_FRAME1_S )	// ユーティリティ
#define ZKN_BG_FRM_AFFINE_S		( GF_BGL_FRAME3_S )	// アフィン面
#define ZKN_BG_FRM_BACK_S		( GF_BGL_FRAME2_S )	// 背景

#define ZKN_BG_FONT_COLOR		( 0 )		// フォント用カラーパレット
#define ZKN_BG_FONT_COLOR_MSK	( GF_PRINTCOLOR_MAKE(2,1,0) )		// フォント用カラーパレット
#define ZKN_BG_FONT_COLOR2_MSK	( GF_PRINTCOLOR_MAKE(4,3,0) )		// フォント用カラーパレット

#define ZKN_BG_FIGHT_FONT_COLOR		( 0xc )		// フォント用カラーパレット
#define ZKN_BG_FIGHT_FONT_COLOR_MSK	( GF_PRINTCOLOR_MAKE(2,1,0) )		// フォント用カラーパレット
#define ZKN_BG_FIGHT_FONT_COLOR2_MSK	( GF_PRINTCOLOR_MAKE(3,4,0) )		// フォント用カラーパレット


// 文字列面ビットマップ
#define ZKN_BG_FONTBMP_CX	( 32 )
#define ZKN_BG_FONTBMP_CY	( 32 )

//-----------------------------------------------------------------------------
/**
 *			OAM 定義
 */
//-----------------------------------------------------------------------------
#define OAM_OAM_MAIN_S					(0)				// メイン画面 OAM使用領域開始
#define OAM_OAM_MAIN_E					(128)			// メイン画面 OAM使用領域終了
#define OAM_AFF_MAIN_S					(0)				// メイン画面 アフィン使用領域開始
#define OAM_AFF_MAIN_E					(32)			// メイン画面 アフィン使用領域終了
#define OAM_OAM_SUB_S					(0)				// サブ画面 OAM使用領域開始
#define OAM_OAM_SUB_E					(128)			// サブ画面 OAM使用領域終了
#define OAM_AFF_SUB_S					(0)				// サブ画面 アフィン使用領域開始
#define OAM_AFF_SUB_E					(32)			// サブ画面 アフィン使用領域終了
#define OAM_CHAR_ENTRY_NUM				(32)			// キャラクタマネージャエントリー数
#define OAM_CHAR_VRAMTRANS_MAIN_SIZE	(0x14000)		// メイン画面 キャラクタマネージャVram管理領域
#define OAM_CHAR_VRAMTRANS_SUB_SIZE		(0x4000)		// サブ画面 キャラクタマネージャVram管理領域
#define OAM_PLTT_ENTRY_NUM				(32)			// パレットマネージャエントリー数

// セルアクター用
#define ZKN_CLACT_SET_WORK_NUM		( 128 )	// セルアクターセットワーク数
#define ZKN_CLACT_RES_MANAGER_NUM	( 4 )	// リソースマネージャの数
#define ZKN_CLACT_RES_DATA_TBL_NUM	( 32 )	// 各リソースマネージャに登録できるデータ数

#define ZKN_CLACT_RES_OBJ_NUM_DEF	( 4 )	// リソースの種類はほとんどが４でしょう

// FONTOAM
#define ZKN_FONTOAM_WORK_NUM	( 16 )	// FONTOAMワーク数

#define ZKN_FOTNOAM_COLOR	( GF_PRINTCOLOR_MAKE(3,2,1) )


// 各画面のリソース管理ID定数
#define ZKN_POKELIST_SUB_RES_ID_OFS		( 1000 )
#define ZKN_ZUKAN_COMMON_RES_ID_OFS		( 2000 )
#define ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS	( 2100 )
#define ZKN_DRAWGLB_POKENAME_TBL_RES_ID	( 3000 )
#define ZKN_ZUKAN_FOOT_RES_ID	( 4000 )
#define ZKN_ZUKAN_SUB_RES_ID	( 5000 )
#define ZKN_RANGE_RES_ID		( 6000 )
#define ZKN_BIG_WEIGHT_RES_ID	( 7000 )
#define ZKN_BIG_WEIGHT_ICON_RES_ID	( 8000 )
#define ZKN_BIG_SUB_RES_ID		( 9000 )
#define ZKN_SOUND_SUB_RES_ID		( 10000 )
#define ZKN_SOUND_RES_ID		( 11000 )
#define ZKN_CUSOR_RES_ID		( 12000 )
#define ZKN_GRAPHIC_SUB_RES_ID		( 13000 )
#define ZKN_GRAPHIC_RES_ID		( 14000 )
#define ZKN_SORTSEARCH_RES_ID		( 15000 )
#define ZKN_SORTSEARCHSUB_RES_ID	( 16000 )
#define ZKN_ZUKAN_POKETYPE_RES_ID	( 17000 )


// 各画面の使用パレット状況
#define ZKN_DRAWGLB_POKENAME_TBL_PLTT_LOAD	(1)
#define ZKN_POKELIST_TBL_PLTT_LOAD	(12)
#define ZKN_POKELIST_SUB_TBL_PLTT_LOAD	(12)
#define ZKN_ZUKAN_FOOT_PLTT_LOAD	(1)
#define ZKN_ZUKAN_COMMON_PLTT_LOAD	(1) 
#define ZKN_ZUKAN_COMMON_PLTT_SUB_LOAD	(6) 
#define ZKN_ZUKAN_PLTT_LOAD	(5) 
#define ZKN_BIG_PLTT_LOAD	(5) 
#define ZKN_BIG_WEIGHT_PLTT_LOAD	(3) 
#define ZKN_SOUNDSUB_PLTT_LOAD	(3) 
#define ZKN_SOUND_PLTT_LOAD	(1) 
#define ZKN_CURSOR_PLTT_LOAD	(1) 
#define ZKN_GRAPHIC_PLTT_LOAD	(1) 

//-----------------------------------------------------------------------------
/**
 *			ポケモングラフィック
 */
//-----------------------------------------------------------------------------
#define ZKN_POKEGRA_TEX_SIZE	(0x8000)	// ポケモン4体分
#define ZKN_POKEGRA_PLTT_SIZE	(0x80)


//-----------------------------------------------------------------------------
/**
 *			ソフトウェアスプライト
 */
//-----------------------------------------------------------------------------
#define ZKN_SWSP_OBJNUM		(8)
#define ZKN_SWSP_CHARNUM	(8)
#define ZKN_SWSP_PLTTNUM	(8)


//-----------------------------------------------------------------------------
/**
 *			ブライトネス
 */
//-----------------------------------------------------------------------------
#define ZKN_BRIGHTNESS_MSK_ALL	(GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD) 
#define ZKN_BRIGHTNESS_MSK_PLANE2DEF (GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD) 

#define ZKN_FADE_SYNC_COMMON	( 1 )
#define ZKN_FADE_SYNC_LONG_COMMON	( 4 )

#endif		// __ZKN_DEFAIN_H__

