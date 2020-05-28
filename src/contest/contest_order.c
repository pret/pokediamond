//==============================================================================
/**
 * @file	contest_order.c
 * @brief	コンテスト通信送受信
 * @author	matsuda
 * @date	2005.12.13(火)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "battle/battle_common.h"
#include "contest_order.h"
#include "communication/communication.h"
#include "comm_command_contest.h"


//==============================================================================
//	定数定義
//==============================================================================
///同時に命令を出せる数(同フレームに出せる命令は1つ)
#define CONTEST_ORDER_SAME_MAX		(32)

///送信タイプ
enum{
	TRANSMIT_TYPE_REQUEST,		///<命令
	TRANSMIT_TYPE_ANSWER,		///<返事
};



//--------------------------------------------------------------
/**
 * @brief   コンテスト送受信ワーク初期化
 *
 * @param   cow				コンテスト送受信ワークへのポインタ
 * @param   initdata		初期化データ
 */
//--------------------------------------------------------------
void CO_WorkInit(CONTEST_ORDER_WORK *cow, const CO_INIT_DATA *initdata)
{
	MI_CpuClear8(cow, sizeof(CONTEST_ORDER_WORK));
	cow->func_tbl = initdata->func_tbl;
	cow->func_tbl_max = initdata->func_tbl_max;
	cow->my_breeder_no = initdata->my_breeder_no;
	cow->sio_flag = initdata->sio_flag;
	cow->server_no = initdata->server_no;
}


//--------------------------------------------------------------
/**
 * @brief   リクエストビットをセットする
 * @param   apw		演技力部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
static int CO_RequestBitSet(CONTEST_ORDER_WORK *cow)
{
	int bit_no;

	for(bit_no = 0; bit_no < CONTEST_ORDER_SAME_MAX; bit_no++){
		if((cow->request_bit & (1 << bit_no)) == 0){
			cow->request_bit |= 1 << bit_no;
			return bit_no;
		}
	}
	
	GF_ASSERT(0 && "最大同時送信命令数を超えています\n");
	return 0;
}

//--------------------------------------------------------------
/**
 * @brief   指定のリクエストビットをリセットする
 *
 * @param   syswork		各部門管理ワークへのポインタ
 * @param   bit_no		ビット番号
 */
//--------------------------------------------------------------
static void CO_RequestBitReset(CONTEST_ORDER_WORK *cow, int bit_no)
{
	cow->request_bit &= 0xffffffff ^ (1 << bit_no);
}

//--------------------------------------------------------------
/**
 * @brief   リクエストビットがいくつ立っているかチェックする
 * @param   apw		演技力部門管理ワークへのポインタ
 * @retval  立っているビット数
 */
//--------------------------------------------------------------
u8 CO_RequestBitNumCheck(CONTEST_ORDER_WORK *cow)
{
	return MATH_CountPopulation(cow->request_bit);
}

//--------------------------------------------------------------
/**
 * @brief   指定ビット番号のリクエストビットが立っているか確認
 *
 * @param   syswork		各部門管理ワークへのポインタ
 * @param   bit_no		ビット番号
 *
 * @retval  TRUE:ビットが立っている。　FALSE:ビットが落ちている
 */
//--------------------------------------------------------------
BOOL CO_RequestBitCheck(CONTEST_ORDER_WORK *cow, int bit_no)
{
	if(cow->request_bit & (1 << bit_no)){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   送信バッファに送信データをセット
 *
 * @param   apw					演技力部門管理ワークへのポインタ
 * @param   select_breeder		対象ブリーダー
 * @param   order_no			命令番号
 * @param   data				送信データのポインタ(ない場合はNULL)
 * @param   data_size			送信データサイズ
 * 
 * @retval	登録されたリクエストビット番号
 */
//--------------------------------------------------------------
int CO_REQUEST_TransmitBufferSet(CONTEST_ORDER_WORK *cow, u8 select_breeder, u16 order_no, void *data, int data_size)
{
	CORDER_HEAD trans_head;
	
//	OS_TPrintf("送信バッファにセットしたデータのサイズ＝%d\n", data_size);
	GF_ASSERT(sizeof(CORDER_HEAD) + data_size <= CO_TRANSMIT_BUF_SIZE);
	
	//送信バッファクリア
	MI_CpuClear8(cow->transmit_buf, CO_TRANSMIT_BUF_SIZE);

	//ヘッダ作成
	trans_head.select_breeder = select_breeder;
	trans_head.order_no = order_no;
	trans_head.bit_no = CO_RequestBitSet(cow);
	trans_head.type = TRANSMIT_TYPE_REQUEST;
	trans_head.data_size = data_size + sizeof(CORDER_HEAD);
	
	//データセット
	MI_CpuCopy32(&trans_head, cow->transmit_buf, sizeof(CORDER_HEAD));
	MI_CpuCopy8(data, &cow->transmit_buf[sizeof(CORDER_HEAD)], data_size);
	
	cow->answer_count = 0;
	cow->transmit_flag = TRUE;
	
	return trans_head.bit_no;
}

//--------------------------------------------------------------
/**
 * @brief   送信バッファに返事データをセット
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   req_head		リクエストヘッダのポインタ
 * @param   data			送信データのポインタ(ない場合はNULL)
 * @param   data_size		送信データサイズ
 */
//--------------------------------------------------------------
void CO_ANSWER_TransmitBufferSet(CONTEST_ORDER_WORK *cow, const CORDER_HEAD *req_head, void *data, int data_size)
{
	CORDER_HEAD answer_head;
	
	GF_ASSERT(sizeof(CORDER_HEAD) + data_size <= CO_TRANSMIT_BUF_SIZE);
	
	//送信バッファクリア
	MI_CpuClear8(cow->transmit_buf, CO_TRANSMIT_BUF_SIZE);

	//ヘッダ作成
	answer_head = *req_head;
	answer_head.select_breeder = CSELECT_SERVER;
	answer_head.type = TRANSMIT_TYPE_ANSWER;
	answer_head.data_size = data_size + sizeof(CORDER_HEAD);
	
	//データセット
	MI_CpuCopy32(&answer_head, cow->transmit_buf, sizeof(CORDER_HEAD));
	if(data != NULL){
		MI_CpuCopy8(data, &cow->transmit_buf[sizeof(CORDER_HEAD)], data_size);
	}
	
	cow->transmit_flag = TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   受信バッファからヘッダデータのアドレスと、データバッファのアドレスを取り出す
 *
 * @param   syswork		各部門管理ワークへのポインタ
 * @param   net_id		取得するバッファのネットID
 * @param   req_head	送受信ヘッダのポインタを代入するポインタ
 * @param   data		受信データへのポインタを代入するポインタ
 */
//--------------------------------------------------------------
static void CO_RECIEVE_BufferDataGet(CONTEST_ORDER_WORK *cow, int net_id, CORDER_HEAD **req_head, void **data)
{
	*req_head = (void*)cow->receive_buf[net_id];
	*data = &cow->receive_buf[net_id][sizeof(CORDER_HEAD)];
}

//--------------------------------------------------------------
/**
 * @brief   命令送信が出来る状態かチェック
 *
 * @param   apw		演技力部門管理ワークへのポインタ
 *
 * @retval  TRUE:出来る。　FALSE:出来ない
 */
//--------------------------------------------------------------
static BOOL COSub_OrderPossibleCheck(CONTEST_ORDER_WORK *cow)
{
	if(cow->transmit_flag == TRUE){
		return FALSE;
	}
	
	if(cow->sio_flag == FALSE){
		return TRUE;
	}
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   命令送信コマンドを実行する
 *
 * @param   syswork		各部門管理ワークへのポインタ
 * @param   order_no	命令番号(AORDER_NO_???)
 * @param   work		任意のポインタ
 *
 * @retval  TRUE:送信成功。　FALSE:送信待ち
 */
//--------------------------------------------------------------
int CO_OrderSet(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work)
{
	if(COSub_OrderPossibleCheck(cow) == FALSE){
		return FALSE;
	}
	
	GF_ASSERT(order_no < cow->func_tbl_max);
	cow->func_tbl[order_no].request_func(cow, syswork, order_no, work);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   select_breederで指定されているのが自分なのかチェックする
 *
 * @param   my_breeder_no		自分のブリーダー番号
 * @param   server_no			サーバーのブリーダー番号
 * @param   select_breeder		選択ブリーダー
 *
 * @retval  TRUE:自分。　FALSE:自分ではない
 */
//--------------------------------------------------------------
static BOOL COSub_SelectBreederCheck(int my_breeder_no, int server_no, int select_breeder)
{
	if(my_breeder_no == select_breeder || select_breeder == CSELECT_ALL
			|| (select_breeder == CSELECT_SERVER && server_no == my_breeder_no)){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   送信バッファにデータが格納されていれば送信を行う
 *
 * @param   apw		演技力部門管理ワークへのポインタ
 *
 * @retval  TRUE:送信した。　FALSE:送信していない
 */
//--------------------------------------------------------------
BOOL CO_TransmitCheckExe(CONTEST_ORDER_WORK *cow)
{
	if(cow->transmit_flag == FALSE){
		return FALSE;
	}
	
	if(cow->sio_flag == FALSE){
		//自分だけ受信
		MI_CpuCopy8(cow->transmit_buf, cow->receive_buf[cow->my_breeder_no], CO_TRANSMIT_BUF_SIZE);
		cow->receive_flag[cow->my_breeder_no] = TRUE;

		MI_CpuClear8(cow->transmit_buf, CO_TRANSMIT_BUF_SIZE);
		cow->transmit_flag = FALSE;
		return TRUE;
	}
	else{
		CORDER_HEAD *chead;
		
		chead = (void*)cow->transmit_buf;
	#if DEBUG_SIO_WAIT
		if((gf_rand() % 10) != 0){
			return FALSE;
		}
	#endif
//		if(CommSendData(CC_NORMAL_DATA, cow->transmit_buf, chead->data_size) == TRUE){
		if(CommSendHugeData(CC_NORMAL_DATA, cow->transmit_buf, chead->data_size) == TRUE){
			OS_TPrintf("データ送信成功\n");
			//↓HugeDataで送信する場合は送信が終わるまで保持する必要があるのでクリアしない
			//MI_CpuClear8(cow->transmit_buf, CO_TRANSMIT_BUF_SIZE);
			cow->transmit_flag = FALSE;
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   命令コマンドを受信したか確認し、受信していれば実行
 *
 * @param   apw		演技力部門管理ワークへのポインタ
 *
 * @retval  TRUE:命令実行した。　FALSE:受信なし
 */
//--------------------------------------------------------------
int CO_RecieveCheckExe(CONTEST_ORDER_WORK *cow, void *syswork)
{
	CORDER_HEAD *req_head;
	void *data;
	CO_ANSDAT ansdat;
	int i;
	
	MI_CpuClear8(&ansdat, sizeof(CO_ANSDAT));
	
	if(1){	//cow->sio_flag == FALSE){
		for(i = 0; i < CC_NETID_MAX; i++){
			if(cow->receive_flag[i] == TRUE){
				//受信データ取得
				CO_RECIEVE_BufferDataGet(cow, i, &req_head, &data);
				//自分が対象に含まれているか確認
				if(COSub_SelectBreederCheck(cow->my_breeder_no, 
						cow->server_no, req_head->select_breeder) == TRUE){
					//命令コマンドが用意されているか確認
					if(req_head->order_no < cow->func_tbl_max){
						//受信命令実行
						if(req_head->type == TRANSMIT_TYPE_REQUEST){
							cow->func_tbl[req_head->order_no].receive_func(cow, syswork, req_head, data);
						}
						else{
							if(cow->func_tbl[req_head->order_no].answer_func != NULL){
								ansdat.data[i] = data;
								cow->func_tbl[req_head->order_no].answer_func(cow, syswork, req_head, &ansdat, i);
							}
							//返事が来たのでビット落とす
							CO_RequestBitReset(cow, req_head->bit_no);
							//返事が来たのでカウントインクリメント
							cow->answer_count++;
						}
					}
					else{
						OS_TPrintf("用意されていない命令番号を受信したので何もせずに無視します\n");
					}
				}
				
				//受信バッファクリア
				cow->receive_flag[i] = FALSE;
				MI_CpuClear8(cow->receive_buf[i], CO_RECEIVE_BUF_SIZE);
				return TRUE;
			}
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   返事受信カウントが指定数に達しているかチェック
 *
 * @param   cow				コンテスト送受信ワークへのポインタ
 * @param   answer_num		指定受信人数
 * @param   my_breeder		自分のブリーダー番号
 * @param   server_breeder	サーバーのブリーダー番号
 *
 * @retval  TRUE:受信している。　FALSE：指定数に達していない
 *
 * サーバー専用命令です。子機が呼んだ場合は常にTRUEが返ります。
 */
//--------------------------------------------------------------
BOOL CO_AnswerCountCheck(CONTEST_ORDER_WORK *cow, int answer_num, int my_breeder, int server_breeder)
{
	if(my_breeder != server_breeder){
		return TRUE;	//サーバー専用命令なので、自分がサーバーでない時は常に結果はTRUE
	}
	
	if(cow->answer_count >= answer_num){
		return TRUE;
	}
	return FALSE;
}
