//==============================================================================
/**
 * @file	we_304.s
 * @brief	�n�C�p�[�{�C�X			304
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HAIPAABOISU
	
// =============================================================================
//
//
//	���n�C�p�[�{�C�X			304
//
//
// =============================================================================
#define W304_BG_PAL_FADE		(0)
#define W304_BG_PAL_FADE_WAIT	(1)
#define W304_BG_PAL_FADE_COL	(0x33ff)

WEST_HAIPAABOISU:
	
	LOAD_PARTICLE_DROP	0,W_304_SPA
	
	LOOP_LABEL	2
		WAIT			10
		VOICE_PLAY	PV_W_HYPER1, WAZA_SE_PAN_AT, PV_VOL_DEFAULT
		VOICE_WAIT_STOP 0
		VOICE_PLAY	PV_W_HYPER2, WAZA_SE_PAN_AT, PV_VOL_MAX

		ADD_PARTICLE 	0,W_304_304_RING_BEAM, EMTFUNC_FIELD_OPERATOR
		EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_L304SP, OPERATOR_AXIS_AT_304, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

		ADD_PARTICLE 	0,W_304_304_HIT_MARK, EMTFUNC_DEFENCE_POS
		
		FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, W304_BG_PAL_FADE, W304_BG_PAL_FADE_WAIT, 0, 8, W304_BG_PAL_FADE_COL,
		FUNC_CALL		WEST_SP_WT_SHAKE, 5, 0, 2, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,
		FUNC_CALL		WEST_SP_WT_SHAKE, 5, 0, 2, 1, 2,  WE_TOOL_E2 | WE_TOOL_SSP,
		
		WAIT_FLAG
		
		FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, W304_BG_PAL_FADE, W304_BG_PAL_FADE_WAIT, 8, 0, W304_BG_PAL_FADE_COL,
		
		WAIT_FLAG
		VOICE_WAIT_STOP 0
		
	LOOP

	WAIT			2			///< ����TCB�폜�҂�

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
