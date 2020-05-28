//==============================================================================
/**
 * @file	contest_order.h
 * @brief	コンテスト通信送受信のヘッダ
 * @author	matsuda
 * @date	2005.12.13(火)
 */
//==============================================================================
#ifndef __CONTEST_ORDER_H__
#define __CONTEST_ORDER_H__


//==============================================================================
//	定数定義
//==============================================================================
///select_breederのパラメータ
enum{
	CSELECT_ALL = 0xff,		///<全員が対象
	CSELECT_SERVER = 0xfe,	///<サーバーが対象
};

///送信用バッファサイズ
#define CO_TRANSMIT_BUF_SIZE		(512)
///受信用バッファサイズ
#define CO_RECEIVE_BUF_SIZE		(CO_TRANSMIT_BUF_SIZE)


//==============================================================================
//	構造体定義
//==============================================================================
///コンテスト送受信構造体
typedef struct{
	const struct _CON_ORDER_FUNC *func_tbl;		///<命令データテーブルへのポインタ
	u16 func_tbl_max;				///<func_tblの数
	
	u8 my_breeder_no;
	u8 sio_flag;					///<TRUE：通信中
	u8 server_no;					///<サーバーのブリーダー番号
	
	u32 request_bit;				///<命令を出しているビット
	u8 transmit_buf[CO_TRANSMIT_BUF_SIZE];	///<送信用バッファ
	u8 receive_buf[CC_NETID_MAX][CO_RECEIVE_BUF_SIZE];	///<受信用バッファ
	u8 transmit_flag;				///<TRUE：送信待ち。　FALSE:新たなデータセット可能
	u8 receive_flag[CC_NETID_MAX];				///<TRUE：データ受信した
	u8 answer_count;				///<返事を受け取った数をカウント
}CONTEST_ORDER_WORK;

///返事受信バッファをまとめた構造体
typedef struct{
	void *data[BREEDER_MAX];
}CO_ANSDAT;

//--------------------------------------------------------------
/**
 * 送信用バッファのヘッダ
 */
//--------------------------------------------------------------
typedef struct{
	u16 data_size;			///<送信データサイズ
	u16 order_no;			///<命令番号
	u8 select_breeder;		///<命令対象のブリーダー番号 or ASELECT_???
	u8 bit_no;				///<リクエストビット番号
	u8 type;				///<送信タイプ(TRANSMIT_TYPE_???)
	
	u8 dummy[1];
}CORDER_HEAD;

///命令送受信用関数ポインタ構造体
typedef struct _CON_ORDER_FUNC{
	///命令送信関数(送信元)
	int (* request_func)(CONTEST_ORDER_WORK *, void *, int, void *);
	///命令受信関数(送信先)
	void (* receive_func)(CONTEST_ORDER_WORK *, void *, const CORDER_HEAD *, void *);
	///返事受信関数(送信元) 返事を受け取るだけでデータの受け取りがないならNULLでOK
	void (* answer_func)(CONTEST_ORDER_WORK *, void *, const CORDER_HEAD *, CO_ANSDAT *, int);
}CON_ORDER_FUNC;

///送受信ワーク初期化データ
typedef struct{
	const struct _CON_ORDER_FUNC *func_tbl;		///<命令データテーブルへのポインタ
	u16 func_tbl_max;				///<func_tblの数
	
	u8 my_breeder_no;
	u8 sio_flag;					///<TRUE：通信中
	u8 server_no;					///<サーバーのブリーダー番号
}CO_INIT_DATA;


//==============================================================================
//	外部関数宣言
//==============================================================================
extern u8 CO_RequestBitNumCheck(CONTEST_ORDER_WORK *cow);
extern BOOL CO_RequestBitCheck(CONTEST_ORDER_WORK *cow, int bit_no);
extern int CO_OrderSet(CONTEST_ORDER_WORK *cow, void *syswork, int order_no, void *work);
extern BOOL CO_TransmitCheckExe(CONTEST_ORDER_WORK *cow);
extern int CO_RecieveCheckExe(CONTEST_ORDER_WORK *cow, void *syswork);
extern int CO_REQUEST_TransmitBufferSet(CONTEST_ORDER_WORK *cow, u8 select_breeder, u16 order_no, void *data, int data_size);
extern void CO_ANSWER_TransmitBufferSet(CONTEST_ORDER_WORK *cow, const CORDER_HEAD *req_head, void *data, int data_size);
extern void CO_WorkInit(CONTEST_ORDER_WORK *cow, const CO_INIT_DATA *initdata);
extern BOOL CO_AnswerCountCheck(CONTEST_ORDER_WORK *cow, int answer_num, int my_breeder, int server_breeder);



#endif	//__CONTEST_ORDER_H__

