//============================================================================
/**
 *
 *@file		be_136.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			136　5ターンの間、「あめ」状態にして「水」タイプの技の攻撃力を上げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_136:
	IF				IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_AME_ALL,Umakukimaran
	MESSAGE_PARAM	AmeMsg,TAG_NONE
	VALUE			VAL_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_TENKI
	VALUE			VAL_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_AME
	VALUE			VAL_SET,BUF_PARA_WEATHER_COUNT,AMAGOI_COUNT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_TENKOU|ADD_STATUS_WAZAKOUKA
	//装備効果であまごいのターン数を増やす効果は、ターン数を増やす
	SOUBI_CHECK		SOUBI_NO_HAVE,SIDE_ATTACK,SOUBI_AMEUPHAREDOWN,BE_136_END
	SOUBI_ATK_GET	SIDE_ATTACK,BUF_PARA_CALC_WORK
	VALUE_WORK		VAL_ADD,BUF_PARA_WEATHER_COUNT,BUF_PARA_CALC_WORK
BE_136_END:
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
