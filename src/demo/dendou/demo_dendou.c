//============================================================================================
/**
 * @file	demo_dendou.c
 * @brief	ポケモン殿堂入りデモ
 * @author	taya
 * @date	2006.04.26
 */
//============================================================================================
#include "common.h"
#include "gflib\bg_system.h"
#include "gflib\simple_3dgraphics.h"
#include "gflib\strbuf.h"
#include "system\arc_util.h"
#include "system\clact_util.h"
#include "system\render_oam.h"
#include "system\wipe.h"
#include "system\gra_tool.h"
#include "system\wordset.h"
#include "system\fontproc.h"
#include "system\snd_tool.h"
#include "battle\graphic\batt_obj_def.h"
#include "battle\trtype_def.h"
#include "msgdata\msg.naix"
#include "msgdata\msg_dendou_demo.h"



#include  "demo\demo_dendou.h"
#include  "dendou_demo.naix"



#define FPS60


#ifdef  FPS60
#define	FRAME_RATIO	(2)
#else
#define	FRAME_RATIO	(1)
#endif

#define FRAMES(f)	((f)*FRAME_RATIO)

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------

enum {
	HEAPSIZE = 0x30000,
};

enum {
	TASKPRI_POKEMOVE,
	TASKPRI_WINMOVE,

	TASKPRI_CONFETTI_CTRL,

	TASKPRI_LIGHT_CTRL,
	TASKPRI_LIGHT,
	TASKPRI_LIGHT_CTRL_TAIL,

	TASKPRI_DRAW,
};

enum {
	POKE_ACT_CGX_BYTESIZE = 100 * 0x20,
	POKE_MOVEIN_FRAMES = FRAMES(14),
	MSG__MOVEOUT_FRAMES = FRAMES(14),
	PLAYER_MOVEIN_FRAMES = FRAMES(14),
	PLAYER_WINDOS_OPEN_FRAMES = FRAMES(6),
	PLAYER_WINDOW_CLOSE_FRAMES = FRAMES(12),
	POKE_DISPMOVE_FRAMES = FRAMES(4),

	PLAYER_OBJ_CHARPOS = 200*TEMOTI_POKEMAX*0x20,
	PLAYER_OBJ_PALPOS = TEMOTI_POKEMAX*0x20,
};


enum {
	PALNO_BG1,
	PALNO_WIN,
};

//--------------------------------------------------------------
/**
 *	ポケモンとの出会い方パターン（殿堂デモ独自）
 */
//--------------------------------------------------------------
typedef enum {
	POKE_MEET_CATCH,		///< ゲーム内で捕獲した
	POKE_MEET_BORN,			///< 自分でタマゴを孵した
	POKE_MEET_TRADE,		///< つうしん交換で
	POKE_MEET_KANTOU,		///< 赤緑から来た
	POKE_MEET_HOUEN,		///< ルビサファエメらから来た
	POKE_MEET_SOMEWHERE,	///< どこかとおいばしょ（コロシアム専用）
	POKE_MEET_OTHER,		///< 後は全部うんめい的な出会い
}POKE_MEET_PATTERN;

typedef struct {
	fx32	num;
	fx32	add;
	fx32	end;
	int		wait;
	BOOL	endFlag;
}FX_MOVE_NUMBER;





//------------------------------------------------------
/**
 *	WORK
 */
//------------------------------------------------------
typedef struct {
	int			seq;
	int			pokeCount;
	int			wait;

	DEMO_DENDOU_PARAM*	param;
	GF_BGL_INI*		bgl;
	GF_BGL_BMPWIN	win;

	CLACT_SET_PTR				actSet;
	CLACT_U_EASYRENDER_DATA		renderData;
	CLACT_WORK_PTR				actPoke[ TEMOTI_POKEMAX ];
	CLACT_WORK_PTR				actPlayer;
	void*						cellLoadPtr;
	void*						animLoadPtr;
	SOFT_SPRITE_ANIME			pokeAnim[ TEMOTI_POKEMAX ][ SS_ANM_SEQ_MAX ];
	int							pokeExistPos[ TEMOTI_POKEMAX ];
	int							pokeMonsNumber[ TEMOTI_POKEMAX ];
	u8							pokeCgxBuf[ POKE_ACT_CGX_BYTESIZE*2 ];

	GF_CAMERA_PTR	camera;
	VecFx32			cameraTarget;
	CAMERA_ANGLE	cameraAngle;

	TCB_PTR			vintrTask;
	TCB_PTR			lightTask;
	TCB_PTR			confettiTask;

	TCB_PTR			workTask[4];

	WORDSET*	wordset;
	STRBUF*		tmpbuf1;
	STRBUF*		tmpbuf2;
	MSGDATA_MANAGER*	msgMan;

}DEMO_WORK;



//==============================================================
// Prototype
//==============================================================
static BOOL mainproc_fadein( DEMO_WORK* wk );
static BOOL mainproc_fadeout( DEMO_WORK* wk );
static BOOL mainproc_poke( DEMO_WORK* wk );
static BOOL mainproc_player( DEMO_WORK* wk );
static BOOL mainproc_close( DEMO_WORK* wk );
static BOOL WaitWorkTaskEnd( DEMO_WORK* wk, int id );
static void DendouDemoVIntr( TCB_PTR tcb, void* wk_adrs );
static TCB_PTR  add_vtask( TCB_FUNC func, void* wk, int pri );
static void setup_bg( DEMO_WORK* wk );
static void cleanup_bg( DEMO_WORK* wk );
static void setup_3d_graphics( DEMO_WORK* wk );
static void setup_camera( DEMO_WORK* wk );
static void cleanup_3d_graphics( DEMO_WORK* wk );
static void setup_actors( DEMO_WORK* wk );
static void setup_poke_actors( DEMO_WORK* wk, NNSG2dCellDataBank* cell, NNSG2dAnimBankData* anim );
static void cleanup_actors( DEMO_WORK* wk );
static void StartPokeMoveInTask( DEMO_WORK* wk, int pos, int taskID );
static void PokeMoveInTask( TCB_PTR tcb, void* wk_adrs );
static void StartPlayerMoveInTask( DEMO_WORK* wk, int taskID );
static void PlayerMoveInTask( TCB_PTR tcb, void* wk_adrs );
static void HardWindowHMoveTask( TCB_PTR tcb, void* wk_adrs );
static void HardWindowVMoveTask( TCB_PTR tcb, void* wk_adrs );
static void HardWindowOpenTask( TCB_PTR tcb, void* wk_adrs );
static void HardWindowVResizeTask( TCB_PTR tcb, void* wk_adrs );
static void StartPokeViewWinMoveInTask( DEMO_WORK* wk, int pos, int taskID );
static void StartPokeViewWinMoveOutTask( DEMO_WORK* wk, int pos, int taskID );
static void StartPlayerViewWinMoveInTask( DEMO_WORK* wk, int taskID );
static void StartPlayerViewWinOpenTask( DEMO_WORK* wk, int taskID );
static void StartWindowCloseTask( DEMO_WORK* wk, int taskID );
static void StartPokeAnimTask( DEMO_WORK* wk, int pos, BOOL voicePlay, int taskID );
static void PokeAnimTask( TCB_PTR tcb, void* wk_adrs );
static void StartPrintPokeProfileTask( DEMO_WORK* wk, int pos, int taskID );
static void PrintPokeProfileTask( TCB_PTR tcb, void* wk_adrs );
static void StartScrollOutMsgTask( DEMO_WORK* wk, int taskID );
static void ScrollOutMsgTask( TCB_PTR tcb, void* wk_adrs );
static void PrintPlayerStatus( DEMO_WORK* wk );
static void StartDispAllPokeTask( DEMO_WORK* wk, int taskID );
static void DispAllPokeTask( TCB_PTR tcb, void* wk_adrs );
static TCB_PTR CreateLightCtrlTask( DEMO_WORK* wk );
static void LightCtrlTask( TCB_PTR tcb, void* wk_adrs );
static void LightCtrlTailTask( TCB_PTR tcb, void* wk_adrs );
static void AddLightTask( TCB_PTR  ctrlTask, fx16 px, fx32 angle );
static void inline adjust_vtx( VecFx16* vtx, u32 key, const char* str );
static void LightTask( TCB_PTR tcb, void* wk_adrs );
static void DrawLight( TCB_PTR tcb );
static void DeleteLightCtrlTask( TCB_PTR tcb );
static BOOL WaitLightTaskDelete( void );
static TCB_PTR CreateConfettiTask( DEMO_WORK* wk );
static void DeleteConfettiTask( TCB_PTR tcb );
static void StartConfettiDraw( TCB_PTR tcb );
static void ConfettiControlTask( TCB_PTR tcb, void* wk_adrs );
static void DrawConfetti( TCB_PTR tcb );
static void GetConfettiPos( TCB_PTR tcb, VecFx16* vtx, int id, int pos, int* color );
static void FxMoveNum_Set( FX_MOVE_NUMBER* num, fx32 start_num, fx32 end_num, int wait );
static fx32 FxMoveNum_Inc( FX_MOVE_NUMBER* num );
static BOOL FxMoveNum_CheckEnd( FX_MOVE_NUMBER* num );
static  POKE_MEET_PATTERN  GetPokeMeetPattern( DEMO_WORK* wk, POKEMON_PARAM* pp, const MYSTATUS* player );





PROC_RESULT  DemoDendouPROC_Init( PROC* proc, int* seq )
{
	DEMO_WORK* wk;

	sys_VBlankFuncChange(NULL, NULL);
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_DENDOU_DEMO, HEAPSIZE );

	wk = PROC_AllocWork( proc, sizeof(DEMO_WORK), HEAPID_DENDOU_DEMO );

	wk->param = PROC_GetParentWork( proc );

	wk->msgMan = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_dendou_demo_dat, HEAPID_DENDOU_DEMO );
	wk->tmpbuf1 = STRBUF_Create( 500, HEAPID_DENDOU_DEMO );
	wk->tmpbuf2 = STRBUF_Create( 500, HEAPID_DENDOU_DEMO );
	wk->wordset = WORDSET_Create( HEAPID_DENDOU_DEMO );

	{
		int i, max;

		wk->pokeCount = 0;
		max = PokeParty_GetPokeCount( wk->param->party );
		for( i=0; i<max; i++ )
		{
			if( PokeParaGet(PokeParty_GetMemberPointer(wk->param->party, i), ID_PARA_tamago_flag, NULL) == FALSE )
			{
				wk->pokeExistPos[ wk->pokeCount ] = i;
				wk->pokeCount++;
			}
		}
	}

	setup_bg( wk );
	setup_3d_graphics( wk );
	setup_actors( wk );

	wk->confettiTask = NULL;
	wk->lightTask = CreateLightCtrlTask( wk );
	AddLightTask( wk->lightTask, -FX16_CONST(0.714f), FX32_CONST(20) );
	AddLightTask( wk->lightTask, -FX16_CONST(0.429f), FX32_CONST(60) );
	AddLightTask( wk->lightTask, -FX16_CONST(0.143f), FX32_CONST(40) );
	AddLightTask( wk->lightTask,  FX16_CONST(0.143f), FX32_CONST(140) );
	AddLightTask( wk->lightTask,  FX16_CONST(0.429f), FX32_CONST(120) );
	AddLightTask( wk->lightTask,  FX16_CONST(0.714f), FX32_CONST(160) );

	wk->confettiTask = CreateConfettiTask( wk );
//	StartConfettiDraw( wk->confettiTask );

	GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB );

	wk->seq = 0;
	wk->vintrTask = add_vtask( DendouDemoVIntr, wk, TASKPRI_DRAW );

	//サウンドデータロード
	Snd_DataSetByScene( SND_SCENE_DENDOU, SEQ_BLD_EV_DENDO2, 1 );	//殿堂デモ曲再生

	return PROC_RES_FINISH;
}


PROC_RESULT  DemoDendouPROC_Quit( PROC* proc, int* seq )
{
	switch( *seq ){
	case 0:
		{
			DEMO_WORK* wk = PROC_GetWork( proc );

			TCB_Delete( wk->vintrTask );

			DeleteConfettiTask( wk->confettiTask );
			DeleteLightCtrlTask( wk->lightTask );

			cleanup_actors( wk );
			cleanup_3d_graphics( wk );
			cleanup_bg( wk );

			WORDSET_Delete( wk->wordset );
			STRBUF_Delete( wk->tmpbuf1 );
			STRBUF_Delete( wk->tmpbuf2 );
			MSGMAN_Delete( wk->msgMan );

			PROC_FreeWork( proc );
			sys_DeleteHeap( HEAPID_DENDOU_DEMO );
		}
		(*seq)++;
		break;
	case 1:
		if( WaitLightTaskDelete() )
		{
			return PROC_RES_FINISH;
		}
	}
	return PROC_RES_CONTINUE;
}


PROC_RESULT  DemoDendouPROC_Main( PROC* proc, int* seq )
{
	static BOOL (* const proc_tbl[])(DEMO_WORK*) = {
		mainproc_fadein,
		mainproc_poke,
		mainproc_player,
		mainproc_close,
		mainproc_fadeout,
	};

	DEMO_WORK* wk = PROC_GetWork( proc );


	if( (*seq) < NELEMS(proc_tbl) )
	{
		if( proc_tbl[(*seq)](wk) )
		{
			wk->seq = 0;
			wk->wait = 0;
			(*seq)++;
		}

		return PROC_RES_CONTINUE;
	}
	return PROC_RES_FINISH;
}

static BOOL mainproc_fadein( DEMO_WORK* wk )
{
	switch( wk->seq ){
	case 0:
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, 16, 1, HEAPID_DENDOU_DEMO );
		wk->seq++;
		break;
	case 1:
		if( WIPE_SYS_EndCheck() )
		{
			return TRUE;
		}
	}
	return FALSE;
}
static BOOL mainproc_fadeout( DEMO_WORK* wk )
{
	switch( wk->seq ){
	case 0:
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, 2, 1, HEAPID_DENDOU_DEMO );
		Snd_BgmFadeOut( 0, 30 );
		wk->seq++;
		break;
	case 1:
		if( WIPE_SYS_EndCheck() && (Snd_FadeCheck() == 0) )
		{
			return TRUE;
		}
	}
	return FALSE;
}

static BOOL mainproc_poke( DEMO_WORK* wk )
{
	enum {
		TASKID_POKE_MOVE = 0,
		TASKID_WINDOW_MOVEIN = 1,

		TASKID_POKE_ANIM = 0,
		TASKID_PRINT = 1,

		TASKID_MSG_OUT = 0,
		TASKID_WINDOW_MOVEOUT = 1,
	};
	enum {
		WAIT_MOVE_ANIM = 20,
		WAIT_ANIM_OUT = 30,
		WAIT_NEXT_POKE = 30,
	};
	static int pos = 0;

	if( wk->wait )
	{
		wk->wait--;
		return FALSE;
	}

	switch( wk->seq ){
	case 0:
		pos = 0;
		wk->seq++;
		/* fallthru */
	case 1:
		StartPokeMoveInTask( wk, pos, TASKID_POKE_MOVE );
		StartPokeViewWinMoveInTask( wk, pos, TASKID_WINDOW_MOVEIN );
		wk->seq++;
		break;
	case 2:
		if( WaitWorkTaskEnd( wk, TASKID_POKE_MOVE ) )
		{
			wk->wait = WAIT_MOVE_ANIM;
			wk->seq++;
		}
		break;
	case 3:
		StartPokeAnimTask( wk, pos, TRUE, TASKID_POKE_ANIM );
		StartPrintPokeProfileTask( wk, pos, TASKID_PRINT );
		wk->seq++;
		break;
	case 4:
		if( WaitWorkTaskEnd(wk, TASKID_POKE_ANIM) && WaitWorkTaskEnd(wk, TASKID_PRINT) )
		{
			wk->wait = WAIT_ANIM_OUT;
			wk->seq++;
		}
		break;
	case 5:
		StartScrollOutMsgTask( wk, TASKID_MSG_OUT );
		StartPokeViewWinMoveOutTask( wk, pos, TASKID_WINDOW_MOVEOUT );
		wk->seq++;
		break;
	case 6:
		if( WaitWorkTaskEnd(wk, TASKID_MSG_OUT) )
		{
			CLACT_SetDrawFlag( wk->actPoke[pos], FALSE );

			if(++pos < wk->pokeCount)
			{
				wk->wait = WAIT_NEXT_POKE;
				wk->seq = 1;
			}
			else
			{
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}

static BOOL mainproc_player( DEMO_WORK* wk )
{
	enum {
		TASKID_PLAYER_MOVE = 0,
		TASKID_WINDOW_MOVE = 1,

		TASKID_WINDOW_OPEN = 0,

		TASKID_POKE_DISP = 0,
	};
	enum {
		WAIT_WINOPEN_PRINT = 20,
		WAIT_PRINT_POKEDISP = 20,
	};

	if( wk->wait )
	{
		wk->wait--;
		return FALSE;
	}

	switch( wk->seq ){
	case 0:
		ArcUtil_ScrnSet(ARC_DENDOU_DEMO, NARC_dendou_demo_bg_player_lz_nscr, wk->bgl, GF_BGL_FRAME3_M, 0, 0, TRUE, HEAPID_DENDOU_DEMO );
		wk->seq++;
		break;

	case 1:
		StartPlayerMoveInTask( wk, TASKID_PLAYER_MOVE );
		StartPlayerViewWinMoveInTask( wk, TASKID_WINDOW_MOVE );
		wk->seq++;
		break;

	case 2:
		if(	WaitWorkTaskEnd( wk, TASKID_PLAYER_MOVE )
		&&	WaitWorkTaskEnd( wk, TASKID_WINDOW_MOVE )
		){
			wk->wait = WAIT_WINOPEN_PRINT;
			wk->seq++;
		}
		break;

	case 3:
		StartPlayerViewWinOpenTask( wk, TASKID_WINDOW_OPEN );
		wk->seq++;
		break;

	case 4:
		if( WaitWorkTaskEnd( wk, TASKID_WINDOW_OPEN ) )
		{
			PrintPlayerStatus( wk );
			wk->wait = WAIT_PRINT_POKEDISP;
			wk->seq++;
		}
		break;

	case 5:
		StartDispAllPokeTask( wk, TASKID_POKE_DISP );
		wk->seq++;
		break;

	case 6:
		if( WaitWorkTaskEnd( wk, TASKID_POKE_DISP ) )
		{
			wk->wait = 20;
			wk->seq++;
		}
		break;
	case 7:
		StartConfettiDraw( wk->confettiTask );
		wk->seq++;
		break;
	case 8:
		if( sys.trg & (PAD_BUTTON_A | PAD_BUTTON_B) )
		{
			return TRUE;
		}
		break;
	}
	return FALSE;
}

static BOOL mainproc_close( DEMO_WORK* wk )
{
	switch( wk->seq ){
	case 0:
		StartWindowCloseTask( wk, 0 );
		wk->seq++;
		break;
	case 1:
		if( WaitWorkTaskEnd( wk, 0 ) )
		{
			return TRUE;
		}
	}
	return FALSE;
}


static BOOL WaitWorkTaskEnd( DEMO_WORK* wk, int id )
{
	return wk->workTask[id] == NULL;
}


//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
static void DendouDemoVIntr( TCB_PTR tcb, void* wk_adrs )
{
	DEMO_WORK* wk = wk_adrs;

	if( G3X_IsGeometryBusy() )
	{
		return;
	}

	G3X_Reset();

	NNS_G3dGePushMtx();
	{
		DrawLight( wk->lightTask );
	}
	NNS_G3dGePopMtx(1);

	NNS_G3dGePushMtx();
	{
		DrawConfetti( wk->confettiTask );
	}
	NNS_G3dGePopMtx(1);

	G3_SwapBuffers( GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z );

	CLACT_Draw( wk->actSet );
	REND_OAMTrans();
}
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
static TCB_PTR  add_vtask( TCB_FUNC func, void* wk, int pri )
{
	#ifdef  FPS60
	return VIntrTCB_Add( func, wk, pri );
	#else
	return VWaitTCB_Add( func, wk, pri );
	#endif
}


//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
static void setup_bg( DEMO_WORK* wk )
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

	// BG1 = 文字描画レイヤー
	static const GF_BGL_BGCNT_HEADER header1 = {
		0, 0, 0x1000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x512, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x10000,
		GX_BG_EXTPLTT_01, 0, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	// BG2 = 真っ黒レイヤー
	static const GF_BGL_BGCNT_HEADER header2 = {
		0, 0, 0, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x18000,
		GX_BG_EXTPLTT_01, 1, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	// BG3 = 背景レイヤー
	static const GF_BGL_BGCNT_HEADER header3 = {
		0, 0, 0, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x18000,
		GX_BG_EXTPLTT_01, 3, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_DENDOU_DEMO );

	GF_Disp_SetBank( &SetBankData );
	GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);
	GF_BGL_InitBG( &BGsys_data );

	GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME1_M, &header1, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME2_M, &header2, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME3_M, &header3, GF_BGL_MODE_TEXT );

	GF_BGL_CharFill( wk->bgl, GF_BGL_FRAME1_M, 0x00, 1, 0 );
	GF_BGL_ScrFill( wk->bgl, GF_BGL_FRAME1_M, 0x0000, 0, 0, 32, 32, 0 );
	GF_BGL_BmpWinAdd( wk->bgl, &(wk->win), GF_BGL_FRAME1_M, 0, 0, 32, 24, PALNO_WIN, 1 );
	GF_BGL_BmpWinDataFill( &(wk->win), 0 );
	GF_BGL_BmpWinCgxOn( &(wk->win) );
	GF_BGL_BmpWinMakeScrn( &wk->win );


	ArcUtil_BgCharSet(ARC_DENDOU_DEMO, NARC_dendou_demo_bg_poke_lz_ncgr, wk->bgl, GF_BGL_FRAME3_M, 0, 0, TRUE, HEAPID_DENDOU_DEMO );
	ArcUtil_ScrnSet(ARC_DENDOU_DEMO, NARC_dendou_demo_bg_poke_lz_nscr, wk->bgl, GF_BGL_FRAME3_M, 0, 0, TRUE, HEAPID_DENDOU_DEMO );
	ArcUtil_PalSet(ARC_DENDOU_DEMO, NARC_dendou_demo_bg_nclr, PALTYPE_MAIN_BG, 0, 0x60, HEAPID_DENDOU_DEMO );

	ArcUtil_ScrnSet(ARC_DENDOU_DEMO, NARC_dendou_demo_bg_mask_lz_nscr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, TRUE, HEAPID_DENDOU_DEMO );

	GF_BGL_LoadScreenReq( wk->bgl, GF_BGL_FRAME1_M );

	G2_SetWnd0Position( 0, 0, 0, 0 );
	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_ALL ^ GX_WND_PLANEMASK_BG2, TRUE );
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_ALL, TRUE );
	GX_SetVisibleWnd(GX_WNDMASK_W0);
}


static void cleanup_bg( DEMO_WORK* wk )
{
	GX_SetVisibleWnd(GX_WNDMASK_NONE);

	GF_BGL_BmpWinDel( &(wk->win) );

	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME3_M );
	sys_FreeMemoryEz( wk->bgl );
}


//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

static void setup_3d_graphics( DEMO_WORK* wk )
{
	// NitroSystem:３Ｄエンジンの初期化
	NNS_G3dInit();
	// マトリクススタックの初期化
    G3X_InitMtxStack();

	// 各種描画モードの設定(シェード＆アンチエイリアス＆半透明)
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(TRUE);

	G3X_AlphaTest(FALSE, 0);	// アルファテスト　　オフ
	G3X_AlphaBlend(TRUE);		// アルファブレンド　オン

	// クリアカラーの設定
    G3X_SetClearColor(GX_RGB(0, 0, 0),	// clear color
                      0,				// clear alpha
                      0x7fff,			// clear depth
                      63,				// clear polygon ID
                      FALSE				// fog
                      );

	// ジオメトリエンジン起動後必ず呼ばれなければならない
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);

	// ビューポートの設定
    G3_ViewPort(0, 0, 255, 191);

    NNS_GfdInitFrmTexVramManager(1, TRUE);
    NNS_GfdInitFrmPlttVramManager(0x4000, TRUE);


	// ３Ｄ使用面の設定(表示＆プライオリティー)
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority(2);
    G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE, GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ, 0, 0 );


	setup_camera( wk );
}

static void setup_camera( DEMO_WORK* wk )
{
	enum {
		CAMERA_PEARCE	= FX_GET_ROTA_NUM(22),
		CAMERA_DISTANCE	= (5 << FX32_SHIFT)
	};
	VecFx32 up;

	wk->camera = GFC_AllocCamera( HEAPID_DENDOU_DEMO );

	wk->cameraTarget.x = 0;
	wk->cameraTarget.y = 0;
	wk->cameraTarget.z = 0;

	wk->cameraAngle.x = FX_GET_ROTA_NUM(0);
	wk->cameraAngle.y = FX_GET_ROTA_NUM(0);
	wk->cameraAngle.z = FX_GET_ROTA_NUM(0);

	GFC_InitCameraTDA( 
			&(wk->cameraTarget),
			CAMERA_DISTANCE,
			&(wk->cameraAngle),
			CAMERA_PEARCE,
			GF_CAMERA_PERSPECTIV,
			TRUE,	
			wk->camera
	);


	up.x = 0;
	up.y = FX32_ONE;
	up.z = 0;
	GFC_SetCamUp( &up, wk->camera );

	GFC_AttachCamera( wk->camera );

	GFC_SetCameraClip( (1<<FX32_SHIFT), (500<<FX32_SHIFT), wk->camera );

}

static void cleanup_3d_graphics( DEMO_WORK* wk )
{
	GFC_FreeCamera( wk->camera );
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
static void setup_actors( DEMO_WORK* wk )
{
	NNSG2dCellDataBank* cell;
	NNSG2dAnimBankData* anim;

	NNS_G2dInitOamManagerModule();
	REND_OAMInit( 0, 128, 0, 32, 0, 128, 0, 32, HEAPID_DENDOU_DEMO );
	wk->actSet = CLACT_U_SetEasyInit( 64, &wk->renderData, HEAPID_DENDOU_DEMO );

	wk->cellLoadPtr = ArcUtil_CellBankDataGet(ARC_BATT_OBJ, POKE_OAM_NCER, FALSE, &cell, HEAPID_DENDOU_DEMO);
	wk->animLoadPtr = ArcUtil_AnimBankDataGet(ARC_BATT_OBJ, POKE_OAM_NANR, FALSE, &anim, HEAPID_DENDOU_DEMO);

	setup_poke_actors( wk, cell, anim );

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}

static void setup_poke_actors( DEMO_WORK* wk, NNSG2dCellDataBank* cell, NNSG2dAnimBankData* anim )
{
	static const CHANGES_INTO_DATA_RECT rect[2] = {
		{ POKE_TEX_X, POKE_TEX_Y, POKE_TEX_W, POKE_TEX_H },
		{ POKE_TEX_X+POKE_TEX_W, POKE_TEX_Y, POKE_TEX_W, POKE_TEX_H },
	};
	SOFT_SPRITE_ARC  arc;
	CLACT_HEADER			header;
	CLACT_ADD_SIMPLE		add;
	NNSG2dImageProxy		imgProxy;
	NNSG2dImagePaletteProxy	palProxy;
	NNSG2dCharacterData*	charData;
	NNSG2dPaletteData*		palData;
	void*	cgxLoadPtr;
	void*	palLoadPtr;
	const POKEMON_PARAM* pp;
	int i, p;

	header.pCharData = NULL;
	header.pMCBank = NULL;
	header.pMCABank = NULL;
	header.flag = FALSE;
	header.pCellBank = cell;
	header.pAnimBank = anim;
	header.priority = 3;
	header.pImageProxy = &imgProxy;
	header.pPaletteProxy = &palProxy;

	add.ClActSet = wk->actSet;
	add.ClActHeader = &header;
	VEC_Set( &(add.mat), 0, 0, 0 );
	add.DrawArea = NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap = HEAPID_DENDOU_DEMO;


	cgxLoadPtr = ArcUtil_CharDataGet( ARC_BATT_OBJ, POKE_OAM_NCGR, FALSE, &charData, HEAPID_DENDOU_DEMO );
	palLoadPtr = ArcUtil_PalDataGet( ARC_BATT_OBJ, POKE_OAM_NCLR, &palData, HEAPID_DENDOU_DEMO );

	for(i=0; i<wk->pokeCount; i++)
	{
		NNS_G2dInitImageProxy(&imgProxy);
		NNS_G2dInitImagePaletteProxy(&palProxy);
		NNS_G2dLoadImage1DMapping( charData, i*2*POKE_ACT_CGX_BYTESIZE, NNS_G2D_VRAM_TYPE_2DMAIN, &imgProxy );
		NNS_G2dLoadPalette( palData, i*0x20, NNS_G2D_VRAM_TYPE_2DMAIN, &palProxy );

		add.pri = 1+i;
		wk->actPoke[i] = CLACT_AddSimple( &add );
		CLACT_SetDrawFlag( wk->actPoke[i], FALSE );

		// 
		pp = PokeParty_GetMemberPointer( wk->param->party, wk->pokeExistPos[i] );

		PokeGraArcDataGetPP( &arc, (POKEMON_PARAM*)pp, PARA_FRONT );
		wk->pokeMonsNumber[i] = PokeParaGet((POKEMON_PARAM*)pp, ID_PARA_monsno, NULL);

		Ex_ChangesInto_OAM_from_PokeTex_RC( arc.arc_no, arc.index_chr, HEAPID_DENDOU_DEMO, &rect[0], wk->pokeCgxBuf,
			PokeParaGet((POKEMON_PARAM*)pp, ID_PARA_personal_rnd, NULL),
			TRUE,
			PARA_FRONT,
			wk->pokeMonsNumber[i]
		);
		DC_FlushRange( wk->pokeCgxBuf, POKE_ACT_CGX_BYTESIZE );
		GX_LoadOBJ( wk->pokeCgxBuf, i*2*POKE_ACT_CGX_BYTESIZE, POKE_ACT_CGX_BYTESIZE );

		Ex_ChangesInto_OAM_from_PokeTex_RC( arc.arc_no, arc.index_chr, HEAPID_DENDOU_DEMO, &rect[1], wk->pokeCgxBuf,
			PokeParaGet((POKEMON_PARAM*)pp, ID_PARA_personal_rnd, NULL),
			TRUE,
			PARA_FRONT,
			wk->pokeMonsNumber[i]
		);
//		ChangesInto_OAM_from_PokeTex_RC( arc.arc_no, arc.index_chr, HEAPID_DENDOU_DEMO, &rect[1], wk->pokeCgxBuf );
		DC_FlushRange( wk->pokeCgxBuf, POKE_ACT_CGX_BYTESIZE );
		GX_LoadOBJ( wk->pokeCgxBuf, i*2*POKE_ACT_CGX_BYTESIZE+POKE_ACT_CGX_BYTESIZE, POKE_ACT_CGX_BYTESIZE );

		ArcUtil_PalSet( arc.arc_no, arc.index_pal, PALTYPE_MAIN_OBJ, i*0x20, 0x20, HEAPID_DENDOU_DEMO );

		PokeAnmDataSet( &wk->pokeAnim[i][0], wk->pokeMonsNumber[i] );
	}

	NNS_G2dInitImageProxy(&imgProxy);
	NNS_G2dInitImagePaletteProxy(&palProxy);
	NNS_G2dLoadImage1DMapping( charData, PLAYER_OBJ_CHARPOS, NNS_G2D_VRAM_TYPE_2DMAIN, &imgProxy );
	NNS_G2dLoadPalette( palData, PLAYER_OBJ_PALPOS, NNS_G2D_VRAM_TYPE_2DMAIN, &palProxy );
	TrTypeGraArcDataGet( &arc, ((MyStatus_GetMySex(wk->param->player)==PM_FEMALE)? TRTYPE_GIRL : TRTYPE_BOY) );
	ChangesInto_OAM_from_PokeTex_RC( arc.arc_no, arc.index_chr, HEAPID_DENDOU_DEMO, &rect[0], wk->pokeCgxBuf );
	DC_FlushRange( wk->pokeCgxBuf, POKE_ACT_CGX_BYTESIZE );
	GX_LoadOBJ( wk->pokeCgxBuf, PLAYER_OBJ_CHARPOS, POKE_ACT_CGX_BYTESIZE );
	ArcUtil_PalSet( arc.arc_no, arc.index_pal, PALTYPE_MAIN_OBJ, PLAYER_OBJ_PALPOS, 0x20, HEAPID_DENDOU_DEMO );

	add.pri = 0;
	wk->actPlayer = CLACT_AddSimple( &add );
	CLACT_SetDrawFlag( wk->actPlayer, FALSE );

	sys_FreeMemoryEz( palLoadPtr );
	sys_FreeMemoryEz( cgxLoadPtr );

}


static void cleanup_actors( DEMO_WORK* wk )
{
	int i;

	for(i=0; i<wk->pokeCount; i++)
	{
		CLACT_Delete( wk->actPoke[i] );
	}

	sys_FreeMemoryEz( wk->animLoadPtr );
	sys_FreeMemoryEz( wk->cellLoadPtr );
	CLACT_DestSet( wk->actSet );
	REND_OAM_Delete();
}
//-----------------------------------------------------------------------------------------------
// VIntrタスク用のワークメモリを解放するための仕組み
//-----------------------------------------------------------------------------------------------
typedef struct {
	void*		taskWork;
	TCB_PTR*	pMine;
}VINTR_TASKFREE_WORK;

 static void VIntrFreeTask( TCB_PTR tcb, void* wk_adrs )
{
	VINTR_TASKFREE_WORK* wk = wk_adrs;

	*(wk->pMine) = NULL;
	sys_FreeMemoryEz( wk->taskWork );
	TCB_Delete( tcb );
}

 static void SetVIntrTaskFreeWork( VINTR_TASKFREE_WORK* wk, void* taskWork, TCB_PTR* pTask )
{
	wk->taskWork = taskWork;
	wk->pMine = pTask;
}

 static void VIntrTaskFreeReq( VINTR_TASKFREE_WORK* wk )
{
	VWaitTCB_Add( VIntrFreeTask, wk, 0 );
}


//-----------------------------------------------------------------------------------------------
// ポケモンが定位置まで移動する動き
//-----------------------------------------------------------------------------------------------
enum {
	POKEIN_MOVE_DISTANCE = FX32_CONST(120),
	POKEIN_ENDXPOS_L =  FX32_CONST(72),
	POKEIN_ENDXPOS_R = FX32_CONST(184),
	POKEIN_STARTXPOS_L = POKEIN_ENDXPOS_L + POKEIN_MOVE_DISTANCE,
	POKEIN_STARTXPOS_R = POKEIN_ENDXPOS_R - POKEIN_MOVE_DISTANCE,
	POKEIN_YPOS = FX32_CONST(96),
};

typedef struct {
	VINTR_TASKFREE_WORK	tfw;
	CLACT_WORK_PTR		act;
	VecFx32				actPos;
	FX_MOVE_NUMBER		x;
}POKE_MOVEIN_WORK;

static void StartPokeMoveInTask( DEMO_WORK* wk, int pos, int taskID )
{
	static const struct {
		fx32  start;
		fx32  end;
	}move_pos[] = {
		{ POKEIN_STARTXPOS_L, POKEIN_ENDXPOS_L },
		{ POKEIN_STARTXPOS_R, POKEIN_ENDXPOS_R },
	};

	POKE_MOVEIN_WORK*  twk;
	int ptn;

	twk = sys_AllocMemory( HEAPID_DENDOU_DEMO, sizeof(POKE_MOVEIN_WORK) );
	ptn = pos&1;

	SetVIntrTaskFreeWork( &twk->tfw, twk, &(wk->workTask[taskID]) );

	twk->act = wk->actPoke[pos];
	FxMoveNum_Set( &twk->x, move_pos[ptn].start, move_pos[ptn].end, POKE_MOVEIN_FRAMES );

	VEC_Set( &twk->actPos, move_pos[ptn].start, POKEIN_YPOS, 0 );
	CLACT_SetMatrix( twk->act, &twk->actPos );
	CLACT_SetDrawFlag( twk->act, TRUE );

	wk->workTask[taskID] = add_vtask( PokeMoveInTask, twk, TASKPRI_POKEMOVE );
}

static void PokeMoveInTask( TCB_PTR tcb, void* wk_adrs )
{
	POKE_MOVEIN_WORK* wk = wk_adrs;

	wk->actPos.x = FxMoveNum_Inc( &wk->x );
	CLACT_SetMatrix( wk->act, &wk->actPos );
	if( FxMoveNum_CheckEnd( &wk->x ) )
	{
		VIntrTaskFreeReq( &wk->tfw );
		TCB_Delete(tcb);
	}
}

//-----------------------------------------------------------------------------------------------
// プレイヤー画像が動いて入ってくる
//-----------------------------------------------------------------------------------------------
enum {
	PLAYER_START_YPOS = 192+40,
	PLAYER_END_YPOS = 104,
	PLAYER_XPOS = 128,
};

typedef struct {
	VINTR_TASKFREE_WORK	tfw;
	CLACT_WORK_PTR	act;
	VecFx32			actPos;
	FX_MOVE_NUMBER	y;
}PLAYER_MOVEIN_WORK;

static void StartPlayerMoveInTask( DEMO_WORK* wk, int taskID )
{
	PLAYER_MOVEIN_WORK*  twk;

	twk = sys_AllocMemory( HEAPID_DENDOU_DEMO, sizeof(PLAYER_MOVEIN_WORK) );

	SetVIntrTaskFreeWork( &twk->tfw, twk, &(wk->workTask[taskID]) );

	twk->act = wk->actPlayer;
	FxMoveNum_Set( &twk->y, FX32_CONST(PLAYER_START_YPOS), FX32_CONST(PLAYER_END_YPOS), PLAYER_MOVEIN_FRAMES );

	VEC_Set( &twk->actPos, FX32_CONST(PLAYER_XPOS), FX32_CONST(PLAYER_START_YPOS), 0 );
	CLACT_SetMatrix( twk->act, &twk->actPos );
	CLACT_SetDrawFlag( twk->act, TRUE );

	wk->workTask[taskID] = add_vtask( PlayerMoveInTask, twk, TASKPRI_POKEMOVE );
}

static void PlayerMoveInTask( TCB_PTR tcb, void* wk_adrs )
{
	PLAYER_MOVEIN_WORK* wk = wk_adrs;

	wk->actPos.y = FxMoveNum_Inc( &wk->y );
	CLACT_SetMatrix( wk->act, &wk->actPos );
	if( FxMoveNum_CheckEnd( &wk->y ) )
	{
		VIntrTaskFreeReq( &wk->tfw );
		TCB_Delete(tcb);
	}
}


//-----------------------------------------------------------------------------------------------
// ハードウィンドウ枠移動
//-----------------------------------------------------------------------------------------------
enum {
	PVWIN_WIDTH = 96,
	PVWIN_HEIGHT = 128,

	PVWIN_LEFT_START_XORG = -PVWIN_WIDTH,
	PVWIN_LEFT_END_XORG   = 24,
	PVWIN_RIGHT_START_XORG = 256+PVWIN_WIDTH,
	PVWIN_RIGHT_END_XORG   = 136,

	PVWIN_YORG = 32,
	PVWIN_END_YORG = -160,

	PVWIN_PLAYER_HEIGHT = 144,
	PVWIN_PLAYER_LEFT = 88,
	PVWIN_PLAYER_RIGHT = 168,
	PVWIN_PLAYER_START_YORG = -PVWIN_PLAYER_HEIGHT,
	PVWIN_PLAYER_END_YORG = 24,


};



typedef struct {
	VINTR_TASKFREE_WORK	tfw;
	FX_MOVE_NUMBER	pos;
}HARDWIN_HMOVE_WORK;

typedef struct {
	VINTR_TASKFREE_WORK	tfw;
	FX_MOVE_NUMBER	pos;
	int				left;
	int				right;
	int				height;
}HARDWIN_VMOVE_WORK;

typedef struct {
	VINTR_TASKFREE_WORK	tfw;
	FX_MOVE_NUMBER	left;
	FX_MOVE_NUMBER	right;
	int				top;
	int				bottom;
}HARDWIN_OPEN_WORK;

typedef struct {
	VINTR_TASKFREE_WORK	tfw;
	FX_MOVE_NUMBER	top;
	FX_MOVE_NUMBER	bottom;
	int				left;
	int				right;
}HARDWIN_V_RESIZE_WORK;



//------------------------------------------------------
// 水平移動タスク
//------------------------------------------------------
static void HardWindowHMoveTask( TCB_PTR tcb, void* wk_adrs )
{
	HARDWIN_HMOVE_WORK* wk = wk_adrs;
	int left, right;

	left = (FxMoveNum_Inc( &(wk->pos) ) >> FX32_SHIFT);
	right = left + PVWIN_WIDTH;

	if( left < 0 ){ left = 0; }
	if( right < 0 ){ right = 0; }
	if( left > 255 ){
		left = right = 0;
	}
	if( right > 255 )
	{
		right = 255;
	}

	G2_SetWnd0Position( left, PVWIN_YORG, right, PVWIN_YORG+PVWIN_HEIGHT );
	if( FxMoveNum_CheckEnd( &(wk->pos) ) )
	{
		VIntrTaskFreeReq( &wk->tfw );
		TCB_Delete( tcb );
	}
}
//------------------------------------------------------
// 垂直移動タスク
//------------------------------------------------------
static void HardWindowVMoveTask( TCB_PTR tcb, void* wk_adrs )
{
	HARDWIN_VMOVE_WORK* wk = wk_adrs;
	int top, bottom;

	top = (FxMoveNum_Inc( &(wk->pos) ) >> FX32_SHIFT);
	bottom = top + wk->height;

	if( top < 0 ){ top = 0; }
	if( bottom < 0 ){ bottom = 0; }
	if( top > 191 )
	{
		top = bottom = 0;
	}
	if( bottom > 191 )
	{
		bottom = 191;
	}

	G2_SetWnd0Position( wk->left, top, wk->right, bottom );
	if( FxMoveNum_CheckEnd( &(wk->pos) ) )
	{
		VIntrTaskFreeReq( &wk->tfw );
		TCB_Delete( tcb );
	}
}
//------------------------------------------------------
// 横幅変更タスク
//------------------------------------------------------
static void HardWindowOpenTask( TCB_PTR tcb, void* wk_adrs )
{
	HARDWIN_OPEN_WORK* wk = wk_adrs;
	int left, right;

	left = FxMoveNum_Inc( &wk->left ) >> FX32_SHIFT;
	right = FxMoveNum_Inc( &wk->right ) >> FX32_SHIFT;

	if( left < 0 ){ left = 0; }
	if( right < 0 ){ right = 0; }
	if( left > 255 ){
		left = right = 0;
	}
	if( right > 255 )
	{
		right = 255;
	}

	G2_SetWnd0Position( left, wk->top, right, wk->bottom );
	if( FxMoveNum_CheckEnd( &(wk->left) ) )
	{
		VIntrTaskFreeReq( &wk->tfw );
		TCB_Delete( tcb );
	}
}
//------------------------------------------------------
// 縦幅変更タスク
//------------------------------------------------------
static void HardWindowVResizeTask( TCB_PTR tcb, void* wk_adrs )
{
	HARDWIN_V_RESIZE_WORK* wk = wk_adrs;
	int top, bottom;

	top = FxMoveNum_Inc( &wk->top ) >> FX32_SHIFT;
	bottom = FxMoveNum_Inc( &wk->bottom ) >> FX32_SHIFT;

	if( top < 0 ){ top = 0; }
	if( bottom < 0 ){ bottom = 0; }
	if( top > 191 ){
		top = bottom = 0;
	}
	if( bottom > 191 )
	{
		bottom = 191;
	}

	G2_SetWnd0Position( wk->left, top, wk->right, bottom );
	if( FxMoveNum_CheckEnd( &(wk->top) ) )
	{
		VIntrTaskFreeReq( &wk->tfw );
		TCB_Delete( tcb );
	}
}


//------------------------------------------------------
// ポケモン表示ウィンドウフレームイン
//------------------------------------------------------
static void StartPokeViewWinMoveInTask( DEMO_WORK* wk, int pos, int taskID )
{
	static const struct {
		fx32  start;
		fx32  end;
	}move_pos[] = {
		{ FX32_CONST(PVWIN_LEFT_START_XORG),  FX32_CONST(PVWIN_LEFT_END_XORG) },
		{ FX32_CONST(PVWIN_RIGHT_START_XORG), FX32_CONST(PVWIN_RIGHT_END_XORG) },
	};

	HARDWIN_HMOVE_WORK* twk;
	int ptn;

	ptn = pos & 1;
	twk = sys_AllocMemory( HEAPID_DENDOU_DEMO, sizeof(HARDWIN_HMOVE_WORK) );

	SetVIntrTaskFreeWork( &twk->tfw, twk, &(wk->workTask[taskID]) );
	FxMoveNum_Set( &twk->pos, move_pos[ptn].start, move_pos[ptn].end, MSG__MOVEOUT_FRAMES );


	wk->workTask[taskID] = add_vtask( HardWindowHMoveTask, twk, TASKPRI_WINMOVE );

//	G2_SetWnd0Position( 0, PVWIN_YORG, 0, PVWIN_YORG+PVWIN_WIDTH );
}

//------------------------------------------------------
// ポケモン表示ウィンドウフレームアウト
//------------------------------------------------------
static void StartPokeViewWinMoveOutTask( DEMO_WORK* wk, int pos, int taskID )
{
	static const int win_left[] = {
		PVWIN_LEFT_END_XORG, PVWIN_RIGHT_END_XORG,
	};

	HARDWIN_VMOVE_WORK* twk;
	int ptn;

	ptn = pos & 1;
	twk = sys_AllocMemory( HEAPID_DENDOU_DEMO, sizeof(HARDWIN_VMOVE_WORK) );

	SetVIntrTaskFreeWork( &twk->tfw, twk, &(wk->workTask[taskID]) );

	FxMoveNum_Set( &twk->pos, FX32_CONST(PVWIN_YORG), FX32_CONST(PVWIN_END_YORG), POKE_MOVEIN_FRAMES );
	twk->left = win_left[ptn];
	twk->right = twk->left + PVWIN_WIDTH;
	twk->height = PVWIN_HEIGHT;

	wk->workTask[taskID] = add_vtask( HardWindowVMoveTask, twk, TASKPRI_WINMOVE );

//	G2_SetWnd0Position( 0, PVWIN_YORG, 0, PVWIN_YORG+PVWIN_WIDTH );
}

//------------------------------------------------------
// プレイヤー表示ウィンドウフレームイン
//------------------------------------------------------
static void StartPlayerViewWinMoveInTask( DEMO_WORK* wk, int taskID )
{
	HARDWIN_VMOVE_WORK* twk;

	twk = sys_AllocMemory( HEAPID_DENDOU_DEMO, sizeof(HARDWIN_VMOVE_WORK) );

	SetVIntrTaskFreeWork( &twk->tfw, twk, &(wk->workTask[taskID]) );

	FxMoveNum_Set( &twk->pos, FX32_CONST(PVWIN_PLAYER_START_YORG), FX32_CONST(PVWIN_PLAYER_END_YORG), PLAYER_MOVEIN_FRAMES );
	twk->left = PVWIN_PLAYER_LEFT;
	twk->right = PVWIN_PLAYER_RIGHT;
	twk->height = PVWIN_PLAYER_HEIGHT;

	wk->workTask[taskID] = add_vtask( HardWindowVMoveTask, twk, TASKPRI_WINMOVE );
}

//------------------------------------------------------
// プレイヤー表示ウィンドウ横いっぱいに広がる
//------------------------------------------------------
static void StartPlayerViewWinOpenTask( DEMO_WORK* wk, int taskID )
{
	HARDWIN_OPEN_WORK* twk = sys_AllocMemory( HEAPID_DENDOU_DEMO, sizeof(HARDWIN_OPEN_WORK) );

	SetVIntrTaskFreeWork( &twk->tfw, twk, &(wk->workTask[taskID]) );

	FxMoveNum_Set( &twk->left, FX32_CONST(PVWIN_PLAYER_LEFT), 0, PLAYER_WINDOS_OPEN_FRAMES );
	FxMoveNum_Set( &twk->right, FX32_CONST(PVWIN_PLAYER_RIGHT), FX32_CONST(255), PLAYER_WINDOS_OPEN_FRAMES );
	twk->top = PVWIN_PLAYER_END_YORG;
	twk->bottom = twk->top + PVWIN_PLAYER_HEIGHT;

	wk->workTask[taskID] = add_vtask( HardWindowOpenTask, twk, TASKPRI_WINMOVE );
}

static void StartWindowCloseTask( DEMO_WORK* wk, int taskID )
{
	HARDWIN_V_RESIZE_WORK* twk = sys_AllocMemory( HEAPID_DENDOU_DEMO, sizeof(HARDWIN_V_RESIZE_WORK) );

	SetVIntrTaskFreeWork( &twk->tfw, twk, &(wk->workTask[taskID]) );

	FxMoveNum_Set( &twk->top, FX32_CONST(PVWIN_PLAYER_END_YORG), FX32_CONST(96), PLAYER_WINDOW_CLOSE_FRAMES );
	FxMoveNum_Set( &twk->bottom, FX32_CONST(PVWIN_PLAYER_END_YORG+PVWIN_PLAYER_HEIGHT), FX32_CONST(96), PLAYER_WINDOW_CLOSE_FRAMES );
	twk->left = 0;
	twk->right = 255;

	wk->workTask[taskID] = add_vtask( HardWindowVResizeTask, twk, TASKPRI_WINMOVE );
}

//-----------------------------------------------------------------------------------------------
// ポケモンアニメーション
//-----------------------------------------------------------------------------------------------

typedef struct {
	VINTR_TASKFREE_WORK	tfw;
	CLACT_WORK_PTR	act;
	const SOFT_SPRITE_ANIME*	anim;
	SOFT_SPRITE_ANIME_WORK		anim_wk;
	NNSG2dImageProxy	imgProxy[2];
	BOOL			voicePlay;
	int				monsno;
}POKE_ANIM_WORK;

static void StartPokeAnimTask( DEMO_WORK* wk, int pos, BOOL voicePlay, int taskID )
{
	POKE_ANIM_WORK*  twk;
	int ptn;

	twk = sys_AllocMemory( HEAPID_DENDOU_DEMO, sizeof(POKE_ANIM_WORK) );

	SetVIntrTaskFreeWork( &twk->tfw, twk, &(wk->workTask[taskID]) );

	twk->act = wk->actPoke[pos];
	twk->anim = &wk->pokeAnim[pos][0];
	SoftSprite_SetupAnimeWork( &twk->anim_wk, twk->anim );

	twk->voicePlay = voicePlay;
	twk->monsno = wk->pokeMonsNumber[ pos ];
	twk->imgProxy[0] = *CLACT_ImageProxyGet( twk->act );
	twk->imgProxy[1] = twk->imgProxy[0];
	NNS_G2dInitImageProxy(&twk->imgProxy[1]);
	NNS_G2dSetImageLocation( &(twk->imgProxy[1]), NNS_G2D_VRAM_TYPE_2DMAIN,
		 pos*2*POKE_ACT_CGX_BYTESIZE+POKE_ACT_CGX_BYTESIZE );

	wk->workTask[taskID] = TCB_Add( PokeAnimTask, twk, 0 );
}

static void PokeAnimTask( TCB_PTR tcb, void* wk_adrs )
{
	POKE_ANIM_WORK* wk = wk_adrs;
	int pat;

	if( wk->voicePlay )
	{
		Snd_PMVoicePlay( wk->monsno );
		wk->voicePlay = FALSE;
	}

	pat = SoftSprite_FwdAnime( &wk->anim_wk );

	if( pat >= 0 )
	{
		CLACT_ImageProxySet( wk->act, &wk->imgProxy[pat] );
	}
	else
	{
		VIntrTaskFreeReq( &wk->tfw );
		TCB_Delete(tcb);
	}
}

//-----------------------------------------------------------------------------------------------
// ○○で出会ったなどのポケモンプロフィールプリント
//-----------------------------------------------------------------------------------------------
enum {
	PRINT_POKEAREA_WIDTH = 15*8,
	PRINT_AREA_WIDTH = 256-PRINT_POKEAREA_WIDTH,	/// BitmapWindow自体は１画面分あるが、書ける領域はこれだけ

	PRINT_CONG_YPOS = 16*1,

	PRINT_NICKNAME_YPOS = 16*3,
	PRINT_POKE_PROF_YPOS = 16*4,

	PRINT_PLAYER_YPOS = 16*6,
	PRINT_MEET_YPOS = 16*7,

};


typedef struct {
	VINTR_TASKFREE_WORK	tfw;
	DEMO_WORK*		mainWork;
	GF_BGL_INI*		bgl;
	GF_BGL_BMPWIN*	win;
	WORDSET*			wordset;
	STRBUF*				bufTmp;
	STRBUF*				bufPrint;
	MSGDATA_MANAGER*	msgMan;
	POKEMON_PARAM*		pp;
	const MYSTATUS*		player;
	int				writeXofs;
	int				wait;
	int				seq;
}PRINT_PROFILE_WORK;

static void StartPrintPokeProfileTask( DEMO_WORK* wk, int pos, int taskID )
{
	PRINT_PROFILE_WORK*  twk;
	int ptn;

	twk = sys_AllocMemory( HEAPID_DENDOU_DEMO, sizeof(PRINT_PROFILE_WORK) );

	SetVIntrTaskFreeWork( &twk->tfw, twk, &(wk->workTask[taskID]) );
	twk->mainWork = wk;
	twk->bgl = wk->bgl;
	twk->win = &(wk->win);
	twk->wordset = wk->wordset;
	twk->bufTmp = wk->tmpbuf1;
	twk->bufPrint = wk->tmpbuf2;
	twk->msgMan = wk->msgMan;
	twk->writeXofs = ( pos & 1 )? 0 : PRINT_POKEAREA_WIDTH;
	twk->pp = PokeParty_GetMemberPointer( wk->param->party, wk->pokeExistPos[pos] );
	twk->player = wk->param->player;
	twk->wait = 0;
	twk->seq  = 0;

	wk->workTask[taskID] = TCB_Add( PrintPokeProfileTask, twk, 0 );
}

 static void print_poke_prof( PRINT_PROFILE_WORK* wk, int ypos )
{
	int i, lines, xpos;

	lines = STRBUF_GetLines( wk->bufPrint );
	for(i=0; i<lines; i++)
	{
		STRBUF_CopyLine( wk->bufTmp, wk->bufPrint, i );
		xpos = (PRINT_AREA_WIDTH - FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->bufTmp, 0 )) / 2;
		GF_STR_PrintColor( wk->win, FONT_SYSTEM, wk->bufTmp, wk->writeXofs+xpos, ypos+i*16, MSG_NO_PUT,
				GF_PRINTCOLOR_MAKE(1,2,0), NULL );
	}
}

 static void setup_poke_prof_str( PRINT_PROFILE_WORK* wk )
{
	WORDSET_RegisterPokeMonsName( wk->wordset, 0, PPPPointerGet(wk->pp) );
	WORDSET_RegisterNumber( wk->wordset, 1, PokeParaLevelCalc(wk->pp), 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );

	switch( PokeSexGet(wk->pp) ){
	case PARA_MALE:		MSGMAN_GetString( wk->msgMan, str_dendemo_poke_male, wk->bufTmp ); break;
	case PARA_FEMALE:	MSGMAN_GetString( wk->msgMan, str_dendemo_poke_female, wk->bufTmp ); break;
	case PARA_UNK:
	default:			MSGMAN_GetString( wk->msgMan, str_dendemo_poke_neutral, wk->bufTmp ); break;
	}

	WORDSET_ExpandStr( wk->wordset, wk->bufPrint, wk->bufTmp );
}

 static void setup_poke_meet_str( PRINT_PROFILE_WORK* wk )
{
	int ptn = GetPokeMeetPattern(wk->mainWork, wk->pp, wk->player);

	switch( ptn ){
	case POKE_MEET_CATCH:
	case POKE_MEET_BORN:
		WORDSET_RegisterPlaceName( wk->wordset, 0, PokeParaGet(wk->pp, ID_PARA_birth_place, NULL) );
		break;
	}

	MSGMAN_GetString( wk->msgMan, str_dendemo_meet0+ptn, wk->bufTmp );
	WORDSET_ExpandStr( wk->wordset, wk->bufPrint, wk->bufTmp );
}

static void PrintPokeProfileTask( TCB_PTR tcb, void* wk_adrs )
{
	enum {
		PRINT_INTERVAL = 20,
	};

	PRINT_PROFILE_WORK* wk = wk_adrs;

	if( wk->wait )
	{
		wk->wait--;
		return;
	}

	switch( wk->seq ){
	case 0:
		MSGMAN_GetString( wk->msgMan, str_dendemo_cong0, wk->bufPrint );
		print_poke_prof( wk, PRINT_CONG_YPOS );

		GF_BGL_BmpWinCgxOn( wk->win );
		wk->wait = PRINT_INTERVAL;
		wk->seq++;
		break;
	case 1:
		PokeParaGet( wk->pp, ID_PARA_nickname_buf, wk->bufPrint );
		print_poke_prof( wk, PRINT_NICKNAME_YPOS );

		setup_poke_prof_str( wk );
		print_poke_prof( wk, PRINT_POKE_PROF_YPOS );

		GF_BGL_BmpWinCgxOn( wk->win );
		wk->wait = PRINT_INTERVAL;
		wk->seq++;
		break;
	case 2:
		WORDSET_RegisterPokeOyaName( wk->wordset, 0, PPPPointerGet(wk->pp) );
		MSGMAN_GetString( wk->msgMan, str_dendemo_player0, wk->bufTmp );
		WORDSET_ExpandStr( wk->wordset, wk->bufPrint, wk->bufTmp );
		print_poke_prof( wk, PRINT_PLAYER_YPOS );

		setup_poke_meet_str( wk );
		print_poke_prof( wk, PRINT_MEET_YPOS );

		GF_BGL_BmpWinCgxOn( wk->win );
		wk->seq++;
		break;
	case 3:
		VIntrTaskFreeReq( &wk->tfw );
		TCB_Delete(tcb);
		break;
	}
}




//-----------------------------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------------------------
typedef struct {
	VINTR_TASKFREE_WORK	tfw;
	DEMO_WORK*		mainWork;
	GF_BGL_INI*		bgl;
	GF_BGL_BMPWIN*	win;
	FX_MOVE_NUMBER	ypos;
	int				seq;
	int				bgFrame;
}MSG_SCROLL_WORK;

static void StartScrollOutMsgTask( DEMO_WORK* wk, int taskID )
{
	MSG_SCROLL_WORK*  twk;
	int ptn;

	twk = sys_AllocMemory( HEAPID_DENDOU_DEMO, sizeof(MSG_SCROLL_WORK) );

	SetVIntrTaskFreeWork( &twk->tfw, twk, &(wk->workTask[taskID]) );

	twk->bgl = wk->bgl;
	twk->win = &(wk->win);
	twk->bgFrame = GF_BGL_FRAME1_M;
	twk->seq = 0;

	FxMoveNum_Set( &(twk->ypos), FX32_CONST(0), FX32_CONST(256), MSG__MOVEOUT_FRAMES );

	wk->workTask[taskID] = add_vtask( ScrollOutMsgTask, twk, TASKPRI_POKEMOVE );
}

static void ScrollOutMsgTask( TCB_PTR tcb, void* wk_adrs )
{
	MSG_SCROLL_WORK*  wk = wk_adrs;

	switch( wk->seq ){
	case 0:
		{
			int ypos = FxMoveNum_Inc( &wk->ypos ) >> FX32_SHIFT;
			GF_BGL_ScrollSet( wk->bgl, wk->bgFrame, GF_BGL_SCROLL_Y_SET, ypos );
			if( FxMoveNum_CheckEnd( &wk->ypos ) )
			{
				wk->seq++;
			}
		}
		break;

	case 1:
		GF_BGL_BmpWinDataFill( wk->win, 0 );
		GF_BGL_BmpWinCgxOn( wk->win );
		wk->seq++;
		break;

	case 2:
		GF_BGL_ScrollSet( wk->bgl, wk->bgFrame, GF_BGL_SCROLL_Y_SET, 0 );
		VIntrTaskFreeReq( &wk->tfw );
		TCB_Delete( tcb );
		break;
	}
}

//-----------------------------------------------------------------------------------------------
// 最後の「ポケモンリーグチャンピオンおめでとう！」などをプリント
//-----------------------------------------------------------------------------------------------
static void PrintPlayerStatus( DEMO_WORK* wk )
{
	int xpos;

	MSGMAN_GetString( wk->msgMan, str_dendemo_cong2, wk->tmpbuf1 );

	xpos = (256 - FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->tmpbuf1, 0 )) / 2;
	GF_STR_PrintColor( &wk->win, FONT_SYSTEM, wk->tmpbuf1, xpos, 4, MSG_NO_PUT,
				GF_PRINTCOLOR_MAKE(1,2,0), NULL );


	WORDSET_RegisterPlayerName( wk->wordset, 0, wk->param->player );
	WORDSET_RegisterNumber( wk->wordset, 1, MyStatus_GetID_Low(wk->param->player),   5, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	WORDSET_RegisterNumber( wk->wordset, 2, PLAYTIME_GetHour(wk->param->playTime),   3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_RegisterNumber( wk->wordset, 3, PLAYTIME_GetMinute(wk->param->playTime), 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );

	MSGMAN_GetString( wk->msgMan, str_dendemo_player1, wk->tmpbuf2 );
	WORDSET_ExpandStr( wk->wordset, wk->tmpbuf1, wk->tmpbuf2 );

	xpos = (256 - FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->tmpbuf1, 0 )) / 2;
	GF_STR_PrintColor( &wk->win, FONT_SYSTEM, wk->tmpbuf1, xpos, 172, MSG_NO_PUT,
				GF_PRINTCOLOR_MAKE(1,2,0), NULL );

	GF_BGL_BmpWinCgxOn( &wk->win );
}

//-----------------------------------------------------------------------------------------------
// ポケモン全部を順番に表示
//-----------------------------------------------------------------------------------------------
typedef struct {
	VINTR_TASKFREE_WORK	tfw;
	CLACT_WORK_PTR*	act;
	DEMO_WORK*		mainWork;
	int   num;
	int   max;
	int   wait;

	FX_MOVE_NUMBER	xpos[ TEMOTI_POKEMAX ];
	VecFx32			actpos[ TEMOTI_POKEMAX ];
}POKE_DISP_WORK;

static void StartDispAllPokeTask( DEMO_WORK* wk, int taskID )
{
	static const VecFx32 poke_start_pos[] = {
		{ FX32_CONST(-40), FX32_CONST(PLAYER_END_YPOS-8),  0 },
		{ FX32_CONST(296), FX32_CONST(PLAYER_END_YPOS-8),  0 },
		{ FX32_CONST(-40), FX32_CONST(PLAYER_END_YPOS-16), 0 },
		{ FX32_CONST(296), FX32_CONST(PLAYER_END_YPOS-16), 0 },
		{ FX32_CONST(-40), FX32_CONST(PLAYER_END_YPOS-24), 0 },
		{ FX32_CONST(296), FX32_CONST(PLAYER_END_YPOS-24), 0 },
	};
	static const fx32 poke_end_xpos[] = {
		FX32_CONST(PLAYER_XPOS+32),
		FX32_CONST(PLAYER_XPOS-32),
		FX32_CONST(PLAYER_XPOS+64),
		FX32_CONST(PLAYER_XPOS-64),
		FX32_CONST(PLAYER_XPOS+96),
		FX32_CONST(PLAYER_XPOS-96),
	};

	POKE_DISP_WORK* twk;
	int i;

	twk = sys_AllocMemory( HEAPID_DENDOU_DEMO, sizeof(POKE_DISP_WORK) );

	SetVIntrTaskFreeWork( &twk->tfw, twk, &(wk->workTask[taskID]) );

	twk->mainWork = wk;
	twk->act = wk->actPoke;
	twk->num = 0;
	twk->wait = 0;
	twk->max = wk->pokeCount;

	for(i=0; i<twk->max; i++)
	{
		twk->actpos[i] = poke_start_pos[i];
		CLACT_SetMatrix( twk->act[i], &poke_start_pos[i] );
		CLACT_SetDrawFlag( twk->act[i], TRUE );
	}

	// 曲の尺合わせのため、手持ちが少なくても６体分ウエイトを入れる
	for(i=0; i<TEMOTI_POKEMAX; i++)
	{
		FxMoveNum_Set( &twk->xpos[i], poke_start_pos[i].x, poke_end_xpos[i], POKE_DISPMOVE_FRAMES );
	}

	wk->workTask[taskID] = TCB_Add( DispAllPokeTask, twk, 0 );
}

static void DispAllPokeTask( TCB_PTR tcb, void* wk_adrs )
{
	POKE_DISP_WORK* wk = wk_adrs;
	int i;

	for(i=0; i<wk->num; i++)
	{
		wk->actpos[i].x = FxMoveNum_Inc( &wk->xpos[i] );
		if( i < wk->max )
		{
			CLACT_SetMatrix( wk->act[i], &(wk->actpos[i]) );
		}
	}

	if( wk->wait )
	{
		wk->wait--;
	}
	else
	{
		if( wk->num < TEMOTI_POKEMAX )
		{
			wk->wait = FRAMES(2);
			wk->num++;
		}
		else
		{
			if( FxMoveNum_CheckEnd( &wk->xpos[wk->max-1] ) )
			{
				VIntrTaskFreeReq( &wk->tfw );
				TCB_Delete( tcb );
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
// ライトポリゴン動かし
//-----------------------------------------------------------------------------------------------
enum {
	LIGHT_MAX = 8,

	CMD_BUFFER_LEN = 64,
	LIGHT_ORG_WIDTH = 0x50,
	LIGHT_ANGLE_MIN = 10 << FX32_SHIFT,
	LIGHT_ANGLE_MAX = 170 << FX32_SHIFT,
	LIGHT_ANGLE_RANGE = LIGHT_ANGLE_MAX - LIGHT_ANGLE_MIN,

};

enum {
	LIGHT_END_WIDTH = 0x240,
	LIGHT_LEN = 0x2800,
};

typedef struct {
	GXDLInfo	cmdInfo;
	u32			cmdBuffer[ CMD_BUFFER_LEN * LIGHT_MAX ];
	u32			cmdSize;

	TCB_PTR		tcb[LIGHT_MAX];
	TCB_PTR		tailTask;
	int			cnt;

	DEMO_WORK*	mainWk;
}LIGHT_CTRL_TASK_WORK;


typedef struct {
	GXDLInfo*	cmdInfo;
	u32			cmdBuffer[ CMD_BUFFER_LEN * LIGHT_MAX ];
	u32			cmdSize;

	fx32		angle;
	fx32		angleSpeed;
	int			color;
	int			id;

	fx16		cx;
	VecFx16		vtxP1;
	VecFx16		vtxP2;
	VecFx16		vtxD1;
	VecFx16		vtxD2;

	DEMO_WORK*  mainWk;

}LIGHT_TASK_WORK;

static TCB_PTR CreateLightTask( LIGHT_CTRL_TASK_WORK* ctrlTask, fx16 px, fx32 angle, int id );
static void inline calc_light_endpos( LIGHT_TASK_WORK* wk );


static u32  LightTaskCount = 0;
static BOOL LightTaskEnable = TRUE;

static TCB_PTR CreateLightCtrlTask( DEMO_WORK* wk )
{
	LIGHT_CTRL_TASK_WORK* twk = sys_AllocMemory( HEAPID_DENDOU_DEMO, sizeof(LIGHT_CTRL_TASK_WORK) );
	if( twk )
	{
		TCB_PTR tcb;

		LightTaskEnable = TRUE;
		LightTaskCount = 2;

		twk->cnt = 0;
		twk->tailTask = add_vtask( LightCtrlTailTask, twk, TASKPRI_LIGHT_CTRL_TAIL );
		twk->mainWk = wk;

		return add_vtask( LightCtrlTask, twk, TASKPRI_LIGHT_CTRL );
	}
	return NULL;
}

static void LightCtrlTask( TCB_PTR tcb, void* wk_adrs )
{
	if( LightTaskEnable )
	{
		LIGHT_CTRL_TASK_WORK* wk = wk_adrs;
	    G3_BeginMakeDL( &wk->cmdInfo, wk->cmdBuffer, sizeof(wk->cmdBuffer) );

		G3B_MaterialColorDiffAmb(	&wk->cmdInfo,
									GX_RGB(31, 31, 31),	// diffuse
									GX_RGB(16, 16, 16),	// ambient
									FALSE				// use diffuse as vtx color if TRUE
		);

		G3B_MaterialColorSpecEmi(	&wk->cmdInfo,
									GX_RGB(16, 16, 16),	// specular
									GX_RGB(0, 0, 0),	// emission
									FALSE				// use shininess table if TRUE
		);
	}
	else
	{
		LightTaskCount--;
		TCB_Delete( tcb );
	}
}

static void LightCtrlTailTask( TCB_PTR tcb, void* wk_adrs )
{
	if( LightTaskEnable )
	{
		LIGHT_CTRL_TASK_WORK* wk = wk_adrs;

		wk->cmdSize = G3_EndMakeDL( &wk->cmdInfo );
		DC_FlushRange( wk->cmdBuffer, wk->cmdSize );
	}
	else
	{
		LightTaskCount--;
		TCB_Delete( tcb );
	}
}

static void AddLightTask( TCB_PTR  ctrlTask, fx16 px, fx32 angle )
{
	LIGHT_CTRL_TASK_WORK* twk = TCB_GetWork( ctrlTask );

	if( twk->cnt < LIGHT_MAX )
	{
		twk->tcb[twk->cnt] = CreateLightTask( twk, px, angle, twk->cnt );
		LightTaskCount++;

		#ifdef PM_DEBUG
		{
			LIGHT_TASK_WORK* wk = TCB_GetWork( twk->tcb[twk->cnt] );
			wk->mainWk = twk->mainWk;
		}
		#endif
		twk->cnt++;
	}
}


 static TCB_PTR CreateLightTask( LIGHT_CTRL_TASK_WORK* ctrlTask, fx16 px, fx32 angle, int id )
{
	static const int col[] = {
		GX_RGB(31,31,12),
		GX_RGB(31,31,16),
		GX_RGB(31,28,8),
		GX_RGB(31,31,12),
		GX_RGB(31,31,16),
		GX_RGB(31,28,8),
		GX_RGB(31,31,12),
		GX_RGB(31,31,12),
	};
	static const fx16 speed[] = {
		0x0c00,
		0x0b00,
		0x0a00,
		0x0c00,
		0x0b00,
		0x0a00,
	};

	LIGHT_TASK_WORK* twk = sys_AllocMemory( HEAPID_DENDOU_DEMO, sizeof(LIGHT_TASK_WORK) );

	if( twk )
	{
		twk->cmdInfo = &(ctrlTask->cmdInfo);
		twk->cx = px;
		twk->color = col[id];
		twk->cmdSize = 0;
		twk->angle = angle;
		twk->angleSpeed = speed[id] * (2/FRAME_RATIO);
		twk->id = id;
		VEC_Fx16Set( &(twk->vtxP1), px - LIGHT_ORG_WIDTH, -FX16_ONE, 0 );
		VEC_Fx16Set( &(twk->vtxP2), px + LIGHT_ORG_WIDTH, -FX16_ONE, 0 );
		return add_vtask( LightTask, twk, TASKPRI_LIGHT );
	}
	return NULL;
}

 static void inline calc_light_endpos( LIGHT_TASK_WORK* wk )
{
	#if 0
	if( wk->mainWk->confettiTask )
	{
		GetConfettiPos( wk->mainWk->confettiTask, &(wk->vtxP1), wk->id, 0, &wk->color );
		GetConfettiPos( wk->mainWk->confettiTask, &(wk->vtxP2), wk->id, 1, &wk->color );
		GetConfettiPos( wk->mainWk->confettiTask, &(wk->vtxD2), wk->id, 2, &wk->color );
		GetConfettiPos( wk->mainWk->confettiTask, &(wk->vtxD1), wk->id, 3, &wk->color );
	}
	else
	#endif
	{
		int angle = wk->angle >> FX32_SHIFT;
		fx32 cx, cy;

		cx = wk->cx + FX_Mul(FixSinCosTbl[90+angle], LIGHT_LEN);
		cy = FX_Mul(FixSinCosTbl[angle], LIGHT_LEN) - FX16_ONE;

		VEC_Fx16Set( &(wk->vtxD1), cx-LIGHT_END_WIDTH, cy, 0 );
		VEC_Fx16Set( &(wk->vtxD2), cx+LIGHT_END_WIDTH, cy, 0 );
	}
}

static void inline adjust_vtx( VecFx16* vtx, u32 key, const char* str )
{
	enum {
		ADJUST_UNIT = 64,
	};
	do{
		if( sys.cont & PAD_BUTTON_L )
		{
			if( key&PAD_KEY_UP    ){ vtx->z -= ADJUST_UNIT; break; }
			if( key&PAD_KEY_DOWN  ){ vtx->z += ADJUST_UNIT; break; }
		}
		if( key&PAD_KEY_UP    ){ vtx->y += ADJUST_UNIT; break; }
		if( key&PAD_KEY_DOWN  ){ vtx->y -= ADJUST_UNIT; break; }
		if( key&PAD_KEY_RIGHT ){ vtx->x += ADJUST_UNIT; break; }
		if( key&PAD_KEY_LEFT  ){ vtx->x -= ADJUST_UNIT; break; }

		return;

	}while(0);

//	OS_TPrintf("%s = x:%04x, y:%04x z:%04x\n", str, (u16)(vtx->x), (u16)(vtx->y), (u16)(vtx->z) );

}

static void LightTask( TCB_PTR tcb, void* wk_adrs )
{
	if( LightTaskEnable )
	{
		LIGHT_TASK_WORK*  wk = wk_adrs;
		wk->angle += wk->angleSpeed;

		if( wk->angleSpeed > 0 )
		{
			if( wk->angle >= LIGHT_ANGLE_MAX )
			{
				wk->angleSpeed *= -1;
			}
		}
		else
		{
			if( wk->angle <= LIGHT_ANGLE_MIN )
			{
				wk->angleSpeed *= -1;
			}
		}

		calc_light_endpos( wk );


		G3B_PolygonAttr(	wk->cmdInfo, GX_LIGHTMASK_NONE,	// disable lights
							GX_POLYGONMODE_MODULATE,			// modulation mode
							GX_CULL_BACK,  // cull back
							wk->id,				// polygon ID(0 - 63)
							16,            // alpha(0 - 31)
							0              // OR of GXPolygonAttrMisc's value
		);


		G3B_Begin( wk->cmdInfo, GX_BEGIN_QUADS );
		{
			G3B_Color( wk->cmdInfo, wk->color );
			G3B_Vtx( wk->cmdInfo, wk->vtxP1.x, wk->vtxP1.y, wk->vtxP1.z );
			G3B_Vtx( wk->cmdInfo, wk->vtxP2.x, wk->vtxP2.y, wk->vtxP2.z );
			G3B_Vtx( wk->cmdInfo, wk->vtxD2.x, wk->vtxD2.y, wk->vtxD2.z );
			G3B_Vtx( wk->cmdInfo, wk->vtxD1.x, wk->vtxD1.y, wk->vtxD1.z );
		}
		G3B_End( wk->cmdInfo );
	}
	else
	{
		LightTaskCount--;
		TCB_Delete( tcb );
	}
}


static void DrawLight( TCB_PTR tcb )
{
	if( tcb != NULL )
	{
		LIGHT_CTRL_TASK_WORK* wk = TCB_GetWork(tcb);

		G3_PushMtx();
		MI_SendGXCommand(3, wk->cmdBuffer, wk->cmdSize);
		G3_PopMtx(1);
	}
}

static void DeleteLightCtrlTask( TCB_PTR tcb )
{
	LightTaskEnable = FALSE;

	if( tcb != NULL )
	{
		LIGHT_CTRL_TASK_WORK* wk;
		int i;

		wk = TCB_GetWork(tcb);
		for(i=0; i<wk->cnt; i++)
		{
			sys_FreeMemoryEz( TCB_GetWork(wk->tcb[i]) );
		}
		sys_FreeMemoryEz( wk );
	}
}

static BOOL WaitLightTaskDelete( void )
{
	return (LightTaskCount == 0);
}

//-----------------------------------------------------------------------------------------------
// 紙吹雪ポリゴン動かし
//-----------------------------------------------------------------------------------------------
enum {
	CONFETTI_MAX = 48,

	CONFETTI_X_MIN = FX16_CONST(-1),
	CONFETTI_X_MAX = FX16_CONST(1),
	CONFETTI_Z_MIN = FX16_CONST(-0.08f),
	CONFETTI_Z_MAX = FX16_CONST(0.08f),
	CONFETTI_Y_MIN = FX16_CONST(-1),
	CONFETTI_Y_MAX   = FX16_CONST(1),

	CONFETTI_X_DIFF = CONFETTI_X_MAX-CONFETTI_X_MIN,
	CONFETTI_Y_DIFF = CONFETTI_Y_MAX-CONFETTI_Y_MIN,
	CONFETTI_Z_DIFF = CONFETTI_Z_MAX-CONFETTI_Z_MIN,

	CONFETTI_X_SIZE = FX16_CONST(0.038f),
	CONFETTI_Y_SIZE = FX16_CONST(0.050f),

	CONFETTI_CMD_LEN = 160,
	CONFETTI_FALL_SPEED = CONFETTI_Y_DIFF / 96,

	CONFETTI_X_SPEED_MIN = 0x0200,
	CONFETTI_X_SPEED_MAX = 0x0400,
	CONFETTI_X_SPEED_DIFF = (CONFETTI_X_SPEED_MAX - CONFETTI_X_SPEED_MIN),
	CONFETTI_Y_SPEED_MIN = 0x0200,
	CONFETTI_Y_SPEED_MAX = 0x0400,
	CONFETTI_Y_SPEED_DIFF = (CONFETTI_Y_SPEED_MAX - CONFETTI_Y_SPEED_MIN),
	CONFETTI_Z_SPEED_MIN = 0x0200,
	CONFETTI_Z_SPEED_MAX = 0x0400,
	CONFETTI_Z_SPEED_DIFF = (CONFETTI_Z_SPEED_MAX - CONFETTI_Z_SPEED_MIN),

	CONFETTI_RAND_SEED = 0x3594,
};

typedef struct {
	int		color;
	int		def_color;
	VecFx16		pos[4];
	VecFx16		rot;
	VecFx16		rotSpeed;
	MtxFx44		rotMtx;

	BOOL   drawFlag;
}CONFETTI_WORK;

typedef struct {
	BOOL			drawStartFlag;
	volatile BOOL	transStartFlag;
	CONFETTI_WORK	confetti[CONFETTI_MAX];

	GXDLInfo	cmdInfo;
	u32			cmdBuffer[ CONFETTI_CMD_LEN * CONFETTI_MAX ];
	u32			cmdSize;

	int			controlPos;

	MtxFx44		current;

}CONFETTI_CONTROL_WORK;

static TCB_PTR CreateConfettiTask( DEMO_WORK* wk )
{
	static const int color_ptn[] = {
		GX_RGB(16,28,21), GX_RGB(31,16,29), GX_RGB(8,8,31), GX_RGB(6,31,31),
		GX_RGB(31,31,0), GX_RGB(9,31,0), GX_RGB(31,18,0), GX_RGB(22,0,31),
	};
	static const  VecFx16  vtxOfs[4] = {
		{ -CONFETTI_X_SIZE, -CONFETTI_Y_SIZE, 0 },
		{  CONFETTI_X_SIZE, -CONFETTI_Y_SIZE, 0 },
		{  CONFETTI_X_SIZE,  CONFETTI_Y_SIZE, 0 },
		{ -CONFETTI_X_SIZE,  CONFETTI_Y_SIZE, 0 },
	};
	CONFETTI_CONTROL_WORK* cwk;
	int i, j, rand_seed, c;
	s16  x, y, z;

	cwk = sys_AllocMemory( HEAPID_DENDOU_DEMO, sizeof(CONFETTI_CONTROL_WORK) );

	rand_seed = gf_rand();
	gf_srand( CONFETTI_RAND_SEED );

	for(i=0, c=0; i<CONFETTI_MAX; i++)
	{
		cwk->confetti[i].color = color_ptn[c];
		if( ++c >= NELEMS(color_ptn) ){ c = 0; }
		x = CONFETTI_X_MIN + (gf_rand() % CONFETTI_X_DIFF);
		y = CONFETTI_Y_MAX + (gf_rand() % CONFETTI_Y_DIFF);
		z = CONFETTI_Z_MIN + (gf_rand() % CONFETTI_Z_DIFF);

		for(j=0; j<4; j++)
		{
			cwk->confetti[i].pos[j].x = x + vtxOfs[j].x;
			cwk->confetti[i].pos[j].y = y + vtxOfs[j].y;
			cwk->confetti[i].pos[j].z = z + vtxOfs[j].z;

			cwk->confetti[i].rot.x = 0;
			cwk->confetti[i].rot.y = 0;
			cwk->confetti[i].rot.z = 0;
			cwk->confetti[i].rotSpeed.x = CONFETTI_X_SPEED_MIN + gf_rand() % CONFETTI_X_SPEED_DIFF;
			cwk->confetti[i].rotSpeed.y = CONFETTI_Y_SPEED_MIN + gf_rand() % CONFETTI_Y_SPEED_DIFF;
			cwk->confetti[i].rotSpeed.z = CONFETTI_Z_SPEED_MIN + gf_rand() % CONFETTI_Z_SPEED_DIFF;

			MTX_Identity44( &cwk->confetti[i].rotMtx );
			#ifdef PM_DEBUG
			cwk->confetti[i].drawFlag = TRUE;
//			OS_TPrintf("x:%d, y:%d, z:%d\n", cwk->confetti[i].pos[j].x, cwk->confetti[i].pos[j].y, cwk->confetti[i].pos[j].z);
			#endif
		}

		j = gf_rand() & 7;
		while(j--)
		{
			VEC_Fx16Add( &cwk->confetti[i].rot, &cwk->confetti[i].rotSpeed, &cwk->confetti[i].rot );
		}
	}

	gf_srand( rand_seed );

	cwk->drawStartFlag = FALSE;
	cwk->transStartFlag = FALSE;
	cwk->controlPos = 0;

	G3_MtxMode( GX_MTXMODE_POSITION_VECTOR );

	return TCB_Add( ConfettiControlTask, cwk, TASKPRI_CONFETTI_CTRL );

}

static void DeleteConfettiTask( TCB_PTR tcb )
{
	if( tcb )
	{
		sys_FreeMemoryEz( TCB_GetWork( tcb ) );
		TCB_Delete( tcb );
	}
}

static void StartConfettiDraw( TCB_PTR tcb )
{
	if(tcb)
	{
		CONFETTI_CONTROL_WORK* wk = TCB_GetWork( tcb );
		wk->drawStartFlag = TRUE;
	}
}

static void ConfettiControlTask( TCB_PTR tcb, void* wk_adrs )
{
	CONFETTI_CONTROL_WORK* wk = wk_adrs;

	if( wk->drawStartFlag )
	{
		int i, j;

		#if 0
		{
			if( sys.repeat & PAD_KEY_UP )
			{
				if( --(wk->controlPos) < 0 )
				{
					wk->controlPos = CONFETTI_MAX - 1;
				}
				OS_TPrintf("control Pos = %d\n", wk->controlPos );
			}
			if( sys.repeat & PAD_KEY_DOWN )
			{
				if( ++(wk->controlPos) >= CONFETTI_MAX )
				{
					wk->controlPos = 0;
				}
				OS_TPrintf("control Pos = %d\n", wk->controlPos );
			}
			if (sys.trg & PAD_BUTTON_SELECT )
			{
				wk->confetti[ wk->controlPos ].drawFlag ^= 1;
				OS_TPrintf("confetti[ %d ] drawFlag = %d\n", wk->controlPos, wk->confetti[ wk->controlPos ].drawFlag);
			}
			if (sys.trg & PAD_BUTTON_START )
			{
				int j, p;

				p = wk->controlPos;
				OS_TPrintf("confetti[ %d ] vtx ---------------\n", p);
				for(j=0; j<4; j++)
				{
					OS_TPrintf("  x:%d, y:%d, z:%d\n", wk->confetti[p].pos[j].x, wk->confetti[p].pos[j].y, wk->confetti[p].pos[j].z);
				}
				OS_TPrintf("------------------------------\n");
			}
		}
		#endif

	    G3_BeginMakeDL( &wk->cmdInfo, wk->cmdBuffer, sizeof(wk->cmdBuffer) );

		G3B_PolygonAttr(	&wk->cmdInfo, GX_LIGHTMASK_01,	// disable lights
							GX_POLYGONMODE_MODULATE,			// modulation mode
							GX_CULL_NONE, 	// cull back
							63,			// polygon ID(0 - 63)
							31,            // alpha(0 - 31)
							0              // OR of GXPolygonAttrMisc's value
		);

		#if 1
		G3B_MaterialColorDiffAmb(	&wk->cmdInfo,
									GX_RGB(20,20,20),	// diffuse
									GX_RGB(0,0,0),		// ambient
									FALSE				// use diffuse as vtx color if TRUE
		);
		#endif

	    for(i=0; i<CONFETTI_MAX; i++)
	    {
			wk->confetti[i].pos[3].y -= CONFETTI_FALL_SPEED;
			if( wk->confetti[i].pos[3].y <= CONFETTI_Y_MIN )
			{
				wk->confetti[i].pos[3].y = CONFETTI_Y_MAX - (CONFETTI_Y_MIN - wk->confetti[i].pos[3].y);
			}
			wk->confetti[i].pos[0].y = wk->confetti[i].pos[3].y - (CONFETTI_Y_SIZE*2);
			wk->confetti[i].pos[1].y = wk->confetti[i].pos[0].y;
			wk->confetti[i].pos[2].y = wk->confetti[i].pos[3].y;

			VEC_Fx16Add( &wk->confetti[i].rot, &wk->confetti[i].rotSpeed, &wk->confetti[i].rot );
			MTX_Identity44( &(wk->confetti[i].rotMtx) );

			MTX_TransApply44( &(wk->confetti[i].rotMtx), &(wk->confetti[i].rotMtx),
				 wk->confetti[i].pos[0].x,  wk->confetti[i].pos[0].y,  wk->confetti[i].pos[0].z );


			G3B_LightColor( &(wk->cmdInfo), GX_LIGHTID_0, GX_RGB(11,11,11) );
			G3B_LightColor( &(wk->cmdInfo), GX_LIGHTID_1, wk->confetti[i].color );
//			G3B_LightColor( &(wk->cmdInfo), GX_LIGHTID_0, wk->confetti[i].color );
			{
				VecFx16 vec;

				VEC_Fx16Set( &vec, 0, FX16_ONE-1, -FX16_ONE+1 );
				VEC_Fx16Normalize( &vec, &vec );
				G3B_LightVector( &wk->cmdInfo, GX_LIGHTID_0, vec.x, vec.y, vec.z );

				VEC_Fx16Set( &vec, 0, -FX16_ONE+1, FX16_ONE-1 );
				VEC_Fx16Normalize( &vec, &vec );
				G3B_LightVector( &wk->cmdInfo, GX_LIGHTID_1, vec.x, vec.y, vec.z );
			}

		#if 1
			{
				MtxFx44  rotMtx;

				MTX_RotX44( &rotMtx, FX_SinIdx((u16)(wk->confetti[i].rot.x)), FX_CosIdx((u16)(wk->confetti[i].rot.x)) );
				MTX_Concat44( &rotMtx, &(wk->confetti[i].rotMtx), &(wk->confetti[i].rotMtx) );

				MTX_RotY44( &rotMtx, FX_SinIdx((u16)(wk->confetti[i].rot.y)), FX_CosIdx((u16)(wk->confetti[i].rot.y)) );
				MTX_Concat44( &rotMtx, &(wk->confetti[i].rotMtx), &(wk->confetti[i].rotMtx) );

				MTX_RotZ44( &rotMtx, FX_SinIdx((u16)(wk->confetti[i].rot.z)), FX_CosIdx((u16)(wk->confetti[i].rot.z)) );
				MTX_Concat44( &rotMtx, &(wk->confetti[i].rotMtx), &(wk->confetti[i].rotMtx) );

			}
		#endif


		#if 1
			G3B_MaterialColorSpecEmi(	&wk->cmdInfo,
										GX_RGB(31,31,31),		// speculer
										wk->confetti[i].color,			// emission
										FALSE					// use shininess table if TRUE
			);
		#endif



			G3B_PushMtx( &wk->cmdInfo );
			G3B_LoadMtx44( &wk->cmdInfo, &(wk->confetti[i].rotMtx) );

			G3B_Begin( &wk->cmdInfo, GX_BEGIN_QUADS );
			{
				G3B_Normal( &wk->cmdInfo, 0, 0, -FX16_ONE+1 );

				G3B_Vtx( &wk->cmdInfo, -CONFETTI_X_SIZE, -CONFETTI_Y_SIZE, 0 );
				G3B_Vtx( &wk->cmdInfo,  CONFETTI_X_SIZE, -CONFETTI_Y_SIZE, 0 );
				G3B_Vtx( &wk->cmdInfo,  CONFETTI_X_SIZE,  CONFETTI_Y_SIZE, 0 );
				G3B_Vtx( &wk->cmdInfo, -CONFETTI_X_SIZE,  CONFETTI_Y_SIZE, 0 );


			}
			G3B_End( &wk->cmdInfo );

			G3B_PopMtx( &wk->cmdInfo, 1 );
		}

		wk->cmdSize = G3_EndMakeDL( &wk->cmdInfo );
		DC_FlushRange( wk->cmdBuffer, wk->cmdSize );

		GF_ASSERT_MSG( wk->cmdSize < sizeof(wk->cmdBuffer), "cmdSize=%d, bufSize=%d", wk->cmdSize, sizeof(wk->cmdBuffer) );

		wk->transStartFlag = TRUE;

	}
}

static void DrawConfetti( TCB_PTR tcb )
{
	if( tcb )
	{
		CONFETTI_CONTROL_WORK* wk = TCB_GetWork( tcb );
		if( wk->transStartFlag )
		{
			G3_PushMtx();
			OS_TPrintf("[VINTR] Send Start\n");
			MI_SendGXCommand(3, wk->cmdBuffer, wk->cmdSize);
//			OS_TPrintf("[VINTR] Send End\n");
			G3_PopMtx(1);
 			wk->transStartFlag = FALSE;
		}
		else
		{
			OS_TPrintf("[VINTR] Send Threw\n");
		}
	}
}

#ifdef PM_DEBUG
static void GetConfettiPos( TCB_PTR tcb, VecFx16* vtx, int id, int pos, int* color )
{
	if( tcb )
	{
		CONFETTI_CONTROL_WORK* wk = TCB_GetWork( tcb );
		*vtx = wk->confetti[id].pos[pos];
		*color = wk->confetti[id].color;

//		OS_TPrintf("served status\n");
//		OS_TPrintf("id=%d, color=%04x\n", id, (u16)(*color));
	}
}
#endif
//-----------------------------------------------------------------------------------------------
// 固定小数を等速で増減するためのオブジェクト
//-----------------------------------------------------------------------------------------------
static void FxMoveNum_Set( FX_MOVE_NUMBER* num, fx32 start_num, fx32 end_num, int wait )
{
	num->num = start_num;
	num->end = end_num;
	num->add = (end_num - start_num) / wait;
	num->wait = wait - 1;
	num->endFlag = FALSE;
}


static fx32 FxMoveNum_Inc( FX_MOVE_NUMBER* num )
{
	if( num->wait )
	{
		num->wait--;
		num->num += num->add;
		return num->num;
	}
	else
	{
		num->endFlag = TRUE;
		return num->end;
	}
}

static BOOL FxMoveNum_CheckEnd( FX_MOVE_NUMBER* num )
{
	return num->endFlag;
}

//-----------------------------------------------------------------------------------------------
// 出会い方パターンチェック
//-----------------------------------------------------------------------------------------------
static  POKE_MEET_PATTERN  GetPokeMeetPattern( DEMO_WORK* wk, POKEMON_PARAM* pp, const MYSTATUS* player )
{
	BOOL fastFlag;
	POKE_MEET_PATTERN ptn = POKE_MEET_OTHER;

	fastFlag = PokeParaFastModeOn(pp);

	do {
		// AGBロムから来たケース
		{
			int romVer = PokeParaGet( pp, ID_PARA_get_cassette, NULL );
			if( romVer == VERSION_SAPPHIRE || romVer == VERSION_RUBY || romVer == VERSION_EMERALD )
			{
				ptn = POKE_MEET_HOUEN;
				break;
			}
			if( romVer == VERSION_RED || romVer == VERSION_GREEN )
			{
				ptn = POKE_MEET_KANTOU;
				break;
			}
			if( romVer == VERSION_COLOSSEUM )
			{
				ptn = POKE_MEET_SOMEWHERE;
				break;
			}
		}

		// 外部配布なら
		if( PokeParaGet( pp, ID_PARA_event_get_flag, NULL ) )
		{
			ptn = POKE_MEET_OTHER;
			break;
		}

		// ID または 親名の不一致なら、通信交換とみなす
		{
			u32 playerID, pokeID;

			playerID = MyStatus_GetID( player );
			pokeID = PokeParaGet( pp, ID_PARA_id_no, NULL );

			if( playerID != pokeID )
			{
				ptn = POKE_MEET_TRADE;
				break;
			}

			MyStatus_CopyNameString( player, wk->tmpbuf1 );
			PokeParaGet( pp, ID_PARA_oyaname_buf, wk->tmpbuf2 );

			if( STRBUF_Compare( wk->tmpbuf1, wk->tmpbuf2 ) )
			{
				ptn = POKE_MEET_TRADE;
				break;
			}
		}

		// ここまで来たらタマゴ孵化か野生捕獲のはずだが、
		// 念のためヘンな場所コードが入っていたら「うんめいてきなであい」ということにしておく
		if( PokeParaGet( pp, ID_PARA_birth_place, NULL ) >= 2000 )
		{
			ptn = POKE_MEET_OTHER;
		}
		else
		{
			// ID_PARA_get_month は“タマゴをもらった日付（月）”という意味なので
			// これが０だったら野生で捕まえたものとみなす
			if( PokeParaGet( pp, ID_PARA_get_month, NULL ) == 0 )
			{
				ptn = POKE_MEET_CATCH;
			}
			else
			{
				ptn = POKE_MEET_BORN;
			}
		}


	}while(0);

	PokeParaFastModeOff(pp, fastFlag);

	return ptn;
}
