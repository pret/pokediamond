//============================================================================
/**
 *
 *@file		be_132.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			132�@�g�o���񕜂��邪���ʂ͓V�C�ŕς��A���{����=�Q�^�R�A�ʏ�=�P�^�Q�A�J�A�����A�����=�P�^�S
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_132:
	WEATHER_KAIFUKU
	//HP����Ώۂ�AttackClient��
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	//�v���[���g�̉񕜓���Ɠ����Ȃ̂ŁA�v���[���g�̒ǉ����ʈ����ɂ���
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_PRESENT|ADD_STATUS_WAZAKOUKA
	//�񕜃G�t�F�N�g���o��悤�Ƀt���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_KAIFUKU_EFFECT
	SEQ_END
