//============================================================================
/**
 *
 *@file		be_239.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			239�@����̓����𖳌��ɂ���B�K�����s���������p�ӂ���K�v�����邩���B
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_239:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_IEKI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END
