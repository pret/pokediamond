//============================================================================
/**
 *
 *@file		be_165.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			165�@���肪�����Z���Q�x�����ďo���Ȃ���Ԃɂ���u�����������́@�����������@����ꂽ�I�v
 *				�i��シ��܂Ō��ʂ͑����j�����Z��I�ڂ��Ƃ���ƁA
 *				�u���������@����ꂽ�̂Ł@�Â��ā@���Ȃ��@�킴���@�����Ȃ��I�v�ƂȂ��đI�ׂȂ�
 *
 *@author	HisashiSogabe
 *@data		2006.02.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_165:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_ICHAMON|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END
