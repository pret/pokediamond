//============================================================================================
/**
 * @file	demo_trade.c
 * @brief	ポケモン交換デモ（メイン）
 * @author	taya
 * @date	2006.04.07
 */
//============================================================================================
#include "common.h"
#include "gflib\bg_system.h"
#include "system\arc_util.h"
#include "system\wipe.h"
#include "system\render_oam.h"
#include "poketool\poke_tool.h"
#include "gflib\simple_3dgraphics.h"
#include "system\wordset.h"
#include "system\msgdata.h"
#include "system\softsprite.h"
#include "system\gra_tool.h"
#include "msgdata\msg.naix"
#include "msgdata\msg_demo_trade.h"
#include "battle/graphic/batt_bg_def.h"
#include "communication\wm_icon.h"


#include "demo_trade_common.h"


enum {
#if 0
//	DEBUG_CAMERA_TARGET_Y = 0xfff66c80,
//	DEBUG_CAMERA_TARGET_Z = 0xfff3b300,
//	DEBUG_MODEL_SCALE = 0xb0,

	DEBUG_CAMERA_TARGET_Y = 0xffffc100,
	DEBUG_CAMERA_TARGET_Z = 0xfff12800,
	DEBUG_MODEL_SCALE = 0x70,

#else
	DEBUG_CAMERA_TARGET_Y = 0,
	DEBUG_CAMERA_TARGET_Z = 0,
	DEBUG_MODEL_SCALE = FX32_ONE,
#endif

};

//-------------------------------------------------
/**
 *	各種定数
 */
//-------------------------------------------------
enum {
	HEAPSIZE_MAIN = 0x18000,
	HEAPSIZE_SUB = 0x18000,

	STRBUF_SIZE = 400,

	IRQ_FREE_QUEUE_MAX = 32,
};


//-------------------------------------------------
/**
 *	メインワーク
 */
//-------------------------------------------------
struct _DEMO_TRADE_WORK {
	const DEMO_TRADE_PARAM*  param;
	int   scene;

	GF_BGL_INI*       bgl;
	WORDSET*          wordset;
	MSGDATA_MANAGER*  mm;
	STRBUF*           strbuf;

	CLACT_SET_PTR				actSet;
	CLACT_U_EASYRENDER_DATA		renderData;
	TCB_PTR						VintrTask;
	BOOL			recvPoke_ReverseOkFlag;

	u16				sendPokeNumber;
	u16				recvPokeNumber;

	void*           sceneWork;
};

//-------------------------------------------------
/**
 *	各シーンの初期化・メイン・終了関数テーブル
 */
//-------------------------------------------------
typedef void* (*pSceneInitProc)(DEMO_TRADE_WORK*);
typedef BOOL  (*pSceneMainProc)(void*, int*);
typedef void  (*pSceneQuitProc)(void*);

static const struct {
	pSceneInitProc		init;
	pSceneMainProc		main;
	pSceneQuitProc		quit;
	int					playFlag;
}SubSceneProc[] = {
	{ DemoTrade_Scene0Init, DemoTrade_Scene0Main, DemoTrade_Scene0Quit, DEMO_TRADE_SEQ_FULL | DEMO_TRADE_SEQ_SEND_ONLY },
	{ DemoTrade_Scene1Init, DemoTrade_Scene1Main, DemoTrade_Scene1Quit, DEMO_TRADE_SEQ_FULL | DEMO_TRADE_SEQ_SEND_ONLY },
	{ DemoTrade_Scene2Init, DemoTrade_Scene2Main, DemoTrade_Scene2Quit, DEMO_TRADE_SEQ_FULL | DEMO_TRADE_SEQ_SEND_ONLY },
	{ DemoTrade_Scene3Init, DemoTrade_Scene3Main, DemoTrade_Scene3Quit, DEMO_TRADE_SEQ_FULL },
	{ DemoTrade_Scene4Init, DemoTrade_Scene4Main, DemoTrade_Scene4Quit, DEMO_TRADE_SEQ_FULL | DEMO_TRADE_SEQ_RECV_ONLY },
	{ DemoTrade_Scene5Init, DemoTrade_Scene5Main, DemoTrade_Scene5Quit, DEMO_TRADE_SEQ_FULL | DEMO_TRADE_SEQ_RECV_ONLY },
	{ DemoTrade_Scene6Init, DemoTrade_Scene6Main, DemoTrade_Scene6Quit, DEMO_TRADE_SEQ_FULL | DEMO_TRADE_SEQ_RECV_ONLY },
};


//==============================================================
// Prototype
//==============================================================
static BOOL check_reverse_ok( POKEMON_PASO_PARAM* ppp );
static void TradeDemo_VBlank(TCB_PTR tcb, void* wk_adrs);
static void WavePalAnmCtrlTask(TCB_PTR tcb, void* wk_adrs);
static void WavePalAnm_ChangeColorReq(DT_WAVE_PALANM_CTRL* wk, int prev_pos, int next_pos, int col);
static void setup_new_palanm_task( DT_WAVE_PALANM_CTRL* wk );
static void cleanup_palanm_task( DT_WAVE_PALANM_CTRL* wk, int id);
static void WavePalAnmTask(TCB_PTR tcb, void* wk_adrs);
static void ds_affine_task(TCB_PTR tcb, void* wk_adrs);
static void ds_affine_setvalue( DT_DSIMG_AFFINE_CTRL* wk );
static void IRQ_FreeReqInit( void );
static void IRQ_FreeReqFlush( void );



//------------------------------------------------------------------
/**
 * 交換デモPROC初期化処理
 *
 * @param   proc		
 * @param   seq		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
PROC_RESULT TradeDemoProc_Init( PROC * proc, int * seq )
{
	if( WIPE_SYS_EndCheck() )
	{
		DEMO_TRADE_WORK* wk;

		sys_CreateHeap(HEAPID_BASE_APP, HEAPID_DEMO_TRADE_MAIN, HEAPSIZE_MAIN );
		sys_CreateHeap(HEAPID_BASE_APP, HEAPID_DEMO_TRADE_SUB,  HEAPSIZE_SUB );

		IRQ_FreeReqInit();

		//サウンドデータロード
		Snd_DataSetByScene( SND_SCENE_TRADE, SEQ_DP_TRADE, 1 );	//交換デモ曲再生

		wk = PROC_AllocWork(proc, sizeof(DEMO_TRADE_WORK), HEAPID_DEMO_TRADE_MAIN);

		if(wk)
		{
			wk->param = PROC_GetParentWork(proc);
			wk->scene = 0;
			wk->bgl = GF_BGL_BglIniAlloc(HEAPID_DEMO_TRADE_MAIN);

			wk->strbuf = STRBUF_Create( STRBUF_SIZE, HEAPID_DEMO_TRADE_MAIN );
			wk->mm = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_demo_trade_dat, HEAPID_DEMO_TRADE_MAIN );
			wk->wordset = WORDSET_Create( HEAPID_DEMO_TRADE_MAIN );

			switch( wk->param->seqFlag ){
			case DEMO_TRADE_SEQ_FULL:
				WORDSET_RegisterPokeNickName( wk->wordset, 0, (POKEMON_PASO_PARAM*)(wk->param->sendPoke) );
				WORDSET_RegisterPokeNickName( wk->wordset, 1, (POKEMON_PASO_PARAM*)(wk->param->recvPoke) );
				WORDSET_RegisterPlayerName( wk->wordset, 2, wk->param->partner );
				wk->recvPoke_ReverseOkFlag = check_reverse_ok( (POKEMON_PASO_PARAM*)(wk->param->recvPoke) );
				break;
			case DEMO_TRADE_SEQ_SEND_ONLY:
				WORDSET_RegisterPokeNickName( wk->wordset, 0, (POKEMON_PASO_PARAM*)(wk->param->sendPoke) );
				break;
			case DEMO_TRADE_SEQ_RECV_ONLY:
				WORDSET_RegisterPokeNickName( wk->wordset, 1, (POKEMON_PASO_PARAM*)(wk->param->recvPoke) );
				wk->recvPoke_ReverseOkFlag = check_reverse_ok( (POKEMON_PASO_PARAM*)(wk->param->recvPoke) );
				break;
			}

			NNS_G2dInitOamManagerModule();
			REND_OAMInit( 0, 128, 0, 32, 1, 127, 0, 32, HEAPID_DEMO_TRADE_MAIN );
			wk->actSet = CLACT_U_SetEasyInit( 64, &wk->renderData, HEAPID_DEMO_TRADE_MAIN );
			CLACT_U_SetSubSurfaceMatrix( &(wk->renderData), 0, (192+DT_LCD_DIFF<<FX32_SHIFT) );

			wk->sendPokeNumber = PokePasoParaGet((POKEMON_PASO_PARAM*)(wk->param->sendPoke), ID_PARA_monsno, NULL);
			wk->recvPokeNumber = PokePasoParaGet((POKEMON_PASO_PARAM*)(wk->param->recvPoke), ID_PARA_monsno, NULL);

			wk->sceneWork = NULL;

			sys_VBlankFuncChange( NULL, NULL );
			sys_HBlankIntrStop();	//HBlank割り込み停止
			GF_Disp_GX_VisibleControlInit();
			GF_Disp_GXS_VisibleControlInit();
			GX_SetVisiblePlane( 0 );
			GXS_SetVisiblePlane( 0 );

			wk->VintrTask = PrintTCB_Add(TradeDemo_VBlank, wk, VINTR_TASKPRI_MAIN);
			wk->sceneWork = NULL;

		}
		return PROC_RES_FINISH;
	}

	return PROC_RES_CONTINUE;
}

// 反転表示して良いポケモンかチェック
static BOOL check_reverse_ok( POKEMON_PASO_PARAM* ppp )
{
	int monsno = PokePasoParaGet( ppp, ID_PARA_monsno, NULL );
	return ( PokePersonalParaGet( monsno, ID_PER_reverse ) == FALSE );
}

//------------------------------------------------------------------
/**
 * 交換デモPROC終了処理
 *
 * @param   proc		
 * @param   seq		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
PROC_RESULT TradeDemoProc_Quit( PROC * proc, int * seq )
{
	OSIntrMode	oldIntr;
	DEMO_TRADE_WORK* wk;

	oldIntr = OS_DisableInterrupts();
	wk = PROC_GetWork(proc);

	TCB_Delete( wk->VintrTask );

	WirelessIconEasyEnd();

	WORDSET_Delete( wk->wordset );
	MSGMAN_Delete( wk->mm );
	STRBUF_Delete( wk->strbuf );

	sys_FreeMemoryEz(wk->bgl);
	CLACT_DestSet( wk->actSet );
	REND_OAM_Delete();

	PROC_FreeWork(proc);

	sys_DeleteHeap(HEAPID_DEMO_TRADE_MAIN);
	sys_DeleteHeap(HEAPID_DEMO_TRADE_SUB);

	OS_RestoreInterrupts( oldIntr );

	return PROC_RES_FINISH;

}


#ifdef  PM_DEBUG
//#define DEBUG_KEY_MODE
#endif






//------------------------------------------------------------------
/**
 * 交換デモPROCメイン処理
 *
 * @param   proc		
 * @param   seq		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
PROC_RESULT TradeDemoProc_Main( PROC * proc, int * seq )
{
	DEMO_TRADE_WORK* wk = PROC_GetWork(proc);

	if( wk->scene < NELEMS(SubSceneProc) )
	{
		#ifdef DEBUG_KEY_MODE
		{
			#define QUIT_KEY_MASK	(PAD_BUTTON_X|PAD_BUTTON_Y)
			static int cnt = 0;
			if( (sys.cont & QUIT_KEY_MASK) == QUIT_KEY_MASK )
			{
				if(++cnt > 40)
				{
					cnt = 0;
					SubSceneProc[wk->scene].quit( wk->sceneWork );
					return PROC_RES_FINISH;
				}
			}
			else
			{
				cnt = 0;
			}
			if( sys.trg & PAD_BUTTON_SELECT )
			{
				SubSceneProc[wk->scene].quit( wk->sceneWork );
				wk->sceneWork = SubSceneProc[wk->scene].init( wk );
				*seq = 0;
			}
		}
		#endif



		if( SubSceneProc[wk->scene].playFlag & wk->param->seqFlag )
		{
			if( wk->sceneWork == NULL )
			{
				wk->sceneWork = SubSceneProc[wk->scene].init( wk );
			}

			if( SubSceneProc[wk->scene].main( wk->sceneWork, seq ) )
			{
				SubSceneProc[wk->scene].quit( wk->sceneWork );
				wk->sceneWork = NULL;

				#ifdef PM_DEBUG
				sys_CheckHeapFullReleased( HEAPID_DEMO_TRADE_SUB );
				#endif

				wk->scene++;
				(*seq) = 0;
				OS_TPrintf("SceneChangeA : %d\n", wk->scene);
			}
		}
		else
		{
			wk->scene++;
			(*seq) = 0;
			OS_TPrintf("SceneChangeB : %d\n", wk->scene);
		}

	// 割り込み中に受け付けたメモリ解放リクエストをここで処理する
		IRQ_FreeReqFlush();

		return PROC_RES_CONTINUE;
	}
	else
	{
		return PROC_RES_FINISH;
	}
}
//------------------------------------------------------------------
/**
 * V Blank
 */
//------------------------------------------------------------------
static void TradeDemo_VBlank(TCB_PTR tcb, void* wk_adrs)
{
	DEMO_TRADE_WORK* wk = wk_adrs;

	CLACT_Draw( wk->actSet );
	REND_OAMTrans();		// レンダラ共有OAMマネージャVram転送
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}




//======================================================================================
// 電波エフェクトタスク
//======================================================================================



enum {
	TASKPRI_WAVE_CTRL = 20,
	TASKPRI_WAVE_ANM  = 10,

	WAVE_ADD_INTERVAL = 30,
	WAVE_ANIMTASK_MAX = 8,

	WAVE_PALPOS_MAX = 15,
};


struct _DT_WAVE_PALANM_CTRL {
	u16  palDat[DT_WAVE_PAL_SIZE];
	TCB_PTR   ctrlTask;
	TCB_PTR   animTask[ WAVE_ANIMTASK_MAX ];
	BOOL*     runFlag;
	BOOL      end;
	int  req;
	int  timer;
	int  taskCnt;
	int  taskID;
	int  direction;
};

typedef struct {
	DT_WAVE_PALANM_CTRL* ctrlWork;
	int pos;
	int wait;
	int timer;
	int id;
	int direction;
}PALANM_TASK_WORK;


//------------------------------------------------------------------
/**
 * 電波パレットアニメ開始
 *（開始前に、正しくVRAMバンク設定をしておく必要がある）
 *（メイン、サブともBG3を拡張アフィン256x16パレットモードに設定）
 *
 * @param	BOOL*		稼働中はTRUE、終了後はFALSEをセットする
 *
 * @retval  DT_WAVE_PALANM_CTRL*	パレットアニメコントロールワーク
 */
//------------------------------------------------------------------
DT_WAVE_PALANM_CTRL* DT_WavePalAnm_Start( BOOL* runFlag, int direction )
{
	DT_WAVE_PALANM_CTRL* cwk = sys_AllocMemory( HEAPID_DEMO_TRADE_MAIN, sizeof(DT_WAVE_PALANM_CTRL) );
	*runFlag = FALSE;
	if( cwk )
	{
		NNSG2dPaletteData* palData;
		void *loadPtr;
		u32  alphaMask;
		int i;

		loadPtr = ArcUtil_PalDataGet( ARC_DEMO_TRADE_GRA, NARC_demo_trade_wave_nclr, &palData, HEAPID_DEMO_TRADE_MAIN );
		if( loadPtr )
		{
			MI_CpuFill16( cwk->palDat, 0x0000, DT_WAVE_PAL_SIZE );
			sys_FreeMemoryEz(loadPtr);
		}
		cwk->req = FALSE;
		cwk->end = FALSE;
		cwk->timer = 0;
		cwk->taskCnt = 0;
		cwk->runFlag = runFlag;
		cwk->taskID = 0;
		cwk->direction = direction;

		for(i=0; i<WAVE_ANIMTASK_MAX; i++)
		{
			cwk->animTask[i] = NULL;
		}

		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3, 16, 8);
		G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3, 16, 8);

		cwk->ctrlTask = TCB_Add( WavePalAnmCtrlTask, cwk, TASKPRI_WAVE_CTRL );
		if( cwk->ctrlTask )
		{
			OS_TPrintf("WaveAnm Start\n");
			*(cwk->runFlag) = TRUE;
		}
	}
	return cwk;
}
//------------------------------------------------------------------
/**
 * 電波パレットアニメ終了リクエスト（徐々に終了）
 *
 * @param   cwk		パレットアニメコントロールワーク
 *
 */
//------------------------------------------------------------------
void DT_WavePalAnm_StopReq( DT_WAVE_PALANM_CTRL* cwk )
{
	if( *(cwk->runFlag) == TRUE )
	{
		cwk->end = TRUE;
		OS_TPrintf("WaveAnm Stop Req\n");
	}
}
//------------------------------------------------------------------
/**
 * 電波パレットアニメ強制終了
 *
 * @param   cwk		パレットアニメコントロールワーク
 *
 */
//------------------------------------------------------------------
void DT_WavePalAnm_Quit( DT_WAVE_PALANM_CTRL* cwk )
{
	if( *(cwk->runFlag) == TRUE )
	{
		int i;
		for(i=0; i<WAVE_ANIMTASK_MAX; i++)
		{
			if( cwk->animTask[i] )
			{
				cleanup_palanm_task( cwk, i );
			}
		}
		*(cwk->runFlag) = FALSE;
		TCB_Delete(cwk->ctrlTask);
		sys_FreeMemoryEz(cwk);
		OS_TPrintf("WaveAnm Force Stop\n");
	}
}

//------------------------------------------------------------------
/**
 * 電波パレットアニメ
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void WavePalAnmCtrlTask( TCB_PTR tcb, void* wk_adrs )
{
	DT_WAVE_PALANM_CTRL* wk = wk_adrs;

	if( wk->end == FALSE )
	{
		if( --(wk->timer) <= 0 )
		{
			Snd_SePlay( SE_WAVE );
			wk->timer = WAVE_ADD_INTERVAL;
			setup_new_palanm_task( wk );
		}

		if( wk->req )
		{
			GX_BeginLoadBGExtPltt();
			GXS_BeginLoadBGExtPltt();

			DC_FlushRange( wk->palDat, DT_WAVE_PAL_SIZE );
			GX_LoadBGExtPltt( wk->palDat, 0x6000, DT_WAVE_PAL_SIZE );
			GXS_LoadBGExtPltt( wk->palDat, 0x6000, DT_WAVE_PAL_SIZE );

			GX_EndLoadBGExtPltt();
			GXS_EndLoadBGExtPltt();
			wk->req = FALSE;
		}
	}
	else
	{
		if( wk->req )
		{
			GX_BeginLoadBGExtPltt();
			GXS_BeginLoadBGExtPltt();

			DC_FlushRange( wk->palDat, DT_WAVE_PAL_SIZE );
			GX_LoadBGExtPltt( wk->palDat, 0x6000, DT_WAVE_PAL_SIZE );
			GXS_LoadBGExtPltt( wk->palDat, 0x6000, DT_WAVE_PAL_SIZE );

			GX_EndLoadBGExtPltt();
			GXS_EndLoadBGExtPltt();
			wk->req = FALSE;
		}

		if( wk->taskCnt == 0 )
		{
			*(wk->runFlag) = FALSE;
			sys_FreeMemoryEz( wk );
			TCB_Delete(tcb);
			OS_TPrintf("WaveAnm End\n");
		}
	}
}
static void WavePalAnm_ChangeColorReq(DT_WAVE_PALANM_CTRL* wk, int prev_pos, int next_pos, int col)
{
	if( prev_pos >= 0 && prev_pos < DT_WAVE_PAL_SIZE)
	{
		wk->palDat[prev_pos] = 0x0000;
	}
	if( next_pos >= 0 && next_pos < DT_WAVE_PAL_SIZE )
	{
		wk->palDat[next_pos] = col;
	}
	wk->req = TRUE;
}
static void setup_new_palanm_task( DT_WAVE_PALANM_CTRL* wk )
{
	if( wk->animTask[wk->taskID] == NULL )
	{
		PALANM_TASK_WORK* twk = sys_AllocMemory(HEAPID_DEMO_TRADE_MAIN, sizeof(PALANM_TASK_WORK));
		if(twk)
		{
			twk->ctrlWork = wk;

			if( wk->direction == 1 )
			{
				twk->pos = -1;
			}
			else
			{
				twk->pos = WAVE_PALPOS_MAX;
			}
			twk->timer = 0;
			twk->wait = 2;
			twk->id = wk->taskID;
			twk->direction = wk->direction;
			wk->animTask[wk->taskID] = TCB_Add( WavePalAnmTask, twk, TASKPRI_WAVE_ANM );
			if( wk->animTask[wk->taskID] )
			{
				wk->taskCnt++;
				if(++(wk->taskID)>=WAVE_ANIMTASK_MAX)
				{
					wk->taskID = 0;
				}
			}
			else
			{
				sys_FreeMemoryEz(twk);
			}
		}
	}
}
static void cleanup_palanm_task( DT_WAVE_PALANM_CTRL* wk, int id)
{
	if( wk->animTask[id] )
	{
		sys_FreeMemoryEz( TCB_GetWork(wk->animTask[id]) );
		TCB_Delete( wk->animTask[id] );
		wk->animTask[id] = NULL;
		wk->taskCnt--;
	}
}

static void WavePalAnmTask(TCB_PTR tcb, void* wk_adrs)
{
	PALANM_TASK_WORK* wk = wk_adrs;

	if( ++(wk->timer) >= wk->wait )
	{
		wk->timer = 0;

		if( wk->direction == 1 )
		{
			if( wk->pos+1 >= WAVE_PALPOS_MAX )
			{
				WavePalAnm_ChangeColorReq( wk->ctrlWork, wk->pos, wk->pos+1, 0x0000 );
				cleanup_palanm_task( wk->ctrlWork, wk->id );
			}
			else
			{
				WavePalAnm_ChangeColorReq( wk->ctrlWork, wk->pos, wk->pos+1, 0x7fff );
				wk->pos++;
			}
		}
		else
		{
			if( wk->pos < 0)
			{
				WavePalAnm_ChangeColorReq( wk->ctrlWork, wk->pos, wk->pos+1, 0x0000 );
				cleanup_palanm_task( wk->ctrlWork, wk->id );
			}
			else
			{
				WavePalAnm_ChangeColorReq( wk->ctrlWork, wk->pos+1, wk->pos, 0x7fff );
				wk->pos--;
			}
		}
	}
}

//======================================================================================
// DS拡縮エフェクト
//======================================================================================

//--------------------------------------------------------------
/**
 *	DSイメージ拡縮エフェクトワーク
 */
//--------------------------------------------------------------
struct _DT_DSIMG_AFFINE_CTRL	{
	GF_BGL_INI*		bgl;
	volatile BOOL*	endFlag;

	fx32     ratio;
	fx32     end_ratio;
	fx32     ratio_speed;
	fx32     ratio_ac;
	int      speed_sign;
	int      lcd_type;
	TCB_PTR  tcb;
};

//------------------------------------------------------------------
/**
 * DS拡縮開始（メイン、サブとも必要なBG設定を行っておくこと）
 *
 * @param   startRatio		初期拡縮率
 * @param   endRatio		最終拡縮率
 * @param   startSpeed		初期拡縮速度
 * @param   ac				拡縮加速度
 * @param   type			0:下画面中心  1:上画面中心
 * @param   endFlag			開始時にFALSE、終了時にTRUEをセットする
 *
 * @retval  DT_DSIMG_AFFINE_CTRL*		
 */
//------------------------------------------------------------------
DT_DSIMG_AFFINE_CTRL*  DT_DSAff_Start( GF_BGL_INI* bgl, fx32 startRatio, fx32 endRatio, fx32 startSpeed, fx32 ac, int type, volatile BOOL* endFlag )
{
	DT_DSIMG_AFFINE_CTRL* wk = sys_AllocMemory( HEAPID_DEMO_TRADE_MAIN, sizeof(DT_DSIMG_AFFINE_CTRL) );
	*endFlag = TRUE;

	if( wk )
	{
		wk->bgl = bgl;
		wk->ratio = startRatio;
		wk->end_ratio = endRatio;
		wk->ratio_speed = startSpeed;
		wk->ratio_ac = ac;
		wk->speed_sign = (startRatio < endRatio)? 0 : 1;
		wk->lcd_type = type;

		wk->endFlag = endFlag;
		*endFlag = FALSE;

		wk->tcb = VIntrTCB_Add( ds_affine_task, wk, TASKPRI_DEFAULT );
		if( wk->tcb )
		{
			OS_TPrintf("DS_Aff Start\n");
		}
		else
		{
			*endFlag = TRUE;
			sys_FreeMemoryEz(wk);
		}
	}

	return wk;
}
static void ds_affine_task(TCB_PTR tcb, void* wk_adrs)
{
	DT_DSIMG_AFFINE_CTRL* wk = wk_adrs;
	fx32 ratio_val;

	ratio_val = ((wk->ratio * wk->ratio_speed) >> FX32_SHIFT) / 32;

	switch( wk->speed_sign ){
	case 0:
		if( (wk->ratio+ratio_val) < wk->end_ratio )
		{
			wk->ratio += ratio_val;
		}
		else
		{
			wk->ratio = wk->end_ratio;
			*(wk->endFlag) = TRUE;
		}
		break;

	case 1:
		if( (wk->ratio - ratio_val) > wk->end_ratio )
		{
			wk->ratio -= ratio_val;
		}
		else
		{
			wk->ratio = wk->end_ratio;
			*(wk->endFlag) = TRUE;
		}
		break;
	}

	ds_affine_setvalue(wk);

	if( *(wk->endFlag) )
	{
		DemoTrade_IRQ_FreeReq( wk );
		TCB_Delete(tcb);
		OS_TPrintf("DS_Aff End ... flagAdrs:%08x\n", (u32)wk->endFlag);
	}
	else
	{
		wk->ratio_speed += wk->ratio_ac;
	}
}
static void ds_affine_setvalue( DT_DSIMG_AFFINE_CTRL* wk )
{
	static const int  aff_cy[] = {
		144, 56,
	};
	MtxFx22  mtx;

	mtx._00 = wk->ratio;
	mtx._01 = 1 << FX32_ONE;
	mtx._10 = 0;
	mtx._11 = wk->ratio;

	GF_BGL_AffineSet( wk->bgl, GF_BGL_FRAME2_M, &mtx, 128, aff_cy[ wk->lcd_type ] );
	GF_BGL_AffineSet( wk->bgl, GF_BGL_FRAME2_S, &mtx, 128, aff_cy[ wk->lcd_type ] );


}

//======================================================================================================
// ポケモングラフィックをBG領域に転送
//======================================================================================================

//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk			ワークポインタ
 * @param   id			0:送った方 1:送られてきた方
 * @param   bg_frame	
 * @param   palno		
 *
 */
//------------------------------------------------------------------
void DemoTrade_TransPokeGraphic( DEMO_TRADE_WORK* wk, int id, u32 bg_frame, u32 palno, BOOL animFlag )
{
	SOFT_SPRITE_ARC  arc;
	u32 palType;
	u32 bufSize;
	void*  tmpbuf;

	bufSize = (animFlag)?  0x20*200 : 0x20*100;
	tmpbuf = sys_AllocMemoryLo( HEAPID_DEMO_TRADE_MAIN, bufSize );

	if(tmpbuf)
	{
		CHANGES_INTO_DATA_RECT rect = {
			POKE_TEX_X,
			POKE_TEX_Y,
			POKE_TEX_W,
			POKE_TEX_H,
		};

		POKEMON_PASO_PARAM* ppp;
		BOOL fastFlag;
		u32  rand;
		u16  monsno;

		ppp = (POKEMON_PASO_PARAM*) ((id == 0)? wk->param->sendPoke : wk->param->recvPoke);
		fastFlag = PokePasoParaFastModeOn( ppp );

		PokeGraArcDataGetPPP( &arc, ppp, PARA_FRONT );
		rand = PokePasoParaGet( ppp, ID_PARA_personal_rnd, NULL );
		monsno = PokePasoParaGet( ppp, ID_PARA_monsno, NULL );

		if(animFlag){ rect.w *= 2; }

		Ex_ChangesInto_OAM_from_PokeTex_RC( arc.arc_no, arc.index_chr, HEAPID_DEMO_TRADE_MAIN, &rect, tmpbuf,
					 rand, animFlag, PARA_FRONT, monsno );
		DC_FlushRange( tmpbuf, bufSize );
		GF_BGL_LoadCharacter( wk->bgl, bg_frame, tmpbuf, bufSize, 0 );

//		ArcUtil_BgCharSet( arc.arc_no, arc.index_chr, wk->bgl, bg_frame, 0, 0, FALSE, HEAPID_DEMO_TRADE_MAIN );

		PokePasoParaFastModeOff( ppp, fastFlag );
		sys_FreeMemoryEz(tmpbuf);
	}

	palType = (bg_frame >= GF_BGL_FRAME0_S)? PALTYPE_SUB_BG : PALTYPE_MAIN_BG;
	ArcUtil_PalSet( arc.arc_no, arc.index_pal, palType, palno*0x20, 0x20, HEAPID_DEMO_TRADE_MAIN );

}

//------------------------------------------------------------------
/**
 * ポケモンBG表示用スクリーンを内部バッファに作成
 *
 * @param   wk		
 * @param   id			0:送るポケ  1:受け取るポケ
 * @param   bg_frame	
 * @param   palno		
 *
 */
//------------------------------------------------------------------
void DemoTrade_SetupPokeScreen( DEMO_TRADE_WORK* wk, int id, u32 bg_frame, u32 palno, u32 xpos, u32 ypos )
{
	void* loadPtr;
	NNSG2dScreenData* scrn;
	u32   datID;

	// 送る方は通常向き、受け取る方は反転。
	if( id == 0 )
	{
		datID = POKE_SCREEN_N_NSCR;
	}
	else
	{
		datID = ( wk->recvPoke_ReverseOkFlag )? POKE_SCREEN_F_NSCR : POKE_SCREEN_N_NSCR;
	}

	loadPtr = ArcUtil_ScrnDataGet( ARC_BATT_BG, datID, FALSE, &scrn, HEAPID_DEMO_TRADE_MAIN );
	if( loadPtr )
	{
//		GF_BGL_ScrWrite( wk->bgl, bg_frame, scrn->rawData, xpos, ypos, 10, 10 );
		GF_BGL_ScrWriteExpand( wk->bgl, bg_frame, xpos, ypos, 10, 10, 
					scrn->rawData, 0, 0, 32, 32 );
		GF_BGL_ScrPalChange( wk->bgl, bg_frame, xpos, ypos, 10, 10, palno );
		sys_FreeMemoryEz( loadPtr );
	}

//extern void* ArcUtil_ScrnDataGet(u32 fileIdx, u32 dataIdx, BOOL compressedFlag, NNSG2dScreenData** scrnData, u32 heapID);
/*

アークID　ARC_BATT_BG

通常　POKE_SCREEN_N_NSCR
反転　POKE_SCREEN_F_NSCR

です。


battle/graphic/batt_bg_def.h
*/
}





//======================================================================================================
// OAMアクター関連
//======================================================================================================
void DemoTrade_LoadCellAnimDatas( DEMO_TRADE_CELLANIM* clpack, u32 arcID, u32 cellDatID, u32 animDatID )
{
	clpack->cellLoadPtr = ArcUtil_CellBankDataGet(arcID, cellDatID, TRUE, &(clpack->cellData), HEAPID_DEMO_TRADE_SUB );
	clpack->animLoadPtr = ArcUtil_AnimBankDataGet(arcID, animDatID, TRUE, &(clpack->animData), HEAPID_DEMO_TRADE_SUB );
}
void DemoTrade_UnloadCellAnimDatas( DEMO_TRADE_CELLANIM* clpack )
{
	if( clpack->cellLoadPtr )
	{
		sys_FreeMemoryEz( clpack->cellLoadPtr );
		clpack->cellLoadPtr = NULL;
	}
	if( clpack->animLoadPtr )
	{
		sys_FreeMemoryEz( clpack->animLoadPtr );
		clpack->animLoadPtr = NULL;
	}
}
void DemoTrade_SetActHeader( CLACT_HEADER* header, DEMO_TRADE_CELLANIM* clpack, NNSG2dImageProxy* imgProxy, NNSG2dImagePaletteProxy* palProxy, u32 bgPri )
{
	header->pImageProxy = imgProxy;
	header->pPaletteProxy = palProxy;
	header->pCellBank = clpack->cellData;
	header->pAnimBank = clpack->animData;
	header->priority = bgPri;

	header->pCharData = NULL;
	header->pMCBank = NULL;
	header->pMCABank = NULL;
	header->flag = FALSE;
}

CLACT_WORK_PTR DemoTrade_AddActor( DEMO_TRADE_WORK* wk, CLACT_HEADER* header, u32 x, u32 y, u32 actPri, int drawArea)
{
	CLACT_WORK_PTR    act;
	CLACT_ADD_SIMPLE  add;

	add.ClActSet = wk->actSet;
	add.ClActHeader = header;
	add.mat.x = x * FX32_ONE;
	add.mat.y = y * FX32_ONE;
	add.mat.z = 0;
	add.pri = actPri;
	add.DrawArea = drawArea;
	add.heap = HEAPID_DEMO_TRADE_MAIN;

	act =  CLACT_AddSimple( &add );
	if( act )
	{
		CLACT_SetAnmFlag( act, TRUE );
		CLACT_SetAnmFrame( act, FX32_ONE );
	}
	return act;

}

//======================================================================================================
//======================================================================================================

GF_BGL_INI* DemoTrade_GetBgl( DEMO_TRADE_WORK* wk )
{
	return wk->bgl;
}

CLACT_SET_PTR DemoTrade_GetActSet( DEMO_TRADE_WORK* wk )
{
	return wk->actSet;
}

WORDSET*  DemoTrade_GetWordSet( DEMO_TRADE_WORK* wk )
{
	return wk->wordset;
}
STRBUF*  DemoTrade_GetStrBuf( DEMO_TRADE_WORK* wk )
{
	return wk->strbuf;
}
MSGDATA_MANAGER* DemoTrade_GetMsgManager( DEMO_TRADE_WORK* wk )
{
	return wk->mm;
}
const POKEMON_PASO_PARAM*  DemoTrade_GetSendPokeParam( DEMO_TRADE_WORK* wk )
{
	return wk->param->sendPoke;
}
const POKEMON_PASO_PARAM*  DemoTrade_GetRecvPokeParam( DEMO_TRADE_WORK* wk )
{
	return wk->param->recvPoke;
}
u32 DemoTrade_GetBGType( DEMO_TRADE_WORK* wk )
{
	return wk->param->bgType;
}

u16 DemoTrade_GetSendPokeNumber( DEMO_TRADE_WORK* wk )
{
	return wk->sendPokeNumber;
}
u16 DemoTrade_GetRecvPokeNumber( DEMO_TRADE_WORK* wk )
{
	return wk->recvPokeNumber;
}

WINTYPE DemoTrade_GetWinFrameType( DEMO_TRADE_WORK* wk )
{
	return CONFIG_GetWindowType( wk->param->config );
}

DEMO_TRADE_SEQFLAG DemoTrade_GetSeq( DEMO_TRADE_WORK* wk )
{
	return wk->param->seqFlag;
}


//======================================================================================================
//======================================================================================================
static int IRQ_FreeReqCount = 0;
static void* IRQ_FreeQueue[ IRQ_FREE_QUEUE_MAX ];

static void IRQ_FreeReqInit( void )
{
	IRQ_FreeReqCount = 0;
}


static void IRQ_FreeReqFlush( void )
{
	if( IRQ_FreeReqCount )
	{
		int i;
		for(i=0; i<IRQ_FreeReqCount; i++)
		{
			sys_FreeMemoryEz( IRQ_FreeQueue[i] );
		}
		IRQ_FreeReqCount = 0;
	}
}

//------------------------------------------------------------------
/**
 * 割り込み中にメモリ解放のリクエストを受け付ける
 *
 * @param   wk		
 * @param   adrs		
 *
 */
//------------------------------------------------------------------
void DemoTrade_IRQ_FreeReq( void* adrs )
{
	GF_ASSERT(IRQ_FreeReqCount < IRQ_FREE_QUEUE_MAX);
	IRQ_FreeQueue[ IRQ_FreeReqCount++ ] = adrs;
}


//======================================================================================================
//======================================================================================================
#ifdef PM_DEBUG


//------------------------------------------------------------------
/**
 * 数値調整（デバッグ用）
 *
 * @param   val		
 * @param   val_unit		
 * @param   key		
 * @param   str		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL DT_adjustValue32( s32* val , u32 val_unit, u32 key, const char* str )
{
	do {
		if( key & PAD_KEY_LEFT )
		{
			*val -= val_unit;
			break;
		}
		if( key & PAD_KEY_RIGHT )
		{
			*val += val_unit;
			break;
		}
		if( key & PAD_KEY_UP )
		{
			*val -= (val_unit * 10);
			break;
		}
		if( key & PAD_KEY_DOWN )
		{
			*val += (val_unit * 10);
			break;
		}

		return FALSE;

	}while(0);

	OS_TPrintf("%s = %08x\n", str, *val);
	return TRUE;
}
//------------------------------------------------------------------
/**
 * 数値調整16bit版（デバッグ用）
 *
 * @param   val		
 * @param   val_unit		
 * @param   key		
 * @param   str		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL DT_adjustValue16( s16* val , u16 val_unit, u32 key, const char* str )
{
	do {
		if( key & PAD_KEY_LEFT )
		{
			*val -= val_unit;
			break;
		}
		if( key & PAD_KEY_RIGHT )
		{
			*val += val_unit;
			break;
		}
		if( key & PAD_KEY_UP )
		{
			*val -= (val_unit * 10);
			break;
		}
		if( key & PAD_KEY_DOWN )
		{
			*val += (val_unit * 10);
			break;
		}

		return FALSE;

	}while(0);

	OS_TPrintf("%s = %04x\n", str, *val);
	return TRUE;
}


#endif
