#ifndef __VHCAT_H_
#define __VHCAT_H_
// ボイスチャット関係。
// dwc_rap.c とvchat.cからのみ呼び出される。
// ボイスチャットを呼ぶ場合は、dwc_rap.h経由で呼ぶ。

extern void myvct_init( int heapID, int codec );
extern void myvct_setCodec( int codec );
extern void myvct_main( );
extern BOOL myvct_checkData( int aid, void *data, int size );

extern void* mydwc_AllocFunc( DWCAllocType name, u32   size, int align );
extern void mydwc_FreeFunc( DWCAllocType name, void* ptr,  u32 size  );

//==============================================================================
/**
 * 会話終了処理完了コールバックを設定します。
 * 相手から切られた場合も呼び出されます。
 * この関数が呼び出される直前に、vchat.c用のワークが解放されます。
 * @param   none
 * @retval  none
 */
//==============================================================================
extern void myvct_setDisconnectCallback( void (*disconnectCallback)() );

//==============================================================================
/**
 * 会話終了要求をだします。まだ通話できていないときは即座に終了します。
 * myvct_setDisconnectCallbackで設定されたコールバックが呼び出されます。
 * @param   none
 * @retval  none
 */
//==============================================================================
extern void myvct_endConnection();

//==============================================================================
/**
 * ライブラリ終了処理。この中から会話終了処理完了コールバックも呼ばれます。
 * 通常終了時はこの関数は、会話終了要求から呼び出されます。
 * @param   none
 * @retval  none
 */
//==============================================================================
extern void myvct_free();

//==============================================================================
/**
 * 音声のノイズカットレベルを調整します（外部からアクセスしたいので、こちらに）
 * @param   d … 今より閾値を下げるか、上げるか（下げるほど拾いやすくなる）
 * @retval  none
 */
//==============================================================================
extern void myvct_changeVADLevel(int d);


// 送信したかどうかを返します
extern BOOL myvct_IsSendVoiceAndInc(void);

// ボイスチャットをオフにします。
extern void myvct_offVchat();

// ボイスチャットをオンにします。
extern void myvct_onVchat();

// ボイスチャットがオンかを返します。
extern BOOL myvct_isVchatOn();

#endif

