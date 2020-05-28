//=============================================================================
/**
 * @file	comm_tool.h
 * @brief	通信システムを使った通信ツール
 * @author	Katsumi Ohno
 * @date    2006.03.14
 */
//=============================================================================

#ifndef __COMM_TOOL_H__
#define __COMM_TOOL_H__

extern void CommToolInitialize(int heapID);
extern void CommToolFinalize(void);
extern BOOL CommToolIsInitialize(void);


extern void CommRecvTimingSync(int netID, int size, void* pData, void* pWork);
extern void CommRecvTimingSyncInfo(int netID, int size, void* pData, void* pWork);
extern void CommRecvTimingSyncEnd(int netID, int size, void* pData, void* pWork);
extern void CommTimingSyncStart(u8 no);
extern BOOL CommIsTimingSync(u8 no);
extern int CommGetTimingSyncNo(int netID);
extern void CommTimingSyncSend(void);

extern void CommRecvListNo(int netID, int size, void* pData, void* pWork);
extern int CommGetListNoSize(void);
extern void CommListSet(u8 no,u8 listNo);
extern int CommListGet(int netID, u8 no);
extern void CommListReset(void);

// 初期化する
extern void CommToolTempDataReset(void);
// 相手に送りたいデータを入れる  10byte
extern BOOL CommToolSetTempData(int netID,const void* pData);
// * 相手に送ったデータを得る  10byte
extern const void* CommToolGetTempData(int netID);
// * テンポラリーデータを受信する
void CommToolRecvTempData(int netID, int size, void* pData, void* pWork);
// テンポラリーデータサイズを返す
int CommToolGetTempDataSize(void);



#define  INVALID_LIST_NO  (-1)

#endif  //__COMM_TOOL_H__


