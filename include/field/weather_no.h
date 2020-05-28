//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		weatheru_no.h
 *@brief	お天気	ナンバー
 *@author	tomoya takahashi
 *@data		2006.06.08
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]



#ifndef __WEATHER_NO_H__
#define	__WEATHER_NO_H__

//-------------------------------------
//	天気データ列挙	(no)
//
//	企画　天候ナンバー順
//=====================================
enum{
	WEATHER_SYS_SUNNY,			// 晴れ
	WEATHER_SYS_CLOUDINESS,		// 曇り		BG	
	WEATHER_SYS_RAIN,			// 雨		OAM	FOG
	WEATHER_SYS_STRAIN,			// 大雨		OAM FOG 
	WEATHER_SYS_SPARK,			// 大雨		OAM FOG BG
	WEATHER_SYS_SNOW,			// 雪		OAM FOG
	WEATHER_SYS_SNOWSTORM,		// 吹雪		OAM FOG
	WEATHER_SYS_SNOWSTORM_H,	// 猛吹雪	OAM FOG BG
	WEATHER_SYS_FOG,			// 霧大		FOG	
	WEATHER_SYS_VOLCANO,		// 火山灰	OAM FOG BG
	WEATHER_SYS_SANDSTORM,		// BG使用砂嵐	OAM FOG BG
	WEATHER_SYS_DIAMONDDUST,	// スノーダスト	OAM FOG
	WEATHER_SYS_SPIRIT,			// 気合		OAM
	WEATHER_SYS_MYSTIC,			// 神秘		OAM FOG
	WEATHER_SYS_MIST1,			// 霧払いの霧	FOG	BG
	WEATHER_SYS_MIST2,			// 霧払いの霧	FOG	BG
	WEATHER_SYS_FLASH,			// フラッシュ		BG

	WEATHER_SYS_SPARK_EFF,		// 雷		BG
	WEATHER_SYS_FOGS,			// 霧		FOG
	WEATHER_SYS_FOGM,		// 霧中		FOG

// いらなくなる	
#if 1
	WEATHER_SYS_RAINBOW,	// 虹		BG
	WEATHER_SYS_SNOW_STORM_BG,// BG使用吹雪	OAM FOG BG
	WEATHER_SYS_STORM,		// 砂嵐		OAM FOG
#endif

	WEATHER_SYS_NUM,// 天気数
};


#endif // __WEATHER_NO_H__
