// メインシーケンス
enum {
	SHOP_SEQ_INIT = 0,		// 初期化
	SHOP_SEQ_MENU,			// メニュー選択

	SHOP_SEQ_BUY_INIT,		// 購入画面初期化
	SHOP_SEQ_BUY_SCROLL,	// 購入位置へスクロール
	SHOP_SEQ_BUY_SELECT,	// アイテム選択
	SHOP_SEQ_BUYSEL_WAIT,	// 「いくつ～」表示ウェイト
	SHOP_SEQ_BUYNUM_SEL,	// 個数選択
	SHOP_SEQ_BUYNUM_WAIT,	// 「合計～なりますが」表示ウェイト
	SHOP_SEQ_BUY_YESNO,		// はい・いいえ選択
	SHOP_SEQ_BUY_CMP,		// 購入
	SHOP_SEQ_BUYCMP_WAIT,	// アイテム選択へ
	SHOP_SEQ_BUYOMAKE_WAIT,	// プレミアボール待ち
	SHOP_SEQ_BUY_END,		// 購入画面終了

	SHOP_SEQ_MENU_RET,		// メニュー選択へ戻り待ち

	SHOP_SEQ_SALE_INIT,		// 「売る」初期化
	SHOP_SEQ_SALE_CALL,		// 「売る」呼び出し
	SHOP_SEQ_SALE_WAIT,		// 「売る」終了待ち
	SHOP_SEQ_SALE_RET,		// 「売る」終了 -> フェードイン
	SHOP_SEQ_SALE_MENU_RET,	// フェードイン -> メニューへ

	SHOP_SEQ_EXIT,
	SHOP_SEQ_END
};

// ウィンドウインデックス
enum {
	WIN_IDX_NENU = 0,	// メニュー
	WIN_IDX_FLDTALK,	// フィールド会話

	WIN_IDX_LIST = 0,	// アイテムリスト
	WIN_IDX_INFO,		// アイテム説明
	WIN_IDX_GOLD,		// おこずかい
	WIN_IDX_NUM,		// 個数選択
	WIN_IDX_MINE,		// 持っている数
	WIN_IDX_TALK,		// 会話

	WIN_IDX_MAX
};

enum {
	SHOP_CLA_ARROW_U = 0,
	SHOP_CLA_ARROW_D,
	SHOP_CLA_CURSOR,
	SHOP_CLA_ITEMICON,
	SHOP_CLA_MAX
};

typedef struct {
	GF_BGL_INI * bgl;		// BGLデータ

	void * bag_wk;			// バッグのワーク

	GF_BGL_BMPWIN	win[WIN_IDX_MAX];	// BMPウィンドウ
	GF_BGL_BMPWIN	yn_win;				// BMPウィンドウ（はい・いいえ）

	BMPLIST_WORK * lw;		// BMPメニューワーク
	BMP_MENULIST_DATA * ld;	// BMPリストデータ

	BMPMENU_WORK * mw;		// BMPメニューワーク
	BMP_MENULIST_DATA * md;	// BMPメニューデータ

	MSGDATA_MANAGER * mman;	// メッセージデータマネージャ
	WORDSET * wset;			// 単語セット

	GF_CAMERA_PTR	camera;

	FIELD_CLACT	fcat;
	CLACT_WORK_PTR	cwp[SHOP_CLA_MAX];
	u16	scr_draw[2];

	MYSTATUS * my;
	void * myitem;
	CONFIG * cfg;

	FNOTE_DATA * fnote;

	RECORD * rec;

	EVENTWORK * evwk;	// イベントワーク
	BOOL	dp_flg;		// デパートフラグ

	u16 * item;
	u8	max;
	u8	pos;
	u8	scr;
	u8	seq;

	STRBUF * msgb;	// 会話領域
	u8	pri[4];
	int	disp;
	u8	midx;		// メッセージインデックス
	u8	cm_cnt;		// カメラ移動カウンタ
	u8	cm_max;		// カメラ移動カウント数

	u8	fnote_buy_cnt;
	u8	fnote_sale_cnt;

	u8	shop_type;	// ショップタイプ

	u16	sel_item;
	s16	sel_num;
	u16	sel_max;
	u32	sel_price;

}SHOP_WORK;


extern BOOL GMEVENT_Shop( GMEVENT_CONTROL * event );
extern BOOL GMEVENT_ShopSale( GMEVENT_CONTROL * event );
