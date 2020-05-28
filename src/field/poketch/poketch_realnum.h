//============================================================================================
/**
 * @file	poketch_realnum.h
 * @bfief	ポケッチ電卓計算
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_REALNUM_H_
#define _POKETCH_REALNUM_H_


enum {
	NUM_0,
	NUM_1,
	NUM_2,
	NUM_3,
	NUM_4,
	NUM_5,
	NUM_6,
	NUM_7,
	NUM_8,
	NUM_9,
	NUM_DOT,
	NUM_MINUS,
	NUM_QUESTION,
	NUM_ENDCODE,
};

typedef struct _REAL_NUMBER		REAL_NUMBER;


//==============================================================
// Prototype
//==============================================================
extern BOOL RNUM_Create( REAL_NUMBER **rn, u32 column_max );
extern void RNUM_Delete( REAL_NUMBER *rn );
extern void RNUM_SetZero( REAL_NUMBER *rn );
extern void RNUM_Set( REAL_NUMBER *lhs, const REAL_NUMBER *rhs );
extern void RNUM_SetByInt( REAL_NUMBER *rn, s32 num );
extern void RNUM_Add( const REAL_NUMBER *lhs, const REAL_NUMBER *rhs, REAL_NUMBER *ans );
extern void RNUM_Sub( const REAL_NUMBER *lhs, const REAL_NUMBER *rhs, REAL_NUMBER *ans );
extern void RNUM_Mul( const REAL_NUMBER *lhs, const REAL_NUMBER *rhs, REAL_NUMBER *ans );
extern void RNUM_Div( const REAL_NUMBER *lhs, const REAL_NUMBER *rhs, REAL_NUMBER *ans );
extern BOOL RNUM_ShiftInteger( REAL_NUMBER *rn, u32 num );
extern BOOL RNUM_ShiftDechimal( REAL_NUMBER *rn, u32 num );
extern BOOL RNUM_IsEqual( const REAL_NUMBER *lhs, const REAL_NUMBER *rhs );
extern BOOL RNUM_CheckDisable( const REAL_NUMBER *rn, u32 col_max );
extern BOOL RNUM_PrintBuf( const REAL_NUMBER *rn, u16 *buf );
extern s64 RNUM_GetInt( const REAL_NUMBER* rn );

#endif
