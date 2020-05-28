//=============================================================================================
/**
 * @file	calctool.c
 * @brief	計算関係
 * @author	mori(GAME FREAK Inc.)
 * @date	2004.10.28
 *
 * @data	2004.10.14 AGB -> NDS
 * @author	mori
 */
//=============================================================================================
#include <nitro.h>

#define __CALCTOOL_H_GLOBAL__
#include "calctool.h"

/**
 *	@brief	SinCosテーブル
 */
const fx32 FixSinCosTbl[360+90] = {
 FX32_SIN0,FX32_SIN1,FX32_SIN2,FX32_SIN3,FX32_SIN4,FX32_SIN5,FX32_SIN6,FX32_SIN7,FX32_SIN8, FX32_SIN9,
 FX32_SIN10,FX32_SIN11,FX32_SIN12,FX32_SIN13,FX32_SIN14,FX32_SIN15,FX32_SIN16,FX32_SIN17,FX32_SIN18,FX32_SIN19,
 FX32_SIN20,FX32_SIN21,FX32_SIN22,FX32_SIN23,FX32_SIN24,FX32_SIN25,FX32_SIN26,FX32_SIN27,FX32_SIN28,FX32_SIN29,
 FX32_SIN30,FX32_SIN31,FX32_SIN32,FX32_SIN33,FX32_SIN34,FX32_SIN35,FX32_SIN36,FX32_SIN37,FX32_SIN38,FX32_SIN39,
 FX32_SIN40,FX32_SIN41,FX32_SIN42,FX32_SIN43,FX32_SIN44,FX32_SIN45,FX32_SIN46,FX32_SIN47,FX32_SIN48,FX32_SIN49,
 FX32_SIN50,FX32_SIN51,FX32_SIN52,FX32_SIN53,FX32_SIN54,FX32_SIN55,FX32_SIN56,FX32_SIN57,FX32_SIN58,FX32_SIN59,
 FX32_SIN60,FX32_SIN61,FX32_SIN62,FX32_SIN63,FX32_SIN64,FX32_SIN65,FX32_SIN66,FX32_SIN67,FX32_SIN68,FX32_SIN69,
 FX32_SIN70,FX32_SIN71,FX32_SIN72,FX32_SIN73,FX32_SIN74,FX32_SIN75,FX32_SIN76,FX32_SIN77,FX32_SIN78,FX32_SIN79,
 FX32_SIN80,FX32_SIN81,FX32_SIN82,FX32_SIN83,FX32_SIN84,FX32_SIN85,FX32_SIN86,FX32_SIN87,FX32_SIN88,FX32_SIN89,
 FX32_SIN90,FX32_SIN91,FX32_SIN92,FX32_SIN93,FX32_SIN94,FX32_SIN95,FX32_SIN96,FX32_SIN97,FX32_SIN98,FX32_SIN99,
 FX32_SIN100,FX32_SIN101,FX32_SIN102,FX32_SIN103,FX32_SIN104,FX32_SIN105,FX32_SIN106,FX32_SIN107,FX32_SIN108,FX32_SIN109,
 FX32_SIN110,FX32_SIN111,FX32_SIN112,FX32_SIN113,FX32_SIN114,FX32_SIN115,FX32_SIN116,FX32_SIN117,FX32_SIN118,FX32_SIN119,
 FX32_SIN120,FX32_SIN121,FX32_SIN122,FX32_SIN123,FX32_SIN124,FX32_SIN125,FX32_SIN126,FX32_SIN127,FX32_SIN128,FX32_SIN129,
 FX32_SIN130,FX32_SIN131,FX32_SIN132,FX32_SIN133,FX32_SIN134,FX32_SIN135,FX32_SIN136,FX32_SIN137,FX32_SIN138,FX32_SIN139,
 FX32_SIN140,FX32_SIN141,FX32_SIN142,FX32_SIN143,FX32_SIN144,FX32_SIN145,FX32_SIN146,FX32_SIN147,FX32_SIN148,FX32_SIN149,
 FX32_SIN150,FX32_SIN151,FX32_SIN152,FX32_SIN153,FX32_SIN154,FX32_SIN155,FX32_SIN156,FX32_SIN157,FX32_SIN158,FX32_SIN159,
 FX32_SIN160,FX32_SIN161,FX32_SIN162,FX32_SIN163,FX32_SIN164,FX32_SIN165,FX32_SIN166,FX32_SIN167,FX32_SIN168,FX32_SIN169,
 FX32_SIN170,FX32_SIN171,FX32_SIN172,FX32_SIN173,FX32_SIN174,FX32_SIN175,FX32_SIN176,FX32_SIN177,FX32_SIN178,FX32_SIN179,
 FX32_SIN180,FX32_SIN181,FX32_SIN182,FX32_SIN183,FX32_SIN184,FX32_SIN185,FX32_SIN186,FX32_SIN187,FX32_SIN188,FX32_SIN189,
 FX32_SIN190,FX32_SIN191,FX32_SIN192,FX32_SIN193,FX32_SIN194,FX32_SIN195,FX32_SIN196,FX32_SIN197,FX32_SIN198,FX32_SIN199,
 FX32_SIN200,FX32_SIN201,FX32_SIN202,FX32_SIN203,FX32_SIN204,FX32_SIN205,FX32_SIN206,FX32_SIN207,FX32_SIN208,FX32_SIN209,
 FX32_SIN210,FX32_SIN211,FX32_SIN212,FX32_SIN213,FX32_SIN214,FX32_SIN215,FX32_SIN216,FX32_SIN217,FX32_SIN218,FX32_SIN219,
 FX32_SIN220,FX32_SIN221,FX32_SIN222,FX32_SIN223,FX32_SIN224,FX32_SIN225,FX32_SIN226,FX32_SIN227,FX32_SIN228,FX32_SIN229,
 FX32_SIN230,FX32_SIN231,FX32_SIN232,FX32_SIN233,FX32_SIN234,FX32_SIN235,FX32_SIN236,FX32_SIN237,FX32_SIN238,FX32_SIN239,
 FX32_SIN240,FX32_SIN241,FX32_SIN242,FX32_SIN243,FX32_SIN244,FX32_SIN245,FX32_SIN246,FX32_SIN247,FX32_SIN248,FX32_SIN249,
 FX32_SIN250,FX32_SIN251,FX32_SIN252,FX32_SIN253,FX32_SIN254,FX32_SIN255,FX32_SIN256,FX32_SIN257,FX32_SIN258,FX32_SIN259,
 FX32_SIN260,FX32_SIN261,FX32_SIN262,FX32_SIN263,FX32_SIN264,FX32_SIN265,FX32_SIN266,FX32_SIN267,FX32_SIN268,FX32_SIN269,
 FX32_SIN270,FX32_SIN271,FX32_SIN272,FX32_SIN273,FX32_SIN274,FX32_SIN275,FX32_SIN276,FX32_SIN277,FX32_SIN278,FX32_SIN279,
 FX32_SIN280,FX32_SIN281,FX32_SIN282,FX32_SIN283,FX32_SIN284,FX32_SIN285,FX32_SIN286,FX32_SIN287,FX32_SIN288,FX32_SIN289,
 FX32_SIN290,FX32_SIN291,FX32_SIN292,FX32_SIN293,FX32_SIN294,FX32_SIN295,FX32_SIN296,FX32_SIN297,FX32_SIN298,FX32_SIN299,
 FX32_SIN300,FX32_SIN301,FX32_SIN302,FX32_SIN303,FX32_SIN304,FX32_SIN305,FX32_SIN306,FX32_SIN307,FX32_SIN308,FX32_SIN309,
 FX32_SIN310,FX32_SIN311,FX32_SIN312,FX32_SIN313,FX32_SIN314,FX32_SIN315,FX32_SIN316,FX32_SIN317,FX32_SIN318,FX32_SIN319,
 FX32_SIN320,FX32_SIN321,FX32_SIN322,FX32_SIN323,FX32_SIN324,FX32_SIN325,FX32_SIN326,FX32_SIN327,FX32_SIN328,FX32_SIN329,
 FX32_SIN330,FX32_SIN331,FX32_SIN332,FX32_SIN333,FX32_SIN334,FX32_SIN335,FX32_SIN336,FX32_SIN337,FX32_SIN338,FX32_SIN339,
 FX32_SIN340,FX32_SIN341,FX32_SIN342,FX32_SIN343,FX32_SIN344,FX32_SIN345,FX32_SIN346,FX32_SIN347,FX32_SIN348,FX32_SIN349,
 FX32_SIN350,FX32_SIN351,FX32_SIN352,FX32_SIN353,FX32_SIN354,FX32_SIN355,FX32_SIN356,FX32_SIN357,FX32_SIN358,FX32_SIN359,

 FX32_COS270,FX32_COS271,FX32_COS272,FX32_COS273,FX32_COS274,FX32_COS275,FX32_COS276,FX32_COS277,FX32_COS278,FX32_COS279,
 FX32_COS280,FX32_COS281,FX32_COS282,FX32_COS283,FX32_COS284,FX32_COS285,FX32_COS286,FX32_COS287,FX32_COS288,FX32_COS289,
 FX32_COS290,FX32_COS291,FX32_COS292,FX32_COS293,FX32_COS294,FX32_COS295,FX32_COS296,FX32_COS297,FX32_COS298,FX32_COS299,
 FX32_COS300,FX32_COS301,FX32_COS302,FX32_COS303,FX32_COS304,FX32_COS305,FX32_COS306,FX32_COS307,FX32_COS308,FX32_COS309,
 FX32_COS310,FX32_COS311,FX32_COS312,FX32_COS313,FX32_COS314,FX32_COS315,FX32_COS316,FX32_COS317,FX32_COS318,FX32_COS319,
 FX32_COS320,FX32_COS321,FX32_COS322,FX32_COS323,FX32_COS324,FX32_COS325,FX32_COS326,FX32_COS327,FX32_COS328,FX32_COS329,
 FX32_COS330,FX32_COS331,FX32_COS332,FX32_COS333,FX32_COS334,FX32_COS335,FX32_COS336,FX32_COS337,FX32_COS338,FX32_COS339,
 FX32_COS340,FX32_COS341,FX32_COS342,FX32_COS343,FX32_COS344,FX32_COS345,FX32_COS346,FX32_COS347,FX32_COS348,FX32_COS349,
 FX32_COS350,FX32_COS351,FX32_COS352,FX32_COS353,FX32_COS354,FX32_COS355,FX32_COS356,FX32_COS357,FX32_COS358,FX32_COS359,
};

/**
 *	@brief	FX_SinIdx(),FX_CosIdx()関数に渡すキーの360度対応変換テーブル
 */
const u16 RotKey360Tbl[360] = {
 0x00000, 0x000b7, 0x0016d, 0x00223, 0x002d9, 0x0038f, 0x00445, 0x004fb, 0x005b1, 0x00667,
 0x0071d, 0x007d3, 0x00889, 0x0093f, 0x009f5, 0x00aab, 0x00b61, 0x00c17, 0x00ccd, 0x00d83,
 0x00e39, 0x00eef, 0x00fa5, 0x0105c, 0x01112, 0x011c8, 0x0127e, 0x01334, 0x013ea, 0x014a0,
 0x01556, 0x0160c, 0x016c2, 0x01778, 0x0182e, 0x018e4, 0x0199a, 0x01a50, 0x01b06, 0x01bbc,
 0x01c72, 0x01d28, 0x01dde, 0x01e94, 0x01f4a, 0x02000, 0x020b7, 0x0216d, 0x02223, 0x022d9,
 0x0238f, 0x02445, 0x024fb, 0x025b1, 0x02667, 0x0271d, 0x027d3, 0x02889, 0x0293f, 0x029f5,
 0x02aab, 0x02b61, 0x02c17, 0x02ccd, 0x02d83, 0x02e39, 0x02eef, 0x02fa5, 0x0305c, 0x03112,
 0x031c8, 0x0327e, 0x03334, 0x033ea, 0x034a0, 0x03556, 0x0360c, 0x036c2, 0x03778, 0x0382e,
 0x038e4, 0x0399a, 0x03a50, 0x03b06, 0x03bbc, 0x03c72, 0x03d28, 0x03dde, 0x03e94, 0x03f4a,
 0x04000, 0x040b7, 0x0416d, 0x04223, 0x042d9, 0x0438f, 0x04445, 0x044fb, 0x045b1, 0x04667,
 0x0471d, 0x047d3, 0x04889, 0x0493f, 0x049f5, 0x04aab, 0x04b61, 0x04c17, 0x04ccd, 0x04d83,
 0x04e39, 0x04eef, 0x04fa5, 0x0505c, 0x05112, 0x051c8, 0x0527e, 0x05334, 0x053ea, 0x054a0,
 0x05556, 0x0560c, 0x056c2, 0x05778, 0x0582e, 0x058e4, 0x0599a, 0x05a50, 0x05b06, 0x05bbc,
 0x05c72, 0x05d28, 0x05dde, 0x05e94, 0x05f4a, 0x06000, 0x060b7, 0x0616d, 0x06223, 0x062d9,
 0x0638f, 0x06445, 0x064fb, 0x065b1, 0x06667, 0x0671d, 0x067d3, 0x06889, 0x0693f, 0x069f5,
 0x06aab, 0x06b61, 0x06c17, 0x06ccd, 0x06d83, 0x06e39, 0x06eef, 0x06fa5, 0x0705c, 0x07112,
 0x071c8, 0x0727e, 0x07334, 0x073ea, 0x074a0, 0x07556, 0x0760c, 0x076c2, 0x07778, 0x0782e,
 0x078e4, 0x0799a, 0x07a50, 0x07b06, 0x07bbc, 0x07c72, 0x07d28, 0x07dde, 0x07e94, 0x07f4a,
 0x08000, 0x080b7, 0x0816d, 0x08223, 0x082d9, 0x0838f, 0x08445, 0x084fb, 0x085b1, 0x08667,
 0x0871d, 0x087d3, 0x08889, 0x0893f, 0x089f5, 0x08aab, 0x08b61, 0x08c17, 0x08ccd, 0x08d83,
 0x08e39, 0x08eef, 0x08fa5, 0x0905c, 0x09112, 0x091c8, 0x0927e, 0x09334, 0x093ea, 0x094a0,
 0x09556, 0x0960c, 0x096c2, 0x09778, 0x0982e, 0x098e4, 0x0999a, 0x09a50, 0x09b06, 0x09bbc,
 0x09c72, 0x09d28, 0x09dde, 0x09e94, 0x09f4a, 0x0a000, 0x0a0b7, 0x0a16d, 0x0a223, 0x0a2d9,
 0x0a38f, 0x0a445, 0x0a4fb, 0x0a5b1, 0x0a667, 0x0a71d, 0x0a7d3, 0x0a889, 0x0a93f, 0x0a9f5,
 0x0aaab, 0x0ab61, 0x0ac17, 0x0accd, 0x0ad83, 0x0ae39, 0x0aeef, 0x0afa5, 0x0b05c, 0x0b112,
 0x0b1c8, 0x0b27e, 0x0b334, 0x0b3ea, 0x0b4a0, 0x0b556, 0x0b60c, 0x0b6c2, 0x0b778, 0x0b82e,
 0x0b8e4, 0x0b99a, 0x0ba50, 0x0bb06, 0x0bbbc, 0x0bc72, 0x0bd28, 0x0bdde, 0x0be94, 0x0bf4a,
 0x0c000, 0x0c0b7, 0x0c16d, 0x0c223, 0x0c2d9, 0x0c38f, 0x0c445, 0x0c4fb, 0x0c5b1, 0x0c667,
 0x0c71d, 0x0c7d3, 0x0c889, 0x0c93f, 0x0c9f5, 0x0caab, 0x0cb61, 0x0cc17, 0x0cccd, 0x0cd83,
 0x0ce39, 0x0ceef, 0x0cfa5, 0x0d05c, 0x0d112, 0x0d1c8, 0x0d27e, 0x0d334, 0x0d3ea, 0x0d4a0,
 0x0d556, 0x0d60c, 0x0d6c2, 0x0d778, 0x0d82e, 0x0d8e4, 0x0d99a, 0x0da50, 0x0db06, 0x0dbbc,
 0x0dc72, 0x0dd28, 0x0ddde, 0x0de94, 0x0df4a, 0x0e000, 0x0e0b7, 0x0e16d, 0x0e223, 0x0e2d9,
 0x0e38f, 0x0e445, 0x0e4fb, 0x0e5b1, 0x0e667, 0x0e71d, 0x0e7d3, 0x0e889, 0x0e93f, 0x0e9f5,
 0x0eaab, 0x0eb61, 0x0ec17, 0x0eccd, 0x0ed83, 0x0ee39, 0x0eeef, 0x0efa5, 0x0f05c, 0x0f112,
 0x0f1c8, 0x0f27e, 0x0f334, 0x0f3ea, 0x0f4a0, 0x0f556, 0x0f60c, 0x0f6c2, 0x0f778, 0x0f82e,
 0x0f8e4, 0x0f99a, 0x0fa50, 0x0fb06, 0x0fbbc, 0x0fc72, 0x0fd28, 0x0fdde, 0x0fe94, 0x0ff4a,
};

/**
 *	@brief	度数法で示した角度に対応するFX_SinIndex()の値を返す(回り込みなし)
 *	@param	deg	u16:0-359度の整数
 *
 *	@return FX_SinIndex()のdegに対応した値
 */
fx32 Sin360(u16 deg)
{
#ifdef ERRCHECK_ON_DEG_TO_XXX
	if(deg >= 360){
		return 0;
	}
#endif
	SDK_MINMAX_ASSERT(deg, 0, 359);
	return FixSinCosTbl[deg];
}
/**
 *	@brief	度数法で示した角度に対応するFX_CosIndex()の値を返す(回り込みなし)
 *	@param	deg	u16:0-359度の整数
 *
 *	@return FX_CosIndex()のdegに対応した値
 */
fx32 Cos360(u16 deg){
#ifdef ERRCHECK_ON_DEG_TO_XXX
	if(deg >= 360)	{
		return 0;
	}
#endif
	SDK_MINMAX_ASSERT(deg, 0, 359);
	return FixSinCosTbl[deg+90];
}

/**
 *	@brief	度数法で示した角度に対応するFX_SinIndex()の値を返す(回り込みあり)
 *	@param	deg	u16:度数法の角度
 *
 *	@return FX_SinIndex()のdegに対応した値
 */
fx32 Sin360R(u16 deg)
{
	return FixSinCosTbl[(deg%360)];
}
/**
 *	@brief	度数法で示した角度に対応するFX_CosIndex()の値を返す(回り込みあり)
 *	@param	deg	u16:度数法の角度
 *
 *	@return FX_CosIndex()のdegに対応した値
 */
fx32 Cos360R(u16 deg)
{
	return FixSinCosTbl[(deg%360)+90];
}

/**
 *	@brief	度数法で示した角度に対応するNitroのローテーションIndexキーを返す(回り込みなし)
 *	@param	deg	u16:度数法の角度
 *
 *	@return degに対応したNitroのIndexキー
 */
u16 RotKey(u16 deg)
{
#ifdef ERRCHECK_ON_DEG_TO_XXX
	if(deg >= 360){
		return 0;
	}
#endif
	SDK_MINMAX_ASSERT(deg, 0, 359);
	return RotKey360Tbl[deg];
}
/**
 *	@brief	度数法で示した角度に対応するNitroのローテーションIndexキーを返す(回り込みなし)
 *	@param	deg	u16:度数法の角度
 *
 *	@return degに対応したNitroのIndexキー
 */
u16 RotKeyR(u16 deg)
{
	return RotKey360Tbl[(deg % 360)];
}

/**
 *	@brief	度数法(fx32)で示した角度に対応するFX_SinIndex()の値を返す(回り込みあり)
 *	@param	deg	fx32:度数法の角度
 *
 *	@return FX_SinIndex()のdegに対応した値
 */
fx32 Sin360FX(fx32 deg)
{
	return FixSinCosTbl[( ((u16)(deg>>12)) % 360 )];
}
/**
 *	@brief	度数法(fx32)で示した角度に対応するFX_CosIndex()の値を返す(回り込みあり)
 *	@param	deg	fx32:度数法の角度
 *
 *	@return FX_CosIndex()のdegに対応した値
 */
fx32 Cos360FX(fx32 deg)
{
	return FixSinCosTbl[( ((u16)(deg>>12)) % 360 ) + 90];
}

//pp_randと干渉しあわない乱数ルーチン
u32 gf_rand_next;

u32 gf_get_seed(void)
{
	return gf_rand_next;
}

void gf_srand(u32 seed)
{
	gf_rand_next = seed;
}

//another_rand
u16 gf_rand(void)
{
    gf_rand_next = gf_rand_next *1103515245L + 24691;	// 
    return (u16)(gf_rand_next / 65536L) ;
}

//==============================================================================
/**
 * $brief   線形合同法乱数取得（乱数の種指定版）
 *          この計算方法では、乱数の種は前回取得した値であることが分かっているため、
 *          返り値を保存すれば、同じ周期の乱数を取得することができる。
 *          ただし、実際にゲーム内で使うときにはu32が値が大きいからといって%（余り）で縮めてはいけない。
 *          0-31でいいからと%32とかすると、同じ値ばかりでるようになります。
 *          /（除算）で小さくすること。
 *
 * @param   seed	乱数の種
 *
 * @retval  u32		乱数（そしてこの値は次の乱数の種にもなる）
 */
//==============================================================================
u32 gf_fix_rand( u32 seed )
{
	// ここで返す値を保存しておけば次の乱数の種になる
	return seed * 1812433253L + 1;
}

/*-----------------------------------------------------------------------------
 *
 *	H16/11/10		Tomoya Takahashi
 *	
 *				MT方での乱数発生関数
 *
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 *					定数宣言
 ----------------------------------------------------------------------------*/
#define N 624						// 乱数配列の要素数
#define M 397						// 自然数
#define MATRIX_A 0x9908b0dfUL		// 求めた値の１ビット目が１の時にXORする値 
#define UPPER_MASK 0x80000000UL		// ビットのw-rビットを取得するマクロ	今はw = 32 r = 31です。
#define LOWER_MASK 0x7fffffffUL		// ビットのrビットを取得するマクロ		こうすると３２ビット符号なしの乱数を取得できます。


/*-----------------------------------------------------------------------------
 *					グローバル変数
 ----------------------------------------------------------------------------*/
static u32 mt[N];						// MTの式の結果の入る配列
static int mti=N+1;						// 配列要素番号(N+1の時は初期化されていない)
static u32 mag01[2]={0x0UL, MATRIX_A};	// 式の結果１ビット目を添え字番号として入れてXorをするテーブル

/*-----------------------------------------------------------------------------
 *
 *				初期化関数
 *
 *	引数
 *		u32 s：シード値(この値から初期化値が線形合同法で生成されます)
 *
 *	戻り値
 *		なし
 *
 *		シード値によりmt配列内を線形合同法の乱数で生成
 * 
 ----------------------------------------------------------------------------*/
void gf_mtSrand(u32 s)
{
    mt[0]= s & 0xffffffff;			// シード値を要素０に代入

	//
	// 線形合同法で乱数を生成
	//
    for (mti=1; mti<N; mti++) {
        mt[mti] = 
	    (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
        mt[mti] &= 0xffffffff;
    }
}



/*-----------------------------------------------------------------------------
 *
 *			符号なし３２ビット長の乱数を取得
 *			
 *	引数
 *		なし
 *
 *	戻り値
 *		u32型：生成された乱数
 *
 ----------------------------------------------------------------------------*/
u32 gf_mtRand(void)
{
    u32 y;
    
	//
	// 乱数の生成
	//
	// 式から乱数を生成するかのチェック
    if (mti >= N) {		// 無限にループさせる
		int kk;			// 式の計算ループ用

		// mtiがN+1のときは初期化
        if (mti == N+1)   
		{
			gf_mtSrand(5489UL);		// 適当な値で初期化
		}

		//
		// mtiがNになったので
		// 式から乱数を生成（僕もわかりません）
		// 
        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;		// 先頭に戻す
    }
  
	//
	// 今の乱数を取得
	// 
    y = mt[mti++];

	// この下の処理でもっと値を分布させています。
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
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
void AffineMtxMake_2D( MtxFx22 * mtx, u16 rad, fx32 scale_x, fx32 scale_y, u8 mode )
{
	if( mode == AFFINE_MAX_256 ){
		rad = (u16)( (u32)(0xffff * rad) >> 8 );
	}else if( mode == AFFINE_MAX_360 ){
		rad = (u16)( (u32)(0xffff * rad) / 360 );
	}

	MTX_Rot22( mtx, FX_SinIdx( rad ), FX_CosIdx( rad ) );
	MTX_ScaleApply22( mtx, mtx, scale_x, scale_y );
}


//-----------------------------------------------------------------------------
/**
 *	平面２頂点から回転動さ距離値を取得する
 */
//-----------------------------------------------------------------------------

// サイズ1のベクトルが動作させた大きさテーブル	半径は2～128です
#define CALC_CIRCLE_VECTOR_PARAM_NUM	( 127 )		// 半径区切る段階数
#define CALC_CIRCLE_VECTOR_MAX			( 0xffff )	// テーブルの1回転の移動大きさ
static const u16 CALC_CircleVectorParam[ CALC_CIRCLE_VECTOR_PARAM_NUM ] = {
	0x169f,
	0xf14,
	0xb4f,
	0x90c,
	0x78a,
	0x676,
	0x5a7,
	0x506,
	0x486,
	0x41c,
	0x3c5,
	0x37a,
	0x33b,
	0x304,
	0x2d3,
	0x2a9,
	0x283,
	0x261,
	0x243,
	0x227,
	0x20e,
	0x1f7,
	0x1e2,
	0x1cf,
	0x1bd,
	0x1ac,
	0x19d,
	0x18f,
	0x182,
	0x175,
	0x169,
	0x15e,
	0x154,
	0x14a,
	0x141,
	0x139,
	0x130,
	0x128,
	0x121,
	0x11a,
	0x113,
	0x10d,
	0x107,
	0x101,
	0xfb,
	0xf6,
	0xf1,
	0xec,
	0xe7,
	0xe3,
	0xde,
	0xda,
	0xd6,
	0xd2,
	0xce,
	0xcb,
	0xc7,
	0xc4,
	0xc1,
	0xbd,
	0xba,
	0xb7,
	0xb4,
	0xb2,
	0xaf,
	0xac,
	0xaa,
	0xa7,
	0xa5,
	0xa3,
	0xa0,
	0x9e,
	0x9c,
	0x9a,
	0x98,
	0x96,
	0x94,
	0x92,
	0x90,
	0x8e,
	0x8d,
	0x8b,
	0x89,
	0x88,
	0x86,
	0x85,
	0x83,
	0x82,
	0x80,
	0x7f,
	0x7d,
	0x7c,
	0x7b,
	0x79,
	0x78,
	0x77,
	0x76,
	0x74,
	0x73,
	0x72,
	0x71,
	0x70,
	0x6f,
	0x6e,
	0x6d,
	0x6c,
	0x6b,
	0x6a,
	0x69,
	0x68,
	0x67,
	0x66,
	0x65,
	0x64,
	0x63,
	0x62,
	0x62,
	0x61,
	0x60,
	0x5f,
	0x5e,
	0x5e,
	0x5d,
	0x5c,
	0x5b,
	0x5b,
	0x5a,
};

//----------------------------------------------------------------------------
/**
 *	@brief	２D専用外積　Zにしか値が入らないのが確定なので高速
 *
 *	@param	cp_a		Aベクトル	ｘ、ｙ
 *	@param	cp_b		Bベクトル	ｘ、ｙ
 *	@param	p_ans		法線ベクトル
 */
//-----------------------------------------------------------------------------
static inline void calcTool_2DGaiseki( const VecFx32* cp_a, const VecFx32* cp_b, VecFx32* p_ans )
{
	p_ans->x = 0;
	p_ans->y = 0;
	p_ans->z = FX_Mul( cp_a->x, cp_b->y ) - FX_Mul( cp_b->x, cp_a->y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	平面２頂点からゲーフリ独自回転動さ距離値を取得する
 *
 *	@param	x0		A点ｘ座標
 *	@param	y0		A点ｙ座標
 *	@param	x1		B点ｘ座標
 *	@param	y1		B点ｙ座標
 *
 *	@return	ゲーフリ独自回転動さ距離値
 */
//-----------------------------------------------------------------------------
s32 CalcTool_CircleVectorMove( s32 x0, s32 y0, s32 x1, s32 y1 )
{
	return CalcTool_CircleVectorNum( x0, y0, x1, y1, 0xffff );
}

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
s32 CalcTool_CircleVectorNum( s32 x0, s32 y0, s32 x1, s32 y1, u16 roopnum )
{
	VecFx32 a,b,c,ans, ac;
	fx32 area_way;
	fx32 r;
	fx32 dist;
	s32 dist_ret;
	s32 r_dis;
	
	// 進んでいる方向を求める
	VEC_Set( &a, x0<<FX32_SHIFT, y0<<FX32_SHIFT, 0 );
	VEC_Set( &b, x1<<FX32_SHIFT, y1<<FX32_SHIFT, 0 );
//	VEC_CrossProduct( &a, &b, &ans );	// 外積で法線ベクトル取得
	calcTool_2DGaiseki( &a, &b, &ans );	// 外積で法線ベクトル取得
	area_way = ans.x + ans.y + ans.z;	// 上下取得

	// 半径を求める
	VEC_Set( &a, x0<<FX32_SHIFT, y0<<FX32_SHIFT, 0 );
	r = VEC_Mag( &a );

	// 進んだ大きさを求める
	// (0, 0)と(x1,x1)の方向ベクトルを作成
	VEC_Set( &b, x1<<FX32_SHIFT, y1<<FX32_SHIFT, 0 );
	VEC_Normalize( &b, &c );	// 単位ベクトル

	// 単位方向ベクトルの半径倍で、(0, 0)と(x1,x1)線分上のRの長さの点Cを作成
	c.x = FX_Mul( c.x, r );	// 半径分進んだ座標
	c.y = FX_Mul( c.y, r );	// 半径分進んだ座標

	VEC_Subtract( &c, &a, &ans );	// A～C線分の長さを求める
	dist = VEC_Mag( &ans );
	dist_ret = dist >> FX32_SHIFT;
	dist_ret = MATH_IAbs( dist_ret );	// 絶対値

	// 距離から動さ値を求める
	r_dis = r >> FX32_SHIFT;
	r_dis -= 2;
	if( r_dis < 0 ){
		r_dis = 0;
	}
	if( r_dis >= CALC_CIRCLE_VECTOR_PARAM_NUM ){
		r_dis = CALC_CIRCLE_VECTOR_PARAM_NUM - 1;
	}

	// 1回転を移動量CALC_CIRCLE_VECTOR_MAXとしたときの値を求める
	dist_ret *= CALC_CircleVectorParam[ r_dis ];

	// その値をroop_numでの値に落とし込む
	dist_ret = (roopnum * dist_ret) / CALC_CIRCLE_VECTOR_MAX;

	// 方向の符号を付ける
	if( area_way <= 0 ){
		dist_ret *= -1;
	}
	return dist_ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	平面２頂点から任意の動作値を取得する
 *
 *	@param	x0		A点ｘ座標
 *	@param	y0		A点ｙ座標
 *	@param	x1		B点ｘ座標
 *	@param	y1		B点ｙ座標
 *	@param	r		基準半径
 *
 *	@return	移動距離
 *
 *	応用方法
 *		rの円周を求め、移動距離が円周の何パーセントに当たるかにより、回転角度を求めることも出来ます
 */
//-----------------------------------------------------------------------------
//#define CALCTOOL_CIRCLEVEC_R_HOSEI
s32 CalcTool_CircleVectorDistance( s32 x0, s32 y0, s32 x1, s32 y1, u32 r )
{
	VecFx32 a,b,c,ans;
	fx32 area_way;
	fx32 dist;
	s32 dist_ret;
	
	// 進んでいる方向を求める
	VEC_Set( &a, x0<<FX32_SHIFT, y0<<FX32_SHIFT, 0 );
	VEC_Set( &b, x1<<FX32_SHIFT, y1<<FX32_SHIFT, 0 );
//	VEC_CrossProduct( &a, &b, &ans );	// 外積で法線ベクトル取得
	calcTool_2DGaiseki( &a, &b, &ans );	// 外積で法線ベクトル取得
	area_way = ans.x + ans.y + ans.z;	// 上下取得

#ifdef CALCTOOL_CIRCLEVEC_R_HOSEI
	// 半径を求める
	VEC_Set( &a, x0<<FX32_SHIFT, y0<<FX32_SHIFT, 0 );
	VEC_Normalize( &a, &b );	// 単位ベクトル
	a.x = FX_Mul( b.x, r << FX32_SHIFT );	// 半径分進んだ座標
	a.y = FX_Mul( b.y, r << FX32_SHIFT );	// 半径分進んだ座標

	// 進んだ大きさを求める
	// (0, 0)と(x1,x1)の方向ベクトルを作成
	VEC_Set( &b, x1<<FX32_SHIFT, y1<<FX32_SHIFT, 0 );
	VEC_Normalize( &b, &c );	// 単位ベクトル

	// 単位方向ベクトルの半径倍で、(0, 0)と(x1,x1)線分上のRの長さの点Cを作成
	c.x = FX_Mul( c.x, r << FX32_SHIFT );	// 半径分進んだ座標
	c.y = FX_Mul( c.y, r << FX32_SHIFT );	// 半径分進んだ座標

	VEC_Subtract( &b, &a, &ans );	// A～C線分の長さを求める
	dist = VEC_Mag( &ans );
	dist_ret = dist >> FX32_SHIFT;
	dist_ret = MATH_IAbs( dist_ret );	// 絶対値

#else
	// oaと垂直な方向に動いている距離を返す
	
	// 原点からa点までのベクトルに垂直な方向ベクトルcを求める
	VEC_Set( &a, y0<<FX32_SHIFT, x0<<FX32_SHIFT, 0 );	// 垂直なベクトル
	VEC_Normalize( &a, &c );	// 単位ベクトルー＞これで方向ベクトルに
	// 方向ベクトルとabベクトルとの内積で、移動距離を求める
	VEC_Set( &a, x0<<FX32_SHIFT, y0<<FX32_SHIFT, 0 );
	VEC_Set( &b, x1<<FX32_SHIFT, y1<<FX32_SHIFT, 0 );
	VEC_Subtract( &b, &a, &ans );	// A～C線分の長さを求める
	dist = VEC_DotProduct( &c, &ans );
	dist_ret = dist >> FX32_SHIFT;
	dist_ret = MATH_IAbs( dist_ret );	// 絶対値
#endif
	// 方向の符号を付ける
	if( area_way <= 0 ){
		dist_ret *= -1;
	}
	return dist_ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	半径と距離から現在の回転角を取得する
 *
 *	@param	r		半径
 *	@param	dist	移動距離
 *
 *	@return	回転角	u16でキャストしてください
 */
//-----------------------------------------------------------------------------
s32 CalcTool_CircleVectroDistRotaGet( u16 r, s32 dist )
{
	s32 r_dist;
	// 円周を求める
	r_dist = FX_Mul( (2*r)<<FX32_SHIFT, FX32_CONST(3.140f) ) >> FX32_SHIFT;
	// distとの比で角度を求める
	return (s32)( (dist * 0xffff) / r_dist );
}
