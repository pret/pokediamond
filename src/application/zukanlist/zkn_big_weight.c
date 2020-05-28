//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_big_weight.c
 *	@brief		図鑑大きさ比べ　重さ比べ
 *	@author		tomoya takahashi 
 *	@data		2006.02.16
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"

#include "include/gflib/calctool.h"
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
#include "include/msgdata/msg_zkn.h"
#include "include/poketool/pokeicon.h"
#include "include/system/palanm.h"


#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_zukan_common.h"


#define	__ZKN_BIG_WEIGHT_H_GLOBAL
#include "include/application/zukanlist/zkn_big_weight.h"

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
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define ZKN_BIG_WE_EVENT_NUM ( 0 )	// イベント数
//#define ZKN_BIG_WE_EVENT_CHANGE_ZUKAN	(0x1 << 1)	// 図鑑へ

#define ZKN_BIG_WE_OAM_BG_PRI	( 3 )
#define ZKN_BIG_WE_OAMDAI_BG_PRI	( 1 )
#define ZKN_BIG_WE_OAM_PRI	( 31 )

// フェード用
#define ZKN_BIG_WE_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

//-------------------------------------
//	シーケンス
//=====================================
enum{
	ZKN_BIG_WE_SEQINIT_ALLOC,
	ZKN_BIG_WE_SEQINIT_LOAD,
	ZKN_BIG_WE_SEQINIT_FADEIN,
	ZKN_BIG_WE_SEQINIT_END,
};
enum{
	ZKN_BIG_WE_SEQDELETE_FADEOUT_INIT,
	ZKN_BIG_WE_SEQDELETE_FADEOUT,
	ZKN_BIG_WE_SEQDELETE_RELEASE,
	ZKN_BIG_WE_SEQDELETE_FREE,
	ZKN_BIG_WE_SEQDELETE_END,
};

// 確保文字列バッファサイズ
#define ZKN_BIG_WE_WEIGHT_NUM_STR	( 32 )

// 文字列描画位置
#define ZKN_BIG_WE_WEIGHT_TITLE_X	( 96 )		// タイトル
#define ZKN_BIG_WE_WEIGHT_TITLE_Y	( 24 )
#define ZKN_BIG_WE_WEIGHT_TAKASA_Y	( 168 )		// "高さ"
#define ZKN_BIG_WE_WEIGHT_TAKASA1_X	( 32 )
#define ZKN_BIG_WE_WEIGHT_TAKASA2_X	( 152 )
#define ZKN_BIG_WE_WEIGHT_NUM_OFS_X	( 32 )	// 実際の値を表示する高さからの位置
#define ZKN_BIG_WE_WEIGHT__M__OFS_X	( 30 )	// Mを表示する値からの位置
#define ZKN_BIG_WE_WEIGHT_NAME_Y		( 152 )
#define ZKN_BIG_WE_WEIGHT_MONSNAME_X	( 24 )
#define ZKN_BIG_WE_WEIGHT_HERO_X		( 146 )

// 主人公基本表示位置
#define ZKN_BIG_WE_WEIGHT_HERO_DEF_X	( 184 )
#define ZKN_BIG_WE_WEIGHT_HERO_DEF_Y	( 64 )
#define ZKN_BIG_WE_WEIGHT_HERO_ANM_SEQ_MAN		( 3 )
#define ZKN_BIG_WE_WEIGHT_HERO_ANM_SEQ_GIRL	( 4 )


// ポケモングラフィック
#define ZKN_BIG_WE_WEIGHT_POKEGRA_DEF_X	( 72 )
#define ZKN_BIG_WE_WEIGHT_POKEGRA_DEF_Y	( ZKN_BIG_WE_WEIGHT_HERO_DEF_Y )

//　天秤データ
#define ZKN_BIG_WE_TENBIN_MAT_X		( 128 )	// 中心
#define ZKN_BIG_WE_TENBIN_MAT_Y		( 96 )	// 中心
#define ZKN_BIG_WE_TENBIN_SIZ_X		( 128 )	
#define ZKN_BIG_WE_TENBIN_SIZ_Y		( 16 )
#define ZKN_BIG_WE_TENBIN_SWSP_PLTT	( 0 )
#define ZKN_BIG_WE_TENBIN_DAI_MAT_OFS_Y	( 10 )
#define ZKN_BIG_WE_TENBIN_DAI_MAT_ANM_SEQ	( 1 )
#define ZKN_BIG_WE_TENBIN_SARA_MAT_OFS_Y	( 24 )
#define ZKN_BIG_WE_TENBIN_SARA_MAT_ANM_SEQ	( 0 )

#define ZKN_BIG_WE_TENBIN_OBJ_DIS_X	( 56 )	// 天秤の中心から主人公までの距離


// ぐらぐらアニメ
#define ZKN_BIG_WE_TENBIN_GURAGURA_ANM_COUNT		( 2 )
#define ZKN_BIG_WE_TENBIN_GURAGURA_ANM_ST_ROTA		( FX_GET_ROTA_NUM(0) )
#define ZKN_BIG_WE_TENBIN_GURAGURA_ANM_AD_ROTA		( FX_GET_ROTA_NUM(1) )
#define ZKN_BIG_WE_TENBIN_GURAGURA_ANM_00_TARGET	( -FX_GET_ROTA_NUM(3) )
#define ZKN_BIG_WE_TENBIN_GURAGURA_ANM_01_TARGET	( FX_GET_ROTA_NUM(3) )
#define ZKN_BIG_WE_TENBIN_GURAGURA_ANM_02_TARGET	( FX_GET_ROTA_NUM(0) )

// ジャンプアニメ
#define ZKN_BIG_WE_JUMP_ANIME_G	( 1 )
#define ZKN_BIG_WE_JUMP_SHAKE_X		( 2*FX32_ONE )
#define ZKN_BIG_WE_JUMP_SHAKE_WAIT	( 1 )
#define ZKN_BIG_WE_JUMP_SHAKE_GET_NUM_DIV	( 2 )


// 主人公の重さ
#define ZKN_BIG_WE_MAN_GRAM	( 380 )
#define ZKN_BIG_WE_GIRL_GRAM	( 340 )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------

//-------------------------------------
//	アニメデータ
//=====================================
typedef struct {
	int		dis;				// 重さの差終了
	BOOL	guragura_flag;		// グラグラアニメフラグ
	u16		rota_add;			// 回転速度
	u16		rota_end;			// 回転終了
	BOOL	jump_flag;			// ジャンプアニメフラグ
	int		jump_num;			// ジャンプ初速度
} ZKN_BIG_WE_ANIME_DATA;
#define ZKN_BIG_WE_ANIME_NUM	( 17 )
#define ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(x)	( (x) * 128 )
#define ZKN_BIG_WE_ANIME_ROTA_END_ONE(x)	( FX_GET_ROTA_NUM(1) * (x) )
const static ZKN_BIG_WE_ANIME_DATA ZknBigWeAnime[ ZKN_BIG_WE_ANIME_NUM ] = {
	{	
		0, TRUE,
		ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(1), ZKN_BIG_WE_ANIME_ROTA_END_ONE(0),
		FALSE, 0
	},
	{	
		10, TRUE,
		ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(1), ZKN_BIG_WE_ANIME_ROTA_END_ONE(4),
		FALSE, 0
	},
	{	
		20, TRUE,
		ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(1), ZKN_BIG_WE_ANIME_ROTA_END_ONE(3),
		FALSE, 0
	},
	{	
		30, TRUE,
		ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(1), ZKN_BIG_WE_ANIME_ROTA_END_ONE(4),
		FALSE, 0
	},
	{	
		40, TRUE,
		ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(1), ZKN_BIG_WE_ANIME_ROTA_END_ONE(5),
		FALSE, 0
	},
	{	
		50, FALSE,
		ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(1), ZKN_BIG_WE_ANIME_ROTA_END_ONE(6),
		FALSE, 0
	},
	{	
		60, FALSE,
		ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(1), ZKN_BIG_WE_ANIME_ROTA_END_ONE(7),
		FALSE, 0
	},
	{	
		70, FALSE,
		ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(1), ZKN_BIG_WE_ANIME_ROTA_END_ONE(8),
		FALSE, 0
	},
	{	
		150, FALSE,
		ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(1), ZKN_BIG_WE_ANIME_ROTA_END_ONE(15),
		FALSE, 0
	},
	{	
		300, FALSE,
		ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(2), ZKN_BIG_WE_ANIME_ROTA_END_ONE(15),
		FALSE, 0
	},
	{	
		500, FALSE,
		ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(3), ZKN_BIG_WE_ANIME_ROTA_END_ONE(15),
		FALSE, 0
	},
	{	
		750, FALSE,
		ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(4), ZKN_BIG_WE_ANIME_ROTA_END_ONE(15),
		FALSE, 0
	},
	{	
		1050, FALSE,
		ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(5), ZKN_BIG_WE_ANIME_ROTA_END_ONE(15),
		TRUE, 0
	},
	{	
		1550, FALSE,
		ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(6), ZKN_BIG_WE_ANIME_ROTA_END_ONE(15),
		TRUE, -2
	},
	{	
		2350, FALSE,
		ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(7), ZKN_BIG_WE_ANIME_ROTA_END_ONE(15),
		TRUE, -4
	},
	{	
		3500, FALSE,
		ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(8), ZKN_BIG_WE_ANIME_ROTA_END_ONE(15),
		TRUE, -8
	},
	{	
		0xffff, FALSE,
		ZKN_BIG_WE_ANIME_ROTA_ADD_ONE(9), ZKN_BIG_WE_ANIME_ROTA_END_ONE(15),
		TRUE, -16
	},
};








//-------------------------------------
//	大きさ比べ画面　グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DATA*		p_glb;				// グローバルデータ

	// メインコモングローバル
	ZKN_APL_DATA*	p_main_common;	// アプリデータ
} ZKN_BIG_WE_GLB;

//-------------------------------------
//	大きさ比べ画面	描画グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// 描画グローバルデータ

	SWSP_CHAR_PTR swsp_char;
	SWSP_PLTT_PTR swsp_pltt;
	SWSP_OBJ_PTR  swsp_obj;
	void* swsp_char_buff;
	void* swsp_pltt_buff;
	NNSG2dCharacterData* p_chardata;
	NNSG2dPaletteData* p_plttdata;

} ZKN_BIG_WE_DRAWGLB;

//-------------------------------------
//	大きさ比べ画面　内部ワーク
//=====================================
typedef struct {
	int gram_dis;
	int omoi_flag;	// 0主人公 1ポケモン
} ZKN_BIG_WE_WORK;



//-------------------------------------
//	ぐらぐらアニメタスク構造体
//=====================================
typedef struct {
	SWSP_OBJ_PTR	ten_bou_obj;
	CLACT_WORK_PTR	ten_sara_hero;
	CLACT_WORK_PTR	ten_sara_poke;
	CLACT_WORK_PTR	hero;
	CLACT_WORK_PTR	poke;
	
	int way;
	int count;
	int now_rota;
	int add_rota;
	int target_rota;
	int set_seq;
	int seq;
	BOOL* anm_end;
} ZKN_BIG_WE_GURAGURA;

//-------------------------------------
//	天秤アニメタスク構造体
//=====================================
typedef struct {
	SWSP_OBJ_PTR	ten_bou_obj;
	CLACT_WORK_PTR	ten_sara_hero;
	CLACT_WORK_PTR	ten_sara_poke;
	CLACT_WORK_PTR	hero;
	CLACT_WORK_PTR	poke;
	
	int now_rota;
	int add_rota;
	int target_rota;
	BOOL* anm_end;
} ZKN_BIG_WE_TENBIN;

//-------------------------------------
//	オブジェクトジャンプ構造体
//=====================================
typedef struct {
	CLACT_WORK_PTR obj;

	fx32 now_x;
	fx32 now_y;
	s16 vo;		// 初速度
	int count_max;
	int count;

	int seq;
	BOOL* anm_end;
} ZKN_BIG_WE_JUMP;



//-------------------------------------
//	大きさ比べ画面　内部ワーク
//=====================================
typedef struct {
	CLACT_WORK_PTR hero;
	CLACT_WORK_PTR poke;
	CLACT_WORK_PTR tenbin_dai;
	CLACT_WORK_PTR tenbin_sara[2];

	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// Resourceオブジェポインタ
	CLACT_U_RES_OBJ_PTR res_obj_main[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// Resourceオブジェポインタ



	const ZKN_BIG_WE_ANIME_DATA* p_anime;	// 反映アニメ
	int way;		// ポケモンか主人公か
	
	// アニメTCBデータ
	TCB_PTR tcb;
	ZKN_BIG_WE_GURAGURA gragra_anm;
	ZKN_BIG_WE_TENBIN tenbin_anm;
	ZKN_BIG_WE_JUMP jump_anm;
	BOOL anm_end;


	// パレットフェード用バッファ
	u16* pal_fade_buff;
	u16* pal_fade_buff_main;
} ZKN_BIG_WE_DRAW;



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
static ZKN_BIG_WE_GLB* MakeBigWeGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_BIG_WE_DRAWGLB* MakeBigWeDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
//static ZKN_EVENT_DATA* MakeBigWeEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteBigWeGlb( ZKN_BIG_WE_GLB* p_glb );
static void DeleteBigWeDrawGlb( ZKN_BIG_WE_DRAWGLB* p_glb );
//static void DeleteBigWeEvent( ZKN_EVENT_DATA* p_event );


static int BigWeEventDataNumGet( void );

//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
static int ZknBigWeProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigWeProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigWeProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigWeProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknBigWeProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknBigWeProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

// フェード処理
static void ZknBigWeOamFadeInit( ZKN_BIG_WE_DRAW* p_draw );
static void ZknBigWeOamFadeDelete( ZKN_BIG_WE_DRAW* p_draw );
static void ZknBigWeFadeInit( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb, const ZKN_BIG_WE_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknBigWeFadeMain( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb, const ZKN_BIG_WE_GLB* cp_glb, BOOL fadein_out );

// 読み込み処理
static void ZknBigWeLoadRes( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb, const ZKN_BIG_WE_GLB* cp_glb, const ZKN_BIG_WE_WORK* cp_datawork, int heap );
static void ZknBigWeDeleteRes( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb );
static void ZknBigWeSetUpBg( ZKN_BIG_WE_DRAWGLB* p_drawglb, const ZKN_BIG_WE_GLB* cp_glb, int heap );
static void ZknBigWeOamResLoad(  ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb, const ZKN_BIG_WE_GLB* cp_glb, int heap );
static void ZknBigWeOamResDelete( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb );
static void ZknBigWeOamInit( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb, const ZKN_BIG_WE_GLB* cp_glb, int heap );
static void ZknBigWeOamDelete( ZKN_BIG_WE_DRAW* p_draw );
static void ZknBigWeFontOamInit( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb, const ZKN_BIG_WE_GLB* cp_glb, int heap );
static void ZknBigWeFontOamDelete( ZKN_BIG_WE_DRAW* p_draw );
static void ZknBigWeSetUpFontBgNormal( ZKN_BIG_WE_DRAWGLB* p_drawglb, int heap );
static void ZknBigWeSetUpFontBgHeroPokeData( ZKN_BIG_WE_DRAWGLB* p_drawglb, const ZKN_BIG_WE_GLB* cp_glb, int heap );

static void ZknBigWeSWSPResLoad( ZKN_BIG_WE_DRAWGLB* p_drawglb, int heap );
static void ZknBigWeSWSPResDelete( ZKN_BIG_WE_DRAWGLB* p_drawglb );
static void ZknBigWeSWSPAdd( ZKN_BIG_WE_DRAWGLB* p_drawglb, int heap );
static void ZknBigWeSWSPDelete( ZKN_BIG_WE_DRAWGLB* p_drawglb );

// アニメテーブル選択
static const ZKN_BIG_WE_ANIME_DATA* ZknBigWeAnimeTblGet( const ZKN_BIG_WE_ANIME_DATA* p_arry, int num,  int dis );

// 動作部分
// 回転角からグラフィックデータ更新
static void ZknBinWeTenbinAnmObjDataSet( SWSP_OBJ_PTR ten_bou, CLACT_WORK_PTR tenbin_sara_hero, CLACT_WORK_PTR tenbin_sara_poke, CLACT_WORK_PTR hero, CLACT_WORK_PTR poke, u16 rota );

// アニメタスク
static void ZknBigWeGuraGuraAnimeReq( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb, int way );
static void ZknBigWeGuraGuraTcb( TCB_PTR tcb, void* work );
static void ZknBigWeGuraGuraAnimeCalc( ZKN_BIG_WE_GURAGURA* p_ggw );

static void ZknBigWeTenbinAnimeReq( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb, u16 add_num, u16 end_num, int way );
static void ZknBigWeTenbinAnimeTcb( TCB_PTR tcb, void* work );

static void ZknBigWeJumpAnimeReq( ZKN_BIG_WE_DRAW* p_draw, s16 jump_num, int way );
static void ZknBigWeJumpAnimeTcb( TCB_PTR tcb, void* work );

//　パレットフェード
static void ZknBigWePalFadeSet( ZKN_BIG_WE_DRAW* p_draw, u8 evy, u16 next_rgb );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　アプリ作成
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
void ZKN_BigWeAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_BIG_WE_GLB*	p_glb;
	ZKN_BIG_WE_DRAWGLB*	p_drawglb;
//	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeBigWeGlb( heap, zkn_sys );
	p_drawglb = MakeBigWeDrawGlb( heap, zkn_sys );
//	p_event = MakeBigWeEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= NULL;
//	p_data->p_event_data	= p_event;
	p_data->event_num		= BigWeEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknBigWeProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknBigWeProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknBigWeProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknBigWeProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknBigWeProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknBigWeProcDrawFuncDelete;
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
void ZKN_BigWeAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteBigWeGlb( p_data->p_glb_data ); 
	DeleteBigWeDrawGlb( p_data->p_glb_draw ); 
//	DeleteBigWeEvent( p_data->p_event_data );
}



//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_BIG_WE_GLB* MakeBigWeGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_BIG_WE_GLB* p_glb;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_BIG_WE_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_BIG_WE_GLB) );


	// グローバルデータ
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	// めいんグローバルアプリデータ取得
	p_glb->p_main_common = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_COMMON );
	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画グローバル作成
 *
 *	@param	heap	ヒープ
 *	@param	zkn_sys	図鑑システム
 *
 *	@return	作成データ
 */
//-----------------------------------------------------------------------------
ZKN_BIG_WE_DRAWGLB* MakeBigWeDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_BIG_WE_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_BIG_WE_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_BIG_WE_DRAWGLB) );

	// 描画データ
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	// SWSP
	ZknBigWeSWSPResLoad( p_glb, heap );
	ZknBigWeSWSPAdd( p_glb, heap );

	// ソフトウェアスプライト描画OFF
	SWSP_SetSpriteDraw( p_glb->swsp_obj, FALSE );


	return p_glb;
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　イベント作成
 *
 *	@param	heap		使用するヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	イベントデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeBigWeEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = BigWeEventDataNumGet();

	// イベントデータテーブル作成
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	MakeBigWeChangeZukan( heap, &p_event_tbl[0], zkn_sys );

	return p_event_tbl;
}
#endif
//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteBigWeGlb( ZKN_BIG_WE_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteBigWeDrawGlb( ZKN_BIG_WE_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );

	// SWSP
	ZknBigWeSWSPResDelete( p_glb );
	ZknBigWeSWSPDelete( p_glb );

	
	sys_FreeMemoryEz( p_glb );
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　イベントデータ破棄
 *
 *	@param	p_event	イベントデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteBigWeEvent( ZKN_EVENT_DATA* p_event )
{
	GF_ASSERT( p_event );
	
	DeleteBigWeChangeZukan( &p_event[0] );

	sys_FreeMemoryEz( p_event );
}
#endif


//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソートアプリ　イベント数取得
 *	
 *	@param	none	
 *
 *	@return	検索ソートアプリ　イベント数
 *
 *
 */
//-----------------------------------------------------------------------------
static int BigWeEventDataNumGet( void )
{
	return ZKN_BIG_WE_EVENT_NUM;
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
static int ZknBigWeProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_BIG_WE_GLB* p_glb = p_glbdata;
	ZKN_BIG_WE_WORK* p_work;
	int poke_gram;
	int hero_gram;
	int monsno;
	
	// ワーク作成
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_BIG_WE_WORK) );
	GF_ASSERT( p_work );
	memset( p_work, 0, sizeof(ZKN_BIG_WE_WORK) );
	p_dodata->p_work = p_work;

	monsno = ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb );
	
	// 重さの差を計算
	poke_gram = ZKN_HEIGHTGRAM_GetGram( p_glb->p_glb->height_gram, monsno );
	if( ZKN_GLBDATA_HeroSexGet( p_glb->p_glb ) == 0 ){
		hero_gram = ZKN_BIG_WE_MAN_GRAM;
	}else{
		hero_gram = ZKN_BIG_WE_GIRL_GRAM;
	}

	if( poke_gram >= hero_gram ){
		p_work->gram_dis = poke_gram - hero_gram;
		p_work->omoi_flag = 1;
	}else{
		p_work->gram_dis = hero_gram - poke_gram;
		p_work->omoi_flag = 0;
	}

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
static int ZknBigWeProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_BIG_WE_GLB* p_glb = p_glbdata;
	ZKN_BIG_WE_WORK*	p_work = p_dodata->p_work;
	
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
static int ZknBigWeProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_BIG_WE_GLB* p_glb = p_glbdata;
	ZKN_BIG_WE_WORK*	p_work = p_dodata->p_work;

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
static int ZknBigWeProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_WE_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_WE_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_WE_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_BIG_WE_DRAW* p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_BIG_WE_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_BIG_WE_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_BIG_WE_DRAW) );
		p_drawwork = p_drawdata->p_work;
		p_drawwork->anm_end = TRUE;

		p_drawdata->seq++;
		break;
		
	case ZKN_BIG_WE_SEQINIT_LOAD:
		ZknBigWeLoadRes( p_drawwork, p_drawglb, cp_dataglb, cp_datawork, p_drawdata->heap );

		// フェード初期化
		ZknBigWeFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIG_WE_SEQINIT_FADEIN:
		if( ZknBigWeFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_BIG_WE_SEQINIT_END:

		// 適応するアニメ設定
		p_drawwork->p_anime = ZknBigWeAnimeTblGet( ZknBigWeAnime, ZKN_BIG_WE_ANIME_NUM, cp_datawork->gram_dis );
		p_drawwork->way		= cp_datawork->omoi_flag;	
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
static int ZknBigWeProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_WE_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_WE_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_WE_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_BIG_WE_DRAW* p_drawwork = p_drawdata->p_work;


	switch( p_drawdata->seq ){
	case 0:		// ぐらぐらアニメ入れるかチェック
		p_drawwork->anm_end = TRUE;
		if( p_drawwork->p_anime->guragura_flag ){
			p_drawdata->seq  = 1;	// グラグラアニメへ
		}else{
			p_drawdata->seq  = 3;	// 天秤アニメへ
		}
		break;

	case 1:		// ぐらぐらアニメ
		ZknBigWeGuraGuraAnimeReq( p_drawwork, p_drawglb, p_drawwork->way );
		p_drawdata->seq ++;
		break;

	case 2:		// ぐらぐらアニメ終了チェック
		if( p_drawwork->anm_end == TRUE ){
			p_drawdata->seq ++;
		}
		break;

	case 3:		// 天秤アニメ
		ZknBigWeTenbinAnimeReq( p_drawwork, p_drawglb, p_drawwork->p_anime->rota_add, p_drawwork->p_anime->rota_end, p_drawwork->way );
		p_drawdata->seq ++;
		break;

	case 4:		// 天秤アニメ終了フラグ
		if( p_drawwork->anm_end == TRUE ){
			p_drawdata->seq ++;
		}
		break;

	case 5:		// ジャンプアニメ開始チェック
		if( p_drawwork->p_anime->jump_flag ){
			ZknBigWeJumpAnimeReq( p_drawwork, p_drawwork->p_anime->jump_num, p_drawwork->way );
			p_drawdata->seq ++;
		}else{
			p_drawdata->seq = 7;
		}
		break;

	case 6:		// ジャンプアニメ終了チェック
		if( p_drawwork->anm_end == TRUE ){
			p_drawdata->seq ++;
		}
		break;

	case 7:		// 終了待ち
		break;
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
static int ZknBigWeProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_WE_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_WE_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_WE_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_BIG_WE_DRAW* p_drawwork = p_drawdata->p_work;


	switch( p_drawdata->seq ){
	case ZKN_BIG_WE_SEQDELETE_FADEOUT_INIT:
		ZknBigWeFadeInit( p_drawwork, p_drawglb, cp_glbdata, FALSE );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIG_WE_SEQDELETE_FADEOUT:
		if( ZknBigWeFadeMain( p_drawwork, p_drawglb, cp_glbdata, FALSE ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_BIG_WE_SEQDELETE_RELEASE:
		ZknBigWeDeleteRes( p_drawwork, p_drawglb );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_BIG_WE_SEQDELETE_FREE:

		// TCBがあったら破棄
		if( p_drawwork->anm_end == FALSE ){
			TCB_Delete( p_drawwork->tcb );
		}
		
		sys_FreeMemoryEz(p_drawdata->p_work);
		p_drawdata->p_work = NULL;
		p_drawdata->seq++;
		break;
		
		
	case ZKN_BIG_WE_SEQDELETE_END:
		return ZKN_PROC_TRUE;
	}

	return ZKN_PROC_FALSE;
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
static void ZknBigWeOamFadeInit( ZKN_BIG_WE_DRAW* p_draw )
{
/*	CLACT_ObjModeSet( p_draw->hero, GX_OAM_MODE_XLU );
	CLACT_ObjModeSet( p_draw->poke, GX_OAM_MODE_XLU );
	CLACT_ObjModeSet( p_draw->tenbin_dai, GX_OAM_MODE_XLU );
	CLACT_ObjModeSet( p_draw->tenbin_sara[0], GX_OAM_MODE_XLU );
	CLACT_ObjModeSet( p_draw->tenbin_sara[1], GX_OAM_MODE_XLU );//*/
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
static void ZknBigWeOamFadeDelete( ZKN_BIG_WE_DRAW* p_draw )
{
/*	CLACT_ObjModeSet( p_draw->hero, GX_OAM_MODE_NORMAL );
	CLACT_ObjModeSet( p_draw->poke, GX_OAM_MODE_NORMAL );
	CLACT_ObjModeSet( p_draw->tenbin_dai, GX_OAM_MODE_NORMAL );
	CLACT_ObjModeSet( p_draw->tenbin_sara[0], GX_OAM_MODE_NORMAL );
	CLACT_ObjModeSet( p_draw->tenbin_sara[1], GX_OAM_MODE_NORMAL );//*/
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
static void ZknBigWeFadeInit( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb, const ZKN_BIG_WE_GLB* cp_glb, BOOL fadein_out )
{
	// 半透明OAM設定
	ZknBigWeOamFadeInit( p_draw );

	// ブライトネス処理を行ってよいか
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_BIG_WE_FADE_PLANEMSK, 0, ZKN_UTIL_FADE_MAIN );

			// フェード設定
			ZknBigWePalFadeSet( p_draw, -ZKN_GLB_GetFadeBrightness( &p_drawglb->p_drawglb->fade ), 0 );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_BIG_WE_FADE_PLANEMSK, 0, ZKN_UTIL_FADE_MAIN );
		}
	}
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
static BOOL ZknBigWeFadeMain( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb, const ZKN_BIG_WE_GLB* cp_glb, BOOL fadein_out )
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
			ZknBigWeOamFadeDelete( p_draw );
		}

		return TRUE;
	}else{

		// フェード
		ZknBigWePalFadeSet( p_draw, -ZKN_GLB_GetFadeBrightness( &p_drawglb->p_drawglb->fade ), 0 );
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
static void ZknBigWeLoadRes( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb, const ZKN_BIG_WE_GLB* cp_glb, const ZKN_BIG_WE_WORK* cp_datawork, int heap )
{
	// BG設定
	ZknBigWeSetUpBg( p_drawglb, cp_glb, heap );

	// フォントBG設定
	ZknBigWeSetUpFontBgNormal( p_drawglb, heap );	// 共通の文字列
	ZknBigWeSetUpFontBgHeroPokeData( p_drawglb, cp_glb, heap );	// データ

	// OAMリソース読み込み
	ZknBigWeOamResLoad( p_draw, p_drawglb, cp_glb, heap );

	// アクター登録
	ZknBigWeOamInit( p_draw, p_drawglb, cp_glb, heap );

	// FONTOAM
	ZknBigWeFontOamInit( p_draw, p_drawglb, cp_glb, heap );


	// ソフトウェアスプライト描画ON
	SWSP_SetSpriteRotZ( p_drawglb->swsp_obj, 0 );
	SWSP_SetSpriteDraw( p_drawglb->swsp_obj, TRUE );
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
static void ZknBigWeDeleteRes( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb )
{
	// FONTOAM
	ZknBigWeFontOamDelete( p_draw );
	
	// アクター破棄
	ZknBigWeOamDelete( p_draw );

	// OAMリソース破棄
	ZknBigWeOamResDelete( p_draw, p_drawglb );

	// bmp破棄
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );

	// ソフトウェアスプライト描画OFF
	SWSP_SetSpriteDraw( p_drawglb->swsp_obj, FALSE );
	SWSP_SetSpriteRotZ( p_drawglb->swsp_obj, 0 );
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
static void ZknBigWeSetUpBg( ZKN_BIG_WE_DRAWGLB* p_drawglb, const ZKN_BIG_WE_GLB* cp_glb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// キャラクタデータ転
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_main_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, 0, 0, TRUE, heap );
	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_weight_bg_main1_lzh_NSCR, TRUE, &p_scrn, heap );
	
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
 *	@brief	OAMResource読み込み
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigWeOamResLoad(  ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb, const ZKN_BIG_WE_GLB* cp_glb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	int char_id, pltt_id, cell_id, cellanm_id;
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	BOOL check;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	int form_type;

	form_type = ZKN_GLBDATA_SaveData_FirstFormGet( cp_glb->p_glb, monsno );

	char_id = PokeIconCgxArcIndexGetByMonsNumber( monsno, 0, form_type );
	pltt_id = PokeIconPalArcIndexGet();
	cell_id = PokeIconCellArcIndexGet();
	cellanm_id = PokeIconCellAnmArcIndexGet();
	
	// キャラクタデータ読み込み
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], ARC_POKEICON,
			char_id, FALSE,
			ZKN_BIG_WEIGHT_ICON_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// 転送
	CLACT_U_CharManagerSetCharModeAdjustAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], ARC_POKEICON,
			pltt_id, FALSE,
			ZKN_BIG_WEIGHT_ICON_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_BIG_WEIGHT_PLTT_LOAD, heap );
	// 転送
	check = CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	GF_ASSERT( check );

	// パレットサイズ分のバッファを作成
	{
		p_draw->pal_fade_buff = sys_AllocMemory( heap, 32 * ZKN_BIG_WEIGHT_PLTT_LOAD );
	}

	// セルデータ読み込み
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], ARC_POKEICON,
			cell_id, FALSE,
			ZKN_BIG_WEIGHT_ICON_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], ARC_POKEICON, 
			cellanm_id, FALSE,
			ZKN_BIG_WEIGHT_ICON_RES_ID,
			CLACT_U_CELLANM_RES, heap );


	// その他
	// キャラクタデータ読み込み
	p_draw->res_obj_main[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main3_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_main3_lzh_NCGR + ZKN_BIG_WEIGHT_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj_main[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj_main[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_draw->res_obj_main[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_data_oam3_NCLR, FALSE, 
			NARC_zukan_zkn_data_oam3_NCLR + ZKN_BIG_WEIGHT_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_BIG_PLTT_LOAD, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj_main[ CLACT_U_PLTT_RES ] );	

	// パレットサイズ分のバッファを作成
	{
		p_draw->pal_fade_buff_main = sys_AllocMemory( heap, 32*ZKN_BIG_PLTT_LOAD );
	}


	// セルデータ読み込み
	p_draw->res_obj_main[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main3_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_main3_lzh_NCER + ZKN_BIG_WEIGHT_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj_main[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_main3_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_main3_lzh_NANR + ZKN_BIG_WEIGHT_RES_ID,
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
static void ZknBigWeOamResDelete( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb )
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


	CLACT_U_CharManagerDelete( p_draw->res_obj_main[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_draw->res_obj_main[ CLACT_U_PLTT_RES ] );

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_obj_main[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw->res_obj_main[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_obj_main[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->res_obj_main[ CLACT_U_CELLANM_RES ] );


	// パレットフェード用ワーク破棄
	sys_FreeMemoryEz( p_draw->pal_fade_buff );
	sys_FreeMemoryEz( p_draw->pal_fade_buff_main );
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
static void ZknBigWeOamInit( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb, const ZKN_BIG_WE_GLB* cp_glb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	VecFx32				scale;
	short				ofs_y;
	short				scale_num;	
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	int form_type = ZKN_GLBDATA_SaveData_FirstFormGet( cp_glb->p_glb, monsno );

	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_main3_lzh_NCGR + ZKN_BIG_WEIGHT_RES_ID,
			NARC_zukan_zkn_data_oam3_NCLR + ZKN_BIG_WEIGHT_RES_ID, 
			NARC_zukan_zkn_data_oam_main3_lzh_NCER + ZKN_BIG_WEIGHT_RES_ID,
			NARC_zukan_zkn_data_oam_main3_lzh_NANR + ZKN_BIG_WEIGHT_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_BIG_WE_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_BIG_WE_OAM_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;

	// 主人公
	add.mat.x = ZKN_BIG_WE_WEIGHT_HERO_DEF_X << FX32_SHIFT;
	add.mat.y = (ZKN_BIG_WE_WEIGHT_HERO_DEF_Y) << FX32_SHIFT;
	p_draw->hero = CLACT_AddSimple( &add );

	if( ZKN_GLBDATA_HeroSexGet( cp_glb->p_glb ) == 0 ){
		CLACT_AnmChg( p_draw->hero, ZKN_BIG_WE_WEIGHT_HERO_ANM_SEQ_MAN );
	}else{
		CLACT_AnmChg( p_draw->hero, ZKN_BIG_WE_WEIGHT_HERO_ANM_SEQ_GIRL );
	}

	// 天秤の台
	add.mat.x = ZKN_BIG_WE_TENBIN_MAT_X << FX32_SHIFT;
	add.mat.y = (ZKN_BIG_WE_TENBIN_MAT_Y + ZKN_BIG_WE_TENBIN_DAI_MAT_OFS_Y) << FX32_SHIFT;
	p_draw->tenbin_dai = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->tenbin_dai, ZKN_BIG_WE_TENBIN_DAI_MAT_ANM_SEQ );
	CLACT_BGPriorityChg( p_draw->tenbin_dai, ZKN_BIG_WE_OAMDAI_BG_PRI);

	// 天秤の皿
	add.mat.x = ZKN_BIG_WE_WEIGHT_HERO_DEF_X << FX32_SHIFT;
	add.mat.y = (ZKN_BIG_WE_WEIGHT_HERO_DEF_Y + ZKN_BIG_WE_TENBIN_SARA_MAT_OFS_Y) << FX32_SHIFT;
	p_draw->tenbin_sara[0] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->tenbin_sara[0], ZKN_BIG_WE_TENBIN_SARA_MAT_ANM_SEQ );
	add.mat.x = ZKN_BIG_WE_WEIGHT_POKEGRA_DEF_X << FX32_SHIFT;
	add.mat.y = (ZKN_BIG_WE_WEIGHT_POKEGRA_DEF_Y + ZKN_BIG_WE_TENBIN_SARA_MAT_OFS_Y) << FX32_SHIFT;
	p_draw->tenbin_sara[1] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->tenbin_sara[1], ZKN_BIG_WE_TENBIN_SARA_MAT_ANM_SEQ );



	// ポケモンアイコン
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			CLACT_U_ResManagerGetResObjID( p_draw->res_obj[ CLACT_U_CHAR_RES ] ),
			CLACT_U_ResManagerGetResObjID( p_draw->res_obj[ CLACT_U_PLTT_RES ] ),
			CLACT_U_ResManagerGetResObjID( p_draw->res_obj[ CLACT_U_CELL_RES ] ),
			CLACT_U_ResManagerGetResObjID( p_draw->res_obj[ CLACT_U_CELLANM_RES ] ),
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_BIG_WE_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_BIG_WE_OAM_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	add.mat.x = ZKN_BIG_WE_WEIGHT_POKEGRA_DEF_X << FX32_SHIFT;
	add.mat.y = ZKN_BIG_WE_WEIGHT_POKEGRA_DEF_Y << FX32_SHIFT;
	p_draw->poke = CLACT_AddSimple( &add );
	CLACT_PaletteNoChgAddTransPlttNo( p_draw->poke, PokeIconPalNumGet( monsno, form_type, 0 ) );
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
static void ZknBigWeOamDelete( ZKN_BIG_WE_DRAW* p_draw )
{
	CLACT_Delete( p_draw->hero );
	CLACT_Delete( p_draw->poke );
	CLACT_Delete( p_draw->tenbin_dai );
	CLACT_Delete( p_draw->tenbin_sara[0] );
	CLACT_Delete( p_draw->tenbin_sara[1] );
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
static void ZknBigWeFontOamInit( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb, const ZKN_BIG_WE_GLB* cp_glb, int heap )
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
static void ZknBigWeFontOamDelete( ZKN_BIG_WE_DRAW* p_draw )
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	FONTBGのセットアップ
 *
 *	@param	p_drawglb	描画グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigWeSetUpFontBgNormal( ZKN_BIG_WE_DRAWGLB* p_drawglb, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_BIG_WE_WEIGHT_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);

	// 重さ比べ
	MSGMAN_GetString( man, ZNK_BIG_01, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_WE_WEIGHT_TITLE_X, ZKN_BIG_WE_WEIGHT_TITLE_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	// 重さ
	MSGMAN_GetString( man, ZNK_ZUKAN_02, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_WE_WEIGHT_TAKASA1_X, ZKN_BIG_WE_WEIGHT_TAKASA_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// 重さ
	MSGMAN_GetString( man, ZNK_ZUKAN_02, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_WE_WEIGHT_TAKASA2_X, ZKN_BIG_WE_WEIGHT_TAKASA_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	
	STRBUF_Delete(str);

	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン名　主人公名　高さデータ　表示
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigWeSetUpFontBgHeroPokeData( ZKN_BIG_WE_DRAWGLB* p_drawglb, const ZKN_BIG_WE_GLB* cp_glb, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_BIG_WE_WEIGHT_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_gram_dat, heap);
	int mons_no =  ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	STRBUF* monsname_str = MSGDAT_UTIL_GetMonsName( mons_no, heap );
	
	// ポケモン名
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, monsname_str, ZKN_BIG_WE_WEIGHT_MONSNAME_X, ZKN_BIG_WE_WEIGHT_NAME_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	//	ポケモンの重さ
	MSGMAN_GetString( man, mons_no, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_WE_WEIGHT_TAKASA1_X + ZKN_BIG_WE_WEIGHT_NUM_OFS_X, ZKN_BIG_WE_WEIGHT_TAKASA_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	STRBUF_Delete(monsname_str);

	MSGMAN_Delete(man);

	// 違うメッセージマネージャオープン
	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);

	// 主人公名
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, 
			ZKN_GLBDATA_HeroNameGet( cp_glb->p_glb ),
			ZKN_BIG_WE_WEIGHT_HERO_X, ZKN_BIG_WE_WEIGHT_NAME_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	
	// 主人公の重さ
	if( ZKN_GLBDATA_HeroSexGet( cp_glb->p_glb ) == 0 ){
		MSGMAN_GetString( man, ZNK_WEIGHT_00, str );
	}else{
		MSGMAN_GetString( man, ZNK_WEIGHT_01, str );
	}
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_WE_WEIGHT_TAKASA2_X + ZKN_BIG_WE_WEIGHT_NUM_OFS_X, ZKN_BIG_WE_WEIGHT_TAKASA_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	// KG
	MSGMAN_GetString( man, ZNK_ZUKAN_04, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_WE_WEIGHT_TAKASA2_X + ZKN_BIG_WE_WEIGHT_NUM_OFS_X + ZKN_BIG_WE_WEIGHT__M__OFS_X, ZKN_BIG_WE_WEIGHT_TAKASA_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	

	STRBUF_Delete(str);
	MSGMAN_Delete(man);
}


//----------------------------------------------------------------------------
/**
 *	@brief	ソフトウェアスプライトのリソース読み込み
 *
 *	@param	p_draw		描画ワーク	
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigWeSWSPResLoad(  ZKN_BIG_WE_DRAWGLB* p_drawglb, int heap )
{
	SWSP_CHARDATA char_ent;
	SWSP_PLTTDATA pltt_ent;
	
	// キャラクタデータ
	p_drawglb->swsp_char_buff = ZKN_GLBDATA_CharDataGet( 
			p_drawglb->p_drawglb, NARC_zukan_zkn_weight_ude_lzh_NCBR, TRUE,
			&p_drawglb->p_chardata, heap );
	
	// パレットデータ読み込み
	p_drawglb->swsp_pltt_buff = ZKN_GLBDATA_PalDataGet( 
			p_drawglb->p_drawglb, NARC_zukan_zkn_data_NCLR,
			&p_drawglb->p_plttdata, heap );

	// キャラクタデータ転送
	char_ent.s_sys		= p_drawglb->p_drawglb->swsp_sys;
	char_ent.res_file	= p_drawglb->p_chardata;
	p_drawglb->swsp_char = SWSP_CharLoad( &char_ent );

	// パレットデータ転送
	pltt_ent.s_sys		= p_drawglb->p_drawglb->swsp_sys;
	pltt_ent.res_file	= p_drawglb->p_plttdata;
	pltt_ent.load_num	= 16;
	p_drawglb->swsp_pltt = SWSP_PlttLoad( &pltt_ent );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ソフトウェアスプライトデータ破棄
 *
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigWeSWSPResDelete( ZKN_BIG_WE_DRAWGLB* p_drawglb )
{
	// Vramから破棄
	SWSP_CharDelete( p_drawglb->swsp_char );
	SWSP_PlttDelete( p_drawglb->swsp_pltt );


	// メモリから破棄
	sys_FreeMemoryEz( p_drawglb->swsp_char_buff );
	sys_FreeMemoryEz( p_drawglb->swsp_pltt_buff );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ソフトウェアスプライト登録
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigWeSWSPAdd( ZKN_BIG_WE_DRAWGLB* p_drawglb, int heap )
{
	SWSP_ADDDATA add;

	add.s_sys	= p_drawglb->p_drawglb->swsp_sys;
	add.p_char	= p_drawglb->swsp_char;
	add.p_pltt	= p_drawglb->swsp_pltt;


	// 登録データ格納
	add.m_x = ZKN_BIG_WE_TENBIN_MAT_X - (ZKN_BIG_WE_TENBIN_SIZ_X / 2);
	add.m_y = ZKN_BIG_WE_TENBIN_MAT_Y - (ZKN_BIG_WE_TENBIN_SIZ_Y / 2);
	add.rota = 0;
	add.alpha = 31;
	add.pri = 0;
	add.pltt_offs = ZKN_BIG_WE_TENBIN_SWSP_PLTT;

	// 登録
	p_drawglb->swsp_obj = SWSP_Add( &add );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ソフトウェアスプライト破棄
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigWeSWSPDelete( ZKN_BIG_WE_DRAWGLB* p_drawglb )
{
	// 破棄
	SWSP_Delete( p_drawglb->swsp_obj );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ぐらぐらアニメ	リクエスト
 *
 *	@param	p_draw	描画ワーク
 *	@param	way		どっちから掛けるか	主人公0 ポケモン1
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigWeGuraGuraAnimeReq( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb, int way )
{
	p_draw->gragra_anm.ten_bou_obj	 = p_drawglb->swsp_obj;
	p_draw->gragra_anm.ten_sara_hero = p_draw->tenbin_sara[0];
	p_draw->gragra_anm.ten_sara_poke = p_draw->tenbin_sara[1];
	p_draw->gragra_anm.hero = p_draw->hero;
	p_draw->gragra_anm.poke = p_draw->poke;
	p_draw->gragra_anm.seq = 0;
	p_draw->gragra_anm.anm_end = &p_draw->anm_end;
	p_draw->anm_end = FALSE;

	// 主人公から傾かせるかポケモンから傾かせるか
	if( way == 0 ){
		p_draw->gragra_anm.way	= -1;
	}else{
		p_draw->gragra_anm.way = 1;
	}

	p_draw->tcb = TCB_Add( ZknBigWeGuraGuraTcb, &p_draw->gragra_anm, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ぐらぐらアニメタスク
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigWeGuraGuraTcb( TCB_PTR tcb, void* work )
{
	ZKN_BIG_WE_GURAGURA* p_ggw = (ZKN_BIG_WE_GURAGURA*)work;
	
	switch( p_ggw->seq ){
	case 0:		//　初期化
		p_ggw->count = ZKN_BIG_WE_TENBIN_GURAGURA_ANM_COUNT;
		p_ggw->seq = 2;	// ﾌﾚｰﾑ0へ
		break;

	case 1:		// 計算シーケンス
		ZknBigWeGuraGuraAnimeCalc( p_ggw );
		break;

	case 2:		// アニメフレーム0	データ設定
		p_ggw->target_rota = ZKN_BIG_WE_TENBIN_GURAGURA_ANM_00_TARGET * p_ggw->way;
		p_ggw->add_rota = -ZKN_BIG_WE_TENBIN_GURAGURA_ANM_AD_ROTA * p_ggw->way;
		p_ggw->set_seq = 3;
		p_ggw->seq = 1;		// 計算
		ZknBigWeGuraGuraAnimeCalc( p_ggw );
		break;

	case 3:		// アニメフレーム1	データ設定
		p_ggw->target_rota = ZKN_BIG_WE_TENBIN_GURAGURA_ANM_01_TARGET * p_ggw->way;
		p_ggw->add_rota = ZKN_BIG_WE_TENBIN_GURAGURA_ANM_AD_ROTA * p_ggw->way;
		p_ggw->set_seq = 4;
		p_ggw->seq = 1;		// 計算
		ZknBigWeGuraGuraAnimeCalc( p_ggw );
		break;

	case 4:		// アニメフレーム2	データ設定
		p_ggw->target_rota = ZKN_BIG_WE_TENBIN_GURAGURA_ANM_02_TARGET * p_ggw->way;
		p_ggw->add_rota = -ZKN_BIG_WE_TENBIN_GURAGURA_ANM_AD_ROTA * p_ggw->way;
		p_ggw->seq = 1;		// 計算

		// カウントが0になったらシーケンス5にそれ以外は2に戻る
		p_ggw->count--;
		if( p_ggw->count > 0 ){
			p_ggw->set_seq = 2;
		}else{
			p_ggw->set_seq = 5;
		}
		ZknBigWeGuraGuraAnimeCalc( p_ggw );
		break;

	case 5:		// アニメ終了
		TCB_Delete( tcb );
		*p_ggw->anm_end = TRUE;
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ぐらぐらアニメ計算
 *
 *	@param	p_ggw	ワーク 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigWeGuraGuraAnimeCalc( ZKN_BIG_WE_GURAGURA* p_ggw )
{
	// 回転角計算
	if( p_ggw->add_rota < 0 ){
		if( (p_ggw->now_rota + p_ggw->add_rota) >= p_ggw->target_rota ){
			p_ggw->now_rota += p_ggw->add_rota;
		}else{
			p_ggw->now_rota = p_ggw->target_rota;
			p_ggw->seq = p_ggw->set_seq;		// 計算終了
		}
	}else{
		if( (p_ggw->now_rota + p_ggw->add_rota) <= p_ggw->target_rota ){
			p_ggw->now_rota += p_ggw->add_rota;
		}else{
			p_ggw->now_rota = p_ggw->target_rota;
			p_ggw->seq = p_ggw->set_seq;		// 計算終了
		}
	}

	// 値設定
	ZknBinWeTenbinAnmObjDataSet( p_ggw->ten_bou_obj,
			p_ggw->ten_sara_hero, p_ggw->ten_sara_poke,
			p_ggw->hero, p_ggw->poke, p_ggw->now_rota );
		
}

//----------------------------------------------------------------------------
/**
 *	@brief	回転角から描画データ設定
 *
 *	@param	ten_bou				描画するオブジェ
 *	@param	tenbin_sara_hero
 *	@param	tenbin_sara_poke
 *	@param	hero
 *	@param	poke
 *	@param	rota		回転角
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBinWeTenbinAnmObjDataSet( SWSP_OBJ_PTR ten_bou, CLACT_WORK_PTR tenbin_sara_hero, CLACT_WORK_PTR tenbin_sara_poke, CLACT_WORK_PTR hero, CLACT_WORK_PTR poke, u16 rota )
{
	fx32 move_x, move_y;
	VecFx32 mat;

	SWSP_SetSpriteRotZ( ten_bou, rota );	//Z軸回転

	// XY移動値を取得
	move_x = FX_Mul( FX_CosIdx( rota ), ZKN_BIG_WE_TENBIN_OBJ_DIS_X << FX32_SHIFT );
	move_y = FX_Mul( FX_SinIdx( rota ), ZKN_BIG_WE_TENBIN_OBJ_DIS_X << FX32_SHIFT );

	// 主人公とポケグラの座標を設定
	mat.x = (ZKN_BIG_WE_TENBIN_MAT_X << FX32_SHIFT) + move_x;
	mat.y = (ZKN_BIG_WE_WEIGHT_HERO_DEF_Y << FX32_SHIFT) + move_y;
	CLACT_SetMatrix( hero, &mat );
	mat.y += ZKN_BIG_WE_TENBIN_SARA_MAT_OFS_Y << FX32_SHIFT;
	CLACT_SetMatrix( tenbin_sara_hero, &mat );

	mat.x = (ZKN_BIG_WE_TENBIN_MAT_X << FX32_SHIFT) - move_x;
	mat.y = (ZKN_BIG_WE_WEIGHT_POKEGRA_DEF_Y << FX32_SHIFT) - move_y;
	CLACT_SetMatrix( poke, &mat );
	mat.y += ZKN_BIG_WE_TENBIN_SARA_MAT_OFS_Y << FX32_SHIFT;
	CLACT_SetMatrix( tenbin_sara_poke, &mat );
}

//----------------------------------------------------------------------------
/**
 *	@brief	天秤アニメリクエスト
 *
 *	@param	p_draw		描画ワーク
 *	@param	add_num		スピード
 *	@param	end_num		終了角度
 *	@param	way			アニメ方向		主人公に反映0　ポケモンに反映1
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigWeTenbinAnimeReq( ZKN_BIG_WE_DRAW* p_draw, ZKN_BIG_WE_DRAWGLB* p_drawglb, u16 add_num, u16 end_num, int way )
{
	p_draw->tenbin_anm.ten_bou_obj	 = p_drawglb->swsp_obj;
	p_draw->tenbin_anm.ten_sara_hero = p_draw->tenbin_sara[0];
	p_draw->tenbin_anm.ten_sara_poke = p_draw->tenbin_sara[1];
	p_draw->tenbin_anm.hero = p_draw->hero;
	p_draw->tenbin_anm.poke = p_draw->poke;
	p_draw->tenbin_anm.now_rota = 0;
	p_draw->tenbin_anm.anm_end = &p_draw->anm_end;
	p_draw->anm_end = FALSE;

	// 主人公から傾かせるかポケモンから傾かせるか
	if( way == 0 ){
		p_draw->tenbin_anm.add_rota = add_num;
		p_draw->tenbin_anm.target_rota = end_num;
	}else{
		p_draw->tenbin_anm.add_rota = -add_num;
		p_draw->tenbin_anm.target_rota = -end_num;
	}

	p_draw->tcb = TCB_Add( ZknBigWeTenbinAnimeTcb, &p_draw->tenbin_anm, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	天秤アニメタスク
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigWeTenbinAnimeTcb( TCB_PTR tcb, void* work )
{
	ZKN_BIG_WE_TENBIN* p_tenw = (ZKN_BIG_WE_TENBIN*)work;
	BOOL end_flag = FALSE;
	
	// 回転角計算
	if( p_tenw->add_rota < 0 ){
		if( (p_tenw->now_rota + p_tenw->add_rota) >= p_tenw->target_rota ){
			p_tenw->now_rota += p_tenw->add_rota;
		}else{
			p_tenw->now_rota = p_tenw->target_rota;
			end_flag = TRUE;		// 計算終了
		}
	}else{
		if( (p_tenw->now_rota + p_tenw->add_rota) <= p_tenw->target_rota ){
			p_tenw->now_rota += p_tenw->add_rota;
		}else{
			p_tenw->now_rota = p_tenw->target_rota;
			end_flag = TRUE;		// 計算終了
		}
	}

	// 値設定
	ZknBinWeTenbinAnmObjDataSet( p_tenw->ten_bou_obj,
			p_tenw->ten_sara_hero, p_tenw->ten_sara_poke,
			p_tenw->hero, p_tenw->poke, p_tenw->now_rota );


	if( end_flag == TRUE ){
		TCB_Delete( tcb );
		*p_tenw->anm_end = TRUE;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェクトジャンプタスクリクエスト
 *
 *	@param	p_draw		描画ワーク
 *	@param	jump_num	ジャンプ値（初速度）
 *	@param	way			主人公0　ポケモン1
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigWeJumpAnimeReq( ZKN_BIG_WE_DRAW* p_draw, s16 jump_num, int way )
{
	const VecFx32* p_mat;
	
	if( way == 0 ){
		p_draw->jump_anm.obj = p_draw->poke;
	}else{
		p_draw->jump_anm.obj = p_draw->hero;
	}

	// 初速度からカウント値を求める
	p_draw->jump_anm.count_max = (-jump_num / ZKN_BIG_WE_JUMP_ANIME_G) * 2;

	// 今のY座標取得
	p_mat = CLACT_GetMatrix( p_draw->jump_anm.obj );
	p_draw->jump_anm.now_x = p_mat->x;
	p_draw->jump_anm.now_y = p_mat->y;

	p_draw->jump_anm.count  = 0;
	p_draw->jump_anm.vo		= jump_num;
	p_draw->jump_anm.seq	= 0;
	p_draw->jump_anm.anm_end = &p_draw->anm_end;
	p_draw->anm_end = FALSE;

	p_draw->tcb = TCB_Add( ZknBigWeJumpAnimeTcb, &p_draw->jump_anm, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ジャンプアニメ
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigWeJumpAnimeTcb( TCB_PTR tcb, void* work )
{
	ZKN_BIG_WE_JUMP* p_jmpw = (ZKN_BIG_WE_JUMP*)work;
	int dis;
	VecFx32 mat;


	switch( p_jmpw->seq ){
	case 0:		// ジャンプ計算
		p_jmpw->count ++;
		dis = (p_jmpw->vo * p_jmpw->count) + ((ZKN_BIG_WE_JUMP_ANIME_G * (p_jmpw->count * p_jmpw->count)) / 2);	// dis = vo*t + 1/2*a*(t*t)	距離

		// 座標設定
		mat.x = p_jmpw->now_x;
		mat.y = p_jmpw->now_y + (dis<<FX32_SHIFT);
		CLACT_SetMatrix( p_jmpw->obj, &mat );	

		if( p_jmpw->count >= p_jmpw->count_max ){

			p_jmpw->count = 0;		// 振るえカウントにも使用する
			p_jmpw->count_max = 1 + (p_jmpw->vo / ZKN_BIG_WE_JUMP_SHAKE_GET_NUM_DIV);	// 振るえ数
			p_jmpw->seq++;
		}
		break;

	case 1:		// 震える
		if( p_jmpw->count == 0 ){
			// 座標設定
			mat.x = p_jmpw->now_x + ZKN_BIG_WE_JUMP_SHAKE_X;
			mat.y = p_jmpw->now_y;
			CLACT_SetMatrix( p_jmpw->obj, &mat );
		}

		p_jmpw->count++;

		if( p_jmpw->count > ZKN_BIG_WE_JUMP_SHAKE_WAIT ){
			p_jmpw->count = 0;
			p_jmpw->seq++;
		}
		break;

	case 2:
		if( p_jmpw->count == 0 ){
			// 座標設定
			mat.x = p_jmpw->now_x - ZKN_BIG_WE_JUMP_SHAKE_X;
			mat.y = p_jmpw->now_y;
			CLACT_SetMatrix( p_jmpw->obj, &mat );
		}

		p_jmpw->count++;

		if( p_jmpw->count > ZKN_BIG_WE_JUMP_SHAKE_WAIT ){
			p_jmpw->count_max--;
			if( p_jmpw->count_max > 0 ){
				p_jmpw->count = 0;
				p_jmpw->seq = 1;
			}else{
				p_jmpw->seq ++;
			}
		}
		break;

	case 3:		// 終了
		// 座標設定
		mat.x = p_jmpw->now_x;
		mat.y = p_jmpw->now_y;
		CLACT_SetMatrix( p_jmpw->obj, &mat );

		TCB_Delete( tcb );
		*p_jmpw->anm_end = TRUE;
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	アニメデータを選ぶ
 *
 *	@param	p_arry	配列
 *	@param	num		配列数
 *	@param	dis		距離
 *
 *	@return	アニメデータ
 */
//-----------------------------------------------------------------------------
static const ZKN_BIG_WE_ANIME_DATA* ZknBigWeAnimeTblGet( const ZKN_BIG_WE_ANIME_DATA* p_arry, int num,  int dis )
{
	int i;

	for( i=0; i<num; i++ ){
		
		if( p_arry[i].dis >= dis ){
			return &p_arry[ i ];
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレットフェードさせる
 *
 *	@param	p_draw		描画
 *	@param	evy				係数
 *	@param	next_rgb		色
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigWePalFadeSet( ZKN_BIG_WE_DRAW* p_draw, u8 evy, u16 next_rgb )
{
	NNSG2dPaletteData* plttdata = CLACT_U_ResManagerGetResObjResPltt( p_draw->res_obj[ CLACT_U_PLTT_RES ] );
	const NNSG2dImagePaletteProxy* pltt_prox = CLACT_U_PlttManagerGetProxy( p_draw->res_obj[ CLACT_U_PLTT_RES ], NULL );
	
	// Icon
	SoftFade( plttdata->pRawData,
			p_draw->pal_fade_buff, ZKN_BIG_WEIGHT_PLTT_LOAD * 16,
			evy, next_rgb );

	AddVramTransferManager(
			NNS_GFD_DST_2D_OBJ_PLTT_MAIN,
			NNS_G2dGetImagePaletteLocation( pltt_prox,NNS_G2D_VRAM_TYPE_2DMAIN  ),
			p_draw->pal_fade_buff,
			ZKN_BIG_WEIGHT_PLTT_LOAD * 32 );


	// その他
	plttdata = CLACT_U_ResManagerGetResObjResPltt( p_draw->res_obj_main[ CLACT_U_PLTT_RES ] );
	pltt_prox = CLACT_U_PlttManagerGetProxy( p_draw->res_obj_main[ CLACT_U_PLTT_RES ], NULL );
	
	SoftFade( plttdata->pRawData,
			p_draw->pal_fade_buff_main, ZKN_BIG_PLTT_LOAD * 16,
			evy, next_rgb );

	AddVramTransferManager(
			NNS_GFD_DST_2D_OBJ_PLTT_MAIN,
			NNS_G2dGetImagePaletteLocation( pltt_prox,NNS_G2D_VRAM_TYPE_2DMAIN  ),
			p_draw->pal_fade_buff_main,
			ZKN_BIG_PLTT_LOAD * 32 );
}
