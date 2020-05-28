//============================================================================================
/**
 * @file	field_clact.c
 * @brief	フィールド用セルアクター設定処理
 * @author	Hiroyuki Nakamura
 * @date	2005.01.13
 */
//============================================================================================
#ifndef FIELD_CLACT_H
#define FIELD_CLACT_H
#undef GLOBAL
#ifdef FIELD_CLACT_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	定数定義
//============================================================================================
typedef struct {
	CLACT_SET_PTR	cas;
	CLACT_U_EASYRENDER_DATA	renddata;	// 簡易レンダーデータ
	CLACT_HEADER_TBL_PTR	clh;		// ヘッダー
	CLACT_U_RES_MANAGER_PTR	resMan[6];	// リソースマネージャ
	CLACT_U_RES_OBJ_TBL * resObjTbl[6];	// リソースオブジェテーブル
	u16	res_max;
	u16	heap;
}FIELD_CLACT;


//============================================================================================
//	プロトタイプ宣言
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * セルアクター設定
 *
 * @param	fcat	設定データ保存場所
 * @param	list	読み込みファイルリスト
 * @param	max		セルアクター最大数
 * @param	heap	ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FieldCellActSet(
				FIELD_CLACT * fcat, const TCATS_RESOURCE_FILE_LIST * list, u32 max, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * セルアクター設定破棄
 *
 * @param	fcat	設定データ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FieldCellActDelete( FIELD_CLACT * fcat );

//--------------------------------------------------------------------------------------------
/**
 * セルアクター登録
 *
 * @param	fcat	設定データ
 * @param	prm		追加データ
 *
 * @return	登録したセルアクターのポインタ
 */
//--------------------------------------------------------------------------------------------
GLOBAL CLACT_WORK_PTR FieldCellActAdd(
						FIELD_CLACT * fcat, const TCATS_OBJECT_ADD_PARAM * prm );


//--------------------------------------------------------------------------------------------
/**
 * セルアクター設定（単発用）
 *
 * @param	fcat	設定データ保存場所
 * @param	crnl	
 * @param	max		セルアクター最大数
 * @param	heap	ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FieldCellActSet_S(
		FIELD_CLACT * fcat, TCATS_RESOURCE_NUM_LIST * crnl, u32 max, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * パレットリソース設定
 *
 * @param	fcat		設定データ
 * @param	arc_id		アーカイブID
 * @param	data_id		データID
 * @param	comp		圧縮フラグ
 * @param	num			転送サイズ
 * @param	trans_mode	転送モード
 * @param	id			リソースID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FldClact_LoadResPlttArc(
		FIELD_CLACT * fcat, int arc_id, int data_id, int comp, int num, int trans_mode, int id );

//--------------------------------------------------------------------------------------------
/**
 * セルリソース設定
 *
 * @param	fcat		設定データ
 * @param	arc_id		アーカイブID
 * @param	data_id		データID
 * @param	comp		圧縮フラグ
 * @param	id			リソースID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FldClact_LoadResCellArc(
					FIELD_CLACT * fcat, int arc_id, int data_id, int comp, int id );

//--------------------------------------------------------------------------------------------
/**
 * セルアニメリソース設定
 *
 * @param	fcat		設定データ
 * @param	arc_id		アーカイブID
 * @param	data_id		データID
 * @param	comp		圧縮フラグ
 * @param	id			リソースID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FldClact_LoadResCellAnmArc(
						FIELD_CLACT * fcat, int arc_id, int data_id, int comp, int id );

//--------------------------------------------------------------------------------------------
/**
 * キャラリソース設定
 *
 * @param	fcat		設定データ
 * @param	arc_id		アーカイブID
 * @param	data_id		データID
 * @param	comp		圧縮フラグ
 * @param	trans_mode	転送モード
 * @param	id			リソースID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FldClact_LoadResourceCharArc(
		FIELD_CLACT * fcat, int arc_id, int data_id, BOOL comp, int trans_mode, int id );

//--------------------------------------------------------------------------------------------
/**
 * キャラのリーソースを変更する
 *
 * @param	fcat		設定データ
 * @param	arc_id		アーカイブID
 * @param	data_id		データID
 * @param	comp		圧縮フラグ
 * @param	id			リソースID
 *
 * @retval	BOOL	
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FldClact_ChangeResourceCharArc(
					FIELD_CLACT * fcat, int arc_id, int data_id, BOOL comp, int id );

//--------------------------------------------------------------------------------------------
/**
 * パレットのリーソースを変更する
 *
 * @param	fcat		設定データ
 * @param	arc_id		アーカイブID
 * @param	data_id		データID
 * @param	comp		圧縮フラグ
 * @param	id			リソースID
 *
 * @retval	BOOL	
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FldClact_ChangeResourcePlttArc(
					FIELD_CLACT * fcat, int arc_id, int data_id, BOOL comp, int id );

//--------------------------------------------------------------------------------------------
/**
 * セルアクター追加（単発用）
 *
 * @param	fcat		設定データ
 * @param	coap_s		表示データ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL CATS_ACT_PTR FieldCellActAdd_S(
				FIELD_CLACT * fcat, const TCATS_OBJECT_ADD_PARAM_S * coap_s );

//--------------------------------------------------------------------------------------------
/**
 * セルアクター削除（単発用）
 *
 * @param	fcat		設定データ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FieldCellActDelete_S( FIELD_CLACT * fcat );





#undef GLOBAL
#endif	/* FIELD_CLACT_H */
