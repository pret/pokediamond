//============================================================================================
/**
 * @file	namein.h
 * @bfief	名前入力画面処理
 * @author	Akito Mori
 * @date	05.10.05
 */
//============================================================================================
#ifndef _NAMEIN_H_
#define _NAMEIN_H_

#include "gflib/strbuf.h"
#include "poketool/boxdata.h"
#include "savedata/config.h"

//============================================================================================
//	定数定義
//============================================================================================

// 名前入力モード
enum {
	NAMEIN_MYNAME = 0,	// 自分の名前
	NAMEIN_POKEMON,		// ポケモンの名前
	NAMEIN_BOX,			// ボックスの名前
	NAMEIN_RIVALNAME,	// ライバルネーム
	NAMEIN_FRIENDCODE,	// ともだちコード
	NAMEIN_RANDOMGROUP, // 乱数の種グループの名前
	NAMEIN_STONE,		// 石碑(配布）
	NAMEIN_FRIENDNAME,  // WIFIともだち手帳に書き込むともだちの名前
};


// ポケモン名前入力の長さ
#if (PM_LANG==LANG_JAPAN)
#define NAMEIN_POKEMON_LENGTH	(  5 )
#else
#define NAMEIN_POKEMON_LENGTH	( 10 )
#endif

// トレーナー名入力の長さ
#if (PM_LANG==LANG_JAPAN)
#define NAMEIN_PERSON_LENGTH	(  5 )
#else
#define NAMEIN_PERSON_LENGTH	( 7 )
#endif


// グループ名入力の長さ
#if (PM_LANG==LANG_JAPAN)
#define NAMEIN_GROUP_LENGTH		(  5 )
#else
#define NAMEIN_GROUP_LENGTH		( 7 )
#endif





#define STRBUF_ENABLE_MAGICNUMBER	(0x12345678)


extern const PROC_DATA NameInProcData;	// プロセス定義データ


typedef struct NAMEIN_WORK NAMEIN_WORK;	// ポインタ参照だけできる名前入力ワーク構造体

// 名前入力呼び出し時に必要なパラメータの構造体
// NAMEIN_PARAM *NameIn_ParamAllocMake(int HeapId, int mode, int info, int wordmax)
// を呼び出して作成する。
// 隠すかも
typedef struct{
	int mode;		// 入力モード(enum参照）
	int info;		// 入力モードとして男主人公・女主人公、ポケモンの開発NOなど
	int form;		// 入力モードがポケモンの時に形状値を受け取る
	int wordmax;	// 入力文字最大数
	int sex;		// ポケモンの性別(PARA_MALE=0...PARA_FEMALE=1...PARA_UNK=2(性別なし))


	int cancel;		// 名前入力が終了した時に反映されるフラグ。
					// 入力文字が０文字だった。もしくは最初と同じだった場合はこのフラグが立つ。

	STRBUF *strbuf; // このSTRBUFには２つの意味が存在する。
					// １つは名前入力画面からデータを受け取るワークであること。名前入力が終わったらここからコピーする
					// もう１つは、名前入力に行くときにここに文字列を格納しておくと,
					// 名前入力画面はその文字列を表示しながら開始する。引数としても機能する

	u16 str[20];	// この配列にも結果は返ってきます。（20に意味はありません）


	// --------ポケモン捕獲でボックス転送になった時に必要-------------
	
	int get_msg_id; 	// ポケモン捕獲の時にBOX転送が発生した時のメッセージIDが入る
	BOX_DATA  *boxdata;	// ポケモン捕獲の時にBOX転送が発生した時に、BOXの名前を取得するために必要
	CONFIG    *config;  // コンフィグ構造体

}NAMEIN_PARAM;

//==============================================================================
/**
 * 外部から名前入力初期化パラメーターをもらい引数ワークを作って返す
 *
 * @param   HeapId		ワークを作成するHEAPIDを指定（自分でFreeする必要があります）
 * @param   mode		名前入力モード（enumから選択）
 * @param   info		男・女(PM_MALE,PM_FEMALE)、ポケモンの開発NOなどを格納、BOXは0でよい
 * @param   wordmax		入力文字最大数
 *
 * @retval  NAMEIN_PARAM *	このポインタをNameInInitに渡す
 */
//==============================================================================
extern NAMEIN_PARAM* NameIn_ParamAllocMake(int HeapId, int mode, int info, int wordmax, CONFIG *config);

//==============================================================================
/**
 * 名前入力パラメーター削除
 * 名前入力終了後に参照し終わった後にこの関数を呼び出して解放してください。
 * 
 * @param   param			
 *
 * @retval  extern void		
 */
//==============================================================================
extern void NameIn_ParamDelete(NAMEIN_PARAM *param);

#endif