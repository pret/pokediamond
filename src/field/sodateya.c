//===============================================================
//
//
//==============
/**
 * @file	sodateya.c
 * @brief	そだて屋・タマゴ処理
 * @author	Akito Mori
 * @date	05.12.10 
 *
 * Copyright (C) 2005 GAME FREAK inc.
*/
//=============================================================================


//現状でまだ存在していないモノ
//	EventFlagSet(FE_SODATE_TAMAGO);											//おじいちゃん移動フラグset
//				if(ksw->dadlist[i] == GetWazaNoItem(ITEM_WAZAMASIN01+w)){	//子供は技マシンでつけることができるなら
//					if(PokeWazaMachineCheck(p,w)){							// 技マシンで技を覚えるか
//		event = POS_EVENT_EGG;												// POS_EVENT_EGGという定義がない
//					ScriptParameter0 = i;									// タマゴが孵るときのデモへの指定方法がない
//				if(PokeParaGet( pp, ID_PARA_fusei_tamago_flag,NULL)){		//これはダメタマゴじゃないか？
//		PokePasoParaGet( ppp, ID_PARA_monsname, buf );						// 開発ＮＯの名前が取れない

//	zukanno = PokeMonsNo2ZukanNoGet(monsno);							//図鑑ＮＯへ変換
//	ZukanCheck(zukanno,Z_SEE_SET);										//図鑑見たフラグセット
//	ZukanCheck(zukanno,Z_GET_SET);										//図鑑ゲットフラグセット
//	mappos = GetNowWorldPos();											//孵化した場所を設定
//	PokePPMaxSet(&PokeParaMine[no]);									//PPを回復
//	SodateyaMsgPrint(bmpid,buf,12+11*7,y);

//#define  SODATEYA_DEBUG
#define SODATEYA_MAIN
//#define RARE_DEBUG		// コメントをはずすとタマゴが必ずレアになる

#include "common.h"
#include "gflib/strbuf.h"
#include "gflib/strbuf_family.h"
#include "gflib/calctool.h"
#include "system/wordset.h"
#include "system\msgdata.h"
#include "system\msgdata_util.h"
#include "fieldsys.h"
#include "system/fontproc.h"
#include "gflib/msg_print.h"
#include "poketool/poke_tool.h"
#include "itemtool/itemsym.h"
#include "poketool/monsno.h"
#include "battle/wazano_def.h"
#include "battle\tokusyu_def.h"
#include "poketool/pokeparty.h"
#include "savedata/savedata.h"
#include "savedata/mystatus.h"
#include "savedata/mail.h"
#include "savedata/record.h"
#include "savedata/perapvoice.h"
#include "itemtool/item.h"
#include "poketool/poke_memo.h"
#include "ev_time.h"

#include "system/gamedata.h"
#include "kowaza.h"
#include "savedata/sodateyadata.h"
#include "sodateya.h"

#include "msgdata/msg_sodateya.h"

#include "system/placename.h"
//#include "msgdata/msg_place_name.h"←レンジャーだけならいらないはず
#include "msgdata/msg_place_name_haihu.h"
#include "msgdata/msg_place_name_tokusyu.h" //←レンジャーだけならいらないはず


// =================================================================
// 定義
// =================================================================
#define WAZA_MACHINE_MAX 	(100)				///< 技マシンの数
#define	BIRTH_LEVEL			(1)					///< タマゴから生まれた時のポケモンのレベル
#define METAMON_NO			(MONSNO_METAMON)	///< メタモンの開発NO
#define HUKA_FIRST_NATUKIDO (120)				///< タマゴから生まれた時のなつき度
#define NON_ITEM			( 0 )
#define POKE_KOWAZA_MAX		( 16 )				///< 子技のマックス


// =================================================================
// extern
// =================================================================
extern s16 BoxTumeMineData();					///< 手持ちを詰める



// =================================================================
// プロトタイプ宣言
// =================================================================
void PokemonTamagoSet(POKEMON_PARAM *pp, u16 monsno, SODATEYA_WORK *sodateya, u32 id, u8 form_no);
void SioMailDataInit(SIO_MAIL_DATA	*smd);
static  u8 SodateyaPokeAffinity(SODATEYA_WORK	*sodateya);
static void	TamagoDemoMsgSet(u8 w_index, const void* msg,u8 x,u8 y,u8 wait);
static int GetGrowthSpeed( POKEPARTY *party );
static u8 CalcAffinity( POKEMON_PASO_PARAM** ppp );

void PokeMakeNidoranOsuTamago(SODATEYA_WORK *sodateya);
void DelSodateyaTamagoSub(SODATEYA_WORK *sodateya);
int PokeHikitoriRyoukinSub(SODATEYA_WORK *sodateya, u8 no, WORDSET *wordset);
u8 SodatePokeLevelSet( SODATEYA_WORK *sodateya, int pos, WORDSET *wordset );
u16	SodateyaAzukeName( POKEPARTY *party, int pos, WORDSET *wordset );
u8 SodateyaZiisannCheck( SODATEYA_WORK *sodateya );
void SodateyaNameSet(SODATEYA_WORK *sodateya, WORDSET *wordset);
static void PokeSodateSetOne( POKEPARTY *party, int pos, SODATEYA_POKE *sodate,  SAVEDATA *sv);
static int GetEggCountSpeed( FIELDSYS_WORK *fsys );


// =================================================================
// 文字定数定義
// =================================================================
//２ひきのなかは
//とってもよいようじゃ

//２ひきのなかは
//まずまずのようじゃ

//２ひきのなかは
//それほどよくないがなあ

//２ひきはおたがいに
//ちがうポケモンたちと
//あそんでおるがなあ

static const int AffinityMsg[]={		//相性文字列テーブル
	msg_sodateya_01,
	msg_sodateya_02,
	msg_sodateya_03,
	msg_sodateya_04,
};

//static const u8 level_msg[]		= {EXFONT1_,Lv__,EOM_};		//「LV」
//level_msgはgmmデータに取り込んだので消去MakeSodateLevelPut関数で使用する必要アリ


static POKEMON_PASO_PARAM *SodateyaWork_GetPokePasoPointer( SODATEYA_WORK *sodateya, int pos)
{
	
	return SodateyaPoke_GetPokePasoPointer( SodateyaWork_GetSodateyaPokePointer(sodateya, pos) );
}


static SODATEYA_WORK *debug_sodateya;
// =================================================================
/**
 * @brief 預けているポケモンの数を返す
 * @param  none
 * @retval  u8
 */
// =================================================================
u8 PokeAzukeruCheck( SODATEYA_WORK *sodateya )
{
	u8 result,i;
	POKEMON_PASO_PARAM *paso;
	
	result=0;
	for(i=0;i<SODATEYA_POKE_MAX;i++){		//預けられているポケモンの数をカウント
		paso = SodateyaPoke_GetPokePasoPointer( SodateyaWork_GetSodateyaPokePointer(sodateya, i) );
		if(PokePasoParaGet(paso,ID_PARA_monsno, NULL)!=0){
			result++;
		}
	}
	return result;
}


// =================================================================
/**
 * @brief 預けられるなら空いてる番号を返す
 * @param  none
 * @retval  s8	0,1=空いてる番号	-1=無し
 */
// =================================================================
int PokeAzukeruCheckGet(SODATEYA_WORK *sodateya)
{	
	u8 i;
	POKEMON_PASO_PARAM *para;

	debug_sodateya = sodateya;

	for(i=0;i<SODATEYA_POKE_MAX;i++){					//預けてない領域があった
		para = SodateyaPoke_GetPokePasoPointer( SodateyaWork_GetSodateyaPokePointer(sodateya, i) );
		if(PokePasoParaGet(para,ID_PARA_monsno,NULL)==0){
			return i;
		}
	}
	return -1;							//両方預けられてた
}


//------------------------------------------------------------------
/**
 * @brief   ポケモンの持っているアイテムはメールか
 *
 * @param   pp		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int  PokeMailCheck(POKEMON_PASO_PARAM *ppp)
{
	int item = PokePasoParaGet(ppp, ID_PARA_item, NULL);

	return ItemMailCheck( item );

}
//--------------pokemon_dp--------------

//--------------------------------------------------------------------------
/**
 * 育て屋ポケモンワークにポケモンを預ける(カントー・ナナシマ共通)
 *
 * @param   p		
 * @param   sodate		
 *
 * @retval  none		
 *
 *
 */
//--------------------------------------------------------------------------
static void PokeSodateSetOne( POKEPARTY *party, int pos, SODATEYA_POKE *sodate,  SAVEDATA *sv)
{
	int           mail;
	POKEMON_PARAM *pp = PokeParty_GetMemberPointer( party, pos);
	const STRCODE *myname;
	STRCODE       pokename[MONS_NAME_SIZE + 1];

	SIO_MAIL_DATA      *smd = SodateyaPoke_GetSioMailPointer( sodate );
	POKEMON_PASO_PARAM *ppp = SodateyaPoke_GetPokePasoPointer( sodate );

	MYSTATUS *mystatus = SaveData_GetMyStatus( sv );
	myname             = MyStatus_GetMyName( mystatus );
	PokeParaGet( pp , ID_PARA_nickname, pokename );

	// メールチェック
	if(PokeMailCheck(PPPPointerGet(pp))){
		PokeParaGet( pp, ID_PARA_mail_data, SodateyaMail_GetMailPointer( smd ) );
	}

	PokeCopyPPtoPPP( pp, ppp);
	SodateyaPoke_SetWalkCount(sodate, 0);	//歩数初期化
	PokeParty_Delete( party, pos );

	// てもちからペラップがいなくなったら声データを消去する
	if(PokeParty_PokemonCheck( party, MONSNO_PERAPPU )==0){
		PERAPVOICE *pv = SaveData_GetPerapVoice( sv );
		PERAPVOICE_ClearExistFlag( pv );
	}
	
//	OS_Printf("MAIL_DATA size = %d\n", sizeof(MAIL_DATA));
}


// =================================================================
/**
 * @brief ポケモンを預けるサブ
 * @param  p
 * @retval  none
 */
// =================================================================
void PokeSodateSet(POKEPARTY *party, int pos, SODATEYA_WORK *sodateya, SAVEDATA *sv)
{
	int work;
	RECORD *record = SaveData_GetRecord( sv );
		
	// 育て屋に預けた回数を＋１
	RECORD_Inc( record, RECID_SODATEYA_CNT );

	//空いてる場所を探す
	work = PokeAzukeruCheckGet(sodateya);				
	
	//ポケモン預け処理
	PokeSodateSetOne(party, pos, SodateyaWork_GetSodateyaPokePointer(sodateya, work), sv);	
}

// =================================================================
/**
 * @brief 育て屋ワークのポケモンを詰める
 * @param  sodateya
 * @retval  none
 */
// =================================================================
static void SodateBoxTume(SODATEYA_WORK *sodateya)
{
	SODATEYA_POKE *sp1, *sp2;
	POKEMON_PASO_PARAM *ppp1, *ppp2;

	
	sp1 = SodateyaWork_GetSodateyaPokePointer( sodateya, 0 );
	sp2 = SodateyaWork_GetSodateyaPokePointer( sodateya, 1 );
	ppp1 = SodateyaPoke_GetPokePasoPointer( sp1 );
	ppp2 = SodateyaPoke_GetPokePasoPointer( sp2 );

	OS_Printf("コピー前\n");
	OS_Printf("1匹目 = %d\n",PokePasoParaGet(ppp1,ID_PARA_monsno,NULL));
	OS_Printf("2匹目 = %d\n",PokePasoParaGet(ppp2,ID_PARA_monsno,NULL));
	
	if(PokePasoParaGet(ppp1,ID_PARA_monsno,NULL)==0){			//Pokemon[1]にﾎﾟｹﾓﾝがいて
		if(PokePasoParaGet(ppp2,ID_PARA_monsno,NULL)!=0){		//Pokemon[0]にいない
			SodateyaPoke_Copy(sp1,sp2);							//pokemon[1]から[0]にコピー
			SodateyaPoke_Init(sp2);								//[1]を初期化	
//			SioMailDataInit(&sodateya->SodatePoke[1].Mail);	
		}
	}

	OS_Printf("コピー後\n");
	OS_Printf("1匹目 = %d\n",PokePasoParaGet(ppp1,ID_PARA_monsno,NULL));
	OS_Printf("2匹目 = %d\n",PokePasoParaGet(ppp2,ID_PARA_monsno,NULL));
}

// =================================================================
/**
 * @brief 技覚えも自動的に行うレベルアップ処理
 * @param  pp
 * @retval  none
 */
// =================================================================
static void PokeAutoLevelUp(POKEMON_PARAM *pp)
{
	int i,count=0,r;
	u16 waza;
	u16 result;
	
	for(i=0;i<100;i++){							//どうせ１００までしかレベルはないし
		if(PokeLevelUpCheck(pp)){				//レベルアップしたか？
			OS_Printf("Level Up - level %d\n", PokeParaGet(pp,ID_PARA_level, NULL));
			count=0;
			while((result=PokeWazaOboeCheck(pp,&count,&waza))!=0){		//技を覚えるか
				OS_Printf( "LevelUpCheck result=%d, count=%d\n", result, count );

				// 技がいっぱいで覚えられなかった
				if(result==NO_WAZA_SET){
					OS_Printf( "OboeWaza =%d, \n", waza );
					//技がいっぱいでも無理やり押しこむ
					PokeWazaOboeOshidashi( pp, waza );	
				}
			}
		}else{									//レベルアップしなかった→終了
			break;
		}
	}
	PokeParaCalc(pp);
}


#if 0
		if(PokeLevelUpCheck(pp)){				//レベルアップしたか？
			while((result=PokeWazaOboeCheck(pp,&count,&waza))){		//技を覚えるか
//				count = 0;
//				result=PokeWazaOboeCheck(pp,&count,waza);
				OS_Printf( "LevelUpCheck result=%d, count=%d\n", result, count );

				// 技がいっぱいで覚えられなかった
				if(result==NO_WAZA_SET){
					OS_Printf( "OboeWaza =%d, \n", waza );
					//技がいっぱいでも無理やり押しこむ
//					for(r=0;r<count;r++){
						PokeWazaOboeOshidashi( pp, waza );	
//					}
				}
//			}
		}else{									//レベルアップしなかった→終了
			break;
		}

#endif

//--------------------------------------------------------------------------
/**
 * 手持ちにポケモンデータを戻す(カントー・ナナシマ共通)
 *
 * @param   party		てもちポケモン構造体
 * @param   sp			育て屋ポケモン構造体
 * @param   wordset		文字展開バッファポインタ
 *
 * @retval  u16		手持ちに戻したポケモンの開発ＮＯ
 *
 *
 */
//--------------------------------------------------------------------------
static int PokeHikitoriOne(POKEPARTY *party, SODATEYA_POKE *sp, WORDSET *wordset)
{
	POKEMON_PARAM		*pp = PokemonParam_AllocWork( HEAPID_FIELD );
	POKEMON_PASO_PARAM  *ppp = SodateyaPoke_GetPokePasoPointer(sp);
	SIO_MAIL_DATA       *smd = SodateyaPoke_GetSioMailPointer( sp );
	u32 exp;
	u16 monsno;

	WORDSET_RegisterPokeNickName( wordset, 0, ppp );		//名前セット

	monsno = PokePasoParaGet(ppp,ID_PARA_monsno,NULL);

	PokeReplace(ppp,pp);								//元のポケモンパラメータを取得
	if(PokeParaGet(pp,ID_PARA_level,NULL)!=100){
		exp =  PokeParaGet(pp,ID_PARA_exp,NULL);						//経験値を足す
		exp += SodateyaPoke_GetWalkCount( sp );
		PokeParaPut(pp,ID_PARA_exp,(u8*)&exp);
		PokeAutoLevelUp(pp);								//ﾚﾍﾞﾙｱｯﾌﾟ処理
	}

	if(PokeMailCheck(ppp)){
		PokeParaPut( pp, ID_PARA_mail_data, SodateyaMail_GetMailPointer( smd ) );	// メールを戻す
	}

	
	PokeParty_Add( party, pp );									// 手持ちポケモンに追加
//	if(sp->Mail.Mail.design_no!=NON_ITEM){						//メールがあったら
//		PokeAddWrittenMail(&PokeParaMine[5], &sp->Mail.Mail);	//手持ちにメールをセット
//		SioMailDataInit(&sp->Mail);								//育て屋のメールを初期化
//	}
	// メールチェック


	PokePasoParaInit(ppp);										//育て屋ワークから消去
	
	SodateyaPoke_SetWalkCount( sp, 0 );							//歩数カウントも消去
	
	sys_FreeMemoryEz(pp);
	
	return monsno;
}



// =================================================================
/**
 * @brief ポケモンを引き取るサブ
 * @param  sodateya 育て屋ワーク
 * @param  no       育て屋ワークのどっちから取り出すか(0か1)
 * @retval  u16 引き取ったポケモンのmonsno
 */
// =================================================================
u16 PokeHikitoriSub(POKEPARTY *party, WORDSET *wordset, SODATEYA_WORK *sodateya,u8 no)
{
	u16 monsno;
	SODATEYA_POKE *sp = SodateyaWork_GetSodateyaPokePointer(sodateya,no);

	monsno = PokeHikitoriOne( party, sp, wordset);	//手持ちにポケモンを戻す
	SodateBoxTume(sodateya);						//育て屋のデータを上詰めにする

	return monsno;									//ひきとったポケモンの番号
}

// =================================================================
/**
 * @brief 歩数カウント足した時のポケモンのレベルを返す
 * @param  p		ポケモン構造体
 * @param  walk		歩数
 * @retval  u8
 */
// =================================================================
int GetSinkaPokeLevel(POKEMON_PASO_PARAM *ppp, u32 walk)
{
	POKEMON_PARAM	   *tmp     = PokemonParam_AllocWork(HEAPID_FIELD);
	POKEMON_PASO_PARAM *tmp_ppp = PPPPointerGet(tmp);
	int level;

	u32	exp;

	
	PokeCopyPPPtoPPP( ppp,tmp_ppp);
	exp   = PokePasoParaGet(tmp_ppp,ID_PARA_exp,NULL);	//最初の経験値を算出
	exp   += walk;										//歩数をたす
	PokePasoParaPut(tmp_ppp,ID_PARA_exp,(u8*)&exp);		//新しい経験値としてセット
	level = PokePasoLevelCalc(tmp_ppp);				//新しいレベルを算出
	sys_FreeMemoryEz(tmp);

	return level;
	
}


//--------------------------------------------------------------------------
/**
 * 歩数分育っているレベルの差を返す（カントー・ナナシマ対応)
 *
 * @param   p		
 *
 * @retval  u8		
 *
 *
 */
//--------------------------------------------------------------------------
int GetSodatePokeLevel(SODATEYA_POKE *sp)
{
	u8 level1,level2;
	POKEMON_PASO_PARAM *ppp;

	ppp = SodateyaPoke_GetPokePasoPointer( sp );

	level1 = PokePasoLevelCalc( ppp );								//最初のレベルを算出
	level2 = GetSinkaPokeLevel( ppp ,SodateyaPoke_GetWalkCount(sp));//新しいレベルを算出
	return level2-level1;											//レベル差を返す
	
}

//--------------------------------------------------------------------------
/**
 * 歩数分育っているレベルの差を返す（カントー・ナナシマ対応)
 *
 * @param   p		
 *
 * @retval  u8		
 *
 *
 */
//--------------------------------------------------------------------------
int GetSodatePokeLevelDirect(SODATEYA_POKE *sp)
{
	u8 level;
	POKEMON_PASO_PARAM *ppp;

	ppp   = SodateyaPoke_GetPokePasoPointer( sp );
	level = GetSinkaPokeLevel( ppp ,SodateyaPoke_GetWalkCount(sp));//新しいレベルを算出

	return level;											//育ったレベルそのままを返す
	
}


// =================================================================
/**
 * @brief 育ててるポケモンの名前とレベル差の文字列をセット
 * @param  sp 育て屋ワーク
 * @retval  none
 */
// =================================================================
u8 SodatePokeLevelSetSub(SODATEYA_POKE *sp, WORDSET *wordset)
{
	int sa;
	STRBUF *strbuf;
	STRCODE tmpname[MONS_NAME_SIZE+1];
	POKEMON_PASO_PARAM *ppp = SodateyaPoke_GetPokePasoPointer(sp);
	
	sa = GetSodatePokeLevel(sp);						//育てたレベル差をセット
	WORDSET_RegisterNumber( wordset, 1, sa, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );

	WORDSET_RegisterPokeNickName( wordset, 0, ppp );	//ポケモンの名前をセット
	
	return sa;
}



//--------------------------------------------------------------------------
/**
 * 引き取り料金を返す（カントー・ナナシマ共通)
 *
 * @param   sp		育て屋ポケモンワーク
 *
 * @retval  u16		育て屋に支払う金額
 *
 *
 */
//--------------------------------------------------------------------------
int PokehikitoriRyoukinOne(SODATEYA_POKE *sp, WORDSET *wordset )
{
	u16 sa;
	POKEMON_PASO_PARAM *ppp = SodateyaPoke_GetPokePasoPointer(sp);

	sa = GetSodatePokeLevel(sp);						// 育てたレベル差を取得

	WORDSET_RegisterPokeNickName( wordset, 0, ppp );	// ポケモンの名前をセット

	sa = sa*100+100;									// 金額を文字列でセット
	WORDSET_RegisterNumber( wordset, 1, sa, 5, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );

	return sa;
	
}


// =================================================================
/**
 * @brief PokeHikitoriRyoukinのサブルーチン
 * @param  none
 * @retval  u16 育てた料金
 */
// =================================================================
int PokeHikitoriRyoukinSub(SODATEYA_WORK *sodateya, u8 no, WORDSET *wordset)
{
	//ポケモンを育てた料金をセット
	SODATEYA_POKE *spoke;

	spoke = SodateyaWork_GetSodateyaPokePointer( sodateya, no );

	return PokehikitoriRyoukinOne(spoke, wordset);	
	
}




// =================================================================
/**
 * @brief 指定歩数歩いたことにする
 * @param  count
 * @retval  none
 */
// =================================================================
void	SodateyaPlusWalk( SODATEYA_WORK *sodateya, u16 count)
{
	SODATEYA_POKE *spoke;
	int i,walkcount;
	
	for(i=0;i<2;i++){
		spoke = SodateyaWork_GetSodateyaPokePointer( sodateya, i );
		walkcount = SodateyaPoke_GetWalkCount(spoke);
		walkcount += count;
		SodateyaPoke_SetWalkCount(spoke, walkcount);
	}

}


// =================================================================
/**
 * @brief ポケモンの名前とレベルの文字列をセットする
 * @param  none(ただしPARAM0を見る)
 * @retval  none
 */
// =================================================================
u8 SodatePokeLevelSet( SODATEYA_WORK *sodateya, int pos, WORDSET *wordset )
{
	SODATEYA_POKE *sp       = SodateyaWork_GetSodateyaPokePointer( sodateya, pos);
	POKEMON_PASO_PARAM *ppp = SodateyaPoke_GetPokePasoPointer(sp);

	if(PokePasoParaGet( ppp, ID_PARA_monsno, NULL)){
		return SodatePokeLevelSetSub( sp, wordset );
	}
	return 0;
}




//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// タマゴ処理
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------





//------------------------------------------------------------------
/**
 * @brief   育て屋ワークからポケモンのポインタを渡す
 *
 * @param   sodateya		
 * @param   ppp[]		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SodateyaWork_GetPokePasoPointerArray( SODATEYA_WORK *sodateya, POKEMON_PASO_PARAM *ppp[] )
{
	ppp[0] = SodateyaWork_GetPokePasoPointer( sodateya, 0);
	ppp[1] = SodateyaWork_GetPokePasoPointer( sodateya, 1);
	
}

//------------------------------------------------------------------
/**
 * 性格を引き継ぐかチェック
 *
 * @param   sodateya	fld->SodateyaWorkのポインタ
 * @retval  int		
 */
//------------------------------------------------------------------
static int PokeMakeCheck(SODATEYA_WORK *sodateya)
{
	int i;
	int monsno[2],mother=-1,metamon;
	POKEMON_PASO_PARAM *ppp[2];

	SodateyaWork_GetPokePasoPointerArray( sodateya, ppp );

	for(i=0;i<2;i++){
		if(PokePasoSexGet( ppp[i] )==PARA_FEMALE){		//母親のポケモンを探す
			mother = i;
		}
	}
	
	for(metamon=0,i=0;i<2;i++){
		if((monsno[i]=PokePasoParaGet( ppp[i], ID_PARA_monsno, NULL ))==METAMON_NO){	//メタモンチェック
			metamon++;		//メタモンの数をチェック
			mother = i;		//メタモンの位置を保存
		}
	}

	if(metamon==2){								//メタモンが２体いる場合はどちらか抽選で決める
		if(gf_rand()>=(GF_RAND_MAX/2)){
			mother = 0;
		}else{
			mother = 1;
		}
	}											//メタモンが１体いる時は既にメタモンの位置が格納されているのでそれを使う

	OS_Printf("ppp[0]=%08x, ppp[1]=%08x, mother=%d\n",ppp[0],ppp[1],mother);

	if(PokePasoParaGet(ppp[mother],ID_PARA_item, NULL)==ITEM_KAWARAZUNOISI){		//かわらずの石を持っているかチェック
		if(gf_rand()>=(GF_RAND_MAX/2)){			//性格を継承するか抽選
			return -1;
		}
	}else{
		return -1;
	}
	
	return mother;								//性格を継承する方の添え字を返す
}



// =================================================================
/**
 * @brief タマゴを作る
 * @param  sodateya
 * @retval  none
 */
// =================================================================
void PokeMakeTamago(SODATEYA_WORK *sodateya)
{
	u32 oya_personal_rnd = 0, personal_rnd;
	int kawarazu,seikaku;
	int limitcounter=0;

	if((kawarazu=PokeMakeCheck(sodateya)) < 0){			//「かわらずの石」を持っているか？抽選で性格を受け継ぐことにするか？
		SodateyaWork_SetEggFlag( sodateya, gf_mtRand() );
	}else{
		POKEMON_PASO_PARAM *ppp = SodateyaWork_GetPokePasoPointer( sodateya, kawarazu );

		oya_personal_rnd=PokePasoParaGet( ppp ,ID_PARA_personal_rnd,NULL);		//個性乱数取得
		seikaku = PokeSeikakuGetRnd( oya_personal_rnd );						//性格取得

		for(;;){
			personal_rnd = gf_mtRand();
			if(seikaku==PokeSeikakuGetRnd(personal_rnd) && personal_rnd!=0){	//親の性格と同じ乱数になるまで無限ループ
				break;
			}
			if(++limitcounter>2400){											//無限ループはしないようにしたいので（リミットカウンターを設けた）
				break;															//もし不安定ならもっと減らします
			}
		}
		SodateyaWork_SetEggFlag( sodateya, personal_rnd );
	}

	OS_Printf("eggflag=%08x\n",SodateyaWork_GetEggFlag( sodateya ));

//	EventFlagSet(FE_SODATE_TAMAGO);					//おじいちゃん移動フラグset
	

	//母親と同じポケモン
	//レベルはパーソナルの生まれてくるレベル
	//パワー乱数は6項目中、ランダムで3項目を父親か母親と同じ数値にします
	//特殊能力は母親と同じ
	//技は通常にデータを作り、それから継承技をたしていきます
	//タマゴビットを立てます。
	//タマゴが孵るまでの歩数をなつき度の場所にいれます
}



void PokeMakeNidoranOsuTamago(SODATEYA_WORK *sodateya)
{
	SodateyaWork_SetEggFlag( sodateya, gf_rand() | 0x8000 );

//	EventFlagSet(FE_SODATE_TAMAGO);					//おじいちゃん移動フラグset
}


#define BOX_MAX	6

// =================================================================
/**
 * @brief 箱を詰める（抽選用）
 * @param  box 個性乱数系列が入っている配列
 * @param  num もう取り出さない配列の番号
 * @retval  u8 今回取り出した配列の番号
 */
// =================================================================
static void SelectBoxTumeru(u8 *box, u8 num)
{
	int i,w;
	u8  work[6];
	
	box[num] = 0xff;				//指定されたＢＯＸをＦＦで埋める
	
	for(i=0;i<BOX_MAX;i++){			//そのままコピー
		work[i] = box[i];
	}
	w = 0;
	for(i=0;i<BOX_MAX;i++){			//0xffが入っていない箱だけ詰めて入れなおす
		if(work[i]!=0xff){
			box[w++] = work[i];
		}
	}
}



// =================================================================
/**
 * @brief 子作り専用の乱数をセット
 * @param  p			ポケモン構造体
 * @param  sodateya		育て屋ワーク
 * @retval  none
 */
// =================================================================
static void PokeChildRandSet(POKEMON_PARAM *pp,SODATEYA_WORK *sodateya)
{
	u8 select[3],i,box[6],oya[3],work;

	for(i=0;i<6;i++) box[i] = i;			//０～５の箱を用意

	for(i=0;i<3;i++){						
		select[i] = box[gf_rand()%(6-i)];	//０～５のうち３つ選ぶ（どのパワー乱数を変更するか）
		SelectBoxTumeru(box,i);				//ネットで指摘されていたバグに対処
	}
	
	for(i=0;i<3;i++) oya[i] = gf_rand()%2;	//3つ０か１の乱数を選ぶ（父・母どちらから乱数を取り出すか）

	for(i=0;i<3;i++){						//抽選の結果から３つパワー乱数を親からコピーする
		POKEMON_PASO_PARAM *ppp = SodateyaWork_GetPokePasoPointer( sodateya, oya[i] );
		switch(select[i]){
			case 0:
				work = PokePasoParaGet( ppp, ID_PARA_hp_rnd,NULL);
				PokeParaPut(pp,ID_PARA_hp_rnd,(u8*)&work);
				break;
			case 1:
				work = PokePasoParaGet( ppp, ID_PARA_pow_rnd,NULL);
				PokeParaPut(pp,ID_PARA_pow_rnd,(u8*)&work);
				break;
			case 2:
				work = PokePasoParaGet( ppp,ID_PARA_def_rnd,NULL);
				PokeParaPut(pp,ID_PARA_def_rnd,(u8*)&work);
				break;
			case 3:
				work = PokePasoParaGet( ppp,ID_PARA_agi_rnd,NULL);
				PokeParaPut(pp,ID_PARA_agi_rnd,(u8*)&work);
				break;
			case 4:
				work = PokePasoParaGet( ppp, ID_PARA_spepow_rnd,NULL);
				PokeParaPut(pp,ID_PARA_spepow_rnd,(u8*)&work);
				break;
			case 5:
				work = PokePasoParaGet( ppp, ID_PARA_spedef_rnd,NULL);
				PokeParaPut(pp,ID_PARA_spedef_rnd,(u8*)&work);
				break;
		}
	}
}


// =================================================================
/**
 * @brief 継承技テーブルを取得する
 * @param  p		ポケモン構造体
 * @param  list		継承技を格納する配列のポインタ
 * @retval u8		配列に格納した継承技の数
 */
// =================================================================
static u8 KowazaListGet(POKEMON_PARAM *p, u16 *list)
{
	u16 monsno,startno,num,i;

	num = 0;
	startno = 0;
		
	monsno = PokeParaGet(p,ID_PARA_monsno,NULL);			//自分のmonsnoを取得
	for(i=0;i<KOWAZA_TABLE_MAX;i++){			//子技テーブルの自分の場所をサーチ
		if(KowazaTable[i]==(20000+monsno)){
			startno = i+1;
			break;
		}
	}
	
	for(i=0;i<POKE_KOWAZA_MAX;i++){							//最高８個しかないので、一応検索も１０個まで
		if(KowazaTable[startno+i]>20000){		//次のポケモンの先頭がきたら終了
			break;
		}else{
			list[i] = KowazaTable[startno+i];	//技リストを登録
			num++;
		}
	}

	return num;
}

typedef struct{
	int dadlist[4];
	int commonlist[4];
	int mamlist[4];
	u16 wazalist[50];
	u16 kowazalist[POKE_KOWAZA_MAX];
}KOWAZA_SEARCH_WORK;


// =================================================================
/**
 * @brief 継承技をセット
 * @param  p		:タマゴのポインタ
 * @param  dad		:父ポケモン
 * @param  mam		:母ポケモン
 * @retval  none
 */
// =================================================================
static void KowazaSet(POKEMON_PARAM *pp, POKEMON_PASO_PARAM *dad, POKEMON_PASO_PARAM *mam)
{
	u16 i,w,n,monsno,levelwazanum,kowazanum,form;
//	PokemonParam wp;
	KOWAZA_SEARCH_WORK *ksw = sys_AllocMemory(HEAPID_FIELD, sizeof(KOWAZA_SEARCH_WORK));

	n=0;
	// クリア
	MI_CpuClearFast(ksw, sizeof(KOWAZA_SEARCH_WORK));
	
	monsno = PokeParaGet(pp,ID_PARA_monsno,NULL);
	form   = PokeParaGet(pp,ID_PARA_form_no,NULL);
//	PokeParaSet(&wp,monsno,100,POW_RND,RND_NO_SET,0,ID_NO_SET,0);
	levelwazanum = PokeOboeruWazaAllGet( monsno, form, ksw->wazalist );		//レベルアップで覚える技をすべてリストアップ

	for(i=0;i<4;i++){											//親の持っている技を取得
		ksw->dadlist[i] = PokePasoParaGet(dad,ID_PARA_waza1+i,NULL);
		ksw->mamlist[i] = PokePasoParaGet(mam,ID_PARA_waza1+i,NULL);
	}

	kowazanum = KowazaListGet( pp, ksw->kowazalist );			//継承技リストを取得
	
	//継承技計算
	for(i=0;i<4;i++){											//父親の持っている技と子の継承技を比較
		if(ksw->dadlist[i]!=0){							
			for(w=0;w<kowazanum;w++){							//子技の数分比較
				if(ksw->dadlist[i]==ksw->kowazalist[w]){
					if(PokeWazaSet(pp,ksw->dadlist[i])==NO_WAZA_SET){	//技を覚えるか
						PokeWazaOboeOshidashi(pp,ksw->dadlist[i]);	//技がいっぱいでも無理やり押しこむ
					}
					break;
				}
			}
		}else{
			break;
		}
	}
	
	//父親の覚えている技が子供が技マシンで覚えられる技の場合
	for(i=0;i<4;i++){
		if(ksw->dadlist[i]!=0){												//父親の持っている技が
			for(w=0;w<WAZA_MACHINE_MAX;w++){								//技マシンにあり、
				if(ksw->dadlist[i] == GetWazaNoItem(ITEM_WAZAMASIN01+w)){	//子供は技マシンでつけることができるなら
					if(PokeWazaMachineCheck(monsno,form,w)){				//技を覚えるか
						if(PokeWazaSet( pp, ksw->dadlist[i] )==NO_WAZA_SET){		//技を覚える
							PokeWazaOboeOshidashi( pp, ksw->dadlist[i] );			//技がいっぱいでも無理やり押しこむ
						}
					}
				}
			}
		}
	}


	//父・母の共通してる技で子供がレベルアップ覚えられる技を取得
	for(i=0;i<4;i++){													//父・母の共通の技を取得
		if(ksw->dadlist[i]==0){
			break;
		}
		for(w=0;w<4;w++){
			if(ksw->dadlist[i]==ksw->mamlist[w] && ksw->dadlist[i]!=0){
				ksw->commonlist[n++] = ksw->dadlist[i];
			}
		}
	}
	
	for(i=0;i<4;i++){													//共通技の継承
		if(ksw->commonlist[i]==0){
			break;														//父母の共通技が
		}
		for(w=0;w<levelwazanum;w++){
			if(ksw->wazalist[w]!=0){											//子供のレベルアップで覚える技と
				if(ksw->commonlist[i] == ksw->wazalist[w]){						//同じなら
					if(PokeWazaSet(pp,ksw->commonlist[i])==NO_WAZA_SET){		//技を覚えるか
						PokeWazaOboeOshidashi(pp,ksw->commonlist[i]);			//技がいっぱいでも無理やり押しこむ
					}
					break;
				}
			}
		}
	
	}
	
	sys_FreeMemoryEz( ksw );
}


// =================================================================
/**
 * @brief タマゴを消す
 * @param  none
 * @retval  none
 */
// =================================================================
void DelSodateyaTamagoSub(SODATEYA_WORK *sodateya)
{
	//タマゴ処理の後始末
	SodateyaWork_SetEggFlag( sodateya, 0 );
	SodateyaWork_SetEggCount( sodateya, 0 );
}

// =================================================================
// アイテムをつけてるときに生まれるタマゴが変わるポケモンのテーブル
// =================================================================
#define ITEM_EVELUTION_MAX		( 9 )
static const u16 ItemPokeEvoTable[ITEM_EVELUTION_MAX][3]={
	{MONSNO_SOONANO,	ITEM_NONKINOOKOU,	MONSNO_SOONANSU		},	// ソーナノ　　のんきのおこう　ソーナンス
	{MONSNO_RURIRI,		ITEM_USIONOOKOU,	MONSNO_MARIRU		},	// ルリリ　　　うしおのおこう　マリル
	{MONSNO_MANENE,		ITEM_AYASIIOKOU,	MONSNO_BARIYAADO,	},	// マネネ　　　あやしいおこう　バリヤード
	{MONSNO_USOHATI,	ITEM_GANSEKIOKOU,	MONSNO_USOKKII,		},	// ウソハチ　　がんせきおこう　ウソッキー
	{MONSNO_GONBE,		ITEM_MANPUKUOKOU,	MONSNO_KABIGON,		},	// ゴンベ　　　まんぷくおこう　カビゴン
	{MONSNO_TAMANTA,	ITEM_SAZANAMINOOKOU,MONSNO_MANTAIN,		},	// タマンタ　　さざなみおこう　マンタイン
	{MONSNO_SUBOMII,	ITEM_OHANANOOKOU,	MONSNO_ROZERIA,		},	// スボミー　　おはなのおこう　ロゼリア
	{MONSNO_KORAKKII,	ITEM_KOUUNNOOKOU,	MONSNO_RAKKII,		},	// コラッキー　こううんおこう　ラッキー
	{MONSNO_RIRIIN,		ITEM_KIYOMENOOKOU,	MONSNO_TIRIIN		},	// リリーン　　きよめおおこう　チリーン
};

// =================================================================
/**
 * @brief アイテムをつけていると生まれるポケモンが変わる処理
 * @param  no      :生まれるタマゴのポケモンナンバー
 * @param  sodateya:育て屋ワーク
 * @retval none
 */
// =================================================================
static u16 ItemEvolutionCheck( u16 no, SODATEYA_WORK *sodateya )
{
	u16 item1,item2,index,i;
	POKEMON_PASO_PARAM *ppp[2];
	
	SodateyaWork_GetPokePasoPointerArray( sodateya, ppp );

	OS_Printf("元のポケモン = %d\n", no);

	// 生まれるポケモンがアイテムで変わる性質のものかチェック
	for(i=0;i<ITEM_EVELUTION_MAX;i++){				
		if(no==ItemPokeEvoTable[i][0]){
			index = i;
			break;
		}
	}

	// チェックから外れたら終了
	if(i==ITEM_EVELUTION_MAX){
		return no;
	}

	//預けているポケモンのアイテムを確認
	item1 = PokePasoParaGet( ppp[0], ID_PARA_item, NULL);
	item2 = PokePasoParaGet( ppp[1], ID_PARA_item, NULL);

	// 親のアイテムが条件に合致していない場合は元のポケモンに戻す
	if( item1 != ItemPokeEvoTable[index][1] && item2 != ItemPokeEvoTable[index][1]){
		no = ItemPokeEvoTable[index][2];
	}

	OS_Printf("書き換わったポケモン = %d\n",no);

	return no;
}

#if 0
static u16 ItemEvolutionCheck( u16 no, SODATEYA_WORK *sodateya )
{
	u16 flag,item1,item2;
	POKEMON_PASO_PARAM *ppp[2];
	
	SodateyaWork_GetPokePasoPointerArray( sodateya, ppp );

	flag = 0;
	if( no != MONSNO_SOONANO && no != MONSNO_RURIRI){				//生まれるポケモンがソーナノかルリリ
		return no;														//違ったら終了
	}
	for(i=0;i<ITEM_EVELUTION_MAX;i++){				// 生まれるポケモンがアイテムで変わる
		if(no==ItemPokeEvoTable[i][0]){				// 性質のものかチェック
			break;
		}
	}
	if(i==ITEM_EVELUTION_MAX){
		return no;
	}
		
	item1 = PokePasoParaGet( ppp[0], ID_PARA_item, NULL);	//預けているポケモンのアイテムを確認
	item2 = PokePasoParaGet( ppp[1], ID_PARA_item, NULL);

	if( no == MONSNO_SOONANO){										//ソーナノにのんきのおこうがなかったら
		if(item1 != ITEM_NONKINOOKOU && item2 != ITEM_NONKINOOKOU){
			no = MONSNO_SOONANSU;									//ソーナンスに
		}
	}
	if( no == MONSNO_RURIRI){										//ルリリにうしおのおこうがなかったら
		if(item1 != ITEM_USIONOOKOU && item2 != ITEM_USIONOOKOU){
			no = MONSNO_MARIRU;									//マリルに
		}
	}

	return no;
}

#endif

//------------------------------------------------------------------
/**
 * ピチューの特別処理(でんきだまを持っているとボルテッカーを覚える)
 *
 * @param   p			ポケモン構造体のポインタ
 * @param   sodateya	育てやワーク
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static void PichuExtraCheck(POKEMON_PARAM *pp, SODATEYA_WORK *sodateya)
{
	int item1,item2;
	POKEMON_PASO_PARAM *ppp[2];

	SodateyaWork_GetPokePasoPointerArray( sodateya, ppp );

	item1 = PokePasoParaGet( ppp[0], ID_PARA_item,NULL );		//親ポケモンのアイテムを確認
	item2 = PokePasoParaGet( ppp[1], ID_PARA_item,NULL );

	if( item1==ITEM_DENKIDAMA || item2==ITEM_DENKIDAMA ){					//でんきだまを持っていたら
		if(PokeWazaSet( pp, WAZANO_BORUTEKKAA )==NO_WAZA_SET){				//「ボルテッカー」を覚える
			PokeWazaOboeOshidashi( pp, WAZANO_BORUTEKKAA );				//押し出してでも覚える
		}
	}

}

#define SODATEYA_MOTHER	( 0 )
#define SODATEYA_FATHER  ( 1 )

// =================================================================
/**
 * @brief タマゴには何をいれるか
 * @param  sodateya		育て屋ワーク
 * @param  oya[2]		oya[0]に母親,oya[1]に父親を格納
 * @retval u16			格納したポケモンの開発NO
 */
// =================================================================
static u16 PokemonBotaiCheck(SODATEYA_WORK *sodateya, u8 oya[])
{
	u16 oyamonsno[2],i,flag,monsno,tamagono,temp;
	POKEMON_PASO_PARAM *ppp[2];

	SodateyaWork_GetPokePasoPointerArray( sodateya, ppp );

	flag = 0;
	for(i=0;i<2;i++){
		if((oyamonsno[i]=PokePasoParaGet( ppp[i], ID_PARA_monsno,NULL))==METAMON_NO){	//メタモンチェック
			oya[SODATEYA_MOTHER] = i^1;
			oya[SODATEYA_FATHER] = i;
		}else if(PokePasoSexGet( ppp[i])==PARA_FEMALE){		//母親のポケモンを探す
			oya[SODATEYA_MOTHER] = i;
			oya[SODATEYA_FATHER] = i^1;
		}
	}

	monsno   = oyamonsno[oya[SODATEYA_MOTHER]];				//母親が元になる
	tamagono = PokeSearchChild(monsno);			//子供を捜す

	if(tamagono==MONSNO_NIDORAN_F){				//ニドラン計算
		if(SodateyaWork_GetEggFlag( sodateya ) & 0x8000){				//タマゴ乱数の最上位ビットが立ってたら　ニドラン♂
			tamagono = MONSNO_NIDORAN_M;
		}else{									//逆はニドラン♀
			tamagono = MONSNO_NIDORAN_F;
		}
	}
	if(tamagono == MONSNO_IRUMIIZE){			//バルビート・イルミーゼ計算
		if(SodateyaWork_GetEggFlag( sodateya ) & 0x8000){
			tamagono = MONSNO_BARUBIITO;
		}else{
			tamagono = MONSNO_IRUMIIZE;
		}
	}
	
	if( tamagono == MONSNO_MANAFI){				// タマゴから生まれるとマナフィはエルフィになる
		tamagono = MONSNO_ERUFI;
	}
	
	//メタモンの反対側を母親として子供を作ったが、実際は♂や性別なしの時はこの後
	//父親として扱わないといけない時に父母を反転させる
	if(oyamonsno[oya[SODATEYA_FATHER]]==METAMON_NO && PokePasoSexGet( ppp[oya[SODATEYA_MOTHER]] )!=PARA_FEMALE){
		temp   = oya[SODATEYA_FATHER];
		oya[SODATEYA_FATHER] = oya[SODATEYA_MOTHER];
		oya[SODATEYA_MOTHER] = temp;
	}
	
	return tamagono;

}




	

//==============================================================================
/**
 * @brief   タマゴを作る(イベント・ふしぎなできごと用。（マナフィ含む）
 *			育て屋では使いません
 *
 * @param   pp			ポインタ
 * @param   monsno		開発NO
 * @param   eventflag	イベントフラグを立てるなら１
 * @param   status		自分のMYSTATUS
 * @param   setid		poke_memo.h参照の上格納するメモのタイプを指定
 * @param   placeid		手に入れた場所もしくはポケモンレンジャーなどのID
 *
 * @retval  none		
 */
//==============================================================================
void PokemonTamagoSet_forEvent(POKEMON_PARAM *pp, u16 monsno, u8 eventflag, MYSTATUS *status, int setid, int placeid )
{
	u8  level,event,flag;
	u16 ball;
	u8  egg_birth = PokePersonalParaGet( monsno, ID_PER_egg_birth );
	STRBUF *tamagoname;

	//レベル1のポケモン
#ifdef RARE_DEBUG
	PokeParaSet(pp,monsno,BIRTH_LEVEL,POW_RND,RND_SET,MyStatus_GetID(status),ID_NO_SET,0);	//レベル1のポケモン
#else
	PokeParaSet(pp,monsno,BIRTH_LEVEL,POW_RND,RND_NO_SET,0,ID_NO_SET,0);	
#endif

	level = 0;
	ball  = ITEM_MONSUTAABOORU;
	PokeParaPut( pp, ID_PARA_get_ball,  &ball );		//取得ボールをモンスターボールに
	PokeParaPut( pp, ID_PARA_friend,    &egg_birth );	//孵化までカウンタをセット
	PokeParaPut( pp, ID_PARA_get_level, &level );		//タマゴは取得時レベルを0に

	//タマゴくれるイベントの時は
	if(eventflag){													
//		event = POS_EVENT_EGG;
		PokeParaPut( pp, ID_PARA_get_place, &eventflag );
	}
	flag = 1;
	PokeParaPut( pp, ID_PARA_tamago_flag, &flag );		//タマゴフラグセット

	tamagoname = MSGDAT_UTIL_GetMonsName( MONSNO_TAMAGO, HEAPID_FIELD );

	PokeParaPut( pp, ID_PARA_nickname_buf,  tamagoname);

	STRBUF_Delete(tamagoname);

	if(setid == TRMEMO_FUSHIGI_PLACESET){
	  // あらかじめ親の名前、性別、IDをコピーしておく
	  u32 oyaid = MyStatus_GetID( status );
	  u32 oyasex = MyStatus_GetMySex( status );
	  STRBUF *oyaname = MyStatus_CreateNameString( status, HEAPID_EVENT );
	  // 親名を変更する場合
	  PokeParaPut(pp, ID_PARA_oyaname_buf, oyaname);
	  // 親のIDをコピー
	  PokeParaPut(pp, ID_PARA_id_no, &oyaid);
	  // 親の性別をコピー
	  PokeParaPut(pp, ID_PARA_oyasex, &oyasex);
	  STRBUF_Delete(oyaname);
	}
	
	// トレーナーメモ情報書き込み
	TrainerMemoSetPP( pp,status,setid,placeid, HEAPID_BASE_SYSTEM );
}


#define RARE_RANDOM_TRY_NUM	(4)
// =================================================================
/**
 * @brief タマゴを作る
 * @param  poke			:格納する場所のポインタ
 * @param  monsno		:ポケモンの番号（開発ナンバー）
 * @param  sodateya		:育て屋ワーク
 * @retval  none
 */
// =================================================================
void PokemonTamagoSet(POKEMON_PARAM *pp, u16 monsno, SODATEYA_WORK *sodateya, u32 id, u8 form_no)
{
	u8  level;
	u16 ball;
	u32 personal_rnd;
	STRBUF *tamagoname;
	u8  egg_birth = PokePersonalParaGet( monsno, ID_PER_egg_birth );

	personal_rnd =  SodateyaWork_GetEggFlag( sodateya );	//タマゴ作成用の個性乱数を取得

	// もしも育て屋に預けているポケモンがレアの生まれやすい状態（外国のポケモンが預けてある）なら
	if(SodateyaWork_GetRareFlag(sodateya)){
		int i;

		OS_Printf("育て屋レアルーチン発動\n");
		// 今持ってる乱数がレアか。
		if(PokeRareGetPara( id, personal_rnd )==FALSE){
			// 残りの４回はレアか？
			for(i=0;i<RARE_RANDOM_TRY_NUM;i++){
				personal_rnd = gf_fix_rand( personal_rnd );
				if(PokeRareGetPara( id, personal_rnd )){
					OS_Printf("レア確定\n");
					break;
				}
			}
		}else{
			OS_Printf("レア確定\n");
		}
	}


#ifdef RARE_DEBUG
	PokeParaSet(pp,monsno,BIRTH_LEVEL,POW_RND,RND_SET,id,ID_NO_SET,0);	//レベル1のポケモン
#else
	PokeParaSet(pp,monsno,BIRTH_LEVEL,POW_RND,RND_SET,personal_rnd,ID_NO_SET,0);	//レベル1のポケモン
#endif
	level = 0;
	ball  = ITEM_MONSUTAABOORU;

	PokeParaPut( pp, ID_PARA_get_ball,  &ball );					//取得ボールをモンスターボールに
	PokeParaPut( pp, ID_PARA_friend,    &egg_birth );				//孵化までカウンタをセット
	PokeParaPut( pp, ID_PARA_get_level, &level );					//タマゴは取得時レベルを0に
	PokeParaPut( pp, ID_PARA_form_no,   &form_no );					//タマゴは取得時レベルを0に

	tamagoname = MSGDAT_UTIL_GetMonsName( MONSNO_TAMAGO, HEAPID_FIELD );
	PokeParaPut( pp, ID_PARA_nickname_buf,  tamagoname);
	STRBUF_Delete(tamagoname);
}



// =================================================================
/**
 * @brief	タマゴを貰う=生まれるポケモンを作る
 * @param  sodateya
 * @retval  none
 */
// =================================================================
void PokeTamagoDel(SODATEYA_WORK *sodateya, POKEPARTY *party, MYSTATUS *my )
{
	u16 tamagono;
	u8 oya[2],flag;
	POKEMON_PARAM *poke = PokemonParam_AllocWork(HEAPID_FIELD);

	//母体とするポケモンを探す
	tamagono = PokemonBotaiCheck( sodateya, oya );					

	//アイテムで母体が変わるポケモンの処理
    //（ルリリとかソーナノとか）
	tamagono = ItemEvolutionCheck( tamagono, sodateya );			
																	
	
	//タマゴを作成
	{																
		u32 id = MyStatus_GetID(my);
		POKEMON_PASO_PARAM *ppp = SodateyaWork_GetPokePasoPointer( sodateya, oya[SODATEYA_MOTHER] );
		u8 form_no = PokePasoParaGet( ppp, ID_PARA_form_no, NULL );
		PokemonTamagoSet( poke, tamagono, sodateya, id, form_no );			
	}
	//子作り専用の乱数セット
	PokeChildRandSet( poke,sodateya );								
	
	//継承技をセット
	KowazaSet( poke, 												
				SodateyaWork_GetPokePasoPointer( sodateya, oya[SODATEYA_FATHER] ),
				SodateyaWork_GetPokePasoPointer( sodateya, oya[SODATEYA_MOTHER] )
	);	

	// トレーナーメモを埋め込み
	TrainerMemoSetPP( poke,my,TRMEMO_SODATEYA_PLACESET,
							  PlaceName_IndexToParamNumber( PLACENAME_TYPE_GAME_EVENT, MAPNAME_SODATEYA ),
							  HEAPID_FIELD );

	//ピチューの特別処理
	if(tamagono==MONSNO_PITYUU){
		PichuExtraCheck( poke, sodateya );							
	}

	//タマゴフラグセット
	flag = 1;
	PokeParaPut( poke, ID_PARA_tamago_flag, &flag);					

	//手持ちに加える
	PokeParty_Add( party, poke );									

	// 育て屋ワークからタマゴフラグ消去
	DelSodateyaTamagoSub( sodateya );								


	sys_FreeMemoryEz( poke );
}


// =================================================================
/**  特性がマグマのよろい、もしくは、ほのおのからだのポケモンが
 * 			手持ちにいる場合はたまごの孵るスピードがはやくなる
 *
 * @param  none
 * @retval u8	タマゴ孵化カウントを引く値
 */
// =================================================================
static int GetGrowthSpeed( POKEPARTY *party )
{
	u8 i;
	u8 spa;
	int total;

	total = PokeParty_GetPokeCount( party );
	for(i=0;i<total;i++){
		// ポケモンがタマゴでない
		if( PokeParaGet( PokeParty_GetMemberPointer( party, i), ID_PARA_tamago_exist, NULL ) == 0 ){
			spa = PokeParaGet(PokeParty_GetMemberPointer( party, i), ID_PARA_speabino, NULL);	// 特殊能力取得
			if( (spa == TOKUSYU_MAGUMANOYOROI)||(spa == TOKUSYU_HONOONOKARADA) ){//マグマのよろい、ほのおのからだ
				return 2;	//成長率2倍
			}
		}
	}
	return 1;//成長率変わらない
}


// =================================================================
/**
 * @brief タマゴグループが同じものがあるか比較する
 * @param  p1	タマゴグループ番号配列１（p1[2])
 * @param  p2	タマゴグループ番号配列２(p2[2])
 * @retval  u8  同じグループがあった
 */
// =================================================================
static u8 TamagoGroupCheck(u16 *p1, u16 *p2)
{
	int i,w;
	
	for(i=0;i<2;i++){
		for(w=0;w<2;w++){
			if(p1[i]==p2[w]) return 1;
		}
	}
	return 0;
}


#define NO_TAMAGO_GROUP		(15)
#define METAMON_GROUP		(13)

// =================================================================
/**
 * @brief   ポケモン２体の相性（卵ができる確率）を返す
 * @param   ppp		ポケモン２体分の POKEMON_PASO_PARAM* 配列
 * @retval  u8		0～70 ０だと絶対に卵はできない
 */
// =================================================================
static u8 CalcAffinity( POKEMON_PASO_PARAM** ppp )
{
	u16 group[2][2],monsno[2];
	u32	id[2],sex[2],rnd,i;

	for(i=0;i<2;i++){
		monsno[i] = PokePasoParaGet( ppp[i], ID_PARA_monsno,NULL);			//モンスターＮＯ
		id[i]     = PokePasoParaGet( ppp[i], ID_PARA_id_no,NULL);		//ＩＤ　ＮＯ

		rnd    = PokePasoParaGet( ppp[i], ID_PARA_personal_rnd,NULL);		//個性乱数
		sex[i] = PokeSexGetMonsNo(monsno[i],rnd);							//性別取得
		group[i][0] = PokePersonalParaGet(monsno[i], ID_PER_egg_group1);	//タマゴグループ１
		group[i][1] = PokePersonalParaGet(monsno[i], ID_PER_egg_group2);	//タマゴグループ２

//		group[i][0] = PPD[monsno[i]].egg_group1;							
//		group[i][1] = PPD[monsno[i]].egg_group2;							
	}

	
	if(group[0][0]==NO_TAMAGO_GROUP||group[1][0]==NO_TAMAGO_GROUP){	//無生殖グループとは生まれない
		return 0;													
	}
	if(group[0][0]==METAMON_GROUP && group[1][0]==METAMON_GROUP){	//メタモンとメタモンからは生まれない
		return 0;
	}
	if(group[0][0]==METAMON_GROUP||group[1][0]==METAMON_GROUP){		//メタモンが片方にいる
		if(id[0]==id[1]) {
			return 20;								//ＩＤが同じなら２０％
		}else{
			return 50;								//違うなら５０％
		}
	}
	if(sex[0]==sex[1]){
		return 0;									//同じ性別は相性ゼロ
	}
	if(sex[0]==PARA_UNK || sex[1]==PARA_UNK){				//メタモンチェック後は性別無しは相性ゼロ
		return 0;
	}
	
	if(TamagoGroupCheck(group[0],group[1])==0){
		return 0;			//グループが違ったら相性ゼロ
	}
	
	if(monsno[0]==monsno[1]){										//ポケモンの種類が同じ
		if(id[0]!=id[1]){
			return 70;								//ＩＤが違う
		}else{
			return 50;
		}
	}else{															//ポケモンの種類が違う
		if(id[0]!=id[1]){
			return 50;								//ＩＤが違う
		}else{
			return 20;
		}
	}
	return 0;
}
// =================================================================
/**
 * @brief ポケモンが２体いるときに相性を返す
 * @param  sodateya	育て屋ワーク
 * @retval  u8		0～70 ０だと絶対に卵はできない
 */
// =================================================================
static  u8 SodateyaPokeAffinity( SODATEYA_WORK	*sodateya )
{
	POKEMON_PASO_PARAM *ppp[2];

	SodateyaWork_GetPokePasoPointerArray( sodateya, ppp );

	return CalcAffinity( ppp );
}

// 記念日データ(日本だけ？）
static const u16 GrowSpeedUpDay[]={
	112,	// Ｂ
	214,	// バレンタインデー
	303,	// ひな祭り
	401,	// 入学式
	501,	// メーデー
	611,	// ダミー
	707,	// 七夕
	821,	// ダミー
	928,	// ＤＰ発売日
	1031,	// ハロウィン
	1121,	// Ｒ＆Ｓ発売日
	1224,	// クリスマスイブ
	1225,	// クリスマス
	
};


//------------------------------------------------------------------
/**
 * @brief   1年に１２回だけタマゴが育つのが速い日がある
 *
 * @param   fsys		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int GetEggCountSpeed( FIELDSYS_WORK *fsys )
{
	int month_day = EVTIME_GetMonth(fsys)*100+EVTIME_GetDay(fsys);
	int i;

	// 時間書き換えで違反状態になっていないか
	if(EVTIME_IsPenaltyMode( fsys )){
		return 255;
	}	

	// 特別な日はタマゴ孵化カウントが減るのが２５歩速い
	for(i=0;i<NELEMS(GrowSpeedUpDay);i++){
		if(GrowSpeedUpDay[i]==month_day){
			return 230;
		}
	}

	return 255;
}

// =================================================================
/**
 * @brief 育て屋処理	（一歩歩く毎に処理されます）
 * @param  none
 * @retval  u8   		タマゴが孵るか？ 0:いいえ	1:はい（タマゴデモ開始)
 */
// =================================================================
BOOL PokeSodateya( SODATEYA_WORK *sodateya, POKEPARTY *party, FIELDSYS_WORK *fsys )
{
	u32 i,work,flag,affinity,lottery;
	u32 walkcount=0,eggcount;
	int GrowthSpeed;
	POKEMON_PASO_PARAM *ppp[2];

	SodateyaWork_GetPokePasoPointerArray( sodateya, ppp );

	flag = 0;
	for(i=0;i<2;i++){			
		if(PokePasoParaGet( ppp[i], ID_PARA_poke_exist,NULL)!=0){	//ポケモンが預けられていたら
			SodateyaPoke_AddWalkCount(SodateyaWork_GetSodateyaPokePointer(sodateya,i),1);	//歩数カウント++
			flag++;
		}
	}
	if(SodateyaWork_GetEggFlag( sodateya )==0 && flag==2){									//たまごが無かったら
		if((SodateyaPoke_GetWalkCount(SodateyaWork_GetSodateyaPokePointer(sodateya,1))&0xff)==0xff){				
			affinity = SodateyaPokeAffinity( sodateya );			//相性取得
			lottery  = gf_rand();
			lottery  = (lottery*100)/GF_RAND_MAX;
			if(affinity>lottery){
				PokeMakeTamago( sodateya );							//タマゴ乱数セット
			}
		}
	}


	
	eggcount = SodateyaWork_GetEggCount( sodateya );				
	SodateyaWork_SetEggCount(sodateya, ++eggcount);

	//たまご孵化チェック
	if(eggcount == GetEggCountSpeed(fsys)){	
		SodateyaWork_SetEggCount(sodateya, 0);
		GrowthSpeed = GetGrowthSpeed( party );
		for(i=0;i<PokeParty_GetPokeCount( party );i++){
			POKEMON_PARAM *pp = PokeParty_GetMemberPointer( party, i);
			if(PokeParaGet( pp, ID_PARA_tamago_flag,NULL)){			//たまごを持っているか
				if(PokeParaGet( pp, ID_PARA_fusei_tamago_flag,NULL)){	//これはダメタマゴじゃないか？
					continue;											//無視する
				}
				work=PokeParaGet( pp, ID_PARA_friend,NULL);
				if(work!=0){											//孵化ウェイトを減らす
					if (work>=GrowthSpeed){
						work-=GrowthSpeed;
					}else{
						work--;
					}
					//デクリメントしたなつき度をセットしなおす
					PokeParaPut( pp, ID_PARA_friend,(u8*)&work);
				}else{													//タマゴが孵る
//					ScriptParameter0 = i;
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

// =================================================================
/**
 * @brief	産まれるポケモンを探す
 * @param	party	手持ちポケモンデータへのポインタ
 * @return	POKEMON_PARAM	うまれるタマゴへのポインタ
 *
 * 産まれるタマゴが存在しない場合、NULLを返す
 */
// =================================================================
POKEMON_PARAM * SodateyaSearchHatchingEgg(POKEPARTY * party)
{
	int i;
	POKEMON_PARAM * pp;
	int num = PokeParty_GetPokeCount(party);
	for (i = 0; i < num; i++) {
		pp = PokeParty_GetMemberPointer(party, i);
		if (PokeParaGet(pp, ID_PARA_tamago_flag, NULL)
				&& PokeParaGet(pp, ID_PARA_friend, NULL) == 0) {
			//タマゴでかつなつき度（タマゴの場合は孵化カウンタ）＝０の場合
			return pp;
		}
	}
	return NULL;
}



// =================================================================
/**
 * @brief じいさんの言葉用に文字列を埋めこむ
 * @param  sodateya
 * @retval  none
 */
// =================================================================
void SodateyaNameSet(SODATEYA_WORK *sodateya, WORDSET *wordset)
{
	POKEMON_PASO_PARAM *ppp[2];
	u16 strbuf[MONS_NAME_SIZE+EOM_SIZE];

	SodateyaWork_GetPokePasoPointerArray( sodateya, ppp );

	if(PokePasoParaGet( ppp[0], ID_PARA_monsno, NULL)!=0){			//一番目のポケモンの名前
		WORDSET_RegisterPokeNickName( wordset, 0, ppp[0] );
		WORDSET_RegisterPokeOyaName( wordset,  2, ppp[0] );			//親の名前
	}

	if(PokePasoParaGet( ppp[1], ID_PARA_monsno, NULL)!=0){			//二番目のポケモンの名前
		WORDSET_RegisterPokeNickName( wordset, 1, ppp[1] );
	}
}
// =================================================================
/**
 * @brief  育て屋に預けているポケモン名,性別、レベル取得
 * @param  sodateya
 * @retval  none
 */
// =================================================================
void SodateyaListNameSet(SODATEYA_WORK *sodateya,u32 buf_id,u32 buf2_id,u32 buf3_id,u8 no,WORDSET *wordset)
{
	SODATEYA_POKE      *sp;
	POKEMON_PASO_PARAM *ppp;
	u8 level,sex;
	u16 monsno;
	
	sp  = SodateyaWork_GetSodateyaPokePointer(sodateya, no);
	ppp = SodateyaWork_GetPokePasoPointer( sodateya, no);

	WORDSET_RegisterPokeNickName( wordset, buf_id, ppp );

	level = GetSinkaPokeLevel( ppp ,SodateyaPoke_GetWalkCount(sp));//新しいレベルを算出
	WORDSET_RegisterNumber( wordset, buf2_id, level, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );

	sex = PokePasoParaGet( ppp, ID_PARA_sex, NULL);

	if(sex != PARA_UNK){
		monsno = PokePasoParaGet( ppp, ID_PARA_monsno, NULL);
		if(((monsno == MONSNO_NIDORAN_F)||(monsno == MONSNO_NIDORAN_M))
				&&(PokePasoParaGet( ppp, ID_PARA_nickname_flag, NULL) == 0)){	//ニックネームをつけていないニドラン
			sex = PARA_UNK;	//既に性別記号があるので、無性扱いにする
		}
	}
	WORDSET_RegisterPokeMonsSex( wordset, buf3_id, sex );
}

// =================================================================
/**
 * @brief ポケモンリストで選択したポケモンの名前をセットする
 * @param  none
 * @retval  monsnoを返す
 */
// =================================================================
u16	SodateyaAzukeName( POKEPARTY *party, int pos, WORDSET *wordset )
{
	POKEMON_PARAM *pp = PokeParty_GetMemberPointer( party, pos );

	WORDSET_RegisterPokeNickName( wordset, 0, PPPPointerGet( pp ) );

	return PokeParaGet( pp, ID_PARA_monsno, NULL);
}

// =================================================================
/**
 * @brief じいさんに話しかけたときにチェック
 * @param  none
 * @retval  u8	0:なし	1:タマゴあり	2:1匹預けてる	3:2匹預けてる
 */
// =================================================================
u8 SodateyaZiisannCheck( SODATEYA_WORK *sodateya )
{ 
	u8 num;
 	if(SodateyaWork_GetEggFlag( sodateya )){			//タマゴチェック
		return 1;
	}
	if((num=PokeAzukeruCheck(  sodateya ))){		//預けてるかチェック
		return num+1;
	}
	return 0;											//無し
}

//------------------------------------------------------------------
/**
 * 卵が産まれる確率（百分率）を、連続した数値（0～3）に変換
 * ※確率は 0, 20, 50, 70% の４パターンしか無いため
 *
 * @param   percentage		確率（百分率）
 *
 * @retval  u8       0:70%  1:50%  2:20%  3:0%
 */
//------------------------------------------------------------------
u8 GetAffinityLevel( u32 percentage )
{
	switch( percentage ){
	case 0: return 3;		//べつべつにあそんどるがなあ
	case 20: return 2;		//それほどよくないがなあ
	case 50: return 1;		//まずまずのようじゃ
	case 70: return 0;		//とってもよいようじゃ
	}
	return 0;
}



// =================================================================
/**
 * @brief ２たいの相性によってじいさんの返す言葉をセットする
 * @param  none
 * @retval  u8
 */
// =================================================================
static int SodateyaPokeAffinityMsgSet( SODATEYA_WORK *sodateya )
{
	
	u8 work,result;
	work = SodateyaPokeAffinity( sodateya );		//二体の相性を取得
	result = GetAffinityLevel( work );

	//	PM_strcpy(MsgExpandBuffer,AffinityMsg[result]);	//相性ごとの文章をセット

	return result;
}

//------------------------------------------------------------------
/**
 * 任意のポケモンパラメータから卵相性レベルを算出(簡易版)
 *
 * 引数  : sodateya
 *
 * @retval  u32		3（相性最低）～ 0（相性最高）
 */
//------------------------------------------------------------------
extern u32 SodateyaGetAffinity(SODATEYA_WORK *sodateya)
{
	u8 work,result;
	work = SodateyaPokeAffinity( sodateya );		//二体の相性を取得
	result = GetAffinityLevel( work );
	return result;
}


// =================================================================
/**
 * @brief 文字列のなかに要求する性別記号はあったか
 * @param  buf	検索する文字列
 * @param  sex	ポケモンの性別
 * @retval  static u8	1:あった	0:なかった・もしくは両方あった
 */
// =================================================================
static int SexSymbolCheck(STRCODE *buf, int sex)
{
	u8 i,check[2];
	check[0] = check[1] = 0;
	i = 0;
	
	while(buf[i]!=EOM_){
		if(buf[i]==osu_ ){
			check[0]++;	//♂記号を検索
		}
		if(buf[i]==mesu_){
			check[1]++;	//♀記号を検索
		}
		i++;
	}
	
	if(sex==PARA_MALE){
		if(check[0]!=0 && check[1]==0){
			return 1;
		}
	}
	if(sex==PARA_FEMALE){
		if(check[1]!=0 && check[0]==0){
			return 1;
		}
	}
	
	return 0;
}


#if 0

// =================================================================
/**
 * @brief 文字列の最後に性別記号を追加する（ただし文字列の中に性別記号が既にないかをチェックする）
 * @param  buf	追記する文字列
 * @param  sex	ポケモンの性別
 * @retval  u8 * 文字列のポインタ
 */
// =================================================================
u8 *PM_SexStrcat(u8 *buf,u8 sex)
{
	if(sex==PARA_MALE){								//♂
		if(SexSymbolCheck(buf,PARA_MALE)==0){		//既に使われていないか
			return PM_strcat(buf,sex_msg[0]);
		}
	}else if(sex==PARA_FEMALE){						//♀
		if(SexSymbolCheck(buf,PARA_FEMALE)==0){		//既に使われていないか
			return PM_strcat(buf,sex_msg[1]);		
		}
	}
	return PM_strcat(buf,sex_msg[2]);				//性別無し・もしくは既に性別あり
	
}



// =================================================================
/**
 * @brief 性別の記号をあてる、ニドラン対策つき
 * @param  buf		:文字列バッファ
 * @param  pokemon	:ポケモンデータ構造体
 * @retval  u8 *		:文字列の最後のポインタ
 */
// =================================================================
u8 *PPP_SexStrcat(u8 *buf, PokemonPasoParam *pokemon)
{
	u8 sex;
	//性別
	sex=PokePasoSexGet(pokemon);						
	return PM_SexStrcat(buf, sex);
}

#endif

static void SodateyaMsgPrint( GF_BGL_BMPWIN *bmpwin, STRCODE *msg, int x, int y)
{
	MSG_PRINT_HEADER mph;

	mph.msg			= msg;
	mph.bmpwin	    = bmpwin;			//表示ウインドウINDEX
	mph.fnt_index	= FONT_SYSTEM;		//使用フォントINDEX
	mph.start_x		= x;				//描画Ｙオフセット
	mph.start_y		= y;				//描画Ｙオフセット
	mph.write_x		= x;				//※初期値はstart_xと同じ
	mph.write_y		= y;				//※初期値はstart_yと同じ
	mph.style		= 0;
//	msg_print_flag.cursor_type = CURSOR_FIELD;

	mph.space_x		= 0;				//文字間隔Ｘ
	mph.space_y		= 1;				//文字間隔Ｙ(１行表示:未使用)
	mph.f_col		= FBMP_COL_BLACK;	//文字色ナンバー
	mph.b_col		= FBMP_COL_WHITE;	//背景色ナンバー
	mph.s_col		= FBMP_COL_BLK_SDW;	//影色　ナンバー

//	MSG_PrintExpand(&mph,MSG_NO_PUT,NULL);
	GF_STR_Print( &mph, MSG_NO_PUT, NULL );

}


static void MakeSodateNamePut(SODATEYA_WORK *sodateya, GF_BGL_BMPWIN *bmpwin, int no, int y)
{
	STRCODE buf[20];
	POKEMON_PASO_PARAM *ppp;
	
	ppp = SodateyaWork_GetPokePasoPointer( sodateya, no);
	
	PokePasoParaGet( ppp, ID_PARA_nickname, buf );
	
//	PPP_SexStrcat(buf,&sodateya->SodatePoke[no].Poke);

	SodateyaMsgPrint(bmpwin,buf,12,y);

}

//--------------------------------------------------------------------------
/**
 * 
 *
 * @param   sodateya		
 * @param   bmpid		
 * @param   no		
 * @param   y		
 *
 * @retval  none		
 *
 *
 */
//--------------------------------------------------------------------------
static void MakeSodateLevelPut(SODATEYA_WORK *sodateya,u8 bmpid,int no,int y, WORDSET *wordset)
{
	STRCODE buf[10],strtmp[5];
	u8 level;
	SODATEYA_POKE      *sp;
	POKEMON_PASO_PARAM *ppp;
	
	sp  = SodateyaWork_GetSodateyaPokePointer(sodateya, no);
	ppp = SodateyaWork_GetPokePasoPointer( sodateya, no);
	
//	strcpy(buf,level_msg);
	level = GetSinkaPokeLevel( ppp, SodateyaPoke_GetWalkCount(sp) );	
	WORDSET_RegisterNumber( wordset, 0, level, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
//	PM_NumMsgSet(strtmp, level, NUM_MODE_LEFT, 3);
//	PM_strcat(buf,strtmp);

//	SodateyaMsgPrint(bmpid,buf,12+11*7,y);
	
}


//--------------------------------------------------------------------------
/**
 * 引き取りポケモン選択リスト表示のコールバック関数
 *
 * @param   index	BitmapID
 * @param   param	リスト行番号（この行の処理をこの関数はする）
 * @param   y		Bitmap内を指定するy座標
 *
 * @retval  none		
 *
 *
 */
//--------------------------------------------------------------------------
static void SodateyaSelectListPut( GF_BGL_BMPWIN *bmpwin, u32 param, u8 y )
{

	if(param < 2){				//「やめる」には名前・レベル表示は必要ない
//		MakeSodateNamePut(  &fld->SodateyaWork,index,param,y);		//	名前表示
//		MakeSodateLevelPut( &fld->SodateyaWork,index,param,y);		//	レベル表示
	}
}




// =================================================================
/**
 * @brief タマゴをポケモンに戻す
 *         他人から貰ったタマゴはＩＤと個性乱数のせいで
 *         タマゴフラグを落とすだけでは処理できないので
 *         必要なパラメータを格納したポケモンを構築しなおすことにする
 *
 * @param  p	ポケモン構造体
 * @param  temp	退避用のポケモン構造体
 * @retval  none
 */
// =================================================================
static void Tamago2Pokemon( POKEMON_PARAM *p, int heap )
{
	//他人からタマゴを貰った時、タマゴから孵化したポケモンは前の人のものではなく
	//孵化させた人のＩＤになる。これに対応するために一旦暗号化されている
	//データをすべて展開して格納しなおすことにする

	u16 monsno;
	u16 waza[4];
	u8  pp[4];
	u32 personal_rnd, id;
	u8	rnds[6], pokerus;
	u8  i,country_code,get_cassette,mark,friend,event,form_no,oyasex;
	STRBUF *oyaname = STRBUF_Create( PERSON_NAME_SIZE+EOM_SIZE, heap );

	POKEMON_PARAM *temp = PokemonParam_AllocWork( heap );


	monsno = PokeParaGet(p,ID_PARA_monsno,NULL);					//ポケモンナンバー
	for(i=0;i<4;i++){
		waza[i] = PokeParaGet(p,ID_PARA_waza1+i,NULL);				//技取得
		pp[i]   = PokeParaGet(p,ID_PARA_pp1+i,  NULL);				//技pp取得
	}
	personal_rnd = PokeParaGet(p,ID_PARA_personal_rnd,NULL);		//個性乱数取得
	for(i=0;i<6;i++){
		rnds[i] = PokeParaGet(p,ID_PARA_hp_rnd+i,NULL);				//６つの乱数取得
	}
	country_code = PokeParaGet(p,ID_PARA_country_code,NULL);		//国コード
	get_cassette = PokeParaGet(p,ID_PARA_get_cassette,NULL);		//捕獲カセット
	mark         = PokeParaGet(p,ID_PARA_mark,NULL);				//マーク
	pokerus      = PokeParaGet(p,ID_PARA_pokerus,NULL);				//ポケルス状態
	event		 = PokeParaGet(p,ID_PARA_event_get_flag,NULL);		//イベント配布か？
	PokeParaGet(p, ID_PARA_oyaname_buf, oyaname);
	oyasex       = PokeParaGet(p,ID_PARA_oyasex,NULL);
	id           = PokeParaGet(p,ID_PARA_id_no,NULL);
	form_no      = PokeParaGet(p,ID_PARA_form_no,NULL);


	// レンジャーマナフィ専用処理(レンジャーからもらったマナフィはレアにならない）
	if(monsno==MONSNO_MANAFI){
		int getplace = PokeParaGet( p, ID_PARA_get_place, NULL);
		OS_Printf("マナフィー孵化処理\n");
		if (getplace == PlaceName_IndexToParamNumber( PLACENAME_TYPE_EXT_EVENT, MAPNAME_RENJA )){
			// レアじゃなくなるまで乱数をまわす
			while(PokeRareGetPara( id, personal_rnd)){
				personal_rnd = gf_fix_rand( personal_rnd );
			}
		}
	
	}
	//ここからポケモン作成

	PokeParaSet(temp,monsno,BIRTH_LEVEL,POW_RND,RND_SET,personal_rnd,ID_NO_SET,0);	//レベル５のポケモン

	for(i=0;i<4;i++){
		PokeParaPut(temp,ID_PARA_waza1+i,&(waza[i]));		//技格納
		PokeParaPut(temp,ID_PARA_pp1+i,  &(pp[i]));			//技pp格納
	}
	for(i=0;i<6;i++){
		PokeParaPut(temp, ID_PARA_hp_rnd+i,&(rnds[i]));		//６つの乱数格納
	}
	PokeParaPut(temp,ID_PARA_country_code,&country_code);	//国コード
    PokeParaPut(temp,ID_PARA_get_cassette,&get_cassette);	//捕獲カセット
	PokeParaPut(temp,ID_PARA_mark,&mark);					//マーク
	friend = HUKA_FIRST_NATUKIDO;							//タマゴからうまれた場合なつき度は120をセットする
	PokeParaPut(temp,ID_PARA_friend,&friend);				//なつき度を120に
	PokeParaPut(temp,ID_PARA_pokerus,&pokerus);				//ポケルス状態をセット
	PokeParaPut(temp,ID_PARA_event_get_flag,&event);		//イベント配布フラグセット
	PokeParaPut(temp,ID_PARA_oyaname_buf, oyaname);			// 親名
	PokeParaPut(temp,ID_PARA_oyasex, &oyasex);			// 親の性別
	PokeParaPut(temp,ID_PARA_id_no,       &id);
	PokeParaPut(temp,ID_PARA_form_no,     &form_no);
	
	///< トレーナーメモでキーにしているデータの受け渡し
	{
		u16 id;
		u8  y, m, d;
		
		id = PokeParaGet(p, ID_PARA_get_place, NULL);
		y  = PokeParaGet(p, ID_PARA_get_year, NULL);
		m  = PokeParaGet(p, ID_PARA_get_month, NULL);
		d  = PokeParaGet(p, ID_PARA_get_day, NULL);
		PokeParaPut(temp, ID_PARA_get_place, &id);
		PokeParaPut(temp, ID_PARA_get_year,  &y);
		PokeParaPut(temp, ID_PARA_get_month, &m);
		PokeParaPut(temp, ID_PARA_get_day,   &d);
			
		id = PokeParaGet(p, ID_PARA_birth_place, NULL);
		y  = PokeParaGet(p, ID_PARA_birth_year, NULL);
		m  = PokeParaGet(p, ID_PARA_birth_month, NULL);
		d  = PokeParaGet(p, ID_PARA_birth_day, NULL);
		PokeParaPut(temp, ID_PARA_birth_place, &id);
		PokeParaPut(temp, ID_PARA_birth_year,  &y);
		PokeParaPut(temp, ID_PARA_birth_month, &m);
		PokeParaPut(temp, ID_PARA_birth_day,   &d);		
	}

	PokeCopyPPtoPP( temp, p );								//データをコピー

	STRBUF_Delete(oyaname);
	sys_FreeMemoryEz( temp );
}


// =================================================================
/**
 * @brief タマゴをポケモンにかえす
 * @param  no = 手持ちＮＯ
 * @retval  none
 */
// =================================================================
void SodateTamagoHuka( POKEMON_PARAM *pp, int heap )
{
	u8 	natsuki, nickname_flag;
	u8	ball, level;
	u16	monsno;
	STRCODE	namebuf[ 11 ];
	
	natsuki       = 70;
	nickname_flag = 0;
	ball          = ITEM_MONSUTAABOORU;
	level         = 0;

	Tamago2Pokemon( pp, heap );				//タマゴをポケモンに戻す

	PokeParaPut( pp, ID_PARA_tamago_flag, &natsuki);			//なつき度を初期値に

	monsno  = PokeParaGet( pp, ID_PARA_monsno, NULL);					//ポケモンＮＯを取得

	MSGDAT_MonsNameGet(monsno,HEAPID_BASE_SYSTEM,namebuf);					// デフォルトネーム取得
	PokeParaPut( pp, ID_PARA_nickname,	namebuf );
	PokeParaPut( pp, ID_PARA_nickname_flag, &nickname_flag );
	
	PokeParaPut( pp, ID_PARA_get_ball,  &ball);							//取得ボールをモンスターボールに
	PokeParaPut( pp, ID_PARA_get_level, &level);						//タマゴは取得時レベルを0に

	PokeParaCalc( pp );
}

#if 0
//------------------------------------------------------------------
/**
 * 育て屋メールが自分の物と違うメールに変わっていないかチェック
 *
 * @param   sodateya	育て屋構造体
 * @param   no			メールボックスNO(0-1)
 *
 * @retval  u8			0:変わってない	1:変わっている
 */
//------------------------------------------------------------------
static u8 SodateyaMailCheckSub(SODATEYA_WORK *sodateya, u8 no, WORDSET *wordset, SAVEDATA *sv )
{
	STRCODE pokename[30], myname[32];
	STRBUF *oyaname, *fpokename;
	SODATEYA_POKE      *sp    = SodateyaWork_GetSodateyaPokePointer( sodateya, no );
	POKEMON_PASO_PARAM *ppp   = SodateyaPoke_GetPokePasoPointer( sp );
	SIO_MAIL_DATA      *smail = SodateyaPoke_GetSioMailPointer( sp );
	MAIL_DATA          *mail  = SodateyaMail_GetMailPointer( smail );
	MYSTATUS		   *my    = SaveData_GetMyStatus( sv );

//	PM_stcpy(&sodateya->SodatePoke[no].Poke,pokename);	
	PokePasoParaGet( ppp, ID_PARA_nickname, pokename );						//ポケモンの名前取得
	MyStatus_SetMyName( my, myname );

	if( mail->design==NON_ITEM){
		return 0;	//メールが無いなら終了
	}
	
	if((PM_strcmp(pokename, SodateyaMail_GetNamePointer( smail, SIOMAIL_FLAG_POKE ))!=0)||	//ポケモンの名前がメールと違うか
	(PM_strcmp( myname, SodateyaMail_GetNamePointer( smail, SIOMAIL_FLAG_OYA ))!=0)){		//メールをつけた親の名前と自分が違うなら
//		PM_strcpy(StrTempBuffer0,pokename);								
//		PM_strcpy(StrTempBuffer1,sodateya->SodatePoke[no].Mail.oyaname);		
//		PM_strcpy(StrTempBuffer2,sodateya->SodatePoke[no].Mail.pokename);		
		WORDSET_RegisterPokeNickName( wordset, 0, ppp );
		oyaname = STRBUF_Create(HEAPID_FIELD, 20);
		fpokename = STRBUF_Create(HEAPID_FIELD, 20);
		STRBUF_SetStringCodeOrderLength( oyaname, SodateyaMail_GetNamePointer( smail, SIOMAIL_FLAG_OYA ), 10 );
		STRBUF_SetStringCodeOrderLength( fpokename, SodateyaMail_GetNamePointer( smail, SIOMAIL_FLAG_POKE ), 10 );

		STRBUF_Delete(oyaname);
		STRBUF_Delete(fpokename);

		return 1;
	}
	return 0;
}

#endif


//======================================================================================
//======================================================================================

//------------------------------------------------------------------
/**
 * 任意のポケモンパラメータから卵相性レベルを算出
 *
 * @param   ppp		ポケモン２体分の POKEMON_PASO_PARAM* 型配列
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 Sodateya_GetAffinityLevel( POKEMON_PASO_PARAM** ppp )
{
	return GetAffinityLevel( CalcAffinity(ppp) );
}

