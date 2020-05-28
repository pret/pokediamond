//============================================================================================
/**
 * @file	poketch_map.h
 * @bfief	ポケッチ（フィールドマップ表示アプリ共通ヘッダ）
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_MAP_H_
#define _POKETCH_MAP_H_

//------------------------------------------------------
/**
 *	アニメシーケンス
 */
//------------------------------------------------------
enum {
	POKETCH_MAPACT_ANMSEQ_PLAYERCURSOR,
	POKETCH_MAPACT_ANMSEQ_MARK1,
	POKETCH_MAPACT_ANMSEQ_MARK2,
	POKETCH_MAPACT_ANMSEQ_MARK3,
	POKETCH_MAPACT_ANMSEQ_MARK4,
	POKETCH_MAPACT_ANMSEQ_MARK5,
	POKETCH_MAPACT_ANMSEQ_MARK6,
	POKETCH_MAPACT_ANMSEQ_SEED,
	POKETCH_MAPACT_ANMSEQ_MARK1_EXPAND,
	POKETCH_MAPACT_ANMSEQ_MARK2_EXPAND,
	POKETCH_MAPACT_ANMSEQ_MARK3_EXPAND,
	POKETCH_MAPACT_ANMSEQ_MARK4_EXPAND,
	POKETCH_MAPACT_ANMSEQ_MARK5_EXPAND,
	POKETCH_MAPACT_ANMSEQ_MARK6_EXPAND,
	POKETCH_MAPACT_ANMSEQ_HIDEMAP1,
	POKETCH_MAPACT_ANMSEQ_HIDEMAP2,
	POKETCH_MAPACT_ANMSEQ_HIDEMAP3,
	POKETCH_MAPACT_ANMSEQ_HIDEMAP4,
	POKETCH_MAPACT_ANMSEQ_MOVEPOKE,
};


//------------------------------------------------------
/**
 *	定数
 */
//------------------------------------------------------
enum {
	POKETCH_HIDEMAP_MAX = 4,	///< 隠しマップエリア数
};



extern void PoketchMap_GridToDot( u32 glid_x, u32 glid_y, u32* dot_x, u32* dot_y );
extern void PoketchMap_GetHideMapPos( int hidemapID, u32* x, u32 *y );
extern BOOL PoketchMap_GetMovePokePos( int zone_id, u32* x, u32* y );

#endif
