
//============================================================================
/**
 *
 *@file		sub_140.s
 *@brief	戦闘シーケンス
 *			かわらわり発動シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.08
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_140:
	KAWARAWARI	SUB_140_NEXT
	//かべ系を破壊するエフェクトをセット
	VALUE		VAL_SET,BUF_PARA_WAZA_EFF_CNT,1
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
	MESSAGE		KawarawariMsg,TAG_NONE
	SERVER_WAIT
	WAIT		MSG_WAIT
	BRANCH		SUB_140_END
SUB_140_NEXT:
	IF			IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_HAZURE,SUB_140_END
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
SUB_140_END:
	SEQ_END
