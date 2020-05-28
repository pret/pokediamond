//==============================================================================
/**
 * @file	we_132.s
 * @brief	����݂�			132
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KARAMITUKU
	
// =============================================================================
//
//
//	������݂�			132
//
//
// =============================================================================
#define KARAMI_RES_NO		(0)
#define KARAMI_RES_NUM		(1)
#define KARAMI_ACT_NUM		(4)
WEST_KARAMITUKU:
	
	///<�����������@�ǂݍ��ݏ���
	CATS_RES_INIT		KARAMI_RES_NO, KARAMI_ACT_NUM, KARAMI_RES_NUM, KARAMI_RES_NUM, KARAMI_RES_NUM, KARAMI_RES_NUM, 0, 0
	CATS_CAHR_RES_LOAD	KARAMI_RES_NO, EFFECT_132_NCGR_BIN
	CATS_PLTT_RES_LOAD	KARAMI_RES_NO, EFFECT_132_NCLR, 1
	CATS_CELL_RES_LOAD	KARAMI_RES_NO, EFFECT_132_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	KARAMI_RES_NO, EFFECT_132_NANR_BIN
	
	///<����
	CATS_ACT_ADD		KARAMI_RES_NO, WEST_CSP_WE_132, EFFECT_132_NCGR_BIN, EFFECT_132_NCLR, EFFECT_132_NCER_BIN, EFFECT_132_NANR_BIN, 0, 0, 0,0,

	LOOP_LABEL	5
		WAIT 2
		SE_R			SEQ_SE_DP_W020
	LOOP

	LOOP_LABEL	2
		WAIT 6
		SE_R			SEQ_SE_DP_W030
	LOOP
	WAIT_FLAG

	///<�j������
	CATS_RES_FREE		KARAMI_RES_NO
	
	SEQEND
