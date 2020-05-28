//============================================================================
/**
 *
 *@file		be_252.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			252�@�T�^�[���̊ԁA���ɕ����y�ӂ䂤�z��ԂɂȂ�B�n�ʋZ��������Ȃ��Ȃ�B
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_252:
	IF_PSP			IF_FLAG_NE,SIDE_ATTACK,ID_PSP_wkw_denzihuyuu_count,0,Umakukimaran
	//�����ӂ䂤�́A���܂����܂��
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_HUYUU,Umakukimaran
	//�˂��͂钆�́A���܂����܂��
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_NEWOHARU,Umakukimaran
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_DENZIHUYUU
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_wkw_denzihuyuu_count,DENZIHUYUU_COUNT
	MESSAGE_PARAM	DenzihuyuuMineMsg,TAG_NICK,SIDE_ATTACK
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
