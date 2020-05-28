//==============================================================================
/**
 * @file	we_199.s
 * @brief	���b�N�I��			199
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ROKKUON
	
// =============================================================================
//
//
//	�����b�N�I��			199
//
//
// =============================================================================
#define ROKKUON_RES_NO			(0)
#define ROKKUON_RES_NUM		(1)
#define ROKKUON_ACT_NUM		(1)
WEST_ROKKUON:
	
	///<�����������@�ǂݍ��ݏ���
	CATS_RES_INIT		ROKKUON_RES_NO, ROKKUON_ACT_NUM, ROKKUON_RES_NUM, ROKKUON_RES_NUM, ROKKUON_RES_NUM, ROKKUON_RES_NUM, 0, 0
	CATS_CAHR_RES_LOAD	ROKKUON_RES_NO, EFFECT_199_NCGR_BIN
	CATS_PLTT_RES_LOAD	ROKKUON_RES_NO, EFFECT_199_NCLR, 1
	CATS_CELL_RES_LOAD	ROKKUON_RES_NO, EFFECT_199_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	ROKKUON_RES_NO, EFFECT_199_NANR_BIN
	
	///<����
	CATS_ACT_ADD		ROKKUON_RES_NO, WEST_CSP_WE_199, EFFECT_199_NCGR_BIN, EFFECT_199_NCLR, EFFECT_199_NCER_BIN, EFFECT_199_NANR_BIN, 0, 0, 0,0,

	WAIT	16

	LOOP_LABEL	4
		SE_R			SEQ_SE_DP_GETTING
		WAIT 8
	LOOP

	WAIT				15
	SE_R				SEQ_SE_DP_081
	
	WAIT_FLAG

	///<�j������
	CATS_RES_FREE		ROKKUON_RES_NO
	
	SEQEND
