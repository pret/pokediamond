
//============================================================================
/**
 *
 *@file		sub_081.s
 *@brief	戦闘シーケンス
 *			フェイントシーケンス（シャドーダイブも）
 *@author	HisashiSogabe
 *@data		2006.07.10
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_081:
	IF				IF_FLAG_EQ,BUF_PARA_WAZA_NO_NOW,WAZANO_FEINTO,Feint
Shadow:
	OTF_CHECK		SIDE_DEFENCE,OTF_mamoru_flag,0,NoMessage
	MESSAGE			ShadowMineMsg,TAG_NICK,SIDE_DEFENCE
	BRANCH			SUB_081_NEXT
Feint:
	MESSAGE			FeintMineMsg,TAG_NICK,SIDE_DEFENCE
SUB_081_NEXT:
	SERVER_WAIT
	WAIT			MSG_WAIT
NoMessage:
	OTF_SET			SIDE_DEFENCE,OTF_mamoru_flag,0
	SEQ_END

