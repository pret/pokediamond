
//============================================================================
/**
 *
 *@file		sub_169.s
 *@brief	戦闘シーケンス
 *			技効果でHP回復シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_169:
	MESSAGE			AquaRingRecoverMineMsg,TAG_NICK_WAZA,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//ダメージエフェクトで点滅しないフラグを立てる
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//装備効果で吸い取る系の威力アップは、威力アップ
	SOUBI_CHECK		SOUBI_NO_HAVE,SIDE_WORK,SOUBI_KYUSYUURYOKUUP,SUB_169_NEXT
	SOUBI_ATK_GET	SIDE_WORK,BUF_PARA_CALC_WORK
	VALUE			VAL_ADD,BUF_PARA_CALC_WORK,100
	VALUE_WORK		VAL_MUL,BUF_PARA_HP_CALC_WORK,BUF_PARA_CALC_WORK
	VALUE			VAL_DIV,BUF_PARA_HP_CALC_WORK,100
SUB_169_NEXT:
	STATUS_EFFECT	SIDE_WORK,STATUS_EFF_RECOVER
	SERVER_WAIT
	//HP計算サブルーチンへ
	GOSUB			SUB_SEQ_HP_CALC
	SEQ_END

