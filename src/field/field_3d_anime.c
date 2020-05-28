//=============================================================================
/**
 * @file	field_3d_anime.c
 * @bfief	フィールド3Dアニメーション関連処理
 * @author	Nozomu Saito
 *
 */
//=============================================================================

#include "common.h"

#include "field_3d_anime.h"
#include "fieldsys.h"
#include "field_event.h"

#include "map_tool.h"
#include "system/snd_tool.h"	//for SE
#include "system/arc_tool.h"

#include "fielddata/build_model/build_model_id.h"

#define ONE_MODEL_ANM_NUM_MAX	(4)	//１つのモデルに対して最大４つまでアニメが持てるとする
#define NO_ANIME		(0)
#define NO_ENTRY		(0)
#define ANIME_CONT_MAX	(16)	//16個まで同時管理
#define CONT_RENDER_OBJ_MAX	(6)	//アニメ管理データが持てる最大レンダーＯＢＪ数

#define SUICIDE_ANIME_MAX	(2)	//自殺アニメ管理最大数

#define ANIME_NONE_CODE		(0xffffffff)

typedef enum{
	STATE_END,	//終了
	STATE_MOVE,	//稼動中
}ANIME_STATE;

typedef enum{
	DATA_INVALID,
	DATA_VALID,
}DATA_VAL_STATE;

//自殺アニメ管理構造体
typedef struct SUICIDE_ANIME_DATA_tag
{
	BOOL Valid;						//データ有効フラグ
	NNSG3dRenderObj *RenderObj;		//アニメが適用されるレンダーOBJ
	FLD_3D_ANM_DAT_PTR AnimePtr;	//対象アニメポインタ
//	int ObjID;						//OBJID
	int AnimeCode;					//対象アニメコード
}SUICIDE_ANIME_DATA;

typedef struct FLD_3D_ANIME_DATA_tag{
	NNSG3dAnmObj* pAnmObj;
	DATA_VAL_STATE Valid;
	int LoopCount;
//	BOOL OneFrameEnd;
//	BOOL *EndFlg;
	int AnimeCode;
	BOOL StopFlg;
	void *pFile;
	int LoopMax;
	ANIME_STATE State;	//
	BOOL Reverse;
	int ControlCode;
}FLD_3D_ANIME_DATA;

typedef struct ANIME_INFO_tag
{
	u8 Flg;			//アニメするかどうか
	u8 Type;		//アニメタイプ
	u8 Suicide;		//自殺フラグ
	u8 dummy;		//ダミー
	int Code[4];	//アニメコード
}ANIME_INFO;

typedef struct FLD_3D_ANIME_MANAGER_tag{
	NNSFndAllocator AnimeAllocator;
	FLD_3D_ANIME_DATA Fld3DAnimeData[FLD_3D_ANIME_MAX];
	SUICIDE_ANIME_DATA SuicideData[SUICIDE_ANIME_MAX];
	ARCHANDLE* AnimeHandle;
	ARCHANDLE* AnmInfoHandle;
}FLD_3D_ANIME_MANAGER;

typedef struct ANIME_DATA_LIST_tag{
	FLD_3D_ANM_DAT_PTR Data[ONE_MODEL_ANM_NUM_MAX];	//アニメーションデータリストポインタ
	int AnimeNum;						//アニメーションデータの数;
}ANIME_DATA_LIST;

typedef struct ANIME_CONT_tag
{
	ANIME_DATA_LIST	AnimeList;			//アニメーションデータリスト
	NNSG3dRenderObj *RenderObj[CONT_RENDER_OBJ_MAX];			//アニメが適用されるレンダーOBJ
	FLD_3D_ANM_DAT_PTR BindAnime;			//バインドされているアニメ
	int ObjID;							//OBJID
	u8 EntryID;							//登録ID
}ANIME_CONT;

typedef struct ANIME_CONT_MNG_tag
{
	ANIME_CONT AnimeCont[ANIME_CONT_MAX];
}ANIME_CONT_MNG;

typedef struct ANIME_TABLE_tag
{
	int AnimeCode[ONE_MODEL_ANM_NUM_MAX];
}ANIME_TABLE;

//==============================================================================
/**
 * 自殺アニメエントリー
 *
 * @param	*ioSuicideData				自殺アニメ管理構造体へのポインタ
 * @param	*objectdata					対象レンダーOBJ
 * @param	anime						アニメポインタ
 * @param	inAnimeCode					対象アニメコード
 *
 * @return	BOOL	TRUE:自殺済みで登録可	FALSE:まだ生きてる
 */
//==============================================================================
static BOOL EntrySuicideAnime(	SUICIDE_ANIME_DATA *ioSuicideData,
								NNSG3dRenderObj *objectdata,
								FLD_3D_ANM_DAT_PTR	anime,
								const u8 inAnimeCode	)
{
	int i;
	GF_ASSERT(anime->LoopMax!=LOOP_INFINIT&&"ループ回数に制限が無いものは、対象外です");
	
	//同一エントリー検索
	for(i=0;i<SUICIDE_ANIME_MAX;i++){
		if (ioSuicideData[i].Valid){
			if ( (ioSuicideData[i].AnimeCode == inAnimeCode)&&
					(ioSuicideData[i].RenderObj == objectdata) ){
///				OS_Printf("同じものがすでにエントリされている\n");
				return FALSE;
			}
		}
	}
	//エントリー
	for(i=0;i<SUICIDE_ANIME_MAX;i++){
		if (!ioSuicideData[i].Valid){
			ioSuicideData[i].Valid = TRUE;
			ioSuicideData[i].AnimeCode = inAnimeCode;
			ioSuicideData[i].AnimePtr = anime;
			ioSuicideData[i].RenderObj = objectdata;
			break;
		}
	}
	return TRUE;
}


//==============================================================================
/**
 * アニメ取得
 *
 * @param	inHandle			アーカイブハンドル
 * @param	inID				アーカイブＩＤ
 * @param	pModel				モデルリソース
 * @param	pAnmObj				アニメOBJ
 * @param	pTex				テクスチャ
 * @param	allocator			アロケータ
 *
 * @return	void*				アニメポインタ
 */
//==============================================================================
static void *GetField3DAnimeByArc(	ARCHANDLE *inHandle,
									const u32 inID,
									NNSG3dResMdl* pModel,
									NNSG3dAnmObj** pAnmObj,
									NNSG3dResTex	*pTex,
									NNSFndAllocator *allocator)
{
    void *pAnmRes;
	void *mem = NULL;

	GF_ASSERT(inID != ANIME_NONE_CODE);

	mem = ArchiveDataLoadAllocByHandle( inHandle, inID, HEAPID_FIELD );

	GF_ASSERT(mem != NULL);
    {
        pAnmRes = NNS_G3dGetAnmByIdx(mem, 0);
        GF_ASSERT(pAnmRes != NULL);

        // 必要量のメモリをアロケートする。イニシャライズは別途必要になる。
        *pAnmObj = NNS_G3dAllocAnmObj(allocator, // 使用するアロケータを指定
                                     pAnmRes,    // アニメーションリソースを指定
                                     pModel);    // モデルリソースを指定
		GF_ASSERT(pAnmObj != NULL);

        //
        // AnmObj を初期化する。ジョイントアニメーション以外も同様
        //
        NNS_G3dAnmObjInit(*pAnmObj, // アニメーションオブジェクトへのポインタ
                          pAnmRes, // アニメリソースへのポインタ
                          pModel,  // NNSG3dResMdlへのポインタ
                          pTex );  // NNSG3dResTexへのポインタ(テクスチャパターンアニメ以外ならばNULLでもよい)
		return mem;
    }
}

//==============================================================================
/**
 * アニメリムーブ
 *
 * @param	inRenderObj				レンダーOBJ
 * @param	inAnmObj				アニメOBJ
 *
 * @return	BOOL				TRUE:リムーブした	FALSE:リムーブしなかった		
 */
//==============================================================================
static const BOOL RemoveAnime(NNSG3dRenderObj *inRenderObj, NNSG3dAnmObj *inAnmObj)
{
	if (inAnmObj == NULL){
		return FALSE;
	}
	if (inRenderObj == NULL){
		return FALSE;
	}

	//現行では、リムーブする対象が無くてもこの関数を通す(その場合、内部ではリムーブせずに戻る)
	NNS_G3dRenderObjRemoveAnmObj( inRenderObj, inAnmObj );
	return TRUE;
}

//==============================================================================
/**
 * 自殺アニメ監視
 *
 * @param	*ioSuicideData				自殺アニメ管理構造体へのポインタ
 * @param	*objectdata					対象レンダーOBJ
 * @param	inAnimeCode					対象アニメコード
 *
 * @return	none
 */
//==============================================================================
static void SuicideAnimeMain(SUICIDE_ANIME_DATA *ioSuicideData)
{
	int i;
	for(i=0;i<SUICIDE_ANIME_MAX;i++){
		if (ioSuicideData[i].Valid){
			//アニメ終了をチェック
			if (F3DA_IsAnimeEnd(ioSuicideData[i].AnimePtr)){
				//終了していたらアニメパージ
				RemoveAnime(ioSuicideData[i].RenderObj, ioSuicideData[i].AnimePtr->pAnmObj);
				ioSuicideData[i].Valid = FALSE;
				ioSuicideData[i].AnimeCode = 0;
				ioSuicideData[i].AnimePtr = NULL;
				ioSuicideData[i].RenderObj = NULL;
			}
		}
	}
}

//==============================================================================
/**
 * 3Dアニメマネージャのメモリアロケーション
 *
 * @return	FLD_3D_ANM_MNG_PTR				アニメ管理構造体へのポインタ
 */
//==============================================================================
FLD_3D_ANM_MNG_PTR F3DA_Field3DAnimeInit(void)
{
	int i;
	FLD_3D_ANM_MNG_PTR field_3d_anime_ptr;
	field_3d_anime_ptr = sys_AllocMemory( HEAPID_FIELD, sizeof(FLD_3D_ANIME_MANAGER) );
	//空いてるアニメ配列を検索
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		field_3d_anime_ptr->Fld3DAnimeData[i].Valid = DATA_INVALID;
		field_3d_anime_ptr->Fld3DAnimeData[i].StopFlg = FALSE;
		field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj = NULL;
		field_3d_anime_ptr->Fld3DAnimeData[i].LoopCount = 0;
//		field_3d_anime_ptr->Fld3DAnimeData[i].EndFlg = NULL;
		field_3d_anime_ptr->Fld3DAnimeData[i].AnimeCode = 0;
		field_3d_anime_ptr->Fld3DAnimeData[i].pFile = NULL;
		field_3d_anime_ptr->Fld3DAnimeData[i].LoopMax = LOOP_INFINIT;
		field_3d_anime_ptr->Fld3DAnimeData[i].State = STATE_END;
		field_3d_anime_ptr->Fld3DAnimeData[i].Reverse = FALSE;
		field_3d_anime_ptr->Fld3DAnimeData[i].ControlCode = 0;
	}
	for(i=0;i<SUICIDE_ANIME_MAX;i++){
		field_3d_anime_ptr->SuicideData[i].Valid = FALSE;
		field_3d_anime_ptr->SuicideData[i].RenderObj = NULL;
		field_3d_anime_ptr->SuicideData[i].AnimePtr = NULL;
		field_3d_anime_ptr->SuicideData[i].AnimeCode = 0;
	}
	//アニメアロケータ
	sys_InitAllocator(&field_3d_anime_ptr->AnimeAllocator,HEAPID_FIELD,4);
	//アニメアーカイブハンドルオープン
	field_3d_anime_ptr->AnimeHandle = ArchiveDataHandleOpen( ARC_BM_ANM, HEAPID_FIELD );
	//アニメ情報アーカイブハンドルオープン
	field_3d_anime_ptr->AnmInfoHandle = ArchiveDataHandleOpen( ARC_BM_ANM_LIST, HEAPID_FIELD );	
//	field_3d_anime_ptr->EndFlg = FALSE;
	return field_3d_anime_ptr;
}


//==============================================================================
/**
 * アニメOBJ取得
 * @param	inFld3DAnmDat			アニメデータポインタ
 *
 * @return	NNSG3dAnmObj			アニメOBJ
 */
//==============================================================================
static NNSG3dAnmObj *GetAnmObj(FLD_3D_ANM_DAT_PTR inFld3DAnmDat)
{
	if (inFld3DAnmDat == NULL){
		return NULL;
	}
	return inFld3DAnmDat->pAnmObj;
}

//==============================================================================
/**
 * 追加に条件があるかどうかをチェック
 * @param	inType			アニメタイプ
 *
 * @return	BOOL			TRUE:ある	FALSE:ない
 */
//==============================================================================
static BOOL CheckAddConditional(const u8 inType)
{
	if ( (inType&0x01) == 0x01 ){
		return TRUE;		//条件あり
	}else{
		return FALSE;		//条件無し
	}
}

//==============================================================================
/**
 * セットに条件があるかどうかをチェック
 * @param	inType			アニメタイプ
 *
 * @return	BOOL			TRUE:ある	FALSE:ない
 */
//==============================================================================
static BOOL CheckSetConditional(const u8 inType)
{
	if ( ((inType>>1)&0x01) == 0x01){
		return TRUE;		//条件あり
	}else{
		return FALSE;		//条件無し
	}
}

//==============================================================================
/**
 * アニメステートの取得
 *
 * @param	inAnimeData				アニメデータポインタ
 *
 * @return	int						アニメステート
 */
//==============================================================================
static int GetAnimeState(const FLD_3D_ANM_DAT_PTR inAnimeData)
{
	GF_ASSERT((inAnimeData->Valid == DATA_VALID)&&"データは無効です");
	return inAnimeData->State;
}

//==============================================================================
/**
 * アニメーション追加
 *
 * @param	inObjCode				OBJID
 * @param	inAnimeNo				再生するアニメナンバー
 * @param	inLoopCount				繰り返し回数
 * @param	inCode					制御コード
 * @param	inReverse				逆再生フラグ
 * @param	inStopFlg				停止フラグ
 * @param	inAnimeType				追加するアニメタイプ
 * @param	objectmodel				リソースモデル
 * @oaram	pTex					テクスチャリソース（テクスチャパターンアニメ用）
 * @param	field_3d_anime_ptr		アニメマネージャへのポインタ
 *
 * @return	ANIME_CONT_PTR	アニメデータポインタ
 */
//==============================================================================
FLD_3D_ANM_DAT_PTR F3DA_AddField3DAnime(const int inObjCode,
										const int inAnimeNo,
										const int inLoopCount,
										const int inCode,
										const BOOL inReverse,
										const BOOL inStopFlg,
										const BOOL inConditional,
										NNSG3dResMdl *objectmodel,
										NNSG3dResTex	*pTex,
										FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	FLD_3D_ANM_DAT_PTR data;
	int i;
	int anime_code;
	ANIME_INFO info;

	//指定ＯＢＪアニメ情報をアーカイバから入手
	ArchiveDataLoadByHandle(field_3d_anime_ptr->AnmInfoHandle, inObjCode, &info);

	GF_ASSERT(inAnimeNo<ONE_MODEL_ANM_NUM_MAX);

	anime_code = info.Code[inAnimeNo];
	if (anime_code == ANIME_NONE_CODE){
		return NULL;
	}

	if ( CheckAddConditional(info.Type) != inConditional){
///		OS_Printf("条件を見たしていない:%d\n",anime_code);
		return NULL;
	}
	
	//制御コード重複チェック
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		if ((inCode != 0)&&
				(field_3d_anime_ptr->Fld3DAnimeData[i].ControlCode == inCode)){
///			OS_Printf("%d:重複登録です\n",inCode);
			GF_ASSERT(0);
		}
	}

	//空いてるアニメ配列を検索
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		if (field_3d_anime_ptr->Fld3DAnimeData[i].Valid == DATA_INVALID){
			field_3d_anime_ptr->Fld3DAnimeData[i].Valid = DATA_VALID;
			field_3d_anime_ptr->Fld3DAnimeData[i].StopFlg = inStopFlg;
			field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj = NULL;
			field_3d_anime_ptr->Fld3DAnimeData[i].LoopCount = 0;
			//field_3d_anime_ptr->Fld3DAnimeData[i].EndFlg = NULL;
			field_3d_anime_ptr->Fld3DAnimeData[i].AnimeCode = anime_code;
			field_3d_anime_ptr->Fld3DAnimeData[i].Reverse = inReverse;
			field_3d_anime_ptr->Fld3DAnimeData[i].ControlCode = inCode;

			field_3d_anime_ptr->Fld3DAnimeData[i].pFile =
									GetField3DAnimeByArc(	field_3d_anime_ptr->AnimeHandle,
																anime_code,
																objectmodel,
																&field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj,
																pTex,
																&field_3d_anime_ptr->AnimeAllocator);
			field_3d_anime_ptr->Fld3DAnimeData[i].LoopMax = inLoopCount;
			field_3d_anime_ptr->Fld3DAnimeData[i].State = STATE_MOVE;
			data = &(field_3d_anime_ptr->Fld3DAnimeData[i]);
			//再生方向を見て、開始フレームをセット
			F3DA_SetStartFrame(&field_3d_anime_ptr->Fld3DAnimeData[i]);
			return data;
		}
	}
	//追加できない場合
	GF_ASSERT(0&&"3Dアニメ追加できませんでした");
	return NULL;
}

//==============================================================================
/**
 * アニメーション追加(詳細な設定は行わない、常駐アニメさせるやつ用)
 *
 * @param	inObjCode				OBJID
 * @param	objectmodel				リソースモデル
 * @oaram	pTex					テクスチャリソース（テクスチャパターンアニメ用）
 * @param	field_3d_anime_ptr		アニメマネージャへのポインタ
 *
 * @return	none
 */
//==============================================================================
void F3DA_AddField3DAnimeEasy(	const int inObjCode,
								NNSG3dResMdl *objectmodel,
								NNSG3dResTex	*pTex,
								FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	int anime_code;
	int n;
	int i;

	ANIME_INFO info;
	//指定ＯＢＪアニメ情報をアーカイバから入手
	ArchiveDataLoadByHandle(field_3d_anime_ptr->AnmInfoHandle, inObjCode, &info);

	//アニメしないものは処理しない
	if (!info.Flg){
		return;
	}
		
	for(n=0;n<ONE_MODEL_ANM_NUM_MAX;n++){
		anime_code = info.Code[n];
		if (anime_code == ANIME_NONE_CODE){
			return;//処理を抜ける
		}
		
		if ( CheckAddConditional(info.Type) != FALSE){
///				OS_Printf("条件を見たしていない:%d\n",anime_code);
				return;
		}

		//空いてるアニメ配列を検索
		for(i=0;i<FLD_3D_ANIME_MAX;i++){
			if (field_3d_anime_ptr->Fld3DAnimeData[i].Valid == DATA_INVALID){
				field_3d_anime_ptr->Fld3DAnimeData[i].Valid = DATA_VALID;
				field_3d_anime_ptr->Fld3DAnimeData[i].StopFlg = FALSE;
				field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj = NULL;
				field_3d_anime_ptr->Fld3DAnimeData[i].LoopCount = 0;
				//field_3d_anime_ptr->Fld3DAnimeData[i].EndFlg = NULL;
				field_3d_anime_ptr->Fld3DAnimeData[i].AnimeCode = anime_code;
				field_3d_anime_ptr->Fld3DAnimeData[i].Reverse = FALSE;
				field_3d_anime_ptr->Fld3DAnimeData[i].ControlCode = 0;

				field_3d_anime_ptr->Fld3DAnimeData[i].pFile =
										GetField3DAnimeByArc(	field_3d_anime_ptr->AnimeHandle,
																anime_code,
																objectmodel,
																&field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj,
																pTex,
																&field_3d_anime_ptr->AnimeAllocator);
				field_3d_anime_ptr->Fld3DAnimeData[i].LoopMax = LOOP_INFINIT;
				field_3d_anime_ptr->Fld3DAnimeData[i].State = STATE_MOVE;
				//再生方向を見て、開始フレームをセット
				F3DA_SetStartFrame(&field_3d_anime_ptr->Fld3DAnimeData[i]);
	
				//自殺アニメは開始時はとめておく（今のところ対象は流砂）
				if ( info.Suicide/*(inObjCode == BMID_CY_SLOPE) || (inObjCode == BMID_CY_SLOPE_DUN)*/ ){	
					field_3d_anime_ptr->Fld3DAnimeData[i].StopFlg = TRUE;
					field_3d_anime_ptr->Fld3DAnimeData[i].LoopMax = 1;
				}
				break;//次の登録へ
			}
		}//end for(i)
		
		//追加できない場合
		GF_ASSERT((i!=FLD_3D_ANIME_MAX)&&"3Dアニメ追加できませんでした");
	}// end for(n)
}

//==============================================================================
/**
 * アニメーションセット
 *
 * @param	inObjCode				OBJID
 * @param	inAnimeNo				再生するアニメナンバー
 * @param	objectdata				レンダーOBJ
 * @param	field_3d_anime_ptr		アニメマネージャへのポインタ
 *
 * @return	BOOL	TRUE:セットできた	FALSE:セットできなかった
 */
//==============================================================================
BOOL F3DA_SetFld3DAnime(const int inObjCode,
						const int inAnimeNo,
						const BOOL inConditional,
						NNSG3dRenderObj *objectdata,
						FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	int i;
	int anime_code;
	ANIME_INFO info;
	
	BOOL rc;
	if (field_3d_anime_ptr==NULL){
		GF_ASSERT_MSG(0,"アニメマネージャがNULLです");
		return FALSE;
	}

	if (inObjCode >= F3DA_GetAnimeArcObjNum(field_3d_anime_ptr)){
		return FALSE;
	}
		
	//指定ＯＢＪアニメ情報をアーカイバから入手
	ArchiveDataLoadByHandle(field_3d_anime_ptr->AnmInfoHandle, inObjCode, &info);

	GF_ASSERT(inAnimeNo<ONE_MODEL_ANM_NUM_MAX);
	
	anime_code = info.Code[inAnimeNo];
	if (anime_code == ANIME_NONE_CODE){
		return FALSE;
	}

	if ( CheckSetConditional(info.Type) != inConditional){
///		OS_Printf("条件を満たしていない:%d\n",anime_code);
		return FALSE;
	}

	//指定アニメをOBJにセット
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		if(anime_code == field_3d_anime_ptr->Fld3DAnimeData[i].AnimeCode){
			//自殺アニメーションエントリー
			if (info.Suicide){
				rc = EntrySuicideAnime(	field_3d_anime_ptr->SuicideData,
										objectdata,
										&field_3d_anime_ptr->Fld3DAnimeData[i],
										anime_code	);
			}else{
				rc = TRUE;
			}

			if (rc){
				NNS_G3dRenderObjAddAnmObj( objectdata, field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj );
			}
			
			return TRUE;
		}
	}
	//アニメがない場合
///	OS_Printf("ObjID=%d:3Dアニメありません\n",inObjCode);
	return FALSE;
}

//==============================================================================
/**
 * アニメーションセット
 *
 * @param	inObjCode				OBJID
 * @param	objectdata				レンダーOBJ
 * @param	field_3d_anime_ptr		アニメマネージャへのポインタ
 *
 * @return	BOOL	TRUE:セットできた	FALSE:セットできなかった
 */
//==============================================================================
BOOL F3DA_SetFld3DAnimeEasy(const int inObjCode,
							NNSG3dRenderObj *objectdata,
							FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	int n;
	int i;
	int anime_code;
	ANIME_INFO info;
	
	BOOL set_flg;
	BOOL rc;

	set_flg = FALSE;
	
	if (field_3d_anime_ptr==NULL){
		GF_ASSERT(0&&"アニメマネージャがNULLです");
	}

	if (inObjCode >= F3DA_GetAnimeArcObjNum(field_3d_anime_ptr)){
		return FALSE;
	}
		
	//指定ＯＢＪアニメ情報をアーカイバから入手
	ArchiveDataLoadByHandle(field_3d_anime_ptr->AnmInfoHandle, inObjCode, &info);

	if ( CheckSetConditional(info.Type) != FALSE){
///		OS_Printf("条件を満たしていない:%d\n",anime_code);
		return FALSE;
	}
	
	for(n=0;n<ONE_MODEL_ANM_NUM_MAX;n++){
		anime_code = info.Code[n];
		if (anime_code == ANIME_NONE_CODE){
			return set_flg;//処理を抜ける
		}

		//指定アニメをOBJにセット
		for(i=0;i<FLD_3D_ANIME_MAX;i++){
			if(anime_code == field_3d_anime_ptr->Fld3DAnimeData[i].AnimeCode){
				//自殺アニメーションエントリー
				if (info.Suicide){
					rc = EntrySuicideAnime(	field_3d_anime_ptr->SuicideData,
											objectdata,
											&field_3d_anime_ptr->Fld3DAnimeData[i],
											anime_code	);
				}else{
					rc = TRUE;
				}

				if (rc){
					NNS_G3dRenderObjAddAnmObj( objectdata, field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj );
					set_flg = TRUE;
				}
			
				break;
			}
		}
		//アニメがない場合
///		OS_Printf("ObjID=%d:3Dアニメありません\n",inObjCode);
	}
	
	return set_flg;
}

//==============================================================================
/**
 * アニメーション全解放
 *
 * @param	field_3d_anime_ptr		アニメマネージャへのポインタ
 *
 * @return	none
 */
//==============================================================================
void RereaseFld3DAnimeAll(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	int i;
	if (field_3d_anime_ptr==NULL) return;
	
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		if (field_3d_anime_ptr->Fld3DAnimeData[i].Valid != DATA_INVALID){
			if (field_3d_anime_ptr->Fld3DAnimeData[i].Valid == DATA_VALID){
				NNS_G3dFreeAnmObj(&field_3d_anime_ptr->AnimeAllocator,field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj);
				field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj = NULL;
				sys_FreeMemoryEz(field_3d_anime_ptr->Fld3DAnimeData[i].pFile);
			}
			field_3d_anime_ptr->Fld3DAnimeData[i].Valid = DATA_INVALID;
			field_3d_anime_ptr->Fld3DAnimeData[i].ControlCode = 0;
		}
	}
}

//==============================================================================
/**
 * インデックスによるアニメーション解放
 *
 * @param	inIdx				インデックス
 * @param	field_3d_anime_ptr		アニメマネージャへのポインタ
 *
 * @return	none
 */
//==============================================================================
void RereaseFld3DAnimeByIdx(const u8 inIdx, FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	GF_ASSERT(inIdx<FLD_3D_ANIME_MAX);
	
	if (field_3d_anime_ptr==NULL) return;
	
	if (field_3d_anime_ptr->Fld3DAnimeData[inIdx].Valid != DATA_INVALID){
		if (field_3d_anime_ptr->Fld3DAnimeData[inIdx].Valid == DATA_VALID){
			NNS_G3dFreeAnmObj(	&field_3d_anime_ptr->AnimeAllocator,
								field_3d_anime_ptr->Fld3DAnimeData[inIdx].pAnmObj);
			field_3d_anime_ptr->Fld3DAnimeData[inIdx].pAnmObj = NULL;
			sys_FreeMemoryEz(field_3d_anime_ptr->Fld3DAnimeData[inIdx].pFile);
		}
		field_3d_anime_ptr->Fld3DAnimeData[inIdx].Valid = DATA_INVALID;
		field_3d_anime_ptr->Fld3DAnimeData[inIdx].ControlCode = 0;
	}
}

//==============================================================================
/**
 * アニメーション解放
 *
 * @param	outAnimePtr				アニメデータポインタ
 * @param	field_3d_anime_ptr		アニメマネージャへのポインタ
 *
 * @return	none
 */
//==============================================================================
void F3DA_RereaseFld3DAnime(FLD_3D_ANM_DAT_PTR outAnimePtr, FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	if (field_3d_anime_ptr==NULL) return;
	
	GF_ASSERT(outAnimePtr!=NULL&&"NULL解放しようとしています");
	
	if (outAnimePtr->Valid != DATA_INVALID){
		if (outAnimePtr->Valid == DATA_VALID){
			NNS_G3dFreeAnmObj(	&field_3d_anime_ptr->AnimeAllocator,
								outAnimePtr->pAnmObj);
			outAnimePtr->pAnmObj = NULL;
			sys_FreeMemoryEz(outAnimePtr->pFile);
		}
		outAnimePtr->Valid = DATA_INVALID;
		outAnimePtr->ControlCode = 0;
	}
}

//==============================================================================
/**
 * アニメーションリムーブ
 *
 * @param	field_3d_anime_ptr		アニメマネージャへのポインタ
 * @param	inRenderObj				レンダーOBJ
 * @param	inObjCode				OBJID
 * @param	inAnimeNo				リムーブするアニメナンバー
 * 
 * @return	none
 */
//==============================================================================
void F3DA_RemoveFld3DAnime(	FLD_3D_ANM_MNG_PTR field_3d_anime_ptr,
							NNSG3dRenderObj *inRenderObj,
							const int inObjCode,
							const int inAnimeNo	)
{
	u8 i;
	int anime_code;
	ANIME_INFO info;
	//指定ＯＢＪアニメ情報をアーカイバから入手
	ArchiveDataLoadByHandle(field_3d_anime_ptr->AnmInfoHandle, inObjCode, &info);
	GF_ASSERT(inAnimeNo<ONE_MODEL_ANM_NUM_MAX);
	anime_code = info.Code[inAnimeNo];
	GF_ASSERT(anime_code != ANIME_NONE_CODE);
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		if ( field_3d_anime_ptr->Fld3DAnimeData[i].Valid == DATA_VALID ){
			if(field_3d_anime_ptr->Fld3DAnimeData[i].AnimeCode == anime_code){
				RemoveAnime(inRenderObj, field_3d_anime_ptr->Fld3DAnimeData[i].pAnmObj);
				return;
			}
		}
	}
}

//==============================================================================
/**
 * アニメーションマネージャ解放
 *
 * @param	field_3d_anime_ptr		アニメマネージャへのポインタ
 * 
 * @return	none
 */
//==============================================================================
void FreeFld3DAnimeManager(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	if (field_3d_anime_ptr==NULL) return;
	
	//ハンドルクローズ
	ArchiveDataHandleClose( field_3d_anime_ptr->AnimeHandle );
	ArchiveDataHandleClose( field_3d_anime_ptr->AnmInfoHandle );
	
	sys_FreeMemoryEz( field_3d_anime_ptr );
	field_3d_anime_ptr = NULL;
}

//==============================================================================
/**
 * マネージャ管理インデックスでアニメデータを取得
 *
 * @param	inIndex					インデックス
 * @param	field_3d_anime_ptr		アニメマネージャへのポインタ
 * 
 * @return	none
 */
//==============================================================================
FLD_3D_ANM_DAT_PTR F3DA_GetFld3DAnmPtrByIdx(const int inIndex,
											FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	FLD_3D_ANM_DAT_PTR data;
	
	GF_ASSERT(inIndex<FLD_3D_ANIME_MAX);
	data = &(field_3d_anime_ptr->Fld3DAnimeData[inIndex]);

	GF_ASSERT(data->Valid!=DATA_INVALID&&"指定データは無効状態です");
	
	return data;
}

//==============================================================================
/**
 * 制御コードでアニメデータを取得
 *
 * @param	inCode					制御コード
 * @param	field_3d_anime_ptr		アニメマネージャへのポインタ
 * 
 * @return	none
 */
//==============================================================================
FLD_3D_ANM_DAT_PTR F3DA_GetFld3DAnmPtrByCode(	const int inCode,
												FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	FLD_3D_ANM_DAT_PTR data;
	int i;
	GF_ASSERT(inCode!=0&&"制御コードがふられていないアニメは取得対象外です");
	data = NULL;
	//検索
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		if (field_3d_anime_ptr->Fld3DAnimeData[i].ControlCode == inCode){
			data = &(field_3d_anime_ptr->Fld3DAnimeData[i]);
			GF_ASSERT(data->Valid!=DATA_INVALID&&"指定データは無効状態です");
			break;
		}
	}
	GF_ASSERT(data!=NULL&&"アニメが見つかりませんでした");
	return data;
}

//==============================================================================
/**
 * アニメデータを取得
 *
 * @param	inObjID					ＯＢＪＩＤ
 * @param	inAnimeNo				アニメナンバー
 * @param	field_3d_anime_ptr		アニメマネージャへのポインタ
 * 
 * @return	none
 */
//==============================================================================
FLD_3D_ANM_DAT_PTR F3DA_GetFld3DAnmPtr(	const int inObjID,
										const int inAnimeNo,
										FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	FLD_3D_ANM_DAT_PTR data;
	int anime_code;
	int i;
	ANIME_INFO info;
	//指定ＯＢＪアニメ情報をアーカイバから入手
	ArchiveDataLoadByHandle(field_3d_anime_ptr->AnmInfoHandle, inObjID, &info);

	GF_ASSERT(inAnimeNo<ONE_MODEL_ANM_NUM_MAX);

	anime_code = info.Code[inAnimeNo];

	data = NULL;
	
	//検索
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		if (field_3d_anime_ptr->Fld3DAnimeData[i].AnimeCode == anime_code){
			data = &(field_3d_anime_ptr->Fld3DAnimeData[i]);
			GF_ASSERT(data->Valid!=DATA_INVALID&&"指定データは無効状態です");
			break;
		}
	}
	GF_ASSERT(data!=NULL&&"アニメが見つかりませんでした");
	return data;
}

//==============================================================================
/**
 * インデックスによるストップフラグの切り替え
 *
 * @param	inIdx					インデックス
 * @param	inFlg					ストップフラグ
 * @param	field_3d_anime_ptr		アニメーションマネージャへのポインタ
 * 
 * @return	none
 */
//==============================================================================
void F3DA_SetStopFlgByIdx(const u8 inIdx, const BOOL inFlg, FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	GF_ASSERT(inIdx<FLD_3D_ANIME_MAX);
	field_3d_anime_ptr->Fld3DAnimeData[inIdx].StopFlg = inFlg;
}

//==============================================================================
/**
 * ストップフラグの切り替え
 *
 * @param	inAnimePtr				アニメデータポインタ
 * @param	inFlg					ストップフラグ
 * 
 * @return	none
 */
//==============================================================================
void F3DA_SetStopFlg(FLD_3D_ANM_DAT_PTR inAnimePtr, const BOOL inFlg)
{
	inAnimePtr->StopFlg = inFlg;
}

//==============================================================================
/**
 * アニメーションステートを動作中にする
 *
 * @param	inAnimePtr				アニメデータポインタ
 * 
 * @return	none
 */
//==============================================================================
void F3DA_MoveAnime(FLD_3D_ANM_DAT_PTR inAnimePtr)
{
	inAnimePtr->State = STATE_MOVE;
}

//==============================================================================
/**
 * アニメーションが最終フレームかを返す
 *
 * @param	inAnimeData	アニメーションデータへのポインタ
 *
 * @return	BOOL TRUE:最終フレーム	FALSE:最終フレーム以外
 */
//==============================================================================
BOOL F3DA_IsLastFrame(FLD_3D_ANM_DAT_PTR	inAnimeData)
{
	BOOL rc;
	if (!inAnimeData->Reverse){	//通常まわし
		if (inAnimeData->pAnmObj->frame >= 
				NNS_G3dAnmObjGetNumFrame(inAnimeData->pAnmObj)-(FX32_ONE)){
			rc = TRUE;
		}else{
			rc = FALSE;
		}
	}else{						//逆まわし
		if (inAnimeData->pAnmObj->frame == 0){
			rc = TRUE;
		}else{
			rc = FALSE;
		}
	}
	return rc;
}

//==============================================================================
/**
 * 開始アニメーションフレームセット
 *
 * @param	outAnimeData	アニメーションデータへのポインタ
 *
 * @return	none
 */
//==============================================================================
void F3DA_SetStartFrame(FLD_3D_ANM_DAT_PTR	outAnimeData)
{
	if (!outAnimeData->Reverse){	//通常まわし
		outAnimeData->pAnmObj->frame = 0;
	}else{						//逆まわし
		outAnimeData->pAnmObj->frame = NNS_G3dAnmObjGetNumFrame(outAnimeData->pAnmObj)-(FX32_ONE);
	}
}

//==============================================================================
/**
 * 開始アニメーションフレームセット
 *
 * @param	outAnimeData	アニメーションデータへのポインタ
 *
 * @return	none
 */
//==============================================================================
void F3DA_SetLastFrame(FLD_3D_ANM_DAT_PTR	outAnimeData)
{
	if (!outAnimeData->Reverse){	//通常まわし
		outAnimeData->pAnmObj->frame = NNS_G3dAnmObjGetNumFrame(outAnimeData->pAnmObj)-(FX32_ONE);
	}else{						//逆まわし
		outAnimeData->pAnmObj->frame = 0;
	}
}

//==============================================================================
/**
 * 開始アニメーションフレーム変更
 *
 * @param	outAnimeData	アニメーションデータへのポインタ
 *
 * @return	none
 */
//==============================================================================
void F3DA_ChangeFrame(FLD_3D_ANM_DAT_PTR	outAnimeData)
{
	if (!outAnimeData->Reverse){	//通常まわし
		outAnimeData->pAnmObj->frame += (FX32_ONE);
		if (outAnimeData->pAnmObj->frame == NNS_G3dAnmObjGetNumFrame(outAnimeData->pAnmObj)){
			outAnimeData->pAnmObj->frame = 0;
		}

	}else{						//逆まわし
		if (outAnimeData->pAnmObj->frame <= 0){
			outAnimeData->pAnmObj->frame =
				NNS_G3dAnmObjGetNumFrame(outAnimeData->pAnmObj)-(FX32_ONE);
		}else{
			outAnimeData->pAnmObj->frame -= (FX32_ONE);
		}
	}
}

//==============================================================================
/**
 * 指定アニメーションの再生方向を逆にする
 *
 * @param	outAnimeData	アニメーションデータへのポインタ
 *
 * @return	none
 */
//==============================================================================
void F3DA_SetAnimeReverse(FLD_3D_ANM_DAT_PTR	outAnimeData)
{
	//回数指定アニメの場合はアサートを発行
	///GF_ASSERT(outAnimeData->LoopMax != LOOP_INFINIT && "回数指定アニメーションの逆回しはサポートしていません");
	if (outAnimeData->Reverse){
		outAnimeData->Reverse = FALSE;
	}else{
		outAnimeData->Reverse = TRUE;
	}
}

//==============================================================================
/**
 * 指定アニメーションの再生方向を逆にする(直接指定)
 *
 * @param	outAnimeData	アニメーションデータへのポインタ
 *
 * @return	none
 */
//==============================================================================
void F3DA_SetAnimeReverseDirect(FLD_3D_ANM_DAT_PTR	outAnimeData, const BOOL inReverse)
{
	//回数指定アニメの場合はアサートを発行
	///GF_ASSERT(outAnimeData->LoopMax != LOOP_INFINIT && "回数指定アニメーションの逆回しはサポートしていません");
	outAnimeData->Reverse = inReverse;
}

//==============================================================================
/**
 * 指定アニメーションの最大ループ数をセット
 *
 * @param	outAnimeData	アニメーションデータへのポインタ
 * @param	inLoopMax		ループ数
 *
 * @return	none
 */
//==============================================================================
void F3DA_SetAnimeLoopMax(FLD_3D_ANM_DAT_PTR	outAnimeData, const int inLoopMax)
{
	outAnimeData->LoopMax = inLoopMax;
}

//==============================================================================
/**
 * 指定アニメーションの制御コードをセット
 *
 * @param	outAnimeData	アニメーションデータへのポインタ
 * @param	inControlCode	制御コード
 *
 * @return	none
 */
//==============================================================================
void F3DA_SetControlCode(FLD_3D_ANM_DAT_PTR	outAnimeData, const int inControlCode)
{
	outAnimeData->ControlCode = inControlCode;
}

//==============================================================================
/**
 * アニメーションメイン関数
 *
 * @param	field_3d_anime_ptr	3Dアニメーションマネージャへのポインタ
 *
 * @return	none
 */
//==============================================================================
void F3DA_Main(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	int i;
	FLD_3D_ANM_DAT_PTR	anime_data;
	if (field_3d_anime_ptr==NULL) return;
	for(i=0;i<FLD_3D_ANIME_MAX;i++){
		anime_data = &(field_3d_anime_ptr->Fld3DAnimeData[i]);
		//アニメは有効かどうか
		if (anime_data->Valid == DATA_VALID){
			//アニメーションが停止している、もしくはアニメが終了している場合は処理を飛ばす
			if ((anime_data->StopFlg == TRUE)||(anime_data->State == STATE_END)){
				continue;
			}

			F3DA_ChangeFrame(anime_data);	//フレーム切り替え
			
			if ( anime_data->LoopMax != LOOP_INFINIT ){	//ループ指定回数あり
				if (F3DA_IsLastFrame(anime_data)){			//最終フレームか？
					if (anime_data->LoopCount+1 >= anime_data->LoopMax){//最終指定ループ回数目か？
						//アニメ終了
						anime_data->State = STATE_END;
					}else{
						anime_data->LoopCount++;	//ループ数をインクリメント
					}
				}
			}
		}
	}// end for
	//自殺監視
	SuicideAnimeMain(field_3d_anime_ptr->SuicideData);

}

//==============================================================================
/**
 * アニメーションが終了しているかを返す
 * @param	inAnimeData	アニメデータへのポインタ
 *
 * @return	BOOL	TRUE:終了　FALSE:NO 継続
 */
//==============================================================================
BOOL F3DA_IsAnimeEnd(const FLD_3D_ANM_DAT_PTR inAnimeData)
{
	int state;
	state = GetAnimeState(inAnimeData);
	if (state == STATE_END){
		return TRUE;
	}else{
		return FALSE;
	}
}

//==============================================================================
/**
 * アニメアーカイブが保持しているＯＢＪの数を返す
 * 
 * @param	field_3d_anime_ptr	3Dアニメーションマネージャへのポインタ
 *
 * @return	u16 ファイル数
 */
//==============================================================================
u16 F3DA_GetAnimeArcObjNum(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	return ArchiveDataFileCntGetByHandle(field_3d_anime_ptr->AnmInfoHandle);
}

//==============================================================================
/**
 * 指定ＯＢＪＩＤのアニメ数を返す
 * 
 * @param	field_3d_anime_ptr	3Dアニメーションマネージャへのポインタ
 *
 * @return	u16 アニメ数
 */
//==============================================================================
const u8 F3DA_GetAnimeNum(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr, const int inObjCode)
{
	u8 n;
	ANIME_INFO info;
	//指定ＯＢＪアニメ情報をアーカイバから入手
	ArchiveDataLoadByHandle(field_3d_anime_ptr->AnmInfoHandle, inObjCode, &info);

	//アニメしないものの数は0
	if (!info.Flg){
		return 0;
	}
		
	for(n=0;n<ONE_MODEL_ANM_NUM_MAX;n++){
		if (info.Code[n] == ANIME_NONE_CODE){
			break;
		}
	}
	return n;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//==============================================================================
/**
 * アニメーションエントリー
 *
 * @param	inAnimeContMng	アニメーション管理マネージャへのポインタ
 * @param	inEntryID		登録ID
 *
 * @return	ANIME_CONT_PTR	アニメ管理データポインタ
 */
//==============================================================================
static ANIME_CONT_PTR EntryAnimeCont(ANIME_CONT_MNG_PTR inAnimeContMng, const u8 inEntryID)
{	
	u8 i;
	u8 idx;
	ANIME_CONT_PTR	data;
	
	data = NULL;
	
	GF_ASSERT(inEntryID!=NO_ENTRY&&"ID=0は指定できません");
	idx = ANIME_CONT_MAX;
	//空いているところを検索しつつ、予約IDがすでにあるかを探す
	for(i=0;i<ANIME_CONT_MAX;i++){
#ifdef PM_DEBUG		
		if (inAnimeContMng->AnimeCont[i].EntryID == inEntryID ){
			OS_Printf("ID=%d:指定されたIDは登録済みです\n",inEntryID);
			GF_ASSERT(0);
		}
#endif		
		if ( (idx == ANIME_CONT_MAX)&&
			 (inAnimeContMng->AnimeCont[i].EntryID)==NO_ENTRY  ){
			idx = i;
		}
	}

	if (idx != ANIME_CONT_MAX){
		inAnimeContMng->AnimeCont[idx].EntryID = inEntryID;
	}else{
		GF_ASSERT_MSG(0,"idx == ANIME_CONT_MAX");
		return NULL;
	}
	
	return &(inAnimeContMng->AnimeCont[idx]);
}

//==============================================================================
/**
 *	エントリークリア
 * 
 * @param	outData	アニメ管理データポインタ
 *
 * @return	none
 */
//==============================================================================
static void EntryClearAnimeCont(ANIME_CONT_PTR outData)
{
	u8 i;
	outData->EntryID = NO_ENTRY;
	outData->ObjID = 0;
	outData->BindAnime = NULL;
	for(i=0;i<CONT_RENDER_OBJ_MAX;i++){
		outData->RenderObj[i] = NULL;
	}
}

//==============================================================================
/**
 *	登録IDでアニメ管理データを取得
 * 
 * @param	inAnimeContMng	アニメーション管理マネージャへのポインタ
 * @param	inEntryID		エントリーＩＤ
 *
 * @return	アニメ管理データポインタ
 */
//==============================================================================
static ANIME_CONT_PTR GetAnmContPtrFromEntryID(	ANIME_CONT_MNG_PTR inAnimeContMng,
												const int inEntryID)
{
	int i;
	ANIME_CONT_PTR data;
	data = NULL;
	//予約されている場所を検索
	for(i=0;i<ANIME_CONT_MAX;i++){
		if (inAnimeContMng->AnimeCont[i].EntryID == inEntryID){
			data = &(inAnimeContMng->AnimeCont[i]);
			break;
		}
	}
#ifdef PM_DEBUG
	if (i==ANIME_CONT_MAX){
		OS_Printf("%d:指定された登録IDを持つアニメーションを取得できませんでした",inEntryID);
		GF_ASSERT(0);
	}
#endif
	return data;
}

//==============================================================================
/**
 *	登録IDでアニメ管理データを取得
 * 
 * @param	*pRenderObj		レンダーＯＢＪ
 * @param	inNum			アニメ数
 * @param	outData			アニメ管理データポインタ
 *
 * @return	none
 */
//==============================================================================
static void SetAnimeCont(	NNSG3dRenderObj *pRenderObj,
							const int inNum,
							ANIME_CONT_PTR	outData	)
{
	GF_ASSERT(inNum<=ONE_MODEL_ANM_NUM_MAX&&"1つのモデルが持てるアニメ数をオーバーしてます");
	if (pRenderObj != NULL){
		outData->RenderObj[0] = pRenderObj;	//レンダーＯＢＪの指定がある場合は0番目に登録する
	}
	outData->AnimeList.AnimeNum = inNum;
}

//==============================================================================
/**
 *	アニメデータセット
 * 
 * @param	inAnimeContPtr	アニメ管理データポインタ
 * @param	inIndex			インデックス
 * @param	inAnimePtr		アニメデータへのポインタ
 *
 * @return	none
 */
//==============================================================================
static void SetAnimePtr(ANIME_CONT_PTR inAnimeContPtr,
						const int inIndex,
						FLD_3D_ANM_DAT_PTR inAnimePtr)
{
	GF_ASSERT(inIndex<inAnimeContPtr->AnimeList.AnimeNum&&"インデックスがオーバーしてます");
	inAnimeContPtr->AnimeList.Data[inIndex] = inAnimePtr;
}

//==============================================================================
/**
 *	アニメデータ取得
 * 
 * @param	inAnimeContPtr	アニメ管理データポインタ
 * @param	inIndex			インデックス
 *
 * @return	FLD_3D_ANM_DAT_PTR	アニメデータポインタ
 */
//==============================================================================
static FLD_3D_ANM_DAT_PTR GetAnimePtr(ANIME_CONT_PTR inAnimeContPtr, const int inIndex)
{
	GF_ASSERT(inIndex<inAnimeContPtr->AnimeList.AnimeNum&&"インデックスがオーバーしてます");
	return inAnimeContPtr->AnimeList.Data[inIndex];
}

//==============================================================================
/**
 *	アニメバインド
 * 
 * @param	ioAnimeContPtr	アニメ管理データポインタ
 * @param	inIndex			インデックス
 *
 */
//==============================================================================
static FLD_3D_ANM_DAT_PTR BindAnimation(ANIME_CONT_PTR ioAnimeContPtr, const int inIndex)
{
	u8 i;
	FLD_3D_ANM_DAT_PTR anime;
	NNSG3dAnmObj *anm_obj;
	NNSG3dAnmObj *bind_anmobj;
	GF_ASSERT(inIndex<ioAnimeContPtr->AnimeList.AnimeNum&&"インデックスがオーバーしてます");
	anime = ioAnimeContPtr->AnimeList.Data[inIndex];
	anm_obj = GetAnmObj(anime);

	bind_anmobj = GetAnmObj(ioAnimeContPtr->BindAnime);
	for(i=0;i<CONT_RENDER_OBJ_MAX;i++){
		if (ioAnimeContPtr->RenderObj[i] != NULL){
			//すでにアニメがついている場合はリムーブする
			RemoveAnime(ioAnimeContPtr->RenderObj[i], bind_anmobj);
			// RenderObj に AnmObj を追加する。ジョイントアニメーション以外も同様
			NNS_G3dRenderObjAddAnmObj(ioAnimeContPtr->RenderObj[i], anm_obj );
		}
	}
	ioAnimeContPtr->BindAnime = anime;
	return anime;
}

//非常駐アニメのみ対応
static void AddField3DAnime(const int inObjID,
							NNSG3dResMdl 	*inObjectModel,
							NNSG3dResTex *inTex,
							const int inAnimeNum,
							const int inLoopCount,
							const BOOL	inReverse,
							FLD_3D_ANM_MNG_PTR field_3d_anime_ptr,
							ANIME_CONT_PTR outData)
{
	FLD_3D_ANM_DAT_PTR	anm_data;
	int i;
	for(i=0;i<inAnimeNum;i++){
		anm_data = F3DA_AddField3DAnime(inObjID,
										i,
										inLoopCount,
										0,		//外部制御しない
										inReverse,	//向き
										TRUE,	//始めは停止
										TRUE,	//条件付
										inObjectModel,
										inTex,
										field_3d_anime_ptr);
		GF_ASSERT(anm_data!=NULL&&"登録失敗");

		//アニメ管理リストに登録したアニメポインタを取得しておく
		SetAnimePtr( outData, i, anm_data);	//アニメ登録
	}
}

static void RereaseField3DAnime(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr,
								ANIME_CONT_PTR outData)
{
	int i;
	NNSG3dAnmObj *anmobj;
	anmobj = GetAnmObj(outData->BindAnime);
	//すでにアニメがついている場合はリムーブする
	for(i=0;i<CONT_RENDER_OBJ_MAX;i++){
		if (outData->RenderObj[i] != NULL){
			RemoveAnime(outData->RenderObj[i], anmobj);
		}
	}
	for (i=0;i<outData->AnimeList.AnimeNum;i++){
		{		
			FLD_3D_ANM_DAT_PTR anime;
			anime = outData->AnimeList.Data[i];	
			F3DA_RereaseFld3DAnime(anime, field_3d_anime_ptr);
		}
		outData->AnimeList.Data[i] = NULL;
	}
}

//3Dアニメマネージャのメモリアロケーション
ANIME_CONT_MNG_PTR F3DASub_InitField3DAnimeCont(void)
{
	int i;
	int size;
	ANIME_CONT_MNG_PTR anime_cont_mng;

	size = sizeof(ANIME_CONT_MNG);

	anime_cont_mng = sys_AllocMemory( HEAPID_FIELD, size );

	MI_CpuClearFast(anime_cont_mng,size);

	return anime_cont_mng;
}

//3Dアニメマネージャの解放
void F3DASub_FreeAnimeContManager(ANIME_CONT_MNG_PTR *outAnimeContMng)
{
	if ((*outAnimeContMng)==NULL) return;

#ifdef	PM_DEBUG
	{
		int i;
		for(i=0;i<ANIME_CONT_MAX;i++){
			if ((*outAnimeContMng)->AnimeCont[i].EntryID != NO_ENTRY ){
				OS_Printf("EntryID:%d 登録の解除がされないまま解放しようとしています\n",
						(*outAnimeContMng)->AnimeCont[i].EntryID);
				GF_ASSERT(0);
			}
		}
	}
#endif
	
	sys_FreeMemoryEz( (*outAnimeContMng) );
	(*outAnimeContMng) = NULL;
}


//アニメーションセットアップ
void F3DASub_SetUpAnimation(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr,
							const ANIME_CONT_MNG_PTR inAnimeContMng,
							const int inEntryID,
							const int inObjID,
							NNSG3dRenderObj *inRenderObj,
							NNSG3dResMdl 	*inObjectModel,
							NNSG3dResTex *inTex,
							const int inAnimeNum,
							const u8 inLoop,
							const BOOL inReverse)
{
	int i;
	u8 loop;
	ANIME_CONT_PTR		cont_data = NULL;
	//アニメエントリー
	cont_data = EntryAnimeCont(inAnimeContMng, inEntryID);
	if (!cont_data){
		GF_ASSERT_MSG(0,"FAIL_ANIME_ENTRY");
		return ;
	}

	//使用するアニメ数分管理用アニメポインタリストを確保
	SetAnimeCont(inRenderObj, inAnimeNum, cont_data);
	loop = inLoop;
	GF_ASSERT(loop != 0);
	if (loop == 0){
		loop = 1;	//0セット防止
	}
	
	//アニメーションの追加
	AddField3DAnime(inObjID, inObjectModel, inTex, inAnimeNum, loop, inReverse,
					field_3d_anime_ptr, cont_data);
	//OBJID記憶(ほぼサウンド用)
	cont_data->ObjID = inObjID;
}

//レンダーＯＢＪのエントリー
//同じアニメを複数のＯＢＪが使う場合に使用
//F3DASub_SetUpAnimationでレンダーＯＢＪ指定しなかったときに
//後でこれを使ってエントリする
void F3DASub_EntryRenderObj(const ANIME_CONT_MNG_PTR inAnimeContMng,
							const int inEntryID,
							const u8 inEntryIndex,
							NNSG3dRenderObj *inRenderObj)
{
	ANIME_CONT_PTR cont_ptr;
	GF_ASSERT(inEntryIndex<CONT_RENDER_OBJ_MAX);
	cont_ptr = GetAnmContPtrFromEntryID( inAnimeContMng, inEntryID);
	GF_ASSERT_MSG((cont_ptr->RenderObj[inEntryIndex]==NULL),"レンダーOBJがすでにあります");
	cont_ptr->RenderObj[inEntryIndex] = inRenderObj;
}


//アニメ開始
void F3DASub_StartAnimation(const ANIME_CONT_MNG_PTR inAnimeContMng,
							const int inEntryID,
							const int inAnimeNo)
{
	ANIME_CONT_PTR cont_ptr;
	FLD_3D_ANM_DAT_PTR anime;
	GF_ASSERT_MSG((inEntryID!=NO_ENTRY),"ID=0は指定できません");
	cont_ptr = GetAnmContPtrFromEntryID(inAnimeContMng, inEntryID);

	anime = BindAnimation(cont_ptr, inAnimeNo);	//アニメをバインド
	//アニメーションをスタート
	F3DA_SetStopFlg(anime, FALSE);
}

//アニメ開始(音つき)
void F3DASub_StartAnimeSnd(const ANIME_CONT_MNG_PTR inAnimeContMng,
							const int inEntryID,
							const int inAnimeNo,
							const int inSound)
{
	ANIME_CONT_PTR cont_ptr;
	FLD_3D_ANM_DAT_PTR anime;
	GF_ASSERT(inEntryID!=NO_ENTRY&&"ID=0は指定できません");
	cont_ptr = GetAnmContPtrFromEntryID(inAnimeContMng, inEntryID);

	anime = BindAnimation(cont_ptr, inAnimeNo);	//アニメをバインド

	//自動ドア閉じる音以外だったらSE再生
	if( inSound != SE_JIDO_DOOR_CLOSE ){
		Snd_SePlay(inSound);
	}

	//アニメーションをスタート
	F3DA_SetStopFlg(anime, FALSE);
}

//アニメバインド
void F3DASub_BindAnimation( const ANIME_CONT_MNG_PTR inAnimeContMng,
							const int inEntryID,
							const int inAnimeNo)
{
	ANIME_CONT_PTR cont_ptr;
	FLD_3D_ANM_DAT_PTR anime;
	GF_ASSERT(inEntryID!=NO_ENTRY&&"ID=0は指定できません");
	cont_ptr = GetAnmContPtrFromEntryID(inAnimeContMng, inEntryID);

	anime = BindAnimation(cont_ptr, inAnimeNo);	//アニメをバインド
}

//アニメストップフラグオンオフ
void F3DASub_SetStopFlg( const ANIME_CONT_MNG_PTR inAnimeContMng,
							const int inEntryID,
							const int inAnimeNo,
							const BOOL inFlg)
{
	ANIME_CONT_PTR cont_ptr;
	FLD_3D_ANM_DAT_PTR anime;
	GF_ASSERT(inEntryID!=NO_ENTRY&&"ID=0は指定できません");
	cont_ptr = GetAnmContPtrFromEntryID(inAnimeContMng, inEntryID);

	anime = BindAnimation(cont_ptr, inAnimeNo);	//アニメをバインド
	//アニメーションをスタート
	F3DA_SetStopFlg(anime, inFlg);
}

//解放処理
void F3DASub_RereaseAnimation(	FLD_3D_ANM_MNG_PTR field_3d_anime_ptr,
								ANIME_CONT_MNG_PTR inAnimeContMng,
								const int inEntryID)
{
	ANIME_CONT_PTR data;
	GF_ASSERT(inEntryID!=NO_ENTRY&&"ID=0は指定できません");
	data = GetAnmContPtrFromEntryID(inAnimeContMng, inEntryID);
	//アニメーションの解放
	RereaseField3DAnime(field_3d_anime_ptr, data);
	//エントリークリア
	EntryClearAnimeCont(data);
}

//アニメ取得
FLD_3D_ANM_DAT_PTR F3DASub_GetFld3DAnmPtr(	const ANIME_CONT_MNG_PTR inAnimeContMng,
											const int inEntryID,
											const int inAnimeNo	)
{
	ANIME_CONT_PTR cont_data;
	FLD_3D_ANM_DAT_PTR anime;
	GF_ASSERT(inEntryID!=NO_ENTRY&&"ID=0は指定できません");
	cont_data =  GetAnmContPtrFromEntryID(inAnimeContMng, inEntryID);
	anime = GetAnimePtr(cont_data, inAnimeNo);
	return anime;
}

//現在バインドされているアニメを取得
FLD_3D_ANM_DAT_PTR F3DASub_GetFld3DBindAnmPtr(	const ANIME_CONT_MNG_PTR inAnimeContMng,
												const int inEntryID	)
{
	ANIME_CONT_PTR cont_data;
	FLD_3D_ANM_DAT_PTR anime;
	GF_ASSERT(inEntryID!=NO_ENTRY&&"ID=0は指定できません");
	cont_data =  GetAnmContPtrFromEntryID(inAnimeContMng, inEntryID);
	anime = cont_data->BindAnime;
	return anime;
}

//アニメーション終了待ち
const BOOL F3DASub_WaitAnimation(	const ANIME_CONT_MNG_PTR inAnimeContMng,
									const int inEntryID	)
{
	FLD_3D_ANM_DAT_PTR data;
	data = F3DASub_GetFld3DBindAnmPtr(inAnimeContMng, inEntryID);

	GF_ASSERT_MSG((data!=NULL),"アニメがバインドされていない");
	
	if ( F3DA_IsAnimeEnd(data) ){
		return TRUE;
	}else{
		return FALSE;
	}
}

const int F3DASub_GetObjIDFromEntryID(	const ANIME_CONT_MNG_PTR inAnimeContMng,
										const int inEntryID)
{
	ANIME_CONT_PTR cont_ptr;
	cont_ptr = GetAnmContPtrFromEntryID(inAnimeContMng, inEntryID);
	return cont_ptr->ObjID;
}
