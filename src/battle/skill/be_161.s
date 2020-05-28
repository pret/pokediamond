//============================================================================
/**
 *
 *@file		be_161.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			161　たくわえた分だけ大きいダメージを与える。攻撃終了後、たくわえるで上げた、ステータスを元に戻す。
 *
 *@author	HisashiSogabe
 *@data		2006.02.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_161:
	IF_PSP			IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_wkw_takuwaeru_count,0,BE_161_NG
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_wkw_takuwaeru_count,BUF_PARA_DAMAGE_POWER
	VALUE			VAL_MUL,BUF_PARA_DAMAGE_POWER,100
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_wkw_takuwaeru_count,0
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_wkw_takuwaeru_def_count,BUF_PARA_CALC_WORK
	PSP_VALUE_WORK	VAL_SUB_ZERO,SIDE_ATTACK,ID_PSP_abiritycnt_def,BUF_PARA_CALC_WORK
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_wkw_takuwaeru_spedef_count,BUF_PARA_CALC_WORK
	PSP_VALUE_WORK	VAL_SUB_ZERO,SIDE_ATTACK,ID_PSP_abiritycnt_spedef,BUF_PARA_CALC_WORK
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_wkw_takuwaeru_def_count,0
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_wkw_takuwaeru_spedef_count,0
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_MORE_NOHIT_MSG
	MESSAGE_PARAM	TakuwaeruEndMineMsg,TAG_NICK,SIDE_ATTACK
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC_NO_LOSS
	SEQ_END
	
BE_161_NG:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	MESSAGE			HakidasuNGMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	SEQ_END
