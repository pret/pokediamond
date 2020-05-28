//=============================================================================
/**
 * @file	rah_cylinder_anm.c
 * @bfief	���C�E�A�C�E�n�C�̃V�����_�[�A�j��
 * @author	Nozomu Saito
 *
 */
//=============================================================================
#include "common.h"
#include "fieldsys.h"
#include "field_3d_anime.h"
#include "fielddata/build_model/build_model_id.h"
#include "field\sysflag.h"

#include "rah_cylinder_anm.h"

static BOOL AnimeEvent(GMEVENT_CONTROL * event);

//--------------------------------------------------------------
/**
 * ������
 *
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
void RAH_CYL_ANM_Setup(FIELDSYS_WORK *fsys)
{
	FLD_3D_ANM_DAT_PTR anime;
	//�~�o�C�x���g�t���O�ɂ���ĕ���
	if ( !SysFlag_ReiAiHaiCheck( SaveData_GetEventWork(fsys->savedata) ) ){
		//�~�o�O
		//1�ԃA�j�����J�n�t���[���Œ�~ ���[�v����1�ɃZ�b�g
		anime = F3DA_GetFld3DAnmPtr( BMID_D26_O02, 1, fsys->field_3d_anime );
		F3DA_SetAnimeLoopMax(anime, 1);
		F3DA_SetStopFlg(anime, TRUE);
	}else{
		//�~�o��
		//0�ԃA�j�����~�@1�ԃA�j�����ŏI�t���[���Œ�~
		anime = F3DA_GetFld3DAnmPtr( BMID_D26_O02, 0, fsys->field_3d_anime );
		F3DA_SetStopFlg(anime, TRUE);
		anime = F3DA_GetFld3DAnmPtr( BMID_D26_O02, 1, fsys->field_3d_anime );
		F3DA_SetLastFrame(anime);
		F3DA_SetStopFlg(anime, TRUE);
	}
}

//--------------------------------------------------------------
/**
 * �V�����_�[�~�o�A�j���J�n
 *
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
void RAH_CYL_ANM_StartFreeEvent(FIELDSYS_WORK *fsys)
{
	//�A�j���C�x���g�R�[��
	FieldEvent_Call(fsys->event, AnimeEvent, NULL);
}

//--------------------------------------------------------------
/**
 * �V�����_�[�~�o�A�j���C�x���g
 *
 * @param	event	�C�x���g�|�C���^
 *
 * @retval	BOOL	TRUE:�C�x���g�I��	FALSE:�C�x���g�p��
 */
//--------------------------------------------------------------
static BOOL AnimeEvent(GMEVENT_CONTROL * event)
{
	int *seq;
	FLD_3D_ANM_DAT_PTR anime;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	
	seq  = FieldEvent_GetSeqWork(event);
	switch(*seq){
	case 0: //0�ԃA�j���̍ŏI�t���[���҂�
		//�A�j������
		anime = F3DA_GetFld3DAnmPtr( BMID_D26_O02, 0, fsys->field_3d_anime );
		if ( F3DA_IsLastFrame(anime) ){
			F3DA_SetStopFlg(anime, TRUE);		//��~
			(*seq)++;
		}
		break;
	case 1: //1�ԃA�j���X�^�[�g
		//�A�j������
		anime = F3DA_GetFld3DAnmPtr( BMID_D26_O02, 1, fsys->field_3d_anime );
		F3DA_SetStopFlg(anime, FALSE);		//�Đ�
		(*seq)++;
		break;
	case 2:	//1�ԃA�j���҂�
		anime = F3DA_GetFld3DAnmPtr( BMID_D26_O02, 1, fsys->field_3d_anime );
		if ( F3DA_IsAnimeEnd(anime) ){
			return TRUE;
		}
		break;
	}
	return FALSE;
}
