//==============================================================================================
/**
 * @file	backup_load.c
 * @brief	�o�b�N�A�b�v�ǂݍ���
 * @author	
 * @date	
 */
//==============================================================================================
#include "common.h"

#include "system/procsys.h"
#include "system/arc_util.h"
#include "savedata/savedata_def.h"

#include "system/lib_pack.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/fontproc.h"
#include "msgdata/msg.naix"
#include "system/pm_str.h"
#include "system/wipe.h"
#include "system/window.h"
#include "system/snd_tool.h"
#include "system/palanm.h"
#include "system/wordset.h"
#include "system/pmfprint.h"
#include "savedata/savedata.h"
#include "system/main.h"

#include "msgdata/msg_load_warning.h"

//================================================================
//================================================================
//
//
//		
//
//
//================================================================
extern const PROC_DATA StartMenuProcData;
FS_EXTERN_OVERLAY( startmenu );

//----------------------------------
//�萔�錾
//----------------------------------
// �o�q�n�b���C���V�[�P���X
enum {
	BACKUP_LOAD_SEQ_INIT = 0,
	BACKUP_LOAD_SEQ_MAIN,
	BACKUP_LOAD_SEQ_EXIT,
};

//----------------------------------
//�^�錾
//----------------------------------
///	�^�C�g���S�̐���p���[�N�\����
typedef struct BACKUP_LOAD_WORK_tag
{
	int					heapID; 
	int					subseq; 
	int					warningID; 
	int					msgseq; 
	int					msgID; 
	STRBUF*				msgstr;
	GF_BGL_INI*			bgl;
	MSGDATA_MANAGER*	msgman;
	GF_BGL_BMPWIN		msgwin;
	BMPMENU_WORK*		yesnowin;
	SAVEDATA*			savedata;
	void*				timericon;

}BACKUP_LOAD_WORK;

//���b�Z�[�W�֐�����w���`
enum {
	A_BUTTON_WAIT = 0,
	A_BUTTON_NOWAIT,
};

//----------------------------------
//�O���֐���`
//----------------------------------
extern void	Main_SetNextProc(FSOverlayID ov_id, const PROC_DATA * proc_data);

//----------------------------------
//�֐��錾
//----------------------------------
PROC_RESULT BackupLoad_Init( PROC * proc, int * seq );
PROC_RESULT BackupLoad_Main( PROC * proc, int * seq );
PROC_RESULT BackupLoad_Exit( PROC * proc, int * seq );

//static void BackupLoad_VBlank( void* work );

static void BackupLoad_VramBankSet( BACKUP_LOAD_WORK* wk );
static void BackupLoad_VramBankRelease( BACKUP_LOAD_WORK* wk );
static void BackupLoad_MsgDataSet( BACKUP_LOAD_WORK* wk );
static void BackupLoad_MsgDataRelease( BACKUP_LOAD_WORK* wk );

static BOOL BackupLoad_SubSeq( BACKUP_LOAD_WORK* wk );
static BOOL BackupLoad_MsgPrint( BACKUP_LOAD_WORK* wk, u32 msgID, int button_mode, int wait );
//----------------------------------
//�}�N���錾
//----------------------------------
#define FADE( pattern, col, heapID ) {						\
	WIPE_SYS_Start(	WIPE_PATTERN_WMS,pattern,pattern,col,	\
					WIPE_DEF_DIV,WIPE_DEF_SYNC,heapID);		\
}

//�a�f�R���g���[���萔
#define BACKUP_LOAD_TEXT_FRAME	(GF_BGL_FRAME0_M)

//=================================================================================================
//
// �o�q�n�b��`�e�[�u��
//
//=================================================================================================
const PROC_DATA BackupLoadProcData = {
	BackupLoad_Init,
	BackupLoad_Main,
	BackupLoad_Exit,
	NO_OVERLAY_ID
};

//================================================================
//----------------------------------
//�o�q�n�b������
//----------------------------------
PROC_RESULT BackupLoad_Init(PROC * proc, int * seq)
{
	BACKUP_LOAD_WORK * wk;
	int	heapID = HEAPID_BACKUPCONT;

	sys_CreateHeap( HEAPID_BASE_APP, heapID, 0x20000 );

	wk = PROC_AllocWork( proc, sizeof( BACKUP_LOAD_WORK ), heapID );
	memset( wk, 0, sizeof( BACKUP_LOAD_WORK ) );

	wk->heapID	= heapID;
	wk->subseq = 0;
	wk->savedata = ((MAINWORK*)PROC_GetParentWork(proc))->savedata;

	return	PROC_RES_FINISH;
}

//----------------------------------
//�o�q�n�b���C��
//----------------------------------
PROC_RESULT BackupLoad_Main(PROC * proc, int* seq)
{
	BACKUP_LOAD_WORK * wk = PROC_GetWork( proc );
	PROC_RESULT result = PROC_RES_CONTINUE;

	switch( *seq ){
	// ��ʏ�����
	case BACKUP_LOAD_SEQ_INIT:
		WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );

		sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
		sys_HBlankIntrSet( NULL,NULL );		// HBlank�Z�b�g

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane(0);
		GXS_SetVisiblePlane(0);
		sys_KeyRepeatSpeedSet(4,8);

		BackupLoad_VramBankSet( wk );
		BackupLoad_MsgDataSet( wk );

		//sys_VBlankFuncChange(BackupLoad_VBlank,(void*)wk);
		GF_Disp_DispOn();

		*seq = BACKUP_LOAD_SEQ_MAIN;
		break;

	// ���C�����[�v
	case BACKUP_LOAD_SEQ_MAIN:
		if (BackupLoad_SubSeq( wk ) == TRUE ){
			*seq = BACKUP_LOAD_SEQ_EXIT;
		}
		break;

	// �I��
	case BACKUP_LOAD_SEQ_EXIT:
		BackupLoad_MsgDataRelease( wk );
		BackupLoad_VramBankRelease( wk );
		sys_VBlankFuncChange( NULL, NULL );

		result = PROC_RES_FINISH;
		break;
	}
	return result;
}

//----------------------------------
//�o�q�n�b�I��
//----------------------------------
PROC_RESULT BackupLoad_Exit(PROC * proc, int * seq)
{
	BACKUP_LOAD_WORK * wk = PROC_GetWork( proc );
	int heapID = wk->heapID;

	PROC_FreeWork( proc );
	sys_DeleteHeap( heapID );

	Main_SetNextProc( FS_OVERLAY_ID( startmenu ), &StartMenuProcData );

	return	PROC_RES_FINISH;
}


//----------------------------------
//�u�a�k�`�m�j�֐�
//----------------------------------
#if 0
static void BackupLoad_VBlank(void* work)
{
	BACKUP_LOAD_WORK* wk = work;

	GF_BGL_VBlankFunc(wk->bgl);
}
#endif


//----------------------------------
//�u�q�`�l�ݒ�
//----------------------------------
#define BACKUP_LOAD_NULL_PALETTE	( 0x6c21 )		//�a�f�o�b�N�O���E���h�p���b�g
#define PALSIZE						( 2*16 )

#define BACKUP_LOAD_TWIN_CGXNUM	(512 - TALK_WIN_CGX_SIZ)
#define BACKUP_LOAD_NWIN_CGXNUM	(BACKUP_LOAD_TWIN_CGXNUM - MENU_WIN_CGX_SIZ)

#define	BACKUP_LOAD_TEXT_PALNUM	(1)
#define BACKUP_LOAD_TWIN_PALNUM	(2)
#define BACKUP_LOAD_NWIN_PALNUM	(3)

static void BackupLoad_VramBankSet( BACKUP_LOAD_WORK* wk )
{
	{ //�u�q�`�l�ݒ�
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_256_AB,				// ���C��2D�G���W����BG
			GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
			GX_VRAM_SUB_BG_NONE,			// �T�u2D�G���W����BG
			GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
			GX_VRAM_OBJ_NONE,				// ���C��2D�G���W����OBJ
			GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
			GX_VRAM_SUB_OBJ_NONE,			// �T�u2D�G���W����OBJ
			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
			GX_VRAM_TEX_NONE,				// �e�N�X�`���C���[�W�X���b�g
			GX_VRAM_TEXPLTT_NONE			// �e�N�X�`���p���b�g�X���b�g
		};
		GF_Disp_SetBank( &vramSetTable );
	}

	{ //�a�f���C�u�����p�������m��
		wk->bgl = GF_BGL_BglIniAlloc(wk->heapID);
	}
	{ // �a�f�V�X�e���ݒ�
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0,GX_BG0_AS_2D
		};	
		GF_BGL_InitBG( &BGsys_data );
	}
	{ // ���C���a�f�V�X�e���ݒ�
		GF_BGL_BGCNT_HEADER hd0 = { 0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
									GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x18000, 
									GX_BG_EXTPLTT_01, 1, 0, 0, FALSE };
		GF_BGL_BGControlSet( wk->bgl, BACKUP_LOAD_TEXT_FRAME, &hd0, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( wk->bgl, BACKUP_LOAD_TEXT_FRAME );	
	}
	//���b�Z�[�W�E�C���h�E�L�������p���b�g�ǂݍ��݁i�E�C���h�E�O���j
	TalkWinGraphicSet(	wk->bgl, BACKUP_LOAD_TEXT_FRAME,
						BACKUP_LOAD_TWIN_CGXNUM, BACKUP_LOAD_TWIN_PALNUM,
						0,wk->heapID);
	//���j���[�E�C���h�E�L�������p���b�g�ǂݍ��݁i�E�C���h�E�O���j
	MenuWinGraphicSet(	wk->bgl, BACKUP_LOAD_TEXT_FRAME,
						BACKUP_LOAD_NWIN_CGXNUM, BACKUP_LOAD_NWIN_PALNUM,
						0,wk->heapID);
	//�t�H���g�p���b�g�ǂݍ��݁i�V�X�e���j
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, BACKUP_LOAD_TEXT_PALNUM * PALSIZE, wk->heapID );

	GF_BGL_ClearCharSet( BACKUP_LOAD_TEXT_FRAME, 32, 0, wk->heapID );
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, 0 );	//�w�i�F������
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0 );	//�w�i�F������
}

static void BackupLoad_VramBankRelease( BACKUP_LOAD_WORK* wk )
{
	GF_BGL_VisibleSet( GF_BGL_FRAME0_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME1_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME2_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME3_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME0_S, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME1_S, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME2_S, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME3_S, VISIBLE_OFF );
	GF_BGL_BGControlExit( wk->bgl, BACKUP_LOAD_TEXT_FRAME );
	sys_FreeMemoryEz( wk->bgl );
}


//----------------------------------
//���b�Z�[�W�ݒ�
//----------------------------------
#define BACKUP_LOAD_STRBUF_SIZE	(0x400)	//���b�Z�[�W�o�b�t�@�T�C�Y
#define DOTSIZE						(8)
// ���b�Z�[�W�E�B���h�E
#define	BACKUP_LOAD_MSG_WIN_PX		(2)
#define	BACKUP_LOAD_MSG_WIN_PY		(19)
#define	BACKUP_LOAD_MSG_WIN_SX		(27)
#define	BACKUP_LOAD_MSG_WIN_SY		(4)
#define	BACKUP_LOAD_MSG_WIN_PAL	(BACKUP_LOAD_TEXT_PALNUM)
#define	BACKUP_LOAD_MSG_WIN_CGX	\
(BACKUP_LOAD_NWIN_CGXNUM-(BACKUP_LOAD_MSG_WIN_SX*BACKUP_LOAD_MSG_WIN_SY))

// �͂�/�������E�B���h�E
#define	BACKUP_LOAD_YESNO_WIN_PX		(25)
#define	BACKUP_LOAD_YESNO_WIN_PY		(13)
#define	BACKUP_LOAD_YESNO_WIN_SX		(6)
#define	BACKUP_LOAD_YESNO_WIN_SY		(4)
#define	BACKUP_LOAD_YESNO_WIN_PAL		(BACKUP_LOAD_TEXT_PALNUM)
#define	BACKUP_LOAD_YESNO_WIN_CGX	\
(BACKUP_LOAD_MSG_WIN_CGX-(BACKUP_LOAD_YESNO_WIN_SX*BACKUP_LOAD_YESNO_WIN_SY))

static const BMPWIN_DAT BackupLoadMsgWinData =
{
	BACKUP_LOAD_TEXT_FRAME,	//�E�C���h�E�g�p�t���[��
	BACKUP_LOAD_MSG_WIN_PX,BACKUP_LOAD_MSG_WIN_PY,//�E�C���h�E�̈�̍���XY���W
	BACKUP_LOAD_MSG_WIN_SX,BACKUP_LOAD_MSG_WIN_SY,//�E�C���h�E�̈��XY�T�C�Y
	BACKUP_LOAD_MSG_WIN_PAL,	//�E�C���h�E�̈�̃p���b�g�i���o�[ 
	BACKUP_LOAD_MSG_WIN_CGX,	//�E�C���h�E�L�����̈�̊J�n�L�����N�^�i���o�[
};

static const BMPWIN_DAT BackupLoadYesNoWinData =
{
	BACKUP_LOAD_TEXT_FRAME,	//�E�C���h�E�g�p�t���[��
	BACKUP_LOAD_YESNO_WIN_PX,BACKUP_LOAD_YESNO_WIN_PY,//�E�C���h�E�̈�̍���XY���W
	BACKUP_LOAD_YESNO_WIN_SX,BACKUP_LOAD_YESNO_WIN_SY,//�E�C���h�E�̈��XY�T�C�Y
	BACKUP_LOAD_YESNO_WIN_PAL,	//�E�C���h�E�̈�̃p���b�g�i���o�[ 
	BACKUP_LOAD_YESNO_WIN_CGX,	//�E�C���h�E�L�����̈�̊J�n�L�����N�^�i���o�[
};

static void BackupLoad_MsgDataSet( BACKUP_LOAD_WORK* wk )
{
	//���b�Z�[�W�f�[�^�ǂݍ���
	wk->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_load_warning_dat,wk->heapID);
	//���b�Z�[�W�\���V�X�e��������
	MSG_PrintInit();
	wk->msgseq = 0; 

	//���b�Z�[�W�E�C���h�E�r�b�g�}�b�v�쐬�i�E�C���h�E�����j
	GF_BGL_BmpWinAddEx(wk->bgl,&wk->msgwin,&BackupLoadMsgWinData );
	GF_BGL_BmpWinFill(	&wk->msgwin,FBMP_COL_WHITE,0,0,//bmp,col,startX,startY,sizeX,sizeY
						BACKUP_LOAD_MSG_WIN_SX*DOTSIZE,BACKUP_LOAD_MSG_WIN_SY*DOTSIZE);
}

static void BackupLoad_MsgDataRelease( BACKUP_LOAD_WORK* wk )
{
	GF_BGL_BmpWinDel(&wk->msgwin);
	//���b�Z�[�W�f�[�^�j��
	MSGMAN_Delete(wk->msgman);
}

//----------------------------------
//���C���V�[�P���X
//----------------------------------
enum {
	BACKUP_LOAD_SUBSEQ_LOADMAIN = 0,
	BACKUP_LOAD_SUBSEQ_LOADWARING_MSGINIT,
	BACKUP_LOAD_SUBSEQ_LOADWARING_MSGINITWAIT,
	BACKUP_LOAD_SUBSEQ_LOADWARING_MSG,
	BACKUP_LOAD_SUBSEQ_LOADWARNING_MSGEXIT,
	BACKUP_LOAD_SUBSEQ_END,
};

static BOOL BackupLoad_SubSeq( BACKUP_LOAD_WORK* wk )
{
	BOOL result = FALSE;

	switch( wk->subseq ){

	case BACKUP_LOAD_SUBSEQ_LOADMAIN:
		{
			LOAD_RESULT load_result = SaveData_GetLoadResult(wk->savedata);

			//���[�h
			//load_result = ���[�h�֐�
			switch (load_result) {
			case LOAD_RESULT_OK:
			case LOAD_RESULT_NULL:
				wk->subseq = BACKUP_LOAD_SUBSEQ_END;
				break;
			case LOAD_RESULT_NG:
				wk->warningID = warning01;
				wk->subseq = BACKUP_LOAD_SUBSEQ_LOADWARING_MSGINIT;
				break;
			case LOAD_RESULT_BREAK:
				wk->warningID = warning02;
				wk->subseq = BACKUP_LOAD_SUBSEQ_LOADWARING_MSGINIT;
				break;
			}
#if 0
			if( load_result == TRUE ){
				wk->warningID = warning01;
				wk->subseq = BACKUP_LOAD_SUBSEQ_LOADWARING_MSGINIT;
			} else {
				wk->subseq = BACKUP_LOAD_SUBSEQ_END;
			}
#endif
		}
		break;

	case BACKUP_LOAD_SUBSEQ_LOADWARING_MSGINIT:
		GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, BACKUP_LOAD_NULL_PALETTE );
		GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, BACKUP_LOAD_NULL_PALETTE );
		FADE( WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, wk->heapID )
		wk->subseq = BACKUP_LOAD_SUBSEQ_LOADWARING_MSGINITWAIT;
		break;

	case BACKUP_LOAD_SUBSEQ_LOADWARING_MSGINITWAIT:
		if(WIPE_SYS_EndCheck() == TRUE){
			wk->subseq = BACKUP_LOAD_SUBSEQ_LOADWARING_MSG;
		}
		break;

	case BACKUP_LOAD_SUBSEQ_LOADWARING_MSG:
		if(BackupLoad_MsgPrint(wk,wk->warningID,A_BUTTON_WAIT,4) == TRUE){
			FADE( WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, wk->heapID )
			wk->subseq = BACKUP_LOAD_SUBSEQ_LOADWARNING_MSGEXIT;
		}
		break;

	case BACKUP_LOAD_SUBSEQ_LOADWARNING_MSGEXIT:
		if(WIPE_SYS_EndCheck() == TRUE){
			GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, 0 );
			GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0 );
			wk->subseq = BACKUP_LOAD_SUBSEQ_END;
		}
		break;

	case BACKUP_LOAD_SUBSEQ_END:
		result = TRUE;
		break;
	}
	return result;
}

//----------------------------------
//���b�Z�[�W�\��
//----------------------------------
static BOOL BackupLoad_MsgPrint( BACKUP_LOAD_WORK* wk, u32 msgID, int button_mode, int wait )
{
	BOOL result = FALSE;

	switch(wk->msgseq){
	case 0:
		//�̈�N���A
		GF_BGL_BmpWinFill( &wk->msgwin, FBMP_COL_WHITE, 0, 0,
						BACKUP_LOAD_MSG_WIN_SX * DOTSIZE, BACKUP_LOAD_MSG_WIN_SY * DOTSIZE );
		BmpTalkWinWrite( &wk->msgwin, WINDOW_TRANS_ON,
						BACKUP_LOAD_TWIN_CGXNUM, BACKUP_LOAD_TWIN_PALNUM );

		//������o�b�t�@�̍쐬
		wk->msgstr = STRBUF_Create( BACKUP_LOAD_STRBUF_SIZE, wk->heapID);	
		//������̎擾
		MSGMAN_GetString(wk->msgman,msgID,wk->msgstr);
		//������̕\���i���b�Z�[�W�X�s�[�h���B�R���t�B�O�ݒ肪���m�ɂƂ�Ȃ�����������j
		wk->msgID = GF_STR_PrintSimple(	&wk->msgwin,FONT_TALK,wk->msgstr,0,0,wait,NULL);
		if( wait == 0 ){
			STRBUF_Delete(wk->msgstr);
			wk->msgseq++;
		}
		wk->msgseq++;
		break;

	case 1:
		//������`��҂�
		if(!(GF_MSG_PrintEndCheck(wk->msgID))){
			STRBUF_Delete(wk->msgstr);
			wk->msgseq++;
		}
		break;

	case 2:
		//�I���҂�
		if((button_mode != A_BUTTON_WAIT)||(sys.trg & PAD_BUTTON_A)){
			wk->msgseq = 0;
			result = TRUE;
		}
	}
	return result;
}






