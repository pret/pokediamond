//============================================================================
/**
 *
 *@file		be_156.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			156 使用したポケモンの「ぼうぎょ」を１段階上げる＋「まるくなる」状態にする
 *
 *@author	HisashiSogabe
 *@data		2005.11.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_156:
	//「まるくなる」フラグを立てる
	PSP_VALUE	VAL_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_MARUKUNARU
	//「ぼうぎょ」を１段階上げる
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_DEFUP|ADD_STATUS_ATTACK
	SEQ_END
