//============================================================================
/**
 *
 *@file		be_201.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			201�@�d�C�^�C�v�̋Z�̈З͂��Z���g�p�����|�P���������邩���蔼���ɂȂ�
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_201:
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_DOROASOBI,Umakukimaran
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_DOROASOBI
	MESSAGE_PARAM	DoroasobiMsg,TAG_NONE
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
