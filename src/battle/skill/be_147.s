//============================================================================
/**
 *
 *@file		be_147.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			147 普通攻撃＋「あなをほる」をしている相手に２倍のダメージ
 *
 *@author	HisashiSogabe
 *@data		2005.11.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_147:
	//あなをほるをしている相手には2倍ダメージを与える
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_ANAWOHORU_HIT
	VALUE		VAL_SET,BUF_PARA_DAMAGE_VALUE,10
	IF_PSP		IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_ANAWOHORU,BE_147_END
	VALUE		VAL_SET,BUF_PARA_DAMAGE_VALUE,20
BE_147_END:
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
