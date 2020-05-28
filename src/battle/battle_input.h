//==============================================================================
/**
 * @file	battle_input.h
 * @brief	戦闘入力画面処理のヘッダ
 * @author	matsuda
 * @date	2005.10.12(水)
 */
//==============================================================================
#ifndef __BATTLE_INPUT_H__
#define __BATTLE_INPUT_H__

#include "battle/battle_common.h"


//==============================================================================
//	型定義
//==============================================================================
///BI_PARAMの不定形ポインタ
typedef struct _BI_PARAM * BI_PARAM_PTR;


//==============================================================================
//	定数定義
//==============================================================================
///表示BGタイプ(※BgMakeDataと並びを同じにしておくこと！！)
enum{
	BINPUT_TYPE_WALL,	///<壁
//	BINPUT_TYPE_WALL_MISSING_PLAYER,	///<主人公キャラがいない壁
	BINPUT_COMMAND_IN,		///<スライドインしてくるコマンド選択画面
	BINPUT_COMMAND_IN_2,	///<2体目(相方)のスライドインしてくるコマンド選択画面
	BINPUT_TYPE_A,
	BINPUT_TYPE_A_2,		///<2体目(相方)のコマンド選択画面
	BINPUT_COMMAND_IN_FIGHTONLY,		///<「たたかう」のみのスライドインしてくるコマンド選択画面
	BINPUT_TYPE_FIGHTONLY,		///<「たたかう」のみのコマンド選択画面
	BINPUT_COMMAND_IN_SAFARI,
	BINPUT_TYPE_A_SAFARI,
	BINPUT_COMMAND_IN_PARK,	///<ポケパーク用のスライドインしてくるコマンド選択画面
	BINPUT_TYPE_PARK,		///<ポケパーク用のコマンド選択画面
	BINPUT_TYPE_WAZA,		///<技選択
	BINPUT_TYPE_POKE,		///<対象選択
	BINPUT_TYPE_YESNO,		///<「はい」「いいえ」選択
	BINPUT_TYPE_WASURERU,	///<技忘れ
	BINPUT_TYPE_AKIRAMERU,	///<技あきらめる
	BINPUT_TYPE_NEXT_POKEMON,	///<次のポケモンを使う
	BINPUT_TYPE_CHANGE_POKEMON,	///<ポケモンを入れ替える
};

///ポケモン選択連結タイプ
///ABCのように続けて書いてあるのは連結選択、A_B_Cのようにアンダーバーが入っているのは単独選択
enum{
	POKESELE_A_B_C_D,	//c
	POKESELE_BD,		//f
	POKESELE_BCD,		//g
	POKESELE_ABCD,		//h
	POKESELE_A,			//i
	POKESELE_AC,		//j
	POKESELE_C,			//k
	POKESELE_ABD,		//l
	POKESELE_B_C_D,		//m
	POKESELE_A_B_D,		//n
	POKESELE_A_C,		//o
	POKESELE_B_D,		//2006.07.29(土) 追加
};

///壁紙のスクロールINしてくる時の速度(下位8ビット小数)
#define BIN_PLAYER_SCROLL_SP_X		(-0xd00)

///戦闘入力画面：背景フェード
enum{
	BINPUT_BACKFADE_LIGHT,		///<明るくする
	BINPUT_BACKFADE_DARK,		///<暗くする
};

///手持ちボールのアニメシーケンス番号
enum{
	STOCK_ANMSEQ_NONE = 0,		///<ポケモンがいない
	STOCK_ANMSEQ_ALIVE = 1,		///<ポケモンがいる(生きている)
	STOCK_ANMSEQ_DEAD = 3,		///<ポケモンがいる(気絶)
	STOCK_ANMSEQ_NG = 2,		///<ポケモンがいる(ステータス異常)
};


//==============================================================================
//	構造体定義
//==============================================================================
//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///技選択画面構成用のデータ
typedef struct{
	u16	wazano[WAZA_TEMOTI_MAX];
	u16	pp[WAZA_TEMOTI_MAX];
	u16	ppmax[WAZA_TEMOTI_MAX];
}BINPUT_WAZA_PARAM;


//==============================================================================
//	外部関数宣言
//==============================================================================
extern void BINPUT_DefaultFrameSet(GF_BGL_INI *bgl);
extern void BINPUT_FrameExit(GF_BGL_INI *bgl);
extern void * BINPUT_SystemInit(BATTLE_WORK *bw, int sex);
extern void BINPUT_CreateBG(BI_PARAM_PTR bip, int select_bg, int force_put, void *scene_work);
extern void BINPUT_SystemFree(BI_PARAM_PTR bip);
extern int BINPUT_TouchCheck(BI_PARAM_PTR bip);
extern BOOL BINPUT_EffectEndCheck(BI_PARAM_PTR bip);
extern void BINPUT_StockBallActorResourceLoad(BI_PARAM_PTR bip);
extern void BINPUT_StockBallAnimeUpdate(BI_PARAM_PTR bip, u8 stock_mine[], u8 stock_enemy[]);
extern void BINPUT_StockBallON(BI_PARAM_PTR bip);
extern void BINPUT_StockBallOFF(BI_PARAM_PTR bip);
extern int BINPUT_RangeBgTypeGet(int range, int client_type);
extern void BINPUT_PlayerBG_SetX(BI_PARAM_PTR bip, int x);
extern void BINPUT_PlayerBG_ScrollX(BI_PARAM_PTR bip, int sp_x, int end_x);
extern void BINPUT_PlayerBG_MaskWindow(BI_PARAM_PTR bip);
extern void BINPUT_EffBGWallSet(BI_PARAM_PTR bip);
extern void BINPUT_BackFadeReq(BI_PARAM_PTR bip, int fade_dir);
extern BOOL BINPUT_BackFadeExeCheck(BI_PARAM_PTR bip);
extern void BINPUT_TemotiMotivationParamSet(BI_PARAM_PTR bip, const u8 *motivation);
extern int BINPUT_CursorDecendGet(BI_PARAM_PTR bip);
extern void BINPUT_CursorDecendSet(BI_PARAM_PTR bip, int decend_key);
extern void BINPUT_DefaultDataSet(BI_PARAM_PTR bip);
extern void BINPUT_DefaultDataFree(BI_PARAM_PTR bip);
extern void BINPUT_WazaParaMemoryDecord(BI_PARAM_PTR bip, int client_type, 
	const BINPUT_WAZA_PARAM *wazapara);



#endif	//__BATTLE_INPUT_H__

