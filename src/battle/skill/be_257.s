//============================================================================
/**
 *
 *@file		be_257.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			257 普通攻撃＋「ダイビング」状態の相手に２倍のダメージ
 *
 *@author	HisashiSogabe
 *@data		2005.11.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_257:
	//ダイビングをしている相手には2倍ダメージを与える
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_DAIBINGU_HIT
	VALUE		VAL_SET,BUF_PARA_DAMAGE_VALUE,10
	IF_PSP		IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_DAIBINGU,BE_257_END
	VALUE		VAL_SET,BUF_PARA_DAMAGE_VALUE,20
BE_257_END:
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
