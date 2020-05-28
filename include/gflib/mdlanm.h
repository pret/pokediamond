/**
 *	@file	mdlanm.h
 *	@biref	汎用3Dモデルアニメーションリソース管理補助ライブラリ
 *	@author	Miyuki Iwasawa
 *	@date	05.11.09
 */

#ifndef _MODEL_ANIME_H_
#define _MODEL_ANIME_H_

typedef enum{
	AMTYPE_SELF,
	AMTYPE_AUTO,
	AMTYPE_AUTOLOOP,
}MDLANM_TYPE;

#define MDLANM_DATA_NULL	(-1)

typedef struct _MDLANM_DATA{
	s16	no;			///<No
	u16	type;		///<アニメタイプ
	u16	frame;		///<フレームNo
	u16	frm_max;	///<フレームの最大数

	u16	valid:1;	///<有効フラグ
	u16	stop_f:1;	///<アニメストップフラグ
	u16	end_f:1;	///<アニメ終了を検知するフラグ
	u16	roop_f:1;	///<ループ設定をするフラグ
	u16	dmy:4;		///<ダミー
	u16	connect:8;	///<アニメコネクトカウント

	NNSG3dAnmObj*	pAnmObj;	///<アニメオブジェ
	void*	pAnmRes;	///<アニメリソース
	void*	pFile;	///<アニメファイルリソース
}MDLANM_DATA;

typedef struct _MDLANN_MAN{
	int	dat_num;	///<データ数
	int	heapID;
	NNSFndAllocator	allocator;	///<アロケータ
	MDLANM_DATA*	pData;	///<データ格納ポインタ
}MDLANM_MAN;

typedef MDLANM_MAN*	GF_MDLANM_PTR;

/**
 *	@brief	モデルアニメマネージャ初期化
 *
 *	@param	num	s16:確保したいアニメデータ構造体の数
 *	@param	heapID	int:使用するヒープのID
 
 *	@return	MDLANM_MAN*:確保したMDLANM_MAN構造体データへのポインタ
 */
extern MDLANM_MAN* MAnm_Init(s16 num,int heapID);

/**
 *	@brief	モデルアニメマネージャエリア解放
 *	@param	wk	MDLANM_MAN*:各モジュールで用意したMDLANM_MAN構造体データへのポインタ
 */
extern void MAnm_End(MDLANM_MAN* wk);

/**
 *	@brief	3Dモデルアニメ　メインコントローラ
 *
 *	@param	wk	MDLANM_MAN*　マネージャへのポインタ
 *
 *	メインシーケンス内で呼び出してください	
 */
extern void MAnm_AnimeMain(MDLANM_MAN* wk);

/**
 *	@brief	モデルアニメ配列から空きデータNOを返す
 *	@param	wk	MDLANM_MAN*:各モジュールで用意したMDLANM_MAN構造体データへのポインタ
 *
 *	@retval	MDLANM_DATA_NULL:-1	空きがない
 *	@retval	それ以外:配列のインデックスNO
 */
extern s16	MAnm_SearchNullDataNo(MDLANM_MAN* wk);

/**
 *	@brief	IDから配列のアドレスを返す
 *	@param	wk	MDLANM_MAN*:各モジュールで用意したMDLANM_MAN構造体データへのポインタ
 *
 *	@retval	NULL	見つからない
 *	@retval	MDLANM_DATA* 構造体アドレス
 *
 */
extern MDLANM_DATA* MAnm_SearchDataByID(MDLANM_MAN* wk,s16 no);

/**
 *	@brief	モデルアニメデータ構造体クリア
 *
 *	@param	pData	クリアしたいMDLANM_DATA型構造体データへのポインタ
 */
extern void MAnm_ClearData(MDLANM_DATA* pData);

/**
 *	@brief	モデルアニメ追加
 *	@param	wk	MDLANM_MAN*:各モジュールで用意したMDLANM_MAN構造体データへのポインタ
 *	@param	inName	アニメデータファイル名
 *	@param	inType	アニメーションタイプ
 *	@param	pModel	関連付けるモデルリソース
 *	@param	pTex	関連付けるテクスチャリソース(パターンアニメ以外ならNULL指定可)
 *
 *	@retval	NULL			アニメ追加失敗
 *	@retval	MDLANM_DATA*	アニメデータ型構造体へのポインタ
 */
extern MDLANM_DATA* MAnm_AddAnime(MDLANM_MAN* wk,const char* inName,const u8 inType,
		NNSG3dResMdl* pModel,NNSG3dResTex* pTex);

/**
 *	@brief	MDLANM_DATA構造体のリソースを解放
 *	@param	pData	MDLANM_DATA*　アニメデータ構造体へのポインタ
 *	@param	allocator	NNSFncAllocator*　マネージャのアロケータ
 *
 *	@retval	TRUE	解放成功
 *	@retval FLASE	解放失敗
 */
extern BOOL MAnm_ReleaseAnmData(MDLANM_DATA* pData,NNSFndAllocator* allocator);

/**
 *	@brief	モデルアニメ解放(IndexNo ver) 
 *	@param	wk	MDLANM_MAN*:各モジュールで用意したMDLANM_MAN構造体データへのポインタ
 *	@param	no	解放したいアニメデータのIndexNo
 *
 *	@retval	1	解放成功
 *	@retval 0	解放失敗(解放するべきものが見つからない)
 */
extern BOOL MAnm_ReleaseAnimeByID(MDLANM_MAN* wk,s16 no);

/**
 *	@brief	アニメデータコネクト(アドレスVer)
 *
 *	@param	pData	MDLANM_DATA*
 *	@param	render	NNSG3dRenderObjへのポインタ
 *
 *	@retval	TRUE	成功
 *	@retval FALSE	失敗
 */
extern BOOL MAnm_ConnectAnimeByAdrs(MDLANM_DATA* pData,NNSG3dRenderObj* render);

/**
 *	@brief	アニメデータディスコネクト(アドレスVer)
 *
 *	@param	pData	MDLANM_DATA*
 *	@param	render	NNSG3dRenderObjへのポインタ
 *
 *	@retval	TRUE	成功
 *	@retval FALSE	失敗
 */
extern BOOL MAnm_DisconnectAnimeByAdrs(MDLANM_DATA* pData,NNSG3dRenderObj* render);

/**
 *	@brief	アニメデータ フレームNoセット(アドレスVer)
 *
 *	@param	pData	MDLANM_DATA*
 *	@param	no		アニメフレームNo	
 *
 *	@retval	TRUE	成功
 *	@retval FALSE	失敗
 */
extern BOOL MAnm_SetAnimeFrameByAdrs(MDLANM_DATA* pData,u16 no);












#endif	//_MODEL_ANIME_H_

