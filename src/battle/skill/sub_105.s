
//============================================================================
/**
 *
 *@file		sub_105.s
 *@brief	戦闘シーケンス
 *			いばる追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.01.31
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_105:
	//みがわりを出されている時は、うまくきまらん
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	//攻撃力がMAXまで上がっていない時は、効果スタート
	IF_PSP			IF_FLAG_NE,SIDE_DEFENCE,ID_PSP_abiritycnt_pow,12,SUB_105_ABICNT_START
	//すでにこんらんしていない時は、混乱スタート
	IF_PSP			IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_KONRAN,SUB_105_KONRAN_START
	//MAXで混乱の時は、うまくきまらん
	BRANCH			Umakukimaran
SUB_105_ABICNT_START:
	//攻撃を2段階上げるをセット
	VALUE			VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_POWUP2
	GOSUB			SUB_SEQ_ABICNT_CALC
	//すでにこんらんしている時は、効果終了
	IF_PSP			IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_KONRAN,SUB_105_END
SUB_105_KONRAN_START:
	GOSUB			SUB_SEQ_KONRAN
SUB_105_END:
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
