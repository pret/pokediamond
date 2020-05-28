//============================================================================================
/**
 * @file	b_plist_anm.h
 * @brief	戦闘用ポケモンリスト画面 ボタン制御
 * @author	Hiroyuki Nakamura
 * @date	05.03.16
 */
//============================================================================================
#ifndef B_PLIST_ANM_H
#define B_PLIST_ANM_H
#undef GLOBAL
#ifdef B_PLIST_ANM_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	定数定義
//============================================================================================
enum {
	BPL_BUTTON_POKE1 = 0,	// ポケモン１
	BPL_BUTTON_POKE2,		// ポケモン２
	BPL_BUTTON_POKE3,		// ポケモン３
	BPL_BUTTON_POKE4,		// ポケモン４
	BPL_BUTTON_POKE5,		// ポケモン５
	BPL_BUTTON_POKE6,		// ポケモン６
	BPL_BUTTON_RET,			// 戻る
	BPL_BUTTON_POKE_CHG,	// 入れ替え
	BPL_BUTTON_STATUS1,		// 強さを見る（左配置）
	BPL_BUTTON_STATUS2,		// 強さを見る（右配置）
	BPL_BUTTON_WAZASEL1,	// 技を見る
	BPL_BUTTON_WAZASEL2,	// 技を見る（単独）
	BPL_BUTTON_UP,			// 切り替え（上）
	BPL_BUTTON_DOWN,		// 切り替え（下）
	BPL_BUTTON_WAZA1,		// 技１
	BPL_BUTTON_WAZA2,		// 技２
	BPL_BUTTON_WAZA3,		// 技３
	BPL_BUTTON_WAZA4,		// 技４
	BPL_BUTTON_CONTEST,		// コンテスト技<->戦う技

	BPL_BUTTON_WAZARCV1,	// 技回復１
	BPL_BUTTON_WAZARCV2,	// 技回復２
	BPL_BUTTON_WAZARCV3,	// 技回復３
	BPL_BUTTON_WAZARCV4,	// 技回復４

	BPL_BUTTON_WAZADEL1,	// 技忘れ１
	BPL_BUTTON_WAZADEL2,	// 技忘れ２
	BPL_BUTTON_WAZADEL3,	// 技忘れ３
	BPL_BUTTON_WAZADEL4,	// 技忘れ４
	BPL_BUTTON_WAZADEL5,	// 技忘れ５

	BPL_BUTTON_WAZADEL_B,	// 忘れさせる（戦闘）
	BPL_BUTTON_WAZADEL_C,	// 忘れさせる（コンテスト）

	BPL_BUTTON_WAZAPOS1,	// 技切り替え１
	BPL_BUTTON_WAZAPOS2,	// 技切り替え２
	BPL_BUTTON_WAZAPOS3,	// 技切り替え３
	BPL_BUTTON_WAZAPOS4,	// 技切り替え４
};


//============================================================================================
//	プロトタイプ宣言
//============================================================================================

GLOBAL void BattlePokeList_ButtonScreenMake( BPLIST_WORK * wk, u16 * scrn );

GLOBAL void BattlePokeList_ButtonScreenMake2( BPLIST_WORK * wk, u16 * scrn );

GLOBAL void BattlePokeList_ButtonAnmInit( BPLIST_WORK * wk, u8 id );


GLOBAL void BattlePokeList_ButtonAnmMain( BPLIST_WORK * wk );


GLOBAL void BattlePokeList_ButtonPageScreenInit( BPLIST_WORK * wk, u8 page );
GLOBAL void BattlePokeList_ButtonPalSet( BPLIST_WORK * wk, u8 page );

GLOBAL void BPL_HPRcvButtonPut( BPLIST_WORK * wk );



#undef GLOBAL
#endif	// B_PLIST_ANM_H
