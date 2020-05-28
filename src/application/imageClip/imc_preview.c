//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_preview.c
 *	@brief		preview画面
 *	@author		tomoya takahashi
 *	@data		2006.06.05
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


#include "system.h"
#include "assert.h"
#include <string.h>

#include "include/system/wipe.h"
#include "include/gflib/display.h"
#include "include/gflib/gf_gx.h"
#include "include/application/imageClip/imc_playsys.h"
#include "include/application/imageClip/imc_drawsys.h"
#include "include/application/imageClip/imc_drawdata_define.h"
#include "include/system/arc_util.h"
#include "include/system/fontproc.h"
#include "include/system/wordset.h"

#include "src/contest/con_tool.h"

// sub画面グラフィック
#include "src/field/poketch/poketch_arc.h"


#define __IMC_PREVIEW_H_GLOBAL
#include "include/application/imageClip/imc_preview.h"

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
#define IMC_PREV_MAIN_FRAME_PL	( 3 )
#define IMC_PREV_SUB_BG_PL	( 0 )

#define IMC_PREV_MAIN_FRAME_OAM_CONT_ID	( 1000 )
#define IMC_PREV_MAIN_FRAME_OAM_PL_NUM	( 6 )
#define IMC_PREV_MAIN_FRAME_OAM_X		( 0 )
#define IMC_PREV_MAIN_FRAME_OAMTV_X		( 48 )
#define IMC_PREV_MAIN_FRAME_OAM_Y		( 144 )
#define IMC_PREV_MAIN_FRAME_OAM_PRI		( 100 )
enum{
	IMC_PREV_OAM_CON_STYLE,
	IMC_PREV_OAM_CON_BEAUTIFUL,
	IMC_PREV_OAM_CON_CUTE,
	IMC_PREV_OAM_CON_CLEVER,
	IMC_PREV_OAM_CON_STRONG,
	IMC_PREV_OAM_TV,
};

// モジメンビットマップ設定
#define IMC_PREV_FONTBMP_X	( 0 )
#define IMC_PREV_FONTBMP_Y	( 18 )
#define IMC_PREV_FONTBMP_SX	( 32 )
#define IMC_PREV_FONTBMP_SY ( 6 )
#define IMC_PREV_FONTBMP_PL	( 5 )
#define IMC_PREV_FONTBMP_COF ( 1 )
#define IMC_PREV_FONTBMP_COLOR		( GF_PRINTCOLOR_MAKE( 1,2,0 ) )

// テレビ文字表示
#define IMC_PREV_FONTBMP_TV_TR_CX	( 128 )	// トレーナー名中心座標
#define IMC_PREV_FONTBMP_TV_TR_Y	( 7 )
#define IMC_PREV_FONTBMP_TV_POKE_X	( 128 )
#define IMC_PREV_FONTBMP_TV_POKE_Y	( 27 )

#define IMC_PREV_FONTBMP_CON_CON_CX	( 128 )	// トレーナー名中心座標
#define IMC_PREV_FONTBMP_CON_CON_Y	( 7 )
#define IMC_PREV_FONTBMP_CON_TR_CX	( 128 )
#define IMC_PREV_FONTBMP_CON_TR_Y	( 27 )
 
//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	イメージクリップデータ
//=====================================
typedef struct {
	// イメージクリップセーブ領域
	const IMC_TELEVISION_SAVEDATA* p_imc_tv_data;
	const IMC_CONTEST_SAVEDATA* p_imc_con_data;
	u32 data_idx;
	u32	prev_type;	
	IMC_PLAYERSYS_PTR p_player;
	IMC_DRAW_DATA	draw_data;

	CLACT_WORK_PTR window;

	GF_BGL_BMPWIN* p_fontbmp;
} IMC_PREV_WORK;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void IMC_Prev_Vblank( void* p_work );
static void IMC_PrevMainFrameSet( IMC_PREV_WORK* p_ip );
static void IMC_PrevSubBackSet( IMC_PREV_WORK* p_ip );
static void IMC_PrevOamWndSet( IMC_PREV_WORK* p_ip );
static void IMC_PrevOamWndDel( IMC_PREV_WORK* p_ip );
static void IMC_PrevBmpInit( IMC_PREV_WORK* p_ip );
static void IMC_PrevBmpDel( IMC_PREV_WORK* p_ip );
static void IMC_PrevTypeDrawSet( IMC_PREV_WORK* p_ip );
static void IMC_PrevTypeTvDrawSet( IMC_PREV_WORK* p_ip );
static void IMC_PrevTypeConDrawSet( IMC_PREV_WORK* p_ip );

// チェック用プロック
PROC_RESULT IMC_Prev_ProcInit( PROC* proc, int* seq )
{
	IMC_PREV_WORK* p_ip;
	IMC_PROC_PREV_WORK* p_proc_w;
	
	// ヒープ作成
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_IMAGECLIP_DATA, 0x20000 );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_IMAGECLIP_DRAW, 0x40000 );

	// イメージクリップワーク作成
	p_ip = PROC_AllocWork( proc, sizeof( IMC_PREV_WORK ), HEAPID_IMAGECLIP_DATA );
	memset( p_ip, 0, sizeof( IMC_PREV_WORK ) );

	// VブランクHブランク関数設定
	sys_VBlankFuncChange( IMC_Prev_Vblank, p_ip );	// VBlankセット
	sys_HBlankIntrStop();	//HBlank割り込み停止

	// 外部からのデータを取得
	p_proc_w = PROC_GetParentWork( proc );

	if( p_proc_w->prev_type == IMC_PREV_TV ){
		p_ip->p_imc_tv_data = ImcSaveData_GetTelevisionSaveData( p_proc_w->p_imc_data, p_proc_w->data_idx );
	}else{
		p_ip->p_imc_con_data = ImcSaveData_GetContestSaveData( p_proc_w->p_imc_data, p_proc_w->data_idx );
	}
	p_ip->data_idx		= p_proc_w->data_idx;
	p_ip->prev_type		= p_proc_w->prev_type;

	// 描画関係
	IMC_DRAW_SetUp();

	// 描画先を変更
	sys.disp3DSW = DISP_3D_TO_MAIN;
	GF_Disp_DispSelect();
	
	// 描画データ設定
	IMC_DRAW_InitSysPrev( &p_ip->draw_data, HEAPID_IMAGECLIP_DRAW );

	{
		IMC_PLAYERSYS_INIT init;
		init.p_bg_ini = p_ip->draw_data.BG_Ini;
		init.x		  = 72;
		init.y		  = 16;
		init.heap_id  = HEAPID_IMAGECLIP_DRAW;

		if( p_ip->prev_type == IMC_PREV_TV ){
			p_ip->p_player = IMC_TelevisionPlayerInit( &init, p_ip->p_imc_tv_data );
		}else{
			p_ip->p_player = IMC_ContestPlayerInit( &init, p_ip->p_imc_con_data );
		}
	}

	// メイン画面とサブ画面にフレームを背景設定
	IMC_PrevMainFrameSet( p_ip );
	IMC_PrevSubBackSet( p_ip );
	IMC_PrevOamWndSet( p_ip );
	IMC_PrevBmpInit( p_ip );

	//　それぞれの文字やウィンドウ表示設定
	IMC_PrevTypeDrawSet( p_ip );
	

	return PROC_RES_FINISH;
}

PROC_RESULT IMC_Prev_ProcMain( PROC* proc, int* seq )
{
	IMC_PREV_WORK* p_ip = PROC_GetWork( proc );
	
	{
		//３Ｄ描画開始
		GF_G3X_Reset();

		NNS_G2dSetupSoftwareSpriteCamera();

		IMC_PlayerMain( p_ip->p_player );

		/* ジオメトリ＆レンダリングエンジン関連メモリのスワップ */
		GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
	}
	IMC_DRAW_DrawSysPrev( &p_ip->draw_data );



	switch( *seq ){
	case 0:
		(*seq) ++;
		break;

	case 1:
		WIPE_SYS_Start( 
				WIPE_PATTERN_WMS,
				WIPE_TYPE_SHUTTERIN_UP,
				WIPE_TYPE_FADEIN,
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
		if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) ){
			(*seq)++;
		}
		break;

	case 4:
		WIPE_SYS_Start( 
				WIPE_PATTERN_WMS,
				WIPE_TYPE_SHUTTEROUT_DOWN,
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

PROC_RESULT IMC_Prev_ProcEnd( PROC* proc, int* seq )
{
	IMC_PREV_WORK* p_ip = PROC_GetWork( proc );

	IMC_PlayerEnd( p_ip->p_player );

	// OAM破棄
	IMC_PrevOamWndDel( p_ip );
	IMC_PrevBmpDel( p_ip );

	// 描画システム破棄
	IMC_DRAW_DeleteSysPrev( &p_ip->draw_data );


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





//-----------------------------------------------------------------------------
/**
 *			プライベート
 */
//-----------------------------------------------------------------------------
// VBlank
static void IMC_Prev_Vblank( void* p_work )
{
	IMC_PREV_WORK* p_ip = p_work;

	IMC_PlayerVblank( p_ip->p_player );
	IMC_DRAW_VBlankPrev( &p_ip->draw_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	メイン画面フレーム設定
 *
 *	@param	p_ip	ワーク
 */
//-----------------------------------------------------------------------------
static void IMC_PrevMainFrameSet( IMC_PREV_WORK* p_ip )
{
	void* p_scrn_buff;
	NNSG2dScreenData* p_scrn;
	int scrn_idx;
	int pltt_no;

	// フレーム設定
	ArcUtil_PalSet( ARC_IMAGECLIP_GRA, 
			NARC_imageclip_imgclip_frame_contv_NCLR, 
			PALTYPE_MAIN_BG, IMC_PREV_MAIN_FRAME_PL * 32, 64,
			HEAPID_IMAGECLIP_DRAW );

	ArcUtil_BgCharSet( ARC_IMAGECLIP_GRA, 
			NARC_imageclip_imgclip_frame_contv_NCGR,
			p_ip->draw_data.BG_Ini, GF_BGL_FRAME1_M, 0, 0,
			FALSE, HEAPID_IMAGECLIP_DRAW);

	if( p_ip->prev_type == IMC_PREV_TV ){
		scrn_idx = NARC_imageclip_imgclip_frame_contv01_NSCR;
		pltt_no = IMC_PREV_MAIN_FRAME_PL + 1;
	}else{
		scrn_idx = NARC_imageclip_imgclip_frame_contv00_NSCR;
		pltt_no = IMC_PREV_MAIN_FRAME_PL;
	}
	p_scrn_buff = ArcUtil_ScrnDataGet( ARC_IMAGECLIP_GRA, 
			scrn_idx, FALSE,
			&p_scrn, HEAPID_IMAGECLIP_DRAW );

	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_ip->draw_data.BG_Ini, GF_BGL_FRAME1_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	// パレットをあわせる
	GF_BGL_ScrPalChange( p_ip->draw_data.BG_Ini, GF_BGL_FRAME1_M,
			0, 0,
			p_scrn->screenWidth / 8,
			p_scrn->screenHeight / 8,
			pltt_no );


	sys_FreeMemoryEz( p_scrn_buff );

	// スクリーン転送
	GF_BGL_LoadScreenV_Req( p_ip->draw_data.BG_Ini, GF_BGL_FRAME1_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	sub画面　背景設定
 *
 *	@param	p_ip 
 */
//-----------------------------------------------------------------------------
static void IMC_PrevSubBackSet( IMC_PREV_WORK* p_ip )
{
	// 
	ArcUtil_PalSet( ARC_POKETCH_IMG, NARC_poketch_before_nclr, 
			PALTYPE_SUB_BG, IMC_PREV_SUB_BG_PL, 32, HEAPID_IMAGECLIP_DRAW );
	
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_before_lz_nscr,
			p_ip->draw_data.BG_Ini, GF_BGL_FRAME0_S, 0, 0, 
			TRUE, HEAPID_IMAGECLIP_DRAW );

	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_before_lz_ncgr,
			p_ip->draw_data.BG_Ini, GF_BGL_FRAME0_S, 0, 0,
			TRUE, HEAPID_IMAGECLIP_DRAW);
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMフレーム設定
 *
 *	@param	p_ip	ワーク
 */
//-----------------------------------------------------------------------------
static void IMC_PrevOamWndSet( IMC_PREV_WORK* p_ip )
{
	// フレーム読み込み
	IMC_DRAW_CLACT_LoadCharData( &p_ip->draw_data, ARC_IMAGECLIP_GRA,
			NARC_imageclip_imgclip_win_contv_NCGR, FALSE, 
			NNS_G2D_VRAM_TYPE_2DMAIN, IMC_PREV_MAIN_FRAME_OAM_CONT_ID );

	IMC_DRAW_CLACT_LoadPlttData( &p_ip->draw_data, ARC_IMAGECLIP_GRA,
			NARC_imageclip_imgclip_win_contv_NCLR, FALSE,
			NNS_G2D_VRAM_TYPE_2DMAIN, IMC_PREV_MAIN_FRAME_OAM_PL_NUM,
			IMC_PREV_MAIN_FRAME_OAM_CONT_ID );

	IMC_DRAW_CLACT_LoadCellData( &p_ip->draw_data, ARC_IMAGECLIP_GRA,
			NARC_imageclip_imgclip_win_contv_NCER, FALSE,
			IMC_PREV_MAIN_FRAME_OAM_CONT_ID );

	IMC_DRAW_CLACT_LoadCellAnmData( &p_ip->draw_data, ARC_IMAGECLIP_GRA,
			NARC_imageclip_imgclip_win_contv_NANR, FALSE,
			IMC_PREV_MAIN_FRAME_OAM_CONT_ID );

	p_ip->window = IMC_DRAW_AddClact( &p_ip->draw_data, 
			IMC_PREV_MAIN_FRAME_OAM_CONT_ID, 
			IMC_PREV_MAIN_FRAME_OAM_X,
			IMC_PREV_MAIN_FRAME_OAM_Y,
			IMC_PREV_MAIN_FRAME_OAM_PRI,
			NNS_G2D_VRAM_TYPE_2DMAIN );

	CLACT_BGPriorityChg( p_ip->window, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMフレーム破棄
 *
 *	@param	p_ip	ワーク
 */
//-----------------------------------------------------------------------------
static void IMC_PrevOamWndDel( IMC_PREV_WORK* p_ip )
{
	IMC_DRAW_CLACT_DeleteCharRes( &p_ip->draw_data, IMC_PREV_MAIN_FRAME_OAM_CONT_ID );
	IMC_DRAW_CLACT_DeletePlttRes( &p_ip->draw_data, IMC_PREV_MAIN_FRAME_OAM_CONT_ID );
	IMC_DRAW_CLACT_DeleteCellRes( &p_ip->draw_data, IMC_PREV_MAIN_FRAME_OAM_CONT_ID );
	IMC_DRAW_CLACT_DeleteCellAnmRes( &p_ip->draw_data, IMC_PREV_MAIN_FRAME_OAM_CONT_ID );

	CLACT_Delete( p_ip->window );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップウィンドウ初期化
 *
 *	@param	p_ip	ワーク
 */
//-----------------------------------------------------------------------------
static void IMC_PrevBmpInit( IMC_PREV_WORK* p_ip )
{
	// モジメンビットマップ作成
	p_ip->p_fontbmp = GF_BGL_BmpWinAllocGet( HEAPID_IMAGECLIP_DRAW, 1 );
	GF_BGL_BmpWinAdd(
			p_ip->draw_data.BG_Ini,
			p_ip->p_fontbmp,
			GF_BGL_FRAME3_M,
			IMC_PREV_FONTBMP_X, IMC_PREV_FONTBMP_Y,
			IMC_PREV_FONTBMP_SX, IMC_PREV_FONTBMP_SY,
			IMC_PREV_FONTBMP_PL, IMC_PREV_FONTBMP_COF );

	// 文字パレット読み込み
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, IMC_PREV_FONTBMP_PL*32, HEAPID_IMAGECLIP_DRAW );

	GF_BGL_PrioritySet( GF_BGL_FRAME3_M, 0 );
	GF_BGL_PrioritySet( GF_BGL_FRAME0_M, 2 );
	GF_BGL_PrioritySet( GF_BGL_FRAME1_M, 1 );


	// スクロール初期化
	GF_BGL_ScrollSet( p_ip->draw_data.BG_Ini, GF_BGL_FRAME3_M, 
			GF_BGL_SCROLL_Y_SET, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップウィンドウ破棄
 *
 *	@param	p_ip	ワーク
 */
//-----------------------------------------------------------------------------
static void IMC_PrevBmpDel( IMC_PREV_WORK* p_ip )
{
	GF_BGL_BmpWinOff( p_ip->p_fontbmp );
	GF_BGL_BmpWinDel( p_ip->p_fontbmp );
	GF_BGL_BmpWinFree( p_ip->p_fontbmp, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画タイプ　設定
 *
 *	@param	p_ip	ワーク
 */
//-----------------------------------------------------------------------------
static void IMC_PrevTypeDrawSet( IMC_PREV_WORK* p_ip )
{

	// ビットマップ
	GF_BGL_BmpWinDataFill( p_ip->p_fontbmp, 0 );
	
	// それぞれのタイプから　
	// 文字表示　枠設定を行う
	if( p_ip->prev_type == IMC_PREV_TV ){
		
		IMC_PrevTypeTvDrawSet( p_ip );
	}else{

		IMC_PrevTypeConDrawSet( p_ip );
	}

	GF_BGL_BmpWinOn( p_ip->p_fontbmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	テレビ描画設定
 *
 *	@param	p_ip	ワーク
 */
//-----------------------------------------------------------------------------
static void IMC_PrevTypeTvDrawSet( IMC_PREV_WORK* p_ip )
{
	VecFx32 matrix;
	int x, y;
	int width;
	PMS_WORD word;
	WORDSET* word_set;
	STRBUF* p_expand;
	STRBUF* p_str;
	MSGDATA_MANAGER* msg_data;


	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, 
			NARC_msg_imageclip_dat, HEAPID_IMAGECLIP_DATA );
	GF_ASSERT( msg_data );

	word_set = WORDSET_Create( HEAPID_IMAGECLIP_DATA );
	

	// 枠設定
	CLACT_AnmChg( p_ip->window, IMC_PREV_OAM_TV );
	matrix.x = IMC_PREV_MAIN_FRAME_OAMTV_X << FX32_SHIFT;
	matrix.y = IMC_PREV_MAIN_FRAME_OAM_Y << FX32_SHIFT;
	matrix.z = 0;
	CLACT_SetMatrix( p_ip->window, &matrix );

	// トレーナー名作品名描画
	p_str = STRBUF_Create( IMC_SAVEDATA_STRBUF_NUM, HEAPID_IMAGECLIP_DATA );
	ImcSaveData_GetTelevisionPokeOyaName( p_ip->p_imc_tv_data, p_str );

	width = FontProc_GetPrintStrWidth( FONT_SYSTEM, p_str, 0 );
	x = IMC_PREV_FONTBMP_TV_TR_CX - (width / 2);
	y = IMC_PREV_FONTBMP_TV_TR_Y;
	GF_STR_PrintColor( p_ip->p_fontbmp, FONT_SYSTEM, p_str,
			x, y, 0,
			IMC_PREV_FONTBMP_COLOR, NULL );

	// 文字列破棄
	STRBUF_Delete( p_str );

	// 作品名
	word = ImcSaveData_GetTelevisionTitlePmsWord( p_ip->p_imc_tv_data );

	// ワードセット設定
	WORDSET_RegisterPMSWord( word_set, 0, word );
	p_str = STRBUF_Create( 200, HEAPID_IMAGECLIP_DATA );
	p_expand = MSGMAN_AllocString( msg_data, contesttitle_03 );
	WORDSET_ExpandStr( word_set, p_str, p_expand );
	
	width = FontProc_GetPrintStrWidth( FONT_SYSTEM, p_str, 0 );
	x = IMC_PREV_FONTBMP_TV_POKE_X - (width / 2);
	y = IMC_PREV_FONTBMP_TV_POKE_Y;
	GF_STR_PrintColor( p_ip->p_fontbmp, FONT_SYSTEM, p_str,
			x, y, 0,
			IMC_PREV_FONTBMP_COLOR, NULL );

	// 文字列破棄
	STRBUF_Delete( p_str );
	STRBUF_Delete( p_expand );
	MSGMAN_Delete( msg_data );
	WORDSET_Delete( word_set );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト描画設定
 *
 *	@param	p_ip	ワーク
 */
//-----------------------------------------------------------------------------
static void IMC_PrevTypeConDrawSet( IMC_PREV_WORK* p_ip )
{
	int contest_rank;
	WORDSET * word_set;
	STRBUF* p_str;
	STRBUF* p_expand;
	int sex;
	POKEMON_PARAM* p_pp;
	POKEMON_PASO_PARAM* p_ppp;
	MSGDATA_MANAGER* msg_data;
	int x, y;
	int width;

	// 枠設定
	CLACT_AnmChg( p_ip->window, p_ip->data_idx );

	// コンテスト名　ランク
	// トレーナー名　ポケモン名描画
	contest_rank = ImcSaveData_GetContestRank( p_ip->p_imc_con_data );

	// ワードセット作成
	word_set = WORDSET_Create( HEAPID_IMAGECLIP_DATA );
	p_str = STRBUF_Create( 200, HEAPID_IMAGECLIP_DATA );

	// コンテスト名
	WORDSET_RegisterContestType( word_set, 0, ConTool_IMCGetTypeMsgID( p_ip->data_idx ) );
	
	// コンテストランク
	WORDSET_RegisterContestRank( word_set, 1, ConTool_IMCGetRankMsgID( contest_rank ) );
	
	// トレーナー名
	sex = ImcSaveData_GetContestPokeOyaSex( p_ip->p_imc_con_data );
	ImcSaveData_GetContestPokeOyaName( p_ip->p_imc_con_data, p_str );
	WORDSET_RegisterWord( word_set, 3, p_str, sex, TRUE, PM_LANG );

	// ポケモンニックネーム
	p_pp = PokemonParam_AllocWork( HEAPID_IMAGECLIP_DATA );
	ImcSaveData_GetContestPokePara( p_ip->p_imc_con_data, p_pp );
	p_ppp = PPPPointerGet( p_pp );
	WORDSET_RegisterPokeNickName( word_set, 4, p_ppp );
	sys_FreeMemoryEz( p_pp );

	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, 
			NARC_msg_imageclip_dat, HEAPID_IMAGECLIP_DATA );
	GF_ASSERT( msg_data );

	//コンテスト情報
	p_expand = MSGMAN_AllocString( msg_data, contesttitle_01 );
	WORDSET_ExpandStr( word_set, p_str, p_expand );
	STRBUF_Delete( p_expand );
	width = FontProc_GetPrintStrWidth( FONT_SYSTEM, p_str, 0 );
	x = IMC_PREV_FONTBMP_CON_CON_CX - (width / 2);
	y = IMC_PREV_FONTBMP_CON_CON_Y;
	GF_STR_PrintColor( p_ip->p_fontbmp, FONT_SYSTEM, p_str,
			x, y, 0,
			IMC_PREV_FONTBMP_COLOR, NULL );

	//トレーナー情報
	p_expand = MSGMAN_AllocString( msg_data, contesttitle_02 );
	WORDSET_ExpandStr( word_set, p_str, p_expand );
	STRBUF_Delete( p_expand );
	width = FontProc_GetPrintStrWidth( FONT_SYSTEM, p_str, 0 );
	x = IMC_PREV_FONTBMP_CON_TR_CX - (width / 2);
	y = IMC_PREV_FONTBMP_CON_TR_Y;
	GF_STR_PrintColor( p_ip->p_fontbmp, FONT_SYSTEM, p_str,
			x, y, 0,
			IMC_PREV_FONTBMP_COLOR, NULL );


	STRBUF_Delete(p_str);
	MSGMAN_Delete( msg_data );
	WORDSET_Delete( word_set );
}
