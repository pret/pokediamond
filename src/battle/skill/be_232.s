//============================================================================
/**
 *
 *@file		be_232.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			232�@�|�P�����A�g���[�i�[�i�󂯂��|�P�����ɑ΂��āj����g�p�o���Ȃ��Ȃ�B���ʎ��ԁF�T�^�[���̊�
 *
 *@author	HisashiSogabe
 *@data		2006.03.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_232:
	//�݂���肪����ꍇ�͂��܂����܂��
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SHUTOUT|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
