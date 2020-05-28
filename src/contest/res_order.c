//==============================================================================
/**
 * @file	res_order.c
 * @brief	コンテスト結果発表画面：命令送受信
 * @author	matsuda
 * @date	2006.03.17(金)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "battle/battle_common.h"
#include "contest_order.h"
#include "con_result.h"
#include "res_order.h"

#include "res_tcb_pri.h"
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
#include "system/wipe.h"

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "res_tool.h"
#include "res_id.h"
#include "res_tcb_pri.h"
#include "poketool/poke_tool.h"
#include "gflib/touchpanel.h"
#include "system/snd_tool.h"
#include "system/window.h"
#include "contest_snd_def.h"

#include "communication/communication.h"
#include "comm_command_contest.h"


//==============================================================================
//	定数定義
//==============================================================================
///どんちょうアニメウェイト
#define DONCHOU_ANM_WAIT		(1)
///どんちょうを1段分アニメ終了する毎にもうけるアニメウェイト
#define DONCHOU_DANSA_ANM_WAIT		(0)
///どんちょうのアニメ転送用のキャラクタが横に何キャラ入っているか
#define DONCHOU_ANM_DATA_X_LEN	(8)
///どんちょうのアニメ転送用のキャラクタが縦に何キャラ入っているか
#define DONCHOU_ANM_DATA_Y_LEN	(4)

///順位発表の時の１つ１つの発表の間のウェイト
#define RANKING_ANNOUNCE_WAIT	(30)

///登場してから、退場を開始するまでのウェイト
#define VICTORY_LEAVE_WAIT		(60)

///ドラムロールを鳴らし始めてから、実際にメーターを動かし始めるまでのウェイト
#define DORAM_ROLL_WAIT			(45)
///メーター上昇時、1ドット上昇毎に入れるウェイト
#define METER_ADD_WAIT			(1)

///結果発表画面フェードアウト：フェードウェイト
#define RESULT_FADEOUT_FRAME		(90)
///結果発表画面フェードアウト：フェードアウトし終わった後の待ち時間
#define RESULT_FADEOUT_FINISH_WAIT	(60)


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static int Request_Sample(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_Sample(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void Answer_Sample(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *answer_head, CO_ANSDAT *ansdat, int net_id);
static int Request_DonchouUp(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_DonchouUp(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void ROTCB_DonchouUp(TCB_PTR tcb, void *work);
static int Request_DonchouDown(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_DonchouDown(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void ROTCB_DonchouDown(TCB_PTR tcb, void *work);
static int Request_ConresExit(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_ConresExit(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static int Request_Talk(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_Talk(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void ROTCB_TalkPut(TCB_PTR tcb, void *work);
static int Request_ResultChange(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_ResultChange(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void ROTCB_ResultChange(TCB_PTR tcb, void *work);
static int Request_VictoryAppear(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_VictoryAppear(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void ROTCB_VictoryAppear(TCB_PTR tcb, void *work);
static int Request_RankingAnnounce(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_RankingAnnounce(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void ROTCB_RankingAnnounce(TCB_PTR tcb, void *work);
static int Request_GameParamUpdate(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_GameParamUpdate(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static int Request_MeterUpdate(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_MeterUpdate(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void ROTCB_MeterUpdate(TCB_PTR tcb, void *work);
static int Request_ResultFadeOut(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_ResultFadeOut(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void ROTCB_ResultFadeOut(TCB_PTR tcb, void *work);


//==============================================================================
//	データ
//==============================================================================
///命令送受信用関数ポインタ構造体テーブル	※ここに追加したら必ず.hのenumにも追加する事!!
static const CON_ORDER_FUNC OrderFuncTbl[] = {
	{//RORDER_NO_SAMPLE		サンプル
		Request_Sample, 
		Recieve_Sample, 
		Answer_Sample, 
	},
	{//RORDER_NO_GAMEPARAM_UPDATE
		Request_GameParamUpdate, 
		Recieve_GameParamUpdate, 
		NULL, 
	},
	{//RORDER_NO_DONCHOU_UP
		Request_DonchouUp, 
		Recieve_DonchouUp, 
		NULL, 
	},
	{//RORDER_NO_DONCHOU_DOWN
		Request_DonchouDown, 
		Recieve_DonchouDown, 
		NULL, 
	},
	{//RORDER_NO_CONRES_EXIT
		Request_ConresExit,
		Recieve_ConresExit,
		NULL,
	},
	{//RORDER_NO_TALK
		Request_Talk, 
		Recieve_Talk, 
		NULL, 
	},
	{//RORDER_NO_RESULT_CHANGE
		Request_ResultChange, 
		Recieve_ResultChange, 
		NULL, 
	},
	{//RORDER_NO_RANKING_ANNOUNCE
		Request_RankingAnnounce, 
		Recieve_RankingAnnounce, 
		NULL, 
	},
	{//RORDER_NO_VICTORY_APPEAR,
		Request_VictoryAppear, 
		Recieve_VictoryAppear, 
		NULL, 
	},
	{//RORDER_NO_METER_UPDATE
		Request_MeterUpdate, 
		Recieve_MeterUpdate, 
		NULL, 
	},
	{//RORDER_NO_RESULT_FADEOUT
		Request_ResultFadeOut,
		Recieve_ResultFadeOut,
		NULL,
	},
};


//--------------------------------------------------------------
//	
//--------------------------------------------------------------
//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///どんちょうアニメのスクリーン書き換えベース位置
ALIGN4 static const s8 DonchouAnmLineData[] = {
	15, 11, 7, 3, -1
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
 * @brief   ダンス部門：コンテスト送受信ワーク初期化
 * @param   rpw		結果発表管理ワークへのポインタ
 */
//--------------------------------------------------------------
void ConresOrder_WorkInit(CONRES_PROC_WORK *rpw)
{
	CO_INIT_DATA initdata;
	
	initdata.func_tbl = OrderFuncTbl;
	initdata.func_tbl_max = NELEMS(OrderFuncTbl);
	initdata.my_breeder_no = rpw->consys->c_game.my_breeder_no;
	initdata.server_no = rpw->consys->c_game.server_no;
	initdata.sio_flag = rpw->consys->sio_flag;
	
	CO_WorkInit(&rpw->cow, &initdata);
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：サンプル
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_Sample(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	CONRES_PROC_WORK *rpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, NULL, 0);
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：サンプル
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_Sample(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	CONRES_PROC_WORK *rpw = syswork;
	
	//返事を返す	バッファは特に渡すものがないのでNULL指定
	CO_ANSWER_TransmitBufferSet(cow, req_head, NULL, 0);
}

//--------------------------------------------------------------
/**
 * @brief   返事受信(送信元)：サンプル
 *
 * @param   rpw				結果発表管理ワークへのポインタ
 * @param   answer_head		返事ヘッダのポインタ
 * @param   ansdat			受信データへのポインタ
 * @param   net_id			返事送信者のネットID
 */
//--------------------------------------------------------------
static void Answer_Sample(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *answer_head, CO_ANSDAT *ansdat, int net_id)
{
	CONRES_PROC_WORK *rpw = syswork;
	
	//返事を受け取るだけなので特にする事がない
	return;
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：ゲームパラメータ更新
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_GameParamUpdate(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	CONRES_PROC_WORK *rpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, work, sizeof(CONRES_GAME_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：ゲームパラメータ更新
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_GameParamUpdate(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	CONRES_PROC_WORK *rpw = syswork;
	CONRES_GAME_PARAM *r_game = data;
	int i;
	
	rpw->r_game = *r_game;
	for(i = 0; i < BREEDER_MAX; i++){
		rpw->consys->c_game.score[i] = r_game->score[i];
	}
	
	//返事を返す	バッファは特に渡すものがないのでNULL指定
	CO_ANSWER_TransmitBufferSet(cow, req_head, NULL, 0);
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：どんちょう上げる
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_DonchouUp(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	CONRES_PROC_WORK *rpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, NULL, 0);
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：どんちょう上げる
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_DonchouUp(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	CONRES_PROC_WORK *rpw = syswork;
	ROLOCAL_DONCHOU_UP *du;
	
	du = sys_AllocMemory(HEAPID_CONRES, sizeof(ROLOCAL_DONCHOU_UP));
	MI_CpuClear8(du, sizeof(ROLOCAL_DONCHOU_UP));

	du->rpw = rpw;
	du->req_head = *req_head;
	du->cow = cow;
	
	TCB_Add(ROTCB_DonchouUp, du, TCBPRI_CONRES_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   どんちょうを上げる
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		ROLOCAL_DONCHOU_UP構造体
 */
//--------------------------------------------------------------
static void ROTCB_DonchouUp(TCB_PTR tcb, void *work)
{
	ROLOCAL_DONCHOU_UP *du = work;
	
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
			
			scrn_buf = GF_BGL_ScreenAdrsGet(du->rpw->sys.bgl, CONRES_FRAME_EFF);
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
			
			GF_BGL_LoadScreenV_Req(du->rpw->sys.bgl, CONRES_FRAME_EFF);
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
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_DonchouDown(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	CONRES_PROC_WORK *rpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, NULL, 0);
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：どんちょう下げる
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_DonchouDown(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	CONRES_PROC_WORK *rpw = syswork;
	ROLOCAL_DONCHOU_DOWN *dd;
	
	dd = sys_AllocMemory(HEAPID_CONRES, sizeof(ROLOCAL_DONCHOU_DOWN));
	MI_CpuClear8(dd, sizeof(ROLOCAL_DONCHOU_DOWN));

	dd->rpw = rpw;
	dd->req_head = *req_head;
	dd->cow = cow;
	
	TCB_Add(ROTCB_DonchouDown, dd, TCBPRI_CONRES_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   どんちょうを下げる
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		ROLOCAL_DONCHOU_DOWN構造体
 */
//--------------------------------------------------------------
static void ROTCB_DonchouDown(TCB_PTR tcb, void *work)
{
	ROLOCAL_DONCHOU_DOWN *dd = work;
	
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
			
			scrn_buf = GF_BGL_ScreenAdrsGet(dd->rpw->sys.bgl, CONRES_FRAME_EFF);
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
			
			GF_BGL_LoadScreenV_Req(dd->rpw->sys.bgl, CONRES_FRAME_EFF);
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
 * @brief   命令送信(送信元)：ダンス部門終了
 *
 * @param   vpw			演技力部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_ConresExit(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	CONRES_PROC_WORK *rpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, NULL, 0);
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：ダンス部門終了
 *
 * @param   rpw			演技力部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_ConresExit(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	CONRES_PROC_WORK *rpw = syswork;

	rpw->main_end = TRUE;
	
	//返事を返す	バッファは特に渡すものがないのでNULL指定
	CO_ANSWER_TransmitBufferSet(cow, req_head, NULL, 0);
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：会話メッセージの表示
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_Talk(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	CONRES_PROC_WORK *rpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(CONRES_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：会話メッセージの表示
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_Talk(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	CONRES_PROC_WORK *rpw = syswork;
	CONRES_ADVANCE_PARAM *dap = data;
	ROLOCAL_TALK_PUT *talk;
	
	talk = sys_AllocMemory(HEAPID_CONRES, sizeof(ROLOCAL_TALK_PUT));
	MI_CpuClear8(talk, sizeof(ROLOCAL_TALK_PUT));
	
	talk->rpw = rpw;
	talk->req_head = *req_head;
	talk->cow = cow;
	talk->breeder_no = dap->now_breeder;
	
	talk->a_talk_tagpara = dap->a_talk_tagpara;
	talk->a_talk_id = dap->a_talk_id;
	talk->a_talk_bmpwin_not_open = dap->a_talk_bmpwin_not_open;
	talk->a_talk_bmpwin_not_close = dap->a_talk_bmpwin_not_close;
	talk->a_talk_bmpwin_close_wait = dap->a_talk_bmpwin_close_wait;
	
	TCB_Add(ROTCB_TalkPut, talk, TCBPRI_CONRES_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   会話メッセージの表示
 * @param   tcb			TCBへのポインタ
 * @param   work		ROLOCAL_TALK_PUT構造体
 */
//--------------------------------------------------------------
static void ROTCB_TalkPut(TCB_PTR tcb, void *work)
{
	ROLOCAL_TALK_PUT *talk = work;
	
	switch(talk->seq){
	case 0:
		if(talk->a_talk_id != A_TALK_CONRES_NULL){
			if(talk->a_talk_bmpwin_not_open == FALSE){
				BmpTalkWinWrite(&talk->rpw->sys.win[CONRES_BMPWIN_TALK], WINDOW_TRANS_OFF,
					CONRES_TALKWIN_CGX_OFFSET, CONRES_TALKWIN_PALNO);
				GF_BGL_LoadScreenV_Req(talk->rpw->sys.bgl, CONRES_FRAME_WIN);
			}
			RT_A_TalkMessageSet(talk->rpw, talk->a_talk_id, &talk->a_talk_tagpara);
			talk->seq++;
		}
		else{
			talk->seq = 100;
		}
		break;
	case 1:
		if(RT_TalkMessageEndCheck(talk->rpw) == 0){
			talk->seq++;
		}
		break;
	case 2:
		talk->close_wait++;
		if(talk->a_talk_bmpwin_not_close == TRUE){
			talk->seq++;
		}
		else if(talk->close_wait >= talk->a_talk_bmpwin_close_wait){
			BmpTalkWinClear(&talk->rpw->sys.win[CONRES_BMPWIN_TALK], WINDOW_TRANS_OFF);
			GF_BGL_LoadScreenV_Req(talk->rpw->sys.bgl, CONRES_FRAME_WIN);
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
 * @brief   命令送信(送信元)：結果発表画面に切り替える
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_ResultChange(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	CONRES_PROC_WORK *rpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, work, sizeof(CONRES_GAME_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：結果発表画面に切り替える
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_ResultChange(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	CONRES_PROC_WORK *rpw = syswork;
	ROLOCAL_RESULT_CHANGE *rrc;
	
	rpw->r_game = *((CONRES_GAME_PARAM *)data);
	
	rrc = sys_AllocMemory(HEAPID_CONRES, sizeof(ROLOCAL_RESULT_CHANGE));
	MI_CpuClear8(rrc, sizeof(ROLOCAL_RESULT_CHANGE));
	
	rrc->rpw = rpw;
	rrc->req_head = *req_head;
	rrc->cow = cow;

	TCB_Add(ROTCB_ResultChange, rrc, TCBPRI_CONRES_RESULT_CHANGE);
}

//--------------------------------------------------------------
/**
 * @brief   披露画面から結果発表画面に切り替え
 * @param   tcb			TCBへのポインタ
 * @param   work		ROLOCAL_RESULT_CHANGE構造体
 */
//--------------------------------------------------------------
static void ROTCB_ResultChange(TCB_PTR tcb, void *work)
{
	ROLOCAL_RESULT_CHANGE *rrc = work;
	enum{
		SEQ_INIT,
		SEQ_INIT_WAIT,
		SEQ_FADE_OUT,
		SEQ_FADE_OUT_WAIT,
		SEQ_DEFAULT_SET,
		SEQ_FADE_IN,
		SEQ_FADE_IN_WAIT,
	};
	
	switch(rrc->seq){
	case SEQ_INIT:
		ADV_FlashEffectTaskDel(rrc->rpw->flash_eff);
		rrc->seq++;
		break;
	case SEQ_INIT_WAIT:
		if(ADV_FlashEffectCheck() == TRUE){
			rrc->seq++;
		}
		break;
	case SEQ_FADE_OUT:
		WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, 
				WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_CONRES);
		Snd_BgmStop(SEQ_CON_TEST, 30);
		rrc->seq++;
		break;
	case SEQ_FADE_OUT_WAIT:
		if(WIPE_SYS_EndCheck() == TRUE){
			rrc->seq++;
		}
		break;
	case SEQ_DEFAULT_SET:
		RT_Announce_BGDel(rrc->rpw);
		RT_Announce_OBJDel(rrc->rpw);
		
		RT_Result_BGSet(rrc->rpw);
		RT_Result_OBJSet(rrc->rpw);
		
		RT_Result_BGSet_Sub(rrc->rpw);

		//ウィンドウ枠描画
		BmpTalkWinWrite(&rrc->rpw->sys.win[CONRES_BMPWIN_TALK], WINDOW_TRANS_ON,
			CONRES_TALKWIN_CGX_OFFSET, CONRES_TALKWIN_PALNO);
		
		GF_BGL_BmpWinDataFill(&rrc->rpw->sys.win[CONRES_BMPWIN_TALK], 0xff);
		GF_BGL_BmpWinOn(&rrc->rpw->sys.win[CONRES_BMPWIN_TALK]);

		//ソフトウェアスプライト非表示
		{
			int i;
			for(i = 0; i < BREEDER_MAX; i++){
				SoftSpriteParaSet(rrc->rpw->sys.ss[i], SS_PARA_VANISH, TRUE);
			}
		}
		
		rrc->rpw->disp_mode = RESDISP_MODE_RESULT;
		rrc->seq++;
		break;
	case SEQ_FADE_IN:
		if(Snd_FadeCheck() == 0){
			WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_CONRES);
			rrc->seq++;
		}
		break;
	case SEQ_FADE_IN_WAIT:
		if(WIPE_SYS_EndCheck() == TRUE){
			Snd_BgmPlay(SEQ_CO_KEKKA);
			rrc->seq++;
		}
		break;
	
	default:
		CO_ANSWER_TransmitBufferSet(rrc->cow, &rrc->req_head, NULL, 0);

		sys_FreeMemoryEz(rrc);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：順位発表
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_RankingAnnounce(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	CONRES_PROC_WORK *rpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(CONRES_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：順位発表
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_RankingAnnounce(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	CONRES_PROC_WORK *rpw = syswork;
	CONRES_ADVANCE_PARAM *dap = data;
	ROLOCAL_RANKING_ANNOUNCE *ra;
	int i;
	
	ra = sys_AllocMemory(HEAPID_CONRES, sizeof(ROLOCAL_RANKING_ANNOUNCE));
	MI_CpuClear8(ra, sizeof(ROLOCAL_RANKING_ANNOUNCE));
	
	ra->rpw = rpw;
	ra->req_head = *req_head;
	ra->cow = cow;
	for(i = 0; i < BREEDER_MAX; i++){
		ra->ranking[i] = dap->ranking[i];
	}
	
	TCB_Add(ROTCB_RankingAnnounce, ra, TCBPRI_CONRES_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   順位発表
 * @param   tcb			TCBへのポインタ
 * @param   work		ROLOCAL_RANKING_ANNOUNCE構造体
 */
//--------------------------------------------------------------
static void ROTCB_RankingAnnounce(TCB_PTR tcb, void *work)
{
	ROLOCAL_RANKING_ANNOUNCE *ra = work;
	enum{
		SEQ_INIT,
		SEQ_ANNOUNCE,
		SEQ_WAIT,
		SEQ_NEXT,
		SEQ_END,
	};
	
	switch(ra->seq){
	case SEQ_INIT:
		ra->seq++;
		break;
	case SEQ_ANNOUNCE:
		RT_RankingIconAppearSet(ra->rpw, 
			ra->ranking[BREEDER_MAX-1 - ra->end_count], BREEDER_MAX-1 - ra->end_count);
		ra->end_count++;
		ra->seq++;
		break;
	case SEQ_WAIT:
		ra->wait++;
		if(ra->wait > RANKING_ANNOUNCE_WAIT){
			ra->wait = 0;
			ra->seq++;
		}
		break;
	case SEQ_NEXT:
		if(ra->end_count < BREEDER_MAX){
			ra->seq = SEQ_ANNOUNCE;
		}
		else{
			ra->seq++;
		}
		break;
	case SEQ_END:
	default:
		CO_ANSWER_TransmitBufferSet(ra->cow, &ra->req_head, NULL, 0);

		sys_FreeMemoryEz(ra);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：優勝したポケモンの登場演出
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_VictoryAppear(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	CONRES_PROC_WORK *rpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(CONRES_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：優勝したポケモンの登場演出
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_VictoryAppear(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	CONRES_PROC_WORK *rpw = syswork;
	CONRES_ADVANCE_PARAM *dap = data;
	ROLOCAL_VICTORY_EFF *ve;
	
	ve = sys_AllocMemory(HEAPID_CONRES, sizeof(ROLOCAL_VICTORY_EFF));
	MI_CpuClear8(ve, sizeof(ROLOCAL_VICTORY_EFF));
	
	ve->rpw = rpw;
	ve->req_head = *req_head;
	ve->cow = cow;
	ve->victory_breeder = dap->victory_breeder;
	
	TCB_Add(ROTCB_VictoryAppear, ve, TCBPRI_CONRES_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   優勝したポケモンの登場演出
 * @param   tcb			TCBへのポインタ
 * @param   work		ROLOCAL_VICTORY_EFF構造体
 */
//--------------------------------------------------------------
static void ROTCB_VictoryAppear(TCB_PTR tcb, void *work)
{
	ROLOCAL_VICTORY_EFF *ve = work;
	enum{
		SEQ_WND_OPEN,
		SEQ_WND_OPEN_WAIT,
		SEQ_POKE_APPEAR,
		SEQ_POKE_APPEAR_WAIT,
		SEQ_POKE_VOICE,
		SEQ_POKE_VOICE_WAIT,
		SEQ_WAIT,
	#if 0		//ひっこめないようになった 2006.05.17(水)
		SEQ_POKE_LEAVE,
		SEQ_POKE_LEAVE_WAIT,
		SEQ_WND_CLOSE,
		SEQ_WND_CLOSE_WAIT,
	#endif
	};
	
	switch(ve->seq){
	case SEQ_WND_OPEN:
		RT_ConfettiCreateTaskSet(ve->rpw);
		RT_WndOpenEffStart(ve->rpw, RT_WNDEFF_OPEN, &ve->wnd_end_flag);
		
		Snd_BgmPlay(SEQ_CO_FANFA);
		Snd_SePlay(RSE_AUDIENCE);
		ve->seq++;
		break;
	case SEQ_WND_OPEN_WAIT:
		if(ve->wnd_end_flag == TRUE){
			ve->seq++;
		}
		break;
	case SEQ_POKE_APPEAR:
		PokeSlideEffectStart(ve->rpw, ve->victory_breeder, RT_POKESLIDE_IN, &ve->poke_end_flag);
		ve->seq++;
		break;
	case SEQ_POKE_APPEAR_WAIT:
		if(ve->poke_end_flag == TRUE){
			ve->seq++;
		}
		break;
	case SEQ_POKE_VOICE:
		{
			int monsno;
			monsno = PokeParaGet(ve->rpw->sys.c_game->pp[ve->victory_breeder],
				ID_PARA_monsno, NULL);
			PokeVoicePlaySet(ve->rpw->consys->perap_voice[ve->victory_breeder],
				PV_NORMAL, monsno, 0, CONTEST_PMVOICE_VOLUME, NULL, HEAPID_CONRES);
		}
		ve->seq++;
		break;
	case SEQ_POKE_VOICE_WAIT:
		if(Snd_PMVoicePlayCheck() == 0){
			ve->seq++;
		}
		break;
	case SEQ_WAIT:
		ve->wait++;
		if(ve->wait > VICTORY_LEAVE_WAIT){
			ve->wait = 0;
			ve->seq++;
		}
		break;
#if 0
	case SEQ_POKE_LEAVE:
		PokeSlideEffectStart(ve->rpw, ve->victory_breeder, RT_POKESLIDE_OUT, &ve->poke_end_flag);
		ve->seq++;
		break;
	case SEQ_POKE_LEAVE_WAIT:
		if(ve->poke_end_flag == TRUE){
			ve->seq++;
		}
		break;
	case SEQ_WND_CLOSE:
		RT_WndOpenEffStart(ve->rpw, RT_WNDEFF_CLOSE, &ve->wnd_end_flag);
		ve->seq++;
		break;
	case SEQ_WND_CLOSE_WAIT:
		if(ve->wnd_end_flag == TRUE){
			RT_ConfettiEndFlagSet(ve->rpw);
			ve->seq++;
		}
		break;
#endif
	default:
		CO_ANSWER_TransmitBufferSet(ve->cow, &ve->req_head, NULL, 0);

		sys_FreeMemoryEz(ve);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：メーターを伸ばす
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_MeterUpdate(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	CONRES_PROC_WORK *rpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(CONRES_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：メーターを伸ばす
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_MeterUpdate(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	CONRES_PROC_WORK *rpw = syswork;
	CONRES_ADVANCE_PARAM *dap = data;
	ROLOCAL_METER *me;
	int i;
	
	me = sys_AllocMemory(HEAPID_CONRES, sizeof(ROLOCAL_METER));
	MI_CpuClear8(me, sizeof(ROLOCAL_METER));
	
	me->rpw = rpw;
	me->req_head = *req_head;
	me->cow = cow;
	me->meter_type = dap->meter_type;
	
	switch(dap->meter_type){
	case CONGAME_VISUAL:
		for(i = 0; i < BREEDER_MAX; i++){
			me->max_meter_dot[i] = rpw->r_game.visual_dot[i];
		}
		break;
	case CONGAME_DANCE:
		for(i = 0; i < BREEDER_MAX; i++){
			me->max_meter_dot[i] = rpw->r_game.dance_dot[i];
		}
		break;
	case CONGAME_ACTIN:
		for(i = 0; i < BREEDER_MAX; i++){
			me->max_meter_dot[i] = rpw->r_game.actin_dot[i];
		}
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	
	TCB_Add(ROTCB_MeterUpdate, me, TCBPRI_CONRES_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   メーターを伸ばす
 * @param   tcb			TCBへのポインタ
 * @param   work		ROLOCAL_METER構造体
 */
//--------------------------------------------------------------
static void ROTCB_MeterUpdate(TCB_PTR tcb, void *work)
{
	ROLOCAL_METER *me = work;
	int i, end_count, breeder_no;
	enum{
		SEQ_INIT,
		SEQ_WAIT,
		SEQ_METER_INIT,
		SEQ_METER_ADD,
		SEQ_METER_END,
		SEQ_END,
	};
	
	switch(me->seq){
	case SEQ_INIT:
		Snd_SePlay(RSE_DORAM_ROLL);
		me->seq++;
		break;
	case SEQ_WAIT:
		me->wait++;
		if(me->wait > DORAM_ROLL_WAIT){
			me->wait = 0;
			me->seq++;
		}
		break;
	case SEQ_METER_INIT:
		for(i = 0; i < BREEDER_MAX; i++){
			if(me->max_meter_dot[i] > 0){
				Snd_SePlay(RSE_METER_UP);	//どれか1つでも上がるメーターがあるならSE鳴らす
				break;
			}
		}
		me->seq++;
		//break;
	case SEQ_METER_ADD:
		me->wait++;
		if(me->wait < METER_ADD_WAIT){
			break;
		}
		me->wait = 0;
		
		end_count = 0;
		for(i = 0; i < BREEDER_MAX; i++){
			breeder_no = me->rpw->r_game.breeder_sort[i];
			me->now_dot[breeder_no]++;
			if(me->now_dot[breeder_no] <= me->max_meter_dot[breeder_no]){
				RT_MeterActorDotCreate(me->rpw, breeder_no, 
					me->meter_type, me->now_dot[breeder_no], i);
			}
			else{
				end_count++;
			}
		}
		if(end_count >= BREEDER_MAX){
			me->seq++;
		}
		break;
	case SEQ_METER_END:
		for(i = 0; i < BREEDER_MAX; i++){
			if(me->max_meter_dot[i] > 0){
				Snd_SePlay(RSE_METER_STOP);	//どれか1つでも上がるメーターがあるならSE鳴らす
				break;
			}
		}
		Snd_SeStopBySeqNo(RSE_DORAM_ROLL, 0);
		me->seq++;
		break;
		
	case SEQ_END:
	default:
		CO_ANSWER_TransmitBufferSet(me->cow, &me->req_head, NULL, 0);

		sys_FreeMemoryEz(me);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：結果発表画面フェードアウト
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_ResultFadeOut(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	CONRES_PROC_WORK *rpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, NULL, 0);
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：結果発表画面フェードアウト
 *
 * @param   rpw			結果発表管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_ResultFadeOut(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	CONRES_PROC_WORK *rpw = syswork;
	ROLOCAL_FADEOUT *fo;
	
	fo = sys_AllocMemory(HEAPID_CONRES, sizeof(ROLOCAL_FADEOUT));
	MI_CpuClear8(fo, sizeof(ROLOCAL_FADEOUT));
	
	fo->rpw = rpw;
	fo->req_head = *req_head;
	fo->cow = cow;
	
	TCB_Add(ROTCB_ResultFadeOut, fo, TCBPRI_CONRES_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   結果発表画面フェードアウト
 * @param   tcb			TCBへのポインタ
 * @param   work		ROLOCAL_FADEOUT構造体
 */
//--------------------------------------------------------------
static void ROTCB_ResultFadeOut(TCB_PTR tcb, void *work)
{
	ROLOCAL_FADEOUT *fo = work;
	
	switch(fo->seq){
	case 0:
		ChangeBrightnessRequest(RESULT_FADEOUT_FRAME, BRIGHTNESS_WHITE, BRIGHTNESS_NORMAL,
			PLANEMASK_ALL, MASK_DOUBLE_DISPLAY);
		Snd_BgmStop(SEQ_CO_FANFA, RESULT_FADEOUT_FRAME);
		fo->seq++;
		break;
	case 1:
		if(IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) == TRUE
				&& Snd_FadeCheck() == 0){
			
			//紙ふぶき削除
			RT_ConfettiEndFlagSet(fo->rpw);
			
			//色を全て真っ白にしておく(画面が見えないように)
		#if 0
			PaletteWork_Clear(fo->rpw->sys.pfd, FADE_MAIN_BG, FADEBUF_ALL, 0x0000, 0, 16*16);
			PaletteWork_Clear(fo->rpw->sys.pfd, FADE_MAIN_OBJ, FADEBUF_ALL, 0x0000, 0, 
				CONTEST_MAIN_OBJPAL_COLOR_NUM);
			PaletteWork_Clear(fo->rpw->sys.pfd, FADE_SUB_BG, FADEBUF_ALL, 0x0000, 0, 16*16);
			PaletteWork_Clear(fo->rpw->sys.pfd, FADE_SUB_OBJ, FADEBUF_ALL, 0x0000, 0, 16*16);
		#else
			GX_SetMasterBrightness(16);
			GXS_SetMasterBrightness(16);
		#endif
			fo->seq++;
		}
		break;
	case 2:
		fo->wait++;
		if(fo->wait > RESULT_FADEOUT_FINISH_WAIT){
			fo->wait = 0;
			fo->seq++;
		}
		break;
	default:
		CO_ANSWER_TransmitBufferSet(fo->cow, &fo->req_head, NULL, 0);

		sys_FreeMemoryEz(fo);
		TCB_Delete(tcb);
		return;
	}
}
