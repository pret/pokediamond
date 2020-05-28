//============================================================================================
/**
 * @file	boxv.c
 * @brief	�{�b�N�X�����ʁ@�`�惁�C��
 * @author	taya
 * @date	2005.09.09
 */
//============================================================================================
#include  "common.h"
#include  "system\arc_util.h"
#include  "system\clact_util.h"
#include  "system\render_oam.h"
#include  "system\brightness.h"
#include  "system\wipe.h"
#include  "system\fontproc.h"

#include  "box_arc.h"
#include  "box_view.h"
#include  "box_common.h"


//==============================================================
// BG 
//==============================================================
#define BG1_CHARBASE	(GX_BG_CHARBASE_0x18000)	// BG1 = ���b�Z�[�W�E�B���h�E��
#define BG1_SCRBASE		(GX_BG_SCRBASE_0xe000)
#define BG2_CHARBASE	(GX_BG_CHARBASE_0x00000)	// BG2 = �X�e�[�^�X�ʓ�
#define BG2_SCRBASE		(GX_BG_SCRBASE_0xe800)
#define BG3_CHARBASE	(GX_BG_CHARBASE_0x10000)	// BG3 = �g���C
#define BG3_SCRBASE		(GX_BG_SCRBASE_0xf000)

#define SUB_BG0_CHARBASE	(GX_BG_CHARBASE_0x10000)	// Sub BG0 = �{�b�N�X���`��E�B���h�E
#define SUB_BG0_SCRBASE		(GX_BG_SCRBASE_0xf000)
#define SUB_BG1_CHARBASE	(GX_BG_CHARBASE_0x00000)	// Sub BG1 = ���E���[���Z���N�^
#define SUB_BG1_SCRBASE		(GX_BG_SCRBASE_0xd000)
#define SUB_BG2_CHARBASE	(GX_BG_CHARBASE_0x00000)	// Sub BG2 = �A�C�R���\���̈�̑�
#define SUB_BG2_SCRBASE		(GX_BG_SCRBASE_0xe000)
#define SUB_BG3_CHARBASE	(GX_BG_CHARBASE_0x00000)	// Sub BG3 = �w�i
#define SUB_BG3_SCRBASE		(GX_BG_SCRBASE_0xf800)


//==============================================================
// const
//==============================================================
#define BOX_ACT_MAX		(128)
#define BOX_BLEND_EVA	(0x06)
#define BOX_BLEND_EVB	(0x0a)

//==============================================================
// work
//==============================================================

enum {
	STORE_COMMAND_MAX = 4,		///< �����ɓ�������R�}���h��
};


struct _BOXAPP_VIEW_WORK {
	TCB_PTR   mainTask;
	TCB_PTR   vintrTask;
	TCB_PTR   command[ STORE_COMMAND_MAX ];


	CLACT_SET_PTR				clactSys;
	CLACT_U_EASYRENDER_DATA		renddata;		// �ȈՃ����_�[�f�[�^����
	NNSG2dImagePaletteProxy		plttProxy;

	SOFT_SPRITE_MANAGER*		spriteManager;

	GF_BGL_INI*				bgl;
	const BOXAPP_VPARAM*	vpara;

	BOX_ICON_SYS			iconSysWork;
	TRAY_VIEW_WORK			trayWork;
	CURSOR_VIEW_WORK		cursorWork;
	BUTTON_VIEW_WORK		buttonWork;
	STATUS_VIEW_WORK		statusWork;
	MSG_VIEW_WORK			msgWork;
	EXWIN_VIEW_WORK			exWinWork;
	PARTY_VIEW_WORK			partyWork;
	REEL_VIEW_WORK*			reelWork;
	ITEMICON_VIEW_WORK*		itemIconWork;
	COMPARE_VIEW_WORK*		compareWork;

	const BOXAPP_WORK*		mainWork;
};

//----------------------------------------------------
/**
 *  �R�}���h�^�X�N���K�������[�N�w�b�_
 */
//----------------------------------------------------
typedef struct {
	u32   commandNumber;
	u16   storeNumber;
	u16   seq;

	u16   val_1;
	u16   val_2;

	BOXAPP_VIEW_WORK *vwk;
	void* work;

}COMMAND_WORK_HEADER;

//==============================================================
// Prototype
//==============================================================
static void BoxAppView_MainTask( TCB_PTR tcb, void* wk_adrs );
static void DeleteCommand( COMMAND_WORK_HEADER* header );
static void BoxVBlankTask(TCB_PTR tcb, void* wk_adrs);
static void CmdInit(TCB_PTR tcb, void* wk_adrs);
static void CmdNormalIn( TCB_PTR tcb, void* wk_adrs );
static void CmdFadeIn( TCB_PTR tcb, void* wk_adrs );
static void CmdFadeOut( TCB_PTR tcb, void* wk_adrs );
static void CmdTrayChange( TCB_PTR tcb, void* wk_adrs );
static void CmdCursorMove( TCB_PTR tcb, void* wk_adrs );
static void CmdStatusUpdate( TCB_PTR tcb, void* wk_adrs );
static void CmdStatusMarkingUpdate( TCB_PTR tcb, void* wk_adrs );
static void CmdStatusClear( TCB_PTR tcb, void* wk_adrs );
static void CmdPokemonCatch( TCB_PTR tcb, void* wk_adrs );
static void CmdPokemonPut( TCB_PTR tcb, void* wk_adrs );
static void CmdPokemonChange( TCB_PTR tcb, void* wk_adrs );
static void CmdCatchPokeAzukeru( TCB_PTR tcb, void* wk_adrs );
static void CmdPointPokeAzukeru( TCB_PTR tcb, void* wk_adrs );
static void CmdCatchPokeNigasu( TCB_PTR tcb, void* wk_adrs );
static void CmdTrayPokeNigasu( TCB_PTR tcb, void* wk_adrs );
static void CmdPartyPokeNigasu( TCB_PTR tcb, void* wk_adrs );
static void CmdItemInfoDisp( TCB_PTR tcb, void* wk_adrs );
static void CmdItemInfoClear( TCB_PTR tcb, void* wk_adrs );
static void CmdItemWithDraw( TCB_PTR tcb, void* wk_adrs );
static void CmdItemSet( TCB_PTR tcb, void* wk_adrs );
static void CmdItemSwap( TCB_PTR tcb, void* wk_adrs );
static void CmdItemPokeUpdate( TCB_PTR tcb, void* wk_adrs );
static void CmdItemIconRestore( TCB_PTR tcb, void* wk_adrs );
static void CmdMsgDisp( TCB_PTR tcb, void* wk_adrs );
static void CmdMenuDisp( TCB_PTR tcb, void* wk_adrs );
static void CmdMsgClear( TCB_PTR tcb, void* wk_adrs );
static void CmdMenuClear( TCB_PTR tcb, void* wk_adrs );
static void CmdMenuCursorUpdate( TCB_PTR tcb, void* wk_adrs );
static void CmdMenuMarkUpdate( TCB_PTR tcb, void* wk_adrs );
static void CmdJumpWinDisp( TCB_PTR tcb, void* wk_adrs );
static void CmdJumpWinUpdate( TCB_PTR tcb, void* wk_adrs );
static void CmdJumpWinClear( TCB_PTR tcb, void* wk_adrs );
static void CmdWallPaperChange( TCB_PTR tcb, void* wk_adrs );
static void CmdButtonPushAction( TCB_PTR tcb, void* wk_adrs );
static void CmdPartyTrayOpen(TCB_PTR tcb, void* wk_adrs);
static void CmdPartyTrayClose(TCB_PTR tcb, void* wk_adrs);
static void CmdPartyIconCloseup(TCB_PTR tcb, void* wk_adrs);
static void CmdPartyLastIconCloseup( TCB_PTR tcb, void* wk_adrs );
static void CmdIconLimitModeUpdate( TCB_PTR tcb, void* wk_adrs );
static void CmdSubLCD_ModeChange( TCB_PTR tcb, void* wk_adrs );
static void CmdSubLCD_MoveIcon( TCB_PTR tcb, void* wk_adrs );
static void CmdSubLCD_MarkIconUpdate( TCB_PTR tcb, void* wk_adrs );
static void CmdChangeExpertMode( TCB_PTR tcb, void* wk_adrs );
static void CmdStartAreaSelect( TCB_PTR tcb, void* wk_adrs );
static void CmdEndAreaSelect( TCB_PTR tcb, void* wk_adrs );
static void CmdUpdateAreaSelect( TCB_PTR tcb, void* wk_adrs );
static void CmdCatchAreaSelectPoke( TCB_PTR tcb, void* wk_adrs );
static void CmdSwitchCompareSide( TCB_PTR tcb, void* wk_adrs );
static void CmdSwitchCompareSideByButton( TCB_PTR tcb, void* wk_adrs );
static void CmdChangeComparePage( TCB_PTR tcb, void* wk_adrs );
static void CmdClose( TCB_PTR tcb, void* wk_adrs );
static void SetupBGRegistParam( BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara );
static void SetupBGGraphicData( BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara );
static void Box3D_BGInit(void);
static void InitMainOBJ( BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara );
static int calc_tray_direction( u32 from, u32 to );
static void FreeMemoryWorkInit( void );
static void FreeMemoryFlush( void );

//------------------------------------------------------------------
/**
 * �`�揉����
 *
 * @param   vwk		���[�N�|�C���^�̃A�h���X
 *
 * @retval  BOOL	TRUE�Ő���
 */
//------------------------------------------------------------------
BOOL BoxAppView_Init( BOXAPP_VIEW_WORK** vwk, const BOXAPP_VPARAM* vpara, const BOXAPP_WORK* mainwk )
{
	BOXAPP_VIEW_WORK* wk = sys_AllocMemory(HEAPID_BOX_VIEW, sizeof(BOXAPP_VIEW_WORK));

	if( wk != NULL )
	{
		wk->vpara = vpara;
		wk->bgl = GF_BGL_BglIniAlloc( HEAPID_BOX_VIEW );

		if( wk->bgl != NULL )
		{
			u32 i;
			BOOL flg = 1;

			sys_VBlankFuncChange( NULL, NULL );
			sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

			GF_Disp_GX_VisibleControlInit();
			GF_Disp_GXS_VisibleControlInit();
			GX_SetVisiblePlane( 0 );
			GXS_SetVisiblePlane( 0 );

			GX_SetOBJVRamModeChar( GX_OBJVRAMMODE_CHAR_1D_64K );
			GXS_SetOBJVRamModeChar( GX_OBJVRAMMODE_CHAR_1D_32K );

			NNS_G2dInitOamManagerModule();
			REND_OAMInit( 0, 128, 0, 32, 0, 128, 0, 32, HEAPID_BOX_VIEW );

			wk->clactSys = CLACT_U_SetEasyInit( BOX_ACT_MAX, &wk->renddata, HEAPID_BOX_VIEW );
			CLACT_U_SetSubSurfaceMatrix( &(wk->renddata), 0, (SUBSURFACE_YOFS<<FX32_SHIFT) );

			NNS_G2dInitImagePaletteProxy( &(wk->plttProxy) );
			ArcUtil_PalSysLoad(ARC_BOX_GRA, NARC_box_m_obj_nclr, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 
				HEAPID_BOX_VIEW, &(wk->plttProxy));


			FontProc_LoadBitData(FONT_SYSTEM, HEAPID_BOX_VIEW);

			wk->spriteManager = SoftSpriteInit( HEAPID_BOX_VIEW );

			for(i = 0; i < STORE_COMMAND_MAX; i++)
			{
				wk->command[i] = NULL;
			}
			FreeMemoryWorkInit();
			*vwk = wk;

			flg &= BoxAppView_IconSysInit( &(wk->iconSysWork), wk, wk->vpara, wk->clactSys );
			flg &= BoxAppView_TrayInit( &(wk->trayWork), wk, wk->vpara, wk->bgl, wk->clactSys );
			flg &= BoxAppView_CursorInit( &(wk->cursorWork), wk, wk->vpara, wk->clactSys );
			flg &= BoxAppView_ButtonInit( &(wk->buttonWork), wk, wk->vpara, wk->clactSys );
			flg &= BoxAppView_StatusInit( &(wk->statusWork), wk, wk->vpara, wk->bgl, wk->clactSys, BoxApp_GetMsgManager(mainwk) );
			flg &= BoxAppView_MsgInit( &(wk->msgWork), wk, wk->vpara, wk->bgl, wk->clactSys, BoxApp_GetMsgManager(mainwk), BoxApp_GetWordSet(mainwk), BoxApp_GetTalkWinType(mainwk) );
			flg &= BoxAppView_ExWinInit( &(wk->exWinWork), wk, wk->vpara, wk->bgl, wk->clactSys );
			flg &= BoxAppView_PartyInit( &(wk->partyWork), wk, wk->vpara, wk->bgl, wk->clactSys );
			flg &= BoxAppView_Reel_Init( &(wk->reelWork), wk, wk->vpara, wk->bgl, wk->clactSys );
			flg &= BoxAppView_ItemIconInit( &(wk->itemIconWork), wk, wk->vpara, wk->bgl, wk->clactSys );
			flg &= BoxAppView_CompareInit( &(wk->compareWork), wk, wk->vpara, wk->bgl, wk->clactSys, BoxApp_GetMsgManager(mainwk) );


			wk->mainWork = mainwk;
			wk->mainTask = TCB_Add( BoxAppView_MainTask, wk, TASKPRI_VIEW_TRANS );
			wk->vintrTask = BoxAppView_VTaskAdd( BoxVBlankTask, wk, TASKPRI_V_MAIN );

			return flg;
		}
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * �`�惁�C���^�X�N
 *
 * @param   wk		
 */
//------------------------------------------------------------------
static void BoxAppView_MainTask( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* wk = (BOXAPP_VIEW_WORK*)wk_adrs;

	FreeMemoryFlush();

	G3X_Reset();
	G3X_ResetMtxStack();
	NNS_G2dSetupSoftwareSpriteCamera();

	SoftSpriteMain( wk->spriteManager );

	G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
}
//------------------------------------------------------------------
/**
 * �`��I��
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_End( BOXAPP_VIEW_WORK* wk )
{
	sys_VBlankFuncChange(NULL, NULL);
	TCB_Delete( wk->mainTask );
	TCB_Delete( wk->vintrTask );

	BoxAppView_CompareQuit( wk->compareWork );
	BoxAppView_ItemIconQuit( wk->itemIconWork );
	BoxAppView_Reel_Quit( wk->reelWork );
	BoxAppView_PartyQuit( &(wk->partyWork) );
	BoxAppView_ExWinQuit( &(wk->exWinWork) );
	BoxAppView_MsgQuit( &(wk->msgWork) );
	BoxAppView_StatusQuit( &(wk->statusWork) );
	BoxAppView_ButtonQuit( &(wk->buttonWork) );
	BoxAppView_CursorQuit( &(wk->cursorWork) );
	BoxAppView_TrayQuit( &(wk->trayWork) );
	BoxAppView_IconSysQuit( &(wk->iconSysWork) );
	CLACT_DestSet( wk->clactSys );

	GF_BGL_BGControlExit(wk->bgl, FRM_MAIN_TRAY);
	GF_BGL_BGControlExit(wk->bgl, FRM_MAIN_STATUS);
	GF_BGL_BGControlExit(wk->bgl, FRM_MAIN_MESSAGE);
	GF_BGL_BGControlExit(wk->bgl, FRM_SUB_BMPWIN);

	SoftSpriteEnd( wk->spriteManager );
	FontProc_UnloadBitData(FONT_SYSTEM);

	sys_FreeMemoryEz(wk->bgl);
	sys_FreeMemoryEz(wk);

	REND_OAM_Delete();
}


//------------------------------------------------------------------
/**
 * �R�}���h�Z�b�g
 *
 * @param   vwk		���[�N�|�C���^
 * @param   cmd		�R�}���h
 *
 */
//------------------------------------------------------------------
void BoxAppView_SetCommand( BOXAPP_VIEW_WORK* vwk,  u32 cmd )
{
	static const struct {
		TCB_FUNC   func;
		u32        workSize;
	}command_tbl[] = {
		{  CmdInit,  0 },
		{  CmdNormalIn, 0 },
		{  CmdFadeIn, 0 },
		{  CmdFadeOut, 0 },

		{  CmdTrayChange, 0 },
		{  CmdCursorMove, 0 },
		{  CmdStatusUpdate, 0 },
		{  CmdStatusMarkingUpdate, 0 },
		{  CmdStatusClear, 0 },

		{  CmdPokemonCatch, 0 },
		{  CmdPokemonPut, 0 },
		{  CmdPokemonChange, 0 },
		{  CmdCatchPokeAzukeru, 0 },
		{  CmdPointPokeAzukeru, 0 },
		{  CmdCatchPokeNigasu, 0 },
		{  CmdTrayPokeNigasu, 0 },
		{  CmdPartyPokeNigasu, 0 },
		{  CmdItemInfoDisp, 0 },
		{  CmdItemInfoClear, 0 },
		{  CmdItemWithDraw, 0 },
		{  CmdItemSet, 0 },
		{  CmdItemSwap, 0 },
		{  CmdItemPokeUpdate, 0 },
		{  CmdItemIconRestore, 0 },

		{  CmdMsgDisp, 0 },
		{  CmdMenuDisp, 0 },
		{  CmdMsgClear, 0 },
		{  CmdMenuClear, 0 },
		{  CmdMenuCursorUpdate, 0 },
		{  CmdMenuMarkUpdate, 0 },

		{  CmdJumpWinDisp, 0 },
		{  CmdJumpWinUpdate, 0 },
		{  CmdJumpWinClear, 0 },
		{  CmdWallPaperChange, 0 },
		{  CmdButtonPushAction, 0 },
		{  CmdPartyTrayOpen, 0 },
		{  CmdPartyTrayClose, 0 },
		{  CmdPartyIconCloseup, 0 },
		{  CmdPartyLastIconCloseup, 0 },
		{  CmdIconLimitModeUpdate, 0 },

		{  CmdSubLCD_ModeChange, 0 },
		{  CmdSubLCD_MoveIcon, 0 },
		{  CmdSubLCD_MarkIconUpdate, 0 },

		{  CmdChangeExpertMode, 0 },
		{  CmdStartAreaSelect, 0 },
		{  CmdEndAreaSelect, 0 },
		{  CmdUpdateAreaSelect, 0 },
		{  CmdCatchAreaSelectPoke, 0 },

		{  CmdSwitchCompareSide, 0 },
		{  CmdSwitchCompareSideByButton, 0 },
		{  CmdChangeComparePage, 0 },
		{  CmdClose, 0 },
	};

	if( cmd < NELEMS(command_tbl) )
	{
		COMMAND_WORK_HEADER* header;
		u32 i;

		for(i = 0; i < STORE_COMMAND_MAX; i++)
		{
			if( vwk->command[i] == NULL )
			{
				header = sys_AllocMemory( HEAPID_BOX_VIEW, sizeof(COMMAND_WORK_HEADER) + command_tbl[cmd].workSize );
				if( header != NULL )
				{
					header->commandNumber = cmd;
					header->storeNumber = i;
					header->seq = 0;
					header->vwk = vwk;
					header->work = ((u8*)(header) + command_tbl[cmd].workSize);

					vwk->command[i] = TCB_Add(command_tbl[cmd].func, header, TASKPRI_VIEW_COMMAND);

//					if(vwk->command[i] != NULL)
//					{
//						command_tbl[cmd].func(vwk->command[i], header);
//					}

				}
				else
				{
					GF_ASSERT(0);
				}
				break;
			}
		}

	}
	else
	{
		GF_ASSERT(0);
	}
}
//------------------------------------------------------------------
/**
 * �R�}���h�P���I���҂�
 *
 * @param   vwk		���[�N�|�C���^
 * @param   cmd		�R�}���h
 *
 * @retval  BOOL	TRUE�ŏI��
 */
//------------------------------------------------------------------
BOOL BoxAppView_WaitCommand( BOXAPP_VIEW_WORK* vwk, u32 cmd )
{
	COMMAND_WORK_HEADER* h;
	int i;

	for(i = 0; i < STORE_COMMAND_MAX; i++)
	{
		if( vwk->command[i] != NULL )
		{
			h = TCB_GetWork( vwk->command[i] );
			if( h->commandNumber == cmd ){
				return FALSE;
			}
		}
	}
	return TRUE;

}
//------------------------------------------------------------------
/**
 * �R�}���h���S�I���҂�
 *
 * @param   vwk		���[�N�|�C���^
 *
 * @retval  BOOL	TRUE�ŏI��
 */
//------------------------------------------------------------------
BOOL BoxAppView_WaitCommandAll( BOXAPP_VIEW_WORK* vwk )
{
	int i;

	for(i = 0; i < STORE_COMMAND_MAX; i++)
	{
		if( vwk->command[i] != NULL )
		{
			return FALSE;
		}
	}
	return TRUE;
}

//------------------------------------------------------------------
/**
 * �R�}���h�폜�i�R�}���h�^�X�N����Ă΂��j
 *
 * @param   header		
 *
 */
//------------------------------------------------------------------
static void DeleteCommand( COMMAND_WORK_HEADER* header )
{
	BOXAPP_VIEW_WORK* vwk = header->vwk;

	TCB_Delete( vwk->command[ header->storeNumber ] );
	vwk->command[ header->storeNumber ] = NULL;
	sys_FreeMemoryEz( header );

}

//------------------------------------------------------------------
/**
 * V Blank
 */
//------------------------------------------------------------------
static void BoxVBlankTask(TCB_PTR tcb, void* wk_adrs)
{
	BOXAPP_VIEW_WORK* wk = (BOXAPP_VIEW_WORK*)wk_adrs;

	BoxAppView_StatusVBlank( &wk->statusWork );

	CLACT_Draw( wk->clactSys );
	REND_OAMTrans();		// �����_�����LOAM�}�l�[�W��Vram�]��
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );

}

//------------------------------------------------------------------
/**
 * �`��R�}���h�F��ʏ�����
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdInit(TCB_PTR tcb, void* wk_adrs)
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;


	switch( header->seq ){
	case 0:
		SetupBGRegistParam( vwk, vpara );
		SetupBGGraphicData( vwk, vpara );
		InitMainOBJ( vwk, vpara );
		if( BoxAppVPara_GetBoxMode(vpara) != BOX_MODE_COMPARE )
		{
			BoxAppView_Status_StartSoftSpritePreparation( &vwk->statusWork );
			header->seq++;
		}
		else
		{
			DeleteCommand( header );
		}
		break;

	case 1:
		if( BoxAppView_Status_WaitSoftSpritePreparation( &vwk->statusWork ) )
		{
			BoxAppView_StatusUpdate( &(vwk->statusWork) );
			DeleteCommand( header );
		}
		break;
	}
}

//------------------------------------------------------------------
/**
 * �`��R�}���h�F��ʕ\���J�n�G�t�F�N�g
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdNormalIn( TCB_PTR tcb, void* wk_adrs )
{
	enum {
		FADE_FRAMES = 8,
	};

	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		Snd_SePlay( SOUND_LOG_IN );
		G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE, GX_BLEND_ALL, BOX_BLEND_EVA, BOX_BLEND_EVB );
		WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, FADE_FRAMES, 1, 
			HEAPID_BOX_VIEW );
		header->seq++;
		break;

	case 1:
		if( WIPE_SYS_EndCheck() )
		{
			DeleteCommand(header);
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F����ʂ��畜�A���鎞�̃t�F�[�h�C���G�t�F�N�g
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdFadeIn( TCB_PTR tcb, void* wk_adrs )
{
	enum {
		FADE_FRAMES = 6,
	};

	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE, GX_BLEND_ALL, BOX_BLEND_EVA, BOX_BLEND_EVB );
		WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, FADE_FRAMES, 1, 
			HEAPID_BOX_VIEW );
		header->seq++;
		break;

	case 1:
		if( WIPE_SYS_EndCheck() )
		{
			DeleteCommand(header);
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F����ʑJ�ڑO�̃t�F�[�h�A�E�g�G�t�F�N�g
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdFadeOut( TCB_PTR tcb, void* wk_adrs )
{
	enum {
		FADE_FRAMES = 6,
	};

	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, FADE_FRAMES, 1, 
			HEAPID_BOX_VIEW );
		header->seq++;
		break;

	case 1:
		if( WIPE_SYS_EndCheck() )
		{
			DeleteCommand(header);
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�g���C�؂�ւ�
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdTrayChange( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch(header->seq){
	case 0:
		BoxAppView_ItemIcon_StartDisappear( vwk->itemIconWork );
		header->seq++;
		/* fallthru */
	case 1:
		if( BoxAppView_ItemIcon_WaitDisappear( vwk->itemIconWork ) == FALSE )
		{
			break;
		}
		header->seq++;
		/* fallthru */
	case 2:
		{
			int  direction = calc_tray_direction( vwk->trayWork.trayNum, vpara->tray.number );
			BoxAppView_TrayWrite( &vwk->trayWork, &vpara->tray, direction, TRUE );
			BoxAppView_TrayScrollSet( &vwk->trayWork, &vpara->tray, direction );
			Snd_SePlay( SOUND_CHANGE_TRAY );
			header->seq++;
		}
		/* fallthru */
	case 3:
		if( BoxAppView_TrayScrollWait( &vwk->trayWork ) == FALSE )
		{
			break;
		}
		BoxAppView_ItemIcon_StartAppear( vwk->itemIconWork );
		header->seq++;
		/* fallthru */
	case 4:
		if( BoxAppView_ItemIcon_WaitAppear( vwk->itemIconWork ) == FALSE )
		{
			break;
		}
		DeleteCommand( header );
		break;
	}

}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�J�[�\���ړ�
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdCursorMove( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		Snd_SePlay( SOUND_MOVE_CURSOR );
		BoxAppView_CursorMoveStart( &(vwk->cursorWork) );
		BoxAppView_ItemIcon_StartAppear( vwk->itemIconWork );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_CursorMoveWait( &(vwk->cursorWork) )
		&&	BoxAppView_ItemIcon_WaitAppear( vwk->itemIconWork )
		)
		{
			DeleteCommand( header );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�X�e�[�^�X�X�V
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdStatusUpdate( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;


	if( BoxAppVPara_GetBoxMode(vpara) != BOX_MODE_COMPARE )
	{
		switch( header->seq ){
		case 0:
			BoxAppView_StatusUpdateStart( &(vwk->statusWork) );
			header->seq++;
			break;
		case 1:
			if( BoxAppView_StatusUpdateWait( &(vwk->statusWork) ) )
			{
				DeleteCommand( header );
			}
			break;
		}
	}
	else
	{
		switch( header->seq ){
		case 0:
			BoxAppView_Compare_StartUpdate( vwk->compareWork );
			header->seq++;
			break;
		case 1:
			if( BoxAppView_Compare_WaitUpdate(vwk->compareWork) )
			{
				DeleteCommand( header );
			}
			break;
		}
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�X�e�[�^�X�̃}�[�L���O�\���̂ݍX�V
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdStatusMarkingUpdate( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	// �X�e�[�^�X�\�����|�P�����A�C�R���̃}�[�L���O�p�X�e�[�^�X���X�V
	if( BoxAppVPara_GetCursorCatchPokeFlag( vpara ) == CURSOR_CATCH_SINGLE )
	{
		BoxAppView_CursorIconMarkUpdate( &vwk->cursorWork );
	}
	else
	{
		switch( BoxAppVPara_GetCursorArea(vpara) ){
		case CURSOR_AREA_TRAY:
			BoxAppView_TrayIconMarkUpdate( &vwk->trayWork );
			break;
		case CURSOR_AREA_PARTY:
			BoxAppView_PartyIconMarkUpdate( &vwk->partyWork );
			break;
		}
	}

	BoxAppView_StatusMarkUpdate( &vwk->statusWork );
	DeleteCommand( header );
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�X�e�[�^�X�\���N���A
 *
 * @param   tcb		
 * @param   wk_adrs		
 */
//------------------------------------------------------------------
static void CmdStatusClear( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	BoxAppView_StatusUpdateClear( &(vwk->statusWork) );
	DeleteCommand( header );
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�|�P�������ޓ���
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdPokemonCatch( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_CursorCatchStart( &(vwk->cursorWork) );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_CursorCatchWait( &(vwk->cursorWork) ) )
		{
			DeleteCommand( header );
		}
		break;
	}

}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�|�P������������
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdPokemonPut( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_CursorPutStart( &(vwk->cursorWork) );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_CursorPutWait( &(vwk->cursorWork) ) )
		{
			DeleteCommand( header );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�|�P�������ꂩ���铮��
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdPokemonChange( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_CursorIconSwapStart( &(vwk->cursorWork) );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_CursorIconSwapWait( &(vwk->cursorWork) ) )
		{
			DeleteCommand( header );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F����ł���|�P�������������铮��
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdCatchPokeAzukeru( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_CursorCatchIconAzukeru( &(vwk->cursorWork) );
		header->seq++;
		break;
	case 1:
		DeleteCommand( header );
		break;
	}

}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�w���Ă���|�P�������������铮��
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdPointPokeAzukeru( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_PartyPointIconAzuke( &(vwk->partyWork) );
		header->seq++;
		break;
	case 1:
		BoxAppView_PartyIconCloseupStart( &(vwk->partyWork) );
		header->seq++;
		break;
	case 2:
		if( BoxAppView_PartyIconCloseupWait( &(vwk->partyWork) ) )
		{
			DeleteCommand( header );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F����ł���|�P�����𓦂���
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdCatchPokeNigasu( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_CursorCatchIconReleaseStart( &(vwk->cursorWork) );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_CursorCatchIconReleaseWait( &(vwk->cursorWork) ) )
		{
			DeleteCommand( header );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�{�b�N�X�g���C�̃J�[�\�����w���Ă���|�P�����𓦂���
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdTrayPokeNigasu( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_TrayIconReleaseStart( &(vwk->trayWork), BoxAppVPara_GetCursorTrayPos(vpara) );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_TrayIconReleaseWait( &(vwk->trayWork) ) )
		{
			DeleteCommand( header );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�莝���g���C�̃J�[�\�����w���Ă���|�P�����𓦂���
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdPartyPokeNigasu( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_PartyIconReleaseStart( &(vwk->partyWork), BoxAppVPara_GetCursorPartyPos(vpara) );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_PartyIconReleaseWait( &(vwk->partyWork) ) )
		{
			DeleteCommand( header );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�A�C�e�������̕\��
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdItemInfoDisp( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_ExWin_ItemInfoWinDispStart( &(vwk->exWinWork) );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_ExWin_ItemInfoWinDispWait( &(vwk->exWinWork) ) )
		{
			DeleteCommand( header );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�A�C�e�������̏���
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdItemInfoClear( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_ExWin_ItemInfoWinClearStart( &(vwk->exWinWork) );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_ExWin_ItemInfoWinClearWait( &(vwk->exWinWork) ) )
		{
			DeleteCommand( header );
		}
		break;
	}

}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�A�C�e���u��������v
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdItemWithDraw( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_CursorItemCatchStart( &(vwk->cursorWork) );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_CursorItemCatchWait( &(vwk->cursorWork) ) )
		{
			BoxAppView_StatusUpdateItemInfo( &(vwk->statusWork) );
			DeleteCommand( header );
		}
		break;
	}

}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�A�C�e���u��������v�i�͂�ł���A�C�e������������j
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdItemSet( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_CursorItemSetStart( &(vwk->cursorWork) );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_CursorItemSetWait( &(vwk->cursorWork) ) )
		{
			BoxAppView_StatusUpdateItemInfo( &(vwk->statusWork) );
			DeleteCommand( header );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�A�C�e���u�Ƃ肩����v
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdItemSwap( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_CursorItemSwapStart( &(vwk->cursorWork) );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_CursorItemSwapWait( &(vwk->cursorWork) ) )
		{
			BoxAppView_StatusUpdateItemInfo( &(vwk->statusWork) );
			DeleteCommand( header );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�X�e�[�^�X�|�P�����̃A�C�e�����L��Ԃɉ����ăA�C�R���\���؂�ւ�
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdItemPokeUpdate( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;
	u32  itemNumber;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	itemNumber = BoxAppVPara_GetStatusPokeItemNumber(vpara);

	if( BoxAppVPara_GetCursorCatchPokeFlag(vpara) == CURSOR_CATCH_SINGLE )
	{
		BoxAppView_CursorCatchIconUpdateItem( &vwk->cursorWork, itemNumber );
	}
	else
	{
		switch(BoxAppVPara_GetCursorArea(vpara)){
		case CURSOR_AREA_PARTY:
			BoxAppView_PartyIconUpdateItem( &vwk->partyWork, BoxAppVPara_GetCursorPartyPos(vpara), itemNumber );
			break;
		case CURSOR_AREA_TRAY:
			BoxAppView_TrayIconUpdateItem( &vwk->trayWork, BoxAppVPara_GetCursorTrayPos(vpara), itemNumber );
			break;
		}
	}
	DeleteCommand( header );
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�A�C�e���A�C�R�����o�b�O�ɖ߂��G�t�F�N�g
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdItemIconRestore( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;
	u32  itemNumber;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;


	switch( header->seq ){
	case 0:
		BoxAppView_CursorItemReleaseStart( &vwk->cursorWork );
		BoxAppView_ItemIcon_StartRestore( vwk->itemIconWork );
		header->seq++;
		break;

	case 1:
		if( BoxAppView_ItemIcon_WaitRestore( vwk->itemIconWork ) )
		{
			BoxAppView_CursorItemReleaseEnd( &vwk->cursorWork );
			DeleteCommand( header );
		}
		break;
	}

}

//------------------------------------------------------------------
/**
 * �`��R�}���h�F���b�Z�[�W�`��
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdMsgDisp( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;


	BoxAppView_MsgWrite( &(vwk->msgWork), BoxAppVPara_GetMessageID(vpara) );
	DeleteCommand( header );
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F���b�Z�[�W�����j���[�`��
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdMenuDisp( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;


	BoxAppView_MsgWrite( &(vwk->msgWork), BoxAppVPara_GetMessageID(vpara) );
	BoxAppView_MenuWrite( &(vwk->msgWork), &(vpara->menu) );
	DeleteCommand( header );
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F���b�Z�[�W�E���j���[�S�N���A
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdMsgClear( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;

	BoxAppView_MsgClear( &(vwk->msgWork) );
	DeleteCommand( header );
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F���j���[�̂݃N���A
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdMenuClear( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;

	BoxAppView_MenuClear( &(vwk->msgWork) );
	DeleteCommand( header );
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F���j���[�J�[�\���ʒu�X�V
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdMenuCursorUpdate( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	Snd_SePlay( SOUND_SELECT_MENU );
	BoxAppView_MenuCursorUpdate( &(vwk->msgWork), &(vpara->menu) );
	DeleteCommand( header );
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F���j���[�}�[�L���O�\���X�V
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdMenuMarkUpdate( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	Snd_SePlay( SOUND_DECIDE );
	BoxAppView_MenuMarkUpdate( &(vwk->msgWork), &(vpara->menu) );
	DeleteCommand( header );
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�{�b�N�X�I���E�B���h�E�\��
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdJumpWinDisp( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_ExWin_JumpWinDispStart( &(vwk->exWinWork) );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_ExWin_JumpWinDispWait( &(vwk->exWinWork) ) )
		{
			DeleteCommand( header );
		}
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�{�b�N�X�I���E�B���h�E�\���X�V
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdJumpWinUpdate( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		Snd_SePlay( SOUND_DECIDE );
		BoxAppView_ExWin_JumpWinUpdate( &(vwk->exWinWork) );
		header->seq++;
		break;
	case 1:
		DeleteCommand( header );
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�{�b�N�X�I���E�B���h�E�\���I�t
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdJumpWinClear( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_ExWin_JumpWinDelStart( &(vwk->exWinWork) );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_ExWin_JumpWinDelWait( &(vwk->exWinWork) ) )
		{
			DeleteCommand( header );
		}
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�J�����g�̕ǎ��ύX
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdWallPaperChange( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_TrayChangeWallPaperStart( &(vwk->trayWork) );
		header->seq++;
		break;
	case 1:
		if(BoxAppView_TrayChangeWallPaperWait( &(vwk->trayWork) ))
		{
			DeleteCommand( header );
		}
		break;
	}

}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�J�[�\���������̃{�^������������
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdButtonPushAction( TCB_PTR tcb, void* wk_adrs )
{
	enum {
		PUSH_HOLD_FRAME = 6,
	};

	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		Snd_SePlay( SOUND_DECIDE );
		BoxAppView_CursorButtonPushActionStart( &(vwk->cursorWork) );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_CursorButtonPushActionWait( &(vwk->cursorWork) ) )
		{
			switch( BoxAppVPara_GetCursorArea(vpara) ){
			case CURSOR_AREA_PARTY_BUTTON:
				BoxAppView_ButtonStateChange( &(vwk->buttonWork), BUTTON_STATE_PARTY_PUSH );
				break;
			case CURSOR_AREA_EXIT_BUTTON:
				BoxAppView_ButtonStateChange( &(vwk->buttonWork), BUTTON_STATE_CLOSE_PUSH );
				break;
			}
			header->val_1 = 0;
			header->seq++;
		}
		break;
	case 2:
		if( ++(header->val_1) >= PUSH_HOLD_FRAME )
		{
			BoxAppView_CursorButtonReleaseActionStart( &(vwk->cursorWork) );
			BoxAppView_ButtonStateChange( &(vwk->buttonWork), BUTTON_STATE_INIT );
			header->seq++;
		}
		break;
	case 3:
		if( BoxAppView_CursorButtonReleaseActionWait( &(vwk->cursorWork) ) )
		{
			DeleteCommand( header );
		}
		break;

	}

}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�莝���g���C�J��
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdPartyTrayOpen(TCB_PTR tcb, void* wk_adrs)
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		Snd_SePlay( SOUND_OPEN_PARTY_TRAY );
		BoxAppView_CursorPriPartyMode( &(vwk->cursorWork) );
		BoxAppView_PartyOpenStart( &(vwk->partyWork) );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_PartyOpenWait( &(vwk->partyWork) ) )
		{
			DeleteCommand( header );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�莝���g���C����
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdPartyTrayClose(TCB_PTR tcb, void* wk_adrs)
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_ItemIcon_StartDisappear( vwk->itemIconWork );
		header->seq++;
		/* fallthru */
	case 1:
		if( BoxAppView_ItemIcon_WaitDisappear( vwk->itemIconWork ) == FALSE )
		{
			break;
		}
		header->seq++;
		/* fallthru */
	case 2:
		Snd_SePlay( SOUND_CLOSE_PARTY_TRAY );
		BoxAppView_PartyCloseStart( &(vwk->partyWork) );
		header->seq++;
		break;
	case 3:
		if( BoxAppView_PartyCloseWait( &(vwk->partyWork) ) )
		{
			BoxAppView_CursorPriNormalMode( &(vwk->cursorWork) );
			DeleteCommand( header );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�莝���g���C��̃A�C�R���󂫋l�߁i�͂񂾌�j
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdPartyIconCloseup(TCB_PTR tcb, void* wk_adrs)
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_PartyIconCloseupStart( &(vwk->partyWork) );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_PartyIconCloseupWait( &(vwk->partyWork) ) )
		{
			DeleteCommand( header );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�莝���g���C��̃A�C�R���󂫋l�߁i�u������j
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdPartyLastIconCloseup( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		// �莝���g���C�ɒu�����A�C�R�����A�󂫂��o���Ȃ��悤�ɋl�߂�K�v������
		if( BoxAppVPara_GetCursorArea( vpara ) == CURSOR_AREA_PARTY )
		{
			BoxAppView_PartyLastIconCloseupStart( &vwk->partyWork );
			header->seq++;
			break;
		}
		DeleteCommand( header );
		break;

	case 1:
		if( BoxAppView_PartyLastIconCloseupWait( &vwk->partyWork ) )
		{
			DeleteCommand( header );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�A�C�R�����i�荞�݃��[�h�\���ɑΉ�������
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdIconLimitModeUpdate( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	BoxAppView_TrayIconLimitModeSet( &vwk->trayWork );
	BoxAppView_PartyIconLimitModeSet( &vwk->partyWork );
	BoxAppView_CursorCatchIconLimitModeSet( &vwk->cursorWork );

	DeleteCommand( header );

}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�T�uLCD�g���C�I�����[�h��ʍ\�z����
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdSubLCD_ModeChange( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_Reel_ChangeState( vwk->reelWork );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_Reel_ChangeStateWait( vwk->reelWork ) )
		{
			if( vpara->subLCD.state == SUBLCD_STATE_NORMAL )
			{
				DeleteCommand( header );
			}
			else
			{
				BoxAppView_Reel_DispIcon( vwk->reelWork );
				header->seq++;
			}
		}
		break;
	case 2:
		if( BoxAppView_Reel_DispIconWait( vwk->reelWork ) )
		{
			DeleteCommand( header );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�T�uLCD�g���C�I�����[�h��ʏI������
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdSubLCD_MoveIcon( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_Reel_MoveIcon( vwk->reelWork );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_Reel_MoveIconWait( vwk->reelWork ) )
		{
			DeleteCommand( header );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�i�荞�݃A�C�R����ԍX�V
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdSubLCD_MarkIconUpdate( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	BoxAppView_Reel_MarkIconUpdate( vwk->reelWork );
	DeleteCommand( header );
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F����Ă�l���[�h�؂�ւ�
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdChangeExpertMode( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	BoxAppView_CursorExpertModeChange( &(vwk->cursorWork) );
	DeleteCommand( header );
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�|�P�����A�C�R���͈̔͑I���J�n
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdStartAreaSelect( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	BoxAppView_CursorAleaSelectStart( &(vwk->cursorWork) );
	BoxAppView_TrayIconAleaSelectUpdate( &(vwk->trayWork) );
	DeleteCommand( header );
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�|�P�����A�C�R���͈̔͑I���J�n
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdEndAreaSelect( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	BoxAppView_TrayIconAleaSelectQuit( &(vwk->trayWork) );
	DeleteCommand( header );
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�|�P�����A�C�R���͈̔͑I����ԍX�V
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdUpdateAreaSelect( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	BoxAppView_TrayIconAleaSelectUpdate( &(vwk->trayWork) );
	DeleteCommand( header );
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�F�͈͑I�𒆂̃|�P������͂ޓ���
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdCatchAreaSelectPoke( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_CursorCatchStart( &(vwk->cursorWork) );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_CursorCatchWait( &(vwk->cursorWork) ) )
		{
			DeleteCommand( header );
		}
		break;
	}
}

//------------------------------------------------------------------
/**
 * �`��R�}���h�F�悳����׃��[�h�F�T�C�h�ύX
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdSwitchCompareSide( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	BoxAppView_Compare_SwitchSide(vwk->compareWork, FALSE);
	DeleteCommand(header);

}

//------------------------------------------------------------------
/**
 * �`��R�}���h�F�悳����׃��[�h�F�T�C�h�ύX
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdSwitchCompareSideByButton( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	BoxAppView_Compare_SwitchSide(vwk->compareWork, TRUE);
	DeleteCommand(header);

}

//------------------------------------------------------------------
/**
 * �`��R�}���h�F�悳����׃��[�h�F�y�[�W�؂�ւ�
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdChangeComparePage( TCB_PTR tcb, void* wk_adrs )
{
	BOXAPP_VIEW_WORK* vwk;
	COMMAND_WORK_HEADER* header;
	const BOXAPP_VPARAM* vpara;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		BoxAppView_Compare_ChangePage( vwk->compareWork );
		header->seq++;
		break;
	case 1:
		if( BoxAppView_Compare_WaitChangePage( vwk->compareWork ) )
		{
			DeleteCommand(header);
		}
		break;
	}

}



//------------------------------------------------------------------
/**
 * �`��R�}���h�F�{�b�N�X��ʂ���鉉�o
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdClose( TCB_PTR tcb, void* wk_adrs )
{
	enum {
		FADE_FRAMES = 6,
	};

	BOXAPP_VIEW_WORK* vwk;
	const BOXAPP_VPARAM* vpara;
	COMMAND_WORK_HEADER* header;

	header = (COMMAND_WORK_HEADER*)wk_adrs;
	vwk = header->vwk;
	vpara = vwk->vpara;

	switch( header->seq ){
	case 0:
		Snd_SePlay( SOUND_LOG_OFF );
		WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, FADE_FRAMES, 1, 
			HEAPID_BOX_VIEW );
		header->seq++;
		break;

	case 1:
		if( WIPE_SYS_EndCheck() )
		{
			DeleteCommand(header);
		}
		break;
	}
}





//------------------------------------------------------------------
/**
 * BG �\�����W�X�^�֘A������
 *
 * @param   vwk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void SetupBGRegistParam( BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara )
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

	static const GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
	};

	static const GF_BGL_BGCNT_HEADER header0 = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		0, 0,
		GX_BG_EXTPLTT_01, 1, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	static const GF_BGL_BGCNT_HEADER header1 = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		BG1_SCRBASE, BG1_CHARBASE,
		GX_BG_EXTPLTT_01, 0, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	static const GF_BGL_BGCNT_HEADER header2 = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		BG2_SCRBASE, BG2_CHARBASE,
		GX_BG_EXTPLTT_01, 1, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	static const GF_BGL_BGCNT_HEADER header3 = {
		0, 0, 0x1000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
		BG3_SCRBASE, BG3_CHARBASE,
		GX_BG_EXTPLTT_01, 3, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	static const GF_BGL_BGCNT_HEADER header0sub = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		SUB_BG0_SCRBASE, SUB_BG0_CHARBASE,
		GX_BG_EXTPLTT_01, 0, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};
	static const GF_BGL_BGCNT_HEADER header1sub = {
		0, 0, 0x000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
		SUB_BG1_SCRBASE, SUB_BG1_CHARBASE,
		GX_BG_EXTPLTT_01, 1, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};
	static const GF_BGL_BGCNT_HEADER header2sub = {
		0, 0, 0x0000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
		SUB_BG2_SCRBASE, SUB_BG2_CHARBASE,
		GX_BG_EXTPLTT_01, 2, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};
	static const GF_BGL_BGCNT_HEADER header3sub = {
		0, 0, 0x0000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		SUB_BG3_SCRBASE, SUB_BG3_CHARBASE,
		GX_BG_EXTPLTT_01, 3, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};


	static const GF_BGL_BGCNT_HEADER header1sub_compare = {
		0, 0, 0x000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 1, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};
	static const GF_BGL_BGCNT_HEADER header2sub_compare = {
		0, 0, 0x0000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 2, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

/*
	static const GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
	};

	GF_BGL_InitBG

typedef struct {
	GXDispMode 	dispMode;		//�\�����[�h�w��
	GXBGMode	bgMode;			//�a�f���[�h�w��(���C���X�N���[��)
	GXBGMode	bgModeSub;		//�a�f���[�h�w��(�T�u�X�N���[��)
	GXBG0As		bg0_2Dor3D;		//�a�f�O�̂Q�c�A�R�c���[�h�I��
}GF_BGL_SYS_HEADER;
*/


	GF_Disp_SetBank( &SetBankData );

	GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);
	GX_SetGraphicsMode( GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BG0_AS_3D);

//			GX_SetBankForBG(GX_VRAM_BG_128_B);
//			GX_SetBankForOBJ(GX_VRAM_OBJ_64_E);


	GF_BGL_InitBG( &BGsys_data );

	GF_BGL_BGControlSet( vwk->bgl, FRM_MAIN_MESSAGE, &header1, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( vwk->bgl, FRM_MAIN_STATUS, &header2, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( vwk->bgl, FRM_MAIN_TRAY, &header3, GF_BGL_MODE_TEXT );

	if( BoxAppVPara_GetBoxMode(vpara) != BOX_MODE_COMPARE )
	{
		GF_BGL_BGControlSet( vwk->bgl, FRM_SUB_BMPWIN,   &header0sub, GF_BGL_MODE_TEXT );
		GF_BGL_BGControlSet( vwk->bgl, FRM_SUB_REEL,     &header1sub, GF_BGL_MODE_TEXT );
		GF_BGL_BGControlSet( vwk->bgl, FRM_SUB_ICONLINE, &header2sub, GF_BGL_MODE_TEXT );
		GF_BGL_BGControlSet( vwk->bgl, FRM_SUB_BACK,     &header3sub, GF_BGL_MODE_TEXT );
	}
	else
	{
		GF_BGL_BGControlSet( vwk->bgl, FRM_SUB_COMPARE_BMPWIN, &header0sub, GF_BGL_MODE_TEXT );
		GF_BGL_BGControlSet( vwk->bgl, FRM_SUB_COMPARE_PAGE1,  &header1sub_compare, GF_BGL_MODE_TEXT );
		GF_BGL_BGControlSet( vwk->bgl, FRM_SUB_COMPARE_PAGE2,  &header2sub_compare, GF_BGL_MODE_TEXT );
		GF_BGL_BGControlSet( vwk->bgl, FRM_SUB_COMPARE_PAGE3,  &header3sub, GF_BGL_MODE_TEXT );
	}

	Box3D_BGInit();
}
//------------------------------------------------------------------
/**
 * 
 *
 * @param   vwk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void SetupBGGraphicData( BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara )
{
	ArcUtil_BgCharSet( ARC_BOX_GRA, NARC_box_bg0_lz_ncgr, vwk->bgl, FRM_MAIN_MESSAGE, 0, 0, TRUE, HEAPID_BOX_VIEW );
	GF_BGL_ScrFill( vwk->bgl, FRM_MAIN_MESSAGE, 0x0000, 0, 0, 32, 32, GF_BGL_SCRWRT_PALIN );
	GF_BGL_LoadScreenReq( vwk->bgl, FRM_MAIN_MESSAGE );

	ArcUtil_BgCharSet(ARC_BOX_GRA, NARC_box_bg1_lz_ncgr, vwk->bgl, FRM_MAIN_STATUS, 0, 0, TRUE, HEAPID_BOX_VIEW);
	ArcUtil_PalSet( ARC_BOX_GRA, NARC_box_bg1_nclr, PALTYPE_MAIN_BG, 0, 0x20*PAL_FIX_USE_MAX, HEAPID_BOX_VIEW );

	if( BoxAppVPara_GetBoxMode(vpara) != BOX_MODE_COMPARE )
	{
		ArcUtil_ScrnSet(ARC_BOX_GRA, NARC_box_bg1_lz_nscr, vwk->bgl, FRM_MAIN_STATUS, 0, 0, TRUE, HEAPID_BOX_VIEW);
	}

	BoxAppView_TraySetup( &vwk->trayWork );
	BoxAppView_TrayWrite( &vwk->trayWork, &vpara->tray, 0, TRUE );
	BoxAppView_StatusSetup( &(vwk->statusWork) );
	BoxAppView_MsgSetup( &(vwk->msgWork) );
	BoxAppView_ExWinSetup( &(vwk->exWinWork) );

	BoxAppView_Reel_Setup( vwk->reelWork );
	BoxAppView_SetupCompare( vwk->compareWork );

	if(BoxAppVPara_GetCursorArea(vpara) == CURSOR_AREA_PARTY)
	{
		BoxAppView_PartyDisp( &(vwk->partyWork) );
	}


	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GX_DispOn();

}

//------------------------------------------------------------------
/**
 * 
 *
 * @param   none		
 *
 */
//------------------------------------------------------------------
static void Box3D_BGInit(void)
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
 * ���C���n�a�i������
 *
 * @param   vwk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void InitMainOBJ( BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara )
{
	BoxAppView_CursorActSet( &vwk->cursorWork );
	BoxAppView_ButtonActSet( &vwk->buttonWork );
	BoxAppView_ItemIcon_StartDisp( vwk->itemIconWork );
//	BoxAppView_SetTrayIcon( &(vwk->iconWork), BoxAppVPara_GetTrayBoxNumber( vpara ), 0 );
}

//------------------------------------------------------------------
/**
 * �g���C�X�N���[�����������߂�
 *
 * @param   from		�X�N���[���O�̃g���C�i���o�[
 * @param   to			�X�N���[����̃g���C�i���o�[
 *
 * @retval  int		1:�E�� -1:����
 */
//------------------------------------------------------------------
static int calc_tray_direction( u32 from, u32 to )
{
	int rlen, llen;

	if( to > from )
	{
		rlen = to - from;
		llen = from + (BOX_MAX_TRAY - to);
	}
	else
	{
		rlen = to + (BOX_MAX_TRAY - from);
		llen = from - to;
	}

	return ( rlen >= llen )? -1 : 1;
}



//------------------------------------------------------------------
/**
 * VBlank�Ń^�C�~���O�����킹�邽�߂̃^�X�N�o�^
 *
 * @param   func		�^�X�N�֐�
 * @param   wk_adrs		�^�X�N���[�N
 * @param   pri			�v���C�I���e�B
 *
 * @retval  TCB_PTR		�^�X�N�|�C���^
 */
//------------------------------------------------------------------
TCB_PTR BoxAppView_VTaskAdd(TCB_FUNC func, void* wk_adrs, u32 pri )
{
#ifdef BOX_FPS_60
	return VIntrTCB_Add( func, wk_adrs, pri );
#else
	return VWaitTCB_Add( func, wk_adrs, pri );
#endif
}
//------------------------------------------------------------------
/**
 * �n�a�i�p���b�g�v���L�V��Ԃ��B�e�퉺�������W���[������Ă΂��
 *
 * @param   vwk		
 *
 * @retval  NNSG2dImagePaletteProxy*		
 */
//------------------------------------------------------------------
NNSG2dImagePaletteProxy* BoxAppView_GetObjPlttProxy( BOXAPP_VIEW_WORK* vwk )
{
	return &(vwk->plttProxy);
}



//------------------------------------------------------------------
/**
 * �{�b�N�X�A�C�R���`��V�X�e���̃��C�����[�N�|�C���^��Ԃ��B
 * �e�퉺�������W���[������K�v�ɉ����ČĂ΂��B
 *
 * @param   vwk		
 *
 * @retval  BOX_ICON_SYS*		
 */
//------------------------------------------------------------------
BOX_ICON_SYS* BoxAppView_GetIconSysWork( BOXAPP_VIEW_WORK* vwk )
{
	return &(vwk->iconSysWork);
}
//------------------------------------------------------------------
/**
 * �{�b�N�X�g���C�`�惏�[�N�|�C���^��Ԃ��B
 * �e�퉺�������W���[������K�v�ɉ����ČĂ΂��B
 *
 * @param   vwk		
 *
 * @retval  BOX_ICON_SYS*		
 */
//------------------------------------------------------------------
TRAY_VIEW_WORK* BoxAppView_GetTrayViewWork( BOXAPP_VIEW_WORK* vwk )
{
	return &(vwk->trayWork);
}
//------------------------------------------------------------------
/**
 * �p�[�e�B�g���C�`�惏�[�N�|�C���^��Ԃ��B
 * �e�퉺�������W���[������K�v�ɉ����ČĂ΂��B
 *
 * @param   vwk		
 *
 * @retval  PARTY_VIEW_WORK*		
 */
//------------------------------------------------------------------
PARTY_VIEW_WORK* BoxAppView_GetPartyViewWork( BOXAPP_VIEW_WORK* vwk )
{
	return &(vwk->partyWork);
}
//------------------------------------------------------------------
/**
 * �J�[�\���`�惏�[�N�|�C���^��Ԃ��B
 * �e�퉺�������W���[������K�v�ɉ����ČĂ΂��B
 *
 * @param   vwk		
 *
 * @retval  BOX_ICON_SYS*		
 */
//------------------------------------------------------------------
CURSOR_VIEW_WORK* BoxAppView_GetCursorWork( BOXAPP_VIEW_WORK* vwk )
{
	return &(vwk->cursorWork);
}
//------------------------------------------------------------------
/**
 * �A�C�e���A�C�R���`�惏�[�N�|�C���^��Ԃ��B
 * �e�퉺�������W���[������K�v�ɉ����ČĂ΂��B
 *
 * @param   vwk		
 *
 * @retval  ITEMICON_VIEW_WORK*		
 */
//------------------------------------------------------------------
ITEMICON_VIEW_WORK* BoxAppView_GetItemIconWork( BOXAPP_VIEW_WORK* vwk )
{
	return vwk->itemIconWork;
}
//------------------------------------------------------------------
/**
 * ����E�B���h�E�`�惏�[�N�|�C���^��Ԃ��B
 * �e�퉺�������W���[������K�v�ɉ����ČĂ΂��B
 *
 * @param   vwk		
 *
 * @retval  EXWIN_VIEW_WORK*		
 */
//------------------------------------------------------------------
EXWIN_VIEW_WORK* BoxAppView_GetExWinViewWork( BOXAPP_VIEW_WORK* vwk )
{
	return &(vwk->exWinWork);
}

//------------------------------------------------------------------
/**
 * �\�t�g�E�F�A�X�v���C�g�}�l�[�W����Ԃ��B
 * �e�퉺�������W���[������K�v�ɉ����ČĂ΂��B
 *
 * @param   vwk		
 *
 * @retval  SOFT_SPRITE_MANAGER*		
 */
//------------------------------------------------------------------
SOFT_SPRITE_MANAGER* BoxAppView_GetSpriteManager( BOXAPP_VIEW_WORK* vwk )
{
	return vwk->spriteManager;
}

//------------------------------------------------------------------
/**
 * �g���C�̃X�N���[���f�t�H���g�I�t�Z�b�g�l��Ԃ�
 *
 * @param   vwk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
int BoxAppView_GetTrayScrollOfs( BOXAPP_VIEW_WORK* vwk )
{
	if( BoxAppVPara_GetBoxMode(vwk->vpara) != BOX_MODE_COMPARE )
	{
		return 0;
	}
	else
	{
		return  -44;
	}
}





//------------------------------------------------------------------
/**
 * CLACT_HEADER�̏�����
 *
 * @param   header		[out] �쐬�����w�b�_�f�[�^�̊i�[��
 * @param   imgProxy	[in]  �w�b�_�ɃZ�b�g����C���[�W�v���L�V
 * @param   pltProxy	[in]  �w�b�_�ɃZ�b�g����p���b�g�v���L�V
 * @param   cellBank	[in]  �w�b�_�ɃZ�b�g����Z���o���N�f�[�^
 * @param   anmBank		[in]  �w�b�_�ɃZ�b�g����A�j���o���N�f�[�^
 * @param   bgPri		[in]  �w�b�_�ɃZ�b�g����BG�v���C�I���e�B
 *
 */
//------------------------------------------------------------------
void BoxAppView_SetActHeader( CLACT_HEADER* header, NNSG2dImageProxy* imgProxy, NNSG2dImagePaletteProxy* pltProxy,
					NNSG2dCellDataBank* cellBank, NNSG2dCellAnimBankData* anmBank, u32 bgPri )
{
	header->pImageProxy = imgProxy;
	header->pPaletteProxy = pltProxy;
	header->pCellBank = cellBank;
	header->pAnimBank = anmBank;
	header->priority = bgPri;

	header->pCharData = NULL;
	header->pMCBank = NULL;
	header->pMCABank = NULL;
	header->flag = FALSE;
}


//------------------------------------------------------------------
/**
 * �A�N�^�[�ǉ�
 *
 * @param   actSys		
 * @param   actHeader		
 * @param   x		
 * @param   y		
 * @param   actPri		
 * @param   drawArea		
 *
 * @retval  CLACT_WORK_PTR		
 */
//------------------------------------------------------------------
CLACT_WORK_PTR BoxAppView_AddActor( CLACT_SET_PTR  actSys, CLACT_HEADER_PTR  actHeader, u32 x, u32 y, u32 actPri, int drawArea)
{
	CLACT_ADD_SIMPLE  add;
	CLACT_WORK_PTR  act;

	add.ClActSet = actSys;
	add.ClActHeader = actHeader;
	add.mat.x = x * FX32_ONE;
	add.mat.y = y * FX32_ONE;
	add.mat.z = 0;
	add.pri = actPri;
	add.DrawArea = drawArea;
	add.heap = HEAPID_BOX_VIEW;

	{	// �A�N�^�[��Add���Ɋ��荞�݂ŃA�N�^�[�`�悪��������ƃ}�Y���̂�
	    OSIntrMode	oldIntr = OS_DisableInterrupts();
		act = CLACT_AddSimple( &add );
		OS_RestoreInterrupts( oldIntr );
	}

	if( act )
	{
		CLACT_SetAnmFlag( act, TRUE );
		CLACT_SetAnmFrame( act, BOX_ANM_SPEED );
	}
	return act;

}


//------------------------------------------------------------------
/**
 * �A�N�^�[�̕`��v���C�I���e�B�ύX
 *
 * @param   act		
 * @param   pri		
 *
 */
//------------------------------------------------------------------
void BoxAppView_ChangeDrawPriority( CLACT_WORK_PTR act, u32 pri )
{
    OSIntrMode	oldIntr = OS_DisableInterrupts();
	CLACT_DrawPriorityChg( act, pri );
	OS_RestoreInterrupts( oldIntr );
}


//------------------------------------------------------------------
/**
 * �p���b�g�t�F�[�h�v�Z
 *
 * @param   src			�Q�Ɛ�p���b�g�A�h���X
 * @param   dst			�t�F�[�h��p���b�g�f�[�^�������݃A�h���X
 * @param   colNum		�v�Z����F��
 * @param   colCode		�t�F�[�h�J���[�istep==16�ŁA�S�F�����̐F�ɂȂ�j
 * @param   step		�t�F�[�h�i�K
 *
 */
//------------------------------------------------------------------
void BoxAppView_PalFade( const u16* src, u16* dst, u32 colNum, u16 colCode, u32 step )
{
	enum {
		SHIFT_VAL = 8,
		STEP_MAX = 16,
	};
	int r,g,b;
	int next_r, next_g, next_b;
	int diff;

	next_r = (colCode & 0x1f) << SHIFT_VAL;
	next_g = ((colCode>>5) & 0x1f) << SHIFT_VAL;
	next_b = ((colCode>>10) & 0x1f) << SHIFT_VAL;

	while( colNum-- )
	{
		r = (((*src) & 0x1f)) << SHIFT_VAL;
		g = ((((*src) >> 5) & 0x1f)) << SHIFT_VAL;
		b = ((((*src) >> 10) & 0x1f)) << SHIFT_VAL;

		r += (((next_r - r) / STEP_MAX) * step);
		g += (((next_g - g) / STEP_MAX) * step);
		b += (((next_b - b) / STEP_MAX) * step);

		r = (r >> SHIFT_VAL) & 0x1f;
		g = (g >> SHIFT_VAL) & 0x1f;
		b = (b >> SHIFT_VAL) & 0x1f;

		*dst = ((b<<10)|(g<<5)|r);

		src++;
		dst++;
	}
}


//------------------------------------------------------------------
/**
 * 
 *
 * @param   vwk		
 *
 * @retval  const BOXAPP_WORK*		
 */
//------------------------------------------------------------------
const BOXAPP_WORK* BoxAppView_GetMainWork( BOXAPP_VIEW_WORK* vwk )
{
	return vwk->mainWork;
}




//==============================================================================================
//==============================================================================================

enum {
	FREE_MEMORY_QUEUE_MAX = 32,
};


static u32  FreeMemoryQueueCount = 0;

static struct {
	pMemoryFreeTaskCallBack  callback;
	void*     arg;
	void*     memory;
}FreeMemoryQueue[ FREE_MEMORY_QUEUE_MAX ];


//------------------------------------------------------------------
/**
 * ���荞�ݒ�����������V�X�e��������
 */
//------------------------------------------------------------------
static void FreeMemoryWorkInit( void )
{
	FreeMemoryQueueCount = 0;
}

//------------------------------------------------------------------
/**
 * ���N�G�X�g���󂯂��������̉������
 */
//------------------------------------------------------------------
static void FreeMemoryFlush( void )
{
	if( FreeMemoryQueueCount )
	{
		u32 i;

		for(i=0; i<FreeMemoryQueueCount; i++)
		{
			sys_FreeMemoryEz( FreeMemoryQueue[i].memory );
			if( FreeMemoryQueue[i].callback )
			{
				FreeMemoryQueue[i].callback( FreeMemoryQueue[i].arg );
			}
		}
		FreeMemoryQueueCount = 0;
	}
}


//------------------------------------------------------------------
/**
 * ���荞�ݒ�������������N�G�X�g
 *
 * @param   memory			Free�������������u���b�N�A�h���X
 * @param   callback		Free��A�Ăяo�������R�[���o�b�N
 * @param   arg				�R�[���o�b�N����
 *
 */
//------------------------------------------------------------------
void BoxAppView_IrqMemoryFreeReq( void* memory, pMemoryFreeTaskCallBack callback, void* arg )
{
	GF_ASSERT(FreeMemoryQueueCount<FREE_MEMORY_QUEUE_MAX);

	FreeMemoryQueue[FreeMemoryQueueCount].memory = memory;
	FreeMemoryQueue[FreeMemoryQueueCount].callback = callback;
	FreeMemoryQueue[FreeMemoryQueueCount].arg = arg;
	FreeMemoryQueueCount++;
}


