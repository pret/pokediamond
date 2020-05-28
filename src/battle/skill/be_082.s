//============================================================================
/**
 *
 *@file		be_082.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			082　敵が最後に使った技を、その戦闘中だけコピーして使える（コピー技のＰＰは５）、敵が技を使う前に使うと技は失敗する
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_082:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_MONOMANE|ADD_STATUS_WAZAKOUKA
	SEQ_END
