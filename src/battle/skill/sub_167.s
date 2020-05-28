
//============================================================================
/**
 *
 *@file		sub_167.s
 *@brief	戦闘シーケンス
 *			なやみのたねシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_167:
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_speabino,TOKUSYU_NAMAKE,Umakukimaran
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_speabino,TOKUSYU_MARUTITAIPU,Umakukimaran
	GOSUB			SUB_SEQ_WAZA_OUT_EFF
	PSP_VALUE		VAL_SET,SIDE_DEFENCE,ID_PSP_speabino,TOKUSYU_HUMIN
	MESSAGE			NayaminotaneMineMsg,TAG_NICK_TOKU,SIDE_DEFENCE,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
