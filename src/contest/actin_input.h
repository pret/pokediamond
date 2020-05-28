//==============================================================================
/**
 * @file	actin_input.h
 * @brief	演技力部門入力画面のヘッダ
 * @author	matsuda
 * @date	2005.12.02(金)
 */
//==============================================================================
#ifndef __ACTIN_INPUT_H__
#define __ACTIN_INPUT_H__


//==============================================================================
//	定数定義
//==============================================================================
//--------------------------------------------------------------
//	フレーム番号
//--------------------------------------------------------------
///パネル面のフレーム
#define ACTINSUB_FRAME_PANEL			(GF_BGL_FRAME0_S)
///黒枠面のフレーム
#define ACTINSUB_FRAME_BF				(GF_BGL_FRAME1_S)
///背景面のフレーム
#define ACTINSUB_FRAME_BACK				(GF_BGL_FRAME2_S)
///エフェクトフレーム面(黒枠スライド用)
#define ACTINSUB_FRAME_EFF				(GF_BGL_FRAME3_S)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///サブ画面の表示BGタイプ
enum{
	AINPUT_TYPE_WALL,			///<ノーマル背景
	AINPUT_TYPE_HEART_WALL,		///<技選択の壁紙のみ
	AINPUT_TYPE_WAZA,			///<技選択
	AINPUT_TYPE_JUDGE,			///<審判選択
};

//--------------------------------------------------------------
//	タッチパネル選択時の結果
//--------------------------------------------------------------
///技選択でのタッチパネル結果
enum{
	ACTIN_TP_WAZA_1,
	ACTIN_TP_WAZA_2,
	ACTIN_TP_WAZA_3,
	ACTIN_TP_WAZA_4,
};

///審判選択でのタッチパネル結果
enum{
	ACTIN_TP_JUDGE_1,
	ACTIN_TP_JUDGE_2,
	ACTIN_TP_JUDGE_3,
	ACTIN_TP_JUDGE_MODORU,
};

//==============================================================================
//	型定義
//==============================================================================
///BI_PARAMの不定形ポインタ
typedef struct _ACI_PARAM * ACI_PARAM_PTR;


//==============================================================================
//	外部関数宣言
//==============================================================================
extern void AINPUT_DefaultFrameSet(GF_BGL_INI *bgl);
extern void AINPUT_FrameExit(GF_BGL_INI *bgl);
extern void * AINPUT_SystemInit(CONTEST_SYSTEM *consys, ACTIN_SYSTEM_PARAM *sys, 
	ACTIN_GAME_PARAM *a_game);
extern void AINPUT_SystemFree(ACI_PARAM_PTR aci);
extern void AINPUT_CreateBG(ACI_PARAM_PTR aci, int select_bg, int force_put, void *scene_work);
extern int AINPUT_TouchCheck(ACI_PARAM_PTR aci);
extern BOOL AINPUT_EffectEndCheck(ACI_PARAM_PTR aci);
extern void AINPUT_WazaParaMemoryDecord(ACI_PARAM_PTR aci, u16 wazano[]);


#endif	//__ACTIN_INPUT_H__

