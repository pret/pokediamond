
//============================================================================
/**
 *
 *@file		sub_244.s
 *@brief	�퓬�V�[�P���X
 *			�V���b�g�A�E�g�I��������b�Z�[�W�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.05.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_244:
	MESSAGE		ShutoutEndMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	//�V���b�g�A�E�g�t���O�𗎂Ƃ�
	PSP_VALUE	VAL_NBIT,SIDE_WORK,ID_PSP_waza_kouka,WAZAKOUKA_SHUTOUT
	SEQ_END
