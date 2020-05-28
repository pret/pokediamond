//============================================================================
/**
 *
 *@file		be_000.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			153　エンカウント戦闘時は強制的に戦闘を終了させる
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_153:
	//野生戦のみ起動
	IF			IF_FLAG_BIT,BUF_PARA_FIGHT_TYPE,FIGHT_TYPE_TRAINER,Umakukimaran
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_TELEPORT|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
