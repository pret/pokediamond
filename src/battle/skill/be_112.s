//============================================================================
/**
 *
 *@file		be_112.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			112　まきびしをまいておくと、相手のトレーナーがポケモンを交代する度に相手にダメージを与えることができる
 *				 使う毎に威力が大きくなっていく（３段階まで）
 *
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_112:
	MAKIBISI		Umakukimaran
	MESSAGE_PARAM	MakibishiMineMsg,TAG_NONE_DIR,SIDE_ATTACK_ENEMY
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
