//==============================================================================
/**
 * @file	dance.c
 * @brief	ダンス部門
 * @author	matsuda
 * @date	2005.12.12(月)
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

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "communication/communication.h"

#include "msgdata/msg.naix"

#include "contest_order.h"
#include "con_tool.h"
#include "dance.h"
#include "dance_tool.h"
#include "dance_tcb_pri.h"
#include "dance_id.h"
#include "dance_order.h"
#include "dance_input.h"

#include "system/window.h"
#include "system/wipe.h"
#include "savedata/config.h"
#include "communication/wm_icon.h"

//RT_CalcRevicePoint関数使用のため
#include "con_result.h"
#include "res_tool.h"

#include "../particledata/particledata.h"
#include "../particledata/particledata.naix"

#include "system/pm_overlay.h"
FS_EXTERN_OVERLAY(bc_common);
FS_EXTERN_OVERLAY(ol_imageclip);



#ifdef PM_DEBUG
extern u8 DmatsuWork_DanceRotationOff;
#endif

//==============================================================================
//	定数定義
//==============================================================================
///現在の動作状態
enum{
	DPW_PROC_MODE_INIT,		///<初期化中
	DPW_PROC_MODE_MAIN,		///<メイン
	DPW_PROC_MODE_ETC,		///<それ以外
};

///Vram転送マネージャータスク数
#define DANCE_VRAM_TRANSFER_TASK_NUM	(BATTLE_VRAM_TRANSFER_TASK_NUM)

///実際の曲とテンポのタイミングが感覚的に微妙にずれている気がするので補正を入れる
#define TICK_VCOUNT_HOSEI		(1)

//--------------------------------------------------------------
//	BMPウィンドウ
//--------------------------------------------------------------
///BMPウィンドウCGXエリア開始位置(オフセット)
#define BMPWIN_CGX_START			(TALK_WIN_CGX_SIZ + DANCE_TALKWIN_CGX_OFFSET)

#define BMPWIN_TALK_COLOR			(13)
#define BMPWIN_TALK_CGX_OFFSET		(BMPWIN_CGX_START)

//--------------------------------------------------------------
//	CL_ACT用の定数定義
//--------------------------------------------------------------
///メイン	OAM管理領域・開始
#define DANCE_OAM_START_MAIN			(BATTLE_OAM_START_MAIN)
///メイン	OAM管理領域・終了
#define DANCE_OAM_END_MAIN				(BATTLE_OAM_END_MAIN)
///メイン	アフィン管理領域・開始
#define DANCE_OAM_AFFINE_START_MAIN		(BATTLE_OAM_AFFINE_START_MAIN)
///メイン	アフィン管理領域・終了
#define DANCE_OAM_AFFINE_END_MAIN		(BATTLE_OAM_AFFINE_END_MAIN)
///サブ	OAM管理領域・開始
#define DANCE_OAM_START_SUB				(BATTLE_OAM_START_SUB)
///サブ	OAM管理領域・終了
#define DANCE_OAM_END_SUB				(BATTLE_OAM_END_SUB)
///サブ アフィン管理領域・開始
#define DANCE_OAM_AFFINE_START_SUB		(BATTLE_OAM_AFFINE_START_SUB)
///サブ	アフィン管理領域・終了
#define DANCE_OAM_AFFINE_END_SUB		(BATTLE_OAM_AFFINE_END_SUB)

///キャラマネージャ：キャラクタID管理数(上画面＋下画面)
#define DANCE_CHAR_MAX					(BATTLE_CHAR_MAX)
///キャラマネージャ：メイン画面サイズ(byte単位)
#define DANCE_CHAR_VRAMSIZE_MAIN		(BATTLE_CHAR_VRAMSIZE_MAIN)
///キャラマネージャ：サブ画面サイズ(byte単位)
#define DANCE_CHAR_VRAMSIZE_SUB			(BATTLE_CHAR_VRAMSIZE_SUB)

///メイン画面＋サブ画面で使用するアクター総数
#define DANCE_ACTOR_MAX					(BATTLE_ACTOR_MAX)

///OBJで使用するパレット本数(上画面＋下画面)
#define DANCE_OAM_PLTT_MAX				(BATTLE_OAM_PLTT_MAX)

///転送モード 3D = 0 main = 1 sub = 2 main/sub = 3
#define DANCE_OAM_VRAM_TRANS			(BATTLE_OAM_VRAM_TRANS)

///OAMリソース：キャラ登録最大数(メイン画面 + サブ画面)
#define DANCE_OAMRESOURCE_CHAR_MAX		(BATTLE_OAMRESOURCE_CHAR_MAX)
///OAMリソース：パレット登録最大数(メイン画面 + サブ画面)
#define DANCE_OAMRESOURCE_PLTT_MAX		(BATTLE_OAMRESOURCE_PLTT_MAX)
///OAMリソース：セル登録最大数
#define DANCE_OAMRESOURCE_CELL_MAX		(BATTLE_OAMRESOURCE_CELL_MAX)
///OAMリソース：セルアニメ登録最大数
#define DANCE_OAMRESOURCE_CELLANM_MAX	(BATTLE_OAMRESOURCE_CELLANM_MAX)
///OAMリソース：マルチセル登録最大数
#define DANCE_OAMRESOURCE_MCELL_MAX		(BATTLE_OAMRESOURCE_MCELL_MAX)
///OAMリソース：マルチセルアニメ登録最大数
#define DANCE_OAMRESOURCE_MCELLANM_MAX	(BATTLE_OAMRESOURCE_MCELLANM_MAX)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///サブ画面BGのスクリーンクリアコード
#define SUB_BG_CLEAR_CODE		(0)


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static void DanceVBlank(void *work);
static void DanceUpdate(TCB_PTR tcb, void *work);
static void DanceSys_VramBankSet(GF_BGL_INI *bgl);
static void DanceSys_DefaultBmpWinAdd(DANCE_PROC_WORK *dpw);
static void DanceSystemWorkInit(DANCE_PROC_WORK *dpw);
static void DanceDefaultOBJSet(DANCE_PROC_WORK *dpw);
static void DanceDefaultOBJDel(DANCE_PROC_WORK *dpw);
static void DanceDefaultOBJSet_Sub(DANCE_PROC_WORK *dpw);
static void DanceDefaultOBJDel_Sub(DANCE_PROC_WORK *dpw);
static void DanceDefaultBGSet(DANCE_PROC_WORK *dpw);
static void DanceDefaultBGDel(DANCE_PROC_WORK *dpw);
static void DanceDefaultBGSet_Sub(DANCE_PROC_WORK *dpw);
static void DanceDefaultBGDel_Sub(DANCE_PROC_WORK *dpw);
static void DanceDefaultParticleSet(DANCE_PROC_WORK *dpw);
static void DanceDefaultParticleDel(DANCE_PROC_WORK *dpw);
static int DanceSeq_Init(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local);
static int DanceSeq_Practice_FastTalk(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local);
static int DanceSeq_FastTalk(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local);
static int DanceSeq_DonchouUp(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local);
static int DanceSeq_DonchouDown(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local);
static int DanceSeq_OpeningEffect(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local);
static int DanceSeq_DanceEndEffect(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local);
static int DanceSeq_EndTalk(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local);
static int DanceSeq_End(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local);
static int DanceSeq_MusicSelect(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local);
static int DanceSeq_PokeSelect(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local);
static int DanceSeq_DancingBefore(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local);
static int DanceSeq_Dancing(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local);
static int DanceSeq_DancingAfter(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local);
static int DanceSeq_Rotation(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local);
static int DanceSeq_NextPoke(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local);
static void DanceParticleInit(void);
static u32 sAllocTex(u32 size, BOOL is4x4comp);
static u32 sAllocTexPalette(u32 size, BOOL is4pltt);


//==============================================================================
//	外部データ
//==============================================================================
#include "dance.dat"

//==============================================================================
//	データ
//==============================================================================

//==============================================================================
//	シーケンステーブル
//==============================================================================
///DanceMainSeqTblの戻り値として使用
enum{
	DSRET_CONTINUE,		///<現状維持
	DSRET_NEXT,			///<次のシーケンスへ
	DSRET_SELECT_SEQ,	///<select_seqワークに入っているシーケンスへ進む
	DSRET_END,			///<終了
};

///ダンス部門メイン関数のシーケンステーブル
static int (* const DanceMainSeqTbl[])(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local) = {
	DanceSeq_Init,
//	DanceSeq_Practice_FastTalk,
	DanceSeq_FastTalk,
//	DanceSeq_DonchouUp,
	DanceSeq_OpeningEffect,
	DanceSeq_MusicSelect,
	DanceSeq_PokeSelect,
	DanceSeq_DancingBefore,
	DanceSeq_Dancing,
	DanceSeq_DancingAfter,
#if 1	//メインダンサーから作る為、ローテーションさせない
	DanceSeq_Rotation,
	DanceSeq_NextPoke,
#else
	DanceSeq_PokeSelect,
	DanceSeq_DancingBefore,
	DanceSeq_Dancing,
	DanceSeq_DancingAfter,
	DanceSeq_PokeSelect,
	DanceSeq_DancingBefore,
	DanceSeq_Dancing,
	DanceSeq_DancingAfter,
	DanceSeq_PokeSelect,
	DanceSeq_DancingBefore,
	DanceSeq_Dancing,
	DanceSeq_DancingAfter,
#endif
//	DanceSeq_DonchouDown,
	DanceSeq_DanceEndEffect,
	DanceSeq_EndTalk,
	DanceSeq_End,
};
///DanceMainSeqTblのシーケンス番号	※DanceMainSeqTblと並びを同じにしておくこと！！
enum{
	DSEQ_INIT,
//	DSEQ_PRACTICE_FAST_TALK,
	DSEQ_FAST_TALK,
//	DSEQ_DONCHOU_UP,
	DSEQ_OPENING_EFFECT,
	DSEQ_MUSIC_SELECT,
	DSEQ_POKE_SELECT,
	DSEQ_DANCE_BEFORE,
	DSEQ_DANCE,
	DSEQ_DANCE_AFTER,
	DSEQ_ROTATION,
	DSEQ_NEXT_POKE,
//	DSEQ_DONCHOU_DOWN,
	DSEQ_END_EFFECT,
	DSEQ_END_TALK,
	DSEQ_END,
};

//==============================================================================
//	CLACT用データ
//==============================================================================
static	const TCATS_OAM_INIT DanceTcats = {
	DANCE_OAM_START_MAIN, DANCE_OAM_END_MAIN,
	DANCE_OAM_AFFINE_START_MAIN, DANCE_OAM_AFFINE_END_MAIN,
	DANCE_OAM_START_SUB, DANCE_OAM_END_SUB,
	DANCE_OAM_AFFINE_START_SUB, DANCE_OAM_AFFINE_END_SUB,
};

static	const TCATS_CHAR_MANAGER_MAKE DanceCcmm = {
	DANCE_CHAR_MAX,
	DANCE_CHAR_VRAMSIZE_MAIN,
	DANCE_CHAR_VRAMSIZE_SUB,
	GX_OBJVRAMMODE_CHAR_1D_64K,
	GX_OBJVRAMMODE_CHAR_1D_32K
};

static const TCATS_RESOURCE_NUM_LIST DanceResourceList = {
	DANCE_OAMRESOURCE_CHAR_MAX,
	DANCE_OAMRESOURCE_PLTT_MAX,
	DANCE_OAMRESOURCE_CELL_MAX,
	DANCE_OAMRESOURCE_CELLANM_MAX,
	DANCE_OAMRESOURCE_MCELL_MAX,
	DANCE_OAMRESOURCE_MCELLANM_MAX,
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
PROC_RESULT DanceProc_Init( PROC * proc, int * seq )
{
	DANCE_PROC_WORK *dpw;

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

	sys_CreateHeap(HEAPID_BASE_APP, HEAPID_DANCE, DANCE_ALLOC_SIZE);

	dpw = PROC_AllocWork(proc, sizeof(DANCE_PROC_WORK), HEAPID_DANCE );
	MI_CpuClear8(dpw, sizeof(DANCE_PROC_WORK));

//	simple_3DBGInit(HEAPID_DANCE);
	dpw->g3Dman = ADV_Contest_3D_Init(HEAPID_DANCE);

	dpw->consys = PROC_GetParentWork(proc);
	dpw->consys->class_proc = dpw;
	dpw->consys->class_flag = CON_CLASS_DANCE;
	dpw->sys.c_game = &dpw->consys->c_game;
	DanceSystemWorkInit(dpw);

	//パレットフェードシステム作成
	dpw->sys.pfd = PaletteFadeInit(HEAPID_DANCE);
	PaletteTrans_AutoSet(dpw->sys.pfd, TRUE);
	PaletteFadeWorkAllocSet(dpw->sys.pfd, FADE_MAIN_BG, 0x200, HEAPID_DANCE);
	PaletteFadeWorkAllocSet(dpw->sys.pfd, FADE_SUB_BG, 0x200, HEAPID_DANCE);
	PaletteFadeWorkAllocSet(dpw->sys.pfd, FADE_MAIN_OBJ, CONTEST_MAIN_OBJPAL_SIZE, HEAPID_DANCE);
	PaletteFadeWorkAllocSet(dpw->sys.pfd, FADE_SUB_OBJ, 0x200, HEAPID_DANCE);
	dpw->middle_fade.buf = sys_AllocMemory(HEAPID_DANCE, DANCE_MIDDLE_PALWORK_SIZE);
	DT_MiddlePaletteOccSet(dpw, TRUE);
	
	dpw->sys.bgl = GF_BGL_BglIniAlloc(HEAPID_DANCE);

	initVramTransferManagerHeap(DANCE_VRAM_TRANSFER_TASK_NUM, HEAPID_DANCE);

	sys_KeyRepeatSpeedSet( 4, 8 );

	dpw->dip = DINPUT_SystemInit(dpw->consys, &dpw->sys);

	//VRAM割り当て設定
	DanceSys_VramBankSet(dpw->sys.bgl);

	// タッチパネルシステム初期化
	InitTPSystem();
	InitTPNoBuff(4);

	// ボタン用フォントを読み込み
	FontProc_LoadFont(FONT_BUTTON, HEAPID_DANCE);

	// 引数を保存
//	SetDanceWorkParameter(dpw, (NAMEIN_PARAM*)PROC_GetParentWork(proc));

	//アクターシステム作成
	dpw->sys.csp=CATS_AllocMemory(HEAPID_DANCE);
	CATS_SystemInit(dpw->sys.csp,&DanceTcats,&DanceCcmm,DANCE_OAM_PLTT_MAX);
	//通信アイコン用にキャラ＆パレット制限
	CLACT_U_WmIcon_SetReserveAreaCharManager(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_64K);
	CLACT_U_WmIcon_SetReserveAreaPlttManager(NNS_G2D_VRAM_TYPE_2DMAIN);
	dpw->sys.crp=CATS_ResourceCreate(dpw->sys.csp);
	CATS_ClactSetInit(dpw->sys.csp, dpw->sys.crp, DANCE_ACTOR_MAX);
	CATS_ResourceManagerInit(dpw->sys.csp,dpw->sys.crp,&DanceResourceList);
	CLACT_U_SetSubSurfaceMatrix(CATS_EasyRenderGet(dpw->sys.csp), 0, DANCE_SUB_ACTOR_DISTANCE);

	dpw->sys.soft_sprite = SoftSpriteInit(HEAPID_DANCE);
	DanceParticleInit();	//パーティクル初期化

	//メッセージマネージャ作成
	dpw->sys.dance_msg = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_cmsg_dance_dat, 
		HEAPID_DANCE);
	dpw->sys.wordset = WORDSET_Create(HEAPID_DANCE);
	dpw->sys.msg_buf = STRBUF_Create(DANCE_MESSAGE_BUF_SIZE, HEAPID_DANCE);	//文字列バッファ作成
	
	//フォントOAMシステム作成
	dpw->sys.fontoam_sys = FONTOAM_SysInit(DANCE_FONTOAM_MAX_MAIN, HEAPID_DANCE);

	//常駐BGセット
	DanceDefaultBGSet(dpw);
	DanceDefaultBGSet_Sub(dpw);

	//BMPウィンドウ追加
	DanceSys_DefaultBmpWinAdd(dpw);

	//常駐OBJセット
	DanceDefaultOBJSet(dpw);
	DanceDefaultOBJSet_Sub(dpw);

	DINPUT_CreateBG(dpw->dip, DINPUT_TYPE_WALL, TRUE, NULL);

	//ポケモン(ソフトウェアスプライト)生成
	DT_SoftSpriteAddAll(dpw);
	DT_PokeAffineUpdateZAll(&dpw->sys);
	
	//パーティクルリソース読み込み
	DanceDefaultParticleSet(dpw);
	
	//自分カーソル追尾タスクセット
	DT_MyCursorTaskSet(dpw);
	//ポケモンダンスエフェクト実行タスクセット
	DT_DanceMoveTaskSet(dpw);

	WirelessIconEasy();	//通信アイコン

	// 輝度変更セット
//	ChangeBrightnessRequest(
//		8, 0, -16, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY );
	WIPE_SYS_Start(WIPE_PATTERN_FMAS, WIPE_TYPE_HOLEIN, WIPE_TYPE_TUNNELIN_TOP, WIPE_FADE_BLACK, 
		WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_DANCE);

	dpw->update_tcb = TCB_Add(DanceUpdate, dpw, TCBPRI_DANCE_UPDATE);
	dpw->proc_mode = DPW_PROC_MODE_MAIN;

	GF_Disp_DispOn();
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);

	//サウンドデータロード(コンテスト)
	Snd_DataSetByScene( SND_SCENE_CONTEST, SEQ_CON_TEST, 1 );
	//if(Snd_NowBgmNoGet() != SEQ_CON_TEST){
	//	Snd_Stop();
	//	Snd_BgmPlay(SEQ_CON_TEST);
	//}

	ConTool_MsgPrintFlagSet(dpw->consys->sio_flag);

	//初期パレットフェードセット
	G2_SetBlendBrightness(DANCE_OPENING_BRIGHTNESS_PALNE, DANCE_OPENING_BRIGHTNESS_EVY);

	Snd_SePlay(DSE_START_SHOUT);
	
	sys_VBlankFuncChange(DanceVBlank, dpw);
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
PROC_RESULT DanceProc_Main( PROC * proc, int * seq )
{
	DANCE_PROC_WORK * dpw  = PROC_GetWork( proc );
	int ret;
	enum{
		SEQ_IN,
		SEQ_MAIN,
		SEQ_OUT,
	};
	
	contest_rand(dpw->consys);
	
	switch( *seq ){
	case SEQ_IN:
//		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) ){
		if(WIPE_SYS_EndCheck() == TRUE){
			*seq = SEQ_MAIN;
		}
		break;

	case SEQ_MAIN:
		if(ConTool_ServerMineCheck(dpw->consys) == TRUE){
			ret = DanceMainSeqTbl[dpw->tbl_seq_no](dpw, &dpw->local);
			if(ret == DSRET_NEXT || ret == DSRET_SELECT_SEQ){
				if(ret == DSRET_NEXT){
					dpw->tbl_seq_no++;
				}
				else{
					dpw->tbl_seq_no = dpw->local.select_seq;
				}
				MI_CpuClear8(&dpw->local, sizeof(DANCE_LOCAL_WORK));
			}
			else if(ret == DSRET_END){
				*seq = SEQ_OUT;
				MI_CpuClear8(&dpw->local, sizeof(DANCE_LOCAL_WORK));
				WIPE_SYS_Start(WIPE_PATTERN_FSAM, WIPE_TYPE_BLINDOUT_H, WIPE_TYPE_BLINDOUT_H, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_DANCE);
				break;
			}
		}
		CO_TransmitCheckExe(&dpw->cow);
		CO_RecieveCheckExe(&dpw->cow, dpw);

		if(dpw->main_end == TRUE){
			*seq = SEQ_OUT;
			MI_CpuClear8(&dpw->local, sizeof(DANCE_LOCAL_WORK));
			WIPE_SYS_Start(WIPE_PATTERN_FSAM, WIPE_TYPE_BLINDOUT_H, WIPE_TYPE_BLINDOUT_H, 
				WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_DANCE);
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
PROC_RESULT DanceProc_End( PROC * proc, int * seq )
{
	DANCE_PROC_WORK * dpw = PROC_GetWork( proc );
	int i;

	//常駐パーティクル削除
	GF_ASSERT(Particle_GetEmitterNum(dpw->ptc) == 0);
	DanceDefaultParticleDel(dpw);
	Particle_SystemExitAll();
	
	DT_ReviewPanelTaskDelAll(&dpw->sys);
	DT_MyCursorTaskDel(dpw);
	DT_DanceMoveTaskDel(dpw);
	DT_PokemonDefaultAnimeTaskDelAll(dpw);
	
	//常駐OBJ削除
	DanceDefaultOBJDel(dpw);
	DanceDefaultOBJDel_Sub(dpw);
	//常駐BG削除
	DanceDefaultBGDel(dpw);
	DanceDefaultBGDel_Sub(dpw);

	//BMP開放
	for(i = 0; i < DANCE_BMPWIN_MAX; i++){
		GF_BGL_BmpWinDel(&dpw->sys.win[i]);
	}

	//メイン画面BG削除
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_BGL_BGControlExit(dpw->sys.bgl, DANCE_FRAME_WIN );
	GF_BGL_BGControlExit(dpw->sys.bgl, DANCE_FRAME_EFF );
	GF_BGL_BGControlExit(dpw->sys.bgl, DANCE_FRAME_BACKGROUND );
	//サブ画面BG削除
	DINPUT_FrameExit(dpw->sys.bgl);
	DINPUT_SystemFree(dpw->dip);

	//アクターシステム削除
	CATS_ResourceDestructor_S(dpw->sys.csp,dpw->sys.crp);
	CATS_FreeMemory(dpw->sys.csp);

	//Vram転送マネージャー削除
	DellVramTransferManager();

	//ソフトウェアスプライト削除
	DT_SoftSpriteDelAll(&dpw->sys);
	SoftSpriteEnd(dpw->sys.soft_sprite);

	//フォントOAMシステム削除
	FONTOAM_SysDelete(dpw->sys.fontoam_sys);
	
	//フォント削除
	FontProc_UnloadFont(FONT_BUTTON);

	//パレットフェードシステム削除
	sys_FreeMemoryEz(dpw->middle_fade.buf);
	PaletteFadeWorkAllocFree(dpw->sys.pfd, FADE_MAIN_BG);
	PaletteFadeWorkAllocFree(dpw->sys.pfd, FADE_SUB_BG);
	PaletteFadeWorkAllocFree(dpw->sys.pfd, FADE_MAIN_OBJ);
	PaletteFadeWorkAllocFree(dpw->sys.pfd, FADE_SUB_OBJ);
	PaletteFadeFree(dpw->sys.pfd);

	//メッセージマネージャの削除
	STRBUF_Delete(dpw->sys.msg_buf);
	WORDSET_Delete(dpw->sys.wordset);
	MSGMAN_Delete(dpw->sys.dance_msg);

	//BGL開放
	sys_FreeMemoryEz(dpw->sys.bgl);

	TCB_Delete(dpw->update_tcb);

//	simple_3DBGExit();
	ADV_Contest_3D_Exit(dpw->g3Dman);

	StopTP();		//タッチパネルの終了

	PROC_FreeWork(proc);				// ワーク開放
	
	sys_VBlankFuncChange( NULL, NULL );		// VBlankセット
	sys_HBlankIntrStop();	//HBlank割り込み停止

	sys_DeleteHeap(HEAPID_DANCE);

	ConTool_MsgPrintFlagReset();

#ifdef PM_DEBUG
	DmatsuWork_DanceRotationOff = 0;
#endif

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
static void DanceVBlank(void *work)
{
	DANCE_PROC_WORK *dpw = work;

#if 0	
	if(dpw->music_vcount_flag){
		dpw->music_vcount++;
	}
#else
	if(dpw->music_vcount_flag){
		u32 tick, tick_vcount;
		
		dpw->music_vcount++;
		
		//tickから現在のVカウントを読み取り補正する
		tick = Snd_PlayerGetTick( SND_HANDLE_BGM );
		
		tick_vcount = dpw->d_game.tick_frame * tick;
		tick_vcount += ONE_TEMPO_CALC_DECIMAL / 2;	//小数四捨五入
		tick_vcount /= ONE_TEMPO_CALC_DECIMAL;
		
		//tickの値は曲のループや繰り返しによって、0に戻ったり繰り返しをした箇所に戻るのか
		//を検証するため、ASSERTを入れておく。
		//戻るならば、music_vcountへの補正の仕方も変更する必要がある。
//		GF_ASSERT(dpw->tick_temp <= tick_vcount);	検証終了したのでコメントアウト
		dpw->tick_temp = tick_vcount;
		
		//カウンタが1以上ずれているか、一定フレーム以上続けてずれているなら補正
	//	OS_TPrintf("vcount = %d\n", dpw->music_vcount);
	//	OS_TPrintf("tick_vcount = %d\n", tick_vcount);
		tick_vcount += TICK_VCOUNT_HOSEI;
		if(tick_vcount != dpw->music_vcount){
			if(dpw->music_vcount_hosei_count > MUSIC_VCOUNT_HOSEI_COUNT
					|| (tick_vcount - dpw->music_vcount) > 1){
				OS_TPrintf("music_vcountの補正が行われました\n");
				OS_TPrintf("補正vcount_hosei_count = %d\n", dpw->music_vcount_hosei_count);
				OS_TPrintf("補正vcount = %d\n", dpw->music_vcount);
				OS_TPrintf("補正tick_vcount = %d\n", tick_vcount);
				dpw->music_vcount = tick_vcount;
				dpw->music_vcount_hosei_count = 0;
			}
			else{
				dpw->music_vcount_hosei_count++;
			//	OS_TPrintf("ずれてます・・・%d\n", dpw->music_vcount_hosei_count);
			}
		}
		else{
			dpw->music_vcount_hosei_count = 0;
		}
	}
#endif

	SoftSpriteTextureTrans(dpw->sys.soft_sprite);
	{
		int i;
		for(i = 0; i < BREEDER_MAX; i++){
			if(dpw->sys.imcwork[i].imc_ptr != NULL){
				IMC_PlayerVblank(dpw->sys.imcwork[i].imc_ptr);
			}
		}
	}

	DoVramTransferManager();	// Vram転送マネージャー実行
	CATS_RenderOamTrans();
	PaletteFadeTrans(dpw->sys.pfd);
	
	GF_BGL_VBlankFunc(dpw->sys.bgl);
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

//--------------------------------------------------------------
/**
 * @brief   中間パレットバッファ処理
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void DanceMiddlePalette(DANCE_PROC_WORK *dpw)
{
	u16 *trans_wk;
	DANCE_MIDDLE_FADE *mf;
	s32 now_evy;
	
	mf = &dpw->middle_fade;
	if(mf->occ == FALSE){
		return;
	}
	
	trans_wk = PaletteWorkTransWorkGet(dpw->sys.pfd, FADE_MAIN_BG);

	MI_CpuCopy16(mf->buf, trans_wk, DANCE_MIDDLE_PALWORK_SIZE);

	if(mf->req == TRUE){
		ColorConceChange(mf->buf, trans_wk, mf->fade_bit, mf->now_evy >> 8, mf->next_rgb);
		if(mf->now_evy == mf->end_evy){
			mf->req = FALSE;
		}
		else{
			now_evy = mf->now_evy;
			now_evy += mf->add_evy;
			if((mf->add_evy > 0 && now_evy >= mf->end_evy)
					|| (mf->add_evy < 0 && now_evy <= mf->end_evy)){
				now_evy = mf->end_evy;
			}
			mf->now_evy = now_evy;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   メインループの最後に行うシステム関連の更新処理
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		dpw
 */
//--------------------------------------------------------------
static void DanceUpdate(TCB_PTR tcb, void *work)
{
	DANCE_PROC_WORK *dpw = work;
	
	DanceMiddlePalette(dpw);

	if(dpw->proc_mode == DPW_PROC_MODE_MAIN){
		SoftSpriteMain(dpw->sys.soft_sprite);
		{
			int i;
			for(i = 0; i < BREEDER_MAX; i++){
				if(dpw->sys.imcwork[i].imc_ptr != NULL){
					IMC_PlayerMain(dpw->sys.imcwork[i].imc_ptr);
				}
			}
		}
		BattleParticle_Main();
		CATS_Draw(dpw->sys.crp);
		CATS_UpdateTransfer();
		G3_SwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
	}

	CommErrorCheck(HEAPID_DANCE, dpw->sys.bgl);
}

//--------------------------------------------------------------
/**
 * @brief   Vramバンク設定を行う
 *
 * @param   bgl		BGLデータへのポインタ
 */
//--------------------------------------------------------------
static void DanceSys_VramBankSet(GF_BGL_INI *bgl)
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
				GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x14000, GX_BG_EXTPLTT_01,
				DANCE_BGPRI_WIN, 0, 0, FALSE
			},
			///<FRAME2_M	エフェクト
			{
				0, 0, 0x2000, 0, GF_BGL_SCRSIZ_512x512, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
				DANCE_BGPRI_EFF, 0, 0, FALSE
			},
			///<FRAME3_M	背景
			{
				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x3000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
				DANCE_BGPRI_BACKGROUND, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, DANCE_FRAME_WIN, &TextBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, DANCE_FRAME_WIN );
		GF_BGL_ScrollSet(bgl, DANCE_FRAME_WIN, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, DANCE_FRAME_WIN, GF_BGL_SCROLL_Y_SET, 0);
		GF_BGL_BGControlSet(bgl, DANCE_FRAME_EFF, &TextBgCntDat[1], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, DANCE_FRAME_EFF );
		GF_BGL_ScrollSet(bgl, DANCE_FRAME_EFF, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, DANCE_FRAME_EFF, GF_BGL_SCROLL_Y_SET, 0);
		GF_BGL_BGControlSet(bgl, DANCE_FRAME_BACKGROUND, &TextBgCntDat[2], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, DANCE_FRAME_BACKGROUND );
		GF_BGL_ScrollSet(bgl, DANCE_FRAME_BACKGROUND, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, DANCE_FRAME_BACKGROUND, GF_BGL_SCROLL_Y_SET, 0);

		G2_SetBG0Priority(DANCE_3DBG_PRIORITY);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	}
	//サブ画面フレーム設定
	{
		DINPUT_DefaultFrameSet(bgl);
	}
}

//--------------------------------------------------------------
/**
 * @brief   初期BMPウィンドウを設定する
 *
 * @param   dpw		ダンス管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void DanceSys_DefaultBmpWinAdd(DANCE_PROC_WORK *dpw)
{
	GF_BGL_BmpWinAdd(dpw->sys.bgl, &dpw->sys.win[DANCE_BMPWIN_TALK], DANCE_FRAME_WIN, 
		0x02,0x13,27,4, BMPWIN_TALK_COLOR, BMPWIN_TALK_CGX_OFFSET);
	GF_BGL_BmpWinAdd(dpw->sys.bgl, &dpw->sys.win[DANCE_BMPWIN_PANEL], DANCE_FRAME_WIN, 
		0x02,0xb,27,2, BMPWIN_TALK_COLOR, BMPWIN_TALK_CGX_OFFSET);
}

//--------------------------------------------------------------
/**
 * @brief   ダンス部門用パーティクル初期化
 */
//--------------------------------------------------------------
static void DanceParticleInit(void)
{
#if 0
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
#endif

	//パーティクルシステムワーク初期化
	Particle_SystemWorkInit();
}

//--------------------------------------------------------------
/**
 * @brief   ダンス部門管理ワークの初期パラメータをセットする
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void DanceSystemWorkInit(DANCE_PROC_WORK *dpw)
{
	int i;
	
	GF_ASSERT(dpw->consys != NULL);
	
	for(i = 0; i < BREEDER_MAX; i++){
		dpw->d_game.breeder_sort[i] = BREEDER_MAX - 1 - i;
		dpw->d_game.breeder_rotation[i] = BREEDER_MAX - 1 - i;
	}
	
	DanceOrder_WorkInit(dpw);
	
	//ジャンプ禁止チェック
	for(i = 0; i < BREEDER_MAX; i++){
		dpw->sys.jump_up[i] = 
			DanceJump_PokeCheck(PokeParaGet(dpw->consys->c_game.pp[i], ID_PARA_monsno, NULL));
	}
}

//--------------------------------------------------------------
/**
 * @brief   ダンス部門で使用する基本的な常駐OBJの登録を行う
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void DanceDefaultOBJSet(DANCE_PROC_WORK *dpw)
{
	//常駐OBJパレットロード
	CATS_LoadResourcePlttWorkArc(dpw->sys.pfd, FADE_MAIN_OBJ, dpw->sys.csp, dpw->sys.crp, 
		ARC_CONTEST_OBJ, CONTEST_DANCE_OBJ_NCLR, 0, 
		DANCE_COMMON_PAL_NUM, NNS_G2D_VRAM_TYPE_2DMAIN, D_PLTTID_OBJ_COMMON);
	
	DT_HeartResourceLoad(dpw->sys.csp, dpw->sys.crp);
	
	DT_OnpuResourceLoad(dpw->sys.csp, dpw->sys.crp);
	
	DT_ReviewPanelResourceLoad(dpw->sys.csp, dpw->sys.crp);
	DT_ReviewPanelActorSetAll(&dpw->sys, dpw->sys.csp, dpw->sys.crp);
	DT_ReviewFontOamCreateAll(&dpw->sys);

	DT_MyCursorResourceLoad(dpw->sys.csp, dpw->sys.crp);
	DT_MyCursorActorSet(&dpw->sys, dpw->sys.csp, dpw->sys.crp);

	DT_PrinResourceLoad(dpw->sys.csp, dpw->sys.crp);
	DT_PrinCreate(dpw, dpw->sys.csp, dpw->sys.crp);

	DT_ShadowResourceLoad(dpw->sys.csp, dpw->sys.crp);
	DT_ShadowActorSetAll(&dpw->sys, dpw->sys.csp, dpw->sys.crp);

	DT_SpotLightResourceLoad(dpw->sys.csp, dpw->sys.crp);
	DT_SpotLightActorSetAll(&dpw->sys, dpw->sys.csp, dpw->sys.crp);
	
	DT_StarResourceLoad(dpw->sys.csp, dpw->sys.crp);
}

//--------------------------------------------------------------
/**
 * @brief   ダンス部門で使用する基本的な常駐OBJの削除を行う
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void DanceDefaultOBJDel(DANCE_PROC_WORK *dpw)
{
	DT_HeartResourceFree(dpw->sys.crp);

	DT_OnpuResourceFree(dpw->sys.crp);
	DT_OnpuActorDelAll(&dpw->sys);

	DT_ReviewPanelResourceFree(dpw->sys.crp);
	DT_ReviewPanelActorDelAll(&dpw->sys);
	DT_ReviewFontOamDeleteAll(&dpw->sys);

	DT_MyCursorResourceFree(dpw->sys.crp);
	DT_MyCursorActorDel(&dpw->sys);

	DT_PrinFree(dpw);
	DT_PrinResourceFree(dpw->sys.crp);

	DT_ShadowResourceFree(dpw->sys.crp);
	DT_ShadowActorDelAll(&dpw->sys);

	DT_SpotLightResourceFree(dpw->sys.crp);
	DT_SpotLightActorDelAll(&dpw->sys);

	DT_StarResourceFree(dpw->sys.crp);
	
	//常駐OBJパレット解放する
	CATS_FreeResourcePltt(dpw->sys.crp, D_PLTTID_OBJ_COMMON);
}

//--------------------------------------------------------------
/**
 * @brief   サブ画面OBJ：ダンス部門で使用する基本的な常駐OBJの登録を行う
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void DanceDefaultOBJSet_Sub(DANCE_PROC_WORK *dpw)
{
	//常駐OBJパレットロード
	CATS_LoadResourcePlttWorkArc(dpw->sys.pfd, FADE_SUB_OBJ, dpw->sys.csp, dpw->sys.crp, 
		ARC_CONTEST_OBJ, CONTEST_DANCE_OBJ_NCLR, 0, 
		DANCE_SUB_COMMON_PAL_NUM, NNS_G2D_VRAM_TYPE_2DSUB, D_PLTTID_OBJ_COMMON_SUB);
	//フォントOAMパレットロード
	CATS_LoadResourcePlttWorkArc(dpw->sys.pfd, FADE_SUB_OBJ, dpw->sys.csp, dpw->sys.crp, 
		ARC_CONTEST_OBJ, CONTEST_FONTOBJ_NCLR, 0, 
		1, NNS_G2D_VRAM_TYPE_2DSUB, D_PLTTID_SUB_FONTACT);

	DINPUT_DefaultActorSet(dpw->dip);
}

//--------------------------------------------------------------
/**
 * @brief   サブ画面OBJ：ダンス部門で使用する基本的な常駐OBJの削除を行う
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void DanceDefaultOBJDel_Sub(DANCE_PROC_WORK *dpw)
{
}

//--------------------------------------------------------------
/**
 * @brief   メイン画面BG：ダンス部門で使用する基本BGデータのセットを行う
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void DanceDefaultBGSet(DANCE_PROC_WORK *dpw)
{
	WINTYPE win_type;
	
	//キャラ
	ArcUtil_BgCharSet(ARC_CONTEST_BG, CON_DANCE_BG_NCGR_BIN, dpw->sys.bgl, 
		DANCE_FRAME_BACKGROUND, 0, 0, 1, HEAPID_DANCE);
	
	//スクリーン
	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_DANCE_BG_NSCR_BIN, dpw->sys.bgl, 
		DANCE_FRAME_BACKGROUND, 0, 0, 1, HEAPID_DANCE);
//	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_DANCE_FUMEN_NSCR_BIN, dpw->sys.bgl, 
//		DANCE_FRAME_WIN, 0, 0, 1, HEAPID_DANCE);
	
	//パレット
	PaletteWorkSet_Arc(dpw->sys.pfd, ARC_CONTEST_BG, CONTEST_DANCE_BG_NCLR, 
		HEAPID_DANCE, FADE_MAIN_BG, 0, 0);
	//フォント用パレット
	PaletteWorkSet_Arc(dpw->sys.pfd, ARC_CONTEST_BG, CON_BG_FONT_NCLR, 
		HEAPID_DANCE, FADE_MAIN_BG, 0x20, BMPWIN_TALK_COLOR * 16);


	//会話ウィンドウ
	win_type = CONFIG_GetWindowType(dpw->consys->config);
	TalkWinGraphicSet(dpw->sys.bgl, DANCE_FRAME_WIN, DANCE_TALKWIN_CGX_OFFSET, 
		DANCE_TALKWIN_BACK_COLOR, win_type, HEAPID_DANCE);
	PaletteWorkSet_Arc(dpw->sys.pfd, ARC_WINFRAME, TalkWinPalArcGet(win_type), 
		HEAPID_DANCE, FADE_MAIN_BG, 0x20, DANCE_TALKWIN_PALNO * 16);
	
	//どんちょう
//	ArcUtil_BgCharSet(ARC_CONTEST_BG, DONTYOU_ANIM_NCGR_BIN, dpw->sys.bgl, 
//		DANCE_FRAME_EFF, 0, 0, 1, HEAPID_DANCE);
//	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_DANCE_DONCHOU_NSCR_BIN, dpw->sys.bgl, 
//		DANCE_FRAME_EFF, 0, 0, 1, HEAPID_DANCE);
//	PaletteWorkSet_Arc(dpw->sys.pfd, ARC_CONTEST_BG, DONTYOU_ANIM_NCLR, 
//		HEAPID_DANCE, FADE_MAIN_BG, 0x20, DONTYOU_PALNO * 16);
	
	//ダンスした時に被せる半透明BG
	DT_BGAlphaDefaultDataSet(dpw);
	
	//中間バッファにパレットコピー
	{
		u16 *def_wk;
		def_wk = PaletteWorkDefaultWorkGet(dpw->sys.pfd, FADE_MAIN_BG);
		MI_CpuCopy16(def_wk, dpw->middle_fade.buf, DANCE_MIDDLE_PALWORK_SIZE);
	}
}

//--------------------------------------------------------------
/**
 * @brief   メイン画面BG：ダンス部門で使用する基本BGデータの削除処理を行う
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void DanceDefaultBGDel(DANCE_PROC_WORK *dpw)
{
	return;
}

//--------------------------------------------------------------
/**
 * @brief   サブ画面BG：ダンス部門で使用する基本BGデータのセットを行う
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void DanceDefaultBGSet_Sub(DANCE_PROC_WORK *dpw)
{
}

//--------------------------------------------------------------
/**
 * @brief   サブ画面BG：ダンス部門で使用する基本BGデータの削除処理を行う
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void DanceDefaultBGDel_Sub(DANCE_PROC_WORK *dpw)
{
}

//--------------------------------------------------------------
/**
 * @brief   常駐パーティクルデータ読み込み
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
///ダンスパーティクルのカメラニア設定
#define DANCE_CAMERA_NEAR			(FX32_ONE)
///ダンスパーティクルのカメラファー設定
#define DANCE_CAMERA_FAR			(FX32_ONE * 900)
static void DanceDefaultParticleSet(DANCE_PROC_WORK *dpw)
{
	void *heap;
	GF_CAMERA_PTR camera_ptr;
	void *resource;

	GF_ASSERT(dpw->ptc == NULL);
	
	heap = sys_AllocMemory(HEAPID_DANCE, PARTICLE_LIB_HEAP_SIZE);
	dpw->ptc = Particle_SystemCreate(sAllocTex, sAllocTexPalette, heap, 
		PARTICLE_LIB_HEAP_SIZE, TRUE, HEAPID_DANCE);
	camera_ptr = Particle_GetCameraPtr(dpw->ptc);
	GFC_SetCameraClip(DANCE_CAMERA_NEAR, DANCE_CAMERA_FAR, camera_ptr);

	//リソース読み込み
	resource = Particle_ArcResourceLoad(
		ARC_PARTICLE_DATA, NARC_particledata_con_dance_spa, HEAPID_DANCE);
	Particle_ResourceSet(dpw->ptc, resource, PTC_AUTOTEX_LNK | PTC_AUTOPLTT_LNK, TRUE);
}

//--------------------------------------------------------------
/**
 * @brief   常駐パーティクルデータ破棄
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void DanceDefaultParticleDel(DANCE_PROC_WORK *dpw)
{
	void *heap;

	heap = Particle_HeapPtrGet(dpw->ptc);
	Particle_SystemExit(dpw->ptc);
	sys_FreeMemoryEz(heap);
	
	dpw->ptc = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   テクスチャVRAMアドレスを返すためのコールバック関数
 *
 * @param   size		テクスチャサイズ
 * @param   is4x4comp	4x4圧縮テクスチャであるかどうかのフラグ(TRUE=圧縮テクスチャ)
 *
 * @retval  読み込みを開始するVRAMのアドレス
 */
//--------------------------------------------------------------
static u32 sAllocTex(u32 size, BOOL is4x4comp)
{
	NNSGfdTexKey key;
	u32 address;
	
	key = NNS_GfdAllocTexVram(size, is4x4comp, 0);
	Particle_LnkTexKeySet(key);		//リンクドリストを使用しているのでキー情報をセット
	
	address = NNS_GfdGetTexKeyAddr(key);
	OS_Printf("テクスチャVramアドレス＝%#x\n", address);
	return address;
}

//--------------------------------------------------------------
/**
 * @brief	テクスチャパレットVRAMアドレスを返すためのコールバック関数
 *
 * @param	size		テクスチャサイズ
 * @param	is4pltt		4色パレットであるかどうかのフラグ
 *
 * @retval	読み込みを開始するVRAMのアドレス
 *
 * direct形式のテクスチャの場合、SPL_LoadTexPlttByCallbackFunctionは
 * コールバック関数を呼び出しません。
 */
//--------------------------------------------------------------
static u32 sAllocTexPalette(u32 size, BOOL is4pltt)
{
	NNSGfdPlttKey key;
	u32 address;
	
	key = NNS_GfdAllocPlttVram(size, is4pltt, 0);
	Particle_PlttLnkTexKeySet(key);	//リンクドリストを使用しているのでキー情報をセット
	
	address = NNS_GfdGetPlttKeyAddr(key);
	OS_Printf("パレットVramアドレス＝%#x\n", address);
	return address;
}



//==============================================================================
//
//	シーケンス
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ダンスシーケンス：初期化処理
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int DanceSeq_Init(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local)
{
	int i;
	
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&dpw->cow, dpw, DORDER_NO_GAMEPARAM, &dpw->d_game) == TRUE){
			local->seq++;
		}
		break;
	default:
		//if(CO_RequestBitNumCheck(&dpw->cow) == 0){
		if(CO_AnswerCountCheck(&dpw->cow, dpw->consys->c_game.player_num, 
				dpw->consys->c_game.my_breeder_no, dpw->consys->c_game.server_no) == TRUE){
			return DSRET_NEXT;
		}
		break;
	}
	return DSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスシーケンス：練習、最初のメッセージ表示
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int DanceSeq_Practice_FastTalk(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local)
{
	if(ConTool_PracticeModeCheck(dpw->consys) == FALSE){
		return DSRET_NEXT;
	}

	switch(local->seq){
	case 0:
		dpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		dpw->advance.a_talk_bmpwin_not_close = 0;
		dpw->advance.a_talk_id = A_TALK_PRAC_DPREFACE;
		if(CO_OrderSet(&dpw->cow, dpw, DORDER_NO_TALK, &dpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 1:
//		if(CO_RequestBitNumCheck(&dpw->cow) == 0){
		if(CO_AnswerCountCheck(&dpw->cow, dpw->consys->c_game.player_num, 
				dpw->consys->c_game.my_breeder_no, dpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	default:
		return DSRET_NEXT;
	}
	return DSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスシーケンス：最初のメッセージ表示
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int DanceSeq_FastTalk(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		dpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		dpw->advance.a_talk_bmpwin_not_close = 0;
		dpw->advance.a_talk_tagpara.mine_brd = dpw->consys->c_game.my_breeder_no;
		dpw->advance.a_talk_tagpara.num = DT_DanceNumGet(dpw->consys->c_game.rank);
		if(ConTool_PracticeModeCheck(dpw->consys) == TRUE){
			dpw->advance.a_talk_id = A_TALK_BEGIN_HOST_PRACTICE_01;
		}
		else{
			dpw->advance.a_talk_id = A_TALK_BEGIN_HOST_01;
		}
		
		if(CO_OrderSet(&dpw->cow, dpw, DORDER_NO_TALK, &dpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 1:
//		if(CO_RequestBitNumCheck(&dpw->cow) == 0){
		if(CO_AnswerCountCheck(&dpw->cow, dpw->consys->c_game.player_num, 
				dpw->consys->c_game.my_breeder_no, dpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	default:
		return DSRET_NEXT;
	}
	return DSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスシーケンス：どんちょうを上げる
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int DanceSeq_DonchouUp(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&dpw->cow, dpw, DORDER_NO_DONCHOU_UP, NULL) == TRUE){
			local->seq++;
		}
		break;
	default:
		//if(CO_RequestBitNumCheck(&dpw->cow) == 0){
		if(CO_AnswerCountCheck(&dpw->cow, dpw->consys->c_game.player_num, 
				dpw->consys->c_game.my_breeder_no, dpw->consys->c_game.server_no) == TRUE){
			return DSRET_NEXT;
		}
		break;
	}
	return DSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスシーケンス：オープニングエフェクト
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int DanceSeq_OpeningEffect(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&dpw->cow, dpw, DORDER_NO_OPENING_EFF, NULL) == TRUE){
			local->seq++;
		}
		break;
	default:
		//if(CO_RequestBitNumCheck(&dpw->cow) == 0){
		if(CO_AnswerCountCheck(&dpw->cow, dpw->consys->c_game.player_num, 
				dpw->consys->c_game.my_breeder_no, dpw->consys->c_game.server_no) == TRUE){
			return DSRET_NEXT;
		}
		break;
	}
	return DSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスシーケンス：曲選択
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int DanceSeq_MusicSelect(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local)
{
	int data_no;
	u64 all_frame;
	
	switch(local->seq){
	case 0:
		switch(dpw->consys->c_game.rank){
		case CONRANK_NORMAL:
		case CONRANK_SUPER:
			data_no = 0;
			break;
		default:
			data_no = 1;
			break;
		}
		dpw->sys.musicdata = &DanceMusicData[data_no];
		dpw->d_game.one_tempo_frame = 
			ONE_MIN_FRAME * ONE_TEMPO_CALC_DECIMAL / DanceMusicData[data_no].tempo;
		all_frame = dpw->d_game.one_tempo_frame * TEMPO_BASE_ONPU;
		//四捨五入して整数化
		all_frame = (all_frame + ONE_TEMPO_CALC_DECIMAL / 2) / ONE_TEMPO_CALC_DECIMAL;
		dpw->d_game.all_tempo_frame = all_frame;
		dpw->d_game.tempo = DanceMusicData[data_no].tempo;
		dpw->d_game.ready_frame = 
			dpw->d_game.one_tempo_frame * DanceMusicData[data_no].ready_count;
		dpw->d_game.rotation_frame = 
			dpw->d_game.one_tempo_frame * DanceMusicData[data_no].rotation_count;
		dpw->d_game.tick_frame = dpw->d_game.one_tempo_frame / QUARTER_NOTE_TICK;
		
		dpw->d_game.touch_count = DanceMusicData[data_no].touch_count;
		dpw->d_game.music_id = DanceMusicData[data_no].music_id;
		
		dpw->advance.musicdata = *(dpw->sys.musicdata);
		dpw->advance.one_tempo_frame = dpw->d_game.one_tempo_frame;
		dpw->advance.all_tempo_frame = dpw->d_game.all_tempo_frame;
		dpw->advance.tempo = dpw->d_game.tempo;
		
		local->seq++;
		break;
	case 1:
		if(CO_OrderSet(&dpw->cow, dpw, DORDER_NO_GAMEPARAM, &dpw->d_game) == TRUE){
			local->seq++;
		}
		break;
	case 2:
		//if(CO_RequestBitNumCheck(&dpw->cow) == 0){
		if(CO_AnswerCountCheck(&dpw->cow, dpw->consys->c_game.player_num, 
				dpw->consys->c_game.my_breeder_no, dpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	case 3:
		if(CO_OrderSet(&dpw->cow, dpw, DORDER_NO_MUSIC_START, &dpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 4:
		//if(CO_RequestBitNumCheck(&dpw->cow) == 0){
		if(CO_AnswerCountCheck(&dpw->cow, dpw->consys->c_game.player_num, 
				dpw->consys->c_game.my_breeder_no, dpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	default:
		return DSRET_NEXT;
	}
	return DSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスシーケンス：ポケモン選択
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int DanceSeq_PokeSelect(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local)
{
	int i;
	
	switch(local->seq){
	case 0:
		dpw->advance.now_breeder = dpw->d_game.breeder_sort[dpw->d_game.breeder_end_count];
		for(i = 0; i < BREEDER_MAX; i++){
			dpw->advance.breeder_rotation[i] = dpw->d_game.breeder_rotation[i];
		}
		
		//AI
		for(i = dpw->consys->c_game.player_num; i < BREEDER_MAX; i++){
			dpw->advance.ai_random_seed[i] = contest_rand(dpw->consys);
		}
		
		local->seq++;
		break;
	default:
		return DSRET_NEXT;
	}
	return DSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスシーケンス：メインダンス前の準備
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int DanceSeq_DancingBefore(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&dpw->cow, dpw, DORDER_NO_BEFORE, &dpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
		//if(CO_RequestBitNumCheck(&dpw->cow) == 0){
		if(CO_AnswerCountCheck(&dpw->cow, dpw->consys->c_game.player_num, 
				dpw->consys->c_game.my_breeder_no, dpw->consys->c_game.server_no) == TRUE){
			return DSRET_NEXT;
		}
		break;
	}
	return DSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスシーケンス：メインダンス
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int DanceSeq_Dancing(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&dpw->cow, dpw, DORDER_NO_DANCING, &dpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
		//if(CO_RequestBitNumCheck(&dpw->cow) == 0){
		if(CO_AnswerCountCheck(&dpw->cow, dpw->consys->c_game.player_num, 
				dpw->consys->c_game.my_breeder_no, dpw->consys->c_game.server_no) == TRUE){
			return DSRET_NEXT;
		}
		break;
	}
	return DSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスシーケンス：メインダンス終了後の後処理
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int DanceSeq_DancingAfter(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&dpw->cow, dpw, DORDER_NO_AFTER, &dpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
		//if(CO_RequestBitNumCheck(&dpw->cow) == 0){
		if(CO_AnswerCountCheck(&dpw->cow, dpw->consys->c_game.player_num, 
				dpw->consys->c_game.my_breeder_no, dpw->consys->c_game.server_no) == TRUE){
			return DSRET_NEXT;
		}
		break;
	}
	return DSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスシーケンス：ローテーション
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int DanceSeq_Rotation(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local)
{
#ifdef PM_DEBUG
	if(DmatsuWork_DanceRotationOff == 1 && dpw->consys->sio_flag == FALSE){
		dpw->advance.now_count++;
		local->select_seq = DSEQ_POKE_SELECT;
		return DSRET_SELECT_SEQ;
	}
#endif

	switch(local->seq){
	case 0:
		if(dpw->d_game.breeder_end_count >= BREEDER_MAX - 1){
			return DSRET_NEXT;
		}

		dpw->advance.a_talk_tagpara.mine_brd = dpw->d_game.breeder_rotation[1];
		dpw->advance.a_talk_tagpara.num = DT_DanceNumGet(dpw->consys->c_game.rank);
	#if 0
		if(dpw->d_game.breeder_end_count >= BREEDER_MAX - 1){
			dpw->advance.a_talk_id = A_TALK_DANCE_NULL;
		}
		else{
			dpw->advance.a_talk_id = A_TALK_BEGIN_HOST_02;
		}
	#else
		dpw->advance.a_talk_id = A_TALK_DANCE_NULL;
	#endif
		
		if(CO_OrderSet(&dpw->cow, dpw, DORDER_NO_ROTATION, &dpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
		//if(CO_RequestBitNumCheck(&dpw->cow) == 0){
		if(CO_AnswerCountCheck(&dpw->cow, dpw->consys->c_game.player_num, 
				dpw->consys->c_game.my_breeder_no, dpw->consys->c_game.server_no) == TRUE){
			return DSRET_NEXT;
		}
		break;
	}
	return DSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスシーケンス：次のポケモンへ
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int DanceSeq_NextPoke(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local)
{
	int i;
	
	switch(local->seq){
	case 0:
		//ローテーション更新
		{
			int temp;
			
			temp = dpw->d_game.breeder_rotation[0];
			for(i = 0; i < BREEDER_MAX - 1; i++){
				dpw->d_game.breeder_rotation[i] = dpw->d_game.breeder_rotation[i + 1];
			}
			dpw->d_game.breeder_rotation[BREEDER_MAX - 1] = temp;
		}
		
		//各種パラメータ更新
		dpw->d_game.breeder_end_count++;

		local->seq++;
		//break;
	case 1:
		if(CO_OrderSet(&dpw->cow, dpw, DORDER_NO_GAMEPARAM, &dpw->d_game) == TRUE){
			local->seq++;
		}
		break;
	case 2:
		//if(CO_RequestBitNumCheck(&dpw->cow) == 0){
		if(CO_AnswerCountCheck(&dpw->cow, dpw->consys->c_game.player_num, 
				dpw->consys->c_game.my_breeder_no, dpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	default:
		if(dpw->d_game.breeder_end_count < BREEDER_MAX){
			dpw->advance.now_count++;
			local->select_seq = DSEQ_POKE_SELECT;
			return DSRET_SELECT_SEQ;
		}
		return DSRET_NEXT;
	}
	return DSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスシーケンス：どんちょうを下げる
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int DanceSeq_DonchouDown(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&dpw->cow, dpw, DORDER_NO_DONCHOU_DOWN, NULL) == TRUE){
			local->seq++;
		}
		break;
	default:
		//if(CO_RequestBitNumCheck(&dpw->cow) == 0){
		if(CO_AnswerCountCheck(&dpw->cow, dpw->consys->c_game.player_num, 
				dpw->consys->c_game.my_breeder_no, dpw->consys->c_game.server_no) == TRUE){
			return DSRET_NEXT;
		}
		break;
	}
	return DSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスシーケンス：全員のダンス終了後のエフェクト処理など
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int DanceSeq_DanceEndEffect(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&dpw->cow, dpw, DORDER_NO_END_EFFECT, &dpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 1:
//		if(CO_RequestBitNumCheck(&dpw->cow) == 0){
		if(CO_AnswerCountCheck(&dpw->cow, dpw->consys->c_game.player_num, 
				dpw->consys->c_game.my_breeder_no, dpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	default:
		return DSRET_NEXT;
	}
	return DSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスシーケンス：最後のメッセージ表示
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int DanceSeq_EndTalk(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local)
{
	int i, top_breeder;
	
	switch(local->seq){
	case 0:
		{//得点セット
			int i, j, t;
			s16 visual_revise[BREEDER_MAX], dance_revise[BREEDER_MAX];
			s16 total_revise[BREEDER_MAX];
			u8 breeder_sort[BREEDER_MAX];
			
			//-- scoreにダンス得点セット --//
			for(i = 0; i < BREEDER_MAX; i++){
				dpw->consys->c_game.score[i].dance = dpw->d_game.dance_point[i];
			}

			//-- ビジュアルとダンスの合計得点から演技力部門の開始並びを決める --//
			RT_CalcRevicePoint(dpw->consys, CONGAME_VISUAL, visual_revise);
			RT_CalcRevicePoint(dpw->consys, CONGAME_DANCE, dance_revise);
			for(i = 0; i < BREEDER_MAX; i++){
				total_revise[i] = visual_revise[i] + dance_revise[i];
				breeder_sort[i] = i;
			}
			//ここまでの合計得点が小さい順にソートする
			for(i = 0; i < BREEDER_MAX - 1; i++){
				for(j = BREEDER_MAX - 1; j > i; j--){
					if(total_revise[j-1] < total_revise[j]){
						//合計得点入れ替え
						t = total_revise[j];
						total_revise[j] = total_revise[j-1];
						total_revise[j-1] = t;
						//ブリーダー番号入れ替え
						t = breeder_sort[j];
						breeder_sort[j] = breeder_sort[j-1];
						breeder_sort[j-1] = t;
					}
				}
			}
			
			//-- consysのactin_sortに結果の並びをセット --//
			for(i = 0; i < BREEDER_MAX; i++){
				dpw->consys->actin_sort[i] = breeder_sort[i];
			}
		}

		dpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		dpw->advance.a_talk_bmpwin_not_close = 0;
		top_breeder = dpw->consys->actin_sort[0];
		dpw->advance.a_talk_tagpara.mine_brd = top_breeder;
		switch(dpw->consys->c_game.mode){
		case CONMODE_CHARM:
		case CONMODE_ACTIVE:
		case CONMODE_GRAND:
			dpw->advance.a_talk_id = A_TALK_AFTER_01;//A_TALK_END_HOST_01;
			break;
		default:
			dpw->advance.a_talk_id = A_TALK_DANCE_NULL;
			break;
		}
		local->seq++;
		//break;
	case 1:
		if(CO_OrderSet(&dpw->cow, dpw, DORDER_NO_TALK, &dpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 2:
//		if(CO_RequestBitNumCheck(&dpw->cow) == 0){
		if(CO_AnswerCountCheck(&dpw->cow, dpw->consys->c_game.player_num, 
				dpw->consys->c_game.my_breeder_no, dpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	default:
		return DSRET_NEXT;
	}
	return DSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスシーケンス：終了処理
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   local		ローカルワークへのポインタ
 *
 * @retval  継続動作フラグ
 */
//--------------------------------------------------------------
static int DanceSeq_End(DANCE_PROC_WORK *dpw, DANCE_LOCAL_WORK *local)
{
	DANCE_EXIT_PARAM dep;
	int i;
	
	switch(local->seq){
	case 0:
		local->seq++;
		//break;
	case 1:
		for(i = 0; i < BREEDER_MAX; i++){
			dep.actin_sort[i] = dpw->consys->actin_sort[i];
		}
		
		if(CO_OrderSet(&dpw->cow, dpw, DORDER_NO_DANCE_EXIT, &dep) == TRUE){
			local->seq++;
		}
		break;
	default:
		//if(CO_RequestBitNumCheck(&dpw->cow) == 0){
		if(CO_AnswerCountCheck(&dpw->cow, dpw->consys->c_game.player_num, 
				dpw->consys->c_game.my_breeder_no, dpw->consys->c_game.server_no) == TRUE){
			return DSRET_END;
		}
		break;
	}
	return DSRET_CONTINUE;
}

