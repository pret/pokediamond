
//============================================================================
/**
 *
 *@file		sub_193.s
 *@brief	�퓬�V�[�P���X
 *			�䂤�΂��_���[�W�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_193:
	//���߂������L���ɂȂ�悤��LAST_DAMAGE�Ƀ_���[�W�l���i�[
//	VALUE_WORK		VAL_SET,BUF_PARA_LAST_DAMAGE_ATTACK,BUF_PARA_HP_CALC_WORK
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			TokuseiDamageM2MMsg,TAG_NICK_TOKU_NICK,SIDE_DEFENCE,SIDE_DEFENCE,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

