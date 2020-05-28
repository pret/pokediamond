//============================================================================
/**
 *
 *@file		be_168.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			168　自分が瀕死になるが、相手の攻撃力、特殊攻撃力を２段階下げる
 *
 *@author	HisashiSogabe
 *@data		2006.02.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_168:
	//自爆の初期化処理
	VALUE			VAL_SET,BUF_PARA_CALC_WORK,SERVER_STATUS_FLAG_JIBAKU
	VALUE_WORK		VAL_LSH,BUF_PARA_CALC_WORK,BUF_PARA_ATTACK_CLIENT
	VALUE_WORK		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,BUF_PARA_CALC_WORK
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_hp,0
	//ゲージを0にする処理
	VALUE			VAL_SET,BUF_PARA_HP_CALC_WORK,JIBAKU_HP
	HP_GAUGE_CALC	SIDE_ATTACK
	//消えている相手にも当てる
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_KIE_HIT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_OKIMIYAGE|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END
