//
//============================================================================================
/**
 * @file	tr_ai_def.h
 * @bfief	トレーナーAIプログラム用定義ファイル
 * @author	HisashiSogabe
 * @date	06.04.25
 */
//============================================================================================

//#define	AIWT				((AIWorkTbl *)&UserWork[0x16800])
//#define	AIWT2				((AIWorkTbl2 *)&UserWork[0x16a00])
//#define	AI_PUSH_ADRS		((PushAdrs *)&UserWork[0x16c00])	//4バイト*8+1

#define	LOSS_CALC_OFF	(0)		//ダメージロス計算のぶれなし
#define	LOSS_CALC_ON	(1)		//ダメージロス計算のぶれあり

//=========================================================================
//	AI_STATUSFLAG宣言
//=========================================================================

#define	AI_STATUSFLAG_END		0x01			//AIシーケンスの終了
#define	AI_STATUSFLAG_ESCAPE	0x02			//にげるを選択
#define	AI_STATUSFLAG_SAFARI	0x04			//サファリゾーン特有のアクション
#define	AI_STATUSFLAG_FINISH	0x08			//チェックする技が残っていても終了
#define	AI_STATUSFLAG_CONTINUE	0x10			//AI計算継続

#define	AI_STATUSFLAG_END_OFF		(0x01^0xff)
#define	AI_STATUSFLAG_ESCAPE_OFF	(0x01^0xff)
#define	AI_STATUSFLAG_SAFARI_OFF	(0x04^0xff)
#define	AI_STATUSFLAG_CONTINUE_OFF	(0x10^0xff)			//AI計算継続

#define	AI_ENEMY_ESCAPE		4
#define	AI_ENEMY_SAFARI		5
#define	AI_ENEMY_RESHUFFLE	6

//=========================================================================
//	AI_THINK_BIT宣言
//=========================================================================

#define	AI_THINK_BIT_BASIC		(0x00000001)			//基本AI
#define	AI_THINK_BIT_ATTACK		(0x00000002)			//攻撃型AI
#define	AI_THINK_BIT_EXPERT		(0x00000004)			//エキスパートAI
#define	AI_THINK_BIT_HOJO		(0x00000008)			//補助技AI
#define	AI_THINK_BIT_GAMBLE		(0x00000010)			//ギャンブルAI
#define	AI_THINK_BIT_DAMAGE		(0x00000020)			//ダメージ重視AI
#define	AI_THINK_BIT_RILAY		(0x00000040)			//リレー型AI
#define	AI_THINK_BIT_DOUBLE		(0x00000080)			//ダブルバトルAI
#define	AI_THINK_BIT_HP_CHECK	(0x00000100)			//HPで判断AI
#define	AI_THINK_BIT_WEATHER	(0x00000200)			//天候技AI
#define	AI_THINK_BIT_HARASS		(0x00000400)			//いやがらせAI
#define	AI_THINK_BIT_MV_POKE	(0x20000000)			//移動ポケモン
#define	AI_THINK_BIT_SAFARI		(0x40000000)			//サファリゾーン
#define	AI_THINK_BIT_GUIDE		(0x80000000)			//ガイドバトル

//tr_ai.s waza_ai.cで使用（マクロでsideに指定する値）
#define	CHECK_DEFENCE			(0)
#define	CHECK_ATTACK			(1)
#define	CHECK_DEFENCE_FRIEND	(2)
#define	CHECK_ATTACK_FRIEND		(3)

#define	CHECK_DEFENCE_TYPE1			(0)
#define	CHECK_ATTACK_TYPE1			(1)
#define	CHECK_DEFENCE_TYPE2			(2)
#define	CHECK_ATTACK_TYPE2			(3)
#define	CHECK_WAZA					(4)
#define	CHECK_DEFENCE_FRIEND_TYPE1	(5)
#define	CHECK_ATTACK_FRIEND_TYPE1	(6)
#define	CHECK_DEFENCE_FRIEND_TYPE2	(7)
#define	CHECK_ATTACK_FRIEND_TYPE2	(8)


//COMP_POWERで使用
#define	COMP_POWER_NONE		(0)		//威力計算しない技
#define	COMP_POWER_NOTOP	(1)		//ダメージ量がトップじゃない
#define	COMP_POWER_TOP		(2)		//ダメージ量がトップ

//IF_FIRSTで使用
#define	IF_FIRST_ATTACK		(0)		//自分が早い
#define	IF_FIRST_DEFENCE	(1)		//相手が早い
#define	IF_FIRST_EQUAL		(2)		//同じ

//AI_CHECK_AISYOUで使用
//AI_CHECK_WAZA_AISYOUで使用
#define	AISYOU_4BAI			(160)	//4倍効果
#define	AISYOU_2BAI			(80)	//2倍効果
#define	AISYOU_15BAI		(60)	//1.5倍効果
#define	AISYOU_1BAI			(40)	//1倍効果
#define	AISYOU_1_2BAI		(20)	//1/2倍効果
#define	AISYOU_1_4BAI		(10)	//1/4倍効果
#define	AISYOU_0BAI			(0)		//効果なし

//AI_IF_PARA_UNDERで使用
//AI_IF_PARA_OVERで使用
//AI_IF_PARA_EQUALで使用
//AI_IFN_PARA_EQUALで使用
#define	PARA_HP					0x00			//体力
#define	PARA_POW				0x01			//攻撃力
#define	PARA_DEF				0x02			//防御力
#define	PARA_AGI				0x03			//素早さ
#define	PARA_SPEPOW				0x04			//特攻
#define	PARA_SPEDEF				0x05			//特防
#define	PARA_HIT				0x06			//命中率
#define	PARA_AVOID				0x07			//回避率

//AI_IF_POKE_CHECK_STATE,AI_IF_WAZA_CHECK_STATEで使用
#define	STATE_KANASIBARI		0x00			//かなしばり
#define	STATE_ENCORE			0x01			//アンコール

//AI_CHECK_WEATHERで使用
#define	WEATHER_NONE			0x00			//天候変化なし
#define	WEATHER_HARE			0x01			//にほんばれ状態
#define	WEATHER_AME				0x02			//あまごい状態
#define	WEATHER_SUNAARASHI		0x03			//すなあらし状態
#define	WEATHER_ARARE			0x04			//あられ状態
#define	WEATHER_HUKAIKIRI		0x05			//ふかいきり状態

//AI_IF_LEVELで使用
#define	LEVEL_ATTACK			0x00			//アタックのレベルが高い
#define	LEVEL_DEFENCE			0x01			//ディフェンスのレベルが高い
#define	LEVEL_EQUAL				0x02			//レベルが一緒

// AI_HAVE_TOKUSEI, AI_HAVE_WAZA 等で使用
#define HAVE_NO			0
#define HAVE_YES		1
#define HAVE_UNKNOWN	2

