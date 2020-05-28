//============================================================================================
/**
 * @file	fld_flg_init.c
 * @brief	�t�B�[���h�ړ��ł̃t���O�I�t�E�l�N���A�Ƃ��i�C�t�������������Ƃ��܂��j
 * @date	2006.05.23
 * @author	Nozomu Saito
 *
 */
//============================================================================================
#include "common.h"
#include "savedata/savedata.h"
#include "savedata/encount.h"
#include "savedata/vidro_type.h"
#include "sysflag.h"
#include "fieldsys.h"
#include "mapdata_warp.h"
#include "move_pokemon.h"
#include "zonedata.h"
#include "situation_local.h"
#include "sysflag.h"
#include "syswork.h"

#include "fld_flg_init.h"


static BOOL FldFlgInit_FnoteTownDataSet( FIELDSYS_WORK * fsys );
static BOOL FldFlgInit_FnoteMapChgDataSet( FIELDSYS_WORK * fsys );

//----------------------------------------------------------------------------
/**
 * @brief	�]�������[�h�̃Z�b�g
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	flag		TRUE�̂Ƃ��A�]�������[�h�ɃZ�b�g
 *
 * ����}�b�v���瑼�̃}�b�v���������������̏ꍇ�̂Ƃ��ɁA
 * �e��t���O�̍X�V���t�b�N����K�v������B���̏ꍇ�́A
 * �C�x���g�J�n���ɂ��̊֐����g���Ė]�������[�h�Ɉڍs���A
 * �}�b�v�J�ڂ��I�������]�������[�h���I������B
 */
//----------------------------------------------------------------------------
void FldFlg_SetScopeMode(FIELDSYS_WORK * fsys, BOOL flag)
{
	fsys->scope_mode_flag = flag;
}

//----------------------------------------------------------------------------
/**
 * @brief	�t���O�������F�����ă]�[�����܂������Ƃ��i�K���Ă΂��j
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
void FldFlgInit_Walk(FIELDSYS_WORK * fsys)
{
	//--�`���m�[�g�p�X�V����
	FldFlgInit_FnoteTownDataSet( fsys );

	//�����肫�t���O�̃N���A
	SysFlag_KairikiReset( SaveData_GetEventWork(fsys->savedata) );
	//�����t���O�̃Z�b�g
	ARRIVEDATA_SetArriveFlag(fsys, fsys->location->zone_id);
	//�r�[�h���N���A
	EncDataSave_SetVidro( EncDataSave_GetSaveDataPtr(fsys->savedata), VIDRO_NONE );
	//�G���J�E���g�����N���A
	fsys->encount.walk_count = 0;
	//�T�t�@���ɂ��Ȃ��Ƃ��̏���
	if ( !SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata)) ){
		//�ړ��|�P��������(�T�t�@�����]�[���؂�ւ��̂Ƃ��͗�����ς܂Ȃ�)
		ENC_SV_PTR data;
		data = EncDataSave_GetSaveDataPtr(fsys->savedata);
		MP_UpdatePlayerZoneHist(data, fsys->location->zone_id);		//�]�[���������X�V
		//�����Ĉړ������ꍇ�͈ړ��|�P�����̈ړ�����
		MP_MovePokemonNeighboring(data);//�ړ��|�P�����אڈړ�
	}
}

//----------------------------------------------------------------------------
/**
 * @brief	�t���O�������F���C�v�̂͂���}�b�v�W�����v�̂Ƃ�(�K���Ă΂��)
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
void FldFlgInit_MapJump(FIELDSYS_WORK * fsys)
{
	if (fsys->scope_mode_flag == TRUE) {
		//�]�������[�h�̏ꍇ�͍X�V�������s��Ȃ�
		return;
	}

	//--�`���m�[�g�p�X�V����
	if( FldFlgInit_FnoteTownDataSet( fsys ) == FALSE ){
		FldFlgInit_FnoteMapChgDataSet( fsys );
	}

	//�T�C�N�����O���[�h���[�h�̃N���A
	SysFlag_CyclingRoadReset( SaveData_GetEventWork(fsys->savedata) );
	//�����肫�t���O�̃N���A
	SysFlag_KairikiReset( SaveData_GetEventWork(fsys->savedata) );
	//�����t���O�̃Z�b�g
	ARRIVEDATA_SetArriveFlag(fsys, fsys->location->zone_id);
	//�r�[�h���N���A
	EncDataSave_SetVidro( EncDataSave_GetSaveDataPtr(fsys->savedata), VIDRO_NONE );
	//�G���J�E���g�����N���A
	fsys->encount.walk_count = 0;
	//�ړ��|�P��������
	{
		ENC_SV_PTR data;
		data = EncDataSave_GetSaveDataPtr(fsys->savedata);
		MP_UpdatePlayerZoneHist(data, fsys->location->zone_id);		//�]�[���������X�V
	}
	//�_���W�����łȂ��ꍇ�A�t���b�V����ԃt���O�Ɩ�������ԃt���O���N���A
	if (!ZoneData_IsDungeon(fsys->location->zone_id)) {
		EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
		SysFlag_FlashReset(ev);
		SysFlag_KiribaraiReset(ev);
	}
	//���@��Ԃ̐ݒ�
	{
		PLAYER_SAVE_DATA * jikisave = Situation_GetPlayerSaveData(SaveData_GetSituation(fsys->savedata));
		if (jikisave->form == HERO_FORM_CYCLE
				&& ZoneData_GetEnableBicycleFlag(fsys->location->zone_id) == FALSE) {
			jikisave->form = HERO_FORM_NORMAL;
		} else if (jikisave->form == HERO_FORM_SWIM) {
			jikisave->form = HERO_FORM_NORMAL;
		}
	}

	//--�^�E���}�b�v����
	if (ZoneData_IsSinouField(fsys->location->zone_id)) {
		//�t�B�[���h�ȊO�ł͑��Ղ̍X�V�͂Ȃ��I
		TOWN_MAP_FOOTMARK * footmark;
		footmark = Situation_GetTMFootMark(SaveData_GetSituation(fsys->savedata));
		TMFootMark_SetNoDir(footmark, fsys->location->grid_x, fsys->location->grid_z);
	}
}

//----------------------------------------------------------------------------
/**
 * @brief	�t���O�������F����Ԃ��g�����Ƃ��ŗL�ōs������
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
void FldFlgInit_FlySky(FIELDSYS_WORK * fsys)
{
	//�T�t�@���t���O�N���A
	SysFlag_SafariReset( SaveData_GetEventWork(fsys->savedata) );
	//�ړ��|�P�����S���W�����v
	MP_JumpMovePokemonAll(EncDataSave_GetSaveDataPtr(fsys->savedata));
}

//----------------------------------------------------------------------------
/**
 * @brief	�t���O�������F�e���|�[�g���g�����Ƃ��ŗL�ōs������
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
void FldFlgInit_Teleport(FIELDSYS_WORK * fsys)
{
	//�T�t�@���t���O�N���A
	SysFlag_SafariReset( SaveData_GetEventWork(fsys->savedata) );
	//�ړ��|�P�����S���W�����v
	MP_JumpMovePokemonAll(EncDataSave_GetSaveDataPtr(fsys->savedata));
}

//----------------------------------------------------------------------------
/**
 * @brief	�t���O�������F���Ȃʂ��̂Ђ��E���Ȃ��ق���g�����Ƃ��ŗL�ōs������
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
void FldFlgInit_Escape(FIELDSYS_WORK * fsys)
{
	//�T�t�@���t���O�N���A
	SysFlag_SafariReset( SaveData_GetEventWork(fsys->savedata) );
}

//----------------------------------------------------------------------------
/**
 * @brief	�t���O�������F�Q�[���I�[�o�[
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
void FldFlgInit_GameOver(FIELDSYS_WORK * fsys)
{
	EVENTWORK* ev = SaveData_GetEventWork( fsys->savedata );

	//�A������t���O�A�g���[�i�[ID�i�[���[�N�̃N���A
	SysFlag_PairReset( ev );
	SysWork_PairTrainerIDSet( ev, 0 );
}

//----------------------------------------------------------------------------
/**
 * @brief	�t���O�������F�R���e�B�j���[
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
void FldFlgInit_Continue(FIELDSYS_WORK * fsys)
{
	//�ړ��|�P�����S���W�����v
	MP_JumpMovePokemonAll(EncDataSave_GetSaveDataPtr(fsys->savedata));
}

//----------------------------------------------------------------------------
/**
 * @brief	�t���O�������F�n���ւ���
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
void FldFlgInit_UnderGround(FIELDSYS_WORK * fsys)
{
	;
}


//----------------------------------------------------------------------------
/**
 * @brief	�`���m�[�g�쐬�F���ɓ���
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @retval	"TURE = �쐬���ꂽ"
 * @retval	"FALSE = �쐬����Ȃ�����"
 *
 */
//-----------------------------------------------------------------------------
static BOOL FldFlgInit_FnoteTownDataSet( FIELDSYS_WORK * fsys )
{
	int warp_id = WARPDATA_SearchByFieldID( fsys->location->zone_id );

	if( warp_id != 0 && ARRIVEDATA_GetArriveFlag( fsys, warp_id ) == FALSE ){
		FNOTE_DataMakeSaveCity( fsys->fnote, fsys->location->zone_id, HEAPID_EVENT );
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 * @brief	�`���m�[�g�쐬�F�}�b�v�؂�ւ�
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @retval	"TURE = �쐬���ꂽ"
 * @retval	"FALSE = �쐬����Ȃ�����"
 *
 */
//-----------------------------------------------------------------------------
static BOOL FldFlgInit_FnoteMapChgDataSet( FIELDSYS_WORK * fsys )
{
	LOCATION_WORK * before = Situation_GetBeforeLocation( SaveData_GetSituation(fsys->savedata) );

	if( before->zone_id != fsys->location->zone_id ){
		FNOTE_DataMakeSaveMapChg(
			SaveData_GetMyStatus( fsys->savedata ),
			fsys->fnote, fsys->location->zone_id, before->zone_id, HEAPID_EVENT );
		return TRUE;
	}
	return FALSE;
}
