//============================================================================
/**
 *
 *@file		be_045.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			045�@�U�����O���Ɨ^����͂��������_���[�W��2���̂P���������󂯂�
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_045:
	//�������Ắ݂A�����_���[�W�n���󂯂�Z�̈З͂�2����������
	TOKUSEI_CHECK	TOKUSEI_NO_HAVE,SIDE_ATTACK,TOKUSYU_SUTEMI,BE_045_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,12
BE_045_NEXT:
	//�Z���O�ꂽ���Ƀy�i���e�B���ۂ��t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NOHIT_PENALTY
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
