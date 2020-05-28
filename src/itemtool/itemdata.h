// アイテムデータ構造体
struct _ITEM_DATA {
/*
	u16	price;					// 買値
	u8	eqp;					// 装備効果
	u8	atc;					// 威力

	u8	imp:2;					// 重要
	u8	cnv_btn:2;				// 便利ボタン
	u8	pocket:4;				// 保存先（ポケット番号）
	u8	field_func;				// field機能
	u8	battle_func;			// battle機能
	u8	work_type;				// ワークタイプ

	u8	work[20];				// 汎用ワーク
*/
	u16	price;				// 買値
	u8	eqp;				// 装備効果
	u8	atc;				// 威力

	u8	tuibamu_eff;		// ついばむ効果
	u8	nage_eff;			// なげつける効果
	u8	nage_atc;			// なげつける威力
	u8	sizen_atc;			// しぜんのめぐみ威力

	u16	sizen_type:5;		// しぜんのめぐみタイプ
	u16	imp:1;				// 重要
	u16	cnv_btn:1;			// 便利ボタン
	u16	fld_pocket:4;		// フィールド保存先（ポケット番号）
	u16	btl_pocket:5;		// 戦闘保存先（ポケット番号）

	u8	field_func;			// field機能
	u8	battle_func;		// battle機能
	u8	work_type;			// ワークタイプ

	u8	dmy;				// ダミー

	u8	work[20];			// 汎用ワーク
};

// ダミーワーク
typedef struct {
	u8	work[20];
}ITEMPARAM_NONE;

// 手持ちポケモンに使用するアイテム
typedef struct {
	u8	sleep_rcv:1;			// 眠り回復
	u8	poison_rcv:1;			// 毒回復
	u8	burn_rcv:1;				// 火傷回復
	u8	ice_rcv:1;				// 氷回復
	u8	paralyze_rcv:1;			// 麻痺回復
	u8	panic_rcv:1;			// 混乱回復
	u8	meromero_rcv:1;			// メロメロ回復
	u8	ability_guard:1;		// 能力ガード

	u8	death_rcv:1;			// 瀕死回復
	u8	alldeath_rcv:1;			// 全員瀕死回復
	u8	lv_up:1;				// レベルアップ
	u8	evolution:1;			// 進化
	u8	atc_up:4;				// 攻撃力アップ

	u8	def_up:4;				// 防御力アップ
	u8	spa_up:4;				// 特攻アップ

	u8	spd_up:4;				// 特防アップ
	u8	agi_up:4;				// 素早さアップ

	u8	hit_up:4;				// 命中率アップ
	u8	critical_up:2;			// クリティカル率アップ
	u8	pp_up:1;				// PPアップ
	u8	pp_3up:1;				// PPアップ（３段階）

	u8	pp_rcv:1;				// PP回復
	u8	allpp_rcv:1;			// PP回復（全ての技）
	u8	hp_rcv:1;				// HP回復
	u8	hp_exp:1;				// HP努力値アップ
	u8	pow_exp:1;				// 攻撃努力値アップ
	u8	def_exp:1;				// 防御努力値アップ
	u8	agi_exp:1;				// 素早さ努力値アップ
	u8	spa_exp:1;				// 特攻努力値アップ

	u8	spd_exp:1;				// 特防努力値アップ
	u8	friend_exp1:1;			// なつき度１
	u8	friend_exp2:1;			// なつき度２
	u8	friend_exp3:1;			// なつき度３

	u8	dmy_bit:4;				// ダミー（余り）

	s8	prm_hp_exp;				// HP努力値
	s8	prm_pow_exp;			// 攻撃努力値
	s8	prm_def_exp;			// 防御努力値
	s8	prm_agi_exp;			// 素早さ努力値
	s8	prm_spa_exp;			// 特攻努力値
	s8	prm_spd_exp;			// 特防努力値
	u8	prm_hp_rcv;				// HP回復値
	u8	prm_pp_rcv;				// pp回復値
	s8	prm_friend1;			// なつき度1
	s8	prm_friend2;			// なつき度2
	s8	prm_friend3;			// なつき度3

	u8	dmy_buf[2];				// ダミー（余り）
}ITEMPARAM_RCV;
