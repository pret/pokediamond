//==============================================================================
/**
 * @file	actin_ex.h
 * @brief	演技力部門：外部公開ヘッダ
 * @author	matsuda
 * @date	2005.11.29(火)
 *
 * 演技力部門で外部に公開する必要のある定義等をここに書いています
 */
//==============================================================================
#ifndef __ACTIN_EX_H__
#define __ACTIN_EX_H__


#define ACTIN_3DBG_PRIORITY			(2)		///<3D面のBGプライオリティ
///ウィンドウ面のBGプライオリティ
#define ACTIN_BGPRI_WINDOW			(0)
///エフェクト面のBGプライオリティ
#define ACTIN_BGPRI_EFFECT			(1)
///背景面のBGプライオリティ
#define ACTIN_BGPRI_BACKGROUND		(3)

#define ACTIN_FRAME_WINDOW			(GF_BGL_FRAME1_M)	///<フレーム面：ウィンドウ
#define ACTIN_FRAME_EFFECT			(GF_BGL_FRAME2_M)	///<フレーム面：エフェクト
#define ACTIN_FRAME_BACKGROUND		(GF_BGL_FRAME3_M)	///<フレーム面：背景

#define ACTIN_BGNO_WINDOW			(1)					///<BG番号：ウィンドウ
#define ACTIN_BGNO_EFFECT			(2)					///<BG番号：エフェクト
#define ACTIN_BGNO_BACKGROUND		(3)					///<BG番号：背景


//--------------------------------------------------------------
//	技エフェクト
//--------------------------------------------------------------
///攻撃ポケモンの座標X
#define CONTEST_ATTACK_POKE_X		(APPEAR_X_TYPE_B)
///攻撃ポケモンの座標Y
#define CONTEST_ATTACK_POKE_Y		(APPEAR_Y_TYPE_A)
///攻撃ポケモンの座標Z
#define CONTEST_ATTACK_POKE_Z		(APPEAR_Z_TYPE_A)

///防御ポケモンの座標X
#define CONTEST_DEFENCE_POKE_X		(APPEAR_X_TYPE_C)
///防御ポケモンの座標Y
#define CONTEST_DEFENCE_POKE_Y		(APPEAR_Y_TYPE_D)
///防御ポケモンの座標Z
#define CONTEST_DEFENCE_POKE_Z		(APPEAR_Z_TYPE_B)


//--------------------------------------------------------------
//	背景で使用しているパレットのフェードbit
//--------------------------------------------------------------
///背景で使用しているパレット開始位置
#define ACTIN_HAIKEI_PAL_START		(0)
///背景で使用しているパレット本数
#define ACTIN_HAIKEI_PAL_NUM		(3)
///背景のフェードbit(技エフェクト用)
#define ACTIN_HAIKEI_FADE_BIT		(0x0007)
///技エフェクトBG用パレットのフェードbit
#define ACTIN_WAZAEFF_FADE_BIT		(0x0300)
///背景のフェードbit＋技エフェクトBG用パレット(技エフェクト用)
#define ACTIN_EFFBG_ALL_FADE_BIT	(ACTIN_HAIKEI_FADE_BIT | ACTIN_WAZAEFF_FADE_BIT)


//==============================================================================
//	外部関数宣言
//==============================================================================
extern void ActinExTool_DefaultBlendSet(void);

#endif	//__ACTIN_EX_H__

