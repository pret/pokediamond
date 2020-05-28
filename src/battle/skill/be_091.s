//============================================================================
/**
 *
 *@file		be_091.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			091　敵のＨＰと自分のＨＰを足して、それを半分にしてそれぞれに分ける
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_091:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_ITAMIWAKE|ADD_STATUS_WAZAKOUKA
	SEQ_END
