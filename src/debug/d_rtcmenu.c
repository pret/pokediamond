//============================================================================================
/**
 * @file	d_rtcmenu.c	
 * @brief	�f�o�b�ORTC���j���[
 * @author	Hiroyuki Nakamura
 * @date	05.07.08
 *
 * 2006.06.20 tamada	d_title.c���R�s�[���č쐬
 */
//============================================================================================

#ifdef	PM_DEBUG

#include "common.h"
#include "system/fontproc.h"
#include "system/bmp_list.h"
#include "system/wordset.h"
#include "system/lib_pack.h"
#include "system/pm_rtc.h"
#include "system/arc_util.h"
#include "system/wipe.h"
#include "system/snd_tool.h"
#include "demo/title.h"

#include "system/main.h"

#include "msgdata/msg_debug_rtc.h"
#include "msgdata/msg.naix"

#include "debug/d_rtcmenu.h"

//============================================================================================
//	overlay��`
//============================================================================================

FS_EXTERN_OVERLAY( title );
FS_EXTERN_OVERLAY( title_debug );

//============================================================================================
//	�萔��`
//============================================================================================

typedef struct {
	GF_BGL_INI * bgl;
	GF_BGL_BMPWIN	menuwin;
	GF_BGL_BMPWIN	infowin;
	BMPLIST_WORK * lw;
	BMP_MENULIST_DATA *bmd;
	u32 change_wait;
	RTCDate date;
	RTCTime time;
}D_RTC_WORK;

typedef void (*CHANGE_FUNC)(D_RTC_WORK *);

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


static void AddMonth(D_RTC_WORK * wk);
static void DelMonth(D_RTC_WORK * wk);
static void AddDay(D_RTC_WORK * wk);
static void DelDay(D_RTC_WORK * wk);
static void AddHour(D_RTC_WORK * wk);
static void DelHour(D_RTC_WORK * wk);
static void AddMinute(D_RTC_WORK * wk);
static void DelMinute(D_RTC_WORK * wk);

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
	{ DT_RTC_01,		(u32)AddMonth},
	{ DT_RTC_02,		(u32)DelMonth},
	{ DT_RTC_03,		(u32)AddDay},
	{ DT_RTC_04,		(u32)DelDay},
	{ DT_RTC_05,		(u32)AddHour},
	{ DT_RTC_06,		(u32)DelHour},
	{ DT_RTC_07,		(u32)AddMinute},
	{ DT_RTC_08,		(u32)DelMinute},
	{ DT_RTC_09,		BMPLIST_CANCEL},
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
/**
 */
//--------------------------------------------------------------------------------------------
static void PutRTCInfo(D_RTC_WORK * wk, int heapID)
{
	MSGDATA_MANAGER * msgman;
	WORDSET * ws;
	STRBUF * expand;
	STRBUF * msg;

	msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_debug_rtc_dat, heapID);
	ws = WORDSET_Create(heapID);

	expand = STRBUF_Create(64, heapID);
	msg = MSGMAN_AllocString(msgman, DT_RTC_TIME);
	WORDSET_RegisterNumber(ws, 0, wk->date.month, 2, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
	WORDSET_RegisterNumber(ws, 1, wk->date.day, 2, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
	WORDSET_RegisterNumber(ws, 2, wk->time.hour, 2, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
	WORDSET_RegisterNumber(ws, 3, wk->time.minute, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
	WORDSET_RegisterNumber(ws, 4, wk->time.second, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
	WORDSET_ExpandStr(ws, expand, msg);

	GF_STR_PrintSimple(&wk->infowin, FONT_SYSTEM, expand, 0, 0, MSG_ALLPUT, NULL);
	STRBUF_Delete(msg);

	STRBUF_Delete(expand);
	WORDSET_Delete(ws);
	MSGMAN_Delete(msgman);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	RTC����v���Z�X�FBMPMENULISTDATA�̐���
 * @param	bmd		BMP_MENULIST_DATA�\���̂ւ̃|�C���^
 */
//--------------------------------------------------------------------------------------------
static	void	BMP_MENULIST_Make(BMP_MENULIST_DATA *bmd)
{
	int				i;
	MSGDATA_MANAGER	*man;

	man=MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,NARC_msg_debug_rtc_dat,HEAPID_DEBUG_TITLE);

	for(i=0;i<NELEMS(ListData);i++){
		BMP_MENULIST_AddArchiveString(bmd,man,ListData[i].strID,ListData[i].param);
	}

	MSGMAN_Delete(man);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	RTC����v���Z�X�F������
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT DebugRtcMenuProc_Init(PROC * proc, int * seq)
{
//�\�[�X�����當�����\�[�X�����O�������̂ɑΉ������o�[�W����
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_DEBUG_TITLE, 0x10000);
	{
		D_RTC_WORK * wk;

		wk = PROC_AllocWork(proc, sizeof(D_RTC_WORK), HEAPID_DEBUG_TITLE);

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
				wk->bgl, &wk->menuwin, GF_BGL_FRAME0_M, 1, 1, 14, 12, FONT_PAL_NO, 1 );

			list_h = ListHeader;
			list_h.list = wk->bmd;
			list_h.win = &wk->menuwin;
			wk->lw = BmpListSet( &list_h, 0, 0, HEAPID_DEBUG_TITLE );
		}
		{
			GF_BGL_BmpWinAdd(
				wk->bgl, &wk->infowin, GF_BGL_FRAME0_M, 1, 15, 24, 4, FONT_PAL_NO, 1 + 14 * 12);
			GF_BGL_BmpWinDataFill(&wk->infowin, FontHeaderGet(FONT_SYSTEM, FONT_HEADER_B_COLOR));
			wk->change_wait = 0;
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
 * @brief	RTC����v���Z�X�F���C��
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT DebugRtcMenuProc_Main(PROC * proc, int * seq)
{
	D_RTC_WORK * wk = PROC_GetWork(proc);
	u32	ret;

	if (wk->change_wait == 0) {
		GF_RTC_GetDateTime(&wk->date, &wk->time);
		PutRTCInfo(wk, HEAPID_DEBUG_TITLE);
		wk->change_wait = 15;
	} else {
		wk->change_wait --;
	}

	ret = BmpListMain( wk->lw );

	switch( ret ){
	case BMPLIST_NULL:
		break;
	case BMPLIST_CANCEL:
		BMP_MENULIST_Delete(wk->bmd);
		BmpListExit( wk->lw, NULL, NULL );
		GF_BGL_BmpWinOff( &wk->menuwin );
		GF_BGL_BmpWinDel( &wk->menuwin );
		GF_BGL_BmpWinOff( &wk->infowin );
		GF_BGL_BmpWinDel( &wk->infowin );
		D_TitleMenuMemFree( wk->bgl );
		sys_FreeMemoryEz( wk->bgl );
		return PROC_RES_FINISH;
	default:
		{
			CHANGE_FUNC func = (CHANGE_FUNC)ret;
			func(wk);
		}
		break;
	}
	return PROC_RES_CONTINUE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	RTC����v���Z�X�F�I���i�^�C�g���֖߂�j
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT DebugTitleRtcMenuProc_End(PROC * proc, int * seq)
{
	D_RTC_WORK * wk = PROC_GetWork(proc);

	Main_SetNextProc(FS_OVERLAY_ID(title), &TitleProcData);
	PROC_FreeWork(proc);

	sys_DeleteHeap(HEAPID_DEBUG_TITLE);
	return PROC_RES_FINISH;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	RTC����v���Z�X�F�I��
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 *
 * �t�B�[���h�֖߂�̂Ń��C���؂�ւ����ĂԕK�v���Ȃ�
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT DebugRtcMenuProc_End(PROC * proc, int * seq)
{
	PROC_FreeWork(proc);

	sys_DeleteHeap(HEAPID_DEBUG_TITLE);
	return PROC_RES_FINISH;
}



//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
const PROC_DATA DebugRtcMenuProcData = {
	DebugRtcMenuProc_Init,
	DebugRtcMenuProc_Main,
	DebugTitleRtcMenuProc_End,
	NO_OVERLAY_ID
};

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static void AddMonth(D_RTC_WORK * wk)
{
	wk->date.month ++;
	if (wk->date.month > 12) {
		wk->date.month = 1;
	}
	RTC_SetDate(&wk->date);
	wk->change_wait = 0;
}

static void DelMonth(D_RTC_WORK * wk)
{
	wk->date.month --;
	if (wk->date.month < 1) {
		wk->date.month = 12;
	}
	RTC_SetDate(&wk->date);
	wk->change_wait = 0;
}

static int GetMaxDayOfMonth(RTCDate * date)
{
	int day;
	static const u8 days[] = {
		31,28,31,30,31,30,31,31,30,31,30,31,
	};
	day = days[date->month - 1];
	if (date->month == 2 && GF_RTC_IsLeapYear(date->year)) {
		day ++;
	}
	return day;
}

static void AddDay(D_RTC_WORK * wk)
{
	wk->date.day ++;
	if (wk->date.day > GetMaxDayOfMonth(&wk->date)) {
		wk->date.day = 1;
	}
	RTC_SetDate(&wk->date);
	wk->change_wait = 0;
}

static void DelDay(D_RTC_WORK * wk)
{
	wk->date.day --;
	if (wk->date.day < 1) {
		wk->date.day = GetMaxDayOfMonth(&wk->date);
	}
	RTC_SetDate(&wk->date);
	wk->change_wait = 0;
}

static void AddHour(D_RTC_WORK * wk)
{
	wk->time.hour ++;
	if (wk->time.hour > 23) {
		wk->time.hour = 0;
	}
	RTC_SetTime(&wk->time);
	wk->change_wait = 0;
}

static void DelHour(D_RTC_WORK * wk)
{
	if (wk->time.hour == 0) {
		wk->time.hour = 23;
	} else {
		wk->time.hour --;
	}
	RTC_SetTime(&wk->time);
	wk->change_wait = 0;
}

static void AddMinute(D_RTC_WORK * wk)
{
	wk->time.minute ++;
	if (wk->time.minute > 59) {
		wk->time.minute = 0;
	}
	RTC_SetTime(&wk->time);
	wk->change_wait = 0;
}

static void DelMinute(D_RTC_WORK * wk)
{
	if (wk->time.minute == 0) {
		wk->time.minute = 59;
	} else {
		wk->time.minute --;
	}
	RTC_SetTime(&wk->time);
	wk->change_wait = 0;
}


#endif	//PM_DEBUG

