//==============================================================================
/**
 * @file	actin_id.h
 * @brief	演技力部門で使用するアクターのキャラID等の定義
 * @author	matsuda
 * @date	2005.11.30(水)
 */
//==============================================================================
#ifndef __ACTIN_ID_H__
#define __ACTIN_ID_H__


///フォントOBJのID定義で、各ID間で空けるID数
#define ACI_FONT_ID_OFFSET		(10)


//==============================================================================
//	キャラID
//==============================================================================
enum{
	CHARID_START = 33000,
	
	CHARID_JUDGE_0,		///<審判０
	CHARID_JUDGE_1,
	CHARID_JUDGE_2,
	
	CHARID_JUDGE_BOX,	///<審判の入っている箱

	CHARID_SPECIAL_HEART,	///<特別審査員につけるハート
	CHARID_APPEAL_POINT,	///<アピールポイントの点数を表すハート
	CHARID_VOLTAGE_EFF,		///<ボルテージ演出
	CHARID_VOLTAGE_POINT,	///<ボルテージポイントの点数を表すランプ
	CHARID_NEXT_ICON,		///<次アイコン
	
	CHARID_WIN_COVER_0,		///<ウィンドウスクロール時のマスクカバー
	CHARID_WIN_COVER_1,		///<ウィンドウスクロール時のマスクカバー
	CHARID_WIN_COVER_2,		///<ウィンドウスクロール時のマスクカバー
	
	CHARID_JUDGE_REACTION,	///<審判リアクションアイコン
	
	//-- サブ画面 --//
	CHARID_CONTYPE_ICON_1,
	CHARID_CONTYPE_ICON_2,
	CHARID_CONTYPE_ICON_3,
	CHARID_CONTYPE_ICON_4,
	
	CHARID_SUB_HEART_8,		///<技説明文のハート
	CHARID_SUB_HEART_32,	///<凄い審査が出来る審査員につけるハート
	CHARID_SUB_CTYPE_ICON,	///<コンテストタイプアイコン

	CHARID_ACTIN_CURSOR,	///<入力画面カーソル

	//-- フォントOBJ --//
	CHARID_ACI_FONT_JUDGE_1,		///<審判1
	CHARID_ACI_FONT_JUDGE_2 = CHARID_ACI_FONT_JUDGE_1 + ACI_FONT_ID_OFFSET,		///<審判2
	CHARID_ACI_FONT_JUDGE_3 = CHARID_ACI_FONT_JUDGE_2 + ACI_FONT_ID_OFFSET,		///<審判3
	CHARID_ACI_FONT_JUDGE_4 = CHARID_ACI_FONT_JUDGE_3 + ACI_FONT_ID_OFFSET,		///<審判4
	CHARID_ACI_FONT_WAZA_1 = CHARID_ACI_FONT_JUDGE_4 + ACI_FONT_ID_OFFSET,		///<技1
	CHARID_ACI_FONT_WAZA_2 = CHARID_ACI_FONT_WAZA_1 + ACI_FONT_ID_OFFSET,		///<技2
	CHARID_ACI_FONT_WAZA_3 = CHARID_ACI_FONT_WAZA_2 + ACI_FONT_ID_OFFSET,		///<技3
	CHARID_ACI_FONT_WAZA_4 = CHARID_ACI_FONT_WAZA_3 + ACI_FONT_ID_OFFSET,		///<技4
	CHARID_ACI_FONT_SETUMEI_UP_1 = 
		CHARID_ACI_FONT_WAZA_4 + ACI_FONT_ID_OFFSET,		///<技1
	CHARID_ACI_FONT_SETUMEI_UP_2 = 
		CHARID_ACI_FONT_SETUMEI_UP_1 + ACI_FONT_ID_OFFSET,	///<技2
	CHARID_ACI_FONT_SETUMEI_UP_3 = 
		CHARID_ACI_FONT_SETUMEI_UP_2 + ACI_FONT_ID_OFFSET,	///<技3
	CHARID_ACI_FONT_SETUMEI_UP_4 = 
		CHARID_ACI_FONT_SETUMEI_UP_3 + ACI_FONT_ID_OFFSET,	///<技4
	CHARID_ACI_FONT_SETUMEI_DOWN_1 = 
		CHARID_ACI_FONT_SETUMEI_UP_4 + ACI_FONT_ID_OFFSET,		///<技1
	CHARID_ACI_FONT_SETUMEI_DOWN_2 = 
		CHARID_ACI_FONT_SETUMEI_DOWN_1 + ACI_FONT_ID_OFFSET,	///<技2
	CHARID_ACI_FONT_SETUMEI_DOWN_3 = 
		CHARID_ACI_FONT_SETUMEI_DOWN_2 + ACI_FONT_ID_OFFSET,	///<技3
	CHARID_ACI_FONT_SETUMEI_DOWN_4 = 
		CHARID_ACI_FONT_SETUMEI_DOWN_3 + ACI_FONT_ID_OFFSET,	///<技4
	
	//フォントOBJID定義終了
	CHARID_ACI_FONT_ID_END,
	CHARID_ACI_FONT_END = CHARID_ACI_FONT_ID_END + ACI_FONT_ID_OFFSET,
};

//==============================================================================
//	パレットID
//==============================================================================
enum{
	PLTTID_START = 33000,

	PLTTID_OBJ_COMMON,	///<常駐OBJパレット
	
	PLTTID_JUDGE_0,
	PLTTID_JUDGE_1,
	PLTTID_JUDGE_2,

	PLTTID_FONTACT,			///<フォントアクター(ブリーダー名など)

	PLTTID_WIN_COVER,		///<ウィンドウスクロール時のマスクカバー

	//-- サブ画面 --//
	PLTTID_OBJ_COMMON_SUB,	///<サブ画面の常駐OBJパレット
	PLTTID_SUB_FONTACT,		///<サブ画面のフォントアクター
	PLTTID_ACTIN_CURSOR,	///<入力画面カーソル
};

//--------------------------------------------------------------
//	常駐OBJパレットオフセット
//--------------------------------------------------------------
enum{
	PALOFS_JUDGE_BOX_LEFT = 2,		///<審判ボックス(左)のパレットオフセット
	PALOFS_JUDGE_BOX_CENTER = 4,	///<審判ボックス(中央)のパレットオフセット
	PALOFS_JUDGE_BOX_RIGHT = 5,		///<審判ボックス(右)のパレットオフセット
	PALOFS_SPECIAL_HEART = 0,	///<特別審査員につけるハート
	PALOFS_APPEAL_POINT = 3,	///<アピールポイントの点数を表すハート
	PALOFS_VOLTAGE_EFF = 0,		///<ボルテージ演出
	PALOFS_VOLTAGE_POINT = 2,	///<ボルテージポイントの点数を表すランプ
	PALOFS_NEXT_ICON = 0,		///<次アイコン
	PALOFS_JUDGE_REACTION = 0,	///<審判リアクションアイコン
	
	ACTIN_COMMON_PAL_NUM = 6,	///<常駐OBJパレットの本数
};

//--------------------------------------------------------------
//	サブ画面の常駐OBJパレットオフセット
//--------------------------------------------------------------
enum{
	PALOFS_SUB_HEART_8 = 0,			///<技説明文のハート(AP値)
	PALOFS_SUB_HEART_BLACK_8 = 1,	///<技説明文のハート(妨害値)
	PALOFS_SUB_HEART_32 = 0,		///<凄い審査が出来る審査員につけるハート
	PALOFS_SUB_CTYPE_ICON = 1,		///<コンテストタイプアイコン
	
	ACTIN_SUB_COMMON_PAL_NUM = 3,	///<サブ画面の常駐OBJパレットの本数
};

//==============================================================================
//	セルID
//==============================================================================
enum{
	CELLID_START = 33000,

	CELLID_JUDGE_0,
	CELLID_JUDGE_1,
	CELLID_JUDGE_2,

	CELLID_JUDGE_BOX,	///<審判の入っている箱

	CELLID_SPECIAL_HEART,	///<特別審査員につけるハート
	CELLID_APPEAL_POINT,	///<アピールポイントの点数を表すハート
	CELLID_VOLTAGE_EFF,		///<ボルテージ演出
	CELLID_VOLTAGE_POINT,	///<ボルテージポイントの点数を表すランプ

	CELLID_NEXT_ICON,		///<次アイコン

	CELLID_WIN_COVER,		///<ウィンドウスクロール時のマスクカバー

	CELLID_JUDGE_REACTION,	///<審判リアクションアイコン

	//-- サブ画面 --//
	CELLID_CONTYPE_ICON,

	CELLID_SUB_HEART_8,		///<技説明文のハート
	CELLID_SUB_HEART_32,	///<凄い審査が出来る審査員につけるハート
	CELLID_SUB_CTYPE_ICON,	///<コンテストタイプアイコン
	CELLID_ACTIN_CURSOR,	///<入力画面カーソル

	//-- フォントOBJ --//
	CELLID_ACI_FONT_JUDGE_1,		///<審判1
	CELLID_ACI_FONT_JUDGE_2 = CELLID_ACI_FONT_JUDGE_1 + ACI_FONT_ID_OFFSET,		///<審判2
	CELLID_ACI_FONT_JUDGE_3 = CELLID_ACI_FONT_JUDGE_2 + ACI_FONT_ID_OFFSET,		///<審判3
	CELLID_ACI_FONT_JUDGE_4 = CELLID_ACI_FONT_JUDGE_3 + ACI_FONT_ID_OFFSET,		///<審判4
	CELLID_ACI_FONT_WAZA_1 = CELLID_ACI_FONT_JUDGE_4 + ACI_FONT_ID_OFFSET,		///<技1
	CELLID_ACI_FONT_WAZA_2 = CELLID_ACI_FONT_WAZA_1 + ACI_FONT_ID_OFFSET,		///<技2
	CELLID_ACI_FONT_WAZA_3 = CELLID_ACI_FONT_WAZA_2 + ACI_FONT_ID_OFFSET,		///<技3
	CELLID_ACI_FONT_WAZA_4 = CELLID_ACI_FONT_WAZA_3 + ACI_FONT_ID_OFFSET,		///<技4
	CELLID_ACI_FONT_SETUMEI_UP_1 = 
		CELLID_ACI_FONT_WAZA_4 + ACI_FONT_ID_OFFSET,		///<技1
	CELLID_ACI_FONT_SETUMEI_UP_2 = 
		CELLID_ACI_FONT_SETUMEI_UP_1 + ACI_FONT_ID_OFFSET,	///<技2
	CELLID_ACI_FONT_SETUMEI_UP_3 = 
		CELLID_ACI_FONT_SETUMEI_UP_2 + ACI_FONT_ID_OFFSET,	///<技3
	CELLID_ACI_FONT_SETUMEI_UP_4 = 
		CELLID_ACI_FONT_SETUMEI_UP_3 + ACI_FONT_ID_OFFSET,	///<技4
	CELLID_ACI_FONT_SETUMEI_DOWN_1 = 
		CELLID_ACI_FONT_SETUMEI_UP_4 + ACI_FONT_ID_OFFSET,		///<技1
	CELLID_ACI_FONT_SETUMEI_DOWN_2 = 
		CELLID_ACI_FONT_SETUMEI_DOWN_1 + ACI_FONT_ID_OFFSET,	///<技2
	CELLID_ACI_FONT_SETUMEI_DOWN_3 = 
		CELLID_ACI_FONT_SETUMEI_DOWN_2 + ACI_FONT_ID_OFFSET,	///<技3
	CELLID_ACI_FONT_SETUMEI_DOWN_4 = 
		CELLID_ACI_FONT_SETUMEI_DOWN_3 + ACI_FONT_ID_OFFSET,	///<技4
	
	//フォントOBJID定義終了
	CELLID_ACI_FONT_ID_END,
	CELLID_ACI_FONT_END = CELLID_ACI_FONT_ID_END + ACI_FONT_ID_OFFSET,
};

//==============================================================================
//	セルアニメID
//==============================================================================
enum{
	CELLANMID_START = 33000,

	CELLANMID_JUDGE_0,
	CELLANMID_JUDGE_1,
	CELLANMID_JUDGE_2,

	CELLANMID_JUDGE_BOX,	///<審判の入っている箱

	CELLANMID_SPECIAL_HEART,	///<特別審査員につけるハート
	CELLANMID_APPEAL_POINT,	///<アピールポイントの点数を表すハート
	CELLANMID_VOLTAGE_EFF,		///<ボルテージ演出
	CELLANMID_VOLTAGE_POINT,	///<ボルテージポイントの点数を表すランプ

	CELLANMID_NEXT_ICON,		///<次アイコン

	CELLANMID_WIN_COVER,		///<ウィンドウスクロール時のマスクカバー

	CELLANMID_JUDGE_REACTION,	///<審判リアクションアイコン

	//-- サブ画面 --//
	CELLANMID_CONTYPE_ICON,

	CELLANMID_SUB_HEART_8,		///<技説明文のハート
	CELLANMID_SUB_HEART_32,		///<凄い審査が出来る審査員につけるハート
	CELLANMID_SUB_CTYPE_ICON,	///<コンテストタイプアイコン
	CELLANMID_ACTIN_CURSOR,	///<入力画面カーソル

	//-- フォントOBJ --//
	CELLANMID_ACI_FONT_JUDGE_1,		///<審判1
	CELLANMID_ACI_FONT_JUDGE_2 = CELLANMID_ACI_FONT_JUDGE_1 + ACI_FONT_ID_OFFSET,		///<審判2
	CELLANMID_ACI_FONT_JUDGE_3 = CELLANMID_ACI_FONT_JUDGE_2 + ACI_FONT_ID_OFFSET,		///<審判3
	CELLANMID_ACI_FONT_JUDGE_4 = CELLANMID_ACI_FONT_JUDGE_3 + ACI_FONT_ID_OFFSET,	///<審判4
	CELLANMID_ACI_FONT_WAZA_1 = CELLANMID_ACI_FONT_JUDGE_4 + ACI_FONT_ID_OFFSET,		///<技1
	CELLANMID_ACI_FONT_WAZA_2 = CELLANMID_ACI_FONT_WAZA_1 + ACI_FONT_ID_OFFSET,		///<技2
	CELLANMID_ACI_FONT_WAZA_3 = CELLANMID_ACI_FONT_WAZA_2 + ACI_FONT_ID_OFFSET,		///<技3
	CELLANMID_ACI_FONT_WAZA_4 = CELLANMID_ACI_FONT_WAZA_3 + ACI_FONT_ID_OFFSET,	///<技4
	CELLANMID_ACI_FONT_SETUMEI_UP_1 = 
		CELLANMID_ACI_FONT_WAZA_4 + ACI_FONT_ID_OFFSET,		///<技1
	CELLANMID_ACI_FONT_SETUMEI_UP_2 = 
		CELLANMID_ACI_FONT_SETUMEI_UP_1 + ACI_FONT_ID_OFFSET,	///<技2
	CELLANMID_ACI_FONT_SETUMEI_UP_3 = 
		CELLANMID_ACI_FONT_SETUMEI_UP_2 + ACI_FONT_ID_OFFSET,	///<技3
	CELLANMID_ACI_FONT_SETUMEI_UP_4 = 
		CELLANMID_ACI_FONT_SETUMEI_UP_3 + ACI_FONT_ID_OFFSET,	///<技4
	CELLANMID_ACI_FONT_SETUMEI_DOWN_1 = 
		CELLANMID_ACI_FONT_SETUMEI_UP_4 + ACI_FONT_ID_OFFSET,		///<技1
	CELLANMID_ACI_FONT_SETUMEI_DOWN_2 = 
		CELLANMID_ACI_FONT_SETUMEI_DOWN_1 + ACI_FONT_ID_OFFSET,	///<技2
	CELLANMID_ACI_FONT_SETUMEI_DOWN_3 = 
		CELLANMID_ACI_FONT_SETUMEI_DOWN_2 + ACI_FONT_ID_OFFSET,	///<技3
	CELLANMID_ACI_FONT_SETUMEI_DOWN_4 = 
		CELLANMID_ACI_FONT_SETUMEI_DOWN_3 + ACI_FONT_ID_OFFSET,	///<技4
	
	//フォントOBJID定義終了
	CELLANMID_ACI_FONT_ID_END,
	CELLANMID_ACI_FONT_END = CELLANMID_ACI_FONT_ID_END + ACI_FONT_ID_OFFSET,
};

//==============================================================================
//	マルチセルID
//==============================================================================
enum{
	MCELLID_START = 33000,
};

//==============================================================================
//	マルチセルアニメID
//==============================================================================
enum{
	MCELLANMID_START = 33000,
};



#endif	//__ACTIN_ID_H__

