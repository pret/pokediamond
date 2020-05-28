//============================================================================================
/**
 * @file	boxv_exwin.c
 * @brief	�{�b�N�X�����ʁ@�`�扺�����i����E�B���h�E�j
 * @author	taya
 * @date	2005.10.04
 */
//============================================================================================
#include  "common.h"
#include  "system\arc_util.h"
#include  "system\numfont.h"
#include  "system\brightness.h"
#include  "system\fontproc.h"
#include  "msgdata\msg.naix"
#include  "poketool\monsno.h"

#include  "box_arc.h"
#include  "box_view.h"
#include  "box_common.h"


enum {
	TRAYICON_WRITE_OX = 9,
	TRAYICON_WRITE_OY = 10,
	TRAYICON_WRITE_WIDTH = 14,
	TRAYICON_WRITE_HEIGHT = 12,
	TRAYICON_DOT_WRITE_OX = 10,
	TRAYICON_DOT_WRITE_OY = 12,
	TRAYICON_SIZE_X = 32,
	TRAYICON_SIZE_Y = 32,


	TRAYICON_DISP_X = 32,
	TRAYICON_DISP_XSPC = 32,
	TRAYICON_DISP_Y = 88,
	TRAYICON_DISP_COUNT = 7,

	// �g���C�A�C�R���\���̈�i�h�b�g�P�ʁB�E�B���h�E�Ɏg���j
	TRAYICON_DISP_START_XPOS = TRAYICON_DISP_X - (TRAYICON_SIZE_X/2),
	TRAYICON_DISP_END_XPOS = TRAYICON_DISP_X + (TRAYICON_DISP_COUNT-1)*TRAYICON_DISP_XSPC + (TRAYICON_SIZE_X/2),
	TRAYICON_DISP_START_YPOS = TRAYICON_DISP_Y - (TRAYICON_SIZE_Y/2),
	TRAYICON_DISP_END_YPOS = TRAYICON_DISP_Y + (TRAYICON_SIZE_Y/2),
	TRAYICON_FADE_TIME = BOX_TIMER(4),



	JUMPWIN_WRITE_XPOS = 0,	// �L�����P�ʕ\���ʒu
	JUMPWIN_WRITE_YPOS = 5,	// �L�����P�ʕ\���ʒu
	JUMPWIN_WIDTH = 32,		// �L�����P�ʃT�C�Y
	JUMPWIN_HEIGHT = 10,	// �L�����P�ʃT�C�Y

	JUMPWIN_DISPEFFECT_SPEED = BOX_EFF_SPEED(1),


	ITEMWIN_WRITE_XPOS = 0,
	ITEMWIN_WRITE_YPOS = 24,
	ITEMWIN_WRITE_WIDTH = 32,
	ITEMWIN_WRITE_HEIGHT = 7,
	ITEMWIN_SCROLL_START = 0,
	ITEMWIN_SCROLL_END = (ITEMWIN_WRITE_HEIGHT * 8),

	ITEMICON_DISP_X = 18,
	ITEMICON_DISP_Y = 168 + ITEMWIN_SCROLL_END,


	// BitmapWindow �ݒ�
	WIN_TRAYNAME_X = 10,
	WIN_TRAYNAME_Y = JUMPWIN_WRITE_YPOS + 1,
	WIN_TRAYNAME_WIDTH = 12,
	WIN_TRAYNAME_HEIGHT = 2,
	WIN_TRAYNAME_CHARSIZE = WIN_TRAYNAME_WIDTH*WIN_TRAYNAME_HEIGHT,

	WIN_POKECNT_X = 3,
	WIN_POKECNT_Y = JUMPWIN_WRITE_YPOS + 8,
	WIN_POKECNT_WIDTH = 26,
	WIN_POKECNT_HEIGHT = 1,
	WIN_POKECNT_CHARSIZE = WIN_POKECNT_WIDTH*WIN_POKECNT_HEIGHT,

	WIN_ITEMINFO_X = 5,
	WIN_ITEMINFO_Y = 25,
	WIN_ITEMINFO_WIDTH = 27,
	WIN_ITEMINFO_HEIGHT = 6,

	// BitmapWindow �L�����I�t�Z�b�g
	WIN_TRAYNAME_CHAROFS = 128,
	WIN_POKECNT_CHAROFS = WIN_TRAYNAME_CHAROFS + WIN_TRAYNAME_CHARSIZE,
	WIN_ITEMINFO_CHAROFS = WIN_POKECNT_CHAROFS + WIN_POKECNT_CHARSIZE,

	// BitmapWindow �J���[�ݒ�
	WIN_TRAYNAME_LETTER_COLOR = 0x02,
	WIN_TRAYNAME_SHADOW_COLOR = 0x08,
	WIN_TRAYNAME_GROUND_COLOR = 0x07,

	WIN_POKECNT_LETTER_COLOR = 0x02,
	WIN_POKECNT_SHADOW_COLOR = 0x0d,
	WIN_POKECNT_GROUND_COLOR = 0x04,

	WIN_ITEMINFO_LETTER_COLOR = 0x02,
	WIN_ITEMINFO_SHADOW_COLOR = 0x01,
	WIN_ITEMINFO_GROUND_COLOR = 0x04,

	WIN_TRAYNAME_CENTER_XPOS = ((WIN_TRAYNAME_WIDTH/2)*8),

	WIN_POKECNT_WRITE_XSPC = TRAYICON_DISP_XSPC,

};

/** �E�B���h�E�^�C�v */
enum {
	WIN_TRAYNAME = 0,
	WIN_POKECNT,
	WIN_ITEMINFO,
	WIN_MAX,
};

/** �E�B���h�E�G�t�F�N�g�^�C�v*/
typedef enum {
	JUMPWIN_EFF_DISP,
	JUMPWIN_EFF_DELETE,
}JUMPWIN_EFFECT_TYPE;

//==============================================================
// Prototype
//==============================================================
static int DispFirstTrayNumber( EXWIN_VIEW_WORK* wk );
static void TrayIconCharStoreInit( EXWIN_VIEW_WORK* wk );
static void TrayIconCharStoreSet( EXWIN_VIEW_WORK* wk, u32 trayno );
static void TrayIconCharStoreTrans( EXWIN_VIEW_WORK* wk, u32 pos, u32 trayno );
static void TrayIconMainViewInit( EXWIN_VIEW_WORK* wk );
static void TrayIconMainViewDelete( EXWIN_VIEW_WORK* wk );
static void TrayIconMainViewFormat( EXWIN_VIEW_WORK* wk );
static void TrayNameWrite( EXWIN_VIEW_WORK* wk );
static void TrayNameClear( EXWIN_VIEW_WORK* wk );
static void PokeCntWrite( EXWIN_VIEW_WORK* wk );
static void PokeCntClear( EXWIN_VIEW_WORK* wk );
static void SetJumpWinEffectTask( EXWIN_VIEW_WORK* wk, JUMPWIN_EFFECT_TYPE type);
static void DeleteJumpWinEffectTask( TCB_PTR tcb, void* wk_adrs );
static BOOL WaitJumpWinEffectTask( EXWIN_VIEW_WORK* wk );
static void JumpWinDispEffectTask( TCB_PTR tcb, void* wk_adrs );
static void JumpWinDeleteEffectTask( TCB_PTR tcb, void* wk_adrs );
static void ItemInfoWinDispTask(TCB_PTR tcb, void* wk_ptr);
static void ItemInfoWinClearTask(TCB_PTR tcb, void* wk_ptr);
static void SetupItemActor( EXWIN_VIEW_WORK* wk, u32 item );
static void ScrollItemIconActor( EXWIN_VIEW_WORK* wk, fx32 ypos );
static void DeleteItemIconActor( EXWIN_VIEW_WORK* wk );



//------------------------------------------------------------------
/**
 * ����������
 *
 * @param   wk			���[�N�|�C���^
 * @param   vwk			�`�惁�C�����[�N�|�C���^
 * @param   vpara		�`��p�����[�^�|�C���^
 * @param   bgl			BGL�V�X�e���|�C���^
 * @param   actsys		�A�N�^�[�V�X�e���|�C���^
 *
 * @retval  BOOL		TRUE�Ő���
 */
//------------------------------------------------------------------
BOOL BoxAppView_ExWinInit( EXWIN_VIEW_WORK* wk, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, GF_BGL_INI* bgl, CLACT_SET_PTR actsys )
{
	int i;

	wk->vwk = vwk;
	wk->bgl = bgl;
	wk->vpara = vpara;
	wk->actsys = actsys;

	ArcUtil_BgCharSet( ARC_BOX_GRA, NARC_box_bg0_lz_ncgr, bgl, FRM_MAIN_MESSAGE, 0, 0, TRUE, HEAPID_BOX_VIEW );

	{
		NNSG2dPaletteData* palData;
		void* allocBuf;

		allocBuf = ArcUtil_PalDataGet(ARC_BOX_GRA, NARC_box_wp_image_nclr, &palData, HEAPID_BOX_VIEW);
		MI_CpuCopy16(palData->pRawData, &(wk->trayIconPalBuf[0][0]), 0x40);
		sys_FreeMemoryEz(allocBuf);

		allocBuf = ArcUtil_PalDataGet(ARC_BOX_GRA, NARC_box_tray_icon_nclr, &palData, HEAPID_BOX_VIEW);
		MI_CpuCopy16(palData->pRawData, &(wk->trayIconPalBuf[0][32]), 0x20);
		sys_FreeMemoryEz(allocBuf);


		{
			int i;
			fx32 step, sub;

			step = 16 << FX32_SHIFT;
			sub = step / (TRAYICON_FADE_MAX-1);

			for(i=TRAYICON_FADE_MAX-1; i>=1; i--)
			{
				BoxAppView_PalFade(wk->trayIconPalBuf[0], wk->trayIconPalBuf[i], TRAYICON_PAL_COLOR_NUM, 
					0x7fff, (step>>FX32_SHIFT));
				step -= sub;
			}
			DC_FlushRange( wk->trayIconPalBuf, TRAYICON_FADE_MAX*TRAYICON_PAL_SIZE );
		}

		GX_LoadOBJPltt( wk->trayIconPalBuf[TRAYICON_FADE_MAX-1], OBJPAL_TRAYICON_TOP*0x20, TRAYICON_PAL_SIZE );
		GXS_LoadOBJPltt( wk->trayIconPalBuf[0], OBJPAL_TRAYICON_TOP*0x20, TRAYICON_PAL_SIZE );
	}

	wk->iconCharBuf = ArcUtil_CharDataGet( ARC_BOX_GRA, NARC_box_tray_icon_lz_ncgr, TRUE, &(wk->iconCharData), HEAPID_BOX_VIEW );
	wk->iconCellBuf = ArcUtil_CellBankDataGet( ARC_BOX_GRA, NARC_box_tray_icon_lz_ncer, TRUE, &(wk->iconCellData), HEAPID_BOX_VIEW );
	wk->itemwinScrnBuf = ArcUtil_ScrnDataGet( ARC_BOX_GRA, NARC_box_bg0a_lz_nscr, TRUE, &(wk->itemwinScrnData), HEAPID_BOX_VIEW );
	wk->jumpwinScrnBuf = ArcUtil_ScrnDataGet( ARC_BOX_GRA, NARC_box_bg0b_lz_nscr, TRUE, &(wk->jumpwinScrnData), HEAPID_BOX_VIEW );

	wk->numfont = NUMFONT_Create( WIN_POKECNT_LETTER_COLOR, WIN_POKECNT_SHADOW_COLOR, WIN_POKECNT_GROUND_COLOR, HEAPID_BOX_VIEW );
	wk->tmpbuf = STRBUF_Create( 500, HEAPID_BOX_VIEW );

	wk->bmpwin = NULL;

	wk->trayIconBmpHeader.adrs = wk->iconCharData->pRawData;
	wk->trayIconBmpHeader.size_x = TRAYICON_SIZE_X;
	wk->trayIconBmpHeader.size_y = TRAYICON_SIZE_Y;

	wk->mm_itemInfo = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_iteminfo_dat, HEAPID_BOX_VIEW);

	for(i = 0; i < BOX_MAX_TRAY; i++)
	{
		wk->trayIconAct[i] = NULL;
	}

	if(	(wk->iconCharBuf == NULL)
	||	(wk->iconCellBuf == NULL)
	||	(wk->jumpwinScrnBuf == NULL)
	||	(wk->itemwinScrnBuf == NULL)
	||	(wk->numfont == NULL)
	||	(wk->tmpbuf == NULL)
	){
		return FALSE;
	}


	return TRUE;
}
//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
void BoxAppView_ExWinSetup( EXWIN_VIEW_WORK* wk )
{
	static const BMPWIN_DAT  windat[] = {
		{
			FRM_MAIN_MESSAGE,
			WIN_TRAYNAME_X, WIN_TRAYNAME_Y, WIN_TRAYNAME_WIDTH, WIN_TRAYNAME_HEIGHT,
			PAL_MAIN_STATUS3, WIN_TRAYNAME_CHAROFS
		},{
			FRM_MAIN_MESSAGE,
			WIN_POKECNT_X, WIN_POKECNT_Y, WIN_POKECNT_WIDTH, WIN_POKECNT_HEIGHT,
			PAL_MAIN_STATUS3, WIN_POKECNT_CHAROFS
		},{
			FRM_MAIN_MESSAGE,
			WIN_ITEMINFO_X, WIN_ITEMINFO_Y, WIN_ITEMINFO_WIDTH, WIN_ITEMINFO_HEIGHT,
			PAL_MAIN_STATUS3, WIN_ITEMINFO_CHAROFS
		}
	};

	wk->bmpwin = GF_BGL_BmpWinAllocGet( HEAPID_BOX_VIEW, NELEMS(windat) );
	if( wk->bmpwin )
	{
		int i;

		for(i = 0; i < NELEMS(windat); i++)
		{
			GF_BGL_BmpWinAddEx( wk->bgl, &wk->bmpwin[i], &windat[i] );
		}
	}
}
//------------------------------------------------------------------
/**
 * �I������
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_ExWinQuit( EXWIN_VIEW_WORK* wk )
{
	if( wk->mm_itemInfo )
	{
		MSGMAN_Delete( wk->mm_itemInfo );
	}
	if( wk->iconCharBuf )
	{
		sys_FreeMemoryEz( wk->iconCharBuf );
	}

	if( wk->iconCellBuf )
	{
		sys_FreeMemoryEz( wk->iconCellBuf );
	}

	if( wk->jumpwinScrnBuf )
	{
		sys_FreeMemoryEz( wk->jumpwinScrnBuf );
	}

	if( wk->itemwinScrnBuf )
	{
		sys_FreeMemoryEz( wk->itemwinScrnBuf );
	}

	if( wk->numfont )
	{
		NUMFONT_Delete( wk->numfont );
	}

	if( wk->tmpbuf )
	{
		STRBUF_Delete( wk->tmpbuf );
	}


	if( wk->bmpwin )
	{
		int i;
		for(i = 0; i < WIN_MAX; i++)
		{
			GF_BGL_BmpWinDel( &(wk->bmpwin[i]) );
		}
		sys_FreeMemoryEz( wk->bmpwin );
	}
}
//------------------------------------------------------------------
/**
 * �{�b�N�X�I���E�B���h�E�\���J�n
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_ExWin_JumpWinDispStart( EXWIN_VIEW_WORK* wk )
{
	wk->center_trayno = BoxAppVPara_GetJumpWinCenterTrayNumber( wk->vpara );
	TrayIconMainViewInit( wk );
	SetJumpWinEffectTask( wk, JUMPWIN_EFF_DISP );
}
//------------------------------------------------------------------
/**
 * �{�b�N�X�I���E�B���h�E�\���I���҂�
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  BOOL	TRUE�ŏI��
 */
//------------------------------------------------------------------
BOOL BoxAppView_ExWin_JumpWinDispWait( EXWIN_VIEW_WORK* wk )
{
	return WaitJumpWinEffectTask( wk );
}
//------------------------------------------------------------------
/**
 * �{�b�N�X�I���E�B���h�E�\���X�V
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
void BoxAppView_ExWin_JumpWinUpdate( EXWIN_VIEW_WORK* wk )
{
	wk->center_trayno = BoxAppVPara_GetJumpWinCenterTrayNumber( wk->vpara );

	TrayIconMainViewFormat( wk );
	TrayNameWrite( wk );
	PokeCntWrite( wk );
}
//------------------------------------------------------------------
/**
 * �{�b�N�X�I���E�B���h�E�����J�n
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
void BoxAppView_ExWin_JumpWinDelStart( EXWIN_VIEW_WORK* wk )
{
	SetJumpWinEffectTask( wk, JUMPWIN_EFF_DELETE );
}
//------------------------------------------------------------------
/**
 * �{�b�N�X�I���E�B���h�E�����I���҂�
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  BOOL	TRUE�ŏI��
 */
//------------------------------------------------------------------
BOOL BoxAppView_ExWin_JumpWinDelWait( EXWIN_VIEW_WORK* wk )
{
	return WaitJumpWinEffectTask( wk );
}

//------------------------------------------------------------------
/**
 * �g���C�A�C�R���̃L�����f�[�^�쐬�E�]���E�v���L�V�쐬
 *
 * @param   wk			���[�N�|�C���^
 * @param   trayno		�g���C�i���o�[
 * @param   charpos		�]����L�����i���o�[
 * @param   vramType	�]����VRAM
 * @param   proxy		�v���L�V�쐬��ϐ��A�h���X�iNULL���Ɠ]���̂ݍs���j
 *
 */
//------------------------------------------------------------------
void BoxAppView_ExWin_TransTrayIconCharData( EXWIN_VIEW_WORK* wk, u32 trayno, u32 charpos, NNS_G2D_VRAM_TYPE vramType, NNSG2dImageProxy* proxy )
{
	const BOX_DATA* boxData;
	POKEMON_PASO_PARAM* ppp;
	u32 x, y, pos, monsno;
	u8 color, fastFlag;

	boxData = BoxAppVPara_GetBoxData( wk->vpara );

// �ǎ��C���[�W�F�œh��Ԃ�
	color = OBJPAL_TRAYICON_WP*0x10 + BOXDAT_GetWallPaperNumber( boxData, trayno );
	GF_BGL_BmpFill256( &(wk->trayIconBmpHeader), TRAYICON_WRITE_OX, TRAYICON_WRITE_OY, 
							TRAYICON_WRITE_WIDTH, TRAYICON_WRITE_HEIGHT, color );

	// �|�P�����C���[�W�F�h�b�g��ł�
	for( y = 0, pos = 0; y < BOX_MAX_RAW; y++ )
	{
		for( x = 0; x < BOX_MAX_COLUMN; x++ )
		{
			ppp = BOXDAT_GetPokeDataAddress( boxData, trayno, pos++ );
			fastFlag = PokePasoParaFastModeOn( ppp );
			monsno = PokePasoParaGet( ppp, ID_PARA_monsno, NULL );
			if( monsno )
			{
				if( PokePasoParaGet( ppp, ID_PARA_tamago_flag, NULL ) == FALSE )
				{
					u16 form = PokePasoParaGet( ppp, ID_PARA_form_no, NULL );
					color = PokeFormNoPersonalParaGet( monsno, form, ID_PER_color );
				}
				else
				{
					color = (monsno != MONSNO_MANAFI)? COLOR_WHITE : COLOR_BLUE;
				}

				// �p�[�\�i���J���[���p���b�g�i���o�[�ɕϊ��B�B���ǎ��J���[�Ƌ��L���Ă�̂ł��Ȃ�L�c�L�c�ł�
				{
					static const u8 color_translate[] = {
					//  ��    ��    ��    ��    ��    ��    ��    �D    ��    ��
						0x0e, 0x0f, 0x05, 0x01, 0x0d, 0x0c, 0x06, 0x0b, 0x0a, 0x09,
					};

					color = OBJPAL_TRAYICON_POKE*0x10 + color_translate[color];

				}

				GF_BGL_BmpFill256( &(wk->trayIconBmpHeader), TRAYICON_DOT_WRITE_OX+x*2, TRAYICON_DOT_WRITE_OY+y*2, 
							2, 2, color );
			}
			PokePasoParaFastModeOff( ppp, fastFlag );
		}
	}


	if( proxy )
	{
		switch( vramType ){
		case NNS_G2D_VRAM_TYPE_2DMAIN:
			wk->iconCharData->mapingType = GX_GetOBJVRamModeChar();
			break;
		case NNS_G2D_VRAM_TYPE_2DSUB:
			wk->iconCharData->mapingType = GXS_GetOBJVRamModeChar();
			break;
		}
		NNS_G2dLoadImage1DMapping( wk->iconCharData, charpos*0x20, vramType, proxy );
	}
	else
	{
		DC_FlushRange( wk->iconCharData->pRawData, wk->iconCharData->szByte );
		switch( vramType ){
		case NNS_G2D_VRAM_TYPE_2DMAIN:
			GX_LoadOBJ( wk->iconCharData->pRawData, charpos*0x20, wk->iconCharData->szByte );
			break;
		case NNS_G2D_VRAM_TYPE_2DSUB:
			GXS_LoadOBJ( wk->iconCharData->pRawData, charpos*0x20, wk->iconCharData->szByte );
			break;
		}
	}
}



//------------------------------------------------------------------
/**
 * �g���C�A�C�R���̃Z���f�[�^�A�h���X��Ԃ�
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  NNSG2dCellDataBank*		�Z���f�[�^�A�h���X
 */
//------------------------------------------------------------------
NNSG2dCellDataBank* BoxAppView_ExWin_GetTrayIconCellDataAdrs( EXWIN_VIEW_WORK* wk )
{
	return wk->iconCellData;
}











//------------------------------------------------------------------
/**
 * �\������擪�̃g���C�i���o�[
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  int		�g���C�i���o�[
 */
//------------------------------------------------------------------
static int DispFirstTrayNumber( EXWIN_VIEW_WORK* wk )
{
	int trayno = wk->center_trayno - ( TRAYICON_DISP_COUNT / 2 );
	if( trayno < 0 ){
		trayno += BOX_MAX_TRAY;
	}
	return trayno;
}


static void TrayIconCharStoreInit( EXWIN_VIEW_WORK* wk )
{
	int i;
	for(i=0; i<BOX_MAX_TRAY; i++)
	{
		wk->trayIconCharCreateFlag[i] = FALSE;
	}
}
static void TrayIconCharStoreSet( EXWIN_VIEW_WORK* wk, u32 trayno )
{
	MI_CpuCopy32(wk->iconCharData->pRawData, wk->trayIconCharBuf[trayno], TRAYICON_CHAR_BYTESIZE );
	DC_FlushRange( wk->trayIconCharBuf, TRAYICON_CHAR_BYTESIZE );
	wk->trayIconCharCreateFlag[trayno] = TRUE;
}

static void TrayIconCharStoreTrans( EXWIN_VIEW_WORK* wk, u32 pos, u32 trayno )
{
	u32 charpos = OBJCHAR_TRAYICON_POS+OBJCHAR_TRAYICON_SIZE*pos;

	if( wk->trayIconCharCreateFlag[trayno] )
	{
		GX_LoadOBJ( wk->trayIconCharBuf[trayno], charpos*0x20, TRAYICON_CHAR_BYTESIZE );
	}
	else
	{
		NNSG2dImageProxy proxy;

		NNS_G2dInitImageProxy( &proxy );
		BoxAppView_ExWin_TransTrayIconCharData( wk, trayno, charpos, NNS_G2D_VRAM_TYPE_2DMAIN, &proxy );
		TrayIconCharStoreSet( wk, trayno );
	}
}
static u32 heavysub( u32 i, u32 num )
{
	return i*num*4;
}
static u32 heavyfunc( void* ptr )
{
	u32 num = (u32)ptr;
	u32 i;

	for(i=0; i<3000; i++)
	{
		num += heavysub( i, (u32)ptr );
	}
	return num;
}
//------------------------------------------------------------------
/**
 * �\������g���C�A�C�R�����쐬�i�\���͂��Ȃ��j
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void TrayIconMainViewInit( EXWIN_VIEW_WORK* wk )
{
	CLACT_HEADER  header;
	BOX_ICON_SYS*  iconSys;
	NNSG2dImageProxy  proxy;
	VecFx32  vec;
	int i, trayno;

	TrayIconCharStoreInit( wk );

	iconSys = BoxAppView_GetIconSysWork( wk->vwk );

	BoxAppView_SetActHeader( &header, NULL, BoxAppView_GetObjPlttProxy( wk->vwk ),
			wk->iconCellData, iconSys->anmBank, 0 );

	trayno = DispFirstTrayNumber( wk );

	for(i=0; i<TRAYICON_DISP_COUNT; i++)
	{
		NNS_G2dInitImageProxy( &proxy );
		BoxAppView_ExWin_TransTrayIconCharData( wk, trayno,
			OBJCHAR_TRAYICON_POS+OBJCHAR_TRAYICON_SIZE*i, NNS_G2D_VRAM_TYPE_2DMAIN, &proxy );
		header.pImageProxy = &proxy;

		// �\�����I�t��O�Ɋ��荞�݂�����ƈ�u�\������Ă��܂��̂�
		// �ŏ��͉�ʊO�̍��W��ݒ肵�Ă���
		wk->trayIconAct[i] = BoxAppView_AddActor( wk->actsys, &header,
			512, 256,
			ACTPRI_TRAY_ICON_MIN, NNS_G2D_VRAM_TYPE_2DMAIN );

		GF_ASSERT(wk->trayIconAct[i]!=NULL);

		// �\���t���O���I�t������ɍ��W�����߂Đݒ�
		CLACT_SetDrawFlag( wk->trayIconAct[i], FALSE );
		VEC_Set(&vec, FX32_CONST(TRAYICON_DISP_X+i*TRAYICON_DISP_XSPC), FX32_CONST(TRAYICON_DISP_Y), 0 );
		CLACT_SetMatrix( wk->trayIconAct[i], &vec );

		TrayIconCharStoreSet( wk, trayno );
		if(++trayno >= BOX_MAX_TRAY){
			trayno = 0;
		}
	}

	for(i=0; i<BOX_MAX_TRAY; i++)
	{
		wk->pokeCount[i] = BOXDAT_GetPokeExistCount( BoxAppVPara_GetBoxData(wk->vpara), i );
	}
}
//------------------------------------------------------------------
/**
 * �S�g���C�A�C�R�����폜
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void TrayIconMainViewDelete( EXWIN_VIEW_WORK* wk )
{
	int i;

	for(i=0; i<TRAYICON_DISP_COUNT; i++)
	{
		if( wk->trayIconAct[i] != NULL )
		{
			CLACT_Delete( wk->trayIconAct[i] );
			wk->trayIconAct[i] = NULL;
		}
	}
}
//------------------------------------------------------------------
/**
 * ���݃Z���^�[�̃g���C�i���o�[����Ƀg���C�A�C�R������E�\��
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void TrayIconMainViewFormat( EXWIN_VIEW_WORK* wk )
{
	int trayno, i;

	trayno = DispFirstTrayNumber( wk );

	for(i=0; i<TRAYICON_DISP_COUNT; i++)
	{
//		CLACT_SetMatrix( wk->trayIconAct[p], &vec );
//		CLACT_SetDrawFlag( wk->trayIconAct[p], TRUE );
		TrayIconCharStoreTrans( wk, i, trayno );
		CLACT_SetDrawFlag( wk->trayIconAct[i], TRUE );
		if(++trayno >= BOX_MAX_TRAY){ trayno = 0; }
	}


//	for(i=0; i < (BOX_MAX_TRAY-TRAYICON_DISP_COUNT); i++)
//	{
//		CLACT_SetDrawFlag( wk->trayIconAct[p], FALSE );
//		if(++p >= BOX_MAX_TRAY){ p = 0; }
//	}
}
//------------------------------------------------------------------
/**
 * ���݃Z���^�[�̃g���C���`��
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void TrayNameWrite( EXWIN_VIEW_WORK* wk )
{
	const BOX_DATA* boxData;
	GF_BGL_BMPWIN* win;
	u32 strwidth, xpos;

	boxData = BoxAppVPara_GetBoxData( wk->vpara );
	win = &wk->bmpwin[WIN_TRAYNAME];

	BOXDAT_GetBoxName( boxData, wk->center_trayno, wk->tmpbuf );
	strwidth = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->tmpbuf, 0 );
	xpos = WIN_TRAYNAME_CENTER_XPOS - ( strwidth / 2 );

	GF_BGL_BmpWinDataFill( win, WIN_TRAYNAME_GROUND_COLOR );
	GF_STR_PrintColor( win, FONT_SYSTEM, wk->tmpbuf, xpos, 0, MSG_NO_PUT, 
						GF_PRINTCOLOR_MAKE( WIN_TRAYNAME_LETTER_COLOR, WIN_TRAYNAME_SHADOW_COLOR, WIN_TRAYNAME_GROUND_COLOR ),
						NULL
					);
	GF_BGL_BmpWinCgxOn( win );
}
//------------------------------------------------------------------
/**
 * �g���C���E�B���h�E�\���N���A
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void TrayNameClear( EXWIN_VIEW_WORK* wk )
{
	GF_BGL_BMPWIN* win = &wk->bmpwin[WIN_TRAYNAME];
	GF_BGL_BmpWinDataFill( win, WIN_TRAYNAME_GROUND_COLOR );
	GF_BGL_BmpWinCgxOn( win );
}
//------------------------------------------------------------------
/**
 * ���݃Z���^�[�̃g���C����Ƀ|�P�������`��
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void PokeCntWrite( EXWIN_VIEW_WORK* wk )
{
	s32 p, i;
	GF_BGL_BMPWIN* win;

	win = &wk->bmpwin[WIN_POKECNT];

	GF_BGL_BmpWinDataFill( win, WIN_POKECNT_GROUND_COLOR );
	p = DispFirstTrayNumber( wk );

	for(i = 0; i < TRAYICON_DISP_COUNT; i++)
	{
		NUMFONT_WriteNumber( wk->numfont, wk->pokeCount[p], 2, NUMFONT_MODE_ZERO, win, WIN_POKECNT_WRITE_XSPC*i, 0 );
		if(++p >= BOX_MAX_TRAY){ p = 0; }
	}

	GF_BGL_BmpWinCgxOn( win );
}
//------------------------------------------------------------------
/**
 * �g���C���E�B���h�E�\���N���A
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void PokeCntClear( EXWIN_VIEW_WORK* wk )
{
	GF_BGL_BMPWIN* win = &wk->bmpwin[WIN_POKECNT];
	GF_BGL_BmpWinDataFill( win, WIN_POKECNT_GROUND_COLOR );
	GF_BGL_BmpWinCgxOn( win );
}


/*====================================================================================*/
/*  �ȉ��A�E�B���h�E�̕\���E�����G�t�F�N�g����                                        */
/*====================================================================================*/


//----------------------------------------------
/**
 *  �{�b�N�X�I���E�B���h�E�G�t�F�N�g���[�N
 */
//----------------------------------------------
typedef struct {
	EXWIN_VIEW_WORK*  parentWork;
	u8  seq;
	u8  workval;
	BOOL  brightCheckFlag;
}JUMPWIN_EFFECT_WORK;

//------------------------------------------------------------------
/**
 * �I���E�B���h�E�\���G�t�F�N�g�̃^�X�N�o�^
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void SetJumpWinEffectTask( EXWIN_VIEW_WORK* wk, JUMPWIN_EFFECT_TYPE type)
{
	static const TCB_FUNC functbl[] = {
		JumpWinDispEffectTask,
		JumpWinDeleteEffectTask,
	};

	JUMPWIN_EFFECT_WORK* taskwk = sys_AllocMemory( HEAPID_BOX_VIEW, sizeof(JUMPWIN_EFFECT_WORK) );

	if( taskwk )
	{
		taskwk->parentWork = wk;
		taskwk->seq = 0;
		taskwk->workval = 0;

		// �p���b�g�R�{���̓]������������̂ŁA�O�̂���VIntr���g��Ȃ�
		wk->effectTask = TCB_Add( functbl[type], taskwk, TASKPRI_VIEW_COMMAND_SUB );

		if( wk->effectTask == NULL )
		{
			sys_FreeMemoryEz( taskwk );
		}
	}
}
//------------------------------------------------------------------
/**
 * �I���E�B���h�E�G�t�F�N�g�̃^�X�N�폜�i�^�X�N�{�̂���Ă΂��j
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void DeleteJumpWinEffectTask( TCB_PTR tcb, void* wk_adrs )
{
	JUMPWIN_EFFECT_WORK* taskwk = (JUMPWIN_EFFECT_WORK*)wk_adrs;

	taskwk->parentWork->effectTask = NULL;
	sys_FreeMemoryEz( taskwk );
	TCB_Delete( tcb );
}
//------------------------------------------------------------------
/**
 * �{�b�N�X�I���E�B���h�E�\���G�t�F�N�g�̃^�X�N�I���҂�
 *
 * @param   wk			���[�N�|�C���^
 *
 * @retval  BOOL		TRUE�ŏI��
 */
//------------------------------------------------------------------
static BOOL WaitJumpWinEffectTask( EXWIN_VIEW_WORK* wk )
{
	return (wk->effectTask == NULL);
}

//------------------------------------------------------------------
/**
 * �{�b�N�X�I���E�B���h�E�\���G�t�F�N�g�̃^�X�N�{��
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void JumpWinDispEffectTask( TCB_PTR tcb, void* wk_adrs )
{
	JUMPWIN_EFFECT_WORK* taskwk = (JUMPWIN_EFFECT_WORK*)wk_adrs;
	EXWIN_VIEW_WORK* wk = taskwk->parentWork;

	switch( taskwk->seq ){
	// �E�B���h�E���̂��ʂ���Əo�Ă���
	case 0:
		taskwk->workval += JUMPWIN_DISPEFFECT_SPEED;

		if( (taskwk->workval*2) < JUMPWIN_HEIGHT )
		{
			// �X�N���[���`��x���S
			u32 cy = JUMPWIN_WRITE_YPOS+(JUMPWIN_HEIGHT/2);
			GF_BGL_ScrWrite( wk->bgl, FRM_MAIN_MESSAGE, wk->jumpwinScrnData->rawData,
						JUMPWIN_WRITE_XPOS, cy-taskwk->workval, JUMPWIN_WIDTH, taskwk->workval );

			GF_BGL_ScrWriteExpand( wk->bgl, FRM_MAIN_MESSAGE, 
						JUMPWIN_WRITE_XPOS, cy, JUMPWIN_WIDTH, taskwk->workval,
						wk->jumpwinScrnData->rawData, 0, JUMPWIN_HEIGHT-taskwk->workval,
						JUMPWIN_WIDTH, JUMPWIN_HEIGHT );
		}
		else
		{
			GF_BGL_ScrWrite( wk->bgl, FRM_MAIN_MESSAGE, wk->jumpwinScrnData->rawData,
						JUMPWIN_WRITE_XPOS, JUMPWIN_WRITE_YPOS, JUMPWIN_WIDTH, JUMPWIN_HEIGHT );
			taskwk->seq++;
		}
		GF_BGL_LoadScreenReq( wk->bgl, FRM_MAIN_MESSAGE );
		taskwk->workval = TRAYICON_FADE_MAX-1;
		break;

	case 1:
		GX_LoadOBJPltt( wk->trayIconPalBuf[taskwk->workval], OBJPAL_TRAYICON_TOP*0x20, TRAYICON_PAL_SIZE );
		TrayIconMainViewFormat( wk );
		taskwk->seq++;
		break;

	case 2:
		if( taskwk->workval ){
			taskwk->workval--;
		}
		GX_LoadOBJPltt( wk->trayIconPalBuf[taskwk->workval], OBJPAL_TRAYICON_TOP*0x20, TRAYICON_PAL_SIZE );

		if(taskwk->workval == 0 )
		{
//			GX_SetVisibleWnd( GX_WNDMASK_NONE );
			GF_BGL_BmpWinMakeScrn( &wk->bmpwin[WIN_TRAYNAME] );
			GF_BGL_BmpWinMakeScrn( &wk->bmpwin[WIN_POKECNT] );
			TrayNameWrite( wk );
			PokeCntWrite( wk );
			GF_BGL_LoadScreenReq( wk->bgl, FRM_MAIN_MESSAGE );
			taskwk->seq++;
		}
		break;

	case 3:
		DeleteJumpWinEffectTask( tcb, taskwk );
		break;
	}
}
//------------------------------------------------------------------
/**
 * �{�b�N�X�I���E�B���h�E�����G�t�F�N�g�̃^�X�N�{��
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void JumpWinDeleteEffectTask( TCB_PTR tcb, void* wk_adrs )
{
	JUMPWIN_EFFECT_WORK* taskwk = (JUMPWIN_EFFECT_WORK*)wk_adrs;
	EXWIN_VIEW_WORK* wk = taskwk->parentWork;

	switch( taskwk->seq ){
	case 0:
		TrayIconMainViewDelete( wk );
		TrayNameClear( wk );
		PokeCntClear( wk );
		taskwk->seq++;
		break;

	case 1:
		GF_BGL_ScrFill( wk->bgl, FRM_MAIN_MESSAGE, 0x0000, JUMPWIN_WRITE_XPOS, JUMPWIN_WRITE_YPOS,
				JUMPWIN_WIDTH, JUMPWIN_HEIGHT, GF_BGL_SCRWRT_PALIN );

		taskwk->workval += JUMPWIN_DISPEFFECT_SPEED;
		if( (taskwk->workval*2) < JUMPWIN_HEIGHT )
		{
			// �X�N���[���`��x���S
			u32 cy = JUMPWIN_WRITE_YPOS+(JUMPWIN_HEIGHT/2);
			GF_BGL_ScrWrite( wk->bgl, FRM_MAIN_MESSAGE, wk->jumpwinScrnData->rawData,
						JUMPWIN_WRITE_XPOS, JUMPWIN_WRITE_YPOS+taskwk->workval,
						JUMPWIN_WIDTH, (JUMPWIN_HEIGHT/2) - taskwk->workval );

			GF_BGL_ScrWriteExpand( wk->bgl, FRM_MAIN_MESSAGE, 
						JUMPWIN_WRITE_XPOS, cy, JUMPWIN_WIDTH, (JUMPWIN_HEIGHT/2) - taskwk->workval,
						wk->jumpwinScrnData->rawData, 0, JUMPWIN_HEIGHT-taskwk->workval,
						JUMPWIN_WIDTH, JUMPWIN_HEIGHT );
		}
		else
		{
			taskwk->seq++;
		}
		GF_BGL_LoadScreenReq( wk->bgl, FRM_MAIN_MESSAGE );
		break;

	case 2:
		DeleteJumpWinEffectTask( tcb, taskwk );
	}
}











/*====================================================================================*/
/*  �A�C�e�������E�B���h�E����                                                        */
/*====================================================================================*/

//----------------------------------------------
/**
 *  �A�C�e�������E�B���h�E�\���G�t�F�N�g���[�N
 */
//----------------------------------------------
typedef struct {
	EXWIN_VIEW_WORK*  parentWork;
	GF_BGL_INI*       bgl;
	fx32  pos;
	fx32  endpos;
	fx32  speed;
	u16   timer;
	u16   seq;
}ITEMWIN_EFFECT_WORK;


//------------------------------------------------------------------
/**
 * �A�C�e�������E�B���h�E�\���J�n
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_ExWin_ItemInfoWinDispStart( EXWIN_VIEW_WORK* wk )
{
	enum {
		EFFECT_FRAMES = 6,
	};

	ITEMWIN_EFFECT_WORK* effwk = sys_AllocMemory( HEAPID_BOX_VIEW, sizeof(ITEMWIN_EFFECT_WORK) );
	

	if( effwk )
	{
		u32 itemNo = BoxAppVPara_GetInfoItemNumber( wk->vpara );

		GF_BGL_ScrollSet( wk->bgl, FRM_MAIN_MESSAGE, GF_BGL_SCROLL_Y_SET, ITEMWIN_SCROLL_START );

		GF_BGL_ScrWrite( wk->bgl, FRM_MAIN_MESSAGE, wk->itemwinScrnData->rawData, 
			ITEMWIN_WRITE_XPOS, ITEMWIN_WRITE_YPOS, ITEMWIN_WRITE_WIDTH, ITEMWIN_WRITE_HEIGHT );


		GF_BGL_BmpWinDataFill(&wk->bmpwin[WIN_ITEMINFO],WIN_ITEMINFO_GROUND_COLOR);
		MSGMAN_GetString( wk->mm_itemInfo, itemNo, wk->tmpbuf );
		GF_STR_PrintColor( &wk->bmpwin[WIN_ITEMINFO], FONT_SYSTEM, wk->tmpbuf, 0, 0, MSG_NO_PUT, 
			GF_PRINTCOLOR_MAKE(WIN_ITEMINFO_LETTER_COLOR,WIN_ITEMINFO_SHADOW_COLOR,WIN_ITEMINFO_GROUND_COLOR), NULL );

		GF_BGL_BmpWinOn( &wk->bmpwin[WIN_ITEMINFO] );
//		GF_BGL_LoadScreenReq( wk->bgl, FRM_MAIN_MESSAGE );

		

//		GF_BGL_ScrFill( wk->bgl, FRM_MAIN_MESSAGE, 0x0000, 0, 0, 32, 32, GF_BGL_SCRWRT_PALIN );

		SetupItemActor( wk, itemNo );


		effwk->seq = 0;
		effwk->parentWork =  wk;
		effwk->bgl = wk->bgl;
		effwk->pos = (ITEMWIN_SCROLL_START << FX32_SHIFT);
		effwk->endpos = ITEMWIN_SCROLL_END << FX32_SHIFT;
		effwk->speed = ( effwk->endpos - effwk->pos ) / EFFECT_FRAMES;
		effwk->timer = EFFECT_FRAMES;

		wk->effectTask = BoxAppView_VTaskAdd( ItemInfoWinDispTask, effwk, TASKPRI_V_SUB );
	}
}

//------------------------------------------------------------------
/**
 * �A�C�e�������E�B���h�E�\���I���҂�
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  BOOL	TRUE�ŏI��
 */
//------------------------------------------------------------------
BOOL BoxAppView_ExWin_ItemInfoWinDispWait( EXWIN_VIEW_WORK* wk )
{
	return wk->effectTask == NULL;
}

static void ItemInfoWinWorkFreeReserve( void* wk_adrs )
{
	EXWIN_VIEW_WORK* wk = wk_adrs;
	wk->effectTask = NULL;
}

static void ItemInfoWinDispTask(TCB_PTR tcb, void* wk_ptr)
{
	ITEMWIN_EFFECT_WORK* wk = wk_ptr;

	switch( wk->seq ){
	case 0:
		wk->seq++;
		break;

	case 1:
		if( wk->timer )
		{
			wk->timer--;
			wk->pos += wk->speed;
			GF_BGL_ScrollSet( wk->bgl, FRM_MAIN_MESSAGE, GF_BGL_SCROLL_Y_SET, (wk->pos >> FX32_SHIFT) );
			ScrollItemIconActor( wk->parentWork, (ITEMICON_DISP_Y << FX32_SHIFT) - wk->pos );
		}
		else
		{
			GF_BGL_ScrollSet( wk->bgl, FRM_MAIN_MESSAGE, GF_BGL_SCROLL_Y_SET, (wk->endpos >> FX32_SHIFT) );
			ScrollItemIconActor( wk->parentWork, (ITEMICON_DISP_Y << FX32_SHIFT) - wk->endpos );

			BoxAppView_IrqMemoryFreeReq( wk, ItemInfoWinWorkFreeReserve, wk->parentWork );
			TCB_Delete(tcb);
		}
		break;
	}
}


//------------------------------------------------------------------
/**
 * �A�C�e�������E�B���h�E�����J�n
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_ExWin_ItemInfoWinClearStart( EXWIN_VIEW_WORK* wk )
{
	enum {
		EFFECT_FRAMES = 6,
	};

	ITEMWIN_EFFECT_WORK* effwk = sys_AllocMemory( HEAPID_BOX_VIEW, sizeof(ITEMWIN_EFFECT_WORK) );

	if( effwk )
	{
		effwk->seq = 0;
		effwk->parentWork =  wk;
		effwk->bgl = wk->bgl;
		effwk->pos = ITEMWIN_SCROLL_END << FX32_SHIFT;
		effwk->endpos = ITEMWIN_SCROLL_START << FX32_SHIFT;
		effwk->speed = ( effwk->endpos - effwk->pos ) / EFFECT_FRAMES;
		effwk->timer = EFFECT_FRAMES;

		wk->effectTask = BoxAppView_VTaskAdd( ItemInfoWinClearTask, effwk, TASKPRI_V_SUB );
	}
}
//------------------------------------------------------------------
/**
 * �A�C�e�������E�B���h�E�����I���҂�
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  BOOL	TRUE�ŏI��
 */
//------------------------------------------------------------------
BOOL BoxAppView_ExWin_ItemInfoWinClearWait( EXWIN_VIEW_WORK* wk )
{
	if( wk->effectTask == NULL )
	{
		GF_BGL_ScrollSet( wk->bgl, FRM_MAIN_MESSAGE, GF_BGL_SCROLL_Y_SET, 0 );
		DeleteItemIconActor(wk);
		return TRUE;
	}
	return FALSE;
}

static void ItemInfoWinClearWorkFreeReserve( void* wk_adrs )
{
	EXWIN_VIEW_WORK* wk = wk_adrs;
	wk->effectTask = NULL;
}

static void ItemInfoWinClearTask(TCB_PTR tcb, void* wk_ptr)
{
	ITEMWIN_EFFECT_WORK* wk = wk_ptr;

	if( wk->timer )
	{
		wk->timer--;
		wk->pos += wk->speed;
		GF_BGL_ScrollSet( wk->bgl, FRM_MAIN_MESSAGE, GF_BGL_SCROLL_Y_SET, (wk->pos >> FX32_SHIFT) );
		ScrollItemIconActor( wk->parentWork, (ITEMICON_DISP_Y << FX32_SHIFT) - wk->pos );
	}
	else
	{
		GF_BGL_ScrollSet( wk->bgl, FRM_MAIN_MESSAGE, GF_BGL_SCROLL_Y_SET, (wk->endpos >> FX32_SHIFT) );
		ScrollItemIconActor( wk->parentWork, (ITEMICON_DISP_Y << FX32_SHIFT) - wk->endpos );
		GF_BGL_ScrFill( wk->bgl, FRM_MAIN_MESSAGE, 0x0000, 0, 0, 32, 32, GF_BGL_SCRWRT_PALIN );
		GF_BGL_LoadScreenReq( wk->bgl, FRM_MAIN_MESSAGE );
//		wk->parentWork->effectTask = NULL;
//		sys_FreeMemoryEz(wk);
		BoxAppView_IrqMemoryFreeReq( wk, ItemInfoWinClearWorkFreeReserve, wk->parentWork );
		TCB_Delete(tcb);
	}
}

//------------------------------------------------------------------
/**
 * �A�C�e���A�C�R���A�N�^�[�Z�b�g�A�b�v
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void SetupItemActor( EXWIN_VIEW_WORK* wk, u32 item )
{
	if( item != ITEM_DUMMY_ID )
	{
		CLACT_HEADER  header;
		BOX_ICON_SYS*  iconSys;
		NNSG2dImageProxy  proxy;
		NNSG2dCharacterData*  charData;
		void * loadBuf;

		iconSys = BoxAppView_GetIconSysWork( wk->vwk );

		BoxAppView_SetActHeader( &header, &proxy, BoxAppView_GetObjPlttProxy( wk->vwk ),
				iconSys->item_cellBank, iconSys->item_anmBank, 0 );

		NNS_G2dInitImageProxy( &proxy );

		loadBuf = ArcUtil_CharDataGet( ARC_ITEMICON, GetItemIndex(item,ITEM_GET_ICON_CGX), FALSE, &charData, HEAPID_BOX_VIEW );
		charData->mapingType = GX_GetOBJVRamModeChar();
		NNS_G2dLoadImage1DMapping( charData, OBJCHAR_ITEMICON_INFO_POS*0x20, NNS_G2D_VRAM_TYPE_2DMAIN, &proxy );

		ArcUtil_PalSet(ARC_ITEMICON, GetItemIndex(item,ITEM_GET_ICON_PAL), PALTYPE_MAIN_OBJ,
					OBJPAL_ITEMICON_INFOWIN*0x20, 0x20, HEAPID_BOX_VIEW );

		wk->itemIconAct = BoxAppView_AddActor( wk->actsys, &header, 
				ITEMICON_DISP_X, ITEMICON_DISP_Y,
				ACTPRI_ITEMICON_INFO, NNS_G2D_VRAM_TYPE_2DMAIN );

		if( wk->itemIconAct )
		{
			CLACT_PaletteNoChg( wk->itemIconAct, OBJPAL_ITEMICON_INFOWIN );
		}

		sys_FreeMemoryEz(loadBuf);
	}
}

static void ScrollItemIconActor( EXWIN_VIEW_WORK* wk, fx32 ypos )
{
	if( wk->itemIconAct )
	{
		VecFx32 mtx;

		mtx.x = ITEMICON_DISP_X << FX32_SHIFT;
		mtx.y = ypos;
		mtx.z = 0;

		CLACT_SetMatrix( wk->itemIconAct, &mtx );
	}
}
static void DeleteItemIconActor( EXWIN_VIEW_WORK* wk )
{
	if( wk->itemIconAct )
	{
		CLACT_Delete( wk->itemIconAct );
	}
}

