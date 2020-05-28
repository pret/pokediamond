//==============================================================================
/**
 * @file	visual_order.c
 * @brief	ビジュアル部門：命令送受信
 * @author	matsuda
 * @date	2005.12.13(火)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "battle/battle_common.h"
#include "contest_order.h"
#include "visual.h"
#include "visual_order.h"

#include "visual_tcb_pri.h"
#include "system/clact_tool.h"
#include "system/palanm.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "system/softsprite.h"

#include "system/fontproc.h"
#include "system/msgdata.h"

#include "wazaeffect/battle_particle.h"
#include "system/particle.h"
#include "wazaeffect/we_mana.h"
#include "wazaeffect/we_sys.h"

#include "system/brightness.h"

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "visual_tool.h"
#include "poketool/poke_tool.h"
#include "gflib/touchpanel.h"
#include "system/snd_tool.h"
#include "system/window.h"
#include "contest_snd_def.h"


//==============================================================================
//	定数定義
//==============================================================================
///どんちょうの上昇速度(下位8ビット小数)
#define DONCHOU_UP_SPEED			(8)
///どんちょうがこれだけスクロールしたら停止させる(下位8ビット小数)
#define DONCHOU_STOP_SCROLL			(200 << 8)
///どんちょうの下降速度(下位8ビット小数)
#define DONCHOU_DOWN_SPEED			(-(DONCHOU_UP_SPEED))

///どんちょうアニメウェイト
#define DONCHOU_ANM_WAIT		(1)
///どんちょうを1段分アニメ終了する毎にもうけるアニメウェイト
#define DONCHOU_DANSA_ANM_WAIT		(0)
///どんちょうのアニメ転送用のキャラクタが横に何キャラ入っているか
#define DONCHOU_ANM_DATA_X_LEN	(8)
///どんちょうのアニメ転送用のキャラクタが縦に何キャラ入っているか
#define DONCHOU_ANM_DATA_Y_LEN	(4)

///トレーナー登場速度(下位8ビット小数)
#define TRAINER_IN_SPEED_X		(0x0400)
///トレーナー退場速度(下位8ビット小数)
#define TRAINER_OUT_SPEED_X		(0x0400)

///ポケモン登場エフェクトのポケモンが大きくなるスピード
#define	POKE_AFF_SPEED		(0x20)
///ポケモン登場エフェクトのポケモンが大きくなるスピード(fx32版)
#define POKE_AFF_SPEED_FX32	(FX32_ONE / (0x100 / POKE_AFF_SPEED))

///ボールエフェクト動作開始する前のウェイト
#define BALL_START_WAIT		(1)

///トレーナーが退場動作開始するまでのウェイト
#define TRAINER_MOVE_START_WAIT		(1)
///トレーナーがボールを投げる時の揺れ幅
#define TRAINER_BALL_SHAKE_Y		(3)
///トレーナーがボールを投げる時の揺らす回数(奇数だと元の位置に戻って終了するので奇数にする事！)
#define TRAINER_BALL_SHAKE_LOOP		(3)
///トレーナーがボールを投げる時、揺れた後、退場するまでのウェイト
#define TRAINER_BALL_OUT_WAIT		(7)

///観客ハートを出し始める前のウェイト
#define EVALUATE_HEART_START_WAIT		(15)	//(30)
///ハートを次々出していく時に開ける間隔
#define EVALUATE_HEART_WAIT		3//(5)
///ハートを全て出し終わった後、終了の返事を返すまでのウェイト
#define EVALUATE_HEART_END_WAIT	30//(60)
///ハート表示位置左端限界座標(ここより左には表示しない)
#define EVALUATE_HEART_X_L		(32)
///ハート表示位置右端限界座標(ここより右には表示しない)
#define EVALUATE_HEART_X_R		(32)
///ハート表示位置ランダム幅X
#define EVALUATE_HEART_X_RND	((256 - EVALUATE_HEART_X_L - EVALUATE_HEART_X_R) / 2)
///ハート表示位置左端限界座標(ここより左には表示しない)
#define EVALUATE_HEART_Y_U		(32)
///ハート表示位置右端限界座標(ここより右には表示しない)
#define EVALUATE_HEART_Y_D		(32)
///ハート表示位置ランダム幅X
#define EVALUATE_HEART_Y_RND	((192 - EVALUATE_HEART_Y_U - EVALUATE_HEART_Y_D) / 2)

///どんちょうエフェクト上昇：上昇速度を上げるまでのウェイト
#define DEU_SPEED_LVUP_WAIT			(30)
///どんちょうエフェクト上昇：上昇速度を上げるウェイトに達した時に発生する待ち時間
#define DEU_SPEED_LVUP_STOP_WAIT	(30)

///全体フェードアウト：対象ビット(BG)
#define DFO_FADE_BIT		(0x1fff)	//会話ウィンドウ、メッセージ、ローカライズ用パレット除く
///全体フェードアウト：対象ビット(OBJ)
#define DFO_FADE_BIT_OBJ	(CONTEST_MAIN_OBJPAL_FADEBIT)//通信アイコン、ローカライズ用パレット除く
///全体パレットクリア：対象カラー数(BG)
#define DFO_FADE_COLOR_NUM	(13 * 16)	//会話ウィンドウ、メッセージ、ローカライズ用パレット除く
///全体パレットクリア：対象カラー数(OBJ)
#define DFO_FADE_COLOR_NUM_OBJ	(CONTEST_MAIN_OBJPAL_COLOR_NUM)//通信アイコン、ローカライズ用パレット除く

///ポケモン登場後のウェイト
#define POKE_APPEAR_WAIT		10//(45)


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static int Request_Sample(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_Sample(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void Answer_Sample(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *answer_head, CO_ANSDAT *ansdat, int net_id);
static int Request_PokeAppear(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_PokeAppear(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void VOTCB_PokeAppear(TCB_PTR tcb, void *work);
static int Request_Advance(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_Advance(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void VOTCB_Advance(TCB_PTR tcb, void *work);
static int Request_AudienceEvaluate(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_AudienceEvaluateBP(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void Recieve_AudienceEvaluateClip(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void Recieve_AudienceEvaluateAll(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void VOTCB_AudienceEvaluate(TCB_PTR tcb, void *work);
static int Request_PokeOut(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_PokeOut(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void VOTCB_PokeOut(TCB_PTR tcb, void *work);
static int Request_VisualExit(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_VisualExit(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static int Request_DonchouUp(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_DonchouUp(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void VOTCB_DonchouUp(TCB_PTR tcb, void *work);
static int Request_DonchouDown(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_DonchouDown(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void VOTCB_DonchouDown(TCB_PTR tcb, void *work);
static int Request_TrainerIn(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_TrainerIn(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void VOTCB_TrainerIn(TCB_PTR tcb, void *work);
static int Request_TrainerOut(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_TrainerOut(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void VOTCB_TrainerOut(TCB_PTR tcb, void *work);
static int Request_AppearEffect(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_AppearEffect(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void VOTCB_AppearEffect(TCB_PTR tcb, void *work);
static void VOTCB_Sub_BallEffect(TCB_PTR tcb, void *work);
static void VOTCB_Sub_BallMove(TCB_PTR tcb, void *work);
static void VOTCB_Sub_PokeAppear(TCB_PTR tcb, void *work);
static void VOTCB_Sub_TrainerOut(TCB_PTR tcb, void *work);
static int Request_Talk(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_Talk(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void VOTCB_TalkPut(TCB_PTR tcb, void *work);
static int Request_DonchouEffectUp(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_DonchouEffectUp(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void VOTCB_DonchouEffectUp(TCB_PTR tcb, void *work);
static int Request_FadeInOut(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_FadeInOut(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void VOTCB_FadeInOut(TCB_PTR tcb, void *work);
static int Request_VisualFinish(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_VisualFinish(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void VOTCB_Finish(TCB_PTR tcb, void *work);


//==============================================================================
//	データ
//==============================================================================
///命令送受信用関数ポインタ構造体テーブル	※ここに追加したら必ず.hのenumにも追加する事!!
static const CON_ORDER_FUNC OrderFuncTbl[] = {
	{//VORDER_NO_SAMPLE		サンプル
		Request_Sample, 
		Recieve_Sample, 
		Answer_Sample, 
	},
	{//VORDER_NO_VISUAL_EXIT
		Request_VisualExit,
		Recieve_VisualExit,
		NULL,
	},
	{//VORDER_NO_POKE_APPEAR
		Request_PokeAppear, 
		Recieve_PokeAppear, 
		NULL, 
	},
	{//VORDER_NO_ADVANCE
		Request_Advance, 
		Recieve_Advance, 
		NULL, 
	},
	{//VORDER_NO_AUDIENCE_EVALUATE_BP
		Request_AudienceEvaluate, 
		Recieve_AudienceEvaluateBP, 
		NULL, 
	},
	{//VORDER_NO_AUDIENCE_EVALUATE_CLIP
		Request_AudienceEvaluate, 
		Recieve_AudienceEvaluateClip, 
		NULL, 
	},
	{//VORDER_NO_AUDIENCE_EVALUATE_ALL
		Request_AudienceEvaluate, 
		Recieve_AudienceEvaluateAll, 
		NULL, 
	},
	{//VORDER_NO_POKE_OUT
		Request_PokeOut, 
		Recieve_PokeOut, 
		NULL, 
	},
	{//VORDER_NO_DONCHOU_UP
		Request_DonchouUp, 
		Recieve_DonchouUp, 
		NULL, 
	},
	{//VORDER_NO_DONCHOU_DOWN
		Request_DonchouDown, 
		Recieve_DonchouDown, 
		NULL, 
	},
	{//VORDER_NO_TRAINER_IN
		Request_TrainerIn, 
		Recieve_TrainerIn, 
		NULL, 
	},
	{//VORDER_NO_TRAINER_OUT
		Request_TrainerOut, 
		Recieve_TrainerOut, 
		NULL, 
	},
	{//VORDER_NO_APPEAR_EFFECT
		Request_AppearEffect, 
		Recieve_AppearEffect, 
		NULL, 
	},
	{//VORDER_NO_TALK
		Request_Talk, 
		Recieve_Talk, 
		NULL, 
	},
	{//VORDER_NO_DONCHOU_FADE_INOUT
		Request_FadeInOut, 
		Recieve_FadeInOut, 
		NULL, 
	},
	{//VORDER_NO_DONCHOU_EFFECT_UP
		Request_DonchouEffectUp, 
		Recieve_DonchouEffectUp, 
		NULL, 
	},
	{//VORDER_NO_VISUAL_FINISH
		Request_VisualFinish, 
		Recieve_VisualFinish, 
		NULL, 
	},
};


//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///どんちょうアニメのスクリーン書き換えベース位置
ALIGN4 static const s8 DonchouAnmLineData[] = {
	13, 9, 5, 1, -3
};

///どんちょうのアニメパターン毎のキャラクタNo開始位置
ALIGN4 static const u16 DonchouAnmPaternStartCharNo[] = {
	0x20, 0x28, 0x30, 0x38,
	0xa0, 0xa8, 0xb0, 0xb8,
	0x120, 0x128, 0x130, 0x138,
};
///どんちょうの抜きなし垂れ幕最下段のキャラクタNo
#define DONCHOU_NUKINASHI_MAKU		(0x200)


//--------------------------------------------------------------
/**
 * @brief   ビジュアル部門：コンテスト送受信ワーク初期化
 * @param   vpw		ビジュアル部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void VisualOrder_WorkInit(VISUAL_PROC_WORK *vpw)
{
	CO_INIT_DATA initdata;
	
	initdata.func_tbl = OrderFuncTbl;
	initdata.func_tbl_max = NELEMS(OrderFuncTbl);
	initdata.my_breeder_no = vpw->consys->c_game.my_breeder_no;
	initdata.server_no = vpw->consys->c_game.server_no;
	initdata.sio_flag = vpw->consys->sio_flag;
	
	CO_WorkInit(&vpw->cow, &initdata);
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：サンプル
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_Sample(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	VISUAL_PROC_WORK *vpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, NULL, 0);
	OS_TPrintf("命令送信：サンプル\n");
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：サンプル
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_Sample(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	VISUAL_PROC_WORK *vpw = syswork;
	
	//返事を返す	バッファは特に渡すものがないのでNULL指定
	CO_ANSWER_TransmitBufferSet(cow, req_head, NULL, 0);

	OS_TPrintf("命令受信：サンプル\n");
}

//--------------------------------------------------------------
/**
 * @brief   返事受信(送信元)：サンプル
 *
 * @param   vpw				ビジュアル部門管理ワークへのポインタ
 * @param   answer_head		返事ヘッダのポインタ
 * @param   ansdat			受信データへのポインタ
 * @param   net_id			返事送信者のネットID
 */
//--------------------------------------------------------------
static void Answer_Sample(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *answer_head, CO_ANSDAT *ansdat, int net_id)
{
	VISUAL_PROC_WORK *vpw = syswork;
	
	OS_TPrintf("命令返信：サンプル\n");
	//返事を受け取るだけなので特にする事がない
	return;
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：ビジュアル部門終了
 *
 * @param   vpw			演技力部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_VisualExit(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	VISUAL_PROC_WORK *vpw = syswork;
	int bit_no;
	
	OS_TPrintf("命令送信：ビジュアル部門終了\n");
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, NULL, 0);
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：ビジュアル部門終了
 *
 * @param   vpw			演技力部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_VisualExit(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	VISUAL_PROC_WORK *vpw = syswork;

	OS_TPrintf("命令受信：ビジュアル部門終了\n");

	vpw->main_end = TRUE;
	
	//返事を返す	バッファは特に渡すものがないのでNULL指定
	CO_ANSWER_TransmitBufferSet(cow, req_head, NULL, 0);
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：ポケモン登場
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_PokeAppear(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	VISUAL_PROC_WORK *vpw = syswork;
	int bit_no;
	
	OS_TPrintf("命令送信：ポケモン登場\n");
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(VISUAL_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：ポケモン登場
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_PokeAppear(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	VISUAL_PROC_WORK *vpw = syswork;
	VISUAL_ADVANCE_PARAM *vap = data;
	VOLOCAL_ADVANCE *pa;
	s32 height;
	int i;
	
	OS_TPrintf("命令受信：ポケモン登場\n");

	pa = sys_AllocMemory(HEAPID_VISUAL, sizeof(VOLOCAL_ADVANCE));
	MI_CpuClear8(pa, sizeof(VOLOCAL_ADVANCE));

	pa->vpw = vpw;
	pa->req_head = *req_head;
	pa->cow = cow;
	pa->breeder_no = vap->now_breeder;
	

	//既に生成されているイメージクリップは削除(PokeOutがされなくなったので)
	for(i = 0; i < BREEDER_MAX; i++){
		if(pa->vpw->imcwork[i].imc_ptr != NULL){
			IMC_PlayerEnd(pa->vpw->imcwork[i].imc_ptr);
			pa->vpw->imcwork[i].imc_ptr = NULL;
		}
	}
	
	height = PokeParaHeightGet(vpw->sys.c_game->pp[vap->now_breeder], PARA_FRONT);

#if 0
	VT_SoftSpriteAdd(&vpw->sys, vap->now_breeder);
	SoftSpriteParaSet(vpw->sys.ss[vap->now_breeder], SS_PARA_POS_Y, VISUAL_APPEAR_X);
	SoftSpriteParaSet(vpw->sys.ss[vap->now_breeder], SS_PARA_POS_Y, 
		VISUAL_APPEAR_Y + height);
	
	SoftSpriteParaSet(vpw->sys.ss[vap->now_breeder], SS_PARA_VANISH, FALSE);
#else
	{//イメージクリップ生成(重いので先に生成して非表示にしておく)
		IMC_PLAYERSYS_INIT imc_init;
		
		MI_CpuClear8(&imc_init, sizeof(IMC_PLAYERSYS_INIT));
		imc_init.heap_id = HEAPID_VISUAL;
		imc_init.x = VISUAL_ARRIVAL_X;
		imc_init.y = VISUAL_ARRIVAL_Y + SOFT_SPRITE_SIZE_Y/2;
		vpw->imcwork[vap->now_breeder].x = VISUAL_ARRIVAL_X;
		vpw->imcwork[vap->now_breeder].y = VISUAL_ARRIVAL_Y + SOFT_SPRITE_SIZE_Y/2;
		vpw->imcwork[vap->now_breeder].imc_ptr = 
			IMC_ContestPlayerInit_NoBG(&imc_init, 
			vpw->consys->c_game.imc_data[vap->now_breeder]);
		//表示OFF
		IMC_Player_SetDrawFlag(vpw->imcwork[vap->now_breeder].imc_ptr, FALSE);
	}
	
	//ウィンドウで囲って輝度を落とす
	{
		G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2
			| GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE);
		G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2
			| GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, FALSE);
		G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0, -16);
		GX_SetVisibleWnd(GX_WNDMASK_W0);
		vpw->wnd0_x1 = 0;
		vpw->wnd0_y1 = 0;
		vpw->wnd0_x2 = 255;
		vpw->wnd0_y2 = (DonchouAnmLineData[0] + DONCHOU_ANM_DATA_Y_LEN) * 8;
	}
#endif

	//どんちょうのスクリーン転送
	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_VISUAL_DONCHOU_NSCR_BIN, vpw->sys.bgl, 
		VISUAL_FRAME_EFF, 0, 0, 1, HEAPID_VISUAL);

	TCB_Add(VOTCB_PokeAppear, pa, TCBPRI_VISUAL_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   ポケモン登場
 *
 * @param   tcb		
 * @param   work		
 */
//--------------------------------------------------------------
static void VOTCB_PokeAppear(TCB_PTR tcb, void *work)
{
	VOLOCAL_POKE_APPEAR *pa = work;
	int height;
	
	switch(pa->seq){
	case 0:	//IMC生成してから1フレーム開けてからDrawFlagをセットするようにするため、
			//ここではまだ何もしない。
		pa->seq++;
		break;
	case 1:
		//なんか最初の1体目だけ、一瞬ポケモンが真四角で表示されるので、
		//ウィンドウ内を3D表示をOFFしておく	※check
		G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2
			| GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE);

		height = PokeParaHeightGet(pa->vpw->sys.c_game->pp[pa->breeder_no], PARA_FRONT);
		IMC_Player_SetPokeMatrix_Ground(pa->vpw->imcwork[pa->breeder_no].imc_ptr,
			pa->vpw->imcwork[pa->breeder_no].x, pa->vpw->imcwork[pa->breeder_no].y,
			height);
		IMC_Player_SetDrawFlag(pa->vpw->imcwork[pa->breeder_no].imc_ptr, TRUE);
		
		pa->seq++;
		break;
	case 2:
		pa->seq++;
		break;
	case 3:
		//なんか最初の1体目だけ、一瞬ポケモンが真四角で表示されるので、
		//ウィンドウ内を3D表示をOFFしておく	※check
		G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2
			| GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE);

		//フェードOFF
		ColorConceChangePfd(pa->vpw->sys.pfd, FADE_MAIN_BG, DFO_FADE_BIT, 0, 0x0000);
		ColorConceChangePfd(pa->vpw->sys.pfd, FADE_MAIN_OBJ, DFO_FADE_BIT_OBJ, 0, 0x0000);
		
		Snd_SePlay(VSE_LIGHT);

		pa->seq++;
		break;
	case 4:
		pa->wait++;
		if(pa->wait > POKE_APPEAR_WAIT){
			pa->wait = 0;
			pa->seq++;
		}
		break;
	default:
		CO_ANSWER_TransmitBufferSet(pa->cow, &pa->req_head, NULL, 0);

		sys_FreeMemoryEz(pa);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：ポケモン前進
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_Advance(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	VISUAL_PROC_WORK *vpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(VISUAL_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：ポケモン前進
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_Advance(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	VISUAL_PROC_WORK *vpw = syswork;
	VISUAL_ADVANCE_PARAM *vap = data;
	VOLOCAL_ADVANCE *ad;
	
	ad = sys_AllocMemory(HEAPID_VISUAL, sizeof(VOLOCAL_ADVANCE));
	MI_CpuClear8(ad, sizeof(VOLOCAL_ADVANCE));

	ad->vpw = vpw;
	ad->req_head = *req_head;
	ad->cow = cow;
	ad->breeder_no = vap->now_breeder;

	TCB_Add(VOTCB_Advance, ad, TCBPRI_VISUAL_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   ポケモン前進
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		VOLOCAL_ADVANCE構造体
 */
//--------------------------------------------------------------
static void VOTCB_Advance(TCB_PTR tcb, void *work)
{
	VOLOCAL_ADVANCE *ad = work;
	int height;
	
	switch(ad->seq){
	case 0:
		ad->x = SoftSpriteParaGet(ad->vpw->sys.ss[ad->breeder_no], SS_PARA_POS_X) << 8;
		ad->y = SoftSpriteParaGet(ad->vpw->sys.ss[ad->breeder_no], SS_PARA_POS_Y) << 8;
		ad->seq++;
		break;
	case 1:
		height = PokeParaHeightGet(ad->vpw->sys.c_game->pp[ad->breeder_no], PARA_FRONT);

		ad->y += 0x0100;
		if(ad->y >= (VISUAL_ARRIVAL_Y << 8)){
		//if((ad->y + height) >= (VISUAL_ARRIVAL_Y << 8)){
			ad->y = VISUAL_ARRIVAL_Y << 8;
			ad->seq++;
		}
		SoftSpriteParaSet(ad->vpw->sys.ss[ad->breeder_no], SS_PARA_POS_X, ad->x >> 8);
		SoftSpriteParaSet(ad->vpw->sys.ss[ad->breeder_no], SS_PARA_POS_Y, ad->y >> 8);
		break;
	default:
		CO_ANSWER_TransmitBufferSet(ad->cow, &ad->req_head, NULL, 0);

		sys_FreeMemoryEz(ad);
		TCB_Delete(tcb);
		return;
	}
}



//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：観客評価
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_AudienceEvaluate(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	VISUAL_PROC_WORK *vpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(VISUAL_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：観客評価(BP)
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_AudienceEvaluateBP(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	VISUAL_PROC_WORK *vpw = syswork;
	VISUAL_ADVANCE_PARAM *vap = data;
	VOLOCAL_EVALUATE *eva;
	
	eva = sys_AllocMemory(HEAPID_VISUAL, sizeof(VOLOCAL_EVALUATE));
	MI_CpuClear8(eva, sizeof(VOLOCAL_EVALUATE));

	eva->vpw = vpw;
	eva->req_head = *req_head;
	eva->cow = cow;
	
	eva->max_count = vap->evaluate_heart_num_bp;
	eva->heart_anm = AUDIENCE_HEART_ANMTYPE_BP;
	
	TCB_Add(VOTCB_AudienceEvaluate, eva, TCBPRI_VISUAL_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：観客評価(クリップ)
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_AudienceEvaluateClip(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	VISUAL_PROC_WORK *vpw = syswork;
	VISUAL_ADVANCE_PARAM *vap = data;
	VOLOCAL_EVALUATE *eva;
	
	eva = sys_AllocMemory(HEAPID_VISUAL, sizeof(VOLOCAL_EVALUATE));
	MI_CpuClear8(eva, sizeof(VOLOCAL_EVALUATE));

	eva->vpw = vpw;
	eva->req_head = *req_head;
	eva->cow = cow;
	
	eva->max_count = vap->evaluate_heart_num_clip;
	eva->heart_anm = AUDIENCE_HEART_ANMTYPE_CLIP;
	
	TCB_Add(VOTCB_AudienceEvaluate, eva, TCBPRI_VISUAL_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：観客評価(BP & クリップ)
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_AudienceEvaluateAll(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	VISUAL_PROC_WORK *vpw = syswork;
	VISUAL_ADVANCE_PARAM *vap = data;
	VOLOCAL_EVALUATE *eva;
	
	eva = sys_AllocMemory(HEAPID_VISUAL, sizeof(VOLOCAL_EVALUATE));
	MI_CpuClear8(eva, sizeof(VOLOCAL_EVALUATE));

	eva->vpw = vpw;
	eva->req_head = *req_head;
	eva->cow = cow;
	
	eva->max_count = vap->evaluate_heart_num_bp + vap->evaluate_heart_num_clip;
	eva->bp_count = vap->evaluate_heart_num_bp;
	eva->clip_count = vap->evaluate_heart_num_clip;
	eva->heart_anm = AUDIENCE_HEART_ANMTYPE_BP;
	eva->all_type = TRUE;
	
	TCB_Add(VOTCB_AudienceEvaluate, eva, TCBPRI_VISUAL_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   観客評価(BP、CLIP、両方ともこのタスクを使用するので修正時は注意)
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		VOLOCAL_EVALUATE構造体
 */
//--------------------------------------------------------------
static void VOTCB_AudienceEvaluate(TCB_PTR tcb, void *work)
{
	VOLOCAL_EVALUATE *eva = work;
	int height;
	
	switch(eva->seq){
	case 0:
		Snd_SePlay(VSE_AUDIENCE);
		eva->wait = EVALUATE_HEART_START_WAIT;
		eva->seq++;
		//break;
	case 1:
		if(eva->put_count >= eva->max_count){
			eva->wait = 0;
			Snd_SePlay(VSE_AUDIENCE);
			eva->seq++;
			break;
		}
		else if(eva->all_type == TRUE){
			if(eva->put_count >= eva->bp_count){
				eva->heart_anm = AUDIENCE_HEART_ANMTYPE_CLIP;
			}
		}
		
		if(eva->wait > 0){
			eva->wait--;
			break;
		}
		
		eva->wait = EVALUATE_HEART_WAIT;
		
		//ハート表示
		{
			s16 x, y, rnd_x, rnd_y;
			
			rnd_x = contest_rand(eva->vpw->consys) % EVALUATE_HEART_X_RND;
			rnd_y = contest_rand(eva->vpw->consys) % EVALUATE_HEART_Y_RND;
			if(contest_rand(eva->vpw->consys) & 1){
				x = 128 + rnd_x;
			}
			else{
				x = 128 - rnd_x;
			}
			if(contest_rand(eva->vpw->consys) & 1){
				y = 96 + rnd_y;
			}
			else{
				y = 96 - rnd_y;
			}
			//ハートが近い場所に固まらないように旧座標と比較して適度に散らす
			if(eva->put_count > 0){
				if(((eva->old_x < 128 && x < 128) || (eva->old_x > 128 && x > 128))
						&& ((eva->old_y < 96 && y < 96) || (eva->old_y > 96 && y > 96))){
					if(contest_rand(eva->vpw->consys) & 1){
						if(x < 128){
							x = 128 + rnd_x;
						}
						else{
							x = 128 - rnd_x;
						}
					}
					else{
						if(y < 96){
							y = 96 + rnd_y;
						}
						else{
							y = 96 - rnd_y;
						}
					}
				}
			}
			
			if(eva->put_count & 1){
				VT_AudienceHeartActorAdd(eva->vpw, x, y, 180 << FX32_SHIFT, eva->heart_anm);
			}
			else{
				VT_AudienceHeartActorAdd(eva->vpw, x, y, 0, eva->heart_anm);
			}
			
			eva->old_x = x;
			eva->old_y = y;
		}
		eva->put_count++;
		break;
	case 2:
		eva->wait++;
		if(eva->wait > EVALUATE_HEART_END_WAIT){
			eva->wait = 0;
			eva->seq++;
		}
		break;
	default:
		CO_ANSWER_TransmitBufferSet(eva->cow, &eva->req_head, NULL, 0);

		sys_FreeMemoryEz(eva);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：ポケモン退場
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_PokeOut(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	VISUAL_PROC_WORK *vpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(VISUAL_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：ポケモン退場
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_PokeOut(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	VISUAL_PROC_WORK *vpw = syswork;
	VISUAL_ADVANCE_PARAM *vap = data;
	VOLOCAL_POKEOUT *po;
	
	po = sys_AllocMemory(HEAPID_VISUAL, sizeof(VOLOCAL_POKEOUT));
	MI_CpuClear8(po, sizeof(VOLOCAL_POKEOUT));

	po->vpw = vpw;
	po->req_head = *req_head;
	po->cow = cow;
	po->breeder_no = vap->now_breeder;

	TCB_Add(VOTCB_PokeOut, po, TCBPRI_VISUAL_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   ポケモン退場
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		VOLOCAL_POKEOUT構造体
 */
//--------------------------------------------------------------
static void VOTCB_PokeOut(TCB_PTR tcb, void *work)
{
	VOLOCAL_POKEOUT *po = work;
	int height;
	
	height = PokeParaHeightGet(po->vpw->sys.c_game->pp[po->breeder_no], PARA_FRONT);
	switch(po->seq){
	case 0:
		po->x = po->vpw->imcwork[po->breeder_no].x << 8;
		po->y = po->vpw->imcwork[po->breeder_no].y << 8;
//		po->x = SoftSpriteParaGet(po->vpw->sys.ss[po->breeder_no], SS_PARA_POS_X) << 8;
//		po->y = SoftSpriteParaGet(po->vpw->sys.ss[po->breeder_no], SS_PARA_POS_Y) << 8;
		po->seq++;
		break;
	case 1:
		po->x += 0x0300;
		if(po->x >= (300<<8)){
//			SoftSpriteParaSet(po->vpw->sys.ss[po->breeder_no], SS_PARA_VANISH, TRUE);
			po->seq++;
		}
//		SoftSpriteParaSet(po->vpw->sys.ss[po->breeder_no], SS_PARA_POS_X, po->x >> 8);
//		SoftSpriteParaSet(po->vpw->sys.ss[po->breeder_no], SS_PARA_POS_Y, po->y >> 8);
		IMC_Player_SetPokeMatrix_Ground(po->vpw->imcwork[po->breeder_no].imc_ptr, 
			po->x >> 8, po->y >> 8, height);
		break;
	default:
		//VT_SoftSpriteDel(&po->vpw->sys, po->breeder_no);
		IMC_PlayerEnd(po->vpw->imcwork[po->breeder_no].imc_ptr);
		po->vpw->imcwork[po->breeder_no].imc_ptr = NULL;
		
		CO_ANSWER_TransmitBufferSet(po->cow, &po->req_head, NULL, 0);

		sys_FreeMemoryEz(po);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：どんちょう上げる
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_DonchouUp(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	VISUAL_PROC_WORK *vpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, NULL, 0);
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：どんちょう上げる
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_DonchouUp(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	VISUAL_PROC_WORK *vpw = syswork;
	VOLOCAL_DONCHOU_UP *du;
	
	du = sys_AllocMemory(HEAPID_VISUAL, sizeof(VOLOCAL_DONCHOU_UP));
	MI_CpuClear8(du, sizeof(VOLOCAL_DONCHOU_UP));

	du->vpw = vpw;
	du->req_head = *req_head;
	du->cow = cow;
	
	TCB_Add(VOTCB_DonchouUp, du, TCBPRI_VISUAL_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   どんちょうを上げる
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		VOLOCAL_DONCHOU_UP構造体
 */
//--------------------------------------------------------------
static void VOTCB_DonchouUp(TCB_PTR tcb, void *work)
{
	VOLOCAL_DONCHOU_UP *du = work;
	
	switch(du->seq){
	case 0:
		//アニメウェイト
		if(du->anm_dansa_wait > 0){
			du->anm_dansa_wait--;
			break;
		}
		if(du->anm_wait > 0){
			du->anm_wait--;
			break;
		}
		du->anm_wait = DONCHOU_ANM_WAIT;
		
		//アニメ書き換え
		{
			u16 *scrn_buf, *dest_scrn;
			int x, y, pos_x, s, base_charno;
			
			scrn_buf = GF_BGL_ScreenAdrsGet(du->vpw->sys.bgl, VISUAL_FRAME_EFF);
			for(y = 0; y < DONCHOU_ANM_DATA_Y_LEN; y++){
				if(DonchouAnmLineData[du->anm_line] + y < 0){
					continue;
				}
				dest_scrn = &scrn_buf[32 * (DonchouAnmLineData[du->anm_line] + y)];
				base_charno = DonchouAnmPaternStartCharNo[du->anm_no] + 32*y;
				pos_x = 0;
				for(s = 0; s < 32 / DONCHOU_ANM_DATA_X_LEN; s++){
					for(x = 0; x < DONCHOU_ANM_DATA_X_LEN; x++){
						dest_scrn[pos_x + x] &= 0xfc00;		//キャラクタNoのみクリア
						dest_scrn[pos_x + x] |= base_charno + x;
					}
					pos_x += DONCHOU_ANM_DATA_X_LEN;
				}
			}
			
			//2段目以降のどんちょうでは最後のアニメが一ライン残ったやつなので、
			//前のどんちょうの残った部分をクリアしてやる
			//意味がわからない場合はとりあえずここの｛｝内をまるごとコメントアウトしてみれば分かる
			{
				if(du->anm_line > 0 && du->anm_no == 0){
					dest_scrn = &scrn_buf[32 * DonchouAnmLineData[du->anm_line - 1]];
					for(s = 0; s < 32; s++){
						dest_scrn[s] &= 0xfc00;		//キャラクタNoのみクリア
					}
				}
			}
			
			GF_BGL_LoadScreenV_Req(du->vpw->sys.bgl, VISUAL_FRAME_EFF);
		}
		
		du->anm_no++;
		if(du->anm_no >= NELEMS(DonchouAnmPaternStartCharNo)){
			du->anm_no = 0;
			du->anm_line++;
			du->anm_dansa_wait = DONCHOU_DANSA_ANM_WAIT;
			if(du->anm_line >= NELEMS(DonchouAnmLineData)){
				du->seq++;
			}
		}
		break;
	default:
		CO_ANSWER_TransmitBufferSet(du->cow, &du->req_head, NULL, 0);

		sys_FreeMemoryEz(du);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：どんちょう下げる
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_DonchouDown(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	VISUAL_PROC_WORK *vpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, NULL, 0);
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：どんちょう下げる
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_DonchouDown(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	VISUAL_PROC_WORK *vpw = syswork;
	VOLOCAL_DONCHOU_DOWN *dd;
	
	dd = sys_AllocMemory(HEAPID_VISUAL, sizeof(VOLOCAL_DONCHOU_DOWN));
	MI_CpuClear8(dd, sizeof(VOLOCAL_DONCHOU_DOWN));

	dd->vpw = vpw;
	dd->req_head = *req_head;
	dd->cow = cow;
	
	TCB_Add(VOTCB_DonchouDown, dd, TCBPRI_VISUAL_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   どんちょうを下げる
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		VOLOCAL_DONCHOU_DOWN構造体
 */
//--------------------------------------------------------------
static void VOTCB_DonchouDown(TCB_PTR tcb, void *work)
{
	VOLOCAL_DONCHOU_DOWN *dd = work;
	
	switch(dd->seq){
	case 0:
		//アニメウェイト
		if(dd->anm_dansa_wait > 0){
			dd->anm_dansa_wait--;
			break;
		}
		if(dd->anm_wait > 0){
			dd->anm_wait--;
			break;
		}
		dd->anm_wait = DONCHOU_ANM_WAIT;
		
		//アニメ書き換え
		{
			u16 *scrn_buf, *dest_scrn;
			int x, y, pos_x, s, base_charno;
			int base_line;
			
			scrn_buf = GF_BGL_ScreenAdrsGet(dd->vpw->sys.bgl, VISUAL_FRAME_EFF);
			for(y = 0; y < DONCHOU_ANM_DATA_Y_LEN; y++){
				base_line = DonchouAnmLineData[NELEMS(DonchouAnmLineData) - 1 - dd->anm_line];
				if(base_line + y < 0){
					continue;
				}
				dest_scrn = &scrn_buf[32 * (base_line + y)];
				base_charno = DonchouAnmPaternStartCharNo[NELEMS(DonchouAnmPaternStartCharNo) - 1 - dd->anm_no] + 32*y;
				pos_x = 0;
				for(s = 0; s < 32 / DONCHOU_ANM_DATA_X_LEN; s++){
					for(x = 0; x < DONCHOU_ANM_DATA_X_LEN; x++){
						dest_scrn[pos_x + x] &= 0xfc00;		//キャラクタNoのみクリア
						dest_scrn[pos_x + x] |= base_charno + x;
					}
					pos_x += DONCHOU_ANM_DATA_X_LEN;
				}
			}
			
			//一番下のライン以外は最後まで下がった部分のアニメが抜きつきの垂れ幕なので、
			//次の段のアニメが実行されたタイミングで抜きなしのアニメに変えてやる
			//意味がわからない場合はとりあえずここの｛｝内をまるごとコメントアウトしてみれば分かる
			{
				if(dd->anm_line > 0 && dd->anm_no == 0){
					base_line = DonchouAnmLineData[NELEMS(DonchouAnmLineData) - 1 - dd->anm_line + 1];
					base_line += DONCHOU_ANM_DATA_Y_LEN - 1;
					dest_scrn = &scrn_buf[base_line * 32];
					for(s = 0; s < 32; s++){
						dest_scrn[s] &= 0xfc00;		//キャラクタNoのみクリア
						dest_scrn[s] |= DONCHOU_NUKINASHI_MAKU + (s % DONCHOU_ANM_DATA_X_LEN);
					}
				}
			}
			
			GF_BGL_LoadScreenV_Req(dd->vpw->sys.bgl, VISUAL_FRAME_EFF);
		}
		
		dd->anm_no++;
		if(dd->anm_no >= NELEMS(DonchouAnmPaternStartCharNo)){
			dd->anm_no = 0;
			dd->anm_line++;
			dd->anm_dansa_wait = DONCHOU_DANSA_ANM_WAIT;
			if(dd->anm_line >= NELEMS(DonchouAnmLineData)){
				dd->seq++;
			}
		}
		break;
	default:
		CO_ANSWER_TransmitBufferSet(dd->cow, &dd->req_head, NULL, 0);

		sys_FreeMemoryEz(dd);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：トレーナー登場
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_TrainerIn(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	VISUAL_PROC_WORK *vpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(VISUAL_ADVANCE_PARAM));
	OS_TPrintf("命令送信：トレーナー登場\n");
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：トレーナー登場
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_TrainerIn(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	VISUAL_PROC_WORK *vpw = syswork;
	VISUAL_ADVANCE_PARAM *vap = data;
	VOLOCAL_TRAINER_INOUT *tio;
	
	OS_TPrintf("命令受信：トレーナー登場\n");
	
	tio = sys_AllocMemory(HEAPID_VISUAL, sizeof(VOLOCAL_TRAINER_INOUT));
	MI_CpuClear8(tio, sizeof(VOLOCAL_TRAINER_INOUT));
	
	tio->vpw = vpw;
	tio->req_head = *req_head;
	tio->cow = cow;
	tio->breeder_no = vap->now_breeder;
	
	TCB_Add(VOTCB_TrainerIn, tio, TCBPRI_VISUAL_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   トレーナー登場
 * @param   tcb			TCBへのポインタ
 * @param   work		VOLOCAL_TRAINER_INOUT構造体
 */
//--------------------------------------------------------------
static void VOTCB_TrainerIn(TCB_PTR tcb, void *work)
{
	VOLOCAL_TRAINER_INOUT *tio = work;
	
	switch(tio->seq){
	case 0:
		VT_TrainerAdd(tio->vpw, tio->breeder_no);
		tio->x = SoftSpriteParaGet(tio->vpw->sys.trainer_ss, SS_PARA_POS_X) * 0x0100;
		tio->y = SoftSpriteParaGet(tio->vpw->sys.trainer_ss, SS_PARA_POS_Y) * 0x0100;
		tio->seq++;
		//break;
	case 1:
		tio->x -= TRAINER_IN_SPEED_X;
		if(tio->x <= (VISUAL_TRAINER_ARRIVAL_X * 0x0100)){
			tio->x = VISUAL_TRAINER_ARRIVAL_X * 0x0100;
			tio->seq++;
		}
		SoftSpriteParaSet(tio->vpw->sys.trainer_ss, SS_PARA_POS_X, tio->x / 0x0100);
		SoftSpriteParaSet(tio->vpw->sys.trainer_ss, SS_PARA_POS_Y, tio->y / 0x0100);
		break;
	default:
		CO_ANSWER_TransmitBufferSet(tio->cow, &tio->req_head, NULL, 0);

		sys_FreeMemoryEz(tio);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：トレーナー退場
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_TrainerOut(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	VISUAL_PROC_WORK *vpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(VISUAL_ADVANCE_PARAM));
	OS_TPrintf("命令送信：トレーナー退場\n");
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：トレーナー退場
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_TrainerOut(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	VISUAL_PROC_WORK *vpw = syswork;
	VISUAL_ADVANCE_PARAM *vap = data;
	VOLOCAL_TRAINER_INOUT *tio;
	
	OS_TPrintf("命令受信：トレーナー退場\n");
	
	tio = sys_AllocMemory(HEAPID_VISUAL, sizeof(VOLOCAL_TRAINER_INOUT));
	MI_CpuClear8(tio, sizeof(VOLOCAL_TRAINER_INOUT));
	
	tio->vpw = vpw;
	tio->req_head = *req_head;
	tio->cow = cow;
	tio->breeder_no = vap->now_breeder;
	
	TCB_Add(VOTCB_TrainerOut, tio, TCBPRI_VISUAL_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   トレーナー退場
 * @param   tcb			TCBへのポインタ
 * @param   work		VOLOCAL_TRAINER_INOUT構造体
 */
//--------------------------------------------------------------
static void VOTCB_TrainerOut(TCB_PTR tcb, void *work)
{
	VOLOCAL_TRAINER_INOUT *tio = work;
	
	switch(tio->seq){
	case 0:
		GF_ASSERT(tio->vpw->sys.trainer_ss != NULL);
		
		tio->x = SoftSpriteParaGet(tio->vpw->sys.trainer_ss, SS_PARA_POS_X) * 0x0100;
		tio->y = SoftSpriteParaGet(tio->vpw->sys.trainer_ss, SS_PARA_POS_Y) * 0x0100;
		tio->seq++;
		//break;
	case 1:
		tio->x += TRAINER_OUT_SPEED_X;
		if(tio->x >= (VISUAL_TRAINER_APPEAR_X * 0x0100)){
			tio->x = VISUAL_TRAINER_APPEAR_X * 0x0100;
			tio->seq++;
		}
		SoftSpriteParaSet(tio->vpw->sys.trainer_ss, SS_PARA_POS_X, tio->x / 0x0100);
		SoftSpriteParaSet(tio->vpw->sys.trainer_ss, SS_PARA_POS_Y, tio->y / 0x0100);
		break;
	default:
		VT_TrainerDel(tio->vpw);
		
		CO_ANSWER_TransmitBufferSet(tio->cow, &tio->req_head, NULL, 0);

		sys_FreeMemoryEz(tio);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：登場エフェクト
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_AppearEffect(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	VISUAL_PROC_WORK *vpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(VISUAL_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：登場エフェクト
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_AppearEffect(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	VISUAL_PROC_WORK *vpw = syswork;
	VISUAL_ADVANCE_PARAM *vap = data;
	VOLOCAL_APPEAR_EFF *ae;
	
	ae = sys_AllocMemory(HEAPID_VISUAL, sizeof(VOLOCAL_APPEAR_EFF));
	MI_CpuClear8(ae, sizeof(VOLOCAL_APPEAR_EFF));
	
	ae->vpw = vpw;
	ae->req_head = *req_head;
	ae->cow = cow;
	ae->breeder_no = vap->now_breeder;
	
	ae->ball_move.vpw = vpw;
	ae->poke_eff.vpw = vpw;
	ae->poke_eff.breeder_no = vap->now_breeder;
	ae->tr_eff.vpw = vpw;
	ae->ball_eff.pp = vpw->sys.c_game->pp[vap->now_breeder];
	
	TCB_Add(VOTCB_AppearEffect, ae, TCBPRI_VISUAL_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   登場エフェクト実行タスク
 * @param   tcb			TCBへのポインタ
 * @param   work		VOLOCAL_APPEAR_EFF構造体
 */
//--------------------------------------------------------------
static void VOTCB_AppearEffect(TCB_PTR tcb, void *work)
{
	VOLOCAL_APPEAR_EFF *ae = work;
	
	switch(ae->seq){
	case 0:
		TCB_Add(VOTCB_Sub_BallMove, &ae->ball_move, TCBPRI_VISUAL_ORDERSUB_SUB);
		TCB_Add(VOTCB_Sub_TrainerOut, &ae->tr_eff, TCBPRI_VISUAL_ORDERSUB_SUB);

		{//イメージクリップ生成(重いので先に生成して非表示にしておく)
			IMC_PLAYERSYS_INIT imc_init;
			int height;
			height = PokeParaHeightGet(
				ae->poke_eff.vpw->sys.c_game->pp[ae->poke_eff.breeder_no], PARA_FRONT);
			MI_CpuClear8(&imc_init, sizeof(IMC_PLAYERSYS_INIT));
			imc_init.heap_id = HEAPID_VISUAL;
			imc_init.x = VISUAL_ARRIVAL_X;
			imc_init.y = VISUAL_ARRIVAL_Y + height;
			ae->poke_eff.vpw->imcwork[ae->poke_eff.breeder_no].imc_ptr = 
				IMC_ContestPlayerInit_NoBG(&imc_init, 
				ae->poke_eff.vpw->consys->c_game.imc_data[ae->poke_eff.breeder_no]);
			//表示OFF
			IMC_Player_SetDrawFlag(
				ae->poke_eff.vpw->imcwork[ae->poke_eff.breeder_no].imc_ptr, FALSE);
		}

		ae->seq++;
		break;
	case 1:
		if(ae->ball_move.end == TRUE){
			TCB_Add(VOTCB_Sub_BallEffect, &ae->ball_eff, TCBPRI_VISUAL_ORDERSUB_SUB);
			TCB_Add(VOTCB_Sub_PokeAppear, &ae->poke_eff, TCBPRI_VISUAL_ORDERSUB_SUB);
			ae->seq++;
		}
		break;
	case 2:
		if(ae->ball_eff.end == TRUE && ae->poke_eff.end == TRUE && ae->tr_eff.end == TRUE){
			Snd_SePlay(VSE_AUDIENCE);
			ae->seq++;
		}
		break;
	default:
		CO_ANSWER_TransmitBufferSet(ae->cow, &ae->req_head, NULL, 0);

		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief	ボールのコールバック関数(とりあえず座標を合わせる為だけの暫定)
 * @param	emit	
 */
//--------------------------------------------------------------
static void BallEffect_CallBack(EMIT_PTR emit)
{
//	TBALL_INIT_PARAM* bip;
	
//	bip = Particle_GetTempPtr();
	
	{
		VecFx32 pos = {0, 0, 0};
		
		SPL_SetEmitterPosition(emit, &pos);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ボールエフェクト実行
 * @param   tcb			TCBへのポインタ
 * @param   work		VOLOCAL_SUB_BALL_EFF構造体
 */
//--------------------------------------------------------------
static void VOTCB_Sub_BallEffect(TCB_PTR tcb, void *work)
{
	VOLOCAL_SUB_BALL_EFF *ball_eff = work;
	
	switch(ball_eff->seq){
	case 0:
		ball_eff->bcp.client_type = CLIENT_TYPE_AA;
		ball_eff->bcp.pp = ball_eff->pp;
		ball_eff->bes = BallEffect_Init(HEAPID_VISUAL, &ball_eff->bcp);
		BallEffect_ResourceLoad(ball_eff->bes);
		BallEffect_Executed(ball_eff->bes, BallEffect_CallBack);
		
		ball_eff->seq++;
		break;
	case 1:
		if(BallEffect_EndCheck(ball_eff->bes) == FALSE){
			BallEffect_FreeMemory(ball_eff->bes);
			ball_eff->seq++;
		}
		break;
	default:
		ball_eff->end = TRUE;
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ボール移動
 * @param   tcb			TCBへのポインタ
 * @param   work		VOLOCAL_SUB_BALL_MOVE構造体
 */
//--------------------------------------------------------------
static void VOTCB_Sub_BallMove(TCB_PTR tcb, void *work)
{
	VOLOCAL_SUB_BALL_MOVE *ball_move = work;
	
	switch(ball_move->seq){
	case 0:
		ball_move->wait++;
		if(ball_move->wait >= BALL_START_WAIT){
			ball_move->wait = 0;
			ball_move->seq++;
		}
		break;
	case 1:
		{
			TBALL_MOVE_DATA bmd;

			bmd.type = EBMT_VISUAL;
			bmd.heap_id = HEAPID_VISUAL;
			bmd.mode = EBMM_THROW;
			bmd.id = 0;
			bmd.csp = ball_move->vpw->sys.csp;
			bmd.pfd = ball_move->vpw->sys.pfd;
			bmd.bg_pri = BM_BG_PRI_BATTLE;

			ball_move->bms = BM_Init(&bmd);
		}
		ball_move->seq++;
		break;
	case 2:
		if(BM_EndCheck(ball_move->bms) == TRUE){
			break;
		}
		//break;
	default:
		BM_Delete(ball_move->bms);
		ball_move->end = TRUE;
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ポケモンが拡大しながら登場
 * @param   tcb			TCBへのポインタ
 * @param   work		VOLOCAL_SUB_POKE_EFF構造体
 */
//--------------------------------------------------------------
static void VOTCB_Sub_PokeAppear(TCB_PTR tcb, void *work)
{
	VOLOCAL_SUB_POKE_EFF *poke_eff = work;
	s32 height;
//	SOFT_SPRITE *ss;
	s32 monsno;
	
	height = PokeParaHeightGet(poke_eff->vpw->sys.c_game->pp[poke_eff->breeder_no], PARA_FRONT);
//	ss = poke_eff->vpw->sys.ss[poke_eff->breeder_no];
	
	switch(poke_eff->seq){
	case 0:
		{
		#if 1
			//縮小
			poke_eff->aff_x = 0;
			poke_eff->aff_y = 0;
			IMC_Player_SetScale(poke_eff->vpw->imcwork[poke_eff->breeder_no].imc_ptr, 
				0, 0, FX32_ONE);
			
			poke_eff->vpw->imcwork[poke_eff->breeder_no].x = VISUAL_ARRIVAL_X;
			poke_eff->vpw->imcwork[poke_eff->breeder_no].y = VISUAL_ARRIVAL_Y + SOFT_SPRITE_SIZE_Y/2;
			IMC_Player_SetDrawFlag(poke_eff->vpw->imcwork[poke_eff->breeder_no].imc_ptr, TRUE);
		#else
			//VT_SoftSpriteAdd(&poke_eff->vpw->sys, poke_eff->breeder_no);
			ss = poke_eff->vpw->sys.ss[poke_eff->breeder_no];
			
			SoftSpriteParaSet(ss, SS_PARA_POS_Y, VISUAL_ARRIVAL_X);
			SoftSpriteParaSet(ss, SS_PARA_POS_Y, VISUAL_ARRIVAL_Y + height);
			
			SoftSpriteParaSet(ss, SS_PARA_VANISH, FALSE);

			//縮小
			SoftSpriteParaSet(ss, SS_PARA_AFF_X, AFF_APPEAR_X_S);
			SoftSpriteParaSet(ss, SS_PARA_AFF_Y, AFF_APPEAR_Y_S);
			SoftSpriteOYCalc(ss, height);
		#endif
		}
		poke_eff->seq++;
		//break;
	case 1:
	#if 1
		poke_eff->aff_x += POKE_AFF_SPEED_FX32;
		poke_eff->aff_y += POKE_AFF_SPEED_FX32;
		if(poke_eff->aff_x >= FX32_ONE){
			poke_eff->aff_x = FX32_ONE;
			poke_eff->aff_y = FX32_ONE;
		}
		IMC_Player_SetScale(poke_eff->vpw->imcwork[poke_eff->breeder_no].imc_ptr, 
			poke_eff->aff_x, poke_eff->aff_y, FX32_ONE);
		IMC_Player_SetPokeMatrix_Ground(poke_eff->vpw->imcwork[poke_eff->breeder_no].imc_ptr,
			poke_eff->vpw->imcwork[poke_eff->breeder_no].x, 
			poke_eff->vpw->imcwork[poke_eff->breeder_no].y,
			height);
		if(poke_eff->aff_x >= FX32_ONE){
			monsno = PokeParaGet(poke_eff->vpw->sys.c_game->pp[poke_eff->breeder_no],
				ID_PARA_monsno, NULL);
			PokeVoicePlaySet(poke_eff->vpw->consys->perap_voice[poke_eff->breeder_no],
				PV_NORMAL, monsno, 0, CONTEST_PMVOICE_VOLUME, NULL, HEAPID_VISUAL);
			
			poke_eff->seq++;
		}
	#else
		SoftSpriteParaCalc(ss, SS_PARA_AFF_X, POKE_AFF_SPEED);
		SoftSpriteParaCalc(ss, SS_PARA_AFF_Y, POKE_AFF_SPEED);
		SoftSpriteOYCalc(ss, height);
	
		if(SoftSpriteParaGet(ss, SS_PARA_AFF_X) >= AFF_APPEAR_X_B){
			SoftSpriteParaSet(ss, SS_PARA_AFF_X, AFF_APPEAR_X_B);
			SoftSpriteParaSet(ss, SS_PARA_AFF_Y, AFF_APPEAR_Y_B);
			
			monsno = PokeParaGet(poke_eff->vpw->sys.c_game->pp[poke_eff->breeder_no],
				ID_PARA_monsno, NULL);
			PokeVoicePlaySet(poke_eff->vpw->consys->perap_voice[poke_eff->breeder_no],
				PV_NORMAL, monsno, 0, CONTEST_PMVOICE_VOLUME, NULL, HEAPID_VISUAL);
			
			poke_eff->seq++;
		}
	#endif
		break;
	default:
		poke_eff->end = TRUE;
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   トレーナー退場
 * @param   tcb			TCBへのポインタ
 * @param   work		VOLOCAL_SUB_TRAINER_EFF構造体
 */
//--------------------------------------------------------------
static void VOTCB_Sub_TrainerOut(TCB_PTR tcb, void *work)
{
	VOLOCAL_SUB_TRAINER_EFF *tr_eff = work;
	
	switch(tr_eff->seq){
	case 0:
		GF_ASSERT(tr_eff->vpw->sys.trainer_ss != NULL);
		
		tr_eff->wait++;
		if(tr_eff->wait > TRAINER_MOVE_START_WAIT){
			tr_eff->wait = 0;
			tr_eff->seq++;
		}
		break;
	case 1:
		tr_eff->x = SoftSpriteParaGet(tr_eff->vpw->sys.trainer_ss, SS_PARA_POS_X) * 0x0100;
		tr_eff->y = SoftSpriteParaGet(tr_eff->vpw->sys.trainer_ss, SS_PARA_POS_Y) * 0x0100;
		tr_eff->seq++;
		//break;
	case 2:
		if(tr_eff->loop & 1){
			SoftSpriteParaSet(tr_eff->vpw->sys.trainer_ss, SS_PARA_POS_X, tr_eff->x / 0x0100);
			SoftSpriteParaSet(tr_eff->vpw->sys.trainer_ss, SS_PARA_POS_Y, tr_eff->y / 0x0100);
		}
		else{
			SoftSpriteParaSet(tr_eff->vpw->sys.trainer_ss, SS_PARA_POS_X, tr_eff->x / 0x0100);
			SoftSpriteParaSet(tr_eff->vpw->sys.trainer_ss, SS_PARA_POS_Y, 
				tr_eff->y / 0x0100 - TRAINER_BALL_SHAKE_Y);
		}
		
		tr_eff->loop++;
		if(tr_eff->loop >= TRAINER_BALL_SHAKE_LOOP){
			tr_eff->seq++;
		}
		break;
	case 3:
		tr_eff->wait++;
		if(tr_eff->wait >= TRAINER_BALL_OUT_WAIT){
			tr_eff->wait = 0;
			tr_eff->seq++;
		}
		break;
	case 4:
		tr_eff->x += TRAINER_OUT_SPEED_X;
		if(tr_eff->x >= (VISUAL_TRAINER_APPEAR_X * 0x0100)){
			tr_eff->x = VISUAL_TRAINER_APPEAR_X * 0x0100;
			tr_eff->seq++;
		}
		SoftSpriteParaSet(tr_eff->vpw->sys.trainer_ss, SS_PARA_POS_X, tr_eff->x / 0x0100);
		SoftSpriteParaSet(tr_eff->vpw->sys.trainer_ss, SS_PARA_POS_Y, tr_eff->y / 0x0100);
		break;
	default:
		VT_TrainerDel(tr_eff->vpw);
		
		tr_eff->end = TRUE;
		TCB_Delete(tcb);
		return;
	}
}

//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：会話メッセージの表示
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_Talk(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	VISUAL_PROC_WORK *vpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(VISUAL_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：会話メッセージの表示
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_Talk(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	VISUAL_PROC_WORK *vpw = syswork;
	VISUAL_ADVANCE_PARAM *vap = data;
	VOLOCAL_TALK_PUT *talk;
	
	talk = sys_AllocMemory(HEAPID_VISUAL, sizeof(VOLOCAL_TALK_PUT));
	MI_CpuClear8(talk, sizeof(VOLOCAL_TALK_PUT));
	
	talk->vpw = vpw;
	talk->req_head = *req_head;
	talk->cow = cow;
	talk->breeder_no = vap->now_breeder;
	
	talk->a_talk_tagpara = vap->a_talk_tagpara;
	talk->a_talk_id = vap->a_talk_id;
	talk->a_talk_bmpwin_not_close = vap->a_talk_bmpwin_not_close;
	talk->a_talk_bmpwin_close_wait = vap->a_talk_bmpwin_close_wait;
	
	TCB_Add(VOTCB_TalkPut, talk, TCBPRI_VISUAL_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   会話メッセージの表示
 * @param   tcb			TCBへのポインタ
 * @param   work		VOLOCAL_TALK_PUT構造体
 */
//--------------------------------------------------------------
static void VOTCB_TalkPut(TCB_PTR tcb, void *work)
{
	VOLOCAL_TALK_PUT *talk = work;
	
	switch(talk->seq){
	case 0:
		if(talk->a_talk_id != A_TALK_VISUAL_NULL){
			BmpTalkWinWrite(&talk->vpw->sys.win[VISUAL_BMPWIN_TALK], WINDOW_TRANS_OFF,
				VISUAL_TALKWIN_CGX_OFFSET, VISUAL_TALKWIN_PALNO);
			GF_BGL_LoadScreenV_Req(talk->vpw->sys.bgl, VISUAL_FRAME_WIN);
			
			VT_A_TalkMessageSet(talk->vpw, talk->a_talk_id, &talk->a_talk_tagpara);
			talk->seq++;
		}
		else{
			talk->seq = 100;
		}
		break;
	case 1:
		if(VT_TalkMessageEndCheck(talk->vpw) == 0){
			talk->seq++;
		}
		break;
	case 2:
		talk->close_wait++;
		if(talk->a_talk_bmpwin_not_close == TRUE){
			talk->seq++;
		}
		else if(talk->close_wait >= talk->a_talk_bmpwin_close_wait){
			BmpTalkWinClear(&talk->vpw->sys.win[VISUAL_BMPWIN_TALK], WINDOW_TRANS_OFF);
			GF_BGL_LoadScreenV_Req(talk->vpw->sys.bgl, VISUAL_FRAME_WIN);
			talk->seq++;
		}
		break;
	default:
		CO_ANSWER_TransmitBufferSet(talk->cow, &talk->req_head, NULL, 0);

		sys_FreeMemoryEz(talk);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：画面全体フェードイン・アウト
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_FadeInOut(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	VISUAL_PROC_WORK *vpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, work, sizeof(VISUAL_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：画面全体フェードイン・アウト
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_FadeInOut(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	VISUAL_PROC_WORK *vpw = syswork;
	VOLOCAL_DFO *dfo;
	VISUAL_ADVANCE_PARAM *vap = data;
	
	dfo = sys_AllocMemory(HEAPID_VISUAL, sizeof(VOLOCAL_DFO));
	MI_CpuClear8(dfo, sizeof(VOLOCAL_DFO));

	dfo->vpw = vpw;
	dfo->req_head = *req_head;
	dfo->cow = cow;
	
	dfo->fade_start_evy = vap->fade_start_evy;
	dfo->fade_end_evy = vap->fade_end_evy;
	dfo->fade_wait = vap->fade_wait;
	dfo->fade_next_rgb = dfo->fade_next_rgb;

	TCB_Add(VOTCB_FadeInOut, dfo, TCBPRI_VISUAL_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   画面全体フェードイン・アウト
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		VOLOCAL_DFO構造体
 */
//--------------------------------------------------------------
static void VOTCB_FadeInOut(TCB_PTR tcb, void *work)
{
	VOLOCAL_DFO *dfo = work;
	int height;
	
	switch(dfo->seq){
	case 0:
		if(dfo->vpw->consys->sio_flag == TRUE){
			//受信強度アイコンにフェードがかからないようにウィンドウ１で囲む
			G2_SetWnd1InsidePlane(
				GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2
				| GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, FALSE);
			G2_SetWndOutsidePlane(
				GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2
				| GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE);
			GX_SetVisibleWnd(GX_WNDMASK_W1);
			dfo->vpw->wnd1_x1 = 256 - 16;
			dfo->vpw->wnd1_y1 = 0;
			dfo->vpw->wnd1_x2 = 255;
			dfo->vpw->wnd1_y2 = 16;
		}

		ChangeBrightnessRequest(dfo->fade_wait, dfo->fade_end_evy, dfo->fade_start_evy, 
			PLANEMASK_ALL ^ GX_BLEND_PLANEMASK_BG1, MASK_MAIN_DISPLAY);
//		PaletteFadeReq(dfo->vpw->sys.pfd, PF_BIT_MAIN_BG, DFO_FADE_BIT, 0, 
//			0, 16, dfo->fade_next_rgb);
//		PaletteFadeReq(dfo->vpw->sys.pfd, PF_BIT_MAIN_OBJ, DFO_FADE_BIT_OBJ, 0, 
//			0, 16, dfo->fade_next_rgb);
		dfo->seq++;
		break;
	case 1:
//		if(PaletteFadeCheck(dfo->vpw->sys.pfd) == 0){
		if(IsFinishedBrightnessChg(MASK_MAIN_DISPLAY) == TRUE){
			PaletteWork_Clear(dfo->vpw->sys.pfd, FADE_MAIN_BG, FADEBUF_TRANS, 0x0000, 0, 
				DFO_FADE_COLOR_NUM);
			PaletteWork_Clear(dfo->vpw->sys.pfd, FADE_MAIN_OBJ, FADEBUF_TRANS, 0x0000, 0, 
				DFO_FADE_COLOR_NUM_OBJ);
			dfo->seq++;
		}
		break;
	default:
		CO_ANSWER_TransmitBufferSet(dfo->cow, &dfo->req_head, NULL, 0);

		sys_FreeMemoryEz(dfo);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：どんちょうエフェクト上昇
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_DonchouEffectUp(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	VISUAL_PROC_WORK *vpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, NULL, 0);
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：どんちょうエフェクト上昇
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_DonchouEffectUp(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	VISUAL_PROC_WORK *vpw = syswork;
	VOLOCAL_DONCHOU_EFFECT_UP *deu;
	
	deu = sys_AllocMemory(HEAPID_VISUAL, sizeof(VOLOCAL_DONCHOU_EFFECT_UP));
	MI_CpuClear8(deu, sizeof(VOLOCAL_DONCHOU_EFFECT_UP));

	deu->vpw = vpw;
	deu->req_head = *req_head;
	deu->cow = cow;

	TCB_Add(VOTCB_DonchouEffectUp, deu, TCBPRI_VISUAL_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   どんちょうエフェクト上昇
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		VOLOCAL_DONCHOU_EFFECT_UP構造体
 */
//--------------------------------------------------------------
static void VOTCB_DonchouEffectUp(TCB_PTR tcb, void *work)
{
	VOLOCAL_DONCHOU_EFFECT_UP *deu = work;
	int set_anm_wait;
	
	deu->lvup_wait++;
	if(deu->lvup_wait == DEU_SPEED_LVUP_WAIT){
		set_anm_wait = 0;
		deu->anm_wait = DEU_SPEED_LVUP_STOP_WAIT;
		deu->lvup_se_req = TRUE;
	}
	if(deu->vpw->consys->sio_flag == FALSE && deu->lvup_wait < DEU_SPEED_LVUP_WAIT 
			&& ((sys.trg & PAD_BUTTON_DECIDE) || (sys.tp_trg))){
		deu->lvup_wait = DEU_SPEED_LVUP_WAIT;	//決定ボタンで無理矢理レベルアップした時の為
		set_anm_wait = 0;
		deu->anm_wait = 0;
		deu->lvup_se_req = TRUE;
	}
	else if(deu->lvup_wait > DEU_SPEED_LVUP_WAIT){
		set_anm_wait = 0;
	}
	else{
		set_anm_wait = DONCHOU_ANM_WAIT;
	}
	
	switch(deu->seq){
	case 0:
		//アニメウェイト
		if(deu->anm_dansa_wait > 0){
			deu->anm_dansa_wait--;
			break;
		}
		if(deu->anm_wait > 0){
			deu->anm_wait--;
			break;
		}
		deu->anm_wait = set_anm_wait;
		if(deu->lvup_se_req == TRUE){
			Snd_SePlay(VSE_CURTAIN_LVUP);
			deu->lvup_se_req = FALSE;
		}
		
		//アニメ書き換え
		{
			u16 *scrn_buf, *dest_scrn;
			int x, y, pos_x, s, base_charno;
			
			scrn_buf = GF_BGL_ScreenAdrsGet(deu->vpw->sys.bgl, VISUAL_FRAME_EFF);
			for(y = 0; y < DONCHOU_ANM_DATA_Y_LEN; y++){
				if(DonchouAnmLineData[deu->anm_line] + y < 0){
					continue;
				}
				dest_scrn = &scrn_buf[32 * (DonchouAnmLineData[deu->anm_line] + y)];
				base_charno = DonchouAnmPaternStartCharNo[deu->anm_no] + 32*y;
				pos_x = 0;
				for(s = 0; s < 32 / DONCHOU_ANM_DATA_X_LEN; s++){
					for(x = 0; x < DONCHOU_ANM_DATA_X_LEN; x++){
						dest_scrn[pos_x + x] &= 0xfc00;		//キャラクタNoのみクリア
						dest_scrn[pos_x + x] |= base_charno + x;
					}
					pos_x += DONCHOU_ANM_DATA_X_LEN;
				}
			}
			
			//2段目以降のどんちょうでは最後のアニメが一ライン残ったやつなので、
			//前のどんちょうの残った部分をクリアしてやる
			//意味がわからない場合はとりあえずここの｛｝内をまるごとコメントアウトしてみれば分かる
			{
				if(deu->anm_line > 0 && deu->anm_no == 0){
					dest_scrn = &scrn_buf[32 * DonchouAnmLineData[deu->anm_line - 1]];
					for(s = 0; s < 32; s++){
						dest_scrn[s] &= 0xfc00;		//キャラクタNoのみクリア
					}
				}
			}
			
			GF_BGL_LoadScreenV_Req(deu->vpw->sys.bgl, VISUAL_FRAME_EFF);
		}

		//ウィンドウマスク設定
		{
			deu->vpw->wnd0_y2 = (DonchouAnmLineData[deu->anm_line] + DONCHOU_ANM_DATA_Y_LEN) * 8 
				- (deu->anm_no * (DONCHOU_ANM_DATA_Y_LEN*8) / NELEMS(DonchouAnmPaternStartCharNo));
			if(deu->vpw->wnd0_y2 == 0){
				G2_BlendNone();
				GX_SetVisibleWnd(GX_WNDMASK_NONE);
			}
		}
		
		deu->anm_no++;
		if(deu->anm_no >= NELEMS(DonchouAnmPaternStartCharNo)){
			deu->anm_no = 0;
			deu->anm_line++;
			deu->anm_dansa_wait = DONCHOU_DANSA_ANM_WAIT;
			if(deu->anm_line >= NELEMS(DonchouAnmLineData)){
				deu->seq++;
			}
		}
		break;
	default:
		G2_BlendNone();
		GX_SetVisibleWnd(GX_WNDMASK_NONE);

		CO_ANSWER_TransmitBufferSet(deu->cow, &deu->req_head, NULL, 0);

		sys_FreeMemoryEz(deu);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：ビジュアル部門終了時の処理
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_VisualFinish(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	VISUAL_PROC_WORK *vpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, work, sizeof(VISUAL_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：ビジュアル部門終了時の処理
 *
 * @param   vpw			ビジュアル部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_VisualFinish(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	VISUAL_PROC_WORK *vpw = syswork;
	VISUAL_ADVANCE_PARAM *vap = data;
	VOLOCAL_FINISH *vof;
	
	vof = sys_AllocMemory(HEAPID_VISUAL, sizeof(VOLOCAL_FINISH));
	MI_CpuClear8(vof, sizeof(VOLOCAL_FINISH));

	vof->vpw = vpw;
	vof->req_head = *req_head;
	vof->cow = cow;

	Snd_SePlay(vap->se_id);

	TCB_Add(VOTCB_Finish, vof, TCBPRI_VISUAL_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   画面全体フェードイン・アウト
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		VOLOCAL_FINISH構造体
 */
//--------------------------------------------------------------
static void VOTCB_Finish(TCB_PTR tcb, void *work)
{
	VOLOCAL_FINISH *vof = work;
	
	switch(vof->seq){
	case 0:
	default:
		if(vof->vpw->heart_count == 0){
			CO_ANSWER_TransmitBufferSet(vof->cow, &vof->req_head, NULL, 0);

			sys_FreeMemoryEz(vof);
			TCB_Delete(tcb);
			return;
		}
		break;
	}
}
