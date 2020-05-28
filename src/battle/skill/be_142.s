//============================================================================
/**
 *
 *@file		be_142.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			142　使用したポケモンのＨＰが半分になる替わりに「こうげき」が最大まで上げる
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_142:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HARADAIKO|ADD_STATUS_WAZAKOUKA
	SEQ_END
