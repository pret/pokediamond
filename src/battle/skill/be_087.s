//============================================================================
/**
 *
 *@file		be_087.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			087　敵の「ぼうぎょ」や、自分の「こうげき」に関係なくレベルと同じ数値の固定ダメージを与える
 *
 *@author	HisashiSogabe
 *@data		2006.01.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_087:
	//タイプ補正計算を無視する
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_FLAT
	//ダメージを自分のレベルに
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_level,BUF_PARA_DAMAGE
	VALUE			VAL_MUL,BUF_PARA_DAMAGE,-1
	SEQ_END
