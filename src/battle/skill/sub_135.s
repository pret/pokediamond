
//============================================================================
/**
 *
 *@file		sub_135.s
 *@brief	�퓬�V�[�P���X
 *			�Ȃ肫��V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_135:
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran
	//�����ӂ����Ȃ܂���́A���܂����܂��
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_speabino,TOKUSYU_HUSIGINAMAMORI,Umakukimaran
	//�����}���`�^�C�v�́A���܂����܂��
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_speabino,TOKUSYU_MARUTITAIPU,Umakukimaran
	//�����}���`�^�C�v�́A���܂����܂��
	IF_PSP			IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_speabino,TOKUSYU_MARUTITAIPU,Umakukimaran
	//�����������Ă��Ȃ��ꍇ�́A���܂����܂��
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_speabino,0,Umakukimaran

	GOSUB			SUB_SEQ_WAZA_OUT_EFF

	//�Ȃ܂��r�b�g��������
	VALUE_WORK		VAL_SET,BUF_PARA_TEMP_WORK,BUF_PARA_TOTAL_TURN
	//���̃^�[���Ȃ܂������邽�߂ɁA�C���N�������g�͂Ȃ�
//	VALUE			VAL_ADD,BUF_PARA_TEMP_WORK,1
	VALUE			VAL_AND,BUF_PARA_TEMP_WORK,1
	PSP_VALUE_WORK	VAL_SET,SIDE_ATTACK,ID_PSP_wkw_namake_bit,BUF_PARA_TEMP_WORK

	PSP_VALUE_WORK	VAL_GET,SIDE_DEFENCE,ID_PSP_speabino,BUF_PARA_TEMP_WORK
	PSP_VALUE_WORK	VAL_SET,SIDE_ATTACK,ID_PSP_speabino,BUF_PARA_TEMP_WORK

	IF				IF_FLAG_NE,BUF_PARA_TEMP_WORK,TOKUSYU_SUROOSUTAATO,Message
	//�Ȃ肫�����������X���[�X�^�[�g�̏ꍇ�́A�J�E���^�����Z�b�g
	VALUE_WORK		VAL_SET,BUF_PARA_TEMP_WORK,BUF_PARA_TOTAL_TURN
	VALUE			VAL_ADD,BUF_PARA_TEMP_WORK,1
	PSP_VALUE_WORK	VAL_SET,SIDE_ATTACK,ID_PSP_wkw_slow_start_count,BUF_PARA_TEMP_WORK
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_slow_start_flag,0
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_slow_start_end_flag,0

Message:
	MESSAGE			NarikiriM2MMsg,TAG_NICK_NICK_TOKU,SIDE_ATTACK,SIDE_DEFENCE,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
