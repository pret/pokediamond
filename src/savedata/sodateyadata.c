//============================================================================================
/**
 * @file	sodateyadata.c
 * @brief	図鑑状態アクセス用ソース
 * @author	mori GAME FREAK inc.
 * @date	2005.12.21
 */
//============================================================================================

#include "savedata/savedata_def.h"	//SAVEDATA参照のため

#include "common.h"

#include "system/gamedata.h"
#include "savedata/mail.h"

#include "savedata/savedata.h"

#include "poketool/poke_tool.h"
#include "poketool/poke_tool_def.h"
#include "savedata/sodateyadata.h"

#include "poketool/monsno.h"

//============================================================================================
//============================================================================================

//----------------------------------------------------------
/**
 * @brief	育て屋データ型定義
 */
//----------------------------------------------------------

// 通信メール
struct SIO_MAIL_DATA{									//レコードコーナー対応メール構造体
	MAIL_DATA	Mail;							//メールデータ
	STRCODE oyaname[PERSON_NAME_SIZE+1];		//メールの持ち主の名前
	STRCODE pokename[MONS_NAME_SIZE+1];		//メールのついてたポケモンの名前
	u8 bLang:4;
	u8 bLangPoke:4;
};

// 育て屋ポケモン一体分
struct SODATEYA_POKE{
	POKEMON_PASO_PARAM	Poke;					///<預けられてるポケモン
	SIO_MAIL_DATA		Mail;                   ///<レコードコーナー用メール構造体
	u32					WalkCount;              ///<歩数カウント
};

// 育て屋ワーク
struct SODATEYA_WORK{
	SODATEYA_POKE		SodatePoke[SODATEYA_POKE_MAX];			///<育て屋ポケモンワーク
	u32					Egg;					///<タマゴ(0=無し 0以外=有り=乱数のタネ
	u8					EggCount;				///<タマゴ孵化カウント
};




//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	育て屋データ用ワークのサイズ取得
 * @return	int		ZUKAN_WORKのサイズ
 */
//----------------------------------------------------------
int SodateyaWork_GetWorkSize(void)
{
	return sizeof(SODATEYA_WORK);
}
//----------------------------------------------------------
/**
 * @brief	育て屋データ用ワークの生成処理
 * @param	heapID		使用するヒープの指定
 * @return	ZUKAN_WORK	生成したSODATEAYA_WORKへのポインタ
 */
//----------------------------------------------------------
SODATEYA_WORK * SodateyaWork_AllocWork(u32 heapID)
{
	SODATEYA_WORK * sw;
	sw = sys_AllocMemory(heapID, sizeof(SODATEYA_WORK));
	SodateyaWork_Init(sw);
	return sw;
}

//----------------------------------------------------------
/**
 * @brief	育て屋データ用ワークのコピー
 * @param	from	コピー元ZUKAN_WORKへのポインタ
 * @param	to		コピー先ZUKAN_WORKへのポインタ
 */
//----------------------------------------------------------
void SodateyaWork_Copy(const SODATEYA_WORK * from, SODATEYA_WORK * to)
{
	MI_CpuCopy8(from, to, sizeof(SODATEYA_WORK));
}

//============================================================================================
//
//				内部関数
//
//============================================================================================

//============================================================================================
//
//			育て屋データ情報操作用の外部公開関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief		育て屋ワークの初期化
 * @param	zw	育て屋ワークへのポインタ
 */
//----------------------------------------------------------
void SodateyaWork_Init(SODATEYA_WORK * sw)
{
	memset(sw, 0, sizeof(SODATEYA_WORK));

	PokePasoParaInit(&sw->SodatePoke[0].Poke);
	PokePasoParaInit(&sw->SodatePoke[1].Poke);

	sw->Egg      = 0;
	sw->EggCount = 0;
}


//==============================================================================
/**
 * 預けられているPOKE_PASO_PARAMのポインタを返す
 *
 * @param   sw		育て屋ワークへのポインタ
 *
 * @retval  int		預けているポケモンの数
 */
//==============================================================================
SODATEYA_POKE *SodateyaWork_GetSodateyaPokePointer( SODATEYA_WORK *sw, int no )
{
	return &(sw->SodatePoke[no]);
}

//==============================================================================
/**
 * 預けられているPOKE_PASO_PARAMのポインタを返す
 *
 * @param   sw		育て屋ワークへのポインタ
 *
 * @retval  int		預けているポケモンの数
 */
//==============================================================================
POKEMON_PASO_PARAM *SodateyaPoke_GetPokePasoPointer( SODATEYA_POKE *sp )
{
	return &(sp->Poke);
}


SIO_MAIL_DATA *SodateyaPoke_GetSioMailPointer( SODATEYA_POKE *sp )
{
	return &(sp->Mail);
}

//==============================================================================
/**
 * ポケモンを預けて何歩目かの取得
 *
 * @param   sw		
 * @param   no		
 *
 * @retval  int		
 */
//==============================================================================
u32 SodateyaPoke_GetWalkCount( const SODATEYA_POKE *sp )
{
	return sp->WalkCount;
}




//==============================================================================
/**
 * 育て屋ポケデータから通信用メールデータポインタを取得する
 *
 * @param   mail		
 *
 * @retval  MAIL_DATA *		
 */
//==============================================================================
MAIL_DATA *SodateyaMail_GetMailPointer( SIO_MAIL_DATA *mail )
{
	return &(mail->Mail);
}

//==============================================================================
/**
 * 通信用メールデータの中から名前文字列を取得する
 *
 * @param   mail		
 * @param   flag		SIOMAIL_FLAG_OYA(親名）かSIOMAIL_FLAG_POKE(ポケモン名）
 *
 * @retval  STRCODE *		
 */
//==============================================================================
STRCODE *SodateyaMail_GetNamePointer( SIO_MAIL_DATA *mail, int flag )
{
	if( flag == SIOMAIL_FLAG_OYA ){
		return mail->oyaname;
	}
	// SIOMAIL_FLAG_POKE
	return mail->pokename;
}

//==============================================================================
/**
 * 育て屋メールの中にある名前の国コードを取得する
 *
 * @param   mail		
 * @param   flag		SIOMAIL_FLAG_OYA(親名）かSIOMAIL_FLAG_POKE(ポケモン名）
 *
 * @retval  int		
 */
//==============================================================================
int SodateyaMail_GetLanguage( SIO_MAIL_DATA *mail, int flag )
{
	if( flag == SIOMAIL_FLAG_OYA ){
		return mail->bLang;
	}
	// SIOMAIL_FLAG_POKE
	return mail->bLangPoke;
	
}

//==============================================================================
/**
 * タマゴが生まれているかの取得
 *
 * @param   sw		
 *
 * @retval  int		
 */
//==============================================================================
int SodateyaWork_GetEggFlag( const SODATEYA_WORK *sw )
{
	return sw->Egg;
}

//==============================================================================
/**
 * 卵孵化歩数の取得
 *
 * @param   sw		
 *
 * @retval  int		
 */
//==============================================================================
int SodateyaWork_GetEggCount( const SODATEYA_WORK *sw )
{
	return sw->EggCount;
}


//==============================================================================
//==============================================================================
//==============================================================================
//
// 設定関数群
//
//==============================================================================



//==============================================================================
/**
 * POKE_PASO_PARAMをコピーする
 *
 * @param   sw		育て屋ワークへのポインタ
 *
 * @retval  int		預けているポケモンの数
 */
//==============================================================================
void SodateyaWork_CopyPokePasoParam( SODATEYA_WORK *sw, const POKEMON_PARAM *pp, int no )
{
	sw->SodatePoke[no].Poke = pp->ppp;


//	memcpy(&(sw->SodatePoke[no].Poke), &(pp->ppp), PokemonPasoParamSizeGet());
}

//==============================================================================
/**
 * ポケモンを預けて何歩目か設定
 *
 * @param   sw		
 * @param   no		
 *
 * @retval  int		
 */
//==============================================================================
void SodateyaPoke_SetWalkCount( SODATEYA_POKE *sp, int num )
{
	sp->WalkCount = num;
}

//==============================================================================
/**
 * 歩数カウント（経験地）を足す
 *
 * @param   sp		
 * @param   num		
 *
 * @retval  none		
 */
//==============================================================================
void SodateyaPoke_AddWalkCount( SODATEYA_POKE *sp, int num )
{
	sp->WalkCount += num;
}


//==============================================================================
/**
 * タマゴが生まれているか設定
 *
 * @param   sw		
 *
 * @retval  int		
 */
//==============================================================================
void SodateyaWork_SetEggFlag( SODATEYA_WORK *sw, int Flag)
{
	sw->Egg = Flag;
}

//==============================================================================
/**
 * 卵孵化歩数の設定
 *
 * @param   sw		
 *
 * @retval  int		
 */
//==============================================================================
void SodateyaWork_SetEggCount( SODATEYA_WORK *sw, int Count )
{
	sw->EggCount = Count;
}


//==============================================================================
/**
 * @brief   育て屋に預けられているポケモンに違う国のポケモンがいるか？
 *
 * @param   sw		
 *
 * @retval  BOOL	TRUE:違う国ポケモンが預けてある
 */
//==============================================================================
BOOL  SodateyaWork_GetRareFlag( SODATEYA_WORK *sw )
{
	int country1, country2;
	country1 = PokePasoParaGet( &sw->SodatePoke[0].Poke, ID_PARA_country_code, NULL);
	country2 = PokePasoParaGet( &sw->SodatePoke[1].Poke, ID_PARA_country_code, NULL);

	// その２匹は違う言語コードのポケモンか？
	if(country1!=country2){
		return TRUE;
	}
	
	return FALSE;
}

//==============================================================================
/**
 * @brief   育て屋内のポケモン情報をコピー
 *
 * @param   des		
 * @param   src		
 *
 * @retval  none		
 */
//==============================================================================
void SodateyaPoke_Copy( SODATEYA_POKE *des, const SODATEYA_POKE *src)
{
	*des = *src;
}



// =================================================================
/**
 * @brief 通信メール構造体初期化
 * @param  smd
 * @retval  none
 */
// =================================================================
void SioMailDataInit( SIO_MAIL_DATA	*smd )
{
	int i;
	
	for(i=0;i<PERSON_NAME_SIZE+EOM_SIZE;i++) {
		smd->oyaname[i] = 0;						//親の名前初期化
	}
	for(i=0;i<MONS_NAME_SIZE+EOM_SIZE;i++){	
		smd->pokename[i] = 0;						//ポケモンの名前初期化
	}
	smd->oyaname[0]  = EOM_;
	smd->pokename[0] = EOM_;

//	MailDataInit(&smd->Mail);						//メールデータ


}

//--------------------------------------------------------------------------
/**
 * 育て屋ポケモンデータ初期化
 *
 * @param   poke		
 *
 * @retval  none		
 *
 *
 */
//--------------------------------------------------------------------------
void SodateyaPoke_Init(SODATEYA_POKE *poke)
{

	PokePasoParaInit(&poke->Poke);
	poke->WalkCount = 0;
	SioMailDataInit(&poke->Mail);
	
}


//============================================================================================
//
//	セーブデータ取得のための関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	自分状態データへのポインタ取得
 * @param	sv			セーブデータ保持ワークへのポインタ
 * @return	ZUKAN_WORK	ずかんワークへのポインタ
 */
//----------------------------------------------------------
SODATEYA_WORK * SaveData_GetSodateyaWork(SAVEDATA * sv)
{
	SODATEYA_WORK * sw;
	sw = SaveData_Get(sv, GMDATA_ID_SODATEYA);
	return sw;
}

//============================================================================================
//============================================================================================



