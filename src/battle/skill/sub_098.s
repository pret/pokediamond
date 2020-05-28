
//============================================================================
/**
 *
 *@file		sub_098.s
 *@brief	戦闘シーケンス
 *			のろいによるダメージシーケンス
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_098:
	//特性マジックガードは、ダメージなし
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_WORK,TOKUSYU_MAZIKKUGAADO,SUB_098_END
	STATUS_EFFECT	SIDE_WORK,STATUS_DAMAGE_NOROI
	SERVER_WAIT
	PSP_VALUE_WORK	VAL_GET,SIDE_WORK,ID_PSP_hpmax,BUF_PARA_HP_CALC_WORK
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,4 
	VALUE			VAL_MUL,BUF_PARA_HP_CALC_WORK,-1
	MESSAGE			NoroiMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	JUMP			SUB_SEQ_HP_CALC
SUB_098_END:
	SEQ_END
