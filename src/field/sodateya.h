// =================================================================
//
//	sodateya.h
//
//	育て屋用定義
//
//
// =================================================================

#ifndef __SODATEYA_H__
#define __SODATEYA_H__

#include "savedata\sodateyadata.h"
#include "poketool\pokeparty.h"
#include "system\wordset.h"
// =================================================================
// 定数定義
// =================================================================


// =================================================================
// 構造体定義
// =================================================================
/* 育て屋状況 (レコードコーナー用)*/
typedef struct{
//	SIO_MAIL_DATA 	SioMail[SODATEYA_POKE_MAX];		//育て屋に置かれるメールデータ
	u8				SioMail[100];
	u32				PokeNum;						//育て屋にいるポケモンの数
	u16				PokeFlag[SODATEYA_POKE_MAX];	//ポケモンがアイテムを持っているかどうかのフラグ
}SODATEYA_MAIL;

// =================================================================
// PokeAzukeruCheck
// 概要  : 預けているポケモンの数を返す
// 引数  : none
// 戻り値: u8
// =================================================================
extern u8 PokeAzukeruCheck(SODATEYA_WORK *sodateya);

// =================================================================
// PokeAzukeruCheckGet
// 概要  : 預けられるなら空いてる番号を返す
// 引数  : none
// 戻り値: s8	0,1=空いてる番号	-1=無し
// =================================================================
extern int PokeAzukeruCheckGet(SODATEYA_WORK *sodateya);

extern void PokeTamagoDel(SODATEYA_WORK *sodateya, POKEPARTY *party, MYSTATUS *my );


// =================================================================
// PokeSodateSet
// 概要  : ポケモンを預ける
// 引数  : p
// 戻り値: none
// =================================================================
extern void PokeSodateSet(POKEPARTY *party, int pos, SODATEYA_WORK *sodateya, SAVEDATA *sv);


// =================================================================
// PokeSodateyaInit
// 概要  : 育て屋ワーク初期化
// 引数  : none
// 戻り値: none
// =================================================================
extern void PokeSodateyaInit(SODATEYA_WORK *sodateya);

// =================================================================
// PokeMakeTamago
// 概要  : タマゴを作る
// 引数  : sodateya
// 戻り値: none
// =================================================================
extern void PokeMakeTamago(SODATEYA_WORK *sodateya);


// =================================================================
// u8	PokeSodateya
// 概要  : 一歩歩く毎に経験値が加算
// 引数  : none
// 戻り値: BOOL  TRUEの時はタマゴが孵化する
// =================================================================
extern BOOL	PokeSodateya( SODATEYA_WORK *sodateya, POKEPARTY *party, FIELDSYS_WORK *fsys );

// =================================================================
// POKEMON_PARAM * SodateyaSearchHatchingEgg
// 概要　：うまれるタマゴへのポインタを取得
// 引数　：party	手持ちへのポインタ
// 戻り値：POKEMON_PARAMへのポインタ、存在しない場合NULLを返す
// =================================================================
extern POKEMON_PARAM * SodateyaSearchHatchingEgg(POKEPARTY * party);

// =================================================================
// PokeTamagoSet
// 概要  : タマゴをセットする
// 引数  : none
// 戻り値: none
// =================================================================
extern void PokeTamagoSet();

// =================================================================
// void	SodateyaPlusWalk
// 概要  : 指定歩数歩いたことにする
// 引数  : none
// 戻り値: none
// =================================================================
extern void	SodateyaPlusWalk( SODATEYA_WORK *sodateya, u16 count);

// =================================================================
// SodateTamagoHuka
// 概要  : タマゴをポケモンにかえす
// 引数  : none(ただしScriptParameter0に手持ちの番号が入ってる)
// 戻り値: none
// =================================================================
extern void SodateTamagoHuka( POKEMON_PARAM *pp, int heap );


// =================================================================
// SioMailDataInit
// 概要  : 育て屋メールワークを初期化
// 引数  : smd
// 戻り値: none
// =================================================================
extern void SioMailDataInit(SIO_MAIL_DATA	*smd);


// =================================================================
// TamagoFlagsSet
// 概要  : タマゴを作る
// 引数  : poke			:格納する場所のポインタ
//       : monsno		:ポケモンの番号（開発ナンバー）
//		 : flag			:ゲーム内イベントでもらったか？（1:はい  0:育て屋）
// 戻り値: none
// =================================================================
extern void PokemonTamagoSet(POKEMON_PARAM *pp, u16 monsno, SODATEYA_WORK *sodateya, u32 id, u8 form_no);

	
// =================================================================
// TamagoFlagsSet_forEvent
// 概要  : タマゴを作る(イベント用）
// 引数  : poke			:格納する場所のポインタ
//       : monsno		:ポケモンの番号（開発ナンバー）
//		 : flag			:ゲーム内イベントでもらったか？（1:はい  0:育て屋）
// 戻り値: none
// =================================================================
void PokemonTamagoSet_forEvent(POKEMON_PARAM *pp, u16 monsno, u8 eventflag, MYSTATUS *status, int setid, int placeid );


// =================================================================
// PokeAzukeInfoCheck
// 概要  : 育て屋に預けているポケモンのアイテム状況を調べる
// 引数  : sodateya
//       : mailinfo
// 戻り値: none
// =================================================================
extern void PokeAzukeInfoCheck(SODATEYA_WORK *sodateya, SODATEYA_MAIL *mailinfo);

// =================================================================
// SodateyaZiisannCheck
// 概要  : 育て屋じいさんの状態取得
// 引数  : sodateya
// 戻り値: u8	0:なし	1:タマゴあり	2:1匹預けてる	3:2匹預けてる
// =================================================================
extern u8 SodateyaZiisannCheck( SODATEYA_WORK *sodateya );

// =================================================================
// SodateyaNameSet
// 概要  : 育て屋に預けているポケモン名取得
// 引数  : sodateya
// 戻り値: none
// =================================================================
extern void SodateyaNameSet(SODATEYA_WORK *sodateya, WORDSET *wordset);

// =================================================================
// SodateyaListNameSet
// 概要  : 育て屋に預けているポケモン名,性別、レベル取得
// 引数  : sodateya
// 戻り値: none
// =================================================================
extern void SodateyaListNameSet(SODATEYA_WORK *sodateya,u32 buf_id,u32 buf2_id,u32 buf3_id,u8 no,WORDSET *wordset);

// =================================================================
/**
 * @brief 育ててるポケモンの名前とレベル差の文字列をセット
 * @param  sp 育て屋ワーク
 * @retval  none
 */
// =================================================================
extern u8 SodatePokeLevelSet( SODATEYA_WORK *sodateya, int pos, WORDSET *wordset );

extern u16 PokeHikitoriSub(POKEPARTY *party, WORDSET *wordset, SODATEYA_WORK *sodateya,u8 no);
extern int GetSinkaPokeLevel(POKEMON_PASO_PARAM *ppp, u32 walk);
extern int GetSodatePokeLevel(SODATEYA_POKE *sp);
extern int GetSodatePokeLevelDirect(SODATEYA_POKE *sp);
extern u8  SodatePokeLevelSetSub(SODATEYA_POKE *sp, WORDSET *wordset);
extern int PokehikitoriRyoukinOne(SODATEYA_POKE *sp, WORDSET *wordset );


//------------------------------------------------------------------
/**
 * 任意のポケモンパラメータから卵相性レベルを算出
 *
 * @param   ppp		ポケモン２体分の POKEMON_PASO_PARAM* 型配列
 *
 * @retval  u32		3（相性最低）～ 0（相性最高）
 */
//------------------------------------------------------------------
extern u32 Sodateya_GetAffinityLevel( POKEMON_PASO_PARAM** ppp );

//------------------------------------------------------------------
/**
 * 任意のポケモンパラメータから卵相性レベルを算出(簡易版)
 *
 * 引数  : sodateya
 *
 * @retval  u32		3（相性最低）～ 0（相性最高）
 */
//------------------------------------------------------------------
extern u32 SodateyaGetAffinity(SODATEYA_WORK *sodateya); 

//------------------------------------------------------------------
/**
 * 任意のポケモンパラメータから卵相性レベルを算出
 *
 * @param   percentage		確率（百分率）
 *
 * @retval  u8		3（相性最低）～ 0（相性最高）
 */
//------------------------------------------------------------------
extern u8 GetAffinityLevel( u32 percentage );

// =================================================================
/**
 * @brief PokeHikitoriRyoukinのサブルーチン
 * @param  none
 * @retval  u16 育てた料金
 */
// =================================================================
extern int PokeHikitoriRyoukinSub(SODATEYA_WORK *sodateya, u8 no, WORDSET *wordset);

// =================================================================
/**
 * @brief ポケモンリストで選択したポケモンの名前をセットする
 * @param  none
 * @retval  monsnoを返す
 */
// =================================================================
extern u16	SodateyaAzukeName( POKEPARTY *party, int pos, WORDSET *wordset );

// =================================================================
/**
 * @brief タマゴを消す
 * @param  none
 * @retval  none
 */
// =================================================================
extern void DelSodateyaTamagoSub(SODATEYA_WORK *sodateya);

#endif 
