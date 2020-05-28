/**
 *	@file	mail.c
 *	@brief	メールセーブデータ　制御
 *	@author	Miyuki Iwasawa
 *	@date	06.02.09
 *
 *	メールセーブデータ反映手順
 *	1,MAIL_SearchNullID()で空き領域を検索、データID取得
 *	2,MailData_CreateWork()でダミーデータ作成用ワークエリアを取得
 *	3,MailData_CreateDataFromSave()などを使ってワークにデータを構築
 *	4,MAIL_AddDataFromWork()と取得済みのデータID,ワークのデータを使って、
 *	　セーブ領域にデータを反映させる
 *	5,ダミーワークエリアを開放する
 */

#include "common.h"
#include "savedata/savedata.h"
#include "savedata/mail.h"
#include "savedata/mail_local.h"
#include "savedata/mystatus.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "poketool/pokeicon.h"
#include "system/pms_data.h"
#include "system/buflen.h"
#include "system/pm_str.h"

/**
 *	@brief	メールデータサイズ取得
 *
 *	＊メールデータ一通のサイズ
 */
int MailData_GetDataWorkSize(void)
{
	return sizeof(MAIL_DATA);
}
/**
 *	@brief	メールデータクリア(初期データセット)
 */
void MailData_Clear(MAIL_DATA* dat)
{
	int i;
	
	dat->writerID = 0;
	dat->sex = PM_MALE;
	dat->region = CasetteLanguage;
	dat->version = CasetteVersion;
	dat->design = MAIL_DESIGN_NULL;

	PM_strclearEOM_(dat->name,BUFLEN_PERSON_NAME);

	for(i = 0;i < MAILDAT_ICONMAX;i++){
		dat->icon[i].dat = MAIL_ICON_NULL;
	}
	for(i = 0;i < MAILDAT_MSGMAX;i++){
		PMSDAT_Clear(&dat->msg[i]);
	}
}

/**
 *	@brief	メールデータが有効かどうか返す
 *	@retval	FALSE	無効
 *	@retval	TRUE	有効
 */
BOOL MailData_IsEnable(MAIL_DATA* dat)
{
	if(	dat->design >= MAIL_DESIGN_START &&
		dat->design <= MAIL_DESIGN_END){
		return TRUE;
	}
	return FALSE;
}

/**
 *	@brief	メールデータのワークを取得して返す
 *
 *	＊呼び出し側が責任もって解放すること
 *	
 */
MAIL_DATA* MailData_CreateWork(int heapID)
{
	MAIL_DATA* p;

	p = sys_AllocMemoryLo(heapID,sizeof(MAIL_DATA));
	MailData_Clear(p);

	return p;
}

/**
 *	@brief	メールデータの構造体コピー
 */
void MailData_Copy(MAIL_DATA* src,MAIL_DATA* dest)
{
	MI_CpuCopy8(src,dest,sizeof(MAIL_DATA));
}

/**
 *	@brief	デザインNo,ポケモンのポジション、セーブデータ指定してメールを新規作成状態に初期化
 *	@param	dat	データを作成するMAIL_DATA構造体型へのポインタ
 *	@param	design_no	メールのイメージNo
 *	@param	pos		メールを持たせるポケモンの手持ち内のポジション
 *	@param	save	セーブデータへのポインタ
 */
void MailData_CreateFromSaveData(MAIL_DATA* dat,u8 design_no,u8 pos,SAVEDATA* save)
{
	u8	i,ct,pal;
	u16	monsno;
	u32 icon,egg,form;
	MYSTATUS	*my;
	POKEPARTY	*party;
	POKEMON_PARAM* pp;
	
	MailData_Clear(dat);
	dat->design = design_no;

	//セーブデータから
	party = SaveData_GetTemotiPokemon(save);
	my = SaveData_GetMyStatus(save);

	//自機の名前
	PM_strcpy(dat->name,MyStatus_GetMyName(my));
	//性別
	dat->sex = (u8)MyStatus_GetMySex(my);
	//トレーナーID
	dat->writerID = MyStatus_GetID(my);

	//ポケモンアイコン取得
	for(i=pos,ct = 0;i < PokeParty_GetPokeCount(party);i++){
		pp = PokeParty_GetMemberPointer(party,i);
		monsno = PokeParaGet(pp,ID_PARA_monsno,NULL);
		egg = PokeParaGet(pp,ID_PARA_tamago_flag,NULL);
		form = PokeParaGet(pp,ID_PARA_form_no,NULL);
		icon = PokeIconCgxArcIndexGetByPP(pp);
//		pal = PokeIconPaletteNumberGet(monsno,egg);
		pal = PokeIconPalNumGet(monsno,form,egg);
		
		dat->icon[ct].cgxID = (u16)icon;
		dat->icon[ct++].palID = pal;
		if(ct >= MAILDAT_ICONMAX){
			break;
		}
	}
}

/**
 *	@brief	メールデータ　トレーナーID取得
 */
u32	MailData_GetWriterID(const MAIL_DATA* dat)
{
	return dat->writerID;
}
/**
 *	@brief	メールデータ　トレーナーID適用
 */
void MailData_SetWriterID(MAIL_DATA* dat,u32 id)
{
	dat->writerID = id;
}

/**
 *	@brief	メールデータ　ライター名取得
 */
STRCODE* MailData_GetWriterName(MAIL_DATA* dat)
{
	return &(dat->name[0]);
}
/**
 *	@brief	メールデータ　ライター名適用
 */
void MailData_SetWriterName(MAIL_DATA* dat,STRCODE* name)
{
	PM_strcpy(dat->name,name);
}

/**
 *	@brief	メールデータ　ライターの性別を取得
 */
u8	MailData_GetWriterSex(const MAIL_DATA* dat)
{
	return dat->sex;
}
/**
 *	@brief	メールデータ　ライターの性別を適用
 */
void MailData_SetWriterSex(MAIL_DATA* dat,const u8 sex)
{
	dat->sex = sex;
}

/**
 *	@brief	メールデータ　デザインNo取得
 */
u8	MailData_GetDesignNo(const MAIL_DATA* dat)
{
	return dat->design;
}
/**
 *	@brief	メールデータ　デザインNo適用
 */
void MailData_SetDesignNo(MAIL_DATA* dat,const u8 design)
{
	if(design >= MAIL_DESIGN_MAX){
		return;
	}
	dat->design = design;
}

/**
 *	@brief	メールデータ　国コード取得
 */
u8	MailData_GetCountryCode(const MAIL_DATA* dat)
{
	return dat->region;
}
/**
 *	@brief	メールデータ　国コード適用
 */
void MailData_SetCountryCode(MAIL_DATA* dat,const u8 code)
{
	dat->region = code;
}

/**
 *	@brief	メールデータ　カセットバージョン取得
 */
u8	MailData_GetCasetteVersion(const MAIL_DATA* dat)
{
	return dat->version;
}
/**
 *	@brief	メールデータ　カセットバージョン適用
 */
void MailData_SetCasetteVersion(MAIL_DATA* dat,const u8 version)
{
	dat->version = version;
}

/**
 *	@brief	メールデータ　メールアイコンパラメータの取得(インデックス指定版)
 *
 *	@param	mode	MAIL_ICONPRM_CGX:cgxNoの取得
 *					MAIL_ICONPRM_PAL:pltNoの取得
 *					MAIL_ICONPRM_ALL:u16型(MAIL_ICON型へキャスト可)で双方の値を返す
 *
 *	＊アイコンCgxIDとモンスターNoは同一ではありません。注意！
 */
u16	MailData_GetIconParamByIndex(const MAIL_DATA* dat,u8 index,u8 mode)
{
	if(index < MAILDAT_ICONMAX){
		switch(mode){
		case MAIL_ICONPRM_CGX:
			return dat->icon[index].cgxID;
		case MAIL_ICONPRM_PAL:
			return dat->icon[index].palID;
		case MAIL_ICONPRM_ALL:
		default:
			return dat->icon[index].dat;
		}
	}else{
		return 0;
	}
}
/**
 *	@brief	メールデータ　メールアイコンパラメータのセット(インデックス指定版)
 *
 *	@param	id		セットするデータID
 *	@param	mode	MAIL_ICONPRM_CGX:cgxNoのセット
 *					MAIL_ICONPRM_PAL:pltNoのセット
 *					MAIL_ICONPRM_ALL:u16型(MAIL_ICON型へキャスト可)で双方の値を返す
 *
 *	＊アイコンCgxIDとモンスターNoは同一ではありません。注意！
 */
void MailData_SetIconParamByIndex(MAIL_DATA* dat,u16 id,u8 index,u8 mode)
{
	if(index >= MAILDAT_ICONMAX){
		return;
	}
	switch(mode){
	case MAIL_ICONPRM_CGX:
		dat->icon[index].cgxID = id;
	case MAIL_ICONPRM_PAL:
		dat->icon[index].palID = id;
	case MAIL_ICONPRM_ALL:
	default:
		dat->icon[index].dat = id;
	}
}

/**
 *	@brief	メールデータ　メールアイコンデータの取得(インデックス指定版)
 *
 *	@param	index	データ取得開始インデックスNo(index<MAILDAT_ICONMAX)
 *	@param	pi		データ格納場所へのポインタ
 *	@param	num		データ取得数
 *	
 *	＊アイコンNoとモンスターNoは同一ではありません。注意！
 *	＊インデックスが不正だった場合、NULLアイコンデータを格納して返します
 */
void MailData_GetIconArray(MAIL_DATA* dat,u8 index,MAIL_ICON* pi,u8 num)
{
	u8	i;
	
	for(i = 0;i < num;i++){
		if(i  < MAILDAT_ICONMAX){
			pi[i].dat = dat->icon[i].dat;
		}else{
			pi[i].dat = MAIL_ICON_NULL;
		}
	}
}

/**
 *	@brief	メールデータ　簡易文取得(インデックス指定版)
 */
PMS_DATA*	MailData_GetMsgByIndex(MAIL_DATA* dat,u8 index)
{
	if(index < MAILDAT_MSGMAX){
		return &(dat->msg[index]);
	}else{
		return &(dat->msg[0]);
	}
}
/**
 *	@brief	メールデータ　簡易文セット(インデックス指定版)
 */
void MailData_SetMsgByIndex(MAIL_DATA* dat,PMS_DATA* pms,u8 index)
{
	if(index >= MAILDAT_MSGMAX){
		return;
	}
	PMSDAT_Copy(&dat->msg[index],pms);
}

/**
 *	@brief	メールデータ　簡易文文字列取得(インデックス指定)
 *
 *	@param	dat	MAIL_DATA*
 *	@param	index	簡易文インデックス
 *	@param	buf		取得した文字列ポインタの格納場所
 *
 *	@retval	FALSE	文字列の取得に失敗(または簡易文が有効なデータではない)
 *	
 *	@li	bufに対して内部でメモリを確保しているので、呼び出し側が明示的に解放すること
 *	@li	FALSEが返った場合、bufはNULLクリアされる
 */
BOOL MailData_GetMsgStrByIndex(const MAIL_DATA* dat,u8 index,STRBUF* buf,int heapID)
{
	if(index >= MAILDAT_MSGMAX){
		buf = NULL;
		return FALSE;
	}
	
	if(!PMSDAT_IsEnabled(&dat->msg[index])){
		buf = NULL;
		return FALSE;
	}

	buf = PMSDAT_ToString(&dat->msg[index],heapID);
	return TRUE;
}

//=================================================================
//
//=================================================================
//ローカル関数プロトタイプ
static int mail_GetNullData(MAIL_DATA* array,int num);
static int mail_GetNumEnable(MAIL_DATA* array,int num);
static MAIL_DATA* mail_GetAddress(MAIL_BLOCK* bloc,MAILBLOCK_ID blockID,int dataID);

/**
 *	@brief	セーブデータブロックへのポインタを取得
 */
MAIL_BLOCK* SaveData_GetMailBlock(SAVEDATA* sv)
{
	return SaveData_Get(sv,GMDATA_ID_MAILDATA);
}

/**
 *	@brief	メールセーブデータブロックサイズ取得
 *
 *	＊メールデータ一通のサイズではないので注意！
 */
int MAIL_GetBlockWorkSize(void)
{
	return sizeof(MAIL_DATA)*MAIL_STOCK_MAX;
}
/**
 *	@brief	メールセーブデータブロック初期化
 */
void MAIL_Init(MAIL_BLOCK* dat)
{
	int i = 0;

#if 0
	for(i = 0;i < MAIL_STOCK_TEMOTI;i++){
		MailData_Clear(&dat->temoti[i]);
	}
	for(i = 0;i < MAIL_STOCK_EXTRADE;i++){
		MailData_Clear(&dat->extrade[i]);
	}
	for(i = 0;i < MAIL_STOCK_SODATEYA;i++){
		MailData_Clear(&dat->sodateya[i]);
	}
#endif
	for(i = 0;i < MAIL_STOCK_PASOCOM;i++){
		MailData_Clear(&dat->paso[i]);
	}
}

/**
 *	@brief	空いているメールデータIDを取得
 *
 *	@param	id 追加したいメールブロックID
 *
 *	@return	int	データを追加できる場合は参照ID
 *				追加できない場合はマイナス値が返る
 */
int MAIL_SearchNullID(MAIL_BLOCK* block,MAILBLOCK_ID id)
{
	switch(id){
#if 0
	case MAILBLOCK_TEMOTI:
		return mail_GetNullData(block->temoti,MAIL_STOCK_TEMOTI);
	case MAILBLOCK_EXTRADE:
		return mail_GetNullData(block->extrade,MAIL_STOCK_EXTRADE);
	case MAILBLOCK_SODATEYA:
		return mail_GetNullData(block->sodateya,MAIL_STOCK_SODATEYA);
#endif
	case MAILBLOCK_PASOCOM:
		return mail_GetNullData(block->paso,MAIL_STOCK_PASOCOM);
	default:
		return MAILDATA_NULLID;
	}
	return MAILDATA_NULLID;
}

/**
 *	@brief	メールデータを削除
 *
 *	@param	blockID	ブロックのID
 *	@param	dataID	データID
 */
void MAIL_DelMailData(MAIL_BLOCK* block,MAILBLOCK_ID blockID,int dataID)
{
	MAIL_DATA* pd = NULL;
	
	pd = mail_GetAddress(block,blockID,dataID);
	if(pd != NULL){
		MailData_Clear(pd);
	}
}

/**
 *	@brief	メールデータをセーブブロックに追加
 *
 *	＊引き渡したMAIL_DATA構造体型データの中身がセーブデータに反映されるので
 *	　おかしなデータを入れないように注意！
 */
void MAIL_AddMailFormWork(MAIL_BLOCK* block,MAILBLOCK_ID blockID,int dataID,MAIL_DATA* src)
{
	MAIL_DATA* pd = NULL;
	
	pd = mail_GetAddress(block,blockID,dataID);
	if(pd != NULL){
		MailData_Copy(src,pd);
	}
}

/**
 *	@brief	指定ブロックに有効データがいくつあるか返す
 */
int MAIL_GetEnableDataNum(MAIL_BLOCK* block,MAILBLOCK_ID blockID)
{
	switch(blockID){
#if 0
	case MAILBLOCK_TEMOTI:
		return mail_GetNumEnable(block->temoti,MAIL_STOCK_TEMOTI);
	case MAILBLOCK_EXTRADE:
		return mail_GetNumEnable(block->extrade,MAIL_STOCK_EXTRADE);
	case MAILBLOCK_SODATEYA:
		return mail_GetNumEnable(block->sodateya,MAIL_STOCK_SODATEYA);
#endif
	case MAILBLOCK_PASOCOM:
		return mail_GetNumEnable(block->paso,MAIL_STOCK_PASOCOM);
	default:
		return 0;
	}
	return 0;

}

/**
 *	@brief	メールデータのコピーを取得
 *
 *	＊内部でメモリを確保するので、呼び出し側が責任持って領域を開放すること
 *	＊無効IDを指定した場合、空データを返す
 */
MAIL_DATA* MAIL_AllocMailData(MAIL_BLOCK* block,MAILBLOCK_ID blockID,int dataID,int heapID)
{
	MAIL_DATA* src = NULL;
	MAIL_DATA* dest;
	
	src = mail_GetAddress(block,blockID,dataID);
	dest = MailData_CreateWork(heapID);
	if(src != NULL){
		MailData_Copy(src,dest);
	}
	return dest;
}

/**
 *	@brief	メールデータのコピーを取得
 *
 *	＊あらかじめ確保したMAIL_DATA型メモリにセーブデータをコピーして取得
 */
void MAIL_GetMailData(MAIL_BLOCK* block,MAILBLOCK_ID blockID,int dataID,MAIL_DATA* dest)
{
	MAIL_DATA* src = NULL;
	
	src = mail_GetAddress(block,blockID,dataID);
	if(src == NULL){
		MailData_Clear(dest);
	}else{
		MailData_Copy(src,dest);
	}
}

//=================================================================
//
//=================================================================

/**
 *	@brief	手持ちブロックの空きを探して返す
 *
 *	@param	array	メールデータ配列へのポインタ
 *	@param	num		第一引数で渡した配列の要素数
 */
static int mail_GetNullData(MAIL_DATA* array,int num)
{
	int i = 0;

	for(i = 0;i < num;i++){
		if(!MailData_IsEnable(&array[i])){
			return i;
		}
	}
	return MAILDATA_NULLID;
}

/**
 *	@brief	有効データの数を探して返す
 */
static int mail_GetNumEnable(MAIL_DATA* array,int num)
{
	int i = 0;
	int ct = 0;
	
	for(i = 0;i < num;i++){
		if(MailData_IsEnable(&array[i])){
			ct++;
		}
	}
	return ct;
}

/**
 *	@brief	指定IDを持つブロック内のメールデータへのポインタを返す
 */
static MAIL_DATA* mail_GetAddress(MAIL_BLOCK* block,MAILBLOCK_ID blockID,int dataID)
{
	MAIL_DATA* pd = NULL;
	
	switch(blockID){
#if 0
	case MAILBLOCK_TEMOTI:
		if(dataID < MAIL_STOCK_TEMOTI){
			pd = &(block->temoti[dataID]);
		}
		break;
	case MAILBLOCK_EXTRADE:
		if(dataID < MAIL_STOCK_EXTRADE){
			pd = &(block->extrade[dataID]);
		}
		break;
	case MAILBLOCK_SODATEYA:
		if(dataID >= MAIL_STOCK_SODATEYA){
			pd = &(block->sodateya[dataID]);
		}
		break;
#endif
	case MAILBLOCK_PASOCOM:
		if(dataID < MAIL_STOCK_PASOCOM){
			pd = &(block->paso[dataID]);
		}
		break;
	default:
		break;
	}
	return pd;
}
