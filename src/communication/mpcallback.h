#ifndef ___MPCALLBACK_H___
#define ___MPCALLBACK_H___
/**
 * @version "$Id: mpcallback.h,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file twl_callback.h
 * @brief 無線通信ライブラリ 状態遷移コールバック関数
 * 
 */
#ifdef __cplusplus
extern "C" {
#endif


/**
 * Indicationコールバック関数
 */
extern void MpCallbackIndicate(void *arg);
  

/**
 * MpRequestSetMPDataToPortのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
extern void MpCallbackSetMPDataToPort(void *arg);


/**
 * MpRequestEnableのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
extern void MpCallbackEnable(void *arg);

  
/**
 * MpRequestDisableのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
extern void MpCallbackDisable(void *arg);


/**
 * MpRequestSearchChannelのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体 
 */
extern void MpCallbackSearchChannel(void *arg);

       
/**
 * MpRequestSetParentParameterのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体 
 */
extern void MpCallbackSetParentParameter(void *arg);

       
/**
 * MpRequestStartParentのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体 
 */
extern void MpCallbackStartParent(void *arg);


/**
 * MpRequestStartScanのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体 
 */
extern void MpCallbackStartScan(void *arg);


/**
 * MpRequestStartScan2のコールバック関数
 *
 * @param arg WM非同期処理関数用構造体 
 */
extern void MpCallbackStartScan2(void *arg);
  
  
/**
 * MpRequestEndScanのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
extern void MpCallbackEndScan(void *arg);


/**
 * MpRequestStartConnectのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
extern void MpCallbackStartConnect(void *arg);

  
/**
 * MpRequestDisConnectのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
extern void MpCallbackDisConnect(void *arg);


/**
 * MpRequestDisConnectChildrenのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
extern void MpCallbackDisConnectChildren(void *arg);
  
       
/**
 * MpRequestStatMPのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
extern void MpCallbackStartMP(void *arg);


/**
 * WM_SetPortCallbackのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
extern void MpCallbackReceiveData(void *arg);

  
/**
 * MpRequestPowerOnのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
extern void MpCallbackPowerOn(void *arg);


/**
 * MpRequestPowerOffのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
extern void MpCallbackPowerOff(void *arg);


/**
 * MpRequestResetのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
extern void MpCallbackReset(void *arg);
  

/**
 * MpRequestEndのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
extern void MpCallbackEnd(void *arg);


  
#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif // ___MPCALLBACK_H___
  

  
