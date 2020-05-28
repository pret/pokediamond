//============================================================================
/**
 *
 *@file		be_007.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			007�@�g�p������A�퓬�s�\�ɂȂ�
 *
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_007:
	//�������߂肯�����鎞�́A���΂����s
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ALL,TOKUSYU_SIMERIKE,TokusyuNoJibaku

	//�����̏�����������������́AJibakuStart�փW�����v
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_JIBAKU_MASK,JibakuStart
//�����̏���������
	VALUE			VAL_SET,BUF_PARA_CALC_WORK,SERVER_STATUS_FLAG_JIBAKU
	VALUE_WORK		VAL_LSH,BUF_PARA_CALC_WORK,BUF_PARA_ATTACK_CLIENT
	VALUE_WORK		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,BUF_PARA_CALC_WORK
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_hp,0
	//�Q�[�W��0�ɂ��鏈��
	VALUE			VAL_SET,BUF_PARA_HP_CALC_WORK,JIBAKU_HP
	HP_GAUGE_CALC	SIDE_ATTACK
	SERVER_WAIT
	GOSUB			SUB_SEQ_WAZA_OUT_EFF
JibakuStart:	
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
TokusyuNoJibaku:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	MESSAGE			ShimerikeM2MMsg,TAG_NICK_TOKU_NICK_WAZA,SIDE_TOKUSEI,SIDE_TOKUSEI,SIDE_ATTACK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//�����̃`�F�b�N�����Ȃ��t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_DOUBLE_CHECK
	//�Z�̋N���Ɏ��s�t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	SEQ_END
