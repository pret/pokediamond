//==============================================================================
/**
 * @file	wpcb_def.h
 * @brief	基本構造体 wpcb_xxx.c しか、includeしてはいけない
 * @author	goto
 * @date	2006.02.12(日)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#ifndef __WPCB_DEF_H__
#define __WPCB_DEF_H__

// -----------------------------------------
//
//	□ プログラム中で扱う
//
// -----------------------------------------
#define OPERATOR_AXIS_PARAM_MAX		(3)				///< 方向がEX_DATAから取得する値の数
#define OPERATOR_POS_PARAM_MAX		(3)				///< 座標がEX_DATAから取得する値の数
#define OPERATOR_REVERCE_FLAG_OFF	(1)				///< 反転フラグ
#define OPERATOR_REVERCE_FLAG_ON	(-1)			///< 反転フラグ

// -----------------------------------------
//
//	□ *.s で扱う
//
// -----------------------------------------
#define OPERATOR_EX_REVERCE_ON			(0)			///< *[ 共通 ] 位置反転あり
#define OPERATOR_EX_REVERCE_OFF			(1)			///< *[ 共通 ] 位置反転無し

#define OPERATOR_DEF_DATA_NUM			(6)			///< データ種類

#define OPERATOR_PRI_NONE				(0)			///< *[ 優先度 ] 
#define OPERATOR_PRI_FRONT				(1)			///< 前面
#define OPERATOR_PRI_BACK				(2)			///< 背面
#define OPERATOR_PRI_Z					(3)			///< Z

#define OPERATOR_DEF_FZ_AA				(256)		///< 前面用基本Z
#define OPERATOR_DEF_BZ_AA				(0)			///< 背面用基本Z
#define OPERATOR_DEF_FZ_BB				(-5120)		///< 前面用基本Z
#define OPERATOR_DEF_BZ_BB				(-5376)		///< 背面用基本Z

#define OPERATOR_TARGET_NONE			(0)			///< *[ ﾀｰｹﾞｯﾄ ] TARGET_NONE == POS_NONE
#define OPERATOR_TARGET_AT				(1)
#define OPERATOR_TARGET_DF				(2)
#define OPERATOR_TARGET_AT_SIDE			(3)
#define OPERATOR_TARGET_DF_SIDE			(4)


#define OPERATOR_POS_NONE				(0)			///< *[ 座標 ]
#define OPERATOR_POS_SP					(1)			///< 開始
#define OPERATOR_POS_EP					(2)			///< 終了
#define OPERATOR_POS_SET				(3)			///< ユーザー指定
#define OPERATOR_POS_SP_OFS				(4)			///< 開始+ofs
#define OPERATOR_POS_EP_OFS				(5)			///< 終了+ofs
#define OPERATOR_POS_LSP				(6)			///< レーザー開始
#define OPERATOR_POS_LEP				(7)			///< レーザー終了
#define OPERATOR_POS_RSP				(8)			///< リング開始
#define OPERATOR_POS_REP				(9)			///< リング終了
#define OPERATOR_POS_L2SP				(10)		///< レーザー開始
#define OPERATOR_POS_L2EP				(11)		///< レーザー終了
#define OPERATOR_POS_AT_SIDE_OFS		(12)		///< 開始+ofs
#define OPERATOR_POS_DF_SIDE_OFS		(13)		///< 終了+ofs
#define OPERATOR_POS_L3SP				(14)		///< レーザー開始
#define OPERATOR_POS_L3EP				(15)		///< レーザー終了
#define OPERATOR_POS_L095SP				(16)		///< レーザー開始
#define OPERATOR_POS_L095EP				(17)		///< レーザー終了
#define OPERATOR_POS_L161SP				(18)		///< レーザー開始
#define OPERATOR_POS_L161EP				(19)		///< レーザー終了
#define OPERATOR_POS_L308SP				(20)		///< レーザー開始
#define OPERATOR_POS_L308EP				(21)		///< レーザー終了
#define OPERATOR_POS_L304SP				(22)		///< レーザー開始
#define OPERATOR_POS_L304EP				(23)		///< レーザー終了
#define OPERATOR_POS_L320SP				(24)		///< レーザー開始
#define OPERATOR_POS_L320EP				(25)		///< レーザー終了
#define OPERATOR_POS_L406SP				(26)		///< レーザー開始
#define OPERATOR_POS_L406EP				(27)		///< レーザー終了
#define OPERATOR_POS_145_CON			(28)		///< コンテスト：泡
#define OPERATOR_POS_169_CON			(29)		///< コンテスト：いと
#define OPERATOR_POS_226				(30)		///< バトンタッチ
#define OPERATOR_POS_145				(31)		///< 泡
#define OPERATOR_POS_225				(32)		///< りゅうのいぶき
#define OPERATOR_POS_389_CON			(33)		///< コンテスト：
#define OPERATOR_POS_194				(34)		///< コンテスト：

#define OPERATOR_POS_SP_OFS_ALL			(100)		///< 開始側からのオフセット全指定
#define OPERATOR_POS_EP_OFS_ALL			(101)		///< 終了側からのオフセット全指定


#define OPERATOR_AXIS_NONE				(0)			///< *[ 方向 ]
#define OPERATOR_AXIS_AT				(1)
#define OPERATOR_AXIS_DF				(2)
#define OPERATOR_AXIS_SET				(3)
#define OPERATOR_AXIS_AT_SIDE			(4)
#define OPERATOR_AXIS_DF_SIDE			(5)
#define OPERATOR_AXIS_AT_OLD			(6)
#define OPERATOR_AXIS_DF_OLD			(7)
#define OPERATOR_AXIS_AT_3				(8)			///< 3 サイケ光線など
#define OPERATOR_AXIS_DF_3				(9)
#define OPERATOR_AXIS_AT_095			(10)		///< 095
#define OPERATOR_AXIS_DF_095			(11)
#define OPERATOR_AXIS_AT_161			(12)		///< 308
#define OPERATOR_AXIS_DF_161			(13)
#define OPERATOR_AXIS_AT_308			(14)		///< 308
#define OPERATOR_AXIS_DF_308			(15)
#define OPERATOR_AXIS_AT_304			(16)		///< 308
#define OPERATOR_AXIS_DF_304			(17)
#define OPERATOR_AXIS_AT_320			(18)		///< 308
#define OPERATOR_AXIS_DF_320			(19)
#define OPERATOR_AXIS_AT_406			(20)		///< 308
#define OPERATOR_AXIS_DF_406			(21)
#define OPERATOR_AXIS_145_CON			(22)		///< コンテスト：泡
#define OPERATOR_AXIS_169_CON			(23)		///< コンテスト：いと
#define OPERATOR_AXIS_145				(24)		///< 泡
#define OPERATOR_AXIS_389_CON			(25)		///< コンテスト：
#define OPERATOR_AXIS_194				(26)		///< みちづれ


#define OPERATOR_FLD_NONE				(0x0000)	///< *[ ﾌｨｰﾙﾄﾞ ]
#define OPERATOR_FLD_GRAVITY_MAG		(0x0002)	///< VecFx16
#define OPERATOR_FLD_RANDOM_MAG			(0x0004)	///< VecFx16
#define OPERATOR_FLD_RANDOM_INTVL		(0x0008)	///< u16
#define OPERATOR_FLD_MAGNET_POS			(0x0010)	///< VecFx32
#define OPERATOR_FLD_MAGNET_MAG			(0x0020)	///< fx16
#define OPERATOR_FLD_SPIN_RAD			(0x0040)	///< u16
#define OPERATOR_FLD_SPIN_AXIS			(0x0080)	///< u16
#define OPERATOR_FLD_SIMPLE_CLS_Y		(0x0100)	///< fx32
#define OPERATOR_FLD_SIMPLE_CLS_CB		(0x0200)	///< fx16
#define OPERATOR_FLD_SIMPLE_CLS_EVT		(0x0400)	///< 2bit
#define OPERATOR_FLD_SIMPLE_CLS_GLB		(0x0800)	///< 1bit
#define OPERATOR_FLD_CONVERGENCE_POS	(0x1000)	///< VecFx32
#define OPERATOR_FLD_CONVERGENCE_RATIO	(0x2000)	///< fx16
#define OPERATOR_FLD_END				(0xFEFE)	///< 

///< EX_DATA に付随する
#define OPERATOR_FLD_EX_DATA_NUM		(5)			///< mode, flip, x, y, z
#define OPERATOR_FLD_DEFAULT			(0)			///< 通常の値を設定
#define OPERATOR_FLD_SET				(1)			///< 後ろに続く値を設定
#define OPERATOR_FLD_AT					(2)			///< 攻撃側の基本位置へ設定
#define OPERATOR_FLD_DF					(3)			///< 対象側の基本位置へ設定
#define OPERATOR_FLD_SET_DF				(4)			///< 後ろに続く値　2個のパーセント 3, 4 なら　3/4
#define OPERATOR_FLD_NO_DATA			(0xFF)		///< 指定無し

#define OPERATOR_CAMERA_NONE			(0)			///< *[ ｶﾒﾗ ]
#define OPERATOR_CAMERA_SPIN			(1)			///< スピン向カメラ設定
#define OPERATOR_CAMERA_SET				(2)			///< ユーザーカメラ指定
#define OPERATOR_CAMERA_MOVE			(3)			///< 移動カメラ指定
#define OPERATOR_CAMERA_145				(4)			///< 移動カメラ指定
#define OPERATOR_CAMERA_169_CON			(5)			///< 移動カメラ指定
#define OPERATOR_CAMERA_126				(6)			///< 移動カメラ指定
#define OPERATOR_CAMERA_AT				(7)			///< 攻撃側カメラ指定
#define OPERATOR_CAMERA_DF				(8)			///< 防御側カメラ指定

///< EX_DATA に付随する
#define OPERATOR_CAMERA_EX_DATA_NUM		(4)			///< flip, x, y, z

///< 基本値
#define OPERATOR_SET_CENTER				(0)			///< 原点

#endif

