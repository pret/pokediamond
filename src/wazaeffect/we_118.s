//==============================================================================
/**
 * @file	we_118.s
 * @brief	��т��ӂ�			118
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_YUBIWOHURU
	
// =============================================================================
//
//
//	����т��ӂ�			118
//
//
// =============================================================================

#define YUBI_RES_NO			(0)
#define YUBI_RES_NUM		(1)
#define YUBI_ACT_NUM		(1)

WEST_YUBIWOHURU:

	///<�����������@�ǂݍ��ݏ���
	CATS_RES_INIT		YUBI_RES_NO, YUBI_ACT_NUM, YUBI_RES_NUM, YUBI_RES_NUM, YUBI_RES_NUM, YUBI_RES_NUM, 0, 0
	CATS_CAHR_RES_LOAD	YUBI_RES_NO, EFFECT_118_NCGR_BIN
	CATS_PLTT_RES_LOAD	YUBI_RES_NO, EFFECT_118_NCLR, 1
	CATS_CELL_RES_LOAD	YUBI_RES_NO, EFFECT_118_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	YUBI_RES_NO, EFFECT_118_NANR_BIN
	
	SE_L				SEQ_SE_DP_W118

	///<����
	CATS_ACT_ADD		YUBI_RES_NO, WEST_CSP_WE_118, EFFECT_118_NCGR_BIN, EFFECT_118_NCLR, EFFECT_118_NCER_BIN, EFFECT_118_NANR_BIN, 0, 0, 0,0,

	WAIT				10
	//SE_REPEAT_L			SEQ_SE_DP_W039,4,5
	//SE_REPEAT_L			SEQ_SE_DP_W039,6,4
	SE_REPEAT_L			SEQ_SE_DP_W039,8,3

	WAIT_FLAG

	WAIT				8

	///<�j������
	CATS_RES_FREE		YUBI_RES_NO

	SEQEND
