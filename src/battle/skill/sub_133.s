
//============================================================================
/**
 *
 *@file		sub_133.s
 *@brief	戦闘シーケンス
 *			ちょうはつで技がだせないシーケンス

 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_133:
	//ちょうはつカウンタを-1する（最初のターン分多めにしてあるので）
//	PSP_VALUE		VAL_SUB,SIDE_ATTACK,ID_PSP_wkw_chouhatsu_count,1
	MESSAGE			ChouhatsuNGMineMsg,TAG_NICK_WAZA,SIDE_ATTACK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//ため系フラグを落とす
	KEEP_OFF		SIDE_ATTACK
	SEQ_END
