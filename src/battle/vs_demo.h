//============================================================================================
/**
 * @file	vs_demo.h
 * @brief	�ʐM�ΐ�f��
 * @author	Hiroyuki Nakamura
 * @date	06.04.26
 */
//============================================================================================
#ifndef VS_DEMO_H
#define VS_DEMO_H
#undef GLOBAL
#ifdef VS_DEMO_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


enum {
	VSD_PARTY_LEFT1 = 0,	// �����p�[�e�B�̃v���C���[�P
	VSD_PARTY_RIGHT1,		// �E���p�[�e�B�̃v���C���[�Q
	VSD_PARTY_LEFT2,		// �����p�[�e�B�̃v���C���[�P
	VSD_PARTY_RIGHT2,		// �E���p�[�e�B�̃v���C���[�Q
	VSD_PARTY_MAX
};

typedef struct {
	BATTLE_PARAM * bp;				// �퓬�p�����[�^
	POKEPARTY * pp[VSD_PARTY_MAX];	// �|�P�����f�[�^
	STRBUF * name[VSD_PARTY_MAX];	// �v���[���[��
	u32	heap;
	u8	mode;
	u8	type;
	u8	result;
	u8	end_flg;
}VS_DEMO_DATA;

enum {
	VSD_MODE_MULTI = 0,
	VSD_MODE_IN,
	VSD_MODE_END
};

enum {
	VSD_TYPE_NORMAL = 0,
	VSD_TYPE_MULTI,

	VSD_TYPE_LEFT = 0,
	VSD_TYPE_RIGHT
};

enum {
	VSD_RESULT_WIN = 1,		// ����
	VSD_RESULT_LOSE,		// ����
	VSD_RESULT_DRAW,		// ��������
};

//--------------------------------------------------------------------------------------------
/**
 * �^�X�N�ǉ�
 *
 * @param	dat		�o�b�O�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void VSDemo_TaskAdd( VS_DEMO_DATA * dat );


#undef GLOBAL
#endif	/* VS_DEMO_H */
