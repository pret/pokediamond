//============================================================================================
/**
 * @file	bag.c
 * @brief	バッグ画面処理 外部参照処理
 * @author	Hiroyuki Nakamura
 * @date	05.07.14
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/clact_tool.h"
#include "system/wordset.h"
#include "system/numfont.h"
#include "savedata/config.h"
#include "savedata/coin.h"
#include "savedata/custom_ball.h"
#include "savedata/b_tower.h"
#include "savedata/imageclip_data.h"
#include "itemtool/itemsym.h"
#include "field/itemuse.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_bag.h"
#include "msgdata/msg_common_scr.h"

#define	BAG_H_GLOBAL
#include "application/bag.h"
#include "bag_main.h"


//============================================================================================
//	定数定義
//============================================================================================


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static u32 BAG_CoinValGet( SAVEDATA * sv );
static u32 BAG_SealValGet( SAVEDATA * sv );
static u32 BAG_AccessoryValGet( SAVEDATA * sv );
static u32 BAG_WallpaperValGet( SAVEDATA * sv );
static u32 BAG_BattlePointGet( SAVEDATA * sv );


//============================================================================================
//	グローバル変数
//============================================================================================


//--------------------------------------------------------------------------------------------
/**
 * バッグ画面のデータ領域確保
 *
 * @param	mode	メモリ取得モード
 *
 * @return	確保した領域のアドレス
 */
//--------------------------------------------------------------------------------------------
BAG_DATA * BagSystemDataAlloc( u8 mode )
{
	BAG_DATA * wk = (BAG_DATA *)sys_AllocMemory( mode, sizeof(BAG_DATA) );
	memset( wk, 0, sizeof(BAG_DATA) );
	return wk;
}

u32 BagSystemDataSizeGet(void)
{
	return sizeof(BAG_DATA);
}



//--------------------------------------------------------------------------------------------
/**
 * バッグ画面の初期ページ設定
 *
 * @param	dat		データ設定場所
 * @param	page	初期ページ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BAG_InitPageSet( BAG_DATA * dat, u8 page )
{
	dat->p_now = page;
}

//--------------------------------------------------------------------------------------------
/**
 * バッグ画面のモード設定
 *
 * @param	dat		データ設定場所
 * @param	mode	バッグ画面の役割
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BAG_ModeSet( BAG_DATA * dat, u8 mode )
{
	dat->mode  = mode;
}

//--------------------------------------------------------------------------------------------
/**
 * バッグ画面の初期データ作成
 *
 * @param	dat		データ設定場所
 * @param	sv		セーブデータ
 * @param	mode	バッグ画面の役割
 * @param	cur		カーソル記憶場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BAG_SysDataSet( BAG_DATA * dat, SAVEDATA * sv, u8 mode, void * cur )
{
	BAG_ModeSet( dat, mode );
	dat->sv = sv;
	dat->bag_cursor = cur;
	dat->ret_item = 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケットデータ作成
 *
 * @param	dat		バッグ画面のデータ
 * @param	item	参照するアイテムデータ
 * @param	type	ポケットタイプ
 * @param	poke	ポケット番号
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BagPocketDataMake( BAG_DATA * dat, MINEITEM * item, u8 type, u8 poke )
{
	dat->p_data[poke].item = item;		// 参照するアイテムデータ
	dat->p_data[poke].type = type;		// ポケットタイプ
}

//--------------------------------------------------------------------------------------------
/**
 * 自転車フラグセット
 *
 * @param	dat		バッグ画面のデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BagCycleFlagSet( BAG_DATA * dat )
{
	dat->cycle_flg = 1;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用チェックワークセット
 *
 * @param	dat		バッグ画面のデータ
 * @param	icwk	アイテム使用チェックワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Bag_ItemUseCheckSet( BAG_DATA * dat, void * icwk )
{
	dat->icwk = icwk;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムを使用したポケモン位置設定
 *
 * @param	dat			バッグ画面のデータ
 * @param	use_poke	使用したポケモン位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Bag_UsePokeSet( BAG_DATA * dat, u8 use_poke )
{
	dat->use_poke = use_poke;
}

//--------------------------------------------------------------------------------------------
/**
 * マップモード設定
 *
 * @param	dat			バッグ画面のデータ
 * @param	map_mode	マップモード
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BAG_SysMapModeSet( BAG_DATA * dat, u16 map_mode )
{
	dat->map_mode = map_mode;
}

//--------------------------------------------------------------------------------------------
/**
 * データ取得：現在のポケット番号
 *
 * @param	dat		バッグ画面のデータ
 *
 * @return	現在のポケット番号
 */
//--------------------------------------------------------------------------------------------
u8 BagSysNowPocketNumGet( BAG_DATA * dat )
{
	return dat->p_now;
}

//--------------------------------------------------------------------------------------------
/**
 * データ取得：バッグ画面の役割
 *
 * @param	dat		バッグ画面のデータ
 *
 * @return	バッグ画面の役割
 */
//--------------------------------------------------------------------------------------------
u8 BagSysModeGet( BAG_DATA * dat )
{
	return dat->mode;
}

//--------------------------------------------------------------------------------------------
/**
 * データ取得：バッグで取得したアイテム
 *
 * @param	dat		バッグ画面のデータ
 *
 * @return	バッグで取得したアイテム
 */
//--------------------------------------------------------------------------------------------
u16 BagSysReturnItemGet( BAG_DATA * dat )
{
	return dat->ret_item;
}

//--------------------------------------------------------------------------------------------
/**
 * データ取得：バッグの戻り値
 *
 * @param	dat		バッグ画面のデータ
 *
 * @return	バッグの戻り値
 */
//--------------------------------------------------------------------------------------------
u16 BagSysReturnModeGet( BAG_DATA * dat )
{
	return dat->ret_mode;
}

//--------------------------------------------------------------------------------------------
/**
 * 前回アイテムを使用したポケモン位置を取得
 *
 * @param	dat			バッグ画面のデータ
 *
 * @return	アイテムを使用したポケモン位置
 */
//--------------------------------------------------------------------------------------------
u8 Bag_UsePokeGet( BAG_DATA * dat )
{
	return dat->use_poke;
}


//--------------------------------------------------------------------------------------------
/**
 * データ取得：カーソル位置、スクロールカウンタ
 *
 * @param	dat		バッグ画面のデータ
 * @param	poke	ポケット番号
 * @param	cur		カーソル位置
 * @param	scr		スクロールカウンタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BagCursorPosGet( BAG_DATA * dat, u8 poke, u16 * cur, u16 * scr )
{
	if( cur != NULL ){
		*cur = dat->p_data[poke].cur;
	}
	if( scr != NULL ){
		*scr = dat->p_data[poke].scr;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * データ取得：売った数カウンタ（冒険ノート用）
 *
 * @param	dat		バッグ画面のデータ
 *
 * @return	現在のポケット番号
 */
//--------------------------------------------------------------------------------------------
u8 BagSysSaleCntGet( BAG_DATA * dat )
{
	return dat->fnote_sale_cnt;
}



// コイン数取得
static u32 BAG_CoinValGet( SAVEDATA * sv )
{
	return COIN_GetValue( SaveData_GetMyCoin(sv) );
}

// シール数取得
static u32 BAG_SealValGet( SAVEDATA * sv )
{
	CB_SAVE_DATA * csd;
	u32	i, max;

	csd = CB_SaveData_AllDataGet( sv );
	max = 0;

	for( i=1; i<=CB_DEF_ITEM_DATA_NUM_MAX; i++ ){
		max += CB_Tool_SealTotalNumGet( csd, i );
	}
	return max;
}

// アクセサリー数取得
static u32 BAG_AccessoryValGet( SAVEDATA * sv )
{
	IMC_ITEM_SAVEDATA * imci = ImcSaveData_GetItemSaveData( SaveData_GetImcSaveData(sv) );

	return ImcSaveData_GetAcceAllNum( imci );
}

// 壁紙数取得
static u32 BAG_WallpaperValGet( SAVEDATA * sv )
{
	IMC_ITEM_SAVEDATA * imci = ImcSaveData_GetItemSaveData( SaveData_GetImcSaveData(sv) );

	return ImcSaveData_GetBGAllNum( imci );
}

// バトルポイント取得
static u32 BAG_BattlePointGet( SAVEDATA * sv )
{
	return (u32)BattlePoint_Get( sv );
}

BOOL BAG_ItemUseMsgSet( SAVEDATA * sv, STRBUF * buf, u16 item, u32 heap )
{
	MSGDATA_MANAGER * mman;
	WORDSET * wset;
	STRBUF * str;

	mman = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_bag_dat, heap );
	wset = WORDSET_Create( heap );

	if( item == ITEM_DUMMY_DATA ){
		str = MSGMAN_AllocString( mman, mes_bag_108 );
	}else if( item == ITEM_POINTOKAADO ){
		str = MSGMAN_AllocString( mman, mes_bag_106 );
		WORDSET_RegisterNumber(
			wset, 0, BAG_BattlePointGet(sv), 4, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	}else if( item == ITEM_SIIRUIRE ){
		str = MSGMAN_AllocString( mman, mes_bag_101 );
		WORDSET_RegisterNumber(
			wset, 0, BAG_SealValGet(sv), 4, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	}else if( item == ITEM_AKUSESARIIIRE ){
		str = MSGMAN_AllocString( mman, mes_bag_102 );
		WORDSET_RegisterNumber(
			wset, 0, BAG_AccessoryValGet(sv), 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		WORDSET_RegisterNumber(
			wset, 1, BAG_WallpaperValGet(sv), 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	}else if( item == ITEM_KOINKEESU ){
		str = MSGMAN_AllocString( mman, msg_bag_062 );
		WORDSET_RegisterNumber(
			wset, 0, BAG_CoinValGet(sv), 5, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	}else{
		WORDSET_Delete( wset );
		MSGMAN_Delete( mman );
		return FALSE;
	}

	WORDSET_ExpandStr( wset, buf, str );
	STRBUF_Delete( str );
	WORDSET_Delete( wset );
	MSGMAN_Delete( mman );

	return TRUE;
}

// エラーメッセージセット
void BAG_ItemUseErrorMsgSet( void * myst, STRBUF * buf, u16 item, u32 err, u32 heap )
{
	MSGDATA_MANAGER * mman;
	WORDSET * wset;
	STRBUF * str;

//	wset = WORDSET_Create( heap );

	switch( err ){
	case ITEMCHECK_ERR_CYCLE_OFF:		// 自転車を降りれない
		mman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_bag_dat, heap );
		MSGMAN_GetString( mman, msg_bag_058, buf );
		MSGMAN_Delete( mman );
		break;

	case ITEMCHECK_ERR_COMPANION:		// 使用不可・連れ歩き
		mman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_bag_dat, heap );
		MSGMAN_GetString( mman, msg_bag_err_01, buf );
		MSGMAN_Delete( mman );
		break;

	default:							// 使用不可・博士の言葉
		mman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_common_scr_dat, heap );
		wset = WORDSET_Create( heap );
		str  = MSGMAN_AllocString( mman, msg_item_ng_01 );
		WORDSET_RegisterPlayerName( wset, 0, myst );
		WORDSET_ExpandStr( wset, buf, str );
		STRBUF_Delete( str );
		WORDSET_Delete( wset );
		MSGMAN_Delete( mman );
	}

/*
	WORDSET_ExpandStr( wset, buf, str );
	STRBUF_Delete( str );
	WORDSET_Delete( wset );
	MSGMAN_Delete( mman );
*/

}
