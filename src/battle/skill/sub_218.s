
//============================================================================
/**
 *
 *@file		sub_218.s
 *@brief	戦闘シーケンス
 *			シャットアウト追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.03.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_218:
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	//特性マルチタイプは、うまくきまらん
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_speabino,TOKUSYU_MARUTITAIPU,Umakukimaran
	IF_PSP			IF_FLAG_NE,SIDE_DEFENCE,ID_PSP_wkw_shutout_count,0,Umakukimaran
	GOSUB			SUB_SEQ_WAZA_OUT_EFF
	PSP_VALUE		VAL_BIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_SHUTOUT
	PSP_VALUE		VAL_SET,SIDE_DEFENCE,ID_PSP_wkw_shutout_count,SHUTOUT_COUNT
	MESSAGE			ShutoutMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
