//==============================================================================
/**
 * @file	dance_input.h
 * @brief	ダンス部門入力画面のヘッダ
 * @author	matsuda
 * @date	2005.12.17(土)
 */
//==============================================================================
#ifndef __DANCE_INPUT_H__
#define __DANCE_INPUT_H__


//==============================================================================
//	定数定義
//==============================================================================
//--------------------------------------------------------------
//	フレーム番号
//--------------------------------------------------------------
///パネル面のフレーム
#define DANCESUB_FRAME_PANEL			(GF_BGL_FRAME0_S)
///黒枠面のフレーム
#define DANCESUB_FRAME_BF				(GF_BGL_FRAME1_S)
///背景面のフレーム
#define DANCESUB_FRAME_BACK				(GF_BGL_FRAME2_S)
///エフェクトフレーム面(黒枠スライド用)
#define DANCESUB_FRAME_EFF				(GF_BGL_FRAME3_S)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///サブ画面の表示BGタイプ
enum{
	DINPUT_TYPE_WALL,			///<ノーマル背景
	DINPUT_TYPE_COMMAND,		///<コマンド選択
};

//--------------------------------------------------------------
//	タッチパネル選択時の結果
//--------------------------------------------------------------
///コマンド選択でのタッチパネル結果
enum{
	DANCE_TP_JUMP,
	DANCE_TP_ADVANCE,
	DANCE_TP_LEFT,
	DANCE_TP_RIGHT,
	
	DANCE_TP_MAX,
};

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///ボタンを変更する時の色(黒)
#define DINPUT_COLOR_BLACK		(0x0000)
///ボタンを暗くする時のEVY値
#define DINPUT_BLACK_EVY		(6)
///ボタン通常時のEVY値
#define DINPUT_NORMAL_EVY		(0)


//==============================================================================
//	型定義
//==============================================================================
///DI_PARAMの不定形ポインタ
typedef struct _DCI_PARAM * DCI_PARAM_PTR;


//==============================================================================
//	外部関数宣言
//==============================================================================
extern void DINPUT_DefaultFrameSet(GF_BGL_INI *bgl);
extern void DINPUT_FrameExit(GF_BGL_INI *bgl);
extern void * DINPUT_SystemInit(CONTEST_SYSTEM *consys, DANCE_SYSTEM_PARAM *sys);
extern void DINPUT_SystemFree(DCI_PARAM_PTR dci);
extern void DINPUT_CreateBG(DCI_PARAM_PTR dci, int select_bg, int force_put, void *scene_work);
extern int DINPUT_TouchCheck(DCI_PARAM_PTR dci);
extern BOOL DINPUT_EffectEndCheck(DCI_PARAM_PTR dci);
extern void DINPUT_DefaultActorSet(DCI_PARAM_PTR dci);
extern int DINPUT_MakeDataNoGet(DCI_PARAM_PTR dci);
extern void DINPUT_FadeSet(DCI_PARAM_PTR dci, u16 color, u8 evy);


#endif	//__DANCE_INPUT_H__

