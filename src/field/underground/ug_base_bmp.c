//============================================================================================
/**
 * @file	ug_base_bmp.c
 * @brief	秘密基地BMP処置
 * @author	saito
 * @date	2006.02.28
 *
 */
//============================================================================================
#include "ug_base_bmp.h"
#include "../fieldsys.h"
#include "../fld_bmp.h"
#include "fielddata/base_goods/goods_id_def.h"
#include "system/bmp_list.h"
#include "system/fontproc.h"
#include "system/window.h"

#include "include/msgdata/msg.naix"
#include "msgdata/msg_undergroundgoods.h"
#include "savedata/undergrounddata.h"

#include "msgdata/msg_uwedit.h"

#include "communication/comm_message.h"	//for window
#include "ug_manager.h"		//for window

#include "../fld_comact.h"

#include "ug_list.h"
#include "ug_base_se_def.h"

#define MENU_MAX	(4)
#define GOODS_MENU_MAX	(7)

#define BASE_MENU_POSX    (19)
#define BASE_MENU_POSY    (3)
#define BASE_MENU_SIZE_X  (12)

#define BASE_MAIN_MENU_MAX	(3)

#define MENURETURN_EXIT		(BASE_MAIN_MENU_MAX)

#define BASE_GOODS_LIST_SIZE_X	(12)

#define BASE_SUB_WIN_POSX    (1)
#define BASE_SUB_WIN_POSY    (1)
#define BASE_SUB_WIN_SIZE_X  (7)
#define BASE_SUB_WIN_SIZE_Y  (1*2)

#define BASE_GOODS_INFO_SIZE_X	(8)
#define BASE_GOODS_INFO_SIZE_Y	(2*2)

#define GOODS_NUM_LEN	(6)

#define POS_SHIFT	(1)

typedef enum {
	MENU_SEQ_INIT,
	MENU_SEQ_LOOP,
	MENU_SEQ_END,
}BASE_MAIN_MENU_SEQ;

typedef enum {
	LIST_SEQ_INIT,
	LIST_SEQ_LOOP,
	LIST_SEQ_END,
}BASE_GOODS_LIST_SEQ;

///汎用選択メニューのリスト
static const BMPLIST_HEADER MenuListHeader = {
    NULL,			// 表示文字データポインタ
    NULL,					// カーソル移動ごとのコールバック関数
    NULL,					// 一列表示ごとのコールバック関数
    NULL,					// 
    MENU_MAX,	// リスト項目数
    MENU_MAX,	// 表示最大項目数
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

typedef struct UG_BASE_MENU_tag
{
	FIELDSYS_WORK* fsys;
    GF_BGL_BMPWIN  Win;		// BMPウィンドウワーク
	GF_BGL_BMPWIN  SubWin;		// BMPサブウィンドウワーク
	BMPLIST_DATA*  MenuList;
	
    BMPLIST_WORK*  ListWork;		// BMPメニューワーク
	STRBUF* StrBuf;
	u16 *StartLine;
	u16 *CurPos;
	u8 Seq;
	u32 ReturnIdx;				//メインイベントに返すメニューインデックス
	u16 pos_bak;
};

typedef struct UG_BASE_LIST_tag
{
	FIELDSYS_WORK* fsys;
	FLD_COMACT_WORK* Cursor;	//上下カーソル
    GF_BGL_BMPWIN  Win;		// BMPウィンドウワーク
	GF_BGL_BMPWIN  SubWin;		// BMPサブウィンドウワーク
	BMPLIST_DATA*  List;
    UG_BMPLIST_WORK* pUgListWork;
    BMPLIST_WORK*  ListWork;		// BMPメニューワーク
	STRBUF* StrBuf;
	u16 *StartLine;
	u16 *CurPos;
	u8 GoodsCount;				//置いているグッズ数
	u8 GoodsLimit;				//置けるグッズ数
	u8 Seq;
	u32 ReturnIndex;				//リストインデックス
	int Count;
	
};

static void CreateBaseMainMenu(UG_BASE_MENU *outMenu);
static void BaseMenuMain(UG_BASE_MENU *outMenu);
static void CloseMenu(UG_BASE_MENU *outMenu);

static void CreateBaseGoodsList(UG_BASE_LIST *outList);
static void BaseGoodsListMain(UG_BASE_LIST *outList);
static void CloseList(UG_BASE_LIST *outList);
static void CheckCursorDisp(FLD_COMACT_WORK* pCursor,
							const u16 inLine,
							const u16 inTotal,
							const u16 inMaxLine);

static void UgBaseListMoveSe( UG_BASE_MENU* outMenu );

//---------------------------------------------------------------------------
/**
 * @brief	秘密基地メニューメモリアロケーション
 * 
 * @return	menu	秘密基地メニュー
 */
//---------------------------------------------------------------------------
UG_BASE_MENU * BMENU_AllocUgBaseMenu(void)
{
	UG_BASE_MENU *menu;

	menu = sys_AllocMemory(HEAPID_FIELD, sizeof(UG_BASE_MENU));

	return menu;
}

//---------------------------------------------------------------------------
/**
 * @brief	秘密基地メニュー初期化
 *
 * @param	menu		メニュー
 * @param	fsys		フィールドシステムポインタ
 * @param	pCurPos		カーソル位置
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void BMENU_InitBaseMainMenu(UG_BASE_MENU *menu, FIELDSYS_WORK * fsys,
							u16 *pStartLine, u16 *pCurPos)
{
	menu->fsys = fsys;
	menu->Seq = MENU_SEQ_INIT;
	menu->StartLine = pStartLine;
	menu->CurPos = pCurPos;
	menu->pos_bak = 0;
	MenuWinGraphicSet(
        fsys->bgl, /*FLD_MBGFRM_FONT*/GF_BGL_FRAME3_M, MENU_WIN_CGX_NUM,
        MENU_WIN_PAL, MENU_TYPE_UG, HEAPID_FIELD );
}

//---------------------------------------------------------------------------
/**
 * @brief	メニュー解放
 * 
 * @param	menu		秘密基地メニュー
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void BMENU_FreeUgBaseMenu(UG_BASE_MENU *menu)
{
	sys_FreeMemoryEz(menu);
}

//---------------------------------------------------------------------------
/**
 * @brief	メニューインデックスを返す
 * 
 * @param	menu		秘密基地メニュー
 * 
 * @return	u32			インデックス
 */
//---------------------------------------------------------------------------
const u32 BMENU_GetReturnIndex(UG_BASE_MENU *menu)
{
	return menu->ReturnIdx;
}

//---------------------------------------------------------------------------
/**
 * @brief	メインメニューイベント
 * 
 * @param	outMenu		秘密基地メニュー
 * 
 * @return	BOOL		TRUE:終了	FALSE:継続
 */
//---------------------------------------------------------------------------
BOOL BMENU_EditMainMenuControl(UG_BASE_MENU *outMenu)
{
	switch(outMenu->Seq){
	case MENU_SEQ_INIT:	//メニュー作成
		CreateBaseMainMenu(outMenu);
		break;
	case MENU_SEQ_LOOP:	//メニュー制御
		BaseMenuMain(outMenu);
		break;
	case MENU_SEQ_END:	//終了
		outMenu->Seq = MENU_SEQ_INIT;	//次回のためにシーケンスを初期化しておく
		CloseMenu(outMenu);
		return TRUE;
	}

	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	メニュー1ラインコールバック
 * 
 * @param	wk			リストワーク
 * @param	param		パラメータ
 * @param	mode		未使用
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void BaseMenuLineSelect(BMPLIST_WORK * wk,u32 param,u8 mode)
{
	const int mes_list[4] = {
		mes_uw_edit_06,
		mes_uw_edit_07,
		mes_uw_edit_08,
		mes_uw_edit_09,
	};
	
	CommMsgTalkWindowAllWrite(CommUnderGetMsgUnderEdit(),mes_list[param],FALSE,NULL);
}

//---------------------------------------------------------------------------
/**
 * @brief	メニュー作成
 * 
 * @param	outMenu		秘密基地メニュー
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void CreateBaseMainMenu(UG_BASE_MENU *outMenu)
{
	BMPLIST_HEADER list_h;
	int menu_size, subwin_size;
    int count = BASE_MAIN_MENU_MAX;
    int line = MENU_MAX;

    //BMPウィンドウ生成
    outMenu->MenuList = BMP_MENULIST_Create( count+1, HEAPID_FIELD );


	menu_size = BASE_MENU_SIZE_X * line * 2;
	subwin_size = BASE_SUB_WIN_SIZE_X * BASE_SUB_WIN_SIZE_Y;
    GF_BGL_BmpWinAdd(outMenu->fsys->bgl, &outMenu->Win,
                     GF_BGL_FRAME3_M, BASE_MENU_POSX, BASE_MENU_POSY,
                     BASE_MENU_SIZE_X, line * 2, FLD_SYSFONT_PAL,
                     FLD_MSG_WIN_CGX-(menu_size));
	GF_BGL_BmpWinAdd(outMenu->fsys->bgl, &outMenu->SubWin,
                     GF_BGL_FRAME3_M, BASE_SUB_WIN_POSX, BASE_SUB_WIN_POSY,
                     BASE_SUB_WIN_SIZE_X, BASE_SUB_WIN_SIZE_Y, FLD_SYSFONT_PAL,
                     FLD_MSG_WIN_CGX-(menu_size+subwin_size));

    BmpMenuWinWrite(&outMenu->Win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	BmpMenuWinWrite(&outMenu->SubWin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );

	{
		MSGDATA_MANAGER* msgman;
		int i;
		const int msg_list[BASE_MAIN_MENU_MAX+1] = {
			mes_uw_edit_02,	//グッズをおく
			mes_uw_edit_03,	//グッズをもどす
			mes_uw_edit_04,	//グッズのいどう
			mes_uw_edit_05,	//やめる
		};
		
		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_uwedit_dat, HEAPID_FIELD);
		//左上サブウィンドウ
		{
			STRBUF * strb;
			GF_BGL_BmpWinDataFill(&outMenu->SubWin, FBMP_COL_WHITE);
			strb = MSGMAN_AllocString( msgman, mes_uw_edit_01 );
			GF_STR_PrintSimple( &outMenu->SubWin, FONT_SYSTEM, strb, 0, 0, MSG_NO_PUT, NULL );
			STRBUF_Delete( strb );
		}
		//メニュー
		for(i = 0; i < count+1; i++){
			BMP_MENULIST_AddArchiveString( outMenu->MenuList, msgman, msg_list[i], i );
		}
		MSGMAN_Delete(msgman);
	}

	list_h = MenuListHeader;
    list_h.count = count + 1;
    list_h.line = line;
    list_h.list = outMenu->MenuList;
    list_h.win = &outMenu->Win;
	list_h.call_back = BaseMenuLineSelect;
    outMenu->ListWork = BmpListSet(	&list_h,
									*(outMenu->StartLine), *(outMenu->CurPos),
									HEAPID_FIELD);

	GF_BGL_BmpWinOn(&outMenu->Win);
	GF_BGL_BmpWinOn(&outMenu->SubWin);
    outMenu->Seq = MENU_SEQ_LOOP;
}

//---------------------------------------------------------------------------
/**
 * @brief	メニューメイン
 * 
 * @param	outMenu		秘密基地メニュー
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void BaseMenuMain(UG_BASE_MENU *outMenu)
{
    u32	ret;

    ret = BmpListMain(outMenu->ListWork);

	UgBaseListMoveSe( outMenu );

    if(ret == MENURETURN_EXIT){
        ret = BMPLIST_CANCEL;
    }

    switch(ret){
    case BMPLIST_NULL:
        return ;
    case BMPLIST_CANCEL:
		Snd_SePlay( SEQ_SE_DP_SELECT );
		outMenu->ReturnIdx = ret;
        outMenu->Seq = MENU_SEQ_END;
		Snd_SePlay( UG_BASE_SE_SELECT );
        break;
    default:	//リターンコードのセット
        {
			//メインイベントに返すリターンコードをセット
			Snd_SePlay( SEQ_SE_DP_SELECT );
			outMenu->ReturnIdx = ret;
            outMenu->Seq = MENU_SEQ_END;
			Snd_SePlay( UG_BASE_SE_SELECT );
        }
        break;
    }
    return ;
}

//---------------------------------------------------------------------------
/**
 * @brief	メニュークローズ
 * 
 * @param	outMenu		
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void CloseMenu(UG_BASE_MENU *outMenu)
{
	CommMsgTalkWindowEnd(CommUnderGetMsgUnderEdit());
	BmpMenuWinClear( &outMenu->SubWin, WINDOW_TRANS_OFF );
	
    BmpListExit(outMenu->ListWork, outMenu->StartLine, outMenu->CurPos);
    
    BmpMenuWinClear(&outMenu->Win, WINDOW_TRANS_OFF );
    GF_BGL_LoadScreenV_Req( outMenu->Win.ini, outMenu->Win.frmnum );
    GF_BGL_BmpWinDel(&outMenu->Win);
	GF_BGL_BmpWinDel(&outMenu->SubWin);
    BMP_MENULIST_Delete(outMenu->MenuList);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------
/**
 * @brief	一行ごとの描画コールバック(メニュー作成時)
 * 
 * @param	wk			リストワーク
 * @param	param		パラメータ
 * @param	y			ｙ 未使用
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void	LineCallBack(BMPLIST_WORK * wk, u32 param, u8 y)
{
	//すでに基地においているかをチェック
	u8 flg;
	flg = param & 0x01;
	if (flg){//配置されていない
		BmpListTmpColorChange( wk, FBMP_COL_BLACK, FBMP_COL_WHITE , FBMP_COL_BLK_SDW );
	}else{		//配置済み
		BmpListTmpColorChange( wk, FBMP_COL_BLK_SDW, FBMP_COL_WHITE , FBMP_COL_BLK_SDW );
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	グッズリストメモリアロケーション
 * 
 * @return	list		リスト
 */
//---------------------------------------------------------------------------
UG_BASE_LIST * BMENU_AllocUgBaseGoodsList(void)
{
	UG_BASE_LIST *list;

	list = sys_AllocMemory(HEAPID_FIELD, sizeof(UG_BASE_LIST));
	return list;
}

//---------------------------------------------------------------------------
/**
 * @brief	グッズリスト初期化
 *
 * @param	list		リスト
 * @param	fsys		フィールドシステムポインタ
 * @param	pCurPos		カーソル位置
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void BMENU_InitBaseGoodsList(	UG_BASE_LIST *list, FIELDSYS_WORK * fsys,
								u16 *pStartLine, u16 *pCurPos)
{
	list->fsys = fsys;
	list->Seq = LIST_SEQ_INIT;
	list->Cursor = NULL;
	list->StartLine = pStartLine;
	list->CurPos = pCurPos;
	
	MenuWinGraphicSet(
        fsys->bgl, GF_BGL_FRAME3_M, MENU_WIN_CGX_NUM,
        MENU_WIN_PAL, MENU_TYPE_UG, HEAPID_FIELD );
}

//---------------------------------------------------------------------------
/**
 * @brief	グッズ数セット
 * 
 * @param	list		リスト
 * @param	inNum		グッズ数
 * @param	inLimit		リミット
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void BMENU_SetGoodsNumToList(UG_BASE_LIST *list, const u8 inNum, const u8 inLimit)
{
	list->GoodsCount = inNum;
	list->GoodsLimit = inLimit;
}

//---------------------------------------------------------------------------
/**
 * @brief	グッズリスト解放
 * 
 * @param	list		リスト
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void BMENU_FreeUgBaseGoodsList(UG_BASE_LIST *list)
{
	sys_FreeMemoryEz(list);
}

//---------------------------------------------------------------------------
/**
 * @brief	グッズリストインデックスを返す
 * 
 * @param	list		リスト
 * 
 * @return	u32			リストインデックス
 */
//---------------------------------------------------------------------------
const u32 BMENU_GetReturnListIdx(UG_BASE_LIST *list)
{
	return list->ReturnIndex;
}

//---------------------------------------------------------------------------
/**
 * @brief	グッズリストコントロール
 * 
 * @param	outList		リスト
 * 
 * @return	BOOL		TRUE:終了	FALSE:継続
 */
//---------------------------------------------------------------------------
BOOL BMENU_EditGoodsListControl(UG_BASE_LIST *outList)
{
	switch(outList->Seq){
	case LIST_SEQ_INIT:	//メニュー作成
		CreateBaseGoodsList(outList);
		break;
	case LIST_SEQ_LOOP:	//メニュー制御
		BaseGoodsListMain(outList);
		break;
	case LIST_SEQ_END:	//終了
		outList->Seq = LIST_SEQ_INIT;	//次回のためにシーケンスを初期化しておく
		CloseList(outList);
		return TRUE;
	}

	//上下カーソル描画
	if(outList->Cursor){
        FActCom_Main(outList->Cursor);
    }

	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	グッズリストメイン
 * 
 * @param	outList		リスト
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void BaseGoodsListMain(UG_BASE_LIST *outList)
{
    u32	ret;
	u32 pos;
	u16 line,cur;

    ret = Ug_BmpListMain(outList->pUgListWork);
//    ret = BmpListMain(outList->ListWork);

	pos = (ret>>POS_SHIFT);
	
	if (outList->Count == pos){
		pos = BMPLIST_CANCEL;
	}

	{
		BmpListPosGet( outList->pUgListWork->pBmpList, &line, &cur );
		CheckCursorDisp(outList->Cursor,
						line,
						BmpListParamGet(outList->pUgListWork->pBmpList,BMPLIST_ID_COUNT),
						BmpListParamGet(outList->pUgListWork->pBmpList,BMPLIST_ID_LINE));
	}
	
    switch(ret){
    case BMPLIST_NULL:
        return ;
    case BMPLIST_CANCEL:
		outList->ReturnIndex = LIST_CANCEL_CODE;	//グッズ非選択
        outList->Seq = LIST_SEQ_END;
		Snd_SePlay( UG_BASE_SE_SELECT );
        break;
    default:	//リターンコードのセット
        {
			outList->ReturnIndex = pos;
			outList->Seq = LIST_SEQ_END;
			Snd_SePlay( UG_BASE_SE_SELECT );
        }
        break;
    }
    return ;
}

//---------------------------------------------------------------------------
/**
 * @brief	リスト1ラインコールバック
 * 
 * @param	wk			リストワーク
 * @param	param		パラメータ
 * @param	mode		未使用	
 * 
 * @return	none
 */
//---------------------------------------------------------------------------

static void BaseGoodMenuLineSelect(BMPLIST_WORK * wk,u32 param,u8 mode)
{
	int idx;
	UNDERGROUNDDATA* pUGData;
	u32 lst_idx;
	u32 count;
	pUGData = (UNDERGROUNDDATA*)BmpListParamGet(wk, BMPLIST_ID_WORK);
	count = BmpListParamGet(wk, BMPLIST_ID_COUNT);
	
	lst_idx = (param>>POS_SHIFT);
	if (lst_idx == count-1){
		idx = UGGoods_edit02;
	}else{
		idx = UnderGroundGetGoodsPCItem(pUGData,lst_idx);
		idx = UGGoods_e007+idx-GOODS_CHAIR_PC01;
	}
	CommMsgTalkWindowAllWrite(CommUnderGetMsgUnderItem(), idx, FALSE, NULL);
}

//---------------------------------------------------------------------------
/**
 * @brief	グッズリスト作成
 * 
 * @param	outList		リスト
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void CreateBaseGoodsList(UG_BASE_LIST *outList)
{
	UNDERGROUNDDATA* pUGData;
	BMPLIST_HEADER list_h;
    int list_size, subwin_size;
	int count;
    int line;

	//グッズの数を取得
	pUGData = SaveData_GetUnderGroundData(outList->fsys->savedata);
	count = UnderGroundGetNumGoodsPCItem(pUGData);
	outList->Count = count;
	line = count+1;
	if (line>GOODS_MENU_MAX){
		line = GOODS_MENU_MAX;
	}
    //BMPウィンドウ生成
    outList->List = BMP_MENULIST_Create( count+1, HEAPID_FIELD );

	list_size = BASE_MENU_SIZE_X * GOODS_MENU_MAX * 2;
	subwin_size = BASE_GOODS_INFO_SIZE_X * BASE_GOODS_INFO_SIZE_Y;
    GF_BGL_BmpWinAdd(outList->fsys->bgl, &outList->Win,
                     GF_BGL_FRAME3_M, BASE_MENU_POSX, BASE_MENU_POSY,
                     BASE_GOODS_LIST_SIZE_X, line * 2, FLD_SYSFONT_PAL,
                     FLD_MSG_WIN_CGX-(list_size));
	GF_BGL_BmpWinAdd(outList->fsys->bgl, &outList->SubWin,
                     GF_BGL_FRAME3_M, BASE_SUB_WIN_POSX, BASE_SUB_WIN_POSY,
                     BASE_GOODS_INFO_SIZE_X, BASE_GOODS_INFO_SIZE_Y, FLD_SYSFONT_PAL,
                     FLD_MSG_WIN_CGX-(list_size+subwin_size));
    BmpMenuWinWrite(&outList->Win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	BmpMenuWinWrite(&outList->SubWin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	{
        MSGDATA_MANAGER* msgman;
		
        int i=0;
		int idx;
		BOOL check;
		int param;
		u8 flg;
        msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_undergroundgoods_dat, HEAPID_FIELD);
		
		//左上サブウィンドウ
		{
			MSGDATA_MANAGER* edit_msgman;
			STRBUF * strb_put_goods;
			STRBUF * strb_goods_num;
			STRBUF * strb_dst;
			WORDSET *wordset;

			edit_msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_uwedit_dat, HEAPID_FIELD);

			GF_BGL_BmpWinDataFill(&outList->SubWin, FBMP_COL_WHITE);
			strb_put_goods = MSGMAN_AllocString( edit_msgman, mes_uw_edit_10 );
			strb_goods_num = MSGMAN_AllocString( edit_msgman, mes_uw_edit_11 );
			strb_dst = STRBUF_Create( GOODS_NUM_LEN, HEAPID_FIELD );
			
			GF_STR_PrintSimple( &outList->SubWin, FONT_SYSTEM, strb_put_goods, 0, 0, MSG_NO_PUT, NULL );
			
			wordset = WORDSET_Create( HEAPID_FIELD );
			WORDSET_RegisterNumber(wordset, 0, outList->GoodsCount, 2,
					NUMBER_DISPTYPE_SPACE , NUMBER_CODETYPE_DEFAULT );	//置いてあるグッズ数
			WORDSET_RegisterNumber(wordset, 1, outList->GoodsLimit, 2,
					NUMBER_DISPTYPE_SPACE , NUMBER_CODETYPE_DEFAULT );	//置けるグッズ数
			
			WORDSET_ExpandStr( wordset, strb_dst, strb_goods_num );
			
			GF_STR_PrintSimple( &outList->SubWin, FONT_SYSTEM, strb_dst, 0, 16, MSG_NO_PUT, NULL );

			WORDSET_Delete( wordset );	
			STRBUF_Delete( strb_put_goods );
			STRBUF_Delete( strb_goods_num );
			STRBUF_Delete( strb_dst );

			MSGMAN_Delete(edit_msgman);
		}
		
        for(i=0; i < count ; i++)
        {
			idx = UnderGroundGetGoodsPCItem(pUGData,i);
			//すでに基地においているかをチェック
			check = UnderGroundIsEntryGoodsPCItem(pUGData, i);
			if (!check){//配置されていない
				flg = 1;
			}else{		//配置済み
				flg = 0;
			}
			param = (i<<POS_SHIFT)+flg;
            BMP_MENULIST_AddArchiveString( outList->List, msgman, idx, param);
        }
		param = (i<<POS_SHIFT)+1;
        BMP_MENULIST_AddArchiveString( outList->List, msgman, UGGoods_edit01, param);
        MSGMAN_Delete(msgman);
    }

	CommMsgChangeMSGMAN(CommUnderGetMsgUnderItem(), NARC_msg_undergroundgoods_dat, MSGMAN_TYPE_NORMAL);
    
	list_h = MenuListHeader;
	list_h.icon = LineCallBack;
    list_h.count = count + 1;
    list_h.line = line;
    list_h.list = outList->List;
    list_h.win = &outList->Win;
	list_h.call_back = BaseGoodMenuLineSelect;
	list_h.work = pUGData;
//    outList->ListWork = BmpListSet(	&list_h,
//									*(outList->StartLine), *(outList->CurPos),
//									HEAPID_FIELD);
    outList->pUgListWork = Ug_BmpListSet(&list_h, *(outList->StartLine), *(outList->CurPos),
                  HEAPID_FIELD, UnderGroundChangeGoodsPcItem, pUGData, TRUE);

    
	GF_BGL_BmpWinOn(&outList->Win);
	GF_BGL_BmpWinOn(&outList->SubWin);

	//カーソル初期化
	outList->Cursor = FComAct_Init(HEAPID_FIELD);
	FComAct_CursorPosSet(outList->Cursor,200,10+8*2,118+8*2);
	FComAct_SetDrawFlg(outList->Cursor,FCA_UCURSOR,FALSE);
	FComAct_SetDrawFlg(outList->Cursor,FCA_DCURSOR,FALSE);
	
    outList->Seq = LIST_SEQ_LOOP;
}

//---------------------------------------------------------------------------
/**
 * @brief	リストクローズ
 * 
 * @param	outList		リスト
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void CloseList(UG_BASE_LIST *outList)
{
	CommMsgTalkWindowEnd(CommUnderGetMsgUnderItem());
	BmpMenuWinClear( &outList->SubWin, WINDOW_TRANS_OFF );	

    Ug_BmpListExit(outList->pUgListWork, outList->StartLine, outList->CurPos);
	//BmpListExit(outList->ListWork, outList->StartLine, outList->CurPos);
    
    BmpMenuWinClear(&outList->Win, WINDOW_TRANS_OFF );
    GF_BGL_LoadScreenV_Req( outList->Win.ini, outList->Win.frmnum );
    GF_BGL_BmpWinDel(&outList->Win);
	GF_BGL_BmpWinDel(&outList->SubWin);
    BMP_MENULIST_Delete(outList->List);
	// カーソル開放
	FComAct_Delete(outList->Cursor);
}

//==============================================================================
/**
 * 上下カーソルの表示検査
 * @param   
 * 
 * @retval  none
 */
//==============================================================================
static void CheckCursorDisp(FLD_COMACT_WORK* pCursor,
							const u16 inLine,
							const u16 inTotal,
							const u16 inMaxLine	)
{
    if(inTotal <= inMaxLine){
        return ;
    }
	
    if(inLine != 0){
        FComAct_SetDrawFlg(pCursor,FCA_UCURSOR,TRUE);
    }
    else{
        FComAct_SetDrawFlg(pCursor,FCA_UCURSOR,FALSE);
    }
    
    if(inTotal != (inLine+inMaxLine)){
        FComAct_SetDrawFlg(pCursor,FCA_DCURSOR,TRUE);
    }
    else{
        FComAct_SetDrawFlg(pCursor,FCA_DCURSOR,FALSE);
    }
}


static void UgBaseListMoveSe( UG_BASE_MENU* outMenu )
{
	u16 tmp_pos_bak;

	//BMPリストの全体位置を取得
	tmp_pos_bak = outMenu->pos_bak;		//退避
	BmpListDirectPosGet( outMenu->ListWork, &outMenu->pos_bak );

	//カーソルが動いたかチェック
	if( tmp_pos_bak != outMenu->pos_bak ){
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}

	return;
}

