//============================================================================================
/**
 * @file	misc.c
 * @brief	�����ރZ�[�u�f�[�^�̃A�N�Z�X
 * @author	tamada	GAME FREAK Inc.
 * @date	2006.01.26
 *
 * ���ނ���Ă��Ȃ��Z�[�u�f�[�^�͂Ƃ肠���������ɒǉ������B
 * �A�v���P�[�V�������x���A�Z�[�u�f�[�^�A�N�Z�X�֐����x�������
 * ����MISC�\���̂����o�����Ƃ͂ł��Ȃ��B
 * MISC�\���̂̓����o�Ɏ��\���̂ւ̃A�N�Z�X��񋟂��邾����
 * �C���^�[�t�F�C�X�Ƃ��ċ@�\���Ă���B
 *
 * �Z�[�u�f�[�^�Ƃ��Ă̐�����������ƒ�`�ł���悤�ɂȂ������_�ŁA
 * �����̃Z�[�u�\���̂͂�����ƕʃ\�[�X�ɐ؂蕪�����邱�ƂɂȂ�B
 *
 * 2006.06.02
 * ���Ԑ؂�ŕ��ނ��킩�����̂͂����ɒǉ����邱�Ƃɂ��܂����B
 * ���O�B
 */
//============================================================================================

#include "common.h"
#include "gflib/system.h"

#include "system/gamedata.h"

#include "savedata/savedata.h"

#include "savedata/misc.h"
#include "misc_local.h"

#include "seedbed_local.h"
#include "savedata/seedbed.h"
#include "gimmickwork_local.h"
#include "savedata/gimmickwork.h"


#include "gflib/strbuf_family.h"
#include "system/pm_str.h"

//============================================================================================
//============================================================================================

//---------------------------------------------------------------------------
/**
 * @brief	MISC�\���̂̒�`
 *
 * ���L�̂悤�ȃZ�[�u�f�[�^�u���b�N�́AMISC�̃����o�[�Ƃ��Ċm�ۂ���B
 * -�ǂ��ɕ��ނ���ׂ����A���f�ɖ������́B���͕��ނ�ۗ����Ă�����������
 * -�K�͂��������A���̂��߂ɃZ�[�u�u���b�N���m�ۂ���̂����������Ȃ�����
 */
//---------------------------------------------------------------------------
struct _MISC {
	SEEDBED seedbed[SEEDBED_MAX];
	GIMMICKWORK gimmick;
	STRCODE rivalname[PERSON_NAME_SIZE + EOM_SIZE];
	STRCODE monument_name[MONUMENT_NAME_SIZE + EOM_SIZE];
};

#ifdef	PM_DEBUG
#if	PM_VERSION == VERSION_DIAMOND
static const STRCODE RivalName[] = {PA_, bou_,RU_, EOM_ };
#elif	PM_VERSION == VERSION_PEARL
static const STRCODE RivalName[] = {DA_, I_, YA_, EOM_ };
#endif
#endif
//============================================================================================
//============================================================================================

//---------------------------------------------------------------------------
/**
 * @brief	MISC�\���̂̃T�C�Y�擾
 * @return	int		MISC�\���̂̃T�C�Y
 */
//---------------------------------------------------------------------------
int MISC_GetWorkSize(void)
{
	return sizeof(MISC);
}

//---------------------------------------------------------------------------
/**
 */
//---------------------------------------------------------------------------
void MISC_Copy(const MISC * from, MISC * to)
{
	MI_CpuCopy8(from ,to, sizeof(MISC));
}

//============================================================================================
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	�F�X�Z�[�u�f�[�^�ێ����[�N�̏�����
 * @param	misc	�F�X�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
void MISC_Init(MISC * misc)
{
	MI_CpuClearFast(misc, sizeof(MISC));
	/* �ȉ��Ɍʕ����̏��������������� */
	SEEDBED_Init(misc->seedbed);
	GIMMICKWORK_Init(&misc->gimmick);
	MI_CpuFill16(misc->rivalname, EOM_, PERSON_NAME_SIZE + EOM_SIZE);
	MI_CpuFill16(misc->monument_name, EOM_, MONUMENT_NAME_SIZE + EOM_SIZE);
#ifdef	PM_DEBUG
	PM_strcpy(misc->rivalname, RivalName);
#endif
}

//============================================================================================
//
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	MISC�Z�[�u�f�[�^�̎擾
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	MISC�\���̂ւ̃|�C���^
 */
//---------------------------------------------------------------------------
MISC * SaveData_GetMisc(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_MISC);
}

//---------------------------------------------------------------------------
/**
 * @brief	MISC�Z�[�u�f�[�^�̎擾
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	MISC�\���̂ւ̃|�C���^
 */
//---------------------------------------------------------------------------
const MISC * SaveData_GetMiscReadOnly(const SAVEDATA * sv)
{
	return SaveData_GetReadOnlyData(sv, GMDATA_ID_MISC);
}

//---------------------------------------------------------------------------
/**
 * @brief	���̂ݏ�ԃf�[�^�ւ̃|�C���^�擾
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	CONFIG		�ݒ���ێ����[�N�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
SEEDBED * SaveData_GetSeedBed(SAVEDATA * sv)
{
	MISC * misc;
	misc = SaveData_Get(sv, GMDATA_ID_MISC);
	return misc->seedbed;
}

//---------------------------------------------------------------------------
/**
 * @brief	�}�b�v�ŗL�̎d�|�����[�N�ւ̃|�C���^�擾
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	GIMMICKWORK	�d�|���p���[�N�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
GIMMICKWORK * SaveData_GetGimmickWork(SAVEDATA * sv)
{
	MISC * misc;
	misc = SaveData_Get(sv, GMDATA_ID_MISC);
	return &misc->gimmick;
}

//============================================================================================
//============================================================================================
//---------------------------------------------------------------------------
/**
 */
//---------------------------------------------------------------------------
const STRCODE * MISC_GetRivalName(const MISC * misc)
{
	return misc->rivalname;
}

//---------------------------------------------------------------------------
/**
 */
//---------------------------------------------------------------------------
void MISC_SetRivalName(MISC * misc, STRBUF * str)
{
	STRBUF_GetStringCode( str, misc->rivalname, PERSON_NAME_SIZE + EOM_SIZE );
}

//---------------------------------------------------------------------------
/**
 */
//---------------------------------------------------------------------------
const STRCODE * MISC_GetMonumentName(const MISC * misc)
{
	return misc->monument_name;
}

//---------------------------------------------------------------------------
/**
 */
//---------------------------------------------------------------------------
void MISC_SetMonumentName(MISC * misc, STRBUF * str)
{
	STRBUF_GetStringCode( str, misc->monument_name, MONUMENT_NAME_SIZE + EOM_SIZE );
}

