//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		blact.c
 *	@brief		新規ビルボードアクター
 *	@author		tomoya takahashi
 *	@data		2005.10.05
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#define __BLACT_H_GLOBAL
#include "string.h"
#include "blact.h"
#include "vram_transfer_anm.h"
#include "vram_transfer_manager.h"
#include "simple_3dgraphics.h"
#include "system.h"
#include "str_tool.h"
#include "gflib_os_print.h"
#include "assert.h"

#include "bounding_box.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
 */
//-----------------------------------------------------------------------------
//-------------------------------------
// アニメーションチェンジ処理の種類
//
// アニメーションセット変更処理の状態
//=====================================
enum
{
	BLACT_CHG_NONE,		// 処理なし
	BLACT_CHG_VRAM,		// Vram転送登録済み
};

enum{
	BLACT_RES_MAN_MDL,
	BLACT_RES_MAN_TEX,
	BLACT_RES_MAN_ANM
};

enum{
	BLACT_DRAW_REF_NONE,
	BLACT_DRAW_REF_DRAW_BEFORE,
	BLACT_DRAW_REF_DRAW_AFTER,
};

// 常駐アニメ
// パレットベースアドレス数マスク
#define BLACT_PLTT_BASE_MASK	(0x000001fff)

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
 */
//-----------------------------------------------------------------------------


//-------------------------------------
//	ビルボードアクター動作構造体
//
//	ビルボード１体のデータ
//=====================================
typedef struct BLACT_WORK_tag{
	//------------------------------------
	//	プログラマーが操作するメンバ郡
	//====================================
	VecFx32		Matrix;						// 相対座標
	VecFx32		Scale;						// スケール
	
	u8			draw;						// 描画を行うか(0:おこなわない 1:行う)

	//------------------------------------
	//	直接操作を禁止するメンバ郡
	//===================================
	void*	pBlActSet;		// 自分の属しているアニメーションセットのポインタ(キャストして使用)

	const BLACT_ANIME_TBL*	pAnmTbl;		// アニメーションテーブル
	
	NNSG3dRenderObj			RenderObj;		// レンダーオブジェクト

	NNSG3dResMdlSet*		pModelSet;		// モデルセット
	NNSG3dResMdl*			pModel;			// モデルリソース
	NNSG3dResTex*			pMdlTex;		// モデルに貼り付けるテクスチャ
	const NNSG3dResTex*		pAnmTex;		// アニメーション用テクスチャ
	NNSGfdTexKey			texKey;			// テクスチャVramKey
	NNSGfdTexKey			tex4x4Key;		// 4xpテクスチャVramKey
	NNSGfdPlttKey			plttKey;		// パレットVramKey
	
	TEXANM_DATATBL				texAnm;		// テクスチャアニメーションデータ
	ITP_VRAM_ANM_PTR		ItpVramObj;		// Vram転送用オブジェ	(Vram転送時のみ)
	
	u8			flag;						// On/Offフラグ
	u16			AnmOffs;					// 今のアニメーションオフセット
	fx32		frame;						// 現在フレーム
	
	// 登録リスト
	struct BLACT_WORK_tag*	next;	// 次のアクター
	struct BLACT_WORK_tag*	prev;	// 前のアクター
	
} BLACT_WORK;


//===================================================================
//
//	ビルボードアクターセット構造体
//
//	ビルボードアクターの実態
//
//===================================================================
typedef struct _BLACT_SET{
	/* コントロールフラグ */
	u8				SysFlag;	// 登録しているか	0:非登録 1:登録
	u8				DrawFlag;	// 描画フラグ 0:非描画 1:描画(デフォルト)
	u8				MoveFlag;	// TCBタスクフラグ 0:非動作 1:動作(デフォルト)

	/* 破棄したオブジェクトがまだ画面に反映されている */
	u8				DelObjDrawRef;
	
	/* ビルボードアクター動作構造体 */
	BLACT_WORK*		pWork;		// 実態
	int				WorkNum;	// 数
	
	/* リストトップデータ */
	BLACT_WORK		Dummy;	
	
	/* スタック */
	BLACT_WORK**	ppWorkStack;	// 実態(数==WorkNum)
	int				WorkStackNow;	// 今のトップの位置
	
	/* アロケーター */
	NNSFndAllocator* pAlloc;		// 使用するアロケータ
	
	/* Vram転送アニメーションのオブジェクト */
	ITP_VRAM_SYS_PTR pItpTop;


}BLACT_SET;



//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	ビルボードアクターシステム操作関数
//=====================================
static BLACT_SET_PTR getCleanBlActSet(void);
static void cleanBlActSet(BLACT_SET* work);

//-------------------------------------
//	BLACT_SET操作関数
//=====================================
static void drawBlActSet(BLACT_SET* pBlActSet);
static void drawBlAct( BLACT_WORK *act );

//-------------------------------------
//	常駐アニメ用システム
//=====================================
static void normAnmTexDataSet( BLACT_WORK* act );
static void normAnmTexParamSet( NNSG3dResMdl* p_mdl, const NNSG3dResTex* p_tex, u8 tex_idx );
static void normAnmTexParamSetOneMatData( NNSG3dResMat* pMat, const	NNSG3dResDictTexToMatIdxData* pBindData, u32 tex_offs );
static void normAnmPlttParamSet( NNSG3dResMdl* p_mdl, const NNSG3dResTex* p_tex, u8 pltt_idx );
static void normAnmPlttParamSetOneMatData( NNSG3dResMat* pMat, const NNSG3dResDictPlttToMatIdxData* pBindData, u32 pltt_offs );


//-------------------------------------
//	stackの処理
//=====================================
static void initStack(BLACT_SET* pSet);			// 初期化
static BLACT_WORK* popStack(BLACT_SET* pSet);	// 取り出し
static BOOL pushStack(BLACT_SET* pSet, BLACT_WORK* pDat);	// 格納

//-------------------------------------
//	リスト管理
//=====================================
static void setList(BLACT_WORK* Dummy, BLACT_WORK* pDat);
static void remList(BLACT_WORK* pDat);

//-------------------------------------
//	テクスチャの描画前処理
//	テクスチャの描画後処理
//=====================================
static void DrawTexBind(BLACT_WORK* bl_w);
static void DrawTexreBind(BLACT_WORK* bl_w);

//-------------------------------------
//	へっだーからリソースを取得
//=====================================
static void* getRes(const BLACT_HEADER* p_head, int flag);
static const BLACT_ANIME_TBL* getAnmTbl(const BLACT_ANIME_TBL* p_anm, int ofs);

//-------------------------------------
//	データロード系関数郡
//=====================================
static NNSG3dResMdlSet* blact_getMdl(const BLACT_HEADER* p_head,NNSG3dResMdl** ppMdl, NNSG3dResTex** ppTex);
static NNSG3dAnmObj* blact_getItp(const BLACT_HEADER* p_head, const NNSG3dResMdl* p_mdl, const NNSG3dResTex* p_tex, NNSFndAllocator* pAlloc);
static NNSG3dResTex* blact_getTex(const BLACT_HEADER* p_head);

//-------------------------------------
//	アニメーションセット変更データ
//=====================================
static void chgBillboadAnmSet_Core( BLACT_WORK* act, const BLACT_HEADER* header );
// Vram転送用テーブルデータ設定関数
static void chgBillboadAnmSet_Core_VRAM( BLACT_WORK* act, const BLACT_HEADER* header );
// 常駐用アニメーションセット変更関数
static void core_anmset_chg_norm( BLACT_WORK* blact_w, const BLACT_HEADER* header);

static fx32	nowOffsAnmStartFrame( const BLACT_WORK* act, int offs );
static int anmFrameChg_Core( BLACT_WORK* act, fx32 num );

static int anmFrameChgSys( const BLACT_ANIME_TBL* anm, fx32* frame, fx32 num );

//-------------------------------------
//
//　テクスチャ貼り付け、破棄処理
//				関数郡
//	
//=====================================
static void allocTexKey(const NNSG3dResTex* tex, NNSG3dTexKey* texkey, NNSG3dTexKey* tex4x4key, NNSG3dPlttKey* plttkey);
static void releaseTexture(NNSG3dResTex* tex, NNSG3dTexKey* texkey, NNSG3dTexKey* tex4x4key, NNSG3dPlttKey* plttkey);
static void reBindTexture(NNSG3dResTex* tex, NNSG3dResMdlSet* mdl, NNSG3dTexKey* texkey, NNSG3dTexKey* tex4x4key, NNSG3dPlttKey* plttkey);
static void delBindTexture(NNSG3dTexKey* texkey, NNSG3dTexKey* tex4x4key, NNSG3dPlttKey* plttkey);
static BOOL check_texsize_equal(const NNSG3dResTex* tex1, const NNSG3dResTex* tex2);

//-------------------------------------
//
//	ビルボードアクター破棄処理
//	関数郡
//	
//=====================================
static void del_blact(BLACT_SET* pBlActSet, BLACT_WORK* delWork);// 破棄処理

//-------------------------------------
//
//	ビルボードアクター登録処理
//	関数郡
//	
//=====================================
static void data_chg_vram_mdl_core(BLACT_WORK* blact_w, const BLACT_HEADER* header);
static void data_chg_vram_anm_core(const BLACT_SET* pBlActSet, BLACT_WORK* blact_w, const BLACT_HEADER* header);

static void data_chg_norm_mdl_core(BLACT_WORK* blact_w, const BLACT_HEADER* header);
static void data_chg_norm_anm_core(BLACT_WORK* blact_w, const BLACT_HEADER* header);

//----------------------------------------------------------------------------
/**
 *					グローバル変数宣言
 */
//-----------------------------------------------------------------------------
static BLACT_SET*	pBlActSetTbl=NULL;	// ビルボードアクター管理テーブル
static int			BlActSetNum=0;		// 登録可能数


//-----------------------------------------------------------------------------
/**
 * 
 *	@brief	BLACT_SET構造体型データ　クリア
 *
 *	@param	work	BLACT_SET構造体型データへのポインタ
 *	@return none
 *	
 */
//-----------------------------------------------------------------------------
static void cleanBlActSet(BLACT_SET* work)
{
	work->SysFlag		= 0;
	work->DrawFlag		= 0;
	work->pWork			= NULL;
	work->WorkNum		= 0;
	work->ppWorkStack	= NULL;
	work->WorkStackNow	= 0;
	work->pAlloc		= NULL;
	work->pItpTop		= NULL;
	work->DelObjDrawRef = BLACT_DRAW_REF_NONE;
}

//-----------------------------------------------------------------------------
/**
 * 
 *	@brief	BLACT_WORK構造体型データ　クリア
 *
 *	@param	pDat	BLACT_WORK構造体型データへのポインタ
 *	@return none
 *	
 */
//-----------------------------------------------------------------------------
void BLACT_WorkClear( BLACT_WORK *pDat )
{
	u8 i = 0;

	pDat->pBlActSet = NULL;
	pDat->pAnmTbl	= NULL;
	
	pDat->pModelSet	= NULL;			// モデルセット
	pDat->pModel	= NULL;			// モデル
	pDat->pMdlTex	= NULL;			// モデルに貼り付けるテクスチャ
	pDat->pAnmTex	= NULL;			// アニメーション用テクスチャ
	// アニメーションデータ
	memset( &pDat->texAnm, 0, sizeof(TEXANM_DATATBL) );
	pDat->texKey	= BLACT_TEXKEY_VRAMANM;
	pDat->tex4x4Key	= BLACT_TEXKEY_VRAMANM;
	pDat->plttKey	= BLACT_PLTTKEY_VRAMANM;
	pDat->ItpVramObj = NULL;

	VEC_Set(&(pDat->Matrix),0,0,0);
	VEC_Set(&(pDat->Scale),FX32_ONE,FX32_ONE,FX32_ONE);

	pDat->AnmOffs = 0;

	pDat->flag = 0;

	pDat->next = NULL;
	pDat->prev = NULL;
	pDat->draw = 0;
}

//=============================================================================
//
//		ビルボードアクターシステム操作関数郡
//		
//		ビルボードアクターのシステムを操作する関数
//=============================================================================
//-----------------------------------------------------------------------------
/**
 *
 *	@brief	ビルボードアクターシステムの初期化
 *
 *	@param	ContNum			管理ビルボードアクターセット数
 *	@param	heap			使用ヒープ
 *
 *	@return none
 *
 * ビルボードアクター使用前に１度実行
 * 
 */
//-----------------------------------------------------------------------------
void BLACT_InitSys(int ContNum, int heap)
{
	int i;		// ループ用

	
	GF_ASSERT((pBlActSetTbl==NULL) && "初期化済みです\n");
	
	// 管理テーブル作成
	pBlActSetTbl = sys_AllocMemory(heap, sizeof(BLACT_SET) * ContNum);
	BlActSetNum = ContNum;

	// 初期化
	for(i=0;i<ContNum;i++){
		cleanBlActSet(&pBlActSetTbl[i]);
	}
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	ビルボードアクターシステムの破棄
 *
 *	@param	none
 *
 *	@return none
 *
 * ビルボードアクター使用後に１度必要
 * 
 */
//-----------------------------------------------------------------------------
void BLACT_DestSys(void)
{
	int i;		// ループ用
	
	// ビルボードアクターセット全てをはき
	for(i=0;i<BlActSetNum;i++){
		BLACT_DestSet(pBlActSetTbl + i);
	}

	sys_FreeMemoryEz(pBlActSetTbl);
	pBlActSetTbl = NULL;
	BlActSetNum = 0;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	ビルボードアクターシステムの描画
 *
 *	@param	none
 *
 *	@return none
 *
 * 登録されているビルボードアクターセットを描画します。
 *
 * 描画したくないときは
 *		BLACT_SET構造体のDrawFlag を0にする
 * 
 */
//-----------------------------------------------------------------------------
void BLACT_DrawSys(void)
{
	int i;		// ループ用
	
	// ビルボードアクターセット全てを描画
	for(i=0;i<BlActSetNum;i++){
		if(pBlActSetTbl[i].DrawFlag == 1){	
			drawBlActSet(&pBlActSetTbl[i]);
		}
		if( pBlActSetTbl[i].DelObjDrawRef == BLACT_DRAW_REF_DRAW_BEFORE ){
			pBlActSetTbl[i].DelObjDrawRef = BLACT_DRAW_REF_DRAW_AFTER;
		}
	}
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	ビルボードアクター単体の描画
 *
 *	@param	act	BLACT_WORK_PTR
 *
 *	@return none
 *
 * 指定したビルボードアクターセットを描画します。
 *
 * 描画したくないときは
 *		BLACT_SET構造体のDrawFlag を0にする
 * 
 */
//-----------------------------------------------------------------------------
void BLACT_Draw(BLACT_WORK_PTR act)
{
	drawBlAct(act);
}

//=============================================================================
//
//		ビルボードアクターセット操作関数郡
//		
//=============================================================================
//-----------------------------------------------------------------------------
/**
 *
 *	@brief	ビルボードアクターセット設定
 *
 *	@param	pSetData		アクターセット情報	
 *
 *	@retval	BLACT_SET_PTR	アクターセットポインタ
 *	@retval	NULL			登録失敗
 *
 * 
 */
//-----------------------------------------------------------------------------
BLACT_SET_PTR BLACT_InitSet(const BLACT_SETDATA* pSetData)
{
	BLACT_SET* set;
	
	// テーブルから空いているアクターセットを取得
	set = getCleanBlActSet();

	if(set == NULL){
		GF_ASSERT_MSG( 0, "登録できるアクターセットがありません。\n BLACT_InitSysの第１引数の数を増やしてください\n" );
		return NULL;
	}

	// 各データ領域を作成
	set->SysFlag = 1;		// 登録
	set->DrawFlag = 1;		// 描画
	
	// アクターワーク
	set->pWork = sys_AllocMemory(pSetData->heap, sizeof(BLACT_WORK)*pSetData->WorkNum);
	set->WorkNum = pSetData->WorkNum;
	
	// リストダミーデータ
	BLACT_WorkClear(&set->Dummy);
	set->Dummy.next = &set->Dummy;
	set->Dummy.prev = &set->Dummy;
	
	// スタック
	set->ppWorkStack = sys_AllocMemory(pSetData->heap, sizeof(BLACT_WORK*)*pSetData->WorkNum);
	initStack(set);
	
	// アロケータ作成
	set->pAlloc = sys_AllocMemory(pSetData->heap, sizeof(NNSFndAllocator));
	sys_InitAllocator(set->pAlloc, pSetData->heap,4);
	// ITPVram転送アニメを作成
	set->pItpTop = initItpVramAnm(pSetData->WorkNum, pSetData->heap);

	return set;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	ビルボードアクターセット破棄
 *
 *	@param	bl_set			アクターセットポインタ
 *
 *	@retval	TRUE			成功
 *	@retval	FALSE			失敗
 *
 * 
 */
//-----------------------------------------------------------------------------
BOOL BLACT_DestSet(BLACT_SET_PTR bl_set)
{
	// ビルボードアクターセット取得
	if(bl_set == NULL){
		GF_ASSERT_MSG( 0, "NULLです\n" );
		return FALSE;
	}

	if(bl_set->SysFlag != 0){
		// ビルボード完全破棄
		BLACT_DeleteWorkAllSet(bl_set);

		// 管理データ破棄
		sys_FreeMemoryEz(bl_set->pWork);
		sys_FreeMemoryEz(bl_set->ppWorkStack);
		sys_FreeMemoryEz(bl_set->pAlloc);
		destItpVramAnm(bl_set->pItpTop);

		cleanBlActSet(bl_set);
	}

	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	ビルボードアクターセット描画フラグを設定
 *
 *	@param	bl_set			アクターセットポインタ	
 *	@param	flag			設定するフラグ値	0:非描画 1:描画
 *
 *	@retval	TRUE			成功
 *	@retval	FALSE			失敗
 *
 * 
 */
//-----------------------------------------------------------------------------
BOOL BLACT_DrawFlagSet(BLACT_SET_PTR bl_set, u8 flag)
{
	// ビルボードアクターセット取得
	if(bl_set == NULL){
		GF_ASSERT_MSG( 0, "NULLです\n" );
		return FALSE;
	}

	if(bl_set->SysFlag != 0){
		bl_set->DrawFlag = flag;
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ビルボードアクターセットの描画フラグを取得
 *
 *@param	bl_set		アクターセットポインタ	
 *
 *@return	u8			1:描画		0:非描画
 *
 *
 */
//-----------------------------------------------------------------------------
u8 BLACT_DrawFlagGet(CONST_BLACT_SET_PTR bl_set)
{
	if(bl_set == NULL){
		GF_ASSERT_MSG( 0, "NULLです\n" );
		return 0;
	}

	if(bl_set->SysFlag != 0){
		return bl_set->DrawFlag;
	}

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	ビルボードアクターセットの全ビルボード破棄
 *	
 *	@param	bl_set			アクターセットポインタ
 *
 *	@retval	TRUE			成功
 *	@retval	FALSE			失敗
 *
 */
//-----------------------------------------------------------------------------
BOOL BLACT_DeleteWorkAllSet(BLACT_SET_PTR bl_set)
{
	BLACT_WORK*	roop;
	BLACT_WORK*	next;
	
	// ビルボードアクターセット取得
	if(bl_set == NULL){
		GF_ASSERT_MSG(bl_set, "NULLです\n");
		return FALSE;
	}

	if(bl_set->SysFlag != 0){
			
		// リストのデータ全破棄
		roop = bl_set->Dummy.next;
		while(roop != &bl_set->Dummy){
			next = roop->next;
			// 破棄
			BLACT_Delete(roop);
			roop = next;
		}
		
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	破棄したオブジェクトがまだ画面に反映されているかチェック
 *	
 *	@param	bl_set	アクターセット
 *
 *	@retval	TRUE	反映されている
 *	@retval	FALSE	反映されていない
 */
//-----------------------------------------------------------------------------
BOOL BLACT_DelObjRefCheck( BLACT_SET_PTR bl_set )
{
	GF_ASSERT( bl_set );
	if( bl_set->DelObjDrawRef == BLACT_DRAW_REF_NONE ){
		return FALSE;
	}
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ビルボードアクターVブランク処理
 *
 *	@param	act		ワーク
 */
//-----------------------------------------------------------------------------
void BLACT_VBlankFunc( BLACT_SET_PTR bl_set )
{
	// VBlankにきたので、スワップバッファが行われ
	// 今まで破棄したのに描画されていたポリゴンが消える
	if( bl_set->DelObjDrawRef == BLACT_DRAW_REF_DRAW_AFTER ){
		bl_set->DelObjDrawRef = BLACT_DRAW_REF_NONE;
	}
}


//=============================================================================
//
//		ビルボードアクターセット操作プライベート関数郡
//
//=============================================================================
//-----------------------------------------------------------------------------
/**
 *
 *	@brief	空いているビルボードアクターセット取得
 *
 *	@param	none
 *
 *	@retval	BLACT_SET_PTR	アクターセットポインタ
 *	@retval	NULL			失敗
 *
 * 
 */
//-----------------------------------------------------------------------------
static BLACT_SET_PTR getCleanBlActSet(void)
{
	int i;		// ループ用

	for(i=0;i<BlActSetNum;i++){
		if(pBlActSetTbl[i].SysFlag == 0){
			return &pBlActSetTbl[i];
		}
	}

	return NULL;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	ビルボードアクターセットの描画
 *
 *	@param	pBlActSet	描画するビルボードアクターセット
 *	@return	none
 *
 * ビルボードアクターセットに登録されたアクターを描画します
 *
 */
//-----------------------------------------------------------------------------
static void drawBlActSet( BLACT_SET* pBlActSet )
{
	BLACT_WORK* roop;		// ループ用
	MtxFx33 rot;				// 回転行列
	VecFx32	matrix;				// 絶対座標＋相対座標

	GF_ASSERT( pBlActSet );
	
	// 回転行列を単位行列にする
	MTX_Identity33( &rot );
	
	roop = pBlActSet->Dummy.next;
	while(roop != &pBlActSet->Dummy){
		
		if(roop->draw == 1){		// 表示するかチェック
			
			// テクスチャバインド
			DrawTexBind(roop);
	
			// 各アニメーションの更新処理
			// 描画関数なのに描画以外のことを行うのは良くないですが、
			// バインドしたデータに行う必要があるため
			// ここで行います
			if(roop->flag == BLACT_MOVE_NORM){
				//常駐アニメテクスチャ・パレット参照先設定
				normAnmTexDataSet( roop );
			}else{
				if(roop->flag == BLACT_MOVE_VRAM){
					BLACT_VramAnmTransUserReq( roop );
				}
			}
			
			// 描画
			simple_3DModelDraw(
					&roop->RenderObj,		// レンダーオブジェ
					&roop->Matrix,			// 座標
					&rot,					// 回転行列
					&roop->Scale);			// 拡縮
			
			// テクスチャリバインド
			DrawTexreBind(roop);
			
		}
		roop = roop->next;
	}
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	ビルボードアクター描画
 *
 *	@param	act		描画するビルボードアクター
 *	@return	none
 *
 * アクターを描画します
 *
 */
//-----------------------------------------------------------------------------
static void drawBlAct( BLACT_WORK *act )
{
	MtxFx33 rot;				// 回転行列
	VecFx32	matrix;				// 絶対座標＋相対座標

	GF_ASSERT( act );
	MTX_Identity33( &rot );
	
	if( act->draw == FALSE ){
		return;
	}
	
	DrawTexBind( act );
	
	if( act->flag == BLACT_MOVE_NORM){
		normAnmTexDataSet( act );
	}else if( act->flag == BLACT_MOVE_VRAM ){
		transItpVramAnm( act->ItpVramObj, act->frame );
	}
	
	simple_3DModelDraw( &act->RenderObj, &act->Matrix, &rot, &act->Scale );
	DrawTexreBind( act );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	Vram転送時用　データチェンジデータ格納関数
 *
 *	@param	act			ビルボードアクター
 *	@param	header		ヘッダーデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void chgBillboadAnmSet_Core_VRAM( BLACT_WORK* act, const BLACT_HEADER* header )
{
	BLACT_SET*	as;	// アクターセット

	// 自分の親のビルボードセット代入
	as = (BLACT_SET*)act->pBlActSet;		

	// 今までのアニメデータ破棄
	del_blact(as, act);

	// 新しいリソースをレンダーオブジェに関連付ける
	// モデルリソース
	// 内部でVramKeyの取得も行う
	data_chg_vram_mdl_core(act, header);
	
	// Ｖｒａｍ転送マネージャーにリストを追加
	data_chg_vram_anm_core(as, act, header);

	if(act->flag == BLACT_MOVE_INIT){
		// リストに設定
		setList(&as->Dummy, act);
	}

	// 実行モードを設定
	act->flag = BLACT_MOVE_VRAM;

	// アニメーションテーブル設定
	act->pAnmTbl	= header->anm;

	// アニメーションオフセットと、フレーム数をセット
	act->AnmOffs		= 0;
	act->frame			= 0;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	常駐アニメのアニメーションセットを変更する関数
 *
 *	@param	blact_w		ビルボードワーク
 *	@param	header		ヘッダー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void core_anmset_chg_norm( BLACT_WORK* blact_w, const BLACT_HEADER* header)
{
	BLACT_SET* pBlActSet = blact_w->pBlActSet;

	// 今までのデータを破棄	
	// モデルリソースを解放
	del_blact(pBlActSet, blact_w);

	// Vram転送モードの時はビルボードアクターが
	// Vramを確保しているのでビルボードアクター内で破棄する
	if(blact_w->flag == BLACT_MOVE_VRAM){
		// VramKeyを破棄
		delBindTexture( &blact_w->texKey, &blact_w->tex4x4Key, &blact_w->plttKey );
	}

	// データを設定
	// モデルデータ　アニメデータ　VramKeyの設定
	// VramKeyを設定
	blact_w->texKey		= header->texKey;
	blact_w->tex4x4Key	= header->tex4x4Key;
	blact_w->plttKey	= header->plttKey;

	// モデルリソースをレンダーオブジェに設定
	data_chg_norm_mdl_core( blact_w, header );

	// アニメーションオブジェを構築し、レンダーオブジェに登録
	data_chg_norm_anm_core( blact_w, header );


	if(blact_w->flag == BLACT_MOVE_INIT){
		// リストに設定
		setList(&pBlActSet->Dummy, blact_w);
	}


	// 実行モードを設定
	blact_w->flag = BLACT_MOVE_NORM;

	// アニメーションテーブル設定
	blact_w->pAnmTbl	= header->anm;

	// アニメーションオフセットと、フレーム数をセット
	blact_w->AnmOffs		= 0;
	blact_w->frame			= 0;
}


//----------------------------------------------------------------------------
//
//
//	アニメーションセット変更関数のコア関数郡
//
//
//============================================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	テクスチャキー領域をVramマネージャーから確保する
 *
 *@param	tex			テクスチャリソース
 *@param	texkey		テクスチャキー
 *@param	tex4x4key	4x4圧縮テクスチャキー
 *@param	plttkey		パレットキー
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void allocTexKey(const NNSG3dResTex* tex, NNSG3dTexKey* texkey, NNSG3dTexKey* tex4x4key, NNSG3dPlttKey* plttkey)
{
    u32 szTex, szTex4x4, szPltt;
	

	// 必要なサイズを取得
	szTex    = NNS_G3dTexGetRequiredSize(tex);
	szTex4x4 = NNS_G3dTex4x4GetRequiredSize(tex);
	szPltt   = NNS_G3dPlttGetRequiredSize(tex);

	if (szTex > 0){
		// 存在すればテクスチャイメージスロットに確保
		*texkey = NNS_GfdAllocTexVram(szTex, FALSE, 0);
		GF_ASSERT(*texkey != BLACT_TEXKEY_VRAMANM);
//		OS_Printf( "tex addr %x size %x\n", NNS_GfdGetTexKeyAddr(*texkey), NNS_GfdGetTexKeySize(*texkey) );
	}else{
		*texkey = 0;
	}

	if (szTex4x4 > 0){
		// 存在すればテクスチャイメージスロットに確保
		*tex4x4key = NNS_GfdAllocTexVram(szTex4x4, TRUE, 0);
		GF_ASSERT(*tex4x4key != BLACT_TEXKEY_VRAMANM);
//		OS_Printf( "4x4tex addr %x size %x\n", NNS_GfdGetTexKeyAddr(*tex4x4key), NNS_GfdGetTexKeySize(*tex4x4key) );
	}else{
		*tex4x4key = 0;
	}

	if (szPltt > 0){
		// 存在すればテクスチャパレットスロットに確保
		*plttkey = NNS_GfdAllocPlttVram(szPltt,
							tex->tex4x4Info.flag & NNS_G3D_RESPLTT_USEPLTT4,
							0);
		GF_ASSERT(*plttkey != BLACT_PLTTKEY_VRAMANM);
//		OS_Printf( "pltt addr %x size %x\n", NNS_GfdGetPlttKeyAddr(*plttkey), NNS_GfdGetPlttKeySize(*plttkey) );
	}else{
		*plttkey = 0;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	テクスチャにバインドされているVramキーを解除する
 *
 *@param	tex			テクスチャ
 *@param	texkey		通常テクスチャキー
 *@param	tex4x4key	4x4圧縮テクスチャキー
 *@param	plttkey		パレットキー
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void releaseTexture(NNSG3dResTex* tex, NNSG3dTexKey* texkey, NNSG3dTexKey* tex4x4key, NNSG3dPlttKey* plttkey)
{
	// 解放
	NNS_G3dTexReleaseTexKey( tex, texkey, tex4x4key );
	*plttkey = NNS_G3dPlttReleasePlttKey( tex );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	テクスチャキーの再設定
 *
 *@param	tex			テクスチャリース
 *@param	mdl			モデルリソースセット
 *@param	texkey		通常テクスチャキー
 *@param	tex4x4key	4x4圧縮テクスチャキー
 *@param	plttkey		パレットキー
 * 
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void reBindTexture(NNSG3dResTex* tex, NNSG3dResMdlSet* mdl, NNSG3dTexKey* texkey, NNSG3dTexKey* tex4x4key, NNSG3dPlttKey* plttkey)
{
	// テクスチャキー
	NNS_G3dTexSetTexKey( tex, *texkey, *tex4x4key );
	// パレットキー
	NNS_G3dPlttSetPlttKey( tex, *plttkey );

	// バインド
	// モデルセットのバインド
	NNS_G3dBindMdlSet(mdl, tex);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	テクスチャキーを破棄する
 *
 *@param	texkey		通常テクスチャキー
 *@param	tex4x4key	4x4圧縮テクスチャキー
 *@param	plttkey		パレットキー
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void delBindTexture(NNSG3dTexKey* texkey, NNSG3dTexKey* tex4x4key, NNSG3dPlttKey* plttkey)
{
	if(*texkey != BLACT_TEXKEY_VRAMANM){
		NNS_GfdFreeTexVram( *texkey );
	}
	if(*tex4x4key != BLACT_TEXKEY_VRAMANM){
		NNS_GfdFreeTexVram( *tex4x4key );
	}
	if(*plttkey != BLACT_PLTTKEY_VRAMANM){
		NNS_GfdFreePlttVram( *plttkey );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	テクスチャサイズが等しいかチェックする
 *
 *@param	tex		チェックするテクスチャリソース
 *
 *@retval	TRUE	等しい
 *@retval	FALSE	等しくない
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL check_texsize_equal(const NNSG3dResTex* tex1, const NNSG3dResTex* tex2)
{
	u32 szTex0, szTex4x40, szPltt0;		// 各サイズ
	u32 szTex1, szTex4x41, szPltt1;		// 各サイズ
	BOOL ret;

	if((tex1 == NULL) || (tex2 == NULL)){
		return FALSE;
	}
	
	szTex0    = NNS_G3dTexGetRequiredSize(tex1);  
	szTex4x40 = NNS_G3dTex4x4GetRequiredSize(tex1);
	szPltt0   = NNS_G3dPlttGetRequiredSize(tex1);

	szTex1    = NNS_G3dTexGetRequiredSize(tex2);  
	szTex4x41 = NNS_G3dTex4x4GetRequiredSize(tex2);
	szPltt1   = NNS_G3dPlttGetRequiredSize(tex2);

	// サイズが違うかチェック
	if( (szTex0 != szTex1) || (szTex4x40 != szTex4x41) || (szPltt0 != szPltt1) ){
		ret = FALSE;		// 等しくない
	}else{
		ret = TRUE;			// 等しい
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ビルボードアクター破棄処理
 *
 *@param	pBlActSet	ビルボードアクターセット
 *@param	delWork		破棄するビルボードアクター
 *
 * 完全に破棄するときは
 *	この後ワークをスタックにプッシュする必要がある。
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void del_blact(BLACT_SET* pBlActSet, BLACT_WORK* delWork)
{

	if(delWork->ItpVramObj){
		// Ｖｒａｍ転送アニメリストから破棄
		remItpVramAnm( delWork->ItpVramObj );
		delWork->ItpVramObj = NULL;
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	モデルデータをワークに設定
 *
 *@param	blact_w			データ格納先ワーク
 *@param	header			ヘッダー
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void data_chg_vram_mdl_core(BLACT_WORK* blact_w, const BLACT_HEADER* header)
{
	NNSG3dResTex* old_tex;
	int	result;

	// テクスチャのサイズが違うかをチェックするため
	// 古いテクスチャを保存
	old_tex = blact_w->pMdlTex;	

	// ビルボードのデータをリソースマネージャーから取得	
	blact_w->pModelSet = blact_getMdl(	// モデルリソースセット取得
			header,					// ヘッダー
			&blact_w->pModel,		// モデルリソース
			&blact_w->pMdlTex);		// テクスチャリソース
	
	NNS_G3dRenderObjInit( &blact_w->RenderObj, blact_w->pModel );	// レンダーオブジェ初期化

	// 古いテクスチャと比べ、VramKeyを変える必要があるかチェック
	// 前が常駐アニメのときは無条件にVramKeyを取得する
	if(blact_w->flag != BLACT_MOVE_NORM){
		
		result = check_texsize_equal(old_tex, blact_w->pMdlTex);
	}else{
		result = FALSE;
	}
	if(result == FALSE){	// resultがFALSEならVramKeyの再取得

		// 前もVram転送なら今のVramKeyを破棄
		if( blact_w->flag == BLACT_MOVE_VRAM ){
			delBindTexture(
					&(blact_w->texKey),
					&(blact_w->tex4x4Key),
					&(blact_w->plttKey) );
		}
		allocTexKey(
				blact_w->pMdlTex,
				&(blact_w->texKey),
				&(blact_w->tex4x4Key),
				&(blact_w->plttKey) );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	テクスチャパターンアニメーション
 *
 *@param	pBlActSet		ビルボードアクターセット
 *@param	blact_w			データ格納先ワーク 
 *@param	header			ヘッダー
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void data_chg_vram_anm_core(const BLACT_SET* pBlActSet, BLACT_WORK* blact_w, const BLACT_HEADER* header)
{
	
	// パターンのテクスチャ取得
	blact_w->pAnmTex = blact_getTex(
			header );

//	OS_Printf( "tex %x \n",NNS_G3dTexGetRequiredSize(p_tex) );

	// テクスチャアニメーションデータを設定
	blact_w->texAnm = header->texanm;

	// Vram転送アニメーションかチェック
	// Ｖｒａｍ転送アニメーションシステムにセット
	blact_w->ItpVramObj = addItpVramAnm( 
				pBlActSet->pItpTop,
				&blact_w->texAnm,		// アニメーションデータテーブル
				blact_w->pAnmTex,		// テクスチャ
				blact_w->texKey,		// テクスチャデータ転送VramKey
				blact_w->plttKey,		// パレットデータ転送VramKey
				blact_w->frame			// フレーム値
				);		

}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	常駐アニメ用モデルデータ作成
 *
 *	@param	blact_w		ビルボードワーク
 *	@param	header		ヘッダー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void data_chg_norm_mdl_core(BLACT_WORK* blact_w, const BLACT_HEADER* header)
{
	// ビルボードのデータをリソースマネージャーから取得	
	blact_w->pModelSet = blact_getMdl(	// モデルリソースセット取得
			header,						// ヘッダー
			&blact_w->pModel,			// モデルリソース
			&blact_w->pMdlTex );		// バインド用テクスチャリソース

	NNS_G3dRenderObjInit( &blact_w->RenderObj, blact_w->pModel );	// レンダーオブジェ初期化

	// アニメーション用テクスチャ取得
	blact_w->pAnmTex = blact_getTex(
			header );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	常駐アニメ用アニメーションオブジェ初期化関数
 *
 *	@param	blact_w		ビルボードワーク
 *	@param	header		ヘッダー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void data_chg_norm_anm_core(BLACT_WORK* blact_w, const BLACT_HEADER* header)
{
	// テクスチャアニメーションデータを設定
	blact_w->texAnm = header->texanm;

	// Vram転送アニメマネージャにNULLを設定
	blact_w->ItpVramObj = NULL;
}

//=============================================================================
//
//		ビルボードアクターワーク操作関数郡
//
//		ビルボードアクター　個々を操作する
//
//=============================================================================
//-----------------------------------------------------------------------------
/**
 *
 *	@brief	ビルボードアクターの追加
 *
 *	@param	add		ビルボードアクター登録データ
 *
 *	@retval BLACT_WORK_PTR	登録したワークのポインタ
 *	@retval	NULL			失敗
 *	
 */
//-----------------------------------------------------------------------------
BLACT_WORK_PTR BLACT_Add(const BLACT_ADD* add)
{
	BLACT_WORK*	bl_w;		// 登録するビルボードワーク
	BLACT_SET*	bs;			// ビルボードアクターセット

	// ビルボードアクターセット取得
	if(add->blact_s == NULL){
		return NULL;
	}

	bs = add->blact_s;

	// スタックから取得
	bl_w = popStack(bs);
	if(bl_w == NULL){
		return NULL;
	}

	// ビルボードアクター動作構造体配列にデータを登録
	bl_w->pBlActSet	= bs;					// アクターセット
	bl_w->Matrix	= add->matrix;			// 相対座標
	bl_w->Scale		= add->scale;			// 拡縮
	bl_w->AnmOffs	= 0;					// 今のアニメーションオフセット
	bl_w->draw		= 1;					// 表示

	// フラグを初期化中にする
	bl_w->flag = BLACT_MOVE_INIT;	// 初期化中

	// ここでの読み込みはできないのでアニメーションセットチェンジシステムに頼む
	chgBillboadAnmSet_Core( bl_w, add->pHeader );
	

	return bl_w;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	ビルボードアクターの削除
 *
 *	@param	del		破棄するビルボードアクター動作構造体
 *
 *	@retval	TRUE	成功(BOOL型：削除に成功したか)
 *	@retval	FALSE	失敗
 *
 */
//-----------------------------------------------------------------------------
BOOL BLACT_Delete(BLACT_WORK* del)
{
	BLACT_SET* as;	// アクターセット

	GF_ASSERT(del);

	// 初期化処理中に直ぐに破棄されたときはアサートを出す
	GF_ASSERT_MSG(del->flag != BLACT_MOVE_INIT,
			"初期化して直ぐの破棄は出来ません。");		

	as = (BLACT_SET*)del->pBlActSet;		// アクターセット代入
	

	// データがあるのかチェック
	if( (del->flag == BLACT_MOVE_NONE) ){
		return FALSE;
	}

	// リストから破棄
	remList(del);

	// Vram転送モードの時は
	// ビルボードアクターがVramKeyを取得しているので
	// テクスチャ解放
	if( del->flag == BLACT_MOVE_VRAM ){
		delBindTexture(&(del->texKey), &(del->tex4x4Key), &(del->plttKey));
	}
	
	// 今までのデータを破棄	
	// モデルリソースを解放
	del_blact(as, del);
	
	// スタックにプッシュ
	pushStack(as, del);

	// 破棄したが、次の描画までは残っている
	as->DelObjDrawRef = BLACT_DRAW_REF_DRAW_BEFORE;

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 * 
 *	@brief	常駐アニメ用　ビルボードアクターヘッダーデータ作成支援関数
 *
 *	@param	p_header		ビルボードアクターヘッダーデータ格納先
 *	@param	p_imd			ビルボードモデルリソース
 *	@param	cp_itx			アニメーションテクスチャリソース
 *	@param	cp_anm			アニメーションテーブル
 *	@param	cp_texanm		テクスチャアニメーションデータテーブル
 *	@param	texkey			テクスチャキー
 *	@param	tex4x4key		4x4圧縮テクスチャキー
 *	@param	plttkey			パレットキー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void BLACT_MakeHeaderNormalAnm( BLACT_HEADER* p_header, void* p_imd, const NNSG3dResTex* cp_itx, const BLACT_ANIME_TBL* cp_anm, const TEXANM_DATATBL* cp_texanm, NNSGfdTexKey texkey, NNSGfdTexKey tex4x4key, NNSGfdPlttKey plttkey  )
{
	p_header->ImdRes	= p_imd;
	p_header->ItxRes	= cp_itx;
	p_header->anm		= cp_anm;
	p_header->texanm	= *cp_texanm;
	p_header->texKey	= texkey;
	p_header->tex4x4Key	= tex4x4key;
	p_header->plttKey	= plttkey;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	Vram転送アニメ用　ビルボードアクターヘッダーデータ作成支援関数
 *
 *	@param	p_header		ビルボードアクターヘッダーデータ格納先
 *	@param	p_imd			ビルボードモデルリソース
 *	@param	cp_itx			アニメーションテクスチャリソース
 *	@param	cp_anm			アニメーションテーブル
 *	@param	cp_texanm		テクスチャアニメーションデータテーブル
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void BLACT_MakeHeaderVramAnm( BLACT_HEADER* p_header, void* p_imd, const NNSG3dResTex* cp_itx, const BLACT_ANIME_TBL* cp_anm, const TEXANM_DATATBL* cp_texanm )
{
	p_header->ImdRes	= p_imd;
	p_header->ItxRes	= cp_itx;
	p_header->anm		= cp_anm;
	p_header->texanm	= *cp_texanm;
	p_header->texKey	= BLACT_TEXKEY_VRAMANM;
	p_header->tex4x4Key	= BLACT_TEXKEY_VRAMANM;
	p_header->plttKey	= BLACT_PLTTKEY_VRAMANM;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	座標を設定
 *
 *@param	act		設定するアクター
 *@param	mat		設定する座標
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void BLACT_MatrixSet(BLACT_WORK_PTR act, const VecFx32* mat)
{
	GF_ASSERT(act);
	act->Matrix = *mat;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	座標を取得
 *
 *@param	act		取得するアクター
 * 
 *@return	const VecFx32*	座標
 *
 */
//-----------------------------------------------------------------------------
const VecFx32* BLACT_MatrixGet(CONST_BLACT_WORK_PTR act)
{
	GF_ASSERT(act);
	return &act->Matrix;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	拡大値を設定する
 *
 *@param	act		設定するアクター
 *@param	sca		設定する拡大値
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void BLACT_ScaleSet(BLACT_WORK_PTR act, const VecFx32* sca)
{
	GF_ASSERT(act);

	act->Scale = *sca;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	拡大値を取得する
 *
 *@param	act		取得するアクター
 *
 *@return	const VecFx32*	拡大値
 *
 *
 */
//-----------------------------------------------------------------------------
const VecFx32* BLACT_ScaleGet(CONST_BLACT_WORK_PTR act)
{
	GF_ASSERT(act);
	return &act->Scale;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	描画フラグを設定する
 *
 *@param	act		設定するアクター
 *@param	flag	描画フラグ	1:描画	0:非描画
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void BLACT_ObjDrawFlagSet(BLACT_WORK_PTR act, u8 flag)
{
	GF_ASSERT(act);

	act->draw = flag;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	描画フラグを取得する
 *
 *@param	act		取得するアクター
 *
 *@return	u8		1:描画	0:非描画
 *
 *
 */
//-----------------------------------------------------------------------------
u8 BLACT_ObjDrawFlagGet(CONST_BLACT_WORK_PTR act)
{
	GF_ASSERT(act);
	return act->draw;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	アニメーションを変える
 *			ここではタスクにデータをセットするだけです。
 *
 *							
 *	@param	act			チェンジする動作配列
 *	@param	header		チェンジするアニメーションヘッダー
 *
 *	@return none
 *
 *	・登録してまだBLACT_AfterDrawSysを通っていないアクターには使用できません
 *	・実際の変更処理はBLACT_AfterDrawSys関数で行われます。
 * 
 */
//-----------------------------------------------------------------------------
void BLACT_AnmSetChg( BLACT_WORK* act, const BLACT_HEADER* header )
{
	GF_ASSERT(act);
	
	// アニメーションセットを変更
	chgBillboadAnmSet_Core( act, header );
}

//-----------------------------------------------------------------------------
/**
 *
 *@brief	アニメーションオフセットを変更
 *
 *@param	act		チェンジする動作配列
 *@param	num		セットするアニメーションオフセットナンバー
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void BLACT_AnmOffsChg( BLACT_WORK_PTR act, int num )
{
	GF_ASSERT(act);

	// アニメーションオフセットを代入する
	act->AnmOffs = num;
}


//-----------------------------------------------------------------------------
/**
 *
 *@brief	アニメーションオフセットを変更と同時に変更を画面に反映
 *
 *@param	act		チェンジする動作配列
 *@param	num		セットするアニメーションオフセットナンバー
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void BLACT_AnmOffsChgRef( BLACT_WORK_PTR act, int num )
{
	BLACT_AnmOffsChg( act, num );
	BLACT_AnmFrameChg( act, FX32_ONE );	// 反映
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	アニメーションオフセットを取得
 *
 *@param	act		取得するアクター
 *
 *@return	int		アニメーションオフセット
 *
 *
 */
//-----------------------------------------------------------------------------
int BLACT_AnmOffsGet( CONST_BLACT_WORK_PTR act )
{
	GF_ASSERT(act);
	
	// ないので、今のアニメーションセットナンバーを返す
	return act->AnmOffs;
}

//----------------------------------------------------------------------------
/**
 *@brief	アニメーションフレームを動かす
 *						実際にアニメーションをループ再生するときに使用する
 *
 *@param	act		アニメーションさせる動作配列
 *@param	num		アニメーションスピード
 *
 *@retval	BLACT_ANISTA_LOOP	再生中
 *@retval	BLACT_ANISTA_END	再生終了
 */
//-----------------------------------------------------------------------------
int BLACT_AnmFrameChg( BLACT_WORK* act, fx32 num )
{
	GF_ASSERT(act);

	return anmFrameChg_Core( act, num );
}

//----------------------------------------------------------------------------
/**
 *@brief	アニメーションフレーム数を設定
 *
 *@param	act		アニメーションさせる動作配列
 *@param	num		設定するフレーム数
 *
 *@return	none
 */
//-----------------------------------------------------------------------------
void BLACT_AnmFrameSet( BLACT_WORK_PTR act, fx32 num )
{
	GF_ASSERT(act);
	act->frame = num;
}

//----------------------------------------------------------------------------
/**
 *@brief	アニメーションフレーム数を取得
 *
 *@param	act		アニメーションさせる動作配列
 *
 *@return	fx32	アニメーションフレーム数
 */
//-----------------------------------------------------------------------------
fx32 BLACT_AnmFrameGet( CONST_BLACT_WORK_PTR act )
{
	GF_ASSERT(act);
	
	// アニメーションオブジェクトのアニメーションフレームの値を返す
	return act->frame;
}

//----------------------------------------------------------------------------
/**
 *@brief	現在のオフセット開始フレームからのアニメーションフレーム数をセット
 *
 *@param	act		アニメーションさせる動作配列
 *@param	num		アニメーションスピード
 *
 *@return	none
 *
 *	アニメーションオフセットの開始フレーム+numのフレームをセットします。
 *	左アニメなら左アニメの開始フレーム+numのフレームがセットされます。 
 */
//-----------------------------------------------------------------------------
void BLACT_AnmFrameSetOffs( BLACT_WORK* act, fx32 num )
{
	GF_ASSERT(act);

	// アニメーションオブジェクトのアニメーションフレームの値をセット
	act->frame = nowOffsAnmStartFrame(act, act->AnmOffs);
	act->frame += num;
}

//----------------------------------------------------------------------------
/**
 *@brief	現在のオフセット開始フレームからのアニメーションフレーム数を取得
 *
 *@param	act		アニメーションさせる動作配列
 *
 *@return	fx32	アニメーションフレーム数
 *	実フレーム数 - 現在のアニメーションオフセット開始フレームの値を返します
 */
//-----------------------------------------------------------------------------
fx32 BLACT_AnmFrameGetOffs( CONST_BLACT_WORK_PTR act )
{
	GF_ASSERT(act);
	
	// アニメーションオブジェクトのアニメーションフレームの値を返す
	return act->frame - nowOffsAnmStartFrame(act, act->AnmOffs);
}

//----------------------------------------------------------------------------
/**
 *	@brief	IDのビルボードモデルリソースを取得
 *
 *	@param	pDat		モデルリソースを取得したいビルボードアクターワーク
 *
 *	@return NNSG3dResMdl* モデルリソース
 *
 */
//-----------------------------------------------------------------------------
NNSG3dResMdl* BLACT_MdlResGet(CONST_BLACT_WORK_PTR pDat)
{
	GF_ASSERT( pDat );
	
	return pDat->pModel;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ビルボードアクターワークのポインタを取得
 *
 *	@param	set			ビルボードアクターセット 
 *	@param	num			ビルボードアクターワークインデックス
 *
 *	@retval BLACT_WORK_PTR	ビルボードアクターワーク
 *	@retval	NULL			そのインデックスのワークは無い
 *
 */
//-----------------------------------------------------------------------------
BLACT_WORK_PTR BLACT_WorkGet(CONST_BLACT_SET_PTR set, int num)
{
	GF_ASSERT( set );

	return &set->pWork[num];
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	現在ビルボードアクターワークはどんな動作を行っているかを取得
 *
 *	@param	act		ビルボードアクターワーク
 *
 *	@retval	BLACT_MOVE_NONE			動作していない
 *	@retval BLACT_MOVE_INIT			初期化中
 *	@retval	BLACT_MOVE_VRAM			Vram転送稼動中
 *	@retval	BLACT_MOVE_NORM			常駐アニメ稼動中
 *
 */
//-----------------------------------------------------------------------------
int BLACT_GetState( CONST_BLACT_WORK_PTR act )
{
	GF_ASSERT(act);
	return act->flag;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	テクスチャキーの取得
 *
 *	@param	act ビルボードアクターワーク
 *
 *	@return	テクスチャキー
 *
 *
 */
//-----------------------------------------------------------------------------
NNSGfdTexKey BLACT_GetTexKey( CONST_BLACT_WORK_PTR act )
{
	GF_ASSERT( act );
	return act->texKey;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットキーの取得
 *
 *	@param	act ビルボードアクターワーク
 *
 *	@return	パレットキー
 *
 *
 */
//-----------------------------------------------------------------------------
NNSGfdPlttKey BLACT_GetPlttKey( CONST_BLACT_WORK_PTR act )
{
	GF_ASSERT( act );
	return act->plttKey;
}

//----------------------------------------------------------------------------
/**
 * ●常駐アニメーション用
 *
 *	@brief	テクスチャキーを設定する
 *
 *	@param	act		ビルボードアクターワーク
 *	@param	texkey	設定するテクスチャキー
 *
 *	@retval	TRUE	設定成功
 *	@retval	FALSE	設定失敗	（Vram転送アニメでは使用することが出来ないです）
 *
 *	これによりグラフィックデータを変更することが出来ます。
 *	ただし、元のグラフィックデータとテクスチャの構成（サイズ）が
 *	同じでないとちゃんとした絵がでません。
 *
 *	設定したtexKeyの解放は外側で管理してください。
 *
 */
//-----------------------------------------------------------------------------
BOOL BLACT_SetTexKey( BLACT_WORK_PTR act, const NNSGfdTexKey* texKey )
{
	GF_ASSERT( act );
	GF_ASSERT( texKey );

	if( act->flag == BLACT_MOVE_NORM ){
		act->texKey = *texKey;
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 * ●常駐アニメーション用
 *
 *	@brief	パレットキーを設定する
 *
 *	@param	act		ビルボードアクターワーク
 *	@param	plttkey	設定するパレットキー
 *
 *	@retval	TRUE	設定成功
 *	@retval	FALSE	設定失敗	（Vram転送アニメでは使用することが出来ないです）
 *
 *	これによりパレットを変更することが出来ます。
 *	ただし、元のパレットデータとパレットの構成（サイズ）が
 *	同じでないとちゃんとした絵がでません。
 *
 *	設定したplttKeyの解放は外側で管理してください。
 *
 */
//-----------------------------------------------------------------------------
BOOL BLACT_SetPlttKey( BLACT_WORK_PTR act, const NNSGfdPlttKey* plttKey )
{
	GF_ASSERT( act );
	GF_ASSERT( plttKey );

	if( act->flag == BLACT_MOVE_NORM ){
		act->plttKey = *plttKey;
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ビルボードアクターのカリングチェック
 *
 *	@param	act		アクター
 *
 *	@return	u32
 */
//-----------------------------------------------------------------------------
u32 BLACT_CullingCheck( BLACT_WORK_PTR act )
{
	MtxFx33 rot;
	
	//　回転行列初期化
	MTX_Identity33( &rot );
	
	return BB_CullingCheck3DModel( act->pModel, &act->Matrix, &rot, &act->Scale );
}


//----------------------------------------------------------------------------
/**
 *	@brief	Vram転送処理時、転送リクエスト
 *	@param	act		アクター
 */
//-----------------------------------------------------------------------------
void BLACT_VramAnmTransUserReq( BLACT_WORK_PTR act )
{
	if(act->flag == BLACT_MOVE_VRAM){
		// Vram転送実行(Vram転送モードのときのみ)
		transItpVramAnm(act->ItpVramObj, act->frame);
	}
}


//=============================================================================
//
//		プライベート関数郡
//
//=============================================================================
//-------------------------------------
//	常駐アニメ用システム
//=====================================
//----------------------------------------------------------------------------
/**
 *
 *	@brief	テクスチャ・パレット参照アドレスを設定
 *
 *	@param	act		ビルボードアクターデータ
 *
 *	@return	none
 *
 * (モデルにテクスチャがバインドされている必要があります)
 *
 */
//-----------------------------------------------------------------------------
static void normAnmTexDataSet( BLACT_WORK* act )
{
	TEXANM_DATA	texdata;		// 現在フレームのテクスチャインデックス　パレットインデックス

	// 現在のフレームのテクスチャ・パレットインデックス取得
	texdata = TEXANM_GetFrameData( &act->texAnm, act->frame >> FX32_SHIFT );

	// テクスチャアドレス設定
	// tex_idxのテクスチャのVramアドレスをモデルのマテリアルデータに設定
	normAnmTexParamSet( act->pModel, act->pAnmTex, texdata.tex_idx );

	// パレットアドレス設定
	// pltt_idxのパレットのVramアドレスをモデルのマテリアルデータに設定
	normAnmPlttParamSet( act->pModel, act->pAnmTex, texdata.pltt_idx );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	モデル内のバインドデータ郡分　テクスチャインデックスのテクスチャのVramアドレスを設定する
 *
 *	@param	p_mdl		モデルデータ
 *	@param	p_tex		テクスチャリソースデータ
 *	@param	tex_idx		テクスチャインデックス
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void normAnmTexParamSet( NNSG3dResMdl* p_mdl, const NNSG3dResTex* p_tex, u8 tex_idx )
{
	NNSG3dResMat*  mat;
    const NNSG3dResDict* dict_tex;
	const NNSG3dResDictTexToMatIdxData* data;
	const NNSG3dResDictTexData* texdict_data;
	u32	tex_offs;			// テクスチャのオフセットナンバー
	int i;

	// 必要なマテリアルデータ
	// テクスチャバインド用マテリアル列辞書を取得
    mat     = NNS_G3dGetMat(p_mdl);
    dict_tex = (NNSG3dResDict*)((u8*)mat + mat->ofsDictTexToMatList);

	// テクスチャオフセットをテクスチャリソース辞書から取得
	texdict_data = NNS_G3dGetTexDataByIdx( p_tex, tex_idx );
	tex_offs = (texdict_data->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK);
    
    // モデルリソースのテクスチャ名->マテリアルインデックス列辞書内の
    // それぞれに対してループを回す
    for (i = 0; i < dict_tex->numEntry; ++i){

		// i番目のテクスチャに関するバインドデータを取得
		data = (NNSG3dResDictTexToMatIdxData*) NNS_G3dGetResDataByIdx(dict_tex, i);

		// バインドされた状態のときのみ
		// テクスチャアドレスを設定
		if ((data->flag & 1)){
			
			// バインドされているときはモデルデータ内のマテリアルー＞TexImageParamの中にVramKeyアドレスが入っている
			normAnmTexParamSetOneMatData(mat, data, tex_offs );
		}
    }
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	バインド情報内のマテリアルデータ数分　テクスチャインデックスのテクスチャVramアドレスを設定する
 *
 *	@param	pMat			マテリアルデータ郡
 *	@param	pBindData		バインド情報
 *	@param	tex_offs		テクスチャオフセット
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void normAnmTexParamSetOneMatData( NNSG3dResMat* pMat, const	NNSG3dResDictTexToMatIdxData* pBindData, u32 tex_offs )
{
	u8* p_matidx;	// マテリアルデータインデックス配列
	int i;			// ループ用
	NNSG3dResMatData* mat_data;	// マテリアルデータ

	// マテリアルデータインデックス配列取得
	p_matidx = (u8*)pMat + pBindData->offset;
	
	// マテリアルデータ分テクスチャアドレスを設定
    for (i = 0; i < pBindData->numIdx; i++){
		
        // 各mat_dataにテクスチャ情報をセットアップしていく。
        mat_data = NNS_G3dGetMatDataByIdx(pMat, *(p_matidx + i));
		
		// 先頭からのオフセット値がoverフローしないかチェック
		GF_ASSERT( ((mat_data->texImageParam & NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK) + tex_offs) <= NNS_G3D_TEXIMAGE_PARAM_TEX_ADDR_MASK );
		
        mat_data->texImageParam += tex_offs;
    }
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	モデル内のバインドデータ郡分　パレットアドレスを設定する
 *
 *	@param	p_mdl		モデルリソース
 *	@param	p_tex		テクスチャリソース
 *	@param	pltt_idx	パレットデータインデックス
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void normAnmPlttParamSet( NNSG3dResMdl* p_mdl, const NNSG3dResTex* p_tex, u8 pltt_idx )
{
    NNSG3dResMat*  mat;
    const NNSG3dResDict* dict_pltt;
	const NNSG3dResDictPlttToMatIdxData* data;
	const NNSG3dResDictPlttData* plttdict_data;
	u32	pltt_offs;			// パレットのオフセットナンバー
    u32 i;

	// モデルマテリアルデータにあるパレットバインドデータを取得
    mat      = NNS_G3dGetMat(p_mdl);
    dict_pltt = (NNSG3dResDict*)((u8*)mat + mat->ofsDictPlttToMatList);

	// テクスチャデータからパレットインデックスナンバーの
	// 時の先頭からのデータオフセットを取得
	// オフセット値は4bit右にシフトした状態で入っているが、
	// 4色カラーパレット以外のときは3bit右シフトした値にする必要がある
	plttdict_data = NNS_G3dGetPlttDataByIdx( p_tex, pltt_idx );
	pltt_offs = plttdict_data->offset;
	if( !(plttdict_data->flag & 1) ){		// 4色カラーパレットの時は1bitがたっている
		pltt_offs >>= 1;
	}

    for (i = 0; i < dict_pltt->numEntry; ++i){
		
		// パレットバインドデータ取得
		data = (NNSG3dResDictPlttToMatIdxData*) NNS_G3dGetResDataByIdx(dict_pltt, i);

		// バインドされているときは変更
		if ((data->flag & 1)){
			
			// バインドされているときはPlttBaseの中にVramKeyアドレスが入っている
			normAnmPlttParamSetOneMatData( mat, data, pltt_offs );
		}
    }
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	バインドデータ内のマテリアルデータ数分パレットオフセットを設定
 *
 *	@param	pMat			マテリアルデータ郡
 *	@param	pBindData		バインド情報
 *	@param	pltt_offs		パレットオフセット 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void normAnmPlttParamSetOneMatData( NNSG3dResMat* pMat, const NNSG3dResDictPlttToMatIdxData* pBindData, u32 pltt_offs )
{
    u8* matdata_idx;
    u32 i;

	// マテリアルデータインデックス配列取得
    matdata_idx = (u8*)pMat + pBindData->offset;
	
	// バインド情報のデータ数分
	// マテリアルデータのパレットアドレスを設定
    for (i = 0; i < pBindData->numIdx; i++) {
        // 各matDataにパレット情報をセットアップしていく。
        NNSG3dResMatData* matData = NNS_G3dGetMatDataByIdx(pMat, *(matdata_idx + i));
		
		// overフローしないかチェック
		GF_ASSERT( ((matData->texPlttBase & BLACT_PLTT_BASE_MASK) + pltt_offs) <= BLACT_PLTT_BASE_MASK );
		
        matData->texPlttBase += pltt_offs;
    }
}


//-------------------------------------
//	stackの処理
//=====================================
//-----------------------------------------------------------------------------
/**
 *
 *	@brief	スタック初期化
 *
 *	@param	pSet		スタックデータ格納先
 *	@return none
 *
 */
//-----------------------------------------------------------------------------
static void initStack(BLACT_SET* pSet)
{
	int i;

	// 初期化
	for (i=0; i<pSet->WorkNum; i++) {
		BLACT_WorkClear(&pSet->pWork[i]);
		pSet->ppWorkStack[i] = pSet->pWork + i;
	}
	pSet->WorkStackNow = 0;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	スタックから取り出し
 *
 *	@param	pSet		スタックデータ格納先
 *	
 *	@retval	NULL以外	ビルボードワーク
 *	@retval	NULL		取り出しに失敗（スタックが空だった場合）
 *
 */
//-----------------------------------------------------------------------------
static BLACT_WORK* popStack(BLACT_SET* pSet)
{
	BLACT_WORK*	ret;

	// リミットチェック
	if(pSet->WorkStackNow >= pSet->WorkNum){
		return NULL;
	}

	ret = pSet->ppWorkStack[pSet->WorkStackNow];
	pSet->WorkStackNow++;

	return ret;
}

//-----------------------------------------------------------------------------
/**
 *
 *	@brief	スタックに格納
 *
 *	@param	pSet		スタックデータ格納先
 *	@param	pDat		格納データ
 *	
 *	@retval	TRUE		成功
 *	@retval	FALSE		スタックいっぱい
 */
//-----------------------------------------------------------------------------
static BOOL pushStack(BLACT_SET* pSet, BLACT_WORK* pDat)
{
	if(pSet->WorkStackNow <= 0){	// 空きチェック
		return FALSE;
	}
	BLACT_WorkClear(pDat);
	pSet->WorkStackNow--;
	pSet->ppWorkStack[pSet->WorkStackNow] = pDat;

	return TRUE;
}

//-------------------------------------
//	リスト管理
//=====================================
//-----------------------------------------------------------------------------
/**
 *
 *	@brief	リストに設定
 *
 *	@param	pDummy		先頭データ
 *	@param	pDat		設定データ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setList(BLACT_WORK* pDummy, BLACT_WORK* pDat)
{
	pDat->prev				= pDummy->prev;
	pDummy->prev->next		= pDat;
	pDat->next				= pDummy;
	pDummy->prev			= pDat;
}

static void remList(BLACT_WORK* pDat)
{
	// リストを外す
	pDat->prev->next = pDat->next;
	pDat->next->prev = pDat->prev;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	モデルリソースを取得する
 *
 *@param	bl_s		ビルボードアクターセット
 *@param	p_head		ヘッダー
 *@param	num			アニメーションセットナンバー
 *@param	ppMdl		モデルリソース
 *@param	ppTex		テクスチャリソース格納用
 *
 *@return	NNSG3dResMdlSet
 *
 *
 */
//-----------------------------------------------------------------------------
static NNSG3dResMdlSet* blact_getMdl(const BLACT_HEADER* p_head,NNSG3dResMdl** ppMdl, NNSG3dResTex** ppTex)
{
	void*				res;		// リソース
	NNSG3dResMdlSet*	mdl_set;		// モデルリソース

	// リソース取得	
	res = getRes(p_head, BLACT_RES_MAN_MDL);

	// モデル取得
	mdl_set = NNS_G3dGetMdlSet(res);
	*ppMdl = NNS_G3dGetMdlByIdx( mdl_set, 0 );

	if(ppTex){

		*ppTex = NNS_G3dGetTex( res );
	}

	return mdl_set;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	テクスチャリソースを取得する
 *
 *@param	bl_s		ビルボードアクターセット
 *@param	p_head		ヘッダー
 *@param	num			アニメーションセットナンバー
 *
 *@return	NNSG3dResMdl
 *
 *
 */
//-----------------------------------------------------------------------------
static NNSG3dResTex* blact_getTex(const BLACT_HEADER* p_head)
{
	NNSG3dResTex*	tex;		// テクスチャリソース

	// リソースデータ取得
	tex = (NNSG3dResTex*)getRes(p_head, BLACT_RES_MAN_TEX);
	return tex;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	テクスチャパターンアニメーションの読み込み
 *
 *@param	bl_s			ビルボードアクターセット
 *@param	p_head			ビルボードアクターヘッダー
 *@param	anm_set			アニメーションセットナンバー
 *@param	p_mdl			モデルリソース（読み込み済み）
 *@param	p_tex			テクスチャリソース（読み込み済み＆NULLじVram転送用）
 *@param	pAlloc			使用アロケータ
 *
 *@return	NNSG3dResFileHeader*	読み込んだアニメーションリソース
 *
 *
 */
//-----------------------------------------------------------------------------
static NNSG3dAnmObj* blact_getItp(const BLACT_HEADER* p_head, const NNSG3dResMdl* p_mdl, const NNSG3dResTex* p_tex, NNSFndAllocator* pAlloc)
{
	void*			res;		// リソース
	NNSG3dAnmObj*	anm;		// アニメーションオブジェ
    NNSG3dResTexPatAnm* pAnmRes;// アニメーションリソース

	// リソース取得
	res = getRes(p_head, BLACT_RES_MAN_ANM);

	// インデックス＃０のアニメーションを指定
    pAnmRes = (NNSG3dResTexPatAnm*)NNS_G3dGetAnmByIdx(res, 0);

	// 必要量のメモリをアロケートする。イニシャライズは別途必要になる。
    anm = NNS_G3dAllocAnmObj(pAlloc, // 使用するアロケータを指定
                            pAnmRes,    // アニメーションリソースを指定
                            p_mdl);    // モデルリソースを指定


	//
    // AnmObj を初期化する。
    //
    NNS_G3dAnmObjInit(anm,		// アニメーションオブジェクトへのポインタ
                      pAnmRes,	// アニメリソースへのポインタ
                      p_mdl,	// NNSG3dResMdlへのポインタ
					  p_tex );	// NNSG3dResTexへのポインタ
	return anm;
}

//-----------------------------------------------------------------------------
/**
 *	@brief	アニメーションセット変更（実際に処理する関数）
 *
 *  @param	act		チェンジする動作配列
 *  @param	header	ヘッダーデータ
 *
 *	@return none
 *
 *ここではタスクにデータをセットする	
 *			実際に入れ替えるのはVブランク中BLACT_VlBank()
 *
 */
//-----------------------------------------------------------------------------
static void chgBillboadAnmSet_Core( BLACT_WORK* act, const BLACT_HEADER* header )
{
	// 常駐アニメかVram転送アニメかチェック
	if( header->texKey == BLACT_TEXKEY_VRAMANM ){
		
		// Vram転送
		chgBillboadAnmSet_Core_VRAM( act, header );
	}else{

		// 常駐アニメ
		core_anmset_chg_norm( act, header );
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	オフセット値の時の開始フレームを取得
 *
 *	@param	act		取得するビルボードアクター
 *	@param	offs	オフセット値
 *
 *	@return	fx32	開始フレーム
 *
 *
 */
//-----------------------------------------------------------------------------
static fx32	nowOffsAnmStartFrame( const BLACT_WORK* act, int offs )
{
	const BLACT_ANIME_TBL* p_anm_tbl;				// アニメーションテーブル
	p_anm_tbl	= getAnmTbl( act->pAnmTbl,  offs );	// アニメーションテーブル

	return p_anm_tbl->start << FX32_SHIFT;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アニメーションフレーム変更　通常時用
 *
 *	@param	act		ビルボードアクターワーク
 *	@param	num		変更数
 *
 *	@retval	BLACT_ANISTA_LOOP	再生中
 *	@retval	BLACT_ANISTA_END	再生終了
 *
 *
 */
//-----------------------------------------------------------------------------
static int anmFrameChg_Core( BLACT_WORK* act, fx32 num )
{
	const BLACT_ANIME_TBL* p_anm_tbl;	// アニメーションテーブル

	p_anm_tbl	= getAnmTbl( act->pAnmTbl, act->AnmOffs );

	return anmFrameChgSys( p_anm_tbl, &act->frame, num );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	フレーム変更システム
 *
 *	@param	anm		アニメーションテーブル
 *	@param	frame	フレーム数のポインタ
 *	@param	num		動かすフレーム数
 *
 *	@retval	BLACT_ANISTA_LOOP	再生中
 *	@retval	BLACT_ANISTA_END	再生終了
 *
 *
 */
//-----------------------------------------------------------------------------
static int anmFrameChgSys( const BLACT_ANIME_TBL* anm, fx32* frame, fx32 num )
{
	int ret = BLACT_ANISTA_LOOP;
	
	// アニメーションデータ内のフレームでループ再生
	// 今ループ範囲内にいるかをチェック
	if( ((anm->start * FX32_ONE) > *frame) || 
		((anm->end * FX32_ONE) < *frame) ){

		// 範囲外なのでアニメーションのスタートフレームにする
		*frame = (anm->start * FX32_ONE);
	}else{
		// アニメーションさせた結果が範囲外にならないかチェック
		if( ((anm->end * FX32_ONE) < *frame + num) ){
			
			if(anm->cmd == BLACT_ANIM_LOOP){
				// 範囲外になるのでスタートフレームにする
				*frame = (anm->start * FX32_ONE);
			}else{

				ret = BLACT_ANISTA_END;
				*frame = (anm->end * FX32_ONE);
			}
		}else{
			// 何のチェックにも当たらなかったらアニメーションさせる
			*frame += num;
		}
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	描画前処理	テクスチャバインド
 *
 *@param	bl_w	バインドするワーク
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DrawTexBind(BLACT_WORK* bl_w)
{
	// テクスチャバインド
	reBindTexture(bl_w->pMdlTex, bl_w->pModelSet, &bl_w->texKey, &bl_w->tex4x4Key, &bl_w->plttKey);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	描画後処理	テクスチャリバインド
 *
 *@param	bl_w	リバインドするワーク
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DrawTexreBind(BLACT_WORK* bl_w)
{
	NNSG3dTexKey tex4x4key;
	NNSG3dTexKey texkey;
	NNSG3dPlttKey plttkey;
	

	// バインドを破棄
	NNS_G3dReleaseMdlSet(bl_w->pModelSet);

	// テクスチャとVramキーのリンクをはずす
	releaseTexture(bl_w->pMdlTex, &texkey, &tex4x4key, &plttkey);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースマネージャーからリソースを取得する
 *
 *@param	p_head		ヘッダー	
 *@param	flag		どのリソースかのフラグ
 *
 *@return	void*		リソース
 *
 *
 */
//-----------------------------------------------------------------------------
static void* getRes(const BLACT_HEADER* p_head, int flag)
{
	void* ret;

	switch(flag){
	case BLACT_RES_MAN_MDL:
		ret = p_head->ImdRes;
		break;
	
	case BLACT_RES_MAN_TEX:
		ret = (void*)p_head->ItxRes;
		break;
	
	default:
		ret = NULL;
		break;
	}
	
	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アニメーションテーブルをヘッダから取得
 *
 *	@param	p_head	アニメーションテーブル
 *	@param	ofs		オフセット
 *
 *	@return	アニメーションテーブル
 *
 *
 */
//-----------------------------------------------------------------------------
static const BLACT_ANIME_TBL* getAnmTbl(const BLACT_ANIME_TBL* p_anm, int ofs)
{
	return (p_anm + ofs);
}
