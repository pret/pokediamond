//============================================================================
/**
 *
 *@file		be_215.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			215�@�T�^�[���̊ԁA�S�Ẵ|�P�������󒆂ɕ������Ƃ��ł��Ȃ��Ȃ�B
 *				 �����y�ӂ䂤�z�A�^�C�v�y�Ђ����z���P�{�œ�����B
 *				 ���ɔ��ōU������̋Z�y������ƂԁA�����ԁA�Ƃт͂˂�A�ł񂶂ӂ䂤�z���g���Ȃ��B
 *				 �Ƃ�ł���|�P�����͗�����B
 *
 *@author	HisashiSogabe
 *@data		2006.02.13
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_215:
	//���łɂ��イ��傭��ԂȂ�A���܂����܂��
	IF			IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_JUURYOKU,Umakukimaran
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_JUURYOKU|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
