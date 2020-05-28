//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_sys.c
 *	@brief		図鑑システム
 *	@author		tomoya takahashi
 *	@data		2006.01.17
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "calctool.h"
#include "calc2d.h"
#include <string.h>
#include <nnsys.h>
#include "touchpanel_system.h"
#include "include/system/heapdefine.h"
#include "include/gflib/display.h"
#include "include/gflib/vram_transfer_manager.h"
#include "include/system/wipe.h"

#include "include/application/zukanlist/zkn_defain.h"
#include "include/application/zukanlist/zkn_snd_def.h"

// 描画関係
#include "include/system/render_oam.h"
#include "include/gflib/char_manager.h"
#include "include/gflib/pltt_manager.h"
#include "gf_gx.h"

#include "button_man.h"
#include "include/system/fontproc.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"

#include "include/application/zukanlist/zkn_sys_static.h"


#include "include/application/zukanlist/zkn_pokelist.h"
#include "include/application/zukanlist/zkn_pokelist_sub.h"
#include "include/application/zukanlist/zkn_sortsearch.h"
#include "include/application/zukanlist/zkn_sortsearch_sub.h"
#include "include/application/zukanlist/zkn_range.h"
#include "include/application/zukanlist/zkn_range_sub.h"
#include "include/application/zukanlist/zkn_zukan.h"
#include "include/application/zukanlist/zkn_zukan_graver.h"
#include "include/application/zukanlist/zkn_zukan_textver.h"
#include "include/application/zukanlist/zkn_zukan_sub.h"
#include "include/application/zukanlist/zkn_zukan_common.h"
#include "include/application/zukanlist/zkn_big.h"
#include "include/application/zukanlist/zkn_big_weight.h"
#include "include/application/zukanlist/zkn_big_sub.h"
#include "include/application/zukanlist/zkn_sound.h"
#include "include/application/zukanlist/zkn_sound_sub.h"
#include "include/application/zukanlist/zkn_event_func.h"
#include "include/application/zukanlist/zkn_world_text_sys.h"
#include "include/application/zukanlist/zkn_zukan_graver_sub.h"

#include "include/communication/wm_icon.h"

#ifdef PM_DEBUG
#include "include/application/zukanlist/zkn_big_debug_sub.h"
#endif

#define __ZKN_SYS_H_GLOBAL
#include "include/application/zukanlist/zkn_sys.h"

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
 *	図鑑プロック
 */
//-----------------------------------------------------------------------------
#define ZKN_VRAMTRANSFER_MANAGER_NUM	( 8 )

#define ZKN_PROC_FADE_DIV	( 6 )
#define ZKN_PROC_FADE_SYNC	( 1 )


//-------------------------------------
//	
//	図鑑プロックワーク
//	
//=====================================
typedef struct {
	// 図鑑システム
	ZKN_SYS_PTR		zkn_sys;
} ZKN_PROC_WORK;



//-----------------------------------------------------------------------------
/**
 *		プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
static void ZknVBlankFunc( void* work );

static void ZknFadeInReq( ZKN_PROC_WORK* p_work );
static void ZknFadeOutReq( ZKN_PROC_WORK* p_work );
static BOOL ZknFadeMain( ZKN_PROC_WORK* p_work );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑プロック生成
 *
 *	@param	proc		プロックデータ	
 *	@param	seq			シーケンス
 *
 *	@return	処理状況
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<動作継続中
 *		PROC_RES_FINISH,			///<動作終了
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT ZKN_ProcInit( PROC* proc, int* seq )
{
	ZKN_PROC_WORK* zkn_w;
	ZKN_PEARENT_DATA* zkn_pearent;
	ZKN_SYS_INIT_DATA zkn_init;
	BOOL check;

	// 音
	Snd_DataSetByScene( SND_SCENE_SUB_ZUKAN, 0, 0 );	// サウンドデータロード（図鑑）（BGM引継ぎ）

	// ヒープ作成
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_ZUKAN, 0x40000 );

	// 図鑑ワーク作成
	zkn_w = PROC_AllocWork( proc, sizeof(ZKN_PROC_WORK), HEAPID_ZUKAN );
	GF_ASSERT( zkn_w );
	memset( zkn_w, 0, sizeof(ZKN_PROC_WORK) );

	// VramTransferManager初期化
	initVramTransferManagerHeap( ZKN_VRAMTRANSFER_MANAGER_NUM, HEAPID_ZUKAN );

	// 図鑑管理者データを取得
	zkn_pearent = PROC_GetParentWork( proc );

	// VBlank HBlank設定
	sys_VBlankFuncChange( ZknVBlankFunc, zkn_w );	// VBlankセット
	sys_HBlankIntrStop();	//HBlank割り込み停止

	// タッチパネルオートサンプリング開始
	InitTPSystem();
	check = InitTPNoBuff( 4 );
	GF_ASSERT( check == TP_OK );

	// 描画セットアップ
	ZKN_SYS_SetUpDraw( HEAPID_ZUKAN );

	// 図鑑システム作成
	zkn_init.cp_zukansave_data	= zkn_pearent->cp_zukansave_data;
	zkn_init.cp_hero_data		= zkn_pearent->cp_hero_data;
	zkn_init.time_zone			= zkn_pearent->time_zone;
	zkn_init.hidemap_id_D15		= zkn_pearent->hidemap_id_D15;
	zkn_init.hidemap_id_D18		= zkn_pearent->hidemap_id_D18;
	zkn_init.hidemap_id_D30		= zkn_pearent->hidemap_id_D30;
	zkn_init.hidemap_id_L04		= zkn_pearent->hidemap_id_L04;
	zkn_init.p_zkn_work			= zkn_pearent->p_zkn_work;
	zkn_w->zkn_sys = ZKN_SYS_Init( HEAPID_ZUKAN, &zkn_init );

	// 音を絞る
	//Snd_BgmFadeOut( BGM_VOL_ZUKAN, BGM_FADE_ZUKAN_TIME );		//フェードアウト
	Snd_PlayerSetPlayerVolume( PLAYER_FIELD, BGM_VOL_ZUKAN );
	
	return PROC_RES_FINISH;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑プロックメイン
 *
 *	@param	proc		プロックデータ	
 *	@param	seq			シーケンス
 *
 *	@return	処理状況
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<動作継続中
 *		PROC_RES_FINISH,			///<動作終了
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT ZKN_ProcMain( PROC* proc, int* seq )
{
	ZKN_PROC_WORK* zkn_w = PROC_GetWork( proc );
	BOOL ret;

#if 1
	switch( *seq ){
	// フェードイン
	case 0:
		ZknFadeInReq( zkn_w );
		SetBrightness( BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY );
		(*seq)++;
		break;
/*	case 1:
		if( ZknFadeMain( zkn_w ) ){
			(*seq)++;
		}
		break;//*/
		
	// メイン動作
	case 1:
		ret = ZKN_SYS_Main( zkn_w->zkn_sys );

		// 終了チェック
		if( ret == TRUE ){
			zkn_w->zkn_sys = NULL;
			(*seq)++;
		}
		break;

	// フェードアウト
	case 2:
		ZknFadeOutReq( zkn_w );
		(*seq)++;
		break;
	case 3:
		if( ZknFadeMain( zkn_w ) ){
			WIPE_ResetWndMask( WIPE_DISP_MAIN );
			WIPE_ResetWndMask( WIPE_DISP_SUB );
			G2_BlendNone();
			G2S_BlendNone();
			return PROC_RES_FINISH;
		}
		break;
	}
#else
	ret = ZKN_SYS_Main( zkn_w->zkn_sys );

	// 終了チェック
	if( ret == TRUE ){
		zkn_w->zkn_sys = NULL;
		return PROC_RES_FINISH;
	}
#endif

	return PROC_RES_CONTINUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑プロック終了
 *
 *	@param	proc		プロックデータ	
 *	@param	seq			シーケンス
 *
 *	@return	処理状況
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<動作継続中
 *		PROC_RES_FINISH,			///<動作終了
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT ZKN_ProcEnd( PROC* proc, int* seq )
{
	ZKN_PROC_WORK* zkn_w = PROC_GetWork( proc );
	BOOL check;

	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット

	// タッチパネルサンプリング終了
	check = StopTP();
	GF_ASSERT( check == TP_OK );
	
	// 表示データ破棄
	ZKN_SYS_ReleaseDraw();

	// VramTransferManager破棄
	DellVramTransferManager();

	// ワーク破棄
	PROC_FreeWork( proc );

	// ヒープ破棄
	sys_DeleteHeap( HEAPID_ZUKAN );

	// 音を戻す
	//Snd_BgmFadeIn( BGM_VOL_MAX, BGM_FADE_ZUKAN_TIME, BGM_FADEIN_START_VOL_NOW );
	Snd_PlayerSetPlayerVolume( PLAYER_FIELD, BGM_VOL_MAX );

	return PROC_RES_FINISH;
}


//-----------------------------------------------------------------------------
/**
 *			プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	VBlank関数
 *
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknVBlankFunc( void* work )
{
	ZKN_PROC_WORK* zkn_w = work;

	if( zkn_w->zkn_sys ){
		ZKN_Vblank( zkn_w->zkn_sys  );
	}

	// Vram転送タスク
	DoVramTransferManager();
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェードイン設定
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFadeInReq( ZKN_PROC_WORK* p_work )
{
	WIPE_SYS_Start(
			WIPE_PATTERN_WMS,
			WIPE_TYPE_FADEIN,
			WIPE_TYPE_FADEIN,
			WIPE_FADE_BLACK,
			ZKN_PROC_FADE_DIV,
			ZKN_PROC_FADE_SYNC,
			HEAPID_ZUKAN
			);
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェードアウト設定
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFadeOutReq( ZKN_PROC_WORK* p_work )
{
	WIPE_SYS_Start(
			WIPE_PATTERN_WMS,
			WIPE_TYPE_FADEOUT,
			WIPE_TYPE_FADEOUT,
			WIPE_FADE_BLACK,
			ZKN_PROC_FADE_DIV,
			ZKN_PROC_FADE_SYNC,
			HEAPID_ZUKAN
			);
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェードチェック
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TRUE		フェード終了
 *	@retval	FALSE		フェード中
 */
//-----------------------------------------------------------------------------
static BOOL ZknFadeMain( ZKN_PROC_WORK* p_work )
{
	return WIPE_SYS_EndCheck();
}















//-----------------------------------------------------------------------------
/**
 *		図鑑システム
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *			図鑑システムデータ
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	図鑑システム構造体
//=====================================
typedef struct _ZKN_SYS{
	// 終了フラグ
	BOOL				zkn_delete;
	// ヒープ
	int					heap;

	// 図鑑ワーク
	ZKN_DATA_WORK*		p_zkn_work;

	// グローバルデータ
	ZKN_GLB_DATA	glb;
	
	// 描画グローバルデータ
	ZKN_GLB_DRAWDATA draw_glb;
	

	//-----------------------------------------------------------------------------
	/**
	 *		イベント関係		（処理分岐）
	 */
	//-----------------------------------------------------------------------------
	// イベントキー
	// 各アプリケーション用イベントキー
	int					event_key_main;	
	int					event_key_sub;	
	// 複数アプリケーション共通で動くアプリケーション用イベントキー（優先度高い）
	int					event_key_common_main;
	int					event_key_common_sub;
	
	// イベント管理
	// 各アプリケーション用
	ZKN_EVENT_SYS_PTR	event_main;	
	ZKN_EVENT_SYS_PTR	event_sub;
	// 複数アプリケーション共通で動くアプリケーション用
	ZKN_EVENT_SYS_PTR	event_main_common;
	ZKN_EVENT_SYS_PTR	event_sub_common;

	// アプリケーション開始イベントデータ
	ZKN_EVENT_DATA	event_apl_start_main;

	//-----------------------------------------------------------------------------
	/**
	 *		アプリケーション関係
	 */
	//-----------------------------------------------------------------------------
	// 各アプリケーションデータ
	ZKN_APL_DATA	main_apl_data[ ZKN_SYS_APLMAIN_NUM ];
	ZKN_APL_DATA	sub_apl_data[ ZKN_SYS_APLSUB_NUM ];
	
	//-------------------------------------
	//	切り替わるアプリケーション
	//=====================================
	// メイン　サブ　プロセス管理
	ZKN_PROC_SYS_PTR	main_proc;
	ZKN_PROC_SYS_PTR	sub_proc;

	//-------------------------------------
	//	ずっと表示されているアプリケーション
	//=====================================
	// 各アプリケーション共通部分プロック
	ZKN_PROC_SYS_PTR	main_common_proc;
	ZKN_PROC_SYS_PTR	sub_common_proc;
	
} ZKN_SYS;




//-----------------------------------------------------------------------------
/**
 *				関数ポインタテーブル
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//		アプリケーションデータ作成
//=====================================
// メイン画面アプリ
const static ZKN_APL_DATA_MAKE_FUNC ZknAplMainDataMakeFunc[ ZKN_SYS_APLMAIN_NUM ] = {
	ZKN_PokeListAplMake,
	ZKN_SortSearchAplMake,
	ZKN_ZukanAplMake,
	ZKN_ZukanGraverAplMake,
	ZKN_ZukanTextverAplMake,
	ZKN_ZukanCommonAplMake,
	ZKN_RangeAplMake,
	ZKN_SoundAplMake,
	ZKN_BigAplMake,
	ZKN_BigWeAplMake,
};
// サブ画面アプリ
const static ZKN_APL_DATA_MAKE_FUNC ZknAplSubDataMakeFunc[ ZKN_SYS_APLSUB_NUM ] = {
	ZKN_PokeListSubAplMake,
	ZKN_SortSearchSubAplMake,
	ZKN_ZukanSubAplMake,
	ZKN_ZukanCommonSubAplMake,
	ZKN_RangeSubAplMake,
	ZKN_SoundSubAplMake,
	ZKN_BigSubAplMake,
	ZKN_GraphicSubAplMake,

#ifdef PM_DEBUG
	ZKN_BigDebugAplMake,
#endif
};

//-------------------------------------
//		アプリケーションデータ破棄
//=====================================
// メイン画面アプリ
const static ZKN_APL_DATA_DELETE_FUNC ZknAplMainDataDeleteFunc[ ZKN_SYS_APLMAIN_NUM ] = {
	ZKN_PokeListAplDelete,
	ZKN_SortSearchAplDelete,
	ZKN_ZukanAplDelete,
	ZKN_ZukanGraverAplDelete,
	ZKN_ZukanTextverAplDelete,
	ZKN_ZukanCommonAplDelete,
	ZKN_RangeAplDelete,
	ZKN_SoundAplDelete,
	ZKN_BigAplDelete,
	ZKN_BigWeAplDelete,
};
// サブ画面アプリ
const static ZKN_APL_DATA_DELETE_FUNC ZknAplSubDataDeleteFunc[ ZKN_SYS_APLSUB_NUM ] = {
	ZKN_PokeListSubAplDelete,
	ZKN_SortSearchSubAplDelete,
	ZKN_ZukanSubAplDelete,
	ZKN_ZukanCommonSubAplDelete,
	ZKN_RangeSubAplDelete,
	ZKN_SoundSubAplDelete,
	ZKN_BigSubAplDelete,
	ZKN_GraphicSubAplDelete,

#ifdef PM_DEBUG
	ZKN_BigDebugAplDelete,
#endif
};

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void DeleteZkn( ZKN_SYS_PTR zkn );

static void VramBankSet( void );
static void OamSet( int heap );
static void setup_3d( void );
static void putback_3d( void );


static void StartAlp( ZKN_SYS_PTR zkn );

static void MakeMainAplStartEvent( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys );
static void DeleteMainAplStartEvent( ZKN_EVENT_DATA* p_event_data );

static void MakeSubAplStartEvent( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys );
static void DeleteSubAplStartEvent( ZKN_EVENT_DATA* p_event_data );

//-----------------------------------------------------------------------------
/**
 *			アプリケーション開始イベント
 */
//-----------------------------------------------------------------------------
#define ZKN_SYS_EVENT_MSK_APL_START  ( 1 )	// アプリケーションスタート



//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑システム初期化
 *
 *	@param	heap	使用するヒープ
 *	@param	p_init	システム初期化データ
 *
 *	@return	作成した図鑑システム
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_SYS_PTR ZKN_SYS_Init( int heap, const ZKN_SYS_INIT_DATA* p_init )
{
	ZKN_SYS_PTR zkn_sys;
	int i;
	ZKN_GLB_DATA_INIT glb_init;

	// メインシステムワーク作成
	zkn_sys = sys_AllocMemory( heap, sizeof(ZKN_SYS) );
	GF_ASSERT( zkn_sys );
	memset( zkn_sys, 0, sizeof(ZKN_SYS) );

	// ヒープ
	zkn_sys->heap	= heap;
	
	// 図鑑グローバルワーク設置
	zkn_sys->p_zkn_work = p_init->p_zkn_work;

	// イベントシステム作成
	zkn_sys->event_main	= ZKN_EVENT_MemoryAlloc( heap );
	zkn_sys->event_sub	= ZKN_EVENT_MemoryAlloc( heap );
	zkn_sys->event_main_common = ZKN_EVENT_MemoryAlloc( heap );
	zkn_sys->event_sub_common  = ZKN_EVENT_MemoryAlloc( heap );

	// プロセス管理システム作成
	zkn_sys->main_proc = ZKN_PROC_MemoryAlloc( heap );
	zkn_sys->sub_proc = ZKN_PROC_MemoryAlloc( heap );
	zkn_sys->main_common_proc = ZKN_PROC_MemoryAlloc( heap );
	zkn_sys->sub_common_proc = ZKN_PROC_MemoryAlloc( heap );

	
	// グローバルデータ初期化
	glb_init.cp_zukansave_data = p_init->cp_zukansave_data;
	glb_init.cp_hero_data = p_init->cp_hero_data;
	glb_init.time_zone = p_init->time_zone;
	glb_init.hidemap_id_D15 = p_init->hidemap_id_D15;
	glb_init.hidemap_id_D30 = p_init->hidemap_id_D30;
	glb_init.hidemap_id_L04 = p_init->hidemap_id_L04;
	glb_init.hidemap_id_D18 = p_init->hidemap_id_D18;
	glb_init.init_list_monsno = ZKN_DW_GetListMonsNo( p_init->p_zkn_work );
	glb_init.zkn_mode = ZKN_DW_GetZknMode( p_init->p_zkn_work );
	ZKN_GLBDATA_Init( &zkn_sys->glb, &glb_init, heap );

	// 描画グローバルデータ初期化
	ZKN_GlbDrawDataInit( &zkn_sys->draw_glb, heap );

	

	// アプリケーションデータ作成
	for( i=0; i<ZKN_SYS_APLMAIN_NUM; i++ ){
		if( ZknAplMainDataMakeFunc[ i ] ){
			ZknAplMainDataMakeFunc[ i ]( &zkn_sys->main_apl_data[ i ], zkn_sys, heap );
		}
	}
	for( i=0; i<ZKN_SYS_APLSUB_NUM; i++ ){
		if( ZknAplSubDataMakeFunc[ i ] ){
			ZknAplSubDataMakeFunc[ i ]( &zkn_sys->sub_apl_data[ i ], zkn_sys, heap );
		}
	}

	// アプリケーション開始イベント作成
	ZKN_EVENT_MakeChangePokeList( heap, &zkn_sys->event_apl_start_main, zkn_sys, ZKN_SYS_EVENT_MSK_APL_START );

	// 最初のアプリケーションイベント発行
	StartAlp( zkn_sys );

	// 通信アイコン設定
/*	
	WirelessIconEasy();	


	CLACT_U_WmIcon_SetReserveAreaCharManager( NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_128K );
	CLACT_U_WmIcon_SetReserveAreaPlttManager( NNS_G2D_VRAM_TYPE_2DMAIN );
//*/

	return zkn_sys;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑メイン
 *
 *	@param	zkn		図鑑システム
 *
 *
 *	@retval	TRUE	終了	メモリのはきも終了
 *	@retval	FALSE	続行
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL ZKN_SYS_Main( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );


	// タッチパネルカーソルフラグ設定
	ZKN_GLBDATA_TouchCursorFlagSet( &zkn->glb );


	// イベント中は動かない
	if( (ZKN_EVENT_DoCheck( zkn->event_main_common ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_main ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_sub_common ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_sub ) == FALSE) ){
		
		ZKN_PROC_MoveLock( zkn->main_common_proc, FALSE );		// メイン画面　複数アプリ共通
		ZKN_PROC_MoveLock( zkn->sub_common_proc, FALSE );		// サブ画面　複数アプリ共通
		ZKN_PROC_MoveLock( zkn->main_proc, FALSE );			// メイン画面
		ZKN_PROC_MoveLock( zkn->sub_proc, FALSE );				// サブ画面
	}else{
		ZKN_PROC_MoveLock( zkn->main_common_proc, TRUE );		// メイン画面　複数アプリ共通
		ZKN_PROC_MoveLock( zkn->sub_common_proc, TRUE );		// サブ画面　複数アプリ共通
		ZKN_PROC_MoveLock( zkn->main_proc, TRUE );			// メイン画面
		ZKN_PROC_MoveLock( zkn->sub_proc, TRUE );				// サブ画面
	}


	// プロセス動作
	ZKN_PROC_Main( zkn->main_common_proc );		// メイン画面　複数アプリ共通
	ZKN_PROC_Main( zkn->sub_common_proc );		// サブ画面　複数アプリ共通
	ZKN_PROC_Main( zkn->main_proc );			// メイン画面
	ZKN_PROC_Main( zkn->sub_proc );				// サブ画面

	ZKN_PROC_Draw( zkn->main_common_proc );		// メイン画面　複数アプリ共通
	ZKN_PROC_Draw( zkn->sub_common_proc );		// サブ画面　複数アプリ共通
	ZKN_PROC_Draw( zkn->main_proc );			// メイン画面
	ZKN_PROC_Draw( zkn->sub_proc );				// サブ画面

	//-----------------------------------------------------------------------------
	/**
	 *			イベント動作		(処理分岐)
	 *			commonの方の判定を優先する
	 *			何か１つ動作しているイベントがあれば他は動かない
	 */
	//-----------------------------------------------------------------------------
	// 複数アプリ共通アプリイベント管理
	// メイン画面イベント
	if( (ZKN_EVENT_DoCheck( zkn->event_main ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_sub_common ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_sub ) == FALSE) ){

		ZKN_EVENT_Main( zkn->event_main_common, zkn->event_key_common_main );	
	}
	if( (ZKN_EVENT_DoCheck( zkn->event_main_common ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_sub_common ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_sub ) == FALSE) ){
		ZKN_EVENT_Main( zkn->event_main, zkn->event_key_main );
	}

	// 各アプリイベント管理
	if( (ZKN_EVENT_DoCheck( zkn->event_main_common ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_main ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_sub ) == FALSE) ){
		ZKN_EVENT_Main( zkn->event_sub_common, zkn->event_key_common_sub );
	}
	if( (ZKN_EVENT_DoCheck( zkn->event_main_common ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_main ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_sub_common ) == FALSE) ){
		ZKN_EVENT_Main( zkn->event_sub, zkn->event_key_sub );
	}

	// 描画main
	GF_G3X_Reset();
	
	ZKN_GlbDrawDataMain( &zkn->draw_glb );
	
	/* ジオメトリ＆レンダリングエンジン関連メモリのスワップ */
	GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);

	// イベントキークリア
	zkn->event_key_common_main = 0;
	zkn->event_key_common_sub = 0;
	zkn->event_key_main = 0;
	zkn->event_key_sub	= 0;


	// 終了チェック
	if( zkn->zkn_delete == TRUE ){

		// 破棄
		DeleteZkn( zkn );
		zkn = NULL;
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画関係のセットアップ
 *
 *	@param	heap	使用ヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_SYS_SetUpDraw( int heap )
{
	// バンクセットアップ
	VramBankSet();
	
	// oam関係セットアップ
	OamSet( heap );


	// 3D面
	setup_3d();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画関係の破棄
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_SYS_ReleaseDraw( void )
{
	// レンダラー共有OAMマネージャ破棄
	REND_OAM_Delete();
	
	// キャラクタデータ破棄
	DeleteCharManager();
	// パレットデータ破棄
	DeletePlttManager();

	// 3D面
	putback_3d();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	Vブランク期間関数
 *
 *	@param	zkn		図鑑システム 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_Vblank( ZKN_SYS_PTR zkn )
{
	ZKN_GlbDrawDataVBlank( &zkn->draw_glb );

	// レンダラーOAM転送
	REND_OAMTrans();
}



//-----------------------------------------------------------------------------
/**
 *		図鑑システムのみ参照可能
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	メイン画面プロセスシステム取得
 *
 *	@param	zkn		図鑑システム
 *
 *	@return	プロセスシステム
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_PROC_SYS_PTR ZKN_SYS_GetProcSysMain( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return zkn->main_proc;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	サブ画面プロセスシステム取得
 *
 *	@param	zkn		図鑑システム
 *
 *	@return	プロセスシステム
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_PROC_SYS_PTR ZKN_SYS_GetProcSysSub( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return zkn->sub_proc;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	メイン画面共通プロセスシステム
 *
 *	@param	zkn		図鑑システム
 *
 *	@return	プロセスシステム
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_PROC_SYS_PTR ZKN_SYS_GetProcSysMainCommon( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return zkn->main_common_proc;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	サブ画面共通プロセスシステム
 *
 *	@param	zkn		図鑑システム
 *
 *	@return	プロセスシステム
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_PROC_SYS_PTR ZKN_SYS_GetProcSysSubCommon( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return zkn->sub_common_proc;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	メイン画面 イベントシステムポインタ取得
 *
 *	@param	zkn 図鑑システム
 *
 *	@return	イベントシステムポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_EVENT_SYS_PTR ZKN_SYS_GetEventSysMain( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return zkn->event_main;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	サブ画面 イベントシステムポインタ取得
 *
 *	@param	zkn 図鑑システム
 *
 *	@return	イベントシステムポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_EVENT_SYS_PTR ZKN_SYS_GetEventSysSub( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return zkn->event_sub;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	メイン画面 共通アプリ イベントシステムポインタ取得
 *
 *	@param	zkn 図鑑システム
 *
 *	@return	イベントシステムポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_EVENT_SYS_PTR ZKN_SYS_GetEventSysMainCommon( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return zkn->event_main_common;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	サブ画面 共通アプリ イベントシステムポインタ取得
 *
 *	@param	zkn 図鑑システム
 *
 *	@return	イベントシステムポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_EVENT_SYS_PTR ZKN_SYS_GetEventSysSubCommon( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return zkn->event_sub_common;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イベントキーポインタ取得
 *
 *	@param	zkn		図鑑システム
 *
 *	@return	イベントキーポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
int* ZKN_SYS_GetEventKeyPtrMain( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return &zkn->event_key_main;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イベントキーポインタ取得
 *
 *	@param	zkn		図鑑システム
 *
 *	@return	イベントキーポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
int* ZKN_SYS_GetEventKeyPtrSub( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return &zkn->event_key_sub;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イベントキーポインタ取得
 *
 *	@param	zkn		図鑑システム
 *
 *	@return	イベントキーポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
int* ZKN_SYS_GetEventKeyPtrMainCommon( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return &zkn->event_key_common_main;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イベントキーポインタ取得
 *
 *	@param	zkn		図鑑システム
 *
 *	@return	イベントキーポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
int* ZKN_SYS_GetEventKeyPtrSubCommon( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return &zkn->event_key_common_sub;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑破棄フラグ取得
 *
 *	@param	zkn		図鑑システム
 *
 *	@return	図鑑破棄フラグ
 *
 * 図鑑破棄フラグは、完全にメモリを破棄しても大丈夫な
 * 状態になってからTRUEにする
 *
 */
//-----------------------------------------------------------------------------
BOOL* ZKN_SYS_GetZknDeleteFlag( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return &zkn->zkn_delete;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	グローバルデータ取得
 *
 *	@param	zkn		図鑑システム
 *
 *	@return	図鑑グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_GLB_DATA* ZKN_SYS_GetGlbData( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return &zkn->glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑描画グローバルデータ
 *
 *	@param	zkn		図鑑システム
 *
 *	@return	図鑑描画グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_GLB_DRAWDATA* ZKN_SYS_GetGlbDrawData( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return &zkn->draw_glb;
}

//----------------------------------------------------------------------------
/**
 *[main画面]
 *	@brief	図鑑アプリケーションデータ取得
 *
 *	@param	zkn			図鑑システム
 *	@param	apl_no		アプリケーションデータ
 *
 *	@return	アプリケーションデータ
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_APL_DATA* ZKN_GetAplDataMain( ZKN_SYS_PTR zkn, int apl_no )
{
	GF_ASSERT( apl_no < ZKN_SYS_APLMAIN_NUM );

	return &zkn->main_apl_data[ apl_no ];
}

//----------------------------------------------------------------------------
/**
 *[sub画面]
 *	@brief	図鑑アプリケーションデータ取得
 *
 *
 *	@param	zkn			図鑑システム
 *	@param	apl_no		アプリケーションデータ
 *
 *	@return	アプリケーションデータ
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_APL_DATA* ZKN_GetAplDataSub( ZKN_SYS_PTR zkn, int apl_no )
{
	GF_ASSERT( apl_no < ZKN_SYS_APLSUB_NUM );

	return &zkn->sub_apl_data[ apl_no ];
}



//-----------------------------------------------------------------------------
/**
 *		いろんなアプリケーションが共通して使用できるもの
 */
//-----------------------------------------------------------------------------
#define ZKN_UTIL_BUTTON_ANIM_SPEED	( FX32_ONE * 2 )

#define ZKN_UTIL_FONTBUTTON_ANIM_PUSH1	( -2 )
#define ZKN_UTIL_FONTBUTTON_ANIM_PUSH2	( -4 )
#define ZKN_UTIL_FONTBUTTON_ANIM_SELECT	( -2 )

//----------------------------------------------------------------------------
/**
 *	@brief	ボタングラフィック共通動作
 *
 *	@param	act				アクター
 *	@param	button_event	ボタンイベント
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_ButtonMove( CLACT_WORK_PTR act, int button_event )
{

	// 押されたとき、押されているときはアニメ
	switch( button_event ){
	case BMN_EVENT_TOUCH:		///< 触れた瞬間
		CLACT_AnmFrameSet( act, ZKN_UTIL_BUTTON_FRAME_PUSH1 );
		break;

	case BMN_EVENT_HOLD:			///< 触りつづけている
		// プッシュ２フレーム目までアニメ
		CLACT_AnmFrameSet( act, ZKN_UTIL_BUTTON_FRAME_PUSH2 );
		break;
		
	case BMN_EVENT_RELEASE:		///< 離された瞬間
		// 選択フレームを設定
		CLACT_AnmFrameSet( act, ZKN_UTIL_BUTTON_FRAME_SELECT );
		break;//*/
		
	case BMN_EVENT_SLIDEOUT:		///< 画面タッチしたままボタン領域から外れた瞬間
	case ZKN_UTIL_BUTTON_PUSH_NONE:	///< 何もされていないとき
		// 先頭までもどす
		if( CLACT_AnmFrameGet( act ) > ZKN_UTIL_BUTTON_FRAME_NONE ){
			CLACT_AnmFrameChg( act, -ZKN_UTIL_BUTTON_ANIM_SPEED );
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンフォントのボタンアニメ
 *
 *	@param	act				親アクター
 *	@param	p_fontoam		フォントOAM
 *	@param	def_y			いつものY位置
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_ButtonFontMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y )
{
	int button_anm = CLACT_AnmFrameGet( act );
	int x, y;

	switch( button_anm ){
	case ZKN_UTIL_BUTTON_FRAME_NONE:		// 無し
		FONTOAM_GetMat( p_fontoam->p_fontoam, &x, &y );

		y = def_y;
		FONTOAM_SetMat( p_fontoam->p_fontoam, x, y );
		break;
		
	case ZKN_UTIL_BUTTON_FRAME_PUSH1:	// プッシュアニメ１フレーム目
		FONTOAM_GetMat( p_fontoam->p_fontoam, &x, &y );

		y = def_y + ZKN_UTIL_FONTBUTTON_ANIM_PUSH1;
		FONTOAM_SetMat( p_fontoam->p_fontoam, x, y );
		break;
		
	case ZKN_UTIL_BUTTON_FRAME_PUSH2:	// プッシュアニメ２フレーム目
		FONTOAM_GetMat( p_fontoam->p_fontoam, &x, &y );

		y = def_y + ZKN_UTIL_FONTBUTTON_ANIM_PUSH2;
		FONTOAM_SetMat( p_fontoam->p_fontoam, x, y );
		break;
		
	case ZKN_UTIL_BUTTON_FRAME_SELECT:	// 選択
		FONTOAM_GetMat( p_fontoam->p_fontoam, &x, &y );

		y = def_y + ZKN_UTIL_FONTBUTTON_ANIM_SELECT;
		FONTOAM_SetMat( p_fontoam->p_fontoam, x, y );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンフォントカラー変更動作
 *
 *	@param	act				アクター
 *	@param	p_fontoam		ボタンフォント
 *	@param	def_y			デフォルトY位置
 *	@param	off_pltt		オフカラーパレットﾅﾝﾊﾞｰ
 *	@param	on_pltt			オンカラーパレットﾅﾝﾊﾞｰ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_ButtonFontMove_Col( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt )
{
	int now_frm;
	
	ZKN_UTIL_ButtonFontMove( 
			act,
			p_fontoam,
			def_y );

	// 現在フレーム取得
	now_frm = CLACT_AnmFrameGet( act );

	// カラーパレット設定
	if( now_frm < ZKN_UTIL_BUTTON_FRAME_PUSH2 ){
		// off_pltt
		FONTOAM_SetPaletteOffsetAddTransPlttNo( p_fontoam->p_fontoam, off_pltt );
	}else{
		// on_pltt
		FONTOAM_SetPaletteOffsetAddTransPlttNo( p_fontoam->p_fontoam, on_pltt );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	当たり判定テーブルデータ設定
 *
 *	@param	p_tbl		テーブル
 *	@param	top			上
 *	@param	bottom		下
 *	@param	left		左
 *	@param	right		右
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_HitTblDataSet( TP_HIT_TBL* p_tbl, int top, int bottom, int left, int right )
{
	p_tbl->rect.top = top;
	p_tbl->rect.bottom = bottom;
	p_tbl->rect.left = left;
	p_tbl->rect.right = right;
}


//----------------------------------------------------------------------------
/**
 *	@brief	BGフェードアウト初期化
 *
 *	@param	p_data		フェードデータ
 *	@param	p_bg		BGシステム
 *	@param	frm			フレームナンバー
 *	@param	p_scrn		スクリーンデータ
 *	@param	top_cs		フェード開始上の位置
 *	@param	top_ce		フェード終了上の位置
 *	@param	bottom_cs	フェード開始したの位置
 *	@param	bottom_ce	フェード終了したの位置
 *	@param	count_max	カウント最大数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_BgShutterFadeInit( ZKN_UTIL_BGSHTTER_DADE* p_data, GF_BGL_INI* p_bg, int frm, NNSG2dScreenData* p_scrn, int top_cs, int top_ce, int bottom_cs, int bottom_ce, int count_max )
{
	p_data->p_bg		= p_bg;
	p_data->frm			= frm;
	p_data->p_scrn		= p_scrn;
	p_data->top_start	= top_cs;
	p_data->top_dis		= top_ce - top_cs;
	p_data->bottom_start= bottom_cs;
	p_data->bottom_dis	= bottom_ce - bottom_cs;
	p_data->move_count_max	= count_max;
	p_data->move_count	= 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	BGシャッターフェード
 *
 *	@param	p_data	フェードデータ
 *
 *	@retval	TRUE　	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL ZKN_UTIL_BgShutterFade( ZKN_UTIL_BGSHTTER_DADE* p_data )
{
	int top_w_size;
	int bottom_w_size;

	
	if( p_data->move_count <= p_data->move_count_max ){

		// スクリーンをクリーン
		GF_BGL_ScrFill( p_data->p_bg, p_data->frm,
				0, 0, 0, 32, 24, GF_BGL_SCRWRT_PALNL );
		
		// 書き込みサイズを求める
		top_w_size = (p_data->top_dis * p_data->move_count) / p_data->move_count_max;
		bottom_w_size = (p_data->bottom_dis * p_data->move_count) / p_data->move_count_max;
		top_w_size += p_data->top_start;
		bottom_w_size += p_data->bottom_start;
		
		// スクリーンデータ書き込み
		if( top_w_size > 0 ){
			GF_BGL_ScrWriteExpand( p_data->p_bg, p_data->frm,
					0, 0,
					32, top_w_size,
					p_data->p_scrn->rawData,
					0, 32 - top_w_size,
					32, 32 );
		}

		// スクリーンデータ書き込み
		if( (32 - bottom_w_size) > 0 ){
			GF_BGL_ScrWriteExpand( p_data->p_bg, p_data->frm,
					0, 32 - bottom_w_size,
					32, bottom_w_size,
					p_data->p_scrn->rawData,
					0, 0,
					32, 32 );
		}
		
		// スクリーンデータ転送
		GF_BGL_LoadScreenV_Req(p_data->p_bg, p_data->frm );


		p_data->move_count++;

		return FALSE;
	}
	
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ビットマップ領域に数字の名前を配置する
 *
 *	@param	p_bmp		ビットマップ領域
 *	@param	num			モンスターナンバー
 *	@param	monsno		モンスターID
 *	@param	heap		使用ヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_PokeListPokeNameBmpMake( GF_BGL_BMPWIN* p_bmp, int num, int monsno, int heap )
{
	STRBUF*	p_num;		// ポケモンナンバー
	STRBUF*	p_name;		// ポケモン名


	// 数字用STRバッファ作成
	p_num = STRBUF_Create( ZKN_POKELIST_POKENAME_NO_NUM, heap );

	// 数字作成
	STRBUF_SetNumber( p_num, num, ZKN_POKELIST_POKENAME_NO_KETA,
			NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );

	// 名前バッファ作成
	p_name = ZKN_WT_GetPokeName( monsno, PM_LANG, heap );

	// 書き込み
	GF_STR_PrintColor( p_bmp, FONT_BUTTON, p_num, ZKN_POKELIST_POKENAME_NO_MAT_X, ZKN_POKELIST_POKENAME_MAT_Y, MSG_NO_PUT, ZKN_FOTNOAM_COLOR, NULL );
	GF_STR_PrintColor( p_bmp, FONT_BUTTON, p_name, ZKN_POKELIST_POKENAME_NAME_MAT_X, ZKN_POKELIST_POKENAME_MAT_Y, MSG_NO_PUT, ZKN_FOTNOAM_COLOR, NULL );
		
	// STRBUF破棄
	STRBUF_Delete( p_num );
	ZKN_WT_DeleteStrBuf( p_name );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンリスト名ビットマップデータ作成
 *
 *	@param	p_drawglb			描画グローバル
 *	@param	cp_glb				データグローバル
 *	@param	heap				ヒープ
 *	@param	mons_no				モンスターナンバー
 *
 *	@return
	// BMP領域破棄
	ZKN_FONTOAM_DeleteBmp( p_bmp );	で破棄してください
 */
//-----------------------------------------------------------------------------
GF_BGL_BMPWIN* ZKN_UTIL_PokeListPokeNameTblBmpMake( ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_GLB_DATA* cp_glb, int heap, int mons_no  )
{
	GF_BGL_BMPWIN* p_bmp;	

	// モンスターナンバー変更処理
	if( ZKN_GLBDATA_PokeZknModeGet( cp_glb ) == ZKN_MODE_SHINOH ){
		p_bmp = ZKN_UTIL_PokeListPokeNameTblBmpMake_Shinou( p_drawglb->fontoam_sys, heap, mons_no );
	}else{
		p_bmp = ZKN_UTIL_PokeListPokeNameTblBmpMake_Zenkoku( p_drawglb->fontoam_sys, heap, mons_no );
	}
	return p_bmp;
}

//----------------------------------------------------------------------------
/**
 * [無条件でmons_noの値で書き込むバージョン]
 *	@brief	ポケモンリスト名ビットマップデータ作成	
 *
 *	@param	p_drawglb			描画グローバル
 *	@param	heap				ヒープ
 *	@param	mons_no				モンスターナンバー
 *
 *	@return
	// BMP領域破棄
	ZKN_FONTOAM_DeleteBmp( p_bmp );	で破棄してください
 */
//-----------------------------------------------------------------------------
GF_BGL_BMPWIN* ZKN_UTIL_PokeListPokeNameTblBmpMake_Zenkoku( ZKN_FONTOAM_SYS_PTR fontoam_sys, int heap, int mons_no )
{
	GF_BGL_BMPWIN* p_bmp;	// 書き込み領域

	// 文字列書き込み領域作成
	p_bmp = ZKN_FONTOAM_GetBmp( fontoam_sys, ZKN_POKELIST_POKENAME_BMP_SIZE_CX, ZKN_POKELIST_POKENAME_BMP_SIZE_CY );

	// ビットマップ領域に書き込み
	ZKN_UTIL_PokeListPokeNameBmpMake( p_bmp, mons_no, mons_no, heap );

	return p_bmp;
}

//----------------------------------------------------------------------------
/**
 * [mons_noの値をシンオウにしなおして書き込むバージョン]
 *	@brief	ポケモンリスト名ビットマップデータ作成	
 *
 *	@param	p_drawglb			描画グローバル
 *	@param	heap				ヒープ
 *	@param	mons_no				モンスターナンバー
 *
 *	@return
	// BMP領域破棄
	ZKN_FONTOAM_DeleteBmp( p_bmp );	で破棄してください
 */
//-----------------------------------------------------------------------------
GF_BGL_BMPWIN* ZKN_UTIL_PokeListPokeNameTblBmpMake_Shinou( ZKN_FONTOAM_SYS_PTR fontoam_sys, int heap, int mons_no )
{
	GF_BGL_BMPWIN* p_bmp;	// 書き込み領域
	int mons_num;

	// シンオウに変更
	mons_num = PokeZenkokuNo2ShinouNo( mons_no );

	// モンスターナンバーが不正　シンオウのポケモンじゃない
	GF_ASSERT_MSG( mons_num > 0, "mons_no[%d] not shinou poke", mons_no );

	// 文字列書き込み領域作成
	p_bmp = ZKN_FONTOAM_GetBmp( fontoam_sys, ZKN_POKELIST_POKENAME_BMP_SIZE_CX, ZKN_POKELIST_POKENAME_BMP_SIZE_CY );

	// ビットマップ領域に書き込み
	ZKN_UTIL_PokeListPokeNameBmpMake( p_bmp, mons_num, mons_no, heap );

	return p_bmp;
}



//----------------------------------------------------------------------------
/**
 *	@brief	描画グローバルエリアにポケモン名リストデータを作成する
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	heap		ヒープ
 *	@param	poke_tbl_no	ポケモンテーブルナンバー（ZKN_GLB_DATA内）
 *	@param	x			リストテーブル座標
 *	@param	y			リストテーブル座用
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_PokeListPokeNameMakeGlb( ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_GLB_DATA* cp_glb, int heap, int poke_tbl_no, fx32 x, fx32 y )
{
	CLACT_WORK_PTR glb_act;
	CLACT_WORK_PTR glbicon_act;
	ZKN_FONTOAM_INIT fontoam_init;
	GF_BGL_BMPWIN* p_bmp;	// 書き込み領域
	CLACT_U_RES_OBJ_PTR pltt_obj;	// パレットプロクシ取得用
	VecFx32 mat;
	const ZKN_POKELIST_DATA* cp_pokedata;
	u32 zkn_mode = ZKN_GLBDATA_PokeZknModeGet( cp_glb );

	//　ポケモンデータ
	cp_pokedata = ZKN_GLBDATA_PokeListTblGet( cp_glb, poke_tbl_no );
	
	// グローバル領域にあるアクター取得
	glb_act = ZKN_GlbPokeNameTblClactGet( p_drawglb );	
	glbicon_act = ZKN_GlbPokeNameIconClactGet( p_drawglb );
	
	// ポケモンリストテーブルの座標を設定
	mat.x = x;
	mat.y = y;
	CLACT_SetMatrix( glb_act, &mat );
	CLACT_SetDrawFlag( glb_act, TRUE );	// 表示
	
	// 捕まえたポケモンならアイコン作成
	if( cp_pokedata->type == ZKN_POKELIST_TYPE_GET ){
		mat.x = x + ZKN_POKELIST_ICON_X_OFS;
		mat.y = y;
		CLACT_SetMatrix( glbicon_act, &mat );
		CLACT_SetDrawFlag( glbicon_act, TRUE );	// 表示
	}else{
		CLACT_SetDrawFlag( glbicon_act, FALSE );	// 表示
	}
	

	// ポケモン名アクターに使用するパレットプロクシ取得
	pltt_obj = ZKN_GlbPokeNameTblResObjGet( p_drawglb, CLACT_U_PLTT_RES );
		
	// ポケモン名アクター作成
	fontoam_init.zkn_fontoam = p_drawglb->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( pltt_obj, NULL );
	fontoam_init.parent		 = glb_act;
	fontoam_init.x			 = -(ZKN_POKELIST_POKENAME_BMP_SIZE_X / 2);
	fontoam_init.y			 = -(ZKN_POKELIST_POKENAME_BMP_SIZE_Y / 2);
	fontoam_init.bg_pri		 = 0;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;


	// 文字列書き込み領域作成
	p_bmp = ZKN_UTIL_PokeListPokeNameTblBmpMake( p_drawglb, cp_glb, heap, cp_pokedata->mons_no );			

	// FONTOAM登録
	fontoam_init.p_bmp = p_bmp;
	ZKN_GlbPokeNameTblSet( p_drawglb, &fontoam_init, 0, cp_pokedata->mons_no, zkn_mode );
	// BMP領域破棄
	ZKN_FONTOAM_DeleteBmp( p_bmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	表示座標を設定
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_PokeListPokeNameGlbMatrixSet(  ZKN_GLB_DRAWDATA* p_drawglb, int x, int y )
{
	ZKN_UTIL_PokeListPokeNameGlbMatrixSet_Minute( &p_drawglb->pokelist_data_draw, x, y );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン名リスト座標を設定
 *
 *	@param	p_data
 *	@param	x
 *	@param	y 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_PokeListPokeNameGlbMatrixSet_Minute(  ZKN_POKELIST_DATA_OAM_DATA* p_data, int x, int y )
{
	VecFx32 mat;

	// ポケモンリストテーブルの座標を設定
	mat.x = x << FX32_SHIFT;
	mat.y = y << FX32_SHIFT;
	CLACT_SetMatrix( p_data->pokelist_tbl, &mat );
	
	mat.x += ZKN_POKELIST_ICON_X_OFS;
	CLACT_SetMatrix( p_data->pokelist_icon, &mat );

	if( p_data->p_pokename->p_fontoam ){
		FONTOAM_ReflectParentMat( p_data->p_pokename->p_fontoam );	
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック設定	性別は自動
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_glb		描画グローバル
 *	@param	mons_no		モンスターナンバー
 *	@param	dir			方向
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_PokemonGraphicSet( ZKN_GLB_DRAWDATA* p_draw, ZKN_GLB_DATA* p_glb, int mons_no, int dir, int x, int y )
{
	// 特殊ポケモン設定かチェック
	if( mons_no == MONSNO_ANNOON ){
		// アンノーン
		ZKN_UTIL_PokemonGraphicSet_Anoon_Idx( p_draw, p_glb, dir, x, y, 0, 0 );
	}else if( mons_no == MONSNO_MINOMUTTI ){
		// ミノムッチ
		ZKN_UTIL_PokemonGraphicSet_Minomutti_Idx( p_draw, p_glb, dir, x, y, 0, 0 );
	}else if( mons_no == MONSNO_MINOMESU ){
		// ミノメス
		ZKN_UTIL_PokemonGraphicSet_Minomesu_Idx( p_draw, p_glb, dir, x, y, 0, 0 );
	}else if( mons_no == MONSNO_SIIUSI ){
		// シーウシ	
		ZKN_UTIL_PokemonGraphicSet_Siiusi_Idx( p_draw, p_glb, dir, x, y, 0, 0 );
	}else if( mons_no == MONSNO_SIIDORUGO ){
		// シードルゴ
		ZKN_UTIL_PokemonGraphicSet_Siidorugo_Idx( p_draw, p_glb, dir, x, y, 0, 0 );

	}else if( mons_no == MONSNO_DEOKISISU ){
		// デオキシス
		ZKN_UTIL_PokemonGraphicSet_Deokisisu_Idx( p_draw, p_glb, dir, x, y, 0, 0 );
	}else{
		// 通常
		ZKN_UTIL_PokemonGraphicSet_FS_Idx( p_draw, p_glb, mons_no, dir, x, y,  ZUKAN_WORK_SEX_FIRST, 0 );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック設定　見た順設定用
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_glb		描画グローバル
 *	@param	mons_no		モンスターナンバー
 *	@param	dir			方向
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	count		ZUKAN_WORK_SEX_FIRST　ZUKAN_WORK_SEX_SECOND
 *	@param	idx			ポケモンスプライトインデックス
 *
 *	@retval	設定した性別ナンバー
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	エラー
 */
//-----------------------------------------------------------------------------
u32 ZKN_UTIL_PokemonGraphicSet_FS_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int mons_no, int dir, int x, int y, int count, int idx )
{
	int sex;
	u32 rnd = 0;

	if( mons_no == MONSNO_PATTIIRU ){
		// パッチールのときは、固体乱数を取得
		rnd = ZKN_GLBDATA_SaveData_PattiruRndGet( cp_glb );
	}
	
	//　性別取得
	sex = ZKN_GLBDATA_SaveData_SexGet( cp_glb, mons_no, count );

	// 性別があったら設定
	if( sex != ZUKAN_WORK_GET_SEX_ERR ){
		// ポケモン設定
		ZKN_GlbPokemonGraphicSet_Idx( p_draw, mons_no,
				sex, dir, PARA_NORMAL, 0, rnd, x, y, idx );
	}
	
	return sex;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィックアンノーン設定
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_glb		描画グローバル
 *	@param	dir			方向
 *	@param	x			X座標
 *	@param	y			Y座標
 *	@param	count		カウント	（0～27）
 *	@param	idx			スプライトインデックス
 *
 *	@retval	設定したフォームナンバー
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	エラー
 */
//-----------------------------------------------------------------------------
u32 ZKN_UTIL_PokemonGraphicSet_Anoon_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx )
{
	int form;
	
	form = ZKN_GLBDATA_SaveData_AnoonFormGet( cp_glb, count );
	
	// フォルムがあったら設定
	if( form != ZUKAN_WORK_GET_SEX_ERR ){

		// ポケモン設定
		ZKN_GlbPokemonGraphicSet_Idx( p_draw, MONSNO_ANNOON,
				PARA_UNK, dir, PARA_NORMAL, form, 0, x, y, idx );
	}
	
	return form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィックウミウシミノムシポケモン設定
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_glb		描画グローバル
 *	@param	dir			方向
 *	@param	x			X座標
 *	@param	y			Y座標
 *	@param	count		順番数	（0～2）
 *	@param	idx			スプライト配列インデックス 
 *
 *	@retval	設定したフォーム
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	エラー
 */
//-----------------------------------------------------------------------------
u32 ZKN_UTIL_PokemonGraphicSet_Siiusi_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx )
{
	int form;
	form = ZKN_GLBDATA_SaveData_SiiusiFormGet( cp_glb, count );
	// エリアがあったら設定
	if( form != ZUKAN_WORK_GET_SEX_ERR ){
		// ポケモン設定
		ZKN_GlbPokemonGraphicSet_Idx( p_draw, MONSNO_SIIUSI,
				PARA_MALE, dir, PARA_NORMAL, form, 0, x, y, idx );
	}
	return form;
}
u32 ZKN_UTIL_PokemonGraphicSet_Siidorugo_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx )
{
	int form;
	form = ZKN_GLBDATA_SaveData_SiidorugoFormGet( cp_glb, count );
	// エリアがあったら設定
	if( form != ZUKAN_WORK_GET_SEX_ERR ){
		// ポケモン設定
		ZKN_GlbPokemonGraphicSet_Idx( p_draw, MONSNO_SIIDORUGO,
				PARA_MALE, dir, PARA_NORMAL, form, 0, x, y, idx );
	}
	return form;
}
u32 ZKN_UTIL_PokemonGraphicSet_Minomutti_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx )
{
	int form;
	form = ZKN_GLBDATA_SaveData_MinomuttiFormGet( cp_glb, count );
	// エリアがあったら設定
	if( form != ZUKAN_WORK_GET_SEX_ERR ){
		// ポケモン設定
		ZKN_GlbPokemonGraphicSet_Idx( p_draw, MONSNO_MINOMUTTI,
				PARA_MALE, dir, PARA_NORMAL, form, 0, x, y, idx );
	}
	return form;
}
u32 ZKN_UTIL_PokemonGraphicSet_Minomesu_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx )
{
	int form;
	form = ZKN_GLBDATA_SaveData_MinomesuFormGet( cp_glb, count );
	// エリアがあったら設定
	if( form != ZUKAN_WORK_GET_SEX_ERR ){
		// ポケモン設定
		ZKN_GlbPokemonGraphicSet_Idx( p_draw, MONSNO_MINOMESU,
				PARA_FEMALE, dir, PARA_NORMAL, form, 0, x, y, idx );
	}
	return form;
}
u32 ZKN_UTIL_PokemonGraphicSet_Deokisisu_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx )
{
	int form;
	form = ZKN_GLBDATA_SaveData_DeokisisuFormGet( cp_glb, count );
	// エリアがあったら設定
	if( form != POKEZUKAN_DEOKISISU_INIT ){
		// ポケモン設定
		ZKN_GlbPokemonGraphicSet_Idx( p_draw, MONSNO_DEOKISISU,
				PARA_FEMALE, dir, PARA_NORMAL, form, 0, x, y, idx );
	}
	return form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑GMMから文字列を取得
 *
 *	@param	data_idx		ﾃﾞｰﾀIDX
 *	@param	heap			ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
STRBUF* ZKN_UTIL_ZknGmmGet( int data_idx, int heap )
{
	STRBUF* str;
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);

	str = MSGMAN_AllocString( man, data_idx );

	MSGMAN_Delete(man);

	return str;
}




//-----------------------------------------------------------------------------
/**
 *			プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
/**
 *
 *	@brief	図鑑破棄
 *
 *	@param	zkn 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZkn( ZKN_SYS_PTR zkn )
{
	int i;

	// 図鑑システムアプリ開始イベントデータ破棄
	ZKN_EVENT_DeleteData( &zkn->event_apl_start_main );
	
	//　イベントデータ破棄
	GF_ASSERT(zkn->event_main);
	sys_FreeMemoryEz( zkn->event_main );
	GF_ASSERT(zkn->event_sub);
	sys_FreeMemoryEz( zkn->event_sub );
	GF_ASSERT(zkn->event_main_common);
	sys_FreeMemoryEz( zkn->event_main_common );
	GF_ASSERT(zkn->event_sub_common);
	sys_FreeMemoryEz( zkn->event_sub_common );

	// プロセスデータ破棄
	GF_ASSERT(zkn->main_proc);
	sys_FreeMemoryEz( zkn->main_proc );
	GF_ASSERT(zkn->sub_proc);
	sys_FreeMemoryEz( zkn->sub_proc );
	GF_ASSERT(zkn->main_common_proc);
	sys_FreeMemoryEz( zkn->main_common_proc );
	GF_ASSERT(zkn->sub_common_proc);
	sys_FreeMemoryEz( zkn->sub_common_proc );

	// アプリケーションデータ破棄
	for( i=0; i<ZKN_SYS_APLMAIN_NUM; i++ ){
		if(ZknAplMainDataDeleteFunc[i]){
			ZknAplMainDataDeleteFunc[i]( &zkn->main_apl_data[ i ] );
		}
	}
	for( i=0; i<ZKN_SYS_APLSUB_NUM; i++ ){
		if(ZknAplSubDataDeleteFunc[i]){
			ZknAplSubDataDeleteFunc[i]( &zkn->sub_apl_data[ i ] );
		}
	}

	// グローバルデータ保存
	ZKN_DW_SetListMonsNo( zkn->p_zkn_work, ZKN_GLBDATA_PokeTextSeeGetMonsno( &zkn->glb ) );	// リストのモンスターナンバー
	// ゼンコク図鑑保持しているかチェック
	if( ZKN_GLBDATA_PokeZknModeChengeCheck( &zkn->glb, ZKN_MODE_ZENKOKU ) == TRUE ){
		ZKN_DW_SetZknMode( zkn->p_zkn_work, ZKN_GLBDATA_PokeTextSeeGetZknMode( &zkn->glb ) );
	}else{
		// まだゼンコク図鑑をもっていない時は、NAZO
		ZKN_DW_SetZknMode( zkn->p_zkn_work, ZKN_MODE_NAZO );
	}

	// グローバルデータ破棄
	ZKN_GLBDATA_Delete( &zkn->glb );
	// 描画グローバルデータ破棄
	ZKN_GlbDrawDataDelete( &zkn->draw_glb );

	sys_FreeMemoryEz( zkn );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	VramBankセットアップ
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void VramBankSet( void )
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_B,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_80_EF,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_0_A,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_0_G				// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &vramSetTable );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMセットアップ
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void OamSet( int heap )
{
	// OAMマネージャーの初期化
	NNS_G2dInitOamManagerModule();

	// 共有OAMマネージャ作成
	// レンダラ用OAMマネージャ作成
	// ここで作成したOAMマネージャをみんなで共有する
	REND_OAMInit( 
			OAM_OAM_MAIN_S, OAM_OAM_MAIN_E,	// メイン画面OAM管理領域
			OAM_AFF_MAIN_S, OAM_AFF_MAIN_E,		// メイン画面アフィン管理領域
			OAM_OAM_SUB_S, OAM_OAM_SUB_E,		// サブ画面OAM管理領域
			OAM_AFF_SUB_S, OAM_AFF_SUB_E,		// サブ画面アフィン管理領域
			heap);
	
	// キャラクタマネージャー初期化
	{
		CHAR_MANAGER_MAKE cm = {
			OAM_CHAR_ENTRY_NUM,
			OAM_CHAR_VRAMTRANS_MAIN_SIZE,
			OAM_CHAR_VRAMTRANS_SUB_SIZE,
		};
		cm.heap = heap;
		
		InitCharManagerReg(&cm, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_32K );
	}
	// パレットマネージャー初期化
	InitPlttManager(OAM_PLTT_ENTRY_NUM, heap);

	// 読み込み開始位置を初期化
	CharLoadStartAll();
	PlttLoadStartAll();

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アプリケーションを開始
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void StartAlp( ZKN_SYS_PTR zkn )
{
	ZKN_EVENT_Init( zkn->event_main, &zkn->event_apl_start_main, 1 );
	zkn->event_key_main = ZKN_SYS_EVENT_MSK_APL_START;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	3D面設定
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setup_3d( void )
{
	// NitroSystem:３Ｄエンジンの初期化
	NNS_G3dInit();
	// マトリクススタックの初期化
    G3X_InitMtxStack();

	// 各種描画モードの設定(シェード＆アンチエイリアス＆半透明)
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(TRUE);
	G3X_AlphaTest(FALSE, 0);	// アルファテスト　　オフ
	G3X_AlphaBlend(TRUE);		// アルファブレンド　オン

	// クリアカラーの設定
    G3X_SetClearColor(GX_RGB(0, 0, 0),	// clear color
                      0,				// clear alpha
                      0x7fff,			// clear depth
                      63,				// clear polygon ID
                      FALSE				// fog
                      );

	// ジオメトリエンジン起動後必ず呼ばれなければならない
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);

	// ビューポートの設定
    G3_ViewPort(0, 0, 255, 191);

	// マネージャがテクスチャイメージスロットを指定スロット分管理できるようにして
	// デフォルトマネージャにする。
	NNS_GfdInitFrmTexVramManager(1, TRUE);
		
	// マネージャがパレットを16KB分管理できるようにして
	// デフォルトマネージャにする。
	NNS_GfdInitFrmPlttVramManager(0x4000, TRUE);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	３D設定で使用したメモリを破棄
 *
 *	@param	none 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void putback_3d( void )
{
	NNS_GfdResetFrmTexVramState();
	NNS_GfdResetFrmPlttVramState();
}

