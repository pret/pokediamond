//============================================================================================
/**
 * @file	poketch_realnum.c
 * @bfief	ポケッチ電卓用数値計算
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/cp.h>
#include "common.h"
#include "fntsys.h"

#include "poketch_prv.h"
#include "poketch_realnum.h"




enum {
	DECIMAL_POINT_MAX = 8,		// 小数点以下の有効桁
	DECIMAL_MAX = 99999999,		// 小数点部の最大値

	INTEGER_BIT = 64,
};

enum {
	PLUS = 0,
	MINUS = 1,
};

struct _REAL_NUMBER {
	u64		number	;	// 数値
	u8		point;		// 小数点位置
	u8		sign;		// 符号
	u8		column_max;	// 最大桁数
	u8		illegal;	// 不正な状態
};

static const u64 PointRatio[] = {
	1,
	10,
	100,
	1000,
	10000,
	100000,
	1000000,
	10000000,
	100000000,
	1000000000,
	10000000000,
};



//==============================================================
// Prototype
//==============================================================
static u32 IntColumns( const REAL_NUMBER *rn );
static u32 TotalColumns(const REAL_NUMBER *rn );
static void DecimalCutoff( REAL_NUMBER *rn );
static void PointAdjust( const REAL_NUMBER *cn1, const REAL_NUMBER *cn2, REAL_NUMBER *n1, REAL_NUMBER *n2 );



//------------------------------------------------------------------
/**
 * 作成
 *
 * @param   rn		
 *
 */
//------------------------------------------------------------------
BOOL RNUM_Create( REAL_NUMBER **rn, u32 column_max )
{
	*rn = sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(REAL_NUMBER) );
	if( *rn )
	{
		(*rn)->column_max = column_max;
		RNUM_SetZero( *rn );
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * 削除
 *
 * @param   rn		
 *
 */
//------------------------------------------------------------------
void RNUM_Delete( REAL_NUMBER *rn )
{
	sys_FreeMemoryEz( rn );
}
//------------------------------------------------------------------
/**
 * ゼロにする
 *
 * @param   rn		
 *
 */
//------------------------------------------------------------------
void RNUM_SetZero( REAL_NUMBER *rn )
{
	rn->number = 0;
	rn->sign = PLUS;
	rn->point = 0;
	rn->illegal = FALSE;
}
//------------------------------------------------------------------
/**
 * A = B
 *
 * @param   lhs		A
 * @param   rhs		B
 *
 */
//------------------------------------------------------------------
void RNUM_Set( REAL_NUMBER *lhs, const REAL_NUMBER *rhs )
{
	*lhs = *rhs;
}
//------------------------------------------------------------------
/**
 * 数値指定で初期化する（整数のみ）
 *
 * @param   rn		
 * @param   num		
 *
 */
//------------------------------------------------------------------
void RNUM_SetByInt( REAL_NUMBER *rn, s32 num )
{
	rn->number = (num ^ (num >> 31)) - (num >> 31);
	rn->point = 0;
	rn->sign = (num >> 31) & 1;
	rn->illegal = FALSE;
}
//------------------------------------------------------------------
/**
 * 足し算  a + b = c
 *
 * @param   lhs		a
 * @param   rhs		b
 * @param   ans		c
 *
 */
//------------------------------------------------------------------
void RNUM_Add( const REAL_NUMBER *lhs, const REAL_NUMBER *rhs, REAL_NUMBER *ans )
{
	// 符号が逆なら引き算にする
	if( (lhs->sign == PLUS) && (rhs->sign == MINUS) )
	{
		REAL_NUMBER  n = *rhs;
		n.sign = PLUS;
		RNUM_Sub( lhs, &n, ans );
		return;
	}
	if( (lhs->sign == MINUS) && (rhs->sign == PLUS) )
	{
		REAL_NUMBER n = *lhs;
		n.sign = PLUS;
		RNUM_Sub( rhs, &n, ans );
		return;
	}

	{
		REAL_NUMBER l, r;

		PointAdjust(lhs, rhs, &l, &r);

		ans->number = l.number + r.number;

		ans->point = l.point;
		ans->sign = l.sign;

		DecimalCutoff( ans );
	}
}
//------------------------------------------------------------------
/**
 * 引き算  a - b = c
 *
 * @param   lhs		a
 * @param   rhs		b
 * @param   ans		c
 *
 */
//------------------------------------------------------------------
void RNUM_Sub( const REAL_NUMBER *lhs, const REAL_NUMBER *rhs, REAL_NUMBER *ans )
{
	// 符号が逆なら足し算にする
	if( ( (lhs->sign == PLUS) && (rhs->sign == MINUS) )
	||	( (lhs->sign == MINUS) && (rhs->sign == PLUS) )
	){
		REAL_NUMBER  n = *rhs;
		n.sign ^= 1;
		RNUM_Add( lhs, &n, ans );
		return;
	}

	// 全く同じならゼロ
	if( RNUM_IsEqual( lhs, rhs ) ){
		RNUM_SetZero( ans );
		return;
	}

	{
		REAL_NUMBER  l, r;

		PointAdjust( lhs, rhs, &l, &r );
		lhs = &l;
		rhs = &r;

		// 左辺の方が小さくて符号がプラス
		// または左辺の方が大きくて符号がマイナスなら反転する
		if( (lhs->number < rhs->number) ^ (lhs->sign) )
		{
			const REAL_NUMBER *tmp = lhs;
			lhs = rhs;
			rhs = tmp;
			ans->sign = lhs->sign ^ 1;
		}
		else
		{
			ans->sign = lhs->sign;
		}

		ans->number = lhs->number - rhs->number;
		ans->point = lhs->point;

		DecimalCutoff( ans );
	}
}
//------------------------------------------------------------------
/**
 * 掛け算  a * b = c
 *
 * @param   lhs		a
 * @param   rhs		b
 * @param   ans		c
 *
 */
//------------------------------------------------------------------
void RNUM_Mul( const REAL_NUMBER *lhs, const REAL_NUMBER *rhs, REAL_NUMBER *ans )
{
	ans->number = lhs->number * rhs->number;
	ans->point = lhs->point + rhs->point;
	ans->sign = lhs->sign ^ rhs->sign;

	DecimalCutoff( ans );
}
//------------------------------------------------------------------
/**
 * 割り算  a / b = c
 *
 * @param   lhs		a
 * @param   rhs		b
 * @param   ans		c
 *
 */
//------------------------------------------------------------------
void RNUM_Div( const REAL_NUMBER *lhs, const REAL_NUMBER *rhs, REAL_NUMBER *ans )
{
	REAL_NUMBER l, r;
	u64 rem;
	u32 col;

	if(rhs->number == 0)
	{
		ans->illegal = TRUE;
		return;
	}

	PointAdjust(lhs, rhs, &l, &r);
	lhs = &l;
	rhs = &r;

	CP_SetDiv64_64( l.number, r.number );
	ans->number = CP_GetDivResult64();
	ans->point = 0;
	col = IntColumns( ans );

	rem = CP_GetDivRemainder64();

	while( rem )
	{
		if( (col + 1 + ans->point) >= ans->column_max )
		{
			break;
		}

		rem *= 10;
		CP_SetDiv64_64( rem, r.number );
		ans->number *= 10;
		ans->number += CP_GetDivResult64();
		ans->point++;
		rem = CP_GetDivRemainder64();
	}

	ans->sign = lhs->sign ^ rhs->sign;
}
//------------------------------------------------------------------
/**
 * 整数最下桁として数値を入力
 *
 * @param   rn		
 * @param   num		
 *
 * @retval  BOOL		TRUEで成功。桁一杯ならFALSE
 */
//------------------------------------------------------------------
BOOL RNUM_ShiftInteger( REAL_NUMBER *rn, u32 num )
{
	if(TotalColumns( rn ) >= rn->column_max)
	{
		return FALSE;
	}

	if(rn->point == 0)
	{
		rn->number *= 10;
		rn->number += num;
	}

	return TRUE;
}
//------------------------------------------------------------------
/**
 * 小数点最下桁として数値を入力
 *
 * @param   btn		
 *
 * @retval  BOOL		TRUEで成功。桁一杯ならFALSE
 */
//------------------------------------------------------------------
BOOL RNUM_ShiftDechimal( REAL_NUMBER *rn, u32 num )
{
	if(TotalColumns( rn ) >= rn->column_max)
	{
		return FALSE;
	}

	rn->number *= 10;
	rn->number += num;
	rn->point++;

	return TRUE;
}


//------------------------------------------------------------------
/**
 * 同じ値かどうか調べる
 *
 * @param   lhs		左辺
 * @param   rhs		右辺
 *
 * @retval  BOOL		lhs == rhs ならTRUE
 */
//------------------------------------------------------------------
BOOL RNUM_IsEqual( const REAL_NUMBER *lhs, const REAL_NUMBER *rhs )
{
	if( lhs->number != rhs->number ){
		return FALSE;
	}
	if( lhs->point != rhs->point ){
		return FALSE;
	}
	if( lhs->sign != rhs->sign ){
		if( lhs->number != 0){
			return FALSE;
		}
	}
	return TRUE;
}
//------------------------------------------------------------------
/**
 * 表示可能な数値かどうかを調べる
 *
 * @param   rn			
 * @param   col_max		表示桁最大
 *
 * @retval  BOOL		TRUEで表示可能
 */
//------------------------------------------------------------------
BOOL RNUM_CheckDisable( const REAL_NUMBER *rn, u32 col_max )
{
	u32 col;

	if(rn->illegal){
		return FALSE;
	}

	col = IntColumns( rn );
	if( rn->point )
	{
		col += (1 + rn->point);
	}

	if( col > col_max ){
		return FALSE;
	}

	return TRUE;
}
//------------------------------------------------------------------
/**
 * バッファに文字列としてコピー
 *
 * @param   rn		
 * @param   buf				バッファ
 *
 * @retval  BOOL			サイズオーバーがなければTRUE
 */
//------------------------------------------------------------------
BOOL RNUM_PrintBuf( const REAL_NUMBER *rn, u16 *buf )
{
	u64 val;
	u32 col, c;
	s32 i;
	u16 *cp;

	if(rn->illegal){
		OS_Printf("illegal number\n");
		return FALSE;
	}
	if(rn->number == 0)
	{
		*buf++ = NUM_0;
		if( rn->point )
		{
			*buf++ = NUM_DOT;
			for(i=0; i<rn->point; i++)
			{
				*buf++ = NUM_0;
			}
		}
		*buf = NUM_ENDCODE;
		return TRUE;
	}


	val = rn->number;
	col = 1;
	while( val >= PointRatio[col] ){
		col++;
	}
	c = col;
	i = rn->point - col;
	if(i >= 0){
		c += (2 + i);
	}else if(rn->point){
		c += 1;
	}
	if( (c + rn->sign) > rn->column_max ){
		return FALSE;
	}

	if( rn->sign == MINUS ){
		*buf++ = NUM_MINUS;
	}

	cp = buf;

	if(i >= 0){
		*cp++ = NUM_0;
		*cp++ = NUM_DOT;
		while( i-- ){
			*cp++ = NUM_0;
		}
	}else{
		s32 max = i * -1;
		for(i = 0; i < max; i++){
			CP_SetDiv64_64( val, PointRatio[ col - 1 - i ] );
			*cp++ = NUM_0 + CP_GetDivResult32();
			val = CP_GetDivRemainder64();
		}
		if(rn->point){
			*cp++ = NUM_DOT;
		}
	}

	if( (cp - buf) < c )
	{
		s32 max = c - (cp - buf);
		for(i = 0; i < max; i++)
		{
			CP_SetDiv64_64( val, PointRatio[ max - 1 - i ] );
			*cp++ = NUM_0 + CP_GetDivResult32();
			val = CP_GetDivRemainder64();
		}
	}

	*cp = NUM_ENDCODE;

	return TRUE;


}

//------------------------------------------------------------------
/**
 * 整数部を数値にして取得
 *
 * @param   rn		
 *
 * @retval  u64		
 */
//------------------------------------------------------------------
s64 RNUM_GetInt( const REAL_NUMBER* rn )
{
	s64 num = rn->number;

	num /= PointRatio[rn->point];
	if( rn->sign == MINUS ){
		num *= -1;
	}
	return num;
}

//------------------------------------------------------------------
/**
 * 整数部の桁数を取得
 *
 * @param   rn		
 *
 * @retval  u32		整数部桁数
 */
//------------------------------------------------------------------
static u32 IntColumns( const REAL_NUMBER *rn )
{
	u64 r = 10;
	u32 ret = 1;

	while( rn->number >= r )
	{
		if(++ret > rn->column_max){
			break;
		}
		r *= 10;
	}

	if(ret > rn->point){
		ret -= rn->point;
	}else{
		ret = 1;
	}
	ret += rn->sign;

	return ret;
}



//------------------------------------------------------------------
/**
 * 表示桁数を計算
 *
 * @param   rn		
 *
 * @retval  u32		表示桁数
 */
//------------------------------------------------------------------
static u32 TotalColumns(const REAL_NUMBER *rn )
{
	u32 ret = IntColumns( rn );
	if(rn->point){
		ret += (1 + rn->point);
	}
	return ret;
}


//------------------------------------------------------------------
/**
 * 表示できる桁数に合わせて小数点以下をカットする
 *
 * @param   rn		
 *
 */
//------------------------------------------------------------------
static void DecimalCutoff( REAL_NUMBER *rn )
{
	u32 col;

	OS_TPrintf("CUT  number:%d, point:%d, colmax:%d\n", rn->number, rn->point, rn->column_max);

	// まずは最下桁にゼロが続いていればそれをカット
	if(rn->point)
	{
		CP_SetDiv64_32( rn->number, 10 );
		while( CP_GetDivRemainder64() == 0 )
		{
			rn->number = CP_GetDivResult64();
			CP_SetDiv64_32( rn->number, 10 );

			if(--(rn->point) == 0)
			{
				break;
			}
		}
	}

	col = IntColumns( rn );
	OS_TPrintf("  ck1 point:%d columns:%d\n", rn->point, col);
	if( rn->point )
	{
		col += (1 + rn->point);
		if( col > rn->column_max )
		{
			u32 d = col - rn->column_max;

			if( d <= rn->point )
			{
				CP_SetDiv64_32( rn->number, PointRatio[ d ] );
				rn->number = CP_GetDivResult64();
				rn->point -= d;
				OS_TPrintf("[1p:%d] ", rn->point);
			}
		}
	}
	OS_TPrintf("  end number:%d, point:%d\n", rn->number, rn->point);
}
//------------------------------------------------------------------
/**
 * ２つの実数を同じ小数点位置にそろえ、非constなオブジェクトに入れる
 *
 * @param   cn1		桁合わせ対象１
 * @param   cn2		桁合わせ対象２
 * @param   n1		cn1の桁合わせ後を入れる
 * @param   n2		cn2の桁合わせ後を入れる
 */
//------------------------------------------------------------------
static void PointAdjust( const REAL_NUMBER *cn1, const REAL_NUMBER *cn2, REAL_NUMBER *n1, REAL_NUMBER *n2 )
{
	*n1 = *cn1;
	*n2 = *cn2;

	if(n1->point < n2->point)
	{
		REAL_NUMBER *tmp = n1;
		n1 = n2;
		n2 = tmp;
	}

	{
		u32 p = n1->point - n2->point;
		n2->number *= PointRatio[ p ];
		n2->point = n1->point;
	}
}
