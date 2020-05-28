//=============================================================================
/**
 * @file	ug_bag.c
 * @brief	地下のかばんの中身を管理するクラス
 * @author	Katsumi Ohno
 * @date    2005.12.21
 */
//=============================================================================

#include "common.h"

#include "../fieldsys.h"
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "system/fontproc.h"
#include "system/window.h"
#include "system/wipe.h"
#include "system/clact_tool.h"
#include "system/menu_gra.naix"

#include "../fld_bmp.h"

#include "msgdata/msg_underworld.h"
#include "msgdata/msg_undergroundtrap.h"
#include "msgdata/msg_undergrounditem.h"
#include "msgdata/msg_undergroundgoods.h"
#include "msgdata/msg_uwflag.h"
#include "msgdata/msg_uwbuy.h"
#include "msgdata/msg_uwpersonal.h"
#include "msgdata/msg.naix"

#include "communication/communication.h"
#include "ug_manager.h"

#include "../ev_mapchange.h"
#include "gflib/camera.h"
#include "../fieldmap.h"
#include "../fld_bmp.h"
#include "../field_clact.h"
#include "../fld_comact.h"
#include "../../fielddata/base_goods/goods_id_def.h"
#include "system/snd_tool.h"
#include "savedata/undergrounddata.h"


#include "ug_local.h"
#include "ug_shop.h"

//==============================================================================
//	定数定義
//==============================================================================


#define _EVWIN_MSG_BUF_SIZE		(50*2)			//メッセージバッファサイズ

//#define	_SUB_MENU_MAX		( 7 )					// 項目最大数

#define	_TRAP_BAG_MAX      (20)
#define	_STONE_BAG_MAX     (20)
#define	_GOODS_BAG_MAX     (20)
#define	_TREASURE_BAG_MAX  (20)

#define _TRAP_COMPUTER_MAX      (200)
#define _STONE_COMPUTER_MAX     (200)
#define _GOODS_COMPUTER_MAX     (200)
#define _TREASURE_COMPUTER_MAX  (200)

// スタートメニューのキャラ位置
#define	BMPWIN_STARTMENU_CGX	( MENU_WIN_CGX_NUM-FLD_MENU_WIN_SX*FLD_MENU_WIN_SY )

// 各メニュー項目のウィンドウXサイズ
#define	BMPWIN_PARAMMENU_SX		( _TRAPMENU_SIZE_X )
// 各メニュー項目のウィンドウYサイズ
#define	BMPWIN_PARAMMENU_SY		( _FIELD_MENU_MAX * 2 )
// 各メニュー項目のウィンドウキャラ位置
#define	BMPWIN_PARAMMENU_CGX	( BMPWIN_STARTMENU_CGX-BMPWIN_PARAMMENU_SX*BMPWIN_PARAMMENU_SY )
// 各メニュー項目からの行動メニュー
#define	BMPWIN_FUNCMENU_CGX		( BMPWIN_STARTMENU_CGX )	// ここからスタートメニューに戻ることはないので、同じ領域でok



//==============================================================================
//	構造体定義
//==============================================================================

typedef struct{
    UNDERGROUNDDATA* pUGData; // 地下セーブデータ
    u8 deleteIndex;   // 消すアイテムが入っているindex
    u8 deleteItem;    // 消すアイテム番号
} _UNDER_ITEM;


static _UNDER_ITEM* _pUnderItem = NULL;


static const BMPWIN_DAT _yesNoBmpDat = {
    FLD_MBGFRM_FONT, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
    FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, FLD_YESNO_WIN_CGX
    };

//==============================================================================
//	型宣言
//==============================================================================
typedef void (*pStartFunc)(_START_WORK *);


//==============================================================================
//	static定義
//==============================================================================

// アイコン関連
static void _CellActDelete( _START_WORK * wk );
static void CellActAnm( _START_WORK * wk );
static void CursorMove( CLACT_WORK_PTR cwp, u32 cur_pos );
static void IconAnmChange( CLACT_WORK_PTR cwp, u16 anm, u16 pal );
static void MoveIconAnmChg( _START_WORK * wk, u16 old_pos, u16 new_pos );
static void SelectIconAnmCheck( CLACT_WORK_PTR cwp );

// メニュー関連
static void _bagProcess(TCB_PTR tcb, void* work);
static BOOL _startMenuFunc(TCB_PTR tcb, void* work);
static void _cardStart(_START_WORK* pStart);
static void _startSendStart(_START_WORK* pStart, int no);
static void _trapSet( _START_WORK* pStart );
static void _trapMenuStart(_START_WORK* pStart,CHANGE_UG_ITEM_FUNC pChangeFunc);
static BOOL _trapMenuFunc(TCB_PTR tcb, void* work);
static void _stoneMenuStart(_START_WORK* pStart,CHANGE_UG_ITEM_FUNC pChangeFunc);
static BOOL _stoneMenuFunc(TCB_PTR tcb, void* work);
static BOOL _stoneSubMenuFunc(TCB_PTR tcb, void* work);
static void _stoneMenuStart_Bag(_START_WORK* pStart);

static void _treasureMenuStart(_START_WORK* pStart,CHANGE_UG_ITEM_FUNC pChangeFunc);
static BOOL _treasureMenuFunc(TCB_PTR tcb, void* work);
static BOOL _treasureSubMenuFunc(TCB_PTR tcb, void* work);
static void _itemDiamond( _START_WORK* pStart );
static void _itemPearl( _START_WORK* pStart );
static void _startExit( _START_WORK* pStart );
static void _underExit( _START_WORK* pStart );
static void _statusList( _START_WORK* pStart );

static BOOL _trapSubMenuFunc(TCB_PTR tcb, void* work);
static BOOL _goodsSubMenuFunc(TCB_PTR tcb, void* work);

// 旗消去メニュー関連
static void _flagProcess(TCB_PTR tcb, void* work);

static void _goodsMenuStart(_START_WORK* pStart,CHANGE_UG_ITEM_FUNC pChangeFunc);
static BOOL _goodsMenuFunc(TCB_PTR tcb, void* work);
static BOOL _goodsMenuFuncSub2(TCB_PTR tcb, void* work);

// 地上に戻る
static void _exitTalkFunc(TCB_PTR tcb, void* work);
static void _exitTalkFunc2(TCB_PTR tcb, void* work);
static void _exitTalkFunc3(TCB_PTR tcb, void* work);
static void _exitTalkFunc4(TCB_PTR tcb, void* work);

static void _delEnd(TCB_PTR tcb, _START_WORK* pStart, BOOL bHold);

//==============================================================================
//	STARTメニューリスト用データ等
//==============================================================================

static const struct {
	u32  str_id;
	u32  param;
}MenuParamList[] = {
    { UGStartMenu01, (u32)_trapMenuStart_Bag },
    { UGStartMenu02, (u32)_stoneMenuStart_Bag },
    { UGStartMenu03, (u32)_goodsMenuStart_Bag },
    { UGStartMenu04, (u32)_treasureMenuStart_Bag },
    { UGStartMenu05, (u32)_statusList },
    { UGStartMenu06, (u32)_underExit },
    { UGStartMenu07, (u32)_startExit },
};


/*
///START選択メニューのリスト
static const BMPLIST_HEADER StartMenuListHeader = {
    NULL,			// 表示文字データポインタ
    NULL,					// カーソル移動ごとのコールバック関数
    NULL,					// 一列表示ごとのコールバック関数
    NULL,					// 
    NELEMS(MenuParamList),	// リスト項目数
    NELEMS(MenuParamList),	// 表示最大項目数
    0,						// ラベル表示Ｘ座標
    8,						// 項目表示Ｘ座標
    0,						// カーソル表示Ｘ座標
    0,						// 表示Ｙ座標
    FBMP_COL_BLACK,			// 文字色
    FBMP_COL_WHITE,			// 背景色
    FBMP_COL_BLK_SDW,		// 文字影色
    0,						// 文字間隔Ｘ
    16,						// 文字間隔Ｙ
    BMPLIST_LRKEY_SKIP,		// ページスキップタイプ
    FONT_SYSTEM,				// 文字指定
    0,						// ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
    NULL,                   // ワーク
};
*/
   
///汎用選択メニューのリスト
static const BMPLIST_HEADER MenuListHeader = {
    NULL,			// 表示文字データポインタ
    NULL,					// カーソル移動ごとのコールバック関数
    NULL,					// 一列表示ごとのコールバック関数
    NULL,					// 
    _TRAP_BAG_MAX,	// リスト項目数
    _TRAP_BAG_MAX,	// 表示最大項目数
    0,						// ラベル表示Ｘ座標
    8,						// 項目表示Ｘ座標
    0,						// カーソル表示Ｘ座標
    0,						// 表示Ｙ座標
    FBMP_COL_BLACK,			// 文字色
    FBMP_COL_WHITE,			// 背景色
    FBMP_COL_BLK_SDW,		// 文字影色
    0,						// 文字間隔Ｘ
    16,						// 文字間隔Ｙ
    BMPLIST_LRKEY_SKIP,		// ページスキップタイプ
    FONT_SYSTEM,			// 文字指定
    0,						// ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
    NULL,                   // ワーク
};


#define	CLA_ID_ICON_START	( 1 )

enum {
	MENU_POS_ZUKAN = 0,
	MENU_POS_POKEMON,
	MENU_POS_BAG,
	MENU_POS_HERO,
	MENU_POS_REPORT,
	MENU_POS_CONFIG,
	MENU_POS_EXIT,
	MENU_POS_CHAT,
};
enum {
	ICON_ZUKAN,		// 図鑑アイコン
	ICON_POKEMON,	// ポケモンリストアイコン
	ICON_BAG,		// バッグアイコン
	ICON_HERO,		// トレーナーカードアイコン
	ICON_REPORT,	// レポートアイコン
	ICON_CONFIG,	// 設定アイコン
	ICON_CLOSE,		// 閉じるアイコン
	ICON_BAG_F,		// バッグ（女）
	ICON_CHAT,		// チャット
};

// セルアクター登録場所
#define	CLA_SET_CURSOR	( 0 )	// 選択カーソル
#define	CLA_SET_ICON	( 1 )	// アイコン

#define	CLA_CURSOR_PX	( 204 )
#define	CLA_CURSOR_PY	( 20 )
#define	CLA_ICON_PX		( 174 )
#define	CLA_ICON_PY		( 20 )
#define	CLA_ICON_SPC_Y	( 24 )

enum {
	ICON_ANM_STOP = 0,
	ICON_ANM_CHANGE,
	ICON_ANM_SELECT,
};

enum {
	FLDMENU_CLA_CHR_H_ID_CURSOR	= 14528,
	FLDMENU_CLA_CHR_H_ID_ICON,
};
enum {
	FLDMENU_CLA_PAL_H_ID = 14528,
};
enum {
	FLDMENU_CLA_CEL_H_ID_CURSOR	= 14528,
	FLDMENU_CLA_CEL_H_ID_ICON,
};
enum {
	FLDMENU_CLA_ANM_H_ID_CURSOR	= 14528,
	FLDMENU_CLA_ANM_H_ID_ICON,
};

static const TCATS_OBJECT_ADD_PARAM_S ActAddParam_S[] =
{
	{	// カーソル
		CLA_CURSOR_PX, CLA_CURSOR_PY, 0,
		0, 1, 1, NNS_G2D_VRAM_TYPE_2DMAIN,
		{
			FLDMENU_CLA_CHR_H_ID_CURSOR, FLDMENU_CLA_PAL_H_ID,
			FLDMENU_CLA_CEL_H_ID_CURSOR, FLDMENU_CLA_ANM_H_ID_CURSOR, 0, 0,
		},
		0, 0
	},
	{	// アイコン１
		CLA_ICON_PX, CLA_ICON_PY, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{
			FLDMENU_CLA_CHR_H_ID_ICON, FLDMENU_CLA_PAL_H_ID,
			FLDMENU_CLA_CEL_H_ID_ICON, FLDMENU_CLA_ANM_H_ID_ICON, 0, 0,
		},
		0, 0
	},
};

#define	FLDMENU_CLA_CHR_RES_MAX		( 8 )
#define	FLDMENU_CLA_PAL_RES_MAX		( 1 )
#define	FLDMENU_CLA_CEL_RES_MAX		( 2 )
#define	FLDMENU_CLA_ANM_RES_MAX		( 2 )

//==============================================================================
// 関数
//==============================================================================

static void CellActSet( _START_WORK * wk, u8 * list, u32 max )
{
	TCATS_RESOURCE_NUM_LIST	crnl = {
		FLDMENU_CLA_CHR_RES_MAX, FLDMENU_CLA_PAL_RES_MAX,
		FLDMENU_CLA_CEL_RES_MAX, FLDMENU_CLA_ANM_RES_MAX, 0, 0
	};
	u32	i;

	FieldCellActSet_S( &wk->fcat, &crnl, _FLDMENU_CLACT_MAX, HEAPID_WORLD );

	FldClact_LoadResPlttArc(
		&wk->fcat, ARC_MENU_GRA,
		NARC_menu_gra_ugmenu_obj_NCLR, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, FLDMENU_CLA_PAL_H_ID );

	FldClact_LoadResCellArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_fmenu_cur_NCER, 0, FLDMENU_CLA_CEL_H_ID_CURSOR );

	FldClact_LoadResCellAnmArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_fmenu_cur_NANR, 0, FLDMENU_CLA_ANM_H_ID_CURSOR );

	FldClact_LoadResourceCharArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_fmenu_cur_NCGR,
		0, NNS_G2D_VRAM_TYPE_2DMAIN, FLDMENU_CLA_CHR_H_ID_CURSOR );

	wk->cap[CLA_SET_CURSOR] = FieldCellActAdd_S( &wk->fcat, &ActAddParam_S[CLA_SET_CURSOR] );

	CursorMove( wk->cap[CLA_SET_CURSOR]->act, wk->pos );


	FldClact_LoadResCellArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_ugmenu_obj_NCER, 0, FLDMENU_CLA_CEL_H_ID_ICON );

	FldClact_LoadResCellAnmArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_ugmenu_obj_NANR, 0, FLDMENU_CLA_ANM_H_ID_ICON );

	FldClact_LoadResourceCharArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_ugmenu_obj_NCGR,
		0, NNS_G2D_VRAM_TYPE_2DMAIN, FLDMENU_CLA_CHR_H_ID_ICON );

	for( i=0; i<max; i++ ){
		TCATS_OBJECT_ADD_PARAM_S	prm;

		prm = ActAddParam_S[CLA_SET_ICON];
		prm.y += CLA_ICON_SPC_Y * i;

        prm.anm = list[i] * 3;

		wk->cap[CLA_SET_ICON+i] = FieldCellActAdd_S( &wk->fcat, &prm );

		{
			VecFx32 sca = { FX32_ONE, FX32_ONE, FX32_ONE };
			CLACT_SetScaleAffine( wk->cap[CLA_SET_ICON+i]->act, &sca, CLACT_AFFINE_NORMAL );
		}
	}
	IconAnmChange( wk->cap[CLA_SET_ICON+wk->pos]->act, ICON_ANM_SELECT, 1 );

	wk->clact_max = max + 1;

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}

static void _CellActDelete( _START_WORK * wk )
{
	u16	i;

	for( i=0; i<wk->clact_max; i++ ){
		CATS_ActorPointerDelete_S( wk->cap[i] );
	}
	FieldCellActDelete_S( &wk->fcat );
  //  MI_CpuClear8(&wk->fcat, sizeof(FIELD_CLACT));
}

static void CellActAnm( _START_WORK * wk )
{
	u16	i;

	for( i=0; i<wk->clact_max; i++ ){
		CLACT_AnmFrameChg( wk->cap[i]->act, FX32_ONE );
	}
}

static void CursorMove( CLACT_WORK_PTR cwp, u32 cur_pos )
{
	VecFx32	act_pos;

	act_pos = *(CLACT_GetMatrix( cwp ));
	act_pos.y = ( CLA_CURSOR_PY + CLA_ICON_SPC_Y * cur_pos ) * FX32_ONE;
	CLACT_SetMatrix( cwp, &act_pos );
}


static void IconAnmChange( CLACT_WORK_PTR cwp, u16 anm, u16 pal )
{
	u32	now_anm = CLACT_AnmGet( cwp );

	CLACT_AnmChg( cwp, (now_anm/3)*3+anm );
	CLACT_PaletteNoChgAddTransPlttNo( cwp, pal );
}

static void MoveIconAnmChg( _START_WORK * wk, u16 old_pos, u16 new_pos )
{
	IconAnmChange( wk->cap[CLA_SET_ICON+old_pos]->act, ICON_ANM_STOP, 0 );
	IconAnmChange( wk->cap[CLA_SET_ICON+new_pos]->act, ICON_ANM_CHANGE, 1 );
}

static void SelectIconAnmCheck( CLACT_WORK_PTR cwp )
{
	if( (CLACT_AnmGet( cwp ) % 3) != ICON_ANM_CHANGE ){
		return;
	}
	if( CLACT_AnmActiveCheck( cwp ) == FALSE ){
		IconAnmChange( cwp, ICON_ANM_SELECT, 1 );
	}
}



//============================================================================================

//==============================================================================
/**
 * パソコンと自分のバッグの領域確保
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommUnderBagInitialize(UNDERGROUNDDATA* pUGData)
{
    _pUnderItem = sys_AllocMemory(HEAPID_COMMUNICATION, sizeof(_UNDER_ITEM));
    MI_CpuClear8(_pUnderItem,sizeof(_UNDER_ITEM));
    _pUnderItem->deleteIndex = 0;   // 消すアイテムが入っているindex
    _pUnderItem->deleteItem = 0;    // 消すアイテム番号
    _pUnderItem->pUGData = pUGData;
    OHNO_PRINT("CommUnderBagInitialize\n");
}

//==============================================================================
/**
 * パソコンと自分のバッグの領域開放
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommUnderBagFinalize(void)
{
    // セーブする必要がある
    sys_FreeMemoryEz(_pUnderItem);
}

//==============================================================================
/**
 * 自分のバッグの罠の数を得る
 * @param   none
 * @retval  罠の数
 */
//==============================================================================

static int _underBagGetTrapNum(void* work)
{
    _START_WORK* pStart = work;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));

    return UnderGroundGetNumTrapBagItem(pUGData);
}

//==============================================================================
/**
 * パソコンのTRAPの数を得る
 * @param   work
 * @retval  TRAPの数
 */
//==============================================================================

static int _underPcGetTrapNum(void* work)
{
    _START_WORK* pStart = work;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));
    
    return UnderGroundGetNumTrapPCItem(pUGData);
}

//==============================================================================
/**
 * パソコンのTRAPTYPEを返す
 * @param   index    何番目のTRAPを得るか
 * @retval  TRAPTYPE
 */
//==============================================================================

int _underPcGetTrapType(int index, void* work)
{
    _START_WORK* pStart = work;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));

    return UnderGroundGetTrapPCItem(pUGData,index);
}

//==============================================================================
/**
 * パソコンのGOODSの数を得る
 * @param   work
 * @retval  GOODSの数
 */
//==============================================================================

static int _underPcGetGoodsNum(void* work)
{
    _START_WORK* pStart = work;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));
    
    return UnderGroundGetNumGoodsPCItem(pUGData);
}

//==============================================================================
/**
 * パソコンのGOODSIDを返す
 * @param   index    何番目のGOODSを得るか
 * @retval  goodsID
 */
//==============================================================================

int _underPcGetGoodsID(int index, void* work)
{
    _START_WORK* pStart = work;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));

    return UnderGroundGetGoodsPCItem(pUGData,index);
}

//==============================================================================
/**
 * 自分のバッグのGOODSの数を得る
 * @param   none
 * @retval  GOODSの数
 */
//==============================================================================

static int _underBagGetGoodsNum(void* work)
{
    _START_WORK* pStart = work;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));
    
    return UnderGroundGetNumGoodsBagItem(pUGData);
}

//==============================================================================
/**
 * 自分のバッグのGOODSIDを返す
 * @param   index    何番目のGOODSを得るか
 * @retval  goodsID
 */
//==============================================================================

int _underBagGetGoodsID(int index, void* work)
{
    _START_WORK* pStart = work;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));
    
    return UnderGroundGetGoodsBagItem(pUGData,index);
}

//--------------------------------------------------------------
/**
 * @brief   バッグのGOODSを消す
 * @param   type   GOODSTYPE
 * @retval  none
 */
//--------------------------------------------------------------
void UgBagDeleteGoods(int type)
{
    GF_ASSERT(_pUnderItem->deleteItem == type);
    UnderGroundDelGoodsBagItem(_pUnderItem->pUGData, _pUnderItem->deleteIndex);
}

//==============================================================================
/**
 * 自分のバッグのタマの数を得る
 * @param   none
 * @retval  たまの数
 */
//==============================================================================

static int _underBagGetStoneNum(void* work)
{
    _START_WORK* pStart = work;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));
    
    return UnderGroundGetNumStoneBagItem(pUGData);
}

//==============================================================================
/**
 * 自分のバッグの罠IDを返す
 * @param   index    何番目の罠を得るか
 * @retval  trapID
 */
//==============================================================================

int _underBagGetTrapID(int index,void* work)
{
    _START_WORK* pStart = work;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));

    return UnderGroundGetTrapBagItem_List(pUGData, index);
}

//==============================================================================
/**
 * 自分のバッグのタマID何かを返す
 * @param   index    何番目のたまを得るか
 * @retval  stoneID
 */
//==============================================================================

int _underBagGetStoneID(int index, void* work)
{
    _START_WORK* pStart = work;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));

    return UnderGroundGetStoneBagItem(pUGData,index);
}

//==============================================================================
/**
 * 自分のバッグのタマCarat何かを返す
 * @param   index    何番目のたまを得るか
 * @retval  Carat
 */
//==============================================================================

int _underBagGetStoneCarat(int index, void* work)
{
    _START_WORK* pStart = work;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));

    return UnderGroundGetStoneCaratBagItem(pUGData,index);
}

//==============================================================================
/**
 * パソコンのタマの数を得る
 * @param   none
 * @retval  たまの数
 */
//==============================================================================

static int _underPcGetStoneNum(void* work)
{
    _START_WORK* pStart = work;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));

    return UnderGroundGetNumStonePCItem(pUGData);
}

//==============================================================================
/**
 * パソコンのタマID何かを返す
 * @param   index    何番目のたまを得るか
 * @retval  stoneID
 */
//==============================================================================

int _underPcGetStoneType(int index, void* work)
{
    _START_WORK* pStart = work;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));

    return UnderGroundGetStonePCItem(pUGData, index);
}

//==============================================================================
/**
 * パソコンのタマが何カラットかを返す
 * @param   index    何番目のたまを得るか
 * @retval  stoneID
 */
//==============================================================================

int _underPcGetStoneCarat(int index, void* work)
{
    _START_WORK* pStart = work;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));

    return UnderGroundGetStoneCaratPCItem(pUGData, index);
}

//==============================================================================
/**
 * 自分のバッグのお宝の数を得る
 * @param   none
 * @retval  たまの数
 */
//==============================================================================

static int _underBagGetTreasureNum(void* work)
{
    _START_WORK* pStart = work;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));

    return UnderGroundGetNumTreasureBagItem(pUGData);
}

//==============================================================================
/**
 * 自分のバッグのタマID何かを返す
 * @param   index    何番目のたまを得るか
 * @retval  stoneID
 */
//==============================================================================

int _underBagGetTreasureID(int index, void* work)
{
    _START_WORK* pStart = work;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));

    return UnderGroundGetTreasureBagItem_List(pUGData,index);
}

//==============================================================================
/**
 * バッグにたまを入れる
 * @param   no      たまタイプ
 * @param   carat   カラット
 * @retval  たまを入れたらTRUE
 */
//==============================================================================

BOOL CommUnderBagAddStone(int no, int carat)
{
    int type = no;
    GF_ASSERT_RETURN(no < DIG_PARTS_TREASURE_MIN ,FALSE);

    if(no >= STONE_TYPE_MAX){
        type -= STONE_TYPE_GREEN;
    }
    if(carat > UG_STONE_CARAT_MAX){
        carat = UG_STONE_CARAT_MAX;
    }
    return UnderGroundAddStoneBagItem(_pUnderItem->pUGData, type, carat);
}

//==============================================================================
/**
 * おたからをバッグに入れる
 * @param   no      宝タイプ
 * @retval  宝を入れたらTRUE
 */
//==============================================================================

BOOL CommUnderBagAddTreasure(int no)
{
    GF_ASSERT_RETURN(no < DIG_PARTS_TREASURE_MAX,FALSE);
    return UnderGroundAddTreasureBagItem(_pUnderItem->pUGData, no);
}

//==============================================================================
/**
 * 罠をかばんに追加
 * @param   no    罠タイプ番号
 * @retval  追加できたらTRUE
 */
//==============================================================================

BOOL CommUnderBagAddTrap(int no)
{
    return UnderGroundAddTrapBagItem(_pUnderItem->pUGData, no);
}

//==============================================================================
/**
 * GOODSをかばんに追加
 * @param   no    GOODSタイプ番号
 * @retval  追加できたらTRUE
 */
//==============================================================================

BOOL CommUnderBagAddGoods(int no)
{
    return UnderGroundAddGoodsBagItem(_pUnderItem->pUGData, no);
}

//==============================================================================
/**
 * 地下バッグ初期化
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommUnderBagInit(pBagEndFunc func, FIELDSYS_WORK* pFSys)
{
    _START_WORK* pStart;
    BMPLIST_HEADER list_h;

    Snd_SePlay( SEQ_SE_DP_WIN_OPEN );
    UgMgrOpenRecordKey(_KEY_NAME_BAG);
    pStart = sys_AllocMemory(HEAPID_FIELD, sizeof(_START_WORK));
    MI_CpuFill8(pStart, 0, sizeof(_START_WORK));
    pStart->pFSys = pFSys;
    pStart->endfunc = func;
    pStart->seq = 0;
    pStart->pStrBuf1 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    pStart->pStrBuf2 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    pStart->pWordSet = WORDSET_Create( HEAPID_FIELD );
    pStart->pTCB = TCB_Add(_bagProcess, pStart, _MENU_UG_PRI);
    UgMgrSetNowTCB(pStart,pStart->pTCB,UgGoodsMenuForceDelete2);
}


//--------------------------------------------------------------------------------------------
/**
 * メニューリスト作成
 *
 * @param	event	フィールドイベント用パラメータ
 * @param	list	リスト作成場所
 *
 * @return	項目数
 */
//--------------------------------------------------------------------------------------------
static u32 _menuListMake( u8 * list )
{
	u32	max = 0;

	list[max] = MENU_POS_ZUKAN;
	max++;
	list[max] = MENU_POS_POKEMON;
	max++;
	list[max] = MENU_POS_BAG;
	max++;
	list[max] = MENU_POS_HERO;
	max++;
    list[max] = MENU_POS_REPORT;
	max++;
	list[max] = MENU_POS_CONFIG;
	max++;
	list[max] = MENU_POS_EXIT;
	max++;

	return max;
}

//==============================================================================
/**
 * 話しかけの起動を行う
 * @param   targetID   話し相手のINDEX
 * @retval  none
 */
//==============================================================================

static void _startMenuInit(_START_WORK* pStart)
{
//    BMPLIST_HEADER list_h;
    BMPMENU_HEADER	hed;
    const _MYNAME_MENUNUM = 4;
	u8	list[ _FIELD_START_MENU_MAX ];
    int max;

	max = _menuListMake( list );
    
    //FieldOBJSys_MoveStopAll( pStart->pFSys->fldobjsys );
    
    //BMPウィンドウ生成
    pStart->menulist = BMP_MENULIST_Create( NELEMS(MenuParamList), HEAPID_FIELD );
    GF_BGL_BmpWinAdd(pStart->pFSys->bgl,&pStart->win,
                     GF_BGL_FRAME3_M, FLD_MENU_WIN_PX, FLD_MENU_WIN_PY, FLD_MENU_WIN_SX,
                     NELEMS(MenuParamList)*3, FLD_SYSFONT_PAL, BMPWIN_STARTMENU_CGX );
//                     FLD_MSG_WIN_CGX-(10*NELEMS(MenuParamList)*3));

    BmpMenuWinWrite(&pStart->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	{
		MSGDATA_MANAGER* msgman;
		int i;

		msgman = CommMsgGetMsgManager(CommUnderGetMsgUnderWorld());
		for(i=0; i < NELEMS(MenuParamList); i++)
		{
            if(i == _MYNAME_MENUNUM){
                const MYSTATUS* pMy = SaveData_GetMyStatus( GameSystem_GetSaveData(pStart->pFSys) );
                STRBUF* pBuf = MyStatus_CreateNameString(pMy, HEAPID_FIELD);
                BMP_MENULIST_AddString( pStart->menulist, pBuf, MenuParamList[i].param );
                STRBUF_Delete(pBuf);
            }
            else{
                BMP_MENULIST_AddArchiveString( pStart->menulist, msgman,
                                               MenuParamList[i].str_id,
                                               MenuParamList[i].param );
            }
        }
	}
    pStart->pos = pStart->pFSys->startmenu_pos;
	hed.menu  = pStart->menulist;
	hed.win   = &pStart->win;
	hed.font  = FONT_TALK;
	hed.x_max = 1;
	hed.y_max = NELEMS(MenuParamList);
	hed.line_spc = 8;
	hed.c_disp_f = 1;
	if( NELEMS(MenuParamList) >= 4 ){
		hed.loop_f = 1;
	}else{
		hed.loop_f = 0;
	}
	pStart->mw = BmpMenuAdd_NoTrans(
				&hed, 28, 4, pStart->pos, HEAPID_WORLD, PAD_BUTTON_CANCEL|PAD_BUTTON_X );
    pStart->lw = NULL;

	GF_BGL_BmpWinOnVReq( &pStart->win );

    
    CellActSet( pStart, list ,NELEMS(MenuParamList) );
    CommPlayerHold();


}

//--------------------------------------------------------------
/**
 * @brief   話しかけを決めるメニュー実行部分
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------

typedef enum{
    _START_INIT,
    _START_MENU,
    _START_END,
    _START_DRILL_END,
    _START_ALL_END,
    _START_TRAP_WAIT,
    _START_STONE_WAIT,
    _START_TREASURE_WAIT,
    _START_GOODS_WAIT,
    _START_GOODS_WAIT_SUB2,
    _START_STATUS_WAIT,
    _START_EXIT_WAIT,
    _START_EXIT_WAIT2,
    _START_QUIT,
    _START_NEXT,
    _START_EXIT_UNDERGROUND,
    _START_STONE_WAIT_SUB,
    _START_TREASURE_WAIT_SUB,
    _START_TRAP_WAIT_SUB,
    _START_GOODS_WAIT_SUB
};


static void _bagProcess(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;
    u32	ret;

    switch(pStart->seq){
      case _START_INIT:
        _startMenuInit(pStart);
        pStart->seq++;
        break;
      case _START_MENU:
        _startMenuFunc(tcb, work);
        break;
      case _START_END:
        _startMenuEnd(pStart);
        UgMgrEndNowTCB();
        _delEnd(tcb, pStart, FALSE);
        return;
      case _START_DRILL_END:
        _startMenuEnd(pStart);
        UgMgrEndNowTCB();
        _delEnd(tcb, pStart, TRUE);
        return;
      case _START_TRAP_WAIT:
        _trapMenuFunc(tcb, work);
        break;
      case _START_STONE_WAIT:
        _stoneMenuFunc(tcb, work);
        break;
      case _START_TREASURE_WAIT:
        _treasureMenuFunc(tcb, work);
        break;
      case _START_GOODS_WAIT:
        _goodsMenuFunc(tcb, work);
        break;
      case _START_GOODS_WAIT_SUB2:
        _goodsMenuFuncSub2(tcb, work);
        break;
      case _START_STATUS_WAIT:


        break;
      case _START_EXIT_WAIT:
        _exitTalkFunc(tcb,work);
        break;
      case _START_EXIT_WAIT2:
        _exitTalkFunc2(tcb,work);
        break;
      case _START_QUIT:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            if(sys.trg & PAD_BUTTON_DECIDE){
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
                _delEnd(tcb,pStart, FALSE);
                UgMgrEndNowTCB();
                return;
            }
        }
        break;
      case _START_NEXT:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            if(sys.trg & PAD_BUTTON_DECIDE){

                NEXTJOB_CALLBACK nextCB = (NEXTJOB_CALLBACK)pStart->menuCallBack;
                nextCB(pStart);
                pStart->seq = pStart->seqNext;
            }
        }
        break;
      case _START_EXIT_UNDERGROUND:
        _startMenuEnd(pStart);
        _delEnd(tcb, pStart, TRUE);
        UgMgrEndNowTCB();
        ChangeUnderGroundDirect(pStart->pFSys);
        return;
      case _START_TRAP_WAIT_SUB:
        _trapSubMenuFunc(tcb, work);
        break;
      case _START_STONE_WAIT_SUB:
        _stoneSubMenuFunc(tcb,work);
        break;
      case _START_TREASURE_WAIT_SUB:
        _treasureSubMenuFunc(tcb,work);
        break;
      case _START_GOODS_WAIT_SUB:
        _goodsSubMenuFunc(tcb, work);
        break;
    }
}


static BOOL _startMenuFunc(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;
	u16	cur;

	cur = BmpMenuCursorPosGet( pStart->mw );
	pStart->ret = BmpMenuMain_SE( pStart->mw, SE_FLD_MENU_SELECT );
	pStart->pos = BmpMenuCursorPosGet( pStart->mw );

	if( cur != pStart->pos ){
		CursorMove( pStart->cap[CLA_SET_CURSOR]->act, pStart->pos );
		MoveIconAnmChg( pStart, cur, pStart->pos );
		pStart->pFSys->startmenu_pos = pStart->pos;
	}
	SelectIconAnmCheck( pStart->cap[CLA_SET_ICON+pStart->pos]->act );
    
    if(CommIsError()){  // エラー時はキャンセル扱いにする
        pStart->ret = BMPLIST_CANCEL;
    }
    switch(pStart->ret){
    case BMPLIST_NULL:
	    CellActAnm( pStart );
        CLACT_Draw( pStart->fcat.cas );
        return FALSE;
    case BMPLIST_CANCEL:
        pStart->seq = _START_END;
        break;
    default:
		if( (pStart->ret == (u32)_trapMenuStart_Bag) ||
			(pStart->ret == (u32)_stoneMenuStart_Bag) ||
			(pStart->ret == (u32)_goodsMenuStart_Bag) ||
			(pStart->ret == (u32)_treasureMenuStart_Bag) ){ // カーソルアクター初期化
			pStart->fca = FComAct_Init(HEAPID_FIELD);
			FComAct_CursorPosSet(pStart->fca,200,20,122);
			FComAct_SetDrawFlg(pStart->fca,FCA_UCURSOR,FALSE);
			FComAct_SetDrawFlg(pStart->fca,FCA_DCURSOR,FALSE);
		}

        if (pStart->clact_max){
            _CellActDelete( pStart );
            BmpMenuExit( pStart->mw, NULL );
            pStart->clact_max = 0;
        }

        {
            pStartFunc func = (pStartFunc)pStart->ret;
            func(pStart);  // 関数ジャンプ
        }
        break;
    }
    return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   メニューリストを閉じる
 * @param   tcb			TCBへのポインタ
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

void _startMenuEnd(_START_WORK* pStart)
{
    if(pStart->pUGlw){
        Ug_BmpListExit(pStart->pUGlw, NULL, NULL);
        pStart->pUGlw = NULL;
    }
    if(pStart->lw){
        BmpListExit(pStart->lw, NULL, NULL);
        pStart->lw = NULL;
    }
    else if (pStart->clact_max){
        _CellActDelete( pStart );
        BmpMenuExit( pStart->mw, NULL );
        pStart->clact_max = 0;
    }
//    else{
  //      return;
//    }
    if(GF_BGL_BmpWinAddCheck(&pStart->win)){
        BmpMenuWinClear(&pStart->win, WINDOW_TRANS_OFF );
        GF_BGL_LoadScreenV_Req( pStart->win.ini, pStart->win.frmnum );
        GF_BGL_BmpWinDel(&pStart->win);
        BMP_MENULIST_Delete(pStart->menulist);
        UgShopMiniInfoDispWindowDel(pStart);
    }
}




//--------------------------------------------------------------
/**
 * @brief   SUBメニューリストを作る 2行か３行
 * @param   tcb			TCBへのポインタ
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

#define _DIG_COMMAND  (1)
#define _TRASH_COMMAND  (2)
#define _IN_COMMAND  (3)

typedef struct {
	u32  str_id;
	u32  param;
} _SUB_MENU_PARAM;

static _SUB_MENU_PARAM SubMenuParamList[] = {
    { mes_uw_item_11, (u32)_DIG_COMMAND },
    { mes_uw_item_09, (u32)_TRASH_COMMAND },
    { mes_uw_item_10, (u32)BMPLIST_CANCEL },
};

static _SUB_MENU_PARAM GoodsSubMenuParamList[] = {
    { mes_uw_item_09, (u32)_TRASH_COMMAND },
    { mes_uw_item_10, (u32)BMPLIST_CANCEL },
};

static _SUB_MENU_PARAM TreasureSubMenuParamList[] = {
    { mes_uw_item_12, (u32)_IN_COMMAND },
    { mes_uw_item_09, (u32)_TRASH_COMMAND },
    { mes_uw_item_10, (u32)BMPLIST_CANCEL },
};



#define _SUBMENU_POSY (11)
#define _SUBMENU_SIZE_X (6)
#define _SUBMENU_POSX (31 - _SUBMENU_SIZE_X)


static void _subMenuStart(_START_WORK* pStart, int type)
{
    BMPLIST_HEADER list_h;
    int line, start;
    int posy = _SUBMENU_POSY;
    int sizex = _SUBMENU_SIZE_X;
    int posx = _SUBMENU_POSX;
    _SUB_MENU_PARAM* pSubList;


    switch(type){
      case _DIG_COMMAND:
        line = 3;
        pSubList = SubMenuParamList;
        break;
      case _TRASH_COMMAND:
        line = 2;
        posy = _SUBMENU_POSY+2;
        pSubList = GoodsSubMenuParamList;
        break;
      case _IN_COMMAND:
        line = 3;
        sizex = _SUBMENU_SIZE_X + 5;
        posx = _SUBMENU_POSX - 5;
        pSubList = TreasureSubMenuParamList;
        break;
    }
    
    pStart->subMenulist = BMP_MENULIST_Create( line, HEAPID_FIELD );
    GF_BGL_BmpWinAdd(pStart->pFSys->bgl,&pStart->winSub,
                     GF_BGL_FRAME3_M, posx, posy,
                     sizex, line * 2, FLD_SYSFONT_PAL,
					 BMPWIN_FUNCMENU_CGX );
//                     FLD_MSG_WIN_CGX - (_SUBMENU_SIZE_X * 15 * 2) -  sizex * line * 2);
    BmpMenuWinWrite(&pStart->winSub, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
    {
        MSGDATA_MANAGER* msgman;
        int i;
        msgman = CommMsgGetMsgManager(CommUnderGetMsgUnderWorld());
        for(i = 0; i < line; i++) {
            BMP_MENULIST_AddArchiveString(pStart->subMenulist,msgman,
                                          pSubList->str_id ,
                                          pSubList->param);
            pSubList++;
        }
    }
    list_h = MenuListHeader;
    list_h.count = line;
    list_h.line = line;
    list_h.list = pStart->subMenulist;
    list_h.win = &pStart->winSub;
    list_h.work = pStart;
    pStart->subLw = BmpListSet(&list_h, 0, 0, HEAPID_FIELD);
//    GF_BGL_BmpWinOn(&pStart->winSub);
}


//--------------------------------------------------------------
/**
 * @brief   SUBメニューリストを閉じる
 * @param   tcb			TCBへのポインタ
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _subMenuEnd(_START_WORK* pStart)
{
    if(pStart->subLw){
        BmpListExit(pStart->subLw, NULL, NULL);
        GF_BGL_LoadScreenV_Req( pStart->winSub.ini, pStart->winSub.frmnum );
        BMP_MENULIST_Delete(pStart->subMenulist);
        pStart->subLw = NULL;
    }
    if(GF_BGL_BmpWinAddCheck(&pStart->winSub)){
        BmpMenuWinClear(&pStart->winSub, WINDOW_TRANS_OFF );
        GF_BGL_BmpWinDel(&pStart->winSub);
    }
}

//--------------------------------------------------------------
/**
 * @brief   メニューキャンセル＋メインメニュー移動
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _menuCancel2MainMenu(_START_WORK* pStart)
{
    _startMenuEnd(pStart);
    if(pStart->fca){
        FComAct_Delete(pStart->fca);
        pStart->fca = NULL;
    }
    pStart->seq = _START_INIT;
    CommMsgTalkWindowEnd(CommUnderGetMsgUnderItem());
}


//--------------------------------------------------------------
/**
 * @brief   トラップメニューで罠をおいた場合のコールバック
 * @param   type  トラップタイプ
 * @retval  none
 */
//--------------------------------------------------------------
void CommUnderBagDeleteTrap(int type)
{
    if(_pUnderItem->deleteItem == type){    // 罠を消す
        UnderGroundDelTrapBagItem(_pUnderItem->pUGData, _pUnderItem->deleteIndex);
    }
}

//--------------------------------------------------------------
/**
 * @brief   トラップメニュー説明文
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

void _trapMenuLineSelect(BMPLIST_WORK * wk,u32 param,u8 mode)
{
    _START_WORK* pStart = (_START_WORK*)BmpListParamGet(wk, BMPLIST_ID_WORK);
    pGetTypeFunc getTypeFunc = pStart->getTypeFunc;
    int idx = param;
    int type = getTypeFunc(idx,pStart);
    
    if(param == _MENURETURN_EXIT){
        idx = UGTrap_e34;
    }
    else{
        idx = UGTrap_e01 + type - UG_TRAPTYPE_DIR_UP;
    }
    CommMsgTalkWindowAllWrite(CommUnderGetMsgUnderItem(), idx, FALSE, NULL);
}

//--------------------------------------------------------------
/**
 * @brief   トラップメニュースタート
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

#define _TRAPMENU_POSX    (19)
#define _TRAPMENU_POSY    (3)
#define _TRAPMENU_SIZE_X  (12)

void _trapMenuStart_Shop(_START_WORK* pStart )
{
    pStart->getNumFunc = _underBagGetTrapNum; // BAG用取得関数をセット
    pStart->getTypeFunc = _underBagGetTrapID;
    pStart->pIconCallBack = NULL;
    _trapMenuStart(pStart,NULL);
}

void _trapMenuStart_Bag(_START_WORK* pStart )
{
    pStart->cursor = UgMgrGetRecordKeyCursor(_KEY_MENU_BAG_TRAP);
    pStart->line = UgMgrGetRecordKeyLine(_KEY_MENU_BAG_TRAP);
    pStart->getNumFunc = _underBagGetTrapNum; // BAG用取得関数をセット
    pStart->getTypeFunc = _underBagGetTrapID;
    pStart->pLineCallBack = _trapMenuLineSelect;
    pStart->pIconCallBack = NULL;
	pStart->pos_bak2 = pStart->cursor;
    _trapMenuStart(pStart,UnderGroundChangeTrapBagItem);
}

static void _trapMenuStart(_START_WORK* pStart,CHANGE_UG_ITEM_FUNC pChangeFunc)
{
    pGetNumFunc getNumFunc = pStart->getNumFunc;
    pGetTypeFunc getTypeFunc = pStart->getTypeFunc;
    BMPLIST_HEADER list_h;
    int count = getNumFunc(pStart);
    int line = _FIELD_MENU_MAX;

    _startMenuEnd(pStart);
    CommMsgChangeMSGMAN(CommUnderGetMsgUnderItem(), NARC_msg_undergroundtrap_dat, MSGMAN_TYPE_NORMAL);
    //BMPウィンドウ生成
    pStart->menulist = BMP_MENULIST_Create( count+1, HEAPID_FIELD );
    GF_BGL_BmpWinAdd(pStart->pFSys->bgl,&pStart->win,
                     GF_BGL_FRAME3_M, _TRAPMENU_POSX, _TRAPMENU_POSY,
					 BMPWIN_PARAMMENU_SX, BMPWIN_PARAMMENU_SY,
					 FLD_SYSFONT_PAL, BMPWIN_PARAMMENU_CGX );
//                     _TRAPMENU_SIZE_X, line * 2, FLD_SYSFONT_PAL,
//                     FLD_MSG_WIN_CGX - (10 * (line+2) * 2));
    BmpMenuWinWrite(&pStart->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	{
		MSGDATA_MANAGER* msgman;
		int i=0;

		msgman = CommMsgGetMsgManager(CommUnderGetMsgUnderItem());
        for(i=0; i < count ; i++){
			BMP_MENULIST_AddArchiveString( pStart->menulist, msgman,
                                           getTypeFunc(i,pStart), i );
		}
        BMP_MENULIST_AddArchiveString( pStart->menulist, msgman, UGTrapMenuEnd, _MENURETURN_EXIT);
	}

    list_h = MenuListHeader;
    list_h.count = count + 1;
    list_h.line = line;
    list_h.list = pStart->menulist;
    list_h.win = &pStart->win;
    list_h.call_back = pStart->pLineCallBack;
    list_h.icon = pStart->pIconCallBack;
    list_h.work = pStart;

    UgBagCursorLineLimit(pStart, line, list_h.count);
//    pStart->lw = BmpListSet(&list_h, pStart->line, pStart->cursor, HEAPID_FIELD);
    pStart->pUGlw = Ug_BmpListSet(&list_h, pStart->line, pStart->cursor,
                                  HEAPID_FIELD, pChangeFunc,_pUnderItem->pUGData,FALSE);
//    GF_BGL_BmpWinOnVReq(&pStart->win);
    pStart->seq = _START_TRAP_WAIT;
}

//--------------------------------------------------------------
/**
 * @brief   トラップメニュー処理
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static BOOL _trapMenuFunc(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;
    u32	ret;
    u16 line,cursor;

    ret = Ug_BmpListMain(pStart->pUGlw);
    BmpListPosGet( pStart->pUGlw->pBmpList, &line, &cursor );
    UgMgrSetRecordKey(_KEY_MENU_BAG_TRAP, cursor, line);
    _udCurDisp(pStart, line,  BmpListParamGet(pStart->pUGlw->pBmpList,BMPLIST_ID_COUNT), _FIELD_MENU_MAX);
    
    if(CommIsError()){  // エラー時はキャンセル扱いにする
        ret = BMPLIST_CANCEL;
    }
    if(ret == _MENURETURN_EXIT){
        ret = BMPLIST_CANCEL;
    }
    switch(ret){
    case BMPLIST_NULL:
        return FALSE;
    case BMPLIST_CANCEL:
        _menuCancel2MainMenu(pStart);
        break;
    default:
        {
            CommMsgTalkWindowEnd(CommUnderGetMsgUnderItem());
            _pUnderItem->deleteIndex = ret;   // 消すアイテムが入っているindex
            _pUnderItem->deleteItem = _underBagGetTrapID(ret,pStart);    // 消すアイテム番号
            if( _pUnderItem->deleteItem == UG_TRAPTYPE_DRILL){  // ドリルは秘密基地制御用
                CommSecretBaseDrillStart();
                pStart->seq = _START_DRILL_END;
            }
            else{
                _startMenuEnd(pStart);
                _subMenuStart(pStart, _DIG_COMMAND);
                pStart->seq = _START_TRAP_WAIT_SUB;
                CommMsgRegisterUGTrapNameIndex(CommUnderGetMsgUnderWorld(), 2, _pUnderItem->deleteItem);
                CommMsgTalkWindowAllWrite(CommUnderGetMsgUnderWorld(),mes_uw_item_06,FALSE,NULL);
//                CommTrapInfoAddTrap(_underBagGetTrapID(ret,pStart));
            }
        }
        FComAct_SetDrawFlg(pStart->fca,FCA_UCURSOR, FALSE);
        FComAct_SetDrawFlg(pStart->fca,FCA_DCURSOR, FALSE);
        break;
    }
    return TRUE;
}

static BOOL _trapSubMenuFunc(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;
    u32	ret;
	u16 tmp_pos_bak;

    ret = BmpListMain(pStart->subLw);

#if 1
	//BMPリストの全体位置を取得
	tmp_pos_bak = pStart->pos_bak2;		//退避
	BmpListDirectPosGet( pStart->subLw, &pStart->pos_bak2 );

	//カーソルが動いたかチェック
	if( tmp_pos_bak != pStart->pos_bak2 ){
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}
#endif

    switch(ret){
    case BMPLIST_NULL:
        return FALSE;
    case BMPLIST_CANCEL:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        _subMenuEnd(pStart);
        _trapMenuStart_Bag(pStart);
        pStart->seq = _START_TRAP_WAIT;
        break;
    default:
        _subMenuEnd(pStart);
        if(ret == _DIG_COMMAND){  // 埋める
            CommTrapInfoAddTrap(_underBagGetTrapID(_pUnderItem->deleteIndex,pStart));
            Snd_SePlay(UG_SE_BURY);  // 埋めた
//            pStart->seq = _START_END;
            pStart->seq = _START_DRILL_END;
        }
        else if(ret == _TRASH_COMMAND){  // すてる
			Snd_SePlay( SEQ_SE_DP_SELECT );
            CommUnderBagDeleteTrap(_pUnderItem->deleteItem);
            CommMsgRegisterUGTrapNameIndex(CommUnderGetMsgUnderWorld(), 2, _pUnderItem->deleteItem);
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                                   mes_uw_item_07, FALSE, NULL);
            pStart->menuCallBack = (void*)_trapMenuStart_Bag;
            pStart->seqNext = _START_TRAP_WAIT;
            pStart->seq = _START_NEXT;
        }
        break;
    }

    return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   たまメニューで石をおいた場合のコールバック
 * @param   type  石タイプ
 * @retval  none
 */
//--------------------------------------------------------------
void CommUnderBagDeleteStone(int type)
{
    GF_ASSERT(_pUnderItem->deleteItem == type);
    UnderGroundDelStoneBagItem(_pUnderItem->pUGData ,_pUnderItem->deleteIndex);
}

//--------------------------------------------------------------
/**
 * @brief   いしメニュー説明文
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _stoneMenuLineSelect(BMPLIST_WORK * wk,u32 param,u8 mode)
{
    _START_WORK* pStart = (_START_WORK*)BmpListParamGet(wk, BMPLIST_ID_WORK);
    pGetTypeFunc getTypeFunc = pStart->getTypeFunc;
    int idx = param;
    int type = getTypeFunc(idx,pStart);
    
    if(param == _MENURETURN_EXIT){
        idx = UGItemEnd1;
    }
    else{
        idx = UGItem_e00 + type;
    }
    CommMsgTalkWindowAllWrite(CommUnderGetMsgUnderItem(), idx, FALSE, NULL);
}

//--------------------------------------------------------------
/**
 * @brief   いしメニュースタート
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

#define _STONEMENU_POSX    (19)
#define _STONEMENU_POSY    (3)
#define _STONEMENU_SIZE_X  (12)

void _stoneMenuStart_ShopBag(_START_WORK* pStart)
{
    pStart->getNumFunc = _underBagGetStoneNum; // BAG用取得関数をセット
    pStart->getTypeFunc = _underBagGetStoneID;
    pStart->getCaratFunc = _underBagGetStoneCarat;
    pStart->pLineCallBack = _stoneMenuLineSelect;
    _stoneMenuStart(pStart,UnderGroundChangeStoneBagItem);
}

static void _stoneMenuStart_Bag(_START_WORK* pStart)
{
    pStart->cursor = UgMgrGetRecordKeyCursor(_KEY_MENU_BAG_STONE);
    pStart->line = UgMgrGetRecordKeyLine(_KEY_MENU_BAG_STONE);
    pStart->getNumFunc = _underBagGetStoneNum; // BAG用取得関数をセット
    pStart->getTypeFunc = _underBagGetStoneID;
    pStart->getCaratFunc = _underBagGetStoneCarat;
    pStart->pLineCallBack = _stoneMenuLineSelect;
	pStart->pos_bak2 = pStart->cursor;
    _stoneMenuStart(pStart,UnderGroundChangeStoneBagItem);
}

static void _stoneMenuStart(_START_WORK* pStart,CHANGE_UG_ITEM_FUNC pChangeFunc)
{
    pGetNumFunc getNumFunc = pStart->getNumFunc;
    pGetTypeFunc getTypeFunc = pStart->getTypeFunc;
    pGetCaratFunc getCaratFunc = pStart->getCaratFunc;
    BMPLIST_HEADER list_h;
    int count = getNumFunc(pStart);
    int line = _FIELD_MENU_MAX;

    _startMenuEnd(pStart);
    CommMsgChangeMSGMAN(CommUnderGetMsgUnderItem(), NARC_msg_undergrounditem_dat, MSGMAN_TYPE_NORMAL);
    //BMPウィンドウ生成
    pStart->menulist = BMP_MENULIST_Create( count+1, HEAPID_FIELD );


    GF_BGL_BmpWinAdd(pStart->pFSys->bgl,&pStart->win,
                     GF_BGL_FRAME3_M, _STONEMENU_POSX, _STONEMENU_POSY,
 					 BMPWIN_PARAMMENU_SX, BMPWIN_PARAMMENU_SY,
					 FLD_SYSFONT_PAL, BMPWIN_PARAMMENU_CGX );
//                     _STONEMENU_SIZE_X, line * 2, FLD_SYSFONT_PAL,
//                     FLD_MSG_WIN_CGX-(10 * (line+2) * 2));
    BmpMenuWinWrite(&pStart->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	{
		MSGDATA_MANAGER* msgman;
		int i;

		msgman = CommMsgGetMsgManager(CommUnderGetMsgUnderItem());
        //MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_undergrounditem_dat, HEAPID_FIELD);
        for(i = 0; i < count; i++) {
            WORDSET_RegisterUGItemName(pStart->pWordSet, 2, getTypeFunc(i,pStart) );
            WORDSET_RegisterNumber(pStart->pWordSet, 6, getCaratFunc(i,pStart), 2,
                                   NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
            MSGMAN_GetString( CommMsgGetMsgManager(CommUnderGetMsgUnderWorld()), UGBallMenuDef,
                              pStart->pStrBuf2 );
            WORDSET_ExpandStr( pStart->pWordSet,  pStart->pStrBuf1,
                               pStart->pStrBuf2 );
            BMP_MENULIST_AddString(pStart->menulist,  pStart->pStrBuf1, i);
		}
        BMP_MENULIST_AddArchiveString( pStart->menulist, msgman,
                                       UGItemEnd, _MENURETURN_EXIT );
	}

    list_h = MenuListHeader;
    list_h.count = count + 1;
    list_h.line = line;
    list_h.list = pStart->menulist;
    list_h.win = &pStart->win;
    list_h.call_back = pStart->pLineCallBack;
    list_h.work = pStart;
    OHNO_PRINT("line cur %d %d\n",pStart->line, pStart->cursor, count);
    UgBagCursorLineLimit(pStart, line, list_h.count);
    OHNO_PRINT("--------line cur %d %d\n",pStart->line, pStart->cursor, count);
    pStart->pUGlw = Ug_BmpListSet(&list_h, pStart->line, pStart->cursor,
                                  HEAPID_FIELD, pChangeFunc,_pUnderItem->pUGData,FALSE);
//    pStart->lw = BmpListSet(&list_h, pStart->line, pStart->cursor, HEAPID_FIELD);
//    GF_BGL_BmpWinOnVReq(&pStart->win);
    pStart->seq = _START_STONE_WAIT;
}




static BOOL _stoneMenuFunc(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;
    u32	ret;
    u16 line,cursor;

    ret = Ug_BmpListMain(pStart->pUGlw);
    BmpListPosGet( pStart->pUGlw->pBmpList, &line, &cursor );
    UgMgrSetRecordKey(_KEY_MENU_BAG_STONE, cursor, line);
    _udCurDisp(pStart, line,  BmpListParamGet(pStart->pUGlw->pBmpList,BMPLIST_ID_COUNT), _FIELD_MENU_MAX);

    if(CommIsError()){  // エラー時はキャンセル扱いにする
        ret = BMPLIST_CANCEL;
    }
    if(ret == _MENURETURN_EXIT){
        ret = BMPLIST_CANCEL;
    }
    switch(ret){
    case BMPLIST_NULL:
        return FALSE;
    case BMPLIST_CANCEL:
        _menuCancel2MainMenu(pStart);
        break;
    default:
        _startMenuEnd(pStart);
        _pUnderItem->deleteIndex = ret;   // 消すアイテムが入っているindex
        _pUnderItem->deleteItem = _underBagGetStoneID(ret,pStart);    // 消すアイテム番号
        _subMenuStart(pStart, _DIG_COMMAND);
        pStart->seq = _START_STONE_WAIT_SUB;
        CommMsgRegisterUGItemNameIndex(CommUnderGetMsgUnderWorld(), 2, _pUnderItem->deleteItem);
        CommMsgTalkWindowAllWrite(CommUnderGetMsgUnderWorld(),mes_uw_item_06,FALSE,NULL);
        FComAct_SetDrawFlg(pStart->fca,FCA_UCURSOR, FALSE);
        FComAct_SetDrawFlg(pStart->fca,FCA_DCURSOR, FALSE);
        break;
    }
    return TRUE;
}

static BOOL _stoneSubMenuFunc(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;
    u32	ret;
	u16 tmp_pos_bak;

    ret = BmpListMain(pStart->subLw);

#if 1
	//BMPリストの全体位置を取得
	tmp_pos_bak = pStart->pos_bak2;		//退避
	BmpListDirectPosGet( pStart->subLw, &pStart->pos_bak2 );

	//カーソルが動いたかチェック
	if( tmp_pos_bak != pStart->pos_bak2 ){
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}
#endif

    switch(ret){
    case BMPLIST_NULL:
        return FALSE;
    case BMPLIST_CANCEL:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        _subMenuEnd(pStart);
        _stoneMenuStart_Bag(pStart);
        pStart->seq = _START_STONE_WAIT;
        break;
    default:
        _subMenuEnd(pStart);
        if(ret == _DIG_COMMAND){  // 埋める
            int netID = CommGetCurrentID();
            int x = CommPlayerGetPosXDirAdd(netID);
            int z = CommPlayerGetPosZDirAdd(netID);
            CommMsgTalkWindowEnd(CommUnderGetMsgUnderItem());
            CommDigStoneAddStone( _pUnderItem->deleteItem,
                                  _underBagGetStoneCarat(_pUnderItem->deleteIndex, pStart),
                                  x,z);
        }
        else if(ret == _TRASH_COMMAND){  // すてる
			Snd_SePlay( SEQ_SE_DP_SELECT );
            CommUnderBagDeleteStone(_pUnderItem->deleteItem);
            CommMsgRegisterUGItemNameIndex(CommUnderGetMsgUnderWorld(), 2, _pUnderItem->deleteItem);
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                                   mes_uw_item_07, FALSE, NULL);
        }
        pStart->menuCallBack = (void*)_stoneMenuStart_Bag;
        pStart->seqNext = _START_STONE_WAIT;
        pStart->seq = _START_NEXT;
        break;
    }
    return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   たからメニュー説明文
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

void _treasureMenuLineSelect(BMPLIST_WORK * wk,u32 param,u8 mode)
{
    _START_WORK* pStart = (_START_WORK*)BmpListParamGet(wk, BMPLIST_ID_WORK);
    pGetTypeFunc getTypeFunc = pStart->getTypeFunc;
    int idx = param;
    int type = getTypeFunc(idx,pStart);
    
    if(param == _MENURETURN_EXIT){
        idx = UGItemEnd1;
    }
    else{
        idx = UGItem_e00 + type;
    }
    CommMsgTalkWindowAllWrite(CommUnderGetMsgUnderItem(),idx,FALSE,NULL);
}

//--------------------------------------------------------------
/**
 * @brief   たからメニュースタート
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

#define _TREASUREMENU_POSX    (19)
#define _TREASUREMENU_POSY    (3)
#define _TREASUREMENU_SIZE_X  (12)

void _treasureMenuStart_Shop(_START_WORK* pStart)
{
    pStart->getNumFunc = _underBagGetTreasureNum; // BAG用取得関数をセット
    pStart->getTypeFunc = _underBagGetTreasureID;
    _treasureMenuStart(pStart,NULL);
}

void _treasureMenuStart_Bag(_START_WORK* pStart)
{
    pStart->cursor = UgMgrGetRecordKeyCursor(_KEY_MENU_BAG_TREASURE);
    pStart->line = UgMgrGetRecordKeyLine(_KEY_MENU_BAG_TREASURE);
    pStart->getNumFunc = _underBagGetTreasureNum; // BAG用取得関数をセット
    pStart->getTypeFunc = _underBagGetTreasureID;
    pStart->pLineCallBack = _treasureMenuLineSelect;
	pStart->pos_bak2 = pStart->cursor;
    _treasureMenuStart(pStart,UnderGroundChangeTreasureBagItem);
}

static void _treasureMenuStart(_START_WORK* pStart, CHANGE_UG_ITEM_FUNC pChangeFunc)
{
    pGetNumFunc getNumFunc = pStart->getNumFunc;
    pGetTypeFunc getTypeFunc = pStart->getTypeFunc;
    BMPLIST_HEADER list_h;
    int count = getNumFunc(pStart); //_underBagGetTreasureNum();
    int line = _FIELD_MENU_MAX;

    _startMenuEnd(pStart);
    CommMsgChangeMSGMAN(CommUnderGetMsgUnderItem(), NARC_msg_undergrounditem_dat, MSGMAN_TYPE_NORMAL);
    //BMPウィンドウ生成
    pStart->menulist = BMP_MENULIST_Create( count+1, HEAPID_FIELD );
    GF_BGL_BmpWinAdd(pStart->pFSys->bgl,&pStart->win,
                     GF_BGL_FRAME3_M, _TREASUREMENU_POSX, _TREASUREMENU_POSY,
					 BMPWIN_PARAMMENU_SX, BMPWIN_PARAMMENU_SY,
					 FLD_SYSFONT_PAL, BMPWIN_PARAMMENU_CGX );
//                     _TREASUREMENU_SIZE_X, line * 2, FLD_SYSFONT_PAL,
//                     FLD_MSG_WIN_CGX - (10* (line+2) * 2));
    BmpMenuWinWrite(&pStart->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	{
		MSGDATA_MANAGER* msgman;
		int i=0;

		msgman = CommMsgGetMsgManager(CommUnderGetMsgUnderItem());
        for(i=0; i < count ; i++){
			BMP_MENULIST_AddArchiveString( pStart->menulist, msgman,
                                           getTypeFunc(i, pStart), i );
		}
        BMP_MENULIST_AddArchiveString( pStart->menulist, msgman, UGItemEnd, _MENURETURN_EXIT);
	}

    list_h = MenuListHeader;
    list_h.count = count + 1;
    list_h.line = line;
    list_h.list = pStart->menulist;
    list_h.win = &pStart->win;
    list_h.call_back = pStart->pLineCallBack;
    list_h.work = pStart;
    UgBagCursorLineLimit(pStart, line, list_h.count);
    pStart->pUGlw = Ug_BmpListSet(&list_h, pStart->line, pStart->cursor,
                                  HEAPID_FIELD, pChangeFunc,_pUnderItem->pUGData,FALSE);
//    pStart->lw = BmpListSet(&list_h, pStart->line, pStart->cursor, HEAPID_FIELD);
//    GF_BGL_BmpWinOnVReq(&pStart->win);
    pStart->seq = _START_TREASURE_WAIT;
}

//--------------------------------------------------------------
/**
 * @brief   たからメニュー処理
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static BOOL _treasureMenuFunc(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;
    u32	ret;
    u16 line,cursor;

    ret = Ug_BmpListMain(pStart->pUGlw);
    BmpListPosGet( pStart->pUGlw->pBmpList, &line, &cursor );
    UgMgrSetRecordKey(_KEY_MENU_BAG_TREASURE, cursor, line);
    _udCurDisp(pStart, line,  BmpListParamGet(pStart->pUGlw->pBmpList,BMPLIST_ID_COUNT), _FIELD_MENU_MAX);
    
    if(CommIsError()){  // エラー時はキャンセル扱いにする
        ret = BMPLIST_CANCEL;
    }
    if(ret == _MENURETURN_EXIT){
        ret = BMPLIST_CANCEL;
    }
    switch(ret){
    case BMPLIST_NULL:
        return FALSE;
    case BMPLIST_CANCEL:
        _menuCancel2MainMenu(pStart);
        break;
    default:
        _startMenuEnd(pStart);
        
        _pUnderItem->deleteIndex = ret;   // 消すアイテムが入っているindex
        _pUnderItem->deleteItem = _underBagGetTreasureID(ret,pStart);    // 消すアイテム番号
        _subMenuStart(pStart, _IN_COMMAND);
        CommMsgRegisterUGItemNameIndex(CommUnderGetMsgUnderWorld(), 2, _pUnderItem->deleteItem);
        CommMsgTalkWindowAllWrite(CommUnderGetMsgUnderWorld(),mes_uw_item_06,FALSE,NULL);

        pStart->seq = _START_TREASURE_WAIT_SUB;
        FComAct_SetDrawFlg(pStart->fca,FCA_UCURSOR, FALSE);
        FComAct_SetDrawFlg(pStart->fca,FCA_DCURSOR, FALSE);
        break;
    }
    return TRUE;
}


static BOOL _treasureSubMenuFunc(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;
    u32	ret;
	u16 tmp_pos_bak;

    ret = BmpListMain(pStart->subLw);

#if 1
	//BMPリストの全体位置を取得
	tmp_pos_bak = pStart->pos_bak2;		//退避
	BmpListDirectPosGet( pStart->subLw, &pStart->pos_bak2 );

	//カーソルが動いたかチェック
	if( tmp_pos_bak != pStart->pos_bak2 ){
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}
#endif

    switch(ret){
    case BMPLIST_NULL:
        return FALSE;
    case BMPLIST_CANCEL:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        _subMenuEnd(pStart);
        _treasureMenuStart_Bag(pStart);
        pStart->seq = _START_TREASURE_WAIT;
        break;
    default:
        _subMenuEnd(pStart);
        if(ret == _IN_COMMAND){  // 地上に輸送
            int item = UnderGroundTreasureItem2Item(_pUnderItem->deleteItem);
            MYITEM* myitem = SaveData_GetMyItem(pStart->pFSys->savedata);
			Snd_SePlay( SEQ_SE_DP_SELECT );
            if(MyItem_AddItem(myitem,item, 1,HEAPID_FIELD)){
                UnderGroundDelTreasureBagItem(_pUnderItem->pUGData, _pUnderItem->deleteIndex);
                CommMsgRegisterUGItemNameIndex(CommUnderGetMsgUnderWorld(), 0, _pUnderItem->deleteItem);
                if((_pUnderItem->deleteItem == DIG_PARTS_GENKI_S) || (_pUnderItem->deleteItem == DIG_PARTS_GENKI_L)){
                    CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_81, FALSE, NULL);
                }
                else{
                    CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_79, FALSE, NULL);
                }
            }
            else{
                CommMsgRegisterUGItemNameIndex(CommUnderGetMsgUnderWorld(), 0, _pUnderItem->deleteItem);
                CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_80, FALSE, NULL);
            }
        }
        else if(ret == _TRASH_COMMAND){  // すてる
			Snd_SePlay( SEQ_SE_DP_SELECT );
            UnderGroundDelTreasureBagItem(_pUnderItem->pUGData, _pUnderItem->deleteIndex);
            CommMsgRegisterUGItemNameIndex(CommUnderGetMsgUnderWorld(), 2, _pUnderItem->deleteItem);
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), mes_uw_item_07, FALSE, NULL);
        }
        pStart->menuCallBack = (void*)_treasureMenuStart_Bag;
        pStart->seqNext = _START_TREASURE_WAIT;
        pStart->seq = _START_NEXT;
        break;
    }
    return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   会話をやめる
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _startExit( _START_WORK* pStart )
{
    pStart->seq = _START_END;
}

//--------------------------------------------------------------
/**
 * @brief   地上に戻る
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _underExit( _START_WORK* pStart )
{
    _startMenuEnd(pStart);

    if(UgSecretBaseIsSecretBasePlace(Player_NowGPosXGet( pStart->pFSys->player ),
                                     Player_NowGPosZGet( pStart->pFSys->player ))){
        // 秘密基地の中からは戻れない
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                               msg_underworld_66, FALSE, NULL);
        pStart->seq = _START_QUIT;
    }
    else{
        pStart->msgIndex =
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                                   msg_underworld_52, FALSE, NULL);
        pStart->seq = _START_EXIT_WAIT;
    }
}

//--------------------------------------------------------------
/**
 * @brief   地上に戻るかどうかをYESNOで確認
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _exitTalkFunc(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;

    if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
        pStart->pYesNoWork =
            BmpYesNoSelectInit( pStart->pFSys->bgl,
                                &_yesNoBmpDat,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL, HEAPID_FIELD );
        pStart->seq = _START_EXIT_WAIT2;
    }
}

//--------------------------------------------------------------
/**
 * @brief   地上に戻るかどうかをYESNOで確認
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _exitTalkFunc2(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;
    int ret = BmpYesNoSelectMain(pStart->pYesNoWork, HEAPID_FIELD);
    if(ret == BMPMENU_NULL){  // まだ選択中
        return;
    }else if(ret == 0){ // はいを選択した場合
        pStart->seq = _START_EXIT_UNDERGROUND;  // 地上へ
    }
    else{  // いいえを選択した場合
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        _menuCancel2MainMenu(pStart);
    }
    pStart->pYesNoWork = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   デバッグ用メニューコールバック
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _stateEndCallBack(void* pWork)
{
    _START_WORK* pStart = pWork;
//    pStart->seq = _START_END;
    _menuCancel2MainMenu(pStart);
}

static void _statusList( _START_WORK* pStart )
{
    _startMenuEnd(pStart);

    UgRecordUpdateMyData();
    UgRecordStatusListStart(pStart->pFSys->bgl,
                            SaveData_GetMyStatus(
                                GameSystem_GetSaveData(pStart->pFSys)),
                            _stateEndCallBack,pStart,TRUE);
    pStart->seq = _START_STATUS_WAIT;
}

//--------------------------------------------------------------
/**
 * @brief   旗の消去に関するメニュー起動
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------


typedef enum{
    _DELMSG_WAIT,
    _DEL_YESNO_WAIT,
    _DEL_END,
    _DELETE_FLAG_END,
    _WAIT_END,
};


void CommUnderBagFlagStart(pBagEndFunc func, FIELDSYS_WORK* pFSys)
{
    _START_WORK* pStart;
    BMPLIST_HEADER list_h;

    pStart = sys_AllocMemory(HEAPID_FIELD, sizeof(_START_WORK));
    MI_CpuFill8(pStart, 0, sizeof(_START_WORK));
    pStart->pFSys = pFSys;
    pStart->endfunc = func;
    pStart->seq = _DELMSG_WAIT;
    pStart->pStrBuf1 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    pStart->pStrBuf2 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    pStart->pWordSet = WORDSET_Create( HEAPID_FIELD );

    // フィールドの動きを止める
    CommPlayerHold();

    CommMsgTalkWindowStart(CommUnderGetMsgUnderFlag(),mes_uw_flag_01,FALSE,NULL);

    pStart->pTCB = TCB_Add(_flagProcess, pStart, _MENU_UG_PRI);
    UgMgrSetNowTCB(pStart,pStart->pTCB,UgGoodsMenuForceDelete2);
}


//==============================================================================
/**
 * ハタを消すかどうか問い合わせる
 * @param   targetID   話し相手のINDEX
 * @retval  none
 */
//==============================================================================

static void _delWait(_START_WORK* pStart)
{
    if( CommMsgIsOutputing(CommUnderGetMsgUnderFlag()) == 0 ){
        // はいいいえウインドウを出す
        pStart->pYesNoWork =
            BmpYesNoSelectInit( pStart->pFSys->bgl,
                                &_yesNoBmpDat,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL, HEAPID_FIELD );
        pStart->seq = _DEL_YESNO_WAIT;
    }
}

static void _delYesNoWait(_START_WORK* pStart)
{
    int ret = BmpYesNoSelectMain(pStart->pYesNoWork, HEAPID_FIELD);
    if(ret == BMPMENU_NULL){  // まだ選択中
        return;
    }else if(ret == 0){ // はいを選択した場合
        pStart->seq = _DELETE_FLAG_END;
    }
    else{  // いいえを選択した場合
        pStart->seq = _DEL_END;
    }
    pStart->pYesNoWork = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   ウインドウ消去
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _delEnd(TCB_PTR tcb, _START_WORK* pStart,BOOL bHold)
{

    if(pStart->pYesNoWork){
        BmpYesNoWinDel( pStart->pYesNoWork, HEAPID_FIELD );
    }
    
    STRBUF_Delete(pStart->pStrBuf1);
    STRBUF_Delete(pStart->pStrBuf2);
    WORDSET_Delete(pStart->pWordSet);
    
    CommMsgTalkWindowEnd(CommUnderGetMsgUnderFlag());
    CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
    if(pStart->endfunc != NULL){
        pStart->endfunc(0);
    }
    pStart->pTCB = NULL;
    if(pStart->fca){
        FComAct_Delete(pStart->fca);
    }
    sys_FreeMemoryEz(pStart);
    if(!bHold){
        CommPlayerHoldEnd();
    }
    TCB_Delete(tcb);
//    CommUnderResetMsgDataManager();
}

//--------------------------------------------------------------
/**
 * @brief   旗の消去に関するメニューの管理プロセス
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _flagProcess(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;

    if(!CommPlayerIsFlagData(CommGetCurrentID())){ // ハタがなくなった場合
        if((pStart->seq == _DELMSG_WAIT) || (pStart->seq == _DEL_YESNO_WAIT)){
            pStart->seq = _DEL_END;
        }
    }
    switch(pStart->seq){
      case _DELMSG_WAIT:
        _delWait(work);
        break;
      case _DEL_YESNO_WAIT:
        _delYesNoWait(work);
        break;
      case _DEL_END:
        UgMgrEndNowTCB();
        _delEnd(tcb, work, FALSE);
        return;
      case _DELETE_FLAG_END:
        UgMgrEndNowTCB();
        _delEnd(tcb, work, TRUE);
        {
            u8 state = UNDER_FLAG_DEL;
            CommSendFixSizeData(CF_FLAG_STATE,&state);// はたすて送信
        }
        return;
      case _WAIT_END:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderFlag()) == 0 ){
            if(sys.trg & PAD_BUTTON_DECIDE){
                pStart->seq = _DEL_END;
            }
        }
        break;
    }
}

//--------------------------------------------------------------
/**
 * @brief   グッズメニュー説明文
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

void _goodsMenuLineSelect(BMPLIST_WORK * wk,u32 param,u8 mode)
{
    _START_WORK* pStart = (_START_WORK*)BmpListParamGet(wk, BMPLIST_ID_WORK);
    pGetTypeFunc getTypeFunc = pStart->getTypeFunc;
    int idx = param;
    int type = getTypeFunc(idx,pStart);
    
    if(param == BMPLIST_CANCEL){
        idx = UGGoods_e001;
    }
    else{
        idx = UGGoods_e007 + type - GOODS_CHAIR_PC01;
    }
    CommMsgTalkWindowAllWrite(CommUnderGetMsgUnderItem(),idx,FALSE,NULL);
}

//--------------------------------------------------------------
/**
 * @brief   グッズメニュー説明文パソコン用
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _goodsPcMenuLineSelect(BMPLIST_WORK * wk,u32 param,u8 mode)
{
    _START_WORK* pStart = (_START_WORK*)BmpListParamGet(wk, BMPLIST_ID_WORK);
    int idx = param;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));

    if (!UnderGroundIsEntryGoodsPCItem(pUGData , idx)){ // 配置されていない
        BmpListTmpColorChange( wk, FBMP_COL_BLACK, FBMP_COL_WHITE , FBMP_COL_BLK_SDW );
    }else{		//配置済み
        BmpListTmpColorChange( wk, FBMP_COL_BLK_SDW, FBMP_COL_WHITE , FBMP_COL_BLK_SDW );
    }
}

//--------------------------------------------------------------
/**
 * @brief   グッズメニュースタート
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

void _goodsMenuStart_Shop(_START_WORK* pStart)
{
    pStart->getNumFunc = _underBagGetGoodsNum; // BAG用取得関数をセット
    pStart->getTypeFunc = _underBagGetGoodsID;
    pStart->pIconCallBack = NULL;
    _goodsMenuStart(pStart,NULL);
}

void _goodsMenuStart_Bag(_START_WORK* pStart)
{
    pStart->cursor = UgMgrGetRecordKeyCursor(_KEY_MENU_BAG_GOODS);
    pStart->line = UgMgrGetRecordKeyLine(_KEY_MENU_BAG_GOODS);
    pStart->getNumFunc = _underBagGetGoodsNum; // BAG用取得関数をセット
    pStart->getTypeFunc = _underBagGetGoodsID;
    pStart->pLineCallBack = _goodsMenuLineSelect;
    pStart->pIconCallBack = NULL;
	pStart->pos_bak2 = pStart->cursor;
    _goodsMenuStart(pStart,UnderGroundChangeGoodsBagItem);

}

void _goodsMenuStart_BagPc(_START_WORK* pStart)
{
    pStart->getNumFunc = _underBagGetGoodsNum; // BAG用取得関数をセット
    pStart->getTypeFunc = _underBagGetGoodsID;
    pStart->pLineCallBack = _goodsMenuLineSelect;
    pStart->pIconCallBack = NULL;
    _goodsMenuStart(pStart,UnderGroundChangeGoodsBagItem);
}

void _goodsMenuStart_Pc(_START_WORK* pStart)
{
    pStart->getNumFunc = _underPcGetGoodsNum; // PC用取得関数をセット
    pStart->getTypeFunc = _underPcGetGoodsID;
    pStart->pLineCallBack = _goodsMenuLineSelect;
    pStart->pIconCallBack = _goodsPcMenuLineSelect;
    _goodsMenuStart(pStart,UnderGroundChangeGoodsPcItem);
}

static void _goodsMenuStart(_START_WORK* pStart, CHANGE_UG_ITEM_FUNC pChangeFunc)
{
    pGetNumFunc getNumFunc = pStart->getNumFunc;
    pGetTypeFunc getTypeFunc = pStart->getTypeFunc;
    BMPLIST_HEADER list_h;
    int count = getNumFunc(pStart); //_underBagGetGoodsNum();
    int line = _FIELD_MENU_MAX;

    _startMenuEnd(pStart);
    CommMsgChangeMSGMAN(CommUnderGetMsgUnderItem(), NARC_msg_undergroundgoods_dat, MSGMAN_TYPE_NORMAL);
    //BMPウィンドウ生成
    pStart->menulist = BMP_MENULIST_Create( count+1, HEAPID_FIELD );
    GF_BGL_BmpWinAdd(pStart->pFSys->bgl,&pStart->win,
                     GF_BGL_FRAME3_M, _TRAPMENU_POSX, _TRAPMENU_POSY,
					 BMPWIN_PARAMMENU_SX, BMPWIN_PARAMMENU_SY,
					 FLD_SYSFONT_PAL, BMPWIN_PARAMMENU_CGX );
//                     _TRAPMENU_SIZE_X, line * 2, FLD_SYSFONT_PAL,
//                     FLD_MSG_WIN_CGX - (10 * (line + 2) * 2));
    BmpMenuWinWrite(&pStart->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	{
		MSGDATA_MANAGER* msgman;
		int i=0;

		msgman = CommMsgGetMsgManager(CommUnderGetMsgUnderItem());
		for(i=0; i < count ; i++)
		{
			BMP_MENULIST_AddArchiveString( pStart->menulist, msgman,
                                           getTypeFunc(i,pStart), i);
		}
        BMP_MENULIST_AddArchiveString( pStart->menulist, msgman, UGGoodsMenuEnd, BMPLIST_CANCEL);
	}

    list_h = MenuListHeader;
    list_h.count = count + 1;
    list_h.line = line;
    list_h.icon = pStart->pIconCallBack;
    list_h.list = pStart->menulist;
    list_h.win = &pStart->win;
    list_h.call_back = pStart->pLineCallBack;
    list_h.work = pStart;
    UgBagCursorLineLimit(pStart, line, list_h.count);
    pStart->pUGlw = Ug_BmpListSet(&list_h, pStart->line, pStart->cursor,
                                  HEAPID_FIELD, pChangeFunc,_pUnderItem->pUGData,FALSE);
//    pStart->lw = BmpListSet(&list_h, pStart->line,  pStart->cursor, HEAPID_FIELD);
//    GF_BGL_BmpWinOnVReq(&pStart->win);
    pStart->seq = _START_GOODS_WAIT;
}

//--------------------------------------------------------------
/**
 * @brief   GOODSメニュー処理
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static BOOL _goodsMenuFunc(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;
    u32	ret;
    u16 line,cursor;

    ret = Ug_BmpListMain(pStart->pUGlw);
    BmpListPosGet( pStart->pUGlw->pBmpList, &line, &cursor );
    UgMgrSetRecordKey(_KEY_MENU_BAG_GOODS, cursor, line);
    _udCurDisp(pStart, line,  BmpListParamGet(pStart->pUGlw->pBmpList,BMPLIST_ID_COUNT), _FIELD_MENU_MAX);

    if(CommIsError()){  // エラー時はキャンセル扱いにする
        ret = BMPLIST_CANCEL;
    }
    if(ret == _MENURETURN_EXIT){
        ret = BMPLIST_CANCEL;
    }
    switch(ret){
    case BMPLIST_NULL:
        return FALSE;
    case BMPLIST_CANCEL:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        _menuCancel2MainMenu(pStart);
        break;
    default:
        _startMenuEnd(pStart);
        _pUnderItem->deleteIndex = ret;   // 消すアイテムが入っているindex
        _pUnderItem->deleteItem = _underBagGetGoodsID(ret,pStart);    // 消すアイテム番号
        _subMenuStart(pStart, _TRASH_COMMAND);
        CommMsgRegisterUGGoodsNameIndex(CommUnderGetMsgUnderWorld(), 2, _pUnderItem->deleteItem);
        CommMsgTalkWindowAllWrite(CommUnderGetMsgUnderWorld(),mes_uw_item_06,FALSE,NULL);
        pStart->seq = _START_GOODS_WAIT_SUB;
        FComAct_SetDrawFlg(pStart->fca,FCA_UCURSOR, FALSE);
        FComAct_SetDrawFlg(pStart->fca,FCA_DCURSOR, FALSE);
        break;
    }
    return TRUE;
}

static BOOL _goodsSubMenuFunc(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;
    u32	ret;
	u16 tmp_pos_bak;

    ret = BmpListMain(pStart->subLw);

#if 1
	//BMPリストの全体位置を取得
	tmp_pos_bak = pStart->pos_bak2;		//退避
	BmpListDirectPosGet( pStart->subLw, &pStart->pos_bak2 );

	//カーソルが動いたかチェック
	if( tmp_pos_bak != pStart->pos_bak2 ){
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}
#endif

    switch(ret){
    case BMPLIST_NULL:
        return FALSE;
    case BMPLIST_CANCEL:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        _subMenuEnd(pStart);
        _goodsMenuStart_Bag(pStart);
        pStart->seq = _START_GOODS_WAIT;
        break;
    default:
        _subMenuEnd(pStart);
        if(ret == _TRASH_COMMAND){  // すてる
			Snd_SePlay( SEQ_SE_DP_SELECT );
            UnderGroundDelGoodsBagItem(_pUnderItem->pUGData, _pUnderItem->deleteIndex);
            CommMsgRegisterUGGoodsNameIndex(CommUnderGetMsgUnderWorld(), 2, _pUnderItem->deleteItem);
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                                   mes_uw_item_07, FALSE, NULL);
        }
        pStart->menuCallBack = (void*)_goodsMenuStart_Bag;
        pStart->seqNext = _START_GOODS_WAIT;
        pStart->seq = _START_NEXT;
        break;
    }
    return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief   GOODSメニュー強制終了処理
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

void UgGoodsMenuForceDelete(void* work, u32 ret)
{
    _START_WORK* pStart = work;

    _startMenuEnd(pStart);

    UgMgrSetMyTrapRadarDisp();
    UnderRecordReset();
    UgTrapRecvNatureRadarEnd();  // 終了処理
    UgFossilPcRadarEnd();
    UgStonePcRadarEnd();

    if(pStart->pWork){
        UgRecordFlagListEnd(pStart->pWork);
    }

    if(pStart->pYesNoWork){
        BmpYesNoWinDel( pStart->pYesNoWork, HEAPID_FIELD );
    }
    _subMenuEnd(pStart);

/*    if(GF_MSG_PrintEndCheck(pStart->msgIndex) ){
        GF_STR_PrintForceStop(pStart->msgIndex);
    }*/
    if(pStart->fca){
        FComAct_Delete(pStart->fca);
    }
    if(pStart->endfunc != NULL){
        _pUnderItem->deleteIndex = ret;
        _pUnderItem->deleteItem = _underBagGetGoodsID(ret,pStart); //UG_GOODS_NONE;   // 消すアイテム番号
        pStart->endfunc(UG_GOODS_NONE);
        pStart->endfunc = NULL;
    }
    if(pStart->pStrBuf1)
        STRBUF_Delete(pStart->pStrBuf1);
    if(pStart->pStrBuf2)
        STRBUF_Delete(pStart->pStrBuf2);
    if(pStart->pWordSet)
        WORDSET_Delete(pStart->pWordSet);
    if(pStart->pTCB)
        TCB_Delete(pStart->pTCB);

    sys_FreeMemoryEz(pStart);
}


//--------------------------------------------------------------
/**
 * @brief   GOODSメニュー処理
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static BOOL _goodsMenuFuncSub2(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;
    u32	ret;

    ret = Ug_BmpListMain(pStart->pUGlw);
//    ret = BmpListMain(pStart->lw);
    if(CommIsError()){  // エラー時はキャンセル扱いにする
        ret = BMPLIST_CANCEL;
    }
    if(ret == _MENURETURN_EXIT){
        ret = BMPLIST_CANCEL;
    }
    switch(ret){
    case BMPLIST_NULL:
        return FALSE;
    case BMPLIST_CANCEL:
        if(pStart->endfunc != NULL){
            _pUnderItem->deleteIndex = ret;
            _pUnderItem->deleteItem = UG_GOODS_NONE;   // 消すアイテム番号
            pStart->endfunc(_pUnderItem->deleteItem);
            pStart->endfunc = NULL;
        }
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderItem());
        UgGoodsMenuForceDelete(pStart,ret);
        UgMgrEndNowTCB();
        return TRUE;
    default:
        
        if(pStart->endfunc != NULL){
            _pUnderItem->deleteIndex = ret;
            _pUnderItem->deleteItem = _underBagGetGoodsID(ret,pStart);
            pStart->endfunc(_pUnderItem->deleteItem);
            pStart->endfunc = NULL;
        }
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderItem());
        UgGoodsMenuForceDelete(pStart,ret);
        UgMgrEndNowTCB();
        return TRUE;
        break;
    }
    return TRUE;
}

//==============================================================================
/**
 * 地下グッズバッグ初期化
 * @param   none
 * @retval  none
 */
//==============================================================================

void* UgBagGoodsMenuStart(pBagEndFunc func, FIELDSYS_WORK* pFSys)
{
    _START_WORK* pStart;
    BMPLIST_HEADER list_h;

//    UgMgrOpenRecordKey(_KEY_NAME_BAG);
    pStart = sys_AllocMemory(HEAPID_FIELD, sizeof(_START_WORK));
    MI_CpuFill8(pStart, 0, sizeof(_START_WORK));
    pStart->pFSys = pFSys;
    pStart->endfunc = func;
    pStart->seq = 0;
    pStart->clact_max = 0;
    pStart->lw = NULL;
    pStart->pLineCallBack = NULL;
    pStart->pStrBuf1 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    pStart->pStrBuf2 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    pStart->pWordSet = WORDSET_Create( HEAPID_FIELD );
    _goodsMenuStart_Bag(pStart);
    pStart->seq = _START_GOODS_WAIT_SUB2;
    pStart->pTCB = TCB_Add(_bagProcess, pStart, _MENU_UG_PRI);
    UgMgrSetNowTCB(pStart,pStart->pTCB,UgGoodsMenuForceDelete2);
    return pStart;
}

//==============================================================================
/**
 * カーソル位置調整
 * @param   none
 * @retval  none
 */
//==============================================================================

void UgBagCursorLineLimit(_START_WORK* pStart, int line,int count)
{
    if((pStart->line + line) >= count){
        pStart->line = count - line;
        if(pStart->line < 0){
            pStart->line = 0;
        }
    }
    if(pStart->cursor >= (count-1)){
        pStart->cursor = count - 1;
        if(pStart->cursor < 0){
            pStart->cursor = 0;
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   GOODSメニュー強制終了処理
 * @param   pStart		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

void UgGoodsMenuForceDelete2( TCB_PTR pTCB, void* work)
{
    SetBrightness(BRIGHTNESS_NORMAL,PLANEMASK_BG0,MASK_MAIN_DISPLAY);
    UgGoodsMenuForceDelete(work,BMPLIST_CANCEL);
}

