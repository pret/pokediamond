//============================================================================
/**
 *
 *@file		be_170.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			170　後攻技　ターンの最初に「○○○○○は　しゅうちゅうりょくを　たかめている！」のメッセージが出て、
 *				 技が出るまでの間、相手が攻撃技を自分にヒットさせたら、ひるんで技が出せなくなる
 *
 *@author	HisashiSogabe
 *@data		2006.02.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_170:
	IF				IF_FLAG_NE,BUF_PARA_BUTSURI_DAMAGE_ATTACK,0,BE_170_NG
	IF				IF_FLAG_NE,BUF_PARA_TOKUSYU_DAMAGE_ATTACK,0,BE_170_NG
	VALUE			VAL_SET,BUF_PARA_WAZA_EFF_CNT,1
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END

BE_170_NG:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_WAZA_KOYUU_NOHIT
	MESSAGE_PARAM	KiaiPunchNoMineMsg,TAG_NICK,SIDE_ATTACK
	SEQ_END
