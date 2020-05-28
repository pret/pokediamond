
//============================================================================
/**
 *
 *@file		sub_014.s
 *@brief	戦闘シーケンス
 *			ひるむ追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2005.11.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_014:
	//対象が技を出し終えていたら、ひるませても意味がないので、終了
	WAZA_OUT_CHECK				SIDE_TSUIKA,SUB_014_END
	//みがわりがいる場合は、ひるまない
	MIGAWARI_CHECK				SIDE_TSUIKA,Umakukimaran
	//特性せいしんりょくは、ひるまない
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_SEISINRYOKU,SEQ_SEISINRYOKU
	//間接追加の時は、りんぷんチェックをする
	IF							IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SEQ_014_NEXT
	//特性りんぷんは、ひるまない
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RINPUN,SUB_014_END
SEQ_014_NEXT:
	PSP_VALUE					VAL_BIT,SIDE_TSUIKA,ID_PSP_condition2,CONDITION2_HIRUMU
SUB_014_END:
	SEQ_END
SEQ_SEISINRYOKU:
	//ねこだましは、間接追加なので、技ナンバーで判断
	IF							IF_FLAG_EQ,BUF_PARA_WAZA_NO_NOW,WAZANO_NEKODAMASI,SEQ_SEISINRYOKU_MESSAGE
	//直接追加の時は、メッセージでひるむを防いだことを表示
	IF							IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,SEQ_SEISINRYOKU_END
SEQ_SEISINRYOKU_MESSAGE:
	MESSAGE						SeisinryokuMineMsg,TAG_NICK_TOKU,SIDE_TSUIKA,SIDE_TSUIKA
	SERVER_WAIT
	WAIT						MSG_WAIT
SEQ_SEISINRYOKU_END:
	SEQ_END

Umakukimaran:
	//直接追加の時は、メッセージで防いだことを表示
	IF							IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,Umakukimaran_END
	VALUE						VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
Umakukimaran_END:
	SEQ_END
