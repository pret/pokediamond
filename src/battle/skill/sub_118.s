
//============================================================================
/**
 *
 *@file		sub_118.s
 *@brief	戦闘シーケンス
 *			すりこみシーケンス
 *@author	HisashiSogabe
 *@data		2006.07.10
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_118:
	IF_PSP		IF_FLAG_NBIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_NEMURI,DokuCheck
	GOSUB		SUB_SEQ_NEMURI
	BRANCH		SUB_118_NEXT
DokuCheck:
	IF_PSP		IF_FLAG_NBIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_DOKU,YakedoCheck
	GOSUB		SUB_SEQ_DOKU
	BRANCH		SUB_118_NEXT
YakedoCheck:
	IF_PSP		IF_FLAG_NBIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_YAKEDO,MahiCheck
	GOSUB		SUB_SEQ_YAKEDO
	BRANCH		SUB_118_NEXT
MahiCheck:
	IF_PSP		IF_FLAG_NBIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_MAHI,DokudokuCheck
	GOSUB		SUB_SEQ_MAHI
	BRANCH		SUB_118_NEXT
DokudokuCheck:
	GOSUB		SUB_SEQ_DOKUDOKU
SUB_118_NEXT:
	IF_PSP		IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_condition,CONDITION_BAD,SUB_118_END
	STATUS_SET	SIDE_ATTACK,STATUS_NORMAL
	PSP_VALUE	VAL_SET,SIDE_ATTACK,ID_PSP_condition,0
SUB_118_END:
	SEQ_END
