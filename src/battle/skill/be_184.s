//============================================================================
/**
 *
 *@file		be_184.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			184�@��x�g�����������̂�������x�g�����Ƃ��ł���B
 *
 *@author	HisashiSogabe
 *@data		2006.02.08
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_184:
	//�A�C�e���������Ă���Ƃ��́A���܂����܂��
	IF_PSP			IF_FLAG_NE,SIDE_ATTACK,ID_PSP_item,0,Umakukimaran
	//���T�C�N���̃��[�N������ۂ̎��́A���܂����܂��
	RECYCLE			Umakukimaran
	PSP_VALUE_WORK	VAL_SET,SIDE_ATTACK,ID_PSP_item,BUF_PARA_ITEM_WORK
	MESSAGE_PARAM	RecycleMineMsg,TAG_NICK_ITEM,SIDE_ATTACK,SIDE_WORK
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
