//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_big_debug_sub.c
 *	@brief		高さ比べDEBUGアプリ
 *	@author		tomoya takahashi
 *	@data		2006.03.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#ifdef PM_DEBUG

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"

#include "include/gflib/vram_transfer_manager.h"
#include "include/system/brightness.h"
#include "include/system/arc_tool.dat"
#include "include/system/arc_util.h"
#include "include/system/clact_util.h"
#include "include/application/zukanlist/zukan.naix"
#include "include/gflib/button_man.h"
#include "include/system/fontproc.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_debug_zukan.h"
#include "include/msgdata/msg_zkn.h"

#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_big.h"

#define	__ZKN_BIG_DEBUG_DEBUG_H_GLOBAL
#include "include/application/zukanlist/zkn_big_debug_sub.h"

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
#define ZKN_BIG_DEBUG_EVENT_NUM ( 2 )	// イベント数
#define ZKN_BIG_DEBUG_EVENT_CHANGE_HEIGHT		(1<<0)
#define ZKN_BIG_DEBUG_EVENT_CHANGE_HEIGHT_ALL	(2<<0)

#define ZKN_BIG_DEBUG_OAM_BG_PTR	( 2 )

enum{
	ZKN_BIGDEBUG_SEQINIT_ALLOC,
	ZKN_BIGDEBUG_SEQINIT_LOAD,
	ZKN_BIGDEBUG_SEQINIT_FADEIN,
	ZKN_BIGDEBUG_SEQINIT_END,
};
enum{
	ZKN_BIGDEBUG_SEQDELETE_FADEOUT_INIT,
	ZKN_BIGDEBUG_SEQDELETE_FADEOUT,
	ZKN_BIGDEBUG_SEQDELETE_RELEASE,
	ZKN_BIGDEBUG_SEQDELETE_FREE,
	ZKN_BIGDEBUG_SEQDELETE_END,
};

//-------------------------------------
//	選択ﾀｲﾌﾟ
//=====================================
enum{
	ZKN_BIGDEBUG_SELE_POKE,
	ZKN_BIGDEBUG_SELE_HERO,
	ZKN_BIGDEBUG_SELE_NUM,
};


//-------------------------------------
//	ビットマップウィンドウ
//=====================================
enum{
	ZKN_BIGDEBUG_WND_POKEGRA_DATA,
	ZKN_BIGDEBUG_WND_HERO_DATA,
	ZKN_BIGDEBUG_WND_CONT_DATA,
	ZKN_BIGDEBUG_WND_NOW_POKE_DATA,
	ZKN_BIGDEBUG_WND_NUM
};

#define ZKN_BIGDEBUG_BMPWND_PL			( 0 )
#define ZKN_BIGDEBUG_STRNUM				( 512 )
#define ZKN_BIGDEBUG_STRNUM_KETA		( 4 )

//-------------------------------------
//	ポケモングラフィックﾃﾞｰﾀ用
//=====================================
#define ZKN_BIGDEBUG_POKEGRA_DATA_CX	( 1 )
#define ZKN_BIGDEBUG_POKEGRA_DATA_CY	( 18 )
#define ZKN_BIGDEBUG_POKEGRA_DATA_CSIZX	( 15 )
#define ZKN_BIGDEBUG_POKEGRA_DATA_CSIZY	( 6 )
#define ZKN_BIGDEBUG_POKEGRA_DATA_CGOFS	( 1 )

// 共通
#define ZKN_BIGDEBUG_POKEHERO_NAME_X	( 0 )
#define ZKN_BIGDEBUG_POKEHERO_HIRITSU_X	( 0 )
#define ZKN_BIGDEBUG_POKEHERO_TAKASA_X	( 64 )
#define ZKN_BIGDEBUG_POKEHERO_NUM_Y		( 32 )
#define ZKN_BIGDEBUG_POKEHERO_STR_Y		( 16 )
#define ZKN_BIGDEBUG_POKEHERO_NAME_Y	( 0 )

//-------------------------------------
//	主人公ﾃﾞｰﾀ用
//=====================================
#define ZKN_BIGDEBUG_HERO_DATA_CX	( 16 )
#define ZKN_BIGDEBUG_HERO_DATA_CY	( 18 )
#define ZKN_BIGDEBUG_HERO_DATA_CSIZX	( 15 )
#define ZKN_BIGDEBUG_HERO_DATA_CSIZY	( 6 )
#define ZKN_BIGDEBUG_HERO_DATA_CGOFS	( 100 )

//-------------------------------------
//	操作方法ﾃﾞｰﾀ用
//=====================================
#define ZKN_BIGDEBUG_CONT_DATA_CX	( 1 )
#define ZKN_BIGDEBUG_CONT_DATA_CY	( 0 )
#define ZKN_BIGDEBUG_CONT_DATA_CSIZX	( 20 )
#define ZKN_BIGDEBUG_CONT_DATA_CSIZY	( 18 )
#define ZKN_BIGDEBUG_CONT_DATA_CGOFS	( 200 )

//-------------------------------------
//	編集中ﾃﾞｰﾀ用
//=====================================
#define ZKN_BIGDEBUG_NOW_POKE_DATA_CX	( 19 )
#define ZKN_BIGDEBUG_NOW_POKE_DATA_CY	( 10 )
#define ZKN_BIGDEBUG_NOW_POKE_DATA_CSIZX	( 12 )
#define ZKN_BIGDEBUG_NOW_POKE_DATA_CSIZY	( 4 )
#define ZKN_BIGDEBUG_NOW_POKE_DATA_CGOFS	( 600 )

#define ZKN_BIGDEBUG_NOW_POKE_DATA_STR_Y	( 16 )


//-------------------------------------
//	操作系
//=====================================
#define ZKN_BIGDEBUG_CONT_TRG_TIME		( 16 )

#define ZKN_BIGDEBUG_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	おおきさくらべサブ画面　グローバル変数
//=====================================
typedef struct {
	int* p_event_key;

	ZKN_GLB_DATA* p_glb;

	// 高さ比べアプリ
	ZKN_APL_DATA* p_height_apl;
} ZKN_BIG_DEBUG_GLB;

//-------------------------------------
//	大きさぐらべサブ画面画面　描画グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA* p_drawglb;
} ZKN_BIG_DEBUG_DRAWGLB;

//-------------------------------------
//	おおきさくらべサブ画面　内部ワーク
//=====================================
typedef struct {
	short scale[ZKN_BIGDEBUG_SELE_NUM];
	short yofs[ZKN_BIGDEBUG_SELE_NUM];

	int now_select;

	int trg_count;		// trgボタンでいるｶｳﾝﾀ
} ZKN_BIG_DEBUG_WORK;

//-------------------------------------
//	おおきさくらべサブ画面画面　内部ワーク
//=====================================
typedef struct {
	GF_BGL_BMPWIN* p_bmp[ZKN_BIGDEBUG_WND_NUM];

	int local_now_select;

	short local_scale[ZKN_BIGDEBUG_SELE_NUM];
	short local_yofs[ZKN_BIGDEBUG_SELE_NUM];
} ZKN_BIG_DEBUG_DRAW;


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
static ZKN_BIG_DEBUG_GLB* MakeBigDebugGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_BIG_DEBUG_DRAWGLB* MakeBigDebugDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeBigDebugEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteBigDebugGlb( ZKN_BIG_DEBUG_GLB* p_glb );
static void DeleteBigDebugDrawGlb( ZKN_BIG_DEBUG_DRAWGLB* p_glb );
static void DeleteBigDebugEvent( ZKN_EVENT_DATA* p_event );


static int BigDebugEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
static int ZknBigDebugProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigDebugProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigDebugProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigDebugProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknBigDebugProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknBigDebugProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

// フェード処理
static void ZknBigDebugOamFadeInit( ZKN_BIG_DEBUG_DRAW* p_draw );
static void ZknBigDebugOamFadeDelete( ZKN_BIG_DEBUG_DRAW* p_draw );
static void ZknBigDebugFadeInit( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, const ZKN_BIG_DEBUG_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknBigDebugFadeMain( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, const ZKN_BIG_DEBUG_GLB* cp_glb, BOOL fadein_out );

static void ZknBigDebugObjDataReset( ZKN_BIG_DEBUG_WORK* p_work );


// 読み込み
static void ZknBigDebugLoadResource( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, const ZKN_BIG_DEBUG_GLB* cp_glb, const ZKN_BIG_DEBUG_WORK* cp_work, int heap );
static void ZknBigDebugReleaseResource( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, int heap );


static void ZknBigDebugInitBmp( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, int heap );
static void ZknBigDebugDeleteBmp( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb );

static void ZknBigDebugDrawHeroBmp( GF_BGL_BMPWIN* p_bmp, const ZKN_BIG_DEBUG_GLB* cp_glb, const ZKN_BIG_DEBUG_WORK* cp_work, int heap );
static void ZknBigDebugDrawPokeBmp( GF_BGL_BMPWIN* p_bmp, const ZKN_BIG_DEBUG_GLB* cp_glb, const ZKN_BIG_DEBUG_WORK* cp_work, int heap );
static void ZknBigDebugDrawContBmp( GF_BGL_BMPWIN* p_bmp, int heap );
static void ZknBigDebugDrawSelectBmp( GF_BGL_BMPWIN* p_bmp, const ZKN_BIG_DEBUG_GLB* cp_glb, const ZKN_BIG_DEBUG_WORK* cp_work, int heap );

static void ZknBigDebugOneParamDataPrint( GF_BGL_BMPWIN* p_bmp, short yofs, short scale, STRBUF* str, MSGDATA_MANAGER* man, STRBUF* name );

static void ZknBigDebug0xNumMake( GF_BGL_BMPWIN* p_bmp, u32 x, u32 y, STRBUF* str, u32 num, u32 keta, MSGDATA_MANAGER* man, u32 start_msg_idx );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	おおきさくらべサブ画面　アプリ作成
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
void ZKN_BigDebugAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_BIG_DEBUG_GLB*	p_glb;
	ZKN_BIG_DEBUG_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeBigDebugGlb( heap, zkn_sys );
	p_drawglb = MakeBigDebugDrawGlb( heap, zkn_sys );
	p_event = MakeBigDebugEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= BigDebugEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknBigDebugProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknBigDebugProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknBigDebugProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknBigDebugProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknBigDebugProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknBigDebugProcDrawFuncDelete;
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
void ZKN_BigDebugAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteBigDebugGlb( p_data->p_glb_data ); 
	DeleteBigDebugDrawGlb( p_data->p_glb_draw ); 
	DeleteBigDebugEvent( p_data->p_event_data );
}


//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	おおきさくらべサブ画面　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_BIG_DEBUG_GLB* MakeBigDebugGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_BIG_DEBUG_GLB* p_glb;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_BIG_DEBUG_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_BIG_DEBUG_GLB) );

	// 変数初期化
	// イベントキー
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrSub( zkn_sys );		

	// グローバルデータ
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );


	// 図鑑高さくらべ アプリ
	p_glb->p_height_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_BIG );
	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	おおきさくらべサブ画面　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_BIG_DEBUG_DRAWGLB* MakeBigDebugDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_BIG_DEBUG_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_BIG_DEBUG_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_BIG_DEBUG_DRAWGLB) );


	// 描画データ
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	おおきさくらべサブ画面　イベント作成
 *
 *	@param	heap		使用するヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	イベントデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeBigDebugEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = BigDebugEventDataNumGet();

	// イベントデータテーブル作成
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_MakeChangeBigMain( heap, &p_event_tbl[0], zkn_sys, ZKN_BIG_DEBUG_EVENT_CHANGE_HEIGHT );
	ZKN_EVENT_BigHeightDebugAplReturn( &p_event_tbl[1], zkn_sys, heap, ZKN_BIG_DEBUG_EVENT_CHANGE_HEIGHT_ALL );

	return p_event_tbl;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	おおきさくらべサブ画面　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteBigDebugGlb( ZKN_BIG_DEBUG_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	おおきさくらべサブ画面　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteBigDebugDrawGlb( ZKN_BIG_DEBUG_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	おおきさくらべサブ画面　イベントデータ破棄
 *
 *	@param	p_event	イベントデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteBigDebugEvent( ZKN_EVENT_DATA* p_event )
{
	GF_ASSERT( p_event );
	
	ZKN_EVENT_DeleteData( &p_event[0] );
	ZKN_EVENT_DeleteData( &p_event[1] );

	sys_FreeMemoryEz( p_event );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	おおきさくらべサブ画面アプリ　イベント数取得
 *	
 *	@param	none	
 *
 *	@return	おおきさくらべサブ画面アプリ　イベント数
 *
 *
 */
//-----------------------------------------------------------------------------
static int BigDebugEventDataNumGet( void )
{
	return ZKN_BIG_DEBUG_EVENT_NUM;
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
static int ZknBigDebugProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_BIG_DEBUG_GLB* p_glb = p_glbdata;
	ZKN_BIG_DEBUG_WORK* p_work = p_dodata->p_work;
	int i;

	// ワークの作成
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_BIG_DEBUG_WORK) );
	memset( p_work, 0, sizeof(ZKN_BIG_DEBUG_WORK) );

	ZknBigDebugObjDataReset( p_work );
	
	p_dodata->p_work = p_work;

	p_work->trg_count = ZKN_BIGDEBUG_CONT_TRG_TIME;

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
static int ZknBigDebugProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{

	ZKN_BIG_DEBUG_GLB* p_glb = p_glbdata;
	ZKN_BIG_DEBUG_WORK* p_work = p_dodata->p_work;
	
	// 終了へ
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}


	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}


	// トリガー　コント　カウント処理
	if( sys.cont != 0 ){
		if( (p_work->trg_count - 1) >= 0 ){
			p_work->trg_count --;
		}
	}else{
		p_work->trg_count = ZKN_BIGDEBUG_CONT_TRG_TIME;
	}


	// 選択の変更
	if( sys.trg & PAD_BUTTON_A ){
		p_work->now_select ^= 1;
	}

	// トリガー検出するか　チェック
	if( p_work->trg_count == 0 ){

		// 拡縮
		if( sys.cont & PAD_KEY_LEFT ){
			p_work->scale[ p_work->now_select ] ++;
		}
		if( sys.cont & PAD_KEY_RIGHT ){
			p_work->scale[ p_work->now_select ] --;
		}

		// Y位置
		if( sys.cont & PAD_KEY_UP ){
			p_work->yofs[ p_work->now_select ] --;
		}
		if( sys.cont & PAD_KEY_DOWN ){
			p_work->yofs[ p_work->now_select ] ++;
		}
	}else{
		// 拡縮
		if( sys.trg & PAD_KEY_LEFT ){
			p_work->scale[ p_work->now_select ] ++;
		}
		if( sys.trg & PAD_KEY_RIGHT ){
			p_work->scale[ p_work->now_select ] --;
		}

		// Y位置
		if( sys.trg & PAD_KEY_UP ){
			p_work->yofs[ p_work->now_select ] --;
		}
		if( sys.trg & PAD_KEY_DOWN ){
			p_work->yofs[ p_work->now_select ] ++;
		}
	}

	// 次のポケモン
	if( sys.trg & PAD_BUTTON_L ){
		if( ZKN_GLBDATA_PokeListTblNoAdd( p_glb->p_glb, 1 ) == FALSE ){
			ZKN_GLBDATA_PokeListTblNoSet( p_glb->p_glb, 0 );
		}
		*p_glb->p_event_key |= ZKN_BIG_DEBUG_EVENT_CHANGE_HEIGHT;
		ZknBigDebugObjDataReset( p_work );
	}

	// 前のポケモン
	if( sys.trg & PAD_BUTTON_R ){
		if( ZKN_GLBDATA_PokeListTblNoAdd( p_glb->p_glb, -1 ) == FALSE ){
			ZKN_GLBDATA_PokeListTblNoSet( p_glb->p_glb, ZKN_GLBDATA_PokeListTblNumGet( p_glb->p_glb ) - 1 );
		}
		*p_glb->p_event_key |= ZKN_BIG_DEBUG_EVENT_CHANGE_HEIGHT;
		ZknBigDebugObjDataReset( p_work );
	}

	// 男女
	if( sys.trg & PAD_BUTTON_SELECT ){
		p_glb->p_glb->hero_sex ^= 1;
		*p_glb->p_event_key |= ZKN_BIG_DEBUG_EVENT_CHANGE_HEIGHT;
		ZknBigDebugObjDataReset( p_work );
	}

	// 終了
	if( sys.trg & PAD_BUTTON_B ){
		*p_glb->p_event_key |= ZKN_BIG_DEBUG_EVENT_CHANGE_HEIGHT_ALL;
	}

	// 値反映
	ZKN_BigAplPokeGraScaleSet( p_glb->p_height_apl, p_work->scale[ ZKN_BIGDEBUG_SELE_POKE ] );
	ZKN_BigAplHeroGraScaleSet( p_glb->p_height_apl, p_work->scale[ ZKN_BIGDEBUG_SELE_HERO ] );
	ZKN_BigAplPokeGraYofsSet( p_glb->p_height_apl, p_work->yofs[ ZKN_BIGDEBUG_SELE_POKE ] );
	ZKN_BigAplHeroGraYofsSet( p_glb->p_height_apl, p_work->yofs[ ZKN_BIGDEBUG_SELE_HERO ] );


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
static int ZknBigDebugProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_BIG_DEBUG_GLB* p_glb = p_glbdata;
	ZKN_BIG_DEBUG_WORK* p_work = p_dodata->p_work;

	// ワーク破棄
	sys_FreeMemoryEz( p_work );

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
static int ZknBigDebugProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_DEBUG_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_DEBUG_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_DEBUG_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_BIG_DEBUG_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_BIGDEBUG_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_BIG_DEBUG_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_BIG_DEBUG_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIGDEBUG_SEQINIT_LOAD:
		// Resource読み込み
		ZknBigDebugLoadResource( p_drawwork, p_drawglb, cp_dataglb, cp_datawork, p_drawdata->heap );
 
		// フェード処理
		ZknBigDebugFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_BIGDEBUG_SEQINIT_FADEIN:
		
		if( ZknBigDebugFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_BIGDEBUG_SEQINIT_END:
		return ZKN_PROC_TRUE;
		
	default:
		break;
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
static int ZknBigDebugProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_DEBUG_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_DEBUG_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_DEBUG_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_BIG_DEBUG_DRAW*		p_drawwork = p_drawdata->p_work;

	
	// ビットマップ描画
	// ポケモンﾃﾞｰﾀ	
	if( (p_drawwork->local_scale[ ZKN_BIGDEBUG_SELE_POKE ] != cp_datawork->scale[ ZKN_BIGDEBUG_SELE_POKE ]) ||
		(p_drawwork->local_yofs[ ZKN_BIGDEBUG_SELE_POKE ] != cp_datawork->yofs[ ZKN_BIGDEBUG_SELE_POKE ]) ){
		ZknBigDebugDrawPokeBmp( p_drawwork->p_bmp[ ZKN_BIGDEBUG_WND_POKEGRA_DATA ], cp_dataglb, cp_datawork, p_drawdata->heap );

		p_drawwork->local_scale[ ZKN_BIGDEBUG_SELE_POKE ] = cp_datawork->scale[ ZKN_BIGDEBUG_SELE_POKE ];
		p_drawwork->local_yofs[ ZKN_BIGDEBUG_SELE_POKE ] = cp_datawork->yofs[ ZKN_BIGDEBUG_SELE_POKE ];
	}

	// 主人公ﾃﾞｰﾀ
	if( (p_drawwork->local_scale[ ZKN_BIGDEBUG_SELE_HERO ] != cp_datawork->scale[ ZKN_BIGDEBUG_SELE_HERO ]) ||
		(p_drawwork->local_yofs[ ZKN_BIGDEBUG_SELE_HERO ] != cp_datawork->yofs[ ZKN_BIGDEBUG_SELE_HERO ]) ){
		ZknBigDebugDrawHeroBmp( p_drawwork->p_bmp[ ZKN_BIGDEBUG_WND_HERO_DATA ], cp_dataglb, cp_datawork, p_drawdata->heap );

		p_drawwork->local_scale[ ZKN_BIGDEBUG_SELE_HERO ] = cp_datawork->scale[ ZKN_BIGDEBUG_SELE_HERO ];
		p_drawwork->local_yofs[ ZKN_BIGDEBUG_SELE_HERO ] = cp_datawork->yofs[ ZKN_BIGDEBUG_SELE_HERO ];
	}

	// 選択データ
	if( p_drawwork->local_now_select != cp_datawork->now_select ){

		ZknBigDebugDrawSelectBmp( p_drawwork->p_bmp[ ZKN_BIGDEBUG_WND_NOW_POKE_DATA ], cp_dataglb, cp_datawork, p_drawdata->heap );
	
		p_drawwork->local_now_select = cp_datawork->now_select;
	}

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
static int ZknBigDebugProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_DEBUG_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_DEBUG_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_DEBUG_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_BIG_DEBUG_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_BIGDEBUG_SEQDELETE_FADEOUT_INIT:
		// フェード処理
		ZknBigDebugFadeInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIGDEBUG_SEQDELETE_FADEOUT:
		if( ZknBigDebugFadeMain( p_drawwork, p_drawglb, cp_dataglb, FALSE ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_BIGDEBUG_SEQDELETE_RELEASE:
		// Resource読み込み
		ZknBigDebugReleaseResource( p_drawwork, p_drawglb, p_drawdata->heap );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIGDEBUG_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
		
	case ZKN_BIGDEBUG_SEQDELETE_END:
		return ZKN_PROC_TRUE;
		
	default:
		break;
	}
	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMフェード処理	初期化
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugOamFadeInit( ZKN_BIG_DEBUG_DRAW* p_draw )
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMフェード処理　後処理
 *
 *	@param	p_draw 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugOamFadeDelete( ZKN_BIG_DEBUG_DRAW* p_draw )
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ画面フェード処理
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	cp_glb		グローバル
 *	@param	fadein_out	フェードイン　TRUE　アウト FALSE	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugFadeInit( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, const ZKN_BIG_DEBUG_GLB* cp_glb, BOOL fadein_out )
{
	// 半透明OAM設定
	ZknBigDebugOamFadeInit( p_draw );


	if( fadein_out ){
		// フェードイン
		ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
				BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_BIGDEBUG_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
	}else{
		// フェードアウト
		ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
				BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_BIGDEBUG_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェード処理　メイン
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	cp_glb		グローバル
 *	@param	fadein_out	フェードイン　TRUE　アウト　FALSE
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL ZknBigDebugFadeMain( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, const ZKN_BIG_DEBUG_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check;

	check = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade_sub );

	// 終わったら終了処理
	if( check ){
		if( fadein_out ){
			// 半透明OAM破棄
			ZknBigDebugOamFadeDelete( p_draw );
		}

		return TRUE;
	}

	return FALSE;
}



//----------------------------------------------------------------------------
/**
 *	@brief	グラフィック初期化処理
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugLoadResource( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, const ZKN_BIG_DEBUG_GLB* cp_glb, const ZKN_BIG_DEBUG_WORK* cp_work, int heap )
{
	// スクリーン初期化
	GF_BGL_ClearCharSet( ZKN_BG_FRM_UTIL_S, 32, 0, heap );
	GF_BGL_ClearCharSet( ZKN_BG_FRM_BACK_S, 32, 0, heap );
	GF_BGL_ClearCharSet( ZKN_BG_FRM_AFFINE_S, 32, 0, heap );
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_S );
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S );
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S );
	
	
	// ビットマップ面
	ZknBigDebugInitBmp( p_draw, p_drawglb, heap );

	// 主人公ﾃﾞｰﾀ表示
	ZknBigDebugDrawHeroBmp( p_draw->p_bmp[ ZKN_BIGDEBUG_WND_HERO_DATA ], cp_glb, cp_work, heap );

	// ポケモンﾃﾞｰﾀ表示
	ZknBigDebugDrawPokeBmp( p_draw->p_bmp[ ZKN_BIGDEBUG_WND_POKEGRA_DATA ], cp_glb, cp_work, heap );

	// 操作方法
	ZknBigDebugDrawContBmp( p_draw->p_bmp[ ZKN_BIGDEBUG_WND_CONT_DATA ], heap );

	// ﾃﾞｰﾀ表示
	// 選択データ
	ZknBigDebugDrawSelectBmp( p_draw->p_bmp[ ZKN_BIGDEBUG_WND_NOW_POKE_DATA ], cp_glb, cp_work, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	グラフィック破棄処理
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugReleaseResource( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, int heap )
{
	// ビットマップ面の破棄
	ZknBigDebugDeleteBmp( p_draw, p_drawglb );
}


//----------------------------------------------------------------------------
/**
 *	@brief	描画用ウィンドウ作成
 *
 *	@param	p_draw
 *	@param	p_drawglb
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugInitBmp( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, int heap )
{
	int i;
	GF_BGL_INI* p_bg = p_drawglb->p_drawglb->p_bg;

	// メモリ確保
	for( i=0; i<ZKN_BIGDEBUG_WND_NUM; i++ ){
		p_draw->p_bmp[ i ] = GF_BGL_BmpWinAllocGet( heap, 1 );
	}


	// 領域確保
	// ﾎﾟｹｸﾞﾗﾃﾞｰﾀ
	GF_BGL_BmpWinAdd( p_bg, p_draw->p_bmp[ ZKN_BIGDEBUG_WND_POKEGRA_DATA ],
			ZKN_BG_FRM_BACK_S,
			ZKN_BIGDEBUG_POKEGRA_DATA_CX, ZKN_BIGDEBUG_POKEGRA_DATA_CY,
			ZKN_BIGDEBUG_POKEGRA_DATA_CSIZX, ZKN_BIGDEBUG_POKEGRA_DATA_CSIZY,
			ZKN_BIGDEBUG_BMPWND_PL, ZKN_BIGDEBUG_POKEGRA_DATA_CGOFS );

	// 主人公ﾃﾞｰﾀ
	GF_BGL_BmpWinAdd( p_bg, p_draw->p_bmp[ ZKN_BIGDEBUG_WND_HERO_DATA ],
			ZKN_BG_FRM_BACK_S,
			ZKN_BIGDEBUG_HERO_DATA_CX, ZKN_BIGDEBUG_HERO_DATA_CY,
			ZKN_BIGDEBUG_HERO_DATA_CSIZX, ZKN_BIGDEBUG_HERO_DATA_CSIZY,
			ZKN_BIGDEBUG_BMPWND_PL, ZKN_BIGDEBUG_HERO_DATA_CGOFS );

	// 操作方法ﾃﾞｰﾀ
	GF_BGL_BmpWinAdd( p_bg, p_draw->p_bmp[ ZKN_BIGDEBUG_WND_CONT_DATA ],
			ZKN_BG_FRM_BACK_S,
			ZKN_BIGDEBUG_CONT_DATA_CX, ZKN_BIGDEBUG_CONT_DATA_CY,
			ZKN_BIGDEBUG_CONT_DATA_CSIZX, ZKN_BIGDEBUG_CONT_DATA_CSIZY,
			ZKN_BIGDEBUG_BMPWND_PL, ZKN_BIGDEBUG_CONT_DATA_CGOFS );

	// 編集中ﾃﾞｰﾀ
	GF_BGL_BmpWinAdd( p_bg, p_draw->p_bmp[ ZKN_BIGDEBUG_WND_NOW_POKE_DATA ],
			ZKN_BG_FRM_BACK_S,
			ZKN_BIGDEBUG_NOW_POKE_DATA_CX, ZKN_BIGDEBUG_NOW_POKE_DATA_CY,
			ZKN_BIGDEBUG_NOW_POKE_DATA_CSIZX, ZKN_BIGDEBUG_NOW_POKE_DATA_CSIZY,
			ZKN_BIGDEBUG_BMPWND_PL, ZKN_BIGDEBUG_NOW_POKE_DATA_CGOFS );
}

//----------------------------------------------------------------------------
/**
 *	@brief	主人公ﾃﾞｰﾀ表示
 *
 *	@param	p_bmp
 *	@param	cp_glb
 *	@param	cp_work
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugDrawHeroBmp( GF_BGL_BMPWIN* p_bmp, const ZKN_BIG_DEBUG_GLB* cp_glb, const ZKN_BIG_DEBUG_WORK* cp_work, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_BIGDEBUG_STRNUM, heap);
	STRBUF* name = STRBUF_Create(ZKN_BIGDEBUG_STRNUM, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_zukan_dat, heap);

	GF_BGL_BmpWinDataFill( p_bmp, 0 );

	// 主人公ﾃﾞｰﾀ書き込み
	if( ZKN_GLBDATA_HeroSexGet( cp_glb->p_glb ) == 0 ){
		MSGMAN_GetString( man, DEBUG_ZUKAN_20, name );
	}else{
		MSGMAN_GetString( man, DEBUG_ZUKAN_03, name );
	}
	ZknBigDebugOneParamDataPrint( p_bmp, 
		cp_work->yofs[ZKN_BIGDEBUG_SELE_HERO], cp_work->scale[ZKN_BIGDEBUG_SELE_HERO],
		str, man, name );
	
	GF_BGL_BmpWinOn( p_bmp );

	STRBUF_Delete(name);
	STRBUF_Delete(str);
	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンﾃﾞｰﾀ表示
 *
 *	@param	p_bmp
 *	@param	cp_glb
 *	@param	cp_work
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugDrawPokeBmp( GF_BGL_BMPWIN* p_bmp, const ZKN_BIG_DEBUG_GLB* cp_glb, const ZKN_BIG_DEBUG_WORK* cp_work, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_BIGDEBUG_STRNUM, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_zukan_dat, heap);
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	STRBUF* mons_name = MSGDAT_UTIL_GetMonsName( monsno, heap );

	GF_BGL_BmpWinDataFill( p_bmp, 0 );

	// ポケモンﾃﾞｰﾀ書き込み
	ZknBigDebugOneParamDataPrint( p_bmp, 
		cp_work->yofs[ZKN_BIGDEBUG_SELE_POKE], cp_work->scale[ZKN_BIGDEBUG_SELE_POKE],
		str, man, mons_name );

	GF_BGL_BmpWinOn( p_bmp );

	STRBUF_Delete(mons_name);
	STRBUF_Delete(str);
	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	操作方法表示
 *
 *	@param	p_bmp
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugDrawContBmp( GF_BGL_BMPWIN* p_bmp, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_BIGDEBUG_STRNUM, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_zukan_dat, heap);

	GF_BGL_BmpWinDataFill( p_bmp, 0 );

	// 操作方法
	MSGMAN_GetString( man, DEBUG_ZUKAN_02, str );
	GF_STR_PrintColor( p_bmp,
			FONT_SYSTEM, str, 0, 0, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	GF_BGL_BmpWinOn( p_bmp );

	STRBUF_Delete(str);
	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	選択方法表示
 *
 *	@param	p_bmp
 *	@param	cp_glb
 *	@param	cp_work
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugDrawSelectBmp( GF_BGL_BMPWIN* p_bmp, const ZKN_BIG_DEBUG_GLB* cp_glb, const ZKN_BIG_DEBUG_WORK* cp_work, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_BIGDEBUG_STRNUM, heap);
	STRBUF* name = STRBUF_Create(ZKN_BIGDEBUG_STRNUM, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_zukan_dat, heap);
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	STRBUF* mons_name = MSGDAT_UTIL_GetMonsName( monsno, heap );

	GF_BGL_BmpWinDataFill( p_bmp, 0 );

	if( ZKN_GLBDATA_HeroSexGet( cp_glb->p_glb ) == 0 ){
		MSGMAN_GetString( man, DEBUG_ZUKAN_20, name );
	}else{
		MSGMAN_GetString( man, DEBUG_ZUKAN_03, name );
	}

	// 選択中のもの
	if( cp_work->now_select == ZKN_BIGDEBUG_SELE_POKE ){
		GF_STR_PrintColor( p_bmp,
				FONT_SYSTEM, mons_name, 0, 0, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	}else{
		GF_STR_PrintColor( p_bmp,
				FONT_SYSTEM, name, 0, 0, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	}

	// へんしゅうちゅう
	MSGMAN_GetString( man, DEBUG_ZUKAN_21, str );
	GF_STR_PrintColor( p_bmp,
			FONT_SYSTEM, str, 0, ZKN_BIGDEBUG_NOW_POKE_DATA_STR_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	GF_BGL_BmpWinOn( p_bmp );

	STRBUF_Delete(str);
	STRBUF_Delete(mons_name);
	STRBUF_Delete(name);
	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ウィンドウの破棄
 *
 *	@param	p_draw
 *	@param	p_drawglb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugDeleteBmp( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb )
{
	int i;

	// 破棄
	for( i=0; i<ZKN_BIGDEBUG_WND_NUM; i++ ){
		GF_BGL_BmpWinOff( p_draw->p_bmp[ i ] );
		GF_BGL_BmpWinDel( p_draw->p_bmp[ i ] );
		GF_BGL_BmpWinFree( p_draw->p_bmp[ i ], 1 );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンと主人公のﾃﾞｰﾀを表示する関数
 *
 *	@param	p_bmp		ビットマップウィンドウ
 *	@param	yofs		表示データ１
 *	@param	scale		表示データ２
 *	@param	str			使用するSTRBUF
 *	@param	man			使用するメッセージマネージャ
 *	@param	name		表示する名前
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugOneParamDataPrint( GF_BGL_BMPWIN* p_bmp, short yofs, short scale, STRBUF* str, MSGDATA_MANAGER* man, STRBUF* name )
{
	// なまえ
	GF_STR_PrintColor( p_bmp,
			FONT_SYSTEM, name, ZKN_BIGDEBUG_POKEHERO_NAME_X, ZKN_BIGDEBUG_POKEHERO_NAME_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	
	// ひりつ
	MSGMAN_GetString( man, DEBUG_ZUKAN_00, str );
	GF_STR_PrintColor( p_bmp,
			FONT_SYSTEM, str, ZKN_BIGDEBUG_POKEHERO_HIRITSU_X, ZKN_BIGDEBUG_POKEHERO_STR_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
		
	// ひりつの数字
	ZknBigDebug0xNumMake( p_bmp, ZKN_BIGDEBUG_POKEHERO_HIRITSU_X, ZKN_BIGDEBUG_POKEHERO_NUM_Y, str, (u32)scale, ZKN_BIGDEBUG_STRNUM_KETA, man, DEBUG_ZUKAN_04 );

	// たかさ
	MSGMAN_GetString( man, DEBUG_ZUKAN_01, str );
	GF_STR_PrintColor( p_bmp,
			FONT_SYSTEM, str, ZKN_BIGDEBUG_POKEHERO_TAKASA_X, ZKN_BIGDEBUG_POKEHERO_STR_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// たかさの数字
	ZknBigDebug0xNumMake( p_bmp, ZKN_BIGDEBUG_POKEHERO_TAKASA_X, ZKN_BIGDEBUG_POKEHERO_NUM_Y, str, (u32)yofs, ZKN_BIGDEBUG_STRNUM_KETA, man, DEBUG_ZUKAN_04 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	16進数の数字を作成
 *
 *	@param	p_bmp	書き込むビットマップ
 *	@param	x		ｘ座標　（ドット）
 *	@param	y		ｙ座標	（ドット）
 *	@param	str		文字列バッファ
 *	@param	num		数字
 *	@param	keta	桁
 *	@param	man		メッセージマネージャ
 *	@param	start_msg_idx	メッセージｲﾝﾃﾞｯｸｽ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigDebug0xNumMake( GF_BGL_BMPWIN* p_bmp, u32 x, u32 y, STRBUF* str, u32 num, u32 keta, MSGDATA_MANAGER* man, u32 start_msg_idx )
{
	int i;
	int draw_num;

	for( i=0; i<keta; i++ ){

		draw_num = num % 0x10;


		MSGMAN_GetString( man, start_msg_idx + draw_num, str );
		
		GF_STR_PrintColor( p_bmp,
				FONT_SYSTEM, str, 
				x + (((keta - 1) - i)*9), y,
				0, ZKN_BG_FONT_COLOR_MSK, NULL );

		num /= 16;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	拡縮値　Y座標初期化
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugObjDataReset( ZKN_BIG_DEBUG_WORK* p_work )
{
	p_work->scale[ ZKN_BIGDEBUG_SELE_POKE ] = 0x100;
	p_work->scale[ ZKN_BIGDEBUG_SELE_HERO ] = 0x100;
	p_work->yofs[ ZKN_BIGDEBUG_SELE_POKE ] = 0;
	p_work->yofs[ ZKN_BIGDEBUG_SELE_HERO ] = 0;
}

#endif // PM_DEBUG


