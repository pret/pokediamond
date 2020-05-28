//==============================================================================================
/**
 * @file	snd_test.h
 * @brief	�T�E���h�e�X�g(�T�E���h�`�F�b�N)
 * @author	nohara
 * @date	2005.07.04
 */
//==============================================================================================
#include "data/sound/sound_data.h"	//�T�E���h�̎�ނ��Ƃ̃X�^�[�g�i���o�[��`


//==============================================================================================
//
//	extern�錾
//
//==============================================================================================
extern void SndTestProc(void);


//==============================================================================================
//
//	��`
//
//==============================================================================================
//�T�E���h�̎��
enum{
	SND_TEST_TYPE_BGM = 0,
	SND_TEST_TYPE_SE,
	SND_TEST_TYPE_PV,

	SND_TEST_TYPE_MAX,
};

//�X�^�[�g�i���o�[
#define SND_TEST_BGM_START_NO	(BGM_START)
#define SND_TEST_SE_START_NO	(SE_START)
#define SND_TEST_PV_START_NO	(PV_START)

//�I���i���o�[
#define SND_TEST_BGM_END_NO		(SEQ_BGM_END - 1)
#define SND_TEST_SE_END_NO		(SEQ_SE_END - 1)
#define SND_TEST_PV_END_NO		(SEQ_PV_END - 1)

//#define SND_TEST_BG_FRAME		(GF_BGL_FRAME1_M)
#define SND_TEST_BG_FRAME		(GF_BGL_FRAME3_M)

//BMP�E�B���h�E
enum{
	SND_TEST_BMPWIN_FRAME	= GF_BGL_FRAME1_M,
	SND_TEST_BMPWIN_PX1		= 1,
	SND_TEST_BMPWIN_PY1		= 1,
	SND_TEST_BMPWIN_SX		= 29,
	SND_TEST_BMPWIN_SY		= 22,
	SND_TEST_BMPWIN_PL		= 0,
	SND_TEST_BMPWIN_CH		= 1,
};

//���b�Z�[�W�\���ʒu
enum{
	ST_TITLE_X			= (8*1),	//�T�E���h�`�F�b�N
	ST_TITLE_Y			= (8*1),

	ST_KEY_X			= (8*13),	//�L�[����
	ST_KEY_Y			= (0),

	ST_NAME_X			= (8*7),	//SEQ_??
	ST_TYPE_X			= (8*2),	//BGM,SE,PV
	ST_CURSOR_X			= (8*1),	//�J�[�\���ʒu

	ST_BGM_MSG_Y		= (16*3),	//BGM
	ST_SE_MSG_Y			= (16*6),	//SE
	ST_PV_MSG_Y			= (16*9),	//PV
};

//mainSys_sequence�̒�`
enum{
	SEQ_SND_TEST_INIT = 0,
	SEQ_SND_TEST_MAIN,
	SEQ_SND_TEST_END,
};


