//===========================================================================
/**
 * @file	field_poketch.c
 * @brief	�t�B�[���h�E�|�P�b�`�� �A���֐��Q
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
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	id
 * @param	value
 */
//------------------------------------------------------------------
void Field_SendPoketchInfo( FIELDSYS_WORK* fsys, FIELD_POKETCH_SEND_ID id, u32 value )
{
	// �|�P�b�`�N�����Ȃ�...
	if( fsys->fldmap->poketch != NULL )
	{
		Poketch_SendRequest( fsys->fldmap->poketch, id, value );
	}
}


//------------------------------------------------------------------
//------------------------------------------------------------------
///�I�[�o�[���C���W���[����extern�錾�ł��B
FS_EXTERN_OVERLAY(ol_poketch);
FS_EXTERN_OVERLAY(ol_before_poketch);

//------------------------------------------------------------------
/**
 * @brief	�|�P�b�`����������
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
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
 * @brief	�|�P�b�`�I���������N�G�X�g
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
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
 * @brief	�|�P�b�`�I�������҂�
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
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
 * @brief	�|�P�b�`�擾�O��ʂ̏�����
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
void FieldBeforePoketch_Init( FIELDSYS_WORK * fsys )
{
	Overlay_Load( FS_OVERLAY_ID( ol_before_poketch ), OVERLAY_LOAD_NOT_SYNCHRONIZE );
	BeforePoketchInit( fsys->bgl );
}

//------------------------------------------------------------------
/**
 * @brief	�|�P�b�`�擾�O��ʂ̏I�����N�G�X�g
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
void FieldBeforePoketch_QuitReq( FIELDSYS_WORK * fsys )
{
	BeforePoketchQuitReq( fsys->bgl );
}

//------------------------------------------------------------------
/**
 * @brief	�|�P�b�`�擾�O��ʂ̏I���҂�
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
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

