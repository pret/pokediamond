//============================================================================
/**
 *
 *@file		be_126.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			126�@�З͂��m���ŕς��A�T��=10�A�P�O��=30�A�Q�O��=50�A�R�O��=70�A�Q�O��=90�A�P�O��=110�A�T��=150�B
 *				�u���Ȃ��ق�v��Ԃ̑���Ɏg�p����Ɣ{�̃_���[�W��^����B
 *
 *@author	HisashiSogabe
 *@data		2006.02.01
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_126:
	//���Ȃ��ق�����Ă��鑊��ɂ�2�{�_���[�W��^����
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_ANAWOHORU_HIT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,10
	IF_PSP			IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_ANAWOHORU,BE_126_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,20
BE_126_NEXT:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_MAGNITUDE|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	MAGNITUDE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
