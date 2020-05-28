
//============================================================================
/**
 *
 *@file		sub_016.s
 *@brief	�퓬�V�[�P���X
 *			�N���e�B�J���q�b�g
 *@author	HisashiSogabe
 *@data		2005.11.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_016:
	IF				IF_FLAG_EQ,BUF_PARA_CRITICAL,1,SUB_016_END
	MESSAGE			CriticalMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	//����������̂ڂ́A�U���͂�MAX�܂ŃA�b�v
	TOKUSEI_CHECK	TOKUSEI_NO_HAVE,SIDE_DEFENCE,TOKUSYU_IKARINOTUBO,SUB_016_END
	//HP0�̎��͉������Ȃ�
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_hp,0,SUB_016_END
	//���łɍU���͂�MAX�̎��͉������Ȃ�
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_abiritycnt_pow,12,SUB_016_END
	//�U����MAX
	STATUS_EFFECT	SIDE_DEFENCE,STATUS_EFF_UP
	SERVER_WAIT
	PSP_VALUE		VAL_SET,SIDE_DEFENCE,ID_PSP_abiritycnt_pow,12
	VALUE			VAL_SET,BUF_PARA_MSG_WORK,COND_POW
	MESSAGE			TokuseiStatusMaxUpMineMsg,TAG_NICK_TOKU_STAT,SIDE_DEFENCE,SIDE_DEFENCE,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
SUB_016_END:
	SEQ_END
