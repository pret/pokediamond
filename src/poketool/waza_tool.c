
//============================================================================================
/**
 * @file	waza_tool.c
 * @bfief	技パラメータツール郡
 * @author	HisashiSogabe
 * @date	05.07.28
 */
//============================================================================================

#include	"common.h"

#include	"battle/battle_common.h"
#include	"battle/battle_server.h"
#include	"battle/fight_tool.h"
#include	"battle/server.h"
#include	"battle/server_tool.h"
#include	"battle/tokusyu_def.h"
#include	"battle/wazano_def.h"
#include	"poketool/monsno.h"
#include	"poketool/poke_tool.h"
#include	"poketool/waza_tool.h"
#include	"system/arc_tool.h"

#include	"itemtool/item.h"
#include	"itemtool/itemequip.h"
#include	"itemtool/itemsym.h"

#include	"waza_tool_def.h"

//============================================================================================
/**
 * 定数宣言
 */
//============================================================================================

typedef struct{
	u16	monsno;
	s16 hp;

	u16	hpmax;
	u8	eqp;
	u8	atc;

	u32 condition;

	u8	speabino;
	u8	sex;
	u8	type1;
	u8	type2;
}WAZA_DAMAGE_CALC_PARAM;

//============================================================================================
/**
 * プロトタイプ宣言
 */
//============================================================================================
void		WT_WazaTableDataGet(void *buffer);
ARCHANDLE	*WT_WazaDataParaHandleOpen(u32 heapID);
void		WT_WazaDataParaHandleClose(ARCHANDLE *handle);
u32			WT_WazaDataParaGet(int waza_no,int id);
u32			WT_WazaDataParaGetHandle(ARCHANDLE *handle,int waza_no,int id);
u8			WT_PPMaxGet(u16 wazano,u8 maxupcnt);
u32			WT_WazaDataParaGetAct(WAZA_TABLE_DATA *wtd,int id);

static	void	WT_WazaDataGet(int waza_no,WAZA_TABLE_DATA *wtd);

//============================================================================================
/**
 *	技データテーブルデータをAllocしたメモリに展開
 *
 * @param[in]	heapID	データを展開するメモリヒープID
 */
//============================================================================================
void	WT_WazaTableDataGet(void *buffer)
{
	ArchiveDataLoadOfs(buffer,ARC_WAZA_TBL,0,0,sizeof(WAZA_TABLE_DATA)*(WAZANO_MAX+1));
}

//============================================================================================
/**
 *	技データテーブルファイルハンドルオープン
 *
 * @param[in]	heapID	ハンドルをAllocするヒープID
 */
//============================================================================================
ARCHANDLE	*WT_WazaDataParaHandleOpen(u32 heapID)
{
	return	ArchiveDataHandleOpen(ARC_WAZA_TBL,heapID);
}

//============================================================================================
/**
 *	技データテーブルファイルハンドルクローズ
 *
 * @param[in]	handle	クローズするHandle
 */
//============================================================================================
void	WT_WazaDataParaHandleClose(ARCHANDLE *handle)
{
	ArchiveDataHandleClose(handle);
}

//============================================================================================
/**
 *	技データテーブルから値を取得
 *
 * @param[in]	waza_no		取得したい技ナンバー
 * @param[in]	id			取得したい値の種類
 */
//============================================================================================
u32	WT_WazaDataParaGet(int waza_no,int id)
{
	WAZA_TABLE_DATA wtd;

	WT_WazaDataGet(waza_no,&wtd);

	return	WT_WazaDataParaGetAct(&wtd,id);
}

//============================================================================================
/**
 *	技データテーブルから値を取得（ファイルハンドルを使用する）
 *
 * @param[in]	waza_no		取得したい技ナンバー
 * @param[in]	id			取得したい値の種類
 */
//============================================================================================
u32	WT_WazaDataParaGetHandle(ARCHANDLE *handle,int waza_no,int id)
{
	WAZA_TABLE_DATA wtd;

	ArchiveDataLoadByHandle(handle,waza_no,&wtd);

	return	WT_WazaDataParaGetAct(&wtd,id);
}

//============================================================================================
/**
 *	PPMaxを取得
 *
 * @param[in]	wazano		取得する技ナンバー
 * @param[in]	maxupcnt	マックスアップを使用した回数
 *
 * @retval	PPMAX
 */
//============================================================================================
u8	WT_PPMaxGet(u16 wazano,u8 maxupcnt)
{
	u8	ppmax;

	if(maxupcnt>3){
		maxupcnt=3;
	}

	ppmax=WT_WazaDataParaGet(wazano,ID_WTD_pp);
	ppmax+=(ppmax*20*maxupcnt)/100;

	return	ppmax;
}

//============================================================================================
/**
 *	技テーブル構造体データから値を取得
 *
 * @param[in]	wtd		技テーブル構造体データへのポインタ
 * @param[in]	id		取得したい技データのIndex
 */
//============================================================================================
u32	WT_WazaDataParaGetAct(WAZA_TABLE_DATA *wtd,int id)
{
	u32	ret;

	switch(id){
	case ID_WTD_battleeffect:
		ret=wtd->battleeffect;
		break;
	case ID_WTD_kind:
		ret=wtd->kind;
		break;
	case ID_WTD_damage:
		ret=wtd->damage;
		break;
	case ID_WTD_wazatype:
		ret=wtd->wazatype;
		break;
	case ID_WTD_hitprobability:
		ret=wtd->hitprobability;
		break;
	case ID_WTD_pp:
		ret=wtd->pp;
		break;
	case ID_WTD_addeffect:
		ret=wtd->addeffect;
		break;
	case ID_WTD_attackrange:
		ret=wtd->attackrange;
		break;
	case ID_WTD_attackpri:
		ret=wtd->attackpri;
		break;
	case ID_WTD_flag:
		ret=wtd->flag;
		break;
	case ID_WTD_ap_no:				//コンテスト用パラメータ　アピールNo
		ret=wtd->condata.ap_no;
		break;
	case ID_WTD_contype:			//コンテスト用パラメータ　コンテスト技タイプ
		ret=wtd->condata.contype;
		break;
	}
	return ret;
}

//============================================================================================
/**
 *							外部公開しない関数郡
 */
//============================================================================================
//============================================================================================
/**
 *	技テーブル構造体データを取得
 *
 * @param[in]	waza_no		取得したい技ナンバー
 * @param[out]	wtd			取得した技データの格納先を指定
 */
//============================================================================================
static	void	WT_WazaDataGet(int waza_no,WAZA_TABLE_DATA *wtd)
{
	ArchiveDataLoad(wtd,ARC_WAZA_TBL,waza_no);
}

