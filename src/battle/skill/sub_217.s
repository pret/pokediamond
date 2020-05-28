
//============================================================================
/**
 *
 *@file		sub_217.s
 *@brief	�퓬�V�[�P���X
 *			2�^�[���Z��1�^�[���ł��������A�C�e�����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.03.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_217:
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	//�Z�G�t�F�N�g�I�t���̂��߂ɏ�����n�̃`�F�b�N�����Ďp������
	IF_PSP			IF_FLAG_NBIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_KIE,NoVanish
	VANISH_ON_OFF	SIDE_ATTACK,SW_VANISH_ON
NoVanish:
	MESSAGE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	STATUS_EFFECT	SIDE_ATTACK,STATUS_ITEM_POKE
	SERVER_WAIT
	MESSAGE			Item1turnMineMsg,TAG_NICK_ITEM,SIDE_ATTACK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	KILL_ITEM		SIDE_ATTACK
	VALUE			VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_WAZA_EFFECT
	SEQ_END
