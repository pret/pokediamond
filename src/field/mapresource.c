//=============================================================================
/**
 * @file	mapresource.c
 * @bfief	フィールドマップリソース構築処理
 * @author	mori         GAME FREAK inc.
 *
 *
 */
//=============================================================================

#include "common.h"
#include "height_def.h"
#include "calctool.h"
#include "str_tool.h"

#include "fieldsys.h"
#include "worldmap.h"
#include "mapresource.h"
#include "debug_saito.h"

#include "mapdefine.h"
#include "zonedata.h"
#include "mat_shp.h"
//#include "field_camera.h"
#include "system/arc_tool.h"
#include "situation_local.h"

#define BUILD_MODEL_MAX	(550)

//エッジマーキングテーブル
static const GXRgb gEdgeColorField[8] = {
    GX_RGB(0, 0, 0),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4)
};
//エッジマーキングテーブル
static const GXRgb gEdgeColorOther[8] = {
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4)
};
enum {
	CAMERA_TYPE1,
	CAMERA_TYPE2,
	CAMERA_TYPE3,
}CAMERA_TYPE;

typedef struct MAP_RES_SETUP_WORK_tag
{
	int AreaID;
	FLD_3D_ANM_MNG_PTR FldAnmMng;
	u16  Num;
	int Seq;
}MAP_RES_SETUP_WORK;

typedef struct RESOURCE_PARAM_tag
{
	u16 model_set;			//モデルセットインデックス
	u16 tex_set;		//地形テクスチャセットインデックス
	u16 move_model_set;		//動作モデルセットインデックス
	u16 light;				//ライトフラグ
}RESOURCE_PARAM;

//-マップリソース構造体(worldmapから分離)------------------------------------------------------
typedef struct _MAP_RESOURCE{
	int 				modelTableNum;	///< modelTableが持つモデリングデータの数
	NNSG3dResFileHeader	*model[BUILD_MODEL_MAX];	///< モデリングデータのポインタのテーブル
	void*				pTexFile;		///< テクスチャーファイル実体へのポインタ
	void*				pBmTexFile;		///< 配置モデルテクスチャーファイル実体へのポインタ
	NNSG3dResTex		*Tex;			///< テクスチャリソース
	NNSG3dResTex		*BmTex;			///< 配置モデルテクスチャリソース

	MSD_PTR				MatShpData;		///< 3ＤＯＢＪのマテリアル、シェイプ対応データ
	
	RESOURCE_PARAM ResourceParam;

	MAP_RES_SETUP_WORK *SetupWork;

	u16 *ModelFile;

}MAP_RESOURCE;


#ifdef PM_DEBUG
///#define DEBUG_TEX_INFO		//テクスチャ情報表示
static void DebugPrintTexInfo(NNSG3dResTex *pTex);
#endif

//==============================================================================
/**
 * テクスチャ実体を破棄
 *
 * @param   memBlock	メモリブロック
 * @param	texture		テクスチャリソース
 *
 * @retval  none
 */
//==============================================================================
static void CollapseResourceMemory(void* memBlock, NNSG3dResTex* texture)
{
    u8* texImgStartAddr;
    u32 newSize;

    // テクスチャ／パレットは、4x4COMP以外のテクスチャ・4x4COMPのテクスチャ・パレット
    // の順番で格納されています。よって4x4COMP以外のテクスチャの開始アドレス以降は
    // 不要になります。なお、4x4COMPフォーマット以外のテクスチャイメージが存在しない
    // 場合でもtexture->texInfo.ofsTexには適切な値が入っています。
    SDK_ASSERT(texture->texInfo.ofsTex != 0);
    texImgStartAddr = (u8*)texture + texture->texInfo.ofsTex;

    // ヒープの先頭からテクスチャイメージまでのサイズ
    newSize = (u32)(texImgStartAddr - (u8*)memBlock);

    // メモリブロックを縮小します。
    // その結果、テクスチャイメージ分のメモリはヒープに返却されます。
    ///(void)NNS_FndResizeForMBlockExpHeap(G3DDemo_AppHeap, memBlock, newSize);
	sys_CutMemoryBlockSize( memBlock, newSize );
}

//==============================================================================
/**
 * MAP_RESOURCEのアロケーション
 *
 * @param   area_id		エリアID
 * @param	field_3d_anime	3Ｄアニメ
 *
 * @retval  MAP_RESOURCE_PTR	確保したMAPRESOURCEのポインタ
 */
//==============================================================================
MAP_RESOURCE_PTR AllocMapResource(const int area_id, FLD_3D_ANM_MNG_PTR field_3d_anime)
{
	MAP_RESOURCE_PTR mapresource;
	mapresource	= sys_AllocMemory(HEAPID_FIELD,sizeof(MAP_RESOURCE));
#ifdef DEBUG_ONLY_FOR_saitou	
	OS_Printf("local_print AREA_ID:%d\n",area_id);
#endif
	//ワークの確保
	mapresource->SetupWork = sys_AllocMemoryLo(HEAPID_FIELD,sizeof(MAP_RES_SETUP_WORK));
	mapresource->SetupWork->AreaID = area_id;
	mapresource->SetupWork->FldAnmMng = field_3d_anime;
	mapresource->SetupWork->Seq = 0;
	return mapresource;
}

//==============================================================================
/**
 * マップリソースセットアップ
 *
 * @param   outMapResource		MAPRESOURCEのポインタ
 *
 * @retval  none	
 */
//==============================================================================
void SetupMapResource(MAP_RESOURCE_PTR outMapResource)
{
	ARCHANDLE* model_handle;
#ifdef PM_DEBUG
	static int debug_tex_size;
#endif
	MAP_RES_SETUP_WORK *work = outMapResource->SetupWork;
	
	//アーカイブからエリアデータを取得
	ArchiveDataLoad(&outMapResource->ResourceParam, ARC_AREA_DATA, work->AreaID);
	
#ifdef DEBUG_ONLY_FOR_saitou	
	OS_Printf("local_print TEX_LOAD:%d\n",outMapResource->ResourceParam.tex_set);
#endif

	//エリア内モデリングデータリスト読み込み
	outMapResource->ModelFile = ArchiveDataLoadMalloc(	ARC_AREA_BUILD_MODEL,
														outMapResource->ResourceParam.model_set,
														HEAPID_FIELD );
	work->Num = outMapResource->ModelFile[0];

	GF_ASSERT(work->Num<BUILD_MODEL_MAX&&"配置モデル登録数オーバー");
	
	//地形用共通テクスチャ読み込み
	outMapResource->Tex = NULL;
	//AreaIDに対応した共通テクスチャファイルを読み込む
	outMapResource->pTexFile = ArchiveDataLoadMalloc(	ARC_AREA_TEX_SET,
														outMapResource->ResourceParam.tex_set,
														HEAPID_FIELD );
	//配置モデルテクスチャセットを読み込む
	outMapResource->pBmTexFile = ArchiveDataLoadMalloc(	ARC_BM_TEX_SET,
														outMapResource->ResourceParam.model_set,
														HEAPID_FIELD );
	// テクスチャファイルを取得
	outMapResource->Tex = NNS_G3dGetTex((NNSG3dResFileHeader*) outMapResource->pTexFile );
	if (work->Num != 0){
		outMapResource->BmTex = NNS_G3dGetTex((NNSG3dResFileHeader*) outMapResource->pBmTexFile );
	}else{
		outMapResource->BmTex = NULL;
	}

	{
		BOOL rc;
#ifdef DEBUG_TEX_INFO
		DebugPrintTexInfo(outMapResource->Tex);
#endif
		//テクスチャをＶＲＡＭへロード
		rc = LoadVRAMTexture(outMapResource->Tex);
		GF_ASSERT(rc && "テクスチャのVRAM確保失敗");
	}
	//実体を破棄
	CollapseResourceMemory(outMapResource->pTexFile, outMapResource->Tex);
	
	if (outMapResource->BmTex != NULL){
		BOOL rc;
#ifdef DEBUG_TEX_INFO
		DebugPrintTexInfo(outMapResource->BmTex);
#endif		
		//テクスチャをＶＲＡＭへロード
		rc = LoadVRAMTexture(outMapResource->BmTex);
		GF_ASSERT(rc && "テクスチャのVRAM確保失敗");
		//実体を破棄
		CollapseResourceMemory(outMapResource->pBmTexFile, outMapResource->BmTex);
	}
	
	{
		int i;
		//初期化
		for(i=0;i<BUILD_MODEL_MAX;i++){
			outMapResource->model[i] = NULL;
		}
		outMapResource->MatShpData = NULL;
		
#ifdef DEBUG_ONLY_FOR_saitou
		OS_Printf("local_print objct_num = %d\n",work->Num);
#endif
#ifdef PM_DEBUG
		debug_tex_size = 0;	
#endif
	}

	//3Dモデルアーカイブハンドルオープン
	model_handle = ArchiveDataHandleOpen( ARC_3D_STRUCT, HEAPID_FIELD );
	{
		int i;
		u16 no;
		int anime_num;

		anime_num = F3DA_GetAnimeArcObjNum(work->FldAnmMng);
		//ポインタ「now」は既に1行読み飛ばされたmodelTableの内容を指しているので次からStrTokはパス名取得になる
		for(i=0;i<work->Num;i++){
			no = outMapResource->ModelFile[i+1];//データはメモリの1番目から（0番目は個数）
#ifdef DEBUG_ONLY_FOR_saitou
			OS_Printf("local_print model_no = %d\n",no);
#endif
			GF_ASSERT_MSG(outMapResource->model[no]==NULL,"配置モデル(%d)の２重登録の可能性あり",no);
			outMapResource->model[no] = ArchiveDataLoadAllocByHandle( model_handle, no, HEAPID_FIELD );
			
			{
				//アニメセット
				NNSG3dResMdl* model;
				if (no < anime_num){
					model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(outMapResource->model[no]), 0);

					F3DA_AddField3DAnimeEasy(	no,
												model,
												outMapResource->BmTex,
												work->FldAnmMng	);
				}
			}
			//テクスチャバインド
			{
				BOOL rc;
				rc = BindTexture(outMapResource->model[no], outMapResource->BmTex);
				GF_ASSERT(rc && "3ＤＯＢＪテクスチャバインド失敗");
			}
#ifdef DEBUG_TEX_INFO				
			{
				NNSG3dResTex *tex;
				// テクスチャファイルを取得
				tex = NNS_G3dGetTex((NNSG3dResFileHeader*) outMapResource->model[no] );
				if(tex != NULL){
					DebugPrintTexInfo(tex);
				}
			}
#endif
		}//end for
	}
	//ダミーデータは常駐させとく
	if (outMapResource->model[0] == NULL){
		BOOL rc;
		NNSG3dResTex *tex;
//		outMapResource->model[0] = ArchiveDataLoadMalloc( ARC_3D_STRUCT, 0, HEAPID_FIELD );
		outMapResource->model[0] = ArchiveDataLoadAllocByHandle( model_handle, 0, HEAPID_FIELD );
		OS_Printf("何も置かれていないので、ダミーを登録\n");
		
		// テクスチャファイルを取得
		tex = NNS_G3dGetTex((NNSG3dResFileHeader*) outMapResource->model[0] );
		if(tex != NULL){
			//テクスチャをＶＲＡＭへロード
			rc = LoadVRAMTexture(tex);
			GF_ASSERT(rc && "テクスチャのVRAM確保失敗");
			//テクスチャバインド
			rc = BindTexture(outMapResource->model[0], tex);
			GF_ASSERT(rc && "3ＤＯＢＪテクスチャバインド失敗");
		}
	}

	//3Dモデルアーカイブハンドルクローズ
	ArchiveDataHandleClose( model_handle );
#if	1
		G3X_EdgeMarking(TRUE);
		if (outMapResource->ResourceParam.light == 0) {
			G3X_SetEdgeColorTable(gEdgeColorField);
		} else {
			G3X_SetEdgeColorTable(gEdgeColorOther);
		}
#endif
	///sys_FreeMemoryEz(work->ModelFile);
	{
		char name[256];
		//マテリアル、シェイプ対応データロード
		outMapResource->MatShpData = AllocMatShpData();
		sprintf(name,"fielddata/build_model/build_model_matshp.dat");
		LoadMatShape(name, outMapResource->MatShpData);
	}
	
///	OS_Printf("model_tex_size_total=%d\n",debug_tex_size);
	
	//ワークの解放
	sys_FreeMemoryEz(outMapResource->SetupWork);
	outMapResource->SetupWork = NULL;
}

//==============================================================================
/**
 * エリアに対応したモデリングデータファイル名の取得
 *
 * @param   index		モデルID
 * @param   mapresource		WORLD_MAPのポインタ
 *
 * @retval  NNSG3dResFileHeader**		モデリングデータのポインタ
 */
//==============================================================================
NNSG3dResFileHeader** GetMapResourceModelRes(const int index, const MAP_RESOURCE_PTR mapresource)
{
	GF_ASSERT((mapresource!=NULL) && "mapresourcemapが未確保");

	if (mapresource->model[index] == NULL){
//		OS_Printf("index = %d 配置モデル登録エラー ダミーを表示します\n",index);
		GF_ASSERT(mapresource->model[0]!=NULL&&"ダミーが登録されていない\n");
		//NULLデータがきたら、ダミーボックスを返すようにしておく
		return &(mapresource->model[0]);	
	}
	
	///GF_ASSERT((mapresource->model[index] != NULL)&&"モデリングデータが登録されていません");
	return &(mapresource->model[index]);	
	
}

//==============================================================================
/**
 * MAP_RESOURCEの解放
 *
 * @param   mapresource		MAP_RESOURCEのポインタ
 *
 * @retval  none		
 */
//==============================================================================
void ReleaseMapResource(MAP_RESOURCE_PTR *mapresource)
{
	int i;

	//マテリアル、シェイプ対応データ解放
	if ((*mapresource)->MatShpData != NULL){
		FreeMatShpData((*mapresource)->MatShpData);
	}

	for(i=0;i<BUILD_MODEL_MAX;i++){
		if((*mapresource)->model[i]!=NULL){
			sys_FreeMemoryEz((*mapresource)->model[i]);
		}
	}

	sys_FreeMemoryEz((*mapresource)->ModelFile);
	
	sys_FreeMemoryEz((*mapresource)->pTexFile);			// フィールド共通テクスチャ解放
	(*mapresource)->pTexFile   = NULL;
	sys_FreeMemoryEz((*mapresource)->pBmTexFile);			// 配置モデルテクスチャ解放
	(*mapresource)->pBmTexFile   = NULL;
	sys_FreeMemoryEz((*mapresource));						// ワールドマップ解放
	(*mapresource) = NULL;
}

//==============================================================================
/**
 * テクスチャファイルの実体のポインタを返す
 *
 * @param   mapresource		WORLD_MAPのポインタ
 *
 * @retval  NNSG3dResTex *		テクスチャデータのポインタ
 */
//==============================================================================
NNSG3dResTex *GetMapResourceTexturePTR(const MAP_RESOURCE_PTR mapresource)
{
	GF_ASSERT((mapresource!=NULL) && "mapresourcemapが未確保");

	return mapresource->Tex;	
}

//==============================================================================
/**
 * テクスチャファイルの実体のポインタを返す
 *
 * @param   mapresource		WORLD_MAPのポインタ
 *
 * @retval  NNSG3dResTex *		テクスチャデータのポインタ
 */
//==============================================================================
NNSG3dResTex *GetMapResourceBmTexturePTR(const MAP_RESOURCE_PTR mapresource)
{
	GF_ASSERT((mapresource!=NULL) && "mapresourcemapが未確保");

	return mapresource->BmTex;	
}

//==============================================================================
/**
 * マテリアル、シェイプ対応データへのポインタ取得関数
 *
 * @param   mapresource		マップリソースのポインタ
 *
 * @retval  MSD_CONST_PTR	マテリアル、シェイプ対応データへのポインタ
 */
//==============================================================================

MSD_CONST_PTR GetMatShpDataPtr(const MAP_RESOURCE_PTR mapresource)
{
	return mapresource->MatShpData;
}

//==============================================================================
/**
 * ライト有効かどうかの取得関数
 *
 * @param   mapresource		マップリソースのポインタ
 *
 * @retval  BOOL	TRUE:ライト有効		FALSE:ライト無効
 */
//==============================================================================
BOOL MAPRES_IsValidLight(const MAP_RESOURCE_PTR mapresource)
{
	if (mapresource->ResourceParam.light){
		return TRUE;
	}else{
		return FALSE;
	}
}

//==============================================================================
/**
 * ライトインデックスを取得
 *
 * @param   mapresource		マップリソースのポインタ
 *
 * @retval  light_idx	ライトインデックス
 */
//==============================================================================
u8 MAPRES_GetLightIndex(const MAP_RESOURCE_PTR mapresource)
{
	u8 light_idx; 
	if (mapresource->ResourceParam.light == 0 ){
		light_idx = LIGHT_TYPE2;
	}else{
		light_idx = LIGHT_TYPE1;
	}
	return light_idx;
}

//==============================================================================
/**
 * モデルファイルからOBJIDを取得
 *
 * @param   mapresource		マップリソースのポインタ
 * @param	inIndex			リストインデックス
 *
 * @retval  obj_id				OBJID（インデックス0番目は個数）
 */
//==============================================================================
int MAPRES_GetObjIDFromModelFile(const MAP_RESOURCE_PTR inMapResource, const int inIndex)
{
	int obj_id;
	obj_id = inMapResource->ModelFile[inIndex];
	return obj_id;
}

//==============================================================================
/**
 * リソースのエントリーチェック
 *
 * @param   mapresource		マップリソースのポインタ
 * @param	inID			OBJID
 *
 * @retval  TRUE:登録済み	FALSE:未登録
 */
//==============================================================================
BOOL CheckResourceEntry(const MAP_RESOURCE_PTR mapresource, const int inID)
{
	if ( mapresource->model[inID] == NULL ){
		return FALSE;
	}else{
		return TRUE;
	}
}

#ifdef PM_DEBUG
static void DebugPrintTexInfo(NNSG3dResTex *pTex)
{
	int szTex,numTex;
	// 必要なサイズを取得
	szTex    = NNS_G3dTexGetRequiredSize(pTex);
	numTex = pTex->dict.numEntry;
	OS_Printf("texsize = %d\n",szTex);
	OS_Printf("texnum = %d\n",numTex);
	{
		u32 fmt;
		int w,h;
		int i;
		int size;
		int total;
		total = 0;
		for(i=0;i<numTex;i++){
			const NNSG3dResName* name = NNS_G3dGetResNameByIdx(&pTex->dict, i);
			const NNSG3dResDictTexData* texData = NNS_G3dGetTexDataByName(pTex, name);
			fmt = (texData->texImageParam >> 26) & 7;
			size = (texData->extraParam & 0x3ff) * ( (texData->extraParam >> 11) & 0x3ff );
			switch(fmt){
			case 1:
				//RES_PRINTF("a3i5");
				break;
			case 2:
				//RES_PRINTF("palette4");
				size/=4;
				break;
			case 3:
				//RES_PRINTF("palette16");
				size/=2;
				break;
			case 4:
				//RES_PRINTF("palette256");
				break;
			case 5:
				//RES_PRINTF("tex4x4");
				break;
			case 6:
				//RES_PRINTF("a5i3");
				break;
			case 7:
				//RES_PRINTF("direct");
				break;
			}
			total+=size;
			OS_Printf("fmt=%d\n",fmt );
			OS_Printf("Addr=%d\n",(texData->texImageParam & 0xffff) << 3 );
		}//end for
	}
}

#endif //PM_DEBUG

