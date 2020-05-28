//=============================================================================
/**
 * @file	ug_shop.c
 * @brief	地下のお店の中身を管理するクラス
 * @author	Katsumi Ohno
 * @date    2006.3.9
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
#include "system/snd_tool.h"
#include "savedata/undergrounddata.h"
#include "../eventdata.h"
#include "../fieldobj.h"

#include "../../fielddata/base_goods/goods_id_def.h"
#include "ug_trapshopdata.h"
#include "ug_trshopdata.h"
#include "../goods_data.h"
#include "../fld_comact.h"
#include "ug_local.h"
#include "ug_shop.h"


/*
	//アイテム、トラップ屋さんの位置を調整
	_SXY_POS_CHANGE		UG_ITEM_SHOP_01,72,104
	_SXY_POS_CHANGE		UG_ITEM_SHOP_02,424,87
	_SXY_POS_CHANGE		UG_ITEM_SHOP_03,200,185
	_SXY_POS_CHANGE		UG_ITEM_SHOP_04,335,264
	_SXY_POS_CHANGE		UG_ITEM_SHOP_05,175,279
	_SXY_POS_CHANGE		UG_ITEM_SHOP_06,424,439
	_SXY_POS_CHANGE		UG_ITEM_SHOP_07,87,456
	_SXY_POS_CHANGE		UG_ITEM_SHOP_08,311,358

	_SXY_POS_CHANGE		UG_TRAP_SHOP_01,232,87
	_SXY_POS_CHANGE		UG_TRAP_SHOP_02,328,151
	_SXY_POS_CHANGE		UG_TRAP_SHOP_03,232,215
	_SXY_POS_CHANGE		UG_TRAP_SHOP_04,232,298
	_SXY_POS_CHANGE		UG_TRAP_SHOP_05,279,328
	_SXY_POS_CHANGE		UG_TRAP_SHOP_06,279,456
	_SXY_POS_CHANGE		UG_TRAP_SHOP_07,183,392
	_SXY_POS_CHANGE		UG_TRAP_SHOP_08,279,245

	_SXY_POS_CHANGE		UG_TREASURE_SHOP_01,40,471
	_SXY_POS_CHANGE		UG_TREASURE_SHOP_02,471,72
	_SXY_POS_CHANGE		UG_TREASURE_SHOP_03,471,471
	_SXY_POS_CHANGE		UG_TREASURE_SHOP_04,40,72
*/

typedef struct {
    u16 type;
    u16 x;
    u16 z;
} _ShopListS;

#define _SHOP_GOODS    (0)
#define _SHOP_TRAP     (1)
#define _SHOP_TREASURE (2)

_ShopListS _shopList[]={

    {_SHOP_GOODS,72,104},
    {_SHOP_GOODS,424,87},
    {_SHOP_GOODS,200,185},
    {_SHOP_GOODS,335,264},
    {	_SHOP_GOODS,175,279},
    {	_SHOP_GOODS,424,439},
    {	_SHOP_GOODS,87,456},
    {	_SHOP_GOODS,311,358},

    {	_SHOP_TRAP,232,87},
    {	_SHOP_TRAP,328,151},
    {	_SHOP_TRAP,232,215},
    {	_SHOP_TRAP,232,298},
    {	_SHOP_TRAP,279,328},
    {	_SHOP_TRAP,279,456},
    {	_SHOP_TRAP,183,392},
    {	_SHOP_TRAP,279,245},

    {	_SHOP_TREASURE,40,471},
    {	_SHOP_TREASURE,471,72},
    {	_SHOP_TREASURE,471,471},
    {	_SHOP_TREASURE,40,72},
};


//==============================================================================
//	定数定義
//==============================================================================

#define _EVWIN_MSG_BUF_SIZE		(50*2)			//メッセージバッファサイズ

#define	_SUB_MENU_MAX		( 7 )					// 項目最大数

#define	_TRAP_BAG_MAX      (20)
#define	_STONE_BAG_MAX     (20)
#define	_GOODS_BAG_MAX     (20)
#define	_TREASURE_BAG_MAX  (20)

#define _TRAP_COMPUTER_MAX      (200)
#define _STONE_COMPUTER_MAX     (200)
#define _GOODS_COMPUTER_MAX     (200)
#define _TREASURE_COMPUTER_MAX  (200)


//==============================================================================
//	構造体定義
//==============================================================================



//==============================================================================
//	型宣言
//==============================================================================


//==============================================================================
//	static定義
//==============================================================================

static const BMPWIN_DAT _yesNoBmpDat = {
    FLD_MBGFRM_FONT, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
    FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, FLD_YESNO_WIN_CGX
    };

static void _shopStoneDispWindow(_START_WORK* pShop);
static void _ugMenuShopEnd(_START_WORK* pShop);




//==============================================================================
/**
 * わなの商品メニューを作成
 * @param   pShop   ワークメニューポインタ
 * @retval  void
 */
//==============================================================================

static void _trapShopListCreate(_START_WORK* pShop,int personal)
{
    MATHRandContext16 rand;
    int type,max,min,j,i;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pShop->pFSys));
    
    MATH_InitRand16(&rand, UnderGroundGetDayRandSeed(pUGData) + personal);

    for(i = 0;i < _SHOP_BUY_LIST_MAX; i++){
        if(i == 0){
            type = UG_TRAPTYPE_DRILL;
        }
        else{
            type = MATH_Rand16(&rand,UG_TRAPTYPE_MAX-1)+1;
        }
        for(j = 0;j < i; j++){
            if(pShop->item[j] == type){
                type = UG_TRAPTYPE_NONE;
            }
        }
        if(type == UG_TRAPTYPE_NONE){
            i--;
            continue;
        }
        min = TrapShopGetChangeStoneCaratMin(type);
        max = TrapShopGetChangeStoneCaratMax(type);
        if((min == 0) && (max == 0)){
            OHNO_PRINT("販売中止\n");
            i--;
            continue;
        }
        pShop->item[i] = type;
        pShop->stone[i] = TrapShopGetChangeStoneType(type);
        if(pShop->stone[i] == STONE_TYPE_MAX){  // ランダムだった
            pShop->stone[i] = MATH_Rand16(&rand,STONE_TYPE_MAX-1)+1;
        }
        pShop->carat[i] = MATH_Rand16(&rand, max-min)+min;
    }

}

//==============================================================================
/**
 * グッズの商品メニューを作成
 * @param   pShop   ワークメニューポインタ
 * @retval  void
 */
//==============================================================================

static void _goodsShopListCreate(_START_WORK* pShop,int personal)
{
    MATHRandContext16 rand;
    int type,max,min,j,i;
    SAVEDATA* pSave = GameSystem_GetSaveData(pShop->pFSys);
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(pSave);
    BOOL bZenkoku = ZukanWork_GetZenkokuZukanFlag(SaveData_GetZukanWork(pSave));
    
    MATH_InitRand16(&rand, UnderGroundGetDayRandSeed(pUGData) + personal);

    for(i = 0;i < _SHOP_BUY_LIST_MAX; i++){
        type = MATH_Rand16(&rand,GOODS_TYPE_MAX-1)+1;
        for(j = 0;j < i; j++){
            if(pShop->item[j] == type){
                type = GOODS_NONE;
            }
        }
        if(type == GOODS_NONE){
            i--;
            continue;
        }
        pShop->item[i] = type;
        pShop->stone[i] = GOODS_GetGoodsChangeStoneType(type);
        if((bZenkoku==FALSE) && (1==GOODS_GetZenkokuMode(type))){  // まだ売ってはいけない
            i--;
            continue;
        }
        if(pShop->stone[i] == STONE_TYPE_NONE){  // お店では売っていないものだった
            i--;
            continue;
        }
        else if(pShop->stone[i] == STONE_TYPE_MAX){  // ランダムだった
            pShop->stone[i] = MATH_Rand16(&rand,STONE_TYPE_MAX-1)+1;
        }
        min = GOODS_GetGoodsChangeStoneCaratMin(type);
        max = GOODS_GetGoodsChangeStoneCaratMax(type);
        pShop->carat[i] = MATH_Rand16(&rand, max-min)+min;
    }
}

//==============================================================================
/**
 * たまと物の交換処理
 * @param   pShop   ワークメニューポインタ
 * @retval  void
 */
//==============================================================================

static int _shopExec(_START_WORK* pShop, int selectIndex,int stoneIndex)
{
    BOOL result = FALSE;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pShop->pFSys));
    
    if(pShop->stone[selectIndex] != _underBagGetStoneID(stoneIndex, pShop)){
        return UG_SHOP_MISS_SELECT;
    }
    if(pShop->carat[selectIndex] > _underBagGetStoneCarat(stoneIndex, pShop)){
        return UG_SHOP_CARAT_SMALL;
    }
    if(pShop->ShopID == UG_SHOP_TRAP){
        result = UnderGroundAddTrapBagItem(pUGData, pShop->item[selectIndex]);
    }
    else if(pShop->ShopID == UG_SHOP_GOODS){
        result = UnderGroundAddGoodsBagItem(pUGData, pShop->item[selectIndex]);
    }
    else if(pShop->ShopID == UG_SHOP_TREASURE){
        result = UnderGroundAddTreasureBagItem(pUGData, pShop->item[selectIndex]);
    }
    if(result){   // たまをとる
        UnderGroundDelStoneBagItem(pUGData ,stoneIndex);
    }
    else{
        return UG_SHOP_BAG_FULL;
    }
    return pShop->item[selectIndex];
}

//==============================================================================
/**
 * わなかグッズかのメニューを出す
 * @param   pTalk   ワークメニューポインタ
 * @retval  ワークポインタ
 */
//==============================================================================

#define _TRAPMENU_POSX    (19)
#define _TRAPMENU_POSY    (3)
#define _TRAPMENU_SIZE_X  (12)

static void* _shopSelectMenuInit( _START_WORK* pShop )
{
    BMPLIST_HEADER list_h;
    int LISTMAX = 3;  // リストの最大

    if(pShop->ShopID == UG_SHOP_TREASURE){
        LISTMAX = 2;
    }
    
    _startMenuEnd(pShop);
    //BMPウィンドウ生成
    pShop->menulist = BMP_MENULIST_Create( LISTMAX, HEAPID_FIELD );
    GF_BGL_BmpWinAdd(pShop->pFSys->bgl, &pShop->win,
                     GF_BGL_FRAME3_M, _TRAPMENU_POSX, _TRAPMENU_POSY, _TRAPMENU_SIZE_X, LISTMAX*2, FLD_SYSFONT_PAL,
                     FLD_MSG_WIN_CGX-(14*LISTMAX*2));
    BmpMenuWinWrite(&pShop->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	{
		int i,msg;

        if(pShop->ShopID == UG_SHOP_TRAP){
            msg = mes_uw_buy_13;
            _trapShopListCreate(pShop,pShop->personal);
            BMP_MENULIST_AddArchiveString( pShop->menulist, CommMsgGetMsgManager(CommUnderGetMsgUnderShop()), msg, 0 );
            BMP_MENULIST_AddArchiveString( pShop->menulist, CommMsgGetMsgManager(CommUnderGetMsgUnderShop()), msg+1, 1 );
            BMP_MENULIST_AddArchiveString( pShop->menulist, CommMsgGetMsgManager(CommUnderGetMsgUnderShop()), msg+2, BMPLIST_CANCEL  );
        }
        else if(pShop->ShopID == UG_SHOP_GOODS){
            msg = mes_uw_buy_16;
            _goodsShopListCreate(pShop,pShop->personal);
            BMP_MENULIST_AddArchiveString( pShop->menulist, CommMsgGetMsgManager(CommUnderGetMsgUnderShop()), msg, 0 );
            BMP_MENULIST_AddArchiveString( pShop->menulist, CommMsgGetMsgManager(CommUnderGetMsgUnderShop()), msg+1, 1 );
            BMP_MENULIST_AddArchiveString( pShop->menulist, CommMsgGetMsgManager(CommUnderGetMsgUnderShop()), msg+2, BMPLIST_CANCEL  );
        }
        else{
            msg = mes_uw_buy_28;
//            _goodsShopListCreate(pShop,pShop->personal);
            BMP_MENULIST_AddArchiveString( pShop->menulist, CommMsgGetMsgManager(CommUnderGetMsgUnderShop()), mes_uw_buy_28, 0 );
            BMP_MENULIST_AddArchiveString( pShop->menulist, CommMsgGetMsgManager(CommUnderGetMsgUnderShop()), mes_uw_buy_22, BMPLIST_CANCEL  );
        }
	}
    MI_CpuCopy8( CommMsgGetNormalBmpListHeader(), &list_h, sizeof(BMPLIST_HEADER));
    list_h.list = pShop->menulist;
    list_h.win = &pShop->win;
    list_h.count = LISTMAX;
    list_h.line = LISTMAX;

    pShop->line = UgMgrGetRecordKeyLine(_KEY_MENU_SHOP_MAIN);
    pShop->cursor = UgMgrGetRecordKeyCursor(_KEY_MENU_SHOP_MAIN);
    UgBagCursorLineLimit(pShop, list_h.line, list_h.count);
    pShop->lw = BmpListSet(&list_h, pShop->line, pShop->cursor, HEAPID_FIELD);
	pShop->pos_bak = pShop->cursor;
    GF_BGL_BmpWinOn(&pShop->win);
    //Snd_SePlay( SEQ_SE_DP_WIN_OPEN );
    return pShop;
}

//==============================================================================
/**
 * カーソルが動いた時にたまのメッセージを変える
 * @param   pTalk   ワークメニューポインタ
 * @retval  none
 */
//==============================================================================

static void _cursorChangeDisp(BMPLIST_WORK * wk,u32 param,u8 mode)
{
    _START_WORK* pShop = (_START_WORK*)BmpListParamGet(wk, BMPLIST_ID_WORK);
    u32 idx = param;

    GF_BGL_BmpWinDataFill( &pShop->winSub, FBMP_COL_WHITE );
    MSGMAN_GetString( CommMsgGetMsgManager(CommUnderGetMsgUnderShop()), mes_uw_buy_23 + pShop->bBuy, pShop->pStrBuf1 );   // ID
    GF_STR_PrintSimple(&pShop->winSub, FONT_SYSTEM,
                       pShop->pStrBuf1, 1, 1, 0, NULL);

    if(param != _MENURETURN_EXIT){ 
        WORDSET_RegisterUGItemName(pShop->pWordSet, 2, pShop->stone[idx] );
        WORDSET_RegisterNumber(pShop->pWordSet, 6,
                               pShop->carat[idx], 2,
                               NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
        MSGMAN_GetString( CommMsgGetMsgManager(CommUnderGetMsgUnderShop()), mes_uw_buy_25, pShop->pStrBuf1 );   // ID
        WORDSET_ExpandStr(pShop->pWordSet, pShop->pStrBuf2, pShop->pStrBuf1 );
        GF_STR_PrintSimple(&pShop->winSub, FONT_SYSTEM, pShop->pStrBuf2, 1, 17, 0, NULL);
    }
    else{
//        STRBUF_Clear(pShop->pStrBuf1);
//        GF_STR_PrintSimple(&pShop->winSub, FONT_SYSTEM, pShop->pStrBuf1, 1, 17, 0, NULL);
    }

    if(idx == _MENURETURN_EXIT){
        idx = BMPLIST_CANCEL;
    }
    
    if(pShop->ShopID == UG_SHOP_TRAP){
        _trapMenuLineSelect(wk,idx,mode);
    }
    else if(pShop->ShopID == UG_SHOP_GOODS){
        _goodsMenuLineSelect(wk,idx,mode);
    }
    else{
        _treasureMenuLineSelect(wk,idx,mode);
    }

	//Snd_SePlay( SEQ_SE_DP_SELECT );
}

//==============================================================================
/**
 * カーソルが動いた時にたまのメッセージを変える
 * @param   pTalk   ワークメニューポインタ
 * @retval  none
 */
//==============================================================================

static void _recycleShopDisp(BMPLIST_WORK * wk,u32 param,u8 mode)
{
    MATHRandContext16 rand;
    _START_WORK* pShop = (_START_WORK*)BmpListParamGet(wk, BMPLIST_ID_WORK);
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pShop->pFSys));
    int idx = param,min,max;
    int type, stone=STONE_TYPE_NONE, carat;
    
    GF_BGL_BmpWinDataFill( &pShop->winSub, FBMP_COL_WHITE );
    if(param != BMPLIST_CANCEL){
//        GF_BGL_BmpWinDataFill( &pShop->winSub, FBMP_COL_WHITE );
        
        if(pShop->ShopID == UG_SHOP_TRAP){
            type = _underBagGetTrapID(idx, pShop);
            MATH_InitRand16(&rand, UnderGroundGetDayRandSeed(pUGData) + pShop->personal + type);
            stone = TrapShopGetChangeStoneType(type);
            if(stone == STONE_TYPE_MAX){  // ランダムだった
                stone= MATH_Rand16(&rand,STONE_TYPE_MAX-1)+1;
            }
            min = TrapShopGetChangeStoneCaratMin(type);
            max = TrapShopGetChangeStoneCaratMax(type);
            carat = MATH_Rand16(&rand, max-min)+min;
            carat = carat / 2;
        }
        else if(pShop->ShopID == UG_SHOP_GOODS){
            type = _underBagGetGoodsID(idx, pShop);
            MATH_InitRand16(&rand, UnderGroundGetDayRandSeed(pUGData) + pShop->personal + type);
            stone = GOODS_GetGoodsChangeStoneType(type);
            if(stone == STONE_TYPE_MAX){  // ランダムだった
                stone= MATH_Rand16(&rand,STONE_TYPE_MAX-1)+1;
            }
            min = GOODS_GetGoodsChangeStoneCaratMin(type);
            max = GOODS_GetGoodsChangeStoneCaratMax(type);
            carat = MATH_Rand16(&rand, max-min)+min;
            carat = carat / 2;
        }
        else{
            type = _underBagGetTreasureID(idx, pShop);
            MATH_InitRand16(&rand, UnderGroundGetDayRandSeed(pUGData) + pShop->personal + type);
            stone = TrShopGetChangeStoneType(type);
            if(stone == STONE_TYPE_MAX){  // ランダムだった
                stone= MATH_Rand16(&rand,STONE_TYPE_MAX-1)+1;
            }
            min = TrShopGetChangeStoneCaratMin(type);
            max = TrShopGetChangeStoneCaratMax(type);
            carat = MATH_Rand16(&rand, max-min)+min;
        }
    }
    MSGMAN_GetString( CommMsgGetMsgManager(CommUnderGetMsgUnderShop()), mes_uw_buy_23 + pShop->bBuy, pShop->pStrBuf1 );   // ID
    GF_STR_PrintSimple(&pShop->winSub, FONT_SYSTEM,
                       pShop->pStrBuf1, 1, 1, 0, NULL);

    if(param == BMPLIST_CANCEL){
    }
    else if(stone != STONE_TYPE_NONE){ 
        WORDSET_RegisterUGItemName(pShop->pWordSet, 2, stone );
        WORDSET_RegisterNumber(pShop->pWordSet, 6,
                               carat, 2,
                               NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
        MSGMAN_GetString( CommMsgGetMsgManager(CommUnderGetMsgUnderShop()), mes_uw_buy_25, pShop->pStrBuf1 );   // ID
        WORDSET_ExpandStr(pShop->pWordSet, pShop->pStrBuf2, pShop->pStrBuf1 );
        GF_STR_PrintSimple(&pShop->winSub, FONT_SYSTEM, pShop->pStrBuf2, 1, 17, 0, NULL);
        pShop->stone[0] = stone;
        pShop->carat[0] = carat;
    }
    else{
        pShop->stone[0] = stone;
        MSGMAN_GetString( CommMsgGetMsgManager(CommUnderGetMsgUnderShop()), mes_uw_buy_26, pShop->pStrBuf1 );
        GF_STR_PrintSimple(&pShop->winSub, FONT_SYSTEM, pShop->pStrBuf1, 1, 17, 0, NULL);
    }

    if(pShop->ShopID == UG_SHOP_TRAP){
        _trapMenuLineSelect(wk,param,mode);
    }
    else if(pShop->ShopID == UG_SHOP_GOODS){
        _goodsMenuLineSelect(wk,param,mode);
    }
    else{
        _treasureMenuLineSelect(wk,param,mode);
    }
}


//==============================================================================
/**
 * お店の商品をindexから中身を渡す
 * @param   pTalk   ワークメニューポインタ
 * @retval  none
 */
//==============================================================================

static int _shopGetType(int index, void* work)
{
    _START_WORK* pShop = work;
    if(index >= _SHOP_BUY_LIST_MAX){
        return 0;
    }
    return pShop->item[index];
}


//==============================================================================
/**
 * お店のメニューを出す
 * @param   pTalk   ワークメニューポインタ
 * @retval  none
 */
//==============================================================================

static void _shopMenuInit(_START_WORK* pShop)
{
    BMPLIST_HEADER list_h;
    const int LISTMAX = _SHOP_BUY_LIST_MAX + 1;  // リストの最大

    _startMenuEnd(pShop);
    //BMPウィンドウ生成
    pShop->menulist = BMP_MENULIST_Create( LISTMAX, HEAPID_FIELD );
    GF_BGL_BmpWinAdd(pShop->pFSys->bgl, &pShop->win,
                     GF_BGL_FRAME3_M, _TRAPMENU_POSX, _TRAPMENU_POSY, _TRAPMENU_SIZE_X, LISTMAX*2, FLD_SYSFONT_PAL,
                     FLD_MSG_WIN_CGX-(14*LISTMAX*2));
    BmpMenuWinWrite(&pShop->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	{
		MSGDATA_MANAGER* msgman;
		int i;

        if(pShop->ShopID == UG_SHOP_TRAP){
            msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_undergroundtrap_dat, HEAPID_FIELD);
            CommMsgChangeMSGMAN(CommUnderGetMsgUnderItem(), NARC_msg_undergroundtrap_dat, MSGMAN_TYPE_NORMAL);
        }
        else if(pShop->ShopID == UG_SHOP_GOODS){
            msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_undergroundgoods_dat, HEAPID_FIELD);
            CommMsgChangeMSGMAN(CommUnderGetMsgUnderItem(), NARC_msg_undergroundgoods_dat, MSGMAN_TYPE_NORMAL);
        }
        else{
            msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_undergrounditem_dat, HEAPID_FIELD);
            CommMsgChangeMSGMAN(CommUnderGetMsgUnderItem(), NARC_msg_undergrounditem_dat, MSGMAN_TYPE_NORMAL);
        }
        for(i = 0 ; i < LISTMAX-1 ; i++) {
            BMP_MENULIST_AddArchiveString( pShop->menulist, msgman, pShop->item[i], i );
        }
        BMP_MENULIST_AddArchiveString( pShop->menulist, msgman, 0, _MENURETURN_EXIT );
		MSGMAN_Delete(msgman);
	}
    MI_CpuCopy8( CommMsgGetNormalBmpListHeader(), &list_h, sizeof(BMPLIST_HEADER));
    list_h.list = pShop->menulist;
    list_h.win = &pShop->win;
    list_h.count = LISTMAX;
    list_h.line = LISTMAX;
    list_h.call_back = _cursorChangeDisp;
    list_h.work = pShop;

    pShop->getTypeFunc = _shopGetType;
    pShop->line = UgMgrGetRecordKeyLine(_KEY_MENU_SHOP_GOODS+pShop->ShopID);
    pShop->cursor = UgMgrGetRecordKeyCursor(_KEY_MENU_SHOP_GOODS+pShop->ShopID);
	pShop->pos_bak = pShop->cursor;
    UgBagCursorLineLimit(pShop, list_h.line, list_h.count);
    pShop->lw = BmpListSet(&list_h, pShop->line, pShop->cursor, HEAPID_FIELD);
    GF_BGL_BmpWinOn(&pShop->win);
    //Snd_SePlay( SEQ_SE_DP_WIN_OPEN );
}

//--------------------------------------------------------------
/**
 * @brief   地下のお店のメニューを終了
 * @param   none
 * @retval  noen
 */
//--------------------------------------------------------------
static void  _shopMenuEnd(_START_WORK* pShop, BOOL bSubWin)
{
    if(GF_BGL_BmpWinAddCheck(&pShop->winSub)){
        BmpMenuWinClear(&pShop->winSub, WINDOW_TRANS_OFF );
        GF_BGL_BmpWinDel(&pShop->winSub);
    }
    _startMenuEnd(pShop);
}

//--------------------------------------------------------------
/**
 * @brief   交換するかの確認メニューを出す
 * @param   index  選択した場所
 * @retval  none
 */
//--------------------------------------------------------------

static void _yesNoWindowOpen(int index, _START_WORK* pShop)
{
    int type;

    if(pShop->ShopID == UG_SHOP_TRAP){
        type = _underBagGetTrapID(index, pShop);
        UgShopTalkRegisterTrapName(2,type);
    }
    else if(pShop->ShopID == UG_SHOP_GOODS){
        type = _underBagGetGoodsID(index, pShop);
        UgShopTalkRegisterGoodsName(2,type);
    }
    else{
        type = _underBagGetTreasureID(index, pShop);
        UgShopTalkRegisterItemName(2,type);
    }
    UgShopTalkRegisterItemName(4,pShop->stone[0]);
    UgShopTalkStart(mes_uw_buy_10);
}

//--------------------------------------------------------------
/**
 * @brief   売る実行処理
 * @param   pShop  このメニューのワークポインタ
 * @retval  結果の番号
 */
//--------------------------------------------------------------

static u32 _sellExec(_START_WORK* pShop)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pShop->pFSys));

    if(CommUnderBagAddStone(pShop->stone[0],pShop->carat[0])){
        if(pShop->ShopID == UG_SHOP_TRAP){
            UnderGroundDelTrapBagItem(pUGData, pShop->work);
        }
        else if(pShop->ShopID == UG_SHOP_GOODS){
            UnderGroundDelGoodsBagItem(pUGData, pShop->work);
        }
        else if(pShop->ShopID == UG_SHOP_TREASURE){
            UnderGroundDelTreasureBagItem(pUGData, pShop->work);
        }
        return pShop->stone[0];
    }
    return UG_SHOP_BAG_FULL;
}

//--------------------------------------------------------------
/**
 * @brief   地下のお店のメニューの状態を得る
 * @param   pWork  このメニューのワークポインタ
 * @retval  結果の番号 UgShopReturnCode_e
 */
//--------------------------------------------------------------
#if 0
#endif

int UgShopMenuFuncAndCheck(void* pWork)
{
    _START_WORK* pShop = pWork;
    u32	ret = UG_SHOP_NONE;
    u32	retcode = UG_SHOP_NONE;
    u16 line,cursor;
    return retcode;
}

//--------------------------------------------------------------
/**
 * @brief   開放処理
 * @param   pShop   ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _ugMenuShopEnd(_START_WORK* pShop)
{
    STRBUF_Delete(pShop->pStrBuf1);
    STRBUF_Delete(pShop->pStrBuf2);
    WORDSET_Delete(pShop->pWordSet);
    sys_FreeMemoryEz(pShop);
}

//--------------------------------------------------------------
/**
 * @brief   お店の商品メニューを開く
 * @param   ShopID   UG_SHOP_TRAP, UG_SHOP_GOODS, UG_SHOP_TREASURE
 * @param   FIELDSYS_WORK   フィールドシステムワークポインタ
 * @param   連番
 * @retval  このメニューのワークポインタ
 */
//--------------------------------------------------------------

void* UgShopMenuInit2(int ShopID, FIELDSYS_WORK* pFSys,int no)
{
    _START_WORK* pShop=NULL;
    /*
    BMPLIST_HEADER list_h;
    const int LISTMAX = 6;  // リストの最大

    UgMgrOpenRecordKey(_KEY_NAME_SHOP_GOODS + ShopID);
    pShop = sys_AllocMemory(HEAPID_FIELD, sizeof(_START_WORK));
    MI_CpuClear8(pShop, sizeof(_START_WORK));
    pShop->pFSys = pFSys;
    pShop->ShopID = ShopID;
    pShop->personal = no;
    pShop->pStrBuf1 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    pShop->pStrBuf2 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    pShop->pWordSet = WORDSET_Create( HEAPID_FIELD );
    _shopSelectMenuInit(pShop);
    pShop->seq = _SHOP_SELECT_FUNC;
       */
    return pShop;
}

//--------------------------------------------------------------
/**
 * @brief   お店の会話開始
 * @param   messageNo   gmmラベル
 * @retval  メッセージインデックス
 */
//--------------------------------------------------------------

int UgShopTalkStart(int messageNo)
{
    CommMsgChangeMSGMAN(CommUnderGetMsgUnderShop(),NARC_msg_uwbuy_dat, MSGMAN_TYPE_DIRECT);
    return CommMsgTalkWindowStart(CommUnderGetMsgUnderShop(),messageNo,FALSE,NULL);

}

//--------------------------------------------------------------
/**
 * @brief   お店の会話終了
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void UgShopTalkEnd(void)
{
    CommMsgTalkWindowEnd(CommUnderGetMsgUnderShop());
}

//--------------------------------------------------------------
/**
 * @brief   アイテムの名前をお店の会話に登録
 * @param   index    何番にregistするのか
 * @param   type     gmm番号
 * @retval  none
 */
//--------------------------------------------------------------

void UgShopTalkRegisterItemName(int index,int type)
{
    CommMsgRegisterUGItemNameIndex(CommUnderGetMsgUnderShop(),index,type);
}

//--------------------------------------------------------------
/**
 * @brief   罠の名前をお店の会話に登録
 * @param   index    何番にregistするのか
 * @param   type     gmm番号
 * @retval  none
 */
//--------------------------------------------------------------

void UgShopTalkRegisterTrapName(int index,int type)
{
    CommMsgRegisterUGTrapNameIndex(CommUnderGetMsgUnderShop(),index,type);
}

//--------------------------------------------------------------
/**
 * @brief   グッズの名前をお店の会話に登録
 * @param   index    何番にregistするのか
 * @param   type     gmm番号
 * @retval  none
 */
//--------------------------------------------------------------

void UgShopTalkRegisterGoodsName(int index,int type)
{
    CommMsgRegisterUGGoodsNameIndex(CommUnderGetMsgUnderShop(),index,type);
}

//==============================================================================
/**
 * もらえるタマ 必要なタマ ウインドウ
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _shopStoneDispWindow(_START_WORK* pShop)
{

    if(!GF_BGL_BmpWinAddCheck(&pShop->winSub)){
        GF_BGL_BmpWinAdd(pShop->pFSys->bgl, &pShop->winSub,
                         GF_BGL_FRAME3_M, 1, 12, 12, 4, FLD_SYSFONT_PAL, 1);
        BmpMenuWinWrite(&pShop->winSub, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
    }
	GF_BGL_BmpWinDataFill( &pShop->winSub, FBMP_COL_WHITE );
    GF_BGL_BmpWinOn(&pShop->winSub);
}

//==============================================================================
/**
 * てもちのたま  ウインドウ
 * @param   none
 * @retval  none
 */
//==============================================================================

void UgShopMiniInfoDispWindow(_START_WORK* pShop, int msg)
{
    //BMPウィンドウ生成
    GF_BGL_BmpWinAdd(pShop->pFSys->bgl, &pShop->winSub2,
                     GF_BGL_FRAME3_M, 1, 1, 7, 4, FLD_SYSFONT_PAL, 51);
    BmpMenuWinWrite(&pShop->winSub2, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );

	GF_BGL_BmpWinDataFill( &pShop->winSub2, FBMP_COL_WHITE );
    GF_BGL_BmpWinOn(&pShop->winSub2);

    MSGMAN_GetString( CommMsgGetMsgManager(CommUnderGetMsgUnderShop()), msg, pShop->pStrBuf1 );   // ID
    GF_STR_PrintSimple(&pShop->winSub2, FONT_SYSTEM, pShop->pStrBuf1, 1, 1, 0, NULL);

}

//==============================================================================
/**
 * てもちのたま  ウインドウ
 * @param   none
 * @retval  none
 */
//==============================================================================

void UgShopMiniInfoDispWindowDel(_START_WORK* pShop)
{
    if(GF_BGL_BmpWinAddCheck(&pShop->winSub2)){
        BmpMenuWinClear(&pShop->winSub2, WINDOW_TRANS_OFF );
        GF_BGL_BmpWinDel(&pShop->winSub2);
    }
}


//==============================================================================
/**
 * 位置からショップのタイプを得る
 * @param   none
 * @retval  none
 */
//==============================================================================

static int UgShopGetType(int x,int z, int* personal)
{
    int i,tblMax = NELEMS(_shopList);

    OHNO_PRINT("店テーブル%d\n",tblMax);
    for(i = 0 ; i < tblMax; i++){
        if((_shopList[i].x == x ) && (_shopList[i].z == z)){
            *personal = i;
            return _shopList[i].type;
        }
    }
    GF_ASSERT(0);  // 位置がおかしい
    return 0;
}




//--------------------------------------------------------------
/**
 * @brief   地下のお店のメニューの状態を得る
 * @param   pWork  このメニューのワークポインタ
 * @retval  結果の番号 UgShopReturnCode_e
 */
//--------------------------------------------------------------

enum{
    _SHOP_TALK_OPEN,
    _SHOP_TALK_WAIT,
    _SHOP_SELECT_OPEN,
    _SHOP_SELECT_FUNC,
    _SHOP_MENU_OPEN,
    _SHOP_MENU_FUNC,
    _STONE_MENU_OPEN,
    _STONE_MENU_FUNC,
    _DESIDE_MSG_WAIT,
    _DESIDE_MSG_WAIT2,
    _SHOP_BAG_FULL,
    
    _BAG_MENU_OPEN,
    _BAG_MENU_FUNC,
    _YESNO_CHECK,
    _YESNO_CHECK_WAIT,
    _SELL_MESSAGE_WAIT,
    _UG_SHOP_CANCEL,
    _UG_SHOP_CANCEL_WAIT,
};

static void _ugShopMenuFuncAndCheck(TCB_PTR tcb, void* pWork)
{
    _START_WORK* pShop = pWork;
    u32	ret = UG_SHOP_NONE;
    u32	retcode = UG_SHOP_NONE;
    u16 line,cursor,tmp_pos_bak;

    switch(pShop->seq){
      case _SHOP_TALK_OPEN:
        if(pShop->ShopID == _SHOP_TREASURE){
            UgShopTalkStart(mes_uw_buy_27);
        }
        else{
            UgShopTalkStart(mes_uw_buy_01);
        }
        pShop->seq = _SHOP_TALK_WAIT;
        break;
      case _SHOP_TALK_WAIT:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderShop()) == 0 ){
            pShop->seq = _SHOP_SELECT_OPEN;
        }
        break;
      case _SHOP_SELECT_OPEN:
        _shopSelectMenuInit(pShop);
        pShop->seq = _SHOP_SELECT_FUNC;
        break;
      case _SHOP_SELECT_FUNC:
        ret = BmpListMain(pShop->lw);
        BmpListPosGet( pShop->lw, &line, &cursor );
        UgMgrSetRecordKey(_KEY_MENU_SHOP_MAIN, cursor, line);

#if 1
		//BMPリストの全体位置を取得
		tmp_pos_bak = pShop->pos_bak;		//退避
		BmpListDirectPosGet( pShop->lw, &pShop->pos_bak );

		//カーソルが動いたかチェック
		if( tmp_pos_bak != pShop->pos_bak ){
			Snd_SePlay( SEQ_SE_DP_SELECT );
		}
#endif

        switch(ret){
          case BMPLIST_CANCEL:
		    Snd_SePlay( SEQ_SE_DP_SELECT );
            _shopMenuEnd(pShop,FALSE);
            pShop->seq = _UG_SHOP_CANCEL;
            break;
          case BMPLIST_NULL:
            break;
          default:
            if(pShop->ShopID == UG_SHOP_TREASURE){
                pShop->bBuy = 1;
                pShop->seq = _BAG_MENU_OPEN;
            }
            else{
                pShop->bBuy = ret;
                if(ret == 0){  // 買う
					Snd_SePlay( SEQ_SE_DP_SELECT );
                    pShop->seq = _SHOP_MENU_OPEN;
                }
                else{  // 売る
					Snd_SePlay( SEQ_SE_DP_SELECT );
                    pShop->seq = _BAG_MENU_OPEN;
                }
            }
            break;
        }
        break;
      case _SHOP_MENU_OPEN:
        _shopStoneDispWindow(pShop);
        _shopMenuInit(pShop);
        pShop->seq = _SHOP_MENU_FUNC;
        break;
      case _SHOP_MENU_FUNC:
        ret = BmpListMain(pShop->lw);
        BmpListPosGet( pShop->lw, &line, &cursor );
        UgMgrSetRecordKey(_KEY_MENU_SHOP_GOODS + pShop->ShopID, cursor, line);

#if 1
		//BMPリストの全体位置を取得
		tmp_pos_bak = pShop->pos_bak;		//退避
		BmpListDirectPosGet( pShop->lw, &pShop->pos_bak );

		//カーソルが動いたかチェック
		if( tmp_pos_bak != pShop->pos_bak ){
			Snd_SePlay( SEQ_SE_DP_SELECT );
		}
#endif

        if(ret == _MENURETURN_EXIT){
            ret = BMPLIST_CANCEL;
        }
        if(ret != BMPLIST_NULL){
            CommMsgTalkWindowEnd(CommUnderGetMsgUnderItem());
        }
        switch(ret){
          case BMPLIST_CANCEL:
		    Snd_SePlay( SEQ_SE_DP_SELECT );
            _shopMenuEnd(pShop,TRUE);
            pShop->seq = _SHOP_SELECT_OPEN;
            break;
          case BMPLIST_NULL:
            break;
          default:
		    Snd_SePlay( SEQ_SE_DP_SELECT );
            pShop->seq = _STONE_MENU_OPEN;
            pShop->work = ret;  // pShop->itemのindexが入っている
            OHNO_PRINT("石メニュー開く\n");
            break;
        }
        break;
      case _STONE_MENU_OPEN:
        _startMenuEnd(pShop);
        pShop->cursor = UgMgrGetRecordKeyCursor(_KEY_MENU_SHOP_STONE);
        pShop->line = UgMgrGetRecordKeyLine(_KEY_MENU_SHOP_STONE);
        _stoneMenuStart_ShopBag(pShop);
        UgShopMiniInfoDispWindow(pShop,mes_uw_buy_19);

        if(pShop->ShopID == UG_SHOP_TRAP){
            UgShopTalkRegisterTrapName(2,pShop->item[pShop->work]);
        }
        else if(pShop->ShopID == UG_SHOP_GOODS){
            UgShopTalkRegisterGoodsName(2,pShop->item[pShop->work]);
        }
        
        UgShopTalkStart(mes_uw_buy_02);
        pShop->seq = _STONE_MENU_FUNC;
        break;
      case _STONE_MENU_FUNC:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderShop()) == 0 ){
            ret = Ug_BmpListMain(pShop->pUGlw);
            BmpListPosGet( pShop->pUGlw->pBmpList, &line, &cursor );
            UgMgrSetRecordKey(_KEY_MENU_SHOP_STONE, cursor, line);
            if(ret != BMPLIST_NULL){
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderItem());
            }
            switch(ret){
              case BMPLIST_NULL:
                break;
              case BMPLIST_CANCEL:
                UgShopMiniInfoDispWindowDel(pShop);
                pShop->seq = _SHOP_MENU_OPEN;
                break;
              default:
                ret = _shopExec(pShop,pShop->work,ret);
                _shopMenuEnd(pShop,TRUE);
                UgShopMiniInfoDispWindowDel(pShop);
                if(ret == UG_SHOP_BAG_FULL){
                    UgShopTalkStart(mes_uw_buy_04);
                    pShop->seq = _DESIDE_MSG_WAIT2;
                }
                else if(ret == UG_SHOP_MISS_SELECT){
                    UgShopTalkStart(mes_uw_buy_05);
                    pShop->seq = _DESIDE_MSG_WAIT2;
                }
                else if(ret == UG_SHOP_CARAT_SMALL){
                    UgShopTalkStart(mes_uw_buy_06);
                    pShop->seq = _DESIDE_MSG_WAIT2;
                }
                else{
                    pShop->work = ret;
                    UgShopTalkStart(mes_uw_buy_03);
                    pShop->seq = _DESIDE_MSG_WAIT;
                }
                break;
            }
        }
        break;
      case _SHOP_BAG_FULL:
        UgShopTalkStart(mes_uw_buy_04);
        pShop->seq = _DESIDE_MSG_WAIT2;
        break;
      case _DESIDE_MSG_WAIT:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderShop()) == 0 ){
            if(sys.trg & PAD_BUTTON_DECIDE){
                if(pShop->ShopID == UG_SHOP_TRAP){
                    UgShopTalkRegisterTrapName(2,pShop->work);
                }
                else if(pShop->ShopID == UG_SHOP_GOODS){
                    UgShopTalkRegisterGoodsName(2,pShop->work);
                }
                UgShopTalkStart(mes_uw_buy_07_1);
                // 交換完了
                Snd_SePlay(UG_SE_FANFA);
                //_ugMenuShopEnd(pShop);
                pShop->seq = _DESIDE_MSG_WAIT2;
//                retcode = pShop->work;
            }
        }
        break;
      case _DESIDE_MSG_WAIT2:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderShop()) == 0 ){
            if(sys.trg & PAD_BUTTON_DECIDE){
                UgShopTalkStart(mes_uw_buy_08);
                pShop->seq = _SHOP_SELECT_OPEN;
            }
        }
        break;
      case _BAG_MENU_OPEN:
        _shopStoneDispWindow(pShop);
        pShop->cursor = UgMgrGetRecordKeyCursor(_KEY_MENU_BUY_GOODS + pShop->ShopID);
        pShop->line = UgMgrGetRecordKeyLine(_KEY_MENU_BUY_GOODS + pShop->ShopID);
        pShop->pLineCallBack = _recycleShopDisp;
        if(pShop->ShopID == UG_SHOP_TRAP){
            _trapMenuStart_Shop(pShop);
            UgShopMiniInfoDispWindow(pShop,mes_uw_buy_20);
        }
        else if(pShop->ShopID == UG_SHOP_GOODS){
            _goodsMenuStart_Shop(pShop);
            UgShopMiniInfoDispWindow(pShop,mes_uw_buy_21);
        }
        else{
            _treasureMenuStart_Shop(pShop);
            UgShopMiniInfoDispWindow(pShop,mes_uw_buy_29);
        }
        pShop->seq = _BAG_MENU_FUNC;
        break;
      case _BAG_MENU_FUNC:
        ret = Ug_BmpListMain(pShop->pUGlw);
        BmpListPosGet( pShop->pUGlw->pBmpList, &line, &cursor );
        UgMgrSetRecordKey(_KEY_MENU_BUY_GOODS + pShop->ShopID, cursor, line);
        switch(ret){
          case BMPLIST_CANCEL:
            CommMsgTalkWindowEnd(CommUnderGetMsgUnderItem());
            _shopMenuEnd(pShop,TRUE);
            UgShopMiniInfoDispWindowDel(pShop);
            pShop->seq = _SHOP_SELECT_OPEN;
            break;
          case BMPLIST_NULL:
            break;
          default:
            if(pShop->stone[0] != STONE_TYPE_NONE){
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderItem());
                pShop->work = ret;  // pShop->itemのindexが入っている
                _shopMenuEnd(pShop,TRUE);
                UgShopMiniInfoDispWindowDel(pShop);
                _yesNoWindowOpen(ret, pShop);
                pShop->seq = _YESNO_CHECK;
            }
            break;
        }
        break;
      case _YESNO_CHECK:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderShop()) == 0 ){
            pShop->pYesNoWork =
                BmpYesNoSelectInit( pShop->pFSys->bgl,
                                    &_yesNoBmpDat,
                                    MENU_WIN_CGX_NUM, MENU_WIN_PAL, HEAPID_FIELD );
            pShop->seq = _YESNO_CHECK_WAIT;
        }
        break;
      case _YESNO_CHECK_WAIT:
        ret = BmpYesNoSelectMain(pShop->pYesNoWork, HEAPID_FIELD);
        if(ret == BMPMENU_NULL){  // まだ選択中
            return;
        }else if(ret == 0){ // はいを選択した場合
            ret = _sellExec(pShop);
            if(ret == UG_SHOP_BAG_FULL){
                UgShopTalkStart(mes_uw_buy_04);
                pShop->seq = _DESIDE_MSG_WAIT2;
            }
            else{
                UgShopTalkStart(mes_uw_buy_11);
                pShop->seq = _SELL_MESSAGE_WAIT;
            }
        }
        else{  // いいえを選択した場合
            pShop->seq = _UG_SHOP_CANCEL;
        }
        pShop->pYesNoWork = NULL;
        break;
      case _SELL_MESSAGE_WAIT:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderShop()) == 0 ){
            if(sys.trg & PAD_BUTTON_DECIDE){
                CommMsgRegisterNumber2(CommUnderGetMsgUnderShop(),pShop->carat[0]);
                UgShopTalkRegisterItemName(2,pShop->stone[0]);
                UgShopTalkStart(mes_uw_buy_07_2);
                // 交換完了
                Snd_SePlay(UG_SE_FANFA);

                pShop->seq = _DESIDE_MSG_WAIT2;
            }
        }
        break;
      case _UG_SHOP_CANCEL:
        UgShopTalkStart(mes_uw_buy_09);
        pShop->seq = _UG_SHOP_CANCEL_WAIT;
        break;
      case _UG_SHOP_CANCEL_WAIT:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderShop()) == 0 ){
            if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
                UgShopTalkEnd();
                _ugMenuShopEnd(pShop);
                UgMgrEndNowTCB();
                TCB_Delete(tcb);
                CommPlayerHoldEnd();
            }
        }
        break;
      default:
        OHNO_PRINT("ジャンプ番号 %d \n",pShop->seq);
        break;
    }
    //return retcode;
}



//==============================================================================
/**
 * 地下ショップ店員タスク
 * @param   none
 * @retval  none
 */
//==============================================================================

void UgShopManInit(FIELDSYS_WORK* pFSys)
{
    BMPLIST_HEADER list_h;
    int x = CommPlayerGetPosXDirAdd(CommGetCurrentID());
    int z = CommPlayerGetPosZDirAdd(CommGetCurrentID());
    int dir = CommPlayerGetReverseDir(CommPlayerGetDir(CommGetCurrentID()));
    _START_WORK* pShop;
    const int LISTMAX = 6;  // リストの最大
    int no;
    int ShopID = UgShopGetType(x,z,&no);
    
    UgMgrOpenRecordKey(_KEY_NAME_SHOP_GOODS + ShopID);
    pShop = sys_AllocMemory(HEAPID_FIELD, sizeof(_START_WORK));
    MI_CpuClear8(pShop, sizeof(_START_WORK));
    pShop->pFSys = pFSys;
    pShop->ShopID = ShopID;
    pShop->personal = no;
    pShop->pStrBuf1 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    pShop->pStrBuf2 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    pShop->pWordSet = WORDSET_Create( HEAPID_FIELD );
    pShop->seq = _SHOP_TALK_OPEN;

	Snd_SePlay( SEQ_SE_DP_SELECT );
    pShop->pTCB = TCB_Add(_ugShopMenuFuncAndCheck,pShop,_MENU_UG_PRI);
    UgMgrSetNowTCB(pShop, pShop->pTCB, UgGoodsMenuForceDelete2);

    {
        int num,i;
        const FIELD_OBJ_H* pFObj;
        FIELD_OBJ_PTR fldobj;		//対象のフィールドOBJのポインタ
        num = EventData_GetNpcCount(pShop->pFSys);
        pFObj = EventData_GetNpcData(pShop->pFSys);
        for(i = 0; i < num; i++){
            if((pFObj[i].gx == x) && (pFObj[i].gz == z)){
                fldobj = FieldOBJSys_OBJIDSearch(pShop->pFSys->fldobjsys,i);
                
                FieldOBJ_DirDispCheckSet(fldobj, dir);
            }
        }
    }
}

