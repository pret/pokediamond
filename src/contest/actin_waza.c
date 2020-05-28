//==============================================================================
/**
 * @file	actin_waza.c
 * @brief	演技力部門：技効果
 * @author	matsuda
 * @date	2006.01.26(木)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "actin.h"
#include "actin_tcb_pri.h"
#include "battle/battle_common.h"
#include "system/clact_tool.h"
#include "system/palanm.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "wazaeffect/battle_particle.h"
#include "system/particle.h"
#include "wazaeffect/we_mana.h"
#include "wazaeffect/we_sys.h"

#include "system/brightness.h"

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "actin_tool.h"
#include "actin_order.h"
#include "actin_id.h"
#include "actin_input.h"
#include "actin_calc.h"
#include "con_tool.h"

#include "poketool/waza_tool.h"


//==============================================================================
//	定数定義
//==============================================================================
///技効果を発生させるタイミング定義(実行する順番)
enum{
	//-- このタイミングではまだ基本AP等は未取得 --//
	SPMSG_TIMING_FIRST,		///<技エフェクト実行前に特殊メッセージ
	
	KOUKA_TIMING_FIRST,		///<即実行する効果(主にシールド系等)
	KOUKA_TIMING_FIELD,		///<場にかかる効果(主に全体妨害技等)
	
	//-- ここで基本APやボルテージ値等を取得 --//
	
	KOUKA_TIMING_NOW,		///<自分のアピールの時に発動する効果
	
	//-- ここで取得AP、技効果、妨害等で取得したAP値の加減算を行い合計を出す --//
	
	KOUKA_TIMING_AFTER,		///<全員のアピール終了後に発生する効果
	KOUKA_TIMING_JUDGESUFFER,	///<審判被り系の技効果
	
	//-- ここで審判被り分の加算 --//
	
	KOUKA_TIMING_END,		///<全ての処理の最後に発生する効果
};

///メッセージタグ指定する時、使用しないので、意図的に指定なし、と表記する為の定義
#define TAG_NULL		(30000)

///特殊メッセージを使用しない
#define SPMSG_TIMING_NULL		(0xff)

//==============================================================================
//	構造体定義
//==============================================================================
///技効果シーケンスの関数型定義
typedef int (*KOUKA_FUNC)(ACTIN_PROC_WORK *, AWAZA_PARAM *, int, int, int);

///技効果シーケンスデータ構造体
typedef struct{
	KOUKA_FUNC func;		///<実行関数へのポインタ
	u8 timing;				///<実行タイミング
	u8 sp_msg;				///<特殊メッセージを表示させるタイミング
	
	u8 dummy[2];
}KOUKA_SEQ_DATA;


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static void AWAZA_SaveParamUpdate(AWAZA_PARAM *wp);

static int Kouka_NextFirst(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_NextEnd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_JudgeSufferAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_VoltageUpAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_Null(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_NoneJudgeSufferAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_Continuation(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_VoltageAddAP(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_AllSufferAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_AllVoltageSub(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_NextTurnTwice(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_VoltageUpStop(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_FrontSame(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_NextRandom(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_EndTwice(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_VoltageLevelAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_FirstAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_EndAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_VoltageSubStop(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_ContinuationVoltageAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_SortAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_VoltageMaxAfterAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);
static int Kouka_LowPointAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, 
	int kouka_breeder, int pos);


//==============================================================================
//	データ
//==============================================================================
#include "actin_waza.dat"

///演技力部門メイン関数のシーケンステーブル
static const KOUKA_SEQ_DATA KoukaSeqTbl[] = {
	{Kouka_Null, 				KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      	//0 1オリジンの為ダミー
	{Kouka_NextFirst,			KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},			//1
	{Kouka_NextEnd, 			KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//2
	{Kouka_JudgeSufferAdd, 		KOUKA_TIMING_JUDGESUFFER, SPMSG_TIMING_NULL},	//3
	{Kouka_VoltageUpAdd, 		KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//4
	{Kouka_Null, 				KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//5
	{Kouka_NoneJudgeSufferAdd, 	KOUKA_TIMING_JUDGESUFFER, SPMSG_TIMING_FIRST}, 	//6
	{Kouka_Continuation, 		KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//7
	{Kouka_VoltageAddAP, 		KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//8
	{Kouka_AllSufferAdd, 		KOUKA_TIMING_JUDGESUFFER, SPMSG_TIMING_FIRST},	//9
	{Kouka_AllVoltageSub, 		KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//10
	{Kouka_NextTurnTwice, 		KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//11
	{Kouka_FrontSame, 			KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//12
	{Kouka_VoltageUpStop, 		KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//13
	{Kouka_NextRandom, 			KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//14
	{Kouka_EndTwice, 			KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//15
	{Kouka_VoltageLevelAdd, 	KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//16
	{Kouka_FirstAdd, 			KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//17
	{Kouka_EndAdd, 				KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},      		//18
	{Kouka_VoltageSubStop,		KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},			//19
	{Kouka_ContinuationVoltageAdd, KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},		//20
	{Kouka_SortAdd,				KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},			//21
	{Kouka_VoltageMaxAfterAdd,	KOUKA_TIMING_NOW, SPMSG_TIMING_NULL},			//22
	{Kouka_LowPointAdd,			KOUKA_TIMING_END, SPMSG_TIMING_NULL},			//23
};


//--------------------------------------------------------------
/**
 * @brief   メッセージパラメータセット
 *
 * @param   personal		
 * @param   apno			技効果番号
 * @param   msg_type		使用するメッセージタイプ(KOUKA_MSGID_???)
 * @param   mine			MINEタグの時参照するブリーダーの番号
 * @param   enemy			ENEMYタグの時参照するブリーダーの番号
 * @param   wazano			WAZAタグの時参照する技番号
 * @param   num				NUMタグの時参照する数値
 */
//--------------------------------------------------------------
static void AWAZA_MsgParamSet(AWAZA_PERSONAL *personal, int apno, int msg_type, int mine, int enemy, int wazano, int num)
{
	personal->msg_apno = apno;
	personal->msg_type = msg_type;

	if(mine != TAG_NULL){
		personal->tagpara.mine_brd = mine;
	}
	if(enemy != TAG_NULL){
		personal->tagpara.enemy_brd = enemy;
	}
	if(wazano != TAG_NULL){
		personal->tagpara.wazano = wazano;
	}
	if(num != TAG_NULL){
		personal->tagpara.num = num;
	}

	OS_TPrintf("技効果メッセージセット：msg_apno=%d, msg_type=%d\n", apno, msg_type);
}

//--------------------------------------------------------------
/**
 * @brief   ターンの最初に行う必要のある初期化処理
 *
 * @param   apw		演技力部門管理ワークへのポインタ
 * @param   wp		技効果パラメータへのポインタ
 */
//--------------------------------------------------------------
void AWAZA_WazaParaTurnInit(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp)
{
	int breeder_no;
	
	*wp = apw->a_game.wazapara;
	
	AWAZA_SaveParamUpdate(wp);	//personalをクリアする前に値更新
	MI_CpuClear8(wp->personal, sizeof(AWAZA_PERSONAL) * BREEDER_MAX);
	
	for(breeder_no = 0; breeder_no < BREEDER_MAX; breeder_no++){
		AT_MsgTagParaInitDataSet(apw, &wp->personal[breeder_no].tagpara, breeder_no);

		wp->personal[breeder_no].judge_no = apw->a_game.judge_no[breeder_no];
		wp->personal[breeder_no].wazano = apw->a_game.waza_no[breeder_no];
		wp->personal[breeder_no].apno = WT_WazaDataParaGet(
			wp->personal[breeder_no].wazano, ID_WTD_ap_no);
		wp->personal[breeder_no].judge_suffer = ACALC_JudgeSufferCheck(&apw->a_game, breeder_no);
	}
}

//--------------------------------------------------------------
/**
 * @brief   各ブリーダーの演技開始前に行う必要のある初期化処理
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   breeder_no		ブリーダーNo
 */
//--------------------------------------------------------------
void AWAZA_WazaParaBreederInit(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		wp->personal[i].before_next_sort = wp->personal[i].next_sort;
		wp->personal[i].before_next_pos = wp->personal[i].next_pos;
	}

	for(i = 0; i < JUDGE_MAX; i++){
		wp->voltage_before[i] = apw->a_game.voltage_total[i];
		wp->voltage_after[i] = apw->a_game.voltage_total[i];
	}
}

//--------------------------------------------------------------
/**
 * @brief   各ブリーダーの演技終了後に行う、ゲームパラメータへのデータ更新処理
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   breeder_no		ブリーダーNo
 */
//--------------------------------------------------------------
void AWAZA_WazaParaBreederGameUpdate(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no)
{
	int i;
	
	for(i = 0; i < JUDGE_MAX; i++){
		apw->a_game.voltage_total[i] = wp->voltage_after[i];
		if(apw->a_game.voltage_total[i] >= VOLTAGE_POINT_FULL){
			apw->a_game.voltage_total[i] = 0;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   ターン終了後に行う、ゲームパラメータへのデータ更新処理
 *
 * @param   apw		演技力部門管理ワークへのポインタ
 * @param   wp		技効果パラメータへのポインタ
 */
//--------------------------------------------------------------
void AWAZA_WazaParaTurnGameUpdate(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		apw->a_game.app_total[i] += wp->personal[i].app_total;
		apw->a_game.app_turn[i] = wp->personal[i].app_total;
	}
	apw->a_game.wazapara = *wp;
}


//--------------------------------------------------------------
/**
 * @brief   技計算前に行う必要のある各種パラメータ更新処理
 *
 * @param   wp				技効果パラメータへのポインタ
 * @param   breeder_no		技を出すぶりーだーの番号
 */
//--------------------------------------------------------------
static void AWAZA_CalcInitUpdateParam(AWAZA_PARAM *wp, int breeder_no)
{
	int i;

	wp->personal[breeder_no].app_total_before = wp->personal[breeder_no].app_total;
	wp->personal[breeder_no].my_effective_ap = 0;
	wp->personal[breeder_no].enemy_effective_ap = 0;

	//変更前のボルテージ値取得
	for(i = 0; i < JUDGE_MAX; i++){
		wp->voltage_before[i] = wp->voltage_after[i];
	}
	
	for(i = 0; i < BREEDER_MAX; i++){
		wp->personal[i].kouka_occ = FALSE;
		wp->personal[i].msg_apno = 0;
	}
}

//--------------------------------------------------------------
/**
 * @brief   全員の技効果発生前のAP値を記憶
 * @param   wp		技効果パラメータへのポインタ
 */
//--------------------------------------------------------------
void AWAZA_TimingBeforeAppUpdate(AWAZA_PARAM *wp)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		wp->personal[i].app_total_timing_before = wp->personal[i].app_total;
	}
}

//--------------------------------------------------------------
/**
 * @brief   技エフェクト実行前に表示する特殊メッセージの判定を行う
 *
 * @param   apw					演技力部門管理ワークへのポインタ
 * @param   wp					技効果パラメータへのポインタ
 * @param   breeder_no			技を出しているブリーダー
 */
//--------------------------------------------------------------
void AWAZA_FirstMsg(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no)
{
	u32 msg_id, msg_tag;

	AWAZA_CalcInitUpdateParam(wp, breeder_no);
	
	if(KoukaSeqTbl[wp->personal[breeder_no].apno].sp_msg == SPMSG_TIMING_FIRST){
		ConTool_GetKoukaMsgID(wp->personal[breeder_no].apno, KOUKA_MSGID_SP, &msg_id, &msg_tag);
		if(msg_id != AMSG_ID_NONE){
			AWAZA_MsgParamSet(&wp->personal[breeder_no], wp->personal[breeder_no].apno, 
				KOUKA_MSGID_SP, breeder_no, TAG_NULL, TAG_NULL, TAG_NULL);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   技の基本AP値の計算を行う
 *
 * @param   apw					演技力部門管理ワークへのポインタ
 * @param   wp					技効果パラメータへのポインタ
 * @param   breeder_no			技を出しているブリーダー
 */
//--------------------------------------------------------------
void AWAZA_BaseAP(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no)
{
	AWAZA_CalcInitUpdateParam(wp, breeder_no);
	
	wp->personal[breeder_no].base_ap = ConTool_GetAPWaza_App(wp->personal[breeder_no].apno);
	
	wp->personal[breeder_no].app_total = wp->personal[breeder_no].base_ap;
}

//--------------------------------------------------------------
/**
 * @brief   技効果発動処理
 *
 * @param   apw					演技力部門管理ワークへのポインタ
 * @param   wp					技効果パラメータへのポインタ
 * @param   now_breeder			技を出しているブリーダー
 * @param   now_breeder_pos		技を出しているブリーダーは何番目のアピールか
 */
//--------------------------------------------------------------
void AWAZA_Kouka(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, int now_breeder_pos)
{
	int i;
	
	AWAZA_CalcInitUpdateParam(wp, now_breeder);
	
	//アピールした本人の技効果発生
	if(KoukaSeqTbl[wp->personal[now_breeder].apno].timing == KOUKA_TIMING_NOW){
		OS_TPrintf("＠＠＠NOW技効果発生：%d＠＠＠(ブリーダーNo%d、pos=%d)\n",
			wp->personal[now_breeder].apno, now_breeder, now_breeder_pos);
		KoukaSeqTbl[wp->personal[now_breeder].apno].func(apw, wp, now_breeder, 
			now_breeder, now_breeder_pos);
		wp->personal[now_breeder].kouka_occ = TRUE;
		wp->personal[now_breeder].app_total += wp->personal[now_breeder].my_effective_ap 
			+ wp->personal[now_breeder].enemy_effective_ap;
	}
	
	//既にアピール済みのブリーダー達の技効果発生チェック
	for(i = 0; i <= now_breeder_pos/*apw->a_game.breeder_end_count*/; i++){
		int kouka_breeder = apw->a_game.breeder_sort[i];
		if(KoukaSeqTbl[wp->personal[kouka_breeder].apno].timing == KOUKA_TIMING_FIELD){
			OS_TPrintf("＠＠＠FIELD技効果発生：%d＠＠＠(ブリーダーNo%d、pos=%d)\n",
				wp->personal[kouka_breeder].apno, kouka_breeder, i);
			AWAZA_CalcInitUpdateParam(wp, kouka_breeder);
			KoukaSeqTbl[wp->personal[kouka_breeder].apno].func(apw, wp, 
				now_breeder, kouka_breeder, now_breeder_pos);
			wp->personal[kouka_breeder].kouka_occ = TRUE;
			wp->personal[kouka_breeder].app_total += wp->personal[kouka_breeder].my_effective_ap;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   出した技の技効果発動後に発動する特殊技効果
 *
 * @param   apw					演技力部門管理ワークへのポインタ
 * @param   wp					技効果パラメータへのポインタ
 * @param   now_breeder			
 * @param   now_breeder_pos		
 */
//--------------------------------------------------------------
void AWAZA_KoukaSpecial(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, 
	int now_breeder, int now_breeder_pos)
{
	int add_ap;

	AWAZA_CalcInitUpdateParam(wp, now_breeder);
	
	if(wp->save[now_breeder].twice_now_apno != 0){
		OS_TPrintf("＠＠＠次ターン2倍の技効果発生＠＠＠(ブリーダーNo%d、pos=%d)\n",
			now_breeder, now_breeder_pos);
		add_ap = wp->personal[now_breeder].app_total;
		wp->personal[now_breeder].my_effective_ap += add_ap;
		AWAZA_MsgParamSet(&wp->personal[now_breeder], wp->save[now_breeder].twice_now_apno, 
			KOUKA_MSGID_A, now_breeder, TAG_NULL, TAG_NULL, add_ap / APPEAL_ICON_ONE_POINT);
	}

	wp->personal[now_breeder].app_total += wp->personal[now_breeder].my_effective_ap 
		+ wp->personal[now_breeder].enemy_effective_ap;
}

//--------------------------------------------------------------
/**
 * @brief   技効果発動処理(全員演技終了後)
 *
 * @param   apw					演技力部門管理ワークへのポインタ
 * @param   wp					技効果パラメータへのポインタ
 * @param   now_breeder			技を出しているブリーダー
 * @param   now_breeder_pos		技を出しているブリーダーは何番目のアピールか
 *
 * @retval	TRUE:発動タイミングだったので処理が行われた。　FALSE:処理は行われなかった
 */
//--------------------------------------------------------------
BOOL AWAZA_KoukaAfterTiming(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, 
	int now_breeder_pos)
{
	int i;
	
	AWAZA_CalcInitUpdateParam(wp, now_breeder);
	
	if(KoukaSeqTbl[wp->personal[now_breeder].apno].timing == KOUKA_TIMING_AFTER){
		OS_TPrintf("＠＠＠AFTER技効果発生：%d＠＠＠(ブリーダーNo%d、pos=%d)\n",
			wp->personal[now_breeder].apno, now_breeder, now_breeder_pos);
		KoukaSeqTbl[wp->personal[now_breeder].apno].func(apw, wp, now_breeder, 
			now_breeder, now_breeder_pos);
		wp->personal[now_breeder].kouka_occ = TRUE;
		wp->personal[now_breeder].app_total += wp->personal[now_breeder].my_effective_ap;
		return TRUE;
	}
	
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   審判被り系の技効果発動処理(全員演技終了後)
 *
 * @param   apw					演技力部門管理ワークへのポインタ
 * @param   wp					技効果パラメータへのポインタ
 * @param   now_breeder			技を出しているブリーダー
 * @param   now_breeder_pos		技を出しているブリーダーは何番目のアピールか
 *
 * @retval	TRUE:発動タイミングだったので処理が行われた。　FALSE:処理は行われなかった
 */
//--------------------------------------------------------------
BOOL AWAZA_KoukaJudgeSufferTiming(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, 
	int now_breeder_pos)
{
	int i;
	
	AWAZA_CalcInitUpdateParam(wp, now_breeder);
	
	if(KoukaSeqTbl[wp->personal[now_breeder].apno].timing == KOUKA_TIMING_JUDGESUFFER){
		OS_TPrintf("＠＠＠JUDGE_SUFFER技効果発生：%d＠＠＠(ブリーダーNo%d、pos=%d)\n",
			wp->personal[now_breeder].apno, now_breeder, now_breeder_pos);
		KoukaSeqTbl[wp->personal[now_breeder].apno].func(apw, wp, now_breeder, 
			now_breeder, now_breeder_pos);
		wp->personal[now_breeder].kouka_occ = TRUE;
		wp->personal[now_breeder].app_total += wp->personal[now_breeder].my_effective_ap;
		return TRUE;
	}
	
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   技効果発動処理(全てのアピール終了後)
 *
 * @param   apw					演技力部門管理ワークへのポインタ
 * @param   wp					技効果パラメータへのポインタ
 * @param   now_breeder			技を出しているブリーダー
 * @param   now_breeder_pos		技を出しているブリーダーは何番目のアピールか
 *
 * @retval	TRUE:発動タイミングだったので処理が行われた。　FALSE:処理は行われなかった
 */
//--------------------------------------------------------------
BOOL AWAZA_KoukaEndTiming(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, 
	int now_breeder_pos)
{
	int i;
	
	AWAZA_CalcInitUpdateParam(wp, now_breeder);
	
	if(KoukaSeqTbl[wp->personal[now_breeder].apno].timing == KOUKA_TIMING_END){
		OS_TPrintf("＠＠＠END技効果発生：%d＠＠＠(ブリーダーNo%d、pos=%d)\n",
			wp->personal[now_breeder].apno, now_breeder, now_breeder_pos);
		KoukaSeqTbl[wp->personal[now_breeder].apno].func(apw, wp, now_breeder, 
			now_breeder, now_breeder_pos);
		wp->personal[now_breeder].kouka_occ = TRUE;
		wp->personal[now_breeder].app_total += wp->personal[now_breeder].my_effective_ap;
		return TRUE;
	}
	
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   技を出した後のボルテージ計算処理
 *
 * @param   apw					演技力部門管理ワークへのポインタ
 * @param   wp					技効果パラメータへのポインタ
 * @param   breeder_no			技を出しているブリーダーの番号
 * @param   nt					A_TALK用通常会話メッセージ代入先
 */
//--------------------------------------------------------------
void AWAZA_Voltage(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no, NORMAL_TALK *nt)
{
	int k, judge_no, voltage_addsub;

	AWAZA_CalcInitUpdateParam(wp, breeder_no);
	nt->a_talk_id = A_TALK_NULL;
	nt->after_a_talk_id = A_TALK_NULL;
	
	judge_no = apw->a_game.judge_no[breeder_no];
	
	//ボルテージチェック
	voltage_addsub = ACALC_VoltageUpDownCheck(apw->consys->c_game.type, 
		wp->personal[breeder_no].wazano, judge_no, apw->consys->c_game.special_judge_no);
	
	if(voltage_addsub > 0 && wp->personal[breeder_no].invalid_voltage_up == 0){
		wp->voltage_after[judge_no] += voltage_addsub;
		if(wp->voltage_after[judge_no] >= VOLTAGE_POINT_FULL){
			wp->voltage_after[judge_no] = VOLTAGE_POINT_FULL;
		}
	}
	else if(voltage_addsub < 0 && wp->personal[breeder_no].invalid_voltage_down == 0
			&& wp->voltage_after[judge_no] > 0){
		wp->voltage_after[judge_no] += voltage_addsub;
		if(wp->voltage_after[judge_no] <= 0){
			wp->voltage_after[judge_no] = 0;
		}
	}
	else{
		voltage_addsub = 0;
	}
	
	//ボルテージ最大チェック
	if(wp->voltage_after[judge_no] >= VOLTAGE_POINT_FULL){
		if(judge_no == apw->consys->c_game.special_judge_no){
			wp->personal[breeder_no].voltage_add_ap = VOLTAGE_FULL_ADD_AP_SPECIAL;
		}
		else{
			wp->personal[breeder_no].voltage_add_ap = VOLTAGE_FULL_ADD_AP;
		}
	}

#if 0
	//最大に達しているボルテージを0クリア
	for(k = 0; k < JUDGE_MAX; k++){
		if(apw->a_game.voltage_total[k] >= VOLTAGE_POINT_FULL){
			apw->a_game.voltage_total[k] = 0;
		}
	}
#endif

	//A_TALKメッセージ
	nt->after_a_talk_tagpara.num = wp->personal[breeder_no].voltage_add_ap / VOLTAGE_ONE_POINT;
	if(voltage_addsub > 0){
	#if 0
		if(voltage_addsub == VOLTAGE_ONE_POINT){
			nt->a_talk_id = A_TALK_VOLTAGE_UP_1;
		}
		else{
			nt->a_talk_id = A_TALK_VOLTAGE_UP_2;
		}
	#else
		nt->a_talk_id = AT_A_TalkIDGet_VoltageUp(
			WT_WazaDataParaGet(wp->personal[breeder_no].wazano, ID_WTD_contype));
	#endif
		switch(wp->voltage_after[judge_no] / VOLTAGE_ONE_POINT){
		case 2:
//			nt->after_a_talk_id = A_TALK_VOLTAGE_STATE_UP_2;
			break;
		case 3:
//			nt->after_a_talk_id = A_TALK_VOLTAGE_STATE_UP_3;
			break;
		case 4:
			nt->after_a_talk_id = A_TALK_VOLTAGE_STATE_UP_4;
			break;
		case 5:
			nt->after_a_talk_id = A_TALK_VOLTAGE_STATE_UP_5;
			break;
		}
	}
	else if(voltage_addsub < 0){
//		nt->a_talk_id = A_TALK_VOLTAGE_SUB_1;
		nt->a_talk_id = AT_A_TalkIDGet_VoltageSub(WT_WazaDataParaGet(
			wp->personal[breeder_no].wazano, ID_WTD_contype));
		switch(wp->voltage_after[judge_no] / VOLTAGE_ONE_POINT){
		case 3:
//			nt->after_a_talk_id = A_TALK_VOLTAGE_STATE_SUB_3;
			break;
		case 2:
//			nt->after_a_talk_id = A_TALK_VOLTAGE_STATE_SUB_2;
			break;
		case 1:
//			nt->after_a_talk_id = A_TALK_VOLTAGE_STATE_SUB_1;
			break;
		case 0:
			if(wp->voltage_before[judge_no] != 0){
//				nt->after_a_talk_id = A_TALK_VOLTAGE_STATE_SUB_0;
			}
			break;
		}
	}

	wp->personal[breeder_no].app_total += wp->personal[breeder_no].voltage_add_ap;
}

//--------------------------------------------------------------
/**
 * @brief   審判被り計算
 *
 * @param   apw					演技力部門管理ワークへのポインタ
 * @param   wp					技効果パラメータへのポインタ
 * @param   nt					A_TALK用通常会話メッセージ代入先
 */
//--------------------------------------------------------------
void AWAZA_JudgeSuffer(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, NORMAL_TALK *nt)
{
	int add_ap;
	
	AWAZA_CalcInitUpdateParam(wp, now_breeder);
	add_ap = ACALC_JudgeSufferPointCheck(wp->personal[now_breeder].judge_suffer);
	wp->personal[now_breeder].app_total += add_ap;
//	if(wp->personal[now_breeder].judge_suffer == 0){
//		nt->after_a_talk_id = A_TALK_NO_JUDGE_SUFFER;
//	}
//	else{
//		nt->after_a_talk_id = A_TALK_JUDGE_SUFFER;
//	}
//	nt->after_a_talk_tagpara.num = add_ap / APPEAL_ICON_ONE_POINT;
	
	OS_TPrintf("ブリーダーNo%d, 審判被り人数＝%d, 取得ポイント＝%d\n", 
		now_breeder, wp->personal[now_breeder].judge_suffer, add_ap);
}

//--------------------------------------------------------------
/**
 * @brief   AWAZA_SAVEパラメータ更新処理
 * @param   wp		技効果パラメータへのポインタ
 */
//--------------------------------------------------------------
static void AWAZA_SaveParamUpdate(AWAZA_PARAM *wp)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		wp->save[i].waza_repeat = 0;
		wp->save[i].twice_now_apno = wp->personal[i].twice_next_apno;
	}
}


//==============================================================================
//	技効果シーケンス
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   次のターンでの順番が最初になる
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_NextFirst(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	u8 sort[BREEDER_MAX];
	int i, t, first_breeder;
	
	first_breeder = BREEDER_MAX;
	for(i = 0; i < BREEDER_MAX; i++){
		if(wp->personal[i].next_sort == AWK_SORT_NONE){
			sort[i] = 0xff;
		}
		else{
			if(wp->personal[i].next_sort == AWK_SORT_SPECIFY_FIRST 
					&& wp->personal[i].next_pos == 0){
				first_breeder = i;	//自分よりも先にこの技で次1番を発動していたブリーダー
			}
			sort[i] = wp->personal[i].next_pos;
		}
	}
	
	sort[kouka_breeder] = 0xff;	//自分の所は空白にしておく
	
	for(i = 0; i < BREEDER_MAX; i++){
		for(t = 0; t < BREEDER_MAX; t++){
			if(sort[t] != 0xff){
				if(i == sort[t] && sort[t] == wp->personal[t].next_pos){
					sort[t]++;
					break;
				}
			}
		}
		if(t == BREEDER_MAX){
			break;
		}
	}

	for(i = 0; i < BREEDER_MAX; i++){
		if(sort[i] != 0xff){
			wp->personal[i].next_pos = sort[i];
			OS_TPrintf("技効果の影響でブリーダー%dは次%d番\n", i, sort[i]);
		}
	}
	wp->personal[kouka_breeder].next_sort = AWK_SORT_SPECIFY_FIRST;
	wp->personal[kouka_breeder].next_pos = 0;
	OS_TPrintf("技効果によりブリーダー%dは次0番\n", kouka_breeder);
	
	if(first_breeder != BREEDER_MAX){
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_B, kouka_breeder, first_breeder, TAG_NULL, TAG_NULL);
	}
	else{
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);
	}
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   次のターンでの順番が最後になる
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_NextEnd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	s8 i, t;
	u8 sort[BREEDER_MAX];
	int before_end_breeder;
	
	before_end_breeder = BREEDER_MAX;
	for(i = 0; i < BREEDER_MAX; i++){
		if(wp->personal[i].next_sort == AWK_SORT_NONE){
			sort[i] = 0xff;
		}
		else{
			if(wp->personal[i].next_sort == AWK_SORT_SPECIFY_END
					&& wp->personal[i].next_pos == BREEDER_MAX - 1){
				before_end_breeder = i;	//自分よりも先にこの技で次最後を発動していたブリーダー
			}
			sort[i] = wp->personal[i].next_pos;
		}
	}

	sort[kouka_breeder] = 0xff;	//自分の所は空白にしておく

	for(i = BREEDER_MAX-1; i > -1; i--){
		for(t = 0; t < BREEDER_MAX; t++){
			if(sort[t] != 0xff){
				if(i == sort[t] && sort[t] == wp->personal[t].next_pos){
					sort[t]--;
					break;
				}
			}
		}
		if(t == BREEDER_MAX){
			break;
		}
	}

	for(i = 0; i < BREEDER_MAX; i++){
		if(sort[i] != 0xff){
			wp->personal[i].next_pos = sort[i];
			OS_TPrintf("技効果の影響でブリーダー%dは次%d番\n", i, sort[i]);
		}
	}
	wp->personal[kouka_breeder].next_sort = AWK_SORT_SPECIFY_END;
	wp->personal[kouka_breeder].next_pos = BREEDER_MAX - 1;
	OS_TPrintf("技効果によりブリーダー%dは次最後\n", kouka_breeder);

	if(before_end_breeder == BREEDER_MAX){
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);
	}
	else{
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_B, kouka_breeder, before_end_breeder, TAG_NULL, TAG_NULL);
	}

	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   審判の指名が被る毎に＋２
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_JudgeSufferAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int msg_type;
	
	wp->personal[kouka_breeder].my_effective_ap += 
		wp->personal[kouka_breeder].judge_suffer * KOUKA_JUDGE_SUFFER_ADD;
	
	switch(wp->personal[kouka_breeder].judge_suffer){
	case 0:
		msg_type = KOUKA_MSGID_A;
		break;
	case 1:
		msg_type = KOUKA_MSGID_B;
		break;
	case 2:
		msg_type = KOUKA_MSGID_C;
		break;
	default:
		msg_type = KOUKA_MSGID_D;
		break;
	}
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		msg_type, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);
	
	OS_TPrintf("審判の被り人数＝%d, 加算ポイント＝%d\n", wp->personal[kouka_breeder].judge_suffer,
		wp->personal[kouka_breeder].judge_suffer * APPEAL_ICON_ONE_POINT);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   盛り上がったら＋2
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_VoltageUpAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int judge_no;
	int voltage_addsub;
	
	judge_no = wp->personal[kouka_breeder].judge_no;
	voltage_addsub = ACALC_VoltageUpDownCheck(apw->consys->c_game.type, 
		wp->personal[kouka_breeder].wazano, judge_no, apw->consys->c_game.special_judge_no);
//	if(wp->voltage_before[judge_no] > wp->voltage_after[judge_no]){
	if(voltage_addsub > 0 && wp->personal[kouka_breeder].invalid_voltage_up == 0){
		wp->personal[kouka_breeder].my_effective_ap += KOUKA_VOLTAGE_UP_ADD;

		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, kouka_breeder, TAG_NULL, wp->personal[kouka_breeder].wazano, TAG_NULL);
		
		OS_TPrintf("盛り上がったので効果発生\n");
		return TRUE;
	}

	OS_TPrintf("盛り上がらなかったので失敗\n");
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   特殊効果なし
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_Null(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	OS_TPrintf("特殊効果何もなし\n");
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   審判の指名が被らなかったら＋3
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_NoneJudgeSufferAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	if(wp->personal[kouka_breeder].judge_suffer == 0){
		wp->personal[kouka_breeder].my_effective_ap += KOUKA_NONE_JUDGE_SUFFER_ADD;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);

		OS_TPrintf("指名が被らなかったので効果発生\n");
	}
	else{
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_B, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);
		
		OS_TPrintf("指名が被っているので失敗\n");
	}
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   2回連続使用可能
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_Continuation(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	if(wp->personal[kouka_breeder].wazano != apw->a_game.waza_history[kouka_breeder]){
		wp->save[kouka_breeder].waza_repeat = wp->personal[kouka_breeder].wazano;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);
		OS_TPrintf("次ターンも同じ技使用OK\n");
		return TRUE;
	}
	
	OS_TPrintf("既に連続で同じ技を出しているので連続技効果失敗\n");
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージ分の☆が追加
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_VoltageAddAP(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int judge_no, add_ap;
	
	judge_no = wp->personal[kouka_breeder].judge_no;
	if(1){	//ボルテージ0でもメッセージ出すようにした	wp->voltage_before[judge_no] > 0){
		add_ap = wp->voltage_before[judge_no];
		wp->personal[kouka_breeder].my_effective_ap += add_ap;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, add_ap / VOLTAGE_ONE_POINT);
//		OS_TPrintf("ボルテージ1以上なので効果発生\n");
		return TRUE;
	}

	OS_TPrintf("ボルテージ0なので失敗\n");
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   全員が被ったら☆が＋3
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_AllSufferAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	if(wp->personal[kouka_breeder].judge_suffer == BREEDER_MAX - 1){
		wp->personal[kouka_breeder].my_effective_ap += KOUKA_ALL_SUFFER_ADD;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);

		OS_TPrintf("全員の指名が被ったので効果発生\n");
	}
	else{
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_B, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);

		OS_TPrintf("全員分の指名が揃わなかったので失敗。被った人数(自分除く)＝%d\n", 
			wp->personal[kouka_breeder].judge_suffer);
	}
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   全員のボルテージが1つずつ減る
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_AllVoltageSub(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int judge_no;
	
	if(wp->personal[kouka_breeder].invalid_voltage_down == 1){
		OS_TPrintf("ボルテージ減少無効の効果発動中の為、失敗\n");
		return FALSE;
	}
	for(judge_no = 0; judge_no < JUDGE_MAX; judge_no++){
		if(wp->voltage_after[judge_no] != 0){
			break;
		}
	}
	if(judge_no == JUDGE_MAX){
		OS_TPrintf("審判全員のボルテージがないため、効果失敗\n");
		return FALSE;
	}
	
	wp->personal[kouka_breeder].voltage_all_down = 1;
	for(judge_no = 0; judge_no < JUDGE_MAX; judge_no++){
		if(wp->voltage_after[judge_no] > 0){
			wp->voltage_after[judge_no] += KOUKA_VOLTAGE_ALL_DOWN;
		}
	}
	
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, TAG_NULL);
	
	OS_TPrintf("審判全員のボルテージを下げる効果発生\n");
	return TRUE;
}

//--------------------------------------------------------------
/**
* @brief   次のターンで☆が2倍
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_NextTurnTwice(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	wp->personal[kouka_breeder].twice_next_apno = wp->personal[kouka_breeder].apno;
	OS_TPrintf("次のターン2倍フラグセット完了\n");
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージの増加が停止
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_VoltageUpStop(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int i;
	
	for(i = pos; i < BREEDER_MAX; i++){
		wp->personal[apw->a_game.breeder_sort[i]].invalid_voltage_up = 1;
		OS_TPrintf("%d番ブリーダーのボルテージ増加なし\n", apw->a_game.breeder_sort[i]);
	}
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, TAG_NULL);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   自分の前に演技したポケモンのボルテージがマックスになった時、ボルテージ分のみもらえる
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_FrontSame(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int front_breeder;
	
	if(pos == 0){
		OS_TPrintf("先頭の為、技失敗\n");
		return FALSE;
	}

	front_breeder = apw->a_game.breeder_sort[pos - 1];

	if(wp->personal[front_breeder].voltage_add_ap == 0){
		OS_TPrintf("前の人がボルテージポイントを取得していないので失敗\n");
		return FALSE;
	}
	
	wp->personal[kouka_breeder].my_effective_ap += wp->personal[front_breeder].voltage_add_ap;
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		KOUKA_MSGID_A, kouka_breeder, front_breeder, TAG_NULL, TAG_NULL);
	OS_TPrintf("ブリーダーNo%dの結果をコピーしました。加算AP＝%d\n", 
		front_breeder, wp->personal[kouka_breeder].my_effective_ap);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   次のターンで順番がランダム
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_NextRandom(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	s8 i, t;
	u8 sort[BREEDER_MAX];
	u8 brdno[BREEDER_MAX];
	u8 temp, temp2;
	
	for(i = 0; i < BREEDER_MAX; i++){
		sort[i] = i;
		brdno[i] = i;
	}

	for(i = 0; i < BREEDER_MAX; i++){
		temp = contest_rand(apw->consys) % (BREEDER_MAX - i);
		temp2 = temp;
		for(t = 0; t < BREEDER_MAX; t++){
			if(brdno[t] != 0xff){
				if(temp2 == 0){
					sort[t] = i;
					brdno[t] = 0xff;
					break;
				}
				else
					temp2--;
			}
		}
	}

	for(i = 0; i < BREEDER_MAX; i++){
		wp->personal[i].next_sort = AWK_SORT_RANDOM;
		wp->personal[i].next_pos = sort[i];
		OS_TPrintf("ブリーダー%dは、次%d番目\n", i, sort[i]);
	}
	
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, TAG_NULL);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   最後のアピールで星が2倍
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_EndTwice(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	if(pos == BREEDER_MAX - 1){
		//基本計算AP値を技効果増分として足しこむ
		wp->personal[kouka_breeder].my_effective_ap += wp->personal[kouka_breeder].app_total;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, 
			wp->personal[kouka_breeder].app_total / APPEAL_ICON_ONE_POINT);
		OS_TPrintf("2倍効果発動。基本計算AP値＝%d\n", 
			wp->personal[kouka_breeder].app_total / APPEAL_ICON_ONE_POINT);
		return TRUE;
	}
	
	OS_TPrintf("順番が最後ではない為、失敗。アピール順番＝%d\n", pos);
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージが低いほど☆がもらえる
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_VoltageLevelAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int voltage_level, judge_no;
	static const u8 VoltageAddData[] = {
		VOLTAGE_ONE_POINT * 4,
		VOLTAGE_ONE_POINT * 3,
		VOLTAGE_ONE_POINT * 2,
		VOLTAGE_ONE_POINT * 1,
		VOLTAGE_ONE_POINT * 0,
		VOLTAGE_ONE_POINT * 0,	//ボルテージ５の時(ありえないけど一応データは埋めとく)
	};
	
	judge_no = wp->personal[kouka_breeder].judge_no;
	voltage_level = wp->voltage_before[judge_no] / VOLTAGE_ONE_POINT;
	wp->personal[kouka_breeder].my_effective_ap += VoltageAddData[voltage_level];
	
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, 
		VoltageAddData[voltage_level] / VOLTAGE_ONE_POINT);
	
	OS_TPrintf("現在のボルテージ=%d, 加算AP=%d\n", voltage_level, VoltageAddData[voltage_level]);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   最初のアピールで星が＋２
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_FirstAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	if(pos == 0){
		wp->personal[kouka_breeder].my_effective_ap += APPEAL_ICON_ONE_POINT * 2;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, TAG_NULL);
		OS_TPrintf("最初のアピールなので効果発動。アピール順番＝%d\n", pos);
		return TRUE;
	}

	OS_TPrintf("最初ではないので、失敗。アピール順番＝%d\n", pos);
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   最後のアピールで星が＋２
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_EndAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	if(pos == BREEDER_MAX - 1){
		wp->personal[kouka_breeder].my_effective_ap += APPEAL_ICON_ONE_POINT * 2;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, TAG_NULL);
		OS_TPrintf("最後のアピールなので効果発動。アピール順番＝%d\n", pos);
		return TRUE;
	}

	OS_TPrintf("最後ではないので、失敗。アピール順番＝%d\n", pos);
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージの低下が停止
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_VoltageSubStop(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int i;
	
	for(i = pos; i < BREEDER_MAX; i++){
		wp->personal[apw->a_game.breeder_sort[i]].invalid_voltage_down = 1;
		OS_TPrintf("%d番ブリーダーのボルテージ減少なし\n", apw->a_game.breeder_sort[i]);
	}
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		KOUKA_MSGID_A, TAG_NULL, TAG_NULL, TAG_NULL, TAG_NULL);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ２匹続けてボルテージが上がると★が「+３」
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_ContinuationVoltageAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int front_breeder, my_up, front_up;
	
	if(pos == 0){
		OS_TPrintf("先頭の為、技失敗\n");
		return FALSE;
	}
	
	front_breeder = apw->a_game.breeder_sort[pos - 1];
	
	if(wp->personal[kouka_breeder].invalid_voltage_up != 0
			|| wp->personal[front_breeder].invalid_voltage_up != 0){
		OS_TPrintf("ボルテージ増加無効の為失敗\n");
		return FALSE;
	}
	
	my_up = ACALC_VoltageUpDownCheck(apw->consys->c_game.type, 
		wp->personal[kouka_breeder].wazano, wp->personal[kouka_breeder].judge_no, 
		apw->consys->c_game.special_judge_no);
	front_up = ACALC_VoltageUpDownCheck(apw->consys->c_game.type, 
		wp->personal[front_breeder].wazano, wp->personal[front_breeder].judge_no, 
		apw->consys->c_game.special_judge_no);
	
	if(front_up > 0 && my_up > 0){
		wp->personal[kouka_breeder].my_effective_ap += KOUKA_CONTINUATION_VOLTAGE_ADD;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, kouka_breeder, front_breeder, TAG_NULL, TAG_NULL);
		
		OS_TPrintf("連続ボルテージUPなので効果発動\n");
		return TRUE;
	}

	OS_TPrintf("連続UPしなかったので失敗\n");
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   何番目に演技するかで評価が変わる
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_SortAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int msg_type;
	
	wp->personal[kouka_breeder].my_effective_ap += Kouka_SortAddPoint[pos];
	switch(pos){
	case 0:
		msg_type = KOUKA_MSGID_A;
		break;
	case 1:
		msg_type = KOUKA_MSGID_B;
		break;
	case 2:
		msg_type = KOUKA_MSGID_C;
		break;
	case 3:
	default:
		msg_type = KOUKA_MSGID_D;
		break;
	}
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		msg_type, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);
	
	OS_TPrintf("順番＝%d, 加算ポイント＝%d\n", pos, Kouka_SortAddPoint[pos]);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージがマックスになった後使うと「+３」
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_VoltageMaxAfterAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int front_breeder;
	
	if(pos == 0){
		OS_TPrintf("先頭の為、技失敗\n");
		return FALSE;
	}
	
	front_breeder = apw->a_game.breeder_sort[pos - 1];
	if(wp->personal[front_breeder].voltage_add_ap >= VOLTAGE_FULL_ADD_AP
			|| wp->personal[front_breeder].voltage_add_ap >= VOLTAGE_FULL_ADD_AP_SPECIAL){
		wp->personal[kouka_breeder].my_effective_ap += KOUKA_VOLTAGE_MAX_AFTER_ADD;
		AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
			KOUKA_MSGID_A, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);
		
		OS_TPrintf("直前がボルテージMaxだったので効果発生\n");
		return TRUE;
	}
	OS_TPrintf("直前はボルテージMaxではなかったので失敗\n");
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   自分が一番評価が低いと★が「+３」
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   wp				技効果パラメータ代入先のポインタ
 * @param   appeal_breeder	アピール中のブリーダー番号
 * @param   kouka_breeder	この技効果を発動しているブリーダーの番号
 * @param   pos				何番目のアピールか(appeal_breederが)
 *
 * @retval  TRUE:効果発生。　FALSE:効果不発
 */
//--------------------------------------------------------------
static int Kouka_LowPointAdd(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int appeal_breeder, int kouka_breeder, int pos)
{
	int i;
	
	OS_TPrintf("kouka_breeder %d = %d\n", kouka_breeder, wp->personal[kouka_breeder].app_total_timing_before);
	for(i = 0; i < BREEDER_MAX; i++){
		if(i == kouka_breeder){
			continue;
		}
		OS_TPrintf("app_total_timing_before breeder %d = %d\n", i, wp->personal[i].app_total_timing_before);
		if(wp->personal[i].app_total_before < wp->personal[kouka_breeder].app_total_timing_before){
			break;
		}
	}
	if(i != BREEDER_MAX){
		OS_TPrintf("ブリーダーNo%dの方が点数が低いので失敗\n", i);
		return FALSE;
	}
	
	wp->personal[kouka_breeder].my_effective_ap += KOUKA_LOW_POINT_ADD;
	AWAZA_MsgParamSet(&wp->personal[kouka_breeder], wp->personal[kouka_breeder].apno, 
		KOUKA_MSGID_A, kouka_breeder, TAG_NULL, TAG_NULL, TAG_NULL);
	
	OS_TPrintf("一番ポイントが低いので効果発生\n");
	return TRUE;
}

