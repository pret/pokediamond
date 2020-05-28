//=============================================================================
/**
 * @file	msgboy.c
 * @brief	メッセージ登録少年イベント処理
 * @author	taya
 * @date	2006.05.27
 */
//=============================================================================
#include "common.h"
#include "gflib\strbuf.h"
#include "gflib\bg_system.h"
#include "system\wipe.h"
#include "system\msgdata.h"
#include "system\wordset.h"
#include "system\window.h"
#include "system\snd_tool.h"
#include "system\bmp_cursor.h"
#include "system\fontproc.h"
#include "system\pms_data.h"
#include "savedata\b_tower.h"
#include "application\pms_input.h"
#include "msgdata\msg.naix"
#include "msgdata\msg_msgboy.h"

#include "field\field.h"
#include "fieldsys.h"
#include "field_event.h"
#include "fieldmap.h"
#include "talk_msg.h"
#include "fld_bmp.h"

#include "msgboy.h"


//----------------------------------------------
/**
 *	定数
 */
//----------------------------------------------
enum {
	PRINT_BUFFER_SIZE = 400,

	MENUWIN_CHARPOS = 1,
	MENUWIN_WIDTH = 14,
	MENUWIN_HEIGHT = 10,
	MENUWIN_OX = 32 - (MENUWIN_WIDTH+1),
	MENUWIN_OY = 24 - (MENUWIN_HEIGHT+1),
	MENUWIN_CHARSIZE = MENUWIN_WIDTH*MENUWIN_HEIGHT,
	MENUWIN_PALPOS = FLD_SYSFONT_PAL,

	YESNOWIN_WIDTH = 6,
	YESNOWIN_HEIGHT = 4,
	YESNOWIN_OX = 32 - (YESNOWIN_WIDTH+1),
	YESNOWIN_OY = 24 - (YESNOWIN_HEIGHT+1+6),
	YESNOWIN_CHARPOS = MENUWIN_CHARPOS + MENUWIN_CHARSIZE,
	YESNOWIN_CHARSIZE = YESNOWIN_WIDTH * YESNOWIN_HEIGHT,
	YESNOWIN_PALPOS = FLD_SYSFONT_PAL,

	MENUWIN_FRAME_CHARPOS = YESNOWIN_CHARPOS + YESNOWIN_CHARSIZE,
	MENUWIN_FRAME_PALPOS = FLD_MENUFRAME_PAL,
	MENUWIN_CLEAR_COLOR = 15,

	MENU_STR_HEIGHT = 16,
	MENU_STR_PRINT_OX = 12,

};


enum {
	MAINMENU_READY = 0,
	MAINMENU_WON,
	MAINMENU_LOST,
	MAINMENU_TOP,
	MAINMENU_CANCEL,
	MAINMENU_MAXELEMS,

	YESNOMENU_YES = 0,
	YESNOMENU_NO,
	YESNOMENU_MAXELEMS,

	MENU_RESULT_WAIT = -1,
};


//----------------------------------------------
/**
 *	イベントワーク
 */
//----------------------------------------------
typedef struct {

	FIELDSYS_WORK*		fsys;
	STRBUF*				tmpBuf;
	STRBUF*				printBuf;
	WORDSET*			wordSet;
	MSGDATA_MANAGER*	msgMan;
	BMPCURSOR*			bmpCursor;
	GF_BGL_BMPWIN		talkWin;
	GF_BGL_BMPWIN		mainMenuWin;
	GF_BGL_BMPWIN		yesnoMenuWin;
	PMS_DATA			pms;
	PMSI_PARAM*			pmsiParam;

	int             seq;
	int             talkmsg_index;
	int             menu_pos;
	int             menu_maxpos;
	int             menu_result;
	GF_BGL_BMPWIN*  menuWin;

}MSGBOY_EVENT_WORK;


//==============================================================
// Prototype
//==============================================================
static void delete_work( MSGBOY_EVENT_WORK* wk );
static void delete_bmpwin( MSGBOY_EVENT_WORK* wk );
static BOOL GMEVENT_MsgBoy( GMEVENT_CONTROL* event );
static void print_talkmsg( MSGBOY_EVENT_WORK* wk, int strID, BOOL expandFlag );
static BOOL wait_talkmsg( MSGBOY_EVENT_WORK* wk );
static void erase_talkmsg( MSGBOY_EVENT_WORK* wk );
static void start_mainmenu( MSGBOY_EVENT_WORK* wk );
static void erase_mainmenu( MSGBOY_EVENT_WORK* wk );
static void start_yesnomenu( MSGBOY_EVENT_WORK* wk );
static void erase_yesnomenu( MSGBOY_EVENT_WORK* wk );
static int ctrl_menu( MSGBOY_EVENT_WORK* wk );




//------------------------------------------------------------------
/**
 * イベント開始
 *
 * @param   fsys		フィールドシステムワークポインタ
 *
 */
//------------------------------------------------------------------
void MSGBOY_EventStart( GMEVENT_CONTROL* event )
{
	FIELDSYS_WORK* fsys = FieldEvent_GetFieldSysWork( event );
	MSGBOY_EVENT_WORK* wk = sys_AllocMemory( HEAPID_EVENT, sizeof(MSGBOY_EVENT_WORK) );


	wk->fsys = fsys;
	wk->tmpBuf = STRBUF_Create( PRINT_BUFFER_SIZE, HEAPID_EVENT );
	wk->printBuf = STRBUF_Create( PRINT_BUFFER_SIZE, HEAPID_EVENT );
	wk->wordSet = WORDSET_Create( HEAPID_EVENT );
	wk->msgMan = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_msgboy_dat, HEAPID_EVENT );
	wk->bmpCursor = BMPCURSOR_Create( HEAPID_EVENT );
	wk->pmsiParam = PMSI_PARAM_Create( PMSI_MODE_SENTENCE, PMSI_GUIDANCE_DEFAULT,
		wk->fsys->savedata, HEAPID_EVENT );

	PMSI_PARAM_SetNotEditEgnore( wk->pmsiParam );

	GF_BGL_BmpWinInit( &(wk->talkWin) );
	GF_BGL_BmpWinInit( &(wk->mainMenuWin) );
	GF_BGL_BmpWinInit( &(wk->yesnoMenuWin) );

	wk->seq = 0;

	FieldEvent_Call( event, GMEVENT_MsgBoy, wk );
}


//------------------------------------------------------------------
/**
 * ワーク破棄
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void delete_work( MSGBOY_EVENT_WORK* wk )
{
	PMSI_PARAM_Delete( wk->pmsiParam );
	BMPCURSOR_Delete( wk->bmpCursor );
	STRBUF_Delete( wk->tmpBuf );
	STRBUF_Delete( wk->printBuf );
	WORDSET_Delete( wk->wordSet );
	MSGMAN_Delete( wk->msgMan );

	delete_bmpwin( wk );
	sys_FreeMemoryEz( wk );
}

//------------------------------------------------------------------
/**
 * BitmapWindow破棄
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void delete_bmpwin( MSGBOY_EVENT_WORK* wk )
{
	if( GF_BGL_BmpWinAddCheck(&(wk->talkWin)) )
	{
		GF_BGL_BmpWinDel(&wk->talkWin);
		GF_BGL_BmpWinInit(&(wk->talkWin));
	}
	if( GF_BGL_BmpWinAddCheck(&(wk->mainMenuWin)) )
	{
		GF_BGL_BmpWinDel(&wk->mainMenuWin);
		GF_BGL_BmpWinInit(&(wk->mainMenuWin));
	}
	if( GF_BGL_BmpWinAddCheck(&(wk->yesnoMenuWin)) )
	{
		GF_BGL_BmpWinDel(&wk->yesnoMenuWin);
		GF_BGL_BmpWinInit(&(wk->yesnoMenuWin));
	}
}


//------------------------------------------------------------------
/**
 * イベント関数本体
 *
 * @param   event		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL GMEVENT_MsgBoy( GMEVENT_CONTROL* event )
{
	enum {
		SEQ_SETUP_FIRST_MSG,
		SEQ_WAIT_FIRST_MSG,
		SEQ_CTRL_MAINMENU,
		SEQ_START_INFO_MSG,
		SEQ_WAIT_INFO_MSG,
		SEQ_WAIT_FIELD_FADEOUT,
		SEQ_WAIT_PMS_INPUT,
		SEQ_WAIT_RETURN_FIELD,
		SEQ_WAIT_FADEIN_FIELD,
		SEQ_WAIT_NEXTINPUT_MSG,
		SEQ_CTRL_YESNO_MENU,
		SEQ_PRINT_CANCEL_MSG,
		SEQ_WAIT_CANCEL_MSG,
		SEQ_QUIT,
	};

	MSGBOY_EVENT_WORK* wk = FieldEvent_GetSpecialWork(event);

	switch( wk->seq ){
	case SEQ_SETUP_FIRST_MSG:
		print_talkmsg( wk, msgboy_str_01, FALSE );
		wk->seq = SEQ_WAIT_FIRST_MSG;
		break;

	case SEQ_WAIT_FIRST_MSG:
		if( wait_talkmsg( wk ) )
		{
			erase_talkmsg( wk );
			start_mainmenu( wk );
			wk->seq = SEQ_CTRL_MAINMENU;
		}
		break;

	case SEQ_CTRL_MAINMENU:
		wk->menu_result = ctrl_menu(wk);
		if( wk->menu_result != MENU_RESULT_WAIT )
		{
			erase_mainmenu( wk );
			switch( wk->menu_result ){
			case MAINMENU_READY:
				PMSDAT_Copy( &(wk->pms), TowerPlayerMsg_Get(wk->fsys->savedata, BTWR_MSG_PLAYER_READY) );
				wk->seq = SEQ_START_INFO_MSG;
				break;
			case MAINMENU_WON:
				PMSDAT_Copy( &(wk->pms), TowerPlayerMsg_Get(wk->fsys->savedata, BTWR_MSG_PLAYER_WIN) );
				wk->seq = SEQ_START_INFO_MSG;
				break;
			case MAINMENU_LOST:
				PMSDAT_Copy( &(wk->pms), TowerPlayerMsg_Get(wk->fsys->savedata, BTWR_MSG_PLAYER_LOSE) );
				wk->seq = SEQ_START_INFO_MSG;
				break;
			case MAINMENU_TOP:
				PMSDAT_Copy( &(wk->pms), TowerPlayerMsg_Get(wk->fsys->savedata, BTWR_MSG_LEADER) );
				wk->seq = SEQ_START_INFO_MSG;
				break;
			case MAINMENU_CANCEL:
				wk->seq = SEQ_PRINT_CANCEL_MSG;
				break;
			}
		}
		break;

	case SEQ_START_INFO_MSG:
		print_talkmsg( wk, msgboy_str_02 + wk->menu_result, FALSE);
		wk->seq = SEQ_WAIT_INFO_MSG;
		break;

	case SEQ_WAIT_INFO_MSG:
		if( wait_talkmsg( wk ) )
		{
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );
			wk->seq = SEQ_WAIT_FIELD_FADEOUT;
		}
		break;

	case SEQ_WAIT_FIELD_FADEOUT:
		if( WIPE_SYS_EndCheck() )
		{
			PMSI_PARAM_SetInitializeDataSentence( wk->pmsiParam, &(wk->pms) );
			PMSI_PARAM_SetReuseState( wk->pmsiParam );
			delete_bmpwin( wk );
			FieldProc_SetPmsInput( wk->fsys, wk->pmsiParam );
			wk->seq = SEQ_WAIT_PMS_INPUT;
		}
		break;

	case SEQ_WAIT_PMS_INPUT:
		if(FieldEvent_Cmd_WaitSubProcEnd(wk->fsys) == FALSE)
		{
			FieldEvent_Cmd_SetMapProc(wk->fsys);
			wk->seq = SEQ_WAIT_RETURN_FIELD;
		}
		break;

	case SEQ_WAIT_RETURN_FIELD:
		if(FieldEvent_Cmd_WaitMapProcStart(wk->fsys))
		{
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
			wk->seq = SEQ_WAIT_FADEIN_FIELD;
		}
		break;

	case SEQ_WAIT_FADEIN_FIELD:
		if( WIPE_SYS_EndCheck() )
		{
			if( PMSI_PARAM_CheckCanceled(wk->pmsiParam) )
			{
				OS_TPrintf("キャンセルされた\n");
				wk->seq = SEQ_PRINT_CANCEL_MSG;
			}
			else
			{
				OS_TPrintf("キャンセルされなかった\n");
				PMSI_PARAM_GetInputDataSentence( wk->pmsiParam, &(wk->pms) );
				TowerPlayerMsg_Set( wk->fsys->savedata, wk->menu_result, &(wk->pms) );
				print_talkmsg( wk, msgboy_str_07, FALSE );
				wk->seq = SEQ_WAIT_NEXTINPUT_MSG;
			}
		}
		break;

	case SEQ_WAIT_NEXTINPUT_MSG:
		if( wait_talkmsg( wk ) )
		{
			start_yesnomenu( wk );
			wk->seq = SEQ_CTRL_YESNO_MENU;
		}
		break;

	case SEQ_CTRL_YESNO_MENU:
		wk->menu_result = ctrl_menu(wk);
		if( wk->menu_result != MENU_RESULT_WAIT )
		{
			switch( wk->menu_result ){
			case YESNOMENU_YES:
				erase_yesnomenu( wk );
				erase_talkmsg( wk );
				start_mainmenu( wk );
				wk->seq = SEQ_CTRL_MAINMENU;
				break;

			case YESNOMENU_NO:
			default:
				{
					PMS_WORD word = PMSDAT_GetWordNumber( &wk->pms, 0 );
					erase_yesnomenu( wk );

					if( word != PMS_WORD_NULL )
					{
						WORDSET_RegisterPMSWord( wk->wordSet, 0, word );
						print_talkmsg( wk, msgboy_str_09, TRUE );
					}
					else
					{
						print_talkmsg( wk, msgboy_str_08, FALSE );
					}
					wk->seq = SEQ_WAIT_CANCEL_MSG;
				}
			}
		}
		break;

	case SEQ_PRINT_CANCEL_MSG:
		print_talkmsg( wk, msgboy_str_06, FALSE );
		wk->seq = SEQ_WAIT_CANCEL_MSG;
		break;

	case SEQ_WAIT_CANCEL_MSG:
		if( wait_talkmsg( wk ) )
		{
			if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B|PAD_PLUS_KEY_MASK) )
			{
				erase_talkmsg( wk );
				wk->seq = SEQ_QUIT;
			}
		}
		break;

	case SEQ_QUIT:
		delete_work( wk );
		return TRUE;

	}

	return FALSE;
}


//------------------------------------------------------------------
/**
 * 会話文章出力
 *
 * @param   wk		
 * @param   strID		
 * @param   expandFlag		
 *
 */
//------------------------------------------------------------------
static void print_talkmsg( MSGBOY_EVENT_WORK* wk, int strID, BOOL expandFlag )
{
	GF_BGL_BMPWIN* win = &(wk->talkWin);

	if( expandFlag )
	{
		MSGMAN_GetString( wk->msgMan, strID, wk->tmpBuf );
		WORDSET_ExpandStr( wk->wordSet, wk->printBuf, wk->tmpBuf );
	}
	else
	{
		MSGMAN_GetString( wk->msgMan, strID, wk->printBuf );
	}

	if( GF_BGL_BmpWinAddCheck(win) == FALSE )
	{
	    FldTalkBmpAdd( wk->fsys->bgl, win, FLD_MBGFRM_FONT );
		FieldTalkWinPut( win, SaveData_GetConfig(wk->fsys->savedata) );
	}
	else
	{
		FieldTalkWinClear( win );
		BmpTalkWinWrite( win, WINDOW_TRANS_ON, TALK_WIN_CGX_NUM, TALK_WIN_PAL );
	}

	wk->talkmsg_index = FieldTalkMsgStart( win, wk->printBuf, SaveData_GetConfig(wk->fsys->savedata), TRUE );
}
//------------------------------------------------------------------
/**
 * 会話文章出力の終了待ち
 *
 * @param   wk		
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
static BOOL wait_talkmsg( MSGBOY_EVENT_WORK* wk )
{
	return FldTalkMsgEndCheck( wk->talkmsg_index );
}
//------------------------------------------------------------------
/**
 * 会話文章ウィンドウの表示オフ
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void erase_talkmsg( MSGBOY_EVENT_WORK* wk )
{
	GF_BGL_BMPWIN* win = &(wk->talkWin);

	if( GF_BGL_BmpWinAddCheck( win ) )
	{
		BmpTalkWinClear( win, WINDOW_TRANS_ON );
	}
}




//------------------------------------------------------------------
/**
 * メインメニュー表示・選択開始
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void start_mainmenu( MSGBOY_EVENT_WORK* wk )
{
	GF_BGL_BMPWIN* win = &(wk->mainMenuWin);

	if( GF_BGL_BmpWinAddCheck( win ) == FALSE )
	{
		int i;

		MenuWinGraphicSet( wk->fsys->bgl, FLD_MBGFRM_FONT,
				MENUWIN_FRAME_CHARPOS, MENUWIN_FRAME_PALPOS, MENU_TYPE_SYSTEM, HEAPID_EVENT );

		GF_BGL_BmpWinAdd( wk->fsys->bgl, win, FLD_MBGFRM_FONT,
			MENUWIN_OX, MENUWIN_OY, MENUWIN_WIDTH, MENUWIN_HEIGHT, 
			MENUWIN_PALPOS, MENUWIN_CHARPOS );

		GF_BGL_BmpWinDataFill(win, MENUWIN_CLEAR_COLOR);

		for(i=0; i<MAINMENU_MAXELEMS; i++)
		{
			MSGMAN_GetString( wk->msgMan, msgboy_menu_01+i, wk->printBuf );
			GF_STR_PrintSimple( win, FONT_SYSTEM, wk->printBuf,
				MENU_STR_PRINT_OX, i*MENU_STR_HEIGHT, MSG_NO_PUT, NULL );
		}

		BMPCURSOR_Print( wk->bmpCursor, win, 0, 0 );
	}

	wk->menuWin = win;
	wk->menu_pos = 0;
	wk->menu_maxpos = MAINMENU_MAXELEMS;
	BmpMenuWinWrite( win, WINDOW_TRANS_ON, MENUWIN_FRAME_CHARPOS, MENUWIN_FRAME_PALPOS );
}
//------------------------------------------------------------------
/**
 * メインメニュー表示消去
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void erase_mainmenu( MSGBOY_EVENT_WORK* wk )
{
	GF_BGL_BMPWIN* win = &(wk->mainMenuWin);
	BmpMenuWinClear( win, TRUE );
}

//------------------------------------------------------------------
/**
 * 「はい／いいえ」メニュー表示・選択開始
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void start_yesnomenu( MSGBOY_EVENT_WORK* wk )
{
	GF_BGL_BMPWIN* win = &(wk->yesnoMenuWin);

	if( GF_BGL_BmpWinAddCheck( win ) == FALSE )
	{
		int i;

		MenuWinGraphicSet( wk->fsys->bgl, FLD_MBGFRM_FONT,
				MENUWIN_FRAME_CHARPOS, MENUWIN_FRAME_PALPOS, MENU_TYPE_SYSTEM, HEAPID_EVENT );

		GF_BGL_BmpWinAdd( wk->fsys->bgl, win, FLD_MBGFRM_FONT,
			YESNOWIN_OX, YESNOWIN_OY, YESNOWIN_WIDTH, YESNOWIN_HEIGHT, 
			YESNOWIN_PALPOS, YESNOWIN_CHARPOS );

		GF_BGL_BmpWinDataFill(win, MENUWIN_CLEAR_COLOR);

		for(i=0; i<YESNOMENU_MAXELEMS; i++)
		{
			MSGMAN_GetString( wk->msgMan, i+msgboy_menu_06, wk->printBuf );
			GF_STR_PrintSimple( win, FONT_SYSTEM, wk->printBuf,
				MENU_STR_PRINT_OX, i*MENU_STR_HEIGHT, MSG_NO_PUT, NULL );
		}

		BMPCURSOR_Print( wk->bmpCursor, win, 0, 0 );
	}

	wk->menuWin = win;
	wk->menu_pos = 0;
	wk->menu_maxpos = YESNOMENU_MAXELEMS;
	BmpMenuWinWrite( win, WINDOW_TRANS_ON, MENUWIN_FRAME_CHARPOS, MENUWIN_FRAME_PALPOS );
}
//------------------------------------------------------------------
/**
 * 「はい／いいえ」メニュー表示消去
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void erase_yesnomenu( MSGBOY_EVENT_WORK* wk )
{
	GF_BGL_BMPWIN* win = &(wk->yesnoMenuWin);
	BmpMenuWinClear( win, TRUE );
}




//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int ctrl_menu( MSGBOY_EVENT_WORK* wk )
{
	do
	{
		if( sys.trg & PAD_KEY_UP )
		{
			wk->menu_pos--;
			if( wk->menu_pos < 0 )
			{
				if( wk->menu_maxpos > 2 )
				{
					wk->menu_pos = wk->menu_maxpos - 1;
				}
				else
				{
					wk->menu_pos = 0;
				}
			}
			break;
		}
		if( sys.trg & PAD_KEY_DOWN )
		{
			wk->menu_pos++;
			if( wk->menu_pos >= wk->menu_maxpos )
			{
				if( wk->menu_maxpos > 2 )
				{
					wk->menu_pos = 0;
				}
				else
				{
					wk->menu_pos = wk->menu_maxpos - 1;
				}
			}
			break;
		}
		if( sys.trg & PAD_BUTTON_A )
		{
			Snd_SePlay( SEQ_SE_DP_SELECT );
			return wk->menu_pos;
		}
		if( sys.trg & PAD_BUTTON_B )
		{
			Snd_SePlay( SEQ_SE_DP_SELECT );
			return wk->menu_maxpos - 1;
		}

		return MENU_RESULT_WAIT;

	}while(0);

	{
		GF_BGL_BmpWinFill( wk->menuWin, MENUWIN_CLEAR_COLOR, 0, 0, MENU_STR_PRINT_OX, wk->menuWin->sizy*8 );
		BMPCURSOR_Print( wk->bmpCursor, wk->menuWin, 0, wk->menu_pos*MENU_STR_HEIGHT );
		GF_BGL_BmpWinCgxOn( wk->menuWin );
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}

	return MENU_RESULT_WAIT;

}

