
//============================================================================
/**
 *
 *@file		sub_089.s
 *@brief	�퓬�V�[�P���X
 *			�݂����V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_089:
	ATTACK_MESSAGE
	SERVER_WAIT
	//���łɂ݂���肪�łĂ���ꍇ�́A���s
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_MIGAWARI,MigawariAlready
	MIGAWARI		MigawariNG
//	WAZA_EFFECT		SIDE_ATTACK
	STATUS_EFFECT	SIDE_ATTACK,STATUS_ACTION_DOLL_ON
	SERVER_WAIT
	//�݂����t���O�𗧂Ă�
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_MIGAWARI
	//�_���[�W�G�t�F�N�g�œ_�ł��Ȃ��t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//HP����Ώۂ�AttackClient��
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			MigawariMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

MigawariNG:
	WAIT			MSG_WAIT
	MESSAGE			MigawariNGMsg,TAG_NONE
	BRANCH			SUB_089_END
MigawariAlready:
	WAIT			MSG_WAIT
	MESSAGE			AlreadyMigawariMineMsg,TAG_NICK,SIDE_ATTACK
SUB_089_END:
	SERVER_WAIT
	WAIT			MSG_WAIT
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	SEQ_END
