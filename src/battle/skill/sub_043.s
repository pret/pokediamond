
//============================================================================
/**
 *
 *@file		sub_043.s
 *@brief	戦闘シーケンス
 *			わるあがき反動シーケンス
 *@author	HisashiSogabe
 *@data		2005.12.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_043:
	//HP操作対象をAttackClientに
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	//HPMAXを取得
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_hpmax,BUF_PARA_HP_CALC_WORK
	//値を４分の１に
	VALUE			VAL_MUL,BUF_PARA_HP_CALC_WORK,-1
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,4
	//ダメージエフェクトで点滅しないフラグを立てる
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			HanekaeriMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
