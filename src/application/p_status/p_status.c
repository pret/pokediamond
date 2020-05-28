//============================================================================================
/**
 * @file	p_status.c
 * @brief	�|�P�����X�e�[�^�X���
 * @author	Hiroyuki Nakamura
 * @date	2004.12.21
 */
//============================================================================================
#include "common.h"
#include "gflib/touchpanel.h"
#include "gflib/strbuf_family.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "system/brightness.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/wordset.h"
#include "system/numfont.h"
#include "system/softsprite.h"
#include "system/buflen.h"
#include "system/wipe.h"
#include "system/window.h"
#include "battle/battle_common.h"
#include "poketool/monsno.h"
#include "poketool/pokeicon.h"
#include "poketool/pokeparty.h"
#include "poketool/waza_tool.h"
#include "contest/contest.h"
#include "contest/con_tool.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_pokestatus.h"
#include "itemtool/item.h"
#include "application/app_tool.h"
#include "application/poru_tool.h"
#include "communication/wm_icon.h"
#include "ribbon.h"
#include "system/snd_perap.h"

#include "../../field/sysflag.h"


#define	P_STATUS_H_GLOBAL
#include "application/p_status.h"
#include "pst_sys.h"
#include "pst_obj.h"
#include "pst_bmp.h"
#include "pst_3d.h"
#include "pst_sub.h"
#include "pst_snd_def.h"
#include "application/pst_gra.naix"


//============================================================================================
//	�萔��`
//============================================================================================
enum {
	SEQ_IN_SET = 0,
	SEQ_IN,					// �����t�F�[�h�҂�
	SEQ_MAIN,				// ���C���R���g���[��

	SEQ_WAZAIN,				// �Z�����C���҂�
	SEQ_WAZAOUT,			// �Z�����A�E�g�҂�

	SEQ_CON_WAZAIN,			// �R���e�X�g�Z�����C���҂�
	SEQ_CON_WAZAOUT,		// �R���e�X�g�Z�����A�E�g�҂�

	SEQ_WAZA_SELECT,		// �Z�I��
	SEQ_WAZA_CHANGE,		// �Z����ւ��I��
	SEQ_WAZA_OBOE,			// �Z�o��/�Y��
	SEQ_WAZA_OBOE_ERROR,	// �Z�o���G���[

	SEQ_RIBBON_IN,			// ���{�������C���҂�
	SEQ_RIBBON_OUT,			// ���{�������A�E�g�҂�
	SEQ_RIBBON_SELECT,		// ���{���I��

	SEQ_BUTTON_ANM,			// ����ʂ̃{�^���A�j���҂�

	SEQ_COND_INIT,			// �����L�[�҂�
	SEQ_COND_MSG,			// ���b�Z�[�W�\��
	SEQ_COND_END,			// �R���f�B�V�����ύX�I��

	SEQ_OUT_SET,			// �I���t�F�[�h�Z�b�g
	SEQ_OUT,				// �I���t�F�[�h�҂�
};

#define	TMP_MSGBUF_SIZ	( 128 )		// �e���|�������b�Z�[�W�o�b�t�@�T�C�Y

#define	PAGE_PRM_AREA_PX	( 14 )		// �y�[�W�̃X�N���[��PX�i�N���A�Ɏg�p�j
#define	PAGE_PRM_AREA_PY	( 4 )		// �y�[�W�̃X�N���[��PY
#define	PAGE_PRM_AREA_SX	( 19 )		// �y�[�W�̃X�N���[��SY
#define	PAGE_PRM_AREA_SY	( 20 )		// �y�[�W�̃X�N���[��SY

#define	HP_CHR_PALETTE	( 0xa000 )	// HP�Q�[�W�̃p���b�g
#define	HP_CHR_GREEN	( 0xc0 )	// HP�Q�[�W�̃L�����J�n�ʒu�i�΁j
#define	HP_CHR_YELLOW	( 0xe0 )	// HP�Q�[�W�̃L�����J�n�ʒu�i���j
#define	HP_CHR_RED		( 0x100 )	// HP�Q�[�W�̃L�����J�n�ʒu�i�ԁj
#define	HP_DOT_CHR_MAX	( 6 )		// HP�Q�[�W�̃L������
#define	HP_DOT_MAX		( 48 )		// HP�Q�[�W�̃h�b�g��
#define	HP_GAUGE_SCR_PX	( 24 )		// HP�Q�[�W�̕\��X���W
#define	HP_GAUGE_SCR_PY	( 6 )		// HP�Q�[�W�̕\��Y���W

#define	EXP_CGX				( 0xac )	// EXP�Q�[�W�L�����J�n�ʒu
#define	EXP_DOT_CHR_MAX		( 7 )		// EXP�Q�[�W�L������
#define	EXP_DOT_MAX			( 56 )		// EXP�Q�[�W�h�b�g��
#define	EXP_GAUGE_SCR_PX	( 23 )		// EXP�Q�[�W�\��X���W
#define	EXP_GAUGE_SCR_PY	( 23 )		// EXP�Q�[�W�\��Y���W

#define	HEART1_CHR_NUM	( 0x12c )	// �R���e�X�g�̃n�[�g�L�����J�n�ʒu�i�L�j
#define	HEART2_CHR_NUM	( 0x12e )	// �R���e�X�g�̃n�[�g�L�����J�n�ʒu�i���j
#define	HEART_MAX		( 6 )		// �R���e�X�g�̃n�[�g�L������
#define	HEART_PX		( 2 )		// �R���e�X�g�̃n�[�g�L�����\��X���W
#define	HEART_PY		( 32+15 )	// �R���e�X�g�̃n�[�g�L�����\��Y���W


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static PROC_RESULT PokeStatusProc_Init( PROC * proc, int * seq );
static PROC_RESULT PokeStatusProc_Main( PROC * proc, int * seq );
static PROC_RESULT PokeStatusProc_End( PROC * proc, int * seq );

static int PST_SeqIn( PST_WORK * wk );
static int PST_SeqMain( PST_WORK * wk );
static int PST_SeqWazaIn( PST_WORK * wk );
static int PST_SeqWazaOut( PST_WORK * wk );
static int PST_SeqContestWazaIn( PST_WORK * wk );
static int PST_SeqContestWazaOut( PST_WORK * wk );
static int PST_SeqWazaSelect( PST_WORK * wk );
static int PST_SeqWazaChange( PST_WORK * wk );
static int PST_SeqWazaAdd( PST_WORK * wk );
static int PST_SeqWazaAddError( PST_WORK * wk );
static int PST_SeqRibbonIn( PST_WORK * wk );
static int PST_SeqRibbonOut( PST_WORK * wk );
static int PST_SeqRibbonSelect( PST_WORK * wk );
static int PST_SeqButtnAnm( PST_WORK * wk );
static int PST_SeqCondUpInit( PST_WORK * wk );
static int PST_SeqCondUpMsgPut( PST_WORK * wk );
static int PST_SeqCondUpEnd( PST_WORK * wk );
static u8 PST_SeqOutSet( PST_WORK * wk );
static u8 PST_SeqOut( PST_WORK * wk );

static void PokeStatusVramBankSet(void);
static void PokeStatusBgSet( GF_BGL_INI * ini );
static void PokeStatusBgExit( GF_BGL_INI * ini );
static void PokeStatusBgGraphicSet( PST_WORK * wk );
static void PokeStatusAlphaSet(void);
static void PokeStatusVBlank( void * work );
static void MsgBufCreate( PST_WORK * wk );
static void MsgBufRelease( PST_WORK * wk );
static void PokeStatusSoftSpriteSet( PST_WORK * wk );
static void PokeDataSet( PST_WORK * wk );
static void PokeDataSet_PokePasoParam(PST_WORK * wk,POKEMON_PASO_PARAM * ppp,PST_POKEDATA * dat);
static void PokeDataSet_PokemonParam( PST_WORK * wk, POKEMON_PARAM * pp, PST_POKEDATA * dat );
static void PokeDataSet_PokeParty( PST_WORK * wk );
static void InitPageSet( PST_WORK * wk );
static void PST_PokeVoicePlay( PST_WORK * wk );

static void PageChangeWrite( PST_WORK * wk, u8 next );
static void PageChange( PST_WORK * wk, s8 mv );
static u8 SubButtonPageChg( PST_WORK * wk );
static void PST_ContestPageCheck( PST_WORK * wk );

static void PageBgScreenChg( PST_WORK * wk );
static void HPGaugeSet( PST_WORK * wk );
static void ExpGaugeSet( PST_WORK * wk );

static void PokeChange( PST_WORK * wk, s8 mv );
static s8 PokeSearch( PST_WORK * wk, s8 mv );
static s8 PokeSearch_PokemonParam( PST_WORK * wk, s8 mv );
static s8 PokeSearch_PokeParty( PST_WORK * wk, s8 mv );
static s8 PokeSearch_PokemonPasoParam( PST_WORK * wk, s8 mv );

static u8 WazaInfoScrollIn( PST_WORK * wk );
static u8 WazaInfoScrollOut( PST_WORK * wk );
static u8 WazaCursorMove( PST_WORK * wk, s8 mv );
static void WazaInfoChange( PST_WORK * wk );
static void WazaChangeMain( PST_WORK * wk );
static void WazaInfoPut( PST_WORK * wk );
static void BattleWazaInfoChg( PST_WORK * wk, u32 waza );
static void ContestWazaInfoChg( PST_WORK * wk, u32 waza );
static void PST_WazaSetInfoOff( PST_WORK * wk );
static void PST_WazaSetInfoChange( PST_WORK * wk );

static u8 ContestWazaInfoScrollIn( PST_WORK * wk );
static u8 ContestWazaInfoScrollOut( PST_WORK * wk );
static void ContestWazaHeartPut( PST_WORK * wk, u32 waza );
static void ContestWazaHeartInit( PST_WORK * wk );

static u8 RibbonInfoScrollIn( PST_WORK * wk );
static u8 RibbonInfoScrollOut( PST_WORK * wk );
static void RibbonSelect( PST_WORK * wk, s8 mv );
u8 PokeStatus_RibbonPosIDGet( PST_WORK * wk, u8 cur_pos );

static int PST_PorutoEatCehck( PST_WORK * wk );


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
// �v���Z�X��`�f�[�^
const PROC_DATA PokeStatusProcData = {
	PokeStatusProc_Init,
	PokeStatusProc_Main,
	PokeStatusProc_End,
	NO_OVERLAY_ID,
};




//--------------------------------------------------------------------------------------------
/**
 * �R���e�X�g�t���O���擾
 *
 * @param	sv		�Z�[�u�f�[�^
 *
 * @return	�R���e�X�g�t���O
 */
//--------------------------------------------------------------------------------------------
BOOL PokeStatus_ContestFlagGet( SAVEDATA * sv )
{
	return SysFlag_PSTContestCheck( SaveData_GetEventWork(sv) );
}


//============================================================================================
//	�v���Z�X�֐�
//============================================================================================

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
static PROC_RESULT PokeStatusProc_Init( PROC * proc, int * seq )
{
	PST_WORK * wk;

	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );
	GX_SetVisibleWnd( GX_WNDMASK_NONE );
	GXS_SetVisibleWnd( GX_WNDMASK_NONE );
	G2_BlendNone();
	G2S_BlendNone();

	sys_KeyRepeatSpeedSet( 4, 8 );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_POKESTATUS, 0x40000 );

	wk = PROC_AllocWork( proc, sizeof(PST_WORK), HEAPID_POKESTATUS );
	memset( wk, 0, sizeof(PST_WORK) );
	wk->dat = PROC_GetParentWork( proc );
	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_POKESTATUS );

	wk->p3d.poke_anm_sys = PokeAnm_AllocMemory( HEAPID_POKESTATUS, 1, 1 );

	FontProc_LoadBitData( FONT_SYSTEM, HEAPID_POKESTATUS );

	InitTPSystem();						// �^�b�`�p�l���V�X�e��������
	InitTPNoBuff(4);

	PST_ContestPageCheck( wk );

	PokeStatusVramBankSet();			// VRAM���蓖��
	PokeStatusBgSet( wk->bgl );			// BG������
	PokeStatusBgGraphicSet( wk );		// BG�O���t�B�b�N�Z�b�g
	PokeStatusAlphaSet();

	PokeStatus_3DInit( wk );			// 3D������

	MsgBufCreate( wk );					// ���b�Z�[�W�֘A�쐬

	PokeDataSet( wk );					// �|�P�����f�[�^�擾

	PokeStatusCellActInit( wk );		// �Z���A�N�^�[������
	PokeStatusCellActSet( wk );			// �Z���A�N�^�[�Z�b�g
	PokeStatus_SoftSpriteSet( wk );		// �\�t�g�E�F�A�X�v���C�g�Z�b�g
	PokeStatusBallAnmChg( wk );			// �ߊl�{�[���؂�ւ�
	PokeStatus_StIconChg( wk );			// ��Ԉُ�A�C�R���؂�ւ�

	PokeStatus_DefaultBmpAdd( wk );
	InitPageSet( wk );					// �����y�[�W�쐬

	PokeStatus_SubButtonMake( wk );		// ����ʂ̃{�^���Z�b�g

	PokeStatus_CameraInit( wk );		// �J�����Z�b�g

	sys_VBlankFuncChange( PokeStatusVBlank, wk );	// VBlank�Z�b�g
//	APP_WipeStart( APP_WIPE_IN, HEAPID_POKESTATUS );

	GF_Disp_DispOn();

	Snd_DataSetByScene( SND_SCENE_SUB_PST, 0, 0 );	// �T�E���h�f�[�^���[�h(PST)(BGM���p��)

	WirelessIconEasyUnion();

	return PROC_RES_FINISH;
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
static PROC_RESULT PokeStatusProc_Main( PROC * proc, int * seq )
{
	PST_WORK * wk  = PROC_GetWork( proc );

	switch( *seq ){
	case SEQ_IN_SET:
		APP_WipeStart( APP_WIPE_IN, HEAPID_POKESTATUS );
		*seq = SEQ_IN;
		break;

	case SEQ_IN:			// �����t�F�[�h�҂�
		*seq = PST_SeqIn( wk );
		break;

	case SEQ_MAIN:			// ���C���R���g���[��
		*seq = PST_SeqMain( wk );
		break;

	case SEQ_WAZAIN:		// �Z�����C���҂�
		*seq = PST_SeqWazaIn( wk );
		break;

	case SEQ_WAZAOUT:		// �Z�����A�E�g�҂�
		*seq = PST_SeqWazaOut( wk );
		break;

	case SEQ_CON_WAZAIN:	// �R���e�X�g�Z�����C���҂�
		*seq = PST_SeqContestWazaIn( wk );
		break;

	case SEQ_CON_WAZAOUT:	// �R���e�X�g�Z�����A�E�g�҂�
		*seq = PST_SeqContestWazaOut( wk );
		break;

	case SEQ_WAZA_SELECT:	// �Z�I��
		*seq = PST_SeqWazaSelect( wk );
		break;

	case SEQ_WAZA_CHANGE:	// �Z����ւ��I��
		*seq = PST_SeqWazaChange( wk );
		break;

	case SEQ_WAZA_OBOE:		// �Z�o��/�Y��
		*seq = PST_SeqWazaAdd( wk );
		break;

	case SEQ_WAZA_OBOE_ERROR:	// �Z�o���G���[
		*seq = PST_SeqWazaAddError( wk );
		break;

	case SEQ_RIBBON_IN:			// ���{�������C���҂�
		*seq = PST_SeqRibbonIn( wk );
		break;

	case SEQ_RIBBON_OUT:		// ���{�������A�E�g�҂�
		*seq = PST_SeqRibbonOut( wk );
		break;

	case SEQ_RIBBON_SELECT:		// ���{���I��
		*seq = PST_SeqRibbonSelect( wk );
		break;

	case SEQ_BUTTON_ANM:	// ����ʂ̃{�^���A�j���҂�
		*seq = PST_SeqButtnAnm( wk );
		break;

	case SEQ_COND_INIT:		// �����L�[�҂�
		*seq = PST_SeqCondUpInit( wk );
		break;

	case SEQ_COND_MSG:		// ���b�Z�[�W�\��
		*seq = PST_SeqCondUpMsgPut( wk );
		break;

	case SEQ_COND_END:		// �R���f�B�V�����ύX�I��
		*seq = PST_SeqCondUpEnd( wk );
		break;

	case SEQ_OUT_SET:		// �I���t�F�[�h�Z�b�g
		*seq = PST_SeqOutSet( wk );
		break;

	case SEQ_OUT:			// �I���t�F�[�h�҂�
		if( PST_SeqOut( wk ) == TRUE ){
			return PROC_RES_FINISH;
		}
		break;
	}

	PokeStatus_CellActAnm( wk );
	PokeStatus_KezuyaAnm( wk );
	PokeStatus_RibbonFlashAnm( wk );

	CATS_Draw( wk->crp );

	PokeStatus_3DMain( wk );

	return PROC_RES_CONTINUE;
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
static PROC_RESULT PokeStatusProc_End( PROC * proc, int * seq )
{
	PST_WORK * wk  = PROC_GetWork( proc );

	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g

	PokeStatus_3DRelease( wk );			// 3D�폜
	PokeStatusCellActRerease( wk );		// �Z���A�N�^�[�폜
//	PokeStatusBmpExit( wk );			// BMP�E�B���h�E�J��
	PokeStatus_BmpFreeAll( wk );
	PokeStatusBgExit( wk->bgl );		// BGL�폜
	StopTP();							// �^�b�`�p�l���I��
	DellVramTransferManager();

	MsgBufRelease( wk );

	FontProc_UnloadBitData( FONT_SYSTEM );

/*
	TCB_Delete( wk->vtask );
*/
	G2_BlendNone();

	PROC_FreeWork( proc );				// ���[�N�J��

	sys_DeleteHeap( HEAPID_POKESTATUS );

	return PROC_RES_FINISH;
}


//============================================================================================
//	�ݒ�֘A
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * VBlank�֐�
 *
 * @param	work	���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeStatusVBlank( void * work )
{
	PST_WORK * wk = work;

	GF_BGL_VBlankFunc( wk->bgl );
	SoftSpriteTextureTrans( wk->p3d.ssm );

	// �Z���A�N�^�[
	DoVramTransferManager();	// Vram�]���}�l�[�W���[���s
	CATS_RenderOamTrans();
	
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
static void PokeStatusVramBankSet(void)
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

		GX_VRAM_TEX_0_B,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_01_FG			// �e�N�X�`���p���b�g�X���b�g
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
 *
 * @li	Main BG0 = 3D
 * @li	Main BG1 = font
 * @li	Main BG2 = SubBG
 * @li	Main BG3 = BG
 * @li	Sub BG0 = Button
 * @li	Sub BG1 = BG
 */
//--------------------------------------------------------------------------------------------
static void PokeStatusBgSet( GF_BGL_INI * ini )
{
	{	// BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	// ����
	{	// FONT (BMP)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
	}

	{	// SUB PAGE (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x2000, 0, GF_BGL_SCRSIZ_512x512, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
		GF_BGL_ScrollReq( ini, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, 136 );
	}

	{	// BG (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	// �����
	{	// BUTTON (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );
	}
	{	// BG (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	GF_BGL_ClearCharSet( GF_BGL_FRAME1_M, 32, 0, HEAPID_POKESTATUS );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_POKESTATUS );
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
static void PokeStatusBgExit( GF_BGL_INI * ini )
{
	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();

	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_M );

	sys_FreeMemory( HEAPID_POKESTATUS, ini );
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
static void PokeStatusBgGraphicSet( PST_WORK * wk )
{
	ArcUtil_BgCharSet(
		ARC_PSTATUS_GRA, NARC_pst_gra_p_st_bg_NCGR,
		wk->bgl, GF_BGL_FRAME3_M, 0, 0, 0, HEAPID_POKESTATUS );
	ArcUtil_ScrnSet(
		ARC_PSTATUS_GRA, NARC_pst_gra_p_st_s0_NSCR,
		wk->bgl, GF_BGL_FRAME3_M, 0, 0, 0, HEAPID_POKESTATUS );
	ArcUtil_PalSet(
		ARC_PSTATUS_GRA, NARC_pst_gra_p_st_bg_NCLR,
		PALTYPE_MAIN_BG, 0, 0, HEAPID_POKESTATUS );

	ArcUtil_ScrnSet(
		ARC_PSTATUS_GRA, NARC_pst_gra_p_st_s4b_NSCR,
		wk->bgl, GF_BGL_FRAME2_M, 0, 0, 0, HEAPID_POKESTATUS );

	ArcUtil_BgCharSet(
		ARC_PSTATUS_GRA, NARC_pst_gra_p_st_but_NCGR,
		wk->bgl, GF_BGL_FRAME0_S, 0, 0, 0, HEAPID_POKESTATUS );
	ArcUtil_BgCharSet(
		ARC_PSTATUS_GRA, NARC_pst_gra_p_st_sub_bg_NCGR,
		wk->bgl, GF_BGL_FRAME1_S, 0, 0, 0, HEAPID_POKESTATUS );
	ArcUtil_ScrnSet(
		ARC_PSTATUS_GRA, NARC_pst_gra_p_st_sub_NSCR,
		wk->bgl, GF_BGL_FRAME1_S, 0, 0, 0, HEAPID_POKESTATUS );
	ArcUtil_PalSet(
		ARC_PSTATUS_GRA, NARC_pst_gra_p_st_sub_NCLR,
		PALTYPE_SUB_BG, 0, 0, HEAPID_POKESTATUS );
}

//--------------------------------------------------------------------------------------------
/**
 * �������ݒ�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeStatusAlphaSet(void)
{
	G2_SetBlendAlpha(
		GX_BLEND_PLANEMASK_BG0,
		GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2|
		GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_OBJ, 23, 8 );
}

//--------------------------------------------------------------------------------------------
/**
 * ���b�Z�[�W�֘A�쐬
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void MsgBufCreate( PST_WORK * wk )
{
	// ���b�Z�[�W�}�l�[�W���쐬
	wk->msg_man = MSGMAN_Create(
					MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_pokestatus_dat, HEAPID_POKESTATUS );

	wk->rbn_man = MSGMAN_Create(
					MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_ribbon_dat, HEAPID_POKESTATUS );

	// 8x8�t�H���g�쐬
	wk->num_font = NUMFONT_Create(
					FBMP_COL_BLACK, FBMP_COL_BLK_SDW, FBMP_COL_NULL, HEAPID_POKESTATUS );

	wk->wset = WORDSET_Create( HEAPID_POKESTATUS );

	wk->pp.monsname = STRBUF_Create( BUFLEN_POKEMON_NAME, HEAPID_POKESTATUS );
	wk->pp.nickname = STRBUF_Create( BUFLEN_POKEMON_NAME, HEAPID_POKESTATUS );
	wk->pp.oya = STRBUF_Create( BUFLEN_PERSON_NAME, HEAPID_POKESTATUS );

	wk->msg_buf = STRBUF_Create( TMP_MSGBUF_SIZ, HEAPID_POKESTATUS );

	wk->wman = MSGMAN_Create(
					MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wazaname_dat, HEAPID_POKESTATUS );

	wk->player_name = STRBUF_Create( PERSON_NAME_SIZE+EOM_SIZE, HEAPID_POKESTATUS );
	if( wk->dat->player_name != NULL ){
		STRBUF_SetStringCode( wk->player_name, wk->dat->player_name );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ���b�Z�[�W�֘A�폜
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void MsgBufRelease( PST_WORK * wk )
{
	MSGMAN_Delete( wk->wman );
	MSGMAN_Delete( wk->rbn_man );
	MSGMAN_Delete( wk->msg_man );
	NUMFONT_Delete( wk->num_font );
	WORDSET_Delete( wk->wset );
	STRBUF_Delete( wk->pp.monsname );
	STRBUF_Delete( wk->pp.nickname );
	STRBUF_Delete( wk->pp.oya );
	STRBUF_Delete( wk->msg_buf );
	STRBUF_Delete( wk->player_name );
}


//============================================================================================
//	���C���V�[�P���X
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F�����t�F�[�h�҂�
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static int PST_SeqIn( PST_WORK * wk )
{
	if( WIPE_SYS_EndCheck() == TRUE ){
		PokeStatus_SoftSpriteAnmSet( wk );
		PST_PokeVoicePlay( wk );

		if( wk->dat->mode == PST_MODE_WAZAADD ){
			return SEQ_WAZA_OBOE;
		}else if( wk->dat->mode == PST_MODE_CONDITION ){
			return SEQ_COND_INIT;
		}else{
			return SEQ_MAIN;
		}
	}
	return SEQ_IN;
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F���C���R���g���[��
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static int PST_SeqMain( PST_WORK * wk )
{
	if( wk->sub_end == 1 ){
		wk->dat->ret_mode = PST_RET_CANCEL;
		return SEQ_OUT_SET;
	}

	if( sys.repeat & PAD_KEY_LEFT ){
		PageChange( wk, -1 );
		return SEQ_MAIN;
	}
	if( sys.repeat & PAD_KEY_RIGHT ){
		PageChange( wk, 1 );
		return SEQ_MAIN;
	}

	if( sys.repeat & PAD_KEY_UP ){
		PokeChange( wk, -1 );
		return SEQ_MAIN;
	}
	if( sys.repeat & PAD_KEY_DOWN ){
		PokeChange( wk, 1 );
		return SEQ_MAIN;
	}

	if( sys.trg & PAD_BUTTON_CANCEL ){
		Snd_SePlay( PST_SE_CANCEL );
		wk->dat->ret_mode = PST_RET_CANCEL;
		return SEQ_OUT_SET;
	}

	if( sys.trg & PAD_BUTTON_DECIDE ){
		if( wk->dat->mode == PST_MODE_PORUTO && wk->page == PST_PAGE_CONDITION ){
			Snd_SePlay( PST_SE_DECIDE );
			return PST_PorutoEatCehck( wk );
//			wk->dat->ret_mode = PST_RET_DECIDE;
//			return SEQ_OUT_SET;
		}
		if( wk->page == PST_PAGE_B_SKILL ){
			Snd_SePlay( PST_SE_WAZAINFO );
			wk->sub_seq = 0;
			return SEQ_WAZAIN;
		}else if( wk->page == PST_PAGE_C_SKILL ){
			Snd_SePlay( PST_SE_WAZAINFO );
			wk->sub_seq = 0;
			return SEQ_CON_WAZAIN;
		}else if( wk->page == PST_PAGE_RIBBON ){
			if( wk->ribbon_max != 0 ){
				Snd_SePlay( PST_SE_DECIDE );
				wk->sub_seq = 0;
				return SEQ_RIBBON_IN;
			}
		}else if( wk->page == PST_PAGE_RET ){
			Snd_SePlay( PST_SE_CANCEL );
			wk->dat->ret_mode = PST_RET_CANCEL;
			return SEQ_OUT_SET;
		}
	}

	if( SubButtonPageChg( wk ) == TRUE ){
		wk->sub_seq = SEQ_MAIN;
		return SEQ_BUTTON_ANM;
	}

	return SEQ_MAIN;
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F�Z�����C���҂�
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static int PST_SeqWazaIn( PST_WORK * wk )
{
	if( WazaInfoScrollIn( wk ) == TRUE ){
		return SEQ_WAZA_SELECT;
	}
	return SEQ_WAZAIN;
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F�Z�����A�E�g�҂�
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static int PST_SeqWazaOut( PST_WORK * wk )
{
	if( WazaInfoScrollOut( wk ) == TRUE ){
		return SEQ_MAIN;
	}
	return SEQ_WAZAOUT;
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F�R���e�X�g�Z�����C���҂�
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static int PST_SeqContestWazaIn( PST_WORK * wk )
{
	if( ContestWazaInfoScrollIn( wk ) == TRUE ){
		return SEQ_WAZA_SELECT;
	}
	return SEQ_CON_WAZAIN;
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F�R���e�X�g�Z�����A�E�g�҂�
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static int PST_SeqContestWazaOut( PST_WORK * wk )
{
	if( ContestWazaInfoScrollOut( wk ) == TRUE ){
		return SEQ_MAIN;
	}
	return SEQ_CON_WAZAOUT;
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F�Z�I��
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static int PST_SeqWazaSelect( PST_WORK * wk )
{
	if( sys.trg & PAD_KEY_UP ){
		if( WazaCursorMove( wk, -1 ) == TRUE ){
			Snd_SePlay( PST_SE_CURSOR_MOVE );
			WazaInfoChange( wk );
		}
		return SEQ_WAZA_SELECT;
	}

	if( sys.trg & PAD_KEY_DOWN ){
		if( WazaCursorMove( wk, 1 ) == TRUE ){
			Snd_SePlay( PST_SE_CURSOR_MOVE );
			WazaInfoChange( wk );
		}
		return SEQ_WAZA_SELECT;
	}

	if( sys.trg & PAD_BUTTON_DECIDE ){
		if( wk->cur_pos == 4 ){
//			Snd_SePlay( PST_SE_CANCEL );
			Snd_SePlay( PST_SE_WAZAINFO );
			wk->sub_seq = 0;
			if( wk->page == PST_PAGE_B_SKILL ){
				return SEQ_WAZAOUT;
			}else{
				return SEQ_CON_WAZAOUT;
			}
		}else if( wk->dat->mode != PST_MODE_NO_WAZACHG ){
			Snd_SePlay( PST_SE_DECIDE );
			PokeStatus_SubWazaCursorSet( wk );
			wk->sub_cur = wk->cur_pos;
			return SEQ_WAZA_CHANGE;
		}
	}

	if( sys.trg & PAD_BUTTON_CANCEL ){
//		Snd_SePlay( PST_SE_CANCEL );
		Snd_SePlay( PST_SE_WAZAINFO );
		wk->sub_seq = 0;
		if( wk->page == PST_PAGE_B_SKILL ){
			return SEQ_WAZAOUT;
		}else{
			return SEQ_CON_WAZAOUT;
		}
	}

	return SEQ_WAZA_SELECT;
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F�Z����ւ��I��
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static int PST_SeqWazaChange( PST_WORK * wk )
{
	if( sys.trg & PAD_KEY_UP ){
		if( WazaCursorMove( wk, -1 ) == TRUE ){
			Snd_SePlay( PST_SE_CURSOR_MOVE );
			WazaInfoChange( wk );
		}
		return SEQ_WAZA_CHANGE;
	}

	if( sys.trg & PAD_KEY_DOWN ){
		if( WazaCursorMove( wk, 1 ) == TRUE ){
			Snd_SePlay( PST_SE_CURSOR_MOVE );
			WazaInfoChange( wk );
		}
		return SEQ_WAZA_CHANGE;
	}

	if( sys.trg & PAD_BUTTON_DECIDE ){
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_WAZACURSOR2], 0 );
		if( wk->cur_pos != 4 && wk->cur_pos != wk->sub_cur ){
			Snd_SePlay( PST_SE_DECIDE );
			WazaChangeMain( wk );
			PokeStatus_WazaTypePosChange( wk, wk->cur_pos, wk->sub_cur );
			PokeStatus_SkillChgRewrite( wk );
			WazaInfoChange( wk );
		}else{
			Snd_SePlay( PST_SE_CANCEL );
		}
		return SEQ_WAZA_SELECT;
	}

	if( sys.trg & PAD_BUTTON_CANCEL ){
		Snd_SePlay( PST_SE_CANCEL );
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_WAZACURSOR2], 0 );
		return SEQ_WAZA_SELECT;
	}
	return SEQ_WAZA_CHANGE;
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F�Z�o��/�Y��
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static int PST_SeqWazaAdd( PST_WORK * wk )
{
	if( sys.trg & PAD_KEY_LEFT ){
		PageChange( wk, -1 );
		return SEQ_WAZA_OBOE;
	}
	if( sys.trg & PAD_KEY_RIGHT ){
		PageChange( wk, 1 );
		return SEQ_WAZA_OBOE;
	}

	if( sys.trg & PAD_KEY_UP ){
		if( WazaCursorMove( wk, -1 ) == TRUE ){
			Snd_SePlay( PST_SE_CURSOR_MOVE );
			WazaInfoChange( wk );
		}
		return SEQ_WAZA_OBOE;
	}

	if( sys.trg & PAD_KEY_DOWN ){
		if( WazaCursorMove( wk, 1 ) == TRUE ){
			Snd_SePlay( PST_SE_CURSOR_MOVE );
			WazaInfoChange( wk );
		}
		return SEQ_WAZA_OBOE;
	}

	if( sys.trg & PAD_BUTTON_DECIDE ){
		Snd_SePlay( PST_SE_DECIDE );
		if( wk->cur_pos != 4 ){
			if( HidenWazaCheck( wk->pp.waza[wk->cur_pos] ) == TRUE && wk->dat->waza != 0 ){
				CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_KIND], 0 );
				ContestWazaHeartInit( wk );
				PokeStatus_WazaOboeErrorMsgPut( wk );
				return SEQ_WAZA_OBOE_ERROR;
			}
		}
		wk->dat->ret_sel = wk->cur_pos;
		wk->dat->ret_mode = PST_RET_DECIDE;
		return SEQ_OUT_SET;
	}

	if( sys.trg & PAD_BUTTON_CANCEL ){
		Snd_SePlay( PST_SE_CANCEL );
		wk->dat->ret_sel  = 4;
		wk->dat->ret_mode = PST_RET_CANCEL;
		return SEQ_OUT_SET;
	}

/*
	if( SubButtonPageChg( wk ) == TRUE ){
		wk->sub_seq = SEQ_WAZA_OBOE;
		return SEQ_BUTTON_ANM;
	}
*/

	return SEQ_WAZA_OBOE;
}

static int PST_SeqWazaAddError( PST_WORK * wk )
{
	if( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ){
		WazaInfoChange( wk );
		return SEQ_WAZA_OBOE;
	}
	return SEQ_WAZA_OBOE_ERROR;
}


//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F���{�������C���҂�
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static int PST_SeqRibbonIn( PST_WORK * wk )
{
	if( RibbonInfoScrollIn( wk ) == TRUE ){
		return SEQ_RIBBON_SELECT;
	}
	return SEQ_RIBBON_IN;
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F���{�������A�E�g�҂�
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static int PST_SeqRibbonOut( PST_WORK * wk )
{
	if( RibbonInfoScrollOut( wk ) == TRUE ){
		return SEQ_MAIN;
	}
	return SEQ_RIBBON_OUT;
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F���{���I��
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static int PST_SeqRibbonSelect( PST_WORK * wk )
{
	if( sys.repeat & PAD_KEY_LEFT ){
		RibbonSelect( wk, -1 );
		return SEQ_RIBBON_SELECT;
	}
	if( sys.repeat & PAD_KEY_RIGHT ){
		RibbonSelect( wk, 1 );
		return SEQ_RIBBON_SELECT;
	}

	if( sys.repeat & PAD_KEY_UP ){
		RibbonSelect( wk, -4 );
		return SEQ_RIBBON_SELECT;
	}
	if( sys.repeat & PAD_KEY_DOWN ){
		RibbonSelect( wk, 4 );
		return SEQ_RIBBON_SELECT;
	}

	if( sys.trg & (PAD_BUTTON_CANCEL|PAD_BUTTON_DECIDE) ){
		Snd_SePlay( PST_SE_DECIDE );
		wk->sub_seq = 0;
		return SEQ_RIBBON_OUT;
	}
	return SEQ_RIBBON_SELECT;
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F����ʂ̃{�^���A�j���҂�
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static int PST_SeqButtnAnm( PST_WORK * wk )
{
	if( PokeStatus_SubButtonAnm( wk ) == TRUE ){
		return wk->sub_seq;
	}

	if( wk->btn_seq == 1 ){
		u8	page = PokeStatus_ButtonPosPageGet( wk, wk->btn_pos );
		if( page == PST_PAGE_RET ){
			wk->sub_end = 1;
		}
		if( wk->pp.tamago == 1 ){
			if( page == PST_PAGE_MEMO || page == PST_PAGE_RET ){
				PageChangeWrite( wk, page );
			}
		}else{
			PageChangeWrite( wk, page );
		}
	}

	return SEQ_BUTTON_ANM;
}




static int PST_SeqCondUpInit( PST_WORK * wk )
{
	if( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ){
		POKEMON_PASO_PARAM * ppp;
		POKEMON_PARAM * pp;
		u8	tmp;

		if( wk->dat->ppt == PST_PP_TYPE_POKEPASO ){
			ppp = PokeStatusPokeParamGet( wk );
			pp  = PokemonParam_AllocWork( HEAPID_POKESTATUS );
			PokeReplace( ppp, pp );
		}else{
			pp = PokeStatusPokeParamGet( wk );
		}

		PoruSys_PoruPara2Poke( wk->dat->poruto, pp );

		wk->sub_seq = 0;

		// �������悳
		tmp = wk->pp.style;
		wk->pp.style = (u8)PokeParaGet( pp, ID_PARA_style, NULL );
		if( tmp != wk->pp.style ){
			wk->sub_seq |= 1;
		}
//		OS_Printf( "style : %d -> %d\n", tmp, wk->pp.style );

		// ��������
		tmp = wk->pp.beautiful;
		wk->pp.beautiful = (u8)PokeParaGet( pp, ID_PARA_beautiful, NULL );
		if( tmp != wk->pp.beautiful ){
			wk->sub_seq |= 2;
		}
//		OS_Printf( "beautiful : %d -> %d\n", tmp, wk->pp.beautiful );

		// ���킢��
		tmp = wk->pp.cute;
		wk->pp.cute = (u8)PokeParaGet( pp, ID_PARA_cute, NULL );
		if( tmp != wk->pp.cute ){
			wk->sub_seq |= 4;
		}
//		OS_Printf( "cute : %d -> %d\n", tmp, wk->pp.cute );

		// ��������
		tmp = wk->pp.clever;
		wk->pp.clever = (u8)PokeParaGet( pp, ID_PARA_clever, NULL );
		if( tmp != wk->pp.clever ){
			wk->sub_seq |= 8;
		}
//		OS_Printf( "clever : %d -> %d\n", tmp, wk->pp.clever );

		// �����܂���
		tmp = wk->pp.strong;
		wk->pp.strong = (u8)PokeParaGet( pp, ID_PARA_strong, NULL );
		if( tmp != wk->pp.strong ){
			wk->sub_seq |= 16;
		}
//		OS_Printf( "strong : %d -> %d\n", tmp, wk->pp.strong );
		
		wk->pp.fur = (u8)PokeParaGet( pp, ID_PARA_fur, NULL );	// �щ�

		if( wk->dat->ppt == PST_PP_TYPE_POKEPASO ){
			sys_FreeMemoryEz( pp );
		}

		// ��b�E�B���h�E�Z�b�g
		TalkFontPaletteLoad( PALTYPE_MAIN_BG, PST_PAL_TALKFONT * 32, HEAPID_POKESTATUS );
		TalkWinGraphicSet(
			wk->bgl, GF_BGL_FRAME1_M, PST_CGX_TALKWIN,
			PST_PAL_TALKWIN, CONFIG_GetWindowType(wk->dat->cfg), HEAPID_POKESTATUS );

		if( wk->sub_seq == 0 ){
			PokeStatus_CondUpMsgPut( wk, PST_MSG_PRMNONE );
			return SEQ_COND_END;
		}else{
			PokeStatus_ConditionParamMake( wk );
			PokeStatus_KezuyaInit( wk );
			PokeStatus_CondUpObjPut( wk );
			return SEQ_COND_MSG;
		}
	}
	return SEQ_COND_INIT;
}

static int PST_SeqCondUpMsgPut( PST_WORK * wk )
{
	u8	i;

	if( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ){
		for( i=0; i<5; i++ ){
			if( ( wk->sub_seq & (1<<i) ) ){
				PokeStatus_CondUpMsgPut( wk, i );
				wk->sub_seq ^= (1<<i);
				if( wk->sub_seq == 0 ){
					return SEQ_COND_END;
				}
				break;
			}
		}
	}
	return SEQ_COND_MSG;
}

static int PST_SeqCondUpEnd( PST_WORK * wk )
{
	if( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ){
//		Snd_SePlay( PST_SE_CANCEL );
		return SEQ_OUT_SET;
	}
	return SEQ_COND_END;
}


//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F�I���t�F�[�h�Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 PST_SeqOutSet( PST_WORK * wk )
{
	APP_WipeStart( APP_WIPE_OUT, HEAPID_POKESTATUS );
	return SEQ_OUT;
}


//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F�I���t�F�[�h�҂�
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 PST_SeqOut( PST_WORK * wk )
{
	if( WIPE_SYS_EndCheck() == TRUE ){
		return TRUE;
	}
	return FALSE;
}


//============================================================================================
//	�c�[��
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����f�[�^�擾
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeDataSet( PST_WORK * wk )
{
	void * pp = PokeStatusPokeParamGet( wk );

	if( wk->dat->ppt == PST_PP_TYPE_POKEPASO ){
		PokeDataSet_PokePasoParam( wk, pp, &wk->pp );
	}else{
		PokeDataSet_PokemonParam( wk, pp, &wk->pp );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����f�[�^�擾 ( POKEMON_PASO_PARAM�� )
 *
 * @param	ppp		POKEMON_PASO_PARAM
 * @param	dat		�f�[�^�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeDataSet_PokePasoParam(
				PST_WORK * wk, POKEMON_PASO_PARAM * ppp, PST_POKEDATA * dat )
{
	POKEMON_PARAM * pp = PokemonParam_AllocWork( HEAPID_POKESTATUS );

	PokeReplace( ppp, pp );
	PokeDataSet_PokemonParam( wk, pp, dat );
	sys_FreeMemoryEz( pp );
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����f�[�^�擾 ( POKEMON_PARAM�� )
 *
 * @param	pp		POKEMON_PARAM
 * @param	dat		�f�[�^�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeDataSet_PokemonParam(
				PST_WORK * wk, POKEMON_PARAM * pp, PST_POKEDATA * dat )
{
	POKEMON_PASO_PARAM * ppp;
	u16	i;
	u8	pp_count;
	BOOL	fast_flg;

	fast_flg = PokeParaFastModeOn( pp );

	dat->mons = (u16)PokeParaGet( pp, ID_PARA_monsno, NULL );

	ppp = PPPPointerGet(pp);

	MSGMAN_GetString( wk->msg_man, mes_status_02_05, wk->msg_buf );
	WORDSET_RegisterPokeMonsName( wk->wset, 0, ppp );
	WORDSET_ExpandStr( wk->wset, wk->pp.monsname, wk->msg_buf );

	MSGMAN_GetString( wk->msg_man, mes_status_01_01, wk->msg_buf );
	WORDSET_RegisterPokeNickName( wk->wset, 0, ppp );
	WORDSET_ExpandStr( wk->wset, wk->pp.nickname, wk->msg_buf );

	MSGMAN_GetString( wk->msg_man, mes_status_02_08, wk->msg_buf );
	WORDSET_RegisterPokeOyaName( wk->wset, 0, ppp );
	WORDSET_ExpandStr( wk->wset, wk->pp.oya, wk->msg_buf );

	dat->item = (u16)PokeParaGet( pp, ID_PARA_item, NULL );
	dat->lv   = (u8)PokeParaGet( pp, ID_PARA_level, NULL );

	dat->tamago = PokeParaGet( pp, ID_PARA_tamago_flag, NULL );

	if( PokeParaGet( pp, ID_PARA_nidoran_nickname, NULL ) == TRUE && dat->tamago == 0 ){
		dat->sex_put = 0;
	}else{
		dat->sex_put = 1;
	}

	dat->sex = PokeSexGet( pp );
	dat->ball = (u8)PokeParaGet( pp, ID_PARA_get_ball, NULL );

	dat->type1 = (u8)PokeParaGet( pp, ID_PARA_type1, NULL );
	dat->type2 = (u8)PokeParaGet( pp, ID_PARA_type2, NULL );

	dat->id = PokeParaGet( pp, ID_PARA_id_no, NULL );
	dat->now_exp  = PokeParaGet( pp, ID_PARA_exp, NULL );
//	dat->next_exp = PokeParaNextLevelExpGet( pp );

	dat->oya_sex = (u8)PokeParaGet( pp, ID_PARA_oyasex, NULL );

	dat->now_lv_exp  = PokeLevelExpGet( dat->mons, dat->lv );
	if( dat->lv == 100 ){
		dat->next_lv_exp = dat->now_lv_exp;
	}else{
		dat->next_lv_exp = PokeLevelExpGet( dat->mons, dat->lv+1 );
	}

	dat->hp  = (u16)PokeParaGet( pp, ID_PARA_hp, NULL );
	dat->mhp = (u16)PokeParaGet( pp, ID_PARA_hpmax, NULL );
	dat->atc = (u16)PokeParaGet( pp, ID_PARA_pow, NULL );
	dat->def = (u16)PokeParaGet( pp, ID_PARA_def, NULL );
	dat->spa = (u16)PokeParaGet( pp, ID_PARA_spepow, NULL );
	dat->spd = (u16)PokeParaGet( pp, ID_PARA_spedef, NULL );
	dat->agi = (u16)PokeParaGet( pp, ID_PARA_agi, NULL );

	dat->tokusei = (u8)PokeParaGet( pp, ID_PARA_speabino, NULL );
	dat->seikaku = PokeSeikakuGet( pp );

	for( i=0; i<4; i++ ){
		dat->waza[i] = (u16)PokeParaGet( pp, ID_PARA_waza1+i, NULL );
		dat->wpp[i]  = (u8)PokeParaGet( pp, ID_PARA_pp1+i, NULL );
		pp_count = (u8)PokeParaGet( pp, ID_PARA_pp_count1+i, NULL );
		dat->mpp[i]  = WT_PPMaxGet( dat->waza[i], pp_count );
	}
/*
	dat->style     = 255;
	dat->beautiful = 255;
	dat->cute      = 255;
	dat->clever    = 255;
	dat->strong    = 255;
*/
	dat->style     = (u8)PokeParaGet( pp, ID_PARA_style, NULL );		// �������悳
	dat->beautiful = (u8)PokeParaGet( pp, ID_PARA_beautiful, NULL );	// ��������
	dat->cute      = (u8)PokeParaGet( pp, ID_PARA_cute, NULL );			// ���킢��
	dat->clever    = (u8)PokeParaGet( pp, ID_PARA_clever, NULL );		// ��������
	dat->strong    = (u8)PokeParaGet( pp, ID_PARA_strong, NULL );		// �����܂���
	dat->fur       = (u8)PokeParaGet( pp, ID_PARA_fur, NULL );			// �щ�

	dat->like = PST_LIKE_TASTE_NONE;
	for( i=0; i<5; i++ ){
		if( PokeParaLikeTasteCheck(pp,i) == 1 ){
			dat->like = i;
			break;
		}
	}

	dat->mark = PokeParaGet( pp, ID_PARA_mark, NULL );

	dat->form = PokeParaGet( pp, ID_PARA_form_no, NULL );

	dat->st = BadStatusIconAnmGet( pp );

	if( PokeParaPokerusedCheck( pp) == TRUE ){
		dat->pokerus = 2;
	}else if( PokeParaPokerusCheck( pp ) == TRUE ){
		dat->pokerus = 1;
		if( dat->st == ST_ICON_NONE ){
			dat->st = ST_ICON_POKERUS;
		}
	}else{
		dat->pokerus = 0;
	}

	if( PokeRareGet( pp ) == TRUE ){
		dat->rare = 1;
	}else{
		dat->rare = 0;
	}

	dat->ribbon[0] = 0;
	dat->ribbon[1] = 0;
	dat->ribbon[2] = 0;
	dat->ribbon[3] = 0;
	wk->ribbon_max = 0;
	for( i=0; i<RIBBON_MAX; i++ ){
		if( PokeParaGet( pp, RIBBON_DataGet(i,RIBBON_PARA_POKEPARA), NULL ) != 0 ){
			dat->ribbon[i/32] |= (1<<(i&0x1f));
			wk->ribbon_max++;
		}
	}

/**** �e�X�g!!! ****/
/*
	dat->ribbon[0] = 0xffffffff;
	dat->ribbon[1] = 0xffffffff;
	dat->ribbon[2] = 0xffff;
	wk->ribbon_max = 80;
*/
/*******************/

	PokeParaFastModeOff( pp, fast_flg );
}

static void PST_PokeVoicePlay( PST_WORK * wk )
{
	if( wk->pp.tamago != 0 ){ return; }

	if( wk->pp.mons == MONSNO_PERAPPU ){
		//�y���b�v�̃|�C���^���K�v�ɂȂ�܂�
		Snd_PerapVoicePlay( wk->dat->perap, PM_MALE, PV_VOL_DEFAULT, 0 );
//		Snd_PerapVoicePlay( NULL, PM_MALE, PV_VOL_DEFAULT, 0 );
	}else{
		Snd_PMVoicePlay( wk->pp.mons );
	}
}


//--------------------------------------------------------------------------------------------
/**
 * �����y�[�W�Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void InitPageSet( PST_WORK * wk )
{
	switch( wk->dat->mode ){
	case PST_MODE_NORMAL:		// �ʏ�
	case PST_MODE_NO_WAZACHG:	// �Z����ւ��s��
		if( wk->pp.tamago == 0 ){
			wk->page = PST_PAGE_INFO;
		}else{
			wk->page = PST_PAGE_MEMO;
		}
		break;
	case PST_MODE_WAZAADD:		// �Z�o��/�Z�Y��
		wk->page = PST_PAGE_B_SKILL;
		break;
	case PST_MODE_PORUTO:		// �|���g�g�p
	case PST_MODE_CONDITION:	// �R���f�B�V�����ύX�f��
		wk->page = PST_PAGE_CONDITION;
		break;
	}

	PokeStatus_A_ButtonMarkPut( wk, NULL );

	PokeStatusTabPosChg( wk );			// �^�uOBJ�؂�ւ�
	PokeStatus_PageTypeIconDrow( wk );	// �����A�C�R���Z�b�g
	PokeStatus_RibbonInit( wk );		// ���{��
	PokeStatus_TabArrowPut( wk );		// �^�u���ʒu�ύX
	PokeStatus_MarkChg( wk );

	PokeStatus_KezuyaInit( wk );

	PokeStatus_PageBmpAdd( wk );
	PokeStatus_PageBmpPut( wk );

	PageBgScreenChg( wk );				// BG�؂�ւ�
	PokeStatus_ConditionParamInit( wk );

	if( wk->dat->mode == PST_MODE_WAZAADD ){
		WazaInfoPut( wk );
	}
}



//--------------------------------------------------------------------------------------------
/**
 * �y�[�W�쐬
 *
 * @param	dat		�X�e�[�^�X��ʃf�[�^
 * @param	tbl		�y�[�W�e�[�u��
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_PageSet( PSTATUS_DATA * dat, const u8 * tbl )
{
	u8	i;

	dat->page_flg = 0;
	for( i=0; i<PST_PAGE_MAX; i++ ){
		if( tbl[i] == PST_PAGE_MAX ){ break; }
		dat->page_flg |= (1<<tbl[i]);
	}
}

static void PST_ContestPageCheck( PST_WORK * wk )
{
	if( wk->dat->ev_contest == 1 ){ return; }

	if( wk->dat->page_flg & (1<<PST_PAGE_CONDITION) ){
		wk->dat->page_flg ^= (1<<PST_PAGE_CONDITION);
	}
	if( wk->dat->page_flg & (1<<PST_PAGE_C_SKILL) ){
		wk->dat->page_flg ^= (1<<PST_PAGE_C_SKILL);
	}
	if( wk->dat->page_flg & (1<<PST_PAGE_RIBBON) ){
		wk->dat->page_flg ^= (1<<PST_PAGE_RIBBON);
	}
}

u8 PokeStatus_PageCheck( PST_WORK * wk, u32 pos )
{
	if( wk->pp.tamago != 0 && pos != PST_PAGE_MEMO && pos != PST_PAGE_RET ){
		return 0;
	}
	return ( wk->dat->page_flg & (1<<pos) );
}

u8 PokeStatus_PageNumGet( PST_WORK * wk )
{
	u8	i, cnt;

	cnt = 0;
	for( i=0; i<PST_PAGE_MAX; i++ ){
		if( wk->dat->page_flg & (1<<i) ){
			cnt++;
		}
	}
	return cnt;

}


static void PageChangeWrite( PST_WORK * wk, u8 next )
{
	if( wk->page == next ){return; }

	if( wk->dat->mode == PST_MODE_WAZAADD ){
		PST_WazaSetInfoOff( wk );
	}

	PokeStatus_PageBmpFree( wk );
	wk->page = next;

	PokeStatus_A_ButtonMarkPut( wk, NULL );

	PokeStatusTabPosChg( wk );
	PokeStatus_TabArrowPut( wk );		// �^�u���ʒu�ύX
	PokeStatus_PageTypeIconDrow( wk );
	PokeStatus_RibbonInit( wk );		// ���{��
	PokeStatus_KezuyaInit( wk );
	PokeStatus_PageBmpAdd( wk );
	PokeStatus_ConditionFlash( wk, 0 );

	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME1_M, 0,
		PAGE_PRM_AREA_PX, PAGE_PRM_AREA_PY, PAGE_PRM_AREA_SX, PAGE_PRM_AREA_SY, 0 );
	GF_BGL_LoadScreenReq( wk->bgl, GF_BGL_FRAME1_M );	// ���]��

	PokeStatus_PageBmpPut( wk );

	PageBgScreenChg( wk );
	PokeStatus_ConditionParamInit( wk );

	if( wk->dat->mode == PST_MODE_WAZAADD ){
		PST_WazaSetInfoChange( wk );
	}
}

static void PageChange( PST_WORK * wk, s8 mv )
{
	s8	next = wk->page;

	while(1){
		next += mv;
		if( next < PST_PAGE_INFO ){
			next = PST_PAGE_RET;
		}else if( next > PST_PAGE_RET ){
			next = PST_PAGE_INFO;
		}
		if( wk->pp.tamago == 0 ){
			if( ( wk->dat->page_flg & (1<<next) ) != 0 ){
				break;
			}
		}else{
			if( ( wk->dat->page_flg & (1<<next) ) != 0 &&
				( next == PST_PAGE_MEMO || next == PST_PAGE_RET ) ){
				break;
			}
		}
	}

	if( next == wk->page ){ return; }

	Snd_SePlay( PST_SE_PAGE_MOVE );
	PokeStatus_SubButtonBgInit( wk );
	PokeStatus_ConditionFlash( wk, 0 );
	PageChangeWrite( wk, next );
}

static u8 SubButtonPageChg( PST_WORK * wk )
{
	u8	ret = PokeStatus_SubBottonPageGet( wk );

	if( ret == 0xff ){
		return FALSE;
	}

/*
	PokeStatus_PageBmpFree( wk );
	wk->page = ret;

	PokeStatusTabPosChg( wk );
	PokeStatus_PageTypeIconDrow( wk );
	PokeStatus_RibbonInit( wk );		// ���{��
	PokeStatus_KezuyaInit( wk );
	PokeStatus_PageBmpAdd( wk );
	PokeStatus_PageBmpPut( wk );

	PageBgScreenChg( wk );
	PokeStatus_ConditionParamInit( wk );
*/

	wk->btn_cnt = 0;
	wk->btn_pos = ret;
	wk->btn_seq = 0;

	return TRUE;
}


static void PageBgScreenChg( PST_WORK * wk )
{
	{
		NNSG2dScreenData * dat;
		void * buf;
		u32	idx;

		if( wk->dat->mode == PST_MODE_WAZAADD && wk->dat->waza != 0 ){
			if( wk->page == PST_PAGE_B_SKILL ){
				idx = NARC_pst_gra_p_st_s4_w_NSCR;
			}else{
				idx = NARC_pst_gra_p_st_s5_w_NSCR;
			}
		}else{
			idx = NARC_pst_gra_p_st_s0_NSCR + wk->page;
		}

		buf = ArchiveDataLoadMalloc( ARC_PSTATUS_GRA, idx, HEAPID_POKESTATUS );
		NNS_G2dGetUnpackedScreenData( buf, &dat );
		GF_BGL_ScrWrite( wk->bgl, GF_BGL_FRAME3_M, dat->rawData, 0, 0, 32, 32 );
		GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME3_M );
		sys_FreeMemoryEz( buf );
	}

	if( wk->page == PST_PAGE_INFO ){
		ExpGaugeSet( wk );
	}else if( wk->page == PST_PAGE_PARAM ){
		HPGaugeSet( wk );
	}
}


static void HPGaugeSet( PST_WORK * wk )
{
	u16	chr;
	u16	cgx;
	u8	dot;
	u8	i;

	switch( GetHPGaugeDottoColor( wk->pp.hp, wk->pp.mhp, HP_DOT_MAX ) ){
	case HP_DOTTO_MAX:		// ��
	case HP_DOTTO_GREEN:
	case HP_DOTTO_NULL:
		chr = HP_CHR_GREEN | HP_CHR_PALETTE;
		break;
	case HP_DOTTO_YELLOW:	// ��
		chr = HP_CHR_YELLOW | HP_CHR_PALETTE;
		break;
	case HP_DOTTO_RED:		// ��
		chr = HP_CHR_RED | HP_CHR_PALETTE;
		break;
	}

	dot = GetNumDotto( wk->pp.hp, wk->pp.mhp, HP_DOT_MAX );

	for( i=0; i<HP_DOT_CHR_MAX; i++ ){
		if( dot >= 8 ){
			cgx = chr + 8;
		}else{
			cgx = chr + dot;
		}

		GF_BGL_ScrFill(
			wk->bgl, GF_BGL_FRAME3_M, cgx,
			HP_GAUGE_SCR_PX+i, HP_GAUGE_SCR_PY, 1, 1, GF_BGL_SCRWRT_PALIN );

		if( dot < 8 ){
			dot = 0;
		}else{
			dot -= 8;
		}
	}

	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME3_M );
}



static void ExpGaugeSet( PST_WORK * wk )
{
	u32	max;
	u32	now;
	u16	cgx;
	u8	dot;
	u8	i;

/* ���r�T�t�@�̈�ĉ���Lv100�ȏ�̌o���l�ɂȂ邽�߁A�}�C�i�X�\���ɂȂ��Ă��܂��s��Ώ� */
#if T1653_060815_FIX	// �Ώ���
	if( wk->pp.lv < 100 ){
		max = wk->pp.next_lv_exp - wk->pp.now_lv_exp;
		now = wk->pp.now_exp - wk->pp.now_lv_exp;
	}else{
		max = 0;
		now = 0;
	}
#else					// �Ώ��O
	max = wk->pp.next_lv_exp - wk->pp.now_lv_exp;
	now = wk->pp.now_exp - wk->pp.now_lv_exp;
#endif	// T1653_060815_FIX

	dot = GetNumDotto( now, max, EXP_DOT_MAX );

	for( i=0; i<EXP_DOT_CHR_MAX; i++ ){
		if( dot >= 8 ){
			cgx = EXP_CGX + 8;
		}else{
			cgx = EXP_CGX + dot;
		}

		GF_BGL_ScrFill(
			wk->bgl, GF_BGL_FRAME3_M, cgx,
			EXP_GAUGE_SCR_PX+i, EXP_GAUGE_SCR_PY, 1, 1, GF_BGL_SCRWRT_PALIN );

		if( dot < 8 ){
			dot = 0;
		}else{
			dot -= 8;
		}
	}

	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME3_M );
}



static void PokeChange( PST_WORK * wk, s8 mv )
{
	s8	pos = PokeSearch( wk, mv );

	if( pos == -1 ){
		return;
	}

	wk->dat->pos = (u8)pos;

	PokeDataSet( wk );

	PST_PokeVoicePlay( wk );

	PokeStatus_NickNamePut( wk );
	PokeStatus_LvPut( wk );
	PokeStatus_ItemPut( wk );

	if( wk->page == PST_PAGE_INFO ){
		ExpGaugeSet( wk );
	}else if( wk->page == PST_PAGE_PARAM ){
		HPGaugeSet( wk );
	}else if( wk->page == PST_PAGE_CONDITION ){
		PokeStatus_ConditionParamMake( wk );
	}

	PokeStatus_SoftSpriteReset( wk );

	PokeStatus_A_ButtonMarkPut( wk, NULL );

	PokeStatusTabPosChg( wk );
	PokeStatus_TabArrowPut( wk );		// �^�u���ʒu�ύX

	PokeStatus_PokeTypeChange( wk );
	PokeStatus_PageTypeIconDrow( wk );
	PokeStatus_RibbonInit( wk );		// ���{��
	PokeStasus_PokeIconChange( wk );
	PokeStatusBallAnmChg( wk );
	PokeStatus_StIconChg( wk );
	PokeStatus_KezuyaInit( wk );
	PokeStatus_MarkChg( wk );

	PokeStatus_PageBmpPut( wk );
}

static s8 PokeSearch( PST_WORK * wk, s8 mv )
{
	switch( wk->dat->ppt ){
	case PST_PP_TYPE_POKEPARAM:	// POKEMON_PARAM
		return PokeSearch_PokemonParam( wk, mv );
	case PST_PP_TYPE_POKEPARTY:	// POKEPARTY
		return PokeSearch_PokeParty( wk, mv );
	case PST_PP_TYPE_POKEPASO:	// POKEMON_PASO_PARAM
		return PokeSearch_PokemonPasoParam( wk, mv );
	}
	return -1;
}

static BOOL PokeSearch_TamagoCheck( PST_WORK * wk )
{
	if( wk->dat->mode == PST_MODE_PORUTO ){
		return FALSE;
	}
	if( wk->page != PST_PAGE_MEMO && wk->page != PST_PAGE_RET ){
		return FALSE;
	}
	return TRUE;
}

static s8 PokeSearch_PokemonParam( PST_WORK * wk, s8 mv )
{
	POKEMON_PARAM * pp;
	s8	pos;

	pos = (s8)wk->dat->pos;
	pp  = (POKEMON_PARAM *)wk->dat->ppd;

	while(1){
		pos += mv;
		if( pos < 0 || pos >= wk->dat->max ){
			return -1;
		}
		pp = (POKEMON_PARAM *)( (u32)wk->dat->ppd + PokemonParamSizeGet()*pos );
		if( PokeParaGet( pp, ID_PARA_monsno, NULL ) != 0 ){
			if( PokeParaGet( pp, ID_PARA_tamago_flag, NULL ) != 0 ){
/*
				if( wk->page == PST_PAGE_MEMO || wk->page == PST_PAGE_RET ){
					break;
				}
*/
				if( PokeSearch_TamagoCheck( wk ) == TRUE ){
					break;
				}
			}else{
				break;
			}
		}
	}

	return pos;
}

static s8 PokeSearch_PokeParty( PST_WORK * wk, s8 mv )
{
	POKEMON_PARAM * pp;
	s8	pos;

	pos = (s8)wk->dat->pos;

	while(1){
		pos += mv;
		if( pos < 0 || pos >= wk->dat->max ){
			return -1;
		}
		pp = PokeParty_GetMemberPointer( wk->dat->ppd, pos );
		if( PokeParaGet( pp, ID_PARA_monsno, NULL ) != 0 ){
			if( PokeParaGet( pp, ID_PARA_tamago_flag, NULL ) != 0 ){
/*
				if( wk->page == PST_PAGE_MEMO || wk->page == PST_PAGE_RET ){
					break;
				}
*/
				if( PokeSearch_TamagoCheck( wk ) == TRUE ){
					break;
				}
			}else{
				break;
			}
		}
	}

	return pos;
}

static s8 PokeSearch_PokemonPasoParam( PST_WORK * wk, s8 mv )
{
	POKEMON_PASO_PARAM * ppp;
	s8	pos;

	pos = (s8)wk->dat->pos;
	ppp = (POKEMON_PASO_PARAM *)wk->dat->ppd;

	while(1){
		pos += mv;
		if( pos < 0 || pos >= wk->dat->max ){
			return -1;
		}
		ppp = (POKEMON_PASO_PARAM *)( (u32)wk->dat->ppd + PokemonPasoParamSizeGet()*pos );
		if( PokePasoParaGet( ppp, ID_PARA_monsno, NULL ) != 0 ){
			if( PokePasoParaGet( ppp, ID_PARA_tamago_flag, NULL ) != 0 ){
/*
				if( wk->page == PST_PAGE_MEMO || wk->page == PST_PAGE_RET ){
					break;
				}
*/
				if( PokeSearch_TamagoCheck( wk ) == TRUE ){
					break;
				}
			}else{
				break;
			}
		}
	}

	return pos;
}

void * PokeStatusPokeParamGet( PST_WORK * wk )
{
	switch( wk->dat->ppt ){
	case PST_PP_TYPE_POKEPARAM:	// POKEMON_PARAM
		return (void *)( (u32)wk->dat->ppd + ( PokemonParamSizeGet()*wk->dat->pos ) );

	case PST_PP_TYPE_POKEPARTY:	// POKEPARTY
		return (void *)PokeParty_GetMemberPointer( wk->dat->ppd, wk->dat->pos );

	case PST_PP_TYPE_POKEPASO:	// POKEMON_PASO_PARAM
		return (void *)((u32)wk->dat->ppd+(PokemonPasoParamSizeGet()*wk->dat->pos));
	}
	return NULL;
}



//--------------------------------------------------------------------------------------------
//	�Z���i�퓬�j
//--------------------------------------------------------------------------------------------
static u8 WazaInfoScrollIn( PST_WORK * wk )
{
	switch( wk->sub_seq ){
	case 0:
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, 136 );
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, 0 );

		PokeStatus_TabArrowVanish( wk, 0 );
		GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_LV] );
		GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_MOTIMONO] );
		GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_ITEMNAME] );
		GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_GUIDE] );
		PokeStatus_A_ButtonMarkPut( wk, NULL );
		wk->cur_pos = 0;
		wk->sub_seq = 1;
		break;
	case 1:
		{
			int	cnt = GF_BGL_ScrollGetX( wk->bgl, GF_BGL_FRAME2_M );

			if( cnt <= 64 ){
				GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, 0 );
				wk->sub_seq = 2;
			}else{
				GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_DEC, 64 );
			}
		}
		break;
	case 2:
		PokeStatus_SkillCancelPut( wk );
		if( wk->dat->mode != PST_MODE_NO_WAZACHG ){
			PokeStatus_GuideStrPut( wk, mes_status_06_25 );
			PokeStatus_A_ButtonMarkPut( wk, &wk->def_win[WIN_GUIDE] );
		}
		WazaInfoChange( wk );
		CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_POKE1], 1 );
		PokeStatus_PokeIconSet( wk );
		if( wk->pp.type1 != wk->pp.type2 ){
			CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_POKE2], 1 );
		}
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_WAZACURSOR1], 1 );
		return TRUE;
	}
	return FALSE;
}

static u8 WazaInfoScrollOut( PST_WORK * wk )
{
	switch( wk->sub_seq ){
	case 0:
		CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_POKE1], 0 );
		CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_POKE2], 0 );
		CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_KIND], 0 );
		CATS_ObjectEnable( wk->awp[PST_OBJ_POKEICON], 0 );
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_WAZACURSOR1], 0 );
		GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_GUIDE] );
		PokeStatus_A_ButtonMarkPut( wk, NULL );
		PokeStatus_SkillCancelDel( wk );
		PokeStatus_WazaInfoOff( wk );
		wk->sub_seq = 1;
		break;
	case 1:
		{
			int	cnt = GF_BGL_ScrollGetX( wk->bgl, GF_BGL_FRAME2_M );

			if( cnt >= 128 ){
				GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, 136 );
				wk->sub_seq = 2;
			}else{
				GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_INC, 64 );
			}
		}
		break;
	case 2:
		GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_LV] );
		GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_MOTIMONO] );
		GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_ITEMNAME] );
		PokeStatus_GuideStrPut( wk, mes_status_06_02 );
		PokeStatus_TabArrowVanish( wk, 1 );
		PokeStatus_A_ButtonMarkPut( wk, &wk->def_win[WIN_GUIDE] );
		return TRUE;
	}
	return FALSE;
}


static u8 WazaCursorMove( PST_WORK * wk, s8 mv )
{
	s8	pos = wk->cur_pos;

	while(1){
		pos += mv;
		if( pos < 0 ){
			pos = 4;
		}else if( pos == 5 ){
			pos = 0;
		}
		if( wk->pp.waza[pos] != 0 || pos == 4 ){
			break;
		}
	}
	if( pos != wk->cur_pos ){
		wk->cur_pos = pos;
		return TRUE;
	}
	return FALSE;	// ���Ԃ�A�����ɂ͂��Ȃ�
}

static void WazaInfoChange( PST_WORK * wk )
{
	PokeStatus_WazaCursorMove( wk );

	if( wk->cur_pos == 4 ){
		if( wk->dat->waza != 0 ){
			if( wk->page == PST_PAGE_B_SKILL ){
				BattleWazaInfoChg( wk, wk->dat->waza );
			}else{
				ContestWazaInfoChg( wk, wk->dat->waza );
			}
		}else{
			if( wk->page == PST_PAGE_B_SKILL ){
				BattleWazaInfoChg( wk, 0xffffffff );
			}else{
				ContestWazaInfoChg( wk, 0xffffffff );
			}
		}
	}else{
		if( wk->page == PST_PAGE_B_SKILL ){
			BattleWazaInfoChg( wk, wk->pp.waza[wk->cur_pos] );
		}else{
			ContestWazaInfoChg( wk, wk->pp.waza[wk->cur_pos] );
		}
	}
}

static void BattleWazaInfoChg( PST_WORK * wk, u32 waza )
{
	if( waza == 0xffffffff ){
		PokeStatus_WazaInfoOff( wk );
		CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_KIND], 0 );
	}else{
		PokeStatus_WazaInfoPut( wk, waza );
		PokeStatus_KindIconChange( wk, waza );
		CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_KIND], 1 );
	}
}

static void ContestWazaInfoChg( PST_WORK * wk, u32 waza )
{
	ContestWazaHeartPut( wk, waza );

	if( waza == 0xffffffff ){
		PokeStatus_ContestWazaInfoOff( wk );
	}else{
		PokeStatus_ContestWazaInfoPut( wk, waza );
	}
}



static void WazaChangeMain( PST_WORK * wk )
{
	void * pp;
	u16	tmp_waza;
	u8	tmp_wpp;
	u8	tmp_mpp;

	pp = PokeStatusPokeParamGet( wk );

	if( wk->dat->ppt == PST_PP_TYPE_POKEPASO ){
		PokePasoParaWazaReplace( pp, wk->cur_pos, wk->sub_cur );
	}else{
		PokeParaWazaReplace( pp, wk->cur_pos, wk->sub_cur );
	}

	tmp_waza = wk->pp.waza[wk->cur_pos];
	wk->pp.waza[wk->cur_pos] = wk->pp.waza[wk->sub_cur];
	wk->pp.waza[wk->sub_cur] = tmp_waza;

	tmp_wpp = wk->pp.wpp[wk->cur_pos];
	wk->pp.wpp[wk->cur_pos] = wk->pp.wpp[wk->sub_cur];
	wk->pp.wpp[wk->sub_cur] = tmp_wpp;

	tmp_mpp = wk->pp.mpp[wk->cur_pos];
	wk->pp.mpp[wk->cur_pos] = wk->pp.mpp[wk->sub_cur];
	wk->pp.mpp[wk->sub_cur] = tmp_mpp;
}

static void WazaInfoPut( PST_WORK * wk )
{
//	PokeStatus_TabArrowVanish( wk, 0 );
	GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_LV] );
	GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_MOTIMONO] );
	GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_ITEMNAME] );

	GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, 0 );

	PokeStatus_SkillCancelPut( wk );
	WazaInfoChange( wk );

	CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_POKE1], 1 );
	PokeStatus_PokeIconSet( wk );
	if( wk->pp.type1 != wk->pp.type2 ){
		CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_POKE2], 1 );
	}
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_WAZACURSOR1], 1 );
}

//--------------------------------------------------------------------------------------------
//	�Z���i�R���e�X�g�j
//--------------------------------------------------------------------------------------------
static u8 ContestWazaInfoScrollIn( PST_WORK * wk )
{
	switch( wk->sub_seq ){
	case 0:
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, 136 );
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, 256 );

		ContestWazaHeartPut( wk, 0xffffffff );
		PokeStatus_TabArrowVanish( wk, 0 );
		GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_LV] );
		GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_MOTIMONO] );
		GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_ITEMNAME] );
		GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_GUIDE] );
		PokeStatus_A_ButtonMarkPut( wk, NULL );
		wk->cur_pos = 0;
		wk->sub_seq = 1;
		break;
	case 1:
		{
			int	cnt = GF_BGL_ScrollGetX( wk->bgl, GF_BGL_FRAME2_M );

			if( cnt <= 64 ){
				GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, 0 );
				wk->sub_seq = 2;
			}else{
				GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_DEC, 64 );
			}
		}
		break;
	case 2:
		PokeStatus_SkillCancelPut( wk );
		if( wk->dat->mode != PST_MODE_NO_WAZACHG ){
			PokeStatus_GuideStrPut( wk, mes_status_06_25 );
			PokeStatus_A_ButtonMarkPut( wk, &wk->def_win[WIN_GUIDE] );
		}
		WazaInfoChange( wk );
		PokeStatus_PokeIconSet( wk );
		PokeStatus_EzConditionPut( wk );
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_WAZACURSOR1], 1 );
		return TRUE;
	}
	return FALSE;
}

static u8 ContestWazaInfoScrollOut( PST_WORK * wk )
{
	switch( wk->sub_seq ){
	case 0:
		PokeStatus_EzConditionOff( wk );
		CATS_ObjectEnable( wk->awp[PST_OBJ_POKEICON], 0 );
		ContestWazaHeartPut( wk, 0xffffffff );
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_WAZACURSOR1], 0 );
		GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_GUIDE] );
		PokeStatus_A_ButtonMarkPut( wk, NULL );
		PokeStatus_SkillCancelDel( wk );
		PokeStatus_ContestWazaInfoOff( wk );
		wk->sub_seq = 1;
		break;
	case 1:
		{
			int	cnt = GF_BGL_ScrollGetX( wk->bgl, GF_BGL_FRAME2_M );

			if( cnt >= 128 ){
				GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, 136 );
				wk->sub_seq = 2;
			}else{
				GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_INC, 64 );
			}
		}
		break;
	case 2:
		GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_LV] );
		GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_MOTIMONO] );
		GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_ITEMNAME] );
		PokeStatus_GuideStrPut( wk, mes_status_07_02 );
		PokeStatus_TabArrowVanish( wk, 1 );
		PokeStatus_A_ButtonMarkPut( wk, &wk->def_win[WIN_GUIDE] );
		return TRUE;
	}
	return FALSE;
}


static void ContestWazaHeartPutMain( PST_WORK * wk, u16 chr, u8 num )
{
	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME2_M, chr,
		HEART_PX+num*2, HEART_PY, 1, 1, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME2_M, chr+1,
		HEART_PX+num*2+1, HEART_PY, 1, 1, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME2_M, chr+32,
		HEART_PX+num*2, HEART_PY+1, 1, 1, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME2_M, chr+33,
		HEART_PX+num*2+1, HEART_PY+1, 1, 1, GF_BGL_SCRWRT_PALNL );
}

static void ContestWazaHeartInit( PST_WORK * wk )
{
	u16	i;

	for( i=0; i<HEART_MAX; i++ ){
		ContestWazaHeartPutMain( wk, HEART2_CHR_NUM, i );
	}
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME2_M );
}

static void ContestWazaHeartPut( PST_WORK * wk, u32 waza )
{
	u32	ap_no;
	u16	i;
	s8	point;

	ContestWazaHeartInit( wk );

	if( waza != 0xffffffff ){
		ap_no = WT_WazaDataParaGet( waza, ID_WTD_ap_no );
		point = ConTool_GetAPWaza_App( ap_no ) / APP_APPEAL_ICON_ONE_POINT;
		for( i=0; i<point; i++ ){
			ContestWazaHeartPutMain( wk, HEART1_CHR_NUM, i );
		}
	}
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME2_M );
}




static void PST_WazaSetInfoOff( PST_WORK * wk )
{
	if( wk->page == PST_PAGE_B_SKILL ){
		PokeStatus_WazaInfoOff( wk );
	}else{
		PokeStatus_ContestWazaInfoOff( wk );
	}
}

static void PST_WazaSetInfoChange( PST_WORK * wk )
{
	PokeStatus_SkillCancelPut( wk );
	WazaInfoChange( wk );
	PokeStatus_PokeIconSet( wk );

	if( wk->page == PST_PAGE_B_SKILL ){
		PokeStatus_EzConditionOff( wk );
		CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_POKE1], 1 );
		if( wk->pp.type1 != wk->pp.type2 ){
			CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_POKE2], 1 );
		}
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, 0 );
	}else{
		PokeStatus_EzConditionPut( wk );
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, 256 );
	}
}




//--------------------------------------------------------------------------------------------
//	���{�����
//--------------------------------------------------------------------------------------------
static u8 RibbonInfoScrollIn( PST_WORK * wk )
{
	switch( wk->sub_seq ){
	case 0:
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, 256 );
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, 0 );

		PokeStatus_TabArrowVanish( wk, 0 );
		GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_MOTIMONO] );
		GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_ITEMNAME] );
		GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_P7_MOTTEIRU] );
		GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_GUIDE] );
		GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P7_NUM] );
		PokeStatus_A_ButtonMarkPut( wk, NULL );
/*
		ContestWazaHeartPut( wk, 0xffffffff );
		GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_LV] );
*/
		wk->ribbon_pos = 0;
		wk->ribbon_scr = 0;
//		wk->cur_pos = 0;
		wk->sub_seq = 1;
		break;
	case 1:
		{
			int	cnt = GF_BGL_ScrollGetY( wk->bgl, GF_BGL_FRAME2_M );

			if( cnt >= 48 ){
				GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, 56 );
				wk->sub_seq = 2;
			}else{
				GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_INC, 16 );
			}
		}
		break;
	case 2:
		PokeStatus_GuideStrPut( wk, mes_status_10_03 );
		PokeStatus_A_ButtonMarkPut( wk, &wk->def_win[WIN_GUIDE] );
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_RIBBON_CUR], 1 );
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_RIBBON_FLASH], 1 );
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_RIBBON09], 0 );
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_RIBBON10], 0 );
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_RIBBON11], 0 );
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_RIBBON12], 0 );
		RibbonSelect( wk, 0 );
/*
		PokeStatus_SkillCancelPut( wk );
		WazaInfoChange( wk );
		PokeStatus_PokeIconSet( wk );
		PokeStatus_EzConditionPut( wk );
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_WAZACURSOR1], 1 );
*/
		return TRUE;
	}
	return FALSE;
}

static u8 RibbonInfoScrollOut( PST_WORK * wk )
{
	switch( wk->sub_seq ){
	case 0:
		wk->ribbon_pos = 0;
		wk->ribbon_scr = 0;
		GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P7_MAXNUM] );
		GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P7_NAME] );
		GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P7_INFO] );
		GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_GUIDE] );
		PokeStatus_A_ButtonMarkPut( wk, NULL );
		PokeStatus_RibbonInit( wk );
/*
		PokeStatus_EzConditionOff( wk );
		CATS_ObjectEnable( wk->awp[PST_OBJ_POKEICON], 0 );
		ContestWazaHeartPut( wk, 0xffffffff );
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_WAZACURSOR1], 0 );
		PokeStatus_SkillCancelDel( wk );
		PokeStatus_ContestWazaInfoOff( wk );
*/
		wk->sub_seq = 1;
		break;
	case 1:
		{
			int	cnt = GF_BGL_ScrollGetY( wk->bgl, GF_BGL_FRAME2_M );

			if( cnt <= 8 ){
				GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, 0 );
				wk->sub_seq = 2;
			}else{
				GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_DEC, 16 );
			}
		}
		break;
	case 2:
		GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_MOTIMONO] );
		GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_ITEMNAME] );
		GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P7_MOTTEIRU] );
		GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_GUIDE] );
		GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P7_NUM] );
		PokeStatus_GuideStrPut( wk, mes_status_10_02 );

/*
		GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_LV] );
		GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_MOTIMONO] );
		GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_ITEMNAME] );
*/
		PokeStatus_TabArrowVanish( wk, 1 );
		PokeStatus_A_ButtonMarkPut( wk, &wk->def_win[WIN_GUIDE] );
		return TRUE;
	}
	return FALSE;
}


static void RibbonSelect( PST_WORK * wk, s8 mv )
{
	u8	cpy_pos;
	u8	cpy_scr;

	cpy_pos = wk->ribbon_pos;
	cpy_scr = wk->ribbon_scr;

	if( mv == 1 ){
		if( ( wk->ribbon_pos & 3 ) == 3 ){ return; }
		if( ( wk->ribbon_scr*4+wk->ribbon_pos+1 ) < wk->ribbon_max ){
			wk->ribbon_pos += 1;
		}
	}else if( mv == -1 ){
		if( ( wk->ribbon_pos & 3 ) == 0 ){ return; }
		wk->ribbon_pos -= 1;
	}else if( mv == 4 ){
		if( wk->ribbon_pos < 4 ){
			if( ( wk->ribbon_scr*4+wk->ribbon_pos+4 ) >= wk->ribbon_max ){
				if( wk->ribbon_max > 4 && ( wk->ribbon_max % 4 ) != 0 ){
					wk->ribbon_pos = wk->ribbon_max%4+3;
				}
			}else{
				wk->ribbon_pos += 4;
			}
		}else{
			if( ( wk->ribbon_scr*4+8 ) < wk->ribbon_max ){
				wk->ribbon_scr++;
				if( ( wk->ribbon_scr*4+wk->ribbon_pos ) >= wk->ribbon_max ){
					wk->ribbon_pos = wk->ribbon_max%4+3;
				}
			}
		}
	}else if( mv == -4 ){
		if( wk->ribbon_pos >= 4 ){
			wk->ribbon_pos -= 4;
		}else if( wk->ribbon_scr != 0 ){
			wk->ribbon_scr--;
		}
	}

	if( cpy_pos != wk->ribbon_pos || cpy_scr != wk->ribbon_scr ){
		Snd_SePlay( PST_SE_CURSOR_MOVE );
	}

	wk->ribbon_num = PokeStatus_RibbonPosIDGet( wk, wk->ribbon_pos );

	PokeStatus_RibbonCursorMove( wk );
	if( cpy_scr != wk->ribbon_scr ){
		PokeStatus_RibbonChange( wk );
	}
	PokeStatus_RibbonInfoPut( wk );
	PokeStatus_RibbonPosNumPut( wk );

	if( wk->ribbon_scr != 0 ){
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_RIBBON_AU], 1 );
	}else{
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_RIBBON_AU], 0 );
	}
	if( ( wk->ribbon_scr*4+8 ) < wk->ribbon_max ){
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_RIBBON_AD], 1 );
	}else{
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_RIBBON_AD], 0 );
	}
}

u8 PokeStatus_RibbonPosIDGet( PST_WORK * wk, u8 cur_pos )
{
	u16	i;
	u8	pos, cnt;

	pos = cur_pos + wk->ribbon_scr * 4;
	cnt = 0;

	for( i=0; i<RIBBON_MAX; i++ ){
		if( ( wk->pp.ribbon[i/32] & (1<<(i&0x1f)) ) != 0 ){
			if( pos == cnt ){
				return (u8)i;
			}
			cnt++;
		}
	}
	return 0;
}





static int PST_PorutoEatCehck( PST_WORK * wk )
{
	if( wk->pp.fur == PST_KEDUYA_MAX ){
		// ��b�E�B���h�E�Z�b�g
		TalkFontPaletteLoad( PALTYPE_MAIN_BG, PST_PAL_TALKFONT * 32, HEAPID_POKESTATUS );
		TalkWinGraphicSet(
			wk->bgl, GF_BGL_FRAME1_M, PST_CGX_TALKWIN,
			PST_PAL_TALKWIN, CONFIG_GetWindowType(wk->dat->cfg), HEAPID_POKESTATUS );
		PokeStatus_CondUpMsgPut( wk, PST_MSG_EATNONE );
		wk->dat->ret_mode = PST_RET_CANCEL;
		return SEQ_COND_END;
	}

	wk->dat->ret_mode = PST_RET_DECIDE;
	return SEQ_OUT_SET;
}


//--------------------------------------------------------------------------------------------
/**
 * �v���C���[���Z�b�g
 *
 * @param	dat		�X�e�[�^�X��ʃf�[�^
 * @param	my		MYSTATUS
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_PlayerSet( PSTATUS_DATA * dat, const MYSTATUS * my )
{
	dat->player_name = MyStatus_GetMyName( my );
	dat->player_id   = MyStatus_GetID( my );
	dat->player_sex  = (u8)MyStatus_GetMySex( my );
}


//--------------------------------------------------------------------------------------------
/**
 * ��Ԉُ�A�C�R���̃A�[�J�C�u�C���f�b�N�X���擾�i�L�����j
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32 BadStatusIconCharArcGet(void)
{
	return NARC_pst_gra_p_st_ijou_NCGR;
}

//--------------------------------------------------------------------------------------------
/**
 * ��Ԉُ�A�C�R���̃A�[�J�C�u�C���f�b�N�X���擾�i�p���b�g�j
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32 BadStatusIconPlttArcGet(void)
{
	return NARC_pst_gra_p_st_ijou_NCLR;
}

//--------------------------------------------------------------------------------------------
/**
 * ��Ԉُ�A�C�R���̃A�[�J�C�u�C���f�b�N�X���擾�i�Z���j
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32 BadStatusIconCellArcGet(void)
{
	return NARC_pst_gra_p_st_ijou_NCER;
}

//--------------------------------------------------------------------------------------------
/**
 * ��Ԉُ�A�C�R���̃A�[�J�C�u�C���f�b�N�X���擾�i�Z���A�j���j
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32 BadStatusIconCanmArcGet(void)
{
	return NARC_pst_gra_p_st_ijou_NANR;
}

//--------------------------------------------------------------------------------------------
/**
 * ��Ԉُ�A�C�R���̃A�j���ԍ����擾
 *
 * @param	pp		�|�P�����f�[�^
 *
 * @return	�A�j���ԍ�
 */
//--------------------------------------------------------------------------------------------
u32 BadStatusIconAnmGet( POKEMON_PARAM * pp )
{
	u32	prm = PokeParaGet( pp, ID_PARA_condition, NULL );

	// �m��
	if( PokeParaGet( pp, ID_PARA_hp, NULL ) == 0 ){
		return ST_ICON_HINSI;
	// ��
	}else if( ( prm & (CONDITION_DOKU|CONDITION_DOKUDOKU) ) != 0 ){
		return ST_ICON_DOKU;
	// ����
	}else if( ( prm & CONDITION_NEMURI ) != 0 ){
		return ST_ICON_NEMURI;
	// �Ώ�
	}else if( ( prm & CONDITION_YAKEDO ) != 0 ){
		return ST_ICON_YAKEDO;
	// �X
	}else if( ( prm & CONDITION_KOORI ) != 0 ){
		return ST_ICON_KOORI;
	// ���
	}else if( ( prm & CONDITION_MAHI ) != 0 ){
		return ST_ICON_MAHI;
	}
	// �Ȃ�
	return ST_ICON_NONE;
}
