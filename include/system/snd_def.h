//============================================================================================
/**
 * @file	snd_def.h
 * @bfief	サウンド定義ファイル
 * @author	Satoshi Nohara
 * @date	06.02.13
 */
//============================================================================================
#ifndef SND_DEF_H
#define SND_DEF_H


//============================================================================================
//
//技SEのパン定義
//
//============================================================================================
//#define WAZA_SE_PAN_L			(-118)//(-128)
#define WAZA_SE_PAN_L			(-117)//(-128)
#define WAZA_SE_PAN_N			(0)
#define WAZA_SE_PAN_R			(117)//(127)


//============================================================================================
//
//鳴き声再生パターン定義
//
//============================================================================================
#define PV_NORMAL				(0)	//通常再生
#define PV_HALF					(1)	//再生時間短縮（２ｖｓ２バトルでポケモン登場時）
#define PV_FLDEVENT				(2)	//怒ったポケモン（フィールドイベント）
#define PV_W_TOOBOE				(3)	//技効果音・とおぼえ用
#define PV_W_HYPER1				(4)	//技効果音・ハイパーボイス用１
#define PV_POKEDOWN				(5)	//ポケモンがやられた時
#define PV_W_HYPER2				(6)	//技効果音・ハイパーボイス用２
#define PV_W_HOERU1				(7)	//技効果音・ほえる１
#define PV_W_HOERU2				(8)	//技効果音・ほえる２
#define PV_W_NAKIGOE1			(9)	//技効果音・なきごえ１
#define PV_W_NAKIGOE2			(10)//技効果音・なきごえ２
#define PV_PINCHNORMAL			(11)//通常再生(元気なし)
#define PV_PINCHHALF			(12)//再生時間短縮（２ｖｓ２バトルでポケモン登場時）(元気なし)
#define PV_ZUKAN_CHORUS			(13)//図鑑コーラス再生(追加06.03.03)
#define PV_ZUKAN_NORMAL			(14)//図鑑ノーマル再生(追加06.04.21)

//鳴き声音量
#define PV_VOL_MAX				(127)//
#define PV_VOL_DEFAULT			(100)//

//BGMボリューム定義
#define BGM_VOL_MAX			(127)							//BGMのボリューム最大
#define BGM_VOL_HALF		(64)							//BGMのボリューム半分
#define BGM_VOL_MIN			(0)								//BGMのボリューム最小
#define BGM_VOL_ZUKAN		(BGM_VOL_MAX / 3)				//図鑑画面BGMのボリューム
#define BGM_VOL_TR_CASE		(BGM_VOL_MAX / 3)				//トレーナーケースBGMのボリューム
#define BGM_VOL_CLIP		(BGM_VOL_MAX / 3)				//イメージクリップ画面BGMのボリューム
#define BGM_VOL_PERAP		(BGM_VOL_MAX / 3)				//ペラップに覚えさせている時のボリューム

//ボイスチャット終了後に音量をセット(sound_data_bgm.sarcで変更がかかったら対応)
#define BGM_WIFILOBBY_VOL		(90)
#define BGM_WIFILOBBY_START_VOL	(90/5)


//============================================================================================
//
//サウンド定義置き換え用の定義
//
//============================================================================================
#define SE_MSG_SKIP				(SEQ_SE_DP_SELECT)			//メッセージキー送りSEナンバー
//#define SE_MSG_SKIP			(SEQ_SE_DP_SELECT2)			//メッセージキー送りSEナンバー
	
#define SE_DECIDE				(SEQ_SE_DP_SELECT)			//決定SEナンバー
//#define SE_DECIDE				(SEQ_SE_DP_DECIDE)			//決定SEナンバー
//#define SE_DECIDE				(SEQ_SE_DP_PIRORIRO)		//決定SEナンバー(シンプルな方がよさそう)

//#define SE_CANCEL 			(SEQ_SE_DP_DECIDE)			//キャンセルSEナンバー
#define SE_CANCEL				(SEQ_SE_DP_SELECT)			//キャンセルSEナンバー

//#define SE_WIN_OPEN			(SEQ_SE_DP_WIN_OPEN3)		//メニューを開く
#define SE_WIN_OPEN				(SEQ_SE_DP_WIN_OPEN)		//メニューを開く

//fieldobj_acmd.c
#define SE_JUMP					(SEQ_SE_DP_DANSA)			//●ジャンプSEナンバー

#define SE_LANDING				(SEQ_SE_DP_SUTYA)			//●着地
	
#define SE_POISON				(SEQ_SE_DP_DOKU2)			//●毒

#define SE_FLD_MENU_SELECT		(SEQ_SE_DP_SELECT78)		//●フィールドメニュー選択SEナンバー

#define SE_DOOR_OPEN			(SEQ_SE_DP_DOOR_OPEN)		//●ドアを開ける

#define SE_DOOR_CLOSE			(SEQ_SE_DP_DOOR_CLOSE2)		//●ドアを閉める

//#define SE_JIDO_DOOR_OPEN		(SEQ_SE_DP_DOOR_OPEN)		//自動ドアを開ける
#define SE_JIDO_DOOR_OPEN		(SEQ_SE_DP_DOOR10)			//自動ドアを開ける

//#define SE_JIDO_DOOR_CLOSE	(SEQ_SE_DP_DOOR_CLOSE2)		//自動ドアを閉める
//#define SE_JIDO_DOOR_CLOSE	(SEQ_SE_DP_DOOR10)			//自動ドアを閉める
#define SE_JIDO_DOOR_CLOSE		(0)							//自動ドアを閉める

//#define SE_KANNON_DOOR_OPEN	(SEQ_SE_DP_DOOR_OPEN)		//ドアを開ける
//#define SE_KANNON_DOOR_CLOSE	(SEQ_SE_DP_DOOR_CLOSE2)		//ドアを閉める

#define SE_C10_LIFT				(SEQ_SE_DP_ELEBETA4)		//●チャンピオン部屋のリフト

//未使用？
#define SE_UG_TRAP_ON			(SEQ_SE_DP_DOKU)			//地下でトラップにひっかかる

#define SE_MARK_GYOE			(SEQ_SE_DP_DECIDE)			//●「！」マーク音

#define SE_TOUCH_SUB_WIN		(SEQ_SE_DP_BUTTON9)			//●下画面の共通「はい、いいえ」

//src\field\effect_uground.c
#define SE_UG_CHG_DOWN			(SEQ_SE_DP_PYUU)			//●地下へおりる
#define SE_UG_CHG_UP			(SEQ_SE_DP_PYUU2)			//●地上へのぼる
#define SE_UG_CHG_TURN			(SEQ_SE_DP_GYURU)			//●地上で主人公がぐるぐる回る

#define SE_UNION_TALK			(SEQ_SE_DP_BUTTON9)			//●ユニオン話しかけれた音
//#define SE_UNION_FALL			(SEQ_SE_DP_DECIDE)			//●ユニオン落ちてくる音
#define SE_UNION_FALL			(SEQ_SE_DP_TELE2)			//●ユニオン落ちてくる音

#define SE_BTL_SEARCHER			(SEQ_SE_DP_UG_005)			//●バトルサーチャー使用音


//============================================================================================
//
//	060619 仮当て効果音
//
//============================================================================================

//============================================================================================
//
//	加賀谷さん担当
//
//============================================================================================

//--------------------------------------------------------------------------------------------
//	自機
//--------------------------------------------------------------------------------------------
//●着地したときの音
#define SE_SUTYA2							(SEQ_SE_DP_SUTYA2)

//●そらをとぶ
#define SE_SORAWOTOBU						(SEQ_SE_DP_FW019)

//●かいりき
#define SE_KAIRIKI							(SEQ_SE_DP_UG_023)

//●あなをほる
#define SE_ANAWOHORU						(SEQ_SE_DP_KAIDAN2)

//●あなぬけのヒモ
#define SE_ANANUKENOHIMO					(SEQ_SE_DP_KAIDAN2)

//●テレポート
#define SE_TELEPORT							(SEQ_SE_DP_TELE)

//●ロッククライム(移動している時)
#define SE_ROCKCLIMB						(SEQ_SE_DP_UG_023)

//●つり(さおを投げた時)
#define SE_FISHING							(SEQ_SE_DP_FW104)

//●自転車乗る時
#define SE_BICYCLE							(SEQ_SE_DP_JITENSYA)

//●自転車に乗っている時にギアを切り替える
#define SE_BICYCLE_GEAR						(SEQ_SE_DP_GEAR)			//up
#define SE_BICYCLE_GEAR2					(SEQ_SE_DP_GEAR2)			//down

//●浅い沼を歩く時
#define SE_SHALLOW_MARSH_WALK				(SEQ_SE_DP_MARSH_WALK)

//●深い沼にはまった時
#define SE_DEEP_MARSH_FALL_DOWN				(SEQ_SE_DP_ZUPO)

//●深い沼から抜け出した時
#define SE_DEEP_MARSH_FALL_OUT				(SEQ_SE_DP_ZUPO2)

//●長い草を歩く時
#define SE_LONG_GRASS_WALK					(SEQ_SE_DP_KUSA)

//●流砂が流れる時
#define SE_DRIFT_SAND						(SEQ_SE_DP_SUNA)

//自転車ジャンプ台(３倍速)
#define SE_BICYCLE_JUMP3					(SEQ_SE_DP_DANSA4)

//自転車ジャンプ台(４倍速)
#define SE_BICYCLE_JUMP4					(SEQ_SE_DP_DANSA5)

//●キッサキジム　雪玉が壊れる音
#define SE_KISSAKI_GYM_BREAK				(SEQ_SE_DP_FW291)

//●地震音
#define SE_SHAKE							(SEQ_SE_DP_FW089)

//●自動販売機で飲み物が出てきた時
#define SE_JIHANKI							(SEQ_SE_DP_JIHANKI)


//--------------------------------------------------------------------------------------------
//
//	ギンガ団アジト
//
//--------------------------------------------------------------------------------------------
//●ギンガ団アジトビル　ロックされたドアを開けた音
#define SE_AZITO_DOOR_OPEN					(SEQ_SE_DP_DOOR10)

//●ギンガ団アジトビル　ワープ床でワープするときの音
#define SE_AZITO_WARP						(SEQ_SE_DP_TELE2)


//--------------------------------------------------------------------------------------------
//
//	交換デモ
//
//--------------------------------------------------------------------------------------------
//●交換デモで、ボールの飛ぶ速度が徐々にアップしていくカットの音
#define SE_KOUKAN_BALL_MOVE					(SEQ_SE_DP_KOUKAN10)


//--------------------------------------------------------------------------------------------
//
//	GTC
//
//--------------------------------------------------------------------------------------------
//●「主人公が部屋に入ってくるときの音」
#define SE_GTC_PLAYER_IN					(SEQ_SE_DP_PYUU)

//●端末の電源を入れる音
#define SE_GTC_ON							(SEQ_SE_DP_PC_LOGIN)

//●ポケモンをさがして見つかったときの音(トレーナーが現れるときの音)
#define SE_GTC_APPEAR						(SEQ_SE_DP_TELE2)

//●端末の電源を落とす音
#define SE_GTC_OFF							(SEQ_SE_DP_PC_LOGOFF)

//●主人公が部屋から出るときの音
#define SE_GTC_PLAYER_OUT					(SEQ_SE_DP_PYUU2)

//●検索中の音
#define SE_GTC_SEARCH						(SEQ_SE_DP_Z_SEARCH)

//●検索したけど見つからなかった
#define SE_GTC_NG							(SEQ_SE_DP_BOX03)


//============================================================================================
//
//	加賀谷さん担当
//
//============================================================================================

//--------------------------------------------------------------------------------------------
//	スロット　本体
//--------------------------------------------------------------------------------------------
//BET音
#define SE_SLOT_BET							(SEQ_SE_DP_ZUKAN02)

//リール回転開始音
#define SE_SLOT_REEL_START					(SEQ_SE_DP_OPEN2)

//停止音
#define SE_SLOT_REEL_STOP					(SEQ_SE_DP_UG_022)

//停止音（ピッピ１&2）
//#define SE_SLOT_REEL_STOP2				(SEQ_SE_DP_SELECT)
#define SE_SLOT_REEL_STOP2					(SEQ_SE_DP_SELECT_SLOT)

//--------------------------------------------------------------------------------------------
//	スロット　演出
//--------------------------------------------------------------------------------------------
//●ボール転がり音（IN）
#define SE_SLOT_BALL_FALL_DOWN				(SEQ_SE_DP_UG_020)

//●ボールオープン音
#define SE_SLOT_BALL_OPEN					(SEQ_SE_DP_SLOT01)

//●ピッピボールIN
#define SE_SLOT_PIPPI_BALL_IN				(SEQ_SE_DP_SLOT02)

//月光音
#define SE_SLOT_MOON_LIGHT					(SEQ_SE_DP_025)


//--------------------------------------------------------------------------------------------
//
//	自機トラップ
//
//--------------------------------------------------------------------------------------------
//●穴にはまって方向を変える時
#define SE_TRAP_HOLE_DIR					(SEQ_SE_DP_BOX02)

//●穴から抜けた時
#define SE_TRAP_HOLE_FALL_OUT				(SEQ_SE_DP_DANSA)

//●岩が落ちてくる時(影が出る)
#define SE_TRAP_ROCK_SHADOW					(SEQ_SE_DP_FW466)

//●岩が地面に落ちた時
#define SE_TRAP_ROCK_FALL					(SEQ_SE_DP_FW452)

//●吹っ飛ばされている時
#define SE_TRAP_MOVE						(SEQ_SE_DP_F007)

//●あわが舞っている時
#define SE_TRAP_BUBBLE						(SEQ_SE_DP_FAWA)

//●煙が画面にはりついた時
#define SE_TRAP_KEMURI						(SEQ_SE_DP_FPASA2)


//============================================================================================
//
//	斉藤さん担当
//
//============================================================================================

//--------------------------------------------------------------------------------------------
//	船デモ
//--------------------------------------------------------------------------------------------
//●モロッコ号　湿原　加速　→　通常
#define SE_TRAIN_START						(SEQ_SE_DP_TRAIN02)

//●モロッコ号　湿原　減速
#define SE_TRAIN_END						(SEQ_SE_DP_TRAIN03)

//●モロッコ号　湿原　チンチン
#define SE_TRAIN_BELL						(SEQ_SE_DP_TRAIN04)

//●船　通常
#define SE_SHIP_RUN							(SEQ_SE_DP_SHIP01)

//●船　汽笛
#define SE_SHIP_KITEKI						(SEQ_SE_DP_SHIP02)

//●桟橋が開く音
#define SE_PIER_OPEN						(SEQ_SE_DP_SHIP03)

//--------------------------------------------------------------------------------------------
//	エレベーター
//--------------------------------------------------------------------------------------------
//●エレベーター　上昇音(下降音も同じ)
#define SE_ELEBETA_UP						(SEQ_SE_DP_ELEBETA2)
#define SE_ELEBETA_DOWN						(SEQ_SE_DP_ELEBETA2)

//●エレベーター　到着音
#define SE_ELEBETA_ARRIVAL					(SEQ_SE_DP_PINPON)

//--------------------------------------------------------------------------------------------
//	ジム
//--------------------------------------------------------------------------------------------
//●ナギサジム　ボタンを踏んだ時＋歯車が回る音
#define SE_NAGISA_GYM_BUTTON				(SEQ_SE_DP_GAGAGA)

//●ノモセジム　ボタンを踏んだ時＋水かさが増える音
//#define SE_NOMOSE_GYM_BUTTON				(SEQ_SE_DP_DENSI05)
#define SE_NOMOSE_GYM_BUTTON				(SEQ_SE_DP_FW056)

//●畳を移動する音
#define SE_TOBARI_GYM_MOVE					(SEQ_SE_DP_TV_NOISE)

//●ヨスガジム　リフトが到着した音
#define SE_YOSUGA_GYM_LIFT					(SEQ_SE_DP_KI_GASYAN)


//============================================================================================
//
//	高橋さん担当
//
//============================================================================================

//--------------------------------------------------------------------------------------------
//	フィールド技
//--------------------------------------------------------------------------------------------
//●あまいかおり(天気が雨、大雨、雷の時は鳴らないので大丈夫)
#define SE_AMAIKAORI						(SEQ_SE_DP_FW230)

//●きりばらい
#define SE_KIRIBARAI						(SEQ_SE_DP_FBRADE)


//============================================================================================
//
//	大野さん担当
//
//============================================================================================
//●強制移動の時にクルクル回っている(リピート音なので停止処理が必要！)(トレーナーとの視線配置はなし)
#define SE_YAZIRUSI_FLOOR					(SEQ_SE_DP_F209)


//============================================================================================
//
//	担当未定(斉藤さんか高橋さん)
//
//============================================================================================
//●いわくだき
#define SE_IWAKUDAKI						(SEQ_SE_DP_FW088)

//●いあいぎり
#define SE_IAIGIRI							(SEQ_SE_DP_FW015)

//●たきのぼり
#define SE_TAKINOBORI						(SEQ_SE_DP_FW463)


//============================================================================================
//
//	後藤さん担当
//
//============================================================================================
//●タマゴ
#define SE_EGG_N01							(SEQ_SE_DP_EGG01)
#define SE_EGG_N02							(SEQ_SE_DP_BOWA3)

//●マナフィーのタマゴ
#define SE_EGG_S01							(SEQ_SE_DP_W278)
#define SE_EGG_S02							(SEQ_SE_DP_W080C)
#define SE_EGG_S03							(SEQ_SE_DP_W361)


#endif	/* SND_DEF_H */


