/*---------------------------------------------------------------------------*
  Project:  
  File:     calc3d.c
 *---------------------------------------------------------------------------*/
#include <nnsys.h>

#define	__CALC3D_H_GLOBAL
#include "calctool.h"
#include "calc3D.h"

//ボックスとボックスの衝突検出(ねじれの位置にある辺同士の衝突)に使う構造体
//面衝突判定において、1頂点衝突したときの点を記憶しておく
typedef struct VTX_DATA_tag{
	u8 Idx;			//ボックスの衝突面
	VecFx32 Vtx;	//衝突した頂点
}VTX_DATA;

typedef struct VTX_DATA_FOR_BOXHIT_tag
{
	VTX_DATA VtxData[2];	//ねじれの位置にある辺同士の衝突では、3頂点以上の面衝突は起こらないので、配列は2つまで用意
	u8 Count;	//1頂点衝突した回数
	
}VTX_DATA_FOR_BOXHIT;


//片方のボックスを軸平行ならびに、1頂点が原点を通るように回転、移動した際の
//ボックスの法線ベクトル
static VecFx32 BoxNrm[6] = {
	{FX32_ONE ,0		,0			},
	{0		  ,FX32_ONE	,0			},
	{0		  ,0		,FX32_ONE	},
	{-FX32_ONE,0		,0			},
	{0		  ,-FX32_ONE,0			},
	{0		  ,0		,-FX32_ONE	}
};

//片方のボックスを軸平行ならびに、1頂点が原点を通るように回転、移動した際の
//ボックス平面のD値（スケール倍する必要あり）
static fx32 BoxDBase[6] = {
	-FX32_ONE,
	-FX32_ONE,
	-FX32_ONE,
	0,
	0,
	0
};

/*---------------------------------------------------------------------
 *
 *
 *
 *			当たり判定計算
 *
 *
 *
 *--------------------------------------------------------------------*/
// グローバル定数 ----------------------------------------------------
#if 0
const fx32	dummy_hitcheck_data[] = {
	0x0000,0x0000,0x0000,		//r,vup,vdown
};

const fx32	entyu1_hitcheck_data[] = {
	FX32_ONE*1,0x0000,0x0000,		//r,vup,vdown
};

const fx32	entyu2_hitcheck_data[] = {
	FX32_ONE*2,0x0000,0x0000,		//r,vup,vdown
};
#endif
fx32 temp1,temp2;
// ローカル変数 ----------------------------------------------------

fx32 Min(fx32 n1,fx32 n2)
{
	if(n1 < n2){
		return n1;
	}else{
		return n2;
	}
}

fx32 Max(fx32 n1,fx32 n2)
{
	if(n1 > n2){
		return n1;
	}else{
		return n2;
	}

}

/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : なし
 *--------------------------------------------------------------------*/
int  BG3D_CalcHitCheck_CylinderCylinder(HIT_CHECK_ENTYUU* object1,HIT_CHECK_ENTYUU* object2)
{
	fx64 r;
	fx64 x,z;

	r = (object1->radius + object2->radius);
	x = (object2->global.x - object1->global.x);
	z = (object2->global.z - object1->global.z);

	if( (r*r) < (x*x) + (z*z) ){
		return 0;
	}
	return 1;
}

//線分と球の交差判定
/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : なし
 *--------------------------------------------------------------------*/
int BG3D_CalcHitCheck_SegmentSphere(const VecFx32 *inCoreVec, const fx32 inRadius, const VecFx32 *inStartVec, const VecFx32 *inEndVec)
{
	fx32 distance;
	//球と線分が2つの交点を持つ場合もしくは、線分と球が接している場合、球の中心点と線分の距離が半径以下になる
	distance = BG3D_GetPointSegmentDistance(inCoreVec, inStartVec, inEndVec);
	if (  (distance < 0) || (distance > inRadius) ){
		//球と線分が1つの交点を持つ場合、線分の1つの端点と球の中心点の距離が半径以下になる
		if ( (VEC_Distance(inStartVec, inCoreVec) < inRadius) ){
			return SEG_SPH_HIT_START;	//始点ヒット
		}
		else if ( (VEC_Distance(inEndVec, inCoreVec) < inRadius) ){
			return SEG_SPH_HIT_END;	//終点ヒット
		}
		else{
			return NO_HIT;//ヒットしてない
		}
	}
	return SEG_SPH_HIT_SEG;//線分ヒット
}

//三角形の内外判定
/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : なし
 *--------------------------------------------------------------------*/
BOOL BG3D_CheckTriangleIO(const VecFx32 *inTargetVtx,VecFx32 inVtx1,VecFx32 inVtx2,VecFx32 inVtx3)
{
	VecFx32	vec1,vec2,vec3,vecCross1,vecCross2;
	fx32	dot;
#if 1	
	//vector:1→2
	VEC_Subtract(&inVtx2,&inVtx1,&vec1);
	//vector:1→3
	VEC_Subtract(&inVtx3,&inVtx1,&vec2);
	//Cross
	VEC_CrossProduct(&vec1,&vec2,&vecCross1);

	//外積が0ベクトルのものは、ヒットしなかったとみなす
	if ( VEC_Mag(&vecCross1)==0 ){
		return FALSE;
	}

	///VEC_Normalize(&vecCross1, &vecCross1);//外積計算で桁あふれしないように正規化しておく
#endif
	//vector:Target→1
	VEC_Subtract(&inVtx1,inTargetVtx,&vec1);
	//vector:Target→2
	VEC_Subtract(&inVtx2,inTargetVtx,&vec2);
	//vector:Target→3
	VEC_Subtract(&inVtx3,inTargetVtx,&vec3);
	
	//Cross
	VEC_CrossProduct(&vec1,&vec2,&vecCross2);
	if (VEC_Mag(&vecCross2)!=0/*vecCross2.y!=0*/){			//外積が０ベクトルのときは、返上にあるので、ヒットしたとみなす
		///VEC_Normalize(&vecCross2, &vecCross2);
		//Dot
		dot = VEC_DotProduct(&vecCross1,&vecCross2);
		if ( (dot) <= 0.0 ){
			return FALSE;
		}
	}

	//Cross
	VEC_CrossProduct(&vec2,&vec3,&vecCross2);
	if (VEC_Mag(&vecCross2)!=0/*vecCross2.y!=0*/){			//外積が０ベクトルのときは、返上にあるので、ヒットしたとみなす
		///VEC_Normalize(&vecCross2, &vecCross2);
		//Dot
		dot = VEC_DotProduct(&vecCross1,&vecCross2);
		if ( (dot) <= 0.0 ){
			return FALSE;
		}
	}

	//Cross
	VEC_CrossProduct(&vec3,&vec1,&vecCross2);
	if (VEC_Mag(&vecCross2)!=0/*vecCross2.y!=0*/){			//外積が０ベクトルのときは、返上にあるので、ヒットしたとみなす
		///VEC_Normalize(&vecCross2, &vecCross2);
		//Dot
		dot = VEC_DotProduct(&vecCross1,&vecCross2);
		if ( (dot) <= 0.0 ){
			return FALSE;
		}
	}
	return TRUE;
}

//線分と点の距離(線分の開始点をＡ、終点をＢ、任意の点をＰ、ＰからＡＢに垂直に伸ばした直線とＡＢの交点をＱとする)
/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : なし
 *--------------------------------------------------------------------*/
fx32 BG3D_GetPointSegmentDistance(const VecFx32 *inPoint, const VecFx32 *inStartVec, const VecFx32 *inEndVec)
{
	fx32 distance;
	fx32 t;
	VecFx32 ab_Vec,ap_Vec,pq_Vec,aq_Vec;
	VecFx32 dummy = {0,0,0};
	
	
	//線分のＡＢベクトルを作成（ベクトルの減法）
	VEC_Subtract(inEndVec, inStartVec, &ab_Vec);
	//ＡＰベクトル作成（ベクトルの減法）
	VEC_Subtract(inPoint, inStartVec, &ap_Vec);
	//ベクトルＡＢ、ＡＰの内積より媒介変数ｔを求め、線分内にあるか調べる
	temp1 = VEC_DotProduct( &ab_Vec, &ap_Vec );
	temp2 = FX_Mul(ab_Vec.z, ab_Vec.z);
	
	t = FX_Div( VEC_DotProduct( &ab_Vec, &ap_Vec ), ( FX_Mul(ab_Vec.x, ab_Vec.x) + FX_Mul(ab_Vec.z, ab_Vec.z) ) );

	//Ｐから下ろした垂線が線分上にないならヒットしなかったとみなす
    if( t < 0 || t > FX32_ONE )
        return -FX32_ONE;

    //線分ＡＢと交点ＱのベクトルＡＱを作成（ベクトル方程式）
	VEC_MultAdd(t , &ab_Vec, &dummy, &aq_Vec);

    //Ｐと交点ＱのベクトルＰＱを作成（ベクトルの減法）
	VEC_Subtract(&aq_Vec, &ap_Vec, &pq_Vec);

    //ベクトルＰＱのスカラーが距離
	distance = VEC_Mag(&pq_Vec);
	return distance;
}

//直線と点の距離(線分の開始点をＡ、終点をＢ、任意の点をＰ、ＰからＡＢに垂直に伸ばした直線とＡＢの交点をＱとする)
/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : なし
 *--------------------------------------------------------------------*/
fx32 BG3D_GetPointSegmentDistance2(const VecFx32 *inPoint, const VecFx32 *inStartVec, const VecFx32 *inEndVec)
{
	fx32 distance;
	fx32 t;
	VecFx32 ab_Vec,ap_Vec,pq_Vec,aq_Vec;
	VecFx32 dummy = {0,0,0};
	
	
	//線分のＡＢベクトルを作成（ベクトルの減法）
	VEC_Subtract(inEndVec, inStartVec, &ab_Vec);
	//ＡＰベクトル作成（ベクトルの減法）
	VEC_Subtract(inPoint, inStartVec, &ap_Vec);
	//ベクトルＡＢ、ＡＰの内積より媒介変数ｔを求め、線分内にあるか調べる
	temp1 = VEC_DotProduct( &ab_Vec, &ap_Vec );
	temp2 = FX_Mul(ab_Vec.z, ab_Vec.z);
	
	t = FX_Div( VEC_DotProduct( &ab_Vec, &ap_Vec ), ( FX_Mul(ab_Vec.x, ab_Vec.x) + FX_Mul(ab_Vec.z, ab_Vec.z) ) );
/**
	//Ｐから下ろした垂線が線分上にないならヒットしなかったとみなす
    if( t < 0 || t > FX32_ONE )
        return -FX32_ONE;
*/
    //線分ＡＢと交点ＱのベクトルＡＱを作成（ベクトル方程式）
	VEC_MultAdd(t , &ab_Vec, &dummy, &aq_Vec);

    //Ｐと交点ＱのベクトルＰＱを作成（ベクトルの減法）
	VEC_Subtract(&aq_Vec, &ap_Vec, &pq_Vec);

    //ベクトルＰＱのスカラーが距離
	distance = VEC_Mag(&pq_Vec);
	return distance;
}

//点と平面の距離 法線ベクトルＮ、平面の方程式のＤ値、対象になる点Ｐ
/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : なし
 *--------------------------------------------------------------------*/
fx32 BG3D_GetPointPlaneDistance(const VecFx32 *inPoint, const VecFx32 *inNrm,const fx32 inD )
{
	fx32 dist;
	dist = FX_Mul(inNrm->x,inPoint->x)+FX_Mul(inNrm->y,inPoint->y)+FX_Mul(inNrm->z,inPoint->z)+inD;
	if (dist<0){
		dist *= (-1);
	}
	return dist;
}

#if 0
//平面へのベクトル貫通判定
/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : なし
 *--------------------------------------------------------------------*/
//void CheckVectorHitToPlane(VecFx32 inNrmVec, inFx32 inD, inTeget)
#endif
#if 0
//平面と直線の交差座標取得
/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : なし
 *--------------------------------------------------------------------*/
VecFx32	GetCrossPointPlaneToLine(VecFx32 inNrmVec, inFx32 inD, VecFx32 inDirVec, VecFx32 inStartVec)
{
	fx32 t;
	fx32	nrm_start;
	fx32 nrm_dir;
	VecFx32	dst_vec;

	nrm_start = VEC_DotProduct(&inNrmVec, &inStartVec);
	nrm_dir = VEC_DotProduct(&inNrmVec, &inDirVec);

	t = FX_Div( inD + nrm_start, nrm_dir);

	VEC_MultAdd(t, inDirVec, inStartVec, &des_vec);
	return dst_vec;
}
#endif

//平面と線分の交差座標取得
/*---------------------------------------------------------------------
  Name       : 
  Description: 
  Returns    : なし
 *--------------------------------------------------------------------*/
BOOL GetCrossPointPlaneToSegment(const VecFx32 *inNrmVec, const fx32 inD, 
								const VecFx32 *inStartVec, const VecFx32 *inEndVec,
								VecFx32 *outVec)
{
	fx32 t;
	fx32 nrm_start;
	fx32 nrm_dir;
	VecFx32 dirVec;

	//方向ベクトル作成(正規化しない)
	VEC_Subtract(inEndVec,inStartVec,&dirVec);

	//線分開始地点と平面の法線ベクトルの内積を計算
	nrm_start = VEC_DotProduct(inNrmVec, inStartVec);
	//線分の方向ベクトルと平面の法線ベクトルの内積を計算
	nrm_dir = VEC_DotProduct(inNrmVec, &dirVec);

	//線分の方向ベクトルと平面の法線ベクトルの内積が0の場合、線分は面に対して平行なので、交点は無しとする
	if (nrm_dir == 0){
		return FALSE;
	}

	//媒介変数を算出
	t = -( FX_Div( inD + nrm_start, nrm_dir) );

	//線分と平面が交差してるかを媒介変数の値から判断
	if (0<=t && t<=1*FX32_ONE){
		VEC_MultAdd(t, &dirVec, inStartVec, outVec);
		return TRUE;		//交点あり
	}else{
		return FALSE;		//交点なし
	}
}



//---------------------------------------------------------------------------------------------------------
/**
 *	進行方向ベクトル修正(壁ずり移動)
 *	@param	*inMoveVec		移動量（移動方向）
 *	@param	*ioDirVec		修正後移動方向
 *
 *	@retval	VecFx32			修正後移動量（移動方向）
*/
//---------------------------------------------------------------------------------------------------------
VecFx32 ChangeDirForWall(const VecFx32* inMoveVec, const VecFx32 *inDirVec)
{
	fx32 len;
	VecFx32 dir_vec,dir_vec1,dir_vec2;
	VecFx32 dumy_vec = {0,0,0};

	dir_vec1 = *inDirVec;
	dir_vec2 = *inDirVec;
	dir_vec2.x = dir_vec2.x*(-1);
	dir_vec2.z = dir_vec2.z*(-1);

	dir_vec1.y = 0x0000;
	dir_vec2.y = 0x0000;

	if ( VEC_DotProduct(&dir_vec1, inMoveVec)>0 ){
		dir_vec = dir_vec1;
	}else if( VEC_DotProduct(&dir_vec2, inMoveVec)>0 ){
		dir_vec = dir_vec2;
	}else{
		dir_vec = dumy_vec;
	}
	VEC_Normalize(&dir_vec, &dir_vec);
	len = VEC_Mag(inMoveVec);
	//斜めの衝突回避移動であっても、その移動量は通常の縦横移動距離と同じにしてある(本当はその方向ベクトルを射影した移動距離)
	VEC_MultAdd(len,&dir_vec,&dumy_vec,&dir_vec);

	return dir_vec;
}

//---------------------------------------------------------------------------------------------------------
/**
 *	方向ベクトルから回転角を計算（ＺＸ平面対応）
 *	@param	*inVec1		基準方向ベクトル
 *	@param	*inVec2		指定方向ベクトル
 *
 *	@retval	rad			回転角
*/
//---------------------------------------------------------------------------------------------------------
fx32 GetRad(const VecFx32 *inVec1, const VecFx32 *inVec2 )
{
	VecFx32 vec1,vec2;
	fx32 sin,cos;
	fx32 rad;
	VEC_Normalize(inVec1, &vec1);
	VEC_Normalize(inVec2, &vec2);
	//内積を使ってコサインを求める
	//cos = VEC_DotProduct(&vec1, &vec2);
	cos = FX_Mul(vec1.z, vec2.z) + FX_Mul(vec1.x, vec2.x); 
	//外積を使ってサインを求める
	sin = FX_Mul(vec1.z, vec2.x) - FX_Mul(vec1.x, vec2.z);
	//XZ平面上での計算なので時計回りが正方向となる（反時計回りにするため、サインの向きを逆にする）
	///sin = FX_Mul(sin, -FX32_ONE);
	if (cos == 0){//アークコサインが使えない場合
		if (sin > 0){
			rad = 0x4000;
		}else{
			rad = 0xc000;
		}
	}else{
		//アークタンジェントを使って角度を求める
		rad = FX_Atan2Idx(sin, cos);
	}
	return rad;
}

static void GetRST(const VecFx32 *inBoxSize, const VecFx32 *inBoxRot, VecFx32 *outR, VecFx32 *outS, VecFx32 *outT)
{
	MtxFx33 box_rot;

	VecFx32_to_MtxFx33(&box_rot,(VecFx32*)inBoxRot);
	//ｘ、ｙ、ｚの単位ベクトルそれぞれに、ボックスの回転行列をかけて、ＲＳＴを求める
	{
		VecFx32 x = {FX32_ONE, 0, 0};
		VecFx32 y = {0, FX32_ONE, 0};
		VecFx32 z = {0, 0, FX32_ONE};
		
		MTX_MultVec33(&x, &box_rot, outR);
		MTX_MultVec33(&y, &box_rot, outS);
		MTX_MultVec33(&z, &box_rot, outT);
	}
	{
		VecFx32 dummy = {0, 0, 0};
		VEC_MultAdd(inBoxSize->x,outR,&dummy,outR);
		VEC_MultAdd(inBoxSize->y,outS,&dummy,outS);
		VEC_MultAdd(inBoxSize->z,outT,&dummy,outT);
	}
}

//---------------------------------------------------------------------------------------------------------
/**
 *	平面とボックスの衝突判定
 *	平面とボックスの実効半径の距離を元に、衝突を検出する
 *	必要データ：ボックスの中心座標
 *				ボックスの幅、高さ、奥行き
 *				ボックスの回転行列
 *				平面の法線ベクトル
 *				平面の方程式に必要なＤ値
 *
 *	@param	*inBoxCore
 *	@param  *inBoxSize
 *	@param	*inBoxRot 
 *	@param	*inNrm
 *	@param	inD
 *
 *	@retval	BOOL
*/
//---------------------------------------------------------------------------------------------------------
BOOL HitCheckPlaneToBox(const VecFx32 *inBoxCore, 
						const VecFx32 *inBoxSize, 
						const VecFx32 *inBoxRot, 
						const VecFx32 *inNrm,
						const fx32 inD )
{
	VecFx32 vecR,vecS,vecT;
	fx32 n_s,n_r,n_t;
	fx32 radius,dist;
	
	GetRST(inBoxSize, inBoxRot, &vecR, &vecS, &vecT);
	
	//ＲＳＴ、平面の法線ベクトルを用いて、実効半径を求める
	n_r = VEC_DotProduct(inNrm,&vecR);
	n_s = VEC_DotProduct(inNrm,&vecS);
	n_t = VEC_DotProduct(inNrm,&vecT);
	if (n_r < 0){
		n_r *=(-1) ;
	}
	if (n_s < 0){
		n_s *=(-1) ;
	}
	if (n_t < 0){
		n_t *=(-1) ;
	}
	radius = (n_r + n_s + n_t) / 2;	//実効半径
	
	//平面と、ボックス中心との距離を求める
	dist = BG3D_GetPointPlaneDistance(inBoxCore, inNrm, inD );
	//求めた距離が実効半径未満なら、衝突している
	if (radius > dist){
		return TRUE;
	}
	
	return FALSE;
}

//
//
//
//---------------------------------------------------------------------------------------------------------
/**
 *	平面とボックスの衝突判定
 *	平面とボックスの実効半径の距離を元に、衝突を検出する
 *	必要データ：ボックスの中心座標
 *				ボックスの幅、高さ、奥行き(RST)
 *				平面の法線ベクトル
 *				平面の方程式に必要なＤ置
 *
 *	@param	*inBoxCore
 *	@param  *inBoxSize
 *	@param	*inBoxRot 
 *	@param	*inNrm
 *	@param	inD
 *
 *	@retval	BOOL
*/
//---------------------------------------------------------------------------------------------------------

BOOL HitCheckPlaneToBox2(const VecFx32 *inBoxCore, 
						const VecFx32 *inVecR,
						const VecFx32 *inVecS,
						const VecFx32 *inVecT,
						const VecFx32 *inNrm,
						const fx32 inD )
{
	fx32 n_s,n_r,n_t;
	fx32 radius,dist;

	//ＲＳＴ、平面の法線ベクトルを用いて、実効半径を求める
	n_r = VEC_DotProduct(inNrm,inVecR);
	n_s = VEC_DotProduct(inNrm,inVecS);
	n_t = VEC_DotProduct(inNrm,inVecT);

	if (n_r < 0){
		n_r *=(-1) ;
	}
	if (n_s < 0){
		n_s *=(-1) ;
	}
	if (n_t < 0){
		n_t *=(-1) ;
	}
	radius = (n_r + n_s + n_t) / 2;//実効半径
	
	//平面と、ボックス中心との距離を求める
	dist = BG3D_GetPointPlaneDistance(inBoxCore, inNrm, inD );
	//求めた距離が実効半径未満なら、衝突している
	if (radius > dist){
		return TRUE;
	}
	
	return FALSE;
}

//値の正負を判定する関数
static int sgn(const fx32 inVal)
{
	if (inVal>=0){
		return 1;
	}else{
		return -1;
	}
}

//---------------------------------------------------------------------------------------------------------
/**
 *	平面とボックスの交点
 *	平面とボックスが衝突した場合その交点を求める
 *	最大で、同時に4点で衝突するので、格納領域は、常に、4つ用意するようにする
 *	必要データ：ボックスの中心座標
 *				ボックスの幅、高さ、奥行き
 *				ボックスの回転行列
 *				平面の法線ベクトル
 *				平面の方程式に必要なＤ置
 *
 *	@param	*inBoxCore
 *	@param  *inBoxSize
 *	@param	*inBoxRot 
 *	@param	*inNrm
 *
 *	@retval	BOOL
*/
//---------------------------------------------------------------------------------------------------------
int GetHitPointPlaneToBox(const VecFx32 *inBoxCore, 
						const VecFx32 *inBoxSize, 
						const VecFx32 *inBoxRot, 
						const VecFx32 *inNrm,
						VecFx32 *outPointList)
{
	VecFx32 vecR,vecS,vecT;	//RST
	fx32 n_s,n_r,n_t;	//法線とＲＳＴそれぞれの内積
	VecFx32 *vec1[2];	//平面に対して、平行なRSTを格納する配列
	VecFx32 *vec2[2];	//平面に対して、非平行なRSTを格納する配列
	fx32 * dot_prod[2];	//平面に対して、非平行なRSTと法線ベクトルとの内積を格納する配列

	int hit_vtx_num = 0;	//衝突頂点の数
	
	int flat_num = 0;	//平面に対して、平行なRSTの数
	int non_flat_num = 0;	//平面に対して、非平行なRSTの数
	
	//ＲＳＴを求める
	GetRST(inBoxSize, inBoxRot, &vecR, &vecS, &vecT);
	//ＲＳＴ、法線ベクトルの内積を計算
	n_r = VEC_DotProduct(inNrm,&vecR);
	n_s = VEC_DotProduct(inNrm,&vecS);
	n_t = VEC_DotProduct(inNrm,&vecT);
	
	if (n_r == 0){
		vec1[flat_num++] = &vecR;
	}else{
		dot_prod[non_flat_num] = &n_r;
		vec2[non_flat_num++] = &vecR;
	}
	if (n_s == 0){
		vec1[flat_num++] = &vecS;
	}else{
		dot_prod[non_flat_num] = &n_s;
		vec2[non_flat_num++] = &vecS;
	}
	if (n_t == 0){
		vec1[flat_num++] = &vecT;
	}else{
		dot_prod[non_flat_num] = &n_t;
		vec2[non_flat_num++] = &vecT;
	}

	{
		VecFx32 dummy = {0,0,0};
		VecFx32 temp1,temp2,temp3;
		if (flat_num == 0 ){	//平面と1頂点で衝突する場合
			//平面と一番近い位置にある頂点を算出
			VEC_MultAdd((fx32)(sgn(n_r)*FX32_ONE),&vecR,&dummy,&temp1);
			VEC_MultAdd((fx32)(sgn(n_s)*FX32_ONE),&vecS,&dummy,&temp2);
			VEC_MultAdd((fx32)(sgn(n_t)*FX32_ONE),&vecT,&dummy,&temp3);
			VEC_Add( &temp1,&temp2,&temp1);
			VEC_Add( &temp1,&temp3,&temp1);
			VEC_MultAdd(FX32_ONE/2,&temp1,&dummy,&temp1);
			VEC_Subtract( inBoxCore,&temp1,&outPointList[0]);
			hit_vtx_num = 1;
		}else if (flat_num == 1){	//平面と2頂点で衝突する場合
			VEC_MultAdd(sgn(*dot_prod[0])*FX32_ONE,vec2[0],&dummy,&temp1);
			VEC_MultAdd(sgn(*dot_prod[1])*FX32_ONE,vec2[1],&dummy,&temp2);
			VEC_Add( &temp1,&temp2,&temp1);
			temp3 = *vec1[0];
			
			VEC_Add( &temp1,&temp3,&outPointList[0]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[0],&dummy,&outPointList[0]);
			VEC_Subtract( inBoxCore,&outPointList[0],&outPointList[0]);
			
			VEC_Subtract( &temp1,&temp3,&outPointList[1]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[1],&dummy,&outPointList[1]);
			VEC_Subtract( inBoxCore,&outPointList[1],&outPointList[1]);
			hit_vtx_num = 2;
		}else{	//平面と4頂点で衝突する場合
			VEC_MultAdd(sgn(*dot_prod[0])*FX32_ONE,vec2[0],&dummy,&temp1);
			temp2 = *vec1[0];
			temp3 = *vec1[1];
			
			//4頂点の算出
			//4頂点と面の衝突判定で、使用可能にするために、
			//格納リストの連続する2つの頂点が、隣り合うような順序で格納する
			//下記の順序に格納すれば、順序が保障される	
			VEC_Add( &temp1,&temp2,&outPointList[0]);
			VEC_Add( &outPointList[0],&temp3,&outPointList[0]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[0],&dummy,&outPointList[0]);
			VEC_Subtract( inBoxCore,&outPointList[0],&outPointList[0]);
			
			VEC_Subtract( &temp1,&temp2,&outPointList[1]);
			VEC_Add( &outPointList[1],&temp3,&outPointList[1]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[1],&dummy,&outPointList[1]);
			VEC_Subtract( inBoxCore,&outPointList[1],&outPointList[1]);

			VEC_Subtract( &temp1,&temp2,&outPointList[2]);
			VEC_Subtract( &outPointList[2],&temp3,&outPointList[2]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[2],&dummy,&outPointList[2]);
			VEC_Subtract( inBoxCore,&outPointList[2],&outPointList[2]);

			VEC_Add( &temp1,&temp2,&outPointList[3]);
			VEC_Subtract( &outPointList[3],&temp3,&outPointList[3]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[3],&dummy,&outPointList[3]);
			VEC_Subtract( inBoxCore,&outPointList[3],&outPointList[3]);
			hit_vtx_num = 4;
		}
	}
	return hit_vtx_num;
}

//---------------------------------------------------------------------------------------------------------
/**
 *	平面とボックスの交点
 *	平面とボックスが衝突した場合その交点を求める
 *	最大で、同時に4点で衝突するので、格納領域は、常に、4つ用意するようにする
 *	必要データ：ボックスの中心座標
 *				ボックスの幅、高さ、奥行き
 *				ボックスの回転行列
 *				平面の法線ベクトル
 *				平面の方程式に必要なＤ置
 *
 *	@param	*inBoxCore
 *	@param  *inBoxSize
 *	@param	*inBoxRot 
 *	@param	*inNrm
 *
 *	@retval	BOOL
*/
//---------------------------------------------------------------------------------------------------------
int GetHitPointPlaneToBox2(const VecFx32 *inBoxCore, 
						const VecFx32 *inVecR,
						const VecFx32 *inVecS,
						const VecFx32 *inVecT,
						const VecFx32 *inNrm,
						VecFx32 *outPointList)
{
	fx32 n_s,n_r,n_t;	//法線とＲＳＴそれぞれの内積
	const VecFx32 *vec1[2];	//平面に対して、平行なRSTを格納する配列
	const VecFx32 *vec2[2];	//平面に対して、非平行なRSTを格納する配列
	fx32 * dot_prod[2];	//平面に対して、非平行なRSTと法線ベクトルとの内積を格納する配列

	int hit_vtx_num = 0;	//衝突頂点の数
	
	int flat_num = 0;	//平面に対して、平行なRSTの数
	int non_flat_num = 0;	//平面に対して、非平行なRSTの数
	
	//ＲＳＴ、法線ベクトルの内積を計算
	n_r = VEC_DotProduct(inNrm,inVecR);
	n_s = VEC_DotProduct(inNrm,inVecS);
	n_t = VEC_DotProduct(inNrm,inVecT);
	if (n_r == 0){
		vec1[flat_num++] = inVecR;
	}else{
		dot_prod[non_flat_num] = &n_r;
		vec2[non_flat_num++] = inVecR;
	}
	if (n_s == 0){
		vec1[flat_num++] = inVecS;
	}else{
		dot_prod[non_flat_num] = &n_s;
		vec2[non_flat_num++] = inVecS;
	}
	if (n_t == 0){
		vec1[flat_num++] = inVecT;
	}else{
		dot_prod[non_flat_num] = &n_t;
		vec2[non_flat_num++] = inVecT;
	}

	{
		VecFx32 dummy = {0,0,0};
		VecFx32 temp1,temp2,temp3;
		if (flat_num == 0 ){	//平面と1頂点で衝突する場合
			//平面と一番近い位置にある頂点を算出
			VEC_MultAdd((fx32)(sgn(n_r)*FX32_ONE),inVecR,&dummy,&temp1);
			VEC_MultAdd((fx32)(sgn(n_s)*FX32_ONE),inVecS,&dummy,&temp2);
			VEC_MultAdd((fx32)(sgn(n_t)*FX32_ONE),inVecT,&dummy,&temp3);
			VEC_Add( &temp1,&temp2,&temp1);
			VEC_Add( &temp1,&temp3,&temp1);
			VEC_MultAdd(FX32_ONE/2,&temp1,&dummy,&temp1);
			VEC_Subtract( inBoxCore,&temp1,&outPointList[0]);
			hit_vtx_num = 1;
		}else if (flat_num == 1){	//平面と2頂点で衝突する場合
			VEC_MultAdd(sgn(*dot_prod[0])*FX32_ONE,vec2[0],&dummy,&temp1);
			VEC_MultAdd(sgn(*dot_prod[1])*FX32_ONE,vec2[1],&dummy,&temp2);
			VEC_Add( &temp1,&temp2,&temp1);
			temp3 = *vec1[0];
			
			VEC_Add( &temp1,&temp3,&outPointList[0]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[0],&dummy,&outPointList[0]);
			VEC_Subtract( inBoxCore,&outPointList[0],&outPointList[0]);
			
			VEC_Subtract( &temp1,&temp3,&outPointList[1]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[1],&dummy,&outPointList[1]);
			VEC_Subtract( inBoxCore,&outPointList[1],&outPointList[1]);
			hit_vtx_num = 2;
		}else{	//平面と4頂点で衝突する場合
			VEC_MultAdd(sgn(*dot_prod[0])*FX32_ONE,vec2[0],&dummy,&temp1);
			temp2 = *vec1[0];
			temp3 = *vec1[1];
			
			//4頂点の算出
			//4頂点と面の衝突判定で、使用可能にするために、
			//格納リストの連続する2つの頂点が、隣り合うような順序で格納する
			//下記の順序に格納すれば、順序が保障される
			VEC_Add( &temp1,&temp2,&outPointList[0]);
			VEC_Add( &outPointList[0],&temp3,&outPointList[0]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[0],&dummy,&outPointList[0]);
			VEC_Subtract( inBoxCore,&outPointList[0],&outPointList[0]);
			
			VEC_Subtract( &temp1,&temp2,&outPointList[1]);
			VEC_Add( &outPointList[1],&temp3,&outPointList[1]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[1],&dummy,&outPointList[1]);
			VEC_Subtract( inBoxCore,&outPointList[1],&outPointList[1]);

			VEC_Subtract( &temp1,&temp2,&outPointList[2]);
			VEC_Subtract( &outPointList[2],&temp3,&outPointList[2]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[2],&dummy,&outPointList[2]);
			VEC_Subtract( inBoxCore,&outPointList[2],&outPointList[2]);

			VEC_Add( &temp1,&temp2,&outPointList[3]);
			VEC_Subtract( &outPointList[3],&temp3,&outPointList[3]);
			VEC_MultAdd(FX32_ONE/2,&outPointList[3],&dummy,&outPointList[3]);
			VEC_Subtract( inBoxCore,&outPointList[3],&outPointList[3]);
			hit_vtx_num = 4;
		}
	}
	return hit_vtx_num;
}

//1頂点が原点を通り、軸平行なボックスの平面の法線ベクトルとD値をインデックスで取得
static void GetBoxPlaneByIdx(const u8 inBoxPlaneIdx, const VecFx32 *inBoxSize, VecFx32 *outNrmVec, fx32 *outD)
{
	*outNrmVec = BoxNrm[inBoxPlaneIdx];
	if ((inBoxPlaneIdx == 0)||(inBoxPlaneIdx == 3)){
		*outD = FX_Mul(BoxDBase[inBoxPlaneIdx],inBoxSize->x);
	}else if((inBoxPlaneIdx == 1)||(inBoxPlaneIdx == 4)){
		*outD = FX_Mul(BoxDBase[inBoxPlaneIdx],inBoxSize->y);
	}else{//((inBoxPlaneIdx == 2)||(inBoxPlaneIdx == 5))
		*outD = FX_Mul(BoxDBase[inBoxPlaneIdx],inBoxSize->z);
	}
}

//1頂点が原点を通り、軸平行なボックスを作成
static void MakeBoxData(VecFx32 * outNrm, fx32 * outD,VecFx32 *outVtx, const VecFx32 *inSize)
{
	u8 i;
	//衝突検出に使うボックスを構成する法線ベクトルと平面のD値を取得
	for(i=0;i<6;i++){
		GetBoxPlaneByIdx(i, inSize, &outNrm[i], &outD[i]);
	}
	
	//ボックスの頂点
	VEC_Set(&outVtx[0],0		,0		  ,0		);
	VEC_Set(&outVtx[1],inSize->x,0		  ,0		);
	VEC_Set(&outVtx[2],inSize->x,inSize->y,0		);
	VEC_Set(&outVtx[3],0		,inSize->y,0		);
	VEC_Set(&outVtx[4],0		,0		  ,inSize->z);
	VEC_Set(&outVtx[5],inSize->x,0		  ,inSize->z);
	VEC_Set(&outVtx[6],inSize->x,inSize->y,inSize->z);
	VEC_Set(&outVtx[7],0		,inSize->y,inSize->z);
}

//1頂点が原点を通り、軸平行なボックスの平面の座標系をインデックスで取得
static u8 GetBoxPlaneFlgByIdx(const u8 inBoxPlaneIdx)
{
	if ((inBoxPlaneIdx == 0)||(inBoxPlaneIdx==3)){
		return YZ_PLANE;
	}else if ((inBoxPlaneIdx == 1)||(inBoxPlaneIdx==4)){
		return ZX_PLANE;
	}else{//(inBoxPlaneIdx == 2)||(inBoxPlaneIdx==5)
		return XY_PLANE;
	}
}


//ボックス平面と直線の交差判定
//平面を構成する4頂点、判定する線分の両端点、平面が構成されている座標系識別フラグ
static BOOL CheckHitPlaneToLineForBox(const VecFx32 *inPlaneVtxs, const VecFx32 *inSegPoints, const u8 inFlg)
{
	//平面と2頂点で衝突した場合
	//衝突した線分が面と交差するかを判定
	//衝突した面は法線ベクトルインデックスから識別する
	VecFx32 vtx[4];
	VecFx32 segPoint[2];

	switch((PLANE_TYPE)inFlg){
	case XY_PLANE:
		//ｘｙ平面で考える
		//関数はｚｘ平面用なので、ｘ→ｚ、ｙ→ｘに変換
		vtx[0].z = inPlaneVtxs[0].x;vtx[0].x = inPlaneVtxs[0].y;
		vtx[1].z = inPlaneVtxs[1].x;vtx[1].x = inPlaneVtxs[1].y;
		vtx[2].z = inPlaneVtxs[2].x;vtx[2].x = inPlaneVtxs[2].y;
		vtx[3].z = inPlaneVtxs[3].x;vtx[3].x = inPlaneVtxs[3].y;
		segPoint[0].z = inSegPoints[0].x;segPoint[0].x = inSegPoints[0].y;
		segPoint[1].z = inSegPoints[1].x;segPoint[1].x = inSegPoints[1].y;
		break;
	case YZ_PLANE:
		//ｙｚ平面で考える
		//関数はｚｘ平面用なので、ｙ→ｚ、ｚ→ｘに変換
		vtx[0].z = inPlaneVtxs[0].y;vtx[0].x = inPlaneVtxs[0].z;
		vtx[1].z = inPlaneVtxs[1].y;vtx[1].x = inPlaneVtxs[1].z;
		vtx[2].z = inPlaneVtxs[2].y;vtx[2].x = inPlaneVtxs[2].z;
		vtx[3].z = inPlaneVtxs[3].y;vtx[3].x = inPlaneVtxs[3].z;
		segPoint[0].z = inSegPoints[0].y;segPoint[0].x = inSegPoints[0].z;
		segPoint[1].z = inSegPoints[1].y;segPoint[1].x = inSegPoints[1].z;
		break;
	case ZX_PLANE:
		//ｚｘ平面で考える
		//関数はｚｘ平面用なので、変換はなし
		vtx[0].z = inPlaneVtxs[0].z;vtx[0].x = inPlaneVtxs[0].x;
		vtx[1].z = inPlaneVtxs[1].z;vtx[1].x = inPlaneVtxs[1].x;
		vtx[2].z = inPlaneVtxs[2].z;vtx[2].x = inPlaneVtxs[2].x;
		vtx[3].z = inPlaneVtxs[3].z;vtx[3].x = inPlaneVtxs[3].x;
		segPoint[0].z = inSegPoints[0].z;segPoint[0].x = inSegPoints[0].x;
		segPoint[1].z = inSegPoints[1].z;segPoint[1].x = inSegPoints[1].x;
		break;
	}
		
	//判定
	if ( CheckHitPlaneToSegment2D( &vtx[0],&vtx[1],&vtx[2],&vtx[3],
						&segPoint[0],&segPoint[1] ) == TRUE ){
		OS_Printf("line_hit_OK!!\n");
		return TRUE;
	}
	return FALSE;

}

////////////////////////////////////////////////////////////////////////////////////////
//ボックス同士の衝突判定
//片方のボックス（衝突される側）を軸に水平になるように回転するための回転行列を作成する
//平行移動行列作成
//衝突する側のＲＳＴ、中心座標を回転行列と掛け合わせる
//衝突面の検索、最大で3面までの判定で言いように、衝突し得ない面を除去する
//各面に対して下記を実行
//面とボックスの衝突判定（ＲＳＴ検出済み版）
//ヒットした場合はいくつの頂点で衝突したかで分岐
//1頂点衝突：衝突座標が面内かを判定
//2頂点衝突：線分が面内にあるか判定
//4頂点衝突：各頂点に対して、1頂点衝突判定を実行
//この時点で衝突していなければ、ボックスの立場を入れ替えて上記を実行
//それでも衝突しない場合は、辺と辺が衝突するかもしれないので、その判定に移る
static BOOL HitCheckBoxToBoxSub(	const VecFx32 *inBoxCore,
									const VecFx32 *inBoxSize, 
									const VecFx32 *inBoxRot,
									const VecFx32 *inDirVec,
									const VecFx32 *inBoxCore2, 
									const VecFx32 *inBoxSize2, 
									const VecFx32 *inBoxRot2,
									VTX_DATA_FOR_BOXHIT *outVDFB)
{
	int i,j;
	MtxFx43 mat4x3;
	MtxFx33 mat3x3;

	VecFx32 vec_P;
	
	VecFx32 dirVec;
	VecFx32 vecR,vecS,vecT;
	VecFx32 vecNrmR,vecNrmS,vecNrmT;
	VecFx32 vecG;

	VecFx32 core_Q;
	VecFx32 vecR_Q,vecS_Q,vecT_Q;
	VecFx32 vtxList[4];

	VecFx32	Nrm[6];
	fx32 D[6];
	VecFx32 box_vtx[8];

	u8 plane_flg;
	
	int vtxNum = 0;	
	VecFx32 core2 = *inBoxCore2;
	VecFx32 core = *inBoxCore;


	vec_P.x = inBoxSize2->x/2;
	vec_P.y = inBoxSize2->y/2;
	vec_P.z = inBoxSize2->z/2;

	MakeBoxData(Nrm,D,box_vtx,inBoxSize2);
	
	GetRST(inBoxSize, inBoxRot, &vecR_Q, &vecS_Q, &vecT_Q);
	
	//片方のボックス（被衝突側）のＲＳＴが各軸(ＸＹＺ)に水平になるように回転、平行移動するための変換行列を作成する
	GetRST(inBoxSize2, inBoxRot2, &vecR, &vecS, &vecT);
	VEC_Normalize(&vecR, &vecNrmR);
	VEC_Normalize(&vecS, &vecNrmS);
	VEC_Normalize(&vecT, &vecNrmT);
	
	//原点へ移動する座標を算出
	{
		VecFx32 dummy={0,0,0};
		VecFx32 temp = {0,0,0};
		VEC_Add(&temp,&vecR,&temp);
		VEC_Add(&temp,&vecS,&temp);
		VEC_Add(&temp,&vecT,&temp);

		VEC_MultAdd(FX32_ONE/2,&temp,&dummy,&temp);

		VEC_Subtract(&core2,&temp,&vecG);
		
	}
	//行列作成
	mat4x3._00 = vecNrmR.x;
	mat4x3._10 = vecNrmR.y;
	mat4x3._20 = vecNrmR.z;
	mat4x3._30 = -(VEC_DotProduct(&vecNrmR, &vecG));
	mat4x3._01 = vecNrmS.x;
	mat4x3._11 = vecNrmS.y;
	mat4x3._21 = vecNrmS.z;
	mat4x3._31 = -(VEC_DotProduct(&vecNrmS, &vecG));
	mat4x3._02 = vecNrmT.x;
	mat4x3._12 = vecNrmT.y;
	mat4x3._22 = vecNrmT.z;
	mat4x3._32 = -(VEC_DotProduct(&vecNrmT, &vecG));
	
	mat3x3._00 = vecNrmR.x;
	mat3x3._10 = vecNrmR.y;
	mat3x3._20 = vecNrmR.z;
	mat3x3._01 = vecNrmS.x;
	mat3x3._11 = vecNrmS.y;
	mat3x3._21 = vecNrmS.z;
	mat3x3._02 = vecNrmT.x;
	mat3x3._12 = vecNrmT.y;
	mat3x3._22 = vecNrmT.z;
	
	//衝突側ボックスの中心座標と、RSTに変換行列を適用
	//被衝突側の変換は、1頂点が原点を通り、軸平行なボックスを作成することで、変換したとみなす
	
	MTX_MultVec43(&core, &mat4x3, &core_Q);
	MTX_MultVec33(&vecR_Q, &mat3x3, &vecR_Q);
	MTX_MultVec33(&vecS_Q, &mat3x3, &vecS_Q);
	MTX_MultVec33(&vecT_Q, &mat3x3, &vecT_Q);
	
	//衝突し得ない面の除去
	//衝突される側のボックスの中心から衝突する側の中心への方向ベクトルと、
	//被衝突側の各面の法線ベクトルとの内積を取り、0以下の面は対象からはずす
	//最大で3面との当たり判定
	//方向ベクトルの指定がない場合(NULL or 0ベクトル)は6面全てと判定する
	for(i=0;i<6;i++){
		//方向ベクトルによる、対象面判定
		if ( (inDirVec != NULL)&&( (inDirVec->x != 0)||(inDirVec->y != 0)||(inDirVec->z != 0) ) ){
			MTX_MultVec33(inDirVec, &mat3x3, &dirVec);
			if(VEC_DotProduct(&Nrm[i],&dirVec) >= 0){
				OS_Printf("through");
				continue;
			}
		}
		
		//衝突側の中心点が比較平面に対し、裏側にある場合は、判定対象からはずしてよい
		//↓回転しながらの衝突もあるため処理をはずす＜＜2004/12/20
/**
		if (VEC_DotProduct(&Nrm[i],&core_Q) + D[i] <= 0){
			OS_Printf("continue\n");
			continue;
		}
*/
		//↑物体が回転しているときは、面が裏側にある場合でも、ねじれの位置の衝突のための1頂点データは取得する必要がある
		//ここで、処理を中断してしまうと、データ取得できないため、この処理は使えない
		//↓代わりの処理
		//被衝突ボックスの中心から衝突ボックスの中心へのベクトルと面の法線ベクトルの内積を取り0、負の場合は
		//判定対象からはずす
		{
			VEC_Subtract(&core_Q,&vec_P,&dirVec);
			if(VEC_DotProduct(&Nrm[i],&dirVec) <= 0){
				continue;
			}
		}

		//衝突検出
		if ( HitCheckPlaneToBox2(&core_Q,
								&vecR_Q,
								&vecS_Q,
								&vecT_Q,
								&Nrm[i],
								D[i] )){
			vtxNum = GetHitPointPlaneToBox2(&core_Q,
											&vecR_Q,
											&vecS_Q,
											&vecT_Q,
											&Nrm[i],
											vtxList);
			OS_Printf("%d_check\n",i);
			
			plane_flg = GetBoxPlaneFlgByIdx(i);
			
			//衝突頂点数により分岐
			if (vtxNum == 1){
				//ねじれの位置の辺どうしの衝突検出のために、衝突頂点を記憶する
				if (outVDFB != NULL){
					if (outVDFB->Count<2){
						outVDFB->VtxData[outVDFB->Count].Idx = i;
						outVDFB->VtxData[outVDFB->Count].Vtx = vtxList[0];
						outVDFB->Count++;
					}
				}
				//平面と1頂点で衝突した場合
				//衝突した点が面内部かを判定
				//衝突した面は法線ベクトルインデックスから識別する
				OS_Printf("vertex_hit\n");
				if (plane_flg == YZ_PLANE){
					if ( ((0<=vtxList[0].y)&&(vtxList[0].y<=inBoxSize2->y))&&
							((0<=vtxList[0].z)&&(vtxList[0].z<=inBoxSize2->z)) ){
						//衝突
						OS_Printf("hit\n");
						return TRUE;
					}
				}else if(plane_flg == ZX_PLANE){
					if ( ((0<=vtxList[0].z)&&(vtxList[0].z<=inBoxSize2->z))&&
							((0<=vtxList[0].x)&&(vtxList[0].x<=inBoxSize2->x)) ){
						//衝突
						OS_Printf("hit\n");
						return TRUE;
					}
				}else{//(plane_flg == XY_PLANE)
					if ( ((0<=vtxList[0].x)&&(vtxList[0].x<=inBoxSize2->x))&&
							((0<=vtxList[0].y)&&(vtxList[0].y<=inBoxSize2->y)) ){
						//衝突
						OS_Printf("hit\n");
						return TRUE;
					}
				}
			}else{ //((vtxNum == 2)||(vtxNum == 4))
				VecFx32 vtx[4];
				VecFx32 segPoint[2];

				if (i==0){
					//ｙｚ平面で考える
					vtx[0] = box_vtx[6];
					vtx[1] = box_vtx[2];
					vtx[2] = box_vtx[1];
					vtx[3] = box_vtx[5];
				}else if(i==1){
					//ｚｘ平面で考える
					vtx[0] = box_vtx[3];
					vtx[1] = box_vtx[2];
					vtx[2] = box_vtx[6];
					vtx[3] = box_vtx[7];
				}else if(i==2){
					//ｘｙ平面で考える
					vtx[0] = box_vtx[7];
					vtx[1] = box_vtx[6];
					vtx[2] = box_vtx[5];
					vtx[3] = box_vtx[4];
				}else if(i==3){
					//ｙｚ平面で考える
					vtx[0] = box_vtx[7];
					vtx[1] = box_vtx[3];
					vtx[2] = box_vtx[0];
					vtx[3] = box_vtx[4];
				}else if(i==4){
					//ｚｘ平面で考える
					vtx[0] = box_vtx[0];
					vtx[1] = box_vtx[1];
					vtx[2] = box_vtx[5];
					vtx[3] = box_vtx[4];
				}else if(i==5){
					//ｘｙ平面で考える
					vtx[0] = box_vtx[3];
					vtx[1] = box_vtx[2];
					vtx[2] = box_vtx[1];
					vtx[3] = box_vtx[0];
				}

				if (vtxNum == 2){
					//平面と2頂点で衝突した場合
					//衝突した線分が面と交差するかを判定
					OS_Printf("segment_hit\n");
					segPoint[0] = vtxList[0];
					segPoint[1] = vtxList[1];
				
					//判定
					if ( CheckHitPlaneToLineForBox(vtx, segPoint, plane_flg) == TRUE ){
						return TRUE;
					}
				}else{//(vtxNum == 4)
					//平面と4頂点で衝突した場合
					//面と衝突する4頂点で構成される4辺それぞれに対し、2頂点衝突時の判定を行う
					OS_Printf("plane_hit\n");
					for (j=0;j<4;j++){
						if (j<3){
							segPoint[0] = vtxList[j];
							segPoint[1] = vtxList[j+1];
						}else{	//(j == 3)
							segPoint[0] = vtxList[3];
							segPoint[1] = vtxList[1];
						}
						//判定
						if ( CheckHitPlaneToLineForBox(vtx, segPoint, plane_flg) == TRUE ){
							return TRUE;
						}
					}//end for
				}//end if (vtxNum == 2)
			}//end if (vtxNum == 1)
		}//end if (HitCheckPlaneToBox2)
	}//end for
	OS_Printf("change\n");
	return FALSE;	//衝突しない
}

//ボックスとボックスのそれぞれの辺がねじれの位置にある場合の衝突検出
static BOOL HitCheckBoxSegToSegNoParallel(VTX_DATA_FOR_BOXHIT *inData, const VecFx32 *inBoxSize)
{
	VecFx32 nrm;
	fx32 d;
	VecFx32 crossPoint;
	u8 flg;
//OS_Printf("HItCount = %d\n",inData->Count);
	if (inData->Count <= 1){
		return FALSE;
	}else if (inData->Count == 2){
		OS_Printf("SegToSeg2Hit\n");
		OS_Printf("idx=%d,%d\n",inData->VtxData[0].Idx,inData->VtxData[1].Idx);
		GetBoxPlaneByIdx(inData->VtxData[0].Idx, inBoxSize, &nrm, &d);

		if ( GetCrossPointPlaneToSegment(&nrm, d, &inData->VtxData[0].Vtx, &inData->VtxData[1].Vtx, &crossPoint)==TRUE){
			//取得座標が面内にあるかを判定
			//ボックスインデックスを渡してどの面で判定するかを決定
			flg = GetBoxPlaneFlgByIdx(inData->VtxData[0].Idx);
			if (flg == YZ_PLANE){
				if ( ((0<=crossPoint.y)&&(crossPoint.y<=inBoxSize->y))&&
						((0<=crossPoint.z)&&(crossPoint.z<=inBoxSize->z)) ){
					//衝突
					OS_Printf("hit_SegToSeg\n");
					return TRUE;
				}
			}else if (flg == ZX_PLANE){
				if ( ((0<=crossPoint.z)&&(crossPoint.z<=inBoxSize->z))&&
						((0<=crossPoint.x)&&(crossPoint.x<=inBoxSize->x)) ){
					//衝突
					OS_Printf("hit_SegToSeg\n");
					return TRUE;
				}
			}else{
				if ( ((0<=crossPoint.x)&&(crossPoint.x<=inBoxSize->x))&&
						((0<=crossPoint.y)&&(crossPoint.y<=inBoxSize->y)) ){
					//衝突
					OS_Printf("hit_SegToSeg\n");
					return TRUE;
				}
			}
		}
	}else { //(inData->count >= 3)
		OS_Printf("SegToSeg3PointOver:%dHit\n",inData->Count);
		SDK_MINMAX_ASSERT(inData->Count, 0, 2);
		//判定を3回行う
		/*for(i=0;i<3;i++){
			GetBoxPlaneByIdx(inData->VtxData[i].Idx, &nrm, &d);
			if (i<2){
				GetCrossPontPlaneToSegment(&nrm, &d, &inData->VtxData[i]Vex, &inData->VtxData[i+1].Vtx, &crossPoint);
			}else{ //(i==2)
				GetCrossPontPlaneToSegment(&nrm, &d, &inData->VtxData[2]Vex, &inData->VtxData[0].Vtx, &crossPoint);
			}
			//取得座標が面内にあるかを判定
			if (1){
				;
			}
		}
		//取得座標が面内にあるかを判定
		if (1){
			;
		}*/
	}
	return FALSE;
}

//ボックスとボックスの衝突検出
BOOL HitCheckBoxToBox(	const VecFx32 *inBoxCore1, 
						const VecFx32 *inBoxSize1, 
						const VecFx32 *inBoxRot1,
						const VecFx32 *inDirVec1,
						const VecFx32 *inBoxCore2, 
						const VecFx32 *inBoxSize2, 
						const VecFx32 *inBoxRot2,
						const VecFx32 *inDirVec2)
{
	VTX_DATA_FOR_BOXHIT data1,data2;
	data1.Count = 0;
	data2.Count = 0;
	//ボックスとボックスの衝突検出する(被衝突ボックスの各面に対して、頂点が衝突、辺が衝突、面が衝突するかを調べる)
	if ( HitCheckBoxToBoxSub(inBoxCore1, inBoxSize1, inBoxRot1, inDirVec1, inBoxCore2, inBoxSize2, inBoxRot2, &data1) == FALSE ){
		//ボックスの立場を入れ替えて、衝突検出する
		if ( HitCheckBoxToBoxSub(inBoxCore2, inBoxSize2, inBoxRot2, inDirVec2, inBoxCore1, inBoxSize1, inBoxRot1, &data2) == FALSE ){
			//衝突する両ボックスの辺が、どの面とも平行ではない場合の衝突を検出する
			if ( HitCheckBoxSegToSegNoParallel(&data1,inBoxSize2) == FALSE ){
				//立場を入れ替えて、衝突検出する
				if ( HitCheckBoxSegToSegNoParallel(&data2,inBoxSize1) == FALSE ){
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}


//クリッピング処理
//2Ｄ空間上の短形と線分の交差判定
//必要データ：4頂点、線分の端点
//ｚｘ平面で考えるので、必ずｙ値を0クリアする
BOOL CheckHitPlaneToSegment2D(	const VecFx32 *inVtx1,
								const VecFx32 *inVtx2,
								const VecFx32 *inVtx3,
								const VecFx32 *inVtx4,
								const VecFx32 *inS_Vec,
								const VecFx32 *inE_Vec )
{
	u8 i;
	u8 res1,res2;
	VecFx32 vtx[5];
	VecFx32 cross;
	VecFx32 segPoint1;
	VecFx32 segPoint2;
	
	vtx[0] = *inVtx1;
	vtx[1] = *inVtx2;
	vtx[2] = *inVtx3;
	vtx[3] = *inVtx4;
	vtx[4] = *inVtx1;
	segPoint1 = *inS_Vec;
	segPoint2 = *inE_Vec;
	//y値の0クリア
	for (i=0;i<5;i++){
		vtx[i].y = 0;
	}
	segPoint1.y = 0;
	segPoint2.y = 0;
	
	for (i=0;i<4;i++){
		res1 = BG2D_VectorSide( &vtx[i], &vtx[i+1], &segPoint1 );
		res2 = BG2D_VectorSide( &vtx[i], &vtx[i+1], &segPoint2 );
		//共に表の場合は、衝突しないので終了
		if (res1 && res2){
			return FALSE;
		}
		else if (res1 ^ res2){
			//表裏に分かれたときは、表側の点を線分との交点に置き換えて処理を続行
			if ( GetPointLineToLine( &vtx[i], &vtx[i+1], &segPoint1,&segPoint2, &cross ) == FALSE ){
				//交点がない場合は、処理を終了
				return FALSE;
			}
			(res1 == 1)? (segPoint1 = cross) : (segPoint2 = cross);
		}else{
			//共に裏の場合は、何もせずに次の線分へ
			;
		}
	}
	//上記処理をこなしても関数を抜けなかった場合は、交差している
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
//2D
//////////////////////////////////////////////////////////////////////
//線分の交差判定
//---------------------------------------------------------------------------------------------------------
/**
 *  外積を使用して指定座標が指定ベクトルの左右どちらにあるかを判定
 *  @param  *inS_Vec        ベクトル始点
 *  @param  *inE_Vec        ベクトル終点
 *  @param  *inT_Vec        指定座標
 *
 *  @retval int         1:表（ベクトル上を含む）　0:裏
*/
//---------------------------------------------------------------------------------------------------------
int BG2D_VectorSide( const VecFx32 *inS_Vec, const VecFx32 *inE_Vec, const VecFx32 *inT_Vec )
{
	fx32 n;
	
	//外積を求める（VEC_CrossProduct未使用）
	n = FX_Mul(inT_Vec->z , (inS_Vec->x - inE_Vec->x))+FX_Mul(inS_Vec->z , (inE_Vec->x - inT_Vec->x))+FX_Mul(inE_Vec->z , (inT_Vec->x - inS_Vec->x));
	
	if      ( n >= 0 ) return  1; // 表(左)
	else  return 0; // 裏(右)
}

//---------------------------------------------------------------------------------------------------------
/**
 * 線分同士の交差判定
 *  @param  *inS_Vec1        ベクトル始点
 *  @param  *inE_Vec1        ベクトル終点
 *  @param  *inS_Vec2        ベクトル始点
 *  @param  *inE_Vec2        ベクトル終点
 *
 *  @retval BOOL
*/
//---------------------------------------------------------------------------------------------------------
BOOL BG2D_CheckSegmentToSegment( const VecFx32 *inS_Vec1, const VecFx32 *inE_Vec1, const VecFx32 *inS_Vec2, const VecFx32 *inE_Vec2 )
{
	if ( ((BG2D_VectorSide(inS_Vec1,inE_Vec1,inS_Vec2) ^ BG2D_VectorSide(inS_Vec1,inE_Vec1,inE_Vec2)) == 0) &&
		 ((BG2D_VectorSide(inS_Vec2,inE_Vec2,inS_Vec1) ^ BG2D_VectorSide(inS_Vec2,inE_Vec2,inE_Vec1)) == 0)	){
		return TRUE;
	}
	else  return FALSE;
}

//直線同士の交点
//直線は、2点で定義する
//定義された直線に対して、もう片方の直線を定義する2点が同じ側にある場合は、交点は外分点となり、異なる場合は、内分点となる
//直線が交差しない場合は、FALSEが返る
BOOL GetPointLineToLine(	const VecFx32 *inS_Vec1,
									const VecFx32 *inE_Vec1,
									const VecFx32 *inS_Vec2,
									const VecFx32 *inE_Vec2,
									VecFx32 *outVec )
{
	fx32 dist1,dist2;
	VecFx32 dirVec;
	fx32 t,len,sc;
	u8 res1,res2;
	
	dist1 = BG3D_GetPointSegmentDistance2(inS_Vec2, inS_Vec1, inE_Vec1);
	dist2 = BG3D_GetPointSegmentDistance2(inE_Vec2, inS_Vec1, inE_Vec1);

	//2点が、判定する直線に対して、どちら側にあるかを調べる
	res1 = BG2D_VectorSide( inS_Vec1, inE_Vec1, inS_Vec2 );
	res2 = BG2D_VectorSide( inS_Vec1, inE_Vec1, inE_Vec2 );
	if (res1 ^ res2){
		//異なる側にあるので、交点は、内分点
		//媒介変数
		t = FX_Div(dist1, (dist1+dist2));
	}else{
		//同じ側にあるので、交点は、外分点
		//媒介変数
		if (dist1>dist2){
			t = FX_Div(dist1, (dist1-dist2));
		}else if (dist1<dist2){
			t = FX_Div(dist2, (dist2-dist1));
		}else{
			//2直線が平行のため交点なし
			return FALSE;
		}
	}
	//媒介変数から交点を求める
	//vector:start→end
	VEC_Subtract(inE_Vec2,inS_Vec2,&dirVec);
	//ｚｘ平面(2D)で考えるので長さ算出やノーマライズする前にｙ値は0クリアする
	dirVec.y = 0;
	//OS_Printf("t = %x\n",t);
	{
		VEC_MultAdd(t , &dirVec, inS_Vec2, outVec);
	}
	return TRUE;
}

//線分の交点
//線分同士が交差しない場合、FLASEが返る
BOOL GetPointSegmentToSegment(	const VecFx32 *inS_Vec1,
									const VecFx32 *inE_Vec1,
									const VecFx32 *inS_Vec2,
									const VecFx32 *inE_Vec2,
									VecFx32 *outVec )
{
	fx32 dist1,dist2;
	VecFx32 dirVec;
	fx32 t;

	//線分同士が交差するかを判定する
	if( BG2D_CheckSegmentToSegment( inS_Vec1, inE_Vec1, inS_Vec2, inE_Vec2 ) == FALSE ){
		return FALSE;	//交差しない
	}
	
	dist1 = BG3D_GetPointSegmentDistance2(inS_Vec2, inS_Vec1, inE_Vec1);
	dist2 = BG3D_GetPointSegmentDistance2(inE_Vec2, inS_Vec1, inE_Vec1);


	//媒介変数
	t = FX_Div(dist1, (dist1+dist2));
	//vector:start→end
	VEC_Subtract(inE_Vec2,inS_Vec2,&dirVec);
	{
		VEC_MultAdd(t , &dirVec, inS_Vec2, outVec);
	}

	return TRUE;
}

//三角形の内外判定ZX射影版
BOOL BG3D_CheckTriangleIObyZX(const VecFx32 inT_Vtx,const VecFx32 inVtx1,const VecFx32 inVtx2,const VecFx32 inVtx3)
{
	//外積を求める（VEC_CrossProduct未使用）
	fx32 cross;
	fx32 cross1;
	fx32 cross2;
	fx32 cross3;
	fx32 cross_total;
	cross = FX_Mul(inVtx3.z,inVtx1.x-inVtx2.x) + FX_Mul(inVtx1.z,inVtx2.x-inVtx3.x) + FX_Mul(inVtx2.z,inVtx3.x-inVtx1.x);
	cross1 = FX_Mul(inVtx2.z,inT_Vtx.x-inVtx1.x) + FX_Mul(inT_Vtx.z,inVtx1.x-inVtx2.x) + FX_Mul(inVtx1.z,inVtx2.x-inT_Vtx.x);
	cross2 = FX_Mul(inVtx3.z,inT_Vtx.x-inVtx2.x) + FX_Mul(inT_Vtx.z,inVtx2.x-inVtx3.x) + FX_Mul(inVtx2.z,inVtx3.x-inT_Vtx.x);
	cross3 = FX_Mul(inVtx1.z,inT_Vtx.x-inVtx3.x) + FX_Mul(inT_Vtx.z,inVtx3.x-inVtx1.x) + FX_Mul(inVtx3.z,inVtx1.x-inT_Vtx.x);

	if (cross < 0){
///		OS_Printf("out\n");
		return FALSE;
	}
	if (cross1 < 0){
///		OS_Printf("out1\n");
		return FALSE;
	}
	if (cross2 < 0){
///		OS_Printf("out2\n");
		return FALSE;
	}
	if (cross3 < 0){
///		OS_Printf("out3\n");
		return FALSE;
	}
#if 0
	OS_Printf("cross:%d\n",cross);
	OS_Printf("cross1:%d\n",cross1);
	OS_Printf("cross2:%d\n",cross2);
	OS_Printf("cross3:%d\n",cross3);
	OS_Printf("cross_total:%d\n",cross_total);
	OS_Printf("z:%x\n",inT_Vtx.z);
	OS_Printf("x:%x\n",inT_Vtx.x);
	OS_Printf("z1:%x\n",inVtx1.z);
	OS_Printf("x1:%x\n",inVtx1.x);
	OS_Printf("z2:%x\n",inVtx2.z);
	OS_Printf("x2:%x\n",inVtx2.x);
	OS_Printf("z3:%x\n",inVtx3.z);
	OS_Printf("x3:%x\n",inVtx3.x);
#endif	
	return TRUE;
}

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
void  VecFx32_to_MtxFx33( MtxFx33* dst, VecFx32* src )
{
	MtxFx33 tmp;

	MTX_RotX33(	dst,FX_SinIdx((u16)src->x),FX_CosIdx((u16)src->x));

	MTX_RotY33(	&tmp,FX_SinIdx((u16)src->y),FX_CosIdx((u16)src->y));
	MTX_Concat33(dst,&tmp,dst);

	MTX_RotZ33(	&tmp,FX_SinIdx((u16)src->z),FX_CosIdx((u16)src->z));
	MTX_Concat33(dst,&tmp,dst);
}

/*---------------------------------------------------------------------
  @brief	360度XYZの回転角→３Ｘ３行列への変換 

  @param	dst MtxFx33:演算結果を格納するMtxFx33型のポインタ
  @param	x	回転角X(360度単位,0-359を超えない事)
  @param	y	回転角Y(360度単位)
  @param	z	回転角Z(360度単位)

  @return none
 *--------------------------------------------------------------------*/
void  Rot360_to_MtxFx33( MtxFx33* dst,u16 x,u16 y,u16 z)
{
	MtxFx33 tmp;

	MTX_RotX33(	dst,_Sin360(x),_Cos360(x));

	MTX_RotY33(	&tmp,_Sin360(y),_Cos360(y));
	MTX_Concat33(dst,&tmp,dst);

	MTX_RotZ33(	&tmp,_Sin360(z),_Cos360(z));
	MTX_Concat33(dst,&tmp,dst);
}

/*---------------------------------------------------------------------
  Name       :ベクトル→４Ｘ３行列への変換 
  In	: dst = 行列ポインタ,dst = ベクトルポインタ 
  Out	: なし
 *--------------------------------------------------------------------*/
void  VecFx32_to_MtxFx43( MtxFx43* dst, VecFx32* src )
{
	MtxFx43 tmp;

	MTX_RotX43(	dst,FX_SinIdx((u16)src->x),FX_CosIdx((u16)src->x));

	MTX_RotY43(	&tmp,FX_SinIdx((u16)src->y),FX_CosIdx((u16)src->y));
	MTX_Concat43(dst,&tmp,dst);

	MTX_RotZ43(	&tmp,FX_SinIdx((u16)src->z),FX_CosIdx((u16)src->z));
	MTX_Concat43(dst,&tmp,dst);
}

/*---------------------------------------------------------------------
  @brief	360度XYZの回転角→4x3行列への変換 

  @param	dst MtxFx43:演算結果を格納するMtxFx43型のポインタ
  @param	x	回転角X(360度単位,0-359を超えない事)
  @param	y	回転角Y(360度単位,0-359)
  @param	z	回転角Z(360度単位,0-359)

  @return none
 *--------------------------------------------------------------------*/
void  Rot360_to_MtxFx43( MtxFx43* dst,u16 x,u16 y,u16 z)
{
	MtxFx43 tmp;

	MTX_RotX43(	dst,_Sin360(x),_Cos360(x));

	MTX_RotY43(	&tmp,_Sin360(y),_Cos360(y));
	MTX_Concat43(dst,&tmp,dst);

	MTX_RotZ43(	&tmp,_Sin360(z),_Cos360(z));
	MTX_Concat43(dst,&tmp,dst);
}

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
void GetPerspectiveScreenSize( u16 PerspWay, fx32 Dist, fx32 Aspect, fx32* pWidth, fx32* pHeight )
{
	fx32 fovySin;
	fx32 fovyCos;
	fx32 fovyTan;

	fovySin = FX_SinIdx( PerspWay );
	fovyCos = FX_CosIdx( PerspWay );

	fovyTan = FX_Div( fovySin, fovyCos );
	
	// 高さを求める
	*pHeight = FX_Mul(Dist, fovyTan);				// (fovySin / fovyCos)*TargetDist
	*pHeight = FX_Mul(*pHeight, 2*FX32_ONE);		// ２かけると画面の高さになる
	
	// 幅を求める(アスペクトを4/3で固定)
	*pWidth  = FX_Mul(*pHeight, Aspect );
}
