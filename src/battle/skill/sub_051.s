
//============================================================================
/**
 *
 *@file		sub_051.s
 *@brief	�퓬�V�[�P���X
 *			���΂ꂽ��̂�����ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_051:
	//�Z���ʂɂ��ǉ����ʃt���O��ݒ�
	VALUE		VAL_SET,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_WAZA_KOUKA
	//������ǉ��V�[�P���X���R�[��
	GOSUB		SUB_SEQ_KONRAN
	//�����񂵂Ă��Ȃ�������A���b�Z�[�W�\�����Ȃ�
	IF_PSP		IF_FLAG_NBIT,SIDE_TSUIKA,ID_PSP_condition2,CONDITION2_KONRAN,SUB_051_END
	MESSAGE		AbareruEndMineMsg,TAG_NICK,SIDE_TSUIKA
	SERVER_WAIT
	WAIT		MSG_WAIT
SUB_051_END:
	SEQ_END
