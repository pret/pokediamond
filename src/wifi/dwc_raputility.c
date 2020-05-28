//=============================================================================
/**
 * @file	dwc_raputility.c
 * @bfief	DWCラッパー。バトルオーバーレイ２層に並列  06.03.25
 * @author	kazuki yoshihara  -> k.ohno
 * @date	06/03/25
 */
//=============================================================================

#include "common.h"
#include "wifi/dwc_rap.h"
#include "communication/communication.h"

//==============================================================================
/**
 * WiFi接続ユーティリティを呼び出す
 * @param   none
 * @retval  none
 */
//==============================================================================
void mydwc_callUtility( int HeapID )
{
	OSIntrMode old;
	void *work;

	CommVRAMDInitialize(); // 
	// アラームシステムを初期化しておかないとDWC_StartUtility呼出し後にPanicが発生する
	OS_InitTick();
	OS_InitAlarm();


	// 割り込み処理を一旦禁止へ
	old = OS_DisableInterrupts();

	// WiFi設定メニュー呼び出し（終わるまで帰ってこない)
	work = sys_AllocMemory( HeapID, DWC_UTILITY_WORK_SIZE );
	(void)DWC_StartUtility( work, DWC_LANGUAGE_JAPANESE, DWC_UTILITY_TOP_MENU_FOR_JPN );
	sys_FreeMemoryEz( work );

	// 禁止した割り込み処理を復帰
	OS_RestoreInterrupts( old );

	//マスター割り込み処理を有効に
	OS_EnableIrq( ); 


}