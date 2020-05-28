
//============================================================================
/**
 *
 *@file		sub_039.s
 *@brief	戦闘シーケンス
 *			こんらんシーケンス（自分を攻撃）
 *@author	HisashiSogabe
 *@data		2005.12.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_039:
	MESSAGE			ConfusedMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	STATUS_EFFECT	SIDE_ATTACK,STATUS_KONRAN
	SERVER_WAIT
	MESSAGE			KonranMsg2,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	//ため系のフラグを落とす
	KEEP_OFF		SIDE_ATTACK
	//HP１で耐える系チェック
	HP1_CHECK		SIDE_ATTACK
	GOSUB			SUB_SEQ_HP_CALC
	GOSUB			SUB_SEQ_WAZA_STATUS_MSG
	SEQ_END
