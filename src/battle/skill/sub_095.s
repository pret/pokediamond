
//============================================================================
/**
 *
 *@file		sub_095.s
 *@brief	�퓬�V�[�P���X
 *			���������Ȃ�ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_095:
	PSP_VALUE	VAL_BIT,SIDE_TSUIKA,ID_PSP_waza_kouka,WAZAKOUKA_CHIISAKUNARU
	//��𗦂�1�i�K�グ����Z�b�g
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_AVOIDUP
	JUMP		SUB_SEQ_ABICNT_CALC
