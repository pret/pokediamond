//=============================================================================================
/**
 * @file	bg_sys.c                                                  
 * @brief	�a�f�`��V�X�e���v���O����(frame_sys �g��)
 * @author	tetsu.w
 * @date	2003/2/10
 */
//=============================================================================================
#include "system.h"
#include "standard.h"
#include "calctool.h"
#include "display.h"
#include "mmap_get.h"
#include "gflib_os_print.h"
#include "system\arc_tool.h"

#define	__BG_SYS_H_GLOBAL
#include "bg_system.h"


#define DMA_USE (1)
//=============================================================================================
//	�^�錾
//=============================================================================================
#define	GF_BGL_FRAME_MAX	(8)
#define	GF_BGL_BMPWIN_MAX	(32)
#define GF_BGL_1SCRDATASIZ	(0x2)
#define GF_BGL_1CHRDATASIZ	(0x20)
#define GF_BGL_1CHRDOTSIZ	(0x08)

#define GF_BGL_8BITCHRSIZ	(0x40)
//------------------------------------------------------------------
///�t���[���ݒ�\����
typedef	struct	{
	void*	screen_buf;	//�X�N���[���f�[�^�]���o�b�t�@�|�C���^
	u32		screen_buf_siz;
	u32		screen_buf_ofs;
	int		scroll_x;
	int		scroll_y;
//	u8		dispsite;
	u8		mode;
	u8		screen_siz;
	u8		col_mode;

	u8		base_char_size;

	u16		rad;
	fx32	scale_x;
	fx32	scale_y;
	int		cx;
	int		cy;

}GF_BGL_SYS_INI;

//------------------------------------------------------------------
///�V�X�e���ݒ�\���́i�V�X�e�����[�N�j
struct _GF_BGL_INI {
	u32		heapID;
	u16		scroll_req;		// �X�N���[�����N�G�X�g�t���O s3/s2/s1/s0_m3/m2/m1/m0
	u16		loadscrn_req;	// �X�N���[���]�����N�G�X�g�t���O s3/s2/s1/s0_m3/m2/m1/m0
	GF_BGL_SYS_INI	bgsys[GF_BGL_FRAME_MAX];
};

//------------------------------------------------------------------

// �������m�ۃ��[�h
enum {
	MS_ALLOC_WORK = 0,
	MS_ALLOC_GRAPHIC
};


//=============================================================================================
//	�v���g�^�C�v�錾
//=============================================================================================
static u8 BgScreenSizeConv( u8 type, u8 mode );
static void ScrollParamSet( GF_BGL_SYS_INI * ini, u8 mode, int value );
static void AffineScrollSetMtxFix( GF_BGL_INI * ini, u8 frmnum );
static void GF_BGL_LoadScreenSub( u8 frmnum, void* src, u32 ofs, u32 siz );
static void LoadCharacter( GF_BGL_INI* ini, u8 frmnum, const void * src, u32 datasiz, u32 offs );
static void GF_BGL_LoadCharacterSub( u8 frmnum, void* src, u32 ofs, u32 siz );
static void GF_BGL_ScrWrite_Normal(
					GF_BGL_SYS_INI * ini, u8 write_px, u8 write_py, u8 write_sx, u8 write_sy,
					u16 * buf, u8 buf_px, u8 buf_py, u8 buf_sx, u8 buf_sy ,u8 mode);
static void GF_BGL_ScrWrite_Affine(
					GF_BGL_SYS_INI * ini, u8 write_px, u8 write_py, u8 write_sx, u8 write_sy,
					u8 * buf, u8 buf_px, u8 buf_py, u8 buf_sx, u8 buf_sy ,u8 mode);
static void GF_BGL_ScrFill_Normal(
					GF_BGL_SYS_INI * ini, u16 dat, u8 px, u8 py, u8 sx, u8 sy, u8 mode );
static void GF_BGL_ScrFill_Affine(
					GF_BGL_SYS_INI * ini, u8 dat, u8 px, u8 py, u8 sx, u8 sy );

static void GF_BGL_BmpWinOn_Normal( GF_BGL_BMPWIN * win );
static void GF_BGL_BmpWinOnVReq_Normal( GF_BGL_BMPWIN * win );
static void GF_BGL_BmpWinOn_Affine( GF_BGL_BMPWIN * win );
static void GF_BGL_BmpWinOnVReq_Affine( GF_BGL_BMPWIN * win );
static void GF_BGL_BmpWinOff_Normal( GF_BGL_BMPWIN * win );
static void GF_BGL_BmpWinOffVReq_Normal( GF_BGL_BMPWIN * win );
static void GF_BGL_BmpWinOff_Affine( GF_BGL_BMPWIN * win );
static void GF_BGL_BmpWinOffVReq_Affine( GF_BGL_BMPWIN * win );
static void GF_BGL_BmpWinShift16( GF_BGL_BMPWIN * win, u8 direct, u8 offset, u8 data );
static void GF_BGL_BmpWinShift256( GF_BGL_BMPWIN * win, u8 direct, u8 offset, u8 data );

static void CgxFlipCheck( GF_BGL_INI* ini, u8 flip, u8 * buf );

static void MakeWinScrnText( GF_BGL_BMPWIN* win );
static void MakeWinScrnAffine( GF_BGL_BMPWIN* win );
static void ClearWinScrnText( GF_BGL_BMPWIN* win );
static void ClearWinScrnAffine( GF_BGL_BMPWIN* win );

static void RadianParamSet( GF_BGL_SYS_INI * ini, u8 mode, u16 value );
static void ScaleParamSet( GF_BGL_SYS_INI * ini, u8 mode, fx32 value );
static void CenterParamSet( GF_BGL_SYS_INI * ini, u8 mode, int value );


//=============================================================================================
//=============================================================================================
//	�ݒ�֐�
//=============================================================================================
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �V�X�e�����[�N�G���A�擾
 *
 * @param	heapID	�q�[�v�h�c
 *
 * @return	�擾�����������̃A�h���X
 */
//--------------------------------------------------------------------------------------------
GF_BGL_INI*  GF_BGL_BglIniAlloc( u32 heapID )
{
	GF_BGL_INI* wk = sys_AllocMemory( heapID, sizeof(GF_BGL_INI) );

	memset( wk, 0, sizeof(GF_BGL_INI) );
	wk->heapID = heapID;
	wk->scroll_req = 0;
	wk->loadscrn_req = 0;

	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �q�[�vID�擾
 *
 * @param	ini		BGL�f�[�^
 *
 * @return	BGL�̃q�[�vID
 */
//--------------------------------------------------------------------------------------------
u32	GF_BGL_HeapIDGet( GF_BGL_INI * ini )
{
	return ini->heapID;
}

//--------------------------------------------------------------------------------------------
/**
 * �a�f���[�h�ݒ�
 *
 * @param	data	�a�f���[�h�ݒ�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void	GF_BGL_InitBG( const GF_BGL_SYS_HEADER* data )
{
    GX_SetGraphicsMode( data->dispMode, data->bgMode, data->bg0_2Dor3D );
    GXS_SetGraphicsMode( data->bgModeSub );

	GX_SetBGScrOffset(GX_BGSCROFFSET_0x00000); 
	GX_SetBGCharOffset(GX_BGCHAROFFSET_0x00000); 

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
}

//--------------------------------------------------------------------------------------------
/**
 * �a�f���[�h�ݒ�i��ʂ��Ɓj
 *
 * @param	data	�a�f���[�h�ݒ�f�[�^
 * @param	flg		�ݒ肷����
 *
 * @return	none
 *
 * @li	flg = GF_BGL_MAIN_DISP : ���C�����
 * @li	flg = GF_BGL_SUB_DISP : �T�u���
 */
//--------------------------------------------------------------------------------------------
void	GF_BGL_InitBGDisp( const GF_BGL_SYS_HEADER * data, u8 flg )
{
	if( flg == GF_BGL_MAIN_DISP ){
		GX_SetGraphicsMode( data->dispMode, data->bgMode, data->bg0_2Dor3D );
		GF_Disp_GX_VisibleControlInit();
	}else{
		GXS_SetGraphicsMode( data->bgModeSub );
		GF_Disp_GXS_VisibleControlInit();
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �a�f�ʐݒ�
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		�a�f�t���[���ԍ�
 * @param	data		�a�f�R���g���[���f�[�^
 * @param	mode		�a�f���[�h
 * 
 * @return	none
 *
 * @li	mode = GF_BGL_MODE_TEXT		: �e�L�X�g
 * @li	mode = GF_BGL_MODE_AFFINE	: �A�t�B��
 * @li	mode = GF_BGL_MODE_256X16	: �A�t�B���g��BG
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BGControlSet( GF_BGL_INI * ini, u8 frmnum, const GF_BGL_BGCNT_HEADER* data, u8 mode )
{
	u8	screen_size = BgScreenSizeConv( data->screenSize, mode );

	switch( frmnum ){
	case GF_BGL_FRAME0_M:
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
		G2_SetBG0Control(
				(GXBGScrSizeText)screen_size, 
				(GXBGColorMode)data->colorMode,
				(GXBGScrBase)data->screenBase,
				(GXBGCharBase)data->charBase,
				(GXBGExtPltt)data->bgExtPltt);
		G2_SetBG0Priority( (int)data->priority );
		G2_BG0Mosaic( (BOOL)data->mosaic );
		break;

	case GF_BGL_FRAME1_M:
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
		G2_SetBG1Control(
				(GXBGScrSizeText)screen_size, 
				(GXBGColorMode)data->colorMode,
				(GXBGScrBase)data->screenBase,
				(GXBGCharBase)data->charBase,
				(GXBGExtPltt)data->bgExtPltt);
		G2_SetBG1Priority( (int)data->priority );
		G2_BG1Mosaic( (BOOL)data->mosaic );
		break;

	case GF_BGL_FRAME2_M:
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		switch( mode ){
		default:
		case GF_BGL_MODE_TEXT:
			G2_SetBG2ControlText(
					(GXBGScrSizeText)screen_size, 
					(GXBGColorMode)data->colorMode,
					(GXBGScrBase)data->screenBase,
					(GXBGCharBase)data->charBase);
			break;
		case GF_BGL_MODE_AFFINE:
			G2_SetBG2ControlAffine(
					(GXBGScrSizeAffine)screen_size, 
					(GXBGAreaOver)data->areaOver,
					(GXBGScrBase)data->screenBase,
					(GXBGCharBase)data->charBase );
			break;
		case GF_BGL_MODE_256X16:
			G2_SetBG2Control256x16Pltt(
					(GXBGScrSize256x16Pltt)screen_size, 
					(GXBGAreaOver)data->areaOver,
					(GXBGScrBase)data->screenBase,
					(GXBGCharBase)data->charBase );
			break;
		}
		G2_SetBG2Priority( (int)data->priority );
		G2_BG2Mosaic( (BOOL)data->mosaic );
		break;

	case GF_BGL_FRAME3_M:
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
		switch( mode ){
		default:
		case GF_BGL_MODE_TEXT:
			G2_SetBG3ControlText(
					(GXBGScrSizeText)screen_size, 
					(GXBGColorMode)data->colorMode,
					(GXBGScrBase)data->screenBase,
					(GXBGCharBase)data->charBase);
			break;
		case GF_BGL_MODE_AFFINE:
			G2_SetBG3ControlAffine(
					(GXBGScrSizeAffine)screen_size, 
					(GXBGAreaOver)data->areaOver,
					(GXBGScrBase)data->screenBase,
					(GXBGCharBase)data->charBase );
			break;
		case GF_BGL_MODE_256X16:
			G2_SetBG3Control256x16Pltt(
					(GXBGScrSize256x16Pltt)screen_size, 
					(GXBGAreaOver)data->areaOver,
					(GXBGScrBase)data->screenBase,
					(GXBGCharBase)data->charBase );
			break;
		}
		G2_SetBG3Priority( (int)data->priority );
		G2_BG3Mosaic( (BOOL)data->mosaic );
		break;

	case GF_BGL_FRAME0_S:
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
		G2S_SetBG0Control(
				(GXBGScrSizeText)screen_size, 
				(GXBGColorMode)data->colorMode,
				(GXBGScrBase)data->screenBase,
				(GXBGCharBase)data->charBase,
				(GXBGExtPltt)data->bgExtPltt);
		G2S_SetBG0Priority( (int)data->priority );
		G2S_BG0Mosaic( (BOOL)data->mosaic );
		break;

	case GF_BGL_FRAME1_S:
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
		G2S_SetBG1Control(
				(GXBGScrSizeText)screen_size, 
				(GXBGColorMode)data->colorMode,
				(GXBGScrBase)data->screenBase,
				(GXBGCharBase)data->charBase,
				(GXBGExtPltt)data->bgExtPltt);
		G2S_SetBG1Priority( (int)data->priority );
		G2S_BG1Mosaic( (BOOL)data->mosaic );
		break;

	case GF_BGL_FRAME2_S:
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		switch( mode ){
		default:
		case GF_BGL_MODE_TEXT:
			G2S_SetBG2ControlText(
					(GXBGScrSizeText)screen_size, 
					(GXBGColorMode)data->colorMode,
					(GXBGScrBase)data->screenBase,
					(GXBGCharBase)data->charBase);
			break;
		case GF_BGL_MODE_AFFINE:
			G2S_SetBG2ControlAffine(
					(GXBGScrSizeAffine)screen_size, 
					(GXBGAreaOver)data->areaOver,
					(GXBGScrBase)data->screenBase,
					(GXBGCharBase)data->charBase );
			break;
		case GF_BGL_MODE_256X16:
			G2S_SetBG2Control256x16Pltt(
					(GXBGScrSize256x16Pltt)screen_size, 
					(GXBGAreaOver)data->areaOver,
					(GXBGScrBase)data->screenBase,
					(GXBGCharBase)data->charBase );
			break;
		}
		G2S_SetBG2Priority( (int)data->priority );
		G2S_BG2Mosaic( (BOOL)data->mosaic );
		break;

	case GF_BGL_FRAME3_S:
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
		switch( mode ){
		default:
		case GF_BGL_MODE_TEXT:
			G2S_SetBG3ControlText(
					(GXBGScrSizeText)screen_size, 
					(GXBGColorMode)data->colorMode,
					(GXBGScrBase)data->screenBase,
					(GXBGCharBase)data->charBase);
			break;
		case GF_BGL_MODE_AFFINE:
			G2S_SetBG3ControlAffine(
					(GXBGScrSizeAffine)screen_size, 
					(GXBGAreaOver)data->areaOver,
					(GXBGScrBase)data->screenBase,
					(GXBGCharBase)data->charBase );
			break;
		case GF_BGL_MODE_256X16:
			G2S_SetBG3Control256x16Pltt(
					(GXBGScrSize256x16Pltt)screen_size, 
					(GXBGAreaOver)data->areaOver,
					(GXBGScrBase)data->screenBase,
					(GXBGCharBase)data->charBase );
			break;
		}
		G2S_SetBG3Priority( (int)data->priority );
		G2S_BG3Mosaic( (BOOL)data->mosaic );
		break;
	}

	ini->bgsys[frmnum].rad     = 0;
	ini->bgsys[frmnum].scale_x = FX32_ONE;
	ini->bgsys[frmnum].scale_y = FX32_ONE;
	ini->bgsys[frmnum].cx      = 0;
	ini->bgsys[frmnum].cy      = 0;

	if( data->scrbufferSiz ){
		ini->bgsys[frmnum].screen_buf = sys_AllocMemory( ini->heapID, data->scrbufferSiz );

#ifdef	OSP_ERR_BGL_SCRBUF_GET		// �X�N���[���o�b�t�@�m�ێ��s
		if( ini->bgsys[frmnum].screen_buf == NULL ){
			OS_Printf("�̈�m�ێ��s\n");
		}
#endif	// OSP_ERR_BGL_SCRBUF_GET

		MI_CpuClear16( ini->bgsys[frmnum].screen_buf, data->scrbufferSiz );
		ini->bgsys[frmnum].screen_buf_siz = data->scrbufferSiz;
		ini->bgsys[frmnum].screen_buf_ofs = data->scrbufferOfs;
#ifdef	OSP_BGL_SCRBUF_GET_SIZ		// �m�ۂ����X�N���[���o�b�t�@�̃T�C�Y
		OS_Printf("�r�b�q�̈�=%x\n",ini->bgsys[frmnum].screen_buf);
#endif	// OSP_BGL_SCRBUF_GET_SIZ
	}else{
		ini->bgsys[frmnum].screen_buf = NULL;
		ini->bgsys[frmnum].screen_buf_siz = 0;
		ini->bgsys[frmnum].screen_buf_ofs = 0;
	}
	ini->bgsys[frmnum].screen_siz = data->screenSize;
	ini->bgsys[frmnum].mode = mode;
	ini->bgsys[frmnum].col_mode = data->colorMode;

	if(mode == GF_BGL_MODE_TEXT && data->colorMode == GX_BG_COLORMODE_16){
		ini->bgsys[frmnum].base_char_size = GF_BGL_1CHRDATASIZ;
	}else{
		ini->bgsys[frmnum].base_char_size = GF_BGL_8BITCHRSIZ;
	}

	GF_BGL_ScrollSet( ini, frmnum, GF_BGL_SCROLL_X_SET, data->scrollX );
	GF_BGL_ScrollSet( ini, frmnum, GF_BGL_SCROLL_Y_SET, data->scrollY );
}

//--------------------------------------------------------------------------------------------
/**
 * �a�f�Ėʐݒ�
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		�a�f�t���[���ԍ�
 * @param	flg			�ύX�p�����[�^
 * @param	prm			�ύX�l
 * 
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BGControlReset( GF_BGL_INI * ini, u8 frm, u8 flg, u8 prm )
{
	if( flg == BGL_RESET_COLOR ){
		ini->bgsys[frm].col_mode = prm;
	}

	switch( frm ){
	case GF_BGL_FRAME0_M:
		{
			GXBg01Control	dat = G2_GetBG0Control();
			if( flg == BGL_RESET_SCRBASE ){
				dat.screenBase = prm;
			}else if( flg == BGL_RESET_CHRBASE ){
				dat.charBase = prm;
			}
			G2_SetBG0Control(
				(GXBGScrSizeText)dat.screenSize, 
				(GXBGColorMode)ini->bgsys[frm].col_mode,
				(GXBGScrBase)dat.screenBase,
				(GXBGCharBase)dat.charBase,
				(GXBGExtPltt)dat.bgExtPltt );
		}
		break;

	case GF_BGL_FRAME1_M:
		{
			GXBg01Control	dat = G2_GetBG1Control();
			if( flg == BGL_RESET_SCRBASE ){
				dat.screenBase = prm;
			}else if( flg == BGL_RESET_CHRBASE ){
				dat.charBase = prm;
			}
			G2_SetBG1Control(
				(GXBGScrSizeText)dat.screenSize, 
				(GXBGColorMode)ini->bgsys[frm].col_mode,
				(GXBGScrBase)dat.screenBase,
				(GXBGCharBase)dat.charBase,
				(GXBGExtPltt)dat.bgExtPltt );
		}
		break;

	case GF_BGL_FRAME2_M:
		switch( ini->bgsys[frm].mode ){
		default:
		case GF_BGL_MODE_TEXT:
			{
				GXBg23ControlText	dat = G2_GetBG2ControlText();
				if( flg == BGL_RESET_SCRBASE ){
					dat.screenBase = prm;
				}else if( flg == BGL_RESET_CHRBASE ){
					dat.charBase = prm;
				}
				G2_SetBG2ControlText(
					(GXBGScrSizeText)dat.screenSize,
					(GXBGColorMode)ini->bgsys[frm].col_mode,
					(GXBGScrBase)dat.screenBase,
					(GXBGCharBase)dat.charBase );
			}
			break;
		case GF_BGL_MODE_AFFINE:
			{
				GXBg23ControlAffine	dat = G2_GetBG2ControlAffine();
				if( flg == BGL_RESET_SCRBASE ){
					dat.screenBase = prm;
				}else if( flg == BGL_RESET_CHRBASE ){
					dat.charBase = prm;
				}
				G2_SetBG2ControlAffine(
					(GXBGScrSizeText)dat.screenSize,
					(GXBGAreaOver)dat.areaOver,
					(GXBGScrBase)dat.screenBase,
					(GXBGCharBase)dat.charBase );
			}
			break;
		case GF_BGL_MODE_256X16:
			{
				GXBg23Control256x16Pltt	dat = G2_GetBG2Control256x16Pltt();
				if( flg == BGL_RESET_SCRBASE ){
					dat.screenBase = prm;
				}else if( flg == BGL_RESET_CHRBASE ){
					dat.charBase = prm;
				}
				G2_SetBG2Control256x16Pltt(
					(GXBGScrSizeText)dat.screenSize,
					(GXBGAreaOver)dat.areaOver,
					(GXBGScrBase)dat.screenBase,
					(GXBGCharBase)dat.charBase );
			}
			break;
		}
		break;

	case GF_BGL_FRAME3_M:
		switch( ini->bgsys[frm].mode ){
		default:
		case GF_BGL_MODE_TEXT:
			{
				GXBg23ControlText	dat = G2_GetBG3ControlText();
				if( flg == BGL_RESET_SCRBASE ){
					dat.screenBase = prm;
				}else if( flg == BGL_RESET_CHRBASE ){
					dat.charBase = prm;
				}
				G2_SetBG3ControlText(
					(GXBGScrSizeText)dat.screenSize,
					(GXBGColorMode)ini->bgsys[frm].col_mode,
					(GXBGScrBase)dat.screenBase,
					(GXBGCharBase)dat.charBase );
			}
			break;
		case GF_BGL_MODE_AFFINE:
			{
				GXBg23ControlAffine	dat = G2_GetBG3ControlAffine();
				if( flg == BGL_RESET_SCRBASE ){
					dat.screenBase = prm;
				}else if( flg == BGL_RESET_CHRBASE ){
					dat.charBase = prm;
				}
				G2_SetBG3ControlAffine(
					(GXBGScrSizeText)dat.screenSize,
					(GXBGAreaOver)dat.areaOver,
					(GXBGScrBase)dat.screenBase,
					(GXBGCharBase)dat.charBase );
			}
			break;
		case GF_BGL_MODE_256X16:
			{
				GXBg23Control256x16Pltt	dat = G2_GetBG3Control256x16Pltt();
				if( flg == BGL_RESET_SCRBASE ){
					dat.screenBase = prm;
				}else if( flg == BGL_RESET_CHRBASE ){
					dat.charBase = prm;
				}
				G2_SetBG3Control256x16Pltt(
					(GXBGScrSizeText)dat.screenSize,
					(GXBGAreaOver)dat.areaOver,
					(GXBGScrBase)dat.screenBase,
					(GXBGCharBase)dat.charBase );
			}
			break;
		}
		break;

	case GF_BGL_FRAME0_S:
		{
			GXBg01Control	dat = G2S_GetBG0Control();
			if( flg == BGL_RESET_SCRBASE ){
				dat.screenBase = prm;
			}else if( flg == BGL_RESET_CHRBASE ){
				dat.charBase = prm;
			}
			G2S_SetBG0Control(
				(GXBGScrSizeText)dat.screenSize, 
				(GXBGColorMode)ini->bgsys[frm].col_mode,
				(GXBGScrBase)dat.screenBase,
				(GXBGCharBase)dat.charBase,
				(GXBGExtPltt)dat.bgExtPltt );
		}
		break;

	case GF_BGL_FRAME1_S:
		{
			GXBg01Control	dat = G2S_GetBG1Control();
			if( flg == BGL_RESET_SCRBASE ){
				dat.screenBase = prm;
			}else if( flg == BGL_RESET_CHRBASE ){
				dat.charBase = prm;
			}
			G2S_SetBG1Control(
				(GXBGScrSizeText)dat.screenSize, 
				(GXBGColorMode)ini->bgsys[frm].col_mode,
				(GXBGScrBase)dat.screenBase,
				(GXBGCharBase)dat.charBase,
				(GXBGExtPltt)dat.bgExtPltt );
		}
		break;

	case GF_BGL_FRAME2_S:
		switch( ini->bgsys[frm].mode ){
		default:
		case GF_BGL_MODE_TEXT:
			{
				GXBg23ControlText	dat = G2S_GetBG2ControlText();
				if( flg == BGL_RESET_SCRBASE ){
					dat.screenBase = prm;
				}else if( flg == BGL_RESET_CHRBASE ){
					dat.charBase = prm;
				}
				G2S_SetBG2ControlText(
					(GXBGScrSizeText)dat.screenSize,
					(GXBGColorMode)ini->bgsys[frm].col_mode,
					(GXBGScrBase)dat.screenBase,
					(GXBGCharBase)dat.charBase );
			}
			break;
		case GF_BGL_MODE_AFFINE:
			{
				GXBg23ControlAffine	dat = G2S_GetBG2ControlAffine();
				if( flg == BGL_RESET_SCRBASE ){
					dat.screenBase = prm;
				}else if( flg == BGL_RESET_CHRBASE ){
					dat.charBase = prm;
				}
				G2S_SetBG2ControlAffine(
					(GXBGScrSizeText)dat.screenSize,
					(GXBGAreaOver)dat.areaOver,
					(GXBGScrBase)dat.screenBase,
					(GXBGCharBase)dat.charBase );
			}
			break;
		case GF_BGL_MODE_256X16:
			{
				GXBg23Control256x16Pltt	dat = G2S_GetBG2Control256x16Pltt();
				if( flg == BGL_RESET_SCRBASE ){
					dat.screenBase = prm;
				}else if( flg == BGL_RESET_CHRBASE ){
					dat.charBase = prm;
				}
				G2S_SetBG2Control256x16Pltt(
					(GXBGScrSizeText)dat.screenSize,
					(GXBGAreaOver)dat.areaOver,
					(GXBGScrBase)dat.screenBase,
					(GXBGCharBase)dat.charBase );
			}
			break;
		}
		break;

	case GF_BGL_FRAME3_S:
		switch( ini->bgsys[frm].mode ){
		default:
		case GF_BGL_MODE_TEXT:
			{
				GXBg23ControlText	dat = G2S_GetBG3ControlText();
				if( flg == BGL_RESET_SCRBASE ){
					dat.screenBase = prm;
				}else if( flg == BGL_RESET_CHRBASE ){
					dat.charBase = prm;
				}
				G2S_SetBG3ControlText(
					(GXBGScrSizeText)dat.screenSize,
					(GXBGColorMode)ini->bgsys[frm].col_mode,
					(GXBGScrBase)dat.screenBase,
					(GXBGCharBase)dat.charBase );
			}
			break;
		case GF_BGL_MODE_AFFINE:
			{
				GXBg23ControlAffine	dat = G2S_GetBG3ControlAffine();
				if( flg == BGL_RESET_SCRBASE ){
					dat.screenBase = prm;
				}else if( flg == BGL_RESET_CHRBASE ){
					dat.charBase = prm;
				}
				G2S_SetBG3ControlAffine(
					(GXBGScrSizeText)dat.screenSize,
					(GXBGAreaOver)dat.areaOver,
					(GXBGScrBase)dat.screenBase,
					(GXBGCharBase)dat.charBase );
			}
			break;
		case GF_BGL_MODE_256X16:
			{
				GXBg23Control256x16Pltt	dat = G2S_GetBG3Control256x16Pltt();
				if( flg == BGL_RESET_SCRBASE ){
					dat.screenBase = prm;
				}else if( flg == BGL_RESET_CHRBASE ){
					dat.charBase = prm;
				}
				G2S_SetBG3Control256x16Pltt(
					(GXBGScrSizeText)dat.screenSize,
					(GXBGAreaOver)dat.areaOver,
					(GXBGScrBase)dat.screenBase,
					(GXBGCharBase)dat.charBase );
			}
			break;
		}
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���T�C�Y�ϊ� ( GFLIB -> NitroSDK )
 *
 * @param	type	�X�N���[���T�C�Y ( GFLIB )
 * @param	mode	�a�f���[�h
 *
 * @return	�X�N���[���T�C�Y ( NitroSDK )
 */
//--------------------------------------------------------------------------------------------
static u8 BgScreenSizeConv( u8 type, u8 mode )
{
	switch( mode ){
	case GF_BGL_MODE_TEXT:		// �e�L�X�g
		if( type == GF_BGL_SCRSIZ_256x256 ){ return GX_BG_SCRSIZE_TEXT_256x256; }
		if( type == GF_BGL_SCRSIZ_256x512 ){ return GX_BG_SCRSIZE_TEXT_256x512; }
		if( type == GF_BGL_SCRSIZ_512x256 ){ return GX_BG_SCRSIZE_TEXT_512x256; }
		if( type == GF_BGL_SCRSIZ_512x512 ){ return GX_BG_SCRSIZE_TEXT_512x512; }
		break;
	case GF_BGL_MODE_AFFINE:	// �A�t�B��
		if( type == GF_BGL_SCRSIZ_128x128 ){ return GX_BG_SCRSIZE_AFFINE_128x128; }
		if( type == GF_BGL_SCRSIZ_256x256 ){ return GX_BG_SCRSIZE_AFFINE_256x256; }
		if( type == GF_BGL_SCRSIZ_512x512 ){ return GX_BG_SCRSIZE_AFFINE_512x512; }
		if( type == GF_BGL_SCRSIZ_1024x1024 ){ return GX_BG_SCRSIZE_AFFINE_1024x1024; }
		break;
	case GF_BGL_MODE_256X16:	// �A�t�B���g��BG
		if( type == GF_BGL_SCRSIZ_128x128 ){ return GX_BG_SCRSIZE_256x16PLTT_128x128; }
		if( type == GF_BGL_SCRSIZ_256x256 ){ return GX_BG_SCRSIZE_256x16PLTT_256x256; }
		if( type == GF_BGL_SCRSIZ_512x512 ){ return GX_BG_SCRSIZE_256x16PLTT_512x512; }
		if( type == GF_BGL_SCRSIZ_1024x1024 ){ return GX_BG_SCRSIZE_256x16PLTT_1024x1024; }
		break;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �L�����P�ʂ̃X�N���[���T�C�Y�擾
 *
 * @param	type	�X�N���[���T�C�Y ( GFLIB )
 * @param	x		X�����̃T�C�Y�i�[�ꏊ
 * @param	y		Y�����̃T�C�Y�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgScreenSizeGet( u8 type, u8 * x, u8 * y )
{
	switch( type ){
	case GF_BGL_SCRSIZ_128x128:
		*x = 16;
		*y = 16;
		return;
	case GF_BGL_SCRSIZ_256x256:
		*x = 32;
		*y = 32;
		return;
	case GF_BGL_SCRSIZ_256x512:
		*x = 32;
		*y = 64;
		return;
	case GF_BGL_SCRSIZ_512x256:
		*x = 64;
		*y = 32;
		return;
	case GF_BGL_SCRSIZ_512x512:
		*x = 64;
		*y = 64;
		return;
	case GF_BGL_SCRSIZ_1024x1024:
		*x = 128;
		*y = 128;
		return;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * GF_BGL_BGControlSet�Ŏ擾�������������J��
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[��
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BGControlExit( GF_BGL_INI * ini, u8 frmnum )
{
	if( ini->bgsys[frmnum].screen_buf == NULL ){
		return;
	}
	sys_FreeMemoryEz( ini->bgsys[frmnum].screen_buf );
	ini->bgsys[frmnum].screen_buf = NULL;
}

//--------------------------------------------------------------------------------------------
/**
 * �\���v���C�I���e�B�ݒ�
 *
 * @param	frmnum		BG�t���[���ԍ�
 * @param	priority	�v���C�I���e�B
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_PrioritySet( u8 frmnum, u8 priority )
{
	switch( frmnum ){
	case GF_BGL_FRAME0_M:
		G2_SetBG0Priority( priority );
		break;
	case GF_BGL_FRAME1_M:
		G2_SetBG1Priority( priority );
		break;
	case GF_BGL_FRAME2_M:
		G2_SetBG2Priority( priority );
		break;
	case GF_BGL_FRAME3_M:
		G2_SetBG3Priority( priority );
		break;
	case GF_BGL_FRAME0_S:
		G2S_SetBG0Priority( priority );
		break;
	case GF_BGL_FRAME1_S:
		G2S_SetBG1Priority( priority );
		break;
	case GF_BGL_FRAME2_S:
		G2S_SetBG2Priority( priority );
		break;
	case GF_BGL_FRAME3_S:
		G2S_SetBG3Priority( priority );
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �\��ON�EOFF�ݒ�
 *
 * @param	frmnum		BG�t���[���ԍ�
 * @param	visible		VISIBLE_ON or VISIBLE_OFF
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_VisibleSet( u8 frmnum, u8 visible )
{
	switch( frmnum ){
	case GF_BGL_FRAME0_M:
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, visible );
		break;
	case GF_BGL_FRAME1_M:
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, visible );
		break;
	case GF_BGL_FRAME2_M:
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, visible );
		break;
	case GF_BGL_FRAME3_M:
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, visible );
		break;
	case GF_BGL_FRAME0_S:
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, visible );
		break;
	case GF_BGL_FRAME1_S:
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, visible );
		break;
	case GF_BGL_FRAME2_S:
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2, visible );
		break;
	case GF_BGL_FRAME3_S:
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG3, visible );
		break;
	}
}


//=============================================================================================
//=============================================================================================
//	�X�N���[���֐�
//=============================================================================================
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �X�N���[������
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���ԍ�
 * @param	mode		�X�N���[�����[�h
 * @param	value		�X�N���[���l
 *
 * @return	none
 *
 * @li	�g�k�ʂ��g�k�E��]����ꍇ��GF_BGL_AffineScrollSet(...)���g�p���邱��
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_ScrollSet( GF_BGL_INI * ini, u8 frmnum, u8 mode, int value )
{
	int		scroll_x, scroll_y;

	ScrollParamSet( &ini->bgsys[frmnum], mode, value );

	scroll_x = ini->bgsys[frmnum].scroll_x;
	scroll_y = ini->bgsys[frmnum].scroll_y;

	switch( frmnum ){
	case GF_BGL_FRAME0_M:
		G2_SetBG0Offset( scroll_x, scroll_y );
		return;
	case GF_BGL_FRAME1_M:
		G2_SetBG1Offset( scroll_x, scroll_y );
		return;
	case GF_BGL_FRAME2_M:
		if( ini->bgsys[GF_BGL_FRAME2_M].mode == GF_BGL_MODE_TEXT ){
			G2_SetBG2Offset( scroll_x, scroll_y );
		}else{
			AffineScrollSetMtxFix( ini, GF_BGL_FRAME2_M );
		}
		return;
	case GF_BGL_FRAME3_M:
		if( ini->bgsys[GF_BGL_FRAME3_M].mode == GF_BGL_MODE_TEXT ){
			G2_SetBG3Offset( scroll_x, scroll_y );
		}else{
			AffineScrollSetMtxFix( ini, GF_BGL_FRAME3_M );
		}
		return;
	case GF_BGL_FRAME0_S:
		G2S_SetBG0Offset( scroll_x, scroll_y );
		return;
	case GF_BGL_FRAME1_S:
		G2S_SetBG1Offset( scroll_x, scroll_y );
		return;
	case GF_BGL_FRAME2_S:
		if( ini->bgsys[GF_BGL_FRAME2_S].mode == GF_BGL_MODE_TEXT ){
			G2S_SetBG2Offset( scroll_x, scroll_y );
		}else{
			AffineScrollSetMtxFix( ini, GF_BGL_FRAME2_S );
		}
		return;
	case GF_BGL_FRAME3_S:
		if( ini->bgsys[GF_BGL_FRAME3_S].mode == GF_BGL_MODE_TEXT ){
			G2S_SetBG3Offset( scroll_x, scroll_y );
		}else{
			AffineScrollSetMtxFix( ini, GF_BGL_FRAME3_S );
		}
		return;
	}
}
//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���l�w�擾
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���ԍ�
 *
 * @return	int			�X�N���[���l�w
 */
//--------------------------------------------------------------------------------------------
int GF_BGL_ScrollGetX( GF_BGL_INI * ini, u32 frmnum )
{
	return ini->bgsys[frmnum].scroll_x;
}
//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���l�x�擾
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���ԍ�
 *
 * @return	int			�X�N���[���l�x
 */
//--------------------------------------------------------------------------------------------
int GF_BGL_ScrollGetY( GF_BGL_INI * ini, u32 frmnum )
{
	return ini->bgsys[frmnum].scroll_y;
}

//--------------------------------------------------------------------------------------------
/**
 * �g�k�ʂ̊g�k�E��]�E�X�N���[������
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���ԍ�
 * @param	mode		�X�N���[�����[�h
 * @param	value		�X�N���[���l
 * @param	mtx			�ϊ��s��
 * @param	cx			��]���SX���W
 * @param	cy			��]���SY���W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_AffineScrollSet(
		GF_BGL_INI * ini, u8 frmnum, u8 mode, int value, const MtxFx22 * mtx, int cx, int cy )
{
	ScrollParamSet( &ini->bgsys[frmnum], mode, value );
	GF_BGL_AffineSet( ini, frmnum, mtx, cx, cy );
}

//--------------------------------------------------------------------------------------------
/**
 * �p�����[�^�Z�b�g
 * @param	frmnum		BG�t���[���ԍ�
 * @param	mode		�X�N���[�����[�h
 * @param	value		�X�N���[���l
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ScrollParamSet( GF_BGL_SYS_INI * ini, u8 mode, int value )
{
	switch(mode){
	case GF_BGL_SCROLL_X_SET:
		ini->scroll_x = value;
		break;
	case GF_BGL_SCROLL_X_INC:
		ini->scroll_x += value;
		break;
	case GF_BGL_SCROLL_X_DEC:
		ini->scroll_x -= value;
		break;
	case GF_BGL_SCROLL_Y_SET:
		ini->scroll_y = value;
		break;
	case GF_BGL_SCROLL_Y_INC:
		ini->scroll_y += value;
		break;
	case GF_BGL_SCROLL_Y_DEC:
		ini->scroll_y -= value;
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �g�k�E��]����
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���ԍ�
 * @param	mtx			�ϊ��s��
 * @param	cx			��]���SX���W
 * @param	cy			��]���SY���W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_AffineSet( GF_BGL_INI * ini, u8 frmnum, const MtxFx22 * mtx, int cx, int cy )
{
	switch( frmnum ){
	case GF_BGL_FRAME2_M:
		G2_SetBG2Affine(
			mtx, cx, cy, ini->bgsys[frmnum].scroll_x, ini->bgsys[frmnum].scroll_y );
		return;
	case GF_BGL_FRAME3_M:
		G2_SetBG3Affine(
			mtx, cx, cy, ini->bgsys[frmnum].scroll_x, ini->bgsys[frmnum].scroll_y );
		return;
	case GF_BGL_FRAME2_S:
		G2S_SetBG2Affine(
			mtx, cx, cy, ini->bgsys[frmnum].scroll_x, ini->bgsys[frmnum].scroll_y );
		return;
	case GF_BGL_FRAME3_S:
		G2S_SetBG3Affine(
			mtx, cx, cy, ini->bgsys[frmnum].scroll_x, ini->bgsys[frmnum].scroll_y );
		return;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �g�k�ʂ̃X�N���[�������i�g�k�E��]���Ă��Ȃ��ꍇ�̏����j
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���ԍ�
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void AffineScrollSetMtxFix( GF_BGL_INI * ini, u8 frmnum )
{
	MtxFx22	mtx;

	OS_TPrintf("[AFSCMTX]  frm:%d\n", frmnum);

	AffineMtxMake_2D( &mtx, 0, FX32_ONE, FX32_ONE, AFFINE_MAX_NORMAL );
	GF_BGL_AffineSet( ini, frmnum, &mtx, 0, 0 );
}


//=============================================================================================
//=============================================================================================
//	�W�J�֐�
//=============================================================================================
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�W�J
 *
 * @param	src			�W�J��
 * @param	dst			�W�J��
 * @param	datasiz		�T�C�Y
 *
 * @return	none
 *
 * @li	datasiz = GF_BGL_DATA_LZH : ���k�f�[�^
 */
//--------------------------------------------------------------------------------------------
void	GF_BGL_DataDecord( const void* src, void* dst, u32 datasiz )
{
	if( datasiz == GF_BGL_DATA_LZH ){
		MI_UncompressLZ8( src, dst);
	}else{
		if((!((u32)src % 4))&&(!((u32)dst % 4))&&(!((u16)datasiz % 4))){
			MI_CpuCopy32( src, dst, datasiz );
			//MI_CpuCopyFast( src, dst, datasiz );
		}else{
			MI_CpuCopy16( src, dst, datasiz );
		}
	}
}


//=============================================================================================
//=============================================================================================
//	�]���֐�
//=============================================================================================
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �t���[���ɐݒ肳�ꂽ�X�N���[���f�[�^��S�]��
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���ԍ�
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_LoadScreenReq( GF_BGL_INI * ini, u8 frmnum )
{
	GF_BGL_LoadScreen(
		ini, frmnum, ini->bgsys[frmnum].screen_buf,
		ini->bgsys[frmnum].screen_buf_siz, ini->bgsys[frmnum].screen_buf_ofs );
}

//--------------------------------------------------------------------------------------------
/**
 * �w��f�[�^���X�N���[���ɓ]��
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���ԍ�
 * @param	src			�]������f�[�^
 * @param	datasiz		�]���T�C�Y
 * @param	offs		�I�t�Z�b�g
 *
 * @return	none
 *
 * @li	datasiz = GF_BGL_DATA_LZH : ���k�f�[�^
 *
 *	���k���ꂽ�f�[�^�͉𓀏ꏊ��ini->bgsys[frmnum].screen_buf���g�p���邽��
 *	ini->bgsys[frmnum].screen_buf�Ƀf�[�^���Z�b�g����邪�A�񈳏k�̏ꍇ�́A
 *	�Z�b�g����Ȃ��̂ŁA���ӂ��邱�ƁB
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_LoadScreen( GF_BGL_INI * ini, u8 frmnum, const void* src, u32 datasiz, u32 offs )
{
	void * decode_buf;

	if( datasiz == GF_BGL_DATA_LZH ){
		if( ini->bgsys[frmnum].screen_buf != NULL ){
			decode_buf = ini->bgsys[frmnum].screen_buf;
			GF_BGL_DataDecord( src, decode_buf, datasiz );

			GF_BGL_LoadScreenSub(
				frmnum, decode_buf, 
				ini->bgsys[frmnum].screen_buf_ofs * GF_BGL_1SCRDATASIZ,
				ini->bgsys[frmnum].screen_buf_siz );
		}else{
			u32	alloc_siz;

			alloc_siz	= ((*(u32*)src) >> 8);
			decode_buf = sys_AllocMemoryLo( ini->heapID, alloc_siz );

#ifdef	OSP_ERR_BGL_DECODEBUF_GET		// �W�J�̈�m�ێ��s
			if(decode_buf == NULL){
				OS_Printf("�̈�m�ێ��s\n");
			}
#endif	// OSP_ERR_BGL_DECODEBUF_GET

			GF_BGL_DataDecord( src, decode_buf, datasiz );

			GF_BGL_LoadScreenSub( frmnum, decode_buf, offs * GF_BGL_1SCRDATASIZ, alloc_siz );
			sys_FreeMemoryEz( decode_buf );
		}
	}else{
		GF_BGL_LoadScreenSub( frmnum, (void*)src, offs * GF_BGL_1SCRDATASIZ, datasiz );
	}
}
//--------------------------------------------------------------------------------------------
/**
 * �w��f�[�^���X�N���[���ɓ]���i�t�@�C���Q�Ɓj
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���ԍ�
 * @param	path		�t�@�C���̃p�X��
 * @param	offs		�I�t�Z�b�g
 *
 * @return	none
 *
 *	���k���Ή�
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_LoadScreenFile( GF_BGL_INI * ini, u8 frmnum, const char * path, u32 offs )
{
	void * mem;
	u32	size;
	u32	mode;

	mem = sys_LoadFileEx( ini->heapID, path, &size );
	if( mem == NULL ){
		return;	//�G���[
	}
	GF_BGL_ScreenBufSet( ini, frmnum, mem, size );
	GF_BGL_LoadScreen( ini, frmnum, mem, size, offs );
	sys_FreeMemory( ini->heapID, mem );
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���]��
 *
 * @param	frmnum		BG�t���[���ԍ�
 * @param	src			�]������f�[�^
 * @param	offs		�I�t�Z�b�g
 * @param	siz			�]���T�C�Y
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void GF_BGL_LoadScreenSub( u8 frmnum, void* src, u32 ofs, u32 siz )
{
#if DMA_USE
	DC_FlushRange( src, siz );

	switch( frmnum ){
	case GF_BGL_FRAME0_M:
		GX_LoadBG0Scr( src, ofs, siz ); 
		return;
	case GF_BGL_FRAME1_M:
		GX_LoadBG1Scr( src, ofs, siz ); 
		return;
	case GF_BGL_FRAME2_M:
		GX_LoadBG2Scr( src, ofs, siz ); 
		return;
	case GF_BGL_FRAME3_M:
		GX_LoadBG3Scr( src, ofs, siz ); 
		return;
	case GF_BGL_FRAME0_S:
		GXS_LoadBG0Scr( src, ofs, siz ); 
		return;
	case GF_BGL_FRAME1_S:
		GXS_LoadBG1Scr( src, ofs, siz ); 
		return;
	case GF_BGL_FRAME2_S:
		GXS_LoadBG2Scr( src, ofs, siz ); 
		return;
	case GF_BGL_FRAME3_S:
		GXS_LoadBG3Scr( src, ofs, siz ); 
		return;
	}
#else
	switch( frmnum ){
	case GF_BGL_FRAME0_M:
		MI_CpuCopy32(src,(void*)((u32)G2_GetBG0ScrPtr() + ofs),siz);
		return;
	case GF_BGL_FRAME1_M:
		MI_CpuCopy32(src,(void*)((u32)G2_GetBG1ScrPtr() + ofs),siz);
		return;
	case GF_BGL_FRAME2_M:
		MI_CpuCopy32(src,(void*)((u32)G2_GetBG2ScrPtr() + ofs),siz);
		return;
	case GF_BGL_FRAME3_M:
		MI_CpuCopy32(src,(void*)((u32)G2_GetBG3ScrPtr() + ofs),siz);
		return;
	case GF_BGL_FRAME0_S:
		MI_CpuCopy32(src,(void*)((u32)G2S_GetBG0ScrPtr() + ofs),siz);
		return;
	case GF_BGL_FRAME1_S:
		MI_CpuCopy32(src,(void*)((u32)G2S_GetBG1ScrPtr() + ofs),siz);
		return;
	case GF_BGL_FRAME2_S:
		MI_CpuCopy32(src,(void*)((u32)G2S_GetBG2ScrPtr() + ofs),siz);
		return;
	case GF_BGL_FRAME3_S:
		MI_CpuCopy32(src,(void*)((u32)G2S_GetBG3ScrPtr() + ofs),siz);
		return;
	}
#endif
}

//--------------------------------------------------------------------------------------------
/**
 *	�X�N���[���f�[�^���o�b�t�@�ɃR�s�[
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[��
 * @param	dat			�w��f�[�^
 * @param	datasizpx	�f�[�^�T�C�Y
 *
 * @retrn	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_ScreenBufSet( GF_BGL_INI * ini, u8 frmnum, const void * dat, u32 datasiz )
{
	GF_BGL_DataDecord( dat, ini->bgsys[frmnum].screen_buf, datasiz );
}


//--------------------------------------------------------------------------------------------
/**
 * �L�����N�^�[�]��
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���ԍ�
 * @param	src			�]������f�[�^
 * @param	datasiz		�]���T�C�Y
 * @param	offs		�I�t�Z�b�g
 *
 * @return	none
 *
 * @li	datasiz = GF_BGL_DATA_LZH : ���k�f�[�^
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_LoadCharacter( GF_BGL_INI * ini, u8 frmnum, const void * src, u32 datasiz, u32 offs )
{
	if( ini->bgsys[frmnum].col_mode == GX_BG_COLORMODE_16 ){
		LoadCharacter( ini, frmnum, src, datasiz, offs * GF_BGL_1CHRDATASIZ );
	}else{
		LoadCharacter( ini, frmnum, src, datasiz, offs * GF_BGL_8BITCHRSIZ );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �L�����N�^�[�]���i�t�@�C���Q�Ɓj
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���ԍ�
 * @param	src			�]������f�[�^
 * @param	datasiz		�]���T�C�Y
 * @param	offs		�I�t�Z�b�g
 *
 * @return	none
 *
 *	���k���Ή�
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_LoadCharacterFile( GF_BGL_INI * ini, u8 frmnum, const char * path, u32 offs )
{
	void * mem;
	u32	size;

	mem = sys_LoadFileEx( ini->heapID, path, &size );
	if(mem == NULL){
		return;	//�G���[
	}
	GF_BGL_LoadCharacter( ini, frmnum, mem, size, offs );
	sys_FreeMemory( ini->heapID, mem );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �L�����f�[�^�W�J
 *
 * @param	frmnum		BG�t���[���ԍ�
 * @param	src			�]������f�[�^
 * @param	datasiz		�]���T�C�Y
 * @param	offs		�I�t�Z�b�g
 *
 * @return	none
 *
 * @li	datasiz = GF_BGL_DATA_LZH : ���k�f�[�^
 */
//--------------------------------------------------------------------------------------------
static void LoadCharacter( GF_BGL_INI* ini, u8 frmnum, const void * src, u32 datasiz, u32 offs )
{
	void * decode_buf;

	if( datasiz == GF_BGL_DATA_LZH ){
		u32	alloc_siz;

		alloc_siz  = ((*(u32*)src) >> 8);
		decode_buf = sys_AllocMemoryLo( ini->heapID, alloc_siz );

#ifdef	OSP_ERR_BGL_DECODEBUF_GET		// �W�J�̈�m�ێ��s
		if( decode_buf == NULL ){
			OS_Printf( "�̈�m�ێ��s\n" );
		}
#endif	// OSP_ERR_BGL_DECODEBUF_GET

		GF_BGL_DataDecord( src, decode_buf, datasiz );

		GF_BGL_LoadCharacterSub( frmnum, decode_buf, offs, alloc_siz );

		sys_FreeMemoryEz( decode_buf );
	}else{
		GF_BGL_LoadCharacterSub( frmnum, (void*)src, offs, datasiz );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �L�����N�^�[�]��
 *
 * @param	frmnum		BG�t���[���ԍ�
 * @param	src			�]������f�[�^
 * @param	offs		�I�t�Z�b�g
 * @param	siz			�]���T�C�Y
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void GF_BGL_LoadCharacterSub( u8 frmnum, void* src, u32 ofs, u32 siz )
{
#if DMA_USE
	DC_FlushRange( src, siz );

	switch( frmnum ){
	case GF_BGL_FRAME0_M:
		GX_LoadBG0Char( src, ofs, siz ); 
		return;
	case GF_BGL_FRAME1_M:
		GX_LoadBG1Char( src, ofs, siz ); 
		return;
	case GF_BGL_FRAME2_M:
		GX_LoadBG2Char( src, ofs, siz ); 
		return;
	case GF_BGL_FRAME3_M:
		GX_LoadBG3Char( src, ofs, siz ); 
		return;
	case GF_BGL_FRAME0_S:
		GXS_LoadBG0Char( src, ofs, siz ); 
		return;
	case GF_BGL_FRAME1_S:
		GXS_LoadBG1Char( src, ofs, siz ); 
		return;
	case GF_BGL_FRAME2_S:
		GXS_LoadBG2Char( src, ofs, siz ); 
		return;
	case GF_BGL_FRAME3_S:
		GXS_LoadBG3Char( src, ofs, siz ); 
		return;
	}
#else
	switch( frmnum ){
	case GF_BGL_FRAME0_M:
		MI_CpuCopy32(src,(void*)((u32)G2_GetBG0CharPtr() + ofs),siz);
		return;
	case GF_BGL_FRAME1_M:
		MI_CpuCopy32(src,(void*)((u32)G2_GetBG1CharPtr() + ofs),siz);
		return;
	case GF_BGL_FRAME2_M:
		MI_CpuCopy32(src,(void*)((u32)G2_GetBG2CharPtr() + ofs),siz);
		return;
	case GF_BGL_FRAME3_M:
		MI_CpuCopy32(src,(void*)((u32)G2_GetBG3CharPtr() + ofs),siz);
		return;
	case GF_BGL_FRAME0_S:
		MI_CpuCopy32(src,(void*)((u32)G2S_GetBG0CharPtr() + ofs),siz);
		return;
	case GF_BGL_FRAME1_S:
		MI_CpuCopy32(src,(void*)((u32)G2S_GetBG1CharPtr() + ofs),siz);
		return;
	case GF_BGL_FRAME2_S:
		MI_CpuCopy32(src,(void*)((u32)G2S_GetBG2CharPtr() + ofs),siz);
		return;
	case GF_BGL_FRAME3_S:
		MI_CpuCopy32(src,(void*)((u32)G2S_GetBG3CharPtr() + ofs),siz);
		return;
	}
#endif
}

//--------------------------------------------------------------------------------------------
/**
 * �O�N���A���ꂽ�L�������Z�b�g
 *
 * @param	frmnum		BG�t���[���ԍ�
 * @param	datasiz		�]���T�C�Y
 * @param	offs		�I�t�Z�b�g
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_ClearCharSet( u8 frmnum, u32 datasiz, u32 offs, u32 heap )
{
	u32 * chr = (u32 *)sys_AllocMemoryLo( heap, datasiz );

	memset( chr, 0, datasiz );

	GF_BGL_LoadCharacterSub( frmnum, (void*)chr, offs, datasiz );
	sys_FreeMemory( heap, chr );
}

//--------------------------------------------------------------------------------------------
/**
 * �w��l�ŃN���A���ꂽ�L�������Z�b�g
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���ԍ�
 * @param	clear_code	�N���A�R�[�h
 * @param	charcnt		�N���A����L������
 * @param	offs		�L�����̈�擪����̃I�t�Z�b�g�i�L�������j
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_CharFill( GF_BGL_INI * ini, u32 frmnum, u32 clear_code, u32 charcnt, u32 offs )
{
	u32 * chr;
	u32  size;

	size = charcnt * ini->bgsys[frmnum].base_char_size;
	chr = (u32 *)sys_AllocMemoryLo( ini->heapID,  size );

	if( ini->bgsys[frmnum].base_char_size == GF_BGL_1CHRDATASIZ )
	{
		clear_code = (clear_code<<12) | (clear_code<<8) | (clear_code<<4) | clear_code;
		clear_code |= ( clear_code << 16 );
	}
	else
	{
		clear_code = (clear_code<<24) | (clear_code<<16) | (clear_code<<8) | clear_code;
	}

	MI_CpuFillFast( chr, clear_code, size);

	GF_BGL_LoadCharacterSub( frmnum, (void*)chr, offs*ini->bgsys[frmnum].base_char_size, size );
	sys_FreeMemoryEz( chr );
}

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g�]��
 *
 * @param	frmnum		BG�t���[���ԍ�
 * @param	buf			�p���b�g�f�[�^
 * @param	siz			�]���T�C�Y�i�o�C�g�P�ʁj
 * @param	ofs			�I�t�Z�b�g�i�o�C�g�P�ʁj
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_PaletteSet( u8 frmnum, void * buf, u16 siz, u16 ofs )
{
#if DMA_USE
	DC_FlushRange( (void *)buf, siz );
	if( frmnum < GF_BGL_FRAME0_S ){
		GX_LoadBGPltt( (const void *)buf, ofs, siz );
	}else{
		GXS_LoadBGPltt( (const void *)buf, ofs, siz );
	}
#else
	if( frmnum < GF_BGL_FRAME0_S ){
		MI_CpuCopy16((const void *)buf,(void*)(GF_MMAP_MainBgPlttAddr()+ofs),siz);
	}else{
		MI_CpuCopy16((const void *)buf,(void*)(GF_MMAP_SubBgPlttAddr()+ofs),siz);
	}
#endif
}

//--------------------------------------------------------------------------------------------
/**
 * �o�b�N�O���E���h�J���[�]���i�p���b�g�O�̃J���[�w��j
 *
 * @param	frmnum		BG�t���[���ԍ�
 * @param	col			�J���[
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BackGroundColorSet( u8 frmnum, u16 col )
{
	GF_BGL_PaletteSet( frmnum, &col, 2, 0 );
}


//=============================================================================================
//=============================================================================================
//	�X�N���[���֘A
//=============================================================================================
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���f�[�^�ʒu�擾
 *
 * @param	px		�w���W
 * @param	py		�x���W
 * @param	size	�X�N���[���f�[�^�T�C�Y
 *
 * @return	u16:�X�N���[�����Windex
 *
 * @li	size = GF_BGL_SCRSIZ_128x128 �` GF_BGL_SCRSIZ_1024x1024
 */
//--------------------------------------------------------------------------------------------
static u16 GetScreenPos( u8 px, u8 py, u8 size )
{
	u16	pos;

	switch( size ){
	case GF_BGL_SCRSIZ_128x128:
		pos = py * 16 + px;
		break;
	case GF_BGL_SCRSIZ_256x256:
	case GF_BGL_SCRSIZ_256x512:
		pos = py * 32 + px;
		break;
	case GF_BGL_SCRSIZ_512x256:
		pos = ( ( px >> 5 ) * 32 + py ) * 32 + ( px & 0x1f );
		break;
	case GF_BGL_SCRSIZ_512x512:
		pos =  ( ( px >> 5 ) + ( py >> 5 ) * 2 );
		pos *= 1024;
		pos += ( py & 0x1f )  * 32 + ( px & 0x1f );
		break;
	case GF_BGL_SCRSIZ_1024x1024:	// ���Ή�
		pos = 0;
	}
	return pos;
}
//--------------------------------------------------------------------------------------------
/**
 * �܂�Ԃ��L��X�N���[���o�b�t�@�f�[�^�ʒu�擾
 *
 * @param	px		�w���W
 * @param	py		�x���W
 * @param	sx		�X�N���[���f�[�^�T�C�Y(�L�����P��)
 * @param	sy		�X�N���[���f�[�^�T�C�Y(�L�����P��)
 *
 * @retrn	none
 *
 * @li	1x1�`64x64char�T�C�Y�܂őΉ�
 */
//--------------------------------------------------------------------------------------------
static u16 GetScrBufferPos(u8 px,u8 py,u8 sx,u8 sy)
{
	u8	area = 0;
	u16 pos = 0;
	s16	gx = sx-32;	
	s16	gy = sy-32;	

	if(px/32){
		area += 1;
	}
	if(py/32){
		area += 2;
	}
	switch(area){
	case 0:
		if(gx >= 0){
			pos += py*32+px;
		}else{
			pos += py*sx+px;
		}
		break;
	case 1:
		if(gy >= 0){
			pos += 1024;
		}else{
			pos += 32*sy;
		}
		pos += py*gx+(px&0x1F);
		break;
	case 2:
		pos += sx*32;
		if(gx >= 0){
			pos += (py&0x1F)*32+px;
		}else{
			pos += (py&0x1F)*sx+px;
		}
		break;
	case 3:
		pos += (u16)sx*32+(u16)32*gy;
		pos += (py&0x1F)*gx+(px&0x1F);
		break;
	}
	return pos;
}
//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���f�[�^��������
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[��
 * @param	buf			�������ރf�[�^
 * @param	px			�������݊J�n�w���W
 * @param	py			�������݊J�n�x���W
 * @param	sx			�������݂w�T�C�Y
 * @param	sy			�������݂x�T�C�Y
 *
 * @retrn	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_ScrWrite(
		GF_BGL_INI * ini, u8 frmnum, const void * buf, u8 px, u8 py, u8 sx, u8 sy )
{
	GF_BGL_ScrWriteExpand( ini, frmnum, px, py, sx, sy, buf, 0, 0, sx, sy );
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���f�[�^�������݁i�g���Łj
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[��
 * @param	write_px	�������݊J�n�w���W
 * @param	write_px	�������݊J�n�x���W
 * @param	write_sx	�������݂w�T�C�Y
 * @param	write_sy	�������݂x�T�C�Y
 * @param	buf			�ǂݍ��݃f�[�^
 * @param	buf_px		�ǂݍ��݊J�n�w���W
 * @param	buf_py		�ǂݍ��݊J�n�x���W
 * @param	buf_sx		�ǂݍ��݃f�[�^�w�T�C�Y�iwrite_sx,sy�Ƃ͈Ⴂ�A�ǂݍ��݃f�[�^��
 * @param	buf_sy		�ǂݍ��݃f�[�^�x�T�C�Y�@�S�̂̑傫�����̂��̂�������j
 *
 * @retrn	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_ScrWriteExpand(
				GF_BGL_INI * ini, u8 frmnum, u8 write_px, u8 write_py, u8 write_sx, u8 write_sy,
				const void * buf, u8 buf_px, u8 buf_py, u8 buf_sx, u8 buf_sy )
{
	if( ini->bgsys[ frmnum ].mode != GF_BGL_MODE_AFFINE ){
		GF_BGL_ScrWrite_Normal(
			&ini->bgsys[frmnum], write_px, write_py, write_sx, write_sy,
			(u16 *)buf, buf_px, buf_py, buf_sx, buf_sy , GF_BGL_MODE_1DBUF);
	}else{
		GF_BGL_ScrWrite_Affine(
			&ini->bgsys[frmnum], write_px, write_py, write_sx, write_sy,
			(u8 *)buf, buf_px, buf_py, buf_sx, buf_sy , GF_BGL_MODE_1DBUF);
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���f�[�^��������(�܂�Ԃ�����f�[�^��)
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[��
 * @param	write_px	�������݊J�n�w���W
 * @param	write_px	�������݊J�n�x���W
 * @param	write_sx	�������݂w�T�C�Y
 * @param	write_sy	�������݂x�T�C�Y
 * @param	buf			�ǂݍ��݃f�[�^
 * @param	buf_px		�ǂݍ��݊J�n�w���W
 * @param	buf_py		�ǂݍ��݊J�n�x���W
 * @param	buf_sx		�ǂݍ��݃f�[�^�w�T�C�Y�iwrite_sx,sy�Ƃ͈Ⴂ�A�ǂݍ��݃f�[�^��
 * @param	buf_sy		�ǂݍ��݃f�[�^�x�T�C�Y�@�S�̂̑傫�����̂��̂�������j
 *
 * @retrn	none
 *
 * @li	�܂�Ԃ��L��1x1�`64x64�L�����̃t���[�T�C�Y�X�N���[���f�[�^�̋�`��������
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_ScrWriteFree(
				GF_BGL_INI * ini, u8 frmnum, u8 write_px, u8 write_py, u8 write_sx, u8 write_sy,
				const void * buf, u8 buf_px, u8 buf_py, u8 buf_sx, u8 buf_sy )
{
	if( ini->bgsys[ frmnum ].mode != GF_BGL_MODE_AFFINE ){
		GF_BGL_ScrWrite_Normal(
			&ini->bgsys[frmnum], write_px, write_py, write_sx, write_sy,
			(u16 *)buf, buf_px, buf_py, buf_sx, buf_sy, GF_BGL_MODE_2DBUF);
	}else{
		GF_BGL_ScrWrite_Affine(
			&ini->bgsys[frmnum], write_px, write_py, write_sx, write_sy,
			(u8 *)buf, buf_px, buf_py, buf_sx, buf_sy, GF_BGL_MODE_2DBUF);
	}
}


//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���f�[�^�������݁i�e�L�X�g�ʁA�A�t�B���g���ʗp�j
 *
 * @param	GF_BGL_ScrWriteExpand+
 * @param	mode	u8:�o�b�t�@�̃f�[�^���[�h
 *					0:GF_BGL_MODE_1DBUF(�ꎟ���z��f�[�^)
 *					1:GF_BGL_MODE_2DBUF(�܂�Ԃ��L��̃f�[�^)
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void GF_BGL_ScrWrite_Normal(
					GF_BGL_SYS_INI * ini, u8 write_px, u8 write_py, u8 write_sx, u8 write_sy,
					u16 * buf, u8 buf_px, u8 buf_py, u8 buf_sx, u8 buf_sy ,u8 mode)
{
	u16 * scrn;
	u8	scr_sx, scr_sy;
	u8	i, j;

	if( ini->screen_buf == NULL ){
		return;
	}
	scrn = (u16 *)ini->screen_buf;

	BgScreenSizeGet( ini->screen_siz, &scr_sx, &scr_sy );

	if(mode == GF_BGL_MODE_1DBUF){	//�܂�Ԃ��Ȃ��f�[�^����
		for( i=0; i<write_sy; i++ ){
			if( (write_py+i) >= scr_sy || (buf_py+i) >= buf_sy ){ break; }
			for( j=0; j<write_sx; j++ ){
				if( (write_px+j) >= scr_sx || (buf_px+j) >= buf_sx ){ break; }

				scrn[ GetScreenPos(write_px+j,write_py+i,ini->screen_siz) ] =
														buf[ (buf_py+i)*buf_sx+buf_px+j ];
			}
		}
	}else{	//�܂�Ԃ��L��f�[�^����
		for( i=0; i<write_sy; i++ ){
			if( (write_py+i) >= scr_sy || (buf_py+i) >= buf_sy ){ break; }
			for( j=0; j<write_sx; j++ ){
				if( (write_px+j) >= scr_sx || (buf_px+j) >= buf_sx ){ break; }
				scrn[ GetScreenPos(write_px+j,write_py+i,ini->screen_siz) ] =
								buf[ GetScrBufferPos(buf_px+j,buf_py+i,buf_sx,buf_sy)];
			}
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���f�[�^�������݁i�g�k�ʗp�j
 *
 * @param	GF_BGL_ScrWriteExpand�@�{
 * @param	mode	u8:�o�b�t�@�̃f�[�^���[�h
 *					0:GF_BGL_MODE_1DBUF(�ꎟ���z��f�[�^)
 *					1:GF_BGL_MODE_2DBUF(�܂�Ԃ��L��̃f�[�^)
 *
 * @retrn	none
 */
//--------------------------------------------------------------------------------------------
static void GF_BGL_ScrWrite_Affine(
					GF_BGL_SYS_INI * ini, u8 write_px, u8 write_py, u8 write_sx, u8 write_sy,
					u8 * buf, u8 buf_px, u8 buf_py, u8 buf_sx, u8 buf_sy ,u8 mode)
{
	u8 * scrn;
	u8	scr_sx, scr_sy;
	u8	i, j;

	if( ini->screen_buf == NULL ){
		return;
	}
	scrn = (u8 *)ini->screen_buf;

	BgScreenSizeGet( ini->screen_siz, &scr_sx, &scr_sy );

	if(mode == GF_BGL_MODE_1DBUF){	//�܂�Ԃ��Ȃ��f�[�^����
		for( i=0; i<write_sy; i++ ){
			if( (write_py+i) >= scr_sy || (buf_py+i) >= buf_sy ){ break; }
			for( j=0; j<write_sx; j++ ){
				if( (write_px+j) >= scr_sx || (buf_px+j) >= buf_sx ){ break; }

				scrn[ GetScreenPos( write_px+j, write_py+i, ini->screen_siz ) ] =
														buf[ (buf_py+i)*buf_sx + buf_px+j ];
			}
		}
	}else{	//�܂�Ԃ�����f�[�^����
		for( i=0; i<write_sy; i++ ){
			if( (write_py+i) >= scr_sy || (buf_py+i) >= buf_sy ){ break; }
			for( j=0; j<write_sx; j++ ){
				if( (write_px+j) >= scr_sx || (buf_px+j) >= buf_sx ){ break; }

				scrn[ GetScreenPos( write_px+j, write_py+i, ini->screen_siz ) ] =
								buf[ GetScrBufferPos(buf_px+j,buf_py+i,buf_sx,buf_sy)];
			}
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���f�[�^�o�b�t�@���ߐs����
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[��
 * @param	dat			�w��f�[�^
 * @param	px			�������݊J�n�w���W
 * @param	py			�������݊J�n�x���W
 * @param	sx			�������݂w�T�C�Y
 * @param	sy			�������݂x�T�C�Y
 * @param	mode		�p���b�g�ԍ��Ȃ�
 *
 * @retrn	none
 *
 * @li	mode = GF_BGL_SCRWRT_PALNL : ���݂̃X�N���[���̃p���b�g�������p��
 * @li	mode = GF_BGL_SCRWRT_PALIN : dat�Ƀp���b�g�f�[�^���܂�
 * @li	mode = 0 �` 15 : �p���b�g�ԍ�
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_ScrFill( GF_BGL_INI * ini, u8 frmnum, u16 dat, u8 px, u8 py, u8 sx, u8 sy, u8 mode )
{
	if( ini->bgsys[ frmnum ].mode != GF_BGL_MODE_AFFINE ){
		GF_BGL_ScrFill_Normal( &ini->bgsys[frmnum], dat, px, py, sx, sy, mode );
	}else{
		GF_BGL_ScrFill_Affine( &ini->bgsys[frmnum], (u8)dat, px, py, sx, sy );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���f�[�^�o�b�t�@���ߐs�����i�e�L�X�g�ʁA�A�t�B���g���ʗp�j
 *
 * @param	GF_BGL_ScrFill�Ɠ���
 *
 * @retrn	none
 */
//--------------------------------------------------------------------------------------------
static void GF_BGL_ScrFill_Normal(
					GF_BGL_SYS_INI * ini, u16 dat, u8 px, u8 py, u8 sx, u8 sy, u8 mode )
{
	u16 * scrn;
	u8	scr_sx, scr_sy;
	u8	i, j;

	if( ini->screen_buf == NULL ){
		return;
	}
	scrn = (u16 *)ini->screen_buf;

	BgScreenSizeGet( ini->screen_siz, &scr_sx, &scr_sy );

	for( i=py; i<py+sy; i++ ){
		if( i >= scr_sy ){ break; }
		for( j=px; j<px+sx; j++ ){
			if( j >= scr_sx ){ break; }
			{
				u16	scr_pos = GetScreenPos( j, i, ini->screen_siz );

				if( mode == GF_BGL_SCRWRT_PALIN ){
					scrn[ scr_pos ] = dat;
				}else if( mode == GF_BGL_SCRWRT_PALNL ){
					scrn[ scr_pos ] = ( scrn[scr_pos] & 0xf000 ) + dat;
				}else{
					scrn[ scr_pos ] = ( mode << 12 ) + dat;
				}
			}
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���f�[�^�o�b�t�@���ߐs�����i�g�k�ʗp�j
 *
 * @param	GF_BGL_ScrFill�Ɠ���
 *
 * @retrn	none
 */
//--------------------------------------------------------------------------------------------
static void GF_BGL_ScrFill_Affine( GF_BGL_SYS_INI * ini, u8 dat, u8 px, u8 py, u8 sx, u8 sy )
{
	u8 * scrn;
	u8	scr_sx, scr_sy;
	u8	i, j;

	if( ini->screen_buf == NULL ){
		return;
	}
	scrn = (u8 *)ini->screen_buf;

	BgScreenSizeGet( ini->screen_siz, &scr_sx, &scr_sy );

	for( i=py; i<py+sy; i++ ){
		if( i >= scr_sy ){ break; }
		for( j=px; j<px+sx; j++ ){
			if( j >= scr_sx ){ break; }
			scrn[ GetScreenPos( j, i, ini->screen_siz ) ] = dat;
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �w��t���[���̃X�N���[���̎w��ʒu�̃p���b�g��ύX����
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 * @param	px		�J�nX�ʒu
 * @param	py		�J�nY�ʒu
 * @param	sx		X�T�C�Y
 * @param	sy		Y�T�C�Y
 * @param	pal		�p���b�g�ԍ�
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_ScrPalChange( GF_BGL_INI * ini, u8 frmnum, u8 px, u8 py, u8 sx, u8 sy, u8 pal )
{
	u16 * scrn;
	u8	scr_sx, scr_sy;
	u8	i, j;

	if( ini->bgsys[frmnum].screen_buf == NULL ){
		return;
	}

	scrn = (u16 *)ini->bgsys[frmnum].screen_buf;

	BgScreenSizeGet( ini->bgsys[frmnum].screen_siz, &scr_sx, &scr_sy );

	for( i=py; i<py+sy; i++ ){
		if( i >= scr_sy ){ break; }
		for( j=px; j<px+sx; j++ ){
			if( j >= scr_sx ){ break; }
			{
				u16	scr_pos = GetScreenPos( j, i, ini->bgsys[frmnum].screen_siz );

				scrn[scr_pos] = ( scrn[scr_pos] & 0xfff ) | ( pal << 12 );
			}
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���o�b�t�@���N���A���ē]��
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_ScrClear( GF_BGL_INI * ini, u8 frmnum )
{
	if( ini->bgsys[frmnum].screen_buf == NULL ){
		return;
	}
	MI_CpuClear16( ini->bgsys[frmnum].screen_buf, ini->bgsys[frmnum].screen_buf_siz );
	GF_BGL_LoadScreenReq( ini, frmnum );
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���o�b�t�@���w��R�[�h�ŃN���A���ē]��
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 * @param   clear_code	�N���A�R�[�h
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_ScrClearCode( GF_BGL_INI * ini, u8 frmnum, u16 clear_code )
{
	if( ini->bgsys[frmnum].screen_buf == NULL ){
		return;
	}
	MI_CpuFill16(ini->bgsys[frmnum].screen_buf, clear_code, ini->bgsys[frmnum].screen_buf_siz );
	GF_BGL_LoadScreenReq( ini, frmnum );
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���o�b�t�@���w��R�[�h�ŃN���A���ē]�����N�G�X�g
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 * @param   clear_code	�N���A�R�[�h
 *
 * @return	none
 *
 * @li	�]����VBlank��
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_ScrClearCodeVReq( GF_BGL_INI * ini, u8 frmnum, u16 clear_code )
{
	if( ini->bgsys[frmnum].screen_buf == NULL ){
		return;
	}
	MI_CpuFill16(ini->bgsys[frmnum].screen_buf, clear_code, ini->bgsys[frmnum].screen_buf_siz );
	GF_BGL_LoadScreenV_Req( ini, frmnum );
}


//=============================================================================================
//=============================================================================================
//	�L�����N�^�[�֘A
//=============================================================================================
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �L�����f�[�^���擾
 *
 * @param	frmnum	BG�t���[���ԍ�
 *
 * @return	�L�����f�[�^�̃A�h���X
 */
//--------------------------------------------------------------------------------------------
void * GF_BGL_CgxGet( u8 frmnum )
{
	switch( frmnum ){
	case GF_BGL_FRAME0_M:
		return G2_GetBG0CharPtr();
	case GF_BGL_FRAME1_M:
		return G2_GetBG1CharPtr();
	case GF_BGL_FRAME2_M:
		return G2_GetBG2CharPtr();
	case GF_BGL_FRAME3_M:
		return G2_GetBG3CharPtr();
	case GF_BGL_FRAME0_S:
		return G2S_GetBG0CharPtr();
	case GF_BGL_FRAME1_S:
		return G2S_GetBG1CharPtr();
	case GF_BGL_FRAME2_S:
		return G2S_GetBG2CharPtr();
	case GF_BGL_FRAME3_S:
		return G2S_GetBG3CharPtr();
	}

	return NULL;
}

//--------------------------------------------------------------------------------------------
/**
 * 4bit�̃L�����f�[�^��8bit�ɕϊ�����i�ϊ���w��j
 *
 * @param	chr			�ϊ����f�[�^�i4bit�L�����j
 * @param	chr_size	�ϊ����f�[�^�̃T�C�Y
 * @param	buf			�ϊ���
 * @param	pal_ofs		���p���b�g�ԍ� ( 0 �` 16 )
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_4BitCgxChange8BitMain( const u8 * chr, u32 chr_size, u8 * buf, u8 pal_ofs )
{
	u32	i;

	pal_ofs <<= 4;
	for( i=0; i<chr_size; i++ ){
		buf[i*2] = chr[i] & 0x0f;
		if( buf[i*2] != 0 ){ buf[i*2] += pal_ofs; }

		buf[i*2+1] = ( chr[i] >> 4 ) & 0x0f;
		if( buf[i*2+1] != 0 ){ buf[i*2+1] += pal_ofs; }
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 4bit�̃L�����f�[�^��8bit�ɕϊ�����i�ϊ���擾�j
 *
 * @param	chr			�ϊ����f�[�^�i4bit�L�����j
 * @param	chr_size	�ϊ����f�[�^�̃T�C�Y
 * @param	pal_ofs		���p���b�g�ԍ� ( 0 �` 16 )
 * @param	heap		�q�[�vID
 *
 * @return	�擾�����������̃A�h���X
 */
//--------------------------------------------------------------------------------------------
void * GF_BGL_4BitCgxChange8Bit( const u8 * chr, u32 chr_size, u8 pal_ofs, u32 heap )
{
	void * buf;

	buf = sys_AllocMemory( heap, chr_size * 2 );
	GF_BGL_4BitCgxChange8BitMain( chr, chr_size, (u8 *)buf, pal_ofs );
	return buf;
}


//=============================================================================================
//=============================================================================================
//	BGL�X�e�[�^�X�擾
//=============================================================================================
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * BGL�X�e�[�^�X�擾�i�X�N���[���o�b�t�@�A�h���X�j
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 *
 * @return	�X�N���[���o�b�t�@�A�h���X
 */
//--------------------------------------------------------------------------------------------
void * GF_BGL_ScreenAdrsGet( GF_BGL_INI * ini, u8 frmnum )
{
	return ini->bgsys[frmnum].screen_buf;
}

//--------------------------------------------------------------------------------------------
/**
 * BGL�X�e�[�^�X�擾�i�X�N���[���o�b�t�@�T�C�Y�j
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 *
 * @return	�X�N���[���o�b�t�@�T�C�Y
 */
//--------------------------------------------------------------------------------------------
u32 GF_BGL_ScreenSizGet( GF_BGL_INI * ini, u8 frmnum )
{
	return ini->bgsys[frmnum].screen_buf_siz;
}

//--------------------------------------------------------------------------------------------
/**
 * BGL�X�e�[�^�X�擾�i�X�N���[���^�C�v�擾�j
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 *
 * @return	GF_BGL_SCRSIZ_128x128 ��
 */
//--------------------------------------------------------------------------------------------
u32 GF_BGL_ScreenTypeGet( GF_BGL_INI * ini, u8 frmnum )
{
	return ini->bgsys[frmnum].screen_siz;
}

//--------------------------------------------------------------------------------------------
/**
 * BGL�X�e�[�^�X�擾�i�X�N���[���J�E���^X�j
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 *
 * @return	�X�N���[���J�E���^X
 */
//--------------------------------------------------------------------------------------------
int GF_BGL_ScreenScrollXGet( GF_BGL_INI * ini, u8 frmnum )
{
	return ini->bgsys[frmnum].scroll_x;
}

//--------------------------------------------------------------------------------------------
/**
 * BGL�X�e�[�^�X�擾�i�X�N���[���J�E���^Y�j
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 *
 * @return	�X�N���[���J�E���^Y
 */
//--------------------------------------------------------------------------------------------
int GF_BGL_ScreenScrollYGet( GF_BGL_INI * ini, u8 frmnum )
{
	return ini->bgsys[frmnum].scroll_y;
}

//--------------------------------------------------------------------------------------------
/**
 * BGL�X�e�[�^�X�擾�i�J���[���[�h�j
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 *
 * @return	�J���[���[�h
 */
//--------------------------------------------------------------------------------------------
u8 GF_BGL_ScreenColorModeGet( GF_BGL_INI * ini, u8 frmnum )
{
	return ini->bgsys[frmnum].col_mode;
}

//--------------------------------------------------------------------------------------------
/**
 * BGL�X�e�[�^�X�擾�i��]�p�x�j
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 *
 * @return	��]�p�x
 */
//--------------------------------------------------------------------------------------------
u16 GF_BGL_RadianGet( GF_BGL_INI * ini, u8 frmnum )
{
	return ini->bgsys[frmnum].rad;
}

//--------------------------------------------------------------------------------------------
/**
 * BGL�X�e�[�^�X�擾�iX�����̊g�k�p�����[�^�j
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 *
 * @return	X�����̊g�k�p�����[�^
 */
//--------------------------------------------------------------------------------------------
fx32 GF_BGL_ScaleXGet( GF_BGL_INI * ini, u8 frmnum )
{
	return ini->bgsys[frmnum].scale_x;
}

//--------------------------------------------------------------------------------------------
/**
 * BGL�X�e�[�^�X�擾�iY�����̊g�k�p�����[�^�j
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 *
 * @return	Y�����̊g�k�p�����[�^
 */
//--------------------------------------------------------------------------------------------
fx32 GF_BGL_ScaleYGet( GF_BGL_INI * ini, u8 frmnum )
{
	return ini->bgsys[frmnum].scale_y;
}

//--------------------------------------------------------------------------------------------
/**
 * BGL�X�e�[�^�X�擾�i��]���SX���W�j
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 *
 * @return	��]���SX���W
 */
//--------------------------------------------------------------------------------------------
int GF_BGL_CenterXGet( GF_BGL_INI * ini, u8 frmnum )
{
	return ini->bgsys[frmnum].cx;
}

//--------------------------------------------------------------------------------------------
/**
 * BGL�X�e�[�^�X�擾�i��]���SY���W�j
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 *
 * @return	��]���SY���W
 */
//--------------------------------------------------------------------------------------------
int GF_BGL_CenterYGet( GF_BGL_INI * ini, u8 frmnum )
{
	return ini->bgsys[frmnum].cy;
}

//--------------------------------------------------------------------------------------------
/**
 * BG�v���C�I���e�B�擾
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 *
 * @return	�v���C�I���e�B
 */
//--------------------------------------------------------------------------------------------
u8 GF_BGL_PriorityGet( GF_BGL_INI * ini, u8 frm )
{
	switch( frm ){
	case GF_BGL_FRAME0_M:
		{
			GXBg01Control	dat = G2_GetBG0Control();
			return (u8)dat.priority;
		}
	case GF_BGL_FRAME1_M:
		{
			GXBg01Control	dat = G2_GetBG1Control();
			return (u8)dat.priority;
		}
	case GF_BGL_FRAME2_M:
		switch( ini->bgsys[frm].mode ){
		default:
		case GF_BGL_MODE_TEXT:
			{
				GXBg23ControlText	dat = G2_GetBG2ControlText();
				return (u8)dat.priority;
			}
		case GF_BGL_MODE_AFFINE:
			{
				GXBg23ControlAffine	dat = G2_GetBG2ControlAffine();
				return (u8)dat.priority;
			}
		case GF_BGL_MODE_256X16:
			{
				GXBg23Control256x16Pltt	dat = G2_GetBG2Control256x16Pltt();
				return (u8)dat.priority;
			}
		}
	case GF_BGL_FRAME3_M:
		switch( ini->bgsys[frm].mode ){
		default:
		case GF_BGL_MODE_TEXT:
			{
				GXBg23ControlText	dat = G2_GetBG3ControlText();
				return (u8)dat.priority;
			}
		case GF_BGL_MODE_AFFINE:
			{
				GXBg23ControlAffine	dat = G2_GetBG3ControlAffine();
				return (u8)dat.priority;
			}
		case GF_BGL_MODE_256X16:
			{
				GXBg23Control256x16Pltt	dat = G2_GetBG3Control256x16Pltt();
				return (u8)dat.priority;
			}
		}
	case GF_BGL_FRAME0_S:
		{
			GXBg01Control	dat = G2S_GetBG0Control();
			return (u8)dat.priority;
		}
	case GF_BGL_FRAME1_S:
		{
			GXBg01Control	dat = G2S_GetBG1Control();
			return (u8)dat.priority;
		}
	case GF_BGL_FRAME2_S:
		switch( ini->bgsys[frm].mode ){
		default:
		case GF_BGL_MODE_TEXT:
			{
				GXBg23ControlText	dat = G2S_GetBG2ControlText();
				return (u8)dat.priority;
			}
		case GF_BGL_MODE_AFFINE:
			{
				GXBg23ControlAffine	dat = G2S_GetBG2ControlAffine();
				return (u8)dat.priority;
			}
		case GF_BGL_MODE_256X16:
			{
				GXBg23Control256x16Pltt	dat = G2S_GetBG2Control256x16Pltt();
				return (u8)dat.priority;
			}
		}
	case GF_BGL_FRAME3_S:
		switch( ini->bgsys[frm].mode ){
		default:
		case GF_BGL_MODE_TEXT:
			{
				GXBg23ControlText	dat = G2S_GetBG3ControlText();
				return (u8)dat.priority;
			}
		case GF_BGL_MODE_AFFINE:
			{
				GXBg23ControlAffine	dat = G2S_GetBG3ControlAffine();
				return (u8)dat.priority;
			}
		case GF_BGL_MODE_256X16:
			{
				GXBg23Control256x16Pltt	dat = G2S_GetBG3Control256x16Pltt();
				return (u8)dat.priority;
			}
		}
	}
	return 0;
}




//=============================================================================================
//=============================================================================================
//	�r�b�g�}�b�v�֘A
//=============================================================================================
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �ǂݍ��݂Ə������݂̃A�h���X�Ɣ͈͂��w�肵�ăL������`��(�����F�w�肠��j
 *
 * @param	src			�ǂݍ��݌��L�����f�[�^�w�b�_�[�\���̃|�C���^
 * @param	dest		�������ݐ�L�����f�[�^�w�b�_�[�\���̃|�C���^
 * @param	pos_sx		�ǂݍ��݌��ǂݍ��݊J�nX���W
 * @param	pos_sy		�ǂݍ��݌��ǂݍ��݊J�nY���W
 * @param	pos_dx		�������ݐ揑�����݊J�nX���W
 * @param	pos_dy		�������ݐ揑�����݊J�nY���W
 * @param	size_x		�`��͈�X�T�C�Y
 * @param	size_y		�`��͈�Y�T�C�Y
 * @param	nuki_col	�����F�w��i0�`15 0xff:�����F�w��Ȃ��j
 *
 * @return	none
 *
 * @li	�P�U�F�p
 */
//--------------------------------------------------------------------------------------------
#define	NULLPAL_L	(nuki_col)

#define SRC_ADRS	(src->adrs)
#define SRC_POSX	(pos_sx)
#define SRC_POSY	(pos_sy)
#define SRC_SIZX	(src->size_x)
#define SRC_SIZY	(src->size_y)
#define	SRC_XARG	(((SRC_SIZX) + (SRC_SIZX & 7))>>3)

#define DST_ADRS	(dest->adrs)
#define DST_POSX	(pos_dx)
#define DST_POSY	(pos_dy)
#define DST_SIZX	(dest->size_x)
#define DST_SIZY	(dest->size_y)
#define	DST_XARG	(((DST_SIZX) + (DST_SIZX & 7))>>3)

#define WRT_SIZX	(size_x)
#define WRT_SIZY	(size_y)

#if 0
#define DPPCALC(adrs, pos_x, pos_y, size_x)		\
	(u8*)((adrs) +								\
	(((pos_x)>>1) & 3) +						\
	(((pos_x)>>3) << 5) +						\
	((((pos_y)>>3) * (size_x)) << 5) +			\
	((u32)((pos_y)<<29)>>27)					\
	)

#define DPPCALC_256(adrs, pos_x, pos_y, size_x)	\
	(u8*)((adrs) +								\
	(pos_x & 7) +								\
	((pos_x>>3) << 6) +							\
	(((pos_y>>3) * size_x) << 6) +				\
	((u32)((pos_y)<<29)>>26)					\
	)
#else
#define DPPCALC(adrs, pos_x, pos_y, size_x)		\
	(u8*)((adrs) +								\
	((pos_x >> 1) & 0x00000003) +				\
	((pos_x << 2) & 0x00003fe0) +				\
	(((pos_y << 2) & 0x00003fe0) * size_x) +	\
	((u32)((pos_y << 2)&0x0000001c))			\
	)

#define DPPCALC_256(adrs, pos_x, pos_y, size_x)	\
	(u8*)((adrs) +								\
	(pos_x & 0x00000007) +						\
	((pos_x << 3) & 0x00007fc0) +				\
	(((pos_y << 3) & 0x00007fc0) * size_x) +	\
	((u32)((pos_y << 3)&0x00000038))			\
	)
#endif


void GF_BMP_PrintMain(
			const BMPPRT_HEADER * src, const BMPPRT_HEADER * dest,
			u16 pos_sx, u16 pos_sy, u16 pos_dx, u16 pos_dy,
			u16 size_x, u16 size_y, u16 nuki_col )
{
	int	sx, dx, sy, dy, src_dat, shiftval, x_max, y_max, srcxarg, dstxarg;
	u8	*srcadrs, *dstadrs;

	if((DST_SIZX - DST_POSX) < WRT_SIZX){
		x_max = DST_SIZX - DST_POSX + SRC_POSX;
	}else{
		x_max = WRT_SIZX + SRC_POSX;
	}

	if((DST_SIZY - DST_POSY) < WRT_SIZY){
		y_max = DST_SIZY - DST_POSY + SRC_POSY;
	}else{
		y_max = WRT_SIZY + SRC_POSY;
	}

	srcxarg = SRC_XARG;
	dstxarg = DST_XARG;

	if(nuki_col==GF_BGL_BMPPRT_NOTNUKI){	//�����F�w��Ȃ�
		for(sy=SRC_POSY, dy=DST_POSY; sy < y_max; sy++, dy++){
			for(sx=SRC_POSX, dx=DST_POSX; sx < x_max; sx++, dx++){
				srcadrs	= DPPCALC(SRC_ADRS, sx, sy, srcxarg);
				dstadrs = DPPCALC(DST_ADRS, dx, dy, dstxarg);
	
				src_dat = (*srcadrs >> ((sx & 1)*4)) & 0x0f;
				shiftval = (dx & 1)*4;
				*dstadrs = (u8)((src_dat << shiftval)|(*dstadrs & (0xf0 >> shiftval)));
			}
		}
	}else{				//�����F�w�肠��
		for(sy=SRC_POSY, dy=DST_POSY; sy < y_max; sy++, dy++){
			for(sx=SRC_POSX, dx=DST_POSX; sx < x_max; sx++, dx++){
				srcadrs	= DPPCALC(SRC_ADRS, sx, sy, srcxarg);
				dstadrs = DPPCALC(DST_ADRS, dx, dy, dstxarg);
	
				src_dat = (*srcadrs >> ((sx & 1)*4)) & 0x0f;
	
				if(src_dat != NULLPAL_L){
					shiftval = (dx & 1)*4;
					*dstadrs = (u8)((src_dat << shiftval)|(*dstadrs & (0xf0 >> shiftval)));
				}
			}
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �ǂݍ��݂Ə������݂̃A�h���X�Ɣ͈͂��w�肵�ăL������`��(�����F�w�肠��j
 *
 * @param	src			�ǂݍ��݌��L�����f�[�^�w�b�_�[�\���̃|�C���^
 * @param	dest		�������ݐ�L�����f�[�^�w�b�_�[�\���̃|�C���^
 * @param	pos_sx		�ǂݍ��݌��ǂݍ��݊J�nX���W
 * @param	pos_sy		�ǂݍ��݌��ǂݍ��݊J�nY���W
 * @param	pos_dx		�������ݐ揑�����݊J�nX���W
 * @param	pos_dy		�������ݐ揑�����݊J�nY���W
 * @param	size_x		�`��͈�X�T�C�Y
 * @param	size_y		�`��͈�Y�T�C�Y
 * @param	nuki_col	�����F�w��i0�`15 0xff:�����F�w��Ȃ��j
 *
 * @return	none
 *
 * @li	�Q�T�U�F�p
 */
//--------------------------------------------------------------------------------------------
void GF_BMP_PrintMain256(
		const BMPPRT_HEADER * src, const BMPPRT_HEADER * dest,
		u16 pos_sx, u16 pos_sy, u16 pos_dx, u16 pos_dy,
		u16 size_x, u16 size_y, u16 nuki_col )
{
	int	sx, dx, sy, dy, x_max, y_max, srcxarg, dstxarg;
	u8 * srcadrs;
	u8 * dstadrs;

	if( (DST_SIZX - DST_POSX) < WRT_SIZX ){
		x_max = DST_SIZX - DST_POSX + SRC_POSX;
	}else{
		x_max = WRT_SIZX + SRC_POSX;
	}

	if( (DST_SIZY - DST_POSY) < WRT_SIZY ){
		y_max = DST_SIZY - DST_POSY + SRC_POSY;
	}else{
		y_max = WRT_SIZY + SRC_POSY;
	}
	srcxarg = SRC_XARG;
	dstxarg = DST_XARG;

	if( nuki_col == GF_BGL_BMPPRT_NOTNUKI ){	//�����F�w��Ȃ�
		for( sy=SRC_POSY, dy=DST_POSY; sy<y_max; sy++, dy++ ){
			for( sx=SRC_POSX, dx=DST_POSX; sx<x_max; sx++, dx++ ){
				srcadrs	= DPPCALC_256( SRC_ADRS, sx, sy, srcxarg );
				dstadrs = DPPCALC_256( DST_ADRS, dx, dy, dstxarg );
				*dstadrs = *srcadrs;
			}
		}
	}else{				//�����F�w�肠��
		for( sy=SRC_POSY, dy=DST_POSY; sy<y_max; sy++, dy++ ){
			for( sx=SRC_POSX, dx=DST_POSX; sx<x_max; sx++, dx++ ){
				srcadrs	= DPPCALC_256( SRC_ADRS, sx, sy, srcxarg );
				dstadrs = DPPCALC_256( DST_ADRS, dx, dy, dstxarg );
				if( *srcadrs != NULLPAL_L ){
					*dstadrs = *srcadrs;
				}
			}
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �͈͂��w�肵�Ďw�肳�ꂽ�F�R�[�h�œh��Ԃ�
 *
 * @param	dest		�������ݐ�L�����f�[�^�w�b�_�[�\���̃|�C���^
 * @param	pos_dx		�������ݐ揑�����݊J�nX���W
 * @param	pos_dy		�������ݐ揑�����݊J�nY���W
 * @param	size_x		�`��͈�X�T�C�Y
 * @param	size_y		�`��͈�Y�T�C�Y
 * @param	col_code	�h��Ԃ��F�R�[�h
 *
 * @return	none
 *
 * @li	�P�U�F�p
 */
//--------------------------------------------------------------------------------------------
void	GF_BGL_BmpFill(	const BMPPRT_HEADER *dest,
						u16 pos_dx,u16 pos_dy,u16 size_x,u16 size_y,u8 col_code)
{
	int	x,y,x_max,y_max,xarg;
	u8	*destadrs;

	x_max = pos_dx + size_x;
	if(x_max > dest->size_x){
		x_max = dest->size_x;
	}

	y_max = pos_dy + size_y;
	if(y_max > dest->size_y){
		y_max = dest->size_y;
	}

	xarg = (((dest->size_x) + (dest->size_x&7))>>3);

	for(y = pos_dy; y < y_max; y++){
		for(x = pos_dx; x < x_max; x++){

			destadrs=DPPCALC(dest->adrs, x, y, xarg);
			if(x&1){
				*destadrs&=0x0f;
				*destadrs|=(col_code<<4);
			}
			else{
				*destadrs&=0xf0;
				*destadrs|=col_code;
			}
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �͈͂��w�肵�Ďw�肳�ꂽ�F�R�[�h�œh��Ԃ�
 *
 * @param	dest		�������ݐ�L�����f�[�^�w�b�_�[�\���̃|�C���^
 * @param	pos_dx		�������ݐ揑�����݊J�nX���W
 * @param	pos_dy		�������ݐ揑�����݊J�nY���W
 * @param	size_x		�`��͈�X�T�C�Y
 * @param	size_y		�`��͈�Y�T�C�Y
 * @param	col_code	�h��Ԃ��F�R�[�h
 *
 * @return	none
 *
 * @li	�Q�T�U�F�p
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpFill256(
		const BMPPRT_HEADER * dest,
		u16 pos_dx, u16 pos_dy, u16 size_x, u16 size_y, u8 col_code )
{
	int	x,y,x_max,y_max,xarg;
	u8	*destadrs;

	x_max = pos_dx + size_x;
	if( x_max > dest->size_x ){
		x_max = dest->size_x;
	}

	y_max = pos_dy + size_y;
	if( y_max > dest->size_y ){
		y_max = dest->size_y;
	}

	xarg = ( dest->size_x + (dest->size_x & 7) ) >> 3;

	for( y=pos_dy; y<y_max; y++ ){
		for( x=pos_dx; x<x_max; x++ ){
			destadrs = DPPCALC_256( dest->adrs, x, y, xarg );
			*destadrs = col_code;
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�f�[�^�m��
 *
 * @param	ini		BGL�f�[�^
 * @param	mode	�������m�ۃ��[�h
 * @param	num		�m�ۂ���BMP�E�B���h�E�̐�
 *
 * @return	�m�ۂ����f�[�^�̃A�h���X
 */
//--------------------------------------------------------------------------------------------
GF_BGL_BMPWIN * GF_BGL_BmpWinAllocGet( u32 heapID, u8 num )
{
	GF_BGL_BMPWIN * wk;
	u16	i;

	wk = (GF_BGL_BMPWIN *)sys_AllocMemory( heapID, sizeof(GF_BGL_BMPWIN) * num );

	for( i=0; i<num; i++ ){
		GF_BGL_BmpWinInit( &wk[i] );
	}

	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�f�[�^������
 *
 * @param	wk		BMP�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinInit( GF_BGL_BMPWIN * wk )
{
	wk->ini    = NULL;
	wk->frmnum = GF_BGL_BITMAP_NULL;
	wk->posx   = 0;
	wk->posy   = 0;
	wk->sizx   = 0;
	wk->sizy   = 0;
	wk->palnum = 0;
	wk->chrofs = 0;
	wk->chrbuf = NULL;
	wk->bitmode = GF_BGL_BMPWIN_BITMODE_4;		// �O�̂��ߗǂ��g�����ŏ��������Ă���
}

//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�o�^�`�F�b�N
 *
 * @param	win		BMP�f�[�^
 *
 * @retval	"TRUE = �o�^�ς�"
 * @retval	"FALSE = ���o�^"
 */
//--------------------------------------------------------------------------------------------
u8 GF_BGL_BmpWinAddCheck( GF_BGL_BMPWIN * win )
{
	if( win->ini == NULL || win->frmnum == GF_BGL_BITMAP_NULL || win->chrbuf == NULL ){
		return FALSE;
	}
	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�ǉ�
 *
 * @param	ini		BGL�f�[�^
 * @param	win		BMP�f�[�^�i�[�ꏊ
 * @param	frmnum	BG�t���[���ԍ�
 * @param	posx	X���W�i�L�����P�ʁj
 * @param	posy	Y���W�i�L�����P�ʁj
 * @param	sizx	X�T�C�Y�i�L�����P�ʁj
 * @param	sizy	X�T�C�Y�i�L�����P�ʁj
 * @param	palnum	�g�p�p���b�g�ԍ�
 * @param	chrofs	�g�pCGX�I�t�Z�b�g
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinAdd(
		GF_BGL_INI * ini, GF_BGL_BMPWIN * win, u8 frmnum,
		u8 posx, u8 posy, u8 sizx, u8 sizy, u8 palnum, u16 chrofs )
{
	void * chrvbuf;
	u32	chrvsiz;

/*
	// �i�[�ꏊ�T�[�`
	if( win->frmnum != GF_BGL_BITMAP_NULL ){
#ifdef	OSP_ERR_BGL_BMPADD		// BMP�o�^�ς�
		OS_Printf( "�a�l�o�o�^�ς�\n" );
#endif	// OSP_ERR_BGL_BMPADD
		return;
	}
*/
	// �g�p�t���[���󋵂̔���i�X�N���[���o�b�t�@�m�ۂ���Ă��邩�j
	if( ini->bgsys[frmnum].screen_buf == NULL ){
#ifdef	OSP_ERR_BGL_BMPADD		// BMP�o�^���s
		OS_Printf( "�a�l�o�o�^���s\n" );
#endif	// OSP_ERR_BGL_BMPADD
		return;
	}

	// �L�����N�^�o�b�t�@�̊m��
	chrvsiz = sizx * sizy * ini->bgsys[frmnum].base_char_size;
	chrvbuf = sys_AllocMemory( ini->heapID, chrvsiz );

	if( chrvbuf == NULL ){
#ifdef	OSP_ERR_BGL_BMPADD		// BMP�o�^���s
		OS_Printf( "�a�l�o�̈�m�ێ��s\n" );
#endif	// OSP_ERR_BGL_BMPADD
		return;
	}

	// �r�b�g�}�b�v�̐ݒ�
	win->ini    = ini;
	win->frmnum = frmnum;
	win->posx   = posx;
	win->posy   = posy;
	win->sizx   = sizx;
	win->sizy   = sizy;
	win->palnum = palnum;
	win->chrofs = chrofs;
	win->chrbuf = chrvbuf;
	win->bitmode = (ini->bgsys[ frmnum ].col_mode == GX_BG_COLORMODE_16)? GF_BGL_BMPWIN_BITMODE_4 : GF_BGL_BMPWIN_BITMODE_8;

#ifdef	OSP_BGL_BMP_SIZ		// BMP�T�C�Y
	OS_Printf( "�a�l�o�b�f�w�̈�=%x\n", chrvbuf );
#endif	// OSP_BGL_BMP_SIZ
}

//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�ǉ��iOBJ�p�ɃL�����̈悾�����m�ہB4bit��p�B�j
 *
 * @param	ini		BGL�f�[�^
 * @param	win		BMP�f�[�^�i�[�ꏊ
 * @param	sizx	X�T�C�Y�i�L�����P�ʁj
 * @param	sizy	X�T�C�Y�i�L�����P�ʁj
 * @param	chrofs	�g�pCGX�I�t�Z�b�g
 * @param   fill_color	���ߐs�����J���[�ԍ�(0�`0xf)
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinObjAdd(GF_BGL_INI * ini, GF_BGL_BMPWIN * win, u8 sizx, u8 sizy, 
	u16 chrofs, u8 fill_color )
{
	void * chrvbuf;
	u32	chrvsiz;

	chrvsiz	= (u32)( sizx * sizy * GF_BGL_1CHRDATASIZ );
	chrvbuf = sys_AllocMemory( ini->heapID, chrvsiz );
	
	fill_color |= fill_color << 4;
	memset(chrvbuf, fill_color, chrvsiz );
	
	if( chrvbuf == NULL ){
#ifdef	OSP_ERR_BGL_BMPADD		// BMP�o�^���s
		OS_Printf( "BMPOBJ�̈�m�ێ��s\n" );
#endif	// OSP_ERR_BGL_BMPADD
		return;
	}

	// �r�b�g�}�b�v�̐ݒ�
	win->ini    = ini;
	win->sizx   = sizx;
	win->sizy   = sizy;
	win->chrofs = chrofs;
	win->chrbuf = chrvbuf;
	win->bitmode = GF_BGL_BMPWIN_BITMODE_4;

#ifdef	OSP_BGL_BMP_SIZ		// BMP�T�C�Y
	OS_Printf( "BMPOBJCGX�̈�=%x\n", chrvbuf );
#endif	// OSP_BGL_BMP_SIZ
}

//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�ǉ��i�f�[�^�w��j
 *
 * @param	ini		BGL�f�[�^
 * @param	win		BMP�f�[�^�i�[�ꏊ
 * @param	dat		BMPWIN_DAT�\���̌^�f�[�^�ւ̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinAddEx( GF_BGL_INI * ini, GF_BGL_BMPWIN * win, const BMPWIN_DAT * dat )
{
	GF_BGL_BmpWinAdd(
		ini, win, dat->frm_num, dat->pos_x, dat->pos_y,
		dat->siz_x, dat->siz_y, dat->palnum, dat->chrnum );
}

//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�폜
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinDel( GF_BGL_BMPWIN * win )
{
	// �L�����N�^�o�b�t�@���蓖�ĊJ��
	sys_FreeMemoryEz( win->chrbuf );

	win->ini    = NULL;
	win->frmnum = GF_BGL_BITMAP_NULL;
	win->posx   = 0;
	win->posy   = 0;
	win->sizx   = 0;
	win->sizy   = 0;
	win->palnum = 0;
	win->chrofs = 0;
	win->chrbuf = NULL;
}

//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�폜�iBMP�f�[�^���J���j
 *
 * @param	win		BMP�f�[�^
 * @param	num		��
 *
 * @return	none
 *
 *	GF_BGL_BmpWinAllocGet()�Ŋm�ۂ����ꍇ�Ɏg�p���ĉ�����
 *	
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinFree( GF_BGL_BMPWIN * win, u8 num )
{
	u16	i;

	// �L�����N�^�o�b�t�@���蓖�ĊJ��
	for( i=0; i<num; i++ ){
		if( win[i].chrbuf == NULL ){ continue; }
		sys_FreeMemoryEz( win[i].chrbuf );
	}

	// BMP�f�[�^�̈�J��
	sys_FreeMemoryEz( win );
}


//*------------------------------------------*/
/**   �E�B���h�E�f�[�^�쐬���]���֐�         */
//*------------------------------------------*/
static void (* const WinOnFunc[])(GF_BGL_BMPWIN*) = {
	GF_BGL_BmpWinOn_Normal,		// �e�L�X�g
	GF_BGL_BmpWinOn_Affine,		// �A�t�B��
	GF_BGL_BmpWinOn_Normal,		// �g���A�t�B��
};
static void (* const WinOnVReqFunc[])(GF_BGL_BMPWIN*) = {
	GF_BGL_BmpWinOnVReq_Normal,		// �e�L�X�g
	GF_BGL_BmpWinOnVReq_Affine,		// �A�t�B��
	GF_BGL_BmpWinOnVReq_Normal,		// �g���A�t�B��
};
//*------------------------------------------*/
/**   �E�B���h�E�\���I�t���]���֐�           */
//*------------------------------------------*/
static void (* const WinOffFunc[])(GF_BGL_BMPWIN*) = {
	GF_BGL_BmpWinOff_Normal,
	GF_BGL_BmpWinOff_Affine,
	GF_BGL_BmpWinOff_Normal,
};
static void (* const WinOffVReqFunc[])(GF_BGL_BMPWIN*) = {
	GF_BGL_BmpWinOffVReq_Normal,
	GF_BGL_BmpWinOffVReq_Affine,
	GF_BGL_BmpWinOffVReq_Normal,
};

//*------------------------------------------*/
/**   �E�B���h�E�X�N���[���쐬�֐��e�[�u��   */
//*------------------------------------------*/
static void (* const WinScrnMakeFunc[])(GF_BGL_BMPWIN*) = {
	MakeWinScrnText,		// �e�L�X�g
	MakeWinScrnAffine,		// �A�t�B��
	MakeWinScrnText,		// �g���A�t�B��
};

//*------------------------------------------*/
/**   �E�B���h�E�X�N���[���N���A�֐��e�[�u�� */
//*------------------------------------------*/
static void (* const WinScrnClearFunc[])(GF_BGL_BMPWIN*) = {
	ClearWinScrnText,		// �e�L�X�g
	ClearWinScrnAffine,		// �A�t�B��
	ClearWinScrnText,		// �g���A�t�B��
};


static const u8 ScreenXElems[] =  {
	16,		// GF_BGL_SCRSIZ_128x128
	32,		// GF_BGL_SCRSIZ_256x256
	32,		// GF_BGL_SCRSIZ_256x512
	32,		// GF_BGL_SCRSIZ_512x256
	32,		// GF_BGL_SCRSIZ_512x512
	32,		// GF_BGL_SCRSIZ_1024x1024
};

#include "gflib/assert.h"

//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�\���i�X�N���[���A�L�����]���j
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinOn( GF_BGL_BMPWIN * win )
{
	GF_ASSERT(win!=NULL);
	GF_ASSERT(win->ini!=NULL);
	GF_ASSERT(win->frmnum<8);
	GF_ASSERT(win->ini->bgsys[win->frmnum].mode < NELEMS(WinOnFunc));
	WinOnFunc[ win->ini->bgsys[win->frmnum].mode ]( win );
}
//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�\���i�X�N���[���]�����N�G�X�g�A�L�����]���j
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinOnVReq( GF_BGL_BMPWIN * win )
{
	GF_ASSERT(win!=NULL);
	GF_ASSERT(win->ini!=NULL);
	GF_ASSERT(win->frmnum<8);
	GF_ASSERT(win->ini->bgsys[win->frmnum].mode < NELEMS(WinOnVReqFunc));
	WinOnVReqFunc[ win->ini->bgsys[win->frmnum].mode ]( win );
}
//------------------------------------------------------------------
/**
 * Window�̈�X�N���[�����֘ABG�����o�b�t�@�ɍ쐬����
 *
 * @param   win		
 *
 */
//------------------------------------------------------------------
void GF_BGL_BmpWinMakeScrn( GF_BGL_BMPWIN* win )
{
	WinScrnMakeFunc[ win->ini->bgsys[win->frmnum].mode ]( win );
}
//------------------------------------------------------------------
/**
 * Window�̈�X�N���[�����֘ABG�����o�b�t�@�ɍ쐬����
 * �i�T�C�Y�w��BBitmapWindow�쐬�������������̈�̃X�N���[���쐬���\�B�傫���̂͂m�f�B�j
 *
 * @param   win			BitmapWindow �ւ̃|�C���^
 * @param   width		�X�N���[���쐬�̈�̕��i�L�����P�ʁj
 * @param   height		�X�N���[���쐬�̈�̍����i�L�����P�ʁj
 *
 */
//------------------------------------------------------------------
void GF_BGL_BmpWinMakeScrnLimited( GF_BGL_BMPWIN* win, u32 width, u32 height )
{
	u32  x_save, y_save;

	x_save = win->sizx;
	y_save = win->sizy;
	win->sizx = width;
	win->sizy = height;

	WinScrnMakeFunc[ win->ini->bgsys[win->frmnum].mode ]( win );

	win->sizx = x_save;
	win->sizy = y_save;

}
//------------------------------------------------------------------
/**
 * �֘ABG�����o�b�t�@��Window�̈�X�N���[�����N���A����
 *
 * @param   win		
 *
 */
//------------------------------------------------------------------
void GF_BGL_BmpWinClearScrn( GF_BGL_BMPWIN* win )
{
	WinScrnClearFunc[ win->ini->bgsys[win->frmnum].mode ]( win );
}

//------------------------------------------------------------------
/**
 * �X�N���[���쐬�i�e�L�X�g�E�g���A�t�B���p�j
 *
 * @param   win		
 *
 */
//------------------------------------------------------------------
static void MakeWinScrnText( GF_BGL_BMPWIN* win )
{
	if( win->ini->bgsys[ win->frmnum ].screen_buf )
	{
		u32 x, y, x_max, y_max, chr, p, xelems;
		u16* scrn;

//		xelems = ScreenXElems[ win->ini->bgsys[win->frmnum].screen_siz ];
		xelems = 32;

		scrn = (u16*)(win->ini->bgsys[ win->frmnum ].screen_buf);

		chr = win->chrofs;

		x_max = win->posx + win->sizx;
		y_max = win->posy + win->sizy;
		for(y = win->posy; y < y_max; y++)
		{
			for(x = win->posx; x < x_max; x++)
			{
				p = ((y&0x20)*32) + ((x&0x20)*32) + ((y&0x1f)*xelems) + (x&0x1f);
				scrn[p] = chr | (win->palnum << 12);
				chr++;
			}
		}
	}
}
//------------------------------------------------------------------
/**
 * �X�N���[���쐬�i�A�t�B��BG�p�j
 *
 * @param   win		
 *
 */
//------------------------------------------------------------------
static void MakeWinScrnAffine( GF_BGL_BMPWIN* win )
{
	if( win->ini->bgsys[ win->frmnum ].screen_buf )
	{
		int x, y, chr, xelems;
		u8* scrn;

		xelems = ScreenXElems[ win->ini->bgsys[win->frmnum].screen_siz ];

		scrn = (u8*)(win->ini->bgsys[ win->frmnum ].screen_buf) + 
				win->posy * xelems + win->posx;

		chr = win->chrofs;

		for( y = 0; y < win->sizy; y++ )
		{
			for( x = 0; x < win->sizx; x++ )
			{
				scrn[x] = chr++;
			}
			scrn += xelems;
		}
	}
}
//------------------------------------------------------------------
/**
 * �X�N���[���N���A�i�e�L�X�g�E�g���A�t�B���p�j
 *
 * @param   win		
 *
 */
//------------------------------------------------------------------
static void ClearWinScrnText( GF_BGL_BMPWIN* win )
{
	if( win->ini->bgsys[ win->frmnum ].screen_buf )
	{
		u32 x, y, x_max, y_max, p, xelems;
		u16* scrn;

		xelems = ScreenXElems[ win->ini->bgsys[win->frmnum].screen_siz ];

		scrn = (u16*)(win->ini->bgsys[ win->frmnum ].screen_buf);

		x_max = win->posx + win->sizx;
		y_max = win->posy + win->sizy;
		for(y = win->posy; y < y_max; y++)
		{
			for(x = win->posx; x < x_max; x++)
			{
				p = ((y&0x20)*32) + ((x&0x20)*32) + ((y&0x1f)*xelems) + (x&0x1f);
				scrn[p] = 0x0000;
			}
		}
	}
}
//------------------------------------------------------------------
/**
 * �X�N���[���N���A�i�A�t�B��BG�p�j
 *
 * @param   win		
 *
 */
//------------------------------------------------------------------
static void ClearWinScrnAffine( GF_BGL_BMPWIN* win )
{
	if( win->ini->bgsys[ win->frmnum ].screen_buf )
	{
		int x, y, xelems;
		u8* scrn;

		xelems = ScreenXElems[ win->ini->bgsys[win->frmnum].screen_siz ];

		scrn = (u8*)(win->ini->bgsys[ win->frmnum ].screen_buf) + 
				win->posy * xelems + win->posx;

		for( y = 0; y < win->sizy; y++ )
		{
			for( x = 0; x < win->sizx; x++ )
			{
				scrn[x] = 0;
			}
			scrn += xelems;
		}
	}

}
//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�\���i�X�N���[���A�L�����]���i�e�L�X�g�A�A�t�B���g��BG�j�j
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void GF_BGL_BmpWinOn_Normal( GF_BGL_BMPWIN * win )
{
	MakeWinScrnText( win );

	GF_BGL_LoadScreen(
		win->ini, win->frmnum, 
		win->ini->bgsys[ win->frmnum ].screen_buf,
		win->ini->bgsys[ win->frmnum ].screen_buf_siz,
		win->ini->bgsys[ win->frmnum ].screen_buf_ofs );

	GF_BGL_BmpWinCgxOn( win );
}
//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�\���i�X�N���[���]�����N�G�X�g�A�L�����]���i�e�L�X�g�A�A�t�B���g��BG�j�j
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void GF_BGL_BmpWinOnVReq_Normal( GF_BGL_BMPWIN * win )
{
	MakeWinScrnText( win );

	GF_BGL_LoadScreenV_Req( win->ini, win->frmnum );
	GF_BGL_BmpWinCgxOn( win );
}
//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�\���i�X�N���[���A�L�����]���i�g�k�ʁj�j
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void GF_BGL_BmpWinOn_Affine( GF_BGL_BMPWIN * win )
{
	MakeWinScrnAffine( win );

	GF_BGL_LoadScreen(
		win->ini, win->frmnum, 
		win->ini->bgsys[ win->frmnum ].screen_buf,
		win->ini->bgsys[ win->frmnum ].screen_buf_siz,
		win->ini->bgsys[ win->frmnum ].screen_buf_ofs );

	GF_BGL_LoadCharacter(
		win->ini, win->frmnum, win->chrbuf,
		(u32)( win->sizx * win->sizy * GF_BGL_8BITCHRSIZ ), (u32)win->chrofs );
}
//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�\���i�X�N���[���]�����N�G�X�g�A�L�����]���i�g�k�ʁj�j
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void GF_BGL_BmpWinOnVReq_Affine( GF_BGL_BMPWIN * win )
{
	MakeWinScrnAffine( win );

	GF_BGL_LoadScreenV_Req( win->ini, win->frmnum );
	GF_BGL_LoadCharacter(
		win->ini, win->frmnum, win->chrbuf,
		(u32)( win->sizx * win->sizy * GF_BGL_8BITCHRSIZ ), (u32)win->chrofs );
}

//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�\���i�L�����]���̂݁j
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinCgxOn( GF_BGL_BMPWIN * win )
{
	u32 chrsize = win->sizx * win->sizy * win->ini->bgsys[ win->frmnum ].base_char_size;

	GF_BGL_LoadCharacter( win->ini, win->frmnum, win->chrbuf, chrsize, win->chrofs );
}

//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v��\���i�X�N���[���N���A���]���j
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinOff( GF_BGL_BMPWIN * win )
{
	WinOffFunc[ win->ini->bgsys[ win->frmnum ].mode ]( win );
}
//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v��\���i�X�N���[���N���A���]�����N�G�X�g�j
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinOffVReq( GF_BGL_BMPWIN * win )
{
	WinOffVReqFunc[ win->ini->bgsys[ win->frmnum ].mode ]( win );
}

//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v��\���i�e�L�X�g�A�A�t�B���g��BG�j
 *
 * @param	win
 *
 */
//--------------------------------------------------------------------------------------------
static void GF_BGL_BmpWinOff_Normal( GF_BGL_BMPWIN * win )
{
	ClearWinScrnText( win );
	GF_BGL_LoadScreen(
		win->ini, win->frmnum,
		win->ini->bgsys[ win->frmnum ].screen_buf,
		win->ini->bgsys[ win->frmnum ].screen_buf_siz,
		win->ini->bgsys[ win->frmnum ].screen_buf_ofs );
}
//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v��\�����N�G�X�g�i�e�L�X�g�A�A�t�B���g��BG�j
 *
 * @param	win
 *
 */
//--------------------------------------------------------------------------------------------
static void GF_BGL_BmpWinOffVReq_Normal( GF_BGL_BMPWIN * win )
{
	ClearWinScrnText( win );
	GF_BGL_LoadScreenV_Req( win->ini, win->frmnum );
}

//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v��\���i�g�k�ʁj
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void GF_BGL_BmpWinOff_Affine( GF_BGL_BMPWIN * win )
{
	ClearWinScrnAffine( win );
	GF_BGL_LoadScreen(
		win->ini, win->frmnum, 
		win->ini->bgsys[ win->frmnum ].screen_buf,
		win->ini->bgsys[ win->frmnum ].screen_buf_siz,
		win->ini->bgsys[ win->frmnum ].screen_buf_ofs );
}
//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v��\�����N�G�X�g�i�g�k�ʁj
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void GF_BGL_BmpWinOffVReq_Affine( GF_BGL_BMPWIN * win )
{
	ClearWinScrnAffine( win );
	GF_BGL_LoadScreenV_Req( win->ini, win->frmnum );
}

//--------------------------------------------------------------------------------------------
/**
 * �w��J���[�őS�̂�h��Ԃ�
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 * @param	col		�J���[�i���o�[
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinDataFill( GF_BGL_BMPWIN * win, u8 col )
{
	u32	datasize;
	u32 data;

	if( win->ini->bgsys[ win->frmnum ].base_char_size == GF_BGL_1CHRDATASIZ ){
		col = (col<<4)|col;
	}
	data = (col<<24)|(col<<16)|(col<<8)|col;

	datasize = win->ini->bgsys[ win->frmnum ].base_char_size * win->sizx * win->sizy;

	MI_CpuFillFast( win->chrbuf, data, datasize );
}

//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�`��
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 * @param	src		�r�b�g�}�b�v�\���f�[�^�|�C���^
 * @param	src_x	�r�b�g�}�b�v�\���J�n�ʒu�w
 * @param	src_y	�r�b�g�}�b�v�\���J�n�ʒu�x
 * @param	src_dx	�r�b�g�}�b�v�f�[�^�T�C�Y�w
 * @param	src_dy	�r�b�g�}�b�v�f�[�^�T�C�Y�w
 * @param	win_x	�E�C���h�E�\���J�n�ʒu�w
 * @param	win_y	�E�C���h�E�\���J�n�ʒu�x
 * @param	win_dx	�E�C���h�E�f�[�^�T�C�Y�w
 * @param	win_dy	�E�C���h�E�f�[�^�T�C�Y�x
 *
 * @retval	�Ȃ�
 *
 * �r�b�g�}�b�v�f�[�^�̏������݂����s
 * �r�b�g�}�b�v�f�[�^�̐؂�����\�ɂ�������
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinPrint(
			GF_BGL_BMPWIN * win, void * src,
			u16 src_x, u16 src_y, u16 src_dx, u16 src_dy,
			u16 win_x, u16 win_y, u16 win_dx, u16 win_dy )
{
	GF_BGL_BmpWinPrintEx(
		win, src, src_x, src_y, src_dx, src_dy, win_x, win_y, win_dx, win_dy, 0 );
}

//--------------------------------------------------------------------------------------------
/**
 *	�r�b�g�}�b�v�`��i�g���Łj
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 * @param	src		�r�b�g�}�b�v�\���f�[�^�|�C���^
 * @param	src_x	�r�b�g�}�b�v�\���J�n�ʒu�w
 * @param	src_y	�r�b�g�}�b�v�\���J�n�ʒu�x
 * @param	src_dx	�r�b�g�}�b�v�f�[�^�T�C�Y�w
 * @param	src_dy	�r�b�g�}�b�v�f�[�^�T�C�Y�w
 * @param	win_x	�E�C���h�E�\���J�n�ʒu�w
 * @param	win_y	�E�C���h�E�\���J�n�ʒu�x
 * @param	win_dx	�E�C���h�E�f�[�^�T�C�Y�w
 * @param	win_dy	�E�C���h�E�f�[�^�T�C�Y�x
 * @param	nuki	�����F�w��i0�`15 0xff:�����F�w��Ȃ��j
 *
 * @retval	�Ȃ�
 *
 * �r�b�g�}�b�v�f�[�^�̏������݂����s
 * �r�b�g�}�b�v�f�[�^�̐؂�����\�ɂ�������
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinPrintEx(
		GF_BGL_BMPWIN * win, void * src,
		u16 src_x, u16 src_y, u16 src_dx, u16 src_dy,
		u16 win_x, u16 win_y, u16 win_dx, u16 win_dy, u16 nuki )
{
	BMPPRT_HEADER	src_data;
	BMPPRT_HEADER	dst_data;

	src_data.adrs	= (u8 *)src;
	src_data.size_x = src_dx;
	src_data.size_y = src_dy;

	dst_data.adrs	= (u8 *)win->chrbuf;
	dst_data.size_x = (u16)(win->sizx * GF_BGL_1CHRDOTSIZ);
	dst_data.size_y = (u16)(win->sizy * GF_BGL_1CHRDOTSIZ);

	if( win->ini->bgsys[ win->frmnum ].col_mode == GX_BG_COLORMODE_16 ){
		GF_BMP_PrintMain(
			&src_data, &dst_data, src_x, src_y, win_x, win_y, win_dx, win_dy, nuki );
	}else{
		GF_BMP_PrintMain256(
			&src_data, &dst_data, src_x, src_y, win_x, win_y, win_dx, win_dy, nuki );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �w��͈͂�h��Ԃ�
 *
 * @param	win			BMP�f�[�^
 * @param	col			�h��Ԃ��J���[
 * @param	px			�J�nX���W
 * @param	py			�J�nY���W
 * @param	sx			X�T�C�Y
 * @param	sy			Y�T�C�Y
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinFill( GF_BGL_BMPWIN * win, u8 col, u16 px, u16 py, u16 sx, u16 sy )
{
	BMPPRT_HEADER	dst_data;

	dst_data.adrs	= (u8 *)win->chrbuf;
	dst_data.size_x = (u16)(win->sizx * GF_BGL_1CHRDOTSIZ);
	dst_data.size_y = (u16)(win->sizy * GF_BGL_1CHRDOTSIZ);

	if( win->ini->bgsys[ win->frmnum ].col_mode == GX_BG_COLORMODE_16 ){
		GF_BGL_BmpFill( (const BMPPRT_HEADER *)&dst_data, px, py, sx, sy, col );
	}else{
		GF_BGL_BmpFill256( (const BMPPRT_HEADER *)&dst_data, px, py, sx, sy, col );
	}
}

//---------------------------------------------------------------------------------------------
/**
 * �����\����p���������A�b�v��
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 * @param	src		�L�����f�[�^
 * @param	ssx		�t�H���gX�T�C�Y
 * @param	ssy		�t�H���gY�T�C�Y
 * @param	wx		��������X���W
 * @param	wy		��������Y���W
 *
 * @return	none
 */
//---------------------------------------------------------------------------------------------
#define	M_NULLPAL_L	(0)
#define	M_NULLPAL_H	(NULLPAL_L << 4)
#define	M_BMPWIN_CHR_DOT	(8)

#define M_SRC_ADRS	(src)
#define M_SRC_POSX	(0)
#define M_SRC_POSY	(0)
#define M_SRC_SIZX	(16)
#define M_SRC_SIZY	(16)
#define	M_SRC_XARG	(((M_SRC_SIZX) + (M_SRC_SIZX & 7))>>3)

#define M_DST_ADRS	(dst)
#define M_DST_POSX	(wx)
#define M_DST_POSY	(wy)
#define M_DST_SIZX	(dsx)
#define M_DST_SIZY	(dsy)
#define	M_DST_XARG	(((M_DST_SIZX) + (M_DST_SIZX & 7))>>3)

#define M_WRT_SIZX	(ssx)
#define M_WRT_SIZY	(ssy)

#define DOT_PUT(xofs,yofs,xsiz,ysiz,dadrs,dpx,dpy,dxarg)				\
	{																	\
		int	sx, dx, sy, dy, shiftval;									\
		u8	src_dat;													\
		u8	*srcadrs, *destadrs;										\
		u32 src_base;													\
																		\
		srcadrs	= M_SRC_ADRS + (yofs / 8 * 0x40) + (xofs / 8 * 0x20);	\
		for(sy=0, dy=dpy+yofs; sy < ysiz; sy++, dy++){					\
			src_base = *(u32*)srcadrs;									\
			for(sx=0, dx=dpx+xofs; sx < xsiz; sx++, dx++){				\
				destadrs = DPPCALC(dadrs, dx, dy, dxarg);				\
																		\
				src_dat = (u8)((src_base >> (sx * 4)) & 0x0f);			\
																		\
				if(src_dat != M_NULLPAL_L){								\
					shiftval = (dx & 1)*4;								\
					*destadrs = (u8)((src_dat << shiftval)|(*destadrs & (0xf0 >> shiftval)));\
				}														\
			}															\
			srcadrs	+= 4;												\
		}																\
	}

#define DOT_PUT_256(xofs,yofs,xsiz,ysiz,dadrs,dpx,dpy,dxarg)			\
	{																	\
		int	sx, dx, sy, dy;												\
		u8	src_dat;													\
		u8	*srcadrs, *destadrs;										\
		u32 src_base;													\
																		\
		srcadrs	= M_SRC_ADRS + (yofs / 8 * 0x40) + (xofs / 8 * 0x40);	\
		for( sy=0, dy=dpy+yofs; sy<ysiz; sy++, dy++ ){					\
			src_base = *(u32*)srcadrs;									\
			for( sx=0, dx=dpx+xofs; sx<xsiz; sx++, dx++ ){				\
				destadrs = DPPCALC_256(dadrs, dx, dy, dxarg);			\
																		\
				src_dat = (u8)((src_base >> (sx * 4)) & 0x0f);			\
																		\
				if( src_dat != M_NULLPAL_L ){							\
					*destadrs = src_dat;								\
				}														\
			}															\
			srcadrs	+= 4;												\
		}																\
	}

void GF_BGL_BmpWinPrintMsg(
		GF_BGL_BMPWIN * win, u8 * src, u16 ssx, u16 ssy, u16 wx, u16 wy )
{
	u8 * dst; 
	u16	dsx, dsy;
	int	x_max, y_max;
	u8	print_pat;

	dst	= (u8 *)win->chrbuf;
	dsx = (u16)(win->sizx * GF_BGL_1CHRDOTSIZ);
	dsy = (u16)(win->sizy * GF_BGL_1CHRDOTSIZ);

	if((M_DST_SIZX - M_DST_POSX) < M_WRT_SIZX){
		x_max = M_DST_SIZX - M_DST_POSX;
	}else{
		x_max = M_WRT_SIZX;
	}

	if((M_DST_SIZY - M_DST_POSY) < M_WRT_SIZY){
		y_max = M_DST_SIZY - M_DST_POSY;
	}else{
		y_max = M_WRT_SIZY;
	}
	print_pat = 0;

	if( x_max > 8 ){ print_pat |= 1; }
	if( y_max > 8 ){ print_pat |= 2; }

	if( win->bitmode == GF_BGL_BMPWIN_BITMODE_4 ){
		switch( print_pat ){
		case 0:	//�P�L����(8x8)
			DOT_PUT( 0, 0, x_max,	y_max,	 M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG );
			return;
		case 1:	//�Q�L����(16x8)
			DOT_PUT( 0, 0, 8,		y_max,	 M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG );
			DOT_PUT( 8, 0, x_max-8,	y_max,	 M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG );
			return;
		case 2:	//�Q�L����(8x16)
			DOT_PUT( 0, 0, x_max,	8,		 M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG );
			DOT_PUT( 0, 8, x_max,	y_max-8, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG );
			return;
		case 3:	//�S�L����(16x16)
			DOT_PUT( 0, 0, 8,		8,		 M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG );
			DOT_PUT( 8, 0, x_max-8,	8,		 M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG );
			DOT_PUT( 0, 8, 8,		y_max-8, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG );
			DOT_PUT( 8, 8, x_max-8,	y_max-8, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG );
			return;
		}
	}else{
		switch( print_pat ){
		case 0:	//�P�L����(8x8)
			DOT_PUT_256( 0, 0, x_max,	y_max,	 M_DST_ADRS,M_DST_POSX,M_DST_POSY,M_DST_XARG);
			return;
		case 1:	//�Q�L����(16x8)
			DOT_PUT_256( 0, 0, 8,		y_max,	 M_DST_ADRS,M_DST_POSX,M_DST_POSY,M_DST_XARG);
			DOT_PUT_256( 8, 0, x_max-8,	y_max,	 M_DST_ADRS,M_DST_POSX,M_DST_POSY,M_DST_XARG);
			return;
		case 2:	//�Q�L����(8x16)
			DOT_PUT_256( 0, 0, x_max,	8,		 M_DST_ADRS,M_DST_POSX,M_DST_POSY,M_DST_XARG);
			DOT_PUT_256( 0, 8, x_max,	y_max-8, M_DST_ADRS,M_DST_POSX,M_DST_POSY,M_DST_XARG);
			return;
		case 3:	//�S�L����(16x16)
			DOT_PUT_256( 0, 0, 8,		8,		 M_DST_ADRS,M_DST_POSX,M_DST_POSY,M_DST_XARG);
			DOT_PUT_256( 8, 0, x_max-8,	8,		 M_DST_ADRS,M_DST_POSX,M_DST_POSY,M_DST_XARG);
			DOT_PUT_256( 0, 8, 8,		y_max-8, M_DST_ADRS,M_DST_POSX,M_DST_POSY,M_DST_XARG);
			DOT_PUT_256( 8, 8, x_max-8,	y_max-8, M_DST_ADRS,M_DST_POSX,M_DST_POSY,M_DST_XARG);
			return;
		}
	}
}


//=============================================================================================
//=============================================================================================
#define	M_PUT_TBL	( tbl )

#define DOT_PUT_W(xofs,yofs,xsiz,ysiz,dadrs,dpx,dpy,dxarg,ptbl)			\
	{																	\
		int	sx, dx, sy, dy, shiftval;									\
		u8	src_dat;													\
		u8	tbl_flg;													\
		u8	tbl_bit;													\
		u8	*destadrs;													\
		const u8* srcadrs;												\
		u32 src_base;													\
																		\
		srcadrs	= M_SRC_ADRS + (yofs / 8 * 0x40) + (xofs / 8 * 0x20);	\
																		\
		if( yofs == 0 ){												\
			dy = dpy + yofs;											\
			tbl_bit = (u8)( ptbl & 0xff );								\
		}else{															\
			dy = dpy + yofs;											\
			for( sy=0; sy<8; sy++ ){									\
				if( ( (ptbl>>sy) & 1 ) != 0 ){ dy++; }					\
			}															\
			tbl_bit = (u8)( ptbl >> 8 );								\
		}																\
																		\
		for( sy=0; sy<ysiz; sy++ ){										\
			src_base = *(u32*)srcadrs;									\
			tbl_flg = (u8)(( tbl_bit >> sy ) & 1);						\
			for(sx=0, dx=dpx+xofs; sx < xsiz; sx++, dx++){				\
				destadrs = DPPCALC(dadrs, dx, dy, dxarg);				\
																		\
				src_dat = (u8)((src_base >> (sx * 4)) & 0x0f);			\
																		\
				if(src_dat != M_NULLPAL_L){								\
					shiftval = (dx & 1)*4;								\
					src_dat = (u8)((src_dat << shiftval)|(*destadrs & (0xf0 >> shiftval)));\
					*destadrs = src_dat;								\
																		\
					if( tbl_flg != 0 ){									\
						destadrs = DPPCALC(dadrs, dx, (dy+1), dxarg);	\
						*destadrs = src_dat;							\
					}													\
				}														\
			}															\
			if( tbl_flg != 0 ){											\
				dy += 2;												\
			}else{														\
				dy++;													\
			}															\
			srcadrs	+= 4;												\
		}																\
	}
/*
#define DOT_PUT_W_256(xofs,yofs,xsiz,ysiz,dadrs,dpx,dpy,dxarg,ptbl)		\
	{																	\
		int	sx, dx, sy, dy, shiftval;									\
		u8	src_dat;													\
		u8	tbl_flg;													\
		u8	tbl_bit;													\
		u8	*destadrs;													\
		const u8* srcadrs;												\
		u32 src_base;													\
																		\
		srcadrs	= M_SRC_ADRS + (yofs / 8 * 0x40) + (xofs / 8 * 0x20);	\
																		\
		if( yofs == 0 ){												\
			dy = dpy + yofs;											\
			tbl_bit = (u8)( ptbl & 0xff );								\
		}else{															\
			dy = dpy + yofs;											\
			for( sy=0; sy<8; sy++ ){									\
				if( ( (ptbl>>sy) & 1 ) != 0 ){ dy++; }					\
			}															\
			tbl_bit = (u8)( ptbl >> 8 );								\
		}																\
																		\
		for( sy=0; sy<ysiz; sy++ ){										\
			src_base = *(u32*)srcadrs;									\
			tbl_flg = (u8)(( tbl_bit >> sy ) & 1);						\
			for(sx=0, dx=dpx+xofs; sx < xsiz; sx++, dx++){				\
				destadrs = DPPCALC_256(dadrs, dx, dy, dxarg);			\
																		\
				src_dat = (u8)((src_base >> (sx * 4)) & 0x0f);			\
																		\
				if(src_dat != M_NULLPAL_L){								\
					shiftval = (dx & 1)*4;								\
					*destadrs = src_dat;								\
																		\
					if( tbl_flg != 0 ){									\
						destadrs = DPPCALC_256(dadrs,dx,(dy+1),dxarg);	\
						*destadrs = src_dat;							\
					}													\
				}														\
			}															\
			if( tbl_flg != 0 ){											\
				dy += 2;												\
			}else{														\
				dy++;													\
			}															\
			srcadrs	+= 4;												\
		}																\
	}
*/

#define CM_SRC_ADRS	(chg_src)

#define DOT_PUT_W_256(xofs,yofs,xsiz,ysiz,dadrs,dpx,dpy,dxarg,ptbl)		\
	{																	\
		int	sx, dx, sy, dy;												\
		u8	src_dat;													\
		u8	tbl_flg;													\
		u8	tbl_bit;													\
		u8	*destadrs;													\
		const u8* srcadrs;												\
		u8 * src_base;													\
																		\
		srcadrs	= CM_SRC_ADRS + (yofs / 8 * 0x80) + (xofs / 8 * 0x40);	\
																		\
		if( yofs == 0 ){												\
			dy = dpy + yofs;											\
			tbl_bit = (u8)( ptbl & 0xff );								\
		}else{															\
			dy = dpy + yofs;											\
			for( sy=0; sy<8; sy++ ){									\
				if( ( (ptbl>>sy) & 1 ) != 0 ){ dy++; }					\
			}															\
			tbl_bit = (u8)( ptbl >> 8 );								\
		}																\
																		\
		for( sy=0; sy<ysiz; sy++ ){										\
			src_base = (u8 *)srcadrs;									\
			tbl_flg = (u8)(( tbl_bit >> sy ) & 1);						\
			for(sx=0, dx=dpx+xofs; sx < xsiz; sx++, dx++){				\
				destadrs = DPPCALC_256(dadrs, dx, dy, dxarg);			\
																		\
				src_dat = src_base[sx];									\
																		\
				if(src_dat != M_NULLPAL_L){								\
					*destadrs = src_dat;								\
																		\
					if( tbl_flg != 0 ){									\
						destadrs = DPPCALC_256(dadrs,dx,(dy+1),dxarg);	\
						*destadrs = src_dat;							\
					}													\
				}														\
			}															\
			if( tbl_flg != 0 ){											\
				dy += 2;												\
			}else{														\
				dy++;													\
			}															\
			srcadrs	+= 8;												\
		}																\
	}

void GF_BGL_BmpWinPrintMsgWide(
		GF_BGL_BMPWIN * win, const u8 * src, u16 ssx, u16 ssy, u16 wx, u16 wy, u16 tbl )
{
	u8 * dst;
	u16	dsx,dsy;
	int	x_max, y_max;
	u8	print_pat;

	dst	= (u8 *)win->chrbuf;
	dsx = (u16)(win->sizx * GF_BGL_1CHRDOTSIZ);
	dsy = (u16)(win->sizy * GF_BGL_1CHRDOTSIZ);

	if((M_DST_SIZX - M_DST_POSX) < M_WRT_SIZX){
		x_max = M_DST_SIZX - M_DST_POSX;
	}else{
		x_max = M_WRT_SIZX;
	}

	if((M_DST_SIZY - M_DST_POSY) < M_WRT_SIZY){
		y_max = M_DST_SIZY - M_DST_POSY;
	}else{
		y_max = M_WRT_SIZY;
	}

	print_pat = 0;

	if( x_max > 8 ){ print_pat |= 1; }
	if( y_max > 8 ){ print_pat |= 2; }

	if( win->bitmode == GF_BGL_BMPWIN_BITMODE_4 ){
		switch( print_pat ){
		case 0:	//�P�L����(8x8)
			DOT_PUT_W( 0, 0, x_max,	y_max, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			return;
		case 1:	//�Q�L����(16x8)
			DOT_PUT_W( 0, 0, 8, y_max, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			DOT_PUT_W( 8, 0, x_max-8, y_max, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			return;
		case 2:	//�Q�L����(8x16)
			DOT_PUT_W( 0, 0, x_max,	8, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			DOT_PUT_W( 0, 8, x_max,	y_max-8, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			return;
		case 3:	//�S�L����(16x16)
			DOT_PUT_W( 0, 0, 8, 8, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			DOT_PUT_W( 8, 0, x_max-8, 8, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			DOT_PUT_W( 0, 8, 8, y_max-8, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			DOT_PUT_W( 8, 8, x_max-8, y_max-8, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			return;
		}
	}else{
		u8 * chg_src = GF_BGL_4BitCgxChange8Bit(
							src, ssx*4*ssy*8, win->palnum, win->ini->heapID );

		switch( print_pat ){
		case 0:	//�P�L����(8x8)
			DOT_PUT_W_256( 0, 0, x_max,	y_max, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			break;
		case 1:	//�Q�L����(16x8)
			DOT_PUT_W_256( 0, 0, 8, y_max, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			DOT_PUT_W_256( 8, 0, x_max-8, y_max, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			break;
		case 2:	//�Q�L����(8x16)
			DOT_PUT_W_256( 0, 0, x_max,	8, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			DOT_PUT_W_256( 0, 8, x_max,	y_max-8, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			break;
		case 3:	//�S�L����(16x16)
			DOT_PUT_W_256( 0, 0, 8, 8, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			DOT_PUT_W_256( 8, 0, x_max-8, 8, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			DOT_PUT_W_256( 0, 8, 8, y_max-8, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			DOT_PUT_W_256( 8, 8, x_max-8, y_max-8, M_DST_ADRS, M_DST_POSX, M_DST_POSY, M_DST_XARG, M_PUT_TBL );
			break;
		}

		sys_FreeMemoryEz( chg_src );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�E�C���h�E�f�[�^�V�t�g
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 * @param	direct	����
 * @param	offset	�V�t�g��
 * @param	data	�󔒂ɂȂ����̈�𖄂߂�f�[�^
 *
 * @return	none
 *
 * �r�b�g�}�b�v�f�[�^(�S�̈�)�̃V�t�g�����s
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinShift( GF_BGL_BMPWIN * win, u8 direct, u8 offset, u8 data )
{
	if( win->ini->bgsys[ win->frmnum ].col_mode == GX_BG_COLORMODE_16 ){
		GF_BGL_BmpWinShift16( win, direct, offset, data );
	}else{
		GF_BGL_BmpWinShift256( win, direct, offset, data );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�E�C���h�E�f�[�^�V�t�g�i�P�U�F�p�j
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 * @param	direct	����
 * @param	offset	�V�t�g��
 * @param	data	�󔒂ɂȂ����̈�𖄂߂�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void GF_BGL_BmpWinShift16( GF_BGL_BMPWIN * win, u8 direct, u8 offset, u8 data )
{
	u8 * cgxram;
	int	chroffs, woffs, roffs;
	int	blanch_chr, over_offs;
	int	xsiz, rline;
	int	i;

	cgxram		= (u8 *)win->chrbuf;
	blanch_chr	= (data<<24) | (data<<16) | (data<<8) | (data<<0);
	over_offs	= win->sizy * win->sizx * GF_BGL_1CHRDATASIZ;
	xsiz		= win->sizx;

	switch( direct ){
	case GF_BGL_BMPWIN_SHIFT_U:
		for( chroffs=0; chroffs<over_offs; chroffs+=GF_BGL_1CHRDATASIZ ){
			rline = offset;

			for( i=0; i<8; i++ ){
				woffs = chroffs + (i << 2);
				roffs = chroffs + (((xsiz * (rline&0xfffffff8))|(rline&0x00000007)) << 2);
				if(roffs < over_offs){
					*(u32*)(cgxram + woffs) = *(u32*)(cgxram + roffs);
				}else{
					*(u32*)(cgxram + woffs) = blanch_chr;
				}
				rline++;
			}
		}
		break;
	case GF_BGL_BMPWIN_SHIFT_D:
		cgxram += over_offs - 4;

		for( chroffs=0; chroffs<over_offs; chroffs+=GF_BGL_1CHRDATASIZ ){
			rline = offset;

			for( i=0; i<8; i++ ){
				woffs = chroffs + (i << 2);
				roffs = chroffs + (((xsiz * (rline&0xfffffff8))|(rline&0x00000007)) << 2);
				if(roffs < over_offs){
					*(u32*)(cgxram - woffs) = *(u32*)(cgxram - roffs);
				}else{
					*(u32*)(cgxram - woffs) = blanch_chr;
				}
				rline++;
			}
		}
		break;
	case GF_BGL_BMPWIN_SHIFT_L:
		break;
	case GF_BGL_BMPWIN_SHIFT_R:
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �r�b�g�}�b�v�E�C���h�E�f�[�^�V�t�g�i�Q�T�U�F�p�j
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 * @param	direct	����
 * @param	offset	�V�t�g��
 * @param	data	�󔒂ɂȂ����̈�𖄂߂�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void GF_BGL_BmpWinShift256( GF_BGL_BMPWIN * win, u8 direct, u8 offset, u8 data )
{
	u8 * cgxram;
	int	chroffs, woffs, roffs;
	int	blanch_chr, over_offs;
	int	xsiz, rline;
	int	i;

	cgxram		= (u8 *)win->chrbuf;
	blanch_chr	= ( data << 24 ) | ( data << 16 ) | ( data << 8 ) | data;
	over_offs	= win->sizy * win->sizx * GF_BGL_8BITCHRSIZ;
	xsiz		= win->sizx;

	switch(direct){
	case GF_BGL_BMPWIN_SHIFT_U:
		for( chroffs=0; chroffs<over_offs; chroffs+=GF_BGL_8BITCHRSIZ ){
			rline = offset;

			for( i=0; i<8; i++ ){
				woffs = chroffs + (i << 3);
				roffs = chroffs + (((xsiz * (rline&0xfffffff8))|(rline&0x00000007)) << 3);
				if( roffs < over_offs ){
					*(u32*)(cgxram + woffs) = *(u32*)(cgxram + roffs);
				}else{
					*(u32*)(cgxram + woffs) = blanch_chr;
				}

				woffs += 4;
				roffs += 4;
				if( roffs < over_offs + 4 ){
					*(u32*)(cgxram + woffs) = *(u32*)(cgxram + roffs);
				}else{
					*(u32*)(cgxram + woffs) = blanch_chr;
				}

				rline++;
			}
		}
		break;
	case GF_BGL_BMPWIN_SHIFT_D:
		cgxram += ( over_offs - 8 );

		for( chroffs=0; chroffs<over_offs; chroffs+=GF_BGL_8BITCHRSIZ ){
			rline = offset;

			for( i=0; i<8; i++ ){
				woffs = chroffs + (i << 3);
				roffs = chroffs + (((xsiz * (rline&0xfffffff8))|(rline&0x00000007)) << 3);
				if( roffs < over_offs ){
					*(u32*)(cgxram - woffs) = *(u32*)(cgxram - roffs);
				}else{
					*(u32*)(cgxram - woffs) = blanch_chr;
				}

				woffs -= 4;
				roffs -= 4;
				if( roffs < over_offs - 4 ){
					*(u32*)(cgxram - woffs) = *(u32*)(cgxram - roffs);
				}else{
					*(u32*)(cgxram - woffs) = blanch_chr;
				}

				rline++;
			}
		}
		break;
	case GF_BGL_BMPWIN_SHIFT_L:
		break;
	case GF_BGL_BMPWIN_SHIFT_R:
		break;
	}
}

//=============================================================================================
//=============================================================================================
//	BMP�f�[�^����
//=============================================================================================
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * BMP�f�[�^�擾�FBGL�f�[�^
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	win->ini
 */
//--------------------------------------------------------------------------------------------
GF_BGL_INI * GF_BGL_BmpWinGet_BglIni( GF_BGL_BMPWIN * win )
{
	return win->ini;
}

//--------------------------------------------------------------------------------------------
/**
 * BMP�f�[�^�擾�FBG�t���[���ԍ�
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	win->frmnum
 */
//--------------------------------------------------------------------------------------------
u8 GF_BGL_BmpWinGet_Frame( GF_BGL_BMPWIN * win )
{
	return win->frmnum;
}

//--------------------------------------------------------------------------------------------
/**
 * BMP�f�[�^�擾�FX�T�C�Y
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	win->sizx
 */
//--------------------------------------------------------------------------------------------
u8 GF_BGL_BmpWinGet_SizeX( GF_BGL_BMPWIN * win )
{
	return win->sizx;
}

//--------------------------------------------------------------------------------------------
/**
 * BMP�f�[�^�擾�FY�T�C�Y
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	win->sizy
 */
//--------------------------------------------------------------------------------------------
u8 GF_BGL_BmpWinGet_SizeY( GF_BGL_BMPWIN * win )
{
	return win->sizy;
}

//--------------------------------------------------------------------------------------------
/**
 * BMP�f�[�^�擾�FX���W
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 * @param	index	�r�b�g�}�b�v�g�p�ݒ�w�b�_INDEX
 *
 * @return	win->posx
 */
//--------------------------------------------------------------------------------------------
u8 GF_BGL_BmpWinGet_PosX( GF_BGL_BMPWIN * win )
{
	return win->posx;
}

//--------------------------------------------------------------------------------------------
/**
 * BMP�f�[�^�擾�FY���W
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	win->posy
 */
//--------------------------------------------------------------------------------------------
u8 GF_BGL_BmpWinGet_PosY( GF_BGL_BMPWIN * win )
{
	return win->posy;
}

//--------------------------------------------------------------------------------------------
/**
 * BMP�f�[�^�擾�F�L�����ԍ�
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	win->chrofs
 */
//--------------------------------------------------------------------------------------------
u16 GF_BGL_BmpWinGet_Chrofs( GF_BGL_BMPWIN * win )
{
	return win->chrofs;
}

//--------------------------------------------------------------------------------------------
/**
 * BMP�f�[�^�ݒ�FX���W
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinSet_PosX( GF_BGL_BMPWIN * win, u8 px )
{
	win->posx = px;
}

//--------------------------------------------------------------------------------------------
/**
 * BMP�f�[�^�ݒ�FY���W
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinSet_PosY( GF_BGL_BMPWIN * win, u8 py )
{
	win->posy = py;
}

//--------------------------------------------------------------------------------------------
/**
 * BMP�f�[�^�ݒ�F�p���b�g�ԍ�
 *
 * @param	win		BMP�f�[�^�i�[�ꏊ
 * @param   palnum	�p���b�g�ԍ�
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_BmpWinSet_Pal( GF_BGL_BMPWIN * win, u8 palnum )
{
	win->palnum = palnum;
}


//=============================================================================================
//=============================================================================================
//	NITRO-CHARACTER�f�[�^�W�J����
//=============================================================================================
//=============================================================================================

void GF_BGL_NTRCHR_CharLoadEx(
		GF_BGL_INI * ini, u8 frmnum, const char * path, u32 offs, u32 size )
{
	void * buf;
	NNSG2dCharacterData * dat;

	buf = sys_LoadFile( ini->heapID, path );

#ifdef	OSP_ERR_BGL_NTRCHR_LOAD		// NITRO-CHARACTER�̃f�[�^�擾�̈�m�ێ��s
	if( buf == NULL ){
		OS_Printf( "ERROR : GF_GBL_NTRCHR_CharLoad -load\n" );
		return;
	}
#endif	// OSP_ERR_BGL_NTRCHR_LOAD

	if( NNS_G2dGetUnpackedBGCharacterData( buf, &dat ) == TRUE ){
		if( size == 0xffffffff ){
#ifdef	OSP_BGL_NTRCHR_LOAD		// NITRO-CHARACTER�̃f�[�^�T�C�Y
			OS_Printf( "GF_GBL_NTRCHR_CharLoad -size %d\n", dat->szByte );
#endif	// OSP_BGL_NTRCHR_LOAD
			GF_BGL_LoadCharacter( ini, frmnum, dat->pRawData, dat->szByte, offs );
		}else{
#ifdef	OSP_BGL_NTRCHR_LOAD		// NITRO-CHARACTER�̃f�[�^�T�C�Y
			OS_Printf( "GF_GBL_NTRCHR_CharLoad -size %d\n", size );
#endif	// OSP_BGL_NTRCHR_LOAD
			GF_BGL_LoadCharacter( ini, frmnum, dat->pRawData, size, offs );
		}
	}

	sys_FreeMemory( ini->heapID, buf );
}

//--------------------------------------------------------------------------------------------
/**
 * NITRO-CHARACTER�̃L�����f�[�^��ǂݍ���
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 * @param	path	�t�@�C���p�X
 * @param	offs	�I�t�Z�b�g�i�L�����P�ʁj
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_NTRCHR_CharLoad( GF_BGL_INI * ini, u8 frmnum, const char * path, u32 offs )
{
	void * buf;
	NNSG2dCharacterData * dat;

	buf = sys_LoadFile( ini->heapID, path );

#ifdef	OSP_ERR_BGL_NTRCHR_LOAD		// NITRO-CHARACTER�̃f�[�^�擾�̈�m�ێ��s
	if( buf == NULL ){
		OS_Printf( "ERROR : GF_GBL_NTRCHR_CharLoad -load\n" );
		return;
	}
#endif	// OSP_ERR_BGL_NTRCHR_LOAD

	if( NNS_G2dGetUnpackedBGCharacterData( buf, &dat ) == TRUE ){
#ifdef	OSP_BGL_NTRCHR_LOAD		// NITRO-CHARACTER�̃f�[�^�T�C�Y
		OS_Printf( "GF_GBL_NTRCHR_CharLoad -size %d\n", dat->szByte );
#endif	// OSP_BGL_NTRCHR_LOAD
		GF_BGL_LoadCharacter( ini, frmnum, dat->pRawData, dat->szByte, offs );
	}

	sys_FreeMemory( ini->heapID, buf );
}




//--------------------------------------------------------------------------------------------
/**
 * NITRO-CHARACTER�̃L�����f�[�^���擾
 *
 * @param	buf		�W�J�p�o�b�t�@
 * @param	mode	�w��q�[�v�̈��`
 * @param	path	�t�@�C���p�X
 *
 * @return	�L�����f�[�^�̍\����
 */
//--------------------------------------------------------------------------------------------
NNSG2dCharacterData * GF_BGL_NTRCHR_CharGet( void ** buf, int mode, const char * path )
{
	NNSG2dCharacterData * dat;

	*buf = sys_LoadFile( mode, path );

#ifdef	OSP_ERR_BGL_NTRCHR_LOAD		// NITRO-CHARACTER�̃f�[�^�擾�̈�m�ێ��s
	if( buf == NULL ){
		OS_Printf( "ERROR : GF_GBL_NTRCHR_CharLoad -load\n" );
		return NULL;
	}
#endif	// OSP_ERR_BGL_NTRCHR_LOAD

	if( NNS_G2dGetUnpackedBGCharacterData( *buf, &dat ) == TRUE ){
#ifdef	OSP_BGL_NTRCHR_LOAD		// NITRO-CHARACTER�̃f�[�^�T�C�Y
		OS_Printf( "GF_GBL_NTRCHR_CharLoad -size %d\n", dat->szByte );
#endif	// OSP_BGL_NTRCHR_LOAD
	}

	return dat;
}

//--------------------------------------------------------------------------------------------
/**
 * NITRO-CHARACTER�̃p���b�g�f�[�^��W�J
 *
 * @param	mem		�W�J�ꏊ
 * @param	mode	�w��q�[�v�̈��`
 * @param	path	�t�@�C���p�X
 *
 * @return	�p���b�g�f�[�^
 *
 * @li		pal->pRawData = �p���b�g�f�[�^
 * @li		pal->szByte   = �T�C�Y
 */
//--------------------------------------------------------------------------------------------
NNSG2dPaletteData * GF_BGL_NTRCHR_PalLoad( void ** mem, int mode, const char * path )
{
	NNSG2dPaletteData * pal;

	*mem = sys_LoadFile( mode, path );

#ifdef	OSP_ERR_BGL_NTRCHR_LOAD		// NITRO-CHARACTER�̃f�[�^�擾�̈�m�ێ��s
	if( mem == NULL ){
		OS_Printf( "ERROR : GF_GBL_NTRCHR_PalLoad -load\n" );
		return NULL;
	}
#endif	// OSP_ERR_BGL_NTRCHR_LOAD

	if( NNS_G2dGetUnpackedPaletteData( *mem, &pal ) == TRUE ){
#ifdef	OSP_BGL_NTRCHR_LOAD		// NITRO-CHARACTER�̃f�[�^�T�C�Y
		OS_Printf( "GF_GBL_NTRCHR_PalLoad -size %d\n", pal->szByte );
#endif	// OSP_BGL_NTRCHR_LOAD
	}
	return pal;
}

//--------------------------------------------------------------------------------------------
/**
 * NITRO-CHARACTER�̃X�N���[���f�[�^��ǂݍ���
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 * @param	path	�t�@�C���p�X
 * @param	offs	�I�t�Z�b�g�i�L�����P�ʁj
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_NTRCHR_ScrnLoad( GF_BGL_INI * ini, u8 frmnum, const char * path, u32 offs )
{
	void * buf;
	NNSG2dScreenData * dat;

	buf = sys_LoadFile( ini->heapID, path );

#ifdef	OSP_ERR_BGL_NTRCHR_LOAD		// NITRO-CHARACTER�̃f�[�^�擾�̈�m�ێ��s
	if( buf == NULL ){
		OS_Printf( "ERROR : GF_GBL_NTRCHR_ScrnLoad -load\n" );
		return;
	}
#endif	// OSP_ERR_BGL_NTRCHR_LOAD

	if( NNS_G2dGetUnpackedScreenData( buf, &dat ) == TRUE ){
#ifdef	OSP_BGL_NTRCHR_LOAD		// NITRO-CHARACTER�̃f�[�^�T�C�Y
		OS_Printf( "GF_GBL_NTRCHR_ScrnLoad -size %d\n", dat->szByte );
#endif	// OSP_BGL_NTRCHR_LOAD
		GF_BGL_ScreenBufSet( ini, frmnum, dat->rawData, dat->szByte );
		GF_BGL_LoadScreen( ini, frmnum, dat->rawData, dat->szByte, offs );
	}

	sys_FreeMemory( ini->heapID, buf );
}


//=============================================================================================
//=============================================================================================
//	VBlank�֘A
//=============================================================================================
//=============================================================================================
#define	SCROLL_REQ_M0	( 1 )			// Bit Flag ( Main Disp BG0 )
#define	SCROLL_REQ_M1	( 2 )			// Bit Flag ( Main Disp BG1 )
#define	SCROLL_REQ_M2	( 4 )			// Bit Flag ( Main Disp BG2 )
#define	SCROLL_REQ_M3	( 8 )			// Bit Flag ( Main Disp BG3 )
#define	SCROLL_REQ_S0	( 16 )			// Bit Flag ( Sub Disp BG0 )
#define	SCROLL_REQ_S1	( 32 )			// Bit Flag ( Sub Disp BG1 )
#define	SCROLL_REQ_S2	( 64 )			// Bit Flag ( Sub Disp BG2 )
#define	SCROLL_REQ_S3	( 128 )			// Bit Flag ( Sub Disp BG3 )

static void VBlankScroll( GF_BGL_INI * ini );
static void VBlankLoadScreen( GF_BGL_INI * ini );

//--------------------------------------------------------------------------------------------
/**
 * VBlank�]��
 *
 * @param	ini		BGL�f�[�^
 *
 * @return	none
 *
 * @li	VBlank���ŌĂ�ŉ�����
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_VBlankFunc( GF_BGL_INI * ini )
{
	VBlankScroll( ini );		// �X�N���[��
	VBlankLoadScreen( ini );	// �X�N���[���]��

	ini->scroll_req = 0;
	ini->loadscrn_req = 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���]�� ( VBlank )
 *
 * @param	ini			BGL�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VBlankLoadScreen( GF_BGL_INI * ini )
{
	// Main Disp BG0
	if( ( ini->loadscrn_req & SCROLL_REQ_M0 ) != 0 ){
		GF_BGL_LoadScreenSub(GF_BGL_FRAME0_M,
			ini->bgsys[GF_BGL_FRAME0_M].screen_buf,
			ini->bgsys[GF_BGL_FRAME0_M].screen_buf_ofs * GF_BGL_1SCRDATASIZ,
			ini->bgsys[GF_BGL_FRAME0_M].screen_buf_siz );
	}
	// Main Disp BG1
	if( ( ini->loadscrn_req & SCROLL_REQ_M1 ) != 0 ){
		GF_BGL_LoadScreenSub(GF_BGL_FRAME1_M,
			ini->bgsys[GF_BGL_FRAME1_M].screen_buf,
			ini->bgsys[GF_BGL_FRAME1_M].screen_buf_ofs * GF_BGL_1SCRDATASIZ,
			ini->bgsys[GF_BGL_FRAME1_M].screen_buf_siz );
	}
	// Main Disp BG2
	if( ( ini->loadscrn_req & SCROLL_REQ_M2 ) != 0 ){
		GF_BGL_LoadScreenSub(GF_BGL_FRAME2_M,
			ini->bgsys[GF_BGL_FRAME2_M].screen_buf,
			ini->bgsys[GF_BGL_FRAME2_M].screen_buf_ofs * GF_BGL_1SCRDATASIZ,
			ini->bgsys[GF_BGL_FRAME2_M].screen_buf_siz );
	}
	// Main Disp BG3
	if( ( ini->loadscrn_req & SCROLL_REQ_M3 ) != 0 ){
		GF_BGL_LoadScreenSub(GF_BGL_FRAME3_M,
			ini->bgsys[GF_BGL_FRAME3_M].screen_buf,
			ini->bgsys[GF_BGL_FRAME3_M].screen_buf_ofs * GF_BGL_1SCRDATASIZ,
			ini->bgsys[GF_BGL_FRAME3_M].screen_buf_siz );
	}
	// Sub Disp BG0
	if( ( ini->loadscrn_req & SCROLL_REQ_S0 ) != 0 ){
		GF_BGL_LoadScreenSub(GF_BGL_FRAME0_S,
			ini->bgsys[GF_BGL_FRAME0_S].screen_buf,
			ini->bgsys[GF_BGL_FRAME0_S].screen_buf_ofs * GF_BGL_1SCRDATASIZ,
			ini->bgsys[GF_BGL_FRAME0_S].screen_buf_siz );
	}
	// Sub Disp BG1
	if( ( ini->loadscrn_req & SCROLL_REQ_S1 ) != 0 ){
		GF_BGL_LoadScreenSub(GF_BGL_FRAME1_S,
			ini->bgsys[GF_BGL_FRAME1_S].screen_buf,
			ini->bgsys[GF_BGL_FRAME1_S].screen_buf_ofs * GF_BGL_1SCRDATASIZ,
			ini->bgsys[GF_BGL_FRAME1_S].screen_buf_siz );
	}
	// Sub Disp BG2
	if( ( ini->loadscrn_req & SCROLL_REQ_S2 ) != 0 ){
		GF_BGL_LoadScreenSub(GF_BGL_FRAME2_S,
			ini->bgsys[GF_BGL_FRAME2_S].screen_buf,
			ini->bgsys[GF_BGL_FRAME2_S].screen_buf_ofs * GF_BGL_1SCRDATASIZ,
			ini->bgsys[GF_BGL_FRAME2_S].screen_buf_siz );
	}
	// Sub Disp BG3
	if( ( ini->loadscrn_req & SCROLL_REQ_S3 ) != 0 ){
		GF_BGL_LoadScreenSub(GF_BGL_FRAME3_S,
			ini->bgsys[GF_BGL_FRAME3_S].screen_buf,
			ini->bgsys[GF_BGL_FRAME3_S].screen_buf_ofs * GF_BGL_1SCRDATASIZ,
			ini->bgsys[GF_BGL_FRAME3_S].screen_buf_siz );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���[���]�����N�G�X�g ( VBlank )
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���ԍ�
 *
 * @return	none
 *
 * @li	VBlank����GF_BGL_VBlankFunc(...)���ĂԂ���
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_LoadScreenV_Req( GF_BGL_INI * ini , u8 frmnum )
{
	ini->loadscrn_req |= ( 1 << frmnum );
}

//--------------------------------------------------------------------------------------------
/**
 * VBlank�X�N���[��
 *
 * @param	ini			BGL�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VBlankScroll( GF_BGL_INI * ini )
{
	// Main Disp BG0
	if( ( ini->scroll_req & SCROLL_REQ_M0 ) != 0 ){
		G2_SetBG0Offset(
			ini->bgsys[GF_BGL_FRAME0_M].scroll_x,
			ini->bgsys[GF_BGL_FRAME0_M].scroll_y );
	}
	// Main Disp BG1
	if( ( ini->scroll_req & SCROLL_REQ_M1 ) != 0 ){
		G2_SetBG1Offset(
			ini->bgsys[GF_BGL_FRAME1_M].scroll_x,
			ini->bgsys[GF_BGL_FRAME1_M].scroll_y );
	}
	// Main Disp BG2
	if( ( ini->scroll_req & SCROLL_REQ_M2 ) != 0 ){
		if( ini->bgsys[GF_BGL_FRAME2_M].mode == GF_BGL_MODE_TEXT ){
			G2_SetBG2Offset(
				ini->bgsys[GF_BGL_FRAME2_M].scroll_x,
				ini->bgsys[GF_BGL_FRAME2_M].scroll_y );
		}else{
			MtxFx22	mtx;

			AffineMtxMake_2D(
				&mtx,
				ini->bgsys[GF_BGL_FRAME2_M].rad,
				ini->bgsys[GF_BGL_FRAME2_M].scale_x,
				ini->bgsys[GF_BGL_FRAME2_M].scale_y,
				AFFINE_MAX_360 );
			G2_SetBG2Affine(
				&mtx,
				ini->bgsys[GF_BGL_FRAME2_M].cx,
				ini->bgsys[GF_BGL_FRAME2_M].cy,
				ini->bgsys[GF_BGL_FRAME2_M].scroll_x,
				ini->bgsys[GF_BGL_FRAME2_M].scroll_y );
		}
	}
	// Main Disp BG3
	if( ( ini->scroll_req & SCROLL_REQ_M3 ) != 0 ){
		if( ini->bgsys[GF_BGL_FRAME3_M].mode == GF_BGL_MODE_TEXT ){
			G2_SetBG3Offset(
				ini->bgsys[GF_BGL_FRAME3_M].scroll_x,
				ini->bgsys[GF_BGL_FRAME3_M].scroll_y );
		}else{
			MtxFx22	mtx;

			AffineMtxMake_2D(
				&mtx,
				ini->bgsys[GF_BGL_FRAME3_M].rad,
				ini->bgsys[GF_BGL_FRAME3_M].scale_x,
				ini->bgsys[GF_BGL_FRAME3_M].scale_y,
				AFFINE_MAX_360 );
			G2_SetBG3Affine(
				&mtx,
				ini->bgsys[GF_BGL_FRAME3_M].cx,
				ini->bgsys[GF_BGL_FRAME3_M].cy,
				ini->bgsys[GF_BGL_FRAME3_M].scroll_x,
				ini->bgsys[GF_BGL_FRAME3_M].scroll_y );
		}
	}
	// Sub Disp BG0
	if( ( ini->scroll_req & SCROLL_REQ_S0 ) != 0 ){
		G2S_SetBG0Offset(
			ini->bgsys[GF_BGL_FRAME0_S].scroll_x, ini->bgsys[GF_BGL_FRAME0_S].scroll_y );
	}
	// Sub Disp BG1
	if( ( ini->scroll_req & SCROLL_REQ_S1 ) != 0 ){
		G2S_SetBG1Offset(
			ini->bgsys[GF_BGL_FRAME1_S].scroll_x, ini->bgsys[GF_BGL_FRAME1_S].scroll_y );
	}
	// Sub Disp BG2
	if( ( ini->scroll_req & SCROLL_REQ_S2 ) != 0 ){
		if( ini->bgsys[GF_BGL_FRAME2_S].mode == GF_BGL_MODE_TEXT ){
			G2S_SetBG2Offset(
				ini->bgsys[GF_BGL_FRAME2_S].scroll_x,
				ini->bgsys[GF_BGL_FRAME2_S].scroll_y );
		}else{
			MtxFx22	mtx;

			AffineMtxMake_2D(
				&mtx,
				ini->bgsys[GF_BGL_FRAME2_S].rad,
				ini->bgsys[GF_BGL_FRAME2_S].scale_x,
				ini->bgsys[GF_BGL_FRAME2_S].scale_y,
				AFFINE_MAX_360 );
			G2S_SetBG2Affine(
				&mtx,
				ini->bgsys[GF_BGL_FRAME2_S].cx,
				ini->bgsys[GF_BGL_FRAME2_S].cy,
				ini->bgsys[GF_BGL_FRAME2_S].scroll_x,
				ini->bgsys[GF_BGL_FRAME2_S].scroll_y );
		}
	}
	// Sub Disp BG3
	if( ( ini->scroll_req & SCROLL_REQ_S3 ) != 0 ){
		if( ini->bgsys[GF_BGL_FRAME3_S].mode == GF_BGL_MODE_TEXT ){
			G2S_SetBG3Offset(
				ini->bgsys[GF_BGL_FRAME3_S].scroll_x,
				ini->bgsys[GF_BGL_FRAME3_S].scroll_y );
		}else{
			MtxFx22	mtx;

			AffineMtxMake_2D(
				&mtx,
				ini->bgsys[GF_BGL_FRAME3_S].rad,
				ini->bgsys[GF_BGL_FRAME3_S].scale_x,
				ini->bgsys[GF_BGL_FRAME3_S].scale_y,
				AFFINE_MAX_360 );
			G2S_SetBG3Affine(
				&mtx,
				ini->bgsys[GF_BGL_FRAME3_S].cx,
				ini->bgsys[GF_BGL_FRAME3_S].cy,
				ini->bgsys[GF_BGL_FRAME3_S].scroll_x,
				ini->bgsys[GF_BGL_FRAME3_S].scroll_y );
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �X�N���[�����N�G�X�g
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���ԍ�
 * @param	mode		�X�N���[�����[�h
 * @param	value		�X�N���[���l
 *
 * @return	none
 *
 * @li	VBlank����GF_BGL_VBlankFunc(...)���ĂԂ���
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_ScrollReq( GF_BGL_INI * ini, u8 frmnum, u8 mode, int value )
{
	ScrollParamSet( &ini->bgsys[frmnum], mode, value );
	ini->scroll_req |= ( 1 << frmnum );
}

//--------------------------------------------------------------------------------------------
/**
 * ��]�p�x�ύX���N�G�X�g
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���ԍ�
 * @param	mode		�p�x�ύX���[�h
 * @param	value		��]�l
 *
 * @return	none
 *
 * @li	VBlank����GF_BGL_VBlankFunc(...)���ĂԂ���
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_RadianSetReq( GF_BGL_INI * ini, u8 frmnum, u8 mode, u16 value )
{
	RadianParamSet( &ini->bgsys[frmnum], mode, value );
	ini->scroll_req |= ( 1 << frmnum );
}

//--------------------------------------------------------------------------------------------
/**
 * ��]�p�x�Z�b�g
 *
 * @param	ini			BGL�t���[���f�[�^
 * @param	mode		�p�x�ύX���[�h
 * @param	value		��]�l
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void RadianParamSet( GF_BGL_SYS_INI * ini, u8 mode, u16 value )
{
	switch( mode ){
	case GF_BGL_RADION_SET:
		ini->rad = value;
		break;
	case GF_BGL_RADION_INC:
		ini->rad += value;
		break;
	case GF_BGL_RADION_DEC:
		ini->rad -= value;
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �g�k�ύX���N�G�X�g
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���ԍ�
 * @param	mode		�g�k�ύX���[�h
 * @param	value		�ύX�l
 *
 * @return	none
 *
 * @li	VBlank����GF_BGL_VBlankFunc(...)���ĂԂ���
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_ScaleSetReq( GF_BGL_INI * ini, u8 frmnum, u8 mode, fx32 value )
{
	ScaleParamSet( &ini->bgsys[frmnum], mode, value );
	ini->scroll_req |= ( 1 << frmnum );
}

//--------------------------------------------------------------------------------------------
/**
 * �g�k�ύX�Z�b�g
 *
 * @param	ini			BGL�t���[���f�[�^
 * @param	mode		�g�k�ύX���[�h
 * @param	value		�ύX�l
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ScaleParamSet( GF_BGL_SYS_INI * ini, u8 mode, fx32 value )
{
	switch( mode ){
	case GF_BGL_SCALE_X_SET:
		ini->scale_x = value;
		break;
	case GF_BGL_SCALE_X_INC:
		ini->scale_x += value;
		break;
	case GF_BGL_SCALE_X_DEC:
		ini->scale_x -= value;
		break;
	case GF_BGL_SCALE_Y_SET:
		ini->scale_y = value;
		break;
	case GF_BGL_SCALE_Y_INC:
		ini->scale_y += value;
		break;
	case GF_BGL_SCALE_Y_DEC:
		ini->scale_y -= value;
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ��]���S���W�ύX���N�G�X�g
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���ԍ�
 * @param	mode		�ύX���[�h
 * @param	value		�ύX�l
 *
 * @return	none
 *
 * @li	VBlank����GF_BGL_VBlankFunc(...)���ĂԂ���
 */
//--------------------------------------------------------------------------------------------
void GF_BGL_RotateCenterSetReq( GF_BGL_INI * ini, u8 frmnum, u8 mode, int value )
{
	CenterParamSet( &ini->bgsys[frmnum], mode, value );
	ini->scroll_req |= ( 1 << frmnum );
}

//--------------------------------------------------------------------------------------------
/**
 * ��]���S���W�ύX�Z�b�g
 *
 * @param	ini			BGL�t���[���f�[�^
 * @param	mode		�ύX���[�h
 * @param	value		�ύX�l
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CenterParamSet( GF_BGL_SYS_INI * ini, u8 mode, int value )
{
	switch( mode ){
	case GF_BGL_CENTER_X_SET:
		ini->cx = value;
		break;
	case GF_BGL_CENTER_X_INC:
		ini->cx += value;
		break;
	case GF_BGL_CENTER_X_DEC:
		ini->cx -= value;
		break;
	case GF_BGL_CENTER_Y_SET:
		ini->cy = value;
		break;
	case GF_BGL_CENTER_Y_INC:
		ini->cy += value;
		break;
	case GF_BGL_CENTER_Y_DEC:
		ini->cy -= value;
		break;
	}
}


//=============================================================================================
//=============================================================================================
//	���̑�
//=============================================================================================
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �w����W�̃h�b�g���`�F�b�N
 *
 * @param	ini		BGL�f�[�^
 * @param	frmnum	BG�t���[���ԍ�
 * @param	px		X���W
 * @param	py		Y���W
 * @param	pat		����f�[�^
 *
 * @retval	"TRUE = ����f�[�^(pat)�ɂ���"
 * @retval	"FALSE = ����f�[�^(pat)�ɂȂ�"
 *
 * @li	�P�U�F�̏ꍇ�Apat�̓r�b�g�Ń`�F�b�N
 *			��j*pat = 0xfffd;
 *				�J���[0��1�̏ꍇ�AFALSE���Ԃ�
 *
 * @li	�Q�T�U�F�̏ꍇ�Apat�̍Ō��0xffff��t��
 *			��jpat[] = { 88, 124, 223, 0xffff };
 *				�J���[88, 124, 223�ȊO��FALSE���Ԃ�
 */
//--------------------------------------------------------------------------------------------
u8 GF_BGL_DotCheck( GF_BGL_INI * ini, u8 frmnum, u16 px, u16 py, u16 * pat )
{
	u8 * cgx;
	u16	pos;
	u8	chr_x, chr_y;
	u8	dot;
	u8	i;

	if( ini->bgsys[frmnum].screen_buf == NULL ){
		return FALSE;
	}

	pos = GetScreenPos( (u8)(px>>3), (u8)(py>>3), ini->bgsys[frmnum].screen_siz );
	cgx = (u8 *)GF_BGL_CgxGet( frmnum );

	chr_x = (u8)(px&7);
	chr_y = (u8)(py&7);

	if( ini->bgsys[frmnum].col_mode == GX_BG_COLORMODE_16 ){

		u16 * scrn;
		u8 * buf;

		scrn = (u16 *)ini->bgsys[frmnum].screen_buf;
		buf  = sys_AllocMemoryLo( ini->heapID, 64 );

		cgx += ( ( scrn[pos] & 0x3ff ) << 5 );
		for( i=0; i<32; i++ ){
			buf[ (i<<1) ]   = cgx[i] & 0x0f;
			buf[ (i<<1)+1 ] = cgx[i] >> 4;
		}

		CgxFlipCheck( ini, (u8)((scrn[pos]>>10)&3), buf );

		dot = buf[ chr_x+(chr_y<<3) ];
		sys_FreeMemoryEz( buf );

		if( ( pat[0] & (1<<dot) ) != 0 ){
			return TRUE;
		}

	}else{
		if( ini->bgsys[ frmnum ].mode != GF_BGL_MODE_AFFINE ){

			u16 * scrn;
			u8 * buf;

			scrn = (u16 *)ini->bgsys[frmnum].screen_buf;
			buf  = sys_AllocMemoryLo( ini->heapID, 64 );

			memcpy( buf, &cgx[(scrn[pos]&0x3ff)<<6], 64 );
			CgxFlipCheck( ini, (u8)((scrn[pos]>>10)&3), buf );

			dot = buf[ chr_x+(chr_y<<3) ];
			sys_FreeMemoryEz(  buf );

		}else{
			u8 * scrn = (u8 *)ini->bgsys[frmnum].screen_buf;

			dot = cgx[ (scrn[pos]<<6) + chr_x + (chr_y<<3) ];
		}

		i = 0;
		while(1){
			if( pat[i] == 0xffff ){ break; }

			if( (u8)pat[i] == dot ){
				return TRUE;
			}
		}
	}

	return FALSE;
}

static void CgxFlipCheck( GF_BGL_INI* ini, u8 flip, u8 * buf )
{
	u8 * tmp;
	u8	i, j;

	if( flip == 0 ){ return; }

	tmp = sys_AllocMemoryLo( ini->heapID, 64 );

	if( flip & 1 ){
		for( i=0; i<8; i++ ){
			for( j=0; j<8; j++ ){
				tmp[ i*8+j ] = buf[ i*8+(7-j) ];
			}
		}
		memcpy( buf, tmp, 64 );
	}

	if( flip & 2 ){
		for( i=0; i<8; i++ ){
			memcpy( &tmp[i*8], &buf[(7-i)*8], 8 );
		}
		memcpy( buf, tmp, 64 );
	}

	sys_FreeMemoryEz( tmp );
}
