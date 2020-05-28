//============================================================================
/**
 *
 *@file		be_115.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			115　　天気を砂嵐の状態にし、お互いのポケモンに毎ターンダメージを与える　いわ、はがね、じめんタイプにはきかない
 *
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_115:
	IF				IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_SUNAARASHI_ALL,Umakukimaran
	MESSAGE_PARAM	SunaarashiMsg,TAG_NONE
	VALUE			VAL_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_TENKI
	VALUE			VAL_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_SUNAARASHI
	VALUE			VAL_SET,BUF_PARA_WEATHER_COUNT,SUNAARASHI_COUNT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_TENKOU|ADD_STATUS_WAZAKOUKA
	//装備効果ですなあらしのターン数を増やす効果は、ターン数を増やす
	SOUBI_CHECK		SOUBI_NO_HAVE,SIDE_ATTACK,SOUBI_SUNAARASIUP,BE_115_END
	SOUBI_ATK_GET	SIDE_ATTACK,BUF_PARA_CALC_WORK
	VALUE_WORK		VAL_ADD,BUF_PARA_WEATHER_COUNT,BUF_PARA_CALC_WORK
BE_115_END:
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
