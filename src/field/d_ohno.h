//=============================================================================
/**
 * @file	d_ohno.h
 * @bfief	大野用デバッグルーチン
 * @author	katsumi ohno
 * @date	05/08/04
 */
//=============================================================================

#ifndef __D_OHNO_H__
#define __D_OHNO_H__
#ifdef PM_DEBUG


// デバッグ用に呼び出す最初の関数。メニューを開くため
extern void DebugCommMenuInit(void* pFSys);

// チャンネル表示をするウインドウを出すかどうか
extern BOOL DebugOhnoGetCommDebugDisp(void);
extern void DebugOhnoCommDebugDisp(void* pDummy);

// 地下接続をデバッグの為隣とつながらないようにした
extern void DebugOhnoCommDebugUnderNo(int no);
// 大きいデータのテスト
extern void CommDebugRecvHugeData(int netID, int size, void* pData, void* pWork);

//親機だけ、子機だけの接続
extern void DebugOhnoCommDebugUnderParentOnly(int no);
extern void DebugOhnoCommDebugUnderChildOnly(int no);


#endif//PM_DEBUG
#endif //__D_OHNO_H__
