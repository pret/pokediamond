//============================================================================================
/**
 * @file	wifi_p2pmatch.c
 * @bfief	WIFIP2P�}�b�`���O���
 * @author	k.ohno
 * @date	06.04.07
 */
//============================================================================================

#include "common.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/pm_str.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_wifi_lobby.h"
#include "msgdata/msg_wifi_system.h"
#include "application\namein.h"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/window.h"
#include "gflib/msg_print.h"
#include "gflib/touchpanel.h"
#include "poketool/monsno.h"
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "application/wifi_p2pmatch.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "msgdata/msg_opening_name.h"
#include "itemtool/itemsym.h"
#include "system/brightness.h"
#include "system/pmfprint.h"

#include "wifi/dwc_rap.h"
#include "wifi_p2pmatch_local.h"
#include "wifi_p2pmatch_se.h"
#include "wifi/dwc_rapfriend.h"

#include "communication/communication.h"
#include "communication/comm_state.h"
#include "msgdata/msg_ev_win.h"
#include "savedata/zukanwork.h"
#include "savedata/wifihistory.h"
#include "savedata/config.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "system/snd_tool.h"  //sndTOOL

#include "wifip2pmatch.naix"			// �O���t�B�b�N�A�[�J�C�u��`

#include "include/system/pm_debug_wifi.h"

// WIFI�@�ΐ�AUTOӰ�ރf�o�b�N
#ifdef _WIFI_DEBUG_TUUSHIN
extern WIFI_DEBUG_BATTLE_WK WIFI_DEBUG_BATTLE_Work;
#endif	//_WIFI_DEBUG_TUUSHIN

///	�a�f�p���b�g��` 2005/09/15
//
//	0 �` 5  : �t�B�[���h�}�b�v�a�f�p
//  6       : �V��
//  7       : �n���E�C���h�E
//  8       : �ŔE�C���h�E�i�}�b�v�A�W���Ȃǁj
//  9       : �ŔE�C���h�E�i�g�A�t�H���g�j
//  10      : ���b�Z�[�W�E�C���h�E
//  11      : ���j���[�E�C���h�E
//  12      : ���b�Z�[�W�t�H���g
//  13      : �V�X�e���t�H���g
//	14		: ���g�p�i���[�J���C�Y�p�j
//	15		: �f�o�b�O�p�i���i�łł͖��g�p�j
#define FLD_WEATHER_PAL      (  6 )			//  �V��
#define FLD_PLACENAME_PAL    (  7 )         //  �n���E�C���h�E
#define FLD_BOARD1FRAME_PAL  (  8 )         //  �ŔE�C���h�E�i�}�b�v�A�W���Ȃǁj
#define FLD_BOARD2FRAME_PAL  (  9 )         //  �ŔE�C���h�E�i�g�A�t�H���g�j
#define FLD_MESFRAME_PAL     ( 10 )         //  ���b�Z�[�W�E�C���h�E
#define FLD_MENUFRAME_PAL    ( 11 )         //  ���j���[�E�C���h�E
#define FLD_MESFONT_PAL      ( 12 )         //  ���b�Z�[�W�t�H���g
#define FLD_SYSFONT_PAL	     ( 13 )         //  �V�X�e���t�H���g
#define FLD_LOCALIZE_PAL     ( 14 )         //	���g�p�i���[�J���C�Y�p�j
#define FLD_DEBUG_PAL        ( 15 )         //	�f�o�b�O�p�i���i�łł͖��g�p�j

/*********************************************************************************************
	���C����ʂ�CGX����U��		2006/01/12

		�E�B���h�E�g	�F	409 - 511
			��b�A���j���[�A�n���A�Ŕ�

		BMP�E�B���h�E�P	�F	297 - 408
			��b�i�ő�j�A�ŔA�c��{�[����

		BMP�E�B���h�E�Q	�F	55 - 296
			���j���[�i�ő�j�A�͂�/�������A�n��

*********************************************************************************************/

/*********************************************************************************************
	�E�B���h�E�g
*********************************************************************************************/
// ��b�E�B���h�E�L����
#define	TALK_WIN_CGX_SIZE	( 18+12 )
#define	TALK_WIN_CGX_NUM	( 512 - TALK_WIN_CGX_SIZE )
#define	TALK_WIN_PAL		( 10 )

// ���j���[�E�B���h�E�L����
#define	MENU_WIN_CGX_SIZE	( 9 )
#define	MENU_WIN_CGX_NUM	( TALK_WIN_CGX_NUM - MENU_WIN_CGX_SIZE )
#define	MENU_WIN_PAL		( 11 )

// �n���E�B���h�E�L����
#define	PLACE_WIN_CGX_SIZE	( 10 )
#define	PLACE_WIN_CGX_NUM	( MENU_WIN_CGX_NUM - PLACE_WIN_CGX_SIZE )
#define	PLACE_WIN_PAL		( 7 )

// �ŔE�B���h�E�L����
#define	BOARD_WIN_CGX_SIZE	( 18+12 + 24 )
#define	BOARD_WIN_CGX_NUM	( PLACE_WIN_CGX_NUM - BOARD_WIN_CGX_SIZE )
#define	BOARD_WIN_PAL		( FLD_BOARD2FRAME_PAL )

/*********************************************************************************************
	BMP�E�B���h�E
*********************************************************************************************/
// ��b�E�B���h�E�i���C���j
#define	FLD_MSG_WIN_PX		( 2 )
#define	FLD_MSG_WIN_PY		( 19 )
#define	FLD_MSG_WIN_SX		( 27 )
#define	FLD_MSG_WIN_SY		( 4 )
#define	FLD_MSG_WIN_PAL		( FLD_MESFONT_PAL )
#define	FLD_MSG_WIN_CGX		( BOARD_WIN_CGX_NUM - ( FLD_MSG_WIN_SX * FLD_MSG_WIN_SY ) )

// �ŔE�B���h�E�i���C���j�i��b�Ɠ����ʒu�i��b��菬�����j�j
#define	FLD_BOARD_WIN_PX	( 9 )
#define	FLD_BOARD_WIN_PY	( 19 )
#define	FLD_BOARD_WIN_SX	( 20 )
#define	FLD_BOARD_WIN_SY	( 4 )
#define	FLD_BOARD_WIN_PAL	( FLD_BOARD2FRAME_PAL )
#define	FLD_BOARD_WIN_CGX	( FLD_MSG_WIN_CGX )

// �c��{�[�����i��b�Ɠ����ʒu�i��b��菬�����j�j
#define	FLD_BALL_WIN_PX		( 1 )
#define	FLD_BALL_WIN_PY		( 1 )
#define	FLD_BALL_WIN_SX		( 12 )
#define	FLD_BALL_WIN_SY		( 4 )
#define	FLD_BALL_WIN_PAL	( FLD_SYSFONT_PAL )
#define	FLD_BALL_WIN_CGX	( FLD_MSG_WIN_CGX )

// ���j���[�E�B���h�E�i���C���j
#define	FLD_MENU_WIN_PX		( 20 )
#define	FLD_MENU_WIN_PY		( 1 )
#define	FLD_MENU_WIN_SX		( 11 )
#define	FLD_MENU_WIN_SY		( 22 )
#define	FLD_MENU_WIN_PAL	( FLD_SYSFONT_PAL )
#define	FLD_MENU_WIN_CGX	( FLD_MSG_WIN_CGX - ( FLD_MENU_WIN_SX * FLD_MENU_WIN_SY ) )

// �͂�/�������E�B���h�E�i���C���j�i���j���[�Ɠ����ʒu�i���j���[��菬�����j�j
#define	FLD_YESNO_WIN_PX	( 25 )
#define	FLD_YESNO_WIN_PY	( 13 )
#define	FLD_YESNO_WIN_SX	( 6 )
#define	FLD_YESNO_WIN_SY	( 4 )
#define	FLD_YESNO_WIN_PAL	( FLD_SYSFONT_PAL )
#define	FLD_YESNO_WIN_CGX	( FLD_MSG_WIN_CGX - ( FLD_YESNO_WIN_SX * FLD_YESNO_WIN_SY ) )

// �n���E�B���h�E�i���j���[�Ɠ����ʒu�i���j���[��菬�����j�j
#define FLD_PLACE_WIN_PX	( 0 )
#define FLD_PLACE_WIN_PY	( 0 )
#define	FLD_PLACE_WIN_SX	( 32 )
#define	FLD_PLACE_WIN_SY	( 3 )
#define	FLD_PLACE_WIN_CGX	( FLD_MSG_WIN_CGX - ( FLD_PLACE_WIN_SX * FLD_PLACE_WIN_SY ) )



// ���b�Z�[�W�E�B���h�E�i�T�u�j
#define	FLD_MSG_WIN_S_PX	( 2  )
#define	FLD_MSG_WIN_S_PY	( 19 )
#define	FLD_MSG_WIN_S_PAL	( FLD_MESFONT_PAL )
#define	FLD_MSG_WIN_S_CGX	( MENU_WIN_CGX_NUM - ( FLD_MSG_WIN_SX * FLD_MSG_WIN_SY ) )

// �ŔE�B���h�E�i�T�u�j
#define	FLD_BOARD_WIN_S_PX	( 9 )
#define	FLD_BOARD_WIN_S_PY	( 19 )
#define	FLD_BOARD_WIN_S_SX	( 21 )
#define	FLD_BOARD_WIN_S_SY	( 4 )
#define	FLD_BOARD_WIN_S_PAL	( FLD_BOARD2FRAME_PAL )
#define	FLD_BOARD_WIN_S_CGX	( FLD_MSG_WIN_S_CGX )

// ���j���[�E�B���h�E�i�T�u�j
#define	FLD_MENU_WIN_S_PX	( 25 )
#define	FLD_MENU_WIN_S_PY	( 1 )
#define	FLD_MENU_WIN_S_SX	( 6 )
#define	FLD_MENU_WIN_S_SY	( 16 )
#define	FLD_MENU_WIN_S_PAL	( FLD_SYSFONT_PAL )
#define	FLD_MENU_WIN_S_CGX	( MENU_WIN_CGX_NUM - ( FLD_MENU_WIN_SX * FLD_MENU_WIN_SY ) )



///	�r�b�g�}�b�v�]���֐��p��`
//------------------------------------------------------------------
#define	FBMP_TRANS_OFF	(0)
#define	FBMP_TRANS_ON	(1)
///	�����\���]���֐��p��`
//------------------------------------------------------------------
#define	FBMPMSG_WAITON_SKIPOFF	(0)
#define	FBMPMSG_WAITON_SKIPON	(1)
#define	FBMPMSG_WAITOFF			(2)

//-------------------------------------------------------------------------
///	�����\���F��`(default)	-> gflib/fntsys.h�ֈړ�
//------------------------------------------------------------------

#define WINCLR_COL(col)	(((col)<<4)|(col))

//-------------------------------------------------------------------------
///	�����\���X�s�[�h��`(default)
//------------------------------------------------------------------
#define	FBMP_MSG_SPEED_SLOW		(8)
#define	FBMP_MSG_SPEED_NORMAL	(4)
#define	FBMP_MSG_SPEED_FAST		(1)



//============================================================================================
//	�萔��`
//============================================================================================
enum {
    SEQ_IN = 0,
    SEQ_MAIN,
    SEQ_OUT,
};

enum {
    _MENU_LIST,
    _MENU_INPUT,
    _MENU_MYCODE,
    _MENU_EXIT,
};

typedef enum {
    _CLACT_UP_CUR,
    _CLACT_DOWN_CUR,
    _CLACT_LINE_CUR,
    _CLACT_VCT_STOP,
    _CLACT_VCT_MOVE,
} _OAM_ANIM_E;

typedef struct{  // �X�N���[���pRECT�\����
    u8 lt_x;
    u8 lt_y;
    u8 rb_x;
    u8 rb_y;
} _SCR_RECT;

#define _PRINTTASK_MAX (8)
#define _TIMING_GAME_CHECK  (13)// �Ȃ���������
#define _TIMING_GAME_CHECK2  (14)// �Ȃ���������
#define _TIMING_GAME_START  (15)// �^�C�~���O�����낦��
#define _TIMING_GAME_START2  (18)// �^�C�~���O�����낦��
#define _TIMING_BATTLE_END  (16)// �^�C�~���O�����낦��

#define _RECONECTING_WAIT_TIME (20)  //�Đڑ�����

// ��b�E�B���h�E�L����
#define	_CGX_BOTTOM	( 512 )


// ��b�E�B���h�E
#define COMM_MESFRAME_PAL     ( 10 )         //  ���b�Z�[�W�E�C���h�E
#define COMM_MENUFRAME_PAL    ( 11 )         //  ���j���[�E�C���h�E
#define COMM_MESFONT_PAL      ( 12 )         //  ���b�Z�[�W�t�H���g
#define COMM_SYSFONT_PAL	  ( 13 )         //  �V�X�e���t�H���g
#define	COMM_TALK_WIN_CGX_SIZE	( 18+12 )
#define	COMM_TALK_WIN_CGX_NUM	( 512 - COMM_TALK_WIN_CGX_SIZE)
#define	COMM_MSG_WIN_PX		( 2 )
#define	COMM_MSG_WIN_PY		( 19 )
#define	COMM_MSG_WIN_SX		( 27 )
#define	COMM_MSG_WIN_SY		( 4 )
#define	COMM_MSG_WIN_PAL		( COMM_MESFONT_PAL )
#define	COMM_MSG_WIN_CGX		( (COMM_TALK_WIN_CGX_NUM - 73) - ( COMM_MSG_WIN_SX * COMM_MSG_WIN_SY ) )

#define	COMM_SYS_WIN_PX		( 4 )
#define	COMM_SYS_WIN_PY		( 4 )
#define	COMM_SYS_WIN_SX		( 23 )
#define	COMM_SYS_WIN_SY		( 16 )
#define	COMM_SYS_WIN_PAL		( COMM_MESFONT_PAL )
#define	COMM_SYS_WIN_CGX		( MENU_WIN_CGX_NUM - ( COMM_SYS_WIN_SX * COMM_SYS_WIN_SY ) )


// ���C�����b�Z�[�W�L����
#define _NUKI_FONT_PALNO  (13)
#define	_COL_N_BLACK	( GF_PRINTCOLOR_MAKE( 1, 2, 0 ) )		// �t�H���g�J���[�F��
#define	_COL_N_WHITE	( GF_PRINTCOLOR_MAKE( 15, 14, 0 ) )		// �t�H���g�J���[�F��
#define	_COL_N_RED	    ( GF_PRINTCOLOR_MAKE( 3, 4, 0 ) )		// �t�H���g�J���[�F��
#define	_COL_N_BLUE	    ( GF_PRINTCOLOR_MAKE( 5, 6, 0 ) )		// �t�H���g�J���[�F��
#define	_COL_N_GRAY  	( GF_PRINTCOLOR_MAKE( 2, 14, 0 ) )		// �t�H���g�J���[�F�D

// ���O�\��BMP�i���ʁj
#define WIFIP2PMATCH_NAME_BMP_W	 ( 16 )
#define WIFIP2PMATCH_NAME_BMP_H	 (  2 )
#define WIFIP2PMATCH_NAME_BMP_SIZE (WIFIP2PMATCH_NAME_BMP_W * WIFIP2PMATCH_NAME_BMP_H)

// ��b�E�C���h�E�\���ʒu��`
#define WIFIP2PMATCH_TALK_X		(  2 )
#define WIFIP2PMATCH_TALK_Y		(  19 )

#define WIFIP2PMATCH_TITLE_X		(   3  )
#define WIFIP2PMATCH_TITLE_Y		(   1  )
#define WIFIP2PMATCH_TITLE_W		(  26  )
#define WIFIP2PMATCH_TITLE_H		(   2  )


#define WIFIP2PMATCH_MSG_WIN_OFFSET 		(1 + TALK_WIN_CGX_SIZ     + MENU_WIN_CGX_SIZ)
#define WIFIP2PMATCH_TITLE_WIN_OFFSET		( WIFIP2PMATCH_MSG_WIN_OFFSET   + FLD_MSG_WIN_SX*FLD_MSG_WIN_SY )
#define WIFIP2PMATCH_NAME_WIN_OFFSET		( WIFIP2PMATCH_TITLE_WIN_OFFSET + WIFIP2PMATCH_TITLE_W*WIFIP2PMATCH_TITLE_H )
#define WIFIP2PMATCH_YESNO_WIN_OFFSET		( WIFIP2PMATCH_NAME_WIN_OFFSET  + WIFIP2PMATCH_NAME_BMP_SIZE*5 )

#ifdef PM_DEBUG
static int _seqBackup;
#endif

//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

/*** �֐��v���g�^�C�v ***/
static void VBlankFunc( void * work );
static void VramBankSet(void);
static void BgInit( GF_BGL_INI * ini );
static void InitWork( WIFIP2PMATCH_WORK *wk );
static void FreeWork( WIFIP2PMATCH_WORK *wk );
static void BgExit( GF_BGL_INI * ini );
static void BgGraphicSet( WIFIP2PMATCH_WORK * wk );
static void char_pltt_manager_init(void);
static void InitCellActor(WIFIP2PMATCH_WORK *wk);
static void SetCellActor(WIFIP2PMATCH_WORK *wk);
static void BmpWinInit(WIFIP2PMATCH_WORK *wk, PROC* proc);
static void MainMenuMsgInit(WIFIP2PMATCH_WORK *wk);
static void SetCursor_Pos( CLACT_WORK_PTR act, int x, int y );
static void WindowSet(void);


static void BmpWinDelete( WIFIP2PMATCH_WORK *wk );
static void _systemMessagePrint( WIFIP2PMATCH_WORK *wk, int msgno );
static void WifiP2PMatchMessagePrint( WIFIP2PMATCH_WORK *wk, int msgno , BOOL bSystem);
static void EndMessageWindowOff( WIFIP2PMATCH_WORK *wk );
static void WifiP2PMatchDataSendRecv( WIFIP2PMATCH_WORK *wk );
static void SequenceChange_MesWait( WIFIP2PMATCH_WORK *wk, int next );
static void _myStatusChange(WIFIP2PMATCH_WORK *wk, int status);
static void _timeWaitIconDel(WIFIP2PMATCH_WORK *wk);
static void _friendNameExpand( WIFIP2PMATCH_WORK *wk, int friendNo);


// FuncTable����V�[�P���X�J�ڂŌĂ΂��֐�
static int WifiP2PMatch_MainInit( WIFIP2PMATCH_WORK *wk, int seq );
static int _normalConnectYesNo( WIFIP2PMATCH_WORK *wk, int seq );
static int _normalConnectWait( WIFIP2PMATCH_WORK *wk, int seq );
static int _differMachineInit( WIFIP2PMATCH_WORK *wk, int seq );
static int _differMachineNext( WIFIP2PMATCH_WORK *wk, int seq );
static int _differMachineOneMore( WIFIP2PMATCH_WORK *wk, int seq );
static int _firstYesNo( WIFIP2PMATCH_WORK *wk, int seq );
static int _poweroffInit( WIFIP2PMATCH_WORK *wk, int seq );
static int _poweroffYesNo( WIFIP2PMATCH_WORK *wk, int seq );
static int _poweroffWait( WIFIP2PMATCH_WORK *wk, int seq );
static int _retryInit( WIFIP2PMATCH_WORK *wk, int seq );
static int _retryYesNo( WIFIP2PMATCH_WORK *wk, int seq );
static int _retryWait( WIFIP2PMATCH_WORK *wk, int seq );
static int _retry( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_ReConnectingWait( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_ConnectingInit( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_Connecting( WIFIP2PMATCH_WORK *wk, int seq );
static int _firstConnectEndMsg( WIFIP2PMATCH_WORK *wk, int seq );
static int _firstConnectEndMsgWait( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_FriendListInit( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_FriendList( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_VCTConnectInit2( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_VCTConnectInit( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_VCTConnectWait( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_VCTConnect( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_VCTConnectEndYesNo( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_VCTConnectEndWait( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_VCTDisconnect(WIFIP2PMATCH_WORK *wk, int seq);
static int WifiP2PMatch_BattleDisconnect(WIFIP2PMATCH_WORK *wk, int seq);
static int WifiP2PMatch_Disconnect(WIFIP2PMATCH_WORK *wk, int seq);
static int WifiP2PMatch_BattleConnectInit( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_BattleConnectWait( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_BattleConnect( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_MainReturn( WIFIP2PMATCH_WORK *wk, int seq );
static int _parentModeSelectMenuInit( WIFIP2PMATCH_WORK *wk, int seq );
static int _parentModeSelectMenuWait( WIFIP2PMATCH_WORK *wk, int seq );
static int _parentModeSubSelectMenuWait( WIFIP2PMATCH_WORK *wk, int seq );
static int _parentModeSelectRelInit( WIFIP2PMATCH_WORK *wk, int seq );
static int _parentModeSelectRelYesNo( WIFIP2PMATCH_WORK *wk, int seq );
static int _parentModeSelectRelWait( WIFIP2PMATCH_WORK *wk, int seq );
static int _childModeMatchMenuInit( WIFIP2PMATCH_WORK *wk, int seq );
static int _childModeMatchMenuWait( WIFIP2PMATCH_WORK *wk, int seq );
static int _childModeMatchMenuLoop( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_BCancelYesNoVCT( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_BCancelWaitVCT( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_BCancelYesNo( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_BCancelWait( WIFIP2PMATCH_WORK *wk, int seq );
static int _parentModeCallMenuInit( WIFIP2PMATCH_WORK *wk, int seq );
static int _parentModeCallMenuYesNo( WIFIP2PMATCH_WORK *wk, int seq );
static int _parentModeCallMenuSend( WIFIP2PMATCH_WORK *wk, int seq );
static int _parentModeCallMenuCheck( WIFIP2PMATCH_WORK *wk, int seq );
static int _parentModeCallMyStatusWait( WIFIP2PMATCH_WORK *wk, int seq );
static int _parentModeCallMenuWait( WIFIP2PMATCH_WORK *wk, int seq );
static int _personalDataInit( WIFIP2PMATCH_WORK *wk, int seq );
static int _personalDataWait( WIFIP2PMATCH_WORK *wk, int seq );
static int _personalDataEnd( WIFIP2PMATCH_WORK *wk, int seq );
static int _exitYesNo( WIFIP2PMATCH_WORK *wk, int seq );
static int _exitWait( WIFIP2PMATCH_WORK *wk, int seq );
static int _exitExiting( WIFIP2PMATCH_WORK *wk, int seq );
static int _exitEnd( WIFIP2PMATCH_WORK *wk, int seq );
static int _nextBattleYesNo( WIFIP2PMATCH_WORK *wk, int seq );
static int _nextBattleWait( WIFIP2PMATCH_WORK *wk, int seq );
static int _vchatNegoCheck( WIFIP2PMATCH_WORK *wk, int seq );
static int _vchatNegoWait( WIFIP2PMATCH_WORK *wk, int seq );

static BOOL _myVChatStatusToggle(WIFIP2PMATCH_WORK *wk);
static BOOL _myVChatStatusToggleOrg(WIFIP2PMATCH_WORK *wk);
static BOOL _myVChatStatusOrgSet(WIFIP2PMATCH_WORK *wk);
static int _vchatToggleWait( WIFIP2PMATCH_WORK *wk, int seq );


static int WifiP2PMatch_EndWait( WIFIP2PMATCH_WORK *wk, int seq );
static int WifiP2PMatch_CheckAndEnd( WIFIP2PMATCH_WORK *wk, int seq );

// ���R�[�h�R�[�i�[���C���V�[�P���X�p�֐��z���`
static int (*FuncTable[])(WIFIP2PMATCH_WORK *wk, int seq)={
    WifiP2PMatch_MainInit,	// WIFIP2PMATCH_MODE_INIT  = 0,
    _normalConnectYesNo,    // WIFIP2PMATCH_NORMALCONNECT_YESNO
    _normalConnectWait,     // WIFIP2PMATCH_NORMALCONNECT_WAIT
    _differMachineInit,     // WIFIP2PMATCH_DIFFER_MACHINE_INIT
    _differMachineNext,     // WIFIP2PMATCH_DIFFER_MACHINE_NEXT
    _differMachineOneMore,  // WIFIP2PMATCH_DIFFER_MACHINE_ONEMORE
    _firstYesNo,            //WIFIP2PMATCH_FIRST_YESNO
    _poweroffInit,      // WIFIP2PMATCH_POWEROFF_INIT
    _poweroffYesNo,     // WIFIP2PMATCH_POWEROFF_YESNO
    _poweroffWait,      // WIFIP2PMATCH_POWEROFF_WAIT
    _retryInit,        //WIFIP2PMATCH_RETRY_INIT
    _retryYesNo,        //WIFIP2PMATCH_RETRY_YESNO
    _retryWait,         //WIFIP2PMATCH_RETRY_WAIT
    _retry,             //WIFIP2PMATCH_RETRY
    WifiP2PMatch_ConnectingInit,        // WIFIP2PMATCH_CONNECTING_INIT,
    WifiP2PMatch_Connecting,            // WIFIP2PMATCH_CONNECTING,
    _firstConnectEndMsg,                 //WIFIP2PMATCH_FIRST_ENDMSG
    _firstConnectEndMsgWait,    //WIFIP2PMATCH_FIRST_ENDMSG_WAIT
    WifiP2PMatch_FriendListInit,        // WIFIP2PMATCH_FRIENDLIST_INIT,
    WifiP2PMatch_FriendList,            // WIFIP2PMATCH_MODE_FRIENDLIST
    _vchatToggleWait,                   // WIFIP2PMATCH_VCHATWIN_WAIT
    WifiP2PMatch_VCTConnectInit2,        // WIFIP2PMATCH_MODE_VCT_CONNECT_INIT2
    WifiP2PMatch_VCTConnectInit,        // WIFIP2PMATCH_MODE_VCT_CONNECT_INIT
    WifiP2PMatch_VCTConnectWait,        // WIFIP2PMATCH_MODE_VCT_CONNECT_WAIT
    WifiP2PMatch_VCTConnect,        // WIFIP2PMATCH_MODE_VCT_CONNECT
    WifiP2PMatch_VCTConnectEndYesNo,   // WIFIP2PMATCH_MODE_VCT_CONNECTEND_YESNO
    WifiP2PMatch_VCTConnectEndWait,   // WIFIP2PMATCH_MODE_VCT_CONNECTEND_WAIT
    WifiP2PMatch_VCTDisconnect,   // WIFIP2PMATCH_MODE_VCT_DISCONNECT
    WifiP2PMatch_BattleDisconnect,   //WIFIP2PMATCH_MODE_BATTLE_DISCONNECT
    WifiP2PMatch_Disconnect,  //WIFIP2PMATCH_MODE_DISCONNECT
    WifiP2PMatch_BattleConnectInit,     // WIFIP2PMATCH_MODE_BATTLE_CONNECT_INIT
    WifiP2PMatch_BattleConnectWait,     // WIFIP2PMATCH_MODE_BATTLE_CONNECT_WAIT
    WifiP2PMatch_BattleConnect,        // WIFIP2PMATCH_MODE_BATTLE_CONNECT
    WifiP2PMatch_MainReturn,            // WIFIP2PMATCH_MODE_MAIN_MENU
    WifiP2PMatch_EndWait,			    // WIFIP2PMATCH_MODE_END_WAIT,
    WifiP2PMatch_CheckAndEnd,          //  WIFIP2PMATCH_MODE_CHECK_AND_END
    _parentModeSelectMenuInit,  // WIFIP2PMATCH_MODE_SELECT_INIT
    _parentModeSelectMenuWait,  // WIFIP2PMATCH_MODE_SELECT_WAIT
    _parentModeSubSelectMenuWait, // WIFIP2PMATCH_MODE_SUBBATTLE_WAIT
    _parentModeSelectRelInit,  //WIFIP2PMATCH_MODE_SELECT_REL_INIT
    _parentModeSelectRelYesNo, //WIFIP2PMATCH_MODE_SELECT_REL_YESNO
    _parentModeSelectRelWait,  //WIFIP2PMATCH_MODE_SELECT_REL_WAIT
    _childModeMatchMenuInit,   //WIFIP2PMATCH_MODE_MATCH_INIT
    _childModeMatchMenuWait,   //WIFIP2PMATCH_MODE_MATCH_WAIT
    _childModeMatchMenuLoop, //WIFIP2PMATCH_MODE_MATCH_LOOP
    WifiP2PMatch_BCancelYesNo, //WIFIP2PMATCH_MODE_BCANCEL_YESNO
    WifiP2PMatch_BCancelWait,    //WIFIP2PMATCH_MODE_BCANCEL_WAIT
    _parentModeCallMenuInit,//WIFIP2PMATCH_MODE_CALL_INIT
    _parentModeCallMenuYesNo,//WIFIP2PMATCH_MODE_CALL_YESNO
    _parentModeCallMenuSend, //WIFIP2PMATCH_MODE_CALL_SEND
    _parentModeCallMenuCheck, //WIFIP2PMATCH_MODE_CALL_CHECK
    _parentModeCallMyStatusWait, //WIFIP2PMATCH_MODE_MYSTATUS_WAIT
    _parentModeCallMenuWait,//WIFIP2PMATCH_MODE_CALL_WAIT
    _personalDataInit,    //WIFIP2PMATCH_MODE_PERSONAL_INIT
    _personalDataWait,    //WIFIP2PMATCH_MODE_PERSONAL_WAIT
    _personalDataEnd,    //WIFIP2PMATCH_MODE_PERSONAL_END
    _exitYesNo,       //WIFIP2PMATCH_MODE_EXIT_YESNO
    _exitWait,        //WIFIP2PMATCH_MODE_EXIT_WAIT
    _exitExiting,        //WIFIP2PMATCH_MODE_EXITING
    _exitEnd,        //WIFIP2PMATCH_MODE_EXIT_END
    _nextBattleYesNo,  //WIFIP2PMATCH_NEXTBATTLE_YESNO
    _nextBattleWait,  //WIFIP2PMATCH_NEXTBATTLE_WAIT
    _vchatNegoCheck, //WIFIP2PMATCH_MODE_VCHAT_NEGO
    _vchatNegoWait, //WIFIP2PMATCH_MODE_VCHAT_NEGO_WAIT
    WifiP2PMatch_ReConnectingWait, //WIFIP2PMATCH_RECONECTING_WAIT
    WifiP2PMatch_BCancelYesNoVCT, //WIFIP2PMATCH_MODE_BCANCEL_YESNO_VCT
    WifiP2PMatch_BCancelWaitVCT,    //WIFIP2PMATCH_MODE_BCANCEL_WAIT_VCT
};


static const BMPWIN_DAT _yesNoBmpDat = {
    GF_BGL_FRAME2_M, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
    FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, FLD_YESNO_WIN_CGX
    };


// �X�e�[�g��BATTLEWAIT���ǂ���
static BOOL _modeBattleWait(int status)
{
    switch(status){
      case WIFI_STATUS_SBATTLE50_WAIT:   // �V���O��Lv50�ΐ��W��
      case WIFI_STATUS_SBATTLE100_WAIT:   // �V���O��Lv100�ΐ��W��
      case WIFI_STATUS_SBATTLE_FREE_WAIT:   // �V���O��Lv100�ΐ��W��
      case WIFI_STATUS_DBATTLE50_WAIT:   // �_�u��Lv50�ΐ��W��
      case WIFI_STATUS_DBATTLE100_WAIT:   // �_�u��Lv100�ΐ��W��
      case WIFI_STATUS_DBATTLE_FREE_WAIT:   // �_�u��Lv100�ΐ��W��
        return TRUE;
      default:
        return FALSE;
    }
}

// �X�e�[�g��WAIT���ǂ���
static BOOL _modeWait(int status)
{
    if(_modeBattleWait(status)){
        return TRUE;
    }
    switch(status){
      case WIFI_STATUS_TRADE_WAIT:    // ������W��
        return TRUE;
    }
    return FALSE;
}

// �X�e�[�g��BATTLE���ǂ���
static BOOL _modeBattle(int status)
{
    switch(status){
      case WIFI_STATUS_SBATTLE50:      // �V���O���ΐ풆
      case WIFI_STATUS_SBATTLE100:      // �V���O���ΐ풆
      case WIFI_STATUS_SBATTLE_FREE:      // �V���O���ΐ풆
      case WIFI_STATUS_DBATTLE50:      // �_�u���ΐ풆
      case WIFI_STATUS_DBATTLE100:      // �_�u���ΐ풆
      case WIFI_STATUS_DBATTLE_FREE:      // �_�u���ΐ풆
        return TRUE;
      default:
        return FALSE;
    }
}

// �X�e�[�g��ACTIVE���ǂ���
static BOOL _modeActive(int status)
{
    if(_modeBattle(status)){
        return TRUE;
    }
    switch(status){
      case WIFI_STATUS_TRADE:    // ������
      case WIFI_STATUS_VCT:    // ������
        return TRUE;
    }
    return FALSE;
}




static BOOL _is2pokeMode(int status)
{
    switch(status){
      case WIFI_STATUS_TRADE_WAIT:
      case WIFI_STATUS_DBATTLE50_WAIT:
      case WIFI_STATUS_DBATTLE100_WAIT:
      case WIFI_STATUS_DBATTLE_FREE_WAIT:
        return TRUE;
    }
    return FALSE;
}


static int _convertState(int state)
{
    int ret = WIFI_STATUS_UNKNOWN;

    switch(state){
      case WIFI_STATUS_TRADE_WAIT:
        ret = WIFI_STATUS_TRADE;
        break;
      case WIFI_STATUS_SBATTLE50_WAIT:
        ret = WIFI_STATUS_SBATTLE50;
        break;
      case WIFI_STATUS_SBATTLE100_WAIT:
        ret = WIFI_STATUS_SBATTLE100;
        break;
      case WIFI_STATUS_SBATTLE_FREE_WAIT:
        ret = WIFI_STATUS_SBATTLE_FREE;
        break;
      case WIFI_STATUS_DBATTLE50_WAIT:
        ret = WIFI_STATUS_DBATTLE50;
        break;
      case WIFI_STATUS_DBATTLE100_WAIT:
        ret = WIFI_STATUS_DBATTLE100;
        break;
      case WIFI_STATUS_DBATTLE_FREE_WAIT:
        ret = WIFI_STATUS_DBATTLE_FREE;
        break;
      case WIFI_STATUS_LOGIN_WAIT:
        ret = WIFI_STATUS_VCT;
        break;
      case WIFI_STATUS_TRADE:
        ret = WIFI_STATUS_TRADE_WAIT;
        break;
      case WIFI_STATUS_SBATTLE50:
        ret = WIFI_STATUS_SBATTLE50_WAIT;
        break;
      case WIFI_STATUS_SBATTLE100:
        ret = WIFI_STATUS_SBATTLE100_WAIT;
        break;
      case WIFI_STATUS_SBATTLE_FREE:
        ret = WIFI_STATUS_SBATTLE_FREE_WAIT;
        break;
      case WIFI_STATUS_DBATTLE50:
        ret = WIFI_STATUS_DBATTLE50_WAIT;
        break;
      case WIFI_STATUS_DBATTLE100:
        ret = WIFI_STATUS_DBATTLE100_WAIT;
        break;
      case WIFI_STATUS_DBATTLE_FREE:
        ret = WIFI_STATUS_DBATTLE_FREE_WAIT;
        break;
      case WIFI_STATUS_VCT:
        ret = WIFI_STATUS_LOGIN_WAIT;
        break;
    }
    return ret;
}

static int _getBattlePokeNum(WIFIP2PMATCH_WORK* wk)
{
    POKEPARTY* pMyPoke = SaveData_GetTemotiPokemon(wk->pSaveData);
    POKEMON_PARAM* poke;
    int max = PokeParty_GetPokeCount(pMyPoke);
    int i,num = 0;

	for(i = 0 ; i < max ; i++){
		poke = PokeParty_GetMemberPointer(pMyPoke, i);
        if (PokeParaGet(poke, ID_PARA_hp, NULL) == 0) {
            continue;
        }
        if (PokeParaGet(poke, ID_PARA_tamago_flag, NULL)) {
            continue;
        }
        num++;
	}
    return num;
}

//============================================================================================
//	�v���Z�X�֐�
//============================================================================================

static void _graphicInit(WIFIP2PMATCH_WORK * wk)
{
    sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
    sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

    GF_Disp_GX_VisibleControlInit();
    GF_Disp_GXS_VisibleControlInit();
    GX_SetVisiblePlane( 0 );
    GXS_SetVisiblePlane( 0 );
    sys_KeyRepeatSpeedSet( 4, 8 );

    wk->bgl = GF_BGL_BglIniAlloc( HEAPID_WIFIP2PMATCH );
    // ������}�l�[�W���[����
    wk->WordSet    = WORDSET_Create( HEAPID_WIFIP2PMATCH );
    wk->MsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wifi_lobby_dat, HEAPID_WIFIP2PMATCH );
    wk->SysMsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wifi_system_dat, HEAPID_WIFIP2PMATCH );

    // VRAM �o���N�ݒ�
    VramBankSet();

    // BGL���W�X�^�ݒ�
    BgInit( wk->bgl );


    //BG�O���t�B�b�N�Z�b�g
    BgGraphicSet( wk );

    // VBlank�֐��Z�b�g
    sys_VBlankFuncChange( VBlankFunc, wk );

    // OBJ�L�����A�p���b�g�}�l�[�W���[������
    char_pltt_manager_init();

    // CellActor�V�X�e��������
    InitCellActor(wk);

    // CellActro�\���o�^
    SetCellActor(wk);
}


//--------------------------------------------------------------------------------------------
/**
 * �v���Z�X�֐��F������
 *
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 *
 * @return	������
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT WifiP2PMatchProc_Init( PROC * proc, int * seq )
{
    WIFIP2PMATCH_WORK * wk;
    WIFIP2PMATCH_PROC_PARAM* pParentWork;

    switch(*seq){
      case 0:
        pParentWork = PROC_GetParentWork(proc);

        if(pParentWork->seq == WIFI_P2PMATCH_DPW){ // ���E�ΐ�Ȃ�
            sys_CreateHeap( HEAPID_BASE_APP, HEAPID_WIFIP2PMATCH, 0x70000 );
        }
        else{
            sys_CreateHeap( HEAPID_BASE_APP, HEAPID_WIFIP2PMATCH, 0xb0000 );
        }
        wk = PROC_AllocWork( proc, sizeof(WIFIP2PMATCH_WORK), HEAPID_WIFIP2PMATCH );
        MI_CpuFill8( wk, 0, sizeof(WIFIP2PMATCH_WORK) );

        wk->MsgIndex = _PRINTTASK_MAX;
        wk->pSaveData = pParentWork->pSaveData;
        wk->pList = SaveData_GetWifiListData(wk->pSaveData);
        wk->initSeq = pParentWork->seq;    // P2P��DPW��
        wk->endSeq = WIFI_P2PMATCH_END;
        wk->preConnect = -1;

        GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0|GX_PLANEMASK_BG1|GX_PLANEMASK_BG2|GX_PLANEMASK_BG3, VISIBLE_OFF );
        GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0|GX_PLANEMASK_BG1|GX_PLANEMASK_BG2|GX_PLANEMASK_BG3, VISIBLE_OFF );
        
        // ���[�N������
        InitWork( wk );
        //        WIPE_ResetBrightness( WIPE_DISP_MAIN );
        WIPE_ResetBrightness( WIPE_DISP_SUB );
        WIPE_ResetWndMask( WIPE_DISP_SUB );
        // ���C�v�t�F�[�h�J�n
        WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK,
                        COMM_BRIGHTNESS_SYNC, 1, HEAPID_WIFIP2PMATCH);
        _graphicInit(wk);

        if(CommStateIsWifiConnect()){
        }
        else{
            DwcOverlayStart();    // WIFI�I�[�o�[���C
        }
        (*seq)++;
        break;
      case 1:
        wk = PROC_GetWork( proc );
        (*seq) = SEQ_IN;
        return PROC_RES_FINISH;
        break;
    }
    return PROC_RES_CONTINUE;
}




//--------------------------------------------------------------------------------------------
/**
 * �v���Z�X�֐��F���C��
 *
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 *
 * @return	������
 */
//--------------------------------------------------------------------------------------------

PROC_RESULT WifiP2PMatchProc_Main( PROC * proc, int * seq )
{
    WIFIP2PMATCH_WORK * wk  = PROC_GetWork( proc );

    switch( *seq ){
      case SEQ_IN:
        if( WIPE_SYS_EndCheck() ){
            // ���C�v�����҂�
            *seq = SEQ_MAIN;


        }
        break;

      case SEQ_MAIN:
        // �J�[�\���ړ�

        // �V�[�P���X���̓���
        if(FuncTable[wk->seq]!=NULL){
#ifdef PM_DEBUG
            static int seqBk=0;

            if(seqBk != wk->seq){
                OHNO_PRINT("wp2p %d \n",wk->seq);
            }
            seqBk = wk->seq;
#endif
            *seq = (*FuncTable[wk->seq])( wk, *seq );
        }

        break;

      case SEQ_OUT:
        if( WIPE_SYS_EndCheck() ){
            return PROC_RES_FINISH;
        }
        break;
    }
    if(wk->clactSet){
        CLACT_Draw( wk->clactSet );									// �Z���A�N�^�[�풓�֐�
    }

    return PROC_RES_CONTINUE;
}

#define DEFAULT_NAME_MAX		18

// �_�C���E�p�[���ŕς��񂾂낤
#define MALE_NAME_START			0
#define FEMALE_NAME_START		18


//--------------------------------------------------------------------------------------------
/**
 * �O���t�B�b�N�ɂ�����镔���̏I������
 * @param	wk	WIFIP2PMATCH_WORK
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void _graphicEnd(WIFIP2PMATCH_WORK* wk)
{
    int i;

    sys_VBlankFuncChange( NULL, NULL );	// VBlankReset

    // �L�����]���}�l�[�W���[�j��
    CLACT_U_CharManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES]);

    // �p���b�g�]���}�l�[�W���[�j��
    CLACT_U_PlttManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES]);

    // �L�����E�p���b�g�E�Z���E�Z���A�j���̃��\�[�X�}�l�[�W���[�j��
    for(i=0;i<CLACT_RESOURCE_NUM;i++){
        CLACT_U_ResManagerDelete(wk->resMan[i]);
    }
    // �Z���A�N�^�[�Z�b�g�j��
    CLACT_DestSet(wk->clactSet);

    //OAM�����_���[�j��
    REND_OAM_Delete();

    // ���\�[�X���
    DeleteCharManager();
    DeletePlttManager();

    // BMP�E�B���h�E�J��
    BmpWinDelete( wk );

    // BGL�폜
    BgExit( wk->bgl );

    // �e�̃v���b�N�̏���
    //    UnionRoomView_ObjInit( (COMM_UNIONROOM_VIEW*)PROC_GetParentWork( proc ) );

    // �^�b�`�p�l���V�X�e���I��
    //	StopTP();


    // ���b�Z�[�W�}�l�[�W���[�E���[�h�Z�b�g�}�l�[�W���[���
    MSGMAN_Delete( wk->SysMsgManager );
    MSGMAN_Delete( wk->MsgManager );
    WORDSET_Delete( wk->WordSet );


}


//--------------------------------------------------------------------------------------------
/**
 * �v���Z�X�֐��F�I��
 *
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 *
 * @return	������
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT WifiP2PMatchProc_End( PROC * proc, int * seq )
{
    WIFIP2PMATCH_WORK  *wk    = PROC_GetWork( proc );
    WIFIP2PMATCH_PROC_PARAM* pParentWork;

    _graphicEnd(wk);

    pParentWork = PROC_GetParentWork(proc);
    pParentWork->seq = wk->endSeq;
    if( (wk->endSeq == WIFI_P2PMATCH_END) || (wk->endSeq == WIFI_P2PMATCH_DPW_END)){  // �I�[�o�[���C����
        DwcOverlayEnd();
    }
    else{
        pParentWork->targetID = mydwc_getFriendIndex();
    }
    // ���[�N���
    FreeWork( wk );

    PROC_FreeWork( proc );				// PROC���[�N�J��

    sys_DeleteHeap( HEAPID_WIFIP2PMATCH );
    //    WIPE_ResetBrightness( WIPE_DISP_MAIN );
    //  WIPE_ResetBrightness( WIPE_DISP_SUB );

    return PROC_RES_FINISH;
}

//--------------------------------------------------------------------------------------------
/**
 * VBlank�֐�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VBlankFunc( void * work )
{
    WIFIP2PMATCH_WORK* wk = work;

    // BG��������
	GF_BGL_VBlankFunc( wk->bgl );
    // �Z���A�N�^�[
    // Vram�]���}�l�[�W���[���s
    DoVramTransferManager();

    // �����_�����LOAM�}�l�[�W��Vram�]��
    REND_OAMTrans();

    OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}


//--------------------------------------------------------------------------------------------
/**
 * VRAM�ݒ�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VramBankSet(void)
{
    GF_BGL_DISPVRAM tbl = {
        GX_VRAM_BG_128_A,				// ���C��2D�G���W����BG
        GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g

        GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
        GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g

        GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
        GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g

        GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
        GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g

        GX_VRAM_TEX_NONE,				// �e�N�X�`���C���[�W�X���b�g
        GX_VRAM_TEXPLTT_NONE			// �e�N�X�`���p���b�g�X���b�g
        };
    GF_Disp_SetBank( &tbl );
}

//--------------------------------------------------------------------------------------------
/**
 * BG�ݒ�
 *
 * @param	ini		BGL�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgInit( GF_BGL_INI * ini )
{
    // BG SYSTEM
    {
        GF_BGL_SYS_HEADER BGsys_data = {
            GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
        };
        GF_BGL_InitBG( &BGsys_data );
    }

    // ���C����ʕ�����0
    {
        GF_BGL_BGCNT_HEADER TextBgCntDat = {
            0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0xc000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
            0, 0, 0, FALSE
            };
        GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
        GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_WIFIP2PMATCH);
        GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );


    }

    // ���C�����1
    {
        GF_BGL_BGCNT_HEADER TextBgCntDat = {
            0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0xd000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
            1, 0, 0, FALSE
            };
        GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
        GF_BGL_ClearCharSet( GF_BGL_FRAME1_M, 32, 0, HEAPID_WIFIP2PMATCH);
        GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
    }

    // ���C����ʔw�i
    {
        GF_BGL_BGCNT_HEADER TextBgCntDat = {
            0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_23,
            2, 0, 0, FALSE
            };
        GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
        GF_BGL_ClearCharSet( GF_BGL_FRAME2_M, 32, 0, HEAPID_WIFIP2PMATCH);
        GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
    }

#if 1
    // �w�i (CHAR)
    {
        GF_BGL_BGCNT_HEADER TextBgCntDat = {
            0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_23,
            3, 0, 0, FALSE
            };
        GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
        GF_BGL_ClearCharSet( GF_BGL_FRAME3_M, 32, 0, HEAPID_WIFIP2PMATCH);
        GF_BGL_ScrClear( ini, GF_BGL_FRAME3_M );
    }
#endif

    // �T�u��ʃe�L�X�g��
    {
        GF_BGL_BGCNT_HEADER TextBgCntDat = {
            0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
            0, 0, 0, FALSE
            };
        GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
        GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );
    }
    /*
	// �T�u��ʔw�i��
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}
     */
    GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_WIFIP2PMATCH );
    GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_WIFIP2PMATCH );

    GF_BGL_PrioritySet(GF_BGL_FRAME0_M , 3);  //�͂�����
    GF_BGL_PrioritySet(GF_BGL_FRAME1_M , 2);   //
    GF_BGL_PrioritySet(GF_BGL_FRAME3_M , 1);  // ���b�Z�[�W
    GF_BGL_PrioritySet(GF_BGL_FRAME2_M , 0);   //

    G2_BlendNone();
    G2S_BlendNone();
}

static void WindowSet(void)
{
    GX_SetVisibleWnd( GX_WNDMASK_NONE );
    GXS_SetVisibleWnd( GX_WNDMASK_NONE );
    /*
    GX_SetVisibleWnd( GX_WNDMASK_W0 );
	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_NONE, 1 );
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_NONE, 1 );
	G2_SetWnd0Position( 0, 255, 0, 192 );

	GXS_SetVisibleWnd( GX_WNDMASK_W0 );
	G2S_SetWnd0InsidePlane( GX_WND_PLANEMASK_NONE, 1 );
	G2S_SetWndOutsidePlane( GX_WND_PLANEMASK_NONE, 1 );
	G2S_SetWnd0Position( 0, 255, 0, 192 );
     */
}

#define TALK_MESSAGE_BUF_NUM	( 190*2 )
#define TITLE_MESSAGE_BUF_NUM	( 90*2 )

//------------------------------------------------------------------
/**
 * ���[�N������
 *
 * @param   wk		WIFIP2PMATCH_WORK*
 *
 * @retval  none
 */
//------------------------------------------------------------------
static void InitWork( WIFIP2PMATCH_WORK *wk )
{
    int i;
    int flag;

    for(i=0;i<WIFIP2PMATCH_MEMBER_MAX;i++){
        wk->TrainerName[i] = STRBUF_Create( PERSON_NAME_SIZE+EOM_SIZE, HEAPID_WIFIP2PMATCH );
        STRBUF_SetStringCode(wk->TrainerName[i] ,WifiList_GetFriendNamePtr(wk->pList,i));
    }
    wk->TalkString =  STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WIFIP2PMATCH );
    wk->pTemp = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WIFIP2PMATCH );        // ���͓o�^���̈ꎞ�o�b�t�@


    // ������o�b�t�@�쐬
    for(i = 0;i < 4;i++){
        wk->MenuString[i]  = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WIFIP2PMATCH );
    }
    wk->pExpStrBuf = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WIFIP2PMATCH );
    wk->TitleString = STRBUF_Create( TITLE_MESSAGE_BUF_NUM, HEAPID_WIFIP2PMATCH );

    wk->seq = WIFIP2PMATCH_MODE_INIT;

}

//------------------------------------------------------------------
/**
 * $brief   ���[�N���
 *
 * @param   wk
 *
 * @retval  none
 */
//------------------------------------------------------------------
static void FreeWork( WIFIP2PMATCH_WORK *wk )
{
    int i;


    for(i=0;i<WIFIP2PMATCH_MEMBER_MAX;i++){
        STRBUF_Delete( wk->TrainerName[i] );
    }
    STRBUF_Delete( wk->TitleString );
    STRBUF_Delete( wk->TalkString );
    STRBUF_Delete( wk->pTemp );

    for(i = 0;i < 4;i++){
        STRBUF_Delete(wk->MenuString[i]);
    }
    STRBUF_Delete(wk->pExpStrBuf);

}

//--------------------------------------------------------------------------------------------
/**
 * BG���
 *
 * @param	ini		BGL�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgExit( GF_BGL_INI * ini )
{

    GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
    GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );
    GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_M );
    GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
    GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_M );
    GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_M );

    sys_FreeMemoryEz( ini );
}


//--------------------------------------------------------------------------------------------
/**
 * �O���t�B�b�N�f�[�^�Z�b�g
 *
 * @param	wk		�|�P�������X�g��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------


static void BgGraphicSet( WIFIP2PMATCH_WORK * wk )
{
    GF_BGL_INI *bgl = wk->bgl;

    GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
    GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
    GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
    GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );

    // �㉺��ʂa�f�p���b�g�]��
    ArcUtil_PalSet(    ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_NCLR, PALTYPE_MAIN_BG, 0, 0,  HEAPID_WIFIP2PMATCH);
    ArcUtil_PalSet(    ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_NCLR, PALTYPE_SUB_BG,  0, 0,  HEAPID_WIFIP2PMATCH);

    // ��b�t�H���g�p���b�g�]��
    TalkFontPaletteLoad( PALTYPE_MAIN_BG, _NUKI_FONT_PALNO*0x20, HEAPID_WIFIP2PMATCH );
    TalkFontPaletteLoad( PALTYPE_MAIN_BG, COMM_MESFONT_PAL*0x20, HEAPID_WIFIP2PMATCH );
    //	TalkFontPaletteLoad( PALTYPE_SUB_BG,  13*0x20, HEAPID_WIFIP2PMATCH );


    // ���C�����BG2�L�����]��
    ArcUtil_BgCharSet( ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_NCGR, bgl,
                       GF_BGL_FRAME0_M, 0, 0, 0, HEAPID_WIFIP2PMATCH);

    // ���C�����BG2�X�N���[���]��
    ArcUtil_ScrnSet(   ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_01_NSCR, bgl,
                       GF_BGL_FRAME0_M, 0, 0, 0, HEAPID_WIFIP2PMATCH);


    // �T�u���BG0�L�����]��
    ArcUtil_BgCharSet( ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_s_NCGR, bgl, GF_BGL_FRAME0_S, 0, 0, 0, HEAPID_WIFIP2PMATCH);

    // �T�u���BG0�X�N���[���]��
    ArcUtil_ScrnSet(   ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_s_NSCR, bgl, GF_BGL_FRAME0_S, 0, 0, 0, HEAPID_WIFIP2PMATCH);

    {
        int type = CONFIG_GetWindowType(SaveData_GetConfig(wk->pSaveData));
        TalkWinGraphicSet(
            bgl, GF_BGL_FRAME2_M, COMM_TALK_WIN_CGX_NUM, COMM_MESFRAME_PAL,  type, HEAPID_WIFIP2PMATCH );
        MenuWinGraphicSet(
            bgl, GF_BGL_FRAME2_M, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_WIFIP2PMATCH );
        MenuWinGraphicSet(
            bgl, GF_BGL_FRAME1_M, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_WIFIP2PMATCH );
    }

}


//** CharManager PlttManager�p **//
#define WIFIP2PMATCH_CHAR_CONT_NUM				(20)
#define WIFIP2PMATCH_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define WIFIP2PMATCH_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define WIFIP2PMATCH_PLTT_CONT_NUM				(20)

//-------------------------------------
//
//	�L�����N�^�}�l�[�W���[
//	�p���b�g�}�l�[�W���[�̏�����
//
//=====================================
static void char_pltt_manager_init(void)
{
    // �L�����N�^�}�l�[�W���[������
    {
        CHAR_MANAGER_MAKE cm = {
            WIFIP2PMATCH_CHAR_CONT_NUM,
            WIFIP2PMATCH_CHAR_VRAMTRANS_MAIN_SIZE,
            WIFIP2PMATCH_CHAR_VRAMTRANS_SUB_SIZE,
            HEAPID_WIFIP2PMATCH
            };
        InitCharManager(&cm);
    }
    // �p���b�g�}�l�[�W���[������
    InitPlttManager(WIFIP2PMATCH_PLTT_CONT_NUM, HEAPID_WIFIP2PMATCH);

    // �ǂݍ��݊J�n�ʒu��������
    CharLoadStartAll();
    PlttLoadStartAll();
	//�ʐM�A�C�R���p�ɃL�������p���b�g����
	CLACT_U_WmIcon_SetReserveAreaCharManager(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_64K);
	CLACT_U_WmIcon_SetReserveAreaPlttManager(NNS_G2D_VRAM_TYPE_2DMAIN);
}


//------------------------------------------------------------------
/**
 * �Z���A�N�^�[������
 *
 * @param   wk		���[�_�[�\���̂̃|�C���^
 *
 * @retval  none
 */
//------------------------------------------------------------------
static void InitCellActor(WIFIP2PMATCH_WORK *wk)
{
    int i;


    // OAM�}�l�[�W���[�̏�����
    NNS_G2dInitOamManagerModule();

    // ���LOAM�}�l�[�W���쐬
    // �����_���pOAM�}�l�[�W���쐬
    // �����ō쐬����OAM�}�l�[�W�����݂�Ȃŋ��L����
    REND_OAMInit(
        0, 126,		// ���C�����OAM�Ǘ��̈�
        0, 32,		// ���C����ʃA�t�B���Ǘ��̈�
        0, 126,		// �T�u���OAM�Ǘ��̈�
        0, 32,		// �T�u��ʃA�t�B���Ǘ��̈�
        HEAPID_WIFIP2PMATCH);



    // �Z���A�N�^�[������
    wk->clactSet = CLACT_U_SetEasyInit( 30, &wk->renddata, HEAPID_WIFIP2PMATCH );

    CLACT_U_SetSubSurfaceMatrix( &wk->renddata, 0, NAMEIN_SUB_ACTOR_DISTANCE );


    //���\�[�X�}�l�[�W���[������
    for(i=0;i<CLACT_RESOURCE_NUM;i++){		//���\�[�X�}�l�[�W���[�쐬
        wk->resMan[i] = CLACT_U_ResManagerInit(2, i, HEAPID_WIFIP2PMATCH);
    }


    //---------���ʗp-------------------

    //chara�ǂݍ���
    wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] =
        CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES],
                                        ARC_WIFIP2PMATCH_GRA,
                                        NARC_wifip2pmatch_conect_obj_NCGR, FALSE, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_WIFIP2PMATCH);

    //pal�ǂݍ���
    wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] =
        CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
                                        ARC_WIFIP2PMATCH_GRA,
                                        NARC_wifip2pmatch_conect_obj_NCLR, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 7, HEAPID_WIFIP2PMATCH);

    //cell�ǂݍ���
    wk->resObjTbl[MAIN_LCD][CLACT_U_CELL_RES] =
        CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
                                            ARC_WIFIP2PMATCH_GRA,
                                            NARC_wifip2pmatch_conect_NCER, FALSE, 0, CLACT_U_CELL_RES,HEAPID_WIFIP2PMATCH);

    //�����֐���anim�ǂݍ���
    wk->resObjTbl[MAIN_LCD][CLACT_U_CELLANM_RES] =
        CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
                                            ARC_WIFIP2PMATCH_GRA,
                                            NARC_wifip2pmatch_conect_NANR, FALSE, 0, CLACT_U_CELLANM_RES,HEAPID_WIFIP2PMATCH);


    // ���\�[�X�}�l�[�W���[����]��

    // Chara�]��
    CLACT_U_CharManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] );
    //	CLACT_U_CharManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] );

    // �p���b�g�]��
    CLACT_U_PlttManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] );
    //	CLACT_U_PlttManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] );

}

#define TRAINER_NAME_POS_X		( 24 )
#define TRAINER_NAME_POS_Y		( 32 )
#define TRAINER_NAME_POS_SPAN	( 32 )

#define TRAINER_NAME_WIN_X		(  3 )
#define TRAINER1_NAME_WIN_Y		(  6 )
#define TRAINER2_NAME_WIN_Y		(  7 )

//------------------------------------------------------------------
/**
 * �Z���A�N�^�[�o�^
 *
 * @param   wk			WIFIP2PMATCH_WORK*
 *
 * @retval  none
 */
//------------------------------------------------------------------
static void SetCellActor(WIFIP2PMATCH_WORK *wk)
{
    int i;
    // �Z���A�N�^�[�w�b�_�쐬
    CLACT_U_MakeHeader(&wk->clActHeader_m, 0, 0, 0, 0, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
                       0, 0,
                       wk->resMan[CLACT_U_CHAR_RES],
                       wk->resMan[CLACT_U_PLTT_RES],
                       wk->resMan[CLACT_U_CELL_RES],
                       wk->resMan[CLACT_U_CELLANM_RES],
                       NULL,NULL);

    /*
	CLACT_U_MakeHeader(&wk->clActHeader_s, 1, 1, 1, 1, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 0,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);
     */
    {
        //�o�^���i�[
        CLACT_ADD add;

        add.ClActSet	= wk->clactSet;
        add.ClActHeader	= &wk->clActHeader_m;

        add.mat.z		= 0;
        add.sca.x		= FX32_ONE;
        add.sca.y		= FX32_ONE;
        add.sca.z		= FX32_ONE;
        add.rot			= 0;
        add.pri			= 1;
        add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
        add.heap		= HEAPID_WIFIP2PMATCH;

        //�Z���A�N�^�[�\���J�n
        // �T�u��ʗp(���̓o�^�j
        for(i=0;i < _OAM_NUM;i++){
            add.mat.x = FX32_ONE *   TRAINER_NAME_POS_X;
            add.mat.y = FX32_ONE * ( TRAINER_NAME_POS_Y + TRAINER_NAME_POS_SPAN*i ) + NAMEIN_SUB_ACTOR_DISTANCE;
            wk->MainActWork[i] = CLACT_Add(&add);
            CLACT_SetAnmFlag(wk->MainActWork[i],1);
            CLACT_AnmChg( wk->MainActWork[i], i );
            CLACT_BGPriorityChg(wk->MainActWork[i], 2);
            CLACT_SetDrawFlag( wk->MainActWork[i], 0 );
        }

    }
    GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_ON );	//���C�����OBJ�ʂn�m
    //	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );	//�T�u���OBJ�ʂn�m

}


//------------------------------------------------------------------
/**
 * BMPWIN�����i�����p�l���Ƀt�H���g�`��j
 *
 * @param   wk
 *
 * @retval  none
 */
//------------------------------------------------------------------
static void MainMenuMsgInit(WIFIP2PMATCH_WORK *wk)
{
    int i,col;


    if(GF_BGL_BmpWinAddCheck(&wk->TitleWin)){
        BmpMenuWinClear(&wk->TitleWin, WINDOW_TRANS_ON );
        GF_BGL_BmpWinDel(&wk->TitleWin);
    }
    GF_BGL_BmpWinAdd(wk->bgl, &wk->TitleWin, GF_BGL_FRAME3_M, 4, 1, 22, 2,
                     _NUKI_FONT_PALNO,  _CGX_BOTTOM - 18*3 );
    GF_BGL_BmpWinDataFill( &wk->TitleWin, 0x8000 );
    MSGMAN_GetString(  wk->MsgManager, msg_wifilobby_018, wk->TitleString );
    GF_STR_PrintColor( &wk->TitleWin, FONT_TALK, wk->TitleString, 0, 0, MSG_NO_PUT,_COL_N_WHITE, NULL);
    GF_BGL_BmpWinOnVReq(&wk->TitleWin);

}


// �͂��E������BMP�i����ʁj
#define YESNO_WIN_FRAME_CHAR	( 1 + TALK_WIN_CGX_SIZ )
#define YESNO_CHARA_OFFSET		( 1 + TALK_WIN_CGX_SIZ + MENU_WIN_CGX_SIZ + FLD_MSG_WIN_SX*FLD_MSG_WIN_SY )
#define YESNO_WINDOW_X			( 22 )
#define YESNO_WINDOW_Y1			(  7 )
#define YESNO_WINDOW_Y2			( 13 )
#define YESNO_CHARA_W			(  8 )
#define YESNO_CHARA_H			(  4 )

static const BMPWIN_DAT TouchYesNoBmpDat[2]={
    {
        GF_BGL_FRAME0_M, YESNO_WINDOW_X, YESNO_WINDOW_Y1,
        YESNO_CHARA_W, YESNO_CHARA_H, 13, YESNO_CHARA_OFFSET
        },
    {
        GF_BGL_FRAME0_M, YESNO_WINDOW_X, YESNO_WINDOW_Y2,
        YESNO_CHARA_W, YESNO_CHARA_H, 13, YESNO_CHARA_OFFSET+YESNO_CHARA_W*YESNO_CHARA_H

        }
};

//------------------------------------------------------------------
/**
 * $brief   �m�ۂ���BMPWIN�����
 *
 * @param   wk
 *
 * @retval  none
 */
//------------------------------------------------------------------
static void BmpWinDelete( WIFIP2PMATCH_WORK *wk )
{
    int i;

    if(GF_BGL_BmpWinAddCheck(&wk->TitleWin)){
        GF_BGL_BmpWinDel(&wk->TitleWin);
    }
    if(GF_BGL_BmpWinAddCheck(&wk->MsgWin)){
        GF_BGL_BmpWinDel(&wk->MsgWin);
    }
    if(GF_BGL_BmpWinAddCheck(&wk->MyWin)){
        GF_BGL_BmpWinDel(&wk->MyWin);
    }
    if(GF_BGL_BmpWinAddCheck(&wk->MyInfoWin)){
        GF_BGL_BmpWinDel(&wk->MyInfoWin);
    }
    if(GF_BGL_BmpWinAddCheck(&wk->ListWin)){
        GF_BGL_BmpWinDel(&wk->ListWin);
    }
    if(wk->lw){
        BmpListExit(wk->lw, NULL, NULL);
    }
    if(wk->menulist){
        BMP_MENULIST_Delete( wk->menulist );
        wk->menulist = NULL;
    }
    
    if(GF_BGL_BmpWinAddCheck(&wk->SysMsgWin)){
        GF_BGL_BmpWinDel(&wk->SysMsgWin);
    }


}


//------------------------------------------------------------------
/**
 * $brief   �J�n���̃��b�Z�[�W   WIFIP2PMATCH_MODE_INIT
 * @param   wk
 * @param   seq
 * @retval  none
 */
//------------------------------------------------------------------

static const BMPWIN_DAT _yesNoBmpDatSys = {
    GF_BGL_FRAME2_M, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
    FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, (COMM_SYS_WIN_CGX - (FLD_YESNO_WIN_SX*FLD_YESNO_WIN_SY))
    };
static const BMPWIN_DAT _yesNoBmpDatSys2 = {
    GF_BGL_FRAME1_M, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY+6,
    FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, (COMM_SYS_WIN_CGX - (FLD_YESNO_WIN_SX*FLD_YESNO_WIN_SY))
    };

static int WifiP2PMatch_MainInit( WIFIP2PMATCH_WORK *wk, int seq )
{
    //Snd_BgmPlay( _BGM_MAIN );
	Snd_DataSetByScene( SND_SCENE_P2P, _BGM_MAIN, 1 );	//wifi���r�[�Đ�

    OHNO_PRINT("�T�E���h��������\n");
    if(CommStateIsWifiConnect()){       // �ڑ���
        WirelessIconEasy();  // �ڑ����Ȃ̂ŃA�C�R���\��
        _friendNameExpand(wk, mydwc_getFriendIndex());
        wk->pMatch = CommStateGetMatchWork();
        wk->pMatch->myMatchStatus.vchat = wk->pMatch->myMatchStatus.vchat_org;
        if(wk->pMatch->myMatchStatus.status == WIFI_STATUS_TRADE){
            CommStateWifiTradeMatchEnd();
            wk->pMatch = CommStateGetMatchWork();
            wk->pMatch->myMatchStatus.vchat = wk->pMatch->myMatchStatus.vchat_org;
            wk->timer = _RECONECTING_WAIT_TIME;
            wk->seq = WIFIP2PMATCH_RECONECTING_WAIT;
        }
        else{
            WifiP2PMatchMessagePrint(wk, msg_wifilobby_044, FALSE);
            CommTimingSyncStart(_TIMING_BATTLE_END);
            wk->seq = WIFIP2PMATCH_NEXTBATTLE_YESNO;
        }
        /*        CommStateWifiMatchEnd();
        wk->pMatch = CommStateGetMatchWork();
        wk->seq = WIFIP2PMATCH_FRIENDLIST_INIT;   */
    }
    else{        // �ڑ����܂�
        MainMenuMsgInit(wk);// BMPWIN�o�^�E�`��
        if( !DWC_CheckHasProfile( WifiList_GetMyUserInfo(wk->pList) ) ){
            GF_BGL_PrioritySet(GF_BGL_FRAME0_M , 3);  //�͂�����
            GF_BGL_PrioritySet(GF_BGL_FRAME3_M , 2);  // ���b�Z�[�W
            GF_BGL_PrioritySet(GF_BGL_FRAME2_M , 1);   //
            GF_BGL_PrioritySet(GF_BGL_FRAME1_M , 0);   //
            _systemMessagePrint(wk, dwc_message_0003);
            wk->pYesNoWork =
                BmpYesNoSelectInit( wk->bgl,
                                    &_yesNoBmpDatSys2,
                                    MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                    HEAPID_WIFIP2PMATCH );
            wk->seq = WIFIP2PMATCH_FIRST_YESNO;
        }
        else if( !DWC_CheckValidConsole(WifiList_GetMyUserInfo(wk->pList)) ){
            _systemMessagePrint(wk, dwc_message_0005);
            wk->seq = WIFIP2PMATCH_DIFFER_MACHINE_INIT;
        }
        else{
            WifiP2PMatchMessagePrint(wk, dwc_message_0002, TRUE);
            wk->seq = WIFIP2PMATCH_NORMALCONNECT_YESNO;
        }
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �ʏ�̐ڑ�  WIFIP2PMATCH_NORMALCONNECT_YESNO
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------
static int _normalConnectYesNo( WIFIP2PMATCH_WORK *wk, int seq )
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        wk->pYesNoWork =
            BmpYesNoSelectInit( wk->bgl,
                                &_yesNoBmpDatSys,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                HEAPID_WIFIP2PMATCH );
        wk->seq = WIFIP2PMATCH_NORMALCONNECT_WAIT;
    }
    return seq;
}


//------------------------------------------------------------------
/**
 * $brief   �ʏ�̐ڑ�  WIFIP2PMATCH_NORMALCONNECT_WAIT
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------
static int _normalConnectWait( WIFIP2PMATCH_WORK *wk, int seq )
{
    int i;
    int ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);
    if(ret == BMPMENU_NULL){  // �܂��I��
        return seq;
    }
    else{
        //BmpTalkWinClear( &wk->SysMsgWin, WINDOW_TRANS_ON );
        if(ret == 0){ // �͂���I�������ꍇ
            //�ڑ��J�n
            wk->pMatch = CommStateWifiEnterLogin(wk->pSaveData,sizeof(TEST_MATCH_WORK));
            WifiP2PMatchMessagePrint(wk, dwc_message_0008, TRUE);
            wk->timeWaitWork = TimeWaitIconAdd( &wk->MsgWin, COMM_TALK_WIN_CGX_NUM );
            wk->seq = WIFIP2PMATCH_CONNECTING_INIT;
        }
        else{  // ��������I�������ꍇ
            wk->seq = WIFIP2PMATCH_MODE_END_WAIT;
        }
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �ʂ�DS�������ꍇ  WIFIP2PMATCH_DIFFER_MACHINE_INIT
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------

static int _differMachineInit( WIFIP2PMATCH_WORK *wk, int seq )
{
    if(sys.trg & (PAD_BUTTON_CANCEL|PAD_BUTTON_DECIDE)){
        _systemMessagePrint(wk,dwc_message_0006);
        GF_BGL_PrioritySet(GF_BGL_FRAME0_M , 3);  //�͂�����
        GF_BGL_PrioritySet(GF_BGL_FRAME3_M , 2);  // ���b�Z�[�W
        GF_BGL_PrioritySet(GF_BGL_FRAME2_M , 1);   //
        GF_BGL_PrioritySet(GF_BGL_FRAME1_M , 0);   //
        wk->pYesNoWork =
            BmpYesNoSelectInit( wk->bgl,
                                &_yesNoBmpDatSys2,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                HEAPID_WIFIP2PMATCH );
        wk->seq = WIFIP2PMATCH_DIFFER_MACHINE_NEXT;
    }

    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �ʂ�DS�������ꍇ  WIFIP2PMATCH_DIFFER_MACHINE_NEXT
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------

static int _differMachineNext( WIFIP2PMATCH_WORK *wk, int seq )
{
    int i;
    int ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);
    if(ret == BMPMENU_NULL){  // �܂��I��
        return seq;
    }
    else{
        BmpTalkWinClear( &wk->SysMsgWin, WINDOW_TRANS_ON );
        GF_BGL_BmpWinDel( &wk->SysMsgWin );
        if(ret == 0){ // �͂���I�������ꍇ
            _systemMessagePrint(wk,dwc_message_0007);
            wk->pYesNoWork =
                BmpYesNoSelectInit( wk->bgl,
                                    &_yesNoBmpDatSys2,
                                    MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                    HEAPID_WIFIP2PMATCH );
            wk->seq = WIFIP2PMATCH_DIFFER_MACHINE_ONEMORE;
        }
        else{  // ��������I�������ꍇ
            wk->seq = WIFIP2PMATCH_MODE_END_WAIT;
        }
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �ʂ�DS�������ꍇ  WIFIP2PMATCH_DIFFER_MACHINE_ONEMORE
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------

static int _differMachineOneMore( WIFIP2PMATCH_WORK *wk, int seq )
{
    int i;
    int ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);
    if(ret == BMPMENU_NULL){  // �܂��I��
        return seq;
    }
    else{
        BmpTalkWinClear( &wk->SysMsgWin, WINDOW_TRANS_ON );
        GF_BGL_BmpWinDel( &wk->SysMsgWin );
        if(ret == 0){ // �͂���I�������ꍇ
            //�ڑ��J�n
            WifiList_Init(wk->pList);

            wk->seq = WIFIP2PMATCH_CONNECTING_INIT;
            wk->pMatch = CommStateWifiEnterLogin(wk->pSaveData,sizeof(TEST_MATCH_WORK));
            WifiP2PMatchMessagePrint(wk, dwc_message_0008, TRUE);
            wk->timeWaitWork = TimeWaitIconAdd( &wk->MsgWin, COMM_TALK_WIN_CGX_NUM );
            wk->bInitMessage = TRUE;
        }
        else{  // ��������I�������ꍇ
            wk->seq = WIFIP2PMATCH_MODE_END_WAIT;
        }
    }
    return seq;
}

//WIFIP2PMATCH_FIRST_YESNO
//------------------------------------------------------------------
/**
 * $brief   ����ڑ����̊m�F  WIFIP2PMATCH_FIRST_YESNO
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------

static int _firstYesNo( WIFIP2PMATCH_WORK *wk, int seq )
{
    int i;
    int ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);
    if(ret == BMPMENU_NULL){  // �܂��I��
        return seq;
    }
    else{
        BmpTalkWinClear( &wk->SysMsgWin, WINDOW_TRANS_ON );
        GF_BGL_BmpWinDel( &wk->SysMsgWin );
        if(ret == 0){ // �͂���I�������ꍇ
            //�ڑ��J�n
            wk->seq = WIFIP2PMATCH_CONNECTING_INIT;
            wk->pMatch = CommStateWifiEnterLogin(wk->pSaveData,sizeof(TEST_MATCH_WORK));
            WifiP2PMatchMessagePrint(wk, dwc_message_0008, TRUE);
            wk->timeWaitWork = TimeWaitIconAdd( &wk->MsgWin, COMM_TALK_WIN_CGX_NUM );
            wk->bInitMessage = TRUE;
        }
        else{  // ��������I�������ꍇ
            wk->seq = WIFIP2PMATCH_MODE_END_WAIT;
        }
    }

    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   ���O�C���ڑ���  WIFIP2PMATCH_CONNECTING_INIT
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------
static int WifiP2PMatch_ConnectingInit( WIFIP2PMATCH_WORK *wk, int seq )
{
    GF_BGL_PrioritySet(GF_BGL_FRAME0_M , 3);  //�͂�����
    GF_BGL_PrioritySet(GF_BGL_FRAME1_M , 2);   //
    GF_BGL_PrioritySet(GF_BGL_FRAME3_M , 1);  // ���b�Z�[�W
    GF_BGL_PrioritySet(GF_BGL_FRAME2_M , 0);   //
    wk->seq = WIFIP2PMATCH_CONNECTING;
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   MyMatchStatus�쐬
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------
static void _makeMyMatchStatus(WIFIP2PMATCH_WORK* wk, int status)
{
    MYSTATUS* pMyStatus = SaveData_GetMyStatus(wk->pSaveData);
    ZUKAN_WORK* pZukan = SaveData_GetZukanWork(wk->pSaveData);
    POKEPARTY* pPokeParty = SaveData_GetTemotiPokemon(wk->pSaveData);
    WIFI_HISTORY* pHistry = SaveData_GetWifiHistory(wk->pSaveData);
    int max,i;

    OHNO_PRINT("_WIFI_STATUS_MAX_SIZE  %d\n",sizeof(_WIFI_MACH_STATUS));
    GF_ASSERT(_WIFI_STATUS_MAX_SIZE == sizeof(_WIFI_MACH_STATUS));

    max = PokeParty_GetPokeCount(pPokeParty);
    for(i = 0;i < max;i++){
        POKEMON_PARAM* poke = PokeParty_GetMemberPointer( pPokeParty, i);
        wk->pMatch->myMatchStatus.pokemonType[i] = PokeParaGet( poke, ID_PARA_monsno, NULL );
        wk->pMatch->myMatchStatus.hasItemType[i] = PokeParaGet( poke, ID_PARA_item, NULL );
    }
    wk->pMatch->myMatchStatus.version = MyStatus_GetRomCode(pMyStatus);
    wk->pMatch->myMatchStatus.regionCode = MyStatus_GetRegionCode(pMyStatus);
    wk->pMatch->myMatchStatus.pokemonZukan = ZukanWork_GetZenkokuZukanFlag(pZukan);
    wk->pMatch->myMatchStatus.status = status;
    wk->pMatch->myMatchStatus.regulation = _REGULATION_BATTLE_TOWER;
    wk->pMatch->myMatchStatus.trainer_view = MyStatus_GetTrainerView(pMyStatus);
    wk->pMatch->myMatchStatus.sex = MyStatus_GetMySex(pMyStatus);
    wk->pMatch->myMatchStatus.nation = WIFIHISTORY_GetMyNation(pHistry);
    wk->pMatch->myMatchStatus.area = WIFIHISTORY_GetMyArea(pHistry);
    wk->pMatch->myMatchStatus.vchat = TRUE;
    wk->pMatch->myMatchStatus.vchat_org = TRUE;

    mydwc_setMyInfo((const char *)&wk->pMatch->myMatchStatus, _WIFI_STATUS_MAX_SIZE);
    mydwc_setFriendStateBuffer(&wk->pMatch->friendMatchStatus[0], _WIFI_STATUS_MAX_SIZE);
}

//------------------------------------------------------------------
/**
 * $brief   �t�����h��status�ǂݍ���
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------

static int _readFriendMatchStatus(WIFIP2PMATCH_WORK* wk)
{
    int i,num = 0;

//    MI_CpuFill8(wk->index2No, 0, sizeof(WIFIP2PMATCH_MEMBER_MAX));
    for(i = 0;i < WIFIP2PMATCH_MEMBER_MAX;i++){
        wk->index2No[i] = 0;
        if(DWC_STATUS_OFFLINE != mydwc_getFriendStatus(i)){
            wk->index2No[num] = i+1;
            num++;
        }
    }
    return num;
}

//------------------------------------------------------------------
/**
 * $brief   �t�����h��status�����@������̏�Ԃƕς������ς��������Ԃ�
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------

static int _checkUserDataMatchStatus(WIFIP2PMATCH_WORK* wk)
{
    int i,num = 0;

    for(i = 0;i < WIFIP2PMATCH_MEMBER_MAX;i++){
        if(wk->matchStatusBackup[i]  != wk->pMatch->friendMatchStatus[i].status){

            wk->matchStatusBackup[i] = wk->pMatch->friendMatchStatus[i].status;
            // �ʐM�擾��������
            OHNO_PRINT("�ʐM�擾��������  %d %d\n", i, wk->pMatch->friendMatchStatus[i].trainer_view);
            WifiList_SetFriendInfo(wk->pList, i,
                                   WIFILIST_FRIEND_UNION_GRA,
                                   wk->pMatch->friendMatchStatus[i].trainer_view);
            WifiList_SetFriendInfo(wk->pList, i,
                                   WIFILIST_FRIEND_SEX,
                                   wk->pMatch->friendMatchStatus[i].sex);
/*            { �o�g�����Ɉꊇ�ŏ������Ă���̂ŁA��������͍폜
                WIFI_HISTORY* pHistry = SaveData_GetWifiHistory(wk->pSaveData);
                int nation = wk->pMatch->friendMatchStatus[i].nation;
                int area = wk->pMatch->friendMatchStatus[i].area;
                WIFIHIST_STAT stat = WIFIHISTORY_GetStat(pHistry, nation, area);
                if((WIFIHIST_STAT_NODATA == stat) || (WIFIHIST_STAT_NEW == stat)){
                    WIFIHISTORY_SetStat(pHistry, nation, area, stat);
                }
            } */
            num++;
        }
    }
    return num;
}

//------------------------------------------------------------------
/**
 * $brief   �G���[�\��
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------

static void _errorDispDebug(WIFIP2PMATCH_WORK* wk, int type)
{
    int msgno,no;

    no = CommStateGetWifiErrorNo();
    if((type == 11) || (no == ERRORCODE_0)){
        msgno = dwc_error_0015;
        type = 11;
    }
    else if(no == ERRORCODE_HEAP){
        msgno = dwc_error_0014;
        type = 12;
    }
    else{
        msgno = dwc_error_0001 + type;
    }
    OHNO_PRINT("�G���[���b�Z�[�W %d \n",msgno);
    EndMessageWindowOff(wk);
    WORDSET_RegisterNumber(wk->WordSet, 0, CommStateGetWifiErrorNo(),
                           5, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);

	// ���ʉ��̎�����񕶎�����N���A����
    _systemMessagePrint(wk, msgno);

    switch(type){
      case 1:
      case 4:
      case 5:
      case 11:
        wk->seq = WIFIP2PMATCH_RETRY_INIT;  // �Đڑ����t�B�[���h��
        break;
      case 6:
      case 7:
      case 8:
      case 9:
        wk->seq = WIFIP2PMATCH_RETRY_INIT;//WIFIP2PMATCH_POWEROFF_INIT;  // �d����؂邩�t�B�[���h
        break;
      case 10:
        wk->seq = WIFIP2PMATCH_RETRY_INIT;  // ���j���[�ꗗ��
        break;
      case 0:
      case 2:
      case 3:
      default:
        wk->seq = WIFIP2PMATCH_MODE_CHECK_AND_END;  // �t�B�[���h
        break;
    }
}

static void _errorDisp(WIFIP2PMATCH_WORK* wk)
{
    int type =  mydwc_errorType(CommStateGetWifiErrorNo());
    _errorDispDebug(wk, type);
#if 0
    //   _myStatusChange(wk, WIFI_STATUS_LOGIN_WAIT);  // �����ł͌Ă΂Ȃ����ɂȂ�܂��� 8/11

	// �����X�e�[�^�X�\����OFF�ɂ���( 2006/08/10 by Mori)
    if(GF_BGL_BmpWinAddCheck(&wk->MyInfoWin)){
		GF_BGL_BmpWinOff( &wk->MyInfoWin );
	}
#endif
}


//------------------------------------------------------------------
/**
 * $brief   �d����؂���WIFI�ݒ��  WIFIP2PMATCH_POWEROFF_INIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _poweroffInit( WIFIP2PMATCH_WORK *wk, int seq )
{
// WIFI�ݒ�ɍs���Ȃ��悤��

    if(sys.trg & (PAD_BUTTON_CANCEL|PAD_BUTTON_DECIDE)){
        if(GF_BGL_BmpWinAddCheck(&wk->SysMsgWin)){
            BmpTalkWinClear(&wk->SysMsgWin, WINDOW_TRANS_ON );
            GF_BGL_BmpWinDel( &wk->SysMsgWin );
        }
//        WifiP2PMatchMessagePrint(wk, msg_wifilobby_051, FALSE);
        wk->seq = WIFIP2PMATCH_POWEROFF_YESNO;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �d����؂���WIFI�ݒ��  WIFIP2PMATCH_POWEROFF_YESNO
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int _poweroffYesNo( WIFIP2PMATCH_WORK *wk, int seq )
{
// WIFI�ݒ�ɍs���Ȃ��悤��
/*    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        // �͂��������E�C���h�E���o��
        wk->pYesNoWork =
            BmpYesNoSelectInit( wk->bgl,
                                &_yesNoBmpDat,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                HEAPID_WIFIP2PMATCH );
        wk->seq = WIFIP2PMATCH_POWEROFF_WAIT;
    }*/
    wk->seq = WIFIP2PMATCH_POWEROFF_WAIT;
    return seq;
}


//------------------------------------------------------------------
/**
 * $brief   �d����؂���WIFI�ݒ��  WIFIP2PMATCH_POWEROFF_WAIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int _poweroffWait( WIFIP2PMATCH_WORK *wk, int seq )
{
// WIFI�ݒ�ɍs���Ȃ��悤��
    /*
    int i;
    int ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);
    if(ret == BMPMENU_NULL){  // �܂��I��
        return seq;
    }else if(ret == 0){ // �͂���I�������ꍇ
        CommStateWifiLogout();
        wk->endSeq = WIFI_P2PMATCH_UTIL;   //�\�t�g�E�G�A���Z�b�g
        wk->seq = WIFIP2PMATCH_MODE_END_WAIT;
        EndMessageWindowOff(wk);
    }
    else{  // ��������I�������ꍇ
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_052, FALSE);
        wk->seq = WIFIP2PMATCH_RETRY_YESNO;
    }
*/
    wk->seq = WIFIP2PMATCH_RETRY_YESNO;
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �ڑ������g���C����  WIFIP2PMATCH_RETRY_INIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _retryInit( WIFIP2PMATCH_WORK *wk, int seq )
{
    if(sys.trg & (PAD_BUTTON_CANCEL|PAD_BUTTON_DECIDE)){
        if(GF_BGL_BmpWinAddCheck(&wk->SysMsgWin)){
            BmpTalkWinClear(&wk->SysMsgWin, WINDOW_TRANS_ON );
            GF_BGL_BmpWinDel( &wk->SysMsgWin );
        }
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_052, FALSE);
        wk->seq = WIFIP2PMATCH_RETRY_YESNO;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �ڑ������g���C����  WIFIP2PMATCH_RETRY_YESNO
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int _retryYesNo( WIFIP2PMATCH_WORK *wk, int seq )
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        // �͂��������E�C���h�E���o��
        wk->pYesNoWork =
            BmpYesNoSelectInit( wk->bgl,
                                &_yesNoBmpDat,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                HEAPID_WIFIP2PMATCH );
        wk->seq = WIFIP2PMATCH_RETRY_WAIT;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �ڑ������g���C����  WIFIP2PMATCH_RETRY_WAIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int _retryWait( WIFIP2PMATCH_WORK *wk, int seq )
{
    int i;
    int ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);
    if(ret == BMPMENU_NULL){  // �܂��I��
        return seq;
    }else if(ret == 0){ // �͂���I�������ꍇ
        CommStateWifiLogout();
        _myStatusChange(wk, WIFI_STATUS_LOGIN_WAIT);
        wk->seq = WIFIP2PMATCH_RETRY;
    }
    else{  // ��������I�������ꍇ
        CommStateWifiLogout();
        CommInfoFinalize();   //Info������
        wk->endSeq = WIFI_P2PMATCH_END;
        wk->seq = WIFIP2PMATCH_MODE_END_WAIT;
    }
    EndMessageWindowOff(wk);
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �ڑ������g���C  WIFIP2PMATCH_RETRAY
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int _retry( WIFIP2PMATCH_WORK *wk, int seq )
{
    int i;
    
    if(!CommIsVRAMDInitialize()){
        //�ڑ��J�n
        GF_BGL_ScrClear(wk->bgl, GF_BGL_FRAME3_M);
        ArcUtil_ScrnSet(   ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_01_NSCR, wk->bgl,
                           GF_BGL_FRAME0_M, 0, 0, 0, HEAPID_WIFIP2PMATCH);

        if( wk->menulist){
            GF_BGL_BmpWinDel(&wk->ListWin);
            BmpListExit(wk->lw, NULL, NULL);
            wk->lw=NULL;
            BMP_MENULIST_Delete( wk->menulist );
            wk->menulist=NULL;
        }
        wk->friendMatchReadCount;
        MI_CpuClear8(wk->index2No, WIFIP2PMATCH_MEMBER_MAX);
        MI_CpuClear8(wk->matchStatusBackup, WIFIP2PMATCH_MEMBER_MAX*sizeof(int));
        for(i=0;i < _OAM_NUM;i++){
            CLACT_SetDrawFlag( wk->MainActWork[i], 0 );
        }
        MainMenuMsgInit(wk);
        wk->pMatch = CommStateWifiEnterLogin(wk->pSaveData,sizeof(TEST_MATCH_WORK));
        WifiP2PMatchMessagePrint(wk, dwc_message_0008, TRUE);
        wk->timeWaitWork = TimeWaitIconAdd( &wk->MsgWin, COMM_TALK_WIN_CGX_NUM );
        wk->seq = WIFIP2PMATCH_CONNECTING_INIT;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   ���O�C���ڑ���  WIFIP2PMATCH_CONNECTING
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------
static int WifiP2PMatch_Connecting( WIFIP2PMATCH_WORK *wk, int seq )
{
    int i;

    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) != 0 ){
        return seq;
    }
    if(CommStateIsWifiLoginState()){
        OHNO_PRINT("WIFI�ڑ�����\n");
        if( wk->bInitMessage ){  // ����ڑ����ɂ̓Z�[�u�V�[�P���X��
//            SaveData_SaveParts(wk->pSaveData, SVBLK_ID_NORMAL);  //�Z�[�u��
            wk->seq = WIFIP2PMATCH_FIRST_ENDMSG;
        }
        else{
            _makeMyMatchStatus(wk, WIFI_STATUS_LOGIN_WAIT);
            _readFriendMatchStatus( wk );
            wk->seq = WIFIP2PMATCH_FRIENDLIST_INIT;
        }
    }
    else if(CommStateIsWifiError() || (CommWifiIsMatched() == 3)){
        _errorDisp(wk);
    }
    return seq;
}






//------------------------------------------------------------------
/**
 * $brief   �ؒf�{VCT�҂��Ɉڍs����܂ő҂�  WIFIP2PMATCH_RECONECTING_WAIT
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------
static int WifiP2PMatch_ReConnectingWait( WIFIP2PMATCH_WORK *wk, int seq )
{
    int i;

    if(wk->timer > 0){
        wk->timer--;
        return seq;
    }

    OHNO_PRINT("CommStateIsWifiLoginState %d  \n",CommStateIsWifiLoginState());
    OHNO_PRINT("CommWifiIsMatched %d  \n",CommWifiIsMatched());
    OHNO_PRINT("CommStateIsWifiDisconnect %d  \n",CommStateIsWifiDisconnect());
    OHNO_PRINT("CommIsConnect %d  \n",CommIsConnect(COMM_PARENT_ID));

    if(CommStateIsWifiLoginMatchState()){
        OHNO_PRINT("WIFI�ڑ�����\n");
        wk->seq = WIFIP2PMATCH_FRIENDLIST_INIT;
    }
    else if((CommWifiIsMatched() >= 4) || CommStateIsWifiDisconnect() || !CommIsConnect(COMM_PARENT_ID)){
        CommStateWifiMatchEnd();
        wk->seq = WIFIP2PMATCH_FRIENDLIST_INIT;
    }
    else if(CommStateIsWifiError() || (CommWifiIsMatched() == 3)){
        _errorDisp(wk);
    }
    return seq;
}




//------------------------------------------------------------------
/**
 * $brief   �ŏ��ڑ�����  WIFIP2PMATCH_FIRST_ENDMSG
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------

static int _firstConnectEndMsg( WIFIP2PMATCH_WORK *wk, int seq )
{
    EndMessageWindowOff(wk);
    _systemMessagePrint(wk, dwc_message_0004);
    wk->seq = WIFIP2PMATCH_FIRST_ENDMSG_WAIT;
    return seq;

}

//WIFIP2PMATCH_FIRST_ENDMSG_WAIT
static int _firstConnectEndMsgWait( WIFIP2PMATCH_WORK *wk, int seq )
{
    if(sys.trg & (PAD_BUTTON_CANCEL|PAD_BUTTON_DECIDE)){
        if(wk->initSeq == WIFI_P2PMATCH_DPW){ // ���E�ΐ�Ȃ�
            wk->endSeq = WIFI_P2PMATCH_DPW_END;   // �I��������
            wk->seq = WIFIP2PMATCH_MODE_END_WAIT;
            CommStateWifiLogout();
        }
        else if( 0==WifiList_GetFriendDataNum(wk->pList) ){  //�t�����h�����Ȃ�
            WifiP2PMatchMessagePrint(wk, dwc_message_0011, TRUE);
            wk->seq = WIFIP2PMATCH_MODE_EXITING;
            wk->timer = 1;
        }
        else{
            _makeMyMatchStatus(wk, WIFI_STATUS_LOGIN_WAIT);
            _readFriendMatchStatus( wk );
            wk->seq = WIFIP2PMATCH_FRIENDLIST_INIT;
            if(GF_BGL_BmpWinAddCheck(&wk->SysMsgWin)){
                BmpTalkWinClear(&wk->SysMsgWin, WINDOW_TRANS_ON );
                GF_BGL_BmpWinDel( &wk->SysMsgWin );
            }
        }
    }
    return seq;

}

//------------------------------------------------------------------
/**
 * $brief   �����̏�Ԃ�\��
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static void	_userDataInfoDisp(WIFIP2PMATCH_WORK * wk)
{
    int col = _COL_N_BLACK,sex;
    MYSTATUS* pMy = SaveData_GetMyStatus(wk->pSaveData);
    STRBUF* pSTRBUF = MyStatus_CreateNameString(pMy, HEAPID_WIFIP2PMATCH);

    if(!GF_BGL_BmpWinAddCheck(&wk->MyInfoWin)){
        STRBUF_Delete(pSTRBUF);
        return;
    }

    //BMP�E�B���h�E����
//    GF_BGL_BmpWinAdd(wk->bgl,&wk->MyInfoWin,
//                     GF_BGL_FRAME3_M, 7, 21, 21, 2,
//                     FLD_SYSFONT_PAL, _CGX_BOTTOM - 18*3 - 21*2 );
    GF_BGL_BmpWinDataFill( &wk->MyInfoWin, 0x8000 );
    GF_STR_PrintColor( &wk->MyInfoWin, FONT_SYSTEM,
                       pSTRBUF, 0, 0,
                       MSG_NO_PUT, _COL_N_BLACK, NULL);
    STRBUF_Delete(pSTRBUF);

    switch(wk->pMatch->myMatchStatus.status){
      case WIFI_STATUS_VCT:      // VCT��
        col = _COL_N_GRAY;
        if(mydwc_getFriendIndex() == -1){
            MSGMAN_GetString(wk->MsgManager, msg_wifilobby_027, wk->pExpStrBuf);
        }
        else{
            sex = WifiList_GetFriendInfo(wk->pList, mydwc_getFriendIndex(), WIFILIST_FRIEND_SEX);
            if( PM_MALE == sex){
                col = _COL_N_BLUE;
            }
            else if( PM_FEMALE == sex){
                col = _COL_N_RED;
            }
            STRBUF_SetStringCode(wk->pExpStrBuf ,WifiList_GetFriendNamePtr(wk->pList,mydwc_getFriendIndex()));
        }
        break;
      case WIFI_STATUS_SBATTLE50:      // �ΐ풆
      case WIFI_STATUS_SBATTLE100:      // �ΐ풆
      case WIFI_STATUS_SBATTLE_FREE:      // �ΐ풆
      case WIFI_STATUS_DBATTLE50:      // �ΐ풆
      case WIFI_STATUS_DBATTLE100:      // �ΐ풆
      case WIFI_STATUS_DBATTLE_FREE:      // �ΐ풆
        MSGMAN_GetString(wk->MsgManager, msg_wifilobby_024, wk->pExpStrBuf);
        col = _COL_N_GRAY;
        break;
      case WIFI_STATUS_SBATTLE50_WAIT:   // �ΐ��W��
        MSGMAN_GetString(wk->MsgManager, msg_wifilobby_060, wk->pExpStrBuf);
        break;
      case WIFI_STATUS_SBATTLE100_WAIT:   // �ΐ��W��
        MSGMAN_GetString(wk->MsgManager, msg_wifilobby_061, wk->pExpStrBuf);
        break;
      case WIFI_STATUS_SBATTLE_FREE_WAIT:   // �ΐ��W��
        MSGMAN_GetString(wk->MsgManager, msg_wifilobby_059, wk->pExpStrBuf);
        break;
      case WIFI_STATUS_DBATTLE50_WAIT:   // �ΐ��W��
        MSGMAN_GetString(wk->MsgManager, msg_wifilobby_063, wk->pExpStrBuf);
        break;
      case WIFI_STATUS_DBATTLE100_WAIT:   // �ΐ��W��
        MSGMAN_GetString(wk->MsgManager, msg_wifilobby_064, wk->pExpStrBuf);
        break;
      case WIFI_STATUS_DBATTLE_FREE_WAIT:   // �ΐ��W��
        MSGMAN_GetString(wk->MsgManager, msg_wifilobby_062, wk->pExpStrBuf);
        break;
      case WIFI_STATUS_TRADE:          // ������
        MSGMAN_GetString(wk->MsgManager, msg_wifilobby_026, wk->pExpStrBuf);
        col = _COL_N_GRAY;
        break;
      case WIFI_STATUS_TRADE_WAIT:    // ������W��
        MSGMAN_GetString(wk->MsgManager, msg_wifilobby_025, wk->pExpStrBuf);
        break;
      case WIFI_STATUS_LOGIN_WAIT:    // �ҋ@���@���O�C������͂���
        MSGMAN_GetString(wk->MsgManager, msg_wifilobby_046, wk->pExpStrBuf);
        break;
      default:
        return;
        break;
    }
    {
        int length = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->pExpStrBuf, 0 );
        int x      = 156 - length;

      //  GF_BGL_BmpWinDataFill( &wk->MyInfoWin, 0x8000 );
        GF_STR_PrintColor( &wk->MyInfoWin, FONT_SYSTEM, wk->pExpStrBuf,
                           x, 0, MSG_NO_PUT, col, NULL);
    }
    GF_BGL_BmpWinOnVReq(&wk->MyInfoWin);
}

//------------------------------------------------------------------
/**
 * $brief   �ꃉ�C���R�[���o�b�N
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static void	_lineCallBack(BMPLIST_WORK * lw, u32 param, u8 y)
{
    WIFIP2PMATCH_WORK* wk = (WIFIP2PMATCH_WORK*)BmpListParamGet(lw,BMPLIST_ID_WORK);
    int gmmNo = 0,col = _COL_N_BLACK;

    if((param == WIFIP2PMATCH_MEMBER_MAX) || (param == BMPLIST_CANCEL)){
        return;
    }
    switch(wk->pMatch->friendMatchStatus[param].status){
      case WIFI_STATUS_VCT:      // VCT��
        gmmNo = msg_wifilobby_027;
        col = _COL_N_GRAY;
        break;
      case WIFI_STATUS_SBATTLE50:      // �ΐ풆
      case WIFI_STATUS_SBATTLE100:      // �ΐ풆
      case WIFI_STATUS_SBATTLE_FREE:      // �ΐ풆
      case WIFI_STATUS_DBATTLE50:      // �ΐ풆
      case WIFI_STATUS_DBATTLE100:      // �ΐ풆
      case WIFI_STATUS_DBATTLE_FREE:      // �ΐ풆
        gmmNo = msg_wifilobby_024;
        col = _COL_N_GRAY;
        break;
      case WIFI_STATUS_SBATTLE50_WAIT:   // �ΐ��W��
        gmmNo = msg_wifilobby_060;
        break;
      case WIFI_STATUS_SBATTLE100_WAIT:   // �ΐ��W��
        gmmNo = msg_wifilobby_061;
        break;
      case WIFI_STATUS_SBATTLE_FREE_WAIT:   // �ΐ��W��
        gmmNo = msg_wifilobby_059;
        break;
      case WIFI_STATUS_DBATTLE50_WAIT:   // �ΐ��W��
        gmmNo = msg_wifilobby_063;
        break;
      case WIFI_STATUS_DBATTLE100_WAIT:   // �ΐ��W��
        gmmNo = msg_wifilobby_064;
        break;
      case WIFI_STATUS_DBATTLE_FREE_WAIT:   // �ΐ��W��
        gmmNo = msg_wifilobby_062;
        break;
      case WIFI_STATUS_TRADE:          // ������
        gmmNo = msg_wifilobby_026;
        col = _COL_N_GRAY;
        break;
      case WIFI_STATUS_TRADE_WAIT:    // ������W��
        gmmNo = msg_wifilobby_025;
        break;
      case WIFI_STATUS_LOGIN_WAIT:    // �ҋ@���@���O�C������͂���
        gmmNo = msg_wifilobby_046;
        break;
      case WIFI_STATUS_UNKNOWN:
      default:
        gmmNo = msg_wifilobby_056;
        break;
    }
    OHNO_PRINT("�����R�[���o�b�N�Ăт��� %d %d %d\n",param,y,gmmNo);

    if(gmmNo != 0){
        MSGMAN_GetString(wk->MsgManager, gmmNo, wk->pExpStrBuf);

        {
            int length = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->pExpStrBuf, 0 );
            int x      = 164 - length;

            GF_STR_PrintColor( &wk->ListWin, FONT_SYSTEM, wk->pExpStrBuf,
                               x, y, MSG_NO_PUT, col, NULL);
            GF_BGL_BmpWinOnVReq(&wk->ListWin);
        }
    }

    {
        int sex = WifiList_GetFriendInfo(wk->pList, param, WIFILIST_FRIEND_SEX);
        col = _COL_N_BLACK;
        if( PM_MALE == sex){
            col = _COL_N_BLUE;
        }
        else if( PM_FEMALE == sex){
            col = _COL_N_RED;
        }

        GF_STR_PrintColor( &wk->ListWin, FONT_SYSTEM, wk->TrainerName[param],
                           8, y, MSG_NO_PUT, col, NULL);
        GF_BGL_BmpWinOnVReq(&wk->ListWin);
    }
}

//------------------------------------------------------------------
/**
 * $brief   �A�C�R���\��
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static void	_iconDisp(WIFIP2PMATCH_WORK * wk, int status, int vctIcon, int x,int y,int x2)
{
    u16 btl[]={ 0x17,0x18,0xc18,0x20 };  //�΂Ƃ�
    u16 chg[]={ 0x25,0x26,0x2a,0xc25 };  //��������
    u16 wai[]={ 0x2f,0x42f,0x82f,0xc2f };  //������
    u16 vct[]={ 0x4a,0x4b,0x084a,0x084b };  //VCT
    u16 vctoff[]={ 0x48,0x49,0x0848,0x0849 };  //VCToff
    u16 hate[]={ 0x44,0x45,0x46,0x47 };  //?
    u16 none[]={ 0x6,0x6,0x6,0x6 };  //none
    u16* pData;
    // 0x06-----------�Ȃ�
    u16* pScrAddr = GF_BGL_ScreenAdrsGet( wk->bgl, GF_BGL_FRAME0_M );
    int pos,col = 0;

    switch(status){
      case WIFI_STATUS_VCT:      // VCT��
        pData = vct;
        break;
      case WIFI_STATUS_SBATTLE50_WAIT:   // �ΐ��W��
      case WIFI_STATUS_SBATTLE100_WAIT:   // �ΐ��W��
      case WIFI_STATUS_SBATTLE_FREE_WAIT:   // �ΐ��W��
      case WIFI_STATUS_DBATTLE50_WAIT:   // �ΐ��W��
      case WIFI_STATUS_DBATTLE100_WAIT:   // �ΐ��W��
      case WIFI_STATUS_DBATTLE_FREE_WAIT:   // �ΐ��W��
        col = 0x1000;
      case WIFI_STATUS_SBATTLE50:      // �ΐ풆
      case WIFI_STATUS_SBATTLE100:      // �ΐ풆
      case WIFI_STATUS_SBATTLE_FREE:      // �ΐ풆
      case WIFI_STATUS_DBATTLE50:      // �ΐ풆
      case WIFI_STATUS_DBATTLE100:      // �ΐ풆
      case WIFI_STATUS_DBATTLE_FREE:      // �ΐ풆
        pData = btl;
        break;
      case WIFI_STATUS_TRADE_WAIT:    // ������W��
        col = 0x1000;
      case WIFI_STATUS_TRADE:          // ������
        pData = chg;
        break;
      case WIFI_STATUS_LOGIN_WAIT:    // �ҋ@���@���O�C������͂���
        pData = wai;
        break;
      case WIFI_STATUS_UNKNOWN:
        pData = hate;
        break;
      default:
        pData = none;
        break;
    }

    pos = x + y * 32;
    pScrAddr[pos] = pData[0]+col;
    pScrAddr[pos+1] = pData[1]+col;
    pScrAddr[pos+32] = pData[2]+col;
    pScrAddr[pos+33] = pData[3]+col;

    if(vctIcon){
        pData = none;
    }
    else{
        pData = vctoff;
    }
    pos = x2 + y * 32;
    pScrAddr[pos] = pData[0];
    pScrAddr[pos+1] = pData[1];
    pScrAddr[pos+32] = pData[2];
    pScrAddr[pos+33] = pData[3];
}

//------------------------------------------------------------------
/**
 * $brief   ���\�����Ƃ̃R�[���o�b�N�֐�
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static void	_iconMenuDisp(WIFIP2PMATCH_WORK * wk, int toppos)
{
    u16* pData;
    // 0x06-----------�Ȃ�
    u16* pScrAddr = GF_BGL_ScreenAdrsGet( wk->bgl, GF_BGL_FRAME0_M );
    int pos,status,i,vchat;


    for(i = 0; i < WIFIP2PMATCH_DISP_MEMBER_MAX;i++){
        pos = toppos + i;
        if(pos >= WIFIP2PMATCH_MEMBER_MAX){
            status = WIFI_STATUS_NONE;
            vchat = 1;
        }
        else if(wk->index2No[pos]==0){
            status = WIFI_STATUS_NONE;
            vchat = 1;
        }
        else{
            status = wk->pMatch->friendMatchStatus[wk->index2No[pos] - 1].status;
            vchat = wk->pMatch->friendMatchStatus[wk->index2No[pos] - 1].vchat;
        }
        pos = 3 + ((5+(i*3)) * 32);
        _iconDisp(wk, status, vchat, 3, 5+(i*3), 27);
    }
    status = wk->pMatch->myMatchStatus.status;
    vchat = wk->pMatch->myMatchStatus.vchat;
    if(wk->pMatch->myMatchStatus.status == WIFI_STATUS_VCT){
        status = WIFI_STATUS_NONE;
    }
    _iconDisp(wk, status, vchat, 3, 21, 27);
    GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME0_M);  // �X�N���[���ɍX�V
}

//------------------------------------------------------------------
/**
 * $brief   �J�[�\���R�[���o�b�N
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static void _curCallBack(BMPLIST_WORK * wk,u32 param,u8 mode)
{
    if(mode == 0){
        Snd_SePlay(_SE_CURSOR);
    }
}


///�I�����j���[�̃��X�g
static const BMPLIST_HEADER _friendInfoMenuListHeader = {
    NULL,			// �\�������f�[�^�|�C���^
    _curCallBack,					// �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
    _lineCallBack,					// ���\�����Ƃ̃R�[���o�b�N�֐�
    NULL,                   // GF_BGL_BMPWIN
    (WIFIP2PMATCH_MEMBER_MAX+2),	// ���X�g���ڐ�
    WIFIP2PMATCH_DISP_MEMBER_MAX,	// �\���ő區�ڐ�
    0,						// ���x���\���w���W
    8,						// ���ڕ\���w���W
    0,						// �J�[�\���\���w���W
    0,						// �\���x���W
    FBMP_COL_BLACK,			// �����F
    0x8000,			// �w�i�F �ʂ��H
    FBMP_COL_BLK_SDW,		// �����e�F
    0,						// �����Ԋu�w
    24,						// �����Ԋu�x
    BMPLIST_LRKEY_SKIP,		// �y�[�W�X�L�b�v�^�C�v
    FONT_SYSTEM,				// �����w��
    1,						// �a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
    NULL                    // work
    };

static int _addListString(WIFIP2PMATCH_WORK* wk)
{
    int i,num=0;

    for(i = 0; i < WIFIP2PMATCH_MEMBER_MAX; i++){
        if( wk->index2No[i] != 0){
            BMP_MENULIST_AddString( wk->menulist, wk->pTemp, wk->index2No[i] - 1 );
            //            BMP_MENULIST_AddString( wk->menulist, wk->TrainerName[wk->index2No[i] - 1], wk->index2No[i] - 1 );
            num++;
        }
    }
    BMP_MENULIST_AddArchiveString( wk->menulist, wk->MsgManager,
                                   msg_wifilobby_028, WIFIP2PMATCH_MEMBER_MAX );
    BMP_MENULIST_AddArchiveString( wk->menulist, wk->MsgManager,
                                   msg_wifilobby_047, BMPLIST_CANCEL );
    return num;
}

static void _menuFriendList(WIFIP2PMATCH_WORK* wk)
{
    int i,num = 0;
    BMPLIST_HEADER list_h;

    wk->menulist = BMP_MENULIST_Create( WIFIP2PMATCH_MEMBER_MAX+2, HEAPID_WIFIP2PMATCH );


    num = _addListString(wk);

    if(GF_BGL_BmpWinAddCheck(&wk->ListWin)){
        BmpTalkWinClear( &wk->ListWin, WINDOW_TRANS_ON );
        GF_BGL_BmpWinDel(&wk->ListWin);
    }
    //BMP�E�B���h�E����
    GF_BGL_BmpWinAdd(wk->bgl,&wk->ListWin,
                     GF_BGL_FRAME3_M, 6, 5, 21, 14, FLD_SYSFONT_PAL, 1);


    list_h = _friendInfoMenuListHeader;
    list_h.list = wk->menulist;
    list_h.win = &wk->ListWin;
    list_h.count = num + 2;
    list_h.work = wk;
    wk->lw = BmpListSet(&list_h, 0, 0, HEAPID_WIFIP2PMATCH);


}

//------------------------------------------------------------------
/**
 * $brief   �t�����h���X�g�\��������   WIFIP2PMATCH_FRIENDLIST_INIT
 *
 * @param   wk
 *
 * @retval  none
 */
//------------------------------------------------------------------

static void _userDataDisp(WIFIP2PMATCH_WORK* wk)
{
    if(GF_BGL_BmpWinAddCheck(&wk->MyInfoWin)){
        BmpTalkWinClear( &wk->MyInfoWin, WINDOW_TRANS_ON );
        GF_BGL_BmpWinDel(&wk->MyInfoWin);
    }
    GF_BGL_BmpWinAdd(wk->bgl,&wk->MyInfoWin,
                     GF_BGL_FRAME3_M, 7, 21, 21, 2,
                     FLD_SYSFONT_PAL, _CGX_BOTTOM - 18*3 - 21*2 );

}

//------------------------------------------------------------------
/**
 * $brief   �t�����h���X�g�\��������   WIFIP2PMATCH_FRIENDLIST_INIT
 *
 * @param   wk
 *
 * @retval  none
 */
//------------------------------------------------------------------

static int WifiP2PMatch_FriendListInit( WIFIP2PMATCH_WORK *wk, int seq )
{
    int i,x;
    int num = 0;

    _myVChatStatusOrgSet(wk);
    _timeWaitIconDel(wk);
    GF_BGL_ScrClear(wk->bgl, GF_BGL_FRAME3_M);
    ArcUtil_ScrnSet(   ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_02_NSCR, wk->bgl,
                       GF_BGL_FRAME0_M, 0, 0, 0, HEAPID_WIFIP2PMATCH);

    if(GF_BGL_BmpWinAddCheck(&wk->TitleWin)){
        BmpMenuWinClear(&wk->TitleWin, WINDOW_TRANS_ON);
        GF_BGL_BmpWinDel(&wk->TitleWin);
    }
    if(wk->menulist){
        GF_BGL_BmpWinDel(&wk->ListWin);
        BmpListExit(wk->lw, NULL, NULL);
        wk->lw = NULL;
        BMP_MENULIST_Delete( wk->menulist );
        wk->menulist = NULL;
    }

    GF_BGL_BmpWinAdd(wk->bgl, &wk->TitleWin, GF_BGL_FRAME3_M, 4, 1, 21, 2,
                     _NUKI_FONT_PALNO,  _CGX_BOTTOM - 18*3 );
    GF_BGL_BmpWinDataFill( &wk->TitleWin, 0x8000 );
    MSGMAN_GetString(  wk->MsgManager, msg_wifilobby_019, wk->TitleString );
    GF_STR_PrintColor( &wk->TitleWin, FONT_TALK, wk->TitleString, 0, 0, MSG_NO_PUT, _COL_N_WHITE, NULL);
    GF_BGL_BmpWinOnVReq(&wk->TitleWin);
    EndMessageWindowOff(wk);
    _readFriendMatchStatus(wk);

    _menuFriendList(wk);


    _userDataDisp(wk);
    _iconMenuDisp(wk,0);

// WIFI�@�ΐ�AUTOӰ�ރf�o�b�N
#ifndef _WIFI_DEBUG_TUUSHIN
    _myStatusChange(wk, WIFI_STATUS_LOGIN_WAIT);
#else	//_WIFI_DEBUG_TUUSHIN

	if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_BATTLE == FALSE ){
		
		if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MODE == _WIFI_DEBUG_MODE_X ){
			_myStatusChange(wk, WIFI_STATUS_SBATTLE50_WAIT);
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_A_REQ = FALSE;
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_B_REQ = FALSE;
		}else{
			_myStatusChange(wk, WIFI_STATUS_LOGIN_WAIT);
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_A_REQ = TRUE;
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_B_REQ = FALSE;
		}

		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_BATTLE = TRUE;
	}else{
		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_BATTLE = FALSE;
		_myStatusChange(wk, WIFI_STATUS_LOGIN_WAIT);
	}
#endif	//_WIFI_DEBUG_TUUSHIN

    wk->preConnect = -1;
    mydwc_ResetNewPlayer();
    CLACT_SetDrawFlag( wk->MainActWork[_CLACT_LINE_CUR], 1 );
    wk->seq = WIFIP2PMATCH_MODE_FRIENDLIST;
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �N�����ڑ����Ă����ꍇ
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _checkParentConnect(WIFIP2PMATCH_WORK *wk)
{
    if( CommWifiIsMatched()==1 ){
        return TRUE;
    }
    return FALSE;
}

//------------------------------------------------------------------
/**
 * $brief   ���C�����X�g�̏�������
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static void _mainListReWrite(WIFIP2PMATCH_WORK *wk)
{
    int num,num2,checkMatch;
    u16 list,cursor;

    num = _readFriendMatchStatus(wk);
    num2 = _checkUserDataMatchStatus(wk);
    if((wk->friendMatchReadCount != num) || (num2 != 0)){
        OHNO_PRINT("�l�����ς���� %d %d\n", num, num2);
        //_readFriendMatchStatus(wk);  //�Čv�Z
        BMP_MENULIST_STRBUFDelete(wk->menulist);
        //BMP_MENULIST_Delete(wk->menulist);
        //wk->menulist = BMP_MENULIST_Create( WIFIP2PMATCH_MEMBER_MAX+2, HEAPID_WIFIP2PMATCH );
        BmpListParamSet(wk->lw ,BMPLIST_ID_COUNT, num + 2);
        if(num > (WIFIP2PMATCH_DISP_MEMBER_MAX-2)){
            BmpListParamSet(wk->lw ,BMPLIST_ID_LINE, WIFIP2PMATCH_DISP_MEMBER_MAX);
        }
        else{
            BmpListParamSet(wk->lw ,BMPLIST_ID_LINE, num+2);
        }
        _addListString(wk);

	// �u������@����v�̉��ɋ󔒍s���o����̂�}��
	BmpListPosGet(wk->lw, &list, &cursor);
	if(num >= 3 && (num - 3) <= list){
	  list = num - 3;
	  if(list < 0)
	    list = 0;
	}
        BmpListMainOutControl(wk->lw, NULL,list,cursor,0,NULL,NULL);
	
        BmpListRewrite(wk->lw);
        wk->friendMatchReadCount = num;
    }

    BmpListPosGet(wk->lw, &list, &cursor);
    // �J�[�\���ʒu�̍ĕ\��
    if((wk->friendMatchReadCount+2) <= (list+cursor)){
      while((wk->friendMatchReadCount+2) <= (list+cursor)){
        if(list != 0){
	  list--;
        }
        else if(cursor != 0){
	  cursor--;
        }
      }
      OHNO_PRINT("�J�[�\���ʒu�ύX %d %d \n",list,cursor);
      BmpListMainOutControl(wk->lw, NULL,list,cursor,0,NULL,NULL);
      BmpListRewrite(wk->lw);
    }

    _iconMenuDisp(wk, list);
    SetCursor_Pos(wk->MainActWork[_CLACT_LINE_CUR], 2*8, 8 * (cursor * 3 + 6));

    if(list > 0){    // ��J�[�\��
        SetCursor_Pos(wk->MainActWork[_CLACT_UP_CUR], 0x80, 32);
        CLACT_SetDrawFlag( wk->MainActWork[_CLACT_UP_CUR], 1 );
    }
    else{
        CLACT_SetDrawFlag( wk->MainActWork[_CLACT_UP_CUR], 0 );
    }
    if((list < (wk->friendMatchReadCount - WIFIP2PMATCH_DISP_MEMBER_MAX + 2))){
        SetCursor_Pos(wk->MainActWork[_CLACT_DOWN_CUR], 0x80, 0x9c);
        CLACT_SetDrawFlag( wk->MainActWork[_CLACT_DOWN_CUR], 1 );
    }
    else{
        CLACT_SetDrawFlag( wk->MainActWork[_CLACT_DOWN_CUR], 0 );
    }
}


//------------------------------------------------------------------
/**
 * $brief   �t�����h���X�g�\�������� WIFIP2PMATCH_MODE_FRIENDLIST
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int WifiP2PMatch_FriendList( WIFIP2PMATCH_WORK *wk, int seq )
{
    u32	ret = BMPLIST_NULL;
    u16 list,cursor;
    int num,num2,checkMatch;

    _mainListReWrite(wk);

#if 0
#ifdef DEBUG_ONLY_FOR_ohno
    if(PAD_BUTTON_Y & sys.trg){
        _errorDispDebug(wk, 11);
        return seq;
    }
#endif
#endif
#ifdef PM_DEBUG  // �f�o�b�O�@�\
    if(PAD_BUTTON_L & sys.trg){
        if(mydwc_toggleDelay()){
            WifiP2PMatchMessagePrint(wk, msg_wifilobby_test_002, FALSE);
        }
        else{
            WifiP2PMatchMessagePrint(wk, msg_wifilobby_test_003, FALSE);
        }
        wk->seq = WIFIP2PMATCH_VCHATWIN_WAIT;
        return seq;
    }
#endif

    if(mydwc_IsNewPlayer() == -1){
        if(PAD_BUTTON_X & sys.trg){
            if(_myVChatStatusToggleOrg(wk)){
                WifiP2PMatchMessagePrint(wk, msg_wifilobby_054, FALSE);
            }
            else{
                WifiP2PMatchMessagePrint(wk, msg_wifilobby_055, FALSE);
            }
            Snd_SePlay(_SE_DESIDE);
            wk->seq = WIFIP2PMATCH_VCHATWIN_WAIT;
            return seq;
        }
    }

    if(CommStateIsWifiError()){
//        wk->localTime=0;
        _errorDisp(wk);
        return seq;
    }
    checkMatch = _checkParentConnect(wk);
    if( 0 !=  checkMatch ){ // �ڑ����Ă���
        OHNO_PRINT("�ڑ����E���Ă��܂��Ă���-------------\n");
        Snd_SePlay(_SE_OFFER);
        wk->seq = WIFIP2PMATCH_MODE_CALL_INIT;
        return seq;
    }
    if((wk->preConnect == -1) && (mydwc_IsNewPlayer() != -1)){
        wk->preConnect = mydwc_IsNewPlayer();
        _friendNameExpand(wk, wk->preConnect);
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_043, FALSE);
        wk->localTime = 0;
    }
    else if((wk->preConnect != -1) && (mydwc_IsNewPlayer() == -1)){

        GF_BGL_BmpWinDel(&wk->ListWin);
        BmpListExit(wk->lw, NULL, NULL);
        wk->lw = NULL;
        BMP_MENULIST_Delete( wk->menulist );
        wk->menulist = NULL;

        _friendNameExpand(wk, wk->preConnect);
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_015, FALSE);
        CommStateWifiMatchEnd();
        wk->seq = WIFIP2PMATCH_MODE_VCT_DISCONNECT;
        return seq;
    }
/*    if(wk->localTime){
        wk->localTime--;
        if(wk->localTime == 0){
            EndMessageWindowOff(wk);
        }
    }*/

//    _mainListReWrite(wk);

    if(wk->preConnect == -1){
        ret = BmpListMain(wk->lw);
    }
    switch(ret){
      case BMPLIST_NULL:
        return seq;
      case BMPLIST_CANCEL:
        Snd_SePlay(_SE_DESIDE);
        if(_modeWait(wk->pMatch->myMatchStatus.status)){
            wk->seq = WIFIP2PMATCH_MODE_SELECT_REL_INIT;  // �������ҋ@�̏ꍇ�K������
        }
        else{
            wk->endSeq = WIFI_P2PMATCH_END;
            wk->seq = WIFIP2PMATCH_MODE_EXIT_YESNO;
            WifiP2PMatchMessagePrint(wk, dwc_message_0010, TRUE);
            //        wk->localTime=0;
            ret = BMPLIST_CANCEL;
        }
        return seq;
      default:
//        wk->localTime=0;
        Snd_SePlay(_SE_DESIDE);
        if(_modeWait(wk->pMatch->myMatchStatus.status)){
            wk->seq = WIFIP2PMATCH_MODE_SELECT_REL_INIT;  // �������ҋ@�̏ꍇ�K������
        }
        else if(ret == WIFIP2PMATCH_MEMBER_MAX){  // ��W��
            if(wk->pMatch->myMatchStatus.status == WIFI_STATUS_LOGIN_WAIT){
                wk->seq = WIFIP2PMATCH_MODE_SELECT_INIT;
            }
            else if(_modeWait(wk->pMatch->myMatchStatus.status)){
                wk->seq = WIFIP2PMATCH_MODE_SELECT_REL_INIT;
            }
        }
        else{  // �l�̖��O
            wk->seq = WIFIP2PMATCH_MODE_MATCH_INIT;
        }
        return seq;
        break;
    }
    GF_BGL_BmpWinDel(&wk->ListWin);
    BmpListExit(wk->lw, NULL, NULL);
    wk->lw = NULL;
    BMP_MENULIST_Delete( wk->menulist );
    wk->menulist = NULL;
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   VCTONOFF�E�C���h�E�����
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _vchatToggleWait( WIFIP2PMATCH_WORK *wk, int seq )
{
    if( 0 !=  _checkParentConnect(wk)){ // �ڑ����Ă���
        wk->seq = WIFIP2PMATCH_MODE_FRIENDLIST;
    }
    else if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        wk->seq = WIFIP2PMATCH_MODE_FRIENDLIST;
        EndMessageWindowOff(wk);
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   VCT�ڑ��J�n
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int WifiP2PMatch_VCTConnectInit2( WIFIP2PMATCH_WORK *wk, int seq )        // WIFIP2PMATCH_MODE_VCT_CONNECT_INIT2
{
    if(sys.trg & PAD_BUTTON_CANCEL){
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_068, FALSE);
        wk->seq = WIFIP2PMATCH_MODE_BCANCEL_YESNO_VCT;
    }
    else if(CommWifiIsMatched() == 5){
        _friendNameExpand(wk, mydwc_getFriendIndex());
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_012, FALSE);
        wk->seq = WIFIP2PMATCH_MODE_VCT_DISCONNECT;
    }
    else if(CommWifiIsMatched() == 3 ){
        _friendNameExpand(wk, mydwc_getFriendIndex());
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_015, FALSE);
        wk->seq = WIFIP2PMATCH_MODE_VCT_DISCONNECT;
    }
    else if((CommWifiIsMatched() == 4) || (CommStateIsWifiDisconnect())){
        _friendNameExpand(wk, mydwc_getFriendIndex());
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_016, FALSE);
        wk->seq = WIFIP2PMATCH_MODE_VCT_DISCONNECT;
    }
    else if(CommStateIsWifiError()){
        _errorDisp(wk);
    }
    if(CommWifiIsMatched()==1){  // �Ȃ�����
        _timeWaitIconDel(wk);
        _myStatusChange(wk, WIFI_STATUS_VCT);  // VCT���ɂȂ�
        wk->seq = WIFIP2PMATCH_MODE_VCT_CONNECT; // ���ɍs���ۂɌĂ�
    }

    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   VCT�ڑ��J�n
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int WifiP2PMatch_VCTConnectInit( WIFIP2PMATCH_WORK *wk, int seq )        // WIFIP2PMATCH_MODE_VCT_CONNECT_INIT
{
    if(CommWifiIsMatched()==1){  // �Ȃ�����
        _friendNameExpand(wk, mydwc_getFriendIndex());
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_011, FALSE);
        _myStatusChange(wk, WIFI_STATUS_VCT);  // VCT���ɂȂ�
        wk->seq = WIFIP2PMATCH_MODE_VCT_CONNECT_WAIT; // ���ɍs���ۂɌĂ�
    }

    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   VCT�ڑ��܂�
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int WifiP2PMatch_VCTConnectWait( WIFIP2PMATCH_WORK *wk, int seq )        // WIFIP2PMATCH_MODE_VCT_CONNECT_WAIT
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        if(sys.trg & (PAD_BUTTON_CANCEL|PAD_BUTTON_DECIDE)){
            EndMessageWindowOff(wk);
            wk->seq = WIFIP2PMATCH_MODE_VCT_CONNECT; // ���ɍs���ۂɌĂ�
        }
        else{
            WifiP2PMatch_VCTConnect(wk,seq);
        }
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   VCT�ڑ���  WIFIP2PMATCH_MODE_VCT_CONNECT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int WifiP2PMatch_VCTConnect( WIFIP2PMATCH_WORK *wk, int seq )
{

    _mainListReWrite(wk);

    CLACT_SetDrawFlag( wk->MainActWork[_CLACT_VCT_MOVE], 0 );
    CLACT_SetDrawFlag( wk->MainActWork[_CLACT_VCT_STOP], 0 );
    if(CommWifiIsMatched() == 5){
        _friendNameExpand(wk, mydwc_getFriendIndex());
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_012, FALSE);
        wk->seq = WIFIP2PMATCH_MODE_VCT_DISCONNECT;
    }
    else if(CommWifiIsMatched() == 3 ){
        _friendNameExpand(wk, mydwc_getFriendIndex());
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_015, FALSE);
        wk->seq = WIFIP2PMATCH_MODE_VCT_DISCONNECT;
    }
    else if((CommWifiIsMatched() == 4) || (CommStateIsWifiDisconnect())){
        _friendNameExpand(wk, mydwc_getFriendIndex());
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_016, FALSE);
        wk->seq = WIFIP2PMATCH_MODE_VCT_DISCONNECT;
    }
    else if(CommStateIsWifiError()){
        _errorDisp(wk);
    }
    else if(sys.trg & (PAD_BUTTON_CANCEL|PAD_BUTTON_DECIDE)){
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_017, FALSE);
        wk->seq = WIFIP2PMATCH_MODE_VCT_CONNECTEND_YESNO;
    }
    else{
        if(mydwc_IsSendVoiceAndInc()){
            SetCursor_Pos(wk->MainActWork[_CLACT_VCT_MOVE], 32, 0xb0);
            CLACT_SetDrawFlag( wk->MainActWork[_CLACT_VCT_MOVE], 1 );
        }
        else{
            SetCursor_Pos(wk->MainActWork[_CLACT_VCT_STOP], 32, 0xb0);
            CLACT_SetDrawFlag( wk->MainActWork[_CLACT_VCT_STOP], 1 );
        }
    }

    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   VCT�ڑ�����
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int WifiP2PMatch_VCTConnectEndYesNo( WIFIP2PMATCH_WORK *wk, int seq )        // WIFIP2PMATCH_MODE_VCT_CONNECT
{
    //Snd_PlayerSetInitialVolume( SND_HANDLE_BGM, PV_VOL_DEFAULT/3 );
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        WifiList_SetLastPlayDate( wk->pList, mydwc_getFriendIndex());
        // �͂��������E�C���h�E���o��
        wk->pYesNoWork =
            BmpYesNoSelectInit( wk->bgl,
                                &_yesNoBmpDat,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                HEAPID_WIFIP2PMATCH );
        wk->seq = WIFIP2PMATCH_MODE_VCT_CONNECTEND_WAIT;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   VCT�ڑ��I��  WIFIP2PMATCH_MODE_VCT_CONNECTEND_WAIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int WifiP2PMatch_VCTConnectEndWait( WIFIP2PMATCH_WORK *wk, int seq )        // WIFIP2PMATCH_MODE_VCT_CONNECT
{
    int i;
    int ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);
    if(ret == BMPMENU_NULL){  // �܂��I��
        if((CommWifiIsMatched() >= 4) || CommStateIsWifiDisconnect() || !CommIsConnect(COMM_PARENT_ID)){
            _myStatusChange(wk, WIFI_STATUS_LOGIN_WAIT);
            BmpYesNoWinDel( wk->pYesNoWork, HEAPID_WIFIP2PMATCH );
            wk->preConnect = -1;
            wk->timer = _RECONECTING_WAIT_TIME;
            wk->seq = WIFIP2PMATCH_RECONECTING_WAIT;
        }
        return seq;
    }else if(ret == 0){ // �͂���I�������ꍇ
        //Snd_PlayerSetInitialVolume( SND_HANDLE_BGM, PV_VOL_DEFAULT );
        _myStatusChange(wk, WIFI_STATUS_LOGIN_WAIT);
        CommStateWifiBattleMatchEnd();
        wk->preConnect = -1;
        wk->timer = _RECONECTING_WAIT_TIME;
        wk->seq = WIFIP2PMATCH_RECONECTING_WAIT;
        //wk->seq = WIFIP2PMATCH_MODE_FRIENDLIST;
    }
    else{  // ��������I�������ꍇ
        wk->seq = WIFIP2PMATCH_MODE_VCT_CONNECT;
    }
    EndMessageWindowOff(wk);
    return seq;
}



//WIFIP2PMATCH_MODE_VCT_DISCONNECT
static int WifiP2PMatch_VCTDisconnect(WIFIP2PMATCH_WORK *wk, int seq)
{
    if(wk->pMatch->myMatchStatus.status != WIFI_STATUS_LOGIN_WAIT){
        _myStatusChange(wk, WIFI_STATUS_LOGIN_WAIT);
    }
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) != 0 ){
        wk->timer = 30;
        return seq;
    }
    wk->timer--;
    if((sys.trg & (PAD_BUTTON_CANCEL|PAD_BUTTON_DECIDE)) || (wk->timer==0)){
        EndMessageWindowOff(wk);
        CommStateWifiMatchEnd();
        if(wk->menulist==NULL){
            wk->timer = _RECONECTING_WAIT_TIME;
            wk->seq = WIFIP2PMATCH_RECONECTING_WAIT;
        }
        else{
            wk->preConnect = -1;
            wk->seq = WIFIP2PMATCH_MODE_FRIENDLIST;
        }
    }
    return seq;
}

//WIFIP2PMATCH_MODE_BATTLE_DISCONNECT
static int WifiP2PMatch_BattleDisconnect(WIFIP2PMATCH_WORK *wk, int seq)
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) != 0 ){
        return seq;
    }
    if(sys.trg & (PAD_BUTTON_CANCEL|PAD_BUTTON_DECIDE)){
        EndMessageWindowOff(wk);
        _myStatusChange(wk, WIFI_STATUS_LOGIN_WAIT);
        CommStateWifiMatchEnd();
        wk->timer = _RECONECTING_WAIT_TIME;
        wk->seq = WIFIP2PMATCH_RECONECTING_WAIT;
    }
    return seq;
}

//WIFIP2PMATCH_MODE_DISCONNECT
static int WifiP2PMatch_Disconnect(WIFIP2PMATCH_WORK *wk, int seq)
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) != 0 ){
        return seq;
    }
    if(sys.trg & (PAD_BUTTON_CANCEL|PAD_BUTTON_DECIDE)){
        EndMessageWindowOff(wk);
        _myStatusChange(wk, WIFI_STATUS_LOGIN_WAIT);
        if(wk->menulist==NULL){
            wk->seq = WIFIP2PMATCH_FRIENDLIST_INIT;
        }
        else{
            wk->preConnect = -1;
            wk->seq = WIFIP2PMATCH_MODE_FRIENDLIST;
        }
    }
    return seq;
}

static int WifiP2PMatch_BattleConnectInit( WIFIP2PMATCH_WORK *wk, int seq )    // WIFIP2PMATCH_MODE_BATTLE_CONNECT_INIT
{
    return seq;
}

static int WifiP2PMatch_BattleConnectWait( WIFIP2PMATCH_WORK *wk, int seq )     // WIFIP2PMATCH_MODE_BATTLE_CONNECT_WAIT
{
    return seq;
}

static int WifiP2PMatch_BattleConnect( WIFIP2PMATCH_WORK *wk, int seq )        // WIFIP2PMATCH_MODE_BATTLE_CONNECT
{
    return seq;
}


//------------------------------------------------------------------
/**
 * $brief   �J�[�\���ʒu��ύX����
 *
 * @param   act		�A�N�^�[�̃|�C���^
 * @param   x
 * @param   y
 *
 * @retval  none
 */
//------------------------------------------------------------------
static void SetCursor_Pos( CLACT_WORK_PTR act, int x, int y )
{
    VecFx32 mat;

    mat.x = FX32_CONST( x );
    mat.y = FX32_CONST( y );
    mat.z = 0;
    CLACT_SetMatrix( act, &mat);

}

//------------------------------------------------------------------
/**
 * $brief   �{�^���������ƏI��  WIFIP2PMATCH_MODE_CHECK_AND_END
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int WifiP2PMatch_CheckAndEnd( WIFIP2PMATCH_WORK *wk, int seq )
{
    if(sys.trg & (PAD_BUTTON_CANCEL|PAD_BUTTON_DECIDE)){
        wk->endSeq = WIFI_P2PMATCH_END;
        wk->seq = WIFIP2PMATCH_MODE_END_WAIT;
        CommStateWifiLogout();
    }
    return seq;
}



//------------------------------------------------------------------
/**
 * $brief   ��W�̎����� WIFIP2PMATCH_MODE_SELECT_REL_INIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _parentModeSelectRelInit( WIFIP2PMATCH_WORK *wk, int seq )
{
    WifiP2PMatchMessagePrint(wk, msg_wifilobby_007, FALSE);
    wk->seq = WIFIP2PMATCH_MODE_SELECT_REL_YESNO;
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   ��W�̎�����  WIFIP2PMATCH_MODE_SELECT_REL_YESNO
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------

static int _parentModeSelectRelYesNo( WIFIP2PMATCH_WORK* wk, int seq )
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        // �͂��������E�C���h�E���o��
        wk->pYesNoWork =
            BmpYesNoSelectInit( wk->bgl,
                                &_yesNoBmpDat,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                HEAPID_WIFIP2PMATCH );
        wk->seq = WIFIP2PMATCH_MODE_SELECT_REL_WAIT;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   ��W�̎�����  WIFIP2PMATCH_MODE_SELECT_REL_WAIT
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------

static int _parentModeSelectRelWait( WIFIP2PMATCH_WORK* wk, int seq )
{
    int i;
    int ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);

    if((wk->preConnect == -1) && (mydwc_IsNewPlayer() != -1)){  // �ڑ���������
		// ���ł�YesNoSelectMain�ŉ������ĂȂ����
		if( ret == BMPMENU_NULL ){
			BmpYesNoWinDel( wk->pYesNoWork, HEAPID_WIFIP2PMATCH );
		}
        ret = 1;  // �������ɕύX
    }
    if(ret == BMPMENU_NULL){  // �܂��I��
        return seq;
    }else if(ret == 0){ // �͂���I�������ꍇ
        //��������
        _myStatusChange(wk, WIFI_STATUS_LOGIN_WAIT);
    }
    else{  // ��������I�������ꍇ
    }
    EndMessageWindowOff(wk);
    wk->seq = WIFIP2PMATCH_MODE_FRIENDLIST;
    return seq;
}



//------------------------------------------------------------------
/**
 * $brief   �ҋ@��ԂɂȂ�ׂ̑I�����j���[ WIFIP2PMATCH_MODE_SELECT_INIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

typedef struct {
    u32  str_id;
    u32  param;
} _infoMenu;

_infoMenu _parentInfoMenuList[] = {
    { msg_wifilobby_057, (u32)0 },
    { msg_wifilobby_058, (u32)1 },
    { msg_wifilobby_025, (u32)WIFI_STATUS_TRADE_WAIT },
    { msg_wifilobby_032, (u32)BMPLIST_CANCEL },
};

_infoMenu _parentSingleInfoMenuList[] = {
    { msg_wifilobby_059, (u32)WIFI_STATUS_SBATTLE_FREE_WAIT },
    { msg_wifilobby_060, (u32)WIFI_STATUS_SBATTLE50_WAIT },
    { msg_wifilobby_061, (u32)WIFI_STATUS_SBATTLE100_WAIT },
    { msg_wifilobby_032, (u32)BMPLIST_CANCEL },
};

_infoMenu _parentDoubleInfoMenuList[] = {
    { msg_wifilobby_062, (u32)WIFI_STATUS_DBATTLE_FREE_WAIT },
    { msg_wifilobby_063, (u32)WIFI_STATUS_DBATTLE50_WAIT },
    { msg_wifilobby_064, (u32)WIFI_STATUS_DBATTLE100_WAIT },
    { msg_wifilobby_032, (u32)BMPLIST_CANCEL },
};


///�I�����j���[�̃��X�g
static const BMPLIST_HEADER _parentInfoMenuListHeader = {
    NULL,			// �\�������f�[�^�|�C���^
    _curCallBack,					// �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
    NULL,					// ���\�����Ƃ̃R�[���o�b�N�֐�
    NULL,                   //
    NELEMS(_parentInfoMenuList),	// ���X�g���ڐ�
    NELEMS(_parentInfoMenuList),	// �\���ő區�ڐ�
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
    FONT_SYSTEM,				// �����w��
    0,						// �a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
    NULL                    // work
    };


static int _parentModeSelectMenuInit( WIFIP2PMATCH_WORK *wk, int seq )
{
    int i,length;
    BMPLIST_HEADER list_h;

    length = NELEMS(_parentInfoMenuList);
    list_h = _parentInfoMenuListHeader;

    wk->submenulist = BMP_MENULIST_Create( length , HEAPID_WIFIP2PMATCH );
    for(i=0; i< length ; i++){
        BMP_MENULIST_AddArchiveString( wk->submenulist, wk->MsgManager, _parentInfoMenuList[i].str_id, _parentInfoMenuList[i].param );
    }
    if(GF_BGL_BmpWinAddCheck(&wk->SubListWin)){
        BmpMenuWinClear(&wk->SubListWin,WINDOW_TRANS_ON);
        GF_BGL_BmpWinDel(&wk->SubListWin);
    }
    //BMP�E�B���h�E����
    GF_BGL_BmpWinAdd(wk->bgl,&wk->SubListWin,
                     GF_BGL_FRAME2_M, 16, 9, 15, length * 2, FLD_SYSFONT_PAL, FLD_MENU_WIN_CGX - length * 2);
    BmpMenuWinWrite(&wk->SubListWin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
    list_h.list = wk->submenulist;
    list_h.win = &wk->SubListWin;

    wk->sublw = BmpListSet(&list_h, 0, wk->battleCur, HEAPID_WIFIP2PMATCH);
    GF_BGL_BmpWinOnVReq(&wk->SubListWin);


    WifiP2PMatchMessagePrint(wk, msg_wifilobby_006, FALSE);

    wk->seq = WIFIP2PMATCH_MODE_SELECT_WAIT;
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �ҋ@��ԂɂȂ�ׂ̑I�����j���[ WIFIP2PMATCH_MODE_SELECT_WAIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int _battleSubMenuInit( WIFIP2PMATCH_WORK *wk, int ret );
static int _parentModeSelectMenuWait( WIFIP2PMATCH_WORK *wk, int seq )
{
    u32	ret;
    int num = _getBattlePokeNum(wk);

    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) != 0 ){
        return seq;
    }
    ret = BmpListMain(wk->sublw);

    if( 0 !=  _checkParentConnect(wk)){ // �ڑ����Ă���
        ret = BMPLIST_CANCEL;
    }
    switch(ret){
      case BMPLIST_NULL:
        return seq;
      case BMPLIST_CANCEL:
        wk->seq = WIFIP2PMATCH_MODE_FRIENDLIST;
        EndMessageWindowOff(wk);
        Snd_SePlay(_SE_DESIDE);
        break;
      default:
        Snd_SePlay(_SE_DESIDE);
        
        if((ret == WIFI_STATUS_TRADE_WAIT) && (2 > num )){
            WifiP2PMatchMessagePrint(wk, msg_wifilobby_053, FALSE);
            wk->seq = WIFIP2PMATCH_MODE_DISCONNECT;
        }
        else if((ret == 1) && (2 > num)){
            WifiP2PMatchMessagePrint(wk, msg_wifilobby_067, FALSE);
            wk->seq = WIFIP2PMATCH_MODE_DISCONNECT;
        }
        else if((ret == 0) || (ret == 1)){
//            _myStatusChange(wk, ret);
            BmpMenuWinClear(&wk->SubListWin, WINDOW_TRANS_ON );
            GF_BGL_BmpWinDel(&wk->SubListWin);
            BmpListExit(wk->sublw, NULL,  &wk->battleCur);
            BMP_MENULIST_Delete( wk->submenulist );
            _battleSubMenuInit(wk, ret);
            wk->seq = WIFIP2PMATCH_MODE_SUBBATTLE_WAIT;
            return seq;
//            EndMessageWindowOff(wk);
        }
        else{
            _myStatusChange(wk, ret);
            wk->seq = WIFIP2PMATCH_MODE_FRIENDLIST;
            EndMessageWindowOff(wk);
        }
        break;
    }
    BmpMenuWinClear(&wk->SubListWin, WINDOW_TRANS_ON );
    GF_BGL_BmpWinDel(&wk->SubListWin);
    BmpListExit(wk->sublw, NULL, &wk->battleCur);
    BMP_MENULIST_Delete( wk->submenulist );
    return seq;

}

//------------------------------------------------------------------
/**
 * $brief   �o�g���̏ڍו��������߂� WIFIP2PMATCH_MODE_SUBBATTLE_INIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _battleSubMenuInit( WIFIP2PMATCH_WORK *wk, int ret )
{
    int i,length;
    BMPLIST_HEADER list_h;
    _infoMenu* pMenu;
    
    if(ret == 0){
        pMenu = _parentSingleInfoMenuList;
        length = NELEMS(_parentSingleInfoMenuList);
        wk->bSingle = 1;
    }
    else{
        pMenu = _parentDoubleInfoMenuList;
        length = NELEMS(_parentDoubleInfoMenuList);
        wk->bSingle = 0;
    }
    list_h = _parentInfoMenuListHeader;

    wk->submenulist = BMP_MENULIST_Create( length , HEAPID_WIFIP2PMATCH );
    for(i=0; i< length ; i++){
        BMP_MENULIST_AddArchiveString( wk->submenulist, wk->MsgManager, pMenu[i].str_id, pMenu[i].param );
    }
    if(GF_BGL_BmpWinAddCheck(&wk->SubListWin)){
        BmpMenuWinClear(&wk->SubListWin, WINDOW_TRANS_ON );
        GF_BGL_BmpWinDel(&wk->SubListWin);
    }
    //BMP�E�B���h�E����
    GF_BGL_BmpWinAdd(wk->bgl,&wk->SubListWin,
                     GF_BGL_FRAME2_M, 16, 9, 15, length * 2, FLD_SYSFONT_PAL, FLD_MENU_WIN_CGX - length * 2);
    BmpMenuWinWrite(&wk->SubListWin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
    list_h.list = wk->submenulist;
    list_h.win = &wk->SubListWin;
    wk->sublw = BmpListSet(&list_h, 0, wk->singleCur[wk->bSingle], HEAPID_WIFIP2PMATCH);
    GF_BGL_BmpWinOnVReq(&wk->SubListWin);

//    WifiP2PMatchMessagePrint(wk, msg_wifilobby_006, FALSE);

//    wk->seq = WIFIP2PMATCH_MODE_SELECT_WAIT;
    return TRUE;
}



//------------------------------------------------------------------
/**
 * $brief   �ҋ@��ԂɂȂ�ׂ̑I�����j���[ WIFIP2PMATCH_MODE_SUBBATTLE_WAIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int _parentModeSubSelectMenuWait( WIFIP2PMATCH_WORK *wk, int seq )
{
    u32	ret;

    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) != 0 ){
        return seq;
    }
    ret = BmpListMain(wk->sublw);
    if( 0 !=  _checkParentConnect(wk)){ // �ڑ����Ă���
        ret = BMPLIST_CANCEL;
    }
    switch(ret){
      case BMPLIST_NULL:
        return seq;
      case BMPLIST_CANCEL:
        Snd_SePlay(_SE_DESIDE);
        wk->seq = WIFIP2PMATCH_MODE_SELECT_INIT;
        break;
      default:
        Snd_SePlay(_SE_DESIDE);
        _myStatusChange(wk, ret);
        wk->seq = WIFIP2PMATCH_MODE_FRIENDLIST;
        EndMessageWindowOff(wk);
        break;
    }
    BmpMenuWinClear(&wk->SubListWin, WINDOW_TRANS_ON );
    GF_BGL_BmpWinDel(&wk->SubListWin);
    BmpListExit(wk->sublw, NULL, &wk->singleCur[wk->bSingle]);
    BMP_MENULIST_Delete( wk->submenulist );
    return seq;

}

//------------------------------------------------------------------
/**
 * $brief   �}�b�`���O�\������ WIFIP2PMATCH_MODE_MATCH_INIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

enum{
    _CONNECTING = 1,
    _INFOVIEW,
};


static const struct {
    u32  str_id;
    u32  param;
}_childMatchMenuList[] = {
    { msg_wifilobby_030, (u32)_CONNECTING },
    { msg_wifilobby_031, (u32)_INFOVIEW },
    { msg_wifilobby_032, (u32)BMPLIST_CANCEL },
};

///�I�����j���[�̃��X�g
static const BMPLIST_HEADER _childMatchMenuListHeader = {
    NULL,			// �\�������f�[�^�|�C���^
    _curCallBack,					// �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
    NULL,					// ���\�����Ƃ̃R�[���o�b�N�֐�
    NULL,                   //
    NELEMS(_childMatchMenuList),	// ���X�g���ڐ�
    NELEMS(_childMatchMenuList),	// �\���ő區�ڐ�
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
    FONT_SYSTEM,				// �����w��
    0,						// �a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
    NULL                    // work
    };


static int _childModeMatchMenuInit( WIFIP2PMATCH_WORK *wk, int seq )
{
    int i,length,gmmno;
    BMPLIST_HEADER list_h;
    u16 mainCursor,friendNo,status,vchat;

    length = NELEMS(_childMatchMenuList);
    list_h = _childMatchMenuListHeader;
    BmpListDirectPosGet(wk->lw,&mainCursor);
    friendNo = wk->index2No[mainCursor];
    status = wk->pMatch->friendMatchStatus[ friendNo - 1 ].status;
    wk->keepStatus = status;
    vchat = wk->pMatch->friendMatchStatus[ friendNo - 1 ].vchat;
    wk->keepVChat = vchat;
    vchat += wk->pMatch->myMatchStatus.vchat;

    wk->submenulist = BMP_MENULIST_Create( length , HEAPID_WIFIP2PMATCH );
    i = 0;

    for(i = 0; i < NELEMS(_childMatchMenuList);i++){
        if(i == 0){
            if(_modeActive(status) || (status == WIFI_STATUS_NONE) ||
               (status >= WIFI_STATUS_UNKNOWN)){  // ���������ނ��o���Ȃ�����
                list_h.line -= 1;
                list_h.count -= 1;
                length -= 1;
            }
            else if(status == WIFI_STATUS_LOGIN_WAIT){
                if(vchat == 2){
                    BMP_MENULIST_AddArchiveString( wk->submenulist, wk->MsgManager,
                                                   msg_wifilobby_027,
                                                   _childMatchMenuList[i].param );
                }
                else{
                    list_h.line -= 1;
                    list_h.count -= 1;
                    length -= 1;
                }
            }
            else{
                BMP_MENULIST_AddArchiveString( wk->submenulist, wk->MsgManager,
                                               _childMatchMenuList[i].str_id,
                                               _childMatchMenuList[i].param );
            }
        }
        else{
            BMP_MENULIST_AddArchiveString( wk->submenulist, wk->MsgManager,
                                           _childMatchMenuList[i].str_id,
                                           _childMatchMenuList[i].param );
        }
    }
    //BMP�E�B���h�E����
    GF_BGL_BmpWinAdd(wk->bgl,&wk->SubListWin,
                     GF_BGL_FRAME2_M, 16, 11+ ((3-length)*2), 15  , length * 2,
                     FLD_SYSFONT_PAL, FLD_MENU_WIN_CGX);
    BmpMenuWinWrite(&wk->SubListWin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
    list_h.list = wk->submenulist;
    list_h.win = &wk->SubListWin;
    wk->sublw = BmpListSet(&list_h, 0, 0, HEAPID_WIFIP2PMATCH);
    GF_BGL_BmpWinOnVReq(&wk->SubListWin);

    _friendNameExpand(wk, friendNo - 1);
    if(status == WIFI_STATUS_TRADE_WAIT){
        gmmno = msg_wifilobby_004;
    }
    else if(_modeBattleWait(status)){
        gmmno = msg_wifilobby_003;
    }
    else if(status == WIFI_STATUS_TRADE){
        gmmno = msg_wifilobby_049;
    }
    else if(_modeBattle(status)){
        gmmno = msg_wifilobby_048;
    }
    else if(status == WIFI_STATUS_VCT){
        gmmno = msg_wifilobby_050;
    }
    else{
        gmmno = msg_wifilobby_005;
    }
    WifiP2PMatchMessagePrint(wk, gmmno, FALSE);
    wk->seq = WIFIP2PMATCH_MODE_MATCH_WAIT;
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   ���m�̃A�C�e������
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static BOOL _isItemCheck(_WIFI_MACH_STATUS* pTargetStatus)
{
    int i;
    
    for(i = 0; i < _POKEMON_NUM; i++){
        if(MONSNO_DAMETAMAGO == pTargetStatus->pokemonType[i]){
            return FALSE;
        }
        if(MONSNO_MAX < pTargetStatus->pokemonType[i]){
            return FALSE;
        }
        if(ITEM_DATA_MAX < pTargetStatus->hasItemType[i]){
            return FALSE;
        }
    }
    return TRUE;
}

//------------------------------------------------------------------
/**
 * $brief   �Ȃ��ɍs���I�����j���[ WIFIP2PMATCH_MODE_MATCH_WAIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int _childModeMatchMenuWait( WIFIP2PMATCH_WORK *wk, int seq )
{
    u32	ret;
    int status,friendNo,message = 0,vchat;
    u16 mainCursor;
    int checkMatch;

    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) != 0 ){
        return seq;
    }
    ret = BmpListMain(wk->sublw);

    checkMatch = _checkParentConnect(wk);
    if( 0 !=  checkMatch ){ // �ڑ����Ă���
        ret = BMPLIST_CANCEL;
    }

    switch(ret){
      case BMPLIST_NULL:
        return seq;
      case BMPLIST_CANCEL:
        Snd_SePlay(_SE_DESIDE);
        wk->seq = WIFIP2PMATCH_MODE_FRIENDLIST;
        break;
      default:
        Snd_SePlay(_SE_DESIDE);
        if(ret == _CONNECTING){  // �q�@���e�@�ɐڑ�
            wk->seq = WIFIP2PMATCH_MODE_FRIENDLIST;
            BmpListDirectPosGet(wk->lw,&mainCursor);
            friendNo = wk->index2No[mainCursor];
            wk->friendNo = friendNo;
            if(  friendNo != 0 ){
                int num = _getBattlePokeNum(wk);
                status = wk->pMatch->friendMatchStatus[ friendNo - 1 ].status;
                vchat = wk->pMatch->friendMatchStatus[ friendNo - 1 ].vchat;
                if((wk->keepStatus != status) || (wk->keepVChat != vchat)){
                    _friendNameExpand(wk, friendNo - 1);
                    WifiP2PMatchMessagePrint(wk, msg_wifilobby_013, FALSE);
                    wk->seq = WIFIP2PMATCH_MODE_DISCONNECT;
                    message = 1;
                    break;
                }
                if(!_isItemCheck(&wk->pMatch->friendMatchStatus[ friendNo - 1 ])){
                    _friendNameExpand(wk, friendNo - 1);
                    WifiP2PMatchMessagePrint(wk, msg_wifilobby_013, FALSE);
                    wk->seq = WIFIP2PMATCH_MODE_DISCONNECT;
                    message = 1;
                    break;
                }
                if(_is2pokeMode(status) && (2 > num)){
                    if(WIFI_STATUS_TRADE_WAIT==status){
                        WifiP2PMatchMessagePrint(wk, msg_wifilobby_053, FALSE);
                    }
                    else{
                        WifiP2PMatchMessagePrint(wk, msg_wifilobby_067, FALSE);
                    }
                    wk->seq = WIFIP2PMATCH_MODE_DISCONNECT;
                    message = 1;
                    break;
                }
                if(vchat != wk->pMatch->myMatchStatus.vchat){  // ������VCHAT�Ə�Ԃ��Ⴄ�ꍇ���b�Z�[�W
                    if(vchat){
                        WifiP2PMatchMessagePrint(wk, msg_wifilobby_069, FALSE);
                    }
                    else{
                        WifiP2PMatchMessagePrint(wk, msg_wifilobby_070, FALSE);
                    }
                    wk->seq = WIFIP2PMATCH_MODE_VCHAT_NEGO;
                    message = 1;
                    break;
                }
                status = _convertState(status);
                if(WIFI_STATUS_UNKNOWN == status){
                    break;
                }
                if( mydwc_getFriendStatus(friendNo - 1) == DWC_STATUS_MATCH_SC_SV ){
                    if( CommWifiBattleStart( friendNo - 1 ) ){
                        _myStatusChange(wk, status);  // �ڑ����ɂȂ�
                        _friendNameExpand(wk, friendNo - 1);
                        WifiP2PMatchMessagePrint(wk,msg_wifilobby_014, FALSE);
                        wk->timeWaitWork = TimeWaitIconAdd( &wk->MsgWin, COMM_TALK_WIN_CGX_NUM );
                        if(status != WIFI_STATUS_VCT){
                            wk->seq = WIFIP2PMATCH_MODE_MATCH_LOOP;  // �}�b�`���O��
                        }
                        else{
                            wk->seq = WIFIP2PMATCH_MODE_VCT_CONNECT_INIT2;  //VCT��p��
                        }
                        message = 1;
                    }
                }
            }
        }
        else if(ret == _INFOVIEW){
            wk->seq = WIFIP2PMATCH_MODE_PERSONAL_INIT;
        }
        break;
    }
    if(message==0){
        EndMessageWindowOff(wk);
    }
    BmpMenuWinClear(&wk->SubListWin, WINDOW_TRANS_ON );
    GF_BGL_BmpWinDel(&wk->SubListWin);
    BmpListExit(wk->sublw, NULL, NULL);
    BMP_MENULIST_Delete( wk->submenulist );
    return seq;
}


//WIFIP2PMATCH_MODE_MATCH_LOOP
static int _childModeMatchMenuLoop( WIFIP2PMATCH_WORK *wk, int seq )
{
    if(sys.trg & PAD_BUTTON_CANCEL){
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_068, FALSE);
        wk->seq = WIFIP2PMATCH_MODE_BCANCEL_YESNO;
    }
    else if(CommWifiIsMatched() == 3 ){
        _friendNameExpand(wk, mydwc_getFriendIndex());
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_015, FALSE);
        wk->seq = WIFIP2PMATCH_MODE_VCT_DISCONNECT;
    }
    else if(CommWifiIsMatched() == 5){
        _friendNameExpand(wk, mydwc_getFriendIndex());
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_012, FALSE);
        wk->seq = WIFIP2PMATCH_MODE_VCT_DISCONNECT;
    }
    else if((CommWifiIsMatched() == 4) || (CommStateIsWifiDisconnect())){
        _friendNameExpand(wk, mydwc_getFriendIndex());
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_015, FALSE);
        wk->seq = WIFIP2PMATCH_MODE_VCT_DISCONNECT;
    }
    else if(CommStateIsWifiError()){
        _errorDisp(wk);
    }
    else if(CommWifiIsMatched()==1){  // ����ɐڑ�����
        _timeWaitIconDel(wk);
        CommInfoInitialize(wk->pSaveData,NULL);   //Info������
        wk->timer = 30;
        wk->seq = WIFIP2PMATCH_MODE_CALL_YESNO; // �q�@�e�@����
    }
    return seq;
}

//-------------------------------------VCT�̃L�����Z���@�\���}篎���

//------------------------------------------------------------------
/**
 * $brief   B�L�����Z��  WIFIP2PMATCH_MODE_BCANCEL_YESNO_VCT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int WifiP2PMatch_BCancelYesNoVCT( WIFIP2PMATCH_WORK *wk, int seq )
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        // �͂��������E�C���h�E���o��
        wk->pYesNoWork =
            BmpYesNoSelectInit( wk->bgl,
                                &_yesNoBmpDat,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                HEAPID_WIFIP2PMATCH );
        wk->seq = WIFIP2PMATCH_MODE_BCANCEL_WAIT_VCT;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   B�L�����Z��  WIFIP2PMATCH_MODE_BCANCEL_WAIT_VCT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int WifiP2PMatch_BCancelWaitVCT( WIFIP2PMATCH_WORK *wk, int seq )
{
    int i;
    int ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);

    if( 0 !=  _checkParentConnect(wk)){ // �ڑ����Ă���
        if(ret == BMPMENU_NULL){
            BmpYesNoWinDel(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);
        }
        wk->seq = WIFIP2PMATCH_MODE_VCT_CONNECT_INIT2;
    }
    else if(ret == BMPMENU_NULL){  // �܂��I��
        return seq;
    }else if(ret == 0){ // �͂���I�������ꍇ
        _myVChatStatusOrgSet(wk);
        _myStatusChange(wk, WIFI_STATUS_LOGIN_WAIT);
        CommStateWifiMatchEnd();
        wk->preConnect = -1;
        wk->seq = WIFIP2PMATCH_MODE_FRIENDLIST;
    }
    else{  // ��������I�������ꍇ
        wk->seq = WIFIP2PMATCH_MODE_VCT_CONNECT_INIT2;
    }
    EndMessageWindowOff(wk);
    return seq;
}

//------------------------------------------

//------------------------------------------------------------------
/**
 * $brief   B�L�����Z��  WIFIP2PMATCH_MODE_BCANCEL_YESNO
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int WifiP2PMatch_BCancelYesNo( WIFIP2PMATCH_WORK *wk, int seq )        // WIFIP2PMATCH_MODE_VCT_CONNECT
{
    //Snd_PlayerSetInitialVolume( SND_HANDLE_BGM, PV_VOL_DEFAULT/3 );
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        // �͂��������E�C���h�E���o��
        wk->pYesNoWork =
            BmpYesNoSelectInit( wk->bgl,
                                &_yesNoBmpDat,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                HEAPID_WIFIP2PMATCH );
        wk->seq = WIFIP2PMATCH_MODE_BCANCEL_WAIT;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   B�L�����Z��  WIFIP2PMATCH_MODE_BCANCEL_WAIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int WifiP2PMatch_BCancelWait( WIFIP2PMATCH_WORK *wk, int seq )        // WIFIP2PMATCH_MODE_VCT_CONNECT
{
    int i;
    int ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);

    if( 0 !=  _checkParentConnect(wk)){ // �ڑ����Ă���
        if(ret == BMPMENU_NULL){
            BmpYesNoWinDel(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);
        }
        wk->seq = WIFIP2PMATCH_MODE_MATCH_LOOP;
    }
    else if(ret == BMPMENU_NULL){  // �܂��I��
        return seq;
    }else if(ret == 0){ // �͂���I�������ꍇ
        _myVChatStatusOrgSet(wk);
        _myStatusChange(wk, WIFI_STATUS_LOGIN_WAIT);
        CommStateWifiMatchEnd();
        wk->preConnect = -1;
        wk->seq = WIFIP2PMATCH_MODE_FRIENDLIST;
    }
    else{  // ��������I�������ꍇ
        wk->seq = WIFIP2PMATCH_MODE_MATCH_LOOP;
    }
    EndMessageWindowOff(wk);
    return seq;
}

//--------------------------------

//------------------------------------------------------------------
/**
 * $brief   �e�@��t�܂��B�q�@���牞�傪���������Ƃ�m�点��
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _parentModeCallMenuInit( WIFIP2PMATCH_WORK *wk, int seq )
{
    int mySt = wk->pMatch->myMatchStatus.status;
    int targetSt = wk->pMatch->friendMatchStatus[ mydwc_getFriendIndex() ].status;

    if((mySt == WIFI_STATUS_DBATTLE50_WAIT)&&(targetSt == WIFI_STATUS_DBATTLE50)){
        wk->seq = WIFIP2PMATCH_MODE_CALL_YESNO;  //ok
    }
    else if((mySt == WIFI_STATUS_DBATTLE100_WAIT)&&(targetSt == WIFI_STATUS_DBATTLE100)){
        wk->seq = WIFIP2PMATCH_MODE_CALL_YESNO;  //ok
    }
    else if((mySt == WIFI_STATUS_DBATTLE_FREE_WAIT)&&(targetSt == WIFI_STATUS_DBATTLE_FREE)){
        wk->seq = WIFIP2PMATCH_MODE_CALL_YESNO;  //ok
    }
    else if((mySt == WIFI_STATUS_SBATTLE50_WAIT)&&(targetSt == WIFI_STATUS_SBATTLE50)){
        wk->seq = WIFIP2PMATCH_MODE_CALL_YESNO;  //ok
    }
    else if((mySt == WIFI_STATUS_SBATTLE100_WAIT)&&(targetSt == WIFI_STATUS_SBATTLE100)){
        wk->seq = WIFIP2PMATCH_MODE_CALL_YESNO;  //ok
    }
    else if((mySt == WIFI_STATUS_SBATTLE_FREE_WAIT)&&(targetSt == WIFI_STATUS_SBATTLE_FREE)){
        wk->seq = WIFIP2PMATCH_MODE_CALL_YESNO;  //ok
    }
    else if((mySt == WIFI_STATUS_TRADE_WAIT)&&(targetSt == WIFI_STATUS_TRADE)){
        wk->seq = WIFIP2PMATCH_MODE_CALL_YESNO;  //ok
    }
    else if((mySt == WIFI_STATUS_LOGIN_WAIT)&&(targetSt == WIFI_STATUS_VCT)){
        wk->seq = WIFIP2PMATCH_MODE_VCT_CONNECT_INIT; //ok
        return seq;
    }
    else{
        // �K�����Ȃ�=>�ؒf������
        _friendNameExpand(wk, mydwc_getFriendIndex());
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_015, FALSE);
        wk->seq = WIFIP2PMATCH_MODE_DISCONNECT;
        _myStatusChange(wk, WIFI_STATUS_LOGIN_WAIT);
        CommStateWifiMatchEnd();
        return seq;
    }
    _friendNameExpand(wk, mydwc_getFriendIndex());
    WifiP2PMatchMessagePrint(wk, msg_wifilobby_008, FALSE);
    CommInfoInitialize(wk->pSaveData,NULL);   //Info������
    wk->seq = WIFIP2PMATCH_MODE_CALL_YESNO;
    wk->timer = 30;
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �R�l�N�V�����͂낤�Ƃ��Ă�����Ԓ��̃G���[�\��
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static BOOL _connectingErrFunc(WIFIP2PMATCH_WORK *wk)
{
    if(CommWifiIsMatched() >= 3){
        _friendNameExpand(wk, wk->preConnect);
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_015, FALSE);
        wk->seq = WIFIP2PMATCH_MODE_VCT_DISCONNECT;
    }
    else if(CommStateIsWifiError()){
        _errorDisp(wk);
    }
    else{
        return FALSE;
    }
    wk->bRetryBattle = FALSE;
    return TRUE;
}

//------------------------------------------------------------------
/**
 * $brief   �Ȃ���ׂ��X�e�[�g�m�F  WIFIP2PMATCH_MODE_CALL_YESNO
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int _parentModeCallMenuYesNo( WIFIP2PMATCH_WORK *wk, int seq )
{
    if((CommWifiIsMatched() >= 4) || CommStateIsWifiDisconnect() || !CommIsConnect(COMM_PARENT_ID)){
        if(wk->bRetryBattle){
            WifiP2PMatchMessagePrint(wk, msg_wifilobby_065, FALSE);
        }
        else{
            _friendNameExpand(wk, wk->preConnect);
            WifiP2PMatchMessagePrint(wk, msg_wifilobby_015, FALSE);
        }
        wk->bRetryBattle = FALSE;
        wk->seq = WIFIP2PMATCH_MODE_VCT_DISCONNECT;
    }
    else if(_connectingErrFunc(wk)){
    }
    else{
        if(wk->timer==0){
            if(CommIsTimingSync(_TIMING_GAME_CHECK)){
                CommToolTempDataReset();
                CommTimingSyncStart(_TIMING_GAME_CHECK2);
                wk->bRetryBattle = FALSE;
                wk->seq = WIFIP2PMATCH_MODE_CALL_SEND;
            }
        }
        else{
            wk->timer--;
            if(wk->timer == 0){
                CommTimingSyncStart(_TIMING_GAME_CHECK);
            }
        }
    }
    return seq;
}

//
//------------------------------------------------------------------
/**
 * $brief   �Ȃ���ׂ��X�e�[�g�𑗐M  WIFIP2PMATCH_MODE_CALL_SEND
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _parentModeCallMenuSend( WIFIP2PMATCH_WORK *wk, int seq )
{
    if(_connectingErrFunc(wk)){
    }
    else if(CommIsTimingSync(_TIMING_GAME_CHECK2)){
        u16 status = wk->pMatch->myMatchStatus.status;
        CommToolSetTempData(CommGetCurrentID() ,&status);
        wk->seq = WIFIP2PMATCH_MODE_CALL_CHECK;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �Ȃ���ׂ��X�e�[�g���  WIFIP2PMATCH_MODE_CALL_CHECK
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int _parentModeCallMenuCheck( WIFIP2PMATCH_WORK *wk, int seq )
{
    const u16* pData = CommToolGetTempData(1 - CommGetCurrentID());

    if(_connectingErrFunc(wk)){
    }
    else if(pData!=NULL){
        u16 status = _convertState(wk->pMatch->myMatchStatus.status);
        if((pData[0] == status) || (pData[0] == wk->pMatch->myMatchStatus.status)){
            CommTimingSyncStart(_TIMING_GAME_START);
            wk->seq = WIFIP2PMATCH_MODE_MYSTATUS_WAIT;
        }
        else{  // �قȂ�X�e�[�g��I�������ꍇ
            _friendNameExpand(wk, mydwc_getFriendIndex());
            WifiP2PMatchMessagePrint(wk, msg_wifilobby_013, FALSE);
            wk->seq = WIFIP2PMATCH_MODE_VCT_DISCONNECT;
        }
    }
    return seq;
}



//------------------------------------------------------------------
/**
 * $brief   �^�C�~���O�R�}���h�҂� WIFIP2PMATCH_MODE_MYSTATUS_WAIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int _parentModeCallMyStatusWait( WIFIP2PMATCH_WORK *wk, int seq )
{
    int status;

    if(_connectingErrFunc(wk)){
    }
    else if(CommIsTimingSync(_TIMING_GAME_START)){
        CommInfoSendPokeData();
        CommStateSetErrorCheck(TRUE,TRUE);
        CommTimingSyncStart(_TIMING_GAME_START2);
        wk->seq = WIFIP2PMATCH_MODE_CALL_WAIT;
    }
    return seq;
}



//------------------------------------------------------------------
/**
 * $brief   �^�C�~���O�R�}���h�҂� WIFIP2PMATCH_MODE_CALL_WAIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static int _parentModeCallMenuWait( WIFIP2PMATCH_WORK *wk, int seq )
{
    int status;
    int checkFriend[COMM_MACHINE_MAX];

    if(_connectingErrFunc(wk)){
    }
    else if(CommIsTimingSync(_TIMING_GAME_START2)){
        dwc_friendAutoInputCheck(wk->pSaveData, checkFriend, HEAPID_WIFIP2PMATCH);
        
        EndMessageWindowOff(wk);

        status = wk->pMatch->friendMatchStatus[ mydwc_getFriendIndex() ].status;
        if((status == WIFI_STATUS_TRADE_WAIT) || (status == WIFI_STATUS_TRADE)){
            status = WIFI_STATUS_TRADE;
            wk->endSeq = WIFI_P2PMATCH_TRADE;
        }
        else if((status == WIFI_STATUS_SBATTLE50_WAIT) || (status == WIFI_STATUS_SBATTLE50)){
            status = WIFI_STATUS_SBATTLE50;
            wk->endSeq = WIFI_P2PMATCH_SBATTLE50;
        }
        else if((status == WIFI_STATUS_SBATTLE100_WAIT) || (status == WIFI_STATUS_SBATTLE100)){
            status = WIFI_STATUS_SBATTLE100;
            wk->endSeq = WIFI_P2PMATCH_SBATTLE100;
        }
        else if((status == WIFI_STATUS_SBATTLE_FREE_WAIT) || (status == WIFI_STATUS_SBATTLE_FREE)){
            status = WIFI_STATUS_SBATTLE_FREE;
            wk->endSeq = WIFI_P2PMATCH_SBATTLE_FREE;
        }
        else if((status == WIFI_STATUS_DBATTLE50_WAIT) || (status == WIFI_STATUS_DBATTLE50)){
            status = WIFI_STATUS_DBATTLE50;
            wk->endSeq = WIFI_P2PMATCH_DBATTLE50;
        }
        else if((status == WIFI_STATUS_DBATTLE100_WAIT) || (status == WIFI_STATUS_DBATTLE100)){
            status = WIFI_STATUS_DBATTLE100;
            wk->endSeq = WIFI_P2PMATCH_DBATTLE100;
        }
        else if((status == WIFI_STATUS_DBATTLE_FREE_WAIT) || (status == WIFI_STATUS_DBATTLE_FREE)){
            status = WIFI_STATUS_DBATTLE_FREE;
            wk->endSeq = WIFI_P2PMATCH_DBATTLE_FREE;
        }

// WIFI�@�ΐ�AUTOӰ�ރf�o�b�N
#ifdef _WIFI_DEBUG_TUUSHIN
		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_A_REQ = FALSE;
		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_TOUCH_REQ = FALSE;
#endif	//_WIFI_DEBUG_TUUSHIN

        _myStatusChange(wk, status);  // �ڑ����ɂȂ�
        CommSetWifiBothNet(TRUE); // wifi�̒ʐM��񓯊����瓯����
        WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK,
                        COMM_BRIGHTNESS_SYNC, 1, HEAPID_WIFIP2PMATCH);
        seq = SEQ_OUT;						//�I���V�[�P���X��
    }
    return seq;
}


//------------------------------------------------------------------
/**
 * $brief   ���C�����j���[�̖߂�ۂ̏�����
 *
 * @param   wk
 *
 * @retval  none
 */
//------------------------------------------------------------------
static int WifiP2PMatch_MainReturn( WIFIP2PMATCH_WORK *wk, int seq )
{
    GF_BGL_ScrClear(wk->bgl, GF_BGL_FRAME3_M);
    ArcUtil_ScrnSet(   ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_02_NSCR, wk->bgl,
                       GF_BGL_FRAME0_M, 0, 0, 0, HEAPID_WIFIP2PMATCH);
    wk->mainCur = 0;
    wk->seq = WIFIP2PMATCH_FRIENDLIST_INIT;
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �l�f�[�^�\�������� WIFIP2PMATCH_MODE_PERSONAL_INIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _personalDataInit( WIFIP2PMATCH_WORK *wk, int seq )
{
    u16 mainCursor, friendNo;
    int num,length,x,width;

    GF_BGL_ScrClear(wk->bgl, GF_BGL_FRAME3_M);
    ArcUtil_ScrnSet(   ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_03_NSCR, wk->bgl,
                       GF_BGL_FRAME1_M, 0, 0, 0, HEAPID_WIFIP2PMATCH);

    CLACT_SetDrawFlag( wk->MainActWork[_CLACT_DOWN_CUR], 0 );
    CLACT_SetDrawFlag( wk->MainActWork[_CLACT_LINE_CUR], 0 );
    CLACT_SetDrawFlag( wk->MainActWork[_CLACT_UP_CUR], 0 );

    if(GF_BGL_BmpWinAddCheck(&wk->MyWin)){
        BmpMenuWinClear(&wk->MyWin, WINDOW_TRANS_ON );
        GF_BGL_BmpWinDel(&wk->MyWin);
    }
    GF_BGL_BmpWinAdd(wk->bgl,&wk->MyWin,
                     GF_BGL_FRAME3_M, 3, 2, 0x1a, 14, FLD_SYSFONT_PAL, 1);
    width = ( 0x1a * 8 )-2;
    GF_BGL_BmpWinDataFill( &wk->MyWin, 0x8000 );

    BmpListDirectPosGet(wk->lw,&mainCursor);
    friendNo = wk->index2No[mainCursor] - 1;
    OHNO_PRINT("�t�����h�ԍ�  %d\n", friendNo);
    _friendNameExpand(wk, friendNo);
    MSGMAN_GetString(  wk->MsgManager, msg_wifilobby_033, wk->pExpStrBuf );
    WORDSET_ExpandStr( wk->WordSet, wk->TitleString, wk->pExpStrBuf );
    GF_STR_PrintColor( &wk->MyWin, FONT_TALK, wk->TitleString, 0, 0, MSG_NO_PUT, _COL_N_BLACK, NULL);
        GF_BGL_BmpWinOnVReq(&wk->MyWin);

    WifiP2PMatchMessagePrint(wk, msg_wifilobby_042, FALSE);


    {
        MYSTATUS* pTarget = MyStatus_AllocWork(HEAPID_WIFIP2PMATCH);
        MyStatus_SetMyName(pTarget, WifiList_GetFriendGroupNamePtr(wk->pList,friendNo));
        WORDSET_RegisterPlayerName( wk->WordSet, 0, pTarget);
        sys_FreeMemoryEz(pTarget);
    }
    MSGMAN_GetString(  wk->MsgManager, msg_wifilobby_034, wk->pExpStrBuf );
    WORDSET_ExpandStr( wk->WordSet, wk->TitleString, wk->pExpStrBuf );
    GF_STR_PrintColor( &wk->MyWin, FONT_SYSTEM, wk->TitleString, 0, 8*2, MSG_NO_PUT, _COL_N_BLACK, NULL);

    // �ΐ퐬��
    MSGMAN_GetString(  wk->MsgManager, msg_wifilobby_035, wk->TitleString );
    GF_STR_PrintColor( &wk->MyWin, FONT_SYSTEM, wk->TitleString, 0, 8*4, MSG_NO_PUT, _COL_N_BLACK, NULL);
    // ����
    num = WifiList_GetFriendInfo(wk->pList, friendNo, WIFILIST_FRIEND_BATTLE_WIN);
    WORDSET_RegisterNumber(wk->WordSet, 0, num, 4, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
    MSGMAN_GetString(  wk->MsgManager, msg_wifilobby_036, wk->pExpStrBuf );
    WORDSET_ExpandStr( wk->WordSet, wk->TitleString, wk->pExpStrBuf );
    GF_STR_PrintColor( &wk->MyWin, FONT_SYSTEM, wk->TitleString, 30, 8*6, MSG_NO_PUT, _COL_N_BLACK, NULL);
    // �܂�
    num = WifiList_GetFriendInfo(wk->pList, friendNo, WIFILIST_FRIEND_BATTLE_LOSE);
    WORDSET_RegisterNumber(wk->WordSet, 0, num, 4, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
    MSGMAN_GetString(  wk->MsgManager, msg_wifilobby_037, wk->pExpStrBuf );
    WORDSET_ExpandStr( wk->WordSet, wk->TitleString, wk->pExpStrBuf );

    length = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->TitleString, 0 );
    x      = width - length;
    GF_STR_PrintColor( &wk->MyWin, FONT_SYSTEM, wk->TitleString, x, 8*6, MSG_NO_PUT, _COL_N_BLACK, NULL);
    // �|�P��������
    MSGMAN_GetString(  wk->MsgManager, msg_wifilobby_038, wk->TitleString );
    GF_STR_PrintColor( &wk->MyWin, FONT_SYSTEM, wk->TitleString, 0,  8*8, MSG_NO_PUT, _COL_N_BLACK, NULL);

    num = WifiList_GetFriendInfo(wk->pList, friendNo, WIFILIST_FRIEND_TRADE_NUM);
    WORDSET_RegisterNumber(wk->WordSet, 0, num, 4, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
    MSGMAN_GetString(  wk->MsgManager, msg_wifilobby_039, wk->pExpStrBuf );
    WORDSET_ExpandStr( wk->WordSet, wk->TitleString, wk->pExpStrBuf );

    length = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->TitleString, 0 );
    x      = width - length;
    GF_STR_PrintColor( &wk->MyWin, FONT_SYSTEM, wk->TitleString, x, 8*8, MSG_NO_PUT, _COL_N_BLACK, NULL);
    //�Ō�̓��t
    MSGMAN_GetString(  wk->MsgManager, msg_wifilobby_040, wk->TitleString );
    GF_STR_PrintColor( &wk->MyWin, FONT_SYSTEM, wk->TitleString, 0, 8*10, MSG_NO_PUT, _COL_N_BLACK, NULL);

    num = WifiList_GetFriendInfo(wk->pList, friendNo, WIFILIST_FRIEND_LASTBT_DAY);
    if(num!=0){
        WORDSET_RegisterNumber(wk->WordSet, 2, num, 2, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
        num = WifiList_GetFriendInfo(wk->pList, friendNo, WIFILIST_FRIEND_LASTBT_YEAR);
        WORDSET_RegisterNumber(wk->WordSet, 0, num, 4, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
        num = WifiList_GetFriendInfo(wk->pList, friendNo, WIFILIST_FRIEND_LASTBT_MONTH);
        WORDSET_RegisterNumber(wk->WordSet, 1, num, 2, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
        MSGMAN_GetString(  wk->MsgManager, msg_wifilobby_041, wk->pExpStrBuf );
        WORDSET_ExpandStr( wk->WordSet, wk->TitleString, wk->pExpStrBuf );
        length = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->TitleString, 0 );
        x      = width - length;
        GF_STR_PrintColor( &wk->MyWin, FONT_SYSTEM, wk->TitleString, x, 8*12, MSG_NO_PUT, _COL_N_BLACK, NULL);
    }
    GF_BGL_BmpWinOnVReq(&wk->MyWin);
    wk->seq = WIFIP2PMATCH_MODE_PERSONAL_WAIT;
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �l�f�[�^�\�� WIFIP2PMATCH_MODE_PERSONAL_WAIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _personalDataWait( WIFIP2PMATCH_WORK *wk, int seq )
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) != 0 ){
        return seq;
    }
    if( 0 !=  _checkParentConnect(wk)){ // �ڑ����Ă���
        wk->seq = WIFIP2PMATCH_MODE_PERSONAL_END;
    }
    if(sys.trg & (PAD_BUTTON_CANCEL|PAD_BUTTON_DECIDE)){
        wk->seq = WIFIP2PMATCH_MODE_PERSONAL_END;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �l�f�[�^�\������� WIFIP2PMATCH_MODE_PERSONAL_END
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _personalDataEnd( WIFIP2PMATCH_WORK *wk, int seq )
{
    int i,x;
    int num = 0;

    BmpMenuWinClear(&wk->MyWin, WINDOW_TRANS_ON );
    GF_BGL_BmpWinDel(&wk->MyWin);
    GF_BGL_ScrClear(wk->bgl, GF_BGL_FRAME1_M);
    GF_BGL_ScrClear(wk->bgl, GF_BGL_FRAME3_M);
    EndMessageWindowOff(wk);

    ArcUtil_ScrnSet(   ARC_WIFIP2PMATCH_GRA, NARC_wifip2pmatch_conect_02_NSCR, wk->bgl,
                       GF_BGL_FRAME0_M, 0, 0, 0, HEAPID_WIFIP2PMATCH);
    GF_BGL_BmpWinDataFill( &wk->TitleWin, 0x8000 );
    MSGMAN_GetString(  wk->MsgManager, msg_wifilobby_019, wk->TitleString );
    GF_STR_PrintColor( &wk->TitleWin, FONT_TALK, wk->TitleString, 0, 0, MSG_NO_PUT, _COL_N_WHITE, NULL);
        GF_BGL_BmpWinOnVReq(&wk->TitleWin);

    _readFriendMatchStatus(wk);
    _userDataDisp(wk);
    _iconMenuDisp(wk,0);
    _myStatusChange(wk, wk->pMatch->myMatchStatus.status);

    CLACT_SetDrawFlag( wk->MainActWork[_CLACT_LINE_CUR], 1 );
    wk->seq = WIFIP2PMATCH_MODE_FRIENDLIST;
    wk->friendMatchReadCount = -1;
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �I���m�F���b�Z�[�W  WIFIP2PMATCH_MODE_EXIT_YESNO
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _exitYesNo( WIFIP2PMATCH_WORK *wk, int seq )
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        // �͂��������E�C���h�E���o��
        wk->pYesNoWork =
            BmpYesNoSelectInit( wk->bgl,
                                &_yesNoBmpDat,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                HEAPID_WIFIP2PMATCH );
        wk->seq = WIFIP2PMATCH_MODE_EXIT_WAIT;
    }
	
// WIFI�@�ΐ�AUTOӰ�ރf�o�b�N
#ifdef _WIFI_DEBUG_TUUSHIN
	WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_A_REQ = TRUE;
	WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_B_REQ = FALSE;
#endif	//_WIFI_DEBUG_TUUSHIN
	
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �I���m�F���b�Z�[�W  WIFIP2PMATCH_MODE_EXIT_WAIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _exitWait( WIFIP2PMATCH_WORK *wk, int seq )
{
    int i;
    int ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);

    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) != 0 ){
        return seq;
    }
    if(ret == BMPMENU_NULL){  // �܂��I��
        return seq;
    }else if(ret == 0){ // �͂���I�������ꍇ
        WifiP2PMatchMessagePrint(wk, dwc_message_0011, TRUE);
        wk->seq = WIFIP2PMATCH_MODE_EXITING;
        wk->timer = 1;
    }
    else{  // ��������I�������ꍇ
        EndMessageWindowOff(wk);
        wk->seq = WIFIP2PMATCH_MODE_FRIENDLIST;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �I���m�F���b�Z�[�W  WIFIP2PMATCH_MODE_EXIT_WAIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _exitExiting( WIFIP2PMATCH_WORK *wk, int seq )
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) != 0 ){
        return seq;
    }
    if(wk->timer == 1){
        wk->timer = 0;
        CommStateWifiLogout();  // �I��
    }
    if(!CommStateIsInitialize()){
        OHNO_PRINT("�ؒf�������Ƀt�����h�R�[�h���l�߂�\n");
        WifiList_FormUpData(wk->pList);  // �ؒf�������Ƀt�����h�R�[�h���l�߂�
        //SaveData_SaveParts(wk->pSaveData, SVBLK_ID_NORMAL);  //�Z�[�u��
        WifiP2PMatchMessagePrint(wk, dwc_message_0012, TRUE);
        wk->seq = WIFIP2PMATCH_MODE_EXIT_END;
        wk->timer = 30;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �I������  WIFIP2PMATCH_MODE_EXIT_END
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------


static int _exitEnd( WIFIP2PMATCH_WORK *wk, int seq )
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) != 0 ){
        return seq;
    }
    wk->timer--;
    if(wk->timer==0){
        wk->endSeq = WIFI_P2PMATCH_END;
        wk->seq = WIFIP2PMATCH_MODE_END_WAIT;
        EndMessageWindowOff(wk);
    }

// WIFI�@�ΐ�AUTOӰ�ރf�o�b�N
#ifdef _WIFI_DEBUG_TUUSHIN
	WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_A_REQ = FALSE;
	WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_B_REQ = FALSE;
	WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_TOUCH_REQ = FALSE;
#endif	//_WIFI_DEBUG_TUUSHIN
    return seq;
}


//------------------------------------------------------------------
/**
 * $brief   ������x�ΐ킷�邩���� WIFIP2PMATCH_NEXTBATTLE_YESNO
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _nextBattleYesNo( WIFIP2PMATCH_WORK *wk, int seq )
{
    CommStateSetErrorCheck(FALSE,FALSE);
    if(CommIsTimingSync(_TIMING_BATTLE_END)==FALSE){
        return seq;
    }
//    CommStateSetErrorCheck(FALSE,FALSE);
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        // �͂��������E�C���h�E���o��
        wk->pYesNoWork =
            BmpYesNoSelectInit( wk->bgl,
                                &_yesNoBmpDat,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                HEAPID_WIFIP2PMATCH );
        wk->seq = WIFIP2PMATCH_NEXTBATTLE_WAIT;
    }
	
// WIFI�@�ΐ�AUTOӰ�ރf�o�b�N
#ifdef _WIFI_DEBUG_TUUSHIN
	WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_A_REQ = FALSE;
	WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_TOUCH_REQ = FALSE;
	WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_B_REQ = TRUE;
#endif	//_WIFI_DEBUG_TUUSHIN
	
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   ������x�ΐ킷�邩���� WIFIP2PMATCH_NEXTBATTLE_WAIT
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _nextBattleWait( WIFIP2PMATCH_WORK *wk, int seq )
{
    int i;
    int ret;

    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) != 0 ){
        return seq;
    }

    if(CommStateIsWifiLoginState() || CommStateIsWifiDisconnect() || (CommWifiIsMatched() >= 3)){  // �ؒf���������Ƃ�
        BmpYesNoWinDel(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_065, FALSE);
        wk->seq = WIFIP2PMATCH_MODE_BATTLE_DISCONNECT;
    }
    else if(CommStateIsWifiError()){
        BmpYesNoWinDel(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);
        _errorDisp(wk);
    }
    else{
        ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);
        if(ret == BMPMENU_NULL){  // �܂��I��
            return seq;
        }else if(ret == 0){ // �͂���I�������ꍇ
            //EndMessageWindowOff(wk);
            WifiP2PMatchMessagePrint(wk, msg_wifilobby_073, FALSE);
            wk->timeWaitWork = TimeWaitIconAdd( &wk->MsgWin, COMM_TALK_WIN_CGX_NUM );
            wk->bRetryBattle = TRUE;
            wk->seq = WIFIP2PMATCH_MODE_CALL_YESNO;
            wk->timer = 30;
        }
        else{  // ��������I�������ꍇ
            EndMessageWindowOff(wk);
            CommStateWifiBattleMatchEnd();
            wk->timer = _RECONECTING_WAIT_TIME;
            wk->seq = WIFIP2PMATCH_RECONECTING_WAIT;
        }
        wk->pMatch = CommStateGetMatchWork();
        wk->pMatch->myMatchStatus.vchat = wk->pMatch->myMatchStatus.vchat_org;
    }
    return seq;
}


//------------------------------------------------------------------
/**
 * $brief   VCAHT��ύX���Ă��������ǂ������� WIFIP2PMATCH_MODE_VCHAT_NEGO
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _vchatNegoCheck( WIFIP2PMATCH_WORK *wk, int seq )
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        // �͂��������E�C���h�E���o��
        wk->pYesNoWork =
            BmpYesNoSelectInit( wk->bgl,
                                &_yesNoBmpDat,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                HEAPID_WIFIP2PMATCH );
        wk->seq = WIFIP2PMATCH_MODE_VCHAT_NEGO_WAIT;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   VCAHT��ύX���Ă��������ǂ�������
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static int _vchatNegoWait( WIFIP2PMATCH_WORK *wk, int seq )
{
    int i;
    int ret,status;

    if(CommWifiIsMatched() >= 3){
        BmpYesNoWinDel(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);
        WifiP2PMatchMessagePrint(wk, msg_wifilobby_065, FALSE);
        wk->seq = WIFIP2PMATCH_MODE_BATTLE_DISCONNECT;
    }
    else if(CommStateIsWifiError()){
        BmpYesNoWinDel(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);
        _errorDisp(wk);
    }
    else{
        ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_WIFIP2PMATCH);
        if(ret == BMPMENU_NULL){  // �܂��I��
            return seq;
        }else if(ret == 0){ // �͂���I�������ꍇ
            // �ڑ��J�n
            status = _convertState(wk->keepStatus);
            if(WIFI_STATUS_UNKNOWN == status){   // ���m�̃X�e�[�g�̏ꍇ���������悤�ɖ߂�
            }
            else if( mydwc_getFriendStatus(wk->friendNo - 1) == DWC_STATUS_MATCH_SC_SV ){
                if( CommWifiBattleStart( wk->friendNo - 1 ) ){
                    CommSetWifiBothNet(FALSE);  // VCT���͓������M�̕K�v�Ȃ�
                    _myVChatStatusToggle(wk); // ������VCHAT�𔽓]
                    _myStatusChange(wk, status);  // �ڑ����ɂȂ�
                    _friendNameExpand(wk, wk->friendNo - 1);
                    WifiP2PMatchMessagePrint(wk,msg_wifilobby_014, FALSE);
                    wk->timeWaitWork = TimeWaitIconAdd( &wk->MsgWin, COMM_TALK_WIN_CGX_NUM );
                    if(status != WIFI_STATUS_VCT){
                        wk->seq = WIFIP2PMATCH_MODE_MATCH_LOOP;  // �}�b�`���O��
                        return seq;
                    }
                    else{
                        wk->seq = WIFIP2PMATCH_MODE_VCT_CONNECT_INIT2;  //VCT��p��
                        return seq;
                    }
                }
            }
        }
        // ��������I�������ꍇ  �������͓K�����Ȃ��ꍇ
        EndMessageWindowOff(wk);
        wk->seq = WIFIP2PMATCH_MODE_FRIENDLIST;
        return seq;
        
    }
    return seq;
}







// WIFIP2PMATCH_MODE_END_WAIT
//------------------------------------------------------------------
/**
 * $brief   �I��
 *
 * @param   wk
 * @param   seq
 *
 * @retval  int
 */
//------------------------------------------------------------------
static int 	WifiP2PMatch_EndWait( WIFIP2PMATCH_WORK *wk, int seq )
{
    if(!CommStateIsInitialize()){
        WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK,
                        COMM_BRIGHTNESS_SYNC, 1, HEAPID_WIFIP2PMATCH);
        seq = SEQ_OUT;						//�I���V�[�P���X��
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   ��b�E�C���h�E�\��
 *
 * @param   wk
 *
 * @retval  none
 */
//------------------------------------------------------------------


static void WifiP2PMatchMessagePrint( WIFIP2PMATCH_WORK *wk, int msgno, BOOL bSystem )
{
    // ������擾
    u8 speed = CONFIG_GetMsgPrintSpeed(SaveData_GetConfig(wk->pSaveData));

    if(GF_BGL_BmpWinAddCheck(&wk->SysMsgWin)){
        BmpTalkWinClear(&wk->SysMsgWin, WINDOW_TRANS_ON );
        GF_BGL_BmpWinDel( &wk->SysMsgWin);
    }
    if(GF_BGL_BmpWinAddCheck(&wk->MsgWin)){
        BmpTalkWinClear(&wk->MsgWin, WINDOW_TRANS_ON );
        GF_BGL_BmpWinDel(&wk->MsgWin);
    }
    if(wk->MsgIndex != _PRINTTASK_MAX){
        if(GF_MSG_PrintEndCheck(wk->MsgIndex)!=0){
            GF_STR_PrintForceStop(wk->MsgIndex);
            wk->MsgIndex = _PRINTTASK_MAX;
        }
    }
    
    GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin,
                     GF_BGL_FRAME2_M,
                     COMM_MSG_WIN_PX, COMM_MSG_WIN_PY,
                     COMM_MSG_WIN_SX, COMM_MSG_WIN_SY,
                     COMM_MESFONT_PAL, COMM_MSG_WIN_CGX);
    if(bSystem){
        MSGMAN_GetString(  wk->SysMsgManager, msgno, wk->pExpStrBuf );
    }
    else{
        MSGMAN_GetString(  wk->MsgManager, msgno, wk->pExpStrBuf );
    }
    WORDSET_ExpandStr( wk->WordSet, wk->TalkString, wk->pExpStrBuf );
    // ��b�E�C���h�E�g�`��
    GF_BGL_BmpWinDataFill(&wk->MsgWin, 15 );
    BmpTalkWinWrite(&wk->MsgWin, WINDOW_TRANS_OFF,COMM_TALK_WIN_CGX_NUM, COMM_MESFRAME_PAL );
    // ������`��J�n
	MsgPrintSkipFlagSet( MSG_SKIP_ON );		// ���b�Z�[�W�X�L�b�vON
	MsgPrintAutoFlagSet( MSG_AUTO_OFF );	// ���b�Z�[�W��������OFF
    wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString,
                                       0, 0, speed, NULL);
    GF_BGL_BmpWinOnVReq(&wk->MsgWin);
}

//------------------------------------------------------------------
/**
 * $brief   �V�X�e�����b�Z�[�W�E�C���h�E�\��
 *
 * @param   wk
 *
 * @retval  none
 */
//------------------------------------------------------------------

static void _systemMessagePrint( WIFIP2PMATCH_WORK *wk, int msgno )
{
    _timeWaitIconDel(wk);
    if(GF_BGL_BmpWinAddCheck(&wk->SysMsgWin)){
        BmpTalkWinClear(&wk->SysMsgWin, WINDOW_TRANS_ON );
        GF_BGL_BmpWinDel( &wk->SysMsgWin);
    }
    if(GF_BGL_BmpWinAddCheck(&wk->MsgWin)){
        BmpTalkWinClear(&wk->MsgWin, WINDOW_TRANS_ON );
        GF_BGL_BmpWinDel(&wk->MsgWin);
    }
    GF_BGL_BmpWinAdd(wk->bgl, &wk->SysMsgWin,
                     GF_BGL_FRAME2_M,
                     COMM_SYS_WIN_PX, COMM_SYS_WIN_PY,
                     COMM_SYS_WIN_SX, COMM_SYS_WIN_SY,
                     COMM_MESFONT_PAL, COMM_SYS_WIN_CGX);
    MSGMAN_GetString(  wk->SysMsgManager, msgno, wk->pExpStrBuf );
    WORDSET_ExpandStr( wk->WordSet, wk->TalkString, wk->pExpStrBuf );
    // ��b�E�C���h�E�g�`��
    GF_BGL_BmpWinDataFill(&wk->SysMsgWin, 15 );
    BmpMenuWinWrite(&wk->SysMsgWin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
    // ������`��J�n
    wk->MsgIndex = GF_STR_PrintSimple( &wk->SysMsgWin, FONT_TALK,
                                       wk->TalkString, 0, 0, MSG_NO_PUT, NULL);
    GF_BGL_BmpWinOnVReq(&wk->SysMsgWin);
}

//------------------------------------------------------------------
/**
 * $brief   �F�l�ԍ��̖��O��expand����
 * @param   msg_index
 * @retval  int		    int friend = mydwc_getFriendIndex();

 */
//------------------------------------------------------------------
static void _friendNameExpand( WIFIP2PMATCH_WORK *wk, int friendNo)
{
    if(friendNo != -1){
        MYSTATUS* pTarget = MyStatus_AllocWork(HEAPID_WIFIP2PMATCH);
        MyStatus_SetMyName(pTarget, WifiList_GetFriendNamePtr(wk->pList,friendNo));
        WORDSET_RegisterPlayerName( wk->WordSet, 0, pTarget);
        sys_FreeMemoryEz(pTarget);
    }
}


//------------------------------------------------------------------
/**
 * $brief
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static void EndMessageWindowOff( WIFIP2PMATCH_WORK *wk )
{
    _timeWaitIconDel(wk);
    if(wk->MsgIndex != _PRINTTASK_MAX){
        if(GF_MSG_PrintEndCheck(wk->MsgIndex)!=0){
            GF_STR_PrintForceStop(wk->MsgIndex);
            wk->MsgIndex = _PRINTTASK_MAX;
        }
    }
    if(GF_BGL_BmpWinAddCheck(&wk->MsgWin)){
        BmpTalkWinClear(&wk->MsgWin, WINDOW_TRANS_ON );
        GF_BGL_BmpWinDel( &wk->MsgWin );
    }
}

//------------------------------------------------------------------
/**
 * $brief
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static void _myStatusChange(WIFIP2PMATCH_WORK *wk, int status)
{
    if(wk->pMatch->myMatchStatus.status != status){
        wk->pMatch->myMatchStatus.status = status;
        if(_modeBattle(status) || (status == WIFI_STATUS_TRADE)){
            //     Snd_BgmFadeOut( 24, BGM_FADE_VCHAT_TIME);
        }
        else if(status == WIFI_STATUS_VCT){
            Snd_BgmFadeOut( 0, BGM_FADE_VCHAT_TIME);
        }
        else if(status == WIFI_STATUS_LOGIN_WAIT){    // �ҋ@���@���O�C������͂���
			//�{�C�X�`���b�g���I�����Ă���̂ŁA�ݒ艹�ʂ������l�ɖ߂��I
			//�{���͐ݒ肵�Ă��鏉�����ʂɖ߂��Ȃ��Ƃ����Ȃ����B�B�Ƃ肠��������őΏ��I
			Snd_PlayerSetInitialVolumeBySeqNo( _BGM_MAIN, BGM_WIFILOBBY_VOL );
			Snd_PlayerMoveVolume( SND_HANDLE_BGM, BGM_WIFILOBBY_START_VOL, 0 );
            Snd_BgmFadeIn( BGM_VOL_MAX, BGM_FADE_VCHAT_TIME, BGM_FADEIN_START_VOL_NOW);
            OHNO_PRINT("Snd_BgmFadeIn\n");
        }
    }
    mydwc_setMyInfo( &(wk->pMatch->myMatchStatus), sizeof(_WIFI_MACH_STATUS) );
    _userDataInfoDisp(wk);
}

//------------------------------------------------------------------
/**
 * $brief   VCHAT�t���O�̐؂�ւ�
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static BOOL _myVChatStatusToggle(WIFIP2PMATCH_WORK *wk)
{
    wk->pMatch->myMatchStatus.vchat = 1 - wk->pMatch->myMatchStatus.vchat;
    mydwc_setVChat(wk->pMatch->myMatchStatus.vchat);
    mydwc_setMyInfo( &(wk->pMatch->myMatchStatus), sizeof(_WIFI_MACH_STATUS) );
    return wk->pMatch->myMatchStatus.vchat;
}

//------------------------------------------------------------------
/**
 * $brief   VCHAT�t���O�̐؂�ւ�
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static BOOL _myVChatStatusToggleOrg(WIFIP2PMATCH_WORK *wk)
{
    wk->pMatch->myMatchStatus.vchat_org = 1 - wk->pMatch->myMatchStatus.vchat_org;
    wk->pMatch->myMatchStatus.vchat = wk->pMatch->myMatchStatus.vchat_org;
    mydwc_setVChat(wk->pMatch->myMatchStatus.vchat);
    mydwc_setMyInfo( &(wk->pMatch->myMatchStatus), sizeof(_WIFI_MACH_STATUS) );
    return wk->pMatch->myMatchStatus.vchat_org;
}

//------------------------------------------------------------------
/**
 * $brief   VCHAT�t���O���I���W�i���ɂ��ǂ�
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------

static BOOL _myVChatStatusOrgSet(WIFIP2PMATCH_WORK *wk)
{
    wk->pMatch->myMatchStatus.vchat = wk->pMatch->myMatchStatus.vchat_org;
    mydwc_setVChat(wk->pMatch->myMatchStatus.vchat);
    mydwc_setMyInfo( &(wk->pMatch->myMatchStatus), sizeof(_WIFI_MACH_STATUS) );
    return wk->pMatch->myMatchStatus.vchat_org;
}


//------------------------------------------------------------------
/**
 * $brief
 * @param   wk
 * @retval  none
 */
//------------------------------------------------------------------
static void _timeWaitIconDel(WIFIP2PMATCH_WORK *wk)
{
    if(wk->timeWaitWork){
        TimeWaitIconTaskDel(wk->timeWaitWork);  // �^�C�}�[�~��
        //TimeWaitIconDel(wk->timeWaitWork);
        //        GF_BGL_ScrClear(wk->bgl, GF_BGL_FRAME2_M);
        wk->timeWaitWork = NULL;
        if(GF_BGL_BmpWinAddCheck(&wk->MsgWin)){
            BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
            GF_BGL_BmpWinDel( &wk->MsgWin );
        }
        //      }
        //		GF_BGL_LoadScreenReq( wk->bgl, GF_BGL_FRAME2_M );
    }
}
