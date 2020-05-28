
//============================================================================================
/**
 * @file	fight.c
 * @bfief	戦闘メインプログラム
 * @author	HisashiSogabe
 * @date	05.05.24
 */
//============================================================================================


#include "common.h"

#include "battle/battle_server.h"
#include "battle/server.h"
#include "battle/server_tool.h"
#include "battle/client.h"
#include "battle/client_tool.h"
#include "battle/fight.h"
#include "battle/fight_tool.h"
#include "battle/shinka.h"
#include "battle/trtype_def.h"
#include "fight_def.h"
#include "ground.h"
#include "itemtool/myitem.h"
#include "system/brightness.h"
#include "system/window.h"
#include "field/field.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/softsprite.h"
#include "system/pm_rtc.h"

#include "system/fontproc.h"
#include "system/font_arc.h"
#include "system/palanm.h"

#include "system/pmfprint.h"
#include "system/msgdata.h"
#include "system/msg_ds_icon.h"
#include "system/wipe.h"
#include "system/wordset.h"
#include "system/snd_tool.h"

#include "system/zukanwork.h"

#include "application/app_tool.h"

#include "wazaeffect/battle_particle.h"
#include "system/particle.h"
#include "wazaeffect/we_mana.h"
#include "wazaeffect/we_sys.h"

#include "battle/graphic/batt_bg_def.h"
#include "battle_input.h"
#include "system/numfont.h"
#include "battle/battle_tcb_pri.h"

#include "pokeanime/p_anm_sys.h"

#include "msgdata/msg.naix"

#include "communication/communication.h"
#include "communication/comm_state.h"
#include "communication/comm_wifihistory.h"
#include "field/comm_union_beacon.h"
#include "comm_command_battle.h"
#include "battle_snd_def.h"

#include "gflib/mmap_get.h"

#include "savedata/perapvoice.h"
#include "savedata/wifihistory.h"

#include "msgdata/msg_fightmsg_dp.h"

#include "system/pm_overlay.h"
#include <nitro/sinit.h>
FS_EXTERN_OVERLAY(battle_bag_list);
FS_EXTERN_OVERLAY(vs_demo);
FS_EXTERN_OVERLAY(bc_common);
FS_EXTERN_OVERLAY(ol_zukan);

//============================================================================================
/**
 * 定数宣言
 */
//============================================================================================

#define	HEAP_CHECK

//#define DEBUG_PRINT			//シーケンス表示をON

#define	BATTLE_BMP_WIN_MAX		(3)		///<戦闘で使用するBMPWINのMAX
#define	BATTLE_CELL_TRANS_MAX	(2)		///<戦闘で使用するCellTransのMAX

#define BATTLE_BG1_V_START_OFFSET	( -51 )	///<戦闘開始時のBG1のVOFFSETの値 

enum {
	SEQ_INIT = 0,
	SEQ_SIO_INIT,
	SEQ_SIO_MAIN,
	SEQ_FIGHT_LIST_DEMO_INIT,
	SEQ_FIGHT_LIST_DEMO_MAIN,
	SEQ_FIGHT_MENU_DEMO_INIT,
	SEQ_FIGHT_MENU_DEMO_MAIN,
	SEQ_FIGHT_SYNCRO_WAIT,
	SEQ_FIGHT_INIT,
	SEQ_FIGHT_MAIN,
	SEQ_WIN_LOSE_INIT,
	SEQ_WIN_LOSE_MAIN,
	SEQ_WIN_LOSE_WAIT,
	SEQ_SHINKA_INIT,
	SEQ_SHINKA_MAIN,
	SEQ_EXIT
};

static	const	u32	BattleServerVersion=0x100;		//戦闘サーババージョン　1.00

//============================================================================================
/**
 * プロトタイプ宣言
 */
//============================================================================================

BOOL BattleSystemProc(PROC *proc,int *seq);
void	FightScreenTransition(BATTLE_WORK *bw);
void	FightScreenEnd(BATTLE_WORK *bw);
void	FightScreenRecover(BATTLE_WORK *bw);
void	FightScreenPokemonGetEnd(BATTLE_WORK *bw);
void	FightScreenPokemonGet(BATTLE_WORK *bw);

static	void	FightInit(PROC *proc);
static	int		FightMain(PROC *proc);
static	void	FightEnd(PROC *proc);

static	BOOL	FightListDemoInit(PROC *proc);
static	BOOL	FightListDemoMain(PROC *proc);

static	BOOL	FightMenuDemoInit(PROC *proc);
static	BOOL	FightMenuDemoMain(PROC *proc);

static	BOOL	FightWinLoseDemoInit(PROC *proc);
static	BOOL	FightWinLoseDemoMain(PROC *proc);

static	void	FightSioInit(PROC *proc,BATTLE_PARAM *bp);
static	BOOL	FightSioMain(PROC *proc);
static	void	FightSioEnd(PROC *proc);

static	void	FightBGCreate(BATTLE_WORK *bw, GF_BGL_INI *bgl);
static	void	FightOBJCreate(BATTLE_WORK *bw);
static	void	FightBGEnd(GF_BGL_INI *bgl);
static	void	FightOBJEnd(BATTLE_WORK *bw);

static	void	FightSystemBoot(BATTLE_WORK *bw,BATTLE_PARAM *bp);

static	void	FightParticleInit(void);	//パーティクル初期化
static	void	FightVBlank(void *work);
static	void	FightSioVBlank(void *work);

static void FightUpdate(TCB_PTR tcb, void *work);

static void FightPinchSECheck(TCB_PTR tcb, void *work);

static GF_G3DMAN * Fight_3D_Init(void);
static void Fight_3D_Exit(GF_G3DMAN *g3Dman);
static void FightSimpleSetUp(void);
static void	FightMsgPrintModeSet(BATTLE_WORK *bw);
static void StartMsgWinMove( TCB_PTR tcb, void *work );

static	BOOL	BossTrTypeCheck(u16 tr_type);
static	void	FightSioServerBootCheck(BATTLE_WORK *bw,BATTLE_PARAM *bp);

//============================================================================================
/**
 * CL_ACT用データ
 */
//============================================================================================

static	const TCATS_OAM_INIT BattleTcats = {
	BATTLE_OAM_START_MAIN, BATTLE_OAM_END_MAIN,
	BATTLE_OAM_AFFINE_START_MAIN, BATTLE_OAM_AFFINE_END_MAIN,
	BATTLE_OAM_START_SUB, BATTLE_OAM_END_SUB,
	BATTLE_OAM_AFFINE_START_SUB, BATTLE_OAM_AFFINE_END_SUB,
};

static	const TCATS_CHAR_MANAGER_MAKE BattleCcmm = {
	BATTLE_CHAR_MAX,
	BATTLE_CHAR_VRAMSIZE_MAIN,
	BATTLE_CHAR_VRAMSIZE_SUB,
	GX_OBJVRAMMODE_CHAR_1D_64K,
	GX_OBJVRAMMODE_CHAR_1D_32K
};

const TCATS_RESOURCE_NUM_LIST BattleResourceList = {
	BATTLE_OAMRESOURCE_CHAR_MAX,
	BATTLE_OAMRESOURCE_PLTT_MAX,
	BATTLE_OAMRESOURCE_CELL_MAX,
	BATTLE_OAMRESOURCE_CELLANM_MAX,
	BATTLE_OAMRESOURCE_MCELL_MAX,
	BATTLE_OAMRESOURCE_MCELLANM_MAX,
};

//============================================================================================
/**
 *
 *	戦闘PROC関数
 *
 * @param
 */
//============================================================================================
BOOL BattleSystemProc(PROC *proc,int * seq)
{
	BATTLE_PARAM	*bp=PROC_GetParentWork(proc);

	switch( *seq ){
	case SEQ_INIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_INIT\n");
#endif
		{
			sys_CreateHeap(HEAPID_BASE_APP,HEAPID_BATTLE,BATTLE_ALLOC_SIZE);
		}
		if(bp->fight_type&FIGHT_TYPE_SIO){
			*seq = SEQ_SIO_INIT;
		}
		else{
			*seq = SEQ_FIGHT_LIST_DEMO_INIT;
		}
		break;
	case SEQ_SIO_INIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_SIO_INIT\n");
#endif
		FightSioInit(proc,bp);
		// 地球儀登録
        Comm_WifiHistoryCheck( bp->wifihistory );
		//通信対戦回数をカウントアップ
		if(!CommStateIsWifiConnect()){
			RECORD_Inc(bp->record,RECID_COMM_BATTLE);
		}
		else{
			RECORD_Inc(bp->record,RECID_WIFI_BATTLE);
		}
		*seq = SEQ_SIO_MAIN;
		break;
	case SEQ_SIO_MAIN:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_SIO_MAIN\n");
#endif
		if(FightSioMain(proc)==TRUE){
			FightSioEnd(proc);
			*seq = SEQ_FIGHT_LIST_DEMO_INIT;
		}
		break;
	case SEQ_FIGHT_LIST_DEMO_INIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_FIGHT_LIST_DEMO_INIT\n");
#endif
		if(FightListDemoInit(proc)==TRUE){
			*seq = SEQ_FIGHT_LIST_DEMO_MAIN;
		}
		else{
			*seq = SEQ_FIGHT_MENU_DEMO_INIT;
		}
		break;
	case SEQ_FIGHT_LIST_DEMO_MAIN:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_FIGHT_LIST_DEMO_MAIN\n");
#endif
		if(FightListDemoMain(proc)==TRUE){
			*seq = SEQ_FIGHT_MENU_DEMO_INIT;
		}
		break;
	case SEQ_FIGHT_MENU_DEMO_INIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_FIGHT_MENU_DEMO_INIT\n");
#endif
		if(FightMenuDemoInit(proc)==TRUE){
			*seq = SEQ_FIGHT_MENU_DEMO_MAIN;
		}
		else{
			*seq = SEQ_FIGHT_INIT;
		}
		break;
	case SEQ_FIGHT_MENU_DEMO_MAIN:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_FIGHT_MENU_DEMO_MAIN\n");
#endif
		if(FightMenuDemoMain(proc)==TRUE){
			Overlay_UnloadID(FS_OVERLAY_ID(vs_demo));
			*seq = SEQ_FIGHT_SYNCRO_WAIT;
			CommTimingSyncStart( COMM_BATTLE_START_WAIT_NUM );
		}
		break;
	case SEQ_FIGHT_SYNCRO_WAIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_FIGHT_SYNCRO_WAIT\n");
#endif
		if(CommIsTimingSync( COMM_BATTLE_START_WAIT_NUM )){
			*seq = SEQ_FIGHT_INIT;
		}
		break;
	case SEQ_FIGHT_INIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_FIGHT_INIT\n");
#endif
		Overlay_Load(FS_OVERLAY_ID(bc_common), OVERLAY_LOAD_NOT_SYNCHRONIZE);
		FightInit(proc);
		*seq = SEQ_FIGHT_MAIN;
		break;
	case SEQ_FIGHT_MAIN:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_FIGHT_MAIN\n");
#endif
		if(FightMain(proc)==1){
			FightEnd(proc);
			*seq = SEQ_WIN_LOSE_INIT;
		}
		break;
	case SEQ_WIN_LOSE_INIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_WIN_LOSE_INIT\n");
#endif
		if(FightWinLoseDemoInit(proc)==TRUE){
			*seq = SEQ_WIN_LOSE_MAIN;
		}
		else{
			sys_DeleteHeap(HEAPID_BATTLE);
			*seq = SEQ_SHINKA_INIT;
		}
		break;
	case SEQ_WIN_LOSE_MAIN:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_WIN_LOSE_MAIN\n");
#endif
		if(FightWinLoseDemoMain(proc)==TRUE){
			Overlay_UnloadID(FS_OVERLAY_ID(vs_demo));
			sys_DeleteHeap(HEAPID_BATTLE);
			CommTimingSyncStart( COMM_BATTLE_WIN_LOSE_WAIT_NUM );
			*seq = SEQ_WIN_LOSE_WAIT;
		}
		break;
	case SEQ_WIN_LOSE_WAIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_WIN_LOSE_WAIT\n");
#endif
		if(CommIsTimingSync( COMM_BATTLE_WIN_LOSE_WAIT_NUM )){
			*seq = SEQ_EXIT;
		}
		break;
	case SEQ_SHINKA_INIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_SHINKA_INIT\n");
#endif
		{
			int				sel_mons_no;
			int				after_mons_no;
			int				shinka_cond;
			POKEMON_PARAM	*pp;

			after_mons_no=BattleWorkShinkaCheck(bp,&sel_mons_no,&shinka_cond);

			if(after_mons_no){
				sys_CreateHeap(HEAPID_BASE_APP,HEAPID_ITEMSHINKA,0x30000);
				pp=PokeParty_GetMemberPointer(bp->poke_party[CLIENT_NO_MINE],sel_mons_no);
				bp->work=ShinkaInit(bp->poke_party[CLIENT_NO_MINE],pp,after_mons_no,
									bp->config,bp->contest_see_flag,bp->zw,bp->my_item,bp->record,bp->poketch_data,
									shinka_cond,SHINKA_STATUS_FLAG_CANCEL_ON|SHINKA_STATUS_FLAG_BATTLE_MODE,HEAPID_ITEMSHINKA);
				*seq = SEQ_SHINKA_MAIN;
			}
			else{
				*seq = SEQ_EXIT;
			}
		}
		break;
	case SEQ_SHINKA_MAIN:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_SHINKA_MAIN\n");
#endif
		{
			SHINKA_WORK *sw=(SHINKA_WORK *)bp->work;
			if(ShinkaEndCheck(sw)==TRUE){
				ShinkaEnd(sw);
				sys_DeleteHeap(HEAPID_ITEMSHINKA);
				*seq = SEQ_SHINKA_INIT;
			}
		}
		break;
	case SEQ_EXIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_EXIT\n");
#endif
		return TRUE;
	}
	return FALSE;
}

//============================================================================================
/**
 *
 *	戦闘画面別処理推移処理（バッグとかリストとかに行くときに削除する関連をまとめてある）
 *
 * @param
 */
//============================================================================================
void	FightScreenTransition(BATTLE_WORK *bw)
{
//	sys_VBlankFuncChange(NULL,NULL);

	BINPUT_SystemFree(bw->bip);

	//サブ画面
	BINPUT_FrameExit(bw->bgl);

	//VRAM初期化リクエスト
	bw->bl_vram_init_req=1;

//	FightBGEnd(bw->bgl);
//	FightOBJEnd(bw);
	
//	CATS_ResourceDestructor_S(bw->csp,bw->crp);
//	CATS_FreeMemory(bw->csp);

//	DellVramTransferManager();

	//リスト、バッグ画面でもボタンフォントを別にロードする可能性があるのでUnload
	FontProc_UnloadFont(FONT_BUTTON);
	BattleWorkProcModeSet(bw,BW_PROC_MODE_BAG_LIST);
	Overlay_UnloadID(FS_OVERLAY_ID(bc_common));
	Overlay_Load(FS_OVERLAY_ID(battle_bag_list), OVERLAY_LOAD_NOT_SYNCHRONIZE);
}

//============================================================================================
/**
 *
 *	戦闘画面削除処理（バッグとかリストとかに行くときに削除する関連から分離）
 *
 * @param
 */
//============================================================================================
void	FightScreenEnd(BATTLE_WORK *bw)
{
	sys_VBlankFuncChange(NULL,NULL);

	BINPUT_SystemFree(bw->bip);

	GF_BGL_BmpWinDel(&bw->win[TALK_WIN_NO]);

	FightBGEnd(bw->bgl);
	FightOBJEnd(bw);
	
	CATS_ResourceDestructor_S(bw->csp,bw->crp);
	CATS_FreeMemory(bw->csp);

	DellVramTransferManager();

	//リスト、バッグ画面でもボタンフォントを別にロードする可能性があるのでUnload
	FontProc_UnloadFont(FONT_BUTTON);
}

//============================================================================================
/**
 *
 *	戦闘画面復帰処理
 *
 * @param
 */
//============================================================================================
void	FightScreenRecover(BATTLE_WORK *bw)
{
	Overlay_UnloadID(FS_OVERLAY_ID(battle_bag_list));
	Overlay_Load(FS_OVERLAY_ID(bc_common), OVERLAY_LOAD_NOT_SYNCHRONIZE);

	BattleWorkProcModeSet(bw,BW_PROC_MODE_FIGHT);

//	MI_CpuFill16((void*)HW_BG_PLTT, 0x0000, HW_BG_PLTT_SIZE);
	MI_CpuFill16((void*)GF_MMAP_SubBgPlttAddr(), 0x0000, GF_MMAP_SubBgPlttSize());


	//戦闘入力画面システムワーク確保
	bw->bip=BINPUT_SystemInit(bw,BattleWorkMySexGet(bw,CommGetCurrentID()));

	//リスト、バッグ画面でUnloadされる可能性があるのでフォントを再ロード
	FontProc_LoadFont(FONT_BUTTON, HEAPID_BATTLE);

	//VRAM設定初期化リクエスト
	bw->vram_init_req=1;

//	initVramTransferManagerHeap(BATTLE_VRAM_TRANSFER_TASK_NUM,HEAPID_BATTLE);
//
//	GF_Disp_GX_VisibleControlInit();

	//VRAM設定
//	{
//		GF_BGL_DISPVRAM vramSetTable = {
//			GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
//			GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
//			GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
//			GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
//			GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
//			GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
//			GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
//			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
//			GX_VRAM_TEX_01_BC,				// テクスチャイメージスロット
//			GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
//		};
//		GF_Disp_SetBank( &vramSetTable );
//
//		MI_CpuClear32((void*)HW_BG_VRAM, HW_BG_VRAM_SIZE);
//		MI_CpuClear32((void*)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
//		MI_CpuClear32((void*)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
//		MI_CpuClear32((void*)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
//	}
	//サブ画面フレーム設定
	{
		BINPUT_DefaultFrameSet(bw->bgl);
	}
//	GF_Disp_DispOn();

//	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);

//	FightBGCreate(bw, bw->bgl);
//	GF_BGL_BmpWinAdd(bw->bgl,bw->win,GF_BGL_FRAME1_M,0x02,0x13,27,4,0x0b,TALK_WIN_CGX_SIZ+1);
//	GF_BGL_BmpWinDataFill(bw->win,0xff);
//	BmpTalkWinWrite(bw->win,WINDOW_TRANS_ON,1,0x0a);

//	bw->csp=CATS_AllocMemory(HEAPID_BATTLE);
//	CATS_SystemInit(bw->csp,&BattleTcats,&BattleCcmm,BATTLE_OAM_PLTT_MAX);
//	bw->crp=CATS_ResourceCreate(bw->csp);
//	CATS_ClactSetInit(bw->csp, bw->crp, BATTLE_ACTOR_MAX);
//	CATS_ResourceManagerInit(bw->csp,bw->crp,&BattleResourceList);

	//サブ画面		アクターシステムが作られてから呼んでください
	BINPUT_DefaultDataSet(bw->bip);
	BINPUT_CreateBG(bw->bip, BINPUT_TYPE_WALL, TRUE, NULL);
	BINPUT_StockBallActorResourceLoad(bw->bip);

//	FightOBJCreate(bw);

//	SoftSpriteRecover(bw->soft_sprite);
	//会話ウインドウのカーソルキャラを再転送
	PokeFontTrgCursorCgxSet(TALK_WIN_CGX_START);

	FightMsgPrintModeSet(bw);
	CLACT_U_SetSubSurfaceMatrix(CATS_EasyRenderGet(bw->csp), 0, BATTLE_SUB_ACTOR_DISTANCE);
}

//============================================================================================
/**
 *
 *	戦闘画面削除処理（ポケモンゲット時の図鑑画面に行くときに削除する）
 *
 * @param
 */
//============================================================================================
void	FightScreenPokemonGetEnd(BATTLE_WORK *bw)
{
	GF_BGL_BmpWinDel(&bw->win[TALK_WIN_NO]);

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_BGL_BGControlExit(bw->bgl, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit(bw->bgl, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit(bw->bgl, GF_BGL_FRAME3_M );

//	FightBGEnd(bw->bgl);
//	FightOBJEnd(bw);

	BattleWorkGaugeOff(bw);
}

//============================================================================================
/**
 *
 *	ポケモン捕獲画面生成
 *
 * @param
 */
//============================================================================================
void	FightScreenPokemonGet(BATTLE_WORK *bw)
{
#if 0
	//VRAM設定
	{
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
			GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
			GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
			GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
			GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
			GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
			GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
			GX_VRAM_TEX_01_BC,				// テクスチャイメージスロット
			GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
		};
		GF_Disp_SetBank( &vramSetTable );

		MI_CpuClear32((void*)HW_BG_VRAM, HW_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
	}
#endif
#if 0
	// BG SYSTEM
	{
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}
#endif

	// ブレンド設定
	{
		bw->bld_init_req=1;
	}

	//メイン画面フレーム設定
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
			///<FRAME1_M
			{
//				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
				0, 0, 0x0800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
				BATTLE_BGPRI_WINDOW, 0, 0, FALSE
			},
			///<FRAME2_M
			{
				0, 0, 0x2000, 0, GF_BGL_SCRSIZ_512x512, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
				BATTLE_BGPRI_EFFECT, 0, 0, FALSE
			},
			///<FRAME3_M
			{
				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_256,
				GX_BG_SCRBASE_0x3000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
				BATTLE_BGPRI_BACKGROUND, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bw->bgl, GF_BGL_FRAME1_M, &TextBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bw->bgl, GF_BGL_FRAME1_M );
		GF_BGL_BGControlSet(bw->bgl, GF_BGL_FRAME2_M, &TextBgCntDat[1], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bw->bgl, GF_BGL_FRAME2_M );
		GF_BGL_BGControlSet(bw->bgl, GF_BGL_FRAME3_M, &TextBgCntDat[2], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bw->bgl, GF_BGL_FRAME3_M );

		G2_SetBG0Priority(BATTLE_3DBG_PRIORITY);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	}

	//背景グラフィックデータロード
	{
		WINTYPE	win_type;

		win_type=BattleWorkConfigWinTypeGet(bw);

		TalkWinGraphicNullSet(bw->bgl, GF_BGL_FRAME1_M,TALK_WIN_CGX_START,TALK_WIN_PAL_NO,win_type,HEAPID_BATTLE);
		ArcUtil_BgCharSet(ARC_BATT_BG,BATTLE_BG00_NCGR_BIN+bw->bg_id,bw->bgl,GF_BGL_FRAME3_M,0,0,1,HEAPID_BATTLE);
		PaletteWorkSet_Arc(bw->pfd, ARC_BATT_BG, BATT_BG00_D_NCLR+(bw->bg_id*3)+BattleWorkTimeZoneOffsetGet(bw), HEAPID_BATTLE, 
			FADE_MAIN_BG, 0, 0);
		PaletteWorkSet_Arc(bw->pfd, ARC_WINFRAME, TalkWinPalArcGet(win_type), HEAPID_BATTLE, 
			FADE_MAIN_BG, 0x20, TALK_WIN_PAL_NO*0x10);
		PaletteWorkSet_Arc(bw->pfd, ARC_FONT, NARC_font_talk_ncrl, HEAPID_BATTLE, 
			FADE_MAIN_BG, 0x20, 0x0b*0x10);
		ArcUtil_ScrnSet(ARC_BATT_BG,BATTLE_BG00_NSCR_BIN,bw->bgl,GF_BGL_FRAME3_M,0,0,1,HEAPID_BATTLE);
	}

	//ウインドウマスク設定の初期化
	{
		GX_SetVisibleWnd(GX_WNDMASK_NONE);
		GXS_SetVisibleWnd(GX_WNDMASK_NONE);
		G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_NONE,NULL);
		G2_SetWndOutsidePlane(GX_WND_PLANEMASK_NONE,NULL);
	}

	GF_Disp_DispOn();

	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	sys_VBlankFuncChange(FightVBlank,bw);

	//VRAM設定初期化リクエスト
	bw->vram_init_req=1;

	GF_BGL_BmpWinAdd(bw->bgl,bw->win,GF_BGL_FRAME1_M,0x02,0x13,27,4,0x0b,TALK_WIN_CGX_SIZ+1);
	GF_BGL_BmpWinDataFill(bw->win,0xff);
	BmpTalkWinWrite(&bw->win[TALK_WIN_NO],WINDOW_TRANS_ON,TALK_WIN_CGX_START,TALK_WIN_PAL_NO);

	FightMsgPrintModeSet(bw);
}

//============================================================================================
/**
 *	エンカウント時の背景色の初期値
 *
 * @param
 */
//============================================================================================
static	const	int	EncountFirstColor[][3]={
	{0x7b51,GX_RGB(30,17,0),GX_RGB(0,16,23)},				//BG_ID_BASIC			//草原
	{0x7b51,GX_RGB(30,17,0),GX_RGB(0,16,23)},				//BG_ID_SEA				//海
	{0x7b51,GX_RGB(30,17,0),GX_RGB(0,16,23)},				//BG_ID_CITY			//街
	{GX_RGB(11,21,5),GX_RGB(11,21,5),GX_RGB(11,21,5)},		//BG_ID_FOREST			//森林
	{0x7b51,GX_RGB(30,17,0),GX_RGB(0,16,23)},				//BG_ID_MOUNTAIN		//山岳
	{GX_RGB(31,26,31),GX_RGB(31,26,22),GX_RGB(24,22,22)},	//BG_ID_SNOW_MOUNTAIN	//雪山
	{0x7fff,0x7fff,0x7fff},									//BG_ID_ROOM_A			//室内Ａ
	{0x7fff,0x7fff,0x7fff},									//BG_ID_ROOM_B			//室内Ｂ
	{0x7fff,0x7fff,0x7fff},									//BG_ID_ROOM_C			//室内Ｃ
	{GX_RGB(5,5,7),GX_RGB(5,5,7),GX_RGB(5,5,7)},			//BG_ID_CAVE_A			//洞窟Ａ
	{GX_RGB(5,5,7),GX_RGB(5,5,7),GX_RGB(5,5,7)},			//BG_ID_CAVE_B			//洞窟Ｂ
	{GX_RGB(5,5,7),GX_RGB(5,5,7),GX_RGB(5,5,7)},			//BG_ID_CAVE_C			//洞窟Ｃ
};

//============================================================================================
/**
 * @param
 */
//============================================================================================
static	void	FightInit(PROC *proc)
{
	BATTLE_WORK		*bw=PROC_GetWork(proc);
	SOFT_SPRITE_ARC	ssa;
	int				i;
	RTCDate date;
	RTCTime time;
	u32 seed;

	MI_CpuFill16((void*)GF_MMAP_MainBgPlttAddr(), 0x0000, GF_MMAP_MainBgPlttSize());
	MI_CpuFill16((void*)GF_MMAP_SubBgPlttAddr(), 0x0000, GF_MMAP_SubBgPlttSize());

	//ランダムの種を退避
	bw->seed_temp=gf_get_seed();

	//ランダムの種を取得
	GF_RTC_GetDateTime(&date, &time);
	seed = date.year + date.month * 0x100 * date.day * 0x10000
		+ time.hour * 0x10000 + (time.minute + time.second) * 0x1000000
		+ sys.vsync_counter;
	gf_srand(seed);

	//3D描画系の初期化
	//simple_3DBGInit(HEAPID_BATTLE);
	bw->g3Dman = Fight_3D_Init();

	sys_HBlankIntrStop();	//HBlank割り込み停止

	FontProc_LoadFont(FONT_BUTTON, HEAPID_BATTLE);
	bw->numfont_hp = NUMFONT_Create(0xe, 1, 0xf, HEAPID_BATTLE);
#if 1	//レベルもnumfont_hpと同じ物を使用するようになった 2005.11.10(木)	※check
	bw->numfont_lv = bw->numfont_hp;
#else
	bw->numfont_lv = NUMFONT_Create(0xe, 1, 0xf, HEAPID_BATTLE);
#endif
	
	bw->pfd = PaletteFadeInit(HEAPID_BATTLE);
	PaletteTrans_AutoSet(bw->pfd, TRUE);
	PaletteFadeWorkAllocSet(bw->pfd, FADE_MAIN_BG, 0x200, HEAPID_BATTLE);
	PaletteFadeWorkAllocSet(bw->pfd, FADE_SUB_BG, 0x200, HEAPID_BATTLE);
	PaletteFadeWorkAllocSet(bw->pfd, FADE_MAIN_OBJ, BATTLE_MAIN_OBJPAL_SIZE, HEAPID_BATTLE);
	PaletteFadeWorkAllocSet(bw->pfd, FADE_SUB_OBJ, 0x200, HEAPID_BATTLE);
	
	bw->bgl=GF_BGL_BglIniAlloc(HEAPID_BATTLE);
	bw->win=GF_BGL_BmpWinAllocGet(HEAPID_BATTLE,BATTLE_BMP_WIN_MAX);

	//技エフェクト用キャラ展開バッファを確保
	for(i=0;i<CLIENT_MAX;i++){
		bw->exchr_param[i].exchr_buffer=sys_AllocMemory(HEAPID_BATTLE,EXCHR_BUFFER_SIZE);
	}

	initVramTransferManagerHeap(BATTLE_VRAM_TRANSFER_TASK_NUM,HEAPID_BATTLE);

	//戦闘入力画面システムワーク確保
	bw->bip=BINPUT_SystemInit(bw,BattleWorkMySexGet(bw,CommGetCurrentID()));

	FightBGCreate(bw,bw->bgl);
	GF_BGL_BmpWinAdd(bw->bgl,&bw->win[TALK_WIN_NO],GF_BGL_FRAME1_M,
					 TALK_WIN_X,TALK_WIN_Y,TALK_WIN_SIZE_X,TALK_WIN_SIZE_Y,TALK_MSG_PAL_NO,TALK_MSG_START);
	GF_BGL_BmpWinDataFill(&bw->win[TALK_WIN_NO],0xff);
	BmpTalkWinWrite(&bw->win[TALK_WIN_NO],WINDOW_TRANS_ON,TALK_WIN_CGX_START,TALK_WIN_PAL_NO);

	bw->csp=CATS_AllocMemory(HEAPID_BATTLE);
	CATS_SystemInit(bw->csp,&BattleTcats,&BattleCcmm,BATTLE_OAM_PLTT_MAX);
	//通信アイコン用にキャラ＆パレット制限
	CLACT_U_WmIcon_SetReserveAreaCharManager(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_64K);
	CLACT_U_WmIcon_SetReserveAreaPlttManager(NNS_G2D_VRAM_TYPE_2DMAIN);
	bw->crp=CATS_ResourceCreate(bw->csp);
	CATS_ClactSetInit(bw->csp, bw->crp, BATTLE_ACTOR_MAX);
	CATS_ResourceManagerInit(bw->csp,bw->crp,&BattleResourceList);
	CLACT_U_SetSubSurfaceMatrix(CATS_EasyRenderGet(bw->csp), 0, BATTLE_SUB_ACTOR_DISTANCE);

	BINPUT_DefaultDataSet(bw->bip);
	//サブ画面		アクターシステムが作られてから呼んでください
#if 0	//主人公背景は表示しないようにした	2006.04.18(火) matsuda
	BINPUT_CreateBG(bw->bip, BINPUT_TYPE_WALL_MISSING_PLAYER, TRUE, NULL);
	BINPUT_PlayerBG_SetX(bw->bip, 256);
	BINPUT_EffBGWallSet(bw->bip);
#else
	BINPUT_CreateBG(bw->bip, BINPUT_TYPE_WALL, TRUE, NULL);
#endif
	BINPUT_StockBallActorResourceLoad(bw->bip);

	bw->soft_sprite=SoftSpriteInit(HEAPID_BATTLE);
	SoftSpritePaletteTransParamSet(bw->soft_sprite,0,SOFT_SPRITE_COL_SIZE);	//影の分も転送するようにサイズを変更

	BattleWorkGaugeInit(bw);	//HPゲージ初期化

	FightParticleInit();	//パーティクル初期化
	bw->wsp=WES_Create(HEAPID_BATTLE);

	FightOBJCreate(bw);

	InitTPSystem();			// タッチパネルシステム初期化
	InitTPNoBuff(4);

	//メッセージマネージャ作成
	bw->fight_msg=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_fightmsg_dp_dat,HEAPID_BATTLE);
	bw->attack_msg=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_atkmsg_dat,HEAPID_BATTLE);
	//単語バッファ作成
	bw->wordset=WORDSET_Create(HEAPID_BATTLE);

	bw->msg_buf=STRBUF_Create(BATTLE_MESSAGE_BUF_SIZE,HEAPID_BATTLE);
	
	//パレットデータを退避
	MI_CpuCopy16(PaletteWorkDefaultWorkGet(bw->pfd,FADE_MAIN_BG),&bw->push_bg_palette[0],0x20*7);
	MI_CpuCopy16(PaletteWorkDefaultWorkGet(bw->pfd,FADE_MAIN_OBJ),&bw->push_obj_palette[0],0x20*7);

	{
		int	time;

		time=BattleWorkTimeZoneOffsetGet(bw);
		PaletteWork_Clear(bw->pfd,FADE_MAIN_BG,FADEBUF_ALL,EncountFirstColor[bw->bg_id][time],0,112);
		PaletteWork_Clear(bw->pfd,FADE_MAIN_BG,FADEBUF_ALL,EncountFirstColor[bw->bg_id][time],0x0c*16,0x0c*16+4*16);
		PaletteWork_Clear(bw->pfd,FADE_MAIN_OBJ,FADEBUF_ALL,EncountFirstColor[bw->bg_id][time],0,BATTLE_MAIN_OBJPAL_COLOR_NUM-1);
	}

	PaletteWork_Clear(bw->pfd,FADE_MAIN_BG,FADEBUF_TRANS,0x0000,0x0a*16,0x0a*16+2*16);
	PaletteWork_Clear(bw->pfd,FADE_SUB_BG,FADEBUF_TRANS,0xffff,0,255);
	PaletteWork_Clear(bw->pfd,FADE_SUB_OBJ,FADEBUF_TRANS,0xffff,0,255);

	//メッセージウインドウ用DSアイコンパレットアニメ
	bw->msg_icon=MSG_DsIconFlashAdd(bw->pfd,MSG_DSI_MAINDISP,0x0b,HEAPID_BATTLE);
	MSG_DsIconFlashReq(bw->msg_icon,MSG_DSI_REQ_STOP);

	bw->update_tcb     = TCB_Add(FightUpdate, bw, TCBPRI_FIGHT_UPDATE);
	bw->pinch_tcb      = TCB_Add(FightPinchSECheck, bw, TCBPRI_PINCH_SE_CHECK);

	// 戦闘開始時にメッセージウインドウを下からスクロールさせるタスクの起動
	bw->msgwinmove_tcb = VIntrTCB_Add( StartMsgWinMove, bw, TCBPRI_MSG_WIN_MOVE );
	bw->bg1_scroll     = BATTLE_BG1_V_START_OFFSET;							// スクロール初期値



	FightMsgPrintModeSet(bw);

	//バッグ画面カーソル位置の初期化
	MyItem_BattleBagCursorPosInit(BattleWorkBagCursorGet(bw));

	//ポケモンプログラムアニメシステムワーク生成
	bw->pasp=PokeAnm_AllocMemory(HEAPID_BATTLE,CLIENT_MAX,0);

	//セル転送マネージャの確保
	bw->cell_trans=InitCellTransfer(BATTLE_CELL_TRANS_MAX,HEAPID_BATTLE);
}

//============================================================================================
/**
 * @param
 */
//============================================================================================

static	int		FightMain(PROC *proc)
{
	BATTLE_WORK	*bw=PROC_GetWork(proc);
	int	i;

	if(bw->server_flag){
		if(bw->fight_type&FIGHT_TYPE_SIO){
			ServerMain(bw,bw->server_param);
		}
		else{
			bw->fight_end_flag=ServerMain(bw,bw->server_param);
			ScioBattleRecvData(bw);
		}
	}
	for(i=0;i<bw->client_set_max;i++){
		ClientMain(bw,bw->client_param[i]);
	}

	return bw->fight_end_flag;
}

//============================================================================================
/**
 * @param
 */
//============================================================================================
static	void	FightEnd(PROC *proc)
{
	BATTLE_WORK		*bw=PROC_GetWork(proc);
	BATTLE_PARAM	*bp=PROC_GetParentWork(proc);
	int	i;

	WIPE_SetBrightness(WIPE_DISP_MAIN, WIPE_FADE_BLACK);
	WIPE_SetBrightness(WIPE_DISP_SUB, WIPE_FADE_BLACK);

	//フォルムチェンジするポケモンのチェック
	BattleWorkFormChgCheck(bw);

	//TV番組コール
	//ゲット時は、捕まえたポケモンのPP
	//それ以外は、対戦相手のPP
	if(bw->win_lose_flag!=FIGHT_POKE_GET){
		BattleWorkTVDataSet(bw,PokeParty_GetMemberPointer(bw->poke_party[CLIENT_NO_ENEMY],0));
	}
	
	for(i=0;i<CLIENT_MAX;i++){
		PokeParty_Copy(bw->poke_party[i],bp->poke_party[i]);
		sys_FreeMemoryEz(bw->poke_party[i]);
		MyStatus_Copy(bw->my_status[i],bp->my_status[i]);
		sys_FreeMemoryEz(bw->my_status[i]);
	}

	//メッセージウインドウDSアイコンパレットアニメ開放
	MSG_DsIconFlashDelete(bw->msg_icon);

	//手持ちアイテムコピー
	MyItem_Copy(bw->my_item,bp->my_item);
	sys_FreeMemoryEz(bw->my_item);

	//図鑑ワークコピー
	ZukanWork_Copy(bw->zw,bp->zw);
	sys_FreeMemoryEz(bw->zw);

	//ボックスコピー
	bp->box=bw->box;

	//バッグカーソルコピー
	bp->bag_cursor=bw->bag_cursor;

	//ポケッチデータコピー
	bp->poketch_data=bw->poketch_data;

	///<テレビ：捕獲番組用コピー
	bp->TVWatchBattleWork=bw->TVWatchBattleWork;

	//サファリボールの数コピー
	bp->safari_ball=bw->safari_ball;

	//勝敗フラグコピー
	bp->win_lose_flag=bw->win_lose_flag&FIGHT_ESCAPE_SELECT_OFF;

	//捕獲したポケモンのClientNoをコピー
	bp->get_pokemon_client=bw->get_pokemon_client;

	//レベルアップポケモン情報コピー
	bp->level_up_flag=ST_ServerParamDataGet(bw,bw->server_param,ID_SP_level_up_pokemon,NULL);

	//バトルタワー成績用ワークコピー
	bp->btr.total_turn+=ST_ServerParamDataGet(bw,bw->server_param,ID_SP_total_turn,NULL);
	bp->btr.total_hinshi+=(ST_ServerParamDataGet(bw,bw->server_param,ID_SP_total_hinshi,CLIENT_NO_MINE)+
						   ST_ServerParamDataGet(bw,bw->server_param,ID_SP_total_hinshi,CLIENT_NO_MINE2));
	bp->btr.total_damage+=(ST_ServerParamDataGet(bw,bw->server_param,ID_SP_total_damage,CLIENT_NO_MINE)+
						   ST_ServerParamDataGet(bw,bw->server_param,ID_SP_total_damage,CLIENT_NO_MINE2));

	//技エフェクト用キャラ展開バッファを開放
	for(i=0;i<CLIENT_MAX;i++){
		sys_FreeMemoryEz(bw->exchr_param[i].exchr_buffer);
	}

	sys_FreeMemoryEz(bw->msg_buf);

	//パレットフェードシステム削除
	PaletteFadeWorkAllocFree(bw->pfd, FADE_MAIN_BG);
	PaletteFadeWorkAllocFree(bw->pfd, FADE_SUB_BG);
	PaletteFadeWorkAllocFree(bw->pfd, FADE_MAIN_OBJ);
	PaletteFadeWorkAllocFree(bw->pfd, FADE_SUB_OBJ);
	PaletteFadeFree(bw->pfd);

	//メッセージマネージャの削除
	MSGMAN_Delete(bw->fight_msg);
	MSGMAN_Delete(bw->attack_msg);

	//単語バッファ削除
	WORDSET_Delete(bw->wordset);

	//ポケモンプログラムアニメ削除
	PokeAnm_FreeMemory(bw->pasp);

	Particle_SystemExitAll();
	WES_Delete(bw->wsp);

	ServerEnd(bw->server_param);
	for(i=0;i<bw->client_set_max;i++){
		ClientEnd(bw,bw->client_param[i],bw->proc_mode);

	}

	SoftSpriteEnd(bw->soft_sprite);

	//名前入力をした後は、FightScreenEndを呼ぶ必要はなし
	if(bw->proc_mode!=BW_PROC_MODE_NAMEIN_AFTER){
		FightScreenEnd(bw);		//削除関連まとめてある関数
	}

	//送りカーソルモードをOFF
	MsgPrintSkipFlagSet(MSG_SKIP_OFF);
	MsgPrintAutoFlagSet(MSG_AUTO_OFF);
	MsgPrintTouchPanelFlagSet(MSG_TP_OFF);

	GF_BGL_BmpWinFree(bw->win,BATTLE_BMP_WIN_MAX);

	sys_FreeMemoryEz(bw->bgl);
	sys_FreeMemoryEz(bw->bg_area);
	sys_FreeMemoryEz(bw->pal_area);

	NUMFONT_Delete(bw->numfont_hp);
#if 1	//レベルもnumfont_hpと同じ物を使用するようになった 2005.11.10(木)	※check
	;
#else
	NUMFONT_Delete(bw->numfont_lv);
#endif
	FontProc_UnloadFont(FONT_BUTTON);

	TCB_Delete(bw->update_tcb);
	TCB_Delete(bw->pinch_tcb);

	StopTP();		//タッチパネルの終了

	//3D描画系の初期化
//	simple_3DBGExit();
	Fight_3D_Exit(bw->g3Dman);

	//退避した乱数の種を戻す
	gf_srand(bw->seed_temp);

	//ピンチSEがなっていたら止める
	if(BattleWorkPinchSEFlagGet(bw)){
		Snd_SeStopBySeqNo(BSE_PINCH,0);
	}

	//セル転送マネージャの開放
	DeleteCellTransfer(bw->cell_trans);

	sys_FreeMemoryEz(bw);

	Overlay_UnloadID(FS_OVERLAY_ID(bc_common));
	if(!CommStateIsWifiConnect()){
		Overlay_UnloadID(FS_OVERLAY_ID(ol_zukan));
	}
}

//============================================================================================
/**
 *	戦闘背景画面初期化＆画面生成
 */
//============================================================================================
static	void	FightBGCreate(BATTLE_WORK *bw, GF_BGL_INI *bgl)
{
	GF_Disp_GX_VisibleControlInit();
	WIPE_ResetBrightness(WIPE_DISP_MAIN);
	WIPE_ResetBrightness(WIPE_DISP_SUB);

	//VRAM設定
	{
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
			GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
			GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
			GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
			GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
			GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
			GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
			GX_VRAM_TEX_01_BC,				// テクスチャイメージスロット
			GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
		};
		GF_Disp_SetBank( &vramSetTable );

		//VRAMクリア
		MI_CpuClear32((void*)HW_BG_VRAM, HW_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
	}

	// BG SYSTEM
	{
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	// ブレンド設定
	{
		bw->bld_init_req=1;
	}

	//メイン画面フレーム設定
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
			///<FRAME1_M
			{
//				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
				0, 0, 0x0800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
				BATTLE_BGPRI_WINDOW, 0, 0, FALSE
			},
			///<FRAME2_M
			{
				0, 0, 0x2000, 0, GF_BGL_SCRSIZ_512x512, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
				BATTLE_BGPRI_EFFECT, 0, 0, FALSE
			},
			///<FRAME3_M
			{
				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_256,
				GX_BG_SCRBASE_0x3000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
				BATTLE_BGPRI_BACKGROUND, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME1_M, &TextBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME1_M );
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME2_M, &TextBgCntDat[1], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME2_M );
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME3_M, &TextBgCntDat[2], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME3_M );

		G2_SetBG0Priority(BATTLE_3DBG_PRIORITY);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	}
	//サブ画面フレーム設定
	{
		BINPUT_DefaultFrameSet(bgl);
	}

	//背景グラフィックデータロード
	{
		WINTYPE	win_type;

		win_type=BattleWorkConfigWinTypeGet(bw);

		TalkWinGraphicNullSet(bgl, GF_BGL_FRAME1_M,TALK_WIN_CGX_START,TALK_WIN_PAL_NO,win_type,HEAPID_BATTLE);
		ArcUtil_BgCharSet(ARC_BATT_BG,BATTLE_BG00_NCGR_BIN+bw->bg_id,bgl,GF_BGL_FRAME3_M,0,0,1,HEAPID_BATTLE);
		PaletteWorkSet_Arc(bw->pfd, ARC_BATT_BG, BATT_BG00_D_NCLR+(bw->bg_id*3)+BattleWorkTimeZoneOffsetGet(bw), HEAPID_BATTLE, 
			FADE_MAIN_BG, 0, 0);
		PaletteWorkSet_Arc(bw->pfd, ARC_WINFRAME, TalkWinPalArcGet(win_type), HEAPID_BATTLE, 
			FADE_MAIN_BG, 0x20, TALK_WIN_PAL_NO*0x10);
		PaletteWorkSet_Arc(bw->pfd, ARC_FONT, NARC_font_talk_ncrl, HEAPID_BATTLE, 
			FADE_MAIN_BG, 0x20, 0x0b*0x10);
		ArcUtil_ScrnSet(ARC_BATT_BG,BATTLE_BG00_NSCR_BIN,bgl,GF_BGL_FRAME3_M,0,0,1,HEAPID_BATTLE);
	}

	//ウインドウマスク設定の初期化
	{
		GX_SetVisibleWnd(GX_WNDMASK_NONE);
		GXS_SetVisibleWnd(GX_WNDMASK_NONE);
		G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_NONE,NULL);
		G2_SetWndOutsidePlane(GX_WND_PLANEMASK_NONE,NULL);
	}

	GF_Disp_DispOn();

	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	sys_VBlankFuncChange(FightVBlank,bw);

}

//============================================================================================
/**
 *	戦闘OBJ画面初期化＆画面生成
 */
//============================================================================================
static	void	FightOBJCreate(BATTLE_WORK *bw)
{
	int				ground_id;
	int				i;
	int				sel_mons_no;
	SERVER_PARAM	*sp;
	POKEMON_PARAM	*pp;
	
	ground_id = BattleWorkGroundIDGet(bw);
	
	Ground_ActorResourceSet(&bw->ground[GROUND_MINE],bw,GROUND_TYPE_NORMAL_MINE, ground_id);
	Ground_ActorResourceSet(&bw->ground[GROUND_ENEMY], bw, GROUND_TYPE_NORMAL_ENEMY, ground_id);

	//ボールリソースの先読み
	sp=BattleWorkServerParamGet(bw);
	for(i=0;i<bw->client_set_max;i++){
		sel_mons_no=ST_ServerParamDataGet(bw,sp,ID_SP_sel_mons_no,i);
		pp=BattleWorkPokemonParamGet(bw,i,sel_mons_no);
		ClientBMInit(bw,bw->client_param[i],PokeParaGet(pp,ID_PARA_get_ball,NULL),sel_mons_no);
	}

	//通信アイコンの起動
	WirelessIconEasy();
}

//============================================================================================
/**
 *	戦闘背景画面終了処理
 */
//============================================================================================
static	void	FightBGEnd(GF_BGL_INI *bgl)
{
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME3_M );
	//サブ画面
	BINPUT_FrameExit(bgl);
}

//============================================================================================
/**
 *	戦闘OBJ画面終了処理
 */
//============================================================================================
static	void	FightOBJEnd(BATTLE_WORK *bw)
{
	int	i;

//削除
//	for(i=0;i<GROUND_MAX;i++){
//	  Ground_ActorResourceDel(&bw->ground[i]);
//	}
}

//============================================================================================
/**
 *	戦闘ルーチン群起動パラメータテーブル
 */
//============================================================================================
//1vs1データ
static	const	u8 ClientTypeTable1vs1[]={
	{CLIENT_TYPE_AA},
	{CLIENT_TYPE_BB},
};

//通信1vs1データ
static	const	u8 ClientTypeTableSIO1vs1[][2]={
	{
	{CLIENT_TYPE_AA},
	{CLIENT_TYPE_BB},
	},
	{
	{CLIENT_TYPE_BB},
	{CLIENT_TYPE_AA},
	},
};

//2vs2データ
static	const	u8 ClientTypeTable2vs2[]={
	{CLIENT_TYPE_A},
	{CLIENT_TYPE_B},
	{CLIENT_TYPE_C},
	{CLIENT_TYPE_D},
};

//通信2vs2データ
static	const	u8 ClientTypeTableSIO2vs2[][4]={
	{
	{CLIENT_TYPE_A},
	{CLIENT_TYPE_B},
	{CLIENT_TYPE_C},
	{CLIENT_TYPE_D},
	},
	{
	{CLIENT_TYPE_B},
	{CLIENT_TYPE_A},
	{CLIENT_TYPE_D},
	{CLIENT_TYPE_C},
	}
};

//通信Multiデータ
static	const	u8 ClientTypeTableSIOMulti[][4]={
	//立ち位置0
	{
	{CLIENT_TYPE_A},	//立ち位置0
	{CLIENT_TYPE_D},	//立ち位置1
	{CLIENT_TYPE_C},	//立ち位置2
	{CLIENT_TYPE_B},	//立ち位置3
	},
	//立ち位置1
	{
	{CLIENT_TYPE_B},	//立ち位置0
	{CLIENT_TYPE_C},	//立ち位置1
	{CLIENT_TYPE_D},	//立ち位置2
	{CLIENT_TYPE_A},	//立ち位置3
	},
	//立ち位置2
	{
	{CLIENT_TYPE_A},	//立ち位置0
	{CLIENT_TYPE_D},	//立ち位置1
	{CLIENT_TYPE_C},	//立ち位置2
	{CLIENT_TYPE_B},	//立ち位置3
	},
	//立ち位置3
	{
	{CLIENT_TYPE_B},	//立ち位置0
	{CLIENT_TYPE_C},	//立ち位置1
	{CLIENT_TYPE_D},	//立ち位置2
	{CLIENT_TYPE_A},	//立ち位置3
	},
};

//============================================================================================
/**
 *	戦闘ルーチン群起動
 *
 * @param[in]	battle_work	戦闘ワーク構造体
 * @param[in]	bp			戦闘パラメータ構造体
 */
//============================================================================================
static	void	FightSystemBoot(BATTLE_WORK *bw,BATTLE_PARAM *bp)
{
	int	i,j;
	FIGHT_SYSTEM_BOOT_PARAM	fsbp;
	POKEMON_PARAM *pp;
	POKEMON_PARAM *pp2;

	bw->fight_type=bp->fight_type;

	for(i=0;i<CLIENT_MAX;i++){
		//マイステータス作成
		bw->my_status[i]=MyStatus_AllocWork(HEAPID_BATTLE);
		MyStatus_Copy(bp->my_status[i],bw->my_status[i]);
		//ポケモン鳴き声データ作成
		bw->poke_voice[i]=bp->poke_voice[i];
	}

	//手持ちアイテム作成
	bw->my_item=MyItem_AllocWork(HEAPID_BATTLE);
	MyItem_Copy(bp->my_item,bw->my_item);

	//図鑑ワーク作成
	bw->zw=ZukanWork_AllocWork(HEAPID_BATTLE);
	ZukanWork_Copy(bp->zw,bw->zw);

	//ボックスコピー
	bw->box=bp->box;

	//コンフィグコピー
	bw->config=bp->config;

	// ともだちグループポインタコピー
	bw->friendlist = bp->friendlist;

	//バッグカーソルコピー
	bw->bag_cursor=bp->bag_cursor;

	//ポケッチデータコピー
	bw->poketch_data=bp->poketch_data;

	//場所進化情報コピー
	bw->shinka_place_mode=bp->shinka_place_mode;

	///<テレビ：捕獲番組用コピー
	bw->TVWatchBattleWork=bp->TVWatchBattleWork;

	//サファリボールの数コピー
	bw->safari_ball=bp->safari_ball;

	//地形ID系コピー
	bw->ground_id=bp->ground_id;
	bw->bg_id=bp->bg_id;
	bw->place_id=bp->place_id;

	//時間帯コピー
	bw->time_zone=bp->time_zone;

	//戦闘効果フラグコピー
	bw->battle_status_flag=bp->battle_status_flag;

	//レギュレーションフラグコピー
	bw->regulation_flag=bp->regulation_flag;

	//コンテストを見たかどうかフラグコピー
	bw->contest_see_flag=bp->contest_see_flag;

	//ミズキにあったかどうかフラグコピー
	bw->mizuki_flag=bp->mizuki_flag;

	//フィールド天候をコピー
	bw->weather=bp->weather;

	//カウントアップ用ワークをコピー
	bw->record=bp->record;
	//レコードがNULLだとまずいので、アサート
	GF_ASSERT(bp->record!=NULL);

	//トレーナーIDをセット
	for(i=0;i<CLIENT_MAX;i++){
		bw->trainer_id[i]=bp->trainer_id[i];
		bw->trainer_data[i]=bp->trainer_data[i];
	}

	bw->server_param=ServerInit(bw);

	for(i=0;i<CLIENT_MAX;i++){
		bw->poke_party[i]=PokeParty_AllocPartyWork(HEAPID_BATTLE);
	}

	//通信対戦
	if(bw->fight_type&FIGHT_TYPE_SIO){
		CommCommandBattleInitialize(bw);
		{
			u8	sio_id=CommGetCurrentID();
			int	cnt;

			//サーバ起動チェック
			FightSioServerBootCheck(bw,bp);

			if(bw->fight_type&FIGHT_TYPE_TOWER){
				for(i=0;i<CLIENT_MAX;i++){
					fsbp.client_no=i;
					fsbp.client_type=ClientTypeTable2vs2[i];
					bw->client_param[i]=ClientInit(bw,&fsbp);
				}
				bw->client_set_max=i;
				//手持ちポケモンセット
				for(i=0;i<CLIENT_MAX;i++){
					//client_paramがすべて生成されないと呼べないので、別ループの中に移動
					CT_UISet(bw,bw->client_param[i]);
					PokeParty_Copy(bp->poke_party[i],bw->poke_party[i]);
				}
				for(i=0;i<bw->client_set_max;i++){
					for(j=0;j<PokeParty_GetPokeCount(bw->poke_party[i]);j++){
						pp=PokeParty_GetMemberPointer(bw->poke_party[i],j);
						if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
						   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
						   (PokeParaGet(pp,ID_PARA_hp,NULL))){
							break;
						}
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
				}
				ST_ServerListRowInit(bw,bw->server_param);
#if 0
				pp=PokemonParam_AllocWork(HEAPID_BATTLE);
				for(i=0;i<2;i++){
					for(j=0;j<POKEMON_TEMOTI_MAX;j++){
						PokeParty_Add(bw->poke_party[i],pp);
					}
				}
				sys_FreeMemoryEz(pp);
				for(i=0;i<CLIENT_MAX;i++){
					fsbp.client_no=i;
					fsbp.client_type=ClientTypeTable2vs2[i];
					bw->client_param[i]=ClientInit(bw,&fsbp);
				}
				//手持ちポケモンセット
				for(i=0;i<CLIENT_MAX;i++){
					cnt=PokeParty_GetPokeCount(bp->poke_party[i]);
					if(cnt>3){
						cnt=3;
					}
					//client_paramがすべて生成されないと呼べないので、別ループの中に移動
					CT_UISet(bw,bw->client_param[i]);
					switch(i){
					case CLIENT_NO_MINE:
						for(j=0;j<cnt;j++){
							pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
							pp2=PokeParty_GetMemberPointer(bw->poke_party[0],j);
							PokeCopyPPtoPP(pp,pp2);
						}
						ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,0);
						break;
					case CLIENT_NO_ENEMY:
						for(j=0;j<cnt;j++){
							pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
							pp2=PokeParty_GetMemberPointer(bw->poke_party[1],j+3);
							PokeCopyPPtoPP(pp,pp2);
						}
						ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,3);
						break;
					case CLIENT_NO_MINE2:
						for(j=0;j<cnt;j++){
							pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
							pp2=PokeParty_GetMemberPointer(bw->poke_party[0],j+3);
							PokeCopyPPtoPP(pp,pp2);
						}
						ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,3);
						break;
					case CLIENT_NO_ENEMY2:
						for(j=0;j<cnt;j++){
							pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
							pp2=PokeParty_GetMemberPointer(bw->poke_party[1],j);
							PokeCopyPPtoPP(pp,pp2);
						}
						ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,0);
						break;
					default:
						GF_ASSERT("不正な立ち位置です\n");
						break;
					}
				}
				bw->client_set_max=CLIENT_MAX;
#endif
			}
			else if(bw->fight_type&FIGHT_TYPE_MULTI){
				for(i=0;i<CLIENT_MAX;i++){
					fsbp.client_no=i;
					fsbp.client_type=ClientTypeTableSIOMulti[CommGetStandNo(sio_id)][CommGetStandNo(i)];
					bw->client_param[i]=ClientInit(bw,&fsbp);
				}
				bw->client_set_max=i;
				//手持ちポケモンセット
				for(i=0;i<CLIENT_MAX;i++){
					//client_paramがすべて生成されないと呼べないので、別ループの中に移動
					CT_UISet(bw,bw->client_param[i]);
					PokeParty_Copy(bp->poke_party[i],bw->poke_party[i]);
				}
				for(i=0;i<bw->client_set_max;i++){
					for(j=0;j<PokeParty_GetPokeCount(bw->poke_party[i]);j++){
						pp=PokeParty_GetMemberPointer(bw->poke_party[i],j);
						if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
						   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
						   (PokeParaGet(pp,ID_PARA_hp,NULL))){
							break;
						}
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
				}
				ST_ServerListRowInit(bw,bw->server_param);
#if 0
				pp=PokemonParam_AllocWork(HEAPID_BATTLE);
				for(i=0;i<2;i++){
					for(j=0;j<POKEMON_TEMOTI_MAX;j++){
						PokeParty_Add(bw->poke_party[i],pp);
					}
				}
				sys_FreeMemoryEz(pp);
				for(i=0;i<CLIENT_MAX;i++){
					fsbp.client_no=i;
					fsbp.client_type=ClientTypeTableSIOMulti[CommGetStandNo(sio_id)][CommGetStandNo(i)];
					bw->client_param[i]=ClientInit(bw,&fsbp);
				}
				//手持ちポケモンセット
				for(i=0;i<CLIENT_MAX;i++){
					cnt=PokeParty_GetPokeCount(bp->poke_party[i]);
					if(cnt>3){
						cnt=3;
					}
					//client_paramがすべて生成されないと呼べないので、別ループの中に移動
					CT_UISet(bw,bw->client_param[i]);
					switch(CommGetStandNo(i)){
					case TRAINER_STAND_A:
						for(j=0;j<cnt;j++){
							pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
							pp2=PokeParty_GetMemberPointer(bw->poke_party[0],j);
							PokeCopyPPtoPP(pp,pp2);
						}
						ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,0);
						break;
					case TRAINER_STAND_B:
						for(j=0;j<cnt;j++){
							pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
							pp2=PokeParty_GetMemberPointer(bw->poke_party[1],j+3);
							PokeCopyPPtoPP(pp,pp2);
						}
						ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,3);
						break;
					case TRAINER_STAND_C:
						for(j=0;j<cnt;j++){
							pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
							pp2=PokeParty_GetMemberPointer(bw->poke_party[0],j+3);
							PokeCopyPPtoPP(pp,pp2);
						}
						ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,3);
						break;
					case TRAINER_STAND_D:
						for(j=0;j<cnt;j++){
							pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
							pp2=PokeParty_GetMemberPointer(bw->poke_party[1],j);
							PokeCopyPPtoPP(pp,pp2);
						}
						ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,0);
						break;
					default:
						GF_ASSERT("不正な立ち位置です\n");
						break;
					}
				}
				bw->client_set_max=CLIENT_MAX;
#endif
			}
			//2vs2
			else if(bw->fight_type&FIGHT_TYPE_2vs2){
				for(i=0;i<4;i++){
					fsbp.client_no=i;
					fsbp.client_type=ClientTypeTableSIO2vs2[sio_id][i];
					bw->client_param[i]=ClientInit(bw,&fsbp);
					CT_UISet(bw,bw->client_param[i]);
				}
				bw->client_set_max=i;
				//手持ちポケモンセット
				for(i=0;i<CLIENT_MAX;i++){
					PokeParty_Copy(bp->poke_party[i],bw->poke_party[i]);
				}
				for(i=0;i<bw->client_set_max;i++){
					for(j=0;j<PokeParty_GetPokeCount(bw->poke_party[i&1]);j++){
						pp=PokeParty_GetMemberPointer(bw->poke_party[i&1],j);
						if(i>1){
							if((ST_ServerParamDataGet(bw,bw->server_param,ID_SP_sel_mons_no,i&1)!=j)&&
							   (PokeParaGet(pp,ID_PARA_monsno,NULL))&&
							   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
							   (PokeParaGet(pp,ID_PARA_hp,NULL))){
								break;
							}
						}
						else{
							if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
							   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
							   (PokeParaGet(pp,ID_PARA_hp,NULL))){
								break;
							}
						}
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
				}
			}
			//1vs1
			else{
				for(i=0;i<2;i++){
					fsbp.client_no=i;
					fsbp.client_type=ClientTypeTableSIO1vs1[sio_id][i];
					bw->client_param[i]=ClientInit(bw,&fsbp);
					CT_UISet(bw,bw->client_param[i]);
				}
				bw->client_set_max=i;
				//手持ちポケモンセット
				for(i=0;i<CLIENT_MAX;i++){
					PokeParty_Copy(bp->poke_party[i],bw->poke_party[i]);
					for(j=0;j<PokeParty_GetPokeCount(bw->poke_party[i]);j++){
						pp=PokeParty_GetMemberPointer(bw->poke_party[i],j);
						if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
						   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
						   (PokeParaGet(pp,ID_PARA_hp,NULL))){
							break;
						}
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
				}
			}
		}
		ST_ServerListRowInit(bw,bw->server_param);
	}
	//タッグバトル
	else if(bw->fight_type&FIGHT_TYPE_TAG){
		{
			int	sel_mons_no;

			for(i=0;i<CLIENT_MAX;i++){
				fsbp.client_no=i;
				fsbp.client_type=ClientTypeTable2vs2[i];
				bw->client_param[i]=ClientInit(bw,&fsbp);
				CT_UISet(bw,bw->client_param[i]);
			}
			bw->client_set_max=i;
			//手持ちポケモンセット
			for(i=0;i<CLIENT_MAX;i++){
				PokeParty_Copy(bp->poke_party[i],bw->poke_party[i]);
			}
			for(i=0;i<bw->client_set_max;i++){
				for(j=0;j<BattleWorkPokeCountGet(bw,i);j++){
					pp=BattleWorkPokemonParamGet(bw,i,j);
					if(i==CLIENT_NO_MINE2){
						if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
						   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
						   (PokeParaGet(pp,ID_PARA_hp,NULL))&&
						   (sel_mons_no!=j)){
							break;
						}
					}
					else{
						if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
						   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
						   (PokeParaGet(pp,ID_PARA_hp,NULL))){
							break;
						}
					}
				}
				ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
				if(i==CLIENT_NO_MINE){
					sel_mons_no=j;
				}
			}
		}
		ST_ServerListRowInit(bw,bw->server_param);
		bw->server_flag=1;
#if 0
		{
			int	cnt;
			pp=PokemonParam_AllocWork(HEAPID_BATTLE);
			for(i=0;i<2;i++){
				for(j=0;j<POKEMON_TEMOTI_MAX;j++){
					PokeParty_Add(bw->poke_party[i],pp);
				}
			}
			sys_FreeMemoryEz(pp);
			for(i=0;i<CLIENT_MAX;i++){
				fsbp.client_no=i;
				fsbp.client_type=ClientTypeTable2vs2[i];
				bw->client_param[i]=ClientInit(bw,&fsbp);
				CT_UISet(bw,bw->client_param[i]);
			}
			//手持ちポケモンセット
			for(i=0;i<CLIENT_MAX;i++){
				cnt=PokeParty_GetPokeCount(bp->poke_party[i]);
				switch(i){
				case 0:
					PokeParty_Copy(bp->poke_party[i],bw->poke_party[0]);
					for(j=0;j<cnt;j++){
						pp=PokeParty_GetMemberPointer(bw->poke_party[0],j);
						if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
						   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
						   (PokeParaGet(pp,ID_PARA_hp,NULL))){
							break;
						}
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
					break;
				case 1:
					if(cnt>3){
						cnt=3;
					}
					for(j=0;j<cnt;j++){
						pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
						pp2=PokeParty_GetMemberPointer(bw->poke_party[1],j);
						PokeCopyPPtoPP(pp,pp2);
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,0);
					break;
				case 2:
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,1);
					break;
				case 3:
					if(cnt>3){
						cnt=3;
					}
					for(j=0;j<cnt;j++){
						pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
						pp2=PokeParty_GetMemberPointer(bw->poke_party[1],j+3);
						PokeCopyPPtoPP(pp,pp2);
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,3);
					break;
				}
			}
			bw->client_set_max=CLIENT_MAX;
			ST_ServerListRowInit(bw,bw->server_param);
			bw->server_flag=1;
		}
#endif
	}
	//AIマルチ
	else if(bw->fight_type&FIGHT_TYPE_MULTI){
		for(i=0;i<CLIENT_MAX;i++){
			fsbp.client_no=i;
			fsbp.client_type=ClientTypeTable2vs2[i];
			bw->client_param[i]=ClientInit(bw,&fsbp);
			CT_UISet(bw,bw->client_param[i]);
		}
		bw->client_set_max=i;
		//手持ちポケモンセット
		for(i=0;i<CLIENT_MAX;i++){
			PokeParty_Copy(bp->poke_party[i],bw->poke_party[i]);
		}
		for(i=0;i<bw->client_set_max;i++){
			for(j=0;j<PokeParty_GetPokeCount(bw->poke_party[i]);j++){
				pp=PokeParty_GetMemberPointer(bw->poke_party[i],j);
				if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
				   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
				   (PokeParaGet(pp,ID_PARA_hp,NULL))){
					break;
				}
			}
			ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
		}
		ST_ServerListRowInit(bw,bw->server_param);
		bw->server_flag=1;
#if 0
		{
			int	cnt;
			pp=PokemonParam_AllocWork(HEAPID_BATTLE);
			for(i=0;i<2;i++){
				for(j=0;j<POKEMON_TEMOTI_MAX;j++){
					PokeParty_Add(bw->poke_party[i],pp);
				}
			}
			sys_FreeMemoryEz(pp);
			for(i=0;i<CLIENT_MAX;i++){
				fsbp.client_no=i;
				fsbp.client_type=ClientTypeTable2vs2[i];
				bw->client_param[i]=ClientInit(bw,&fsbp);
				CT_UISet(bw,bw->client_param[i]);
			}
			//手持ちポケモンセット
			for(i=0;i<CLIENT_MAX;i++){
				cnt=PokeParty_GetPokeCount(bp->poke_party[i]);
				if(cnt>3){
					cnt=3;
				}
				switch(i){
				case 0:
					for(j=0;j<cnt;j++){
						pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
						pp2=PokeParty_GetMemberPointer(bw->poke_party[0],j);
						PokeCopyPPtoPP(pp,pp2);
					}
					for(j=0;j<cnt;j++){
						pp=PokeParty_GetMemberPointer(bw->poke_party[0],j);
						if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
						   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
						   (PokeParaGet(pp,ID_PARA_hp,NULL))){
							break;
						}
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
					break;
				case 1:
					for(j=0;j<cnt;j++){
						pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
						pp2=PokeParty_GetMemberPointer(bw->poke_party[1],j);
						PokeCopyPPtoPP(pp,pp2);
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,0);
					break;
				case 2:
					for(j=0;j<cnt;j++){
						pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
						pp2=PokeParty_GetMemberPointer(bw->poke_party[0],j+3);
						PokeCopyPPtoPP(pp,pp2);
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,3);
					break;
				case 3:
					for(j=0;j<cnt;j++){
						pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
						pp2=PokeParty_GetMemberPointer(bw->poke_party[1],j+3);
						PokeCopyPPtoPP(pp,pp2);
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,3);
					break;
				}
			}
			bw->server_flag=1;
			bw->client_set_max=CLIENT_MAX;
		}
#endif
	}
	//2vs2で起動
	else if(bw->fight_type&FIGHT_TYPE_2vs2){
		for(i=0;i<CLIENT_MAX;i++){
			fsbp.client_no=i;
			fsbp.client_type=ClientTypeTable2vs2[i];
			bw->client_param[i]=ClientInit(bw,&fsbp);
			CT_UISet(bw,bw->client_param[i]);
		}
		bw->client_set_max=i;
		//手持ちポケモンセット
		for(i=0;i<CLIENT_MAX;i++){
			PokeParty_Copy(bp->poke_party[i],bw->poke_party[i]);
		}
		for(i=0;i<bw->client_set_max;i++){
			for(j=0;j<PokeParty_GetPokeCount(bw->poke_party[i&1]);j++){
				pp=PokeParty_GetMemberPointer(bw->poke_party[i&1],j);
				if(i>1){
					if((ST_ServerParamDataGet(bw,bw->server_param,ID_SP_sel_mons_no,i&1)!=j)&&
					   (PokeParaGet(pp,ID_PARA_monsno,NULL))&&
					   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
					   (PokeParaGet(pp,ID_PARA_hp,NULL))){
						break;
					}
				}
				else{
					if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
					   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
					   (PokeParaGet(pp,ID_PARA_hp,NULL))){
						break;
					}
				}
			}
			ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
		}
		ST_ServerListRowInit(bw,bw->server_param);
		bw->server_flag=1;
	}
	//1vs1で起動
	else{
		for(i=0;i<2;i++){
			fsbp.client_no=i;
			fsbp.client_type=ClientTypeTable1vs1[i];
			bw->client_param[i]=ClientInit(bw,&fsbp);
			CT_UISet(bw,bw->client_param[i]);
		}
		bw->client_set_max=i;
		//手持ちポケモンセット
		for(i=0;i<CLIENT_MAX;i++){
			PokeParty_Copy(bp->poke_party[i],bw->poke_party[i]);
			for(j=0;j<PokeParty_GetPokeCount(bw->poke_party[i]);j++){
				pp=PokeParty_GetMemberPointer(bw->poke_party[i],j);
				if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
				   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
				   (PokeParaGet(pp,ID_PARA_hp,NULL))){
					break;
				}
			}
			ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
		}
		ST_ServerListRowInit(bw,bw->server_param);
		bw->server_flag=1;
	}

	//ポケパークの時は、相手のトレーナーデータの名前に親の名前を入れておく
	if(bw->fight_type&FIGHT_TYPE_POKE_PARK){
		pp=PokeParty_GetMemberPointer(bw->poke_party[CLIENT_NO_ENEMY],0);
		PokeParaGet(pp,ID_PARA_oyaname,(u8 *)&bw->trainer_data[CLIENT_NO_ENEMY].name);
	}

	//ボス戦参加のなつき度計算
	if(bw->fight_type&FIGHT_TYPE_TRAINER){
		if((BossTrTypeCheck(bw->trainer_data[CLIENT_NO_ENEMY].tr_type)==TRUE)||
		   (BossTrTypeCheck(bw->trainer_data[CLIENT_NO_ENEMY2].tr_type)==TRUE)){
			for(i=0;i<PokeParty_GetPokeCount(bw->poke_party[CLIENT_NO_MINE]);i++){
				pp=PokeParty_GetMemberPointer(bw->poke_party[CLIENT_NO_MINE],i);
				FriendCalc(pp,FRIEND_BOSS_BATTLE,bw->place_id);
			}
			for(i=0;i<PokeParty_GetPokeCount(bw->poke_party[CLIENT_NO_MINE2]);i++){
				pp=PokeParty_GetMemberPointer(bw->poke_party[CLIENT_NO_MINE2],i);
				FriendCalc(pp,FRIEND_BOSS_BATTLE,bw->place_id);
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   トレーナータイプがボスクラスかチェック
 */
//--------------------------------------------------------------
static	BOOL	BossTrTypeCheck(u16 tr_type)
{
	switch(tr_type){
	case TRTYPE_LEADER1:
	case TRTYPE_LEADER2:
	case TRTYPE_LEADER3:
	case TRTYPE_LEADER4:
	case TRTYPE_LEADER5:
	case TRTYPE_LEADER6:
	case TRTYPE_LEADER7:
	case TRTYPE_LEADER8:
	case TRTYPE_BIGFOUR1:
	case TRTYPE_BIGFOUR2:
	case TRTYPE_BIGFOUR3:
	case TRTYPE_BIGFOUR4:
	case TRTYPE_CHAMPION:
		return TRUE;
		break;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   戦闘用3DBG初期化関数
 */
//--------------------------------------------------------------
static GF_G3DMAN * Fight_3D_Init(void)
{
	GF_G3DMAN *g3Dman;
	
	g3Dman = GF_G3DMAN_Init(HEAPID_BATTLE, GF_G3DMAN_LNK, GF_G3DTEX_256K, 
		GF_G3DMAN_LNK, GF_G3DPLT_32K, FightSimpleSetUp);
	return g3Dman;
}

static void FightSimpleSetUp(void)
{
	// ３Ｄ使用面の設定(表示＆プライオリティー)
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority(1);

	// 各種描画モードの設定(シェード＆アンチエイリアス＆半透明)
    G3X_SetShading( GX_SHADING_TOON );
    G3X_AntiAlias( TRUE );
	G3X_AlphaTest( FALSE, 0 );	// アルファテスト　　オフ
	G3X_AlphaBlend( TRUE );		// アルファブレンド　オン
	G3X_EdgeMarking( FALSE );
	G3X_SetFog( FALSE, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0 );

	// クリアカラーの設定
    G3X_SetClearColor(GX_RGB(0,0,0),0,0x7fff,63,FALSE);	//color,alpha,depth,polygonID,fog

	// ビューポートの設定
    G3_ViewPort(0, 0, 255, 191);
}

//--------------------------------------------------------------
/**
 * @brief   戦闘用3DBG終了処理
 *
 * @param   g3Dman		
 */
//--------------------------------------------------------------
static void Fight_3D_Exit(GF_G3DMAN *g3Dman)
{
	GF_G3D_Exit(g3Dman);
}

//--------------------------------------------------------------
/**
 * @brief   戦闘用パーティクル初期化
 */
//--------------------------------------------------------------
static	void	FightParticleInit(void)
{
	//--------------------------------------------------------------
	//	初期化
	//--------------------------------------------------------------
#if 0
	// マネージャがテクスチャイメージスロットを指定スロット分管理できるようにして
	// デフォルトマネージャにする。
	NNS_GfdInitFrmTexVramManager(2, TRUE);
		
	// マネージャがパレットを32KB分管理できるようにして
	// デフォルトマネージャにする。
	NNS_GfdInitFrmPlttVramManager(0x8000, TRUE);

	//ポケモンで使用する分を確保
	NNS_GfdAllocFrmTexVram(0x4000, 0, 0);
	NNS_GfdAllocFrmPlttVram(0x20 * 4, 0, NNS_GFD_ALLOC_FROM_LOW);
#else
	NNSGfdTexKey tex_key;
	NNSGfdPlttKey pltt_key;
	u32 tex_addrs, pltt_addrs;
	
	//ポケモンで使用する分を確保
	tex_key = NNS_GfdAllocTexVram(0x2000 * CLIENT_MAX, 0, 0);
	pltt_key = NNS_GfdAllocPlttVram(0x20 * (CLIENT_MAX+2), 0, 0);		//影の分も追加
	
	GF_ASSERT(tex_key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	GF_ASSERT(pltt_key != NNS_GFD_ALLOC_ERROR_PLTTKEY);
	tex_addrs = NNS_GfdGetTexKeyAddr(tex_key);
	pltt_addrs = NNS_GfdGetPlttKeyAddr(pltt_key);
	OS_TPrintf("ポケモン用に確保したテクスチャVramの先頭アドレス＝%d\n", tex_addrs);
	OS_TPrintf("ポケモン用に確保したパレットVramの先頭アドレス＝%d\n", pltt_addrs);
#endif
	//パーティクルシステムワーク初期化
	Particle_SystemWorkInit();
}

//--------------------------------------------------------------
/**
 * @brief	VBLANK関数
 *
 * @param	work	VBLankには引数が必要なので定義してあるが実際にはNULLが入っているので、アクセスは禁止！
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static	void	FightVBlank(void *work)
{
	BATTLE_WORK *bw = work;

	//乱数の偏りをなくすために、ランダムを呼んでおく
	gf_rand();

	if(bw->bld_init_req){
		bw->bld_init_req=0;
		G2_BlendNone();
		G2S_BlendNone();
	}
	if(bw->vram_init_req){
		bw->vram_init_req=0;
		{
			GF_BGL_DISPVRAM vramSetTable = {
				GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
				GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
				GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
				GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
				GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
				GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
				GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
				GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
				GX_VRAM_TEX_01_BC,				// テクスチャイメージスロット
				GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
			};
			GF_Disp_SetBank( &vramSetTable );
		}
	}
	if(bw->bl_vram_init_req){
		bw->bl_vram_init_req=0;
		{
			GF_BGL_DISPVRAM	tbl = {
				GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
				GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
				GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
				GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
				GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
				GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
				GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
				GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
				GX_VRAM_TEX_0_B,				// テクスチャイメージスロット
				GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
			};
			GF_Disp_SetBank( &tbl );
		}
	}

	SoftSpriteTextureTrans(bw->soft_sprite);
	
	DoVramTransferManager();	// Vram転送マネージャー実行
	CATS_RenderOamTrans();
	PaletteFadeTrans(bw->pfd);

	GF_BGL_VBlankFunc( bw->bgl );

	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

//--------------------------------------------------------------
/**
 * @brief	VBLANK関数
 *
 * @param	work	VBLankには引数が必要なので定義してあるが実際にはNULLが入っているので、アクセスは禁止！
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static	void	FightSioVBlank(void *work)
{
	BATTLE_SIO_WORK *bsw = work;

	PaletteFadeTrans(bsw->pfd);

	DoVramTransferManager();	// Vram転送マネージャー実行

	GF_BGL_VBlankFunc( bsw->bgl );

	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

//--------------------------------------------------------------
/**
 * @brief   メインループの最後に行うシステム関連の更新処理
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		bw
 */
//--------------------------------------------------------------
static void FightUpdate(TCB_PTR tcb, void *work)
{
	BATTLE_WORK *bw = work;

	//通信エラー監視
	CommErrorCheck(HEAPID_BATTLE,bw->bgl);
	
	if((bw->proc_mode==BW_PROC_MODE_FIGHT)||(bw->proc_mode==BW_PROC_MODE_BAG_LIST)){
//ためしに後ろに移動
//		SoftSpriteMain(bw->soft_sprite);
		if(bw->proc_mode==BW_PROC_MODE_FIGHT){
			BattleParticle_Main();
		}
		SoftSpriteMain(bw->soft_sprite);
		CATS_Draw(bw->crp);
		CATS_UpdateTransfer();
		GF_G3_RequestSwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
	}

#ifdef PM_DEBUG		//ポリゴンのラインズオーバーチェック
	if(G3X_IsLineBufferUnderflow() != 0){
		OS_TPrintf("--------------ラインズオーバー発生！！----------\n");
		//GF_ASSERT(0 && "ラインズオーバーが発生しました");
		G3X_ResetLineBufferUnderflow();
	}
	else if(G3X_GetRenderedLineCount() < 10){
		OS_TPrintf("========== ラインズオーバーが発生しそうです… Count = %d\n", 
			G3X_GetRenderedLineCount());
	}
#endif
}

//--------------------------------------------------------------
/**
 * @brief   ピンチSEのチェック
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		bw
 */
//--------------------------------------------------------------
#define	PINCH_SE_WAIT	(4)
#define	PINCH_SE_PAUSE	(2)
static void FightPinchSECheck(TCB_PTR tcb, void *work)
{
	BATTLE_WORK		*bw=work;
	CLIENT_PARAM	*cp;
	GAUGE_WORK		*gauge;
	int				client_no;
	int				client_set_max;
	int				flag;
	int				se_flag;
	int				wait;

	client_set_max=BattleWorkClientSetMaxGet(bw);
	flag=0;
	se_flag=BattleWorkPinchSEFlagGet(bw);

	if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_NO_PINCH_SE){
		return;
	}

	if(se_flag&PINCH_SE_PAUSE){
		if(se_flag&1){
			Snd_SeStopBySeqNo(BSE_PINCH,0);
			BattleWorkPinchSEFlagSet(bw,PINCH_SE_PAUSE);
		}
		return;
	}
	
	for(client_no=0;client_no<client_set_max;client_no++){
		cp=BattleWorkClientParamGet(bw,client_no);
		if(CT_CPClientBootGet(cp)==CLIENT_BOOT_NORMAL){
			gauge=CT_CPGaugeWorkGet(cp);
			if(gauge!=NULL){	
				if(GetHPGaugeDottoColor(gauge->hp,gauge->hpmax,GAUGE_HP_DOTTOMAX)==HP_DOTTO_RED){
					flag|=No2Bit(client_no);
				}
			}
		}
	}
	if((flag)&&(BattleWorkPinchSEFlagGet(bw)==0)){
		Snd_SePlay(BSE_PINCH);
		BattleWorkPinchSEFlagSet(bw,1);
		BattleWorkPinchSEWaitSet(bw,PINCH_SE_WAIT);
	}
	else if((flag==0)&&(BattleWorkPinchSEFlagGet(bw))){
		Snd_SeStopBySeqNo(BSE_PINCH,0);
		BattleWorkPinchSEFlagSet(bw,0);
	}

	//ピンチSEはループではないので、再コールをする
	if(BattleWorkPinchSEFlagGet(bw)){
		wait=BattleWorkPinchSEWaitGet(bw);
		if(Snd_SePlayCheck(BSE_PINCH)==FALSE){
			if(--wait==0){
				Snd_SePlay(BSE_PINCH);
				BattleWorkPinchSEWaitSet(bw,PINCH_SE_WAIT);
			}
			else{
				BattleWorkPinchSEWaitSet(bw,wait);
			}
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief   戦闘開始時にウインドウ面が下から現れるようにする
 * 			BG1OFFSETの値が０になったら終了（自殺します）
 *
 *
 * @param   tcb		
 * @param   work	BATTLE_WORK*
 *
 * @retval  none
 */
//------------------------------------------------------------------
static void StartMsgWinMove( TCB_PTR tcb, void *work )
{
	BATTLE_WORK		*bw=work;

	bw->bg1_scroll += 3;
	
	GF_BGL_ScrollSet( bw->bgl, GF_BGL_FRAME1_M, GF_BGL_SCROLL_Y_SET, bw->bg1_scroll );

	if(bw->bg1_scroll==0){
		TCB_Delete( tcb );
	}
}

//--------------------------------------------------------------
/**
 * @brief   
 *
 * ProcDataで指定した以外のオーバーレイのロードを行う
 *
 */
//--------------------------------------------------------------
static void NitroStaticInit(void)
{
	if(!CommStateIsWifiConnect()){
		Overlay_Load(FS_OVERLAY_ID(ol_zukan), OVERLAY_LOAD_NOT_SYNCHRONIZE);
	}
}

//--------------------------------------------------------------
/**
 * @brief   通信対戦時の対戦前手持ちポケモンリスト表示ルーチン
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		bw
 */
//--------------------------------------------------------------
static	void	FightSioInit(PROC *proc,BATTLE_PARAM *bp)
{
	BATTLE_SIO_WORK	*bsw=PROC_AllocWork(proc,sizeof(BATTLE_SIO_WORK), HEAPID_BATTLE);

	bsw->bp=bp;
	bsw->send_count=0;
	bsw->seq_no=0;
	bsw->time_out_count=0;

	bsw->pfd = PaletteFadeInit(HEAPID_BATTLE);
	PaletteTrans_AutoSet(bsw->pfd, TRUE);
	PaletteFadeWorkAllocSet(bsw->pfd, FADE_MAIN_BG, 0x200, HEAPID_BATTLE);
	PaletteWork_Clear(bsw->pfd,FADE_MAIN_BG,FADEBUF_ALL,0x0000,0,256);
	
	bsw->bgl=GF_BGL_BglIniAlloc(HEAPID_BATTLE);
	bsw->win=GF_BGL_BmpWinAllocGet(HEAPID_BATTLE,1);

	CommCommandBattleCPInitialize(bsw);

	GF_Disp_GX_VisibleControlInit();

	//VRAM設定
	{
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
			GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
			GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
			GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
			GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
			GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
			GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
			GX_VRAM_TEX_01_BC,				// テクスチャイメージスロット
			GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
		};
		GF_Disp_SetBank( &vramSetTable );

		//VRAMクリア
		MI_CpuClear32((void*)HW_BG_VRAM, HW_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
		MI_CpuFill16((void*)HW_BG_PLTT, 0x0000, HW_BG_PLTT_SIZE);
	}

	// BG SYSTEM
	{
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	//メイン画面フレーム設定
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x0800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			BATTLE_BGPRI_WINDOW, 0, 0, FALSE
		};
		GF_BGL_BGControlSet(bsw->bgl, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bsw->bgl, GF_BGL_FRAME1_M );
	}

	//背景グラフィックデータロード
	{
		WINTYPE	win_type;

		win_type=CONFIG_GetWindowType(bp->config);

		TalkWinGraphicNullSet(bsw->bgl, GF_BGL_FRAME1_M,TALK_WIN_CGX_START,TALK_WIN_PAL_NO,win_type,HEAPID_BATTLE);
		PaletteWorkSet_Arc(bsw->pfd, ARC_FONT, NARC_font_talk_ncrl, HEAPID_BATTLE, FADE_MAIN_BG, 0x20, 0x0b*0x10);
		PaletteWorkSet_Arc(bsw->pfd, ARC_WINFRAME, TalkWinPalArcGet(win_type), HEAPID_BATTLE, 
			FADE_MAIN_BG, 0x20, TALK_WIN_PAL_NO*0x10);

		PaletteWork_Clear(bsw->pfd,FADE_MAIN_BG,FADEBUF_TRANS,0x0000,0,256);
	}

	GF_Disp_DispOn();
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);

	GF_BGL_BmpWinAdd(bsw->bgl,bsw->win,GF_BGL_FRAME1_M,
					 TALK_WIN_X,TALK_WIN_Y,TALK_WIN_SIZE_X,TALK_WIN_SIZE_Y,TALK_MSG_PAL_NO,TALK_MSG_START);
	GF_BGL_BmpWinDataFill(bsw->win,0xff);
	BmpTalkWinWrite(bsw->win,WINDOW_TRANS_ON,TALK_WIN_CGX_START,TALK_WIN_PAL_NO);

	//メッセージ表示
	{
		MSGDATA_MANAGER		*msg_m;
		STRBUF				*msg_buf;


		msg_m=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_fightmsg_dp_dat,HEAPID_BATTLE);
		msg_buf=STRBUF_Create(0x100,HEAPID_BATTLE);

		MSGMAN_GetString(msg_m,TaikiMsg,msg_buf);
		GF_STR_PrintSimple(bsw->win,FONT_TALK,msg_buf,0,0,NULL,NULL);

		//メッセージマネージャ関連削除
		STRBUF_Delete(msg_buf);
		MSGMAN_Delete(msg_m);
	}

	sys_VBlankFuncChange(FightSioVBlank,bsw);

	PaletteFadeReq(bsw->pfd,PF_BIT_MAIN_ALL,0xffff,0,16,0,0x0000);

	bsw->time_icon=TimeWaitIconAdd(bsw->win,TALK_WIN_CGX_START);

	//通信アイコンの起動
	WirelessIconEasy();
}

enum{
	FSM_SEQ_FADE_INIT=0,
	FSM_SEQ_FADE_WAIT,
	FSM_SEQ_SYNCHRONIZE,
	FSM_SEQ_SYNCHRONIZE_WAIT,
	FSM_SEQ_SEND_SV_DATA,
	FSM_SEQ_SEND_SV_DATA_WAIT,
	FSM_SEQ_SEND_MS_DATA_MAKE,
	FSM_SEQ_SEND_MS_DATA,
	FSM_SEQ_SEND_MS_DATA_WAIT,
	FSM_SEQ_SEND_TR_DATA_MAKE,
	FSM_SEQ_SEND_TR_DATA,
	FSM_SEQ_SEND_TR_DATA_WAIT,
	FSM_SEQ_SEND_POKE_DATA_MAKE,
	FSM_SEQ_SEND_POKE_DATA,
	FSM_SEQ_SEND_POKE_DATA_WAIT,
	FSM_SEQ_SEND_POKE_VOICE_MAKE,
	FSM_SEQ_SEND_POKE_VOICE,
	FSM_SEQ_SEND_POKE_VOICE_WAIT,

	FSM_SEQ_SEND_FRIEND_LIST_MAKE,
	FSM_SEQ_SEND_FRIEND_LIST,
	FSM_SEQ_SEND_FRIEND_LIST_WAIT,

	FSM_SEQ_SEND_TOWER_TR_DATA1_MAKE,
	FSM_SEQ_SEND_TOWER_TR_DATA1,
	FSM_SEQ_SEND_TOWER_TR_DATA1_WAIT,
	FSM_SEQ_SEND_TOWER_TR_DATA2_MAKE,
	FSM_SEQ_SEND_TOWER_TR_DATA2,
	FSM_SEQ_SEND_TOWER_TR_DATA2_WAIT,
	FSM_SEQ_SEND_TOWER_POKE_DATA1_MAKE,
	FSM_SEQ_SEND_TOWER_POKE_DATA1,
	FSM_SEQ_SEND_TOWER_POKE_DATA1_WAIT,
	FSM_SEQ_SEND_TOWER_POKE_DATA2_MAKE,
	FSM_SEQ_SEND_TOWER_POKE_DATA2,
	FSM_SEQ_SEND_TOWER_POKE_DATA2_WAIT,
	FSM_SEQ_SEND_DATA_END
};

static	BOOL	FightSioMain(PROC *proc)
{
	BATTLE_SIO_WORK	*bsw=PROC_GetWork(proc);
	BOOL			ret;

	//通信エラー監視
	CommErrorCheck(HEAPID_BATTLE,bsw->bgl);

	ret=FALSE;

	switch(bsw->seq_no){
	case FSM_SEQ_FADE_INIT:
		WIPE_ResetBrightness(WIPE_DISP_MAIN);
		bsw->seq_no++;
		break;
	case FSM_SEQ_FADE_WAIT:
		if(PaletteFadeCheck(bsw->pfd)==0){	//輝度変更フェード終了待ちして色々削除
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SYNCHRONIZE:
		CommTimingSyncStart( COMM_BATTLE_STRAT_SYNC_NUM );
		bsw->seq_no++;
		break;
	case FSM_SEQ_SYNCHRONIZE_WAIT:
		if(CommIsTimingSync( COMM_BATTLE_STRAT_SYNC_NUM )){
			CommTimingSyncStart( COMM_BATTLE_SV_SYNC_NUM );
			bsw->time_out_count=0;
			bsw->seq_no++;
		}
		else{
			bsw->time_out_count++;
			if(bsw->time_out_count>SERVER_QUE_TIME_OUT){
				OS_Printf("戦闘開始前タイムアウト発生\n");
				CommStateSetError(COMM_ERROR_RESET_SAVEPOINT);
			}
		}
		break;
	case FSM_SEQ_SEND_SV_DATA:
		if(CommCommandBattleSendServerVersionData(bsw,BattleServerVersion)==TRUE){
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_MS_DATA_MAKE:
		if(CommCommandBattleSendMyStatusDataMake(bsw)==TRUE){
			CommTimingSyncStart( COMM_BATTLE_MS_SYNC_NUM );
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_MS_DATA:
		if(CommCommandBattleSendMyStatusDataWait(bsw)==TRUE){
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_TR_DATA_MAKE:
		if(CommCommandBattleSendTrainerDataMake(bsw)==TRUE){
			CommTimingSyncStart( COMM_BATTLE_TR_SYNC_NUM );
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_TR_DATA:
		if(CommCommandBattleSendTrainerDataWait(bsw)==TRUE){
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_POKE_DATA_MAKE:
		if(CommCommandBattleSendPokeDataMake(bsw)==TRUE){
			CommTimingSyncStart( COMM_BATTLE_POKE_SYNC_NUM );
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_POKE_DATA:
		if(CommCommandBattleSendPokeDataWait(bsw)==TRUE){
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_POKE_VOICE_MAKE:
		if(CommCommandBattleSendPokeVoiceMake(bsw)==TRUE){
			CommTimingSyncStart( COMM_BATTLE_POKEV_SYNC_NUM );
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_POKE_VOICE:
		if(CommCommandBattleSendPokeVoiceWait(bsw)==TRUE){
			OS_Printf("ペラップボイス受信待ち\n");
			bsw->seq_no++;
		}
		break;

	case FSM_SEQ_SEND_FRIEND_LIST_MAKE:
		if(CommCommandBattleSendFriendListMake(bsw)==TRUE){
			OS_Printf("ともだちグループデータ作成終了\n");
			CommTimingSyncStart( COMM_BATTLE_FLIST_SYNC_NUM );
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_FRIEND_LIST:
		if(CommCommandBattleSendFriendListWait(bsw)==TRUE){
			OS_Printf("ともだちグループデータ受信\n");
			bsw->seq_no++;
		}
		break;


	case FSM_SEQ_SEND_TOWER_TR_DATA1_MAKE:
		if((bsw->bp->fight_type&FIGHT_TYPE_TOWER)==0){
			bsw->seq_no=FSM_SEQ_SEND_DATA_END;
			OS_Printf("トレーナーデータ作成\n");
		}
		else{
			//子機側からは送信しない
			if(CommGetCurrentID()){
				CommTimingSyncStart( COMM_BATTLE_TTDATA1_SYNC_NUM );
				bsw->seq_no++;
			}
			else if(CommCommandBattleSendTowerTrDataMake(bsw,CLIENT_NO_ENEMY)==TRUE){
				CommTimingSyncStart( COMM_BATTLE_TTDATA1_SYNC_NUM );
				bsw->seq_no++;
			}
		}
		break;
	case FSM_SEQ_SEND_TOWER_TR_DATA1:
		bsw->send_count=1;
		//子機側からは送信しない
		if(CommGetCurrentID()){
			if(CommIsTimingSync(COMM_BATTLE_TTDATA1_SYNC_NUM)==TRUE){
				bsw->seq_no++;
			}
		}
		else if(CommCommandBattleSendTowerTrDataWait(bsw,CLIENT_NO_ENEMY,COMM_BATTLE_TTDATA1_SYNC_NUM)==TRUE){
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_TOWER_TR_DATA2_MAKE:
		//子機側からは送信しない
		if(CommGetCurrentID()){
			CommTimingSyncStart( COMM_BATTLE_TTDATA2_SYNC_NUM );
			bsw->seq_no++;
		}
		else if(CommCommandBattleSendTowerTrDataMake(bsw,CLIENT_NO_ENEMY2)==TRUE){
			CommTimingSyncStart( COMM_BATTLE_TTDATA2_SYNC_NUM );
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_TOWER_TR_DATA2:
		bsw->send_count=1;
		//子機側からは送信しない
		if(CommGetCurrentID()){
			if(CommIsTimingSync(COMM_BATTLE_TTDATA2_SYNC_NUM)==TRUE){
				bsw->seq_no++;
			}
		}
		else if(CommCommandBattleSendTowerTrDataWait(bsw,CLIENT_NO_ENEMY2,COMM_BATTLE_TTDATA2_SYNC_NUM)==TRUE){
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_TOWER_POKE_DATA1_MAKE:
		//子機側からは送信しない
		if(CommGetCurrentID()){
			CommTimingSyncStart( COMM_BATTLE_TPDATA1_SYNC_NUM );
			bsw->seq_no++;
		}
		else if(CommCommandBattleSendTowerPokeDataMake(bsw,CLIENT_NO_ENEMY)==TRUE){
			CommTimingSyncStart( COMM_BATTLE_TPDATA1_SYNC_NUM );
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_TOWER_POKE_DATA1:
		bsw->send_count=1;
		//子機側からは送信しない
		if(CommGetCurrentID()){
			if(CommIsTimingSync(COMM_BATTLE_TPDATA1_SYNC_NUM)==TRUE){
				bsw->seq_no++;
			}
		}
		else if(CommCommandBattleSendTowerPokeDataWait(bsw,CLIENT_NO_ENEMY,COMM_BATTLE_TPDATA1_SYNC_NUM)==TRUE){
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_TOWER_POKE_DATA2_MAKE:
		//子機側からは送信しない
		if(CommGetCurrentID()){
			CommTimingSyncStart( COMM_BATTLE_TPDATA2_SYNC_NUM );
			bsw->seq_no++;
		}
		else if(CommCommandBattleSendTowerPokeDataMake(bsw,CLIENT_NO_ENEMY2)==TRUE){
			CommTimingSyncStart( COMM_BATTLE_TPDATA2_SYNC_NUM );
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_TOWER_POKE_DATA2:
		bsw->send_count=1;
		//子機側からは送信しない
		if(CommGetCurrentID()){
			if(CommIsTimingSync(COMM_BATTLE_TPDATA2_SYNC_NUM)==TRUE){
				bsw->seq_no++;
			}
		}
		else if(CommCommandBattleSendTowerPokeDataWait(bsw,CLIENT_NO_ENEMY2,COMM_BATTLE_TPDATA2_SYNC_NUM)==TRUE){
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_SV_DATA_WAIT:
	case FSM_SEQ_SEND_MS_DATA_WAIT:
	case FSM_SEQ_SEND_TR_DATA_WAIT:
	case FSM_SEQ_SEND_POKE_DATA_WAIT:
	case FSM_SEQ_SEND_POKE_VOICE_WAIT:
	case FSM_SEQ_SEND_FRIEND_LIST_WAIT:
	case FSM_SEQ_SEND_TOWER_TR_DATA1_WAIT:
	case FSM_SEQ_SEND_TOWER_TR_DATA2_WAIT:
	case FSM_SEQ_SEND_TOWER_POKE_DATA1_WAIT:
	case FSM_SEQ_SEND_TOWER_POKE_DATA2_WAIT:
		if(bsw->send_count==CommGetConnectNum()){

			if(bsw->seq_no==FSM_SEQ_SEND_FRIEND_LIST_WAIT){
				int i;
				for(i=0;i<CLIENT_MAX;i++){
					sys_FreeMemoryEz(bsw->recv_flist[i]);
				}
			}

			bsw->send_count=0;
			bsw->time_out_count=0;
			bsw->seq_no++;
			if(bsw->seq_no==FSM_SEQ_SEND_DATA_END){
				PaletteFadeReq(bsw->pfd,PF_BIT_MAIN_ALL,0xffff,0,0,16,0x0000);
			}

		}
		else{
			bsw->time_out_count++;
			if(bsw->time_out_count>SERVER_QUE_TIME_OUT){
				OS_Printf("戦闘開始前タイムアウト発生\n");
				CommStateSetError(COMM_ERROR_RESET_SAVEPOINT);
			}
		}
		break;
	case FSM_SEQ_SEND_DATA_END:
		if(PaletteFadeCheck(bsw->pfd)==0){	//輝度変更フェード終了待ちして色々削除
			ret=TRUE;
			TimeWaitIconDel(bsw->time_icon);
			CommSetWifiBothNet(FALSE); // 戦闘の通信を同期から非同期に変える
		}
		break;
	}

	return ret;
}

static	void	FightSioEnd(PROC *proc)
{
	BATTLE_SIO_WORK	*bsw=PROC_GetWork(proc);

	sys_VBlankFuncChange(NULL,NULL);

	WIPE_SetBrightness(WIPE_DISP_MAIN, WIPE_FADE_BLACK);

	//パレットフェードシステム削除
	PaletteFadeWorkAllocFree(bsw->pfd, FADE_MAIN_BG);
	PaletteFadeFree(bsw->pfd);

	GF_BGL_BmpWinFree(bsw->win,1);

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_BGL_BGControlExit(bsw->bgl, GF_BGL_FRAME1_M );

	sys_FreeMemoryEz(bsw->bgl);

	sys_FreeMemoryEz(bsw);
}

//--------------------------------------------------------------
/**
 * @brief   通信対戦開始前デモ（マルチ時のポケモンリスト表示）
 */
//--------------------------------------------------------------
static	BOOL	FightListDemoInit(PROC *proc)
{
	BATTLE_WORK		*bw=PROC_AllocWork(proc,sizeof(BATTLE_WORK), HEAPID_BATTLE);
	BATTLE_PARAM	*bp=PROC_GetParentWork(proc);
	u8	sio_id;

	sio_id=CommGetCurrentID();

	MI_CpuClearFast(bw,sizeof(BATTLE_WORK));

	FightSystemBoot(bw,bp);

	//通信対戦でなければデモはなし、バトルタワーもなし
	if(((bw->fight_type&FIGHT_TYPE_SIO)==0)||
		(bw->fight_type&FIGHT_TYPE_TOWER)){
		return FALSE;
	}

	//デモプログラムをロード
	Overlay_Load(FS_OVERLAY_ID(vs_demo), OVERLAY_LOAD_NOT_SYNCHRONIZE);

	//マルチではない時はデモなし
	if((bw->fight_type&FIGHT_TYPE_MULTI)==0){
		return FALSE;
	}

	bw->vdd=sys_AllocMemory(HEAPID_BATTLE,sizeof(VS_DEMO_DATA));
	MI_CpuClearFast(bw->vdd,sizeof(VS_DEMO_DATA));

	//マルチ対戦
	switch(CommGetStandNo(sio_id)){
	case 0:
	case 3:
		bw->vdd->pp[0]=bw->poke_party[sio_id];
		bw->vdd->pp[2]=bw->poke_party[BattleWorkPartnerClientNoGet(bw,sio_id)];
		break;
	case 1:
	case 2:
		bw->vdd->pp[0]=bw->poke_party[BattleWorkPartnerClientNoGet(bw,sio_id)];
		bw->vdd->pp[2]=bw->poke_party[sio_id];
		break;
	}
	bw->vdd->heap=HEAPID_BATTLE;
	bw->vdd->mode=VSD_MODE_MULTI;
	switch(CommGetStandNo(sio_id)){
	case 0:
	case 3:
		bw->vdd->type=VSD_TYPE_LEFT;
		break;
	case 1:
	case 2:
		bw->vdd->type=VSD_TYPE_RIGHT;
		break;
	}

	VSDemo_TaskAdd(bw->vdd);

	return TRUE;
}

static	BOOL	FightListDemoMain(PROC *proc)
{
	int	i;
	BATTLE_WORK		*bw=PROC_GetWork(proc);

	if(bw->vdd->end_flg){
		for(i=0;i<CLIENT_MAX;i++){
			if(bw->vdd->name[i]!=NULL){
				sys_FreeMemoryEz(bw->vdd->name[i]);
			}
		}
		sys_FreeMemoryEz(bw->vdd);
		return TRUE;
	}

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   通信対戦開始前デモ
 */
//--------------------------------------------------------------
static	BOOL	FightMenuDemoInit(PROC *proc)
{
	BATTLE_WORK		*bw=PROC_GetWork(proc);
	BATTLE_PARAM	*bp=PROC_GetParentWork(proc);
	u8	sio_id;
	int	i;

	sio_id=CommGetCurrentID();

	//通信対戦でなければデモはなし、バトルタワーもなし
	if(((bw->fight_type&FIGHT_TYPE_SIO)==0)||
		(bw->fight_type&FIGHT_TYPE_TOWER)){
		return FALSE;
	}

	bw->vdd=sys_AllocMemory(HEAPID_BATTLE,sizeof(VS_DEMO_DATA));
	MI_CpuClearFast(bw->vdd,sizeof(VS_DEMO_DATA));

	//マルチ対戦
	if(bw->fight_type&FIGHT_TYPE_MULTI){
		for(i=0;i<CLIENT_MAX;i++){
			bw->vdd->pp[CommGetStandNo(i)]=bw->poke_party[i];
			bw->vdd->name[CommGetStandNo(i)]=MyStatus_CreateNameString(bw->my_status[i],HEAPID_BATTLE);
			OS_TPrintf("sio_id:%d stand_no:%d pp:%08x\n",i,CommGetStandNo(i),bw->vdd->pp[CommGetStandNo(i)]);
		}
		bw->vdd->heap=HEAPID_BATTLE;
		bw->vdd->mode=VSD_MODE_IN;
		bw->vdd->type=VSD_TYPE_MULTI;
	}
	else{
		bw->vdd->pp[CommGetStandNo(sio_id)]=bw->poke_party[sio_id];
		bw->vdd->pp[CommGetStandNo(sio_id^1)]=bw->poke_party[sio_id^1];
		bw->vdd->name[CommGetStandNo(sio_id)]=MyStatus_CreateNameString(bw->my_status[sio_id],HEAPID_BATTLE);
		bw->vdd->name[CommGetStandNo(sio_id^1)]=MyStatus_CreateNameString(bw->my_status[sio_id^1],HEAPID_BATTLE);
		bw->vdd->heap=HEAPID_BATTLE;
		bw->vdd->mode=VSD_MODE_IN;
		bw->vdd->type=VSD_TYPE_NORMAL;
	}

	VSDemo_TaskAdd(bw->vdd);

	return TRUE;
}

static	BOOL	FightMenuDemoMain(PROC *proc)
{
	int	i;
	BATTLE_WORK		*bw=PROC_GetWork(proc);

	if(bw->vdd->end_flg){
		for(i=0;i<CLIENT_MAX;i++){
			if(bw->vdd->name[i]!=NULL){
				sys_FreeMemoryEz(bw->vdd->name[i]);
			}
		}
		sys_FreeMemoryEz(bw->vdd);
		return TRUE;
	}

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   通信対戦結果デモ
 */
//--------------------------------------------------------------
static	BOOL	FightWinLoseDemoInit(PROC *proc)
{
	BATTLE_PARAM	*bp=PROC_GetParentWork(proc);
	VS_DEMO_DATA	*vdd;
	u8	sio_id;
	int	i;

	sio_id=CommGetCurrentID();

	//通信対戦でなければデモはなし、バトルタワーもなし
	if(((bp->fight_type&FIGHT_TYPE_SIO)==0)||
		(bp->fight_type&FIGHT_TYPE_TOWER)){
		return FALSE;
	}

	//デモプログラムをロード
	Overlay_Load(FS_OVERLAY_ID(vs_demo), OVERLAY_LOAD_NOT_SYNCHRONIZE);

	vdd=sys_AllocMemory(HEAPID_BATTLE,sizeof(VS_DEMO_DATA));
	bp->work=vdd;
	MI_CpuClearFast(vdd,sizeof(VS_DEMO_DATA));
	vdd->bp=bp;

	switch(bp->win_lose_flag){
	case FIGHT_WIN:
		if(!CommStateIsWifiConnect()){
			RECORD_Inc(bp->record,RECID_COMM_BTL_WIN);
		}
		else{
			RECORD_Inc(bp->record,RECID_WIFI_BTL_WIN);
		}
		break;
	case FIGHT_LOSE:
		if(!CommStateIsWifiConnect()){
			RECORD_Inc(bp->record,RECID_COMM_BTL_LOSE);
		}
		else{
			RECORD_Inc(bp->record,RECID_WIFI_BTL_LOSE);
		}
		break;
	case FIGHT_DRAW:
	case FIGHT_ESCAPE:
		if(!CommStateIsWifiConnect()){
			RECORD_Inc(bp->record,RECID_COMM_BTL_DRAW);
		}
		else{
			RECORD_Inc(bp->record,RECID_WIFI_BTL_DRAW);
		}
		break;
	}

	//マルチ対戦
	if(bp->fight_type&FIGHT_TYPE_MULTI){
		for(i=0;i<CLIENT_MAX;i++){
			vdd->pp[CommGetStandNo(i)]=bp->poke_party[i];
			vdd->name[CommGetStandNo(i)]=MyStatus_CreateNameString(bp->my_status[i],HEAPID_BATTLE);
		}
		vdd->heap=HEAPID_BATTLE;
		vdd->mode=VSD_MODE_END;
		vdd->type=VSD_TYPE_MULTI;
		if(bp->win_lose_flag!=FIGHT_ESCAPE){
			vdd->result=bp->win_lose_flag;
		}
		else{
			vdd->result=VSD_RESULT_DRAW;
		}
	}
	else{
		vdd->pp[CommGetStandNo(sio_id)]=bp->poke_party[sio_id];
		vdd->pp[CommGetStandNo(sio_id^1)]=bp->poke_party[sio_id^1];
		vdd->name[CommGetStandNo(sio_id)]=MyStatus_CreateNameString(bp->my_status[sio_id],HEAPID_BATTLE);
		vdd->name[CommGetStandNo(sio_id^1)]=MyStatus_CreateNameString(bp->my_status[sio_id^1],HEAPID_BATTLE);
		vdd->heap=HEAPID_BATTLE;
		vdd->mode=VSD_MODE_END;
		vdd->type=VSD_TYPE_NORMAL;
		if(bp->win_lose_flag!=FIGHT_ESCAPE){
			vdd->result=bp->win_lose_flag;
		}
		else{
			vdd->result=VSD_RESULT_DRAW;
		}
	}

	VSDemo_TaskAdd(vdd);

	return TRUE;
}

static	BOOL	FightWinLoseDemoMain(PROC *proc)
{
	int	i;
	BATTLE_PARAM	*bp=PROC_GetParentWork(proc);
	VS_DEMO_DATA	*vdd=bp->work;

	if(vdd->end_flg){
		for(i=0;i<CLIENT_MAX;i++){
			if(vdd->name[i]!=NULL){
				sys_FreeMemoryEz(vdd->name[i]);
			}
		}
		sys_FreeMemoryEz(vdd);
		return TRUE;
	}

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   戦闘時の送りカーソルモードの設定
 */
//--------------------------------------------------------------
static void	FightMsgPrintModeSet(BATTLE_WORK *bw)
{
	if(bw->fight_type&(FIGHT_TYPE_SIO|FIGHT_TYPE_GET_DEMO)){
		//文字キー送りをAUTOに
		MsgPrintAutoFlagSet(MSG_AUTO_ON);
	}
	else{
		MsgPrintAutoFlagSet(MSG_AUTO_SKIP_ON);
		MsgPrintSkipFlagSet(MSG_SKIP_ON);
		MsgPrintTouchPanelFlagSet(MSG_TP_ON);
	}
}

//--------------------------------------------------------------
/**
 * @brief   通信対戦時のサーバ起動チェック
 */
//--------------------------------------------------------------
static	void	FightSioServerBootCheck(BATTLE_WORK *bw,BATTLE_PARAM *bp)
{
	int	i,j,work;
	int	sio_id,max;
	int	id[CLIENT_MAX];
	int	version[CLIENT_MAX];

	for(i=0;i<CLIENT_MAX;i++){
		id[i]=i;
		version[i]=bp->server_version[i];
	}

	sio_id=CommGetCurrentID();
	max=CommGetConnectNum();

	for(i=0;i<max-1;i++){
		for(j=i+1;j<max;j++){
			if(version[i]<version[j]){
				work=id[i];
				id[i]=id[j];
				id[j]=work;
				work=version[i];
				version[i]=version[j];
				version[j]=work;
			}
		}
	}

	if(id[0]==sio_id){
		bw->server_flag=1;
	}
}

