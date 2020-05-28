//============================================================================================
/**
 * @file	vs_demo.h
 * @brief	通信対戦デモ
 * @author	Hiroyuki Nakamura
 * @date	06.04.26
 */
//============================================================================================
#ifndef VS_DEMO_H
#define VS_DEMO_H
#undef GLOBAL
#ifdef VS_DEMO_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


enum {
	VSD_PARTY_LEFT1 = 0,	// 左側パーティのプレイヤー１
	VSD_PARTY_RIGHT1,		// 右側パーティのプレイヤー２
	VSD_PARTY_LEFT2,		// 左側パーティのプレイヤー１
	VSD_PARTY_RIGHT2,		// 右側パーティのプレイヤー２
	VSD_PARTY_MAX
};

typedef struct {
	BATTLE_PARAM * bp;				// 戦闘パラメータ
	POKEPARTY * pp[VSD_PARTY_MAX];	// ポケモンデータ
	STRBUF * name[VSD_PARTY_MAX];	// プレーヤー名
	u32	heap;
	u8	mode;
	u8	type;
	u8	result;
	u8	end_flg;
}VS_DEMO_DATA;

enum {
	VSD_MODE_MULTI = 0,
	VSD_MODE_IN,
	VSD_MODE_END
};

enum {
	VSD_TYPE_NORMAL = 0,
	VSD_TYPE_MULTI,

	VSD_TYPE_LEFT = 0,
	VSD_TYPE_RIGHT
};

enum {
	VSD_RESULT_WIN = 1,		// 勝ち
	VSD_RESULT_LOSE,		// 負け
	VSD_RESULT_DRAW,		// 引き分け
};

//--------------------------------------------------------------------------------------------
/**
 * タスク追加
 *
 * @param	dat		バッグデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void VSDemo_TaskAdd( VS_DEMO_DATA * dat );


#undef GLOBAL
#endif	/* VS_DEMO_H */
