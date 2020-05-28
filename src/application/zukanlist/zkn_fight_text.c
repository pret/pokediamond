//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_fight_text.c
 *	@brief		図鑑戦闘語のテキストデータ表示システム
 *	@author		tomoya takahashi
 *	@data		2006.03.22
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#include "include/gflib/display.h"

#include "include/system/brightness.h"
#include "include/system/arc_util.h"
#include "include/system/fontproc.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"
#include "include/msgdata/msg_zkn_height.h"
#include "include/msgdata/msg_zkn_gram.h"
#include "include/msgdata/msg_zkn_comment_00.h"
#include "include/msgdata/msg_zkn_type.h"
#include "include/poketool/pokefoot.h"
#include "include/poketool/poke_tool.h"
#include "include/poketool/poke_number.h"
#include "include/gflib/vram_transfer_manager.h"

#include "include/system/snd_tool.h"

#include "include/battle/battle_common.h"

#include "include/application/zukanlist/zukan.naix"
#include "include/application/zukanlist/zkn_sys_static.h"

#define	__ZKN_FIGHT_TEXT_H_GLOBAL
#include "include/application/zukanlist/zkn_fight_text.h"

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


#define ZKN_FIGHT_MANAG_RES_NUM		( 8 )
#define ZKN_FIGHT_FONTOAM_WORKNUM	( 3 )
#define ZKN_FIGHT_CLACT_WORKNUM		( 32 )
#define ZKN_FIGHT_CHAR_WORKNUM		( 32 )
#define ZKN_FIGHT_CHAR_AREA_SIZE_MAIN	( 1024 * 0x40 )	// 64k
#define ZKN_FIGHT_CHAR_AREA_SIZE_SUB	( 512 * 0x20 )	// 32k

#define ZKN_FIGHT_OAM_BG_PRI	( 2 )
#define ZKN_FIGHT_OAM_SOFT_PRI	( 32 )

// 背景座標
#define ZKN_FIGHT_POKE_DRAW_FRAME_CX	( 0 )
#define ZKN_FIGHT_POKE_DRAW_FRAME_CY	( 3 )
#define ZKN_FIGHT_FOOT_FRAME_CX			( 12 )
#define ZKN_FIGHT_FOOT_FRAME_CY			( 8 )
#define ZKN_FIGHT_TEXT_FRAME_CX			( 0 )
#define ZKN_FIGHT_TEXT_FRAME_CY			( 16 )


// 文字列面
#define ZKN_FIGHT_NUM_STR		( 64 )	// バッファサイズ

#define ZKN_FIGHT_TITLE_TEXT_X	( 32 )
#define ZKN_FIGHT_TITLE_TEXT_Y	( 1 )

//-------------------------------------
//	表示シーケンス
//=====================================
enum
{
	ZKN_FIGHT_FADE_IN,
	ZKN_FIGHT_FADE_IN_WAIT,
	ZKN_FIGHT_SND_PLY,
	ZKN_FIGHT_SND_WAIT,
	ZKN_FIGHT_END
};

// ポケモンリスト座標
#define ZKN_FIGHT_POKELIST_MAT_X	( 172 )
#define ZKN_FIGHT_POKELIST_MAT_Y	( 32 )

// 足跡
#define ZKN_FIGHT_FOOT_MAT_X	( 120 * FX32_ONE )
#define ZKN_FIGHT_FOOT_MAT_Y	( 88 * FX32_ONE )

// タイプ座標
#define ZKN_FIGHT_POKETYPE1_MAT_X	( 170 * FX32_ONE )
#define ZKN_FIGHT_POKETYPE2_MAT_X	( 220 * FX32_ONE )
#define ZKN_FIGHT_POKETYPE_MAT_Y	( 72 * FX32_ONE )
// ﾀｲﾌﾟ数
enum{
	ZKN_FIGHT_TYPE_1,
	ZKN_FIGHT_TYPE_2,
	ZKN_FIGHT_TYPE_NUM
};

// ～ポケモン座標
#define ZKN_FIGHT_POKETYPE_TEXT_MAT_X	( 192 * FX32_ONE )
#define ZKN_FIGHT_POKETYPE_TEXT_MAT_Y	( 52 * FX32_ONE )


// パレットアニメ
enum{
	ZKN_FIGHT_PALANM_ONE,
	ZKN_FIGHT_PALANM_TWO,
	ZKN_FIGHT_PALANM_NUM
};
#define ZKN_FIGHT_PALANM_TIMING		( 16 )
#define ZKN_FIGHT_PALANN_PAL		( 0 )
#define ZKN_FIGHT_PALANN_PAL_NUM	( 1 )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	足跡データ
//=====================================
typedef struct {
	CLACT_WORK_PTR foot;
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];
} ZKN_FIGHT_FOOT;

//-------------------------------------
//	～ポケモン
//=====================================
typedef struct {
	CLACT_WORK_PTR  poketype_text_tbl;
	ZKN_FONTOAM_DATA*  p_poketype_text;
} ZKN_FIGHT_POKETYPE_NAME;

//-------------------------------------
//	ﾀｲﾌﾟ
//=====================================
typedef struct {
	CLACT_WORK_PTR  type[ ZKN_FIGHT_TYPE_NUM ];
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// Resourceオブジェポインタ
} ZKN_FIGHT_TYPE;

//-------------------------------------
//	パレットアニメワーク
//=====================================
typedef struct {
	void* p_pltt_buff[ ZKN_FIGHT_PALANM_NUM ];
	NNSG2dPaletteData* p_plt[ ZKN_FIGHT_PALANM_NUM ];
	int count;
	int anmtbl[ ZKN_FIGHT_PALANM_NUM ];
	int now_set;
} ZKN_PALANM_WORK;




//-------------------------------------
//	描画ワーク
//=====================================
typedef struct _ZKN_FIGHT_TEXT_DRAW{
	GF_BGL_INI*			p_bgl;		// BGL
	GF_BGL_BMPWIN*		p_bmp;		// ビットマップウィンドウ
	PALETTE_FADE_PTR	p_pfd;		// パレットフェード
	SOFT_SPRITE*		p_ssp;		// 表示ポケモンデータ
	CLACT_U_EASYRENDER_DATA render_data;	// レンダラーデータ
	CLACT_SET_PTR		clact_set;	// セルアクターセット
	CLACT_U_RES_MANAGER_PTR	res_manager[ ZKN_CLACT_RES_MANAGER_NUM ];	// リソースマネージャ
	ZKN_FONTOAM_SYS_PTR p_fontoam_sys;	// FONTOAMシステム

	ZKN_POKELIST_DATA_OAM_DATA poketbl;	// ポケモンデータテーブルデータ
	ZKN_FIGHT_FOOT pokefoot;	// ポケモン足跡
	ZKN_FIGHT_POKETYPE_NAME poketype_name;	// ～ポケモン
	ZKN_FIGHT_TYPE poke_type;	// ポケモンﾀｲﾌﾟワーク

	u32 oam_mapping_mode_tmp;	// オブジェマップモード保存

	u32 seq;

	u32 monsno;

	TCB_PTR tcb;

	ZKN_PALANM_WORK palanm;	// パレットアニメ
	BOOL palanm_flag;

} ;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
// タスク
static void ZknFight_TCB( TCB_PTR tcb, void* p_work );


// パレットフェード処理
static void ZknFight_PalFadeWorkSet( PALETTE_FADE_PTR pfd, SOFT_SPRITE* ssp );
static void ZknFight_PalFadeReq( PALETTE_FADE_PTR pfd, SOFT_SPRITE* ssp, int ssp_s_evy, int s_evy, int e_evy, int wait, int rgb );
static BOOL ZknFight_PalFadeEndCheck( PALETTE_FADE_PTR pfd, SOFT_SPRITE* ssp );


//描画関係です
static void ZknFight_InitDraw( ZKN_FIGHT_TEXT_DRAW* p_zftd, const ZKN_FIGHT_TEXT_PARAM* cp_param );
static void ZknFight_DeleteDraw( ZKN_FIGHT_TEXT_DRAW* p_zftd );

static void ZknFight_InitBgSystem( GF_BGL_INI* p_bg, int heap );
static void ZknFitht_ReleaseBgSystem( GF_BGL_INI* p_bg );
static GF_BGL_BMPWIN* ZknFight_InitTextBmp( GF_BGL_INI* p_bgl, int heap );
static void ZknFight_DeleteTextBmp( GF_BGL_BMPWIN* p_bmp );
static void ZknFight_InitResManager( CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap );
static void ZknFight_DeleteResManager( CLACT_U_RES_MANAGER_PTR* pp_res_manager );
static void ZknFight_InitPokeNameTblFontOamData( ZKN_POKELIST_DATA_OAM_DATA* p_poketbl, ZKN_FONTOAM_SYS_PTR p_fontoam_sys, int heap, int monsno, int pokenum_mode );
static void ZknFight_DeletePokeNameTblFontOamData( ZKN_POKELIST_DATA_OAM_DATA* p_poketbl );
static SOFT_SPRITE* ZknFight_InitSoftSprite( SOFT_SPRITE_MANAGER* p_ssp, POKEMON_PARAM* p_pp, int x, int y, int heap );

static void ZknFight_DefaultClactResLoad( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, int arc_idx, int charidx, int plttidx, int cellidx, int cellanmidx, int plttload_num, int common_res_id );
static void ZknFight_DefaultClactResDelete( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager );
static void ZknFight_DefaultClactHeaderMake( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager, CLACT_HEADER* p_head, int bg_pri );

static void ZknFight_PokeFootResLoad( ZKN_FIGHT_FOOT* foot, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int monsno, int heap );
static void ZknFight_PokeFootResDelete( ZKN_FIGHT_FOOT* foot, CLACT_U_RES_MANAGER_PTR* pp_res_manager );
static void ZknFight_PokeFootClactAdd( ZKN_FIGHT_FOOT* foot, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap );
static void ZknFight_PokeFootClactDelete( ZKN_FIGHT_FOOT* foot );

static void ZknFight_PokeTypeNameClactAdd( ZKN_FIGHT_POKETYPE_NAME* typename, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, CLACT_U_RES_OBJ_PTR* pp_poketbl_res_obj );
static void ZknFight_PokeTypeNameClactDelete( ZKN_FIGHT_POKETYPE_NAME* typename );
static void ZknFight_PokeTypeNameFontAdd( ZKN_FIGHT_POKETYPE_NAME* typename, ZKN_FONTOAM_SYS_PTR p_fontoam_sys, int heap, int monsno, CLACT_U_RES_OBJ_PTR pltt_res );
static void ZknFight_PokeTypeNameFontDelete( ZKN_FIGHT_POKETYPE_NAME* typename );

static void ZknFight_PokeTypeResLoad( ZKN_FIGHT_TYPE* type, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int monsno, int heap );
static void ZknFight_PokeTypeResDelete( ZKN_FIGHT_TYPE* type, CLACT_U_RES_MANAGER_PTR* pp_res_manager );
static void ZknFight_PokeTypeClactAdd( ZKN_FIGHT_TYPE* type, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, int monsno );
static void ZknFight_PokeTypeClactDelete( ZKN_FIGHT_TYPE* type );

static void ZknFight_BackGroundSetUp( GF_BGL_INI* p_bg, int heap );
static void ZknFight_BackUtilSetUp( GF_BGL_INI* p_bg, int heap );
static void ZknFight_TextSetUp( GF_BGL_BMPWIN* p_bmp, int heap, int monsno );
static void ZknFight_FontSetPokeTitle( GF_BGL_BMPWIN* p_bmp, int heap );

static int ZknFight_GetPokemonNumber( u32 mode, POKEMON_PARAM* p_pp );

static void ZknFight_InitCharManager( int heap );
static void ZknFight_DeleteCharManager( void );


// パレットアニメ
static void ZknFight_InitPalAnm( ZKN_PALANM_WORK* p_data, int heap, int poke_num_mode );
static void ZknFight_MainPalAnm( ZKN_PALANM_WORK* p_data );
static void ZknFight_DeletePalAnm( ZKN_PALANM_WORK* p_data );
static void ZknFight_TransPalAnm( ZKN_PALANM_WORK* p_data, int frm );
static void ZknFight_TransPalAnmVblank( ZKN_PALANM_WORK* p_data, int frm );


//----------------------------------------------------------------------------
/**
 *	@brief	図鑑テキスト描画リクエスト
 *
 *	@param	cp_param	データパラメータ
 *
 *	@return	描画ワーク
 */
//-----------------------------------------------------------------------------
ZKN_FIGHT_TEXT_DRAW* ZKN_FIGHT_TextDrawReq( const ZKN_FIGHT_TEXT_PARAM* cp_param )
{
	ZKN_FIGHT_TEXT_DRAW* p_zftd = sys_AllocMemory( cp_param->heap, sizeof( ZKN_FIGHT_TEXT_DRAW ) );
	memset( p_zftd, 0, sizeof( ZKN_FIGHT_TEXT_DRAW ) );

	// 描画面設定
	ZknFight_InitDraw( p_zftd, cp_param );

	// パレットフェード初期化
	ZknFight_PalFadeWorkSet( p_zftd->p_pfd, p_zftd->p_ssp );
	ZknFight_PalFadeReq( p_zftd->p_pfd, p_zftd->p_ssp, 10, 15, 0, 0, 0x0 );
		
	// タスク登録
	p_zftd->tcb = TCB_Add( ZknFight_TCB, p_zftd, ZKN_FIGHT_TCB_PRI );

	return p_zftd;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑テキスト描画　破棄
 *
 *	@param	p_data	描画ワーク
 *
 *	@return	none
 *
 *	フェードアウト後に破棄する必要があります.
 */
//-----------------------------------------------------------------------------
void ZKN_FIGHT_TextDrawDelete( ZKN_FIGHT_TEXT_DRAW* p_data )
{
	// ワーク内データ破棄
	ZknFight_DeleteDraw( p_data );

	// TCB破棄
	TCB_Delete( p_data->tcb );

	// ワーク破棄
	sys_FreeMemoryEz( p_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑テキスト描画　終了チェック
 *
 *	@param	cp_data		図鑑ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
BOOL ZKN_FIGHT_TexDrawEndCheck( const ZKN_FIGHT_TEXT_DRAW* cp_data )
{
	if( cp_data->seq == ZKN_FIGHT_END ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ソフトウェアスプライトワークを返す
 *
 *	@param	p_data	ワーク
 *
 *	@return	ソフトウェアスプライトワーク
 */
//-----------------------------------------------------------------------------
SOFT_SPRITE* ZKN_FIGHT_TexDrawGetSsp( ZKN_FIGHT_TEXT_DRAW* p_data )
{
	return p_data->p_ssp;
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレットアニメONOFFフラグ設定
 *
 *	@param	p_data	ワーク
 *	@param	flag	パレットアニメフラグ
 *
 *	@return	none
 *
 *	flag
 *		TRUE	アニメON
 *		FALSE	アニメOFF
 */
//-----------------------------------------------------------------------------
void ZKN_FIGHT_PalAnmFlagSet( ZKN_FIGHT_TEXT_DRAW* p_data, BOOL flag )
{
	p_data->palanm_flag = flag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレットアニメONOFFフラグ取得
 *
 *	@param	cp_data		ワーク
 *
 *	@retval	TRUE	アニメ中
 *	@retval	FALSE	アニメOFF中
 */
//-----------------------------------------------------------------------------
BOOL ZKN_FIGHT_PalAnmFlagGet( const ZKN_FIGHT_TEXT_DRAW* cp_data )
{
	return cp_data->palanm_flag;
}



//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	描画関係の全初期化
 *
 *	@param	p_zftd		ワーク
 *	@param	cp_param	システム引数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_InitDraw( ZKN_FIGHT_TEXT_DRAW* p_zftd, const ZKN_FIGHT_TEXT_PARAM* cp_param )
{
	ZKN_FONTOAM_SYS_INIT fontoam_init;

	// 全国図鑑ナンバー
	p_zftd->monsno = PokeParaGet( cp_param->p_pp, ID_PARA_monsno, NULL );

	// BGシステム
	p_zftd->p_bgl = cp_param->p_bgl;

	// セルアクターセット
	p_zftd->clact_set = CLACT_U_SetEasyInit( ZKN_FIGHT_CLACT_WORKNUM, &p_zftd->render_data, cp_param->heap );

	// 一応OAM面のクリア
	CLACT_UtilOamRamClear_Main( cp_param->heap );

	//　キャラクタマネージャ初期化
	ZknFight_InitCharManager( cp_param->heap );

	// ssp
	p_zftd->p_ssp	= ZknFight_InitSoftSprite( 
			cp_param->p_ssm, cp_param->p_pp,
			ZKN_FIGHT_POKEGRA_MAT_X, ZKN_FIGHT_POKEGRA_MAT_Y,
			cp_param->heap );
	
	// パレットフェード
	p_zftd->p_pfd	= cp_param->p_pfd;

	// FONTOAM作成
	fontoam_init.clact_set	= p_zftd->clact_set;
	fontoam_init.p_bg		= p_zftd->p_bgl;
	fontoam_init.work_num	= ZKN_FIGHT_FONTOAM_WORKNUM;
	fontoam_init.heap		= cp_param->heap;
	p_zftd->p_fontoam_sys	= ZKN_FONTOAM_InitSys( &fontoam_init );
	
	// BGSystem初期化
	ZknFight_InitBgSystem( p_zftd->p_bgl, cp_param->heap );

	// 全ての面を非表示にする
	G2_SetBlendBrightness( PLANEMASK_ALL, -16 );
/*	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_OFF );
//*/
	// BMPの取得
	p_zftd->p_bmp = ZknFight_InitTextBmp( p_zftd->p_bgl, cp_param->heap );

	// リソースマネージャ作成
	ZknFight_InitResManager( p_zftd->res_manager, cp_param->heap );
	
	// ポケモン名テーブル作成
	ZKN_GlbPokeNameTblResLoad_Minute( &p_zftd->poketbl, p_zftd->res_manager, cp_param->heap );

	// ポケモン名テーブルアクター登録
	ZKN_GlbPokeNameTblActAdd_Minute( &p_zftd->poketbl, p_zftd->clact_set, p_zftd->res_manager, cp_param->heap, ZKN_FIGHT_OAM_BG_PRI );

	// ポケモン名設定
	ZknFight_InitPokeNameTblFontOamData( &p_zftd->poketbl, p_zftd->p_fontoam_sys, cp_param->heap, p_zftd->monsno, cp_param->pokenum_mode );
	
	// ポケモン名座標設定
	ZKN_UTIL_PokeListPokeNameGlbMatrixSet_Minute( &p_zftd->poketbl, ZKN_FIGHT_POKELIST_MAT_X, ZKN_FIGHT_POKELIST_MAT_Y );

	// ポケモン名表示
	ZKN_GlbPokeNameTblDrawFlagSet_Minute( &p_zftd->poketbl, TRUE );

	// ポケフット初期化
	ZknFight_PokeFootResLoad( &p_zftd->pokefoot, p_zftd->res_manager, p_zftd->monsno, cp_param->heap );
	ZknFight_PokeFootClactAdd( &p_zftd->pokefoot, p_zftd->clact_set, p_zftd->res_manager, cp_param->heap );

	// ポケモンﾀｲﾌﾟアクター初期化
	ZknFight_PokeTypeResLoad( &p_zftd->poke_type, p_zftd->res_manager, p_zftd->monsno, cp_param->heap );
	ZknFight_PokeTypeClactAdd( &p_zftd->poke_type, p_zftd->clact_set, p_zftd->res_manager, cp_param->heap, p_zftd->monsno );


	// ～ポケモン初期化
	ZknFight_PokeTypeNameClactAdd( &p_zftd->poketype_name, p_zftd->clact_set, p_zftd->res_manager, cp_param->heap, p_zftd->poke_type.res_obj );
	ZknFight_PokeTypeNameFontAdd( &p_zftd->poketype_name, p_zftd->p_fontoam_sys, cp_param->heap, p_zftd->monsno, p_zftd->poketbl.pokelist_res_obj[ CLACT_U_PLTT_RES ] );

	// 背景設定
	ZknFight_BackGroundSetUp( p_zftd->p_bgl, cp_param->heap );
	ZknFight_BackUtilSetUp( p_zftd->p_bgl, cp_param->heap );

	// 文字列面設定
	ZknFight_TextSetUp( p_zftd->p_bmp, cp_param->heap, p_zftd->monsno );

	// パレットアニメ初期化
	ZknFight_InitPalAnm( &p_zftd->palanm, cp_param->heap, cp_param->pokenum_mode );
	p_zftd->palanm_flag = TRUE;		// パレットアニメフラグON
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画関係の全破棄
 *
 *	@param	p_zftd		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_DeleteDraw( ZKN_FIGHT_TEXT_DRAW* p_zftd )
{
	// パレットアニメ破棄
	ZknFight_DeletePalAnm( &p_zftd->palanm );
	
	// ポケモンﾀｲﾌﾟアクター
	ZknFight_PokeTypeClactDelete( &p_zftd->poke_type );
	ZknFight_PokeTypeResDelete( &p_zftd->poke_type, p_zftd->res_manager );
	
	// ～ポケモンの破棄
	ZknFight_PokeTypeNameFontDelete( &p_zftd->poketype_name );
	ZknFight_PokeTypeNameClactDelete( &p_zftd->poketype_name );
	
	// ポケフット破棄
	ZknFight_PokeFootClactDelete( &p_zftd->pokefoot );
	ZknFight_PokeFootResDelete( &p_zftd->pokefoot, p_zftd->res_manager );
	
	// ポケモン名リスト破棄
	ZknFight_DeletePokeNameTblFontOamData( &p_zftd->poketbl );	// FONTOAM
	ZKN_GlbPokeNameTblActDelete_Minute( &p_zftd->poketbl );		// アクター破棄
	ZKN_GlbPokeNameTblResRelease_Minute( &p_zftd->poketbl, p_zftd->res_manager );	// リソース破棄	

	// リソースマネージャ破棄
	ZknFight_DeleteResManager( p_zftd->res_manager );

	// セルアクター破棄
	CLACT_DestSet( p_zftd->clact_set );

	// ビットマップウィンドウ破棄
	ZknFight_DeleteTextBmp( p_zftd->p_bmp );

	// BGシステム破棄
	ZknFitht_ReleaseBgSystem( p_zftd->p_bgl );

	// FONTOAMシステム破棄
	ZKN_FONTOAM_DeleteSys( p_zftd->p_fontoam_sys );

	// キャラクタマネージャ破棄
	ZknFight_DeleteCharManager();
}

//----------------------------------------------------------------------------
/**
 *	@brief	BGシステムデータ書き換え
 *
 *	@param	p_bgl	BGシステム
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_InitBgSystem( GF_BGL_INI* p_bg, int heap )
{
	// メイン画面 BG1面		文字列書き込み面
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 1, 0, 0, FALSE
		};
		GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_FONT_M );
		GF_BGL_BGControlSet( p_bg, ZKN_BG_FRM_FONT_M, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( ZKN_BG_FRM_FONT_M, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_FONT_M );
	}

	// メイン画面 BG2面		ユーティリティ面
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0800, GX_BG_CHARBASE_0x0c000,
			GX_BG_EXTPLTT_01, 2, 0, 0, FALSE
		};
		GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_UTIL_M );
		GF_BGL_BGControlSet( p_bg, ZKN_BG_FRM_UTIL_M, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( ZKN_BG_FRM_UTIL_M, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_UTIL_M );
	}

	// 3D面
	GF_BGL_PrioritySet( GF_BGL_FRAME0_M, 0 );
	// BG0ON
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	GF_BGL_BGControlExit( p_bg, 0 );

	// メイン画面 BG3面		背景面
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x14000,
			GX_BG_EXTPLTT_01, 3, 0, 0, FALSE
		};
		GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_BACK_M );
		GF_BGL_BGControlSet( p_bg, ZKN_BG_FRM_BACK_M, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( ZKN_BG_FRM_BACK_M, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_BACK_M );
	}

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGコントロールデータ破棄
 *
 *	@param	p_bg	BGコントロール
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknFitht_ReleaseBgSystem( GF_BGL_INI* p_bg )
{
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_FONT_M );
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_UTIL_M );
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_BACK_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	戦闘捕獲後　図鑑画面　ビットマップウィンドウ作成
 *
 *	@param	p_bgl	BGシステム
 *	@param	heap	ヒープ
 *
 *	@return	ビットマップウィンドウ	
 */
//-----------------------------------------------------------------------------
static GF_BGL_BMPWIN* ZknFight_InitTextBmp( GF_BGL_INI* p_bgl, int heap )
{
	GF_BGL_BMPWIN* p_bmp;

	// メモリ確保
	p_bmp = GF_BGL_BmpWinAllocGet( heap, 1 );	
	
	// モジメンのビットマップウィンドウ作成
	// ビットマップウィンドウ登録
	GF_BGL_BmpWinAdd( p_bgl, p_bmp, ZKN_BG_FRM_FONT_M, 0, 0, ZKN_BG_FONTBMP_CX, ZKN_BG_FONTBMP_CY, ZKN_BG_FIGHT_FONT_COLOR, 0 );

	// クリーン
	GF_BGL_BmpWinDataFill( p_bmp, 0 );

	// 表示
	GF_BGL_BmpWinOn( p_bmp );

	return p_bmp;
}

//----------------------------------------------------------------------------
/**
 *	@brief	戦闘捕獲後　図鑑画面　ビットマップウィンドウ破棄
 *
 *	@param	p_bmp		ビットマップ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_DeleteTextBmp( GF_BGL_BMPWIN* p_bmp )
{
	GF_BGL_BmpWinOff( p_bmp );
	GF_BGL_BmpWinDel( p_bmp );
	GF_BGL_BmpWinFree( p_bmp, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	リソースマネージャの作成
 *
 *	@param	pp_res_manager	リソースマネージャバッファ
 *	@param	heap			ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_InitResManager( CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap )
{
	int i;

	for( i=0; i<ZKN_CLACT_RES_MANAGER_NUM; i++ ){
		pp_res_manager[i] = CLACT_U_ResManagerInit( ZKN_FIGHT_MANAG_RES_NUM, i, heap );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	リソースマネージャのはき
 *
 *	@param	pp_res_manager	リソースマネージャ
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_DeleteResManager( CLACT_U_RES_MANAGER_PTR* pp_res_manager )
{
	int i;

	for( i=0; i<ZKN_CLACT_RES_MANAGER_NUM; i++ ){
		CLACT_U_ResManagerDelete( pp_res_manager[i] );
		pp_res_manager[i] = NULL;
	}	
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン名テーブル文字作成
 *
 *	@param	p_poketbl			ポケモンテーブルワーク
 *	@param	p_fontoam_sys		フォントOAMシステム
 *	@param	heap				ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_InitPokeNameTblFontOamData( ZKN_POKELIST_DATA_OAM_DATA* p_poketbl, ZKN_FONTOAM_SYS_PTR p_fontoam_sys, int heap, int monsno, int pokenum_mode )
{
	ZKN_FONTOAM_INIT fontoam_init;
	GF_BGL_BMPWIN* p_bmp;	// 書き込み領域
	CLACT_U_RES_OBJ_PTR pltt_obj;	// パレットプロクシ取得用

	// ポケモン名アクターに使用するパレットプロクシ取得
	pltt_obj = p_poketbl->pokelist_res_obj[ CLACT_U_PLTT_RES ];
		
	// ポケモン名アクター作成
	fontoam_init.zkn_fontoam = p_fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( pltt_obj, NULL );
	fontoam_init.parent		 = p_poketbl->pokelist_tbl;
	fontoam_init.x			 = -(ZKN_POKELIST_POKENAME_BMP_SIZE_X / 2);
	fontoam_init.y			 = -(ZKN_POKELIST_POKENAME_BMP_SIZE_Y / 2);
	fontoam_init.bg_pri		 = ZKN_FIGHT_OAM_BG_PRI;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;


	// 文字列書き込み領域作成
	if( pokenum_mode == PM_NUMBER_SHINOU ){
		p_bmp = ZKN_UTIL_PokeListPokeNameTblBmpMake_Shinou( p_fontoam_sys, heap, monsno );
	}else{
		p_bmp = ZKN_UTIL_PokeListPokeNameTblBmpMake_Zenkoku( p_fontoam_sys, heap, monsno );
	}

	// FONTOAM登録
	fontoam_init.p_bmp = p_bmp;
	ZKN_GlbPokeNameTblSet_Minute( p_poketbl, &fontoam_init, 0, monsno, pokenum_mode );
	// BMP領域破棄
	ZKN_FONTOAM_DeleteBmp( p_bmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンテーブルフォントデータ破棄
 *
 *	@param	p_poketbl	ポケモンテーブルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_DeletePokeNameTblFontOamData( ZKN_POKELIST_DATA_OAM_DATA* p_poketbl )
{
	if( p_poketbl->p_pokename ){
		ZKN_FONTOAM_Delete( p_poketbl->p_pokename );
		p_poketbl->p_pokename = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	基本的なアクターリソース読み込み関数
 *
 *	@param	p_res_obj		リソースオブジェ
 *	@param	pp_res_manager	リソースマネージャ
 *	@param	heap			ヒープ
 *	@param	charidx			キャラクタデータインデックス
 *	@param	plttidx			パレットデータインデックス
 *	@param	cellidx			セルデータインデックス
 *	@param	cellanmidx		セルアニメインデックス
 *	@param	plttload_num	パレット読み込み本数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_DefaultClactResLoad( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, int arc_idx, int charidx, int plttidx, int cellidx, int cellanmidx, int plttload_num, int common_res_id )
{
	// キャラクタデータ読み込み
	p_res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar( 
			pp_res_manager[ CLACT_U_CHAR_RES ], arc_idx,
			charidx, TRUE,
			common_res_id,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_res_obj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt( 
			pp_res_manager[ CLACT_U_PLTT_RES ], arc_idx,
			plttidx, FALSE, 
			common_res_id,
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			plttload_num, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_res_obj[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_res_obj[ CLACT_U_PLTT_RES ] );


	// セルデータ読み込み
	p_res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			pp_res_manager[ CLACT_U_CELL_RES ], arc_idx,
			cellidx, TRUE,
			common_res_id,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			pp_res_manager[ CLACT_U_CELLANM_RES ], arc_idx, 
			cellanmidx, TRUE,
			common_res_id,
			CLACT_U_CELLANM_RES, heap );
}


//----------------------------------------------------------------------------
/**
 *	@brief	基本的なリソース破棄
 *
 *	@param	p_res_obj		リソースオブジェ	
 *	@param	pp_res_manager	リソースマネージャ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_DefaultClactResDelete( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager )
{
	CLACT_U_CharManagerDelete( p_res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_res_obj[ CLACT_U_PLTT_RES ] );

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_CHAR_RES ],
			p_res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_PLTT_RES ],
			p_res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_CELL_RES ],
			p_res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_CELLANM_RES ],
			p_res_obj[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクターヘッダーデータ作成
 *
 *	@param	p_res_obj			リソースオブジェ
 *	@param	pp_res_manager		リソースマネージャ
 *	@param	p_head				ヘッダーワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_DefaultClactHeaderMake( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager, CLACT_HEADER* p_head, int bg_pri )
{
	
	// 各ボタンを登録
	// アクターヘッダー作成
	CLACT_U_MakeHeader( p_head,
			CLACT_U_ResManagerGetResObjID( p_res_obj[ CLACT_U_CHAR_RES ] ),
			CLACT_U_ResManagerGetResObjID( p_res_obj[ CLACT_U_PLTT_RES ] ),
			CLACT_U_ResManagerGetResObjID( p_res_obj[ CLACT_U_CELL_RES ] ),
			CLACT_U_ResManagerGetResObjID( p_res_obj[ CLACT_U_CELLANM_RES ] ),
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, bg_pri,
			pp_res_manager[ CLACT_U_CHAR_RES ],
			pp_res_manager[ CLACT_U_PLTT_RES ],
			pp_res_manager[ CLACT_U_CELL_RES ],
			pp_res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン足跡リソース読み込み
 *
 *	@param	foot			足跡ワーク
 *	@param	pp_res_manager	リソースマネージャ
 *	@param	monsno			モンスターナンバー
 *	@param	heap			ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeFootResLoad( ZKN_FIGHT_FOOT* foot, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int monsno, int heap )
{
	int arc_file = PokeFootArcFileGet();
	int char_idx = PokeFootCharDataIdxGet( monsno );
	int pltt_idx = PokeFootPlttDataIdxGet();
	int cell_idx = PokeFootCellDataIdxGet();
	int cellanm_idx = PokeFootCellAnmDataIdxGet();

	// リソース読み込み
	ZknFight_DefaultClactResLoad( foot->res_obj, pp_res_manager, heap, arc_file, char_idx, pltt_idx, cell_idx, cellanm_idx, ZKN_ZUKAN_FOOT_PLTT_LOAD, ZKN_ZUKAN_FOOT_RES_ID );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン足跡リソース破棄
 *
 *	@param	foot
 *	@param	pp_res_manager 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeFootResDelete( ZKN_FIGHT_FOOT* foot, CLACT_U_RES_MANAGER_PTR* pp_res_manager )
{
	ZknFight_DefaultClactResDelete( foot->res_obj, pp_res_manager );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン足跡アクター登録
 *
 *	@param	foot			足跡ワーク
 *	@param	clact_set		セルアクターセット
 *	@param	pp_res_manager	リソースマネージャ
 *	@param	heap			ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeFootClactAdd( ZKN_FIGHT_FOOT* foot, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap )
{
	CLACT_ADD_SIMPLE add;
	CLACT_HEADER head;

	// ヘッダー作成
	ZknFight_DefaultClactHeaderMake( foot->res_obj, pp_res_manager, &head, ZKN_FIGHT_OAM_BG_PRI );

	// 設定
	add.ClActSet	= clact_set;
	add.ClActHeader	= &head;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.pri			= ZKN_FIGHT_OAM_SOFT_PRI;
	add.heap		= heap;
	add.mat.x		= ZKN_FIGHT_FOOT_MAT_X;
	add.mat.y		= ZKN_FIGHT_FOOT_MAT_Y;
	foot->foot	= CLACT_AddSimple( &add );
	GF_ASSERT( foot->foot );
}

//----------------------------------------------------------------------------
/**
 *	@brief	足跡アクター破棄
 *
 *	@param	foot	足跡ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeFootClactDelete( ZKN_FIGHT_FOOT* foot )
{
	CLACT_Delete( foot->foot );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンﾀｲﾌﾟ名テーブルのアクター登録
 *
 *	@param	typename			ワーク
 *	@param	clact_set			アクターセット
 *	@param	pp_res_manager		リソースマネージャ
 *	@param	heap				ヒープ
 *	@param	pp_poketbl_res_obj	ポケリストのリソースオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeTypeNameClactAdd( ZKN_FIGHT_POKETYPE_NAME* typename, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, CLACT_U_RES_OBJ_PTR* pp_poketbl_res_obj )
{
	CLACT_ADD_SIMPLE add;
	CLACT_HEADER head;

	// ヘッダー作成
	ZknFight_DefaultClactHeaderMake( pp_poketbl_res_obj, pp_res_manager, &head, ZKN_FIGHT_OAM_BG_PRI );

	// 設定
	add.ClActSet	= clact_set;
	add.ClActHeader	= &head;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.pri			= ZKN_FIGHT_OAM_SOFT_PRI;
	add.heap		= heap;
	add.mat.x		= ZKN_FIGHT_POKETYPE_TEXT_MAT_X;
	add.mat.y		= ZKN_FIGHT_POKETYPE_TEXT_MAT_Y;
	typename->poketype_text_tbl	= CLACT_AddSimple( &add );
	GF_ASSERT( typename->poketype_text_tbl );
	CLACT_AnmChg( typename->poketype_text_tbl, ZKN_ZUKAN_POKETYPE_TEXT_TBL_SEQ );
}

//----------------------------------------------------------------------------
/**
 *	@brief	～ポケモン　のアクター破棄
 *
 *	@param	typename	ポケモンﾀｲﾌﾟ名ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeTypeNameClactDelete( ZKN_FIGHT_POKETYPE_NAME* typename )
{
	CLACT_Delete( typename->poketype_text_tbl );
}

//----------------------------------------------------------------------------
/**
 *	@brief	～ポケモンフォントOAMアッド
 *
 *	@param	typename			～ポケモンワーク
 *	@param	p_fontoam_sys		フォントOAMシステム
 *	@param	heap				ヒープ
 *	@param	monsno				モンスターナンバー
 *	@param	pltt_res			使用パレットリソース
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeTypeNameFontAdd( ZKN_FIGHT_POKETYPE_NAME* typename, ZKN_FONTOAM_SYS_PTR p_fontoam_sys, int heap, int monsno, CLACT_U_RES_OBJ_PTR pltt_res )
{
	GF_BGL_BMPWIN* p_bmp;
	ZKN_FONTOAM_INIT fontoam_init;

	// 文字データ作成
	p_bmp = ZknZukanPokeTypeTextBmpMake( p_fontoam_sys, monsno, heap );

	// 共通データ代入
	fontoam_init.zkn_fontoam = p_fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( pltt_res, NULL );
	fontoam_init.parent		 = typename->poketype_text_tbl;
	fontoam_init.x			 = ZKN_ZUKAN_POKETYPE_TEXT_FONT_OFS_X;
	fontoam_init.y			 = ZKN_ZUKAN_POKETYPE_TEXT_FONT_OFS_Y;
	fontoam_init.bg_pri		 = ZKN_FIGHT_OAM_BG_PRI;
	fontoam_init.soft_pri	 = ZKN_FIGHT_OAM_SOFT_PRI - 1;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;
	fontoam_init.p_bmp		 = p_bmp;
	typename->p_poketype_text = ZKN_FONTOAM_Make( &fontoam_init );
	
	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( p_bmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	～ポケモン　フォントOAM破棄
 *
 *	@param	typename	～ポケモンワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeTypeNameFontDelete( ZKN_FIGHT_POKETYPE_NAME* typename )
{
	ZKN_FONTOAM_Delete( typename->p_poketype_text );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンﾀｲﾌﾟ　アクター　リソース読み込み
 *
 *	@param	type				ﾀｲﾌﾟワーク
 *	@param	pp_res_manager		リソースマネージャ
 *	@param	monsno				モンスターナンバー
 *	@param	heap				ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeTypeResLoad( ZKN_FIGHT_TYPE* type, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int monsno, int heap )
{
	// リソース読み込み
	ZknFight_DefaultClactResLoad( type->res_obj, 
			pp_res_manager, heap, ARC_ZUKAN_GRA, 
			NARC_zukan_zkn_data_oam_main2_lzh_NCGR,
			NARC_zukan_zkn_data_oam2_NCLR,
			NARC_zukan_zkn_data_oam_main2_lzh_NCER,
			NARC_zukan_zkn_data_oam_main2_lzh_NANR,
			ZKN_ZUKAN_PLTT_LOAD,
			ZKN_ZUKAN_POKETYPE_RES_ID );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンﾀｲﾌﾟリソース破棄
 *
 *	@param	type				ﾀｲﾌﾟ
 *	@param	pp_res_manager		リソースマネージャ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeTypeResDelete( ZKN_FIGHT_TYPE* type, CLACT_U_RES_MANAGER_PTR* pp_res_manager )
{
	ZknFight_DefaultClactResDelete( type->res_obj, pp_res_manager );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンﾀｲﾌﾟアクター登録
 *
 *	@param	type			ﾀｲﾌﾟワーク
 *	@param	clact_set		セルアクターセット
 *	@param	pp_res_manager	リソースマネージャ
 *	@param	heap			ヒープ
 *	@param	monsno			モンスターナンバー
 *		
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeTypeClactAdd( ZKN_FIGHT_TYPE* type, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, int monsno )
{
	CLACT_ADD_SIMPLE add;
	CLACT_HEADER head;
	int type1, type2;

	type1 = PokePersonalParaGet( monsno, ID_PER_type1 );
	type2 = PokePersonalParaGet( monsno, ID_PER_type2 );
	// typeをニトロキャラクタのアニメシーケンスナンバーに変更
	type1 =	ZknZukanClactTypeNoChg( type1 );
	type2 =	ZknZukanClactTypeNoChg( type2 );


	// ヘッダー作成
	ZknFight_DefaultClactHeaderMake(type->res_obj, pp_res_manager, &head, ZKN_FIGHT_OAM_BG_PRI );
	
	// 設定
	add.ClActSet	= clact_set;
	add.ClActHeader	= &head;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.pri			= ZKN_FIGHT_OAM_SOFT_PRI;
	add.heap		= heap;

	// ﾀｲﾌﾟ1
	add.mat.x		= ZKN_FIGHT_POKETYPE1_MAT_X;
	add.mat.y		= ZKN_FIGHT_POKETYPE_MAT_Y;
	type->type[ ZKN_FIGHT_TYPE_1 ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( type->type[ ZKN_FIGHT_TYPE_1 ], ZKN_ZUKAN_POKETYPE_NORMAL + type1 );

	// タイプ2
	if( type1 != type2 ){
		add.mat.x = ZKN_FIGHT_POKETYPE2_MAT_X;
		add.mat.y = ZKN_FIGHT_POKETYPE_MAT_Y;
		type->type[ ZKN_FIGHT_TYPE_2 ] = CLACT_AddSimple( &add );
		CLACT_AnmChg( type->type[ ZKN_FIGHT_TYPE_2 ], ZKN_ZUKAN_POKETYPE_NORMAL + type2 );
	}else{
		type->type[ ZKN_FIGHT_TYPE_2 ] = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクターワーク　アクター破棄
 *
 *	@param	type ﾀｲﾌﾟ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeTypeClactDelete( ZKN_FIGHT_TYPE* type )
{
	if( type->type[ ZKN_FIGHT_TYPE_1 ] ){
		CLACT_Delete( type->type[ ZKN_FIGHT_TYPE_1 ] );
	}
	if(type->type[ ZKN_FIGHT_TYPE_2 ]){
		CLACT_Delete( type->type[ ZKN_FIGHT_TYPE_2 ] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	背景設定
 *
 *	@param	p_bg	BGシステム
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_BackGroundSetUp( GF_BGL_INI* p_bg, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// パレット転送
	ArcUtil_PalSet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_NCLR, PALTYPE_MAIN_BG, 0, 0, heap );
	// キャラクタデータ転送
	ArcUtil_BgCharSet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_main_lzh_NCGR, p_bg, ZKN_BG_FRM_BACK_M, 0, 0, TRUE, heap );

	// スクリーンデータ読み込み
	buff = ArcUtil_ScrnDataGet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_bg_main1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_bg, ZKN_BG_FRM_BACK_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// ポケモンの表示枠を背景に貼り付け	
	buff = ArcUtil_ScrnDataGet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_bg_main1_a_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_FIGHT_POKE_DRAW_FRAME_CX, ZKN_FIGHT_POKE_DRAW_FRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// ポケモン足跡の表示枠を背景に貼り付け	
	buff = ArcUtil_ScrnDataGet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_bg_main1_b_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_FIGHT_FOOT_FRAME_CX, ZKN_FIGHT_FOOT_FRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// ポケモン説明text枠を貼り付け	
	buff = ArcUtil_ScrnDataGet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_bg_main1_d_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_FIGHT_TEXT_FRAME_CX, ZKN_FIGHT_TEXT_FRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );
	
	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_bg, ZKN_BG_FRM_BACK_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑ユーティリティ面設定
 *
 *	@param	p_bg
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknFight_BackUtilSetUp( GF_BGL_INI* p_bg, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// キャラクタデータ転送
	ArcUtil_BgCharSet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_main_lzh_NCGR, p_bg, ZKN_BG_FRM_UTIL_M, 0, 0, TRUE, heap );

	// スクリーンデータ読み込み
	buff = ArcUtil_ScrnDataGet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_bg_main2_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_bg, ZKN_BG_FRM_UTIL_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_bg, ZKN_BG_FRM_UTIL_M );
}


//----------------------------------------------------------------------------
/**
 *	@brief	捕獲後画面タスク
 *
 *	@param	tcb			タスクワーク
 *	@param	p_work		データワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_TCB( TCB_PTR tcb, void* p_work )
{
	ZKN_FIGHT_TEXT_DRAW* p_zftd = p_work;
	BOOL check;
	
	switch( p_zftd->seq ){
	case ZKN_FIGHT_FADE_IN:
		// 表示ON
		G2_BlendNone();
/*		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );//*/
		p_zftd->seq++;
		break;

	case ZKN_FIGHT_FADE_IN_WAIT:
		if( ZknFight_PalFadeEndCheck( p_zftd->p_pfd, p_zftd->p_ssp ) ){
			p_zftd->seq++;
		}
		break;

	case ZKN_FIGHT_SND_PLY:
		check = Snd_PMVoicePlayEx( PV_ZUKAN_NORMAL, p_zftd->monsno, PV_PTN_PARAM_NONE, 
								   PV_PTN_PARAM_NONE, PV_PTN_PARAM_NONE );	//ぺラップ(default)
		GF_ASSERT( check );
		p_zftd->seq++;
		break;
		
	case ZKN_FIGHT_SND_WAIT:
		if( Snd_PMVoicePlayCheck() == 0 ){
			p_zftd->seq++;
		}
		break;

	case ZKN_FIGHT_END:
		break;

	default:
		break;
	}

	// パレットアニメフラグ
	if( p_zftd->palanm_flag ){
		// パレットアニメ
		ZknFight_MainPalAnm( &p_zftd->palanm );
	}

	// セルアクター描画
	CLACT_Draw( p_zftd->clact_set );
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレットフェード用ワーク作成
 *
 *	@param	pfd		パレットフェードワーク
 *	@param	ssp		ソフトウェアスプライト
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PalFadeWorkSet( PALETTE_FADE_PTR pfd, SOFT_SPRITE* ssp )
{
	PaletteWorkSet_VramCopy( pfd, FADE_MAIN_BG, 0, 32 * 0x10 );
	PaletteWorkSet_VramCopy( pfd, FADE_MAIN_OBJ, 0, BATTLE_MAIN_OBJPAL_SIZE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレットフェード　フェードインリクエスト
 *
 *	@param	pfd		パレットフェードシステム
 *	@param	ssp		ソフトウェアスプライト
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PalFadeReq( PALETTE_FADE_PTR pfd, SOFT_SPRITE* ssp, int ssp_s_evy, int s_evy, int e_evy, int wait, int rgb )
{
	SoftSpritePalFadeSet( ssp, ssp_s_evy, e_evy, wait, rgb );
	PaletteFadeReq( pfd, PF_BIT_MAIN_BG|PF_BIT_MAIN_OBJ, 0xffff, wait, s_evy, e_evy, rgb );

	// 全転送はしない
	PaletteTrans_AutoSet( pfd, FALSE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレットフェード終了チェック
 *
 *	@param	pfd		パレットフェード
 *	@param	ssp		ソフトウェアスプライト
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL ZknFight_PalFadeEndCheck( PALETTE_FADE_PTR pfd, SOFT_SPRITE* ssp )
{
	BOOL check[2];

	check[0] = PaletteFadeCheck( pfd );
	check[1] = SoftSpritePalFadeExist( ssp );

	if( (check[0] == FALSE) &&
		(check[1] == FALSE) ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	文字列描画
 *
 *	@param	p_bmp		書き込み先
 *	@param	heap		ヒープ
 *	@param	monsno		モンスターナンバー 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_TextSetUp( GF_BGL_BMPWIN* p_bmp, int heap, int monsno )
{
	ZknZukanSetUpFontBg_Minute( p_bmp, monsno, heap, 0, ZKN_BG_FIGHT_FONT_COLOR_MSK );

	// ポケモン図鑑の　登録　完了
	ZknFight_FontSetPokeTitle( p_bmp, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン図鑑の　登録　完了
 *
 *	@param	p_bmp		ビットマップ	
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_FontSetPokeTitle( GF_BGL_BMPWIN* p_bmp, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_FIGHT_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);

	//	ポケモン図鑑の　登録　完了
	MSGMAN_GetString( man, ZKN_POKEGET_00, str );
	GF_STR_PrintColor( p_bmp, FONT_SYSTEM, str, ZKN_FIGHT_TITLE_TEXT_X, ZKN_FIGHT_TITLE_TEXT_Y, 0, ZKN_BG_FIGHT_FONT_COLOR2_MSK, NULL );

	STRBUF_Delete(str);
	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ソフトウェアスプライト　の初期化
 *
 *	@param	p_ssp		ソフトウェアスプライト
 *	@param	p_pp		ポケモンパラメータ
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	heap		ヒープ
 *
 *	@return	SOFT_SPRITE
 */
//-----------------------------------------------------------------------------
static SOFT_SPRITE* ZknFight_InitSoftSprite( SOFT_SPRITE_MANAGER* p_ssp, POKEMON_PARAM* p_pp, int x, int y, int heap )
{
	SOFT_SPRITE_ARC arc;
	
	PokeGraArcDataGetPP( &arc, p_pp, PARA_FRONT );
		
	return SoftSpriteAdd( p_ssp,
					&arc,
					x, y, 0,
					0,
					NULL,
					NULL);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンナンバーを取得する
 *
 *	@param	mode	モード
 *	@param	p_pp	ポケモンパラメータ
 *
 *	@return	ポケモンナンバー
 */
//-----------------------------------------------------------------------------
static int ZknFight_GetPokemonNumber( u32 mode, POKEMON_PARAM* p_pp )
{
	int monsno;
	
	monsno = PokeParaGet( p_pp, ID_PARA_monsno, NULL );
	return PMNumber_GetPokeNumber( mode, monsno );
}

//----------------------------------------------------------------------------
/**
 *	@brief	キャラクタマネージャ初期化
 *
 *	@param	heap	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_InitCharManager( int heap )
{
	CHAR_MANAGER_MAKE init = {
		ZKN_FIGHT_CHAR_WORKNUM,
		ZKN_FIGHT_CHAR_AREA_SIZE_MAIN,
		ZKN_FIGHT_CHAR_AREA_SIZE_SUB,
		0
	};
	init.heap = heap;
	InitCharManagerReg( &init, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_32K );
}

//----------------------------------------------------------------------------
/**
 *	@brief	キャラクタマネージャ破棄
 *
 *	@param	none 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknFight_DeleteCharManager( void )
{
	DeleteCharManager();
}


//----------------------------------------------------------------------------
/**
 *	@brief	パレットアニメ初期化
 *
 *	@param	p_data	ワーク
 *	@param	heap	ヒープ
 *	@param	poke_num_mode ポケモンナンバーモード
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_InitPalAnm( ZKN_PALANM_WORK* p_data, int heap, int poke_num_mode )
{
	int i;
	
	// 1フレ目
	if( poke_num_mode == PM_NUMBER_SHINOU ){
		p_data->p_pltt_buff[ZKN_FIGHT_PALANM_ONE] = ArcUtil_PalDataGet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_sin_NCLR, &p_data->p_plt[ZKN_FIGHT_PALANM_ONE], heap );
	}else{
		p_data->p_pltt_buff[ZKN_FIGHT_PALANM_ONE] = ArcUtil_PalDataGet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_zen_NCLR, &p_data->p_plt[ZKN_FIGHT_PALANM_ONE], heap );
	}
	
	// 2フレ目
	p_data->p_pltt_buff[ZKN_FIGHT_PALANM_TWO] = ArcUtil_PalDataGet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_get_NCLR, &p_data->p_plt[ZKN_FIGHT_PALANM_TWO], heap );


	p_data->count = 0;
	p_data->now_set = 0;
	for( i=0; i<ZKN_FIGHT_PALANM_NUM; i++ ){
		p_data->anmtbl[ i ] = (i+1) * ZKN_FIGHT_PALANM_TIMING;
	}

	// パレット転送
	ZknFight_TransPalAnm( p_data, p_data->now_set );
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレットアニメメイン
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_MainPalAnm( ZKN_PALANM_WORK* p_data )
{
	// アニメ制御
	if( p_data->anmtbl[ p_data->now_set ] <= p_data->count ){

		// アニメ更新
		p_data->now_set ++;

		if( p_data->now_set >= ZKN_FIGHT_PALANM_NUM ){
			p_data->now_set = 0;
			p_data->count = 0;
		}
		// アニメ転送
		ZknFight_TransPalAnmVblank( p_data, p_data->now_set );
//		ZknFight_TransPalAnm( p_data, p_data->now_set );		
	}else{
		// カウントアップ
		p_data->count ++;	
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレットアニメ破棄
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_DeletePalAnm( ZKN_PALANM_WORK* p_data )
{
	int i;
	
	for( i=0; i<ZKN_FIGHT_PALANM_NUM; i++ ){
		sys_FreeMemoryEz( p_data->p_pltt_buff[ZKN_FIGHT_PALANM_ONE] );
	}
	memset( p_data, 0, sizeof(ZKN_PALANM_WORK) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレット転送
 *
 *	@param	p_data	ワーク
 *	@param	frm		設定フレーム
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_TransPalAnm( ZKN_PALANM_WORK* p_data, int frm )
{
	GX_LoadBGPltt(
			p_data->p_plt[ frm ]->pRawData,
			ZKN_FIGHT_PALANN_PAL * 32,
			ZKN_FIGHT_PALANN_PAL_NUM * 32 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレット転送
 *
 *	@param	p_data	ワーク
 *	@param	frm		設定フレーム
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_TransPalAnmVblank( ZKN_PALANM_WORK* p_data, int frm )
{
	AddVramTransferManager(
			NNS_GFD_DST_2D_BG_PLTT_MAIN,
			ZKN_FIGHT_PALANN_PAL * 32,
			p_data->p_plt[ frm ]->pRawData,
			ZKN_FIGHT_PALANN_PAL_NUM * 32 );
}
