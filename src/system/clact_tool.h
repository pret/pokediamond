//==============================================================================
/**
 * @file	clact_tool.h
 * @brief	clact上位関数郡
 * @author	goto
 * @date	2005.09.12(月)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#ifndef	_CLACT_TOOL_H_
#define _CLACT_TOOL_H_

#include "gflib/clact.h"

#include "system/clact_util.h"
#include "system/render_oam.h"
#include "system/palanm.h"


// -----------------------------------------------------------------------------
//
//
//	■有効・無効フラグ操作系定義
//
//
// -----------------------------------------------------------------------------
// -----------------------------------------
//
//	■可変引数リソースロードを利用する
//
//		有効 = 利用する
//
// -----------------------------------------
#define CATS_CBP_RES_LOAD


// -----------------------------------------
//
//	■RENDER を利用する
//
//		有効 = 利用する
//
// -----------------------------------------
#define CATS_RENDER_USE


// -----------------------------------------------------------------------------
//
//
//	■実装部
//
//
// -----------------------------------------------------------------------------
// -----------------------------------------
//
//	■システム管理構造体
//
//		各アプリで１個だけ用意する
//		clact_tool内では[ csp ]で表現されている
//
// -----------------------------------------
typedef struct _TCATS_SYSTEM   * CATS_SYS_PTR;


// -----------------------------------------
//
//	■リソース管理構造体
//
//		単位ごとに用意する(エフェクト１個など)
//		clact_tool内では[ crp ]で表現されている
//
// -----------------------------------------
typedef struct _TCATS_RESOURCE * CATS_RES_PTR;


// -----------------------------------------
//
//	■CATS を使う時の専用アクター構造体
//
// -----------------------------------------
typedef struct _TCATS_ACT {
	
	CLACT_WORK_PTR			act;		///< アクターのポインタ
	CLACT_HEADER_PTR		act_hd;		///< アクターヘッダーのポインタ
	CLACT_HEADER_TBL_PTR	act_htp;	///< アクターヘッダーテーブルのポインタ
	
	int vram_trans;
	
} TCATS_ACT;

typedef struct _TCATS_ACT * CATS_ACT_PTR;


// -----------------------------------------
//
//	■OAM初期化用構造体
//
// -----------------------------------------
typedef struct {
	
	int mos;		///< メイン	OAM管理領域・開始
	int moe;		///< メイン	OAM管理領域・終了
	int mas;		///< メイン	アフィン管理領域・開始
	int mae;		///< メイン	アフィン管理領域・終了
	int sos;		///< サブ	OAM管理領域・開始
	int soe;		///< サブ	OAM管理領域・開始
	int sas;		///< サブ	アフィン管理領域・開始
	int sae;		///< サブ	アフィン管理領域・終了
	
} TCATS_OAM_INIT;


// -----------------------------------------
//
//	■キャラマネージャ初期化用構造体
//
// -----------------------------------------
typedef struct {
	
	int num;						///< キャラクタID管理数
	int m_size;						///< メイン画面サイズ(byte単位)
	int s_size;						///< サブ画面サイズ(byte単位)

	GXOBJVRamModeChar	main_mode;	///< キャラクタマッピングモード メイン画面
	GXOBJVRamModeChar	sub_mode;	///< キャラクタマッピングモード サブ画面
	
} TCATS_CHAR_MANAGER_MAKE;


// -----------------------------------------
//
//	■リソースとヘッダーをまとめた共用体
//
// -----------------------------------------
typedef union {

	const char* res_file[ CLACT_U_RES_MAX + 1];	///< リソース配列 + ヘッダー
	
	struct {
	
		const char* char_path;					///< キャラ
		const char* pltt_path;					///< パレット
		const char* cell_path;					///< セル
		const char* cell_anm_path;				///< セルアニメ
		const char* mcell_path;					///< マルチセル
		const char* mcell_anm_path;				///< マルチセルアニメ
		
		const char* clact_header_path;			///< セルアクターヘッダー

	} resource;
	
} TCATS_RESOURCE_FILE_LIST;

// -----------------------------------------
//
//	■リソースのみまとめたもの
//
// -----------------------------------------
typedef union {
	
	const char* res_file[ CLACT_U_RES_MAX ];
	
	struct {
		
		const char* char_path;					///< キャラ
		const char* pltt_path;					///< パレット
		const char* cell_path;					///< セル
		const char* cell_anm_path;				///< セルアニメ
		const char* mcell_path;					///< マルチセル
		const char* mcell_anm_path;				///< マルチセルアニメ
		
	} resource;
	
} TCATS_ADD_FILE_LIST;


// -----------------------------------------
//
//	■OBJ登録用構造体
//
// -----------------------------------------
typedef struct {
	
	int no;				///< リソース内データの登録番号
	
	s16 x;				///< [ X ] 座標
	s16 y;				///< [ Y ] 座標
	s16 z;				///< [ Z ] 座標
	
	u16	anm;			///< アニメ番号
	int pri;			///< 優先順位
	int	pal;			///< パレット番号
	int d_area;			///< 描画エリア
	
	int param1;			///< 転送用フラグ
	int param2;
	int param3;
	int param4;
	
} TCATS_OBJECT_ADD_PARAM;

// -----------------------------------------
//
//	■リソース登録最大数定義構造体
//
// -----------------------------------------
typedef union {
	
	int res_num[ CLACT_U_RES_MAX ];
	
	struct {
		
		int char_num;				///< キャラの数
		int pltt_num;				///< パレットの数
		int cell_num;				///< セルの数
		int cell_anm_num;			///< セルアニメの数
		int mcell_num;				///< マルチセルの数
		int mcell_anm_num;			///< マルチセルアニメの数
		
	} resource_num;	
	
} TCATS_RESOURCE_NUM_LIST;

// -----------------------------------------
//
//	■登録用構造体 単体登録用
//
// -----------------------------------------
typedef struct {
	
	s16 x;							///< [ X ] 座標
	s16 y;							///< [ Y ] 座標
	s16 z;							///< [ Z ] 座標
	
	u16	anm;						///< アニメ番号
	int pri;						///< 優先順位
	int	pal;						///< パレット番号
	int d_area;						///< 描画エリア
	
	int id[ CLACT_U_RES_MAX ];		///< 使用リソースIDテーブル
		
	int bg_pri;						///< BG面への優先度
	int vram_trans;					///< Vram転送フラグ
	
} TCATS_OBJECT_ADD_PARAM_S;


// -----------------------------------------
//
//	■CATS 専用の定義群
//
// -----------------------------------------
enum ECATS {
	
	CATS_ENABLE_TRUE	= 1,
	CATS_ENABLE_FALSE	= 0,
	
	CATS_D_AREA_MAIN	= NNS_G2D_VRAM_TYPE_2DMAIN,
	CATS_D_AREA_SUB		= NNS_G2D_VRAM_TYPE_2DSUB,
	
	CATS_ANM_AUTO_ON	= 1,
	CATS_ANM_AUTO_OFF	= 0,
	
	CATS_RENDER_USE_ON	= 1,
	CATS_RENDER_USE_OFF = 0,
		
};


// =============================================================================
//
//
//	■共通操作関数 － 単体登録、ヘッダー登録兼用
//
//
// =============================================================================
// -----------------------------------------
//
//	■CATS_SYSTEM のメモリ確保
//
// -----------------------------------------
extern CATS_SYS_PTR CATS_AllocMemory(int heap_area);


// -----------------------------------------
//
//	■CATS_RESOURCE のメモリ確保
//
// -----------------------------------------
extern CATS_RES_PTR CATS_ResourceCreate(CATS_SYS_PTR csp);


// -----------------------------------------
//
//	■CATS リソースの数を取得
//
// -----------------------------------------
extern int CATS_ResourceNumGet(CATS_SYS_PTR csp);


//------------------------------------------
//
//	■CATS レンダラーデータを取得
//
//------------------------------------------
extern CLACT_U_EASYRENDER_DATA * CATS_EasyRenderGet(CATS_SYS_PTR csp);


// -----------------------------------------
//
//	■CATS システムの初期化
//
// -----------------------------------------
extern BOOL CATS_SystemInit(CATS_SYS_PTR csp, const TCATS_OAM_INIT* coi, const TCATS_CHAR_MANAGER_MAKE* ccmm, int pal_num);


// -----------------------------------------
//
//	■CATS RENDERの利用フラグ設定
//
// -----------------------------------------
extern void CATS_RenderUseSet(CATS_SYS_PTR csp, int flag);

// -----------------------------------------
//
//	■CATS セルアクターセットの作成
//
// -----------------------------------------
extern BOOL CATS_ClactSetInit(CATS_SYS_PTR csp, CATS_RES_PTR crp, int num);


// -----------------------------------------
//
//	■CATS OBJ破棄
//
// -----------------------------------------
extern void CATS_ObjectDel(CLACT_WORK_PTR act);


// -----------------------------------------
//
//	■CATS 描画
//
// -----------------------------------------
extern void CATS_Draw(CATS_RES_PTR crp);


// -----------------------------------------
//
//	■CATS Vram転送設定
//
// -----------------------------------------
extern void CATS_UpdateTransfer(void);


// -----------------------------------------
//
//	■CATS OAM転送
//
// -----------------------------------------
extern void CATS_RenderOamTrans(void);
extern void CATS_RenderOamTransEx(CATS_SYS_PTR csp);


// -----------------------------------------
//
//	■CATS セルアクターセット破棄	※
//
// -----------------------------------------
extern void CATS_ClactSetDelete(CATS_RES_PTR crp);


// -----------------------------------------
//
//	■CATS ヘッダーテーブル破棄		※
//
// -----------------------------------------
extern void CATS_HeaderTblDelete(CATS_RES_PTR crp);


// -----------------------------------------
//
//	■CATS リソースデータ破棄		※
//
// -----------------------------------------
extern void CATS_ResourceDelete(CATS_RES_PTR crp);


// -----------------------------------------
//
//	■CATS マネージャー破棄			※
//
// -----------------------------------------
extern void CATS_ManagerDelete(CATS_SYS_PTR csp);


// -----------------------------------------
//
//	■CATS リソース用のメモリ破棄	※
//
// -----------------------------------------
extern void CATS_ResourceFree(CATS_SYS_PTR csp, CATS_RES_PTR crp);


// -----------------------------------------
//
//	■CATS リソース関連の破棄 [ 推奨 ]
//
//	 ※の付いている動作をすべて行なうので推奨
//
// -----------------------------------------
extern void CATS_ResourceDestructor(CATS_SYS_PTR csp, CATS_RES_PTR crp);


// -----------------------------------------
//
//	■CATS System本体のメモリ破棄
//
// -----------------------------------------
extern void CATS_FreeMemory(CATS_SYS_PTR csp);


// =============================================================================
//
//
//	■ヘッダー読み込み関数
//
//
// =============================================================================
// -----------------------------------------
//
//	■CATS リソースロード
//
// -----------------------------------------
extern BOOL CATS_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_RESOURCE_FILE_LIST* res_list);
extern BOOL CATS_ResourceLoadBinary(
			CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_RESOURCE_FILE_LIST* res_list );

#ifdef CATS_CBP_RES_LOAD	///< 可変引数

extern BOOL CATS_ResourceLoad_FileName(CATS_SYS_PTR csp, CATS_RES_PTR crp, ...);

#endif


// -----------------------------------------
//
//	■CATS OBJ登録
//
// -----------------------------------------
extern CLACT_WORK_PTR CATS_ObjectAdd(CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_OBJECT_ADD_PARAM* coap);
extern CLACT_WORK_PTR CATS_ObjectAdd_EX(CATS_SYS_PTR csp, CATS_RES_PTR crp, int no,
							 				s16 x, s16 y, s16 z, u16 anm, int pri, int pal, int d_area,
							 				int param1, int param2, int param3, int param4); 




// =============================================================================
//
//
//	■単体登録用
//
//
// =============================================================================
// -----------------------------------------
//
//	■CATS リソース管理数の設定
//
// -----------------------------------------
extern BOOL CATS_ResourceManagerInit(CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_RESOURCE_NUM_LIST* crnl);


// -----------------------------------------
//
//	■CATS リソース登録
//
// -----------------------------------------
extern BOOL CATS_LoadResourceChar(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int trans_mode, int id);
extern BOOL CATS_LoadResourceCharArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int trans_mode, int id);
extern u8 CATS_LoadResourcePltt(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, 
	int num, int trans_mode, int id);
extern s8 CATS_LoadResourcePlttArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	int arc_id, int data_id, int comp, int num, int trans_mode, int id);
extern BOOL CATS_LoadResourceCell(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int id);
extern BOOL CATS_LoadResourceCellArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int id);
extern BOOL CATS_LoadResourceCellAnm(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int id);
extern BOOL CATS_LoadResourceCellAnmArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int id);
extern BOOL CATS_LoadResourceMCell(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int id);
extern BOOL CATS_LoadResourceMCellArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int id);
extern BOOL CATS_LoadResourceMCellAnm(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int id);
extern BOOL CATS_LoadResourceMCellAnmArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int id);
extern u8 CATS_LoadResourcePlttWork(PALETTE_FADE_PTR pfd, FADEREQ req, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, const char* path, int num, int trans_mode, int id);
extern u8 CATS_LoadResourcePlttWorkArc(PALETTE_FADE_PTR pfd, FADEREQ req, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, int arc_id, int data_id, int comp, int num, int trans_mode, int id);


// -----------------------------------------
//
//	■CATS リソース削除
//
// -----------------------------------------
extern BOOL CATS_FreeResourceChar(CATS_RES_PTR crp, int id);
extern BOOL CATS_FreeResourcePltt(CATS_RES_PTR crp, int id);
extern BOOL CATS_FreeResourceCell(CATS_RES_PTR crp, int id);
extern BOOL CATS_FreeResourceCellAnm(CATS_RES_PTR crp, int id);
extern BOOL CATS_FreeResourceMCell(CATS_RES_PTR crp, int id);
extern BOOL CATS_FreeResourceMCellAnm(CATS_RES_PTR crp, int id);


// -----------------------------------------
//
//	■CATS OBJ登録
//
// -----------------------------------------
extern CATS_ACT_PTR CATS_ObjectAdd_S(CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_OBJECT_ADD_PARAM_S* coap_s);


// -----------------------------------------
//
//	■CATS リソース関連の破棄
//
// -----------------------------------------
extern void CATS_ResourceDestructor_S(CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern void CATS_ActorPointerDelete_S(CATS_ACT_PTR cap);








// =============================================================================
//
//
//	■OBJ操作関連まとめ
//
//
// =============================================================================
// =============================================================================
//
//	■表示操作
//
// =============================================================================
// -----------------------------------------
//
//	■CATS OBJのアニメ更新
//
// -----------------------------------------
extern void CATS_ObjectUpdate(CLACT_WORK_PTR act);
extern void CATS_ObjectUpdateCap(CATS_ACT_PTR cap);
extern void CATS_ObjectUpdateNumCap(CATS_ACT_PTR cap, fx32 frame);


// -----------------------------------------
//
//	■CATS OBJのアニメシーケンス設定＆取得
//
// -----------------------------------------
extern void CATS_ObjectAnimeSeqSetCap( CATS_ACT_PTR cap, u32 seq );
extern u32 CATS_ObjectAnimeSeqGetCap( CATS_ACT_PTR cap );


// -----------------------------------------
//
//	■CATS OBJのオートアニメ設定
//
// -----------------------------------------
extern void CATS_ObjectAutoAnimeSet(CLACT_WORK_PTR act, int flag);
extern void CATS_ObjectAutoAnimeSetCap(CATS_ACT_PTR cap, int flag);


// -----------------------------------------
//
//	■CATS OBJのオートアニメ取得
//
// -----------------------------------------
extern int CATS_ObjectAutoAnimeGet(CLACT_WORK_PTR act);
extern int CATS_ObjectAutoAnimeGetCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	■CATS OBJのオートアニメスピード設定＆取得
//
// -----------------------------------------
extern void CATS_ObjectAutoAnimeSpeedSet(CLACT_WORK_PTR act, fx32 frame);
extern void CATS_ObjectAutoAnimeSpeedSetCap(CATS_ACT_PTR cap, fx32 frame);
extern fx32 CATS_ObjectAutoAnimeSpeedGet(CLACT_WORK_PTR act);
extern fx32 CATS_ObjectAutoAnimeSpeedGetCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	■CATS OBJのアニメフレーム設定＆取得
//
// -----------------------------------------
extern void CATS_ObjectAnimeFrameSet(CLACT_WORK_PTR act, u16 frame);
extern void CATS_ObjectAnimeFrameSetCap(CATS_ACT_PTR cap, u16 frame);
extern u16 CATS_ObjectAnimeFrameGet(CLACT_WORK_PTR act);
extern u16 CATS_ObjectAnimeFrameGetCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	■CATS OBJのアニメ動作チェック
//
// -----------------------------------------
extern BOOL CATS_ObjectAnimeActiveCheck(CLACT_WORK_PTR act);
extern BOOL CATS_ObjectAnimeActiveCheckCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	■CATS OBJの表示非表示
//
// -----------------------------------------
extern void CATS_ObjectEnable(CLACT_WORK_PTR act, int enable);
extern void CATS_ObjectEnableCap(CATS_ACT_PTR cap, int enable);
extern int	CATS_ObjectEnableGet(CLACT_WORK_PTR act);
extern int	CATS_ObjectEnableGetCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	■CATS パレット変更
//
// -----------------------------------------
extern void CATS_ObjectPaletteSet(CLACT_WORK_PTR act, int pal);
extern void CATS_ObjectPaletteSetCap(CATS_ACT_PTR cap, int pal);
extern void CATS_ObjectPaletteOffsetSet(CLACT_WORK_PTR act, int pal_ofs);
extern void CATS_ObjectPaletteOffsetSetCap(CATS_ACT_PTR cap, int pal_ofs);
extern int CATS_ObjectPaletteOffsetGetCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	■CATS BGとの優先度変更
//
// -----------------------------------------
extern void CATS_ObjectBGPriSet(CLACT_WORK_PTR act, int pri);
extern void CATS_ObjectBGPriSetCap(CATS_ACT_PTR cap, int pri);
extern int	CATS_ObjectBGPriGetCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	■CATS OBJとの優先度変更
//
// -----------------------------------------
extern void CATS_ObjectPriSet(CLACT_WORK_PTR act, int pri);
extern void CATS_ObjectPriSetCap(CATS_ACT_PTR cap, int pri);
extern u32	CATS_ObjectPriGet(CLACT_WORK_PTR act);
extern u32	CATS_ObjectPriGetCap(CATS_ACT_PTR cap);



// =============================================================================
//
//	■座標操作
//
// =============================================================================
// -----------------------------------------
//
//	■CATS OBJの座標変更
//
// -----------------------------------------
extern void CATS_ObjectPosSet(CLACT_WORK_PTR act, s16 x, s16 y);
extern void CATS_ObjectPosSetCap(CATS_ACT_PTR cap, s16 x, s16 y);
extern void CATS_ObjectPosSet_SubSurface(CLACT_WORK_PTR act, s16 x, s16 y, fx32 sub_surface_y);
extern void CATS_ObjectPosSetCap_SubSurface(CATS_ACT_PTR cap, s16 x, s16 y, fx32 sub_surface_y);


// -----------------------------------------
//
//	■CATS OBJの座標取得
//
// -----------------------------------------
extern void CATS_ObjectPosGet(CLACT_WORK_PTR act, s16 *x, s16 *y);
extern void CATS_ObjectPosGetCap(CATS_ACT_PTR cap, s16 *x, s16 *y);
extern void CATS_ObjectPosGet_SubSurface(CLACT_WORK_PTR act, s16 *x, s16 *y, fx32 sub_surface_y);
extern void CATS_ObjectPosGetCap_SubSurface(CATS_ACT_PTR cap, s16 *x, s16 *y, fx32 sub_surface_y);


// -----------------------------------------
//
//	■CATS OBJの移動
//
// -----------------------------------------
extern void CATS_ObjectPosMove(CLACT_WORK_PTR act, s16 x, s16 y);
extern void CATS_ObjectPosMoveCap(CATS_ACT_PTR cap, s16 x, s16 y);



// =============================================================================
//
//	■アフィン操作 フリップ操作
//
// =============================================================================
// -----------------------------------------
//
//	■CATS OBJのアフィンパラメータをセット
//
// -----------------------------------------
extern void CATS_ObjectAffineSet(CLACT_WORK_PTR act, int affine);
extern void CATS_ObjectAffineSetCap(CATS_ACT_PTR cap, int affine);


// -----------------------------------------
//
//	■CATS OBJのアフィンパラメータ取得
//
// -----------------------------------------
extern int CATS_ObjectAffineGet(CLACT_WORK_PTR act);
extern int CATS_ObjectAffineGetCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	■CATS OBJの拡縮率の変更
//
// -----------------------------------------
extern void CATS_ObjectScaleSet(CLACT_WORK_PTR act, f32 sx, f32 sy);
extern void CATS_ObjectScaleSetCap(CATS_ACT_PTR cap, f32 sx, f32 sy);


// -----------------------------------------
//
//	■CATS OBJの拡縮率の加減算
//
// -----------------------------------------
extern void CATS_ObjectScaleAdd(CLACT_WORK_PTR act, f32 sx, f32 sy);
extern void CATS_ObjectScaleAddCap(CATS_ACT_PTR cap, f32 sx, f32 sy);


// -----------------------------------------
//
//	■CATS OBJの拡縮率の取得
//
// -----------------------------------------
extern void CATS_ObjectScaleGet(CLACT_WORK_PTR act, f32* sx, f32* sy);
extern void CATS_ObjectScaleGetCap(CATS_ACT_PTR cap, f32* sx, f32* sy);


// -----------------------------------------
//
//	■CATS OBJの回転率の変更
//
// -----------------------------------------
extern void CATS_ObjectRotationSet(CLACT_WORK_PTR act, u16 rot);
extern void CATS_ObjectRotationSetCap(CATS_ACT_PTR cap, u16 rot);


// -----------------------------------------
//
//	■CATS OBJの回転率の加減算
//
// -----------------------------------------
extern void CATS_ObjectRotationAdd(CLACT_WORK_PTR act, s32 rot);
extern void CATS_ObjectRotationAddCap(CATS_ACT_PTR cap, s32 rot);


// -----------------------------------------
//
//	■CATS OBJの回転率取得
//
// -----------------------------------------
extern u16	CATS_ObjectRotationGet(CLACT_WORK_PTR act);
extern u16	CATS_ObjectRotationGetCap(CATS_ACT_PTR cap);


// -----------------------------------------
//
//	■フリップ操作
//
// -----------------------------------------
extern void CATS_ObjectFlipSet(CLACT_WORK_PTR act, int flip);
extern void CATS_ObjectFlipSetCap(CATS_ACT_PTR cap, int flip);


// -----------------------------------------
//
//	■フリップ取得
//
// -----------------------------------------
extern int CATS_ObjectFlipGet(CLACT_WORK_PTR act);
extern int CATS_ObjectFlipGetCap(CATS_ACT_PTR cap);

// -----------------------------------------
//
//	■CATS アフィン変換座標の設定
//		cap座標 + アフィン座標　位置で回転拡大されます
//
// -----------------------------------------
extern void CATS_ObjectAffinePosSetCap(CATS_ACT_PTR cap, s16 x, s16 y);


// -----------------------------------------
//
//	■CATS アフィン変換座標の取得
//		cap座標 + アフィン座標　位置で回転拡大されます
//
// -----------------------------------------
extern void CATS_ObjectAffinePosGetCap(CATS_ACT_PTR cap, s16 *x, s16 *y);


// -----------------------------------------
//
//	■CATS アフィン変換座標の移動
//		cap座標 + アフィン座標　位置で回転拡大されます
//
// -----------------------------------------
extern void CATS_ObjectAffinePosMoveCap(CATS_ACT_PTR cap, s16 x, s16 y);

// -----------------------------------------
//
//	■CATS モザイク
//
// -----------------------------------------
extern void CATS_ObjectMosaicSet(CATS_ACT_PTR cap, BOOL flag);


// =============================================================================
//
//	■OBJモード操作
//
// =============================================================================
// -----------------------------------------
//
//	■OBJモード操作
//
// -----------------------------------------
extern void CATS_ObjectObjModeSet(CLACT_WORK_PTR act, GXOamMode objmode);
extern void CATS_ObjectObjModeSetCap(CATS_ACT_PTR cap, GXOamMode objmode);


// -----------------------------------------
//
//	■OBJモード取得
//
// -----------------------------------------
extern GXOamMode CATS_ObjectObjModeGet(CLACT_WORK_PTR act);
extern GXOamMode CATS_ObjectObjModeGetCap(CATS_ACT_PTR cap);





// =============================================================================
//
//	■その他のツール系
//
// =============================================================================
extern BOOL CATS_LoadResourceCharArcModeAdjust(
				CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int trans_mode, int id );
extern BOOL CATS_LoadResourceCharArcModeAdjustAreaCont(
				CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int trans_mode, int id);
extern void CATS_ChangeResourceCharArc(
				CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int id );
extern void CATS_ChangeResourcePlttArc(
				CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int id );
extern CLACT_SET_PTR CATS_GetClactSetPtr(CATS_RES_PTR crp);
extern const NNSG2dImagePaletteProxy* CATS_PlttProxy( CATS_RES_PTR crp, int pltt_id );
extern u32 CATS_PlttID_NoGet(CATS_RES_PTR crp, int pltt_id, NNS_G2D_VRAM_TYPE vram_type);

#if 0
typedef struct {
	
	int x;
	int y;
	int w;
	int h;
	
} CHANGES_INTO_DATA_RECT;

#define CHAR_DOT_X		(8/2)						///< 1キャラのバイトサイズ
#define CHAR_DOT_Y		(8)							///< 1キャラのバイトサイズ
#define CHAR_BYTE		(CHAR_DOT_X * CHAR_DOT_Y)	///< 1キャラバイト数
#define POKE_TEX_SX		(0)							///< ポケモン変換用テクスチャ切り取り位置
#define POKE_TEX_SY		(0)
#define POKE_TEX_EX		(10)
#define POKE_TEX_EY		(10)
#define POKE_TEX_SIZE	((POKE_TEX_EX - POKE_TEX_SX) *  (POKE_TEX_EY - POKE_TEX_SY) * CHAR_BYTE)

extern void	 ChangesInto_1D_from_2D(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff);
extern void	 ChangesInto_1D_from_2D_RC(int arc_id, int index_no, int heap_id, CHANGES_INTO_DATA_RECT* rc, void* buff);

extern void* ChangesInto_1D_from_2D_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h);
extern void* ChangesInto_1D_from_2D_Alloc_RC(int arc_id, int index_no, int heap_id, CHANGES_INTO_DATA_RECT* rc);

extern void  ChangesInto_OAM_from_1D(int sx, int sy, int x, int y, int w, int h, int* bofs, const void* src, void* dst);
extern void  ChangesInto_OAM_from_1D_RC(int sx, int sy, CHANGES_INTO_DATA_RECT* rc, int* bofs, const void* src, void* dst);

extern void  ChangesInto_OAM_from_PokeTex(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff);
extern void  ChangesInto_OAM_from_PokeTex_RC(int arc_id, int index_no, int heap_id, CHANGES_INTO_DATA_RECT* rc, void* buff);

extern void* ChangesInto_OAM_from_PokeTex_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h);
extern void* ChangesInto_OAM_from_PokeTex_Alloc_RC(int arc_id, int index_no, int heap_id, CHANGES_INTO_DATA_RECT* rc);

extern void  ChangesInto_BattlePokeData(int arc_id, int index_no, int heap_id, void* buff);
extern void* ChangesInto_BattlePokeData_Alloc(int arc_id, int index_no, int heap_id);
#endif

#endif
