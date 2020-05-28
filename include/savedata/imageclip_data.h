//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imageclip_data.h
 *	@brief		イメージクリップセーブデータ
 *	@author		tomoya takahashi
 *	@data		2006.02.27
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMAGECLIP_DATA_H__
#define __IMAGECLIP_DATA_H__

// savedata
#include "savedata/savedata_def.h"	//SAVEDATA参照のため

#include "include/application/imageClip/imc_right_box.h"
#include "include/application/imageClip/imc_accessorie.h"
#include "include/application/imageClip/imc_itemid_define.h"
#include "include/contest/contest_def.h"
#include "include/system/pms_data.h"
#include "include/system/pm_str.h"
#include "strbuf.h"

#undef GLOBAL
#ifdef	__IMAGECLIP_DATA_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define IMC_SAVEDATA_TELEVISION_MYDATA	(0)	///<自分のセーブデータ
#define IMC_SAVEDATA_TELEVISION_OTHER_S	(1)	///<友達のセーブデータ
#define IMC_SAVEDATA_TELEVISION_SAVENUM	(11)///<テレビ局用セーブ数

#define IMC_SAVEDATA_CONTEST_SAVENUM	(5)	///<コンテスト用セーブ数

#define IMC_SAVEDATA_NICKNAME_STR_NUM (11)	///<ニックネームの文字列数
#define IMC_SAVEDATA_OYANAME_STR_NUM (8)	///<親ネームの文字列数
#define IMC_SAVEDATA_STRBUF_NUM	  ( 12 )	///<STRBUFFの必要要素数
#define IMC_SAVEDATA_TELEVISION_ACCE_NUM	( IMC_RBOX_OBJ_MAX - 1 )		///<テレビ局アクセサリ登録数
#define IMC_SAVEDATA_CONTEST_ACCE_NUM	( IMC_RBOX_OBJ_CONTEST_MAX - 1 )


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------

///<大本セーブデータ
typedef struct _IMC_SAVEDATA IMC_SAVEDATA;

///<テレビ局でのクリップワーク
typedef struct _IMC_TELEVISION_SAVEDATA IMC_TELEVISION_SAVEDATA;

///<コンテストでのクリップワーク
typedef struct _IMC_CONTEST_SAVEDATA IMC_CONTEST_SAVEDATA;

///<アイテムのワーク
typedef struct _IMC_ITEM_SAVEDATA IMC_ITEM_SAVEDATA;

///<クリップワーク　ポケモンデータ
typedef struct _IMC_SAVEDATA_POKEMON IMC_SAVEDATA_POKEMON;

///<クリップワーク　アクセサリデータ
typedef struct _IMC_SAVEDATA_ACCESSORIE IMC_SAVEDATA_ACCESSORIE;



//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------
//	セーブデータシステムが依存する関数
//----------------------------------------------------------
GLOBAL int ImcSaveData_GetWorkSize(void);
GLOBAL IMC_SAVEDATA * ImcSaveData_AllocWork(u32 heapID);


// 個々のセーブ領域サイズ取得関数
GLOBAL int ImcSaveData_GetTelevisionWorkSize(void);
GLOBAL int ImcSaveData_GetContestWorkSize(void);

// 個々のセーブ領域確保関数
GLOBAL IMC_TELEVISION_SAVEDATA* ImcSaveData_TelevisionAllocWork(u32 heapID);
GLOBAL IMC_CONTEST_SAVEDATA* ImcSaveData_ContestAllocWork(u32 heapID);
GLOBAL IMC_ITEM_SAVEDATA* ImcSaveData_ItemAllocWork(u32 heapID);


//----------------------------------------------------------
//	セーブデータ取得のための関数
//----------------------------------------------------------
GLOBAL IMC_SAVEDATA * SaveData_GetImcSaveData(SAVEDATA* sv);

//-----------------------------------------------------------------------------
//
//	IMC_SAVEDATA操作関数
//
//-----------------------------------------------------------------------------
//-------------------------------------
//	セーブデータ初期化	
//=====================================
GLOBAL void ImcSaveData_Init(IMC_SAVEDATA* iw);
//-------------------------------------
//	1つのセーブデータを取得する
//=====================================
GLOBAL IMC_TELEVISION_SAVEDATA* ImcSaveData_GetTelevisionSaveData(IMC_SAVEDATA* iw, int no);
GLOBAL IMC_CONTEST_SAVEDATA* ImcSaveData_GetContestSaveData(IMC_SAVEDATA* iw, int no);
GLOBAL IMC_ITEM_SAVEDATA* ImcSaveData_GetItemSaveData(IMC_SAVEDATA* iw);

//-------------------------------------
//	インデックスのセーブデータに値を設定済みかチェック
//	要するにセーブ済みかチェック
//=====================================
GLOBAL BOOL ImcSaveData_CheckTelevisionSaveData(const IMC_SAVEDATA* iw, int no);		// テレビ局用
GLOBAL BOOL ImcSaveData_CheckContestSaveData(const IMC_SAVEDATA* iw, int no);			// コンテスト用



//-----------------------------------------------------------------------------
/**
 *		アクセサリ　BG背景　のアイテム保持フラグ操作関係
 *
 *		アクセサリは、保持最大が、１つの物と９つの物があります。
 *		BG背景の最大保持数は１つです。
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	ちぇっく関数
//=====================================
GLOBAL BOOL ImcSaveData_CheckAcceAdd( const IMC_ITEM_SAVEDATA* p_iow, u32 acce_no, u32 num );
GLOBAL BOOL ImcSaveData_CheckAcceGet( const IMC_ITEM_SAVEDATA* p_iow, u32 acce_no );
GLOBAL BOOL ImcSaveData_CheckBgGet( const IMC_ITEM_SAVEDATA* p_iow, u32 bg_no );

//-------------------------------------
//	保持データ取得関数
//=====================================
GLOBAL u32 ImcSaveData_GetAcceFlag( const IMC_ITEM_SAVEDATA* cp_iow, u32 acce_no );
GLOBAL u32 ImcSaveData_GetBGFlag( const IMC_ITEM_SAVEDATA* cp_iow, u32 bg_no );

GLOBAL u32 ImcSaveData_GetAcceBGAllNum( const IMC_ITEM_SAVEDATA* cp_iow );	// アクセサリとBG背景の全保持数をまとめて返す
GLOBAL u32 ImcSaveData_GetAcceAllNum( const IMC_ITEM_SAVEDATA* cp_iow );	// アクセサリの全保持数をまとめて返す
GLOBAL u32 ImcSaveData_GetBGAllNum( const IMC_ITEM_SAVEDATA* cp_iow );	// BGの全保持数をまとめて返す

//-------------------------------------
//	保持データ設定関数
//=====================================
GLOBAL void ImcSaveData_SetAcceFlag( IMC_ITEM_SAVEDATA* p_iow, u32 acce_no, u32 num );
GLOBAL void ImcSaveData_SetBGFlag( IMC_ITEM_SAVEDATA* p_iow, u32 bg_no );
GLOBAL void ImcSaveData_AddAcceFlag( IMC_ITEM_SAVEDATA* p_iow, u32 acce_no, u32 num );
GLOBAL void ImcSaveData_SubAcceFlag( IMC_ITEM_SAVEDATA* p_iow, u32 acce_no, u32 num );



//-----------------------------------------------------------------------------
//
//	テレビ局クリッピング用セーブデータ
//	IMC_TELEVISION_SAVEDATA操作関数
//
//-----------------------------------------------------------------------------
//-------------------------------------
//	インデックスのセーブデータに値を設定済みかチェック
//=====================================
GLOBAL BOOL ImcSaveData_CheckTelevisionData(const IMC_TELEVISION_SAVEDATA* iow);
//-------------------------------------
//	セーブ完了フラグ設定
//=====================================
GLOBAL void ImcSaveData_SetComplateFlagTelevisionData(IMC_TELEVISION_SAVEDATA* iow);
//-------------------------------------
//	セーブ領域の初期化	再設定のさいにはこれを行う
//=====================================
GLOBAL void ImcSaveData_ClaenTelevisionData(IMC_TELEVISION_SAVEDATA* iow);

//-------------------------------------
//	データ設定関数
//=====================================
GLOBAL void ImcSaveData_SetTelevisionPokeData(IMC_TELEVISION_SAVEDATA* iow, POKEMON_PARAM* pp, IMC_POKE* ip);
GLOBAL void ImcSaveData_SetTelevisionAcceData(IMC_TELEVISION_SAVEDATA* iow, const IMC_ACCESSORIE_OBJ* ao, int no);
GLOBAL void ImcSaveData_SetTelevisionBgId(IMC_TELEVISION_SAVEDATA* iow, u8 bg);
GLOBAL void ImcSaveData_SetTelevisionTitle( IMC_TELEVISION_SAVEDATA* iow, const PMS_DATA* str );	// 使用禁止　下の関数を使用してください
GLOBAL void ImcSaveData_SetTelevisionTitlePmsWord( IMC_TELEVISION_SAVEDATA* iow, PMS_WORD word );
GLOBAL void ImcSaveData_CopyTelevision( IMC_TELEVISION_SAVEDATA* iow, const IMC_TELEVISION_SAVEDATA* set_iow );
GLOBAL void ImcSaveData_SetTelevisionTrData( IMC_TELEVISION_SAVEDATA* iow, const STRBUF* pbuff, int sex );

//-------------------------------------
//	アクセサリの設定チェック関数
//=====================================
GLOBAL BOOL ImcSaveData_CheckTelevisionAcceDataSet(const IMC_TELEVISION_SAVEDATA* iow, int no);

//-------------------------------------
//	データ取得関数
//=====================================
GLOBAL u16 ImcSaveData_GetTelevisionPokeMonsNo(const IMC_TELEVISION_SAVEDATA* iow);
GLOBAL void ImcSaveData_GetTelevisionPokeNickName(const IMC_TELEVISION_SAVEDATA* iow, STRBUF* pbuff);
GLOBAL void ImcSaveData_GetTelevisionPokeOyaName(const IMC_TELEVISION_SAVEDATA* iow, STRBUF* pbuff);	// トレーナー名に変更
GLOBAL u32 ImcSaveData_GetTelevisionPokeOyaSex(const IMC_TELEVISION_SAVEDATA* iow);
GLOBAL u32 ImcSaveData_GetTelevisionPokeRnd(const IMC_TELEVISION_SAVEDATA* iow);
GLOBAL u32 ImcSaveData_GetTelevisionPokeIDNo(const IMC_TELEVISION_SAVEDATA* iow);
GLOBAL u32 ImcSaveData_GetTelevisionPokeFormID(const IMC_TELEVISION_SAVEDATA* iow);
GLOBAL s8 ImcSaveData_GetTelevisionPokePri(const IMC_TELEVISION_SAVEDATA* iow);
GLOBAL u8 ImcSaveData_GetTelevisionPokeX(const IMC_TELEVISION_SAVEDATA* iow);
GLOBAL u8 ImcSaveData_GetTelevisionPokeY(const IMC_TELEVISION_SAVEDATA* iow);
GLOBAL void ImcSaveData_GetTelevisionPokePara(const IMC_TELEVISION_SAVEDATA* iow, POKEMON_PARAM* pp);
GLOBAL u8 ImcSaveData_GetTelevisionAcceNo(const IMC_TELEVISION_SAVEDATA* iow, int no);
GLOBAL u8 ImcSaveData_GetTelevisionAcceMatX(const IMC_TELEVISION_SAVEDATA* iow, int no);
GLOBAL u8 ImcSaveData_GetTelevisionAcceMatY(const IMC_TELEVISION_SAVEDATA* iow, int no);
GLOBAL s8 ImcSaveData_GetTelevisionAccePri(const IMC_TELEVISION_SAVEDATA* iow, int no);
GLOBAL u8 ImcSaveData_GetTelevisionBgId(const IMC_TELEVISION_SAVEDATA* iow);
GLOBAL void ImcSaveData_GetTelevisionTitle( const IMC_TELEVISION_SAVEDATA* iow, PMS_DATA* pbuff );		// 使用禁止　下の関数を使用してください
GLOBAL PMS_WORD ImcSaveData_GetTelevisionTitlePmsWord( const IMC_TELEVISION_SAVEDATA* iow );
GLOBAL u8 ImcSaveData_GetCountryCode( const IMC_TELEVISION_SAVEDATA* iow );



//-----------------------------------------------------------------------------
//
//	コンテストクリッピング用セーブデータ
//	IMC_CONTEST_SAVEDATA操作関数
//	
//-----------------------------------------------------------------------------
//-------------------------------------
//	インデックスのセーブデータに値を設定済みかチェック
//=====================================
GLOBAL BOOL ImcSaveData_CheckContestData(const IMC_CONTEST_SAVEDATA* iow);
//-------------------------------------
//	セーブ完了フラグ設定
//=====================================
GLOBAL void ImcSaveData_SetComplateFlagContestData(IMC_CONTEST_SAVEDATA* iow);
//-------------------------------------
//	セーブ領域の初期化	再設定のさいにはこれを行う
//=====================================
GLOBAL void ImcSaveData_ClaenContestData(IMC_CONTEST_SAVEDATA* iow);

//-------------------------------------
//	データ設定関数
//=====================================
GLOBAL void ImcSaveData_SetContestPokeData(IMC_CONTEST_SAVEDATA* iow, POKEMON_PARAM* pp, IMC_POKE* ip);
GLOBAL void ImcSaveData_SetContestAcceData(IMC_CONTEST_SAVEDATA* iow, const IMC_ACCESSORIE_OBJ* ao, int no);
GLOBAL void ImcSaveData_SetContestBgId(IMC_CONTEST_SAVEDATA* iow, u8 bg);
GLOBAL void ImcSaveData_SetContestRank(IMC_CONTEST_SAVEDATA* iow, u32 rank_code);
GLOBAL void ImcSaveData_CopyContest( IMC_CONTEST_SAVEDATA* iow, const IMC_CONTEST_SAVEDATA* set_iow );

GLOBAL void ImcSaveData_SetContestPokeData_Easy( IMC_CONTEST_SAVEDATA* iow, POKEMON_PARAM* pp, s8 pri );
GLOBAL void ImcSaveData_SetContestAcceData_Easy( IMC_CONTEST_SAVEDATA* iow, u32 acce_idx, u8 acce_no, u8 x, u8 y, s8 pri );

GLOBAL void ImcSaveData_SetContestTrData( IMC_CONTEST_SAVEDATA* iow, const STRBUF* pbuff, int sex );

//-------------------------------------
//	アクセサリ設定チェック関数
//=====================================
GLOBAL BOOL ImcSaveData_CheckContestAcceDataSet(const IMC_CONTEST_SAVEDATA* iow, int no);

//-------------------------------------
//	データ取得関数
//=====================================
GLOBAL u16 ImcSaveData_GetContestPokeMonsNo(const IMC_CONTEST_SAVEDATA* iow);
GLOBAL void ImcSaveData_GetContestPokeNickName(const IMC_CONTEST_SAVEDATA* iow, STRBUF* pbuff);
GLOBAL void ImcSaveData_GetContestPokeOyaName(const IMC_CONTEST_SAVEDATA* iow, STRBUF* pbuff);		// トレーナー名に変更
GLOBAL u32 ImcSaveData_GetContestPokeOyaSex(const IMC_CONTEST_SAVEDATA* iow);		// トレーナー性別に変更
GLOBAL u32 ImcSaveData_GetContestPokeRnd(const IMC_CONTEST_SAVEDATA* iow);
GLOBAL u32 ImcSaveData_GetContestPokeIDNo(const IMC_CONTEST_SAVEDATA* iow);
GLOBAL u32 ImcSaveData_GetContestPokeFormID(const IMC_CONTEST_SAVEDATA* iow);
GLOBAL s8 ImcSaveData_GetContestPokePri(const IMC_CONTEST_SAVEDATA* iow);
GLOBAL u8 ImcSaveData_GetContestPokeX(const IMC_CONTEST_SAVEDATA* iow);
GLOBAL u8 ImcSaveData_GetContestPokeY(const IMC_CONTEST_SAVEDATA* iow);
GLOBAL void ImcSaveData_GetContestPokePara(const IMC_CONTEST_SAVEDATA* iow, POKEMON_PARAM* pp);
GLOBAL u8 ImcSaveData_GetContestAcceNo(const IMC_CONTEST_SAVEDATA* iow, int no);
GLOBAL u8 ImcSaveData_GetContestAcceMatX(const IMC_CONTEST_SAVEDATA* iow, int no);
GLOBAL u8 ImcSaveData_GetContestAcceMatY(const IMC_CONTEST_SAVEDATA* iow, int no);
GLOBAL s8 ImcSaveData_GetContestAccePri(const IMC_CONTEST_SAVEDATA* iow, int no);
GLOBAL u8 ImcSaveData_GetContestBgId(const IMC_CONTEST_SAVEDATA* iow);
GLOBAL u32 ImcSaveData_GetContestRank(const IMC_CONTEST_SAVEDATA* iow);



//-----------------------------------------------------------------------------
/**
 * 
 * アクセサリの２つのデータ
 * テレビ局用
 * コンテスト用
 * 中身には共通の部分が多いです。
 * ポケモンデータとアクセサリ1つのデータです。
 * 共通部分を取り出し、値の取得が出来る仕組みを作成しました。
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	セーブデータワークから
//	ポケモンとアクセサリのワークを取得する
//=====================================
GLOBAL const IMC_SAVEDATA_POKEMON* ImcSaveData_GetTelevisionPokemon(const IMC_TELEVISION_SAVEDATA* iow);
GLOBAL const IMC_SAVEDATA_ACCESSORIE* ImcSaveData_GetTelevisionAcce(const IMC_TELEVISION_SAVEDATA* iow, int no);
GLOBAL const IMC_SAVEDATA_POKEMON* ImcSaveData_GetContestPokemon(const IMC_CONTEST_SAVEDATA* iow);
GLOBAL const IMC_SAVEDATA_ACCESSORIE* ImcSaveData_GetContestAcce(const IMC_CONTEST_SAVEDATA* iow, int no);

//-------------------------------------
//	ポケモンデータ取得
//=====================================
GLOBAL u16 ImcSaveData_GetUtilPokeMonsNo(const IMC_SAVEDATA_POKEMON* iow);
GLOBAL void ImcSaveData_GetUtilPokeNickName(const IMC_SAVEDATA_POKEMON* iow, STRBUF* pbuff);
GLOBAL void ImcSaveData_GetUtilPokeOyaName(const IMC_SAVEDATA_POKEMON* iow, STRBUF* pbuff);
GLOBAL u32 ImcSaveData_GetUtilPokeOyaSex(const IMC_SAVEDATA_POKEMON* iow);
GLOBAL u32 ImcSaveData_GetUtilPokeRnd(const IMC_SAVEDATA_POKEMON* iow);
GLOBAL u32 ImcSaveData_GetUtilPokeIDNo(const IMC_SAVEDATA_POKEMON* iow);
GLOBAL u32 ImcSaveData_GetUtilPokeFormID(const IMC_SAVEDATA_POKEMON* iow);
GLOBAL s8 ImcSaveData_GetUtilPokePri(const IMC_SAVEDATA_POKEMON* iow);
GLOBAL u8 ImcSaveData_GetUtilPokeX(const IMC_SAVEDATA_POKEMON* iow);
GLOBAL u8 ImcSaveData_GetUtilPokeY(const IMC_SAVEDATA_POKEMON* iow);
GLOBAL void ImcSaveData_GetUtilPokePara(const IMC_SAVEDATA_POKEMON* iow, POKEMON_PARAM* pp);

//-------------------------------------
//	アクセサリデータ取得
//=====================================
GLOBAL u8 ImcSaveData_GetUtilAcceNo(const IMC_SAVEDATA_ACCESSORIE* iow);
GLOBAL u8 ImcSaveData_GetUtilAcceMatX(const IMC_SAVEDATA_ACCESSORIE* iow);
GLOBAL u8 ImcSaveData_GetUtilAcceMatY(const IMC_SAVEDATA_ACCESSORIE* iow);
GLOBAL s8 ImcSaveData_GetUtilAccePri(const IMC_SAVEDATA_ACCESSORIE* iow);


//-------------------------------------
//	レコード処理
//=====================================
GLOBAL void ImcSaveData_RecordMix( u8 datanum, int myid, IMC_SAVEDATA* iw, const void** cpp_arry );



//----------------------------------------------------------
//	デバッグ用
//----------------------------------------------------------
#ifdef PM_DEBUG
GLOBAL void Debug_ImcSaveData_Make(IMC_SAVEDATA* iw, int option);
GLOBAL void Debug_ImcSaveData_SetItemData(IMC_ITEM_SAVEDATA* iow);
GLOBAL void Debug_ImcSaveData_MakeTelevisionDummyData(IMC_TELEVISION_SAVEDATA* iow, POKEMON_PARAM* p_pp, u32 acce_num );
GLOBAL void Debug_ImcSaveData_MakeContestDummyData(IMC_CONTEST_SAVEDATA* iow, POKEMON_PARAM* p_pp, u32 acce_num, u32 rank_code );
#endif

#undef	GLOBAL
#endif		// __IMC_SAVEDATA_H__

