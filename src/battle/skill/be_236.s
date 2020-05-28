//============================================================================
/**
 *
 *@file		be_236.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			236　５ターンの間、対象相手が技で回復できない状態になる。
 *				【じこさいせい】【ねむる】【やどりぎのたね】など全ての回復系にきく。
 *
 *@author	HisashiSogabe
 *@data		2006.02.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_236:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HEALBLOCK|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END
