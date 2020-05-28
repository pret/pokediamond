//==============================================================================
/**
 * @file	we_134.s
 * @brief	�X�v�[���܂�			134
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_SUPUUNMAGE
	
// =============================================================================
//
//
//	���X�v�[���܂�			134
//
//
// =============================================================================
#define SPOON_RES_NO		(0)
#define SPOON_RES_NUM		(1)
#define SPOON_ACT_NUM		(3)
WEST_SUPUUNMAGE:

	SE_L			SEQ_SE_DP_W060

	///<�����������@�ǂݍ��ݏ���
	CATS_RES_INIT		SPOON_RES_NO, SPOON_ACT_NUM, SPOON_RES_NUM, SPOON_RES_NUM, SPOON_RES_NUM, SPOON_RES_NUM, 0, 0
	CATS_CAHR_RES_LOAD	SPOON_RES_NO, EFFECT_134_NCGR_BIN
	CATS_PLTT_RES_LOAD	SPOON_RES_NO, EFFECT_134_NCLR, 1
	CATS_CELL_RES_LOAD	SPOON_RES_NO, EFFECT_134_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	SPOON_RES_NO, EFFECT_134_NANR_BIN
	
	///<����
	CATS_ACT_ADD		SPOON_RES_NO, CLACT_SP_WE_134, EFFECT_134_NCGR_BIN, EFFECT_134_NCLR, EFFECT_134_NCER_BIN, EFFECT_134_NANR_BIN, 0, 0, 0,0,

	WAIT 32

	SE_L			SEQ_SE_DP_154
	SE_WAITPLAY_L	SEQ_SE_DP_154,20

	// ���邨��
	LOOP_LABEL	3
		WAIT 20
	LOOP

	WAIT 27
	// �܂��鉹
	SE_L				SEQ_SE_DP_150
	WAIT 13

	
	WAIT_FLAG

	///<�j������
	CATS_RES_FREE		SPOON_RES_NO
	
	SEQEND
