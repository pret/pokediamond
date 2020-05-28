//=============================================================================================
/**
 * @file	calctool.h
 * @brief	計算関係
 * @author	mori
 * @date	2004.10.28
 *
 */
//=============================================================================================
#ifndef	__CALCTOOL_H__
#define	__CALCTOOL_H__
#undef GLOBAL
#ifdef __CALCTOOL_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif

#include "assert.h"


//=============================================================================================
//	定数定義
//=============================================================================================
#define	AFFINE_MAX_NORMAL	( 0 )	// 拡縮の角度を0～0xffffで計算
#define	AFFINE_MAX_256		( 1 )	// 拡縮の角度を0～255で計算
#define	AFFINE_MAX_360		( 2 )	// 拡縮の角度の0～359で計算

#define FX_GET_ROTA_NUM(x)	( (x*0xffff) / 360 )	// FX_SinIdx CosIdxの引数の回転値を求める

#define GF_RAND_MAX			( 0xffff )		// gf_rand()の最大数
#define GF_MT_RAND_MAX		( 0xffffffff )	// gf_mtRand()の最大数

//=============================================================================================
//	プロトタイプ宣言
//=============================================================================================
#define ERRCHECK_ON_DEG_TO_XXX	//この定義を無効にするとDEG関数のエラーチェックを無効にできる

GLOBAL const fx32 FixSinCosTbl[360+90];
GLOBAL const u16 RotKey360Tbl[360];
 #define _Sin360( a ) (FixSinCosTbl[(a)])
 #define _Cos360( a ) (FixSinCosTbl[(a)+90])
 #define _RotKey( a ) (RotKey360Tbl[a])
/**
 *	@brief	度数法で指定した角度から、それぞれの対応する値を取得する
 *	@param	deg	u16:0-359までの変数
 */
 ///SinIdx(),CosIdx(),Indexキーの値を返す(回り込みなし)
 GLOBAL fx32 Sin360(u16 deg);
 GLOBAL fx32 Cos360(u16 deg);
 GLOBAL u16	RotKey(u16 deg);
 ///SinIdx(),CosIdx(),Indexキーの値を返す(回り込みあり)
 GLOBAL fx32 Sin360R(u16 deg);
 GLOBAL fx32 Cos360R(u16 deg);
 GLOBAL u16	RotKeyR(u16 deg);
 ///SinIdx(),CosIdx()の値を返す(fx32型を引数に取る、回り込みあり)
 GLOBAL fx32 Sin360FX(fx32 deg);
 GLOBAL fx32 Cos360FX(fx32 deg);

GLOBAL u32 gf_get_seed(void);		// 乱数の種の取得
GLOBAL void gf_srand(u32 seed);		// 乱数の初期化
GLOBAL u16 gf_rand(void);			// 乱数取得（0 - 65535)
GLOBAL u32 gf_fix_rand( u32 seed );	// 種を渡して取得する乱数

GLOBAL void gf_mtSrand(u32 s);		// MT方乱数初期化関数
GLOBAL u32 gf_mtRand(void);			// MT方乱数取得

//==============================================================================
/**
 *	確率計算用ランダム取得関数
 * 
 * @param   inDinominate	確率分母
 *
 * @retval  u16		0～inDinominate-1の数
 */
//==============================================================================
inline u16 gf_p_rand(const u16 inDinominate)
{
	GF_ASSERT(inDinominate != 0);
	if (inDinominate <= 1){
		return 0;
	}else{
		u16 per;
		u16 val;
		per = (0xffff/inDinominate)+1;
		val = gf_rand()/per;
		GF_ASSERT((val<inDinominate)&&"ERROR:Random Calc Error!");//念のため
		return val;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * BG・OBJのAffine用変換行列を作成 ( 2D )
 *
 * @param	mtx			変換行列格納場所
 * @param	rad			角度 ( MAX = 0xffff )
 * @param	scale_x		X方向の拡大率
 * @param	scale_y		Y方向の拡大率
 * @param	mode		角度変換モード
 *
 * @return	変換行列
 *
 * @li	mode = AFFINE_MAX_256 : theta < 256
 * @li	mode = AFFINE_MAX_360 : theta < 360
 * @li	scale_x(y) = FX32_ONE : １倍
 */
//--------------------------------------------------------------------------------------------
GLOBAL void AffineMtxMake_2D( MtxFx22 * mtx, u16 rad, fx32 scale_x, fx32 scale_y, u8 mode );


///==========================================
//ベクトル演算系のマクロ
///==========================================
//ベクトルコピー
#define VEC_COPY(a,b)	{ \
 (a)->x = (b)->x;	\
 (a)->y = (b)->y;	\
 (a)->z = (b)->z;	\
}

//ベクトル乗算
#define VEC_MUL(dest,a,b)	{	\
 (dest)->x = FX_Mul((a)->x,(b)->x);	\
 (dest)->y = FX_Mul((a)->y,(b)->y);	\
 (dest)->z = FX_Mul((a)->z,(b)->z);	\
}
//ベクトル除算
#define VEC_DIV(dest,a,b)	{	\
 (dest)->x = FX_Div((a)->x,(b)->x);	\
 (dest)->y = FX_Div((a)->y,(b)->y);	\
 (dest)->z = FX_Div((a)->z,(b)->z);	\
}
//ベクトルの実数倍
#define VEC_APPLYM(dest,a,fval) {	\
 (dest)->x = FX_MUL((a)->x,fval);	\
 (dest)->y = FX_MUL((a)->y,fval);	\
 (dest)->z = FX_MUL((a)->z,fval);	\
}
//ベクトルを実数で割る
#define VEC_APPLYD(dest,a,fval) {	\
 (dest)->x = FX_Div((a)->x,fval);	\
 (dest)->y = FX_Div((a)->y,fval);	\
 (dest)->z = FX_Div((a)->z,fval);	\
}


//-----------------------------------------------------------------------------
/**
 *		
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	平面２頂点からゲーフリ独自回転動さ値を取得する
 *
 *	@param	x0		A点ｘ座標
 *	@param	y0		A点ｙ座標
 *	@param	x1		B点ｘ座標
 *	@param	y1		B点ｙ座標
 *
 *	@return	ゲーフリ独自回転動さ距離値
 */
//-----------------------------------------------------------------------------
GLOBAL s32 CalcTool_CircleVectorMove( s32 x0, s32 y0, s32 x1, s32 y1 );


//----------------------------------------------------------------------------
/**
 *	@brief	平面２頂点から任意の動作値を取得する
 *
 *	@param	x0		A点ｘ座標
 *	@param	y0		A点ｙ座標
 *	@param	x1		B点ｘ座標
 *	@param	y1		B点ｙ座標
 *	@param	roopnum	１回転を表す距離
 *
 *	@return	roopnum単位の動作値
 */
//-----------------------------------------------------------------------------
GLOBAL s32 CalcTool_CircleVectorNum( s32 x0, s32 y0, s32 x1, s32 y1, u16 roopnum );


//----------------------------------------------------------------------------
/**
 *	@brief	平面２頂点から任意の動作値を取得する
 *
 *	@param	x0		A点ｘ座標
 *	@param	y0		A点ｙ座標
 *	@param	x1		B点ｘ座標
 *	@param	y1		B点ｙ座標
 *	@param	r		基準半径	この半径で上で移動した距離を求めます
 *
 *	@return	移動距離
 *
 *	応用方法
 *		rの円周を求め、移動距離が円周の何パーセントに当たるかにより、回転角度を求めることも出来ます
 */
//-----------------------------------------------------------------------------
GLOBAL s32 CalcTool_CircleVectorDistance( s32 x0, s32 y0, s32 x1, s32 y1, u32 r );

//----------------------------------------------------------------------------
/**
 *	@brief	半径と距離から現在の回転角を取得する
 *
 *	@param	r		半径
 *	@param	dist	移動距離
 *
 *	@return	移動距離から
 */
//-----------------------------------------------------------------------------
GLOBAL s32 CalcTool_CircleVectroDistRotaGet( u16 r, s32 dist );


#undef GLOBAL
#endif	/*__CALCTOOL_H__*/
