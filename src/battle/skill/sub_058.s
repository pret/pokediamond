
//============================================================================
/**
 *
 *@file		sub_058.s
 *@brief	�퓬�V�[�P���X
 *			���߂��n�ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_058:
	//�݂���肪����ꍇ�́A�Ȃɂ����Ȃ�
	MIGAWARI_CHECK	SIDE_TSUIKA,SUB_058_END
	//���łɒ��ߕt�����Ă��鎞�́A�Ȃɂ����Ȃ�
	IF_PSP			IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_SHIME,SUB_058_END
	MESSAGE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//�Q�`�T�^�[���̗������擾
	RANDOM_GET		3,3
	//�������ʂł܂����n�̃J�E���^�A�b�v�́A�J�E���^���ő�ɂ���
	SOUBI_CHECK		SOUBI_NO_HAVE,SIDE_ATTACK,SOUBI_MAKITUKUKEIUP,SUB_058_NEXT
	VALUE			VAL_SET,BUF_PARA_CALC_WORK,6
SUB_058_NEXT:
	//���߃J�E���^�ɂȂ�悤�Ƀr�b�g�V�t�g
	VALUE			VAL_LSH,BUF_PARA_CALC_WORK,SHIME_SHIFT
	PSP_VALUE_WORK	VAL_BIT,SIDE_DEFENCE,ID_PSP_condition2,BUF_PARA_CALC_WORK
	//�N�ɂ��߂���ꂽ���A���[�N�Ɋi�[
	PSP_VALUE_WORK	VAL_SET,SIDE_DEFENCE,ID_PSP_wkw_shime_client_no,BUF_PARA_ATTACK_CLIENT
	//���̋Z�ł��߂���ꂽ���A���[�N�Ɋi�[
	PSP_VALUE_WORK	VAL_SET,SIDE_DEFENCE,ID_PSP_wkw_shime_wazano,BUF_PARA_WAZA_NO_NOW
SUB_058_END:
	SEQ_END
