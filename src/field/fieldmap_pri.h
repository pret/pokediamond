//============================================================================================
/**
 * @file	fieldmap_pri.h
 * @brief	フィールドマップ内で動作するタスクのプライオリティ定義
 */
//============================================================================================

#ifndef	__FIELDMAP_PRI_H__
#define	__FIELDMAP_PRI_H__

typedef enum {
	FLDMAP_PRI_POKETCH = 0,				///<ポケッチ

	FLDMAP_PRI_PLACENAME = 0,			///<地名表示ウィンドウ

	FLDMAP_PRI_DIVMAP_MODEL = 1,		///<地形モデルデータ読み込み
	FLDMAP_PRI_DIVMAP_HEIGHT = 1,		///<地形たかさデータ読み込み

	FLDMAP_PRI_MSGICON = 0,				///<進行ウィンドウのアイコン制御
	FLDMAP_PRI_SCRIPT_MENU = 0,			///<スクリプト呼び出しメニュー
	FLDMAP_PRI_OBJSYS = 5,				///<動作モデル制御の基準プライオリティ

	FLDMAP_PRI_WEATHER_CHG = 0,			///<天候システム：変更
	FLDMAP_PRI_WEATHER_DIVINIT = 1,		///<天候システム：初期化
	FLDMAP_PRI_WEATHER_MAIN = 4,		///<天候システム：メイン

	FLDMAP_PRI_ENCOUNT_EFF = 5,			///<エンカウントエフェクト
	FLDMAP_PRI_UG_CHG_EFF = 5,			///<炭鉱移動エフェクト

	FLDMAP_PRI_UNION_MAIN = 10,			///<ユニオンルーム制御
	FLDMAP_PRI_UNION_VIEW = 11,			///<ユニオンルーム表示

	FLDMAP_PRI_UG_COMMON = 100,			///<炭鉱の基準プライオリティ

	FLDMAP_PRI_VOICE_CTRL = 0,			///<鳴き声制御
	FLDMAP_PRI_QUICK_SAND	= 2,		///<流砂アニメ監視
	FLDMAP_PRI_BASE_PANEL = 0,			///<秘密基地パネルカーソル
	FLDMAP_PRI_DEBUGPRINT	= 0x10000,
}FLDMAP_PRI;


#endif	/* __FIELDMAP_PRI_H__ */
