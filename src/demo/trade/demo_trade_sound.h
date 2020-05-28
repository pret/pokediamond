#ifndef __DEMO_TRADE_SOUND_H__

#include "system\snd_tool.h"


enum {
	//battle,trcard
	
	//SE_POKE_TO_BALL = SEQ_SE_DP_000,		///< ポケモンがピカッと光ってボールに格納される音
	SE_POKE_TO_BALL = SEQ_SE_DP_KOUKAN01,	///< ポケモンがピカッと光ってボールに格納される音

	SE_BALL_REFRECT = SEQ_SE_DP_KON,		///< ボールが床で跳ねるコン、コンという音

	//何度かコールする
	//SE_BALL_RISE = SEQ_SE_DP_PYUU,		///< ボールが上空に向かってビューンと飛んでいく音
	SE_BALL_RISE = SEQ_SE_DP_KOUKAN06,		///< ボールが上空に向かってビューンと飛んでいく音

	//SE_BALL_KIRARI = SEQ_SE_DP_KIRA,		///< ボールが空に飛んでいってキラーンと星になる音
	SE_BALL_KIRARI = SEQ_SE_DP_KOUKAN07,	///< ボールが空に飛んでいってキラーンと星になる音

	//何度かコールする
	//SE_BALL_FALL = SEQ_SE_DP_PYUU2,		///< ボールが上空からギューンと落ちてくる音
	SE_BALL_FALL = SEQ_SE_DP_KOUKAN05,		///< ボールが上空からギューンと落ちてくる音

	//SE_POKE_CROSS = SEQ_SE_DP_025,		///< ポケモンがすれ違う時のピキーンという音
	//SE_POKE_CROSS = SEQ_SE_DP_KOUKAN04,	///< ポケモンがすれ違う時のピキーンという音
	SE_POKE_CROSS = SEQ_SE_DP_KOUKAN03,		///< ポケモンがすれ違う時のピキーンという音

	//SE_WAVE = SEQ_SE_DP_081,				///< 電波がピリッ、ピリッと出る音
	SE_WAVE = SEQ_SE_DP_KOUKAN08,			///< 電波がピリッ、ピリッと出る音
	
#if 0
	SE_??? = SEQ_SE_DP_KOUKAN09,			///< 
#endif

	ME_FANFARE = SEQ_FANFA5,
};


#endif
