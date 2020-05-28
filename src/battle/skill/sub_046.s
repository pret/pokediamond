
//============================================================================
/**
 *
 *@file		sub_046.s
 *@brief	戦闘シーケンス
 *			じこさいせいシーケンス
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_046:
	ATTACK_MESSAGE
	SERVER_WAIT
	//HPMAXを読み込み
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_hpmax,BUF_PARA_HP_CALC_WORK
	//HPMAXを半分に
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,2
	//HP操作対象をAttackClientに
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	GOSUB			SUB_SEQ_KAIFUKU
	SEQ_END
