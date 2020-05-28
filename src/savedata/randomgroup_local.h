//============================================================================================
/**
 * @file	randomgroup_local.h
 * @brief	�����_���O���[�v�\���̒�`
 * @author	mori GAME FREAK inc.
 * @date	2006.03.22
 */
//============================================================================================
#ifndef __RANDOMGROUP_LOCAL_H__
#define __RANDOMGROUP_LOCAL_H__

typedef struct{

	/// �O���[�v��
	STRCODE 		group_name[GROUP_NAME_SIZE + EOM_SIZE];		// 16

	/// ���[�_�[��
	STRCODE 		name[PERSON_NAME_SIZE + EOM_SIZE];			// 32

	///	���[�_�[�̐���
	u8 sex;														// 33

	///	���[�_�[�̌���R�[�h
	u8 region_code;												// 34

	///	pudding
	u16 dummy;													// 36

	/// �����̎�i�V�K�o�^���ɍ쐬�j
	u32				seed;										// 40

	/// ����(1��1��X�V�j
	u32				random;										// 44

}RANDOM_SEED;

struct _RANDOM_GROUP{

	RANDOM_SEED	group[RANDOMGROUP_MAX];

};


extern BOOL RandomGroup_IsNullData(const RANDOM_SEED * rs);
extern BOOL RandomGroup_Compare(const RANDOM_SEED * s1, const RANDOM_SEED * s2);

#endif
