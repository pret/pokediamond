//==============================================================================
/**
 * @file	dance_order.c
 * @brief	ダンス部門：命令送受信
 * @author	matsuda
 * @date	2005.12.13(火)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "battle/battle_common.h"
#include "contest_order.h"
#include "dance.h"
#include "dance_order.h"

#include "dance_tcb_pri.h"
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

#include "dance_tool.h"
#include "poketool/poke_tool.h"
#include "gflib/touchpanel.h"
#include "system/snd_tool.h"
#include "dance_input.h"
#include "system/window.h"

#include "communication/communication.h"
#include "comm_command_contest.h"


#ifdef PM_DEBUG
extern u8 DmatsuWork_DanceRotationOff;
#endif

//==============================================================================
//	定数定義
//==============================================================================
///ローテーションの移動にかけるフレーム数
#define ROTATION_SPEED_NORMAL		(90)
///ローテーションの移動に、rotation_frameの何%のフレーム数で移動を終えるようにするか
///(100だとrotation_frameのフレーム数きっちりでローテーションを終える
#define ROTATION_FRAME_PERCENT		(40)	//(50)	//(70)

///どんちょうの上昇速度(下位8ビット小数)
#define DONCHOU_UP_SPEED			(3 << 8)
///どんちょうがこれだけスクロールしたら停止させる(下位8ビット小数)
#define DONCHOU_STOP_SCROLL			(200 << 8)

///どんちょうアニメウェイト
#define DONCHOU_ANM_WAIT		(1)
///どんちょうを1段分アニメ終了する毎にもうけるアニメウェイト
#define DONCHOU_DANSA_ANM_WAIT		(0)
///どんちょうのアニメ転送用のキャラクタが横に何キャラ入っているか
#define DONCHOU_ANM_DATA_X_LEN	(8)
///どんちょうのアニメ転送用のキャラクタが縦に何キャラ入っているか
#define DONCHOU_ANM_DATA_Y_LEN	(4)

///メインテーマ曲を停止する時のフェードアウトにかけるフレーム
#define DANCE_MAINMUSIC_FADEOUT_FRAME	(30)
///オープニングエフェクト終了後のウェイト
#define OPENING_EFFECT_END_WAIT			(30)	//(60)

///フェード：ローテーション時のウェイト
#define FADE_ROTATION_WAIT		(-2)
///フェード：ローテーション時のカラー
#define FADE_ROTATION_COLOR		(0x0000)
///フェード：ローテーション時のEVY値
#define FADE_ROTATION_EVY		(6)

///ダンスの曲を停止する時のフェードアウトにかけるフレーム数
#define EE_DANCEMUSIC_FADEOUT_FRAME		(30)
///ランキング発表後の待ち時間
#define EE_RANKING_AFTER_WAIT			(60)


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static int Request_Sample(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_Sample(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void Answer_Sample(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *answer_head, CO_ANSDAT *ansdat, int net_id);
static int Request_DonchouUp(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_DonchouUp(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void DOTCB_DonchouUp(TCB_PTR tcb, void *work);
static int Request_DonchouDown(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_DonchouDown(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void DOTCB_DonchouDown(TCB_PTR tcb, void *work);
static int Request_Rotation(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_Rotation(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void DOTCB_Rotation(TCB_PTR tcb, void *work);
static void DOTCB_RotationBreeder(TCB_PTR tcb, void *work);
static int Request_Dancing(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_Dancing(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void DOTCB_Dancing(TCB_PTR tcb, void *work);
static void Answer_Dancing(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *answer_head, CO_ANSDAT *ansdat, int net_id);
static int Request_DanceExit(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_DanceExit(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static int DanceTouchCheck(DANCE_TOUCH_WORK *dtw, int *tp_ret, int check, int no_touch_bg);
static DANCING_SEND_WORK * DancingParamSendTaskSet(DANCE_PROC_WORK *dpw, int ai);
static void DancingParamSendTaskFree(DANCING_SEND_WORK *sendwork);
static void DancingParamSendTaskMain(TCB_PTR tcb, void *work);
static int Request_Before(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_Before(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void DOTCB_Before(TCB_PTR tcb, void *work);
static int Request_After(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_After(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void DOTCB_After(TCB_PTR tcb, void *work);
static int Request_Talk(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_Talk(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void DOTCB_TalkPut(TCB_PTR tcb, void *work);
static int Request_GameParam(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_GameParam(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static int Request_MusicStart(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_MusicStart(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static int Request_OpeningEff(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_OpeningEff(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void DOTCB_OpeningEff(TCB_PTR tcb, void *work);
static void FumenCounterInit(DANCE_PROC_WORK *dpw);
static int Request_EndEffect(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
static void Recieve_EndEffect(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data);
static void DOTCB_EndEffect(TCB_PTR tcb, void *work);


//==============================================================================
//	データ
//==============================================================================
///命令送受信用関数ポインタ構造体テーブル	※ここに追加したら必ず.hのenumにも追加する事!!
static const CON_ORDER_FUNC OrderFuncTbl[] = {
	{//DORDER_NO_SAMPLE		サンプル
		Request_Sample, 
		Recieve_Sample, 
		Answer_Sample, 
	},
	{//DORDER_NO_DONCHOU_UP
		Request_DonchouUp, 
		Recieve_DonchouUp, 
		NULL, 
	},
	{//DORDER_NO_DONCHOU_DOWN
		Request_DonchouDown, 
		Recieve_DonchouDown, 
		NULL, 
	},
	{//DORDER_NO_OPENING_EFF
		Request_OpeningEff, 
		Recieve_OpeningEff, 
		NULL, 
	},
	{//DORDER_NO_DANCE_EXIT
		Request_DanceExit,
		Recieve_DanceExit,
		NULL,
	},
	{//DORDER_NO_DANCING
		Request_Dancing, 
		Recieve_Dancing, 
		Answer_Dancing, 
	},
	{//DORDER_NO_ROTATION
		Request_Rotation, 
		Recieve_Rotation, 
		NULL, 
	},
	{//DORDER_NO_BEFORE
		Request_Before, 
		Recieve_Before, 
		NULL, 
	},
	{//DORDER_NO_AFTER
		Request_After, 
		Recieve_After, 
		NULL, 
	},
	{//DORDER_NO_TALK
		Request_Talk, 
		Recieve_Talk, 
		NULL, 
	},
	{//DORDER_NO_GAMEPARAM
		Request_GameParam, 
		Recieve_GameParam, 
		NULL, 
	},
	{//DORDER_NO_MUSIC_START
		Request_MusicStart, 
		Recieve_MusicStart, 
		NULL, 
	},
	{//DORDER_NO_END_EFFECT
		Request_EndEffect, 
		Recieve_EndEffect, 
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
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void DanceOrder_WorkInit(DANCE_PROC_WORK *dpw)
{
	CO_INIT_DATA initdata;
	
	initdata.func_tbl = OrderFuncTbl;
	initdata.func_tbl_max = NELEMS(OrderFuncTbl);
	initdata.my_breeder_no = dpw->consys->c_game.my_breeder_no;
	initdata.server_no = dpw->consys->c_game.server_no;
	initdata.sio_flag = dpw->consys->sio_flag;
	
	CO_WorkInit(&dpw->cow, &initdata);
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：サンプル
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_Sample(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	DANCE_PROC_WORK *dpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, NULL, 0);
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：サンプル
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_Sample(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	DANCE_PROC_WORK *dpw = syswork;
	
	//返事を返す	バッファは特に渡すものがないのでNULL指定
	CO_ANSWER_TransmitBufferSet(cow, req_head, NULL, 0);
}

//--------------------------------------------------------------
/**
 * @brief   返事受信(送信元)：サンプル
 *
 * @param   dpw				ダンス部門管理ワークへのポインタ
 * @param   answer_head		返事ヘッダのポインタ
 * @param   ansdat			受信データへのポインタ
 * @param   net_id			返事送信者のネットID
 */
//--------------------------------------------------------------
static void Answer_Sample(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *answer_head, CO_ANSDAT *ansdat, int net_id)
{
	DANCE_PROC_WORK *dpw = syswork;
	
	//返事を受け取るだけなので特にする事がない
	return;
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：どんちょう上げる
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_DonchouUp(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	DANCE_PROC_WORK *dpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, NULL, 0);
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：どんちょう上げる
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_DonchouUp(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	DANCE_PROC_WORK *dpw = syswork;
	DOLOCAL_DONCHOU_UP *du;
	
	du = sys_AllocMemory(HEAPID_DANCE, sizeof(DOLOCAL_DONCHOU_UP));
	MI_CpuClear8(du, sizeof(DOLOCAL_DONCHOU_UP));

	du->dpw = dpw;
	du->req_head = *req_head;
	du->cow = cow;
	
	TCB_Add(DOTCB_DonchouUp, du, TCBPRI_DANCE_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   どんちょうを上げる
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		DOLOCAL_DONCHOU_UP構造体
 */
//--------------------------------------------------------------
static void DOTCB_DonchouUp(TCB_PTR tcb, void *work)
{
	DOLOCAL_DONCHOU_UP *du = work;
	
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
			
			scrn_buf = GF_BGL_ScreenAdrsGet(du->dpw->sys.bgl, DANCE_FRAME_EFF);
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
			
			GF_BGL_LoadScreenV_Req(du->dpw->sys.bgl, DANCE_FRAME_EFF);
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
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_DonchouDown(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	DANCE_PROC_WORK *dpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, NULL, 0);
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：どんちょう下げる
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_DonchouDown(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	DANCE_PROC_WORK *dpw = syswork;
	DOLOCAL_DONCHOU_DOWN *dd;
	
	dd = sys_AllocMemory(HEAPID_DANCE, sizeof(DOLOCAL_DONCHOU_DOWN));
	MI_CpuClear8(dd, sizeof(DOLOCAL_DONCHOU_DOWN));

	dd->dpw = dpw;
	dd->req_head = *req_head;
	dd->cow = cow;
	
	TCB_Add(DOTCB_DonchouDown, dd, TCBPRI_DANCE_ORDERSUB);

	dpw->music_vcount_flag = FALSE;
	Snd_BgmPlay(SEQ_CON_TEST);
}

//--------------------------------------------------------------
/**
 * @brief   どんちょうを下げる
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		DOLOCAL_DONCHOU_DOWN構造体
 */
//--------------------------------------------------------------
static void DOTCB_DonchouDown(TCB_PTR tcb, void *work)
{
	DOLOCAL_DONCHOU_DOWN *dd = work;
	
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
			
			scrn_buf = GF_BGL_ScreenAdrsGet(dd->dpw->sys.bgl, DANCE_FRAME_EFF);
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
			
			GF_BGL_LoadScreenV_Req(dd->dpw->sys.bgl, DANCE_FRAME_EFF);
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
 * @brief   命令送信(送信元)：オープニングエフェクト
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_OpeningEff(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	DANCE_PROC_WORK *dpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, NULL, 0);
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：オープニングエフェクト
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_OpeningEff(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	DANCE_PROC_WORK *dpw = syswork;
	DOLOCAL_OPENING_EFF *oe;
	
	oe = sys_AllocMemory(HEAPID_DANCE, sizeof(DOLOCAL_OPENING_EFF));
	MI_CpuClear8(oe, sizeof(DOLOCAL_OPENING_EFF));

	oe->dpw = dpw;
	oe->req_head = *req_head;
	oe->cow = cow;
	
	TCB_Add(DOTCB_OpeningEff, oe, TCBPRI_DANCE_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   オープニングエフェクト
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		DOLOCAL_OPENING_EFF構造体
 */
//--------------------------------------------------------------
static void DOTCB_OpeningEff(TCB_PTR tcb, void *work)
{
	DOLOCAL_OPENING_EFF *oe = work;
	
	switch(oe->seq){
	case 0:
		Snd_BgmStop(SEQ_CON_TEST, DANCE_MAINMUSIC_FADEOUT_FRAME);
		oe->seq++;
		break;
	case 1:
		if(Snd_FadeCheck() == 0){
			oe->seq++;
		}
		break;
	case 2:
		G2_BlendNone();		//ハードフェードOFF
		
		DT_BGAlphaDefaultBlendModeSet();
		DT_ShadowEnableSet(&oe->dpw->sys, CATS_ENABLE_TRUE);
		Snd_SePlay(DSE_LIGHT_ON);
		oe->seq++;
		break;
	case 3:
		oe->wait++;
		if(oe->wait > OPENING_EFFECT_END_WAIT){
			oe->wait = 0;
			oe->seq++;
		}
		break;
	case 4:		//自分のポケモンだけ動く
		DT_PokeAppealMove(oe->dpw, oe->dpw->consys->c_game.my_breeder_no, &oe->end_flag);
		oe->seq++;
		break;
	case 5:
		if(oe->end_flag == TRUE){
			oe->seq++;
		}
		break;
	default:
		CO_ANSWER_TransmitBufferSet(oe->cow, &oe->req_head, NULL, 0);

		sys_FreeMemoryEz(oe);
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
static int Request_DanceExit(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	DANCE_PROC_WORK *dpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, work, sizeof(DANCE_EXIT_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：ダンス部門終了
 *
 * @param   dpw			演技力部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_DanceExit(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	DANCE_PROC_WORK *dpw = syswork;
	DANCE_EXIT_PARAM *dep = data;
	int i;
	
	dpw->main_end = TRUE;
	for(i = 0; i < BREEDER_MAX; i++){
		dpw->consys->actin_sort[i] = dep->actin_sort[i];
	}
	
	//返事を返す	バッファは特に渡すものがないのでNULL指定
	CO_ANSWER_TransmitBufferSet(cow, req_head, NULL, 0);
}


//==============================================================================
//	
//==============================================================================
#if 0	//メインダンサーもバックダンサーも同じ譜面を参照するようになった。
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：メインダンス
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_Dancing(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	DANCE_PROC_WORK *dpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(DANCE_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：メインダンス
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_Dancing(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	DANCE_PROC_WORK *dpw = syswork;
	DANCE_ADVANCE_PARAM *dap = data;
	DOLOCAL_MAINDANCE *md;
	
	md = sys_AllocMemory(HEAPID_DANCE, sizeof(DOLOCAL_MAINDANCE));
	MI_CpuClear8(md, sizeof(DOLOCAL_MAINDANCE));

	md->dpw = dpw;
	md->req_head = *req_head;
	md->cow = cow;
	md->dap = *dap;
	
	md->dtw.dpw = dpw;
	
	TCB_Add(DOTCB_Dancing, md, TCBPRI_DANCE_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   ダンス実行パラメータ送信タスクを生成します
 * @param   param		ダンス実行パラメータへのポインタ
 * @retval  生成した送信タスクのポインタ
 */
//--------------------------------------------------------------
static TCB_PTR DancingParamSendReqSet(DANCE_PROC_WORK *dpw, const DANCING_PARAM *param)
{
	DANCING_SEND_WORK *sendwork;
	
	sendwork = sys_AllocMemory(HEAPID_DANCE, sizeof(DANCING_SEND_WORK));
	MI_CpuClear8(sendwork, sizeof(DANCING_SEND_WORK));
	sendwork->dpw = dpw;
	sendwork->dancing_param = *param;
	
	//非通信の時でも、メインダンサーのダンス履歴更新タイミングを個々のクライアントでも
	//同じにするため、Order系が全て終わってから実行されるタスクでパラメータの送信をする
	return TCB_Add(DancingParamSendTaskMain, sendwork, TCBPRI_DANCE_DANCING_PARAM_SEND);
}

//--------------------------------------------------------------
/**
 * @brief   ダンス実行パラメータ送信タスクメイン処理
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		DANCING_SEND_WORK構造体
 */
//--------------------------------------------------------------
static void DancingParamSendTaskMain(TCB_PTR tcb, void *work)
{
	DANCING_SEND_WORK *sendwork = work;
	int end = 0;
	
	if(sendwork->dpw->consys->sio_flag == FALSE){
		DT_DancingParamRecieve(sendwork->dpw, &sendwork->dancing_param);
		OS_TPrintf("ダンス実行動作データ送信：送信ブリーダー=%d\n", 
			sendwork->dancing_param.breeder_no);

		end++;
	}
	else{
		if(CommSendFixSizeData(CC_DANCE_DATA, &sendwork->dancing_param) == TRUE){
			OS_TPrintf("ダンス実行動作データ送信：送信ブリーダー=%d\n", 
				sendwork->dancing_param.breeder_no);
			
			end++;
		}
		else{
			
		}
	}
	
	if(end > 0){
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   メインダンス(自分が踊る場合)
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		DOLOCAL_MAINDANCE構造体
 */
//--------------------------------------------------------------
static void DOTCB_Dancing(TCB_PTR tcb, void *work)
{
	DOLOCAL_MAINDANCE *md = work;
	int tp_ret, dancer_type, rotation_pos;
	
	if(md->dpw->consys->c_game.my_breeder_no == md->dap.now_breeder){
		dancer_type = DANCER_MAIN;
	}
	else{
		dancer_type = DANCER_BACK;
	}
	
	switch(md->seq){
	case 0:
		if(dancer_type == DANCER_MAIN){
			DT_FumenColorSet(&md->dpw->sys, FUMENCOLOR_MAIN);
		}
		else{
			DT_FumenColorSet(&md->dpw->sys, FUMENCOLOR_BACK);
		}
		md->seq++;
		break;
	case 1:
		md->frame++;
		
		{//曲進行バー更新
			int frame;
			
			if(dancer_type == DANCER_MAIN){
				frame = md->frame;
			}
			else{
				if(md->frame <= md->dap.musicdata.frame / 2){
					if(md->loop == 0){
						frame = 0;
					}
					else{
						frame = md->frame + md->dap.musicdata.frame / 2;
					}
				}
				else{
					frame = md->frame - md->dap.musicdata.frame / 2;
				}
			}
			DT_MusicBarAnimeUpdateFrame(&md->dpw->sys, frame, md->dap.musicdata.frame);
		}
		
		{//曲進行バーの到達やループを確認
			if(md->frame >= md->dap.musicdata.frame){
				md->loop++;
				md->frame = 0;
				if(dancer_type == DANCER_MAIN){
					DT_OnpuActorDelAll(&md->dpw->sys);
					if(md->loop >= md->dap.musicdata.loop){
						DT_FumenColorSet(&md->dpw->sys, FUMENCOLOR_NULL);
					}
				}
			}
			else if(md->loop >= md->dap.musicdata.loop 
					&& md->frame >= md->dap.musicdata.frame / 2){
				md->seq++;
				break;
			}
			else if(dancer_type == DANCER_BACK && md->frame == md->dap.musicdata.frame / 2){
				DT_OnpuActorDelAll(&md->dpw->sys);
			}
		}
		
		{//ローテーション位置取得
			for(rotation_pos = 0; rotation_pos < BREEDER_MAX; rotation_pos++){
				if(md->dap.breeder_rotation[rotation_pos] ==md->dpw->consys->c_game.my_breeder_no){
					break;
				}
			}
		}
		
		{//タッチチェック
			DANCING_PARAM dancing_param;
			
			if(dancer_type == DANCER_MAIN){
				//メインダンサー
				if(md->loop < md->dap.musicdata.loop 
						&& md->frame >= md->dap.musicdata.frame / 2){
					DanceTouchCheck(&md->dtw, &tp_ret, FALSE, FALSE);
				}
				else{
					DanceTouchCheck(&md->dtw, &tp_ret, TRUE, TRUE);
				}
				
				if(tp_ret != RECT_HIT_NONE){
					DancerReactionSet(md->dpw->consys->c_game.my_breeder_no, tp_ret, md->frame, 
						md->dap.musicdata.frame, &md->dap.musicdata.lag, 
						&dancing_param, NULL, rotation_pos);
					DancingParamSendReqSet(md->dpw, &dancing_param);
				}
			}
			else{
				//バックダンサー
				if(md->loop > 0 && md->frame < md->dap.musicdata.frame / 2){
					DanceTouchCheck(&md->dtw, &tp_ret, FALSE, FALSE);
				}
				else{
					DanceTouchCheck(&md->dtw, &tp_ret, TRUE, TRUE);
				}
				
				if(tp_ret != RECT_HIT_NONE){
					DancerReactionSet(md->dpw->consys->c_game.my_breeder_no, tp_ret, md->frame, 
						md->dap.musicdata.frame, &md->dap.musicdata.lag, 
						&dancing_param, md->dpw->maindancer_record, rotation_pos);
					DancingParamSendReqSet(md->dpw, &dancing_param);
				}
			}
		}
		break;
	default:
		if(DanceTouchCheck(&md->dtw, &tp_ret, TRUE, FALSE) == TRUE){
			DT_OnpuActorDelAll(&md->dpw->sys);
			DT_MusicBarAnimeUpdateFrame(&md->dpw->sys, 0, md->dap.musicdata.frame);
			DT_FumenColorSet(&md->dpw->sys, FUMENCOLOR_NULL);
			if(DINPUT_MakeDataNoGet(md->dpw->dip) != DINPUT_TYPE_WALL){
				DINPUT_CreateBG(md->dpw->dip, DINPUT_TYPE_WALL, TRUE, NULL);
			}
			
			CO_ANSWER_TransmitBufferSet(md->cow, &md->req_head, NULL, 0);

			sys_FreeMemoryEz(md);
			TCB_Delete(tcb);
			return;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ダンス操作でのタッチ反応チェック
 *
 * @param   dtw			
 * @param   tp_ret		タッチ反応結果代入先
 * @param   check		TRUE:待機状態かチェックする(タッチには反応させない)
 * @param   no_touch_bg	TRUE:タッチ出来ない時のBG状態にする(待機状態になっている時のみ有効)
 *
 * @retval  TRUE:待機中。　FALSE:処理中(エフェクト中など)
 */
//--------------------------------------------------------------
static int DanceTouchCheck(DANCE_TOUCH_WORK *dtw, int *tp_ret, int check, int no_touch_bg)
{
	int taiki;
	
	taiki = FALSE;
	*tp_ret = RECT_HIT_NONE;
	
	switch(dtw->seq){
	case 0:
		if(check == FALSE && no_touch_bg == FALSE){
			DINPUT_CreateBG(dtw->dpw->dip, DINPUT_TYPE_COMMAND, TRUE, NULL);
			dtw->seq++;
		}
		else{
			taiki = TRUE;
		}
		break;
	case 1:
		if(check == TRUE){
			taiki = TRUE;
			break;		//チェックの時はあらたなタッチをさせない
		}
		
		*tp_ret = DINPUT_TouchCheck(dtw->dpw->dip);
		if(*tp_ret != RECT_HIT_NONE){
			Snd_SePlay(DSE_DECIDE);
			dtw->seq++;
		}
		else{
			taiki = TRUE;
		}
		break;
	case 2:
		if(DINPUT_EffectEndCheck(dtw->dpw->dip) == TRUE){
			DINPUT_CreateBG(dtw->dpw->dip, DINPUT_TYPE_COMMAND, TRUE, NULL);
			dtw->seq = 1;
		}
		break;
	}
	
	if(no_touch_bg == TRUE && taiki == TRUE){
		if(DINPUT_MakeDataNoGet(dtw->dpw->dip) != DINPUT_TYPE_WALL){
			DINPUT_CreateBG(dtw->dpw->dip, DINPUT_TYPE_WALL, TRUE, NULL);
			dtw->seq = 0;
		}
	}
	
	return taiki;
}

//--------------------------------------------------------------
/**
 * @brief   タッチパネル結果をダンスタイプに変換する
 * @param   dance_tp		DANCE_TP_???
 * @retval  DANCE_STEP_???
 */
//--------------------------------------------------------------
static int DanceTP_to_DanceStep(int dance_tp)
{
	int dance_step;
	
	switch(dance_tp){
	case DANCE_TP_JUMP:
		dance_step = DANCE_STEP_JUMP;
		break;
	case DANCE_TP_ADVANCE:
		dance_step = DANCE_STEP_ADVANCE;
		break;
	case DANCE_TP_LEFT:
		dance_step = DANCE_STEP_LEFT;
		break;
	case DANCE_TP_RIGHT:
		dance_step = DANCE_STEP_RIGHT;
		break;
	default:
		GF_ASSERT(0 && "無効なリアクションです\n");
		return 0;
	}
	return dance_step;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスのずれから評価を取得する
 *
 * @param   lag				ダンスのずれ(拍子から何フレームずれているか)
 * @param   dld				ずれ比較データへのポインタ
 * @param   ret_review		評価タイプ代入先
 * @param   ret_lag			ラグタイプ代入先
 * @param   ret_onpu		音符タイプ代入先
 */
//--------------------------------------------------------------
static void DanceLagReviewTypeGet(int lag, const DANCE_LAG_DATA *dld, 
	u8 *ret_review, u8 *ret_lag, u8 *ret_onpu)
{
	if(lag <= dld->excellent_a){
		*ret_review = REVIEW_TYPE_EXCELLENT;
		*ret_lag = DANCE_LAG_EXCELLENT_A;
		*ret_onpu = ONPU_TYPE_B;
	}
	else if(lag <= dld->excellent_b){
		*ret_review = REVIEW_TYPE_EXCELLENT;
		*ret_lag = DANCE_LAG_EXCELLENT_B;
		*ret_onpu = ONPU_TYPE_B;
	}
	else if(lag <= dld->good_a){
		*ret_review = REVIEW_TYPE_GOOD;
		*ret_lag = DANCE_LAG_GOOD_A;
		*ret_onpu = ONPU_TYPE_A;
	}
	else if(lag <= dld->good_b){
		*ret_review = REVIEW_TYPE_GOOD;
		*ret_lag = DANCE_LAG_GOOD_B;
		*ret_onpu = ONPU_TYPE_A;
	}
	else{
		*ret_review = REVIEW_TYPE_FAILED;
		*ret_lag = DANCE_LAG_FAILED;
		*ret_onpu = ONPU_TYPE_A;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ダンスしたフレームから対象となる小節と、
 *          その小節丁度のフレームから何フレームずれているか取得
 *
 * @param   frame		ダンスを実行した瞬間のフレーム
 * @param   max_frame	曲進行の最大フレーム
 * @param   ret_lag		ずれ代入先(何フレーム拍子からずれているか)
 * @param   ret_beat	対象となった小節代入先
 */
//--------------------------------------------------------------
static void DancerLagBeatCheck(int frame, int max_frame, u32 *ret_lag, u32 *ret_beat)
{
	u32 just_frame, hit_frame, min_frame, big_frame, check_frame;
	u32 min_lag, big_lag;
	u32 hit_beat, lag;
	
	just_frame = (max_frame << 8) / DANCE_BEAT;
	hit_frame = frame << 8;
	
	min_frame = 0;
	hit_beat = 0;
	for(check_frame = 0; check_frame < hit_frame; check_frame += just_frame){
		min_frame = check_frame;
		hit_beat++;
	}
	big_frame = check_frame;
	
	min_frame = (min_frame + 0x0080) >> 8;	//小数を四捨五入して正数化
	big_frame = (big_frame + 0x0080) >> 8;
	hit_frame >>= 8;
	
	//ずれの少ない方を計算の対象とする
	min_lag = MATH_ABS((s32)(hit_frame - min_frame));
	big_lag = MATH_ABS((s32)(hit_frame - big_frame));
	if(min_lag <= big_lag){
		lag = min_lag;
		hit_beat--;
	}
	else{
		lag = big_lag;
	}
	
	*ret_lag = lag;
	*ret_beat = hit_beat;
}

//--------------------------------------------------------------
/**
 * @brief   ダンサーがダンス実行時のリアクションパラメータセット
 *
 * @param   breeder_no		自分のブリーダー番号
 * @param   reaction		行ったダンス(DANCE_TP_???)
 * @param   frame			ダンスを実行したフレーム
 * @param   max_frame		曲進行最大フレーム
 * @param   dld				ずれ比較データへのポインタ
 * @param   param			リアクションパラメータ代入先へのポインタ
 * @param   maindancer_record	ダンスしているのがメインダンサーの場合はNULL指定
 *                              バックダンサーの場合はメインダンサーのダンス履歴へのポインタ
 * @param   rotation_pos	ローテーション位置
 */
//--------------------------------------------------------------
static void DancerReactionSet(int breeder_no, int reaction, int frame, int max_frame, 
	const DANCE_LAG_DATA *dld, DANCING_PARAM *param, const DANCING_PARAM *maindancer_record,
	int rotation_pos)
{
	int dance_step, i;
	u8 review_type, lag_type, onpu_type;
	u32 lag, hit_beat;
	int main_back;
	
	//タッチパネル結果からダンスタイプを取得
	dance_step = DanceTP_to_DanceStep(reaction);
	
	//タッチしたフレームから対象となる小節と、その小節丁度のフレームから何フレームずれているか取得
	DancerLagBeatCheck(frame, max_frame, &lag, &hit_beat);
	OS_TPrintf("対象小節=%d, ずれ=%dフレーム\n", hit_beat, lag);
	
	//ずれから評価を取得する
	DanceLagReviewTypeGet(lag, dld, &review_type, &lag_type, &onpu_type);
	if(maindancer_record != NULL){
		//バックダンサーの場合、メインダンサーのダンス履歴と比較を行う
		for(i = 0; i < DANCING_RECORD_MAX; i++){
			if(maindancer_record[i].frame != 0 && maindancer_record[i].hit_beat == hit_beat){
				break;	//小節のメインダンサーの履歴にあったので今のずれデータを採用
			}
		}
		if(i == DANCING_RECORD_MAX){
			lag = 0xff;	//ヒットした小節がなかったのでずれを最大にする(FAILED評価を得る為)
			OS_TPrintf("メインダンサーとヒットしなかったのでずれ最大\n");
		}
		main_back = DANCER_BACK;
	}
	else{
		main_back = DANCER_MAIN;
	}
	
	//パラメータセット
	param->breeder_no = breeder_no;
	param->frame = frame;
	param->dance_step = dance_step;
	param->review_type = review_type;
	param->lag_type = lag_type;
	param->onpu_type = onpu_type;
	param->hit_beat = hit_beat;
	param->rotation_pos = rotation_pos;
	param->main_back = main_back;
}

//--------------------------------------------------------------
/**
 * @brief   返事受信(送信元)：メインダンス
 *
 * @param   dpw				ダンス部門管理ワークへのポインタ
 * @param   answer_head		返事ヘッダのポインタ
 * @param   ansdat			受信データへのポインタ
 */
//--------------------------------------------------------------
static void Answer_Dancing(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *answer_head, CO_ANSDAT *ansdat, int net_id)
{
	DANCE_PROC_WORK *dpw = syswork;
	
	//返事を受け取るだけなので特にする事がない
	return;
}
#else	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//==============================================================================
//	メインダンス
//==============================================================================
//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：メインダンス
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_Dancing(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	DANCE_PROC_WORK *dpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(DANCE_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：メインダンス
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_Dancing(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	DANCE_PROC_WORK *dpw = syswork;
	DANCE_ADVANCE_PARAM *dap = data;
	DOLOCAL_MAINDANCE *md;
	int i, rotation_pos;
	
	md = sys_AllocMemory(HEAPID_DANCE, sizeof(DOLOCAL_MAINDANCE));
	MI_CpuClear8(md, sizeof(DOLOCAL_MAINDANCE));

	md->dpw = dpw;
	md->req_head = *req_head;
	md->cow = cow;
	md->dap = *dap;
	
	md->dtw.dpw = dpw;
	
#ifdef PM_DEBUG
	if(DmatsuWork_DanceRotationOff == 2){
		md->dap.musicdata.touch_count = 100;	//実質タッチ制限なしにする
	}
#endif

	TCB_Add(DOTCB_Dancing, md, TCBPRI_DANCE_ORDERSUB);
	for(i = 0; i < BREEDER_MAX; i++){
		if(i < dpw->consys->c_game.player_num){
			md->sendwork[i] = DancingParamSendTaskSet(dpw, FALSE);
		}
		else{
			md->sendwork[i] = DancingParamSendTaskSet(dpw, TRUE);
		}
	}

	{//自分のローテーション位置取得
		for(rotation_pos = 0; rotation_pos < BREEDER_MAX; rotation_pos++){
			if(md->dap.breeder_rotation[rotation_pos] ==md->dpw->consys->c_game.my_breeder_no){
				md->dpw->sys.my_dancing_rotation_pos = rotation_pos;
				break;
			}
		}
	}
	
	FumenCounterInit(dpw);
	
	//AIタスク生成(通信での遅延を考慮してAIはAI番号とAI用のランダムの種だけ同期させて
	//各ローカルで計算は行う)
	for(i = dpw->consys->c_game.player_num; i < BREEDER_MAX; i++){
		{//ローテーション位置取得
			for(rotation_pos = 0; rotation_pos < BREEDER_MAX; rotation_pos++){
				if(md->dap.breeder_rotation[rotation_pos] == i){
					break;
				}
			}
		}
		DanceAI_Init(&md->aiwork[i], i, rotation_pos, dap->ai_random_seed[i], 
			dpw->consys->c_game.character[i]);
	}
}

///メインダンサーのフレーム内か確認(TRUEだとメインダンサーフレーム内)
#define MAIN_DANCER_FRAME_CHECK(frame, all_tempo_frame)		(frame < (all_tempo_frame >> 1))
///バックダンサーのフレーム内か確認(TRUEだとバックダンサーフレーム内)
#define BACK_DANCER_FRAME_CHECK(frame, all_tempo_frame)		(frame >= (all_tempo_frame >> 1))

//--------------------------------------------------------------
/**
 * @brief   ダンス実行パラメータ送信タスクを生成します
 * @param   ai			TRUE=AI、FALSE=プレイヤー操作
 * @retval  生成した送信タスクワークのポインタ
 */
//--------------------------------------------------------------
static DANCING_SEND_WORK * DancingParamSendTaskSet(DANCE_PROC_WORK *dpw, int ai)
{
	DANCING_SEND_WORK *sendwork;
	
	sendwork = sys_AllocMemory(HEAPID_DANCE, sizeof(DANCING_SEND_WORK));
	MI_CpuClear8(sendwork, sizeof(DANCING_SEND_WORK));
	sendwork->dpw = dpw;
	sendwork->ai = ai;
	
	//非通信の時でも、メインダンサーのダンス履歴更新タイミングを個々のクライアントでも
	//同じにするため、Order系が全て終わってから実行されるタスクでパラメータの送信をする
	sendwork->tcb = TCB_Add(DancingParamSendTaskMain, sendwork, TCBPRI_DANCE_DANCING_PARAM_SEND);
	
	return sendwork;
}

//--------------------------------------------------------------
/**
 * @brief   ダンス実行パラメータ送信タスクを削除します
 * @param   sendwork		送信タスクワークのポインタ
 */
//--------------------------------------------------------------
static void DancingParamSendTaskFree(DANCING_SEND_WORK *sendwork)
{
	TCB_Delete(sendwork->tcb);
	sys_FreeMemoryEz(sendwork);
}

//--------------------------------------------------------------
/**
 * @brief   ダンス実行パラメータ送信タスクを生成します
 * @param   param		ダンス実行パラメータへのポインタ
 * @retval  生成した送信タスクのポインタ
 */
//--------------------------------------------------------------
void DancingParamSendReqSet(DANCING_SEND_WORK *sendwork, const DANCING_PARAM *param)
{
	sendwork->dancing_param = *param;
	sendwork->req = TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンス実行パラメータ送信タスクメイン処理
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		DANCING_SEND_WORK構造体
 */
//--------------------------------------------------------------
static void DancingParamSendTaskMain(TCB_PTR tcb, void *work)
{
	DANCING_SEND_WORK *sendwork = work;
	
	if(sendwork->req == FALSE){
		return;
	}
	
	if(sendwork->dpw->consys->sio_flag == FALSE || sendwork->ai == TRUE){
		DT_DancingParamRecieve(sendwork->dpw, &sendwork->dancing_param);
		OS_TPrintf("ダンス実行動作データ送信：送信ブリーダー=%d\n", 
			sendwork->dancing_param.breeder_no);
		
		sendwork->req = FALSE;
	}
	else{
		if(CommSendFixSizeData(CC_DANCE_DATA, &sendwork->dancing_param) == TRUE){
			OS_TPrintf("ダンス実行動作データ送信：送信ブリーダー=%d\n", 
				sendwork->dancing_param.breeder_no);
			
			sendwork->req = FALSE;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   メインダンス(自分が踊る場合)
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		DOLOCAL_MAINDANCE構造体
 */
//--------------------------------------------------------------
static void DOTCB_Dancing(TCB_PTR tcb, void *work)
{
	DOLOCAL_MAINDANCE *md = work;
	int tp_ret, dancer_type, rotation_pos;
	u32 frame;
	int now_frame_dancer;
	
	if(md->dpw->consys->c_game.my_breeder_no == md->dap.now_breeder){
		dancer_type = DANCER_MAIN;
	}
	else{
		dancer_type = DANCER_BACK;
	}
	
	frame = md->dpw->music_vcount - md->dpw->music_vcount_start;
	if(MAIN_DANCER_FRAME_CHECK(frame, md->dap.all_tempo_frame)){
		now_frame_dancer = DANCER_MAIN;
	}
	else{
		now_frame_dancer = DANCER_BACK;
	}
	
	switch(md->seq){
	case 0:
	#if 0
		if(dancer_type == DANCER_MAIN){
			DT_FumenColorSet(&md->dpw->sys, FUMENCOLOR_MAIN);
		}
		else{
			DT_FumenColorSet(&md->dpw->sys, FUMENCOLOR_BACK);
		}
	#endif
		DT_FumenColorSet(&md->dpw->sys, FUMENCOLOR_MAIN);
		DT_MainDancerRecordInit(md->dpw);
		DancdAI_MainDancerCalc(md->dpw, &md->aiwork[md->dap.now_breeder], 
			md->dap.all_tempo_frame, md->dap.one_tempo_frame);
		PrinReq_InMove(md->dpw->sys.prin_sys);
		DT_BGAlphaEffectSet(md->dpw, DANCE_BGALPHA_TYPE_NULL);
		DT_FumenFlashTaskSet(md->dpw);
		
		//どこでダンスするのかをパネルメッセージで表示
		{
			DTAG_PARAM tagpara;
			tagpara.num = md->dap.musicdata.touch_count;
			if(dancer_type == DANCER_MAIN){
				DT_PanelMessagePut(md->dpw, A_TALK_BEGIN_HOST_02, &tagpara);
			}
			else{
				DT_PanelMessagePut(md->dpw, A_TALK_BEGIN_HOST_03, &tagpara);
			}
		}
		
		md->seq++;
		break;
	case 1:
//		if(Snd_BgmPlayCheck(SEQ_CO_JUNBI) == FALSE){
		if(DT_DancingStartFrameCheck(md->dpw, &(md->dap.musicdata), md->dap.now_count) <= 0){
			DT_PanelMessageClear(md->dpw);

			md->dpw->music_vcount_start = md->dpw->music_vcount 
				+ DT_DancingStartFrameCheck(md->dpw, 
				&(md->dap.musicdata), md->dap.now_count);
			
			if(dancer_type == DANCER_MAIN){
				DT_FumenFlashEffectSet(md->dpw, dancer_type);
				md->flash_flag++;
			}
			
			DT_DancerLightEffectSet(md->dpw, md->dap.now_breeder, DANCER_MAIN);
			
			OS_TPrintf("１週目count = %d\n", md->dpw->music_vcount_start);
			md->seq++;
		}
		else{
			OS_TPrintf("開始までの残りフレーム=%d\n", DT_DancingStartFrameCheck(md->dpw, &(md->dap.musicdata), md->dap.now_count));
		}
		break;
	case 2:
		{//曲進行バー更新
			DT_MusicBarAnimeUpdateFrame(&md->dpw->sys, 
				md->dpw->music_vcount - md->dpw->music_vcount_start, md->dap.all_tempo_frame);
			PrinReq_FrameUpdate(md->dpw->sys.prin_sys, 
				md->dpw->music_vcount - md->dpw->music_vcount_start, md->dap.all_tempo_frame);
		}
		
		{//曲進行バーの到達やループを確認
			if(frame >= md->dap.all_tempo_frame){
				md->loop++;
				md->dpw->music_vcount_start = md->dpw->music_vcount;
				md->flash_flag = 0;
				md->back_dancer_light_flag = 0;
				
				//カウンタクリア
				FumenCounterInit(md->dpw);

				//タッチ回数リセット
				{
					int i;

					md->touch_count = 0;
					for(i = md->dpw->consys->c_game.player_num; i < BREEDER_MAX; i++){
						DanceAI_ParamClear(&md->aiwork[i]);
					}
				}
				
				OS_TPrintf("2週目count = %d\n", md->dpw->music_vcount_start);
				DT_OnpuActorDelAll(&md->dpw->sys);
				DT_MainDancerRecordInit(md->dpw);
				DancdAI_MainDancerCalc(md->dpw, &md->aiwork[md->dap.now_breeder], 
					md->dap.all_tempo_frame, md->dap.one_tempo_frame);
				DT_BGAlphaEffectSet(md->dpw, DANCE_BGALPHA_TYPE_NULL);

				if(md->loop >= md->dap.musicdata.loop){
					DT_DancerLightEffectOff(md->dpw);
					DT_FumenColorSet(&md->dpw->sys, FUMENCOLOR_NULL);
					md->seq++;
					break;
				}
				else{
					DT_DancerLightEffectSet(md->dpw, md->dap.now_breeder, DANCER_MAIN);
					if(dancer_type == DANCER_MAIN){
						if(md->flash_flag == 0){
							DT_FumenFlashEffectSet(md->dpw, dancer_type);
							md->flash_flag++;
						}
					}
				}
				break;
			}
		}
		
		{//ローテーション位置取得
			rotation_pos = md->dpw->sys.my_dancing_rotation_pos;
		}
		
		{//タッチチェック
			DANCING_PARAM dancing_param;
			int now_frame_dancer;
			
			if(MAIN_DANCER_FRAME_CHECK(frame, md->dap.all_tempo_frame)){
				now_frame_dancer = DANCER_MAIN;
			}
			else{
				now_frame_dancer = DANCER_BACK;
			}
			
			if(dancer_type == DANCER_MAIN){
				//メインダンサー
				//if(frame < md->dap.all_tempo_frame / 2){
				if(now_frame_dancer == DANCER_MAIN
						&& md->touch_count < md->dap.musicdata.touch_count
						&& (frame < md->dap.all_tempo_frame / 2 - (md->dap.one_tempo_frame / 2 / 2)/ONE_TEMPO_CALC_DECIMAL)){
						   //↑タッチした時バックダンサーの譜面に達するタイミングではタッチ無効
					DanceTouchCheck(&md->dtw, &tp_ret, FALSE, FALSE);
				}
				else{
					DanceTouchCheck(&md->dtw, &tp_ret, TRUE, TRUE);
				}
				
				if(tp_ret != RECT_HIT_NONE){
					DancerReactionSet(md->dpw->consys->c_game.my_breeder_no, tp_ret, frame, 
						md->dap.one_tempo_frame, &md->dap.musicdata.lag, 
						&dancing_param, NULL, rotation_pos,
						md->touch_count, md->dap.musicdata.touch_count);
					DancingParamSendReqSet(md->sendwork[md->dpw->consys->c_game.my_breeder_no], 
						&dancing_param);
					md->touch_count++;
				}
			}
			else{
				//バックダンサー
				//if(frame >= md->dap.all_tempo_frame / 2){
				if(now_frame_dancer == DANCER_BACK
						&& md->touch_count < md->dap.musicdata.touch_count
						&& (frame < md->dap.all_tempo_frame - (md->dap.one_tempo_frame / 2 / 2)/ONE_TEMPO_CALC_DECIMAL)){
						   //↑タッチした時バックダンサーの譜面に達するタイミングではタッチ無効
					DanceTouchCheck(&md->dtw, &tp_ret, FALSE, FALSE);
					if(md->flash_flag == 0){
						DT_FumenFlashEffectSet(md->dpw, dancer_type);
						md->flash_flag++;
					}
				}
				else{
					DanceTouchCheck(&md->dtw, &tp_ret, TRUE, TRUE);
				}
				
				if(tp_ret != RECT_HIT_NONE){
					DancerReactionSet(md->dpw->consys->c_game.my_breeder_no, tp_ret, frame, 
						md->dap.one_tempo_frame, &md->dap.musicdata.lag, 
						&dancing_param, md->dpw->maindancer_record, rotation_pos,
						md->touch_count, md->dap.musicdata.touch_count);
					DancingParamSendReqSet(md->sendwork[md->dpw->consys->c_game.my_breeder_no], 
						&dancing_param);
					md->touch_count++;
				}
			}
		}
		
		//AI計算
		{
			int i;
			for(i = md->dpw->consys->c_game.player_num; i < BREEDER_MAX; i++){
				DanceAI_Main(now_frame_dancer, md->dpw, &md->aiwork[i], frame, 
					md->dap.all_tempo_frame, md->dap.one_tempo_frame, 
					&md->dap.musicdata, md->sendwork[i]);
			}
		}

		//ライト設定(バックダンサー)
		if(now_frame_dancer == DANCER_BACK && md->back_dancer_light_flag == 0){
			DT_DancerLightEffectSet(md->dpw, md->dap.now_breeder, DANCER_BACK);
			md->back_dancer_light_flag++;
		}
		
		//バックダンサーの場合、メインダンサーの履歴を参照して半透明BGセット
		//if(dancer_type == DANCER_BACK && now_frame_dancer == DANCER_BACK){
		if(now_frame_dancer == DANCER_BACK){
			DT_BGAlphaEffectSet_MainDancerHistory(md->dpw, frame);
		}
		break;
	case 3:
		if(DanceTouchCheck(&md->dtw, &tp_ret, TRUE, FALSE) == TRUE){
			DT_OnpuActorDelAll(&md->dpw->sys);
			DT_MusicBarAnimeUpdateFrame(&md->dpw->sys, 0, md->dap.all_tempo_frame);
			PrinReq_OutMove(md->dpw->sys.prin_sys);
			DT_FumenColorSet(&md->dpw->sys, FUMENCOLOR_NULL);
			DT_BGAlphaEffectSet(md->dpw, DANCE_BGALPHA_TYPE_NULL);
			DT_FumenFlashTaskDel(md->dpw);
			
			if(DINPUT_MakeDataNoGet(md->dpw->dip) != DINPUT_TYPE_WALL){
				//DINPUT_CreateBG(md->dpw->dip, DINPUT_TYPE_WALL, TRUE, NULL);
				DINPUT_FadeSet(md->dpw->dip, DINPUT_COLOR_BLACK, DINPUT_BLACK_EVY);
			}
			
			md->seq++;
		}
		break;
	default:
		if(1){//Snd_FadeCheck() == 0){
			CO_ANSWER_TransmitBufferSet(md->cow, &md->req_head, NULL, 0);

			{
				int i;
				for(i = 0; i < BREEDER_MAX; i++){
					DancingParamSendTaskFree(md->sendwork[i]);
				}
			}

			sys_FreeMemoryEz(md);
			TCB_Delete(tcb);
			return;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ダンス操作でのタッチ反応チェック
 *
 * @param   dtw			
 * @param   tp_ret		タッチ反応結果代入先
 * @param   check		TRUE:待機状態かチェックする(タッチには反応させない)
 * @param   no_touch_bg	TRUE:タッチ出来ない時のBG状態にする(待機状態になっている時のみ有効)
 *
 * @retval  TRUE:待機中。　FALSE:処理中(エフェクト中など)
 */
//--------------------------------------------------------------
static int DanceTouchCheck(DANCE_TOUCH_WORK *dtw, int *tp_ret, int check, int no_touch_bg)
{
	int taiki;
	
	taiki = FALSE;
	*tp_ret = RECT_HIT_NONE;
	
	if(check == FALSE && dtw->touch_wait > 0){
		dtw->touch_wait--;
		if(dtw->touch_wait == 0){
			DINPUT_FadeSet(dtw->dpw->dip, DINPUT_COLOR_BLACK, DINPUT_NORMAL_EVY);
		}
	}
	
	switch(dtw->seq){
	case 0:
		if(check == FALSE && no_touch_bg == FALSE){
			dtw->touch_wait = 0;
			//DINPUT_CreateBG(dtw->dpw->dip, DINPUT_TYPE_COMMAND, TRUE, NULL);
			DINPUT_FadeSet(dtw->dpw->dip, DINPUT_COLOR_BLACK, DINPUT_NORMAL_EVY);
			dtw->seq++;
		}
		else{
			taiki = TRUE;
		}
		break;
	case 1:
		if(check == TRUE || dtw->touch_wait > 0){
			taiki = TRUE;
			break;		//チェックの時はあらたなタッチをさせない
		}
		
		*tp_ret = DINPUT_TouchCheck(dtw->dpw->dip);
		if(*tp_ret != RECT_HIT_NONE){
//			Snd_SePlay(DSE_DECIDE);
			dtw->touch_wait = dtw->dpw->d_game.one_tempo_frame / ONE_TEMPO_CALC_DECIMAL;
			dtw->touch_wait -= DANCE_TOUCH_WAIT_SUB_OFFSET;
			dtw->seq++;
		}
		else{
			taiki = TRUE;
		}
		break;
	case 2:
		if(DINPUT_EffectEndCheck(dtw->dpw->dip) == TRUE){
			if(dtw->touch_wait > 0){
				DINPUT_FadeSet(dtw->dpw->dip, DINPUT_COLOR_BLACK, DINPUT_BLACK_EVY);
			}
			dtw->seq = 1;
		}
		break;
	}
	
	if(no_touch_bg == TRUE && taiki == TRUE){
		if(DINPUT_MakeDataNoGet(dtw->dpw->dip) != DINPUT_TYPE_WALL){
			//DINPUT_CreateBG(dtw->dpw->dip, DINPUT_TYPE_WALL, TRUE, NULL);
			DINPUT_FadeSet(dtw->dpw->dip, DINPUT_COLOR_BLACK, DINPUT_BLACK_EVY);
			dtw->seq = 0;
		}
	}
	
	return taiki;
}

//--------------------------------------------------------------
/**
 * @brief   タッチパネル結果をダンスタイプに変換する
 * @param   dance_tp		DANCE_TP_???
 * @retval  DANCE_STEP_???
 */
//--------------------------------------------------------------
int DanceTP_to_DanceStep(int dance_tp)
{
	int dance_step;
	
	switch(dance_tp){
	case DANCE_TP_JUMP:
		dance_step = DANCE_STEP_JUMP;
		break;
	case DANCE_TP_ADVANCE:
		dance_step = DANCE_STEP_ADVANCE;
		break;
	case DANCE_TP_LEFT:
		dance_step = DANCE_STEP_LEFT;
		break;
	case DANCE_TP_RIGHT:
		dance_step = DANCE_STEP_RIGHT;
		break;
	default:
		GF_ASSERT(0 && "無効なリアクションです\n");
		return 0;
	}
	return dance_step;
}

//--------------------------------------------------------------
/**
 * @brief   タッチパネル結果をダンスタイプに変換する
 * @param   dance_tp		DANCE_STEP_???
 * @retval  DANCE_TP_???
 */
//--------------------------------------------------------------
int DanceStep_to_TP(int dance_step)
{
	int tp;
	
	switch(dance_step){
	case DANCE_STEP_JUMP:
		tp = DANCE_TP_JUMP;
		break;
	case DANCE_STEP_ADVANCE:
		tp = DANCE_TP_ADVANCE;
		break;
	case DANCE_STEP_LEFT:
		tp = DANCE_TP_LEFT;
		break;
	case DANCE_STEP_RIGHT:
		tp = DANCE_TP_RIGHT;
		break;
	default:
		GF_ASSERT(0 && "無効なリアクションです\n");
		return 0;
	}
	return tp;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスのずれから評価を取得する
 *
 * @param   lag				ダンスのずれ(拍子から何フレームずれているか)
 * @param   dld				ずれ比較データへのポインタ
 * @param   ret_review		評価タイプ代入先
 * @param   ret_lag			ラグタイプ代入先
 */
//--------------------------------------------------------------
static void DanceLagReviewTypeGet(int lag, const DANCE_LAG_DATA *dld, 
	u8 *ret_review, u8 *ret_lag)
{
	if(lag <= dld->excellent_a){
		*ret_review = REVIEW_TYPE_EXCELLENT;
		*ret_lag = DANCE_LAG_EXCELLENT_A;
	}
	else if(lag <= dld->excellent_b){
		*ret_review = REVIEW_TYPE_EXCELLENT;
		*ret_lag = DANCE_LAG_EXCELLENT_B;
	}
	else if(lag <= dld->good_a){
		*ret_review = REVIEW_TYPE_GOOD;
		*ret_lag = DANCE_LAG_GOOD_A;
	}
	else if(lag <= dld->good_b){
		*ret_review = REVIEW_TYPE_GOOD;
		*ret_lag = DANCE_LAG_GOOD_B;
	}
	else{
		*ret_review = REVIEW_TYPE_FAILED;
		*ret_lag = DANCE_LAG_FAILED;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ダンスしたフレームから対象となる小節と、
 *          その小節丁度のフレームから何フレームずれているか取得
 *
 * @param   frame				ダンスを実行した瞬間のフレーム
 * @param   one_tempo_frame		1小節にかかるフレーム数
 * @param   ret_lag				ずれ代入先(何フレーム拍子からずれているか)
 * @param   ret_beat			対象となった小節代入先
 */
//--------------------------------------------------------------
static void DancerLagBeatCheck(u32 frame, u32 one_tempo_frame, u32 *ret_lag, u32 *ret_beat)
{
	u32 just_frame, hit_frame, min_frame, big_frame, check_frame;
	u32 min_lag, big_lag;
	u32 hit_beat, lag;
	u32 half_tempo_frame;
	s64 calc_frame;
	
	hit_frame = frame * ONE_TEMPO_CALC_DECIMAL;
	half_tempo_frame = one_tempo_frame / 2;	//裏拍も取るため、1小節の半分にする
	
	min_frame = 0;
	hit_beat = 0;
	for(check_frame = 0; check_frame < hit_frame; check_frame += half_tempo_frame){
		min_frame = check_frame;
		hit_beat++;
	}
	big_frame = check_frame;
	
	//小数を四捨五入して正数化
	min_frame = (min_frame + ONE_TEMPO_CALC_DECIMAL / 2) / ONE_TEMPO_CALC_DECIMAL;
	big_frame = (big_frame + ONE_TEMPO_CALC_DECIMAL / 2) / ONE_TEMPO_CALC_DECIMAL;
	hit_frame /= ONE_TEMPO_CALC_DECIMAL;
	
	//ずれの少ない方を計算の対象とする
	calc_frame = hit_frame;	//u32のまま計算するとマイナスが取れないのでs64に移す
	min_lag = MATH_IAbs(calc_frame - min_frame);
	big_lag = MATH_IAbs(calc_frame - big_frame);
	if(min_lag <= big_lag){
		lag = min_lag;
		hit_beat--;
	}
	else{
		lag = big_lag;
	}
	
	*ret_lag = lag;
	*ret_beat = hit_beat;

	OS_TPrintf("min_lag = %d, big_lag = %d, min_frame = %d, big_frame = %d, hit_frame = %d, hit_beat = %d\n", min_lag, big_lag, min_frame, big_frame, hit_frame, hit_beat);
}

//--------------------------------------------------------------
/**
 * @brief   ダンサーがダンス実行時のリアクションパラメータセット
 *
 * @param   breeder_no		自分のブリーダー番号
 * @param   reaction		行ったダンス(DANCE_TP_???)
 * @param   frame			ダンスを実行したフレーム
 * @param   one_tempo_frame	1小節にかかるフレーム数
 * @param   dld				ずれ比較データへのポインタ
 * @param   param			リアクションパラメータ代入先へのポインタ
 * @param   maindancer_record	ダンスしているのがメインダンサーの場合はNULL指定
 *                              バックダンサーの場合はメインダンサーのダンス履歴へのポインタ
 * @param   rotation_pos	ローテーション位置
 * @param   touch_count		現在までにダンスした回数
 * @param   max_touch		ダンス出来る最大数
 */
//--------------------------------------------------------------
void DancerReactionSet(int breeder_no, int reaction, u32 frame, u32 one_tempo_frame, 
	const DANCE_LAG_DATA *dld, DANCING_PARAM *param, const DANCING_PARAM *maindancer_record,
	int rotation_pos, int touch_count, int max_touch)
{
	int dance_step, i;
	u8 review_type, lag_type;
	u32 lag, hit_beat, check_beat;
	u32 main_hit, button_failed = 0;
	
	//タッチパネル結果からダンスタイプを取得
	dance_step = DanceTP_to_DanceStep(reaction);
	
	//タッチしたフレームから対象となる小節と、その小節丁度のフレームから何フレームずれているか取得
	DancerLagBeatCheck(frame, one_tempo_frame, &lag, &hit_beat);
	OS_TPrintf("対象小節=%d, ずれ=%dフレーム\n", hit_beat, lag);
	
	if(maindancer_record != NULL){
		check_beat = hit_beat - DANCE_BEAT / 2;
		//バックダンサーの場合、メインダンサーのダンス履歴と比較を行う
		for(main_hit = 0; main_hit < DANCING_RECORD_MAX; main_hit++){
			if(maindancer_record[main_hit].occ == TRUE 
					&& maindancer_record[main_hit].hit_beat == check_beat){
				break;	//小節のメインダンサーの履歴にあったので今のずれデータを採用
			}
		}
		if(main_hit == DANCING_RECORD_MAX){
			lag = 0xff;	//ヒットした小節がなかったのでずれを最大にする(FAILED評価を得る為)
			OS_TPrintf("メインダンサーとヒットしなかったのでずれ最大\n");
		}
	}
	//ずれから評価を取得する
	DanceLagReviewTypeGet(lag, dld, &review_type, &lag_type);
	
	//バックダンサーの場合、さらにメインダンサーと同じボタンを押したかチェック
	if(maindancer_record != NULL && main_hit != DANCING_RECORD_MAX){
		switch(review_type){
		case REVIEW_TYPE_EXCELLENT:
		case REVIEW_TYPE_GOOD:
			if(maindancer_record[main_hit].dance_step != dance_step){
				lag = 0xff;		//違うボタンを押したのでずれ最大
				lag_type = DANCE_LAG_FAILED;
				review_type = REVIEW_TYPE_FAILED;
				button_failed = TRUE;
			}
			break;
		}
	}
	
	//パラメータセット
	param->breeder_no = breeder_no;
	param->frame = frame;
	param->dance_step = dance_step;
	param->review_type = review_type;
	param->lag_type = lag_type;
	param->hit_beat = hit_beat;
	param->rotation_pos = rotation_pos;
	param->finish = (touch_count >= max_touch-1) ? TRUE : FALSE;
	param->button_failed = button_failed;
	param->occ = TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ダンスを始める時のカウンタ初期化処理
 * @param   dpw		ダンス部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static void FumenCounterInit(DANCE_PROC_WORK *dpw)
{
	int i;
	for(i = 0; i < BREEDER_MAX; i++){
		dpw->sys.now_excellent_count[i] = 0;
		dpw->sys.now_failed_count[i] = 0;
	}
	dpw->sys.now_back_excellent_all_count = 0;
	dpw->sys.now_back_good_all_count = 0;
	dpw->sys.now_back_failed_all_count = 0;
}

//--------------------------------------------------------------
/**
 * @brief   返事受信(送信元)：メインダンス
 *
 * @param   dpw				ダンス部門管理ワークへのポインタ
 * @param   answer_head		返事ヘッダのポインタ
 * @param   ansdat			受信データへのポインタ
 */
//--------------------------------------------------------------
static void Answer_Dancing(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *answer_head, CO_ANSDAT *ansdat, int net_id)
{
	DANCE_PROC_WORK *dpw = syswork;
	
	//返事を受け取るだけなので特にする事がない
	return;
}
#endif	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：ローテーション
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_Rotation(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	DANCE_PROC_WORK *dpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(DANCE_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：ローテーション
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_Rotation(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	DANCE_PROC_WORK *dpw = syswork;
	DANCE_ADVANCE_PARAM *dap = data;
	DOLOCAL_ROTATION *rt;
	
	rt = sys_AllocMemory(HEAPID_DANCE, sizeof(DOLOCAL_ROTATION));
	MI_CpuClear8(rt, sizeof(DOLOCAL_ROTATION));

	rt->dpw = dpw;
	rt->req_head = *req_head;
	rt->cow = cow;
	rt->dap = *dap;
	
	TCB_Add(DOTCB_Rotation, rt, TCBPRI_DANCE_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   ポケモンローテーション
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		DOLOCAL_ROTATION構造体
 */
//--------------------------------------------------------------
static void DOTCB_Rotation(TCB_PTR tcb, void *work)
{
	DOLOCAL_ROTATION *rt = work;
	int breeder, i;
	
	switch(rt->seq){
	case 0:
		DT_MiddlePaletteOccSet(rt->dpw, FALSE);
		PaletteFadeReq(rt->dpw->sys.pfd, PF_BIT_MAIN_BG, DANCE_DISP_BG_FADE_BIT, 
			FADE_ROTATION_WAIT, 0, FADE_ROTATION_EVY, FADE_ROTATION_COLOR);
		for(i = 0; i < BREEDER_MAX; i++){
			DT_DancerLightFadeReq(rt->dpw, i, IMC_LIGHT_COLOR_NORMAL, IMC_LIGHT_COLOR_BLACK, 
				EVY_MAX, 4, &rt->light_fade_end[i]);
		}
		rt->seq++;
		break;
	case 1:
		if(PaletteFadeCheck(rt->dpw->sys.pfd) == 0){
			for(i = 0; i < BREEDER_MAX; i++){
				if(rt->light_fade_end[i] == FALSE){
					break;
				}
			}
			if(i == BREEDER_MAX){
				rt->seq++;
			}
		}
		break;
	case 2:
		for(i = 0; i < BREEDER_MAX; i++){
			breeder = rt->dap.breeder_rotation[i];
			rt->sub_rb[breeder].pp = rt->dpw->sys.c_game->pp[breeder];
			rt->sub_rb[breeder].ss = rt->dpw->sys.ss[breeder];
			rt->sub_rb[breeder].imcwork = &rt->dpw->sys.imcwork[breeder];
			rt->sub_rb[breeder].move_frame = 
				(rt->dpw->d_game.rotation_frame / ONE_TEMPO_CALC_DECIMAL) 
				* ROTATION_FRAME_PERCENT / 100;
			rt->sub_rb[breeder].now_rotation_pos = i;
			if(i == 0){
				rt->sub_rb[breeder].next_rotation_pos = DANCE_ROTATION_POS_D;
			}
			else{
				rt->sub_rb[breeder].next_rotation_pos = i - 1;
			}
			
			TCB_Add(DOTCB_RotationBreeder, &rt->sub_rb[breeder], TCBPRI_DANCE_ROTATION);
		}

	#if 0
		//次は自分がメインダンサーならばメッセージ表示
		if(rt->dap.a_talk_id != A_TALK_DANCE_NULL
				&& rt->dap.breeder_rotation[1] == rt->dpw->consys->c_game.my_breeder_no){
			BmpTalkWinWrite(&rt->dpw->sys.win[DANCE_BMPWIN_TALK], WINDOW_TRANS_OFF,
				DANCE_TALKWIN_CGX_OFFSET, DANCE_TALKWIN_PALNO);
			GF_BGL_LoadScreenV_Req(rt->dpw->sys.bgl, DANCE_FRAME_WIN);
			DT_A_TalkMessageSet(rt->dpw, rt->dap.a_talk_id, &rt->dap.a_talk_tagpara);
		}
	#endif
		//どこでダンスするのかをパネルメッセージで表示
		{
			DTAG_PARAM tagpara;
			tagpara.num = rt->dap.musicdata.touch_count;
			if(rt->dap.breeder_rotation[1] == rt->dpw->consys->c_game.my_breeder_no){
				DT_PanelMessagePut(rt->dpw, A_TALK_BEGIN_HOST_02, &tagpara);
			}
			else{
				DT_PanelMessagePut(rt->dpw, A_TALK_BEGIN_HOST_03, &tagpara);
			}
		}
		
		Snd_SePlay(DSE_ROTATION);
		rt->seq++;
		break;
	case 3:
		for(i = 0; i < BREEDER_MAX; i++){
			if(rt->sub_rb[i].end == FALSE){
				break;
			}
		}
		if(i == BREEDER_MAX){
			rt->seq++;
		}
		break;
	case 4:
		PaletteFadeReq(rt->dpw->sys.pfd, PF_BIT_MAIN_BG, DANCE_DISP_BG_FADE_BIT, 
			FADE_ROTATION_WAIT, FADE_ROTATION_EVY, 0, FADE_ROTATION_COLOR);
	#if 0
		if(rt->dap.a_talk_id != A_TALK_DANCE_NULL
				&& rt->dap.breeder_rotation[1] == rt->dpw->consys->c_game.my_breeder_no){
			if(DT_TalkMessageEndCheck(rt->dpw) == 0){
				BmpTalkWinClear(&rt->dpw->sys.win[DANCE_BMPWIN_TALK], WINDOW_TRANS_OFF);
				GF_BGL_LoadScreenV_Req(rt->dpw->sys.bgl, DANCE_FRAME_WIN);
				rt->seq++;
			}
		}
		else{
			rt->seq++;
		}
	#else
		rt->seq++;
	#endif
		break;
	case 5:
		if(PaletteFadeCheck(rt->dpw->sys.pfd) == 0){
			DT_MiddlePaletteOccSet(rt->dpw, TRUE);
			rt->seq++;
		}
		break;
	default:
		CO_ANSWER_TransmitBufferSet(rt->cow, &rt->req_head, NULL, 0);

		sys_FreeMemoryEz(rt);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ポケモンローテーション：各ブリーダー動作
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		DOLOCAL_ROTATION_BREEDER構造体
 */
//--------------------------------------------------------------
///ローテーションする時、どれだけ画面外に出すか(メインダンサー)
#define DANCE_ROTATION_OUT_X_MAIN		(100)
///ローテーションする時、どれだけ画面外に出すか(バックダンサー)
#define DANCE_ROTATION_OUT_X_BACK		(80)
static void DOTCB_RotationBreeder(TCB_PTR tcb, void *work)
{
	DOLOCAL_ROTATION_BREEDER *rtb = work;
	int now_x, now_y, now_z, end_x, end_y, end_z;
	int height;
	
	switch(rtb->seq){
	case 0:
//		rtb->x = SoftSpriteParaGet(rtb->ss, SS_PARA_POS_X) * 0x100;
//		rtb->y = SoftSpriteParaGet(rtb->ss, SS_PARA_POS_Y) * 0x100;
//		rtb->z = SoftSpriteParaGet(rtb->ss, SS_PARA_POS_Z) * 0x100;
		rtb->x = rtb->imcwork->x * 0x100;
		rtb->y = rtb->imcwork->y * 0x100;
		rtb->z = rtb->imcwork->z * 0x100;
		{
			now_x = DT_RotationPosGetX(rtb->now_rotation_pos) * 0x100;
			now_y = DT_RotationPosGetY(rtb->now_rotation_pos) * 0x100;
			now_z = DT_RotationPosGetZ(rtb->now_rotation_pos) * 0x100;
			if(rtb->next_rotation_pos == 0 || rtb->next_rotation_pos == BREEDER_MAX - 1){
				if(rtb->next_rotation_pos == 0){
					end_x = (0 - DANCE_ROTATION_OUT_X_BACK) * 0x100;
				}
				else{
					end_x = (256 + DANCE_ROTATION_OUT_X_MAIN) * 0x100;
				}
				end_y = now_y;
				end_z = now_z;
				rtb->add_x = (end_x - now_x) / (rtb->move_frame / 2);
				rtb->add_y = (end_y - now_y) / (rtb->move_frame / 2);
				rtb->add_z = (end_z - now_z) / (rtb->move_frame / 2);
			}
			else{
				end_x = DT_RotationPosGetX(rtb->next_rotation_pos) * 0x100;
				end_y = DT_RotationPosGetY(rtb->next_rotation_pos) * 0x100;
				end_z = DT_RotationPosGetZ(rtb->next_rotation_pos) * 0x100;
				rtb->add_x = (end_x - now_x) / rtb->move_frame;
				rtb->add_y = (end_y - now_y) / rtb->move_frame;
				rtb->add_z = (end_z - now_z) / rtb->move_frame;
			}
		}
		
		rtb->seq++;
		break;
	case 1:
		rtb->x += rtb->add_x;
		rtb->y += rtb->add_y;
		rtb->z += rtb->add_z;
		rtb->frame++;
		
		if(rtb->next_rotation_pos == 0 || rtb->next_rotation_pos == BREEDER_MAX - 1){
			if(rtb->frame == (rtb->move_frame / 2)){
				int check_frame;
				
				if(rtb->next_rotation_pos == 0){
					rtb->x = (0 - DANCE_ROTATION_OUT_X_MAIN) * 0x100;
					IMC_Player_SetAcceDrawFlag(rtb->imcwork->imc_ptr, TRUE);
					IMC_Player_AddPriority(rtb->imcwork->imc_ptr, -DANCE_BACK_IMC_ADD_PRI);
				}
				else{
					rtb->x = (DT_RotationPosGetX(rtb->next_rotation_pos) 
						+ DANCE_ROTATION_OUT_X_BACK) * 0x100;
					IMC_Player_SetAcceDrawFlag(rtb->imcwork->imc_ptr, FALSE);
					IMC_Player_AddPriority(rtb->imcwork->imc_ptr, DANCE_BACK_IMC_ADD_PRI);
				}
				height = PokeParaHeightGet(rtb->pp, PARA_FRONT);
				rtb->y = (DT_RotationPosGetY(rtb->next_rotation_pos) + height) * 0x100;
				rtb->z = DT_RotationPosGetZ(rtb->next_rotation_pos) * 0x100;

				end_x = DT_RotationPosGetX(rtb->next_rotation_pos) * 0x100;
				end_y = rtb->y;
				end_z = rtb->z;
				check_frame = rtb->move_frame - rtb->frame - 1;
				rtb->add_x = (end_x - rtb->x) / check_frame;
				rtb->add_y = (end_y - rtb->y) / check_frame;
				rtb->add_z = (end_z - rtb->z) / check_frame;
			}
		}
		
		if(rtb->frame >= rtb->move_frame){
			height = PokeParaHeightGet(rtb->pp, PARA_FRONT);
			rtb->x = DT_RotationPosGetX(rtb->next_rotation_pos) * 0x100;
			rtb->y = (DT_RotationPosGetY(rtb->next_rotation_pos) + height) * 0x100;
			rtb->z = DT_RotationPosGetZ(rtb->next_rotation_pos) * 0x100;
			rtb->seq++;
		}
//		SoftSpriteParaSet(rtb->ss, SS_PARA_POS_X, rtb->x / 0x100);
//		SoftSpriteParaSet(rtb->ss, SS_PARA_POS_Y, rtb->y / 0x100);
//		SoftSpriteParaSet(rtb->ss, SS_PARA_POS_Z, rtb->z / 0x100);
		rtb->imcwork->x = rtb->x / 0x100;
		rtb->imcwork->y = rtb->y / 0x100;
		rtb->imcwork->z = rtb->z / 0x100;
		IMC_Player_SetPokeMatrix(rtb->imcwork->imc_ptr, rtb->imcwork->x, rtb->imcwork->y);
		DT_PokeAffineUpdateZ(rtb->ss, rtb->imcwork);
		break;
	default:
		rtb->end = TRUE;
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：ダンス開始前
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_Before(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	DANCE_PROC_WORK *dpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(DANCE_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：ダンス開始前
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_Before(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	DANCE_PROC_WORK *dpw = syswork;
	DOLOCAL_BEFORE *db;
	DANCE_ADVANCE_PARAM *dap = data;
	
	db = sys_AllocMemory(HEAPID_DANCE, sizeof(DOLOCAL_BEFORE));
	MI_CpuClear8(db, sizeof(DOLOCAL_BEFORE));
	
	db->dpw = dpw;
	db->req_head = *req_head;
	db->cow = cow;
	db->dap = *dap;
	
	TCB_Add(DOTCB_Before, db, TCBPRI_DANCE_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   ダンス開始前に行う処理
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		DOLOCAL_BEFORE構造体
 */
//--------------------------------------------------------------
static void DOTCB_Before(TCB_PTR tcb, void *work)
{
	DOLOCAL_BEFORE *db = work;
	int i;
	
	switch(db->seq){
	case 0:
		for(i = 0; i < BREEDER_MAX; i++){
			DT_PokemonDefaultAnimeTaskSet(db->dpw, db->dap.breeder_rotation[i], i);
		}

		DINPUT_CreateBG(db->dpw->dip, DINPUT_TYPE_COMMAND, TRUE, NULL);
		DINPUT_FadeSet(db->dpw->dip, DINPUT_COLOR_BLACK, DINPUT_BLACK_EVY);

		db->seq++;
		break;
	default:
		CO_ANSWER_TransmitBufferSet(db->cow, &db->req_head, NULL, 0);

		sys_FreeMemoryEz(db);
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：ダンス終了後
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_After(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	DANCE_PROC_WORK *dpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(DANCE_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：ダンス終了後
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_After(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	DANCE_PROC_WORK *dpw = syswork;
	DOLOCAL_AFTER *da;
	DANCE_ADVANCE_PARAM *dap = data;
	
	da = sys_AllocMemory(HEAPID_DANCE, sizeof(DOLOCAL_AFTER));
	MI_CpuClear8(da, sizeof(DOLOCAL_AFTER));
	
	da->dpw = dpw;
	da->req_head = *req_head;
	da->cow = cow;
	da->dap = *dap;
	
	TCB_Add(DOTCB_After, da, TCBPRI_DANCE_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   ダンス終了後に行う処理
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		DOLOCAL_AFTER構造体
 */
//--------------------------------------------------------------
static void DOTCB_After(TCB_PTR tcb, void *work)
{
	DOLOCAL_AFTER *da = work;
	int i;
	
	switch(da->seq){
	case 0:
		if(DT_DanceMoveStepNoneAllCheck(da->dpw) == FALSE){
			break;
		}
		
		for(i = 0; i < BREEDER_MAX; i++){
			DT_PokemonDefaultAnimeReq(da->dpw, i, PDA_REQ_AFF_STOP_REQ);
			DT_PokemonDefaultAnimeReq(da->dpw, i, PDA_REQ_MOVE_STOP_REQ);
		}
		da->seq++;
		break;
	case 1:
		{
			int aff_end = 0, move_end = 0;
			
			for(i = 0; i < BREEDER_MAX; i++){
				if(DT_PokemonDefaultAnimeStopCheckAff(da->dpw, i) == TRUE){
					aff_end++;
				}
				if(DT_PokemonDefaultAnimeStopCheckMove(da->dpw, i) == TRUE){
					move_end++;
				}
			}
			if(aff_end >= BREEDER_MAX && move_end >= BREEDER_MAX){
				DT_PokemonDefaultAnimeTaskDelAll(da->dpw);
				da->seq++;
			}
		}
		break;
	default:
		DINPUT_CreateBG(da->dpw->dip, DINPUT_TYPE_WALL, TRUE, NULL);
		DINPUT_FadeSet(da->dpw->dip, DINPUT_COLOR_BLACK, DINPUT_NORMAL_EVY);

		CO_ANSWER_TransmitBufferSet(da->cow, &da->req_head, NULL, 0);

		sys_FreeMemoryEz(da);
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
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_Talk(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	DANCE_PROC_WORK *dpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(DANCE_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：会話メッセージの表示
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_Talk(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	DANCE_PROC_WORK *dpw = syswork;
	DANCE_ADVANCE_PARAM *dap = data;
	DOLOCAL_TALK_PUT *talk;
	
	talk = sys_AllocMemory(HEAPID_DANCE, sizeof(DOLOCAL_TALK_PUT));
	MI_CpuClear8(talk, sizeof(DOLOCAL_TALK_PUT));
	
	talk->dpw = dpw;
	talk->req_head = *req_head;
	talk->cow = cow;
	talk->breeder_no = dap->now_breeder;
	
	talk->a_talk_tagpara = dap->a_talk_tagpara;
	talk->a_talk_id = dap->a_talk_id;
	talk->a_talk_bmpwin_not_close = dap->a_talk_bmpwin_not_close;
	talk->a_talk_bmpwin_close_wait = dap->a_talk_bmpwin_close_wait;
	
	TCB_Add(DOTCB_TalkPut, talk, TCBPRI_DANCE_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   会話メッセージの表示
 * @param   tcb			TCBへのポインタ
 * @param   work		DOLOCAL_TALK_PUT構造体
 */
//--------------------------------------------------------------
static void DOTCB_TalkPut(TCB_PTR tcb, void *work)
{
	DOLOCAL_TALK_PUT *talk = work;
	
	switch(talk->seq){
	case 0:
		if(talk->a_talk_id != A_TALK_DANCE_NULL){
			BmpTalkWinWrite(&talk->dpw->sys.win[DANCE_BMPWIN_TALK], WINDOW_TRANS_OFF,
				DANCE_TALKWIN_CGX_OFFSET, DANCE_TALKWIN_PALNO);
			GF_BGL_LoadScreenV_Req(talk->dpw->sys.bgl, DANCE_FRAME_WIN);

			DT_A_TalkMessageSet(talk->dpw, talk->a_talk_id, &talk->a_talk_tagpara);
			talk->seq++;
		}
		else{
			talk->seq = 100;
		}
		break;
	case 1:
		if(DT_TalkMessageEndCheck(talk->dpw) == 0){
			talk->seq++;
		}
		break;
	case 2:
		talk->close_wait++;
		if(talk->a_talk_bmpwin_not_close == TRUE){
			talk->seq++;
		}
		else if(talk->close_wait >= talk->a_talk_bmpwin_close_wait){
			BmpTalkWinClear(&talk->dpw->sys.win[DANCE_BMPWIN_TALK], WINDOW_TRANS_OFF);
			GF_BGL_LoadScreenV_Req(talk->dpw->sys.bgl, DANCE_FRAME_WIN);
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
 * @brief   命令送信(送信元)：ゲームパラメータ更新
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_GameParam(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	DANCE_PROC_WORK *dpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, work, sizeof(DANCE_GAME_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：ゲームパラメータ更新
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_GameParam(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	DANCE_PROC_WORK *dpw = syswork;
	
	dpw->d_game = *((DANCE_GAME_PARAM *)data);
	
	//返事を返す	バッファは特に渡すものがないのでNULL指定
	CO_ANSWER_TransmitBufferSet(cow, req_head, NULL, 0);
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：音楽開始
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_MusicStart(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	DANCE_PROC_WORK *dpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(DANCE_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：音楽開始
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_MusicStart(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	DANCE_PROC_WORK *dpw = syswork;
	DANCE_ADVANCE_PARAM *dap = data;
	
//	Snd_BgmStop(SEQ_CON_TEST, 0);
	Snd_Stop();
	Snd_BgmPlay(dap->musicdata.music_id);
	dpw->music_vcount_flag = TRUE;
	dpw->music_vcount_start = dpw->music_vcount;
	
	//返事を返す	バッファは特に渡すものがないのでNULL指定
	CO_ANSWER_TransmitBufferSet(cow, req_head, NULL, 0);
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   命令送信(送信元)：全員のダンス終了後のエフェクトなど
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   work		任意のポインタ
 *
 * @retval  登録されたリクエストビット番号
 */
//--------------------------------------------------------------
static int Request_EndEffect(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	DANCE_PROC_WORK *dpw = syswork;
	int bit_no;
	
	bit_no = CO_REQUEST_TransmitBufferSet(cow, CSELECT_ALL, order_no, 
		work, sizeof(DANCE_ADVANCE_PARAM));
	return bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   命令受信(送信先)：全員のダンス終了後のエフェクトなど
 *
 * @param   dpw			ダンス部門管理ワークへのポインタ
 * @param   req_head	リクエストヘッダのポインタ
 * @param   data		受信データへのポインタ
 */
//--------------------------------------------------------------
static void Recieve_EndEffect(CONTEST_ORDER_WORK *cow, void *syswork, const CORDER_HEAD *req_head, void *data)
{
	DANCE_PROC_WORK *dpw = syswork;
	DANCE_ADVANCE_PARAM *dap = data;
	DOLOCAL_END_EFFECT *ee;
	
	ee = sys_AllocMemory(HEAPID_DANCE, sizeof(DOLOCAL_END_EFFECT));
	MI_CpuClear8(ee, sizeof(DOLOCAL_END_EFFECT));
	
	ee->dpw = dpw;
	ee->req_head = *req_head;
	ee->cow = cow;
	
	ee->dap = *dap;
	
	TCB_Add(DOTCB_EndEffect, ee, TCBPRI_DANCE_ORDERSUB);
}

//--------------------------------------------------------------
/**
 * @brief   全員のダンス終了後のエフェクトなど
 * @param   tcb			TCBへのポインタ
 * @param   work		DOLOCAL_END_EFFECT構造体
 */
//--------------------------------------------------------------
static void DOTCB_EndEffect(TCB_PTR tcb, void *work)
{
	DOLOCAL_END_EFFECT *ee = work;
	
	switch(ee->seq){
	case 0:
		ee->dpw->music_vcount_flag = FALSE;
//		Snd_BgmStop(ee->dpw->d_game.music_id, EE_DANCEMUSIC_FADEOUT_FRAME);
		ee->seq++;
		break;
	case 1:
//		if(Snd_FadeCheck() == 0){
		if(Snd_BgmPlayCheck(ee->dap.musicdata.music_id) == FALSE){
			ee->seq++;
		}
		break;
	case 2:
		DT_DancerLightRankingSet(ee->dpw);
		ee->seq++;
		break;
	case 3:
		ee->wait++;
		if(ee->wait > EE_RANKING_AFTER_WAIT){
			ee->wait = 0;
			ee->seq++;
		}
		break;
	case 4:
		Snd_BgmPlay(SEQ_CON_TEST);//dap->musicdata.music_id);
		Snd_SePlay(DSE_END_SHOUT);
		ee->seq++;
		break;
	
	default:
		CO_ANSWER_TransmitBufferSet(ee->cow, &ee->req_head, NULL, 0);

		sys_FreeMemoryEz(ee);
		TCB_Delete(tcb);
		return;
	}
}

