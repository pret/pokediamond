//============================================================================================
/**
 * @file	sleep.c
 * @brief	スリープモード設定
 * @author	Hiroyuki Nakamura
 * @date	2005.02.28
 */
//============================================================================================
#define	SLEEP_H_GLOBAL

#include "system.h"
#include "standard.h"
#include "tcb.h"
#include "gflib_os_print.h"

#include "sleep.h"


//============================================================================================
//	シンボル定義
//============================================================================================


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void CoverCloseCheckTask( TCB_PTR _tcb, void * work );


//============================================================================================
//	設定
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * スリープデータ領域確保、初期化
 *
 * @param	heap	ヒープID
 *
 * @return	スリープデータ領域
 */
//--------------------------------------------------------------------------------------------
GF_SLEEP_SYS * GF_SleepSystemInit( u32 heap )
{
	GF_SLEEP_SYS * dat = (GF_SLEEP_SYS *)sys_AllocMemory( heap, sizeof(GF_SLEEP_SYS) );

#ifdef	OSP_ERR_SLEEPBUF_GET	// スリープ用のバッファ確保失敗
	if( dat == NULL ){
		OS_Printf( "ERROR : GF_SleepSystemInit\n" );
		return;
	}
#endif	// OSP_ERR_SLEEPBUF_GET	// スリープ用のバッファ確保失敗

	memset( dat, 0, sizeof(GF_SLEEP_SYS) );
	dat->heap = (u16)heap;

	return dat;
}

//--------------------------------------------------------------------------------------------
/**
 * システム消去
 *
 * @param	dat		スリープデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_SleepSystemDelete( GF_SLEEP_SYS * dat )
{
#ifdef	OSP_ERR_SLEEP_DEL		// スリープ用のバッファを確保していない
	if( dat == NULL ){
		OS_Printf( "ERROR : GF_SleepSystemDelete\n" );
		return;
	}
#endif	// OSP_ERR_SLEEP_DEL

	GF_SleepCallBackDel( dat, GF_SLEEP_CB_BEFORE );
	GF_SleepCallBackDel( dat, GF_SLEEP_CB_AFTER );
	sys_FreeMemory( dat->heap, dat );
}

//--------------------------------------------------------------------------------------------
/**
 * スリープのトリガー設定
 *
 * @param	dat		スリープデータ
 * @param	trg		スリープ状態からの復帰要因
 * @param	logic	キー割込みで復帰する場合のキーの組み合わせ論理
 * @param	pat		キー割込みで復帰する場合のキー
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_SleepTriggerSet( GF_SLEEP_SYS * dat, PMWakeUpTrigger trg, PMLogic logic, u16 pat )
{
	dat->trigger = trg;
	dat->logic = logic;
	dat->keyPattern = pat;
}

//--------------------------------------------------------------------------------------------
/**
 * スリープデータ設定
 *
 * @param	dat		スリープデータ
 *
 * @return	none
 *
 * @li	dat->hold : GF_SLEEP_MODE = 即スリープ
 * @li	スリープを不許可にするにはGF_SleepModeSet(GF_SLEEP_HOLD)を呼ぶこと
 */
//--------------------------------------------------------------------------------------------
void GF_SleepSystemSetAll( GF_SLEEP_SYS * dat )
{
	u16	init;

#ifdef	OSP_ERR_SLEEP_SET		// スリープ設定失敗
	if( dat == NULL ){
		OS_Printf( "ERROR : GF_SleepSystemSetAll\n" );
		return;
	}
#endif	// SP_ERR_SLEEP_SET

	init = dat->hold;
	dat->hold = GF_SLEEP_MODE;

	if( dat->b_info.callback != NULL ){
		GF_SleepCallBackAdd( dat, &dat->b_info, GF_SLEEP_CB_BEFORE, GF_SLEEP_CB_BEFORE );
	}
	if( dat->a_info.callback != NULL ){
		GF_SleepCallBackAdd( dat, &dat->a_info, GF_SLEEP_CB_AFTER, GF_SLEEP_CB_BEFORE );
	}

	if( init == GF_SLEEP_MODE ){
		GF_GoSleepMode( dat );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 動作切り替え
 *
 * @param	dat		スリープデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_GoSleepMode( GF_SLEEP_SYS * dat )
{
	if( dat->hold == GF_SLEEP_HOLD ){ return; }
	PM_GoSleepMode( dat->trigger, dat->logic, dat->keyPattern );
}

//--------------------------------------------------------------------------------------------
/**
 * 動作切り替え
 *
 * @param	dat		スリープデータ
 * @param	flg		GF_SLEEP_MODE = 許可, GF_SLEEP_HOLD = 不許可
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_SleepModeSet( GF_SLEEP_SYS * dat, u8 flg )
{
	dat->hold = flg;
}


//============================================================================================
//	コールバック
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * コールバック情報セット
 *
 * @param	dat		スリープデータ
 * @param	info	コールバック情報
 * @param	type	追加タイプ ( GF_SLEEP_CB_BEFORE = 移行時, GF_SLEEP_CB_AFTER = 復帰時 )
 * @param	mode	追加モード ( GF_SLEEP_CB_BEFORE = 先頭へ, GF_SLEEP_CB_AFTER = 末尾へ )
 *
 * @return	none
 *
 * @li	複数登録は未対応
 */
//--------------------------------------------------------------------------------------------
void GF_SleepCallBackAdd( GF_SLEEP_SYS * dat, PMSleepCallbackInfo * info, u8 type, u8 mode )
{
	u8	i;

	if( type == GF_SLEEP_CB_BEFORE ){
#ifdef	OSP_ERR_SLEEP_CALLBACK_SET		// コールバック設定失敗
		if( dat->b_info.callback != NULL ){
			OS_Printf( "ERROR : GF_SleepCallBackAdd( GF_SLEEP_CB_BEFORE )\n" );
			return;
		}
#endif	// OSP_ERR_SLEEP_CALLBACK_SET
		dat->b_info = *info;

		if( mode == GF_SLEEP_CB_BEFORE ){
			PM_PrependPreSleepCallback( &dat->b_info );
		}else{
			PM_AppendPreSleepCallback( &dat->b_info );
		}
	}else{
#ifdef	OSP_ERR_SLEEP_CALLBACK_SET		// コールバック設定失敗
		if( dat->a_info.callback != NULL ){
			OS_Printf( "ERROR : GF_SleepCallBackAdd( GF_SLEEP_CB_AFTER )\n" );
			return;
		}
#endif	// OSP_ERR_SLEEP_CALLBACK_SET
		dat->a_info = *info;

		if( mode == GF_SLEEP_CB_BEFORE ){
			PM_PrependPostSleepCallback( &dat->a_info );
		}else{
			PM_AppendPostSleepCallback( &dat->a_info );
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * コールバック情報削除
 *
 * @param	dat		スリープデータ
 * @param	id		削除タイプ ( GF_SLEEP_CB_BEFORE = 移行時, GF_SLEEP_CB_AFTER = 復帰時 )
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_SleepCallBackDel( GF_SLEEP_SYS * dat, u8 id )
{
	if( id == GF_SLEEP_CB_BEFORE ){
		if( dat->b_info.callback == NULL ){ return; }
		PM_DeletePreSleepCallback( &dat->b_info );
	}else{
		if( dat->a_info.callback == NULL ){ return; }
		PM_DeletePostSleepCallback( &dat->a_info );
	}
}


//============================================================================================
//	本体の開閉でスリープ
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 本体の開閉でスリープするタスクをセット
 *
 * @param	dat		スリープデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_SleepCoverCloseAdd( GF_SLEEP_SYS * dat )
{
/*
	GF_SLEEP_SYS	dat = {
		{NULL,NULL,NULL}, {NULL,NULL,NULL}, PM_TRIGGER_COVER_OPEN, 0, 0, 1
	};

	GF_SleepSystemSetAll( &dat );
*/
	GF_SleepTriggerSet( dat, PM_TRIGGER_COVER_OPEN, 0, 0 );
	TCB_Add( CoverCloseCheckTask, dat, 0 );
}

//--------------------------------------------------------------------------------------------
/**
 * 本体の開閉でスリープするタスク
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CoverCloseCheckTask( TCB_PTR _tcb, void * work )
{
	if( PAD_DetectFold() == FALSE ){ return; }

	{
		GF_SLEEP_SYS * dat = (GF_SLEEP_SYS *)work;
		GF_GoSleepMode( dat );
	}
}
