
//============================================================================
/**
 *
 *@file		sub_154.s
 *@brief	戦闘シーケンス
 *			はねやすめシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.10
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_154:
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_hpmax,BUF_PARA_HP_CALC_WORK
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,2
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	ATTACK_MESSAGE
	SERVER_WAIT
	GOSUB			SUB_SEQ_KAIFUKU
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI,SUB_154_END
	OTF_SET			SIDE_ATTACK,OTF_haneyasume_flag,1
SUB_154_END:
	SEQ_END
