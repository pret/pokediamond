//=============================================================================
/**
 * @file	comm_command_mystery.c
 * @brief	データを送るためのコマンドをテーブル化しています
 *		「ふしぎなおくりもの」用          
 *          	comm_command_mystery.h の enum と同じ並びである必要があります
 * @author	Satoshi Mitsuhara
 * @date    2006.05.16
 * $Id: comm_command_mystery.c,v 1.1 2006/05/18 11:04:55 mitsuhara Exp $
*/
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "comm_command_mystery.h"
#include "comm_mystery_state.h"


//==============================================================================
//  テーブルに書く関数の定義
//==============================================================================

//==============================================================================
//  static定義
//==============================================================================

//==============================================================================
//	テーブル宣言
//  comm_shar.h の enum と同じならびにしてください
//  CALLBACKを呼ばれたくない場合はNULLを書いてください
//  コマンドのサイズを返す関数を書いてもらえると通信が軽くなります
//  _getZeroはサイズなしを返します。_getVariableは可変データ使用時に使います
//==============================================================================
static const CommPacketTbl _CommPacketTbl[] = {
  /* ふしぎなおくりもの　データ送信 */
  { CommMysteryGiftRecvPlace, CommMysteryGetRecvPlaceSize, CommGetMysteryGiftRecvBuff },
  /* 受信成功しましたのフラグ　データ送信 */
  { CommMysterySendRecvResult, _getZero, NULL },
};

//--------------------------------------------------------------
/**
 * @brief   ふしぎなできごと用のコマンド体系に初期化します
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
void CommCommandMysteryInitialize(void* pWork)
{
    int length = sizeof(_CommPacketTbl)/sizeof(CommPacketTbl);
    CommCommandInitialize(_CommPacketTbl, length, pWork);
}

/*  */
