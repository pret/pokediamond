
//============================================================================
/**
 *
 *@file		sub_169.s
 *@brief	�퓬�V�[�P���X
 *			�Z���ʂ�HP�񕜃V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_169:
	MESSAGE			AquaRingRecoverMineMsg,TAG_NICK_WAZA,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//�_���[�W�G�t�F�N�g�œ_�ł��Ȃ��t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//�������ʂŋz�����n�̈З̓A�b�v�́A�З̓A�b�v
	SOUBI_CHECK		SOUBI_NO_HAVE,SIDE_WORK,SOUBI_KYUSYUURYOKUUP,SUB_169_NEXT
	SOUBI_ATK_GET	SIDE_WORK,BUF_PARA_CALC_WORK
	VALUE			VAL_ADD,BUF_PARA_CALC_WORK,100
	VALUE_WORK		VAL_MUL,BUF_PARA_HP_CALC_WORK,BUF_PARA_CALC_WORK
	VALUE			VAL_DIV,BUF_PARA_HP_CALC_WORK,100
SUB_169_NEXT:
	STATUS_EFFECT	SIDE_WORK,STATUS_EFF_RECOVER
	SERVER_WAIT
	//HP�v�Z�T�u���[�`����
	GOSUB			SUB_SEQ_HP_CALC
	SEQ_END

