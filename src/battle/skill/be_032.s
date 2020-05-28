//============================================================================
/**
 *
 *@file		be_032.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			032　ＨＰを最大値の半分の値だけ回復する
 *
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_032:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_JIKOSAISEI|ADD_STATUS_WAZAKOUKA
	SEQ_END
