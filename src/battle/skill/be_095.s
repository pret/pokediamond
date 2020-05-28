//============================================================================
/**
 *
 *@file		be_095.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			095　敵が最後に使用した技をコピーする（コピーした技のＰＰは基本値）、
 *				 コピーした技は戦闘終了後も残りスケッチの技がなくなる
 *
 *@author	HisashiSogabe
 *@data		2006.01.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_095:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SKETCH|ADD_STATUS_WAZAKOUKA
	SEQ_END
