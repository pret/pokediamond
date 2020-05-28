//============================================================================
/**
 *
 *@file		be_265.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			265　異性の場合、特攻を２段階下げる
 *
 *@author	HisashiSogabe
 *@data		2006.05.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_265:
	//特性どんかんにはきかない
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_DEFENCE,TOKUSYU_DONKAN,TokuseiUmakukimaran
	IF_PSP						IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_sex,PARA_UNK,Umakukimaran
	IF_PSP						IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_sex,PARA_UNK,Umakukimaran
	PSP_VALUE_WORK				VAL_GET,SIDE_DEFENCE,ID_PSP_sex,BUF_PARA_CALC_WORK
	IF_PSP_WORK					IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_sex,BUF_PARA_CALC_WORK,Umakukimaran
	VALUE						VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SPEPOWDOWN2|ADD_STATUS_DEFENCE
	SEQ_END

Umakukimaran:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT/2
	MESSAGE			KimaranMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	SEQ_END

TokuseiUmakukimaran:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT/2
	MESSAGE			TokuseiNoWazaMineMsg,TAG_NICK_TOKU_WAZA,SIDE_DEFENCE,SIDE_DEFENCE,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	SEQ_END

