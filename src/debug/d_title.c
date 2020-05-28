//============================================================================================
/**
 * @file	d_title.c	
 * @brief	�f�o�b�O�^�C�g�����j���[
 * @author	Hiroyuki Nakamura
 * @date	05.07.08
 */
//============================================================================================

#ifdef	PM_DEBUG

#include "common.h"
#include "system/fontproc.h"
#include "system/bmp_list.h"
#include "system/lib_pack.h"
#include "system/arc_util.h"
#include "system/wipe.h"
#include "system/snd_tool.h"
#include "demo/title.h"
#include "system/gamestart.h"
//#include "demo/opening/opening_sys.h"
//#include "field/field.h"
#include "poke_test.h"
#include "tr_test.h"

#include "communication/communication.h"
#include "system/main.h"

#include "msgdata/msg_debug_title.h"
#include "msgdata/msg.naix"

#include "wifi/dwc_rap.h"
#include "wifi/dwc_test.h"

#include "system/builddate.h"

//============================================================================================
//	overlay��`
//============================================================================================

FS_EXTERN_OVERLAY( title );
FS_EXTERN_OVERLAY( title_debug );

//============================================================================================
//	�萔��`
//============================================================================================
typedef void (*SELECT_FUNC)(SAVEDATA *);

typedef struct {
	GF_BGL_INI * bgl;
	GF_BGL_BMPWIN	win;
	GF_BGL_BMPWIN	datewin;
	BMPLIST_WORK * lw;
	SELECT_FUNC select_func;
	BMP_MENULIST_DATA *bmd;
	u32	end_flg;
}D_TITLE_WORK;

#define	FONT_PAL_NO		( 0 )


#define	HEAPID_DEBUG_TITLE	HEAPID_DEBUG_APPLICATION

//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

static void VramBankSet(void);
static void BgInit( GF_BGL_INI * ini );
static void BmpListCB1( u32 param, u8 mode );
static void BmpListCB2( u8 index, u32 param, u8 y );
static void D_TitleMenuMemFree( GF_BGL_INI * ini );


static void SetFieldDebugStartProc(SAVEDATA * savedata);
static void SetFieldContinueProc(SAVEDATA * savedata);
static void SetDebugPokeGraProc(SAVEDATA * savedata);
static void SetDebugTrGraProc(SAVEDATA * savedata);
static void SetDebugSoundTestProc(SAVEDATA * savedata);
static void SetDebugFightProc(SAVEDATA * savedata);
static void SetTitleProc(SAVEDATA * savedata);
static void SetDebugWiFiProc( SAVEDATA * savedata );
static void SetDebugWiFiTestProc( SAVEDATA * savedata );
static void SetDebugSeletNameProc(SAVEDATA * savedata);
static void SetDebugBreakSaveProc(SAVEDATA * savedata);
static void SetDebugRtcSettingProc(SAVEDATA * savedata);
//static void SetOpeningProc(SAVEDATA * savedata);

//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================

//gmm�t�@�C����ID�𕶎���w��Ɏg���\���̐錾
typedef struct
{
	u32	strID;
	u32	param;
}LIST_DATA;

static const LIST_DATA ListData[] =
{
	//���j���[�̕�����́Aconvert/message/src/debug_title.gmm�ɒǉ����Ă�������
	{ DT_DEBUGGAME,		(u32)SetFieldDebugStartProc },
	{ DT_CONTINUE,		(u32)SetFieldContinueProc },
	{ DT_SELNAME,		(u32)SetDebugSeletNameProc },
	//{ DT_OPENING,		(u32)SetOpeningProc },
	{ DT_SOUNDTEST,		(u32)SetDebugSoundTestProc },
	{ DT_POKEGRATEST,	(u32)SetDebugPokeGraProc },
	{ DT_TRGRATEST,		(u32)SetDebugTrGraProc },
	{ DT_DEBUGFIGHT,	(u32)SetDebugFightProc },
//	{ DT_WIFI,			(u32)SetDebugWiFiProc },
	{ DT_BREAKSAVE,		(u32)SetDebugBreakSaveProc },
	{ DT_RTC_SETTING,	(u32)SetDebugRtcSettingProc },
	{ DT_MODORU,		(u32)SetTitleProc },
};

static const BMPLIST_HEADER ListHeader = {
	NULL,
	NULL,					// �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
	NULL,					// ���\�����Ƃ̃R�[���o�b�N�֐�
	NULL,					// BMP�E�B���h�E�f�[�^
	NELEMS(ListData),		// ���X�g���ڐ�
	6,						// �\���ő區�ڐ�
	0,						// ���x���\���w���W
	12,						// ���ڕ\���w���W
	0,						// �J�[�\���\���w���W
	0,						// �\���x���W
	FBMP_COL_WHITE,			//�����F
	FBMP_COL_BLACK,			//�w�i�F
	FBMP_COL_BLK_SDW,		//�����e�F
	0,						// �����Ԋu�w
	16,						// �����Ԋu�x
	BMPLIST_LRKEY_SKIP,		// �y�[�W�X�L�b�v�^�C�v
	FONT_SYSTEM,			// �����w��(�{���� u8 �����ǁA����Ȃɍ��Ȃ��Ǝv���̂�)
	0						// �a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
};




//--------------------------------------------------------------------------------------------
/**
 * VRAM������
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VramBankSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_C,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_32_H,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_16_F,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_01_AB,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_0123_E			// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &vramSetTable );
}

//--------------------------------------------------------------------------------------------
/**
 * BG������
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgInit( GF_BGL_INI * ini )
{
	{	// BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	{	// MAIN DISP BG0
		GF_BGL_BGCNT_HEADER MBg0_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd000, GX_BG_CHARBASE_0x00000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &MBg0_Data, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );
	}

	{	// MAIN DISP BG1
		GF_BGL_BGCNT_HEADER MBg1_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x00000,
			GX_BG_EXTPLTT_01, 1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &MBg1_Data, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
	}

	{	// MAIN DISP BG2
		GF_BGL_BGCNT_HEADER MBg2_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x00000,
			GX_BG_EXTPLTT_23, 2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &MBg2_Data, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}

	{	// MAIN DISP BG3
		GF_BGL_BGCNT_HEADER MBg3_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000,
			GX_BG_EXTPLTT_23, 3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &MBg3_Data, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME3_M );
	}
}


//--------------------------------------------------------------------------------------------
/**
 * �������J��
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void D_TitleMenuMemFree( GF_BGL_INI * ini )
{
	// BGL�J��
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_M );
/*
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
*/
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//�f�o�b�O�Q�[���J�n
static void SetFieldDebugStartProc(SAVEDATA * savedata)
{
	Main_SetNextProc(OVERLAY_ID_GAMESTART, &DebugNewGameStartProcData);
}
//�l���I�����ăf�o�b�O�Q�[���J�n
static void SetDebugSeletNameProc(SAVEDATA * savedata)
{
	Main_SetNextProc(FS_OVERLAY_ID(title_debug), &DebugPersonMenuProcData);
}
//�R���e�B�j���[�ŃQ�[���J�n
static void SetFieldContinueProc(SAVEDATA * savedata)
{
	if (SaveData_GetExistFlag(savedata)) {
		Main_SetNextProc(OVERLAY_ID_GAMESTART, &ContinueGameStartProcData);
	} else {
		Main_SetNextProc(FS_OVERLAY_ID(title), &TitleProcData);
	}
}
//�|�P�����O���t�B�b�N�m�F
static void SetDebugPokeGraProc(SAVEDATA * savedata)
{
	Main_SetNextProc(FS_OVERLAY_ID(title_debug), &PokeGraTestProcData);
}
//�g���[�i�[�O���t�B�b�N�m�F
static void SetDebugTrGraProc(SAVEDATA * savedata)
{
	Main_SetNextProc(FS_OVERLAY_ID(title_debug), &TrGraTestProcData);
}
//�f�o�b�O�t�@�C�g�J�n
static void SetDebugFightProc(SAVEDATA * savedata)
{
	Main_SetNextProc(NO_OVERLAY_ID, &DebugFightProcData);
}
//�T�E���h�e�X�g�J�n
static void SetDebugSoundTestProc(SAVEDATA * savedata)
{
	Main_SetNextProc(FS_OVERLAY_ID(title_debug), &SoundTestProcData);
}
//�q�s�b����
static void SetDebugRtcSettingProc(SAVEDATA * savedata)
{
	Main_SetNextProc(FS_OVERLAY_ID(title_debug), &DebugRtcMenuProcData);
}
//�^�C�g���ɖ߂�
static void SetTitleProc(SAVEDATA * savedata)
{
	Main_SetNextProc(FS_OVERLAY_ID(title), &TitleProcData);
}
//------------------------------------------------------------------
///	�Z�[�u�f�[�^�j��
//------------------------------------------------------------------
static void SetDebugBreakSaveProc(SAVEDATA * savedata)
{
	SaveData_Erase(savedata);
	Main_SetNextProc(FS_OVERLAY_ID(title), &TitleProcData);
}

//------------------------------------------------------------------
/**
 * @brief	�X�^�[�g���j���[����Ăяo�����Wi-Fi�ݒ���
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static PROC_RESULT StartMenuWifiProc_Init(PROC * proc, int * seq)
{
  sys_CreateHeap( HEAPID_BASE_APP, HEAPID_WIFIMENU, 0x41000);
  DwcUtilOverlayCall(((MAINWORK *)PROC_GetParentWork(proc))->savedata, HEAPID_WIFIMENU);
  sys_DeleteHeap(HEAPID_WIFIMENU);
  OS_ResetSystem(0); 
  return PROC_RES_FINISH;
}
static const PROC_DATA StartMenuWifiProcData = {
  StartMenuWifiProc_Init,
  NULL,
  NULL,
  NO_OVERLAY_ID,
};

static void SetDebugWiFiProc( SAVEDATA * savedata )
{
    // Wi-Fi�����Ă�
    Main_SetNextProc(NO_OVERLAY_ID, &StartMenuWifiProcData);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�^�C�g���v���Z�X�FBMPMENULISTDATA�̐���
 * @param	bmd		BMP_MENULIST_DATA�\���̂ւ̃|�C���^
 */
//--------------------------------------------------------------------------------------------
static	void	BMP_MENULIST_Make(BMP_MENULIST_DATA *bmd)
{
	int				i;
	MSGDATA_MANAGER	*man;

	man=MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,NARC_msg_debug_title_dat,HEAPID_DEBUG_TITLE);

	for(i=0;i<NELEMS(ListData);i++){
		BMP_MENULIST_AddArchiveString(bmd,man,ListData[i].strID,ListData[i].param);
	}

	MSGMAN_Delete(man);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�^�C�g���v���Z�X�F������
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT DebugTitleMenuProc_Init(PROC * proc, int * seq)
{
//�\�[�X�����當�����\�[�X�����O�������̂ɑΉ������o�[�W����
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_DEBUG_TITLE, 0x10000);
	{
		D_TITLE_WORK * wk;

		wk = PROC_AllocWork(proc, sizeof(D_TITLE_WORK), HEAPID_DEBUG_TITLE);

		wk->bgl = GF_BGL_BglIniAlloc( HEAPID_DEBUG_TITLE );

		GF_Disp_GX_VisibleControlInit();
		VramBankSet();
		BgInit( wk->bgl );

		MSG_PrintInit();

		SystemFontPaletteLoad( PALTYPE_MAIN_BG, FONT_PAL_NO * 32, HEAPID_DEBUG_TITLE );

		{
			BMPLIST_HEADER	list_h;

			wk->bmd=BMP_MENULIST_Create(NELEMS(ListData),HEAPID_DEBUG_TITLE);
			BMP_MENULIST_Make(wk->bmd);

			GF_BGL_BmpWinAdd(
				wk->bgl, &wk->win, GF_BGL_FRAME0_M, 1, 1, 14, 12, FONT_PAL_NO, 1 );

			list_h = ListHeader;
			list_h.list = wk->bmd;
			list_h.win = &wk->win;
			wk->lw = BmpListSet( &list_h, 0, 0, HEAPID_DEBUG_TITLE );

		}
		{
			STRBUF * strbuf;
			STRBUF * msg;
			WORDSET * ws;
			ws = WORDSET_Create(HEAPID_DEBUG_TITLE);
			msg = MSGDAT_GetStrDirectAlloc(ARC_MSG, NARC_msg_debug_title_dat,
					DT_BUILDDATE, HEAPID_DEBUG_TITLE);
			GF_BGL_BmpWinAdd(
				wk->bgl, &wk->datewin, GF_BGL_FRAME0_M, 1, 15, 25, 3, FONT_PAL_NO, 1 + 14 * 12);
			GF_BGL_BmpWinDataFill(&wk->datewin, FontHeaderGet(FONT_SYSTEM, FONT_HEADER_B_COLOR));

			strbuf = STRBUF_Create(64, HEAPID_DEBUG_TITLE);
			WORDSET_DebugBuildTime(ws);
			WORDSET_ExpandStr(ws, strbuf, msg);
			GF_STR_PrintSimple(&wk->datewin, FONT_SYSTEM, strbuf, 0, 0, MSG_ALLPUT, NULL);
			STRBUF_Delete(strbuf);
			STRBUF_Delete(msg);
			WORDSET_Delete(ws);
		}
	}

		WIPE_ResetBrightness( WIPE_DISP_MAIN );
		WIPE_ResetBrightness( WIPE_DISP_SUB );

		GF_Disp_DispOn();

	Snd_BgmChannelSetAndReverbSet( 0 );	//�g�p�\�`�����l������A���o�[�u�ݒ�(�N���A)

	return PROC_RES_FINISH;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�^�C�g���v���Z�X�F���C��
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT DebugTitleMenuProc_Main(PROC * proc, int * seq)
{
	D_TITLE_WORK * wk = PROC_GetWork(proc);
	u32	ret;

	ret = BmpListMain( wk->lw );

	switch( ret ){
	case BMPLIST_NULL:
		break;
	case BMPLIST_CANCEL:
		ret = (u32)SetTitleProc;
	default:
		BMP_MENULIST_Delete(wk->bmd);
		BmpListExit( wk->lw, NULL, NULL );
		GF_BGL_BmpWinOff( &wk->win );
		GF_BGL_BmpWinDel( &wk->win );
		GF_BGL_BmpWinOff( &wk->datewin );
		GF_BGL_BmpWinDel( &wk->datewin);
		D_TitleMenuMemFree( wk->bgl );
		sys_FreeMemoryEz( wk->bgl );
		wk->select_func = (SELECT_FUNC)ret;
		return PROC_RES_FINISH;
	}
	return PROC_RES_CONTINUE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�^�C�g���v���Z�X�F�I��
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT DebugTitleMenuProc_End(PROC * proc, int * seq)
{
	D_TITLE_WORK * wk = PROC_GetWork(proc);
	wk->select_func(((MAINWORK*)PROC_GetParentWork(proc))->savedata);
	PROC_FreeWork(proc);

	sys_DeleteHeap(HEAPID_DEBUG_TITLE);
	return PROC_RES_FINISH;
}


//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
const PROC_DATA DebugTitleMenuProcData = {
	DebugTitleMenuProc_Init,
	DebugTitleMenuProc_Main,
	DebugTitleMenuProc_End,
	NO_OVERLAY_ID
};

#endif	//PM_DEBUG

