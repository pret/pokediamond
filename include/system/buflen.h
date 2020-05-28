//============================================================================================
/**
 *	文字列バッファ用サイズ定義
 */
//============================================================================================
#ifndef __BUFLEN_H__
#define __BUFLEN_H__


//	文字列関連の長さ定義
#define PERSON_NAME_SIZE	7	// 人物の名前の長さ（自分も含む）
#define	TR_NAME_SIZE		5	// トレーナーの名前の長さ	// localspecmark (ダミー)
#define MONS_NAME_SIZE		10	// ポケモン名の長さ(バッファサイズ EOM_含まず)
#define MONS_DISP_SIZE		5	// ポケモン名の長さ(表示サイズ EOM_含まず)
#define	WAZA_NAME_SIZE		7	// わざ名の長さ
#define	ITEM_NAME_SIZE		8	// どうぐ名の長さ
#define SEED_NAME_SIZE		6	// タネの名前の長さ
#define SPEABI_NAME_SIZE	7	// 特性名の長さ		// localspecmark 
#define ZOKUSEI_NAME_SIZE	4	// 属性名の長さ		// localspecmark 
#define MAPNAME_WIDTH		10  // 地名文字列の表示幅	// mapname.c, townmap.h から移動
#define MAPNAME_MAX			18  // 地名文字列の最大長	// mapname.c, townmap.h から移動
#define TRTYPE_NAME_SIZE	10	// トレーナータイプ名の長さ	// localspecmark murakawa
#define	GOODS_NAME_SIZE		10	// グッズ名の長さ
#define	ZUKAN_TYPE_SIZE		5	// 図鑑タイプ名の長さ
#define	EOM_SIZE			1	// 終了コードの長さ
#define	KAIWA_WORK_SIZE		7	// 簡易会話の１単語の最長文字数（EOM_含まず）
#define MONUMENT_NAME_SIZE	10	// 石碑の名前の長さ
#define	GROUP_NAME_SIZE		7	// ランダムグループの名前の長さ


//-------------------------------------------------------------------------------
/**
 *  これらの定義は「海外版でもこれだけ確保されていれば充分」というバッファ長の定義です。
 *  各要素の文字列をコピーするバッファの作成に使用します。余裕を持って定義して下さい。
 *  セーブデータのように、厳密な最大長が必要な箇所では使用しないでください。
 */
//-------------------------------------------------------------------------------

// 一応、全部偶数でそろえています

#define BUFLEN_EOM_SIZE					(GLOBAL_MSGLEN)		// EOMサイズ
#define BUFLEN_PERSON_NAME				(8)		// 人物名（プレイヤー含む）（海外でも７文字まで+EOM）
#define BUFLEN_POKEMON_NAME				(12)	// ポケモン名（海外でも10文字＋EOM）
#define BUFLEN_WAZA_NAME				(16)	// 技名（日本語７文字→海外14文字想定＋EOM）
#define BUFLEN_ITEM_NAME				(18)	// アイテム名（日本語８文字→海外16文字想定＋EOM）
#define BUFLEN_SEED_NAME				(14)	// タネ名（日本語６文字→海外12文字想定＋EOM）
#define BUFLEN_POKEMON_ABILITY_NAME		(16)	// ポケモンとくせい名（日本語７文字→海外14文字想定＋EOM）
#define BUFLEN_POKEMON_TYPE_NAME		(10)	// ポケモンタイプ名（日本語４文字→海外８文字想定＋EOM）
#define BUFLEN_POKEMON_CHARACTER_NAME	(12)	// ポケモンせいかく名（日本語５文字→海外10文字想定＋EOM）
#define BUFLEN_PLACE_NAME				(22)	// 地名（日本語10文字→海外20文字想定 +EOM）
#define BUFLEN_TRAINER_TYPE_NAME		(22)	// トレーナータイプ名（日本語10文字→海外20文字想定 +EOM）
#define BUFLEN_GOODS_NAME				(22)	// グッズ名（日本語10文字→海外20文字想定 +EOM）
#define BUFLEN_ZUKAN_TYPE_NAME			(12)	// 図鑑タイプ名（日本語５文字→海外10文字想定＋EOM）
#define BUFLEN_SEX						(2)		// 性別(♂♀ + EOM)
#define BUFLEN_ITEM_INFO				(114)	// アイテム説明（日本語57文字(改行・終了コード含む)→海外114文字想定）
#define BUFLEN_WAZA_INFO				(110)	// 技説明（日本語55文字(改行・終了コード含む)→海外110文字想定）
#define BUFLEN_PMS_WORD					(32)	// 簡易会話単語（日本語は７文字。余裕を持ってこれくらい）
#define BUFLEN_PORUTO_NAME				(22)	// ポルト名(日本語10文字→海外20文字+EOM_+パディング1)

//==============================================================================
//==============================================================================
//==============================================================================


//--------------------------------------------------------------
//	戦闘入力画面	battle_input.c
//--------------------------------------------------------------
///戦闘入力画面：ポケモン選択(技効果)　ポケモン名＋性別　将来的にスペースが入った時に備えて余分に+5
#define BUFLEN_BI_POKESELENAME			(BUFLEN_POKEMON_NAME + BUFLEN_SEX + (5*GLOBAL_MSGLEN))
///戦闘入力画面：PP + num + / + num
#define BUFLEN_BI_WAZAPP	((2 + 2 + 1 + 2) * GLOBAL_MSGLEN + BUFLEN_EOM_SIZE)
///戦闘入力画面：PP数値(日本語2文字＋EOM)
#define BUFLEN_BI_PP_NUM	(3*GLOBAL_MSGLEN)
///戦闘入力画面：「技名」をわすれる！
#define BUFLEN_BI_WASURERU	(100)		//適当に大きく
///戦闘入力画面：「技名」をわすれない！
#define BUFLEN_BI_WASURENAI	(100)
///戦闘入力画面：「つぎの　ポケモンを　つかう」
#define BUFLEN_BI_NEXT_POKEMON	(100)
///戦闘入力画面：「にげる」
#define BUFLEN_BI_NEXT_ESCAPE	(100)
///戦闘入力画面：「ポケモンを　いれかえる」
#define BUFLEN_BI_CHANGE_POKEMON	(100)
///戦闘入力画面：「そのまま　たたかう」
#define BUFLEN_BI_CHANGE_NOT	(100)

//--------------------------------------------------------------
//	戦闘ゲージ
//--------------------------------------------------------------
///戦闘ゲージ：ニックネーム　将来的にスペースが入った時に備えて余分に+5
#define BUFLEN_GAUGE_POKESELENAME			(BUFLEN_POKEMON_NAME + (5*GLOBAL_MSGLEN))
///戦闘ゲージ：「サファリボール」
#define BUFLEN_GAUGE_SAFARIBALL				(30)	//適当に大きく
///戦闘ゲージ：「のこり　○○こ」
#define BUFLEN_GAUGE_SAFARI_NOKORI			(30)	//適当に大きく



#endif
