//============================================================================
/**
 *
 *@file		be_236.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			236�@�T�^�[���̊ԁA�Ώۑ��肪�Z�ŉ񕜂ł��Ȃ���ԂɂȂ�B
 *				�y�������������z�y�˂ނ�z�y��ǂ肬�̂��ˁz�ȂǑS�Ẳ񕜌n�ɂ����B
 *
 *@author	HisashiSogabe
 *@data		2006.02.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_236:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HEALBLOCK|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END
