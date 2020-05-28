//=============================================================================
/**
 * @file	comm_command.h
 * @brief	データ共有を行う場合の通信システム
 *          使用する場合に書き込む必要があるものをまとめたヘッダー
 * @author	Katsumi Ohno
 * @date    2005.07.26
 */
//=============================================================================

#ifndef __COMM_COMMAND_H__
#define __COMM_COMMAND_H__


//==============================================================================
//	定義
//==============================================================================

//==============================================================================
//	型宣言
//==============================================================================
// コールバック関数の書式
typedef void (*PTRCommRecvFunc)(int netID, int size, void* pData, void* pWork);
// サイズが固定の場合サイズを関数で返す
typedef int (*PTRCommRecvSizeFunc)(void);
// 受信バッファを持っている場合そのポインタ
typedef u8* (*PTRCommRecvBuffAddr)(int netID, void* pWork, int size);


typedef struct {
    PTRCommRecvFunc callbackFunc;    ///< コマンドがきた時に呼ばれるコールバック関数
    PTRCommRecvSizeFunc getSizeFunc; ///< コマンドの送信データサイズが固定なら書いてください
    PTRCommRecvBuffAddr getAddrFunc;
} CommPacketTbl;

#define   _SET(callfunc, getSize, name)       {callfunc,  getSize},

/// 汎用通信コマンドの定義
enum CommCommand_e {
  CS_NONE = 0xee,                ///< なにもしない
  CS_FREE = 0,                   ///< 空コマンド
  CS_COMMAND_MIN = 1,             ///< 最小値
  CS_EXIT = CS_COMMAND_MIN,            ///< 終了
  CS_AUTO_EXIT,            ///< 自動終了
  CS_COMM_INFO,       ///< info情報
  CS_COMM_INFO_ARRAY,  ///< info情報を投げ返す
  CS_COMM_INFO_END,   ///< info情報送信終了
  CS_COMM_NEGOTIATION,  ///< 初期化時のネゴシエーション
  CS_COMM_NEGOTIATION_RETURN,
  CS_DEBUG_VARIABLE,         ///< デバッグ用（本番でコマンド番号が変わらないようにこのままおいておく）
  CS_DEBUG_START,            ///< デバッグ用 バトルスタート
  CS_DSMP_CHANGE,            ///< DSモード通信かMPモード通信かに切り替える許可を得る
  CS_DSMP_CHANGE_REQ,        ///< DSモード通信かMPモード通信かに切り替える指示を出す
  CS_DSMP_CHANGE_END,        ///< DSモード通信かMPモード通信かに切り替え完了したことを通知
  CS_COMMAND_THROWOUT,       ///< コマンドを破棄する許可を得る
  CS_COMMAND_THROWOUT_REQ,   ///< コマンドを破棄する指示を出す
  CS_COMMAND_THROWOUT_END,   ///< コマンド破棄完了したことを通知-----
  CS_TIMING_SYNC,            ///< 同期を取るコマンド
  CS_TIMING_SYNC_END,        ///< 同期が取れたことを返すコマンド
  CS_TIMING_SYNC_INFO,       ///< 同期の状況を子機に返すコマンド
  CS_LIST_NO,                ///< DS専用 選択番号を送りあう
  CS_TOOL_TEMP,              ///< DS専用 汎用データ転送
  CS_WIFI_EXIT,
  //------------------------------------------------ここまで----------
  CS_COMMAND_MAX   // 終端--------------これは移動させないでください     21
};

#define COMM_VARIABLE_SIZE (0xffff)   ///< 可変データ送信であることを示している


/// コマンドテーブルの初期化をする
extern void CommCommandInitialize(const CommPacketTbl* pCommPacketLocal,int listNum,void* pWork);
/// コマンドテーブルの開放処理
extern void CommCommandFinalize( void );
/// データのサイズを得る
extern int CommCommandGetPacketSize(int command);
///  コマンドテーブルを破棄する時の命令
extern BOOL CommCommandThrowOut(void);
///  コマンドテーブルが破棄し終わったかどうか検査
extern BOOL CommCommandIsThrowOuted(void);
///  コールバックを呼ぶ
extern void CommCommandCallBack(int netID, int command, int size, void* pData);
/// プリント
extern void CommCommandDebugPrint(int command);

// サイズ指定用簡易関数  容量削減の為extern宣言  06.03.29
extern int _getVariable(void);
extern int _getZero(void);
extern int _getOne(void);

extern void* CommCommandCreateBuffStart(int command, int netID, int size);
extern BOOL CommCommandCreateBuffCheck(int command);


#endif// __COMM_COMMAND_H__

