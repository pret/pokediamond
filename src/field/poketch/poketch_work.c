//============================================================================================
/**
 * @file	poketch_work.c
 * @bfief	ポケッチ（フィールド <-> 他画面 切り替わり時にも各種アプリの状況を記憶しておく領域）
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "field\poketch.h"
#include "poketch_prv.h"

enum {
	APPNUMBER_NULL = 0xffffffff,
	POKETCH_WORK_SIZE = 0x3000,
};

static int ReserveAppNumber = APPNUMBER_NULL;
static u8 PoketchWork[ POKETCH_WORK_SIZE ];



//------------------------------------------------------------------
/**
 * アプリ切り替え時に呼ばれ、予約アプリ番号をリセットする
 */
//------------------------------------------------------------------
void PoketchWork_Reset( void )
{
	ReserveAppNumber = APPNUMBER_NULL;
}


//------------------------------------------------------------------
/**
 * ポケッチワークエリアへアプリの任意データを保存
 *
 * @param   appNumber	アプリナンバー
 * @param   dat			保存データポインタ
 * @param   size		データサイズ
 *
 */
//------------------------------------------------------------------
void PoketchWork_Save( u32 appNumber, const void* dat, u32 size )
{
	if( size < POKETCH_WORK_SIZE )
	{
		MI_CpuCopy32( dat, PoketchWork, size );
		ReserveAppNumber = appNumber;
	}
	else
	{
		GF_ASSERT(0);
	}
}


//------------------------------------------------------------------
/**
 * ポケッチワークエリアから直前にセーブしたアプリデータをコピー
 *
 * @param   appNumber	アプリナンバー（一致しなければコピーしない）
 * @param   buf			データコピー先バッファ
 * @param   size		データサイズ
 *
 * @retval  BOOL		正しくコピーされたらTRUEが返る
 */
//------------------------------------------------------------------
BOOL PoketchWork_Load( u32 appNumber, void* buf, u32 size )
{
	if( size < POKETCH_WORK_SIZE )
	{
		if( appNumber == ReserveAppNumber )
		{
			MI_CpuCopy32( PoketchWork, buf, size );
			return TRUE;
		}
	}
	else
	{
		GF_ASSERT(0);
	}
	return FALSE;
}


//------------------------------------------------------------------
/**
 * ポケッチワークエリアへアプリの任意データを保存（高速版）
 *
 * @param   appNumber	アプリナンバー
 * @param   dat			保存データポインタ
 * @param   size		データサイズ
 *
 */
//------------------------------------------------------------------
void PoketchWork_SaveFast( u32 appNumber, const void* dat, u32 size )
{
	if( size < POKETCH_WORK_SIZE )
	{
		MI_CpuCopyFast( dat, PoketchWork, size );
		ReserveAppNumber = appNumber;
	}
	else
	{
		GF_ASSERT(0);
	}
}
//------------------------------------------------------------------
/**
 * ポケッチワークエリアから直前にセーブしたアプリデータをコピー（高速版）
 *
 * @param   appNumber	アプリナンバー（一致しなければコピーしない）
 * @param   buf			データコピー先バッファ
 * @param   size		データサイズ
 *
 * @retval  BOOL		正しくコピーされたらTRUEが返る
 */
//------------------------------------------------------------------
BOOL PoketchWork_LoadFast( u32 appNumber, void* buf, u32 size )
{
	if( size < POKETCH_WORK_SIZE )
	{
		if( appNumber == ReserveAppNumber )
		{
			MI_CpuCopyFast( PoketchWork, buf, size );
			return TRUE;
		}
	}
	else
	{
		GF_ASSERT(0);
	}
	return FALSE;
}
