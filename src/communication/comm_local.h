//=============================================================================
/**
 * @file	comm_local.h
 * @brief	通信クラスのみで参照したい構造体とメソッドが書かれている.h
 * @author	Katsumi Ohno
 * @date    2005.07.12
 */
//=============================================================================
#ifndef _COMM_LOCAL_
#define _COMM_LOCAL_

#include "communication/comm_ring_buff.h"

//==============================================================================
// 定義
//==============================================================================
#define _COMM_RECV_BACKUP_NUM   (2)  ///< 通信は1/60なので 60/30分受信データを蓄える必要がある

#define _DEFAULT_TIMEOUT_FRAME (30*5) ///< 通信処理のタイムアウト時間のデフォルト

#define _SCAN_ALL_CHANNEL  (0)  ///< スキャンするチャンネルがランダムで行う場合０に設定する

// 通信サービスの最大子機台数
extern u16 CommLocalGetServiceMaxEntry(u16 serviceNo);
// 通信サービスの最小子機台数
extern u16 CommLocalGetServiceMinEntry(u16 serviceNo);

// デバッグ用コマンドプリント
#define _COMMAND_TEST  (0)

#endif //_COMM_SHARING_LOCAL_

