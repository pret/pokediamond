//=============================================================================
/**
 * @file	myitem.c
 * @brief	手持ちアイテム操作用
 * @author	tamada
 * @author	hiroyuki nakamura
 * @date	2005.10.13
 */
//=============================================================================

#include "common.h"
#include "gflib/system.h"

#include "system/gamedata.h"

#include "itemtool/myitem.h"
#include "itemtool/item.h"

#include "system/savedata.h"		//SaveData_Get & GMDATA_ID_TEMOTI_ITEM

#include "system/procsys.h"
#include "application/bag.h"


//=============================================================================
//=============================================================================
//------------------------------------------------------------------
/**
 * @brief	手持ちアイテム構造体の定義
 */
//------------------------------------------------------------------
struct _MYITEM {
	MINEITEM MyNormalItem[ BAG_NORMAL_ITEM_MAX ];	// 手持ちの普通の道具
	MINEITEM MyEventItem[ BAG_EVENT_ITEM_MAX ];		// 手持ちの大切な道具
	MINEITEM MySkillItem[ BAG_WAZA_ITEM_MAX ];		// 手持ちの技マシン
	MINEITEM MySealItem[ BAG_SEAL_ITEM_MAX ];		// 手持ちのシール
	MINEITEM MyDrugItem[ BAG_DRUG_ITEM_MAX ];		// 手持ちの薬
	MINEITEM MyNutsItem[ BAG_NUTS_ITEM_MAX ];		// 手持ちの木の実
	MINEITEM MyBallItem[ BAG_BALL_ITEM_MAX ];		// 手持ちのモンスターボール
	MINEITEM MyBattleItem[ BAG_BATTLE_ITEM_MAX ];	// 手持ちの戦闘用アイテム
	u32	cnv_button;									// 便利ボタン
};

// フィールドのバッグのカーソル位置
typedef struct {
	u8	scr[8];
	u8	pos[8];
	u16	pocket;
	u16	dummy;
}FLDBAG_CURSOR;

// 戦闘のバッグのカーソル位置
typedef struct {
	u8	scr[5];
	u8	pos[5];
	u16	item;
	u16	page;
	u16	pocket;		// ポケットページの位置
}BTLBAG_CURSOR;

// バッグのカーソル位置データ
struct _BAG_CURSOR {
	FLDBAG_CURSOR	fld;
	BTLBAG_CURSOR	btl;
};



#define	ITEM_CHECK_ERR	( 0xffffffff )		// チェックエラー

#define	ITEM_MAX_NORMAL			( 999 )		// 通常のアイテム所持数最大
#define	ITEM_MAX_WAZAMACHINE	( 99 )		// 技マシンの所持数最大

static u32 MyItemDataGet( MYITEM * myitem, u16 id, MINEITEM ** item, u32 * max, u32 heap );



//=============================================================================
//=============================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------
int MyItem_GetWorkSize(void)
{
	return sizeof(MYITEM);
}

//------------------------------------------------------------------
/**
 * @brief	手持ちアイテムワークを生成する
 * @param	myitem	手持ちアイテム構造体へのポインタ
 * @return	MYITEMへのポインタ
 */
//------------------------------------------------------------------
MYITEM * MyItem_AllocWork(int heapID)
{
	MYITEM * item;
	item = sys_AllocMemory(heapID, sizeof(MYITEM));
	MyItem_Init(item);
	return item;
}

//------------------------------------------------------------------
/**
 * @brief	初期化処理
 * @param	item	MYITEMへのポインタ
 */
//------------------------------------------------------------------
void MyItem_Init(MYITEM * item)
{
	MI_CpuClear16(item, sizeof(MYITEM));
}

//------------------------------------------------------------------
/**
 * @brief	MYITEMのコピー
 * @param	from	コピー元へのポインタ
 * @param	to		コピー先へのポインタ
 */
//------------------------------------------------------------------
void MyItem_Copy(const MYITEM * from, MYITEM * to)
{
	MI_CpuCopy8(from, to, sizeof(MYITEM));
}

//------------------------------------------------------------------
/**
 * @brief	便利ボタンに割り当てられているアイテム取得
 * @param	myitem	MYITEMへのポインタ
 * @return	アイテム番号
 */
//------------------------------------------------------------------
u32 MyItem_CnvButtonItemGet( const MYITEM * myitem )
{
	return myitem->cnv_button;
}

//------------------------------------------------------------------
/**
 * @brief	便利ボタンにアイテムセット
 * @param	myitem	MYITEMへのポインタ
 * @param	setitem	セットするアイテム
 * @return	アイテム番号
 */
//------------------------------------------------------------------
void MyItem_CnvButtonItemSet( MYITEM * myitem, u32 setitem )
{
	myitem->cnv_button = setitem;
}

//------------------------------------------------------------------
/**
 * @brief	MYITEMと最大数取得
 * @param	id		アイテム番号
 * @param	item	MYITEM取得場所
 * @param	max		最大数取得場所
 * @param	heap		ヒープID
 * @return	ポケット番号
 */
//------------------------------------------------------------------
static u32 MyItemDataGet( MYITEM * myitem, u16 id, MINEITEM ** item, u32 * max, u32 heap )
{
	u32	pocket = ItemParamGet( id, ITEM_PRM_POCKET, heap );

	switch( pocket ){
	case BAG_POKE_EVENT:	// 大切な物
		*item = myitem->MyEventItem;
		*max = BAG_EVENT_ITEM_MAX;
		break;
	case BAG_POKE_NORMAL:	// 道具
		*item = myitem->MyNormalItem;
		*max = BAG_NORMAL_ITEM_MAX;
		break;
	case BAG_POKE_NUTS:		// 木の実
		*item = myitem->MyNutsItem;
		*max = BAG_NUTS_ITEM_MAX;
		break;
	case BAG_POKE_DRUG:		// 薬
		*item = myitem->MyDrugItem;
		*max = BAG_DRUG_ITEM_MAX;
		break;
	case BAG_POKE_BALL:		// ボール
		*item = myitem->MyBallItem;
		*max = BAG_BALL_ITEM_MAX;
		break;
	case BAG_POKE_BATTLE:	// 戦闘用
		*item = myitem->MyBattleItem;
		*max = BAG_BATTLE_ITEM_MAX;
		break;
	case BAG_POKE_SEAL:		// シール
		*item = myitem->MySealItem;
		*max = BAG_SEAL_ITEM_MAX;
		break;
	case BAG_POKE_WAZA:		// 技マシン
		*item = myitem->MySkillItem;
		*max = BAG_WAZA_ITEM_MAX;
		break;
	}
	return pocket;
}


//------------------------------------------------------------------
/**
 * @brief	加えるアイテムをチェック
 * @param	item		手持ちアイテム構造体へのポインタ
 * @param	siz			手持ちアイテム構造体のサイズ（個数）
 * @param	id			指定するアイテムのナンバー
 * @param	num			加えるアイテムの個数
 * @param	max			アイテム最大数
 * @retval	成功 = アイテム位置
 * @retval	失敗 = NULL
 */
//------------------------------------------------------------------
static MINEITEM * AddItemSearch( MINEITEM * item, u32 siz, u16 id, u16 num, u16 max )
{
	u32	i;
	u32	pos = ITEM_CHECK_ERR;

	for( i=0; i<siz; i++ ){
		if( item[i].id == id ){
			if( ( item[i].no + num ) > max ){
				return NULL;
			}
			return &item[i];
		}
		if( pos == ITEM_CHECK_ERR ){
			if( item[i].id == 0 && item[i].no == 0 ){
				pos = i;
			}
		}
	}

	if( pos == ITEM_CHECK_ERR ){
		return NULL;
	}
	return &item[pos];
}

//------------------------------------------------------------------
/**
 * @brief	アイテムを加える場所を取得
 * @param	myitem		手持ちアイテム構造体へのポインタ
 * @param	item_no		指定するアイテムのナンバー
 * @param	num			アイテムの個数
 * @param	heap		ヒープID
 * @retval	成功 = アイテム位置
 * @retval	失敗 = NULL
 */
//------------------------------------------------------------------
static MINEITEM * AddItemPosGet( MYITEM * myitem, u16 item_no, u16 num, u32 heap )
{
	MINEITEM * add;
	u32	max;
	u32	pocket;

	pocket = MyItemDataGet( myitem, item_no, &add, &max, heap );
	if( pocket == BAG_POKE_WAZA ){
		return AddItemSearch( add, max, item_no, num, ITEM_MAX_WAZAMACHINE );
	}
	return AddItemSearch( add, max, item_no, num, ITEM_MAX_NORMAL );
}

//------------------------------------------------------------------
/**
 * @brief	手持ちにアイテムを加えられるかチェック
 * @param	myitem		手持ちアイテム構造体へのポインタ
 * @param	item_no		指定するアイテムのナンバー
 * @param	num			アイテムの個数
 * @param	heap		ヒープID
 * @retval	TRUE	成功
 * @retval	FALSE	失敗
 */
//------------------------------------------------------------------
BOOL MyItem_AddCheck( MYITEM * myitem, u16 item_no, u16 num, u32 heap )
{
	if( AddItemPosGet( myitem, item_no, num, heap ) == NULL ){
		return FALSE;
	}
	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	手持ちにアイテムを加える
 * @param	myitem		手持ちアイテム構造体へのポインタ
 * @param	item_no		指定するアイテムのナンバー
 * @param	num			アイテムの個数
 * @param	heap		ヒープID
 * @retval	TRUE	成功
 * @retval	FALSE	失敗
 */
//------------------------------------------------------------------
BOOL MyItem_AddItem( MYITEM * myitem, u16 item_no, u16 num, u32 heap )
{
	MINEITEM * add = AddItemPosGet( myitem, item_no, num, heap );

	if( add == NULL ){ return FALSE; }

	add->id = item_no;
	add->no += num;

	{
		u32	pocket;
		u32	max;
		pocket = MyItemDataGet( myitem, item_no, &add, &max, heap );
		if( pocket == BAG_POKE_NUTS || pocket == BAG_POKE_WAZA ){
			MyItem_SortNumber( add, max );
		}
	}

	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	取り除くアイテムをチェック
 * @param	item		手持ちアイテム構造体へのポインタ
 * @param	siz			手持ちアイテム構造体のサイズ（個数）
 * @param	id			指定するアイテムのナンバー
 * @param	num			アイテムの個数
 * @retval	成功 = アイテム位置
 * @retval	失敗 = NULL
 */
//------------------------------------------------------------------
static MINEITEM * SubItemSearch( MINEITEM * item, u32 siz, u16 id, u16 num )
{
	u32	i;

	for( i=0; i<siz; i++ ){
		if( item[i].id == id ){
			if( item[i].no >= num ){
				return &item[i];
			}else{
				return NULL;
			}
		}
	}
	return NULL;
}

//------------------------------------------------------------------
/**
 * @brief	アイテムを取り除く場所を取得
 * @param	myitem		手持ちアイテム構造体へのポインタ
 * @param	item_no		指定するアイテムのナンバー
 * @param	num			アイテムの個数
 * @param	heap		ヒープID
 * @retval	成功 = アイテム位置
 * @retval	失敗 = NULL
 */
//------------------------------------------------------------------
static MINEITEM * SubItemPosGet( MYITEM * myitem, u16 item_no, u16 num, u32 heap )
{
	MINEITEM * sub;
	u32	max;

	MyItemDataGet( myitem, item_no, &sub, &max, heap );
	return SubItemSearch( sub, max, item_no, num );

/*
	switch( ItemParamGet( item_no, ITEM_PRM_POCKET, heap ) ){
	case BAG_POKE_EVENT:	// 大切な物
		sub = SubItemSearch( myitem->MyEventItem, BAG_EVENT_ITEM_MAX, item_no, num );
		break;
	case BAG_POKE_NORMAL:	// 道具
		sub = SubItemSearch( myitem->MyNormalItem, BAG_NORMAL_ITEM_MAX, item_no, num );
		break;
	case BAG_POKE_NUTS:		// 木の実
		sub = SubItemSearch( myitem->MyNutsItem, BAG_NUTS_ITEM_MAX, item_no, num );
		break;
	case BAG_POKE_DRUG:		// 薬
		sub = SubItemSearch( myitem->MyDrugItem, BAG_DRUG_ITEM_MAX, item_no, num );
		break;
	case BAG_POKE_BALL:		// ボール
		sub = SubItemSearch( myitem->MyBallItem, BAG_BALL_ITEM_MAX, item_no, num );
		break;
	case BAG_POKE_BATTLE:	// 戦闘用
		sub = SubItemSearch( myitem->MyBattleItem, BAG_BATTLE_ITEM_MAX, item_no, num );
		break;
	case BAG_POKE_SEAL:		// シール
		sub = SubItemSearch( myitem->MySealItem, BAG_SEAL_ITEM_MAX, item_no, num );
		break;
	case BAG_POKE_WAZA:		// 技マシン
		sub = SubItemSearch( myitem->MySkillItem, BAG_WAZA_ITEM_MAX, item_no, num );
		break;
	default:
		return NULL;
	}

	return sub;
*/

}

//------------------------------------------------------------------
/**
 * @brief	手持ちからアイテムを取り除く
 * @param	myitem		手持ちアイテム構造体へのポインタ
 * @param	item_no		指定するアイテムのナンバー
 * @param	num			アイテムの個数
 * @param	heap		ヒープID
 * @retval	TRUE	成功
 * @retval	FALSE	失敗
 */
//------------------------------------------------------------------
BOOL MyItem_SubItem( MYITEM * myitem, u16 item_no, u16 num, u32 heap )
{
	MINEITEM * sub = SubItemPosGet( myitem, item_no, num, heap );

	if( sub == NULL ){ return FALSE; }

	sub->no -= num;
	if( sub->no == 0 ){
		sub->id = 0;
	}

	{
		u32	max;

		MyItemDataGet( myitem, item_no, &sub, &max, heap );
		MyItem_SortSpace( sub, max );
	}

	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	手持ちからアイテムを取り除く（ポケット指定）
 * @param	myitem		手持ちアイテム構造体へのポインタ
 * @param	max			検索数
 * @param	item_no		指定するアイテムのナンバー
 * @param	num			アイテムの個数
 * @param	heap		ヒープID
 * @retval	TRUE	成功
 * @retval	FALSE	失敗
 */
//------------------------------------------------------------------
BOOL MyItem_SubItemDirect( MINEITEM * myitem, u32 max, u16 item_no, u16 num, u32 heap )
{
	MINEITEM * sub = SubItemSearch( myitem, max, item_no, num );

	if( sub == NULL ){ return FALSE; }

	sub->no -= num;
	if( sub->no == 0 ){
		sub->id = 0;
	}

	MyItem_SortSpace( myitem, max );

	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	手持ちアイテム内での存在チェック
 * @param	myitem		手持ちアイテム構造体へのポインタ
 * @param	item_no		指定するアイテムのナンバー
 * @param	num			アイテムの個数
 * @param	heap		ヒープID
 * @retval	TRUE	存在する
 * @retval	FALSE	存在しない
 */
//------------------------------------------------------------------
BOOL MyItem_CheckItem( MYITEM * myitem, u16 item_no, u16 num, u32 heap )
{
	if( SubItemPosGet( myitem, item_no, num, heap ) == NULL ){
		return FALSE;
	}
	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	ポケットにアイテムが存在するかチェック
 * @param	myitem		手持ちアイテム構造体へのポインタ
 * @param	pocket		ポケット番号
 * @retval	TRUE	存在する
 * @retval	FALSE	存在しない
 */
//------------------------------------------------------------------
BOOL MyItem_CheckItemPocket( MYITEM * myitem, u32 pocket )
{
	MINEITEM * item;
	u32	max;
	u32	i;

	switch( pocket ){
	case BAG_POKE_EVENT:	// 大切な物
		item = myitem->MyEventItem;
		max  = BAG_EVENT_ITEM_MAX;
		break;
	case BAG_POKE_NORMAL:	// 道具
		item = myitem->MyNormalItem;
		max  = BAG_NORMAL_ITEM_MAX;
		break;
	case BAG_POKE_NUTS:		// 木の実
		item = myitem->MyNutsItem;
		max  = BAG_NUTS_ITEM_MAX;
		break;
	case BAG_POKE_DRUG:		// 薬
		item = myitem->MyDrugItem;
		max  = BAG_DRUG_ITEM_MAX;
		break;
	case BAG_POKE_BALL:		// ボール
		item = myitem->MyBallItem;
		max  = BAG_BALL_ITEM_MAX;
		break;
	case BAG_POKE_BATTLE:	// 戦闘用
		item = myitem->MyBattleItem;
		max  = BAG_BATTLE_ITEM_MAX;
		break;
	case BAG_POKE_SEAL:		// シール
		item = myitem->MySealItem;
		max  = BAG_SEAL_ITEM_MAX;
		break;
	case BAG_POKE_WAZA:		// 技マシン
		item = myitem->MySkillItem;
		max  = BAG_WAZA_ITEM_MAX;
		break;
	default:
		return FALSE;
	}

	for( i=0; i<max; i++ ){
		if( item[i].id != 0 ){ return TRUE; }
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	手持ちの個数チェック
 * @param	myitem		手持ちアイテム構造体へのポインタ
 * @param	item_no		指定するアイテムのナンバー
 * @param	heap		ヒープID
 * @return	手持ち数
 */
//------------------------------------------------------------------
u16 MyItem_GetItemNum( MYITEM * myitem, u16 item_no, u32 heap )
{
	MINEITEM * sub = SubItemPosGet( myitem, item_no, 1, heap );

	if( sub == NULL ){
		return 0;
	}
	return sub->no;
}

//------------------------------------------------------------------
/**
 * @brief	手持ちの個数チェック（ポケット指定）
 * @param	myitem		手持ちアイテム構造体へのポインタ
 * @param	max			検索数
 * @param	item_no		指定するアイテムのナンバー
 * @param	num			アイテムの個数
 * @param	heap		ヒープID
 * @retval	TRUE	成功
 * @retval	FALSE	失敗
 */
//------------------------------------------------------------------
u16 MyItem_GetItemNumDirect( MINEITEM * myitem, u32 max, u16 item_no, u32 heap )
{
	MINEITEM * sub = SubItemSearch( myitem, max, item_no, 1 );

	if( sub == NULL ){ return 0; }

	return sub->no;
}

//------------------------------------------------------------------
/**
 * @brief	指定個所のアイテムを入れ替え
 * @param	p1		入れ替えるデータ1
 * @param	p2		入れ替えるデータ2
 * @return	none
 */
//------------------------------------------------------------------
static void ChengeItem( MINEITEM * p1, MINEITEM * p2 )
{
	MINEITEM	copy;

	copy = *p1;
	*p1  = *p2;
	*p2  = copy;
}

//------------------------------------------------------------------
/**
 * @brief	アイテムソート（スペースをつめる）
 * @param	item	アイテムデータ
 * @param	max		最大値
 * @return	none
 */
//------------------------------------------------------------------
void MyItem_SortSpace( MINEITEM * item, const u32 max )
{
	u32	i, j;

	for( i=0; i<max-1; i++ ){
		for( j=i+1; j<max; j++ ){
			if( item[i].no == 0 ){
				ChengeItem( &item[i], &item[j] );
			}
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief	アイテムソート（番号順）
 * @param	p	ポケットデータ
 * @param	max		最大値
 * @return	none
 */	
//------------------------------------------------------------------
void MyItem_SortNumber( MINEITEM * item, const u32 max )
{
	u32	i, j;

	for( i=0; i<max-1; i++ ){
		for( j=i+1; j<max; j++ ){
			if( item[i].no == 0 || ( item[j].no != 0 && item[i].id > item[j].id ) ){
				ChengeItem( &item[i], &item[j] );
			}
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief	バッグのデータ作成
 * @param	myitem		手持ちアイテム構造体へのポインタ
 * @param	list		ポケットリスト
 * @param	heap		ヒープID
 */
//------------------------------------------------------------------
void * MyItem_MakeBagData( MYITEM * myitem, const u8 * list, u32 heap )
{
	BAG_DATA * bag;
	int i;

	bag = BagSystemDataAlloc( heap );
	for( i=0; list[i] != 0xff; i++ ){
		switch( list[i] ){
		case BAG_POKE_EVENT:
			BagPocketDataMake( bag, myitem->MyEventItem, BAG_POKE_EVENT, i );
			break;
		case BAG_POKE_NORMAL:
			BagPocketDataMake( bag, myitem->MyNormalItem, BAG_POKE_NORMAL, i );
			break;
		case BAG_POKE_NUTS:
			BagPocketDataMake( bag, myitem->MyNutsItem, BAG_POKE_NUTS, i );
			break;
		case BAG_POKE_DRUG:
			BagPocketDataMake( bag, myitem->MyDrugItem, BAG_POKE_DRUG, i );
			break;
		case BAG_POKE_BALL:
			BagPocketDataMake( bag, myitem->MyBallItem, BAG_POKE_BALL, i );
			break;
		case BAG_POKE_BATTLE:
			BagPocketDataMake( bag, myitem->MyBattleItem, BAG_POKE_BATTLE, i );
			break;
		case BAG_POKE_SEAL:
			BagPocketDataMake( bag, myitem->MySealItem, BAG_POKE_SEAL, i );
			break;
		case BAG_POKE_WAZA:
			BagPocketDataMake( bag, myitem->MySkillItem, BAG_POKE_WAZA, i );
			break;
		}
	}
	return bag;
}


//------------------------------------------------------------------
/**
 * @brief	指定ポケットの指定位置のアイテムを取得
 * @param	myitem		手持ちアイテム構造体へのポインタ
 * @param	pocket		ポケットID
 * @param	pos			位置
 * @return	アイテムデータ
 */
//------------------------------------------------------------------
MINEITEM * MyItem_PosItemGet( MYITEM * myitem, u16 pocket, u16 pos )
{
	MINEITEM * item;
	u16	max;

	switch( pocket ){
	case BAG_POKE_EVENT:	// 大切な物
		item = myitem->MyEventItem;
		max  = BAG_EVENT_ITEM_MAX;
		break;
	case BAG_POKE_NORMAL:	// 道具
		item = myitem->MyNormalItem;
		max  = BAG_NORMAL_ITEM_MAX;
		break;
	case BAG_POKE_NUTS:		// 木の実
		item = myitem->MyNutsItem;
		max  = BAG_NUTS_ITEM_MAX;
		break;
	case BAG_POKE_DRUG:		// 薬
		item = myitem->MyDrugItem;
		max  = BAG_DRUG_ITEM_MAX;
		break;
	case BAG_POKE_BALL:		// ボール
		item = myitem->MyBallItem;
		max  = BAG_BALL_ITEM_MAX;
		break;
	case BAG_POKE_BATTLE:	// 戦闘用
		item = myitem->MyBattleItem;
		max  = BAG_BATTLE_ITEM_MAX;
		break;
	case BAG_POKE_SEAL:		// シール
		item = myitem->MySealItem;
		max  = BAG_SEAL_ITEM_MAX;
		break;
	case BAG_POKE_WAZA:		// 技マシン
		item = myitem->MySkillItem;
		max  = BAG_WAZA_ITEM_MAX;
		break;
	}

	if( pos >= max ){ return NULL; }

	return &item[pos];
}


//------------------------------------------------------------------
/**
 * @brief	セーブデータから手持ちアイテムへのポインタを取得する
 * @param	sv	セーブデータへのポインタ
 * @return	セーブデータ中のMYITEMへのポインタ
 */
//------------------------------------------------------------------
MYITEM * SaveData_GetMyItem(SAVEDATA * sv)
{
	MYITEM * myitem;
	myitem = (MYITEM *)SaveData_Get(sv, GMDATA_ID_TEMOTI_ITEM);
	return myitem;
}

//------------------------------------------------------------------
/**
 * @brief	デバッグ用：適当に手持ちを生成する
 * @param	myitem	手持ちアイテム構造体へのポインタ
 */
//------------------------------------------------------------------
static const MINEITEM DebugItem[] = {
	{ ITEM_MASUTAABOORU,	111 },
	{ ITEM_MONSUTAABOORU,	222 },
	{ ITEM_SUUPAABOORU,		333 },
	{ ITEM_HAIPAABOORU,		444 },
	{ ITEM_PUREMIABOORU,	555 },
	{ ITEM_DAIBUBOORU,		666 },
	{ ITEM_TAIMAABOORU,		777 },
	{ ITEM_RIPIITOBOORU,	888 },
	{ ITEM_NESUTOBOORU,		999 },
	{ ITEM_GOOZYASUBOORU,	100 },
	{ ITEM_KIZUGUSURI,		123 },
	{ ITEM_NEMUKEZAMASI,	456 },
	{ ITEM_TAUNMAPPU,		1 },
	{ ITEM_TANKENSETTO,		1 },
	{ ITEM_ZITENSYA,		1 },
	{ ITEM_NANDEMONAOSI,	18 },
	{ ITEM_PIIPIIRIKABAA,	18 },
	{ ITEM_PIIPIIMAKKUSU,	18 },
	{ ITEM_DOKUKESI,		18 },		// どくけし
	{ ITEM_YAKEDONAOSI,		19 },		// やけどなおし
	{ ITEM_KOORINAOSI,		20 },		// こおりなおし
	{ ITEM_MAHINAOSI,		22 },		// まひなおし
	{ ITEM_EFEKUTOGAADO,	54 },		// エフェクトガード
	{ ITEM_KURITHIKATTAA,	55 },		// クリティカッター
	{ ITEM_PURASUPAWAA,		56 },		// プラスパワー
	{ ITEM_DHIFENDAA,		57 },		// ディフェンダー
	{ ITEM_SUPIIDAA,		58 },		// スピーダー
	{ ITEM_YOKUATAARU,		59 },		// ヨクアタール
	{ ITEM_SUPESYARUAPPU,	60 },		// スペシャルアップ
	{ ITEM_SUPESYARUGAADO,	61 },		// スペシャルガード
	{ ITEM_PIPPININGYOU,	62 },		// ピッピにんぎょう
	{ ITEM_ENEKONOSIPPO,	63 },		// エネコのシッポ
	{ ITEM_GENKINOKAKERA,	28 },		// げんきのかけら
	{ ITEM_KAIHUKUNOKUSURI,	28 },		// げんきのかけら
	{ ITEM_PIIPIIEIDO,	28 },
	{ ITEM_PIIPIIEIDAA,	28 },
	{ ITEM_DAAKUBOORU,	13 },		// ダークボール
	{ ITEM_HIIRUBOORU,  14 },		// ヒールボール
	{ ITEM_KUIKKUBOORU,	15 },		// クイックボール
	{ ITEM_PURESYASUBOORU,	16 },	// プレシアボール
	{ ITEM_TOMODATITETYOU,  1},  // ともだち手帳
};

void Debug_MyItem_MakeBag(MYITEM * myitem, int heapID)
{
	u32	i;

	memset( myitem->MyEventItem, 0, sizeof(MINEITEM) * BAG_EVENT_ITEM_MAX );
	memset( myitem->MyNormalItem, 0, sizeof(MINEITEM) * BAG_NORMAL_ITEM_MAX );
	memset( myitem->MyNutsItem, 0, sizeof(MINEITEM) * BAG_NUTS_ITEM_MAX );
	memset( myitem->MyDrugItem, 0, sizeof(MINEITEM) * BAG_DRUG_ITEM_MAX );
	memset( myitem->MyBallItem, 0, sizeof(MINEITEM) * BAG_BALL_ITEM_MAX );
	memset( myitem->MyBattleItem, 0, sizeof(MINEITEM) * BAG_BATTLE_ITEM_MAX );
	memset( myitem->MySealItem, 0, sizeof(MINEITEM) * BAG_SEAL_ITEM_MAX );
	memset( myitem->MySkillItem, 0, sizeof(MINEITEM) * BAG_WAZA_ITEM_MAX );

	for( i=0; i<NELEMS(DebugItem); i++ ){
		MyItem_AddItem( myitem, DebugItem[i].id, DebugItem[i].no, heapID );
	}
}


//------------------------------------------------------------------
/**
 * @brief	バッグのカーソル位置データ確保
 * @param	heapID	ヒープID
 * @return	カーソル位置データ
 */
//------------------------------------------------------------------
BAG_CURSOR * MyItem_BagCursorAlloc( u32 heapID )
{
	BAG_CURSOR * cursor;

	cursor = sys_AllocMemory( heapID, sizeof(BAG_CURSOR) );
	MI_CpuClear16( cursor, sizeof(BAG_CURSOR) );
	return cursor;
}

//------------------------------------------------------------------
/**
 * @brief	フィールドバッグのカーソル位置取得
 * @param	wk		カーソルデータ
 * @param	pocket	ポケットID
 * @param	pos		カーソル位置取得場所
 * @param	scr		スクロールカウンタ取得場所
 * @return	none
 */
//------------------------------------------------------------------
void MyItem_FieldBagCursorGet( BAG_CURSOR * wk, u32 pocket, u8 * pos, u8 * scr )
{
	*pos = wk->fld.pos[pocket];
	*scr = wk->fld.scr[pocket];
}

//------------------------------------------------------------------
/**
 * @brief	フィールドバッグのポケット位置取得
 * @param	wk		カーソルデータ
 * @return	none
 */
//------------------------------------------------------------------
u16 MyItem_FieldBagPocketGet( BAG_CURSOR * wk )
{
	return wk->fld.pocket;
}

//------------------------------------------------------------------
/**
 * @brief	フィールドバッグのカーソル位置セット
 * @param	wk		カーソルデータ
 * @param	pocket	ポケットID
 * @param	pos		カーソル位置
 * @param	scr		スクロールカウンタ
 * @return	none
 */
//------------------------------------------------------------------
void MyItem_FieldBagCursorSet( BAG_CURSOR * wk, u32 pocket, u8 pos, u8 scr )
{
	wk->fld.pos[pocket] = pos;
	wk->fld.scr[pocket] = scr;
}

//------------------------------------------------------------------
/**
 * @brief	フィールドバッグのポケット位置セット
 * @param	wk		カーソルデータ
 * @param	pocket	ポケットID
 * @return	none
 */
//------------------------------------------------------------------
void MyItem_FieldBagPocketSet( BAG_CURSOR * wk, u16 pocket )
{
	wk->fld.pocket = pocket;
}

//------------------------------------------------------------------
/**
 * @brief	戦闘バッグのカーソル位置取得
 * @param	wk		カーソルデータ
 * @param	pocket	ポケットID
 * @param	pos		カーソル位置取得場所
 * @param	scr		スクロールカウンタ取得場所
 * @return	none
 */
//------------------------------------------------------------------
void MyItem_BattleBagCursorGet( BAG_CURSOR * wk, u32 pocket, u8 * pos, u8 * scr )
{
	*pos = wk->btl.pos[pocket];
	*scr = wk->btl.scr[pocket];
}

//------------------------------------------------------------------
/**
 * @brief	戦闘バッグの最後に使った道具取得
 * @param	wk		カーソルデータ
 * @return	最後に使った道具
 */
//------------------------------------------------------------------
u16 MyItem_BattleBagLastItemGet( BAG_CURSOR * wk )
{
	return wk->btl.item;
}

//------------------------------------------------------------------
/**
 * @brief	戦闘バッグの最後に使った道具のポケット取得
 * @param	wk		カーソルデータ
 * @return	最後に使った道具のポケット
 */
//------------------------------------------------------------------
u16 MyItem_BattleBagLastPageGet( BAG_CURSOR * wk )
{
	return wk->btl.page;
}

//------------------------------------------------------------------
/**
 * @brief	戦闘バッグのポケットページのカーソル位置取得
 * @param	wk		カーソルデータ
 * @return	最後に使った道具
 */
//------------------------------------------------------------------
u16 MyItem_BattleBagPocketPagePosGet( BAG_CURSOR * wk )
{
	return wk->btl.pocket;
}

//------------------------------------------------------------------
/**
 * @brief	戦闘バッグのカーソル位置セット
 * @param	wk		カーソルデータ
 * @param	pocket	ポケットID
 * @param	pos		カーソル位置
 * @param	scr		スクロールカウンタ
 * @return	none
 */
//------------------------------------------------------------------
void MyItem_BattleBagCursorSet( BAG_CURSOR * wk, u32 pocket, u8 pos, u8 scr )
{
	wk->btl.pos[pocket] = pos;
	wk->btl.scr[pocket] = scr;
}

//------------------------------------------------------------------
/**
 * @brief	戦闘バッグのカーソル位置初期化
 * @param	wk		カーソルデータ
 * @return	none
 */
//------------------------------------------------------------------
void MyItem_BattleBagCursorPosInit( BAG_CURSOR * wk )
{
	u32	i;

	for( i=0; i<5; i++ ){
		MyItem_BattleBagCursorSet( wk, i, 0, 0 );
	}
	MyItem_BattleBagPocketPagePosSet( wk, 0 );
}

//------------------------------------------------------------------
/**
 * @brief	戦闘バッグの最後に使った道具をセット
 * @param	wk		カーソルデータ
 * @param	item	最後に使ったアイテム
 * @param	page	最後に使ったアイテムのページ
 * @return	none
 */
//------------------------------------------------------------------
void MyItem_BattleBagLastItemSet( BAG_CURSOR * wk, u16 item, u16 page )
{
	wk->btl.item = item;
	wk->btl.page = page;
}

//------------------------------------------------------------------
/**
 * @brief	戦闘バッグのポケットページのカーソル位置セット
 * @param	wk		カーソルデータ
 * @return	最後に使った道具
 */
//------------------------------------------------------------------
void MyItem_BattleBagPocketPagePosSet( BAG_CURSOR * wk, u16 pocket )
{
	wk->btl.pocket = pocket;
}

// 外部参照インデックスを作る時のみ有効(ゲーム中は無効)
#ifdef CREATE_INDEX
void *Index_Get_Myitem_Offset(MYITEM *item, int type)
{
  switch(type){
  case BAG_POKE_NORMAL: return item->MyNormalItem; break;
  case BAG_POKE_EVENT: return item->MyEventItem; break;
  case BAG_POKE_WAZA: return item->MySkillItem; break;
  case BAG_POKE_SEAL: return item->MySealItem; break;
  case BAG_POKE_DRUG: return item->MyDrugItem; break;
  case BAG_POKE_NUTS: return item->MyNutsItem; break;
  case BAG_POKE_BALL: return item->MyBallItem; break;
  case BAG_POKE_BATTLE: return item->MyBattleItem; break;
  }
}
#endif
