//==============================================================================
/**
 * @file	we_262.s
 * @brief	�����݂₰			262
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_OKIMIYAGE
	
// =============================================================================
//
//
//	�������݂₰			262
//
//
// =============================================================================
WEST_OKIMIYAGE:
	
	// �|�P����OAM����
	POKEOAM_RES_INIT

	POKEOAM_RES_LOAD	0,
	POKEOAM_RES_LOAD	1,

	// �`��J�n
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_E1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_1,

	PT_DROP_EX_2		WEDEF_DROP_M2, WEDEF_DROP_M2, WEDEF_POKE_CAP_ID_2, WEDEF_POKE_RES_2,
	PT_DROP_EX_2		WEDEF_DROP_E2, WEDEF_DROP_E2, WEDEF_POKE_CAP_ID_3, WEDEF_POKE_RES_3,

	FUNC_CALL		WEST_SP_WE_262, 0,0,0,0,0,0,0,0,0
	SE_L			SEQ_SE_DP_W060
	WAIT	24
	SE_R			SEQ_SE_DP_W060B

	WAIT_FLAG	///<TCB�҂�

	// �|�P����OAM�j��
	POKEOAM_RES_FREE
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1

	PT_DROP_RESET_EX_2	WEDEF_POKE_CAP_ID_2
	PT_DROP_RESET_EX_2	WEDEF_POKE_CAP_ID_3
	
	SEQEND
