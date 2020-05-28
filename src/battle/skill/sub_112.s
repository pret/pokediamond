
//============================================================================
/**
 *
 *@file		sub_112.s
 *@brief	戦闘シーケンス
 *			プレゼントシーケンス
 *@author	HisashiSogabe
 *@data		2006.01.31
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_112:
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_HAZURE,Hazure
	ATTACK_MESSAGE
	SERVER_WAIT
	//ヒールブロックを受けている時は回復動作なし
	IF_PSP			IF_FLAG_NE,SIDE_DEFENCE,ID_PSP_wkw_healblock_count,0,Healblock
	GOSUB			SUB_SEQ_KAIFUKU
Hazure:
	SEQ_END

Healblock:
	VALUE			VAL_SET,BUF_PARA_WAZA_WORK,WAZANO_KAIHUKUHUUZI
	MESSAGE			HealblockRecoverNGMineMsg,TAG_NICK_WAZA,SIDE_DEFENCE,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
