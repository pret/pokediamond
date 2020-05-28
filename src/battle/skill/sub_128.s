
//============================================================================
/**
 *
 *@file		sub_128.s
 *@brief	戦闘シーケンス
 *			おだてる追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_128:
	//みがわりを出されている時は、うまくきまらん
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	//特攻がMAXまで上がっていない時は、効果スタート
	IF_PSP			IF_FLAG_NE,SIDE_DEFENCE,ID_PSP_abiritycnt_spepow,12,SUB_128_ABICNT_START
	//すでにこんらんしていない時は、混乱スタート
	IF_PSP			IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_KONRAN,SUB_128_KONRAN_START
	//MAXで混乱の時は、うまくきまらん
	BRANCH			Umakukimaran
SUB_128_ABICNT_START:
	//特攻を1段階上げるをセット
	VALUE			VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_SPEPOWUP
	GOSUB			SUB_SEQ_ABICNT_CALC
	//すでにこんらんしている時は、効果終了
	IF_PSP			IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_KONRAN,SUB_128_END
SUB_128_KONRAN_START:
	GOSUB			SUB_SEQ_KONRAN
SUB_128_END:
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
