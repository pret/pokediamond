/**
 *	@file	poruto_def.h
 *	@brief	ポルトデータ　定数定義ファイル
 *	@author	Miyuki Iwasawa
 *	@date	06.02.28
 */

#ifndef __H_PORUTO_DEF_H__
#define __H_PORUTO_DEF_H__

#define PORUTO_STOCK_MAX	(100)	///<ケースに入れておける数
#define PORUTO_PARAM_MAX	(255)	///<味のパラメータMAX値
#define PORUTO_PARAM_VMAX	(99)	///<味のパラメータ描画上限値
#define PORUTO_DATA_NULL	(0xFFFF)	///<空き領域がないときに返る値
#define PORUTO_MILD_VALUE	(50)	///<「マイルド」と判定される値

///ポルトセーブデータのパラメータ参照ID
typedef enum{
 PORUTO_PARAID_FLAVOR,
 PORUTO_PARAID_SPICY,
 PORUTO_PARAID_ASTR,
 PORUTO_PARAID_SWEET,
 PORUTO_PARAID_BITTER,
 PORUTO_PARAID_SOUR,
 PORUTO_PARAID_TASTE,
 PORUTO_PARAID_NUM,
}PORUTO_PARAID;

//味ID
typedef enum{
 PORUTO_FLAVOR_SPICY,	///<辛い
 PORUTO_FLAVOR_SP_AS,	///<からしぶ
 PORUTO_FLAVOR_SP_SW,	///<からあま
 PORUTO_FLAVOR_SP_BI,	///<からにが
 PORUTO_FLAVOR_SP_SO,	///<からすっぱ
 PORUTO_FLAVOR_AS_SP,	///<しぶから
 PORUTO_FLAVOR_ASTR,	///<渋い
 PORUTO_FLAVOR_AS_SW,	///<しぶあま
 PORUTO_FLAVOR_AS_BI,	///<しぶにが
 PORUTO_FLAVOR_AS_SO,	///<しぶすっぱ
 PORUTO_FLAVOR_SW_SP,	///<あまから
 PORUTO_FLAVOR_SW_AS,	///<あましぶ
 PORUTO_FLAVOR_SWEET,	///<甘い
 PORUTO_FLAVOR_SW_BI,	///<あまにが
 PORUTO_FLAVOR_SW_SO,	///<あまずっぱ
 PORUTO_FLAVOR_BI_SP,	///<にがから
 PORUTO_FLAVOR_BI_AS,	///<にがしぶ
 PORUTO_FLAVOR_BI_SW,	///<にがあま
 PORUTO_FLAVOR_BITTER,	///<苦い
 PORUTO_FLAVOR_BI_SO,	///<にがすっぱ
 PORUTO_FLAVOR_SO_SP,	///<すっぱから
 PORUTO_FLAVOR_SO_AS,	///<すっぱしぶ
 PORUTO_FLAVOR_SO_SW,	///<すっぱあま
 PORUTO_FLAVOR_SO_BI,	///<すっぱにが
 PORUTO_FLAVOR_SOUR,	///<酸っぱい
 PORUTO_FLAVOR_HEAVY,	///<こってり
 PORUTO_FLAVOR_THICK,	///<くどい
 PORUTO_FLAVOR_NGOOD,	///<まずい
 PORUTO_FLAVOR_MILD,	///<まろやか
 PORUTO_FLAVOR_MAX,		///<味の種類数
 PORUTO_FLAVOR_NULL,	///<無効値
}PORUTO_FLAVORID;

///味タイプ
typedef enum{
 PORUTO_FTYPE_SPICY,	///<辛い系
 PORUTO_FTYPE_ASTR,		///<渋い系
 PORUTO_FTYPE_SWEET,	///<甘い系
 PORUTO_FTYPE_BITTER,	///<苦い系
 PORUTO_FTYPE_SOUR,		///<酸っぱい系
 PORUTO_FTYPE_MIX,		///<ミックス
 PORUTO_FTYPE_MAX,
 PORUTO_FTYPE_NUM = 5,	///<一系統の数
}PORUTO_FTYPE;

#endif	//__H_PORUTO_DEF_H__

