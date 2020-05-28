//=============================================================================
/**
 * @file	ug_list.c
 * @brief	SELECT�{�^���� BMPLIST_DATA�����ւ��Ă��܂��@�\�t��bmplist
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
 * �ݒ�֐�
 * @param	bmplist		�\�����X�g�w�b�_�|�C���^
 * @param	list_p		���X�g�����ʒu
 * @param	cursor_p	�J�[�\�������ʒu
 * @param	mode		�������擾���[�h
 * @return	BMP���X�g���[�N
 * @li	BMP���X�g���[�N��sys_AllocMemory�Ŋm��
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
 * SELECT�J�[�\���̕\��
 * @param	pUg		UGBMP���X�g���[�N
 * @retval	none
 */
//--------------------------------------------------------------------------------------------

static void _cursorDisp(u16 lp,u16 cp, UG_BMPLIST_WORK* pUg)
{
    u16 pos = pUg->lp + pUg->cp;   // �I�����Ă�ʒu
    u16 line = BmpListParamGet(pUg->pBmpList,BMPLIST_ID_LINE);
    
    if((pUg->bklp != lp) || (pUg->bkcp != cp)){
        pUg->bklp = lp;
        pUg->bkcp = cp;
        if(((lp + line) < pos) || (lp > pos)){
            return;  // �͈͊O�͕`�悵�Ȃ�
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
        OHNO_PRINT("sel �\��  %d %d \n",x,y);
        BMPCURSOR_Print( pUg->pCursor, pWin, x, y );
    }
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���֐�
 *
 * @param	pUg		UGBMP���X�g���[�N
 *
 * @retval	"param = �I���p�����[�^"
 * @retval	"BMPLIST_NULL = �I��"
 * @retval	"BMPLIST_CANCEL	= �L�����Z��(�a�{�^��)"
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
                if(lp + cp == count - 1){  //�L�����Z���Ƃ͓���ւ��Ȃ�
                    return BMPLIST_NULL;
                }
                if(lp + cp == pUg->lp + pUg->cp){  //�����ꏊ�Ƃ͓���ւ��Ȃ�
                    return BMPLIST_NULL;
                }
                // �f�[�^����
                pUg->pChangeFunc(pUg->pUGData,pUg->lp + pUg->cp,lp + cp);
                tempList = BMP_MENULIST_Create(count,pUg->heapID);
                j = 0;
                for(i = 0 ; i < count; i++){
                    if(i == (pUg->lp + pUg->cp)){  // �����o���|�C���g
                        j++;
                    }
                    else{
                        BMP_MENULIST_AddLinkList(tempList, &pUg->pLinkMenuData[j]);
                        j++;
                    }
                    if((i) == (lp + cp)){  // �}���|�C���g
                        BMP_MENULIST_AddLinkList(tempList, &pUg->pLinkMenuData[pUg->lp + pUg->cp]);
                    }
                }
                if(pUg->bBase){
                    int param;
                    for(i=0; i < count-1 ; i++){
                        int flg;
                        int check = UnderGroundIsEntryGoodsPCItem(pUg->pUGData, i);
                        if (!check){//�z�u����Ă��Ȃ�
                            flg = 1;
                        }else{		//�z�u�ς�
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
                         tempList[i].param = i;  // �ӂ�Ȃ���
                     }
                }
                sys_FreeMemoryEz(pUg->pLinkMenuData);
                pUg->pLinkMenuData = tempList;
                BmpListSetMenuListData(lw, tempList);
                // ���X�g�����ւ�����
                pUg->bPush = FALSE;
                BmpListRewrite(lw);

                OHNO_PRINT("SEL ��������\n");
                return BMPLIST_NULL;
            }
        }
        else{
            if( sys.trg & PAD_BUTTON_SELECT ){
				Snd_SePlay( SEQ_SE_DP_SELECT );
                if(lp + cp == count - 1){  //�L�����Z���͑I�����Ȃ�
                    return BMPLIST_NULL;
                }
                pUg->lp = lp;
                pUg->cp = cp;
                pUg->bklp = lp;
                pUg->bkcp = cp;
                pUg->bPush = TRUE;
                OHNO_PRINT("SEL �I��\n");
                return BMPLIST_NULL;
            }
        }
    }

#if 0

    return BmpListMain( lw );

#else

    ret = BmpListMain( lw );

	//BMP���X�g�̑S�̈ʒu���擾
	tmp_pos_bak = pUg->pos_bak;		//�ޔ�
	BmpListDirectPosGet( lw, &pUg->pos_bak );

	//�J�[�\�������������`�F�b�N
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
 * �I���֐�
 *
 * @param	lw			BMP���X�g���[�N
 * @param	list_bak	���X�g�ʒu�o�b�N�A�b�v���[�N�|�C���^
 * @param	cursor_bak	�J�[�\���ʒu�o�b�N�A�b�v���[�N�|�C���^
 *
 * @return	none
 *
 * @li	lw��sys_FreeMemory�ŊJ��
 * @li	�o�b�N�A�b�v���[�N�́ANULL�w��ŕۑ����Ȃ�
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

