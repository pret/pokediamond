//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan_sub.c
 *	@brief		図鑑サブ画面
 *	@author		tomoya takahashi 
 *	@data		2006.01.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

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
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"

#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_zukan_common.h"
#include "include/application/zukanlist/zkn_zukan.h"
#include "include/application/zukanlist/zkn_zukan_graver.h"
#include "include/application/zukanlist/zkn_zukan_textver.h"
#include "include/application/zukanlist/zkn_world_text_sys.h"
#include "include/application/zukanlist/zkn_world_text_data.h"

#define	__ZKN_ZUKAN_SUB_H_GLOBAL
#include "include/application/zukanlist/zkn_zukan_sub.h"

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
#define ZKN_ZUKAN_SUB_EVENT_NUM ( 3 )	// イベント数
#define ZKN_ZUKAN_SUB_EVENT_CHANGE_NORMAL		(1<<0)
#define ZKN_ZUKAN_SUB_EVENT_CHANGE_TEXT			(1<<1)
#define ZKN_ZUKAN_SUB_EVENT_CHANGE_DATA_MAIN	(1<<2)


#define ZKN_ZUKAN_SUB_OAM_SF_PRI	( 31 )
#define ZKN_ZUKAN_SUB_OAM_BG_PRI	( 2 )

enum{
	ZKN_ZUKANSUB_SEQINIT_ALLOC,
	ZKN_ZUKANSUB_SEQINIT_LOAD,
	ZKN_ZUKANSUB_SEQINIT_FADEIN,
	ZKN_ZUKANSUB_SEQINIT_END,
};
enum{
	ZKN_ZUKANSUB_SEQDELETE_FADEOUT_INIT,
	ZKN_ZUKANSUB_SEQDELETE_FADEOUT,
	ZKN_ZUKANSUB_SEQDELETE_RELEASE,
	ZKN_ZUKANSUB_SEQDELETE_FREE,
	ZKN_ZUKANSUB_SEQDELETE_END,
};

// サブ画面で変更するアプリケーションタイプ
enum{
	ZKN_ZUKANSUB_CONTROL_NORMAL,	// ノーマルタイプ図鑑を今表示中
	ZKN_ZUKANSUB_CONTROL_TEXT00,		// テキストバージョン
	ZKN_ZUKANSUB_CONTROL_TEXT01,		// テキストバージョン
	ZKN_ZUKANSUB_CONTROL_TEXT02,		// テキストバージョン
	ZKN_ZUKANSUB_CONTROL_TEXT03,		// テキストバージョン
	ZKN_ZUKANSUB_CONTROL_TEXT04,		// テキストバージョン
};

// ボタン
enum{
	ZKN_ZUKANSUB_BUTTON_NEXT,
	ZKN_ZUKANSUB_BUTTON_BACK,
	ZKN_ZUKANSUB_BUTTON_MY_COUNTRY,		// 自国ボタン
	ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_00,	// 外国00ボタン
	ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_01,	// 外国01ボタン
	ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_02,	// 外国02ボタン
	ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_03,	// 外国03ボタン
	ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_04,	// 外国04ボタン
	ZKN_ZUKANSUB_BUTTON_NUM,
};
#define ZKN_ZUKANSUB_BUTTON_SIZE_X	( 160 )
#define ZKN_ZUKANSUB_BUTTON_SIZE_Y	( 40 )
#define ZKN_ZUKANSUB_BUTTON_DEF_X	( 128 )
#define ZKN_ZUKANSUB_BUTTON_NEXT_Y	( 132 )
#define ZKN_ZUKANSUB_BUTTON_BACK_Y		( 76 )
#define ZKN_ZUKANSUB_BUTTON_FONT_OFS_Y	( -6 )
#define ZKN_ZUKANSUB_BUTTON_FONT_NEXT_OFS_X	( -32 )
#define ZKN_ZUKANSUB_BUTTON_FONT_BACK_OFS_X	( -16 )
#define ZKN_ZUKANSUB_BUTTON_ANM_SEQ		( 0 )
#define ZKN_ZUKANSUB_BUTTONFONT_BMP_SIZE_CX	( 8 )
#define ZKN_ZUKANSUB_BUTTONFONT_BMP_SIZE_CY	( 4 )
#define ZKN_ZUKANSUB_BUTTON_NEXTBG_PLTT_NO	(4)
#define ZKN_ZUKANSUB_BUTTON_BACKBG_PLTT_NO	(5)

#define ZKN_ZUKANSUB_BUTTON_MY_C_X	( 28 )
#define ZKN_ZUKANSUB_BUTTON_O_C00_X	( 68 )
#define ZKN_ZUKANSUB_BUTTON_O_C01_X	( 108 )
#define ZKN_ZUKANSUB_BUTTON_O_C02_X	( 148 )
#define ZKN_ZUKANSUB_BUTTON_O_C03_X	( 188 )
#define ZKN_ZUKANSUB_BUTTON_O_C04_X	( 228 )
#define ZKN_ZUKANSUB_BUTTON_DEF_Y	( 176 )
#define ZKN_ZUKANSUB_BUTTON_C_SIZE_X	( 40 )
#define ZKN_ZUKANSUB_BUTTON_C_SIZE_Y	( 32 )
enum{
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_JPN_OFF,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_JPN_ON,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_E_OFF,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_E_ON,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_FRA_OFF,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_FRA_ON,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_GER_OFF,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_GER_ON,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_ITA_OFF,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_ITA_ON,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_SPA_OFF,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_SPA_ON,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_BACK_ICON,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_NEXT_ICON,
};


#define ZKN_ZUKANSUB_BUTTON_PAL_OFS		( 4 )
#define ZKN_ZUKANSUB_BUTTON_PAL_OFS_ON		( 1 )

#define ZKN_ZUKANSUB_BUTTON_BG_DEF_X	( (ZKN_ZUKANSUB_BUTTON_DEF_X - (ZKN_ZUKANSUB_BUTTON_SIZE_X / 2)) / 8 )
#define ZKN_ZUKANSUB_BUTTON_BG_GRA_Y	( ((ZKN_ZUKANSUB_BUTTON_NEXT_Y - (ZKN_ZUKANSUB_BUTTON_SIZE_Y / 2)) / 8) )
#define ZKN_ZUKANSUB_BUTTON_BG_TEXT_Y	( ((ZKN_ZUKANSUB_BUTTON_BACK_Y - (ZKN_ZUKANSUB_BUTTON_SIZE_Y / 2)) / 8) )

// ボタンアイコン
#define ZKN_ZUKANSUB_BUTTON_ICON_NEXT_OFS_X	( +32 )
#define ZKN_ZUKANSUB_BUTTON_ICON_BACK_OFS_X	( -32 )
#define ZKN_ZUKANSUB_BUTTON_ICON_NEXT_Y		( ZKN_ZUKANSUB_BUTTON_NEXT_Y + 2 )
#define ZKN_ZUKANSUB_BUTTON_ICON_BACK_Y		( ZKN_ZUKANSUB_BUTTON_BACK_Y + 2 )


//-------------------------------------
//	どの国の言語を出せるかのマスク	
//=====================================
enum{
	ZKN_ZUKANSUB_COUNTRY_HOME = 1 << 0,
	ZKN_ZUKANSUB_COUNTRY_OUT00 = 1 << 1,
	ZKN_ZUKANSUB_COUNTRY_OUT01 = 1 << 2,
	ZKN_ZUKANSUB_COUNTRY_OUT02 = 1 << 3,
	ZKN_ZUKANSUB_COUNTRY_OUT03 = 1 << 4,
	ZKN_ZUKANSUB_COUNTRY_OUT04 = 1 << 5,
	ZKN_ZUKANSUB_COUNTRY_ALL = ZKN_ZUKANSUB_COUNTRY_HOME| ZKN_ZUKANSUB_COUNTRY_OUT00 | ZKN_ZUKANSUB_COUNTRY_OUT01 | ZKN_ZUKANSUB_COUNTRY_OUT02 | ZKN_ZUKANSUB_COUNTRY_OUT03 | ZKN_ZUKANSUB_COUNTRY_OUT04,
};
	


#define ZKN_ZUKANSUB_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	図鑑サブ画面　グローバル変数
//=====================================
typedef struct {
	int* p_event_key;		// イベントキー

	ZKN_GLB_DATA* p_glb;		// グローバルデータ
	ZKN_ZUKAN_GLB* p_zukan_glb;	// 図鑑グローバル
	ZKN_APL_DATA* p_zukan_graver_apl;	// 図鑑グラフィックバージョン
	ZKN_APL_DATA* p_zukan_textver_apl;	// 図鑑グラフィックバージョン

	// 図鑑コモンサブアプリデータ
	const ZKN_APL_DATA* cp_zukan_common_apl;
} ZKN_ZUKAN_SUB_GLB;


//-------------------------------------
//	図鑑サブ画面　描画グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA* p_drawglb;
} ZKN_ZUKAN_SUB_DRAWGLB;

//-------------------------------------
//	ボタンコールバックへのワーク
//=====================================
typedef struct {
	void* p_glb;
	void* p_work;
} ZKN_ZUKAN_BUTTON_CALLBACK;


//-------------------------------------
//	図鑑サブ画面　内部ワーク
//=====================================
typedef struct {
	// ボタンマネージャ
	BUTTON_MAN* p_button_man;
	TP_HIT_TBL *hit_tbl;	// ボタンデータ
	ZKN_ZUKAN_BUTTON_CALLBACK callcack;

	// アプリデータ
	int now_apply;
	int button_event[ ZKN_ZUKANSUB_BUTTON_NUM ];	// ボタンイベントデータ

	int poke_tbl_move;		// NEXT:ZKN_ZUKANSUB_BUTTON_NEXT  BACK:ZKN_ZUKANSUB_BUTTON_BACK  NONE:ZKN_ZUKANSUB_BUTTON_NUM

	u32 poke_country_msk;	// どの国のテキストなら出せるか
} ZKN_ZUKAN_SUB_WORK;

//-------------------------------------
//	図鑑サブ画面　描画ワーク
//=====================================
typedef struct {
	// ボタングラフィック
	CLACT_WORK_PTR button[ ZKN_ZUKANSUB_BUTTON_NUM ];
	ZKN_FONTOAM_DATA* p_button_font[ ZKN_ZUKANSUB_BUTTON_NUM ];
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	// ボタンアイコン
	CLACT_WORK_PTR button_icon[ ZKN_ZUKANSUB_BUTTON_NUM ];

	// 外国語ボタングラフィック
	CLACT_U_RES_OBJ_PTR res_obj_world[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	int	bgpltt_no[ ZKN_ZUKANSUB_BUTTON_NUM ];

	void* pltt_buff[ ZKN_ZUKANSUB_BUTTON_NUM ];


	u32 local_poke_country_msk;	// どの国のテキストなら出せるか
} ZKN_ZUKAN_SUB_DRAW;

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
static ZKN_ZUKAN_SUB_GLB* MakeZukanSubGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_ZUKAN_SUB_DRAWGLB* MakeZukanSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeZukanSubEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteZukanSubGlb( ZKN_ZUKAN_SUB_GLB* p_glb );
static void DeleteZukanSubDrawGlb( ZKN_ZUKAN_SUB_DRAWGLB* p_glb );
static void DeleteZukanSubEvent( ZKN_EVENT_DATA* p_event );


static int ZukanSubEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
static int ZknZukanSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

// フェード処理
static void ZknZukanSubOamFadeInit( ZKN_ZUKAN_SUB_DRAW* p_draw );
static void ZknZukanSubOamFadeDelete( ZKN_ZUKAN_SUB_DRAW* p_draw );
static void ZknZukanSubFadeInit( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_SUB_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknZukanSubFadeMain( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_SUB_GLB* cp_glb, BOOL fadein_out );

// ボタン制御
static void ZknZukanSubButtonMake( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb, int heap );
static void ZknZukanSubButtonMove( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb );
static void ZknZukanSubButtonDelete( ZKN_ZUKAN_SUB_WORK* p_work );
static void ZknZukanSubButtonCallBack( u32 button_no, u32 event, void* p_work );

// ボタン描画制御
static void ZknZukanSubButtonControl( ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, CLACT_WORK_PTR button, ZKN_FONTOAM_DATA* p_fontoam, int event, int def_y, int bgpltt_no, int* p_nowbgpltt_no, int heap, int off_fontoam_pl, int on_fontoam_pl, void** buff );

static void ZknZukanSubFontButtonMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt );

// 外国語ボタン表示非表示設定
static void ZknZukanSubWorldTextButtonDrawSet( ZKN_ZUKAN_SUB_DRAW* p_draw, const ZKN_ZUKAN_SUB_WORK* cp_work );
// 外国語ボタンアニメ
static void ZknZUkanSubWorldTextButtonAnm( CLACT_WORK_PTR act, int button_event, int world );

// 外国語テキストマスク設定
static void ZknZukanSubWorldTextMskSet( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb );


// 読み込み処理
static void ZknZukanSubLoadResource( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanSubReleaseResource( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanSubSetUpBg( ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanSubLoadOamData( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanSubReleaseOamData( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb );
static void ZknZukanSubAddClact( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanSubDeleteClact( ZKN_ZUKAN_SUB_DRAW* p_draw );
static void ZknZukanSubAddFontOam( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanSubDeleteFontOam( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb );

// アプリケーション変更
static void ZknZukanSubChangMons( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb, int now_apply );
static void ZknZukanSubApplyChange( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb, int now_apply, int next_apply );


// ポケモン切り替え処理
static void ZknZukanSubPokeTblMove(  ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb );
static void ZKnZukanSubKeyMove( ZKN_ZUKAN_SUB_WORK* p_work );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑サブ画面　アプリ作成
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
void ZKN_ZukanSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_ZUKAN_SUB_GLB*	p_glb;
	ZKN_ZUKAN_SUB_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeZukanSubGlb( heap, zkn_sys );
	p_drawglb = MakeZukanSubDrawGlb( heap, zkn_sys );
	p_event = MakeZukanSubEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= ZukanSubEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanSubProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanSubProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanSubProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanSubProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanSubProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanSubProcDrawFuncDelete;
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
void ZKN_ZukanSubAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteZukanSubGlb( p_data->p_glb_data ); 
	DeleteZukanSubDrawGlb( p_data->p_glb_data ); 
	DeleteZukanSubEvent( p_data->p_event_data );
}



//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑サブ画面　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKAN_SUB_GLB* MakeZukanSubGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKAN_SUB_GLB* p_glb;
	ZKN_APL_DATA* p_apl;
	ZKN_GLB_DATA* p_glbdata;
	int i;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKAN_SUB_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKAN_SUB_GLB) );

	// 変数初期化
	// イベントキー
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrSub( zkn_sys );		

	// グローバルデータ
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	// 図鑑コモンアプリグローバルデータ
	p_apl = ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_COMMON );
	p_glb->cp_zukan_common_apl = p_apl;

	// 図鑑グローバル変数
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN );
	p_glb->p_zukan_glb = p_apl->p_glb_data;

	// 図鑑グラフィックバージョン変数
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_GRA );
	p_glb->p_zukan_graver_apl = p_apl;

	// 図鑑言語グラフィックバージョン変数
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_TEXT );
	p_glb->p_zukan_textver_apl = p_apl;
	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ画面描画グローバル作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	サブ画面描画グローバル
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKAN_SUB_DRAWGLB* MakeZukanSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKAN_SUB_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKAN_SUB_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKAN_SUB_DRAWGLB) );


	// 描画データ
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑サブ画面　イベント作成
 *
 *	@param	heap		使用するヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	イベントデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeZukanSubEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = ZukanSubEventDataNumGet();

	// イベントデータテーブル作成
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_MakeChangeZukanOnly( heap, &p_event_tbl[0], zkn_sys, ZKN_ZUKAN_SUB_EVENT_CHANGE_NORMAL );
	ZKN_EVENT_MakeChangeZukanTextMainOnly( heap, &p_event_tbl[1], zkn_sys, ZKN_ZUKAN_SUB_EVENT_CHANGE_TEXT );
	ZKN_EVENT_MakeChangeZukanNormalMainOnly( heap, &p_event_tbl[2], zkn_sys, ZKN_ZUKAN_SUB_EVENT_CHANGE_DATA_MAIN );

	return p_event_tbl;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑サブ画面　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanSubGlb( ZKN_ZUKAN_SUB_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ画面描画グローバル破棄
 *
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void DeleteZukanSubDrawGlb( ZKN_ZUKAN_SUB_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑サブ画面　イベントデータ破棄
 *
 *	@param	p_event	イベントデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanSubEvent( ZKN_EVENT_DATA* p_event )
{
	GF_ASSERT( p_event );
	
	ZKN_EVENT_DeleteData( &p_event[0] );
	ZKN_EVENT_DeleteData( &p_event[1] );
	ZKN_EVENT_DeleteData( &p_event[2] );

	sys_FreeMemoryEz( p_event );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑サブ画面アプリ　イベント数取得
 *	
 *	@param	none	
 *
 *	@return	図鑑サブ画面アプリ　イベント数
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZukanSubEventDataNumGet( void )
{
	return ZKN_ZUKAN_SUB_EVENT_NUM;
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
static int ZknZukanSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_SUB_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_SUB_WORK* p_work = p_dodata->p_work;
	int i;

	// ワークの作成
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_ZUKAN_SUB_WORK) );
	memset( p_work, 0, sizeof(ZKN_ZUKAN_SUB_WORK) );

	// ボタンイベントデータ
	for( i=0; i<ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
		p_work->button_event[ i ] = ZKN_UTIL_BUTTON_PUSH_NONE;	// ボタンイベントデータ
	}

	// 今のアプリケーション
	p_work->now_apply = ZKN_ZUKANSUB_CONTROL_NORMAL;

	// ボタンを作成
	ZknZukanSubButtonMake( p_work, p_glb, p_dodata->heap );

	// 外国語テキストを出せるかチェック
	ZknZukanSubWorldTextMskSet( p_work, p_glb );
	
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
static int ZknZukanSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_SUB_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_SUB_WORK* p_work = p_dodata->p_work;

	// 終了へ
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}


	// 動作チェック
	if( ZKN_ZukanCommonSubMoveFlagGet( p_glb->cp_zukan_common_apl ) ){

		// キー動作
		ZKnZukanSubKeyMove( p_work );
		
		// ボタン動作
		ZknZukanSubButtonMove( p_work, p_glb );

		// ポケモン切り替え
		ZknZukanSubPokeTblMove( p_work, p_glb );
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
static int ZknZukanSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_SUB_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_SUB_WORK* p_work = p_dodata->p_work;

	// ボタン破棄
	ZknZukanSubButtonDelete( p_work );

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
static int ZknZukanSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_ZUKAN_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_ZUKAN_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_ZUKANSUB_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_ZUKAN_SUB_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_ZUKAN_SUB_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANSUB_SEQINIT_LOAD:
		// Resource読み込み
		ZknZukanSubLoadResource( p_drawwork, p_drawglb, p_drawdata->heap );

		// 外国語ボタン表示非表示設定
		ZknZukanSubWorldTextButtonDrawSet( p_drawwork, cp_datawork );
		
		// フェード処理
		ZknZukanSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANSUB_SEQINIT_FADEIN:
		if( ZknZukanSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_ZUKANSUB_SEQINIT_END:
		
		// カーソルアニメ開始
		ZKN_UTIL_CursorSetAnimeStopFlag( &p_drawglb->p_drawglb->cursor, FALSE );
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
static int ZknZukanSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_ZUKAN_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_ZUKAN_SUB_DRAW*		p_drawwork = p_drawdata->p_work;
	int i;	// ループ用
	int bgpltt_no;
	BOOL move;


	// マスクが変更されたらボタンの表示を変更する
	if( p_drawwork->local_poke_country_msk != cp_datawork->poke_country_msk ){
		
		ZknZukanSubWorldTextButtonDrawSet( p_drawwork, cp_datawork );

		p_drawwork->local_poke_country_msk = cp_datawork->poke_country_msk;
	}

	// ボタン表示動作
	for( i=0; i<=ZKN_ZUKANSUB_BUTTON_BACK; i++ ){
		move = FALSE;
		
		if( i==0 ){	
			move = TRUE;
		}else{
			move = TRUE;
		}
		
		if( move ){
			if( i == ZKN_ZUKANSUB_BUTTON_NEXT ){
				bgpltt_no = ZKN_ZUKANSUB_BUTTON_NEXTBG_PLTT_NO;
			}else{
				bgpltt_no = ZKN_ZUKANSUB_BUTTON_BACKBG_PLTT_NO;
			}
			
			ZknZukanSubButtonControl( p_drawglb, p_drawwork->button[i],
					p_drawwork->p_button_font[i], cp_datawork->button_event[i],
					ZKN_ZUKANSUB_BUTTON_FONT_OFS_Y, bgpltt_no,
					&p_drawwork->bgpltt_no[i], p_drawdata->heap,
					ZKN_ZUKANSUB_BUTTON_PAL_OFS, 
					ZKN_ZUKANSUB_BUTTON_PAL_OFS_ON,
					&p_drawwork->pltt_buff[i] );

			// アイコンも同時に動かす
			ZKN_UTIL_ButtonMove( p_drawwork->button_icon[i],
			cp_datawork->button_event[i] );

		}
	}

	// 外国語用ボタン
	for( i=ZKN_ZUKANSUB_BUTTON_MY_COUNTRY; i<ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
		// ボタン動作
		ZknZUkanSubWorldTextButtonAnm( p_drawwork->button[i],
				cp_datawork->button_event[i],
				i );

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
static int ZknZukanSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_ZUKAN_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_ZUKAN_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_ZUKANSUB_SEQDELETE_FADEOUT_INIT:

		// カーソルアニメ停止
		ZKN_UTIL_CursorSetAnimeStopFlag( &p_drawglb->p_drawglb->cursor, TRUE );
		// フェード処理
		ZknZukanSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANSUB_SEQDELETE_FADEOUT:
		if( ZknZukanSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, FALSE ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_ZUKANSUB_SEQDELETE_RELEASE:
		// Resource読み込み
		ZknZukanSubReleaseResource( p_drawwork, p_drawglb, p_drawdata->heap );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANSUB_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
		
	case ZKN_ZUKANSUB_SEQDELETE_END:
		return ZKN_PROC_TRUE;
		
	default:
		break;
	}
	return ZKN_PROC_FALSE;
}




//----------------------------------------------------------------------------
/**
 *	@brief	ボタン作成関数
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバル
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubButtonMake( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb, int heap )
{
	// テーブル作成
	p_work->hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_ZUKANSUB_BUTTON_NUM );

	// テーブルデータ設定
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKANSUB_BUTTON_NEXT ],
			ZKN_ZUKANSUB_BUTTON_NEXT_Y - (ZKN_ZUKANSUB_BUTTON_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_NEXT_Y + (ZKN_ZUKANSUB_BUTTON_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_DEF_X - (ZKN_ZUKANSUB_BUTTON_SIZE_X/2),
			ZKN_ZUKANSUB_BUTTON_DEF_X + (ZKN_ZUKANSUB_BUTTON_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKANSUB_BUTTON_BACK ],
			ZKN_ZUKANSUB_BUTTON_BACK_Y - (ZKN_ZUKANSUB_BUTTON_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_BACK_Y + (ZKN_ZUKANSUB_BUTTON_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_DEF_X - (ZKN_ZUKANSUB_BUTTON_SIZE_X/2),
			ZKN_ZUKANSUB_BUTTON_DEF_X + (ZKN_ZUKANSUB_BUTTON_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKANSUB_BUTTON_MY_COUNTRY ],
			ZKN_ZUKANSUB_BUTTON_DEF_Y - (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_DEF_Y + (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_MY_C_X - (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2),
			ZKN_ZUKANSUB_BUTTON_MY_C_X + (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_00 ],
			ZKN_ZUKANSUB_BUTTON_DEF_Y - (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_DEF_Y + (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_O_C00_X - (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2),
			ZKN_ZUKANSUB_BUTTON_O_C00_X + (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_01 ],
			ZKN_ZUKANSUB_BUTTON_DEF_Y - (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_DEF_Y + (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_O_C01_X - (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2),
			ZKN_ZUKANSUB_BUTTON_O_C01_X + (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_02 ],
			ZKN_ZUKANSUB_BUTTON_DEF_Y - (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_DEF_Y + (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_O_C02_X - (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2),
			ZKN_ZUKANSUB_BUTTON_O_C02_X + (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_03 ],
			ZKN_ZUKANSUB_BUTTON_DEF_Y - (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_DEF_Y + (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_O_C03_X - (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2),
			ZKN_ZUKANSUB_BUTTON_O_C03_X + (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_04 ],
			ZKN_ZUKANSUB_BUTTON_DEF_Y - (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_DEF_Y + (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_O_C04_X - (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2),
			ZKN_ZUKANSUB_BUTTON_O_C04_X + (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2) );


	p_work->callcack.p_glb = p_glb;
	p_work->callcack.p_work = p_work;

	// ボタンマネージャ作成
	p_work->p_button_man = BMN_Create( 
			p_work->hit_tbl,
			ZKN_ZUKANSUB_BUTTON_NUM,
			ZknZukanSubButtonCallBack,
			&p_work->callcack,
			heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタン動作処理
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubButtonMove( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb )
{
	int i;
	
	// 放されたら全てのボタンが元の絵に戻る
	for( i = 0; i < ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
		p_work->button_event[ i ] = BMN_EVENT_SLIDEOUT;
	}

	BMN_Main( p_work->p_button_man );
	
	// 押されている外国語ボタンは、押しっぱなし
	switch( p_work->now_apply ){
	case ZKN_ZUKANSUB_CONTROL_NORMAL:	// ノーマルタイプ図鑑を今表示中
		p_work->button_event[ ZKN_ZUKANSUB_BUTTON_MY_COUNTRY ] = BMN_EVENT_RELEASE;
		break;
		
	case ZKN_ZUKANSUB_CONTROL_TEXT00:		// テキストバージョン
		p_work->button_event[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_00 ] = BMN_EVENT_RELEASE;
		break;
		
	case ZKN_ZUKANSUB_CONTROL_TEXT01:		// テキストバージョン
		p_work->button_event[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_01 ] = BMN_EVENT_RELEASE;
		break;
		
	case ZKN_ZUKANSUB_CONTROL_TEXT02:		// テキストバージョン
		p_work->button_event[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_02 ] = BMN_EVENT_RELEASE;
		break;
		
	case ZKN_ZUKANSUB_CONTROL_TEXT03:		// テキストバージョン
		p_work->button_event[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_03 ] = BMN_EVENT_RELEASE;
		break;
		
	case ZKN_ZUKANSUB_CONTROL_TEXT04:		// テキストバージョン
		p_work->button_event[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_04 ] = BMN_EVENT_RELEASE;
		break;

	default:
		break;
	}


	// ポケモン変更がかかったら対応する
	// ボタンを反応させる
	switch( p_work->poke_tbl_move ){
		
	case ZKN_ZUKANSUB_BUTTON_NEXT:
		p_work->button_event[ ZKN_ZUKANSUB_BUTTON_NEXT ] = BMN_EVENT_HOLD;
		break;

	case ZKN_ZUKANSUB_BUTTON_BACK:
		p_work->button_event[ ZKN_ZUKANSUB_BUTTON_BACK ] = BMN_EVENT_HOLD;
		break;
		
	default:
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
static void ZknZukanSubButtonDelete( ZKN_ZUKAN_SUB_WORK* p_work )
{
	BMN_Delete( p_work->p_button_man );

	// テーブルワーク破棄
	sys_FreeMemoryEz( p_work->hit_tbl );
	p_work->hit_tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンコールバック関数
 *
 *	@param	button_no	ボタンナンバー
 *	@param	event		ボタンイベントタイプ
 *	@param	p_work		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_ZUKAN_BUTTON_CALLBACK* p_work_data = p_work;
	ZKN_ZUKAN_SUB_GLB* p_glb = p_work_data->p_glb;
	ZKN_ZUKAN_SUB_WORK* p_subwork = p_work_data->p_work;
	BOOL check;

	// ボタンイベント格納
	p_subwork->button_event[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_HOLD:
		switch( button_no ){
		case ZKN_ZUKANSUB_BUTTON_NEXT:
			p_subwork->poke_tbl_move = ZKN_ZUKANSUB_BUTTON_NEXT;
			break;
			
		case ZKN_ZUKANSUB_BUTTON_BACK:
			p_subwork->poke_tbl_move = ZKN_ZUKANSUB_BUTTON_BACK;
			break;

		case ZKN_ZUKANSUB_BUTTON_MY_COUNTRY:		// 自国ボタン
			if( p_subwork->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_HOME ){
				// 外国語モードのときは、自国語モードにする
				if( p_subwork->now_apply == ZKN_ZUKANSUB_CONTROL_NORMAL ){
					// ページ送り
					check = ZKN_ZukanAplPageAdd( p_glb->p_zukan_glb, 1 );
				}else{
					// ページ初期化
					ZKN_ZukanAplPageSet( p_glb->p_zukan_glb, 0 );

					check = TRUE;	// フェードはする
				}

				// アプリケーション変更で今のアプリケーションをリセット
				if( check ){
					ZknZukanSubApplyChange( p_subwork, p_glb, p_subwork->now_apply, ZKN_ZUKANSUB_CONTROL_NORMAL );

					// 選択移動音
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
				}
			}
			break;
			
		case ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_00:	// 外国00ボタン
			if( p_subwork->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT00 ){

				if( p_subwork->now_apply == ZKN_ZUKANSUB_CONTROL_TEXT00 ){
					// ページ送り
					check = ZKN_ZukanTexverPageAdd( p_glb->p_zukan_textver_apl );
				}else{
					// ページ初期化
					ZKN_ZukanTexverPageSet( p_glb->p_zukan_textver_apl, 0 );
					check = TRUE;	// フェードはする
				}

				if( check ){
					ZknZukanSubApplyChange( p_subwork, p_glb, p_subwork->now_apply, ZKN_ZUKANSUB_CONTROL_TEXT00 );

					// 選択移動音
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );

				}
			}
			break;
			
		case ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_01:	// 外国01ボタン
			if( p_subwork->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT01 ){
				// 外国語モードのときは、自国語モードにする
				if( p_subwork->now_apply == ZKN_ZUKANSUB_CONTROL_TEXT01 ){
					// ページ送り
					check = ZKN_ZukanTexverPageAdd( p_glb->p_zukan_textver_apl );
				}else{
					// ページ初期化
					ZKN_ZukanTexverPageSet( p_glb->p_zukan_textver_apl, 0 );
					check = TRUE;	// フェードはする
				}

				if( check ){
					ZknZukanSubApplyChange( p_subwork, p_glb, p_subwork->now_apply, ZKN_ZUKANSUB_CONTROL_TEXT01 );

					// 選択移動音
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
				}
			}
			break;
			
		case ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_02:	// 外国02ボタン
			if( p_subwork->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT02 ){

				// 外国語モードのときは、自国語モードにする
				if( p_subwork->now_apply == ZKN_ZUKANSUB_CONTROL_TEXT02 ){
					// ページ送り
					check = ZKN_ZukanTexverPageAdd( p_glb->p_zukan_textver_apl );
				}else{
					// ページ初期化
					ZKN_ZukanTexverPageSet( p_glb->p_zukan_textver_apl, 0 );
					check = TRUE;	// フェードはする
				}
				// アプリケーション変更で今のアプリケーションをリセット
				if( check ){
					ZknZukanSubApplyChange( p_subwork, p_glb, p_subwork->now_apply, ZKN_ZUKANSUB_CONTROL_TEXT02 );

					// 選択移動音
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
				}
			}
			break;
			
		case ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_03:	// 外国03ボタン
			if( p_subwork->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT03 ){

				// 外国語モードのときは、自国語モードにする
				if( p_subwork->now_apply == ZKN_ZUKANSUB_CONTROL_TEXT03 ){
					// ページ送り
					check = ZKN_ZukanTexverPageAdd( p_glb->p_zukan_textver_apl );
				}else{
					// ページ初期化
					ZKN_ZukanTexverPageSet( p_glb->p_zukan_textver_apl, 0 );
					check = TRUE;	// フェードはする
				}
				// アプリケーション変更で今のアプリケーションをリセット
				if( check ){
					ZknZukanSubApplyChange( p_subwork, p_glb, p_subwork->now_apply, ZKN_ZUKANSUB_CONTROL_TEXT03 );

					// 選択移動音
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
				}
			}
			break;
			
		case ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_04:	// 外国04ボタン
			if( p_subwork->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT04 ){

				// 外国語モードのときは、自国語モードにする
				if( p_subwork->now_apply == ZKN_ZUKANSUB_CONTROL_TEXT04 ){
					// ページ送り
					check = ZKN_ZukanTexverPageAdd( p_glb->p_zukan_textver_apl );
				}else{
					// ページ初期化
					ZKN_ZukanTexverPageSet( p_glb->p_zukan_textver_apl, 0 );
					check = TRUE;	// フェードはする
				}

				// アプリケーション変更で今のアプリケーションをリセット
				if( check ){
					ZknZukanSubApplyChange( p_subwork, p_glb, p_subwork->now_apply, ZKN_ZUKANSUB_CONTROL_TEXT04 );

					// 選択移動音
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
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
 *	@brief	グラフィック初期化処理
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubLoadResource( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap )
{
	// 背景
	ZknZukanSubSetUpBg( p_drawglb, heap );

	// OAM
	ZknZukanSubLoadOamData( p_draw, p_drawglb, heap );

	// セルアクター登録
	ZknZukanSubAddClact( p_draw, p_drawglb, heap );

	// FONTOAM登録
	ZknZukanSubAddFontOam( p_draw, p_drawglb, heap );
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
static void ZknZukanSubReleaseResource( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap )
{
	int i;


	// パレットをリセット
	ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_4_NCLR, PALTYPE_SUB_BG, ZKN_ZUKANSUB_BUTTON_NEXTBG_PLTT_NO*32, 32, heap );
	ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_4_NCLR, PALTYPE_SUB_BG, ZKN_ZUKANSUB_BUTTON_BACKBG_PLTT_NO*32, 32, heap );
	
	// セルアクター破棄
	ZknZukanSubDeleteClact( p_draw );

	// FONTOAM破棄
	ZknZukanSubDeleteFontOam( p_draw, p_drawglb );

	// OAM
	ZknZukanSubReleaseOamData( p_draw, p_drawglb );

	// パレットバッファ破棄
	for( i=0;i<ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
		if( p_draw->pltt_buff[i] ){
			sys_FreeMemoryEz( p_draw->pltt_buff[i] );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG面セットアップ
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubSetUpBg( ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// キャラクタデータ転送
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_sub_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S, 0, 0, TRUE, heap );

	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_sub2_c_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_sub2_a_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// ボタン１	
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S,
			p_scrn->rawData, ZKN_ZUKANSUB_BUTTON_BG_DEF_X, ZKN_ZUKANSUB_BUTTON_BG_GRA_Y,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );


	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_sub2_d_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// ボタン2
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S,
			p_scrn->rawData, ZKN_ZUKANSUB_BUTTON_BG_DEF_X, ZKN_ZUKANSUB_BUTTON_BG_TEXT_Y,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );
	
	sys_FreeMemoryEz( buff );



	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMリソース読み込み
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubLoadOamData( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_draw_glb );
	
	// キャラクタデータ読み込み
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR + ZKN_ZUKAN_SUB_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// セルデータ読み込み
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER + ZKN_ZUKAN_SUB_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR + ZKN_ZUKAN_SUB_RES_ID,
			CLACT_U_CELLANM_RES, heap );


	// キャラクタデータ読み込み
	p_draw->res_obj_world[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub2_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_sub2_lzh_NCGR + ZKN_ZUKAN_SUB_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj_world[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj_world[ CLACT_U_CHAR_RES ] );

	// セルデータ読み込み
	p_draw->res_obj_world[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub2_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_sub2_lzh_NCER + ZKN_ZUKAN_SUB_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj_world[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_sub2_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_sub2_lzh_NANR + ZKN_ZUKAN_SUB_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMリソース破棄
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubReleaseOamData( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb )
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


	// 世界の言語ボタン
	CLACT_U_CharManagerDelete( p_draw->res_obj_world[ CLACT_U_CHAR_RES ] );

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_obj_world[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_obj_world[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->res_obj_world[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクター登録
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubAddClact( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i;
	
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR + ZKN_ZUKAN_SUB_RES_ID,
			NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS, 
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER + ZKN_ZUKAN_SUB_RES_ID,
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR + ZKN_ZUKAN_SUB_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_ZUKAN_SUB_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_ZUKAN_SUB_OAM_SF_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;
	
	// グラフィックタイプ変更ボタン
	add.mat.x = ZKN_ZUKANSUB_BUTTON_DEF_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_NEXT_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_ZUKANSUB_BUTTON_NEXT ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_ZUKANSUB_BUTTON_NEXT ], ZKN_ZUKANSUB_BUTTON_ANM_SEQ );	

	// テキストタイプ変更ボタン
	add.mat.x = ZKN_ZUKANSUB_BUTTON_DEF_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_BACK_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_ZUKANSUB_BUTTON_BACK ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_ZUKANSUB_BUTTON_BACK ], ZKN_ZUKANSUB_BUTTON_ANM_SEQ );	


	// 外国語ボタン用
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_sub2_lzh_NCGR + ZKN_ZUKAN_SUB_RES_ID,
			NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS, 
			NARC_zukan_zkn_data_oam_sub2_lzh_NCER + ZKN_ZUKAN_SUB_RES_ID,
			NARC_zukan_zkn_data_oam_sub2_lzh_NANR + ZKN_ZUKAN_SUB_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_ZUKAN_SUB_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActHeader = &clact_head;

	// 自国図鑑開くようアクター
	add.mat.x = ZKN_ZUKANSUB_BUTTON_MY_C_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_ZUKANSUB_BUTTON_MY_COUNTRY ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_ZUKANSUB_BUTTON_MY_COUNTRY ], ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_JPN_OFF );	

	// 外国語00鑑開くようアクター
	add.mat.x = ZKN_ZUKANSUB_BUTTON_O_C00_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_00 ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_00 ], ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_E_OFF );	

	// 外国語01鑑開くようアクター
	add.mat.x = ZKN_ZUKANSUB_BUTTON_O_C01_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_01 ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_01 ], ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_FRA_OFF );	

	// 外国語02鑑開くようアクター
	add.mat.x = ZKN_ZUKANSUB_BUTTON_O_C02_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_02 ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_02 ], ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_GER_OFF );	

	// 外国語03鑑開くようアクター
	add.mat.x = ZKN_ZUKANSUB_BUTTON_O_C03_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_03 ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_03 ], ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_ITA_OFF );	

	// 外国語04鑑開くようアクター
	add.mat.x = ZKN_ZUKANSUB_BUTTON_O_C04_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_04 ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_04 ], ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_SPA_OFF );	

	add.pri = ZKN_ZUKAN_SUB_OAM_SF_PRI - 1;
	
	// ボタンアイコン
	add.mat.x = (ZKN_ZUKANSUB_BUTTON_DEF_X + ZKN_ZUKANSUB_BUTTON_ICON_NEXT_OFS_X) << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_ICON_NEXT_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button_icon[ ZKN_ZUKANSUB_BUTTON_NEXT ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button_icon[ ZKN_ZUKANSUB_BUTTON_NEXT ], ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_NEXT_ICON );	

	// ボタンアイコン
	add.mat.x = (ZKN_ZUKANSUB_BUTTON_DEF_X + ZKN_ZUKANSUB_BUTTON_ICON_BACK_OFS_X) << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_ICON_BACK_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button_icon[ ZKN_ZUKANSUB_BUTTON_BACK ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button_icon[ ZKN_ZUKANSUB_BUTTON_BACK ], ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_BACK_ICON );
	
	// ボタンアイコンなし
	for( i=ZKN_ZUKANSUB_BUTTON_BACK + 1; i<ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
		p_draw->button_icon[ i ] = NULL;
	}
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
static void ZknZukanSubDeleteClact( ZKN_ZUKAN_SUB_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
		CLACT_Delete( p_draw->button[ i ] );
		if( p_draw->button_icon[ i ] ){
			CLACT_Delete( p_draw->button_icon[ i ] );
		}
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
static void ZknZukanSubAddFontOam( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap )
{
	GF_BGL_BMPWIN* win;	// 文字列書き込み先
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR res_obj;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;
	int pltt_ofs;	// パレットアドレス
	int i;

	// 先にCLACTを登録してある必要がある
	GF_ASSERT( p_draw->button[ ZKN_ZUKANSUB_BUTTON_NEXT ] );

	// パレットのリソースデータ取得
	// パレットプロクシ取得用
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_glb_draw->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS );

	// 初期化データの共通部分を作成
	// 共通データ代入
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( res_obj, NULL );
	fontoam_init.y			 = ZKN_ZUKANSUB_BUTTON_FONT_OFS_Y;
	fontoam_init.bg_pri		 = ZKN_ZUKAN_SUB_OAM_BG_PRI;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DSUB;
	fontoam_init.heap		 = heap;

	// パレット転送先アドレス取得
	pltt_ofs = GetPlttProxyOffset( fontoam_init.pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_ZUKANSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_ZUKANSUB_BUTTONFONT_BMP_SIZE_CY );

	// すがた
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_ZUKAN_BUTTON_00, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_draw->button[ ZKN_ZUKANSUB_BUTTON_NEXT ];
	fontoam_init.x		= ZKN_ZUKANSUB_BUTTON_FONT_NEXT_OFS_X;
	p_draw->p_button_font[ ZKN_ZUKANSUB_BUTTON_NEXT ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_button_font[ ZKN_ZUKANSUB_BUTTON_NEXT ]->p_fontoam, pltt_ofs + ZKN_ZUKANSUB_BUTTON_PAL_OFS );

	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( win );


	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_ZUKANSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_ZUKANSUB_BUTTONFONT_BMP_SIZE_CY );

	// せつめい
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_ZUKAN_BUTTON_01, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_draw->button[ ZKN_ZUKANSUB_BUTTON_BACK ];
	fontoam_init.x		= ZKN_ZUKANSUB_BUTTON_FONT_BACK_OFS_X;
	p_draw->p_button_font[ ZKN_ZUKANSUB_BUTTON_BACK ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_button_font[ ZKN_ZUKANSUB_BUTTON_BACK ]->p_fontoam, pltt_ofs + ZKN_ZUKANSUB_BUTTON_PAL_OFS );

	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( win );


	// 文字は出さない
	for( i=ZKN_ZUKANSUB_BUTTON_MY_COUNTRY; i< ZKN_ZUKANSUB_BUTTON_NUM; i++){
		p_draw->p_button_font[ i ] = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM破棄
 *	
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubDeleteFontOam( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb )
{
	int i;

	for( i=0; i<ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
		if(p_draw->p_button_font[ i ]){
			ZKN_FONTOAM_Delete( p_draw->p_button_font[ i ] );
		}
	}
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
static void ZknZukanSubOamFadeInit( ZKN_ZUKAN_SUB_DRAW* p_draw )
{
	int i;
	// OBJMODEを半透明にする
	for( i=0; i<ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
		CLACT_ObjModeSet( p_draw->button[ i ], GX_OAM_MODE_XLU );
		if(p_draw->p_button_font[ i ]){
			FONTOAM_ObjModeSet( p_draw->p_button_font[ i ]->p_fontoam, GX_OAM_MODE_XLU );
		}
		if(p_draw->button_icon[ i ]){
			CLACT_ObjModeSet( p_draw->button_icon[ i ], GX_OAM_MODE_XLU );
		}
	}
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
static void ZknZukanSubOamFadeDelete( ZKN_ZUKAN_SUB_DRAW* p_draw )
{
	int i;
	// OBJMODEをノーマルにする
	for( i=0; i<ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
		CLACT_ObjModeSet( p_draw->button[ i ], GX_OAM_MODE_NORMAL );
		if(p_draw->p_button_font[ i ]){
			FONTOAM_ObjModeSet( p_draw->p_button_font[ i ]->p_fontoam, GX_OAM_MODE_NORMAL );
		}
		if(p_draw->button_icon[ i ]){
			CLACT_ObjModeSet( p_draw->button_icon[ i ], GX_OAM_MODE_NORMAL );
		}
	}
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
static void ZknZukanSubFadeInit( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_SUB_GLB* cp_glb, BOOL fadein_out )
{
	// 半透明OAM設定
	ZknZukanSubOamFadeInit( p_draw );

	// ブライトネス処理を行ってよいか
	if( ZKN_ZukanCommonSubBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_ZUKANSUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_ZUKANSUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
		}
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
static BOOL ZknZukanSubFadeMain( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_SUB_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check;

	// ブライトネスしよう許可でてるかチェック
	if( ZKN_ZukanCommonSubBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		check = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade_sub );
	}else{
//		check = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade_sub );
		check = IsFinishedBrightnessChg( MASK_SUB_DISPLAY );
	}

	// 終わったら終了処理
	if( check ){
		if( fadein_out ){
			// 半透明OAM破棄
			ZknZukanSubOamFadeDelete( p_draw );
		}

		return TRUE;
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ボタン描画制御
 *
 *	@param	button		ボタンアクター
 *	@param	event		イベント
 *	@param	p_fontoam	フォントOAM
 *	@param	def_y		Y距離
 *	@param	bgpltt_no	BGパレットNO
 *	@param	heap		ヒープ
 *	@param	off_fontoam_pl	フォントOAMオフ時
 *	@param	on_fontoam_pl	フォントOAMオン時
 *	@param	パレットバッファ	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubButtonControl( ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, CLACT_WORK_PTR button, ZKN_FONTOAM_DATA* p_fontoam, int event, int def_y, int bgpltt_no, int* p_nowbgpltt_no, int heap, int off_fontoam_pl, int on_fontoam_pl, void** buff )
{
	int now_frm;
	NNSG2dPaletteData* p_plt;
	BOOL check;
	BOOL chenge = FALSE;
	int arc_data_idx;

	// ボタン動作
	ZKN_UTIL_ButtonMove( button,
			event );


	ZknZukanSubFontButtonMove( 
			button,
			p_fontoam,
			def_y,
			off_fontoam_pl,
			on_fontoam_pl );

	// 現在フレーム取得
	now_frm = CLACT_AnmFrameGet( button );


	// カラーパレット設定
	switch( now_frm ){
	case ZKN_UTIL_BUTTON_FRAME_NONE:
	case ZKN_UTIL_BUTTON_FRAME_PUSH1:
		if( *p_nowbgpltt_no != 0 ){
			// off_pltt
			chenge = TRUE;
			arc_data_idx = NARC_zukan_zkn_data_4_NCLR;
			*p_nowbgpltt_no = 0;
		}
		break;
	case ZKN_UTIL_BUTTON_FRAME_PUSH2:
		if( *p_nowbgpltt_no != 1 ){
			// on_pltt
			chenge = TRUE;
			arc_data_idx = NARC_zukan_zkn_data_5_NCLR;
			*p_nowbgpltt_no = 1;
		}
		break;

	case ZKN_UTIL_BUTTON_FRAME_SELECT:
		if( *p_nowbgpltt_no != 2 ){
			// on_pltt
			chenge = TRUE;
			arc_data_idx = NARC_zukan_zkn_data_3_NCLR;
			*p_nowbgpltt_no = 2;
		}
		break;
	}
	if( chenge ){
		// 今までのを破棄
		if( *buff ){
			sys_FreeMemoryEz( *buff );
		}
		*buff = ZKN_GLBDATA_PalDataGet( p_drawglb->p_drawglb, arc_data_idx, &p_plt, heap );
		// TransferManagerに登録
		check = AddVramTransferManager(
				NNS_GFD_DST_2D_BG_PLTT_SUB,
				bgpltt_no*32,
				p_plt->pRawData,
				32);
		// 転送タスク生成失敗
		GF_ASSERT( check );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ボタンフォント動作
 *
 *	@param	act				アクター
 *	@param	p_fontoam		フォントOAM
 *	@param	def_y			デフォルトY位置
 *	@param	off_pltt		ボタンOFF時のカラーパレット
 *	@param	on_pltt			ボタンON時のカラーパレット
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubFontButtonMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt )
{
	ZKN_UTIL_ButtonFontMove_Col( act, p_fontoam, def_y, off_pltt, on_pltt );
}

//----------------------------------------------------------------------------
/**
 *	@brief	モンスターを変更する
 *
 *	@param	p_work		ワーク
 *	@param	p_glb		グローバル
 *	@param	now_apply	今のアプリケーション
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubChangMons( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb, int now_apply )
{
	int gra_x, gra_y;
	
	// ポケモンの声を出す
	p_glb->p_zukan_glb->mons_snd_req = TRUE;
		
	// 次のアプリフェードモード設定
	*p_glb->p_event_key |= ZKN_ZUKAN_SUB_EVENT_CHANGE_DATA_MAIN;
	p_work->now_apply = ZKN_ZUKANSUB_CONTROL_NORMAL;
	gra_x = ZKN_ZUKAN_POKEGRA_MAT_X;
	gra_y = ZKN_ZUKAN_POKEGRA_MAT_Y;
	p_glb->p_zukan_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_OTHER;


	// 今のアプリフェード設定
	switch( now_apply ){
	case ZKN_ZUKANSUB_CONTROL_NORMAL:	// ノーマルタイプ図鑑を今表示中
		p_glb->p_zukan_glb->poke_gra_move_x = gra_x;
		p_glb->p_zukan_glb->poke_gra_move_y = gra_y;
		p_glb->p_zukan_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_NORMAL;
		break;
		
	case ZKN_ZUKANSUB_CONTROL_TEXT00:		// 外国語00
	case ZKN_ZUKANSUB_CONTROL_TEXT01:		// 外国語01
	case ZKN_ZUKANSUB_CONTROL_TEXT02:		// 外国語02
	case ZKN_ZUKANSUB_CONTROL_TEXT03:		// 外国語03
	case ZKN_ZUKANSUB_CONTROL_TEXT04:		// 外国語04
		ZKN_ZukanTextverPokeGraFadeOutSet( p_glb->p_zukan_textver_apl, gra_x, gra_y );
		ZKN_ZukanTextverFadeModeSet( p_glb->p_zukan_textver_apl, ZKK_ZUKANTEXTVER_FADE_MODE_NORMAL );
		break;

	default:
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	アプリケーション変更
 *	
 *	@param	p_work			ワーク
 *	@param	p_glb			グローバル
 *	@param	now_apply		今のアプリ
 *	@param	next_apply		次のアプリ
 *	@param	fade_mode		フェードモード	TRUE:ポケモン残したまま FALSE:全けしフェード
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubApplyChange( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb, int now_apply, int next_apply )
{
	int gra_x, gra_y;
	int lang_code;

	// ポケモンの声を鳴らす
	
	// 次のアプリフェードモード設定
	switch( next_apply ){
	case ZKN_ZUKANSUB_CONTROL_NORMAL:	// ノーマルタイプ図鑑を今表示中
		*p_glb->p_event_key |= ZKN_ZUKAN_SUB_EVENT_CHANGE_DATA_MAIN;
		p_work->now_apply = ZKN_ZUKANSUB_CONTROL_NORMAL;
		gra_x = ZKN_ZUKAN_POKEGRA_MAT_X;
		gra_y = ZKN_ZUKAN_POKEGRA_MAT_Y;
		p_glb->p_zukan_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_OTHER;
		break;
		
	case ZKN_ZUKANSUB_CONTROL_TEXT00:		// 外国語00
	case ZKN_ZUKANSUB_CONTROL_TEXT01:		// 外国語01
	case ZKN_ZUKANSUB_CONTROL_TEXT02:		// 外国語02
	case ZKN_ZUKANSUB_CONTROL_TEXT03:		// 外国語03
	case ZKN_ZUKANSUB_CONTROL_TEXT04:		// 外国語04
		*p_glb->p_event_key |= ZKN_ZUKAN_SUB_EVENT_CHANGE_TEXT;
		p_work->now_apply = next_apply;
		gra_x = ZKN_ZUKANTEXTVER_POKEGRA_MAT_X;
		gra_y = ZKN_ZUKANTEXTVER_POKEGRA_MAT_Y;

		ZKN_ZukanTextverFadeModeSet( p_glb->p_zukan_textver_apl, ZKK_ZUKANTEXTVER_FADE_MODE_OTHER );

		// 国コード設定
		lang_code = ZKN_WT_WORLD_TEXT_GMM_Idx_LANG_Code( next_apply - ZKN_ZUKANSUB_CONTROL_TEXT00 );
		ZKN_ZukanTexverTypeSet( p_glb->p_zukan_textver_apl, lang_code );

		break;

	default:
		break;
	}

	// 今のアプリフェード設定
	switch( now_apply ){
	case ZKN_ZUKANSUB_CONTROL_NORMAL:	// ノーマルタイプ図鑑を今表示中
		p_glb->p_zukan_glb->poke_gra_move_x = gra_x;
		p_glb->p_zukan_glb->poke_gra_move_y = gra_y;
		p_glb->p_zukan_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_OTHER;
		break;
		
	case ZKN_ZUKANSUB_CONTROL_TEXT00:		// 外国語00
	case ZKN_ZUKANSUB_CONTROL_TEXT01:		// 外国語01
	case ZKN_ZUKANSUB_CONTROL_TEXT02:		// 外国語02
	case ZKN_ZUKANSUB_CONTROL_TEXT03:		// 外国語03
	case ZKN_ZUKANSUB_CONTROL_TEXT04:		// 外国語04
		ZKN_ZukanTextverPokeGraFadeOutSet( p_glb->p_zukan_textver_apl, gra_x, gra_y );

		ZKN_ZukanTextverFadeModeSet( p_glb->p_zukan_textver_apl, ZKK_ZUKANTEXTVER_FADE_MODE_OTHER );
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン切り替え処理
 *
 *	@param	p_work		ワーク
 *	@param	p_glb		グローバル
 *	@param	up_down		上に行くか下に行くか
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubPokeTblMove( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb )
{
	BOOL check;

	if( p_work->poke_tbl_move != ZKN_ZUKANSUB_BUTTON_NUM ){
		
		// 図鑑データ画面で上下が押されたらポケモンを入れ替える
		if( p_work->poke_tbl_move == ZKN_ZUKANSUB_BUTTON_BACK ){
			// ポケモンリストを進める
			check = ZKN_GLBDATA_PokeListTblNoAdd( p_glb->p_glb, -1 );
		}else{
			// ポケモンリストを進める
			check = ZKN_GLBDATA_PokeListTblNoAdd( p_glb->p_glb, 1 );
		}
		
		if( check == TRUE ){
			// アプリケーション変更で今のアプリケーションをリセット
			ZknZukanSubChangMons( p_work, p_glb, p_work->now_apply );

			// 外国語テキストを出せるかチェック
			ZknZukanSubWorldTextMskSet( p_work, p_glb );

			// 選択移動音
			Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	キー操作による変更
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZKnZukanSubKeyMove( ZKN_ZUKAN_SUB_WORK* p_work )
{

	if( sys.trg & PAD_KEY_UP ){
		p_work->poke_tbl_move = ZKN_ZUKANSUB_BUTTON_BACK;
		return ;
	}

	if( sys.trg & PAD_KEY_DOWN ){
		p_work->poke_tbl_move = ZKN_ZUKANSUB_BUTTON_NEXT;
		return ;
	}

	p_work->poke_tbl_move = ZKN_ZUKANSUB_BUTTON_NUM;
}

//----------------------------------------------------------------------------
/**
 *	@brief	外国語テキストのボタンONOFF設定
 *
 *	@param	p_draw		描画ワーク
 *	@param	cp_work		データワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubWorldTextButtonDrawSet( ZKN_ZUKAN_SUB_DRAW* p_draw, const ZKN_ZUKAN_SUB_WORK* cp_work )
{
	if( (cp_work->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_HOME) == 0 ){
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_MY_COUNTRY ], FALSE );
	}else{
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_MY_COUNTRY ], TRUE );
	}

	if( (cp_work->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT00) == 0 ){
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_00 ], FALSE );
	}else{
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_00 ], TRUE );
	}

	if( (cp_work->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT01) == 0 ){
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_01 ], FALSE );
	}else{
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_01 ], TRUE );
	}

	if( (cp_work->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT02) == 0 ){
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_02 ], FALSE );
	}else{
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_02 ], TRUE );
	}

	if( (cp_work->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT03) == 0 ){
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_03 ], FALSE );
	}else{
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_03 ], TRUE );
	}

	if( (cp_work->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT04) == 0 ){
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_04 ], FALSE );
	}else{
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_04 ], TRUE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	外国語マスク設定
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubWorldTextMskSet( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb )
{
	BOOL ret;
	int i;
	int lang;
	
	p_work->poke_country_msk = 0;

	// 今のポケモンの外国フラグが設定されているかチェック
	for( i=0; i<ZKN_WORLD_TEXT_OUTWORLD_NUM; i++ ){
		// iの値は外国用国コードではなくGMMIDX値なので
		// 外国用国コードに変換する
		lang = ZKN_WT_WORLD_TEXT_GMM_Idx_LANG_Code( i );
		ret = ZKN_GLBDATA_PokeTextVersionFlagGet( p_glb->p_glb, lang );
		if( ret ){
			p_work->poke_country_msk |= ZKN_ZUKANSUB_COUNTRY_HOME;
			p_work->poke_country_msk |= 1 << (i + 1);
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンアニメ
 *	
 *	@param	act				アクター
 *	@param	button_event	ボタンイベント
 *	@param  world			ボタンナンバー	ZKN_ZUKANSUB_BUTTON～定数とリンク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZUkanSubWorldTextButtonAnm( CLACT_WORK_PTR act, int button_event, int world )
{
	int anm_seq;

	GF_ASSERT( (world >= ZKN_ZUKANSUB_BUTTON_MY_COUNTRY) && (world < ZKN_ZUKANSUB_BUTTON_NUM) );

	// worldからアニメシーケンスナンバー取得
	anm_seq = (world - ZKN_ZUKANSUB_BUTTON_MY_COUNTRY) * 2;
	
	if( button_event == BMN_EVENT_RELEASE ){
		
		// 押したボタンにする
		CLACT_AnmChg( act, anm_seq + 1 );
	}else{

		// おしてないボタンにする
		CLACT_AnmChg( act, anm_seq );
	}
}
