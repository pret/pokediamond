#ifndef __COMM_COMMAND_TRADELIST_H__
#define __COMM_COMMAND_TRADELIST_H__


// ポケモンパーティーを送信するときのデータ量
#define POKEPARTY_SEND_ONCE_SIZE	( 236*6+4*2 )	// sizeof(POKEPARTY)

#include "communication/comm_command.h"


/// 交換リスト専用通信コマンドの定義。
enum CommCommandTradeList_e {

  CT_POKEDATA  = CS_COMMAND_MAX,	///< ポケモンデータの送信コマンド
  CT_CURSOR_POS,					///< カーソル位置情報
  CT_TRADE_DECIDE,					///< 決定
  CT_TRADE_YES,						///< はい
  CT_TRADE_NO,						///< いいえ
  CT_TRADE_START,					///< 交換デモへ
  CT_FRINEDLIST,					///< 友達リストデータを送る
  CT_PERAPVOICE,					///< ペラップヴォイスデータを送る
  CT_TRADE_END,						///< 終了
  CT_SAVE_WAIT_TIME,				///< セーブまでのウェイト	
  CT_SP_RIBBON_INFO,				///< 拡張リボン情報
  
  //------------------------------------------------ここまで
  CT_COMMAND_MAX   // 終端--------------これは移動させないでください
};

extern void CommTradeListPokemonData(int netID, int size, void* pBuff, void* pWork);
extern void CommTradeListCusorPos(int netID, int size, void* pBuff, void* pWork);
extern void CommTradeListDecide(int netID, int size, void* pBuff, void* pWork);
extern void CommTradeListResultYes(int netID, int size, void* pBuff, void* pWork);
extern void CommTradeListResultNo(int netID, int size, void* pBuff, void* pWork);
extern void CommTradeListTradeStart(int netID, int size, void* pBuff, void* pWork);
extern void CommTradeListFriendList(int netID, int size, void* pBuff, void* pWork);
extern void CommTradeListEnd(int netID, int size, void* pBuff, void* pWork);
extern void SetFieldSys_in_TradeWorkPtr(FIELDSYS_WORK* fsys, TRADELIST_WORK *tradelist_work);

extern void CommCommandTradeListInitialize(void* pWork);
#endif