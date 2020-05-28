//============================================================================================
/**
 * @file	d_person_menu.c	
 * @brief	�f�o�b�O�l�����j���[
 * @author	Hiroyuki Nakamura
 * @date	05.07.08
 *
 * 2006.06.07	d_title.c���R�s�[���č쐬
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
#include "field/game_init.h"

#include "system/main.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_debugname.h"

#include "wifi/dwc_rap.h"
#include "wifi/dwc_test.h"

//============================================================================================
//	overlay��`
//============================================================================================

FS_EXTERN_OVERLAY( title );

//============================================================================================
//	�萔��`
//============================================================================================
typedef struct {
	GF_BGL_INI * bgl;
	GF_BGL_BMPWIN	win;
	BMPLIST_WORK * lw;
	BMP_MENULIST_DATA *bmd;
	int select_id;
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
static void SetTitleProc(SAVEDATA * savedata);

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
	//���j���[�̕�����́Aconvert/message/src/debugname.gmm�ɒǉ����Ă�������
	{ DEBUG_NAME_MASUDA, DEBUG_NAME_MASUDA },
	{ DEBUG_NAME_SUGIMORI, DEBUG_NAME_SUGIMORI },
	{ DEBUG_NAME_MORIMOTO, DEBUG_NAME_MORIMOTO },
	{ DEBUG_NAME_WATANABE, DEBUG_NAME_WATANABE },
	{ DEBUG_NAME_OHMORI, DEBUG_NAME_OHMORI },
	{ DEBUG_NAME_UNNO, DEBUG_NAME_UNNO },
	{ DEBUG_NAME_ICHINOSE, DEBUG_NAME_ICHINOSE },
	{ DEBUG_NAME_MATSUSHIMA, DEBUG_NAME_MATSUSHIMA },
	{ DEBUG_NAME_SOGABE, DEBUG_NAME_SOGABE },
	{ DEBUG_NAME_FUJIWARA, DEBUG_NAME_FUJIWARA },
	{ DEBUG_NAME_TAMADA, DEBUG_NAME_TAMADA },
	{ DEBUG_NAME_MORI, DEBUG_NAME_MORI },
	{ DEBUG_NAME_HIRONOBU, DEBUG_NAME_HIRONOBU },
	{ DEBUG_NAME_OOTA, DEBUG_NAME_OOTA },
	{ DEBUG_NAME_EO, DEBUG_NAME_EO },
	{ DEBUG_NAME_FUCHINO, DEBUG_NAME_FUCHINO },
	{ DEBUG_NAME_TOYAMA, DEBUG_NAME_TOYAMA },
	{ DEBUG_NAME_EMI, DEBUG_NAME_EMI },
	{ DEBUG_NAME_YAGI, DEBUG_NAME_YAGI },
	{ DEBUG_NAME_OOMURA, DEBUG_NAME_OOMURA },
	{ DEBUG_NAME_TOMOMICHI, DEBUG_NAME_TOMOMICHI },
	{ DEBUG_NAME_MATSUDA, DEBUG_NAME_MATSUDA },
	{ DEBUG_NAME_KAGAYA, DEBUG_NAME_KAGAYA },
	{ DEBUG_NAME_NOHARA, DEBUG_NAME_NOHARA },
	{ DEBUG_NAME_TAYA, DEBUG_NAME_TAYA },
	{ DEBUG_NAME_NAHI, DEBUG_NAME_NAHI },
	{ DEBUG_NAME_IWASAWA, DEBUG_NAME_IWASAWA },
	{ DEBUG_NAME_GOTO, DEBUG_NAME_GOTO },
	{ DEBUG_NAME_SAITO, DEBUG_NAME_SAITO },
	{ DEBUG_NAME_TOMOYA, DEBUG_NAME_TOMOYA },
	{ DEBUG_NAME_OHNO, DEBUG_NAME_OHNO },
	{ DEBUG_NAME_NISHINO, DEBUG_NAME_NISHINO },
	{ DEBUG_NAME_TETSUJI, DEBUG_NAME_TETSUJI },
	{ DEBUG_NAME_SIMOYAMADA, DEBUG_NAME_SIMOYAMADA },
	{ DEBUG_NAME_TOMISAWA, DEBUG_NAME_TOMISAWA },
	{ DEBUG_NAME_KAWACHIMARU, DEBUG_NAME_KAWACHIMARU },
	{ DEBUG_NAME_SATO, DEBUG_NAME_SATO },
	{ DEBUG_NAME_TADASHI, DEBUG_NAME_TADASHI },
	{ DEBUG_NAME_NAKATSUI, DEBUG_NAME_NAKATSUI },
	{ DEBUG_NAME_HIROKI, DEBUG_NAME_HIROKI },
	{ DEBUG_NAME_MATSUMIYA, DEBUG_NAME_MATSUMIYA },
	{ DEBUG_NAME_JOHNNY, DEBUG_NAME_JOHNNY },
	{ DEBUG_NAME_MASAFUMI, DEBUG_NAME_MASAFUMI },
	{ DEBUG_NAME_SAYA, DEBUG_NAME_SAYA },
	{ DEBUG_NAME_DIAMOND, DEBUG_NAME_DIAMOND },
	{ DEBUG_NAME_PEARL, DEBUG_NAME_PEARL },
	{ DEBUG_NAME_NGNAME, DEBUG_NAME_NGNAME },
	{ DEBUG_NAME_KAEDE,    DEBUG_NAME_KAEDE,    },
	{ DEBUG_NAME_PUKA,     DEBUG_NAME_PUKA,     },
	{ DEBUG_NAME_MASARIN,  DEBUG_NAME_MASARIN,  },
	{ DEBUG_NAME_NORIRIN,  DEBUG_NAME_NORIRIN,  },
	{ DEBUG_NAME_YOSINORI, DEBUG_NAME_YOSINORI, },
	{ DEBUG_NAME_T_1,      DEBUG_NAME_T_1,      },
	{ DEBUG_NAME_TAKAFUMI, DEBUG_NAME_TAKAFUMI, },
	{ DEBUG_NAME_TORECHEKO,DEBUG_NAME_TORECHEKO,},
	{ DEBUG_NAME_NORIHIDE, DEBUG_NAME_NORIHIDE, },
	{ DEBUG_NAME_NORISTAR, DEBUG_NAME_NORISTAR, },
	{ DEBUG_NAME_WWWWW, DEBUG_NAME_WWWWW, },

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
 * @brief	�l���I���v���Z�X�FBMPMENULISTDATA�̐���
 * @param	bmd		BMP_MENULIST_DATA�\���̂ւ̃|�C���^
 */
//--------------------------------------------------------------------------------------------
static	void	BMP_MENULIST_Make(BMP_MENULIST_DATA *bmd)
{
	int				i;
	MSGDATA_MANAGER	*man;

	man=MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,NARC_msg_debugname_dat,HEAPID_DEBUG_TITLE);

	for(i=0;i<NELEMS(ListData);i++){
		BMP_MENULIST_AddArchiveString(bmd,man,ListData[i].strID,ListData[i].param);
	}

	MSGMAN_Delete(man);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�l���I���v���Z�X�F������
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT DebugPersonMenuProc_Init(PROC * proc, int * seq)
{
//�\�[�X�����當�����\�[�X�����O�������̂ɑΉ������o�[�W����
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_DEBUG_TITLE, 0x10000);
	{
		D_TITLE_WORK * wk;
		//int id = Debug_GetMyID();

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
	}

		WIPE_ResetBrightness( WIPE_DISP_MAIN );
		WIPE_ResetBrightness( WIPE_DISP_SUB );

		GF_Disp_DispOn();

	Snd_BgmChannelSetAndReverbSet( 0 );	//�g�p�\�`�����l������A���o�[�u�ݒ�(�N���A)

	return PROC_RES_FINISH;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�l���I���v���Z�X�F���C��
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT DebugPersonMenuProc_Main(PROC * proc, int * seq)
{
	D_TITLE_WORK * wk = PROC_GetWork(proc);
	u32	ret;

	ret = BmpListMain( wk->lw );

	switch( ret ){
	case BMPLIST_NULL:
		break;
	case BMPLIST_CANCEL:
		wk->select_id = -1;
		return PROC_RES_FINISH;
	default:
		wk->select_id= ret;
		return PROC_RES_FINISH;
	}
	return PROC_RES_CONTINUE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�l���I���v���Z�X�F�I��
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT DebugPersonMenuProc_End(PROC * proc, int * seq)
{
	D_TITLE_WORK * wk = PROC_GetWork(proc);

	BMP_MENULIST_Delete(wk->bmd);
	BmpListExit( wk->lw, NULL, NULL );
	GF_BGL_BmpWinOff( &wk->win );
	GF_BGL_BmpWinDel( &wk->win );
	D_TitleMenuMemFree( wk->bgl );
	sys_FreeMemoryEz( wk->bgl );

	((MAINWORK*)PROC_GetParentWork(proc))->select_id = wk->select_id;
	if (wk->select_id != -1) {
		//�f�o�b�O�Q�[���J�n
		Main_SetNextProc(OVERLAY_ID_GAMESTART, &DebugNewGameStartProcData);
	} else {
		//�^�C�g���ɖ߂�
		Main_SetNextProc(FS_OVERLAY_ID(title), &TitleProcData);
	}
	PROC_FreeWork(proc);

	sys_DeleteHeap(HEAPID_DEBUG_TITLE);
	return PROC_RES_FINISH;
}


//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
const PROC_DATA DebugPersonMenuProcData = {
	DebugPersonMenuProc_Init,
	DebugPersonMenuProc_Main,
	DebugPersonMenuProc_End,
	NO_OVERLAY_ID
};

#endif	//PM_DEBUG

