
//============================================================================
/**
 *
 *@file		sub_242.s
 *@brief	戦闘シーケンス
 *			でんじふゆう終わったメッセージシーケンス
 *@author	HisashiSogabe
 *@data		2006.05.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_242:
	MESSAGE		DenzihuyuuEndMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	//でんじふゆうフラグを落とす
	PSP_VALUE	VAL_NBIT,SIDE_WORK,ID_PSP_waza_kouka,WAZAKOUKA_DENZIHUYUU
	SEQ_END
