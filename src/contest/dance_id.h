//==============================================================================
/**
 * @file	dance_id.h
 * @brief	ダンス部門で使用するアクターのキャラID等の定義
 * @author	matsuda
 * @date	2005.12.12(月)
 */
//==============================================================================
#ifndef __DANCE_ID_H__
#define __DANCE_ID_H__


///フォントOBJのID定義で、各ID間で空けるID数
#define DCI_FONT_ID_OFFSET		(10)


//==============================================================================
//	キャラID
//==============================================================================
enum{
	D_CHARID_START = 33000,
	
	D_CHARID_MUSIC_BAR8,		///<曲の進行を示すバー
	D_CHARID_MUSIC_BAR32,
	D_CHARID_ONPU_B,			///<音符(青)
	D_CHARID_ONPU_G,			///<音符(緑)
	D_CHARID_ONPU_R,			///<音符(赤)
	D_CHARID_ONPU_Y,			///<音符(黄)
	D_CHARID_REVIEW,			///<評価パネル
	D_CHARID_MY_CURSOR,			///<自分を指すカーソル
	D_CHARID_PRIN,				///<プリン
	D_CHARID_SHADOW,			///<影
	D_CHARID_SPOTLIGHT,			///<スポットライト
	D_CHARID_STAR,				///<星
	

	//-- サブ画面 --//
	
	
	//-- フォントOBJ --//
	D_CHARID_DCI_FONT_FORWARD,		///<まえ
	D_CHARID_DCI_FONT_BACK = D_CHARID_DCI_FONT_FORWARD + DCI_FONT_ID_OFFSET,	///<うしろ
	D_CHARID_DCI_FONT_LEFT = D_CHARID_DCI_FONT_BACK + DCI_FONT_ID_OFFSET,		///<ひだり
	D_CHARID_DCI_FONT_RIGHT = D_CHARID_DCI_FONT_LEFT + DCI_FONT_ID_OFFSET,		///<みぎ
	
	//フォントOBJID定義終了
	D_CHARID_DCI_FONT_ID_END,
	D_CHARID_DCI_FONT_END = D_CHARID_DCI_FONT_ID_END + DCI_FONT_ID_OFFSET,
};

//==============================================================================
//	パレットID
//==============================================================================
enum{
	D_PLTTID_START = 33000,

	D_PLTTID_OBJ_COMMON,	///<常駐OBJパレット
	
	//-- サブ画面 --//
	D_PLTTID_OBJ_COMMON_SUB,	///<サブ画面の常駐OBJパレット
	D_PLTTID_SUB_FONTACT,		///<サブ画面のフォントOBJ用パレット
};

//--------------------------------------------------------------
//	常駐OBJパレットオフセット
//--------------------------------------------------------------
enum{
	PALOFS_MUSIC_BAR = 0,		///<2006.03.14(火) 現在未使用
	PALOFS_ONPU_B = 2,
	PALOFS_ONPU_G = 2,
	PALOFS_ONPU_R = 7,
	PALOFS_ONPU_Y = 6,
	PALOFS_REVIEW = 3,
	PALOFS_MY_CURSOR = 1,
	PALOFS_PRIN = 5,
	PALOFS_SHADOW = 1,
	PALOFS_SPOTLIGHT = 4,
	PALOFS_STAR = 3,
	
	DANCE_COMMON_PAL_NUM = 8,	///<常駐OBJパレットの本数
};

//--------------------------------------------------------------
//	サブ画面の常駐OBJパレットオフセット
//--------------------------------------------------------------
enum{
	
	DANCE_SUB_COMMON_PAL_NUM = 2,	///<サブ画面の常駐OBJパレットの本数
};

//==============================================================================
//	セルID
//==============================================================================
enum{
	D_CELLID_START = 33000,

	D_CELLID_MUSIC_BAR8,		///<曲の進行を示すバー
	D_CELLID_MUSIC_BAR32,
	D_CELLID_ONPU,				///<音符
	D_CELLID_REVIEW,			///<評価パネル
	D_CELLID_MY_CURSOR,			///<自分を指すカーソル
	D_CELLID_PRIN,				///<プリン
	D_CELLID_SHADOW,			///<影
	D_CELLID_SPOTLIGHT,			///<スポットライト
	D_CELLID_STAR,				///<星


	//-- サブ画面 --//
	
	
	//-- フォントOBJ --//
	D_CELLID_DCI_FONT_FORWARD,		///<まえ
	D_CELLID_DCI_FONT_BACK = D_CELLID_DCI_FONT_FORWARD + DCI_FONT_ID_OFFSET,	///<うしろ
	D_CELLID_DCI_FONT_LEFT = D_CELLID_DCI_FONT_BACK + DCI_FONT_ID_OFFSET,		///<ひだり
	D_CELLID_DCI_FONT_RIGHT = D_CELLID_DCI_FONT_LEFT + DCI_FONT_ID_OFFSET,		///<みぎ
	
	//フォントOBJID定義終了
	D_CELLID_DCI_FONT_ID_END,
	D_CELLID_DCI_FONT_END = D_CELLID_DCI_FONT_ID_END + DCI_FONT_ID_OFFSET,
};

//==============================================================================
//	セルアニメID
//==============================================================================
enum{
	D_CELLANMID_START = 33000,

	D_CELLANMID_MUSIC_BAR8,		///<曲の進行を示すバー
	D_CELLANMID_MUSIC_BAR32,
	D_CELLANMID_ONPU,			///<音符
	D_CELLANMID_REVIEW,			///<評価パネル
	D_CELLANMID_MY_CURSOR,			///<自分を指すカーソル
	D_CELLANMID_PRIN,				///<プリン
	D_CELLANMID_SHADOW,			///<影
	D_CELLANMID_SPOTLIGHT,			///<スポットライト
	D_CELLANMID_STAR,				///<星


	//-- サブ画面 --//
	
	
	//-- フォントOBJ --//
	D_CELLANMID_DCI_FONT_FORWARD,		///<まえ
	D_CELLANMID_DCI_FONT_BACK = D_CELLANMID_DCI_FONT_FORWARD + DCI_FONT_ID_OFFSET,	///<うしろ
	D_CELLANMID_DCI_FONT_LEFT = D_CELLANMID_DCI_FONT_BACK + DCI_FONT_ID_OFFSET,		///<ひだり
	D_CELLANMID_DCI_FONT_RIGHT = D_CELLANMID_DCI_FONT_LEFT + DCI_FONT_ID_OFFSET,		///<みぎ
	
	//フォントOBJID定義終了
	D_CELLANMID_DCI_FONT_ID_END,
	D_CELLANMID_DCI_FONT_END = D_CELLANMID_DCI_FONT_ID_END + DCI_FONT_ID_OFFSET,
};

//==============================================================================
//	マルチセルID
//==============================================================================
enum{
	D_MCELLID_START = 33000,
};

//==============================================================================
//	マルチセルアニメID
//==============================================================================
enum{
	D_MCELLANMID_START = 33000,
};



#endif	//__DANCE_ID_H__

