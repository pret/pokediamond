#ifndef ___MPREQUEST_H___
#define ___MPREQUEST_H___
/**
 * @version "$Id: mprequest.h,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file mprequest.h
 * @brief 無線通信ライブラリ 状態遷移関数
 * 
 */
#ifdef __cplusplus
extern "C" {
#endif


/**
 * PORT通信を行う
 *
 * @return エラーが発生した場合FALSEが返る
 */
extern BOOL MpRequestSetMPData(const void *buf, u32 size, u16 aid_bitmap);

       
/**
 * 無線デバイスを使用可能な状態にする
 *
 * @return エラーが発生した場合FALSEが返る
 */
extern BOOL MpRequestEnable(void);


/**
 * 無線デバイスを使用不可の状態にする
 *
 * @return エラーが発生した場合FALSEが返る
 */
extern BOOL MpRequestDisable(void);
  

/**
 * 指定チャンネルの電波使用率を測定
 *
 * @param チャンネル番号（1,7,13） 
 * @return エラーが発生した場合FALSEが返る
 */
extern BOOL MpRequestSearchChannel(u32 channel);
  
       
/**
 * 親機として必要なパラメータを設定
 *
 * @return エラーが発生した場合FALSEが返る
 */
extern BOOL MpRequestSetParentParameter(void);
  

/**
 * 親機として活動開始
 *
 * @return エラーが発生した場合FALSEが返る
 */
extern BOOL MpRequestStartParent(void);


/**
 * 子機として親機のスキャン開始
 *
 * @return エラーが発生した場合FALSEが返る
 */
extern BOOL MpRequestStartScan(void);


/**
 * 子機として特定の親機のスキャン開始
 *
 * @return エラーが発生した場合FALSEが返る
 */
extern BOOL MpRequestStartScan2(void);
  

/**
 * 子機の親機スキャン終了
 *
 * @return エラーが発生した場合FALSEが返る
 */
extern BOOL MpRequestEndScan(void);
  

/**
 * 親機への接続開始
 *
 * @return エラーが発生した場合FALSEが返る
 */
extern BOOL MpRequestStartConnect(void);

  
/**
 * 接続解除
 *
 * @param 対象AID
 * @return エラーが発生した場合FALSEが返る
 */
extern BOOL MpRequestDisConnect(u16 aid);


/**
 * 複数の子機との接続解除 （親機専用）
 *
 * @param 対象AIDビットマップ
 * @return エラーが発生した場合FALSEが返る
 */
extern BOOL MpRequestDisConnectChildren(u16 aid_bit);
  
       
/**
 * MP通信モード開始
 *
 * @return エラーが発生した場合FALSEが返る
 */
extern BOOL MpRequestStartMP(void);


/**
 * 無線デバイスに電源投入
 *
 * @return エラーが発生した場合FALSEが返る
 */
extern BOOL MpRequestPowerOn(void);


/**
 * 無線デバイスの電源OFF
 *
 * @return エラーが発生した場合FALSEが返る
 */
extern BOOL MpRequestPowerOff(void);


/**
 * WMをリセット WMのREADY、IDLEステート以外全てのステートからIDLEステートに移行
 *
 * @return エラーが発生した場合FALSEが返る
 */
extern BOOL MpRequestReset(void);
  

/**
 * WMを終了 WMのIDLEステートから無線機能全停止に移行
 *
 * @return エラーが発生した場合FALSEが返る
 */
extern BOOL MpRequestEnd(void);

       
#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif // ___MPREQUEST_H___
  

  
