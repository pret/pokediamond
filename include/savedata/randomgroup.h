//============================================================================================
/**
 * @file	randomgroup.h
 * @brief	�����̎�O���[�v��`�w�b�_�t�@�C��
 * @author	mori GAME FREAK inc.
 * @date	2006.03.22
 */
//============================================================================================
#ifndef __RANDOMGROUP_H__
#define __RANDOMGROUP_H__


#include "savedata/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���

#include "gflib/msg_print.h"		//STRCODE�Q�Ƃ̂���
#include "gflib/strbuf.h"			//STRBUF�Q�Ƃ̂���


//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�����_���O���[�v�f�[�^�^��`
 */
//----------------------------------------------------------
typedef struct _RANDOM_GROUP RANDOM_GROUP;


// RandomGroup_<Get*Set>FriendInfo�Ŏg��enum
enum{
	RANDOMGROUP_MINE=0,
	RANDOMGROUP_MYUSE,
	RANDOMGROUP_DATA0,
	RANDOMGROUP_DATA1,
	RANDOMGROUP_DATA2,
	RANDOMGROUP_DATA3,
	
	RANDOMGROUP_MAX,	///< �����_���O���[�v�̐�
};


enum{
	RANDOMGROUP_NAME_GROUP=0,	///< �O���[�v��
	RANDOMGROUP_NAME_LEADER,	///< ���[�_�[��
};
//============================================================================================
//============================================================================================
//----------------------------------------------------------
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//----------------------------------------------------------
extern int RandomGroup_GetWorkSize(void);
extern void RandomGroup_Init(RANDOM_GROUP * randomgroup );

extern RANDOM_GROUP *SaveData_GetRandomGroup(SAVEDATA * sv);

extern void RandomGroup_Copy( RANDOM_GROUP *randomgroup, int from, int to );

//�����o�߂ɂ��X�V����
extern void RandomGroup_Update( RANDOM_GROUP* randomgroup, u32 days );
//�Q�[�����ŎQ�Ƃ��闐���̃^�l�擾
extern u32  RandomGroup_GetDefaultRandom( RANDOM_GROUP* randomgroup );

//�����̃^�l�ݒ�E�擾�֘A
extern void RandomGroup_SetRandomSeed( RANDOM_GROUP* randomgroup, int no, u32 seed );
extern u32  RandomGroup_GetRandomSeed( RANDOM_GROUP* randomgroup, int no );
extern void RandomGroup_SetRandom( RANDOM_GROUP* randomgroup, int no );
extern u32  RandomGroup_GetRandom( RANDOM_GROUP* randomgroup, int no );


//���O�擾
extern const STRCODE *RandomGroup_GetNamePtr( const RANDOM_GROUP *randomgroup, int no, int type );
//���O�Z�b�g
extern void  RandomGroup_SetName( RANDOM_GROUP *randomgroup, int no, int type, STRBUF *name );
//���[�W�����R�[�h�i���R�[�h�j�Z�b�g
extern void RandomGroup_SetRegionCode( RANDOM_GROUP *randomgroup, int no, int region_code );
//���[�W�����R�[�h�i���R�[�h�j�擾
extern int RandomGroup_GetRegionCode( const RANDOM_GROUP *randomgroup, int no);
//���ʃZ�b�g
extern void RandomGroup_SetSex( RANDOM_GROUP *randomgroup, int no, int sex);
//���ʎ擾
extern int RandomGroup_GetSex( const RANDOM_GROUP *randomgroup, int no);

//���݃`�F�b�N
extern BOOL RandomGroup_ExistCheck(const RANDOM_GROUP * rg, int no);
//�o�^�`�F�b�N
extern BOOL RandomGroup_EntryCheck(const RANDOM_GROUP * rg, int no);

//�����O���[�v���̑��݃`�F�b�N
extern BOOL RandomGroup_SameGroupNameCheck(const RANDOM_GROUP * rg, const STRCODE * group_name);

//----------------------------------------------------------
//	���R�[�h�֘A�֐�
//	���풓�̈�ɂȂ����߂Ƀ��R�[�h�ȊO����ĂԂ��Ƃ͂ł��Ȃ�
//----------------------------------------------------------
extern u32 RandomGroup_GetDefaultDataSize(RANDOM_GROUP * rg);
extern void * RandomGroup_GetDefaultData(RANDOM_GROUP * rg);
extern void RandomGroup_RecordMix(int member, int my_id, RANDOM_GROUP * rg, const void ** darray);
extern void RandomGroup_Debug_RecordMix(SAVEDATA * sv);;

#endif

