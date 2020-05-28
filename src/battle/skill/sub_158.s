
//============================================================================
/**
 *
 *@file		sub_158.s
 *@brief	戦闘シーケンス
 *			ミラクルアイ追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_158:
	PSP_VALUE	VAL_BIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_MIRACLE_EYE
	MESSAGE		MiyaburuM2MMsg,TAG_NICK_NICK,SIDE_ATTACK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
