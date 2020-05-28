
//============================================================================================
/**
 * @file	battle_common.h
 * @bfief	戦闘用ソースのヘッダで使用する定数定義のみを定義
 * @author	HisashiSogabe
 * @date	05.05.30
 */
//============================================================================================

#ifndef __BATTLE_COMMON_H_
#define __BATTLE_COMMON_H_

#define DEBUG_WIFIHISTORY

#define	BATTLE_TOWER_TRAINER_ID	(10000)				///<バトルタワーのトレーナーID

//戦闘種別フラグ（戦闘システム内の判別で使用していますBattleParamのfight_typeの指定には使わないでください）
#define	FIGHT_TYPE_1vs1			(0x00000000)		///<1vs1
#define	FIGHT_TYPE_YASEI		(0x00000000)		///<野生戦1vs1
#define	FIGHT_TYPE_TRAINER		(0x00000001)		///<トレーナー戦
#define	FIGHT_TYPE_2vs2			(0x00000002)		///<2vs2
#define	FIGHT_TYPE_SIO			(0x00000004)		///<通信対戦
#define	FIGHT_TYPE_MULTI		(0x00000008)		///<マルチ対戦
#define	FIGHT_TYPE_TAG			(0x00000010)		///<タッグ
#define	FIGHT_TYPE_SAFARI		(0x00000020)		///<サファリゾーン
#define	FIGHT_TYPE_AI			(0x00000040)		///<AIマルチ
#define	FIGHT_TYPE_TOWER		(0x00000080)		///<バトルタワー
#define	FIGHT_TYPE_MOVE			(0x00000100)		///<移動ポケモン
#define	FIGHT_TYPE_POKE_PARK	(0x00000200)		///<ポケパーク
#define	FIGHT_TYPE_GET_DEMO		(0x00000400)		///<捕獲デモ

#define	FIGHT_TYPE_DEBUG		(0x80000000)		///<デバッグ戦闘

//戦闘種別フラグ（必要なフラグをOR済みのものBattleParamのfight_type指定にはこちらを使ってください）
#define	FIGHT_TYPE_1vs1_YASEI				(FIGHT_TYPE_1vs1|FIGHT_TYPE_YASEI)						///<1vs1野生戦
#define	FIGHT_TYPE_2vs2_YASEI				(FIGHT_TYPE_2vs2|FIGHT_TYPE_MULTI|FIGHT_TYPE_AI)		///<2vs2野生戦
#define	FIGHT_TYPE_1vs1_TRAINER				(FIGHT_TYPE_1vs1|FIGHT_TYPE_TRAINER)					///<1vs1トレーナー戦
#define	FIGHT_TYPE_2vs2_TRAINER				(FIGHT_TYPE_2vs2|FIGHT_TYPE_TRAINER)					///<2vs2トレーナー戦
#define	FIGHT_TYPE_1vs1_SIO					(FIGHT_TYPE_SIO|FIGHT_TYPE_TRAINER)						///<1vs1通信トレーナー戦
#define	FIGHT_TYPE_2vs2_SIO					(FIGHT_TYPE_1vs1_SIO|FIGHT_TYPE_2vs2)					///<2vs2通信トレーナー戦
#define	FIGHT_TYPE_MULTI_SIO				(FIGHT_TYPE_2vs2_SIO|FIGHT_TYPE_MULTI)					///<2vs2通信トレーナー戦
#define	FIGHT_TYPE_AI_MULTI					(FIGHT_TYPE_2vs2_TRAINER|FIGHT_TYPE_MULTI|FIGHT_TYPE_AI)///<2vs2AIマルチ戦
#define	FIGHT_TYPE_BATTLE_TOWER_1vs1		(FIGHT_TYPE_1vs1_TRAINER|FIGHT_TYPE_TOWER)				///<1vs1バトルタワー戦
#define	FIGHT_TYPE_BATTLE_TOWER_2vs2		(FIGHT_TYPE_2vs2_TRAINER|FIGHT_TYPE_TOWER)				///<2vs2バトルタワー戦
#define	FIGHT_TYPE_BATTLE_TOWER_AI_MULTI	(FIGHT_TYPE_AI_MULTI|FIGHT_TYPE_TOWER)					///<バトルタワーAIマルチ戦
#define	FIGHT_TYPE_BATTLE_TOWER_SIO_MULTI	(FIGHT_TYPE_MULTI_SIO|FIGHT_TYPE_TOWER)					///<バトルタワー通信マルチ戦
#define	FIGHT_TYPE_TAG_BATTLE				(FIGHT_TYPE_2vs2_TRAINER|FIGHT_TYPE_TAG)				///<タッグバトル戦

///<経験値をもらえないFightType
#define	FIGHT_TYPE_NO_EXP	(FIGHT_TYPE_SIO|FIGHT_TYPE_SAFARI|FIGHT_TYPE_TOWER|FIGHT_TYPE_POKE_PARK)

///<図鑑登録をしないFightType
#define	FIGHT_TYPE_NO_ZUKAN	(FIGHT_TYPE_SIO|FIGHT_TYPE_TOWER)

///<どろぼうできるFightType
#define	FIGHT_TYPE_DOROBOU	(FIGHT_TYPE_SIO|FIGHT_TYPE_TOWER)

///<必ず逃げれるFightType
#define	FIGHT_TYPE_ESCAPE	(FIGHT_TYPE_SIO|FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK|FIGHT_TYPE_TOWER)

///<入れ替え戦にならないFightType
#define	FIGHT_TYPE_NO_IREKAE	(FIGHT_TYPE_SIO|FIGHT_TYPE_2vs2|FIGHT_TYPE_TOWER)

///<おこづかいをもらえないFightType
#define	FIGHT_TYPE_NO_MONEY	(FIGHT_TYPE_TOWER)

///<バッジチェックをしないFightType
#define	FIGHT_TYPE_NO_BADGE	(FIGHT_TYPE_SIO|FIGHT_TYPE_TOWER)

///<ポケモンにアイテムを持たせないFightType
#define	FIGHT_TYPE_POKE_NO_HAVE_ITEM	(FIGHT_TYPE_TRAINER|FIGHT_TYPE_TOWER)

///<フォルムチェンジチェックをしないFightType
#define	FIGHT_TYPE_NO_FORM_CHG	(FIGHT_TYPE_SIO|FIGHT_TYPE_TOWER|FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK)

///<アイテムAIを起動しないFightType
#define	FIGHT_TYPE_NO_ITEM_AI	(FIGHT_TYPE_SIO|FIGHT_TYPE_TOWER|FIGHT_TYPE_SAFARI|FIGHT_TYPE_AI|FIGHT_TYPE_POKE_PARK)

///<どうぐを使えないFightType
#define	FIGHT_TYPE_NO_ITEM_USE	(FIGHT_TYPE_SIO|FIGHT_TYPE_TOWER)

///<ゲージの矢印アニメをしないFightType
#define	FIGHT_TYPE_NO_ARROW_ANIME	(FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK)

///<特性をセットしないFightType
#define	FIGHT_TYPE_NO_TOKUSEI	(FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK)

///<ピンチSEチェックをしないFightType
#define	FIGHT_TYPE_NO_PINCH_SE	(FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK)

///<AI計算をするFightType
#define	FIGHT_TYPE_AI_CALC	(FIGHT_TYPE_TRAINER|FIGHT_TYPE_MOVE)

///<win_lose_flag
#define	FIGHT_WIN					(0x01)		///戦闘勝利
#define	FIGHT_LOSE					(0x02)		///戦闘負け
#define	FIGHT_DRAW					(0x03)		///戦闘引き分け
#define	FIGHT_POKE_GET				(0x04)		///ポケモン捕獲
#define	FIGHT_ESCAPE				(0x05)		///逃げた
#define	FIGHT_ENEMY_ESCAPE			(0x06)		///相手が逃げた
	
#define	FIGHT_ESCAPE_SELECT_PAUSE	(0x40)		///逃げるを選択
#define	FIGHT_ESCAPE_SELECT			(0x80)		///逃げるを選択

#define	FIGHT_ESCAPE_SELECT_OFF		(0xc0^0xff)	///逃げるを選択

//バッグ画面、リスト画面に行き来時のフェードスピード
#define	BATTLE_BAGLIST_FADE_SPEED	(-8)

///<戦闘システムのモード
#define	BW_PROC_MODE_FIGHT			(0)		///<戦闘中
#define	BW_PROC_MODE_NAMEIN			(1)		///<名前入力画面へ
#define	BW_PROC_MODE_NAMEIN_AFTER	(2)		///<名前入力画面へ
#define	BW_PROC_MODE_BAG_LIST		(3)		///<バッグ＆リスト画面

//POKEPARTY構造体の配列の添え字
#define	POKEPARTY_MINE			(0)					///<自分の手持ち
#define	POKEPARTY_ENEMY			(1)					///<相手の手持ち
#define	POKEPARTY_MINE_PAIR		(2)					///<マルチの時のパートナーの手持ち
#define	POKEPARTY_ENEMY_PAIR	(3)					///<マルチの時のパートナーの手持ち

//COMMAND_SELECTのstatusパラメータの意味
#define	COMSEL_STATUS_NONE		(0)		///<ポケモンがいない
#define	COMSEL_STATUS_ALIVE		(1)		///<ポケモンがいる（いきてる）
#define	COMSEL_STATUS_DEAD		(2)		///<ポケモンがいる（気絶）
#define	COMSEL_STATUS_NG		(3)		///<ポケモンがいる（ステータス異常）

//メッセージ用単語展開バッファ定義
#define	STR_TEMP_BUF0			(0)
#define	STR_TEMP_BUF1			(1)
#define	STR_TEMP_BUF2			(2)
#define	STR_TEMP_BUF3			(3)
#define	STR_TEMP_BUF4			(4)
#define	STR_TEMP_BUF5			(5)

///<支持するクライアント指定
#define	SIDE_ALL				(0x00)	///<起動しているクライアントすべて	
#define	SIDE_ATTACK				(0x01)	///<攻撃側クライアント
#define	SIDE_DEFENCE			(0x02)	///<防御側クライアント
#define	SIDE_MINE				(0x03)	///<自分側クライアント
#define	SIDE_ENEMY				(0x04)	///<相手側クライアント
#define	SIDE_KIZETSU			(0x05)	///<気絶したクライアント
#define	SIDE_RESHUFFLE			(0x06)	///<入れ替えを選択したクライアント
#define	SIDE_TSUIKA				(0x07)	///<追加効果のあったクライアント
#define	SIDE_TOKUSEI			(0x08)	///<特性チェックをして持っていたクライアント
#define	SIDE_MINE_1				(0x09)	///<自分側クライアント
#define	SIDE_ENEMY_1			(0x0a)	///<相手側クライアント
#define	SIDE_MINE_2				(0x0b)	///<自分側クライアント（2vs2時のパートナー）
#define	SIDE_ENEMY_2			(0x0c)	///<相手側クライアント（2vs2時のパートナー）
#define	SIDE_ATTACK_WORK		(0x0e)	///<攻撃側クライアントワーク(sp->attack_client_work)
#define	SIDE_DEFENCE_WORK		(0x0f)	///<防御側クライアントワーク(sp->defence_client_work)
#define	SIDE_ATTACK_PAIR		(0x10)	///<攻撃側クライアントのパートナー
#define	SIDE_DEFENCE_PAIR		(0x11)	///<防御側クライアントのパートナー
#define	SIDE_HUKITOBASI			(0x12)	///<ふきとばし限定
#define	SIDE_ATTACK_ENEMY		(0x13)	///<攻撃側クライアントの相手
#define	SIDE_DEFENCE_ENEMY		(0x14)	///<防御側クライアントの相手
#define	SIDE_CLIENT_WORK		(0x15)	///<sp->client_workを参照
#define	SIDE_RESHUFFLE_AFTER	(0x16)	///<入れ替えを選択したクライアント（reshuffle_sel_mons_noを参照する）

#define	SIDE_WORK				(0xff)	///<ワークに格納されている値を参照

//=========================================================================
//	ポケモンコンディションビット（AIのIF_CONDでも使用する）
//=========================================================================

#define	CONDITION_NOCHECK			(0x00000000)				//ビットのチェックをしない
#define	CONDITION_NEMURI			(0x00000007)				//眠り
#define	CONDITION_DOKU				(0x00000008)				//毒
#define	CONDITION_YAKEDO			(0x00000010)				//やけど
#define	CONDITION_KOORI				(0x00000020)				//こおり
#define	CONDITION_MAHI				(0x00000040)				//まひ
#define	CONDITION_DOKUDOKU			(0x00000080)				//どくどく
#define	CONDITION_DOKUDOKU_CNT		(0x00000f00)				//どくどくカウンタ

#define	CONDITION_SINKURO			(0x00000058)				//シンクロ
#define	CONDITION_KARAGENKI			(0x000000d8)				//からげんき
#define	CONDITION_DOKUALL			(0x00000f88)				//どく全部

#define	CONDITION_NEMURI_OFF		(0x00000007^0xffffffff)		//眠り
#define	CONDITION_DOKU_OFF			(0x00000008^0xffffffff)		//毒
#define	CONDITION_YAKEDO_OFF		(0x00000010^0xffffffff)		//やけど
#define	CONDITION_KOORI_OFF			(0x00000020^0xffffffff)		//こおり
#define	CONDITION_MAHI_OFF			(0x00000040^0xffffffff)		//まひ
#define	CONDITION_DOKUDOKU_CNT_OFF	(0x00000f00^0xffffffff)		//どくどくカウンタ
#define	CONDITION_KARAGENKI_OFF		(0x000000d8^0xffffffff)		//からげんき
#define	CONDITION_POISON_OFF		((CONDITION_DOKU|CONDITION_DOKUDOKU|CONDITION_DOKUDOKU_CNT)^0xffffffff)

#define	DOKUDOKU_COUNT				(0x00000100)

#define	CONDITION_BAD				(0x000000ff)

//=========================================================================
//	ポケモンコンディションビット（AIのIF_COND2でも使用する）
//=========================================================================

#define	CONDITION2_NOCHECK			(0x00000000)			//ビットのチェックをしない
#define	CONDITION2_KONRAN			(0x00000007)			//こんらん
#define	CONDITION2_HIRUMU			(0x00000008)			//ひるむ
#define	CONDITION2_SAWAGU			(0x00000070)			//さわぐ
#define	CONDITION2_TRIATTACK		(0x00000080)			//トライアタック
#define	CONDITION2_GAMAN			(0x00000300)			//がまん
#define	CONDITION2_ABARERU			(0x00000c00)			//あばれる
#define	CONDITION2_KEEP				(0x00001000)			//ため
#define	CONDITION2_SHIME			(0x0000e000)			//しめわざ
#define	CONDITION2_MEROMERO			(0x000f0000)			//メロメロビット
#define	CONDITION2_KIAIDAME			(0x00100000)			//きあいだめ
#define	CONDITION2_HENSHIN			(0x00200000)			//へんしん中
#define	CONDITION2_HANDOU			(0x00400000)			//はんどう中
#define	CONDITION2_IKARI			(0x00800000)			//いかり
#define	CONDITION2_MIGAWARI			(0x01000000)			//みがわり
#define	CONDITION2_MICHIDURE		(0x02000000)			//みちづれ
#define	CONDITION2_KUROIMANAZASHI	(0x04000000)			//くろいまなざし
#define	CONDITION2_AKUMU			(0x08000000)			//あくむ
#define	CONDITION2_NOROI			(0x10000000)			//のろい
#define	CONDITION2_MIYABURU			(0x20000000)			//みやぶる
#define	CONDITION2_MARUKUNARU		(0x40000000)			//まるくなる
#define	CONDITION2_ICHAMON			(0x80000000)			//いちゃもん

#define	CONDITION2_KONRAN_OFF		(0x00000007^0xffffffff)	//こんらん
#define	CONDITION2_HIRUMU_OFF		(0x00000008^0xffffffff)	//ひるむ
#define	CONDITION2_SAWAGU_OFF		(0x00000070^0xffffffff)	//さわぐ
#define	CONDITION2_TRIATTACK_OFF	(0x00000080^0xffffffff)	//トライアタック
#define	CONDITION2_GAMAN_OFF		(0x00000300^0xffffffff)	//がまん
#define	CONDITION2_ABARERU_OFF		(0x00000c00^0xffffffff)	//あばれる
#define	CONDITION2_KEEP_OFF			(0x00001000^0xffffffff)	//ため
#define	CONDITION2_SHIME_OFF		(0x0000e000^0xffffffff)	//しめわざ
#define	CONDITION2_MEROMERO_OFF		(0x000f0000^0xffffffff)	//メロメロビット
#define	CONDITION2_KIAIDAME_OFF		(0x00100000^0xffffffff)	//きあいだめ
#define	CONDITION2_HENSHIN_OFF		(0x00200000^0xffffffff)	//へんしん中
#define	CONDITION2_HANDOU_OFF		(0x00400000^0xffffffff)	//はんどう中
#define	CONDITION2_IKARI_OFF		(0x00800000^0xffffffff)	//いかり
#define	CONDITION2_MIGAWARI_OFF		(0x01000000^0xffffffff)	//みがわり
#define	CONDITION2_MICHIDURE_OFF	(0x02000000^0xffffffff)	//みちづれ
#define	CONDITION2_KUROIMANAZASHI_OFF (0x04000000^0xffffffff)	//くろいまなざし
#define	CONDITION2_AKUMU_OFF		(0x08000000^0xffffffff)	//あくむ
#define	CONDITION2_NOROI_OFF		(0x10000000^0xffffffff)	//のろい
#define	CONDITION2_MIYABURU_OFF		(0x20000000^0xffffffff)	//みやぶる
#define	CONDITION2_ICHAMON_OFF		(0x80000000^0xffffffff)	//いちゃもん

#define	CONDITION2_BATON_TOUCH_ON	(CONDITION2_KIAIDAME|CONDITION2_KUROIMANAZASHI|\
									 CONDITION2_KONRAN|CONDITION2_NOROI|CONDITION2_MIGAWARI)

#define	KONRAN_COUNT				(0x00000001)
#define	SAWAGU_COUNT				(0x00000010)
#define	GAMAN_TURN					(0x00000200)
#define	GAMAN_COUNT					(0x00000100)
#define	ABARERU_COUNT				(0x00000400)
#define	SHIME_COUNT					(0x00002000)
#define	HOROBINOUTA_COUNT			(0x40000000)

#define	KONRAN_SHIFT				(0)
#define	SAWAGU_SHIFT				(4)
#define	GAMAN_SHIFT					(8)
#define	ABARERU_SHIFT				(10)
#define	SHIME_SHIFT					(13)
#define	MEROMERO_SHIFT				(16)
#define	HOROBINOUTA_SHIFT			(30)

#define	KOBAN_MAX					(0xffff)		//ねこにこばんでもらえるお金のMAX

//======================================================================================================

#define	HP_KETA_MAX			(3)		///<HPの最大桁数
#define	LEVEL_KETA_MAX		(3)		///<レベルの最大桁数

#define	BATTLE_MESSAGE_BUF_SIZE		(2*160)		///<戦闘用メッセージ展開領域サイズ（１６０文字分）
#define	BATTLE_STR_TEMP_BUF_SIZE	(2*20)		///<戦闘用タグ展開領域サイズ（２０文字分）

#define	WAZA_TEMOTI_MAX		(4)		///<1体のポケモンがもてる技の最大値
#define	POKEMON_TEMOTI_MAX	(6)		///<手持ちに持てるポケモンの最大値
#define	POKEMON_ABIRITY_MAX	(8)		///<ポケモンの能力値種類の最大値
#define	ID_MAX				(4)		///<通信IDMAX
#define	CLIENT_MAX			(4)		///<同時に起動するクライアントの最大数
#define	SERVER_QUE_MAX		(16)	///<クライアントへの命令キューの最大数（4では絶対足りない）
#define	BUF_SIZE			(256)	///<サーバ、クライアントの命令、応答格納バッファのサイズ

#define	NONE_CLIENT_NO		(0xff)	///<各ClientNo格納ワークの初期値

#define GROUND_MINE			(0)		///<自分側地面
#define GROUND_ENEMY		(1)		///<敵側地面
#define GROUND_MAX			(2)		///<地面の最大数

#define	BATTLE_ALLOC_SIZE	(0xb0000)	///<戦闘で使用するヒープサイズ

#define BATTLE_VRAM_TRANSFER_TASK_NUM	(64)	///<Vram転送マネージャータスク数

#define	BATTLE_SIO_BUF_SIZE	(0x1000)	///<戦闘通信用バッファサイズ

#define	EXCHR_BUFFER_SIZE	(32*10*10)	///<技エフェクト用キャラ展開バッファサイズ

#define BATTLE_3DBG_PRIORITY		(1)//元々(2)	///<3D面のBGプライオリティ
#define BATTLE_BGPRI_WINDOW			(0)	///<ウィンドウ面のBGプライオリティ
#define BATTLE_BGPRI_EFFECT			(1)	///<エフェクト面のBGプライオリティ
#define BATTLE_BGPRI_BACKGROUND		(3)	///<背景面のBGプライオリティ

#define BATTLE_FRAME_WINDOW			(GF_BGL_FRAME1_M)	///<フレーム面：ウィンドウ
#define BATTLE_FRAME_EFFECT			(GF_BGL_FRAME2_M)	///<フレーム面：エフェクト
#define BATTLE_FRAME_BACKGROUND		(GF_BGL_FRAME3_M)	///<フレーム面：背景

#define BATTLE_BGNO_WINDOW			(1)					///<BG番号：ウィンドウ
#define BATTLE_BGNO_EFFECT			(2)					///<BG番号：エフェクト
#define BATTLE_BGNO_BACKGROUND		(3)					///<BG番号：背景

//HPゲージがスライドインしてくるまでのウエイト
#define	HP_GAUGE_IN_WAIT			(4)

//技の分類に関する定義
#define	KIND_BUTSURI	(0)			///<物理攻撃
#define	KIND_TOKUSYU	(1)			///<特殊攻撃
#define	KIND_HENKA		(2)			///<状態変化

//技の効果範囲に関する定義
#define	RANGE_NORMAL		(0x0000)		//自分以外の3体
#define	RANGE_NONE			(0x0001)		//選択なし
#define	RANGE_RANDOM		(0x0002)		//ランダム
#define	RANGE_DOUBLE		(0x0004)		//２体に当たる
#define	RANGE_TRIPLE		(0x0008)		//自分以外3体に当たる
#define	RANGE_MINE			(0x0010)		//自分選択
#define	RANGE_MINE_DOUBLE	(0x0020)		//自分２体選択
#define	RANGE_FIELD			(0x0040)		//場にかかる
#define	RANGE_MAKIBISHI		(0x0080)		//まきびし専用
#define	RANGE_TEDASUKE		(0x0100)		//てだすけ専用
#define	RANGE_TUBOWOTUKU	(0x0200)		//つぼをつく専用
#define	RANGE_SAKIDORI		(0x0400)		//さきどり専用

#define	RANGE_NO_DIR	(RANGE_DOUBLE|RANGE_NONE|RANGE_MINE|RANGE_RANDOM|RANGE_TRIPLE|RANGE_FIELD)

#define	RANGE_MINE_DIR	(RANGE_NONE|RANGE_MINE|RANGE_FIELD|RANGE_TUBOWOTUKU)

//技覚えに関する定義
#define	NO_WAZA_OBOE		(0x0000)		//技を覚えなかった
#define	NO_WAZA_SET			(0xffff)		//技のセットができなかったときの返り値
#define	SAME_WAZA_SET		(0xfffe)		//すでに覚えていた技のときの返り値

//ポケモンや技のタイプ定義
#define	NORMAL_TYPE			(0)
#define	BATTLE_TYPE			(1)
#define	HIKOU_TYPE			(2)
#define	POISON_TYPE			(3)
#define	JIMEN_TYPE			(4)
#define	IWA_TYPE			(5)
#define	MUSHI_TYPE			(6)
#define	GHOST_TYPE			(7)
#define	METAL_TYPE			(8)
#define	HATE_TYPE			(9)
#define	FIRE_TYPE			(10)
#define	WATER_TYPE			(11)
#define	KUSA_TYPE			(12)
#define	ELECTRIC_TYPE		(13)
#define	SP_TYPE				(14)
#define	KOORI_TYPE			(15)
#define	DRAGON_TYPE			(16)
#define	AKU_TYPE			(17)

#define	POKE_WAZA_TYPE_MAX	(17)

///<通信対戦以外での起動されたクライアントのClientNo定義
#define	CLIENT_NO_MINE		(0)
#define	CLIENT_NO_ENEMY		(1)
#define	CLIENT_NO_MINE2		(2)
#define	CLIENT_NO_ENEMY2	(3)

//ポケモンの立ち位置指定(1vs1)
//			 BB
//
//	 AA
//ポケモンの立ち位置指定(2vs2)
//			D	B
//
//	A　C
#define	CLIENT_TYPE_AA	(0)
#define	CLIENT_TYPE_BB	(1)

#define	CLIENT_TYPE_A	(2)
#define	CLIENT_TYPE_B	(3)
#define	CLIENT_TYPE_C	(4)
#define	CLIENT_TYPE_D	(5)

#define	CLIENT_ENEMY_FLAG	(0x01)	///<client_typeの1bit目が立っていれば敵側だと判断できる

#define	CLIENT_TYPE_MAX		(6)
#define	CLIENT_TYPE_NONE	(0xff)	///<ClientTypeなし

//トレーナーの立ち位置（通信部屋内）
//
//	A		B
//
//	C		D
//
#define	TRAINER_STAND_A		(0)
#define	TRAINER_STAND_B		(1)
#define	TRAINER_STAND_C		(2)
#define	TRAINER_STAND_D		(3)

//クライアントの起動状態フラグ
#define	CLIENT_BOOT_NORMAL	(0x00)	///<通常起動
#define	CLIENT_BOOT_AI		(0x01)	///<AI起動
#define	CLIENT_BOOT_SIO		(0x02)	///<通信のクローン起動

//エンカウント時の初期位置
#define	ENCOUNT_X_TYPE_AA	(256+80)
#define	ENCOUNT_Y_TYPE_AA	(104+8)
#define	ENCOUNT_Z_TYPE_AA	(-0x200)

#define	ENCOUNT_X_TYPE_BB	(-80)
#define	ENCOUNT_Y_TYPE_BB	(50)
#define	ENCOUNT_Z_TYPE_BB	(-0x280)

#define	ENCOUNT_X_TYPE_A	(256+60)
#define	ENCOUNT_Y_TYPE_A	(104+8)
#define	ENCOUNT_Z_TYPE_A	(ENCOUNT_Z_TYPE_AA)

#define	ENCOUNT_X_TYPE_B	(-60)
#define	ENCOUNT_Y_TYPE_B	(50)
#define	ENCOUNT_Z_TYPE_B	(-100)

#define	ENCOUNT_X_TYPE_C	(256+100)
#define	ENCOUNT_Y_TYPE_C	(ENCOUNT_Y_TYPE_A + 8)
#define	ENCOUNT_Z_TYPE_C	(0)

#define	ENCOUNT_X_TYPE_D	(-100)
#define	ENCOUNT_Y_TYPE_D	(ENCOUNT_Y_TYPE_B - 8)
#define	ENCOUNT_Z_TYPE_D	(ENCOUNT_Z_TYPE_BB)

//登場時の位置(1vs1)
#define	APPEAR_X_TYPE_AA	(64)
#define	APPEAR_Y_TYPE_AA	(104+8)
#define	APPEAR_Z_TYPE_AA	(ENCOUNT_Z_TYPE_AA)

#define	APPEAR_X_TYPE_BB	(256-64)
#define	APPEAR_Y_TYPE_BB	(48)
#define	APPEAR_Z_TYPE_BB	(ENCOUNT_Z_TYPE_BB)

//登場時の位置(2vs2)
#define	APPEAR_X_TYPE_A	(40)
#define	APPEAR_Y_TYPE_A	(ENCOUNT_Y_TYPE_A)
#define	APPEAR_Z_TYPE_A	(ENCOUNT_Z_TYPE_A)

#define	APPEAR_X_TYPE_B	(256-40)
#define	APPEAR_Y_TYPE_B	(ENCOUNT_Y_TYPE_B)
#define	APPEAR_Z_TYPE_B	(ENCOUNT_Z_TYPE_B)

#define	APPEAR_X_TYPE_C	(80)
#define	APPEAR_Y_TYPE_C	(ENCOUNT_Y_TYPE_C)
#define	APPEAR_Z_TYPE_C	(ENCOUNT_Z_TYPE_C)

#define	APPEAR_X_TYPE_D	(256-80)
#define	APPEAR_Y_TYPE_D	(ENCOUNT_Y_TYPE_D)
#define	APPEAR_Z_TYPE_D	(ENCOUNT_Z_TYPE_D)

//スライドINの初期位置
#define	SLIDEIN_X_TYPE_AA	(-80)
#define	SLIDEIN_Y_TYPE_AA	(ENCOUNT_Y_TYPE_AA)
#define	SLIDEIN_Z_TYPE_AA	(ENCOUNT_Z_TYPE_AA)
#define	SLIDEIN_X_TYPE_BB	(256+80)
#define	SLIDEIN_Y_TYPE_BB	(ENCOUNT_Y_TYPE_BB)
#define	SLIDEIN_Z_TYPE_BB	(ENCOUNT_Z_TYPE_AA)

//トレーナーメッセージアクション時の位置
#define	MSG_X_TYPE_AA	(32)
#define	MSG_X_TYPE_BB	(256-32)

//登場エフェクトの拡縮値
#define	AFF_APPEAR_X_S	(0x000)		///<小さいとき
#define	AFF_APPEAR_Y_S	(0x000)		///<小さいとき
#define	AFF_APPEAR_X_B	(0x100)		///<元の大きさ
#define	AFF_APPEAR_Y_B	(0x100)		///<元の大きさ

//画面外の位置
#define	FRAME_OUT_X_L	(-40)
#define	FRAME_OUT_X_R	(256+40)

//ボールを投げる位置
#define	BALL_THROW_X_L	(-20)
#define	BALL_THROW_X_R	(256+20)

//ポケモン選択時に1体目選択がない定義
#define	NO_DOUBLE_SEL	(6)

//=========================================================================
//		HPゲージでのステータス表示用定義
//=========================================================================
///< 検索用 ___STATUS_EFFECT____
#define	STATUS_NORMAL	(0)		//状態異常なし
#define	STATUS_NEMURI	(1)		//眠り
#define	STATUS_DOKU		(2)		//毒
#define	STATUS_YAKEDO	(3)		//やけど
#define	STATUS_KOORI	(4)		//こおり
#define	STATUS_MAHI		(5)		//まひ

// =========================================
//
// ステータスエフェクト定義(表示の連番を引き継ぐ)
//
// =========================================
#define	STATUS_KONRAN			(6)		///< こんらん
#define	STATUS_MEROMERO			(7)		///< メロメロ

#define	STATUS_LVUP				(8)		///< LvUp
#define	STATUS_ITEM_TR			(9)		///< トレーナー アイテム
#define	STATUS_ITEM_POKE		(10)	///< oポケモン きのみ
#define	STATUS_REA				(11)	///< oレアエフェクト

///< 能力
#define STATUS_EFF_UP			(12)	///< 能力上昇
#define STATUS_EFF_DOWN			(13)	///< 能力下降
#define STATUS_EFF_RECOVER		(14)	///< 回復
#define STATUS_EFF_MIGAWARI_OUT	(15)	///< o画面外に
#define STATUS_EFF_MIGAWARI_IN	(16)	///< o画面内に
#define STATUS_EFF_ITEM_POUCH	(17)	///< oエネコしっぽとピッピ人形

///< 天気（STARTとENDは、エフェクト起動時のHPゲージON/OFFを範囲で判定するために用いている）
#define STATUS_WEATHER_START	(18)	///< 天候エフェクト開始ナンバー
#define STATUS_WEATHER_MIST		(18)	///< 天候 霧
#define STATUS_WEATHER_RAIN		(19)	///< 天候 雨
#define STATUS_WEATHER_ICE		(20)	///< 天候 あられ
#define STATUS_WEATHER_SAND		(21)	///< 天候 砂あらし
#define STATUS_WEATHER_SUN		(22)	///< 天候 ひざし
#define STATUS_WEATHER_END		(22)	///< 天候エフェクト終了ナンバー

///< その他
#define STATUS_ACTION_DOLL_ON	(25)	///< o動き みがわりおちてくる
#define STATUS_ACTION_DOLL_OFF	(26)	///< 動き みがわりOFF
#define STATUS_ACTION_JOY		(27)	///< 動き ちょいちょい
#define STATUS_ACTION_EAT		(28)	///< 動き パクパク
#define STATUS_ACTION_ANGER		(29)	///< 動き ピキピキ

///< ターンごと
#define STATUS_DAMAGE_NOROI		(30)	///< ターン のろい
#define STATUS_DAMAGE_AKUMU		(31)	///< ターン あくむ
#define STATUS_DAMAGE_YADORIGI	(32)	///< ターン やどりぎ
#define STATUS_DAMAGE_SIMETUKE	(33)	///< ターン しめつける
#define STATUS_DAMAGE_MAKITUKU	(34)	///< ターン まきつく
#define STATUS_DAMAGE_HONOO		(35)	///< ターン ほのおのうず
#define STATUS_DAMAGE_MAGUMA	(36)	///< ターン マグマストーム
#define STATUS_DAMAGE_KARA		(37)	///< ターン からではさむ
#define STATUS_DAMAGE_UZUSIO	(38)	///< ターン うずしお
#define STATUS_DAMAGE_SUNA		(39)	///< ターン すなじごく
#define STATUS_DAMAGE_NEWOHARU	(40)	///< ターン ねをはる

//=========================================================================
//		CL_ACT用の定数定義
//=========================================================================

///メイン	OAM管理領域・開始
#define BATTLE_OAM_START_MAIN			(0)
///メイン	OAM管理領域・終了
#define BATTLE_OAM_END_MAIN				(128)
///メイン	アフィン管理領域・開始
#define BATTLE_OAM_AFFINE_START_MAIN	(0)
///メイン	アフィン管理領域・終了
#define BATTLE_OAM_AFFINE_END_MAIN		(32)
///サブ	OAM管理領域・開始
#define BATTLE_OAM_START_SUB			(0)
///サブ	OAM管理領域・終了
#define BATTLE_OAM_END_SUB				(128)
///サブ アフィン管理領域・開始
#define BATTLE_OAM_AFFINE_START_SUB		(0)
///サブ	アフィン管理領域・終了
#define BATTLE_OAM_AFFINE_END_SUB		(32)

///キャラマネージャ：キャラクタID管理数(上画面＋下画面)
#define BATTLE_CHAR_MAX					(48 + 48)
///キャラマネージャ：メイン画面サイズ(byte単位)
#define BATTLE_CHAR_VRAMSIZE_MAIN		(1024 * 0x40)	//64K
///キャラマネージャ：サブ画面サイズ(byte単位)
#define BATTLE_CHAR_VRAMSIZE_SUB		(512 * 0x20)	//32K

///メイン画面＋サブ画面で使用するアクター総数
#define BATTLE_ACTOR_MAX				(64 + 64)	//メイン画面 + サブ画面

///サブサーフェースY(fx32)
#define BATTLE_SUB_ACTOR_DISTANCE		((192 + 80) << FX32_SHIFT)
///サブサーフェースY(int)
#define BATTLE_SUB_ACTOR_DISTANCE_INTEGER		(BATTLE_SUB_ACTOR_DISTANCE >> FX32_SHIFT)

///OBJで使用するパレット本数(上画面＋下画面)
#define BATTLE_OAM_PLTT_MAX				(16 + 16)

///転送モード 3D = 0 main = 1 sub = 2 main/sub = 3
#define BATTLE_OAM_VRAM_TRANS			(3)

///OAMリソース：キャラ登録最大数(メイン画面 + サブ画面)
#define BATTLE_OAMRESOURCE_CHAR_MAX			(BATTLE_CHAR_MAX)
///OAMリソース：パレット登録最大数(メイン画面 + サブ画面)
#define BATTLE_OAMRESOURCE_PLTT_MAX			(BATTLE_OAM_PLTT_MAX)
///OAMリソース：セル登録最大数
#define BATTLE_OAMRESOURCE_CELL_MAX			(64)
///OAMリソース：セルアニメ登録最大数
#define BATTLE_OAMRESOURCE_CELLANM_MAX		(64)
///OAMリソース：マルチセル登録最大数
#define BATTLE_OAMRESOURCE_MCELL_MAX		(8)
///OAMリソース：マルチセルアニメ登録最大数
#define BATTLE_OAMRESOURCE_MCELLANM_MAX		(8)

///OBJパレット：PFD管理本数(パレット単位)
#define BATTLE_MAIN_OBJPAL_NUM				(16 - 2)	//-2 = 通信アイコン＋ローカライズ用
///OBJパレット：PFD管理本数(カラー単位)
#define BATTLE_MAIN_OBJPAL_COLOR_NUM		(BATTLE_MAIN_OBJPAL_NUM * 16)
///OBJパレット：バイトサイズ
#define BATTLE_MAIN_OBJPAL_SIZE				(BATTLE_MAIN_OBJPAL_COLOR_NUM * sizeof(u16))
///OBJパレット：フェードbit
#define BATTLE_MAIN_OBJPAL_FADEBIT			(0x3fff)

//==============================================================================
//	パレット展開場所定義
//==============================================================================
///エフェクトBGパレット０
#define BATTLE_PAL_EFF_0				(8)
///エフェクトBGパレット１
#define BATTLE_PAL_EFF_1				(9)

//=========================================================================
//		進化条件定義
//=========================================================================
//
#define	SHINKA_NONE					(0)
#define	SHINKA_FRIEND_HIGH			(1)
#define	SHINKA_FRIEND_HIGH_NOON		(2)
#define	SHINKA_FRIEND_HIGH_NIGHT	(3)
#define	SHINKA_LEVELUP				(4)
#define	SHINKA_TUUSHIN				(5)
#define	SHINKA_TUUSHIN_ITEM			(6)
#define	SHINKA_ITEM					(7)
#define	SHINKA_SPECIAL_POW			(8)
#define	SHINKA_SPECIAL_EVEN			(9)
#define	SHINKA_SPECIAL_DEF			(10)
#define	SHINKA_SPECIAL_RND_EVEN		(11)
#define	SHINKA_SPECIAL_RND_ODD		(12)
#define	SHINKA_SPECIAL_LEVELUP		(13)
#define	SHINKA_SPECIAL_NUKENIN		(14)
#define	SHINKA_SPECIAL_BEAUTIFUL	(15)
#define	SHINKA_ITEM_MALE			(16)
#define	SHINKA_ITEM_FEMALE			(17)
#define	SHINKA_SOUBI_NOON			(18)
#define	SHINKA_SOUBI_NIGHT			(19)
#define	SHINKA_WAZA					(20)
#define	SHINKA_POKEMON				(21)
#define	SHINKA_MALE					(22)
#define	SHINKA_FEMALE				(23)
#define	SHINKA_PLACE_TENGANZAN		(24)
#define	SHINKA_PLACE_KOKE			(25)
#define	SHINKA_PLACE_ICE			(26)

//=========================================================================
//		battle_status_flag
//=========================================================================

#define	BATTLE_STATUS_FLAG_FIRST_BATTLE		(0x00000001)	///<最初のデモ戦闘
#define	BATTLE_STATUS_FLAG_MITSUNURI_BATTLE	(0x00000002)	///<みつぬりでのエンカウント
#define	BATTLE_STATUS_FLAG_NO_ESCAPE_YASEI	(0x00000004)	///<野生戦でもにげれない
#define	BATTLE_STATUS_FLAG_DENSETSU_BATTLE	(0x00000008)	///<伝説系とのエンカウント

#define	BATTLE_STATUS_FLAG_DEBUG_BIT		(0xf0000000)	///<デバッグ用フラグ（サーババージョン）
#define	BATTLE_STATUS_FLAG_AUTO_BATTLE		(0x08000000)	///<デバッグ用フラグ
#define	BATTLE_STATUS_FLAG_NO_HP_DEC		(0x04000000)	///<デバッグ用フラグ
#define	BATTLE_STATUS_FLAG_NO_PP_DEC		(0x02000000)	///<デバッグ用フラグ

//=========================================================================
//		HP回復系アイテム用定義
//=========================================================================
#define	HP_MAX_RECOVER				(255)		//HP全回復
#define	HP_HALF_RECOVER				(254)		//HP半回復
#define	HP_25PER_RECOVER			(253)		//HPMAXの25%回復

//=========================================================================
//		レギュレーションフラグ
//=========================================================================
#define	REGULATION_FLAG_LITTLE_CUP	(0x00000001)	//リトルカップレギュレーション

//=========================================================================
//アセンブラでincludeされている場合は、下の宣言を無視できるようにifndefで囲んである
#ifndef	__ASM_NO_DEF_

//CT_AppearPosGetのpos_id定義
enum{
	POS_ID_X=0,
	POS_ID_Y,
	POS_ID_Z
};

//クライアントからの返答コード
enum{
	SELECT_FIGHT_COMMAND=1,
	SELECT_ITEM_COMMAND,
	SELECT_POKEMON_COMMAND,
	SELECT_ESCAPE_COMMAND,
	SELECT_DEBUG_ESCAPE_COMMAND,		//デバッグ用に強制的に逃げるコマンド
	SELECT_DEBUG_WIN_ESCAPE_COMMAND,	//デバッグ用に強制的に逃げるコマンド
	//サファリの場合
	SELECT_SAFARI_BALL = SELECT_FIGHT_COMMAND,
	SELECT_SAFARI_ESA = SELECT_ITEM_COMMAND,
	SELECT_SAFARI_DORO = SELECT_POKEMON_COMMAND,
	SELECT_SAFARI_ESCAPE = SELECT_ESCAPE_COMMAND,
	SELECT_SAFARI_YOUSUMI,
	//ポケパークの場合
	SELECT_POKEPARK_BALL = SELECT_FIGHT_COMMAND,
	SELECT_POKEPARK_ESCAPE = SELECT_ESCAPE_COMMAND,
	
	//技選択
	SELECT_SKILL_1 = 1,
	SELECT_SKILL_2,
	SELECT_SKILL_3,
	SELECT_SKILL_4,

	//ポケモン選択(リスト)
	SELECT_POKE_1 = 1,
	SELECT_POKE_2,
	SELECT_POKE_3,
	SELECT_POKE_4,
	SELECT_POKE_5,
	SELECT_POKE_6,

	//ポケモン選択(技ターゲット)	後ろのアルファベットはクライアントタイプの位置に対応
	SELECT_TARGET_A = 1,
	SELECT_TARGET_B,
	SELECT_TARGET_C,
	SELECT_TARGET_D,
	
	SELECT_CANCEL=0xff
};

//進化条件
enum{
	LEVELUP_SHINKA=0,		//レベルアップによる進化
	TUUSHIN_SHINKA,			//通信による進化
	ITEM_SHINKA,			//アイテムによる進化
	ITEM_SHINKA_CHECK,		//アイテムによる進化（かわらずのいしを装備していてもチェックはする）
};

#define	POKE_LEVEL_MAX		(100)		//レベルMAX
#define	SHINKA_FRIEND		(220)		//進化に必要ななつき度
#define	FRIEND_MAX			(255)		//なつき度MAX値
#define	STYLE_MAX			(255)		//かっこよさMAX値
#define	BEAUTIFUL_MAX		(255)		//うつくしさMAX値
#define	CUTE_MAX			(255)		//かわいさMAX値
#define	CLEVER_MAX			(255)		//かしこさMAX値
#define	STRONG_MAX			(255)		//たくましさMAX値
#define	FUR_MAX				(255)		//毛艶MAX値
#define	PP_COUNT_MAX		(3)			//pp_countMAX値
#define	POW_RND_MAX			(31)		//パワー乱数MAX値

//エフェクトコール用のフラグ
#define	EFFTYPE_WAZA		(0)			//技エフェクト
#define	EFFTYPE_STATUS		(1)			//ステータスエフェクト

//============================================================================================
//	構造体宣言
//============================================================================================

typedef struct _POKEPARTY POKEPARTY;
typedef struct _MYSTATUS MYSTATUS;
typedef struct _MYITEM MYITEM;
typedef struct _ZUKAN_WORK ZUKAN_WORK;
typedef struct _BOX_DATA BOX_DATA;
typedef struct _BAG_CURSOR	BAG_CURSOR;
typedef struct PERAPVOICE	PERAPVOICE;
typedef struct _CONFIG	CONFIG;
typedef struct _POKETCH_DATA POKETCH_DATA;

#include "poketool/poke_tool.h"
#include "field/tvtopic_battle.h"		//TVWATCH_BATTLE_WORK
#include "system/pms_data.h"
#include "system/palanm.h"
#include "savedata/record.h"
#include "savedata/fnote_mem.h"

#ifndef	__ASM_NO_DEF_	// ↓これ以降は、アセンブラでは無視
#include "savedata/wifihistory.h"
#include "savedata/friendlist.h"
#endif

//トレーナーデータパラメータ
typedef struct{
	u8			data_type;					//データタイプ
	u8			tr_type;					//トレーナー分類
	u8			tr_gra;						//トレーナーグラフィック
	u8			poke_count;					//所持ポケモン数

	u16			use_item[4];				//使用道具

	u32			aibit;						//AIパターン
	u32			fight_type;					//戦闘タイプ（1vs1or2vs2）

	STRCODE		name[BUFLEN_PERSON_NAME];	//トレーナー名
	PMS_DATA	win_word;
	PMS_DATA	lose_word;
}TRAINER_DATA;


//トレーナー持ちポケモンパラメータ
enum{
	DATATYPE_NORMAL=0,
	DATATYPE_WAZA,
	DATATYPE_ITEM,
	DATATYPE_MULTI
};

//トレーナー持ちポケモンパラメータ（データタイプノーマル）
typedef	struct
{
	u16		pow;			//セットするパワー乱数(u8でOKだけど4バイト境界対策）
	u16		level;			//セットするポケモンのレベル
	u16		monsno;			//セットするポケモン
}POKEDATA_TYPE_NORMAL;

//トレーナー持ちポケモンパラメータ（データタイプ技）
typedef	struct
{
	u16		pow;			//セットするパワー乱数(u8でOKだけど4バイト境界対策）
	u16		level;			//セットするポケモンのレベル
	u16		monsno;			//セットするポケモン
	u16		waza[4];		//持ってる技
}POKEDATA_TYPE_WAZA;

//トレーナー持ちポケモンパラメータ（データタイプアイテム）
typedef	struct
{
	u16		pow;			//セットするパワー乱数(u8でOKだけど4バイト境界対策）
	u16		level;			//セットするポケモンのレベル
	u16		monsno;			//セットするポケモン
	u16		itemno;			//セットするアイテム
}POKEDATA_TYPE_ITEM;

//トレーナー持ちポケモンパラメータ（データタイプマルチ）
typedef	struct
{
	u16		pow;			//セットするパワー乱数(u8でOKだけど4バイト境界対策）
	u16		level;			//セットするポケモンのレベル
	u16		monsno;			//セットするポケモン
	u16		itemno;			//セットするアイテム
	u16		waza[4];		//持ってる技
}POKEDATA_TYPE_MULTI;

typedef struct
{
	int		total_turn;		//総ターン数
	int		total_hinshi;	//総瀕死数
	int		total_damage;	//総ダメージ数
}BATTLE_TOWER_RECORD;

//戦闘開始パラメータ
typedef struct{
	u32					fight_type;					///<戦闘種別フラグ
	POKEPARTY			*poke_party[CLIENT_MAX];	///<手持ちポケモンデータ
	int					win_lose_flag;				///<勝ち負けフラグ
	int					trainer_id[CLIENT_MAX];		///<トレーナーのID
	TRAINER_DATA		trainer_data[CLIENT_MAX];	///<トレーナーデータ
	MYSTATUS			*my_status[CLIENT_MAX];		///<自キャラデータ
	MYITEM				*my_item;					///<持ちアイテムデータ
	BAG_CURSOR			*bag_cursor;				///<バッグのカーソルデータ
	ZUKAN_WORK			*zw;						///<図鑑ワーク
	BOX_DATA			*box;						///<ボックスデータ
	PERAPVOICE			*poke_voice[CLIENT_MAX];	///<ポケモンの鳴き声データ
	POKETCH_DATA		*poketch_data;				///<ポケッチデータ
#ifdef DEBUG_WIFIHISTORY
	WIFI_HISTORY		*wifihistory;				///<世界通信履歴データ
#endif
	CONFIG				*config;					///<ゲームコンフィグ
	TVWATCH_BATTLE_WORK * TVWatchBattleWork;		///<テレビ：捕獲番組用
	BATTLE_TOWER_RECORD	btr;						///<バトルタワー成績用ワーク
	RECORD				*record;					///<カウントアップワーク
	FNOTE_DATA			*fnote_data;				///<冒険ノートワーク
	FRIEND_LIST			*friendlist;				///<ともだちグループポインタ
	int					bg_id;						///<背景ID
	int					ground_id;					///<地形ID
	int					place_id;					///<地域名ID
	int					zone_id;					///<ゾーンID
	int					time_zone;					///<時間帯定義
	int					shinka_place_mode;			///<場所進化情報（SHINKA_PLACE～）
	int					contest_see_flag;			///<コンテストを見たかどうかのフラグ
	int					mizuki_flag;				///<ミズキにあったかどうかのフラグ
//	EVENT_DATA			event_data;					///<イベントデータ
//	TIME				time;						///<時間
	int					get_pokemon_client;			///<捕獲したポケモンのClientNo（POKEPARTY_ENEMYかPOKEPARTY_ENEMY_PAIR）
	int					weather;					///<天候
	int					level_up_flag;				///<レベルアップしたポケモンフラグ（進化チェックをする）
	u32					server_version[CLIENT_MAX];	///<戦闘サーバプログラムのバージョン（通信対戦時に使用）
	u32					battle_status_flag;			///<戦闘内分岐用フラグ
	int					safari_ball;				///<サファリボールの数
	u32					regulation_flag;			///<レギュレーションフラグ
	void				*work;						///<汎用的に使用するためのポインタワーク
}BATTLE_PARAM;

typedef struct{
	BATTLE_PARAM		*bp;
	GF_BGL_INI			*bgl;
	GF_BGL_BMPWIN		*win;
	PALETTE_FADE_PTR	pfd;									///<パレットフェードシステムワークへのポインタ
	FRIEND_LIST			*recv_flist[4];							///<フレンドリスト受信バッファ（受信後に解放）
	u8					sio_send_buffer[BATTLE_SIO_BUF_SIZE];	///<通信送信バッファ
	u8					send_count;
	u8					seq_no;
	u16					time_out_count;							///<通信タイムアウト用カウンタ
	void				*time_icon;								///<通信待機中の時計アイコンタスク
}BATTLE_SIO_WORK;

///<手持ちポケモンのサーバ用構造体
typedef struct pokemon_server_param POKEMON_SERVER_PARAM;

///<対戦録画用パラメータ構造体宣言
typedef struct record_param RECORD_PARAM;

///<戦闘システムワーク構造体
typedef struct battle_work BATTLE_WORK;

///<サーバ用パラメータ構造体宣言
typedef struct server_param SERVER_PARAM;

///<クライアント用パラメータ構造体宣言
typedef struct client_param CLIENT_PARAM;

///<FieldCondition用カウンタ構造体宣言
typedef struct field_condition_count FIELD_CONDITION_COUNT;

///<SideCondition用パラメータ構造体宣言
typedef struct side_condition_work	SIDE_CONDITION_WORK;

///<OneTurnFlag用パラメータ構造体宣言
typedef struct one_turn_flag	ONE_TURN_FLAG;

///<OneSelfTurnFlag用パラメータ構造体宣言
typedef struct one_self_turn_flag	ONE_SELF_TURN_FLAG;

///<WazaOutCheckFlag用パラメータ構造体宣言
typedef struct waza_out_check_flag	WAZA_OUT_CHECK_FLAG;

///<技効果用パラメータ構造体宣言
typedef struct waza_kouka_work	WAZA_KOUKA_WORK;

///<SkillIntpで使用されるタスク用ワークへのポインタ
typedef	struct tcb_skill_intp_work	TCB_SKILL_INTP_WORK;

///<メッセージ表示用ワーク構造体
typedef struct message_param_data MESSAGE_PARAM_DATA;

///<進化デモワーク構造体
typedef struct shinka_work SHINKA_WORK;

///<トレーナーAI構造体
typedef struct ai_work_tbl AI_WORK_TBL;

//戦闘用関数定義
typedef	void	(*btFunc)(BATTLE_WORK *battle_work);
typedef	void	(*svFunc)(BATTLE_WORK *battle_work,SERVER_PARAM *sp);
typedef	void	(*clFunc)(BATTLE_WORK *battle_work,CLIENT_PARAM *cp);
typedef	BOOL	(*siFunc)(BATTLE_WORK *battle_work,SERVER_PARAM *sp);
typedef	void	(*aiFunc)(BATTLE_WORK *battle_work,SERVER_PARAM *sp);

//abiritycntによるパラメータ増減テーブル
extern	const	u8	CondChgTable[][2];

#endif	__ASM_NO_DEF_

#endif __BATTLE_COMMON_H_


