//=============================================================================
/**
 * @file	worldmap.c
 * @bfief	ワールドマップ構築処理
 * @author	saitou, mori GAME FREAK inc.
 *
 *
 */
//=============================================================================
// エリア毎にテクスチャファイルを切り替えるので、エリア遷移した際に
// テクスチャファイルをエリア番号から生成して読み込む処理の追加を後々行う


#include "common.h"
#include "height_def.h"
#include "calctool.h"

#include "worldmap.h"

#include "fieldsys.h"
#include "debug_saito.h"

#include "mapdefine.h"
#include "zonedata.h"
#include "mapdefine.h"
#include "system/arc_tool.h"

#include "include/field/field_matrix.h"


//===========================================================================
// 定数
//===========================================================================
///#define	OLD_MAP_MATRIX
#define MAP_MATRIX_WIDTH_MAX	(30)
#define MAP_MATRIX_HEIGHT_MAX	(30)
#define MAP_MATRIX_MAX			(MAP_MATRIX_WIDTH_MAX*MAP_MATRIX_HEIGHT_MAX)
#define MAP_MATRIX_PREFIX_MAX	(16)

//===========================================================================
// 構造体定義
//===========================================================================
//------------------------------------------------------------------
///	マップマトリックス情報保持用ワーク
//------------------------------------------------------------------
typedef struct MATRIX_TABLE_tag
{
	u8	size_h;							///<マップマトリックスの縦幅
	u8	size_w;							///<マップマトリックスの横幅
	u16	ZoneMat[MAP_MATRIX_MAX];		///<ゾーンIDテーブル
	u8	HeightBase[MAP_MATRIX_MAX];		///<高さ指定テーブル
	u16	ArcIndex[MAP_MATRIX_MAX];		///<アーカイブインデックステーブル
	u8	Prefix[MAP_MATRIX_PREFIX_MAX];	///<ファイル名のプレフィックス
}MATRIX_TABLE;

//------------------------------------------------------------------
///	ワールドマップ構造体
//------------------------------------------------------------------
struct _WORLD_MAP{
	u8  MatrixW,MatrixH;						///< エリアの縦横幅
	u8 matrix_id;
	MATRIX_TABLE MapMatrix;
};




//============================================================================================
//============================================================================================
//------------------------------------------------------------------
//アーカイバからマトリックスを取得
//------------------------------------------------------------------
static void SetupMapMatrix(MATRIX_TABLE * Mmtx, const u16 matrix_id, int zone_id)
{
	u8 zone_flg,height_flg;
	u8 prefix_size;
	void *mem;
	u8 *p;

	{
		int i;
		//構造体初期化
		Mmtx->size_w = 0;
		Mmtx->size_h = 0;
	
		for(i=0;i<MAP_MATRIX_MAX;i++){
			Mmtx->ZoneMat[i] = 0;
			Mmtx->HeightBase[i] = 0;
			Mmtx->ArcIndex[i] = 0;
		}
		for(i=0;i<MAP_MATRIX_PREFIX_MAX;i++){
			Mmtx->Prefix[i] = 0;
		}
	}
	
	mem = ArchiveDataLoadMallocLo( ARC_MAP_MATRIX, matrix_id, HEAPID_WORLD );
	p = &((u8*)(mem))[0];
	Mmtx->size_w = *p;	//横サイズ
	p++;
	Mmtx->size_h = *p;	//縦サイズ
	p++;
	zone_flg = *p;
	p++;
	height_flg = *p;
	p++;
	prefix_size = *p;					//プレフィクス文字列サイズ
	p++;

	GF_ASSERT(prefix_size <= MAP_MATRIX_PREFIX_MAX);
	MI_CpuCopy8(p,Mmtx->Prefix,prefix_size);
	p+=(prefix_size);

#ifdef	DEBUG_ONLY_FOR_saitou
	OS_Printf("data=%d,%d,%d,%d\n",Mmtx->size_w,Mmtx->size_h,zone_flg,height_flg);
	OS_Printf("prefix = %s,%d\n",Mmtx->Prefix,prefix_size);
#endif
	
	if (zone_flg){
		MI_CpuCopy8(p, Mmtx->ZoneMat, Mmtx->size_w * Mmtx->size_h * 2);
		p+=(Mmtx->size_w * Mmtx->size_h * 2);
	}else{
		//ゾーン指定のマトリックス表がない場合は、ゾーンIDを敷き詰めて生成する
		MI_CpuFill16(Mmtx->ZoneMat, zone_id, Mmtx->size_w * Mmtx->size_h * sizeof(u16));
	}
	if (height_flg){
		MI_CpuCopy8(p, Mmtx->HeightBase, Mmtx->size_w * Mmtx->size_h);
		p+=(Mmtx->size_w * Mmtx->size_h);
	}

	MI_CpuCopy8(p, Mmtx->ArcIndex, Mmtx->size_w * Mmtx->size_h*2);
	
	sys_FreeMemoryEz(mem);
}

//------------------------------------------------------------------
//------------------------------------------------------------------
WORLD_MAP_PTR WorldMapInit(void)
{
	WORLD_MAP_PTR world;

	// ワールドマップ構造体ワークを確保
	world = sys_AllocMemory(HEAPID_WORLD,sizeof(WORLD_MAP));

	world->MatrixW = 0;
	world->MatrixH = 0;
	
	world->matrix_id = 0;
	
	return world;
}

//==============================================================================
/**
 * ゾーンＩＤを元に、マップマトリックスを作成
 *
 * @param   zone_id	ゾーンＩＤ
 * @param   world	WORLD_MAP構造体のポインタ
 *
 * @retval  none		
 */
//==============================================================================
void SetUpWorldMatrix(const int zone_id, WORLD_MAP_PTR world)
{
	u16 matrix_id;

	matrix_id = ZoneData_GetMatrixID(zone_id);
	//アーカイバからマトリックスを取得
	SetupMapMatrix(&world->MapMatrix,matrix_id,zone_id);
	world->matrix_id = matrix_id;
	world->MatrixH = world->MapMatrix.size_h;
	world->MatrixW = world->MapMatrix.size_w;
}


//==============================================================================
/**
 * ワールドマップ構造体の解放
 *
 * @param   world		WORLD_MAPのポインタ
 *
 * @retval  none		
 */
//==============================================================================
void WorldMapRelease(const WORLD_MAP_PTR world)
{
	sys_FreeMemoryEz(world);						// ワールドマップ解放
	
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//
//
// ここから下はWORLD_MAPのメンバを参照するためのインターフェース関数です。
//
//
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
u16 GetArcIndexFromBlockIndex(int index, const WORLD_MAP_PTR world)
{
	GF_ASSERT((index<(world->MatrixW*world->MatrixH)) && "マップの範囲を超えている");
	return world->MapMatrix.ArcIndex[index];
}

//==============================================================================
/**
 * 現在読み込んでいるワールドマップの横幅を取得する
 *
 * @param   world		WORLD_MAPのポインタ
 *
 * @retval  int			横幅
 */
//==============================================================================
int  GetWorldMapMatrixW(const WORLD_MAP_PTR world)
{
	GF_ASSERT((world!=NULL) && "worldmapが未確保");

	return world->MatrixW;
}
//==============================================================================
/**
 * 現在読み込んでいるワールドマップの縦幅を取得する
 *
 * @param   world		WORLD_MAPのポインタ
 *
 * @retval  int			縦幅
 */
//==============================================================================
int  GetWorldMapMatrixH(const WORLD_MAP_PTR world)
{
	GF_ASSERT((world!=NULL) && "worldmapが未確保");

	return world->MatrixH;

}


//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	ブロック座標をもとにマップマトリックスからのゾーンID取得
 * @param	world	WORLD_MAPのポインタ
 * @param	gx		X位置（地形ブロック単位）
 * @param	gz		Z位置（地形ブロック単位）
 */
//------------------------------------------------------------------
u16 World_GetZoneIDFromMatrixXZ(const WORLD_MAP * world, int gx, int gz)
{
	int gw = world->MatrixW;
	int gh = world->MatrixH;
	GF_ASSERT(0 <= gx && gx < gw);
	GF_ASSERT(0 <= gz && gz < gh);
	return world->MapMatrix.ZoneMat[gx + gz * gw];
}

//------------------------------------------------------------------
/**
 * @brief	ブロックインデックスを元にマップマトリックスからのゾーンID取得
 * @param	world	WORLD_MAPのポインタ
 * @param	gx		X位置（地形ブロック単位）
 * @param	gz		Z位置（地形ブロック単位）
 */
//------------------------------------------------------------------
u16 World_GetZoneIDFromBlockIdx(const WORLD_MAP * world, const int inBlockIdx)
{
	int idx_max = world->MatrixW*world->MatrixH;
#ifdef	DEBUG_ONLY_FOR_saitou	
	OS_Printf("local_print idx=%d,%d",idx_max,inBlockIdx);
#endif	
	GF_ASSERT(0 <= inBlockIdx && inBlockIdx < idx_max);
	return world->MapMatrix.ZoneMat[inBlockIdx];
}

//==============================================================================
/**
 * マトリックスID取得
 *
 * @param   world	WORLD_MAPのポインタ
 *
 * @retval  none		
 */
//==============================================================================

u8 GetWorldMatrixID(const WORLD_MAP_PTR world)
{
	return world->matrix_id;
}

//==============================================================================
/**
 * マトリクスIDからゾーンIDを取得
 *
 * @param   world		WORLD_MAPのポインタ
 * @param   matrix_id	マトリクスID
 * @param   gx			X座標(ブロック)
 * @param   gz			Z座標(ブロック)
 * @param   gw			幅
 *
 * @retval  int			ゾーンID		
 */
//==============================================================================
int GetZoneIDFromMatrixID(	const WORLD_MAP_PTR world,
							const int matrix_id,
							const int gx,
							const int gz,
							const int gw)
{
	GF_ASSERT(gx < gw);
	GF_ASSERT( (gx + gz * gw) < MAP_MATRIX_MAX );
	return world->MapMatrix.ZoneMat[gx + gz * gw];
}

//==============================================================================
/**
 * マトリクスIDから高さベースを取得
 *
 * @param   world		WORLD_MAPのポインタ
 * @param   matrix_id	マトリクスID
 * @param   gx			X座標
 * @param   gz			Z座標
 * @param   gw			幅
 *
 * @retval  int			高さベース		
 */
//==============================================================================
int GetHeightBaseFromMatrixID(	const WORLD_MAP_PTR world,
								const int matrix_id,
								const int gx,
								const int gz,
								const int gw)
{
	GF_ASSERT(gx < gw);
	GF_ASSERT( (gx + gz * gw) < MAP_MATRIX_MAX );
	return world->MapMatrix.HeightBase[gx + gz * gw];
}

//==============================================================================
//==============================================================================
//
//		アプリケーション用アクセス関数
//
//==============================================================================
//==============================================================================
typedef struct FIELD_MAT_ZONE_ID_tag
{
	u16 ZoneMat[MAP_MATRIX_MAX];
}FIELD_MAT_ZONE_ID;

//==============================================================================
/**
 * フィールドマトリクス構造体作成
 *
 * @param   inHeapID	ヒープID
 *
 * @retval  FMZ_PTR		構造体へのポインタ		
 */
//==============================================================================
FMZ_PTR InitFMZ(const u32 inHeapID)
{
	int prefix_size;
	void *mem;
	u8 *p;
	FMZ_PTR fmz_p;
	fmz_p = sys_AllocMemory(inHeapID, sizeof(FIELD_MAT_ZONE_ID));

	mem = ArchiveDataLoadMallocLo( ARC_MAP_MATRIX, MATRIX_ID_SINOU, inHeapID );
	p = &((u8*)(mem))[0];
	//横サイズ
	p++;
	//縦サイズ
	p++;
	//ゾーンフラグ
	p++;
	//ハイトフラグ
	p++;
	prefix_size = *p;					//プレフィクス文字列サイズ
	p++;
	p+=(prefix_size);

	MI_CpuCopy8(p,fmz_p->ZoneMat,30*30*2);
	
	sys_FreeMemoryEz(mem);
	
	return fmz_p;
}

//==============================================================================
/**
 * フィールドマトリクス構造体解放
 *
 * @param   fmzp		構造体へのポインタ
 *
 * @retval  none		
 */
//==============================================================================
void FreeFMZ(FMZ_PTR fmzp)
{
	GF_ASSERT(fmzp!=NULL);
	sys_FreeMemoryEz(fmzp);
}

//==============================================================================
/**
 * ブロック座標から、ソーンIDを取得
 *
 * @param   fmzp		構造体へのポインタ
 * @param   inBlockX	ブロックX座標
 * @param   inBlockZ	ブロックZ座標
 *
 * @retval  none		
 */
//==============================================================================
int GetFieldMatrixZoneID(const FMZ_CONST_PTR fmdp, const u32 inBlockX, const u32 inBlockZ)
{
	return fmdp->ZoneMat[inBlockX+inBlockZ*MAP_MATRIX_WIDTH_MAX];
}

#ifdef PM_DEBUG
//==============================================================================
/**
 * @brief	指定したゾーンの左上ブロック座標を取得する
 *
 * @param	zoneID		ゾーンID
 * @param   px			取得したブロックX座標を格納するポインタ
 * @param   pz			取得したブロックZ座標を格納するポインタ
 *
 * @retval  none		
 */
//==============================================================================
int GetBlockPosFromZoneID(int zoneID,u16* px,u16* pz)
{
	MATRIX_TABLE	mData;
	u16	x,z;
	int	matrixID;
		
	matrixID = ZoneData_GetMatrixID(zoneID);
	SetupMapMatrix(&mData,matrixID,zoneID);

	for(z = 0;z < mData.size_h;z++){
		for(x = 0;x < mData.size_w;x++){
			if(mData.ZoneMat[z*mData.size_w+x] == zoneID){
				*px = x;
				*pz = z;
				return 1;
			}
		}
	}
	//見つからない
	*px = 0;
	*pz = 0;
	return 0;
}
#endif

//==============================================================================
/**
 * @brief	指定したマトリックスＩＤのブロック座標に対応するゾーンＩＤを取得
 * ※使う場所は限定されます。
 *
 * @param   matrixID	マトリクスID
 * @param   x			ブロックX座標
 * @param   z			ブロックZ座標
 *
 * @retval  int			ゾーンＩＤ		
 */
//==============================================================================
int GetZoneIDFromMatID(const int inMatID, const u16 inX, const u16 inZ)
{
	MATRIX_TABLE	mData;
	u16	x,z;
		
	SetupMapMatrix(&mData,inMatID,0);

	GF_ASSERT(inX<mData.size_w);
	GF_ASSERT(inZ<mData.size_h);

	return mData.ZoneMat[inZ*mData.size_w+inX];

}

//==============================================================================
/**
 * 指定のブロックに対応している高さデータアーカイブインデックスを取得
 *
 * @param   Block		ブロック
 * @param   mapresource		WORLD_MAPのポインタ
 *
 * @retval  char *		ブロックファイル名のポインタ
 */
//==============================================================================
const u16 GetWorldMapArcIdx(const int Block, const WORLD_MAP_PTR world)
{
	u16 index;
	int ggx = Block % world->MatrixW;							//現在はゾーン内情報が無いので仮構築
	int ggz = Block / world->MatrixW;
	GF_ASSERT((world!=NULL) && "worldが未確保");

	index = GetArcIndexFromBlockIndex(Block,world);
	return index;
}



//============================================================================================
//
//
//			マップ書き換え特殊処理
//
//
//			※汎用性はまったくない。ダイヤモンド＆パール専用だと思われる
//
//
//============================================================================================
#include "../fielddata/land_data/land_data.naix"

//------------------------------------------------------------------
/**
 * @brief	クリア後の湖を出現させる
 * @param	world	WORLD_MAPのポインタ
 */
//------------------------------------------------------------------
void World_Overwrite_L04(WORLD_MAP_PTR world)
{
	u16 * arc_tbl = world->MapMatrix.ArcIndex;
	u8 * height_tbl = world->MapMatrix.HeightBase;
	int map_h = world->MatrixH;
	int map_w = world->MatrixW;
	int i, j;
	if (world->matrix_id != MATRIX_ID_SINOU) {
		return;
	}
	arc_tbl[23 + map_w * 21] = NARC_land_data_ro_tree2_bin;
	arc_tbl[24 + map_w * 21] = NARC_land_data_ro_tree2_bin;
	arc_tbl[23 + map_w * 22] = NARC_land_data_ro_tree2_bin;
	arc_tbl[24 + map_w * 22] = NARC_land_data_ro_tree2_bin;
	height_tbl[23 + map_w * 21] = 2;
	height_tbl[24 + map_w * 21] = 2;
	height_tbl[23 + map_w * 22] = 2;
	height_tbl[24 + map_w * 22] = 2;
}

//------------------------------------------------------------------
/**
 * @brief	花の楽園への道を出現させる
 * @param	world	WORLD_MAPのポインタ
 */
//------------------------------------------------------------------
void World_Overwrite_R224(WORLD_MAP_PTR world)
{
	int i, j;
	u16 * arc_tbl = world->MapMatrix.ArcIndex;
	int map_h = world->MatrixH;
	int map_w = world->MatrixW;
	if (world->matrix_id != MATRIX_ID_SINOU) {
		return;
	}
	arc_tbl[map_w * 15 + 28] = NARC_land_data_sp28_15_bin;
	arc_tbl[map_w * 16 + 27] = NARC_land_data_sp27_16_bin;
	arc_tbl[map_w * 16 + 28] = NARC_land_data_sp28_16_bin;
	arc_tbl[map_w * 17 + 27] = NARC_land_data_sp27_17_bin;
}




