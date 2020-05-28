/*---------------------------------------------------------------------------*
  Project:  
  File:     calc2d.c
 *---------------------------------------------------------------------------*/
#include <nnsys.h>
#define	__CALC2D_H_GLOBAL
#include "calc2d.h"

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
int BG2D_VectorSideS32( const Vec2DS32 *inS_Vec, const Vec2DS32 *inE_Vec, const Vec2DS32 *inT_Vec )
{
    s32 n;
    
    //外積を求める（VEC_CrossProduct未使用）
    n = ( inT_Vec->x * (inS_Vec->y - inE_Vec->y))+(inS_Vec->x * (inE_Vec->y - inT_Vec->y))+(inE_Vec->x * (inT_Vec->y - inS_Vec->y));
    if      ( n >= 0 ){
		return  1; // 表(左)
	}
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
BOOL BG2D_CheckSegmentToSegmentS32( const Vec2DS32 *inS_Vec1, const Vec2DS32 *inE_Vec1, const Vec2DS32 *inS_Vec2, const Vec2DS32 *inE_Vec2 )
{

	if ( ((BG2D_VectorSideS32(inS_Vec1,inE_Vec1,inS_Vec2) ^ BG2D_VectorSideS32(inS_Vec1,inE_Vec1,inE_Vec2)) == 1) &&
		 ((BG2D_VectorSideS32(inS_Vec2,inE_Vec2,inS_Vec1) ^ BG2D_VectorSideS32(inS_Vec2,inE_Vec2,inE_Vec1)) == 1)	){
		return TRUE;
	}
	else  return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ベクトルデータを作成する
 *
 *@param	u16 x1：始点座標
 *@param	u16 y1：始点座標
 *@param	u16 x2：終点座標
 *@param	u16 y2：終点座標
 *
 *@return	TP_VECTOR_DATA型：ベクトルの傾きのX=０の時の高さ
 *
 */
//-----------------------------------------------------------------------------
TP_VECTOR_DATA MakeVector( u16 x1, u16 y1, u16 x2, u16 y2 )
{
	s16 height;		// 点の距離高さ
	s16 width;		// 点の距離幅
	TP_VECTOR_DATA	vect;	// ベクトルデータ
	
	//
	// 開始座標と終点座標から傾きとｘ＝０の時のYの値を求める
	//
	height = y2 - y1;
	width = x2 - x1;
	if( width != 0 ){	// ０割回避
		vect.x = FX_Div( height << FX32_SHIFT, width << FX32_SHIFT );		// 傾き
	}else{
		vect.x = 255 << FX32_SHIFT;		// 限りなくY軸に近い傾き値を入れる
	}
	vect.c = (y1 << FX32_SHIFT) - FX_Mul(vect.x, x1 << FX32_SHIFT);	// X=0の時の値セット

	return vect;		// ベクトルを返す
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ベクトルの交点を求める
 *
 *@param	Vec2DS32* vector1_s：ベクトル１の開始点
 *@param	Vec2DS32* vector1_e：ベクトル１の終了点
 *@param	Vec2DS32* vector2_s：ベクトル２の開始点
 *@param	Vec2DS32* vector2_e：ベクトル２の終了点
 *@param	Vec2DS32* cross：交点座標
 *
 *@return	u32型：０：交点なし		１：交点あり
 *
 */
//-----------------------------------------------------------------------------
u32 CheckCrossMatrix( Vec2DS32* vector1_s, Vec2DS32* vector1_e, Vec2DS32* vector2_s, Vec2DS32* vector2_e, Vec2DS32* cross )
{
	fx32 cross_x;					// 小数点型の交点
	fx32 cross_y;					// 小数点型の交点
	fx32 half_x;					// 四捨五入用
	fx32 half_y;					// 四捨五入用	
	TP_VECTOR_DATA vector_data_1;	// 交点計算用ベクトルデータ１
	TP_VECTOR_DATA vector_data_2;	// 交点計算用ベクトルデータ２
	Vec2DS32 vect1_max;				// ベクトル１の最大 範囲内かﾁｪｯｸ用
	Vec2DS32 vect1_min;				// ベクトル１の最小 範囲内かﾁｪｯｸ用
	Vec2DS32 vect2_max;				// ベクトル２の最大 範囲内かﾁｪｯｸ用
	Vec2DS32 vect2_min;				// ベクトル２の最小 範囲内かﾁｪｯｸ用
	


	//
	// 交点初期化
	//
	// 交点をセット
 	if( cross != NULL ){
		cross->x = 0xffff;
		cross->y = 0xffff;
	}


	// ベクトル範囲内に交点があるのかチェック
	if( BG2D_CheckSegmentToSegmentS32( vector1_s, vector1_e,
							vector2_s, vector2_e ) == FALSE ){
		// 交点はありません
		return 0;
	}
	

	// 交点を求めるためのベクトルデータを作成
	vector_data_1 = MakeVector( vector1_s->x, vector1_s->y, vector1_e->x, vector1_e->y );
	vector_data_2 = MakeVector( vector2_s->x, vector2_s->y, vector2_e->x, vector2_e->y );

	
	//
	// 交点を求める
	// ベクトルの２Dの線の方程式から
	// 求める
	// 交点があるかチェック	= 平行かチェック
	if( vector_data_1.x == vector_data_2.x ){
		return 0;
	}

	// 平行でないとき
	// X座標				
	cross_x = FX_Div( (vector_data_2.c - vector_data_1.c), vector_data_1.x - vector_data_2.x );
	
	// Y座標
	cross_y = FX_Mul(vector_data_2.x, cross_x) + vector_data_2.c;
	

	// X座標を四捨五入してs32の座標にする
	if( FX_Modf( cross_x, &half_x ) >= FX32_HALF ){
		half_x += FX32_ONE;
	}
	cross->x = half_x >> FX32_SHIFT;

	// Y座標を四捨五入してs32の座標にする
	if( FX_Modf( cross_y, &half_y ) >= FX32_HALF ){
		half_y += FX32_ONE;
	}
	cross->y = half_y >> FX32_SHIFT;

	//
	// ベクトルの範囲内にあるかチェック
	// 
	// 最大最小値をセット
	// ベクトル１
	if( vector1_s->x >= vector1_e->x ){
		vect1_max.x = vector1_s->x;
		vect1_min.x = vector1_e->x;
	}else{
		vect1_max.x = vector1_e->x;
		vect1_min.x = vector1_s->x;
	}
	if( vector1_s->y >= vector1_e->y ){
		vect1_max.y = vector1_s->y;
		vect1_min.y = vector1_e->y;
	}else{
		vect1_max.y = vector1_e->y;
		vect1_min.y = vector1_s->y;
	}
	// ベクトル２
	if( vector2_s->x >= vector2_e->x ){
		vect2_max.x = vector2_s->x;
		vect2_min.x = vector2_e->x;
	}else{
		vect2_max.x = vector2_e->x;
		vect2_min.x = vector2_s->x;
	}
	if( vector2_s->y >= vector2_e->y ){
		vect2_max.y = vector2_s->y;
		vect2_min.y = vector2_e->y;
	}else{
		vect2_max.y = vector2_e->y;
		vect2_min.y = vector2_s->y;
	}
	
	//
	// 範囲内かチェック
	//
	if( (((vect1_max.x >= cross->x) && (vect1_min.x <= cross->x)) &&
		((vect1_max.y >= cross->y) && (vect1_min.y <= cross->y))) &&
		(((vect2_max.x >= cross->x) && (vect2_min.x <= cross->x)) &&
		((vect2_max.y >= cross->y) && (vect2_min.y <= cross->y))) ){

#if 0
	OS_Printf( "交点  x[%d] y[%d]\n", cross->x, cross->y );
	OS_Printf( "vect1 x[%d] y[%d] - x[%d] y[%d]\n", vect1_max.x, vect1_max.y, vect1_min.x, vect1_min.y );
	OS_Printf( "vect2 x[%d] y[%d] - x[%d] y[%d]\n", vect2_max.x, vect2_max.y, vect2_min.x, vect2_min.y );
	OS_Printf( "vect1 s_x[%d] s_y[%d] e_x[%d] e_y[%d]\n", vector1_s->x, vector1_s->y, vector1_e->x, vector1_e->y );
	OS_Printf( "vect2 s_x[%d] s_y[%d] e_x[%d] e_y[%d]\n", vector2_s->x, vector2_s->y, vector2_e->x, vector2_e->y );
	OS_Printf( "vect1 a[%d] c[%d]\n", vector_data_1.x >> FX32_SHIFT, vector_data_1.c >> FX32_SHIFT );
	OS_Printf( "vect2 a[%d] c[%d]\n\n", vector_data_2.x >> FX32_SHIFT, vector_data_2.c >> FX32_SHIFT );
#endif
		
		return 1;		// 交点がある
	}
	
	return 0;		// 交点はあるが、範囲内ではない
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	絵の情報から内外判定をする
 *
 *@param	Vec2DS32* pData：ピクチャーデータ
 *@param	u32 Size：データサイズ
 *@param	u16 x：判定するX座標
 *@param	u16 y：判定するY座標
 *
 *@return	u32型：０：外　１：内
 *
 */
//-----------------------------------------------------------------------------
u32 CheckInOut( Vec2DS32* pData, u32 Size, u16 x, u16 y )
{
	int				i;					// ループ用	
	u32				check_num;			// 項点数
	Vec2DS32		main_s;				// ﾁｪｯｸ用ベクトル始点座標
	Vec2DS32		main_e;				// ﾁｪｯｸ用ベクトル終点座標
	u8				next_way;			// 次のデータの方向
	u8				now_way;			// 今の方向
	u8				skip_flag;			// 次交点があってもスキップするフラグ
	u32				skip_data_num;		// スキップチェックするデータの要素数
	s32				skip_work;			// スキップチェックの作業用
	

	//
	// 始点と終点を作成
	//
	main_s.x = x;					// チェックする頂点座標を代入
	main_s.y = y;					// チェックする頂点座標を代入
	main_e.x = x;					// チェックする頂点座標の真下の点を代入
	main_e.y = CALC_IN_OUT_CECK_Y;	// チェックする頂点座標の真下の点を代入

	// 変数初期化
	skip_flag = 0;			// スキップしないように初期化

	
	//
	// ピクチャデータ内の全ベクトルを検索し、交点のあるベクトルの数
	// を数える
	// 複数の時：外
	// 単数の時：内
	//
	check_num = 0;		// 項点数カウント初期化
	for( i = 0; i < Size - 1; i++ ){

		// スキップかチェック
		if( skip_flag == 1 ){
			
			skip_flag = 0;		// スキップ解除
			
		}else{
			// 今の点がチェックするベクトルの右にあるか左にあるかチェック 
			// ０の時は絶対に通るようにする
			skip_work = pData[ i ].x - main_s.x;
			if( skip_work == 0 ){	
				// 頂点と同じ
				now_way = 2;
			}else{
				if( skip_work < 0 ){
					// 左
					now_way = 0;
				}else{
					// 右
					now_way = 1;
				}
			}
			
			// 次の方向をチェック
			skip_work = pData[ i + 1 ].x - main_s.x;
			if( skip_work == 0 ){
				// 頂点と同じ
				next_way = 2;
			}else{
				if( skip_work < 0 ){
					// 左
					next_way = 0;
				}else{
					// 右
					next_way = 1;
				}
			}

			// 方向チェック
			if( (now_way != next_way) ||
				((now_way == 2) || (next_way == 2)) ){
			
				// 交点があるのかﾁｪｯｸ
				if( BG2D_CheckSegmentToSegmentS32( &main_s, &main_e,
							&pData[ i ], &pData[ i + 1 ] ) == TRUE ){
					// スキップチェックの要素数をセット
					skip_data_num = i + 2;

					// バッファをオーバーしたら１の頂点からの位置にする
					// なぜなら最終の頂点と０の頂点は一緒になるように作られているためです
					if( skip_data_num >= Size ){
						skip_data_num = (skip_data_num % Size) + 1;
					}
					
					// もし２つ次の頂点がmain_s-_eで作成されるベクトルにY軸で２分割されているときは、
					// 頂点は１つになるので次で、交点があるときはスキップする
					if( (BG2D_VectorSideS32( &main_s, &main_e, &pData[ i ] ) ^
						BG2D_VectorSideS32( &main_s, &main_e, &pData[ skip_data_num ] )) == 1 ){
						// 次交点があったらスキップする
						skip_flag = 1;
					}

					// チェック
					check_num++;
				}				
			}
		}
	}


	//
	// 項点数が単数なら１を返す
	//
	return check_num % 2;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ベクトルの作る角度を求める
 *
 *@param	u16 x1：始点座標
 *@param	u16 y1：始点座標
 *@param	u16 x2：終点座標
 *@param	u16 y2：終点座標
 *@param	u16 x3：始点２座標
 *@param	u16 y3：始点２座標
 *@param	u16 x4：終点２座標
 *@param	u16 y4：終点２座標
 *
 *@return	u16型：ベクトル１と２の作る狭いほうの角度
 *
 */
//-----------------------------------------------------------------------------
u16 GetVectorAngle( u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3, u16 x4, u16 y4 )
{
	u16 rota1, rota2;		// 回転角
	s16	vec_x, vec_y;		// ベクトル
	
	//
	// 1-2　1-3のベクトルを作成し、２直線間の角度を返す 
	//
	// 1-2の角度を計算
	vec_x = x2 - x1;
	vec_y = y2 - y1;

	// 角度を求める
	rota1 = FX_Atan2Idx( vec_y << FX32_SHIFT, vec_x << FX32_SHIFT );

	// 1-3の角度を計算
	vec_x = x3 - x4;
	vec_y = y3 - y4;

	// 角度を求める
	rota2 = FX_Atan2Idx( vec_y << FX32_SHIFT, vec_x << FX32_SHIFT );
	
	
	// 間の角度にする
	if( rota1 > rota2 ){
		rota1 -= rota2;
	}else{
		rota2 -= rota1;
		rota1 = rota2;
	}

	// 間の角度が180より多きときは反対側の小さい角度の方の値にする
	if( rota1 > (180 * 182) ){
		rota1 = (360*182) - rota1;
	}


	return rota1;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ベクトルの長さを求める
 *
 *@param	s32 x1, s32 y1：頂点１
 *@param	s32 x2, s32 y2：頂点２
 *
 *
 *@return	u32型：長さ
 *
 */
//-----------------------------------------------------------------------------
u32 GetVectorDistance( s32 x1, s32 y1, s32 x2, s32 y2 )
{
	s32 dist_x, dist_y;			// 各方向の長さ
	u32	dist;					// ベクトルの長さ
	
	
	//
	// ベクトルの長さを求める
	//
	dist_x = x1 - x2;
	dist_y = y1 - y2;

	// 長さを求める
	dist = FX_Sqrt( ((dist_x * dist_x) + (dist_y * dist_y)) << FX32_SHIFT ) >> FX32_SHIFT;

	return dist;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	頂点のバッファを受け取り中心の座標を求める
 *
 *@param	Vec2DS32* pBuff：バッファ
 *@param	u32 Size：サイズ
 *
 *
 *@return	Vec2DS32型：中心の座標
 *
 */
//-----------------------------------------------------------------------------
Vec2DS32 GetCenterMatrix( Vec2DS32* pBuff, u32 Size )
{
	Vec2DS32 max;		// 最大値
	Vec2DS32 min;		// 最小値
	Vec2DS32 ret;		// 戻り値用
	int	i;				// ループ用
	

	
	// 初期化
	min = pBuff[ 0 ];
	max = pBuff[ 0 ];
	
	//
	//たてと横の最大、最小値を取得 
	//
	for( i = 0; i < Size; i++ ){
		//
		// XとYの最大最小チェック
		//
		if( min.x > pBuff[ i ].x ){
			min.x = pBuff[ i ].x;
		}else{
			if( max.x < pBuff[ i ].x ){
				max.x = pBuff[ i ].x;
			}
		}

		if( min.y > pBuff[ i ].y ){
			min.y = pBuff[ i ].y;
		}else{
			if( max.y < pBuff[ i ].y ){
				max.y = pBuff[ i ].y;
			}
		}
	}


	//
	// 中心座標を求める
	//
	ret.x = ((max.x - min.x) / 2) + min.x;
	ret.y = ((max.y - min.y) / 2) + min.y;
	

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	行列に回転行列をかける
 *
 *@param	MtxFx33* p_matrix：行列
 *@param	u16 rota_num：回転角
 *
 *
 *@return	なし
 *
 */
//-----------------------------------------------------------------------------
void SetRotaMatrix2D( MtxFx33* p_matrix, u16 rota_num )
{
	MtxFx33 work;
	//
	// 回転行列をかける
	//
	MTX_RotZ33( &work, FX_SinIdx(rota_num), FX_CosIdx(rota_num) );

	// かけ合わせる
	MTX_Concat33( &work, p_matrix, p_matrix );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	行列に拡縮行列をかける
 *			使用前にMTX_Identity33（）で単位行列にしておいてください
 *
 *@param	MtxFx33* p_matrix：行列
 *@param	fx32 x：横拡縮値
 *@param	fx32 y：たて拡縮値
 *
 *
 *@return	なし
 *
 */
//-----------------------------------------------------------------------------
void SetScaleMatrix2D( MtxFx33* p_matrix, fx32 x, fx32 y )
{
	MtxFx33 work;

	//
	// 回転行列をかける
	//
	MTX_Scale33( &work, x, y, FX32_ONE );

	// かけ合わせる
	MTX_Concat33( &work, p_matrix, p_matrix );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	行列に座標をかけて、回転、拡縮後の座標を求める
 *			使用前にMTX_Identity33（）で単位行列にしておいてください
 *
 *@param	MtxFx33* p_matrix：行列
 *@param	fx32 x：横座標
 *@param	fx32 y：たて座標
 *@param	fx32* p_get_x：変換後の座標格納用
 *@param	fx32* p_get_y：変換後の座標格納用
 *
 *
 *@return	なし
 *
 */
//-----------------------------------------------------------------------------
void GetMatrix2D( MtxFx33* p_matrix, fx32 x, fx32 y, fx32* p_get_x, fx32* p_get_y )
{
	// 計算する
	*p_get_x = FX_Mul( p_matrix->_00, x ) + FX_Mul( p_matrix->_01, y );
	*p_get_y = FX_Mul( p_matrix->_10, x ) + FX_Mul( p_matrix->_11, y );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	近い点を求める
 *
 *@param	Vec2DS32* pBuff：バッファ
 *@param	u32 Size：サイズ
 *@param	Vec2DS32 mat：近い点を探す座標
 *
 *
 *@return	u32 型：近い座標の添え字
 *
 */
//-----------------------------------------------------------------------------
u32 GetNearMatrix( Vec2DS32* pBuff, u32 Size, Vec2DS32 mat )
{
	u32		  ret;				// 戻り値用
	u32		  dist;				// 最短距離格納用
	int		  i;				// ループ用
	u32		  dist_work;		// 最短ﾁｪｯｸ用
		

	//
	// バッファ０の値で初期化
	// 
	ret = 0;
	dist = GetVectorDistance( pBuff[0].x, pBuff[0].y, mat.x, mat.y );
	
	//
	// 一番近い点のポインタを返す
	//
	for( i = 0; i < Size; i++ ){
		// 距離を求める
		dist_work = GetVectorDistance( pBuff[i].x, pBuff[i].y, mat.x, mat.y );

		// 最短かチェック
		if( dist > dist_work  ){
			dist = dist_work;
			ret = i;
		}
	}

	return ret;
}
