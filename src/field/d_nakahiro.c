#ifdef PM_DEBUG
//============================================================================================
/**
 *	デバッグメニュー「なかむら」の処理
 */
//============================================================================================
#include "common.h"
#include "system/gamedata.h"
#include "system/lib_pack.h"
#include "system/bmp_list.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/snd_tool.h"
#include "system/palanm.h"
#include "system/window.h"
#include "system/wordset.h"
#include "system/numfont.h"
#include "system/bmp_cursor.h"
#include "system/msg_ds_icon.h"
#include "system/wipe.h"
#include "system/debug_flag.h"
#include "system/clact_tool.h"
#include "itemtool/itemsym.h"
#include "itemtool/item.h"
#include "itemtool/myitem.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "fld_bmp.h"
#include "battle/battle_common.h"
#include "battle/wazano_def.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "poketool/waza_tool.h"
#include "poketool/monsno.h"
#include "poketool/boxdata.h"
#include "poketool/poke_number.h"
#include "poketool/pokeicon.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_debug_nakahiro.h"
#include "msgdata/msg_icontest.h"
#include "fld_bmp.h"
#include "vm.h"
#include "script.h"
#include "scrcmd.h"
#include "sxytype.h"
#include "sysflag.h"
#include "ev_mapchange.h"
#include "fd_shop.h"
#include "talk_msg.h"
#include "field_clact.h"
#include "savedata/sp_ribbon.h"
#include "application/waza_oshie.h"
#include "../../src/application/p_status/ribbon.h"


//============================================================================================
//	メイン
//============================================================================================
#define	TCB_WK_SIZE		( 4*16 )

enum {
	WK_SEQ = 0,
//	WK_WIN_INDEX,
//	WK_LIST_ID,
	WK_LIST_RET,

	WK_MAX
};

typedef struct {
	void * fsys;
	GF_BGL_BMPWIN	win;

	BMPLIST_WORK * lw;
	BMP_MENULIST_DATA * ld;	// BMPリストデータ

	MSGDATA_MANAGER * mman;	// メッセージデータマネージャ

	u32	work[WK_MAX];
}D_NAKAHIRO_PARAM;

typedef void (*pHNfunc)(void *);

// カラーテーブル
/*
enum {
	COL_W_BLACK = 0,	// 黒（背景白）
	COL_W_BLUE,			// 青（背景白）
	COL_W_RED,			// 赤（背景白）
	COL_W_PINK,			// ピンク（背景白）
	COL_W_GREEN,		// 緑（背景白）
};
*/

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static void MainBmpListCB1( u32 param, u8 mode );
static void MainBmpListCB2( u8 index, u32 param, u8 y );
static void DN_MenuMain( TCB_PTR _tcb, void * work );
static void DN_MenuExit( D_NAKAHIRO_PARAM * wk );

static void DebugSleepSet(void);
static void DebugDispCheckCall( void * fsys );
static void DebugNutsMax( void * fsys );
static void DebugWazaMachineMax( void * fsys );
static void DebugFNoteSet( void * fsys );
static void DebugFNoteClear( void * fsys );
static void DebugPokeWinInit( void * fsys );

static void DebugFieldPokeStatus( FIELDSYS_WORK * fsys );
static void DebugWazaSetPokeStatus( FIELDSYS_WORK * fsys );
static void DebugWazaDelPokeStatus( FIELDSYS_WORK * fsys );
static void DebugPorutoPokeStatus( FIELDSYS_WORK * fsys );
static void DebugConditionPokeStatus( FIELDSYS_WORK * fsys );

static void DebugVSDemoCall1( FIELDSYS_WORK * fsys );
static void DebugVSDemoCall2( FIELDSYS_WORK * fsys );
static void DebugVSDemoCall3( FIELDSYS_WORK * fsys );
static void DebugVSDemoCall4( FIELDSYS_WORK * fsys );
static void DebugVSDemoCall5( FIELDSYS_WORK * fsys );
static void DebugVSDemoCall6( FIELDSYS_WORK * fsys );
static void DebugVSDemoCall7( FIELDSYS_WORK * fsys );

//static void DebugWazaOshieSet( FIELDSYS_WORK * fsys, u16 mode );
static void DebugWazaOshieCall1( FIELDSYS_WORK * fsys );
static void DebugWazaOshieCall2( FIELDSYS_WORK * fsys );
//static void DebugWazaOshieProcSet( FIELDSYS_WORK * fsys , D_WO_WORK * wk );
static BOOL D_WazaOshieEvent( GMEVENT_CONTROL * event );
static void DebugRibbonAdd( void * fsys );

static void DebugPokeIconCheckInit( void * fsys );
static void DebugItemIconCheckInit( void * fsys );

void DebugNakamuraInit( void * fsys );
void DebugEncountSetInit( void * fsys );
void DebugItemMakeInit( void * fsys );
void DebugPokemonMakeInit( void * fsys );
void DebugPokemonChangeInit( void * fsys );
void DebugDameTamagoSet( void * fsys );


//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
#define	MAIN_BMPLIST_MAX	( 9 )

static const u32 d_menu_list[][2] =
{
	{ msg_menu_10, (u32)DebugNutsMax },
//	{ msg_menu_10, (u32)DebugPokeWinInit },
	{ msg_menu_11, (u32)DebugWazaMachineMax },
	{ msg_menu_05, (u32)DebugDispCheckCall },
	{ msg_menu_28, (u32)DebugPokeIconCheckInit },
	{ msg_menu_29, (u32)DebugItemIconCheckInit },
	{ msg_menu_27, (u32)DebugRibbonAdd },

	{ msg_label_04,	BMPLIST_RABEL },
	{ msg_menu_12, (u32)DebugFNoteSet },
	{ msg_menu_30, (u32)DebugFNoteClear },
/*
	{ msg_label_03,	BMPLIST_RABEL },
	{ msg_menu_25, (u32)DebugWazaOshieCall1 },
	{ msg_menu_26, (u32)DebugWazaOshieCall2 },
*/
/*
	{ msg_label_02,	BMPLIST_RABEL },
	{ msg_menu_18, (u32)DebugVSDemoCall6 },
	{ msg_menu_21, (u32)DebugVSDemoCall7 },
	{ msg_menu_19, (u32)DebugVSDemoCall1 },
	{ msg_menu_22, (u32)DebugVSDemoCall2 },
	{ msg_menu_20, (u32)DebugVSDemoCall3 },
	{ msg_menu_23, (u32)DebugVSDemoCall4 },
	{ msg_menu_24, (u32)DebugVSDemoCall5 },
*/
/*
	{ msg_label_01,	BMPLIST_RABEL },
	{ msg_menu_27, (u32)DebugRibbonAdd },
	{ msg_menu_13, (u32)DebugFieldPokeStatus },
	{ msg_menu_14, (u32)DebugWazaSetPokeStatus },
	{ msg_menu_15, (u32)DebugWazaDelPokeStatus },
	{ msg_menu_16, (u32)DebugPorutoPokeStatus },
	{ msg_menu_17, (u32)DebugConditionPokeStatus },
*/
};

static const BMPLIST_HEADER d_menu_list_h = {
	NULL,				// 表示文字データポインタ
	NULL,				// カーソル移動ごとのコールバック関数
	NULL,				// 一列表示ごとのコールバック関数
	NULL,
	MAIN_BMPLIST_MAX,	// リスト項目数
	6,						// 表示最大項目数
	0,						// ラベル表示Ｘ座標
	12,						// 項目表示Ｘ座標
	0,						// カーソル表示Ｘ座標
	0,						// 表示Ｙ座標
	FBMP_COL_WHITE,			//文字色
	FBMP_COL_BLACK,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
	0,						// 文字間隔Ｘ
	16,						// 文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,		// ページスキップタイプ
	FONT_SYSTEM,			// 文字指定(本来は u8 だけど、そんなに作らないと思うので)
	0						// ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
};

// フォントカラーテーブル
static const u8 ColorTbl[][3] =
{
	{ 15, 1, 2 },	// 黒（背景白）
	{ 15, 3, 4 },	// 青（背景白）
	{ 15, 5, 6 },	// 赤（背景白）
	{ 15, 7, 8 },	// ピンク（背景白）
	{ 15, 9, 10 },	// 緑（背景白）
};

#define	COL_W_BLACK	( GF_PRINTCOLOR_MAKE( 1, 2, 15 ) )	// フォントカラー：黒
#define	COL_W_BLUE	( GF_PRINTCOLOR_MAKE( 3, 4, 15 ) )	// フォントカラー：青
#define	COL_W_RED	( GF_PRINTCOLOR_MAKE( 5, 6, 15 ) )	// フォントカラー：赤
#define	COL_W_PINK	( GF_PRINTCOLOR_MAKE( 7, 8, 15 ) )	// フォントカラー：赤
#define	COL_W_GREEN	( GF_PRINTCOLOR_MAKE( 9, 10, 15 ) )	// フォントカラー：赤



void DebugNakamuraInit( void * fsys )
{
	D_NAKAHIRO_PARAM * wk;
	GF_BGL_INI * bgl;
	BMPLIST_HEADER	list_h;
	u32	i;


	OS_Printf( "HEAPID_WORLD : %d\n", sys_GetHeapFreeSize( HEAPID_WORLD ) );

	bgl = FieldBglIniGet( fsys );

	wk = (D_NAKAHIRO_PARAM *)TCB_GetWork(
					PMDS_taskAdd( DN_MenuMain, sizeof(D_NAKAHIRO_PARAM), 0, HEAPID_BASE_APP ) );

	wk->fsys = fsys;
	wk->work[ WK_SEQ ] = 0;
	GF_BGL_BmpWinAdd( bgl, &wk->win, FLD_MBGFRM_FONT, 1, 1, 12, 12, 13, 1 );

	wk->mman = MSGMAN_Create(
				MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_debug_nakahiro_dat, HEAPID_BASE_APP );

	wk->ld = BMP_MENULIST_Create( MAIN_BMPLIST_MAX, HEAPID_BASE_APP );
	for( i=0; i<MAIN_BMPLIST_MAX; i++ ){
		BMP_MENULIST_AddArchiveString( wk->ld, wk->mman, d_menu_list[i][0], d_menu_list[i][1] );
	}

	list_h = d_menu_list_h;
	list_h.list = wk->ld;
	list_h.win  = &wk->win;
	wk->lw = BmpListSet( &list_h, 0, 0, HEAPID_BASE_APP );

	GF_BGL_BmpWinOn( &wk->win );
}

static void DN_MenuMain( TCB_PTR _tcb, void * work )
{
	D_NAKAHIRO_PARAM * wk = (D_NAKAHIRO_PARAM *)work;
	GF_BGL_INI * bgl;
	u32	ret;

	switch( wk->work[ WK_SEQ ] ){
	case 0:
		ret = BmpListMain( wk->lw );

		switch( ret ){
		case BMPLIST_NULL:
			break;
		case BMPLIST_CANCEL:
			DN_MenuExit( wk );
			PMDS_taskDel( _tcb );
			FieldSystemProc_SeqHoldEnd();
			break;
		default:
			wk->work[WK_LIST_RET] = ret;
			wk->work[WK_SEQ]++;
		}
		break;
	case 1:
		{
			pHNfunc func = (pHNfunc)wk->work[WK_LIST_RET];
			void * fsys = wk->fsys;

			DN_MenuExit( wk );
			PMDS_taskDel( _tcb );
			func( fsys );
		}
	}
}

static void DN_MenuExit( D_NAKAHIRO_PARAM * wk )
{
	BmpListExit( wk->lw, NULL, NULL );
	BMP_MENULIST_Delete( wk->ld );

	MSGMAN_Delete( wk->mman );

	GF_BGL_BmpWinOff( &wk->win );
	GF_BGL_BmpWinDel( &wk->win );
}





//============================================================================================
//	ステータス画面
//============================================================================================
typedef struct {
//	void * fsys;
	PSTATUS_DATA * psd;
	u32	seq;
}DEBUG_P_STATUS;

//static void D_PokeStatusTask( TCB_PTR _tcb, void * work );
static BOOL D_PokeStatusTask( GMEVENT_CONTROL * event );


// 通常
static void DebugFieldPokeStatus( FIELDSYS_WORK * fsys )
{
	DEBUG_P_STATUS * wk;

	u8	page[] = {
		PST_PAGE_INFO, PST_PAGE_MEMO, PST_PAGE_PARAM, PST_PAGE_CONDITION,
		PST_PAGE_B_SKILL, PST_PAGE_C_SKILL, PST_PAGE_RIBBON, PST_PAGE_RET, PST_PAGE_MAX
	};

	wk = sys_AllocMemory( HEAPID_BASE_APP, sizeof(DEBUG_P_STATUS) );

	wk->seq  = 0;
	wk->psd  = sys_AllocMemory( HEAPID_BASE_APP, sizeof(PSTATUS_DATA) );

	wk->psd->ppd  = SaveData_GetTemotiPokemon( ((FIELDSYS_WORK *)fsys)->savedata );
	wk->psd->cfg  = SaveData_GetConfig( fsys->savedata );
	wk->psd->ppt  = PST_PP_TYPE_POKEPARTY;
	wk->psd->pos  = 0;
	wk->psd->max  = (u8)PokeParty_GetPokeCount( wk->psd->ppd );
	wk->psd->waza = 0;
	wk->psd->mode = PST_MODE_NORMAL;
	wk->psd->ribbon = SaveData_GetSpRibbon( ((FIELDSYS_WORK *)fsys)->savedata );
	wk->psd->zukan_mode = PMNumber_GetMode( ((FIELDSYS_WORK *)fsys)->savedata );
	wk->psd->ev_contest = 1;
	wk->psd->perap = NULL;
	PokeStatus_PageSet( wk->psd, page );
	PokeStatus_PlayerSet(
		wk->psd, SaveData_GetMyStatus( ((FIELDSYS_WORK *)fsys)->savedata ) );

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );

	FieldEvent_Set( fsys, D_PokeStatusTask, wk );
}

// 技覚え
static void DebugWazaSetPokeStatus( FIELDSYS_WORK * fsys )
{
	DEBUG_P_STATUS * wk;

	u8	page[] = { PST_PAGE_B_SKILL, PST_PAGE_C_SKILL, PST_PAGE_MAX };

	wk = sys_AllocMemory( HEAPID_BASE_APP, sizeof(DEBUG_P_STATUS) );

	wk->seq  = 0;
	wk->psd  = sys_AllocMemory( HEAPID_BASE_APP, sizeof(PSTATUS_DATA) );

	wk->psd->ppd  = SaveData_GetTemotiPokemon( ((FIELDSYS_WORK *)fsys)->savedata );
	wk->psd->cfg  = SaveData_GetConfig( fsys->savedata );
	wk->psd->ppt  = PST_PP_TYPE_POKEPARTY;
	wk->psd->pos  = 0;
	wk->psd->max  = (u8)PokeParty_GetPokeCount( wk->psd->ppd );
	wk->psd->waza = 0x20;
	wk->psd->mode = PST_MODE_WAZAADD;
	wk->psd->zukan_mode = PMNumber_GetMode( ((FIELDSYS_WORK *)fsys)->savedata );
	wk->psd->ev_contest = 1;
	wk->psd->perap = NULL;
	PokeStatus_PageSet( wk->psd, page );
	PokeStatus_PlayerSet(
		wk->psd, SaveData_GetMyStatus( ((FIELDSYS_WORK *)fsys)->savedata ) );

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );

	FieldEvent_Set( fsys, D_PokeStatusTask, wk );
}

// 技忘れ
static void DebugWazaDelPokeStatus( FIELDSYS_WORK * fsys )
{
	DEBUG_P_STATUS * wk;

	u8	page[] = { PST_PAGE_B_SKILL, PST_PAGE_C_SKILL, PST_PAGE_MAX };

	wk = sys_AllocMemory( HEAPID_BASE_APP, sizeof(DEBUG_P_STATUS) );

	wk->seq  = 0;
	wk->psd  = sys_AllocMemory( HEAPID_BASE_APP, sizeof(PSTATUS_DATA) );

	wk->psd->ppd  = SaveData_GetTemotiPokemon( ((FIELDSYS_WORK *)fsys)->savedata );
	wk->psd->cfg  = SaveData_GetConfig( fsys->savedata );
	wk->psd->ppt  = PST_PP_TYPE_POKEPARTY;
	wk->psd->pos  = 0;
	wk->psd->max  = (u8)PokeParty_GetPokeCount( wk->psd->ppd );
	wk->psd->waza = 0;
	wk->psd->mode = PST_MODE_WAZAADD;
	wk->psd->zukan_mode = PMNumber_GetMode( ((FIELDSYS_WORK *)fsys)->savedata );
	wk->psd->ev_contest = 1;
	wk->psd->perap = NULL;
	PokeStatus_PageSet( wk->psd, page );
	PokeStatus_PlayerSet(
		wk->psd, SaveData_GetMyStatus( ((FIELDSYS_WORK *)fsys)->savedata ) );

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );

	FieldEvent_Set( fsys, D_PokeStatusTask, wk );
}

// ポルト使用
static void DebugPorutoPokeStatus( FIELDSYS_WORK * fsys )
{
	DEBUG_P_STATUS * wk;

	u8	page[] = { PST_PAGE_CONDITION, PST_PAGE_RET, PST_PAGE_MAX };

	wk = sys_AllocMemory( HEAPID_BASE_APP, sizeof(DEBUG_P_STATUS) );

	wk->seq  = 0;
	wk->psd  = sys_AllocMemory( HEAPID_BASE_APP, sizeof(PSTATUS_DATA) );

	wk->psd->ppd  = SaveData_GetTemotiPokemon( ((FIELDSYS_WORK *)fsys)->savedata );
	wk->psd->cfg  = SaveData_GetConfig( fsys->savedata );
	wk->psd->ppt  = PST_PP_TYPE_POKEPARTY;
	wk->psd->pos  = 0;
	wk->psd->max  = (u8)PokeParty_GetPokeCount( wk->psd->ppd );
	wk->psd->waza = 0;
	wk->psd->mode = PST_MODE_PORUTO;
	wk->psd->zukan_mode = PMNumber_GetMode( ((FIELDSYS_WORK *)fsys)->savedata );
	wk->psd->ev_contest = 1;
	wk->psd->perap = NULL;
	PokeStatus_PageSet( wk->psd, page );
	PokeStatus_PlayerSet(
		wk->psd, SaveData_GetMyStatus( ((FIELDSYS_WORK *)fsys)->savedata ) );

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );

	FieldEvent_Set( fsys, D_PokeStatusTask, wk );
}

// コンディション変更デモ
static void DebugConditionPokeStatus( FIELDSYS_WORK * fsys )
{
	DEBUG_P_STATUS * wk;

	u8	page[] = { PST_PAGE_CONDITION, PST_PAGE_MAX };

	wk = sys_AllocMemory( HEAPID_BASE_APP, sizeof(DEBUG_P_STATUS) );

	wk->seq  = 0;
	wk->psd  = sys_AllocMemory( HEAPID_BASE_APP, sizeof(PSTATUS_DATA) );

	wk->psd->ppd  = SaveData_GetTemotiPokemon( ((FIELDSYS_WORK *)fsys)->savedata );
	wk->psd->cfg  = SaveData_GetConfig( fsys->savedata );
	wk->psd->ppt  = PST_PP_TYPE_POKEPARTY;
	wk->psd->pos  = 0;
	wk->psd->max  = (u8)PokeParty_GetPokeCount( wk->psd->ppd );
	wk->psd->waza = 0;
	wk->psd->mode = PST_MODE_CONDITION;
	wk->psd->zukan_mode = PMNumber_GetMode( ((FIELDSYS_WORK *)fsys)->savedata );
	wk->psd->ev_contest = 1;
	wk->psd->perap = NULL;
	PokeStatus_PageSet( wk->psd, page );
	PokeStatus_PlayerSet(
		wk->psd, SaveData_GetMyStatus( ((FIELDSYS_WORK *)fsys)->savedata ) );

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );

	FieldEvent_Set( fsys, D_PokeStatusTask, wk );
}


static BOOL D_PokeStatusTask( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	DEBUG_P_STATUS * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	switch( wk->seq ){
	case 0:
		if( WIPE_SYS_EndCheck() ){
			FieldSystemProc_SeqHoldEnd();
//			FieldOBJSys_MoveStopAll( fsys->fldobjsys );
			FieldOBJSys_MovePauseAll( fsys->fldobjsys );
			FieldPokeStatus_SetProc( fsys, wk->psd );
			wk->seq = 1;
		}
		break;

	case 1:
		if( !( FieldEvent_Cmd_WaitSubProcEnd(fsys) ) ) {
			sys_FreeMemoryEz( wk->psd );
			FieldEvent_Cmd_SetMapProc( fsys );
			wk->seq = 2;
		}
		break;

	case 2:
		if( FieldEvent_Cmd_WaitMapProcStart( fsys ) ){
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
			wk->seq = 3;
		}
		break;

	case 3:
		if( WIPE_SYS_EndCheck() ){
			sys_FreeMemoryEz( wk );
//			FieldOBJSys_MoveStopAllClear( fsys->fldobjsys );
			FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
//	リボン追加
//--------------------------------------------------------------------------------------------
static void DebugRibbonAdd( void * fsys )
{
	POKEPARTY * party;
	POKEMON_PARAM * pp;
	u32	i;
	u8	flg;

	party = SaveData_GetTemotiPokemon( ((FIELDSYS_WORK *)fsys)->savedata );
	pp = PokeParty_GetMemberPointer( party, 0 );
	flg = 1;

	for( i=0; i<RIBBON_MAX; i++ ){
		PokeParaPut( pp, RIBBON_DataGet( i, RIBBON_PARA_POKEPARA ), &flg );
	}

	FieldSystemProc_SeqHoldEnd();
}


//============================================================================================
//	VSデモ
//============================================================================================
extern PROC_RESULT D_VsDemoProc_Main( PROC * proc, int * seq );
extern PROC_RESULT D_VsDemoProc_End( PROC * proc, int * seq );
extern PROC_RESULT D_VSDemoProc_Init00( PROC * proc, int * seq );
extern PROC_RESULT D_VSDemoProc_Init01( PROC * proc, int * seq );
extern PROC_RESULT D_VSDemoProc_Init10( PROC * proc, int * seq );
extern PROC_RESULT D_VSDemoProc_Init11( PROC * proc, int * seq );
extern PROC_RESULT D_VSDemoProc_Init20( PROC * proc, int * seq );
extern PROC_RESULT D_VSDemoProc_Init21( PROC * proc, int * seq );
extern PROC_RESULT D_VSDemoProc_Init22( PROC * proc, int * seq );



static BOOL D_VSDemoEvent( GMEVENT_CONTROL * event );

typedef struct {
//	const PROC_DATA * pd;
	u16	seq;
	u16	id;
}D_VSD_WORK;


static void DebugVSDemoSet( FIELDSYS_WORK * fsys, u16 id )
{
	D_VSD_WORK * wk;

	wk = sys_AllocMemory( HEAPID_BASE_APP, sizeof(D_VSD_WORK) );
	wk->seq = 0;
	wk->id  = id;
	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );
	FieldEvent_Set( fsys, D_VSDemoEvent, wk );
}

static void DebugVSDemoCall1( FIELDSYS_WORK * fsys )
{
	DebugVSDemoSet( fsys, 0 );
}
static void DebugVSDemoCall2( FIELDSYS_WORK * fsys )
{
	DebugVSDemoSet( fsys, 1 );
}
static void DebugVSDemoCall3( FIELDSYS_WORK * fsys )
{
	DebugVSDemoSet( fsys, 2 );
}
static void DebugVSDemoCall4( FIELDSYS_WORK * fsys )
{
	DebugVSDemoSet( fsys, 3 );
}
static void DebugVSDemoCall5( FIELDSYS_WORK * fsys )
{
	DebugVSDemoSet( fsys, 4 );
}
static void DebugVSDemoCall6( FIELDSYS_WORK * fsys )
{
	DebugVSDemoSet( fsys, 5 );
}
static void DebugVSDemoCall7( FIELDSYS_WORK * fsys )
{
	DebugVSDemoSet( fsys, 6 );
}

static void DebugVSDProcSet( FIELDSYS_WORK * fsys, D_VSD_WORK * wk )
{
	// オーバーレイID宣言
	FS_EXTERN_OVERLAY(vs_demo);

	const PROC_DATA D_VSDProcData[] =
	{
		{ D_VSDemoProc_Init10, D_VsDemoProc_Main, D_VsDemoProc_End, FS_OVERLAY_ID(vs_demo) },
		{ D_VSDemoProc_Init11, D_VsDemoProc_Main, D_VsDemoProc_End, FS_OVERLAY_ID(vs_demo) },
		{ D_VSDemoProc_Init20, D_VsDemoProc_Main, D_VsDemoProc_End, FS_OVERLAY_ID(vs_demo) },
		{ D_VSDemoProc_Init21, D_VsDemoProc_Main, D_VsDemoProc_End, FS_OVERLAY_ID(vs_demo) },
		{ D_VSDemoProc_Init22, D_VsDemoProc_Main, D_VsDemoProc_End, FS_OVERLAY_ID(vs_demo) },
		{ D_VSDemoProc_Init00, D_VsDemoProc_Main, D_VsDemoProc_End, FS_OVERLAY_ID(vs_demo) },
		{ D_VSDemoProc_Init01, D_VsDemoProc_Main, D_VsDemoProc_End, FS_OVERLAY_ID(vs_demo) },
	};

	GameSystem_StartSubProc( fsys, &D_VSDProcData[wk->id], NULL );
}


static BOOL D_VSDemoEvent( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	D_VSD_WORK * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	switch( wk->seq ){
	case 0:
		if( WIPE_SYS_EndCheck() ){
			FieldSystemProc_SeqHoldEnd();
			FieldOBJSys_MoveStopAll( fsys->fldobjsys );
//			GameSystem_StartSubProc( fsys, wk->pd, NULL );
			DebugVSDProcSet( fsys, wk );
			wk->seq = 1;
		}
		break;

	case 1:
		if( !( FieldEvent_Cmd_WaitSubProcEnd(fsys) ) ) {
			FieldEvent_Cmd_SetMapProc( fsys );
			wk->seq = 2;
		}
		break;

	case 2:
		if( FieldEvent_Cmd_WaitMapProcStart( fsys ) ){
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
			wk->seq = 3;
		}
		break;

	case 3:
		if( WIPE_SYS_EndCheck() ){
			sys_FreeMemoryEz( wk );
			FieldOBJSys_MoveStopAllClear( fsys->fldobjsys );
			return TRUE;
		}
	}
	return FALSE;
}


//============================================================================================
//	技教え
//============================================================================================
extern void WazaOshie_ProcSet( FIELDSYS_WORK * fsys , WAZAOSHIE_DATA * wk );

typedef struct {
	WAZAOSHIE_DATA	dat;
	u32	seq;
}D_WO_WORK;

static const u16 DebugWazaOshieTbl[] = {
	 1, 2, 3, 4, 5, 6, 7, 8, 9,10,
	11,12,13,14,15,16,17,18,19,20,
	21,22,23,24,25,26,27,28,29,30, WAZAOSHIE_TBL_MAX
};

static void DebugWazaOshieCall1( FIELDSYS_WORK * fsys )
{
	D_WO_WORK * wk;

	wk = sys_AllocMemory( HEAPID_BASE_APP, sizeof(D_WO_WORK) );
	wk->seq  = 0;

	wk->dat.pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), 0 );
	wk->dat.cfg  = SaveData_GetConfig( fsys->savedata );
	wk->dat.myst = SaveData_GetMyStatus( fsys->savedata );
	wk->dat.waza_tbl = (u16 *)&DebugWazaOshieTbl;
	wk->dat.pos = 0;
	wk->dat.scr = 0;
	wk->dat.page = 0;
	wk->dat.mode = WAZAOSHIE_MODE_TEACH;
	wk->dat.ret = 0;

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );
	FieldEvent_Set( fsys, D_WazaOshieEvent, wk );
}

static void DebugWazaOshieCall2( FIELDSYS_WORK * fsys )
{
	D_WO_WORK * wk;

	wk = sys_AllocMemory( HEAPID_BASE_APP, sizeof(D_WO_WORK) );
	wk->seq  = 0;

	wk->dat.pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), 0 );
	wk->dat.cfg  = SaveData_GetConfig( fsys->savedata );
	wk->dat.myst = SaveData_GetMyStatus( fsys->savedata );
	wk->dat.waza_tbl = RemaindWazaGet( wk->dat.pp, HEAPID_BASE_APP );
	wk->dat.pos = 0;
	wk->dat.scr = 0;
	wk->dat.page = 0;
	wk->dat.mode = WAZAOSHIE_MODE_REMIND;
	wk->dat.ret = 0;

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );
	FieldEvent_Set( fsys, D_WazaOshieEvent, wk );
}

static BOOL D_WazaOshieEvent( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	D_WO_WORK * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	switch( wk->seq ){
	case 0:
		if( WIPE_SYS_EndCheck() ){
			FieldSystemProc_SeqHoldEnd();
			FieldOBJSys_MoveStopAll( fsys->fldobjsys );
			WazaOshie_ProcSet( fsys , &wk->dat );
			wk->seq = 1;
		}
		break;

	case 1:
		if( !( FieldEvent_Cmd_WaitSubProcEnd(fsys) ) ) {
			FieldEvent_Cmd_SetMapProc( fsys );
			wk->seq = 2;
		}
		break;

	case 2:
		if( FieldEvent_Cmd_WaitMapProcStart( fsys ) ){
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
			wk->seq = 3;
		}
		break;

	case 3:
		if( WIPE_SYS_EndCheck() ){
			if( wk->dat.mode == WAZAOSHIE_MODE_REMIND ){
				sys_FreeMemoryEz( wk->dat.waza_tbl );
			}
			sys_FreeMemoryEz( wk );
			FieldOBJSys_MoveStopAllClear( fsys->fldobjsys );
			return TRUE;
		}
	}
	return FALSE;
}








typedef struct {
	FIELDSYS_WORK * fsys;
	GF_BGL_BMPWIN win;
	STRBUF * msg;
	void * dsi_task;
	u16	seq;
	u8	cnt;
	u8	midx;
}DEBUG_DISPCHECK;

static void DebugDispCheckMain( TCB_PTR _tcb, void * work );


static void DebugDispCheckCall( void * fsys )
{
	DEBUG_DISPCHECK * wk;

	wk = (DEBUG_DISPCHECK *)TCB_GetWork(
				PMDS_taskAdd( DebugDispCheckMain,
				sizeof(DEBUG_DISPCHECK), 8, HEAPID_BASE_APP ) );
	wk->seq = 0;
	wk->cnt = 0;
	wk->fsys = fsys;
	FldTalkBmpAdd( FieldBglIniGet(fsys), &wk->win, FLD_MBGFRM_FONT );

	wk->dsi_task = MSG_DsIconFlashAdd( NULL, MSG_DSI_MAINDISP, FLD_MSG_WIN_PAL, HEAPID_BASE_APP );
}

static void DebugDispCheckMain( TCB_PTR _tcb, void * work )
{
	DEBUG_DISPCHECK * wk = (DEBUG_DISPCHECK * )work;
	GF_BGL_INI * bgl = FieldBglIniGet( wk->fsys );

	switch( wk->seq ){
	case 0:		// init
		FieldTalkWinPut( &wk->win, SaveData_GetConfig(wk->fsys->savedata) );
		{
			MSGDATA_MANAGER * man = MSGMAN_Create(
				MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_icontest_dat, HEAPID_BASE_APP );
//			WORDSET * wset = WORDSET_Create( HEAPID_BASE_APP );
//			STRBUF * exp = STRBUF_Create( 64, HEAPID_BASE_APP );
			wk->msg = MSGMAN_AllocString( man, msg_icontest_0001+wk->cnt );
//			WORDSET_ExpandStr( wset, exp, wk->msg );
			MSGMAN_Delete( man );
//			WORDSET_Delete( wset );
//			GF_STR_PrintSimple( &wk->win, FONT_TALK, exp, 0, 0, MSG_ALLPUT, NULL );
		}
		wk->midx = FieldTalkMsgStart(
						&wk->win, wk->msg, SaveData_GetConfig(wk->fsys->savedata), 1 );
		wk->seq++;
		break;
	case 1:		// main
		if( FldTalkMsgEndCheck( wk->midx ) == 0 ){
			return;
		}
		STRBUF_Delete( wk->msg );
		wk->seq = 2;
		break;
	case 2:
		if( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ){
			if( wk->cnt == 3 ){
				wk->seq = 3;
			}else{
				wk->seq = 0;
			}
			wk->cnt++;
		}
		break;
	case 3:		// end
		BmpTalkWinClear( &wk->win, WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->win );

		MSG_DsIconFlashReq( wk->dsi_task, MSG_DSI_REQ_FREE );

		PMDS_taskDel( _tcb );
		FieldSystemProc_SeqHoldEnd();
		break;
	}
}










//============================================================================================
//	アイテムMAX
//============================================================================================
static void DebugItemAdd( MYITEM * myitem, u32 id, u32 add_max )
{
	u16	num;

	num = MyItem_GetItemNum( myitem, id, HEAPID_BASE_APP );
	if( num == add_max ){ return; }
	MyItem_AddItem( myitem, id, add_max-num, HEAPID_BASE_APP );
}

//--------------------------------------------------------------------------------------------
//	木の実MAX
//--------------------------------------------------------------------------------------------
static void DebugNutsMax( void * fsys )
{
	MYITEM * myitem;
	u32	i;

	myitem = SaveData_GetMyItem( ((FIELDSYS_WORK *)fsys)->savedata );

	for( i=0; i<ITEM_NUTS_MAX; i++ ){
		DebugItemAdd( myitem, ITEM_KURABONOMI+i, 999 );
	}
	FieldSystemProc_SeqHoldEnd();
}

//--------------------------------------------------------------------------------------------
//	技マシンMAX
//--------------------------------------------------------------------------------------------
static void DebugWazaMachineMax( void * fsys )
{
	MYITEM * myitem;
	u32	i;

	myitem = SaveData_GetMyItem( ((FIELDSYS_WORK *)fsys)->savedata );

	for( i=0; i<92; i++ ){
		DebugItemAdd( myitem, ITEM_WAZAMASIN01+i, 99 );
	}
	for( i=0; i<8; i++ ){
		DebugItemAdd( myitem, ITEM_HIDENMASIN01+i, 99 );
	}
	FieldSystemProc_SeqHoldEnd();
}




//============================================================================================
//	冒険ノートセット
//============================================================================================
// 追加
static void DebugFNoteSet( void * fsys )
{
	MYITEM * myitem;
	u32	i;

	myitem = SaveData_GetMyItem( ((FIELDSYS_WORK *)fsys)->savedata );
	MyItem_AddItem( myitem, ITEM_BOUKENNOOTO, 1, HEAPID_BASE_APP );

	SysFlag_FNoteSet( SaveData_GetEventWork(((FIELDSYS_WORK *)fsys)->savedata) );

	((FIELDSYS_WORK *)fsys)->fnote =
		FNOTE_SavePageGet( SaveData_GetFNote(((FIELDSYS_WORK *)fsys)->savedata), TRUE );

	FNoteStartDataSet( fsys );
/*
	{
		void * buf = FNOTE_SioPorutoDataMake( HEAPID_BASE_APP );
		FNOTE_DataSave( ((FIELDSYS_WORK *)fsys)->fnote, buf, FNOTE_TYPE_SIO );
	}
*/
	FieldSystemProc_SeqHoldEnd();
}

// 初期化
static void DebugFNoteClear( void * fsys )
{
	FNOTE_InitAll( SaveData_GetFNote(((FIELDSYS_WORK *)fsys)->savedata) );
	DebugFNoteSet( fsys );
}


//============================================================================================
//	スリープモード
//============================================================================================
static void B_SleepCallBack( void * arg )
{
	OS_Printf( "INFO : B_SleepCallBack\n" );
}
static void A_SleepCallBack( void * arg )
{
	OS_Printf( "INFO : A_SleepCallBack\n" );
}

static void DebugSleepSet(void)
{
//	GF_SleepSystemInit();
/*
	{
		PMSleepCallbackInfo	b_info = { B_SleepCallBack, NULL, NULL };
		PMSleepCallbackInfo	a_info = { A_SleepCallBack, NULL, NULL };

		GF_SleepSystemSet(
			&b_info, &a_info, PM_TRIGGER_KEY,
			PM_PAD_LOGIC_AND, PAD_BUTTON_A | PAD_BUTTON_START, 0 );

		GF_SleepSystemDelete();
	}
*/
//	GF_SleepCoverCloseAdd();

	FieldSystemProc_SeqHoldEnd();
}


//============================================================================================
//	BMP OBJ TEST
//============================================================================================
/*
void GF_BmpPrintObj(
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
*/



//============================================================================================
//============================================================================================
//	ポケウィン
//============================================================================================
//============================================================================================
typedef struct {
	u8 * cmd;
	u32	flg;
}D_POKEWIN;


static void D_PokeWinMain( TCB_PTR _tcb, void * work );

static void DebugPokeWinInit( void * fsys )
{
	D_POKEWIN * wk;
	GF_BGL_INI * bgl;
	POKEMON_PARAM * pp;
	
	bgl = FieldBglIniGet( fsys );
	pp  = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(((FIELDSYS_WORK *)fsys)->savedata), 0 );

	wk = (D_POKEWIN *)TCB_GetWork(
			PMDS_taskAdd( D_PokeWinMain, sizeof(D_POKEWIN), 0, HEAPID_BASE_APP ) );

	MenuWinGraphicSet(
		bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_BASE_APP );
/*
	wk->cmd = PokeWindowPut(
				bgl, FLD_MBGFRM_FONT, 1, 1, MENU_WIN_PAL,
				MENU_WIN_CGX_NUM, MONSNO_PERAPPU, 0, HEAPID_WORLD );
*/
	wk->cmd = PokeWindowPutPP(
				bgl, FLD_MBGFRM_FONT, 1, 1, MENU_WIN_PAL, MENU_WIN_CGX_NUM, pp, HEAPID_WORLD );

	wk->flg = 0;
}

// メイン処理
static void D_PokeWinMain( TCB_PTR _tcb, void * work )
{
	D_POKEWIN * wk = work;

	if( wk->flg == 1 ){
		if( *wk->cmd == POKEWIN_CMD_NONE ){
			*wk->cmd = POKEWIN_CMD_END;
			PMDS_taskDel( _tcb );
			FieldSystemProc_SeqHoldEnd();
		}
		return;
	}

	if( sys.trg & PAD_BUTTON_A ){
		*wk->cmd = POKEWIN_CMD_ANM;
		wk->flg = 1;
		return;
	}
	if( sys.trg & PAD_BUTTON_B ){
		*wk->cmd = POKEWIN_CMD_END;
		PMDS_taskDel( _tcb );
		FieldSystemProc_SeqHoldEnd();
		return;
	}
}


//============================================================================================
//============================================================================================
//	エンカウント制御
//============================================================================================
//============================================================================================
typedef struct {
	FIELDSYS_WORK * fsys;
	GF_BGL_BMPWIN	win;
}D_ENCOUNT;

static void D_EncountSetMain( TCB_PTR _tcb, void * work );
static void D_EncountStrPut( D_ENCOUNT * wk );

// 初期化
void DebugEncountSetInit( void * fsys )
{
	D_ENCOUNT * wk;
	GF_BGL_INI * bgl;

	bgl = FieldBglIniGet( fsys );

	wk = (D_ENCOUNT *)TCB_GetWork(
			PMDS_taskAdd( D_EncountSetMain, sizeof(D_ENCOUNT), 0, HEAPID_BASE_APP ) );

	wk->fsys = fsys;
	GF_BGL_BmpWinAdd( bgl, &wk->win, FLD_MBGFRM_FONT, 1, 1, 5, 2, 13, 1 );

	MenuWinGraphicSet(
		bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_BASE_APP );
	BmpMenuWinWrite( &wk->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );

	D_EncountStrPut( wk );
}

// メイン処理
static void D_EncountSetMain( TCB_PTR _tcb, void * work )
{
	D_ENCOUNT * wk = (D_ENCOUNT *)work;

	if( sys.trg & (PAD_KEY_UP|PAD_KEY_DOWN|PAD_KEY_LEFT|PAD_KEY_RIGHT) ){
		DebugFlagData.encount_flag ^= 1;
		D_EncountStrPut( wk );
		return;
	}
	if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B) ){
		BmpMenuWinClear( &wk->win, WINDOW_TRANS_ON );
		GF_BGL_BmpWinOff( &wk->win );
		GF_BGL_BmpWinDel( &wk->win );
		PMDS_taskDel( _tcb );
		FieldSystemProc_SeqHoldEnd();
		return;
	}
}

static void D_EncountStrPut( D_ENCOUNT * wk )
{
	MSGDATA_MANAGER * mman;
	STRBUF * str;

	GF_BGL_BmpWinDataFill( &wk->win, 15 );

	mman = MSGMAN_Create(
			MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_nakahiro_dat, HEAPID_BASE_APP );
	if( DebugFlagData.encount_flag == 0 ){
		str = MSGMAN_AllocString( mman, msg_pmstr_04 );
	}else{
		str = MSGMAN_AllocString( mman, msg_pmstr_05 );
	}
	GF_STR_PrintColor( &wk->win, FONT_SYSTEM, str, 0, 0, MSG_ALLPUT, COL_W_BLACK, NULL );
	STRBUF_Delete( str );
	MSGMAN_Delete( mman );
}






//============================================================================================
//============================================================================================
//	ポケアイコンチェック
//============================================================================================
//============================================================================================
#define	PICON_MAX		( 12 )
#define	DHN_CLA_ID		( 53718 )

typedef struct {
	GF_BGL_BMPWIN	win[2];
	FIELDSYS_WORK * fsys;
	FIELD_CLACT	fcat;
	CATS_ACT_PTR	cap[PICON_MAX];
	u16	page;
	u16 mode;
	u16	form;
}D_POKEICON;

static void D_PokeIconChgAll( D_POKEICON * wk );
static void D_PokeIconChg( D_POKEICON * wk, u8 pos );
static void D_PokeIconFormChg( D_POKEICON * wk, s8 mv );
static void D_PokeIconStrPut( D_POKEICON * wk );

static void D_PokeIconCheckMain( TCB_PTR _tcb, void * work );
static void CellActSet( D_POKEICON * wk );
static void CellActDelete( D_POKEICON * wk );
static void CellActAnm( D_POKEICON * wk );

// 初期化
static void DebugPokeIconCheckInit( void * fsys )
{
	D_POKEICON * wk;
	GF_BGL_INI * bgl;

	bgl = FieldBglIniGet( fsys );

	wk = (D_POKEICON *)TCB_GetWork(
				PMDS_taskAdd( D_PokeIconCheckMain, sizeof(D_POKEICON), 0, HEAPID_BASE_APP ) );

	wk->fsys = fsys;
	wk->page = 0;
	wk->mode = 0;
	wk->form = 0;

	GF_BGL_BmpWinAdd( bgl, &wk->win[0], FLD_MBGFRM_FONT,  6, 0, 10, 24, 13, 1 );
	GF_BGL_BmpWinAdd( bgl, &wk->win[1], FLD_MBGFRM_FONT, 21, 0, 10, 24, 13, 1+10*24 );

	CellActSet( wk );
	D_PokeIconChgAll( wk );
	D_PokeIconStrPut( wk );

	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, 0x7fff );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
}

// メイン処理
static void D_PokeIconCheckMain( TCB_PTR _tcb, void * work )
{
	D_POKEICON * wk = (D_POKEICON *)work;

	if( sys.trg & PAD_KEY_UP ){
		if( wk->page != 0 ){
			wk->page--;
			wk->form = 0;
			D_PokeIconChgAll( wk );
			D_PokeIconStrPut( wk );
		}
	}else if( sys.trg & PAD_KEY_DOWN ){
		if( wk->page < (MONSNO_END/PICON_MAX) ){
			wk->page++;
			wk->form = 0;
			D_PokeIconChgAll( wk );
			D_PokeIconStrPut( wk );
		}
	}else if( sys.trg & PAD_KEY_LEFT ){
		if( wk->page >= 10 ){
			wk->page -= 10;
		}else{
			wk->page = 0;
		}
		wk->form = 0;
		D_PokeIconChgAll( wk );
		D_PokeIconStrPut( wk );
	}else if( sys.trg & PAD_KEY_RIGHT ){
		wk->page += 10;
		if( wk->page > (MONSNO_END/PICON_MAX) ){
			wk->page = (MONSNO_END/PICON_MAX);
		}
		wk->form = 0;
		D_PokeIconChgAll( wk );
		D_PokeIconStrPut( wk );
	}else if( sys.trg & PAD_BUTTON_R ){
		D_PokeIconFormChg( wk, 1 );
	}else if( sys.trg & PAD_BUTTON_L ){
		D_PokeIconFormChg( wk, -1 );
	}else if( sys.trg & PAD_BUTTON_B ){
		CellActDelete( wk );
		GF_BGL_BmpWinOff( &wk->win[0] );
		GF_BGL_BmpWinOff( &wk->win[1] );
		GF_BGL_BmpWinDel( &wk->win[0] );
		GF_BGL_BmpWinDel( &wk->win[1] );
		PMDS_taskDel( _tcb );
		GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, 0 );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
		FieldSystemProc_SeqHoldEnd();
		return;
	}

	CellActAnm( wk );
	CLACT_Draw( wk->fcat.cas );
}

static void D_PokeIconChgAll( D_POKEICON * wk )
{
	u32	i;

	for( i=0; i<PICON_MAX; i++ ){
		D_PokeIconChg( wk, (u8)i );
	}
}

static void D_PokeIconChg( D_POKEICON * wk, u8 pos )
{
	u16	mons;
	u16	egg;

	mons = wk->page * PICON_MAX + pos;

	if( mons == 494 ){
		egg = 1;
	}else if( mons == 495 ){
		mons = MONSNO_MANAFI;
		egg  = 1;
	}else{
		egg = 0;
	}

	FldClact_ChangeResourceCharArc(
		&wk->fcat, ARC_POKEICON,
		PokeIconCgxArcIndexGetByMonsNumber(mons,egg,wk->form), 0, DHN_CLA_ID+pos );
	CATS_ObjectPaletteSetCap( wk->cap[pos], PokeIconPalNumGet(mons,wk->form,egg) );
}

static u8 D_PokeIconFormMaxGet( u16 mons )
{
	if( mons == MONSNO_DEOKISISU ){
		return 4;
	}else if( mons == MONSNO_ANNOON ){
		return 28;
	}else if( mons == MONSNO_MINOMUTTI ){
		return 3;
	}else if( mons == MONSNO_MINOMESU ){
		return 3;
	}else if( mons == MONSNO_SIIUSI ){
		return 2;
	}else if( mons == MONSNO_SIIDORUGO ){
		return 2;
	}
	return 0;
}

static void D_PokeIconFormChg( D_POKEICON * wk, s8 mv )
{
	u16	i;
	u16	mons;
	s32	form;
	u16	flg=0;
	u16	old;

	form = wk->form + mv;
	if( form < 0 ){ return; }
	if( form > 28 ){ return; }

	old = wk->form;
	wk->form = form;

	for( i=0; i<PICON_MAX; i++ ){
		mons = wk->page * PICON_MAX + i;
		if( D_PokeIconFormMaxGet( mons ) > wk->form ){
			D_PokeIconChg( wk, i );
			flg = 1;
		}
	}
	if( flg == 0 ){ wk->form = old; }
}

// 文字列表示
static void D_PokeIconStrPut( D_POKEICON * wk )
{
	NUMFONT * nfnt;
	MSGDATA_MANAGER * mman;
	WORDSET * wset;
	STRBUF * str;
	POKEMON_PARAM * pp;
	u32	i;

	GF_BGL_BmpWinDataFill( &wk->win[0], 0 );
	GF_BGL_BmpWinDataFill( &wk->win[1], 0 );

	mman = MSGMAN_Create(
			MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_nakahiro_dat, HEAPID_BASE_APP );
	nfnt = NUMFONT_Create( FBMP_COL_BLACK, FBMP_COL_BLK_SDW, FBMP_COL_NULL, HEAPID_BASE_APP );
	wset = WORDSET_Create( HEAPID_BASE_APP );
	str  = STRBUF_Create( 32, HEAPID_BASE_APP );
	pp   = PokemonParam_AllocWork( HEAPID_BASE_APP );

	for( i=0; i<PICON_MAX; i++ ){
		GF_BGL_BMPWIN * win;
		u16	mons;
		u16	py;

		mons = wk->page*PICON_MAX+i;
		if( mons > MONSNO_END ){ break; }

		if( i < PICON_MAX/2 ){
			win = &wk->win[0];
			py = i*32;
		}else{
			win = &wk->win[1];
			py = (i-(PICON_MAX/2))*32;
		}
		NUMFONT_WriteNumber( nfnt, mons, 3, NUMFONT_MODE_ZERO, win, 0, py+21 );

		PokeParaSet( pp, mons, 1, POW_RND, RND_SET, 0, ID_SET, 0 );
		{
			STRBUF * tmp = MSGMAN_AllocString( mman, msg_pokeicon_name );
			WORDSET_RegisterPokeMonsName( wset, 0, PPPPointerGet(pp) );
			WORDSET_ExpandStr( wset, str, tmp );
			STRBUF_Delete( tmp );
		}
		GF_STR_PrintSimple( win, FONT_SYSTEM, str, 26, py+16, MSG_NO_PUT, NULL );
	}

	sys_FreeMemoryEz( pp );
	STRBUF_Delete( str );
	WORDSET_Delete( wset );
	NUMFONT_Delete( nfnt );
	MSGMAN_Delete( mman );

	GF_BGL_BmpWinOnVReq( &wk->win[0] );
	GF_BGL_BmpWinOnVReq( &wk->win[1] );
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクターセット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------

// セルアクターデータ
static const TCATS_OBJECT_ADD_PARAM_S ActAddParam_S[] =
{
	{	24, 16, 0,		1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID, DHN_CLA_ID, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	24, 16+32, 0,	1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+1, DHN_CLA_ID, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	24, 16+64, 0,	1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+2, DHN_CLA_ID, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	24, 16+96, 0,	1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+3, DHN_CLA_ID, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	24, 16+128, 0,	1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+4, DHN_CLA_ID, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	24, 16+160, 0,	1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+5, DHN_CLA_ID, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},

	{	144, 16, 0,		1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+6, DHN_CLA_ID, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	144, 16+32, 0,	1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+7, DHN_CLA_ID, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	144, 16+64, 0,	1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+8, DHN_CLA_ID, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	144, 16+96, 0,	1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+9, DHN_CLA_ID, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	144, 16+128, 0,	1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+10, DHN_CLA_ID, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	144, 16+160, 0,	1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+11, DHN_CLA_ID, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
};

static void CellActSet( D_POKEICON * wk )
{
	TCATS_RESOURCE_NUM_LIST	crnl = { PICON_MAX, 1, 1, 1, 0, 0 };
	u32	i;

	FieldCellActSet_S( &wk->fcat, &crnl, PICON_MAX, HEAPID_WORLD );

	FldClact_LoadResPlttArc(
		&wk->fcat, ARC_POKEICON,
		PokeIconPalArcIndexGet(), 0, 3, NNS_G2D_VRAM_TYPE_2DMAIN, DHN_CLA_ID );

	FldClact_LoadResCellArc(
		&wk->fcat, ARC_POKEICON, PokeIconAnmCellArcIndexGet(), 0, DHN_CLA_ID );

	FldClact_LoadResCellAnmArc(
		&wk->fcat, ARC_POKEICON, PokeIconAnmCellAnmArcIndexGet(), 0, DHN_CLA_ID );

	for( i=0; i<PICON_MAX; i++ ){
		FldClact_LoadResourceCharArc(
			&wk->fcat, ARC_POKEICON,
			PokeIconCgxArcIndexGetByMonsNumber(0,0,0), 0, NNS_G2D_VRAM_TYPE_2DMAIN, DHN_CLA_ID+i );
		wk->cap[i] = FieldCellActAdd_S( &wk->fcat, &ActAddParam_S[i] );
	}

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクター削除
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CellActDelete( D_POKEICON * wk )
{
	u16	i;

	for( i=0; i<PICON_MAX; i++ ){
		CATS_ActorPointerDelete_S( wk->cap[i] );
	}
	FieldCellActDelete_S( &wk->fcat );
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクターアニメ
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CellActAnm( D_POKEICON * wk )
{
	u16	i;

	for( i=0; i<PICON_MAX; i++ ){
		CLACT_AnmFrameChg( wk->cap[i]->act, FX32_ONE );
	}
}




//============================================================================================
//============================================================================================
//	アイテムアイコンチェック
//============================================================================================
//============================================================================================
static void D_ItemIconChgAll( D_POKEICON * wk );
static void D_ItemIconChg( D_POKEICON * wk, u8 pos );
static void D_ItemIconStrPut( D_POKEICON * wk );

static void D_ItemIconCheckMain( TCB_PTR _tcb, void * work );
static void D_ItemIconCellActSet( D_POKEICON * wk );

// 初期化
static void DebugItemIconCheckInit( void * fsys )
{
	D_POKEICON * wk;
	GF_BGL_INI * bgl;

	bgl = FieldBglIniGet( fsys );

	wk = (D_POKEICON *)TCB_GetWork(
				PMDS_taskAdd( D_ItemIconCheckMain, sizeof(D_POKEICON), 0, HEAPID_BASE_APP ) );

	wk->fsys = fsys;
	wk->page = 0;
	wk->mode = 0;
	wk->form = 0;

	GF_BGL_BmpWinAdd( bgl, &wk->win[0], FLD_MBGFRM_FONT,  3, 0, 13, 24, 13, 1 );
	GF_BGL_BmpWinAdd( bgl, &wk->win[1], FLD_MBGFRM_FONT, 19, 0, 13, 24, 13, 1+13*24 );

	D_ItemIconCellActSet( wk );
	D_ItemIconChgAll( wk );
	D_ItemIconStrPut( wk );

	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, 0x7fff );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
}

// メイン処理
static void D_ItemIconCheckMain( TCB_PTR _tcb, void * work )
{
	D_POKEICON * wk = (D_POKEICON *)work;

	if( sys.trg & PAD_KEY_UP ){
		if( wk->page != 0 ){
			wk->page--;
			wk->form = 0;
			D_ItemIconChgAll( wk );
			D_ItemIconStrPut( wk );
		}
	}else if( sys.trg & PAD_KEY_DOWN ){
		if( wk->page < (ITEM_DATA_MAX/PICON_MAX) ){
			wk->page++;
			wk->form = 0;
			D_ItemIconChgAll( wk );
			D_ItemIconStrPut( wk );
		}
	}else if( sys.trg & PAD_KEY_LEFT ){
		if( wk->page >= 10 ){
			wk->page -= 10;
		}else{
			wk->page = 0;
		}
		wk->form = 0;
		D_ItemIconChgAll( wk );
		D_ItemIconStrPut( wk );
	}else if( sys.trg & PAD_KEY_RIGHT ){
		wk->page += 10;
		if( wk->page > (ITEM_DATA_MAX/PICON_MAX) ){
			wk->page = (ITEM_DATA_MAX/PICON_MAX);
		}
		wk->form = 0;
		D_ItemIconChgAll( wk );
		D_ItemIconStrPut( wk );
	}else if( sys.trg & PAD_BUTTON_B ){
		CellActDelete( wk );
		GF_BGL_BmpWinOff( &wk->win[0] );
		GF_BGL_BmpWinOff( &wk->win[1] );
		GF_BGL_BmpWinDel( &wk->win[0] );
		GF_BGL_BmpWinDel( &wk->win[1] );
		PMDS_taskDel( _tcb );
		GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, 0 );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
		FieldSystemProc_SeqHoldEnd();
		return;
	}

	CLACT_Draw( wk->fcat.cas );
}

static void D_ItemIconChgAll( D_POKEICON * wk )
{
	u32	i;

	for( i=0; i<PICON_MAX; i++ ){
		D_ItemIconChg( wk, (u8)i );
	}
}

static void D_ItemIconChg( D_POKEICON * wk, u8 pos )
{
	u16	item;

	item = wk->page * PICON_MAX + pos;
	if( item > ITEM_DATA_MAX ){ item = 0; }

	FldClact_ChangeResourceCharArc(
		&wk->fcat, ARC_ITEMICON,
		GetItemIndex(item,ITEM_GET_ICON_CGX), 0, DHN_CLA_ID+pos );
	FldClact_ChangeResourcePlttArc(
		&wk->fcat, ARC_ITEMICON,
		GetItemIndex(item,ITEM_GET_ICON_PAL), 0, DHN_CLA_ID+pos );
}

// 文字列表示
static void D_ItemIconStrPut( D_POKEICON * wk )
{
	NUMFONT * nfnt;
	MSGDATA_MANAGER * mman;
	WORDSET * wset;
	STRBUF * str;
	u32	i;

	GF_BGL_BmpWinDataFill( &wk->win[0], 0 );
	GF_BGL_BmpWinDataFill( &wk->win[1], 0 );

	mman = MSGMAN_Create(
			MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_nakahiro_dat, HEAPID_BASE_APP );
	nfnt = NUMFONT_Create( FBMP_COL_BLACK, FBMP_COL_BLK_SDW, FBMP_COL_NULL, HEAPID_BASE_APP );
	wset = WORDSET_Create( HEAPID_BASE_APP );
	str  = STRBUF_Create( 32, HEAPID_BASE_APP );

	for( i=0; i<PICON_MAX; i++ ){
		GF_BGL_BMPWIN * win;
		u16	item;
		u16	py;

		item = wk->page*PICON_MAX+i;
		if( item > ITEM_DATA_MAX ){ break; }

		if( i < PICON_MAX/2 ){
			win = &wk->win[0];
			py = i*32;
		}else{
			win = &wk->win[1];
			py = (i-(PICON_MAX/2))*32;
		}
		NUMFONT_WriteNumber( nfnt, item, 3, NUMFONT_MODE_ZERO, win, 0, py+21 );

		{
			STRBUF * tmp = MSGMAN_AllocString( mman, msg_itemicon_name0002 );
			WORDSET_RegisterItemName( wset, 0, item );
			WORDSET_ExpandStr( wset, str, tmp );
			STRBUF_Delete( tmp );
		}
		GF_STR_PrintSimple( win, FONT_SYSTEM, str, 24, py+16, MSG_NO_PUT, NULL );
	}

	STRBUF_Delete( str );
	WORDSET_Delete( wset );
	NUMFONT_Delete( nfnt );
	MSGMAN_Delete( mman );

	GF_BGL_BmpWinOnVReq( &wk->win[0] );
	GF_BGL_BmpWinOnVReq( &wk->win[1] );
}

// セルアクターデータ
static const TCATS_OBJECT_ADD_PARAM_S ItemIconActAddParam_S[] =
{
	{	16, 16+8, 0,		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID, DHN_CLA_ID, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	16, 16+32+8, 0,	0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+1, DHN_CLA_ID+1, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	16, 16+64+8, 0,	0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+2, DHN_CLA_ID+2, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	16, 16+96+8, 0,	0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+3, DHN_CLA_ID+3, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	16, 16+128+8, 0,	0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+4, DHN_CLA_ID+4, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	16, 16+160+8, 0,	0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+5, DHN_CLA_ID+5, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},

	{	144, 16+8, 0,		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+6, DHN_CLA_ID+6, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	144, 16+32+8, 0,	0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+7, DHN_CLA_ID+7, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	144, 16+64+8, 0,	0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+8, DHN_CLA_ID+8, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	144, 16+96+8, 0,	0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+9, DHN_CLA_ID+9, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	144, 16+128+8, 0,	0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+10, DHN_CLA_ID+10, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
	{	144, 16+160+8, 0,	0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ DHN_CLA_ID+11, DHN_CLA_ID+11, DHN_CLA_ID, DHN_CLA_ID, 0, 0 },	0, 0	},
};

static void D_ItemIconCellActSet( D_POKEICON * wk )
{
	TCATS_RESOURCE_NUM_LIST	crnl = { PICON_MAX, PICON_MAX, 1, 1, 0, 0 };
	u32	i;

	FieldCellActSet_S( &wk->fcat, &crnl, PICON_MAX, HEAPID_WORLD );

	FldClact_LoadResCellArc( &wk->fcat, ARC_ITEMICON, ItemIconCellGet(), 0, DHN_CLA_ID );

	FldClact_LoadResCellAnmArc( &wk->fcat, ARC_ITEMICON, ItemIconCAnmGet(), 0, DHN_CLA_ID );

	for( i=0; i<PICON_MAX; i++ ){
		FldClact_LoadResourceCharArc(
			&wk->fcat, ARC_ITEMICON,
			GetItemIndex(0,ITEM_GET_ICON_CGX), 0, NNS_G2D_VRAM_TYPE_2DMAIN, DHN_CLA_ID+i );
		FldClact_LoadResPlttArc(
			&wk->fcat, ARC_ITEMICON,
			GetItemIndex(0,ITEM_GET_ICON_PAL), 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, DHN_CLA_ID+i );
		wk->cap[i] = FieldCellActAdd_S( &wk->fcat, &ItemIconActAddParam_S[i] );
	}

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}











//============================================================================================
//============================================================================================
//	どうぐをつくる
//============================================================================================
//============================================================================================
typedef struct {
	FIELDSYS_WORK * fsys;
	GF_BGL_BMPWIN	win;
	MINEITEM	item;
	u32	seq;
}D_ITEMMAKE;

static void D_ItemMakeMain( TCB_PTR _tcb, void * work );
static void D_ItemMakeBmpExit( D_ITEMMAKE * wk );
static void D_ItemStrPut( D_ITEMMAKE * wk );
static u8 D_ItemIDSel( D_ITEMMAKE * wk );
static u8 D_ItemNumSel( D_ITEMMAKE * wk );


// 初期化
void DebugItemMakeInit( void * fsys )
{
	D_ITEMMAKE * wk;
	GF_BGL_INI * bgl;

	bgl = FieldBglIniGet( fsys );

	wk = (D_ITEMMAKE *)TCB_GetWork(
				PMDS_taskAdd( D_ItemMakeMain, sizeof(D_ITEMMAKE), 0, HEAPID_BASE_APP ) );

	wk->fsys = fsys;
	wk->seq  = 0;
	wk->item.id = 1;
	wk->item.no = 1;
	GF_BGL_BmpWinAdd( bgl, &wk->win, FLD_MBGFRM_FONT, 1, 19, 30, 4, 13, 1 );

	MenuWinGraphicSet(
		bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_BASE_APP );
	BmpMenuWinWrite( &wk->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );

	D_ItemStrPut( wk );
}

// 文字列表示
static void D_ItemStrPut( D_ITEMMAKE * wk )
{
	GF_BGL_BMPWIN * win;
	MSGDATA_MANAGER * mman;
	WORDSET * wset;
	STRBUF * expb;
	STRBUF * strb;

	win = &wk->win;
	GF_BGL_BmpWinDataFill( win, 15 );

	mman = MSGMAN_Create(
				MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_debug_nakahiro_dat, HEAPID_BASE_APP );
	wset = WORDSET_Create( HEAPID_BASE_APP );
	expb = STRBUF_Create( 64, HEAPID_BASE_APP );

	strb = MSGMAN_AllocString( mman, msg_itemmake_02 );
	WORDSET_RegisterNumber( wset, 0, wk->item.id, 3, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wset, expb, strb );
	if( wk->seq == 0 ){
		GF_STR_PrintColor( win, FONT_SYSTEM, expb, 32, 8, MSG_NO_PUT, COL_W_RED, NULL );
	}else{
		GF_STR_PrintColor( win, FONT_SYSTEM, expb, 32, 8, MSG_NO_PUT, COL_W_BLACK, NULL );
	}
	STRBUF_Delete( strb );

	strb = MSGMAN_AllocString( mman, msg_itemmake_01 );
	WORDSET_RegisterItemName( wset, 0, wk->item.id );
	WORDSET_ExpandStr( wset, expb, strb );
	if( wk->seq == 0 ){
		GF_STR_PrintColor( win, FONT_SYSTEM, expb, 64, 8, MSG_NO_PUT, COL_W_RED, NULL );
	}else{
		GF_STR_PrintColor( win, FONT_SYSTEM, expb, 64, 8, MSG_NO_PUT, COL_W_BLACK, NULL );
	}
	STRBUF_Delete( strb );

	strb = MSGMAN_AllocString( mman, msg_itemmake_00 );
	GF_STR_PrintColor( win, FONT_SYSTEM, strb, 176, 8, MSG_NO_PUT, COL_W_BLACK, NULL );
	STRBUF_Delete( strb );
	strb = MSGMAN_AllocString( mman, msg_itemmake_02 );
	WORDSET_RegisterNumber( wset, 0, wk->item.no, 3, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wset, expb, strb );
	if( wk->seq == 1 ){
		GF_STR_PrintColor( win, FONT_SYSTEM, expb, 188, 8, MSG_ALLPUT, COL_W_RED, NULL );
	}else{
		GF_STR_PrintColor( win, FONT_SYSTEM, expb, 188, 8, MSG_ALLPUT, COL_W_BLACK, NULL );
	}
	STRBUF_Delete( strb );

	STRBUF_Delete( expb );
	MSGMAN_Delete( mman );
	WORDSET_Delete( wset );
}

// メイン処理
static void D_ItemMakeMain( TCB_PTR _tcb, void * work )
{
	D_ITEMMAKE * wk = (D_ITEMMAKE *)work;

	switch( wk->seq ){
	case 0:		// アイテム選択
		if( D_ItemIDSel( wk ) == TRUE ){
			D_ItemMakeBmpExit( wk );
			PMDS_taskDel( _tcb );
			FieldSystemProc_SeqHoldEnd();
		}
		break;
	case 1:
		if( D_ItemNumSel( wk ) == TRUE ){
			wk->seq = 0;
		}
		break;
	}
}

// ID変更
static void D_ItemIDSet( D_ITEMMAKE * wk, s8 plus )
{
	s16	id = wk->item.id;

	id += plus;

	if( id <= 0 ){
		wk->item.id = ITEM_DATA_MAX;
	}else if( id > ITEM_DATA_MAX ){
		wk->item.id = 1;
	}else{
		wk->item.id = id;
	}
}

// ID変更処理
static u8 D_ItemIDSel( D_ITEMMAKE * wk )
{
	if( sys.repeat & PAD_KEY_UP ){
		D_ItemIDSet( wk, 1 );
		D_ItemStrPut( wk );
		return FALSE;
	}
	if( sys.repeat & PAD_KEY_DOWN ){
		D_ItemIDSet( wk, -1 );
		D_ItemStrPut( wk );
		return FALSE;
	}
	if( sys.repeat & PAD_KEY_LEFT ){
		D_ItemIDSet( wk, -10 );
		D_ItemStrPut( wk );
		return FALSE;
	}
	if( sys.repeat & PAD_KEY_RIGHT ){
		D_ItemIDSet( wk, 10 );
		D_ItemStrPut( wk );
		return FALSE;
	}

	if( sys.trg & PAD_BUTTON_A ){
		wk->seq = 1;
		D_ItemStrPut( wk );
		return FALSE;
	}

	if( sys.trg & PAD_BUTTON_B ){
		return TRUE;
	}

	return FALSE;
}

// 個数変更
static void D_ItemNumSet( D_ITEMMAKE * wk, s8 plus )
{
	s16	num = wk->item.no;

	num += plus;

	if( num <= 0 ){
		wk->item.no = 999;
	}else if( num >= 1000 ){
		wk->item.no = 1;
	}else{
		wk->item.no = num;
	}
}

// 個数変更
static u8 D_ItemNumSel( D_ITEMMAKE * wk )
{
	if( sys.repeat & PAD_KEY_UP ){
		D_ItemNumSet( wk, 1 );
		D_ItemStrPut( wk );
		return FALSE;
	}
	if( sys.repeat & PAD_KEY_DOWN ){
		D_ItemNumSet( wk, -1 );
		D_ItemStrPut( wk );
		return FALSE;
	}
	if( sys.repeat & PAD_KEY_LEFT ){
		D_ItemNumSet( wk, -10 );
		D_ItemStrPut( wk );
		return FALSE;
	}
	if( sys.repeat & PAD_KEY_RIGHT ){
		D_ItemNumSet( wk, 10 );
		D_ItemStrPut( wk );
		return FALSE;
	}

	if( sys.trg & PAD_BUTTON_A ){
		wk->seq = 0;
		MyItem_AddItem(
			SaveData_GetMyItem( wk->fsys->savedata ),
			wk->item.id, wk->item.no, HEAPID_BASE_APP );
		D_ItemStrPut( wk );
		return FALSE;
	}

	if( sys.trg & PAD_BUTTON_B ){
		wk->seq = 0;
		D_ItemStrPut( wk );
		return TRUE;
	}

	return FALSE;
}

static void D_ItemMakeBmpExit( D_ITEMMAKE * wk )
{
	BmpMenuWinClear( &wk->win, WINDOW_TRANS_ON );

	GF_BGL_BmpWinOff( &wk->win );
	GF_BGL_BmpWinDel( &wk->win );
}



//============================================================================================
//============================================================================================
//	ポケモンをつくる
//============================================================================================
//============================================================================================
typedef struct {
	POKEMON_PARAM * PokeMakeData;
	u32	PMD[64];
	u32	data_bak;

	u16	str[0x100];

	u8	page_p;
	u8	cursor_p;
	u8	value_p;
}PokeMakeWork;

typedef struct {
	u32	min;
	u32	max;
	u8	mode;
	u8	count;
}PmakeCont;

typedef struct {
	u32 label;
	const PmakeCont * cont;
}PmakeParamData;

typedef struct {
	const u8 * page;
	u8	listcount;
}PmakePageTable;


#define	PMC_INCDEC		(0)
#define	PMC_INIT		(0)
#define	PMC_INC			(1)
#define	PMC_DEC			(2)


typedef struct {
	FIELDSYS_WORK * fsys;
	GF_BGL_BMPWIN	win;
	GF_BGL_BMPWIN	win_title;
	MSGDATA_MANAGER * mman;	// メッセージデータマネージャ
	WORDSET * wset;			// 単語セット
	BMPCURSOR * cursor;
	PokeMakeWork	pmw;
	u32	seq;
	u32	mode;
}D_POKEMONMAKE;


#define	PMAKE_NAME			( 0 )	//ポケモンナンバー（16bit）
#define	PMAKE_LEVEL			( 1 )	//レベル（8bit）
#define	PMAKE_EXP			( 2 )	//経験値（32bit）
#define	PMAKE_ID			( 3 )	//ＩＤ（32bit）
#define	PMAKE_PERRND		( 4 )	//個体乱数（32bit）
#define	PMAKE_SEX			( 5 )	//性別（8bit）
#define	PMAKE_PERSONAL		( 6 )	//性格（8bit）
#define	PMAKE_WAZA1			( 7 )	//持っている技１（8bit）
#define	PMAKE_WAZA2			( 8 )	//持っている技２（8bit）
#define	PMAKE_WAZA3			( 9 )	//持っている技３（8bit）
#define	PMAKE_WAZA4			( 10 )	//持っている技４（8bit）
#define	PMAKE_ITEM			( 11 )	//所持アイテム（8bit）
#define	PMAKE_SPABI			( 12 )	//特殊能力（1bit）
#define	PMAKE_HP_RND		( 13 )	//ＨＰ乱数（5bit）
#define	PMAKE_HP_EXP		( 14 )	//ＨＰ経験値（8bit）
#define	PMAKE_POW_RND		( 15 )	//こうげき乱数（5bit）
#define	PMAKE_POW_EXP		( 16 )	//こうげき経験値（8bit）
#define	PMAKE_DEF_RND		( 17 )	//ぼうぎょ乱数（5bit）
#define	PMAKE_DEF_EXP		( 18 )	//ぼうぎょ経験値（8bit）
#define	PMAKE_AGI_RND		( 19 )	//すばやさ乱数（5bit）
#define	PMAKE_AGI_EXP		( 20 )	//すばやさ経験値（8bit）
#define	PMAKE_EXPOW_RND		( 21 )	//特殊こうげき乱数（5bit）
#define	PMAKE_EXPOW_EXP		( 22 )	//特殊こうげき経験値（8bit）
#define	PMAKE_EXDEF_RND		( 23 )	//特殊ぼうぎょ乱数（5bit）
#define	PMAKE_EXDEF_EXP		( 24 )	//特殊ぼうぎょ経験値（8bit）
#define	PMAKE_STYLE			( 25 )	//かっこよさ（8bit）
#define	PMAKE_BEAUTIFUL		( 26 )	//うつくしさ（8bit）
#define	PMAKE_CUTE			( 27 )	//かわいさ（8bit）
#define	PMAKE_CLEVER		( 28 )	//かしこさ（8bit）
#define	PMAKE_STRONG		( 29 )	//たくましさ（8bit）
#define	PMAKE_FUR			( 30 )	//毛艶（8bit）
#define	PMAKE_FRIEND		( 31 )	//なつき度（8bit）
#define	PMAKE_POKERUS		( 32 )	//ポケルス（8bit）
#define	PMAKE_TAMAGO		( 33 )	//タマゴ状態フラグ（1bit）
#define	PMAKE_CONDITION		( 34 )	//からだの状態（32bit）
#define	PMAKE_HP			( 35 )	//ＨＰ
#define	PMAKE_POW			( 36 )	//こうげき
#define	PMAKE_DEF			( 37 )	//ぼうぎょ
#define	PMAKE_AGI			( 38 )	//すばやさ
#define	PMAKE_EXPOW			( 39 )	//特殊こうげき
#define	PMAKE_EXDEF			( 40 )	//特殊ぼうぎょ
#define	PMAKE_EVGET			( 41 )	//イベント配布ビット（1bit）
#define	PMAKE_GETPLACE		( 42 )	//捕獲場所（10bit）
#define	PMAKE_GETLEVEL		( 43 )	//捕獲レベル（7bit）
#define	PMAKE_GETCASSETTE	( 44 )	//捕獲カセット（4bit）
#define	PMAKE_GETBALL		( 45 )	//捕獲ボール（8bit）
#define	PMAKE_CONTRY_CODE	( 46 )	//国コード（8bit）
#define	PMAKE_FORM_NO		( 47 )	//フォルムNo（8bit）

#define PMAKE_BATTLEPARAM1	( 0xfe )
#define PMAKE_BATTLEPARAM2	( 0xfd )

static const PmakeCont	cont00		= {1,MONSNO_TAMAGO-1,PMC_INCDEC,3};
static const PmakeCont	cont01		= {1,100,PMC_INCDEC,3};
static const PmakeCont	cont02		= {1,2000000,PMC_INCDEC,7};
static const PmakeCont	cont03		= {0,0xffffffff,PMC_INCDEC,10};
static const PmakeCont	cont04		= {0,0xffffffff,PMC_INCDEC,10};
static const PmakeCont	cont05		= {0,2,PMC_INCDEC,0xff};
static const PmakeCont	cont06		= {0,24,PMC_INCDEC,0xff};
static const PmakeCont	cont07		= {0,WAZANO_MAX,PMC_INCDEC,3};
static const PmakeCont	cont08		= {0,WAZANO_MAX,PMC_INCDEC,3};
static const PmakeCont	cont09		= {0,WAZANO_MAX,PMC_INCDEC,3};
static const PmakeCont	cont10		= {0,WAZANO_MAX,PMC_INCDEC,3};
static const PmakeCont	cont11		= {0,ITEM_DATA_MAX,PMC_INCDEC,3};
static const PmakeCont	cont12		= {0,1,PMC_INCDEC,0xff};
static const PmakeCont	cont13		= {0,0x1f,PMC_INCDEC,2};
static const PmakeCont	cont14		= {0,255,PMC_INCDEC,3};
static const PmakeCont	cont15		= {0,0x1f,PMC_INCDEC,2};
static const PmakeCont	cont16		= {0,255,PMC_INCDEC,3};
static const PmakeCont	cont17		= {0,0x1f,PMC_INCDEC,2};
static const PmakeCont	cont18		= {0,255,PMC_INCDEC,3};
static const PmakeCont	cont19		= {0,0x1f,PMC_INCDEC,2};
static const PmakeCont	cont20		= {0,255,PMC_INCDEC,3};
static const PmakeCont	cont21		= {0,0x1f,PMC_INCDEC,2};
static const PmakeCont	cont22		= {0,255,PMC_INCDEC,3};
static const PmakeCont	cont23		= {0,0x1f,PMC_INCDEC,2};
static const PmakeCont	cont24		= {0,255,PMC_INCDEC,3};
static const PmakeCont	cont25		= {0,255,PMC_INCDEC,3};
static const PmakeCont	cont26		= {0,255,PMC_INCDEC,3};
static const PmakeCont	cont27		= {0,255,PMC_INCDEC,3};
static const PmakeCont	cont28		= {0,255,PMC_INCDEC,3};
static const PmakeCont	cont29		= {0,255,PMC_INCDEC,3};
static const PmakeCont	cont30		= {0,255,PMC_INCDEC,3};
static const PmakeCont	cont31		= {0,255,PMC_INCDEC,3};
static const PmakeCont	cont32		= {0,255,PMC_INCDEC,3};
static const PmakeCont	cont33		= {0,1,PMC_INCDEC,0xff};
static const PmakeCont	cont34		= {0,6,PMC_INCDEC,0xff};
static const PmakeCont	cont41		= {0,1,PMC_INCDEC,0xff};
static const PmakeCont	cont42		= {0,9999,PMC_INCDEC,4};
static const PmakeCont	cont43		= {0,100,PMC_INCDEC,3};
static const PmakeCont	cont44		= {1,15,PMC_INCDEC,2};
static const PmakeCont	cont45		= {1,16,PMC_INCDEC,2};
static const PmakeCont	cont46		= {1,7,PMC_INCDEC,1};
static const PmakeCont	cont47		= {0,255,PMC_INCDEC,3};

static const PmakeParamData	PMakelabelTable[] =
{
	{msg_pmlabel_00,&cont00}, {msg_pmlabel_01,&cont01}, {msg_pmlabel_02,&cont02}, {msg_pmlabel_03,&cont03},
	{msg_pmlabel_04,&cont04}, {msg_pmlabel_05,&cont05}, {msg_pmlabel_06,&cont06}, {msg_pmlabel_07,&cont07},
	{msg_pmlabel_08,&cont08}, {msg_pmlabel_09,&cont09}, {msg_pmlabel_10,&cont10}, {msg_pmlabel_11,&cont11},
	{msg_pmlabel_12,&cont12}, {msg_pmlabel_13,&cont13}, {msg_pmlabel_14,&cont14}, {msg_pmlabel_15,&cont15},
	{msg_pmlabel_16,&cont16}, {msg_pmlabel_17,&cont17}, {msg_pmlabel_18,&cont18}, {msg_pmlabel_19,&cont19},
	{msg_pmlabel_20,&cont20}, {msg_pmlabel_21,&cont21}, {msg_pmlabel_22,&cont22}, {msg_pmlabel_23,&cont23},
	{msg_pmlabel_24,&cont24}, {msg_pmlabel_25,&cont25}, {msg_pmlabel_26,&cont26}, {msg_pmlabel_27,&cont27},
	{msg_pmlabel_28,&cont28}, {msg_pmlabel_29,&cont29}, {msg_pmlabel_30,&cont30}, {msg_pmlabel_31,&cont31},
	{msg_pmlabel_32,&cont32}, {msg_pmlabel_33,&cont33}, {msg_pmlabel_34,&cont34}, {msg_pmlabel_35,&cont00},
	{msg_pmlabel_36,&cont00}, {msg_pmlabel_37,&cont00}, {msg_pmlabel_38,&cont00}, {msg_pmlabel_39,&cont00},
	{msg_pmlabel_40,&cont00}, {msg_pmlabel_41,&cont41}, {msg_pmlabel_42,&cont42}, {msg_pmlabel_43,&cont43},
	{msg_pmlabel_44,&cont44}, {msg_pmlabel_45,&cont45}, {msg_pmlabel_46,&cont46}, {msg_pmlabel_47,&cont47},
};

static const u32 CondTable[][2] =
{
	{ msg_pmcnname_01, 0x00000000 },	// 通常
	{ msg_pmcnname_02, 0x00000001 },	// 眠り		( 0x00000007 )
	{ msg_pmcnname_03, 0x00000008 },	// 毒		( 0x00000008 )
	{ msg_pmcnname_04, 0x00000010 },	// やけど	( 0x00000010 )
	{ msg_pmcnname_05, 0x00000020 },	// こおり	( 0x00000020 )
	{ msg_pmcnname_06, 0x00000040 },	// まひ		( 0x00000040 )
	{ msg_pmcnname_07, 0x00000080 },	// どくどく	( 0x00000080 )
};


static const u8 Page1[] = {
	PMAKE_NAME, PMAKE_LEVEL, PMAKE_EXP, PMAKE_ID,
	PMAKE_PERRND, PMAKE_SEX, PMAKE_PERSONAL, 0xff
};
static const u8 Page2[] = {
	PMAKE_CONDITION, PMAKE_FRIEND, PMAKE_POKERUS,
	PMAKE_TAMAGO, PMAKE_EVGET, 0xff
};
static const u8 Page3[] = {
	PMAKE_WAZA1, PMAKE_WAZA2, PMAKE_WAZA3,
	PMAKE_WAZA4, PMAKE_ITEM, PMAKE_SPABI, 0xff
};
static const u8 Page4[] = {
	PMAKE_HP_RND, PMAKE_HP_EXP, PMAKE_POW_RND, PMAKE_POW_EXP,
	PMAKE_DEF_RND, PMAKE_DEF_EXP, PMAKE_BATTLEPARAM1, 0xff
};
static const u8 Page5[] = {
	PMAKE_AGI_RND, PMAKE_AGI_EXP, PMAKE_EXPOW_RND, PMAKE_EXPOW_EXP,
	PMAKE_EXDEF_RND, PMAKE_EXDEF_EXP, PMAKE_BATTLEPARAM2, 0xff
};
static const u8 Page6[] = {
	PMAKE_STYLE, PMAKE_BEAUTIFUL, PMAKE_CUTE,
	PMAKE_CLEVER, PMAKE_STRONG, PMAKE_FUR, 0xff
};
static const u8 Page7[] = {
	PMAKE_GETPLACE, PMAKE_GETLEVEL, PMAKE_GETCASSETTE,
	PMAKE_GETBALL, PMAKE_CONTRY_CODE, PMAKE_FORM_NO, 0xff
};

#define	PMAKE_PAGE_MAX	(7)
static const PmakePageTable PageTable[] =
{
	{ Page1,5}, {Page2,5},
	{ Page3,6}, {Page4,6},
	{ Page5,6}, {Page6,6},
	{ Page7,6}
};




static void D_PokemonMakeMain( TCB_PTR _tcb, void * work );
static void PokeMakeSeq_PagePut( D_POKEMONMAKE * wk );
static void	PokeMakeSeq_ParamSelect( D_POKEMONMAKE * wk );
static void	PokeMakeSeq_ParamChange( D_POKEMONMAKE * wk );
static void	PokeMakeSeq_ButtonWait( D_POKEMONMAKE * wk );

static void PmakeExitTaskSeq( D_POKEMONMAKE * wk );
static void D_PokemonMakeStrPut( D_POKEMONMAKE * wk );

static void PokeMakeInit( D_POKEMONMAKE * wk );
static u8 PokeMakeCopy( D_POKEMONMAKE * wk );
static void PokeMakeWorkInit( PokeMakeWork * dpw );
static void PokeMakePokeParaCalcInit( PokeMakeWork * dpw );
static void PokeMakePokeParaCalcGetExp( PokeMakeWork * dpw );
static void PokeMakePokeParaCalcGetBattleParam( PokeMakeWork * dpw );
static void PokeMakePokeParaCalcEnd( D_POKEMONMAKE * wk, PokeMakeWork * dpw );
static void D_PokeWazaSetPos( POKEMON_PARAM * pp, u16 waza, u16 pos );
static void ValueControl( PokeMakeWork * dpw, u8 mode );
static void CursorPut( D_POKEMONMAKE * wk, u8 mode );
static void PagePut( D_POKEMONMAKE * wk );
static void PageValuePut( D_POKEMONMAKE * wk );
static void NumPutBuffer( PokeMakeWork * dpw, u16 * buf, u32 num, u8 cnt, u8 pal );
static void WazaNameGet( u16 * buf, u16 waza );
static void SeikakuStrGet( u16 * buf, u16 num );
static void TokuseiStrGet( u16 * buf, u16 mons, u16 num );
static void PokeMake_StrPrint(
			GF_BGL_BMPWIN * win, MSGDATA_MANAGER * man, u32 id, u32 x, u32 y, u32 wait, u32 col );
static void PokeMake_StrPrintExp(
			GF_BGL_BMPWIN * win, MSGDATA_MANAGER * man, WORDSET * wset,
			u32 id, u32 x, u32 y, u32 wait, u32 col );
static void PokeMake_NumPrint(
			GF_BGL_BMPWIN * win, MSGDATA_MANAGER * man, WORDSET * wset,
			PokeMakeWork * dpw, u32 num, u32 keta, u32 x, u32 y, u32 wait, u32 col );
static void PokeMake_MonsNamePut( GF_BGL_BMPWIN * win, u32 mons, u32 x, u32 y, u32 wait, u32 col );


static void PokeMakePokeParaWorkPutAll( PokeMakeWork * dpw );

// 初期化（ポケモンをつくる）
void DebugPokemonMakeInit( void * fsys )
{
	D_POKEMONMAKE * wk;
	GF_BGL_INI * bgl;

	bgl = FieldBglIniGet( fsys );

	wk = (D_POKEMONMAKE *)TCB_GetWork(
				PMDS_taskAdd( D_PokemonMakeMain, sizeof(D_POKEMONMAKE), 0, HEAPID_BASE_APP ) );

	wk->fsys = fsys;
	wk->seq  = 0;
	wk->mode = 0;

	wk->mman = MSGMAN_Create(
				MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_nakahiro_dat, HEAPID_BASE_APP );
	wk->wset = WORDSET_Create( HEAPID_BASE_APP );
	wk->cursor = BMPCURSOR_Create( HEAPID_BASE_APP );

	GF_BGL_BmpWinAdd( bgl, &wk->win_title, FLD_MBGFRM_FONT, 1, 1, 30, 4, 13, 1 );
	GF_BGL_BmpWinAdd( bgl, &wk->win, FLD_MBGFRM_FONT, 1, 7, 30, 16, 13, 1+30*4 );

	MenuWinGraphicSet(
		bgl, FLD_MBGFRM_FONT, 1+30*4+30*18, MENU_WIN_PAL, 0, HEAPID_BASE_APP );
	BmpMenuWinWrite( &wk->win_title, WINDOW_TRANS_OFF, 1+30*4+30*18, MENU_WIN_PAL );
	BmpMenuWinWrite( &wk->win, WINDOW_TRANS_OFF, 1+30*4+30*18, MENU_WIN_PAL );

	PokeMakeInit( wk );
}

// 初期化（ポケモン書き換え）
void DebugPokemonChangeInit( void * fsys )
{
	D_POKEMONMAKE * wk;
	GF_BGL_INI * bgl;

	bgl = FieldBglIniGet( fsys );

	wk = (D_POKEMONMAKE *)TCB_GetWork(
				PMDS_taskAdd( D_PokemonMakeMain, sizeof(D_POKEMONMAKE), 0, HEAPID_BASE_APP ) );

	wk->fsys = fsys;
	wk->seq  = 0;
	wk->mode = 1;

	wk->mman = MSGMAN_Create(
				MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_nakahiro_dat, HEAPID_BASE_APP );
	wk->wset = WORDSET_Create( HEAPID_BASE_APP );
	wk->cursor = BMPCURSOR_Create( HEAPID_BASE_APP );

	GF_BGL_BmpWinAdd( bgl, &wk->win_title, FLD_MBGFRM_FONT, 1, 1, 30, 4, 13, 1 );
	GF_BGL_BmpWinAdd( bgl, &wk->win, FLD_MBGFRM_FONT, 1, 7, 30, 16, 13, 1+30*4 );

	MenuWinGraphicSet(
		bgl, FLD_MBGFRM_FONT, 1+30*4+30*18, MENU_WIN_PAL, 0, HEAPID_BASE_APP );
	BmpMenuWinWrite( &wk->win_title, WINDOW_TRANS_OFF, 1+30*4+30*18, MENU_WIN_PAL );
	BmpMenuWinWrite( &wk->win, WINDOW_TRANS_OFF, 1+30*4+30*18, MENU_WIN_PAL );

	PokeMakeInit( wk );
}




#include	"include/poketool/poke_memo.h"
#define	TRMEMO_MSGWRITE( msgdata ){													\
	if( msgdata.msg != NULL	){														\
		GF_STR_PrintColor( &wk->win, FONT_SYSTEM, msgdata.msg,						\
							8, (msgdata.line-1) * 16, MSG_ALLPUT, COL_W_BLACK, NULL );	\
	}																				\
}

static void D_PokemonTrainerMemoPut( D_POKEMONMAKE * wk, BOOL orner_flag )
{
	// ポケモンをつくる
	if( wk->mode == 0 ){
		PokeMakePokeParaCalcEnd( wk, &wk->pmw );
	// ポケモンかきかえ
	}else{
		PokeMakePokeParaWorkPutAll( &wk->pmw );
	}
	GF_BGL_BmpWinDataFill( &wk->win, 15 );
	{
		TRMEMO_DATA* trdata = 
			TrainerMemoGet( wk->pmw.PokeMakeData,orner_flag, HEAPID_BASE_APP );
	
		TRMEMO_MSGWRITE( trdata->character1 )
		TRMEMO_MSGWRITE( trdata->encount )
		TRMEMO_MSGWRITE( trdata->character2 )
		TRMEMO_MSGWRITE( trdata->palate )
		TRMEMO_MSGWRITE( trdata->eggstatus )

		TrainerMemoFree( trdata );
	}
}

/********************************************************************/
/*				基準ポケモン選択									*/
/********************************************************************/
// メイン処理
static void D_PokemonMakeMain( TCB_PTR _tcb, void * work )
{
	D_POKEMONMAKE * wk = (D_POKEMONMAKE *)work;

	switch( wk->seq ){
	case 0:	// ページ表示
		PokeMakeSeq_PagePut( wk );
		break;
	case 1:	// 項目選択
		PokeMakeSeq_ParamSelect( wk );
		break;
	case 2:	// 項目変更
		PokeMakeSeq_ParamChange( wk );
		break;
	case 3:	// ボタン入力待ち
		PokeMakeSeq_ButtonWait( wk );
		break;
	case 4:	// 終了処理
		PmakeExitTaskSeq( wk );
		PMDS_taskDel( _tcb );
		FieldSystemProc_SeqHoldEnd();
		break;
	case 5:	// トレーナーメモ
		if( sys.trg & ( PAD_BUTTON_X|PAD_BUTTON_Y) ){
			wk->seq = 0;
		}
		break;
	}
}

// スクリーン描画
static void PokeMakeSeq_PagePut( D_POKEMONMAKE * wk )
{
	PagePut( wk );
	CursorPut( wk, PMC_INIT );
	wk->seq = 1;
}

// 項目選択
static void	PokeMakeSeq_ParamSelect( D_POKEMONMAKE * wk )
{
	u8	ret;

	if( sys.trg & PAD_BUTTON_A ){
		//変更
		wk->pmw.data_bak = wk->pmw.PMD[ PageTable[wk->pmw.page_p].page[wk->pmw.cursor_p] ];
		wk->pmw.value_p = 0;
		PageValuePut( wk );
		wk->seq = 2;
		return;
	}

	if( sys.trg & PAD_BUTTON_B ){
		wk->seq = 4;
		return;
	}

	if( sys.trg & PAD_BUTTON_START ){
//		SePlay(SE_SELECT);
		// ポケモンをつくる
		if( wk->mode == 0 ){
			PokeMakePokeParaCalcEnd( wk, &wk->pmw );
		// ポケモンをかきかえる
		}else{
			PokeMakePokeParaWorkPutAll( &wk->pmw );
		}
		ret = PokeMakeCopy( wk );
		GF_BGL_BmpWinFill( &wk->win, 15, 24, 64, 30*8-24, 32 );
		if( ret == 1 ){
			PokeMake_StrPrint( &wk->win, wk->mman, msg_pminfo_01, 32, 72, MSG_ALLPUT, COL_W_BLACK );
		}else{
			PokeMake_StrPrint( &wk->win, wk->mman, msg_pminfo_00, 32, 72, MSG_ALLPUT, COL_W_BLACK );
		}
		wk->seq = 3;
		return;
	}

	if( sys.trg & PAD_KEY_UP ){
		CursorPut( wk, PMC_DEC );
		return;
	}

	if( sys.trg & PAD_KEY_DOWN ){
		CursorPut( wk, PMC_INC );
		return;
	}

	if( ( sys.trg & PAD_BUTTON_L ) && wk->pmw.page_p > 0 ){
		wk->pmw.page_p--;
		wk->pmw.cursor_p = 0;
		wk->seq = 0;
		return;
	}

	if( ( sys.trg & PAD_BUTTON_R ) && wk->pmw.page_p < PMAKE_PAGE_MAX-1 ){
		wk->pmw.page_p++;
		wk->pmw.cursor_p = 0;
		wk->seq = 0;
		return;
	}

	if( ( sys.trg & PAD_BUTTON_X ) ){
		D_PokemonTrainerMemoPut( wk, TRUE );
		wk->seq = 5;
		return;
	}
	if( ( sys.trg & PAD_BUTTON_Y ) ){
		D_PokemonTrainerMemoPut( wk, FALSE );
		wk->seq = 5;
		return;
	}
}

// 項目変更
static void	PokeMakeSeq_ParamChange( D_POKEMONMAKE * wk )
{
	u8	data_id;

	data_id = PageTable[wk->pmw.page_p].page[wk->pmw.cursor_p];

	if( sys.trg & PAD_BUTTON_A ){
		wk->seq = 0;
		return;
	}

	if( sys.trg & PAD_BUTTON_B ){
		wk->pmw.PMD[data_id] = wk->pmw.data_bak;
		wk->seq = 0;
		return;
	}

	if( sys.repeat & PAD_KEY_UP ){
		ValueControl( &wk->pmw, PMC_INC );
		PageValuePut( wk );
		return;
	}
	if( sys.repeat & PAD_KEY_DOWN ){
		ValueControl( &wk->pmw, PMC_DEC );
		PageValuePut( wk );
		return;
	}

	if( PMakelabelTable[data_id].cont->count != 0xff ){
		if( ( sys.trg & PAD_KEY_LEFT ) &&
			wk->pmw.value_p < PMakelabelTable[data_id].cont->count-1 ){

			wk->pmw.value_p++;
			PageValuePut( wk );
			return;
		}
		if( ( sys.trg & PAD_KEY_RIGHT ) && wk->pmw.value_p > 0 ){
			wk->pmw.value_p--;
			PageValuePut( wk );
			return;
		}
	}
}

// ボタン入力待ち
static void	PokeMakeSeq_ButtonWait( D_POKEMONMAKE * wk )
{
	if( sys.trg & PAD_BUTTON_A ){
		wk->seq = 0;
	}
}

// 終了処理
static void PmakeExitTaskSeq( D_POKEMONMAKE * wk )
{
	sys_FreeMemoryEz( wk->pmw.PokeMakeData );

	BmpMenuWinClear( &wk->win_title, WINDOW_TRANS_OFF );
	BmpMenuWinClear( &wk->win, WINDOW_TRANS_ON );

	GF_BGL_BmpWinOff( &wk->win_title );
	GF_BGL_BmpWinOff( &wk->win );
	GF_BGL_BmpWinDel( &wk->win_title );
	GF_BGL_BmpWinDel( &wk->win );

	MSGMAN_Delete( wk->mman );
	WORDSET_Delete( wk->wset );
	BMPCURSOR_Delete( wk->cursor );
}


/********************************************************************/
/*				初期化												*/
/********************************************************************/
static void PokeMakePokeParaWorkGetAll( PokeMakeWork * dpw );

static void PokeMakeInit( D_POKEMONMAKE * wk )
{
	GF_BGL_BmpWinDataFill( &wk->win_title, 15 );
	PokeMake_StrPrint( &wk->win_title, wk->mman, msg_pminfo_02, 0, 0, MSG_ALLPUT, COL_W_BLACK );

	wk->pmw.PokeMakeData = PokemonParam_AllocWork( HEAPID_BASE_APP );

	// ポケモンをつくる
	if( wk->mode == 0 ){
		PokeMakeWorkInit( &wk->pmw );
	// ポケモンをかきかえる
	}else{
		POKEPARTY* temoti = SaveData_GetTemotiPokemon( wk->fsys->savedata);
		POKEMON_PARAM* change_poke =  PokeParty_GetMemberPointer( temoti, 0 );

		MI_CpuCopy8( change_poke, wk->pmw.PokeMakeData, PokemonParam_GetWorkSize());

		PokeMakePokeParaWorkGetAll( &wk->pmw );
	}

	wk->pmw.page_p   = 0;
	wk->pmw.cursor_p = 0;
}

/********************************************************************/
/*				手持ちポケモンセット								*/
/********************************************************************/
static u8 PokeMakeCopy( D_POKEMONMAKE * wk )
{
	// ポケモンをつくる
	if( wk->mode == 0 ){

//		ZukanCheck(dpw->PMD[PMAKE_NAME],Z_SEE_SET);
//		ZukanCheck(dpw->PMD[PMAKE_NAME],Z_GET_SET);

		POKEPARTY * party = SaveData_GetTemotiPokemon( wk->fsys->savedata );

		if( PokeParty_Add( party, wk->pmw.PokeMakeData ) == TRUE ){
			return 0;
		}

		// 手持ちがいっぱいなので、ボックス転送
		BOXDAT_PutPokemon(
			SaveData_GetBoxData(wk->fsys->savedata), PPPPointerGet(wk->pmw.PokeMakeData) );
		return 1;

	// ポケモンをかきかえる
	}else{
		POKEPARTY* temoti = SaveData_GetTemotiPokemon(wk->fsys->savedata);

		// 名前に「タマゴ」セット
		if( wk->pmw.PMD[PMAKE_TAMAGO] ){
			STRBUF * strb;
			strb = MSGMAN_AllocString( wk->mman, msg_pmtname );
			PokeParaPut( wk->pmw.PokeMakeData, ID_PARA_nickname_buf, strb );
			STRBUF_Delete( strb );
		}
		// 親引継ぎ
		{
			POKEMON_PARAM * pp;
			STRBUF * str;
			u8	sex;
			
			pp  = PokeParty_GetMemberPointer( temoti, 0 );
//			str = STRBUF_Create( 16, HEAPID_BASE_APP );
//			PokeParaGet( pp, ID_PARA_oyaname_buf, str );
//			PokeParaPut( wk->pmw.PokeMakeData, ID_PARA_oyaname_buf, str );
//			STRBUF_Delete( str );
			// 親名に「デバッグポケ１」セット
			str = MSGMAN_AllocString( wk->mman, msg_pmdname );
			PokeParaPut( wk->pmw.PokeMakeData, ID_PARA_oyaname_buf, str );
			STRBUF_Delete( str );

			sex = PokeParaGet( pp, ID_PARA_oyasex, NULL );
			PokeParaPut( wk->pmw.PokeMakeData, ID_PARA_oyasex, &sex );
		}
		PokeParty_SetMemberData( temoti, 0, wk->pmw.PokeMakeData );
		return 0;
	}
	return 0;
}

/********************************************************************/
/*				作成データ初期化									*/
/********************************************************************/
static void PokeMakeWorkInit( PokeMakeWork * dpw )
{
	u16	i;

	for( i=0; i<64; i++ ){
		dpw->PMD[i]	= 0;
	}
	// ポケモンナンバー（作成中は全国図鑑ナンバー）
	dpw->PMD[ PMAKE_NAME ] = 1;	
	//ＩＤ
//	dpw->PMD[PMAKE_ID] = (myd->ID[0]<<0)|(myd->ID[1]<<8)|(myd->ID[2]<<16)|(myd->ID[3]<<24);
	dpw->PMD[ PMAKE_ID ] = 0;

	//個体乱数
	dpw->PMD[ PMAKE_PERRND ] = (gf_rand()<<16) | (gf_rand());
	//経験値＆レベル
	dpw->PMD[ PMAKE_LEVEL ]       = 1;	
	dpw->PMD[ PMAKE_EXP ]         = 1;	
	dpw->PMD[ PMAKE_GETPLACE ]    = 0;
	dpw->PMD[ PMAKE_GETLEVEL ]    = 1;
//	dpw->PMD[ PMAKE_GETCASSETTE ] = CasetteVersion;
	dpw->PMD[ PMAKE_GETCASSETTE ] = 1;
	dpw->PMD[ PMAKE_GETBALL ]     = 1;
	dpw->PMD[ PMAKE_CONTRY_CODE ] = 1;
	dpw->PMD[ PMAKE_FORM_NO ] = 0;
	//持っている技
	//コンテスト用パラメータ
	//戦闘用パラメータ
	//その他状態
	PokeMakePokeParaCalcInit( dpw );
}


/********************************************************************/
/*				データ計算											*/
/********************************************************************/
static void PokeMakePokeParaCalcInit( PokeMakeWork * dpw )
{
	u32	pow_rnd;

	pow_rnd = ( (dpw->PMD[PMAKE_HP_RND]&0x0000001f) << 0 )
			| ( (dpw->PMD[PMAKE_POW_RND]&0x0000001f) << 5 )
			| ( (dpw->PMD[PMAKE_DEF_RND]&0x0000001f) << 10 )
			| ( (dpw->PMD[PMAKE_AGI_RND]&0x0000001f) << 15 )
			| ( (dpw->PMD[PMAKE_EXPOW_RND]&0x0000001f) << 20 )
			| ( (dpw->PMD[PMAKE_EXDEF_RND]&0x0000001f) << 25 );

	PokeParaSet(
		dpw->PokeMakeData,
		dpw->PMD[PMAKE_NAME],
		dpw->PMD[PMAKE_LEVEL],
		pow_rnd,
		1, dpw->PMD[PMAKE_PERRND],
		1, dpw->PMD[PMAKE_ID] );

	dpw->PMD[ PMAKE_SEX ]      = PokeSexGet( dpw->PokeMakeData );
	dpw->PMD[ PMAKE_PERSONAL ] = PokeSeikakuGet( dpw->PokeMakeData );
	dpw->PMD[ PMAKE_WAZA1 ]    = PokeParaGet( dpw->PokeMakeData, ID_PARA_waza1, NULL );
	dpw->PMD[ PMAKE_WAZA2 ]    = PokeParaGet( dpw->PokeMakeData, ID_PARA_waza2, NULL );
	dpw->PMD[ PMAKE_WAZA3 ]    = PokeParaGet( dpw->PokeMakeData, ID_PARA_waza3, NULL );
	dpw->PMD[ PMAKE_WAZA4 ]    = PokeParaGet( dpw->PokeMakeData, ID_PARA_waza4, NULL );
	dpw->PMD[ PMAKE_EXP ]      = PokeParaGet( dpw->PokeMakeData, ID_PARA_exp, NULL );

	dpw->PMD[ PMAKE_HP ]       = PokeParaGet( dpw->PokeMakeData,ID_PARA_hpmax, NULL );
	dpw->PMD[ PMAKE_POW ]      = PokeParaGet( dpw->PokeMakeData,ID_PARA_pow, NULL );
	dpw->PMD[ PMAKE_DEF ]      = PokeParaGet( dpw->PokeMakeData,ID_PARA_def, NULL );
	dpw->PMD[ PMAKE_AGI ]      = PokeParaGet( dpw->PokeMakeData,ID_PARA_agi, NULL );
	dpw->PMD[ PMAKE_EXPOW ]    = PokeParaGet( dpw->PokeMakeData,ID_PARA_spepow, NULL );
	dpw->PMD[ PMAKE_EXDEF ]    = PokeParaGet( dpw->PokeMakeData,ID_PARA_spedef, NULL );
}

static void PokeMakePokeParaCalcGetExp( PokeMakeWork * dpw )
{
	u32	nulldata = 0;

	PokeParaPut( dpw->PokeMakeData, ID_PARA_exp, &dpw->PMD[PMAKE_EXP] );
	//技クリア
	PokeParaPut( dpw->PokeMakeData, ID_PARA_waza1, &nulldata );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_waza2, &nulldata );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_waza3, &nulldata );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_waza4, &nulldata );

	PokeParaCalc( dpw->PokeMakeData );
	PokeWazaOboe( dpw->PokeMakeData );

	dpw->PMD[ PMAKE_LEVEL ] = PokeParaGet( dpw->PokeMakeData, ID_PARA_level, NULL );
	dpw->PMD[ PMAKE_WAZA1 ] = PokeParaGet( dpw->PokeMakeData, ID_PARA_waza1, NULL );
	dpw->PMD[ PMAKE_WAZA2 ] = PokeParaGet( dpw->PokeMakeData, ID_PARA_waza2, NULL );
	dpw->PMD[ PMAKE_WAZA3 ] = PokeParaGet( dpw->PokeMakeData, ID_PARA_waza3, NULL );
	dpw->PMD[ PMAKE_WAZA4 ] = PokeParaGet( dpw->PokeMakeData, ID_PARA_waza4, NULL );

	dpw->PMD[ PMAKE_HP ]    = PokeParaGet( dpw->PokeMakeData, ID_PARA_hpmax, NULL );
	dpw->PMD[ PMAKE_POW ]   = PokeParaGet( dpw->PokeMakeData, ID_PARA_pow, NULL );
	dpw->PMD[ PMAKE_DEF ]   = PokeParaGet( dpw->PokeMakeData, ID_PARA_def, NULL );
	dpw->PMD[ PMAKE_AGI ]   = PokeParaGet( dpw->PokeMakeData, ID_PARA_agi, NULL );
	dpw->PMD[ PMAKE_EXPOW ] = PokeParaGet( dpw->PokeMakeData, ID_PARA_spepow, NULL );
	dpw->PMD[ PMAKE_EXDEF ] = PokeParaGet( dpw->PokeMakeData, ID_PARA_spedef, NULL );
}

static void PokeMakePokeParaCalcGetBattleParam( PokeMakeWork * dpw )
{
	PokeParaPut( dpw->PokeMakeData, ID_PARA_hp_rnd, &dpw->PMD[PMAKE_HP_RND] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_hp_exp, &dpw->PMD[PMAKE_HP_EXP] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_pow_rnd, &dpw->PMD[PMAKE_POW_RND] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_pow_exp, &dpw->PMD[PMAKE_POW_EXP] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_def_rnd, &dpw->PMD[PMAKE_DEF_RND] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_def_exp, &dpw->PMD[PMAKE_DEF_EXP] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_agi_rnd, &dpw->PMD[PMAKE_AGI_RND] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_agi_exp, &dpw->PMD[PMAKE_AGI_EXP] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_spepow_rnd, &dpw->PMD[PMAKE_EXPOW_RND] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_spepow_exp, &dpw->PMD[PMAKE_EXPOW_EXP] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_spedef_rnd, &dpw->PMD[PMAKE_EXDEF_RND] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_spedef_exp, &dpw->PMD[PMAKE_EXDEF_EXP] );

	PokeParaCalc( dpw->PokeMakeData );

	dpw->PMD[ PMAKE_HP ]    = PokeParaGet( dpw->PokeMakeData, ID_PARA_hpmax, NULL );
	dpw->PMD[ PMAKE_POW ]   = PokeParaGet( dpw->PokeMakeData, ID_PARA_pow, NULL );
	dpw->PMD[ PMAKE_DEF ]   = PokeParaGet( dpw->PokeMakeData, ID_PARA_def, NULL );
	dpw->PMD[ PMAKE_AGI ]   = PokeParaGet( dpw->PokeMakeData, ID_PARA_agi, NULL );
	dpw->PMD[ PMAKE_EXPOW ] = PokeParaGet( dpw->PokeMakeData, ID_PARA_spepow, NULL );
	dpw->PMD[ PMAKE_EXDEF ] = PokeParaGet( dpw->PokeMakeData, ID_PARA_spedef, NULL );
}

static void PokeMakePokeParaCalcEnd( D_POKEMONMAKE * wk, PokeMakeWork * dpw )
{
	u32	pow_rnd;
	u32	tmp;

	pow_rnd = ( (dpw->PMD[PMAKE_HP_RND]&0x0000001f) << 0 )
			| ( (dpw->PMD[PMAKE_POW_RND]&0x0000001f) << 5 )
			| ( (dpw->PMD[PMAKE_DEF_RND]&0x0000001f) << 10 )
			| ( (dpw->PMD[PMAKE_AGI_RND]&0x0000001f) << 15 )
			| ( (dpw->PMD[PMAKE_EXPOW_RND]&0x0000001f) << 20 )
			| ( (dpw->PMD[PMAKE_EXDEF_RND]&0x0000001f) << 25 );

	PokeParaSet(
		dpw->PokeMakeData,
		dpw->PMD[PMAKE_NAME],
		dpw->PMD[PMAKE_LEVEL],
		pow_rnd,
		1, dpw->PMD[PMAKE_PERRND],
		1, dpw->PMD[PMAKE_ID] );

	if( dpw->PMD[PMAKE_WAZA1] ){
		D_PokeWazaSetPos( dpw->PokeMakeData, dpw->PMD[PMAKE_WAZA1], 0 );
	}
	if( dpw->PMD[PMAKE_WAZA2] ){
		D_PokeWazaSetPos( dpw->PokeMakeData, dpw->PMD[PMAKE_WAZA2], 1 );
	}
	if( dpw->PMD[PMAKE_WAZA3] ){
		D_PokeWazaSetPos( dpw->PokeMakeData, dpw->PMD[PMAKE_WAZA3], 2 );
	}
	if( dpw->PMD[PMAKE_WAZA4] ){
		D_PokeWazaSetPos( dpw->PokeMakeData, dpw->PMD[PMAKE_WAZA4], 3 );
	}
	PokeParaPut( dpw->PokeMakeData, ID_PARA_exp, &dpw->PMD[PMAKE_EXP] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_hp_rnd, &dpw->PMD[PMAKE_HP_RND] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_hp_exp, &dpw->PMD[PMAKE_HP_EXP] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_pow_rnd, &dpw->PMD[PMAKE_POW_RND] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_pow_exp, &dpw->PMD[PMAKE_POW_EXP] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_def_rnd, &dpw->PMD[PMAKE_DEF_RND] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_def_exp, &dpw->PMD[PMAKE_DEF_EXP] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_agi_rnd, &dpw->PMD[PMAKE_AGI_RND] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_agi_exp, &dpw->PMD[PMAKE_AGI_EXP] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_spepow_rnd, &dpw->PMD[PMAKE_EXPOW_RND] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_spepow_exp, &dpw->PMD[PMAKE_EXPOW_EXP] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_spedef_rnd, &dpw->PMD[PMAKE_EXDEF_RND] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_spedef_exp, &dpw->PMD[PMAKE_EXDEF_EXP] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_style, &dpw->PMD[PMAKE_STYLE] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_beautiful, &dpw->PMD[PMAKE_BEAUTIFUL] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_cute, &dpw->PMD[PMAKE_CUTE] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_clever, &dpw->PMD[PMAKE_CLEVER] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_strong, &dpw->PMD[PMAKE_STRONG] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_fur, &dpw->PMD[PMAKE_FUR] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_friend, &dpw->PMD[PMAKE_FRIEND] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_pokerus, &dpw->PMD[PMAKE_POKERUS] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_item, &dpw->PMD[PMAKE_ITEM] );

	tmp = PokePersonalParaGet( dpw->PMD[PMAKE_NAME], ID_PER_speabi1+dpw->PMD[PMAKE_SPABI] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_speabino, &tmp );

	PokeParaPut( dpw->PokeMakeData, ID_PARA_event_get_flag, &dpw->PMD[PMAKE_EVGET] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_get_place, &dpw->PMD[PMAKE_GETPLACE] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_get_level, &dpw->PMD[PMAKE_GETLEVEL] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_get_cassette, &dpw->PMD[PMAKE_GETCASSETTE] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_get_ball, &dpw->PMD[PMAKE_GETBALL] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_country_code, &dpw->PMD[PMAKE_CONTRY_CODE] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_form_no, &dpw->PMD[PMAKE_FORM_NO] );
	PokeParaPut(
		dpw->PokeMakeData, ID_PARA_condition, &CondTable[ dpw->PMD[PMAKE_CONDITION] ][1] );

	PokeParaPut( dpw->PokeMakeData, ID_PARA_tamago_flag, &dpw->PMD[PMAKE_TAMAGO] );
	{
		STRBUF * strb;

		// 名前に「タマゴ」セット
		if( dpw->PMD[PMAKE_TAMAGO] ){
			strb = MSGMAN_AllocString( wk->mman, msg_pmtname );
			PokeParaPut( dpw->PokeMakeData, ID_PARA_nickname_buf, strb );
			STRBUF_Delete( strb );
		}
		// 親名に「デバッグポケ１」セット
		strb = MSGMAN_AllocString( wk->mman, msg_pmdname );
		PokeParaPut( dpw->PokeMakeData, ID_PARA_oyaname_buf, strb );
		STRBUF_Delete( strb );
	}

	PokeParaCalc( dpw->PokeMakeData );
}

static void D_PokeWazaSetPos( POKEMON_PARAM * pokeparam, u16 waza, u16 pos )
{
	u8	pp;

	pp = WT_WazaDataParaGet( waza, ID_WTD_pp );
	PokeParaPut( pokeparam, ID_PARA_waza1+pos, &waza );
	PokeParaPut( pokeparam, ID_PARA_pp1+pos, &pp );
}


/********************************************************************/
/*				各項目表示制御										*/
/*				各項目設定制御										*/
/********************************************************************/
//表示データ作成
static u8 putproc( D_POKEMONMAKE * wk, u8 id, u32 pal, u8 y )
{
	PokeMakeWork * dpw;
	u16	i;
	u8	vp,vpl;

	dpw = &wk->pmw;

	if( id == PMAKE_BATTLEPARAM1 ){
		PokeMake_StrPrint( &wk->win, wk->mman, msg_pmlabel_35, 12, y, MSG_NO_PUT, COL_W_GREEN );
		PokeMake_NumPrint(
			&wk->win, wk->mman, wk->wset, dpw,
			dpw->PMD[PMAKE_HP], 3, 12+24, y+16, MSG_NO_PUT, COL_W_BLACK );

		PokeMake_StrPrint( &wk->win, wk->mman, msg_pmlabel_36, 12+72, y, MSG_NO_PUT, COL_W_GREEN );
		PokeMake_NumPrint(
			&wk->win, wk->mman, wk->wset, dpw,
			dpw->PMD[PMAKE_POW], 3, 12+72+24, y+16, MSG_NO_PUT, COL_W_BLACK );

		PokeMake_StrPrint( &wk->win, wk->mman, msg_pmlabel_37, 12+72+72, y, MSG_NO_PUT, COL_W_GREEN );
		PokeMake_NumPrint(
			&wk->win, wk->mman, wk->wset, dpw,
			dpw->PMD[PMAKE_DEF], 3, 12+72+72+24, y+16, MSG_NO_PUT, COL_W_BLACK );
		return 0;
	}

	if(id == PMAKE_BATTLEPARAM2){
		PokeMake_StrPrint( &wk->win, wk->mman, msg_pmlabel_38, 12, y, MSG_NO_PUT, COL_W_GREEN );
		PokeMake_NumPrint(
			&wk->win, wk->mman, wk->wset, dpw,
			dpw->PMD[PMAKE_AGI], 3, 12+24, y+16, MSG_NO_PUT, COL_W_BLACK );

		PokeMake_StrPrint( &wk->win, wk->mman, msg_pmlabel_39, 12+72, y, MSG_NO_PUT, COL_W_GREEN );
		PokeMake_NumPrint(
			&wk->win, wk->mman, wk->wset, dpw,
			dpw->PMD[PMAKE_EXPOW], 3, 12+72+24, y+16, MSG_NO_PUT, COL_W_BLACK );

		PokeMake_StrPrint( &wk->win, wk->mman, msg_pmlabel_40, 12+72+72, y, MSG_NO_PUT, COL_W_GREEN );
		PokeMake_NumPrint(
			&wk->win, wk->mman, wk->wset, dpw,
			dpw->PMD[PMAKE_EXDEF], 3, 12+72+72+24, y+16, MSG_NO_PUT, COL_W_BLACK );
		return 0;
	}

	PokeMake_StrPrint( &wk->win, wk->mman, PMakelabelTable[id].label, 12, y, MSG_NO_PUT, pal );

	vp	= PMakelabelTable[id].cont->count;
	vpl = vp*4;

	switch( id ){
	case PMAKE_NAME:
		PokeMake_NumPrint(
			&wk->win, wk->mman, wk->wset, dpw, dpw->PMD[id], vp, 12+72+24, y, MSG_NO_PUT, pal );
		PokeMake_MonsNamePut( &wk->win, dpw->PMD[id], 12+72+24+32, y, MSG_NO_PUT, COL_W_BLACK );
		break;

	case PMAKE_SEX:
		switch(dpw->PMD[id]){
		case 0:	// オス
			PokeMake_StrPrint(
				&wk->win, wk->mman, msg_pmstr_01, 12+72+24, y, MSG_NO_PUT, COL_W_BLACK );
			break;
		case 1:	// メス
			PokeMake_StrPrint(
				&wk->win, wk->mman, msg_pmstr_02, 12+72+24, y, MSG_NO_PUT, COL_W_BLACK );
			break;
		case 2:	// なし
			PokeMake_StrPrint(
				&wk->win, wk->mman, msg_pmstr_00, 12+72+24, y, MSG_NO_PUT, COL_W_BLACK );
			break;
		}
		break;

	case PMAKE_WAZA1:
	case PMAKE_WAZA2:
	case PMAKE_WAZA3:
	case PMAKE_WAZA4:
		PokeMake_NumPrint(
			&wk->win, wk->mman, wk->wset, dpw, dpw->PMD[id], vp, 12+72+24, y, MSG_NO_PUT, pal );
		WORDSET_RegisterWazaName( wk->wset, 0, dpw->PMD[id] );
		PokeMake_StrPrintExp(
			&wk->win, wk->mman, wk->wset, msg_pmstr_08, 12+72+24+32, y, MSG_NO_PUT, pal );
		break;

	case PMAKE_ITEM:
		PokeMake_NumPrint(
			&wk->win, wk->mman, wk->wset, dpw, dpw->PMD[id], vp, 12+72+24, y, MSG_NO_PUT, pal );
		WORDSET_RegisterItemName( wk->wset, 0, dpw->PMD[id] );
		PokeMake_StrPrintExp(
			&wk->win, wk->mman, wk->wset, msg_pmstr_09, 12+72+24+32, y, MSG_NO_PUT, pal );
		break;

	case PMAKE_SPABI:
		WORDSET_RegisterTokuseiName(
			wk->wset, 0, PokePersonalParaGet(dpw->PMD[PMAKE_NAME],ID_PER_speabi1+dpw->PMD[id]) );
		PokeMake_StrPrintExp(
			&wk->win, wk->mman, wk->wset, msg_pmstr_10, 12+72+24, y, MSG_NO_PUT, pal );
		break;

	case PMAKE_CONDITION:
		PokeMake_StrPrint(
			&wk->win, wk->mman, CondTable[dpw->PMD[id]][0], 12+72+24, y, MSG_NO_PUT, COL_W_BLACK );
		break;

	case PMAKE_ID:
	case PMAKE_PERRND:
	case PMAKE_HP_RND:
	case PMAKE_POW_RND:
	case PMAKE_DEF_RND:
	case PMAKE_AGI_RND:
	case PMAKE_EXPOW_RND:
	case PMAKE_EXDEF_RND:
	case PMAKE_LEVEL:
	case PMAKE_HP_EXP:
	case PMAKE_POW_EXP:
	case PMAKE_DEF_EXP:
	case PMAKE_AGI_EXP:
	case PMAKE_EXPOW_EXP:
	case PMAKE_EXDEF_EXP:
	case PMAKE_STYLE:
	case PMAKE_BEAUTIFUL:
	case PMAKE_CUTE:
	case PMAKE_CLEVER:
	case PMAKE_STRONG:
	case PMAKE_FUR:
	case PMAKE_FRIEND:
	case PMAKE_POKERUS:
	case PMAKE_EXP:

	case PMAKE_GETPLACE:
	case PMAKE_GETLEVEL:
	case PMAKE_GETCASSETTE:
	case PMAKE_GETBALL:
	case PMAKE_CONTRY_CODE:
	case PMAKE_FORM_NO:
		PokeMake_NumPrint(
			&wk->win, wk->mman, wk->wset, dpw, dpw->PMD[id], vp, 12+72+24, y, MSG_NO_PUT, pal );
		break;

	case PMAKE_TAMAGO:
	case PMAKE_EVGET:
		if( dpw->PMD[id] ){
			PokeMake_StrPrint(
				&wk->win, wk->mman, msg_pmstr_04, 12+72+24, y, MSG_NO_PUT, COL_W_BLACK );
		}else{
			PokeMake_StrPrint(
				&wk->win, wk->mman, msg_pmstr_05, 12+72+24, y, MSG_NO_PUT, COL_W_BLACK );
		}
		break;

	case PMAKE_PERSONAL:
		WORDSET_RegisterSeikaku( wk->wset, 0, dpw->PMD[id] );
		PokeMake_StrPrintExp(
			&wk->win, wk->mman, wk->wset, msg_pmstr_11, 12+72+24, y, MSG_NO_PUT, pal );
		break;

	default:
		break;
	}

	return	0;
}

//データ取得
static u32 getproc( PokeMakeWork * dpw, u8 id )
{
	u32	dat;

	switch( id ){
	default:
		dat	= dpw->PMD[id];
		break;
	}
	return dat;
}

//データセット
static void setproc( PokeMakeWork * dpw, u32 dat, u8 id )
{
	switch( id ){
	case PMAKE_NAME:
	case PMAKE_PERRND:
	case PMAKE_ID:
		dpw->PMD[id] = dat;
		PokeMakePokeParaCalcInit( dpw );
		break;

	case PMAKE_LEVEL:
		dpw->PMD[id] = dat;
		dpw->PMD[PMAKE_EXP] = PokeLevelExpGet( dpw->PMD[PMAKE_NAME], dat );
		PokeMakePokeParaCalcInit( dpw );
		break;

	case PMAKE_EXP:
		dpw->PMD[id] = dat;
		PokeMakePokeParaCalcGetExp( dpw );
		break;

	case PMAKE_HP_RND:
	case PMAKE_POW_RND:
	case PMAKE_DEF_RND:
	case PMAKE_AGI_RND:
	case PMAKE_EXPOW_RND:
	case PMAKE_EXDEF_RND:
	case PMAKE_HP_EXP:
	case PMAKE_POW_EXP:
	case PMAKE_DEF_EXP:
	case PMAKE_AGI_EXP:
	case PMAKE_EXPOW_EXP:
	case PMAKE_EXDEF_EXP:
		dpw->PMD[id] = dat;
		PokeMakePokeParaCalcGetBattleParam( dpw );
		break;

	default:
		dpw->PMD[id] = dat;
		break;
	}
}


/********************************************************************/
/*				サブ												*/
/********************************************************************/
static const u32 PmakeValueTable[] = {
	1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
};

static void ValueControl( PokeMakeWork * dpw, u8 mode )
{
	u32	data, datamin, datamax, value;

	data    = getproc( dpw, PageTable[dpw->page_p].page[dpw->cursor_p] );
	datamin = PMakelabelTable[ PageTable[dpw->page_p].page[dpw->cursor_p] ].cont->min;
	datamax = PMakelabelTable[ PageTable[dpw->page_p].page[dpw->cursor_p] ].cont->max;
	value   = PmakeValueTable[ dpw->value_p ];

	switch( PMakelabelTable[ PageTable[dpw->page_p].page[dpw->cursor_p] ].cont->mode ){
	case PMC_INCDEC:
		switch( mode ){
		case PMC_INC:
			if( data < datamax-value ){
				data += value;
			}else{
				if( data < datamax ){
					data = datamax;
				}else{
					data = datamin;
				}
			}
			break;

		case PMC_DEC:
			if( data > datamin+value ){
				data-=value;
			}else{
				if( data > datamin ){
					data = datamin;
				}else{
					data = datamax;
				}
			}
			break;
		}
		break;
	}
	setproc( dpw, data, PageTable[dpw->page_p].page[dpw->cursor_p] );
}

/********************************************************************/
static void CursorPut( D_POKEMONMAKE * wk, u8 mode )
{
	PokeMakeWork * dpw = &wk->pmw;

	switch( mode ){
	case PMC_INIT:
		BMPCURSOR_Print( wk->cursor, &wk->win, 0, dpw->cursor_p*16 );
		GF_BGL_BmpWinOnVReq( &wk->win );
		break;
	case PMC_INC:
		if( dpw->cursor_p < PageTable[dpw->page_p].listcount-1 ){
			GF_BGL_BmpWinFill( &wk->win, 15, 0, dpw->cursor_p*16, 12, 16 );
			dpw->cursor_p++;
			BMPCURSOR_Print( wk->cursor, &wk->win, 0, dpw->cursor_p*16 );
			GF_BGL_BmpWinOnVReq( &wk->win );
		}
		break;
	case PMC_DEC:
		if( dpw->cursor_p > 0 ){
			GF_BGL_BmpWinFill( &wk->win, 15, 0, dpw->cursor_p*16, 12, 16 );
			dpw->cursor_p--;
			BMPCURSOR_Print( wk->cursor, &wk->win, 0, dpw->cursor_p*16 );
			GF_BGL_BmpWinOnVReq( &wk->win );
		}
		break;
	}
}

/********************************************************************/
static void PagePut( D_POKEMONMAKE * wk )
{
	PokeMakeWork * dpw = &wk->pmw;
	u16	i;

	GF_BGL_BmpWinDataFill( &wk->win, 15 );
	i = 0;
	while( PageTable[dpw->page_p].page[i] != 0xff ){
		putproc( wk, PageTable[dpw->page_p].page[i], COL_W_BLACK, i*16 );
		i++;
	}
	GF_BGL_BmpWinCgxOn( &wk->win );
}

/********************************************************************/
static void PageValuePut( D_POKEMONMAKE * wk )
{
	PokeMakeWork * dpw = &wk->pmw;
	u16	i;

	GF_BGL_BmpWinDataFill( &wk->win, 15 );
	i = 0;
	while( PageTable[dpw->page_p].page[i] != 0xff ){
		if(i==dpw->cursor_p){
			putproc( wk, PageTable[dpw->page_p].page[i], COL_W_RED, i*16 );
		}else{
			putproc( wk, PageTable[dpw->page_p].page[i], COL_W_BLACK, i*16 );
		}
		i++;
	}
	GF_BGL_BmpWinCgxOn( &wk->win );
}

/********************************************************************/
static void NumPutBufferSet( PokeMakeWork * dpw, u16 * buf, u8 num, u8 pal, u8 cp )
{
	*buf = C_DCOL_;
	buf++;
	if( pal == COL_W_RED ){
		if( cp == dpw->value_p ){
			*buf = DCOL_BLUE_;
		}else{
			*buf = DCOL_RED_;
		}
	}else{
		*buf = DCOL_BLACK_;
	}
	buf++;
	*buf = n0_ + num;
}
//ナンバーデータ作成
static void NumPutBuffer( PokeMakeWork * dpw, u16 * buf, u32 num, u8 cnt, u8 pal )
{
	u8	i;

	i = 0;

	switch(cnt){
	default:
	case 10:
		NumPutBufferSet( dpw, &buf[i], num/1000000000, pal, 9 );
		num = num%1000000000;
		i += 3;
	case 9:
		NumPutBufferSet( dpw, &buf[i], num/100000000, pal, 8 );
		num = num%100000000;
		i += 3;
	case 8:
		NumPutBufferSet( dpw, &buf[i], num/10000000, pal, 7 );
		num = num%10000000;
		i += 3;
	case 7:
		NumPutBufferSet( dpw, &buf[i], num/1000000, pal, 6 );
		num = num%1000000;
		i += 3;
	case 6:
		NumPutBufferSet( dpw, &buf[i], num/100000, pal, 5 );
		num = num%100000;
		i += 3;
	case 5:
		NumPutBufferSet( dpw, &buf[i], num/10000, pal, 4 );
		num = num%10000;
		i += 3;
	case 4:
		NumPutBufferSet( dpw, &buf[i], num/1000, pal, 3 );
		num = num%1000;
		i += 3;
	case 3:
		NumPutBufferSet( dpw, &buf[i], num/100, pal, 2 );
		num = num%100;
		i += 3;
	case 2:
		NumPutBufferSet( dpw, &buf[i], num/10, pal, 1 );
		num = num%10;
		i += 3;
	case 1:
		NumPutBufferSet( dpw, &buf[i], num, pal, 0 );
		i += 3;
		buf[i] = EOM_;
	}
}

/********************************************************************/
static void PokeMake_StrPrint(
			GF_BGL_BMPWIN * win, MSGDATA_MANAGER * man, u32 id, u32 x, u32 y, u32 wait, u32 col )
{
	STRBUF * strb;

	strb = MSGMAN_AllocString( man, id );
	GF_STR_PrintColor( win, FONT_SYSTEM, strb, x, y, wait, col, NULL );
	STRBUF_Delete( strb );
}

static void PokeMake_StrPrintExp(
			GF_BGL_BMPWIN * win, MSGDATA_MANAGER * man, WORDSET * wset,
			u32 id, u32 x, u32 y, u32 wait, u32 col )
{
	STRBUF * expb;
	STRBUF * strb;

	expb = STRBUF_Create( 128, HEAPID_BASE_APP );
	strb = MSGMAN_AllocString( man, id );

	WORDSET_ExpandStr( wset, expb, strb );

	GF_STR_PrintColor( win, FONT_SYSTEM, expb, x, y, wait, col, NULL );
	STRBUF_Delete( strb );
	STRBUF_Delete( expb );
}

static void PokeMake_MonsNamePut( GF_BGL_BMPWIN * win, u32 mons, u32 x, u32 y, u32 wait, u32 col )
{
	MSGDATA_MANAGER* man;
	STRBUF * strb;

	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_monsname_dat, HEAPID_BASE_APP );

	strb = MSGMAN_AllocString( man, mons );
	GF_STR_PrintColor( win, FONT_SYSTEM, strb, x, y, wait, col, NULL );
	STRBUF_Delete( strb );
	MSGMAN_Delete( man );
}

static u32 NumPutColorGet( PokeMakeWork * dpw, u8 cp, u32 col )
{
	if( col == COL_W_RED ){
		if( cp == dpw->value_p ){
			return COL_W_BLUE;
		}else{
			return COL_W_RED;
		}
	}
	return COL_W_BLACK;
}

//ナンバーデータ作成
static void PokeMake_NumPrint(
			GF_BGL_BMPWIN * win, MSGDATA_MANAGER * man, WORDSET * wset,
			PokeMakeWork * dpw, u32 num, u32 keta, u32 x, u32 y, u32 wait, u32 col )
{
	STRBUF * expb;
	STRBUF * strb;
	u32	i, tmp, siz;

	expb = STRBUF_Create( 32, HEAPID_BASE_APP );
	strb = MSGMAN_AllocString( man, msg_pmstr_06 );

	tmp = 1;
	for( i=0; i<keta-1; i++ ){
		tmp *= 10;
	}

	siz = 0;
	for( i=keta; i>=1; i-- ){
		WORDSET_RegisterNumber( wset, 0, num/tmp, 1, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr( wset, expb, strb );
		GF_STR_PrintColor(
			win, FONT_SYSTEM, expb, x+siz, y, MSG_NO_PUT, NumPutColorGet(dpw,i-1,col), NULL );
		num %= tmp;
		tmp /= 10;
		siz += FontProc_GetPrintStrWidth( FONT_SYSTEM, expb, 0 );
	}

	if( wait == MSG_ALLPUT ){
		GF_BGL_BmpWinOnVReq( win );
	}

	STRBUF_Delete( strb );
	STRBUF_Delete( expb );
}


/********************************************************************/
#define PARAMGET( index, ID ) { dpw->PMD[index] = PokeParaGet( dpw->PokeMakeData, ID, NULL ); }

static void PokeMakePokeParaWorkGetAll( PokeMakeWork * dpw )
{
	PARAMGET( PMAKE_NAME, ID_PARA_monsno )
	PARAMGET( PMAKE_LEVEL, ID_PARA_level )
	PARAMGET( PMAKE_EXP, ID_PARA_exp )
	PARAMGET( PMAKE_ID, ID_PARA_id_no )
	PARAMGET( PMAKE_PERRND, ID_PARA_personal_rnd )
	PARAMGET( PMAKE_SEX, ID_PARA_sex )
	dpw->PMD[ PMAKE_PERSONAL ] = PokeSeikakuGet( dpw->PokeMakeData );
	PARAMGET( PMAKE_WAZA1, ID_PARA_waza1 )
	PARAMGET( PMAKE_WAZA2, ID_PARA_waza2 )
	PARAMGET( PMAKE_WAZA3, ID_PARA_waza3 )
	PARAMGET( PMAKE_WAZA4, ID_PARA_waza4 )
	PARAMGET( PMAKE_ITEM, ID_PARA_item )

	PARAMGET( PMAKE_SPABI, ID_PARA_speabino )
	if( dpw->PMD[PMAKE_SPABI] == PokePersonalParaGet(dpw->PMD[PMAKE_NAME],ID_PER_speabi1) ){
		dpw->PMD[PMAKE_SPABI] = 0;
	}else{
		dpw->PMD[PMAKE_SPABI] = 1;
	}

	PARAMGET( PMAKE_HP_RND, ID_PARA_hp_rnd )
	PARAMGET( PMAKE_HP_EXP, ID_PARA_hp_exp )
	PARAMGET( PMAKE_POW_RND, ID_PARA_pow_rnd )
	PARAMGET( PMAKE_POW_EXP, ID_PARA_pow_exp )
	PARAMGET( PMAKE_DEF_RND, ID_PARA_def_rnd )
	PARAMGET( PMAKE_DEF_EXP, ID_PARA_def_exp )
	PARAMGET( PMAKE_AGI_RND, ID_PARA_agi_rnd )
	PARAMGET( PMAKE_AGI_EXP, ID_PARA_agi_exp )
	PARAMGET( PMAKE_EXPOW_RND, ID_PARA_spepow_rnd )
	PARAMGET( PMAKE_EXPOW_EXP, ID_PARA_spepow_exp )
	PARAMGET( PMAKE_EXDEF_RND, ID_PARA_spedef_rnd )
	PARAMGET( PMAKE_EXDEF_EXP, ID_PARA_spedef_exp )
	PARAMGET( PMAKE_STYLE, ID_PARA_style )
	PARAMGET( PMAKE_BEAUTIFUL, ID_PARA_beautiful )
	PARAMGET( PMAKE_CUTE, ID_PARA_cute )
	PARAMGET( PMAKE_CLEVER, ID_PARA_clever )
	PARAMGET( PMAKE_STRONG, ID_PARA_strong )
	PARAMGET( PMAKE_FUR, ID_PARA_fur )
	PARAMGET( PMAKE_FRIEND, ID_PARA_friend )
	PARAMGET( PMAKE_POKERUS, ID_PARA_pokerus )
	PARAMGET( PMAKE_TAMAGO, ID_PARA_tamago_flag )

//	PARAMGET( PMAKE_CONDITION, ID_PARA_condition )
	{
		u32	prm;
		u32	i;

		prm = PokeParaGet( dpw->PokeMakeData, ID_PARA_condition, NULL );
		dpw->PMD[PMAKE_CONDITION] = 0;
		for( i=0; i<7; i++ ){
			if( prm == CondTable[i][1] ){
				dpw->PMD[PMAKE_CONDITION] = i;
				break;
			}
		}
	}

	PARAMGET( PMAKE_HP, ID_PARA_hpmax )
	PARAMGET( PMAKE_POW, ID_PARA_pow )
	PARAMGET( PMAKE_DEF, ID_PARA_def )
	PARAMGET( PMAKE_AGI, ID_PARA_agi )
	PARAMGET( PMAKE_EXPOW, ID_PARA_spepow )
	PARAMGET( PMAKE_EXDEF, ID_PARA_spedef )
	PARAMGET( PMAKE_EVGET, ID_PARA_event_get_flag )
	PARAMGET( PMAKE_GETPLACE, ID_PARA_birth_place )
	PARAMGET( PMAKE_GETLEVEL, ID_PARA_get_level )
	PARAMGET( PMAKE_GETCASSETTE, ID_PARA_get_cassette )
	PARAMGET( PMAKE_GETBALL, ID_PARA_get_ball )
	PARAMGET( PMAKE_CONTRY_CODE, ID_PARA_country_code )
	PARAMGET( PMAKE_FORM_NO, ID_PARA_form_no )
}
	
#define PARAMPUT( index, ID ) {	PokeParaPut( dpw->PokeMakeData, ID, &dpw->PMD[index] ); }

static void PokeMakePokeParaWorkPutAll( PokeMakeWork * dpw )
{
	int	val;

	PARAMPUT( PMAKE_NAME, ID_PARA_monsno )
	PARAMPUT( PMAKE_LEVEL, ID_PARA_level )
	PARAMPUT( PMAKE_EXP, ID_PARA_exp )
	PARAMPUT( PMAKE_ID, ID_PARA_id_no )
	PARAMPUT( PMAKE_PERRND, ID_PARA_personal_rnd )
	PARAMPUT( PMAKE_SEX, ID_PARA_sex )
/*
	PARAMPUT( PMAKE_WAZA1, ID_PARA_waza1 )
	PARAMPUT( PMAKE_WAZA2, ID_PARA_waza2 )
	PARAMPUT( PMAKE_WAZA3, ID_PARA_waza3 )
	PARAMPUT( PMAKE_WAZA4, ID_PARA_waza4 )
*/
	if( dpw->PMD[PMAKE_WAZA1] ){
		D_PokeWazaSetPos( dpw->PokeMakeData, dpw->PMD[PMAKE_WAZA1], 0 );
	}
	if( dpw->PMD[PMAKE_WAZA2] ){
		D_PokeWazaSetPos( dpw->PokeMakeData, dpw->PMD[PMAKE_WAZA2], 1 );
	}
	if( dpw->PMD[PMAKE_WAZA3] ){
		D_PokeWazaSetPos( dpw->PokeMakeData, dpw->PMD[PMAKE_WAZA3], 2 );
	}
	if( dpw->PMD[PMAKE_WAZA4] ){
		D_PokeWazaSetPos( dpw->PokeMakeData, dpw->PMD[PMAKE_WAZA4], 3 );
	}

	PARAMPUT( PMAKE_ITEM, ID_PARA_item )

	val = PokePersonalParaGet( dpw->PMD[PMAKE_NAME], ID_PER_speabi1+dpw->PMD[PMAKE_SPABI] );
	PokeParaPut( dpw->PokeMakeData, ID_PARA_speabino, &val );

	PARAMPUT( PMAKE_HP_RND, ID_PARA_hp_rnd )
	PARAMPUT( PMAKE_HP_EXP, ID_PARA_hp_exp )
	PARAMPUT( PMAKE_POW_RND, ID_PARA_pow_rnd )
	PARAMPUT( PMAKE_POW_EXP, ID_PARA_pow_exp )
	PARAMPUT( PMAKE_DEF_RND, ID_PARA_def_rnd )
	PARAMPUT( PMAKE_DEF_EXP, ID_PARA_def_exp )
	PARAMPUT( PMAKE_AGI_RND, ID_PARA_agi_rnd )
	PARAMPUT( PMAKE_AGI_EXP, ID_PARA_agi_exp )
	PARAMPUT( PMAKE_EXPOW_RND, ID_PARA_spepow_rnd )
	PARAMPUT( PMAKE_EXPOW_EXP, ID_PARA_spepow_exp )
	PARAMPUT( PMAKE_EXDEF_RND, ID_PARA_spedef_rnd )
	PARAMPUT( PMAKE_EXDEF_EXP, ID_PARA_spedef_exp )
	PARAMPUT( PMAKE_STYLE, ID_PARA_style )
	PARAMPUT( PMAKE_BEAUTIFUL, ID_PARA_beautiful )
	PARAMPUT( PMAKE_CUTE, ID_PARA_cute )
	PARAMPUT( PMAKE_CLEVER, ID_PARA_clever )
	PARAMPUT( PMAKE_STRONG, ID_PARA_strong )
	PARAMPUT( PMAKE_FUR, ID_PARA_fur )
	PARAMPUT( PMAKE_FRIEND, ID_PARA_friend )
	PARAMPUT( PMAKE_POKERUS, ID_PARA_pokerus )
	PARAMPUT( PMAKE_TAMAGO, ID_PARA_tamago_flag )

//	PARAMPUT( PMAKE_CONDITION, ID_PARA_condition )

	PokeParaPut(
		dpw->PokeMakeData, ID_PARA_condition, &CondTable[ dpw->PMD[PMAKE_CONDITION] ][1] );

	PARAMPUT( PMAKE_HP, ID_PARA_hpmax )
	PARAMPUT( PMAKE_POW, ID_PARA_pow )
	PARAMPUT( PMAKE_DEF, ID_PARA_def )
	PARAMPUT( PMAKE_AGI, ID_PARA_agi )
	PARAMPUT( PMAKE_EXPOW, ID_PARA_spepow )
	PARAMPUT( PMAKE_EXDEF, ID_PARA_spedef )
	PARAMPUT( PMAKE_EVGET, ID_PARA_event_get_flag )
	PARAMPUT( PMAKE_GETPLACE, ID_PARA_birth_place )
	PARAMPUT( PMAKE_GETLEVEL, ID_PARA_get_level )
	PARAMPUT( PMAKE_GETCASSETTE, ID_PARA_get_cassette )
	PARAMPUT( PMAKE_GETBALL, ID_PARA_get_ball )
	PARAMPUT( PMAKE_CONTRY_CODE, ID_PARA_country_code )
	PARAMPUT( PMAKE_FORM_NO, ID_PARA_form_no )

	PokeParaCalc( dpw->PokeMakeData );
}



//============================================================================================
//============================================================================================
//	ダメタマゴ
//============================================================================================
//============================================================================================
void DebugDameTamagoSet( void * fsys )
{
	POKEPARTY * party;
	POKEMON_PARAM * pp;
	u32	csum;
	u8	flg;

	party = SaveData_GetTemotiPokemon( ((FIELDSYS_WORK *)fsys)->savedata );
	pp    = PokeParty_GetMemberPointer( party, 0 );
	csum  = 1234567;
	flg   = 1;

	PokeParaPut( pp, ID_PARA_fusei_tamago_flag, &flg );
	PokeParaPut( pp, ID_PARA_checksum, &csum );

	FieldSystemProc_SeqHoldEnd();
}


#endif
