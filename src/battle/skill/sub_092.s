
//============================================================================
/**
 *
 *@file		sub_092.s
 *@brief	�퓬�V�[�P���X
 *			�ւ񂵂�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.26
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_092:
	//�����Ă��鑊��ł́A���܂����܂��i���b�N�I�����Ă��Ă��O���j
	IF_PSP		IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_KIE,Umakukimaran
	//�ւ񂵂񂵂Ă��鑊��́A���܂����܂��
	IF_PSP		IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_HENSHIN,Umakukimaran
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
	HENSIN
	MESSAGE		HenshinMineMsg,TAG_NICK_POKE,SIDE_ATTACK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
