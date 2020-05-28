//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_playsys.c
 *	@brief		イメージクリッププレイヤー
 *	@author		tomoya takahashi 
 *	@data		2005.12.27
 *
 *
 * イメージクリッププロックを作成して表示する以外の方法で
 * 表示するイメージクリッププレイヤー
 * 
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include <string.h>
#include "system.h"
#include "assert.h"
#include "calctool.h"
#include "calc2d.h"
#include "include/system/lib_pack.h"
#include "include/application/imageClip/imc_drawsys.h"
#include "include/application/imageClip/imc_accessorie.h"
#include "include/application/imageClip/imc_drawdata_define.h"
#include "include/application/imageClip/imc_right_box.h"
#include "include/application/imageClip/imc_obj_list.h"
#include "include/application/imageClip/imc_obj_list_func.h"
#include "include/application/imageClip/imc_rbox_player.h"
#include "include/system/arc_util.h"

#define __IMC_PLAYSYS_H_GLOBAL
#include "include/application/imageClip/imc_playsys.h"

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
#define IMC_PLAYSYS_OBJLIST_NUM	( IMC_RBOX_OBJ_CONTEST_MAX )
#define IMC_PLAYSYS_ACCE_NUM	( IMC_RBOX_ACCE_CONTEST_MAX )



//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
typedef struct _IMC_PLAYERSYS{
	// 描画関係
	IMC_DRAW_DATA drawSys;

	// オブジェクトリストデータ
	IMC_OBJLIST_TBL	objListTbl;

	// アクセサリデータ
	IMC_ACCESSORIE_OBJ_TBL* acce;

	// 右画面データ
	IMC_RIGHT_BOX rbox;
	IMC_RBOX_PLAYER rbox_player;		// 右ボックスプレイヤー

	// ポケモンデータ
	POKEMON_PARAM* poke_para;

	// ヒープID
	int		heap_id;

	// 現在中心座標
	int x;
	int y;
	int center_ofs_x;	// 中心までの座標
	int center_ofs_y;	// 中心までの座標
	u16 rota_num;
	VecFx32 scale;
	GXRgb color;		// 全体描画カラー

	BOOL BG_use;				// BG使用フラグ

	BOOL draw_flag;			// 描画ON:TRUE OFF:FALSE
} IMC_PLAYERSYS;


//-------------------------------------
//	右ボックス　初期化データ
//=====================================
typedef struct {
	const IMC_SAVEDATA_POKEMON* p_poke;
	const IMC_SAVEDATA_ACCESSORIE* p_acce[ IMC_SAVEDATA_CONTEST_ACCE_NUM ];
	int acce_num;
	GF_BGL_INI* p_bg_ini;	// BGシステム	NOBGのときはNULLでOK
	int bg_id;				// BGID
							// GF_BGL_FRAME2_Mのコントロールセットを内部で行います。
	int x;				// 全体の中心
	int y;				// 全体の中心
	int heap_id;		// 使用するヒープID
} IMC_PLAYERSYS_INIT_LOCAL;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static IMC_PLAYERSYS_PTR initPlayerSys( const IMC_PLAYERSYS_INIT_LOCAL* cp_init );
static IMC_PLAYERSYS_PTR initPlayerSys_NoBG( const IMC_PLAYERSYS_INIT_LOCAL* cp_init );
static void initDrawSys( IMC_PLAYERSYS* p_sys, const IMC_PLAYERSYS_INIT_LOCAL* cp_init );
static void mainDrawSys( IMC_PLAYERSYS* p_sys );
static void deleteDrawSys( IMC_PLAYERSYS* p_sys );

static void initRightBox( IMC_PLAYERSYS* p_sys, const IMC_PLAYERSYS_INIT_LOCAL* cp_init );
static void initRightBoxBG( IMC_PLAYERSYS* p_sys, const IMC_PLAYERSYS_INIT_LOCAL* cp_init );
static void deleteRightBox( IMC_PLAYERSYS* p_sys );
static void deleteRightBoxBG( IMC_PLAYERSYS* p_sys );

static void initWorkParam( IMC_PLAYERSYS* p_sys, const IMC_PLAYERSYS_INIT_LOCAL* cp_init );

static void setInitParamData( IMC_PLAYERSYS_INIT_LOCAL* p_init, const IMC_PLAYERSYS_INIT* cp_param );
static void setTelevisionSaveData( IMC_PLAYERSYS_INIT_LOCAL* p_init, const IMC_TELEVISION_SAVEDATA* save_data );
static void setContestSaveData( IMC_PLAYERSYS_INIT_LOCAL* p_init, const IMC_CONTEST_SAVEDATA* save_data );

static void imc_draw_MakeLoadSWSP_player( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData, const IMC_PLAYERSYS_INIT_LOCAL* cp_init, int heap );
static void loadAcceDataPlayer( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData, const IMC_PLAYERSYS_INIT_LOCAL* cp_init, int heap );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリッププレイヤー生成
 *
 *	@param	cp_init		初期化データ
 *	@param	save_data	セーブデータ
 *
 *	@return	生成されたデータ
 *
 *
 */
//-----------------------------------------------------------------------------
IMC_PLAYERSYS_PTR IMC_TelevisionPlayerInit( const IMC_PLAYERSYS_INIT* cp_init, const IMC_TELEVISION_SAVEDATA* save_data )
{
	IMC_PLAYERSYS_INIT_LOCAL init_local;

	// 引数データ設定
	setInitParamData( &init_local, cp_init );

	// セーブデータ設定
	setTelevisionSaveData( &init_local, save_data );
	
	return initPlayerSys( &init_local );
}

IMC_PLAYERSYS_PTR IMC_TelevisionPlayerInit_NoBG( const IMC_PLAYERSYS_INIT* cp_init, const IMC_TELEVISION_SAVEDATA* save_data )
{
	IMC_PLAYERSYS_INIT_LOCAL init_local;

	// 引数データ設定
	setInitParamData( &init_local, cp_init );

	// セーブデータ設定
	setTelevisionSaveData( &init_local, save_data );
	
	return initPlayerSys_NoBG( &init_local );
}

IMC_PLAYERSYS_PTR IMC_ContestPlayerInit( const IMC_PLAYERSYS_INIT* cp_init, const IMC_CONTEST_SAVEDATA* save_data )
{
	IMC_PLAYERSYS_INIT_LOCAL init_local;
	
	// 引数データ設定
	setInitParamData( &init_local, cp_init );

	// セーブデータ設定
	setContestSaveData( &init_local, save_data );
	
	return initPlayerSys( &init_local );
}

IMC_PLAYERSYS_PTR IMC_ContestPlayerInit_NoBG( const IMC_PLAYERSYS_INIT* cp_init, const IMC_CONTEST_SAVEDATA* save_data )
{
	IMC_PLAYERSYS_INIT_LOCAL init_local;
	
	// 引数データ設定
	setInitParamData( &init_local, cp_init );

	// セーブデータ設定
	setContestSaveData( &init_local, save_data );
	
	return initPlayerSys_NoBG( &init_local );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリッププレイヤーメイン
 *
 *	@param	p_sys		イメージクリッププレイヤーシステム
 *
 *	@retval	none
 *
 */
//-----------------------------------------------------------------------------
void IMC_PlayerMain( IMC_PLAYERSYS_PTR p_sys )
{
	if( p_sys->BG_use == TRUE ){
		// 右ボックスプレイヤー
		IMC_RBOX_PLAYER_Main( &p_sys->rbox_player );
	}

	// 描画処理
	if( p_sys->draw_flag == TRUE ){
		mainDrawSys( p_sys );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリッププレイヤー終了
 *
 *	@param	p_sys		イメージクリッププレイヤーシステム
 *
 *	@retval	none
 *
 */
//-----------------------------------------------------------------------------
void IMC_PlayerEnd( IMC_PLAYERSYS_PTR p_sys )
{
	// 右ボックス破棄
	if(p_sys->BG_use){
		deleteRightBoxBG( p_sys );
	}
	deleteRightBox( p_sys );

	// アクセサリ格納データ破棄
	IMC_ACCE_ObjTblDelete( p_sys->acce );
	p_sys->acce = NULL;
	
	// オブジェクトリストテーブル破棄
	IMC_OBJLIST_TblDelete( &p_sys->objListTbl );
	
	// 描画システム破棄
	deleteDrawSys( p_sys );

	// ポケモンパラメータ破棄
	sys_FreeMemoryEz( p_sys->poke_para );

	sys_FreeMemoryEz( p_sys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	VBlank期間中に呼ぶ関数
 *
 *	@param	p_sys	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_PlayerVblank( IMC_PLAYERSYS_PTR p_sys )
{
	IMC_DRAW_VBlankPlayer( &p_sys->drawSys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画フラグ設定
 *
 *	@param	p_sys	ワーク
 *	@param	flag	描画フラグ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetDrawFlag( IMC_PLAYERSYS_PTR p_sys, BOOL flag )
{
	p_sys->draw_flag = flag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画フラグ取得
 *
 *	@param	p_sys	ワーク
 *
 *	@retval	TRUE	描画
 *	@retval	FALSE	非描画
 */
//-----------------------------------------------------------------------------
BOOL IMC_Player_GetDrawFlag( CONST_IMC_PLAYERSYS_PTR p_sys )
{
	return p_sys->draw_flag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ描画　フラグONOFF
 *	
 *	@param	p_sys		システムワーク
 *	@param	flag		フラグ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetAcceDrawFlag( IMC_PLAYERSYS_PTR p_sys, BOOL flag )
{
	p_sys->drawSys.SWSP_DrawFlag = flag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ描画　フラグ取得
 *
 *	@param	p_sys		システムワーク
 *
 *	@retval	TRUE	描画
 *	@retval	FALSE	非描画
 */
//-----------------------------------------------------------------------------
BOOL IMC_Player_GetAcceDrawFlag( CONST_IMC_PLAYERSYS_PTR p_sys )
{
	return p_sys->drawSys.SWSP_DrawFlag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	座標を設定
 *
 *	@param	p_sys	システム
 *	@param	x		x座標
 *	@param	y		y座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetMatrix( IMC_PLAYERSYS_PTR p_sys, int x, int y )
{
	IMC_RBOX_ListMatSet( &p_sys->rbox, p_sys->x, p_sys->y, x, y );

	//　BGを使っているときはBG面も設定
	if( p_sys->BG_use ){
		GF_BGL_ScrollSet( p_sys->drawSys.BG_Ini, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, IMC_RBOX_AREA_X - x );
		GF_BGL_ScrollSet( p_sys->drawSys.BG_Ini, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, IMC_RBOX_AREA_Y - y );
	}
	
	p_sys->x = x;
	p_sys->y = y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	回転,拡大時の中心オフセット値を設定
 *
 *	@param	p_sys	ワーク
 *	@param	x		ｘオフセット
 *	@param	y		ｙオフセット
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetRotScaleCenterOfs( IMC_PLAYERSYS_PTR p_sys, int x, int y )
{
	p_sys->center_ofs_x = x;
	p_sys->center_ofs_y = y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	回転各設定
 *
 *	@param	p_sys		ワーク
 *	@param	rota		回転角
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetRota( IMC_PLAYERSYS_PTR p_sys, u16 rota )
{
	p_sys->rota_num = rota;
}

//----------------------------------------------------------------------------
/**
 *	@brief	拡大縮小値設定
 *
 *	@param	p_sys	ワーク
 *	@param	x		ｘ拡大
 *	@param	y		ｙ拡大
 *	@param	z		ｚ拡大
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetScale( IMC_PLAYERSYS_PTR p_sys, fx32 x, fx32 y, fx32 z )
{
	p_sys->scale.x = x;
	p_sys->scale.y = y;
	p_sys->scale.z = z;
}

//-----------------------------------------------------------------------------
/**
 *	@brief	ポケモンを中心とした座標と中心オフセットの設定
 *
 *	@param	p_sys	ワーク
 *	@param	x		ｘ座標	（ここは左上ではなくポケモンの中心座標）
 *	@param	y		ｙ座標	（ここは左上ではなくポケモンの中心座標）
 *
 *	@param	none
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetPokeMatrix( IMC_PLAYERSYS_PTR p_sys, int x, int y )
{
	int pokex, pokey;
	int dis_x, dis_y;
	int pokesizx, pokesizy;
	int all_left, all_top;
	int c_x, c_y;

	// ポケモンサイズ
	IMC_POKE_SizeGet( &p_sys->rbox.boxDraw.poke, &pokesizx, &pokesizy );

	//　ポケモン座標
	IMC_RBOX_GetPokeMatrix( &p_sys->rbox, &pokex, &pokey );

	// 全体の移動値計算
	dis_x = x - pokex;
	dis_y = y - pokey;

	// 全体を移動
	all_left = p_sys->x + dis_x;
	all_top = p_sys->y + dis_y;
	IMC_Player_SetMatrix( p_sys, all_left, all_top );

	// 回転　拡大　の中心座標を設定
	c_x  = x - all_left; 
	c_y  = y - all_top; 
	IMC_Player_SetRotScaleCenterOfs( p_sys, c_x, c_y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンの足跡座標を設定する
 *
 *	@param	p_sys	ワーク
 *	@param	x		ｘ座標	（ここは左上ではなくポケモンの足元座標）
 *	@param	y		ｙ座標	（ここは左上ではなくポケモンの足元座標）
 *	@param	height	そのポケモンの高さ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetPokeMatrix_Ground( IMC_PLAYERSYS_PTR p_sys, int x, int y, int height )
{
	int oy;	// Yオフセット値
	fx32 scale_y_height;

	// 中心から足元までの高さに変更
	height = (SOFT_SPRITE_SIZE_Y/2) - height;
	
	// 中心からの値の今の拡大値での値を求める
	scale_y_height = FX_Mul( height * FX32_ONE, p_sys->scale.y );
	oy = scale_y_height >> FX32_SHIFT;

	IMC_Player_SetPokeMatrix( p_sys, x, y-oy );
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画色指定
 *
 *	@param	p_sys	プレイヤーシステム
 *	@param	color	色
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetColor( IMC_PLAYERSYS_PTR p_sys, GXRgb color )
{
	p_sys->color = color;

	// 全アクセサリ、ポケモンに色を設定
	IMC_RBOX_SetObjColor( &p_sys->rbox, color );	
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画色　取得
 *
 *	@param	p_sys	プレイヤーシステム
 *
 *	@return	色
 */
//-----------------------------------------------------------------------------
GXRgb IMC_Player_GetColor( CONST_IMC_PLAYERSYS_PTR cp_sys )
{
	return cp_sys->color;
}

//----------------------------------------------------------------------------
/**
 *	@brief	優先順位を設定	先頭のアクセサリの優先順位
 *
 *	@param	p_sys	ワーク
 *	@param	pri		優先順位
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetPriority( IMC_PLAYERSYS_PTR p_sys, int pri )
{
	IMC_RBOX_SetObjPriorityMC( &p_sys->rbox, pri );
}

void IMC_Player_AddPriority( IMC_PLAYERSYS_PTR p_sys, int pri )
{
	IMC_RBOX_AddObjPriorityMC( &p_sys->rbox, pri );
}



//-----------------------------------------------------------------------------
/**
 *
 *			プライベート関数
 * 
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	イメージクリッププレイヤーシステム作成
 *
 *	@param	cp_init		初期化データ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static IMC_PLAYERSYS_PTR initPlayerSys( const IMC_PLAYERSYS_INIT_LOCAL* cp_init )
{
	IMC_PLAYERSYS* p_sys;		// イメージクリップワーク
	BOOL	check;				// ﾁｪｯｸ用


	// システムワーク生成
	p_sys = sys_AllocMemory( cp_init->heap_id, sizeof(IMC_PLAYERSYS) );
	memset( p_sys, 0, sizeof(IMC_PLAYERSYS) );

	// ヒープID
	p_sys->heap_id	= cp_init->heap_id;
	p_sys->poke_para = PokemonParam_AllocWork( cp_init->heap_id );
	ImcSaveData_GetUtilPokePara( cp_init->p_poke, p_sys->poke_para );

	// 描画データ設定を行います。
	initDrawSys( p_sys, cp_init );
	// BG面を使用するので、表示
	IMC_DRAW_InitSysPlayerBG( &p_sys->drawSys, cp_init->p_bg_ini, cp_init->heap_id );

	// オブジェクトリストテーブル作成
	IMC_OBJLIST_TblInit( &p_sys->objListTbl, IMC_PLAYSYS_OBJLIST_NUM, cp_init->heap_id );
	
	// アクセサリ格納データ作成
	p_sys->acce = IMC_ACCE_ObjTblInit( IMC_PLAYSYS_ACCE_NUM, cp_init->heap_id );

	// 右ボックスデータ作成
	initRightBox( p_sys, cp_init );
	initRightBoxBG( p_sys, cp_init );

	// 右ボックスプレイヤーに登録
	IMC_RBOX_PLAYER_Init( &p_sys->rbox_player, &p_sys->rbox, cp_init->heap_id );

	p_sys->BG_use = TRUE;
	p_sys->draw_flag = TRUE;

	// 座標などの初期データ代入
	initWorkParam( p_sys, cp_init );

	return p_sys;
}

//----------------------------------------------------------------------------
/**
 *	@brief	イメージクリッププレイヤーシステム作成		BGなしVer
 *
 *	@param	cp_init		初期化データ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static IMC_PLAYERSYS_PTR initPlayerSys_NoBG( const IMC_PLAYERSYS_INIT_LOCAL* cp_init )
{
	IMC_PLAYERSYS* p_sys;		// イメージクリップワーク
	BOOL	check;				// ﾁｪｯｸ用

	// システムワーク生成
	p_sys = sys_AllocMemory( cp_init->heap_id, sizeof(IMC_PLAYERSYS) );
	memset( p_sys, 0, sizeof(IMC_PLAYERSYS) );

	// ヒープID
	p_sys->heap_id	= cp_init->heap_id;
	p_sys->poke_para = PokemonParam_AllocWork( cp_init->heap_id );
	ImcSaveData_GetUtilPokePara( cp_init->p_poke, p_sys->poke_para );

	// 描画データ設定を行います。
	initDrawSys( p_sys, cp_init );

	// オブジェクトリストテーブル作成
	IMC_OBJLIST_TblInit( &p_sys->objListTbl, IMC_PLAYSYS_OBJLIST_NUM, cp_init->heap_id );
	
	// アクセサリ格納データ作成
	p_sys->acce = IMC_ACCE_ObjTblInit( IMC_PLAYSYS_ACCE_NUM, cp_init->heap_id );

	// 右ボックスデータ作成
	initRightBox( p_sys, cp_init );

	p_sys->BG_use = FALSE;
	p_sys->draw_flag = TRUE;


	// 座標などの初期データ代入
	initWorkParam( p_sys, cp_init );

	return p_sys;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画システムデータ作成
 *
 *	@param	p_sys			イメージクリッププレイヤーシステム
 *	@param	cp_init			初期化データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initDrawSys( IMC_PLAYERSYS* p_sys, const IMC_PLAYERSYS_INIT_LOCAL* cp_init )
{
	IMC_DRAW_LOADRES_DATA loadData;	// 画像データ読み込みデータ

	// 画面データ設定
//	IMC_DRAW_SetUp();

	// 描画システム作成
	// プレイヤー用初期化関数を作成してください↓
	// 詳細　必要な描画システムの作成
	//	ソフトウェアスプライト
	//	アクセサリ用スプライト描画システム
	//	アクセサリ用パレットオフセットテーブル
	SWSP_SYSDATA swsp;
	swsp.obj_num	= IMC_SPRITE_OBJ_NUM;
	swsp.char_num	= IMC_SPRITE_CHAR_NUM;
	swsp.pltt_num	= IMC_SPRITE_PLTT_NUM;
	swsp.heap		= cp_init->heap_id;
	IMC_DRAW_InitSysPlayer( &p_sys->drawSys, &swsp, cp_init->heap_id );

	// 描画データ作成
	// ここもプレイヤー用初期化関数を作成↓
	// アクセサリデータから必要なテクスチャ、パレットのテーブル
	// を作成
	imc_draw_MakeLoadSWSP_player( &p_sys->drawSys, &loadData, cp_init, cp_init->heap_id );

	// 描画データVram転送
	IMC_DRAW_LoadResource( &p_sys->drawSys, &loadData );

	// 描画データ破棄
	IMC_DRAW_DestLoadSWSP( &loadData );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画システムメイン関数
 *
 *	@param	p_sys	イメージクリッププレイヤーシステム
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void mainDrawSys( IMC_PLAYERSYS* p_sys )
{
	IMC_DRAW_DrawSysPlayer( &p_sys->drawSys,
			p_sys->x + p_sys->center_ofs_x,
			p_sys->y + p_sys->center_ofs_y,
			p_sys->rota_num, &p_sys->scale );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画システム破棄関数
 *
 *	@param	p_sys	イメージクリッププレイヤーシステム
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteDrawSys( IMC_PLAYERSYS* p_sys )
{
	// 描画データ破棄
	IMC_DRAW_DeleteResource( &p_sys->drawSys );

	// 描画システム破棄
	IMC_DRAW_DeleteSysPlayer( &p_sys->drawSys );
	if(p_sys->BG_use){
		IMC_DRAW_DeleteSysPlayerBG(&p_sys->drawSys);
	}

	// 描画面設定破棄
//	IMC_DRAW_PutBack();
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	右ボックスデータ作成
 *
 *	@param	p_sys		イメージクリッププレイヤーシステム
 *	@param	cp_init		初期化データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initRightBox( IMC_PLAYERSYS* p_sys, const IMC_PLAYERSYS_INIT_LOCAL* cp_init )
{
	IMC_RIGHT_BOX_INIT	rbox_init;	// 右ボックス初期化データ
	int poke_x, poke_y, poke_pri;


	// 右ボックスデータ作成
	// 描画データ
	memset( &rbox_init, 0, sizeof(IMC_RIGHT_BOX_INIT) );
	rbox_init.SWSP_drawSys		= p_sys->drawSys.SWSP_drawSys;
	rbox_init.SWSP_charData		= p_sys->drawSys.SWSP_charData;
	rbox_init.SWSP_plttData		= p_sys->drawSys.SWSP_plttData;
	rbox_init.accePlttOfsTbl	= p_sys->drawSys.accePlttOfsTbl;
	rbox_init.SSM_drawSys		= p_sys->drawSys.SSM_drawSys;
	rbox_init.BG_Ini			= p_sys->drawSys.BG_Ini;

	rbox_init.acce		= p_sys->acce;			// アクセサリデータ
	rbox_init.objListTbl= &p_sys->objListTbl;	// オブジェクトリストテーブル
	rbox_init.acce_count_max = IMC_RBOX_OBJ_CONTEST_MAX;
	IMC_RBOX_InitSys( &p_sys->rbox, &rbox_init );
	
	// ポケモンを登録
	{
		SOFT_SPRITE_ARC	arc;
		poke_x = ImcSaveData_GetUtilPokeX( cp_init->p_poke );
		poke_y = ImcSaveData_GetUtilPokeY( cp_init->p_poke );
		poke_pri = ImcSaveData_GetUtilPokePri( cp_init->p_poke );
		IMC_RBOX_AddPokePlayer( &p_sys->rbox, p_sys->poke_para, &arc, poke_x, poke_y, poke_pri, cp_init->heap_id );
	}

	// 右ボックスに配置するデータを作成
	// データから配置を行うようにする
	{
		int i;
		int x,y;
		int acce_no;
		s8 pri;
		for(i=0;i<cp_init->acce_num; i++){

			acce_no = ImcSaveData_GetUtilAcceNo( cp_init->p_acce[i] );
			x = ImcSaveData_GetUtilAcceMatX( cp_init->p_acce[i] );
			y = ImcSaveData_GetUtilAcceMatY( cp_init->p_acce[i] );
			pri = ImcSaveData_GetUtilAccePri( cp_init->p_acce[i] );
			
			// 右アクセサリ配置
			IMC_RBOX_AddAccessorieEasy( &p_sys->rbox, acce_no, 
					x, y, pri );
		}
	}//*/

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	右ボックスデータ作成		BG面初期化
 *
 *	@param	p_sys		イメージクリッププレイヤーシステム
 *	@param	cp_init		初期化データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initRightBoxBG( IMC_PLAYERSYS* p_sys, const IMC_PLAYERSYS_INIT_LOCAL* cp_init )
{
	// BGを表示
	// データからBGのデータNOを設定する
	IMC_RBOX_BGSet( &p_sys->rbox, cp_init->bg_id, cp_init->heap_id );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	右ボックスデータ破棄
 *
 *	@param	p_sys 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteRightBox( IMC_PLAYERSYS* p_sys )
{
	// 右ボックス配置データ破棄
	IMC_RBOX_DeleteAccessorieAll( &p_sys->rbox );
	
	// 右ボックスデータ破棄
	IMC_RBOX_DeleteSys( &p_sys->rbox );
}

//----------------------------------------------------------------------------
/**
 *	@brief	右ボックスBG
 *
 *	@param	p_sys 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void deleteRightBoxBG( IMC_PLAYERSYS* p_sys )
{
	// BGをクリーン
	IMC_RBOX_BGClean( &p_sys->rbox );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワークデータの初期設定
 *
 *	@param	p_sys	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void initWorkParam( IMC_PLAYERSYS* p_sys, const IMC_PLAYERSYS_INIT_LOCAL* cp_init )
{
	// 現在座標設定
	p_sys->x = IMC_RBOX_END_SX;
	p_sys->y = IMC_RBOX_END_SY;
	p_sys->center_ofs_x = (IMC_RBOX_AREA_WIDTH/2);
	p_sys->center_ofs_y = (IMC_RBOX_AREA_HEIGHT/2);

	// スケール値設定
	p_sys->scale.x = FX32_ONE;
	p_sys->scale.y = FX32_ONE;
	p_sys->scale.z = FX32_ONE;

	// 回転角
	p_sys->rota_num = 0;

	// 座標設定
	IMC_Player_SetMatrix( p_sys, cp_init->x, cp_init->y );

	// 色
	p_sys->color = GX_RGB( 31,31,31 );
}


//----------------------------------------------------------------------------
/**
 *	@brief	システム引数の値を代入
 *
 *	@param	p_init		初期化ワーク
 *	@param	cp_param	データ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setInitParamData( IMC_PLAYERSYS_INIT_LOCAL* p_init, const IMC_PLAYERSYS_INIT* cp_param )
{
	p_init->p_bg_ini	= cp_param->p_bg_ini;
	p_init->x			= cp_param->x;
	p_init->y			= cp_param->y;
	p_init->heap_id		= cp_param->heap_id;
}

//----------------------------------------------------------------------------
/**
 *	@brief	テレビアクセサリデータ取得関数
 *
 *	@param	p_init		格納先
 *	@param	save_data	セーブデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setTelevisionSaveData( IMC_PLAYERSYS_INIT_LOCAL* p_init, const IMC_TELEVISION_SAVEDATA* save_data )
{
	int i;

	// ポケモン
	p_init->p_poke = ImcSaveData_GetTelevisionPokemon( save_data );
	
	// アクセサリ
	p_init->acce_num = 0;
	for( i=0; i<IMC_SAVEDATA_TELEVISION_ACCE_NUM; i++ ){
		// アクセサリ設定チェック
		if( ImcSaveData_CheckTelevisionAcceDataSet( save_data, i ) ){
			p_init->p_acce[ p_init->acce_num ] = ImcSaveData_GetTelevisionAcce( save_data, i );
			p_init->acce_num ++;
		}
	}

	// BGID
	p_init->bg_id = ImcSaveData_GetTelevisionBgId( save_data );
}
//----------------------------------------------------------------------------
/**
 *	@brief	コンテストアクセサリデータ取得関数
 *
 *	@param	p_init		格納先
 *	@param	save_data	セーブデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setContestSaveData( IMC_PLAYERSYS_INIT_LOCAL* p_init, const IMC_CONTEST_SAVEDATA* save_data )
{
	int i;

	// ポケモン
	p_init->p_poke = ImcSaveData_GetContestPokemon( save_data );
	
	// アクセサリ
	p_init->acce_num = 0;
	for( i=0; i<IMC_SAVEDATA_CONTEST_ACCE_NUM; i++ ){
		// アクセサリ設定チェック
		if( ImcSaveData_CheckContestAcceDataSet( save_data, i ) ){
			p_init->p_acce[ p_init->acce_num ] = ImcSaveData_GetContestAcce( save_data, i );
			p_init->acce_num ++;
		}
	}

	// BGID
	p_init->bg_id = ImcSaveData_GetContestBgId( save_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	スプライト用の読み込むファイルを作成	イメージクリッププレイヤー用
 *
 *	@param	drawData	描画システムデータ
 *	@param	loadData	作成先
 *	@param	pp_acce		アクセサリデータテーブル
 *	@param	acce_num	アクセサリ数
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void imc_draw_MakeLoadSWSP_player( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData, const IMC_PLAYERSYS_INIT_LOCAL* cp_init, int heap )
{
	// SWSPのリソース登録データメモリを確保
	IMC_DRAW_SWSPResDataAllocMemory( loadData, heap );
	
	// アクセサリ用リソース
	loadAcceDataPlayer( drawData, loadData, cp_init, heap );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリデータの作成　プレイヤーなど用
 *
 *	@param	drawData		描画システムデータ
 *	@param	loadData		読み込みデータ格納先
 *	@param	pp_acce		アクセサリデータテーブル
 *	@param	acce_num	アクセサリ数
 *	@param	heap			使用するヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadAcceDataPlayer( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData, const IMC_PLAYERSYS_INIT_LOCAL* cp_init, int heap )
{
	int i;			// ループ用
	int cont_id;	// データ登録先ID
	void* buff;
	int acce_no;

	// アクセサリ用データ読み込み
	for(i=0; i<cp_init->acce_num; i++ ){
		acce_no = ImcSaveData_GetUtilAcceNo( cp_init->p_acce[i] );

		// 管理ID取得
		cont_id = IMC_ACCE_CHAR_CONT_ID( acce_no );
		
		// 同じものを登録済みでないかチェック
		if( RESM_CheckID( loadData->SWSP_charRes, cont_id ) == TRUE ){
			
			// キャラクタデータ取得
			buff = ArcUtil_Load(ARC_IMAGECLIP_GRA,
					IMC_ACCE_ARC_NO_GET( acce_no ),
					FALSE, heap, ALLOC_BOTTOM);

			// リソースマネージャに登録
			RESM_AddResNormal( loadData->SWSP_charRes, buff, cont_id );		

			// アンパック後のデータを登録
			NNS_G2dGetUnpackedCharacterData( buff, &loadData->SWSP_charTbl[ cont_id ].res_file );
			
			// スプライト描画システムポインタ設定
			loadData->SWSP_charTbl[ cont_id ].s_sys = drawData->SWSP_drawSys;
		}
	}

	// パレットデータ登録
	buff = ArcUtil_Load(ARC_IMAGECLIP_GRA,
			IMC_DRAW_ACCESSORIE_PLTT_ARC, FALSE, heap, ALLOC_BOTTOM);
	
	// リソースマネージャに登録
	RESM_AddResNormal( loadData->SWSP_plttRes, buff, IMC_DRAW_ACCESSORIE_PLTT_ID );		
	
	// アンパック
	NNS_G2dGetUnpackedPaletteData( buff,
			&loadData->SWSP_plttTbl[ IMC_DRAW_ACCESSORIE_PLTT_ID ].res_file );

	// 描画システムデータ
	loadData->SWSP_plttTbl[ IMC_DRAW_ACCESSORIE_PLTT_ID ].s_sys = drawData->SWSP_drawSys;

	// 読み込みすう
	loadData->SWSP_plttTbl[ IMC_DRAW_ACCESSORIE_PLTT_ID ].load_num = IMC_DRAW_ACCESSORIE_PLTT_NUM;
	
}




#ifdef PM_DEBUG
#include "include/system/wipe.h"
#include "include/gflib/display.h"
#include "include/gflib/gf_gx.h"
#include "include/application/imageClip/imc_drawsys.h"

//-------------------------------------
//	イメージクリップ外部データ
//=====================================
typedef struct {
	// イメージクリップセーブ領域
	const IMC_TELEVISION_SAVEDATA* p_imc_one_data;
	GF_BGL_INI*		BG_Ini;
	IMC_PLAYERSYS_PTR p_player;
} IMC_PLAY_WORK;

// VBlank
static void IMC_PlayTelevision_Vblank( void* p_work )
{
	IMC_PLAY_WORK* p_ip = p_work;

	IMC_PlayerVblank( p_ip->p_player );
	GF_BGL_VBlankFunc( p_ip->BG_Ini );
}

// チェック用プロック
PROC_RESULT IMC_PlayTelevision_ProcInit( PROC* proc, int* seq )
{
	IMC_PLAY_WORK* p_ip;
	IMC_PROC_PLAY_WORK* p_proc_w;
	
	// ヒープ作成
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_IMAGECLIP_DATA, 0x20000 );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_IMAGECLIP_DRAW, 0x40000 );

	// イメージクリップワーク作成
	p_ip = PROC_AllocWork( proc, sizeof( IMC_PLAY_WORK ), HEAPID_IMAGECLIP_DATA );
	memset( p_ip, 0, sizeof( IMC_PLAY_WORK ) );

	// VブランクHブランク関数設定
	sys_VBlankFuncChange( IMC_PlayTelevision_Vblank, p_ip );	// VBlankセット
	sys_HBlankIntrStop();	//HBlank割り込み停止

	// 外部からのデータを取得
	p_proc_w = PROC_GetParentWork( proc );

	// 描画関係
	IMC_DRAW_SetUp();
	
	p_ip->BG_Ini = GF_BGL_BglIniAlloc( HEAPID_IMAGECLIP_DRAW );

	{
		IMC_PLAYERSYS_INIT init;
		init.p_bg_ini = p_ip->BG_Ini;
		init.x		  = 80;
		init.y		  = 16;
		init.heap_id  = HEAPID_IMAGECLIP_DRAW;
		p_ip->p_player = IMC_TelevisionPlayerInit( &init, p_proc_w->p_imc_one_data );
	}

	return PROC_RES_FINISH;
}

PROC_RESULT IMC_PlayTelevision_ProcMain( PROC* proc, int* seq )
{
	IMC_PLAY_WORK* p_ip = PROC_GetWork( proc );
	
/*	static GXRgb color;

	if( sys.cont & PAD_BUTTON_L ){ OS_Printf( "color %x\n", ++color ); }
	if( sys.cont & PAD_BUTTON_R ){ OS_Printf( "color %x\n", --color ); }
	IMC_Player_SetColor( p_ip->p_player, color );//*/

	{
		//３Ｄ描画開始
		GF_G3X_Reset();

		NNS_G2dSetupSoftwareSpriteCamera();

		IMC_PlayerMain( p_ip->p_player );

		/* ジオメトリ＆レンダリングエンジン関連メモリのスワップ */
		GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
	}



	switch( *seq ){
	case 0:
		(*seq) ++;
		break;

	case 1:
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_SHUTTERIN_UP,
				WIPE_TYPE_SHUTTERIN_UP,
				WIPE_FADE_BLACK,
				WIPE_DEF_DIV,WIPE_DEF_SYNC,
				HEAPID_IMAGECLIP_DATA );
		(*seq) ++;
		break;
	
	case 2:
		if( WIPE_SYS_EndCheck() ){
			(*seq) ++;
		}
		break;

	case 3:
		if( sys.trg & PAD_BUTTON_A ){
			IMC_Player_SetAcceDrawFlag( p_ip->p_player, FALSE );
		}
		if( sys.trg & PAD_BUTTON_Y ){
			IMC_Player_SetAcceDrawFlag( p_ip->p_player, TRUE );
		}
		if( sys.trg & PAD_BUTTON_B ){
			(*seq)++;
		}
		break;

	case 4:
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,
				WIPE_FADE_BLACK,
				WIPE_DEF_DIV,WIPE_DEF_SYNC,
				HEAPID_IMAGECLIP_DATA );
		(*seq) ++;
		break;

	case 5:
		if( WIPE_SYS_EndCheck() ){
			return PROC_RES_FINISH;
		}
		break;
	}
	return PROC_RES_CONTINUE;
}

PROC_RESULT IMC_PlayTelevision_ProcEnd( PROC* proc, int* seq )
{
	IMC_PLAY_WORK* p_ip = PROC_GetWork( proc );

	IMC_PlayerEnd( p_ip->p_player );

	// 描画システム破棄
	sys_FreeMemoryEz( p_ip->BG_Ini );

	// 描画面設定破棄
	IMC_DRAW_PutBack();

	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
	sys_HBlankIntrStop();	//HBlank割り込み停止

	// ワーク破棄
	PROC_FreeWork( proc );

	// ヒープ破棄
	sys_DeleteHeap( HEAPID_IMAGECLIP_DATA );
	sys_DeleteHeap( HEAPID_IMAGECLIP_DRAW );

	return PROC_RES_FINISH;
}

#endif

