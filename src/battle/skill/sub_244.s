
//============================================================================
/**
 *
 *@file		sub_244.s
 *@brief	戦闘シーケンス
 *			シャットアウト終わったメッセージシーケンス
 *@author	HisashiSogabe
 *@data		2006.05.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_244:
	MESSAGE		ShutoutEndMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	//シャットアウトフラグを落とす
	PSP_VALUE	VAL_NBIT,SIDE_WORK,ID_PSP_waza_kouka,WAZAKOUKA_SHUTOUT
	SEQ_END
