/**
 *	@file	poru_3d.h
 *	@brief	ポルトデモ 3Dヘッダ
 *	@author	Miyuki Iwasawa
 *	@date	06.03.28
 */

#ifndef __H_PORU_3D_H__
#define __H_PORU_3D_H__

#undef	GLOBAL
#ifdef	PORU_DEMO_3D_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif

typedef struct _PORUDEMO_POKE{
	POKEMON_PARAM*	pp;	///<丸ごと
	u16	monsno;		///<ポケモンNo
	u8	seikaku;	///<ポケモンの性格
	u8	sex;		///<ポケモンの性別
	u8	flip;		///<フリップフラグ
	u8	favolite;	///<好き嫌い
	STRBUF*	name;	///<ポケモンのニックネーム
}PORUDEMO_POKE;

typedef struct _PORU3D_WORK{
	GF_CAMERA_PTR	camera;
	void*			ssm;

	SOFT_SPRITE_ARC	ssa;	///<ソフトウェアスプライト
	SOFT_SPRITE	* ss;
}PORU3D_WORK;

#define POKEA_INI_PX	(128)	///<デモポケモン初期座標X
#define POKEA_INI_PY	(96)	///<デモポケモン初期座標Y

/**
 *	@brief	3D関連初期化
 */
GLOBAL void PoruDemo_3DInit(PORU3D_WORK* wk,PORUDEMO_POKE* poke,int heapID);
GLOBAL void PoruDemo_3DMain(PORU3D_WORK* wk);
GLOBAL void PoruDemo_3DRelease(PORU3D_WORK* wk);


#endif	//__H_PORU_3D_H__
