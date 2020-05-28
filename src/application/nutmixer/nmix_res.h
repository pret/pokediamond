/**
 *	@file	nmix_res.h
 *	@brief	ナッツミキサー　リソース管理
 *	@author	Miyuki Iwasawa
 *	@date	06.04.08
 *
 *
 *	描画ツールもここに追加
 */

#ifndef __H_NMIX_RES_H__
#define __H_NMIX_RES_H__

#ifdef __NMIX_RES_H_GLOBAL
#define GLOBAL	/***/
#else
#define GLOBAL	extern
#endif



//-----------------------------------------------------------------------------
/**
 *		定数定義
 */
//-----------------------------------------------------------------------------
//-------------------------------------
// OAM
//=====================================
#define NMIX_OAM_OAM_MAIN_S			(0)			// メイン画面 OAM使用領域開始
#define NMIX_OAM_OAM_MAIN_E			(128)		// メイン画面 OAM使用領域終了
#define NMIX_OAM_AFF_MAIN_S			(0)			// メイン画面 アフィン使用領域開始
#define NMIX_OAM_AFF_MAIN_E			(32)		// メイン画面 アフィン使用領域終了
#define NMIX_OAM_OAM_SUB_S			(0)			// サブ画面 OAM使用領域開始
#define NMIX_OAM_OAM_SUB_E			(128)		// サブ画面 OAM使用領域終了
#define NMIX_OAM_AFF_SUB_S			(0)			// サブ画面 アフィン使用領域開始
#define NMIX_OAM_AFF_SUB_E			(32)		// サブ画面 アフィン使用領域終了
#define NMIX_OAM_CHAR_ENTRY_NUM		(32)		// キャラクタマネージャエントリー数
#define NMIX_OAM_CHAR_VRAMTRANS_MAIN_SIZE	(0x20000)	// メイン画面 キャラクタマネージャVram管理領域
#define NMIX_OAM_CHAR_VRAMTRANS_SUB_SIZE	(0x0)		// サブ画面 キャラクタマネージャVram管理領域
#define NMIX_OAM_PLTT_ENTRY_NUM		(32)		// パレットマネージャエントリー数



//-------------------------------------
//	セルアクター
//=====================================
#define NMIX_GAME_CLACT_WORK_MAX		( 72 )	// ワーク最大
#define NMIX_GAME_CLACT_RES_MAX			( 16 )	// それぞれリソース最大
#define NMIX_GAME_CLACT_RES_OBJ_TYPE	( 4 )	// char/pltt/cell/cellanm

//-------------------------------------
//	ソフトウェアスプライト
//=====================================
#define NMIX_GAME_SWSP_WORK_MAX			( 48 )
#define NMIX_GAME_SWSP_CHAR_MAX			( 32 )
#define NMIX_GAME_SWSP_PLTT_MAX			( 32 )





//-----------------------------------------------------------------------------
/**
 *
 *		プロトタイプ宣言
 *
 */
//-----------------------------------------------------------------------------


/**
 *	@brief	コマンド　リソース初期化
 */
GLOBAL void NMixGameCom_GameStartGraphicInit(NMIX_GAMEWORK* wk);
/**
 *	@brief	コマンド　リソース解放
 */
GLOBAL void NMixGameCom_GameStartGraphicRelease(NMIX_GAMEWORK* wk);


/**
 *	@brief	コマンド　リソース初期化
 */
GLOBAL int NMixGameCom_ResInit(NMIX_GAMEWORK* wk,int* seq);
/**
 *	@brief	コマンド　リソース解放
 */
GLOBAL int NMixGameCom_ResRelease(NMIX_GAMEWORK* wk,int *seq);


// 描画処理
GLOBAL void NMixGame_Draw( NMIX_GAMEWORK* wk );
GLOBAL void NMixGame_GraVBlank( NMIX_GAMEWORK* wk );



#endif	//__H_NMIX_RES_H__
