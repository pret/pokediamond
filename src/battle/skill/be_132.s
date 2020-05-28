//============================================================================
/**
 *
 *@file		be_132.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			132　ＨＰを回復するが効果は天気で変わる、日本晴れ=２／３、通常=１／２、雨、砂嵐、あられ=１／４
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_132:
	WEATHER_KAIFUKU
	//HP操作対象をAttackClientに
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	//プレゼントの回復動作と同じなので、プレゼントの追加効果扱いにする
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_PRESENT|ADD_STATUS_WAZAKOUKA
	//回復エフェクトが出るようにフラグを立てる
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_KAIFUKU_EFFECT
	SEQ_END
