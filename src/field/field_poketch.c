//===========================================================================
/**
 * @file	field_poketch.c
 * @brief	フィールド・ポケッチ間 連絡関数群
 * @author	taya	GAME FREAK Inc.
 *
 */
//===========================================================================
#include "common.h"

#include "field_common.h"
#include "field\poketch.h"

#include "field_poketch.h"
#include "fieldmap_work.h"
#include "fieldsys.h"

#include "system/render_oam.h"
#include "system/pm_overlay.h"
#include "field/eventflag.h"
#include "sysflag.h"

//------------------------------------------------------------------
/**
 * @brief	
 * @param	fsys		フィールド制御ワークへのポインタ
 * @param	id
 * @param	value
 */
//------------------------------------------------------------------
void Field_SendPoketchInfo( FIELDSYS_WORK* fsys, FIELD_POKETCH_SEND_ID id, u32 value )
{
	// ポケッチ起動中なら...
	if( fsys->fldmap->poketch != NULL )
	{
		Poketch_SendRequest( fsys->fldmap->poketch, id, value );
	}
}


//------------------------------------------------------------------
//------------------------------------------------------------------
///オーバーレイモジュールのextern宣言です。
FS_EXTERN_OVERLAY(ol_poketch);
FS_EXTERN_OVERLAY(ol_before_poketch);

//------------------------------------------------------------------
/**
 * @brief	ポケッチ初期化処理
 * @param	fsys		フィールド制御ワークへのポインタ
 */
//------------------------------------------------------------------
void FieldPoketch_Init( FIELDSYS_WORK * fsys )
{
	POKETCH_DATA* poketch_data = SaveData_GetPoketchData( fsys->savedata );
	EVENTWORK* ev = SaveData_GetEventWork( fsys->savedata );
	

	if( PoketchData_GetPoketchGetFlag( poketch_data )
			&& SysFlag_PoketchHookCheck(ev) == FALSE)
	{
		Overlay_Load( FS_OVERLAY_ID( ol_poketch ), OVERLAY_LOAD_NOT_SYNCHRONIZE );
		PoketchInit( fsys, &fsys->fldmap->poketch, fsys->savedata, fsys->bgl, REND_OAM_GetOamManagerInstance(REND_OAM_SUB) );
	}
	else
	{
		Overlay_Load( FS_OVERLAY_ID( ol_before_poketch ), OVERLAY_LOAD_NOT_SYNCHRONIZE );
		BeforePoketchInit( fsys->bgl );
	}
}

//------------------------------------------------------------------
/**
 * @brief	ポケッチ終了処理リクエスト
 * @param	fsys		フィールド制御ワークへのポインタ
 */
//------------------------------------------------------------------
void FieldPoketch_QuitReq( FIELDSYS_WORK * fsys )
{
	POKETCH_DATA* poketch_data = SaveData_GetPoketchData( fsys->savedata );
	EVENTWORK* ev = SaveData_GetEventWork( fsys->savedata );

	if( PoketchData_GetPoketchGetFlag( poketch_data )
			&& SysFlag_PoketchHookCheck(ev) == FALSE)
	{
		PoketchQuitReq( fsys->fldmap->poketch );
	}
	else
	{
		BeforePoketchQuitReq( fsys->bgl );
	}
}

//------------------------------------------------------------------
/**
 * @brief	ポケッチ終了処理待ち
 * @param	fsys		フィールド制御ワークへのポインタ
 */
//------------------------------------------------------------------
u8 FieldPoketch_QuitWait( FIELDSYS_WORK * fsys )
{
	POKETCH_DATA* poketch_data = SaveData_GetPoketchData( fsys->savedata );
	EVENTWORK* ev = SaveData_GetEventWork( fsys->savedata );

	if( PoketchData_GetPoketchGetFlag( poketch_data ) 
			&& SysFlag_PoketchHookCheck(ev) == FALSE)
	{
		if( PoketchQuitWait( fsys->fldmap->poketch ) ){
			fsys->fldmap->poketch = NULL;
			Overlay_UnloadID( FS_OVERLAY_ID( ol_poketch ) );
			return TRUE;
		}
	}
	else
	{
		if( BeforePoketchQuitWait( fsys->bgl ) )
		{
			Overlay_UnloadID( FS_OVERLAY_ID( ol_before_poketch ) );
			return TRUE;
		}
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	ポケッチ取得前画面の初期化
 * @param	fsys		フィールド制御ワークへのポインタ
 */
//------------------------------------------------------------------
void FieldBeforePoketch_Init( FIELDSYS_WORK * fsys )
{
	Overlay_Load( FS_OVERLAY_ID( ol_before_poketch ), OVERLAY_LOAD_NOT_SYNCHRONIZE );
	BeforePoketchInit( fsys->bgl );
}

//------------------------------------------------------------------
/**
 * @brief	ポケッチ取得前画面の終了リクエスト
 * @param	fsys		フィールド制御ワークへのポインタ
 */
//------------------------------------------------------------------
void FieldBeforePoketch_QuitReq( FIELDSYS_WORK * fsys )
{
	BeforePoketchQuitReq( fsys->bgl );
}

//------------------------------------------------------------------
/**
 * @brief	ポケッチ取得前画面の終了待ち
 * @param	fsys		フィールド制御ワークへのポインタ
 */
//------------------------------------------------------------------
BOOL FieldBeforePoketch_QuitWait( FIELDSYS_WORK * fsys )
{
	if( BeforePoketchQuitWait( fsys->bgl ) )
	{
		Overlay_UnloadID( FS_OVERLAY_ID( ol_before_poketch ) );
		return TRUE;
	}
	return FALSE;
}

