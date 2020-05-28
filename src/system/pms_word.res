// このファイルはコンバータで自動生成されています
// 手作業での編集は行わないようにお願いします
// Game Freak   taya


#ifdef __PMS_WORD_RES__	// 単一のファイルからのみincludeを許可する

//----------------------------------------------------------------
/**
 * 各gmmファイル指定のための定数
*/
//----------------------------------------------------------------

enum {
	PMSW_SRC_POKEMON,
	PMSW_SRC_SKILL,
	PMSW_SRC_TYPE,
	PMSW_SRC_TOKUSEI,
	PMSW_SRC_TRAINER,
	PMSW_SRC_HITO,
	PMSW_SRC_AISATSU,
	PMSW_SRC_SEIKATSU,
	PMSW_SRC_KIMOTI,
	PMSW_SRC_NANKAI,
	PMSW_SRC_UNION,
};

//----------------------------------------------------------------
/**
 * 各gmmファイル毎の要素数
*/
//----------------------------------------------------------------

static const u16 PMS_SrcElems[] = {
	 496,	//ポケモン名	0 ... 495
	 468,	//わざ名	496 ... 963
	  18,	//ポケモンタイプ名	964 ... 981
	 124,	//とくせい名	982 ... 1105
	  38,	//トレーナー	1106 ... 1143
	  38,	//ひと	1144 ... 1181
	 107,	//あいさつ	1182 ... 1288
	 104,	//せいかつ	1289 ... 1392
	  47,	//きもち	1393 ... 1439
	  32,	//なんかいことば	1440 ... 1471
	  23,	//ユニオン	1472 ... 1494
};

//----------------------------------------------------------------
/**
 * 各gmmファイルのアーカイブ内ファイルID
*/
//----------------------------------------------------------------

static const u16 PMS_SrcFileID[] = {
	NARC_msg_monsname_dat,
	NARC_msg_wazaname_dat,
	NARC_msg_typename_dat,
	NARC_msg_tokusei_dat,
	NARC_msg_pms_word06_dat,
	NARC_msg_pms_word07_dat,
	NARC_msg_pms_word08_dat,
	NARC_msg_pms_word09_dat,
	NARC_msg_pms_word10_dat,
	NARC_msg_pms_word11_dat,
	NARC_msg_pms_word12_dat,
};

//----------------------------------------------------------------
/**
 * 重複単語テーブル
*/
//----------------------------------------------------------------

static const PMS_WORD DupWord_00[] = {
	944,1300,
};

static const PMS_WORD DupWord_01[] = {
	872,1112,
};

static const PMS_WORD DupWord_02[] = {
	 93,971,
};

static const PMS_WORD DupWord_03[] = {
	1044,1116,
};

static const struct {
    const PMS_WORD* data;
    int   count;
}DupWordTable[] = {
	{ DupWord_00, 2 },
	{ DupWord_01, 2 },
	{ DupWord_02, 2 },
	{ DupWord_03, 2 },
};

//----------------------------------------------------------------
/**
 * 関連定数
*/
//----------------------------------------------------------------

#define  PMS_SRCFILE_MAX  (11)

#undef __PMS_WORD_RES__
#endif

