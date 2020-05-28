//============================================================================================
/**
 * @file	ug_base_bmp.c
 * @brief	�閧��nBMP���u
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

///�ėp�I�����j���[�̃��X�g
static const BMPLIST_HEADER MenuListHeader = {
    NULL,			// �\�������f�[�^�|�C���^
    NULL,					// �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
    NULL,					// ���\�����Ƃ̃R�[���o�b�N�֐�
    NULL,					// 
    MENU_MAX,	// ���X�g���ڐ�
    MENU_MAX,	// �\���ő區�ڐ�
    0,						// ���x���\���w���W
    8,						// ���ڕ\���w���W
    0,						// �J�[�\���\���w���W
    0,						// �\���x���W
    FBMP_COL_BLACK,			// �����F
    FBMP_COL_WHITE,			// �w�i�F
    FBMP_COL_BLK_SDW,		// �����e�F
    0,						// �����Ԋu�w
    16,						// �����Ԋu�x
    BMPLIST_LRKEY_SKIP,		// �y�[�W�X�L�b�v�^�C�v
    FONT_SYSTEM,			// �����w��
    0,						// �a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
    NULL,                   // ���[�N
};

typedef struct UG_BASE_MENU_tag
{
	FIELDSYS_WORK* fsys;
    GF_BGL_BMPWIN  Win;		// BMP�E�B���h�E���[�N
	GF_BGL_BMPWIN  SubWin;		// BMP�T�u�E�B���h�E���[�N
	BMPLIST_DATA*  MenuList;
	
    BMPLIST_WORK*  ListWork;		// BMP���j���[���[�N
	STRBUF* StrBuf;
	u16 *StartLine;
	u16 *CurPos;
	u8 Seq;
	u32 ReturnIdx;				//���C���C�x���g�ɕԂ����j���[�C���f�b�N�X
	u16 pos_bak;
};

typedef struct UG_BASE_LIST_tag
{
	FIELDSYS_WORK* fsys;
	FLD_COMACT_WORK* Cursor;	//�㉺�J�[�\��
    GF_BGL_BMPWIN  Win;		// BMP�E�B���h�E���[�N
	GF_BGL_BMPWIN  SubWin;		// BMP�T�u�E�B���h�E���[�N
	BMPLIST_DATA*  List;
    UG_BMPLIST_WORK* pUgListWork;
    BMPLIST_WORK*  ListWork;		// BMP���j���[���[�N
	STRBUF* StrBuf;
	u16 *StartLine;
	u16 *CurPos;
	u8 GoodsCount;				//�u���Ă���O�b�Y��
	u8 GoodsLimit;				//�u����O�b�Y��
	u8 Seq;
	u32 ReturnIndex;				//���X�g�C���f�b�N�X
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
 * @brief	�閧��n���j���[�������A���P�[�V����
 * 
 * @return	menu	�閧��n���j���[
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
 * @brief	�閧��n���j���[������
 *
 * @param	menu		���j���[
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	pCurPos		�J�[�\���ʒu
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
 * @brief	���j���[���
 * 
 * @param	menu		�閧��n���j���[
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
 * @brief	���j���[�C���f�b�N�X��Ԃ�
 * 
 * @param	menu		�閧��n���j���[
 * 
 * @return	u32			�C���f�b�N�X
 */
//---------------------------------------------------------------------------
const u32 BMENU_GetReturnIndex(UG_BASE_MENU *menu)
{
	return menu->ReturnIdx;
}

//---------------------------------------------------------------------------
/**
 * @brief	���C�����j���[�C�x���g
 * 
 * @param	outMenu		�閧��n���j���[
 * 
 * @return	BOOL		TRUE:�I��	FALSE:�p��
 */
//---------------------------------------------------------------------------
BOOL BMENU_EditMainMenuControl(UG_BASE_MENU *outMenu)
{
	switch(outMenu->Seq){
	case MENU_SEQ_INIT:	//���j���[�쐬
		CreateBaseMainMenu(outMenu);
		break;
	case MENU_SEQ_LOOP:	//���j���[����
		BaseMenuMain(outMenu);
		break;
	case MENU_SEQ_END:	//�I��
		outMenu->Seq = MENU_SEQ_INIT;	//����̂��߂ɃV�[�P���X�����������Ă���
		CloseMenu(outMenu);
		return TRUE;
	}

	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	���j���[1���C���R�[���o�b�N
 * 
 * @param	wk			���X�g���[�N
 * @param	param		�p�����[�^
 * @param	mode		���g�p
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
 * @brief	���j���[�쐬
 * 
 * @param	outMenu		�閧��n���j���[
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

    //BMP�E�B���h�E����
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
			mes_uw_edit_02,	//�O�b�Y������
			mes_uw_edit_03,	//�O�b�Y�����ǂ�
			mes_uw_edit_04,	//�O�b�Y�̂��ǂ�
			mes_uw_edit_05,	//��߂�
		};
		
		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_uwedit_dat, HEAPID_FIELD);
		//����T�u�E�B���h�E
		{
			STRBUF * strb;
			GF_BGL_BmpWinDataFill(&outMenu->SubWin, FBMP_COL_WHITE);
			strb = MSGMAN_AllocString( msgman, mes_uw_edit_01 );
			GF_STR_PrintSimple( &outMenu->SubWin, FONT_SYSTEM, strb, 0, 0, MSG_NO_PUT, NULL );
			STRBUF_Delete( strb );
		}
		//���j���[
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
 * @brief	���j���[���C��
 * 
 * @param	outMenu		�閧��n���j���[
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
    default:	//���^�[���R�[�h�̃Z�b�g
        {
			//���C���C�x���g�ɕԂ����^�[���R�[�h���Z�b�g
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
 * @brief	���j���[�N���[�Y
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
 * @brief	��s���Ƃ̕`��R�[���o�b�N(���j���[�쐬��)
 * 
 * @param	wk			���X�g���[�N
 * @param	param		�p�����[�^
 * @param	y			�� ���g�p
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void	LineCallBack(BMPLIST_WORK * wk, u32 param, u8 y)
{
	//���łɊ�n�ɂ����Ă��邩���`�F�b�N
	u8 flg;
	flg = param & 0x01;
	if (flg){//�z�u����Ă��Ȃ�
		BmpListTmpColorChange( wk, FBMP_COL_BLACK, FBMP_COL_WHITE , FBMP_COL_BLK_SDW );
	}else{		//�z�u�ς�
		BmpListTmpColorChange( wk, FBMP_COL_BLK_SDW, FBMP_COL_WHITE , FBMP_COL_BLK_SDW );
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	�O�b�Y���X�g�������A���P�[�V����
 * 
 * @return	list		���X�g
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
 * @brief	�O�b�Y���X�g������
 *
 * @param	list		���X�g
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	pCurPos		�J�[�\���ʒu
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
 * @brief	�O�b�Y���Z�b�g
 * 
 * @param	list		���X�g
 * @param	inNum		�O�b�Y��
 * @param	inLimit		���~�b�g
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
 * @brief	�O�b�Y���X�g���
 * 
 * @param	list		���X�g
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
 * @brief	�O�b�Y���X�g�C���f�b�N�X��Ԃ�
 * 
 * @param	list		���X�g
 * 
 * @return	u32			���X�g�C���f�b�N�X
 */
//---------------------------------------------------------------------------
const u32 BMENU_GetReturnListIdx(UG_BASE_LIST *list)
{
	return list->ReturnIndex;
}

//---------------------------------------------------------------------------
/**
 * @brief	�O�b�Y���X�g�R���g���[��
 * 
 * @param	outList		���X�g
 * 
 * @return	BOOL		TRUE:�I��	FALSE:�p��
 */
//---------------------------------------------------------------------------
BOOL BMENU_EditGoodsListControl(UG_BASE_LIST *outList)
{
	switch(outList->Seq){
	case LIST_SEQ_INIT:	//���j���[�쐬
		CreateBaseGoodsList(outList);
		break;
	case LIST_SEQ_LOOP:	//���j���[����
		BaseGoodsListMain(outList);
		break;
	case LIST_SEQ_END:	//�I��
		outList->Seq = LIST_SEQ_INIT;	//����̂��߂ɃV�[�P���X�����������Ă���
		CloseList(outList);
		return TRUE;
	}

	//�㉺�J�[�\���`��
	if(outList->Cursor){
        FActCom_Main(outList->Cursor);
    }

	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	�O�b�Y���X�g���C��
 * 
 * @param	outList		���X�g
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
		outList->ReturnIndex = LIST_CANCEL_CODE;	//�O�b�Y��I��
        outList->Seq = LIST_SEQ_END;
		Snd_SePlay( UG_BASE_SE_SELECT );
        break;
    default:	//���^�[���R�[�h�̃Z�b�g
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
 * @brief	���X�g1���C���R�[���o�b�N
 * 
 * @param	wk			���X�g���[�N
 * @param	param		�p�����[�^
 * @param	mode		���g�p	
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
 * @brief	�O�b�Y���X�g�쐬
 * 
 * @param	outList		���X�g
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

	//�O�b�Y�̐����擾
	pUGData = SaveData_GetUnderGroundData(outList->fsys->savedata);
	count = UnderGroundGetNumGoodsPCItem(pUGData);
	outList->Count = count;
	line = count+1;
	if (line>GOODS_MENU_MAX){
		line = GOODS_MENU_MAX;
	}
    //BMP�E�B���h�E����
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
		
		//����T�u�E�B���h�E
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
					NUMBER_DISPTYPE_SPACE , NUMBER_CODETYPE_DEFAULT );	//�u���Ă���O�b�Y��
			WORDSET_RegisterNumber(wordset, 1, outList->GoodsLimit, 2,
					NUMBER_DISPTYPE_SPACE , NUMBER_CODETYPE_DEFAULT );	//�u����O�b�Y��
			
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
			//���łɊ�n�ɂ����Ă��邩���`�F�b�N
			check = UnderGroundIsEntryGoodsPCItem(pUGData, i);
			if (!check){//�z�u����Ă��Ȃ�
				flg = 1;
			}else{		//�z�u�ς�
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

	//�J�[�\��������
	outList->Cursor = FComAct_Init(HEAPID_FIELD);
	FComAct_CursorPosSet(outList->Cursor,200,10+8*2,118+8*2);
	FComAct_SetDrawFlg(outList->Cursor,FCA_UCURSOR,FALSE);
	FComAct_SetDrawFlg(outList->Cursor,FCA_DCURSOR,FALSE);
	
    outList->Seq = LIST_SEQ_LOOP;
}

//---------------------------------------------------------------------------
/**
 * @brief	���X�g�N���[�Y
 * 
 * @param	outList		���X�g
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
	// �J�[�\���J��
	FComAct_Delete(outList->Cursor);
}

//==============================================================================
/**
 * �㉺�J�[�\���̕\������
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

	//BMP���X�g�̑S�̈ʒu���擾
	tmp_pos_bak = outMenu->pos_bak;		//�ޔ�
	BmpListDirectPosGet( outMenu->ListWork, &outMenu->pos_bak );

	//�J�[�\�������������`�F�b�N
	if( tmp_pos_bak != outMenu->pos_bak ){
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}

	return;
}

