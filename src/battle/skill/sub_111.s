
//============================================================================
/**
 *
 *@file		sub_111.s
 *@brief	�퓬�V�[�P���X
 *			HP�񕜃V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.31
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_111:
	//HPMAX��ǂݍ���
	PSP_VALUE_WORK	VAL_GET,SIDE_WORK,ID_PSP_hpmax,BUF_PARA_CALC_WORK
	//HP���܂񂽂�̎��́A���̎|�̃��b�Z�[�W��\��
	IF_PSP_WORK		IF_FLAG_EQ,SIDE_WORK,ID_PSP_hp,BUF_PARA_CALC_WORK,HP_MANTAN
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	//�_���[�W�G�t�F�N�g�œ_�ł��Ȃ��t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//HP�v�Z�T�u���[�`����
	IF				IF_FLAG_NBIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_KAIFUKU_EFFECT,NoEffect
	STATUS_EFFECT	SIDE_WORK,STATUS_EFF_RECOVER
	SERVER_WAIT
NoEffect:
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			JikosaiseiMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

HP_MANTAN:
	WAIT			MSG_WAIT
	MESSAGE			MantanMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//�Z�̋N���Ɏ��s�t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	SEQ_END
