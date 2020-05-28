/**
 *	@file	mdlanm.c
 *	@brief	汎用3Dモデルアニメーションリソース管理補助ライブラリ
 *	@author	Miyuki Iwasawa
 *	@date	05.11.09
 */

#include "common.h"
#include "gflib/heapsys.h"
#include "gflib/mdlanm.h"

//プロトタイプ
static void* SMAnm_LoadAnmFile(MDLANM_DATA* pData,const char* path,int heapID);

/**
 *	@brief	モデルアニメマネージャ初期化
 *
 *	@param	num	s16:確保したいアニメデータ構造体の数
 *	@param	heapID	int:使用するヒープのID
 
 *	@return	MDLANM_MAN*:確保したMDLANM_MAN構造体データへのポインタ
 */
MDLANM_MAN* MAnm_Init(s16 num,int heapID) 
{
	MDLANM_MAN* wk = NULL;
	u16	i;

	wk = sys_AllocMemory(heapID,sizeof(MDLANM_MAN));
	if(wk == NULL){
		return NULL;
	}
	memset(wk,0,sizeof(MDLANM_MAN));

	wk->dat_num = num;
	wk->heapID = heapID;
	wk->pData = sys_AllocMemory(heapID,sizeof(MDLANM_DATA)*wk->dat_num);
	if(wk->pData == NULL){
		sys_FreeMemoryEz(wk);
		return NULL;
	}

	//データ領域初期化
	for(i = 0;i < wk->dat_num;i++){
		MAnm_ClearData(&wk->pData[i]);
	}
	
	//アロケータ初期化
	sys_InitAllocator(&wk->allocator,heapID,4);

	return wk;
}

/**
 *	@brief	モデルアニメマネージャエリア解放
 *	@param	wk	MDLANM_MAN*:各モジュールで用意したMDLANM_MAN構造体データへのポインタ
 */
void MAnm_End(MDLANM_MAN* wk) 
{
	s16	i;

	for(i = 0;i < wk->dat_num;i++){
		if(!wk->pData[i].valid){
			continue;
		}
		MAnm_ReleaseAnmData(&(wk->pData[i]),&(wk->allocator));
	}
	sys_FreeMemoryEz(wk->pData);
	sys_FreeMemoryEz(wk);
}

/**
 *	@brief	3Dモデルアニメ　メインコントローラ
 *
 *	@param	wk	MDLANM_MAN*　マネージャへのポインタ
 *
 *	メインシーケンス内で呼び出してください	
 */
void MAnm_AnimeMain(MDLANM_MAN* wk)
{
	s16	i = 0;
	MDLANM_DATA* wp;
	if(wk == NULL){
		return;
	}

	for(i = 0;i < wk->dat_num;i++){
		wp = &wk->pData[i];
		if(wp->valid == 0 || wp->end_f == 1 || wp->stop_f == 1){
			continue;
		}
		if(wp->type == AMTYPE_SELF){
			continue;
		}
		wp->pAnmObj->frame = FX32_CONST(wp->frame++);

		if(wp->frame < wp->frm_max){
			continue;
		}
		if(wp->roop_f){
			wp->frame = 0;
		}else{
			wp->end_f = 1;
		}
	}
}

/**
 *	@brief	モデルアニメ配列から空きデータNOを返す
 *	@param	wk	MDLANM_MAN*:各モジュールで用意したMDLANM_MAN構造体データへのポインタ
 *
 *	@retval	MDLANM_DATA_NULL:-1	空きがない
 *	@retval	それ以外:配列のインデックスNO
 *
 */
s16	MAnm_SearchNullDataNo(MDLANM_MAN* wk)
{
	s16	i;

	if(wk->pData == NULL){
		return MDLANM_DATA_NULL;
	}
	for(i = 0;i < wk->dat_num;i++){
		if(!wk->pData[i].valid){
			return i;
		}
	}
	return MDLANM_DATA_NULL;
}
/**
 *	@brief	IDから配列のアドレスを返す
 *	@param	wk	MDLANM_MAN*:各モジュールで用意したMDLANM_MAN構造体データへのポインタ
 *
 *	@retval	NULL	見つからない
 *	@retval	MDLANM_DATA* 構造体アドレス
 *
 */
MDLANM_DATA* MAnm_SearchDataByID(MDLANM_MAN* wk,s16 no)
{
	s16	i;

	if(wk == NULL || wk->pData == NULL){
		return NULL;
	}
	if(no >= wk->dat_num){
		return NULL;
	}
	for(i = 0;i < wk->dat_num;i++){
		if(wk->pData[i].no == no){
			return &(wk->pData[i]);
		}
	}
	return NULL;
}

/**
 *	@brief	モデルアニメデータ構造体クリア
 *
 *	@param	pData	クリアしたいMDLANM_DATA型構造体データへのポインタ
 */
void MAnm_ClearData(MDLANM_DATA* pData)
{
	pData->no = -1;
	pData->type = 0;
	pData->frame = 0;
	pData->connect = 0;
	pData->valid = 0;
	pData->stop_f = 0;
	pData->end_f = 0;
	pData->pAnmObj = NULL;
	pData->pFile = NULL;
}

/**
 *	@brief	モデルアニメ追加
 *	@param	wk	MDLANM_MAN*:各モジュールで用意したMDLANM_MAN構造体データへのポインタ
 *	@param	inName	アニメデータファイル名
 *	@param	inType	アニメーションタイプ
 *	@param	pModel	関連付けるモデルリソース
 */
MDLANM_DATA* MAnm_AddAnime(MDLANM_MAN* wk,const char* inName,const u8 inType,
		NNSG3dResMdl* pModel,NNSG3dResTex* pTex)
{
	s16 ret = 0;
	void*	anmRes = NULL;
	MDLANM_DATA* wp = NULL;
	
	ret = MAnm_SearchNullDataNo(wk);
	if(ret == MDLANM_DATA_NULL){
		return NULL;	//空きがないので追加できない
	}
	
	wp = &wk->pData[ret];	//ポインタ取得
	MAnm_ClearData(wp);	//一旦クリア

	//ファイルロード
	anmRes = SMAnm_LoadAnmFile(wp,inName,wk->heapID);
	GF_ASSERT((anmRes != NULL) && "model anime file load failed");

	// 必要量のメモリをアロケートする。イニシャライズは別途必要になる。
    wp->pAnmObj = NNS_G3dAllocAnmObj(&(wk->allocator),	// 使用するアロケータを指定
                                     wp->pAnmRes,	// アニメーションリソースを指定
                                     pModel);		// モデルリソースを指定
	SDK_NULL_ASSERT(wp->pAnmObj);

	// AnmObj を初期化する。ジョイントアニメーション以外も同様
	//
	NNS_G3dAnmObjInit(	wp->pAnmObj, // アニメーションオブジェクトへのポインタ
						wp->pAnmRes, // アニメリソースへのポインタ
						pModel,  // NNSG3dResMdlへのポインタ
                        pTex);  // NNSG3dResTexへのポインタ(テクスチャパターンアニメ以外ならばNULLでもよい)

	wp->frm_max =  (NNS_G3dAnmObjGetNumFrame(wp->pAnmObj) >> FX32_SHIFT);
	wp->type = inType;
	if(wp->type == AMTYPE_AUTOLOOP){
		wp->roop_f = 1;
	}
	//有効にする
	wp->valid = 1;
	wp->no = ret;
	return wp;
}

/**
 *	@brief	MDLANM_DATA構造体のリソースを解放
 *	@param	pData	MDLANM_DATA*　アニメデータ構造体へのポインタ
 *	@param	allocator	NNSFncAllocator*　マネージャのアロケータ
 *
 *	@retval	TRUE	解放成功
 *	@retval FLASE	解放失敗
 */
BOOL MAnm_ReleaseAnmData(MDLANM_DATA* pData,NNSFndAllocator* allocator)
{
	if(pData->connect  != 0){
		//このアニメがコネクトされているオブジェがいるので解放するべきではない
		GF_ASSERT("3Dモデルアニメーションがコネクトされたままです\n");
//		return FALSE;
	}
	
	//アニメオブジェリソース解放
	NNS_G3dFreeAnmObj(allocator,pData->pAnmObj);
	//ファイルリソース解放
	sys_FreeMemoryEz(pData->pFile);

	//データエリアクリア
	MAnm_ClearData(pData);

	return TRUE;
}

/**
 *	@brief	モデルアニメ解放(IndexNo ver) 
 *	@param	wk	MDLANM_MAN*:各モジュールで用意したMDLANM_MAN構造体データへのポインタ
 *	@param	no	解放したいアニメデータのIndexNo
 *
 *	@retval	1	解放成功
 *	@retval 0	解放失敗(解放するべきものが見つからない)
 */
BOOL MAnm_ReleaseAnimeByID(MDLANM_MAN* wk,s16 no)
{
	MDLANM_DATA* wp;
	
	wp = MAnm_SearchDataByID(wk,no);
	if(wp == NULL){
		return FALSE;	//見つからない
	}
	return MAnm_ReleaseAnmData(wp,&(wk->allocator));
}

/**
 *	@brief	アニメデータコネクト(アドレスVer)
 *
 *	@param	pData	MDLANM_DATA*
 *	@param	render	NNSG3dRenderObjへのポインタ
 *
 *	@retval	TRUE	成功
 *	@retval FALSE	失敗
 */
BOOL MAnm_ConnectAnimeByAdrs(MDLANM_DATA* pData,NNSG3dRenderObj* render)
{
	if(pData == NULL || render == NULL){
		return FALSE;
	}
	if(pData->valid == 0){
		return FALSE;
	}
	NNS_G3dRenderObjAddAnmObj(render,pData->pAnmObj);
	pData->connect++;
	return TRUE;
}

/**
 *	@brief	アニメデータディスコネクト(アドレスVer)
 *
 *	@param	pData	MDLANM_DATA*
 *	@param	render	NNSG3dRenderObjへのポインタ
 *
 *	@retval	TRUE	成功
 *	@retval FALSE	失敗
 */
BOOL MAnm_DisconnectAnimeByAdrs(MDLANM_DATA* pData,NNSG3dRenderObj* render)
{
	if(pData == NULL || render == NULL){
		return FALSE;
	}
	if(pData->valid == 0){
		return FALSE;
	}
	NNS_G3dRenderObjRemoveAnmObj(render,pData->pAnmObj);
	pData->connect--;
	return TRUE;
}

/**
 *	@brief	アニメデータ フレームNoセット(アドレスVer)
 *
 *	@param	pData	MDLANM_DATA*
 *	@param	no		アニメフレームNo	
 *
 *	@retval	TRUE	成功
 *	@retval FALSE	失敗
 */
BOOL MAnm_SetAnimeFrameByAdrs(MDLANM_DATA* pData,u16 no)
{
	if(no > pData->frm_max){
		no = 0;
	}
	pData->frame = no;
	pData->pAnmObj->frame = FX32_CONST(pData->frame);

	return TRUE;
}

/**
 *	@brief	モデルアニメ　ファイルロード
 *
 *	@param	MDLANM_DATA*	pData	アニメを登録する構造体アドレス
 *	@param	const char*		path	ファイルパス
 *	@param	NNSFndAllocator*	allocator	アロケータポインタ
 *	@param	heapID	使用するヒープID
 *
 *	@return 取得したアニメリソースへのポインタ
 */
static void* SMAnm_LoadAnmFile(MDLANM_DATA* pData,const char* path,int heapID)
{
	void* pAnmRes = NULL;

	if(path == NULL){
		return NULL;
	}

	pData->pFile = sys_LoadFile(heapID,path);	
	if(pData->pFile == NULL){
		return NULL;
	}

	//リソース取得
	pData->pAnmRes = NNS_G3dGetAnmByIdx(pData->pFile,0);
	if(pData->pAnmRes == NULL){
		return NULL;
	}
	
	return pData->pAnmRes;
}
