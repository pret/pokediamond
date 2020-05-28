
//============================================================================
/**
 *
 *@file		sub_062.s
 *@brief	戦闘シーケンス
 *			きあいだめ処理
 *@author	HisashiSogabe
 *@data		2005.07.29
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_062:
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
	//きあいだめフラグを立てる
	PSP_VALUE	VAL_BIT,SIDE_TSUIKA,ID_PSP_condition2,CONDITION2_KIAIDAME
	MESSAGE		KiaidameMineMsg,TAG_NICK,SIDE_TSUIKA
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END

