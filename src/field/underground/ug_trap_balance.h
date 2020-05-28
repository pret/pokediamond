//=============================================================================
/**
 * @file	ug_trap_balance.h
 * @brief	罠のバランスのdefine
 * @author	k.ohno
 * @date    2006.06.08
 */
//=============================================================================

#ifndef __UG_TRAP_BALANCE_H__
#define __UG_TRAP_BALANCE_H__

// こんらん
#define _GIDDY_STEP_NUM  (30)  // こんらん歩数

// はんてん
#define _REVERSE_STEP_NUM  (30)  // 反転歩数

// あな
#define _HOLE_STEP_NUM (10)   //あがく回数

// おおあな
#define _BIGHOLE_STEP_NUM (20)  // あがく回数

// はなびら
#define _CLACT_BLOSSOMS_OAMNUM             (32)   // 画面に出すOAM数
// このは
#define _CLACT_LEAF_OAMNUM             (16)   // 画面に出すOAM数
// おおあわ
#define _CLACT_BUBBLE_OAMNUM             (20)   // 画面に出すBUBBLEのOAM数
// ぷちあわ
#define _CLACT_SUDS_OAMNUM             (7)   // 画面に出すSUDSのOAM数

// わなフラッシュ時間
#define _FIRST_FLASH_LEVEL (10)
// わな実行時暗くしているレベル
#define _TRAP_DARK_LEVEL (-4)

// 炎のわな
#define _MIC_SAMPLE_NUM (10)  //吹きかける息のサンプリング数
#define _MIC_TOTAL_NUM  (500)  // 息の合計値  一息128以下
#define _MIC_SCALEDOWN_TIME  (10)  // 一個小さくなる為のフレーム  30 = 一秒



#endif //__UG_TRAP_BALANCE_H__

