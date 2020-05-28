typedef struct {
	u8	person_name_size;	// 人物の名前の長さ（自分も含む）
	u8	tr_name_size;		// トレーナーの名前の長さ
	u8	mons_name_size;		// ポケモン名の長さ(バッファサイズ EOM_含まず)
	u8	mons_disp_size;		// ポケモン名の長さ(表示サイズ EOM_含まず)
	u8	waza_name_size;		// わざ名の長さ
	u8	item_name_size;		// どうぐ名の長さ
	u8	seed_name_size;		// タネの名前の長さ
	u8	speabi_name_size;	// 特性名の長さ
	u8	zokusei_name_size;	// 属性名の長さ
	u8	map_name_width;		// 地名文字列の表示幅
	u8	mapname_max;		// 地名文字列の最大長
	u8	trtype_name_size;	// トレーナータイプ名の長さ
	u8	goods_name_size;	// グッズ名の長さ
	u8	zukan_type_size;	// 図鑑タイプ名の長さ
	u8	eom_size;			// 終了コードの長さ
	u8	btl_tr_name_size;	// バトルタワー・トレーナーの名前の長さ
	u8	kaiwa_work_size;	// 簡易会話の１単語の最長文字数（EOM_含まず）
}POKE_DATALEN;

typedef struct {
	u8	normal_max;	// 通常アイテム保存数
	u8	extra_max;	// 大事アイテム保存数
	u8	ball_max;	// ボールアイテム保存数
	u8	skill_max;	// 技マシンアイテム保存数
	u8	seed_max;	// 種アイテム保存数
	u8	pc_max;		// ＰＣアイテム保存数
}POKE_ITEMMAX;

typedef struct {
	u32	membox:1;	// メモリーボックス使用可能フラグ
	u32	coliseum:1;	// ポケモンコロシアム使用可能フラグ
	u32	dummy:30;	// 予備
}POKESOFT_ENABLE;

typedef struct {
	///カセットバージョン
	u32	pm_version;
	///言語バージョン
	u32 pm_lang;

	///ゲームタイトル名
	u8 rom_name[32];

	///ポケモン正面画像データアドレステーブル
	const void * front_cell;
	///ポケモン背面画像データアドレステーブル
	const void * back_cell;
	///ポケモンノーマルカラーデータアドレステーブル
	const void * normal_pal;
	///ポケモンレアカラーデータアドレステーブル
	const void * rare_pal;

	///アイコン画像データアドレステーブル
	u8* const	* icon_char;
	///アイコンアトリビュートデータアドレステーブル
	const u8 * icon_attr;
	///ポケモンアイコンパレットデータ
	const void * icon_pal;

	///ポケモン名前データテーブル
	const void *mons_name;
	///わざ名データテーブル
	const void *waza_name;
	///グッズデータテーブル
	const void * goods;

	///セーブデータ(fld)：イベントフラグオフセット
	u32	event_flag_offset;
	///セーブデータ(fld)：イベントワークオフセット
	u32 event_work_offset;
	///セーブデータ(MyData)：図鑑ブロックオフセット
	u32 zukan_work_offset;
	///セーブデータ(fld):図鑑データオフセット（見つけたフラグその２）
	u32 zukan_flag2_offset;
	///セーブデータ(fld):図鑑データオフセット（見つけたフラグその３）
	u32 zukan_flag3_offset;

	///図鑑全国モードワークナンバー
	u32 zenkoku_work_no;
	///図鑑全国モードフラグナンバー
	u32 zenkoku_flag_no;
	///「ふしぎなできごと」フラグナンバー
	u32 husigi_flag_no;

	///ポケモン最大数
	u32 poke_cnt_max;

	//データ長設定関連
	POKE_DATALEN	pm_datalen;

	///セーブデータ：MyData　データサイズ
	u32	MyData_size;
	///セーブデータ：fld　データサイズ
	u32	Fld_size;

	///セーブデータ：ポケモン手持ち数
	u32 temoti_cnt;
	///セーブデータ：ポケモン手持ちデータ
	u32 temoti_dat;

	///セーブデータ：セーブ状態判定
	u32 pokecen_flg;
	///セーブデータ：自分のＩＤ
	u32 my_id;

	///セーブデータ：自分の名前
	u32 my_name;
	///セーブデータ：自分の性別
	u32 my_sex;

	///セーブデータ：バトルタワーＬＶ５０モードのステータス
	u32 b_tower_stat50;
	///セーブデータ：バトルタワーＬＶ１００モードのステータス
	u32 b_tower_stat100;

	///セーブデータ(Fld)：拡張イベントフラグオフセット
	u32	ex_event_flag_offset;
	///セーブデータ(Fld)：拡張イベントワークオフセット
	u32 ex_event_work_offset;

	///外部連動ソフト使用可否判定フラグ
	POKESOFT_ENABLE	expand_soft_disable_flag;

	///ポケモンパーソナルデータテーブル
	const void*	PokemonData;
	///特性名データテーブル
	const void * special_ability_msg;
	///特性説明データテーブル
	const void * special_ability_info_msg;
	///アイテムデータテーブル
	const void* item_data;

	///技データテーブル
	const void* waza_data;

	///モンスターボール画像データアドレステーブル
	const void * monsterball_cell_tbl;
	///モンスターボールパレットデータアドレステーブル
	const void * monsterball_pal_tbl;

	///ポケモン交換判定フラグ
	u32		pokemon_trade_flag;				//ポケモン交換Enableフラグ

	///ゲームクリアフラグナンバー
	u32		game_clr_flag_no;

	///リボン取得許可フラグナンバー
	u32		ribbon_enable_flag_no;

	///アイテム保存最大数
	POKE_ITEMMAX	item_max_cnt;

	///パソコン保存アイテムデータ構造体
	u32		pc_item;

	///リボンとメッセージの関連づけテーブル
	u32			ribbon_no;

	///ＲＡＭ木の実ワーク
	u32		ram_seed_data;

	///ＲＡＭ木の実ワークサイズ
	u32		ram_seed_data_size;
}POKEMON_ROM_HEADER;