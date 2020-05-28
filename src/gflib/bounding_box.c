//============================================================================================
/**
 * @file	bounding_box.c
 * @brief	3Dモデルのカメラ内外判定処理
 * @author	Nozomu Saito
 * @date	2005.10.28
 */
//============================================================================================

#include "bounding_box.h"

#ifdef PM_DEBUG
///#define DRAW_BOUNDING_BOX	//バウンディングボックス表示
#endif //PM_DEBUG


static void SetBoxSize( const fx16 x,
						const fx16 y,
						const fx16 z,
						const fx16 width,
						const fx16 height,
						const fx16 depth,
						GXBoxTestParam *outBox);

static u32 CheckBoundingBox( const GXBoxTestParam	*inBox );
static void CulcFx32toFx16(const fx32 inFx32, fx16 *outFx16, int *outMul);

#ifdef DRAW_BOUNDING_BOX
static void DrawBox( const GXBoxTestParam *inBox );
#endif //DRAW_BOUNDING_BOX

//----------------------------------------------------------------------------
/**
 *
 *@brief	カリングチェック
 *
 *@param	object_p		レンダーオブジェ
 *@param	trans_p			平行移動値
 *@param	rot_p			回転行列
 *@param	scale_p			拡縮値
 *
 *@return	u32			0以外の値であれば、ボックスの一部または全部が視体積内
 *						0であれば、ボックスの全てが視体積外
 *
 */
//-----------------------------------------------------------------------------
u32	BB_CullingCheck3DModel(	const NNSG3dResMdl* model_p,
							const VecFx32* trans_p,
							const MtxFx33* rot_p,
							const VecFx32* scale_p )
{
	u32 check_ret;		// チェックの戻り値用
	GXBoxTestParam bounding_box;
	VecFx32 obj_box_trans;
	NNSG3dResMdlInfo*	model_info;		// モデルデータからボックステスト用パラメータ取得用

	obj_box_trans = *trans_p;
	
	model_info = NNS_G3dGetMdlInfo( model_p );			// モデルリソースインフォデータ取得

	SetBoxSize( 
			model_info->boxX,
			model_info->boxY,
			model_info->boxZ,
			model_info->boxW,	// 幅
			model_info->boxH,	// 高さ
			model_info->boxD,	// 奥行き
			&bounding_box);

	//
	// 座標をセット
	//
	// 位置設定
	NNS_G3dGlbSetBaseTrans(&obj_box_trans);
	// 角度設定
	NNS_G3dGlbSetBaseRot(rot_p);
	// スケール設定
	NNS_G3dGlbSetBaseScale(scale_p);

	NNS_G3dGlbFlush();		//　ジオメトリコマンドを転送

	
	// 上のボックステストの箱の値をposScaleでかけることにより本当の値になる
	NNS_G3dGePushMtx();
	NNS_G3dGeScale( model_info->boxPosScale,
					model_info->boxPosScale,
					model_info->boxPosScale );
	
	//
	// チェック
	//
	check_ret = CheckBoundingBox(&bounding_box);	// チェック

#ifdef DRAW_BOUNDING_BOX
	// ボックステストの箱を描画　これでチェック用のボックスがどこに描画されているかがわかります
	DrawBox(&bounding_box);
#endif //DRAW_BOUNDING_BOX
	
	NNS_G3dGePopMtx(1);

	return check_ret;

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	カリングチェック(リソースを使用しない)
 *
 *@param	trans_p			平行移動値
 *@param	rot_p			回転行列
 *@param	scale_p			拡縮値
 *
 *@return	u32			0以外の値であれば、ボックスの一部または全部が視体積内
 *						0であれば、ボックスの全てが視体積外
 *
 */
//-----------------------------------------------------------------------------
u32	BB_CullingCheck3DModelNonResource(	const VecFx32* trans_p,
									const fx32 inBoxW,
									const fx32 inBoxH,
									const fx32 inBoxD
									/*const MtxFx33* rot_p*/
									/*const VecFx32* scale_p*/ )
{
	u32 check_ret;		// チェックの戻り値用
	GXBoxTestParam bounding_box;

	BOUNDING_BOX	box;

	BB_MakeBoundingBox(inBoxW, inBoxH, inBoxD, &box);

	SetBoxSize( 
			0,
			0,
			0,
			box.w,	// 幅
			box.h,	// 高さ
			box.d,	// 奥行き
			&bounding_box);

	//
	// 座標をセット
	//
	// 位置設定
	NNS_G3dGlbSetBaseTrans(trans_p);
	// 角度設定
	///NNS_G3dGlbSetBaseRot(rot_p);
	// スケール設定
	///NNS_G3dGlbSetBaseScale(scale_p);
	
	NNS_G3dGlbFlush();		//　ジオメトリコマンドを転送

	// 上のボックステストの箱の値をposScaleでかけることにより本当の値になる
	NNS_G3dGePushMtx();
	NNS_G3dGeScale( box.ScaleW*FX32_ONE,
					box.ScaleH*FX32_ONE,
					box.ScaleD*FX32_ONE );

	check_ret = CheckBoundingBox(&bounding_box);	// チェック

#ifdef DRAW_BOUNDING_BOX
	// ボックステストの箱を描画　これでチェック用のボックスがどこに描画されているかがわかります
	DrawBox(&bounding_box);
#endif //DRAW_BOUNDING_BOX

	NNS_G3dGePopMtx(1);
	
	return check_ret;

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	カリングチェック(リソースを使用しない)
 *
 *@param	trans_p			平行移動値
 *@param	rot_p			回転行列
 *@param	scale_p			拡縮値
 *
 *@return	u32			0以外の値であれば、ボックスの一部または全部が視体積内
 *						0であれば、ボックスの全てが視体積外
 *
 */
//-----------------------------------------------------------------------------
u32	BB_CullingCheck3DModelNonResQuick(	const VecFx32* trans_p,
									const BOUNDING_BOX *inBox
									/*const MtxFx33* rot_p*/
									/*const VecFx32* scale_p*/ )
{
	u32 check_ret;		// チェックの戻り値用
	GXBoxTestParam bounding_box;

	SetBoxSize( 
			0,
			0,
			0,
			inBox->w,	// 幅
			inBox->h,	// 高さ
			inBox->d,	// 奥行き
			&bounding_box);

	//
	// 座標をセット
	//
	// 位置設定
	NNS_G3dGlbSetBaseTrans(trans_p);
	// 角度設定
	///NNS_G3dGlbSetBaseRot(rot_p);
	// スケール設定
	///NNS_G3dGlbSetBaseScale(scale_p);
	
	NNS_G3dGlbFlush();		//　ジオメトリコマンドを転送

	// 上のボックステストの箱の値をposScaleでかけることにより本当の値になる
	NNS_G3dGePushMtx();
	NNS_G3dGeScale( inBox->ScaleW*FX32_ONE,
					inBox->ScaleH*FX32_ONE,
					inBox->ScaleD*FX32_ONE );

	check_ret = CheckBoundingBox(&bounding_box);	// チェック

#ifdef DRAW_BOUNDING_BOX
	// ボックステストの箱を描画　これでチェック用のボックスがどこに描画されているかがわかります
	DrawBox(&bounding_box);
#endif //DRAW_BOUNDING_BOX

	NNS_G3dGePopMtx(1);
	
	return check_ret;

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	バウンディングボックスの作成
 *
 *@param	inBoxW			幅
 *@param	inBoxH			高さ
 *@param	inBoxD			奥行き
 *@param	outBox			作成するバウンディングボックスのバッファ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void BB_MakeBoundingBox(const fx32 inBoxW, const fx32 inBoxH, const fx32 inBoxD, BOUNDING_BOX *outBox)
{
	CulcFx32toFx16(inBoxW, &outBox->w, &outBox->ScaleW);
	CulcFx32toFx16(inBoxH, &outBox->h, &outBox->ScaleH);
	CulcFx32toFx16(inBoxD, &outBox->d, &outBox->ScaleD);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	バウンディングボックスセット
 *
 *@param	x		基準X座標
 *@param	y		基準Y座標
 *@param	z		基準Z座標
 *@param	width	幅
 *@param	height	高さ
 *@param	depth	奥行き
 *@param	outBox	ボックステスト用パラメータ格納アドレス
 *
 *@return	なし 
 *
 */
//-----------------------------------------------------------------------------
static void SetBoxSize( const fx16 x,
						const fx16 y,
						const fx16 z,
						const fx16 width,
						const fx16 height,
						const fx16 depth,
						GXBoxTestParam *outBox)
{
	//
	// パラメータをセット
	//
	outBox->x		= x;				// 左上のｘ座標	
	outBox->y		= y;				// 左上のｙ座標
	outBox->z		= z;				// 左上のｚ座標
	outBox->width	= width;			// 四角の幅
	outBox->height	= height;			// 四角の高さ
	outBox->depth	= depth;			// 立方体の奥行き
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ボックスチェック
 *
 *@param	inBox	ボックステスト用パラメータへのポインタ
 *
 *@return	u32		0以外の値であれば、ボックスの一部または全部が視体積内
 *					0であれば、ボックスの全てが視体積外 
 *
 */
//-----------------------------------------------------------------------------
static u32 CheckBoundingBox( const GXBoxTestParam	*inBox )
{
	s32 result = 1;			// 結果

	// ポリゴン設定を行う
	NNS_G3dGePolygonAttr(
			GX_LIGHTMASK_0,         
			GX_POLYGONMODE_MODULATE,
			GX_CULL_NONE,           
			0,                      
			0,                      
			GX_POLYGON_ATTR_MISC_FAR_CLIPPING
			| GX_POLYGON_ATTR_MISC_DISP_1DOT
			);

	//ポリゴンアトリビュート反映 
	NNS_G3dGeBegin( GX_BEGIN_TRIANGLES );							
	NNS_G3dGeEnd();	

	//
	// ボックステスト
	//
	NNS_G3dGeBoxTest( inBox );

	//
	// 同期を取る
	//
	NNS_G3dGeFlushBuffer();

	//
	// 今設定されているボックスが視体積内かチェック
	//
	while ( G3X_GetBoxTestResult(&result) != 0 ) ;

	return result;
}

#ifdef DRAW_BOUNDING_BOX
//----------------------------------------------------------------------------
/**
 *
 *@brief	バウンディングボックスを描画
 *
 *@param	inBox	ボックステスト用パラメータへのポインタ
 *
 *@return	なし
 *
 */
//-----------------------------------------------------------------------------
static void DrawBox( const GXBoxTestParam *inBox )
{
	//
	// 箱を描画
	//
	NNS_G3dGePolygonAttr(
			GX_LIGHTMASK_0,				// ライトを反映しない
			GX_POLYGONMODE_MODULATE,	// モジュレーションモード
			GX_CULL_BACK,				// カルバックを行う
			1,							// ポリゴンＩＤ
			31,							// アルファ値
			GX_POLYGON_ATTR_MISC_NONE
			);
	
	// 描画開始
	NNS_G3dGeBegin(GX_BEGIN_QUADS);           // 頂点リストの開始
                                        // (四角形ポリゴンでの描画宣言)
	{
		NNS_G3dGeNormal(0, 1 << 9, 0);
		NNS_G3dGeColor(GX_RGB(16,16,16));
		NNS_G3dGeVtx(	inBox->x + inBox->width,
						inBox->y + inBox->height,
						inBox->z + inBox->depth);
		NNS_G3dGeVtx(	inBox->x + inBox->width,
						inBox->y + inBox->height,
					    inBox->z );
		NNS_G3dGeVtx(   inBox->x,
						inBox->y + inBox->height,
					    inBox->z );
		NNS_G3dGeVtx(   inBox->x,
						inBox->y + inBox->height,
					    inBox->z + inBox->depth);
		
		NNS_G3dGeNormal(0, -1 << 9, 0);
		NNS_G3dGeVtx(	inBox->x + inBox->width,
						inBox->y,
						inBox->z + inBox->depth);
		NNS_G3dGeVtx(	inBox->x + inBox->width,
						inBox->y,
						inBox->z );
		NNS_G3dGeVtx(	inBox->x,
						inBox->y,
						inBox->z );
		NNS_G3dGeVtx(	inBox->x,
						inBox->y,
						inBox->z + inBox->depth);
		
		NNS_G3dGeNormal(1 << 9, 0, 0);
		NNS_G3dGeVtx(   inBox->x + inBox->width,
						inBox->y,
					    inBox->z);
		NNS_G3dGeVtx(	inBox->x + inBox->width,
						inBox->y,
						inBox->z + inBox->depth);
		NNS_G3dGeVtx(	inBox->x + inBox->width,
						inBox->y + inBox->height,
						inBox->z + inBox->depth);
		NNS_G3dGeVtx(	inBox->x + inBox->width,
						inBox->y + inBox->height,
						inBox->z);
		
		NNS_G3dGeNormal(-1 << 9, 0, 0);
		NNS_G3dGeVtx(	inBox->x,
						inBox->y,
					    inBox->z + inBox->depth);
		NNS_G3dGeVtx(	inBox->x,
						inBox->y,
						inBox->z );
		NNS_G3dGeVtx(   inBox->x,
						inBox->y + inBox->height,
					    inBox->z );
		NNS_G3dGeVtx(   inBox->x,
						inBox->y + inBox->height,
					    inBox->z + inBox->depth);
						
	}
	NNS_G3dGeEnd();                            // 頂点リストの終了
}
#endif //DRAW_BOUNDING_BOX

//----------------------------------------------------------------------------
/**
 *
 *@brief	fx32をfx16に落とし込む処理
 *
 *@param	inFx32		fx32の値
 *@param	outFx16		落とし込んだfx16
 *@param	outMul		元の値に戻すための倍化数
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void CulcFx32toFx16(const fx32 inFx32, fx16 *outFx16, int *outMul)
{
	int i;
	u8 shift_count;
	u32 val32;
	u16 val16;
	shift_count = 0;
	val32 = (u32)inFx32;
	while(0x00007fff<=val32){
		val32 = (val32>>1);
		shift_count++;
	}
	val16 = val32;
	*outFx16 = (fx16)val16;
	(*outMul) = 1;
	for (i=0;i<shift_count;i++){
		(*outMul) *= 2;
	}
}
