//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		clact.c
 *@brief	セルアクター
 *@author	tomoya takahashi
 *@data		2005.05.19
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#define	_CLACT_H_GLOBAL
#include <string.h>
#include "clact.h"
#include "system.h"
#include "gflib_os_print.h"
#include "vram_transfer_manager.h"
#include "assert.h"

//
#include "char_manager.h"
#include "pltt_manager.h"
#include "str_tool.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
 */
//-----------------------------------------------------------------------------
#define PLTT_ONE_SIZE	(32)	
#define	SIMPLE_DRAW_OAM_TMP	(128)

// アトリビュート操作
#define		CLACT_ATTR_PRIORITY_MASK	(0x0c00)			// 優先度データ抜き出しマスク
#define		CLACT_ATTR_PRIORITY_SHIFT	(10)				// 優先度データのシフト数

// オートアニメーションフレーム
#define		CLACT_AUTO_ANM_FRAME		(FX32_ONE * 2)

// アニメーションタイプ構造体の最大サイズ(intで)
#define		CLACT_ANM_DATA_MAX			(29)		// 本当のサイズはこれｘ４

//-------------------------------------
///	アニメーションタイプ構造体
enum
{
	CLACT_NONE,			// 使用していない
	CLACT_CELL,			// セルアニメーション
	CLACT_MULTICELL,	// マルチセルアニメーション
	CLACT_VRAM_CELL,	// セルアニメVram転送アニメーション
};

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
 */
//-----------------------------------------------------------------------------
//-------------------------------------
///	セルアニメーション構造体	
typedef	struct CLACT_ANIM_DATA_tag
{
	const NNSG2dCellDataBank*             pCellBank;   // セルデータ
	const NNSG2dCellAnimBankData*         pAnimBank;   // セルアニメーション

	NNSG2dCellAnimation				AnmCtrl;	// アニメーションコントローラ
} CLACT_ANIM_DATA;


//-------------------------------------
///	Vram転送セルアニメーション構造体
typedef struct CLACT_VRAM_ANIM_DATA_tag
{
	NNSG2dCellDataBank*             pCellBank;   // セルデータ
	const NNSG2dCellAnimBankData*         pAnimBank;   // セルアニメーション

	NNSG2dCellAnimation				AnmCtrl;	// アニメーションコントローラ

	u32								CellTransManHandle;	// セルアニメーションのVram転送を管理する
														// セル転送状態管理オブジェクトのハンドル
} CLACT_VRAM_ANIM_DATA;

//-------------------------------------
///	マルチセルアニメーション構造体	
typedef	struct CLACT_MULTICELL_ANIM_DATA_tag
{
	const NNSG2dCellDataBank*             pCellBank;	// セルデータ
    const NNSG2dCellAnimBankData*         pAnimBank;  // セルアニメーション
	
	NNSG2dMultiCellAnimation		AnmCtrl;	// アニメーションコントローラ
	
	const NNSG2dMultiCellDataBank*        pMCBank;    // マルチセルデータ
    const NNSG2dMultiCellAnimBankData*    pMCABank;   // マルチセルアニメーション
	NNSG2dNode*						pNode;		// マルチセルに必要なノード
	NNSG2dCellAnimation*			pCellAnim;	// マルチセルに必要なアニメーションコントローラ
	
} CLACT_MULTICELL_ANIM_DATA;


//-------------------------------------
///	セルアクター動作構造体
typedef struct CLACT_WORK_tag{
	VecFx32		Matrix;						// 座標
	VecFx32		AffineMatrix;				// アフィン変換座標
	VecFx32		Scale;						// スケール
	u16			Rotation;					// 回転
	u8			affin;						// アフィン、倍角アフィンフラグ
	u8			flip;						// フリップフラグ
	u8			over_write;					// レンダラーオーバーライトフラグ
	u8			palNo;						// パレットナンバー
	u8			palOfs;						// パレットオフセット
	BOOL		mosaic;						// モザイク
	GXOamMode	objmode;					// OBJモード
		
	// 描画種類フラグ
	u8			DrawFlag;	// 0:非描画		1:レンダラー描画
	// オートアニメーションフラグ
	u8			AnmFlag;	// 0:非アニメ	1:オートアニメ
	fx32		Frame;		// アニメーションスピード
											
	
	CLACT_SET_PTR	pClActSet;		// 親のアクターセットのポインタ
	u32				AnmData[ CLACT_ANM_DATA_MAX ];	// アニメーションデータ構造体（セルアニメーション、マルチセルアニメーション、Vram転送アニメーション各構造体データ　flagのアニメーションデータ型にキャストをして使う）
	NNSG2dImageProxy        ImageProxy;		// キャラクタ/テクスチャプロキシ
	NNSG2dImagePaletteProxy  PaletteProxy;	// パレットプロキシ
	u32			flag;						// セルアニメーション、マルチセルアニメーション、Vram転送アニメーションかのフラグ
	u16			AnmNum;						// シーケンスナンバー（今のアニメナンバー）
	u8			Priority;					// BG面との優先順位(0,1,2,3)
	u16			DrawPriority;				// 描画での優先順位(0=最前面	1,2,3....)
	NNS_G2D_VRAM_TYPE	type;				// VramType どっちに描画しているか
	/*	typedef enum NNS_G2D_VRAM_TYPE
		{
			NNS_G2D_VRAM_TYPE_3DMAIN = 0,		// スプライトは今は使わないので指定しない
			NNS_G2D_VRAM_TYPE_2DMAIN = 1,
			NNS_G2D_VRAM_TYPE_2DSUB  = 2,
			NNS_G2D_VRAM_TYPE_MAX    = 3
		}NNS_G2D_VRAM_TYPE;
	 */
	// リスト構造
	struct CLACT_WORK_tag*		pLast;		// 前のアクター
	struct CLACT_WORK_tag*		pNext;		// 次のアクター
} CLACT_WORK;

//-------------------------------------
//
//	セルアクターセット
//
//	セルアクターシステムの実態
//
//=====================================
typedef struct _CLACT_SET{
	CLACT_WORK*		pWork;			// セルアクター動作構造体
	int				WorkNum;		// 配列数
	CLACT_WORK**	ppWorkStack;	// スタック
	int				WorkStackNow;	// 今のスタックのpop位置
	
	CLACT_WORK	Dummy;	// アクターリストダミーデータ
	
	// OAMマネージャポインタ
//	NNSG2dOamManagerInstance* pMainMan;
//	NNSG2dOamManagerInstance* pSubMan;
	
	
	// レンダラー
	NNSG2dRendererInstance*		pRender;			// 描画用 Renderer

	// デフォルトアニメーションデータ
	void*							pAnimBuff;	// バッファ
    NNSG2dCellAnimBankData*         pAnimBank;  // セルアニメーション

	u32			DrawFlag;		// 1:表示　0:非表示
}CLACT_SET;

//-------------------------------------
//	
//	描画関数テーブル用
//	
//=====================================
typedef void (*CLACT_DRAW)( const CLACT_SET* pClActSet, CLACT_WORK* act );

//-------------------------------------
//	
//	オートアニメーション関数テーブル用
//	
//=====================================
typedef void (*CLACT_ANM)( CLACT_WORK* act );

//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	セルアクターセット操作ローカル関数
//=====================================
static void CleanActSet(CLACT_SET* pClAct);

//-------------------------------------
//	セルアクターワーク用
//=====================================
static u32	getActType( const CLACT_HEADER* pHeader );	// セルアニメか、マルチセルアニメかを返す
static void LoadCell( const NNSG2dCellDataBank* Cell, CLACT_WORK* pWork );		// セルを読み込む
static void LoadCellAnm( const NNSG2dCellAnimBankData* Anm, CLACT_WORK* pWork );	// セルアニメを読み込む
static void LoadMultiCell( const NNSG2dMultiCellDataBank* Mlt, CLACT_WORK* pWork );// マルチセルを読み込む
static void LoadMultiCellAnm( const NNSG2dMultiCellAnimBankData* Anm, CLACT_WORK* pWork );// マルチセルアニメを読み込む
static void MakeCellAnm( CLACT_WORK* pWork, int heap );
static void MakeCellAnmVram( const CLACT_HEADER* pHeader, CLACT_WORK* pWork , int heap);
static void MakeMultiCellAnm( CLACT_WORK* pWork, int heap );							// マルチセルアニメの構築を行う
static BOOL LoadData( const CLACT_SET* pSet, const CLACT_HEADER* pHeader, CLACT_WORK* pWork, int heap );
static u32 GetPlttProxyOffset( const NNSG2dImagePaletteProxy* pPltt, u32 vramType );	// パレットをずらす値を取得
// レンダラーを使用した高度な描画
static void renderDraw( const CLACT_SET* pClActSet, CLACT_WORK* act );
static void noDraw( const CLACT_SET* pClActSet, CLACT_WORK* act );

// オートアニメーション
static void autoAnm( CLACT_WORK* act );
static void noAnm( CLACT_WORK* act );

//-----------------------------------------------------------------------------
//				アクターリスト処理
//				描画優先順位で描画するため
//=============================================================================
static void addCellActList( CLACT_SET* cs, CLACT_WORK* pWork );		// リストに追加
static void dellCellActList( CLACT_WORK* pWork );	// リストから破棄(メモリ領域の破棄はしない)
//-------------------------------------
//	stackの処理
//=====================================
static void initStack(CLACT_SET* pSet);			// 初期化
static CLACT_WORK* popStack(CLACT_SET* pSet);	// 取り出し
static BOOL pushStack(CLACT_SET* pSet, CLACT_WORK* pDat);	// 格納
//=============================================================================
//----------------------------------------------------------------------------
/**
 *					グローバル変数宣言
 */
//-----------------------------------------------------------------------------

//=============================================================================
//
//		アクターシステム操作
//
//				アクターセット作成前
//				アクターセット破棄後
//				
//			に行う処理の関数
//
//=============================================================================
//=============================================================================
//
//	アクターセット操作関数郡
//
//=============================================================================
//-----------------------------------------------------------------------------
/**
 *@brief			セルアクターセットの初期化
 *
 *@param	pSetData		セルアクターセット作成データ
 *
 *@retval	CLACT_SET_PTR	作成したセルアクターセットポインタ
 *@retval	NULL			失敗
 *
 * セルアクターセットを作成
 *
 */
 //----------------------------------------------------------------------------
CLACT_SET_PTR CLACT_InitSet( const CLACT_SETDATA* pSetData )
{
	CLACT_SET*	cs;		// セルアクターセット	
	int			idx;	// セルアクターインデックス
	
	GF_ASSERT(pSetData);
	GF_ASSERT(pSetData->pRender);
	
	// アクターセットメモリ確保
	cs = sys_AllocMemory(pSetData->heap, sizeof(CLACT_SET));
	GF_ASSERT(cs);
	CleanActSet(cs);
	
	// ワークの作成
	cs->pWork = sys_AllocMemory(pSetData->heap, sizeof(CLACT_WORK)*pSetData->WorkNum);
	GF_ASSERT(cs->pWork);
	cs->WorkNum = pSetData->WorkNum;	// ワーク数
	// スタックの初期化
	cs->ppWorkStack = sys_AllocMemory(pSetData->heap, sizeof(CLACT_WORK*)*pSetData->WorkNum);
	GF_ASSERT(cs->ppWorkStack);
	initStack(cs);
	
	// リストのダミーの初期化
	CLACT_WorkClear(&cs->Dummy);
	cs->Dummy.pLast = &cs->Dummy;
	cs->Dummy.pNext = &cs->Dummy;

	// OAMマネージャ
//	cs->pMainMan	= pSetData->pMainMan;
//	cs->pSubMan		= pSetData->pSubMan;
	
	// レンダラー 
	cs->pRender = pSetData->pRender;

	// デフォルトアニメデータ読み込み
	cs->pAnimBuff = sys_LoadFile( pSetData->heap, "data/clact_default.NANR" );
	NNS_G2dGetUnpackedAnimBank( cs->pAnimBuff, &cs->pAnimBank );

	// 描画フラグ
	cs->DrawFlag = 1;

	return cs;
}

//-----------------------------------------------------------------------------
/**
 *@brief			セルアクターセットの破棄
 *
 *@param	ClActSet			破棄するセルアクターセットポインタ
 *
 *@retval	TRUE	成功
 *@retval	FALSE	失敗	(ClActSetが間違い)
 *
 * セルアクターセットを破棄する
 *		実行していたアクターオブジェも一斉解放
 *
 */
 //----------------------------------------------------------------------------
BOOL CLACT_DestSet( CLACT_SET_PTR ClActSet )
{	

	if(ClActSet == NULL){
		return FALSE;
	}

	if(ClActSet->pWork == NULL){	// 削除済みかチェック
		return TRUE;
	}
	
	// アクター破棄
	CLACT_DelAllSet(ClActSet);

	// アニメデータ破棄
	sys_FreeMemoryEz( ClActSet->pAnimBuff );
	
	// スタック破棄
	sys_FreeMemoryEz(ClActSet->ppWorkStack);

	// ワーク破棄
	sys_FreeMemoryEz(ClActSet->pWork);

	// アクターセット初期化
	CleanActSet(ClActSet);

	sys_FreeMemoryEz(ClActSet);
	ClActSet = NULL;

	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 *@brief			セルアクターセットの描画フラグを設定
 *
 *@param	ClActSet			破棄するセルアクターセットポインタ
 *@param	flag				0:非描画	1:描画
 *
 *@retval	TRUE	成功
 *@retval	FALSE	失敗	(ClActSetが間違い)
 *
 *	登録されているビルボード全てを描画/非描画するかを設定
 *
 */
 //----------------------------------------------------------------------------
BOOL CLACT_DrawFlagSet( CLACT_SET_PTR ClActSet, u8 flag )
{
	if(ClActSet == NULL){
		return FALSE;
	}

	if(ClActSet->pWork == NULL){	// 登録してあるかチェック
		return FALSE;
	}

	ClActSet->DrawFlag = flag;

	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 *@brief			全アクター破棄
 *
 *@param	ClActSet		セルアクターセットポインタ
 *
 *@retval	TRUE	成功
 *@retval	FALSE	失敗	(ClActSetが間違い)
 */
 //----------------------------------------------------------------------------
BOOL CLACT_DelAllSet( CLACT_SET_PTR ClActSet )
{
	CLACT_WORK*	p_work;		// ループ用
	CLACT_WORK*	p_next;		// 次を保存用

	if(ClActSet == NULL){
		return FALSE;
	}
	
	if(ClActSet->pWork == NULL){	// 登録してあるかチェック
		return TRUE;
	}
	
	// 破棄
	p_work = ClActSet->Dummy.pNext;
	while(p_work != &ClActSet->Dummy){
		p_next = p_work->pNext;
		
		CLACT_Delete(p_work);

		p_work = p_next;
	}

	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 *@brief				描画する
 *
 *@param	pClActSys	セルアクターシステム
 *@param	pClAct		セルアクターセット
 *
 *@return	none
 */
 //----------------------------------------------------------------------------
void CLACT_Draw( const CLACT_SET* pClAct )
{
	CLACT_WORK*	p_work;		// ループ用
	// 描画関数テーブル
	static const CLACT_DRAW	drawTbl[] = {
		noDraw,		// 描画しない
		renderDraw,
	};
	
	// オートアニメーションテーブル
	static const CLACT_ANM	anmTbl[] = {
		noAnm,
		autoAnm,	
	};

	GF_ASSERT( pClAct );
	
	if( pClAct->DrawFlag == 0 ){
		return ;
	}

	// 描画する
	p_work = pClAct->Dummy.pNext;
	while(p_work != &pClAct->Dummy){

		// 描画
		drawTbl[ p_work->DrawFlag ]( pClAct, p_work );

		// オートアニメーション
		anmTbl[ p_work->AnmFlag ]( p_work );
		
		p_work = p_work->pNext;
	}
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアクターセットに登録されているOAMマネージャのOAMを転送
 *
 *@param	pClAct		セルアクターセット
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_OAMTrans( CLACT_SET_PTR pClAct )
{
	if(pClAct->pMainMan != NULL){
		NNS_G2dApplyOamManagerToHW(pClAct->pMainMan);
		NNS_G2dResetOamManagerBuffer(pClAct->pMainMan);
	}
	if(pClAct->pSubMan != NULL){
		NNS_G2dApplyOamManagerToHW(pClAct->pSubMan);
		NNS_G2dResetOamManagerBuffer(pClAct->pSubMan);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	登録されているOAMマネージャを取得
 *
 *@param	pClAct			セルアクター
 *@param	vramType		Vramタイプ	
					main	NNS_G2D_VRAM_TYPE_2DMAIN
					sub		NNS_G2D_VRAM_TYPE_2DSUB
 *
 *@retval	NNSG2dOamManagerInstance* OAMマネージャ
 *@retval	NULL						設定されていない
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dOamManagerInstance* CLACT_OAMManagerGet( CLACT_SET_PTR pClAct, int vramType )
{
	if(vramType == NNS_G2D_VRAM_TYPE_2DMAIN){
		return pClAct->pMainMan;
	}
	if(vramType == NNS_G2D_VRAM_TYPE_2DSUB){
		return pClAct->pSubMan;
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	OAMマネージャを設定
 *
 *@param	pClAct		セルアクター
 *@param	pOamMan		OAMマネージャ
 *@param	vramType	
				mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN
				subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_OAMManagerSet( CLACT_SET_PTR pClAct, NNSG2dOamManagerInstance* pOamMan, int vramType )
{
	if(vramType == NNS_G2D_VRAM_TYPE_2DMAIN){
		pClAct->pMainMan = pOamMan;
	}
	if(vramType == NNS_G2D_VRAM_TYPE_2DSUB){
		pClAct->pSubMan = pOamMan;
	}
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *@brief	登録されているレンダラーを取得
 *
 *@param	pClAct			セルアクター
 *
 *@retval	NNSG2dRendererInstance*		OAMマネージャ
 *@retval	NULL						設定されていない
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dRendererInstance* CLACT_RenderGet( CONST_CLACT_SET_PTR pClAct)
{
	return pClAct->pRender;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	レンダラーを設定
 *
 *@param	pClAct		セルアクター
 *@param	pRender		レンダラー
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_RenderSet( CLACT_SET_PTR pClAct, NNSG2dRendererInstance* pRender)
{
	pClAct->pRender = pRender;
}

//-----------------------------------------------------------------------------
/**
 *@brief			アクターセット初期化
 *
 *@param	pClAct		セルアクターセット
 *
 *@return	none
 */
 //----------------------------------------------------------------------------
static void CleanActSet(CLACT_SET* pClAct)
{
	pClAct->pWork		= NULL;		// セルアクター動作構造体
	pClAct->WorkNum		= 0;		// 配列数
	pClAct->ppWorkStack	= NULL;		// スタック
	pClAct->WorkStackNow= 0;		// 今のスタックのpop位置
//	pClAct->pMainMan	= NULL;
//	pClAct->pSubMan		= NULL;
	pClAct->pRender		=NULL;		// レンダラー
	
	CLACT_WorkClear(&pClAct->Dummy);	// アクターリストダミーデータ
	pClAct->DrawFlag = 0;
}

//=============================================================================
//
//	アクターワーク操作関数郡
//
//=============================================================================
//-----------------------------------------------------------------------------
/**
 *@brief		セルアクターデータ初期化
 *						
 *
 *@param	pWork		初期化する(0 Clear)データ
 *
 *@return	none
 *
 */
 //----------------------------------------------------------------------------
void CLACT_WorkClear( CLACT_WORK_PTR pWork )
{
	int i;		// ループ用
	
	pWork->pClActSet		= NULL;
	memset( pWork, 0, sizeof(CLACT_WORK) );
//	memset(&pWork->AnmData, 0, sizeof(u32) * CLACT_ANM_DATA_MAX);
	NNS_G2dInitImageProxy( &pWork->ImageProxy );
	NNS_G2dInitImagePaletteProxy( &pWork->PaletteProxy );
	pWork->objmode			= GX_OAM_MODE_NORMAL;
}

//-----------------------------------------------------------------------------
/**
 *@brief		セルアクターワークの取得
 *						
 *
 *@param	ClActSetIdx		セルアクターセットポインタ
 *@param	ClActIdx		セルアクターワークインデックス
 *
 *@retval	CLACT_WORK_PTR		成功
 *@retval	NULL			失敗
 *
 */
//----------------------------------------------------------------------------
CLACT_WORK_PTR CLACT_GetWork(CONST_CLACT_SET_PTR ClActSet, s16 ClActIdx)
{
	if(ClActSet == NULL){
		return NULL;
	}
	if(ClActIdx >= ClActSet->WorkNum){
		return NULL;
	}

	return &ClActSet->pWork[ClActIdx];
}

//-----------------------------------------------------------------------------
/**
 *@brief			追加処理
 *
 *@param	add		登録データ
 *
 *@retval	BLACT_WORK*		登録したアクターのポインタ
 *@retval	NULL			失敗
 */
// ----------------------------------------------------------------------------
CLACT_WORK_PTR CLACT_Add(const CLACT_ADD* add)
{
	CLACT_WORK*	cl_w;		// 追加するアクターワーク
	
	// スタックからワークを取得
	cl_w = popStack(add->ClActSet);

	if(cl_w == NULL){
		return NULL;
	}

	
	// この要素のデータを初期化する
	cl_w->pClActSet		= add->ClActSet;		// アクターセットを代入
	cl_w->AnmNum		= 0;
	cl_w->Matrix		= add->mat;			// 座標セット
	cl_w->Scale			= add->sca;			// 拡縮セット
	cl_w->Rotation		= add->rot;			// 回転角セット
	cl_w->type			= add->DrawArea;	// 転送画面セット
	cl_w->DrawPriority	= add->pri;			// 描画優先順位
	cl_w->affin			= 0;				// デフォはアフィンなし
	cl_w->flip			= 0;				// デフォはフリップなし
	cl_w->mosaic		= FALSE;			// モザイクフラグ
	cl_w->objmode		= GX_OAM_MODE_NORMAL;// オブジェモードノーマル

	// パレットナンバー
	// BG表示優先順位はoverライトする
	cl_w->over_write	= NNS_G2D_RND_OVERWRITE_PLTTNO_OFFS | NNS_G2D_RND_OVERWRITE_PRIORITY;	

	// アフィン変換設定
	NNS_G2dSetRndCoreAffineOverwriteMode(
			&( add->ClActSet->pRender->rendererCore ),
			cl_w->affin );
	// フリップ設定
	NNS_G2dSetRndCoreFlipMode(
			&( add->ClActSet->pRender->rendererCore ),
			cl_w->flip & CLACT_FLIP_H,
			cl_w->flip & CLACT_FLIP_V);

	// 描画フラグを設定
	cl_w->DrawFlag		= 1;		// レンダラー描画
	
	// オートアニメーション設定
	cl_w->AnmFlag		= 0;
	cl_w->Frame			= CLACT_AUTO_ANM_FRAME;

	// アニメーションデータを読み込む
	if( LoadData( add->ClActSet, add->ClActHeader,cl_w, add->heap ) == FALSE ){
		// 失敗
		CLACT_Delete( cl_w );

		return NULL;
	}

	// パレットオフセットを取得
	cl_w->palOfs = GetPlttProxyOffset( &cl_w->PaletteProxy, cl_w->type );
	cl_w->palNo = cl_w->palOfs;	// 初期値はパレットオフセット位置にする

	// アクターリストに追加
	addCellActList(add->ClActSet, cl_w);
	
	return cl_w;
}

//-----------------------------------------------------------------------------
/**
 *@brief			シンプル追加処理
 *
 *@param	add		登録データ
 *
 *@retval	CLACT_WORK_PTR		登録したアクターポインタ
 *@retval	NULL				失敗
 */
// ----------------------------------------------------------------------------
CLACT_WORK_PTR CLACT_AddSimple(const CLACT_ADD_SIMPLE* add)
{
	CLACT_ADD add_ex;

	add_ex.ClActSet		= add->ClActSet;
	add_ex.ClActHeader	= add->ClActHeader;
	add_ex.mat			= add->mat;
	add_ex.sca.x		= FX32_ONE;
	add_ex.sca.y		= FX32_ONE;
	add_ex.sca.z		= FX32_ONE;
	add_ex.rot			= 0;
	add_ex.pri			= add->pri;
	add_ex.DrawArea		= add->DrawArea;
	add_ex.heap			= add->heap;

	return CLACT_Add( &add_ex );
}

//-----------------------------------------------------------------------------
/**
 *@brief			削除処理
 *
 *@param	del		削除するアクターワーク
 *
 *@return	none
 * 
 */
// ----------------------------------------------------------------------------
void CLACT_Delete(CLACT_WORK_PTR del)
{
	CLACT_SET* cs;
	
	// データがあるかチェック
	if( del->flag != CLACT_NONE ){
			
		CLACT_ANIM_DATA* cell_anm = (CLACT_ANIM_DATA*)&del->AnmData;

		// 描画リストから破棄
		if(del->pLast != NULL){
			dellCellActList( del );
		}

		
		// Vram転送アニメーションのハンドル解放
		if( del->flag == CLACT_VRAM_CELL ){
			CLACT_VRAM_ANIM_DATA* p_vram = (CLACT_VRAM_ANIM_DATA*)&del->AnmData;	

			if( NNS_G2dGetImageLocation(&del->ImageProxy, del->type) != NNS_G2D_VRAM_ADDR_NONE ){
				NNS_G2dFreeCellTransferStateHandle( p_vram->CellTransManHandle );
			}
		}

		// マルチセルデータの解放
		if( del->flag == CLACT_MULTICELL ){
			CLACT_MULTICELL_ANIM_DATA* p_multi = (CLACT_MULTICELL_ANIM_DATA*)&del->AnmData;

			// ノード
			if(p_multi->pNode != NULL){
				sys_FreeMemoryEz( p_multi->pNode );
			}

			// アニメーションコントローラ
			if(p_multi->pCellAnim != NULL){
				sys_FreeMemoryEz( p_multi->pCellAnim );
			}
		}
		
		// 使用していないにする
		del->flag = CLACT_NONE;	

		// スタックにプッシュ
		cs = (CLACT_SET*)del->pClActSet;
		pushStack(cs, del);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	座標を設定
 *
 *@param	act			アクター
 *@param	Matrix		座標
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetMatrix(CLACT_WORK_PTR act, const VecFx32* Matrix)
{
	act->Matrix = *Matrix;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	アフィン変換座標を設定
 *
 *@param	act			アクター
 *@param	Matrix		座標
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetAffineMatrix(CLACT_WORK_PTR act, const VecFx32* Matrix)
{
	act->AffineMatrix = *Matrix;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	拡大値を設定
 *
 *@param	act		アクター
 *@param	Scale	拡大値
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetScale(CLACT_WORK_PTR act, const VecFx32* Scale)
{
	act->Scale = *Scale;
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	拡大値を設定し、アフィンフラグを設定する
 *
 *@param	act		アクター
 *@param	Scale	拡大値
 *@param	affine	アフィンフラグ
 *
 *@return	none
 *
 *affineフラグ
 *	enum{
 *		CLACT_AFFINE_NONE,		// アフィン変換なし
 *		CLACT_AFFINE_NORMAL,	// アフィン変換
 *		CLACT_AFFINE_DOUBLE,	// 倍角アフィン変換
 *	};
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetScaleAffine(CLACT_WORK_PTR act, const VecFx32* Scale, int affine)
{
	CLACT_SetScale( act, Scale );
	CLACT_SetAffineParam( act, affine );
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	回転角を設定
 *
 *@param	act			アクター
 *@param	Rotation	回転角
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetRotation(CLACT_WORK_PTR act, u16 Rotation)
{
	act->Rotation = Rotation;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	回転角を設定してアフィンフラグを設定
 *
 *@param	act			アクター
 *@param	Rotation	回転角		(0～65535)
 *@param	affine		アフィンフラグ
 *
 *@return	none
 *
 *affineフラグ
 *	enum{
 *		CLACT_AFFINE_NONE,		// アフィン変換なし
 *		CLACT_AFFINE_NORMAL,	// アフィン変換
 *		CLACT_AFFINE_DOUBLE,	// 倍角アフィン変換
 *	};
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetRotationAffine(CLACT_WORK_PTR act, u16 Rotation, int affine)
{
	CLACT_SetRotation( act, Rotation );
	CLACT_SetAffineParam( act, affine );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	描画フラグを設定
 *
 *@param	act		アクター
 *@param	flag	描画フラグ	0:非描画	1:レンダラ描画	
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetDrawFlag(CLACT_WORK_PTR act, int flag)
{
	GF_ASSERT( act );
	GF_ASSERT( flag < 2 );		// 2より小さい必要がある
	act->DrawFlag = flag;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	オートアニメフラグを設定
 *
 *@param	act		アクター
 *@param	flag	オートアニメフラグ	0:非アニメ	1:オートアニメ
 *
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetAnmFlag(CLACT_WORK_PTR act, int flag)
{
	GF_ASSERT( act );
	GF_ASSERT( flag < 2 );		// 2より小さい必要がある
	act->AnmFlag = flag;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	オートアニメーションフレームを設定
 *
 *@param	act		アクター
 *@param	frame	１シンクに進めるフレーム数
 *
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetAnmFrame(CLACT_WORK_PTR act, fx32 frame)
{
	GF_ASSERT( act );

	act->Frame = frame;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アフィン変換パラメータ
 *
 *	@param	act		アクター
 *	@param	param	アフィン変換パラメータ
 *
 *	@return	none
 *
 * param
 *	enum{
 *		CLACT_AFFINE_NONE,		// アフィン変換なし
 *		CLACT_AFFINE_NORMAL,	// アフィン変換
 *		CLACT_AFFINE_DOUBLE,	// 倍角アフィン変換
 *	};
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetAffineParam( CLACT_WORK_PTR act, int param )
{
	GF_ASSERT(act);

	act->affin	= param;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	フリップの設定
 *
 *	@param	act		アクター
 *	@param	flag	フリップフラグ 
 *
 *	@return	none
 *
 * flag
 *	enum{
 * 		CLACT_FLIP_NONE,		// フリップなし
 * 		CLACT_FLIP_H,			// フリップ水平方向
 *		CLACT_FLIP_V,			// フリップ垂直方向
 *		CLACT_FLIP_HV,			// 両方向フリップ
 *	};
 *
 */
//-----------------------------------------------------------------------------
void CLACT_SetFlip( CLACT_WORK_PTR act, int flag )
{
	GF_ASSERT(act);
	act->flip = flag;
	act->affin	= CLACT_AFFINE_NONE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	座標を取得
 *
 *@param	act		アクター
 *
 *@return	VecFx32	座標
 *
 *
 */
//-----------------------------------------------------------------------------
const VecFx32* CLACT_GetMatrix(CONST_CLACT_WORK_PTR act)
{
	return &act->Matrix;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	アフィン変換座標を取得
 *
 *@param	act		アクター
 *
 *@return	VecFx32	座標
 *
 *
 */
//-----------------------------------------------------------------------------
const VecFx32* CLACT_GetAffineMatrix(CONST_CLACT_WORK_PTR act)
{
	return &act->AffineMatrix;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	拡大値を取得
 *
 *@param	act		アクター
 *
 *@return	VecFx32	拡大値
 *
 *
 */
//-----------------------------------------------------------------------------
const VecFx32* CLACT_GetScale(CONST_CLACT_WORK_PTR act)
{
	return &act->Scale;
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	回転角度を取得
 *
 *@param	act		アクター
 *
 *@return	u16		回転角度
 *
 *
 */
//-----------------------------------------------------------------------------
u16 CLACT_GetRotation(CONST_CLACT_WORK_PTR act)
{
	return act->Rotation;
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	描画フラグを取得
 *
 *@param	act	アクター
 *
 *@return	int		0:非描画	1:描画
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_GetDrawFlag(CONST_CLACT_WORK_PTR act)
{
	return act->DrawFlag;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	オートアニメフラグを取得
 *
 *@param	act	アクター
 *
 *@return	int		0:非アニメ	1:オートアニメーション
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_GetAnmFlag(CONST_CLACT_WORK_PTR act)
{
	return act->AnmFlag;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	オートアニメーションフレームを取得
 *
 *@param	act	アクター
 *
 *@return	fx32		１シンクに進めるフレーム数
 *
 *
 */
//-----------------------------------------------------------------------------
fx32 CLACT_GetAnmFrame(CONST_CLACT_WORK_PTR act)
{
	return act->Frame;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アフィンパラメータ	取得
 *
 *	@param	act		アクター
 *
 *	@return	int		アフィンパラメータ
 *
 * ret
 *	enum{
 *		CLACT_AFFINE_NONE,		// アフィン変換なし
 *		CLACT_AFFINE_NORMAL,	// アフィン変換
 *		CLACT_AFFINE_DOUBLE,	// 倍角アフィン変換
 *	};
 *
 */
//-----------------------------------------------------------------------------
int CLACT_GetAffineParam( CONST_CLACT_WORK_PTR act )
{
	GF_ASSERT(act);
	return act->affin;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	フリップ設定を取得
 *
 *	@param	act		アクター
 *
 *	@return	int		フリップ設定
 *
 * ret
 *	enum{
 * 		CLACT_FLIP_NONE,		// フリップなし
 * 		CLACT_FLIP_H,			// フリップ水平方向
 *		CLACT_FLIP_V,			// フリップ垂直方向
 *		CLACT_FLIP_HV,			// 両方向フリップ
 *	};
 *
 */
//-----------------------------------------------------------------------------
int CLACT_GetFlip( CONST_CLACT_WORK_PTR act )
{
	GF_ASSERT(act);
	return act->flip;
}

//-----------------------------------------------------------------------------
/*
 *@brief	アニメーションのシーケンスをチェンジする
 *
 *@param	actCell：セルアクター
 *@param	num：シーケンスナンバー
 *
 *@return	none
 */
 //----------------------------------------------------------------------------
void CLACT_AnmChg( CLACT_WORK_PTR actCell, u32 num )
{
	const NNSG2dAnimSequence* pSeq;		// シーケンス

	// 変更したシーケンスナンバーをセット
	actCell->AnmNum = num;
	
	// セルアニメーションかチェック
	if( (actCell->flag == CLACT_CELL) || (actCell->flag == CLACT_VRAM_CELL) ){
		CLACT_ANIM_DATA* anm = (CLACT_ANIM_DATA*)&actCell->AnmData;
		
		// シーケンスを取得
		pSeq = NNS_G2dGetAnimSequenceByIdx( anm->pAnimBank, num );

		// シーケンスを適用
		NNS_G2dSetCellAnimationSequence( &anm->AnmCtrl, pSeq );

		// アニメーションスタート
		NNS_G2dStartAnimCtrl( &anm->AnmCtrl.animCtrl );
	}else{
		CLACT_MULTICELL_ANIM_DATA* anm = (CLACT_MULTICELL_ANIM_DATA*)&actCell->AnmData;
		
		// マルチセルアニメーション
		// シーケンスを取得
		pSeq = NNS_G2dGetAnimSequenceByIdx( anm->pMCABank, num );

		// シーケンスを適用
		NNS_G2dSetAnimSequenceToMCAnimation( &anm->AnmCtrl, pSeq );

		// アニメーションスタート
		NNS_G2dStartAnimCtrl( &anm->AnmCtrl.animCtrl );
	}
}

//-----------------------------------------------------------------------------
/*
 *@brief	アニメーションのシーケンスをチェンジする
 *
 *@param	actCell：セルアクター
 *@param	num：シーケンスナンバー
 *
 *@return	none
 */
 //----------------------------------------------------------------------------
void CLACT_AnmChgCheck( CLACT_WORK_PTR actCell, u32 num )
{
	// シーケンスが違ったらチェンジ
	if( actCell->AnmNum != num ){
		CLACT_AnmChg( actCell, num );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	アニメーションリスタート
 *
 *	@param	actCell		セルアクタ－
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void CLACT_AnmReStart( CLACT_WORK_PTR actCell )
{
	// セルアニメーションかチェック
	if( (actCell->flag == CLACT_CELL) || (actCell->flag == CLACT_VRAM_CELL) ){
		CLACT_ANIM_DATA* anm = (CLACT_ANIM_DATA*)&actCell->AnmData;
		
		// ステータスリセット
		NNS_G2dResetAnimCtrlState( &anm->AnmCtrl.animCtrl );

		// アニメーションスタート
		NNS_G2dStartAnimCtrl( &anm->AnmCtrl.animCtrl );
		
		CLACT_AnmFrameSet( actCell, 0 );
	}else{
		CLACT_MULTICELL_ANIM_DATA* anm = (CLACT_MULTICELL_ANIM_DATA*)&actCell->AnmData;
		
		// マルチセルアニメーション
		// ステータスリセット
		NNS_G2dResetAnimCtrlState( &anm->AnmCtrl.animCtrl );

		// アニメーションスタート
		NNS_G2dStartAnimCtrl( &anm->AnmCtrl.animCtrl );

		CLACT_AnmFrameSet( actCell, 0 );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	現在のアニメーションシーケンスを取得
 *
 *@param	actCell		アクター
 *
 *@return	s32		アニメーションシーケンスナンバー
 *
 *
 */
//-----------------------------------------------------------------------------
u32 CLACT_AnmGet( CONST_CLACT_WORK_PTR actCell )
{
	return actCell->AnmNum;
}

//-----------------------------------------------------------------------------
/**	
 *@brief	アニメーションさせる
 *
 *@param	actCell：動作構造体
 *@param	num：フレームを進める値
 *
 *@return	none
 */
 //----------------------------------------------------------------------------
void CLACT_AnmFrameChg( CLACT_WORK_PTR actCell, fx32 num )
{
	// アニメーション
	// セルアニメーションかチェック
	if( (actCell->flag == CLACT_CELL) || (actCell->flag == CLACT_VRAM_CELL) ){
		CLACT_ANIM_DATA* anm = (CLACT_ANIM_DATA*)&actCell->AnmData;
		NNS_G2dTickCellAnimation( &anm->AnmCtrl, num );
	}else{
		CLACT_MULTICELL_ANIM_DATA* anm = (CLACT_MULTICELL_ANIM_DATA*)&actCell->AnmData;
		NNS_G2dTickMCAnimation( &anm->AnmCtrl, num );
	}
}

//-----------------------------------------------------------------------------
/**	
 *@brief	アニメーションフレームをセット
 *
 *@param	actCell：動作構造体
 *@param	num：セットするアニメーションフレーム数
 *
 *@return	none
 */
//----------------------------------------------------------------------------
void CLACT_AnmFrameSet( CLACT_WORK_PTR actCell, u16 num )
{
	// シーケンス番号のフレーム数のところにする
	// セルアニメーションかチェック
	if( (actCell->flag == CLACT_CELL) || (actCell->flag == CLACT_VRAM_CELL) ){
		CLACT_ANIM_DATA* anm = (CLACT_ANIM_DATA*)&actCell->AnmData;
		NNS_G2dSetCellAnimationCurrentFrame( &anm->AnmCtrl, num );
	}else{
		CLACT_MULTICELL_ANIM_DATA* anm = (CLACT_MULTICELL_ANIM_DATA*)&actCell->AnmData;
		NNS_G2dSetMCAnimationCurrentFrame( &anm->AnmCtrl, num );
	}
}

//-----------------------------------------------------------------------------
/**	
 *@brief				アニメーションフレームを取得
 *
 *@param	actCell：動作構造体
 *
 *@return	今のフレーム数
 */
//----------------------------------------------------------------------------
u16 CLACT_AnmFrameGet( CONST_CLACT_WORK_PTR actCell)
{
	NNSG2dAnimController*	anm_cntl;		// アニメーションコントローラ
	
	// セルアニメーションかチェック
	if( (actCell->flag == CLACT_CELL) || (actCell->flag == CLACT_VRAM_CELL) ){
		CLACT_ANIM_DATA* anm = (CLACT_ANIM_DATA*)&actCell->AnmData;
		anm_cntl = NNS_G2dGetCellAnimationAnimCtrl( &anm->AnmCtrl );
	}else{
		CLACT_MULTICELL_ANIM_DATA* anm = (CLACT_MULTICELL_ANIM_DATA*)&actCell->AnmData;
		anm_cntl = NNS_G2dGetMCAnimAnimCtrl( &anm->AnmCtrl );
	}
	return NNS_G2dGetAnimCtrlCurrentFrame( anm_cntl );
}

//-----------------------------------------------------------------------------
/**
 *@brief	BG面との優先度を変更する
 *
 *@param	actCell：動作構造体
 *@param	Priority：優先度
 *
 *@return	none
 */
 //----------------------------------------------------------------------------
void CLACT_BGPriorityChg( CLACT_WORK_PTR actCell, u8 Priority )
{
	actCell->Priority = Priority;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	BG面との描画優先度を取得
 *
 *@param	actCell		アクター
 *
 *@return	u8			優先度
 *
 *
 */
//-----------------------------------------------------------------------------
u8 CLACT_BGPriorityGet( CONST_CLACT_WORK_PTR actCell)
{
	return actCell->Priority;
}

//-----------------------------------------------------------------------------
/**
 *@brief				パレットナンバーを変更
 *
 *@param	actCell：動作構造体
 *@param	pltt_num：変更するパレットナンバー
 * 
 *@return	none
 *
 * ■パレットナンバー設定とパレットオフセット設定は同居しません。
 *　　●パレットナンバーを設定するとオフセットの値は反映されなくなります。
 *	　●オフセット値を設定したときはパレットナンバーが反映されなくなります。
 */
 //----------------------------------------------------------------------------
void CLACT_PaletteNoChg( CLACT_WORK_PTR actCell, u32 pltt_num )
{
	GF_ASSERT( actCell );

	actCell->palNo = pltt_num;

	// パレットナンバー反映
	// パレットオフセット反映
	actCell->over_write	|= NNS_G2D_RND_OVERWRITE_PLTTNO;	
	actCell->over_write &= ~NNS_G2D_RND_OVERWRITE_PLTTNO_OFFS;
}

//-----------------------------------------------------------------------------
/**
 * ●CLACT_PaletteNoChgの結果にパレット転送先頭ナンバーを加算します。
 *
 *@brief				パレットナンバーを変更
 *
 *@param	actCell			動作構造体
 *@param	pltt_num		変更するパレットナンバー
 * 
 *@return	none
 *
 * ■パレットナンバー設定とパレットオフセット設定は同居しません。
 *　　●パレットナンバーを設定するとオフセットの値は反映されなくなります。
 *	　●オフセット値を設定したときはパレットナンバーが反映されなくなります。
 * 
 */
 //----------------------------------------------------------------------------
void CLACT_PaletteNoChgAddTransPlttNo( CLACT_WORK_PTR actCell, u32 pltt_num )
{
	CLACT_PaletteNoChg( actCell, pltt_num );

	actCell->palNo += GetPlttProxyOffset( &actCell->PaletteProxy, actCell->type );

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットナンバー取得
 *
 *@param	actCell		アクター
 *
 *@return	u32		今のパレットナンバー
 *
 *
 */
//-----------------------------------------------------------------------------
u32 CLACT_PaletteNoGet( CONST_CLACT_WORK_PTR actCell )
{
	return actCell->palNo;
}

//-----------------------------------------------------------------------------
/**
 * ●OAMアトリビュートに設定されているパレットナンバーに加算されます。
 * 
 *@brief	パレットオフセットを設定
 *
 *@param	actCell		動作構造体
 *@param	pltt_num	パレットオフセットナンバー
 * 
 *@return	none
 *
 * ■パレットナンバー設定とパレットオフセット設定は同居しません。
 *　　●パレットナンバーを設定するとオフセットの値は反映されなくなります。
 *	　●オフセット値を設定したときはパレットナンバーが反映されなくなります。
 * 
 */
 //----------------------------------------------------------------------------
void CLACT_PaletteOffsetChg( CLACT_WORK_PTR actCell, u32 pltt_num )
{
	GF_ASSERT( actCell );

	actCell->palOfs = pltt_num;

	// パレットナンバー非反映
	// パレットオフセット反映
	actCell->over_write	|= NNS_G2D_RND_OVERWRITE_PLTTNO_OFFS;	
	actCell->over_write &= ~NNS_G2D_RND_OVERWRITE_PLTTNO;
}

//----------------------------------------------------------------------------
/**
 * ●CLACT_PaletteOffsetChg関数の結果にパレットの転送先先頭パレットナンバーを加算します。
 *
 *@brief	パレットオフセットを設定
 *
 *	@param	act		アクター
 *
 *	@return	パレットナンバー
 *
 *
 * ■パレットナンバー設定とパレットオフセット設定は同居しません。
 *　　●パレットナンバーを設定するとオフセットの値は反映されなくなります。
 *	　●オフセット値を設定したときはパレットナンバーが反映されなくなります。
 */
//-----------------------------------------------------------------------------
void CLACT_PaletteOffsetChgAddTransPlttNo( CLACT_WORK_PTR act, u32 pltt_num )
{
	CLACT_PaletteOffsetChg( act, pltt_num );

	act->palOfs += GetPlttProxyOffset( &act->PaletteProxy, act->type );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットオフセット値取得
 *
 *@param	actCell		アクター
 *
 *@return	u32		今のパレットオフセット値
 *
 *
 */
//-----------------------------------------------------------------------------
u32 CLACT_PaletteOffsetGet( CONST_CLACT_WORK_PTR actCell )
{
	GF_ASSERT( actCell );

	return actCell->palOfs;
}

//-----------------------------------------------------------------------------
/**
 *@brief	描画優先順位を設定
 *
 *@param	actCell		動作構造体
 *@param	Priority	優先順位
 *				
 * 
 *@return	none
 */
 //----------------------------------------------------------------------------
void CLACT_DrawPriorityChg( CLACT_WORK_PTR actCell, u32 Priority )
{
	CLACT_SET* cs = (CLACT_SET*)actCell->pClActSet;
	
	// 優先順位を変更
	actCell->DrawPriority = Priority;
	
	// アクターリストの再登録を行う
	dellCellActList(actCell);
	addCellActList(cs, actCell);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	描画優先順位を取得
 *
 *@param	actCell		アクター
 *
 *@return	u32			描画優先順位
 *
 *
 */
//-----------------------------------------------------------------------------
u32 CLACT_DrawPriorityGet( CONST_CLACT_WORK_PTR actCell )
{
	return actCell->DrawPriority;
}

//----------------------------------------------------------------------------
//
/**
 *
 *	@brief	プロクシデータを設定
 *
 *	@param	act			アクター
 *	@param	pImageProxy	設定するイメージプロクシ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_ImageProxySet( CLACT_WORK_PTR act, const NNSG2dImageProxy* pImageProxy )
{
	act->ImageProxy = *pImageProxy;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	プロクシデータを取得
 *
 *	@param	act			アクター
 *
 *	@return	アクターが所持しているイメージプロクシ
 */
//-----------------------------------------------------------------------------
NNSG2dImageProxy * CLACT_ImageProxyGet( CLACT_WORK_PTR act )
{
	return &act->ImageProxy;
}


//--------------------------------------------------------------
/**
 * @brief	プロクシデータを設定
 *
 * @param	act	
 * @param	PaletteProxy	
 *
 * @retval	GLOBAL void	
 *
 */
//--------------------------------------------------------------
void CLACT_PaletteProxySet( CLACT_WORK_PTR act, const NNSG2dImagePaletteProxy*  PaletteProxy)
{
	act->PaletteProxy = *PaletteProxy;
}


//--------------------------------------------------------------
/**
 * @brief	プロクシデータを取得
 *
 * @param	act	
 *
 * @retval	アクターが所持してるプロクシ
 *
 */
//--------------------------------------------------------------
NNSG2dImagePaletteProxy * CLACT_PaletteProxyGet( CLACT_WORK_PTR act )
{
	return &act->PaletteProxy;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	モザイク設定
 *
 *	@param	act		アクターワーク
 *	@param	flag	フラグ	TRUE＝モザイクON	FALSE＝モザイクOFF
 *
 *	@return	none
 *
 * モザイクOFFの時でも、ニトロキャラクタでモザイクONにしたOAMは
 * モザイクがかかって描画されます。
 *
 */
//-----------------------------------------------------------------------------
void CLACT_MosaicSet( CLACT_WORK_PTR act, BOOL flag )
{
	act->mosaic = flag;

	if(flag == TRUE){
		act->over_write |= NNS_G2D_RND_OVERWRITE_MOSAIC;
	}else{
		act->over_write ^= NNS_G2D_RND_OVERWRITE_MOSAIC;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	モザイク設定状態を取得
 *
 *	@param	act		アクターワーク
 *
 *	@retval	TRUE	モザイク＝ON
 *	@retval	FALSE	モザイク＝OFF	（ニトロキャラクタで設定してるときは反映される）
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_MosaicGet( CONST_CLACT_WORK_PTR act )
{
	return act->mosaic;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	VRAMタイプを取得
 *
 *	@param	act		アクターワーク
 *
 *	@retval	VRAMタイプ
 *
 *
 */
//-----------------------------------------------------------------------------
NNS_G2D_VRAM_TYPE CLACT_VramTypeGet( CONST_CLACT_WORK_PTR act )
{
	return act->type;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクターがアニメーション中かチェック
 *
 *	@param	act		アクターワーク
 *
 *	@retval	TRUE	アニメーション中
 *	@retval	FALSE	ストップ
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_AnmActiveCheck( CLACT_WORK_PTR act )
{
	GF_ASSERT( act );

	// シーケンス番号のフレーム数のところにする
	// セルアニメーションかチェック
	if( (act->flag == CLACT_CELL) || (act->flag == CLACT_VRAM_CELL) ){
		CLACT_ANIM_DATA* anm = (CLACT_ANIM_DATA*)&act->AnmData;
		return NNS_G2dIsAnimCtrlActive( &anm->AnmCtrl.animCtrl );
	}else{
		CLACT_MULTICELL_ANIM_DATA* anm = (CLACT_MULTICELL_ANIM_DATA*)&act->AnmData;
		return NNS_G2dIsAnimCtrlActive( &anm->AnmCtrl.animCtrl );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オブジェモードを設定
 *
 *	@param	act			アクターワーク
 *	@param	objmode		オブジェモード 
 *
 *	@return	none
 *
 *	オブジェモードをGX_OAM_MODE_NORMALにするとNitroCharacterで設定した
 *	オブジェモードで描画されます。
 *	
	GX_OAM_MODE_NORMAL		ノーマルOBJ 
	GX_OAM_MODE_XLU			半透明OBJ 
	GX_OAM_MODE_OBJWND OBJ	ウィンドウ 
	GX_OAM_MODE_BITMAPOBJ	ビットマップOBJ 
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_ObjModeSet( CLACT_WORK_PTR act, GXOamMode objmode )
{
	GF_ASSERT(act);
	
	act->objmode = objmode;

	if(objmode == GX_OAM_MODE_NORMAL){
		act->over_write ^= NNS_G2D_RND_OVERWRITE_OBJMODE;
	}else{
		act->over_write |= NNS_G2D_RND_OVERWRITE_OBJMODE;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オブジェモードを取得
 *
 *	@param	act		アクターワーク
 *
 *	@retval	GX_OAM_MODE_NORMAL		ノーマルOBJ 
 *	@retval	GX_OAM_MODE_XLU			半透明OBJ 
 *	@retval	GX_OAM_MODE_OBJWND OBJ	ウィンドウ 
 *	@retval	GX_OAM_MODE_BITMAPOBJ	ビットマップOBJ 
 *
 *	オブジェモードがGX_OAM_MODE_NORMALの時はNitroCharacterで設定した
 *	オブジェモードで描画されます。
 *
 */
//-----------------------------------------------------------------------------
GXOamMode CLACT_ObjModeGet( CONST_CLACT_WORK_PTR act )
{
	GF_ASSERT( act );
	return act->objmode;
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMレジスタクリア　メイン
 *
 *	@param	heap ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void CLACT_UtilOamRamClear_Main( int heap )
{
	void* p_cbff;	// 初期化用バッファ

	p_cbff = sys_AllocMemory( heap, sizeof(GXOamAttr) * 128 );
	memset( p_cbff, 0xC0, sizeof(GXOamAttr) * 128 );
	DC_FlushRange( p_cbff, sizeof(GXOamAttr) * 128 );
	GX_LoadOAM( p_cbff, 0, sizeof(GXOamAttr) * 128 );
	sys_FreeMemoryEz( p_cbff );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMレジスタクリア　サブ
 *
 *	@param	heap ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void CLACT_UtilOamRamClear_Sub( int heap )
{
	void* p_cbff;	// 初期化用バッファ

	p_cbff = sys_AllocMemory( heap, sizeof(GXOamAttr) * 128 );
	memset( p_cbff, 0xC0, sizeof(GXOamAttr) * 128 );
	GXS_LoadOAM( p_cbff, 0, sizeof(GXOamAttr) * 128 );
	sys_FreeMemoryEz( p_cbff );
}


//=============================================================================
//
//	プライベート関数
//
//=============================================================================
//-----------------------------------------------------------------------------
/**
 *@brief				アニメーションデータを読み込む
 *		
 *@param	pSet	セルアクターセット
 *@param	pHeader：各ファイルの入った構造体
 *@param	pWork：動作構造体
 *		 	
 *@retval	TRUE ：成功
 *@retval 	FALSE：失敗
 *
 */
 //----------------------------------------------------------------------------
static BOOL LoadData( const CLACT_SET* pSet, const CLACT_HEADER* pHeader, CLACT_WORK* pWork, int heap )
{
	//
	// アニメーションTypeを調べてアニメーションの読み込みをする
	// アニメーションTypeの取得
	pWork->flag = getActType( pHeader );

	// プロクシ設定
	pWork->ImageProxy = *pHeader->pImageProxy;
	// パレットデータ
	pWork->PaletteProxy = *pHeader->pPaletteProxy;

	// Typeのアニメーションを読み込む
	// Cellデータ
	LoadCell( pHeader->pCellBank, pWork );

	// Cellアニメーションデータ
	if( pHeader->pAnimBank ){
		
		LoadCellAnm( pHeader->pAnimBank, pWork );
	}else{
		
		LoadCellAnm( pSet->pAnimBank, pWork );
	}

	// typeがマルチセルのとき
	if( pWork->flag == CLACT_MULTICELL ){
		// MultiCellデータ
		LoadMultiCell( pHeader->pMCBank, pWork );

		// MultiCellアニメーションデータ
		LoadMultiCellAnm( pHeader->pMCABank, pWork );

		// MultiCellアニメーションコントローラを作成
		MakeMultiCellAnm( pWork , heap);
	}else{
		// Vram転送かチェック
		if( pWork->flag == CLACT_VRAM_CELL ){
			CLACT_VRAM_ANIM_DATA* p_vram = (CLACT_VRAM_ANIM_DATA*)&pWork->AnmData;
		
			
			// セル転送アニメーションでアニメーションコントローラを作成
			MakeCellAnmVram( pHeader, pWork, heap );
		}else{
			// セルアニメーションコントローラを作成
			MakeCellAnm( pWork, heap );
		}
	}

	// BG面との優先度をセット
	pWork->Priority = pHeader->priority;


	return TRUE;
}

//-----------------------------------------------------------------------------
/**
 *@brief				アニメーションTypeを取得する
 *
 *@param	pHeader：アニメデータ（ファイルパスの集まり）
 *		
 *@return	Typeの値
 *
 */
 //----------------------------------------------------------------------------
static u32	getActType( const CLACT_HEADER* pHeader )
{
	//
	// ファイル名があるかをチェックしてアニメーション方法を返す
	//
	// マルチセルアニメーションかチェック
	if( pHeader->pMCBank != NULL ){
		return CLACT_MULTICELL;
	}

	// Vram転送かチェック
	if( pHeader->flag == 1 ){
		return CLACT_VRAM_CELL;
	}

	return CLACT_CELL;
}




//-----------------------------------------------------------------------------
/**
 *@brief				セルデータを読み込む
 *
 *@param	p_str：ファイルパス
 *@param	pWork：動作構造体
 *
 *@return	none
 *
 */
 //----------------------------------------------------------------------------
static void LoadCell( const NNSG2dCellDataBank* Cell, CLACT_WORK* pWork )
{
	CLACT_ANIM_DATA*	pCell;	

	//
	// セルデータを取得
	//
	pCell = (CLACT_ANIM_DATA*)&pWork->AnmData;
	
	// データの設定
	pCell->pCellBank = Cell;
}

//-----------------------------------------------------------------------------
/**
 *@brief				セルアニメーションデータを読み込む
 *
 *@param	p_str：ファイルパス
 *@param	pWork：動作構造体
 *
 *@return	none
 *
 */
 //----------------------------------------------------------------------------
static void LoadCellAnm( const NNSG2dCellAnimBankData* Anm, CLACT_WORK* pWork )
{
	CLACT_ANIM_DATA*	pCell;	

	//
	// セルデータを取得
	//
	pCell = (CLACT_ANIM_DATA*)&pWork->AnmData;
	
	// データの設定
	pCell->pAnimBank = Anm;
}

//-----------------------------------------------------------------------------
/**
 *@brief			マルチセルの読み込み
 *				
 *@param	p_str：ファイルパス
 *@param	pWork：動作構造体
 *
 *@return	none
 *
 */
 //----------------------------------------------------------------------------
static void LoadMultiCell( const NNSG2dMultiCellDataBank* Mlt, CLACT_WORK* pWork )
{
	CLACT_MULTICELL_ANIM_DATA*	pMulti;		// マルチセル用のデータ取得用

	// マルチセル用のデータ取得
	pMulti = (CLACT_MULTICELL_ANIM_DATA*)&pWork->AnmData;

	// データ設定
	pMulti->pMCBank = Mlt;
}

//-----------------------------------------------------------------------------
/**
 *@brief			マルチセルアニメーションの読み込み
 *				
 *@param	p_str：ファイルパス
 *@param	pWork：動作構造体
 *
 *preturn	none
 *
 */
 //----------------------------------------------------------------------------
static void LoadMultiCellAnm( const NNSG2dMultiCellAnimBankData* Anm, CLACT_WORK* pWork )
{
	CLACT_MULTICELL_ANIM_DATA*	pMulti;		// マルチセル用のデータ取得用

	// マルチセル用のデータ取得
	pMulti = (CLACT_MULTICELL_ANIM_DATA*)&pWork->AnmData;

	// データの設定
	pMulti->pMCABank = Anm;
}

//-----------------------------------------------------------------------------
/**
 *@brief			セルアニメーションを構築
 *
 *@param	pWork：動作構造体
 *
 *@return	none
 *
 */
 //----------------------------------------------------------------------------
static void MakeCellAnm( CLACT_WORK* pWork, int heap )
{
	CLACT_ANIM_DATA*	pCell;			// セルデータを取得


	//
	// セルデータを取得
	//
	pCell = (CLACT_ANIM_DATA*)&pWork->AnmData;

	//
	// セルアニメーションを初期化
	//
	NNS_G2dInitCellAnimation(
                (NNSG2dCellAnimation*)&pCell->AnmCtrl,
                NNS_G2dGetAnimSequenceByIdx(pCell->pAnimBank, 0),
                pCell->pCellBank );
}

//-----------------------------------------------------------------------------
/**
 *@brief			セルVram転送アニメーションを構築
 *
 *@param	pWork：動作構造体
 *
 *@return	none
 *
 */
 //----------------------------------------------------------------------------
static void MakeCellAnmVram( const CLACT_HEADER* pHeader, CLACT_WORK* pWork , int heap)
{
	CLACT_VRAM_ANIM_DATA*	pCell;			// セルデータを取得
	const NNSG2dCharacterData* pCharData;	// キャラクタデータ

	//
	// セルデータを取得
	//
	pCell = (CLACT_VRAM_ANIM_DATA*)&pWork->AnmData;

	// セルアニメーションVram転送管理オブジェクトハンドル取得
	pCell->CellTransManHandle = NNS_G2dGetNewCellTransferStateHandle();
	

	// キャラクタデータを設定
	pCharData = pHeader->pCharData;

	//
	// セルVram転送アニメの初期化
	//
	NNS_G2dInitCellAnimationVramTransfered(
                (NNSG2dCellAnimation*)&pCell->AnmCtrl,
                NNS_G2dGetAnimSequenceByIdx(pCell->pAnimBank, 0),
                pCell->pCellBank,

                pCell->CellTransManHandle,  // このセルアニメーションのVRAM転送を管理する
											// セル転送状態管理オブジェクトのハンドル
											// 以下の3つは (1) のCallback関数に dstAddr として渡されます
				// 通常は ImageProxy に指定したものと同じ値を指定します
                NNS_G2D_VRAM_ADDR_NONE ,		// テクスチャ転送先オフセット使用しません
                NNS_G2dGetImageLocation(&pWork->ImageProxy, NNS_G2D_VRAM_TYPE_2DMAIN),      // メイン画面キャラクタ転送先オフセット
                NNS_G2dGetImageLocation(&pWork->ImageProxy, NNS_G2D_VRAM_TYPE_2DSUB),		// サブ画面キャラクタ転送先オフセット
                pCharData->pRawData,  // キャラクタデータ
                NULL,				  // テクスチャデータ
                pCharData->szByte     // テクスチャデータ or キャラクタデータのサイズ
            );
}

//-----------------------------------------------------------------------------
/**
 *@brief			マルチセルアニメーションを構築
 *					これを行う前にセルアニメーションの構築が必要
 *
 *@param	pWork：動作構造体
 *
 *@return	none
 *
 */
 //----------------------------------------------------------------------------
static void MakeMultiCellAnm( CLACT_WORK* pWork, int heap )
{
	CLACT_MULTICELL_ANIM_DATA*	pCell;			// セルデータを取得
	const NNSG2dMultiCellAnimSequence* pSequence;
    u16 numNodes;


	//
	// セルデータを取得
	//
	pCell = (CLACT_MULTICELL_ANIM_DATA*)&pWork->AnmData;

	
	// 再生するシーケンスを取得
	pSequence = NNS_G2dGetAnimSequenceByIdx( pCell->pMCABank, 0 );

	// このマルチセルの各シーケンスに必要なノードの最大数を取得
	numNodes = NNS_G2dGetMCBankNumNodesRequired( pCell->pMCBank );
	
	// ヒープから numNode ぶんの NNSG2dNode と NNSG2dCellAnimation を取得
    pCell->pNode     = sys_AllocMemory( heap, sizeof(NNSG2dNode) * numNodes );
    pCell->pCellAnim = sys_AllocMemory( heap, sizeof(NNSG2dCellAnimation) * numNodes );

	
	
	//
	// マルチセルアニメーションコントローラを構築
	// 
    NNS_G2dInitMCAnimation( (NNSG2dMultiCellAnimation*)&pCell->AnmCtrl,	// マルチセルアニメーション
                            pCell->pNode,			// ノード配列
                            pCell->pCellAnim,		// セルアニメーション配列
                            numNodes,				// ノード数
                            pCell->pAnimBank,		// アニメーションデータバンク
                            pCell->pCellBank,		// セルデータバンク
                            pCell->pMCBank );		// マルチセルデータバンク


	// マルチセルアニメーションに再生するシーケンスをセット
    NNS_G2dSetAnimSequenceToMCAnimation(
                (NNSG2dMultiCellAnimation*)&pCell->AnmCtrl,
                pSequence );

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットプロクシのあるパレットナンバーを取得する
 *
 *@param	pPltt：パレットナンバーを取得するパレットプロクシ
 *@param	vramType：メイン面かサブ面か
 *
 *@return	パレットナンバー
 *
 */
//-----------------------------------------------------------------------------
static u32 GetPlttProxyOffset( const NNSG2dImagePaletteProxy* pPltt, u32 vramType )
{
	u32 size;			// １パレットサイズ
	u32 pltt_offset;	// パレットナンバー計算処理用
	
	// 拡張パレットかチェック
	if( pPltt->bExtendedPlt ){
		size = PLTT_ONE_SIZE * 16;
	}else{
		// 標準で256でないかチェック
		if( pPltt->fmt == GX_TEXFMT_PLTT256 ){
			// 256の時はサイズを０にして計算しない
			size = 0;
		}else{
			size = PLTT_ONE_SIZE;
		}
	}

	// 標準２５６色以外かチェック
	if( size != 0 ){
		// ずらす値取得
		pltt_offset = NNS_G2dGetImagePaletteLocation( pPltt, vramType );
		pltt_offset /= size;			// ずらす値にする(何パレットずらすか)
	}else{
		pltt_offset = 0;
	}

	return pltt_offset;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	レンダラーを使用した高度な描画
 *
 *@param	pClActSet	セルアクターセット
 *@param	act			アクターポインタ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void renderDraw(const CLACT_SET* pClActSet, CLACT_WORK* act)
{
	
	VecFx32	matrix = act->Matrix;
	
	// プロキシ登録
	NNS_G2dSetRendererImageProxy( pClActSet->pRender, &act->ImageProxy, &act->PaletteProxy );
	
	NNS_G2dBeginRendering( pClActSet->pRender );		// 描画開始
	
	// 描画
	NNS_G2dPushMtx();{

		// アフィン変換　フリップモード設定
		// アフィン変換設定
		NNS_G2dSetRndCoreAffineOverwriteMode(
				&( pClActSet->pRender->rendererCore ),
				act->affin );
		
		if(act->affin == CLACT_AFFINE_NONE){
			// フリップ設定
			NNS_G2dSetRndCoreFlipMode(
					&( pClActSet->pRender->rendererCore ),
					act->flip & CLACT_FLIP_H,
					act->flip & CLACT_FLIP_V);
		}else{
			// フリップ設定
			NNS_G2dSetRndCoreFlipMode(
					&( pClActSet->pRender->rendererCore ),
					FALSE,
					FALSE );
		}
		
		
		NNS_G2dTranslate( matrix.x, matrix.y, matrix.z );
		
		if(act->affin != CLACT_AFFINE_NONE){
			NNS_G2dTranslate( act->AffineMatrix.x, act->AffineMatrix.y, act->AffineMatrix.z );
			NNS_G2dScale( act->Scale.x, act->Scale.y, act->Scale.z );
			NNS_G2dRotZ( FX_SinIdx(act->Rotation), FX_CosIdx(act->Rotation) );
			NNS_G2dTranslate( -act->AffineMatrix.x, -act->AffineMatrix.y, -act->AffineMatrix.z );
		}

	
		// オーバーライト有効フラグ設定
		NNS_G2dSetRendererOverwriteEnable( pClActSet->pRender, act->over_write );

		// オーバーライト無効フラグ設定
		NNS_G2dSetRendererOverwriteDisable( pClActSet->pRender, ~act->over_write );
		
		// パレットナンバー設定
		NNS_G2dSetRendererOverwritePlttNo( pClActSet->pRender, act->palNo );
		
		// パレットオフセット設定
		NNS_G2dSetRendererOverwritePlttNoOffset( pClActSet->pRender, act->palOfs );

		// オーバーライトにモザイクの値を設定
		NNS_G2dSetRendererOverwriteMosaicFlag( pClActSet->pRender, act->mosaic );

		// オーバーライトにOBJモードの値を設定
		NNS_G2dSetRendererOverwriteOBJMode( pClActSet->pRender, act->objmode );

		// BG優先順位を設定
		NNS_G2dSetRendererOverwritePriority( pClActSet->pRender, act->Priority );
		
		// セルアニメかマルチセルあにめかチェック
		if( (act->flag == CLACT_CELL) || (act->flag == CLACT_VRAM_CELL) ){
			CLACT_ANIM_DATA* anim = (CLACT_ANIM_DATA*)&act->AnmData;
			
			// 描画
			NNS_G2dDrawCellAnimation( &anim->AnmCtrl );
		}
		else{
			CLACT_MULTICELL_ANIM_DATA* anim = (CLACT_MULTICELL_ANIM_DATA*)&act->AnmData;

			// 描画
			NNS_G2dDrawMultiCellAnimation( &anim->AnmCtrl );
		}
	}
	NNS_G2dPopMtx();
	NNS_G2dEndRendering();					// 描画終了
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画しない
 *
 *	@param	pClActSet		セルアクターセット
 *	@param	act				セルアクター
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void noDraw( const CLACT_SET* pClActSet, CLACT_WORK* act )
{
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オートアニメーション
 *
 *	@param	act			アクター
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void autoAnm( CLACT_WORK* act )
{
	// アニメーション
	CLACT_AnmFrameChg( act, act->Frame );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オートアニメーションなし
 *
 *	@param	act		アクター
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void noAnm( CLACT_WORK* act )
{
}

/*-----------------------------------------------------------------------------
 *
 *		リスト処理
 * 
 *===========================================================================*/
//-----------------------------------------------------------------------------
/**
 *@brief			リストに追加
 *
 *@param	cs			セルアクターセット
 *@param	pWork		追加するセルアクターデータ
 *
 *@return	none
 *
 *
 */
 //----------------------------------------------------------------------------
static void addCellActList( CLACT_SET* cs, CLACT_WORK* pWork )
{
	CLACT_WORK* p_work;		// ループ用
	
	
	// 先頭が開いているかチェック
	if(cs->Dummy.pNext == &cs->Dummy){
		
		cs->Dummy.pNext	= pWork;
		cs->Dummy.pLast	= pWork;
		pWork->pLast			= &cs->Dummy;
		pWork->pNext			= &cs->Dummy;
	}else{
		
		// 最後のデータの優先順位が自分の優先順位以下なら最後にセット
		if(cs->Dummy.pLast->DrawPriority <= pWork->DrawPriority){
			
			pWork->pLast			= cs->Dummy.pLast;
			cs->Dummy.pLast->pNext	= pWork;
			pWork->pNext			= &cs->Dummy;
			cs->Dummy.pLast			= pWork;
		}else{
		
			// 自分の優先順位より大きいデータの前に追加
			p_work = cs->Dummy.pNext;		// 先頭データセット
			while(p_work != &cs->Dummy){		// ダミーデータになるまで
				// p_workの優先順位がpWorkの優先順位より多きとき
				// p_workの前に登録する
				if(p_work->DrawPriority > pWork->DrawPriority){

					p_work->pLast->pNext	= pWork;
					pWork->pLast			= p_work->pLast;
					p_work->pLast			= pWork;
					pWork->pNext			= p_work;
					break;
				}

				p_work = p_work->pNext;
			}
		}
	}
}

//-----------------------------------------------------------------------------
/**
 *@brief			リストから削除
 *
 *@param	pWork		削除するセルアクターデータ
 *
 *@return	none
 *
 *
 */
 //----------------------------------------------------------------------------
static void dellCellActList( CLACT_WORK* pWork )
{
	// リストを外す
	pWork->pLast->pNext = pWork->pNext;
	pWork->pNext->pLast = pWork->pLast;
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
static void initStack(CLACT_SET* pSet)
{
	int i;

	// 初期化
	for (i=0; i<pSet->WorkNum; i++) {
		CLACT_WorkClear(&pSet->pWork[i]);
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
static CLACT_WORK* popStack(CLACT_SET* pSet)
{
	CLACT_WORK*	ret;
	
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
static BOOL pushStack(CLACT_SET* pSet, CLACT_WORK* pDat)
{
	if(pSet->WorkStackNow <= 0){	// 空きチェック
		return FALSE;
	}
	CLACT_WorkClear(pDat);
	pSet->WorkStackNow--;
	pSet->ppWorkStack[pSet->WorkStackNow] = pDat;

	return TRUE;
}
