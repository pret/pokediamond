#ifndef ___MPDEBUG_H___
#define ___MPDEBUG_H___
/**
 * @version "$Id: mpdebug.h,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file mpdebug.h
 * @brief MP無線通信デバッグ用関数
 * 
 */
#include "mpconnect.h"  

#ifdef __cplusplus
extern "C" {
#endif

  
/**
 * 指定ステータスを文字列で返す
 */
extern const char* MpGetStatusString(MP_STATUS status);


/**
 * エラーコードを表示する
 *
 * @param WMが返すエラーコード
 */
extern void MpPrintErrorCode(WMErrCode code);


/**
 * ステータスコードを表示する
 *
 * @param WMが返すステータスコード
 */
extern  void MpPrintStateCode(WMStateCode code);


/**
 * WMBssDescの内容を表示する
 */
extern void MpPrintBssDesc(WMBssDesc *desc);


/**
 * MpDataChildMPの内容を表示する
 */
extern void MpPrintDataChildMP(MpDataChildMP *drmp);


/**
 * MpDataParentMPの内容を表示する
 */
extern void MpPrintDataParentMP(MpDataParentMP *dpmp);
  

/**
 * MP_CONTROL_CODEを文字列返す
 */
extern const char* MpPrintControlCode(MP_CONTROL_CODE code);

       
/**
 * MpSendHeaderの内容を表示する
 */
extern void MpPrintSendHeader(MpSendHeader *header);

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif // ___MPDEBUG_H___
