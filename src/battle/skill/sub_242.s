
//============================================================================
/**
 *
 *@file		sub_242.s
 *@brief	�퓬�V�[�P���X
 *			�ł񂶂ӂ䂤�I��������b�Z�[�W�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.05.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_242:
	MESSAGE		DenzihuyuuEndMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	//�ł񂶂ӂ䂤�t���O�𗎂Ƃ�
	PSP_VALUE	VAL_NBIT,SIDE_WORK,ID_PSP_waza_kouka,WAZAKOUKA_DENZIHUYUU
	SEQ_END
