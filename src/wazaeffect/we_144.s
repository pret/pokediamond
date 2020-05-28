//==============================================================================
/**
 * @file	we_144.s
 * @brief	�ւ񂵂�			144
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HENSIN
	
// =============================================================================
//
//
//	���ւ񂵂�			144
//
//
// =============================================================================
WEST_HENSIN:
	
	POKEOAM_RES_INIT
	POKEOAM_RES_LOAD	0
	///< ����
	FUNC_CALL			WEST_SP_WE_SSP_POKE_VANISH, 2, WE_TOOL_M1, 1
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
	PT_DROP_EX			WEDEF_DROP_M2, WEDEF_DROP_M2,
	WAIT_FLAG
	
	SE_L				SEQ_SE_DP_W100
	
	FUNC_CALL			WEST_SP_MOSAIC, 4, 0, +1,  0,  0
	WAIT_FLAG
//	POKEOAM_RES_FREE
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	
	///< �|�P��������ւ�
	HENSIN_ON			WE_HENSIN_DF
	
	///< �ϐg�|�P
//	POKEOAM_RES_INIT
	POKEOAM_RES_LOAD	1
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_1,
//	PT_DROP_EX			WEDEF_DROP_M2, WEDEF_DROP_M2,
	
	FUNC_CALL			WEST_SP_MOSAIC, 4, 1, -1, 15, 15
	WAIT				12
	
	FUNC_CALL			WEST_SP_WE_SSP_POKE_VANISH, 2, WE_TOOL_M1, 0
	
	WAIT				1
	
	POKEOAM_RES_FREE
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1
	PT_DROP_RESET_EX
	
	SEQEND
