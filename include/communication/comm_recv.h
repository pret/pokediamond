//=============================================================================
/**
 * @file	comm_recv.h
 * @brief	全員のデータをまとめて検査したい場合ここに記述します
 * @author	Katsumi Ohno
 * @date    2005.07.12
 */
//=============================================================================


#ifndef _COMM_RECV_H_
#define _COMM_RECV_H_

//==============================================================================
// extern宣言
//==============================================================================

/// ロビーを抜ける命令がきたかどうか
extern BOOL CommRecvIsExitRobby(void);
/// 終了キャンセルを受信
extern BOOL CommRecvIsExitCancel(void);
/// 終了を受信
extern BOOL CommRecvIsExit(void);
/// 全員の終了を受信
extern BOOL CommRecvIsExitAll(void);
/// 全員がゲストルームに行くことを承諾した
extern BOOL CommRecvIsPleaseGuestRoomAll(void);
/// 終了コマンドを受信したらモードに応じて処理を行い自動切断する
extern void CommAutoExitCommandFunc(void);
/// 自動終了コマンド受信
extern void CommRecvAutoExit(int netID, int size, void* pData, void* pWork);



#endif //_COMM_RECV_H_
