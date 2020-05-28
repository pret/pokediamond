//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_sound.c
 *	@brief		泣き声アプリケーション
 *	@author		tomoya takahashi
 *	@data		2006.01.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"

#include "include/system/snd_tool.h"


#include "include/gflib/display.h"
#include "include/system/brightness.h"
#include "include/system/arc_tool.dat"
#include "include/system/arc_util.h"
#include "include/system/clact_util.h"
#include "include/application/zukanlist/zukan.naix"
#include "include/gflib/button_man.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"

#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_zukan_common.h"
#include "include/application/zukanlist/zkn_sound_sub.h"

#define	__ZKN_SOUND_H_GLOBAL
#include "include/application/zukanlist/zkn_sound.h"


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
#define ZKN_SOUND_EVENT_NUM ( 0 )	// イベント数
//#define ZKN_SOUND_EVENT_CHANGE_BIG ( 0x1 << 0 )	// 大きさくらべへ

#define ZKN_SOUND_OAM_BG_PRI	(0)
#define ZKN_SOUND_OAM_PRI	(17)

//-------------------------------------
//	シーケンス
//=====================================
enum{
	ZKN_SOUND_SEQINIT_ALLOC,
	ZKN_SOUND_SEQINIT_LOAD,
	ZKN_SOUND_SEQINIT_FADEIN,
	ZKN_SOUND_SEQINIT_END,
};
enum{
	ZKN_SOUND_SEQDELETE_FADEOUT_INIT,
	ZKN_SOUND_SEQDELETE_FADEOUT,
	ZKN_SOUND_SEQDELETE_RELEASE,
	ZKN_SOUND_SEQDELETE_FREE,
	ZKN_SOUND_SEQDELETE_END,
};



// 波形データ描画
#define ZKN_SOUND_DRAW_BMP_ONE_SIZE_X	( 1 )
#define ZKN_SOUND_DRAW_BMP_ONE_SIZE_Y	( 1 )
#define ZKN_SOUND_DRAW_BMP_Y_MAX		( 32 )
#define ZKN_SOUND_DRAW_BMP_DEF_Y		( 151 )
#define ZKN_SOUND_DRAW_BMP_PL_TBL		(9)
#define ZKN_SOUND_DRAW_BMP_PL			(6)


// 波形データスクロール
#define ZKN_SOUND_SCRL_BMP_SPEED	( 4 )


// 棒グラフ
#define ZKN_SOUND_GRAPH_NUM			( 9 )		// グラフの横要素数
#define ZKN_SOUND_GRAPH_ZANZOU_NUM	( 9 )		// 残像の縦要素数
#define ZKN_SOUND_GRAPH_MAT_DEF_X	( 112 )
#define ZKN_SOUND_GRAPH_MAT_DEF_Y	( 96 )
#define ZKN_SOUND_GRAPH_MAT_OFS_X	( 16 )
#define ZKN_SOUND_GRAPH_MAT_OFS_Y	( -8 )
#define ZKN_SOUND_GRAPH_DES_COUNT	( 2 )
#define ZKN_SOUND_GRAPH_DOWN_COUNT	( 16 )

// フェード用
#define ZKN_SOUND_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	泣き声画面　グローバル変数
//=====================================
typedef struct {
	int*				p_event_key;		// イベントキー
	ZKN_GLB_DATA*		p_glb;				// グローバルデータ

	// メインコモングローバル
	ZKN_APL_DATA*	p_main_common;	// アプリデータ

	// サブサウンドアプリデータ
	ZKN_APL_DATA*	p_sub_sound;	// アプリデータ
} ZKN_SOUND_GLB;

//-------------------------------------
//	泣き声画面　描画グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// 描画グローバルデータ

	int pokegra_move_x;
	int pokegra_move_y;

	int fade_mode;		// フェードモード
	int fade_sync;		// フェードシンク数
} ZKN_SOUND_DRAWGLB;


//-------------------------------------
//	泣き声画面　内部ワーク
//=====================================
typedef struct {
	// 音声データ
	const SNDWaveData* cp_snd_data;
	int tick;
	int data_num;
	u8 snd_graph_data[ ZKN_SOUND_GRAPH_NUM ];

} ZKN_SOUND_WORK;

//-------------------------------------
//	グラフ残像データ
//=====================================
typedef struct {
	CLACT_WORK_PTR act;
	int dess_count;		// 非表示カウンタ
} ZKN_GRAPH_ZANZOU;

//-------------------------------------
//	グラフ先頭
//=====================================
typedef struct {
	CLACT_WORK_PTR act;
	int level;			// 今いるレベル
	int down_count;	// 落ちるまでのカウンタ

} ZKNGRAPH_TOP;


//-------------------------------------
//	グラフ１要素データ
//=====================================
typedef struct {
	ZKN_GRAPH_ZANZOU zanzou[ ZKN_SOUND_GRAPH_ZANZOU_NUM ];
	ZKNGRAPH_TOP	top;
} ZKN_GRAPH_ONE_DATA;


//-------------------------------------
//	泣き声画面　内部ワーク
//=====================================
typedef struct {
	// ポケグラフェード用動作ワーク
	ZKN_UTIL_MOVE_WORK pokegra_move;

	// グラフデータ
	ZKN_GRAPH_ONE_DATA snd_graph_act[ ZKN_SOUND_GRAPH_NUM ];
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	// BMPスクロール制御
	int scrl_num;
	int last_y;
	int last_tick;

} ZKN_SOUND_DRAW;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *		アプリケーションデータ作成関係
 */
//-----------------------------------------------------------------------------
static ZKN_SOUND_GLB* MakeSoundGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_SOUND_DRAWGLB* MakeSoundDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
//static ZKN_EVENT_DATA* MakeSoundEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteSoundGlb( ZKN_SOUND_GLB* p_glb );
static void DeleteSoundDrawGlb( ZKN_SOUND_DRAWGLB* p_glb );
//static void DeleteSoundEvent( ZKN_EVENT_DATA* p_event );


static int SoundEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
static int ZknSoundProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSoundProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSoundProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSoundProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknSoundProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknSoundProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// ポケグラ
static void ZknSoundPokeGraOn( ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb );
static void ZknSoundPokeGraOff( ZKN_SOUND_DRAWGLB* p_drawglb );

// フェード処理
static void ZknSoundOamFadeInit( ZKN_SOUND_DRAW* p_draw );
static void ZknSoundOamFadeDelete( ZKN_SOUND_DRAW* p_draw );
static void ZknSoundFadeInit( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknSoundFadeMain( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, BOOL fadein_out );
static void ZknSoundFadeOtherInit( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknSoundFadeOtherMain( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, BOOL fadein_out );

// Resource読み込み
static void ZknSoundLoadRes( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, const ZKN_SOUND_WORK* cp_datawork, int heap );
static void ZknSoundDeleteRes( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb );
static void ZknSoundSetUpBg( ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, int heap );
static void ZknSoundPutBackBg( ZKN_SOUND_DRAWGLB* p_drawglb );
static void ZknSoundOamResLoad( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, int heap );
static void ZknSoundOamResDelete( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb );
static void ZknSoundOamInit( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, int heap );
static void ZknSoundOamDelete( ZKN_SOUND_DRAW* p_draw );
static void ZknSoundFontOamInit( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, int heap );
static void ZknSoundFontOamDelete( ZKN_SOUND_DRAW* p_draw );


static void ZknSoundGetTich( ZKN_SOUND_WORK* p_work, ZKN_SOUND_GLB* p_glb );


static void ZknSoundBmpScrollSetUp( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb );
static void ZknSoundBmpScroll( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_WORK* cp_work );
static void ZknSoundBmpDraw( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const SNDWaveData* cp_snd_data, int start, int end, int draw_xnum, int x, int def_y, int* p_set_y );
static void ZknSoundBmpDammyDraw( ZKN_SOUND_DRAWGLB* p_drawglb, int start, int end, int x, int def_y, int* p_set_y );
static void ZknSoundBmpDrawOne( GF_BGL_BMPWIN* p_bmp, u8 data, int x, int def_y, int* p_set_y );

// 棒グラフ
static void ZknSoundGraphLevelSet( ZKN_SOUND_WORK* p_work, ZKN_SOUND_GLB* p_glb );
static void ZknSoundGraphInit( ZKN_SOUND_DRAW* p_draw );
static void ZknSoundGraphMove( ZKN_SOUND_DRAW* p_draw, const ZKN_SOUND_WORK* cp_work );

static void ZknSoundGraphInitData( ZKN_GRAPH_ONE_DATA* p_data, int x_num );
static void ZknSoundGraphMoveData( ZKN_GRAPH_ONE_DATA* p_data, int level );
static void ZknSoundGraphSetLevelMatrixTop( CLACT_WORK_PTR act, int level );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	泣き声　アプリ作成
 *
 *	@param	p_data		アプリケーションデータ
 *	@param	zkn_sys		図鑑システム
 *	@param	heap		使用ヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_SoundAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_SOUND_GLB*	p_glb;
	ZKN_SOUND_DRAWGLB*	p_drawglb;
//	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeSoundGlb( heap, zkn_sys );
	p_drawglb = MakeSoundDrawGlb( heap, zkn_sys );
//	p_event = MakeSoundEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= NULL;
//	p_data->p_event_data	= p_event;
	p_data->event_num		= SoundEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknSoundProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknSoundProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknSoundProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknSoundProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknSoundProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknSoundProcDrawFuncDelete;
}
//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリスト	サブ画面　メニューアプリ破棄
 *
 *	@param	p_data	アプリケーションデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_SoundAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteSoundGlb( p_data->p_glb_data ); 
	DeleteSoundDrawGlb( p_data->p_glb_draw ); 
//	DeleteSoundEvent( p_data->p_event_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケグラフェードアウト先設定
 *
 *	@param	p_data	アプリケーションデータ
 *	@param	x		Ｘ座標
 *	@param	y		Ｙ座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_SoundPokeGraFadeOutSet( ZKN_APL_DATA* p_data, int x, int y )
{
	ZKN_SOUND_DRAWGLB* p_glb = p_data->p_glb_draw;

	p_glb->pokegra_move_x = x;
	p_glb->pokegra_move_y = y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェードモード設定
 *
 *	@param	p_data		アプリケーションデータ
 *	@param	fade_mode	フェードモード
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_SoundFadeModeSet( ZKN_APL_DATA* p_data, int fade_mode )
{
	ZKN_SOUND_DRAWGLB* p_glb = p_data->p_glb_draw;

	p_glb->fade_mode = fade_mode;
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェードシンク数設定
 *
 *	@param	p_data		アプリケーションデータ
 *	@param	fade_mode	フェードシンク数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_SoundFadeModeSync( ZKN_APL_DATA* p_data, int fade_sync )
{
	ZKN_SOUND_DRAWGLB* p_glb = p_data->p_glb_draw;

	p_glb->fade_sync = fade_sync;
}


//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	泣き声　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_SOUND_GLB* MakeSoundGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_SOUND_GLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_SOUND_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_SOUND_GLB) );

	// main画面からのイベントキー
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrMain( zkn_sys ); 

	// グローバルデータ
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );
	
	// めいんグローバルアプリデータ取得
	p_glb->p_main_common = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_COMMON );

	// サブ鳴き声グローバルアプリデータ取得
	p_glb->p_sub_sound = ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_SOUND );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	泣き声　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_SOUND_DRAWGLB* MakeSoundDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_SOUND_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_SOUND_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_SOUND_DRAWGLB) );

	// 描画データ
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}
#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	泣き声　イベント作成
 *
 *	@param	heap		使用するヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	イベントデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeSoundEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = SoundEventDataNumGet();

	// イベントデータテーブル作成
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	MakeSoundChangeBig( heap, &p_event_tbl[0], zkn_sys );

	return p_event_tbl;
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	泣き声　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSoundGlb( ZKN_SOUND_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	泣き声　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSoundDrawGlb( ZKN_SOUND_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}
#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	泣き声　イベントデータ破棄
 *
 *	@param	p_event	イベントデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSoundEvent( ZKN_EVENT_DATA* p_event )
{
	GF_ASSERT( p_event );
	
	DeleteSoundChangeBig( &p_event[0] );

	sys_FreeMemoryEz( p_event );
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	泣き声アプリ　イベント数取得
 *	
 *	@param	none	
 *
 *	@return	泣き声アプリ　イベント数
 *
 *
 */
//-----------------------------------------------------------------------------
static int SoundEventDataNumGet( void )
{
	return ZKN_SOUND_EVENT_NUM;
}


//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	[初期化]
 *	@brief	アプリケーションプロセス	データ変更
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSoundProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SOUND_GLB* p_glb = p_glbdata;
	ZKN_SOUND_WORK* p_work;
	int mons_no = ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb );
	
	// ワーク作成
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_SOUND_WORK) );
	GF_ASSERT( p_work );
	memset( p_work, 0, sizeof(ZKN_SOUND_WORK) );
	p_dodata->p_work = p_work;
	

	// サウンドデータ取得
	p_work->cp_snd_data = Snd_ZukanWaveDataSet( mons_no );

	// データ配列数取得
	p_work->data_num = Snd_WaveDataSampleSizeGet( p_work->cp_snd_data );

	// チック数取得
	ZknSoundGetTich( p_work, p_glb );
	
	return ZKN_PROC_TRUE;
}

//----------------------------------------------------------------------------
/**
 *	[メイン]
 *	@brief	アプリケーションプロセス	データ変更
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSoundProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SOUND_GLB* p_glb = p_glbdata;
	ZKN_SOUND_WORK*	p_work = p_dodata->p_work;
	
	
	// 終了へ
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	// チック数を取得
	ZknSoundGetTich( p_work, p_glb );

	// 波形レベル設定
	ZknSoundGraphLevelSet( p_work, p_glb );

	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	[破棄]
 *	@brief	アプリケーションプロセス	データ変更
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSoundProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SOUND_WORK* p_work = p_dodata->p_work;

	
	sys_FreeMemoryEz( p_work );
	p_dodata->p_work = NULL;
	
	return ZKN_PROC_TRUE;
}

//----------------------------------------------------------------------------
/**
 * [初期化]
 *
 *	@brief	アプリケーションプロセス	描画
 *
 *	@param	p_glbdraw	描画グローバルデータ
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *	@param	cp_dodata	今の処理の内部ワークデータ
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSoundProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SOUND_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SOUND_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SOUND_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SOUND_DRAW* p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_SOUND_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_SOUND_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_SOUND_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_SOUND_SEQINIT_LOAD:
		ZknSoundLoadRes( p_drawwork, p_drawglb, cp_dataglb, cp_datawork, p_drawdata->heap );

		
		// フェード初期化
		if( p_drawglb->fade_mode == ZKN_SOUND_FADE_MODE_MY ){
			ZknSoundFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		}else{
			ZknSoundFadeOtherInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		}

		// 音のフェード
		Snd_BgmFadeOut( 0, BGM_FADE_ZUKAN_NAKIGOE_TIME );		//フェードアウト
		
		p_drawdata->seq++;
		break;
		
	case ZKN_SOUND_SEQINIT_FADEIN:
		if( p_drawglb->fade_mode == ZKN_SOUND_FADE_MODE_MY ){
			check = ZknSoundFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		}else{
			check = ZknSoundFadeOtherMain( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		}

		if( (check == TRUE) && ( Snd_FadeCheck() == 0 ) ){
			Snd_PlayerPause( PLAYER_FIELD, TRUE );		//フィールドBGMポーズ
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_SOUND_SEQINIT_END:
		return ZKN_PROC_TRUE;
	}

	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 * [メイン]
 *
 *	@brief	アプリケーションプロセス	描画
 *
 *	@param	p_glbdraw	描画グローバルデータ
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *	@param	cp_dodata	今の処理の内部ワークデータ
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSoundProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SOUND_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SOUND_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SOUND_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SOUND_DRAW* p_drawwork = p_drawdata->p_work;

	// 波形データ動作
	ZknSoundBmpScroll( p_drawwork, p_drawglb, cp_datawork );

	// グラフ動作
	ZknSoundGraphMove( p_drawwork, cp_datawork );

	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 * [破棄]
 *
 *	@brief	アプリケーションプロセス	描画
 *
 *	@param	p_glbdraw	描画グローバルデータ
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *	@param	cp_dodata	今の処理の内部ワークデータ
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSoundProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SOUND_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SOUND_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SOUND_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SOUND_DRAW* p_drawwork = p_drawdata->p_work;
	BOOL check;


	switch( p_drawdata->seq ){
	case ZKN_SOUND_SEQDELETE_FADEOUT_INIT:
		if( p_drawglb->fade_mode == ZKN_SOUND_FADE_MODE_MY ){
			ZknSoundFadeInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		}else{
			ZknSoundFadeOtherInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		}

		Snd_PlayerPause( PLAYER_FIELD, FALSE );			//フィールドBGM再開
		Snd_BgmFadeIn( BGM_VOL_MAX, BGM_FADE_ZUKAN_NAKIGOE_TIME, BGM_FADEIN_START_VOL_MIN );	//フェードイン

		p_drawdata->seq++;
		break;
		
	case ZKN_SOUND_SEQDELETE_FADEOUT:
		if( p_drawglb->fade_mode == ZKN_SOUND_FADE_MODE_MY ){
			check = ZknSoundFadeMain( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		}else{
			check = ZknSoundFadeOtherMain( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		}
		if( check ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_SOUND_SEQDELETE_RELEASE:
		
		ZknSoundDeleteRes( p_drawwork, p_drawglb );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_SOUND_SEQDELETE_FREE:

		sys_FreeMemoryEz(p_drawdata->p_work);
		p_drawdata->p_work = NULL;
		p_drawdata->seq++;
		break;
		
		
	case ZKN_SOUND_SEQDELETE_END:
		return ZKN_PROC_TRUE;
	}

	return ZKN_PROC_FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック表示ON
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundPokeGraOn( ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );

	// ポケモン設定
	ZKN_UTIL_PokemonGraphicSet( p_drawglb->p_drawglb, cp_glb->p_glb, monsno,
			PARA_FRONT, ZKN_SOUND_POKEGRA_DRAW_X, ZKN_SOUND_POKEGRA_DRAW_Y );
	
	// 表示
	SoftSpriteParaSet( p_pokegra, SS_PARA_VANISH, FALSE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック表示OFF
 *
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundPokeGraOff( ZKN_SOUND_DRAWGLB* p_drawglb )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );

	// 表示OFF
	SoftSpriteParaSet( p_pokegra, SS_PARA_VANISH, TRUE );

	// ソフトパレットフェードがかかっている可能性があるのでOFF
	SoftSpritePalFadeOff( p_pokegra );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMフェード初期化
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundOamFadeInit( ZKN_SOUND_DRAW* p_draw )
{
	int i, j;

	// 全グラフアクター生成
	for( i=0; i<ZKN_SOUND_GRAPH_NUM; i++ ){

		for( j=0; j<ZKN_SOUND_GRAPH_ZANZOU_NUM; j++ ){
			CLACT_ObjModeSet( p_draw->snd_graph_act[i].zanzou[ j ].act, GX_OAM_MODE_XLU );
		}
		CLACT_ObjModeSet( p_draw->snd_graph_act[i].top.act, GX_OAM_MODE_XLU );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMフェードリセット
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundOamFadeDelete( ZKN_SOUND_DRAW* p_draw )
{
	int i, j;

	// 全グラフアクター生成
	for( i=0; i<ZKN_SOUND_GRAPH_NUM; i++ ){

		for( j=0; j<ZKN_SOUND_GRAPH_ZANZOU_NUM; j++ ){
			CLACT_ObjModeSet( p_draw->snd_graph_act[i].zanzou[ j ].act, GX_OAM_MODE_NORMAL );
		}
		CLACT_ObjModeSet( p_draw->snd_graph_act[i].top.act, GX_OAM_MODE_NORMAL );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェード処理初期化
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	fadein_out	フェードインアウト
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundFadeInit( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, BOOL fadein_out )
{
	// 半透明OAM設定
	ZknSoundOamFadeInit( p_draw );

	// ブライトネス処理を行ってよいか
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_SOUND_FADE_SYNC, 
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_SOUND_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_SOUND_FADE_SYNC, 
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_SOUND_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}
	}

	// ブライトネス値設定
	ZKN_GLB_SpritePokeGraPalFade( p_drawglb->p_drawglb, &p_drawglb->p_drawglb->fade );
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェード処理メイン
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	fadein_out	フェードインアウト
 *
 *	@retval	TRUE	フェード終了
 *	@retval	FALSE	フェード途中
 */
//-----------------------------------------------------------------------------
static BOOL ZknSoundFadeMain( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check;

	// ブライトネスしよう許可でてるかチェック
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
		check = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade );
	}else{
		check = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade );
	}

	// 終わったら終了処理
	if( check ){
		if( fadein_out ){
			// 半透明OAM破棄
			ZknSoundOamFadeDelete( p_draw );
		}

		return TRUE;
	}else{
		// ブライトネス値設定
		ZKN_GLB_SpritePokeGraPalFade( p_drawglb->p_drawglb, &p_drawglb->p_drawglb->fade );
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	他アプリケーションへのフェード処理
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	fadein_out	フェードイン　アウト
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundFadeOtherInit( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, BOOL fadein_out )
{
	// 半透明OAM設定
	ZknSoundOamFadeInit( p_draw );


	// フェードアウトの時だけの処理
	if( fadein_out == FALSE ){
		// ポケモングラフィックフェード
		ZKN_UTIL_MoveReq( &p_draw->pokegra_move, ZKN_SOUND_POKEGRA_DRAW_X, p_drawglb->pokegra_move_x, ZKN_SOUND_POKEGRA_DRAW_Y, p_drawglb->pokegra_move_y, p_drawglb->fade_sync );
	}

	// ブライトネスを使って良いかﾁｪｯｸ
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
		
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, p_drawglb->fade_sync, 
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_SOUND_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, p_drawglb->fade_sync, 
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_SOUND_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}
	}
}
//----------------------------------------------------------------------------
/**
 *	@brief	他アプリケーションへのフェード処理メイン
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	fadein_out	フェードイン　アウト
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL ZknSoundFadeOtherMain( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check[ 2 ];
	int i;
	

	// フェードアウトのときのみの処理
	if( fadein_out == FALSE ){
		// ポケモングラフィック
		check[0] = ZKN_UTIL_MoveMain( &p_draw->pokegra_move );

		// 座標設定
		ZKN_GlbPokemonGraphicSetMatrix( p_drawglb->p_drawglb, p_draw->pokegra_move.x, p_draw->pokegra_move.y );

	}else{
		check[0] = TRUE;
	}
	
	// ブライトネスを使用してよいときは自分でfadeを動かす
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
		check[1] = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade );
	}else{
		check[1] = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade );
	}

	for( i=0; i<2; i++ ){
		if( check[i] == FALSE ){
			break;
		}
	}

	if( i==2 ){

		// フェードインのときは半透明破棄
		if( fadein_out == TRUE ){
			// OAM半透明設定破棄
			ZknSoundOamFadeDelete( p_draw );
		}
		return TRUE;
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	Resource読み込み＆画面構築
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	cp_datawork	データワーク
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundLoadRes( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, const ZKN_SOUND_WORK* cp_datawork, int heap )
{
	
	// BG設定
	ZknSoundSetUpBg( p_drawglb, cp_glb, heap );


	// OAMリソース読み込み
	ZknSoundOamResLoad( p_draw, p_drawglb, heap );

	// アクター登録
	ZknSoundOamInit( p_draw, p_drawglb, heap );

	// FONTOAM
	ZknSoundFontOamInit( p_draw, p_drawglb, cp_glb, heap );

	// ポケグラON
	ZknSoundPokeGraOn( p_drawglb, cp_glb );

	// スクロール設定
	ZknSoundBmpScrollSetUp( p_draw, p_drawglb );

	// グラフ初期化
	ZknSoundGraphInit( p_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	Resource破棄
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundDeleteRes( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb )
{
	// FONTOAM
	ZknSoundFontOamDelete( p_draw );
	
	// アクター破棄
	ZknSoundOamDelete( p_draw );

	// OAMリソース破棄
	ZknSoundOamResDelete( p_draw, p_drawglb );

	// BG設定リセット
	ZknSoundPutBackBg( p_drawglb );
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	背景面セット	
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSetUpBg( ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// キャラクタデータ転
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_main_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, 0, 0, TRUE, heap );
	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_voice_bg_main1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG面を元に戻す
 *
 *	@param	p_drawglb
 *	@param	cp_glb 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundPutBackBg( ZKN_SOUND_DRAWGLB* p_drawglb )
{
	GF_BGL_ScrollReq( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M, GF_BGL_SCROLL_X_SET, 0 );

	// 描画エリアのキャラクタを初期化
	GF_BGL_BmpWinFill( &p_drawglb->p_drawglb->bmp_mfont,
			0 , 
			0,
			0,
			256,
			192 );
	

	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );

	GF_BGL_BmpWinSet_Pal( &p_drawglb->p_drawglb->bmp_mfont, ZKN_BG_FONT_COLOR );
}


//----------------------------------------------------------------------------
/**
 *	@brief	OAMResource読み込み
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundOamResLoad(  ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );

	// キャラクタデータ読み込み
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_voice_oam_main_lzh_NCGR, TRUE,
			NARC_zukan_zkn_voice_oam_main_lzh_NCGR + ZKN_SOUND_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_voice_oam_main_NCLR, FALSE, 
			NARC_zukan_zkn_voice_oam_main_NCLR + ZKN_SOUND_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_SOUND_PLTT_LOAD, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// セルデータ読み込み
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_voice_oam_main_lzh_NCER, TRUE,
			NARC_zukan_zkn_voice_oam_main_lzh_NCER + ZKN_SOUND_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_voice_oam_main_lzh_NANR, TRUE,
			NARC_zukan_zkn_voice_oam_main_lzh_NANR + ZKN_SOUND_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMResource破棄
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundOamResDelete( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;

	CLACT_U_CharManagerDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw->res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->res_obj[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMアクターバッファ作成
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundOamInit( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i, j;
	
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_voice_oam_main_lzh_NCGR + ZKN_SOUND_RES_ID,
			NARC_zukan_zkn_voice_oam_main_NCLR + ZKN_SOUND_RES_ID, 
			NARC_zukan_zkn_voice_oam_main_lzh_NCER + ZKN_SOUND_RES_ID,
			NARC_zukan_zkn_voice_oam_main_lzh_NANR + ZKN_SOUND_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_SOUND_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_SOUND_OAM_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	add.mat.x		= 0;
	add.mat.y		= 0;

	// 全グラフアクター生成
	for( i=0; i<ZKN_SOUND_GRAPH_NUM; i++ ){

		for( j=0; j<ZKN_SOUND_GRAPH_ZANZOU_NUM; j++ ){
			p_draw->snd_graph_act[ i ].zanzou[ j ].act = CLACT_AddSimple( &add );
		}
		p_draw->snd_graph_act[ i ].top.act = CLACT_AddSimple( &add );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMアクターバッファ破棄
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundOamDelete( ZKN_SOUND_DRAW* p_draw )
{
	int i, j;

	// 全グラフアクター生成
	for( i=0; i<ZKN_SOUND_GRAPH_NUM; i++ ){

		for( j=0; j<ZKN_SOUND_GRAPH_ZANZOU_NUM; j++ ){
			CLACT_Delete( p_draw->snd_graph_act[ i ].zanzou[ j ].act );
		}
		CLACT_Delete( p_draw->snd_graph_act[ i ].top.act );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM作成
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	p_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundFontOamInit( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, int heap )
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM破棄
 *
 *	@param	p_draw 描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundFontOamDelete( ZKN_SOUND_DRAW* p_draw )
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	チック数取得
 *
 *	@param	p_work	ワーク
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundGetTich( ZKN_SOUND_WORK* p_work, ZKN_SOUND_GLB* p_glb )
{
	int pitch = ZKN_SoundSubAplGetPitchNum( p_glb->p_sub_sound );
	
	// チック数取得
	p_work->tick = Snd_ZukanPlayerGetSampleTick( SND_HANDLE_PMVOICE, p_work->cp_snd_data, pitch );
}


//----------------------------------------------------------------------------
/**
 *	@brief	波形データをビットマップに書く
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_snd_data	音データ
 *	@param	start		描画データ配列開始位置
 *	@param	end			描画データ配列終了位置
 *	@param	draw_xnum	描画するｘ値		この数横に書きたい
 *	@param	x			描画ｘ座標
 *	@param	def_y		デフォルトY位置
 *	@param	p_set_y		最後に設定したY座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundBmpDraw( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const SNDWaveData* cp_snd_data, int start, int end, int draw_xnum, int x, int def_y, int* p_set_y )
{
	const u8* p_snd_wave = Snd_WaveDataSampleAdrsGet( cp_snd_data );
	int i;
	int arry_idx;		// 参照配列インデックス
	int arry_num;		// 配列要素数

	// 描画エリアのキャラクタを初期化
	GF_BGL_BmpWinFill( &p_drawglb->p_drawglb->bmp_mfont,
			0 , x,
			def_y - ZKN_SOUND_DRAW_BMP_Y_MAX,
			ZKN_SOUND_DRAW_BMP_ONE_SIZE_X * (draw_xnum),
			ZKN_SOUND_DRAW_BMP_Y_MAX * 2 );
	
	arry_num = end - start;
	
	for( i=0; i<draw_xnum; i++ ){
		arry_idx = FX_Mul( arry_num << FX32_SHIFT, i << FX32_SHIFT );
		arry_idx = FX_Div( arry_idx, draw_xnum << FX32_SHIFT ) >> FX32_SHIFT;
		
		
		arry_idx += start;

		ZknSoundBmpDrawOne( &p_drawglb->p_drawglb->bmp_mfont, 
				p_snd_wave[ arry_idx ], x, def_y, p_set_y );

		x += ZKN_SOUND_DRAW_BMP_ONE_SIZE_X;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	１つのデータをビットマップに書き込む
 *
 *	@param	p_bmp
 *	@param	data
 *	@param	x
 *	@param	def_y
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundBmpDrawOne( GF_BGL_BMPWIN* p_bmp, u8 data, int x, int def_y, int* p_set_y )
{
	int y;
	int draw_st_y;
	int draw_y, draw_y2;

	// y座標に変更
	if( data > 127 ){
		y = data - 255;
	}else{
		y = data;
	}

	if( y != 0 ){
		// 高さをあわせる		-32～32の値に変更
		y = FX_Mul( ZKN_SOUND_DRAW_BMP_Y_MAX << FX32_SHIFT, y << FX32_SHIFT );	
		y = FX_Div( y, 127 << FX32_SHIFT ) >> FX32_SHIFT;
	}

	//　描画縦数　と描画開始座標取得
	draw_y = (def_y + y);
	draw_y2 = (def_y + (*p_set_y));
	if( draw_y > draw_y2 ){

		draw_st_y = draw_y2;

		draw_y = draw_y - draw_y2;		
		
	}else{
		draw_st_y = draw_y;

		draw_y = draw_y2 - draw_y;		
	}
	draw_y ++;
	draw_y *= ZKN_SOUND_DRAW_BMP_ONE_SIZE_Y;

	GF_BGL_BmpWinFill( p_bmp, ZKN_SOUND_DRAW_BMP_PL, x, draw_st_y, ZKN_SOUND_DRAW_BMP_ONE_SIZE_X, draw_y );

	// 今設定した点を保存
	*p_set_y = y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ダミーデータを描画する
 *
 *	@param	p_drawglb
 *	@param	start
 *	@param	end
 *	@param	x
 *	@param	def_y 
 *	@param	p_set_y
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundBmpDammyDraw( ZKN_SOUND_DRAWGLB* p_drawglb, int start, int end, int x, int def_y, int* p_set_y )
{
	int i;
	
	// 描画エリアのキャラクタを初期化
	GF_BGL_BmpWinFill( &p_drawglb->p_drawglb->bmp_mfont,
			0, x, def_y - ZKN_SOUND_DRAW_BMP_Y_MAX,
			ZKN_SOUND_DRAW_BMP_ONE_SIZE_X * (end - start),
			ZKN_SOUND_DRAW_BMP_Y_MAX * 2 );
	
	for( i=start; i<end; i++ ){
		ZknSoundBmpDrawOne( &p_drawglb->p_drawglb->bmp_mfont, 
				0, x, def_y, p_set_y );

		x += ZKN_SOUND_DRAW_BMP_ONE_SIZE_X;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップウィンドウのスクロール制御
 *
 *	@param	p_draw
 *	@param	p_drawglb
 *	@param	cp_work 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundBmpScroll( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_WORK* cp_work )
{
	int draw_x;

	// 一定スピードでスクロール
	p_draw->scrl_num += ZKN_SOUND_SCRL_BMP_SPEED;
	p_draw->scrl_num %= 256;

	// 描画開始位置決定
	draw_x = p_draw->scrl_num - (ZKN_SOUND_SCRL_BMP_SPEED * 2);
	if( draw_x < 0 ){
		draw_x += 256;
	}

	// スクロール座標とスピードから波形データ描画
	if( p_draw->last_tick != cp_work->tick ){
		ZknSoundBmpDraw( p_draw, p_drawglb, 
				cp_work->cp_snd_data, 
				p_draw->last_tick, cp_work->tick, ZKN_SOUND_SCRL_BMP_SPEED,
				draw_x, ZKN_SOUND_DRAW_BMP_DEF_Y, &p_draw->last_y );
	}else{
		ZknSoundBmpDammyDraw( p_drawglb, 
				0, ZKN_SOUND_SCRL_BMP_SPEED,
				draw_x, ZKN_SOUND_DRAW_BMP_DEF_Y, &p_draw->last_y );
	}

	// スクロール設定
	GF_BGL_ScrollReq( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M, GF_BGL_SCROLL_X_SET, p_draw->scrl_num );
	
	// CG転送設定
	GF_BGL_BmpWinOnVReq( &p_drawglb->p_drawglb->bmp_mfont );

	// チック保存
	p_draw->last_tick = cp_work->tick;
}

//----------------------------------------------------------------------------
/**
 *	@brief	鳴き声波形データの初期化
 *
 *	@param	p_draw		描画ワーク	
 *	@param	p_drawglb	描画グローバル
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundBmpScrollSetUp( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb )
{
	GF_BGL_BmpWinSet_Pal( &p_drawglb->p_drawglb->bmp_mfont, ZKN_SOUND_DRAW_BMP_PL_TBL );
	
	ZknSoundBmpDammyDraw( p_drawglb, 
			0, 256,
			0, ZKN_SOUND_DRAW_BMP_DEF_Y, &p_draw->last_y );
	
	GF_BGL_BmpWinOn( &p_drawglb->p_drawglb->bmp_mfont );
}

//----------------------------------------------------------------------------
/**
 *	@brief	グラフのデータ全部初期化
 *
 *	@param	p_draw 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundGraphInit( ZKN_SOUND_DRAW* p_draw )
{
	int i;

	// グラフデータ初期化
	for( i=0; i<ZKN_SOUND_GRAPH_NUM; i++ ){
		ZknSoundGraphInitData( &p_draw->snd_graph_act[i], i );
	}
}

//----------------------------------------------------------------------------
/**	
 *	@brief	グラフ動作
 *
 *	@param	p_draw	描画ワーク
 *	@param	cp_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundGraphMove( ZKN_SOUND_DRAW* p_draw, const ZKN_SOUND_WORK* cp_work )
{
	int i;

	// グラフデータ動作
	for( i=0; i<ZKN_SOUND_GRAPH_NUM; i++ ){
		ZknSoundGraphMoveData( &p_draw->snd_graph_act[i], cp_work->snd_graph_data[ i ] );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	グラフデータ初期化
 *
 *	@param	p_data	データ
 *	@param	x_num	ｘ要素数	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundGraphInitData( ZKN_GRAPH_ONE_DATA* p_data, int x_num )
{
	int i;
	VecFx32 mat;

	// 座標を設定＆非表示にする
	mat.x = (ZKN_SOUND_GRAPH_MAT_DEF_X + ( ZKN_SOUND_GRAPH_MAT_OFS_X*x_num )) << FX32_SHIFT;
	mat.y = ZKN_SOUND_GRAPH_MAT_DEF_Y << FX32_SHIFT;
	for( i=0; i<ZKN_SOUND_GRAPH_ZANZOU_NUM; i++ ){
		CLACT_SetMatrix( p_data->zanzou[ i ].act, &mat );
		CLACT_SetDrawFlag( p_data->zanzou[ i ].act, FALSE );
		mat.y += ZKN_SOUND_GRAPH_MAT_OFS_Y << FX32_SHIFT;
		CLACT_AnmChg( p_data->zanzou[ i ].act, 1 );
	}

	// 先頭のアクターの座標と初期ワークを設定
	mat.y = ZKN_SOUND_GRAPH_MAT_DEF_Y << FX32_SHIFT;
	CLACT_SetMatrix( p_data->top.act, &mat );
	CLACT_SetDrawFlag( p_data->top.act, FALSE );
}


//----------------------------------------------------------------------------
/**
 *	@brief	グラフ動作
 *
 *	@param	p_data	グラフデータ
 *	@param	level	今のレベル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundGraphMoveData( ZKN_GRAPH_ONE_DATA* p_data, int level )
{
	int i;
	int now_max_level = 0;
	
	// levelによる各ワークの設定
	for( i=0; i<level; i++ ){
		CLACT_SetDrawFlag( p_data->zanzou[i].act, TRUE );
		p_data->zanzou[i].dess_count = ZKN_SOUND_GRAPH_DES_COUNT * (i + 1);
	}

	// 残像動作
	for( i=0; i<ZKN_SOUND_GRAPH_ZANZOU_NUM; i++ ){
		// 描画しているなら
		// 破棄カウンタが0になるまで描画する
		if( CLACT_GetDrawFlag( p_data->zanzou[i].act ) ){
			if( (p_data->zanzou[i].dess_count - 1) > 0 ){
				p_data->zanzou[i].dess_count--;
				now_max_level = i + 1;	// 今の最大レベル
			}else{

				CLACT_SetDrawFlag( p_data->zanzou[i].act, FALSE );
			}

		}
	}
	
	// levelの座標に頂点を持っていく
	if( p_data->top.level <= now_max_level ){
		
		ZknSoundGraphSetLevelMatrixTop( p_data->top.act, now_max_level );
		p_data->top.down_count = ZKN_SOUND_GRAPH_DOWN_COUNT;

		// こうすることにより一番下の時は０でも非表示で
		// なにか上昇するときにのみ描画開始という処理になるはず
		if( p_data->top.level < now_max_level ){
			// 表示に
			CLACT_SetDrawFlag( p_data->top.act, TRUE );
		}

		p_data->top.level = now_max_level;

	}



	// 先頭動作
	if( p_data->top.level > 0 ){

		// ダウンカウントが0より小さくなったら落ちていく
		if( p_data->top.down_count < 0 ){
			p_data->top.level --;
			ZknSoundGraphSetLevelMatrixTop( p_data->top.act, p_data->top.level );
		}else{
			p_data->top.down_count --;
		}
	}else{

		// 非表示に
		CLACT_SetDrawFlag( p_data->top.act, FALSE );
	}
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクターに引数レベルのY座標を設定する
 *
 *	@param	act
 *	@param	level 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundGraphSetLevelMatrixTop( CLACT_WORK_PTR act, int level )
{
	VecFx32 mat;
	const VecFx32* cp_mat;
	
	cp_mat = CLACT_GetMatrix( act );
	mat = *cp_mat;
	mat.y = (ZKN_SOUND_GRAPH_MAT_DEF_Y + ( ZKN_SOUND_GRAPH_MAT_OFS_Y*level)) << FX32_SHIFT;
	CLACT_SetMatrix( act, &mat );
}

//----------------------------------------------------------------------------
/**
 *	@brief	棒線グラフデータ取得関数
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバルデータ
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundGraphLevelSet( ZKN_SOUND_WORK* p_work, ZKN_SOUND_GLB* p_glb )
{
	int pitch = ZKN_SoundSubAplGetPitchNum( p_glb->p_sub_sound );
	
	memset( p_work->snd_graph_data, 0, sizeof(u8)* ZKN_SOUND_GRAPH_NUM);

	if( Snd_PMVoicePlayCheck() != 0 ){	// 再生中のみ取得
		Snd_ZukanWaveLevelSet_New( p_work->cp_snd_data, p_work->snd_graph_data, ZKN_SOUND_GRAPH_NUM, pitch );
	}
}
