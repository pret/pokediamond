
//============================================================================
/**
 *
 *@file		sub_276.s
 *@brief	戦闘シーケンス
 *			経験値取得シーケンス
 *@author	HisashiSogabe
 *@data		2006.06.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_276:
	GET_EXP_CHECK	NoExpGet		//経験値ゲット処理がないときのとび先を指定
GetExpLoop:
	GET_EXP_INIT
	GET_EXP
	GET_EXP_LOOP	GetExpLoop		//経験値ゲット処理を繰り返すときのとび先を指定
NoExpGet:
	SEQ_END
