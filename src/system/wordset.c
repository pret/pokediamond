//============================================================================================
/**
 * @file	wordset.c
 * @brief	単語モジュール処理
 * @author	taya
 * @date	2005.09.28
 */
//============================================================================================
#include "common.h"

#include "gflib\msg_print.h"
#include "gflib\fntsys.h"
#include "gflib\strbuf_family.h"
#include "system\gamedata.h"
#include "system\msgdata.h"
#include "system\pm_str.h"
#include "system\placename.h"
#include "application\wifi_country.h"
#include "savedata\mystatus.h"
#include "savedata\randomgroup.h"
#include "savedata\misc.h"
#include "msgdata\msg_sodateya.h"
#include "msgdata\msg_common_scr.h"
#include "msgdata\msg_supportname.h"

#include "battle\battle_common.h"

#include "msgdata\msg.naix"
#include "system\wordset.h"


/*----------------------------------*/
/** 文法性                          */
/*----------------------------------*/
enum {
	WORDSET_GRAMMER_NONE,		///< 使用しない
	WORDSET_GRAMMER_MALE,		///< 男性
	WORDSET_GRAMMER_FEMALE,		///< 女性
	WORDSET_GRAMMER_NEUTRAL,	///< 中性
};


/*----------------------------------*/
/** 単語パラメータ                  */
/*----------------------------------*/
typedef struct {
	u8  def_article;		///< 定冠詞ＩＤ
	u8  indef_article;		///< 不定冠詞ＩＤ
	u8  preposition;		///< 前置詞ＩＤ
	u8  grammer : 7;		///< 文法性
	u8  form : 1;			///< 単数・複数（0 = 単数）
}WORDSET_PARAM;


typedef struct {
	WORDSET_PARAM	param;
	STRBUF*			str;
}WORD;



struct _WORDSET{

	u32			max;
	u32			heapID;
	WORD*		word;
	STRBUF*		tmpBuf;

};




//==============================================================
// Prototype
//==============================================================
static void RegisterWord( WORDSET* wordset, u32 bufID, const STRBUF* str, const WORDSET_PARAM* param );
static void InitParam(WORDSET_PARAM* param);
static void RegistWord(u32 idx, const STRBUF* str, const WORDSET_PARAM* param);

//======================================================================================================
// システム初期化・終了
//======================================================================================================

//------------------------------------------------------------------
/**
 * 単語セットモジュール作成
 *
 * @param   heapID			作成先ヒープＩＤ
 *
 * @retval  WORDSET*		単語セット
 */
//------------------------------------------------------------------
WORDSET*  WORDSET_Create( u32 heapID )
{
	return WORDSET_CreateEx( WORDSET_DEFAULT_SETNUM, WORDSET_DEFAULT_BUFLEN, heapID );
}

//------------------------------------------------------------------
/**
 * 単語セットモジュール作成（登録単語数・文字列長の指定版）
 *
 * @param   word_max		
 * @param   buflen			
 * @param   heapID			
 *
 * @retval  WORDSET*		
 */
//------------------------------------------------------------------
WORDSET* WORDSET_CreateEx( u32 word_max, u32 buflen, u32 heapID )
{
	WORDSET* wordset = NULL;
	u32 i;

	GF_ASSERT_RETURN(word_max, NULL);
	GF_ASSERT_RETURN(buflen, NULL);

	do {
		WORDSET* wordset = sys_AllocMemoryLo( heapID, sizeof(WORDSET) );
		if( wordset == NULL ){ break; }

		wordset->max = word_max;
		wordset->heapID = heapID;

		wordset->tmpBuf = STRBUF_Create(buflen, heapID );
		if( wordset->tmpBuf == NULL ){ break; }

		wordset->word = sys_AllocMemoryLo( heapID, sizeof(WORD)*word_max );
		if( wordset->word == NULL ){ break; }

		for(i=0; i<word_max; i++)
		{
			InitParam(&(wordset->word[i].param));
			wordset->word[i].str = STRBUF_Create( buflen, heapID );
			if( wordset->word[i].str == NULL ){
				break;
			}
		}

		if( i == word_max )
		{
			return wordset;
		}

	}while(0);

	if( wordset )
	{
		WORDSET_Delete(wordset);
	}
	return NULL;
}

//------------------------------------------------------------------
/**
 * 単語セット破棄
 *
 * @param   wordset		
 *
 */
//------------------------------------------------------------------
void WORDSET_Delete( WORDSET* wordset )
{
	u32 i;

	GF_ASSERT(wordset->max);

	if( wordset->word )
	{
		for(i=0; i<wordset->max; i++)
		{
			if( wordset->word[i].str )
			{
				STRBUF_Delete( wordset->word[i].str );
			}
			else
			{
				break;
			}
		}
		sys_FreeMemoryEz(wordset->word);
	}

	if( wordset->tmpBuf )
	{
		STRBUF_Delete(wordset->tmpBuf);
	}

	wordset->max = 0;
	sys_FreeMemoryEz(wordset);
}


//------------------------------------------------------------------
/**
 * 単語パラメータ初期化
 *
 * @param   param		パラメータ構造体へのポインタ
 *
 */
//------------------------------------------------------------------
static void InitParam(WORDSET_PARAM* param)
{
	// 現状なにもしていない
}

//======================================================================================================
// 単語セットモジュールに各種単語を登録する
//======================================================================================================

//------------------------------------------------------------------
/**
 * 単語文字列＆パラメータを指定バッファに登録
 *
 * @param   wordset		単語セットモジュール
 * @param   bufID		バッファＩＤ
 * @param   str			文字列
 * @param   param		文字列に付随するパラメータ
 *
 */
//------------------------------------------------------------------
static void RegisterWord( WORDSET* wordset, u32 bufID, const STRBUF* str, const WORDSET_PARAM* param )
{
	GF_ASSERT_MSG( bufID < wordset->max, "bufID=%d, wordmax=%d", bufID, wordset->max );

	if( bufID < wordset->max )
	{
		if( param != NULL )
		{
			wordset->word[bufID].param = *param;
		}
		STRBUF_Copy( wordset->word[bufID].str, str );
	}
}



//------------------------------------------------------------------
/**
 * 任意文字列をパラメータ付きで登録
 *
 * @param   wordset			単語セット
 * @param   bufID			バッファID
 * @param   word			文字列
 * @param   sex				性別コード
 * @param	singular_flag	単／複（TRUEで単数）
 * @param   lang			言語コード
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterWord( WORDSET* wordset, u32 bufID, const STRBUF* word, u32 sex, BOOL singular_flag, u32 lang )
{
	RegisterWord( wordset, bufID, word, NULL );
}


//------------------------------------------------------------------
/**
 * プレイヤー名を登録
 *
 * @param   wordset		単語セットオブジェクト
 * @param   bufID		バッファID
 * @param   status		
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPlayerName( WORDSET* wordset, u32 bufID, const MYSTATUS* status )
{
	const STRCODE * name;
	name = MyStatus_GetMyName( status );

	STRBUF_SetStringCode( wordset->tmpBuf, name );

	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
}

//------------------------------------------------------------------
/**
 * ライバル名を登録
 *
 * @param   wordset		単語セットモジュール
 * @param   bufID			バッファID
 * @param   savedata		セーブデータへのポインタ
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterRivalName( WORDSET* wordset,  u32 bufID, const SAVEDATA * savedata )
{
#if 0
	static const STRCODE name[] = {
		PA_, bou_, RU_, EOM_,
	};

	// [[[ 今は固定名をコピーしているだけ。いずれトレーナー情報を参照していろいろやる。
	STRBUF_SetStringCode( wordset->tmpBuf, name );
#endif
	const STRCODE * rivalname = MISC_GetRivalName(SaveData_GetMiscReadOnly(savedata));
	STRBUF_SetStringCode( wordset->tmpBuf, rivalname );

	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
}

//------------------------------------------------------------------
/**
 * サポートキャラ名を指定バッファに登録
 *
 * @param   bufID			バッファID
 * @param   savedata		セーブデータへのポインタ
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterSupportName( WORDSET* wordset, u32 bufID, const SAVEDATA * savedata )
{
	const MYSTATUS*  myStatus = SaveData_GetMyStatus( (SAVEDATA*)savedata );

	MSGDATA_MANAGER* man;

	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_supportname_dat, wordset->heapID );

	if( MyStatus_GetMySex( myStatus ) == PM_MALE )
	{
		MSGMAN_GetString( man, support_name_female, wordset->tmpBuf );
	}
	else
	{
		MSGMAN_GetString( man, support_name_male, wordset->tmpBuf );
	}

	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
	MSGMAN_Delete(man);
}
//------------------------------------------------------------------
/**
 * 石碑の名前を指定バッファに登録
 *
 * @param	wordset	
 * @param   bufID			バッファID
 * @param   savedata		セーブデータへのポインタ
 */
//------------------------------------------------------------------
void WORDSET_RegisterMonumentName( WORDSET* wordset, u32 bufID, const SAVEDATA * savedata )
{
	const MISC * misc = SaveData_GetMiscReadOnly( savedata );
	STRBUF_SetStringCode( wordset->tmpBuf, MISC_GetMonumentName( misc ) );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
}

//------------------------------------------------------------------
/**
 * 指定バッファにポケモン名を登録
 *
 * @param   bufID		バッファID
 * @param   ppp		ポケモンパラメータ
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPokeMonsName( WORDSET* wordset, u32 bufID, POKEMON_PASO_PARAM* ppp )
{
	MSGDATA_MANAGER* man;
	u32 monsno;

	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_monsname_dat, wordset->heapID );

	// [[[ここでポケモンの性別等をチェックできる]]]
	monsno = PokePasoParaGet( ppp, ID_PARA_monsno, NULL );
	MSGMAN_GetString( man, monsno, wordset->tmpBuf );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);

	MSGMAN_Delete(man);
}

//------------------------------------------------------------------
/**
 * 指定バッファにポケモンのニックネームを登録
 *
 * @param   bufID		バッファID
 * @param   ppp		ポケモンパラメータ
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPokeNickName( WORDSET* wordset, u32 bufID, POKEMON_PASO_PARAM* ppp )
{
	// [[[ここでポケモンの性別等をチェックできる]]]
	PokePasoParaGet( ppp, ID_PARA_nickname_buf, wordset->tmpBuf );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
}

//------------------------------------------------------------------
/**
 * 指定バッファにポケモンの親名を登録
 *
 * @param   bufID		バッファID
 * @param   ppp		ポケモンパラメータ
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPokeOyaName( WORDSET* wordset,  u32 bufID, POKEMON_PASO_PARAM* ppp )
{
	// [[[ここで親の性別もチェックできる]]]
	PokePasoParaGet( ppp, ID_PARA_oyaname_buf, wordset->tmpBuf );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);

}

//------------------------------------------------------------------
/**
 * 指定バッファに数字を登録
 *
 * @param   bufID		バッファID
 * @param   number		数値
 * @param   keta		桁数
 * @param   dispType	整形タイプ
 * @param   codeType	文字コードタイプ
 *
 * dispType :  NUMBER_DISPTYPE_LEFT    左詰め
 *             NUMBER_DISPTYPE_SPACE   右詰め（スペース埋め）
 *             NUMBER_DISPTYPE_ZERO    右詰め（ゼロ埋め）
 *
 *
 * codeType :  NUMBER_CODETYPE_DEFAULT  ローカライズ時のデフォルト幅（日本＝全角幅／海外＝半角幅）になる
 *             NUMBER_CODETYPE_ZENKAKU  全角幅指定
 *             NUMBER_CODETYPE_HANKAKU  半角幅指定
 */
//------------------------------------------------------------------
void WORDSET_RegisterNumber( WORDSET* wordset, u32 bufID, s32 number, u32 keta, NUMBER_DISPTYPE dispType, NUMBER_CODETYPE codeType )
{
	STRBUF_SetNumber( wordset->tmpBuf, number, keta, dispType, codeType );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
}

//------------------------------------------------------------------
/**
 * 指定バッファにワザ名を登録
 *
 * @param   bufID			バッファID
 * @param   wazaID			ワザID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterWazaName( WORDSET* wordset, u32 bufID, u32 wazaID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_wazaname_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString(man, wazaID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファにリボン名を登録
 *
 * @param   bufID			バッファID
 * @param   ribbonID		リボンID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterRibbonName( WORDSET* wordset, u32 bufID, u32 ribbonID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_ribbon_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString(man, ribbonID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファにポケモンのとくせい名を登録
 *
 * @param   bufID			バッファID
 * @param   tokuseiID		とくせいID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterTokuseiName( WORDSET* wordset, u32 bufID, u32 tokuseiID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_tokusei_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString(man, tokuseiID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファにポケモンのせいかくを登録
 *
 * @param   bufID			バッファID
 * @param   seikakuID		せいかくID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterSeikaku( WORDSET * wordset, u32 bufID, u32 seikakuID )
{
	MSGDATA_MANAGER * man;
	
	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_chr_dat, wordset->heapID );
	
	MSGMAN_GetString( man, seikakuID, wordset->tmpBuf );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );

	MSGMAN_Delete(man);
}

//------------------------------------------------------------------
/**
 * 指定バッファにアイテム名を登録
 *
 * @param   bufID			バッファID
 * @param   itemID			アイテムID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterItemName( WORDSET* wordset, u32 bufID, u32 itemID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_itemname_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, itemID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファにアイテムを入れるポケット名を登録
 *
 * @param   bufID			バッファID
 * @param   wazaID			ポケットID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterItemPocketName( WORDSET* wordset, u32 bufID, u32 pocketID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_itempocket_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, pocketID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファにアイテムを入れるポケット名（アイコン付き）を登録
 *
 * @param   bufID			バッファID
 * @param   wazaID			ポケットID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterItemPocketWithIcon( WORDSET* wordset, u32 bufID, u32 pocketID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_itempocket_icon_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, pocketID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}


//------------------------------------------------------------------
/**
 * 指定バッファにポケモン（ワザ）タイプ名を登録
 *
 * @param   bufID			バッファID
 * @param   typeID			タイプID
 * @param   msgManager		タイプ名GMMを操作するマネージャポインタ
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPokeTypeName( WORDSET* wordset, u32 bufID, u32 typeID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_typename_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, typeID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}
//------------------------------------------------------------------
/**
 * 指定バッファにポケモンステータス名を登録
 *
 * @param   bufID			バッファID
 * @param   statusID		ステータスID
 * @param   msgManager		ステータス名GMMを操作するマネージャポインタ
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPokeStatusName( WORDSET* wordset, u32 bufID, u32 statusID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_status_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, statusID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}
//------------------------------------------------------------------
/**
 * 指定バッファに状態異常名を登録
 *
 * @param   bufID			バッファID
 * @param   conditionID		状態異常ID
 * @param   msgManager		状態異常名GMMを操作するマネージャポインタ
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterBadConditionName( WORDSET* wordset, u32 bufID, u32 conditionID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_condition_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, conditionID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファに木の実の味名を登録
 *
 * @param   bufID			バッファID
 * @param   tasteID			木の実の味ID
 * @param   msgManager		木の実の味名GMMを操作するマネージャポインタ
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterSeedTasteName( WORDSET* wordset, u32 bufID, u32 tasteID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_taste_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, tasteID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファに地名を登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		地名ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPlaceName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_place_name_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファにポケッチアプリ名を登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		アプリ名ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPoketchAppName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_poketch_app_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファにトレーナー種別を登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		トレーナー種別ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterTrTypeName( WORDSET* wordset, u32 bufID, u32 strID )
{
	//poketool/tr_tool.hをインクルードして
	//TT_TrainerTypeSexGet(strID)とすることでトレーナーの性別が取得できます
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_trtype_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファにトレーナー種別を登録（戦闘専用）
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		トレーナー種別ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterTrTypeNameBattle( WORDSET* wordset, u32 bufID, TRAINER_DATA *tr_data )
{
	//poketool/tr_tool.hをインクルードして
	//TT_TrainerTypeSexGet(tr_data->tr_type)とすることでトレーナーの性別が取得できます
	
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_trtype_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, tr_data->tr_type, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファにトレーナー名を登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		トレーナー種別ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterTrainerName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_trname_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファにトレーナー名を登録（戦闘専用）
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		トレーナー種別ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterTrainerNameBattle( WORDSET* wordset, u32 bufID, TRAINER_DATA *tr_data )
{
	//poketool/tr_tool.hをインクルードして
	//TT_TrainerTypeSexGet(tr_data->tr_type)とすることでトレーナーの性別が取得できます

	STRBUF_SetStringCode( wordset->tmpBuf, &tr_data->name[0] );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
}

//------------------------------------------------------------------
/**
 * 指定バッファに地下アイテム（化石）名を登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		地下アイテム（化石）ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterUGItemName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_undergrounditem_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファに地下罠名を登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		地下わなID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterUGTrapName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_undergroundtrap_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファに審判名を登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		審判名ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterJudgeName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_cmsg_judge_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファにコンテストランク名を登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		ランクID(CAMSG_CONRANK_NORMAL, CAMSG_CONRANK_SUPER, 等)
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterContestRank( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_cmsg_acting_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * コンテストタイプ(コンテスト名称)にタイプ名を登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		タイプID(CAMSG_CONTYPE_STYLE, 等)
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterContestType( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_cmsg_acting_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファに秘密の質問を登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		秘密の質問ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterSecretQuestion( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_undersecretquestion_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファに秘密の質問の答えを登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		秘密の質問の答えID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterSecretAnswer( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_undersecretanswer_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファにグッズ名を登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		グッズ名ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterUGGoodsName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_undergroundgoods_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファにポケモン性別名を登録
 *
 * @param   bufID		バッファID
 * @param   sex			性別
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPokeMonsSex( WORDSET* wordset, u32 bufID, u8 sex)
{
	MSGDATA_MANAGER* man;

	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_common_scr_dat, wordset->heapID );

	switch(sex){
	case PARA_MALE:
		MSGMAN_GetString( man, msg_mons_sex_osu, wordset->tmpBuf );
		break;
	case PARA_FEMALE:
		MSGMAN_GetString( man, msg_mons_sex_mesu, wordset->tmpBuf );
		break;
	default:
		STRBUF_Clear( wordset->tmpBuf );
	}
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL);
	MSGMAN_Delete(man);

}

//------------------------------------------------------------------
/**
 * 指定バッファにボックスのトレイ名を登録
 *
 * @param   wordset		ワードセットオブジェクトポインタ
 * @param   bufID		バッファID
 * @param   boxData		ボックスデータポインタ
 * @param   u32         トレイナンバー
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterBoxTrayName( WORDSET* wordset, u32 bufID, const BOX_DATA* boxData, u32 trayNumber )
{
	BOXDAT_GetBoxName( boxData, trayNumber, wordset->tmpBuf );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
}

//------------------------------------------------------------------
/**
 * 指定バッファにジム名を登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		グッズ名ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterGymName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_gym_name_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファに時間帯を登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		グッズ名ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterTimeType( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_time_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファに国名を登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		国ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterCountryName( WORDSET* wordset, u32 bufID, u32 countryID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_wifi_place_msg_world_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, countryID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファに地域名を登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   countryID	国ID
 * @param   placeID		地域ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterLocalPlaceName( WORDSET* wordset, u32 bufID, u32 countryID, u32 placeID )
{
	u32  datID;

	datID = WIFI_COUNTRY_CountryCodeToPlaceMsgDataID(countryID);
	if( datID )
	{
		if( placeID )
		{
			MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, datID, wordset->heapID);
			if( man )
			{
				MSGMAN_GetString( man, placeID, wordset->tmpBuf );
				RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
				MSGMAN_Delete(man);
			}
		}
	}
}


//------------------------------------------------------------------
/**
 * 指定バッファに簡易会話単語を登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   word		簡易会話単語ナンバー
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPMSWord( WORDSET* wordset, u32 bufID, PMS_WORD word )
{
	PMSW_GetStr( word, wordset->tmpBuf );
	RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
}


//------------------------------------------------------------------
/**
 * 指定バッファにシール名を登録
 *
 * @param   wordset		ワードセットオブジェクト
 * @param   bufID		何番のバッファに登録するか
 * @param   strID		シール名ID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterSealName( WORDSET* wordset, u32 bufID, u32 strID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_bc_seal_name_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, strID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}
//------------------------------------------------------------------
/**
 * 指定バッファにポケモン捕獲場所名を登録
 *
 * @param   wordset			ワードセットオブジェクト
 * @param   bufID			何番のバッファに登録するか
 * @param   placeNumber		捕獲場所ナンバー
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPokeGetPlace( WORDSET* wordset, u32 bufID, u32 placeNumber )
{
	static const u16 placenameFileID[] = {
		NARC_msg_place_name_dat,
		NARC_msg_place_name_tokusyu_dat,
		NARC_msg_place_name_haihu_dat,
	};

	PLACENAME_TYPE type;
	int strID;
	MSGDATA_MANAGER* man;

	type = PlaceName_GetType( placeNumber );
	strID = PlaceName_GetIndex( placeNumber );

	man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, placenameFileID[type], wordset->heapID);
	if( man )
	{
		if( strID < MSGMAN_GetMessageCount(man) )
		{
			MSGMAN_GetString( man, strID, wordset->tmpBuf );
			RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
			MSGMAN_Delete( man );
		}
		else
		{
			MSGMAN_Delete( man );
			man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, placenameFileID[0], wordset->heapID);
			if( man )
			{
				MSGMAN_GetString( man, 0, wordset->tmpBuf );
				RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
				MSGMAN_Delete( man );
			}
		}
	}
}


//------------------------------------------------------------------
/**
 * 指定バッファにポルト名を登録
 *
 * @param   wordset			ワードセットオブジェクト
 * @param   bufID			何番のバッファに登録するか
 * @param   porutoID		ポルトID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterPorutoName( WORDSET* wordset, u32 bufID, u32 porutoID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_porutoname_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, porutoID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファにアクセサリ名（イメージクリップ）を登録
 *
 * @param   wordset			ワードセットオブジェクト
 * @param   bufID			何番のバッファに登録するか
 * @param   porutoID		アクセサリID
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterAccessoryName( WORDSET* wordset, u32 bufID, u32 acID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_imageclip_acce_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, acID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * 指定バッファにイメージクリップ背景の名前を登録
 *
 * @param   wordset		
 * @param   bufID		
 * @param   bgID		
 *
 */
//------------------------------------------------------------------
void WORDSET_RegisterImageClibBgName( WORDSET* wordset, u32 bufID, u32 bgID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_imageclip_bg_dat, wordset->heapID);
	if( man )
	{
		MSGMAN_GetString( man, bgID, wordset->tmpBuf );
		RegisterWord( wordset, bufID, wordset->tmpBuf, NULL );
		MSGMAN_Delete(man);
	}
}

//------------------------------------------------------------------
/**
 * @brief	グループ名・リーダー名の単語登録
 * @param	ws			WORDSETへのポインタ
 * @param	sv			セーブデータへのポインタ
 * @param	gid			グループ指定ID
 * @param	bufID		バッファ指定ID
 * @param	name_type	RANDOMGROUP_NAME_GROUP or RANDOMGROUP_NAME_LEADER
 */
//------------------------------------------------------------------
void WORDSET_RegisterGroupName(WORDSET * ws, SAVEDATA * sv, int gid, int bufID, int name_type)
{
	int sex, region_code;
	STRBUF * strbuf;
	RANDOM_GROUP * rg = SaveData_GetRandomGroup(sv);
	sex = RandomGroup_GetSex(rg, gid);
	region_code = RandomGroup_GetRegionCode(rg, gid);
	strbuf = STRBUF_Create(64, HEAPID_FIELD);	//バッファ長てきとー
	STRBUF_SetStringCode(strbuf, RandomGroup_GetNamePtr(rg, gid, name_type));
	WORDSET_RegisterWord(ws, bufID, strbuf, sex, TRUE, region_code);
	STRBUF_Delete(strbuf);
}


//======================================================================================================
// 文字列展開
//======================================================================================================

//------------------------------------------------------------------
/**
 * 登録された単語を使って文字列展開する
 *
 * @param   dst		展開先バッファ
 * @param   src		展開元文字列
 *
 */
//------------------------------------------------------------------
void WORDSET_ExpandStr( const WORDSET* wordset, STRBUF* dstbuf, const STRBUF* srcbuf )
{
	const STRCODE* src;
	STRCODE *dst;

	src = STRBUF_GetStringCodePointer(srcbuf);
	STRBUF_Clear( dstbuf );

	while( *src != EOM_ )
	{
		if( *src == _CTRL_TAG )
		{
			if( STRCODE_CheckWordSetTagType(src) )
			{
				u32 word_id;

				word_id = STRCODE_GetTagParam(src, 0);

				GF_ASSERT( word_id < wordset->max );

				// [[[海外版ではパラメータの解釈が必要]]]
				STRBUF_AddStr( dstbuf, wordset->word[ word_id ].str );
				src = STRCODE_SkipTag(src);
			}
			else
			{
				const STRCODE* p = src;

				src = STRCODE_SkipTag(src);
				while(p < src)
				{
					STRBUF_AddChar( dstbuf, *p++ );
				}
				
			}
		}
		else
		{
			STRBUF_AddChar( dstbuf, *src++ );
		}
	}
}




//======================================================================================================
// バッファクリア
//======================================================================================================

//------------------------------------------------------------------
/**
 * 内部バッファを全て空文字列でクリアする
 *
 * @param   wordset		WORDSETへのポインタ
 *
 */
//------------------------------------------------------------------
void WORDSET_ClearAllBuffer( WORDSET* wordset )
{
	u32 i;
	for(i=0; i<wordset->max; i++)
	{
		STRBUF_Clear( wordset->word[i].str );
	}
}




