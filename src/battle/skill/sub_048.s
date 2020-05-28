
//============================================================================
/**
 *
 *@file		sub_048.s
 *@brief	戦闘シーケンス
 *			ねこにこばんの追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_048:
	//攻撃したポケモンのレベルを取得
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_level,BUF_PARA_CALC_WORK
	//その値を5倍に
	VALUE			VAL_MUL,BUF_PARA_CALC_WORK,5
	//敵側は加算しない
	SIDE_CHECK		SIDE_ATTACK,SIDE_ENEMY,SUB_048_NEXT
	//ねこにこばんカウンターに加算
	VALUE_WORK		VAL_ADD,BUF_PARA_KOBAN_COUNTER,BUF_PARA_CALC_WORK
SUB_048_NEXT:
	MESSAGE			NekonikobanMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
