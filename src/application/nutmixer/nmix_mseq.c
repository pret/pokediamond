/**
 *	@file	nmix_bag.c
 *	@brief	ナッツミキサー　木の実袋参照
 *	@author	Miyuki Iwasawa
 *	@date	06.04.07
 */

#include "common.h"
#include "system/procsys.h"
#include "system/snd_tool.h"
#include "system/savedata.h"
#include "system/gamedata.h"
#include "itemtool/itemsym.h"
#include "itemtool/item.h"
#include "application/bag.h"
#include "application/nuts_tag.h"
#include "communication/communication.h"

#include "application/nutmixer.h"
#include "nutmixer_sys.h"

#include "nmix_mseq.h"

///バッグ画面プロセスコントロール
typedef enum{
 BAGSEQ_BAG_CALL,
 BAGSEQ_BAG_WAIT,
 BAGSEQ_TAG_CALL,
 BAGSEQ_TAG_WAIT,
 BAGSEQ_BAG_END,
 BAGSEQ_BAG_GAME_END,
 BAGSEQ_END,
};

//======================================================
///プロトタイプ宣言
static int bagseq_bagCall(NUTMIXER_WORK* mp);
static int bagseq_bagWait(NUTMIXER_WORK* mp);
static int bagseq_tagCall(NUTMIXER_WORK* mp);
static int bagseq_tagWait(NUTMIXER_WORK* mp);

extern PROC_RESULT NMixGameProc_Init(PROC* proc,int *seq);
extern PROC_RESULT NMixGameProc_Main(PROC* proc,int *seq);
extern PROC_RESULT NMixGameProc_End(PROC* proc,int *seq);

//======================================================
///メイン関数
/**
 *	@brief	メインコマンド　木の実選択フロー
 */
int NMixMainSeq_Bag(NUTMIXER_WORK* mp,int* seq)
{
	switch(*seq){
	case BAGSEQ_BAG_CALL:
		*seq = bagseq_bagCall(mp);
		break;
	case BAGSEQ_BAG_WAIT:
#ifdef DEBUG_NUTMIXER_AUTO
		sys.trg |= PAD_BUTTON_A;	//Aボタン押しっぱなし
#endif	// DEBUG_NUTMIXER_AUTO
		
		*seq = bagseq_bagWait(mp);
		break;
	case BAGSEQ_TAG_CALL:
		*seq = bagseq_tagCall(mp);
		break;
	case BAGSEQ_TAG_WAIT:
		*seq = bagseq_tagWait(mp);
		break;
	
	case BAGSEQ_BAG_END:
		return NMSEQ_GAME_CALL;

	case BAGSEQ_BAG_GAME_END:	// ゲーム自体を終了
		return NMSEQ_MAIN_END;
	}
	return NMSEQ_BAG_MAIN;
}

/**
 *	@brief	メインコマンド　ゲームメインプロセスコール
 */
int NMixMainSeq_GameCall(NUTMIXER_WORK* mp,int* seq)
{
	// オーバーレイID宣言
	FS_EXTERN_OVERLAY(nuts_mixer);

	// プロセス定義データ
	const PROC_DATA NMixGameProcData = {
		NMixGameProc_Init,
		NMixGameProc_Main,
		NMixGameProc_End,
		FS_OVERLAY_ID(nuts_mixer)
//		NO_OVERLAY_ID
	};
	mp->proc = PROC_Create(&NMixGameProcData,mp,mp->heapID);
	return NMSEQ_GAME_WAIT;
}

/**
 *	@brief	メインコマンド　ゲームメインプロセス終了待ち
 */
int NMixMainSeq_GameWait(NUTMIXER_WORK* mp,int *seq)
{
	if(NutMixerProcCall(&mp->proc) == FALSE){
		return NMSEQ_GAME_WAIT;
	}

	if( mp->game_next == TRUE ){
		return NMSEQ_BAG_MAIN;	// 木の実選択画面へ
	}else{
		return NMSEQ_GAME_END;	// 終了へ
	}
	
}

/**
 *	@brief	メインコマンド　ゲームメインプロセス終了処理
 */
int NMixMainSeq_GameEnd(NUTMIXER_WORK* mp,int *seq)
{
	return NMSEQ_MAIN_END;
}

//======================================================
///ローカルサブ関数

/**
 *	@brief	バッグ画面呼び出し
 */
static int bagseq_bagCall(NUTMIXER_WORK* mp)
{
	void * buf;
	u32 mode;

	// オーバーレイID宣言
	FS_EXTERN_OVERLAY(fld_bag);

	// プロセス定義データ
	const PROC_DATA BagProcData = {
		BagProc_Init,
		BagProc_Main,
		BagProc_End,
		FS_OVERLAY_ID(fld_bag)
	};

	static const u8 NMixerBagList[] = {
		BAG_POKE_NUTS, 0xff
	};

	buf = MyItem_MakeBagData( mp->param->itemSave, NMixerBagList,mp->heapID);

//	BagSystemDataSet( buf, 0, BAG_MODE_ITEMSET, mp->param->mySave );
//	BagSystemDataSet( buf, 0, BAG_MODE_FIELD, mp->param->mySave );

	if( mp->comm_f == 1 ){
		mode = BAG_MODE_MIX_SIO;
	}else{
		mode = BAG_MODE_MIX;
	}
	
	BAG_SysDataSet(
		buf, 
		mp->param->SaveData,
		mode,
		mp->bag_cursor );

	/*
	if( Player_FormGet( fsys->player ) == HERO_FORM_CYCLE ){
		BagCycleFlagSet( buf );
	}

	if( !(ZoneData_IsSinouField(fsys->location->zone_id)) ){
		BagUnderCheckFlagSet( buf );
	}
*/
	mp->proc = PROC_Create(&BagProcData,buf,mp->heapID);
	
	mp->app_wk = buf;
	return BAGSEQ_BAG_WAIT;
}

/**
 *	@brief	バッグ画面終了待ち
 */
static int bagseq_bagWait(NUTMIXER_WORK* mp)
{
	BAG_DATA* dat = NULL;
	BOOL result;

	if(!NutMixerProcCall(&mp->proc)){
		return BAGSEQ_BAG_WAIT;
	}

	dat = BagSystemDataAlloc( mp->heapID);
	memcpy( dat, mp->app_wk, BagSystemDataSizeGet() );
	sys_FreeMemoryEz( mp->app_wk );
	mp->app_wk = NULL;

	mp->itemno = BagSysReturnItemGet( dat );
	sys_FreeMemoryEz( dat );

	switch( BagSysReturnModeGet( dat ) ){
	case BAG_RET_TAG:		// タグをみる
		return BAGSEQ_TAG_CALL;
	
	case BAG_RET_USE:		// つかう
	case BAG_RET_ITEMSET:	// もたせる
	case BAG_RET_POKEITEMSET:	// ポケモンリスト「もたせる」
	case BAG_RET_ENTER:		// 使う
		break;

	case BAG_RET_CANCEL:	// ゲーム自体終了
		return BAGSEQ_BAG_GAME_END;
		
	default:
		GF_ASSERT( 0 );
		//本当はここにはこないので、ダミーを仕込む
		mp->itemno = ITEM_KURABONOMI;
		break;
	}

#ifndef DEBUG_NUTMIXER_AUTO
	// 手持ちからアイテムを引く
	result = MyItem_SubItem( mp->param->itemSave, mp->itemno, 1, mp->heapID );
	GF_ASSERT( result );
#endif
	
	return BAGSEQ_BAG_END;
}

/**
 *	@breif	タグ画面呼び出し
 */
static int bagseq_tagCall(NUTMIXER_WORK* mp)
{
	u8	i;
	u8	scr, cur, max, item;
	MYITEM * myitem = mp->param->itemSave;
	
	// オーバーレイID宣言
	FS_EXTERN_OVERLAY(nuts_tag);

	// プロセス定義データ
	const PROC_DATA NutsTagProcData = {
		NutsTagProc_Init,
		NutsTagProc_Main,
		NutsTagProc_End,
		FS_OVERLAY_ID(nuts_tag)
	};
	
	mp->app_wk = NutsTagSystemDataAlloc( mp->heapID );
	NutsTagPutDataSet( mp->app_wk, mp->itemno, TAG_ON );

	max = 0;
	for( i=0; i<ITEM_NUTS_MAX; i++ ){
		item = NutsIDItemGet( i );
		if( MyItem_CheckItem( myitem, item, 1, mp->heapID ) == TRUE ){
			NutsTagPutDataSet( mp->app_wk, item, TAG_OFF );
			max++;
		}
	}

	MyItem_FieldBagCursorGet( mp->bag_cursor, BAG_POKE_NUTS, &cur, &scr );
	NutsTagBagCursorSet( mp->app_wk, scr, cur, max+2 );

	mp->proc = PROC_Create(&NutsTagProcData,mp->app_wk,mp->heapID);
	return BAGSEQ_TAG_WAIT;
}

/**
 *	@brief	木の実タグ終了待ち
 */
static int bagseq_tagWait(NUTMIXER_WORK* mp)
{
	u8	scr, cur;
	if(!NutMixerProcCall(&mp->proc)){
		return BAGSEQ_TAG_WAIT;
	}

	TagPosGet( mp->app_wk, &scr, &cur );
	MyItem_FieldBagCursorSet( mp->bag_cursor, BAG_POKE_NUTS, cur, scr );
	
	sys_FreeMemoryEz(mp->app_wk);
	mp->app_wk = NULL;
	return BAGSEQ_BAG_CALL;
}
