
// 化石


#ifndef _UG_DIG_FOSSIL_H_
#define _UG_DIG_FOSSIL_H_

#include "../fieldsys.h"

/// 化石初期化
extern void CommFossilInitialize(void* pWork, FIELDSYS_WORK* pFSys);
/// ワークサイズ取得
extern int CommFossilGetWorkSize(void);
/// 一時的なリセット
extern void CommFossilReset(void);
/// 一時的な復帰
extern void CommFossilReboot(void);
/// 終了処理
extern void CommFossilFinalize(void);
/// 目の前の化石を検査
extern BOOL CommFossilCheck(int netID, Grid* pTouch);
/// 化石発見をクライアントに表示＋掘るかどうか問い合わせる
extern void CommFossilRecvFind(int netID, int size, void* pData, void* pWork);
/// 発掘開始要求
extern void CommFossilRecvDigStartReq(int netID, int size, void* pData, void* pWork);
/// 発掘開始
extern void CommFossilRecvDigStart(int netID, int size, void* pData, void* pWork);
/// 発掘終了要求
extern void CommFossilRecvDigEndReq(int netID, int size, void* pData, void* pWork);
/// 発掘終了
extern void CommFossilRecvDigEnd(int netID, int size, void* pData, void* pWork);
/// 発掘位置を親機に送る
extern void CommFossilRecvDigPos(int netID, int size, void* pData, void* pWork);
/// 化石発掘時の位置を送るコマンドのサイズ
extern int CommFossilGetDigPosSize(void);
/// 化石発掘時の位置を子機に再分配
extern void CommFossilRecvDigPosReturn(int netID, int size, void* pData, void* pWork);
/// 化石発掘時の位置を親機から送る場合のコマンドのサイズ
extern int CommFossilGetDigPosReturnSize(void);
/// 化石サーチタッチパネル処理
extern void CommFossilTouch(int netID, Grid* pTouch);
/// 化石があるかどうか調べる
extern BOOL UGFossileCheck(int x,int z);
/// パソコン化石レーダー開始
extern void UgFossilPcRadarStart(void);
/// パソコン化石レーダー終了
extern void UgFossilPcRadarEnd(void);
/// パソコン化石レーダーの開始が来た
extern void UgFossilRecvPcRadar(int netID, int size, void* pData, void* pWork);
/// パソコン化石レーダー返信
extern void UgFossilRecvPcRadarPos(int netID, int size, void* pData, void* pWork);
/// パソコン化石レーダー返信サイズ
extern int UgFossilGetPcRadarSize(void);

/// 毎フレーム行う必要がある処理
extern void UgFossilProcess(void);
/// レーダー用化石の位置X座標を得る
extern int UgFossilGetRadarPointX(int index);
/// レーダー用化石の位置Z座標を得る
extern int UgFossilGetRadarPointZ(int index);

/// レーダー用化石の位置X座標を得る
extern int UgFossilGetIntervalRadarPointX(int index);
/// レーダー用化石の位置Z座標を得る
extern int UgFossilGetIntervalRadarPointZ(int index);

/// 化石を一個この周辺に配置
extern void UgFossilOneSetup(int xbase,int zbase, MATHRandContext16* pRand);

/// 化石に関するLOGを返す
extern BOOL UgDigFossilGetActionMessage(STRBUF* pStrBuf);

extern BOOL UgDigFossilIsDig(int netID);
/// 離脱プレーヤーのパラメーター消し
extern void UgDigFossilResetPlayer(int netID);
/// かせき掘り初期化データ受信
//extern void CommFossilRecvInit(int netID, int size, void* pData, void* pWork);
/// かせき掘り初期化データ送信
//extern void UgDigFossilPlayerInit(void);

// 今化石を掘っているかどうか クライアント状態
extern BOOL UgDigFossilIsNow(void);
// 今化石を掘っているかどうか サーバー状態として保存
extern void UgDigFossilSetNow(int netID, int bDig);


#endif //__UG_MANAGER_H__
