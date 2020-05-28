//============================================================================================
/**
 * @file	poketch_map.c
 * @bfief	ポケッチ（フィールドマップ表示アプリ共通ルーチン）
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "poketch_prv.h"
#include "poketch_map.h"
#include "..\mapdefine.h"

//--------------------------------------------------------------
// マップグリッドから
// ポケッチ画面上の座標（ドット単位）へ変換するためのテーブル
//--------------------------------------------------------------
static const u16 GridToDotX[] = {
 26, 32, 38, 44, 50, 56, 62, 68, 74, 80,
 86, 92, 98,104,110,116,122,128,134,140,
146,152,158,164,170,176,182,188,194,200,
};
static const u16 GridToDotY[] = {
 // 0～4まではあり得ないはず
   0,  0,  0,  0,  0, 24, 30, 36, 42, 48,
  54, 60, 66, 72, 78, 84, 90, 96,102,108,
 114,120,126,132,138,144,150,156,162,168,
 174,180,186,
};


void PoketchMap_GridToDot( u32 glid_x, u32 glid_y, u32* dot_x, u32* dot_y )
{
	GF_ASSERT(glid_x < NELEMS(GridToDotX));
	GF_ASSERT(glid_y < NELEMS(GridToDotY));

	if( glid_x >= NELEMS(GridToDotX) ){ glid_x = 0; }
	if( glid_y >= NELEMS(GridToDotY) ){ glid_y = 0; }

	*dot_x = GridToDotX[glid_x];
	*dot_y = GridToDotY[glid_y];
}


//------------------------------------------------------------------
/**
 * 隠しマップ・配布マップの表示座標を取得
 *
 * @param   hidemapID		
 * @param   x		
 * @param   y		
 *
 */
//------------------------------------------------------------------
void PoketchMap_GetHideMapPos( int hidemapID, u32* x, u32 *y )
{
	static const struct {
		u32  x;
		u32  y;
	}hidemap_pos[] = {
		{  32,   42, },
		{  50,   42, },
		{ 168,  122, },
		{ 194,   58, },
	};

	GF_ASSERT(hidemapID < NELEMS(hidemap_pos));

	*x = hidemap_pos[hidemapID].x;
	*y = hidemap_pos[hidemapID].y;

}


//------------------------------------------------------------------
/**
 * 移動ポケモンの表示座標を取得
 *
 * @param   zone_id		移動ポケモンのゾーンID
 * @param   x			
 * @param   y			
 *
 * @retval  BOOL		TRUEが返ったら表示位置を取得できている
 */
//------------------------------------------------------------------
BOOL PoketchMap_GetMovePokePos( int zone_id, u32* x, u32* y )
{
	static const struct {
		u16  zone_id;
		u8   x;
		u8   y;
	}zone_pos_tbl[] = {

		{ ZONE_ID_R201,  47, 150 },
		{ ZONE_ID_R202,  56, 144 },
		{ ZONE_ID_R203,  65, 132 },//○
		{ ZONE_ID_R204A,  50, 126 },
		{ ZONE_ID_R204B,  50, 120 },
		{ ZONE_ID_R205A,  62, 108 },//○
		//{ ZONE_ID_R205AR0101,  0, 0 },
		{ ZONE_ID_R205B,  74, 90 },
		{ ZONE_ID_R206,  80, 111 },
		//{ ZONE_ID_R206R0101,  0, 0 },
		//{ ZONE_ID_R206R0201,  0, 0 },
		{ ZONE_ID_R207,  83, 126 },//○
		{ ZONE_ID_R208,  101, 126 },
		//{ ZONE_ID_R208R0101,  0, 0 },
		{ ZONE_ID_R209,  125, 126 },
		//{ ZONE_ID_R209R0101,  0, 0 },
		//{ ZONE_ID_R209R0102,  0, 0 },
		//{ ZONE_ID_R209R0103,  0, 0 },
		//{ ZONE_ID_R209R0104,  0, 0 },
		//{ ZONE_ID_R209R0105,  0, 0 },
		{ ZONE_ID_R210A,  128, 102 },
		{ ZONE_ID_R210B,  122, 90 },
		//{ ZONE_ID_R210BR0101,  0, 0 },
		{ ZONE_ID_R211A,  92, 90 },
		{ ZONE_ID_R211B,  104, 90 },
		{ ZONE_ID_R212A,  110, 138 },
		//{ ZONE_ID_R212AR0101,  0, 0 },
		//{ ZONE_ID_R212AR0102,  0, 0 },
		//{ ZONE_ID_R212AR0103,  0, 0 },
		{ ZONE_ID_R212B,  119, 150 },
		//{ ZONE_ID_R212BR0101,  0, 0 },
		{ ZONE_ID_R213,  152, 147 },
		//{ ZONE_ID_R213R0101,  0, 0 },
		//{ ZONE_ID_R213R0201,  0, 0 },
		//{ ZONE_ID_R213R0301,  0, 0 },
		//{ ZONE_ID_R213R0401,  0, 0 },
		//{ ZONE_ID_R213R0501,  0, 0 },
		//{ ZONE_ID_R213R0601,  0, 0 },
		{ ZONE_ID_R214,  152, 120 },
		//{ ZONE_ID_R214R0101,  0, 0 },
		{ ZONE_ID_R215,  140, 102 },
		{ ZONE_ID_R216,  86, 66 },
		//{ ZONE_ID_R216R0101,  0, 0 },
		{ ZONE_ID_R217,  80, 51 },
		//{ ZONE_ID_R217R0101,  0, 0 },
		//{ ZONE_ID_R217R0201,  0, 0 },
		{ ZONE_ID_R218,  41, 132 },
		//{ ZONE_ID_R218R0101,  0, 0 },
		//{ ZONE_ID_R218R0201,  0, 0 },
		{ ZONE_ID_R219,  56, 156 },
		{ ZONE_ID_W220,  59, 162 },
		{ ZONE_ID_R221,  74, 162 },
		//{ ZONE_ID_R221R0101,  0, 0 },
		//{ ZONE_ID_R221R0201,  0, 0 },
		{ ZONE_ID_R222,  170, 138 },
		{ ZONE_ID_D02,  68, 114 },//はつでんしょ○
		{ ZONE_ID_D04,  56, 102 },
		//{ ZONE_ID_R222R0101,  0, 0 },
		//{ ZONE_ID_R222R0201,  0, 0 },
		//{ ZONE_ID_R222R0301,  0, 0 },
		//{ ZONE_ID_R224,  0, 0 },
		//{ ZONE_ID_R225,  0, 0 },
		//{ ZONE_ID_R226A,  0, 0 },
		//{ ZONE_ID_R226B,  0, 0 },
		//{ ZONE_ID_R227,  0, 0 },
		//{ ZONE_ID_R227A,  0, 0 },
		//{ ZONE_ID_R227B,  0, 0 },
		//{ ZONE_ID_R228,  0, 0 },
		//{ ZONE_ID_R229,  0, 0 },
		//{ ZONE_ID_R230,  0, 0 },
		//{ ZONE_ID_R232,  0, 0 },
	};

	int i;

	for(i=0; i<NELEMS(zone_pos_tbl); i++)
	{
		if( zone_pos_tbl[i].zone_id == zone_id )
		{
			*x = zone_pos_tbl[i].x;
			*y = zone_pos_tbl[i].y;
			return TRUE;
		}
	}

	return FALSE;

}


