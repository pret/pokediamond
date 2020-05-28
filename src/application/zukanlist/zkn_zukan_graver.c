//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan_graver.c
 *	@brief		図鑑グラフィックバージョン
 *	@author		tomoya takahashi
 *	@data		2006.02.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"
#include "include/system/brightness.h"
#include "include/system/arc_util.h"
#include "include/system/fontproc.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"
#include "include/poketool/pokefoot.h"

#include "include/battle/battle_common.h"

#include "include/application/zukanlist/zukan.naix"
#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_zukan_common.h"

#define	__ZKN_ZUKANGRAVER_GRAVER_H_GLOBAL
#include "include/application/zukanlist/zkn_zukan_graver.h"

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
#define ZKN_ZUKANGRAVER_EVENT_NUM ( 0 )	// イベント数
#define ZKN_ZUKANGRAVER_OAM_BG_PRI	( 3 )
#define ZKN_ZUKANGRAVER_OAM_SOFT_PRI	( 32 )

// BGブライトネスフェード面
#define ZKN_ZUKANGRAVER_BRIGHTNESS_MSK	( GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )



enum{
	// 描画タイプフラグ
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_NORMAL = 0,	// 通常描画タイプ
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MANONLY,		// オスのみ描画タイプ
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_GIRLONLY,		// メスのみ描画タイプ
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWNONLY,	// 不明のみ描画タイプ
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_SIIUSI,		// シーウシ描画タイプ
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_SIIDORUGO,	// シードルゴ描画タイプ
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MINOMUTTI,	// ミノムッチ描画タイプ
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MINOMESU,		// ミノメス描画タイプ
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWN_POKE,	// アンノーン描画タイプ
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_DEOKISISU_POKE,// デオキシス描画タイプ

	// 通常描画タイプ
	ZKN_ZUKANGRAVER_DRAW_TYPE_MAN = 0,	// 男
	ZKN_ZUKANGRAVER_DRAW_TYPE_GIRL,		// 女
	ZKN_ZUKANGRAVER_DRAW_TYPE_NORM_NUM,

	// オスメスのみ描画タイプ
	ZKN_ZUKANGRAVER_DRAW_TYPE_ONLY = 0,
	ZKN_ZUKANGRAVER_DRAW_TYPE_ONLY_NUM,

	// ミノムッチ ミノメス描画タイプ
	ZKN_ZUKANGRAVER_DRAW_TYPE_MINOMUTTI_NUM = ZUKAN_WORK_MINOMUSHI_FORM_NUM,
	ZKN_ZUKANGRAVER_DRAW_TYPE_MINOMESU_NUM = ZUKAN_WORK_MINOMUSHI_FORM_NUM,

	// ウミウシ描画タイプ
	ZKN_ZUKANGRAVER_DRAW_TYPE_SIIUSI_NUM = ZUKAN_WORK_UMIUSHI_FORM_NUM,
	ZKN_ZUKANGRAVER_DRAW_TYPE_SIIDORUGO_NUM = ZUKAN_WORK_UMIUSHI_FORM_NUM,

	// アンノーン描画タイプ
	ZKN_ZUKANGRAVER_DRAW_TYPE_UNKNOWN_POKE_NUM = 28,
};


//-------------------------------------
//	ポケモングラフィック数
//=====================================
enum{
	ZKN_ZUKANGRAVER_GRA_FRONT,			// 今の表の絵
	ZKN_ZUKANGRAVER_GRA_BACK,			// 今の後ろの絵
	ZKN_ZUKANGRAVER_GRA_FRONT_NEXT,		// 次の表の絵
	ZKN_ZUKANGRAVER_GRA_BACK_NEXT,		// 次の後ろの絵
	ZKN_ZUKANGRAVER_GRA_NUM,
};
#define ZKN_ZUKANGRAVER_GRA_DRAW_Y			( 88 )
#define ZKN_ZUKANGRAVER_GRA_OAM_DRAW_Y_OFS	( 8 )
#define ZKN_ZUKANGRAVER_GRA_DRAW_FRONT_X	( 72 )
#define ZKN_ZUKANGRAVER_GRA_DRAW_BACK_X_OFS	( 112 )
#define ZKN_ZUKANGRAVER_GRA_DRAW_FRONT_NEXT_X	( ZKN_ZUKANGRAVER_GRA_DRAW_FRONT_X + 256 )

// FONTOAM
#define ZKN_GRAPHIC_BUTTONFONT_NUM			( 2 )
#define ZKN_GRAPHIC_BUTTONFONT_BMP_SIZE_CX ( 10 )
#define ZKN_GRAPHIC_BUTTONFONT_BMP_SIZE_CY ( 2 )
#define ZKN_GRAPHIC_BUTTON_PAL_OFS			( 4 )
#define ZKN_GRAPHIC_BUTTON_PAL_OFS_ON		( 1 )
#define ZKN_GRAPHIC_BUTTON_FONT_OFS_X		( -40 )
#define ZKN_GRAPHIC_BUTTON_FONT_OFS_Y		( 40 )

// ポケモン動作距離
#define ZKN_GRAPHIC_MOVE_X	( -256 )
#define ZKN_GRAPHIC_MOVE_Y	( 0 )
#define ZKN_GRAPHIC_MOVE_SYNC	( 16 )

// アイコン描画までのタイム
#define ZKN_GRAPHIC_MOVE_ICON_OFF_SYNC	( ZKN_GRAPHIC_MOVE_SYNC + 8 )

//-------------------------------------
//	描画初期化シーケンス
//=====================================
enum
{
	ZKN_ZUKANGRAVER_SEQINIT_ALLOC,
	ZKN_ZUKANGRAVER_SEQINIT_LOAD,
	ZKN_ZUKANGRAVER_SEQINIT_FADEIN,
	ZKN_ZUKANGRAVER_SEQINIT_END,
};

//-------------------------------------
//	図鑑破棄シーケンス
//=====================================
enum{
	ZKN_ZUKANGRAVER_SEQDELETE_FADEOUT_INIT,
	ZKN_ZUKANGRAVER_SEQDELETE_FADEOUT,
	ZKN_ZUKANGRAVER_SEQDELETE_RELEASE,
	ZKN_ZUKANGRAVER_SEQDELETE_FREE,
	ZKN_ZUKANGRAVER_SEQDELETE_END,
};


//-------------------------------------
//	OAMアニメシーケンス
//=====================================
enum{
	ZKN_ZUKANGRAVER_CELL_ANM_SEQ_BACK,
	ZKN_ZUKANGRAVER_CELL_ANM_SEQ_ICON,
	ZKN_ZUKANGRAVER_CELL_ANM_SEQ_BACK_2,
};

// アイコン座標
#define ZKN_ZUKANGRAVER_ICON_X	( 248 )
#define ZKN_ZUKANGRAVER_ICON_Y	( 96 )


// ポケグラダブルバッファ交互表示
enum{
	ZKN_ZUKANGRAVER_GRA_NOW_DRAW_01,
	ZKN_ZUKANGRAVER_GRA_NOW_DRAW_23,
	ZKN_ZUKANGRAVER_GRA_NOW_NUM
};

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	図鑑画面　グローバル変数
//=====================================
typedef struct {
	int*				p_event_key;		// イベントキー
	ZKN_GLB_DATA*		p_glb;				// グローバルデータ

	// 図鑑コモンアプリデータ
	const ZKN_APL_DATA* cp_zukan_common_apl;

	int					draw_type_flag;		// 描画タイプフラグ
	int					draw_type_max;		// 描画タイプ数
	int					draw_type;			// 描画タイプ
} ZKN_ZUKANGRAVER_GLB;

//-------------------------------------
//	図鑑画面　描画グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// 描画グローバルデータ
	BOOL pokegra_move_flag;	// 動作フラグ
	BOOL pokegra_move_end;	// ポケモングラフィック動作終了
} ZKN_ZUKANGRAVER_DRAWGLB;

//-------------------------------------
//	図鑑画面　描画ワーク
//=====================================
typedef struct {
	// ポケグラ描画用
	CLACT_WORK_PTR	pokegra_back[ ZKN_ZUKANGRAVER_GRA_NUM ];
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];
	ZKN_FONTOAM_DATA*	p_pokegra_font[ ZKN_GRAPHIC_BUTTONFONT_NUM ];
	ZKN_UTIL_MOVE_WORK pokegra_move[ ZKN_ZUKANGRAVER_GRA_NUM ];
	int pokegra_y[ ZKN_ZUKANGRAVER_GRA_NUM ];	// ポケモングラフィックY
	int now_draw_buff;		// 現在表示中のバッファIDX	0:(0と1) 1:(2と3)

	// 次のポケグラへ..のアイコン
	CLACT_WORK_PTR next_icon;

	// アイコン表示タイムｶｳﾝﾀとフラグ
	int icon_draw_s_time;
	BOOL icon_draw_flag;

	// drawtype
	int		draw_type_flag;		// 描画タイプフラグ
	int		draw_type;			// 描画タイプ
} ZKN_ZUKANGRAVER_DRAW;


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
static ZKN_ZUKANGRAVER_GLB* MakeZukanGraverGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_ZUKANGRAVER_DRAWGLB* MakeZukanGraverDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
//static ZKN_EVENT_DATA* MakeZukanGraverEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteZukanGraverGlb( ZKN_ZUKANGRAVER_GLB* p_glb );
static void DeleteZukanGraverDrawGlb( ZKN_ZUKANGRAVER_DRAWGLB* p_glb );
//static void DeleteZukanGraverEvent( ZKN_EVENT_DATA* p_event );


static int ZukanGraverEventDataNumGet( void );

static int ZknGraverAddDrawTypeGet( int draw_type_flag, int now, int num, int max );

//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanGraverProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanGraverProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanGraverProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanGraverProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanGraverProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// フェードインアウト
static void ZknZukanGraverDefaultFadeReq( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknZukanGraverDefaultFadeEndCheck( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb , BOOL fadein_out );

static void ZknZukanGraverSpritePokeGraPalFade( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb );

static void ZknZukanGraverOamFadeInit( ZKN_ZUKANGRAVER_DRAW* p_draw );
static void ZknZukanGraverOamFadeDelete( ZKN_ZUKANGRAVER_DRAW* p_draw );


static void ZknZukanGraverPokeGraFadeInit_Pack( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb );
static BOOL ZknZukanGraverPokeGraFadeMain_Pack( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb );
static void ZknZukanGraverPokeGraFadeInit( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, int move_x, int move_y, int idx );
static BOOL ZknZukanGraverPokeGraFadeMain( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, int idx );


// 描画タイプ関係
static int ZknZukanGraverPokeDrawTypeFlagGet( int monsno, const ZKN_ZUKANGRAVER_GLB* cp_glb );
static int ZknZukanGraverPokeDrawTypeNumGet( int monsno, const ZKN_ZUKANGRAVER_GLB* cp_glb );
static int ZknZukanGraverPokeDrawTypeFlagNormal( int monsno, const ZKN_ZUKANGRAVER_GLB* cp_glb );



// BG設定
static void ZknZukanGraverLoadResource( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap );
static void ZknZukanGraverReleaseResource( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb );
static void ZknZukanGraverSetUpBackGround( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, int heap );


// 足跡以外のアクター
static void ZknZukanGraverClactResLoad( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, int heap );
static void ZknZukanGraverClactResDelete( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb );
static void ZknZukanGraverClactAdd( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap );
static void ZknZukanGraverClactDelete( ZKN_ZUKANGRAVER_DRAW* p_draw );
static int ZknZukanGraverClactTypeNoChg( int type );

// ポケモングラフィック
static void ZknZukanGraverPokeGraDrawInit( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb );
static void ZknZukanGraverPokeGraDrawOn( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb );
static void ZknZukanGraverPoke_GraSet( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type_flag, int draw_type, int idx );
static void ZknZukanGraverPokeGraDrawOnTypeNormal( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx );
static void ZknZukanGraverPokeGraDrawOnTypeMinomutti( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx );
static void ZknZukanGraverPokeGraDrawOnTypeMinomesu( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx );
static void ZknZukanGraverPokeGraDrawOnTypeSiiusi( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx );
static void ZknZukanGraverPokeGraDrawOnTypeSiidorugo( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx );
static void ZknZukanGraverPokeGraDrawOnTypeAnnoon( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx );
static void ZknZukanGraverPokeGraDrawOnTypeDeokisisu( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx );

static void ZknZukanGraverPokeGraMatGet( int idx, int* x, int* y );
static void ZknZukanGraverPokeGraDrawOff( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb );
static inline int ZknZukanGraverGetBuffIdx_PokeGraIdx( int buff_idx, int idx );

// ポケモングラフィックテキスト
static void ZknZukanGraverFontInitGraphicType_Pack( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap, int draw_type_flag, int draw_type );
static void ZknZukanGraverFontSetUpGraphicType_Pack( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap, int draw_type_flag, int draw_type );
static void ZknZukanGraverFontSetUpGraphicType( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap, int draw_type_flag, int draw_type, int parent_idx, int fontoam_idx );
static int ZknZukanGraverFontSetUpGraphicTypeNormal( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeManOnly( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeGirlOnly( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeUnknownOnly( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeMinomutti( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeMinomesu( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeSiiusi( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeSiidorugo( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeAnnoon( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeDeokisisu( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );

static int ZknZukanGraverFontGet(ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type_flag, int draw_type);
static void ZknZukanGraverFontOamDelete( ZKN_ZUKANGRAVER_DRAW* p_draw );


// アイコン
static void ZknZukanGraverIconDrawAnm_S( ZKN_ZUKANGRAVER_DRAW* p_draw );
static void ZknZukanGraverIconDrawAnm_Main( ZKN_ZUKANGRAVER_DRAW* p_draw );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑　アプリ作成
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
void ZKN_ZukanGraverAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_ZUKANGRAVER_GLB*	p_glb;
	ZKN_ZUKANGRAVER_DRAWGLB*	p_drawglb;
//	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeZukanGraverGlb( heap, zkn_sys );
	p_drawglb = MakeZukanGraverDrawGlb( heap, zkn_sys );
//	p_event = MakeZukanGraverEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= NULL;
//	p_data->p_event_data	= p_event;
	p_data->event_num		= ZukanGraverEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanGraverProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanGraverProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanGraverProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanGraverProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanGraverProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanGraverProcDrawFuncDelete;
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
void ZKN_ZukanGraverAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteZukanGraverGlb( p_data->p_glb_data ); 
	DeleteZukanGraverDrawGlb( p_data->p_glb_draw );
//	DeleteZukanGraverEvent( p_data->p_event_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画タイプ足し算
 *
 *	@param	p_data			アプリデータ
 *	@param	num				足す値
 *
 *	@retval	TRUE	値変更した
 *	@retval	FALSE	変更できなかった
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanGraverDrawTypeAdd( ZKN_APL_DATA* p_data, int num )
{
	ZKN_ZUKANGRAVER_GLB* p_glb = p_data->p_glb_data;
	ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb = p_data->p_glb_draw;
	int last_num;

	// リスト動作中は変更できない
	if( p_drawglb->pokegra_move_flag == TRUE ){
		return FALSE;
	}
	
	last_num = p_glb->draw_type;

	// 計算結果描画タイプを取得
	p_glb->draw_type = ZknGraverAddDrawTypeGet( p_glb->draw_type_flag, p_glb->draw_type, num, p_glb->draw_type_max );

	// 変更されたかチェック
	if( last_num != p_glb->draw_type ){
		return TRUE;
	}

	return FALSE;
}


//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKANGRAVER_GLB* MakeZukanGraverGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKANGRAVER_GLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKANGRAVER_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKANGRAVER_GLB) );

	// main画面からのイベントキー
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrMain( zkn_sys ); 

	// グローバルデータ
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	// 図鑑コモンアプリグローバルデータ
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_COMMON );
	p_glb->cp_zukan_common_apl = p_apl;
	

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑	描画グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	描画グローバルデータ
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKANGRAVER_DRAWGLB* MakeZukanGraverDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKANGRAVER_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKANGRAVER_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKANGRAVER_DRAWGLB) );

	// 描画データ
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );
	
	return p_glb;
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑　イベント作成
 *
 *	@param	heap		使用するヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	イベントデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeZukanGraverEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = ZukanGraverEventDataNumGet();

	// イベントデータテーブル作成
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_MakeChangeRange( heap, &p_event_tbl[0], zkn_sys, ZKN_ZUKNA_EVENT_CHANGE_RANGE );

	return p_event_tbl;
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanGraverGlb( ZKN_ZUKANGRAVER_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑　描画グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanGraverDrawGlb( ZKN_ZUKANGRAVER_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑　イベントデータ破棄
 *
 *	@param	p_event	イベントデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanGraverEvent( ZKN_EVENT_DATA* p_event )
{

	GF_ASSERT( p_event );
	ZKN_EVENT_DeleteData( &p_event[0] );

	sys_FreeMemoryEz( p_event );//*/
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑アプリ　イベント数取得
 *	
 *	@param	none	
 *
 *	@return	図鑑アプリ　イベント数
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZukanGraverEventDataNumGet( void )
{
	return ZKN_ZUKANGRAVER_EVENT_NUM;
}



// 足し算コア部分
static inline int ZknGraverDrawTypeAddCore( int now, int max, int add )
{
	int ret;
	
	if( add > 0 ){
		if( (now + add) < max ){
			ret = now + add;
		}else{
			ret = 0;
		}
	}else{
		if( (now + add) >= 0 ){
			ret = add;
		}else{
			ret = max - 1;
		}
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画タイプフラグ別　次の描画タイプ取得関数
 *
 *	@param	draw_type_flag	描画タイプフラグ
 *	@param	now				今の描画タイプ
 *	@param	num				足す値
 *	@param	max				最大数
 *
 *	@return	移動先描画タイプ
 */
//-----------------------------------------------------------------------------
static int ZknGraverAddDrawTypeGet( int draw_type_flag, int now, int num, int max )
{
	int ret;

	ret = ZknGraverDrawTypeAddCore( now, max, num );

	return ret;
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
static int ZknZukanGraverProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKANGRAVER_GLB* p_glb = p_glbdata;
	int monsno;

	
	// ポケモンナンバー取得
	monsno = ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb );
	
	// ポケモンからグラフィック切り替えタイプを設定
	p_glb->draw_type_flag = ZknZukanGraverPokeDrawTypeFlagGet( monsno, p_glb );
	p_glb->draw_type_max = ZknZukanGraverPokeDrawTypeNumGet( monsno, p_glb );
	p_glb->draw_type = 0;

	
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
static int ZknZukanGraverProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKANGRAVER_GLB* p_glb = p_glbdata;
	
	
	// 終了へ
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
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
static int ZknZukanGraverProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
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
static int ZknZukanGraverProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKANGRAVER_GLB* cp_glb = cp_glbdata;
	ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKANGRAVER_DRAW*	p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_ZUKANGRAVER_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_ZUKANGRAVER_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_ZUKANGRAVER_DRAW) );
		p_drawwork = p_drawdata->p_work;
		p_drawwork->draw_type_flag = cp_glb->draw_type_flag;

		// 描画グローバル変数初期化
		p_drawglb->pokegra_move_flag = FALSE;
		p_drawglb->pokegra_move_end = FALSE;
		
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANGRAVER_SEQINIT_LOAD:
		ZknZukanGraverLoadResource( p_drawwork, p_drawglb, cp_glb, p_drawdata->heap );

		ZknZukanGraverDefaultFadeReq( p_drawwork, p_drawglb, cp_glb, TRUE );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANGRAVER_SEQINIT_FADEIN:

		check = ZknZukanGraverDefaultFadeEndCheck( p_drawwork, p_drawglb, cp_glb, TRUE );

		if( check ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_ZUKANGRAVER_SEQINIT_END:
		G2_BlendNone();
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
static int ZknZukanGraverProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKANGRAVER_GLB* cp_glb = cp_glbdata;
	ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKANGRAVER_DRAW*	p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case 0:	
		// フラグが切り替わったら描画変更
		if( cp_glb->draw_type != p_drawwork->draw_type ){

			// 更新
			p_drawwork->draw_type = cp_glb->draw_type;
			p_drawwork->now_draw_buff = (p_drawwork->now_draw_buff + 1) % ZKN_ZUKANGRAVER_GRA_NOW_NUM;		// 表示バッファインデックス変更

			// グラフィック動作処理初期化
			ZknZukanGraverPokeGraFadeInit_Pack( p_drawwork, p_drawglb );
			ZknZukanGraverIconDrawAnm_S( p_drawwork );

			// ﾎﾟｹｸﾞﾗ動作中
			p_drawglb->pokegra_move_flag = TRUE;

			// ボタンにタッチ
			Snd_SePlay( ZKN_SND_SLIDE );
			p_drawdata->seq ++;
		}
		break;

	case 1:
		if( ZknZukanGraverPokeGraFadeMain_Pack( p_drawwork, p_drawglb ) == TRUE ){
			p_drawglb->pokegra_move_end = TRUE;
			p_drawdata->seq ++;
		}
		break;

	case 2:
		// １シンク前で　動作が終わったらグラフィック変更
		if( (p_drawglb->pokegra_move_end == TRUE) ){
			// フォント切り替え
			ZknZukanGraverFontSetUpGraphicType_Pack( p_drawwork, p_drawglb, cp_glb, p_drawdata->heap, cp_glb->draw_type_flag, cp_glb->draw_type );
			// 表示切替
			ZknZukanGraverPokeGraDrawOn( p_drawwork, p_drawglb, cp_glb );
			p_drawglb->pokegra_move_end = FALSE;

			// ﾎﾟｹｸﾞﾗ動作完了
			p_drawglb->pokegra_move_flag = FALSE;

			// 最初に戻る
			p_drawdata->seq = 0;
		}
		break;

	default:
		// おかしい
		GF_ASSERT( 0 );
		break;
	}

	// アイコン描画ONOFF処理
	ZknZukanGraverIconDrawAnm_Main( p_drawwork );

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
static int ZknZukanGraverProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKANGRAVER_GLB* cp_glb = cp_glbdata;
	ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKANGRAVER_DRAW*	p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
		
	case ZKN_ZUKANGRAVER_SEQDELETE_FADEOUT_INIT:
		ZknZukanGraverDefaultFadeReq( p_drawwork, p_drawglb, cp_glb, FALSE );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANGRAVER_SEQDELETE_FADEOUT:
		check = ZknZukanGraverDefaultFadeEndCheck( p_drawwork, p_drawglb, cp_glb, FALSE );

		if( check ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_ZUKANGRAVER_SEQDELETE_RELEASE:
		ZknZukanGraverReleaseResource( p_drawwork, p_drawglb );
		p_drawdata->seq++;
		break;

	case ZKN_ZUKANGRAVER_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANGRAVER_SEQDELETE_END:
		return ZKN_PROC_TRUE;

	default:
		break;
	}
	
	return ZKN_PROC_FALSE;
}






//----------------------------------------------------------------------------
/**
 *	@brief	リソース読み込み
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverLoadResource(  ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap  )
{

	// ポケモングラフィック表示ON
	ZknZukanGraverPokeGraDrawInit( p_draw, p_drawglb, cp_glb );

	// アクターリソース読み込み
	ZknZukanGraverClactResLoad( p_draw, p_drawglb, heap );

	// 背景設定
	ZknZukanGraverSetUpBackGround( p_drawglb, heap );

	// アクター登録
	ZknZukanGraverClactAdd( p_draw, p_drawglb, cp_glb, heap );

	// FONTOAM設定
	ZknZukanGraverFontInitGraphicType_Pack( p_draw, p_drawglb, cp_glb, heap,cp_glb->draw_type_flag, cp_glb->draw_type );
}

//----------------------------------------------------------------------------
/**
 *	@brief	リソースの破棄
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverReleaseResource(  ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb )
{
	// FONTOAM破棄
	ZknZukanGraverFontOamDelete( p_draw );
	
	// アクター破棄
	ZknZukanGraverClactDelete( p_draw );	

	// アクターリソース破棄
	ZknZukanGraverClactResDelete( p_draw, p_drawglb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	背景設定
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverSetUpBackGround( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;
	
	// キャラクタデータ転送
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_main_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, 0, 0, TRUE, heap );

	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_main1_lzh_NSCR, TRUE, &p_scrn, heap );
	
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
 *	@brief	描画ON初期化
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		データグローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawInit( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb )
{
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	int i;
	int next_type;

	// 今のポケモン
	ZknZukanGraverPoke_GraSet( p_draw, p_drawglb, cp_glb, monsno, cp_glb->draw_type_flag, cp_glb->draw_type, ZKN_ZUKANGRAVER_GRA_FRONT );

	// 次のポケモン設定
	next_type = ZknGraverAddDrawTypeGet( cp_glb->draw_type_flag, cp_glb->draw_type, 1, cp_glb->draw_type_max );
	ZknZukanGraverPoke_GraSet( p_draw, p_drawglb, cp_glb, monsno, cp_glb->draw_type_flag, next_type, ZKN_ZUKANGRAVER_GRA_FRONT_NEXT );

	// 表示
	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){
		ZKN_GlbPokemonGraphicDrawFlagSet_Idx( p_drawglb->p_drawglb, TRUE, i );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック表示ON
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawOn( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb )
{
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	int i;
	int next_type;

	// 次のポケモン設定
	next_type = ZknGraverAddDrawTypeGet( cp_glb->draw_type_flag, cp_glb->draw_type, 1, cp_glb->draw_type_max );
	ZknZukanGraverPoke_GraSet( p_draw, p_drawglb, cp_glb, monsno, cp_glb->draw_type_flag, next_type, ZKN_ZUKANGRAVER_GRA_FRONT_NEXT );
}

//----------------------------------------------------------------------------
/**
 *	@brief	表示グラフィック設定
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	monsno			モンスターナンバー
 *	@param	draw_type_flag	描画タイプフラグ
 *	@param	draw_type		描画タイプ
 *	@param	idx				インデックス
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPoke_GraSet( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type_flag, int draw_type, int idx )
{
	GF_ASSERT( idx <= 2 );
	
	switch( draw_type_flag ){
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_NORMAL:	// 通常描画タイプ
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MANONLY:		// オスのみ描画タイプ
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_GIRLONLY:		// メスのみ描画タイプ
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWNONLY:	// 不明のみ描画タイプ
		ZknZukanGraverPokeGraDrawOnTypeNormal( p_draw, p_drawglb, cp_glb, monsno, draw_type, idx );
		break;
		
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MINOMUTTI:		// ミノッチ描画タイプ
		ZknZukanGraverPokeGraDrawOnTypeMinomutti( p_draw, p_drawglb, cp_glb, monsno, draw_type, idx );
		break;
		
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MINOMESU:	// ミノメス描画タイプ
		ZknZukanGraverPokeGraDrawOnTypeMinomesu( p_draw, p_drawglb, cp_glb, monsno, draw_type, idx );
		break;
		
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_SIIUSI:		// シーウシ描画タイプ
		ZknZukanGraverPokeGraDrawOnTypeSiiusi( p_draw, p_drawglb, cp_glb, monsno, draw_type, idx );
		break;

	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_SIIDORUGO:		// シードルゴ描画タイプ
		ZknZukanGraverPokeGraDrawOnTypeSiidorugo( p_draw, p_drawglb, cp_glb, monsno, draw_type, idx );
		break;

	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWN_POKE:		// アンノーン描画タイプ
		ZknZukanGraverPokeGraDrawOnTypeAnnoon( p_draw, p_drawglb, cp_glb, monsno, draw_type, idx );
		break;

	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_DEOKISISU_POKE:
		ZknZukanGraverPokeGraDrawOnTypeDeokisisu( p_draw, p_drawglb, cp_glb, monsno, draw_type, idx );
		break;

	default:
		GF_ASSERT(0);
		break;
	}
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
static void ZknZukanGraverPokeGraDrawOff( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb )
{
	int i;
	
	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){
		ZKN_GlbPokemonGraphicDrawFlagSet_Idx( p_drawglb->p_drawglb, FALSE, i );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	セルアクターのリソース読み込み
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverClactResLoad( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// キャラクタデータ読み込み
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_sugata_oam_lzh_NCGR, TRUE,
			NARC_zukan_zkn_sugata_oam_lzh_NCGR + ZKN_GRAPHIC_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_sugata_oam_NCLR, FALSE, 
			NARC_zukan_zkn_sugata_oam_NCLR + ZKN_GRAPHIC_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_GRAPHIC_PLTT_LOAD, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// セルデータ読み込み
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_sugata_oam_lzh_NCER, TRUE,
			NARC_zukan_zkn_sugata_oam_lzh_NCER + ZKN_GRAPHIC_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_sugata_oam_lzh_NANR, TRUE,
			NARC_zukan_zkn_sugata_oam_lzh_NANR + ZKN_GRAPHIC_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクターリソース破棄
 *	
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverClactResDelete( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb )
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
 *	@param	cp_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverClactAdd( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int x, y;
	int i;

	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_sugata_oam_lzh_NCGR + ZKN_GRAPHIC_RES_ID,
			NARC_zukan_zkn_sugata_oam_NCLR + ZKN_GRAPHIC_RES_ID, 
			NARC_zukan_zkn_sugata_oam_lzh_NCER + ZKN_GRAPHIC_RES_ID,
			NARC_zukan_zkn_sugata_oam_lzh_NANR + ZKN_GRAPHIC_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_ZUKANGRAVER_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_ZUKANGRAVER_OAM_SOFT_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	add.mat.x = 0;
	add.mat.y = 0;
	
	// 背景
	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){

		// 座標
		ZknZukanGraverPokeGraMatGet( i, &x, &y );
		add.mat.x = x << FX32_SHIFT;
		add.mat.y = (y + ZKN_ZUKANGRAVER_GRA_OAM_DRAW_Y_OFS) << FX32_SHIFT;


		p_draw->pokegra_back[ i ] = CLACT_AddSimple( &add );
		if( (i % 2) == 0 ){
			CLACT_AnmChg( p_draw->pokegra_back[ i ], ZKN_ZUKANGRAVER_CELL_ANM_SEQ_BACK );
		}else{
			CLACT_AnmChg( p_draw->pokegra_back[ i ], ZKN_ZUKANGRAVER_CELL_ANM_SEQ_BACK_2 );
		}
	}

	// アイコン
	add.mat.x = ZKN_ZUKANGRAVER_ICON_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANGRAVER_ICON_Y << FX32_SHIFT;
	add.pri	  = 0;
	p_draw->next_icon = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->next_icon, ZKN_ZUKANGRAVER_CELL_ANM_SEQ_ICON );
	CLACT_SetAnmFlag( p_draw->next_icon, TRUE );
	CLACT_BGPriorityChg( p_draw->next_icon, 0 );
	// 描画ONOFF設定
	if( cp_glb->draw_type_max <= 1 ){
		CLACT_SetDrawFlag( p_draw->next_icon, FALSE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクターを破棄
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverClactDelete( ZKN_ZUKANGRAVER_DRAW* p_draw )
{
	int i;
	
	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){
		CLACT_Delete( p_draw->pokegra_back[ i ] );
	}

	CLACT_Delete( p_draw->next_icon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑デフォルトフェード処理
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	fadein_out	フェードインアウト
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverDefaultFadeReq( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, BOOL fadein_out )
{
	// 半透明OAM設定
	ZknZukanGraverOamFadeInit( p_draw );

	// ブライトネスを使って良いかﾁｪｯｸ
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_ZUKANGRAVER_BRIGHTNESS_MSK, PLANEMASK_BG3, ZKN_UTIL_FADE_MAIN );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					 BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_ZUKANGRAVER_BRIGHTNESS_MSK, PLANEMASK_BG3, ZKN_UTIL_FADE_MAIN );

		}
	}

	// ポケグラパレットフェード設定
	ZknZukanGraverSpritePokeGraPalFade( p_drawglb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑デフォルトフェード処理　終了チェック
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	fadein_out	フェードイン TRUE アウト FALSE
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanGraverDefaultFadeEndCheck( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check;
	
	// フェードワークを図鑑データが動かしてよいかチェック
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		check = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade );
	}else{
		check = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade );
	}
	

	if( check == TRUE ){

		// フェードインのときは半透明破棄
		if( fadein_out == TRUE ){
			// OAM半透明設定破棄
			ZknZukanGraverOamFadeDelete( p_draw );
		}else{
			// ポケモングラフィック表示OFF
			ZknZukanGraverPokeGraDrawOff( p_drawglb );
		}
	}else{
		// ポケグラパレットフェード設定
		ZknZukanGraverSpritePokeGraPalFade( p_drawglb );
	}

	return check;
}


//----------------------------------------------------------------------------
/**
 *	@brief	OAMのフェード処理初期化
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverOamFadeInit( ZKN_ZUKANGRAVER_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){
		CLACT_ObjModeSet( p_draw->pokegra_back[ i ], GX_OAM_MODE_XLU );
	}

	CLACT_ObjModeSet( p_draw->next_icon, GX_OAM_MODE_XLU );

	// フォントOAM
	for( i=0; i<ZKN_GRAPHIC_BUTTONFONT_NUM; i++ ){
		FONTOAM_ObjModeSet( p_draw->p_pokegra_font[ i ]->p_fontoam, GX_OAM_MODE_XLU );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMのフェード処理リセット
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverOamFadeDelete( ZKN_ZUKANGRAVER_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){
		CLACT_ObjModeSet( p_draw->pokegra_back[ i ], GX_OAM_MODE_NORMAL );
	}
	CLACT_ObjModeSet( p_draw->next_icon, GX_OAM_MODE_NORMAL );

	// フォントOAM
	for( i=0; i<ZKN_GRAPHIC_BUTTONFONT_NUM; i++ ){
		FONTOAM_ObjModeSet( p_draw->p_pokegra_font[ i ]->p_fontoam, GX_OAM_MODE_NORMAL );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィックパレットフェード値設定
 *
 *	@param	p_drawglb	描画グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverSpritePokeGraPalFade( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb )
{
	int i;

	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){
		// ブライトネス値設定
		ZKN_GLB_SpritePokeGraPalFade_Idx( p_drawglb->p_drawglb, &p_drawglb->p_drawglb->fade, i );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック動作初期化　パック
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraFadeInit_Pack( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb )
{
	int i;

	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){
		ZknZukanGraverPokeGraFadeInit( p_draw, p_drawglb, ZKN_GRAPHIC_MOVE_X, ZKN_GRAPHIC_MOVE_Y, i );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック動作メイン　パック
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	終わっていない
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanGraverPokeGraFadeMain_Pack( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb )
{
	int i;
	BOOL check;

	// 初期化していないときは何もしない
	if( p_drawglb->pokegra_move_flag == FALSE ){
		return TRUE;
	}

	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){
		check = ZknZukanGraverPokeGraFadeMain( p_draw, p_drawglb, i );
	}

	// FONT_OAMを変更
	for( i=0; i<ZKN_GRAPHIC_BUTTONFONT_NUM; i++ ){
		FONTOAM_ReflectParentMat( p_draw->p_pokegra_font[ i ]->p_fontoam );
	}

	return check;	// 全部同じシンク数で動くのでこれでよい
}

//----------------------------------------------------------------------------
/**
 * [ポケモンリスト画面フェード]
 *	@brief	ポケモングラフィックフェード初期化
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	move_x		ｘ開始座標までの距離
 *	@param	move_y		ｙ開始座標までの距離
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraFadeInit( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, int move_x, int move_y, int idx )
{
	int x;
	int y;
	int def_x;
	int def_y;
	int poke_arry_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, idx );

	// デフォルト座標の取得
	ZknZukanGraverPokeGraMatGet( idx, &def_x, &def_y );
	
	// 今の座標取得
	ZKN_GlbPokemonGraphicGetMatrix_Idx( p_drawglb->p_drawglb, &x, &y, poke_arry_idx );

	// 座標を設定
	ZKN_UTIL_MoveReq( &p_draw->pokegra_move[idx], def_x + move_x, def_x, def_y + move_y, def_y, ZKN_GRAPHIC_MOVE_SYNC );

	// スプライトのポケモンは高さが変更されている可能性があるので保存
	p_draw->pokegra_y[idx] = y - def_y;
}

//----------------------------------------------------------------------------
/**
 * [ポケモンリスト画面フェード]
 *	@brief	ポケモングラフィックフェード
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanGraverPokeGraFadeMain( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, int idx )
{
	BOOL check;
	VecFx32 mat;
	int poke_arry_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, idx );
	
	check = ZKN_UTIL_MoveMain( &p_draw->pokegra_move[ idx ] );

	// 座標設定
	ZKN_GlbPokemonGraphicSetMatrix_Idx( p_drawglb->p_drawglb, p_draw->pokegra_move[ idx ].x, p_draw->pokegra_move[ idx ].y + p_draw->pokegra_y[idx], poke_arry_idx );

	// OAM座標設定
	mat.x = p_draw->pokegra_move[ idx ].x << FX32_SHIFT;
	mat.y = (p_draw->pokegra_move[ idx ].y + ZKN_ZUKANGRAVER_GRA_OAM_DRAW_Y_OFS) << FX32_SHIFT;
	CLACT_SetMatrix( p_draw->pokegra_back[ poke_arry_idx ], &mat );

	return check;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン描画タイプフラグ設定
 *
 *	@param	monsno	モンスターナンバー
 *	@param	cp_glb	グローバルデータ
 *
 *	@return	描画タイプフラグ
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverPokeDrawTypeFlagGet( int monsno, const ZKN_ZUKANGRAVER_GLB* cp_glb )
{
#if 1	// 1にするとミノムッチなどが反映
	// ミノムッチ
	if( monsno == MONSNO_MINOMUTTI ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MINOMUTTI;
	}

	// ミノメス
	if( monsno == MONSNO_MINOMESU ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MINOMESU;
	}

	// シーウシ
	if( monsno == MONSNO_SIIUSI ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_SIIUSI;
	}

	// シードルゴ
	if( monsno == MONSNO_SIIDORUGO ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_SIIDORUGO;
	}
#endif

	// アンノーン
	if( monsno == MONSNO_ANNOON ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWN_POKE;
	}

	// デオキシス
	if( monsno == MONSNO_DEOKISISU ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_DEOKISISU_POKE;
	}

	// その他はノーマルで調べる
	return ZknZukanGraverPokeDrawTypeFlagNormal( monsno, cp_glb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画タイプの数を取得
 *
 *	@param	monsno	モンスターナンバー
 *	@param	cp_glb	グローバル
 *
 *	@return	描画タイプ数
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverPokeDrawTypeNumGet( int monsno, const ZKN_ZUKANGRAVER_GLB* cp_glb )
{
#if 1	// 1にするとミノムッチなどが反映
	// ミノムッチ
	if( monsno == MONSNO_MINOMUTTI ){
		return ZKN_GLBDATA_SaveData_MinomuttiNumGet( cp_glb->p_glb );
	}

	// ミノメス
	if( monsno == MONSNO_MINOMESU ){
		return ZKN_GLBDATA_SaveData_MinomesuNumGet( cp_glb->p_glb );
	}

	// シーウシ
	if( monsno == MONSNO_SIIUSI ){
		return ZKN_GLBDATA_SaveData_SiiusiNumGet( cp_glb->p_glb );
	}

	// シードルゴ
	if( monsno == MONSNO_SIIDORUGO ){
		return ZKN_GLBDATA_SaveData_SiidorugoNumGet( cp_glb->p_glb );
	}
#endif

	// アンノーン
	if( monsno == MONSNO_ANNOON ){
		return ZKN_GLBDATA_SaveData_AnoonNumGet( cp_glb->p_glb );
	}

	// デオキシス
	if( monsno == MONSNO_DEOKISISU ){
		return ZKN_GLBDATA_SaveData_DeokisisuFormSeeNumGet( cp_glb->p_glb );
	}

	// その他はノーマルで調べる
	return ZKN_GLBDATA_SaveData_SexNumGet( cp_glb->p_glb, monsno );
}

//----------------------------------------------------------------------------
/**
 *	@brief	通常ポケモンの描画タイプフラグを取得
 *
 *	@param	monsno		モンスターナンバー
 *	@param	cp_glb		グローバル
 *
 *	@return	描画タイプフラグ
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverPokeDrawTypeFlagNormal( int monsno, const ZKN_ZUKANGRAVER_GLB* cp_glb )
{
	int sex;
	int type_num;
	sex = PokePersonalParaGet( monsno, ID_PER_sex );

	if( sex == MONS_MALE ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MANONLY;
	}
	if( sex == MONS_FEMALE ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_GIRLONLY;
	}
	if( sex == MONS_UNKNOWN ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWNONLY;
	}

	// 数を求め1個しかないときも～ONLYタイプにする
	type_num = ZKN_GLBDATA_SaveData_SexNumGet( cp_glb->p_glb, monsno );
	if( type_num == 1 ){
		sex = ZKN_GLBDATA_SaveData_SexGet( cp_glb->p_glb, monsno, ZUKAN_WORK_SEX_FIRST );
		GF_ASSERT( sex != ZUKAN_WORK_GET_SEX_ERR );
		if( sex == MONS_MALE ){
			return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MANONLY;
		}
		if( sex == MONS_FEMALE ){
			return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_GIRLONLY;
		}
		if( sex == MONS_UNKNOWN ){
			return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWNONLY;
		}
	}
	
	return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_NORMAL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン描画	描画タイプ　普通
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバルデータ
 *	@param	monsno			モンスターナンバー
 *	@param	draw_type		描画タイプ
 *	@param	s_idx			インデックス
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawOnTypeNormal( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx )
{
	int sex;
	int x, y;
	int buff_idx;

	// 表
	ZknZukanGraverPokeGraMatGet( s_idx, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx );
	sex = ZKN_UTIL_PokemonGraphicSet_FS_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			monsno, PARA_FRONT,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( sex != ZUKAN_WORK_GET_SEX_ERR );

	// 裏
	ZknZukanGraverPokeGraMatGet( s_idx+1, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx + 1 );
	sex = ZKN_UTIL_PokemonGraphicSet_FS_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			monsno, PARA_BACK,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( sex != ZUKAN_WORK_GET_SEX_ERR );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン描画	描画タイプ　ミノムッチ
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバルデータ
 *	@param	cp_glb			グローバルデータ
 *	@param	monsno			モンスターナンバー
 *	@param	draw_type		描画ﾀｲﾌﾟ
 *	@param	s_idx			ポケモングラフィックインデックス
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawOnTypeMinomutti( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx )
{
	int x, y;
	int area_type;
	int buff_idx;
	
	// 表
	ZknZukanGraverPokeGraMatGet( s_idx, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx );
	area_type = ZKN_UTIL_PokemonGraphicSet_Minomutti_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_FRONT,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( area_type != ZUKAN_WORK_GET_SEX_ERR );

	// 裏
	ZknZukanGraverPokeGraMatGet( s_idx+1, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx + 1 );
	area_type = ZKN_UTIL_PokemonGraphicSet_Minomutti_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_BACK,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( area_type != ZUKAN_WORK_GET_SEX_ERR );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン描画	描画タイプ　ミノメス
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバルデータ
 *	@param	cp_glb			グローバルデータ
 *	@param	monsno			モンスターナンバー
 *	@param	draw_type		描画ﾀｲﾌﾟ
 *	@param	s_idx			ポケモングラフィックインデックス
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawOnTypeMinomesu( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx )
{
	int x, y;
	int area_type;
	int buff_idx;
	
	// 表
	ZknZukanGraverPokeGraMatGet( s_idx, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx );
	area_type = ZKN_UTIL_PokemonGraphicSet_Minomesu_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_FRONT,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( area_type != ZUKAN_WORK_GET_SEX_ERR );

	// 裏
	ZknZukanGraverPokeGraMatGet( s_idx+1, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx + 1 );
	area_type = ZKN_UTIL_PokemonGraphicSet_Minomesu_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_BACK,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( area_type != ZUKAN_WORK_GET_SEX_ERR );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン描画	描画タイプ　シーウシ
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバルデータ
 *	@param	cp_glb			グローバルデータ
 *	@param	monsno			モンスターナンバー
 *	@param	draw_type		描画ﾀｲﾌﾟ
 *	@param	s_idx			ポケモングラフィックインデックス
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawOnTypeSiiusi( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx )
{
	int x, y;
	int area_type;
	int buff_idx;
	
	// 表
	ZknZukanGraverPokeGraMatGet( s_idx, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx );
	area_type = ZKN_UTIL_PokemonGraphicSet_Siiusi_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_FRONT,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( area_type != ZUKAN_WORK_GET_SEX_ERR );

	// 裏
	ZknZukanGraverPokeGraMatGet( s_idx+1, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx + 1 );
	area_type = ZKN_UTIL_PokemonGraphicSet_Siiusi_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_BACK,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( area_type != ZUKAN_WORK_GET_SEX_ERR );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン描画	描画タイプ　シーシードルゴ
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバルデータ
 *	@param	cp_glb			グローバルデータ
 *	@param	monsno			モンスターナンバー
 *	@param	draw_type		描画ﾀｲﾌﾟ
 *	@param	s_idx			ポケモングラフィックインデックス
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawOnTypeSiidorugo( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx )
{
	int x, y;
	int area_type;
	int buff_idx;
	
	// 表
	ZknZukanGraverPokeGraMatGet( s_idx, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx );
	area_type = ZKN_UTIL_PokemonGraphicSet_Siidorugo_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_FRONT,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( area_type != ZUKAN_WORK_GET_SEX_ERR );

	// 裏
	ZknZukanGraverPokeGraMatGet( s_idx+1, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx + 1 );
	area_type = ZKN_UTIL_PokemonGraphicSet_Siidorugo_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_BACK,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( area_type != ZUKAN_WORK_GET_SEX_ERR );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン描画	描画タイプ　アンノーン
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバルデータ
 *	@param	monsno			モンスターナンバー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawOnTypeAnnoon( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx )
{
	int x, y;
	int form;
	int buff_idx;
	
	// 表
	ZknZukanGraverPokeGraMatGet( s_idx, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx );
	form = ZKN_UTIL_PokemonGraphicSet_Anoon_Idx(	
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_FRONT,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( form != ZUKAN_WORK_GET_SEX_ERR );

	// 裏
	ZknZukanGraverPokeGraMatGet( s_idx+1, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx + 1 );
	form = ZKN_UTIL_PokemonGraphicSet_Anoon_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_BACK,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( form != ZUKAN_WORK_GET_SEX_ERR );
}

//----------------------------------------------------------------------------
/**
 *	@brief	デオキシス　描画
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	monsno		モンスターナンバー
 *	@param	draw_type	描画タイプ
 *	@param	s_idx		グラフィックインデックス
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawOnTypeDeokisisu( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx )
{
	int x, y;
	int form;
	int buff_idx;
	
	// 表
	ZknZukanGraverPokeGraMatGet( s_idx, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx );
	form = ZKN_UTIL_PokemonGraphicSet_Deokisisu_Idx(	
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_FRONT,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( form != POKEZUKAN_DEOKISISU_INIT );

	// 裏
	ZknZukanGraverPokeGraMatGet( s_idx+1, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx + 1 );
	form = ZKN_UTIL_PokemonGraphicSet_Deokisisu_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_BACK,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( form != POKEZUKAN_DEOKISISU_INIT );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ふぉんとOAMの初期化パック関数
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバル	
 *	@param	heap			ヒープ
 *	@param	draw_type_flag	描画タイプフラグ
 *	@param	draw_type		描画タイプ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverFontInitGraphicType_Pack( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap, int draw_type_flag, int draw_type )
{
	int next_draw_type;
	int pearent_idx;
	
	
	// 今表示中のもののテキスト
	pearent_idx		= ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, ZKN_ZUKANGRAVER_GRA_FRONT );
	ZknZukanGraverFontSetUpGraphicType( p_draw, p_drawglb, cp_glb, heap,  draw_type_flag, draw_type, pearent_idx, 0 );

	// 次表示するもののテキスト
	next_draw_type	= ZknGraverAddDrawTypeGet( draw_type_flag, draw_type, 1, cp_glb->draw_type_max );	
	pearent_idx		= ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, ZKN_ZUKANGRAVER_GRA_FRONT_NEXT );
	ZknZukanGraverFontSetUpGraphicType( p_draw, p_drawglb, cp_glb, heap,  draw_type_flag, next_draw_type, pearent_idx, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ふぉんとOAMの設定パック関数
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバル	
 *	@param	heap			ヒープ
 *	@param	draw_type_flag	描画タイプフラグ
 *	@param	draw_type		描画タイプ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverFontSetUpGraphicType_Pack( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap, int draw_type_flag, int draw_type )
{
	int next_draw_type;
	int pearent_idx;
	int fontoam_idx;
	
	// 次表示するもののテキスト
	next_draw_type	= ZknGraverAddDrawTypeGet( draw_type_flag, draw_type, 1, cp_glb->draw_type_max );	
	pearent_idx		= ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, ZKN_ZUKANGRAVER_GRA_FRONT_NEXT );
	fontoam_idx	= (p_draw->now_draw_buff + 1) % ZKN_ZUKANGRAVER_GRA_NOW_NUM;

	// 破棄してから作る
	ZKN_FONTOAM_Delete( p_draw->p_pokegra_font[ fontoam_idx ] );
	ZknZukanGraverFontSetUpGraphicType( p_draw, p_drawglb, cp_glb, heap,  draw_type_flag, next_draw_type, pearent_idx, fontoam_idx );
}


//----------------------------------------------------------------------------
/**
 *	@brief	描画タイプ文字列の描画
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	heap			ヒープ
 *	@param	draw_type_flag	描画タイプフラグ
 *	@param	draw_type		描画タイプ
 *	@param  pearent_idx		親アクターIDX
 *	@param	fontoam_idx		フォントOAMIDX
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverFontSetUpGraphicType( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap, int draw_type_flag, int draw_type, int parent_idx, int fontoam_idx )
{
	GF_BGL_BMPWIN* win;	// 文字列書き込み先
	ZKN_FONTOAM_INIT fontoam_init;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;
	int pltt_ofs;	// パレットアドレス
	int comment;

	// 先にCLACTを登録してある必要がある
	GF_ASSERT( p_draw->pokegra_back[ parent_idx ] );


	// BMMデータIDX取得
	comment = ZknZukanGraverFontGet( p_drawglb, cp_glb, draw_type_flag, draw_type );

	// 初期化データの共通部分を作成
	// 共通データ代入
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( p_draw->res_obj[ CLACT_U_PLTT_RES ], NULL );
	fontoam_init.x			 = ZKN_GRAPHIC_BUTTON_FONT_OFS_X;
	fontoam_init.y			 = ZKN_GRAPHIC_BUTTON_FONT_OFS_Y;
	fontoam_init.bg_pri		 = ZKN_ZUKANGRAVER_OAM_BG_PRI;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;

	// パレット転送先アドレス取得
	pltt_ofs = GetPlttProxyOffset( fontoam_init.pltt, NNS_G2D_VRAM_TYPE_2DMAIN );

	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_GRAPHIC_BUTTONFONT_BMP_SIZE_CX,
			ZKN_GRAPHIC_BUTTONFONT_BMP_SIZE_CY );

	// comment
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, comment, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_draw->pokegra_back[ parent_idx ];
	p_draw->p_pokegra_font[ fontoam_idx ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_pokegra_font[ fontoam_idx ]->p_fontoam, pltt_ofs );

	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( win );
}


//----------------------------------------------------------------------------
/**
 *	@brief	描画タイプ文字列の描画	描画タイプ　普通
 *
 *	@param	p_drawglb		描画グローバル
 *	@param	heap			ヒープ
 *	@param	draw_type		描画タイプ 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverFontSetUpGraphicTypeNormal( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment;
	int sex;
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );

	// 性別取得
	sex = ZKN_GLBDATA_SaveData_SexGet( cp_glb->p_glb, monsno, draw_type );
	GF_ASSERT( sex != ZUKAN_WORK_GET_SEX_ERR );
	
	switch( sex ){
	case PARA_MALE:
		comment = ZNK_ZUKAN_GRAPH_00;
		break;
		
	case PARA_FEMALE:
		comment = ZNK_ZUKAN_GRAPH_01;
		break;
		
	default:
		GF_ASSERT(0);		// おかしい
		break;
	}
	
	return comment;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画タイプ文字列の描画	描画タイプ　男のみ
 *
 *	@param	p_drawglb		描画グローバル
 *	@param	draw_type		描画タイプ 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverFontSetUpGraphicTypeManOnly( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment;

	comment = ZNK_ZUKAN_GRAPH_00;

	return comment;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画タイプ文字列の描画	描画タイプ　女のみ
 *
 *	@param	p_drawglb		描画グローバル
 *	@param	draw_type		描画タイプ 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverFontSetUpGraphicTypeGirlOnly( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment;

	comment = ZNK_ZUKAN_GRAPH_01;
	return comment;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画タイプ文字列の描画	描画タイプ　不明のみ
 *
 *	@param	p_drawglb		描画グローバル
 *	@param	draw_type		描画タイプ 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverFontSetUpGraphicTypeUnknownOnly( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment = ZNK_ZUKAN_GRAPH_08;

	return comment;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画タイプ文字列の描画	描画タイプ　ミノムシ
 *
 *	@param	p_drawglb		描画グローバル
 *	@param	draw_type		描画タイプ 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverFontSetUpGraphicTypeMinomutti( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment;
	int form = ZKN_GLBDATA_SaveData_MinomuttiFormGet( cp_glb->p_glb, draw_type );

	comment = ZNK_ZUKAN_GRAPH_04 + form;
	return comment;
}

static int ZknZukanGraverFontSetUpGraphicTypeMinomesu( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment;
	int form = ZKN_GLBDATA_SaveData_MinomesuFormGet( cp_glb->p_glb, draw_type );

	comment = ZNK_ZUKAN_GRAPH_04 + form;

	return comment;
}

static int ZknZukanGraverFontSetUpGraphicTypeSiiusi( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment;
	int form = ZKN_GLBDATA_SaveData_SiiusiFormGet( cp_glb->p_glb, draw_type );

	comment = ZNK_ZUKAN_GRAPH_02 + form;

	return comment;
}

static int ZknZukanGraverFontSetUpGraphicTypeSiidorugo( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment;
	int form = ZKN_GLBDATA_SaveData_SiidorugoFormGet( cp_glb->p_glb, draw_type );

	comment = ZNK_ZUKAN_GRAPH_02 + form;

	return comment;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画タイプ文字列の描画	描画タイプ　アンノーン
 *
 *	@param	p_drawglb		描画グローバル
 *	@param	draw_type		描画タイプ 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverFontSetUpGraphicTypeAnnoon( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment = ZNK_ZUKAN_GRAPH_07;

	return comment;
}

//----------------------------------------------------------------------------
/**
 *	@brief	デオキシスコメントを取得
 *
 *	@param	p_drawglb		描画グローバル
 *	@param	cp_glb			グローバルデータ
 *	@param	draw_type		描画タイプ 
 *
 *	@return	コメントデータ
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverFontSetUpGraphicTypeDeokisisu( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment;
	int form = ZKN_GLBDATA_SaveData_DeokisisuFormGet( cp_glb->p_glb, draw_type );

	comment = ZKN_DNA_00 + form;
	return comment;
}

//----------------------------------------------------------------------------
/**
 *	@brief	バッファインデックスとその中のインデックスから
 *			実際のポケモン描画インデックスを取得する
 *
 *	@param	buff_idx		バッファIDX
 *	@param	idx				IDX
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static inline int ZknZukanGraverGetBuffIdx_PokeGraIdx( int buff_idx, int idx )
{
	if( buff_idx == ZKN_ZUKANGRAVER_GRA_NOW_DRAW_01 ){
		// 今表示 01 次23
		return idx;	
	}
	
	// 今表示23 次01
	idx -= ZKN_ZUKANGRAVER_GRA_FRONT_NEXT;	
	if( idx < 0 ){
		idx += ZKN_ZUKANGRAVER_GRA_NUM;
	}
	return idx;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック座標取得
 *
 *	@param	idx			インデックス
 * 
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraMatGet( int idx, int* x, int* y )
{
	int set_x = 0;
	int set_y = 0;
	
	switch( idx ){
	case ZKN_ZUKANGRAVER_GRA_BACK:			// 今の後ろの絵
		set_x = ZKN_ZUKANGRAVER_GRA_DRAW_BACK_X_OFS;
		
	case ZKN_ZUKANGRAVER_GRA_FRONT:			// 今の表の絵
		set_x += ZKN_ZUKANGRAVER_GRA_DRAW_FRONT_X;
		set_y = ZKN_ZUKANGRAVER_GRA_DRAW_Y;
		break;
		
	case ZKN_ZUKANGRAVER_GRA_BACK_NEXT:		// 次の後ろの絵
		set_x = ZKN_ZUKANGRAVER_GRA_DRAW_BACK_X_OFS;
		
	case ZKN_ZUKANGRAVER_GRA_FRONT_NEXT:		// 次の表の絵
		set_x += ZKN_ZUKANGRAVER_GRA_DRAW_FRONT_NEXT_X;
		set_y = ZKN_ZUKANGRAVER_GRA_DRAW_Y;
		break;

	default:
		GF_ASSERT(0);
		break;
	}

	*x = set_x;
	*y = set_y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	GMMこめんとIDX取得
 *
 *	@param	p_drawglb		描画グローバル
 *	@param	draw_type_flag	描画タイプフラグ
 *	@param	draw_type		描画タイプ
 *
 *	@return	GMMIDX
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverFontGet(ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type_flag, int draw_type)
{
	int comment;

	switch( draw_type_flag ){
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_NORMAL:	// 通常描画タイプ
		comment = ZknZukanGraverFontSetUpGraphicTypeNormal( p_drawglb, cp_glb, draw_type );
		break;
		
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MANONLY:		// オスのみ描画タイプ
		comment = ZknZukanGraverFontSetUpGraphicTypeManOnly( p_drawglb, cp_glb, draw_type );
		break;
		
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_GIRLONLY:		// メスのみ描画タイプ
		comment = ZknZukanGraverFontSetUpGraphicTypeGirlOnly( p_drawglb, cp_glb, draw_type );
		break;
		
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWNONLY:	// 不明のみ描画タイプ
		comment = ZknZukanGraverFontSetUpGraphicTypeUnknownOnly( p_drawglb, cp_glb, draw_type );
		break;
		
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MINOMUTTI:	// ミノムっチ描画タイプ
		comment = ZknZukanGraverFontSetUpGraphicTypeMinomutti( p_drawglb, cp_glb, draw_type );
		break;

	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MINOMESU:	// ミノメス描画タイプ
		comment = ZknZukanGraverFontSetUpGraphicTypeMinomesu( p_drawglb, cp_glb, draw_type );
		break;
		
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_SIIUSI:		// シーウシ描画タイプ
		comment = ZknZukanGraverFontSetUpGraphicTypeSiiusi( p_drawglb, cp_glb, draw_type );
		break;

	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_SIIDORUGO:	// シードルゴ描画タイプ
		comment = ZknZukanGraverFontSetUpGraphicTypeSiidorugo( p_drawglb, cp_glb, draw_type );
		break;

	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWN_POKE:		// アンノーン描画タイプ
		comment = ZknZukanGraverFontSetUpGraphicTypeAnnoon( p_drawglb, cp_glb, draw_type );
		break;

	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_DEOKISISU_POKE:
		comment = ZknZukanGraverFontSetUpGraphicTypeDeokisisu( p_drawglb, cp_glb, draw_type );
		break;

	default:
		break;
	}

	return comment;
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAMの破棄
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverFontOamDelete( ZKN_ZUKANGRAVER_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_GRAPHIC_BUTTONFONT_NUM; i++ ){
		ZKN_FONTOAM_Delete( p_draw->p_pokegra_font[ i ] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	グラフィックバージョンアイコン描画アニメ　スタート
 *
 *	@param	p_draw	描画ワーク 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverIconDrawAnm_S( ZKN_ZUKANGRAVER_DRAW* p_draw )
{
	CLACT_SetDrawFlag( p_draw->next_icon, FALSE );

	p_draw->icon_draw_s_time = ZKN_GRAPHIC_MOVE_ICON_OFF_SYNC;
	p_draw->icon_draw_flag = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	グラフィックバーションアイコン描画ONアニメ　メイン
 *
 *	@param	p_draw 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverIconDrawAnm_Main( ZKN_ZUKANGRAVER_DRAW* p_draw )
{
	if( p_draw->icon_draw_flag ){
		
		p_draw->icon_draw_s_time --;

		if( p_draw->icon_draw_s_time <= 0 ){
			CLACT_SetDrawFlag( p_draw->next_icon, TRUE );
			p_draw->icon_draw_flag = FALSE;
		}
	}
}

