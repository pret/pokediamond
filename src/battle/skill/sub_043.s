
//============================================================================
/**
 *
 *@file		sub_043.s
 *@brief	�퓬�V�[�P���X
 *			��邠���������V�[�P���X
 *@author	HisashiSogabe
 *@data		2005.12.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_043:
	//HP����Ώۂ�AttackClient��
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	//HPMAX���擾
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_hpmax,BUF_PARA_HP_CALC_WORK
	//�l���S���̂P��
	VALUE			VAL_MUL,BUF_PARA_HP_CALC_WORK,-1
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,4
	//�_���[�W�G�t�F�N�g�œ_�ł��Ȃ��t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			HanekaeriMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
