
//============================================================================
/**
 *
 *@file		sub_036.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			���܂񒆃V�[�P���X
 *
 *@author	HisashiSogabe
 *@data		2005.12.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_036:
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_GAMAN,SeqGamaning

//���܂񂪂Ƃ��ꂽ
SeqGamanOff:
	MESSAGE			GamanOverMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//�Z�G�t�F�N�g��ς��邽�߂ɃJ�E���g���P��
	VALUE			VAL_SET,BUF_PARA_WAZA_EFF_CNT,1
	//���߃t���O�𗎂Ƃ�
	PSP_VALUE		VAL_NBIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP
	//���ߔ����t���O���Z�b�g
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_AFTER
	//�_���[�W���[�N���O�̎��́A���܂񎸔s
	IF				IF_FLAG_EQ,BUF_PARA_DAMAGE,0,SeqGamanFaild
	SEQ_END

SeqGamanFaild:
	GOSUB			SUB_SEQ_UMAKUKIMARAN
	//�Z�̋N���Ɏ��s�t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	SEQ_END

//���܂�
SeqGamaning:
	MESSAGE			GamanMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
SeqGamanRet:
	SEQ_END

