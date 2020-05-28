
//============================================================================
/**
 *
 *@file		sub_192.s
 *@brief	戦闘シーケンス
 *			特性でHP回復シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.23
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_192:
	MESSAGE			TokuseiHPKaifukuMineMsg,TAG_NICK_TOKU,SIDE_WORK,SIDE_CLIENT_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//ダメージエフェクトで点滅しないフラグを立てる
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//HP計算サブルーチンへ
	GOSUB			SUB_SEQ_HP_CALC
	SEQ_END
