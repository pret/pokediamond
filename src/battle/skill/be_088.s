//============================================================================
/**
 *
 *@file		be_088.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			088　使用したポケモンのレベル×０．５～１．５までの数値をランダムでダメージとして敵に与える
 *
 *@author	HisashiSogabe
 *@data		2006.01.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_088:
	//タイプ補正計算を無視する
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_FLAT
	//ダメージを自分のレベル×０．５～１．５までにする
	RANDOM_GET		10,5
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_level,BUF_PARA_DAMAGE
	VALUE_WORK		VAL_MUL,BUF_PARA_DAMAGE,BUF_PARA_CALC_WORK
	VALUE			VAL_DIV,BUF_PARA_DAMAGE,10
	IF				IF_FLAG_NE,BUF_PARA_DAMAGE,0,BE_088_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE,1
BE_088_NEXT:
	VALUE			VAL_MUL,BUF_PARA_DAMAGE,-1
	SEQ_END
