//============================================================================
/**
 *
 *@file		be_148.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			148�@�Q�^�[����ɓG���U������
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_148:
	MIRAIYOCHI	Umakukimaran
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	//���������͂����Ă���̂ŁA�K��������悤�Ƀt���O�𗧂Ă�
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_NONE|SERVER_STATUS_FLAG_OTHER_HIT_CALC|SERVER_STATUS_FLAG_KIE_HIT
	SEQ_END

Umakukimaran:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	GOSUB			SUB_SEQ_UMAKUKIMARAN
	SEQ_END
