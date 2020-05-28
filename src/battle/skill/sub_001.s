
//============================================================================
/**
 *
 *@file		sub_001.s
 *@brief	戦闘シーケンス
 *			技発動シーケンス
 *@author	HisashiSogabe
 *@data		2005.07.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_001:
//直接追加の場合、追加効果シーケンスでメッセージや技エフェクトを出すのでここでは出さない
	IF			IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,NoWazaEffect
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
NoWazaEffect:
	SEQ_END
