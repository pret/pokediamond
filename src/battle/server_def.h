
//============================================================================================
/**
 * @file	server_def.h
 * @bfief	戦闘サーバプログラム
 * @author	HisashiSogabe
 * @date	05.05.24
 */
//============================================================================================

#include	"battle/battle_common.h"
#include	"itemtool/item.h"
#include	"poketool/poke_tool.h"
#include	"poketool/waza_tool_def.h"
#include	"wazaeffect/ball_effect.h"
#include	"battle/wazano_def.h"
#include	"system/fontoam.h"

#ifndef __SERVER_DEF_H_
#define __SERVER_DEF_H_

///<client_act_workの最大値
#define	ACT_PARA_MAX	(4)

///<技シーケンス用格納ワークのサイズ（×４でバイト数になります）
#define	SKILL_SEQ_MAX		(400)

///<技シーケンスのスタックの最大値
#define	SKILL_SEQ_STACK	(4)

///<client_act_workの中身
enum{
	ACT_PARA_ACT_NO=0,		///<動作ナンバー
	ACT_PARA_CLIENT_NO,		///<動作対象クライアントナンバー
	ACT_PARA_WORK,			///<動作ナンバー用ワーク（たたかうなら、使用するわざの位置、ポケモン入れ替えなら、入れ替えるナンバー）
	ACT_PARA_SELECT_COMMAND	///<選択したコマンドナンバー
};

///<技効果用ワーク構造体宣言
struct waza_kouka_work{
	u32		kanashibari_count		: 3;		///<かなしばりカウンタ
	u32		encore_count			: 3;		///<アンコールカウンタ
	u32		juuden_count			: 2;		///<じゅうでんカウンタ
	u32		chouhatsu_count			: 3;		///<ちょうはつカウンタ
	u32		success_count			: 2;		///<まもる、こらえるが成功したカウンタ
	u32		horobinouta_count		: 2;		///<ほろびのうたカウンタ
	u32		korogaru_count			: 3;		///<ころがるカウンタ
	u32		renzokugiri_count		: 3;		///<れんぞくぎりカウンタ
	u32		takuwaeru_count			: 3;		///<たくわえるカウンタ
	u32		takuwaeru_def_count		: 3;		///<たくわえるカウンタ（防御アップ）
	u32		takuwaeru_spedef_count	: 3;		///<たくわえるカウンタ（特防アップ）
	u32		namake_bit				: 1;		///<なまけビット
	u32		moraibi_flag			: 1;		///<もらいびフラグ

	u32		lockon_client_no		: 2;		///<ロックオンされたClientNo
	u32		monomane_bit			: 4;		///<ものまねビット
	u32		shime_client_no			: 2;		///<しめつけたClientNo
	u32		manazashi_client_no		: 2;		///<くろいまなざしをしたClientNo
	u32		totteoki_count			: 3;		///<とっておき用技を出したフラグ
	u32		denzihuyuu_count		: 3;		///<でんじふゆうカウンタ
	u32		healblock_count			: 3;		///<ヒールブロックカウンタ
	u32		shutout_count			: 3;		///<シャットアウトカウンタ
	u32		karuwaza_flag			: 1;		///<かるわざフラグ
	u32		metronome_work			: 4;		///<メトロノームワーク
	u32		once_hit_up				: 1;		///<装備効果で一度だけ命中UPフラグ
	u32		once_agi_up				: 1;		///<装備効果で一度だけ先制攻撃フラグ
	u32		sensei_flag				: 1;		///<せんせいのつめ発動フラグ
	u32		sakidori_flag			: 1;		///<さきどりフラグ
	u32								: 1;

	int		handou_count;						///<反動を受けた戦闘ターンを格納（＋１のターンの時だけ反動を受ければよい）
	int		nekodamashi_count;					///<反動を受けた戦闘ターンを格納（＋１のターンの時だけ反動を受ければよい）
	int		slow_start_count;					///<反動を受けた戦闘ターンを格納（＋１のターンの時だけ反動を受ければよい）
	int		sakidori_count;						///<反動を受けた戦闘ターンを格納（＋１のターンの時だけ反動を受ければよい）
	int		migawari_hp;						///<みがわりのHP
	u32		henshin_rnd;						///<へんしん用の個性乱数（アンノーンやパッチールの形状決めに使用）

	u16		kanashibari_wazano;					///<かなしばりされた技ナンバー
	u16		shime_wazano;						///<しめつけられた技ナンバー
	u16		encore_wazano;						///<アンコールされた技ナンバー
	u16		encore_wazapos;						///<アンコールされた技の位置
	u16		totteoki_wazano[WAZA_TEMOTI_MAX];	///<とっておき用技ナンバー格納ワーク
	u16		kodawari_wazano;					///<こだわりハチマキ用技ナンバー格納ワーク
	u16		henshin_sex;						///<へんしん用性別格納ワーク

	int		item_hp_recover;					///<アイテムHP回復量
};

///<手持ちポケモンのサーバ用構造体宣言
struct pokemon_server_param
{
	u16	monsno;								//02h
	u16	pow;								//04h

	u16	def;								//06h
	u16	agi;								//08h

	u16	spepow;								//0ah
	u16	spedef;								//0ch

	u16	waza[WAZA_TEMOTI_MAX];				//14h
	
	u32	hp_rnd			:5;
	u32	pow_rnd			:5;
	u32	def_rnd			:5;
	u32	agi_rnd			:5;
	u32	spepow_rnd		:5;
	u32	spedef_rnd		:5;
	u32	tamago_flag		:1;					//18h	0:タマゴじゃない1:タマゴだよ
	u32	nickname_flag	:1;					//18h	ニックネームをつけたかどうかフラグ（0:つけていない　1:つけた）

	s8	abiritycnt[POKEMON_ABIRITY_MAX];	//20h

	int	weight;								//24h

	u8	type1;								//25h
	u8	type2;								//26h
	u8	form_no				:5;				//27h
	u8	rare				:1;				//27h
	u8						:2;				//27h
	u8	speabino;							//28h
											//ここから上はへんしん用パラメータ
											//移動は厳禁
											
	u32	appear_check_flag	:1;				//2ch	登場時天候系特性チェックをしたかどうか
	u32	ikaku_flag			:1;				//2ch	登場時いかくチェックしたかどうか
	u32	trace_flag			:1;				//2ch	登場時トレースチェックしたかどうか
	u32	download_flag		:1;				//2ch	登場時ダウンロードチェック
	u32	kikenyochi_flag		:1;				//2ch	登場時きけんよちチェック
	u32	yochimu_flag		:1;				//2ch	登場時よちむチェック
	u32	slow_start_flag		:1;				//2ch	登場時スロースタートチェック
	u32	slow_start_end_flag	:1;				//2ch	スロースタート終了チェック
	u32	omitooshi_flag		:1;				//2ch	登場時おみとおしチェック
	u32	katayaburi_flag		:1;				//2ch	登場時かたやぶりチェック
	u32	pressure_flag		:1;				//2ch	登場時プレッシャーチェック
	u32						:21;			//2ch

	u8	pp[WAZA_TEMOTI_MAX];				//30h

	u8	pp_count[WAZA_TEMOTI_MAX];			//34h

	u8	level;								//35h
	u8	friend;								//36h
	u16	nickname[MONS_NAME_SIZE+EOM_SIZE];	//4ch	(MONS_NAME_SIZE=10)+(EOM_SIZE=1)=11*2

	s32	hp;									//40h
	u32	hpmax;								//54h

	u16	oyaname[PERSON_NAME_SIZE+EOM_SIZE];	//64h	(PERSON_NAME_SIZE=7)+(EOM_SIZE=1)=8*2

	u32	exp;								//68h
	u32	personal_rnd;						//6ch
	u32	condition;							//70h
	u32	condition2;							//74h
	u32	id_no;								//78h

	u16 item;								//7ah
	u16 dummy;								//7ch

	u8	hit_count;							//7dh	攻撃を受けた回数
	u8	message_flag;						//7eh	TRAINER_MESSAGE判定用フラグ
	u8	sex		:4;							//7fh
	u8	oyasex	:4;							//7fh	親の性別
	u8	get_ball;							//80h	捕獲ボール

	u32 waza_kouka;							//84h 技効果フラグワーク
	u32 waza_kouka_temp;					//88h 技効果フラグ退避ワーク
	WAZA_KOUKA_WORK	wkw;					//	  技効果用ワーク
};

///<FieldCondition用カウンタ構造体宣言
struct field_condition_count{
	u32		weather_count;						///<天候変化用カウンタ

	u8		miraiyochi_count[CLIENT_MAX];		///<みらいよちカウンタ
	u8		negaigoto_count[CLIENT_MAX];		///<ねがいごとカウンタ

	u16		miraiyochi_wazano[CLIENT_MAX];		///<みらいよち技ナンバーワーク
	int		miraiyochi_client_no[CLIENT_MAX];	///<みらいよちしたClientNo
	s32		miraiyochi_damage[CLIENT_MAX];		///<みらいよちダメージ

	u8		negaigoto_sel_mons[CLIENT_MAX];		///<ねがいごとをしたポケモンの手持ちの位置
};

///<SideCondition用ワーク構造体宣言
struct side_condition_work{
	u32		butsuri_guard_client	: 2;		///<物理ガード効果を発生させたClientNoを格納
	u32		butsuri_guard_count		: 3;		///<物理ガード効果カウンタ
	u32		tokusyu_guard_client	: 2;		///<特殊ガード効果を発生させたClientNoを格納
	u32		tokusyu_guard_count		: 3;		///<特殊ガード効果カウンタ
	u32		shiroikiri_client		: 2;		///<しろいきり効果を発生させたClientNoを格納
	u32		shiroikiri_count		: 3;		///<しろいきり効果カウンタ
	u32		shinpi_client			: 2;		///<しんぴのまもり効果を発生させたClientNoを格納
	u32		shinpi_count			: 3;		///<しんぴのまもり効果カウンタ

	u32		konoyubitomare_flag		: 1;		///<このゆびとまれフラグ
	u32		konoyubitomare_client	: 2;		///<このゆびとまれを発動したClientNo
	u32		hatakiotosu_item		: 6;		///<はたきおとすされているSelMonsNoをbitで格納
	u32		oikaze_count			: 3;		///<おいかぜカウンタ

	u32		makibisi_count			: 2;		///<まきびしカウンタ
	u32		dokubisi_count			: 2;		///<どくびしカウンタ
	u32								:28;
};

///<OneTurnFlag用ワーク構造体宣言
struct one_turn_flag{
	u32		waruagaki_flag		:1;		//わるあがきフラグ
	u32		pp_dec_flag			:1;		//PPを減らしたフラグ
	u32		mamoru_flag			:1;		//まもるフラグ
	u32		tedasuke_flag		:1;		//てだすけフラグ
	u32		magic_cort_flag		:1;
	u32		yokodori_flag		:1;
	u32		haneyasume_flag		:1;
	u32		escape_flag			:2;		//にげたフラグ（特性or装備道具効果）
	u32		koraeru_flag		:1;		///<こらえるフラグ
	u32							:22;
	int		butsuri_otf_damage[CLIENT_MAX];		///<ダメージ量（物理攻撃)
	int		butsuri_otf_client;					///<物理攻撃したクライアント
	int		butsuri_otf_client_bit;				///<物理攻撃したクライアント
	int		tokusyu_otf_damage[CLIENT_MAX];		///<ダメージ量（特殊攻撃)
	int		tokusyu_otf_client;					///<特殊攻撃したクライアント
	int		tokusyu_otf_client_bit;				///<特殊攻撃したクライアント
	int		last_otf_damage;					///<ダメージ量（最後に受けた攻撃)
	int		last_otf_client;					///<最後に攻撃したクライアント
	int		dameoshi_damage;					///<ダメージ量（だめおし用)
};

///<OneSelfTurnFlag用ワーク構造体宣言
struct one_self_turn_flag{
	u32		no_pressure_flag	:1;		///<特性プレッシャーの効果を受けない
	u32		hiraisin_flag		:1;		///<特性ひらいしんの効果が発動
	u32		yobimizu_flag		:1;		///<特性よびみずのの効果が発動
	u32		katayaburi_flag		:1;		///<特性かたやぶりの効果が発動
	u32		trickroom_flag		:1;		///<トリックルーム発動
	u32		item_koraeru_flag	:1;		///<こらえるフラグ（装備道具効果）
	u32		korogaru_count		:3;		///<ころがるカウント（メトロノーム判定で使用）
	u32							:23;	///<ステータス上昇下降エフェクトを発動
	int		butsuri_ostf_damage;		///<ダメージ量（物理攻撃)
	int		butsuri_ostf_client;		///<物理攻撃したクライアント
	int		tokusyu_ostf_damage;		///<ダメージ量（特殊攻撃)
	int		tokusyu_ostf_client;		///<特殊攻撃したクライアント
	int		status_flag;				///<ステータスフラグ（battle_server.hにdefine定義）
	int		kaigara_damage;				///<かいがらのすず用ダメージ量
};

///<SkillIntpで使用されるタスク用ワークへのポインタ
struct	tcb_skill_intp_work{
	BATTLE_WORK				*bw;
	SERVER_PARAM			*sp;
	BMS_PTR					bms;
	CATS_ACT_PTR			cap[2];				///<控えポケモンレベルアップ用アイコン表示
	FONTOAM_OBJ_PTR			fop;				///<控えポケモンレベルアップ用アイコン表示
	CHAR_MANAGER_ALLOCDATA	cma;
	int						flag;
	int						seq_no;
	int						ballID;				///<ポケモンゲット時の投げるボールID
	int						work[8];
	void					*work_p[2];			///<汎用ワークポインタ
};

//レベルアップ時に退避しておくパラメータ
typedef struct{
	int	para[6];
}PUSH_POKEMON_PARAM;

//メッセージ表示用パラメータ構造体
struct	message_param_data
{
	int	msg_id;
	int	msg_tag;
	int	msg_para[6];
};

//技の発動を妨げた効果を示すフラグ
struct waza_out_check_flag
{
	u32	mahi_flag		:1;		//まひで技がだせない
	u32	koukanai_flag	:1;		//効果がない技だった
	u32	huuin_flag		:1;		//ふういんされて技がだせない
	u32	meromero_flag	:1;		//メロメロで技がだせない
	u32	kanashibari_flag:1;		//かなしばりで技がだせない
	u32	chouhatsu_flag	:1;		//ちょうはつされて技がだせない
	u32	hirumu_flag		:1;		//ひるんで技がだせない
	u32	konran_flag		:1;		//こんらんして自分を攻撃
	u32	juuryoku_flag	:1;		//じゅうりょくで技がだせない
	u32	healblock_flag	:1;		//ヒールブロックで技がだせない
	u32					:21;
};

//=========================================================================
//	AI用の構造体宣言
//=========================================================================

struct ai_work_tbl{
	u8	AI_SEQNO;
	u8	AI_WAZAPOS;
	u16	AI_WAZANO;

	s8	AI_WAZAPOINT[4];

	int	AI_CALC_WORK;
	u32	AI_THINK_BIT;

	u8	AI_STATUSFLAG;
	u8	AI_THINK_NO;
	u8	AI_ALL_WAZA_CHECK_LOOP_CNT;
	u8	AI_ALL_WAZA_CHECK_PUSH_POS;

	u8	*AI_ALL_WAZA_CHECK_LOOP_ADRS;
	u8	AI_DAMAGELOSS[4];
										//ここから上は、AIチェックのたびにクリアする
	u16	AI_DEFENCE_USE_WAZA[4][4];

	u8	AI_TOKUSYUNO[4];
	u16	AI_SOUBIITEM[4];

	u16	AI_HAVEITEM[2][4];

	u32	PushAdrsBuf[8];

	u8	PushAdrsCnt;
	u8	AI_ITEMCNT[2];
	u8	AI_AttackClient;
	u8	AI_DefenceClient;

	u8	AI_ITEM_TYPE[2];
	u8	AI_ITEM_CONDITION[2];

	u16	AI_ITEM_NO[2];

	u8	AI_DirSelectClient[CLIENT_MAX];			//AIで選択した攻撃対象

	WAZA_TABLE_DATA	wtd[WAZANO_MAX+1];			//技テーブル用のファイルハンドル
	ITEMDATA		*item;						//アイテムテーブル

	u16				AI_CALC_COUNT[CLIENT_MAX];		//計算実行した回数
	u16				AI_CALC_CONTINUE[CLIENT_MAX];	//計算途中かどうか
};

//デバッグツール用構造体
#ifdef PM_DEBUG
typedef struct{
	MSGDATA_MANAGER		*msg_m;			
	GF_BGL_BMPWIN		*win;
	STRBUF				*msg_buf;

	u8					seq_no;
	u8					sub_seq_no;
	u8					page;
	u8					pos;

	u32					debug_flag;

	u8					server_buffer_clear[CLIENT_MAX];///<server_bufferのクリアが正しく行われているか監視

	u32					yubihuru_waza[7];				///<ゆびをふるデバッグ用の技ナンバー格納ワーク

	u16					yubihuru_no;					///<ゆびをふるデバッグ用のシーケンスナンバー格納ワーク
	u8					cur_pos_keta;
	u8					client_no;						///<ポケモンパラメータ操作時の対象を格納

	u8					sel_mons;
	u8					osyaberi_rank;					///<おしゃべりランク固定
	u16					dummy;
}DEBUG_BATTLE_PARAM;
#endif

///<サーバ用パラメータ構造体宣言
struct server_param{
	u8		com_seq_no[CLIENT_MAX];						///<コマンドセレクトシーケンスでのシーケンスナンバー格納ワーク
	u8		ret_seq_no[CLIENT_MAX];						///<ALERT_MESSAGE_WAIT終了時の戻り先シーケンスナンバー格納ワーク
	int		server_seq_no;								///<サーバシーケンスナンバーワーク
	int		next_server_seq_no;							///<現在実行しているシーケンスの次に推移するシーケンスナンバーを格納するワーク
	int		fcc_seq_no;									///<FieldConditionCheck用シーケンスナンバー格納ワーク
	int		fcc_work;									///<FieldConditionCheckで汎用的に使用するワーク
	int		pcc_seq_no;									///<PokeConditionCheck用シーケンスナンバー格納ワーク
	int		pcc_work;									///<PokeConditionCheckで汎用的に使用するワーク
	int		scc_seq_no;									///<SideConditionCheck用シーケンスナンバー格納ワーク
	int		scc_work;									///<SideConditionCheckで汎用的に使用するワーク
	int		sba_seq_no;									///<ServerBeforeAct用シーケンスナンバー格納ワーク
	int		sba_work;									///<ServerBeforeActで汎用的に使用するワーク
	int		swhac_seq_no;								///<ServerWazaHitAfterCheck用シーケンスナンバー格納ワーク
	int		swhac_work;									///<ServerWazaHitAfterCheck用で汎用的に使用するワーク
	int		swoam_type;									///<ServerWazaOutAfterMessage用タイプナンバー格納ワーク
	int		swoam_seq_no;								///<ServerWazaOutAfterMessage用シーケンスナンバー格納ワーク
	int		swoak_seq_no;								///<ServerWazaOutAfterKouka用シーケンスナンバー格納ワーク
	int		swoak_work;									///<ServerWazaOutAfterKoukaで汎用的に使用するワーク
	int		wb_seq_no;									///<WazaBeforeのシーケンスナンバー
	int		woc_seq_no;									///<WazaOutCheckのシーケンスナンバー
	int		ssc_seq_no;									///<ServerStatusCheckのシーケンスナンバー
	int		stc_seq_no;									///<ServerTokuseiCheckのシーケンスナンバー
	int		spac_seq_no;								///<ServerPokeAppearCheckのシーケンスナンバー
	int		svc_work;									///<ServerVanishCheckで汎用的に使用するワーク

	int		waza_seq_adrs;								///<技シーケンスアドレス
	int		attack_client;
	int		attack_client_temp;
	int		defence_client;
	int		defence_client_temp;
	int		kizetsu_client;								///<気絶したクライアント
	int		reshuffle_client;							///<入れ替えをするクライアント
	int		reshuffle_client_temp;						///<入れ替えをするクライアント（退避用）
	int		tokusei_client;								///<特性チェックをして持っていたクライアント
	int		magic_cort_client;							///<マジックコート用クライアント退避ワーク
	int		tsuika_type;								///<追加効果の種類（直接、間接、特性）
	int		tsuika_para;								///<追加効果の種類（ねむる、まひとか）
	int		tsuika_flag;								///<追加効果のフラグ
	int		tsuika_client;								///<追加効果をするクライアント
	int		push_client;								///<退避用クライアント格納ワーク
	int		get_exp;									///<獲得する経験値格納ワーク
	int		gakusyuu_get_exp;							///<学習装置をもっているポケモンが獲得する経験値格納ワーク
	u32		get_exp_right_flag[2];						///<経験値を獲得する権利を持つポケモンフラグ
	int		skill_arc_kind;								///<技シーケンスの種類（ARC_BE_SEQ、ARC_SUB_SEQなど）
	int		skill_arc_index;							///<技シーケンスのインデックス
	int		skill_seq_no;								///<技シーケンスの現在位置
	int		push_count;									///<PUSHカウンタ
	int		push_skill_arc_kind[SKILL_SEQ_STACK];		///<技シーケンスの種類（ARC_BE_SEQ、ARC_SUB_SEQなど）PUSH領域
	int		push_skill_arc_index[SKILL_SEQ_STACK];		///<技シーケンスのインデックスPUSH領域
	int		push_skill_seq_no[SKILL_SEQ_STACK];			///<技シーケンスの現在位置PUSH領域
	int		agi_cnt;									///<素早さ順の何番目かを示すカウンタ
	int		wait_cnt;									///<WS_WAITコマンド用のカウンタ
	MESSAGE_PARAM	mp;									///<MESSAGE_WORKで使用されるMsgID格納ワーク
	int		client_work;								///<メッセージ表示用ClientNoパラメータ格納ワーク
	int		attack_client_work;							///<メッセージ表示用AttackClientNoパラメータ格納ワーク
	int		defence_client_work;						///<メッセージ表示用DefenceClientNoパラメータ格納ワーク
	int		waza_work;									///<メッセージ表示用WazaNoパラメータ格納ワーク
	int		item_work;									///<メッセージ表示用ItemNoパラメータ格納ワーク
	int		tokusei_work;								///<メッセージ表示用TokuseiNoパラメータ格納ワーク
	int		msg_work;									///<メッセージ表示パラメータ格納ワーク
	int		calc_work;									///<技シーケンス用計算ワーク
	int		temp_work;									///<技シーケンス用汎用ワーク
	u32		client_status[CLIENT_MAX];					///<ClientStatusFlag
	u32		koban_counter;								///<ねこにこばんカウンター
	int		total_turn;									///<総ターン数
	int		total_hinshi[CLIENT_MAX];					///<総瀕死数
	int		total_damage[CLIENT_MAX];					///<総ダメージ数
	int		sakidori_total_turn;						///<総ターン数（さきどり用）

	TCB_SKILL_INTP_WORK		*tsiw;						///<SkillIntpで使用されるタスク用ワークへのポインタ
	void	*work;										///<汎用的に使用されるAllocしたメモリへのポインタ

	u32						field_condition;			///<場にかかる戦闘効果フラグワーク
	FIELD_CONDITION_COUNT	fcc;						///<場にかかる戦闘効果カウンタワーク

	u32					side_condition[2];				///<お互いの場にかかる戦闘効果フラグワーク
	SIDE_CONDITION_WORK	scw[2];							///<お互いの場にかかる戦闘効果ワーク

	ONE_TURN_FLAG		otf[CLIENT_MAX];				///<１ターンのみ生存可能なフラグ
	ONE_SELF_TURN_FLAG	ostf[CLIENT_MAX];				///<自分のターンのみ生存可能なフラグ
	WAZA_OUT_CHECK_FLAG	wocf[CLIENT_MAX];				///<技の発動を妨げた効果を示すフラグ

	AI_WORK_TBL	AIWT;									///<トレーナーAI用ワーク構造体
	u32		*AISeqWork;									///<トレーナーAIシーケンス格納ワークへのポインタ
	u32		AISeqAdrs;									///<トレーナーAIシーケンス格納ワークへのポインタ

	u32		server_status_flag;							///<サーバステータスフラグ（技シーケンスに影響を及ぼす）
	u32		server_status_flag2;						///<サーバステータスフラグ（技シーケンスに影響を及ぼす）

	int		damage;										///<ダメージ量
	int		hit_damage;									///<ダメージ量（実際にＨＰを減らした量）
	int		critical_count;								///<クリティカルチェックに使用するクリティカルの出やすさ倍率ワーク
	int		critical;									///<クリティカルヒットワーク
	int		damage_power;								///<技による攻撃力ワーク
	int		damage_value;								///<技によるダメージ倍率ワーク
	int		hp_calc_work;								///<HP計算用ワーク
	int		waza_type;									///<技タイプワーク
	int		waza_eff_cnt;								///<技エフェクトカウンタ
	int		okodukai_value;								///<お小遣いの倍率ワーク
	u32		waza_status_flag;							///<技が当たったことで変化するフラグ
	u32		add_status_flag_direct;						///<追加効果フラグ（直接）
	u32		add_status_flag_indirect;					///<追加効果フラグ（間接）
	u32		add_status_flag_tokusei;					///<追加効果フラグ（特性）
	u8		renzoku_count;								///<連続攻撃用カウンタ
	u8		renzoku_count_temp;							///<連続攻撃用カウンタ（表示用）
	u8		client_loop;								///<複数体当たる技カウンタ
	u8		hukurodataki_count;							///<ふくろだたきのカウンタ

	u32		loop_flag;									///<ループをしたフラグ
	u32		waza_out_check_on_off;						///<HITCHECK有無フラグ
	u32		loop_hit_check;								///<ループした時のHITCHECK有無フラグ

	u32		condition2_off_req[CLIENT_MAX];				///<psp構造体のcondition2フラグの削除要求

	u8		sel_mons_no[CLIENT_MAX];					///<手持ちの何番目を繰り出しているかを格納
	u8		reshuffle_sel_mons_no[CLIENT_MAX];			///<手持ちの何番目を繰り出すかを格納
	u8		ai_reshuffle_sel_mons_no[CLIENT_MAX];		///<手持ちの何番目を繰り出すかを格納（AIが選択したもの）
	u32		client_act_work[CLIENT_MAX][ACT_PARA_MAX];	///<クライアントの動作ナンバーと動作対象を格納
	u8		client_agi_work[CLIENT_MAX];				///<すばやさ順にクライアントNoを格納
	u8		psp_agi_work[CLIENT_MAX];					///<すばやさ順にクライアントNoを格納（純粋に素早さの値のみで判断）
	u32		psp_agi_point[CLIENT_MAX];					///<素早さを格納
	u8		ServerQue[ID_MAX][CLIENT_MAX][SERVER_QUE_MAX];		///<クライアントへの命令キューワーク
	u8		server_buffer[CLIENT_MAX][BUF_SIZE];		///<クライアントからの応答格納ワーク

	int		SkillSeqWork[SKILL_SEQ_MAX];				///<技シーケンス格納ワーク

	POKEMON_SERVER_PARAM	psp[CLIENT_MAX];			///<手持ちポケモンのサーバ用構造体

	u32		waza_no_temp;								///<繰り出した技
	u32		waza_no_now;								///<現在繰り出されている技（ゆびをふるから派生などで、更新される）
	u32		waza_no_last;								///<直前に繰り出されていた技
	u32		waza_no_keep[CLIENT_MAX];					///<ため系の技を格納
	
	u16		waza_no_mamoru[CLIENT_MAX];					///<1ターン前に繰り出されていた技が発動したかどうか（まもる用）
	u16		waza_no_hit[CLIENT_MAX];					///<1ターン前に繰り出されていた技が受けたかどうか
	u16		waza_no_hit_client[CLIENT_MAX];				///<1ターン前に繰り出されていた技を発動したClientNo
	u16		waza_no_hit_type[CLIENT_MAX];				///<1ターン前に繰り出されていた技を発動したClientNo
	u16		waza_no_old[CLIENT_MAX];					///<1ターン前に繰り出されていた技
	u16		waza_no_oumu[CLIENT_MAX];					///<直前に受けた技を格納（オウムがえし用）
	u16		waza_no_oumu_hit[CLIENT_MAX][CLIENT_MAX];	///<直前に受けた技を格納（2vs2時のオウムがえし用）
	u16		waza_no_sketch[CLIENT_MAX];					///<スケッチ用の技ナンバーワーク
	u16		waza_no_select[CLIENT_MAX];					///<選択した技ナンバーワーク
	u16		waza_no_pos[CLIENT_MAX];					///<選択した技ナンバーの位置
	u16		waza_no_texture2[CLIENT_MAX];				///<1ターン前に繰り出されていた技が受けたかどうか（テクスチャー２専用）
	u16		waza_no_texture2_client[CLIENT_MAX];		///<1ターン前に繰り出されていた技を発動したClient（テクスチャー２専用）
	u16		waza_no_texture2_type[CLIENT_MAX];			///<1ターン前に繰り出されていた技のタイプ（テクスチャー２専用）
	u16		waza_no_metronome[CLIENT_MAX];				///<メトロノーム用技ワーク
	
	int		store_damage[CLIENT_MAX];					///<がまん用のダメージストックワーク

	int		client_no_hit[CLIENT_MAX];					///<技を最後に当てたClientNoを格納

	int		client_no_agi;								///<CLIENT_NO_GET_AGIで使用する専用ワーク

	u8		no_reshuffle_client;						///<入れ替えるポケモンを持たないClientNoをビットで格納
	u8		level_up_pokemon;							///<レベルアップしたポケモンの手持ちの位置をビットで格納
	u16		que_check_wait;								///<ServerQueCheck後のWAIT

	u16		agi_rand[CLIENT_MAX];						///<素早さチェックに使用する乱数値

	int		nagetsukeru_work;							///<なげつける用ワーク
	int		nagetsukeru_seq_no;							///<なげつける用追加効果とび先ワーク

	u8		safari_get_count;							///<サファリの捕獲率カウンタ
	u8		safari_escape_count;						///<サファリの逃走率カウンタ
	u8		escape_count;								///<逃げるを選択した回数
	u8		fight_end_flag;								///<戦闘終了フラグ

	u8		magnitude;									///<マグニチュードの大きさ
	u8		weather_check_flag;							///<フィールド天候チェックフラグ
	s16		hp_temp;									///<対戦相手のHPを保存
	
	u16		recycle_item[CLIENT_MAX];					///<リサイクル用アイテムワーク

	u8		list_row[CLIENT_MAX][POKEMON_TEMOTI_MAX];	///<ポケモンの並び順ワーク

	int		jingle_flag;								///<経験値獲得BGMフラグ

	int		server_que_time_out;						///<ServerQueCheckでのタイムアウトカウンタ

#ifdef PM_DEBUG
	DEBUG_BATTLE_PARAM		dbp;						///<デバッグツール用パラメータ
#endif
};

#endif __SERVER_DEF_H_
