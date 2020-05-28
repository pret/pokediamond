//============================================================================
/**
 *
 *@file		be_215.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			215　５ターンの間、全てのポケモンが空中に浮くことができなくなる。
 *				 特性【ふゆう】、タイプ【ひこう】が１倍で当たる。
 *				 上空に飛んで攻撃するの技【そらをとぶ、うかぶ、とびはねる、でんじふゆう】が使えない。
 *				 とんでいるポケモンは落ちる。
 *
 *@author	HisashiSogabe
 *@data		2006.02.13
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_215:
	//すでにじゅうりょく状態なら、うまくきまらん
	IF			IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_JUURYOKU,Umakukimaran
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_JUURYOKU|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
