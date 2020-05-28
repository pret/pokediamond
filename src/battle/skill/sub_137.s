
//============================================================================
/**
 *
 *@file		sub_137.s
 *@brief	戦闘シーケンス
 *			ねをはるでHP回復シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.08
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_137:
	STATUS_EFFECT	SIDE_WORK,STATUS_DAMAGE_NEWOHARU
	SERVER_WAIT
	MESSAGE			NewoharuRecoverMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//HPMAXの1/16回復
	PSP_VALUE_WORK	VAL_GET,SIDE_WORK,ID_PSP_hpmax,BUF_PARA_HP_CALC_WORK
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,16
	//装備効果で吸い取る系の威力アップは、威力アップ
	SOUBI_CHECK		SOUBI_NO_HAVE,SIDE_WORK,SOUBI_KYUSYUURYOKUUP,SUB_137_NEXT
	SOUBI_ATK_GET	SIDE_WORK,BUF_PARA_CALC_WORK
	VALUE			VAL_ADD,BUF_PARA_CALC_WORK,100
	VALUE_WORK		VAL_MUL,BUF_PARA_HP_CALC_WORK,BUF_PARA_CALC_WORK
	VALUE			VAL_DIV,BUF_PARA_HP_CALC_WORK,100
SUB_137_NEXT:
	//ダメージエフェクトで点滅しないフラグを立てる
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//HP計算サブルーチンへ
	GOSUB			SUB_SEQ_HP_CALC
	SEQ_END

