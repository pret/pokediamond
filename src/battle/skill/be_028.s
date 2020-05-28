//============================================================================
/**
 *
 *@file		be_028.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			028　エンカウント戦闘時は強制的に戦闘を終了させる、
 *				 トレーナー戦で使用するとポケモンを強制的に入れ替えさせる（敵に交換するポケモンがいない場合、技は失敗する）
 *
 *@author	HisashiSogabe
 *@data		2006.01.26
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_028:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HUKITOBASI|ADD_STATUS_WAZAKOUKA
	SEQ_END
