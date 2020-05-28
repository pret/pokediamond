//=============================================================================
/**
 * @file	comm_command_record.c
 * @brief	データを送るためのコマンドをテーブル化しています
 *          レコードコーナー用です
 * @author	Akito Mori
 * @date    2006.03.27
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "system/procsys.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "system/bmp_menu.h"
#include "application/record_corner.h"
#include "system/snd_tool.h"

typedef struct RECORD_WORK RECORD_WORK;

#include "record_corner_local.h"


#include "comm_command_record.h"

#include "communication/wh.h"



static int _getZero(void);
static int _getOne(void);
static int _getRecordSize(void);
static u8* _getRecordRecvBuf( int netID, void* pWork, int size );
static int _getCRECW(void);


static void RecordCorner_DataSend( RECORD_WORK *wk, int no);
void CommRecord_RecordData( int netID, int size, void* pBuff, void* pWork );
void CommRecordBanFlag( int netID, int size, void* pBuff, void* pWork );


// 対応するコールバック関数
static const CommPacketTbl _CommPacketTbl[] = {
    { CommDummyCallBack, _getZero, NULL},// comm_command_field.cで登録されているコマンドテーブルの無効化するために
    { CommDummyCallBack, _getZero, NULL},// 登録する
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},	// comm_command_field.cで登録されているコマンドテーブルの無効化するために
    { CommDummyCallBack, _getZero, NULL}, // 登録する

	// レコードが使用するコマンド部分
	{CommRecordCornerYes,   		_getOne},              	// CR_RECORD_YES  		 はい
	{CommRecordCornerNo,   	   	 	_getOne},             	// CR_RECORD_NO,		 いいえ
    {CommRecordCornerStop,			_getOne},             	// CR_RECORD_STOP,		 乱入者が来たので一旦ストップ
    {CommRecordCornerReStart,		_getZero},             	// CR_RECORD_RESTART,	 乱入者処理が終わったので再会
    {CommRecordCornerEndChild,		_getCRECW},            	// CR_RECORD_END_CHILD,	 子機が離脱
    {CommRecordCornerEnd,			_getZero},              // CR_RECORD_END,		 終了
	{CommRecordCornerChildJoin,		_getZero},				// CR_RECORD_CHILD_JOIN, 子機が乱入を宣言
	{CommRecordStart,				_getZero},				// CR_RECORD_START, 	 レコード交換開始を親が通達
	{CommRecord_RecordData,			_getRecordSize, _getRecordRecvBuf},// CR_RECORD_DATA, 	 レコード交換開始を親が通達
	{CommRecordBanFlag,				_getOne},				// CR_RECORD_BAN		離脱禁止通達

	// おえかきのコマンドを無視するための部分
	{ CommDummyCallBack, _getZero, NULL},
	{ CommDummyCallBack, _getZero, NULL},
	{ CommDummyCallBack, _getZero, NULL},
	{ CommDummyCallBack, _getZero, NULL},
	{ CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
	{ CommDummyCallBack, _getZero, NULL},
	{ CommDummyCallBack, _getZero, NULL},

};


//==============================================================================
/**
 * お絵かきボード用通信コマンド登録処理
 *
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommCommandRecordInitialize(void* pWork)
{
	RECORD_WORK *wk = (RECORD_WORK *)pWork;

	int i;
	
	// 受信コールバック設定
    int length = sizeof(_CommPacketTbl)/sizeof(CommPacketTbl);
    CommCommandInitialize(_CommPacketTbl, length, pWork);


	// 巨大データ受信バッファ設定
	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
//		CommSetSpritDataRecvBuff( i, &wk->recv_data[i], sizeof(RECORD_DATA) );
	}
}


//==============================================================================
/**
 * $brief   レコードデータ受信コールバック関数
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommRecord_RecordData( int netID, int size, void* pBuff, void* pWork )
{
	RECORD_WORK *wk = (RECORD_WORK *)pWork;

	wk->recv_count++;

	OS_Printf("レコードデータ受信完了 id=%d\n",netID);
}

//==============================================================================
/**
 * @brief   離脱制御フラグ到着
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommRecordBanFlag( int netID, int size, void* pBuff, void* pWork )
{
	RECORD_WORK *wk = (RECORD_WORK *)pWork;
	u8  *flag        = (u8*)pBuff;

	if(netID==0){
		if(wk->banFlag != *flag){
			OS_Printf("親機からの離脱禁止フラグ banFlag=%d\n",*flag);
		}
		wk->banFlag = *flag;
	}
	
}


//------------------------------------------------------------------
/**
 * $brief   レコード交換開始
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void CommRecordStart(int netID, int size, void* pBuff, void* pWork)
{
	RECORD_WORK *wk = (RECORD_WORK*)pWork;

	wk->recv_count = 0;
	wk->record_execute = TRUE;
	
	// レコードデータ送信開始
	RecordCorner_DataSend( wk, CommGetCurrentID());

	// 画面上部を「レコードこうかんちゅう！」
	RecordCornerTitleChange( wk );

	RecordCorner_MainSeqForceChange( wk, RECORD_MODE_RECORD_SEND_DATA, netID );
	
    CommStateSetErrorCheck(TRUE,TRUE); // ここ以降は切断＝エラー

	// かき混ぜSE
	Snd_SePlay(SEQ_SE_DP_F209);

}


//==============================================================================
/**
 * 通信画面を開始する
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommRecordCornerReStart(int netID, int size, void* pBuff, void* pWork)
{
	RECORD_WORK *wk = (RECORD_WORK*)pWork;

	OS_Printf("親機からレコード募集再開通知\n");
	RecordCorner_MainSeqForceChange( wk, RECORD_MODE_NEWMEMBER_END, 0 );
	
}
//==============================================================================
/**
 * $brief   子機が離脱
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		子(離脱者)からの送信＝0:離脱許可確認。　1:離脱実行
 *						親からの送信＝上位4ビット：親のshareNum(0xfの場合は離脱NG)
 * 									＝下位4ビット：離脱者のID
 * @param   pWork		RECORD_WORK*
 *
 * @retval  none		
 */
//==============================================================================
void CommRecordCornerEndChild(int netID, int size, void* pBuff, void* pWork)
{
	RECORD_WORK *wk = (RECORD_WORK*)pWork;
	COMM_RECORD_END_CHILD_WORK trans_work;
	COMM_RECORD_END_CHILD_WORK *recieve_work;
	
	recieve_work = pBuff;
	
	if(netID != 0){
		//子機(離脱者)からの送信
		//離脱します通知
		if(CommGetCurrentID()==0){
			// 子機から(親機が受け取る)
			// 子機がいなくなった事を全員に通知する
			trans_work = *recieve_work;
			trans_work.ridatu_id = netID;
			trans_work.oya_share_num = wk->shareNum;
			switch(recieve_work->request){
			case CREC_REQ_RIDATU_CHECK:
				if(wk->shareNum != CommGetConnectNum() 
						|| wk->shareNum != RecordCorner_MyStatusGetNum()
						|| wk->shareNum != MATH_CountPopulation(WH_GetBitmap())){
					trans_work.ridatu_kyoka = FALSE;	//離脱NG！
				}
				else{
					wk->ridatu_bit |= 1 << netID;
					trans_work.ridatu_kyoka = TRUE;
					//離脱OKなので参加制限をかける(乱入があればそちら側で制限がはずされるはず)
					CommStateSetLimitNum(CommGetConnectNum());
				}
				break;
			case CREC_REQ_RIDATU_EXE:
				break;
			}

			CommSendData( CR_RECORD_END_CHILD, &trans_work, sizeof(COMM_RECORD_END_CHILD_WORK) );
			OS_Printf("子機%dから離脱を受け取った→送信\n",netID);
		}
	}
	else{
		//親からの送信
		switch(recieve_work->request){
		case CREC_REQ_RIDATU_CHECK:
			//離脱確認なので、離脱しようとした子機にのみ結果を送る
			if(recieve_work->ridatu_id == CommGetCurrentID()){
				if(recieve_work->ridatu_kyoka == FALSE){
					RecordCorner_MainSeqForceChange( wk, RECORD_MODE_END_SELECT_ANSWER_NG, recieve_work->ridatu_id );
				}
				else{
					wk->oya_share_num = recieve_work->oya_share_num;
					RecordCorner_MainSeqForceChange( wk, RECORD_MODE_END_SELECT_ANSWER_OK, recieve_work->ridatu_id );
				}
			}
			break;
		case CREC_REQ_RIDATU_EXE:
			OS_Printf("親機が子機%dの離脱通知した\n", recieve_work->ridatu_id);
		//	RecordCorner_MainSeqCheckChange( wk, RECORD_MODE_LOGOUT_CHILD, id );
			RecordCorner_MainSeqForceChange( wk, RECORD_MODE_LOGOUT_CHILD, recieve_work->ridatu_id );
			break;
		}
	}
}

//==============================================================================
/**
 * $brief   「子機が乱入してきたので一旦絵を送るよ止まってね」
 *			と親機が送信してきた時のコールバック
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommRecordCornerStop(int netID, int size, void* pBuff, void* pWork)
{

	RECORD_WORK *wk = (RECORD_WORK*)pWork;
	u8 id;

	id = *(u8*)pBuff;
	// メインシーケンス変更
	RecordCorner_MainSeqCheckChange( wk, RECORD_MODE_NEWMEMBER, id );

	// 親機が画像データ送信を開始する
	if(CommGetCurrentID()==0){
		wk->send_num = 0;

		// ここでレコードコーナー用データを皆で送信開始する(だろう)
		// RECORD_GraphicDataSend(wk, wk->send_num);
	}


	OS_Printf("親機からの「子機%dに絵を送るから止まってね」通知\n",id);

}

void CommRecordCornerYes(int netID, int size, void* pBuff, void* pWork)
{
	
}
void CommRecordCornerNo(int netID, int size, void* pBuff, void* pWork)
{
	
}

//==============================================================================
/**
 * $brief   親機がやめるので強制終了させる
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommRecordCornerEnd(int netID, int size, void* pBuff, void* pWork)
{
	RECORD_WORK *wk = (RECORD_WORK*)pWork;
	OS_Printf("親機からの終了通知がきたのでやめる\n");

	// 親機以外はこのコマンドで強制しゅうりょうする
	if(CommGetCurrentID() != 0){
		RecordCorner_MainSeqForceChange( wk, RECORD_MODE_FORCE_END, 0  );
	}
}

//==============================================================================
/**
 * $brief   ３台目・４台目・５台目の子機が「絵をちょーだい」と言う
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommRecordCornerChildJoin(int netID, int size, void* pBuff, void* pWork)
{
	u8 id;
//	GF_ASSERT(CommGetCurrentID()==0 && "子機がうけとった");

	// 親機が受け取ったら(というか親しか受け取らないけど）
	if(CommGetCurrentID()==0){
		id  = netID;
		
		// 全台に「これから絵を送るので止まってください」と送信する
		CommSendData( CR_RECORD_STOP, &id, 1 );
		OS_Printf("子機(%d = %d)からの乱入／絵のください通知\n",id,netID);
	}
	
}





//------------------------------------------------------------------
/**
 * $brief   グラフィックデータを分割送信
 *
 * @param   wk		
 * @param   no		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void RecordCorner_DataSend( RECORD_WORK *wk, int no)
{
	// xor取得・格納
	{
		int i;
		u32 *p,result;
		p = (u32*)wk->send_data.data;
		for(result=0,i=0;i<RECORD_SEND_DATASIZE/4;i++){
			result ^= p[i];
		}
		wk->send_data._xor        = result;
	}

	// 分割番号を書き込む(親機の値だけが使用される）
	wk->send_data.seed = gf_rand();
	
	// 送信開始
//	CommSendSpritData( &wk->send_data, sizeof(RECORD_DATA) );
	CommSendHugeData(CR_RECORD_DATA, &wk->send_data, sizeof(RECORD_DATA) );
	

	OS_Printf("送信データ no=%d, xor = %08x\n",  wk->send_data.seed,  wk->send_data._xor);
}


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// パレットサイズ通知関数群
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------
// 0バイトを表す関数
//--------------------------------------------------------------------------------
static int _getZero(void)
{
    return 0;
}

//--------------------------------------------------------------------------------
// 1バイトを表す関数
//--------------------------------------------------------------------------------
static int _getOne(void)
{
    return 1;
}

//--------------------------------------------------------------------------------
// 1バイトを表す関数
//--------------------------------------------------------------------------------
static int _getCRECW(void)
{
	return sizeof(COMM_RECORD_END_CHILD_WORK);
}


//--------------------------------------------------------------------------------
// レコードデータの受信バッファを設定する関数
//--------------------------------------------------------------------------------
static u8* _getRecordRecvBuf( int netID, void* pWork, int size )
{
	RECORD_WORK *wk = (RECORD_WORK*)pWork;
	
	return (u8*)&wk->recv_data[netID];
}
