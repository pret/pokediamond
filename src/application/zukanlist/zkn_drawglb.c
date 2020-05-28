//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_drawglb.c
 *	@brief		図鑑描画グローバルデータ
 *	@author		tomoya takahashi
 *	@data		2006.01.19
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/gflib/display.h"
#include "include/poketool/poke_tool.h"
#include "include/system/fontproc.h"
#include "include/application/zukanlist/zukan.naix"
#include "include/system/arc_util.h"

#include "include/application/zukanlist/zkn_drawglb.h"

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
#define ZKN_DRAWGLB_POKEGRA_BACK_OFS	(0)


// カーソルアニメ
#define ZKN_CURSOR_ANM_COUNT_HALF	( 32 )		// 動くカウンタの中間
#define ZKN_CURSOR_ANM_COUNT_MAX	( ZKN_CURSOR_ANM_COUNT_HALF*2 )		// 動くカウンタの最大
#define ZKN_CURSOR_ANM_DIS			( 4 )		// カーソルアニメの動き幅
#define ZKN_CORSOR_ANM_TCB_PRI		( 1 )		// タスク優先順位

// カーソル座標変更動作
#define ZKN_CURSOR_MOVE_SYNC		( 3 )		// 動作シンク数
#define ZKN_CORSOR_MOVE_TCB_PRI		( 0 )		// タスク優先順位

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void ZknBgSetUp( GF_BGL_INI* p_bg, int heap );
static void ZknBgRelease( GF_BGL_INI* p_bg );

static void ZknFontBgBmpWinMake( ZKN_GLB_DRAWDATA* p_drawglb, int heap );
static void ZknFontBgBmpWinDelete( ZKN_GLB_DRAWDATA* p_drawglb );

static void ZknSoftSpriteInit( ZKN_GLB_DRAWDATA* p_drawglb, int heap );
static void ZknSoftSpriteDelete( ZKN_GLB_DRAWDATA* p_drawglb );

static void ZknPokeNameTblResLoad( ZKN_GLB_DRAWDATA* p_draw, int heap );
static void ZknPokeNameTblResRelease( ZKN_GLB_DRAWDATA* p_draw );
static void ZknPokeNameTblActAdd( ZKN_GLB_DRAWDATA* p_draw, int heap );
static void ZknPokeNameTblActDelete( ZKN_GLB_DRAWDATA* p_draw );

static void ZknCursorResInit( ZKN_GLB_DRAWDATA* p_draw, int heap );
static void ZknCursorResDelete( ZKN_GLB_DRAWDATA* p_draw );
static void ZknCursorActInit( ZKN_GLB_DRAWDATA* p_draw, int heap );
static void ZknCursorActDelete( ZKN_GLB_DRAWDATA* p_draw );
static void ZknCursorAnmAdd( ZKN_GLB_DRAWDATA* p_draw );
static void ZknCursorAnmDelete( ZKN_GLB_DRAWDATA* p_draw );
static void ZknCursorAnmTcb( TCB_PTR tcb, void* work );
static void ZknCursorSetMatrixLocal( ZKN_UTIL_CURSOR_OBJ* p_obj, int def_x, int def_y, int size_x, int size_y );
static void ZknCursorMoveTcbAdd( ZKN_GLB_DRAWDATA* p_draw );
static void ZknCursorMoveTcbDelete( ZKN_GLB_DRAWDATA* p_draw );
static void ZknCursorMoveSet( ZKN_GLB_DRAWDATA* p_draw, int x, int y, int size_x, int size_y );
static void ZknCursorMoveTcb( TCB_PTR tcb, void* p_work );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑描画グローバルデータ初期化
 *
 *	@param	p_draw		描画グローバルデータ
 *	@param	heap		ヒープID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_GlbDrawDataInit( ZKN_GLB_DRAWDATA* p_draw, int heap )
{
	GF_BGL_SYS_HEADER bg_header;
	ZKN_FONTOAM_SYS_INIT fontoam_init;

	// グラフィックファイルヒープハンドルオープン
	p_draw->p_graphic_arc_handl = ArchiveDataHandleOpen( ARC_ZUKAN_GRA, heap );


	// BGシステムの作成
	p_draw->p_bg = GF_BGL_BglIniAlloc( heap );

	// BGセットアップ
	bg_header.dispMode	= GX_DISPMODE_GRAPHICS;
	bg_header.bgMode	= GX_BGMODE_0;
	bg_header.bgModeSub	= GX_BGMODE_1;
	bg_header.bg0_2Dor3D= GX_BG0_AS_3D;
	GF_BGL_InitBG( &bg_header );

	// BG初期化
	ZknBgSetUp( p_draw->p_bg, heap );

	// font画面用ビットマップ作成
	ZknFontBgBmpWinMake( p_draw, heap );

	// セルアクターセット
	p_draw->clact_set = CLACT_U_SetEasyInit( ZKN_CLACT_SET_WORK_NUM, &p_draw->oam_rend, heap );

	// セルアクター用リソース管理システム
	p_draw->res_manager[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerInit( ZKN_CLACT_RES_DATA_TBL_NUM, CLACT_U_CHAR_RES, heap );
	p_draw->res_manager[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerInit( ZKN_CLACT_RES_DATA_TBL_NUM, CLACT_U_PLTT_RES, heap );
	p_draw->res_manager[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerInit( ZKN_CLACT_RES_DATA_TBL_NUM, CLACT_U_CELL_RES, heap );
	p_draw->res_manager[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerInit( ZKN_CLACT_RES_DATA_TBL_NUM, CLACT_U_CELLANM_RES, heap );

	// OBJON
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

	// フォントOAMシステム作成
	fontoam_init.clact_set	= p_draw->clact_set;
	fontoam_init.p_bg		= p_draw->p_bg;
	fontoam_init.work_num	= ZKN_FONTOAM_WORK_NUM;
	fontoam_init.heap		= heap;
	p_draw->fontoam_sys = ZKN_FONTOAM_InitSys( &fontoam_init );

	// フォントデータ読み込み
	FontProc_LoadFont( FONT_BUTTON, heap );
	

	// ソフトウェアマネージャ
	ZknSoftSpriteInit( p_draw, heap );


	// ポケモンリスト用リソース読み込み＆アクター登録
	ZknPokeNameTblResLoad( p_draw, heap );
	ZknPokeNameTblActAdd( p_draw, heap );

	// カーソル用リソース読み込み＆アクター登録
	ZknCursorResInit( p_draw, heap );
	ZknCursorActInit( p_draw, heap );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑グローバル描画データ破棄
 *
 *	@param	p_draw		描画グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_GlbDrawDataDelete( ZKN_GLB_DRAWDATA* p_draw )
{
	
	// アクター破棄＆リソース破棄
	ZknPokeNameTblActDelete( p_draw );
	ZknPokeNameTblResRelease( p_draw );

	// カーソル用リソース破棄＆アクター破棄
	ZknCursorActDelete( p_draw );
	ZknCursorResDelete( p_draw );
	
	// 文字列描画用ビットマップ破棄
	ZknFontBgBmpWinDelete( p_draw );

	// BG破棄
	ZknBgRelease( p_draw->p_bg );

	
	// BGシステム
	sys_FreeMemoryEz( p_draw->p_bg );

	// セルアクターセット
	CLACT_DestSet( p_draw->clact_set );

	// セルアクター用リソース管理システム
	CLACT_U_ResManagerDelete( p_draw->res_manager[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerDelete( p_draw->res_manager[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerDelete( p_draw->res_manager[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerDelete( p_draw->res_manager[ CLACT_U_CELLANM_RES ] );

	// FONTOAM
	ZKN_FONTOAM_DeleteSys( p_draw->fontoam_sys );

	// 文字列フォント破棄
	FontProc_UnloadFont( FONT_BUTTON );

	// ソフトウェアマネージャ
	ZknSoftSpriteDelete( p_draw );

	// アーカイブハンドルを閉じる
	ArchiveDataHandleClose( p_draw->p_graphic_arc_handl );

	memset( p_draw, 0, sizeof( ZKN_GLB_DRAWDATA ) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑描画グローバルデータ　内描画システム　描画処理
 *
 *	@param	p_draw	描画グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_GlbDrawDataMain( ZKN_GLB_DRAWDATA* p_draw )
{
	// セルアクター描画
	CLACT_Draw( p_draw->clact_set );
	
	// カメラセットアップ
	NNS_G2dSetupSoftwareSpriteCamera();
	
	// ソフトウェアスプライト描画
	SoftSpriteMain( p_draw->soft_sprite_man );
	SWSP_SysDraw( p_draw->swsp_sys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	VBlank関数
 *
 *	@param	p_draw		描画グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_GlbDrawDataVBlank( ZKN_GLB_DRAWDATA* p_draw )
{
	GF_BGL_VBlankFunc( p_draw->p_bg );

	// ソフトウェアスプライト
	SoftSpriteTextureTrans( p_draw->soft_sprite_man );
}



//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック設定
 *
 *	@param	p_draw		描画データ
 *	@param	mons_no		モンスターナンバー
 *	@param	sex			性別		-1のときデフォ
 *	@param	dir			方向
 *	@param	col			レアカラーか
 *	@param	form_no		フォームナンバー　関係ないとき０
 *	@param	rnd			固体乱数			関係ないとき０
 *
 *	@return	none
 *
 *	sex
		PARA_MALE=0,		おす
		PARA_FEMALE,		めす
		PARA_UNK,			なぞ

	dir
		PARA_FRONT:正面
		PARA_BACK:背面
	
	col
		PARA_NORMAL:ノーマル
		PARA_RARE:レア
 */
//----------------------------------------------------------------------------
void ZKN_GlbPokemonGraphicSet( ZKN_GLB_DRAWDATA* p_draw, int mons_no, int sex, int dir, int col, u8 form_no, u32 rnd, int x, int y )
{
	ZKN_GlbPokemonGraphicSet_Idx( p_draw, mons_no, sex, dir, col, form_no, rnd, x, y, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケグラ座標を設定
 *
 *	@param	p_draw	描画グローバル
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokemonGraphicSetMatrix( ZKN_GLB_DRAWDATA* p_draw, int x, int y )
{
	ZKN_GlbPokemonGraphicSetMatrix_Idx( p_draw, x, y, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケグラ座標を取得
 *
 *	@param	p_draw	描画グローバル
 *	@param	x		ｘ座標格納先
 *	@param	y		ｙ座標格納先
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokemonGraphicGetMatrix( ZKN_GLB_DRAWDATA* p_draw, int* x, int* y )
{
	ZKN_GlbPokemonGraphicGetMatrix_Idx( p_draw, x, y, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンオブジェクト取得
 *
 *	@param	p_draw	描画データ
 *
 *	@return	ソフトウェアスプライト
 */
//-----------------------------------------------------------------------------
SOFT_SPRITE* ZKN_GlbPokemonGraphicGet( const ZKN_GLB_DRAWDATA* cp_draw )
{
	return ZKN_GlbPokemonGraphicGet_Idx( cp_draw, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画フラグ設定
 *
 *	@param	cp_draw
 *	@param	flag 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokemonGraphicDrawFlagSet( const ZKN_GLB_DRAWDATA* cp_draw, BOOL flag )
{
	ZKN_GlbPokemonGraphicDrawFlagSet_Idx( cp_draw, flag, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック設定
 *
 *	@param	p_draw		描画データ
 *	@param	mons_no		モンスターナンバー
 *	@param	sex			性別		-1のときデフォ
 *	@param	dir			方向
 *	@param	col			レアカラーか
 *	@param	form_no		フォームナンバー	関係ないとき０
 *	@param	rnd			固体乱数			関係ないとき０
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	idx			インデックス
 *
 *	@return	none
 *
 *	sex
		PARA_MALE=0,		おす
		PARA_FEMALE,		めす
		PARA_UNK,			なぞ

	dir
		PARA_FRONT:正面
		PARA_BACK:背面
	
	col
		PARA_NORMAL:ノーマル
		PARA_RARE:レア
 */
//----------------------------------------------------------------------------
void ZKN_GlbPokemonGraphicSet_Idx( ZKN_GLB_DRAWDATA* p_draw, int mons_no, int sex, int dir, int col, u8 form_no, u32 rnd, int x, int y, int idx )
{
	SOFT_SPRITE_ARC poke_arc;
	s16 height;
	
	// 今までのを破棄
	if( p_draw->soft_sprite[idx] ){
		SoftSpriteDel( p_draw->soft_sprite[idx] );
	}

	// sex が -1のときは普通の性別を設定
	if( sex == -1 ){
		sex = PokeSexGetMonsNo( mons_no, 0 );
	}

	// ポケモングラフィックデータ取得
	PokeGraArcDataGet( &poke_arc, mons_no, sex, dir, col, form_no, rnd );		//最後の引数は、FormNoと個性乱数です by soga 2006.05.01 確認しました by tomoya

	// 高さ調整
	if( dir == PARA_BACK ){
		height = PokeHeightGet( mons_no, sex, dir, form_no, rnd);
		height += ZKN_DRAWGLB_POKEGRA_BACK_OFS;	// 図鑑での高さに
	}else{
		height = 0;
	}

	// 登録
	p_draw->soft_sprite[idx] = SoftSpriteAdd( 
			p_draw->soft_sprite_man,
			&poke_arc,
			x, y+height, 0, 0,
			NULL, NULL
			);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケグラ座標を設定
 *
 *	@param	p_draw	描画グローバル
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標
 *	@param	idx		インデックス
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokemonGraphicSetMatrix_Idx( ZKN_GLB_DRAWDATA* p_draw, int x, int y, int idx )
{
	SoftSpriteParaSet( p_draw->soft_sprite[idx], SS_PARA_POS_X, x );
	SoftSpriteParaSet( p_draw->soft_sprite[idx], SS_PARA_POS_Y, y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケグラ座標を取得
 *
 *	@param	p_draw	描画グローバル
 *	@param	x		ｘ座標格納先
 *	@param	y		ｙ座標格納先
 *	@param	idx		インデックス
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokemonGraphicGetMatrix_Idx( ZKN_GLB_DRAWDATA* p_draw, int* x, int* y, int idx )
{
	*x = SoftSpriteParaGet( p_draw->soft_sprite[idx], SS_PARA_POS_X );
	*y = SoftSpriteParaGet( p_draw->soft_sprite[idx], SS_PARA_POS_Y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンオブジェクト取得
 *
 *	@param	p_draw	描画データ
 *	@param	idx		インデックス
 *
 *	@return	ソフトウェアスプライト
 */
//-----------------------------------------------------------------------------
SOFT_SPRITE* ZKN_GlbPokemonGraphicGet_Idx( const ZKN_GLB_DRAWDATA* cp_draw, int idx )
{
	return cp_draw->soft_sprite[idx];
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画フラグ設定
 *
 *	@param	cp_draw
 *	@param	flag 
 *	@param	idx			インデックス
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokemonGraphicDrawFlagSet_Idx( const ZKN_GLB_DRAWDATA* cp_draw, BOOL flag, int idx )
{
	if( cp_draw->soft_sprite[idx] == NULL ){
		return ;
	}
	
	if( flag == TRUE ){
		SoftSpriteParaSet( cp_draw->soft_sprite[idx], SS_PARA_VANISH, FALSE );
	}else{
		SoftSpriteParaSet( cp_draw->soft_sprite[idx], SS_PARA_VANISH, TRUE );
	}
}




//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン名リストのテーブルアクター取得
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	アクター
 */
//-----------------------------------------------------------------------------
CLACT_WORK_PTR ZKN_GlbPokeNameTblClactGet( const ZKN_GLB_DRAWDATA* p_draw )
{
	GF_ASSERT( p_draw->pokelist_data_draw.pokelist_tbl );

	return p_draw->pokelist_data_draw.pokelist_tbl;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン名リストのアイコンアクター取得
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	アクター
 */
//-----------------------------------------------------------------------------
CLACT_WORK_PTR ZKN_GlbPokeNameIconClactGet( const ZKN_GLB_DRAWDATA* p_draw )
{
	GF_ASSERT( p_draw->pokelist_data_draw.pokelist_icon );

	return p_draw->pokelist_data_draw.pokelist_icon;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン名設定
 *
 *	@param	p_draw			描画グローバル
 *	@param	p_fontoam_init	ふぉんとOAM初期化データ
 *	@param	char_size		キャラクタ転送領域サイズ
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblSet( ZKN_GLB_DRAWDATA* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, int char_size, int mons_no, u32 zkn_mode )
{
	ZKN_GlbPokeNameTblSet_Minute( &p_draw->pokelist_data_draw, p_fontoam_init, char_size, mons_no, zkn_mode );
}


//----------------------------------------------------------------------------
/**
 *	@brief	実際にポケモン名設定
 *
 *	@param	p_data				データ
 *	@param	p_fontoam_init		フォント初期化データ
 *	@param	char_size			キャラクタサイズ
 *	@param	mons_no				モンスターナンバー 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblSet_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, ZKN_FONTOAM_INIT* p_fontoam_init, int char_size, int mons_no, u32 zkn_mode )
{
	// モンスターが一緒なら何もしない
	if( (mons_no == p_data->mons_no) && (zkn_mode == p_data->zkn_mode) ){
		FONTOAM_SetDrawFlag( p_data->p_pokename->p_fontoam, TRUE );
		return ;
	}else{
		p_data->mons_no = mons_no;
		p_data->zkn_mode = zkn_mode;
	}
	
	// 今までのを破棄
	if( p_data->p_pokename ){
		ZKN_FONTOAM_Delete( p_data->p_pokename );
	}
	
	if( char_size != 0 ){
		p_data->p_pokename = ZKN_FONTOAM_MakeCharOfs( p_fontoam_init, char_size );
	}else{
		p_data->p_pokename = ZKN_FONTOAM_Make( p_fontoam_init );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン名OAMデータ取得
 *
 *	@param	p_draw 描画グローバル
 *
 *	@return	OAMデータ
 */
//-----------------------------------------------------------------------------
ZKN_FONTOAM_DATA* ZKN_GlbPokeNameTblGet( const ZKN_GLB_DRAWDATA* p_draw )
{
	GF_ASSERT( p_draw->pokelist_data_draw.p_pokename );

	return  p_draw->pokelist_data_draw.p_pokename;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン名テーブル用リソースオブジェ取得
 *
 *	@param	p_draw		描画グローバル
 *	@param	res_type	リソースタイプ
 *
 *	@return	リソースオブジェ
 *
 *	res_type
		CLACT_U_CHAR_RES,		// キャラクタリソースを管理
		CLACT_U_PLTT_RES,		// パレットリソースを管理
		CLACT_U_CELL_RES,		// セルリソースを管理
		CLACT_U_CELLANM_RES,	// セルアニメリソースを管理
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR ZKN_GlbPokeNameTblResObjGet( const ZKN_GLB_DRAWDATA* p_draw, int res_type )
{
	GF_ASSERT( res_type <= CLACT_U_CELLANM_RES );
	
	return p_draw->pokelist_data_draw.pokelist_res_obj[ res_type ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン名テーブルのOAMモードを設定
 *
 *	@param	p_draw	描画グローバル
 *	@param	mode	OAMモード
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblObjModeSet( const ZKN_GLB_DRAWDATA* p_draw, GXOamMode mode )
{
	CLACT_ObjModeSet( p_draw->pokelist_data_draw.pokelist_tbl, mode );
	CLACT_ObjModeSet( p_draw->pokelist_data_draw.pokelist_icon, mode );
	FONTOAM_ObjModeSet( p_draw->pokelist_data_draw.p_pokename->p_fontoam, mode );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン名リストのBG優先順位設定
 *
 *	@param	p_draw	描画ワーク
 *	@param	pri		描画BGpriority
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblBGPriSet( const ZKN_GLB_DRAWDATA* p_draw, int pri )
{
	CLACT_BGPriorityChg( p_draw->pokelist_data_draw.pokelist_tbl, pri );
	CLACT_BGPriorityChg( p_draw->pokelist_data_draw.pokelist_icon, pri );
	FONTOAM_SetBGPriority( p_draw->pokelist_data_draw.p_pokename->p_fontoam, pri );
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画フラグ設定
 *
 *	@param	p_draw
 *	@param	flag 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblDrawFlagSet( const ZKN_GLB_DRAWDATA* p_draw, BOOL flag )
{
	if( p_draw->pokelist_data_draw.pokelist_tbl ){
		CLACT_SetDrawFlag( p_draw->pokelist_data_draw.pokelist_tbl, flag );
	}
	if( p_draw->pokelist_data_draw.pokelist_icon ){
		CLACT_SetDrawFlag( p_draw->pokelist_data_draw.pokelist_icon, flag );
	}
	if( p_draw->pokelist_data_draw.p_pokename->p_fontoam ){
		FONTOAM_SetDrawFlag( p_draw->pokelist_data_draw.p_pokename->p_fontoam, flag );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑ユーティティ　独自フェードイン　アウトシステム
 *
 *	@param	p_fade		フェードデータ
 *	@param	sync		シンク数
 *	@param	brightness_sブライトネス開始値
 *	@param	brightness_eブライトネス終了値
 *	@param	s_alpha		開始α値	
 *	@param	e_alpha		終了α値	
 *	@param	plane1		α対称面１	
 *	@param	plane2		α対称面２	（対称面２は絶対にBDが加えられます）
 *	@param	disp_flag	メインかサブか
 *
 *	@return	none
 *
 *	disp_flag
	ZKN_UTIL_FADE_MAIN,
	ZKN_UTIL_FADE_SUB,
 */
//-----------------------------------------------------------------------------
void ZKN_GLB_ChangeFadeRequest( ZKN_UTIL_FADE_SYS* p_fade, u8 sync, int brightness_s, int brightness_e, int s_alpha, int e_alpha, BRIGHT_PLANEMASK plane1, BRIGHT_PLANEMASK plane2, int disp_flag )
{
	// メインかサブか
	p_fade->disp_flag = disp_flag;

	// 対称面
	p_fade->plane1 = plane1;
	p_fade->plane2 = plane2 | PLANEMASK_BD;
	
	// フェードデータ
	p_fade->brightness_s		= brightness_s;
	p_fade->brightness_dis		= brightness_e - brightness_s;
	p_fade->alpha_s				= s_alpha;
	p_fade->alpha_dis			= e_alpha - s_alpha;
	p_fade->count_max			= sync;
	p_fade->count				= 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑ユーティティ　独自フェードイン　アウトシステム
 *
 *	@param	p_fade	フェードデータ
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLB_ChangeFadeMain( ZKN_UTIL_FADE_SYS* p_fade )
{
	int set_alpha, set_brightness;

	if( ZKN_GLB_ChangeFadeEndCheck( p_fade ) == FALSE ){
		
		set_alpha = ZKN_GLB_GetFadeAlpha( p_fade );
		set_brightness = ZKN_GLB_GetFadeBrightness( p_fade );

		// 設定
		if( p_fade->disp_flag == ZKN_UTIL_FADE_MAIN ){
			G2_SetBlendBrightnessExt( p_fade->plane1, p_fade->plane2,
					set_alpha, 0,
					set_brightness );
		}else{
			G2S_SetBlendBrightnessExt( p_fade->plane1, p_fade->plane2,
					set_alpha, 0,
					set_brightness );
		}

		// カウント
		p_fade->count++;
	}

	return ZKN_GLB_ChangeFadeEndCheck( p_fade );
}

//----------------------------------------------------------------------------
/**
 *	@brief	今のα値を取得
 *
 *	@param	p_fade 
 *
 *	@return	α値
 */
//-----------------------------------------------------------------------------
int ZKN_GLB_GetFadeAlpha( ZKN_UTIL_FADE_SYS* p_fade )
{
	fx32 alpha;

	alpha = FX_Mul( p_fade->alpha_dis << FX32_SHIFT, p_fade->count << FX32_SHIFT );
	alpha = FX_Div( alpha, p_fade->count_max << FX32_SHIFT );

	return (alpha >> FX32_SHIFT) + p_fade->alpha_s;
}

//----------------------------------------------------------------------------
/**
 *	@brief	今のブライトネス値を取得
 *
 *	@param	p_fade 
 *
 *	@return	ブライトネス値
 */
//-----------------------------------------------------------------------------
int ZKN_GLB_GetFadeBrightness( ZKN_UTIL_FADE_SYS* p_fade )
{
	fx32 brightness;

	brightness = FX_Mul( p_fade->brightness_dis << FX32_SHIFT, p_fade->count << FX32_SHIFT );
	brightness = FX_Div( brightness, p_fade->count_max << FX32_SHIFT );
	
	return (brightness >> FX32_SHIFT) + p_fade->brightness_s;
}

//----------------------------------------------------------------------------
/**
 *	@brief	終了チェック
 *
 *	@param	p_fade	フェードワーク
 *
 *	@retval TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLB_ChangeFadeEndCheck( ZKN_UTIL_FADE_SYS* p_fade )
{
	if( p_fade->count <= p_fade->count_max ){
		return FALSE;
	}

	return TRUE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケグラパレットフェード値を設定
 *
 *	@param	p_draw		描画グローバル
 *	@param	p_fade		フェードデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GLB_SpritePokeGraPalFade( const ZKN_GLB_DRAWDATA* p_draw, ZKN_UTIL_FADE_SYS* p_fade )
{
	SOFT_SPRITE* ssp;
	int brightness;

	brightness = -ZKN_GLB_GetFadeBrightness( p_fade );
	
	// ポケモンソフトパレットフェード
	ssp = ZKN_GlbPokemonGraphicGet( p_draw );
	SoftSpritePalFadeSet( ssp, brightness, brightness, 0, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケグラパレットフェード値を設定
 *
 *	@param	p_draw		描画グローバル
 *	@param	p_fade		フェードデータ
 *	@param	idx			インデックス
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GLB_SpritePokeGraPalFade_Idx( const ZKN_GLB_DRAWDATA* p_draw, ZKN_UTIL_FADE_SYS* p_fade, int idx )
{
	SOFT_SPRITE* ssp;
	int brightness;

	brightness = -ZKN_GLB_GetFadeBrightness( p_fade );
	
	// ポケモンソフトパレットフェード
	ssp = ZKN_GlbPokemonGraphicGet_Idx( p_draw, idx );
	SoftSpritePalFadeSet( ssp, brightness, brightness, 0, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソルオブジェクトに座標を設定
 *
 *	@param	cp_cursor	カーソルシステム
 *	@param	p_draw		描画グローバル
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_CursorSetMatrixCursorSys( const ZKN_CURSOR* cp_cursor, ZKN_GLB_DRAWDATA* p_draw )
{
	int x,y,size_x,size_y;
	
	// 座標とサイズを取得
	ZKN_CURSOR_GetMat( cp_cursor, &x, &y );
	ZKN_CURSOR_GetSize( cp_cursor, &size_x, &size_y );
	ZKN_UTIL_CursorSetMatrix( p_draw, x, y, size_x, size_y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル座標を設定
 *
 *	@param　p_draw		描画グローバル	
 *	@param	def_x		デフォルトＸ
 *	@param	def_y		デフォルトＹ
 *	@param	size_x		カーソルサイズＸ
 *	@param	size_y		カーソルサイズＹ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_CursorSetMatrix( ZKN_GLB_DRAWDATA* p_draw, int def_x, int def_y, int size_x, int size_y )
{
	ZknCursorMoveSet( p_draw, def_x, def_y, size_x, size_y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画ＯＮＯＦＦ
 *
 *	@param	p_obj	描画オブジェ
 *	@param	flag	フラグ
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_CursorSetDrawFlag( ZKN_UTIL_CURSOR_OBJ* p_obj, int flag )
{
	int i;

	// 描画ＯＮＯＦＦ
	for( i=0; i<ZKN_CURROS_MAT_RECT_NUM; i++ ){
		CLACT_SetDrawFlag( p_obj->cursor[i], flag );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画ONOFF取得
 *
 *	@param	p_obj	オブジェクト
 *
 *	@retval	TRUE	描画ON
 *	@retval	FALSE	描画OFF
 */
//-----------------------------------------------------------------------------
BOOL ZKN_UTIL_CursorGetDrawFlag( ZKN_UTIL_CURSOR_OBJ* p_obj )
{
	return CLACT_GetDrawFlag( p_obj->cursor[0] );	// 代表して0
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作アニメＯＮＯＦＦフラグ
 *
 *	@param	p_obj	カーソルオブジェクト
 *	@param	anm		アニメフラグ
 *
 *	@return	none
 *
 *	anm
 *		TRUE	ストップ
 *		FALSE	再生
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_CursorSetAnimeStopFlag( ZKN_UTIL_CURSOR_OBJ* p_obj, BOOL anm )
{
	p_obj->anm_stop = anm;

	// 開始ならカウンタ初期化
	if( anm == FALSE ){
		p_obj->anm_count = 0;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	移動アニメなしの座標設定　初期化用
 *
 *	@param	cp_cursor	カーソルシステム
 *	@param	p_draw		描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_CursorSetMatrixCursorSysNotAnm( const ZKN_CURSOR* cp_cursor, ZKN_GLB_DRAWDATA* p_draw )
{
	int x, y, size_x, size_y;

	// 座標とサイズを取得
	ZKN_CURSOR_GetMat( cp_cursor, &x, &y );
	ZKN_CURSOR_GetSize( cp_cursor, &size_x, &size_y );

	// 座標設定
	ZKN_UTIL_CursorSetMatrixNotAnm( p_draw, x, y, size_x, size_y );
}
//----------------------------------------------------------------------------
/**
 *	@brief	移動アニメなしの座標設定　初期化用
 *
 *	@param	p_draw
 *	@param	def_x
 *	@param	def_y
 *	@param	size_x
 *	@param	size_y 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_CursorSetMatrixNotAnm( ZKN_GLB_DRAWDATA* p_draw, int def_x, int def_y, int size_x, int size_y )
{
	p_draw->cursor.x = def_x;
	p_draw->cursor.y = def_y;
	p_draw->cursor.size_x = size_x;
	p_draw->cursor.size_y = size_y;

	// 座標設定
	ZknCursorSetMatrixLocal( &p_draw->cursor, p_draw->cursor.x, p_draw->cursor.y,
			p_draw->cursor.size_x, p_draw->cursor.size_y );

	p_draw->cursor_move.ta_x = def_x;
	p_draw->cursor_move.ta_y = def_y;
	p_draw->cursor_move.ta_size_x = size_x;
	p_draw->cursor_move.ta_size_y = size_y;
	p_draw->cursor_move.move_stop = FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	動作
 *
 *	@param	p_work			動作ワーク
 *	@param	s_x				開始x座標
 *	@param	e_x				終了x座標
 *	@param	s_y				開始y座標
 *	@param	e_y				終了y座標
 *	@param	count_max		カウント最大値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_MoveReq( ZKN_UTIL_MOVE_WORK* p_work, int s_x, int e_x, int s_y, int e_y, int count_max )
{
	p_work->x = s_x;
	p_work->y = s_y;

	p_work->s_x = s_x;
	p_work->s_y = s_y;
	p_work->dis_x = e_x - s_x;
	p_work->dis_y = e_y - s_y;
	p_work->count_max = count_max;
	p_work->count = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作メイン
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL ZKN_UTIL_MoveMain( ZKN_UTIL_MOVE_WORK* p_work )
{
	fx32 w_x, w_y;



	// 現在座標取得
	w_x = FX_Mul( p_work->dis_x << FX32_SHIFT, p_work->count << FX32_SHIFT );
	w_x = FX_Div( w_x, p_work->count_max << FX32_SHIFT );
	w_y = FX_Mul( p_work->dis_y << FX32_SHIFT, p_work->count << FX32_SHIFT );
	w_y = FX_Div( w_y, p_work->count_max << FX32_SHIFT );

	
	p_work->x = (w_x >> FX32_SHIFT) + p_work->s_x;
	p_work->y = (w_y >> FX32_SHIFT) + p_work->s_y;

	if( (p_work->count + 1) <= p_work->count_max ){
		p_work->count++;
		return FALSE;
	}

	p_work->count = p_work->count_max;
	return TRUE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	アーカイブファイルハンドルを取得する
 *
 *	@param	p_draw	描画ﾃﾞｰﾀ
 *
 *	@return	アーカイブファイルハンドル
 */
//-----------------------------------------------------------------------------
ARCHANDLE* ZKN_GLBDATA_ArcHandlGet( ZKN_GLB_DRAWDATA* p_draw )
{
	return p_draw->p_graphic_arc_handl;
}

//------------------------------------------------------------------
/**
 * アーカイブデータの読み出し（メモリ確保する）
 *
 * @param   p_draw			描画ｸﾞﾛｰﾊﾞﾙﾃﾞｰﾀ
 * @param   dataIdx			アーカイブデータインデックス
 * @param   compressedFlag	圧縮されているか？
 * @param	heapID			使用するヒープ
 *
 * @retval  void*			読み出し領域ポインタ
 */
//------------------------------------------------------------------
void* ZKN_GLBDATA_Arc_Load(ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, BOOL compressedFlag, u32 heapID)
{
	void* arcData;
	
	arcData = ArchiveDataLoadAllocByHandle( p_draw->p_graphic_arc_handl, dataIdx, heapID );

	if( arcData != NULL )
	{
		if( compressedFlag )
		{
			void* data;

			data = sys_AllocMemory( heapID, MI_GetUncompressedSize( arcData ) );
			if( data )
			{
				MI_UncompressLZ8( arcData, data );
				sys_FreeMemoryEz( arcData );
			}
			arcData = data;
		}
	}

	return arcData;
}

//------------------------------------------------------------------
/**
 * BGｷｬﾗﾃﾞｰﾀの VRAM 転送
 *
 * @param   p_draw			描画ｸﾞﾛｰﾊﾞﾙﾃﾞｰﾀ
 * @param   dataIndex		ｱｰｶｲﾌﾞﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 * @param   bgl				BGLﾃﾞｰﾀ
 * @param   frm				転送先ﾌﾚｰﾑﾅﾝﾊﾞ
 * @param   offs			転送ｵﾌｾｯﾄ（ｷｬﾗ単位）
 * @param	transSize		転送するｻｲｽﾞ（ﾊﾞｲﾄ単位 ==0で全転送）
 * @param   compressedFlag	圧縮されているﾃﾞｰﾀか？
 * @param   heapID			ﾃﾞｰﾀ読み込み・解凍ﾃﾝﾎﾟﾗﾘとして使うﾋｰﾌﾟID
 *
 * @return  転送したデータサイズ（バイト）
 */
//------------------------------------------------------------------
u32 ZKN_GLBDATA_BgCharSet(ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID)
{
	void* arcData = ZKN_GLBDATA_Arc_Load( p_draw, dataIdx, compressedFlag, heapID );

	if( arcData != NULL )
	{
		NNSG2dCharacterData* charData;

		if( NNS_G2dGetUnpackedBGCharacterData( arcData, &charData ) )
		{
			if( transSize == 0 )
			{
				transSize = charData->szByte;
			}
			GF_BGL_LoadCharacter(bgl, frm, charData->pRawData, transSize, offs);
		}

		sys_FreeMemoryEz( arcData );
	}
    return transSize;
}
//------------------------------------------------------------------
/**
 * ﾊﾟﾚｯﾄﾃﾞｰﾀ の VRAM 転送
 *
 * @param   p_draw			描画ｸﾞﾛｰﾊﾞﾙﾃﾞｰﾀ
 * @param   dataIdx		ｱｰｶｲﾌﾞﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 * @param   palType		ﾊﾟﾚｯﾄ転送先ﾀｲﾌﾟ
 * @param   offs		ﾊﾟﾚｯﾄ転送先ｵﾌｾｯﾄ
 * @param   transSize	ﾊﾟﾚｯﾄ転送ｻｲｽﾞ（0 で全転送）
 * @param   heapID		ﾃﾞｰﾀ読み込みﾃﾝﾎﾟﾗﾘとして使うﾋｰﾌﾟID
 *
 */
//------------------------------------------------------------------
void ZKN_GLBDATA_PalSet(ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, PALTYPE palType, u32 offs, u32 transSize, u32 heapID )
{
	static void (* const load_func[])(const void*, u32, u32) = {
		GX_LoadBGPltt,
		GX_LoadOBJPltt,
		GX_LoadBGExtPltt,
		GX_LoadOBJExtPltt,
		GXS_LoadBGPltt,
		GXS_LoadOBJPltt,
		GXS_LoadBGExtPltt,
		GXS_LoadOBJExtPltt,
	};

	void* arcData = ZKN_GLBDATA_Arc_Load( p_draw, dataIdx, FALSE, heapID );

	if( arcData != NULL )
	{
		NNSG2dPaletteData* palData;

		if( NNS_G2dGetUnpackedPaletteData( arcData, &palData ) )
		{
			if( transSize == 0 )
			{
				transSize = palData->szByte;
			}
			DC_FlushRange( palData->pRawData, transSize );
			load_func[ palType ]( palData->pRawData, offs, transSize );
		}

		sys_FreeMemoryEz( arcData );
	}
}
//--------------------------------------------------------------------------------------------
/**
 * ｽｸﾘｰﾝﾃﾞｰﾀを ﾛｰﾄﾞして Unpack するだけです。解放は各自で。
 *
 * @param   p_draw			描画ｸﾞﾛｰﾊﾞﾙﾃﾞｰﾀ
 * @param   arcIndex		[in] ｱｰｶｲﾌﾞﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 * @param   compressedFlag	[in] 圧縮されているﾃﾞｰﾀか？
 * @param   scrnData		[out] ｽｸﾘｰﾝﾃﾞｰﾀｱﾄﾞﾚｽを保持するﾎﾟｲﾝﾀのｱﾄﾞﾚｽ
 * @param   heapID			[in] ﾋｰﾌﾟID
 *
 * @retval  void*		ﾛｰﾄﾞしたﾃﾞｰﾀの先頭ﾎﾟｲﾝﾀ
 */
//--------------------------------------------------------------------------------------------
void* ZKN_GLBDATA_ScrnDataGet(ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, BOOL compressedFlag, NNSG2dScreenData** scrnData, u32 heapID)
{
	void* arcData = ZKN_GLBDATA_Arc_Load( p_draw, dataIdx, compressedFlag, heapID );

	if( arcData != NULL )
	{
		if( NNS_G2dGetUnpackedScreenData( arcData, scrnData ) == FALSE )
		{
			sys_FreeMemoryEz( arcData );
			return NULL;
		}
	}
	return arcData;
}
//------------------------------------------------------------------
/**
 * ﾊﾟﾚｯﾄﾃﾞｰﾀをﾛｰﾄﾞして Unpack するだけです。解放は各自で。
 *
 * @param   p_draw			描画ｸﾞﾛｰﾊﾞﾙﾃﾞｰﾀ
 * @param   arcIndex		ｱｰｶｲﾌﾞﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 * @param   palData			ﾊﾟﾚｯﾄﾃﾞｰﾀｱﾄﾞﾚｽを保持するﾎﾟｲﾝﾀのｱﾄﾞﾚｽ
 * @param   heapID			ﾋｰﾌﾟID
 *
 * @retval  void*		ﾛｰﾄﾞしたﾃﾞｰﾀの先頭ﾎﾟｲﾝﾀ
 */
//------------------------------------------------------------------
void* ZKN_GLBDATA_PalDataGet( ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, NNSG2dPaletteData** palData, u32 heapID )
{
	void* arcData = ZKN_GLBDATA_Arc_Load( p_draw, dataIdx, FALSE, heapID );

	if( arcData != NULL )
	{
		if( NNS_G2dGetUnpackedPaletteData( arcData, palData ) == FALSE )
		{
			sys_FreeMemoryEz( arcData );
			return NULL;
		}
	}
	return arcData;
}
//------------------------------------------------------------------
/**
 * ｷｬﾗﾃﾞｰﾀを ﾛｰﾄﾞして Unpack するだけです。解放は各自で。
 *
 * @param   p_draw			描画ｸﾞﾛｰﾊﾞﾙﾃﾞｰﾀ
 * @param   dataIdx				[in] ﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 * @param   compressedFlag		[in] 圧縮されているか
 * @param   charData			[out] ｷｬﾗﾃﾞｰﾀｱﾄﾞﾚｽを保持するﾎﾟｲﾝﾀのｱﾄﾞﾚｽ
 * @param   heapID				[in] ﾋｰﾌﾟID
 *
 * @retval  void*		ﾛｰﾄﾞしたﾃﾞｰﾀの先頭ﾎﾟｲﾝﾀ
 */
//------------------------------------------------------------------
void* ZKN_GLBDATA_CharDataGet( ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, BOOL compressedFlag, NNSG2dCharacterData** charData, u32 heapID )
{
	void* arcData = ZKN_GLBDATA_Arc_Load( p_draw, dataIdx, compressedFlag, heapID );

	if( arcData != NULL )
	{
		if( NNS_G2dGetUnpackedBGCharacterData( arcData, charData ) == FALSE)
		{
			// 失敗したらNULL
			sys_FreeMemoryEz( arcData );
			return NULL;
		}
	}
	return arcData;
}




//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGデータ設定
 *
 *	@param	p_bg	BGシステム
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknBgSetUp( GF_BGL_INI* p_bg, int heap )
{
	// メイン画面 BG1面		文字列書き込み面
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
		};
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
			GX_BG_EXTPLTT_01, 1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, ZKN_BG_FRM_UTIL_M, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( ZKN_BG_FRM_UTIL_M, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_UTIL_M );
	}

	// 3D面
	GF_BGL_PrioritySet( GF_BGL_FRAME0_M, 2 );
	// BG0ON
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );


	// メイン画面 BG3面		背景面
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x14000,
			GX_BG_EXTPLTT_01, 3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, ZKN_BG_FRM_BACK_M, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( ZKN_BG_FRM_BACK_M, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_BACK_M );
	}


	// サブ画面 BG1面		ユーティリティ面
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, ZKN_BG_FRM_UTIL_S, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( ZKN_BG_FRM_UTIL_S, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_UTIL_S );
	}

	// サブ画面 BG2面		背景面
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x08000,
			GX_BG_EXTPLTT_01, 2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, ZKN_BG_FRM_BACK_S, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( ZKN_BG_FRM_BACK_S, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_BACK_S );
	}

	// サブ画面 BG3面		拡縮BG面
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x400, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0x0800, GX_BG_CHARBASE_0x10000,
			GX_BG_EXTPLTT_01, 1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, ZKN_BG_FRM_AFFINE_S, &bg_cnt_header, GF_BGL_MODE_AFFINE );
		GF_BGL_ClearCharSet( ZKN_BG_FRM_AFFINE_S, 64, 0, heap );
		GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_AFFINE_S );
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
static void ZknBgRelease( GF_BGL_INI* p_bg )
{
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_FONT_M );
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_UTIL_M );
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_BACK_M );
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_UTIL_S );
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_AFFINE_S );
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_BACK_S );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	文字列描画用ビットマップ作成
 *
 *	@param	p_drawglb	描画グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknFontBgBmpWinMake( ZKN_GLB_DRAWDATA* p_drawglb, int heap )
{
	// ビットマップウィンドウ登録
	GF_BGL_BmpWinAdd( p_drawglb->p_bg, &p_drawglb->bmp_mfont,
			ZKN_BG_FRM_FONT_M, 0, 0, ZKN_BG_FONTBMP_CX, ZKN_BG_FONTBMP_CY, ZKN_BG_FONT_COLOR, 0 );

	// クリーン
	GF_BGL_BmpWinDataFill( &p_drawglb->bmp_mfont, 0 );

	// 表示
	GF_BGL_BmpWinOn( &p_drawglb->bmp_mfont );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	文字描画用ビットマップデータ破棄
 *
 *	@param	p_drawglb		描画グローバルデータ破棄
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknFontBgBmpWinDelete( ZKN_GLB_DRAWDATA* p_drawglb )
{
	GF_BGL_BmpWinDel( &p_drawglb->bmp_mfont );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ソフトウェアスプライト初期化
 *
 *	@param	p_drawglb	描画データ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoftSpriteInit( ZKN_GLB_DRAWDATA* p_drawglb, int heap )
{
	NNSGfdTexKey	texKey;
	NNSGfdPlttKey	plttKey;
	int i;

	// ポケモンデータ転送領域のVramを確保＆転送アドレスとサイズを設定
	p_drawglb->soft_sprite_man = SoftSpriteInit( heap );	
	texKey = NNS_GfdAllocTexVram(ZKN_POKEGRA_TEX_SIZE, FALSE, 0);
	plttKey = NNS_GfdAllocPlttVram(ZKN_POKEGRA_PLTT_SIZE, FALSE, NNS_GFD_ALLOC_FROM_LOW);
	SoftSpriteTextureTransParamSet( 
			p_drawglb->soft_sprite_man,
			NNS_GfdGetTexKeyAddr(texKey),
			NNS_GfdGetTexKeySize(texKey) );
	SoftSpritePaletteTransParamSet( 
			p_drawglb->soft_sprite_man,
			NNS_GfdGetPlttKeyAddr(plttKey),
			NNS_GfdGetPlttKeySize(plttKey) );

/*
	OS_Printf( 
			" addr %x size %x \n",
			NNS_GfdGetTexKeyAddr(texKey),
			NNS_GfdGetTexKeySize(texKey) );
	OS_Printf( 
			" addr %x size %x \n ",
			NNS_GfdGetPlttKeyAddr(plttKey),
			NNS_GfdGetPlttKeySize(plttKey) );
//*/

	//初期化
	for( i=0; i<ZKN_DRAWGLB_POKEGRA_NUM; i++ ){
		p_drawglb->soft_sprite[i] = NULL;
	}



	// ポケグラ以外のスプライトシステム
	{
		SWSP_SYSDATA swsp_sys_data = {
			ZKN_SWSP_OBJNUM,
			ZKN_SWSP_CHARNUM,			
			ZKN_SWSP_PLTTNUM,
			0
		};
		swsp_sys_data.heap = heap;

		p_drawglb->swsp_sys = SWSP_SysInit( &swsp_sys_data );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ソフトウェアスプライト破棄
 *
 *	@param	p_drawglb	描画データ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoftSpriteDelete( ZKN_GLB_DRAWDATA* p_drawglb )
{
	int i;
	
	for( i=0; i<ZKN_DRAWGLB_POKEGRA_NUM; i++ ){

		if( p_drawglb->soft_sprite[i] ){
			SoftSpriteDel( p_drawglb->soft_sprite[i] );
		}
	}
	
	// ポケモン描画スプライトデータ破棄
	SoftSpriteEnd( p_drawglb->soft_sprite_man );


	// ソフトウェアスプライト
	SWSP_SysDelete( p_drawglb->swsp_sys );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン名テーブルリソース読み込み
 *
 *	@param	p_draw	描画データ
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeNameTblResLoad( ZKN_GLB_DRAWDATA* p_draw, int heap )
{
	ZKN_POKELIST_DATA_OAM_DATA* p_darw_data = &p_draw->pokelist_data_draw;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_draw );

	
	// キャラクタデータ読み込み
	p_darw_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( p_draw->res_manager[ CLACT_U_CHAR_RES ], 
			p_handle, NARC_zukan_zkn_oam_main_lzh_NCGR,
			TRUE, ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_darw_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_darw_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_darw_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( p_draw->res_manager[ CLACT_U_PLTT_RES ],
			p_handle, NARC_zukan_zkn_list_oam_NCLR,
			FALSE, ZKN_DRAWGLB_POKENAME_TBL_RES_ID, NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_DRAWGLB_POKENAME_TBL_PLTT_LOAD, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_darw_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_darw_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] );



	// セルデータ読み込み
	p_darw_data->pokelist_res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw->res_manager[ CLACT_U_CELL_RES ],
			p_handle, NARC_zukan_zkn_oam_main_lzh_NCER,
			TRUE, ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_darw_data->pokelist_res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw->res_manager[ CLACT_U_CELLANM_RES ],
			p_handle, NARC_zukan_zkn_oam_main_lzh_NANR,
			TRUE, ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンネームテーブルリソース読み込み
 *
 *	@param	p_data
 *	@param	pp_res_manager
 *	@param	heap 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblResLoad_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap )
{
	// キャラクタデータ読み込み
	p_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar( pp_res_manager[ CLACT_U_CHAR_RES ], 
			ARC_ZUKAN_GRA, NARC_zukan_zkn_oam_main_lzh_NCGR,
			TRUE, ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt( pp_res_manager[ CLACT_U_PLTT_RES ],
			ARC_ZUKAN_GRA, NARC_zukan_zkn_list_oam_NCLR,
			FALSE, ZKN_DRAWGLB_POKENAME_TBL_RES_ID, NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_DRAWGLB_POKENAME_TBL_PLTT_LOAD, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] );



	// セルデータ読み込み
	p_data->pokelist_res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			pp_res_manager[ CLACT_U_CELL_RES ],
			ARC_ZUKAN_GRA, NARC_zukan_zkn_oam_main_lzh_NCER,
			TRUE, ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_data->pokelist_res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			pp_res_manager[ CLACT_U_CELLANM_RES ],
			ARC_ZUKAN_GRA, NARC_zukan_zkn_oam_main_lzh_NANR,
			TRUE, ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン名テーブルリソース破棄
 *
 *	@param	p_draw	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeNameTblResRelease( ZKN_GLB_DRAWDATA* p_draw )
{
	ZKN_POKELIST_DATA_OAM_DATA* p_draw_data = &p_draw->pokelist_data_draw;

	CLACT_U_CharManagerDelete( p_draw_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_draw_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] );

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			p_draw->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw->res_manager[ CLACT_U_CELL_RES ],
			p_draw_data->pokelist_res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw_data->pokelist_res_obj[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンネームテーブル　リソース破棄
 *
 *	@param	p_data
 *	@param	pp_res_manager 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblResRelease_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, CLACT_U_RES_MANAGER_PTR* pp_res_manager )
{
	CLACT_U_CharManagerDelete( p_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] );

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_CHAR_RES ],
			p_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_PLTT_RES ],
			p_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_CELL_RES ],
			p_data->pokelist_res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_CELLANM_RES ],
			p_data->pokelist_res_obj[ CLACT_U_CELLANM_RES ] );
}


//----------------------------------------------------------------------------
/**
 *	@brief	リストアクター登録
 *
 *	@param	p_draw	描画グローバル
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeNameTblActAdd( ZKN_GLB_DRAWDATA* p_draw, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_manager[ CLACT_U_PLTT_RES ],
			p_draw->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 0;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	
	// テーブル部分
	add.mat.x = 0;
	add.mat.y = 0;
	p_draw->pokelist_data_draw.pokelist_tbl = CLACT_AddSimple( &add );
	// 非表示
	CLACT_SetDrawFlag( p_draw->pokelist_data_draw.pokelist_tbl, FALSE );
	CLACT_DrawPriorityChg( p_draw->pokelist_data_draw.pokelist_tbl, 1 );

	// アイコン部分
	add.mat.x = 0;
	add.mat.y = 0;
	p_draw->pokelist_data_draw.pokelist_icon = CLACT_AddSimple( &add );
	// 非表示
	CLACT_SetDrawFlag( p_draw->pokelist_data_draw.pokelist_icon, FALSE );
	CLACT_AnmChg( p_draw->pokelist_data_draw.pokelist_icon, 1 );


	// 名前は登録しない
	p_draw->pokelist_data_draw.p_pokename = NULL;
	p_draw->pokelist_data_draw.mons_no = 0;
	p_draw->pokelist_data_draw.zkn_mode = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン名テーブルアクター破棄
 *
 *	@param	p_draw	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeNameTblActDelete( ZKN_GLB_DRAWDATA* p_draw )
{
	CLACT_Delete( p_draw->pokelist_data_draw.pokelist_tbl );
	p_draw->pokelist_data_draw.pokelist_tbl = NULL;
	CLACT_Delete( p_draw->pokelist_data_draw.pokelist_icon );
	p_draw->pokelist_data_draw.pokelist_icon = NULL;
	if(p_draw->pokelist_data_draw.p_pokename){
		ZKN_FONTOAM_Delete( p_draw->pokelist_data_draw.p_pokename );
		p_draw->pokelist_data_draw.p_pokename = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンネームテーブルアクター登録
 *
 *	@param	p_data
 *	@param	clact_set
 *	@param	pp_res_manager
 *	@param	heap 
 *	@param	bg_pri
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblActAdd_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, int bg_pri )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, bg_pri,
			pp_res_manager[ CLACT_U_CHAR_RES ],
			pp_res_manager[ CLACT_U_PLTT_RES ],
			pp_res_manager[ CLACT_U_CELL_RES ],
			pp_res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 0;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	
	// テーブル部分
	add.mat.x = 0;
	add.mat.y = 0;
	p_data->pokelist_tbl = CLACT_AddSimple( &add );
	// 非表示
	CLACT_SetDrawFlag( p_data->pokelist_tbl, FALSE );
	CLACT_DrawPriorityChg( p_data->pokelist_tbl, 1 );

	// アイコン部分
	add.mat.x = 0;
	add.mat.y = 0;
	p_data->pokelist_icon = CLACT_AddSimple( &add );
	// 非表示
	CLACT_SetDrawFlag( p_data->pokelist_icon, FALSE );
	CLACT_AnmChg( p_data->pokelist_icon, 1 );


	// 名前は登録しない
	p_data->p_pokename = NULL;
	p_data->mons_no = 0;
	p_data->zkn_mode = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンネームテーブルアクター破棄
 *
 *	@param	p_data 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblActDelete_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data )
{
	CLACT_Delete( p_data->pokelist_tbl );
	p_data->pokelist_tbl = NULL;
	CLACT_Delete( p_data->pokelist_icon );
	p_data->pokelist_icon = NULL;
	if(p_data->p_pokename){
		ZKN_FONTOAM_Delete( p_data->p_pokename );
		p_data->p_pokename = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンネームテーブル描画　ONOFF
 *
 *	@param	p_data		ポケモンネームテーブル
 *	@param	flag		描画　ON　OFF　フラグ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblDrawFlagSet_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, BOOL flag )
{
	if( p_data->pokelist_tbl ){
		CLACT_SetDrawFlag( p_data->pokelist_tbl, flag );
	}
	if( p_data->pokelist_icon ){
		CLACT_SetDrawFlag( p_data->pokelist_icon, flag );
	}
	if( p_data->p_pokename->p_fontoam ){
		FONTOAM_SetDrawFlag( p_data->p_pokename->p_fontoam, flag );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル　リソース読み込み処理
 *
 *	@param	p_draw	描画グローバル
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorResInit( ZKN_GLB_DRAWDATA* p_draw, int heap )
{
	ZKN_UTIL_CURSOR_OBJ* p_cursor = &p_draw->cursor;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_draw );

	
	// カーソル用リソース
	// キャラクタデータ読み込み
	p_cursor->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_cursor_oam_sub_lzh_NCGR, TRUE,
			ZKN_CUSOR_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_cursor->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_cursor->res_obj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_cursor->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_cursor_oam_sub_NCLR, FALSE, 
			ZKN_CUSOR_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DSUB, 
			ZKN_CURSOR_PLTT_LOAD, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_cursor->res_obj[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_cursor->res_obj[ CLACT_U_PLTT_RES ] );


	// セルデータ読み込み
	p_cursor->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_cursor_oam_sub_lzh_NCER, TRUE,
			ZKN_CUSOR_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_cursor->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_cursor_oam_sub_lzh_NANR, TRUE,
			ZKN_CUSOR_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソルリソースの破棄
 *
 *	@param	p_draw	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorResDelete( ZKN_GLB_DRAWDATA* p_draw )
{
	ZKN_UTIL_CURSOR_OBJ* p_cursor = &p_draw->cursor;

	CLACT_U_CharManagerDelete( p_cursor->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_cursor->res_obj[ CLACT_U_PLTT_RES ] );

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			p_draw->res_manager[ CLACT_U_CHAR_RES ],
			p_cursor->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw->res_manager[ CLACT_U_PLTT_RES ],
			p_cursor->res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw->res_manager[ CLACT_U_CELL_RES ],
			p_cursor->res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw->res_manager[ CLACT_U_CELLANM_RES ],
			p_cursor->res_obj[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル アクターの登録
 *
 *	@param	p_draw	描画グローバル
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorActInit( ZKN_GLB_DRAWDATA* p_draw, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	int i;
	ZKN_UTIL_CURSOR_OBJ* p_cursor = &p_draw->cursor;

	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			ZKN_CUSOR_RES_ID,
			ZKN_CUSOR_RES_ID, 
			ZKN_CUSOR_RES_ID,
			ZKN_CUSOR_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_manager[ CLACT_U_PLTT_RES ],
			p_draw->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	add.ClActSet	= p_draw->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 0;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;
	add.mat.y		= SUB_SURFACE_Y + (100 * FX32_ONE);	// 0だと上画面に移るため
	add.mat.x		= (100 * FX32_ONE);

	for( i=0; i<ZKN_CURROS_MAT_RECT_NUM; i++ ){
		p_cursor->cursor[i] = CLACT_AddSimple( &add );
		CLACT_AnmChg( p_cursor->cursor[i], i );
	}
	ZKN_UTIL_CursorSetDrawFlag( p_cursor, FALSE );


	// カーソルアニメ登録
	ZknCursorAnmAdd( p_draw );

	// カーソル動作タスク登録
	ZknCursorMoveTcbAdd( p_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソルアクターの破棄
 *		
 *	@param	p_draw	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorActDelete( ZKN_GLB_DRAWDATA* p_draw )
{
	int i;
	ZKN_UTIL_CURSOR_OBJ* p_cursor = &p_draw->cursor;

	// カーソル動作アニメ破棄
	ZknCursorMoveTcbDelete( p_draw );

	// カーソルアニメ破棄
	ZknCursorAnmDelete( p_draw );

	for( i=0; i<ZKN_CURROS_MAT_RECT_NUM; i++ ){
		CLACT_Delete( p_cursor->cursor[i] );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	図鑑カーソルアニメタスク登録
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorAnmAdd( ZKN_GLB_DRAWDATA* p_draw )
{
	p_draw->cursor_anm_tcb = TCB_Add( ZknCursorAnmTcb, &p_draw->cursor, ZKN_CORSOR_ANM_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソルアニメ破棄
 *
 *	@param	p_draw
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorAnmDelete( ZKN_GLB_DRAWDATA* p_draw )
{
	TCB_Delete( p_draw->cursor_anm_tcb );
}	

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑カーソルアニメタスク
 *
 *	@param	tcb
 *	@param	wrok 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorAnmTcb( TCB_PTR tcb, void* work )
{
	ZKN_UTIL_CURSOR_OBJ* p_cursor = work;
	int i;
	int size_x, size_y;
	fx32 calc;
	int count;
	
	// 停止処理中かチェック
	if( p_cursor->anm_stop ){
		ZknCursorSetMatrixLocal( p_cursor, p_cursor->x, p_cursor->y,
				p_cursor->size_x, p_cursor->size_y );
		return ;
	}

	p_cursor->anm_count = (p_cursor->anm_count + 1) % ZKN_CURSOR_ANM_COUNT_MAX;

	// カウンタ値を取得
	if( p_cursor->anm_count < ZKN_CURSOR_ANM_COUNT_HALF ){
		count = p_cursor->anm_count;
	}else{
		// 1を足す ZKN_CURSOR_ANM_COUNT_HALFと==のcountにしないためにこれを
		// 行う。"=="になるとその一瞬のみsize_x, yの値が変わってしまい、見た目が変
		count = ZKN_CURSOR_ANM_COUNT_MAX - (p_cursor->anm_count + 1);
	}

	// サイズを求める
	calc = FX_Mul( ZKN_CURSOR_ANM_DIS << FX32_SHIFT, count << FX32_SHIFT );
	calc = FX_Div( calc, ZKN_CURSOR_ANM_COUNT_HALF << FX32_SHIFT );
	calc >>= FX32_SHIFT;
	size_x = p_cursor->size_x + calc;
	size_y = p_cursor->size_y + calc;

	ZknCursorSetMatrixLocal( p_cursor, p_cursor->x, p_cursor->y, size_x, size_y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	座標設定のみ行う
 *
 *	@param	p_obj
 *	@param	def_x
 *	@param	def_y
 *	@param	size_x
 *	@param	size_y 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknCursorSetMatrixLocal( ZKN_UTIL_CURSOR_OBJ* p_obj, int def_x, int def_y, int size_x, int size_y )
{
	VecFx32 mat;
	int x, y;
	int i;

	for( i=0; i<ZKN_CURROS_MAT_RECT_NUM; i++ ){
		// 座標取得
		ZKN_CURSOR_UTIL_GetRectMat( i, &x, &y, def_x, def_y, size_x, size_y );
		mat.x = x << FX32_SHIFT;
		mat.y = (y << FX32_SHIFT) + SUB_SURFACE_Y;

		//　設定
		CLACT_SetMatrix( p_obj->cursor[ i ], &mat );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル移動パラメータ設定
 *
 *	@param	p_draw
 *	@param	x
 *	@param	y
 *	@param	size_x
 *	@param	size_y 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------

static void ZknCursorMoveSet( ZKN_GLB_DRAWDATA* p_draw, int x, int y, int size_x, int size_y )
{
	ZKN_UTIL_CURSOR_OBJ_MOVE* p_cursor_move = &p_draw->cursor_move;


	// 今のターゲット座標と違うときのみ設定
	if( (p_cursor_move->ta_x == x) &&
		(p_cursor_move->ta_y == y) &&
		(p_cursor_move->ta_size_x == size_x) &&
		(p_cursor_move->ta_size_y == size_y) ){
		return;
	}

	//　カーソルポインタ設定
	p_cursor_move->p_cursor = &p_draw->cursor;
	
	// 今の座標　サイズから新座標サイズに変更する
	// 座標
	ZKN_UTIL_MoveReq( &p_cursor_move->mat_move,
			p_cursor_move->p_cursor->x, x,
			p_cursor_move->p_cursor->y, y,
			ZKN_CURSOR_MOVE_SYNC );

	// サイズ
	ZKN_UTIL_MoveReq( &p_cursor_move->size_move,
			p_cursor_move->p_cursor->size_x, size_x,
			p_cursor_move->p_cursor->size_y, size_y,
			ZKN_CURSOR_MOVE_SYNC );


	p_cursor_move->ta_x = x;
	p_cursor_move->ta_y = y;
	p_cursor_move->ta_size_x = size_x;
	p_cursor_move->ta_size_y = size_y;

	// 動作開始
	p_cursor_move->move_stop = TRUE;

/*	OS_Printf( "	p_cursor_move->ta_x %d\n", p_cursor_move->ta_x );
	OS_Printf( "	p_cursor_move->ta_y %d\n", p_cursor_move->ta_y );
	OS_Printf( "	p_cursor_move->ta_size_x %d\n", p_cursor_move->ta_size_x );
	OS_Printf( "	p_cursor_move->ta_size_y %d\n", p_cursor_move->ta_size_y );//*/
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル移動
 *
 *	@param	tcb		タスクデータ
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorMoveTcb( TCB_PTR tcb, void* p_work )
{
	ZKN_UTIL_CURSOR_OBJ_MOVE* p_cursor_move = p_work;
	BOOL check;

	// 初期化されていなければ動作しない
	if( p_cursor_move->move_stop == FALSE ){
		return ;
	}

	// 動作させる
	check = ZKN_UTIL_MoveMain( &p_cursor_move->mat_move );		
	ZKN_UTIL_MoveMain( &p_cursor_move->size_move );		


	//　値が変更されたら
	// 座標サイズを設定
	p_cursor_move->p_cursor->x = p_cursor_move->mat_move.x;
	p_cursor_move->p_cursor->y = p_cursor_move->mat_move.y;
	p_cursor_move->p_cursor->size_x = p_cursor_move->size_move.x;
	p_cursor_move->p_cursor->size_y = p_cursor_move->size_move.y;

	// 終了したら終わり
	if( check == TRUE ){
		p_cursor_move->move_stop = FALSE;
	}

/*	OS_Printf( "p_cursor_move->p_cursor->x %d\n", p_cursor_move->p_cursor->x );
	OS_Printf( "p_cursor_move->p_cursor->y %d\n", p_cursor_move->p_cursor->y );
	OS_Printf( "p_cursor_move->p_cursor->size_x %d\n", p_cursor_move->p_cursor->size_x );
	OS_Printf( "p_cursor_move->p_cursor->size_y %d\n", p_cursor_move->p_cursor->size_y );//*/
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作TCBを登録する
 *
 *	@param	p_draw	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorMoveTcbAdd( ZKN_GLB_DRAWDATA* p_draw )
{
	p_draw->cursor_move_tcb = TCB_Add( ZknCursorMoveTcb, &p_draw->cursor_move, ZKN_CORSOR_MOVE_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作TCBを破棄
 *
 *	@param	p_draw	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorMoveTcbDelete( ZKN_GLB_DRAWDATA* p_draw )
{
	TCB_Delete( p_draw->cursor_move_tcb );
	p_draw->cursor_move_tcb = NULL;
}
