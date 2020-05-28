//==============================================================================
/**
 * @file	we_098.s
 * @brief	�ł񂱂�������			98
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_DENKOUSEKKA
	
// =============================================================================
//
//
//	���ł񂱂�������			98
//
//
// =============================================================================
#define WE098_SHAKE_W_X	(2)		// �ӂ蕝
#define WE098_SHAKE_NUM	(1)		// �ӂ��
#define WE098_SHAKE_SYNC (1)	// �V���N��
WEST_DENKOUSEKKA:
	LOAD_PARTICLE_DROP	0,W_098_SPA

	POKEOAM_RES_INIT

	POKEOAM_RES_LOAD	0,
	POKEOAM_RES_LOAD	1,

	SE_L			SEQ_SE_DP_W104

	// �`��J�n
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_1,
	PT_DROP_EX			WEDEF_DROP_M2, WEDEF_DROP_M2,
/*	
// -------------------------------------------------------------
	ADD_PARTICLE 	0,W_098_098_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_098_098_BALL_BURN,	EMTFUNC_DEFENCE_POS

	//SE_R			SEQ_SE_DP_030
	//SE_R			SEQ_SE_DP_W026
	SE_R			SEQ_SE_DP_030

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, WE098_SHAKE_W_X, 0,WE098_SHAKE_SYNC, WE098_SHAKE_NUM, WE_TOOL_E1 | WE_TOOL_SSP, 0, 0
	FUNC_CALL		WEST_SP_WE_098, 0,0,0,0,0,0,0,0,0
*/
	FUNC_CALL		WEST_SP_WE_098, 0,0,0,0,0,0,0,0,0
	
	WAIT			15
	SE_R			SEQ_SE_DP_030
	
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1
	POKEOAM_RES_FREE
	PT_DROP_RESET_EX
	
	ADD_PARTICLE 	0,W_098_098_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_098_098_BALL_BURN,	EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, WE098_SHAKE_W_X, 0,WE098_SHAKE_SYNC, WE098_SHAKE_NUM, WE_TOOL_E1 | WE_TOOL_SSP, 0, 0

	WAIT_FLAG

// -------------------------------------------------------------
//	WAIT			30	WAIT			5	
/*
	WORK_CLEAR
	HAIKEI_PARA_CHG	WEDEF_GP_INDEX_SPEED_X,  32
	WAIT			5
	HAIKEI_PARA_CHG	WEDEF_GP_INDEX_SPEED_X,  16
	WAIT			5
	HAIKEI_PARA_CHG	WEDEF_GP_INDEX_SPEED_X,  8
	WAIT			5
	HAIKEI_PARA_CHG	WEDEF_GP_INDEX_SPEED_X,  4
	WAIT			5
	WORK_SET		WEDEF_GP_INDEX_SPEED_X,  2
	WORK_SET		WEDEF_GP_INDEX_SPEED_Y,  WEDEF_HAIKEI_SPEED_Y
	HAIKEI_RECOVER	BG_ID_097, WEDEF_HAIKEI_RC_MODE_NONE | WEDEF_HAIKEI_SBIT_STOP
	HAIKEI_CHG_WAIT
*/

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
