#ifndef B_BAG_H
#define B_BAG_H
#undef GLOBAL
#ifdef B_BAG_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


enum {
	BBAG_MODE_NORMAL = 0,	// 通常モード
	BBAG_MODE_GETDEMO,		// 捕獲デモモード
};

enum {
	BBAG_POKE_HPRCV = 0,	// HP回復ポケット
	BBAG_POKE_STRCV,		// 状態回復ポケット
	BBAG_POKE_BALL,			// ボールポケット
	BBAG_POKE_BATTLE,		// 戦闘用ポケット
	BBAG_POKE_MAX
};


typedef struct {
	BATTLE_WORK * bw;	// 戦闘用ワーク

	MYSTATUS * myst;	// プレーヤーデータ
	MYITEM * myitem;	// アイテムデータ

	u32	heap;			// ヒープID
	s32 client_no;		// クライアントNo

	u32	mode;			// 制御モード

	u32	skill_item_use;	// 技で使用不可

	u16	ret_item;		// 使用したアイテム
	u8	ret_page;		// 使用したアイテムのポケット

	u8	used_poke;		// 前回使用したアイテムのポケット
	u16	used_item;		// 前回使用したアイテム

	u8	enc_double;		// 野生2vs2でボールが投げられない場合は１
	u8	waza_vanish;	// 相手が「そらをとぶ」などで見えない場合は１
	u8	waza_migawari;	// 相手が「みがわり」を使用している場合は１

	u8	cursor_flg;		// カーソル表示フラグ

	u8	end_flg;		// 終了フラグ

	u8	item_pos[5];	// アイテム位置
	u8	item_scr[5];	// アイテムスクロールカウンタ
}BBAG_DATA;


extern void BattleBag_TaskAdd( BBAG_DATA * dat );






#undef GLOBAL
#endif	/* B_BAG_H */
