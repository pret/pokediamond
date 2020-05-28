/**
 *	@file	poruto_util.h
 *	@brief	ポルトデータ　アクセス系関数定義ファイル
 *	@author	Miyuki Iwasawa
 *	@date	06.02.28
 *
 *	＊実データ参照が不要の場所では、このヘッダに定義された
 *	　アクセス関数を通してデータを扱う
 */

#ifndef __H_PORUTO_UTIL_H__
#define __H_PORUTO_UTIL_H__

#include "savedata/savedata_def.h"
#include "savedata/poruto_def.h"

//------------------------------------------------------------
/**
 * @brief	ポルトセーブデータブロック管理構造への不完全型ポインタ
 *
 * 中身は見えないけどポインタ経由で参照はできる
 */
//------------------------------------------------------------
typedef struct _PORUTO_BLOCK PORUTO_BLOCK;

//------------------------------------------------------------
/**
 * @brief	ポルトデータ管理構造への不完全型ポインタ
 *
 * 中身は見えないけどポインタ経由で参照はできる
 */
//------------------------------------------------------------
typedef struct _PORUTO_DATA PORUTO_DATA;


/**
 *	@brief	セーブデータブロックへのポインタを取得
 */
extern PORUTO_BLOCK* SaveData_GetPorutoBlock(SAVEDATA* sv);

/**
 *	@brief	ポルトセーブデータサイズ取得
 */
extern int PORUTO_GetSaveWorkSize(void);

/**
 *	@brief	ポルトデータ配列初期化
 */
extern void PORUTO_Init(PORUTO_BLOCK* dat);

/**
 *	@brief	ポルトセーブデータの空き領域を探す
 *
 *	@retval	PORUTO_DATA_NULL	空き領域がない
 *	@retval "その他"			空き領域のIndexNo
 */
extern u16 PORUTO_SearchNullData(PORUTO_BLOCK* block);

/**
 *	@brief	ポルトデータをセーブデータ空き領域に追加する
 *
 *	@retval	PORUTO_DATA_NULL	空き領域がなくて追加できなかった
 *	@retval "その他"			追加した領域のindex
 */
extern u16 PORUTO_AddData(PORUTO_BLOCK* block,PORUTO_DATA* dat);

/**
 *	@brief	ポルトデータをセーブデータから削除する(index指定)
 *
 */
extern BOOL PORUTO_DelData(PORUTO_BLOCK* block,u16 idx);

/**
 *	@brief	ポルトセーブデータを整理する
 *
 *	＊データ配列の穴空きを詰める
 */
extern void PORUTO_DataAdjust(PORUTO_BLOCK* block);

/**
 *	@brief	セーブデータ領域にある有効なポルトデータ数を返す
 */
extern u16	PORUTO_GetDataNum(PORUTO_BLOCK* block);

/**
 *	@brief	ポルトデータをセーブデータから取得する(index指定)
 *
 *	＊引き渡されたPORUTO_DATA構造体型領域へ、セーブデータをコピーして返す
 */
extern void PORUTO_GetData(PORUTO_BLOCK* block,u16 idx,PORUTO_DATA* dest);

/**
 *	@brief	ポルトデータをセーブデータから取得する(index指定/メモリ確保版)
 *
 *	＊PORUTO_DATA構造体型領域を確保し、セーブデータをコピーして返す
 *	　呼び出し側が明示的に解放すること！
 */
extern PORUTO_DATA* PORUTO_GetDataAlloc(PORUTO_BLOCK* block,u16 idx,int heapID);

//============================================================
/**
 *	ポルトデータアクセス系関数
 */
//============================================================
/**
 *	@brief	ポルトデータサイズ取得
 */
extern int PorutoData_GetWorkSize(void);

/**
 *	@brief	そのポルトデータが有効かどうか返す
 */
extern BOOL PorutoData_IsEnable(PORUTO_DATA* dat);

/**
 *	@brief	ポルトデータワーク作成
 */
extern PORUTO_DATA* PorutoData_AllocWork(int heapID);

/**
 *	@brief	ポルトデータクリア
 */
extern void PorutoData_Clear(PORUTO_DATA* dat);

/**
 *	@brief	ポルトデータコピー
 */
extern void PorutoData_Copy(PORUTO_DATA* src,PORUTO_DATA* dest);

/**
 *	@brief	ポルトのパラメータを取得
 *
 *	@param	dat
 *	@param	id	enum PORUTO_PARAID型(poruto_def.h参照)
 *
 *	@return	u8:取得したパラメータ
 */
extern u8 PorutoData_GetParam(PORUTO_DATA* dat,PORUTO_PARAID id);

/**
 *	@brief	ポルトのパラメータをセット
 *
 *	@param	dat
 *	@param	value	セットしたいデータ
 *	@param	id	enum PORUTO_PARAID型(poruto_def.h参照)
 *
 */
extern void PorutoData_SetParam(PORUTO_DATA* dat,u8 valid,PORUTO_PARAID id);

/**
 *	@brief	味と旨味からポルトの種類を決定し、パラメータをセットして返す
 *
 *	@param	dat	PORUTO_DATA*:パラメータをセットするポルトデータ型構造体
 *	@param	prm	u8[5]:5種類の味値を格納
 *	@param	taste	旨味値を格納
 *	@param	mazui	強制的に不味いポルトになるかどうか？ TRUEならまずいポルト
 *
 *	@return	PORUTO_FLAVORID	作成されたポルトのフレバーID
 */
extern PORUTO_FLAVORID PorutoData_CalcParam(PORUTO_DATA* dat,u8 *prm,u8 taste,BOOL mazui);

/**
 *	@brief	ポルトパラメータ取得(配列版)
 *
 *	＊呼び出し側でデータの取得場所を用意するバージョン
 *	　u8[PORUTO_PARAID_NUM] 分のメモリエリアが必要
 */
extern void PorutoData_GetParamArray(PORUTO_DATA* dat,u8* array);

/**
 *	@brief	ポルトパラメータ取得(配列,メモリ確保版)
 *
 *	＊関数内で必要なバッファを取得して返すバージョン
 *	　呼び出し側で明示的なメモリ解放が必要
 */
extern u8* PorutoData_GetParamArrayMem(PORUTO_DATA* dat,int heapID);

/**
 *	@brief	ポルトのレベルを取得
 */
extern u8 PorutoData_GetLevel(PORUTO_DATA* dat);




//デバッグ専用
#ifdef PM_DEBUG
/**
 *	@brief	ポルトデバッグ　データ全部消す
 */
extern void PorutoDebug_AllDataDelete(PORUTO_BLOCK* block);
/**
 *	@brief	ポルトデバッグ　テキトーなポルトを指定した数追加
 */
extern u16 PorutoDebug_AddRndData(PORUTO_BLOCK* block,u16 num);
#endif	//PM_DEBUG

#endif	//__H_PORUTO_UTIL_H__

