//============================================================================
/**
 *
 *@file		be_181.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			181�@���^�[���`�F�b�N�ɂP�^�P�U�Â񕜁B�|�P��������ւ����ł��Ȃ��Ȃ�B�ق���Ȃǂ������Ȃ��Ȃ�
 *
 *@author	HisashiSogabe
 *@data		2006.02.08
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_181:
	//���łɂ˂��͂��Ă���ꍇ�́A���܂����܂��
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_NEWOHARU,Umakukimaran
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_NEWOHARU
	MESSAGE_PARAM	NewoharuMineMsg,TAG_NICK,SIDE_ATTACK
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
