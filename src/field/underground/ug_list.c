//=============================================================================
/**
 * @file	ug_list.c
 * @brief	SELECTボタンで BMPLIST_DATAを入れ替えてしまう機能付のbmplist
 * @author	k.ohno
 * @date    2006.06.11
 */
//=============================================================================

#include "common.h"
#include "fntsys.h"
#include "system/fontproc.h"
#include "system/snd_tool.h"
#include "ug_list.h"
#include "communication/communication.h"

//--------------------------------------------------------------------------------------------
/**
 * 設定関数
 * @param	bmplist		表示リストヘッダポインタ
 * @param	list_p		リスト初期位置
 * @param	cursor_p	カーソル初期位置
 * @param	mode		メモリ取得モード
 * @return	BMPリストワーク
 * @li	BMPリストワークはsys_AllocMemoryで確保
 */
//--------------------------------------------------------------------------------------------
UG_BMPLIST_WORK * Ug_BmpListSet(BMPLIST_HEADER * bmplist, u16 list_p, u16 cursor_p,
                                u8 heapID, CHANGE_UG_ITEM_FUNC pChangeFunc,
                                UNDERGROUNDDATA* pUGData,BOOL bBase)
{
    UG_BMPLIST_WORK* pUg = (UG_BMPLIST_WORK *)sys_AllocMemory( heapID, sizeof(UG_BMPLIST_WORK) );

    MI_CpuClear8(pUg, sizeof(UG_BMPLIST_WORK));

    pUg->pChangeFunc = pChangeFunc;
    if(pUg->pChangeFunc){
        pUg->pUGData = pUGData;
        pUg->bBase = bBase;
        pUg->pCursor = BMPCURSOR_Create( heapID );
        BMPCURSOR_ChangeColor(pUg->pCursor,
                              GF_PRINTCOLOR_MAKE(0x08,
                                                 0x09,
                                                 0x0f) );

        pUg->heapID = heapID;
//        pUg->pHead = bmplist;
        {
            BMP_MENULIST_DATA* tempList = BMP_MENULIST_Create(bmplist->count,pUg->heapID);
            int i;
            for(i = 0 ; i < bmplist->count; i++){
                BMP_MENULIST_AddLinkList(tempList, &bmplist->list[i]);
            }
            bmplist->list = tempList;
            pUg->pLinkMenuData = tempList;
        }
    }
	pUg->pos_bak = (list_p + cursor_p);
    pUg->pBmpList = BmpListSet(bmplist, list_p, cursor_p, heapID);
    return pUg;
}

//--------------------------------------------------------------------------------------------
/**
 * SELECTカーソルの表示
 * @param	pUg		UGBMPリストワーク
 * @retval	none
 */
//--------------------------------------------------------------------------------------------

static void _cursorDisp(u16 lp,u16 cp, UG_BMPLIST_WORK* pUg)
{
    u16 pos = pUg->lp + pUg->cp;   // 選択してる位置
    u16 line = BmpListParamGet(pUg->pBmpList,BMPLIST_ID_LINE);
    
    if((pUg->bklp != lp) || (pUg->bkcp != cp)){
        pUg->bklp = lp;
        pUg->bkcp = cp;
        if(((lp + line) < pos) || (lp > pos)){
            return;  // 範囲外は描画しない
        }
    }
    else{
        return;
    }
    {
        int x = BmpListParamGet(pUg->pBmpList, BMPLIST_ID_CURSOR_X);
        u8	yblk = BmpListParamGet(pUg->pBmpList, BMPLIST_ID_LINE_YBLK);
        int y =  (pos-lp) * yblk + BmpListParamGet(pUg->pBmpList, BMPLIST_ID_LINE_Y);
        GF_BGL_BMPWIN* pWin = (GF_BGL_BMPWIN*)BmpListParamGet(pUg->pBmpList, BMPLIST_ID_WIN);
        OHNO_PRINT("sel 表示  %d %d \n",x,y);
        BMPCURSOR_Print( pUg->pCursor, pWin, x, y );
    }
}

//--------------------------------------------------------------------------------------------
/**
 * メイン関数
 *
 * @param	pUg		UGBMPリストワーク
 *
 * @retval	"param = 選択パラメータ"
 * @retval	"BMPLIST_NULL = 選択中"
 * @retval	"BMPLIST_CANCEL	= キャンセル(Ｂボタン)"
 */
//--------------------------------------------------------------------------------------------
u32 Ug_BmpListMain( UG_BMPLIST_WORK* pUg )
{
    BMPLIST_WORK *lw = pUg->pBmpList;
    u16 lp,cp,tmp_pos_bak;
    int i,j;
	u32 ret;
    BMPLIST_DATA* tempList;
    
    if(pUg->pChangeFunc){
        int count = BmpListParamGet(lw, BMPLIST_ID_COUNT);
        BmpListPosGet(lw,&lp,&cp);
        if(pUg->bPush){
            _cursorDisp(lp,cp,pUg);
            if( (sys.trg & PAD_BUTTON_DECIDE) || (sys.trg & PAD_BUTTON_SELECT) ){
				Snd_SePlay( SEQ_SE_DP_SELECT );
                if(lp + cp == count - 1){  //キャンセルとは入れ替えない
                    return BMPLIST_NULL;
                }
                if(lp + cp == pUg->lp + pUg->cp){  //同じ場所とは入れ替えない
                    return BMPLIST_NULL;
                }
                // データ交換
                pUg->pChangeFunc(pUg->pUGData,pUg->lp + pUg->cp,lp + cp);
                tempList = BMP_MENULIST_Create(count,pUg->heapID);
                j = 0;
                for(i = 0 ; i < count; i++){
                    if(i == (pUg->lp + pUg->cp)){  // 抜き出しポイント
                        j++;
                    }
                    else{
                        BMP_MENULIST_AddLinkList(tempList, &pUg->pLinkMenuData[j]);
                        j++;
                    }
                    if((i) == (lp + cp)){  // 挿入ポイント
                        BMP_MENULIST_AddLinkList(tempList, &pUg->pLinkMenuData[pUg->lp + pUg->cp]);
                    }
                }
                if(pUg->bBase){
                    int param;
                    for(i=0; i < count-1 ; i++){
                        int flg;
                        int check = UnderGroundIsEntryGoodsPCItem(pUg->pUGData, i);
                        if (!check){//配置されていない
                            flg = 1;
                        }else{		//配置済み
                            flg = 0;
                        }
                        param = (i<<1)+flg;
                        tempList[i].param = param;
                    }
                    param = (i<<1)+1;
                    tempList[i].param = param;
                }
                else{
                     for(i = 0 ; i < count-1; i++){
                         tempList[i].param = i;  // ふりなおし
                     }
                }
                sys_FreeMemoryEz(pUg->pLinkMenuData);
                pUg->pLinkMenuData = tempList;
                BmpListSetMenuListData(lw, tempList);
                // リスト差し替え完了
                pUg->bPush = FALSE;
                BmpListRewrite(lw);

                OHNO_PRINT("SEL さしかえ\n");
                return BMPLIST_NULL;
            }
        }
        else{
            if( sys.trg & PAD_BUTTON_SELECT ){
				Snd_SePlay( SEQ_SE_DP_SELECT );
                if(lp + cp == count - 1){  //キャンセルは選択しない
                    return BMPLIST_NULL;
                }
                pUg->lp = lp;
                pUg->cp = cp;
                pUg->bklp = lp;
                pUg->bkcp = cp;
                pUg->bPush = TRUE;
                OHNO_PRINT("SEL 選択\n");
                return BMPLIST_NULL;
            }
        }
    }

#if 0

    return BmpListMain( lw );

#else

    ret = BmpListMain( lw );

	//BMPリストの全体位置を取得
	tmp_pos_bak = pUg->pos_bak;		//退避
	BmpListDirectPosGet( lw, &pUg->pos_bak );

	//カーソルが動いたかチェック
	if( tmp_pos_bak != pUg->pos_bak ){
		Snd_SePlay( SEQ_SE_DP_SELECT );
		//OS_Printf( "tmp_pos_bak = %d\n", tmp_pos_bak );
		//OS_Printf( "pUg->pos_bak = %d\n", pUg->pos_bak );
	}

	switch( ret ){
	case BMPLIST_NULL:
		break;
	case BMPLIST_CANCEL:
		Snd_SePlay( SEQ_SE_DP_SELECT );
		break;
	default:
		Snd_SePlay( SEQ_SE_DP_SELECT );
		break;
	};

	return ret;

#endif
}



//--------------------------------------------------------------------------------------------
/**
 * 終了関数
 *
 * @param	lw			BMPリストワーク
 * @param	list_bak	リスト位置バックアップワークポインタ
 * @param	cursor_bak	カーソル位置バックアップワークポインタ
 *
 * @return	none
 *
 * @li	lwをsys_FreeMemoryで開放
 * @li	バックアップワークは、NULL指定で保存しない
 */
//--------------------------------------------------------------------------------------------
void Ug_BmpListExit( UG_BMPLIST_WORK* pUg, u16 * list_bak, u16 * cursor_bak )
{
    BMPLIST_WORK *lw = pUg->pBmpList;

    BmpListExit(lw,list_bak,cursor_bak);
    if(pUg->pChangeFunc){
        BMPCURSOR_Delete( pUg->pCursor );
        sys_FreeMemoryEz(pUg->pLinkMenuData);
    }
    sys_FreeMemoryEz( pUg );
}

