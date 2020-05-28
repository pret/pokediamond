//==============================================================================
/**
 * @file	we_224.s
 * @brief	���K�z�[��			224
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MEGAHOON
	
// =============================================================================
//
//
//	�����K�z�[��			224
//
//
// =============================================================================
#define MEGAHOON_SPEED_AT	( 1 )

#define MEGAHOON_RES_NO			(0)
#define MEGAHOON_RES_NUM		(2)
#define MEGAHOON_ACT_NUM		(2)

WEST_MEGAHOON:
	
	LOAD_PARTICLE_DROP	0,W_224_SPA

	///<�U������J�n	
	FUNC_CALL			WEST_SP_WE_224AT, 0, 0,

	SE_L			SEQ_SE_DP_W082
	WAIT	10
	
	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 	1
	HAIKEI_CHG		BG_ID_224, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	WAIT			5
	
	ADD_PARTICLE 	0,W_224_224_MEGA_SHOOT1, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_SP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	ADD_PARTICLE 	0,W_224_224_MEGA_SHOOT2, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_SP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	///< �p�[�e�B�N��
	ADD_PARTICLE 	0,W_224_224_MEGA_HIT1, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_224_224_MEGA_HIT2, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_224_224_MEGA_HIT3, EMTFUNC_DEFENCE_POS
	SE_R			SEQ_SE_DP_W011

	///< �h�䓮��
	FUNC_CALL			WEST_SP_WE_224DF, 0, 0,
	
	WAIT			5
	FUNC_CALL		WEST_SP_BG_SHAKE, 5, 5, 0, 1, 6, 0

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	WAIT_FLAG

	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R,	1
	HAIKEI_RECOVER	BG_ID_224, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	HAIKEI_CHG_WAIT
		
	SEQEND

