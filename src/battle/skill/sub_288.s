
//============================================================================
/**
 *
 *@file		sub_288.s
 *@brief	戦闘シーケンス
 *			ちょうはつ終わったメッセージシーケンス
 *@author	HisashiSogabe
 *@data		2006.07.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_288:
	VALUE		VAL_SET,BUF_PARA_WAZA_WORK,WAZANO_TYOUHATU
	MESSAGE		TyouhatuEndMineMsg,TAG_NICK_WAZA,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
