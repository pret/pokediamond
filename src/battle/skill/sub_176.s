
//============================================================================
/**
 *
 *@file		sub_176.s
 *@brief	�퓬�V�[�P���X
 *			������Ȃ��������b�Z�[�W���o��

 *@author	HisashiSogabe
 *@data		2006.07.11
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_176:
	MESSAGE			DoubleNoHitMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	//WazaStatusMessage�𖳌��ɂ��邽�߂ɂ��̃t���O�𗧂Ă�
	//VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI_RENZOKU_CHECK
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	SEQ_END
