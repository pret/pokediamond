
//============================================================================
/**
 *
 *@file		sub_156.s
 *@brief	�퓬�V�[�P���X
 *			���イ��傭�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.13
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_156:
	MESSAGE				JuuryokuMsg,TAG_NONE
	SERVER_WAIT
	WAIT				MSG_WAIT
	VALUE				VAL_BIT,BUF_PARA_FIELD_CONDITION,JUURYOKU_COUNT<<FIELD_JUURYOKU_SHIFT
	VALUE				VAL_SET,BUF_PARA_CLIENT_NO_AGI,0
SUB_156_LOOP:
	CLIENT_NO_GET_AGI	BUF_PARA_CLIENT_WORK
	//HP0�͖���
	IF_PSP				IF_FLAG_EQ,SIDE_WORK,ID_PSP_hp,0,SUB_156_NEXT
	//�ł񂶂ӂ䂤���H
	IF_PSP				IF_FLAG_NE,SIDE_WORK,ID_PSP_wkw_denzihuyuu_count,0,Denzihuyuu
	//������ƂԒ��H
	IF_PSP				IF_FLAG_BIT,SIDE_WORK,ID_PSP_waza_kouka,WAZAKOUKA_SORAWOTOBU,Sorawotobu
	//�����ӂ䂤�H
	//���������͖���
	IF_PSP				IF_FLAG_BIT,SIDE_WORK,ID_PSP_waza_kouka,WAZAKOUKA_IEKI,SUB_156_NEXT
	//�˂��͂钆�͖���
	IF_PSP				IF_FLAG_BIT,SIDE_WORK,ID_PSP_waza_kouka,WAZAKOUKA_NEWOHARU,SUB_156_NEXT
	IF_PSP				IF_FLAG_EQ,SIDE_WORK,ID_PSP_speabino,TOKUSYU_HUYUU,FallMessage
	//�Ђ����^�C�v�����b�Z�[�W
	IF_PSP				IF_FLAG_EQ,SIDE_WORK,ID_PSP_type1,HIKOU_TYPE,FallMessage
	IF_PSP				IF_FLAG_EQ,SIDE_WORK,ID_PSP_type2,HIKOU_TYPE,FallMessage
	BRANCH				SUB_156_NEXT
Denzihuyuu:
	//�ł񂶂ӂ䂤�J�E���g�N���A
	PSP_VALUE			VAL_SET,SIDE_WORK,ID_PSP_wkw_denzihuyuu_count,0
	BRANCH				FallMessage
Sorawotobu:
	KEEP_OFF			SIDE_WORK
	VANISH_ON_OFF		SIDE_WORK,SW_VANISH_OFF
	SERVER_WAIT
FallMessage:
	MESSAGE				JuuryokuFallMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT				MSG_WAIT
SUB_156_NEXT:
	VALUE				VAL_ADD,BUF_PARA_CLIENT_NO_AGI,1
	CLIENT_SET_MAX_LOOP	BUF_PARA_CLIENT_NO_AGI,SUB_156_LOOP
SUB_156_END:
	SEQ_END
