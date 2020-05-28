//============================================================================================
/**
 * @file	zukanwork.h
 * @brief	自分状態データアクセス用ヘッダ
 * @author	tamada GAME FREAK inc.
 * @date	2005.12.15
 */
//============================================================================================
#ifndef __ZUKANWORK_H__
#define __ZUKANWORK_H__

#include "savedata/savedata_def.h"	//SAVEDATA参照のため

#include "poketool/poke_tool.h"
#include "poketool/monsno.h"

//============================================================================================
//============================================================================================
enum{
	ZUKAN_WORK_RANDOM_PACHI = 0,		// パッチール個性乱数

	// ポケモン性別取得用
	ZUKAN_WORK_SEX_FIRST = 0,
	ZUKAN_WORK_SEX_SECOND,

	// ZukanWork_GetPokeSexFlag系関数のエラーコード
	ZUKAN_WORK_GET_SEX_ERR	= 0xffffffff,	

	
	// 全国図鑑最大
	ZUKAN_WORK_ZENKOKU_MONSMAX		= MONSNO_END,
	
	// ｼﾝｵｳｽﾞｶﾝ最大数
	// 今は全国と同じ　後々は　monsno.hにシンオウの最大数定義が出来る
	ZUKAN_WORK_SHINOU_MONSMAX	= SINOU_MAX,

	// ゼンコク図鑑完成に必要なポケモンの数
	ZUKAN_WORK_ZENKOKU_COMP_NOPOKE_NUM = 11,	// 不必要なポケモン数
	ZUKAN_WORK_ZENKOKU_COMP_NUM	= ZUKAN_WORK_ZENKOKU_MONSMAX - ZUKAN_WORK_ZENKOKU_COMP_NOPOKE_NUM,

	// シンオウ図鑑完成に必要なポケモンの数
	ZUKAN_WORK_SHINOU_COMP_NOPOKE_NUM = 1,	// 不必要なポケモン数
	ZUKAN_WORK_SHINOU_COMP_NUM	= ZUKAN_WORK_SHINOU_MONSMAX - ZUKAN_WORK_SHINOU_COMP_NOPOKE_NUM,
		


	// シーウシ　シードルゴの形状数
	ZUKAN_WORK_UMIUSHI_FORM_NUM = 2,	//(ここを変えただけではセーブ領域の方式やワークサイズは変わらないので、形状数が変わったときは内部も変更すること)

	// ミノムッチ　ミノメス　形状数
	ZUKAN_WORK_MINOMUSHI_FORM_NUM = 3,	//(ここを変えただけではセーブ領域の方式やワークサイズは変わらないので、形状数が変わったときは内部も変更すること)

	// デオキシスの形状数
	ZUKAN_WORK_DEOKISISU_FORM_NUM = 4,
	ZUKAN_WORK_DEOKISISU_FORM_SAVEDATA_CUTNUM = 2,	// デオキシスセーブ領域は、急遽　捕獲見たフラグのけつ1byteずづに割り振っています。各1byteにセーブできる形状の数です
	POKEZUKAN_DEOKISISU_INIT = 0xf,	// 初期化時格納されている値
};

//----------------------------------------------------------
//----------------------------------------------------------
typedef struct _ZUKAN_WORK ZUKAN_WORK;

//----------------------------------------------------------
//	セーブデータシステムが依存する関数
//----------------------------------------------------------
extern int ZukanWork_GetWorkSize(void);
extern ZUKAN_WORK * ZukanWork_AllocWork(u32 heapID);


//----------------------------------------------------------
//----------------------------------------------------------
extern void ZukanWork_Init(ZUKAN_WORK * zw);

extern u16 ZukanWork_GetPokeGetCount(const ZUKAN_WORK * zw);
extern u16 ZukanWork_GetPokeSeeCount(const ZUKAN_WORK * zw);

extern u16 ZukanWork_GetShinouPokeGetCount(const ZUKAN_WORK * zw);
extern u16 ZukanWork_GetShinouPokeSeeCount(const ZUKAN_WORK * zw);

// ゼンコク図鑑持っているときー＞全国用の各数字を返す
// ｼﾝｵｳｽﾞｶﾝしかもっていないときー＞シンオウ図鑑用の各数字を返す
extern u16 ZukanWork_GetZukanPokeGetCount(const ZUKAN_WORK * zw);
extern u16 ZukanWork_GetZukanPokeSeeCount(const ZUKAN_WORK * zw);


// ゼンコク図鑑　ｼﾝｵｳ図鑑
// 完成に必要なポケモンだけでカウントした値を取得
extern u16 ZukanWork_GetZenkokuGetCompCount(const ZUKAN_WORK * zw);
extern u16 ZukanWork_GetShinouSeeCompCount(const ZUKAN_WORK * zw);

extern BOOL ZukanWork_CheckZenkokuComp(const ZUKAN_WORK * zw);
extern BOOL ZukanWork_CheckShinouComp(const ZUKAN_WORK * zw);

extern BOOL ZukanWork_GetPokeGetFlag(const ZUKAN_WORK * zw, u16 monsno);
extern BOOL ZukanWork_GetPokeSeeFlag(const ZUKAN_WORK * zw, u16 monsno);
extern u32 ZukanWork_GetPokeSexFlag(const ZUKAN_WORK * zw, u16 monsno, int first_second );
extern u32 ZukanWork_GetPokeAnoonForm(const ZUKAN_WORK * zw, int count);
extern u32 ZukanWork_GetPokeAnoonSeeNum(const ZUKAN_WORK * zw);
extern u32 ZukanWork_GetPokeSiiusiForm(const ZUKAN_WORK * zw, int count);
extern u32 ZukanWork_GetPokeSiiusiSeeNum(const ZUKAN_WORK * zw);
extern u32 ZukanWork_GetPokeSiidorugoForm(const ZUKAN_WORK * zw, int count);
extern u32 ZukanWork_GetPokeSiidorugoSeeNum(const ZUKAN_WORK * zw);
extern u32 ZukanWork_GetPokeMinomuttiForm(const ZUKAN_WORK * zw, int count);
extern u32 ZukanWork_GetPokeMinomuttiSeeNum(const ZUKAN_WORK * zw);
extern u32 ZukanWork_GetPokeMinomesuForm(const ZUKAN_WORK * zw, int count);
extern u32 ZukanWork_GetPokeMinomesuSeeNum(const ZUKAN_WORK * zw);
extern u32 ZukanWork_GetPokeRandomFlag(const ZUKAN_WORK * zw, u8 random_poke);
extern u32 ZukanWork_GetPokeDeokisisuForm(const ZUKAN_WORK * zw, int count);
extern u32 ZukanWork_GetPokeDeokisisuFormSeeNum(const ZUKAN_WORK * zw);
extern u32 ZukanWork_GetPokeForm( const ZUKAN_WORK* zw, int monsno, int count );

extern void ZukanWork_SetPokeSee(ZUKAN_WORK * zw, POKEMON_PARAM * pp);
extern void ZukanWork_SetPokeGet(ZUKAN_WORK * zw, POKEMON_PARAM * pp);

extern BOOL ZukanWork_GetZukanGetFlag(const ZUKAN_WORK * zw);
extern void ZukanWork_SetZukanGetFlag(ZUKAN_WORK * zw);

extern BOOL ZukanWork_GetZenkokuZukanFlag(const ZUKAN_WORK * zw);
extern void ZukanWork_SetZenkokuZukanFlag(ZUKAN_WORK * zw);

extern BOOL ZukanWork_GetGraphicVersionUpFlag(const ZUKAN_WORK * zw);
extern void ZukanWork_SetGraphicVersionUpFlag(ZUKAN_WORK * zw);

extern BOOL ZukanWork_GetTextVersionUpFlag(const ZUKAN_WORK * zw, u16 monsno, u32 country_code);

extern void ZukanWork_SetTextVersionUpMasterFlag( ZUKAN_WORK * zw );
extern BOOL ZukanWork_GetTextVersionUpMasterFlag(const ZUKAN_WORK * zw);

extern void ZukanWork_Copy(const ZUKAN_WORK * from, ZUKAN_WORK * to);

//----------------------------------------------------------
//	セーブデータ取得のための関数
//----------------------------------------------------------
extern ZUKAN_WORK * SaveData_GetZukanWork(SAVEDATA * sv);


//----------------------------------------------------------
//	デバッグ用
//----------------------------------------------------------
extern void Debug_ZukanWork_Make(ZUKAN_WORK * zw, int start, int end, BOOL see_flg);
extern void Debug_ZukanWork_DeokisisuBuckUp( ZUKAN_WORK * zw );

#ifdef CREATE_INDEX
extern void *Index_Get_Zukan_Offset(ZUKAN_WORK *zw);
extern void *Index_Get_Zenkoku_Zukan_Offset(ZUKAN_WORK *zw);
extern void *Index_Get_Get_Flag_Offset(ZUKAN_WORK *zw);
extern void *Index_Get_See_Flag_Offset(ZUKAN_WORK *zw);
extern void *Index_Get_Sex_Flag_Offset(ZUKAN_WORK *zw);
#endif

#endif	// __ZUKANWORK_H__
