
//============================================================================
/**
 *
 *@file		sub_095.s
 *@brief	戦闘シーケンス
 *			ちいさくなる追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_095:
	PSP_VALUE	VAL_BIT,SIDE_TSUIKA,ID_PSP_waza_kouka,WAZAKOUKA_CHIISAKUNARU
	//回避率を1段階上げるをセット
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_AVOIDUP
	JUMP		SUB_SEQ_ABICNT_CALC
