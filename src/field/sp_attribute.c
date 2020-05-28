//============================================================================================
/**
 * @file	sp_attribute.c
 * @brief	特殊マトリックス関連
 * @author	Nozomu Saito
 * @date	2006.02.17
 */
//============================================================================================
#include "common.h"
#include "fieldsys.h"
#include "worldmap.h"
#include "sp_attribute_def.h"

#include "system/arc_tool.h"

#define SP_MAP_SIZE			(15)

typedef struct SP_MATRIX_DATA_tag{
	u8 Matrix[SP_MAP_SIZE*SP_MAP_SIZE];
	u16 GroundAttr[GROUND_ATTR_SIZE];
}SP_MATRIX_DATA;

static void MakeSpMatrix(WORLD_MAP_PTR inWorld, SMD_PTR outUgMatrixData, const u8 inNum);
static const u8 AddSpArcList(const u16 inArcIndex, u16 *outList, u8 *ioListPos);

//--------------------------------------------------------------------------------------------
/**
 * 特殊アトリビュートセットアップ
 *
 * @param	fsys			フィールドシステムポインタ
 * @param	inNum			データ数
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SPATTR_SetUpGroundAttr(FIELDSYS_WORK *fsys, const u8 inNum)
{
	int i;
	void *mem;	
	//メモリアロケーション
	if (fsys->SpMatData == NULL){
		fsys->SpMatData = sys_AllocMemory( HEAPID_WORLD, sizeof(SP_MATRIX_DATA) );
		//特殊マトリクス作成
		MakeSpMatrix(fsys->World, fsys->SpMatData, inNum);
		
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 特殊アトリビュート解放
 *
 * @param	fsys			フィールドシステムポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SPATTR_FreeGroundAttr(FIELDSYS_WORK *fsys)
{
	if (fsys->SpMatData != NULL){
		sys_FreeMemoryEz(  fsys->SpMatData );
		fsys->SpMatData = NULL;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 特殊アトリビュートブロックを取得
 *
 * @param	inBlockindex	ブロックインデックス 
 * @param	inSpMatrixData	特殊マトリクスデータ
 *
 * @return	block_attr	ブロックアトリビュート先頭ポインタ
 */
//--------------------------------------------------------------------------------------------
u16 const * SPATTR_GetSpBlockAttribute(const u32 inBlockindex, SMD_CONST_PTR inSpMatrixData)
{
	u16 const *block_attr;
	u8 list_idx;
	list_idx = inSpMatrixData->Matrix[inBlockindex];
	block_attr = (u16 const *)&(inSpMatrixData->GroundAttr[BLOCK_ATTR_SIZE*list_idx]);
	return block_attr;
}

//--------------------------------------------------------------------------------------------
/**
 * 特殊マトリクスを作成
 *
 * @param	inWorld			ワールドポインタ
 * @param	outSpMatrixData	特殊マトリクスデータ
 * @param	inNum			データ数
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void MakeSpMatrix(WORLD_MAP_PTR inWorld, SMD_PTR outSpMatrixData, const u8 inNum)
{
	u8 list_pos;
	u16 arc_idx;
	u8 list_idx;
	u16 idx;
	int i,j;
	int h,w;
	u16 list[SP_ATTR_DATA_NUM_MAX];
	void *mem;
	ARCHANDLE *arc_handle;

	list_pos = 0;

	//現在マップマトリクスを取得
	w = GetWorldMapMatrixW(inWorld);
	h = GetWorldMapMatrixH(inWorld);

	//アトリビュート取得用にマトリクスを作成
	for(j=0;j<h;j++){
		for(i=0;i<w;i++){
			idx = j*w+i;
			arc_idx = GetArcIndexFromBlockIndex(idx,inWorld);
#ifdef DEBUG_ONLY_FOR_saitou			
			OS_Printf("local_print %d:arc_idx:%d\n",idx,arc_idx);
#endif			
			//特殊マトリックスのアーカイブインデックスをリストに追加
			list_idx = AddSpArcList(arc_idx, list, &list_pos);
			outSpMatrixData->Matrix[idx] = list_idx;
		}
	}
	//アトリビュートをまとめてロードする
	//アーカイブハンドルの取得
	arc_handle = ArchiveDataHandleOpen( ARC_FIELD_MAP_DATA, HEAPID_WORLD );

	for(i=0;i<inNum;i++){
		arc_idx = list[i];
		mem = &(outSpMatrixData->GroundAttr[BLOCK_ATTR_SIZE*i]);
		//アトリビュートはアーカイブデータの先頭から固定バイトサイズなので、オフセット、サイズ取得は省く
		ArchiveDataLoadOfsByHandle( arc_handle, arc_idx, 0x10, 0x800,  mem);
	}
	//アーカイブハンドルの解放
	ArchiveDataHandleClose( arc_handle );
}

//--------------------------------------------------------------------------------------------
/**
 * リストに登録
 *
 * @param	inArcIndex	アーカイブインデックス
 * @param	outList		リスト
 * @param	ioListPos	リスト位置
 *
 * @return	u8			登録してある（した）リストインデックス
 */
//--------------------------------------------------------------------------------------------
static const u8 AddSpArcList(const u16 inArcIndex, u16 *outList, u8 *ioListPos)
{
	u8 i;
	//指定したアーカイブインデックスがリストに登録されていなければ追加
	for(i=0;i<(*ioListPos);i++){
		if (outList[i] == inArcIndex){
			return i;	//すでに登録済み
		}
	}
	//新規登録
	GF_ASSERT( i<SP_ATTR_DATA_NUM_MAX && "データ数がオーバーしてます" );
	outList[i] = inArcIndex;
	(*ioListPos)++;
	return i;
	
}
