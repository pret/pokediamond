
//============================================================================
/**
 *
 *@file		sub_258.s
 *@brief	�퓬�V�[�P���X
 *			�������Ƃ𕷂����Ɏ������U���V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.05.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_258:
	MESSAGE		IukotowokikanaiMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT		MSG_WAIT
	MESSAGE		KonranMsg2,TAG_NONE
	SERVER_WAIT
	WAIT		MSG_WAIT
	//���ߌn�̃t���O�𗎂Ƃ�
	KEEP_OFF	SIDE_ATTACK
	JUMP		SUB_SEQ_HP_CALC
