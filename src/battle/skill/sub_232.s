
//============================================================================
/**
 *
 *@file		sub_232.s
 *@brief	�퓬�V�[�P���X
 *			�������p���`�����肾���O�̃��b�Z�[�W�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.05.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_232:
	VALUE			VAL_SET,BUF_PARA_WAZA_WORK,WAZANO_KIAIPANTI
	WAZA_EFFECT2	SIDE_WORK,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	MESSAGE			KiaiPunchMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//���ɋZ�G�t�F�N�g���o��悤�Ƀt���O�𗎂Ƃ��Ă���
	VALUE			VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_WAZA_EFFECT
	SEQ_END
