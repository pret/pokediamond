//=============================================================================
/**
 * @file	comm_direct_counter.h
 * @bfief	通信ダイレクトコーナーのカウンター
 * @author	katsumi ohno
 * @date	05/08/04
 */
//=============================================================================

#ifndef __COMM_DIRECT_COUNTER_H__
#define __COMM_DIRECT_COUNTER_H__

#include "comm_direct_counter_def.h"
#include "battle/battle_common.h"

//==============================================================================
// extern宣言
//==============================================================================
/// 通信ダイレクトコーナーのカウンタのメニュー
extern void CommDirectCounterMenu(FIELDSYS_WORK* pFSys);


/// 親機選択ウインドウを開く
extern void CommSelectParentWindowOpen(FIELDSYS_WORK* pFSys,
                                       int connectMode,int type1,int type2);
/// 親機選択ウインドウを検査する
extern u32 CommSelectParentWindowCheck(void);

/// 子機一覧ウインドウを開く
extern void CommChildWindowOpen(FIELDSYS_WORK* pFSys,
                                int connectMode,int type1,int type2);
/// 子機一覧ウインドウを監視する
extern u32 CommChildWindowCheck(void);

extern void CommChildListWindowOpen(void);
extern void CommParentSelectParentWindowOpen(void);

/// 通信ダイレクトルームに入った時の処理
extern void CommDirectEnterBattleRoom(FIELDSYS_WORK* pFSys);
/// 通信ダイレクトルームの初期化処理が終わったかどうか
extern BOOL CommDirectIsRoomInitialize(void);
/// 通信ダイレクトコーナーの終了処理を開始する
extern void CommDirectEnd(void);
// バトルパラメータセット
extern BATTLE_PARAM* DirectCounter_BattleParamSet(FIELDSYS_WORK* fsys);




#ifdef PM_DEBUG
///   デバッグ用ダイレクトコーナー親機接続
extern void CommDirectParent_Debug(FIELDSYS_WORK* pFSys);
///   デバッグ用ダイレクトコーナー子機接続
extern void CommDirectChild_Debug(FIELDSYS_WORK* pFSys);
/// デバッグ用ダイレクトコーナー接続完了
extern void CommDirectConnect_Debug(void);
/// デバッグ用ダイレクトコーナー初期化パラメータ設定
extern void CommDirectConnectSetParam_Debug(FIELDSYS_WORK* pFSys, int gameMode, int type1, int type2);
#endif

#endif  // __COMM_DIRECT_COUNTER_H__
