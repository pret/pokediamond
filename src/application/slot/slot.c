//******************************************************************************
/**
 * 
 * @file	slot.c
 * @brief	�~�j�Q�[���@�X���b�g
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#define SLOT_LOCAL
#include "common.h"
#include "system\wipe.h"
#include "slot_local.h"

//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	struct
//==============================================================================
typedef struct _TAG_SLOTPROC SLOTPROC;

//--------------------------------------------------------------
///	SLOTPROC�\����
//--------------------------------------------------------------
typedef struct _TAG_SLOTPROC
{
	SLOT_PARAM *param;
	SLOTMAIN *main;
};

#define SLOTPROC_SIZE (sizeof(SLOTPROC))

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void slot_SlotParamReflect( SLOTPROC *slotproc, SLOTMAIN *main );

static SLOTMAIN * slot_MainWorkInit( SLOT_PARAM *param );
static void slot_MainWorkDelete( SLOTMAIN *main );

static void slotDraw_Init( SLOTMAIN *main );
static void slotDraw_Delete( SLOTMAIN *main );

static void slotDraw_VramBankSet( void );
static void slotDraw_BGLSet( GF_BGL_INI *ini );
static void slotDraw_BGLDelete( GF_BGL_INI *ini );
static void slotDraw_WindowInit( void );

static void slotBG_Init( SLOTMAIN *main );

static void slotCharPalM_Init( void );
static void slotCharPalM_Delete( void );

static void slotClAct_Init( SLOTMAIN *main );
static void slotClAct_Delete( SLOTMAIN *main );
static void slotClAct_VramInit( SLOTMAIN *main );
static void slotClAct_VramDelete( SLOTMAIN *main );

static void slotEoa_Init( SLOTMAIN *main );
static void slotEoa_Delete( SLOTMAIN *main );

static int slotBGM_ChangeCheck( SLOTMAIN *main );
static void slotBGM_Init( SLOTMAIN *main );
static void slotBGM_Delete( SLOTMAIN *main );
static void slotBGM_Tcb( TCB_PTR tcb, void *wk );

static void slot_VBlankFunc( void *work );

static void slotArc_HandleOpen( SLOTMAIN *main );
static void slotArc_HandleClose( SLOTMAIN *main );

static const BMPWIN_DAT DATA_SlotBmpWinList[SLOTWIN_MAX];

#ifdef DEBUG_SLOT_PARAM_INIT
static SLOT_PARAM DEBUG_SlotParam;
static int DEBUG_SlotCoin;
#endif

//==============================================================================
//	�X���b�g	�v���Z�X
//==============================================================================
//--------------------------------------------------------------
/**
 * �X���b�g�v���Z�X�@������
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 * @retval	PROC_RESULT	PROC_RESULT
 */
//--------------------------------------------------------------
PROC_RESULT SlotProc_Init( PROC *proc, int *seq )
{
	SLOTPROC *slotproc;
	SLOTMAIN *main;
	SLOT_PARAM *param;
    
	sys_VBlankFuncChange( NULL, NULL );
	sys_HBlankIntrStop();
	
	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_SLOT, SLOT_HEAPSIZE );
	
	slotproc = PROC_AllocWork( proc, SLOTPROC_SIZE, HEAPID_SLOT );
	memset( slotproc, 0, SLOTPROC_SIZE );
	
	param = PROC_GetParentWork( proc );
	
#ifdef DEBUG_SLOT_PARAM_INIT
	if( param == NULL ){
		
		DEBUG_SlotCoin = 1000;
		DEBUG_SlotParam.coin = &DEBUG_SlotCoin;
		DEBUG_SlotParam.hard = SLOT_HARD_5;
		DEBUG_SlotParam.record = NULL;
		DEBUG_SlotParam.r_count = 0;
		
		param = &DEBUG_SlotParam;
	}
	
	slotproc->param = param;
	main = slot_MainWorkInit( slotproc->param );
	slotproc->main = main;
#else
	slotproc->param = param;
	main = slot_MainWorkInit( slotproc->param );
	slotproc->main = main;
#endif
	
	slotArc_HandleOpen( main );
	
	slotEoa_Init( main );
	slotDraw_Init( main );
	slotBG_Init( main );
	SlotTalkWinFont_Init( main );
	slotCharPalM_Init();
	slotClAct_Init( main );
	
	SlotMain_GameInit( main );
	
	SlotSubEoa_ReelPatternInit( main );
	SlotSubEoa_CreditFontInit( main );
	SlotSubEoa_PayOutFontInit( main );
	
	Snd_DataSetByScene( SND_SCENE_SUB_SLOT, 0, 0 );	// �T�E���h�f�[�^���[�h(�X���b�g)(BGM���p��)
	slotBGM_Init( main );
	
	WIPE_SYS_Start( WIPE_PATTERN_WMS,
		WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, 8, 1, HEAPID_SLOT );	
	
	return( PROC_RES_FINISH );
}

//--------------------------------------------------------------
/**
 * �X���b�g�v���Z�X�@���C��
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 * @retval	PROC_RESULT	PROC_RESULT
 */
//--------------------------------------------------------------
PROC_RESULT SlotProc_Main( PROC *proc, int *seq )
{
	SLOTPROC *slotproc = PROC_GetWork( proc );
	SLOTMAIN *main = slotproc->main;
	
	switch( *seq ){
	case 0:
		if( WIPE_SYS_EndCheck() ){
			(*seq)++;
		}
		break;
	case 1:
		if( SlotMain_Game(main) == TRUE ){
			(*seq)++;
			WIPE_SYS_Start( WIPE_PATTERN_FSAM,
				WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, 8, 1, HEAPID_SLOT );
			
			SlotBGM_Play( main, BGM_NORMAL );
		}
		break;
	case 2:
		if( WIPE_SYS_EndCheck() == 0 ){
			break;
		}
		
		(*seq)++;
	case 3:
		if( slotBGM_ChangeCheck(main) == FALSE ){
			return( PROC_RES_FINISH );
		}
	}
	
	EOA_SysDraw( main->eoa_sys );
	ClActSetDataDraw( main->clactset );
	
	return( PROC_RES_CONTINUE );
}

//--------------------------------------------------------------
/**
 * �X���b�g�v���Z�X�@�I��
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 * @retval	PROC_RESULT	PROC_RESULT
 */
//--------------------------------------------------------------
PROC_RESULT SlotProc_End( PROC *proc, int *seq )
{
	SLOTPROC *slotproc = PROC_GetWork( proc );
	SLOTMAIN *main = slotproc->main;
	
	sys_VBlankFuncChange( NULL, NULL );
	
	slot_SlotParamReflect( slotproc, main );
	
	slotEoa_Delete( main );
	slotDraw_Delete( main );
	SlotTalkWinFont_Delete( main );
	
	SlotMain_GameDelete( main );
	slotBGM_Delete( main );
	
	slotArc_HandleClose( main );
	slot_MainWorkDelete( main );
	PROC_FreeWork( proc );
	sys_DeleteHeap( HEAPID_SLOT );
	
	return( PROC_RES_FINISH );
}

//--------------------------------------------------------------
/**
 * �I������SLOT_PARAM���f
 * @param	slotproc	SLOTPROC
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slot_SlotParamReflect( SLOTPROC *slotproc, SLOTMAIN *main )
{
	u32 credit = main->credit;
	if( credit > SLOT_COIN_MAX ){ credit = SLOT_COIN_MAX; }
	(*slotproc->param->coin) = credit;
	slotproc->param->r_count = main->bonus_continue_count_max;
	
	if( slotproc->param->record != NULL ){
		RECORD_Add( slotproc->param->record, RECID_SLOT_FEAVER, main->bonus_hit_count );	
	}
}

//==============================================================================
//	�X���b�g�@���C�����[�N
//==============================================================================
//--------------------------------------------------------------
/**
 * SLOTMAIN������
 * @param	slotparam	SLOT_PARAM
 * @retval	SLOTPROC	SLOTPROC *
 */
//--------------------------------------------------------------
static SLOTMAIN * slot_MainWorkInit( SLOT_PARAM *param )
{
	SLOTMAIN *main = Slot_AllocMemory( SLOTMAIN_SIZE );
	
	main->credit = *(param->coin);
	main->hard = param->hard;
	main->win_type = param->win_type;
	return( main );
}

//--------------------------------------------------------------
/**
 * SLOTMAIN�폜
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slot_MainWorkDelete( SLOTMAIN *main )
{
	sys_FreeMemoryEz( main );
}

//==============================================================================
//	�`��
//==============================================================================
//--------------------------------------------------------------
/**
 * �`�揉����
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotDraw_Init( SLOTMAIN *main )
{
	main->bgl = GF_BGL_BglIniAlloc( HEAPID_SLOT );
	
	slotDraw_VramBankSet();
	slotDraw_BGLSet( main->bgl );
	slotDraw_WindowInit();
	
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	
	G2_SetBG0Priority( 0 );
	G2_SetBG1Priority( 1 );
	G2_SetBG2Priority( 2 );
	G2_SetBG3Priority( 3 );
	G2S_SetBG0Priority( 0 );
	G2S_SetBG1Priority( 1 );
	G2S_SetBG2Priority( 2 );
	G2S_SetBG3Priority( 3 );
	
	G2_SetBlendAlpha( GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_OBJ, 8, 9 );
	
	sys_VBlankFuncChange( slot_VBlankFunc, main );
}

//--------------------------------------------------------------
/**
 * �`��폜
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotDraw_Delete( SLOTMAIN *main )
{
	slotDraw_BGLDelete( main->bgl );
	slotClAct_Delete( main );
	slotCharPalM_Delete();
}

//--------------------------------------------------------------
/**
 * VRAM BANK���蓖��
 * @param	nothing
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotDraw_VramBankSet( void )
{
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
}

//--------------------------------------------------------------
/**
 * BG�������@
 * @param	bgl		GF_BGL_INI
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotDraw_BGLSet( GF_BGL_INI *ini )
{
	GX_SetDispSelect( GX_DISP_SELECT_MAIN_SUB );
	
	{	//BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}
	
	{	//���ʁ@��b�E�B���h�E
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		
		GF_BGL_BGControlSet( ini, BGFRAME_KAIWA, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, BGFRAME_KAIWA );
		GF_BGL_ClearCharSet( BGFRAME_KAIWA, 32, 0, HEAPID_SLOT );
	}
	
	{	//�X���b�g��
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0800, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		
		GF_BGL_BGControlSet( ini, BGFRAME_SLOT, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, BGFRAME_SLOT );
	}
	
	{	//�X���b�g�e
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x14000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		
		GF_BGL_BGControlSet( ini, BGFRAME_SLOT_SHADOW, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, BGFRAME_SLOT_SHADOW );
	}
	
	{	//����ʔw�i
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1800, GX_BG_CHARBASE_0x20000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		
		GF_BGL_BGControlSet( ini, BGFRAME_BGSUB, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, BGFRAME_BGSUB );
	}
	
#ifdef DEBUG_ON_SLOT
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x2000, GX_BG_CHARBASE_0x2c000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		
		GF_BGL_BGControlSet( ini, BGFRAME_SUB_DEBUG, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, BGFRAME_SUB_DEBUG );
	}
#endif
}

//--------------------------------------------------------------
/**
 * BG�폜
 * @param	bgl		GF_BGL_INI
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotDraw_BGLDelete( GF_BGL_INI *ini )
{
	GF_BGL_BGControlExit( ini, BGFRAME_KAIWA );
	GF_BGL_BGControlExit( ini, BGFRAME_SLOT );
	GF_BGL_BGControlExit( ini, BGFRAME_SLOT_SHADOW );
	GF_BGL_BGControlExit( ini, BGFRAME_BGSUB );
	
#ifdef DEBUG_ON_SLOT
	GF_BGL_BGControlExit( ini, BGFRAME_SUB_DEBUG );
#endif
	
	sys_FreeMemoryEz( ini );
}

//--------------------------------------------------------------
/**
 * �E�B���h�E������
 * @param	nothing
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotDraw_WindowInit( void )
{
	GX_SetVisibleWnd( GX_WNDMASK_W0 );
	
	G2_SetWnd0InsidePlane(
			GX_WND_PLANEMASK_BG0 |
			GX_WND_PLANEMASK_BG1 |
			GX_WND_PLANEMASK_BG2 |
			GX_WND_PLANEMASK_BG3 |
			GX_WND_PLANEMASK_OBJ,
			TRUE );
	
	G2_SetWndOutsidePlane(
			GX_WND_PLANEMASK_BG0 |
			GX_WND_PLANEMASK_BG1 |
			GX_WND_PLANEMASK_BG2 |
			GX_WND_PLANEMASK_BG3 |
			GX_WND_PLANEMASK_OBJ,
			TRUE );
			
	G2_SetWnd0Position( 0, 0, 255, 255 );
}

//==============================================================================
//	�X���b�g BG
//==============================================================================
//--------------------------------------------------------------
/**
 * BG������
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotBG_Init( SLOTMAIN *main )
{
	//�X���b�gBG�p���b�g
	void *buf = SlotArc_DataLoad( main, NARC_slot_slot_mount_NCLR, FALSE );
	NNS_G2dGetUnpackedPaletteData( buf, &main->bg_pPltt );
	GF_BGL_PaletteSet( BGFRAME_SLOT, main->bg_pPltt->pRawData, 
		BGF_SLOT_PLTT_SIZE, BGF_SLOT_PLTT_OFFSET );
	sys_FreeMemoryEz( buf );
	
	//�X���b�g��
	buf = SlotArc_DataLoad( main, NARC_slot_slot_machine_NCGR, FALSE );
	NNS_G2dGetUnpackedCharacterData( buf, &main->bg_pChar );
	GF_BGL_LoadCharacter( main->bgl, BGFRAME_SLOT,
		main->bg_pChar->pRawData, main->bg_pChar->szByte, BGF_SLOT_CHAR_OFFSET );
	sys_FreeMemoryEz( buf );
	
	buf = SlotArc_DataLoad( main, NARC_slot_slot_machine_NSCR, FALSE );
	NNS_G2dGetUnpackedScreenData( buf, &main->bg_pScr );
	GF_BGL_ScreenBufSet( main->bgl, BGFRAME_SLOT,
		(void*)main->bg_pScr->rawData, main->bg_pScr->szByte );
	GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SLOT );
	sys_FreeMemoryEz( buf );
	
	//�e
	buf = SlotArc_DataLoad( main, NARC_slot_slot_bg_shadow_NCGR, FALSE );
	NNS_G2dGetUnpackedCharacterData( buf, &main->bg_pChar );
	GF_BGL_LoadCharacter( main->bgl, BGFRAME_SLOT_SHADOW,
		main->bg_pChar->pRawData, main->bg_pChar->szByte, BGF_SLOT_CHAR_OFFSET );
	sys_FreeMemoryEz( buf );
	
	buf = SlotArc_DataLoad( main, NARC_slot_slot_bg_shadow_NSCR, FALSE );
	NNS_G2dGetUnpackedScreenData( buf, &main->bg_pScr );
	GF_BGL_ScreenBufSet( main->bgl, BGFRAME_SLOT_SHADOW,
		(void*)main->bg_pScr->rawData, main->bg_pScr->szByte );
	GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SLOT_SHADOW );
	sys_FreeMemoryEz( buf );
	
	//�����
	buf = SlotArc_DataLoad( main, NARC_slot_slot_mount_NCLR, FALSE );
	NNS_G2dGetUnpackedPaletteData( buf, &main->bg_pPltt );
	GF_BGL_PaletteSet( BGFRAME_BGSUB, main->bg_pPltt->pRawData, 
		BGF_SLOT_PLTT_SIZE, BGF_SLOT_PLTT_OFFSET );
	sys_FreeMemoryEz( buf );
	
	buf = SlotArc_DataLoad( main, NARC_slot_slot_mount_NCGR, FALSE );
	NNS_G2dGetUnpackedCharacterData( buf, &main->bg_pChar );
	GF_BGL_LoadCharacter( main->bgl, BGFRAME_BGSUB,
		main->bg_pChar->pRawData, main->bg_pChar->szByte, 0 );
	sys_FreeMemoryEz( buf );
	
	buf = SlotArc_DataLoad( main, NARC_slot_slot_mount_NSCR, FALSE );
	NNS_G2dGetUnpackedScreenData( buf, &main->bg_pScr );
	GF_BGL_ScreenBufSet( main->bgl, BGFRAME_BGSUB,
		(void*)main->bg_pScr->rawData, main->bg_pScr->szByte );
	GF_BGL_LoadScreenReq( main->bgl, BGFRAME_BGSUB );
	sys_FreeMemoryEz( buf );
	
	//����ʁ@�f�o�b�O
#ifdef DEBUG_ON_SLOT
	main->bg_pPltt = GF_BGL_NTRCHR_PalLoad( buf, HEAPID_SLOT, "data/nfont.NCLR" );
	GF_BGL_PaletteSet( BGFRAME_SUB_DEBUG, main->bg_pPltt->pRawData, 32, BGF_SLOT_PANO_FONT*32 );
	sys_FreeMemoryEz( buf );
	GF_BGL_NTRCHR_CharLoad( main->bgl, BGFRAME_SUB_DEBUG, "data/nfont.NCGR", 0 );
#endif
}

//==============================================================================
//	�X���b�g�@�t�H���g
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�H���g ������
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotTalkWinFont_Init( SLOTMAIN *main )
{
	int i;
	MSGWORK *msg = &main->msgwork;
	
	MenuWinGraphicSet( main->bgl, BGFRAME_KAIWA,
		BGF_SLOT_CHAR_NO_WIN, BGF_SLOT_PANO_FONT, 0, HEAPID_SLOT );
	
	TalkWinGraphicSet(
		main->bgl, BGFRAME_KAIWA, BGF_SLOT_CHAR_NO_TALK,
		BGF_SLOT_PANO_TALK, main->win_type, HEAPID_SLOT );
	
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, BGF_SLOT_PANO_FONT*32, HEAPID_SLOT );
	
	msg->msgman = MSGMAN_Create(
			MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_slot_dat, HEAPID_SLOT );
	
	msg->wordset = WORDSET_Create( HEAPID_SLOT );
	
	for( i = 0; i < SLOTWIN_MAX; i++ ){
		GF_BGL_BmpWinAddEx( main->bgl, &msg->bmpwin[i], &DATA_SlotBmpWinList[i] );
	}
	
	msg->strbuf = STRBUF_Create( STR_BUF_SIZE, HEAPID_SLOT );
}

//--------------------------------------------------------------
/**
 * �t�H���g�폜
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotTalkWinFont_Delete( SLOTMAIN *main )
{
	int i;
	MSGWORK *msg = &main->msgwork;
	
	for( i = 0; i < SLOTWIN_MAX; i++ ){
		GF_BGL_BmpWinOff( &msg->bmpwin[i] );
		GF_BGL_BmpWinDel( &msg->bmpwin[i] );
	}
	
	MSGMAN_Delete( msg->msgman );
	WORDSET_Delete( msg->wordset );
	STRBUF_Delete( msg->strbuf );
}

//--------------------------------------------------------------
/**
 * ��b�E�B���h�E�\��
 * @param	main	SLOTMAIN
 * @param	msgno	���b�Z�[�W�f�[�^No
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotTalkWin_Write( SLOTMAIN *main, u32 msgno )
{
	MSGWORK *msg = &main->msgwork;
	
	BmpTalkWinWrite( &msg->bmpwin[SLOTWIN_TALK],
			WINDOW_TRANS_OFF, BGF_SLOT_CHAR_NO_TALK, BGF_SLOT_PANO_TALK );
	
	GF_BGL_BmpWinDataFill( &msg->bmpwin[SLOTWIN_TALK], FBMP_COL_WHITE );
	
	MSGMAN_GetString( msg->msgman, msgno, msg->strbuf );
	GF_STR_PrintSimple( &msg->bmpwin[SLOTWIN_TALK],
			FONT_TALK, msg->strbuf, 0, 0, MSG_NO_PUT, NULL );
	
	GF_BGL_BmpWinOnVReq( &msg->bmpwin[SLOTWIN_TALK] );	
}

//--------------------------------------------------------------
/**
 * ��b�E�B���h�E�N���A
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotTalkWin_Clear( SLOTMAIN *main )
{
	MSGWORK *msg = &main->msgwork;
	
	BmpTalkWinClear( &msg->bmpwin[SLOTWIN_TALK], WINDOW_TRANS_OFF );
	GF_BGL_BmpWinDataFill( &msg->bmpwin[SLOTWIN_TALK], FBMP_COL_NULL );
	GF_BGL_BmpWinOnVReq( &msg->bmpwin[SLOTWIN_TALK] );	
}

//==============================================================================
//	�X���b�g�@�L�����A�p���b�g�}�l�[�W��
//==============================================================================
//--------------------------------------------------------------
/**
 * �L�����A�p���b�g�}�l�[�W��������
 * @param	nothing
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotCharPalM_Init( void )
{
	CHAR_MANAGER_MAKE cm = {
		CHAR_MANAGER_MAX,CHAR_VRAMTRANS_M_SIZE,CHAR_VRAMTRANS_S_SIZE,HEAPID_SLOT};
	
//	InitCharManager( &cm );
	InitCharManagerReg( &cm, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_128K );
	InitPlttManager( PLTT_MANAGER_MAX, HEAPID_SLOT );
	
	CharLoadStartAll();
	PlttLoadStartAll();
}

//--------------------------------------------------------------
/**
 * �L�����A�p���b�g�}�l�[�W���폜
 * @param	nothing
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotCharPalM_Delete( void )
{
	DeleteCharManager();
	DeletePlttManager();
}

//==============================================================================
//	�X���b�g�@�Z���A�N�^�[
//==============================================================================
//--------------------------------------------------------------
/**
 * �Z���A�N�^�[�@������
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotClAct_Init( SLOTMAIN *main )
{
	//OAM�}�l�[�W���[�̏�����
	NNS_G2dInitOamManagerModule();
	
	//���LOAM�}�l�[�W���쐬
	//�����_���pOAM�}�l�[�W���쐬
	//�����ō쐬����OAM�}�l�[�W�����݂�Ȃŋ��L����
	REND_OAMInit( 
			0, 128,		// ���C�����OAM�Ǘ��̈�
			0, 32,		// ���C����ʃA�t�B���Ǘ��̈�
			0, 128,		// �T�u���OAM�Ǘ��̈�
			0, 32,		// �T�u��ʃA�t�B���Ǘ��̈�
			HEAPID_SLOT );
	
	main->clactset = ClActSetDataInit( HEAPID_SLOT, SLOT_CLACT_MAX, SLOT_CLACT_TRANS_MAX,
		SLOT_CHAR_MAX, SLOT_PLTT_MAX, SLOT_CELL_MAX, SLOT_ANM_MAX,
		SLOT_CHARID_MAX, SLOT_PLTTID_MAX, SLOT_CELLID_MAX, SLOT_ANMID_MAX );
	
	slotClAct_VramInit( main );
}

//--------------------------------------------------------------
/**
 * �Z���A�N�^�[�@�폜
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotClAct_Delete( SLOTMAIN *main )
{
	slotClAct_VramDelete( main );
	ClActSetDataDelete( main->clactset );
	REND_OAM_Delete();
}

//--------------------------------------------------------------
/**
 * �Z���A�N�^�[VRAM������
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotClAct_VramInit( SLOTMAIN *main )
{
	ClActCharAdd( main->clactset, G2D_2DMAIN,
		main->arc_handle, NARC_slot_slotreel_NCGR, SLOT_CHARID_REEL );
	ClActCharAdd( main->clactset, G2D_2DMAIN,
		main->arc_handle, NARC_slot_credit_font_NCGR, SLOT_CHARID_CREDITFONT );
	ClActCharAdd( main->clactset, G2D_2DSUB,
		main->arc_handle, NARC_slot_slot_bonus_NCGR, SLOT_CHARID_BONUSFONT );
	ClActCharAdd( main->clactset, G2D_2DSUB,
		main->arc_handle, NARC_slot_slot_get_NCGR, SLOT_CHARID_GETFONT );
	ClActCharAdd( main->clactset, G2D_2DSUB,
		main->arc_handle, NARC_slot_bonus_get_font_NCGR, SLOT_CHARID_BONUSGETFONT );
	ClActCharAdd( main->clactset, G2D_2DSUB,
		main->arc_handle, NARC_slot_moon_font_NCGR, SLOT_CHARID_MOONFONT );
	
	ClActPlttAdd( main->clactset, G2D_2DMAX,	//�r�b�O�q�b�g�A����ʗ��p
			main->arc_handle, NARC_slot_slotreel_NCLR, SLOT_PLTTID_REEL );
	ClActPlttAdd( main->clactset, G2D_2DMAIN,
			main->arc_handle, NARC_slot_credit_font_NCLR, SLOT_PLTTID_CREDITFONT );
	ClActPlttAdd( main->clactset, G2D_2DSUB,
			main->arc_handle, NARC_slot_bonus_get_font_NCLR, SLOT_PLTTID_BONUSFONT );
	ClActPlttAdd( main->clactset, G2D_2DSUB,
			main->arc_handle, NARC_slot_moon_font_NCLR, SLOT_PLTTID_MOONFONT );
	
	ClActCellAdd( main->clactset,
			main->arc_handle, NARC_slot_slotreel_NCER, SLOT_CELLID_REEL );
	ClActCellAdd( main->clactset,
			main->arc_handle, NARC_slot_credit_font_NCER, SLOT_CELLID_CREDITFONT );
	ClActCellAdd( main->clactset,
			main->arc_handle, NARC_slot_slot_bonus_NCER, SLOT_CELLID_BONUSFONT );
	ClActCellAdd( main->clactset,
			main->arc_handle, NARC_slot_slot_get_NCER, SLOT_CELLID_GETFONT );
	ClActCellAdd( main->clactset,
			main->arc_handle, NARC_slot_bonus_get_font_NCER, SLOT_CELLID_BONUSGETFONT );
	ClActCellAdd( main->clactset,
			main->arc_handle, NARC_slot_moon_font_NCER, SLOT_CELLID_MOONFONT );
	
	ClActAnmAdd( main->clactset,
			main->arc_handle, NARC_slot_slotreel_NANR, SLOT_ANMID_REEL );
	ClActAnmAdd( main->clactset,
			main->arc_handle, NARC_slot_credit_font_NANR, SLOT_ANMID_CREDITFONT );
	ClActAnmAdd( main->clactset,
			main->arc_handle, NARC_slot_slot_bonus_NANR, SLOT_ANMID_BONUSFONT );
	ClActAnmAdd( main->clactset,
			main->arc_handle, NARC_slot_slot_get_NANR, SLOT_ANMID_GETFONT );
	ClActAnmAdd( main->clactset,
			main->arc_handle, NARC_slot_bonus_get_font_NANR, SLOT_ANMID_BONUSGETFONT );
	ClActAnmAdd( main->clactset,
			main->arc_handle, NARC_slot_moon_font_NANR, SLOT_ANMID_MOONFONT );
	
	ClActCharVramAreaSet( main->clactset, SLOT_CHARID_REEL );
	ClActCharVramAreaSet( main->clactset, SLOT_CHARID_CREDITFONT );
	ClActCharVramAreaSet( main->clactset, SLOT_CHARID_BONUSFONT );
	ClActCharVramAreaSet( main->clactset, SLOT_CHARID_GETFONT );
	ClActCharVramAreaSet( main->clactset, SLOT_CHARID_BONUSGETFONT );
	ClActCharVramAreaSet( main->clactset, SLOT_CHARID_MOONFONT );
	ClActCharResDelete( main->clactset, SLOT_CHARID_REEL );
	ClActCharResDelete( main->clactset, SLOT_CHARID_CREDITFONT );
	ClActCharResDelete( main->clactset, SLOT_CHARID_BONUSFONT );
	ClActCharResDelete( main->clactset, SLOT_CHARID_GETFONT );
	ClActCharResDelete( main->clactset, SLOT_CHARID_BONUSGETFONT );
	ClActCharResDelete( main->clactset, SLOT_CHARID_MOONFONT );
	
	ClActPlttVramAreaSet( main->clactset, SLOT_PLTTID_REEL );
	ClActPlttVramAreaSet( main->clactset, SLOT_PLTTID_CREDITFONT );
	ClActPlttVramAreaSet( main->clactset, SLOT_PLTTID_BONUSFONT );
	ClActPlttVramAreaSet( main->clactset, SLOT_PLTTID_MOONFONT );
	ClActPlttResDelete( main->clactset, SLOT_PLTTID_REEL );
	ClActPlttResDelete( main->clactset, SLOT_PLTTID_CREDITFONT );
	ClActPlttResDelete( main->clactset, SLOT_PLTTID_BONUSFONT );
	ClActPlttResDelete( main->clactset, SLOT_PLTTID_MOONFONT );
}

//--------------------------------------------------------------
/**
 * �Z���A�N�^�[VRAM�폜
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotClAct_VramDelete( SLOTMAIN *main )
{
}

//==============================================================================
//	�X���b�g EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA������
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotEoa_Init( SLOTMAIN *main )
{
	main->eoa_sys = EOA_SysInit( HEAPID_SLOT, SLOT_EOA_MAX );
}

//--------------------------------------------------------------
/**
 * EOA�폜
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotEoa_Delete( SLOTMAIN *main )
{
	EOA_SysDeleteAll( main->eoa_sys );
}

//==============================================================================
//	BGM
//==============================================================================
//--------------------------------------------------------------
/**
 * �w��BGM�Đ�
 * @param	main	SLOTMAIN
 * @param	type	BGMTYPE
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotBGM_Play( SLOTMAIN *main, BGMTYPE type )
{
	SLOTBGM *bgm = &main->bgm;
	
	if( bgm->now_play == type || bgm->next_play == type ){
		return;
	}
	
	bgm->next_play = type;
	bgm->seq_no = 1;
	bgm->chg_flag = TRUE;
}

//--------------------------------------------------------------
/**
 * BGM�Đ��`�F�b�N
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=BGM�؂�ւ���
 */
//--------------------------------------------------------------
static int slotBGM_ChangeCheck( SLOTMAIN *main )
{
	SLOTBGM *bgm = &main->bgm;
	return( bgm->chg_flag );
}

//--------------------------------------------------------------
/**
 * BGM�Ǘ�������
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotBGM_Init( SLOTMAIN *main )
{
	SLOTBGM *bgm = &main->bgm;
	
	bgm->now_play = BGM_NORMAL;
	bgm->next_play = BGM_MAX;
	bgm->tcb = TCB_Add( slotBGM_Tcb, main, TCBPRI_BGM );
}

//--------------------------------------------------------------
/**
 * BGM�Ǘ��폜
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotBGM_Delete( SLOTMAIN *main )
{
	TCB_Delete( main->bgm.tcb );
}

//--------------------------------------------------------------
/**
 * BGM�Ǘ�
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotBGM_Tcb( TCB_PTR tcb, void *wk )
{
	SLOTMAIN *main = wk;
	SLOTBGM *bgm = &main->bgm;
	
	switch( bgm->seq_no ){
	case 0:
		break;
	case 1:
		switch( bgm->now_play ){
		case BGM_NORMAL: Snd_PlayerPause( PLAYER_FIELD, TRUE ); break;
		case BGM_HIT: Snd_BgmStop( SEQ_SLOT_ATARI, 0 ); break;
		case BGM_BIGHIT: Snd_BgmStop( SEQ_SLOT_OOATARI, 0 ); break;
		}
		
		bgm->seq_no++;
		break;
	case 2:
		switch( bgm->next_play ){
		case BGM_NORMAL: Snd_PlayerPause( PLAYER_FIELD, FALSE ); break;
		case BGM_HIT: Snd_BgmPlayBasicData( SEQ_SLOT_ATARI ); break;
		case BGM_BIGHIT: Snd_BgmPlayBasicData( SEQ_SLOT_OOATARI ); break;
		}
		
		bgm->now_play = bgm->next_play;
		bgm->next_play = BGM_MAX;
		bgm->chg_flag = FALSE;
		bgm->seq_no = 0;
	}
}

//==============================================================================
//	�X���b�g�@V�u�����N
//==============================================================================
//--------------------------------------------------------------
/**
 * �X���b�gVBlank����
 * @param	work	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slot_VBlankFunc( void *work )
{
	SLOTMAIN *main = work;
	
	//�Z���A�N�^�[Vram�]���}�l�[�W���[���s
	DoVramTransferManager();
	
	//�����_�����LOAM�}�l�[�W��Vram�]��
	REND_OAMTrans();
	
	//BG�]��
	GF_BGL_VBlankFunc( main->bgl );
}

//==============================================================================
//	�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * �������m��
 * @param	size	�m�ۃT�C�Y
 * @retval	void*	�m�ۂ����̈�
 */
//--------------------------------------------------------------
void * Slot_AllocMemory( u32 size )
{
	void *alloc = sys_AllocMemory( HEAPID_SLOT, size );
	GF_ASSERT( alloc != NULL && "Slot_AllocMemory() alloc error" );
	memset( alloc, 0, size );
	return( alloc );
}

//--------------------------------------------------------------
/**
 * �������m�ہ@���
 * @param	size	�m�ۃT�C�Y
 * @retval	void*	�m�ۂ����̈�
 */
//--------------------------------------------------------------
void * Slot_AllocMemoryLo( u32 size )
{
	void *alloc = sys_AllocMemoryLo( HEAPID_SLOT, size );
	GF_ASSERT( alloc != NULL && "Slot_AllocMemory() alloc error" );
	memset( alloc, 0, size );
	return( alloc );
}

//--------------------------------------------------------------
/**
 * �A�[�J�C�u�I�[�v��
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotArc_HandleOpen( SLOTMAIN *main )
{
	main->arc_handle = ArchiveDataHandleOpen( ARC_SLOT, HEAPID_SLOT );
}

//--------------------------------------------------------------
/**
 * �A�[�J�C�u�N���[�Y
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotArc_HandleClose( SLOTMAIN *main )
{
	ArchiveDataHandleClose( main->arc_handle );
}

//--------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^���[�h
 * @param	main	SLOTMAIN
 * @param	id		�f�[�^�C���f�b�N�X
 * @param	fb		TRUE=�O FALSE=��납��̈�擾
 * @retval	void*	���[�h�����f�[�^
 */
//--------------------------------------------------------------
void * SlotArc_DataLoad( SLOTMAIN *main, u32 id, int fb )
{
	void *buf;
	u32 size = ArchiveDataSizeGetByHandle( main->arc_handle, id );
	
	if( fb == TRUE ){
		buf = sys_AllocMemory( HEAPID_SLOT, size );
	}else{
		buf = sys_AllocMemoryLo( HEAPID_SLOT, size );
	}
	
	GF_ASSERT( buf != NULL && "slotArc_DataLoad() alloc error" );
	ArchiveDataLoadByHandle( main->arc_handle, id, buf );
	return( buf );
}

//==============================================================================
//	msg data
//==============================================================================
//--------------------------------------------------------------
///	�r�b�g�}�b�v�E�B���h�E
//--------------------------------------------------------------
static const BMPWIN_DAT DATA_SlotBmpWinList[SLOTWIN_MAX] =
{
	{ //SLOTWIN_TALK
		BGFRAME_KAIWA, 2, 19, 26, 4,
		BGF_SLOT_PANO_FONT, BGF_SLOT_CHAR_NO_TALK+TALK_WIN_CGX_SIZ,
	},
};
