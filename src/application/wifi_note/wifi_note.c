//============================================================================================
/**
 * @file	wifi_note.c
 * @bfief	WIFI�F�B�蒠�ݒ���
 * @author	k.ohno
 * @date	06.04.05
 */
//============================================================================================
#define DEBUGPLAY_ONE	( 0 )



#include "common.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/pm_str.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_wifi_note.h"
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
#include "application/wifi_note.h"
#include "savedata/config.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "msgdata/msg_opening_name.h"
//#include "field/fld_bmp.h"

#include "wifi/dwc_rap.h"
#include "wifi/dwc_rapfriend.h"
#include "wifi_note_local.h"
#include "system/brightness.h"

#include "poketool/poke_tool.h"
#include "src/field/comm_union_beacon.h"
#include "field/union_beacon_tool.h"

#include "communication/communication.h"


//#include "msgdata/msg.naix"
#include "msgdata/msg_ev_win.h"


#include "wifinote.naix"			// �O���t�B�b�N�A�[�J�C�u��`
#include "../record/record.naix"			// �O���t�B�b�N�A�[�J�C�u��`

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



#define MAIN_LCD (1)
#define SUB_LCD (0)

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

typedef struct{  // �X�N���[���pRECT�\����
    u8 lt_x;
    u8 lt_y;
    u8 rb_x;
    u8 rb_y;
} _SCR_RECT;


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
//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

/*** �֐��v���g�^�C�v ***/
static void VBlankFunc( void * work );
static void VramBankSet(void);
static void BgInit( GF_BGL_INI * ini );
static void InitWork( WIFINOTE_WORK *wk );
static void FreeWork( WIFINOTE_WORK *wk );
static void BgExit( GF_BGL_INI * ini );
static void BgGraphicSet( WIFINOTE_WORK * wk );
static void char_pltt_manager_init(void);
static void InitCellActor(WIFINOTE_WORK *wk);
static void SetCellActor(WIFINOTE_WORK *wk);
static void BmpWinInit(WIFINOTE_WORK *wk, PROC* proc);
static void MainMenuMsgInit(WIFINOTE_WORK *wk);
static void _dispVisibleControl(int flg);
static void WifiNoteMessagePrintAll( WIFINOTE_WORK *wk, int msgno );


static void BmpWinDelete( WIFINOTE_WORK *wk );
static void SetCursor_Pos( CLACT_WORK_PTR act, int x, int y );
static void WifiNoteMessagePrint( WIFINOTE_WORK *wk, int msgno );
static int  EndMessageWait( int msg_index );
static void EndMessageWindowOff( WIFINOTE_WORK *wk );
static void CenteringPrint(GF_BGL_BMPWIN *win, STRBUF *strbuf, int wait, int width, GF_PRINTCOLOR col);
static void SequenceChange_MesWait( WIFINOTE_WORK *wk, int next );
static void mainMenuCursorDisp(WIFINOTE_WORK *wk);
static void _userCodeInRegister(WIFINOTE_WORK *wk,u64 code);


// FuncTable����V�[�P���X�J�ڂŌĂ΂��֐�
static int WifiNote_MainInit( WIFINOTE_WORK *wk, int seq );
static int WifiNote_MainNormal( WIFINOTE_WORK *wk, int seq );
static int WifiNote_FriendListInit( WIFINOTE_WORK *wk, int seq );
static int WifiNote_FriendList( WIFINOTE_WORK *wk, int seq );
static int WifiNote_FriendListPersonalMenu( WIFINOTE_WORK *wk, int seq );
static int WifiNote_FriendListPersonalMenuWait( WIFINOTE_WORK *wk, int seq );
static int WifiNote_MainReturn( WIFINOTE_WORK *wk, int seq );

static int InputFriendCodeInit( WIFINOTE_WORK* wk, int seq );
static int InputFriendCodeInitWait( WIFINOTE_WORK* wk, int seq );
static int InputFriendCodeLoop( WIFINOTE_WORK* wk, int seq );
static int InputFriendCodeLoopNext( WIFINOTE_WORK* wk, int seq );
static int InputFriendCodeLoop2( WIFINOTE_WORK* wk, int seq );
static int InputFriendCodeEndWait( WIFINOTE_WORK* wk, int seq );
static int InputFriendCodeYesNo( WIFINOTE_WORK* wk, int seq );
static int InputFriendCodeYesNoWait( WIFINOTE_WORK* wk, int seq );
static int InputFriendCodeDiffer( WIFINOTE_WORK* wk, int seq );
static int InputFriendCodeDifferWait( WIFINOTE_WORK* wk, int seq );
static int WifiNote_EndWait( WIFINOTE_WORK *wk, int seq );
static int _dispMyCodeInit( WIFINOTE_WORK* wk, int seq );
static int _dispMyCodeWait( WIFINOTE_WORK* wk, int seq );
static int _infoFriendDataInit( WIFINOTE_WORK* wk, int seq );
static int _infoFriendDataDisp( WIFINOTE_WORK* wk, int seq );
static int _infoFriendDataEnd( WIFINOTE_WORK* wk, int seq );
static int _renameInit( WIFINOTE_WORK* wk, int seq );
static int _renameOpenWindow( WIFINOTE_WORK* wk, int seq );
static int _renameWait( WIFINOTE_WORK* wk, int seq );
static int _renameEntry( WIFINOTE_WORK* wk, int seq );
static int _deleteInit( WIFINOTE_WORK* wk, int seq );
static int _deleteYesNo( WIFINOTE_WORK* wk, int seq );
static int _deleteCheck( WIFINOTE_WORK* wk, int seq );
static int _friendCodeDispInit(WIFINOTE_WORK *wk, int seq);

static int _createFriendKeyToken(SAVEDATA* pSaveData, int no, u64 friendCode);


// ���R�[�h�R�[�i�[���C���V�[�P���X�p�֐��z���`
static int (*FuncTable[])(WIFINOTE_WORK *wk, int seq)={
    WifiNote_MainInit,				// 	WIFINOTE_MODE_INIT  = 0, 
	WifiNote_MainNormal,              // 	WIFINOTE_MODE,
    WifiNote_FriendListInit,          //    WIFINOTE_MODE_FRIENDLIST_INIT,
    WifiNote_FriendList,        //WIFINOTE_MODE_FRIENDLIST
    WifiNote_FriendListPersonalMenu,        //WIFINOTE_MODE_PERSONAL_MENU
    WifiNote_FriendListPersonalMenuWait,        //WIFINOTE_MODE_PERSONAL_MENU_WAIT
    WifiNote_MainReturn,            //WIFINOTE_MODE_MAIN_MENU
    InputFriendCodeInit,      //WIFINOTE_MODE_CODEINPUT_INIT,
    InputFriendCodeInitWait,  //WIFINOTE_MODE_CODEINPUT_INIT_WAIT,
    InputFriendCodeLoop,      //WIFINOTE_MODE_CODEINPUT_LOOP,
    InputFriendCodeLoopNext,      //WIFINOTE_MODE_CODEINPUT_LOOPNEXT,
    InputFriendCodeLoop2,       //WIFINOTE_MODE_CODEINPUT_LOOP2,
    InputFriendCodeEndWait,   //WIFINOTE_MODE_CODEINPUT_END_WAIT,
    InputFriendCodeYesNo,  // WIFINOTE_MODE_CODEINPUT_YESNO
    InputFriendCodeYesNoWait,  // WIFINOTE_MODE_CODEINPUT_YESNO_WAIT
    InputFriendCodeDiffer, //WIFINOTE_MODE_FRIENDCODE_DIFFER
    InputFriendCodeDifferWait, //WIFINOTE_MODE_FRIENDCODE_DIFFER_WAIT
    WifiNote_EndWait,			//  WIFINOTE_MODE_END_WAIT,
    _dispMyCodeInit,      // WIFINOTE_MODE_MYCODE_DISP_INIT,
    _dispMyCodeWait,      // WIFINOTE_MODE_MYCODE_DISP,
    _infoFriendDataInit,    //WIFINOTE_MODE_INFO_INIT
    _infoFriendDataDisp, //WIFINOTE_MODE_INFO_DISP
    _infoFriendDataEnd,  //WIFINOTE_MODE_INFO_END
    _renameInit,         //WIFINOTE_MODE_RENAME_INIT
    _renameOpenWindow,    //WIFINOTE_MODE_RENAME_OPEN_WINDOW
    _renameWait,         //WIFINOTE_MODE_RENAME_WAIT
    _renameEntry,        //WIFINOTE_MODE_RENAME_ENTRY
    _deleteInit,       //WIFINOTE_MODE_DELETE_INIT
    _deleteYesNo,     //WIFINOTE_MODE_DELETE_YESNO
    _deleteCheck,     //WIFINOTE_MODE_DELETE_CHECK
    _friendCodeDispInit, //WIFINOTE_MODE_CODE_INIT
};



//============================================================================================
//	�v���Z�X�֐�
//============================================================================================

static void _cellActInit(WIFINOTE_WORK * wk)
{
    char_pltt_manager_init();
    InitCellActor(wk);
    SetCellActor(wk);
	wk->ObjPaletteTable = UnionView_PalleteTableAlloc( HEAPID_WIFINOTE );
}

static void _graphicInit(WIFINOTE_WORK * wk)
{
    sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
    sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

    GF_Disp_GX_VisibleControlInit();
    GF_Disp_GXS_VisibleControlInit();
    GX_SetVisiblePlane( 0 );
    GXS_SetVisiblePlane( 0 );
    sys_KeyRepeatSpeedSet( 4, 8 );

    wk->bgl = GF_BGL_BglIniAlloc( HEAPID_WIFINOTE );

    VramBankSet();
    BgInit( wk->bgl );
    BgGraphicSet( wk );
    sys_VBlankFuncChange( VBlankFunc, wk );	
    _cellActInit( wk );

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
PROC_RESULT WifiNoteProc_Init( PROC * proc, int * seq )
{
	WIFINOTE_WORK * wk;

	switch(*seq){
	case 0:
		WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );
        
		_dispVisibleControl(VISIBLE_OFF);
		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_WIFINOTE, 0x40000 );
		wk = PROC_AllocWork( proc, sizeof(WIFINOTE_WORK), HEAPID_WIFINOTE );
		MI_CpuFill8( wk, 0, sizeof(WIFINOTE_WORK) );
        wk->pSaveData = PROC_GetParentWork(proc);
		
		// ���[�N������
		InitWork( wk );
///     WIPE_ResetBrightness( WIPE_DISP_MAIN );	<<20060721 del
///     WIPE_ResetBrightness( WIPE_DISP_SUB );	<<20060721 del
		// ���C�v�t�F�[�h�J�n
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEIN, WIPE_TYPE_HOLEIN, WIPE_FADE_BLACK, 
				COMM_BRIGHTNESS_SYNC, 1, HEAPID_WIFINOTE);
        _graphicInit(wk);
        // BMPWIN�o�^�E�`��
        MainMenuMsgInit(wk);
        mainMenuCursorDisp(wk);


		// �T�E���h�f�[�^���[�h(���O����)(BGM���p��)
//		Snd_DataSetByScene( SND_SCENE_SUB_NAMEIN, 0, 0 );

		// ��ʏo�͂��㉺����ւ���
//		GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);

        _dispVisibleControl(VISIBLE_ON);

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

// �Ƃ������R�[�h�o�^�̍폜���ɌĂ΂��PROC

PROC_RESULT WifiNoteEntryProc_Init( PROC * proc, int * seq )
{
	WIFINOTE_WORK * wk;

	switch(*seq){
	case 0:
		WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );
		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_WIFINOTE, 0x40000 );
		wk = PROC_AllocWork( proc, sizeof(WIFINOTE_WORK), HEAPID_WIFINOTE );
		MI_CpuFill8( wk, 0, sizeof(WIFINOTE_WORK) );
        wk->pSaveData = PROC_GetParentWork(proc);
		
		// ���[�N������
		InitWork( wk );
        _dispVisibleControl(VISIBLE_OFF);

///     WIPE_ResetBrightness( WIPE_DISP_MAIN );	<<20060721 del
///     WIPE_ResetBrightness( WIPE_DISP_SUB );	<<20060721 del
		// ���C�v�t�F�[�h�J�n
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEIN, WIPE_TYPE_HOLEIN, WIPE_FADE_BLACK, 
				COMM_BRIGHTNESS_SYNC, 1, HEAPID_WIFINOTE);
        _graphicInit(wk);
        // BMPWIN�o�^�E�`��
        MainMenuMsgInit(wk);
        mainMenuCursorDisp(wk);

        _dispVisibleControl(VISIBLE_ON);

//        wk->seq = WIFINOTE_MODE_AUTOINPUT_CHECK;

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

PROC_RESULT WifiNoteProc_Main( PROC * proc, int * seq )
{
	WIFINOTE_WORK * wk  = PROC_GetWork( proc );

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
			*seq = (*FuncTable[wk->seq])( wk, *seq );
		}
		break;

	case SEQ_OUT:
		if( WIPE_SYS_EndCheck() ){
            _dispVisibleControl(VISIBLE_OFF);
			return PROC_RES_FINISH;
		}
		break;
	}
    if(wk->clactSet){
        CLACT_Draw( wk->clactSet );									// �Z���A�N�^�[�풓�֐�
    }
	return PROC_RES_CONTINUE;
}

static void _cellActFree(WIFINOTE_WORK* wk)
{
    int i;
    // �L�����]���}�l�[�W���[�j��
	CLACT_U_CharManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES]);
	CLACT_U_CharManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES]);

	// �p���b�g�]���}�l�[�W���[�j��
	CLACT_U_PlttManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES]);
    CLACT_U_PlttManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES]);
		
	// �L�����E�p���b�g�E�Z���E�Z���A�j���̃��\�[�X�}�l�[�W���[�j��
	for(i=0;i<CLACT_RESOURCE_NUM;i++){
		CLACT_U_ResManagerDelete(wk->resMan[i]);
	}
	// �Z���A�N�^�[�Z�b�g�j��
	CLACT_DestSet(wk->clactSet);
    wk->clactSet = NULL;

	//OAM�����_���[�j��
	REND_OAM_Delete();

	// ���\�[�X���
	DeleteCharManager();
	DeletePlttManager();

    sys_FreeMemoryEz(wk->ObjPaletteTable);
}



//--------------------------------------------------------------------------------------------
/**
 * �O���t�B�b�N�ɂ�����镔���̏I������
 * @param	wk	WIFINOTE_WORK
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void _graphicEnd(WIFINOTE_WORK* wk)
{
	int i;

    sys_VBlankFuncChange( NULL, NULL );	// VBlankReset

    _cellActFree( wk );

	// BMP�E�B���h�E�J��
	BmpWinDelete( wk );

	// BGL�폜
	BgExit( wk->bgl );


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
PROC_RESULT WifiNoteProc_End( PROC * proc, int * seq )
{
	WIFINOTE_WORK  *wk    = PROC_GetWork( proc );

    _graphicEnd(wk);

	// ���[�N���
	FreeWork( wk );

	PROC_FreeWork( proc );				// PROC���[�N�J��

	sys_DeleteHeap( HEAPID_WIFINOTE );

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
    WIFINOTE_WORK  *wk = work;
    
    if( wk->sprite ){
        SoftSpriteTextureTrans(wk->spriteManager);
    }

    // BG��������
    GF_BGL_VBlankFunc(wk->bgl);
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


	static const GF_BGL_DISPVRAM SetBankData = {
		GX_VRAM_BG_128_B,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_0_A,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_01_FG			// �e�N�X�`���p���b�g�X���b�g
	};


	GF_Disp_SetBank( &SetBankData );

/*
    GF_BGL_DISPVRAM tbl = {
		GX_VRAM_BG_128_A,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g

		GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g

		GX_VRAM_OBJ_128_B,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g

		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g

		GX_VRAM_TEX_NONE,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_NONE			// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &tbl );
*/
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
		GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_WIFINOTE);
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
		GF_BGL_ClearCharSet( GF_BGL_FRAME1_M, 32, 0, HEAPID_WIFINOTE);
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
		GF_BGL_ClearCharSet( GF_BGL_FRAME2_M, 32, 0, HEAPID_WIFINOTE);
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
		GF_BGL_ClearCharSet( GF_BGL_FRAME3_M, 32, 0, HEAPID_WIFINOTE);
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
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_WIFINOTE );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_WIFINOTE );

    GF_BGL_PrioritySet(GF_BGL_FRAME0_M , 3);  //�͂�����
    GF_BGL_PrioritySet(GF_BGL_FRAME1_M , 2);   // 
    GF_BGL_PrioritySet(GF_BGL_FRAME3_M , 1);  // ���b�Z�[�W
    GF_BGL_PrioritySet(GF_BGL_FRAME2_M , 0);   // 
    G2_BlendNone();
    G2S_BlendNone();
}

#define TALK_MESSAGE_BUF_NUM	( 90*2 )
#define TITLE_MESSAGE_BUF_NUM	( 20*2 )

//------------------------------------------------------------------
/**
 * ���G�������[�N������
 *
 * @param   wk		WIFINOTE_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork( WIFINOTE_WORK *wk )
{
	int i;
    int flag;
    STRBUF* pBuff;
    WIFI_LIST* pList;

    // �f�o�b�O
    // ������}�l�[�W���[����
    wk->WordSet    = WORDSET_Create( HEAPID_WIFINOTE );
    wk->MsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wifi_note_dat, HEAPID_WIFINOTE );

	for(i=0;i<WIFINOTE_MEMBER_MAX;i++){
		wk->TrainerName[i] = STRBUF_Create( (PERSON_NAME_SIZE+EOM_SIZE)*GLOBAL_MSGLEN, HEAPID_WIFINOTE );
	}
    wk->pTempTrainerName = STRBUF_Create( (PERSON_NAME_SIZE+EOM_SIZE)*GLOBAL_MSGLEN, HEAPID_WIFINOTE );
    wk->pTempFriendCode = STRBUF_Create( (FRIENDCODE_MAXLEN+EOM_SIZE)*GLOBAL_MSGLEN, HEAPID_WIFINOTE );
    wk->TalkString =  STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WIFINOTE );
    
	// ������o�b�t�@�쐬
    for(i = 0;i < 4;i++){
        wk->MenuString[i]  = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WIFINOTE );
    }
    wk->pExpStrBuf = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_WIFINOTE );
	wk->TitleString = STRBUF_Create( TITLE_MESSAGE_BUF_NUM, HEAPID_WIFINOTE );

	wk->seq = WIFINOTE_MODE_INIT;
	
    //	MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_01, wk->TitleString );

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
static void FreeWork( WIFINOTE_WORK *wk )
{
	int i;

	// ���b�Z�[�W�}�l�[�W���[�E���[�h�Z�b�g�}�l�[�W���[���
	MSGMAN_Delete( wk->MsgManager );
	WORDSET_Delete( wk->WordSet );

	for(i=0;i<WIFINOTE_MEMBER_MAX;i++){
		STRBUF_Delete( wk->TrainerName[i] );
	}
    STRBUF_Delete(wk->pExpStrBuf);
	STRBUF_Delete( wk->TalkString );
	STRBUF_Delete( wk->TitleString ); 
    for(i = 0;i < 4;i++){
        STRBUF_Delete(wk->MenuString[i]);
    }
    STRBUF_Delete(wk->pTempTrainerName);
    STRBUF_Delete(wk->pTempFriendCode);
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

// ���C�����b�Z�[�W�L����
#define _NUKI_FONT_PALNO  (13)
#define	_COL_N_BLACK	( GF_PRINTCOLOR_MAKE( 1, 2, 0 ) )		// �t�H���g�J���[�F��
#define	_COL_N_WHITE	( GF_PRINTCOLOR_MAKE( 15, 14, 0 ) )		// �t�H���g�J���[�F��
#define	_COL_N_RED	    ( GF_PRINTCOLOR_MAKE( 3, 4, 0 ) )		// �t�H���g�J���[�F��
#define	_COL_N_BLUE	    ( GF_PRINTCOLOR_MAKE( 5, 6, 0 ) )		// �t�H���g�J���[�F��



static void BgGraphicSet( WIFINOTE_WORK * wk )
{
	GF_BGL_INI *bgl = wk->bgl;

    // �㉺��ʂa�f�p���b�g�]��
	ArcUtil_PalSet(    ARC_WIFINOTE_GRA, NARC_wifinote_techo_NCLR, PALTYPE_MAIN_BG, 0, 0,  HEAPID_WIFINOTE);
	ArcUtil_PalSet(    ARC_WIFINOTE_GRA, NARC_wifinote_techo_NCLR, PALTYPE_SUB_BG,  0, 0,  HEAPID_WIFINOTE);
	
	// ��b�t�H���g�p���b�g�]��
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, _NUKI_FONT_PALNO*0x20, HEAPID_WIFINOTE );
	//TalkFontPaletteLoad( PALTYPE_SUB_BG,  13*0x20, HEAPID_WIFINOTE );
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, COMM_MESFONT_PAL*0x20, HEAPID_WIFINOTE );

    {
        u16 pal = 0x52d8;
        
        GX_LoadBGPltt(&pal,_NUKI_FONT_PALNO*0x20 + 2*14, 2);
    }

	ArcUtil_BgCharSet( ARC_WIFINOTE_GRA, NARC_wifinote_techo_NCGR, bgl,
                       GF_BGL_FRAME0_M, 0, 0, 0, HEAPID_WIFINOTE);

	ArcUtil_ScrnSet(   ARC_WIFINOTE_GRA, NARC_wifinote_techo_main_NSCR, bgl,
                       GF_BGL_FRAME0_M, 0, 0, 0, HEAPID_WIFINOTE);
    ArcUtil_ScrnSet(   ARC_WIFINOTE_GRA, NARC_wifinote_techo_01_NSCR, wk->bgl,
                      GF_BGL_FRAME1_M, 0, 0, 0, HEAPID_WIFINOTE);



	// �T�u���BG0�L�����]��  0x7fff 0x5d28
	ArcUtil_BgCharSet( ARC_WIFINOTE_GRA, NARC_wifinote_techo_sub_NCGR, bgl, GF_BGL_FRAME0_S, 0, 0, 0, HEAPID_WIFINOTE);

	// �T�u���BG0�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_WIFINOTE_GRA, NARC_wifinote_techo_sub_NSCR, bgl, GF_BGL_FRAME0_S, 0, 0, 0, HEAPID_WIFINOTE);

    {
        int type = CONFIG_GetWindowType(SaveData_GetConfig(wk->pSaveData));
        TalkWinGraphicSet(
            bgl, GF_BGL_FRAME2_M, COMM_TALK_WIN_CGX_NUM,
            COMM_MESFRAME_PAL,  type, HEAPID_WIFINOTE );
    }

	MenuWinGraphicSet(
        bgl, GF_BGL_FRAME2_M, MENU_WIN_CGX_NUM,
        MENU_WIN_PAL, 0, HEAPID_WIFINOTE );
}


#define COMM_MESFRAME_PAL     ( 10 )         //  ���b�Z�[�W�E�C���h�E
#define COMM_MENUFRAME_PAL    ( 11 )         //  ���j���[�E�C���h�E

//** CharManager PlttManager�p **//
#define WIFINOTE_CHAR_CONT_NUM				(20)
#define WIFINOTE_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define WIFINOTE_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define WIFINOTE_PLTT_CONT_NUM				(20)

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
			WIFINOTE_CHAR_CONT_NUM,
			WIFINOTE_CHAR_VRAMTRANS_MAIN_SIZE,
			WIFINOTE_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_WIFINOTE
		};
		InitCharManager(&cm);
	}
	// �p���b�g�}�l�[�W���[������
	InitPlttManager(WIFINOTE_PLTT_CONT_NUM, HEAPID_WIFINOTE);

	// �ǂݍ��݊J�n�ʒu��������
	CharLoadStartAll();
	PlttLoadStartAll();
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
static void InitCellActor(WIFINOTE_WORK *wk)
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
			HEAPID_WIFINOTE);
	
	
	
	// �Z���A�N�^�[������
	wk->clactSet = CLACT_U_SetEasyInit( 30, &wk->renddata, HEAPID_WIFINOTE );
	
	CLACT_U_SetSubSurfaceMatrix( &wk->renddata, 0, NAMEIN_SUB_ACTOR_DISTANCE );

	
	//���\�[�X�}�l�[�W���[������
	for(i=0;i<CLACT_RESOURCE_NUM;i++){		//���\�[�X�}�l�[�W���[�쐬
		wk->resMan[i] = CLACT_U_ResManagerInit(2, i, HEAPID_WIFINOTE);
	}


	//---------���ʗp-------------------


	//chara�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] =
        CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
                                        ARC_RECORD_GRA, NARC_record_union_chara_lz_ncgr,
                                        1, _UNION_CREATURE, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_WIFINOTE);
	wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] =
        CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
                                        ARC_WIFINOTE_GRA, NARC_wifinote_techo_obj_NCGR,
                                        0, _LIST_ARROW, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_WIFINOTE);

    //pal�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] =
        CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
                                        ARC_RECORD_GRA, NARC_record_union_chara_nclr, 0, _UNION_CREATURE, NNS_G2D_VRAM_TYPE_2DMAIN, 5, HEAPID_WIFINOTE);
	wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] =
        CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
                                        ARC_WIFINOTE_GRA, NARC_wifinote_techo_NCLR, 0, _LIST_ARROW, NNS_G2D_VRAM_TYPE_2DMAIN, 5, HEAPID_WIFINOTE);
	//cell�ǂݍ���
    wk->resObjTbl[MAIN_LCD][CLACT_U_CELL_RES] =
        CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
                                            ARC_RECORD_GRA, NARC_record_friend_note_lz_ncer, 1, _UNION_CREATURE, CLACT_U_CELL_RES,HEAPID_WIFINOTE);
    wk->resObjTbl[SUB_LCD][CLACT_U_CELL_RES] =
        CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
                                            ARC_WIFINOTE_GRA, NARC_wifinote_techo_NCER, 0, _LIST_ARROW, CLACT_U_CELL_RES,HEAPID_WIFINOTE);
    //�����֐���anim�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELLANM_RES] =
        CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
                                            ARC_RECORD_GRA, NARC_record_friend_note_lz_nanr, 1, _UNION_CREATURE, CLACT_U_CELLANM_RES,HEAPID_WIFINOTE);
	wk->resObjTbl[SUB_LCD][CLACT_U_CELLANM_RES] =
        CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
                                            ARC_WIFINOTE_GRA, NARC_wifinote_techo_NANR, 0, _LIST_ARROW, CLACT_U_CELLANM_RES,HEAPID_WIFINOTE);


	// ���\�[�X�}�l�[�W���[����]��

	// Chara�]��
	CLACT_U_CharManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] );
	CLACT_U_CharManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] );

	// �p���b�g�]��
	CLACT_U_PlttManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] );
	CLACT_U_PlttManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] );

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
 * @param   wk			WIFINOTE_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor(WIFINOTE_WORK *wk)
{
	int i;
	// �Z���A�N�^�[�w�b�_�쐬
	CLACT_U_MakeHeader(&wk->clActHeader_m, 0, 0, 0, 0,
                       CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 0,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);

    
	CLACT_U_MakeHeader(&wk->clActHeader_s, 1, 1, 1, 1,
                       CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 0,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);
	{
		//�o�^���i�[
		CLACT_ADD add;

		add.ClActSet	= wk->clactSet;
		add.ClActHeader	= &wk->clActHeader_s;

		add.mat.z		= 0;
		add.sca.x		= FX32_ONE;
		add.sca.y		= FX32_ONE;
		add.sca.z		= FX32_ONE;
		add.rot			= 0;
		add.pri			= 1;
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		add.heap		= HEAPID_WIFINOTE;

		for(i=0;i<_OAM_NUM;i++){
			add.mat.x = FX32_ONE *  (22 + (120 * (i / 4) ));
			add.mat.y = FX32_ONE * ( 43 + 32 * (i % 4) );
            if(i == _LEFT_ARROW){
                add.mat.x = FX32_ONE * 6;
                add.mat.y = FX32_ONE * 98;
                add.ClActHeader	= &wk->clActHeader_m;
            }
            else if(i == _RIGHT_ARROW){
                add.mat.x = FX32_ONE * 249;
                add.mat.y = FX32_ONE * 98;
                add.ClActHeader	= &wk->clActHeader_m;
            }
            wk->MainActWork[i] = CLACT_Add(&add);
            if((i == _LEFT_ARROW) || (i == _RIGHT_ARROW)){
                CLACT_SetAnmFlag(wk->MainActWork[i], 1);
            }
			CLACT_BGPriorityChg(wk->MainActWork[i], 2);
			CLACT_SetDrawFlag( wk->MainActWork[i], 0 );
		}
		
	}	
	GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_ON );	//���C�����OBJ�ʂn�m
}

// ���������{�[�hBMP�i����ʁj
#define OEKAKI_BOARD_POSX	 ( 1 )
#define OEKAKI_BOARD_POSY	 ( 2 )
#define OEKAKI_BOARD_W	 ( 30 )
#define OEKAKI_BOARD_H	 ( 15 )


// ���O�\��BMP�i���ʁj
#define WIFINOTE_NAME_BMP_W	 ( 16 )
#define WIFINOTE_NAME_BMP_H	 (  2 )
#define WIFINOTE_NAME_BMP_SIZE (WIFINOTE_NAME_BMP_W * WIFINOTE_NAME_BMP_H)


// �u��߂�v������BMP�i����ʁj
#define OEKAKI_END_BMP_X	( 26 )
#define OEKAKI_END_BMP_Y	( 20 )
#define OEKAKI_END_BMP_W	( 6  )
#define OEKAKI_END_BMP_H	( 2  )


// ��b�E�C���h�E�\���ʒu��`
#define WIFINOTE_TALK_X		(  2 )
#define WIFINOTE_TALK_Y		(  19 )

#define WIFINOTE_TITLE_X		(   3  )
#define WIFINOTE_TITLE_Y		(   1  )
#define WIFINOTE_TITLE_W		(  26  )
#define WIFINOTE_TITLE_H		(   2  )


#define WIFINOTE_MSG_WIN_OFFSET 		(1 + TALK_WIN_CGX_SIZ     + MENU_WIN_CGX_SIZ)
#define WIFINOTE_TITLE_WIN_OFFSET		( WIFINOTE_MSG_WIN_OFFSET   + FLD_MSG_WIN_SX*FLD_MSG_WIN_SY )
#define WIFINOTE_NAME_WIN_OFFSET		( WIFINOTE_TITLE_WIN_OFFSET + WIFINOTE_TITLE_W*WIFINOTE_TITLE_H )
#define WIFINOTE_YESNO_WIN_OFFSET		( WIFINOTE_NAME_WIN_OFFSET  + WIFINOTE_NAME_BMP_SIZE*5 )

//------------------------------------------------------------------
/**
 * BMPWIN�����i�����p�l���Ƀt�H���g�`��j
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------

static void MainMenuMsgInit(WIFINOTE_WORK *wk)
{
    int i,col;

    // ---------- ���C����� ------------------
    if(GF_BGL_BmpWinAddCheck(&wk->TitleWin)){
        GF_BGL_BmpWinDel(&wk->TitleWin);
    }
    GF_BGL_BmpWinAdd(wk->bgl, &wk->TitleWin, GF_BGL_FRAME3_M, 1, 0, 13, 3, _NUKI_FONT_PALNO,  MENU_WIN_CGX_NUM - 13*4*2 );
	GF_BGL_BmpWinDataFill( &wk->TitleWin, 0x8000 );
	MSGMAN_GetString(wk->MsgManager, msg_wifi_note_01, wk->TitleString );
    GF_STR_PrintColor(&wk->TitleWin, FONT_TALK, wk->TitleString, 0, 4, MSG_NO_PUT, _COL_N_WHITE, NULL);

    GF_BGL_BmpWinOnVReq(&wk->TitleWin);
    
    // ���j���[����
    for(i = 0;i < 4; i++){
        if(GF_BGL_BmpWinAddCheck(&wk->MenuWin[i])){
            GF_BGL_BmpWinDel(&wk->MenuWin[i]);
        }
        GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[i], GF_BGL_FRAME3_M,
                         7, 5+i*5, 21, 2, _NUKI_FONT_PALNO,  MENU_WIN_CGX_NUM - 13*4*2 - (20*3*(i+1)) );
        GF_BGL_BmpWinDataFill( &wk->MenuWin[i], 0x8000 );
        if(i == 2){
            WORDSET_RegisterPlayerName( wk->WordSet, 0, SaveData_GetMyStatus(wk->pSaveData));
            MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_02+i, wk->pExpStrBuf );
            WORDSET_ExpandStr( wk->WordSet, wk->MenuString[i], wk->pExpStrBuf );
        }
        else{
            MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_02+i, wk->MenuString[i] );
        }
        CenteringPrint(&wk->MenuWin[i], wk->MenuString[i], MSG_NO_PUT, 18*8, _COL_N_BLACK);
        GF_BGL_BmpWinOnVReq(&wk->MenuWin[i]);
    }
}

//void GF_BGL_BmpWinSet_Pal( GF_BGL_BMPWIN * win, u8 palnum )

//------------------------------------------------------------------
/**
 * MainMenu�ł̃J�[�\������
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------

static void mainMenuCursorDisp(WIFINOTE_WORK *wk)
{
    _SCR_RECT pos[] = { 2, 4, 28, 4  };
    u16* pScrAddr = GF_BGL_ScreenAdrsGet( wk->bgl, GF_BGL_FRAME1_M );
    int no = wk->mainCur;
    int i,col;
    int scr,y,x;

    for(i = 0;i < 4; i++){
        if(no == i){
            col = 0x1000;
        }
        else{
            col = 0;
        }
        for(y = pos[0].lt_y; y < pos[0].rb_y+pos[0].lt_y; y++){
            scr = pos[0].lt_x + (y * 32);
            for(x = 0; x < pos[0].rb_x; x++){
                pScrAddr[scr] = (pScrAddr[scr] & 0x0fff) + col;
                scr++;
            }
        }
        pos[0].lt_y += 5;
    }
    GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME1_M);  // �X�N���[���ɍX�V
}


//------------------------------------------------------------------
/**
 * $brief   �Z���^�����O���ăv�����g
 *
 * @param   win		GF_BGL_BMPWIN
 * @param   strbuf	
 *
 * @retval  none
 */
//------------------------------------------------------------------
static void CenteringPrint(GF_BGL_BMPWIN *win, STRBUF *strbuf, int wait, int width,GF_PRINTCOLOR col)
{
	int length = FontProc_GetPrintStrWidth( FONT_SYSTEM, strbuf, 0 );
	int x      = (width - length)/2;

    if(col == 0){
        GF_STR_PrintSimple( win, FONT_SYSTEM, strbuf, x, 1, wait, NULL);
    }
    else{
        GF_STR_PrintColor( win, FONT_SYSTEM, strbuf, x, 1, wait, col, NULL);
    }
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
static void BmpWinDelete( WIFINOTE_WORK *wk )
{
	int i;
	
	for(i=0;i<WIFINOTE_DISP_MEMBER_MAX;i++){
        if(GF_BGL_BmpWinAddCheck(&wk->TrainerNameWin[i])){
            GF_BGL_BmpWinDel( &wk->TrainerNameWin[i] );
        }
	}
	for(i=0;i<4;i++){
        if(GF_BGL_BmpWinAddCheck(&wk->MenuWin[i])){
            GF_BGL_BmpWinDel( &wk->MenuWin[i] );
        }
	}
    
    if(GF_BGL_BmpWinAddCheck(&wk->MsgWin)){
        GF_BGL_BmpWinDel(&wk->MsgWin);
    }
    if(GF_BGL_BmpWinAddCheck(&wk->TitleWin)){
        GF_BGL_BmpWinDel( &wk->TitleWin );
    }
    if(GF_BGL_BmpWinAddCheck(&wk->ListWin)){
        GF_BGL_BmpWinDel(&wk->ListWin);
    }
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


#define PAL_BUTTON_X	(  0  )
#define PAL_BUTTON_Y	( 150 )
#define PAL_BUTTON_W	( 3*8 )
#define PAL_BUTTON_H	( 5*8 )
#define PAL_BUTTON_RECT ( 3*8 -1 )
#define PAL_BUTTON_RECT ( 3*8 -1 )
#define END_BUTTON_RECT ( 8*8 -1 )

#define PAL_BUTTON0_X	( PAL_BUTTON_X+PAL_BUTTON_W*0 )
#define PAL_BUTTON1_X	( PAL_BUTTON_X+PAL_BUTTON_W*1 )
#define PAL_BUTTON2_X	( PAL_BUTTON_X+PAL_BUTTON_W*2 )
#define PAL_BUTTON3_X	( PAL_BUTTON_X+PAL_BUTTON_W*3 )
#define PAL_BUTTON4_X	( PAL_BUTTON_X+PAL_BUTTON_W*4 )
#define PAL_BUTTON5_X	( PAL_BUTTON_X+PAL_BUTTON_W*5 )
#define PAL_BUTTON6_X	( PAL_BUTTON_X+PAL_BUTTON_W*6 )
#define PAL_BUTTON7_X	( PAL_BUTTON_X+PAL_BUTTON_W*7 )
#define END_BUTTON_X	( PAL_BUTTON_X+PAL_BUTTON_W*8 )


static const RECT_HIT_TBL sub_button_hittbl[]={
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON0_X,PAL_BUTTON0_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON1_X,PAL_BUTTON1_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON2_X,PAL_BUTTON2_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON3_X,PAL_BUTTON3_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON4_X,PAL_BUTTON4_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON5_X,PAL_BUTTON5_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON6_X,PAL_BUTTON6_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON7_X,PAL_BUTTON7_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,END_BUTTON_X,END_BUTTON_X+END_BUTTON_RECT},
{RECT_HIT_END,0,0,0},		// �I���f�[�^
};

#define DRAW_AREA_X	(  8  )
#define DRAW_AREA_Y	( 16  )
#define DRAW_AREA_W	( OEKAKI_BOARD_W*8 )
#define DRAW_AREA_H	( OEKAKI_BOARD_W*8)

static const RECT_HIT_TBL sub_canvas_touchtbl[]={
	{DRAW_AREA_Y,DRAW_AREA_Y+DRAW_AREA_H,DRAW_AREA_X,DRAW_AREA_X+DRAW_AREA_W},
{RECT_HIT_END,0,0,0},		// �I���f�[�^
};


// ����ʗp�͂��E�����������̃^�b�`����e�[�u��
static const RECT_HIT_TBL end_button_touchtbl[]={
	{	YESNO_WINDOW_Y1*8, (YESNO_WINDOW_Y1+YESNO_CHARA_H)*8, YESNO_WINDOW_X*8, (YESNO_WINDOW_X+YESNO_CHARA_W)*8,},
	{	YESNO_WINDOW_Y2*8, YESNO_WINDOW_Y2*8+YESNO_CHARA_H*8, YESNO_WINDOW_X*8, (YESNO_WINDOW_X+YESNO_CHARA_W)*8,},
	{RECT_HIT_END,0,0,0},		// �I���f�[�^
};




//------------------------------------------------------------------
/**
 * $brief   �J�n���̃��b�Z�[�W
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static int WifiNote_MainInit( WIFINOTE_WORK *wk, int seq )
{
	wk->seq = WIFINOTE_MODE;
    

	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   ���G�����{�[�h�ʏ폈��
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int WifiNote_MainNormal( WIFINOTE_WORK *wk, int seq )
{
    if( !WIPE_SYS_EndCheck() ){
        return seq;
    }


    if(sys.trg&PAD_BUTTON_DECIDE){

        Snd_SePlay(WIFINOTE_DECIDE_SE);

        switch(wk->mainCur){
          case _MENU_LIST:
            wk->mainCur = 0;
            wk->subCur = 0;
            wk->horizontalCur = 0;
            wk->verticalCur = 0;
            wk->seq = WIFINOTE_MODE_FRIENDLIST_INIT;
            break;
          case _MENU_INPUT:
            wk->seq = WIFINOTE_MODE_CODEINPUT_INIT;
            break;
          case _MENU_MYCODE:
            wk->seq = WIFINOTE_MODE_MYCODE_DISP_INIT;
            break;
          case _MENU_EXIT:
            wk->seq = WIFINOTE_MODE_END_WAIT;
            break;
        }
	}
    else if(sys.trg & PAD_BUTTON_CANCEL){
        Snd_SePlay(WIFINOTE_BS_SE);
        wk->seq = WIFINOTE_MODE_END_WAIT;
    }
	else if( sys.repeat & PAD_KEY_UP){
        if(wk->mainCur > 0){
            Snd_SePlay(WIFINOTE_MOVE_SE);
            wk->mainCur--;
            mainMenuCursorDisp(wk);
        }
	}
	else if( sys.repeat & PAD_KEY_DOWN){
        if(wk->mainCur < 3){
            Snd_SePlay(WIFINOTE_MOVE_SE);
            wk->mainCur++;
            mainMenuCursorDisp(wk);
        }
	}
	return seq;
}


//------------------------------------------------------------------
/**
 * �t�����h�R�[�h����
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static int InputFriendCodeInit( WIFINOTE_WORK* wk, int seq )
{
    WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);
    BOOL bEmpty = FALSE;
    int i;
    
    for(i = 0; i < WIFILIST_FRIEND_MAX;i++){
        if( !WifiList_IsFriendData( pList, i ) ){  // 
            bEmpty = TRUE;
        }
    }

    if(bEmpty){
        WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEOUT, WIPE_TYPE_HOLEOUT, WIPE_FADE_BLACK, 
                        COMM_BRIGHTNESS_SYNC, 1, HEAPID_WIFINOTE);
        wk->seq = WIFINOTE_MODE_CODEINPUT_INIT_WAIT; //WIFINOTE_MODE_CODEINPUT_END_WAIT;
    }
    else{
        WifiNoteMessagePrint(wk,msg_wifi_note_30);
        wk->seq = WIFINOTE_MODE_FRIENDCODE_DIFFER;  // 
    }
    return seq;
}


//------------------------------------------------------------------
/**
 * �t�����h�R�[�h����
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------

static int InputFriendCodeInitWait( WIFINOTE_WORK* wk, int seq )
{
    if( WIPE_SYS_EndCheck() ){
        _dispVisibleControl(VISIBLE_OFF);
        _graphicEnd(wk);
        wk->nameinParam = NameIn_ParamAllocMake( HEAPID_WIFINOTE, NAMEIN_FRIENDNAME, 0, 
        											NAMEIN_PERSON_LENGTH, SaveData_GetConfig(wk->pSaveData) );
        wk->subProc = PROC_Create( &NameInProcData, wk->nameinParam, HEAPID_WIFINOTE );
        wk->seq = WIFINOTE_MODE_CODEINPUT_LOOP;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * �t�����h�R�[�h����
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static int InputFriendCodeLoop( WIFINOTE_WORK* wk, int seq )
{
    if( ProcMain( wk->subProc ) ) {
        PROC_Delete( wk->subProc );
        if(wk->nameinParam->cancel==0){            // ���O�ۑ�
            STRBUF_Copy(wk->pTempTrainerName, wk->nameinParam->strbuf);
            wk->seq = WIFINOTE_MODE_CODEINPUT_LOOPNEXT;
        }
        else{
			WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
			WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );
///			WIPE_ResetBrightness( WIPE_DISP_MAIN );	<<20060721 del
///			WIPE_ResetBrightness( WIPE_DISP_SUB );	<<20060721 del
            _dispVisibleControl(VISIBLE_OFF);
            WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEIN, WIPE_TYPE_HOLEIN, WIPE_FADE_BLACK, 
                            COMM_BRIGHTNESS_SYNC, 1, HEAPID_WIFINOTE);
            _graphicInit(wk);
            // BMPWIN�o�^�E�`��
            MainMenuMsgInit(wk);
            mainMenuCursorDisp(wk);
            _dispVisibleControl(VISIBLE_ON);
            wk->seq = WIFINOTE_MODE_MAIN_MENU;
        }
        NameIn_ParamDelete( wk->nameinParam );
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * �t�����h�R�[�h����
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static int InputFriendCodeLoopNext( WIFINOTE_WORK* wk, int seq )
{
    wk->nameinParam = NameIn_ParamAllocMake( HEAPID_WIFINOTE, NAMEIN_FRIENDCODE, 0, 
    											FRIENDCODE_MAXLEN, SaveData_GetConfig(wk->pSaveData) );
    wk->subProc = PROC_Create( &NameInProcData, wk->nameinParam, HEAPID_WIFINOTE );
    wk->seq = WIFINOTE_MODE_CODEINPUT_LOOP2;
    return seq;
}

//------------------------------------------------------------------
/**
 * �t�����h�R�[�h����
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static int InputFriendCodeLoop2( WIFINOTE_WORK* wk, int seq )
{
    if( ProcMain( wk->subProc ) ) {
        PROC_Delete( wk->subProc );
        // ���O�ۑ�
        STRBUF_Copy(wk->pTempFriendCode, wk->nameinParam->strbuf);
        NameIn_ParamDelete( wk->nameinParam );
		WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );
///     WIPE_ResetBrightness( WIPE_DISP_MAIN );	<<20060721 del
///     WIPE_ResetBrightness( WIPE_DISP_SUB );	<<20060721 del
        _dispVisibleControl(VISIBLE_OFF);
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEIN, WIPE_TYPE_HOLEIN, WIPE_FADE_BLACK, 
				COMM_BRIGHTNESS_SYNC, 1, HEAPID_WIFINOTE);
        _graphicInit(wk);
        // BMPWIN�o�^�E�`��
        MainMenuMsgInit(wk);
        mainMenuCursorDisp(wk);

        _dispVisibleControl(VISIBLE_ON);
        wk->seq = WIFINOTE_MODE_CODEINPUT_END_WAIT;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * �t�����h�R�[�h���� WIFINOTE_MODE_CODEINPUT_END_WAIT
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static int InputFriendCodeEndWait( WIFINOTE_WORK* wk, int seq )
{
    MYSTATUS* pMy;
    u64 friendCode,num;
    BOOL bFlag;

    if( WIPE_SYS_EndCheck() ){
        friendCode = STRBUF_GetNumber(wk->pTempFriendCode, &bFlag);
        if(bFlag){
            pMy = MyStatus_AllocWork(HEAPID_WIFINOTE);
            MyStatus_SetMyName(pMy, STRBUF_GetStringCodePointer(wk->pTempTrainerName));
            WORDSET_RegisterPlayerName(wk->WordSet, 0, pMy);
            _userCodeInRegister(wk, friendCode);
            WifiNoteMessagePrint(wk,msg_wifi_note_26);
            sys_FreeMemoryEz(pMy);
            wk->seq = WIFINOTE_MODE_CODEINPUT_YESNO;
        }
        else{
            wk->seq = WIFINOTE_MODE_FRIENDCODE_DIFFER;
       }
	}
    return seq;
}


static const BMPWIN_DAT _yesNoBmpDat = {
    GF_BGL_FRAME2_M, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
    FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, FLD_YESNO_WIN_CGX
    };

//------------------------------------------------------------------
/**
 * �Ƃ��낭�m�F WIFINOTE_MODE_CODEINPUT_YESNO
 * @param   wk		
 * @retval  none		
 */
//------------------------------------------------------------------

static int InputFriendCodeYesNo( WIFINOTE_WORK* wk, int seq )  // WIFINOTE_MODE_CODEINPUT_YESNO
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        // �͂��������E�C���h�E���o��
        wk->pYesNoWork =
            BmpYesNoSelectInit( wk->bgl,
                                &_yesNoBmpDat,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                HEAPID_WIFINOTE );
        wk->seq = WIFINOTE_MODE_CODEINPUT_YESNO_WAIT;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * MainMenu�ł̃J�[�\������
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------

static int InputFriendCodeYesNoWait( WIFINOTE_WORK* wk, int seq )  // WIFINOTE_MODE_CODEINPUT_YESNO_WAIT
{
    int i;
    int ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_WIFINOTE);
    if(ret == BMPMENU_NULL){  // �܂��I��
        return seq;
    }else if(ret == 0){ // �͂���I�������ꍇ
        //��������
        WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);
        for(i = 0; i < WIFILIST_FRIEND_MAX;i++){
            if( !WifiList_IsFriendData( pList, i ) ){
                BOOL bFlag;
                u64 friendCode = STRBUF_GetNumber(wk->pTempFriendCode, &bFlag);
                u64 myCode = DWC_CreateFriendKey(WifiList_GetMyUserInfo(pList));
                if(friendCode == myCode){
                    bFlag = FALSE;
                }
                if(bFlag){
                    int ret = _createFriendKeyToken(wk->pSaveData ,i , friendCode);
                    if(ret == 0){
                        WifiList_SetFriendName(pList, i, wk->pTempTrainerName);
                        // �o�^�����΂���̏ꍇ����
                        WifiList_SetFriendInfo(pList, i, WIFILIST_FRIEND_SEX, PM_NEUTRAL);
                        break;
                    }
                    else if(ret == -1){
                        WifiNoteMessagePrint(wk,msg_wifi_note_27);
                        wk->seq = WIFINOTE_MODE_FRIENDCODE_DIFFER;  // �Ƃ������R�[�h�Ⴄ�\��
                        return seq;
                    }
                    else if(ret == -2){
                        WifiNoteMessagePrint(wk,msg_wifi_note_31);
                        wk->seq = WIFINOTE_MODE_FRIENDCODE_DIFFER;  // �Ƃ������R�[�h�Ⴄ�\��
                        return seq;
                    }
                }
                else{
                    WifiNoteMessagePrint(wk,msg_wifi_note_27);
                    wk->seq = WIFINOTE_MODE_FRIENDCODE_DIFFER;  // �Ƃ������R�[�h�Ⴄ�\��
                    return seq;
                }
            }
        }
        // ���s @@OO���������͎̂��O�������K�v�Ȃ̂ł����ł͂Ȃɂ����Ȃ�
    }
    else{  // ��������I�������ꍇ
    }
    EndMessageWindowOff(wk);                  // 
    wk->seq = WIFINOTE_MODE_MAIN_MENU;
    return seq;
}


static int InputFriendCodeDiffer( WIFINOTE_WORK* wk, int seq ) //WIFINOTE_MODE_FRIENDCODE_DIFFER
{
    wk->seq = WIFINOTE_MODE_FRIENDCODE_DIFFER_WAIT;
    return seq;
}

static int InputFriendCodeDifferWait( WIFINOTE_WORK* wk, int seq ) //WIFINOTE_MODE_FRIENDCODE_DIFFER_WAIT
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        if(sys.trg & PAD_BUTTON_DECIDE){
            BmpTalkWinClear(&wk->MsgWin, WINDOW_TRANS_ON );  // ��������
            GF_BGL_BmpWinOff(&wk->MsgWin);
            wk->seq = WIFINOTE_MODE_MAIN_MENU;
        }
    }
    return seq;
}


//------------------------------------------------------------------
/**
 * MainMenu�ł̃J�[�\������
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------

static void _listMenuCursorDisp(WIFINOTE_WORK *wk)
{
    _SCR_RECT pos[] = { 1, 4, 15, 4  };
    _SCR_RECT ques[] = { 2, 5, 2, 2  };
    u16* pScrAddr = GF_BGL_ScreenAdrsGet( wk->bgl, GF_BGL_FRAME1_M );
    int no = wk->mainCur % 8;
    int page = wk->mainCur / 8;
    int left = (wk->mainCur / 8) * 8;  // ��_�͔��̔{��
    int i,col;
    int scr,y,x,k;
    WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);
    u16* pCScr;
    u16 hate[] = {  0x2e,  0x2f,  0x33, 0x34 };
    u16 kara[] = {  0x08,  0x42,  0x808, 0x842};
    
    // �͂Ăȃ}�[�N
    for(i = 0 ; i < WIFINOTE_DISP_MEMBER_MAX; i++){
        int sex = WifiList_GetFriendInfo(pList, wk->index2No[i+left]-1, WIFILIST_FRIEND_SEX);
        if((wk->index2No[i+left]!=0) && (sex != PM_NEUTRAL)){
            pCScr = kara;
        }
        else{
            pCScr = hate;
        }
        k = 0;
        for(y = ques[0].lt_y; y < ques[0].rb_y + ques[0].lt_y; y++){
            scr = ques[0].lt_x + (y * 32);
            for(x = 0; x < ques[0].rb_x; x++){
                pScrAddr[scr] = pCScr[k];
                k++;
                scr++;
            }
        }
        ques[0].lt_y += 4;
        if(i == 3){
            ques[0].lt_y = 5;
            ques[0].lt_x = 17;
        }
    }

    x = 0x17;  // �y�[�W�}�[�N
    for(i = 0;i < 4;i++){
        scr = x + 32;
        if(i == page){
            col = 0x02;
        }
        else{
            col = 0x16;
        }
        pScrAddr[scr] = (pScrAddr[scr] & 0xfc00) + col;
        x += 2;
    }
    
    if(wk->subCur){  // �J�[�\���p���b�g
        no = 8;
    }
    for(i = 0;i < WIFINOTE_DISP_MEMBER_MAX+1; i++){
        if(no == i){
            col = 0x1000;
        }
        else{
            col = 0;
        }
        for(y = pos[0].lt_y; y < pos[0].rb_y+pos[0].lt_y; y++){
            scr = pos[0].lt_x + (y * 32);
            for(x = 0; x < pos[0].rb_x; x++){
                pScrAddr[scr] = (pScrAddr[scr] & 0x0fff) + col;
                scr++;
            }
        }
        pos[0].lt_y += 4;
        if(i == 3){
            pos[0].lt_y=4;
            pos[0].lt_x=16;
        }
        if(i == 7){
            pos[0].lt_y = 20;
            pos[0].lt_x = 9;
        }
    }
    GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME1_M);  // �X�N���[���ɍX�V
}

//------------------------------------------------------------------
/**
 * �g���[�i�[�A�C�R�����o��
 * @param   wk		
 * @retval  none		
 */
//------------------------------------------------------------------

static void _listMenuTrainerDisp(WIFINOTE_WORK *wk)
{
    int i;
    WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);
    int left = (wk->mainCur / 8) * 8;  // ��_�͔��̔{��

    for(i = 0 ; i < WIFINOTE_DISP_MEMBER_MAX; i++){
        CLACT_SetDrawFlag( wk->MainActWork[i], 0 );
        if(wk->index2No[i+left] != 0){
            int listNo = wk->index2No[i+left]-1;
            int id = WifiList_GetFriendInfo(pList, listNo, WIFILIST_FRIEND_UNION_GRA);
            int sex = WifiList_GetFriendInfo(pList, listNo, WIFILIST_FRIEND_SEX);
            if(sex != PM_NEUTRAL){
                int no = UnionView_GetTrainerInfo(sex, id, UNIONVIEW_ICONINDEX);
                GX_LoadOBJPltt(&wk->ObjPaletteTable[no * 16], (i+7)*16*2, 32);
                CLACT_PaletteNoChg(wk->MainActWork[i], (i+7));
                CLACT_AnmChg( wk->MainActWork[i], no );
                CLACT_SetDrawFlag( wk->MainActWork[i], 1 );
            }
/*
            if(0 != WifiList_GetFriendInfo(pList, listNo, WIFILIST_FRIEND_LASTBT_DAY)){
                int id = WifiList_GetFriendInfo(pList, listNo, WIFILIST_FRIEND_UNION_GRA);
                int sex = WifiList_GetFriendInfo(pList, listNo, WIFILIST_FRIEND_SEX);
                int no = UnionView_GetTrainerInfo(sex, id, UNIONVIEW_ICONINDEX);
                GX_LoadOBJPltt(&wk->ObjPaletteTable[no * 16], i*16*2, 32);
                CLACT_PaletteNoChg(wk->MainActWork[i], i);
                CLACT_AnmChg( wk->MainActWork[i], no );
                CLACT_SetDrawFlag( wk->MainActWork[i], 1 );
            }
   */
        }
    }
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
static void WifiNoteFriendListChange( WIFINOTE_WORK *wk)
{
    WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);
    BOOL bDisp;
    int i,sex,no;
    int left = (wk->mainCur / 8) * 8;  // ��_�͔��̔{��
    GF_PRINTCOLOR col[] = {_COL_N_BLUE,_COL_N_RED,_COL_N_BLACK}; 
    
    for(i = 0; i < WIFINOTE_DISP_MEMBER_MAX; i++){
        bDisp = FALSE;
        if(wk->index2No[i+left] != 0){
            no = wk->index2No[i+left] - 1;
            if(WifiList_IsFriendData(pList,no)){
                sex = WifiList_GetFriendInfo(pList, no, WIFILIST_FRIEND_SEX);
                GF_BGL_BmpWinDataFill( &wk->TrainerNameWin[i], 0x8000 );
                GF_STR_PrintColor( &wk->TrainerNameWin[i], FONT_SYSTEM, wk->TrainerName[no],
                                   1, 1, MSG_NO_PUT, col[sex], NULL);
                bDisp = TRUE;
            }
        }
        if(!bDisp){
            GF_BGL_BmpWinOffVReq( &wk->TrainerNameWin[i]);
        }
        else{
            GF_BGL_BmpWinOnVReq( &wk->TrainerNameWin[i]);
        }
    }
}

//------------------------------------------------------------------
/**
 * $brief   index2No���쐬����
 * @param   wk		
 * @retval  none		
 */
//------------------------------------------------------------------

static void _makeIndex2NoTbl( WIFINOTE_WORK *wk)
{    
    int i,x;
    WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);
    int num = 0;

    MI_CpuFill8(wk->index2No, 0, WIFINOTE_MEMBER_MAX);
    
    for(i = 0; i < WIFINOTE_MEMBER_MAX; i++){  // �Z�[�u�f�[�^���疼�O�𓾂�
        STRBUF_Clear(wk->TrainerName[i]);
        if( WifiList_IsFriendData( pList, i ) ){
            STRBUF_SetStringCode(wk->TrainerName[i] ,WifiList_GetFriendNamePtr(pList,i));
        //if( WifiList_IsFriendData( pList, i ) ){
            wk->index2No[num] = i+1;
            num++;
        }
    }
}

//------------------------------------------------------------------
/**
 * $brief   �t�����h���X�g�\��������  WIFINOTE_MODE_FRIENDLIST_INIT
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------

static int WifiNote_FriendListInit( WIFINOTE_WORK *wk, int seq )
{
    int i,x;
    WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);
    int num = 0;

    GF_BGL_ScrClear(wk->bgl, GF_BGL_FRAME3_M);
	ArcUtil_BgCharSet( ARC_WIFINOTE_GRA, NARC_wifinote_techo_NCGR, wk->bgl,
                       GF_BGL_FRAME0_M, 0, 0, 0, HEAPID_WIFINOTE);
	ArcUtil_ScrnSet(   ARC_WIFINOTE_GRA, NARC_wifinote_techo_main_NSCR, wk->bgl,
                       GF_BGL_FRAME0_M, 0, 0, 0, HEAPID_WIFINOTE);
    ArcUtil_ScrnSet(   ARC_WIFINOTE_GRA, NARC_wifinote_techo_02_NSCR, wk->bgl,
                       GF_BGL_FRAME1_M, 0, 0, 0, HEAPID_WIFINOTE);

    if(GF_BGL_BmpWinAddCheck(&wk->TitleWin)){
        GF_BGL_BmpWinDel(&wk->TitleWin);
    }
    GF_BGL_BmpWinAdd(wk->bgl, &wk->TitleWin, GF_BGL_FRAME3_M, 1, 0, 13, 3, _NUKI_FONT_PALNO,  MENU_WIN_CGX_NUM - 13*4*2 );
    GF_BGL_BmpWinDataFill( &wk->TitleWin, 0x8000 );
	MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_06, wk->TitleString );
	GF_STR_PrintColor( &wk->TitleWin, FONT_TALK, wk->TitleString, 0, 4, MSG_NO_PUT, _COL_N_WHITE, NULL);
    GF_BGL_BmpWinOnVReq( &wk->TitleWin);

    if(GF_BGL_BmpWinAddCheck(&wk->MenuWin[3])){
        GF_BGL_BmpWinDel( &wk->MenuWin[3] );
    }
    GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[3], GF_BGL_FRAME3_M,
                     15, 21, 8, 2, _NUKI_FONT_PALNO,  MENU_WIN_CGX_NUM - 13*4*2 - (20*3) );
    GF_BGL_BmpWinDataFill( &wk->MenuWin[3], 0x8000 );
	MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_08, wk->MenuString[3] );
	GF_STR_PrintColor( &wk->MenuWin[3], FONT_SYSTEM, wk->MenuString[3], 0, 0, MSG_NO_PUT, _COL_N_BLACK, NULL);

    GF_BGL_BmpWinOnVReq( &wk->MenuWin[3]);

    _makeIndex2NoTbl(wk);

    for(i = 0;i < WIFINOTE_DISP_MEMBER_MAX; i++){
        if(i < 4){
            x = 5;
        }
        else{
            x = 20;
        }

        if(GF_BGL_BmpWinAddCheck(&wk->TrainerNameWin[i])){
            GF_BGL_BmpWinDel(&wk->TrainerNameWin[i]);
        }
        
        GF_BGL_BmpWinAdd(wk->bgl, &wk->TrainerNameWin[i], GF_BGL_FRAME3_M,
                         x, 5 + (i%4) * 4, 8, 2, _NUKI_FONT_PALNO,
                         MENU_WIN_CGX_NUM - 13*4*2 - (20*3) - (8 * 3 * (i+1)) );
        GF_BGL_BmpWinDataFill( &wk->TrainerNameWin[i], 0x8000 );
        GF_BGL_BmpWinOnVReq( &wk->TrainerNameWin[i]);
    }
    _listMenuCursorDisp(wk);
    WifiNoteFriendListChange(wk);
    _listMenuTrainerDisp(wk);

    CLACT_AnmChg( wk->MainActWork[_LEFT_ARROW], 0 );
    CLACT_AnmChg( wk->MainActWork[_RIGHT_ARROW], 1 );
    CLACT_SetDrawFlag( wk->MainActWork[_LEFT_ARROW], 1 );
    CLACT_SetDrawFlag( wk->MainActWork[_RIGHT_ARROW], 1 );
    
    wk->seq = WIFINOTE_MODE_FRIENDLIST;
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   main�J�[�\���ʒu�v�Z
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _mathMainCur(WIFINOTE_WORK* wk, int add)
{
    int pageOld = wk->mainCur / 8;
    
    if(wk->horizontalCur == 4){
        wk->subCur = 1;
    }
    else if(wk->subCur == 1){
        wk->subCur = 0;
    }
    else{
        wk->mainCur += add;
        wk->mainCur %= 32;
    }
    _listMenuCursorDisp(wk);
    if(pageOld != (wk->mainCur / 8)){
        WifiNoteFriendListChange(wk);
        _listMenuTrainerDisp(wk);
    }
}

//------------------------------------------------------------------
/**
 * $brief   �t�����h���X�g�\��������
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------

static int WifiNote_FriendList( WIFINOTE_WORK *wk, int seq )
{
    if(wk->friendTrg && sys.trg){
        EndMessageWindowOff(wk);

		// �Ƃ��������X�g���ĕ`�悷��K�v�͂Ȃ��̂ŁA���̂ݕ��A
        CLACT_SetDrawFlag( wk->MainActWork[_LEFT_ARROW], 1 );
        CLACT_SetDrawFlag( wk->MainActWork[_RIGHT_ARROW], 1 );

        wk->friendTrg = 0;
    }
    else if(sys.trg & PAD_BUTTON_DECIDE){

        Snd_SePlay(WIFINOTE_DECIDE_SE);

        if(wk->subCur){
            wk->seq = WIFINOTE_MODE_MAIN_MENU;
        }
        else{
            if(wk->index2No[wk->mainCur] != 0){
                wk->seq = WIFINOTE_MODE_PERSONAL_MENU;
            }
        }
	}
	else if(sys.trg & PAD_BUTTON_CANCEL){
        Snd_SePlay(WIFINOTE_BS_SE);
        wk->seq = WIFINOTE_MODE_MAIN_MENU;
	}
	else if( sys.repeat & PAD_KEY_UP){
        if(wk->horizontalCur != 0){
            wk->horizontalCur--;
            Snd_SePlay(WIFINOTE_MOVE_SE);
            _mathMainCur(wk,-1);
        }
	}
	else if( sys.repeat & PAD_KEY_DOWN){
        if(wk->horizontalCur < 4){
            wk->horizontalCur++;
            Snd_SePlay(WIFINOTE_MOVE_SE);
            _mathMainCur(wk,1);
        }
	}
	else if( sys.repeat & PAD_KEY_LEFT){
        if(!wk->subCur){
            wk->verticalCur = 1 - wk->verticalCur;
            Snd_SePlay(WIFINOTE_MOVE_SE);
            _mathMainCur(wk,-4);
        }
	}
	else if( sys.repeat & PAD_KEY_RIGHT){
        if(!wk->subCur){
            wk->verticalCur = 1 - wk->verticalCur;
            Snd_SePlay(WIFINOTE_MOVE_SE);
            _mathMainCur(wk,4);
        }
	}
    if(wk->seq != WIFINOTE_MODE_FRIENDLIST){
        CLACT_SetDrawFlag( wk->MainActWork[_LEFT_ARROW], 0 );
        CLACT_SetDrawFlag( wk->MainActWork[_RIGHT_ARROW], 0 );
    }
    
	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �t�����h���X�g�\��������  ���j���[����  WIFINOTE_MODE_PERSONAL_MENU
 * @param   wk		
 * @retval  none		
 */
//------------------------------------------------------------------

//==============================================================================
//	���j���[���X�g�p�f�[�^��
//==============================================================================
static const struct {
	u32  str_id;
	u32  param;
}_friendInfoMenuList[] = {
	{ msg_wifi_note_09, (u32)WIFINOTE_MODE_INFO_INIT },
	{ msg_wifi_note_10, (u32)WIFINOTE_MODE_RENAME_INIT },
    { msg_wifi_note_11, (u32)WIFINOTE_MODE_DELETE_INIT },
    { msg_wifi_note_12, (u32)BMPLIST_CANCEL },
};


static const struct {
	u32  str_id;
	u32  param;
}_friendInfoMenuListMini[] = {
    { msg_wifi_note_33, (u32)WIFINOTE_MODE_CODE_INIT },
	{ msg_wifi_note_10, (u32)WIFINOTE_MODE_RENAME_INIT },
    { msg_wifi_note_11, (u32)WIFINOTE_MODE_DELETE_INIT },
    { msg_wifi_note_12, (u32)BMPLIST_CANCEL },
};



///�I�����j���[�̃��X�g
static const BMPLIST_HEADER _friendInfoMenuListHeader = {
    NULL,			// �\�������f�[�^�|�C���^
    NULL,					// �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
    NULL,					// ���\�����Ƃ̃R�[���o�b�N�֐�
    NULL,                   // 
    NELEMS(_friendInfoMenuList),	// ���X�g���ڐ�
    NELEMS(_friendInfoMenuList),	// �\���ő區�ڐ�
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

///�I�����j���[�̃��X�g
static const BMPLIST_HEADER _friendInfoMenuListHeaderMini = {
    NULL,			// �\�������f�[�^�|�C���^
    NULL,					// �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
    NULL,					// ���\�����Ƃ̃R�[���o�b�N�֐�
    NULL,                   // 
    NELEMS(_friendInfoMenuListMini),	// ���X�g���ڐ�
    NELEMS(_friendInfoMenuListMini),	// �\���ő區�ڐ�
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

static int WifiNote_FriendListPersonalMenu(WIFINOTE_WORK *wk, int seq )
{
    int i,length,sex;
    BMPLIST_HEADER list_h;
    WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);

    sex = WifiList_GetFriendInfo(pList, wk->index2No[wk->mainCur]-1, WIFILIST_FRIEND_SEX);
    if(sex == PM_NEUTRAL){
//    if(0 == WifiList_GetFriendInfo(pList, wk->index2No[wk->mainCur]-1, WIFILIST_FRIEND_LASTBT_DAY)){
        // �V��łȂ��ꍇ�ڍ׉�ʂ��o�Ȃ�
        length = NELEMS(_friendInfoMenuListMini);
        list_h = _friendInfoMenuListHeaderMini;
        wk->menulist = BMP_MENULIST_Create( length , HEAPID_WIFINOTE );
        for(i=0; i< length ; i++){
            BMP_MENULIST_AddArchiveString( wk->menulist, wk->MsgManager, _friendInfoMenuListMini[i].str_id, _friendInfoMenuListMini[i].param );
        }
    }
    else{
        length = NELEMS(_friendInfoMenuList);
        list_h = _friendInfoMenuListHeader;
        wk->menulist = BMP_MENULIST_Create( length , HEAPID_WIFINOTE );
        for(i=0; i< length ; i++){
            BMP_MENULIST_AddArchiveString( wk->menulist, wk->MsgManager, _friendInfoMenuList[i].str_id, _friendInfoMenuList[i].param );
        }
    }
    if(GF_BGL_BmpWinAddCheck(&wk->ListWin)){
        GF_BGL_BmpWinDel(&wk->ListWin);
    }
    //BMP�E�B���h�E����
    GF_BGL_BmpWinAdd(wk->bgl,&wk->ListWin,
                     GF_BGL_FRAME2_M, 16, 9, 15, length * 2, FLD_SYSFONT_PAL, FLD_MENU_WIN_CGX - length * 2);
    BmpMenuWinWrite(&wk->ListWin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	list_h.list = wk->menulist;
    list_h.win = &wk->ListWin;
    wk->lw = BmpListSet(&list_h, 0, 0, HEAPID_WIFINOTE);
    GF_BGL_BmpWinOnVReq(&wk->ListWin);

    {
        MYSTATUS* pTarget = MyStatus_AllocWork(HEAPID_WIFINOTE);

        MyStatus_SetMyName(pTarget, WifiList_GetFriendNamePtr(pList,wk->index2No[wk->mainCur]-1));
        WORDSET_RegisterPlayerName( wk->WordSet, 0, pTarget);
        WifiNoteMessagePrint(wk,msg_wifi_note_13);
        sys_FreeMemoryEz(pTarget);
    }

	wk->pos_bak = 0;
    wk->seq = WIFINOTE_MODE_PERSONAL_MENU_WAIT;
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �l�f�[�^�A�N�Z�X���j���[ WIFINOTE_MODE_PERSONAL_MENU_WAIT
 * @param   wk		
 * @retval  none		
 */
//------------------------------------------------------------------

static int WifiNote_FriendListPersonalMenuWait(WIFINOTE_WORK *wk, int seq )        //
{
	u16 tmp_pos_bak;
    u32	ret;

    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) != 0 ){
        return seq;
    }
    ret = BmpListMain(wk->lw);

#if 1
	//BMP���X�g�̑S�̈ʒu���擾
	tmp_pos_bak = wk->pos_bak;		//�ޔ�
	BmpListDirectPosGet( wk->lw, &wk->pos_bak );

	//�J�[�\�������������`�F�b�N
	if( tmp_pos_bak != wk->pos_bak ){
        Snd_SePlay(WIFINOTE_MOVE_SE);
	}
#endif

    switch(ret){
    case BMPLIST_NULL:
        return seq;
    case BMPLIST_CANCEL:
        Snd_SePlay(WIFINOTE_BS_SE);
        CLACT_SetDrawFlag( wk->MainActWork[_LEFT_ARROW], 1 );
        CLACT_SetDrawFlag( wk->MainActWork[_RIGHT_ARROW], 1 );

        wk->seq = WIFINOTE_MODE_FRIENDLIST;
        break;
    default:
        Snd_SePlay(WIFINOTE_DECIDE_SE);
        if(ret == WIFINOTE_MODE_INFO_INIT){
            GF_BGL_ScrClear(wk->bgl, GF_BGL_FRAME3_M);
            WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT,
                            WIPE_FADE_BLACK, 
                            6, 1, HEAPID_WIFINOTE);
        }
        wk->seq = ret;
        break;
    }
    EndMessageWindowOff(wk);
    BmpMenuWinClear(&wk->ListWin, WINDOW_TRANS_ON );
    GF_BGL_BmpWinDel(&wk->ListWin);
    BmpListExit(wk->lw, NULL, NULL);
    BMP_MENULIST_Delete( wk->menulist );
    return seq;
}



//------------------------------------------------------------------
/**
 * $brief   �Ƃ������̃R�[�h�̕\�� WIFINOTE_MODE_CODE_INIT
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------

static int _friendCodeDispInit(WIFINOTE_WORK *wk, int seq)
{

    if(wk->index2No[wk->mainCur] != 0){
        WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);
        DWCFriendData *frienddata = WifiList_GetDwcDataPtr(pList,wk->index2No[wk->mainCur]-1);
        u64 code = DWC_GetFriendKey(frienddata);
        
        if(code!=0){
            MYSTATUS* pTarget = MyStatus_AllocWork(HEAPID_WIFINOTE);
            MyStatus_SetMyName(pTarget, WifiList_GetFriendNamePtr(pList,wk->index2No[wk->mainCur]-1));
            
            Snd_SePlay(WIFINOTE_DECIDE_SE);
            _userCodeInRegister(wk, code);
            WORDSET_RegisterPlayerName( wk->WordSet, 0, pTarget);
            WifiNoteMessagePrintAll(wk,msg_wifi_note_32);
            wk->friendTrg = 1;
            sys_FreeMemoryEz(pTarget);
        }
    }
    wk->seq = WIFINOTE_MODE_FRIENDLIST;
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �����̃R�[�h�̕\�� WIFINOTE_MODE_MYCODE_DISP_INIT
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------

static int _dispMyCodeInit( WIFINOTE_WORK* wk, int seq )
{
    int i,x;
    WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);
    int num = 0;
    DWCUserData *userdata = WifiList_GetMyUserInfo(pList);
    u64 code = DWC_CreateFriendKey(userdata);

    GF_BGL_ScrClear(wk->bgl, GF_BGL_FRAME3_M);
    ArcUtil_ScrnSet(   ARC_WIFINOTE_GRA, NARC_wifinote_techo_04_NSCR, wk->bgl,
                       GF_BGL_FRAME1_M, 0, 0, 0, HEAPID_WIFINOTE);

    if(GF_BGL_BmpWinAddCheck(&wk->TitleWin)){
        GF_BGL_BmpWinDel(&wk->TitleWin);
    }
    GF_BGL_BmpWinAdd(wk->bgl, &wk->TitleWin,
                     GF_BGL_FRAME3_M,
                     1, 0,
                     20, 3,
                     _NUKI_FONT_PALNO, MENU_WIN_CGX_NUM - 20 * 4 * 2);
    GF_BGL_BmpWinDataFill( &wk->TitleWin, 0x8000 );
    WORDSET_RegisterPlayerName( wk->WordSet, 0, SaveData_GetMyStatus(wk->pSaveData));
    MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_23, wk->pExpStrBuf );
    WORDSET_ExpandStr( wk->WordSet, wk->TitleString, wk->pExpStrBuf );
	GF_STR_PrintColor( &wk->TitleWin, FONT_TALK, wk->TitleString, 0, 4, MSG_NO_PUT, _COL_N_WHITE, NULL);

    GF_BGL_BmpWinOnVReq(&wk->TitleWin);

    // ���ɏo��������
    if(GF_BGL_BmpWinAddCheck(&wk->MsgWin)){
        GF_BGL_BmpWinDel(&wk->MsgWin);
    }
    GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin,
                     GF_BGL_FRAME3_M,
                     5, 13,
                     21, 8,
                     _NUKI_FONT_PALNO, 100 );
	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x8000 );
    if(code == 0){  // �R�[�h�擾���s
        MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_25, wk->TalkString );
    }
    else{
        MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_24, wk->TalkString );
    }
    GF_STR_PrintColor( &wk->MsgWin, FONT_SYSTEM,
                       wk->TalkString, 0, 0, MSG_NO_PUT, _COL_N_BLACK, NULL);

    GF_BGL_BmpWinOnVReq(&wk->MsgWin);
    
    if(code != 0){
        _userCodeInRegister(wk, code);
        if(GF_BGL_BmpWinAddCheck(&wk->ListWin)){
            GF_BGL_BmpWinDel(&wk->ListWin);
        }
        GF_BGL_BmpWinAdd(wk->bgl, &wk->ListWin,
                         GF_BGL_FRAME3_M,
                         8, 8,
                         14, 2,
                         _NUKI_FONT_PALNO, 50);
        MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_28, wk->pExpStrBuf );
        WORDSET_ExpandStr( wk->WordSet, wk->TalkString, wk->pExpStrBuf );
        // ��b�E�C���h�E�g�`��
        GF_BGL_BmpWinDataFill(&wk->ListWin, 0x8000 );
        // ������`��J�n
        GF_STR_PrintColor( &wk->ListWin, FONT_SYSTEM, wk->TalkString,
                                           0, 0, MSG_NO_PUT,_COL_N_BLACK, NULL);
        GF_BGL_BmpWinOnVReq(&wk->ListWin);
    }


    wk->seq = WIFINOTE_MODE_MYCODE_DISP;
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �����̃R�[�h�̕\�� WIFINOTE_MODE_MYCODE_DISP
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------

static int _dispMyCodeWait( WIFINOTE_WORK* wk, int seq )
{
	if(sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL)){
        wk->seq = WIFINOTE_MODE_MAIN_MENU;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �t�����h�R�[�h��3�������ă��W�X�^�ɓ˂�����
 * @param   code �t�����h�R�[�h
 * @retval  none		
 */
//------------------------------------------------------------------

static void _userCodeInRegister(WIFINOTE_WORK* wk, u64 code)
{
    u64 num;

    num = code / 100000000;
    WORDSET_RegisterNumber(wk->WordSet, 1, num, 4,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
    num = (code/10000) % 10000;
    WORDSET_RegisterNumber(wk->WordSet, 2, num, 4,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
    num = code % 10000;
    WORDSET_RegisterNumber(wk->WordSet, 3, num, 4,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
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
static void BgInit3D( GF_BGL_INI * ini )
{
/*
    static const GF_BGL_DISPVRAM SetBankData = {
		GX_VRAM_BG_128_B,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_0_A,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_01_FG			// �e�N�X�`���p���b�g�X���b�g
	};


	GF_Disp_SetBank( &SetBankData );
   */
	GX_SetGraphicsMode( GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BG0_AS_3D);


    // BG SYSTEM
	{	
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
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
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME1_M, 32, 0, HEAPID_WIFINOTE);
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );


	}
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME2_M, 32, 0, HEAPID_WIFINOTE);
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}

/*	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_23,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME2_M, 32, 0, HEAPID_WIFINOTE);
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}*/

	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_23,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME3_M, 32, 0, HEAPID_WIFINOTE);
		GF_BGL_ScrClear( ini, GF_BGL_FRAME3_M );
	}
/*
	// �T�u��ʃe�L�X�g��
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );
	}

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
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_WIFINOTE );
//	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_WIFINOTE );

    GF_BGL_PrioritySet(GF_BGL_FRAME1_M , 3);   // �w�i
    GF_BGL_PrioritySet(GF_BGL_FRAME2_M , 2);  // �w�i
    GF_BGL_PrioritySet(GF_BGL_FRAME0_M , 1);  // �g���[�i�[3D
    GF_BGL_PrioritySet(GF_BGL_FRAME3_M , 0);   //����
}

//------------------------------------------------------------------
/**
 * 
 *
 * @param   none		
 *
 */
//------------------------------------------------------------------
static void BGInit3DDrive(void)
{
	// NitroSystem:�R�c�G���W���̏�����
	NNS_G3dInit();
	// �}�g���N�X�X�^�b�N�̏�����
    G3X_InitMtxStack();

	// �R�c�g�p�ʂ̐ݒ�(�\�����v���C�I���e�B�[)
//    GX_SetVisiblePlane(GX_PLANEMASK_BG0);
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority(1);

	// �e��`�惂�[�h�̐ݒ�(�V�F�[�h���A���`�G�C���A�X��������)
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(TRUE);
//    G2_BlendNone(); 
	G3X_AlphaTest(FALSE, 0);	// �A���t�@�e�X�g�@�@�I�t
	G3X_AlphaBlend(TRUE);		// �A���t�@�u�����h�@�I��

	// �N���A�J���[�̐ݒ�
    G3X_SetClearColor(GX_RGB(0, 0, 0),	// clear color
                      0,				// clear alpha
                      0x7fff,			// clear depth
                      63,				// clear polygon ID
                      FALSE				// fog
                      );

	// �W�I���g���G���W���N����K���Ă΂�Ȃ���΂Ȃ�Ȃ�
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);

	// �r���[�|�[�g�̐ݒ�
    G3_ViewPort(0, 0, 255, 191);
}

//------------------------------------------------------------------
/**
 * $brief   �Ƃ������̏ڍ׃f�[�^�\��������
 * @param   wk		WIFINOTE_WORK
 * @retval  none		seq
 */
//------------------------------------------------------------------

static int _infoFriendDataInit( WIFINOTE_WORK* wk, int seq )    //WIFINOTE_MODE_INFO_INIT
{
	SOFT_SPRITE_ARC	ssa;
    int i,x,y;
    MYSTATUS *pTarget;
    WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);
    int num = 0;
    int friendNo = wk->index2No[wk->mainCur]-1;

    if(!WIPE_SYS_EndCheck()){
        return seq;
    }

    _cellActFree( wk );
	BmpWinDelete( wk );
    BgExit(wk->bgl);
    
    wk->bgl = GF_BGL_BglIniAlloc( HEAPID_WIFINOTE );
    BgInit3D(wk->bgl);
    BGInit3DDrive();

    // �w�i
    ArcUtil_BgCharSet( ARC_WIFINOTE_GRA, NARC_wifinote_techo_NCGR, wk->bgl,
                       GF_BGL_FRAME1_M, 0, 0, 0, HEAPID_WIFINOTE);
    ArcUtil_ScrnSet( ARC_WIFINOTE_GRA, NARC_wifinote_techo_main_NSCR, wk->bgl,
                     GF_BGL_FRAME1_M, 0, 0, 0, HEAPID_WIFINOTE);
    ArcUtil_ScrnSet( ARC_WIFINOTE_GRA, NARC_wifinote_techo_03_NSCR, wk->bgl,
                     GF_BGL_FRAME2_M, 0, 0, 0, HEAPID_WIFINOTE);
    // �^�C�g��
    if(GF_BGL_BmpWinAddCheck(&wk->TitleWin)){
        GF_BGL_BmpWinDel(&wk->TitleWin);
    }
    GF_BGL_BmpWinAdd(wk->bgl, &wk->TitleWin,
                     GF_BGL_FRAME3_M,
                     1, 0,
                     20, 3,
                     _NUKI_FONT_PALNO, MENU_WIN_CGX_NUM - 20 * 3);
    GF_BGL_BmpWinDataFill( &wk->TitleWin, 0x8000 );

    pTarget = MyStatus_AllocWork(HEAPID_WIFINOTE);
    MyStatus_SetMyName(pTarget, WifiList_GetFriendNamePtr(pList,friendNo));
    WORDSET_RegisterPlayerName( wk->WordSet, 0, pTarget);
    MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_14, wk->pExpStrBuf );
    WORDSET_ExpandStr( wk->WordSet, wk->TitleString, wk->pExpStrBuf );
	GF_STR_PrintColor( &wk->TitleWin, FONT_TALK, wk->TitleString, 0, 4, MSG_NO_PUT, _COL_N_WHITE, NULL);
    GF_BGL_BmpWinOnVReq(&wk->TitleWin);

    // ���O
    if(GF_BGL_BmpWinAddCheck(&wk->ListWin)){
        GF_BGL_BmpWinDel(&wk->ListWin);
    }
    GF_BGL_BmpWinAdd(wk->bgl, &wk->ListWin,
                     GF_BGL_FRAME3_M,
                     3, 18,  8, 2,_NUKI_FONT_PALNO, MENU_WIN_CGX_NUM - 20 * 3 * 2 - 8*2*2);
    GF_BGL_BmpWinDataFill( &wk->ListWin, 0x8000 );
    WORDSET_RegisterPlayerName( wk->WordSet, 0, pTarget);
    MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_07, wk->pExpStrBuf );
    WORDSET_ExpandStr( wk->WordSet, wk->TitleString, wk->pExpStrBuf );
	GF_STR_PrintColor( &wk->ListWin, FONT_SYSTEM, wk->TitleString, 0, 0, MSG_NO_PUT, _COL_N_WHITE, NULL);
    GF_BGL_BmpWinOnVReq(&wk->ListWin);

    // �g���[�i�[�G
    wk->spriteManager = SoftSpriteInit( HEAPID_WIFINOTE );
    {
        int id = WifiList_GetFriendInfo(pList, friendNo, WIFILIST_FRIEND_UNION_GRA);
        int sex = WifiList_GetFriendInfo(pList, friendNo, WIFILIST_FRIEND_SEX);
        int no = UnionView_GetTrainerInfo(sex, id, UNIONVIEW_TRTYPE);
        TrGraArcDataGet(&ssa, no, PARA_FRONT , sex);
        wk->sprite = SoftSpriteAdd(wk->spriteManager, &ssa, 54, 84, 0, 0, NULL, NULL);
        if(sex == PM_FEMALE){
            u16* pScrAddr = GF_BGL_ScreenAdrsGet( wk->bgl, GF_BGL_FRAME2_M );
            for(y = 0x10;y < 0x15;y++){
                for(x = 0;x < 12;x++){
                    pScrAddr[x+y*32] = ((pScrAddr[x+y*32] & 0xfff ) + 0x1000);
                }
            }
            GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME2_M);  // �X�N���[���ɍX�V
        }
    }
    // ���
    if(GF_BGL_BmpWinAddCheck(&wk->MenuWin[0])){
        GF_BGL_BmpWinDel(&wk->MenuWin[0]);
    }
    GF_BGL_BmpWinAdd(wk->bgl, &wk->MenuWin[0],
                     GF_BGL_FRAME3_M,
                     15, 4,  16, 19,_NUKI_FONT_PALNO, 2 );
    GF_BGL_BmpWinDataFill( &wk->MenuWin[0], 0x8000 );

    // �O���[�v
    {
        MYSTATUS* pTarget = MyStatus_AllocWork(HEAPID_WIFINOTE);
        MyStatus_SetMyName(pTarget, WifiList_GetFriendGroupNamePtr(pList,friendNo));
        WORDSET_RegisterPlayerName( wk->WordSet, 0, pTarget);
        sys_FreeMemoryEz(pTarget);
    }
    MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_15, wk->pExpStrBuf );
    WORDSET_ExpandStr( wk->WordSet, wk->MenuString[0], wk->pExpStrBuf );
	GF_STR_PrintColor( &wk->MenuWin[0], FONT_SYSTEM, wk->MenuString[0], 0, 2, MSG_NO_PUT, _COL_N_BLACK, NULL);
    // �ΐ퐬��
    MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_16, wk->MenuString[1] );
	GF_STR_PrintColor( &wk->MenuWin[0], FONT_SYSTEM, wk->MenuString[1], 0, 24, MSG_NO_PUT, _COL_N_BLACK, NULL);
    // ����
    num = WifiList_GetFriendInfo(pList, friendNo, WIFILIST_FRIEND_BATTLE_WIN);
    WORDSET_RegisterNumber(wk->WordSet, 0, num, 4, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
    MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_17, wk->pExpStrBuf );
    WORDSET_ExpandStr( wk->WordSet, wk->TitleString, wk->pExpStrBuf );
	GF_STR_PrintColor( &wk->MenuWin[0], FONT_SYSTEM, wk->TitleString, 60, 40-1, MSG_NO_PUT, _COL_N_BLACK, NULL);
    // �܂�
    num = WifiList_GetFriendInfo(pList, friendNo, WIFILIST_FRIEND_BATTLE_LOSE);
    WORDSET_RegisterNumber(wk->WordSet, 0, num, 4, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
    MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_18, wk->pExpStrBuf );
    WORDSET_ExpandStr( wk->WordSet, wk->TitleString, wk->pExpStrBuf );
	GF_STR_PrintColor( &wk->MenuWin[0], FONT_SYSTEM, wk->TitleString, 61, 56-3, MSG_NO_PUT, _COL_N_BLACK, NULL);
    // �|�P��������
    MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_19, wk->TitleString );
	GF_STR_PrintColor( &wk->MenuWin[0], FONT_SYSTEM, wk->TitleString, 0, 72+2, MSG_NO_PUT, _COL_N_BLACK, NULL);
    
    num = WifiList_GetFriendInfo(pList, friendNo, WIFILIST_FRIEND_TRADE_NUM);
    WORDSET_RegisterNumber(wk->WordSet, 0, num, 4, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
    MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_20, wk->pExpStrBuf );
    WORDSET_ExpandStr( wk->WordSet, wk->TitleString, wk->pExpStrBuf );
	GF_STR_PrintColor( &wk->MenuWin[0], FONT_SYSTEM, wk->TitleString, 60, 94-2, MSG_NO_PUT, _COL_N_BLACK, NULL);
 //�Ō�̓��t
    MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_21, wk->TitleString );
	GF_STR_PrintColor( &wk->MenuWin[0], FONT_SYSTEM, wk->TitleString, 0, 110+3, MSG_NO_PUT, _COL_N_BLACK, NULL);

    num = WifiList_GetFriendInfo(pList, friendNo, WIFILIST_FRIEND_LASTBT_DAY);
    if(num != 0){
        WORDSET_RegisterNumber(wk->WordSet, 2, num, 2, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
        num = WifiList_GetFriendInfo(pList, friendNo, WIFILIST_FRIEND_LASTBT_YEAR);
        WORDSET_RegisterNumber(wk->WordSet, 0, num, 4, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
        num = WifiList_GetFriendInfo(pList, friendNo, WIFILIST_FRIEND_LASTBT_MONTH);
        WORDSET_RegisterNumber(wk->WordSet, 1, num, 2, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
        num = WifiList_GetFriendInfo(pList, friendNo, WIFILIST_FRIEND_LASTBT_DAY);
        WORDSET_RegisterNumber(wk->WordSet, 2, num, 2, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
        MSGMAN_GetString(  wk->MsgManager, msg_wifi_note_22, wk->pExpStrBuf );
        WORDSET_ExpandStr( wk->WordSet, wk->TitleString, wk->pExpStrBuf );
        GF_STR_PrintColor( &wk->MenuWin[0], FONT_SYSTEM, wk->TitleString, 0, 126+3, MSG_NO_PUT, _COL_N_BLACK, NULL);
    }
    GF_BGL_BmpWinOnVReq(&wk->MenuWin[0]);
    sys_FreeMemoryEz(pTarget);

    wk->seq = WIFINOTE_MODE_INFO_DISP;

    WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN,
                    WIPE_FADE_BLACK, 
                    6, 1, HEAPID_WIFINOTE);
    
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �Ƃ������̏ڍ׃f�[�^�\���@//WIFINOTE_MODE_INFO_DISP
 * @param   wk		WIFINOTE_WORK
 * @retval  none		seq
 */
//------------------------------------------------------------------

static int _infoFriendDataDisp( WIFINOTE_WORK* wk, int seq )    
{

	G3X_Reset();
	G3X_ResetMtxStack();
	NNS_G2dSetupSoftwareSpriteCamera();

	SoftSpriteMain( wk->spriteManager );

	G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
    
    if(!WIPE_SYS_EndCheck()){
        return seq;
    }
	if(sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL)){

        Snd_SePlay(WIFINOTE_BS_SE);

        WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT,
                        WIPE_FADE_BLACK, 
                        6, 1, HEAPID_WIFINOTE);

        wk->seq = WIFINOTE_MODE_INFO_END;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �Ƃ������̏ڍ׃f�[�^�\�������@//WIFINOTE_MODE_INFO_END
 * @param   wk		WIFINOTE_WORK
 * @retval  none		seq
 */
//------------------------------------------------------------------

static int _infoFriendDataEnd( WIFINOTE_WORK* wk, int seq )    
{

	G3X_Reset();
	G3X_ResetMtxStack();
	NNS_G2dSetupSoftwareSpriteCamera();

	SoftSpriteMain( wk->spriteManager );

	G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
    
    if(!WIPE_SYS_EndCheck()){
        return seq;
    }

    
    if( wk->sprite ){  // �J������
        SoftSpriteDel( wk->sprite );
        SoftSpriteEnd( wk->spriteManager );
        wk->sprite = NULL;
    }
    BgExit(wk->bgl);
    
    wk->bgl = GF_BGL_BglIniAlloc( HEAPID_WIFINOTE );
    BgInit(wk->bgl);
    _cellActInit( wk );

    // �T�u���BG0�L�����]��  0x7fff 0x5d28
    ArcUtil_BgCharSet( ARC_WIFINOTE_GRA, NARC_wifinote_techo_sub_NCGR, wk->bgl, GF_BGL_FRAME0_S, 0, 0, 0, HEAPID_WIFINOTE);
    // �T�u���BG0�X�N���[���]��
    ArcUtil_ScrnSet(   ARC_WIFINOTE_GRA, NARC_wifinote_techo_sub_NSCR, wk->bgl, GF_BGL_FRAME0_S, 0, 0, 0, HEAPID_WIFINOTE);

    WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN,
                    WIPE_FADE_BLACK, 
                    3, 1, HEAPID_WIFINOTE);

    wk->seq = WIFINOTE_MODE_FRIENDLIST_INIT;
    return seq;
}


//------------------------------------------------------------------
/**
 * $brief   ���C�����j���[�̖߂�ۂ̏����� WIFINOTE_MODE_MAIN_MENU
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static int WifiNote_MainReturn( WIFINOTE_WORK *wk, int seq )
{
    int i;
    
    GF_BGL_ScrClear(wk->bgl, GF_BGL_FRAME3_M);
    ArcUtil_ScrnSet(   ARC_WIFINOTE_GRA, NARC_wifinote_techo_main_NSCR, wk->bgl,
                       GF_BGL_FRAME0_M, 0, 0, 0, HEAPID_WIFINOTE);
    ArcUtil_ScrnSet(   ARC_WIFINOTE_GRA, NARC_wifinote_techo_01_NSCR, wk->bgl,
                       GF_BGL_FRAME1_M, 0, 0, 0, HEAPID_WIFINOTE);

    for(i=0;i<_OAM_NUM;i++){
        CLACT_SetDrawFlag( wk->MainActWork[i], 0 );
    }

    wk->mainCur = 0;
    wk->subCur = 0;
    MainMenuMsgInit(wk);
    mainMenuCursorDisp(wk);
    wk->seq = WIFINOTE_MODE;
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   ���O�ύX������  WIFINOTE_MODE_RENAME_INIT
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------
static int _renameInit( WIFINOTE_WORK* wk, int seq )
{
    WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEOUT, WIPE_TYPE_HOLEOUT, WIPE_FADE_BLACK, 
                    COMM_BRIGHTNESS_SYNC, 1, HEAPID_WIFINOTE);
    wk->seq = WIFINOTE_MODE_RENAME_OPEN_WINDOW;
    return seq;
}

//------------------------------------------------------------------
/**
 * ���{��o�[�W�����œ��͂��ꂽ�����񂩃`�F�b�N
 *
 * @retval  BOOL	TRUE���Ɠ��{��
 */
//------------------------------------------------------------------
static BOOL IsJapaneseName( const STRCODE* name )
{
	// �ŏ��̂P���������ŗǂ��ł��낤
	return IsJapaneseCode( *name );
}

//------------------------------------------------------------------
/**
 * $brief   ���O�ύX�҂� WIFINOTE_MODE_RENAME_OPEN_WINDOW
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------
static int _renameOpenWindow( WIFINOTE_WORK* wk, int seq )
{
    WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);

    if( WIPE_SYS_EndCheck() ){
        _dispVisibleControl(VISIBLE_OFF);
        _graphicEnd(wk);

        wk->nameinParam = NameIn_ParamAllocMake( HEAPID_WIFINOTE, NAMEIN_FRIENDNAME, 0, 
        											NAMEIN_PERSON_LENGTH, SaveData_GetConfig(wk->pSaveData) );
        wk->subProc     = PROC_Create( &NameInProcData, wk->nameinParam, HEAPID_WIFINOTE );
        wk->seq         = WIFINOTE_MODE_RENAME_WAIT;

		{
			const STRCODE* pname = WifiList_GetFriendNamePtr( pList, wk->index2No[wk->mainCur]-1 );

			#if( PM_LANG == LANG_JAPAN )
			{
				if( IsJapaneseName( pname ) )
				{
					STRBUF_SetStringCode( wk->nameinParam->strbuf, pname );
				}
				else
				{
					STRBUF_Clear( wk->nameinParam->strbuf );
				}
			}
			#else
			{
				if( IsJapaneseName( pname ) == FALSE )
				{
					STRBUF_SetStringCode( wk->nameinParam->strbuf, pname );
				}
				else
				{
					STRBUF_Clear( wk->nameinParam->strbuf );
				}
			}
			#endif
		}

    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   ���O�ύX�҂� WIFINOTE_MODE_RENAME_OPEN_WINDOW
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------
static int _renameWait( WIFINOTE_WORK* wk, int seq )
{
    if( ProcMain( wk->subProc ) ) {
        PROC_Delete( wk->subProc );
        // ���O�ۑ�
		if(!wk->nameinParam->cancel){
	        STRBUF_Copy(wk->pTempTrainerName, wk->nameinParam->strbuf);
	        {
    	        WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);
        	    WifiList_SetFriendName(pList, wk->index2No[wk->mainCur]-1, wk->pTempTrainerName);
        	}
		}

        NameIn_ParamDelete( wk->nameinParam );
		WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );
///     WIPE_ResetBrightness( WIPE_DISP_MAIN );	<<20060721 del
///     WIPE_ResetBrightness( WIPE_DISP_SUB );	<<20060721 del
        _dispVisibleControl(VISIBLE_OFF);
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEIN, WIPE_TYPE_HOLEIN, WIPE_FADE_BLACK, 
				COMM_BRIGHTNESS_SYNC, 1, HEAPID_WIFINOTE);
        _graphicInit(wk);
        WifiNote_FriendListInit(wk,seq);  // ��
        _dispVisibleControl(VISIBLE_ON);
        wk->seq = WIFINOTE_MODE_RENAME_ENTRY;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   ���O�ύX���� WIFINOTE_MODE_RENAME_ENTRY
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------
static int _renameEntry( WIFINOTE_WORK* wk, int seq )
{
    if( WIPE_SYS_EndCheck() ){
        wk->seq = WIFINOTE_MODE_FRIENDLIST;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   ���O������ WIFINOTE_MODE_DELETE_INIT
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------

static int _deleteInit( WIFINOTE_WORK* wk, int seq )
{
    MYSTATUS* pTarget = MyStatus_AllocWork(HEAPID_WIFINOTE);
    WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);

    MyStatus_SetMyName(pTarget, WifiList_GetFriendNamePtr(pList,wk->index2No[wk->mainCur] - 1));
    WORDSET_RegisterPlayerName( wk->WordSet, 0, pTarget);
    WifiNoteMessagePrint(wk,msg_wifi_note_29);
    sys_FreeMemoryEz(pTarget);
    wk->seq = WIFINOTE_MODE_DELETE_YESNO;
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   ���O������YESNO�m�F  WIFINOTE_MODE_DELETE_YESNO
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------

static int _deleteYesNo( WIFINOTE_WORK* wk, int seq )
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        // �͂��������E�C���h�E���o��
        wk->pYesNoWork =
            BmpYesNoSelectInit( wk->bgl,
                                &_yesNoBmpDat,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                HEAPID_WIFINOTE );
        wk->seq = WIFINOTE_MODE_DELETE_CHECK;
    }
    return seq;
}

//------------------------------------------------------------------
/**
 * $brief   ���O������  WIFINOTE_MODE_DELETE_CHECK
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------


static int _deleteCheck( WIFINOTE_WORK* wk, int seq )
{
    int i;
    int ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_WIFINOTE);
    if(ret == BMPMENU_NULL){  // �܂��I��
        return seq;
    }else if(ret == 0){ // �͂���I�������ꍇ
        //����
        WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);
        WifiList_ResetData(pList, wk->index2No[wk->mainCur] - 1);

        wk->seq = WIFINOTE_MODE_FRIENDLIST_INIT;
    }
    else{  // ��������I�������ꍇ

		// �Ƃ��������X�g���ĕ`�悷��K�v�͂Ȃ��̂ŁA���̂ݕ��A
        CLACT_SetDrawFlag( wk->MainActWork[_LEFT_ARROW], 1 );
        CLACT_SetDrawFlag( wk->MainActWork[_RIGHT_ARROW], 1 );

        wk->seq = WIFINOTE_MODE_FRIENDLIST;
    }
    EndMessageWindowOff(wk);
    return seq;
}

// WIFINOTE_MODE_END_WAIT
//------------------------------------------------------------------
/**
 * $brief   �I�����b�Z�[�W�\���I���҂�
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	WifiNote_EndWait( WIFINOTE_WORK *wk, int seq )
{			
    // ���C�v�t�F�[�h�J�n
    WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEOUT, WIPE_TYPE_HOLEOUT, WIPE_FADE_BLACK, 
                    COMM_BRIGHTNESS_SYNC, 1, HEAPID_WIFINOTE);
    seq = SEQ_OUT;						//�I���V�[�P���X��
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


static void WifiNoteMessagePrint( WIFINOTE_WORK *wk, int msgno )
{
    u8 speed = CONFIG_GetMsgPrintSpeed(SaveData_GetConfig(wk->pSaveData));
	// ������擾
    if(GF_BGL_BmpWinAddCheck(&wk->MsgWin)){
        GF_BGL_BmpWinDel(&wk->MsgWin);
    }
    GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin,
                     GF_BGL_FRAME2_M,
                     COMM_MSG_WIN_PX, COMM_MSG_WIN_PY,
                     COMM_MSG_WIN_SX, COMM_MSG_WIN_SY,
                     COMM_MESFONT_PAL, COMM_MSG_WIN_CGX);

	MSGMAN_GetString(  wk->MsgManager, msgno, wk->pExpStrBuf );
	WORDSET_ExpandStr( wk->WordSet, wk->TalkString, wk->pExpStrBuf );

	// ��b�E�C���h�E�g�`��
    GF_BGL_BmpWinDataFill(&wk->MsgWin, 15 );
    BmpTalkWinWrite(&wk->MsgWin, WINDOW_TRANS_OFF,COMM_TALK_WIN_CGX_NUM, COMM_MESFRAME_PAL );

	// ������`��J�n
	wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0,
                                       speed, NULL);

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


static void WifiNoteMessagePrintAll( WIFINOTE_WORK *wk, int msgno )
{
	// ������擾
    if(GF_BGL_BmpWinAddCheck(&wk->MsgWin)){
        GF_BGL_BmpWinDel(&wk->MsgWin);
    }
    GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin,
                     GF_BGL_FRAME2_M,
                     COMM_MSG_WIN_PX, COMM_MSG_WIN_PY,
                     COMM_MSG_WIN_SX, COMM_MSG_WIN_SY,
                     COMM_MESFONT_PAL, COMM_MSG_WIN_CGX);

	MSGMAN_GetString(  wk->MsgManager, msgno, wk->pExpStrBuf );
	WORDSET_ExpandStr( wk->WordSet, wk->TalkString, wk->pExpStrBuf );

	// ��b�E�C���h�E�g�`��
    GF_BGL_BmpWinDataFill(&wk->MsgWin, 15 );
    BmpTalkWinWrite(&wk->MsgWin, WINDOW_TRANS_OFF,COMM_TALK_WIN_CGX_NUM, COMM_MESFRAME_PAL );

	// ������`��J�n
    wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0,
                                       MSG_NO_PUT, NULL);
    GF_BGL_BmpWinOnVReq(&wk->MsgWin);

}

//------------------------------------------------------------------
/**
 * $brief   ��b�\���E�C���h�E�I���҂�
 *
 * @param   msg_index		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int EndMessageWait( int msg_index )
{
	if(GF_MSG_PrintEndCheck( msg_index )==0){
		return 1;
	}
	return 0;
}


//------------------------------------------------------------------
/**
 * $brief   
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void EndMessageWindowOff( WIFINOTE_WORK *wk )
{
	BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
}

//==============================================================================
/**
 * �t�����h���X�g�ɂƂ�������ǉ�
 * @param 	nonte
 * @retval  1 = �����B0 = ���s�B
 */
//==============================================================================
static int _createFriendKeyToken(SAVEDATA* pSaveData, int no, u64 friendCode)
{
    DWCFriendData *list = NULL;
    DWCUserData *userdata = NULL;
    int pos,ret;

    if(pSaveData!=NULL){
        userdata = WifiList_GetMyUserInfo(SaveData_GetWifiListData(pSaveData));
        if(!DWC_CheckFriendKey(userdata, friendCode)){
            return -1;
        }
        ret = dwc_checkFriendCodeByToken(pSaveData, friendCode, &pos);
        if(ret == DWCFRIEND_INLIST){
            return -2;
        }
        list = WifiList_GetDwcDataPtr(SaveData_GetWifiListData(pSaveData), no);
        DWC_CreateFriendKeyToken(list, friendCode);
    }
    return 0;
}


static void _dispVisibleControl(int flg)
{
    GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0|GX_PLANEMASK_BG1|GX_PLANEMASK_BG2|GX_PLANEMASK_BG3, flg );
    GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, flg );
}
