//==============================================================================================
/**
 * @file	opneing_obj.h
 * @brief	オープニング OBJ
 * @author	Satoshi Nohara
 * @date	2005.12.08
 */
//==============================================================================================
#ifndef _OPENING_OBJ_H_
#define _OPENING_OBJ_H_

#include "system/clact_tool.h"


//==============================================================================================
//
//	定義
//
//==============================================================================================
//CellActorに処理させるリソースマネージャの種類の数（＝マルチセル・マルチセルアニメは使用しない）
#define RESOURCE_NUM					(4)

#define OPENING_ACT_MAX					(3)

#define OPENING_ACT_START				(0)

//リソースマネージャーオブジェクトナンバー
enum{
	OP_RES_OBJ_HAKASE = 0,
	OP_RES_OBJ_RIVAL,

	OP_RES_OBJ_MAX,						//最大数
};


//==============================================================================================
//
//	構造体宣言
//
//==============================================================================================
typedef struct OPENING_OBJ_WORK_tag
{
	CLACT_SET_PTR 			ClactSet;						//セルアクターセット
	CLACT_U_EASYRENDER_DATA	RendData;						//簡易レンダーデータ
	CLACT_U_RES_MANAGER_PTR	ResMan[RESOURCE_NUM];			//リソースマネージャ

	CLACT_U_RES_OBJ_PTR 	ResObjTbl[2][RESOURCE_NUM];		//リソースオブジェテーブル(上下画面)

	CLACT_WORK_PTR			ClActWork[OPENING_ACT_MAX];		//セルアクターワークポインタ配列
}OPENING_OBJ_WORK;


//==============================================================================================
//
//	extern宣言
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	セルアクター初期化
 *
 * @param	wk		OPENING_OBJ_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
extern void OpeningInitCellActor( OPENING_OBJ_WORK *wk );

//--------------------------------------------------------------
/**
 * @brief	セルアクターをセット
 *
 * @param	wk		OPENING_OBJ_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
//extern void OpeningSetActor( OPENING_OBJ_WORK *wk );
extern void OpeningSetActor( OPENING_OBJ_WORK *wk, u32 index, u32 data_no, u32 anm_no );

//--------------------------------------------------------------
/**
 * @brief	2Dセルオブジェクト解放
 *
 * @param	wk		OPENING_OBJ_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
extern void OpeningRereaseCellObject(OPENING_OBJ_WORK *wk);

//--------------------------------------------------------------
/**
 * @brief	バニッシュ操作
 *
 * @param	wk		OPENING_OBJ_WORK型のポインタ
 *@param	flag	描画フラグ	0:非描画	1:レンダラ描画	
 *
 * @return	none
 */
//--------------------------------------------------------------
extern void OpeningClactVanish(OPENING_OBJ_WORK *wk, int no, int flag);

//--------------------------------------------------------------
/**
 * @brief	移動
 *
 * @param	wk		OPENING_OBJ_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
extern VecFx32 OpeningClactMove(OPENING_OBJ_WORK *wk, int no, int spd);

//--------------------------------------------------------------
/**
 * @brief	初期座標セット
 *
 * @param	wk		OPENING_OBJ_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
extern void OpeningClactMoveInit(OPENING_OBJ_WORK *wk, int no );

//--------------------------------------------------------------
/**
 * @brief	座標セット
 *
 * @param	wk		OPENING_OBJ_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
extern void OpeningClactPosSet(OPENING_OBJ_WORK *wk, int no, int x, int y );


#endif //_OPENING_OBJ_H_


