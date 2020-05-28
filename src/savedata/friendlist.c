//============================================================================================
/**
 * @file	friendlist.c
 * @brief	������ԃf�[�^�A�N�Z�X�p�\�[�X
 * @author	tamada GAME FREAK inc.
 * @date	2005.10.27
 */
//============================================================================================

// �R�����g���͂����ƗF�B�O���[�v�̂h�c��\������
//#define FRIENDLIST_DEBUG

#include "savedata/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���

#include "common.h"

#include "system/gamedata.h"
#include "savedata/savedata.h"


#include "savedata/friendlist.h"
#include "friendlist_local.h"

#include "system/pm_str.h"

#include "gflib/strbuf_family.h"

//============================================================================================
//============================================================================================


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
int FriendList_GetWorkSize(void)
{
	return sizeof(FRIEND_LIST)*FRIENDLIST_MAX;
}

//----------------------------------------------------------
/**
 * @brief	������ԕێ����[�N�̊m��
 * @param	heapID		�������m�ۂ������Ȃ��q�[�v�w��
 * @return	FRIEND_LIST	�擾�������[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
FRIEND_LIST * FriendList_AllocWork(u32 heapID)
{
	int i;
	FRIEND_LIST * flist;
	flist = sys_AllocMemory(heapID, sizeof(FRIEND_LIST)*FRIENDLIST_MAX);
	
	FriendList_Init( flist );

	return flist;
}

//----------------------------------------------------------
/**
 * @brief	FRIEND_LIST�̃R�s�[
 * @param	from	�R�s�[��FRIEND_LIST�ւ̃|�C���^
 * @param	to		�R�s�[��FRIEND_LIST�ւ̃|�C���^
 */
//----------------------------------------------------------
void FriendList_Copy(const FRIEND_LIST * from, FRIEND_LIST * to)
{
	MI_CpuCopy8(from, to, sizeof(FRIEND_LIST));
}


//----------------------------------------------------------
/**
 * @brief	FRIEND_LIST�|�C���^��Ԃ�
 * @param	sv				�Z�[�u�f�[�^
 * @return  FRIEND_LIST		FRIEND_LIST�ւ̃|�C���^
 */
//----------------------------------------------------------
FRIEND_LIST *SaveData_GetFriendList(SAVEDATA * sv)
{
	return SaveData_Get( sv, GMDATA_ID_FRIEND);
}
//============================================================================================
//
//	FRIEND_LIST����̂��߂̊֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�F�B���X�g�f�[�^�̏�����
 * @param	my		�F�B���X�g�ێ����[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
void FriendList_Init( FRIEND_LIST * flist )
{
	int i;
	
	for(i=0;i<FRIENDLIST_MAX;i++){
		memset(&flist[i], 0, sizeof(FRIEND_LIST));
		flist[i].name[0]  = EOM_;
	}
}

//----------------------------------------------------------
/**
 * @brief	���O�Z�b�g
 * @param	flist		������ԕێ����[�N�ւ̃|�C���^
 * @param	name	���O������ւ̃|�C���^
 */
//----------------------------------------------------------
extern void FriendList_SetName(FRIEND_LIST * flist, int no, const STRCODE * name)
{
	int len;

	len = PM_strlen(name);
	GF_ASSERT(len < PERSON_NAME_SIZE + EOM_SIZE);
	PM_strcpy(flist[no].name, name);
}

//----------------------------------------------------------
/**
 * @brief	���O�擾
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @return	STRCODE		���O������ւ̃|�C���^
 */
//----------------------------------------------------------
const STRCODE * FriendList_GetName(const FRIEND_LIST * flist, int no)
{
	return flist[no].name;
}


//----------------------------------------------------------
/**
 * @brief	�����̂h�c�Z�b�g
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @param	id		�h�c�w��	
 */
//----------------------------------------------------------
extern void FriendList_SetID(FRIEND_LIST * flist, int no, u32 id)
{
	flist[no].id = id;
}
//----------------------------------------------------------
/**
 * @brief	�����̂h�c�擾
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @return	int		�����̂h�c	
 */
//----------------------------------------------------------
u32 FriendList_GetID(const FRIEND_LIST * flist, int no)
{
	return flist[no].id;
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
u8  FriendList_GetRomCode( const FRIEND_LIST * flist, int no )
{
	return flist[no].rom_code;
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
void  FriendList_SetRomCode( FRIEND_LIST * flist, int no, u8 rom )
{
	flist[no].rom_code = rom;
}

//----------------------------------------------------------
/**
 * @brief	���ʃZ�b�g
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @param	id		����	
 */
//----------------------------------------------------------
void FriendList_SetSex(FRIEND_LIST * flist, int no, u32 sex)
{
	flist[no].sex = sex;
}
//----------------------------------------------------------
/**
 * @brief	���ʎ擾
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @return	int		�����̐���
 */
//----------------------------------------------------------
u32 FriendList_GetSex(const FRIEND_LIST * flist, int no)
{
	return flist[no].sex;
}



//==============================================================================
/**
 * $brief   �O���[�v���X�gID�Z�b�g
 */
//==============================================================================
void  FriendList_SetGroupListId( FRIEND_LIST * flist , int no, u32 id )
{
	flist->group_id[no] = id;
}

//==============================================================================
/**
 * $brief   �O���[�v���X�gID�Q�b�g
 */
//==============================================================================
u8  FriendList_GetGroupListId( const FRIEND_LIST * flist , int no )
{
	return flist->group_id[no];
}

//==============================================================================
/**
 * $brief   �����R�[�h�擾
 */
//==============================================================================
void  FriendList_SetGroupListRomCode( FRIEND_LIST * flist , int no, u8 rom )
{
	flist->group_romcode[no] = rom;
}

//==============================================================================
/**
 * $brief   �O���[�v�����R�[�h�Z�b�g
 */
//==============================================================================
u8  FriendList_GetGroupListRomCode( const FRIEND_LIST * flist , int no )
{
	return flist->group_romcode[no];
}

//==============================================================================
/**
 * $brief   �O���[�v�C�O�R�[�h�Z�b�g
 */
//==============================================================================
void  FriendList_SetGroupListRegion( FRIEND_LIST * flist , int no, u8 code )
{
	flist->group_region[no] = code;
}

//==============================================================================
/**
 * $brief   �O���[�v�C�O�R�[�h�擾
 */
//==============================================================================
u8  FriendList_GetGroupListRegion( const FRIEND_LIST * flist , int no )
{
	return flist->group_region[no];
}
//==============================================================================
/**
 * $brief   �O���[�v���ʃZ�b�g
 */
//==============================================================================
void  FriendList_SetGroupListSex( FRIEND_LIST * flist , int no, u8 code )
{
	flist->group_sex[no] = code;
}

//==============================================================================
/**
 * $brief   �O���[�v���ʎ擾
 */
//==============================================================================
u8  FriendList_GetGroupListSex( const FRIEND_LIST * flist , int no )
{
	return flist->group_sex[no];
}


//--------------------------------------------------------------------------
/**
 * �w��̃f�[�^�͂��肠���O���[�v�ɓo�^����Ă��邩
 *
 * @param   id		�g���[�i�[�h�c
 * @param   name	���O�i�|�P����������)
 *
 * @retval  int		1:��v����	0:�Ȃ������i�������͑ł��؂����j
 *
 *
 */
//--------------------------------------------------------------------------
int FriendList_Check( FRIEND_LIST * list, u32 id, STRCODE *name)
{
	int i;
	for(i=0;i<FRIENDLIST_MAX;i++){
	    if(0 == PM_strcmp(list->name, name) && (list->id == id)){
			return 1;
		}
	}
	return 0;
}


//----------------------------------------------------------
/**
 * @brief	FriendList���m���������̂��ǂ����𒲂ׂ�
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @param	target	����̎�����ԕێ����[�N�ւ̃|�C���^
 * @return	��v������TRUE
 */
//----------------------------------------------------------
BOOL FriendList_Compare(const FRIEND_LIST * src, const FRIEND_LIST * des)
{
    if(0 == PM_strcmp(src->name, des->name)){
        if(src->id == des->id){
            return TRUE;
        }
    }
    return FALSE;
}




//--------------------------------------------------------------------------
/**
 * ���ݐڑ����̃����o�[�����肠���O���[�v�ɓo�^����
 *
 * @param  none
 *
 * @retval  none	
 *
 *
 */
//--------------------------------------------------------------------------
void FriendList_Update( FRIEND_LIST *mylist, FRIEND_LIST *friends, int num, int heapID)
{
	int i,r,count;
	int search[5];
	FRIEND_LIST *tmp;
	
	// �e���|�����m�ہ�������	
	tmp = sys_AllocMemory(heapID, sizeof(FRIEND_LIST)*FRIENDLIST_MAX);
	FriendList_Init( tmp );

	//����̃����o�[�͊��ɓo�^���݂��H
	for(i=0;i<num;i++){
		search[i] = -1;
		for(r=0;r<FRIENDLIST_MAX;r++){		//�z��search�Ɏ����̂��肠���O���[�v�Ɣ�r�������ʂ��i�[����(-1�F����,0�`:�L��)
			if(FriendList_Compare(&mylist[r], &friends[i])){
				search[i] = r;
			}
		}
	}
	
	//����ʐM���Ă��郁���o�[��o�^����
	count=0;
	for(i=0;i<num;i++){
		tmp[count] = friends[i];
		if(search[i]>=0){
			mylist[search[i]].name[0] = EOM_;			//�o�^�ς݂̏ꍇ�͌��̃e�[�u�����疼�O�������Ă��܂�
		}
		count++;
	}
	
	//���������o�[���X�V����
	for(i=0;i<FRIENDLIST_MAX;i++){
		if(mylist[i].name[0]!=EOM_){			//���ږ�������Ȃ���΍X�V
			tmp[count] = mylist[i];
			count++;
			if(count>=FRIENDLIST_MAX){
				break;							//MAX�𒴂�����o�^�I��
			}
		}
	}
	memcpy(mylist,tmp,sizeof(FRIEND_LIST)*FRIENDLIST_MAX);		//�e���|�������猳�̏ꏊ�ɍX�V
	
	
	sys_FreeMemoryEz(tmp);		//�e���|�������
}



//==============================================================================
/**
 * $brief   �w���ID�͒m�荇����ID�����`�F�b�N����
 *
 * @param   mylist		
 * @param   id		
 *
 * @retval  int		�����̒m�荇����������DIRECT_FRIEND + (���Ԗڂ̒m�荇����<<16)
 *					�Ƃ������̒m�荇��INDIRECT_FRIEND + (���Ԗڂ̒m�荇����<<16)
 *
 */
//==============================================================================
int FriendList_IdFullCheck( FRIEND_LIST *mylist, u32 id )
{
	int i,r;

	for(i=0;i<FRIENDLIST_MAX;i++){
		// ���ڂ̒m�荇�����H
		if(mylist[i].id==id){
			return DIRECT_FRIEND;
		}
	}

	// �ԐړI�Ȓm�荇�����H
	for(i=0;i<FRIENDLIST_MAX;i++){
		for(r=0;r<FRIENDLIST_FRIEND_MAX;r++){
			if(mylist[i].group_id[r]==id){
				return INDIRECT_FRIEND + i;
			}
		}
	}
	return 0;	// �m�荇������Ȃ�
}


//============================================================================================
//	�f�o�b�O�p
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�f�o�b�O�p�F������ԃZ�b�g
 * @param	my		������ԕێ����[�N�ւ̃|�C���^
 * @param	name	���O������ւ̃|�C���^
 * @param	id		ID�w��
 */
//----------------------------------------------------------
void Debug_FriendList_Make(FRIEND_LIST * flist, const STRCODE * name, int id )
{
	FriendList_SetName( flist, 0, name);
	FriendList_SetID( flist, 0, id);
}

void Debug_FriendListAllPrint( FRIEND_LIST * mylist )
{
	int i,r;
	for(i=0;i<FRIENDLIST_MAX;i++){
		OS_TPrintf("%02d: id = %08x\n", i, mylist[i].id);
		OS_TPrintf("    ");
		for(r=0;r<FRIENDLIST_FRIEND_MAX/2;r++){
			OS_TPrintf("%02d: = %08x ", r, mylist[i].group_id[r]);
		}
		OS_TPrintf("\n    ");
		for(r=FRIENDLIST_FRIEND_MAX/2;r<FRIENDLIST_FRIEND_MAX;r++){
			OS_TPrintf("%02d: = %08x ", r, mylist[i].group_id[r]);
		}
		OS_TPrintf("\n");
	}
}