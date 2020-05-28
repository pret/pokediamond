//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_range.c
 *	@brief		分布図アプリケーション
 *	@author		tomoya takahashi
 *	@data		2006.01.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"

#include "src/application/zukanlist/zkn_data/zkn_hidemap.dat"

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

#include "include/application/zukanlist/zkn_encount_draw.h"
#include "include/application/zukanlist/zkn_range_data.h"

#include "include/system/timezone.h"

#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_zukan_common.h"

#define	__ZKN_RANGE_H_GLOBAL
#include "include/application/zukanlist/zkn_range.h"


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
#define ZKN_RANGE_EVENT_NUM ( 0 )			// イベント数
//#define ZKN_RANGE_EVENT_CHANGE_SOUND ( 0x1 << 1 )	// 泣き声へ

#define ZKN_RANGE_OAM_BG_PRI	( 1 )
#define ZKN_RANGE_OAM_PRI	( 31 )

//-------------------------------------
//	シーケンス
//=====================================
enum{
	ZKN_RANGE_SEQINIT_ALLOC,
	ZKN_RANGE_SEQINIT_LOAD,
	ZKN_RANGE_SEQINIT_FADEIN,
	ZKN_RANGE_SEQINIT_END,
};
enum{
	ZKN_RANGE_SEQDELETE_FADEOUT_INIT,
	ZKN_RANGE_SEQDELETE_FADEOUT,
	ZKN_RANGE_SEQDELETE_RELEASE,
	ZKN_RANGE_SEQDELETE_FREE,
	ZKN_RANGE_SEQDELETE_END,
};

// 生息地不明
#define ZKN_RANGE_NONE_OAM_X	( 160 )
#define ZKN_RANGE_NONE_OAM_Y	( 96 )
#define ZKN_RANGE_NONE_FONTOAM_OFS_X	( -53 )
#define ZKN_RANGE_NONE_FONTOAM_OFS_Y	( -8 )
#define ZKN_RANGE_NONE_FONTOAM_BMP_SIZX	( 16 )
#define ZKN_RANGE_NONE_FONTOAM_BMP_SIZY	( 2 )
#define ZKN_RANGE_NONE_OAM_SEQ	( 2 )

#define ZKN_RANGE_FONTOAM_PAL_OFS	(2)

// 隠しマップ配置位置
#define ZKN_RANGE_HIDEMAP_D15_X	( 13 )
#define ZKN_RANGE_HIDEMAP_D15_Y	( 8 )
#define ZKN_RANGE_HIDEMAP_D18_X	( 28 )
#define ZKN_RANGE_HIDEMAP_D18_Y	( 7 )
#define ZKN_RANGE_HIDEMAP_D30_X	( 11 )
#define ZKN_RANGE_HIDEMAP_D30_Y	( 8 )
#define ZKN_RANGE_HIDEMAP_L04_X	( 25 )
#define ZKN_RANGE_HIDEMAP_L04_Y	( 16 )



// 分布図グリッド数
#define ZKN_RANGE_GRID_NUM_X	( 30 )
#define ZKN_RANGE_GRID_NUM_Y	( 30 )
#define ZKN_RANGE_GRID_ARRAY_SIZE	( ZKN_RANGE_GRID_NUM_X * ZKN_RANGE_GRID_NUM_Y )
#define ZKN_RANGE_GRAPHIC_GRID_SIZE	( 5 )
#define ZKN_RANGE_BMP_DRAW_X	( 89 )
#define ZKN_RANGE_BMP_DRAW_Y	( 30 )



// ダンジョンOAM
#define ZKN_RANGE_DAN_OAMNORM_SP_SEQ	( 0 )
#define ZKN_RANGE_DAN_OAMSP_SP_SEQ		( 1 )
#define ZKN_RANGE_DAN_OAMNORM_NORM_SEQ	( 2 )
#define ZKN_RANGE_DAN_OAMSP_NORM_SEQ	( 3 )
#define ZKN_RANGE_DAN_OAM_BUFF_NUM		( ZKN_DAN_ID_MAX*2 )
#define ZKN_RANGE_DAN_DRAW_X	( 92 )
#define ZKN_RANGE_DAN_DRAW_Y	( 32 )
// ヒンバス用
#define ZKN_RANGE_DAN_OAMNORM_HIN_SEQ	( 4 )	// ヒンバス用
#define ZKN_RANGE_DAN_OAMSP_HIN_SEQ		( 5 )	// ヒンバス用
#define ZKN_RANGE_DAN_HIN_DRAW_OFS_X	( 0 ) 
#define ZKN_RANGE_DAN_HIN_DRAW_OFS_Y	( -18 )

// あさ　ひる　よる
#define ZKN_RANGE_TYPE_OAM_X	( 32 )
#define ZKN_RANGE_TYPE_OAM_Y	( 32 )
#define ZKN_RANGE_TYPE_FONTOAM_BMP_SIZX	( 9 )
#define ZKN_RANGE_TYPE_FONTOAM_BMP_SIZY	( 2 )


// フェード用
#define ZKN_RANGE_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

// 描画動作用
#define ZKN_RANGE_DRAW_MOVE_COUNT_MAX	( 32 )
#define ZKN_RANGE_DRAW_MOVE_COUNT_HALF	( 16 )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	分布図画面　グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DATA*		p_glb;				// グローバルデータ
	int					type;				// 表示分布タイプ

	// メインコモングローバル
	ZKN_APL_DATA*	p_main_common;	// アプリデータ
} ZKN_RANGE_GLB;

//-------------------------------------
//	分布図画面	描画グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// 描画グローバルデータ

	int pokegra_move_x;
	int pokegra_move_y;

	int fade_mode;		// フェードモード

	int move_sync;		// 動作シンク数
} ZKN_RANGE_DRAWGLB;


//-------------------------------------
//	分布図画面　内部ワーク
//=====================================
typedef struct {
	// ローカル分布タイプ
	int type;

	u8* p_hidemap_fld;
	u8* p_hidemap_dan;
	u32 hidemap_fld_num;
	u32 hidemap_dan_num;

	
	// ダンジョン　フィールド　分布データ
	ZKN_RANGE_DATA_MONS dan_range;	// 通常
	ZKN_RANGE_DATA_MONS fld_range;	// 通常
	ZKN_RANGE_DATA_MONS dansp_range;	// 特殊
	ZKN_RANGE_DATA_MONS fldsp_range;	// 特殊

} ZKN_RANGE_WORK;

//-------------------------------------
//	分布図画面　内部ワーク
//=====================================
typedef struct {
	// ローカル分布タイプ
	int type;

	// ダンジョン位置OAM
	CLACT_WORK_PTR danzyon_icon[ ZKN_RANGE_DAN_OAM_BUFF_NUM ];
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];
	int now_use;	
	
	// 生息地不明
	CLACT_WORK_PTR range_none;
	ZKN_FONTOAM_DATA* range_none_font;
	CLACT_U_RES_OBJ_PTR res_obj_other[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	// あさひるよる
	ZKN_FONTOAM_DATA* range_mode_font[ ZKN_RANGE_TYPE_NUM ];

	// 分布図グリッドデータ
	u8 range_grid_data[ ZKN_RANGE_GRID_ARRAY_SIZE ];	// 通常
	u8 range_grid_spdata[ ZKN_RANGE_GRID_ARRAY_SIZE ];	// 特殊

	// 分布図キャラクタデータ
	void * p_range_char_buff;			// 通常
	NNSG2dCharacterData* p_range_char;
	void * p_rangesp_char_buff;			//　特殊
	NNSG2dCharacterData* p_rangesp_char;

	// ダンジョン　フィールド描画データ
	ZKN_RANGE_DATA_DAN_GRID* p_dan_grid;
	ZKN_RANGE_DATA_FLD_GRID* p_fld_grid;

	// OAMとBGを交互に点滅させるワーク
	int drawmove_count;	// カウンタ
	int drawmove_flag;	// 動作フラグ

	// ポケリストフェード用動作ワーク
	ZKN_UTIL_MOVE_WORK pokegra_move;


	// 隠しマップで排除される可能性があるため、
	// 実際に存在した分布データ数
	u32 dan_range_num;
	u32 fld_range_num;
	u32 dansp_range_num;
	u32 fldsp_range_num;
} ZKN_RANGE_DRAW;

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
static ZKN_RANGE_GLB* MakeRangeGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_RANGE_DRAWGLB* MakeRangeDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
//static ZKN_EVENT_DATA* MakeRangeEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteRangeGlb( ZKN_RANGE_GLB* p_glb );
static void DeleteRangeDrawGlb( ZKN_RANGE_DRAWGLB* p_glb );
//static void DeleteRangeEvent( ZKN_EVENT_DATA* p_event );


static int RangeEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
static int ZknRangeProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknRangeProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknRangeProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknRangeProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknRangeProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknRangeProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// ポケグラ
static void ZknRangePokeGraOn( ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb );
static void ZknRangePokeGraOff( ZKN_RANGE_DRAWGLB* p_drawglb );

// フェード処理
static void ZknRangeOamFadeInit( ZKN_RANGE_DRAW* p_draw );
static void ZknRangeOamFadeDelete( ZKN_RANGE_DRAW* p_draw );
static void ZknRangeFadeInit( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknRangeFadeMain( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, BOOL fadein_out );
static void ZknRangeFadeOtherInit( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknRangeFadeOtherMain( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, BOOL fadein_out );

// Resource読み込み
static void ZknRangeLoadRes( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, const ZKN_RANGE_WORK* cp_datawork, int heap );
static void ZknRangeDeleteRes( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb );
static void ZknRangeSetUpBg( ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, int heap );
static void ZknRangeBgCharLoad( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, int heap );
static void ZknRangeBgCharDelete( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb );
static void ZknRangeOamResLoad( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, int heap );
static void ZknRangeOamResDelete( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb );
static void ZknRangeOamInit( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, int heap );
static void ZknRangeOamDelete( ZKN_RANGE_DRAW* p_draw );
static void ZknRangeFontOamInit( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, int heap );
static void ZknRangeFontOamDelete( ZKN_RANGE_DRAW* p_draw );

static void ZknRangeRangeNoneDrawSet( ZKN_RANGE_DRAW* p_draw, const ZKN_RANGE_WORK* p_work );
static void ZknRangeRangeTypeOn( ZKN_RANGE_DRAW* p_draw, int type );

static void ZknRangeGraphicChange( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, const ZKN_RANGE_WORK* cp_datawork, int heap );

// 分布グラフィックデータ作成
static void ZknRangeGraphicDataMake( ZKN_RANGE_DRAW* p_draw, const ZKN_RANGE_GLB* cp_glb, const ZKN_RANGE_WORK* cp_datawork, int heapID );
static void ZknRangeGraphicDataDelete( ZKN_RANGE_DRAW* p_draw );
static u8* ZknRangeGraphicDataFldHideMapTblGet( u32 heap, const ZKN_RANGE_GLB* cp_glb, u32* p_tbl_num );
static u8* ZknRangeGraphicDataDanHideMapTblGet( u32 heap, const ZKN_RANGE_GLB* cp_glb, u32* p_tbl_num );

static void ZknRangeGraphicDrawMain( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb );

// OAMとBGを交互に点滅させる
static void ZknRangeGraphicDrawMoveInit( ZKN_RANGE_DRAW* p_draw );
static void ZknRangeGraphicDrawMoveStart( ZKN_RANGE_DRAW* p_draw );
static void ZknRangeGraphicDrawMoveMain( ZKN_RANGE_DRAW* p_draw );

// 分布データ関係
static void ZknRangeMonsRangeDataLoad( ZKN_RANGE_WORK* p_work, ZKN_RANGE_GLB* p_glb, int heap );
static void ZknRangeMonsRangeDataDelete( ZKN_RANGE_WORK* p_work );
//----------------------------------------------------------------------------
/**
 *
 *	@brief	分布図　アプリ作成
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
void ZKN_RangeAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_RANGE_GLB*	p_glb;
	ZKN_RANGE_DRAWGLB*	p_drawglb;
//	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeRangeGlb( heap, zkn_sys );
	p_drawglb = MakeRangeDrawGlb( heap, zkn_sys );
//	p_event = MakeRangeEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= NULL;
//	p_data->p_event_data	= p_event;
	p_data->event_num		= RangeEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknRangeProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknRangeProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknRangeProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknRangeProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknRangeProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknRangeProcDrawFuncDelete;
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
void ZKN_RangeAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteRangeGlb( p_data->p_glb_data ); 
	DeleteRangeDrawGlb( p_data->p_glb_draw ); 
//	DeleteRangeEvent( p_data->p_event_data );
}


// 分布タイプ設定
//----------------------------------------------------------------------------
/**
 *	@brief	分布タイプ取得
 *	
 *	@param	p_data	分布アプリデータ
 *
 *	@return	分布タイプ
 */
//-----------------------------------------------------------------------------
int ZKN_RangeTypeGet( const ZKN_APL_DATA* p_data )
{
	const ZKN_RANGE_GLB* cp_glb = p_data->p_glb_data;

	return cp_glb->type;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑タイプ設定
 *
 *	@param	p_data	分布アプリデータ
 *	@param	type	分布タイプ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_RangeTypeSet( ZKN_APL_DATA* p_data, int type )
{
	ZKN_RANGE_GLB* p_glb = p_data->p_glb_data;

	GF_ASSERT( type < ZKN_RANGE_TYPE_NUM );

	p_glb->type = type;
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
void ZKN_RangePokeGraFadeOutSet( ZKN_APL_DATA* p_data, int x, int y )
{
	ZKN_RANGE_DRAWGLB* p_glb = p_data->p_glb_draw;

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
void ZKN_RangeFadeModeSet( ZKN_APL_DATA* p_data, int fade_mode )
{
	ZKN_RANGE_DRAWGLB* p_glb = p_data->p_glb_draw;

	p_glb->fade_mode = fade_mode;
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェードシンク数設定
 *
 *	@param	p_data		アプリケーションデータ
 *	@param	fade_sync	フェードシンク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_RangeFadeModeSync( ZKN_APL_DATA* p_data, int fade_sync )
{
	ZKN_RANGE_DRAWGLB* p_glb = p_data->p_glb_draw;

	p_glb->move_sync = fade_sync;
}



//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	分布図　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_RANGE_GLB* MakeRangeGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_RANGE_GLB* p_glb;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_RANGE_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_RANGE_GLB) );

	// グローバルデータ
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	// めいんグローバルアプリデータ取得
	p_glb->p_main_common = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_COMMON );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	作成したデータ
 */
//-----------------------------------------------------------------------------
static ZKN_RANGE_DRAWGLB* MakeRangeDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_RANGE_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_RANGE_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_RANGE_DRAWGLB) );

	// 描画データ
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	分布図　イベント作成
 *
 *	@param	heap		使用するヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	イベントデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeRangeEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = RangeEventDataNumGet();

	// イベントデータテーブル作成
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	MakeRangeChangeSound( heap, &p_event_tbl[0], zkn_sys );

	return p_event_tbl;
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	分布図　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteRangeGlb( ZKN_RANGE_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	分布図　描画グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteRangeDrawGlb( ZKN_RANGE_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}
#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	分布図　イベントデータ破棄
 *
 *	@param	p_event	イベントデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteRangeEvent( ZKN_EVENT_DATA* p_event )
{
	GF_ASSERT( p_event );
	
	ZKN_EVENT_DeleteData( &p_event[0] );

	sys_FreeMemoryEz( p_event );
}
#endif


//----------------------------------------------------------------------------
/**
 *
 *	@brief	分布図アプリ　イベント数取得
 *	
 *	@param	none	
 *
 *	@return	分布図アプリ　イベント数
 *
 *
 */
//-----------------------------------------------------------------------------
static int RangeEventDataNumGet( void )
{
	return ZKN_RANGE_EVENT_NUM;
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
static int ZknRangeProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_RANGE_GLB* p_glb = p_glbdata;
	ZKN_RANGE_WORK* p_work;
	
	// ワーク作成
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_RANGE_WORK) );
	GF_ASSERT( p_work );
	memset( p_work, 0, sizeof(ZKN_RANGE_WORK) );
	p_dodata->p_work = p_work;
	
	
	// 現在時間から初期分布データタイプを設定
	if( p_glb->p_glb->time_zone == TIMEZONE_MORNING ){
		p_glb->type = ZKN_RANGE_TYPE_MORNING;
	}else{
		if( (p_glb->p_glb->time_zone == TIMEZONE_NOON) ||
			(p_glb->p_glb->time_zone == TIMEZONE_EVENING) ){
			p_glb->type = ZKN_RANGE_TYPE_NOON;
		}else{
			p_glb->type = ZKN_RANGE_TYPE_NIGHT;
		}
	}

	// 隠しマップ情報作成
	p_work->p_hidemap_fld = ZknRangeGraphicDataFldHideMapTblGet( p_dodata->heap, p_glb, &p_work->hidemap_fld_num );
	p_work->p_hidemap_dan = ZknRangeGraphicDataDanHideMapTblGet( p_dodata->heap, p_glb, &p_work->hidemap_dan_num );

	
	// 分布データ作成
	ZknRangeMonsRangeDataLoad( p_work, p_glb, p_dodata->heap );
	p_work->type = p_glb->type;	// ローカルにも反映
	
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
static int ZknRangeProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_RANGE_GLB* p_glb = p_glbdata;
	ZKN_RANGE_WORK* p_work = p_dodata->p_work;
	
	// 終了へ
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	// タイプが変わったら分布データを変更する
	if( p_work->type != p_glb->type ){
		ZknRangeMonsRangeDataDelete( p_work );
		ZknRangeMonsRangeDataLoad( p_work, p_glb, p_dodata->heap );
		p_work->type = p_glb->type;	// ローカルにも反映
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
static int ZknRangeProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_RANGE_WORK* p_work = p_dodata->p_work;

	// 隠しマップテーブル破棄
	if( p_work->p_hidemap_fld ){
		sys_FreeMemoryEz( p_work->p_hidemap_fld );
	}
	if( p_work->p_hidemap_dan ){
		sys_FreeMemoryEz( p_work->p_hidemap_dan );
	}

	// 分布データ破棄
	ZknRangeMonsRangeDataDelete( p_work );
	
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
static int ZknRangeProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_RANGE_GLB* cp_dataglb = cp_glbdata;
	const ZKN_RANGE_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_RANGE_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_RANGE_DRAW* p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_RANGE_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_RANGE_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_RANGE_DRAW) );

		p_drawwork = p_drawdata->p_work;
		p_drawwork->type = cp_dataglb->type;	// 初期化タイプ設定

		// グリッドデータ取得
		p_drawwork->p_dan_grid = ZKN_RANGEDATA_GetDanGridOamData( p_drawdata->heap, NULL );		
		p_drawwork->p_fld_grid = ZKN_RANGEDATA_GetFldGridAraaData( p_drawdata->heap, NULL );		
		
		p_drawdata->seq++;
		break;
		
	case ZKN_RANGE_SEQINIT_LOAD:
		ZknRangeLoadRes( p_drawwork, p_drawglb, cp_dataglb, cp_datawork, p_drawdata->heap );

		// 分布描画データ作成
		ZknRangeGraphicDataMake( p_drawdata->p_work, cp_dataglb, cp_datawork, p_drawdata->heap );

		// 生息地不明表示
		ZknRangeRangeNoneDrawSet( p_drawdata->p_work, cp_datawork );


		// 描画動作初期化
		ZknRangeGraphicDrawMoveInit( p_drawwork );

		// 分布データ描画
		ZknRangeGraphicDrawMain( p_drawwork, p_drawglb );
		
		// フェード初期化
		if( p_drawglb->fade_mode == ZKN_RANGE_FADE_MODE_MY ){
			ZknRangeFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		}else{
			ZknRangeFadeOtherInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		}
		p_drawdata->seq++;
		break;
		
	case ZKN_RANGE_SEQINIT_FADEIN:
		if( p_drawglb->fade_mode == ZKN_RANGE_FADE_MODE_MY ){
			check = ZknRangeFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		}else{
			check = ZknRangeFadeOtherMain( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		}
		if( check ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_RANGE_SEQINIT_END:
		// 動作開始
		ZknRangeGraphicDrawMoveStart( p_drawwork );
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
static int ZknRangeProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_RANGE_GLB* cp_dataglb = cp_glbdata;
	const ZKN_RANGE_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_RANGE_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_RANGE_DRAW* p_drawwork = p_drawdata->p_work;


	// 描画動作メイン
	ZknRangeGraphicDrawMoveMain( p_drawwork );
	
	//分布グラフィック更新
	ZknRangeGraphicChange( p_drawwork, p_drawglb, cp_dataglb, cp_datawork, p_drawdata->heap );

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
static int ZknRangeProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_RANGE_GLB* cp_dataglb = cp_glbdata;
	const ZKN_RANGE_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_RANGE_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_RANGE_DRAW* p_drawwork = p_drawdata->p_work;
	BOOL check;


	switch( p_drawdata->seq ){
	case ZKN_RANGE_SEQDELETE_FADEOUT_INIT:
		// 描画動作初期化
		ZknRangeGraphicDrawMoveInit( p_drawwork );

		if( p_drawglb->fade_mode == ZKN_RANGE_FADE_MODE_MY ){
			ZknRangeFadeInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		}else{
			ZknRangeFadeOtherInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		}
		p_drawdata->seq++;
		break;
		
	case ZKN_RANGE_SEQDELETE_FADEOUT:
		if( p_drawglb->fade_mode == ZKN_RANGE_FADE_MODE_MY ){
			check = ZknRangeFadeMain( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		}else{
			check = ZknRangeFadeOtherMain( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		}
		if( check ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_RANGE_SEQDELETE_RELEASE:
		
		// 分布描画データ破棄
		ZknRangeGraphicDataDelete( p_drawwork );
		
		ZknRangeDeleteRes( p_drawwork, p_drawglb );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_RANGE_SEQDELETE_FREE:
		// BG1OAMは表示
		GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG1, VISIBLE_ON );

		// グリッドデータ破棄
		sys_FreeMemoryEz( p_drawwork->p_dan_grid );		
		sys_FreeMemoryEz( p_drawwork->p_fld_grid );		

		sys_FreeMemoryEz(p_drawdata->p_work);
		p_drawdata->p_work = NULL;
		p_drawdata->seq++;
		break;
		
		
	case ZKN_RANGE_SEQDELETE_END:
		return ZKN_PROC_TRUE;
	}

	return ZKN_PROC_FALSE;
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
static void ZknRangeLoadRes( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, const ZKN_RANGE_WORK* cp_datawork, int heap )
{
	// BG設定
	ZknRangeSetUpBg( p_drawglb, cp_glb, heap );

	// キャラクタデータ読み込み
	ZknRangeBgCharLoad( p_draw, p_drawglb, heap );

	// OAMリソース読み込み
	ZknRangeOamResLoad( p_draw, p_drawglb, heap );

	// アクター登録
	ZknRangeOamInit( p_draw, p_drawglb, heap );

	// FONTOAM
	ZknRangeFontOamInit( p_draw, p_drawglb, cp_glb, heap );

	// 分布タイプ表示	
	ZknRangeRangeTypeOn( p_draw, cp_glb->type );

	// ポケグラON
	ZknRangePokeGraOn( p_drawglb, cp_glb );
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
static void ZknRangeDeleteRes( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb )
{
	// キャラクタデータ破棄
	ZknRangeBgCharDelete( p_draw, p_drawglb );

	// FONTOAM
	ZknRangeFontOamDelete( p_draw );
	
	// アクター破棄
	ZknRangeOamDelete( p_draw );

	// OAMリソース破棄
	ZknRangeOamResDelete( p_draw, p_drawglb );
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
 *
 * [イベントで出てくる島のスクリーンデータ書き換えもこの中]
 */
//-----------------------------------------------------------------------------
static void ZknRangeSetUpBg( ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// キャラクタデータ転
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_main_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, 0, 0, TRUE, heap );
	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_bg_main1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// フラグを見てスクリーン上書き
	if( cp_glb->p_glb->hidemap_id_D30 ){

		// スクリーンデータ読み込み
		buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_bg_main2a_lzh_NSCR, TRUE, &p_scrn, heap );
		
		// スクリーンデータ書き込み
		GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
				p_scrn->rawData, 
				ZKN_RANGE_HIDEMAP_D15_X, 
				ZKN_RANGE_HIDEMAP_D15_Y,
				p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

		sys_FreeMemoryEz( buff );
	}
	if( cp_glb->p_glb->hidemap_id_D18 ){
		// スクリーンデータ読み込み
		buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_bg_main2b_lzh_NSCR, TRUE, &p_scrn, heap );
		
		// スクリーンデータ書き込み
		GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
				p_scrn->rawData, 
				ZKN_RANGE_HIDEMAP_D18_X, 
				ZKN_RANGE_HIDEMAP_D18_Y,
				p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

		sys_FreeMemoryEz( buff );
	}
	if( cp_glb->p_glb->hidemap_id_D15 ){
		// スクリーンデータ読み込み
		buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_bg_main2c_lzh_NSCR, TRUE, &p_scrn, heap );
		
		// スクリーンデータ書き込み
		GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
				p_scrn->rawData, 
				ZKN_RANGE_HIDEMAP_D30_X, 
				ZKN_RANGE_HIDEMAP_D30_Y,
				p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

		sys_FreeMemoryEz( buff );
	}
	if( cp_glb->p_glb->hidemap_id_L04 ){
		// スクリーンデータ読み込み
		buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_bg_main2d_lzh_NSCR, TRUE, &p_scrn, heap );
		
		// スクリーンデータ書き込み
		GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
				p_scrn->rawData, 
				ZKN_RANGE_HIDEMAP_L04_X, 
				ZKN_RANGE_HIDEMAP_L04_Y,
				p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

		sys_FreeMemoryEz( buff );
	}

	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M );

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
static void ZknRangeOamResLoad(  ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );

	// キャラクタデータ読み込み
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_map_dungeon_lzh_NCGR, TRUE,
			NARC_zukan_zkn_map_dungeon_lzh_NCGR + ZKN_RANGE_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );


	// セルデータ読み込み
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_map_dungeon_lzh_NCER, TRUE,
			NARC_zukan_zkn_map_dungeon_lzh_NCER + ZKN_RANGE_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_map_dungeon_lzh_NANR, TRUE,
			NARC_zukan_zkn_map_dungeon_lzh_NANR + ZKN_RANGE_RES_ID,
			CLACT_U_CELLANM_RES, heap );
	


	
	// キャラクタデータ読み込み
	p_draw->res_obj_other[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main3_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_main3_lzh_NCGR + ZKN_RANGE_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj_other[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj_other[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_draw->res_obj_other[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_data_oam3_NCLR, FALSE, 
			NARC_zukan_zkn_data_oam3_NCLR + ZKN_RANGE_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_BIG_PLTT_LOAD, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj_other[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj_other[ CLACT_U_PLTT_RES ] );


	// セルデータ読み込み
	p_draw->res_obj_other[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main3_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_main3_lzh_NCER + ZKN_RANGE_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj_other[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_main3_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_main3_lzh_NANR + ZKN_RANGE_RES_ID,
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
static void ZknRangeOamResDelete( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;


	CLACT_U_CharManagerDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->res_obj[ CLACT_U_CELLANM_RES ] );



	CLACT_U_CharManagerDelete( p_draw->res_obj_other[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_draw->res_obj_other[ CLACT_U_PLTT_RES ] );

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_obj_other[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw->res_obj_other[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_obj_other[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->res_obj_other[ CLACT_U_CELLANM_RES ] );
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
static void ZknRangeOamInit( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i;
	
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_main3_lzh_NCGR + ZKN_RANGE_RES_ID,
			NARC_zukan_zkn_data_oam3_NCLR + ZKN_RANGE_RES_ID, 
			NARC_zukan_zkn_data_oam_main3_lzh_NCER + ZKN_RANGE_RES_ID,
			NARC_zukan_zkn_data_oam_main3_lzh_NANR + ZKN_RANGE_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_RANGE_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_RANGE_OAM_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	
	// 生息地不明OAM
	add.mat.x = ZKN_RANGE_NONE_OAM_X * FX32_ONE;
	add.mat.y = ZKN_RANGE_NONE_OAM_Y * FX32_ONE;
	p_draw->range_none = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->range_none, ZKN_RANGE_NONE_OAM_SEQ );



	// ダンジョンOAM
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_map_dungeon_lzh_NCGR + ZKN_RANGE_RES_ID,
			NARC_zukan_zkn_data_oam3_NCLR + ZKN_RANGE_RES_ID, 
			NARC_zukan_zkn_map_dungeon_lzh_NCER + ZKN_RANGE_RES_ID,
			NARC_zukan_zkn_map_dungeon_lzh_NANR + ZKN_RANGE_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );
	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_RANGE_OAM_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	add.mat.x = 0;
	add.mat.y = 0;
	for( i=0; i<ZKN_RANGE_DAN_OAM_BUFF_NUM; i++ ){
		p_draw->danzyon_icon[i] = CLACT_AddSimple( &add );
		CLACT_SetDrawFlag( p_draw->danzyon_icon[i], FALSE );	// 非表示に
		CLACT_ObjModeSet( p_draw->danzyon_icon[i], GX_OAM_MODE_XLU );
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
static void ZknRangeOamDelete( ZKN_RANGE_DRAW* p_draw )
{
	int i;

	CLACT_Delete( p_draw->range_none );
	p_draw->range_none = NULL;

	for( i=0; i<ZKN_RANGE_DAN_OAM_BUFF_NUM; i++ ){
		CLACT_Delete( p_draw->danzyon_icon[i] );
		p_draw->danzyon_icon[i] = NULL;
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
static void ZknRangeFontOamInit( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, int heap )
{
	GF_BGL_BMPWIN* win;	// 文字列書き込み先
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR res_obj;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;
	int pltt_ofs;	// パレットアドレス
	int i;

	// 先にCLACTを登録してある必要がある
	GF_ASSERT( p_draw->range_none );

	// パレットのリソースデータ取得
	// パレットプロクシ取得用
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_drawglb->p_drawglb->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_data_oam3_NCLR + ZKN_RANGE_RES_ID );

	// 初期化データの共通部分を作成
	// 共通データ代入
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( res_obj, NULL );
	fontoam_init.bg_pri		 = ZKN_RANGE_OAM_BG_PRI;
	fontoam_init.soft_pri	 = ZKN_RANGE_OAM_PRI - 1;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;

	// パレット転送先アドレス取得
	pltt_ofs = GetPlttProxyOffset( fontoam_init.pltt, NNS_G2D_VRAM_TYPE_2DMAIN );

	
	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_RANGE_NONE_FONTOAM_BMP_SIZX,
			ZKN_RANGE_NONE_FONTOAM_BMP_SIZY );

	// 分布ふてい
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_RANGE_00, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent		 = p_draw->range_none;
	fontoam_init.x			 = ZKN_RANGE_NONE_FONTOAM_OFS_X;
	fontoam_init.y			 = ZKN_RANGE_NONE_FONTOAM_OFS_Y;
	p_draw->range_none_font  = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->range_none_font->p_fontoam, pltt_ofs + ZKN_RANGE_FONTOAM_PAL_OFS );

	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( win );


	// ビットマップウィンドウ作成
	for( i=0; i<ZKN_RANGE_TYPE_NUM; i++ ){
		win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
				ZKN_RANGE_TYPE_FONTOAM_BMP_SIZX,
				ZKN_RANGE_TYPE_FONTOAM_BMP_SIZY );

		// あさ
		ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
				NARC_msg_zkn_dat, ZNK_RANGE_01 + i, 0, 0 );
		fontoam_init.p_bmp		 = win;
		fontoam_init.parent		 = NULL;
		fontoam_init.x			 = ZKN_RANGE_TYPE_OAM_X;
		fontoam_init.y			 = ZKN_RANGE_TYPE_OAM_Y;
		p_draw->range_mode_font[i]  = ZKN_FONTOAM_Make( &fontoam_init );
		FONTOAM_SetPaletteNo( p_draw->range_mode_font[i]->p_fontoam, pltt_ofs + ZKN_RANGE_FONTOAM_PAL_OFS );

		// ビットマップウィンドウ破棄
		ZKN_FONTOAM_DeleteBmp( win );
	}
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
static void ZknRangeFontOamDelete( ZKN_RANGE_DRAW* p_draw )
{
	int i;
	
	ZKN_FONTOAM_Delete( p_draw->range_none_font );

	for( i=0; i<ZKN_RANGE_TYPE_NUM; i++ ){
		ZKN_FONTOAM_Delete( p_draw->range_mode_font[i]  );
	}
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
static void ZknRangeOamFadeInit( ZKN_RANGE_DRAW* p_draw )
{
	int i;
	
	CLACT_ObjModeSet( p_draw->range_none, GX_OAM_MODE_XLU );
	FONTOAM_ObjModeSet( p_draw->range_none_font->p_fontoam, GX_OAM_MODE_XLU );
	for( i=0; i<ZKN_RANGE_TYPE_NUM; i++ ){
		FONTOAM_ObjModeSet( p_draw->range_mode_font[i]->p_fontoam, GX_OAM_MODE_XLU );
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
static void ZknRangeOamFadeDelete( ZKN_RANGE_DRAW* p_draw )
{
	int i;
	
	CLACT_ObjModeSet( p_draw->range_none, GX_OAM_MODE_NORMAL );
	FONTOAM_ObjModeSet( p_draw->range_none_font->p_fontoam, GX_OAM_MODE_NORMAL );
	for( i=0; i<ZKN_RANGE_TYPE_NUM; i++ ){
		FONTOAM_ObjModeSet( p_draw->range_mode_font[ i ]->p_fontoam, GX_OAM_MODE_NORMAL );
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
static void ZknRangeFadeInit( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, BOOL fadein_out )
{
	// 半透明OAM設定
	ZknRangeOamFadeInit( p_draw );

	// ブライトネス処理を行ってよいか
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_RANGE_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_RANGE_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
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
static BOOL ZknRangeFadeMain( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, BOOL fadein_out )
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
			ZknRangeOamFadeDelete( p_draw );
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
static void ZknRangeFadeOtherInit( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, BOOL fadein_out )
{
	// 半透明OAM設定
	ZknRangeOamFadeInit( p_draw );


	// フェードアウトの時だけの処理
	if( fadein_out == FALSE ){
		// ポケモングラフィックフェード
		ZKN_UTIL_MoveReq( &p_draw->pokegra_move, ZKN_RANGE_POKEGRA_DRAW_X, p_drawglb->pokegra_move_x, ZKN_RANGE_POKEGRA_DRAW_Y, p_drawglb->pokegra_move_y, p_drawglb->move_sync);
	}

	// ブライトネスを使って良いかﾁｪｯｸ
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
		
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, p_drawglb->move_sync,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_RANGE_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, p_drawglb->move_sync,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_RANGE_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
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
static BOOL ZknRangeFadeOtherMain( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, BOOL fadein_out )
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
			ZknRangeOamFadeDelete( p_draw );
		}
		return TRUE;
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	分布書き込みキャラクタチップ読み込み
 *
 *	@param	p_draw	描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeBgCharLoad( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, int heap )
{
	// 文字面ビットマップ初期化
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );

	// キャラクタリソース読み込み
	p_draw->p_range_char_buff = ZKN_GLBDATA_CharDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_chip_lzh_NCGR, TRUE, &p_draw->p_range_char, heap );

	// キャラクタリソース読み込み
	p_draw->p_rangesp_char_buff = ZKN_GLBDATA_CharDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_chip2_lzh_NCGR, TRUE, &p_draw->p_rangesp_char, heap );

	// パレットナンバー設定
	GF_BGL_BmpWinSet_Pal( &p_drawglb->p_drawglb->bmp_mfont, 8 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	分布書き込みキャラクタチップ破棄
 *
 *	@param	p_draw 描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeBgCharDelete( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb ) 
{
	// 文字面ビットマップ初期化
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );

	sys_FreeMemoryEz( p_draw->p_range_char_buff );
	p_draw->p_range_char_buff = NULL;
	p_draw->p_range_char = NULL;

	sys_FreeMemoryEz( p_draw->p_rangesp_char_buff );
	p_draw->p_rangesp_char_buff = NULL;
	p_draw->p_rangesp_char = NULL;

	// パレットナンバー設定
	GF_BGL_BmpWinSet_Pal( &p_drawglb->p_drawglb->bmp_mfont, ZKN_BG_FONT_COLOR );
}

// 分布グラフィックデータ作成
//----------------------------------------------------------------------------
/**
 *	@brief	分布グラフィックデータ作成
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	cp_glb			グローバルデータ
 *	@param	cp_datawork		データワーク
 *	@param	heap			ヒープ
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeGraphicDataMake( ZKN_RANGE_DRAW* p_draw, const ZKN_RANGE_GLB* cp_glb, const ZKN_RANGE_WORK* cp_datawork, int heapID )
{
	int i,j;
	int norm_oam, sp_oam;
	int draw_ofs_x, draw_ofs_y;
	int monsno;
	u8* p_rem_appy;	// 排除配列
	int rem_appy_num;

	ZknRangeGraphicDataDelete( p_draw );

	// 分布データから
	// グリッドデータを作成

	// グリッドデータに書き込み
	//　通常
	p_draw->fld_range_num = ZKN_RANGE_DATA_FldGridDataWriteMonsRangeData( p_draw->range_grid_data, ZKN_RANGE_GRID_NUM_X, ZKN_RANGE_GRID_NUM_Y, p_draw->p_fld_grid, &cp_datawork->fld_range, cp_datawork->p_hidemap_fld, cp_datawork->hidemap_fld_num );

	// 特殊から排除する分布ID列を作成する
	rem_appy_num = (cp_datawork->fld_range.num - 1) + cp_datawork->hidemap_fld_num;
	p_rem_appy = sys_AllocMemoryLo( heapID, rem_appy_num );
	for( i=0; i<rem_appy_num; i++ ){
		if( i < cp_datawork->hidemap_fld_num ){
			p_rem_appy[i] = cp_datawork->p_hidemap_fld[i];
		}else{
			p_rem_appy[i] = cp_datawork->fld_range.p_rangeid[i - cp_datawork->hidemap_fld_num ];
		}
	}
	//　特殊
	p_draw->fldsp_range_num = ZKN_RANGE_DATA_FldGridDataWriteMonsRangeData( p_draw->range_grid_spdata, ZKN_RANGE_GRID_NUM_X, ZKN_RANGE_GRID_NUM_Y, p_draw->p_fld_grid, &cp_datawork->fldsp_range, p_rem_appy, rem_appy_num );

	// 特殊から排除する分布ID列を破棄
	sys_FreeMemoryEz( p_rem_appy );
	

	// 丸めキャラクタ処理
	ZKN_ENCOUNTDRAW_MakeMuddyData( p_draw->range_grid_data, ZKN_RANGE_GRID_NUM_X, ZKN_RANGE_GRID_NUM_Y );
	ZKN_ENCOUNTDRAW_MakeMuddyData( p_draw->range_grid_spdata, ZKN_RANGE_GRID_NUM_X, ZKN_RANGE_GRID_NUM_Y );


	// ヒンバスのときはOAMが特殊なものになる
	monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	if( monsno == MONSNO_HINBASU ){
		norm_oam = ZKN_RANGE_DAN_OAMNORM_HIN_SEQ;
		sp_oam = ZKN_RANGE_DAN_OAMSP_HIN_SEQ;
		draw_ofs_x = ZKN_RANGE_DAN_DRAW_X + ZKN_RANGE_DAN_HIN_DRAW_OFS_X;
		draw_ofs_y = ZKN_RANGE_DAN_DRAW_Y + ZKN_RANGE_DAN_HIN_DRAW_OFS_Y;
	}else{
		norm_oam = ZKN_RANGE_DAN_OAMNORM_SP_SEQ;
		sp_oam = ZKN_RANGE_DAN_OAMSP_SP_SEQ;
		draw_ofs_x = ZKN_RANGE_DAN_DRAW_X;
		draw_ofs_y = ZKN_RANGE_DAN_DRAW_Y;
	}

	// ダンジョンデータ設定
	p_draw->now_use = 0;
	p_draw->now_use = ZKN_RANGE_DATA_DanGridDataSetMonsRangeData(
			p_draw->danzyon_icon, p_draw->now_use, ZKN_RANGE_DAN_OAM_BUFF_NUM, 
			draw_ofs_x, draw_ofs_y,
			ZKN_RANGE_GRAPHIC_GRID_SIZE, ZKN_RANGE_GRAPHIC_GRID_SIZE,
			p_draw->p_dan_grid, &cp_datawork->dan_range, 
			ZKN_RANGE_DAN_OAMNORM_NORM_SEQ, norm_oam,
			cp_datawork->p_hidemap_dan, cp_datawork->hidemap_dan_num,
			&p_draw->dan_range_num );

	// 特殊から排除する分布ID列を作成する
	rem_appy_num = (cp_datawork->dan_range.num - 1) + cp_datawork->hidemap_dan_num;
	p_rem_appy = sys_AllocMemoryLo( heapID, rem_appy_num );
	for( i=0; i<rem_appy_num; i++ ){
		if( i < cp_datawork->hidemap_dan_num ){
			p_rem_appy[i] = cp_datawork->p_hidemap_dan[i];
		}else{
			p_rem_appy[i] = cp_datawork->dan_range.p_rangeid[i - cp_datawork->hidemap_dan_num];
		}
	}

	p_draw->now_use = ZKN_RANGE_DATA_DanGridDataSetMonsRangeData(
			p_draw->danzyon_icon, p_draw->now_use, ZKN_RANGE_DAN_OAM_BUFF_NUM, 
			draw_ofs_x, draw_ofs_y,
			ZKN_RANGE_GRAPHIC_GRID_SIZE, ZKN_RANGE_GRAPHIC_GRID_SIZE,
			p_draw->p_dan_grid, &cp_datawork->dansp_range, 
			ZKN_RANGE_DAN_OAMSP_NORM_SEQ, sp_oam,
			p_rem_appy, rem_appy_num,
			&p_draw->dansp_range_num  );//*/

	// 特殊から排除する分布ID列を破棄
	sys_FreeMemoryEz( p_rem_appy );
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	グリッドデータ破棄
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeGraphicDataDelete(  ZKN_RANGE_DRAW* p_draw )
{
	int i;
	
	memset( p_draw->range_grid_data, 0, sizeof(u8) * ZKN_RANGE_GRID_ARRAY_SIZE );
	memset( p_draw->range_grid_spdata, 0, sizeof(u8) * ZKN_RANGE_GRID_ARRAY_SIZE );

	// OAM非表示
	for( i=0; i<p_draw->now_use; i++ ){
		CLACT_SetDrawFlag( p_draw->danzyon_icon[i], FALSE );
	}
	p_draw->now_use = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	フィールド隠しマップゾーンIDテーブル作成
 *
 *	@param	heap	ヒープ
 *	@param	cp_glb	グローバルデータ
 *	@param	p_tbl_num テーブル数格納先
 *
 *	@return	テーブル　破棄の必要あり
 */
//-----------------------------------------------------------------------------
static u8* ZknRangeGraphicDataFldHideMapTblGet( u32 heap, const ZKN_RANGE_GLB* cp_glb, u32* p_tbl_num )
{
	u32 tbl_num;
	int i;
	u8* p_tbl;

	tbl_num = 0;
	
	// テーブル作成のため数を数える必要がある
	if( cp_glb->p_glb->hidemap_id_D15 == FALSE ){
		i = 0;
		while( ZKN_FLD_ZONE_ID_D15_IDTBL[ i ] != 0xffff ){
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_D18 == FALSE ){
		i = 0;
		while( ZKN_FLD_ZONE_ID_D18_IDTBL[ i ] != 0xffff ){
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_D30 == FALSE ){
		i = 0;
		while( ZKN_FLD_ZONE_ID_D30_IDTBL[ i ] != 0xffff ){
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_L04 == FALSE ){
		i = 0;
		while( ZKN_FLD_ZONE_ID_L04_IDTBL[ i ] != 0xffff ){
			tbl_num++;
			i++;
		}
	}
	if( tbl_num > 0 ){
		p_tbl = sys_AllocMemory( heap, sizeof(u8) * tbl_num );
	}else{
		p_tbl = NULL;
	}
	*p_tbl_num = tbl_num;


	// テーブル設定
	if( cp_glb->p_glb->hidemap_id_D15 == FALSE ){
		i = 0;
		while( ZKN_FLD_ZONE_ID_D15_IDTBL[ i ] != 0xffff ){
			p_tbl[ i ] = ZKN_FLD_ZONE_ID_D15_IDTBL[ i ];
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_D18 == FALSE ){
		i = 0;
		while( ZKN_FLD_ZONE_ID_D18_IDTBL[ i ] != 0xffff ){
			p_tbl[ i ] = ZKN_FLD_ZONE_ID_D18_IDTBL[ i ];
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_D30 == FALSE ){
		i = 0;
		while( ZKN_FLD_ZONE_ID_D30_IDTBL[ i ] != 0xffff ){
			p_tbl[ i ] = ZKN_FLD_ZONE_ID_D30_IDTBL[ i ];
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_L04 == FALSE ){
		i = 0;
		while( ZKN_FLD_ZONE_ID_L04_IDTBL[ i ] != 0xffff ){
			p_tbl[ i ] = ZKN_FLD_ZONE_ID_L04_IDTBL[ i ];
			tbl_num++;
			i++;
		}
	}

	return p_tbl;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ダンジョン隠しマップゾーンIDテーブル作成
 *
 *	@param	heap	ヒープ
 *	@param	cp_glb	グローバルデータ
 *	@param	p_tbl_num テーブル数格納先
 *
 *	@return	テーブル　破棄の必要あり
 */
//-----------------------------------------------------------------------------
static u8* ZknRangeGraphicDataDanHideMapTblGet( u32 heap, const ZKN_RANGE_GLB* cp_glb, u32* p_tbl_num )
{
	u32 tbl_num;
	int i;
	u8* p_tbl;

	tbl_num = 0;
	
	// テーブル作成のため数を数える必要がある
	if( cp_glb->p_glb->hidemap_id_D15 == FALSE ){
		i = 0;
		while( ZKN_DAN_ZONE_ID_D15_IDTBL[ i ] != 0xffff ){
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_D18 == FALSE ){
		i = 0;
		while( ZKN_DAN_ZONE_ID_D18_IDTBL[ i ] != 0xffff ){
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_D30 == FALSE ){
		i = 0;
		while( ZKN_DAN_ZONE_ID_D30_IDTBL[ i ] != 0xffff ){
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_L04 == FALSE ){
		i = 0;
		while( ZKN_DAN_ZONE_ID_L04_IDTBL[ i ] != 0xffff ){
			tbl_num++;
			i++;
		}
	}

	if( tbl_num > 0 ){
		p_tbl = sys_AllocMemory( heap, sizeof(u8) * tbl_num );
		
	}else{
		p_tbl = NULL;
	}

	*p_tbl_num = tbl_num;


	//　テーブルを設定する
	tbl_num = 0;
	if( cp_glb->p_glb->hidemap_id_D15 == FALSE ){
		i=0;
		while( ZKN_DAN_ZONE_ID_D15_IDTBL[ i ] != 0xffff ){
			p_tbl[ tbl_num ] = ZKN_DAN_ZONE_ID_D15_IDTBL[ i ];
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_D18 == FALSE ){
		i = 0;
		while( ZKN_DAN_ZONE_ID_D18_IDTBL[ i ] != 0xffff ){
			p_tbl[ tbl_num ] = ZKN_DAN_ZONE_ID_D18_IDTBL[ i ];
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_D30 == FALSE ){
		i = 0;
		while( ZKN_DAN_ZONE_ID_D30_IDTBL[ i ] != 0xffff ){
			p_tbl[ tbl_num ] = ZKN_DAN_ZONE_ID_D30_IDTBL[ i ];
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_L04 == FALSE ){
		i = 0;
		while( ZKN_DAN_ZONE_ID_L04_IDTBL[ i ] != 0xffff ){
			p_tbl[ tbl_num ] = ZKN_DAN_ZONE_ID_L04_IDTBL[ i ];
			tbl_num++;
			i++;
		}
	}

	return p_tbl;
}

//----------------------------------------------------------------------------
/**
 *	@brief	グリッドデータ描画メイン処理
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeGraphicDrawMain( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb )
{
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );

	// 特殊
	ZKN_ENCOUNTDRAW_PrintChar(
			&p_drawglb->p_drawglb->bmp_mfont,
			p_draw->p_rangesp_char->pRawData,
			p_draw->p_rangesp_char->W * 8, p_draw->p_rangesp_char->H * 8,
			ZKN_RANGE_GRAPHIC_GRID_SIZE,
			p_draw->range_grid_spdata,
			ZKN_RANGE_GRID_NUM_X, ZKN_RANGE_GRID_NUM_Y,
			ZKN_RANGE_BMP_DRAW_X, ZKN_RANGE_BMP_DRAW_Y );

	
	// 通常
	ZKN_ENCOUNTDRAW_PrintChar(
			&p_drawglb->p_drawglb->bmp_mfont,
			p_draw->p_range_char->pRawData,
			p_draw->p_range_char->W * 8, p_draw->p_range_char->H * 8,
			ZKN_RANGE_GRAPHIC_GRID_SIZE,
			p_draw->range_grid_data,
			ZKN_RANGE_GRID_NUM_X, ZKN_RANGE_GRID_NUM_Y,
			ZKN_RANGE_BMP_DRAW_X, ZKN_RANGE_BMP_DRAW_Y );

	// 表示ON
	GF_BGL_BmpWinOn( &p_drawglb->p_drawglb->bmp_mfont );
}


//----------------------------------------------------------------------------
/**
 *	@brief	生息地ふめい描画ONOFF
 *
 *	@param	p_draw	描画ワーク
 *	@param	p_work	ワーク
 * 
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeRangeNoneDrawSet( ZKN_RANGE_DRAW* p_draw, const ZKN_RANGE_WORK* p_work )
{
	// ダンジョンもフィールドも分布データが無いとき非標示 その他表示
	if( (p_draw->dan_range_num <= 0) &&
		(p_draw->fld_range_num <= 0) &&
		(p_draw->dansp_range_num <= 0) &&
		(p_draw->fldsp_range_num <= 0) ){
		
		CLACT_SetDrawFlag( p_draw->range_none, TRUE );
		FONTOAM_SetDrawFlag( p_draw->range_none_font->p_fontoam, TRUE );
	}else{

		CLACT_SetDrawFlag( p_draw->range_none, FALSE );
		FONTOAM_SetDrawFlag( p_draw->range_none_font->p_fontoam, FALSE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	分布タイプ表示切替
 *
 *	@param	p_draw	描画ワーク
 *	@param	type	分布タイプ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeRangeTypeOn( ZKN_RANGE_DRAW* p_draw, int type )
{
	int i;

	for( i=0; i<ZKN_RANGE_TYPE_NUM; i++ ){
		if( i == type ){
			FONTOAM_SetDrawFlag( p_draw->range_mode_font[ i ]->p_fontoam, TRUE );
		}else{
			FONTOAM_SetDrawFlag( p_draw->range_mode_font[ i ]->p_fontoam, FALSE );
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	分布描画データ更新
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	cp_glb			データグローバル
 *	@param	cp_datawork		データワーク
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeGraphicChange( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, const ZKN_RANGE_WORK* cp_datawork, int heap )
{
	// タイプが変更されたら文字や,グラフィックデータ変更
	if( p_draw->type != cp_datawork->type ){
		
		// 分布描画データ作成
		ZknRangeGraphicDataMake( p_draw, cp_glb, cp_datawork, heap );

		// 分布データ描画
		ZknRangeGraphicDrawMain( p_draw, p_drawglb );

		// 分布タイプ表示	
		ZknRangeRangeTypeOn( p_draw, cp_glb->type );

		// 生息地不明表示
		ZknRangeRangeNoneDrawSet( p_draw, cp_datawork );

		// 分布更新
		p_draw->type = cp_datawork->type;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン分布データ読み込み
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバルデータ
 *	@param	heap	ヒープ
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeMonsRangeDataLoad( ZKN_RANGE_WORK* p_work, ZKN_RANGE_GLB* p_glb, int heap )
{
	int dan_type;
	int fld_type;
	int mons_no = ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb );
	
	switch( p_glb->type ){
	case ZKN_RANGE_TYPE_MORNING:// 朝
		dan_type = ZKN_RANGEDATA_TYPE_DAN_MORNING;
		fld_type = ZKN_RANGEDATA_TYPE_FLD_MORNING;
		break;
		
	case ZKN_RANGE_TYPE_NOON:	// 昼
		dan_type = ZKN_RANGEDATA_TYPE_DAN_NOON;
		fld_type = ZKN_RANGEDATA_TYPE_FLD_NOON;
		break;
		
	case ZKN_RANGE_TYPE_NIGHT:	// 夜
		dan_type = ZKN_RANGEDATA_TYPE_DAN_NIGHT;
		fld_type = ZKN_RANGEDATA_TYPE_FLD_NIGHT;
		break;

	default:
		// おかしい
		GF_ASSERT( 0 );
		break;
	}

	// 通常ダンジョン
	ZKN_RANGEDATA_GetMonsNoRange( &p_work->dan_range, mons_no, dan_type, heap );

	// 通常フィールド
	ZKN_RANGEDATA_GetMonsNoRange( &p_work->fld_range, mons_no, fld_type, heap );
	
	// 図鑑保持と保持後で　特殊データは変更する
	if( ZKN_GLBDATA_SaveData_ZenkokuZukanGet( p_glb->p_glb ) == FALSE ){
		
		// 図鑑保持前
		// 特殊ダンジョン
		ZKN_RANGEDATA_GetMonsNoRange( &p_work->dansp_range, mons_no, ZKN_RANGEDATA_TYPE_DAN_SPECIAL, heap );
		// 特殊フィールド
		ZKN_RANGEDATA_GetMonsNoRange( &p_work->fldsp_range, mons_no, ZKN_RANGEDATA_TYPE_FLD_SPECIAL, heap );
	}else{
		
		// 図鑑保持後
		// 特殊ダンジョン
		ZKN_RANGEDATA_GetMonsNoRange( &p_work->dansp_range, mons_no, ZKN_RANGEDATA_TYPE_DAN_SPECIAL_COMP, heap );
		// 特殊フィールド
		ZKN_RANGEDATA_GetMonsNoRange( &p_work->fldsp_range, mons_no, ZKN_RANGEDATA_TYPE_FLD_SPECIAL_COMP, heap );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン分布データ破棄
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeMonsRangeDataDelete( ZKN_RANGE_WORK* p_work )
{
	// 通常ダンジョン
	ZKN_RANGEDATA_DeleteMonsNoRange( &p_work->dan_range );

	// 通常フィールド
	ZKN_RANGEDATA_DeleteMonsNoRange( &p_work->fld_range );
	
	// 特殊ダンジョン
	ZKN_RANGEDATA_DeleteMonsNoRange( &p_work->dansp_range );
	
	// 特殊フィールド
	ZKN_RANGEDATA_DeleteMonsNoRange( &p_work->fldsp_range );
}


//----------------------------------------------------------------------------
/**
 *	@brief	分布図グラフィックを交互に表示する初期化
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeGraphicDrawMoveInit( ZKN_RANGE_DRAW* p_draw )
{
	int i;
	p_draw->drawmove_count = 0;
	p_draw->drawmove_flag = 0;

	// BG1OAMは非標示
	GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG1, VISIBLE_OFF );
	for( i=0; i<p_draw->now_use; i++ ){
		CLACT_SetDrawFlag( p_draw->danzyon_icon[i], FALSE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	開始
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeGraphicDrawMoveStart( ZKN_RANGE_DRAW* p_draw )
{
	int i;

	G2_SetBlendAlpha( GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3, GX_BLEND_PLANEMASK_BG3, 0, 16 );

	// BGを表示し、OAMは非標示
	GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG1, VISIBLE_ON );
	for( i=0; i<p_draw->now_use; i++ ){
		CLACT_SetDrawFlag( p_draw->danzyon_icon[i], FALSE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	分布図グラフィックを交互に表示する
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeGraphicDrawMoveMain( ZKN_RANGE_DRAW* p_draw )
{
	fx32 alpha;
	int count;
	int i;


	// 表示処理		完全に消えてから表示されるように
	// 非表示処理ー＞VBLANK－＞表示処理というふうにしています
	if( p_draw->drawmove_count >= ZKN_RANGE_DRAW_MOVE_COUNT_MAX ){
		p_draw->drawmove_count = 0;	// カウント初期化
		// 0のときBG
		if( p_draw->drawmove_flag == 0 ){

			// OAM表示設定
			for( i=0; i<p_draw->now_use; i++ ){
				CLACT_SetDrawFlag( p_draw->danzyon_icon[ i ], TRUE );
			}
			p_draw->drawmove_flag = 1;
		}else{
			// BG表示設定
			GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG1, VISIBLE_ON );
			p_draw->drawmove_flag = 0;
		}
	}
	
	// α値設定
	if( p_draw->drawmove_count < ZKN_RANGE_DRAW_MOVE_COUNT_HALF ){
		count = p_draw->drawmove_count;
	}else{
		count = ZKN_RANGE_DRAW_MOVE_COUNT_MAX - p_draw->drawmove_count;
	}
	alpha = FX_Mul( (16 << FX32_SHIFT), (count << FX32_SHIFT) );
	alpha = FX_Div( alpha, (ZKN_RANGE_DRAW_MOVE_COUNT_HALF << FX32_SHIFT) );
	G2_ChangeBlendAlpha( alpha >> FX32_SHIFT, 16 );
	
	// カウント処理
	p_draw->drawmove_count++;


	// 非表示処理
	if( p_draw->drawmove_count >= ZKN_RANGE_DRAW_MOVE_COUNT_MAX ){
		// 0のときBG
		if( p_draw->drawmove_flag == 0 ){

			GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG1, VISIBLE_OFF );
		}else{
			// OAM非表示設定
			for( i=0; i<p_draw->now_use; i++ ){
				CLACT_SetDrawFlag( p_draw->danzyon_icon[ i ], FALSE );
			}
		}
	}
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
static void ZknRangePokeGraOn( ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );

	// ポケモン設定
	ZKN_UTIL_PokemonGraphicSet( p_drawglb->p_drawglb, cp_glb->p_glb,
			monsno,
			PARA_FRONT, ZKN_RANGE_POKEGRA_DRAW_X, ZKN_RANGE_POKEGRA_DRAW_Y );
	
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
static void ZknRangePokeGraOff( ZKN_RANGE_DRAWGLB* p_drawglb )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );

	// 表示OFF
	SoftSpriteParaSet( p_pokegra, SS_PARA_VANISH, TRUE );

	// ソフトパレットフェードがかかっている可能性があるのでOFF
	SoftSpritePalFadeOff( p_pokegra );
}
