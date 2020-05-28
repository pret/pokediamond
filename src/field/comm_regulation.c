//=============================================================================
/**
 * @file	comm_regulation.c
 * @bfief	���M�����[�V�����Ǘ��̃C�x���g
 * @author	katsumi ohno
 * @date	06/05/22
 */
//=============================================================================

#include "common.h"
#include "system/bmp_list.h"
#include "system/fontproc.h"
#include "system/bmp_menu.h"
#include "field/fieldsys.h"
//#include "system/pm_str.h"
#include "system/gamedata.h"
#include "system/window.h"
#include "system/wipe.h"
#include "system\bmp_cursor.h"

#include "communication/communication.h"
#include "communication/comm_state.h"
#include "comm_command_field.h"
#include "comm_player.h"
#include "comm_field_state.h"
#include "msgdata/msg.naix"
#include "system/wordset.h"
#include "msgdata/msg_connect.h"
#include "msgdata/msg_directbattlecorner.h"

#include "fieldmap.h"
#include "fld_bmp.h"
#include "talk_msg.h"
#include "field_subproc.h"
#include "field/field.h"
#include "application/pokelist.h"
#include "field_battle.h"
#include "battle/attr_def.h"

#include "savedata/zukanwork.h"
#include "poketool/poke_number.h"
#include "savedata/perapvoice.h"
#include "savedata/regulation_data.h"
#include "ev_time.h"
#include "comm_direct_counter_def.h"
#include "comm_direct_counter_se.h"
#include "poketool/poke_regulation.h"

#include "comm_regulation.h"

#define _EVWIN_MSG_BUF_SIZE		(90 * 2)			//���b�Z�[�W�o�b�t�@�T�C�Y
#define _CGX_COUNTER_TOP_NUM (1)

//------------------------------------------------
///�ėp�I�����j���[�̃��X�g
//------------------------------------------------
static const BMPLIST_HEADER _menuListHeader = {
    NULL,			// �\�������f�[�^�|�C���^
    NULL,					// �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
    NULL,					// ���\�����Ƃ̃R�[���o�b�N�֐�
    NULL,					// 
    0,	// ���X�g���ڐ�
    0,	// �\���ő區�ڐ�
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


//-----------------------------------------------------------------
//  ���M�����[�V�������X�g
//-----------------------------------------------------------------

typedef struct{
    BMPLIST_WORK* lw;		 // ���j���[���[�N�|�C���^
    BMPLIST_WORK* subLw;		 // ���j���[���[�N�|�C���^
	BMPLIST_DATA*   menulist;
	BMPLIST_DATA*   subMenulist;
    FIELDSYS_WORK* pFSys;
	STRBUF* MsgString;							// ��b���b�Z�[�W�p
	STRBUF* MsgString2;							// ��b���b�Z�[�W�p
	STRBUF* TalkString;							// ��b���b�Z�[�W�p
	STRBUF* TalkStringEx;							// ��b���b�Z�[�WExpand�p
    GF_BGL_BMPWIN winReg;
    GF_BGL_BMPWIN win;
    GF_BGL_BMPWIN winSub;
	GF_BGL_BMPWIN MsgWin;									// ��b�E�C���h�E
	WORDSET* WordSet;					// ���b�Z�[�W�W�J�p���[�N�}�l�[�W���[
	MSGDATA_MANAGER* MsgManager;				// ���O���̓��b�Z�[�W�f�[�^�}�l�[�W���[
    ZKN_HEIGHT_GRAM_PTR pZKN;
    u16* retWk;
    int	msgIndex;								// �I�����o�p���[�N
    u16 selectReg;
    u16 selectSub;
    int seq;
	u16 pos_bak;
	u16 pos_bak2;
} _EV_REGULATION_LIST_WORK;


//------------------------------------------------------------------
/**
 * ���b�Z�[�W������
 * @param   wk		
 */
//------------------------------------------------------------------

static void _messageOn(_EV_REGULATION_LIST_WORK* wk, int msg)
{
    if( GF_BGL_BmpWinAddCheck(&wk->MsgWin) == FALSE ){
        GF_BGL_BmpWinInit( &wk->MsgWin );
        FldTalkBmpAdd( wk->pFSys->bgl, &wk->MsgWin, FLD_MBGFRM_FONT );
        FieldTalkWinPut( &wk->MsgWin, SaveData_GetConfig(wk->pFSys->savedata) );
    }
    else{
        FieldTalkWinClear( &wk->MsgWin );
    }
    MSGMAN_GetString( wk->MsgManager, msg, wk->MsgString );
    WORDSET_ExpandStr(wk->WordSet, wk->MsgString2, wk->MsgString);
    wk->msgIndex = FieldTalkMsgStart(&wk->MsgWin, wk->MsgString2, SaveData_GetConfig(wk->pFSys->savedata), 1);
}


//------------------------------------------------------------------
/**
 * ���b�Z�[�W������
 * @param   wk		
 */
//------------------------------------------------------------------

static void _messageDelete(_EV_REGULATION_LIST_WORK* wk, BOOL bDisp)
{
    if(bDisp){
        BmpTalkWinClear(&wk->MsgWin, WINDOW_TRANS_ON );
        GF_BGL_BmpWinOff(&wk->MsgWin);
    }
    GF_BGL_BmpWinDel(&wk->MsgWin);
}

//------------------------------------------------------------------
/**
 * CUP�����O�ɓo�^
 * @param   wk		
 */
//------------------------------------------------------------------

static void _registerCupName(_EV_REGULATION_LIST_WORK* wk,int regNo)
{
    Data_GetRegulationName(wk->pFSys->savedata, regNo, wk->TalkString, HEAPID_FIELD);
    WORDSET_RegisterWord(wk->WordSet, 0, wk->TalkString, PM_MALE, TRUE, PM_LANG);
}

//------------------------------------------------------------------
/**
 * ���M�����[�V�������X�g�\��
 * @param   wk		
 */
//------------------------------------------------------------------
#define _REG_NONE_NO (12)

static void _createRegulationList(_EV_REGULATION_LIST_WORK* wk)
{
    BMPLIST_HEADER list_h;
	GF_BGL_BMPWIN* win = &(wk->win);
    REGULATION* pReg = SaveData_GetRegulation(wk->pFSys->savedata,0);
    int line = 5;

    if(pReg){
        line++;
    }
    if( GF_BGL_BmpWinAddCheck(win) == FALSE ){
        int i;
        wk->menulist = BMP_MENULIST_Create( line + 2, HEAPID_FIELD );
		GF_BGL_BmpWinAdd( wk->pFSys->bgl, win, FLD_MBGFRM_FONT,
                          1, 1,
                          16, (line + 2) * 2,
                          FLD_SYSFONT_PAL, _CGX_COUNTER_TOP_NUM );
        BmpMenuWinWrite(&wk->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );

        BMP_MENULIST_AddArchiveString(wk->menulist, wk->MsgManager, msg_connect_rulebook_18, _REG_NONE_NO);
		for(i = 0; i < line; i++){
            _registerCupName(wk, i);
//            Data_GetRegulationName(wk->pFSys->savedata, i, wk->TalkString, HEAPID_FIELD);
  //          WORDSET_RegisterWord(wk->WordSet, 0, wk->TalkString, PM_MALE, TRUE, PM_LANG);
            MSGMAN_GetString(wk->MsgManager, msg_connect_rulebook_08, wk->TalkString);
            WORDSET_ExpandStr(wk->WordSet, wk->TalkStringEx, wk->TalkString);
            BMP_MENULIST_AddString(wk->menulist, wk->TalkStringEx, i);
		}
        BMP_MENULIST_AddArchiveString(wk->menulist, wk->MsgManager, msg_connect_rulebook_09, BMPLIST_CANCEL);
	}

    list_h = _menuListHeader;
    list_h.count = line+2;
    list_h.line = line+2;
    list_h.list = wk->menulist;
    list_h.win = &wk->win;
    list_h.work = wk;
    wk->lw = BmpListSet(&list_h, 0, wk->selectReg, HEAPID_FIELD);
    GF_BGL_BmpWinOn(&wk->win);
}

static void _deleteRegulationList(_EV_REGULATION_LIST_WORK* wk)
{
    if(wk->lw){
        BmpListExit(wk->lw, NULL, NULL);
        BmpMenuWinClear(&wk->win, WINDOW_TRANS_OFF );
        GF_BGL_LoadScreenV_Req( wk->win.ini, wk->win.frmnum );
        GF_BGL_BmpWinDel(&wk->win);
        BMP_MENULIST_Delete(wk->menulist);
        wk->lw = NULL;
    }
}

//------------------------------------------------------------------
/**
 * ���M�����[�V�����I�����j���[ �I��
 * @param   _EV_REGULATION_LIST_WORK wk
 */
//------------------------------------------------------------------

static int _regulationListFunc(_EV_REGULATION_LIST_WORK* wk)
{
    int ret;
	u16 tmp_pos_bak;

    ret = BmpListMain(wk->lw);
    BmpListPosGet( wk->lw, NULL, &wk->selectReg );

	//BMP���X�g�̑S�̈ʒu���擾
	tmp_pos_bak = wk->pos_bak;		//�ޔ�
	BmpListDirectPosGet( wk->lw, &wk->pos_bak );

	//�J�[�\�������������`�F�b�N
	if( tmp_pos_bak != wk->pos_bak ){
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}

    switch(ret){
      case BMPLIST_NULL:
        return 0;
      case _REG_NONE_NO:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        wk->pFSys->regulation = NULL;
        _deleteRegulationList(wk);
        return 2;
      case BMPLIST_CANCEL:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        wk->pFSys->regulation = NULL;
        _deleteRegulationList(wk);
        return -1;
      default:  // ���M�����[�V�����I��
		Snd_SePlay( SEQ_SE_DP_SELECT );
        wk->pFSys->regulation = Data_GetRegulation(wk->pFSys->savedata, ret);
        break;
    }
    return 1;
}

//------------------------------------------------------------------
/**
 * �T�u�E�C���h�E�\���@OK�����[���`�F�b�N��
 * @param   wk		
 */
//------------------------------------------------------------------

#define _OK_COMMAND  (1)
#define _VIEW_COMMAND  (2)

typedef struct {
	u32  str_id;
	u32  param;
} _SUB_MENU_PARAM;

static _SUB_MENU_PARAM SubMenuParamList[] = {
    { msg_connect_rulebook_10, (u32)_OK_COMMAND },
    { msg_connect_rulebook_11, (u32)_VIEW_COMMAND },
    { msg_connect_rulebook_09, (u32)BMPLIST_CANCEL },
};

static void _subMenuStart(_EV_REGULATION_LIST_WORK* wk)
{
    BMPLIST_HEADER list_h;
    int line = 3, start;
    int posy = 10;
    int sizex = 9;
    int posx = 22;

    _SUB_MENU_PARAM* pSubList = SubMenuParamList;

    wk->subMenulist = BMP_MENULIST_Create( line, HEAPID_FIELD );
    GF_BGL_BmpWinAdd(wk->pFSys->bgl,&wk->winSub,
                     GF_BGL_FRAME3_M, posx, posy,
                     sizex, line * 2, FLD_SYSFONT_PAL,
                     FLD_MSG_WIN_CGX - sizex * line * 2);
    BmpMenuWinWrite(&wk->winSub, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
    {
        int i;
        for(i = 0; i < line; i++) {
            BMP_MENULIST_AddArchiveString(wk->subMenulist,wk->MsgManager,
                                          pSubList->str_id,
                                          pSubList->param);
            pSubList++;
        }
    }
    list_h = _menuListHeader;
    list_h.count = line;
    list_h.line = line;
    list_h.list = wk->subMenulist;
    list_h.win = &wk->winSub;
    list_h.work = wk;
    wk->subLw = BmpListSet(&list_h, 0, wk->selectSub, HEAPID_FIELD);
    GF_BGL_BmpWinOn(&wk->winSub);
}


static int _regulationSubFunc(_EV_REGULATION_LIST_WORK* wk)
{
    int ret;
	u16 tmp_pos_bak;

    ret = BmpListMain(wk->subLw);
    BmpListPosGet( wk->subLw, NULL, &wk->selectSub );
    
	//BMP���X�g�̑S�̈ʒu���擾
	tmp_pos_bak = wk->pos_bak2;		//�ޔ�
	BmpListDirectPosGet( wk->subLw, &wk->pos_bak2 );

	//�J�[�\�������������`�F�b�N
	if( tmp_pos_bak != wk->pos_bak2 ){
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}

    switch(ret){
      case BMPLIST_NULL:
        return 0;
      case BMPLIST_CANCEL:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        ret = -1;
        break;
      default:  // submenu����
		Snd_SePlay( SEQ_SE_DP_SELECT );
        _deleteRegulationList(wk);
        break;
    }
    if(wk->subLw){
        BmpListExit(wk->subLw, NULL, NULL);
        BmpMenuWinClear(&wk->winSub, WINDOW_TRANS_OFF );
        GF_BGL_LoadScreenV_Req( wk->winSub.ini, wk->winSub.frmnum );
        GF_BGL_BmpWinDel(&wk->winSub);
        BMP_MENULIST_Delete(wk->subMenulist);
        wk->subLw = NULL;
    }
    return ret;
}

//-----------------------------------------------------------------------------
/**
 * @brief	���M�����[�V���������\��
 * @param	FIELDSYS_WORK
 * @retval	none
 */
//-----------------------------------------------------------------------------

static u8 getTbl[]={
  REGULATION_POKE_NUM,      //�|�P������
  REGULATION_LEVEL,         //�|�P�����̃��x��
  REGULATION_TOTAL_LEVEL,   //�|�P�����̃��x�����v
  REGULATION_HEIGHT,        //�g��   0.2 - 9.9m 
  REGULATION_WEIGHT,       //�̏d    1-99  kg
  REGULATION_EVOLUTION,     //�i���|�P�������ǂ���
  REGULATION_LEGEND,       // �`���n�L��
  REGULATION_BOTH_MONSTER, //�����|�P�����n�j���H
  REGULATION_BOTH_ITEM,    //��������n�j���H
};

static u8 getMsg[]={
    msg_dbc_rule15,
    msg_dbc_rule16,
    msg_dbc_rule17,
    msg_dbc_rule18,
    msg_dbc_rule20,
    msg_dbc_rule22,
    msg_dbc_rule22,
    msg_dbc_rule22,
    msg_dbc_rule24,
};



static void _createViewWindow(_EV_REGULATION_LIST_WORK* wk)
{
    MSGDATA_MANAGER* msgman;
    WORDSET* pWordSet = wk->WordSet;
    STRBUF* pBuf1;
    STRBUF* pBuf2;
    GF_BGL_BMPWIN* pWin;
    int i, ans, msg, left;
    const int _STATE_UP = 16;
    const int _HEAD_LEFT = 2;
    const int _HEIGHT = 15;
    const int _COLON = 55;
    const int _LEFT = (24*8)-1;
    
    msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_directbattlecorner_dat, HEAPID_FIELD);
    pBuf1 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD);
    pBuf2 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD);
    pWin = &wk->winReg;

    GF_BGL_BmpWinAdd( wk->pFSys->bgl, pWin,
                      GF_BGL_FRAME3_M, 4, 2, 24, 19,
                      FLD_SYSFONT_PAL, _CGX_COUNTER_TOP_NUM );
    BmpMenuWinWrite(pWin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	GF_BGL_BmpWinDataFill( pWin, FBMP_COL_WHITE );

    _registerCupName(wk, wk->selectReg-1);
//    Data_GetRegulationName(wk->pFSys->savedata, wk->selectReg, pBuf2, HEAPID_FIELD);
  //  WORDSET_RegisterWord( pWordSet, 0, pBuf2, PM_MALE, TRUE, PM_LANG);
    MSGMAN_GetString( msgman, msg_dbc_rule26, pBuf1 );   //������
    WORDSET_ExpandStr(pWordSet, pBuf2, pBuf1 );
    GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf2, _HEAD_LEFT + _COLON, 0, MSG_NO_PUT, NULL);

    for(i = 0;i < 9;i++){
        MSGMAN_GetString( msgman, msg_dbc_rule06+i, pBuf1 );   // ���ڑS��
        GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf1, _HEAD_LEFT,
                           _STATE_UP + _HEIGHT*i, MSG_NO_PUT, NULL);
    }

    for(i = 0;i < 9;i++){
        ans = Regulation_GetParam(wk->pFSys->regulation,getTbl[i]);
        msg = getMsg[i];
        switch(getTbl[i]){
          case REGULATION_POKE_NUM:      //�|�P������
            WORDSET_RegisterNumber(pWordSet, 0,
                                   ans, 1,
                                   NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
            break;
          case REGULATION_LEVEL:         //�|�P�����̃��x��
            WORDSET_RegisterNumber(pWordSet, 0,
                                   ans, 3,
                                   NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
            break;
          case REGULATION_TOTAL_LEVEL:   //�|�P�����̃��x�����v
            if(ans == 0){
                msg = msg_dbc_rule27;
            }
            else{
                WORDSET_RegisterNumber(pWordSet, 0,
                                       ans, 3,
                                       NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
            }
            break;
          case REGULATION_HEIGHT:        //�g��   0.2 - 9.9m
            WORDSET_RegisterNumber(pWordSet, 0,
                                   abs(ans/10), 2,
                                   NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
            WORDSET_RegisterNumber(pWordSet, 1,
                                   abs(ans%10), 2,
                                   NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
            if(ans == 0){
                msg = msg_dbc_rule27;
            }
            else if(ans > 0){
                msg++;
            }
            break;
          case REGULATION_WEIGHT:       //�̏d    1-99  kg
            WORDSET_RegisterNumber(pWordSet, 0,
                                   abs(ans), 2,
                                   NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
            if(ans == 0){
                msg = msg_dbc_rule27;
            }
            else if(ans > 0){
                msg++;
            }
            break;
          case REGULATION_EVOLUTION:     //�i���|�P�������ǂ���
          case REGULATION_LEGEND:       // �`���n�L��
          case REGULATION_BOTH_MONSTER: //�����|�P�����n�j���H
          case REGULATION_BOTH_ITEM:    //��������n�j���H
            if(ans == 0){
                msg++;
            }
            break;
          default:
            break;
        }
//        OHNO_SP_PRINT("ans = %d\n",ans);
        MSGMAN_GetString( msgman, msg, pBuf1 );
        WORDSET_ExpandStr(pWordSet, pBuf2, pBuf1 );
        {
            int length = FontProc_GetPrintStrWidth( FONT_SYSTEM, pBuf2, 0 );
            int x      = _LEFT - length;
            GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf2, x,
                               _STATE_UP+_HEIGHT*i, MSG_NO_PUT, NULL);
        }
    }
    STRBUF_Delete(pBuf1);
    STRBUF_Delete(pBuf2);
    MSGMAN_Delete(msgman);

    GF_BGL_BmpWinOn(pWin);
}

static void _deleteViewWindow(_EV_REGULATION_LIST_WORK* wk)
{
    BmpMenuWinClear(&wk->winReg, WINDOW_TRANS_OFF );
    GF_BGL_LoadScreenV_Req( wk->winReg.ini, wk->winReg.frmnum );
    GF_BGL_BmpWinDel(&wk->winReg);
}

//-----------------------------------------------------------------------------
/**
 * @brief	�|�P��������
 * @param	FIELDSYS_WORK
 * @retval	none
 */
//-----------------------------------------------------------------------------

static BOOL _pokeCheck(_EV_REGULATION_LIST_WORK* wk)
{
	POKEPARTY *temoti = SaveData_GetTemotiPokemon(wk->pFSys->savedata);
    int ret = PokeRegulationMatchPartialPokeParty(wk->pFSys->regulation,temoti,wk->pZKN);
    int ans;

    switch(ret){
      case POKE_REG_OK:
        return TRUE;
      case POKE_REG_NUM_FAILED:
        Snd_SePlay(DIRECT_BATTLE_SE_ERROR);
        _registerCupName(wk, wk->selectReg-1);
        ans = Regulation_GetParam(wk->pFSys->regulation,REGULATION_POKE_NUM);
        WORDSET_RegisterNumber(wk->WordSet, 1,
                               ans, 1,
                               NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
        _messageOn(wk, msg_connect_rulebook_02);
        break;
      default:
      case POKE_REG_TOTAL_LV_FAILED:
        Snd_SePlay(DIRECT_BATTLE_SE_ERROR);
        _registerCupName(wk, wk->selectReg-1);
        ans = Regulation_GetParam(wk->pFSys->regulation,REGULATION_TOTAL_LEVEL);
        WORDSET_RegisterNumber(wk->WordSet, 1,
                               ans, 3,
                               NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
        _messageOn(wk, msg_connect_rulebook_16);
        break;
    }
    return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	���M�����[�V�����C�x���g
 * @param	FIELDSYS_WORK
 * @retval	none
 */
//-----------------------------------------------------------------------------

static BOOL GMEVENT_RegulationList(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	_EV_REGULATION_LIST_WORK *wk = FieldEvent_GetSpecialWork(event);
    int ret;

    enum{
        _INIT,
        _REG_LIST,
        _MENU_LOOP,
        _SUB_MENU,
        _SUB_MENU_LOOP,
        _CHECK,
        _ERROR_KEYWAIT,
        _VIEW_MENU,
        _VIEW_MENU_WAIT,
        _VIEW_MENU_END,
        _EXIT,
        _FREE,
        _NOP
	};

    switch (wk->seq) {
      case _INIT:
        OHNO_PRINT("_INIT\n");
        _messageOn(wk,msg_connect_rulebook_01);
        OHNO_PRINT("_INIT_END\n");
        wk->seq++;
        break;
      case _REG_LIST:
        if(FldTalkMsgEndCheck(wk->msgIndex)){
            _createRegulationList(wk);
            wk->seq ++;
        }
        break;
      case _MENU_LOOP:
        ret = _regulationListFunc(wk);
        if( ret == -1){
            *wk->retWk = REGULATION_RET_END;
            wk->seq = _FREE;  // ���M�����[�V�������߂Ȃ�����
        }
        else if(ret == 2){
            *wk->retWk = REGULATION_RET_NONE;
            wk->seq = _FREE;  // ���M�����[�V�������߂Ȃ�����
        }
        else if(ret == 1){
            wk->seq = _SUB_MENU;
        }
        break;
      case _SUB_MENU:
        _subMenuStart(wk);
        wk->seq++;
        break;
      case _SUB_MENU_LOOP:
        ret = _regulationSubFunc(wk);
        if( ret == -1){
            wk->seq = _MENU_LOOP;
        }
        else if(ret == _OK_COMMAND){
            wk->seq = _CHECK;
        }
        else if(ret == _VIEW_COMMAND){
            wk->seq = _VIEW_MENU;
        }
        break;
      case _CHECK:  // �����̌���
        if(_pokeCheck(wk)){
            *wk->retWk = REGULATION_RET_OK;
            wk->seq = _FREE;  // ����
        }
        else{
            wk->seq = _ERROR_KEYWAIT;
        }
        break;
      case _ERROR_KEYWAIT:
        if(FldTalkMsgEndCheck(wk->msgIndex)){
            if(sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL)){
                wk->seq = _INIT;
            }
        }
        break;
      case _VIEW_MENU:
        _messageDelete(wk,TRUE);
        _createViewWindow(wk);
        wk->seq++;
        break;
      case _VIEW_MENU_WAIT:
        if(sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL)){
            _deleteViewWindow(wk);
            _messageOn(wk,msg_connect_rulebook_01);
            _createRegulationList(wk);
            wk->seq = _VIEW_MENU_END;
        }
        break;
      case _VIEW_MENU_END:
        if(FldTalkMsgEndCheck(wk->msgIndex)){
            wk->seq = _SUB_MENU;
        }
        break;
      case _EXIT:
        break;
      case _FREE:
        _deleteRegulationList(wk);
        _messageDelete(wk,FALSE);
        WORDSET_Delete(wk->WordSet);
        MSGMAN_Delete(wk->MsgManager);
        STRBUF_Delete(wk->MsgString);
        STRBUF_Delete(wk->MsgString2);
        STRBUF_Delete(wk->TalkString);
        STRBUF_Delete(wk->TalkStringEx);
        PokeRegulationEnd(wk->pZKN);
        sys_FreeMemoryEz(wk);
		return TRUE;
      default:
		return TRUE;
	}
	return FALSE;
}



static _EV_REGULATION_LIST_WORK* _createRegulationWork(FIELDSYS_WORK * pFSys)
{
    _EV_REGULATION_LIST_WORK *wk = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(_EV_REGULATION_LIST_WORK));
    MI_CpuClear8(wk, sizeof(_EV_REGULATION_LIST_WORK));
    wk->seq = 0;
    wk->pFSys = pFSys;
    wk->pFSys->regulation = NULL;
    wk->WordSet    = WORDSET_Create( HEAPID_FIELD );
    wk->MsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_connect_dat, HEAPID_FIELD );
    wk->MsgString =  STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    wk->MsgString2 =  STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    wk->TalkString =  STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    wk->TalkStringEx =  STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    wk->pZKN = PokeRegulationInit(HEAPID_WORLD);
    return wk;
}

//-----------------------------------------------------------------------------
/**
 * @brief	���M�����[�V�������j���[�N��
 * @param	FIELDSYS_WORK
 * @retval	none
 */
//-----------------------------------------------------------------------------

void EventCmd_RegulationListCall(GMEVENT_CONTROL * event, u16* work)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
    _EV_REGULATION_LIST_WORK *wk = _createRegulationWork(fsys);
    wk->retWk = work;
    FieldEvent_Call(event, GMEVENT_RegulationList, wk);
}

