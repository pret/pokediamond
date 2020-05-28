//============================================================================
/**
 *
 *@file		be_258.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			258　敵の回避率を１段階下げる＋
 *				 相手側のひかりのかべ、リフレクター、しんぴのまもり、しろいきり、まきびし、どくびしの効果をなくす。
 *
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_258:
	VALUE					VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KIRIHARAI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END

