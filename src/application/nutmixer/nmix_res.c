/**
 *	@file	nmix_res.c
 *	@brief	�i�b�c�~�L�T�[�@���\�[�X�Ǘ�
 *	@author	Miyuki Iwasawa
 *	@date	06.04.08
 */

#include "common.h"
#include "system/procsys.h"
#include "system/snd_tool.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/buflen.h"
#include "system/palanm.h"
#include "system/savedata.h"
#include "system/render_oam.h"
#include "itemtool/itemsym.h"
#include "itemtool/item.h"
#include "gflib/strbuf_family.h"

#include "application/nutmixer.h"
#include "nutmixer_sys.h"
#include "nmix_game.h"
#include "nmix_gameseq.h"

#include "nutmixer.naix"

#define __NMIX_RES_H_GLOBAL
#include "nmix_res.h"

//======================================================
//�Q�[���v���Z�X�@�R�}���h���T�u�V�[�P���X�Q
//======================================================
static void nmixGame_BGLInit(GF_BGL_INI** bgl,int heapID);
static void nmixGame_BGLRelease(GF_BGL_INI** bgl);
static void nmixGame_ClactInit( NMIX_GAMEWORK* wk );
static void nmixGame_ClactDelete( NMIX_GAMEWORK* wk );
static void nmixGame_SwspInit( NMIX_GAMEWORK* wk );
static void nmixGame_SwspDelete( NMIX_GAMEWORK* wk );
static void nmixGame_OamRegInit( NMIX_GAMEWORK* wk );
static void nmixGame_OamRegDelete( NMIX_GAMEWORK* wk );
static void nmixGame_DefOamResLoad( NMIX_GAMEWORK* wk );
static void nmixGame_DefOamResRelease( NMIX_GAMEWORK* wk );
static void nmixGame_3DInit( NMIX_GAMEWORK* wk );
static void nmixGame_3DRelease( NMIX_GAMEWORK* wk );
static void nmix_CommonDataInit(NMIX_GAMEWORK* wk);
static void nmix_CommonDataRelease(NMIX_GAMEWORK* wk);

//======================================================
//�Q�[���v���Z�X�@�R�}���h�Q
//======================================================
/**
 *	@brief	�R�}���h�@���\�[�X������
 */
void NMixGameCom_GameStartGraphicInit(NMIX_GAMEWORK* wk)
{
	// �Ǘ��V�X�e��������
	nmixGame_3DInit( wk );
	nmixGame_BGLInit(&(wk->bgl),wk->heapID);	
	nmixGame_OamRegInit( wk );
	nmixGame_ClactInit( wk );
	nmixGame_SwspInit( wk );


	nmixGame_DefOamResLoad( wk );	// �f�t�H���gOAM���\�[�X
	NMixGameDemo_SubWin_GraphicLoad( &wk->sub_win, wk->bgl, wk->heapID );
	NMixGameDemo_MainWin_GraphicLoad( &wk->main_win, wk->bgl, wk->heapID );
	NMixGameDemo_NabeGra_GraphicLoad( &wk->nabe_gra, wk->swsp_sys, wk->heapID );
	NMixGameDemo_CountDown_GraphicLoad( &wk->countdown, &wk->clact,
			wk->def_clact_res, wk->heapID, NMIX_GAME_DEF_OAM_RES_START, 0 );

	NMixGameDemo_CountDown_GraphicLoad( &wk->pen, &wk->clact,
			wk->def_clact_res, wk->heapID, NMIX_GAME_DEF_OAM_RES_START, 2 );
	NMixGameDemo_CountDown_GraphicLoad( &wk->end_mark, &wk->clact,
			wk->def_clact_res, wk->heapID, NMIX_GAME_DEF_OAM_RES_END, 0 );
	NMixGameDemo_OtherMark_GraphicLoad( &wk->other_mark, &wk->clact,
			wk->def_clact_res, wk->heapID );
	NMixGameDemo_SoopEffect_GraphicLoad( &wk->soop_effect, &wk->clact,
			wk->def_clact_res, wk->heapID );
	NMixGameDemo_Yazirusi_GraphicLoad( &wk->yazirusi, &wk->clact, wk->heapID );
	NMixGameDemo_HosiKiraKira_GraphicLoad( &wk->hosi_kira, &wk->clact,
			wk->def_clact_res, wk->heapID );



	// ���b�Z�[�W�f�[�^
	nmix_CommonDataInit(wk);

	// �`����ύX
	sys.disp3DSW = DISP_3D_TO_SUB;
	GF_Disp_DispSelect();
}

/**
 *	@brief	�R�}���h�@���\�[�X���
 */
void NMixGameCom_GameStartGraphicRelease(NMIX_GAMEWORK* wk)
{

	NMixGameDemo_MainWin_GraphicRelease( &wk->main_win );
	NMixGameDemo_SubWin_GraphicRelease( &wk->sub_win );
	NMixGameDemo_NabeGra_GraphicRelease( &wk->nabe_gra );
	nmixGame_DefOamResRelease( wk );	// �f�t�H���gOAM���\�[�X
	NMixGameDemo_CountDown_GraphicRelease( &wk->countdown );
	NMixGameDemo_CountDown_GraphicRelease( &wk->end_mark );
	NMixGameDemo_CountDown_GraphicRelease( &wk->pen );
	NMixGameDemo_OtherMark_GraphicRelease( &wk->other_mark );
	NMixGameDemo_SoopEffect_GraphicRelease( &wk->soop_effect );
	NMixGameDemo_Yazirusi_GraphicRelease( &wk->yazirusi );
	NMixGameDemo_HosiKiraKira_GraphicRelease( &wk->hosi_kira );
	
	
	// �Ǘ��V�X�e���j��
	nmixGame_BGLRelease(&(wk->bgl));	
	nmixGame_ClactDelete( wk );
	nmixGame_OamRegDelete( wk );
	nmixGame_SwspDelete( wk );
	nmixGame_3DRelease( wk );

	//���b�Z�[�W�f�[�^
	nmix_CommonDataRelease(wk);

	// �`����ύX
	sys.disp3DSW = DISP_3D_TO_MAIN;
	GF_Disp_DispSelect();
}


/**
 *	@brief	�R�}���h�@���\�[�X������
 */
int NMixGameCom_ResInit(NMIX_GAMEWORK* wk,int* seq)
{
	// �e���[�N�̕`�敨�ǂݍ���
	NMixGameDemo_NutsIn_GraphicLoad( &wk->nuts_in, 
			&wk->game_comm_pack.get_ko_before_data, &wk->clact, 
			wk->def_clact_res, wk->heapID);

	return wk->main_seq + 1;
}

/**
 *	@brief	�R�}���h�@���\�[�X���
 */
int NMixGameCom_ResRelease(NMIX_GAMEWORK* wk,int *seq)
{
	// �e���[�N�̕`�敨�j��
	NMixGameDemo_NutsIn_GraphicRelease( &wk->nuts_in, &wk->clact );

	
	return wk->main_seq + 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief		�O���t�B�b�N�`�揈��
 */
//-----------------------------------------------------------------------------
void NMixGame_Draw( NMIX_GAMEWORK* wk )
{
	//�R�c�`��J�n
	GF_G3X_Reset();

	NNS_G3dGePushMtx();
	{
		NNS_G3dGeFlushBuffer();

		// �\�t�g�E�F�A�X�v���C�g�̕`��
		// �J�����Z�b�g�A�b�v
		NNS_G2dSetupSoftwareSpriteCamera();
		// �\�t�g�E�F�A�X�v���C�g�`��
		if( wk->swsp_sys ){
			SWSP_SysDraw( wk->swsp_sys );
		}
	}
	NNS_G3dGePopMtx(1);

	/* �W�I���g���������_�����O�G���W���֘A�������̃X���b�v */
	GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);

	// �Z���A�N�^�[�`��
	if( wk->clact_draw ){
		if( wk->clact.cas ){
			CLACT_Draw( wk->clact.cas );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief		�`��֌WV�u�����N����
 */
//-----------------------------------------------------------------------------
void NMixGame_GraVBlank( NMIX_GAMEWORK* wk )
{
	// �����_���[OAM�]��
	REND_OAMTrans();
	if( wk->bgl ){
		GF_BGL_VBlankFunc( wk->bgl );
	}
}





//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------

//======================================================
//�Q�[���v���Z�X�@���[�J���T�u�֐��Q
//======================================================
/**
 *	@brief	�i�b�c�~�L�T�[VramBank�ݒ�
 */
static void nmixGame_VBankSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_64_E,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_48_HI,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_128_A,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_NONE,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_01_BC,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_01_FG			// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &vramSetTable );
}

/**
 *	@brief	BGL�Z�b�g
 */
static void nmixGame_BGLInit(GF_BGL_INI** bgl,int heapID)
{
	int i = 0,frame;

	//VramBank�Z�b�g
	nmixGame_VBankSet();

	//BGL������
	*bgl = GF_BGL_BglIniAlloc(heapID);
	
	{	//BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0,GX_BG0_AS_3D
		};
		GF_BGL_InitBG(&BGsys_data);
	}

	// 3D�ʕ\��ON
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	GF_BGL_PrioritySet( GF_BGL_FRAME0_M, 2 );
	
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
			{	//MAIN BG1	�e�L�X�g�w�i��
				0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0xf000,GX_BG_CHARBASE_0x08000,GX_BG_EXTPLTT_01,
				1,0,0,FALSE
			},
			{	//MAIN BG2	�e�L�X�g��
				0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0xe800,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
				0,0,0,FALSE
			},
			{	//SUB BG0	������ʂɎg�p
				0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0xb000,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
				0,0,0,FALSE
			},
			{	//SUB BG1	�w�i�Ɏg�p
				0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0xa800,GX_BG_CHARBASE_0x08000,GX_BG_EXTPLTT_01,
				1,0,0,FALSE
			},
		};
		for(i = 0;i < 4;i++){
			const u8 frame[4] = 
			{GF_BGL_FRAME1_M,GF_BGL_FRAME2_M,GF_BGL_FRAME0_S,GF_BGL_FRAME1_S};
			
			GF_BGL_BGControlSet(*bgl,frame[i],&(TextBgCntDat[i]),GF_BGL_MODE_TEXT);
			GF_BGL_ScrClear(*bgl,frame[i]);
			GF_BGL_ClearCharSet(frame[i],32,0,heapID);
		}
	}
}

/**
 *	@brief	BGL���
 */
static void nmixGame_BGLRelease(GF_BGL_INI** bgl)
{
	GF_BGL_BGControlExit(*bgl,GF_BGL_FRAME1_S);
	GF_BGL_BGControlExit(*bgl,GF_BGL_FRAME0_S);
	GF_BGL_BGControlExit(*bgl,GF_BGL_FRAME2_M);
	GF_BGL_BGControlExit(*bgl,GF_BGL_FRAME1_M);
	sys_FreeMemoryEz(*bgl);
}


//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[������
 *
 *	@param	wk	���[�N
 */
//-----------------------------------------------------------------------------
static void nmixGame_ClactInit( NMIX_GAMEWORK* wk )
{
	NMIXGAME_CLACT_Init( &wk->clact, NMIX_GAME_CLACT_WORK_MAX, NMIX_GAME_CLACT_RES_MAX, wk->heapID );
	
	// OBJON
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[�j��
 *
 *	@param	wk	���[�N
 */
//-----------------------------------------------------------------------------
static void nmixGame_ClactDelete( NMIX_GAMEWORK* wk )
{
	NMIXGAME_CLACT_Delete( &wk->clact );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�\�t�g�E�F�A�X�v���C�g������
 *
 *	@param	wk	���[�N
 */
//-----------------------------------------------------------------------------
static void nmixGame_SwspInit( NMIX_GAMEWORK* wk )
{
	SWSP_SYSDATA swsp_sys_data = {
		NMIX_GAME_SWSP_WORK_MAX,
		NMIX_GAME_SWSP_CHAR_MAX,			
		NMIX_GAME_SWSP_PLTT_MAX,
		0
	};
	swsp_sys_data.heap = wk->heapID;

	wk->swsp_sys = SWSP_SysInit( &swsp_sys_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�\�t�g�E�F�A�X�v���C�g�j��
 *
 *	@param	wk	���[�N
 */
//-----------------------------------------------------------------------------
static void nmixGame_SwspDelete( NMIX_GAMEWORK* wk )
{
	// �\�t�g�E�F�A�X�v���C�g
	SWSP_SysDelete( wk->swsp_sys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�̃��W�X�^������
 */
//-----------------------------------------------------------------------------
static void nmixGame_OamRegInit( NMIX_GAMEWORK* wk )
{
	// OAM�}�l�[�W���[�̏�����
	NNS_G2dInitOamManagerModule();

	// ���LOAM�}�l�[�W���쐬
	// �����_���pOAM�}�l�[�W���쐬
	// �����ō쐬����OAM�}�l�[�W�����݂�Ȃŋ��L����
	REND_OAMInit( 
			NMIX_OAM_OAM_MAIN_S, NMIX_OAM_OAM_MAIN_E,	// ���C�����NMIX_OAM�Ǘ��̈�
			NMIX_OAM_AFF_MAIN_S, NMIX_OAM_AFF_MAIN_E,			// ���C����ʃA�t�B���Ǘ��̈�
			NMIX_OAM_OAM_SUB_S, NMIX_OAM_OAM_SUB_E,		// �T�u���NMIX_OAM�Ǘ��̈�
			NMIX_OAM_AFF_SUB_S, NMIX_OAM_AFF_SUB_E,		// �T�u��ʃA�t�B���Ǘ��̈�
			wk->heapID);
	
	// �L�����N�^�}�l�[�W���[������
	{
		CHAR_MANAGER_MAKE cm = {
			NMIX_OAM_CHAR_ENTRY_NUM,
			NMIX_OAM_CHAR_VRAMTRANS_MAIN_SIZE,
			NMIX_OAM_CHAR_VRAMTRANS_SUB_SIZE,
		};
		cm.heap = wk->heapID;
		
		InitCharManagerReg(&cm, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_32K );
	}
	// �p���b�g�}�l�[�W���[������
	InitPlttManager(NMIX_OAM_PLTT_ENTRY_NUM, wk->heapID);

	// �ǂݍ��݊J�n�ʒu��������
	CharLoadStartAll();
	PlttLoadStartAll();
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�̃��W�X�^�Ǘ��f�[�^�j��
 */
//-----------------------------------------------------------------------------
static void nmixGame_OamRegDelete( NMIX_GAMEWORK* wk )
{
	// �����_���[���LOAM�}�l�[�W���j��
	REND_OAM_Delete();
	
	// �L�����N�^�f�[�^�j��
	DeleteCharManager();
	// �p���b�g�f�[�^�j��
	DeletePlttManager();
}

//----------------------------------------------------------------------------
/**
 *	@brief	�f�t�H���gOAM���\�[�X�ǂݍ���
 */
//-----------------------------------------------------------------------------
static void nmixGame_DefOamResLoad( NMIX_GAMEWORK* wk )
{
	int i;
	static const u8 ClPlttTbl[ NMIX_GAME_DEF_OAM_RES_NUM ] = {
		NARC_nutmixer_cook_s_obj0_NCLR,
		NARC_nutmixer_cook_s_obj0_NCLR,
		NARC_nutmixer_cook_s_obj2_NCLR,
		NARC_nutmixer_cook_s_obj3_NCLR,
		NARC_nutmixer_cook_s_obj4_NCLR,
		NARC_nutmixer_cook_s_obj0_NCLR,
	};

	for( i=0; i<NMIX_GAME_DEF_OAM_RES_NUM; i++ ){
		if( (i > 0) && (ClPlttTbl[ i ] == NARC_nutmixer_cook_s_obj0_NCLR) ){		
			NMIXGAME_CLACT_ResLoadEasy_PlttCopy( &wk->clact,		// ���\�[�X�C���f�b�N�X0�̃p���b�g���F���ʂŎg�p����
					&wk->def_clact_res[ i ], ARC_NUTMIXER_GRA,
					wk->def_clact_res[ 0 ].resobj[1],
					NARC_nutmixer_cook_s_obj0_NCGR + (3*i), 
					NARC_nutmixer_cook_s_obj0_NCER + (3*i), 
					NARC_nutmixer_cook_s_obj0_NANR + (3*i), 
					NMIX_GAME_DEF_OAM_CONTID + i, wk->heapID );

		}else{
			NMIXGAME_CLACT_ResLoadEasy( &wk->clact,
					&wk->def_clact_res[ i ], ARC_NUTMIXER_GRA,
					ClPlttTbl[ i ],
					NMIX_GAME_DEF_OAM_CL,
					NARC_nutmixer_cook_s_obj0_NCGR + (3*i), 
					NARC_nutmixer_cook_s_obj0_NCER + (3*i), 
					NARC_nutmixer_cook_s_obj0_NANR + (3*i), 
					NMIX_GAME_DEF_OAM_CONTID + i, wk->heapID );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�f�t�H���gOAM���\�[�X�j��
 */
//-----------------------------------------------------------------------------
static void nmixGame_DefOamResRelease( NMIX_GAMEWORK* wk )
{
	int i;

	for( i=0; i<NMIX_GAME_DEF_OAM_RES_NUM; i++ ){
		NMIXGAME_CLACT_ResDeleteEasy( &wk->clact,
				&wk->def_clact_res[ i ] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�RD������
 */
//-----------------------------------------------------------------------------
static void nmixGame_3DInit( NMIX_GAMEWORK* wk )
{
	// NitroSystem:�R�c�G���W���̏�����
	NNS_G3dInit();
	// �}�g���N�X�X�^�b�N�̏�����
    G3X_InitMtxStack();

	// �e��`�惂�[�h�̐ݒ�(�V�F�[�h���A���`�G�C���A�X��������)
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(TRUE);
	G3X_AlphaTest(FALSE, 0);	// �A���t�@�e�X�g�@�@�I�t
	G3X_AlphaBlend(TRUE);		// �A���t�@�u�����h�@�I��

	// �G�b�W�}�[�L���O
	G3X_EdgeMarking(FALSE);

	
	// �N���A�J���[�̐ݒ�
    G3X_SetClearColor(GX_RGB(31, 31, 16),	// clear color
                      0,				// clear alpha
                      0x7fff,			// clear depth
                      63,				// clear polygon ID
                      FALSE				// fog
                      );

	// �W�I���g���G���W���N����K���Ă΂�Ȃ���΂Ȃ�Ȃ�
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);

	// �r���[�|�[�g�̐ݒ�
    G3_ViewPort(0, 0, 255, 191);

	// �}�l�[�W�����e�N�X�`���C���[�W�X���b�g���w��X���b�g���Ǘ��ł���悤�ɂ���
	// �f�t�H���g�}�l�[�W���ɂ���B
	NNS_GfdInitFrmTexVramManager(2, TRUE);
		
	// �}�l�[�W�����p���b�g��32KB���Ǘ��ł���悤�ɂ���
	// �f�t�H���g�}�l�[�W���ɂ���B
	NNS_GfdInitFrmPlttVramManager(0x8000, TRUE);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�RD�j��
 */
//-----------------------------------------------------------------------------
static void nmixGame_3DRelease( NMIX_GAMEWORK* wk )
{
	NNS_GfdResetFrmTexVramState();
	NNS_GfdResetFrmPlttVramState();
}

/**
 *	@brief	������f�[�^�쐬	
 */
static void nmix_CommonDataInit(NMIX_GAMEWORK* wk)
{
	int i;
	
	//���b�Z�[�W�}�l�[�W��������
	wk->msgDat.man = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
		NARC_msg_porutogame1_dat,wk->heapID);
	
	wk->msgDat.wset = WORDSET_CreateEx( NMIX_GAME_WORD_SET_MAX, WORDSET_NMIXER_BUFLEN,wk->heapID);
	
	//�f�t�H���g������擾
	wk->msgDat.tmp = STRBUF_Create(WORDSET_NMIXER_BUFLEN,wk->heapID);

	wk->msgDat.wait = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_00_01);
	wk->msgDat.nuts_in = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_01_01);
	wk->msgDat.tr_name = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_02_01);

	wk->msgDat.casein = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_05_01);
	wk->msgDat.replay = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_05_02);
	wk->msgDat.exit = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_05_03);
	wk->msgDat.bag_erabu = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_05_04);
	wk->msgDat.poruto_ippai = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_05_05);
	wk->msgDat.nuts_none = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_05_06);

	wk->msgDat.end = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_03_06);
	wk->msgDat.result = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_04_01);

	for(i = 0;i < NMIX_STMSG_SPEED_NUM;i++){
		wk->msgDat.spd[i] = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_03_01+i);
	}
	for(i = 0;i < NMIX_STMSG_RESULT_NUM;i++){
		wk->msgDat.res[i] = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_04_02+i);
	}
}


/**
 *	@brief	������f�[�^�j��
 */
static void nmix_CommonDataRelease(NMIX_GAMEWORK* wk)
{
	int i;
	
	STRBUF_Delete(wk->msgDat.result);	
	STRBUF_Delete(wk->msgDat.end);	
	
	STRBUF_Delete(wk->msgDat.exit);	
	STRBUF_Delete(wk->msgDat.replay);	
	STRBUF_Delete(wk->msgDat.casein);	
	
	STRBUF_Delete(wk->msgDat.tr_name);	
	STRBUF_Delete(wk->msgDat.nuts_in);	
	STRBUF_Delete(wk->msgDat.wait);	
	STRBUF_Delete(wk->msgDat.bag_erabu);
	STRBUF_Delete(wk->msgDat.poruto_ippai);
	STRBUF_Delete(wk->msgDat.nuts_none);
	
	for(i = 0;i < NMIX_STMSG_SPEED_NUM;i++){
		STRBUF_Delete(wk->msgDat.spd[i]);
	}
	for(i = 0;i < NMIX_STMSG_RESULT_NUM;i++){
		STRBUF_Delete(wk->msgDat.res[i]);
	}
	STRBUF_Delete(wk->msgDat.tmp);
	
	WORDSET_Delete(wk->msgDat.wset);
	MSGMAN_Delete(wk->msgDat.man);
}



