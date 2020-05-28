//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		clact.h
 *@brief	セルアクター
 *@author	tomoya takahashi
 *@data		2005.05.19
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#ifndef _CLACT_H__
#define	_CLACT_H__

#include <nnsys.h>

#undef	GLOBAL
#ifdef	_CLACT_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
 */
//-----------------------------------------------------------------------------

//--------------------------------------------------------------
//	OAMタイプ
//--------------------------------------------------------------
#define OAMTYPE_8x8				(0)						// OAMアクターヘッダ OAM型 8x8
#define OAMTYPE_16x16			(1)						// 16x16
#define OAMTYPE_32x32			(2)						// 32x32
#define OAMTYPE_64x64			(3)						// 64x64
#define OAMTYPE_16x8			(4)						// 16x8
#define OAMTYPE_32x8			(5)						// 32x8
#define OAMTYPE_32x16			(6)						// 32x16
#define OAMTYPE_64x32			(7)						// 64x32
#define OAMTYPE_8x16			(8)						// 8x16
#define OAMTYPE_8x32			(9)						// 8x32
#define OAMTYPE_16x32			(10)					// 16x32
#define OAMTYPE_32x64			(11)					// 32x64

//--------------------------------------------------------------
//	OAM BGプライオリティ
//--------------------------------------------------------------
#define OAMBGPRI_0				(0)
#define OAMBGPRI_1				(1)
#define OAMBGPRI_2				(2)
#define OAMBGPRI_3				(3)

//--------------------------------------------------------------
//	OAM パレットNo
//--------------------------------------------------------------
#define OAMPALNO_0				(0)
#define OAMPALNO_1				(1)
#define OAMPALNO_2				(2)
#define OAMPALNO_3				(3)
#define OAMPALNO_4				(4)
#define OAMPALNO_5				(5)
#define OAMPALNO_6				(6)
#define OAMPALNO_7				(7)
#define OAMPALNO_8				(8)
#define OAMPALNO_9				(9)
#define OAMPALNO_10				(10)
#define OAMPALNO_11				(11)
#define OAMPALNO_12				(12)
#define OAMPALNO_13				(13)
#define OAMPALNO_14				(14)
#define OAMPALNO_15				(15)

//--------------------------------------------------------------
//	OAM拡縮パラメータ番号
//--------------------------------------------------------------
#define OAMAFFNO_0				(0)
#define OAMAFFNO_1				(1)
#define OAMAFFNO_2				(2)
#define OAMAFFNO_3				(3)
#define OAMAFFNO_4				(4)
#define OAMAFFNO_5				(5)
#define OAMAFFNO_6				(6)
#define OAMAFFNO_7				(7)
#define OAMAFFNO_8				(8)
#define OAMAFFNO_9				(9)
#define OAMAFFNO_10				(10)
#define OAMAFFNO_11				(11)
#define OAMAFFNO_12				(12)
#define OAMAFFNO_13				(13)
#define OAMAFFNO_14				(14)
#define OAMAFFNO_15				(15)
#define OAMAFFNO_16				(16)
#define OAMAFFNO_17				(17)
#define OAMAFFNO_18				(18)
#define OAMAFFNO_19				(19)
#define OAMAFFNO_20				(20)
#define OAMAFFNO_21				(21)
#define OAMAFFNO_22				(22)
#define OAMAFFNO_23				(23)
#define OAMAFFNO_24				(24)
#define OAMAFFNO_25				(25)
#define OAMAFFNO_26				(26)
#define OAMAFFNO_27				(27)
#define OAMAFFNO_28				(28)
#define OAMAFFNO_29				(29)
#define OAMAFFNO_30				(30)
#define OAMAFFNO_31				(31)

//--------------------------------------------------------------
//	OBJキャラサイズ 16色
//--------------------------------------------------------------
#define OBJ_CHAR_SIZE			(32)					// OBJ 1キャラサイズ 32byte
#define OBJSIZE_8x8				(OBJ_CHAR_SIZE*1)		// 8x8キャラサイズ
#define OBJSIZE_16x16			(OBJ_CHAR_SIZE*4)		// 16x16
#define OBJSIZE_32x32			(OBJ_CHAR_SIZE*16)		// 32x32
#define OBJSIZE_64x64			(OBJ_CHAR_SIZE*64)		// 64x64
#define OBJSIZE_16x8			(OBJ_CHAR_SIZE*2)		// 16x8
#define OBJSIZE_32x8			(OBJ_CHAR_SIZE*4)		// 32x8
#define OBJSIZE_32x16			(OBJ_CHAR_SIZE*8)		// 32x16
#define OBJSIZE_64x32			(OBJ_CHAR_SIZE*32)		// 64x32
#define OBJSIZE_8x16			(OBJ_CHAR_SIZE*2)		// 8x16
#define OBJSIZE_8x32			(OBJ_CHAR_SIZE*4)		// 8x32
#define OBJSIZE_16x32			(OBJ_CHAR_SIZE*8)		// 16x32
#define OBJSIZE_32x64			(OBJ_CHAR_SIZE*32)		// 32x64

//--------------------------------------------------------------
//	OBJキャラサイズ 256色
//--------------------------------------------------------------
#define OBJ_CHAR_SIZE256		(64)					// OBJ 1キャラサイズ 64byte
#define OBJSIZE256_8x8			(OBJ_CHAR_SIZE256*1)	// OBJ8x8キャラサイズ
#define OBJSIZE256_16x16		(OBJ_CHAR_SIZE256*4)	// 16x16
#define OBJSIZE256_32x32		(OBJ_CHAR_SIZE256*16)	// 32x32
#define OBJSIZE256_64x64		(OBJ_CHAR_SIZE256*64)	// 64x64
#define OBJSIZE256_16x8			(OBJ_CHAR_SIZE256*2)	// 16x8
#define OBJSIZE256_32x8			(OBJ_CHAR_SIZE256*4)	// 32x8
#define OBJSIZE256_32x16		(OBJ_CHAR_SIZE256*8)	// 32x16
#define OBJSIZE256_64x32		(OBJ_CHAR_SIZE256*32)	// 64x32
#define OBJSIZE256_8x16			(OBJ_CHAR_SIZE256*2)	// 8x16
#define OBJSIZE256_8x32			(OBJ_CHAR_SIZE256*4)	// 8x32
#define OBJSIZE256_16x32		(OBJ_CHAR_SIZE256*8)	// 16x32
#define OBJSIZE256_32x64		(OBJ_CHAR_SIZE256*32)	// 32x64

//--------------------------------------------------------------
//	OBJキャラ数
//--------------------------------------------------------------
#define OBJNO_8x8				(1)						// 8x8OBJキャラ数1
#define	OBJNO_16x16				(4)						// 16x16
#define	OBJNO_32x32				(16)					// 32x32
#define	OBJNO_64x64				(64)					// 64x64
#define	OBJNO_16x8				(2)						// 16x8
#define	OBJNO_32x8				(4)						// 32x8
#define	OBJNO_32x16				(8)						// 32x16
#define	OBJNO_64x32				(32)					// 64x32
#define	OBJNO_8x16				(2)						// 8x16
#define	OBJNO_8x32				(4)						// 8x32
#define	OBJNO_16x32				(8)						// 16x32
#define	OBJNO_32x64				(32)					// 32x64




//-------------------------------------
/// 描画種類
//	個々のワークに設定する描画フラグ
//	デフォはレンダラー描画
enum{
	CLACT_DRAW_NONE,		// 描画しない
	CLACT_DRAW_RENDERER,	// レンダラー描画
};

//-------------------------------------
//	
//	アフィン、倍角アフィン、アフィンなし
//	フラグ
//	
//=====================================
enum{
	CLACT_AFFINE_NONE,		// アフィン変換なし
	CLACT_AFFINE_NORMAL,	// アフィン変換
	CLACT_AFFINE_DOUBLE,	// 倍角アフィン変換
};

//-------------------------------------
//	
//	両方向へのフリップ
//	
//=====================================
enum{
	CLACT_FLIP_NONE,		// フリップなし
	CLACT_FLIP_H,			// フリップ水平方向
	CLACT_FLIP_V,			// フリップ垂直方向
	CLACT_FLIP_HV,			// 両方向フリップ
};

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
 */
//-----------------------------------------------------------------------------
typedef struct _CLACT_SET*		CLACT_SET_PTR;			// セルアクターセットポインタ
typedef const struct _CLACT_SET* CONST_CLACT_SET_PTR;	// コンスト型

typedef struct CLACT_WORK_tag*	CLACT_WORK_PTR;			// セルアクターセットポインタ
typedef const struct CLACT_WORK_tag* CONST_CLACT_WORK_PTR;	// セルアクターセットポインタ



//-------------------------------------
//
//	セルアクターセット作成関数
//						引数構造体
//
//=====================================
typedef struct{
	int		WorkNum;		// セルアクター動作構造体配列数

	// OAMマネージャポインタ
//	NNSG2dOamManagerInstance* pMainMan;
//	NNSG2dOamManagerInstance* pSubMan;

	// レンダラーポインタ
	// レンダラー描画を行うときは、
	// 作成してから登録してください。
	NNSG2dRendererInstance*		pRender;			// 描画用 Renderer
	
	int	heap;				// 使用するヒープ
}CLACT_SETDATA;

//-------------------------------------
///	ヘッダーデータ	
typedef struct _CLACT_HEADER{
	const NNSG2dImageProxy*				pImageProxy;	// キャラクタ/テクスチャプロキシ
	const NNSG2dCharacterData*			pCharData;		// キャラクタデータ		（Vram転送時のみ必要）
	const NNSG2dImagePaletteProxy*		pPaletteProxy;	// パレットプロキシ
	NNSG2dCellDataBank*					pCellBank;		// セルデータ
    const NNSG2dCellAnimBankData*       pAnimBank;		// セルアニメーション		（無いときNULL）
	const NNSG2dMultiCellDataBank*      pMCBank;		// マルチセルデータ			（無いときNULL）
    const NNSG2dMultiCellAnimBankData*  pMCABank;		// マルチセルアニメーション	（無いときNULL）
	
	int  flag;				//転送アニメ確認用のフラグ
	u8	 priority;			// BG面との優先度

}CLACT_HEADER;

typedef struct _CLACT_HEADER*	CLACT_HEADER_PTR;		// セルアクターヘッダーポインタ

//-------------------------------------
//
//	セルアクター登録構造体
//
//=====================================
typedef struct{
	CLACT_SET_PTR	ClActSet;	// セルアクターセット
	const CLACT_HEADER*	ClActHeader;// ヘッダーデータ
	VecFx32				mat;		// 座標		
	VecFx32				sca;		// 拡大値
	u16					rot;		// 回転		(0～65535)
	u32					pri;		// 優先順位
	int					DrawArea;	// 描画面
		// mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN
		// subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB

	int					heap;		// 使用するヒープ
}CLACT_ADD;

//-------------------------------------
//
//	セルアクターシンプル登録構造体
//
//=====================================
typedef struct{
	CLACT_SET_PTR	ClActSet;	// セルアクターセット
	const CLACT_HEADER*	ClActHeader;// ヘッダーデータ
	VecFx32				mat;		// 座標
	u32					pri;		// 優先順位
	int					DrawArea;	// 描画面
		// mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN
		// subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB
	

	int					heap;		// 使用するヒープ
}CLACT_ADD_SIMPLE;

//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
//=============================================================================
//
//		アクターセット操作関数
//
//=============================================================================
//-----------------------------------------------------------------------------
/**
 *@brief			セルアクターセットの初期化
 *
 *@param	pSetData		セルアクターセット作成データ
 *
 *@retval	CLACT_SET_PTR			作成したセルアクターセットのポインタ
 *@retval	NULL					失敗
 *
 * セルアクターセットを作成
 *
 */
 //----------------------------------------------------------------------------
GLOBAL CLACT_SET_PTR CLACT_InitSet( const CLACT_SETDATA* pSetData );

//-----------------------------------------------------------------------------
/**
 *@brief			セルアクターセットの破棄
 *
 *@param	ClActSet			破棄するセルアクターセットポインタ
 *
 *@retval	TRUE	成功
 *@retval	FALSE	失敗	(ClActSetがNULL)
 *
 * セルアクターセットを破棄する
 *		実行していたアクターオブジェも一斉解放
 *
 */
 //----------------------------------------------------------------------------
GLOBAL BOOL CLACT_DestSet( CLACT_SET_PTR ClActSet );

//-----------------------------------------------------------------------------
/**
 *@brief			セルアクターセットの描画フラグを設定
 *
 *@param	ClActSet			破棄するセルアクターセットポインタ
 *@param	flag				0:非描画	1:描画
 *
 *@retval	TRUE	成功
 *@retval	FALSE	失敗	(ClActSetがNULL)
 *
 *	登録されているセル全てを描画/非描画するかを設定
 *
 */
 //----------------------------------------------------------------------------
GLOBAL BOOL CLACT_DrawFlagSet( CLACT_SET_PTR ClActSet, u8 flag );

//-----------------------------------------------------------------------------
/**
 *@brief				描画する
 *
 *@param	pClAct		セルアクターセット
 *
 *@return	none
 */
 //----------------------------------------------------------------------------
GLOBAL void CLACT_Draw( CONST_CLACT_SET_PTR pClAct );

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
GLOBAL NNSG2dRendererInstance* CLACT_RenderGet( CONST_CLACT_SET_PTR pClAct);

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
GLOBAL void CLACT_RenderSet( CLACT_SET_PTR pClAct, NNSG2dRendererInstance* pRender);


//-----------------------------------------------------------------------------
/**
 *@brief			全アクター破棄
 *
 *@param	ClActSet		セルアクターセットインデックス
 *
 *@retval	TRUE	成功
 *@retval	FALSE	失敗	(ClActSetIdxがNULL)
 */
 //----------------------------------------------------------------------------
GLOBAL BOOL CLACT_DelAllSet( CLACT_SET_PTR ClActSet );


//=============================================================================
//
//		セルアクターワーク操作関数
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
GLOBAL void CLACT_WorkClear( CLACT_WORK_PTR pWork );

//-----------------------------------------------------------------------------
/**
 *@brief		セルアクターワークの取得
 *						
 *
 *@param	ClActSetIdx		セルアクターセットインデックス
 *@param	ClActIdx		セルアクターワークインデックス
 *
 *@retval	CLACT_WORK_PTR	成功
 *@retval	NULL			失敗
 *
 */
//----------------------------------------------------------------------------
GLOBAL CLACT_WORK_PTR CLACT_GetWork(CONST_CLACT_SET_PTR ClActSet, s16 ClActIdx);

//-----------------------------------------------------------------------------
/**
 *@brief			追加処理
 *
 *@param	add		登録データ
 *
 *@retval	CLACT_WORK_PTR		登録したアクターポインタ
 *@retval	NULL				失敗
 */
// ----------------------------------------------------------------------------
GLOBAL CLACT_WORK_PTR CLACT_Add(const CLACT_ADD* add);

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
GLOBAL CLACT_WORK_PTR CLACT_AddSimple(const CLACT_ADD_SIMPLE* add);

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
GLOBAL void CLACT_Delete(CLACT_WORK_PTR del);

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
GLOBAL void CLACT_SetMatrix(CLACT_WORK_PTR act, const VecFx32* Matrix);

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アフィン変換座標を設定
 *
 *	@param	act			アクター
 *	@param	Matrix		アフィン変換を反映させるオフセット座標
 *
 *	@return	none
 *
 * アクターに設定されている座標 + アフィン変換座標
 * の位置で回転拡大縮小を行います。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_SetAffineMatrix(CLACT_WORK_PTR act, const VecFx32* Matrix);

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
 * 設定してもアフィンフラグが
 *	CLACT_AFFINE_NORMALかCLACT_AFFINE_DOUBLEでないと反映されません。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_SetScale(CLACT_WORK_PTR act, const VecFx32* Scale);

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
GLOBAL void CLACT_SetScaleAffine(CLACT_WORK_PTR act, const VecFx32* Scale, int affine);

//----------------------------------------------------------------------------
/**
 *
 *@brief	回転角を設定
 *
 *@param	act			アクター
 *@param	Rotation	回転角		(0～65535)
 *
 *@return	none
 *
 * 設定してもアフィンフラグが
 *	CLACT_AFFINE_NORMALかCLACT_AFFINE_DOUBLEでないと反映されません。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_SetRotation(CLACT_WORK_PTR act, u16 Rotation);

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
GLOBAL void CLACT_SetRotationAffine(CLACT_WORK_PTR act, u16 Rotation, int affine);

//----------------------------------------------------------------------------
/**
 *
 *@brief	描画フラグを設定
 *
 *@param	act		アクター
 *@param	flag	描画フラグ	0:非描画	1:レンダラー描画
 *
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_SetDrawFlag(CLACT_WORK_PTR act, int flag);

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
GLOBAL void CLACT_SetAnmFlag(CLACT_WORK_PTR act, int flag);

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
GLOBAL void CLACT_SetAnmFrame(CLACT_WORK_PTR act, fx32 frame);

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
GLOBAL void CLACT_SetAffineParam( CLACT_WORK_PTR act, int param );

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
 *	"アフィン変換フラグをCLACT_AFFINE_NONEにします"
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_SetFlip( CLACT_WORK_PTR act, int flag );

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
GLOBAL const VecFx32* CLACT_GetMatrix(CONST_CLACT_WORK_PTR act);

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
GLOBAL const VecFx32* CLACT_GetAffineMatrix(CONST_CLACT_WORK_PTR act);

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
GLOBAL const VecFx32* CLACT_GetScale(CONST_CLACT_WORK_PTR act);

//----------------------------------------------------------------------------
/**
 *
 *@brief	回転角度を取得
 *
 *@param	act		アクター
 *
 *@return	u16		回転角度	(0～65535)
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u16 CLACT_GetRotation(CONST_CLACT_WORK_PTR act);

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
GLOBAL int CLACT_GetDrawFlag(CONST_CLACT_WORK_PTR act);

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
GLOBAL int CLACT_GetAnmFlag(CONST_CLACT_WORK_PTR act);

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
GLOBAL fx32 CLACT_GetAnmFrame(CONST_CLACT_WORK_PTR act);

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
GLOBAL int CLACT_GetAffineParam( CONST_CLACT_WORK_PTR act );

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
GLOBAL int CLACT_GetFlip( CONST_CLACT_WORK_PTR act );

//-----------------------------------------------------------------------------
/*
 * ●無条件にアニメーションシーケンスを変更します。
 * 
 *@brief	アニメーションのシーケンスをチェンジする
 *
 *@param	actCell：セルアクター
 *@param	num：シーケンスナンバー
 *
 *@return	none
 *
 *	同じシーケンスナンバーでもシーケンス変更を行いフレーム０からアニメを
 *	はじめます。
 * 
 */
 //----------------------------------------------------------------------------
GLOBAL void CLACT_AnmChg( CLACT_WORK_PTR actCell, u32 num );

//-----------------------------------------------------------------------------
/*
 * ●アニメーションシーケンスが違ったら変更します。
 * 
 *@brief	アニメーションのシーケンスをチェンジする
 *
 *@param	actCell：セルアクター
 *@param	num：シーケンスナンバー
 *
 *@return	none
 *
 * アニメーションシーケンスが同じときは何も行いません。
 *
 */
 //----------------------------------------------------------------------------
GLOBAL void CLACT_AnmChgCheck( CLACT_WORK_PTR actCell, u32 num );

//----------------------------------------------------------------------------
/**
 *	@brief	アニメーションリスタート
 *
 *	@param	actCell		セルアクタ－
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_AnmReStart( CLACT_WORK_PTR actCell );

//----------------------------------------------------------------------------
/**
 *
 *@brief	現在のアニメーションシーケンスを取得
 *
 *@param	actCell		アクター
 *
 *@return			アニメーションシーケンスナンバー
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u32 CLACT_AnmGet( CONST_CLACT_WORK_PTR actCell );

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
GLOBAL void CLACT_AnmFrameChg( CLACT_WORK_PTR actCell, fx32 num );

//-----------------------------------------------------------------------------
/**	
 *@brief	アニメーションフレームをセット
 *
 *@param	actCell：動作構造体
 *@param	num：セットするアニメーション ｲﾝﾃﾞｯｸｽ値
 *				この値はNitroCharacterに設定されているCellAnmのNoの項目の数字が入ります。
 *
 *@return	none
 */
//----------------------------------------------------------------------------
GLOBAL void CLACT_AnmFrameSet( CLACT_WORK_PTR actCell, u16 num );

//-----------------------------------------------------------------------------
/**	
 *@brief				アニメーションフレームを取得
 *
 *@param	actCell：動作構造体
 *
 *@return	今ｲﾝﾃﾞｯｸｽ値
 *				この値はNitroCharacterに設定されているCellAnmのNoの項目の数字が入ります。
 */
//----------------------------------------------------------------------------
GLOBAL u16 CLACT_AnmFrameGet( CONST_CLACT_WORK_PTR actCell);


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
GLOBAL void CLACT_BGPriorityChg( CLACT_WORK_PTR actCell, u8 Priority );

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
GLOBAL u8 CLACT_BGPriorityGet( CONST_CLACT_WORK_PTR actCell);

//-----------------------------------------------------------------------------
/**
 * ●OAMがこのパレットナンバーを見るようになります。
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
GLOBAL void CLACT_PaletteNoChg( CLACT_WORK_PTR actCell, u32 pltt_num );

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
GLOBAL void CLACT_PaletteNoChgAddTransPlttNo( CLACT_WORK_PTR actCell, u32 pltt_num );

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
GLOBAL u32 CLACT_PaletteNoGet( CONST_CLACT_WORK_PTR actCell );

//-----------------------------------------------------------------------------
/**
 * ●OAMアトリビュートに設定されているパレットナンバーに加算されます。
 *	 もし、OAMアトリビュートのカラーパレットNoが２でオフセットに２を
 *	 設定すると、４のカラーパレットを参照するようになります
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
GLOBAL void CLACT_PaletteOffsetChg( CLACT_WORK_PTR actCell, u32 pltt_num );

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
GLOBAL void CLACT_PaletteOffsetChgAddTransPlttNo( CLACT_WORK_PTR act, u32 pltt_num );

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットオフセット値取得
 *
 *@param	actCell		アクター
 *
 *@return	u32		今のパレットオフセット値
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u32 CLACT_PaletteOffsetGet( CONST_CLACT_WORK_PTR actCell );

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
GLOBAL void CLACT_DrawPriorityChg( CLACT_WORK_PTR actCell, u32 Priority );

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
GLOBAL u32 CLACT_DrawPriorityGet( CONST_CLACT_WORK_PTR actCell );

//----------------------------------------------------------------------------
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
GLOBAL void CLACT_ImageProxySet( CLACT_WORK_PTR act, const NNSG2dImageProxy* pImageProxy );

//----------------------------------------------------------------------------
//
/**
 *
 *	@brief	プロクシデータを取得
 *
 *	@param	act			アクター
 *
 *	@return	アクターが所持しているイメージプロクシ
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dImageProxy * CLACT_ImageProxyGet( CLACT_WORK_PTR act );


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
GLOBAL void CLACT_PaletteProxySet( CLACT_WORK_PTR act, const NNSG2dImagePaletteProxy*  PaletteProxy);

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
GLOBAL NNSG2dImagePaletteProxy * CLACT_PaletteProxyGet( CLACT_WORK_PTR act );

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
GLOBAL void CLACT_MosaicSet( CLACT_WORK_PTR act, BOOL flag );

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
GLOBAL BOOL CLACT_MosaicGet( CONST_CLACT_WORK_PTR act );

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
GLOBAL NNS_G2D_VRAM_TYPE CLACT_VramTypeGet( CONST_CLACT_WORK_PTR act );

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
GLOBAL BOOL CLACT_AnmActiveCheck( CLACT_WORK_PTR act );

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
	GX_OAM_MODE_OBJWND		OBJウィンドウ 
	GX_OAM_MODE_BITMAPOBJ	ビットマップOBJ 
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_ObjModeSet( CLACT_WORK_PTR act, GXOamMode objmode );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オブジェモードを取得
 *
 *	@param	act		アクターワーク
 *
 *	@retval	GX_OAM_MODE_NORMAL		ノーマルOBJ 
 *	@retval	GX_OAM_MODE_XLU			半透明OBJ 
 *	@retval	GX_OAM_MODE_OBJWND		OBJウィンドウ 
 *	@retval	GX_OAM_MODE_BITMAPOBJ	ビットマップOBJ 
 *
 *	オブジェモードがGX_OAM_MODE_NORMALの時はNitroCharacterで設定した
 *	オブジェモードで描画されます。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL GXOamMode CLACT_ObjModeGet( CONST_CLACT_WORK_PTR act );


//----------------------------------------------------------------------------
/**
 *	@brief	OAMレジスタクリア　メイン
 *
 *	@param	heap ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_UtilOamRamClear_Main( int heap );

//----------------------------------------------------------------------------
/**
 *	@brief	OAMレジスタクリア　サブ
 *
 *	@param	heap ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_UtilOamRamClear_Sub( int heap );


#undef	GLOBAL
#endif

