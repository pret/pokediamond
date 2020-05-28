//============================================================================
/**
 *
 *@file		be_249.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			249　まきびしの毒バージョン。ダメージの代わりに、踏んだポケモンをどく状態にする。
 *				 毒ポケモンを出せば、毒を受けずに消える。１回まくと毒、２回まくと猛毒。まきびしと同時にまくことは可能。
 *
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_249:
	DOKUBISI		Umakukimaran
	MESSAGE_PARAM	DokubisiMineMsg,TAG_NONE_DIR,SIDE_ATTACK_ENEMY
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
