//=============================================================================
/**
 * @file	comm_command_mystery.h
 * @brief	通信のコマンド一覧  ふしぎなおくりもの用
 * @author	Satoshi Mitsuhara
 * @date	2006.05.16
 */
//=============================================================================

#ifndef __COMM_COMMAND_MYSTERY_H__
#define __COMM_COMMAND_MYSTERY_H__

#include "communication/comm_command.h"


/// ふしぎなおくりもの専用通信コマンドの定義。
enum CommCommandField_e {
  CM_GIFT_DATA = CS_COMMAND_MAX,              	// プレゼントのデータを送る
  CM_RECV_RESULT,				// ちゃんと受け取りましたよ返答
  //------------------------------------------------ここまで
  CM_COMMAND_MAX   // 終端--------------これは移動させないでください
};

extern void CommCommandMysteryInitialize(void* pWork);

#endif	// __COMM_COMMAND_MYSTERY_H__

/*  */
