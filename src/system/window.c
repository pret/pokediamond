//============================================================================================
/**
 * @file	window.c
 * @brief	ウィンドウ表示
 * @author	Hiroyuki Nakamura
 * @date	2005.10.13
 */
//============================================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/lib_pack.h"
#include "system/winframe.naix"
#include "system/menu_gra.naix"
#include "system/softsprite.h"
#include "system/clact_tool.h"
#include "system/gra_tool.h"
#include "system/pmfprint.h"
#include "poketool/poke_tool.h"
#include "field/field_board.naix"
#include "../field/field_clact.h"
#include "../field/field_cutin.naix"

#define WINDOW_H_GLOBAL
#include "system/window.h"


//============================================================================================
//	定数定義
//============================================================================================
#define	MAKE_CURSOR_CGX_SIZ		( 0x20*4*3 )	// 送りカーソルサイズ

// 看板ウィンドウマップ開始アーカイブID
#define	BOARD_TOWNMAP_START		( NARC_field_board_board_town_dmy_NCGR )	// 街
#define	BOARD_ROADMAP_START		( NARC_field_board_board_road000_NCGR )		// 道

#define	TIMEWAIT_ICON_SIZE	( 0x20 * 4 * 8 )	// 待機アイコンのサイズ
#define	TIMEWAIT_WAIT		( 16 )				// 待機アイコンのアニメウェイト

// 待機アイコンワーク
typedef struct {
	GF_BGL_BMPWIN * win;			// 表示するBMP
	u8	cgx[TIMEWAIT_ICON_SIZE];	// カーソルキャラ作成領域
	u8	backup[0x20*4];				// キャラバックアップ領域
	u16	cgxpos;						// 会話ウィンドウの転送位置
	u8	cnt;						// カウンタ
	u8	pat:7;						// アニメ番号
	u8	seq:2;						// シーケンス
}TIMEWAIT_ICON;

// ポケモン表示ウィンドウワーク
typedef struct {
	FIELD_CLACT fcat;		// フィールドセルアクターワーク
	CATS_ACT_PTR	cap;	// セルアクター
	GF_BGL_INI * bgl;		// BGL
	u8	frm;				// 描画フレーム
	u8	px;					// 表示X座標
	u8	py;					// 表示Y座標
	u8	cmd;				// 外部コマンド
}POKEWIN_WORK;

#define	POKEWIN_CLA_CHR_ID	( 89301 )	// ポケモンセルアクターのキャラリソースID
#define	POKEWIN_CLA_PAL_ID	( 89301 )	// ポケモンセルアクターのパレットリソースID
#define	POKEWIN_CLA_CEL_ID	( 89301 )	// ポケモンセルアクターのセルリソースID
#define	POKEWIN_CLA_ANM_ID	( 89301 )	// ポケモンセルアクターのセルアニメリソースID

#define	POKEWIN_OBJCGX_SIZ		( 32*10*10 )				// ポケモンOBJのCGXサイズ（１パターン）
#define	POKEWIN_OBJCGX_SIZ_ALL	( POKEWIN_OBJCGX_SIZ*2 )	// ポケモンOBJのCGXサイズ（全体）


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void CursorCgxMake( GF_BGL_BMPWIN * win, u16 cgxnum );

static void BoardMapCgxSet(
				GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 type, u16 map, u32 heap );

static void TimeWaitIconPut( TIMEWAIT_ICON * wk, u32 flg );
static void TimeWaitIconMain( TCB_PTR tcb, void * work );

static POKEWIN_WORK * PokeWin_TcbAdd( GF_BGL_INI * bgl, u8 frm, u8 px, u8 py, u32 heap );
static void PokeWin_ClactSet( POKEWIN_WORK * wk, u32 heap );
static void PokeWin_LoadRes( POKEWIN_WORK * wk );
static void PokeWin_ClactAdd( POKEWIN_WORK * wk, u8 px, u8 py );
static void PokeWin_PokeGraSetCore( FIELD_CLACT * wk, SOFT_SPRITE_ARC * ssa );
static void PokeWin_PokeGraSetEz( FIELD_CLACT * wk, u16 mons, u8 sex );
static void PokeWin_PokeGraSetPP( FIELD_CLACT * wk, POKEMON_PARAM * pp );
static void PokeWin_Main( TCB_PTR tcb, void * work );
static void PokeWinFrameWrite( POKEWIN_WORK * wk, u8 pal, u16 cgx );
static void PokeWinFrameClear( POKEWIN_WORK * wk );


//============================================================================================
//	グローバル変数
//============================================================================================
// ポケモンセルアクターの登録データ
static const TCATS_OBJECT_ADD_PARAM_S PokeWinAct_S =
{
	0, 0, 0,
	0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
	{
		POKEWIN_CLA_CHR_ID, POKEWIN_CLA_PAL_ID,
		POKEWIN_CLA_CEL_ID, POKEWIN_CLA_ANM_ID, 0, 0,
	},
	0, 0
};


//============================================================================================
//============================================================================================
//	メニューウィンドウ
//============================================================================================
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * メニューウィンドウのキャラをセット
 *
 * @param	ini			BGLデータ
 * @param	frmnum		BGフレーム
 * @param	cgx			キャラ転送位置
 * @param	win_num		ウィンドウ番号
 * @param	heap		ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void MenuWinCgxSet( GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 win_num, u32 heap )
{
	if( win_num == MENU_TYPE_SYSTEM ){
		ArcUtil_BgCharSet(
			ARC_WINFRAME, NARC_winframe_system_ncgr, ini, frmnum, cgx, 0, 0, heap );
	}else{
		ArcUtil_BgCharSet(
			ARC_WINFRAME, NARC_winframe_fmenu_ncgr, ini, frmnum, cgx, 0, 0, heap );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * メニューウィンドウパレットのアーカイブインデックス取得
 *
 * @param	none
 *
 * @return	アーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
u32 MenuWinPalArcGet(void)
{
	return ( NARC_winframe_system_nclr );
}

//--------------------------------------------------------------------------------------------
/**
 * メニューウィンドウのグラフィックをセット
 *
 * @param	ini			BGLデータ
 * @param	frmnum		BGフレーム
 * @param	cgx			キャラ転送位置
 * @param	pal			パレット番号
 * @param	win_num		ウィンドウ番号
 * @param	heap		ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void MenuWinGraphicSet( GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 pal, u8 win_num, u32 heap )
{
	u32	arc;

	// キャラ
	if( win_num == MENU_TYPE_SYSTEM ){
		arc = NARC_winframe_system_ncgr;
	}else{
		arc = NARC_winframe_fmenu_ncgr;
	}
	ArcUtil_BgCharSet( ARC_WINFRAME, arc, ini, frmnum, cgx, 0, 0, heap );

	// パレット
	if( win_num == MENU_TYPE_UG ){
		arc = NARC_winframe_ugmenu_win_nclr;
	}else{
		arc = NARC_winframe_system_nclr;
	}
	if( frmnum < GF_BGL_FRAME0_S ){
		ArcUtil_PalSet( ARC_WINFRAME, arc , PALTYPE_MAIN_BG, pal*0x20, 0x20, heap );
	}else{
		ArcUtil_PalSet( ARC_WINFRAME, arc , PALTYPE_SUB_BG, pal*0x20, 0x20, heap );
	}
}

//--------------------------------------------------------------------------------------------
/**
 *	メニューウインドウ描画メイン
 *
 * @param	frm			BGフレームナンバー(bg_sys)
 * @param	px			Ｘ座標
 * @param	py			Ｙ座標
 * @param	sx			Ｘサイズ
 * @param	sy			サイズ
 * @param	pal			使用パレット
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BmpMenuWinWriteMain(
				GF_BGL_INI * ini, u8 frm, u8 px, u8 py, u8 sx, u8 sy, u8 pal, u16 cgx )
{
	GF_BGL_ScrFill( ini, frm, cgx,   px-1,  py-1, 1,  1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+1, px,    py-1, sx, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+2, px+sx, py-1, 1,  1, pal );

	GF_BGL_ScrFill( ini, frm, cgx+3, px-1,  py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+5, px+sx, py, 1, sy, pal );

	GF_BGL_ScrFill( ini, frm, cgx+6, px-1,  py+sy, 1,  1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+7, px,    py+sy, sx, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+8, px+sx, py+sy, 1,  1, pal );
}

//--------------------------------------------------------------------------------------------
/**
 * メニューウィンドウを描画
 *
 * @param	win			BMPウィンドウデータ
 * @param	trans_sw	転送スイッチ
 * @param	win_cgx		ウィンドウキャラ位置
 * @param	pal			パレット
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpMenuWinWrite( GF_BGL_BMPWIN * win, u8 trans_sw, u16 win_cgx, u8 pal )
{
	u8	frm = GF_BGL_BmpWinGet_Frame( win );

	BmpMenuWinWriteMain(
		win->ini, frm,
		GF_BGL_BmpWinGet_PosX( win ),
		GF_BGL_BmpWinGet_PosY( win ),
		GF_BGL_BmpWinGet_SizeX( win ),
		GF_BGL_BmpWinGet_SizeY( win ),
		pal, win_cgx );

	if( trans_sw == WINDOW_TRANS_ON ){
//		GF_BGL_LoadScreenReq( win->ini, frm );
		GF_BGL_BmpWinOn( win );
	}
}

//--------------------------------------------------------------------------------------------
/**
 *	メニューウィンドウをクリア
 *
 * @param	win			BMPウィンドウデータ
 * @param	trans_sw	転送スイッチ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpMenuWinClear( GF_BGL_BMPWIN * win, u8 trans_sw )
{
	u8	frm = GF_BGL_BmpWinGet_Frame( win );

	GF_BGL_ScrFill(
		win->ini, frm, 0,
		GF_BGL_BmpWinGet_PosX( win ) - 1,
		GF_BGL_BmpWinGet_PosY( win ) - 1,
		GF_BGL_BmpWinGet_SizeX( win ) + 2,
		GF_BGL_BmpWinGet_SizeY( win ) + 2,
		0 );

	if( trans_sw == WINDOW_TRANS_ON ){
//		GF_BGL_LoadScreenReq( win->ini, frm );
		GF_BGL_BmpWinOff( win );
	}
}


//============================================================================================
//============================================================================================
//	会話ウィンドウ
//============================================================================================
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 *	会話ウインドウキャラのアーカイブインデックス取得
 *
 * @param	id		ウィンドウID
 *
 * @return	アーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
u32 TalkWinCgxArcGet( u32 id )
{
	return ( NARC_winframe_talk_win00_ncgr + id );
}

//--------------------------------------------------------------------------------------------
/**
 *	会話ウインドウパレットのアーカイブインデックス取得
 *
 * @param	id		ウィンドウID
 *
 * @return	アーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
u32 TalkWinPalArcGet( u32 id )
{
	return ( NARC_winframe_talk_win00_nclr + id );
}

//--------------------------------------------------------------------------------------------
/**
 *	会話ウインドウセット
 *
 * @param	ini			BGLデータ
 * @param	frm			BGフレームナンバー(bg_sys)
 * @param	cgx			キャラセット位置
 * @param	pal			使用パレット
 * @param	win_num		ウィンドウ番号
 * @param	heap		ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TalkWinGraphicSet( GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 pal, u8 win_num, u32 heap )
{
	ArcUtil_BgCharSet( ARC_WINFRAME, TalkWinCgxArcGet(win_num), ini, frmnum, cgx, 0, 0, heap );
	if( frmnum < GF_BGL_FRAME0_S ){
		ArcUtil_PalSet(
			ARC_WINFRAME, TalkWinPalArcGet(win_num), PALTYPE_MAIN_BG, pal*0x20, 0x20, heap );
	}else{
		ArcUtil_PalSet(
			ARC_WINFRAME, TalkWinPalArcGet(win_num), PALTYPE_SUB_BG, pal*0x20, 0x20, heap );
	}
}

//--------------------------------------------------------------------------------------------
/**
 *	会話ウインドウ描画メイン
 *
 * @param	ini			BGLデータ
 * @param	frm			BGフレームナンバー(bg_sys)
 * @param	px			Ｘ座標
 * @param	py			Ｙ座標
 * @param	sx			Ｘサイズ
 * @param	sy			サイズ
 * @param	pal			使用パレット
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BmpTalkWinWriteMain(
				GF_BGL_INI * ini, u8 frm, u8 px, u8 py, u8 sx, u8 sy, u8 pal, u16 cgx )
{
	GF_BGL_ScrFill( ini, frm, cgx, px-2, py-1, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+1, px-1, py-1, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+2, px, py-1, sx, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+3, px+sx,	py-1, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+4, px+sx+1, py-1, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+5, px+sx+2, py-1, 1, 1, pal );

	GF_BGL_ScrFill( ini, frm, cgx+6, px-2, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+7, px-1, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+9, px+sx, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+10, px+sx+1, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+11, px+sx+2, py, 1, sy, pal );

	GF_BGL_ScrFill( ini, frm, cgx+12, px-2, py+sy, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+13, px-1, py+sy, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+14, px, py+sy, sx, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+15, px+sx, py+sy, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+16, px+sx+1, py+sy, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+17, px+sx+2, py+sy, 1, 1, pal );
}

//--------------------------------------------------------------------------------------------
/**
 * 会話ウィンドウスクリーンデータを、BitmapWindowに関連付けられた
 * BGフレームのスクリーンバッファにセットする
 *
 * @param   win		
 * @param   charno		
 * @param   palno		
 *
 */
//--------------------------------------------------------------------------------------------
void BmpTalkWinScreenSet( GF_BGL_BMPWIN * win, u32 charno, u32 palno )
{
	BmpTalkWinWriteMain(
		win->ini,
		GF_BGL_BmpWinGet_Frame( win ),
		GF_BGL_BmpWinGet_PosX( win ),
		GF_BGL_BmpWinGet_PosY( win ),
		GF_BGL_BmpWinGet_SizeX( win ),
		GF_BGL_BmpWinGet_SizeY( win ),
		palno, charno );
}

//--------------------------------------------------------------------------------------------
/**
 * 会話ウィンドウを描画
 *
 * @param	win			BMPウィンドウデータ
 * @param	trans_sw	転送スイッチ
 * @param	win_cgx		ウィンドウキャラ位置
 * @param	pal			パレット
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpTalkWinWrite( GF_BGL_BMPWIN * win, u8 trans_sw, u16 win_cgx, u8 pal )
{
	BmpTalkWinScreenSet( win, win_cgx, pal );

	if( trans_sw == WINDOW_TRANS_ON ){
//		GF_BGL_LoadScreenReq( win->ini, frm );
		GF_BGL_BmpWinOn( win );
	}

	CursorCgxMake( win, win_cgx );
//	PokeFontTrgCursorCgxSet( win_cgx );
}

//--------------------------------------------------------------------------------------------
/**
 *	会話ウィンドウをクリア
 *
 * @param	win			BMPウィンドウデータ
 * @param	trans_sw	転送スイッチ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpTalkWinClear( GF_BGL_BMPWIN * win, u8 trans_sw )
{
	u8	frm = GF_BGL_BmpWinGet_Frame( win );

	GF_BGL_ScrFill(
		win->ini, frm, 0,
		GF_BGL_BmpWinGet_PosX( win ) - 2,
		GF_BGL_BmpWinGet_PosY( win ) - 1,
		GF_BGL_BmpWinGet_SizeX( win ) + 5,
		GF_BGL_BmpWinGet_SizeY( win ) + 2,
		0 );

	if( trans_sw == WINDOW_TRANS_ON ){
//		GF_BGL_LoadScreenReq( win->ini, frm );
		GF_BGL_BmpWinOff( win );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * キャラ作成
 *
 * @param	src			転送するキャラデータ
 * @param	src_x		読み込み元読み込み開始X座標
 * @param	src_y		読み込み元読み込み開始Y座標
 * @param	src_dx		転送するキャラのXサイズ
 * @param	src_dy		転送するキャラのYサイズ
 * @param	buf			転送先のキャラデータ
 * @param	buf_sx		転送先のキャラのXサイズ
 * @param	buf_sy		転送先のキャラのYサイズ
 * @param	win_x		書き込み先書き込み開始X座標
 * @param	win_y		書き込み先書き込み開始Y座標
 * @param	win_dx		描画範囲Xサイズ
 * @param	win_dy		描画範囲Yサイズ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BmpPrintCharMake(
			void * src, u16 src_x, u16 src_y, u16 src_dx, u16 src_dy,
			void * buf, u16 buf_sx, u16 buf_sy, u16 win_x, u16 win_y, u16 win_dx, u16 win_dy )
{
	BMPPRT_HEADER	src_data;
	BMPPRT_HEADER	dst_data;

	src_data.adrs	= (u8 *)src;
	src_data.size_x = src_dx;
	src_data.size_y = src_dy;

	dst_data.adrs	= (u8 *)buf;
	dst_data.size_x = buf_sx;
	dst_data.size_y = buf_sy;

	GF_BMP_PrintMain( &src_data, &dst_data, src_x, src_y, win_x, win_y, win_dx, win_dy, 0 );
}

//--------------------------------------------------------------------------------------------
/**
 * 送りカーソルセット
 *
 * @param	win			BMPウィンドウデータ
 * @param	cgxnum		ウィンドウ位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CursorCgxMake( GF_BGL_BMPWIN * win, u16 cgxnum )
{
	u32	heap;
	u8 * wincgx;
	u8 * scrcgx;
	u8 * curcgx;
	void * arc;
	u8	frm;
	u8	i;

	heap   = GF_BGL_HeapIDGet( win->ini );
	frm    = GF_BGL_BmpWinGet_Frame( win );
	wincgx = sys_AllocMemory( heap, MAKE_CURSOR_CGX_SIZ );
	scrcgx = GF_BGL_CgxGet( frm );

	{
		NNSG2dCharacterData * dat;
		arc = ArcUtil_CharDataGet( ARC_WINFRAME, NARC_winframe_win_cursol1_ncgr, 0, &dat, heap );
		curcgx = (u8 *)dat->pRawData;
	}

	for( i=0; i<3; i++ ){
		memcpy( &wincgx[i*0x20*4+0x20*0], &scrcgx[(cgxnum+10)*0x20], 0x20 );
		memcpy( &wincgx[i*0x20*4+0x20*1], &scrcgx[(cgxnum+11)*0x20], 0x20 );
		memcpy( &wincgx[i*0x20*4+0x20*2], &scrcgx[(cgxnum+10)*0x20], 0x20 );
		memcpy( &wincgx[i*0x20*4+0x20*3], &scrcgx[(cgxnum+11)*0x20], 0x20 );
	}

	BmpPrintCharMake( curcgx, 4, 0, 12, 16*3, wincgx, 12, 16*3, 1, 0, 12, 16*3 );

	GF_BGL_LoadCharacter( win->ini, frm, wincgx, MAKE_CURSOR_CGX_SIZ, cgxnum+18 );
	PokeFontTrgCursorCgxSet( cgxnum );

	sys_FreeMemoryEz( arc );
	sys_FreeMemoryEz( wincgx );
}


//--------------------------------------------------------------------------------------------
/**
 * 会話ウィンドウのカラー０のドットを指定カラーに変更する
 *
 * @param	ini			BGLデータ
 * @param	frmnum		BGフレームナンバー(bg_sys)
 * @param	cgx			キャラセット位置
 * @param	cal			変更カラー
 * @param	heap		ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TalkWinGraphicNullSet( GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 col, u8 win_num, u32 heap )
{
	void * arc;
	NNSG2dCharacterData * dat;
	u8 * curcgx;
	u32	i;
	u8	dott, dotu;

	arc = ArcUtil_CharDataGet(
			ARC_WINFRAME, TalkWinCgxArcGet(win_num), 0, &dat, heap );
	curcgx = sys_AllocMemory( heap, 0x20*18 );
	memcpy( curcgx, dat->pRawData, 0x20*18 );

	for( i=0; i<0x20*18; i++ ){
		dott = curcgx[i] >> 4;
		dotu = curcgx[i] & 0x0f;
		if( dott == 0 ){ dott = col; }
		if( dotu == 0 ){ dotu = col; }
		curcgx[i] = (dott<<4)|dotu;
	}

	GF_BGL_LoadCharacter( ini, frmnum, curcgx, 0x20*18, cgx );
	sys_FreeMemoryEz( arc );
	sys_FreeMemoryEz( curcgx );
}


//============================================================================================
//============================================================================================
//	看板ウィンドウ
//============================================================================================
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 看板ウインドウセット
 *
 * @param	ini			BGLデータ
 * @param	frmnum		BGフレームナンバー(bg_sys)
 * @param	cgx			キャラセット位置
 * @param	pal			使用パレット
 * @param	type		看板タイプ
 * @param	map			マップ番号（タウンマップ、標識）
 * @param	heap		ヒープID
 *
 * @return	none
 *
 *	type = *_POST, *_INFO の場合は、map = 0 で良い
 */
//--------------------------------------------------------------------------------------------
void BoardWinGraphicSet(
		GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 pal, u8 type, u16 map, u32 heap )
{
	// ウィンドウキャラ転送
	ArcUtil_BgCharSet(
		ARC_FIELD_BOARD, NARC_field_board_kanb_win00_NCGR,
		ini, frmnum, cgx, BOARD_WIN_CGX_SIZ*0x20, 0, heap );

	// ウィンドウパレット転送
	{
		NNSG2dPaletteData * nns;
		void * buf;
		u16 * dat;
		
		buf = ArchiveDataLoadMalloc( ARC_FIELD_BOARD, NARC_field_board_kanb_win00_NCLR, heap );
		NNS_G2dGetUnpackedPaletteData( buf, &nns );
		dat = (u16 *)nns->pRawData;
		GF_BGL_PaletteSet( frmnum, (void *)&dat[type*16], 0x20, pal*0x20 );
		sys_FreeMemory( heap, buf );
	}

	// 地図セット
	if( type == BOARD_TYPE_TOWN || type == BOARD_TYPE_ROAD ){
//		BoardMapSet( ini, frmnum, cgx+BOARD_WIN_CGX_SIZ, pal, type, map, heap );
		BoardMapCgxSet( ini, frmnum, cgx+BOARD_WIN_CGX_SIZ, type, map, heap );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 看板ウインドウマップデータセット
 *
 * @param	ini			BGLデータ
 * @param	frmnum		BGフレームナンバー
 * @param	cgx			キャラセット位置
 * @param	type		看板タイプ
 * @param	map			マップ番号（タウンマップ、標識）
 * @param	heap		ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BoardMapCgxSet(
				GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 type, u16 map, u32 heap )
{
	if( type == BOARD_TYPE_TOWN ){
		map += BOARD_TOWNMAP_START;
	}else{
		map += BOARD_ROADMAP_START;
	}

	ArcUtil_BgCharSet(
		ARC_FIELD_BOARD, map, ini, frmnum, cgx, BOARD_MAP_CGX_SIZ*0x20, 0, heap );
}

//--------------------------------------------------------------------------------------------
/**
 *	看板ウインドウ描画メイン（町、道看板）
 *
 * @param	ini			BGLデータ
 * @param	frm			BGフレームナンバー(bg_sys)
 * @param	px			Ｘ座標
 * @param	py			Ｙ座標
 * @param	sx			Ｘサイズ
 * @param	sy			サイズ
 * @param	pal			使用パレット
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BmpBoardWinWriteMain(
				GF_BGL_INI * ini, u8 frm, u8 px, u8 py, u8 sx, u8 sy, u8 pal, u16 cgx )
{
	GF_BGL_ScrFill( ini, frm, cgx, px-9, py-1, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+1, px-8, py-1, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+2, px-7, py-1, sx+7, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+3, px+sx,	py-1, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+4, px+sx+1, py-1, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+5, px+sx+2, py-1, 1, 1, pal );

	GF_BGL_ScrFill( ini, frm, cgx+6, px-9, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+7, px-8, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+8, px-1, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+9, px+sx, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+10, px+sx+1, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+11, px+sx+2, py, 1, sy, pal );

	GF_BGL_ScrFill( ini, frm, cgx+12, px-9, py+sy, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+13, px-8, py+sy, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+14, px-7, py+sy, sx+7, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+15, px+sx, py+sy, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+16, px+sx+1, py+sy, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+17, px+sx+2, py+sy, 1, 1, pal );
}

//--------------------------------------------------------------------------------------------
/**
 *	看板ウインドウマップ描画
 *
 * @param	win		BMPウィンドウデータ
 * @param	cgx		マップキャラ位置
 * @param	pal		パレット
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BmpBoardMapWrite( GF_BGL_BMPWIN * win, u16 cgx, u8 pal )
{
	u16	i, j;
	u16	px, py;
	u8	frm;
	
	frm = GF_BGL_BmpWinGet_Frame( win );
	px  = GF_BGL_BmpWinGet_PosX( win ) - 7;
	py  = GF_BGL_BmpWinGet_PosY( win );

	for( i=0; i<4; i++ ){
		for( j=0; j<6; j++ ){
			GF_BGL_ScrFill( win->ini, frm, cgx+i*6+j, px+j, py+i, 1, 1, pal );
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 看板ウィンドウを描画
 *
 * @param	win			BMPウィンドウデータ
 * @param	trans_sw	転送スイッチ
 * @param	win_cgx		ウィンドウキャラ位置
 * @param	type		看板タイプ
 * @param	pal			パレット
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpBoardWinWrite( GF_BGL_BMPWIN * win, u8 trans_sw, u16 win_cgx, u8 pal, u8 type )
{
	u8	frm = GF_BGL_BmpWinGet_Frame( win );

	// 町、道
	if( type == BOARD_TYPE_TOWN || type == BOARD_TYPE_ROAD ){
		BmpBoardWinWriteMain(
			win->ini, frm,
			GF_BGL_BmpWinGet_PosX( win ),
			GF_BGL_BmpWinGet_PosY( win ),
			GF_BGL_BmpWinGet_SizeX( win ),
			GF_BGL_BmpWinGet_SizeY( win ),
			pal, win_cgx );

		BmpBoardMapWrite( win, win_cgx+BOARD_WIN_CGX_SIZ, pal );
	// 町、道以外
	}else{
		// データ構成が会話ウィンドウと同じなので、会話ウィンドウ描画
		BmpTalkWinWriteMain(
			win->ini, frm,
			GF_BGL_BmpWinGet_PosX( win ),
			GF_BGL_BmpWinGet_PosY( win ),
			GF_BGL_BmpWinGet_SizeX( win ),
			GF_BGL_BmpWinGet_SizeY( win ),
			pal, win_cgx );
	}

	if( trans_sw == WINDOW_TRANS_ON ){
		GF_BGL_BmpWinOn( win );
	}

	CursorCgxMake( win, win_cgx );
}

//--------------------------------------------------------------------------------------------
/**
 *	看板ウィンドウをクリア
 *
 * @param	win			BMPウィンドウデータ
 * @param	type		看板タイプ
 * @param	trans_sw	転送スイッチ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpBoardWinClear( GF_BGL_BMPWIN * win, u8 type, u8 trans_sw )
{
	u8	frm = GF_BGL_BmpWinGet_Frame( win );

	// 町、道
	if( type == BOARD_TYPE_TOWN || type == BOARD_TYPE_ROAD ){
		GF_BGL_ScrFill(
			win->ini, frm, 0,
			GF_BGL_BmpWinGet_PosX( win ) - 9,
			GF_BGL_BmpWinGet_PosY( win ) - 1,
			GF_BGL_BmpWinGet_SizeX( win ) + 11,
			GF_BGL_BmpWinGet_SizeY( win ) + 2,
			0 );
	}else{
		GF_BGL_ScrFill(
			win->ini, frm, 0,
			GF_BGL_BmpWinGet_PosX( win ) - 2,
			GF_BGL_BmpWinGet_PosY( win ) - 1,
			GF_BGL_BmpWinGet_SizeX( win ) + 4,
			GF_BGL_BmpWinGet_SizeY( win ) + 2,
			0 );
	}

	if( trans_sw == WINDOW_TRANS_ON ){
		GF_BGL_BmpWinOff( win );
	}
}


//============================================================================================
//============================================================================================
//	待機アイコン
//============================================================================================
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 待機アイコン表示タスク追加
 *
 * @param	win		会話ウィンドウのBMP
 * @param	cgxpos	会話ウィンドウ枠キャラ（TalkWinGraphicSetなど）の転送位置
 *
 * @return	待機アイコンのワーク
 */
//--------------------------------------------------------------------------------------------
void * TimeWaitIconAdd( GF_BGL_BMPWIN * win, u32 cgxpos )
{
	TIMEWAIT_ICON * wk;
	u32	heap;
	u8 * scrcgx;
	u8 * curcgx;
	u8 * back_win;
	void * arc;
	u8	frm;
	u8	i;

	heap   = GF_BGL_HeapIDGet( win->ini );
	frm    = GF_BGL_BmpWinGet_Frame( win );
	scrcgx = GF_BGL_CgxGet( frm );

//	wk = TCB_GetWork( PMDS_taskAdd(TimeWaitIconMain,sizeof(TIMEWAIT_ICON),0,heap) );
	wk = sys_AllocMemory( heap, sizeof(TIMEWAIT_ICON) );

	// 転送領域バックアップ
	memcpy( wk->backup, &scrcgx[(cgxpos+18)*0x20], 0x20*4 );
	// 作成領域初期化
	back_win = (u8 *)sys_AllocMemory( heap, 0x20*4 );
	memcpy( &back_win[0x20*0], &scrcgx[(cgxpos+10)*0x20], 0x20 );
	memcpy( &back_win[0x20*1], &scrcgx[(cgxpos+11)*0x20], 0x20 );
	memcpy( &back_win[0x20*2], &scrcgx[(cgxpos+10)*0x20], 0x20 );
	memcpy( &back_win[0x20*3], &scrcgx[(cgxpos+11)*0x20], 0x20 );
	for( i=0; i<8; i++ ){
		memcpy( &wk->cgx[0x20*4*i], back_win, 0x20*4 );
	}
	sys_FreeMemoryEz( back_win );

	{
		NNSG2dCharacterData * dat;
		arc = ArcUtil_CharDataGet( ARC_WINFRAME, NARC_winframe_win_cursol2_ncgr, 0, &dat, heap );
		curcgx = (u8 *)dat->pRawData;
	}

	BmpPrintCharMake( curcgx, 0, 0, 16, 16*8, wk->cgx, 16, 16*8, 0, 0, 16, 16*8 );

	sys_FreeMemoryEz( arc );

	wk->win = win;
	wk->cgxpos = (u16)cgxpos;
	wk->cnt = 0;
	wk->pat = 0;
	wk->seq = 0;

	VIntrTCB_Add( TimeWaitIconMain, wk, 0 );
	TimeWaitIconPut( wk, 1 );

	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * 待機アイコン表示
 *
 * @param	wk		待機アイコンのワーク
 * @param	cgxpos	会話ウィンドウの転送位置
 *
 * @return	none
 *
 * @li	flg = 0 : 通常
 * @li	flg = 1 : スクリーンも転送
 * @li	flg = 2 : 終了時
 */
//--------------------------------------------------------------------------------------------
static void TimeWaitIconPut( TIMEWAIT_ICON * wk, u32 flg )
{
	u8	frm, px, py, sx;

	frm = GF_BGL_BmpWinGet_Frame( wk->win );
	px  = GF_BGL_BmpWinGet_PosX( wk->win );
	py  = GF_BGL_BmpWinGet_PosY( wk->win );
	sx  = GF_BGL_BmpWinGet_SizeX( wk->win );

	if( flg == 2 ){
		GF_BGL_LoadCharacter( wk->win->ini, frm, wk->backup, 0x20*4, wk->cgxpos+18 );
		GF_BGL_ScrFill(
			wk->win->ini, frm, wk->cgxpos+10, px+sx+1, py+2, 1, 1, GF_BGL_SCRWRT_PALNL );
		GF_BGL_ScrFill(
			wk->win->ini, frm, wk->cgxpos+11, px+sx+2, py+2, 1, 1, GF_BGL_SCRWRT_PALNL );
		GF_BGL_ScrFill(
			wk->win->ini, frm, wk->cgxpos+10, px+sx+1, py+3, 1, 1, GF_BGL_SCRWRT_PALNL );
		GF_BGL_ScrFill(
			wk->win->ini, frm, wk->cgxpos+11, px+sx+2, py+3, 1, 1, GF_BGL_SCRWRT_PALNL );
		GF_BGL_LoadScreenReq( wk->win->ini, frm );
		return;
	}

	GF_BGL_LoadCharacter(
		wk->win->ini, frm, &wk->cgx[0x20*4*wk->pat], 0x20*4, wk->cgxpos+18 );

	if( flg == 0 ){ return; }

	GF_BGL_ScrFill(
		wk->win->ini, frm, wk->cgxpos+18, px+sx+1, py+2, 1, 1, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->win->ini, frm, wk->cgxpos+19, px+sx+2, py+2, 1, 1, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->win->ini, frm, wk->cgxpos+20, px+sx+1, py+3, 1, 1, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->win->ini, frm, wk->cgxpos+21, px+sx+2, py+3, 1, 1, GF_BGL_SCRWRT_PALNL );

	GF_BGL_LoadScreenReq( wk->win->ini, frm );
}

//--------------------------------------------------------------------------------------------
/**
 * 待機アイコンメインタスク
 *
 * @param	tcb
 * @param	work
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TimeWaitIconMain( TCB_PTR tcb, void * work )
{
	TIMEWAIT_ICON * wk = work;

	if( wk->seq != 0 ){
        if(wk->seq == 1){
            TimeWaitIconPut( wk, 2 );
        }
		TCB_Delete( tcb );
		return;
	}
	wk->cnt++;

	if( wk->cnt == TIMEWAIT_WAIT ){
		wk->cnt = 0;
		wk->pat = ( wk->pat + 1 ) & 7;
		TimeWaitIconPut( wk, 0 );
	}
}

//------------------------------------------------------------------
/**
 * 待機アイコンタスクのワークを解放するためだけのタスク
 *（割り込み中にメモリ解放をさせないため）
 *
 * @param   tcb		
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void TimeWaitIconWorkFreeTask( TCB_PTR tcb, void* wk )
{
	sys_FreeMemoryEz( wk );
	TCB_Delete( tcb );
}

//--------------------------------------------------------------------------------------------
/**
 * 待機アイコン表示タスク削除リクエスト
 *
 * @param	work	待機アイコンのワーク
 *
 * @return	none
 *
 *	workも削除されます
 */
//--------------------------------------------------------------------------------------------
void TimeWaitIconDel( void * work )
{
	TIMEWAIT_ICON * wk = work;

	VWaitTCB_Add( TimeWaitIconWorkFreeTask, wk, 0 );

	wk->seq = 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 待機アイコン表示タスク削除リクエスト
 *
 * @param	work	待機アイコンのワーク
 *
 * @return	none
 *
 *	workも削除されます  SCRは書き換えません
 */
//--------------------------------------------------------------------------------------------
void TimeWaitIconTaskDel( void * work )
{
	TIMEWAIT_ICON * wk = work;

	VWaitTCB_Add( TimeWaitIconWorkFreeTask, wk, 0 );

	wk->seq = 2;
}


//============================================================================================
//============================================================================================
//	ポケモン表示ウィンドウ
//============================================================================================
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ポケモンウィンドウ表示（番号、性別指定）
 *
 * @param	bgl		BGLデータ
 * @param	frm		表示BGフレーム
 * @param	px		表示X座標
 * @param	py		表示Y座標
 * @param	pal		ウィンドウパレット
 * @param	cgx		ウィンドウキャラ
 * @param	mons	ポケモン番号
 * @param	sex		ポケモンの性別
 * @param	heap	ヒープID
 *
 * @return	コマンドのポインタ
 *
 *	表示座標は、枠を含めない値を指定すること
 */
//--------------------------------------------------------------------------------------------
u8 * PokeWindowPut(
		GF_BGL_INI * bgl, u8 frm, u8 px, u8 py, u8 pal, u16 cgx, u16 mons, u8 sex, int heap )
{
	POKEWIN_WORK * wk = PokeWin_TcbAdd( bgl, frm, px, py, heap );

	PokeWin_ClactSet( wk, heap );
	PokeWin_LoadRes( wk );
	PokeWin_ClactAdd( wk, px, py );
	PokeWin_PokeGraSetEz( &wk->fcat, mons, sex );
	PokeWinFrameWrite( wk, pal, cgx );

	GF_BGL_LoadScreenReq( bgl, frm );

	return &wk->cmd;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンウィンドウ表示（POKEMON_PARAM指定）
 *
 * @param	bgl		BGLデータ
 * @param	frm		表示BGフレーム
 * @param	px		表示X座標
 * @param	py		表示Y座標
 * @param	pal		ウィンドウパレット
 * @param	cgx		ウィンドウキャラ
 * @param	pp		POKEMON_PARAM
 * @param	heap	ヒープID
 *
 * @return	コマンドのポインタ
 *
 *	表示座標は、枠を含めない値を指定すること
 */
//--------------------------------------------------------------------------------------------
u8 * PokeWindowPutPP(
		GF_BGL_INI * bgl, u8 frm, u8 px, u8 py, u8 pal, u16 cgx, POKEMON_PARAM * pp, int heap )
{
	POKEWIN_WORK * wk = PokeWin_TcbAdd( bgl, frm, px, py, heap );

	PokeWin_ClactSet( wk, heap );
	PokeWin_LoadRes( wk );
	PokeWin_ClactAdd( wk, px, py );
	PokeWin_PokeGraSetPP( &wk->fcat, pp );
	PokeWinFrameWrite( wk, pal, cgx );

	GF_BGL_LoadScreenReq( bgl, frm );

	return &wk->cmd;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンウィンドウ監視タスク
 *
 * @param	tcb
 * @param	work
 *
 * @return	none
 *
 *	終了する場合は、外部からフラグを操作
 */
//--------------------------------------------------------------------------------------------
static void PokeWin_Main( TCB_PTR tcb, void * work )
{
	POKEWIN_WORK * wk = work;

	switch( wk->cmd ){
	case POKEWIN_CMD_END:
		PokeWinFrameClear( wk );
		CATS_ActorPointerDelete_S( wk->cap );
		FieldCellActDelete_S( &wk->fcat );
		PMDS_taskDel( tcb );
		return;

	case POKEWIN_CMD_ANM:
		wk->cmd = POKEWIN_CMD_MOVE;
		CLACT_AnmChg( wk->cap->act, 1 );
		break;

	case POKEWIN_CMD_MOVE:
		if( CLACT_AnmFrameGet( wk->cap->act ) == 6 ){
			wk->cmd = POKEWIN_CMD_NONE;
		}
	}
	
	CLACT_AnmFrameChg( wk->cap->act, FX32_ONE );
	CLACT_Draw( wk->fcat.cas );
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンウィンドウ TCB追加 & ワーク作成
 *
 * @param	bgl		BGLデータ
 * @param	frm		表示BGフレーム
 * @param	px		表示X座標
 * @param	py		表示Y座標
 * @param	heap	ヒープID
 *
 * @return	ポケモンウィンドウのワーク
 */
//--------------------------------------------------------------------------------------------
static POKEWIN_WORK * PokeWin_TcbAdd( GF_BGL_INI * bgl, u8 frm, u8 px, u8 py, u32 heap )
{
	POKEWIN_WORK * wk = TCB_GetWork( PMDS_taskAdd(PokeWin_Main,sizeof(POKEWIN_WORK),0,heap) );
	wk->cmd = POKEWIN_CMD_NONE;
	wk->bgl = bgl;
	wk->frm = frm;
	wk->px  = px;
	wk->py  = py;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンウィンドウ セルアクターセット
 *
 * @param	wk		ワーク
 * @param	heap	ヒープID
 *
 * @return	ポケモンウィンドウのワーク
 */
//--------------------------------------------------------------------------------------------
static void PokeWin_ClactSet( POKEWIN_WORK * wk, u32 heap )
{
	TCATS_RESOURCE_NUM_LIST	crnl = { 1, 1, 1, 1, 0, 0 };
	FieldCellActSet_S( &wk->fcat, &crnl, 1, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンウィンドウ リソース読み込み
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeWin_LoadRes( POKEWIN_WORK * wk )
{
	// パレット
	FldClact_LoadResPlttArc(
		&wk->fcat, ARC_WINFRAME,
		NARC_winframe_poke_win_nclr, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, POKEWIN_CLA_PAL_ID );
	// セル
	FldClact_LoadResCellArc(
		&wk->fcat, ARC_WINFRAME, NARC_winframe_poke_win_ncer, 0, POKEWIN_CLA_CEL_ID );
	// セルアニメ
	FldClact_LoadResCellAnmArc(
		&wk->fcat, ARC_WINFRAME, NARC_winframe_poke_win_nanr, 0, POKEWIN_CLA_ANM_ID );
	// キャラ
	FldClact_LoadResourceCharArc(
		&wk->fcat, ARC_WINFRAME,
		NARC_winframe_poke_win_ncgr, 0, NNS_G2D_VRAM_TYPE_2DMAIN, POKEWIN_CLA_CHR_ID );
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンウィンドウ セルアクター追加
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeWin_ClactAdd( POKEWIN_WORK * wk, u8 px, u8 py )
{
	TCATS_OBJECT_ADD_PARAM_S	prm = PokeWinAct_S;

	prm.x = ( px + 5 ) * 8;
	prm.y = ( py + 5 ) * 8;
	wk->cap = FieldCellActAdd_S( &wk->fcat, &prm );

	CLACT_Draw( wk->fcat.cas );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモングラフィックセット（番号、性別指定）
 *
 * @param	wk		フィールドセルアクターワーク
 * @param	mons	ポケモン番号
 * @param	sex		ポケモンの性別
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeWin_PokeGraSetEz( FIELD_CLACT * wk, u16 mons, u8 sex )
{
	void * ssm;
	SOFT_SPRITE_ARC	ssa;

	ssm = SoftSpriteInit( wk->heap );
	PokeGraArcDataGet( &ssa, mons, sex, PARA_FRONT, PARA_NORMAL, NULL, NULL );	//最後の引数はFormNoと個性乱数です by soga
	PokeWin_PokeGraSetCore( wk, &ssa );
	SoftSpriteEnd( ssm );
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモングラフィックセット（POKEMON_PARAM指定）
 *
 * @param	wk		フィールドセルアクターワーク
 * @param	pp		POKEMON_PARAM
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeWin_PokeGraSetPP( FIELD_CLACT * wk, POKEMON_PARAM * pp )
{
	void * ssm;
	SOFT_SPRITE_ARC	ssa;

	ssm = SoftSpriteInit( wk->heap );
	PokeGraArcDataGetPP( &ssa, pp, PARA_FRONT );
	PokeWin_PokeGraSetCore( wk, &ssa );
	SoftSpriteEnd( ssm );
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモングラフィックセット コア
 *
 * @param	wk		フィールドセルアクターワーク
 * @param	ssa
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeWin_PokeGraSetCore( FIELD_CLACT * wk, SOFT_SPRITE_ARC * ssa )
{
	u8 * buf;
	u32 vram;
	CLACT_U_RES_OBJ_PTR c_res;
	NNSG2dImageProxy * c_pxy;
	CLACT_U_RES_OBJ_PTR p_res;
	const NNSG2dImagePaletteProxy * p_pxy;

	// キャラ
	buf = sys_AllocMemory( wk->heap, POKEWIN_OBJCGX_SIZ_ALL );
	{
		CHANGES_INTO_DATA_RECT rc = { 0, 0, 10, 10 };
		ChangesInto_OAM_from_PokeTex_RC( ssa->arc_no, ssa->index_chr, wk->heap, &rc, &buf[0] );
	}
	{
		CHANGES_INTO_DATA_RECT rc = { 10, 0, 10, 10 };
		ChangesInto_OAM_from_PokeTex_RC(
			ssa->arc_no, ssa->index_chr, wk->heap, &rc, &buf[POKEWIN_OBJCGX_SIZ] );
	}

	c_res  = CLACT_U_ResManagerGetIDResObjPtr( wk->resMan[0], POKEWIN_CLA_CHR_ID );
	c_pxy  = CLACT_U_CharManagerGetProxy( c_res );
	vram   = NNS_G2dGetImageLocation( c_pxy, NNS_G2D_VRAM_TYPE_2DMAIN );
	DC_FlushRange( buf, POKEWIN_OBJCGX_SIZ_ALL );
	GX_LoadOBJ( buf, vram, POKEWIN_OBJCGX_SIZ_ALL );
	sys_FreeMemoryEz( buf );

	// パレット
	buf    = ChangesInto_BattlePokePalData_Alloc( ssa->arc_no, ssa->index_pal, wk->heap );
	p_res  = CLACT_U_ResManagerGetIDResObjPtr( wk->resMan[1], POKEWIN_CLA_PAL_ID );
	p_pxy  = CLACT_U_PlttManagerGetProxy( p_res, c_pxy );
	vram   = NNS_G2dGetImagePaletteLocation( p_pxy, NNS_G2D_VRAM_TYPE_2DMAIN );
	DC_FlushRange( buf, 32 );
	GX_LoadOBJPltt( buf, vram, 32 );	//32byte 1Palette
	sys_FreeMemoryEz( buf );
}

//--------------------------------------------------------------------------------------------
/**
 * ウィンドウ描画
 *
 * @param	wk		ワーク
 * @param	pal		使用パレット
 * @param	cgx		使用キャラ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeWinFrameWrite( POKEWIN_WORK * wk, u8 pal, u16 cgx )
{
	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx,   wk->px-1,  wk->py-1, 1,  1, pal );
	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx+1, wk->px,    wk->py-1, 10, 1, pal );
	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx+2, wk->px+10, wk->py-1, 1,  1, pal );

	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx+4, wk->px,    wk->py, 10, 10, pal );
	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx+3, wk->px-1,  wk->py, 1,  10, pal );
	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx+5, wk->px+10, wk->py, 1,  10, pal );

	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx+6, wk->px-1,  wk->py+10, 1,  1, pal );
	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx+7, wk->px,    wk->py+10, 10, 1, pal );
	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx+8, wk->px+10, wk->py+10, 1,  1, pal );

	GF_BGL_LoadScreenV_Req( wk->bgl, wk->frm );
}

//--------------------------------------------------------------------------------------------
/**
 * ウィンドウクリア
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeWinFrameClear( POKEWIN_WORK * wk )
{
	GF_BGL_ScrFill( wk->bgl, wk->frm, 0, wk->px-1, wk->py-1, 12, 12, 0 );
	GF_BGL_LoadScreenV_Req( wk->bgl, wk->frm );
}
