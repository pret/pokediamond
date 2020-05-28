//=============================================================================================
/**
 * @file	calc3D.h
 * @brief	ＢＧ描画計算プログラム
 */
//=============================================================================================
#undef GLOBAL
#ifdef __CALC3D_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif

/*---------------------------------------------------------------------
 *
 *
 *
 *			当たり判定
 *
 *
 *
 *--------------------------------------------------------------------*/
////////////////////////////
GLOBAL fx32 Min(fx32 n1,fx32 n2);
GLOBAL fx32 Max(fx32 n1,fx32 n2);
// 当たり判定用構造体：円柱
typedef struct {
	VecFx32	global;	//グローバル座標ベクトル

	fx32	vUp;		//中心点からの＋Ｙ方向オフセット
	fx32	vDown;		//中心点からの－Ｙ方向オフセット

	fx32	radius;		//半径
}HIT_CHECK_ENTYUU;

GLOBAL int  BG3D_CalcHitCheck_CylinderCylinder(HIT_CHECK_ENTYUU* object1,HIT_CHECK_ENTYUU* object2);

GLOBAL int BG3D_CalcHitCheck_SegmentSphere(const VecFx32 *inCoreVec, const fx32 inRadius, const VecFx32 *inStartVec, const VecFx32 *inEndVec);

GLOBAL BOOL BG3D_CheckTriangleIO(const VecFx32 *inTargetVtx,VecFx32 inVtx1,VecFx32 inVtx2,VecFx32 inVtx3);
GLOBAL BOOL BG3D_CheckTriangleIObyZX(const VecFx32 inT_Vtx,const VecFx32 inVtx1,const VecFx32 inVtx2,const VecFx32 inVtx3);

GLOBAL fx32 BG3D_GetPointSegmentDistance(const VecFx32 *inPoint, const VecFx32 *inStartVec, const VecFx32 *inEndVec);

GLOBAL fx32 BG3D_GetPointSegmentDistance2(const VecFx32 *inPoint, const VecFx32 *inStartVec, const VecFx32 *inEndVec);

GLOBAL fx32 BG3D_GetPointPlaneDistance(const VecFx32 *inPoint, const VecFx32 *inNrm,const fx32 inD );

GLOBAL BOOL GetCrossPointPlaneToSegment(const VecFx32 *inNrmVec, const fx32 inD, 
								const VecFx32 *inStartVec, const VecFx32 *inEndVec,
								VecFx32 *outVec);

GLOBAL BOOL HitCheckPlaneToBox2(const VecFx32 *inBoxCore, 
						const VecFx32 *inVecR,
						const VecFx32 *inVecS,
						const VecFx32 *inVecT,
						const VecFx32 *inNrm,
						const fx32 inD );

GLOBAL int GetHitPointPlaneToBox2(const VecFx32 *inBoxCore, 
						const VecFx32 *inVecR,
						const VecFx32 *inVecS,
						const VecFx32 *inVecT,
						const VecFx32 *inNrm,
						VecFx32 *outPointList);

#define	HITCHECK_TYPE_ENTYU		(1)

#define NO_HIT				(0)		//ヒットしていない
#define SEG_SPH_HIT_SEG		(1)		//線分と球がヒット
#define SEG_SPH_HIT_START	(2)		//線分の始点と球がヒット
#define SEG_SPH_HIT_END		(3)		//線分の終点と球がヒット

typedef enum {
	XY_PLANE,
	YZ_PLANE,
	ZX_PLANE
}PLANE_TYPE;

////////////////////////////
// 当たり判定構造体
typedef struct {
	int			type;
	const fx32*	data;

}HITCHECK_HEADER;
GLOBAL const  fx32	dummy_hitcheck_data[];
GLOBAL const  fx32	entyu1_hitcheck_data[];
GLOBAL const  fx32	entyu2_hitcheck_data[];


//---------------------------------------------------------------------------------------------------------
/**
 *	進行方向ベクトル修正(壁ずり移動)
 *	@param	*inMoveVec		移動量（移動方向）
 *	@param	*ioDirVec		修正後移動方向
 *
 *	@retval	VecFx32			修正後移動量（移動方向）
*/
//---------------------------------------------------------------------------------------------------------
GLOBAL	VecFx32 ChangeDirForWall(const VecFx32* inMoveVec, const VecFx32 *inDirVec);
//---------------------------------------------------------------------------------------------------------
/**
 *	方向ベクトルから回転角を計算（ＺＸ平面対応）
 *	@param	*inVec1		基準方向ベクトル
 *	@param	*inVec2		指定方向ベクトル
 *
 *	@retval	rad			回転角
*/
//---------------------------------------------------------------------------------------------------------
GLOBAL	fx32 GetRad(const VecFx32 *inVec1, const VecFx32 *inVec2 );


//平面とボックスの衝突判定
//平面とボックスの実効半径の距離を元に、衝突を検出する
//必要データ：	ボックスの中心座標
//				ボックスの幅、高さ、奥行き
//				ボックスの回転行列
//				平面の法線ベクトル
//				平面の方程式に必要なＤ置
GLOBAL BOOL HitCheckPlaneToBox(const VecFx32 *inBoxCore, 
						const VecFx32 *inBoxSize, 
						const VecFx32 *inBoxRot, 
						const VecFx32 *inNrm,
						const fx32 inD );

GLOBAL int GetHitPointPlaneToBox(const VecFx32 *inBoxCore, 
						const VecFx32 *inBoxSize, 
						const VecFx32 *inBoxRot, 
						const VecFx32 *inNrm,
						VecFx32 *outPointList);

GLOBAL BOOL HitCheckBoxToBox(const VecFx32 *inBoxCore1, 
						const VecFx32 *inBoxSize1, 
						const VecFx32 *inBoxRot1,
						const VecFx32 *inDirVec1,
						const VecFx32 *inBoxCore2, 
						const VecFx32 *inBoxSize2, 
						const VecFx32 *inBoxRot2,
						const VecFx32 *inDirVec2);

//////////////////////////////////////////////////
//2D
//////////////////////////////////////////////////

GLOBAL int BG2D_VectorSide( const VecFx32 *inS_Vec, const VecFx32 *inE_Vec, const VecFx32 *inT_Vec );
GLOBAL BOOL BG2D_CheckSegmentToSegment( const VecFx32 *inS_Vec1, const VecFx32 *inE_Vec1, const VecFx32 *inS_Vec2, const VecFx32 *inE_Vec2 );
GLOBAL BOOL GetPointLineToLine(	const VecFx32 *inS_Vec1,
									const VecFx32 *inE_Vec1,
									const VecFx32 *inS_Vec2,
									const VecFx32 *inE_Vec2,
									VecFx32 *outVec );
GLOBAL BOOL GetPointSegmentToSegment(	const VecFx32 *inS_Vec1,
									const VecFx32 *inE_Vec1,
									const VecFx32 *inS_Vec2,
									const VecFx32 *inE_Vec2,
									VecFx32 *outVec );
GLOBAL BOOL CheckHitPlaneToSegment2D(	const VecFx32 *inVtx1,
								const VecFx32 *inVtx2,
								const VecFx32 *inVtx3,
								const VecFx32 *inVtx4,
								const VecFx32 *inS_Vec,
								const VecFx32 *inE_Vec );

/*---------------------------------------------------------------------
 *
 *
 *
 *			演算
 *
 *
 *
 *--------------------------------------------------------------------*/
/*---------------------------------------------------------------------
  Name       :ベクトル→３Ｘ３行列への変換 
  In	: dst = 行列ポインタ,dst = ベクトルポインタ 
  Out	: なし
 *--------------------------------------------------------------------*/
GLOBAL void  VecFx32_to_MtxFx33( MtxFx33* dst, VecFx32* src );
/*---------------------------------------------------------------------
  Name       :ベクトル→４Ｘ３行列への変換 
  In	: dst = 行列ポインタ,dst = ベクトルポインタ 
  Out	: なし
 *--------------------------------------------------------------------*/
GLOBAL void  VecFx32_to_MtxFx43( MtxFx43* dst, VecFx32* src );

/*---------------------------------------------------------------------
  @brief	360度XYZの回転角→３Ｘ３行列への変換 

  @param	dst MtxFx33:演算結果を格納するMtxFx33型のポインタ
  @param	x	回転角X(360度単位,0-359を超えない事)
  @param	y	回転角Y(360度単位)
  @param	z	回転角Z(360度単位)

  @return none
 *--------------------------------------------------------------------*/
GLOBAL void  Rot360_to_MtxFx33( MtxFx33* dst,u16 x,u16 y,u16 z);

/*---------------------------------------------------------------------
  @brief	360度XYZの回転角→4x3行列への変換 

  @param	dst MtxFx43:演算結果を格納するMtxFx43型のポインタ
  @param	x	回転角X(360度単位,0-359を超えない事)
  @param	y	回転角Y(360度単位,0-359)
  @param	z	回転角Z(360度単位,0-359)

  @return none
 *--------------------------------------------------------------------*/
GLOBAL void  Rot360_to_MtxFx43( MtxFx43* dst,u16 x,u16 y,u16 z);

//----------------------------------------------------------------------------
/**
 *
 *@brief	射影行列のデータから今の高さと幅を返す
 *
 *@param	PerspWay	視野角
 *@param	Dist		ターゲットまでの距離
 *@param	Aspect		アスペクト比	(幅/高さ)
 *@param	pWidth		幅格納用
 *@param	pHeight		高さ格納用
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void GetPerspectiveScreenSize( u16 PerspWay, fx32 Dist, fx32 Aspect, fx32* pWidth, fx32* pHeight );
#undef GLOBAL

