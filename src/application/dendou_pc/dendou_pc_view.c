//============================================================================================
/**
 * @file	dendou_pc_view.c
 * @bfief	殿堂入りパソコン画面（描画処理）
 * @author	taya GAME FREAK inc.
 *
 * @date	2006.04.21
 */
//============================================================================================
#include "common.h"
#include "gflib\msg_print.h"
#include "system\clact_util.h"
#include "system\render_oam.h"
#include "system\fontproc.h"
#include "system\arc_util.h"
#include "system\wipe.h"
#include "system\msgdata.h"
#include "system\wordset.h"
#include "system\window.h"
#include "system\gra_tool.h"
#include "system\snd_perap.h"
#include "msgdata\msg.naix"
#include "msgdata\msg_dendou_pc.h"
#include "battle\graphic\batt_obj_def.h"

#include "dendou_pc_common.h"
#include "dendou_pc.naix"

//--------------------------------------------------------------
/**
 *
 */
//--------------------------------------------------------------
enum {
	STRBUF_SIZE = 256,		// こんだけありゃ充分
	POKE_ALPHA_SELECT = 31,	// 選択されているポケモンの透明度
	POKE_ALPHA_NOT_SELECT = 16,		// 選択されていないポケモンの透明度

	COLOR_LETTER = 1,
	COLOR_SHADOW = 2,
	COLOR_GROUND = 15,

	// ポケモンアクター１体分キャラ数
	POKE_ACT_CHARS = 100,
	POKE_ACT_CGX_BYTESIZE = POKE_ACT_CHARS * 0x20,

	// パラメータウィンドウの描画レイアウト
	PARAM_NICKNAME_X = 0,
	PARAM_SRASH_X = 72,
	PARAM_MONSNAME_X = 94,
	PARAM_SEX_X = 174,
	PARAM_LEVEL_X = 194,

	PARAM_WAZANAME_DIFF_X = 96,
};



enum {
	WIN_RECORD,
	WIN_PARAMS,

	WIN_MAX,
};

enum {
	PALNO_WIN,
	PALNO_BASE,
	PALNO_WIN_FRAME,
};





extern u32 SSM_CheckHeapID( SOFT_SPRITE_MANAGER* ssm );




//--------------------------------------------------------------
/**
 *
 */
//--------------------------------------------------------------
struct _DENDOU_PC_VIEW {
	DENDOU_PC_WORK*					mainWork;
	const DENDOU_PC_VIEWPARAM*		vpara;
	int			seq;
	int			command;

	GF_BGL_INI*				bgl;
	GF_BGL_BMPWIN			win[WIN_MAX];

	CLACT_SET_PTR				actSet;
	CLACT_U_EASYRENDER_DATA		renderData;
	CLACT_WORK_PTR				pokeAct[ TEMOTI_POKEMAX ];
	void*						cellLoadPtr;
	void*						animLoadPtr;

	MSGDATA_MANAGER*		mm;
	MSGDATA_MANAGER*		mmPoke;
	MSGDATA_MANAGER*		mmWaza;
	WORDSET*				wordset;
	STRBUF*					loadStrBuf;
	STRBUF*					expandStrBuf;

	POKEMON_PARAM*			pokeParaWork;
	u8						pokeCgxBuf[ POKE_ACT_CGX_BYTESIZE ];
};

//==============================================================
// Prototype
//==============================================================
static void DendouPCView_VBlank( void* wk_adrs );
static BOOL Cmd_Init( DENDOU_PC_VIEW* vwk, int* seq );
static BOOL Cmd_Quit( DENDOU_PC_VIEW* vwk, int* seq );
static BOOL Cmd_ChangePoke( DENDOU_PC_VIEW* vwk, int* seq );
static BOOL Cmd_ChangeRecord( DENDOU_PC_VIEW* vwk, int* seq );
static BOOL Cmd_ChangeParamMode( DENDOU_PC_VIEW* vwk, int* seq );
static void setup_bg_params( DENDOU_PC_VIEW* vwk );
static void cleanup_bg_params( DENDOU_PC_VIEW* vwk );
static u32 setup_bmpwin( DENDOU_PC_VIEW* vwk, u32 charpos );
static void cleanup_bmpwin( DENDOU_PC_VIEW* vwk );
static void update_bmpwin_all( DENDOU_PC_VIEW* vwk );
static void clear_bmpwin_all( DENDOU_PC_VIEW* vwk );
static void update_bmpwin_record( DENDOU_PC_VIEW* vwk );
static void update_bmpwin_params( DENDOU_PC_VIEW* vwk );
static void setup_actors( DENDOU_PC_VIEW* vwk );
static void cleanup_actors( DENDOU_PC_VIEW* vwk );
static void setup_dummy_actors( DENDOU_PC_VIEW* vwk, NNSG2dCellDataBank* cell, NNSG2dAnimBankData* anim );
static void update_poke_actors( DENDOU_PC_VIEW* vwk );
static void vanish_poke_actors( DENDOU_PC_VIEW* vwk );

//--------------------------------------------------------
/**
 *	描画コマンド対応関数テーブル
 */
//--------------------------------------------------------
static BOOL (*CommandFuncTable[])(DENDOU_PC_VIEW*, int*) = {
	Cmd_Init,
	Cmd_Quit,
	Cmd_ChangePoke,
	Cmd_ChangeRecord,
	Cmd_ChangeParamMode,
};



//------------------------------------------------------------------
/**
 * 描画ワーク作成
 *
 * @param   mainWork		
 *
 * @retval  DENDOU_PC_VIEW*			
 */
//------------------------------------------------------------------
DENDOU_PC_VIEW*	DendouPCView_CreateWork( DENDOU_PC_WORK* mainWork, const DENDOU_PC_VIEWPARAM* vpara )
{
	DENDOU_PC_VIEW* vwk = sys_AllocMemory( HEAPID_DENDOU_PC_VIEW, sizeof(DENDOU_PC_VIEW) );
	if( vwk )
	{
		vwk->mainWork = mainWork;
		vwk->vpara = vpara;
		vwk->bgl = GF_BGL_BglIniAlloc( HEAPID_DENDOU_PC_VIEW );

		NNS_G2dInitOamManagerModule();
		REND_OAMInit( 0, 128, 0, 32, 0, 128, 0, 32, HEAPID_DENDOU_PC_VIEW );
		vwk->actSet = CLACT_U_SetEasyInit( 64, &vwk->renderData, HEAPID_DENDOU_PC_VIEW );

		vwk->mm = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_dendou_pc_dat, HEAPID_DENDOU_PC_VIEW );
		vwk->mmPoke = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_monsname_dat, HEAPID_DENDOU_PC_VIEW );
		vwk->mmWaza = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_wazaname_dat, HEAPID_DENDOU_PC_VIEW );
		vwk->wordset = WORDSET_Create( HEAPID_DENDOU_PC_VIEW );
		vwk->loadStrBuf = STRBUF_Create( STRBUF_SIZE, HEAPID_DENDOU_PC_VIEW );
		vwk->expandStrBuf = STRBUF_Create( STRBUF_SIZE, HEAPID_DENDOU_PC_VIEW );
		vwk->pokeParaWork = PokemonParam_AllocWork( HEAPID_DENDOU_PC_VIEW );

		sys_VBlankFuncChange( DendouPCView_VBlank, vwk );

	}
	return vwk;
}
//------------------------------------------------------------------
/**
 * 描画ワーク破棄
 *
 * @param   vwk		
 *
 */
//------------------------------------------------------------------
void DendouPCView_DeleteWork( DENDOU_PC_VIEW* vwk )
{
	if( vwk )
	{
		sys_VBlankFuncChange( NULL, NULL );

		sys_FreeMemoryEz( vwk->pokeParaWork );
		STRBUF_Delete( vwk->expandStrBuf );
		STRBUF_Delete( vwk->loadStrBuf );
		WORDSET_Delete( vwk->wordset );
		MSGMAN_Delete( vwk->mmWaza );
		MSGMAN_Delete( vwk->mmPoke );
		MSGMAN_Delete( vwk->mm );
		CLACT_DestSet( vwk->actSet );
		REND_OAM_Delete();
		sys_FreeMemoryEz( vwk->bgl );
		sys_FreeMemoryEz( vwk );
	}
}

//------------------------------------------------------------------
/**
 * VBlank
 *
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void DendouPCView_VBlank( void* wk_adrs )
{
	DENDOU_PC_VIEW* vwk = wk_adrs;

	CLACT_Draw( vwk->actSet );
	REND_OAMTrans();		// レンダラ共有OAMマネージャVram転送
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );

}



//------------------------------------------------------------------
/**
 * 描画コマンドスタート
 *
 * @param   vwk			
 * @param   command		
 *
 * @retval  BOOL		TRUEなら動き待ちの必要がある
 */
//------------------------------------------------------------------
BOOL DendouPCView_StartCommand( DENDOU_PC_VIEW* vwk, int command )
{
	vwk->command = command;
	vwk->seq = 0;
	return (CommandFuncTable[command]( vwk, &(vwk->seq) ) == FALSE);
}
//------------------------------------------------------------------
/**
 * 描画コマンド終了待ち
 *
 * @param   vwk		
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL DendouPCView_WaitCommand( DENDOU_PC_VIEW* vwk )
{
	return CommandFuncTable[ vwk->command ]( vwk, &(vwk->seq) );
}



//------------------------------------------------------------------
/**
 * 描画コマンド：初期化処理＆フェードイン
 *
 * @param   vwk		
 * @param   seq		
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
static BOOL Cmd_Init( DENDOU_PC_VIEW* vwk, int* seq )
{
	switch( *seq ){
	case 0:
		setup_bg_params( vwk );
		setup_actors( vwk );
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK,
			WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_DENDOU_PC_VIEW );
		(*seq)++;
		break;
	case 1:
		if( WIPE_SYS_EndCheck() )
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * 描画コマンド：フェードアウト＆終了処理
 *
 * @param   vwk		
 * @param   seq		
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
static BOOL Cmd_Quit( DENDOU_PC_VIEW* vwk, int* seq )
{
	switch(*seq){
	case 0:
		Snd_SePlay( SE_DENDOUPC_LOGOUT );
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK,
			WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_DENDOU_PC_VIEW );
		(*seq)++;
		break;
	case 1:
		if( WIPE_SYS_EndCheck() )
		{
			cleanup_actors( vwk );
			cleanup_bg_params( vwk );
			return TRUE;
		}
		break;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * 描画コマンド：選択ポケモン切り替え
 *
 * @param   vwk		
 * @param   seq		
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
static BOOL Cmd_ChangePoke( DENDOU_PC_VIEW* vwk, int* seq )
{
	const DENDOU_PC_VIEWPARAM* vpara;
	int i;

//	Snd_SePlay( SE_DENDOUPC_CHANGE_POKE );

	vpara = vwk->vpara;
	for(i=0; i<vpara->pokeCount; i++)
	{
		if(i == vpara->pokePos)
		{
			CLACT_ObjModeSet( vwk->pokeAct[i], GX_OAM_MODE_NORMAL );
			CLACT_DrawPriorityChg( vwk->pokeAct[i], 0 );
			Snd_PerapVoiceDefaultFlagSet( TRUE );
			Snd_PMVoicePlay( vpara->pokemon[i].monsno );
		}
		else
		{
			CLACT_ObjModeSet( vwk->pokeAct[i], GX_OAM_MODE_XLU );
			CLACT_DrawPriorityChg( vwk->pokeAct[i], i+1 );
		}
	}

	update_bmpwin_params( vwk );

	return TRUE;
}
//------------------------------------------------------------------
/**
 * 描画コマンド：レコード切り替え
 *
 * @param   vwk		
 * @param   seq		
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
static BOOL Cmd_ChangeRecord( DENDOU_PC_VIEW* vwk, int* seq )
{
	switch( *seq ){
	case 0:
//		Snd_SePlay( SE_DENDOUPC_CHANGE_RECORD );
		clear_bmpwin_all( vwk );
		(*seq)++;
		break;
	case 1:
		vanish_poke_actors( vwk );
		(*seq)++;
		break;
	case 2:
		update_poke_actors( vwk );
		(*seq)++;
		break;
	case 3:
		update_bmpwin_all( vwk );
		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * 描画コマンド：パラメータ表示モード変更
 *
 * @param   vwk		
 * @param   seq		
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
static BOOL Cmd_ChangeParamMode( DENDOU_PC_VIEW* vwk, int* seq )
{
	Snd_SePlay( SE_DENDOUPC_CHANGE_PARAMMODE );
	update_bmpwin_params( vwk );
	return TRUE;
}


//======================================================================================
//======================================================================================

static void setup_bg_params( DENDOU_PC_VIEW* vwk )
{
	static const GF_BGL_DISPVRAM SetBankData = {
		GX_VRAM_BG_128_B,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_0_A,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
	};

	static const GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
	};

	static const GF_BGL_BGCNT_HEADER header1 = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 0, 1, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};
	static const GF_BGL_BGCNT_HEADER header2 = {
		0, 0, 0, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x04000,
		GX_BG_EXTPLTT_01, 0, 2, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	u32 charpos;


	GF_Disp_SetBank( &SetBankData );
	GX_SetDispSelect( GX_DISP_SELECT_MAIN_SUB );
	GF_BGL_InitBG( &BGsys_data );

	GF_BGL_BGControlSet( vwk->bgl, GF_BGL_FRAME1_M, &header1, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( vwk->bgl, GF_BGL_FRAME2_M, &header2, GF_BGL_MODE_TEXT );

	ArcUtil_BgCharSet(ARC_DENDOU_PC_GRA, NARC_dendou_pc_base_lz_ncgr, vwk->bgl, GF_BGL_FRAME2_M, 0, 0, TRUE, HEAPID_DENDOU_PC_VIEW );
	ArcUtil_ScrnSet(ARC_DENDOU_PC_GRA, NARC_dendou_pc_base_lz_nscr, vwk->bgl, GF_BGL_FRAME2_M, 0, 0, TRUE, HEAPID_DENDOU_PC_VIEW );
	ArcUtil_PalSet(ARC_DENDOU_PC_GRA, NARC_dendou_pc_base_nclr, PALTYPE_MAIN_BG, 0, 0x40, HEAPID_DENDOU_PC_VIEW );

	GF_BGL_CharFill( vwk->bgl, GF_BGL_FRAME1_M, 0x00, 1, 0 );
	GF_BGL_ScrFill( vwk->bgl, GF_BGL_FRAME1_M, 0x0000, 0, 0, 32, 32, 0 );

	charpos = setup_bmpwin( vwk, 1 );
	update_bmpwin_all( vwk );

	MenuWinGraphicSet( vwk->bgl, GF_BGL_FRAME1_M, charpos, PALNO_WIN_FRAME, 0, HEAPID_DENDOU_PC_VIEW );
	BmpMenuWinWrite( &(vwk->win[WIN_RECORD]), FALSE, charpos, PALNO_WIN_FRAME );
	BmpMenuWinWrite( &(vwk->win[WIN_PARAMS]), FALSE, charpos, PALNO_WIN_FRAME );

	GF_BGL_LoadScreenReq( vwk->bgl, GF_BGL_FRAME1_M );

	G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE, GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG1, 8, 8 );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}

static void cleanup_bg_params( DENDOU_PC_VIEW* vwk )
{
	GF_BGL_BGControlExit( vwk->bgl, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( vwk->bgl, GF_BGL_FRAME2_M );

	cleanup_bmpwin( vwk );
}

static u32 setup_bmpwin( DENDOU_PC_VIEW* vwk, u32 charpos )
{
	enum {
		WINTOP_X = 1,
		WINTOP_Y = 1,
		WINTOP_WIDTH = 30,
		WINTOP_HEIGHT = 2,

		WINBTM_X = 1,
		WINBTM_Y = 19,
		WINBTM_WIDTH = 30,
		WINBTM_HEIGHT = 4,
	};

	GF_BGL_BmpWinAdd( vwk->bgl, &(vwk->win[WIN_RECORD]), GF_BGL_FRAME1_M,
			 WINTOP_X, WINTOP_Y, WINTOP_WIDTH, WINTOP_HEIGHT, PALNO_WIN, charpos );

	charpos += (WINTOP_WIDTH*WINTOP_HEIGHT);

	GF_BGL_BmpWinAdd( vwk->bgl, &(vwk->win[WIN_PARAMS]), GF_BGL_FRAME1_M,
			 WINBTM_X, WINBTM_Y, WINBTM_WIDTH, WINBTM_HEIGHT, PALNO_WIN, charpos );

	charpos += (WINBTM_WIDTH*WINBTM_HEIGHT);

	GF_BGL_BmpWinMakeScrn( &(vwk->win[WIN_RECORD]) );
	GF_BGL_BmpWinMakeScrn( &(vwk->win[WIN_PARAMS]) );

	return charpos;
}
static void cleanup_bmpwin( DENDOU_PC_VIEW* vwk )
{
	int i;

	for(i=0; i<WIN_MAX; i++)
	{
		GF_BGL_BmpWinDel(&(vwk->win[i]));
	}
}

//------------------------------------------------------------------
/**
 * 
 *
 * @param   vwk		
 *
 */
//------------------------------------------------------------------
static void update_bmpwin_all( DENDOU_PC_VIEW* vwk )
{
	update_bmpwin_record( vwk );
	update_bmpwin_params( vwk );
}

static void clear_bmpwin_all( DENDOU_PC_VIEW* vwk )
{
	GF_BGL_BmpWinDataFill( &(vwk->win[WIN_RECORD]), COLOR_GROUND );
	GF_BGL_BmpWinDataFill( &(vwk->win[WIN_PARAMS]), COLOR_GROUND );
	GF_BGL_BmpWinCgxOn( &(vwk->win[WIN_RECORD]) );
	GF_BGL_BmpWinCgxOn( &(vwk->win[WIN_PARAMS]) );
}

static void update_bmpwin_record( DENDOU_PC_VIEW* vwk )
{
	const DENDOU_PC_VIEWPARAM* vpara = vwk->vpara;
	GF_BGL_BMPWIN* win = &(vwk->win[WIN_RECORD]);

	WORDSET_RegisterNumber( vwk->wordset, 0, vpara->times, 4, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_RegisterNumber( vwk->wordset, 1, vpara->date.year+2000, 4, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_RegisterNumber( vwk->wordset, 2, vpara->date.month, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_RegisterNumber( vwk->wordset, 3, vpara->date.day, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	MSGMAN_GetString( vwk->mm, dendoupc_str_01, vwk->loadStrBuf );
	WORDSET_ExpandStr( vwk->wordset, vwk->expandStrBuf, vwk->loadStrBuf );

	GF_BGL_BmpWinDataFill( win, COLOR_GROUND );
	GF_STR_PrintSimple( win, FONT_SYSTEM, vwk->expandStrBuf, 0, 0, MSG_NO_PUT, NULL );

	GF_BGL_BmpWinCgxOn( win );
}

static void update_bmpwin_params( DENDOU_PC_VIEW* vwk )
{
	const DENDOU_PC_VIEWPARAM* vpara = vwk->vpara;
	const DENDOU_POKEMON_DATA* poke = &(vpara->pokemon[vpara->pokePos]);
	GF_BGL_BMPWIN* win = &(vwk->win[WIN_PARAMS]);

	GF_BGL_BmpWinDataFill( win, COLOR_GROUND );

	switch( vpara->paramMode ){
	case PARAM_NORMAL:
		GF_STR_PrintSimple( win, FONT_SYSTEM, poke->nickname, PARAM_NICKNAME_X, 0, MSG_NO_PUT, NULL );
		MSGMAN_GetString( vwk->mm, dendoupc_str_sura, vwk->loadStrBuf );
		GF_STR_PrintSimple( win, FONT_SYSTEM, vwk->loadStrBuf, PARAM_SRASH_X, 0, MSG_NO_PUT, NULL );
		MSGMAN_GetString( vwk->mmPoke, poke->monsno, vwk->loadStrBuf );
		GF_STR_PrintSimple( win, FONT_SYSTEM, vwk->loadStrBuf, PARAM_MONSNAME_X, 0, MSG_NO_PUT, NULL );

		switch( PokeSexGetMonsNo(poke->monsno, poke->personalRandom) ){
		case PARA_MALE:
			MSGMAN_GetString( vwk->mm, dendoupc_str_osu, vwk->loadStrBuf );
			break;
		case PARA_FEMALE:
			MSGMAN_GetString( vwk->mm, dendoupc_str_mesu, vwk->loadStrBuf );
			break;
		default:
			STRBUF_Clear(vwk->loadStrBuf);
			break;
		}
		GF_STR_PrintSimple( win, FONT_SYSTEM, vwk->loadStrBuf, PARAM_SEX_X, 0, MSG_NO_PUT, NULL );

		MSGMAN_GetString( vwk->mm, dendoupc_str_02, vwk->loadStrBuf );
		WORDSET_RegisterNumber( vwk->wordset, 0, poke->level, 4, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr( vwk->wordset, vwk->expandStrBuf, vwk->loadStrBuf );
		GF_STR_PrintSimple( win, FONT_SYSTEM, vwk->expandStrBuf, PARAM_LEVEL_X, 0, MSG_NO_PUT, NULL );

		MSGMAN_GetString( vwk->mm, dendoupc_str_03, vwk->loadStrBuf );
		GF_STR_PrintSimple( win, FONT_SYSTEM, vwk->loadStrBuf, 0, 16, MSG_NO_PUT, NULL );
		GF_STR_PrintSimple( win, FONT_SYSTEM, poke->oyaname,
				 FontProc_GetPrintStrWidth(FONT_SYSTEM,vwk->loadStrBuf,0), 16, MSG_NO_PUT, NULL );
		break;

	case PARAM_WAZA:
		{
			int i;

			for(i=0; i<4; i++)
			{
				if( poke->waza[i] )
				{
					MSGMAN_GetString( vwk->mmWaza, poke->waza[i], vwk->loadStrBuf );
					GF_STR_PrintSimple( win, FONT_SYSTEM, vwk->loadStrBuf,
							 (i&1)*PARAM_WAZANAME_DIFF_X, (i/2)*16, MSG_NO_PUT, NULL );
				}
				else
				{
					break;
				}
			}
		}
		break;
	}


	GF_BGL_BmpWinCgxOn( win );

}


//======================================================================================
//======================================================================================

static void setup_actors( DENDOU_PC_VIEW* vwk )
{
	NNSG2dCellDataBank* cell;
	NNSG2dAnimBankData* anim;
	int i;

	vwk->cellLoadPtr = ArcUtil_CellBankDataGet(ARC_BATT_OBJ, POKE_OAM_NCER, FALSE, &cell, HEAPID_DENDOU_PC_VIEW );
	vwk->animLoadPtr = ArcUtil_AnimBankDataGet(ARC_BATT_OBJ, POKE_OAM_NANR, FALSE, &anim, HEAPID_DENDOU_PC_VIEW );

	MI_CpuClearFast( vwk->pokeCgxBuf, sizeof(vwk->pokeCgxBuf) );

	setup_dummy_actors( vwk, cell, anim );

	update_poke_actors( vwk );
}

static void cleanup_actors( DENDOU_PC_VIEW* vwk )
{
	int i;

	for(i=0; i<TEMOTI_POKEMAX; i++)
	{
		if( vwk->pokeAct[i] )
		{
			CLACT_Delete( vwk->pokeAct[i] );
		}
	}
	sys_FreeMemoryEz( vwk->cellLoadPtr );
	sys_FreeMemoryEz( vwk->animLoadPtr );
}


static void setup_dummy_actors( DENDOU_PC_VIEW* vwk, NNSG2dCellDataBank* cell, NNSG2dAnimBankData* anim )
{
	static const struct {
		int  x;
		int  y;
	}poke_pos[] = {
		{ 120,  56 },
		{  40,  56 },
		{ 200,  56 },
		{ 136, 112 },
		{ 216, 112 },
		{  56, 112 },
	};

	CLACT_HEADER			header;
	CLACT_ADD_SIMPLE		add;
	NNSG2dImageProxy		imgProxy;
	NNSG2dImagePaletteProxy	palProxy;
	NNSG2dCharacterData*	charData;
	NNSG2dPaletteData*		palData;
	void*	cgxLoadPtr;
	void*	palLoadPtr;
	int i;

	header.pCharData = NULL;
	header.pMCBank = NULL;
	header.pMCABank = NULL;
	header.flag = FALSE;
	header.pCellBank = cell;
	header.pAnimBank = anim;
	header.priority = 0;
	header.pImageProxy = &imgProxy;
	header.pPaletteProxy = &palProxy;

	add.ClActSet = vwk->actSet;
	add.ClActHeader = &header;
	add.mat.z = 0;
	add.DrawArea = NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap = HEAPID_DENDOU_PC_VIEW;

	cgxLoadPtr = ArcUtil_CharDataGet( ARC_BATT_OBJ, POKE_OAM_NCGR, FALSE, &charData, HEAPID_DENDOU_PC_VIEW );
	palLoadPtr = ArcUtil_PalDataGet( ARC_BATT_OBJ, POKE_OAM_NCLR, &palData, HEAPID_DENDOU_PC_VIEW );

	for(i=0; i<TEMOTI_POKEMAX; i++)
	{
		NNS_G2dInitImageProxy(&imgProxy);
		NNS_G2dInitImagePaletteProxy(&palProxy);

		NNS_G2dLoadImage1DMapping( charData, i*POKE_ACT_CGX_BYTESIZE, NNS_G2D_VRAM_TYPE_2DMAIN, &imgProxy );
		NNS_G2dLoadPalette( palData, i*0x20, NNS_G2D_VRAM_TYPE_2DMAIN, &palProxy );

		add.mat.x = poke_pos[i].x << FX32_SHIFT;
		add.mat.y = poke_pos[i].y << FX32_SHIFT;
		add.pri = i+1;

		vwk->pokeAct[i] = CLACT_AddSimple( &add );
		CLACT_SetDrawFlag( vwk->pokeAct[i], FALSE );

	}

	sys_FreeMemoryEz( palLoadPtr );
	sys_FreeMemoryEz( cgxLoadPtr );

}

// SoftSprite_MakeStrike

static void update_poke_actors( DENDOU_PC_VIEW* vwk )
{
	static const CHANGES_INTO_DATA_RECT rect = {
		POKE_TEX_X,
		POKE_TEX_Y,
		POKE_TEX_W,
		POKE_TEX_H,
	};

	SOFT_SPRITE_ARC  arc;
	const DENDOU_PC_VIEWPARAM* vpara;
	int i;

	vpara = vwk->vpara;
	for(i=0; i<vpara->pokeCount; i++)
	{
		PokeParaSet(vwk->pokeParaWork, vpara->pokemon[i].monsno, vpara->pokemon[i].level, POW_RND,
						RND_SET, vpara->pokemon[i].personalRandom, ID_SET, vpara->pokemon[i].idNumber );

		PokeParaPut( vwk->pokeParaWork, ID_PARA_form_no, (void*)(&(vpara->pokemon[i].formNumber)) );

		PokeGraArcDataGetPP( &arc, vwk->pokeParaWork, PARA_FRONT );

		Ex_ChangesInto_OAM_from_PokeTex_RC( arc.arc_no, arc.index_chr, HEAPID_DENDOU_PC_VIEW,
			&rect, vwk->pokeCgxBuf,  vpara->pokemon[i].personalRandom, FALSE, PARA_FRONT, vpara->pokemon[i].monsno );

		DC_FlushRange( vwk->pokeCgxBuf, sizeof(vwk->pokeCgxBuf) );

		GX_LoadOBJ( vwk->pokeCgxBuf, POKE_ACT_CGX_BYTESIZE*i, POKE_ACT_CGX_BYTESIZE );

		ArcUtil_PalSet( arc.arc_no, arc.index_pal, PALTYPE_MAIN_OBJ, i*0x20, 0x20, HEAPID_DENDOU_PC_VIEW );

		if(i == vpara->pokePos)
		{
			Snd_PerapVoiceDefaultFlagSet( TRUE );
			Snd_PMVoicePlay( vpara->pokemon[i].monsno );
			CLACT_ObjModeSet( vwk->pokeAct[i], GX_OAM_MODE_NORMAL );
		}
		else
		{
			CLACT_ObjModeSet( vwk->pokeAct[i], GX_OAM_MODE_XLU );
		}
		CLACT_SetDrawFlag( vwk->pokeAct[i], TRUE );
	}

	for( ; i<TEMOTI_POKEMAX; i++)
	{
		CLACT_SetDrawFlag( vwk->pokeAct[i], FALSE );
	}
}

static void vanish_poke_actors( DENDOU_PC_VIEW* vwk )
{
	int i;

	for(i=0; i<TEMOTI_POKEMAX; i++)
	{
		CLACT_SetDrawFlag( vwk->pokeAct[i], FALSE );
	}
}
