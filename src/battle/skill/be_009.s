//============================================================================
/**
 *
 *@file		be_009.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			009�@�G���g�����Z�Ɠ����Z���o��
 *
 *@author	HisashiSogabe
 *@data		2005.12.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_009:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	//�I�E���Ԃ����[�N���`�F�b�N���āA�Ԃ���Ƃ��͂��̋Z�̃V�[�P���X�փW�����v
	OUMU_CHECK
OumuSippai:
	MESSAGE			OumuNGMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	//�Z�̋N���Ɏ��s�t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	SEQ_END
