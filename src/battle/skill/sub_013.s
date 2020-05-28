
//============================================================================
/**
 *
 *@file		sub_013.s
 *@brief	戦闘シーケンス
 *			ため系追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2005.11.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_013:
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	MESSAGE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	KEEP_ON			SIDE_TSUIKA
	IF_PSP			IF_FLAG_NBIT,SIDE_TSUIKA,ID_PSP_waza_kouka,WAZAKOUKA_KIE,SUB_013_END
	VANISH_ON_OFF	SIDE_TSUIKA,SW_VANISH_ON
SUB_013_END:
	SEQ_END
