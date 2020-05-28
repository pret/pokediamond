
//============================================================================
/**
 *
 *@file		sub_014.s
 *@brief	�퓬�V�[�P���X
 *			�Ђ�ޒǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2005.11.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_014:
	//�Ώۂ��Z���o���I���Ă�����A�Ђ�܂��Ă��Ӗ����Ȃ��̂ŁA�I��
	WAZA_OUT_CHECK				SIDE_TSUIKA,SUB_014_END
	//�݂���肪����ꍇ�́A�Ђ�܂Ȃ�
	MIGAWARI_CHECK				SIDE_TSUIKA,Umakukimaran
	//�������������傭�́A�Ђ�܂Ȃ�
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_SEISINRYOKU,SEQ_SEISINRYOKU
	//�Ԑڒǉ��̎��́A���Ղ�`�F�b�N������
	IF							IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SEQ_014_NEXT
	//�������Ղ�́A�Ђ�܂Ȃ�
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RINPUN,SUB_014_END
SEQ_014_NEXT:
	PSP_VALUE					VAL_BIT,SIDE_TSUIKA,ID_PSP_condition2,CONDITION2_HIRUMU
SUB_014_END:
	SEQ_END
SEQ_SEISINRYOKU:
	//�˂����܂��́A�Ԑڒǉ��Ȃ̂ŁA�Z�i���o�[�Ŕ��f
	IF							IF_FLAG_EQ,BUF_PARA_WAZA_NO_NOW,WAZANO_NEKODAMASI,SEQ_SEISINRYOKU_MESSAGE
	//���ڒǉ��̎��́A���b�Z�[�W�łЂ�ނ�h�������Ƃ�\��
	IF							IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,SEQ_SEISINRYOKU_END
SEQ_SEISINRYOKU_MESSAGE:
	MESSAGE						SeisinryokuMineMsg,TAG_NICK_TOKU,SIDE_TSUIKA,SIDE_TSUIKA
	SERVER_WAIT
	WAIT						MSG_WAIT
SEQ_SEISINRYOKU_END:
	SEQ_END

Umakukimaran:
	//���ڒǉ��̎��́A���b�Z�[�W�Ŗh�������Ƃ�\��
	IF							IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,Umakukimaran_END
	VALUE						VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
Umakukimaran_END:
	SEQ_END
