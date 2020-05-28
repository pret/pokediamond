
//============================================================================
/**
 *
 *@file		sub_114.s
 *@brief	戦闘シーケンス
 *			バトンタッチシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_114:
	RESHUFFLE_CHECK		SIDE_ATTACK,POKE_LIST_ON,Umakukimaran
	GOSUB				SUB_SEQ_WAZA_OUT_EFF
	//特性しぜんかいふくをもっていたら、状態異常を直す
	SIZENKAIHUKU_CHECK	SIDE_ATTACK,SUB_114_NEXT
	PSP_VALUE			VAL_SET,SIDE_ATTACK,ID_PSP_condition,0
SUB_114_NEXT:
	POKEMON_DELETE		SIDE_ATTACK
	SERVER_WAIT
	HP_GAUGE_OUT		SIDE_ATTACK
	SERVER_WAIT
	VALUE_WORK			VAL_SET,BUF_PARA_RESHUFFLE_CLIENT,BUF_PARA_ATTACK_CLIENT
//	VALUE				VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_BATON_TOUCH|SERVER_STATUS_FLAG_NO_WAZANO_SET
	VALUE				VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_BATON_TOUCH
	JUMP				SUB_SEQ_POKEMON_LIST

Umakukimaran:
	VALUE				VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
