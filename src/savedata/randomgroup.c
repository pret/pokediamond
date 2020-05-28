//============================================================================================
/**
 * @file	randomgroup.c
 * @brief	�����̎�O���[�v�\�[�X
 * @author	mori GAME FREAK inc.
 * @date	2006.03.22
 */
//============================================================================================

#include "savedata/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���

#include "common.h"

#include "system/gamedata.h"
#include "savedata/savedata.h"


#include "savedata/randomgroup.h"
#include "randomgroup_local.h"

#include "system/pm_str.h"

#include "gflib/strbuf_family.h"

//============================================================================================
//============================================================================================


RANDOM_GROUP * DebugRandomGroupPtr;


//============================================================================================
//
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	������ԕێ����[�N�̃T�C�Y�擾
 * @return	int		�T�C�Y�i�o�C�g�P�ʁj
 */
//----------------------------------------------------------
int RandomGroup_GetWorkSize(void)
{
	return sizeof(RANDOM_GROUP);
}

//==============================================================================
/**
 * $brief   �����_���O���[�v���ł̃R�s�[�i�f�[�^�S�̂̃R�s�[�ł͂Ȃ��j
 *
 * @param   randomgroup		
 * @param   from		
 * @param   to		
 *
 * @retval  none		
 */
//==============================================================================
void RandomGroup_Copy( RANDOM_GROUP *randomgroup, int from, int to )
{
	randomgroup->group[to] = randomgroup->group[from];
}


//==============================================================================
/**
 * $brief   �����_���O���[�v������
 *
 * @param   randomgroup		
 *
 * @retval  none		
 */
//==============================================================================
void RandomGroup_Init(RANDOM_GROUP * randomgroup )
{
	int i;
	
	MI_CpuClearFast(randomgroup, sizeof(RANDOM_GROUP));

	for(i=0;i<RANDOMGROUP_MAX;i++){
		randomgroup->group[i].group_name[0] = EOM_;
		randomgroup->group[i].name[0]       = EOM_;
	}

	DebugRandomGroupPtr = randomgroup;
	
}

//==============================================================================
/**
 * @brief	�����̎�X�V����
 *
 * @param	randomgroup
 * @param	days			�����o��
 *
 * �����o�߂̉񐔂��������_���̃^�l���X�V����B
 */
//==============================================================================
void RandomGroup_Update(RANDOM_GROUP * randomgroup, u32 days)
{
	u32 no, times;
	for (no = 0; no < RANDOMGROUP_MAX; no++) {
		for (times = 0; times < days; times++) {
			//RandomGroup_SetRandom(randomgroup, no);
			randomgroup->group[no].random = gf_fix_rand( randomgroup->group[no].random );
		}
	}
}

//==============================================================================
/**
 * $brief   �����̎�擾(�قƂ�ǌĂ΂Ȃ����낤�j
 *
 * @param   randomgroup		
 * @param   no		
 *
 * @retval  u32		
 */
//==============================================================================
u32  RandomGroup_GetRandomSeed( RANDOM_GROUP* randomgroup, int no )
{
	return randomgroup->group[no].seed;
}

//==============================================================================
/**
 * $brief   �����̎�̐ݒ�i�����O���[�v���쐬�������Ɉ�񂾂��Ăԁj
 *
 * @param   randomgroup		�����O���[�v�\����
 * @param   no				���Ԗڂ�
 * @param   seed			�����l
 *
 * @retval  u32		
 */
//==============================================================================
void  RandomGroup_SetRandomSeed( RANDOM_GROUP* randomgroup, int no, u32 seed )
{
	// �����̎���i�[�i�Q�x�ƍX�V���Ȃ��j
	randomgroup->group[no].seed = seed;

	// �������i�[���Ă���
	randomgroup->group[no].random = gf_fix_rand( seed );

}

//==============================================================================
/**
 * $brief   ������ς�闐���l���擾
 *
 * @param   randomgroup		
 * @param   no				
 *
 * @retval  u32		
 */
//==============================================================================
u32  RandomGroup_GetRandom( RANDOM_GROUP* randomgroup, int no )
{
	return randomgroup->group[no].random;
}

//==============================================================================
/**
 * @brief   ������ς�闐���l���擾�i�f�t�H���g�j
 *
 * @param	randomgroup
 *
 * @return	u32
 *
 * ��{�I�ɃQ�[�����ŎQ�Ƃ���u�����̃^�l�v�͂��̊֐��ɂ���Ď擾����B
 */
//==============================================================================
u32  RandomGroup_GetDefaultRandom( RANDOM_GROUP* randomgroup )
{
	return randomgroup->group[RANDOMGROUP_MYUSE].random;
}

//==============================================================================
/**
 * $brief   �����X�V(�P���P��X�V����j
 *          ���ݕێ����Ă��闐���̒l���V���������̎�Ȃ̂ŊO����p�����[�^�͖��Ȃ�
 *
 * @param   randomgroup		
 * @param   no				
 *
 * @retval  none			
 */
//==============================================================================
void RandomGroup_SetRandom( RANDOM_GROUP* randomgroup, int no )
{
	u32 temp = randomgroup->group[no].random;
	randomgroup->group[no].random = gf_fix_rand( randomgroup->group[no].random );

	OS_TPrintf("�����X�V no=%d from=%08x, to=%08x\n",no,temp,randomgroup->group[no].random);
}


//==============================================================================
/**
 * $brief   �O���[�v���E�������̓��[�_�[���̃|�C���^�擾
 *
 * @param   randomgroup		
 * @param   no		
 * @param   type		
 *
 * @retval  const STRCODE *		
 */
//==============================================================================
const STRCODE *RandomGroup_GetNamePtr( const RANDOM_GROUP *randomgroup, int no, int type )
{
	if(type==RANDOMGROUP_NAME_GROUP){
		return randomgroup->group[no].group_name;
	}
	return randomgroup->group[no].name;

}

//==============================================================================
/**
 * $brief   �O���[�v���E�܂��̓��[�_�[���̃Z�b�g
 *
 * @param   randomgroup		
 * @param   no		
 * @param   type		
 * @param   str		
 *
 * @retval  none		
 */
//==============================================================================
void  RandomGroup_SetName( RANDOM_GROUP *randomgroup, int no, int type, STRBUF *str )
{
	STRCODE *name;

	if(type==RANDOMGROUP_NAME_GROUP){
		name = randomgroup->group[no].group_name;
		STRBUF_GetStringCode( str, name, GROUP_NAME_SIZE + EOM_SIZE );
	}else{
		name = randomgroup->group[no].name;
		STRBUF_GetStringCode( str, name, PERSON_NAME_SIZE + EOM_SIZE );
	}
	
}

//==============================================================================
/**
 * @brief	���ʂ��Z�b�g����
 *
 * @param   randomgroup		
 * @param   no		
 */
//==============================================================================
void RandomGroup_SetSex( RANDOM_GROUP *randomgroup, int no, int sex)
{
	randomgroup->group[no].sex = sex;
}

//==============================================================================
/**
 * @brief	���ʂ��擾����
 *
 * @param   randomgroup		
 * @param   no		
 * @return	int		���ʃR�[�h
 */
//==============================================================================
int RandomGroup_GetSex( const RANDOM_GROUP *randomgroup, int no)
{
	return randomgroup->group[no].sex;
}

//==============================================================================
/**
 * @brief	���[�W�����R�[�h���擾����
 *
 * @param   randomgroup		
 * @param   no		
 * @return	int		���[�W�����R�[�h
 */
//==============================================================================
int RandomGroup_GetRegionCode( const RANDOM_GROUP *randomgroup, int no)
{
	return randomgroup->group[no].region_code;
}

//==============================================================================
/**
 * @brief	���[�W�����R�[�h���Z�b�g����
 *
 * @param   randomgroup		
 * @param   no		
 */
//==============================================================================
void RandomGroup_SetRegionCode( RANDOM_GROUP *randomgroup, int no, int region_code )
{
	randomgroup->group[no].region_code = region_code;
}

//==============================================================================
/**
 * $brief   �����̎�O���[�v�̃|�C���^��Ԃ�
 *
 * @param   sv		
 *
 * @retval  RANDOM_GROUP *		
 */
//==============================================================================
RANDOM_GROUP *SaveData_GetRandomGroup(SAVEDATA * sv)
{
	return (RANDOM_GROUP *)SaveData_Get(sv, GMDATA_ID_RANDOMGROUP);
}


//==============================================================================
/**
 * @brief	�O���[�v�f�[�^�̑��݃`�F�b�N
 *
 * @param   randomgroup		
 * @param   no				�`�F�b�N����f�[�^��ID
 * @retval	TRUE			���݂���
 * @retval	FALSE			���݂��Ȃ�
 */
//==============================================================================
BOOL RandomGroup_ExistCheck(const RANDOM_GROUP * rg, int no)
{
	const RANDOM_SEED * rs = &rg->group[no];
	return !(RandomGroup_IsNullData(rs));
}

//==============================================================================
/**
 * @brief	�O���[�v�f�[�^�������̓o�^���Ă���f�[�^���ǂ����̃`�F�b�N
 *
 * @param   randomgroup		
 * @param   no				��r����f�[�^��ID
 * @retval	TRUE			��v����
 * @retval	FALSE			��v���Ȃ�
 */
//==============================================================================
BOOL RandomGroup_EntryCheck(const RANDOM_GROUP * rg, int no)
{
	const RANDOM_SEED * rs1, * rs2;
	rs1 = &rg->group[RANDOMGROUP_MYUSE];
	rs2 = &rg->group[no];
	return RandomGroup_Compare(rs1, rs2);
}

//==============================================================================
/**
 * @brief	�w�肵���O���[�v�������݂��邩�ǂ����̃`�F�b�N
 * @param	rg
 * @param	group_name
 * @return	BOOL	TRUE�̂Ƃ��A��v���閼�O������
 */
//==============================================================================
BOOL RandomGroup_SameGroupNameCheck(const RANDOM_GROUP * rg, const STRCODE * group_name)
{
	int index;
	const RANDOM_SEED * rs;

	if (*group_name == EOM_) {
		//���O�����݂��Ȃ�
		return FALSE;
	}
	for (index = 0; index < RANDOMGROUP_MAX; index ++ ) {
		rs = &rg->group[index];
		if (!PM_strncmp(group_name, rs->group_name, GROUP_NAME_SIZE + EOM_SIZE)) {
			return TRUE;
		}
	}
	return FALSE;
}

//============================================================================================
//
//		�����_���O���[�v�����ł̂ݎg�p����֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�f�[�^�����݂��邩�ǂ����̃`�F�b�N
 * @param	rs
 * @retval	TRUE	���݂��Ȃ�
 * @retval	FALSE	���݂���
 */
//----------------------------------------------------------
BOOL RandomGroup_IsNullData(const RANDOM_SEED * rs)
{
	if (rs->group_name[0] == EOM_) {
		return TRUE;
	}
	if (rs->name[0] == EOM_) {
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	�����_���̃^�l���������ǂ������`�F�b�N
 * @param	s1			�����_���̃^�l���̂P
 * @param	s2			�����_���̃^�l���̂Q
 * @retval	TRUE		��v����
 * @retval	FALSE		�Ⴄ�f�[�^������
 */
//----------------------------------------------------------
BOOL RandomGroup_Compare(const RANDOM_SEED * s1, const RANDOM_SEED * s2)
{
	int i;
	if (PM_strncmp(s1->name, s2->name, PERSON_NAME_SIZE + EOM_SIZE)) {
		return FALSE;
	}
	if (PM_strncmp(s1->group_name, s2->group_name, GROUP_NAME_SIZE + EOM_SIZE)) {
		return FALSE;
	}
	if (s1->sex != s2->sex) {
		return FALSE;
	}
	if (s1->region_code != s2->region_code) {
		return FALSE;
	}
	if (s1->seed != s2->seed) {
		return FALSE;
	}
	/*
	 * if (s1->random != s2->random) {
	 *		�����͂ǂ����悤�c
	 * }
	 */
	return TRUE;
}

