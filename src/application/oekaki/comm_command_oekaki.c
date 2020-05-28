//=============================================================================
/**
 * @file	comm_command_oekaki.c
 * @brief	データを送るためのコマンドをテーブル化しています
 *          お絵かきボード用です
 * @author	Akito Mori
 * @date    2005.02.14
 */
//=============================================================================

#include "common.h"
#include "system/procsys.h"
#include "communication/communication.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "communication/communication.h"
#include "communication/wh.h"
#include "field/fieldobj.h"
#include "field/comm_union_beacon.h"
#include "field/comm_union_view_common.h"



typedef struct OEKAKI_WORK OEKAKI_WORK;

#include "application/oekaki.h"

#include "oekaki_local.h"


#include "comm_command_oekaki.h"



static int _getPictureSize(void);
static int _getLinePosSize(void);
static int _getLinePosServerSize(void);
static u8* _setPictureBuff( int netID, void* pWork, int size);
static int _getCRECW(void);
static int _getCOECW(void);

static void Oekaki_GraphicDataSend( OEKAKI_WORK *wk, int no);
static void CommOekakiBoardFreeze( int netID, int size, void* pBuff, void* pWork );


// CommCommandOekaki.cから定義するコマンドで対応するコールバック関数
static const CommPacketTbl _CommPacketTbl[] = {

    { CommDummyCallBack, _getOne, NULL},// comm_command_field.cで登録されているコマンドテーブルの無効化するために
    { CommDummyCallBack, _getOne, NULL},// 登録する
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},	// comm_command_field.cで登録されているコマンドテーブルの無効化するために
    { CommDummyCallBack, _getOne, NULL}, // 登録する


	// レコードのコマンドテーブルを無視するための部分
	{ CommDummyCallBack, _getOne, NULL},
	{ CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getCRECW, NULL},
    { CommDummyCallBack, _getOne, NULL},
	{ CommDummyCallBack, _getOne, NULL},
	{ CommDummyCallBack, _getOne, NULL},
	{ CommDummyCallBack, _getOne, NULL},
	{ CommDummyCallBack, _getOne, NULL},

	// お絵かきが見る部分
	{CommOekakiBoardPicture, 		_getPictureSize, _setPictureBuff}, 		// CO_OEKAKI_GRAPHICDATA  みんなで描いていた画像データ
	{CommOekakiBoardLinePos,   		_getLinePosSize},    	// CO_OEKAKI_LINEPOS,	  タッチパネルで取得したポジションデータ
	{CommOekakiBoardLinePosServer, _getLinePosServerSize}, 	// CO_OEKAKI_LINEPOS,	  タッチパネルで取得したポジションデータ
	{CommOekakiBoardYes,   			_getOne},              	// CO_OEKAKI_YES,		  はい
	{CommOekakiBoardNo,   	   	 	_getOne},             	// CO_OEKAKI_NO,		  いいえ
    {CommOekakiBoardStop,			_getOne},             	// CO_OEKAKI_STOP,		  乱入者が来たので一旦ストップ
    {CommOekakiBoardReStart,		_getZero},             	// CO_OEKAKI_RESTART,	  乱入者処理が終わったので再会
    {CommOekakiBoardEndQuestion,	_getZero},          	// CO_OEKAKI_END_QUESTION 終了
    {CommOekakiBoardEndChild,		_getCOECW},            	// CO_OEKAKI_END_CHILD,	  子機が離脱
    {CommOekakiBoardEnd,			_getZero},              // CO_OEKAKI_END,		  終了
	{CommOekakiBoardChildJoin,		_getZero},				// CO_OEKAKI_CHILD_JOIN	  子機が乱入を宣言
	{CommOekakiBoardFreeze,			_getZero},				// CO_OEKAKI_OUT_CONTROL	離脱禁止期間
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
void CommCommandOekakiBoardInitialize(void* pWork)
{
    int length = sizeof(_CommPacketTbl)/sizeof(CommPacketTbl);
    CommCommandInitialize(_CommPacketTbl, length, pWork);
}


//==============================================================================
/**
 * 親機が接続するまでにかかれていた画像を一気に送信する
 * 
 * 
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommOekakiBoardPicture(int netID, int size, void* pBuff, void* pWork)
{
	OEKAKI_WORK *wk = (OEKAKI_WORK *)pWork;

	// 子機の場合は親機からもらった画像データを取り込む
	if(CommGetCurrentID()!=0){
		OEKAKIG_SPLIT_DATA *osd = (OEKAKIG_SPLIT_DATA *)pBuff;;
		OS_Printf("画像取得 no=%d, xor=%08x\n",osd->no, osd->_xor);
		if(osd->no*1000 > OEKAKI_GRAPHI_SIZE){
			MI_CpuCopyFast( osd->chara, &wk->canvas_buf[osd->no*1000], OEKAKI_GRAPHI_SIZE%1000);
		}else{
			MI_CpuCopyFast( osd->chara, &wk->canvas_buf[osd->no*1000],  1000);
		}
		// BMPWINのバッファにコピーする
		MI_CpuCopyFast( wk->canvas_buf, wk->OekakiBoard.chrbuf, OEKAKI_GRAPHI_SIZE);

		// 画面に反映
		GF_BGL_BmpWinOn( &wk->OekakiBoard );

	// 親機は次のデータを送信する
	}else{
		OEKAKIG_SPLIT_DATA *osd = (OEKAKIG_SPLIT_DATA *)pBuff;;
		OS_Printf("画像取得 no=%d, xor=%08x",osd->no, osd->_xor);
	
		if(wk->send_num*1000 < OEKAKI_GRAPHI_SIZE){
			wk->send_num++;
			Oekaki_GraphicDataSend(wk, wk->send_num);
		}else{
			CommSendData_ServerSide( CO_OEKAKI_RESTART, NULL, 0);
		}
	}

}


//==============================================================================
/**
 * カーソル位置情報を受信したときのコールバック
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommOekakiBoardLinePos(int netID, int size, void* pBuff, void* pWork)
{
	OEKAKI_WORK *wk     = (OEKAKI_WORK*)pWork;
	TOUCH_INFO  *result = (TOUCH_INFO*)pBuff;

	// 子機から貰ったデータを格納する
	if(netID!=0){
		wk->ParentTouchResult[netID] = *result;
	}

}



//==============================================================================
/**
 * $brief   ラインデータを親機から受信した（全員描画)
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommOekakiBoardLinePosServer( int netID, int size, void* pBuff, void* pWork )
{
	OEKAKI_WORK *wk     = (OEKAKI_WORK*)pWork;
	TOUCH_INFO  *result = (TOUCH_INFO*)pBuff;

    if(wk==NULL){  // このときはお絵かき準備ができていないので無視
        return;
    }

    
	if(netID==0){	// 絶対に親からしか来ないはずだが
		int i;
		for(i=0;i<OEKAKI_MEMBER_MAX;i++){
			wk->AllTouchResult[i] = result[i];
		}
	}
	
	if(wk->AllTouchResult[0].banFlag==OEKAKI_BAN_ON){
		OS_TPrintf("親機から操作禁止命令\n");
	}
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
void CommOekakiBoardReStart(int netID, int size, void* pBuff, void* pWork)
{
	OEKAKI_WORK *wk = (OEKAKI_WORK*)pWork;

	OS_Printf("親機からお絵かき再開通知\n");
	OekakiBoard_MainSeqForceChange( wk, OEKAKI_MODE_NEWMEMBER_END, 0 );
	
	MI_CpuClearFast( wk->canvas_buf, OEKAKI_GRAPHI_SIZE );
	
	if(CommGetCurrentID()==0){
		// 絵を共有した接続人数を更新
		wk->shareNum = CommGetConnectNum();
		wk->shareBit = WH_GetBitmap();
		wk->banFlag  = OEKAKI_BAN_OFF;
	}
}
//==============================================================================
/**
 * $brief   子機が離脱
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		離脱者のID(親からの送信で最上位ビットが立っている場合は離脱NG)
 * @param   pWork		OEKAKI_WORK*
 *
 * @retval  none		
 */
//==============================================================================
void CommOekakiBoardEndChild(int netID, int size, void* pBuff, void* pWork)
{
	OEKAKI_WORK *wk = (OEKAKI_WORK*)pWork;
	COMM_OEKAKI_END_CHILD_WORK trans_work;
	COMM_OEKAKI_END_CHILD_WORK *recieve_work;

	recieve_work = pBuff;
	
	// 親機からきた場合はみんなで「●●●がいなくなりました」とだす
	if(netID!=0){
		//子機(離脱者)からの送信
		//離脱します通知
		if(CommGetCurrentID()==0){
			// 子機から(親機が受け取る)
			// 子機がいなくなった事を全員に通知する
			trans_work = *recieve_work;
			trans_work.ridatu_id = netID;
			trans_work.oya_share_num = wk->shareNum;
			switch(recieve_work->request){
			case COEC_REQ_RIDATU_CHECK:
				if(wk->shareNum != CommGetConnectNum() 
						|| wk->shareNum != OekakiBoard_MyStatusGetNum()
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
			case COEC_REQ_RIDATU_EXE:
				break;
			}

			CommSendData_ServerSide( CO_OEKAKI_END_CHILD, &trans_work, 
				sizeof(COMM_OEKAKI_END_CHILD_WORK) );
			OS_Printf("子機%dから離脱を受け取った→送信\n",netID);
		}
	
	}else{
	// 親機から子機離脱の通知が来た
		switch(recieve_work->request){
		case COEC_REQ_RIDATU_CHECK:
			//離脱確認なので、離脱しようとした子機にのみ結果を送る
			if(recieve_work->ridatu_id == CommGetCurrentID()){
				if(recieve_work->ridatu_kyoka == FALSE){
					OekakiBoard_MainSeqForceChange( wk, OEKAKI_MODE_END_SELECT_ANSWER_NG, recieve_work->ridatu_id );
				}
				else{
					wk->oya_share_num = recieve_work->oya_share_num;
					OekakiBoard_MainSeqForceChange( wk, OEKAKI_MODE_END_SELECT_ANSWER_OK, recieve_work->ridatu_id );
				}
			}
			break;
		case COEC_REQ_RIDATU_EXE:
			OS_TPrintf("親機が子機%dの離脱通知した\n", recieve_work->ridatu_id);
		//	OekakiBoard_MainSeqCheckChange( wk, OEKAKI_MODE_LOGOUT_CHILD, id );
			OekakiBoard_MainSeqForceChange( wk, OEKAKI_MODE_LOGOUT_CHILD, recieve_work->ridatu_id );
			break;
		}
	}
}
void CommOekakiBoardEndQuestion(int netID, int size, void* pBuff, void* pWork)
{

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
void CommOekakiBoardStop(int netID, int size, void* pBuff, void* pWork)
{

	OEKAKI_WORK *wk = (OEKAKI_WORK*)pWork;
	u8 id;

	id = *(u8*)pBuff;
	// メインシーケンス変更
	OekakiBoard_MainSeqForceChange( wk, OEKAKI_MODE_NEWMEMBER, id );

	// 親機が画像データ送信を開始する
	if(CommGetCurrentID()==0 && wk->proc_seq == SEQ_MAIN){
		wk->send_num = 0;

		//グラフィック分割送信
		Oekaki_GraphicDataSend(wk, wk->send_num);
	}


	OS_Printf("親機からの「子機%dに絵を送るから止まってね」通知\n",id);

}

void CommOekakiBoardYes(int netID, int size, void* pBuff, void* pWork)
{
	
}
void CommOekakiBoardNo(int netID, int size, void* pBuff, void* pWork)
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
void CommOekakiBoardEnd(int netID, int size, void* pBuff, void* pWork)
{
	OEKAKI_WORK *wk = (OEKAKI_WORK*)pWork;
	OS_Printf("親機からの終了通知がきたのでやめる\n");

	// 親機以外はこのコマンドで強制しゅうりょうする
	if(CommGetCurrentID() != 0){
		OekakiBoard_MainSeqForceChange( wk, OEKAKI_MODE_FORCE_END, 0  );
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
void CommOekakiBoardChildJoin(int netID, int size, void* pBuff, void* pWork)
{
	OEKAKI_WORK *wk = (OEKAKI_WORK*)pWork;
	u8 id;
	GF_ASSERT(CommGetCurrentID()==0 && "子機がうけとった");
OS_Printf("_子機(%d)からの乱入／絵のください通知\n",netID);
	// 親機が受け取ったら(というか親しか受け取らないけど）
	if(CommGetCurrentID()==0){
		if(wk->firstChild!=0){
			id  = netID;
		
			// 全台に「これから絵を送るので止まってください」と送信する
			CommSendData_ServerSide( CO_OEKAKI_STOP, &id, 1 );
			OS_Printf("子機(%d = %d)からの乱入／絵のください通知\n",id,netID);
		}else{
			OS_Printf("最初の子機%dからの乱入なので無視する\n",netID);
			wk->firstChild = 1;
		}
	}
    // お絵かき時には接続切断でエラー扱いしない(途中でTRUE,TRUEに戻る事があるので再度）
    CommStateSetErrorCheck(FALSE,TRUE);
	
}

//------------------------------------------------------------------
/**
 * @brief   離脱禁止コマンド到着
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CommOekakiBoardFreeze( int netID, int size, void* pBuff, void* pWork )
{
	OEKAKI_WORK *wk = (OEKAKI_WORK*)pWork;

	// 離脱禁止
	wk->banFlag = 1;
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
static void Oekaki_GraphicDataSend( OEKAKI_WORK *wk, int no)
{
	// 送信バッファにコピー
	u8 *p = (u8*)wk->OekakiBoard.chrbuf;
	MI_CpuCopyFast( &p[no*1000], wk->send_buf.chara, 1000 ); 

	// xor取得・格納
	{
		int i;
		u32 *p,result;
		p = (u32*)wk->send_buf.chara;
		for(result=0,i=0;i<1000/4;i++){
			result ^= p[i];
		}
		wk->send_buf._xor        = result;
	}

	// 分割番号を書き込む
	wk->send_buf.no = no;
	
	// 送信開始
	CommSendHugeData_ServerSide( CO_OEKAKI_GRAPHICDATA, &wk->send_buf, sizeof(OEKAKIG_SPLIT_DATA));
//	CommSendHugeData(CO_OEKAKI_GRAPHICDATA, &wk->send_buf, 1004);

	OS_Printf("送信データ no=%d, xor = %08x\n",  wk->send_buf.no,  wk->send_buf._xor);
}




//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// パレットサイズ通知関数群
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------



//--------------------------------------------------------------------------------
// 受信データサイズを返す関数
//--------------------------------------------------------------------------------
static u8* _setPictureBuff( int netID, void* pWork, int size)
{
	OEKAKI_WORK *wk = (OEKAKI_WORK*)pWork;

	return (u8*)&wk->split_temp[netID];
}

//--------------------------------------------------------------------------------
// バイトを表す関数
//--------------------------------------------------------------------------------
static int _getCRECW(void)
{
	return 4;
}

//--------------------------------------------------------------------------------
// バイトを表す関数
//--------------------------------------------------------------------------------
static int _getCOECW(void)
{
	return sizeof(COMM_OEKAKI_END_CHILD_WORK);
}
