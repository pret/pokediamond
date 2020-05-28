//============================================================================
/**
 *
 *@file		sub_259.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			ため技系の溜めた後の処理をまとめたサブルーチン
 *
 *@author	HisashiSogabe
 *@data		2005.11.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_259:
	//技エフェクトカウンタをセット
	VALUE			VAL_SET,BUF_PARA_WAZA_EFF_CNT,1
	//ためフラグを落とす
	PSP_VALUE		VAL_NBIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP
	//ため発動フラグをセット
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_AFTER
	SEQ_END
