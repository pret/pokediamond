//=============================================================================
/**
 * @file	comm_tradelist.c
 * @brief	データを送るためのコマンドをテーブル化しています
 *          フィールド用です
 *          comm_command_field.h の enum と同じ並びである必要があります
 * @author	Akito Mori
 * @date    2005.12.21
 */
//=============================================================================

#include "common.h"
#include "system/procsys.h"
#include "communication/communication.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "system/gra_tool.h"
#include "system/bmp_menu.h"
#include "savedata/friendlist.h"
#include "savedata/friendlist_local.h"


#include "application/tradelist.h"
#include "comm_command_tradelist.h"
#include "tradelist_def.h"

#include "field/fieldsys.h" //FIELDSYS_WORK
#include "system/mystatus.h"
#include "poketool/pokeparty.h"


void CommTradeListFriendList(int netID, int size, void* pBuff, void* pWork);
void CommTradeListPerapVoice(int netID, int size, void* pBuff, void* pWork);
void CommTradeListSaveWait(int netID, int size, void* pBuff, void* pWork);
void CommTradeListRibbonInfo(int netID, int size, void* pBuff, void* pWork);


static int PositionChangeLR(u8 pos);
static int _getPokePartySplitSize(void);
static int _getFriendListSize(void);
static u8* _getPokePartyRecvBuff( int netID, void* pWork, int size);
static u8* _getPerapVoiceRecvBuff( int netID, void* pWork, int size );
static int _getPerapVoiceSize(void);
static int _getSpRibbonSize(void);


static const CommPacketTbl _CommPacketTbl[] = {
	
{CommTradeListPokemonData,_getPokePartySplitSize, _getPokePartyRecvBuff}, // CT_POKEDATA
{CommTradeListCusorPos,   _getOne},               // CT_CURSOR_POS,		///< カーソル位置情報
{CommTradeListDecide,     _getOne},               // CT_TRADE_DECIDE,		///< 決定
{CommTradeListResultYes,  _getOne},               // CT_TRADE_YES,		///< はい
{CommTradeListResultNo,	  _getOne},               // CT_TRADE_NO,			///< いいえ
{CommTradeListTradeStart, _getOne},               // CT_TRADE_START,		///< 交換デモへ
{CommTradeListFriendList, _getFriendListSize,     _getPokePartyRecvBuff },	// CT_FRIENDLIST,	///< しりあいグループデータ
{CommTradeListPerapVoice, _getPerapVoiceSize,     _getPokePartyRecvBuff },	// CT_FRIENDLIST,	///< ペラップボイスデータ
{CommTradeListEnd,		  _getZero},              // CT_TRADE_END,		///< 終了
{CommTradeListSaveWait,	  _getOne},               // CT_SAVE_WAIT_TIME,	///< セーブまでのウェイト
{CommTradeListRibbonInfo, _getSpRibbonSize},      // CT_SP_RIBBON,		///< 拡張リボン情報

};


//==============================================================================
/**
 * 
 *
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommCommandTradeListInitialize(void* pWork)
{
    int length = sizeof(_CommPacketTbl)/sizeof(CommPacketTbl);
    CommCommandInitialize(_CommPacketTbl, length, pWork);
}

//------------------------------------------------------------------
/**
 * 通信で取得したカーソル位置を左右反転させる（「おわり」はそのまま）
 *
 * @param   pos		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int PositionChangeLR(u8 pos)
{
	// おわり
	if(pos==12){
		return 12;
	}
	// 左側は右側に
	if(pos<6){
		return pos+6;
	}
	//残り右側なので左側に
	return pos-6;
}

//------------------------------------------------------------------
/**
 * 分割して送られてくるPOKEPARTYをコピーする関数
 *
 * @param   party		
 * @param   buf		
 * @param   no		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CopyPokePartySplitData(POKEPARTY *party, void *buf, int no)
{
	u32 adrs   = (u32)party+no*POKEPARTY_SEND_ONCE_SIZE;
	u32 total  = no*POKEPARTY_SEND_ONCE_SIZE+POKEPARTY_SEND_ONCE_SIZE;
	u32 offset = no*POKEPARTY_SEND_ONCE_SIZE;


	if(total > PokeParty_GetWorkSize()){
		int rest;

		rest = PokeParty_GetWorkSize() - offset;
		memcpy((void*)adrs,buf,rest);
	}else{
		memcpy((void*)adrs,buf,POKEPARTY_SEND_ONCE_SIZE);
	}
}

//==============================================================================
/**
 * ポケモンデータを受信し格納。次のデータ送信を呼び出す(親子交互の送信になり）
 * 数珠繋ぎに１２体分を送信することになるはず
 * 
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommTradeListPokemonData(int netID, int size, void* pBuff, void* pWork)
{
	FIELDSYS_WORK  *fsys = (FIELDSYS_WORK*)pWork;
	TRADELIST_WORK *tlw  = fsys->tradelist_work;



	// 受信したデータが自分のＩＤと違うのであれば取り込む
	if(netID!=CommGetCurrentID()){

		OS_Printf("ポケモン netID = %d  no=%d, %d/%d  pokesize=%d\n",netID,tlw->exchange_friend_count,(tlw->exchange_friend_count+1)*POKEPARTY_SEND_ONCE_SIZE,PokeParty_GetWorkSize(),PokemonParam_GetWorkSize());

		// ワークのPokePartyにコピー
//		PokeParty_Add(tlw->FriendPokeParty, (POKEMON_PARAM *)pBuff);
//		CopyPokePartySplitData(tlw->FriendPokeParty,pBuff,tlw->exchange_friend_count++);
		memcpy((void*)tlw->FriendPokeParty,pBuff,POKEPARTY_SEND_ONCE_SIZE);
		tlw->exchange_friend_count++;

		// 自分のデータを送信する
		if((tlw->exchange_friend_count)*POKEPARTY_SEND_ONCE_SIZE >= PokeParty_GetWorkSize()){
//			tlw->exchange_finish = 1;
			if(CommGetCurrentID()==1){
				TradeListCommDiffSend( tlw, CT_TRADE_START,0);
			}else{
				TradeListCommSendPokeData(CommGetCurrentID(), tlw->MyPokeParty, tlw->exchange_work);
			}
		}else{
			TradeListCommSendPokeData(CommGetCurrentID(), tlw->MyPokeParty, tlw->exchange_work);
		}
		tlw->exchange_work++;
	}

}


//==============================================================================
/**
 * 交換リストのカーソル位置を受信したときのコールバック
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommTradeListCusorPos(int netID, int size, void* pBuff, void* pWork)
{
	TRADELIST_WORK *tlw  = ((FIELDSYS_WORK*)pWork)->tradelist_work;
	u8 *pos = (u8*)pBuff;

	// 自分で送ったデータじゃないＩＤのを採用する
	if(netID!=CommGetCurrentID()){
		tlw->cursor_pos[1] =  PositionChangeLR( *pos );
	}
}
void CommTradeListDecide(int netID, int size, void* pBuff, void* pWork)
{
	TRADELIST_WORK *tlw  = ((FIELDSYS_WORK*)pWork)->tradelist_work;
	u8 *data = (u8*)pBuff;

	OS_Printf("ID%d :終了コマンド到着\n",netID);
	
	tlw->end_flag[netID] = *data;
}
void CommTradeListResultYes(int netID, int size, void* pBuff, void* pWork)
{
	
}
void CommTradeListResultNo(int netID, int size, void* pBuff, void* pWork)
{
	
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
void CommTradeListTradeStart(int netID, int size, void* pBuff, void* pWork)
{
	TRADELIST_WORK *tlw  = ((FIELDSYS_WORK*)pWork)->tradelist_work;
	
	OS_Printf("開始データ\n");

	tlw->exchange_finish=2;

}


void CommTradeListEnd(int netID, int size, void* pBuff, void* pWork)
{

}

//==============================================================================
/**
 * @brief   親機がセーブまでのウェイトを乱数で生成して渡してくれる
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommTradeListSaveWait(int netID, int size, void* pBuff, void* pWork)
{
	TRADELIST_WORK *tlw  = ((FIELDSYS_WORK*)pWork)->tradelist_work;
	u8 *wait = (u8*)pBuff;

	tlw->savePreWait = *wait;
	
	OS_TPrintf("親機からセーブまでの時間を%dsync待てと通知が来た\n", *wait*2);
}

//==============================================================================
/**
 * @brief   拡張リボン情報をやりとり
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommTradeListRibbonInfo(int netID, int size, void* pBuff, void* pWork)
{
	FIELDSYS_WORK *fsys  = (FIELDSYS_WORK*)pWork;
	int i;
	u8 *mySpRibbon   = SaveData_GetSpRibbon( fsys->savedata );
	u8 *recvSpRibbon = (u8*)pBuff;

	OS_Printf("ID %dのリボン情報を受信\n", netID);
	
	if(CommGetCurrentID()==netID){
		// 自分の情報はいらない
		return;
	}

	for(i=0;i<HAIFU_RIBBON_MAX;i++){
		// 受信した情報が0じゃなくて
		if(recvSpRibbon[i]!=0){
			// 自分のリボンと相手の情報が違うのであれば
			if(mySpRibbon[i]!=recvSpRibbon[i]){
				// リボン情報を書き換える
				mySpRibbon[i]=recvSpRibbon[i];
			}
		}
	}
	
	
	
}


//==============================================================================
/**
 * $brief   ともだちグループに登録するためのデータを受信した
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommTradeListFriendList(int netID, int size, void* pBuff, void* pWork)
{
	TRADELIST_WORK *tlw  = ((FIELDSYS_WORK*)pWork)->tradelist_work;
	
	OS_Printf("しりあいグループデータ到着\n");
	
	if(CommGetCurrentID()!=netID){
		FriendList_Update( tlw->friendlist, (FRIEND_LIST*)pBuff, 1, HEAPID_TRADELIST );
		tlw->exchange_finish = 3;
	}
}


//==============================================================================
/**
 * @brief   ペラップボイスデータの受信
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommTradeListPerapVoice(int netID, int size, void* pBuff, void* pWork)
{
	TRADELIST_WORK *tlw  = ((FIELDSYS_WORK*)pWork)->tradelist_work;
	
	OS_Printf("ペラップボイス到着\n");
	
	if(CommGetCurrentID()!=netID){
		MI_CpuCopyFast( pBuff, tlw->perap_buf[netID], PERAPVOICE_LENGTH );
		tlw->exchange_finish = 4;
        CommSetWifiBothNet(FALSE); // wifiの通信を同期から非同期に変える
	}
	
}

//==============================================================================
/// FIELDSYS_WORKに確保済みワークのポインタを渡す 
//==============================================================================
void SetFieldSys_in_TradeWorkPtr(FIELDSYS_WORK* fsys, TRADELIST_WORK *tradelist_work)
{
	fsys->tradelist_work = tradelist_work;
}

//==============================================================================
/// PERAP_VOICEのサイズを返す
//==============================================================================
static int _getPerapVoiceSize(void)
{
    return PERAPVOICE_DATA_LENGTH;
}

//==============================================================================
/// 拡張リボン情報のサイズを返す
//==============================================================================
static int _getSpRibbonSize(void)
{
	return HAIFU_RIBBON_MAX;

}

//==============================================================================
/// FRIEND_LISTのサイズを返す
//==============================================================================
static int _getFriendListSize(void)
{
    return sizeof(FRIEND_LIST);
}

//==============================================================================
/// 手持ちポケモンのサイズを返す
//==============================================================================
static int _getPokePartySplitSize(void)
{
	return POKEPARTY_SEND_ONCE_SIZE;
}


//==============================================================================
/// 受信バッファを渡す
//==============================================================================
static u8* _getPokePartyRecvBuff( int netID, void* pWork, int size)
{
	TRADELIST_WORK *tlw  = ((FIELDSYS_WORK*)pWork)->tradelist_work;
	
	return (u8*)tlw->recv_buf[netID];
}


