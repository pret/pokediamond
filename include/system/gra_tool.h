//==============================================================================
/**
 * @file	gra_tool.h
 * @brief	グラフィックツール
 * @author	goto
 * @date	2005.11.16
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#ifndef	_GRA_TOOL_H_
#define _GRA_TOOL_H_

#include "battle/graphic/batt_obj_def.h"						///< アーカイブデータ
#include "battle/graphic/batt_bg_def.h"						///< アーカイブデータ


//==============================================================================
//	構造体定義
//==============================================================================
///ポケモンキャラ展開パラメータ
typedef struct
{
	u8	*exchr_buffer;		///<ポケモンキャラデータ展開バッファ
	int	arcID;				///<アーカイブ内のポケモングラフィックアーカイブナンバー
	int	pal_index;			///<アーカイブ内のポケモンパレットインデックスナンバー
	int	height;				///<ポケモン高さ情報
}EXCHR_PARAM;


// -----------------------------------------
//
//	■定数定義
//
// -----------------------------------------
// 2D→1D変換に使用
#define CHAR_DOT_X		(8/2)								///< 1キャラのバイトサイズ
#define CHAR_DOT_Y		(8)									///< 1キャラのバイトサイズ
#define CHAR_BYTE		(CHAR_DOT_X * CHAR_DOT_Y)			///< 1キャラバイト数

// -----------------------------------------
//
//	■ポケモン用定数定義
//		(戦闘特化なので移動する場合もあります。)
//
// -----------------------------------------
#define POKE_TEX_X		(0)									///< ポケモン変換用テクスチャ切り取り開始位置X
#define POKE_TEX_Y		(0)									///< ポケモン変換用テクスチャ切り取り開始位置Y
#define POKE_TEX_W		(10)								///< ポケモン変換用テクスチャ切り取り終了位置X
#define POKE_TEX_H		(10)								///< ポケモン変換用テクスチャ切り取り終了位置Y
#define POKE_TEX_SIZE	(POKE_TEX_W * POKE_TEX_H * CHAR_BYTE)

#define PO_CHAR_ID		(POKE_OAM_NCGR)		///< ダミーデータのアーカイブID
#define PO_PLTT_ID		(POKE_OAM_NCLR)
#define PO_CELL_ID		(POKE_OAM_NCER)
#define PO_CELLANM_ID	(POKE_OAM_NANR)

#define PB_N_SCREEN_ID		(POKE_SCREEN_N_NSCR);		///< ダミースクリーンのアーカイブID
#define PB_F_SCREEN_ID		(POKE_SCREEN_F_NSCR);
#define PB_N_512_SCREEN_ID	(POKE_SCREEN_N_512_NSCR);	///< ダミースクリーンのアーカイブID512x512
#define PB_F_512_SCREEN_ID	(POKE_SCREEN_F_512_NSCR);

// -----------------------------------------
//
//	■変換用の矩形構造体
//
// -----------------------------------------
typedef struct {
	
	int x;
	int y;
	int w;
	int h;
	
} CHANGES_INTO_DATA_RECT;

extern void	 ChangesInto_1D_from_2D(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff);
extern void	 ChangesInto_1D_from_2D_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc, void* buff);

extern void* ChangesInto_1D_from_2D_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h);
extern void* ChangesInto_1D_from_2D_Alloc_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc);

extern void  ChangesInto_OAM_from_1D(int sx, int sy, int x, int y, int w, int h, int* bofs, const void* src, void* dst);
extern void  ChangesInto_OAM_from_1D_RC(int sx, int sy, const CHANGES_INTO_DATA_RECT* rc, int* bofs, const void* src, void* dst);

extern void  ChangesInto_OAM_from_PokeTex(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff);
extern void  ChangesInto_OAM_from_PokeTex_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc, void* buff);

extern void* ChangesInto_OAM_from_PokeTex_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h);
extern void* ChangesInto_OAM_from_PokeTex_Alloc_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc);

extern void  ChangesInto_BattlePokeData(int arc_id, int index_no, int heap_id, void* buff);
extern void* ChangesInto_BattlePokeData_Alloc(int arc_id, int index_no, int heap_id);

extern void* ChangesInto_BattlePokePalData_Alloc(int arc_id, int index_no, int heap_id);


/// ポケモンのぶち対応Ver 使ってるものだけ増やしました。
extern void  Ex_ChangesInto_OAM_from_PokeTex(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff, u32 rnd, BOOL animeFlag, int dir, int monsno);
extern void  Ex_ChangesInto_OAM_from_PokeTex_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc, void* buff, u32 rnd, BOOL animeFlag, int dir, int monsno);

extern void  Ex_ChangesInto_BattlePokeData(int arc_id, int index_no, int heap_id, void* buff, u32 rnd, BOOL animeFlag, int dir, int monsno);
extern void* Ex_ChangesInto_BattlePokeData_Alloc(int arc_id, int index_no, int heap_id, u32 rnd, BOOL animeFlag, int dir, int monsno);

#endif

