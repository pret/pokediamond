//============================================================================
/**
 *
 *@file		be_213.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			213　フィールドタイプと同じタイプになる
 *
 *@author	HisashiSogabe
 *@data		2006.03.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_213:
	HOGOSYOKU		Umakukimaran
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_HOGOSYOKU
	MESSAGE_PARAM	TextureMineMsg,TAG_NICK_TYPE,SIDE_ATTACK,SIDE_WORK
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
