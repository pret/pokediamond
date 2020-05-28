//============================================================================================
/**
 * @file	mystatus_local.h
 * @author	tamada
 * @date	2006.01.27
 * @brief	������ԃf�[�^�^
 *
 * �Z�[�u�f�[�^�֘A�̋��L�w�b�_�B�O�����J�͂��Ȃ��B
 */
//============================================================================================
#ifndef	__MYSTATUS_LOCAL_H__
#define	__MYSTATUS_LOCAL_H__

//----------------------------------------------------------
/**
 * @brief	������ԃf�[�^�^��`
 */
//----------------------------------------------------------
struct _MYSTATUS {
	STRCODE name[PERSON_NAME_SIZE + EOM_SIZE];		// 16
	u32 id;											// 20
	u32 gold;										// 24

	u8 sex;	
	u8 region_code;									//26

	u8 badge;										
	u8 trainer_view;	// ���j�I�����[�����ł̌����ڃt���O //28
	u8 rom_code;		// 0:�_�C��  1:�p�[��		// 29

	u8 dp_clear:1;		// DP�N���A���Ă��邩�t���O
	u8 dp_zenkoku:1;	// DP�S���}�ӎ�ɓ���Ă��邩�t���O
	u8 dummy1:6;									// 30
	u8 dummy2;										// 31
	u8 dummy3;										// 32
};


#endif	/* __MYSTATUS_LOCAL_H__ */
