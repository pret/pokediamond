//============================================================================================
/**
 * @file	d_taya.c
 * @bfief	田谷 デバッグメニュー
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifdef PM_DEBUG

#include "common.h"
#include "system/lib_pack.h"
#include "system/bmp_list.h"
#include "system/wipe.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "system/fontproc.h"
#include "fld_bmp.h"
#include "system/pm_str.h"
#include "system/pm_overlay.h"
#include "field_event.h"
#include "system\palanm.h"
#include "application\pms_input.h"
#include "system\pm_rtc.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_debug_taya.h"



#include "d_taya.h"





//---------------------------------------------------------------------------------------------
// 定義
//---------------------------------------------------------------------------------------------
enum {
	WK_SEQ = 0,
	WK_WIN_INDEX,
	WK_LIST_ID,
	WK_LIST_RET
};

typedef struct {
	u16 seq;
	u16 list_ret;

	FIELDSYS_WORK*  fsys;
	BMPLIST_WORK*   list_work;
	GF_BGL_BMPWIN   win;
	BMPLIST_DATA*   menulist;
	GF_BGL_INI*     bgl;

}WORK;

//-----------------------------------------------------------------
/**
 * たんにフェードアウトして何か別画面の初期化を呼ぶだけ
 */
//-----------------------------------------------------------------
typedef void (*ScheneChangeCallback)(FIELDSYS_WORK*, void* wk);




//==============================================================
// Prototype
//==============================================================
static void DebugTayaBmpMenuExit( WORK* wk );
static void DebugMenuExitSub( TCB_PTR tcb );
static void DebugMenuExit( void );
static void DebugTayaMenuMain( TCB_PTR _tcb, void * work );
static void PoketchStartDebug(FIELDSYS_WORK* fsys);
static void BoxStartDebug(FIELDSYS_WORK* fsys, BOX_MODE mode );
static void BoxStartCallBack( FIELDSYS_WORK* fsys, void* wk );
static void BoxEndCallBack( FIELDSYS_WORK* fsys, void* wk );
static void BoxStartDebugSeiri(FIELDSYS_WORK* fsys);
static void BoxStartDebugItem(FIELDSYS_WORK* fsys);
static void BoxStartDebugComp(FIELDSYS_WORK* fsys);
static void TradeDemoStart( FIELDSYS_WORK* fsys );
static void TradeDemoStartCallBack( FIELDSYS_WORK* fsys, void* wk );
static void TradeDemoEndCallBack( FIELDSYS_WORK* fsys, void* wk );
static void TestTask( TCB_PTR tcb, void* wk_adrs );
static void TestTaskSet( void );
static void DendouDemo_Call( FIELDSYS_WORK* fsys );
static void DendouDemo_StartCallBack( FIELDSYS_WORK* fsys, void* wk );
static void DendouDemo_EndCallBack( FIELDSYS_WORK* fsys, void* wk );
static void DendouPC_Call( FIELDSYS_WORK* fsys );
static void DendouPC_StartCallBack( FIELDSYS_WORK* fsys, void* wk );
static void DendouPC_EndCallBack(FIELDSYS_WORK* fsys, void* wk);
static void EndingDemo_Call( FIELDSYS_WORK* fsys );
static void EndingStartCallback( FIELDSYS_WORK* fsys, void* wk );
static void EndingEndCallback( FIELDSYS_WORK* fsys, void* wk );
static void PmsStartSingle( FIELDSYS_WORK* fsys );
static void PmsStartDouble( FIELDSYS_WORK* fsys );
static void PmsStartSentence( FIELDSYS_WORK* fsys );
static void PmsCallbackStart(FIELDSYS_WORK* fsys, void* wk);
static void PmsCallbackEnd(FIELDSYS_WORK* fsys, void* wk);
static void CurrentFullTool( FIELDSYS_WORK* fsys );
static void BoxFullTool( FIELDSYS_WORK* fsys );
static void PmsWordFullTool( FIELDSYS_WORK* fsys );
static BOOL GMEVENT_ChangeScheneDebug(GMEVENT_CONTROL * event);
static void Debug_ChangeScheneReq( FIELDSYS_WORK* fsys, ScheneChangeCallback start_func, ScheneChangeCallback end_func, void* gen_wk );



//--------------------------------------------------------------------------------------------
// デバッグメニュー用定義
//--------------------------------------------------------------------------------------------
static const struct {
	u32  str_id;
	u32  param;
}MenuParamList[] = {
	{ menu_box_seiri,	(u32)BoxStartDebugSeiri },
	{ menu_box_item,	(u32)BoxStartDebugItem },
	{ menu_box_comp,	(u32)BoxStartDebugComp },
	{ menu_demo1,		(u32)TradeDemoStart },
	{ menu_demo2,		(u32)DendouDemo_Call },
	{ menu_demo3,		(u32)DendouPC_Call },
	{ menu_demo4,		(u32)EndingDemo_Call },
	{ menu_poketch,		(u32)PoketchStartDebug },
	{ menu_pms_single,	(u32)PmsStartSingle },
	{ menu_pms_double,	(u32)PmsStartDouble },
	{ menu_pms_sentence,(u32)PmsStartSentence },
	{ menu_current_full,(u32)CurrentFullTool },
	{ menu_box_full,	(u32)BoxFullTool },
	{ menu_pmsword_full,(u32)PmsWordFullTool },

};



static const BMPLIST_HEADER d_menu_list_h = {
	NULL,					// 表示文字データポインタ
	NULL,					// カーソル移動ごとのコールバック関数
	NULL,					// 一列表示ごとのコールバック関数
	NULL,					// BitmapWindow
	NELEMS(MenuParamList),	// リスト項目数
	10,						// 表示最大項目数
	0,						// ラベル表示Ｘ座標
	8,						// 項目表示Ｘ座標
	0,						// カーソル表示Ｘ座標
	0,						// 表示Ｙ座標
	FBMP_COL_BLACK,			// 文字色
	FBMP_COL_WHITE,			// 背景色
	FBMP_COL_BLK_SDW,		// 文字影色
	0,						// 文字間隔Ｘ
	16,						// 文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,		// ページスキップタイプ
	FONT_SYSTEM,			// 文字指定(本来は u8 だけど、そんなに作らないと思うので)
	0						// ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
};


typedef void (*pDebugMenu)(FIELDSYS_WORK*);

//==============================================================================
/**
 * デバッグメニュー初期化関数（fld_debug.cから呼ばれます)
 *
 * @param   none		
 *
 * @retval  none		
 */
//==============================================================================
void DebugTayaMenuInit( void* fsys )
{
	WORK* wk;
	GF_BGL_INI * bgl;
	BMPLIST_HEADER	list_h;

	bgl = FieldBglIniGet( fsys );

	wk = (WORK*)TCB_GetWork( PMDS_taskAdd( DebugTayaMenuMain, sizeof(WORK), 0, HEAPID_BASE_DEBUG ) );
	wk->seq = 0;
	wk->bgl = bgl;
	wk->fsys = fsys;
	wk->menulist = BMP_MENULIST_Create( NELEMS(MenuParamList), HEAPID_BASE_DEBUG );
	GF_BGL_BmpWinAdd( bgl, &(wk->win), FLD_MBGFRM_FONT, 1, 1, 14, 20, FLD_SYSFONT_PAL, 1 );

	{
		MSGDATA_MANAGER* msgman;
		int i;

		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_taya_dat, HEAPID_BASE_DEBUG);
		for(i=0; i<NELEMS(MenuParamList); i++)
		{
			BMP_MENULIST_AddArchiveString( wk->menulist, msgman, MenuParamList[i].str_id, MenuParamList[i].param );
		}
		MSGMAN_Delete(msgman);
	}

	list_h = d_menu_list_h;
	list_h.list = wk->menulist;
	list_h.win = &(wk->win);
	wk->list_work = BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->win );

}
//------------------------------------------------------------------
/**
 * デバッグメニューBmpList解放
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DebugTayaBmpMenuExit( WORK* wk )
{
	BMP_MENULIST_Delete( wk->menulist );
	BmpListExit( wk->list_work, NULL, NULL );

	GF_BGL_BmpWinOff( &wk->win );
	GF_BGL_BmpWinDel( &wk->win );
}


//------------------------------------------------------------------
/**
 * デバッグメニュー解放処理
 *
 * @param   tcb		
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void DebugMenuExitSub( TCB_PTR tcb )
{
	WORK* wk = (WORK*)TCB_GetWork(tcb);

	DebugTayaBmpMenuExit( wk );
	PMDS_taskDel( tcb );
	FieldSystemProc_SeqHoldEnd();
}

//------------------------------------------------------------------
/**
 * 呼び出し
 *
 * @param   none		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DebugMenuExit( void )
{

	FieldSystemProc_SeqHoldEnd();

}


//------------------------------------------------------------------
/**
 * 
 *
 * @param   _tcb		
 * @param   work		
 *
 */
//------------------------------------------------------------------
static void DebugTayaMenuMain( TCB_PTR _tcb, void * work )
{
	WORK* wk = (WORK*)work;
	u32	ret;

	switch( wk->seq ){
	case 0:
		ret = BmpListMain( wk->list_work );

		switch( ret ){
		case BMPLIST_NULL:
			break;
		case BMPLIST_CANCEL:
			DebugMenuExitSub( _tcb );
			break;
		default:
			{
				pDebugMenu func = (pDebugMenu)ret;
				FIELDSYS_WORK* fsys = wk->fsys;
				DebugMenuExitSub( _tcb );
				func( fsys );
			}
			break;
		}
	}
}



/*====================================================================================================*/
/*  ポケッチ関連                                                                                      */
/*====================================================================================================*/
#include "field\poketch.h"
#include "field\poketch_data.h"
#include "field\eventflag.h"
#include "syswork.h"
///オーバーレイモジュールのextern宣言です。
FS_EXTERN_OVERLAY(ol_poketch);

extern struct _POKETCH_WORK* GetPoketchMainWorkPtr(void);

//------------------------------------------------------------------
/**
 * ポケッチ初期化開始
 */
//------------------------------------------------------------------
static void PoketchStartDebug(FIELDSYS_WORK* fsys)
{
	extern void EventCmd_DebugGetPoketch(FIELDSYS_WORK* fsys);
	POKETCH_DATA* pd = SaveData_GetPoketchData( fsys->savedata );

	if( PoketchData_GetPoketchGetFlag( pd ) == FALSE )
	{
		#if 1
		PoketchData_AddAllApplication( pd );
		#else
		PoketchData_AddApplication( pd, POKETCH_APPID_DWATCH );
		PoketchData_AddApplication( pd, POKETCH_APPID_CALC );
		PoketchData_AddApplication( pd, POKETCH_APPID_PEDOMETER );
		PoketchData_AddApplication( pd, POKETCH_APPID_POKELIST );
		#endif
		EventCmd_DebugGetPoketch( fsys );
	}

	#if 0 // ポケモンヒストリーに手持ちを全部追加
	{
		POKEPARTY* party;
		int i, max;

		party = SaveData_GetTemotiPokemon( fsys->savedata );
		max = PokeParty_GetPokeCount( party );
		for(i=0; i<max; i++)
		{
			PoketchData_PokeHistory_Add( pd, (const POKEMON_PASO_PARAM*)PokeParty_GetMemberPointer( party, i ) );
		}
	}
	#endif

	#if 0
	{
		EVENTWORK* ev = SaveData_GetEventWork( fsys->savedata );
		int i;
		for(i=0; i<4; i++)
		{
			SysWork_HideMapWorkSet( ev, i );
		}
	}
	#endif
}


/*====================================================================================================*/
/*  ボックス関連                                                                                      */
/*====================================================================================================*/
#include "application\box.h"
#include "field\field_subproc.h"
#include "savedata\mystatus.h"
#include "itemtool\itemsym.h"

typedef struct {
	u32					seq;
	ScheneChangeCallback	start_func;
	ScheneChangeCallback	end_func;
	BOOL				fadeFlag;
	void*				gen_wk;
}DEBUG_CHANGESCHENE_WORK;

static void BoxStartDebug(FIELDSYS_WORK* fsys, BOX_MODE mode )
{
	BOX_PROC_PARAM* param = sys_AllocMemory(HEAPID_BASE_DEBUG, sizeof(BOX_PROC_PARAM));
	param->mode = mode;
	param->savedata = fsys->savedata;
	Debug_ChangeScheneReq( fsys, BoxStartCallBack, BoxEndCallBack, param );
}
static void BoxStartCallBack( FIELDSYS_WORK* fsys, void* wk )
{
	BOX_DATA* boxDat = SaveData_GetBoxData( fsys->savedata );

	if( sys.cont & PAD_BUTTON_L )
	{
		int i;
		for(i=0; i<BOX_EX_WALLPAPER_MAX; i++)
		{
			BOXDAT_SetDaisukiKabegamiFlag( boxDat, i );
		}
	}

#if 0
	{
		#include "poketool\monsno.h"
		static const u16 monsno[] = {
			MONSNO_HUSIGIDANE,
			MONSNO_HUSIGISOU,
			MONSNO_HUSIGIBANA,
			MONSNO_HITOKAGE,
			MONSNO_RIZAADO,
			MONSNO_RIZAADON,
			MONSNO_ZENIGAME,
			MONSNO_KAMEERU,
			MONSNO_KAMEKKUSU,
			MONSNO_KYATAPII,
			MONSNO_TORANSERU,
			MONSNO_BATAHURII,
			MONSNO_BIIDORU,
			MONSNO_WANRIKII,
			MONSNO_ZUBATTO,
			MONSNO_POPPO,
			MONSNO_PIZYON,
			MONSNO_PIZYOTTO,
			MONSNO_KORATTA,
			MONSNO_RATTA,
		};

		POKEMON_PASO_PARAM* ppp = sys_AllocMemory(HEAPID_BASE_DEBUG, PokemonPasoParamSizeGet() );
		if( ppp )
		{
			MYSTATUS* myst = SaveData_GetMyStatus( fsys->savedata );
			int i;
			for(i=0; i<NELEMS(monsno); i++)
			{
				PokePasoParaSet(ppp, monsno[i], 50, POW_RND, RND_NO_SET, 0, ID_NO_SET, 0);
				PokePasoParaGetInfoSet(ppp, myst, ITEM_MONSUTAABOORU, 1, 1, HEAPID_BASE_DEBUG);
				BOXDAT_PutPokemonPos( boxDat, 0, i, ppp );
			}
			sys_FreeMemoryEz(ppp);
		}
	}
#endif

	FieldBox_SetProc(fsys, wk);
}
static void BoxEndCallBack( FIELDSYS_WORK* fsys, void* wk )
{
	sys_FreeMemoryEz(wk);
}

static void BoxStartDebugSeiri(FIELDSYS_WORK* fsys)
{
	BoxStartDebug( fsys, BOX_MODE_SEIRI );
}
static void BoxStartDebugItem(FIELDSYS_WORK* fsys)
{
	BoxStartDebug( fsys, BOX_MODE_ITEM );
}
static void BoxStartDebugComp(FIELDSYS_WORK* fsys)
{
	BoxStartDebug( fsys, BOX_MODE_COMPARE );
}

/*====================================================================================================*/
/*  交換デモ                                                                                          */
/*====================================================================================================*/
#include "demo\demo_trade.h"

static void TradeDemoStart( FIELDSYS_WORK* fsys )
{
	DEMO_TRADE_PARAM* param;
	POKEPARTY* party;

	party = SaveData_GetTemotiPokemon(fsys->savedata);
	param = sys_AllocMemory( HEAPID_BASE_DEBUG, sizeof(DEMO_TRADE_PARAM) );
	param->sendPoke = (const POKEMON_PASO_PARAM*)PokeParty_GetMemberPointer(party, 0);
	param->recvPoke = (const POKEMON_PASO_PARAM*)PokeParty_GetMemberPointer(party, 1);
	param->partner = SaveData_GetMyStatus(fsys->savedata);
	param->bgType = DEMO_TRADE_BGTYPE_WIFI;
	param->seqFlag = DEMO_TRADE_SEQ_FULL;
	param->config = SaveData_GetConfig( fsys->savedata );

	Debug_ChangeScheneReq( fsys, TradeDemoStartCallBack, TradeDemoEndCallBack, param );
}
static void TradeDemoStartCallBack( FIELDSYS_WORK* fsys, void* wk )
{
	// プロセス定義データ
	static const PROC_DATA proc_data = {
		TradeDemoProc_Init,
		TradeDemoProc_Main,
		TradeDemoProc_Quit,
		FS_OVERLAY_ID(demo_trade),
	};


	GameSystem_StartSubProc(fsys,  &proc_data, wk );
}

static void TradeDemoEndCallBack( FIELDSYS_WORK* fsys, void* wk )
{
	sys_FreeMemoryEz(wk);
}

/*====================================================================================================*/
/*  殿堂入りデモ画面                                                                                  */
/*====================================================================================================*/
typedef struct {
	int seq;
	int sp;
	int timer;
	int cnt;
}TEST_TASKWORK;

extern void sys_ForceKeySet( int key );

static void TestTask( TCB_PTR tcb, void* wk_adrs )
{
	static const struct {
		int wait;
		int key;
		int cnt;
	}keytbl[] = {
		{ 20, PAD_KEY_RIGHT,	60 },
		{ 20, PAD_KEY_LEFT,		70 },
	};
	TEST_TASKWORK* wk = wk_adrs;

	switch( wk->seq ){
	case 0:
		if(++(wk->timer) < keytbl[wk->sp].wait)
		{
			break;
		}
		wk->timer = 0;
		wk->seq++;
		/* fallthru */
	case 1:
		sys_ForceKeySet( keytbl[wk->sp].key );
		if(++(wk->cnt) >= keytbl[wk->sp].cnt)
		{
			wk->cnt = 0;
			if(++(wk->sp) >= NELEMS(keytbl))
			{
				wk->sp = 0;
			}
			wk->seq=0;
		}
		break;
	}
}
static void TestTaskSet( void )
{
	TEST_TASKWORK* wk = sys_AllocMemory( HEAPID_BASE_DEBUG, sizeof(TEST_TASKWORK) );
	wk->timer = 0;
	wk->seq = 0;
	wk->cnt = 0;
	wk->sp = 0;
	TCB_Add( TestTask, wk, 0 );
}


FS_EXTERN_OVERLAY(demo_dendou);

#include "demo\demo_dendou.h"

static void DendouDemo_Call( FIELDSYS_WORK* fsys )
{
	DEMO_DENDOU_PARAM*  param;
	POKEPARTY* party;

	param = sys_AllocMemory( HEAPID_BASE_DEBUG, sizeof(DEMO_DENDOU_PARAM) );
	param->player = SaveData_GetMyStatus(fsys->savedata);
	param->party = SaveData_GetTemotiPokemon(fsys->savedata);
	param->playTime = SaveData_GetPlayTime(fsys->savedata);

	Debug_ChangeScheneReq( fsys, DendouDemo_StartCallBack, DendouDemo_EndCallBack, param );
}
static void DendouDemo_StartCallBack( FIELDSYS_WORK* fsys, void* wk )
{
	// プロセス定義データ
	static const PROC_DATA proc_data = {
		DemoDendouPROC_Init,
		DemoDendouPROC_Main,
		DemoDendouPROC_Quit,
		FS_OVERLAY_ID(demo_dendou),
	};


	GameSystem_StartSubProc(fsys,  &proc_data, wk );
}
static void DendouDemo_EndCallBack( FIELDSYS_WORK* fsys, void* wk )
{
	sys_FreeMemoryEz( wk );
}

/*====================================================================================================*/
/*  殿堂入りパソコン画面                                                                              */
/*====================================================================================================*/
FS_EXTERN_OVERLAY(dendou_pc);

#include "savedata\dendou_data.h"
#include "application\dendou_pc.h"
#include "system\snd_tool.h"

static void DendouPC_Call( FIELDSYS_WORK* fsys )
{
	DENDOU_SAVEDATA*  dd;
	POKEPARTY* party;
	RTCDate	date;
	LOAD_RESULT result;

	dd = SaveData_Extra_LoadDendouData(fsys->savedata, HEAPID_WORLD, &result);

	if( (sys.cont_org & (PAD_BUTTON_L|PAD_BUTTON_R)) == (PAD_BUTTON_L|PAD_BUTTON_R) )
	{
		if( result != LOAD_RESULT_NG )
		{
			DendouData_Init(dd);
			SaveData_Extra_SaveDendouData(fsys->savedata, dd);
			Snd_SePlay( SEQ_SE_DP_SAVE );
		}
		sys_FreeMemoryEz( dd );
		return;
	}

	party = SaveData_GetTemotiPokemon(fsys->savedata);
	if( result == LOAD_RESULT_NG )
	{
		DendouData_Init(dd);
	}
	GF_RTC_GetDate(&date);

	if( sys.cont_org & PAD_BUTTON_L )
	{
		u32 n = DendouData_GetRecordNumber( dd, 0 );
		while( n < (DENDOU_NUMBER_MAX-1) )
		{
			DendouData_AddRecord( dd, party, &date );
			n++;
		}
	}
	else
	{
		DendouData_AddRecord( dd, party, &date );
	}

	SaveData_Extra_SaveDendouData(fsys->savedata, dd);
	Debug_ChangeScheneReq( fsys, DendouPC_StartCallBack, DendouPC_EndCallBack, dd );

}
static void DendouPC_StartCallBack( FIELDSYS_WORK* fsys, void* wk )
{
	// プロセス定義データ
	static const PROC_DATA proc_data = {
		DendouPc_PROC_Init,
		DendouPc_PROC_Main,
		DendouPc_PROC_Quit,
		FS_OVERLAY_ID(dendou_pc),
	};


	GameSystem_StartSubProc(fsys,  &proc_data, wk );
}

static void DendouPC_EndCallBack(FIELDSYS_WORK* fsys, void* wk)
{
	sys_FreeMemoryEz(wk);
}


/*====================================================================================================*/
/*  エンディングデモ呼び出し                                                                          */
/*====================================================================================================*/
#include "demo\demo_ending.h"

FS_EXTERN_OVERLAY(demo_ending);

static void EndingDemo_Call( FIELDSYS_WORK* fsys )
{
	ENDING_PROC_PARAM*  param = sys_AllocMemory( HEAPID_BASE_DEBUG, sizeof(ENDING_PROC_PARAM) );

	param->playerSex = MyStatus_GetMySex( SaveData_GetMyStatus(fsys->savedata) );
	param->clearFlag = TRUE;
	param->zukanWork = SaveData_GetZukanWork(fsys->savedata);
	Debug_ChangeScheneReq( fsys, EndingStartCallback, EndingEndCallback, param );
}
static void EndingStartCallback( FIELDSYS_WORK* fsys, void* wk )
{

	// プロセス定義データ
	static const PROC_DATA proc_data = {
		EndingDemoProc_Init,
		EndingDemoProc_Main,
		EndingDemoProc_Quit,
		FS_OVERLAY_ID(demo_ending),
	};

	GameSystem_StartSubProc(fsys,  &proc_data, wk );
}
static void EndingEndCallback( FIELDSYS_WORK* fsys, void* wk )
{
	sys_FreeMemoryEz( wk );
}

/*====================================================================================================*/
/*  簡易会話入力画面関連                                                                              */
/*====================================================================================================*/
#include "application\pms_input.h"

static void PmsStartSingle( FIELDSYS_WORK* fsys )
{
	PMSI_PARAM*  param = PMSI_PARAM_Create( PMSI_MODE_SINGLE, PMSI_GUIDANCE_DEFAULT, fsys->savedata, HEAPID_BASE_DEBUG );
	Debug_ChangeScheneReq( fsys, PmsCallbackStart, PmsCallbackEnd, param );

}
static void PmsStartDouble( FIELDSYS_WORK* fsys )
{
	PMSI_PARAM*  param = PMSI_PARAM_Create( PMSI_MODE_DOUBLE, PMSI_GUIDANCE_DEFAULT, fsys->savedata, HEAPID_BASE_DEBUG );
	Debug_ChangeScheneReq( fsys, PmsCallbackStart, PmsCallbackEnd, param );
}
static void PmsStartSentence( FIELDSYS_WORK* fsys )
{
	PMSI_PARAM*  param = PMSI_PARAM_Create( PMSI_MODE_SENTENCE, PMSI_GUIDANCE_DEFAULT, fsys->savedata, HEAPID_BASE_DEBUG );
	Debug_ChangeScheneReq( fsys, PmsCallbackStart, PmsCallbackEnd, param );
}

static void PmsCallbackStart(FIELDSYS_WORK* fsys, void* wk)
{
	FieldProc_SetPmsInput(fsys, wk);
}

static void PmsCallbackEnd(FIELDSYS_WORK* fsys, void* wk)
{
	sys_FreeMemoryEz(wk);
}



/*====================================================================================================*/
/*  その他デバッグ機能                                                                                */
/*====================================================================================================*/
#include "poketool\monsno.h"
#include "poketool\boxdata.h"
#include "savedata\mystatus.h"
#include "gflib\strcode.h"
static void CurrentFullTool( FIELDSYS_WORK* fsys )
{
	BOX_DATA* boxdat = SaveData_GetBoxData(fsys->savedata);
	POKEMON_PASO_PARAM* ppp = sys_AllocMemory(HEAPID_BASE_DEBUG, PokemonPasoParamSizeGet() );
	if( ppp )
	{
		int i;
		STRBUF* playerName = MyStatus_CreateNameString( SaveData_GetMyStatus(fsys->savedata), HEAPID_BASE_DEBUG );

		PokePasoParaSet(ppp, MONSNO_YADON, 50, POW_RND, RND_NO_SET, 0, ID_NO_SET, 0);
		PokePasoParaPut( ppp, ID_PARA_oyaname_buf, playerName );

		for(i=0; i<BOX_MAX_POS; i++)
		{
			BOXDAT_PutPokemonPos( boxdat, BOXDAT_TRAYNUM_CURRENT, i, ppp );
		}
		STRBUF_Delete( playerName );
		sys_FreeMemoryEz(ppp);
	}

}
static void BoxFullTool( FIELDSYS_WORK* fsys )
{
	BOX_DATA* boxdat = SaveData_GetBoxData(fsys->savedata);
	POKEMON_PASO_PARAM* ppp = sys_AllocMemory(HEAPID_BASE_DEBUG, PokemonPasoParamSizeGet() );
	if( ppp )
	{
		int i, p;
		STRBUF* playerName = MyStatus_CreateNameString( SaveData_GetMyStatus(fsys->savedata), HEAPID_BASE_DEBUG );
		for(i=0; i<BOX_MAX_TRAY; i++)
		{
			for(p=0; p<BOX_MAX_POS; p++)
			{
				if(sys.cont&PAD_BUTTON_L){
					PokePasoParaSet(ppp, 1+gf_rand()%490, 50, POW_RND, RND_NO_SET, 0, ID_NO_SET, 0);
				}else{
					PokePasoParaSet(ppp, 80, 50, POW_RND, RND_NO_SET, 0, ID_NO_SET, 0);
				}
				PokePasoParaPut( ppp, ID_PARA_oyaname_buf, playerName );
				BOXDAT_PutPokemonPos( boxdat, i, p, ppp );
			}
		}
		STRBUF_Delete( playerName );
		sys_FreeMemoryEz(ppp);
	}

}

#include "sysflag.h"
// 簡易会話単語全部ＯＮ
static void PmsWordFullTool( FIELDSYS_WORK* fsys )
{
	// 図鑑全部ＯＮ
	{
		ZUKAN_WORK* zw;
		zw = SaveData_GetZukanWork( fsys->savedata );

		ZukanWork_SetZukanGetFlag( zw );
		ZukanWork_SetZenkokuZukanFlag( zw );
		MyStatus_SetDpZenkokuFlag( SaveData_GetMyStatus(fsys->savedata) );
		Debug_ZukanWork_Make( zw, 1, MONSNO_END, FALSE );
	}

	{
		// なんかいことば全部ＯＮ
		PMSW_SAVEDATA*  pmsw = SaveData_GetPMSW( fsys->savedata );
		int i;

		while( PMSW_CheckNankaiWordComplete(pmsw) == FALSE )
		{
			PMSW_SetNewNankaiWord( pmsw );
		}

		// 世界のあいさつ全部ＯＮ
		for(i=0; i<PMSW_AISATSU_HIDE_MAX; i++)
		{
			PMSW_SetAisatsuFlag( pmsw, i );
		}

	}


	// ゲームクリアフラグＯＮ
	{
		EVENTWORK* ev = SaveData_GetEventWork( fsys->savedata );
		MYSTATUS*  my = SaveData_GetMyStatus( fsys->savedata );

		SysFlag_GameClearSet( ev );
		MyStatus_SetDpClearFlag( my );
	}
}

//===================================================================================================
//===================================================================================================
extern GMEVENT_FUNC FieldEvent_GetFunc( GMEVENT_CONTROL * event );


static BOOL GMEVENT_ChangeScheneDebug(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK* fsys;
	DEBUG_CHANGESCHENE_WORK* wk;

//	if( PaletteFadeCheck() != 0 ){
//		return FALSE;
//	}

	fsys = FieldEvent_GetFieldSysWork(event);
	wk = FieldEvent_GetSpecialWork(event);

	switch( wk->seq ){
	case 0:
		FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );
		wk->seq++;
		/* fallthru */
	case 1:
		if( WIPE_SYS_EndCheck() )
		{
			wk->start_func( fsys, wk->gen_wk );
			wk->seq++;
		}
		break;
	case 2:
		if (FieldEvent_Cmd_WaitSubProcEnd(fsys) == FALSE) {
			FieldEvent_Cmd_SetMapProc(fsys);
			wk->seq++;
		}
		break;
	case 3:
		if (FieldEvent_Cmd_WaitMapProcStart(fsys) == FALSE) {
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
			wk->seq++;
		}
		break;
	case 4:
		if( WIPE_SYS_EndCheck() )
		{
			if( wk->end_func )
			{
				wk->end_func( fsys, wk->gen_wk );
			}
			sys_FreeMemoryEz(wk);
			return TRUE;
		}
		break;
	}
	return FALSE;
}


static void Debug_ChangeScheneReq( FIELDSYS_WORK* fsys, ScheneChangeCallback start_func, ScheneChangeCallback end_func, void* gen_wk )
{
	DEBUG_CHANGESCHENE_WORK* wk = sys_AllocMemory( HEAPID_BASE_DEBUG, sizeof(DEBUG_CHANGESCHENE_WORK) );
	if( wk != NULL )
	{
		wk->seq = 0;
		wk->start_func = start_func;
		wk->end_func = end_func;
		wk->gen_wk = gen_wk;
		FieldEvent_Set(fsys, GMEVENT_ChangeScheneDebug, wk);
	}
}

//===================================================================================================
// デバッグ用キー再生システム
//===================================================================================================


static const DEBUG_KEYPLAY_DATA* KeyPlayTable = NULL;
static u16 KeyPlaySeq = 0;
static u16 KeyPlayWait = 0;
static u16 KeyPlayRepeat = 0;

void DebugKeyPlay_Start( const DEBUG_KEYPLAY_DATA* tbl )
{
	KeyPlayTable = tbl;
	KeyPlaySeq = 0;
	KeyPlayWait = 0;
	KeyPlayRepeat = 0;
}

void DebugKeyPlay_Stop( void )
{
	KeyPlayTable = NULL;
}

BOOL DebugKeyPlay_IsPlaying( void )
{
	return KeyPlayTable != NULL;
}

void DebugKeyPlay_Main( void )
{
	if( KeyPlayTable )
	{
		if( KeyPlayWait == 0 )
		{
			const DEBUG_KEYPLAY_DATA* tbl = &KeyPlayTable[KeyPlaySeq];

			if( tbl->key != DEBUG_KEYPLAY_END )
			{
				sys.cont |= tbl->key;
				sys.trg |= tbl->key;
				sys.repeat |= tbl->key;
				KeyPlayWait = tbl->frames;
				if(KeyPlayRepeat >= tbl->repeat)
				{
					KeyPlayRepeat = 0;
					KeyPlaySeq++;
				}
				else
				{
					KeyPlayRepeat++;
				}
			}
			else
			{
				KeyPlaySeq = 0;
			}
		}
		else
		{
			KeyPlayWait--;
		}
	}
}


#endif
