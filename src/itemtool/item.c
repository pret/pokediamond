//============================================================================================
/**
 * @file	item.c
 * @brief	アイテムデータ処理
 * @author	Hiroyuki Nakamura
 * @date	05.09.06
 */
//============================================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/gamedata.h"
#include "system/msgdata.h"
#include "battle/wazano_def.h"

#include "msgdata\msg.naix"
#include "msgdata\msg_iteminfo.h"

#include "itemtool/myitem.h"

#define	ITEM_H_GLOBAL
#include "itemtool/item.h"
#include "itemdata.h"
#include "agb_itemsym.h"
#include "item_data.naix"
#include "item_icon.naix"


//============================================================================================
//	定数定義
//============================================================================================
typedef struct {
	u16	arc_data;
	u16	arc_cgx;
	u16	arc_pal;
	u16	agb_id;
}ITEMDATA_INDEX;

#define	NORMAL_WAZAMACHINE_MAX	( 92 )		// 通常の技マシン数
#define	HIDENWAZA_MAX			( 8 )		// 秘伝技数


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static s32 ItemParamRcvGet( ITEMPARAM_RCV * rcv, u16 param );


//============================================================================================
//	グローバル変数
//============================================================================================
#include "itemindex.dat"
#include "waza_mcn.dat"
#include "itemtype.dat"


//--------------------------------------------------------------------------------------------
/**
 * 指定アイテムを指定位置に挿入
 *
 * @param	item	アイテムデータ
 * @param	pos1	指定アイテム位置
 * @param	pos2	挿入位置
 *
 * @return	none
 */	
//--------------------------------------------------------------------------------------------
void ItemPutIn( void * item, u16 pos1, u16 pos2 )
{
	MINEITEM * data;
	MINEITEM copy;
	s16	i;

	if( pos1 == pos2 ){ return; }

	data = (MINEITEM *)item;
	copy = data[pos1];

	if( pos2 > pos1 ){
		pos2 -= 1;
		for( i=(s16)pos1; i<(s16)pos2; i++ ){
			data[i] = data[i+1];
		}
	}else{
		for( i=(s16)pos1; i>(s16)pos2; i-- ){
			data[i] = data[i-1];
		}

	}
	data[pos2] = copy;
}


//============================================================================================
//============================================================================================
//	データ取得
//============================================================================================
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * データインデックス取得
 *
 * @param	item		アイテム番号
 * @param	type		取得データ
 *
 * @return	指定データ
 *
 * @li	type = ITEM_GET_DATA		: アイテムデータのアーカイブインデックス
 * @li	type = ITEM_GET_ICON_CGX	: アイコンキャラのアーカイブインデックス
 * @li	type = ITEM_GET_ICON_PAL	: アイコンパレットのアーカイブインデックス
 * @li	type = ITEM_GET_AGB_NUM		: AGBのアイテム番号
 */
//--------------------------------------------------------------------------------------------
u16 GetItemIndex( u16 item, u16 type )
{
	switch( type ){
	case ITEM_GET_DATA:		// アイテムデータ
		if( item == ITEM_DUMMY_ID || item == ITEM_RETURN_ID ){ break; }
		return ItemDataIndex[item].arc_data;

	case ITEM_GET_ICON_CGX:	// アイコンキャラデータ
		if( item == ITEM_DUMMY_ID ){ return NARC_item_icon_item_dumy_NCGR; }
		if( item == ITEM_RETURN_ID ){ return NARC_item_icon_item_yaji_NCGR; }
		return ItemDataIndex[item].arc_cgx;

	case ITEM_GET_ICON_PAL:	// アイコンパレットデータ
		if( item == ITEM_DUMMY_ID ){ return NARC_item_icon_item_dumy_NCLR; }
		if( item == ITEM_RETURN_ID ){ return NARC_item_icon_item_yaji_NCLR; }
		return ItemDataIndex[item].arc_pal;

	case ITEM_GET_AGB_NUM:	// AGBのアイテム番号
		if( item == ITEM_DUMMY_ID || item == ITEM_RETURN_ID ){ break; }
		return ItemDataIndex[item].agb_id;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * AGBのアイテムをDPのアイテムに変換
 *
 * @param	agb		AGBのアイテム番号
 *
 * @retval	"ITEM_DUMMY_ID = DPにないアイテム"
 * @retval	"ITEM_DUMMY_ID != DPのアイテム番号"
 */
//--------------------------------------------------------------------------------------------
u16	ITEM_AgbItemCnv( u16 agb )
{
	u16	i;

	for( i=1; i<=ITEM_DATA_MAX; i++ ){
		if( agb == ItemDataIndex[i].agb_id ){
			return i;
		}
	}
	return ITEM_DUMMY_ID;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムアイコンのセルアーカイブインデックス取得
 *
 * @param	none
 *
 * @return	セルアーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
u16	ItemIconCellGet(void)
{
	return NARC_item_icon_itemicon_NCER;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムアイコンのセルアニメアーカイブインデックス取得
 *
 * @param	none
 *
 * @return	セルアニメアーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
u16	ItemIconCAnmGet(void)
{
	return NARC_item_icon_itemicon_NANR;
}

//--------------------------------------------------------------------------------------------
/**
 * アーカイブデータロード
 *
 * @param	item		アイテム番号
 * @param	type		取得データ
 * @param	heap_id		ヒープID
 *
 * @return	指定データ
 *
 * @li	type = ITEM_GET_DATA		: アイテムデータ
 * @li	type = ITEM_GET_ICON_CGX	: アイコンのキャラデータ
 * @li	type = ITEM_GET_ICON_PAL	: アイコンのパレットデータ
 */
//--------------------------------------------------------------------------------------------
void * GetItemArcData( u16 item, u16 type, u32 heap_id )
{
	if( item > ITEM_DATA_MAX ){ item = 0; }

	switch( type ){
	case ITEM_GET_DATA:		// アイテムデータ
		return ArchiveDataLoadMalloc( ARC_ITEMDATA, ItemDataIndex[item].arc_data, heap_id );
	case ITEM_GET_ICON_CGX:	// アイコンキャラデータ
		return ArchiveDataLoadMalloc( ARC_ITEMICON, ItemDataIndex[item].arc_cgx, heap_id );
	case ITEM_GET_ICON_PAL:	// アイコンパレットデータ
		return ArchiveDataLoadMalloc( ARC_ITEMICON, ItemDataIndex[item].arc_pal, heap_id );
	}
	return NULL;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテム名取得
 *
 * @param   buf			アイテム名格納先バッファ
 * @param   item		アイテム番号
 * @param   heap_id		ヒープID（テンポラリとして使用）
 *
 */
//--------------------------------------------------------------------------------------------
void GetItemName( STRBUF* buf, u16 item, u32 heap_id )
{
	MSGDATA_MANAGER* man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_itemname_dat, heap_id );
	MSGMAN_GetString( man, item, buf );
	MSGMAN_Delete( man );
}

//--------------------------------------------------------------------------------------------
/**
 * 説明取得
 *
 * @param   buf			アイテム名格納先バッファ
 * @param	item		アイテム番号
 * @param	heap_id		ヒープID
 *
 * @return	説明
 */
//--------------------------------------------------------------------------------------------
void ItemInfoGet( STRBUF * buf, u16 item, u16 heap_id )
{
	MSGDATA_MANAGER * man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_iteminfo_dat, heap_id );
	MSGMAN_GetString( man, item, buf );
	MSGMAN_Delete( man );
}

//--------------------------------------------------------------------------------------------
/**
 * 装備説明取得
 *
 * @param   buf			アイテム名格納先バッファ
 * @param	item		アイテム番号
 * @param	heap_id		ヒープID
 *
 * @return	装備説明
 */
//--------------------------------------------------------------------------------------------
void ItemEpuipInfoGet( STRBUF * buf, u16 item, u16 heap_id )
{
	MSGDATA_MANAGER * man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_itemeqp_dat, heap_id );
	MSGMAN_GetString( man, item, buf );
	MSGMAN_Delete( man );
}

//--------------------------------------------------------------------------------------------
/**
 * パラメータ取得（アイテム番号指定）
 *
 * @param	item	アイテム番号
 * @param	param	取得パラメータ定義
 * @param	heap_id		ヒープID
 *
 * @return	指定パラメータ
 */
//--------------------------------------------------------------------------------------------
s32	ItemParamGet( u16 item, u16 param, u32 heap_id )
{
	ITEMDATA * dat;
	s32	ret;
	
	dat = (ITEMDATA *)GetItemArcData( item, ITEM_GET_DATA, heap_id );
	ret = ItemBufParamGet( dat, param );
	sys_FreeMemory( heap_id, dat );

	return ret;
}

//--------------------------------------------------------------------------------------------
/**
 * パラメータ取得（アイテムデータ指定）
 *
 * @param	item	アイテムデータ
 * @param	param	取得パラメータ定義
 *
 * @return	指定パラメータ
 */
//--------------------------------------------------------------------------------------------
s32 ItemBufParamGet( ITEMDATA * item, u16 param )
{
	switch( param ){
	case ITEM_PRM_PRICE:				// 買値
		return (s32)item->price;
	case ITEM_PRM_EQUIP:				// 装備効果
		return (s32)item->eqp;
	case ITEM_PRM_ATTACK:				// 威力
		return (s32)item->atc;
	case ITEM_PRM_EVENT:				// 重要
		return (s32)item->imp;
	case ITEM_PRM_CNV:					// 便利ボタン
		return (s32)item->cnv_btn;
	case ITEM_PRM_POCKET:				// 保存先（ポケット番号）
		return (s32)item->fld_pocket;
	case ITEM_PRM_FIELD:				// field機能
		return (s32)item->field_func;
	case ITEM_PRM_BATTLE:				// battle機能
		return (s32)item->battle_func;
	case ITEM_PRM_TUIBAMU_EFF:			// ついばむ効果
		return (s32)item->tuibamu_eff;
	case ITEM_PRM_NAGETUKERU_EFF:		// なげつける効果
		return (s32)item->nage_eff;
	case ITEM_PRM_NAGETUKERU_ATC:		// なげつける威力
		return (s32)item->nage_atc;
	case ITEM_PRM_SIZENNOMEGUMI_ATC:	// しぜんのめぐみ威力
		return (s32)item->sizen_atc;
	case ITEM_PRM_SIZENNOMEGUMI_TYPE:	// しぜんのめぐみタイプ
		return (s32)item->sizen_type;
	case ITEM_PRM_BTL_POCKET:			// 戦闘保存先（ポケット番号）
		return (s32)item->btl_pocket;
	case ITEM_PRM_W_TYPE:				// ワークタイプ
		return (s32)item->work_type;

	default:							// 汎用ワーク
		switch( item->work_type ){
		case ITEM_WKTYPE_DUMMY:			// 普通データ
			return (s32)item->work[0];
		case ITEM_WKTYPE_POKEUSE:		// ポケモンに使う道具
			return ItemParamRcvGet( (ITEMPARAM_RCV *)item->work, param );
		}
	}

	return 0;
}

static s32 ItemParamRcvGet( ITEMPARAM_RCV * rcv, u16 param )
{
	switch( param ){
	case ITEM_PRM_SLEEP_RCV:			// 眠り回復
		return (s32)rcv->sleep_rcv;
	case ITEM_PRM_POISON_RCV:			// 毒回復
		return (s32)rcv->poison_rcv;
	case ITEM_PRM_BURN_RCV:				// 火傷回復
		return (s32)rcv->burn_rcv;
	case ITEM_PRM_ICE_RCV:				// 氷回復
		return (s32)rcv->ice_rcv;
	case ITEM_PRM_PARALYZE_RCV:			// 麻痺回復
		return (s32)rcv->paralyze_rcv;
	case ITEM_PRM_PANIC_RCV:			// 混乱回復
		return (s32)rcv->panic_rcv;
	case ITEM_PRM_MEROMERO_RCV:			// メロメロ回復
		return (s32)rcv->meromero_rcv;
	case ITEM_PRM_ABILITY_GUARD:		// 能力ガード
		return (s32)rcv->ability_guard;
	case ITEM_PRM_DEATH_RCV:			// 瀕死回復
		return (s32)rcv->death_rcv;
	case ITEM_PRM_ALL_DEATH_RCV:		// 全員瀕死回復
		return (s32)rcv->alldeath_rcv;
	case ITEM_PRM_LV_UP:				// レベルアップ
		return (s32)rcv->lv_up;
	case ITEM_PRM_EVOLUTION:			// 進化
		return (s32)rcv->evolution;
	case ITEM_PRM_ATTACK_UP:			// 攻撃力アップ
		return (s32)rcv->atc_up;
	case ITEM_PRM_DEFENCE_UP:			// 防御力アップ
		return (s32)rcv->def_up;
	case ITEM_PRM_SP_ATTACK_UP:			// 特攻アップ
		return (s32)rcv->spa_up;
	case ITEM_PRM_SP_DEFENCE_UP:		// 特防アップ
		return (s32)rcv->spd_up;
	case ITEM_PRM_AGILITY_UP:			// 素早さアップ
		return (s32)rcv->agi_up;
	case ITEM_PRM_HIT_UP:				// 命中率アップ
		return (s32)rcv->hit_up;
	case ITEM_PRM_CRITICAL_UP:			// クリティカル率アップ
		return (s32)rcv->critical_up;
	case ITEM_PRM_PP_UP:				// PPアップ
		return (s32)rcv->pp_up;
	case ITEM_PRM_PP_3UP:				// PPアップ（３段階）
		return (s32)rcv->pp_3up;
	case ITEM_PRM_PP_RCV:				// PP回復
		return (s32)rcv->pp_rcv;
	case ITEM_PRM_ALL_PP_RCV:			// PP回復（全ての技）
		return (s32)rcv->allpp_rcv;
	case ITEM_PRM_HP_RCV:				// HP回復
		return (s32)rcv->hp_rcv;
	case ITEM_PRM_HP_EXP:				// HP努力値アップ
		return (s32)rcv->hp_exp;
	case ITEM_PRM_POWER_EXP:			// 攻撃努力値アップ
		return (s32)rcv->pow_exp;
	case ITEM_PRM_DEFENCE_EXP:			// 防御努力値アップ
		return (s32)rcv->def_exp;
	case ITEM_PRM_AGILITY_EXP:			// 素早さ努力値アップ
		return (s32)rcv->agi_exp;
	case ITEM_PRM_SP_ATTACK_EXP:		// 特攻努力値アップ
		return (s32)rcv->spa_exp;
	case ITEM_PRM_SP_DEFENCE_EXP:		// 特防努力値アップ
		return (s32)rcv->spd_exp;
	case ITEM_PRM_FRIEND1:				// なつき度１
		return (s32)rcv->friend_exp1;
	case ITEM_PRM_FRIEND2:				// なつき度２
		return (s32)rcv->friend_exp2;
	case ITEM_PRM_FRIEND3:				// なつき度３
		return (s32)rcv->friend_exp3;

	case ITEM_PRM_HP_EXP_POINT:			// HP努力値の値
		return (s32)rcv->prm_hp_exp;
	case ITEM_PRM_POWER_EXP_POINT:		// 攻撃努力値の値
		return (s32)rcv->prm_pow_exp;
	case ITEM_PRM_DEFENCE_EXP_POINT:	// 防御努力値の値
		return (s32)rcv->prm_def_exp;
	case ITEM_PRM_AGILITY_EXP_POINT:	// 素早さ努力値の値
		return (s32)rcv->prm_agi_exp;
	case ITEM_PRM_SP_ATTACK_EXP_POINT:	// 特攻努力値の値
		return (s32)rcv->prm_spa_exp;
	case ITEM_PRM_SP_DEFENCE_EXP_POINT:	// 特防努力値の値
		return (s32)rcv->prm_spd_exp;
	case ITEM_PRM_HP_RCV_POINT:			// HP回復値の値
		return (s32)rcv->prm_hp_rcv;
	case ITEM_PRM_PP_RCV_POINT:			// pp回復値の値
		return (s32)rcv->prm_pp_rcv;
	case ITEM_PRM_FRIEND1_POINT:		// なつき度1の値
		return (s32)rcv->prm_friend1;
	case ITEM_PRM_FRIEND2_POINT:		// なつき度2の値
		return (s32)rcv->prm_friend2;
	case ITEM_PRM_FRIEND3_POINT:		// なつき度3の値
		return (s32)rcv->prm_friend3;
	}

	return 0;
}


//============================================================================================
//	技マシン
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 技マシンで覚えられる技を取得
 *
 * @param	item	アイテム番号
 *
 * @return	技番号
 */
//--------------------------------------------------------------------------------------------
const u16 GetWazaNoItem( u16 item )
{
	if( item < ITEM_WAZAMASIN01 || item > ITEM_HIDENMASIN08 ){
		return 0;
	}
	item -= ITEM_WAZAMASIN01;
	return MachineNo[ item ];
}

//--------------------------------------------------------------------------------------------
/**
 * 選択された技が秘伝技かどうか
 *
 * @param	waza	技番号
 *
 * @retval	"TRUE = 秘伝技"
 * @retval	"FALSE = 秘伝技以外"
 */
//--------------------------------------------------------------------------------------------
u8 HidenWazaCheck( u16 waza )
{
	u8	i;

	for( i=0; i<HIDENWAZA_MAX; i++ ){
		if( MachineNo[NORMAL_WAZAMACHINE_MAX+i] == waza ){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * 技マシン番号取得
 *
 * @param	item	アイテム番号
 *
 * @return	技マシン番号
 */
//--------------------------------------------------------------------------------------------
u8 WazaMashineNoGet( u16 item )
{
	if( item < ITEM_WAZAMASIN01 || item > ITEM_HIDENMASIN08 ){
		return 0;
	}
	return ( item - ITEM_WAZAMASIN01 );
}


//============================================================================================
//	メールチェック
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * アイテムがメールかどうかをチェック
 *
 * @param	item	アイテム番号
 *
 * @retval	"TRUE = メール"
 * @retval	"FALSE = メール以外"
 */
//--------------------------------------------------------------------------------------------
u8 ItemMailCheck( u16 item )
{
	u32	i;

	for( i=0; i<ITEM_MAIL_MAX; i++ ){
		if( ItemMailTable[i] == item ){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテム番号からメールのデザインを取得
 *
 * @param	item	アイテム番号
 *
 * @return	デザインID
 */
//--------------------------------------------------------------------------------------------
u8 ItemMailDesignGet( u16 item )
{
	u32	i;

	for( i=0; i<ITEM_MAIL_MAX; i++ ){
		if( ItemMailTable[i] == item ){
			return (u8)i;
		}
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * メールのデザインからアイテム番号を取得
 *
 * @param	design		デザインID
 *
 * @return	アイテム番号
 */
//--------------------------------------------------------------------------------------------
u16 MailItemNumGet( u8 design )
{
	if( design >= ITEM_MAIL_MAX ){
		return 0;
	}
	return ItemMailTable[design];
}


//============================================================================================
//	木の実チェック
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * アイテムが木の実かどうかをチェック
 *
 * @param	item	アイテム番号
 *
 * @retval	"TRUE = 木の実"
 * @retval	"FALSE = 木の実以外"
 */
//--------------------------------------------------------------------------------------------
u8 ItemNutsCheck( u16 item )
{
	u32	i;

	for( i=0; i<ITEM_NUTS_MAX; i++ ){
		if( ItemNutsTable[i] == item ){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * 木の実の番号を取得
 *
 * @param	item	アイテム番号
 *
 * @return	木の実番号
 */
//--------------------------------------------------------------------------------------------
u8 NutsNoGet( u16 item )
{
	if( item < ITEM_KURABONOMI ){
		return 0xff;
	}
	return ( item - ITEM_KURABONOMI );
}

//--------------------------------------------------------------------------------------------
/**
 * 指定IDの木の実のアイテム番号を取得
 *
 * @param	id		木の実のID
 *
 * @return	アイテム番号
 */
//--------------------------------------------------------------------------------------------
u16 NutsIDItemGet( u8 id )
{
	u32	i;

	if( id >= ITEM_NUTS_MAX ){ return 0xffff; }		// エラー

	return ItemNutsTable[id];
}


//============================================================================================
//	漢方薬チェック
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * アイテムが漢方薬かどうかをチェック
 *
 * @param	item	アイテム番号
 *
 * @retval	"TRUE = 漢方薬"
 * @retval	"FALSE = 漢方薬"
 */
//--------------------------------------------------------------------------------------------
u8 ItemKanpouyakuCheck( u16 item )
{
	u32	i;

	if( item == ITEM_TIKARANOKONA || item == ITEM_TIKARANONEKKO ||
		item == ITEM_BANNOUGONA || item == ITEM_HUKKATUSOU ){

		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムテーブルをすべてメモリに展開
 *
 * @param	heapID	展開するメモリヒープID
 *
 * @retval	確保したメモリのアドレス
 */
//--------------------------------------------------------------------------------------------
void	*ItemDataTableLoad(int heapID)
{
	int	max;

	max=GetItemIndex(ITEM_DATA_MAX,ITEM_GET_DATA);

//	return ArchiveDataLoadMallocOfs(ARC_ITEMDATA,0,heapID,0,sizeof(ITEMDATA)*ITEM_DATA_MAX);
	return ArchiveDataLoadMallocOfs(ARC_ITEMDATA,0,heapID,0,36*max);
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムテーブルから任意のアドレスを取得
 *
 * @param	item	アイテムテーブル
 * @param	index	とりだすインデックスナンバー
 *
 * @retval	取得したアドレス
 */
//--------------------------------------------------------------------------------------------
ITEMDATA	*GetItemDataPointer(ITEMDATA *item,u16 index)
{
	u8 *ret_item;

	ret_item=(u8 *)item;
	ret_item+=index*36;

	return (ITEMDATA *)ret_item;
}

