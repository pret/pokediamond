//============================================================================================
/**
 * @file	namein.h
 * @bfief	���O���͉�ʏ���
 * @author	Akito Mori
 * @date	05.10.05
 */
//============================================================================================
#ifndef _NAMEIN_H_
#define _NAMEIN_H_

#include "gflib/strbuf.h"
#include "poketool/boxdata.h"
#include "savedata/config.h"

//============================================================================================
//	�萔��`
//============================================================================================

// ���O���̓��[�h
enum {
	NAMEIN_MYNAME = 0,	// �����̖��O
	NAMEIN_POKEMON,		// �|�P�����̖��O
	NAMEIN_BOX,			// �{�b�N�X�̖��O
	NAMEIN_RIVALNAME,	// ���C�o���l�[��
	NAMEIN_FRIENDCODE,	// �Ƃ������R�[�h
	NAMEIN_RANDOMGROUP, // �����̎�O���[�v�̖��O
	NAMEIN_STONE,		// �Δ�(�z�z�j
	NAMEIN_FRIENDNAME,  // WIFI�Ƃ������蒠�ɏ������ނƂ������̖��O
};


// �|�P�������O���͂̒���
#if (PM_LANG==LANG_JAPAN)
#define NAMEIN_POKEMON_LENGTH	(  5 )
#else
#define NAMEIN_POKEMON_LENGTH	( 10 )
#endif

// �g���[�i�[�����͂̒���
#if (PM_LANG==LANG_JAPAN)
#define NAMEIN_PERSON_LENGTH	(  5 )
#else
#define NAMEIN_PERSON_LENGTH	( 7 )
#endif


// �O���[�v�����͂̒���
#if (PM_LANG==LANG_JAPAN)
#define NAMEIN_GROUP_LENGTH		(  5 )
#else
#define NAMEIN_GROUP_LENGTH		( 7 )
#endif





#define STRBUF_ENABLE_MAGICNUMBER	(0x12345678)


extern const PROC_DATA NameInProcData;	// �v���Z�X��`�f�[�^


typedef struct NAMEIN_WORK NAMEIN_WORK;	// �|�C���^�Q�Ƃ����ł��閼�O���̓��[�N�\����

// ���O���͌Ăяo�����ɕK�v�ȃp�����[�^�̍\����
// NAMEIN_PARAM *NameIn_ParamAllocMake(int HeapId, int mode, int info, int wordmax)
// ���Ăяo���č쐬����B
// �B������
typedef struct{
	int mode;		// ���̓��[�h(enum�Q�Ɓj
	int info;		// ���̓��[�h�Ƃ��Ēj��l���E����l���A�|�P�����̊J��NO�Ȃ�
	int form;		// ���̓��[�h���|�P�����̎��Ɍ`��l���󂯎��
	int wordmax;	// ���͕����ő吔
	int sex;		// �|�P�����̐���(PARA_MALE=0...PARA_FEMALE=1...PARA_UNK=2(���ʂȂ�))


	int cancel;		// ���O���͂��I���������ɔ��f�����t���O�B
					// ���͕������O�����������B�������͍ŏ��Ɠ����������ꍇ�͂��̃t���O�����B

	STRBUF *strbuf; // ����STRBUF�ɂ͂Q�̈Ӗ������݂���B
					// �P�͖��O���͉�ʂ���f�[�^���󂯎�郏�[�N�ł��邱�ƁB���O���͂��I������炱������R�s�[����
					// �����P�́A���O���͂ɍs���Ƃ��ɂ����ɕ�������i�[���Ă�����,
					// ���O���͉�ʂ͂��̕������\�����Ȃ���J�n����B�����Ƃ��Ă��@�\����

	u16 str[20];	// ���̔z��ɂ����ʂ͕Ԃ��Ă��܂��B�i20�ɈӖ��͂���܂���j


	// --------�|�P�����ߊl�Ń{�b�N�X�]���ɂȂ������ɕK�v-------------
	
	int get_msg_id; 	// �|�P�����ߊl�̎���BOX�]���������������̃��b�Z�[�WID������
	BOX_DATA  *boxdata;	// �|�P�����ߊl�̎���BOX�]���������������ɁABOX�̖��O���擾���邽�߂ɕK�v
	CONFIG    *config;  // �R���t�B�O�\����

}NAMEIN_PARAM;

//==============================================================================
/**
 * �O�����疼�O���͏������p�����[�^�[�����炢�������[�N������ĕԂ�
 *
 * @param   HeapId		���[�N���쐬����HEAPID���w��i������Free����K�v������܂��j
 * @param   mode		���O���̓��[�h�ienum����I���j
 * @param   info		�j�E��(PM_MALE,PM_FEMALE)�A�|�P�����̊J��NO�Ȃǂ��i�[�ABOX��0�ł悢
 * @param   wordmax		���͕����ő吔
 *
 * @retval  NAMEIN_PARAM *	���̃|�C���^��NameInInit�ɓn��
 */
//==============================================================================
extern NAMEIN_PARAM* NameIn_ParamAllocMake(int HeapId, int mode, int info, int wordmax, CONFIG *config);

//==============================================================================
/**
 * ���O���̓p�����[�^�[�폜
 * ���O���͏I����ɎQ�Ƃ��I�������ɂ��̊֐����Ăяo���ĉ�����Ă��������B
 * 
 * @param   param			
 *
 * @retval  extern void		
 */
//==============================================================================
extern void NameIn_ParamDelete(NAMEIN_PARAM *param);

#endif