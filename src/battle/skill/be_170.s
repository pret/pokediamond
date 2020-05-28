//============================================================================
/**
 *
 *@file		be_170.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			170�@��U�Z�@�^�[���̍ŏ��Ɂu�����������́@���イ���イ��傭���@�����߂Ă���I�v�̃��b�Z�[�W���o�āA
 *				 �Z���o��܂ł̊ԁA���肪�U���Z�������Ƀq�b�g��������A�Ђ��ŋZ���o���Ȃ��Ȃ�
 *
 *@author	HisashiSogabe
 *@data		2006.02.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_170:
	IF				IF_FLAG_NE,BUF_PARA_BUTSURI_DAMAGE_ATTACK,0,BE_170_NG
	IF				IF_FLAG_NE,BUF_PARA_TOKUSYU_DAMAGE_ATTACK,0,BE_170_NG
	VALUE			VAL_SET,BUF_PARA_WAZA_EFF_CNT,1
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END

BE_170_NG:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_WAZA_KOYUU_NOHIT
	MESSAGE_PARAM	KiaiPunchNoMineMsg,TAG_NICK,SIDE_ATTACK
	SEQ_END
