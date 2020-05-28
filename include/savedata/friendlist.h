//============================================================================================
/**
 * @file	friendlist.h
 * @brief	���肠���O���[�v�f�[�^��`�iWiFI�p�͕ʁB�c�r�ʐM�ł̒m�荇���j
 * @author	mori GAME FREAK inc.
 * @date	2006.02.10
 */
//============================================================================================
#ifndef __FRIENDLIST_H__
#define __FRIENDLIST_H__

#include "savedata/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���

#include "gflib/msg_print.h"		//STRCODE�Q�Ƃ̂���
#include "gflib/strbuf.h"			//STRBUF�Q�Ƃ̂���


#define FRIENDLIST_MAX			( 16 )
#define FRIENDLIST_FRIEND_MAX	( 16 )	// �m�荇�����X�g�����u�F�B�̗F�B�v�̐�


#define DIRECT_FRIEND			(  1 )	// ���ڂ̒m�荇��
#define INDIRECT_FRIEND			(  2 )	// �m�荇���̒m�荇��

#define FRIEND_LIST_SIZE		( 136 )

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	���肠���O���[�v�f�[�^�^��`
 */
//----------------------------------------------------------
typedef struct _FRIEND_LIST FRIEND_LIST;

//============================================================================================
//============================================================================================
//----------------------------------------------------------
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//----------------------------------------------------------
extern int           FriendList_GetWorkSize(void);
extern FRIEND_LIST  *FriendList_AllocWork(u32 heapID);
extern void          FriendList_Copy(const FRIEND_LIST * from, FRIEND_LIST * to);

//----------------------------------------------------------
//	FRIEND_LIST����̂��߂̊֐�
//----------------------------------------------------------
extern void  FriendList_Init(FRIEND_LIST * flist);

//���O
extern void  FriendList_SetName(FRIEND_LIST * flist, int no, const STRCODE * name);
extern const STRCODE * FriendList_GetName(const FRIEND_LIST * flist, int no);
//ID
extern void FriendList_SetID(FRIEND_LIST * flist, int no, u32 id);
extern u32  FriendList_GetID(const FRIEND_LIST * flist, int no);

// ����
extern void FriendList_SetSex(FRIEND_LIST * flist, int no, u32 sex);
extern u32 FriendList_GetSex(const FRIEND_LIST * flist, int no);

// ROM�R�[�h�i0:�_�C�� 1:�p�[���j
extern void FriendList_SetRomCode( FRIEND_LIST * flist , int no, u8 rom);
extern u8   FriendList_GetRomCode( const FRIEND_LIST * flist ,int no );


// �O���[�v���X�gID
extern void FriendList_SetGroupListId( FRIEND_LIST * flist , int no, u32 id );
extern u8   FriendList_GetGroupListId( const FRIEND_LIST * flist , int no );

// �O���[�v���X�gROM�R�[�h
extern void FriendList_SetGroupListRomCode( FRIEND_LIST * flist , int no, u8 rom );
extern u8   FriendList_GetGroupListRomCode( const FRIEND_LIST * flist , int no );

// �O���[�v���X�g���R�[�h
extern void FriendList_SetGroupListRegion( FRIEND_LIST * flist , int no, u8 code );
extern u8   FriendList_GetGroupListRegion( const FRIEND_LIST * flist , int no );

// �O���[�v���[�_�[����
u8    FriendList_GetGroupListSex( const FRIEND_LIST * flist , int no );
void  FriendList_SetGroupListSex( FRIEND_LIST * flist , int no, u8 code );

// �O���[�v�`�F�b�N
int   FriendList_Check( FRIEND_LIST * list, u32 id, STRCODE *name);


//--------------------------------------------------------------------------------
// �w���ID�͒m�荇��������������(���d�j
//
// �Ԃ�l��0���ƒm�荇������
// DIRECT_FRIEND���Ǝ����̂��肠��
// INDIRECT_FRIEND���ƗF�B�̂��肠���iINDIRECT_FRIEND + �F�B�̔z��̓Y�������Ԃ�j
//--------------------------------------------------------------------------------
extern int FriendList_IdFullCheck( FRIEND_LIST *mylist, u32 id );

// ���肠���O���[�v�f�[�^����l���n���Ǝ����̂��肠���O���[�v���X�V����
extern void FriendList_Update( FRIEND_LIST *mylist, FRIEND_LIST *friends, int num, int heapID);
//----------------------------------------------------------
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//----------------------------------------------------------
extern FRIEND_LIST * SaveData_GetFriendList(SAVEDATA * sv);


//	flistStatus���m���������̂��ǂ����𒲂ׂ�
BOOL FriendList_Compare(const FRIEND_LIST * flist, const FRIEND_LIST * target);

//----------------------------------------------------------
//	�f�o�b�O�p�f�[�^�����̂��߂̊֐�
//----------------------------------------------------------
extern void Debug_FriendList_Make(FRIEND_LIST * fliststatus, const STRCODE * name, int id);
extern void Debug_FriendListAllPrint( FRIEND_LIST * flist );


#endif //__FRIEND_LIST_H__
