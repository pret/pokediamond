//============================================================================
/**
 *
 *@file		be_122.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			122�@���ʂ��m���ŕς��B�S�O��=�S�O�̈З́A�R�O��=�W�O�̈З́A�P�O��=�P�Q�O�̈З́A�Q�O��=�G1/4�񕜁B
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_122:
	PRESENT			HPKaifuku
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END

HPKaifuku:
	//HP����Ώۂ�DefenceClient��
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_DEFENCE_CLIENT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_PRESENT|ADD_STATUS_WAZAKOUKA
	//�������Ȃ��^�C�v�ł��񕜂���悤�ɁA�������ɂ���
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_NONE
	//�Z�G�t�F�N�g���񕜗p�ɕς���
	VALUE			VAL_SET,BUF_PARA_WAZA_EFF_CNT,1
	SEQ_END
	
