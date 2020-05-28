
//============================================================================
/**
 *
 *@file		sub_026.s
 *@brief	戦闘シーケンス
 *			やけどによるダメージシーケンス
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_026:
	//特性マジックガードは、ダメージなし
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_WORK,TOKUSYU_MAZIKKUGAADO,SUB_026_END
	PSP_VALUE_WORK	VAL_GET,SIDE_WORK,ID_PSP_hpmax,BUF_PARA_HP_CALC_WORK
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,8 
	//特性たいねつは、ダメージを1/16に
	TOKUSEI_CHECK	TOKUSEI_NO_HAVE,SIDE_WORK,TOKUSYU_TAINETU,SUB_026_NEXT
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,2 
SUB_026_NEXT:
	VALUE			VAL_MUL,BUF_PARA_HP_CALC_WORK,-1 
	MESSAGE			YakedoDamageMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	STATUS_EFFECT	SIDE_WORK,STATUS_YAKEDO
	SERVER_WAIT
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	JUMP			SUB_SEQ_HP_CALC
SUB_026_END:
	SEQ_END
