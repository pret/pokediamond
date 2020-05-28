
//============================================================================
/**
 *
 *@file		sub_101.s
 *@brief	戦闘シーケンス
 *			ほろびのうた追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_101:
	HOROBINOUTA					Umakukimaran
	GOSUB						SUB_SEQ_WAZA_OUT_EFF
	MESSAGE						HorobinoutaMsg,TAG_NONE
	SERVER_WAIT
	WAIT						MSG_WAIT
	VALUE						VAL_SET,BUF_PARA_WAZA_WORK,WAZANO_HOROBINOUTA
	VALUE						VAL_SET,BUF_PARA_TOKUSEI_WORK,TOKUSYU_BOUON
	VALUE						VAL_SET,BUF_PARA_CLIENT_NO_AGI,0
BouonLoop:
	CLIENT_NO_GET_AGI			BUF_PARA_CLIENT_WORK
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_NO_HAVE,SIDE_WORK,TOKUSYU_BOUON,BouonNext
	MESSAGE						BouonMineMsg,TAG_NICK_TOKU_WAZA,SIDE_WORK,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT						MSG_WAIT
BouonNext:
	VALUE						VAL_ADD,BUF_PARA_CLIENT_NO_AGI,1
	CLIENT_SET_MAX_LOOP			BUF_PARA_CLIENT_NO_AGI,BouonLoop
	SEQ_END

Umakukimaran:
	VALUE						VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
