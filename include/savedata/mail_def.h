/**
 *	@file	mail_def.h
 *	@brief	メールデータ　定数定義ファイル
 *	@author	Miyuki Iwasawa
 *	@date	06.02.09
 */

#ifndef __H_MAIL_DEF_H__
#define __H_MAIL_DEF_H__

#if 0
#define MAIL_STOCK_TEMOTI	(6)		///<手持ちでｽﾄｯｸしておける数
#define MAIL_STOCK_EXTRADE	(1)		///<世界交換
#define MAIL_STOCK_SODATEYA	(2)		///<育て屋メール
#define MAIL_STOCK_MAX	(	MAIL_STOCK_TEMOTI+\
							MAIL_STOCK_PASOCOM+\
							MAIL_STOCK_EXTRADE+\
							MAIL_STOCK_SODATEYA)
#endif
#define MAIL_STOCK_PASOCOM	(20)	///<ﾊﾟｿｺﾝでｽﾄｯｸして置ける数
#define MAIL_STOCK_MAX	(MAIL_STOCK_PASOCOM)

#define MAILDAT_MSGMAX	(3)	///<簡易文要素数
#define MAILDAT_ICONMAX	(3)	///<ポケモンアイコン要素数

///データブロックアクセスID定義
typedef enum{
 MAILBLOCK_PASOCOM,
 MAILBLOCK_MAX,
 MAILBLOCK_TEMOTI,	///<ブロック外データID(手持ち)
// MAILBLOCK_EXTRADE,	///<ブロック外データID(世界交換)
// MAILBLOCK_SODATEYA,///<ブロック外データID(育てやメール)
 MAILBLOCK_NULL,	///<ブロック外データID(無効ID)
}MAILBLOCK_ID;

///デザインNo定義
typedef enum{
 MAIL_DESIGN_START = 0,
 MAIL_DESIGN_00 = 0,
 MAIL_DESIGN_01,
 MAIL_DESIGN_02,
 MAIL_DESIGN_03,
 MAIL_DESIGN_04,
 MAIL_DESIGN_05,
 MAIL_DESIGN_06,
 MAIL_DESIGN_07,
 MAIL_DESIGN_08,
 MAIL_DESIGN_09,
 MAIL_DESIGN_10,
 MAIL_DESIGN_11,
 MAIL_DESIGN_END = 11,
 MAIL_DESIGN_MAX,
 MAIL_DESIGN_NULL = 0xFFFF,	///<無効
}MAIL_DESIGN_NO;

#define MAILDATA_NULLID	(0xFFFFFFFF)
#define MAIL_ICON_NULL	(0xFFFF)
#define MAIL_ICON_CGXN	(0xFFF)
#define MAIL_ICON_PALNULL	(0xF)

///メールポケモンアイコンデータ型
typedef union _MAIL_ICON{
	struct{
		u16	cgxID:12;	///<ポケモンアイコンキャラクタCgxID
		u16	palID:4;	///<ポケモンアイコンパレットID
	};
	u16	dat;
}MAIL_ICON;

#define MAIL_ICONPRM_CGX	(0)
#define MAIL_ICONPRM_PAL	(1)
#define MAIL_ICONPRM_ALL	(2)

#endif	//__H_MAIL_DEF_H__


