
//============================================================================
/**
 *
 *@file		sub_243.s
 *@brief	�퓬�V�[�P���X
 *			�q�[���u���b�N�I��������b�Z�[�W�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.05.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_243:
	VALUE		VAL_SET,BUF_PARA_WAZA_WORK,WAZANO_KAIHUKUHUUZI
	MESSAGE		HealblockEndMineMsg,TAG_NICK_WAZA,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	//�q�[���u���b�N�t���O�𗎂Ƃ�
	PSP_VALUE	VAL_NBIT,SIDE_WORK,ID_PSP_waza_kouka,WAZAKOUKA_HEALBLOCK
	SEQ_END
