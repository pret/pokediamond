
//============================================================================
/**
 *
 *@file		sub_002.s
 *@brief	�퓬�V�[�P���X
 *			�|�P����HP�v�Z�V�[�P���X
 *@author	HisashiSogabe
 *@data		2005.07.29
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_002:
	//�u�����N�G�t�F�N�g���邩���Ȃ����`�F�b�N
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK,NoBlinkEffect
	WAZAKOUKA_SE	SIDE_WORK
	POKEMON_BLINK	SIDE_WORK
	SERVER_WAIT
	//���Q�̈З͂���߂鑕�����ʂ̃`�F�b�N
	GOSUB			SUB_SEQ_SOUBI_BATSUGUN_DOWN_CHECK
NoBlinkEffect:
	//�t���O�͗��Ƃ��Ă���
	VALUE			VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	HP_GAUGE_CALC	SIDE_WORK
	SERVER_WAIT
	HP_CALC			SIDE_WORK
	KIZETSU_CHECK	SIDE_WORK
	//�_���[�W�́A���߂������[�N�Ɋi�[
	IF				IF_FLAG_C,BUF_PARA_HP_CALC_WORK,0,SUB_002_END
	VALUE_WORK		VAL_SET,BUF_PARA_DAMEOSHI_DAMAGE,BUF_PARA_HP_CALC_WORK
SUB_002_END:
	SEQ_END
