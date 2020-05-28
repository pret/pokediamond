//============================================================================
/**
 *
 *@file		be_220.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			220　瀕死になるが、次に出てくるポケモンの体力と状態異常を全回復させる。【おきみやげ】の回復版。
 *				 控えポケモンがいない場合は失敗。
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_220:
	RESHUFFLE_CHECK		SIDE_ATTACK,POKE_LIST_ON,Umakukimaran
	VALUE				VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_IYASINONEGAI|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE				VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
