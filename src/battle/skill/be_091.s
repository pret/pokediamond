//============================================================================
/**
 *
 *@file		be_091.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			091�@�G�̂g�o�Ǝ����̂g�o�𑫂��āA����𔼕��ɂ��Ă��ꂼ��ɕ�����
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_091:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_ITAMIWAKE|ADD_STATUS_WAZAKOUKA
	SEQ_END
