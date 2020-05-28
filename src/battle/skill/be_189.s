//============================================================================
/**
 *
 *@file		be_189.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			189　相手のＨＰ－自分のＨＰ分のダメージを与える。
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_189:
	//相手のHPを取得
	PSP_VALUE_WORK	VAL_GET,SIDE_DEFENCE,ID_PSP_hp,BUF_PARA_DAMAGE
	//自分のHPを取得
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_hp,BUF_PARA_CALC_WORK
	//相手のHP<=自分のHPなら、うまくきまらん
	IF_WORK			IF_FLAG_NC,BUF_PARA_DAMAGE,BUF_PARA_CALC_WORK,Umakukimaran

	//ダメージ量計算
	VALUE_WORK		VAL_SUB,BUF_PARA_DAMAGE,BUF_PARA_CALC_WORK
	VALUE			VAL_MUL,BUF_PARA_DAMAGE,-1
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_FLAT
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
