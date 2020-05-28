//=============================================================================
/**
 * @file	comm_direct_counter_def.h
 * @bfief	通信ダイレクトコーナーのカウンター スクリプトと共用の定義
 * @author	katsumi ohno
 * @date	05/08/04
 */
//=============================================================================

#ifndef __COMM_DIRECT_COUNTER_DEF_H__
#define __COMM_DIRECT_COUNTER_DEF_H__


#define DBC_TIM_BATTLE_MPDS (3)  // 対戦部屋->バトル
#define DBC_TIM_BATTLE_DSOK (4)  // バトルモードになった
#define DBC_TIM_BATTLE_MPOK (5)  // 歩きモードになった


#define DBC_TIM_BATTLE_BACK (30)    // 対戦部屋待機状態位置移動完了
#define DBC_TIM_BATTLE_PAUSE (92)    // 対戦部屋待機状態
#define DBC_TIM_BATTLE_START (93)    // 対戦部屋終了 > バトル
#define DBC_TIM_BATTLE_EXIT  (94)    // 対戦部屋出て行くとき
#define DBC_TIM_BATTLE_EXIT2  (91)    // 対戦部屋出て行くとき  もう一回

#define DBC_TIM_BATTLE_TR (95)    // 対戦部屋トレーナーカード交換待機
#define DBC_TIM_BATTLE_ROOMIN	(96) // 対戦部屋に入るとき
#define DBC_TIM_BATTLE_DSCHANGE (97)  // データ形式切り替え
#define DBC_TIM_BATTLE_DSEND (98) // 切り替え完了


#define REGULATION_RET_NONE  (3)   // レギュレーションいらない
#define REGULATION_RET_OK  (1)   // レギュレーション完了
#define REGULATION_RET_END (2)   // レギュレーションを選択せずに終了


#endif //__COMM_DIRECT_COUNTER_DEF_H__
