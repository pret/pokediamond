#ifndef __PAST_DEF_H__
#define __PAST_DEF_H__

//必ずsoftsprite.hのenumに合わせる
#define PARA_POS_X	(0)				// X座標
#define PARA_POS_Y	(1)				// Y座標
#define PARA_ROT_CX	(10)			// 回転Xオフセット
#define PARA_AFF_X	(12)			// X方向拡大縮小率
#define PARA_AFF_Y	(13)			// Y方向拡大縮小率
#define PARA_ALPHA	(19)			//アルファ
/**
	SS_PARA_POS_Y,			// Y座標
	SS_PARA_POS_Z,			// Z座標
	SS_PARA_POS_OX,			// X座標オフセット
	SS_PARA_POS_OY,			// Y座標オフセット
	SS_PARA_POS_OZ,			// Z座標オフセット
	SS_PARA_VANISH,			// バニッシュフラグ（0:表示　1:非表示）
	SS_PARA_ROT_X,			// X方向回転角度
	SS_PARA_ROT_Y,			// Y方向回転角度
	SS_PARA_ROT_Z,			// Z方向回転角度
	SS_PARA_ROT_CX,			// 回転中心X座標オフセット
	SS_PARA_ROT_CY,			// 回転中心Y座標オフセット
	SS_PARA_AFF_X,			// X方向拡大縮小率
	SS_PARA_AFF_Y,			// Y方向拡大縮小率
	SS_PARA_VISIBLE,		// ビジブルモードフラグ（0:OFF　1:ON）
	SS_PARA_OFS_POS_X,		// テクスチャ可視範囲左上X座標
	SS_PARA_OFS_POS_Y,		// テクスチャ可視範囲左上Y座標
	SS_PARA_OFS_SIZE_X,		// テクスチャ可視範囲Xサイズ
	SS_PARA_OFS_SIZE_Y,		// テクスチャ可視範囲Yサイズ
	SS_PARA_ALPHA,			// Alpha値
	SS_PARA_PAL_FADE,		// パレットフェードフラグ
	SS_PARA_PAL_RGB,		// パレットフェード RGB値
	SS_PARA_PAL_START_EVY,	// パレットフェード START_EVY値
	SS_PARA_PAL_END_EVY,	// パレットフェード END_EVY値
	SS_PARA_PAL_WAIT,		// パレットフェード WAIT値
	SS_PARA_H_FLIP,			// 左右反転フラグ
	SS_PARA_V_FLIP,			// 上下反転フラグ
	SS_PARA_DRAW_STOP,		// 強制描画ストップ

	SS_PARA_END
*/
#define WORK0 (0)
#define WORK1 (1)
#define WORK2 (2)
#define WORK3 (3)
#define WORK4 (4)
#define WORK5 (5)
#define WORK6 (6)
#define WORK7 (7)

#define PARAM_X (8)
#define PARAM_Y (9)
#define PARAM_DX (10)
#define PARAM_DY (11)
#define PARAM_RX (12)
#define PARAM_RY (13)
#define PARAM_ROT	(14)

#define COMP_MINUS	(15)
#define COMP_PLUS	(16)
#define COMP_EQUAL	(17)

#define CALC_VAL	(18)
#define CALC_WORK	(19)

#define USE_VAL		(20)
#define USE_WORK	(21)

#define PARAM_SET	(22)
#define PARAM_ADD	(23)

#define APPLY_SET	(24)
#define APPLY_ADD	(25)
#define APPLY_SYNTHE		(26)

#define CORRECT_ON_MINUS	(27)
#define CORRECT_OFF			(28)
#define CORRECT_ON_NOT_EQ	(29)



#define CURVE_SIN			(30)
#define CURVE_COS			(31)
#define CURVE_SIN_MINUS		(32)
#define CURVE_COS_MINUS		(33)

#define TARGET_NONE			(34)
#define TARGET_DX			(35)
#define TARGET_DY			(36)
#define TARGET_RX			(37)
#define TARGET_RY			(38)
#define TARGET_ROT			(39)

#endif	//__PAST_DEF_H__
