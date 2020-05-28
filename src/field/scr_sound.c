//============================================================================================
/**
 * @file	scr_sound.c
 * @bfief	�X�N���v�g�R�}���h�F�T�E���h�֘A
 * @author	Satoshi Nohara
 * @date	06.06.26
 */
//============================================================================================
#include "common.h"
#include "system/lib_pack.h"
#include "fieldsys.h"

#include "script.h"
#include "scrcmd_def.h"
#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "syswork.h"

#include "savedata/perapvoice.h"
#include "system/snd_tool.h"
#include "system/snd_perap.h"
#include "fld_bgm.h"


//============================================================================================
//
//	�v�����g�^�C�v�錾
//
//============================================================================================
static BOOL EvWaitBgmFade( VM_MACHINE * core );
static BOOL EvWaitSe(VM_MACHINE * core);
static BOOL EvWaitVoicePlay(VM_MACHINE * core);
static BOOL EvWaitMe( VM_MACHINE * core );

BOOL EvCmdBgmPlay(VM_MACHINE * core );
BOOL EvCmdBgmStop(VM_MACHINE * core );
BOOL EvCmdBgmNowMapPlay(VM_MACHINE * core );
BOOL EvCmdBgmSpecialSet(VM_MACHINE * core );
BOOL EvCmdBgmFadeOut( VM_MACHINE * core );
BOOL EvWaitBgmFade( VM_MACHINE * core );
BOOL EvCmdBgmFadeIn( VM_MACHINE * core );
BOOL EvCmdBgmPlayerPause( VM_MACHINE * core );
BOOL EvCmdPlayerFieldDemoBgmPlay( VM_MACHINE * core );
BOOL EvCmdCtrlBgmFlagSet( VM_MACHINE * core );
BOOL EvCmdSePlay( VM_MACHINE * core );
BOOL EvCmdSeStop( VM_MACHINE * core );
BOOL EvCmdSeWait(VM_MACHINE * core);
BOOL EvCmdVoicePlay( VM_MACHINE * core );
BOOL EvCmdVoicePlayWait( VM_MACHINE * core );
BOOL EvCmdMePlay(VM_MACHINE * core );
BOOL EvCmdMeWait(VM_MACHINE * core );
BOOL EvCmdPerapDataCheck( VM_MACHINE * core );
BOOL EvCmdPerapRecStart( VM_MACHINE * core );
BOOL EvCmdPerapRecStop( VM_MACHINE * core );
BOOL EvCmdPerapSave( VM_MACHINE * core );
BOOL EvCmdSndClimaxDataLoad( VM_MACHINE * core );
BOOL EvCmdSndInitialVolSet( VM_MACHINE * core );
BOOL EvCmdBgmPlayCheck(VM_MACHINE * core );


//============================================================================================
//
//	�R�}���h
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * BGM�I���҂�
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBgmPlayCheck( VM_MACHINE * core )
{
	u16 music	= VMGetU16(core);
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = Snd_BgmPlayCheck( music );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * BGM�ύX
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBgmPlay( VM_MACHINE * core )
{
	u16 music = VMGetU16(core);
	Snd_BgmPlay( music );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * BGM��~
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBgmStop( VM_MACHINE * core )
{
	u16 music = VMGetU16(core);	//"���g�p"
	//Snd_BgmStop( music, 0 );
	Snd_BgmStop( Snd_NowBgmNoGet(), 0 );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ���݂̃}�b�v��BGM���Đ�
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBgmNowMapPlay( VM_MACHINE * core )
{
	int zone_id = core->fsys->location->zone_id;
	//u16 music	= Snd_PcBgmNoGet( core->fsys, Snd_FieldBgmNoGet(core->fsys,zone_id) );
	u16 music	= Snd_FieldBgmNoGetNonBasicBank( core->fsys,zone_id );
	Snd_BgmPlay( music );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �}�b�v�������BGM�w�肪�Z�b�g�����
 * ���]��BGM�̐���ȂǂɎg�p
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBgmSpecialSet( VM_MACHINE * core )
{
	Snd_FieldBgmSetSpecial( core->fsys, VMGetU16(core) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * BGM�t�F�[�h�A�E�g�҂�
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	���1
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBgmFadeOut( VM_MACHINE * core )
{
	u16 vol		= VMGetU16(core);
	u16 frame	= VMGetU16(core);
	Snd_BgmFadeOut( vol, frame );
	VM_SetWait( core, EvWaitBgmFade );
	return 1;
}

//return 1 = �I��
static BOOL EvWaitBgmFade( VM_MACHINE * core )
{
	if( Snd_FadeCheck() == 0 ){
		return TRUE;
	}
	return FALSE;
};

//--------------------------------------------------------------------------------------------
/**
 * BGM�t�F�[�h�C���҂�(�t�F�[�h�A�E�g�������̂��ĊJ����)
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBgmFadeIn( VM_MACHINE * core )
{
	u16 frame = VMGetU16(core);
	Snd_BgmFadeIn( BGM_VOL_MAX, frame, BGM_FADEIN_START_VOL_MIN );
	VM_SetWait( core, EvWaitBgmFade );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �V�[�P���X���ꎞ��~�܂��͍ĊJ
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBgmPlayerPause( VM_MACHINE * core )
{
	u8 player = VMGetU8(core);
	BOOL flag = VMGetU8(core);

	Snd_PlayerPause( player, flag );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ���oBGM�Đ�(���C�o���A�T�|�[�g�A��Ă�)
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPlayerFieldDemoBgmPlay( VM_MACHINE * core )
{
	Snd_PlayerFieldDemoBgmPlay( SND_SCENE_FIELD, VMGetU16(core) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���hBGM���Œ�ɂ���t���O�Z�b�g(�Z�[�u���Ȃ�)
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdCtrlBgmFlagSet( VM_MACHINE * core )
{
	Snd_CtrlBgmFlagSet( VMGetU8(core) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �r�d��炷
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSePlay( VM_MACHINE * core )
{
	Snd_SePlay( VMGetWorkValue(core) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �r�d���~�߂�
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSeStop( VM_MACHINE * core )
{
	Snd_SeStopBySeqNo( VMGetWorkValue(core), 0 );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * SE�I���҂�
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	���1
 *
 * @li		�J�Ȃǂ̃��[�v���ŁA�������[�v�ɂȂ��Ă��܂��̂ŁASE�i���o�[�w�肵�āA������`�F�b�N�I
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSeWait(VM_MACHINE * core)
{
	//���z�}�V���̔ėp���W�X�^��BGM�i���o�[���i�[
	core->reg[0] = VMGetWorkValue(core);

	VM_SetWait( core, EvWaitSe );
	return 1;
}

//return 1 = �I��
static BOOL EvWaitSe(VM_MACHINE * core)
{
	//if( Snd_SePlayCheckAll() == 0 ){
	if( Snd_SePlayCheck(core->reg[0]) == 0 ){
		return TRUE;
	}

	return FALSE;
};


//--------------------------------------------------------------------------------------------
/**
 * ������炷
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdVoicePlay( VM_MACHINE * core )
{
	u16 no, ptn;
	no	= VMGetWorkValue(core);
	ptn = VMGetWorkValue(core);

	//�؃��b�v�Đ��e�X�g
	//no = MONSNO_PERAPPU;

	//�p�^�[�����w��ł���֐��ɒu��������\��
	Snd_PMVoicePlay( no );
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * �����I���҂�
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	���1
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdVoicePlayWait( VM_MACHINE * core )
{
	VM_SetWait( core, EvWaitVoicePlay );
	return 1;
}

//return 1 = �I��
static BOOL EvWaitVoicePlay(VM_MACHINE * core)
{
	if( Snd_PMVoicePlayCheck() == 0 ){
		return 1;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ME�Đ�
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdMePlay(VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	Snd_MePlay( VMGetU16(core) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ME�I���҂�
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdMeWait(VM_MACHINE * core )
{
	VM_SetWait( core, EvWaitMe );
	return 1;
}

//return 1 = �I��
static BOOL EvWaitMe( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;

	//�I���҂��̂�
	//if( Snd_MePlayCheck() == 0 ){
	
	//�I���҂��{�E�F�C�g���[�N�҂�
	if( Snd_MePlayCheckBgmPlay() == 0 ){ 
		return TRUE;
	}

	return FALSE;
};

//--------------------------------------------------------------------------------------------
/**
 * �y���b�v�f�[�^�����邩�`�F�b�N
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPerapDataCheck( VM_MACHINE * core )
{
	u16* ret_wk	= VMGetWork( core );

	if( Snd_PerapVoiceCheck(SaveData_GetPerapVoice(core->fsys->savedata)) == TRUE ){
		*ret_wk = TRUE;
		return 0;
	}

	*ret_wk = FALSE;
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �y���b�v�^���J�n
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPerapRecStart( VM_MACHINE * core )
{
	u16* ret_wk			= VMGetWork( core );

	if( Snd_PerapVoiceRecStart() == MIC_RESULT_SUCCESS ){
		*ret_wk = TRUE;	//����
		return 0;
	}

	*ret_wk = FALSE;	//���s
	return 0;

}

//--------------------------------------------------------------------------------------------
/**
 * �y���b�v�^����~
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPerapRecStop( VM_MACHINE * core )
{
	Snd_PerapVoiceRecStop();
	return 1;

}

//--------------------------------------------------------------------------------------------
/**
 * �y���b�v�^�������f�[�^���Z�[�u
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPerapSave( VM_MACHINE * core )
{
	Snd_PerapVoiceDataSave( SaveData_GetPerapVoice(core->fsys->savedata) );
	return 1;

}

//--------------------------------------------------------------------------------------------
/**
 * �N���C�}�b�N�X���o�T�E���h�f�[�^�ǉ����[�h
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSndClimaxDataLoad( VM_MACHINE * core )
{
	Snd_DataSetByScene( SND_SCENE_SUB_CLIMAX, 0, 0 );	//�T�E���h�f�[�^���[�h(BGM���p��)
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �����{�����[���Z�b�g
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSndInitialVolSet( VM_MACHINE * core )
{
	u16 no	= VMGetWorkValue(core);
	u16 vol = VMGetWorkValue(core);

	Snd_PlayerSetInitialVolumeBySeqNo( no, vol );
	return 0;
}


