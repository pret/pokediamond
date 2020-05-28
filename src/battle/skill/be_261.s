//============================================================================
/**
 *
 *@file		be_261.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			261�@�Q�`�T�^�[���̊ԃ_���[�W��^����B���̊ԁA����͓������Ȃ��{�_�C�r���O���̑����2�{�_���[�W
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_261:
	//�_�C�r���O�����Ă��鑊��ɂ�2�{�_���[�W��^����
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_DAIBINGU_HIT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,10
	IF_PSP			IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_DAIBINGU,BE_261_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,20
BE_261_NEXT:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_SHIME|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_CHECK
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
