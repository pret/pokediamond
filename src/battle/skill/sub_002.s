
//============================================================================
/**
 *
 *@file		sub_002.s
 *@brief	戦闘シーケンス
 *			ポケモンHP計算シーケンス
 *@author	HisashiSogabe
 *@data		2005.07.29
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_002:
	//ブリンクエフェクトするかしないかチェック
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK,NoBlinkEffect
	WAZAKOUKA_SE	SIDE_WORK
	POKEMON_BLINK	SIDE_WORK
	SERVER_WAIT
	//抜群の威力を弱める装備効果のチェック
	GOSUB			SUB_SEQ_SOUBI_BATSUGUN_DOWN_CHECK
NoBlinkEffect:
	//フラグは落としておく
	VALUE			VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	HP_GAUGE_CALC	SIDE_WORK
	SERVER_WAIT
	HP_CALC			SIDE_WORK
	KIZETSU_CHECK	SIDE_WORK
	//ダメージは、だめおしワークに格納
	IF				IF_FLAG_C,BUF_PARA_HP_CALC_WORK,0,SUB_002_END
	VALUE_WORK		VAL_SET,BUF_PARA_DAMEOSHI_DAMAGE,BUF_PARA_HP_CALC_WORK
SUB_002_END:
	SEQ_END
