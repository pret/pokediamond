//==============================================================================
/**
 * @file	visual.c
 * @brief	ビジュアル部門
 * @author	matsuda
 * @date	2005.12.10(土)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "battle/battle_common.h"
#include "system/clact_tool.h"
#include "system/palanm.h"
#include "system/pmfprint.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "system/softsprite.h"
#include "system/gra_tool.h"

#include "wazaeffect/battle_particle.h"
#include "system/particle.h"

#include "system/fontproc.h"
#include "system/msgdata.h"

#include "system/brightness.h"
#include "system/snd_tool.h"

#include "communication/communication.h"

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "msgdata/msg.naix"

#include "con_tool.h"
#include "visual.h"
#include "visual_tool.h"
#include "visual_tcb_pri.h"
#include "visual_id.h"
#include "visual_order.h"
#include "adv_tool.h"

#include "system/window.h"
#include "system/wipe.h"
#include "savedata/config.h"
#include "communication/wm_icon.h"

#include "system/pm_overlay.h"
FS_EXTERN_OVERLAY(bc_common);
FS_EXTERN_OVERLAY(ol_imageclip);



//==============================================================================
//	定数定義
//==============================================================================
///現在の動作状態
enum{
	VPW_PROC_MODE_INIT,		///<初期化中
	VPW_PROC_MODE_MAIN,		///<メイン
	VPW_PROC_MODE_ETC,		///<それ以外
};

///Vram転送マネージャータスク数
#define VISUAL_VRAM_TRANSFER_TASK_NUM	(BATTLE_VRAM_TRANSFER_TASK_NUM)

//--------------------------------------------------------------
//	BMPウィンドウ
//--------------------------------------------------------------
///BMPウィンドウCGXエリア開始位置(オフセット)
#define BMPWIN_CGX_START			(TALK_WIN_CGX_SIZ + VISUAL_TALKWIN_CGX_OFFSET)

#define BMPWIN_TALK_COLOR			(13)
#define BMPWIN_TALK_CGX_OFFSET		(BMPWIN_CGX_START)

//--------------------------------------------------------------
//	CL_ACT用の定数定義
//--------------------------------------------------------------
///メイン	OAM管理領域・開始
#define VISUAL_OAM_START_MAIN			(BATTLE_OAM_START_MAIN)
///メイン	OAM管理領域・終了
#define VISUAL_OAM_END_MAIN				(BATTLE_OAM_END_MAIN)
///メイン	アフィン管理領域・開始
#define VISUAL_OAM_AFFINE_START_MAIN		(BATTLE_OAM_AFFINE_START_MAIN)
///メイン	アフィン管理領域・終了
#define VISUAL_OAM_AFFINE_END_MAIN		(BATTLE_OAM_AFFINE_END_MAIN)
///サブ	OAM管理領域・開始
#define VISUAL_OAM_START_SUB				(BATTLE_OAM_START_SUB)
///サブ	OAM管理領域・終了
#define VISUAL_OAM_END_SUB				(BATTLE_OAM_END_SUB)
///サブ アフィン管理領域・開始
#define VISUAL_OAM_AFFINE_START_SUB		(BATTLE_OAM_AFFINE_START_SUB)
///サブ	アフィン管理領域・終了
#define VISUAL_OAM_AFFINE_END_SUB		(BATTLE_OAM_AFFINE_END_SUB)

///キャラマネージャ：キャラクタID管理数(上画面＋下画面)
#define VISUAL_CHAR_MAX					(BATTLE_CHAR_MAX)
///キャラマネージャ：メイン画面サイズ(byte単位)
#define VISUAL_CHAR_VRAMSIZE_MAIN		(BATTLE_CHAR_VRAMSIZE_MAIN)
///キャラマネージャ：サブ画面サイズ(byte単位)
#define VISUAL_CHAR_VRAMSIZE_SUB			(BATTLE_CHAR_VRAMSIZE_SUB)

///メイン画面＋サブ画面で使用するアクター総数
#define VISUAL_ACTOR_MAX					(BATTLE_ACTOR_MAX)

///OBJで使用するパレット本数(上画面＋下画面)
#define VISUAL_OAM_PLTT_MAX				(BATTLE_OAM_PLTT_MAX)

///転送モード 3D = 0 main = 1 sub = 2 main/sub = 3
#define VISUAL_OAM_VRAM_TRANS			(BATTLE_OAM_VRAM_TRANS)

///OAMリソース：キャラ登録最大数(メイン画面 + サブ画面)
#define VISUAL_OAMRESOURCE_CHAR_MAX		(BATTLE_OAMRESOURCE_CHAR_MAX)
///OAMリソース：パレット登録最大数(メイン画面 + サブ画面)
#define VISUAL_OAMRESOURCE_PLTT_MAX		(BATTLE_OAMRESOURCE_PLTT_MAX)
///OAMリソース：セル登録最大数
#define VISUAL_OAMRESOURCE_CELL_MAX		(BATTLE_OAMRESOURCE_CELL_MAX)
///OAMリソース：セルアニメ登録最大数
#define VISUAL_OAMRESOURCE_CELLANM_MAX	(BATTLE_OAMRESOURCE_CELLANM_MAX)
///OAMリソース：マルチセル登録最大数
#define VISUAL_OAMRESOURCE_MCELL_MAX		(BATTLE_OAMRESOURCE_MCELL_MAX)
///OAMリソース：マルチセルアニメ登録最大数
#define VISUAL_OAMRESOURCE_MCELLANM_MAX	(BATTLE_OAMRESOURCE_MCELLANM_MAX)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///サブ画面BGのスクリーンクリアコード
#define SUB_BG_CLEAR_CODE		(0)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///どんちょうのパレット番号
#define DONTYOU_PALNO			(0xc)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///どんちょうフェードアウト：フェード速度
#define DFO_WAIT			(16)//(3)
///どんちょうフェードアウト：開始EVY
#define DFO_START_EVY		(0)
///どんちょうフェードアウト：終了EVY
#define DFO_END_EVY			(-16)
///どんちょうフェードアウト：変更後の色
#define DFO_NEXT_RGB		(0x0000)

///どんちょうフェードイン：フェード速度
#define DFI_WAIT			(2)
///どんちょうフェードイン：開始EVY
#define DFI_START_EVY		(DFO_END_EVY)
///どんちょうフェードイン：終了EVY
#define DFI_END_EVY			(4)
///どんちょうフェードイン：変更後の色
#define DFI_NEXT_RGB		(DFO_NEXT_RGB)

///どんちょうフェードイン最後：フェード速度
#define DFE_WAIT			(1)
///どんちょうフェードイン最後：開始EVY
#define DFE_START_EVY		(DFI_END_EVY)
///どんちょうフェードイン最後：終了EVY
#define DFE_END_EVY			(0)
///どんちょうフェードイン最後：変更後の色
#define DFE_NEXT_RGB		(DFO_NEXT_RGB)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///ビジュアル部門開始時の最初のフェードインのウェイト
#define VISUAL_START_FADEIN_WAIT		(6)


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static void VisualVBlank(void *work);
static void VisualUpdate(TCB_PTR tcb, void *work);
static void VisualSys_VramBankSet(GF_BGL_INI *bgl);
static void VisualSys_DefaultBmpWinAdd(VISUAL_PROC_WORK *vpw);
static void VisualSystemWorkInit(VISUAL_PROC_WORK *vpw);
static void VisualDefaultOBJSet(VISUAL_PROC_WORK *vpw);
static void VisualDefaultOBJDel(VISUAL_PROC_WORK *vpw);
static void VisualDefaultOBJSet_Sub(VISUAL_PROC_WORK *vpw);
static void VisualDefaultOBJDel_Sub(VISUAL_PROC_WORK *vpw);
static void VisualDefaultBGSet(VISUAL_PROC_WORK *vpw);
static void VisualDefaultBGDel(VISUAL_PROC_WORK *vpw);
static void VisualDefaultBGSet_Sub(VISUAL_PROC_WORK *vpw);
static void VisualDefaultBGDel_Sub(VISUAL_PROC_WORK *vpw);
static int VisualSeq_Init(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_JudgeFastTalk(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_EndTalk(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_End(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static void VisualParticleInit(void);
static int VisualSeq_PokeSelect(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_Appear(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_TrainerIn(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_IntroduceTalk(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_AppearEffect(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_TrainerOut(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_Advance(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_AudienceEvaluate(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_PokeOut(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_NextPoke(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_DonchouUp(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_DonchouDown(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_DonchouFadeOut(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_DonchouFadeIn(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_FullFadeIn(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_DonchouEffectUp(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);


//==============================================================================
//	データ
//==============================================================================

//==============================================================================
//	シーケンステーブル
//==============================================================================
///VisualMainSeqTblの戻り値として使用
enum{
	VSRET_CONTINUE,		///<現状維持
	VSRET_NEXT,			///<次のシーケンスへ
	VSRET_SELECT_SEQ,	///<select_seqワークに入っているシーケンスへ進む
	VSRET_END,			///<終了
};

///ビジュアル部門メイン関数のシーケンステーブル
static int (* const VisualMainSeqTbl[])(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local) = {
	VisualSeq_Init,
	VisualSeq_JudgeFastTalk,
	VisualSeq_PokeSelect,
	
	VisualSeq_DonchouFadeOut,
	
	VisualSeq_IntroduceTalk,

	VisualSeq_Appear,
//	VisualSeq_DonchouFadeIn,
	VisualSeq_DonchouEffectUp,
//	VisualSeq_FullFadeIn,
	
//	VisualSeq_DonchouUp,

//	VisualSeq_TrainerIn,
//	VisualSeq_AppearEffect,
//	VisualSeq_TrainerOut,
//	VisualSeq_Advance,
	VisualSeq_AudienceEvaluate,
//	VisualSeq_PokeOut,
//	VisualSeq_DonchouDown,
	VisualSeq_NextPoke,
	VisualSeq_EndTalk,
	VisualSeq_End,
};
///VisualMainSeqTblのシーケンス番号	※VisualMainSeqTblと並びを同じにしておくこと！！
enum{
	VSEQ_INIT,
	VSEQ_JUDGE_FAST_TALK,
	VSEQ_POKE_SELECT,
	
	VSEQ_DONCHOU_FADEOUT,

	VSEQ_INTRODUCE_TALK,

	VSEQ_APPEAR,
//	VSEQ_DONCHOU_FADEIN,
	VSEQ_DONCHOU_EFFECT_UP,
//	VSEQ_FULL_FADEIN,
	
//	VSEQ_DONCHOU_UP,

//	VSEQ_TRAINER_IN,
//	VSEQ_APPEAR_EFFECT,
//	VSEQ_TRAINER_OUT,
//	VSEQ_ADVANCE,
	VSEQ_AUDIENCE_EVALUATE,
//	VSEQ_POKE_OUT,
//	VSEQ_DONCHOU_DOWN,
	VSEQ_NEXT_POKE,
	VSEQ_END_TALK,
	VSEQ_END,
};

//==============================================================================
//	CLACT用データ
//==============================================================================
static	const TCATS_OAM_INIT VisualTcats = {
	VISUAL_OAM_START_MAIN, VISUAL_OAM_END_MAIN,
	VISUAL_OAM_AFFINE_START_MAIN, VISUAL_OAM_AFFINE_END_MAIN,
	VISUAL_OAM_START_SUB, VISUAL_OAM_END_SUB,
	VISUAL_OAM_AFFINE_START_SUB, VISUAL_OAM_AFFINE_END_SUB,
};

static	const TCATS_CHAR_MANAGER_MAKE VisualCcmm = {
	VISUAL_CHAR_MAX,
	VISUAL_CHAR_VRAMSIZE_MAIN,
	VISUAL_CHAR_VRAMSIZE_SUB,
	GX_OBJVRAMMODE_CHAR_1D_64K,
	GX_OBJVRAMMODE_CHAR_1D_32K
};

static const TCATS_RESOURCE_NUM_LIST VisualResourceList = {
	VISUAL_OAMRESOURCE_CHAR_MAX,
	VISUAL_OAMRESOURCE_PLTT_MAX,
	VISUAL_OAMRESOURCE_CELL_MAX,
	VISUAL_OAMRESOURCE_CELLANM_MAX,
	VISUAL_OAMRESOURCE_MCELL_MAX,
	VISUAL_OAMRESOURCE_MCELLANM_MAX,
};



//--------------------------------------------------------------
/**
 * @brief   プロセス関数：初期化
 *
 * @param   proc		プロセスデータ
 * @param   seq			シーケンス
 *
 * @retval  処理状況
 */
//--------------------------------------------------------------
PROC_RESULT VisualProc_Init( PROC * proc, int * seq )
{
	VISUAL_PROC_WORK *vpw;

	sys_VBlankFuncChange(NULL, NULL);	// VBlankセット
	sys_HBlankIntrStop();	//HBlank割り込み停止

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane(0);
	GXS_SetVisiblePlane(0);
	GX_SetVisibleWnd(GX_WNDMASK_NONE);
	GXS_SetVisibleWnd(GX_WNDMASK_NONE);
	G2_BlendNone();
	G2S_BlendNone();

	sys_CreateHeap(HEAPID_BASE_APP, HEAPID_VISUAL, VISUAL_ALLOC_SIZE);

	vpw = PROC_AllocWork(proc, sizeof(VISUAL_PROC_WORK), HEAPID_VISUAL );
	MI_CpuClear8(vpw, sizeof(VISUAL_PROC_WORK));

//	simple_3DBGInit(HEAPID_VISUAL);
	vpw->g3Dman = ADV_Contest_3D_Init(HEAPID_VISUAL);

	vpw->consys = PROC_GetParentWork(proc);
	vpw->consys->class_proc = vpw;
	vpw->consys->class_flag = CON_CLASS_VISUAL;
	vpw->sys.c_game = &vpw->consys->c_game;
	VisualSystemWorkInit(vpw);
	
	//パレットフェードシステム作成
	vpw->sys.pfd = PaletteFadeInit(HEAPID_VISUAL);
	PaletteTrans_AutoSet(vpw->sys.pfd, TRUE);
	PaletteFadeWorkAllocSet(vpw->sys.pfd, FADE_MAIN_BG, 0x200, HEAPID_VISUAL);
	PaletteFadeWorkAllocSet(vpw->sys.pfd, FADE_SUB_BG, 0x200, HEAPID_VISUAL);
	PaletteFadeWorkAllocSet(vpw->sys.pfd, FADE_MAIN_OBJ, CONTEST_MAIN_OBJPAL_SIZE, HEAPID_VISUAL);
	PaletteFadeWorkAllocSet(vpw->sys.pfd, FADE_SUB_OBJ, 0x200, HEAPID_VISUAL);
	
	vpw->sys.bgl = GF_BGL_BglIniAlloc(HEAPID_VISUAL);

	initVramTransferManagerHeap(VISUAL_VRAM_TRANSFER_TASK_NUM, HEAPID_VISUAL);

	sys_KeyRepeatSpeedSet( 4, 8 );

//	vpw->aip = AINPUT_SystemInit(&vpw->sys);

	//VRAM割り当て設定
	VisualSys_VramBankSet(vpw->sys.bgl);

	// タッチパネルシステム初期化
	InitTPSystem();
	InitTPNoBuff(4);

	// ボタン用フォントを読み込み
	FontProc_LoadFont(FONT_BUTTON, HEAPID_VISUAL);

	// 引数を保存
//	SetVisualWorkParameter(vpw, (NAMEIN_PARAM*)PROC_GetParentWork(proc));

	//アクターシステム作成
	vpw->sys.csp=CATS_AllocMemory(HEAPID_VISUAL);
	CATS_SystemInit(vpw->sys.csp,&VisualTcats,&VisualCcmm,VISUAL_OAM_PLTT_MAX);
	//通信アイコン用にキャラ＆パレット制限
	CLACT_U_WmIcon_SetReserveAreaCharManager(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_64K);
	CLACT_U_WmIcon_SetReserveAreaPlttManager(NNS_G2D_VRAM_TYPE_2DMAIN);
	vpw->sys.crp=CATS_ResourceCreate(vpw->sys.csp);
	CATS_ClactSetInit(vpw->sys.csp, vpw->sys.crp, VISUAL_ACTOR_MAX);
	CATS_ResourceManagerInit(vpw->sys.csp,vpw->sys.crp,&VisualResourceList);
	CLACT_U_SetSubSurfaceMatrix(CATS_EasyRenderGet(vpw->sys.csp), 0, VISUAL_SUB_ACTOR_DISTANCE);

	vpw->sys.soft_sprite = SoftSpriteInit(HEAPID_VISUAL);
	VisualParticleInit();	//パーティクル初期化

	//メッセージマネージャ作成
	vpw->sys.visual_msg = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_cmsg_visual_dat, 
		HEAPID_VISUAL);
	vpw->sys.wordset = WORDSET_Create(HEAPID_VISUAL);
	vpw->sys.msg_buf = STRBUF_Create(VISUAL_MESSAGE_BUF_SIZE, HEAPID_VISUAL);
	
	//常駐BGセット
	VisualDefaultBGSet(vpw);
	VisualDefaultBGSet_Sub(vpw);

	//BMPウィンドウ追加
	VisualSys_DefaultBmpWinAdd(vpw);

	//常駐OBJセット
	VisualDefaultOBJSet(vpw);
	VisualDefaultOBJSet_Sub(vpw);
	
	//転送パレットを真っ白にする(バッググラウンドは除く)
	PaletteWork_Clear(vpw->sys.pfd, FADE_MAIN_BG, FADEBUF_TRANS, 0x7fff, 1, 16*16);
	PaletteWork_Clear(vpw->sys.pfd, FADE_SUB_BG, FADEBUF_TRANS, 0x7fff, 1, 16*16);
	PaletteWork_Clear(vpw->sys.pfd, FADE_MAIN_OBJ, FADEBUF_TRANS, 0x7fff, 0, 
		CONTEST_MAIN_OBJPAL_COLOR_NUM);
	PaletteWork_Clear(vpw->sys.pfd, FADE_SUB_OBJ, FADEBUF_TRANS, 0x7fff, 0, 16*16);
	
	//ポケモン(ソフトウェアスプライト)生成
	//VT_SoftSpriteAddAll(&vpw->sys);

	WirelessIconEasy();	//通信アイコン
	
	// 輝度変更セット
//	ChangeBrightnessRequest(
//		8, 0, -16, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY );
	WIPE_SYS_Start(WIPE_PATTERN_FMAS, WIPE_TYPE_DOORIN, WIPE_TYPE_DOORIN, WIPE_FADE_BLACK, 
		WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_VISUAL);

	vpw->update_tcb = TCB_Add(VisualUpdate, vpw, TCBPRI_VISUAL_UPDATE);
	vpw->proc_mode = VPW_PROC_MODE_MAIN;

	GF_Disp_DispOn();
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);

	//サウンドデータロード(コンテスト)
	Snd_SceneSet( SND_SCENE_DUMMY );		//必ずロードされるようにクリアする！
	Snd_DataSetByScene( SND_SCENE_CONTEST, SEQ_CON_TEST, 1 );
	//Snd_Stop();
	//Snd_BgmPlay(SEQ_CON_TEST);

	ConTool_MsgPrintFlagSet(vpw->consys->sio_flag);
	
	sys_VBlankFuncChange(VisualVBlank, vpw);
	
	Snd_SePlay(VSE_DOOR_OPEN);
	
	return PROC_RES_FINISH;
}

//--------------------------------------------------------------
/**
 * @brief   プロセス関数：メイン
 *
 * @param   proc		プロセスデータ
 * @param   seq			シーケンス
 *
 * @retval  処理状況
 */
//--------------------------------------------------------------
PROC_RESULT VisualProc_Main( PROC * proc, int * seq )
{
	VISUAL_PROC_WORK * vpw  = PROC_GetWork( proc );
	int ret;
	enum{
		SEQ_IN,
		SEQ_MAIN,
		SEQ_OUT,
	};
	
	contest_rand(vpw->consys);
	
	switch( *seq ){
	case SEQ_IN:
//		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) ){
		if(WIPE_SYS_EndCheck() == TRUE){
			PaletteFadeReq(vpw->sys.pfd, PF_BIT_MAIN_BG, 0xffff, VISUAL_START_FADEIN_WAIT,
				EVY_MAX, 0, 0x7fff);
			PaletteFadeReq(vpw->sys.pfd, PF_BIT_SUB_BG, 0xffff, VISUAL_START_FADEIN_WAIT,
				EVY_MAX, 0, 0x7fff);
			PaletteFadeReq(vpw->sys.pfd, PF_BIT_MAIN_OBJ, CONTEST_MAIN_OBJPAL_FADEBIT, 
				VISUAL_START_FADEIN_WAIT, EVY_MAX, 0, 0x7fff);
			PaletteFadeReq(vpw->sys.pfd, PF_BIT_SUB_OBJ, 0xffff, VISUAL_START_FADEIN_WAIT,
				EVY_MAX, 0, 0x7fff);
			
			Snd_SePlay(VSE_AUDIENCE);
			*seq = SEQ_MAIN;
		}
		break;

	case SEQ_MAIN:
		if(ConTool_ServerMineCheck(vpw->consys) == TRUE){
			ret = VisualMainSeqTbl[vpw->tbl_seq_no](vpw, &vpw->local);
			if(ret == VSRET_NEXT || ret == VSRET_SELECT_SEQ){
				if(ret == VSRET_NEXT){
					vpw->tbl_seq_no++;
				}
				else{
					vpw->tbl_seq_no = vpw->local.select_seq;
				}
				MI_CpuClear8(&vpw->local, sizeof(VISUAL_LOCAL_WORK));
			}
			else if(ret == VSRET_END){
				*seq = SEQ_OUT;
				MI_CpuClear8(&vpw->local, sizeof(VISUAL_LOCAL_WORK));
				WIPE_SYS_Start(WIPE_PATTERN_FSAM, WIPE_TYPE_HOLEOUT, WIPE_TYPE_TUNNELOUT_TOP,
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_VISUAL);
				break;
			}
		}
		
		CO_TransmitCheckExe(&vpw->cow);
		CO_RecieveCheckExe(&vpw->cow, vpw);

		if(vpw->main_end == TRUE){
			*seq = SEQ_OUT;
			MI_CpuClear8(&vpw->local, sizeof(VISUAL_LOCAL_WORK));
			WIPE_SYS_Start(WIPE_PATTERN_FSAM, WIPE_TYPE_HOLEOUT, WIPE_TYPE_TUNNELOUT_TOP,
				WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_VISUAL);
		}
		break;

	case SEQ_OUT:
//		if(IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY)){
		if(WIPE_SYS_EndCheck() == TRUE){
			return PROC_RES_FINISH;
		}
		break;
	}

	return PROC_RES_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   プロセス関数：終了
 *
 * @param   proc		プロセスデータ
 * @param   seq			シーケンス
 *
 * @retval  処理状況
 */
//--------------------------------------------------------------
PROC_RESULT VisualProc_End( PROC * proc, int * seq )
{
	VISUAL_PROC_WORK * vpw = PROC_GetWork( proc );
	int i;

	Particle_SystemExitAll();

	//常駐OBJ削除
	VisualDefaultOBJDel(vpw);
	VisualDefaultOBJDel_Sub(vpw);
	//常駐BG削除
	VisualDefaultBGDel(vpw);
	VisualDefaultBGDel_Sub(vpw);

	//BMP開放
	for(i = 0; i < VISUAL_BMPWIN_MAX; i++){
		GF_BGL_BmpWinDel(&vpw->sys.win[i]);
	}

	//メイン画面BG削除
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_BGL_BGControlExit(vpw->sys.bgl, VISUAL_FRAME_WIN );
	GF_BGL_BGControlExit(vpw->sys.bgl, VISUAL_FRAME_EFF );
	GF_BGL_BGControlExit(vpw->sys.bgl, VISUAL_FRAME_BACKGROUND );
	//サブ画面BG削除
	GF_BGL_VisibleSet(VISUAL_FRAME_SUB_AUDIENCE, VISIBLE_OFF);
	GF_BGL_BGControlExit(vpw->sys.bgl, VISUAL_FRAME_SUB_AUDIENCE);

	//アクターシステム削除
	CATS_ResourceDestructor_S(vpw->sys.csp,vpw->sys.crp);
	CATS_FreeMemory(vpw->sys.csp);

	//Vram転送マネージャー削除
	DellVramTransferManager();

	//イメージクリップ削除
	for(i = 0; i < BREEDER_MAX; i++){
		if(vpw->imcwork[i].imc_ptr != NULL){
			IMC_PlayerEnd(vpw->imcwork[i].imc_ptr);
		}
	}

	//ソフトウェアスプライト削除
	VT_SoftSpriteDelAll(&vpw->sys);
	VT_TrainerDel(vpw);
	SoftSpriteEnd(vpw->sys.soft_sprite);

	//メッセージマネージャの削除
//	MSGMAN_Delete(vpw->fight_msg);

	//フォント削除
	FontProc_UnloadFont(FONT_BUTTON);

	//パレットフェードシステム削除
	PaletteFadeWorkAllocFree(vpw->sys.pfd, FADE_MAIN_BG);
	PaletteFadeWorkAllocFree(vpw->sys.pfd, FADE_SUB_BG);
	PaletteFadeWorkAllocFree(vpw->sys.pfd, FADE_MAIN_OBJ);
	PaletteFadeWorkAllocFree(vpw->sys.pfd, FADE_SUB_OBJ);
	PaletteFadeFree(vpw->sys.pfd);

	//メッセージマネージャの削除
	WORDSET_Delete(vpw->sys.wordset);
	STRBUF_Delete(vpw->sys.msg_buf);
	MSGMAN_Delete(vpw->sys.visual_msg);

	//BGL開放
	sys_FreeMemoryEz(vpw->sys.bgl);

	TCB_Delete(vpw->update_tcb);

//	simple_3DBGExit();
	ADV_Contest_3D_Exit(vpw->g3Dman);

	StopTP();		//タッチパネルの終了

	PROC_FreeWork(proc);				// ワーク開放
	
	sys_VBlankFuncChange( NULL, NULL );		// VBlankセット
	sys_HBlankIntrStop();	//HBlank割り込み停止

	sys_DeleteHeap(HEAPID_VISUAL);

	ConTool_MsgPrintFlagReset();

	WirelessIconEasyEnd();
	
	Overlay_UnloadID(FS_OVERLAY_ID(bc_common));
	Overlay_UnloadID(FS_OVERLAY_ID(ol_imageclip));
	return PROC_RES_FINISH;
}

//--------------------------------------------------------------
/**
 * @brief	VBLANK関数
 *
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void VisualVBlank(void *work)
{
	VISUAL_PROC_WORK *vpw = work;

	{//ウィンドウ座標
		G2_SetWnd0Position(vpw->wnd0_x1, vpw->wnd0_y1, vpw->wnd0_x2, vpw->wnd0_y2);
		G2_SetWnd1Position(vpw->wnd1_x1, vpw->wnd1_y1, vpw->wnd1_x2, vpw->wnd1_y2);
	}
	
	SoftSpriteTextureTrans(vpw->sys.soft_sprite);
	{
		int i;
		for(i = 0; i < BREEDER_MAX; i++){
			if(vpw->imcwork[i].imc_ptr != NULL){
				IMC_PlayerVblank(vpw->imcwork[i].imc_ptr);
			}
		}
	}

	DoVramTransferManager();	// Vram転送マネージャー実行
	CATS_RenderOamTrans();
	PaletteFadeTrans(vpw->sys.pfd);

	GF_BGL_VBlankFunc(vpw->sys.bgl);
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

//--------------------------------------------------------------
/**
 * @brief   メインループの最後に行うシステム関連の更新処理
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		vpw
 */
//--------------------------------------------------------------
static void VisualUpdate(TCB_PTR tcb, void *work)
{
	VISUAL_PROC_WORK *vpw = work;
	
	if(vpw->proc_mode == VPW_PROC_MODE_MAIN){
		SoftSpriteMain(vpw->sys.soft_sprite);	//トレーナー用に計算必要
		{
			int i;
			for(i = 0; i < BREEDER_MAX; i++){
				if(vpw->imcwork[i].imc_ptr != NULL){
					IMC_PlayerMain(vpw->imcwork[i].imc_ptr);
				}
			}
		}
		BattleParticle_Main();
		CATS_Draw(vpw->sys.crp);
		CATS_UpdateTransfer();
		G3_SwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
	}

	CommErrorCheck(HEAPID_VISUAL, vpw->sys.bgl);
}

//--------------------------------------------------------------
/**
 * @brief   Vramバンク設定を行う
 *
 * @param   bgl		BGLデータへのポインタ
 */
//--------------------------------------------------------------
static void VisualSys_VramBankSet(GF_BGL_INI *bgl)
{
	GF_Disp_GX_VisibleControlInit();

	//VRAM設定
	{
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_C,				// メイン2DエンジンのBG
			GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
			GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
			GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
			GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
			GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
			GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
			GX_VRAM_TEX_01_AB,				// テクスチャイメージスロット
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

	//メイン画面フレーム設定
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
			///<FRAME1_M	ウィンドウ
			{
				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
//				0, 0, 0x0800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
				VISUAL_BGPRI_WIN, 0, 0, FALSE
			},
			///<FRAME2_M	エフェクト
			{
				0, 0, 0x2000, 0, GF_BGL_SCRSIZ_512x512, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x14000, GX_BG_EXTPLTT_01,
				VISUAL_BGPRI_EFF, 0, 0, FALSE
			},
			///<FRAME3_M	背景
			{
				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x3000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
				VISUAL_BGPRI_SUB_AUDIENCE, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, VISUAL_FRAME_WIN, &TextBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, VISUAL_FRAME_WIN );
		GF_BGL_ScrollSet(bgl, VISUAL_FRAME_WIN, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, VISUAL_FRAME_WIN, GF_BGL_SCROLL_Y_SET, 0);
		GF_BGL_BGControlSet(bgl, VISUAL_FRAME_EFF, &TextBgCntDat[1], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, VISUAL_FRAME_EFF );
		GF_BGL_ScrollSet(bgl, VISUAL_FRAME_EFF, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, VISUAL_FRAME_EFF, GF_BGL_SCROLL_Y_SET, 0);
		GF_BGL_BGControlSet(bgl, VISUAL_FRAME_BACKGROUND, &TextBgCntDat[2], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, VISUAL_FRAME_BACKGROUND );
		GF_BGL_ScrollSet(bgl, VISUAL_FRAME_BACKGROUND, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, VISUAL_FRAME_BACKGROUND, GF_BGL_SCROLL_Y_SET, 0);

		G2_SetBG0Priority(VISUAL_3DBG_PRIORITY);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	}
	//サブ画面フレーム設定
	{
		GF_BGL_BGCNT_HEADER SubBgCntDat[] = {
			///<FRAME0_S	観客
			{
				0, 0, 0x0800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
				VISUAL_BGPRI_SUB_AUDIENCE, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, VISUAL_FRAME_SUB_AUDIENCE, &SubBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, VISUAL_FRAME_SUB_AUDIENCE );
		GF_BGL_ScrollSet(bgl, VISUAL_FRAME_SUB_AUDIENCE, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, VISUAL_FRAME_SUB_AUDIENCE, GF_BGL_SCROLL_Y_SET, 0);
	}
}

//--------------------------------------------------------------
/**
 * @brief   初期BMPウィンドウを設定する
 *
 * @param   vpw		ビジュアル管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void VisualSys_DefaultBmpWinAdd(VISUAL_PROC_WORK *vpw)
{
	GF_BGL_BmpWinAdd(vpw->sys.bgl, &vpw->sys.win[VISUAL_BMPWIN_TALK], VISUAL_FRAME_WIN, 
		0x02,0x13,27,4, BMPWIN_TALK_COLOR, BMPWIN_TALK_CGX_OFFSET);
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアル部門用パーティクル初期化
 */
//--------------------------------------------------------------
static void VisualParticleInit(void)
{
	NNSGfdTexKey tex_key;
	NNSGfdPlttKey pltt_key;
	u32 tex_addrs, pltt_addrs;
	
	//ポケモンで使用する分を確保
	tex_key = NNS_GfdAllocTexVram(0x2000 * CLIENT_MAX, 0, 0);
	pltt_key = NNS_GfdAllocPlttVram(0x20 * CLIENT_MAX, 0, 0);
	
	GF_ASSERT(tex_key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	GF_ASSERT(pltt_key != NNS_GFD_ALLOC_ERROR_PLTTKEY);
	tex_addrs = NNS_GfdGetTexKeyAddr(tex_key);
	pltt_addrs = NNS_GfdGetPlttKeyAddr(pltt_key);
	OS_TPrintf("ポケモン用に確保したテクスチャVramの先頭アドレス＝%d\n", tex_addrs);
	OS_TPrintf("ポケモン用に確保したパレットVramの先頭アドレス＝%d\n", pltt_addrs);

	//パーティクルシステムワーク初期化
	Particle_SystemWorkInit();
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアル部門管理ワークの初期パラメータをセットする
 * @param   vpw		ビジュアル部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void VisualSystemWorkInit(VISUAL_PROC_WORK *vpw)
{
	int i;
	
	GF_ASSERT(vpw->consys != NULL);
	
	for(i = 0; i < BREEDER_MAX; i++){
		vpw->v_game.breeder_sort[i] = BREEDER_MAX - 1 - i;
	}

	VisualOrder_WorkInit(vpw);
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアル部門で使用する基本的な常駐OBJの登録を行う
 * @param   vpw		ビジュアル部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void VisualDefaultOBJSet(VISUAL_PROC_WORK *vpw)
{
	//常駐OBJパレットロード
	CATS_LoadResourcePlttWorkArc(vpw->sys.pfd, FADE_MAIN_OBJ, vpw->sys.csp, vpw->sys.crp, 
		ARC_CONTEST_OBJ, CONTEST_VISUAL_OBJ_NCLR, 0, 
		VISUAL_COMMON_PAL_NUM, NNS_G2D_VRAM_TYPE_2DMAIN, V_PLTTID_OBJ_COMMON);
	
	VT_AudienceHeartResourceLoad(vpw->sys.csp, vpw->sys.crp);
	
	ADV_FlowerResourceLoad(vpw->sys.csp, vpw->sys.crp, vpw->sys.pfd,
		V_CHARID_FLOWER, -1, V_CELLID_FLOWER, V_CELLANMID_FLOWER);
	ADV_FlowerActorAddAll(&vpw->sys.flower, vpw->sys.csp, vpw->sys.crp, 
		V_CHARID_FLOWER, V_PLTTID_OBJ_COMMON, V_CELLID_FLOWER, V_CELLANMID_FLOWER, 
		PALOFS_FLOWER, V_FLOWER_SOFTPRI, V_FLOWER_BGPRI, TCBPRI_VISUAL_EFFECT);
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアル部門で使用する基本的な常駐OBJの削除を行う
 * @param   vpw		ビジュアル部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void VisualDefaultOBJDel(VISUAL_PROC_WORK *vpw)
{
	VT_AudienceHeartResourceFree(vpw->sys.crp);
	
	ADV_FlowerActorDelAll(&vpw->sys.flower);
	ADV_FlowerResourceFree(vpw->sys.crp, V_CHARID_FLOWER, -1, V_CELLID_FLOWER, V_CELLANMID_FLOWER);
	
	//常駐OBJパレット解放する
	CATS_FreeResourcePltt(vpw->sys.crp, V_PLTTID_OBJ_COMMON);
}

//--------------------------------------------------------------
/**
 * @brief   サブ画面OBJ：ビジュアル部門で使用する基本的な常駐OBJの登録を行う
 * @param   vpw		ビジュアル部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void VisualDefaultOBJSet_Sub(VISUAL_PROC_WORK *vpw)
{
	//常駐OBJパレットロード
	CATS_LoadResourcePlttWorkArc(vpw->sys.pfd, FADE_SUB_OBJ, vpw->sys.csp, vpw->sys.crp, 
		ARC_CONTEST_OBJ, CONTEST_VISUAL_SUB_OBJ_NCLR, 0, 
		VISUAL_SUB_COMMON_PAL_NUM, NNS_G2D_VRAM_TYPE_2DSUB, V_PLTTID_OBJ_COMMON_SUB);
}

//--------------------------------------------------------------
/**
 * @brief   サブ画面OBJ：ビジュアル部門で使用する基本的な常駐OBJの削除を行う
 * @param   vpw		ビジュアル部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void VisualDefaultOBJDel_Sub(VISUAL_PROC_WORK *vpw)
{
	//常駐OBJパレット解放する
	CATS_FreeResourcePltt(vpw->sys.crp, V_PLTTID_OBJ_COMMON_SUB);
}

//--------------------------------------------------------------
/**
 * @brief   メイン画面BG：ビジュアル部門で使用する基本BGデータのセットを行う
 * @param   vpw		ビジュアル部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void VisualDefaultBGSet(VISUAL_PROC_WORK *vpw)
{
	WINTYPE win_type;
	
	//キャラクタ
	ArcUtil_BgCharSet(ARC_CONTEST_BG, CON_VISUAL_BG_NCGR_BIN, vpw->sys.bgl, 
		VISUAL_FRAME_BACKGROUND, 0, 0, 1, HEAPID_VISUAL);
	//スクリーン
	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_VISUAL_BG_NSCR_BIN, vpw->sys.bgl, 
		VISUAL_FRAME_BACKGROUND, 0, 0, 1, HEAPID_VISUAL);
	GF_BGL_ScrClear(vpw->sys.bgl, VISUAL_FRAME_WIN);

	//パレット
	PaletteWorkSet_Arc(vpw->sys.pfd, ARC_CONTEST_BG, CONTEST_VISUAL_BG_NCLR, 
		HEAPID_VISUAL, FADE_MAIN_BG, 0, 0);
	//フォント用パレット
	PaletteWorkSet_Arc(vpw->sys.pfd, ARC_CONTEST_BG, CON_BG_FONT_NCLR, 
		HEAPID_VISUAL, FADE_MAIN_BG, 0x20, BMPWIN_TALK_COLOR * 16);


	//会話ウィンドウ
	win_type = CONFIG_GetWindowType(vpw->consys->config);
	TalkWinGraphicSet(vpw->sys.bgl, VISUAL_FRAME_WIN, VISUAL_TALKWIN_CGX_OFFSET, 
		VISUAL_TALKWIN_BACK_COLOR, win_type, HEAPID_VISUAL);
	PaletteWorkSet_Arc(vpw->sys.pfd, ARC_WINFRAME, TalkWinPalArcGet(win_type), 
		HEAPID_VISUAL, FADE_MAIN_BG, 0x20, VISUAL_TALKWIN_PALNO * 16);

	//どんちょう
	ArcUtil_BgCharSet(ARC_CONTEST_BG, DONTYOU_ANIM_NCGR_BIN, vpw->sys.bgl, 
		VISUAL_FRAME_EFF, 0, 0, 1, HEAPID_VISUAL);
	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_VISUAL_DONCHOU_NSCR_BIN, vpw->sys.bgl, 
		VISUAL_FRAME_EFF, 0, 0, 1, HEAPID_VISUAL);
	PaletteWorkSet_Arc(vpw->sys.pfd, ARC_CONTEST_BG, DONTYOU_ANIM_NCLR, 
		HEAPID_VISUAL, FADE_MAIN_BG, 0x20, DONTYOU_PALNO * 16);
}

//--------------------------------------------------------------
/**
 * @brief   メイン画面BG：ビジュアル部門で使用する基本BGデータの削除処理を行う
 * @param   vpw		ビジュアル部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void VisualDefaultBGDel(VISUAL_PROC_WORK *vpw)
{
	return;
}

//--------------------------------------------------------------
/**
 * @brief   サブ画面BG：ビジュアル部門で使用する基本BGデータのセットを行う
 * @param   vpw		ビジュアル部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void VisualDefaultBGSet_Sub(VISUAL_PROC_WORK *vpw)
{
	//キャラクタ
	ArcUtil_BgCharSet(ARC_CONTEST_BG, CON_VISUAL_SUB_BG_NCGR_BIN, vpw->sys.bgl, 
		VISUAL_FRAME_SUB_AUDIENCE, 0, 0, 1, HEAPID_VISUAL);
	//スクリーン
	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_VISUAL__SUB_BG_NSCR_BIN, vpw->sys.bgl, 
		VISUAL_FRAME_SUB_AUDIENCE, 0, 0, 1, HEAPID_VISUAL);

	//パレット
	PaletteWorkSet_Arc(vpw->sys.pfd, ARC_CONTEST_BG, CONTEST_VISUAL_SUB_BG_NCLR, 
		HEAPID_VISUAL, FADE_SUB_BG, 0, 0);
}

//--------------------------------------------------------------
/**
 * @brief   サブ画面BG：ビジュアル部門で使用する基本BGデータの削除処理を行う
 * @param   vpw		ビジュアル部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void VisualDefaultBGDel_Sub(VISUAL_PROC_WORK *vpw)
{
}




//==============================================================================
//
//	シーケンス
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：初期化処理
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_Init(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(PaletteFadeCheck(vpw->sys.pfd) != 0){
			break;
		}
		
		//クリップの得点計算
		ADV_ClipScoreCalc(vpw->consys, HEAPID_VISUAL);
		//BPの得点計算
		ADV_BPScoreCalc(vpw->consys);
		
		//VT_SoftSpriteAddAll(&vpw->sys);
//		if(CO_OrderSet(vpw, AORDER_NO_POKEMON_SPRITE_ADD_ALL, NULL) == TRUE){
			local->seq++;
//		}
		break;
	default:
//		if(CO_RequestBitNumCheck(vpw) == 0){
//		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
//		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：審判の最初の会話分
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_JudgeFastTalk(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	
	switch(local->seq){
	case 0:
		if(ConTool_PracticeModeCheck(vpw->consys) == TRUE){
			vpw->advance.a_talk_id = A_TALK_VISUAL_HOST_PRACTICE_01;
		}
		else{
			vpw->advance.a_talk_id = A_TALK_VISUAL_HOST_01;
		}
		vpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		vpw->advance.a_talk_bmpwin_not_close = 0;
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_TALK, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：ポケモン選択
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_PokeSelect(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	
	switch(local->seq){
	case 0:
		vpw->advance.now_breeder = vpw->v_game.breeder_sort[vpw->v_game.breeder_end_count];
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_SAMPLE, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：どんちょうをフェードアウト
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_DonchouFadeOut(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		vpw->advance.fade_start_evy = DFO_START_EVY;
		vpw->advance.fade_end_evy = DFO_END_EVY;
		vpw->advance.fade_wait = DFO_WAIT;
		vpw->advance.fade_next_rgb = DFO_NEXT_RGB;
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_FADE_INOUT, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：どんちょうをフェードイン
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_DonchouFadeIn(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		vpw->advance.fade_start_evy = DFI_START_EVY;
		vpw->advance.fade_end_evy = DFI_END_EVY;
		vpw->advance.fade_wait = DFI_WAIT;
		vpw->advance.fade_next_rgb = DFI_NEXT_RGB;
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_FADE_INOUT, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：完全に明るく
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_FullFadeIn(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		vpw->advance.fade_start_evy = DFE_START_EVY;
		vpw->advance.fade_end_evy = DFE_END_EVY;
		vpw->advance.fade_wait = DFE_WAIT;
		vpw->advance.fade_next_rgb = DFE_NEXT_RGB;
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_FADE_INOUT, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：どんちょうをエフェクト上昇
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_DonchouEffectUp(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_DONCHOU_EFFECT_UP, NULL) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：ポケモン登場
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_Appear(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_APPEAR, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：どんちょう上げる
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_DonchouUp(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_DONCHOU_UP, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：トレーナー登場
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_TrainerIn(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_TRAINER_IN, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：紹介メッセージ
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_IntroduceTalk(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		switch(vpw->v_game.breeder_end_count){
		case 0:
			vpw->advance.a_talk_id = A_TALK_VISUAL_HOST_02;
			break;
		case 1:
			vpw->advance.a_talk_id = A_TALK_VISUAL_HOST_03;
			break;
		case 2:
			vpw->advance.a_talk_id = A_TALK_VISUAL_HOST_04;
			break;
		default:
			vpw->advance.a_talk_id = A_TALK_VISUAL_HOST_05;
			break;
		}
		vpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		vpw->advance.a_talk_bmpwin_not_close = 0;
		vpw->advance.a_talk_tagpara.mine_brd = vpw->advance.now_breeder;
		local->seq++;
		//break;
	case 1:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_TALK, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：ポケモン登場エフェクト
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_AppearEffect(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_APPEAR_EFFECT, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：トレーナー退場
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_TrainerOut(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_TRAINER_OUT, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：ポケモン前進
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_Advance(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_ADVANCE, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：観客評価
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_AudienceEvaluate(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	enum{
		SEQ_INIT,
	#if 1
		SEQ_ALL_HEART,
		SEQ_ALL_HEART_WAIT,
	#else
		SEQ_BP_TALK,
		SEQ_BP_TALK_WAIT,
		SEQ_BP_HEART,
		SEQ_BP_HEART_WAIT,
		SEQ_CLIP_TALK,
		SEQ_CLIP_TALK_WAIT,
		SEQ_CLIP_HEART,
		SEQ_CLIP_HEART_WAIT,
	#endif
		SEQ_END,
	};
	
	switch(local->seq){
	case SEQ_INIT:
		vpw->advance.evaluate_heart_num_bp = 
			ConTool_HeartNumGet_BP(vpw->consys, vpw->advance.now_breeder);
		vpw->advance.evaluate_heart_num_clip = 
			ConTool_HeartNumGet_Clip(vpw->consys, vpw->advance.now_breeder);
		local->seq++;
		//break;

#if 1
	case SEQ_ALL_HEART:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_AUDIENCE_EVALUATE_ALL, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case SEQ_ALL_HEART_WAIT:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;

#else
	case SEQ_BP_TALK:
//		vpw->advance.a_talk_id = VT_A_TalkIDGet_BPAppeal(vpw->consys->c_game.type);
		vpw->advance.a_talk_id = A_TALK_VISUAL_NULL;
		vpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		vpw->advance.a_talk_bmpwin_not_close = 0;
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_TALK, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case SEQ_BP_TALK_WAIT:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			vpw->advance.a_talk_id = A_TALK_VISUAL_NULL;
			local->seq++;
		}
		break;
	case SEQ_BP_HEART:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_AUDIENCE_EVALUATE_BP, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case SEQ_BP_HEART_WAIT:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;

	case SEQ_CLIP_TALK:
//		vpw->advance.a_talk_id = A_TALK_VISUAL_HOST_13;
		vpw->advance.a_talk_id = A_TALK_VISUAL_NULL;
		vpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		vpw->advance.a_talk_bmpwin_not_close = 0;
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_TALK, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case SEQ_CLIP_TALK_WAIT:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			vpw->advance.a_talk_id = A_TALK_VISUAL_NULL;
			local->seq++;
		}
		break;
	case SEQ_CLIP_HEART:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_AUDIENCE_EVALUATE_CLIP, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case SEQ_CLIP_HEART_WAIT:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
#endif

	default:
		return VSRET_NEXT;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：ポケモン退場
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_PokeOut(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(vpw->v_game.breeder_end_count + 1 == BREEDER_MAX){
			local->select_seq = VSEQ_NEXT_POKE;
			return VSRET_SELECT_SEQ;
		}
		local->seq++;
		break;
	case 1:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_POKE_OUT, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：どんちょう下げる
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_DonchouDown(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_DONCHOU_DOWN, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：次のポケモンへ進む前の後処理
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_NextPoke(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		vpw->v_game.breeder_end_count++;
		local->seq++;
		break;
	default:
		if(vpw->v_game.breeder_end_count >= BREEDER_MAX){
			return VSRET_NEXT;
		}
		local->select_seq = VSEQ_POKE_SELECT;
		return VSRET_SELECT_SEQ;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：ビジュアル部門を終了する時のメッセージ表示
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_EndTalk(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		vpw->advance.se_id = VSE_AUDIENCE;
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_VISUAL_FINISH, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 1:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
		
	case 2:
		switch(vpw->consys->c_game.mode){
		case CONMODE_GRAND:
			vpw->advance.a_talk_id = A_TALK_VISUAL_HOST_06;
			break;
		default:
			vpw->advance.a_talk_id = A_TALK_VISUAL_NULL;
			break;
		}
		vpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		vpw->advance.a_talk_bmpwin_not_close = 0;
		local->seq++;
		//break;
	case 3:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_TALK, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ビジュアルシーケンス：終了処理
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int VisualSeq_End(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_VISUAL_EXIT, NULL) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_END;
		}
		break;
	}
	return VSRET_CONTINUE;
}

