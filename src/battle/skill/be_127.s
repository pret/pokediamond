//============================================================================
/**
 *
 *@file		be_127.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			127　味方のポケモンと交代する、交代する時に今までかかっていた補助効果をそのまま受け継がせる事が出来る
 *				（交換するポケモンがいない場合、技は失敗する）
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_127:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_BATONTOUCH|ADD_STATUS_WAZAKOUKA
	SEQ_END
