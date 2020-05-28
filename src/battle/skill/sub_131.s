
//============================================================================
/**
 *
 *@file		sub_131.s
 *@brief	戦闘シーケンス
 *			じゅうでんシーケンス
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
	//AttackClientを追加対象に
	VALUE_WORK	VAL_SET,BUF_PARA_TSUIKA_CLIENT,BUF_PARA_ATTACK_CLIENT
	//特防を1段階上げるをセット
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_SPEDEFUP
	GOSUB		SUB_SEQ_ABICNT_CALC
	SEQ_END
