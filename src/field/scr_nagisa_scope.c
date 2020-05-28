//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		scr_nagisa_scope.c
 *	@brief		�i�M�T�V�e�B�@����]����
 *	@author		tomoya takahashi
 *	@data		2006.07.10
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "fieldsys.h"
#include "field_event.h"
#include "ev_mapchange.h"
#include "system/wipe.h"
#include "system/snd_tool.h"
#include "map_jump.h"		//for wipe
#include "fieldmap_work.h"	//for hblamk wipe
#include "sysflag.h"

#include "fielddata/maptable/zone_id.h"

#include "fld_flg_init.h"


#define __SCR_NAGISA_SCOPE_H_GLOBAL
#include "scr_nagisa_scope.h"

//-----------------------------------------------------------------------------
/**
 *					�R�[�f�B���O�K��
 *		���֐���
 *				�P�����ڂ͑啶������ȍ~�͏������ɂ���
 *		���ϐ���
 *				�E�ϐ�����
 *						const�ɂ� c_ ��t����
 *						static�ɂ� s_ ��t����
 *						�|�C���^�ɂ� p_ ��t����
 *						�S�č��킳��� csp_ �ƂȂ�
 *				�E�O���[�o���ϐ�
 *						�P�����ڂ͑啶��
 *				�E�֐����ϐ�
 *						�������Ɓh�Q�h�Ɛ������g�p���� �֐��̈���������Ɠ���
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define WAIT_KEY	( PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�X�R�[�v�f�[�^
//=====================================
typedef struct
{
	FIELDSYS_WORK * fsys;
	u16 pos_x;	// �߂��X
	u16 pos_z;	// �߂��Z

	u8 seq;
	u8 dummy[3];
}SCOPE_EVENT_WORK;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static BOOL GMEVENT_NagisaScope( GMEVENT_CONTROL * event );
static void NagisaScope_PlayerVanish( PLAYER_STATE_PTR jiki, BOOL vanish );
static void NagisaScope_CameraSet( FIELDSYS_WORK* p_fsys );


//----------------------------------------------------------------------------
/**
 *	@brief	�i�M�T�V�e�B�@�]�����@�C�x���g�R�[��
 *
 *	@param	fsys	�t�B�[���h�V�X�e��
 */
//-----------------------------------------------------------------------------
void CallNagisaScopeEvent(FIELDSYS_WORK * fsys)
{
	SCOPE_EVENT_WORK * sew = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(SCOPE_EVENT_WORK));

	memset( sew, 0, sizeof(SCOPE_EVENT_WORK) );
	
	//�}�b�v�W�����v�C�x���g���쐬
	FieldEvent_Call(fsys->event, GMEVENT_NagisaScope, sew);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�i�M�T�V�e�B�[�@�]�����@�C�x���g
 *
 *	@param	event	�C�x���g�|�C���^
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_NagisaScope( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * p_fsys = FieldEvent_GetFieldSysWork(event);
	SCOPE_EVENT_WORK * p_work = FieldEvent_GetSpecialWork(event);
	EVENTWORK* p_sv_event = SaveData_GetEventWork( p_fsys->savedata );

	switch( p_work->seq ){
	case 0:
		// �����̈ʒu��ۑ�
		p_work->pos_x = Player_NowGPosXGet( p_fsys->player );
		p_work->pos_z = Player_NowGPosZGet( p_fsys->player );

		// �]����Ӱ�ސݒ�
		FldFlg_SetScopeMode( p_fsys, TRUE );

		// �t�F�[�h�A�E�g
		EventCmd_FieldFadeOut(event);			//�t�F�[�h�A�E�g
		p_work->seq ++;
		break;

	case 1:	// �t�B�[���h�v���Z�X	�I��
		EventCmd_FinishFieldMap(event);
		p_work->seq ++;
		break;

	case 2:	// �}�b�v�J��
		// �|�P�b�`OFF
		SysFlag_PoketchHookSet( p_sv_event );
		{
			LOCATION_WORK location;
			SetLocation( &location, ZONE_ID_C10, DOOR_ID_JUMP_CODE, 847, 561, DIR_DOWN );
			EventCmd_MapChangeByLocation(event, &location);
		}
		p_work->seq ++;
		break;

	case 3:	// �t�B�[���h�J�n
		EventCmd_StartFieldMap(event);
		p_work->seq ++;
		break;

	case 4:	// ���C�vIN
		NagisaScope_PlayerVanish( p_fsys->player, TRUE );
		NagisaScope_CameraSet( p_fsys );
		MJUMP_RequestWipe( event,WIPE_PATTERN_M, WIPE_TYPE_HOLEIN,
					0xffff,0x0000,WIPE_DEF_DIV,WIPE_DEF_SYNC,HEAPID_WORLD);
		Snd_SePlay( SEQ_SE_DP_KASYA );		//�`�����Ƃ��̉�

		p_work->seq ++;
		break;

	case 5:	// �L�[�҂�
		if( (sys.trg & WAIT_KEY) ){
			p_work->seq ++;
		}
		break;

	case 6:	// ���C�v�A�E�g
		MJUMP_RequestWipe( event,WIPE_PATTERN_M, WIPE_TYPE_HOLEOUT,
					0xffff,0x0000,WIPE_DEF_DIV,WIPE_DEF_SYNC,HEAPID_WORLD);
		Snd_SePlay( SEQ_SE_DP_KASYA );		//�����Ƃ��̉�

		p_work->seq ++;
		break;

	case 7:
		EventCmd_FinishFieldMap(event);
		p_work->seq ++;
		break;

	case 8:	// ��ʕ��A
		// �|�P�b�`OFF
		SysFlag_PoketchHookReset( p_sv_event );
		{
			LOCATION_WORK location;
			SetLocation( &location, ZONE_ID_C08R0801,DOOR_ID_JUMP_CODE,p_work->pos_x,p_work->pos_z,DIR_UP );
			EventCmd_MapChangeByLocation(event, &location);
		}
		p_work->seq ++;
		break;

	case 9:
		EventCmd_StartFieldMap(event);
		p_work->seq ++;
		break;

	case 10:
		NagisaScope_PlayerVanish( p_fsys->player, FALSE );
		EventCmd_FieldFadeIn(event);		//�t�F�[�h�C��
		p_work->seq ++;
		break;

	case 11:	// �I������
		sys_FreeMemoryEz( p_work );

		// �]����Ӱ�ސݒ�
		FldFlg_SetScopeMode( p_fsys, FALSE );
		return TRUE;
	}
	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�v���C���[�̃o�j�b�V��
 *
 *	@param	jiki	�v���C���[
 *	@param	vanish	TRUE	��\��
 */
//-----------------------------------------------------------------------------
static void NagisaScope_PlayerVanish( PLAYER_STATE_PTR jiki, BOOL vanish )
{
	FIELD_OBJ_PTR player = Player_FieldOBJGet( jiki );
	FieldOBJ_StatusBitSet_Vanish( player, vanish );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�����ݒ�
 */
//-----------------------------------------------------------------------------
static void NagisaScope_CameraSet( FIELDSYS_WORK* p_fsys )
{
	VecFx32 matrix;
	CAMERA_ANGLE angle;

	// �J�����p�����[�^�ݒ�
	GFC_SetCameraPerspWay( 0x8c1, p_fsys->camera_ptr );	
	GFC_SetCameraDistance( 0xf81b8, p_fsys->camera_ptr );
	matrix.x = 0x350523d;
	matrix.y = 0x15edb7;
	matrix.z = 0x23da40e;
	GFC_SetLookTarget( &matrix, p_fsys->camera_ptr );
	angle.x = 0x823;
	angle.y = 0x520;
	angle.z = 0;
	GFC_SetCameraAngleRev( &angle, p_fsys->camera_ptr );
	GFC_SetCameraClip( 12*FX32_ONE, 1564*FX32_ONE, p_fsys->camera_ptr );
}
