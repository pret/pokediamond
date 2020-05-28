//============================================================================================
/**
 * @file	mystatus.c
 * @brief	������ԃf�[�^�A�N�Z�X�p�\�[�X
 * @author	tamada GAME FREAK inc.
 * @date	2005.10.27
 */
//============================================================================================

#include "savedata/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���

#include "common.h"

#include "system/gamedata.h"
#include "savedata/savedata.h"

#include "mystatus_local.h"

#include "savedata/mystatus.h"

#include "system/pm_str.h"

#include "gflib/strbuf_family.h"

#define TR_LOW_MASK		(0xffff)

//============================================================================================
//============================================================================================

enum {
	MY_GOLD_MAX	= 999999,
};



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
int MyStatus_GetWorkSize(void)
{
	return sizeof(MYSTATUS);
}

//----------------------------------------------------------
/**
 * @brief	������ԕێ����[�N�̊m��
 * @param	heapID		�������m�ۂ������Ȃ��q�[�v�w��
 * @return	MYSTATUS	�擾�������[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
MYSTATUS * MyStatus_AllocWork(u32 heapID)
{
	MYSTATUS * my;
	my = sys_AllocMemory(heapID, sizeof(MYSTATUS));
	MyStatus_Init(my);


	return my;
}

//----------------------------------------------------------
/**
 * @brief	MYSTATUS�̃R�s�[
 * @param	from	�R�s�[��MYSTATUS�ւ̃|�C���^
 * @param	to		�R�s�[��MYSTATUS�ւ̃|�C���^
 */
//----------------------------------------------------------
void MyStatus_Copy(const MYSTATUS * from, MYSTATUS * to)
{
	MI_CpuCopy8(from, to, sizeof(MYSTATUS));
}

//============================================================================================
//
//	MYSTATUS����̂��߂̊֐�
//
//============================================================================================

//----------------------------------------------------------
/**
 * @brief		������ԃf�[�^�̏�����
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
void MyStatus_Init(MYSTATUS * my)
{
	memset(my, 0, sizeof(MYSTATUS));

	// �J�Z�b�g�̌���R�[�h�𖄂ߍ���
	my->region_code = PM_LANG;		

#ifdef PM_DEBUG

	// �f�o�b�O�ő����̐l�ɂȂ肷�܂���B
	if(sys.cont&PAD_BUTTON_L){
		MyStatus_SetRegionCode(my, LANG_JAPAN );
	}else if(sys.cont&PAD_BUTTON_R){
		MyStatus_SetRegionCode(my, LANG_ENGLISH );
	}else if(sys.cont&PAD_BUTTON_SELECT){
		MyStatus_SetRegionCode(my, LANG_FRANCE	 );
	}else if(sys.cont&PAD_BUTTON_START){
		MyStatus_SetRegionCode(my, LANG_ITALY	 );
	}else if(sys.cont&PAD_KEY_UP){
		MyStatus_SetRegionCode(my, LANG_GERMANY );
	}else if(sys.cont&PAD_KEY_LEFT){
		MyStatus_SetRegionCode(my, LANG_SPAIN	 );
	}

#endif
}

//----------------------------------------------------------
/**
 * @brief	�����̖��O�Z�b�g
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @param	name	���O������ւ̃|�C���^
 */
//----------------------------------------------------------
void MyStatus_SetMyName(MYSTATUS * my, const STRCODE * name)
{
	int len;
	len = PM_strlen(name);
	GF_ASSERT(len < PERSON_NAME_SIZE + EOM_SIZE)
	PM_strcpy(my->name, name);
}

//----------------------------------------------------------
/**
 * @brief	�����̖��O�Z�b�g(STRBUF�Łj
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @param	str		���O�ێ��o�b�t�@�ւ̃|�C���^
 */
//----------------------------------------------------------
void MyStatus_SetMyNameFromString(MYSTATUS * my, const STRBUF * str)
{
	STRBUF_GetStringCode( str, my->name, PERSON_NAME_SIZE + EOM_SIZE );
}

//----------------------------------------------------------
/**
 * @brief	�����̖��O�擾
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @return	STRCODE		���O������ւ̃|�C���^
 */
//----------------------------------------------------------
const STRCODE * MyStatus_GetMyName(const MYSTATUS * my)
{
	return my->name;
}

//----------------------------------------------------------
/**
 * @brief	�����̖��O�擾�iSTRBUF�ɃR�s�[�j
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @param	buf		�R�s�[������STRBUF�ւ̃|�C���^�i�e���œ��e�͊m�ۂ��Ă��鎖���O��j
 * @return	none
 */
//----------------------------------------------------------
void MyStatus_CopyNameString( const MYSTATUS * my, STRBUF *buf )
{
	STRBUF_SetStringCode( buf, my->name );
}

//----------------------------------------------------------
/**
 * @brief	�����̖��O�擾�iSTRBUF�𐶐��j
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @param	heapID	STRBUF�𐶐�����q�[�v��ID
 * @return	STRBUF	���O���i�[����STRBUF�ւ̃|�C���^
 */
//----------------------------------------------------------
STRBUF * MyStatus_CreateNameString(const MYSTATUS * my, int heapID)
{
	STRBUF * tmpBuf = STRBUF_Create(PERSON_NAME_SIZE + EOM_SIZE, heapID);
//	STRBUF_SetStringCode( tmpBuf, my->name );
	MyStatus_CopyNameString( my, tmpBuf );
	return tmpBuf;
}


//----------------------------------------------------------
/**
 * @brief	�����̂h�c�Z�b�g
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @param	id		�h�c�w��	
 */
//----------------------------------------------------------
void MyStatus_SetID(MYSTATUS * my, u32 id)
{
	my->id = id;
}
//----------------------------------------------------------
/**
 * @brief	�����̂h�c�擾
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @return	int		�����̂h�c	
 */
//----------------------------------------------------------
u32 MyStatus_GetID(const MYSTATUS * my)
{
	return my->id;
}

//----------------------------------------------------------
/**
 * @brief	�����̂h�c�擾(���ʂQ�o�C�g)
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @return	int		�����̂h�c	
 */
//----------------------------------------------------------
u16 MyStatus_GetID_Low(const MYSTATUS * my)
{
	return (u16)(my->id&TR_LOW_MASK);
}

//----------------------------------------------------------
/**
 * @brief	�����̐��ʃZ�b�g
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @param	sex		�����̐���
 */
//----------------------------------------------------------
void MyStatus_SetMySex(MYSTATUS * my, int sex)
{
	my->sex = sex;
}
//----------------------------------------------------------
/**
 * @brief	�����̐��ʎ擾
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @return	sex		�����̐���
 */
//----------------------------------------------------------
u32 MyStatus_GetMySex(const MYSTATUS * my)
{
	return my->sex;
}

//----------------------------------------------------------
/**
 * @brief	�o�b�W�ێ���Ԃ̎擾
 * @param	my			������ԕێ����[�N�ւ̃|�C���^
 * @param	badge_id	�o�b�W�̎w��
 * @return	BOOL	�o�b�W�������Ă��邩�ǂ���
 */
//----------------------------------------------------------
BOOL MyStatus_GetBadgeFlag(const MYSTATUS * my, int badge_id)
{
	if (my->badge & (1 << badge_id)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//----------------------------------------------------------
/**
 * @brief	�o�b�W�擾�̃Z�b�g
 * @param	my			������ԕێ����[�N�ւ̃|�C���^
 * @param	badge_id	�o�b�W�̎w��
 */
//----------------------------------------------------------
void MyStatus_SetBadgeFlag(MYSTATUS * my, int badge_id)
{
	my->badge |= (1 << badge_id);
}

//----------------------------------------------------------
/**
 * @brief	�����Ă���o�b�W�̐����擾����
 * @param	my			������ԕێ����[�N�ւ̃|�C���^
 * @return	int		�����Ă���o�b�W�̐��i�O�`�W�j
 */
//----------------------------------------------------------
int MyStatus_GetBadgeCount(const MYSTATUS * my)
{
	int count = 0;
	u32 badge;
	
	for (badge = my->badge; badge != 0; badge >>= 1) {
		if (badge & 1) {
			count ++;
		}
	}
	return count;
}
//----------------------------------------------------------
/**
 * @brief	�����Ă�����z���擾����
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @return	u32		�����Ă�����z
 */
//----------------------------------------------------------
u32 MyStatus_GetGold(const MYSTATUS * my)
{
	return my->gold;
}

//----------------------------------------------------------
/**
 * @brief
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @param	gold	�Z�b�g������z
 * @return	u32		���݂̎莝�����z
 */
//----------------------------------------------------------
u32 MyStatus_SetGold(MYSTATUS * my, u32 gold)
{
	if (gold > MY_GOLD_MAX) {
		gold = MY_GOLD_MAX;
	}
	my->gold = gold;
	return my->gold;
}

//==============================================================================
/**
 * $brief   �������g���[�i�[�Ƃ��Č����鎞�̔ԍ���Ԃ��i���j�I�����[���p�j
 *
 * @param   my		������ԕێ����[�N�ւ̃|�C���^
 *
 * @retval  u8		�g���[�i�[�Ƃ��Ă̎����̌�����
 */
//==============================================================================
u8 MyStatus_GetTrainerView( const MYSTATUS *my )
{
	return my->trainer_view;
}

//==============================================================================
/**
 * $brief   �������g���[�i�[�Ƃ��Č����鎞�̔ԍ����Z�b�g�i���j�I�����[���p�j
 *
 * @param   my		������ԕێ����[�N�ւ̃|�C���^
 * @param   view	�g���[�i�[�����ڔԍ�
 *
 * @retval  none
 */
//==============================================================================
void MyStatus_SetTrainerView( MYSTATUS *my, u8 view )
{
	my->trainer_view = view;
}

//----------------------------------------------------------
/**
 * @brief
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @param	add		��������z
 * @return	u32		���݂̎莝�����z
 */
//----------------------------------------------------------
u32 Mystatus_AddGold(MYSTATUS * my, u32 add)
{
	if (add > MY_GOLD_MAX) {
		my->gold = MY_GOLD_MAX;
	} else {
		my->gold += add;
	}
	if (my->gold > MY_GOLD_MAX) {
		my->gold = MY_GOLD_MAX;
	}
	return my->gold;
}

//----------------------------------------------------------
/**
 * @brief
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @param	sub		�����o�����z
 * @return	u32		���݂̎莝�����z
 */
//----------------------------------------------------------
u32 Mystatus_SubGold(MYSTATUS * my, u32 sub)
{
	if (my->gold < sub) {
		my->gold = 0;
	} else {
		my->gold -= sub;
	}
	return my->gold;
}



//==============================================================================
/**
 * $brief   �q�n�l�o�[�W�����R�[�h��Ԃ�
 *
 * @param   my		������ԕێ����[�N�ւ̃|�C���^
 *
 * @retval  u8		0:�_�C�� 1:�p�[��
 */
//==============================================================================
u8  MyStatus_GetRomCode( const MYSTATUS * my )
{
	return my->rom_code;
}

//==============================================================================
/**
 * $brief   �q�n�l�o�[�W�����R�[�h��ݒ肷��
 *
 * @param   my		������ԕێ����[�N�ւ̃|�C���^
 *
 * @param  rom_code		0:�_�C�� 1:�p�[��
 */
//==============================================================================
void  MyStatus_SetRomCode( MYSTATUS * my, u8 rom_code )
{
	my->rom_code = rom_code;
}

//==============================================================================
/**
 * $brief   ���[�W�����R�[�h��Ԃ�
 *
 * @param   my		������ԕێ����[�N�ւ̃|�C���^
 *
 * @retval  u8		���[�W�����R�[�h
 */
//==============================================================================
u8  MyStatus_GetRegionCode( const MYSTATUS * my )
{
	return my->region_code;
}

//==============================================================================
/**
 * $brief   ���[�W�����R�[�h��ݒ肷��
 *
 * @param   my		������ԕێ����[�N�ւ̃|�C���^
 *
 * @param  region_code		
 */
//==============================================================================
void  MyStatus_SetRegionCode( MYSTATUS * my, u8 region_code )
{
	my->region_code = region_code;
}

//==============================================================================
/**
 * @brief   DP�N���A���Ă��邩�t���O�̃Z�b�g
 *
 * @param   my		
 * @param   flag	0:���ĂȂ�	1:�N���A���Ă���
 *
 * @retval  none		
 */
//==============================================================================
void MyStatus_SetDpClearFlag( MYSTATUS * my )
{
	my->dp_clear = 1;
}

int MyStatus_GetDpClearFlag( MYSTATUS * my )
{
	return my->dp_clear;
}

//==============================================================================
/**
 * @brief   DP�S���}�ӂ����Ă���t���O�̃Z�b�g
 *
 * @param   my		
 * @param   flag	0:�V���I�E�}��	1:�S���}��
 *
 * @retval  none		
 */
//==============================================================================
void MyStatus_SetDpZenkokuFlag( MYSTATUS * my )
{
	my->dp_zenkoku = 1;
}

int MyStatus_GetDpZenkokuFlag( MYSTATUS * my )
{
	return my->dp_zenkoku;
}





//----------------------------------------------------------
/**
 * @brief	myStatus���m���������̂��ǂ����𒲂ׂ�
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @param	target	����̎�����ԕێ����[�N�ւ̃|�C���^
 * @return	��v������TRUE
 */
//----------------------------------------------------------
BOOL MyStatus_Compare(const MYSTATUS * my, const MYSTATUS * target)
{
    if(0 == PM_strncmp(my->name, target->name, PERSON_NAME_SIZE)){
        if(my->id == target->id){
            return TRUE;
        }
    }
    return FALSE;
}



//============================================================================================
//	�f�o�b�O�p
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�f�o�b�O�p�F������ԃZ�b�g
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @param	name	���O������ւ̃|�C���^
 * @param	sex		���ʎw��
 */
//----------------------------------------------------------
void Debug_MyStatus_Make(MYSTATUS * mystatus, const STRCODE * name, int sex)
{
	MyStatus_SetMyName(mystatus, name);
	MyStatus_SetMySex(mystatus, sex);
}

// �O���Q�ƃC���f�b�N�X����鎞�̂ݗL��(�Q�[�����͖���)
#ifdef CREATE_INDEX
void *Index_Get_Mystatus_Name_Offset(MYSTATUS *my){ return &my->name; }
void *Index_Get_Mystatus_Id_Offset(MYSTATUS *my){ return &my->id; }
void *Index_Get_Mystatus_Sex_Offset(MYSTATUS *my){ return &my->sex; }
#endif
