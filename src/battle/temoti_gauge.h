//==============================================================================
/**
 * @file	temoti_gauge.h
 * @brief	手持ちゲージのヘッダ
 * @author	matsuda
 * @date	2006.06.14(水)
 */
//==============================================================================
#ifndef __TEMOTI_GAUGE_H__
#define __TEMOTI_GAUGE_H__


//==============================================================================
//	定数定義
//==============================================================================
///手持ちゲージが同時に出る最大数
#define TEMOTIGAUGE_MAX			(2)		//自機側＋敵側

typedef enum{
	TEMOTI_MINE,	///<自機側手持ちゲージ
	TEMOTI_ENEMY,	///<敵側手持ちゲージ
}TEMOTI_SIDE;

///矢印退場動作指定
typedef enum{
	ARROW_OUT_TYPE_SCROLL,		///<スクロールしながら消える
	ARROW_OUT_TYPE_SPOT,		///<その場で消える
}ARROW_OUT_TYPE;

///ボール登場動作指定
typedef enum{
	BALL_IN_TYPE_ENCOUNT,		///<エンカウント時のボールイン
	BALL_IN_TYPE_CHANGE,		///<入れ替え時のボールイン
}BALL_IN_TYPE;

///ボール退場動作指定
typedef enum{
	BALL_OUT_TYPE_ENCOUNT,		///<エンカウント時のボールアウト
	BALL_OUT_TYPE_CHANGE,		///<入れ替え時のボールアウト
}BALL_OUT_TYPE;

///ボール登場位置指定
typedef enum{
	BALL_POS_HIGH,				///<上段に表示
	BALL_POS_MIDDLE,			///<中断に表示
	BALL_POS_LOW,				///<下段に表示
}BALL_POS_TYPE;


//==============================================================================
//	型定義
//==============================================================================
///TEMOTIGAUGE_WORKの不定形ポインタ
typedef struct _TEMOTIGAUGE_WORK * TEMOTIGAUGE_PTR;


//==============================================================================
//	外部関数宣言
//==============================================================================
extern void TEMOTI_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd);
extern void TEMOTI_ResourceFree(CATS_RES_PTR crp);
extern TEMOTIGAUGE_PTR TEMOTI_InEffectSet(u8 status[], TEMOTI_SIDE side, BALL_IN_TYPE ball_in_type,
	BALL_POS_TYPE pos_type, CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void TEMOTI_OutEffectSet(TEMOTIGAUGE_PTR tg, 
	ARROW_OUT_TYPE arrow_out_type, BALL_OUT_TYPE ball_out_type);
extern BOOL TEMOTI_InEffectEndCheck(TEMOTIGAUGE_PTR tg);
extern BOOL TEMOTI_OutEffectEndCheck(TEMOTIGAUGE_PTR tg);
extern void TEMOTI_EffectFree(TEMOTIGAUGE_PTR tg);


#endif	__TEMOTI_GAUGE_H__

