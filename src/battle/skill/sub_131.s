
//============================================================================
/**
 *
 *@file		sub_131.s
 *@brief	�퓬�V�[�P���X
 *			���イ�ł�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_131:
	PSP_VALUE	VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_JUUDEN
	PSP_VALUE	VAL_SET,SIDE_ATTACK,ID_PSP_wkw_juuden_count,2
	MESSAGE		JuudenMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT		MSG_WAIT
	//AttackClient��ǉ��Ώۂ�
	VALUE_WORK	VAL_SET,BUF_PARA_TSUIKA_CLIENT,BUF_PARA_ATTACK_CLIENT
	//���h��1�i�K�グ����Z�b�g
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_SPEDEFUP
	GOSUB		SUB_SEQ_ABICNT_CALC
	SEQ_END
