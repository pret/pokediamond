//=============================================================================
/**
 * @file	comm_message.h
 * @brief	通信用 メッセージを簡単に扱うためのクラス
 * @author	k.ohno
 * @date    2006.02.05
 */
//=============================================================================

#ifndef __COMM_MESSAGE_H__
#define __COMM_MESSAGE_H__

#include "gflib/bg_system.h" //GF_BGL_INI


/// 通信エラー用ウインドウを出す
extern void CommErrorMessageStart(int heapID, GF_BGL_INI* bgl);

/// 通信エラーを検査していてエラーになると止まる
extern void CommErrorCheck(int heapID, GF_BGL_INI* bgl);

/// 通信エラーを検査していてエラーになると止まる
extern void CommErrorDispCheck(int heapID);



#endif //__COMM_MESSAGE_H__
