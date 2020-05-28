#ifndef _AGB_ACCESS_H
#define _AGB_ACCESS_H

#include "pokeparam.h"
#include "pm_version.h"

#define SOFTTYPE_RS	0	// ルビー、サファイア
#define SOFTTYPE_FL	1	// ファイアレッド、リーフグリーン
#define SOFTTYPE_EM 2	// エメラルド

#if 0
#define LANGTYPE_JP 0
#define LANGTYPE_US 1
#define LANGTYPE_FR 2
#define LANGTYPE_GE 3
#define LANGTYPE_SP 4
#define LANGTYPE_IT 5
#else
#define LANGTYPE_JP LANG_JAPAN
#define LANGTYPE_US LANG_ENGLISH
#define LANGTYPE_FR LANG_FRANCE
#define LANGTYPE_GE LANG_GERMANY
#define LANGTYPE_SP LANG_SPAIN
#define LANGTYPE_IT LANG_ITALY
#endif

enum {
  CASTYPE_RUBY = 0,
  CASTYPE_SAPPHIRE,
  CASTYPE_GREEN,
  CASTYPE_RED,
  CASTYPE_EMERALD,
  CASTYPE_MAX
};


#define	SVLD_RET_NG			(0xff)		//セーブ結果（書き込み出来なかった）
#define	SVLD_RET_NULL		(0x0)		//セーブ結果（バックアップなし）
#define	SVLD_RET_OK			(0x1)		//セーブ結果（正常に終了）
#define	SVLD_RET_DESTROY	(0x2)		//セーブ結果（完全破壊：復帰不可能）
#define	SVLD_RET_FULL		(0x3)		//セーブ結果（これ以上書き込み出来ない）
#define	SVLD_RET_HARDERROR	(0x4)		//ハードエラー（基盤なし）
#define	SVLD_RET_ERROR		(0x5)		//読み込みに失敗　（電源をきって、カートリッジをしっかりさすことを促す）

#define	SVLD_HEADER_SIZE	(4+2+4+2)	//ヘッダサイズ
#define	SVLD_SECTOR_SIZE	(0x1000)	//セクタサイズ
#define	SVLD_DATA_SIZE		(SVLD_SECTOR_SIZE - SVLD_HEADER_SIZE)	//実データサイズ





typedef struct
{
	u32 buffer[SVLD_SECTOR_SIZE / 4];
	u8 MyData[SVLD_SECTOR_SIZE];
	u8 Fld[SVLD_SECTOR_SIZE*4];
	POKEBOX_SAVE_DATA pc_data;
} AGBPOKE_SAVEDATA;

#define AGBPOKE_BUFFERSIZE (sizeof(AGBPOKE_SAVEDATA)) 

enum
{
	AGBPOKE_ERROR_OK,
	AGBPOKE_ERROR_NOROM,
	AGBPOKE_ERROR_NOTPOKEMON,
	AGBPOKE_ERROR_NOFLASH,
	AGBPOKE_ERROR_READ,
	AGBPOKE_ERROR_NG,
	AGBPOKE_ERROR_DESTROY,
	AGBPOKE_ERROR_NULL,	
	AGBPOKE_ERROR_WRITE,
	AGBPOKE_ERROR_WRITING,
	AGBPOKE_ERROR_CONTINUE,	
	AGBPOKE_ERROR_LAST,
	AGBPOKE_ERROR_OTHER			
};

//==============================================================================
/**
 * agbpoke_*が呼び出される前に、この関数をコールしてください。
 * @param   buffer…バッファを渡す。必要な量はAGBPOKE_BUFFERSIZE
 * @retval  エラーコード
 */
//==============================================================================
extern int agbpoke_init( void *buffer );
extern void agbpoke_preinit(void);

//==============================================================================
/**
 * ささっているソフトのイニシャルコードを取得します。
 * @retval  TRUE…初期化成功　FALSE…初期化失敗
 */
//==============================================================================
extern u32 agbpoke_getInitialCode();

//==============================================================================
/**
 * ささっているソフトのゲーム種類を返します。
 * @retval  カセットのポケモンタイプ
 */
//==============================================================================
extern int agbpoke_getPokemonType();

//==============================================================================
/**
 * ささっているポケモンソフトの言語を返す。
 * @retval  カセットの言語
 */
//==============================================================================
extern int agbpoke_getPokemonLanguage();

//==============================================================================
/**
 * データをロードする。
 * @param   newsector…新しいセクターの番号が入ってくる(0か1)
 * @param   buffer   …SVLD_SECTOR_SIZE 必要
 * @retval  結果。
 */
//==============================================================================
extern int agbpoke_LoadDATA();

//==============================================================================
/**
 * パソコンデータへのポインタを取得する。
 * @param   newsector…新しいセクターの番号が入ってくる(0か1)
 * @param   buffer   …SVLD_SECTOR_SIZE 必要
 * @retval  結果。
 */
//==============================================================================
extern POKEBOX_SAVE_DATA *agbpoke_getPCdata();

//==============================================================================
/**
 * 図鑑をもっているか判定。
 * @retval  結果。
 */
//==============================================================================
extern BOOL gbapoke_hasZukan();

//==============================================================================
/**
 * ポケモンセンター内でセーブしているかどうか
 * @retval  結果。
 */
//==============================================================================
extern BOOL gbapoke_inPokemonCenter();

//==============================================================================
/**
 * データを非同期でセーブする。
 * @retval  結果。
 */
//==============================================================================
extern BOOL agbpoke_saveEdit_Async();
//==============================================================================
/**
 * データを非同期でセーブしたとき、終了したかをチェックする関数。
 * @retval  結果。
 */
//==============================================================================
extern int agbpoke_saveEdit_check();
extern int agbpoke_check_status(void);

//==============================================================================
/**
 * データをセーブする。AGBPOKE_ERROR_CONTINUE以外の値が返すまで呼び出して下さい。
 * @retval  結果。
 */
//==============================================================================
extern int agbpoke_saveEdit( );
extern void *agbpoke_GetMyDataPtr(void);

#endif
