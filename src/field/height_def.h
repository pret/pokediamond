#ifndef _HEIGHT_DEF_H_
#define _HEIGHT_DEF_H_

#include "system/arc_tool.h"

typedef struct MAP_HEIGHT_INFO_tag * MHI_PTR;
typedef struct MAP_HEIGHT_INFO_tag const * MHI_CONST_PTR;

typedef struct EX_HEIGHT_LIST_tag * EHL_PTR;
typedef struct EX_HEIGHT_LIST_tag const * EHL_CONST_PTR;

//メモリ確保
extern MHI_PTR	AllocMapHeightInfo(void);

//ロード関連
extern void SetupHeightData(const char  *path,
							MHI_PTR	outMapHeightInfo,
							u8 *inHeightMem);
extern void SetupHeightDataArc(	ARCHANDLE *ioHandle,
								const int inDataSize,
								MHI_PTR outMapHeightInfo, u8 * inHeightMem );
extern void FreeMapHeightInfo(MHI_PTR	outMapHeightInfo);
/*
extern TCB_PTR SetupHeightDataTask(const char  *path, 
		MHI_PTR	ioMapHeightInfo,
		int *inEndFlg,
		u8 **inHeightMem);
*/
extern TCB_PTR SetupHeightDataArcTask(	ARCHANDLE *inHandle,
										const int DataSize,
										MHI_PTR ioMap3DInfo,
										int *inEndFlg,
										u8 **inHeightMem,
										int *inStartFlg);
extern void StopHeightLoadTaskRequest(TCB_PTR tcb);
extern void InitHeightData(MHI_PTR outData);

extern VecFx32 MoveRevise(fx32 inMoveVal, VecFx32 inNewVec, VecFx32 inOldVec);

extern void SetInvalidHeightData(MHI_PTR outMap3DInfo);

//高さ取得
extern BOOL GetHeightForBlock(	const fx32 inNowY, const fx32 inX, const fx32 inZ,
								MHI_CONST_PTR inMap3DInfo,fx32 *outY);

extern BOOL GetInvalidHeightDataFlg(MHI_CONST_PTR inMap3DInfo);

//--------------------------------------------------------------------------------------------
/**
 * 拡張高さデータのメモリアロケート
 *
 * @param	inNum		確保するデータ個数
 * @param	inHeapID	確保するヒープID
 *
 * @return	EHL_PTR	確保した領域の先頭ポインタ
 */
//--------------------------------------------------------------------------------------------
extern EHL_PTR EXH_AllocExHeightList(const u8 inNum, const u8 inHeapID);

//--------------------------------------------------------------------------------------------
/**
 * 拡張高さデータのセットアップ
 *
 * @param	inIndex		取得する高さデータのインデックス
 * @param	inStX			領域開始グリッドX座標
 * @param	instZ			領域開始グリッドZ座標
 * @param	inSizX			領域グリッド横幅
 * @param	inSizZ			領域グリッド縦幅
 * @param	inHeight		領域内高さ
 * @param	outExHeightList	拡張高さデータへのポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void EXH_SetUpExHeightData(	const u8 inIndex,
									const int inStX,
									const int inStZ,
									const int inSizX,
									const int inSizZ,
									const fx32 inHeight,
									EHL_PTR outExHeightList );

//--------------------------------------------------------------------------------------------
/**
 * 拡張高さデータ解放
 *
 * @param	outExHeightData	拡張高さデータの先頭ポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void EXH_FreeExHeightList(EHL_PTR outExHeightList);

//--------------------------------------------------------------------------------------------
/**
 * 拡張高さデータのヒットチェック
 *
 * @param	inGridX			チェックするグリッドX座標
 * @param	inGridZ			チェックするグリッドZ座標
 * @param	inExHeightList	拡張高さデータへのポインタ
 *
 * @return	BOOL	TRUE:ヒット	FALSE:ノーヒット
 */
//--------------------------------------------------------------------------------------------
extern BOOL EXH_HitCheckExHeight(	const int inGridX, const int inGridZ,
									EHL_CONST_PTR inExHeightList,
									u8 *outIndex);

//--------------------------------------------------------------------------------------------
/**
 * 拡張高さデータから高さを取得(リスト)
 *
 * @param	inIndex	拡張高さデータインデックス
 * @param	inExHeightList	拡張高さデータへのポインタ
 *
 * @return	fx32	高さ
 */
//--------------------------------------------------------------------------------------------
extern fx32 EXH_GetExHeight(const u8 inIndex, EHL_CONST_PTR inExHeightList);

//--------------------------------------------------------------------------------------------
/**
 * 拡張高さデータの高さセット(リスト)
 *
 * @param	inIndex	拡張高さデータインデックス
 * @param	inHeight		領域内高さ
 * @param	outExHeightList	拡張高さデータへのポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void EXH_SetExHeight(	const u8 inIndex, const fx32 inHeight, EHL_PTR outExHeightList );

//--------------------------------------------------------------------------------------------
/**
 * 拡張高さデータの有効・無効化(リスト)
 *
 * @param	inIndex	拡張高さデータインデックス
 * @param	inValid			TRUE:有効	FALSE:無効
 * @param	outExHeightData	拡張高さデータへのポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void EXH_SetExHeightValid(	const u8 inIndex, const BOOL inValid, EHL_PTR outExHeightList );

#endif //_HEIGHT_DEF_H_
