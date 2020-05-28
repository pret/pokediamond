//============================================================================
/**
 *
 *@file		be_045.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			045　攻撃が外れると与えるはずだったダメージの2分の１を自分が受ける
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_045:
	//特性すてみは、反動ダメージ系を受ける技の威力を2割増しする
	TOKUSEI_CHECK	TOKUSEI_NO_HAVE,SIDE_ATTACK,TOKUSYU_SUTEMI,BE_045_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,12
BE_045_NEXT:
	//技が外れた時にペナルティを課すフラグを立てる
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NOHIT_PENALTY
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
