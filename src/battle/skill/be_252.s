//============================================================================
/**
 *
 *@file		be_252.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			252　５ターンの間、宙に浮き【ふゆう】状態になる。地面技が当たらなくなる。
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_252:
	IF_PSP			IF_FLAG_NE,SIDE_ATTACK,ID_PSP_wkw_denzihuyuu_count,0,Umakukimaran
	//特性ふゆうは、うまくきまらん
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_HUYUU,Umakukimaran
	//ねをはる中は、うまくきまらん
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_NEWOHARU,Umakukimaran
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_DENZIHUYUU
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_wkw_denzihuyuu_count,DENZIHUYUU_COUNT
	MESSAGE_PARAM	DenzihuyuuMineMsg,TAG_NICK,SIDE_ATTACK
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
