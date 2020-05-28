//=============================================================================================
/**
 * @file	calc2D.h
 * @brief	計算プログラム
 */
//=============================================================================================



#undef GLOBAL
#ifdef __CALC2D_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif

#define		CALC_IN_OUT_CECK_Y		(512)			// 内外判定時のY位置

typedef struct Vec2DS32_tag{
	s32 x;
	s32 y;
}Vec2DS32;

//-------------------------------------
/// 範囲のベクトルをあらわす構造体
typedef struct
{
	fx32 x;			// 傾き
	fx32 c;			// x = 0の時のYの値
} TP_VECTOR_DATA;


GLOBAL int BG2D_VectorSideS32( const Vec2DS32 *inS_Vec, const Vec2DS32 *inE_Vec, const Vec2DS32 *inT_Vec );

GLOBAL BOOL BG2D_CheckSegmentToSegmentS32( const Vec2DS32 *inS_Vec1, const Vec2DS32 *inE_Vec1, const Vec2DS32 *inS_Vec2, const Vec2DS32 *inE_Vec2 );

GLOBAL TP_VECTOR_DATA MakeVector( u16 x1, u16 y1, u16 x2, u16 y2 );

GLOBAL u32 CheckCrossMatrix( Vec2DS32* vector1_s, Vec2DS32* vector1_e, Vec2DS32* vector2_s, Vec2DS32* vector2_e, Vec2DS32* cross );
GLOBAL u32 CheckInOut( Vec2DS32* pData, u32 Size, u16 x, u16 y );
GLOBAL u16 GetVectorAngle( u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3, u16 x4, u16 y4 );
GLOBAL u32 GetVectorDistance( s32 x1, s32 y1, s32 x2, s32 y2 );
GLOBAL Vec2DS32 GetCenterMatrix( Vec2DS32* pBuff, u32 Size );
GLOBAL void SetRotaMatrix2D( MtxFx33* p_matrix, u16 rota_num );
GLOBAL void SetScaleMatrix2D( MtxFx33* p_matrix, fx32 x, fx32 y );
GLOBAL void GetMatrix2D( MtxFx33* p_matrix, fx32 x, fx32 y, fx32* p_get_x, fx32* p_get_y );
GLOBAL u32 GetNearMatrix( Vec2DS32* pBuff, u32 Size, Vec2DS32 mat );


#undef	GLOBAL
