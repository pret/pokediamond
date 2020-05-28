//==============================================================================
/**
 * @file	we_130.s
 * @brief	���P�b�g����			130
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ROKETTOZUTUKI
	
// =============================================================================
//
//
//	�����P�b�g����			130
//
//
// =============================================================================
#define WE_130_MOVE_X	(14)
#define WE_130_MOVE_Y	(8)
WEST_ROKETTOZUTUKI:
	
	LOAD_PARTICLE_DROP	0,W_130_SPA
	
	TURN_CHK	WEST_130_TURN_1, WEST_130_TURN_2
	
	SEQEND

#define ROTA_NUM_S ((360*0xffff) / 360)
#define ROTA_NUM_E ((375*0xffff) / 360)
#define ROTA_SYNC	(10)
WEST_130_TURN_1:

//	ADD_PARTICLE 	0,W_130_130_ROKET_KEMURI,	EMTFUNC_ATTACK_POS

	LOOP_LABEL		2
		SE_L			SEQ_SE_DP_W036
		FUNC_CALL		WEST_SP_WE_T10,	4, 4, -WE_MOVE_X_VAL_DEF, 0, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT_FLAG
		FUNC_CALL		WEST_SP_POKEROTA_00, 6, ROTA_NUM_S, ROTA_NUM_E, ROTA_SYNC,1,0,64,0,0
		WAIT_FLAG
		FUNC_CALL		WEST_SP_WE_T10,	4, 4, +WE_MOVE_X_VAL_DEF, 0, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT_FLAG
	LOOP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	SEQEND
	
WEST_130_TURN_2:

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG
	
	SE_L			SEQ_SE_DP_W036

//	ADD_PARTICLE 	0,W_130_130_ROKET_KEMURI,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_WE_T10,	4, 4, -WE_MOVE_X_VAL_DEF, 0, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	FUNC_CALL		WEST_SP_POKEROTA_00, 4, ROTA_NUM_S, ROTA_NUM_E, ROTA_SYNC,1,0,0,0,0
	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_T10,	4, 4, WE_MOVE_X_VAL_DEF + 14, -8, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG

	SE_R			SEQ_SE_DP_W025B
	ADD_PARTICLE 	0,W_130_130_ROKET_HIT,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_130_130_ROKET_BOMB,		EMTFUNC_DEFENCE_POS
//	ADD_PARTICLE 	0,W_130_130_ROKET_LINE,		EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 6, 0, 1, 6,  WE_TOOL_E1 | WE_TOOL_SSP,

	FUNC_CALL		WEST_SP_WE_T10,	4, 2, -14, +8, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG
	SEQEND

