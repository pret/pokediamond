
//============================================================================
/**
 *
 *@file		sub_135.s
 *@brief	戦闘シーケンス
 *			なりきりシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_135:
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran
	//特性ふしぎなまもりは、うまくきまらん
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_speabino,TOKUSYU_HUSIGINAMAMORI,Umakukimaran
	//特性マルチタイプは、うまくきまらん
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_speabino,TOKUSYU_MARUTITAIPU,Umakukimaran
	//特性マルチタイプは、うまくきまらん
	IF_PSP			IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_speabino,TOKUSYU_MARUTITAIPU,Umakukimaran
	//特性を持っていない場合は、うまくきまらん
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_speabino,0,Umakukimaran

	GOSUB			SUB_SEQ_WAZA_OUT_EFF

	//なまけビットを初期化
	VALUE_WORK		VAL_SET,BUF_PARA_TEMP_WORK,BUF_PARA_TOTAL_TURN
	//次のターンなまけさせるために、インクリメントはなし
//	VALUE			VAL_ADD,BUF_PARA_TEMP_WORK,1
	VALUE			VAL_AND,BUF_PARA_TEMP_WORK,1
	PSP_VALUE_WORK	VAL_SET,SIDE_ATTACK,ID_PSP_wkw_namake_bit,BUF_PARA_TEMP_WORK

	PSP_VALUE_WORK	VAL_GET,SIDE_DEFENCE,ID_PSP_speabino,BUF_PARA_TEMP_WORK
	PSP_VALUE_WORK	VAL_SET,SIDE_ATTACK,ID_PSP_speabino,BUF_PARA_TEMP_WORK

	IF				IF_FLAG_NE,BUF_PARA_TEMP_WORK,TOKUSYU_SUROOSUTAATO,Message
	//なりきった特性がスロースタートの場合は、カウンタをリセット
	VALUE_WORK		VAL_SET,BUF_PARA_TEMP_WORK,BUF_PARA_TOTAL_TURN
	VALUE			VAL_ADD,BUF_PARA_TEMP_WORK,1
	PSP_VALUE_WORK	VAL_SET,SIDE_ATTACK,ID_PSP_wkw_slow_start_count,BUF_PARA_TEMP_WORK
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_slow_start_flag,0
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_slow_start_end_flag,0

Message:
	MESSAGE			NarikiriM2MMsg,TAG_NICK_NICK_TOKU,SIDE_ATTACK,SIDE_DEFENCE,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
