#include "common.h"
#include "trcard_obj.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "trainer_case.naix"

#define MAIN_LCD	( GF_BGL_MAIN_DISP )	// 0
#define SUB_LCD		( GF_BGL_SUB_DISP )		// 1

//** CharManager PlttManager�p **//
#define TR_CARD_CHAR_CONT_NUM				(1)
#define TR_CARD_CHAR_VRAMTRANS_MAIN_SIZE	(2048)
#define TR_CARD_CHAR_VRAMTRANS_SUB_SIZE		(0)
#define TR_CARD_PLTT_CONT_NUM				(2)
#define TR_CARD_PALETTE_NUM					(9)	//�p���b�g9�{
#define TR_CARD_BADGE_PALETTE_NUM			(4)	//�p���b�g4�{

#define BTN_EFF_POS_X	(12*8)
#define BTN_EFF_POS_Y	(17*8)


typedef struct BADGE_POS_tag{
	int x;
	int y;
}BADGE_POS;

//���\�[�X�}�l�[�W���[�o�^���e�[�u��
static const u8 ResEntryNumTbl[RESOURCE_NUM] = {
	1,			//�L�������\�[�X
	2,			//�p���b�g���\�[�X
	1,			//�Z�����\�[�X
	1,			//�Z���A�j�����\�[�X
};

static const BADGE_POS BadgePos[] = {
	{8*3,8*5},
	{8*10,8*5},
	{8*17,8*5},
	{8*24,8*5},
	{8*3,8*(12-3)},
	{8*10,8*(12-3)},
	{8*17,8*(12-3)},
	{8*24,8*(12-3)},
};

static const BADGE_POS StarPos[] = {
	{8*3,8*5},
	{8*10,8*5},
	{8*17,8*5},
	{8*24,8*5},
	{8*3,8*12},
	{8*10,8*12},
	{8*17,8*12},
	{8*24,8*12},
};

static void InitCharPlttManager(void);

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[������
 *
 * @param	wk	�g���[�i�[�J�[�hOBJ���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void InitTRCardCellActor( TR_CARD_OBJ_WORK *wk )
{
	int i;
//	initVramTransferManagerHeap( 32, HEAPID_TR_CARD );
		
	InitCharPlttManager();
	// OAM�}�l�[�W���[�̏�����
	NNS_G2dInitOamManagerModule();

	// ���LOAM�}�l�[�W���쐬
	// �����_���pOAM�}�l�[�W���쐬
	// �����ō쐬����OAM�}�l�[�W�����݂�Ȃŋ��L����
	REND_OAMInit( 
			0, 128,		// ���C�����OAM�Ǘ��̈�
			0, 32,		// ���C����ʃA�t�B���Ǘ��̈�
			0, 128,		// �T�u���OAM�Ǘ��̈�
			0, 32,		// �T�u��ʃA�t�B���Ǘ��̈�
			HEAPID_TR_CARD);
	
	// �Z���A�N�^�[������
	wk->ClactSet = CLACT_U_SetEasyInit( TR_CARD_ACT_MAX, &wk->RendData, HEAPID_TR_CARD );
	
	//���\�[�X�}�l�[�W���[������
	for(i=0;i<RESOURCE_NUM;i++){		//���\�[�X�}�l�[�W���[�쐬
		wk->ResMan[i] = CLACT_U_ResManagerInit(ResEntryNumTbl[i], i, HEAPID_TR_CARD);
	}

	//chara�ǂݍ���
	wk->ResObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
										wk->ResMan[CLACT_U_CHAR_RES],
										ARC_TR_CASE_GRA, NARC_trainer_case_card_badge_NCGR,
										FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_TR_CARD);

	//pal�ǂݍ���
	wk->ResObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
										wk->ResMan[CLACT_U_PLTT_RES],
										ARC_TR_CASE_GRA, NARC_trainer_case_card_badge_NCLR,
										FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, TR_CARD_PALETTE_NUM, HEAPID_TR_CARD);

	//cell�ǂݍ���
	wk->ResObjTbl[MAIN_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELL_RES],
										ARC_TR_CASE_GRA, NARC_trainer_case_card_badge_NCER,
										FALSE, 1, CLACT_U_CELL_RES, HEAPID_TR_CARD);

	//�����֐���anim�ǂݍ���
	wk->ResObjTbl[MAIN_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELLANM_RES],
										ARC_TR_CASE_GRA, NARC_trainer_case_card_badge_NANR,
										FALSE, 1, CLACT_U_CELLANM_RES, HEAPID_TR_CARD);
							
	// ���\�[�X�}�l�[�W���[����]��

	// Chara�]��
	CLACT_U_CharManagerSet( wk->ResObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] );

	// �p���b�g�]��
	CLACT_U_PlttManagerSet( wk->ResObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] );
#if 0
	{
		CLACT_U_RES_OBJ_PTR res_obj_badge_plt;
		//pal�ǂݍ���(�o�b�W�p���b�g)
		res_obj_badge_plt = CLACT_U_ResManagerResAddArcPltt(
										wk->ResMan[CLACT_U_PLTT_RES],
										ARC_TR_CASE_GRA, NARC_trainer_case_card_badge2_NCLR,
										FALSE, 2, NNS_G2D_VRAM_TYPE_2DMAIN, TR_CARD_BADGE_PALETTE_NUM, HEAPID_TR_CARD);
		// �p���b�g�]��
		CLACT_U_PlttManagerSet( res_obj_badge_plt );
	}
#endif
	{
		u8 i;
		ARCHANDLE* pal_handle;

		const int pal_arc_idx[TR_CARD_BADGE_ACT_MAX] = {
			NARC_trainer_case_card_badge2_0_NCLR,
			NARC_trainer_case_card_badge2_1_NCLR,
			NARC_trainer_case_card_badge2_2_NCLR,
			NARC_trainer_case_card_badge2_3_NCLR,
			NARC_trainer_case_card_badge2_4_NCLR,
			NARC_trainer_case_card_badge2_5_NCLR,
			NARC_trainer_case_card_badge2_6_NCLR,
			NARC_trainer_case_card_badge2_7_NCLR
		};
		//�p���b�g�A�[�J�C�u�n���h���I�[�v��
		pal_handle  = ArchiveDataHandleOpen( ARC_TR_CASE_GRA, HEAPID_TR_CARD);
		for (i=0;i<TR_CARD_BADGE_ACT_MAX;i++){
			wk->PalDataBuf[i] = ArchiveDataLoadAllocByHandle( pal_handle, pal_arc_idx[i], HEAPID_TR_CARD );
			if( wk->PalDataBuf[i] != NULL )
			{
				if( NNS_G2dGetUnpackedPaletteData( wk->PalDataBuf[i], &wk->PalData[i] ) == FALSE ){
					sys_FreeMemoryEz( wk->PalData[i] );
					GF_ASSERT(0);
				}
			}else{
				GF_ASSERT(0);
			}
		}
		//�n���h���N���[�Y
		ArchiveDataHandleClose( pal_handle );
	}
	
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );		// MAIN DISP OBJ ON
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[���Z�b�g
 *
 * @param	
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SetTrCardActor( TR_CARD_OBJ_WORK *wk, const u8 *inBadgeDisp )
{
	int i;
	CLACT_HEADER			cl_act_header;
	
	// �Z���A�N�^�[�w�b�_�쐬	
	CLACT_U_MakeHeader(	&cl_act_header,
						1, 1, 1, 1,
						CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
						0, 1,
						wk->ResMan[CLACT_U_CHAR_RES],
						wk->ResMan[CLACT_U_PLTT_RES],
						wk->ResMan[CLACT_U_CELL_RES],
						wk->ResMan[CLACT_U_CELLANM_RES],
						NULL,NULL);

	{
		//�o�^���i�[
		u8 ofs;
		CLACT_ADD add;

		add.ClActSet	= wk->ClactSet;
		add.ClActHeader	= &cl_act_header;

		add.mat.x		= 0;//FX32_CONST(32) ;
		add.mat.y		= 0;//FX32_CONST(96) ;		//��ʂ͏㉺�A�����Ă���
		add.mat.z		= 0;
		add.sca.x		= FX32_ONE;
		add.sca.y		= FX32_ONE;
		add.sca.z		= FX32_ONE;
		add.rot			= 0;
		add.pri			= 2;
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		add.heap		= HEAPID_TR_CARD;

		//�Z���A�N�^�[�\���J�n

		// �����(���C�����)
		//�o�b�W
		for(i=0;i<TR_CARD_BADGE_ACT_MAX;i++){
			add.mat.x = FX32_ONE * BadgePos[i].x;
			add.mat.y = FX32_ONE * BadgePos[i].y;
			wk->ClActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->ClActWork[i],0);
			CLACT_AnmChg( wk->ClActWork[i], i );
			if (!inBadgeDisp[i]){
				CLACT_SetDrawFlag(wk->ClActWork[i], 0);	//��\��
			}
		}
		//�L���L��
		{
			ofs = TR_CARD_BADGE_ACT_MAX;
			for (i=0;i<TR_CARD_STAR_ACT_MAX;i++){
				add.mat.x = FX32_ONE * StarPos[i].x;
				add.mat.y = FX32_ONE * StarPos[i].y;
				add.pri	= 1;
				wk->ClActWork[ofs+i] = CLACT_Add(&add);
				CLACT_SetAnmFlag(wk->ClActWork[ofs+i],1);
				CLACT_AnmChg( wk->ClActWork[ofs+i], 8 );
				CLACT_SetDrawFlag(wk->ClActWork[ofs+i], 0);	//��\��
			}
			ofs += TR_CARD_STAR_ACT_MAX;
			for (i=0;i<TR_CARD_GRATE_STAR_ACT_MAX;i++){
				add.mat.x = FX32_ONE * StarPos[i].x;
				add.mat.y = FX32_ONE * StarPos[i].y;
				add.pri	= 1;
				wk->ClActWork[ofs+i] = CLACT_Add(&add);
				CLACT_SetAnmFlag(wk->ClActWork[ofs+i],1);
				CLACT_AnmChg( wk->ClActWork[ofs+i], 9 );
				CLACT_SetDrawFlag(wk->ClActWork[ofs+i], 0);	//��\��
			}
		}
		ofs += TR_CARD_GRATE_STAR_ACT_MAX;
		//�{�^���G�t�F�N�g
		{
			cl_act_header.priority = 0;
			add.mat.x = FX32_ONE * BTN_EFF_POS_X;
			add.mat.y = FX32_ONE * BTN_EFF_POS_Y;
			add.pri	= 0;
			wk->ClActWork[ofs] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->ClActWork[ofs],0);
			CLACT_AnmChg( wk->ClActWork[ofs], 10 );
			CLACT_SetDrawFlag(wk->ClActWork[ofs], 0);	//��\��;
		}
	}	
}

//--------------------------------------------------------------------------------------------
/**
 * 2D�Z���I�u�W�F�N�g���
 *
 * @param	wk	�I�u�W�F�N�g���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void RereaseCellObject(TR_CARD_OBJ_WORK *wk)
{
	u8 i;
	//�p���b�g���
	for(i=0;i<TR_CARD_BADGE_ACT_MAX;i++){
		sys_FreeMemoryEz(wk->PalDataBuf[i]);
	}

	// �Z���A�N�^�[���\�[�X���

	// �L�����]���}�l�[�W���[�j��
	CLACT_U_CharManagerDelete(wk->ResObjTbl[MAIN_LCD][CLACT_U_CHAR_RES]);

	// �p���b�g�]���}�l�[�W���[�j��
	CLACT_U_PlttManagerDelete(wk->ResObjTbl[MAIN_LCD][CLACT_U_PLTT_RES]);
		
	// �L�����E�p���b�g�E�Z���E�Z���A�j���̃��\�[�X�}�l�[�W���[�j��
	for(i=0;i<RESOURCE_NUM;i++){
		CLACT_U_ResManagerDelete(wk->ResMan[i]);
	}
	// �Z���A�N�^�[�Z�b�g�j��
	CLACT_DestSet(wk->ClactSet);

	//OAM�����_���[�j��
	REND_OAM_Delete();

	DeleteCharManager();
	DeletePlttManager();

}

//--------------------------------------------------------------------------------------------
/**
 * �o�b�W�p���b�g�ύX
 *
 * @param	wk			OBJ���[�N
 * @param	inBadgeNo	�o�b�W�i���o�[
 * @param	inOalNo		�p���b�g�ԍ�
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SetBadgePalette( TR_CARD_OBJ_WORK *wk, const u8 inBadgeNo, const u8 inPalNo )
{
	NNSG2dImagePaletteProxy *proxy;
	u32 palette_vram;
	u32 pal_ofs;
	u8 * adr;
	
	GF_ASSERT(inBadgeNo<TR_CARD_BADGE_ACT_MAX);
	GF_ASSERT(inPalNo<=3);
	
///	CLACT_PaletteNoChg( wk->ClActWork[inBadgeNo], inPalNo );

	proxy = CLACT_PaletteProxyGet( wk->ClActWork[inBadgeNo] );
	palette_vram = NNS_G2dGetImagePaletteLocation(proxy, NNS_G2D_VRAM_TYPE_2DMAIN);
	palette_vram += inBadgeNo*(16*2);
	adr = wk->PalData[inBadgeNo]->pRawData;
	DC_FlushRange( &adr[inPalNo*16*2], 16*2 );
	GX_LoadOBJPltt( &adr[inPalNo*16*2], palette_vram, 16*2 );	//32byte 1Palette
}

//-------------------------------------
//
//	�L�����N�^�}�l�[�W���[
//	�p���b�g�}�l�[�W���[�̏�����
//
//=====================================
static void InitCharPlttManager(void)
{
	// �L�����N�^�}�l�[�W���[������
	{
		CHAR_MANAGER_MAKE cm = {
			TR_CARD_CHAR_CONT_NUM,
			TR_CARD_CHAR_VRAMTRANS_MAIN_SIZE,
			TR_CARD_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_TR_CARD
		};
		InitCharManager(&cm);
	}
	// �p���b�g�}�l�[�W���[������
	InitPlttManager(TR_CARD_PLTT_CONT_NUM, HEAPID_TR_CARD);

	// �ǂݍ��݊J�n�ʒu��������
	CharLoadStartAll();
	PlttLoadStartAll();

//	DellVramTransferManager();
}


