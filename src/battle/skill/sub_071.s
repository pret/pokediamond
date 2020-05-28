
//============================================================================
/**
 *
 *@file		sub_071.s
 *@brief	戦闘シーケンス
 *			かなしばりで技がだせないシーケンス

 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_071:
	//ため技をかなしばってきた場合は、カウンタを-1する必要なし
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP,NoDecCounter
	//かなしばりカウンタを-1する（最初のターン分多めにしてあるので）
//	PSP_VALUE		VAL_SUB,SIDE_ATTACK,ID_PSP_wkw_kanashibari_count,1
NoDecCounter:
	MESSAGE			KanashibariNGMineMsg,TAG_NICK_WAZA,SIDE_ATTACK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//ため系フラグを落とす
	KEEP_OFF		SIDE_ATTACK
	SEQ_END
