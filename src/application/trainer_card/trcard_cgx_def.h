#ifndef __TRCARD_CGX_DEF_H__
#define __TRCARD_CGX_DEF_H__

#define TR_BG_BASE		(1)
//トレーナー画像サイズ	(男女主人公のキャラは32x3だが、ユニオントレーナーサイズに合わせる)
#define TR_BG_SIZE		(10*11/*32*3*/)	

//サイン
#define SIGN_CGX	(TR_BG_BASE)
#define SIGN_PX	(4)
#define SIGN_PY	(14)
#define SIGN_SX	(24)
#define SIGN_SY	(8)
#define SIGN_BYTE_SIZE	(SIGN_SX*SIGN_SY*64)
#define TR_SIGN_SIZE	(SIGN_SX*SIGN_SY)	//サインサイズ

#endif	//__TRCARD_CGX_DEF_H__
