//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan_common.c
 *	@brief		図鑑共通
 *	@author		tomoya takahashi 
 *	@data		2006.01.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"

#include "include/system/brightness.h"
#include "include/system/arc_tool.dat"
#include "include/system/arc_util.h"
#include "include/system/clact_util.h"
#include "include/application/zukanlist/zukan.naix"
#include "include/gflib/button_man.h"
#include "include/gflib/calctool.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"

#include "include/application/zukanlist/zkn_zukan.h"
#include "include/application/zukanlist/zkn_zukan_graver.h"
#include "include/application/zukanlist/zkn_zukan_textver.h"
#include "include/application/zukanlist/zkn_range.h"
#include "include/application/zukanlist/zkn_sound.h"
#include "include/application/zukanlist/zkn_big_sub.h"
#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_cursor.h"


// エフェクトで座標をLinkさせるため、仕方なくインクルード
#include "include/application/zukanlist/zkn_pokelist.h"
#include "include/application/zukanlist/zkn_pokelist_sub.h"


#define	__ZKN_ZUKAN_COMMON_H_GLOBAL
#include "include/application/zukanlist/zkn_zukan_common.h"

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
#define ZKN_ZUKAN_COMMON_EVENT_NUM ( 8 )	// イベント数
#define ZKN_ZUKAN_COMMON_EVENT_CHANGE_POKELIST	( 0x1 << 1 )	// ポケモンリストに変更
#define ZKN_ZUKAN_COMMON_EVENT_CHANGE_ZUKAN	( 0x1 << 2 )		// 図鑑へ
#define ZKN_ZUKAN_COMMON_EVENT_CHANGE_RANGE	( 0x1 << 3 )		// 分布へ
#define ZKN_ZUKAN_COMMON_EVENT_CHANGE_SOUND	( 0x1 << 4 )		// 泣き声へ
#define ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG	( 0x1 << 5 )		// 大きさ比べへ
#define ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG_HEIGHT	( 0x1 << 6 )		// 大きさ比べへ
#define ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG_WEIGHT	( 0x1 << 7 )		// 大きさ比べへ
#define ZKN_ZUKAN_COMMON_EVENT_CHANGE_GRAPHIC	( 0x1 << 8 )		// 大きさ比べへ

#define ZKN_ZUKAN_COMMON_RESOBJ_NUM			( 4 )		// リソースオブジェ格納領域数

#define ZKN_ZUKAN_COMMON_ICON_Y			( 8 * FX32_ONE )
#define ZKN_ZUKAN_COMMON_ICON_X			( 168 * FX32_ONE )
#define ZKN_ZUKAN_COMMON_ICON_X_ADD		( 24 * FX32_ONE )


#define ZKN_ZUKAN_COMMON_ICON_SEQ		( 0 )	// ICONアニメシーケンス


// タイトル
#define ZKN_ZUKAN_TITLE_DRAW_X		( 16 )
#define ZKN_ZUKAN_TITLE_DRAW_Y		( 0 )
#define ZKN_GRAPHIC_BUTTONFONT_BMP_SIZE_CX	(8)
#define ZKN_GRAPHIC_BUTTONFONT_BMP_SIZE_CY	(2)

//-------------------------------------
//	アプリケーションデータ
//=====================================
enum{
	ZKN_ZUKAN_COMMON_APL_ZUKAN00,
	ZKN_ZUKAN_COMMON_APL_RANGE,
	ZKN_ZUKAN_COMMON_APL_SOUND,
	ZKN_ZUKAN_COMMON_APL_BIG,
	ZKN_ZUKAN_COMMON_APL_GRAPHIC,
	ZKN_ZUKAN_COMMON_APL_NUM,
};

//-------------------------------------
//	図鑑描画初期化シーケンス
//=====================================
enum{
	ZKN_ZUKAN_COMMON_SEQINIT_ALLOC,
	ZKN_ZUKAN_COMMON_SEQINIT_LOAD,
	ZKN_ZUKAN_COMMON_SEQINIT_FADEIN,
	ZKN_ZUKAN_COMMON_SEQINIT_END,
};

//-------------------------------------
//	図鑑描画破棄シーケンス
//=====================================
enum{
	ZKN_ZUKAN_COMMON_SEQDELETE_FADEOUT_INIT,
	ZKN_ZUKAN_COMMON_SEQDELETE_FADEOUT,
	ZKN_ZUKAN_COMMON_SEQDELETE_RELEASE,
	ZKN_ZUKAN_COMMON_SEQDELETE_FREE,
	ZKN_ZUKAN_COMMON_SEQDELETE_END,
};



//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	図鑑共通画面　グローバル変数
//=====================================
typedef struct _ZKN_ZUKAN_COMMON_GLB{
	int*				p_event_key;		// イベントキー
	ZKN_GLB_DATA*		p_glb;				// グローバルデータ
	int					now_apply;			// 今のアプリケーション
	ZKN_POKELIST_GLB_DATA* p_pokelist_glb;	// ポケモンリストグローバル
	ZKN_ZUKAN_GLB*		p_zkn_data_glb;		// 図鑑データグローバルデータ
	ZKN_APL_DATA* p_zkn_datagraver_glb;		// 図鑑グラフィックverのグローバル
	ZKN_APL_DATA* p_zkn_datatextver_glb;	// 図鑑言語verのグローバル
	ZKN_APL_DATA* p_range_glb;				// 分布図のグローバル
	ZKN_APL_DATA* p_sound_glb;				// 泣き声のグローバル
	ZKN_APL_DATA* p_big_sub_glb;			// 重さ比べサブ画面
	
	BOOL sub_apply_brightness_on;	// サブアプリにブライトネス使用を許可
	BOOL fade_mode;		// TREU	ただのブライトネス FALSE	半透明設定あり
	BOOL pal_load_flag;	// パレット読み込みフラグ
} ZKN_ZUKAN_COMMON_GLB;

//-------------------------------------
//	図鑑共通画面	描画グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// 描画グローバルデータ
} ZKN_ZUKAN_COMMON_DRAWGLB;


//-------------------------------------
//	図鑑共通画面　内部ワーク
//=====================================
typedef struct {
	int dummy;
} ZKN_ZUKAN_COMMON_WORK;

//-------------------------------------
//	図鑑共通画面　描画ワーク
//=====================================
typedef struct{
//	CLACT_WORK_PTR icon;		// アイコン
	int local_apl_tmp;			// 今のアイコンが表示されているアプリ位置

	ZKN_FONTOAM_DATA* p_title[ZKN_ZUKAN_COMMON_APL_NUM];	// タイトルフォントOAM
	
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_ZUKAN_COMMON_RESOBJ_NUM ];	// Resourceオブジェポインタ

} ZKN_ZUKAN_COMMON_DRAW;

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
static ZKN_ZUKAN_COMMON_GLB* MakeZukanCommonGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_ZUKAN_COMMON_DRAWGLB* MakeZukanCommonDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeZukanCommonEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteZukanCommonGlb( ZKN_ZUKAN_COMMON_GLB* p_glb );
static void DeleteZukanCommonDrawGlb( ZKN_ZUKAN_COMMON_DRAWGLB* p_glb );
static void DeleteZukanCommonEvent( ZKN_EVENT_DATA* p_event );


static int ZukanCommonEventDataNumGet( void );

//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
static int ZknZukanCommonProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanCommonProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanCommonProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanCommonProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanCommonProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanCommonProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

static void ZknZukanCommonProcDoFuncMainInit( ZKN_ZUKAN_COMMON_GLB* p_glb );
// アプリケーション変更
static BOOL ZknZukanCommonGetFadeModeOther( int apply );
static BOOL ZknZukanCommonChangeApply( ZKN_ZUKAN_COMMON_GLB* p_glb, int apply, int last_apply );
static void ZknZukanCommonResetMainApply( ZKN_ZUKAN_COMMON_GLB* p_glb );
static void ZknZukanCommonChangePokeList( ZKN_ZUKAN_COMMON_GLB* p_glb );
static void ZknZukanCommon_MainChangePokelist( ZKN_ZUKAN_COMMON_GLB* p_glb );

// リソース読み込み
static void ZknZukanCommonLoadResource( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw, const ZKN_ZUKAN_COMMON_GLB* cp_glb, int heap );
static void ZknZukanCommonDeleteResource( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw );
static void ZknZukanCommonSetUpBg( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_GLB* cp_glb, int heap );
static void ZknZukanCommonLoadCell( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw, int heap );
static void ZknZukanCommonReleaseCell( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw );
static void ZknZukanCommonAddCell( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw, int heap );
static void ZknZukanCommonDeleteCell( ZKN_ZUKAN_COMMON_DRAW* p_draw );
static void ZknZukanCommonIconMatSet( ZKN_ZUKAN_COMMON_DRAW* p_draw, int apl );
static void ZknZukanCommonAddFontOam( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw, int heap );
static void ZknZukanCommonDeleteFontOam( ZKN_ZUKAN_COMMON_DRAW* p_draw );

static void ZknZukanCommonFontOamChg( ZKN_ZUKAN_COMMON_DRAW* p_draw, int apl, int old_apl  );

static void ZknZukanCommonOamFadeInit( ZKN_ZUKAN_COMMON_DRAW* p_draw );
static void ZknZukanCommonOamFadeDelete( ZKN_ZUKAN_COMMON_DRAW* p_draw );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑共通　アプリ作成
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
void ZKN_ZukanCommonAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_ZUKAN_COMMON_GLB*		p_glb;
	ZKN_ZUKAN_COMMON_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeZukanCommonGlb( heap, zkn_sys );
	p_drawglb = MakeZukanCommonDrawGlb( heap, zkn_sys );
	p_event = MakeZukanCommonEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= ZukanCommonEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanCommonProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanCommonProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanCommonProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanCommonProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanCommonProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanCommonProcDrawFuncDelete;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリスト	　メニューアプリ破棄
 *
 *	@param	p_data	アプリケーションデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_ZukanCommonAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteZukanCommonGlb( p_data->p_glb_data ); 
	DeleteZukanCommonDrawGlb( p_data->p_glb_draw ); 
	DeleteZukanCommonEvent( p_data->p_event_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ブライトネスしようフラグチェック
 *	
 *	@param	cp_glb	グローバルデータ
 *
 *	@retval	TRUE	使用許可
 *	@retval	FALSE	使用不可能
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanCommonBrightnessOnFlagGet( const ZKN_APL_DATA* cp_glb )
{
	const ZKN_ZUKAN_COMMON_GLB * cp_glbdata = cp_glb->p_glb_data;
	return cp_glbdata->sub_apply_brightness_on;
}



//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑共通　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKAN_COMMON_GLB* MakeZukanCommonGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKAN_COMMON_GLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKAN_COMMON_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKAN_COMMON_GLB) );

	// main画面からのイベントキー
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrMainCommon( zkn_sys ); 

	// グローバルデータ
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	// 最初のアプリケーション
	p_glb->now_apply = ZKN_ZUKAN_COMMON_APL_ZUKAN00;

	// 図鑑グローバルデータ
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN );
	p_glb->p_zkn_data_glb = p_apl->p_glb_data;

	// 図鑑グラフィックバージョングローバルデータ
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_GRA );
	p_glb->p_zkn_datagraver_glb = p_apl;

	// 図鑑言語バージョングローバルデータ
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_TEXT );
	p_glb->p_zkn_datatextver_glb = p_apl;

	// 分布グローバルデータ
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_RANGE );
	p_glb->p_range_glb = p_apl;

	// 泣き声グローバルデータ
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_SOUND );
	p_glb->p_sound_glb = p_apl;

	// 重さ比べサブ画面グローバルデータ
	p_apl = ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_BIG );
	p_glb->p_big_sub_glb = p_apl;

	// ポケモンリストグローバルデータ
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_POKELIST );
	p_glb->p_pokelist_glb = p_apl->p_glb_data;


	// フェードモード取得
	p_glb->fade_mode = TRUE;
	
	// パレット読み込みフラグ
	p_glb->pal_load_flag = TRUE;
	
	return p_glb;
}


//----------------------------------------------------------------------------
/**
 *	@brief	描画グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑データ
 *
 *	@return	描画グローバルデータ
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKAN_COMMON_DRAWGLB* MakeZukanCommonDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKAN_COMMON_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKAN_COMMON_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKAN_COMMON_DRAWGLB) );

	// 描画データ
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑共通　イベント作成
 *
 *	@param	heap		使用するヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	イベントデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeZukanCommonEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = ZukanCommonEventDataNumGet();

	// イベントデータテーブル作成
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_MakeChangePokeList( heap, &p_event_tbl[0], zkn_sys, ZKN_ZUKAN_COMMON_EVENT_CHANGE_POKELIST );
	ZKN_EVENT_MakeChangeZukanOnly( heap, &p_event_tbl[1], zkn_sys, ZKN_ZUKAN_COMMON_EVENT_CHANGE_ZUKAN );
	ZKN_EVENT_MakeChangeRange( heap, &p_event_tbl[2], zkn_sys, ZKN_ZUKAN_COMMON_EVENT_CHANGE_RANGE );
	ZKN_EVENT_MakeChangeSound( heap, &p_event_tbl[3], zkn_sys, ZKN_ZUKAN_COMMON_EVENT_CHANGE_SOUND );
	ZKN_EVENT_MakeChangeBig( heap, &p_event_tbl[4], zkn_sys, ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG );
	ZKN_EVENT_MakeChangeBigMain( heap, &p_event_tbl[5], zkn_sys, ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG_HEIGHT );
	ZKN_EVENT_MakeChangeBigWeightMain( heap, &p_event_tbl[6], zkn_sys, ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG_WEIGHT );

	ZKN_EVENT_MakeChangeZukanGraphic( heap, &p_event_tbl[7], zkn_sys, ZKN_ZUKAN_COMMON_EVENT_CHANGE_GRAPHIC );

	return p_event_tbl;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑共通　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanCommonGlb( ZKN_ZUKAN_COMMON_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑共通　描画グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanCommonDrawGlb( ZKN_ZUKAN_COMMON_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑共通　イベントデータ破棄
 *
 *	@param	p_event	イベントデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanCommonEvent( ZKN_EVENT_DATA* p_event )
{
	GF_ASSERT( p_event );
	
	ZKN_EVENT_DeleteData( &p_event[0] );
	ZKN_EVENT_DeleteData( &p_event[1] );
	ZKN_EVENT_DeleteData( &p_event[2] );
	ZKN_EVENT_DeleteData( &p_event[3] );
	ZKN_EVENT_DeleteData( &p_event[4] );
	ZKN_EVENT_DeleteData( &p_event[5] );
	ZKN_EVENT_DeleteData( &p_event[6] );
	ZKN_EVENT_DeleteData( &p_event[7] );

	sys_FreeMemoryEz( p_event );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑共通アプリ　イベント数取得
 *	
 *	@param	none	
 *
 *	@return	図鑑共通アプリ　イベント数
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZukanCommonEventDataNumGet( void )
{
	return ZKN_ZUKAN_COMMON_EVENT_NUM;
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
static int ZknZukanCommonProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_COMMON_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_COMMON_WORK*	p_work = p_dodata->p_work;

	// ポケモンの声を鳴らす
	p_glb->p_zkn_data_glb->mons_snd_req = TRUE;
	
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
static int ZknZukanCommonProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_COMMON_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_COMMON_WORK*	p_work = p_dodata->p_work;

	// 終了へ
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	// seq0 == 初期化
	if( p_dodata->seq == 0 ){
		ZknZukanCommonProcDoFuncMainInit( p_glb );
		p_dodata->seq++;
	}

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
static int ZknZukanCommonProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_COMMON_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_COMMON_WORK*	p_work = p_dodata->p_work;

	// アプリケーション初期化
	p_glb->now_apply = ZKN_ZUKAN_COMMON_APL_ZUKAN00;
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
static int ZknZukanCommonProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_COMMON_GLB* cp_glb = cp_glbdata;
	const ZKN_ZUKAN_COMMON_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKAN_COMMON_DRAW*		p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_ZUKAN_COMMON_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_ZUKAN_COMMON_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_ZUKAN_COMMON_DRAW) );
		p_drawwork = p_drawdata->p_work;
		p_drawwork->local_apl_tmp = cp_glb->now_apply;	// 今表示中の位置
		p_drawdata->seq ++;
		break;
		
	case ZKN_ZUKAN_COMMON_SEQINIT_LOAD:
		ZknZukanCommonLoadResource( p_drawglb, p_drawwork, cp_glb, p_drawdata->heap );
		// 半透明OAM設定
		ZknZukanCommonOamFadeInit( p_drawwork );

		// 半透明OAMにすれば、フェードインアウトする設定でブライトネスフェード
		ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_LONG_COMMON,
				BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_BRIGHTNESS_MSK_ALL, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_COMMON_SEQINIT_FADEIN:
		if( ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_ZUKAN_COMMON_SEQINIT_END:
		// 半透明OAM設定解除
		ZknZukanCommonOamFadeDelete( p_drawwork );
		return ZKN_PROC_TRUE;

	default:
		GF_ASSERT(0);
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
static int ZknZukanCommonProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_COMMON_GLB* cp_glb = cp_glbdata;
	const ZKN_ZUKAN_COMMON_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKAN_COMMON_DRAW*		p_drawwork = p_drawdata->p_work;


	// アプリケーションが変わったらアイコンの表示位置を変更
	if( p_drawwork->local_apl_tmp != cp_glb->now_apply ){
		ZknZukanCommonIconMatSet( p_drawwork, cp_glb->now_apply );
		ZknZukanCommonFontOamChg( p_drawwork, cp_glb->now_apply, p_drawwork->local_apl_tmp );
		p_drawwork->local_apl_tmp = cp_glb->now_apply;
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
static int ZknZukanCommonProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_COMMON_GLB* cp_glb = cp_glbdata;
	const ZKN_ZUKAN_COMMON_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKAN_COMMON_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_ZUKAN_COMMON_SEQDELETE_FADEOUT_INIT:
		// 大きさ比べ重さ比べのためただのブラックフェードモードも作成
		if( cp_glb->fade_mode ){
			
			// 半透明OAM設定
			ZknZukanCommonOamFadeInit( p_drawwork );
			
			
			// 半透明OAMにすれば、フェードインアウトする設定でブライトネスフェード
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_LONG_COMMON,

					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_BRIGHTNESS_MSK_ALL, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// フェードインアウトする設定で全てブライトネスフェード
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_LONG_COMMON,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, PLANEMASK_ALL, 0, ZKN_UTIL_FADE_MAIN );
		}
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_COMMON_SEQDELETE_FADEOUT:
		if( ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_ZUKAN_COMMON_SEQDELETE_RELEASE:
		ZknZukanCommonDeleteResource( p_drawglb, p_drawwork );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_COMMON_SEQDELETE_FREE:		
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->p_work = NULL;
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_COMMON_SEQDELETE_END:
		return ZKN_PROC_TRUE;
			
	default:
		GF_ASSERT(0);
		break;
	}

	return ZKN_PROC_FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンリストに戻る時の処理　複数の処理をパック
 *
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommon_MainChangePokelist( ZKN_ZUKAN_COMMON_GLB* p_glb )
{
	ZknZukanCommonChangePokeList( p_glb );

	p_glb->pal_load_flag = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケリストに戻るときの処理
 *
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonChangePokeList( ZKN_ZUKAN_COMMON_GLB* p_glb )
{
	// イベント発行
	// ポケリストに分岐
	*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_POKELIST;
	
	// このシステムの下で動く全てのアプリのブライトネス
	// 使用を許可しない
	p_glb->sub_apply_brightness_on = FALSE;

	// 図鑑のフェード種類を初期化する
	p_glb->p_zkn_data_glb->fade_mode = ZKN_ZUKAN_FADE_MODE_CHPOKELIST;	
	ZKN_ZukanTextverFadeModeSet( p_glb->p_zkn_datatextver_glb, ZKN_ZUKANTEXTVER_FADE_MODE_CHPOKELIST );


	// メインで動作しているもののフェードアウト準備
	switch( p_glb->now_apply ){
	case ZKN_ZUKAN_COMMON_APL_ZUKAN00:
		p_glb->p_zkn_data_glb->poke_gra_move_x = ZKN_POKELIST_POKEGRA_X;
		p_glb->p_zkn_data_glb->poke_gra_move_y = ZKN_POKELIST_POKEGRA_Y;

		ZKN_ZukanTextverPokeGraFadeOutSet( p_glb->p_zkn_datatextver_glb, ZKN_POKELIST_POKEGRA_X, ZKN_POKELIST_POKEGRA_Y );
		p_glb->p_pokelist_glb->fade_zukan_data = TRUE;	// 図鑑->pokelistエフェクト

		// フェードモード
		p_glb->fade_mode = TRUE;	// 半透明設定OAMフェード
		break;
		
	case ZKN_ZUKAN_COMMON_APL_RANGE:
		ZKN_RangeFadeModeSet( p_glb->p_range_glb, ZKN_RANGE_FADE_MODE_OTHER );
		ZKN_RangeFadeModeSync( p_glb->p_range_glb, ZKN_FADE_SYNC_LONG_COMMON );
		ZKN_RangePokeGraFadeOutSet( p_glb->p_range_glb, ZKN_POKELIST_POKEGRA_X, ZKN_POKELIST_POKEGRA_Y );
		p_glb->p_pokelist_glb->fade_zukan_data = TRUE;	// 図鑑->pokelist

		// フェードモード
		p_glb->fade_mode = TRUE;	// 半透明設定OAMフェード
		break;
		
	case ZKN_ZUKAN_COMMON_APL_SOUND:
		ZKN_SoundFadeModeSet( p_glb->p_sound_glb, ZKN_SOUND_FADE_MODE_OTHER );
		ZKN_SoundFadeModeSync( p_glb->p_sound_glb, ZKN_FADE_SYNC_LONG_COMMON );
		ZKN_SoundPokeGraFadeOutSet( p_glb->p_sound_glb, ZKN_POKELIST_POKEGRA_X, ZKN_POKELIST_POKEGRA_Y );
		p_glb->p_pokelist_glb->fade_zukan_data = TRUE;	// 図鑑->pokelist

		// フェードモード
		p_glb->fade_mode = TRUE;	// 半透明設定OAMフェード
		break;
		
	case ZKN_ZUKAN_COMMON_APL_BIG:
		p_glb->p_pokelist_glb->fade_zukan_data = FALSE;	// 通常

		// フェードモード
		p_glb->fade_mode = FALSE;	// 全体ブライトネスフェード
		break;

	case ZKN_ZUKAN_COMMON_APL_GRAPHIC:
		p_glb->p_pokelist_glb->fade_zukan_data = FALSE;	// 通常
		// フェードモード
		p_glb->fade_mode = FALSE;	// 全体ブライトネスフェード
		break;

	default:
		break;
	}
}

// フェードモードをあざーにするかチェック
static BOOL ZknZukanCommonGetFadeModeOther( int apply )
{
// 全部をブラックフェードにする		03/16
	
/*	if( (apply != ZKN_ZUKAN_COMMON_APL_BIG) &&
		(apply != ZKN_ZUKAN_COMMON_APL_GRAPHIC) ){
		return TRUE;
	}//*/

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アプリケーション変更
 *
 *	@param	p_glb
 *	@param	apply
 *	@param	last_apply 
 *
 *	@retval	TRUE	変更します
 *	@retval FALSE	変更しません
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanCommonChangeApply( ZKN_ZUKAN_COMMON_GLB* p_glb, int apply, int last_apply )
{
	int pokegra_x, pokegra_y;
	BOOL ret = TRUE;

	switch( apply ){
	case ZKN_ZUKAN_COMMON_APL_ZUKAN00:
		if( ZknZukanCommonGetFadeModeOther( last_apply ) ){
			p_glb->p_zkn_data_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_OTHER;
		}else{
			p_glb->p_zkn_data_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_NORMAL;
		}
		*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_ZUKAN;
		p_glb->now_apply = ZKN_ZUKAN_COMMON_APL_ZUKAN00;
		pokegra_x = ZKN_ZUKAN_POKEGRA_MAT_X;
		pokegra_y = ZKN_ZUKAN_POKEGRA_MAT_Y;
		break;
		
	case ZKN_ZUKAN_COMMON_APL_RANGE:
		if( ZknZukanCommonGetFadeModeOther( last_apply ) ){
			ZKN_RangeFadeModeSet( p_glb->p_range_glb, ZKN_RANGE_FADE_MODE_OTHER );
			ZKN_RangeFadeModeSync( p_glb->p_range_glb, ZKN_FADE_SYNC_COMMON );
		}else{
			ZKN_RangeFadeModeSet( p_glb->p_range_glb, ZKN_RANGE_FADE_MODE_MY );
		}
		*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_RANGE;
		p_glb->now_apply = ZKN_ZUKAN_COMMON_APL_RANGE;
		pokegra_x = ZKN_RANGE_POKEGRA_DRAW_X;
		pokegra_y = ZKN_RANGE_POKEGRA_DRAW_Y;
		break;
		
	case ZKN_ZUKAN_COMMON_APL_SOUND:
		if( ZknZukanCommonGetFadeModeOther( last_apply ) ){
			ZKN_SoundFadeModeSet( p_glb->p_sound_glb, ZKN_SOUND_FADE_MODE_OTHER );
			ZKN_SoundFadeModeSync( p_glb->p_sound_glb, ZKN_FADE_SYNC_COMMON );
		}else{
			ZKN_SoundFadeModeSet( p_glb->p_sound_glb, ZKN_SOUND_FADE_MODE_MY );
		}
		*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_SOUND;
		p_glb->now_apply = ZKN_ZUKAN_COMMON_APL_SOUND;
		pokegra_x = ZKN_SOUND_POKEGRA_DRAW_X;
		pokegra_y = ZKN_SOUND_POKEGRA_DRAW_Y;
		break;
		
	case ZKN_ZUKAN_COMMON_APL_BIG:

		// 捕獲したポケモンかチェック
		if( ZKN_GLBDATA_PokeMonsTypeGet( p_glb->p_glb ) == ZKN_POKELIST_TYPE_GET ){
			*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG;
			p_glb->now_apply = ZKN_ZUKAN_COMMON_APL_BIG;
		}else{
			ret = FALSE;
		}
		break;

	case ZKN_ZUKAN_COMMON_APL_GRAPHIC:

		// グラフィックモードになっているかチェック
		if( ZKN_GLBDATA_PokeGraphicVersionFlagGet( p_glb->p_glb ) == TRUE ){
			*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_GRAPHIC;
			p_glb->now_apply = ZKN_ZUKAN_COMMON_APL_GRAPHIC;
		}else{
			ret = FALSE;
		}
		break;
		
	default:
		// おかしい
		GF_ASSERT(0);
		break;
	}

	switch( last_apply ){
	case ZKN_ZUKAN_COMMON_APL_ZUKAN00:
		if( ZknZukanCommonGetFadeModeOther( apply ) ){
			p_glb->p_zkn_data_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_OTHER;
			ZKN_ZukanTextverFadeModeSet( p_glb->p_zkn_datatextver_glb, ZKK_ZUKANTEXTVER_FADE_MODE_OTHER );
		}else{
			p_glb->p_zkn_data_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_NORMAL;
			ZKN_ZukanTextverFadeModeSet( p_glb->p_zkn_datatextver_glb, ZKK_ZUKANTEXTVER_FADE_MODE_NORMAL );
		}
		p_glb->p_zkn_data_glb->poke_gra_move_x = pokegra_x;
		p_glb->p_zkn_data_glb->poke_gra_move_y = pokegra_y;
		ZKN_ZukanTextverPokeGraFadeOutSet( p_glb->p_zkn_datatextver_glb, pokegra_x, pokegra_y );
		break;
		
	case ZKN_ZUKAN_COMMON_APL_RANGE:
		if( ZknZukanCommonGetFadeModeOther( apply ) ){
			ZKN_RangeFadeModeSet( p_glb->p_range_glb, ZKN_RANGE_FADE_MODE_OTHER );
			ZKN_RangeFadeModeSync( p_glb->p_range_glb, ZKN_FADE_SYNC_COMMON );
		}else{
			ZKN_RangeFadeModeSet( p_glb->p_range_glb, ZKN_RANGE_FADE_MODE_MY );
		}
		ZKN_RangePokeGraFadeOutSet( p_glb->p_range_glb, pokegra_x, pokegra_y );
		break;
		
	case ZKN_ZUKAN_COMMON_APL_SOUND:
		if( ZknZukanCommonGetFadeModeOther( apply ) ){
			ZKN_SoundFadeModeSet( p_glb->p_sound_glb, ZKN_SOUND_FADE_MODE_OTHER );
			ZKN_SoundFadeModeSync( p_glb->p_sound_glb, ZKN_FADE_SYNC_COMMON );
		}else{
			ZKN_SoundFadeModeSet( p_glb->p_sound_glb, ZKN_SOUND_FADE_MODE_MY );
		}
		ZKN_SoundPokeGraFadeOutSet( p_glb->p_sound_glb, pokegra_x, pokegra_y );
		break;
		
	case ZKN_ZUKAN_COMMON_APL_BIG:
		break;

	case ZKN_ZUKAN_COMMON_APL_GRAPHIC:
		break;
		
	default:
		// おかしい
		GF_ASSERT(0);
		break;
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	メイン画面のみの変更
 *
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonResetMainApply( ZKN_ZUKAN_COMMON_GLB* p_glb )
{
	// ブライトネス使用を許可
	p_glb->sub_apply_brightness_on = TRUE;


	switch( p_glb->now_apply ){
	case ZKN_ZUKAN_COMMON_APL_ZUKAN00:
		ZKN_ZukanTextverFadeModeSet( p_glb->p_zkn_datatextver_glb, ZKK_ZUKANTEXTVER_FADE_MODE_NORMAL );
		p_glb->p_zkn_data_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_NORMAL;
		*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_ZUKAN;
		break;
		
	case ZKN_ZUKAN_COMMON_APL_RANGE:
		ZKN_RangeFadeModeSet( p_glb->p_range_glb, ZKN_RANGE_FADE_MODE_MY );
		*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_RANGE;
		break;
		
	case ZKN_ZUKAN_COMMON_APL_SOUND:
		ZKN_SoundFadeModeSet( p_glb->p_sound_glb, ZKN_SOUND_FADE_MODE_MY );
		*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_SOUND;
		break;
		
	case ZKN_ZUKAN_COMMON_APL_BIG:
		// 高さ重さ比べチェック
		if( ZKN_BigSubNowAplTypeGet( p_glb->p_big_sub_glb ) == ZKN_BIGSUB_CONTROL_HEIGHT ){
			*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG_HEIGHT;
		}else{
			*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG_WEIGHT;
		}
		break;

	case ZKN_ZUKAN_COMMON_APL_GRAPHIC:
/*		ZKN_SoundFadeModeSet( p_glb->p_sound_glb, ZKN_SOUND_FADE_MODE_MY );
		*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_SOUND;//*/
		break;
		
	default:
		// おかしい
		GF_ASSERT(0);
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	Resource読み込み
 *
 *	@param	p_drawglb	描画グローバルデータ
 *	@param	p_draw		描画ワーク
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonLoadResource( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw, const ZKN_ZUKAN_COMMON_GLB* cp_glb, int heap )
{
	// BG読み込み
	ZknZukanCommonSetUpBg( p_drawglb, cp_glb, heap );
	
	// OAM読み込み
	ZknZukanCommonLoadCell( p_drawglb, p_draw, heap );

	// セルアクター登録
	ZknZukanCommonAddCell( p_drawglb, p_draw, heap );

	// FONTOAM
	ZknZukanCommonAddFontOam( p_drawglb, p_draw, heap );
	ZknZukanCommonFontOamChg( p_draw, ZKN_ZUKAN_COMMON_APL_ZUKAN00, ZKN_ZUKAN_COMMON_APL_RANGE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	Resource破棄
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	p_draw		描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonDeleteResource( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw )
{
	ZknZukanCommonDeleteCell( p_draw );
	ZknZukanCommonReleaseCell( p_drawglb, p_draw );
	ZknZukanCommonDeleteFontOam( p_draw );

	// ユーティリティ面スクリーンデータ初期化
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG面セットアップ
 *
 *	@param	p_drawglb	描画グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSetUpBg( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_GLB* cp_glb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// パレットデータ転送
	ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_NCLR, PALTYPE_MAIN_BG, 0, 0, heap );

	// 全国図鑑の時は色を変える
	if( ZKN_GLBDATA_PokeZknModeGet( cp_glb->p_glb ) == ZKN_MODE_ZENKOKU ){
		ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_zen_NCLR, PALTYPE_MAIN_BG, 0, 32, heap );
	}
	
	// キャラクタデータ転送
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_main_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M, 0, 0, TRUE, heap );

	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_main2_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルResource読み込み
 *
 *	@param	p_drawglb	描画グローバルデータ 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonLoadCell( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// キャラクタデータ読み込み
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main1_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_main1_lzh_NCGR + ZKN_ZUKAN_COMMON_RES_ID_OFS,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_data_oam1_NCLR, FALSE, 
			NARC_zukan_zkn_data_oam1_NCLR + ZKN_ZUKAN_COMMON_RES_ID_OFS, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_ZUKAN_COMMON_PLTT_LOAD, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// セルデータ読み込み
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main1_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_main1_lzh_NCER + ZKN_ZUKAN_COMMON_RES_ID_OFS,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_main1_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_main1_lzh_NANR + ZKN_ZUKAN_COMMON_RES_ID_OFS,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMResourceデータ破棄
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	p_draw		描画データ
 *
 *	@return	none	
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonReleaseCell( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw )
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
 *	@brief	セルアクター登録
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	p_draw		描画データ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonAddCell( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw, int heap )
{
/*	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_main1_lzh_NCGR + ZKN_ZUKAN_COMMON_RES_ID_OFS,
			NARC_zukan_zkn_data_oam1_NCLR + ZKN_ZUKAN_COMMON_RES_ID_OFS, 
			NARC_zukan_zkn_data_oam_main1_lzh_NCER + ZKN_ZUKAN_COMMON_RES_ID_OFS,
			NARC_zukan_zkn_data_oam_main1_lzh_NANR + ZKN_ZUKAN_COMMON_RES_ID_OFS,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 0;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	
	// アイコンを登録
	add.mat.x = 0;
	add.mat.y = 0;
	p_draw->icon = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->icon, ZKN_ZUKAN_COMMON_ICON_SEQ );

	// 座標設定
	ZknZukanCommonIconMatSet( p_draw, p_draw->local_apl_tmp );//*/
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクター破棄
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonDeleteCell( ZKN_ZUKAN_COMMON_DRAW* p_draw )
{
//	CLACT_Delete( p_draw->icon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM登録
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	p_draw		描画ワーク
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonAddFontOam( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw, int heap )
{
	GF_BGL_BMPWIN* win;	// 文字列書き込み先
	ZKN_FONTOAM_INIT fontoam_init;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;
	int pltt_ofs;	// パレットアドレス
	int	i;
		

	// 初期化データの共通部分を作成
	// 共通データ代入
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( p_draw->res_obj[ CLACT_U_PLTT_RES ], NULL );
	fontoam_init.x			 = ZKN_ZUKAN_TITLE_DRAW_X;
	fontoam_init.y			 = ZKN_ZUKAN_TITLE_DRAW_Y;
	fontoam_init.bg_pri		 = 0;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.parent		 = NULL;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;

	// パレット転送先アドレス取得
	pltt_ofs = GetPlttProxyOffset( fontoam_init.pltt, NNS_G2D_VRAM_TYPE_2DMAIN );

	for( i=0; i<ZKN_ZUKAN_COMMON_APL_NUM; i++ ){
		
		// ビットマップウィンドウ作成
		win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
				ZKN_GRAPHIC_BUTTONFONT_BMP_SIZE_CX,
				ZKN_GRAPHIC_BUTTONFONT_BMP_SIZE_CY );

		// comment
		ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
				NARC_msg_zkn_dat,ZNK_TITLE_00 + i, 0, 0 );
		fontoam_init.p_bmp		 = win;
		p_draw->p_title[ i ] = ZKN_FONTOAM_Make( &fontoam_init );
		FONTOAM_SetPaletteNo( p_draw->p_title[ i ]->p_fontoam, pltt_ofs );
		FONTOAM_SetDrawFlag( p_draw->p_title[ i ]->p_fontoam, FALSE );

		// ビットマップウィンドウ破棄
		ZKN_FONTOAM_DeleteBmp( win );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM破棄
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonDeleteFontOam( ZKN_ZUKAN_COMMON_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_ZUKAN_COMMON_APL_NUM; i++ ){
		ZKN_FONTOAM_Delete( p_draw->p_title[ i ] );
	}	
}


//----------------------------------------------------------------------------
/**
 *	@brief	アプリナンバーの座標に設定
 *
 *	@param	p_draw	描画ワーク
 *	@param	apl		アプリナンバー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonIconMatSet( ZKN_ZUKAN_COMMON_DRAW* p_draw, int apl )
{
/*	VecFx32 mat;

	mat.x = ZKN_ZUKAN_COMMON_ICON_X + (ZKN_ZUKAN_COMMON_ICON_X_ADD * apl);
	mat.y = ZKN_ZUKAN_COMMON_ICON_Y;

	CLACT_SetMatrix( p_draw->icon, &mat );//*/
}


//----------------------------------------------------------------------------
/**
 *	@brief	メイン関数初期化
 *
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonProcDoFuncMainInit( ZKN_ZUKAN_COMMON_GLB* p_glb )
{
	// ブライトネス使用を許可
	p_glb->sub_apply_brightness_on = TRUE;

	// アプリフェードモード設定
	p_glb->p_zkn_data_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_NORMAL;
}





//-----------------------------------------------------------------------------
/**
 *			サブ画面
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define ZKN_ZUKAN_COMMON_SUB_EVENT_NUM ( 0 )	// イベント数

//-------------------------------------
//	動作モード
//=====================================
enum{
	ZKN_ZUKAN_COMMON_SUB_MODE_CLOSE,
	ZKN_ZUKAN_COMMON_SUB_MODE_OPEN,
};


//-------------------------------------
//	サブ画面初期化シーケンス
//=====================================
enum{
	ZKN_ZUKAN_COMMON_SUB_SEQINIT_ALLOC,
	ZKN_ZUKAN_COMMON_SUB_SEQINIT_LOAD,
	ZKN_ZUKAN_COMMON_SUB_SEQINIT_FADEIN_INIT,
	ZKN_ZUKAN_COMMON_SUB_SEQINIT_FADEIN,
	ZKN_ZUKAN_COMMON_SUB_SEQINIT_END,
};

//-------------------------------------
//	サブ画面破棄シーケンス
//=====================================
enum{
	ZKN_ZUKAN_COMMON_SUB_SEQDELETE_FADEOUT_INIT,
	ZKN_ZUKAN_COMMON_SUB_SEQDELETE_FADEOUT,
	ZKN_ZUKAN_COMMON_SUB_SEQDELETE_RELEASE,
	ZKN_ZUKAN_COMMON_SUB_SEQDELETE_FREE,
	ZKN_ZUKAN_COMMON_SUB_SEQDELETE_END,
};


//-------------------------------------
//	サブコモンボタン数	閉じモード
//=====================================
enum{
	ZKN_ZUKAN_COMMON_SUB_BUTTON_CLOSE,
	ZKN_ZUKAN_COMMON_SUB_BUTTON_CLOSE_NUM,
};
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_CLOSE_R	( 32 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_CLOSE_X	( 128 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_CLOSE_Y	( 96 )


//-------------------------------------
//	サブコモンボタン数
//=====================================
enum{
	ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA,
	ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE,
	ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND,
	ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG,
	ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC,
	ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK,
	ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM,
};
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX		( 40 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY		( 32 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_Y			( 24 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA_X		( 28 )	
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK_X		( 228 )	
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE_X		( 68 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND_X		( 108 )	
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG_X		( 148 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC_X	( 188 )


// FONTOAM
#define ZKN_ZUKAN_COMMON_SUB_BUTTONFONT_BMP_SIZE_CX	( 8 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTONFONT_BMP_SIZE_CY	( 2 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTONFONT_OFS_3_X		( -20 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTONFONT_OFS_4_X		( -24 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTONFONT_OFS_Y		( -6 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTONFONT_PLTOFS	( 0 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTONFONT_PUSHPLTOFS	( 1 )

//-------------------------------------
//	カーソルデータ
//=====================================
enum{
	ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA  = ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA,
	ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE = ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE,
	ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND = ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND,
	ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG   = ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG,
	ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC  = ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC,
	ZKN_ZUKAN_COMMON_SUB_CURSOR_BACK  = ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK,

	ZKN_ZUKAN_COMMON_SUB_CURSOR_NUM,
};
enum{
	ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA_X  = ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA_X,
	ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE_X = ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE_X,	
	ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND_X = ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND_X,	
	ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG_X   = ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG_X,	
	ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC_X   = ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC_X,	
	ZKN_ZUKAN_COMMON_SUB_CURSOR_BACK_X  = ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK_X,

	ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA_Y  = ZKN_ZUKAN_COMMON_SUB_BUTTON_Y,
	ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE_Y = ZKN_ZUKAN_COMMON_SUB_BUTTON_Y,	
	ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND_Y = ZKN_ZUKAN_COMMON_SUB_BUTTON_Y,	
	ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG_Y   = ZKN_ZUKAN_COMMON_SUB_BUTTON_Y,	
	ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC_Y = ZKN_ZUKAN_COMMON_SUB_BUTTON_Y,	
	ZKN_ZUKAN_COMMON_SUB_CURSOR_BACK_Y  = ZKN_ZUKAN_COMMON_SUB_BUTTON_Y,
};
#define ZKN_ZUKAN_COMMMON_SUB_CURSOR_MAX_X	( ZKN_ZUKAN_COMMON_SUB_CURSOR_NUM )
#define ZKN_ZUKAN_COMMMON_SUB_CURSOR_MAX_Y	( 1 )
#define ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZX		( 24 )
#define ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZY		( 16 )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	図鑑共通画面　グローバル変数
//=====================================
typedef struct {
	int*				p_event_key;		// イベントキー
	ZKN_ZUKAN_COMMON_GLB* p_main_common_glb;// メイン画面コモングローバルデータ
	ZKN_GLB_DATA* p_glb;					// グローバルデータ
	int button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM ];	// ボタンイベントデータ

	BOOL sub_apply_brightness_on;	// サブアプリにブライトネス使用を許可

	int sub_common_sub_mode_flag;	// commonの下で動くアプリが動作してよいか動作モード

	BOOL back_key_push;				// 戻るボタンの機能は、キーでも出来るのでアニメを同期させるため

	BOOL sub_cursor_flag;	// カーソル動作をサブアプリが行うのか共通アプリが行うのか
} ZKN_ZUKAN_COMMON_SUB_GLB;

//-------------------------------------
//	図鑑共通画面　描画グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// 描画グローバルデータ
} ZKN_ZUKAN_COMMON_SUB_DRAWGLB;

//-------------------------------------
//	ボタン用ワーク
//=====================================
typedef struct {
	void* p_glb;
	void* p_work;
} ZKN_ZUKAN_COMMON_SUB_BUTTON_WORK;


//-------------------------------------
//	図鑑共通画面　内部ワーク
//=====================================
typedef struct {
	// ボタンマネージャ
	BUTTON_MAN* p_button_man;
	TP_HIT_TBL *hit_tbl;	// ボタンデータ
	ZKN_ZUKAN_COMMON_SUB_BUTTON_WORK button_work;
	int button_cancel_flg;


	// カーソルシステム
	ZKN_CURSOR* p_cursor;
	ZKN_CURSOR_ONEDATA* p_cursor_tbl;
} ZKN_ZUKAN_COMMON_SUB_WORK;

//-------------------------------------
//	図鑑共通画面　描画内部ワーク
//=====================================
typedef struct {
	CLACT_WORK_PTR clact[ ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM ];

	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_ZUKAN_COMMON_RESOBJ_NUM ];	// Resourceオブジェポインタ
} ZKN_ZUKAN_COMMON_SUB_DRAW;


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
static ZKN_ZUKAN_COMMON_SUB_GLB* MakeZukanCommonSubGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_ZUKAN_COMMON_SUB_DRAWGLB* MakeZukanCommonSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeZukanCommonSubEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteZukanCommonSubGlb( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );
static void DeleteZukanCommonSubDrawGlb( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_glb );
static void DeleteZukanCommonSubEvent( ZKN_EVENT_DATA* p_event );

static int ZukanCommonSubEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
static int ZknZukanCommonSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanCommonSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanCommonSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanCommonSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanCommonSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanCommonSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// アプリケーション変更処理
static BOOL ZknZukanCommonSubApplyChange( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb, int apply, int last_apply );

// ボタン制御
static void ZknZukanCommonSubButtonMake( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb, int heap );
static void ZknZukanCommonSubButtonEventBuffInit( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );
static void ZknZukanCommonSubButtonMove( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );
static void ZknZukanCommonSubButtonDelete( ZKN_ZUKAN_COMMON_SUB_WORK* p_work );
static void ZknZukanCommonSubButtonCallBack( u32 button_no, u32 event, void* p_work );

// カーソル制御
static void ZknZukanCommonSubCursorMake( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb, int heap );
static void ZknZukanCommonSubCursorMove( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );
static void ZknZukanCommonSubCursorDelete( ZKN_ZUKAN_COMMON_SUB_WORK* p_work );

static void ZknZukanCommonSubCursorInit( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );
static void ZknZukanCommonSubCursorKeyMove( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );
	
static void ZknZukanCommonSubCursorDrawInit( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_WORK* cp_work, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb );
static void ZknZukanCommonSubCursorDrawPack( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_WORK* cp_work, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb );
static void ZknZukanCommonSubCursorDraw( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_WORK* cp_work );
static BOOL ZknZukanCommonSubCursorOnOff( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb,  BOOL flag );


static void ZknZukanCommonSubProcDoFuncMainMain( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );
static void ZknZukanCommonSubOtherDoMain( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );
static void ZknZUkanCommonSubKeyFlagReset( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );


// Resource読み込み処理
static void ZknZukanCommonSubResourceLoad( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb, int heap );
static void ZknZukanCommonSubResourceDelete( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb );
static void ZknZukanCommonSubSetUpBG( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb, int heap );
static void ZknZukanCommonSubLoadOam( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanCommonSubReleaseOam( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb );

// セルアクター登録
static void ZknZukanCommonSubAddClact( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanCommonSubDeleteClact( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw );

// グラフィックパターンボタンの描画ONOFF
static void ZknZukanCommonSubSetGraVerButtonDrawFlag( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb );

// FONTOAM作成
static void ZknZukanCommonSubAddFontOam( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanCommonSubDeleteFontOam( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑共通　アプリ作成
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
void ZKN_ZukanCommonSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_ZUKAN_COMMON_SUB_GLB*	p_glb;
	ZKN_ZUKAN_COMMON_SUB_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeZukanCommonSubGlb( heap, zkn_sys );
	p_drawglb = MakeZukanCommonSubDrawGlb( heap, zkn_sys );
	p_event = MakeZukanCommonSubEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= ZukanCommonSubEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanCommonSubProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanCommonSubProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanCommonSubProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanCommonSubProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanCommonSubProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanCommonSubProcDrawFuncDelete;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリスト	　メニューアプリ破棄
 *
 *	@param	p_data	アプリケーションデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_ZukanCommonSubAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteZukanCommonSubGlb( p_data->p_glb_data ); 
	DeleteZukanCommonSubDrawGlb( p_data->p_glb_draw ); 
	DeleteZukanCommonSubEvent( p_data->p_event_data );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ブライトネスしようフラグチェック
 *	
 *	@param	cp_glb	グローバルデータ
 *
 *	@retval	TRUE	使用許可
 *	@retval	FALSE	使用不可能
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanCommonSubBrightnessOnFlagGet( const ZKN_APL_DATA* cp_glb )
{
	const ZKN_ZUKAN_COMMON_SUB_GLB * cp_glbdata = cp_glb->p_glb_data;
	return cp_glbdata->sub_apply_brightness_on;
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作してよいかチェック
 *
 *	@param	cp_glb	アプリケーションデータ
 *
 *	@retval	TRUE	動作OK
 *	@retval	FALSE	動作NG
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanCommonSubMoveFlagGet( const ZKN_APL_DATA* cp_glb )
{
	const ZKN_ZUKAN_COMMON_SUB_GLB * cp_glbdata = cp_glb->p_glb_data;
	
	return cp_glbdata->sub_common_sub_mode_flag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル動作してよいかチェック
 *
 *	@param	cp_glb	アプリケーションデータ
 *
 *	@retval	TRUE	動作OK
 *	@retval	FALSE	動作NG
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanCommonSubCursorFlagGet( const ZKN_APL_DATA* cp_glb )
{
	const ZKN_ZUKAN_COMMON_SUB_GLB * cp_glbdata = cp_glb->p_glb_data;
	
	return cp_glbdata->sub_cursor_flag;
}


//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑共通　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKAN_COMMON_SUB_GLB* MakeZukanCommonSubGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKAN_COMMON_SUB_GLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKAN_COMMON_SUB_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKAN_COMMON_SUB_GLB) );

	// イベントキー
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrSubCommon( zkn_sys );		

	// メイン画面コモングローバルデータ
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_COMMON );
	p_glb->p_main_common_glb = p_apl->p_glb_data;							

	// グローバルデータ
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	描画グローバルデータ
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKAN_COMMON_SUB_DRAWGLB* MakeZukanCommonSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKAN_COMMON_SUB_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKAN_COMMON_SUB_DRAWGLB) );


	// 描画データ
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑共通　イベント作成
 *
 *	@param	heap		使用するヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	イベントデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeZukanCommonSubEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑共通　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanCommonSubGlb( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑共通　描画グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanCommonSubDrawGlb( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑共通　イベントデータ破棄
 *
 *	@param	p_event	イベントデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanCommonSubEvent( ZKN_EVENT_DATA* p_event )
{
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑共通アプリ　イベント数取得
 *	
 *	@param	none	
 *
 *	@return	図鑑共通アプリ　イベント数
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZukanCommonSubEventDataNumGet( void )
{
	return ZKN_ZUKAN_COMMON_SUB_EVENT_NUM;
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
static int ZknZukanCommonSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_COMMON_SUB_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_COMMON_SUB_WORK* p_work = p_dodata->p_work;
	int i;
	// ワークの作成
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_ZUKAN_COMMON_SUB_WORK) );
	memset( p_work, 0, sizeof(ZKN_ZUKAN_COMMON_SUB_WORK) );


	// ボタンカーソルを作成
	ZknZukanCommonSubButtonMake( p_work, p_glb, p_dodata->heap );
	ZknZukanCommonSubCursorMake( p_work, p_glb, p_dodata->heap );
	ZknZukanCommonSubCursorInit( p_work, p_glb );


	// ボタンイベントデータ
	for( i=0; i<ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM; i++ ){
		p_glb->button_event[ i ] = ZKN_UTIL_BUTTON_PUSH_NONE;	// ボタンイベントデータ
	}


	p_dodata->p_work = p_work;
	
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
static int ZknZukanCommonSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_COMMON_SUB_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_COMMON_SUB_WORK* p_work = p_dodata->p_work;


	// 終了へ
	if( p_dodata->end_req == TRUE ){
		// サブアプリのブライトネス使用を非許可
		p_glb->sub_apply_brightness_on = FALSE;

		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	// seq==0初期化
	if( p_dodata->seq == 0 ){
		// サブアプリのブライトネス使用を許可
		p_glb->sub_apply_brightness_on = TRUE;

		// パレット読み込み済み
		p_glb->p_main_common_glb->pal_load_flag = FALSE;

		// 動作フラグ設定
		p_glb->sub_common_sub_mode_flag = TRUE;	// 動作許可

		
		p_dodata->seq++;
	}else{

		// 処理分岐動作
		ZknZukanCommonSubProcDoFuncMainMain( p_glb );

		// カーソルをメインアプリ　サブアプリに操作を許す分岐処理
		ZknZukanCommonSubCursorKeyMove( p_work, p_glb );

		// ボタンイベントバッファ初期化
		ZknZukanCommonSubButtonEventBuffInit( p_glb );

		// カーソル動作
		if( (ZKN_GLBDATA_TouchCursorFlagGet( p_glb->p_glb ) == TRUE) &&
			(p_glb->sub_cursor_flag == FALSE) ){

			ZknZukanCommonSubCursorMove( p_work, p_glb );
		}

		// ボタン動作
		ZknZukanCommonSubButtonMove( p_work, p_glb );
	}


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
static int ZknZukanCommonSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_COMMON_SUB_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_COMMON_SUB_WORK* p_work = p_dodata->p_work;

	// ボタンカーソル破棄
	ZknZukanCommonSubButtonDelete( p_work );
	ZknZukanCommonSubCursorDelete( p_work );
	

	// ワーク破棄
	sys_FreeMemoryEz( p_dodata->p_work );
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
 */
//-----------------------------------------------------------------------------
static int ZknZukanCommonSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_COMMON_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_ZUKAN_COMMON_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_COMMON_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_ZUKAN_COMMON_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_ZUKAN_COMMON_SUB_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof( ZKN_ZUKAN_COMMON_SUB_DRAW ) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_ZUKAN_COMMON_SUB_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_COMMON_SUB_SEQINIT_LOAD:

		//　モードチェック
		ZknZukanCommonSubResourceLoad( p_drawwork, p_drawglb, cp_dataglb,  p_drawdata->heap );

		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_COMMON_SUB_SEQINIT_FADEIN_INIT:
		ChangeBrightnessRequest( ZKN_FADE_SYNC_LONG_COMMON,
				BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_SUB_DISPLAY );

		// カーソル初期化
		ZknZukanCommonSubCursorDrawInit( p_drawglb, cp_datawork, cp_dataglb );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_COMMON_SUB_SEQINIT_FADEIN:
		if( IsFinishedBrightnessChg( MASK_SUB_DISPLAY  ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_ZUKAN_COMMON_SUB_SEQINIT_END:
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
 */
//-----------------------------------------------------------------------------
static int ZknZukanCommonSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_COMMON_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_ZUKAN_COMMON_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_COMMON_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_ZUKAN_COMMON_SUB_DRAW*		p_drawwork = p_drawdata->p_work;
	int i;		// ループ用

	// ボタン動作
	for( i=0; i<ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM; i++ ){
		ZKN_UTIL_ButtonMove( p_drawwork->clact[ i ],
				cp_dataglb->button_event[ i ] );
	}
	
	// カーソル動作
	ZknZukanCommonSubCursorDrawPack( p_drawglb, cp_datawork, cp_dataglb );
	
	
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
 */
//-----------------------------------------------------------------------------
static int ZknZukanCommonSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_COMMON_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_ZUKAN_COMMON_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_COMMON_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_ZUKAN_COMMON_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
		
	case ZKN_ZUKAN_COMMON_SUB_SEQDELETE_FADEOUT_INIT:
		ChangeBrightnessRequest( ZKN_FADE_SYNC_LONG_COMMON,
				BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, PLANEMASK_ALL, MASK_SUB_DISPLAY );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_COMMON_SUB_SEQDELETE_FADEOUT:
		if( IsFinishedBrightnessChg( MASK_SUB_DISPLAY  ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_ZUKAN_COMMON_SUB_SEQDELETE_RELEASE:
		ZknZukanCommonSubResourceDelete( p_drawwork, p_drawglb );

		// カーソル非表示
		ZKN_UTIL_CursorSetDrawFlag( &p_drawglb->p_drawglb->cursor, FALSE );
		p_drawdata->seq++;
		break;

	case ZKN_ZUKAN_COMMON_SUB_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->p_work = NULL;
		p_drawdata->seq++;
		break;
		
		
	case ZKN_ZUKAN_COMMON_SUB_SEQDELETE_END:
		return ZKN_PROC_TRUE;	

	default:
		break;
	}
	
	return ZKN_PROC_FALSE;
}




//----------------------------------------------------------------------------
/**
 *	@brief	ボタンタッチデータ作成
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバルデータ
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubButtonMake( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb, int heap )
{
	// テーブル作成
	p_work->hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM );

	// テーブルデータ設定
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA ],
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA_X - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA_X + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2) );
	
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK ],
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK_X - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK_X + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE ],
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE_X - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE_X + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND ],
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND_X - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND_X + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG ],
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG_X - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG_X + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC ],
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC_X - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC_X + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2) );

	p_work->button_work.p_glb = p_glb;
	p_work->button_work.p_work = p_work;

	// ボタンマネージャ作成
	p_work->p_button_man = BMN_Create( 
			p_work->hit_tbl,
			ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM,
			ZknZukanCommonSubButtonCallBack,
			&p_work->button_work,
			heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	イベントバッファ初期化処理
 *
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubButtonEventBuffInit( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	int i;
	
	// 放されたら全てのボタンが元の絵に戻る
	for( i = 0; i < ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM; i++ ){
		p_glb->button_event[ i ] = BMN_EVENT_SLIDEOUT;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタン動作
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubButtonMove( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	
	// すでに終わるキーが押されていた場合、
	// ボタンのタッチは判断しない
	if( p_glb->back_key_push == FALSE ){
		BMN_Main( p_work->p_button_man );
	}

	// キーで終わる分岐に行ったら終わるのボタンを押した状態にする
	if( p_glb->back_key_push ){
		if( p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK ] != BMN_EVENT_HOLD ){
			p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK ] = BMN_EVENT_RELEASE;
		}
	}

	// 今選択中のアプリケーションのボタンは押しっぱなしにする
	switch( p_glb->p_main_common_glb->now_apply ){
	case ZKN_ZUKAN_COMMON_APL_ZUKAN00:
		if( p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA ] != BMN_EVENT_HOLD ){
			p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_ZUKAN_COMMON_APL_RANGE:
		if( p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE ] != BMN_EVENT_HOLD ){
			p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_ZUKAN_COMMON_APL_SOUND:
		if( p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND ] != BMN_EVENT_HOLD ){
			p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_ZUKAN_COMMON_APL_BIG:
		if( p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG ] != BMN_EVENT_HOLD ){
			p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG ] = BMN_EVENT_RELEASE;
		}
		break;

	case ZKN_ZUKAN_COMMON_APL_GRAPHIC:
		if( p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC ] != BMN_EVENT_HOLD ){
			p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC ] = BMN_EVENT_RELEASE;
		}
		break;

	default:
		// おかしい
		GF_ASSERT(0);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタン破棄
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubButtonDelete( ZKN_ZUKAN_COMMON_SUB_WORK* p_work )
{
	BMN_Delete( p_work->p_button_man );

	// テーブルワーク破棄
	sys_FreeMemoryEz( p_work->hit_tbl );
	p_work->hit_tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンイベントコールバック
 *
 *	@param	button_no	ボタンナンバー
 *	@param	event		イベントタイプ
 *	@param	p_work		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_ZUKAN_COMMON_SUB_BUTTON_WORK* p_button_work = p_work;
	ZKN_ZUKAN_COMMON_SUB_GLB* p_glb = p_button_work->p_glb;
	ZKN_ZUKAN_COMMON_SUB_WORK* p_subwork = p_button_work->p_work;
	ZKN_ZUKAN_COMMON_GLB* p_main_glb = p_glb->p_main_common_glb;

	// ボタンイベント格納
	p_glb->button_event[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_TOUCH:
		p_subwork->button_cancel_flg = 0;
		break;
		
	case BMN_EVENT_HOLD:
		switch( button_no ){
		case ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK:
			// ポケモンリスト画面に戻る
			// ポケモンリストへ
			ZknZukanCommon_MainChangePokelist( p_main_glb );
			// 選択移動音
			Snd_SePlay( ZKN_SND_CANCEL );
			break;

		case ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_ZUKAN00 ){	
				ZknZukanCommonSubApplyChange( p_glb, ZKN_ZUKAN_COMMON_APL_ZUKAN00, p_main_glb->now_apply );
				
				ZknZukanCommonSubCursorInit( p_subwork, p_glb );
				// 選択移動音
				Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
			}
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_RANGE ){	
				ZknZukanCommonSubApplyChange( p_glb, ZKN_ZUKAN_COMMON_APL_RANGE, p_main_glb->now_apply );
				ZknZukanCommonSubCursorInit( p_subwork, p_glb );
				// 選択移動音
				Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
			}
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_SOUND ){	
				ZknZukanCommonSubApplyChange( p_glb, ZKN_ZUKAN_COMMON_APL_SOUND, p_main_glb->now_apply );
				ZknZukanCommonSubCursorInit( p_subwork, p_glb );
				// 選択移動音
				Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
			}
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_BIG ){	

				// ちゃんと変更されるかチェック
				if( ZknZukanCommonSubApplyChange( p_glb, ZKN_ZUKAN_COMMON_APL_BIG, p_main_glb->now_apply ) ){
					ZknZukanCommonSubCursorInit( p_subwork, p_glb );
					// 選択移動音
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
				}else{
					if( p_subwork->button_cancel_flg == 0 ){
						
						if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_SOUND ){	// 鳴き声画面ならならさない
							// キャンセル音
							Snd_SePlay( ZKN_SND_CANCEL );
						}
						p_subwork->button_cancel_flg = 1;
					}
				}
			}
			break;

		case ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_GRAPHIC ){

				// ちゃんと変更されるかチェック
				if( ZknZukanCommonSubApplyChange( p_glb, ZKN_ZUKAN_COMMON_APL_GRAPHIC, p_main_glb->now_apply ) ){
					ZknZukanCommonSubCursorInit( p_subwork, p_glb );
					// 選択移動音
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
				}else{
					if( p_subwork->button_cancel_flg == 0 ){

						// バージョンアップチェック
						if( ZKN_GLBDATA_PokeGraphicVersionFlagGet( p_main_glb->p_glb ) == TRUE ){

							if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_SOUND ){	// 鳴き声画面ならならさない
								// キャンセル音
								Snd_SePlay( ZKN_SND_CANCEL );
							}
						}

						
						p_subwork->button_cancel_flg = 0;
					}
				}
			}
			break;

		default:
			break;
		}
		break;
		
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ画面Resource読み込み
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	heap			ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubResourceLoad( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb, int heap )
{
	// BGセットアップ
	ZknZukanCommonSubSetUpBG( p_drawglb, cp_glb, heap );

	// OAMセットアップ
	ZknZukanCommonSubLoadOam( p_draw, p_drawglb, heap );


	// セル登録
	ZknZukanCommonSubAddClact( p_draw, p_drawglb, heap );

	// FONTOAM登録
	ZknZukanCommonSubAddFontOam( p_draw, p_drawglb, heap );

	// グラフィックバージョンボタンの非表示
	ZknZukanCommonSubSetGraVerButtonDrawFlag( p_draw, cp_glb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ画面Resource破棄
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubResourceDelete( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb )
{
	// FONTOAM破棄
	ZknZukanCommonSubDeleteFontOam( p_draw );
	
	// セル破棄
	ZknZukanCommonSubDeleteClact( p_draw );
	
	// OAMResourcey破棄
	ZknZukanCommonSubReleaseOam( p_draw, p_drawglb );

	// ユーティリティ面スクリーンデータ初期化
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_S );
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ画面共通部分BGセットアップ
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb
 *	@param	heap		ヒープ 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubSetUpBG( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	if( cp_glb->p_main_common_glb->pal_load_flag ){
		// パレットデータ転送
		ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_NCLR, PALTYPE_SUB_BG, 0, 0, heap );

		// 全国図鑑の時は色を変える
		if( ZKN_GLBDATA_PokeZknModeGet( cp_glb->p_glb ) == ZKN_MODE_ZENKOKU ){
			ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_zen_NCLR, PALTYPE_SUB_BG, 0, 32, heap );
		}
	}
	

	// キャラクタデータ転送
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_sub_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_S, 0, 0, TRUE, heap );

	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_sub1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_S,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_S );
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ画面OAMResource読み込み
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローばる
 *	@param	heap			ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubLoadOam( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// キャラクタデータ読み込み
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_sub_lzh_NCGR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub_NCLR, FALSE, 
			NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS, 
			NNS_G2D_VRAM_TYPE_2DSUB, 
			ZKN_ZUKAN_COMMON_PLTT_SUB_LOAD, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// セルデータ読み込み
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_sub_lzh_NCER + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_sub_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_sub_lzh_NANR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ画面OAMResource破棄
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubReleaseOam( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb )
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
 *	@brief	アクター登録
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubAddClact( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i;
	
	// 各ボタンを登録
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_sub_lzh_NCGR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS,
			NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS, 
			NARC_zukan_zkn_data_oam_sub_lzh_NCER + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS,
			NARC_zukan_zkn_data_oam_sub_lzh_NANR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 32;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;
	add.mat.y		= (ZKN_ZUKAN_COMMON_SUB_BUTTON_Y * FX32_ONE) + SUB_SURFACE_Y;
	
	// ボタン作成
	for( i=0; i<ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM; i++ ){
		// 登録座標設定
		switch( i ){
		case ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK:
			add.mat.x		= ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK_X * FX32_ONE;
			break;

		case ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA:
			add.mat.x		= ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA_X * FX32_ONE;
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE:
			add.mat.x		= ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE_X * FX32_ONE;
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND:
			add.mat.x		= ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND_X * FX32_ONE;
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG:
			add.mat.x		= ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG_X * FX32_ONE;
			break;

		case ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC:
			add.mat.x		= ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC_X * FX32_ONE;
			break;
		}

		// 登録　アニメーション設定
		p_draw->clact[ i ] = CLACT_AddSimple( &add );
		CLACT_AnmChg( p_draw->clact[ i ], i );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクター破棄
 *
 *	@param	p_draw		描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubDeleteClact( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM; i++ ){
		CLACT_Delete( p_draw->clact[i] );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM作成
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubAddFontOam( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, int heap )
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM破棄
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubDeleteFontOam( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw )
{
}


//----------------------------------------------------------------------------
/**
 *	@brief	フェードインアウトのために半透明OAMにする
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonOamFadeInit( ZKN_ZUKAN_COMMON_DRAW* p_draw )
{
//	CLACT_ObjModeSet( p_draw->icon, GX_OAM_MODE_XLU );
	int i;

	for( i=0; i<ZKN_ZUKAN_COMMON_APL_NUM; i++ ){
		FONTOAM_ObjModeSet( p_draw->p_title[ i ]->p_fontoam, GX_OAM_MODE_XLU );
	}	
}

//----------------------------------------------------------------------------
/**
 *	@brief	半透明OAM設定を破棄
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonOamFadeDelete( ZKN_ZUKAN_COMMON_DRAW* p_draw )
{
//	CLACT_ObjModeSet( p_draw->icon, GX_OAM_MODE_NORMAL );
	int i;

	for( i=0; i<ZKN_ZUKAN_COMMON_APL_NUM; i++ ){
		FONTOAM_ObjModeSet( p_draw->p_title[ i ]->p_fontoam, GX_OAM_MODE_NORMAL );
	}	
}


//----------------------------------------------------------------------------
/**
 *	@brief	サブ画面アプリケーション変更処理
 *
 *	@param	p_glb	グローバル
 *	@param	apply	変更アプリケーション
 *	@param	last_apply	前のアプリケーション
 *
 *	@retval	TRUE	変更します
 *	@retval	FALSE	変更しません
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanCommonSubApplyChange( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb, int apply, int last_apply )
{
	ZKN_ZUKAN_COMMON_GLB* p_main_glb = p_glb->p_main_common_glb;
	BOOL ret;
	
	ret = ZknZukanCommonChangeApply( p_main_glb, apply, last_apply );
	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	メイン関数　メイン
 *
 *	@param	p_glb		グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubProcDoFuncMainMain( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	ZKN_ZUKAN_COMMON_GLB* p_main_glb = p_glb->p_main_common_glb;

	ZknZukanCommonSubOtherDoMain( p_glb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	その他共通アプリのメイン動作
 *
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubOtherDoMain( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	ZKN_ZUKAN_COMMON_GLB* p_main_glb = p_glb->p_main_common_glb;
	int last_apply;
	int next_apply;

	//　キーボタンフラグリセット
	ZknZUkanCommonSubKeyFlagReset( p_glb );


	if( sys.trg & PAD_BUTTON_B ){
		// ポケモンリストへ
		ZknZukanCommon_MainChangePokelist( p_main_glb );
		// 戻るキーボタンを押した
		p_glb->back_key_push = TRUE;
		// キャンセル音
		Snd_SePlay( ZKN_SND_CANCEL );
		return;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	キーボタンフラグリセット
 *
 *	@param	p_glb 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZUkanCommonSubKeyFlagReset( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	// 戻るキーボタンを押したか初期化
	p_glb->back_key_push = FALSE;

}


//----------------------------------------------------------------------------
/**
 *	@brief	カーソルデータ作成
 *	
 *	@param	p_work	ワーク
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubCursorMake( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb, int heap )
{
	int move_mode;

	p_work->p_cursor_tbl = sys_AllocMemory( heap, sizeof(ZKN_CURSOR_ONEDATA) * ZKN_ZUKAN_COMMON_SUB_CURSOR_NUM );

	// カーソル移動データ設定
	ZKN_CURSOR_SetOneData( 
			&p_work->p_cursor_tbl[ ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA ],
			ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA_X, 
			ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA_Y,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZX,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZY,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA );

	ZKN_CURSOR_SetOneData( 
			&p_work->p_cursor_tbl[ ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE ],
			ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE_X, 
			ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE_Y,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZX,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZY,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE );

	ZKN_CURSOR_SetOneData( 
			&p_work->p_cursor_tbl[ ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND ],
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND_X, 
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND_Y,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZX,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZY,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND );

	ZKN_CURSOR_SetOneData( 
			&p_work->p_cursor_tbl[ ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG ],
			ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG_X, 
			ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG_Y,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZX,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZY,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG );

	if( ZKN_GLBDATA_PokeGraphicVersionFlagGet( p_glb->p_glb ) == TRUE ){
		move_mode = ZKN_CURSOR_MOVE_NORMAL;
	}else{
		move_mode = ZKN_CURSOR_MOVE_SKIP;
	}
	ZKN_CURSOR_SetOneData( 
			&p_work->p_cursor_tbl[ ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC ],
			ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC_X, 
			ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC_Y,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZX,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZY,
			move_mode,
			move_mode,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC );

	ZKN_CURSOR_SetOneData( 
			&p_work->p_cursor_tbl[ ZKN_ZUKAN_COMMON_SUB_CURSOR_BACK ],
			ZKN_ZUKAN_COMMON_SUB_CURSOR_BACK_X, 
			ZKN_ZUKAN_COMMON_SUB_CURSOR_BACK_Y,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZX,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZY,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_BACK );

	// カーソルデータ設定
	p_work->p_cursor = ZKN_CURSOR_Alloc( heap );
	ZKN_CURSOR_Init( p_work->p_cursor, p_work->p_cursor_tbl,
			ZKN_ZUKAN_COMMMON_SUB_CURSOR_MAX_X,
			ZKN_ZUKAN_COMMMON_SUB_CURSOR_MAX_Y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル動作
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubCursorMove( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	ZKN_ZUKAN_COMMON_GLB* p_main_glb = p_glb->p_main_common_glb;

	// Bボタンが押されていたら実行しない
	if( p_glb->back_key_push ){
		return ;
	}
	
	if( sys.trg & PAD_KEY_RIGHT ){
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_ADD_X, 1 );
//		Snd_SePlay( ZKN_SND_SELECT );
	}

	if( sys.trg & PAD_KEY_LEFT ){
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_ADD_X, -1 );
//		Snd_SePlay( ZKN_SND_SELECT );
	}

	// カーソル位置の機能を実行
	if( sys.trg & PAD_BUTTON_A ){

		switch( ZKN_CURSOR_GetContID( p_work->p_cursor ) ){
		case ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_ZUKAN00 ){
				ZknZukanCommonChangeApply( p_main_glb, ZKN_ZUKAN_COMMON_APL_ZUKAN00, p_main_glb->now_apply );
				p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA ] = BMN_EVENT_HOLD;

				// 選択移動音
				Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
			}
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_RANGE ){
				ZknZukanCommonChangeApply( p_main_glb, ZKN_ZUKAN_COMMON_APL_RANGE, p_main_glb->now_apply );
				p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE ] = BMN_EVENT_HOLD;

				// 選択移動音
				Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
			}
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_SOUND ){
				ZknZukanCommonChangeApply( p_main_glb, ZKN_ZUKAN_COMMON_APL_SOUND, p_main_glb->now_apply );
				p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND ] = BMN_EVENT_HOLD;

				// 選択移動音
				Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
			}
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_BIG ){

				// ちゃんと変更されるかチェック
				if( ZknZukanCommonChangeApply( p_main_glb, ZKN_ZUKAN_COMMON_APL_BIG, p_main_glb->now_apply ) ){
					p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG ] = BMN_EVENT_HOLD;
	
					// 選択移動音
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
				}else{

					if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_SOUND ){	// 鳴き声画面ならならさない
						// キャンセル音
						Snd_SePlay( ZKN_SND_CANCEL );
					}
				}
			}
			break;

		case ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_GRAPHIC ){
				// ちゃんと変更されるかチェック
				if( ZknZukanCommonChangeApply( p_main_glb, ZKN_ZUKAN_COMMON_APL_GRAPHIC, p_main_glb->now_apply ) ){
					p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC ] = BMN_EVENT_HOLD;	
	
					// 選択移動音
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
				}else{

					if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_SOUND ){	// 鳴き声画面ならならさない
						// キャンセル音
						Snd_SePlay( ZKN_SND_CANCEL );
					}
				}
			}
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_CURSOR_BACK:
			// ポケモンリストへ
			ZknZukanCommon_MainChangePokelist( p_main_glb );
			// 戻るキーボタンを押した
			p_glb->back_key_push = TRUE;
			p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK ] = BMN_EVENT_HOLD;
			// キャンセル音
			Snd_SePlay( ZKN_SND_CANCEL );
			break;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソルデータ破棄
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubCursorDelete( ZKN_ZUKAN_COMMON_SUB_WORK* p_work )
{
	sys_FreeMemoryEz( p_work->p_cursor_tbl );
	ZKN_CURSOR_Free( p_work->p_cursor );
	p_work->p_cursor = NULL;
	p_work->p_cursor_tbl = NULL;
}


//----------------------------------------------------------------------------
/**
 *	@brief	カーソル初期化処理
 *
 *	@param	p_work
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubCursorInit( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	ZKN_ZUKAN_COMMON_GLB* p_main_glb = p_glb->p_main_common_glb;

	// カーソルの操作は共通アプリ（自分）が持つ
	p_glb->sub_cursor_flag = FALSE;

	switch( p_main_glb->now_apply ){
	case ZKN_ZUKAN_COMMON_APL_ZUKAN00:
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_SET_CONTID, ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA );
		break;
		
	case ZKN_ZUKAN_COMMON_APL_RANGE:
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_SET_CONTID, ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE );
		break;
		
	case ZKN_ZUKAN_COMMON_APL_SOUND:
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_SET_CONTID, ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND );
		break;
		
	case ZKN_ZUKAN_COMMON_APL_BIG:
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_SET_CONTID, ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG );
		break;

	case ZKN_ZUKAN_COMMON_APL_GRAPHIC:
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_SET_CONTID, ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC );
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル処理のメインサブを切り替える
 *
 *	@param	p_work	　ワーク
 *	@param	p_glb	　グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubCursorKeyMove( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	ZKN_ZUKAN_COMMON_GLB* p_main_glb = p_glb->p_main_common_glb;


	// 以下のアプリのときはサブアプリがカーソル操作しない
	if( (p_main_glb->now_apply == ZKN_ZUKAN_COMMON_APL_ZUKAN00) ){
		return ;
	}
	
	// 今どっち側の操作に対応しているのかチェック
	if( (p_glb->sub_cursor_flag == FALSE) ){
		
		// 共通アプリが操作している
		if( sys.trg & PAD_KEY_DOWN ){
			p_glb->sub_cursor_flag = TRUE;
		}
	}else{

		// サブアプリが操作している
		if( sys.trg & PAD_KEY_UP ){
			p_glb->sub_cursor_flag = FALSE;
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	カーソル初期化
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_work		データワーク
 *	@param	cp_glb		データグローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubCursorDrawInit( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_WORK* cp_work, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb )
{
	// カーソル初期化座標設定
	ZKN_UTIL_CursorSetMatrixCursorSysNotAnm( cp_work->p_cursor, p_drawglb->p_drawglb );
	// カーソル動作
	ZknZukanCommonSubCursorDrawPack( p_drawglb, cp_work, cp_glb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル描画処理パック関数
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_work		データワーク
 *	@param	cp_glb		データグローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubCursorDrawPack( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_WORK* cp_work, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb )
{
	BOOL check;
	
	//　表示ＯＮＯＦＦとカーソル動作
	if( (ZKN_GLBDATA_TouchCursorFlagGet( cp_glb->p_glb ) == TRUE) ){

		check = ZknZukanCommonSubCursorOnOff( p_drawglb, TRUE );

		// 自分がカーソルを動かして良いときのみ動作させる
		if( (cp_glb->sub_cursor_flag == FALSE) ){

			if( check ){
				// 再描画されたときは,カーソル描画座標を初期化
				// カーソル初期化座標設定
				ZKN_UTIL_CursorSetMatrixCursorSysNotAnm( cp_work->p_cursor, p_drawglb->p_drawglb );
			}

			ZknZukanCommonSubCursorDraw( p_drawglb, cp_work );
		}
	}else{
		ZknZukanCommonSubCursorOnOff( p_drawglb, FALSE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑カーソル描画処理
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	p_work		データワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubCursorDraw( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_WORK* cp_work )
{
	ZKN_GLB_DRAWDATA* p_draw = p_drawglb->p_drawglb;
	
	ZKN_UTIL_CursorSetMatrixCursorSys( cp_work->p_cursor, p_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル描画ONOFF
 *
 *	@param	p_draw	描画ワーク
 *	@param	flag	ONOFFフラグ
 *	
 *	@retval	TRUE	値変更
 *	@retval	FALSE	変更しなかった
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanCommonSubCursorOnOff( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb,  BOOL flag )
{
	ZKN_GLB_DRAWDATA* p_draw = p_drawglb->p_drawglb;
	
	if( ZKN_UTIL_CursorGetDrawFlag( &p_draw->cursor ) != flag ){
		ZKN_UTIL_CursorSetDrawFlag( &p_draw->cursor, flag );
		return TRUE;
	}
	
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑フォントOAM変更
 *
 *	@param	p_draw
 *	@param	apl		アプリﾅﾝﾊﾞｰ
 *	@param	old_apl	1個前のアプリ
 * 
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonFontOamChg( ZKN_ZUKAN_COMMON_DRAW* p_draw, int apl, int old_apl  )
{
	FONTOAM_SetDrawFlag( p_draw->p_title[ old_apl ]->p_fontoam, FALSE );
	FONTOAM_SetDrawFlag( p_draw->p_title[ apl ]->p_fontoam, TRUE );
}

// グラフィックパターンボタンの描画ONOF
//----------------------------------------------------------------------------
/**
 *	@brief	グラフィックバージョンボタンの表示ONOFF
 *
 *	@param	p_draw		描画ワーク
 *	@param	cp_glb		グローバルﾃﾞｰﾀ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubSetGraVerButtonDrawFlag( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb )
{
	if( ZKN_GLBDATA_PokeGraphicVersionFlagGet( cp_glb->p_glb ) == FALSE ){
		CLACT_SetDrawFlag( p_draw->clact[ ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC ], FALSE );
	}
}
