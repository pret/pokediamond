
//============================================================================
/**
 *
 *@file		sub_290.s
 *@brief	�퓬�V�[�P���X
 *			���΂ނŃA�C�e�����Ȃ������`�F�b�N�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.07.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_290:
	//���΂ނ���̔����́A�A�C�e�����Ȃ����������΂�
	IF				IF_FLAG_BIT,BUF_PARA_OSTF_STATUS_FLAG_ATTACK,OSTF_STATUS_FLAG_TSUIBAMU,SUB_290_END
	KILL_ITEM		SIDE_WORK
SUB_290_END:
	VALUE			VAL_NBIT,BUF_PARA_OSTF_STATUS_FLAG_ATTACK,OSTF_STATUS_FLAG_TSUIBAMU
	SEQ_END

