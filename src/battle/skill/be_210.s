//============================================================================
/**
 *
 *@file		be_210.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			210�@���^�C�v�̋Z�̈З͂��Z���g�p�����|�P���������邩���蔼���ɂȂ�
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_210:
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_MIZUASOBI,Umakukimaran
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_MIZUASOBI
	MESSAGE_PARAM	MizuasobiMsg,TAG_NONE
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
