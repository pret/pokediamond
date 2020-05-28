//============================================================================================
/**
 * @file	ntag_dat.c
 * @brief	木の実タグ画面データ処理
 * @author	Hiroyuki Nakamura
 * @date	06.03.29
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "itemtool/itemsym.h"
#include "itemtool/nuts.h"

#include "ntag_dat.h"
#include "application/nuts_tag.h"


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void TagPutFlagSet( u32 * flg, u16 id );


//--------------------------------------------------------------------------------------------
/**
 * 木の実タグ画面のデータ領域確保
 *
 * @param	heap	ヒープＩＤ
 *
 * @return	確保した領域のアドレス
 */
//--------------------------------------------------------------------------------------------
NTAG_DATA * NutsTagSystemDataAlloc( u8 heap )
{
	NTAG_DATA * wk = (NTAG_DATA *)sys_AllocMemory( heap, sizeof(NTAG_DATA) );
	memset( wk, 0, sizeof(NTAG_DATA) );
	return wk;
}

u32 NutsTagSystemDataSizeGet(void)
{
	return sizeof(NTAG_DATA);
}

//--------------------------------------------------------------------------------------------
/**
 * 木の実タグ画面の表示タグ設定
 *
 * @param	dat		データ設定場所
 * @param	item	アイテム番号
 * @param	flg		初期タグ設定フラグ
 *
 * @return	none
 *
 * @li	flg = TAG_ON : 最初に表示されるタグに設定
 */
//--------------------------------------------------------------------------------------------
void NutsTagPutDataSet( NTAG_DATA * dat, u16 item, u16 flg )
{
	u16	num = item - NUTS_START_ITEMNUM;

	TagPutFlagSet( dat->tag_flg, num );
	if( flg == TAG_ON ){
		dat->now_tag = num;
	}
}

void NutsTagBagCursorSet( NTAG_DATA * dat, u8 scr, u8 cur, u8 max )
{
	dat->scr = scr;
	dat->cur = cur;
	dat->max = max;
}

//--------------------------------------------------------------------------------------------
/**
 * 表示可能タグセット
 *
 * @param	flg		フラグ設定場所
 * @param	id		タグID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TagPutFlagSet( u32 * flg, u16 id )
{
	flg[id/32] |= (1<<(id%32));
}

//--------------------------------------------------------------------------------------------
/**
 * 表示可能タグチェック
 *
 * @param	flg		フラグ設定場所
 * @param	id		タグID
 *
 * @retval	"TRUE = 可"
 * @retval	"FALSE = 不可"
 */
//--------------------------------------------------------------------------------------------
u8 TagPutFlagGet( u32 * flg, u16 id )
{
	if( ( flg[id/32] & (1<<(id%32)) ) != 0 ){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * 現在の表示位置取得
 *
 * @param	dat		データ設定場所
 *
 * @return	表示位置
 */
//--------------------------------------------------------------------------------------------
void TagPosGet( NTAG_DATA * dat, u8 * scr, u8 * cur )
{
	*scr = dat->scr;
	*cur = dat->cur;
}


