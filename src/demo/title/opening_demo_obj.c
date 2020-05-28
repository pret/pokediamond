//=============================================================================
/**
 * @file	opening_demo_obj.c
 * @brief	�I�[�v�j���O�f���n�a�i
 * @author	Nozomu Saito
 * @date    2006.06.03
 */
//=============================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "op_demo.naix"
#include "opening_kira_obj.h"
#include "opening_demo_obj.h"
#include "op_frame_def.h"


#define RESOURCE_NUM	(4)
#define PERSON_ACT_MAX	(3)
#define BIRD_ACT_MAX	(6)
#define KIRA_ACT_MAX	(16)

#define OPD_CHAR_CONT_NUM				(ACT_ID_MAX)
#define OPD_CHAR_VRAMTRANS_MAIN_SIZE	(0)
#define OPD_CHAR_VRAMTRANS_SUB_SIZE		(0)
#define OPD_PLTT_CONT_NUM				(ACT_ID_MAX)


#define PALETTE_NUM	(1)		//�p���b�g�P�{

#define OP_DEMO_ACT_MAX	( PERSON_ACT_MAX+BIRD_ACT_MAX+KIRA_ACT_MAX )
#define CLACT_WORK_MAX	( PERSON_ACT_MAX+BIRD_ACT_MAX )

#define HERO_POS_X		(128-48)	//�j��l���̂w�ʒu�i�h�b�g�j
#define HEROINE_POS_X	(128+48)	//����l���̂w�ʒu�i�h�b�g�j
#define HERO_POS_Y		(14*8)		//�j��l���̂x�ʒu�i�h�b�g�j
#define HEROINE_POS_Y	(14*8)		//����l���̂x�ʒu�i�h�b�g�j
#define RIVAL_POS_X		(256+64)	//���C�o���̂w�ʒu�i�h�b�g�j
#define RIVAL_POS_Y		(14*8)		//���C�o���̂x�ʒu�i�h�b�g�j
#define BIRD_1_POS_X	(256+8)		//��1�̂w�ʒu�i�h�b�g�j
#define BIRD_1_POS_Y	(16*8)		//��1�̂x�ʒu�i�h�b�g�j
#define BIRD_2_POS_X	(256+32)	//��2�̂w�ʒu�i�h�b�g�j
#define BIRD_2_POS_Y	(14*8)		//��2�̂x�ʒu�i�h�b�g�j
#define BIRD_3_POS_X	(256+32)	//��3�̂w�ʒu�i�h�b�g�j
#define BIRD_3_POS_Y	(18*8)		//��3�̂x�ʒu�i�h�b�g�j

#define BIRD_4_POS_X	(192+8)		//��4�̂w�ʒu�i�h�b�g�j
#define BIRD_4_POS_Y	(28*8)		//��4�̂x�ʒu�i�h�b�g�j
#define BIRD_5_POS_X	(192+32)	//��5�̂w�ʒu�i�h�b�g�j
#define BIRD_5_POS_Y	(26*8)		//��5�̂x�ʒu�i�h�b�g�j
#define BIRD_6_POS_X	(192+32)	//��6�̂w�ʒu�i�h�b�g�j
#define BIRD_6_POS_Y	(30*8)		//��6�̂x�ʒu�i�h�b�g�j

#define RIVAL_SLIDE_SPEED	(FX32_ONE*14)


#define RIVAL_POS_END_X	(FX32_ONE*(128+48))	//�X���C�h�C���I�����̃��C�o���ʒu�i�h�b�g�j
typedef enum {
	ACT_ID_HERO,
	ACT_ID_HEROINE,
	ACT_ID_RIVAL,
	ACT_ID_BIRD,
	ACT_ID_KIRA,
	ACT_ID_MAX,
};

typedef struct OP_DEMO_OBJ_WORK_tag
{
	CLACT_SET_PTR 			ClactSet;								// �Z���A�N�^�[�Z�b�g
	CLACT_U_EASYRENDER_DATA	RendData;								// �ȈՃ����_�[�f�[�^
	CLACT_U_RES_MANAGER_PTR	ResMan[RESOURCE_NUM];				// ���\�[�X�}�l�[�W��
	CLACT_U_RES_OBJ_PTR 	ResObjTbl[ACT_ID_MAX][RESOURCE_NUM];		// ���\�[�X�I�u�W�F�e�[�u��
	CLACT_WORK_PTR			ClActWork[CLACT_WORK_MAX];				// �Z���A�N�^�[���[�N�|�C���^�z��
}OP_DEMO_OBJ_WORK;


//���\�[�X�}�l�[�W���[�o�^���e�[�u��
static const u8 ResEntryNumTbl[RESOURCE_NUM] = {
	ACT_ID_MAX,			//�L�������\�[�X
	ACT_ID_MAX,			//�p���b�g���\�[�X
	ACT_ID_MAX,			//�Z�����\�[�X
	ACT_ID_MAX,			//�Z���A�j�����\�[�X
};

//�A�N�^�[�h�c�ƃA�N�^�[���[�N�̑Ή��\
static int ActIDTbl[CLACT_WORK_MAX] = {
	ACT_ID_HERO,			//��l���j
	ACT_ID_HEROINE,			//��l����
	ACT_ID_RIVAL,			//���C�o��
	ACT_ID_BIRD,			//��
	ACT_ID_BIRD,			//��
	ACT_ID_BIRD,			//��
	ACT_ID_KIRA,			//�L���L��
};

static u16 BlackPalette[16] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

static fx32 BirdXSpeed1[3] = {
	(FX32_ONE/2)*12,(FX32_ONE/2)*11,(FX32_ONE/2)*10,
};

static fx32 BirdXSpeed2[3] = {
	(FX32_ONE/2)*8,(FX32_ONE/2)*10,(FX32_ONE/2)*11,
};

//-------------------------------------
//
//	�L�����N�^�}�l�[�W���[
//	�p���b�g�}�l�[�W���[�̏�����
//
//=====================================
static void OpdInitCharPlttManager()
{
	const int heapid = HEAPID_OP_DEMO;
	// �L�����N�^�}�l�[�W���[������
	{
		CHAR_MANAGER_MAKE cm = {
			OPD_CHAR_CONT_NUM,
			OPD_CHAR_VRAMTRANS_MAIN_SIZE,
			OPD_CHAR_VRAMTRANS_SUB_SIZE,
			heapid
		};
		InitCharManager(&cm);
	}
	// �p���b�g�}�l�[�W���[������
	InitPlttManager(OPD_PLTT_CONT_NUM, heapid);

	// �ǂݍ��݊J�n�ʒu��������
	CharLoadStartAll();
	PlttLoadStartAll();

}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�w�b�_�쐬
 *
 * @param	inActID		�o�^�h�c
 * @param	wk			�I�[�v�j���O�n�a�i�f�[�^�|�C���^
 * @param	outAdd		�A�N�^�[�w�b�_�i�[�ꏊ
 * 
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void MakeClActHeader(const int inActID, OPD_OBJ_PTR wk,
							const int inPriority,
							CLACT_ADD *outAdd, CLACT_HEADER *outClActHeader)
{
	// �Z���A�N�^�[�w�b�_�쐬	
	CLACT_U_MakeHeader(	outClActHeader,
						inActID, inActID, inActID, inActID,
						CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
						0, inPriority,
						wk->ResMan[CLACT_U_CHAR_RES],
						wk->ResMan[CLACT_U_PLTT_RES],
						wk->ResMan[CLACT_U_CELL_RES],
						wk->ResMan[CLACT_U_CELLANM_RES],
						NULL,NULL);

	{
		outAdd->ClActSet	= wk->ClactSet;
		outAdd->ClActHeader	= outClActHeader;

		outAdd->mat.x		= 0;//FX32_CONST(32) ;
		outAdd->mat.y		= 0;//FX32_CONST(96) ;		//��ʂ͏㉺�A�����Ă���
		outAdd->mat.z		= 0;
		outAdd->sca.x		= FX32_ONE;
		outAdd->sca.y		= FX32_ONE;
		outAdd->sca.z		= FX32_ONE;
		outAdd->rot			= 0;
		outAdd->pri			= 1;
		outAdd->DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		outAdd->heap		= HEAPID_OP_DEMO;
	}	
}

//--------------------------------------------------------------------------------------------
/**
 * �I�[�v�j���O�n�a�i�f�[�^�\���̃T�C�Y�擾�֐�
 *
 * @param	void
 *
 * @return	int		�T�C�Y
 */
//--------------------------------------------------------------------------------------------
const int OPD_Obj_GetWorkSize( void )
{
	return sizeof(OP_DEMO_OBJ_WORK);
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[������
 *
 * @param	wk	OBJ���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_InitCellActor( OPD_OBJ_PTR wk )
{
	int i;
	const int heapid = HEAPID_OP_DEMO;

	//�}�b�s���O���[�h�ݒ�
	GX_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);
	
	OpdInitCharPlttManager();
	// OAM�}�l�[�W���[�̏�����
	NNS_G2dInitOamManagerModule();

	// ���LOAM�}�l�[�W���쐬
	// �����_���pOAM�}�l�[�W���쐬
	REND_OAMInit( 
			0, 128,		// ���C�����OAM�Ǘ��̈�
			0, 32,		// ���C����ʃA�t�B���Ǘ��̈�
			0, 128,		// �T�u���OAM�Ǘ��̈�
			0, 32,		// �T�u��ʃA�t�B���Ǘ��̈�
			heapid);
	
	// �Z���A�N�^�[������
	wk->ClactSet = CLACT_U_SetEasyInit( OP_DEMO_ACT_MAX, &wk->RendData, heapid );
	
	//���\�[�X�}�l�[�W���[������
	for(i=0;i<RESOURCE_NUM;i++){		//���\�[�X�}�l�[�W���[�쐬
		wk->ResMan[i] = CLACT_U_ResManagerInit(ResEntryNumTbl[i], i, heapid);
	}

	//--chara�ǂݍ���
										
	//��l���@�j
	wk->ResObjTbl[ACT_ID_HERO][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
										wk->ResMan[CLACT_U_CHAR_RES],
										ARC_OP_DEMO, NARC_op_demo_title_hero_NCGR,
										FALSE, ACT_ID_HERO, NNS_G2D_VRAM_TYPE_2DMAIN, heapid);
	//��l���@��
	wk->ResObjTbl[ACT_ID_HEROINE][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
										wk->ResMan[CLACT_U_CHAR_RES],
										ARC_OP_DEMO, NARC_op_demo_title_heroine_NCGR,
										FALSE, ACT_ID_HEROINE, NNS_G2D_VRAM_TYPE_2DMAIN, heapid);
	//���C�o��
	wk->ResObjTbl[ACT_ID_RIVAL][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
										wk->ResMan[CLACT_U_CHAR_RES],
										ARC_OP_DEMO, NARC_op_demo_title_rivel_NCGR,
										FALSE, ACT_ID_RIVAL, NNS_G2D_VRAM_TYPE_2DMAIN, heapid);

	//��
	wk->ResObjTbl[ACT_ID_BIRD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
										wk->ResMan[CLACT_U_CHAR_RES],
										ARC_OP_DEMO, NARC_op_demo_title_bird_NCGR,
										FALSE, ACT_ID_BIRD, NNS_G2D_VRAM_TYPE_2DMAIN, heapid);

	//�L���L��
	wk->ResObjTbl[ACT_ID_KIRA][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
										wk->ResMan[CLACT_U_CHAR_RES],
										ARC_OP_DEMO, NARC_op_demo_logo_kira_NCGR,
										FALSE, ACT_ID_KIRA, NNS_G2D_VRAM_TYPE_2DSUB, heapid);	
	//--pal�ǂݍ���

	//��l���@�j
	wk->ResObjTbl[ACT_ID_HERO][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
										wk->ResMan[CLACT_U_PLTT_RES],
										ARC_OP_DEMO, NARC_op_demo_title_hero_NCLR,
										FALSE, ACT_ID_HERO, NNS_G2D_VRAM_TYPE_2DMAIN, PALETTE_NUM, heapid);
	//��l���@��
	wk->ResObjTbl[ACT_ID_HEROINE][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
										wk->ResMan[CLACT_U_PLTT_RES],
										ARC_OP_DEMO, NARC_op_demo_title_heroine_NCLR,
										FALSE, ACT_ID_HEROINE, NNS_G2D_VRAM_TYPE_2DMAIN, PALETTE_NUM, heapid);
	//���C�o��
	wk->ResObjTbl[ACT_ID_RIVAL][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
										wk->ResMan[CLACT_U_PLTT_RES],
										ARC_OP_DEMO, NARC_op_demo_title_rivel_NCLR,
										FALSE, ACT_ID_RIVAL, NNS_G2D_VRAM_TYPE_2DMAIN, PALETTE_NUM, heapid);

	//��
	wk->ResObjTbl[ACT_ID_BIRD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
										wk->ResMan[CLACT_U_PLTT_RES],
										ARC_OP_DEMO, NARC_op_demo_title_bird_NCLR,
										FALSE, ACT_ID_BIRD, NNS_G2D_VRAM_TYPE_2DMAIN, PALETTE_NUM, heapid);

	//�L���L��
	wk->ResObjTbl[ACT_ID_KIRA][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
										wk->ResMan[CLACT_U_PLTT_RES],
										ARC_OP_DEMO, NARC_op_demo_logo_kira_NCLR,
										FALSE, ACT_ID_KIRA, NNS_G2D_VRAM_TYPE_2DSUB, PALETTE_NUM, heapid);
	//--cell�ǂݍ���
										
	//��l���@�j
	wk->ResObjTbl[ACT_ID_HERO][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELL_RES],
										ARC_OP_DEMO, NARC_op_demo_title_hero_NCER,
										FALSE, ACT_ID_HERO, CLACT_U_CELL_RES, heapid);
	//��l���@��
	wk->ResObjTbl[ACT_ID_HEROINE][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELL_RES],
										ARC_OP_DEMO, NARC_op_demo_title_heroine_NCER,
										FALSE, ACT_ID_HEROINE, CLACT_U_CELL_RES, heapid);
	//���C�o��
	wk->ResObjTbl[ACT_ID_RIVAL][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELL_RES],
										ARC_OP_DEMO, NARC_op_demo_title_rivel_NCER,
										FALSE, ACT_ID_RIVAL, CLACT_U_CELL_RES, heapid);

	//��
	wk->ResObjTbl[ACT_ID_BIRD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELL_RES],
										ARC_OP_DEMO, NARC_op_demo_title_bird_NCER,
										FALSE, ACT_ID_BIRD, CLACT_U_CELL_RES, heapid);

	//�L���L��
	wk->ResObjTbl[ACT_ID_KIRA][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELL_RES],
										ARC_OP_DEMO, NARC_op_demo_logo_kira_NCER,
										FALSE, ACT_ID_KIRA, CLACT_U_CELL_RES, heapid);
	//--�����֐���anim�ǂݍ���
										
	//��l���@�j
	wk->ResObjTbl[ACT_ID_HERO][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELLANM_RES],
										ARC_OP_DEMO, NARC_op_demo_title_hero_NANR,
										FALSE, ACT_ID_HERO, CLACT_U_CELLANM_RES, heapid);
	//��l���@��
	wk->ResObjTbl[ACT_ID_HEROINE][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELLANM_RES],
										ARC_OP_DEMO, NARC_op_demo_title_heroine_NANR,
										FALSE, ACT_ID_HEROINE, CLACT_U_CELLANM_RES, heapid);
	//���C�o��
	wk->ResObjTbl[ACT_ID_RIVAL][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELLANM_RES],
										ARC_OP_DEMO, NARC_op_demo_title_rivel_NANR,
										FALSE, ACT_ID_RIVAL, CLACT_U_CELLANM_RES, heapid);

	//��
	wk->ResObjTbl[ACT_ID_BIRD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELLANM_RES],
										ARC_OP_DEMO, NARC_op_demo_title_bird_NANR,
										FALSE, ACT_ID_BIRD, CLACT_U_CELLANM_RES, heapid);

	//�L���L��
	wk->ResObjTbl[ACT_ID_KIRA][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELLANM_RES],
										ARC_OP_DEMO, NARC_op_demo_logo_kira_NANR,
										FALSE, ACT_ID_KIRA, CLACT_U_CELLANM_RES, heapid);
	
	// ���\�[�X�}�l�[�W���[����]��

	for (i=0;i<ACT_ID_MAX;i++){
		// Chara�]��
		CLACT_U_CharManagerSet( wk->ResObjTbl[i][CLACT_U_CHAR_RES] );
		// �p���b�g�]��
		CLACT_U_PlttManagerSet( wk->ResObjTbl[i][CLACT_U_PLTT_RES] );
	}

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );		// MAIN DISP OBJ ON
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[���I��
 *
 * @param	wk	OBJ���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_EndCellActor( OPD_OBJ_PTR wk )
{
	u8 i;
	// �Z���A�N�^�[���\�[�X���

	for (i=0;i<ACT_ID_MAX;i++){
		// �L�����]���}�l�[�W���[�j��
		CLACT_U_CharManagerDelete(wk->ResObjTbl[i][CLACT_U_CHAR_RES]);
		// �p���b�g�]���}�l�[�W���[�j��
		CLACT_U_PlttManagerDelete(wk->ResObjTbl[i][CLACT_U_PLTT_RES]);
	}
	
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
 * �Z���A�N�^�[���Z�b�g
 *
 * @param	wk	OBJ���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_SetActor( OPD_OBJ_PTR wk )
{
	int i;
	CLACT_HEADER			cl_act_header;
	CLACT_ADD add;

	const int bird_act[BIRD_ACT_MAX] = {
		ACT_WORK_BIRD_1,
		ACT_WORK_BIRD_2,
		ACT_WORK_BIRD_3,
		ACT_WORK_BIRD_4,
		ACT_WORK_BIRD_5,
		ACT_WORK_BIRD_6,
	};

	const int bird_pos_x[BIRD_ACT_MAX] = {
		BIRD_1_POS_X,
		BIRD_2_POS_X,
		BIRD_3_POS_X,
		BIRD_4_POS_X,
		BIRD_5_POS_X,
		BIRD_6_POS_X,
	};

	const int bird_pos_y[BIRD_ACT_MAX] = {
		BIRD_1_POS_Y,
		BIRD_2_POS_Y,
		BIRD_3_POS_Y,
		BIRD_4_POS_Y,
		BIRD_5_POS_Y,
		BIRD_6_POS_Y,
	};

	{
		//�Z���A�N�^�[�\���J�n
		// �����(���C�����)
		
		//��l���@�j
		MakeClActHeader( ACT_ID_HERO, wk, 1, &add, &cl_act_header );
		add.mat.x = FX32_ONE * HERO_POS_X;
		add.mat.y = FX32_ONE * HERO_POS_Y;
		wk->ClActWork[ACT_WORK_HERO] = CLACT_Add(&add);
		CLACT_SetAnmFlag(wk->ClActWork[ACT_WORK_HERO],0);
		CLACT_SetDrawFlag(wk->ClActWork[ACT_WORK_HERO], 0);	//��\��
		
		//��l���@��
		MakeClActHeader( ACT_ID_HEROINE, wk, 1, &add, &cl_act_header );
		add.mat.x = FX32_ONE * HERO_POS_X/*HEROINE_POS_X*/;
		add.mat.y = FX32_ONE * HERO_POS_Y/*HEROINE_POS_Y*/;
		wk->ClActWork[ACT_WORK_HEROINE] = CLACT_Add(&add);
		CLACT_SetAnmFlag(wk->ClActWork[ACT_WORK_HEROINE],0);
		CLACT_SetDrawFlag(wk->ClActWork[ACT_WORK_HEROINE], 0);	//��\��

		//��l���A�j��
		OPD_Obj_ChangeHeroHeroineAnime(wk, 3);
		
		//���C�o��
		MakeClActHeader( ACT_ID_RIVAL, wk, 1, &add, &cl_act_header );
		add.mat.x = FX32_ONE * RIVAL_POS_X;
		add.mat.y = FX32_ONE * RIVAL_POS_Y;
		wk->ClActWork[ACT_WORK_RIVAL] = CLACT_Add(&add);
		CLACT_SetAnmFlag(wk->ClActWork[ACT_WORK_RIVAL],1);
		CLACT_SetDrawFlag(wk->ClActWork[ACT_WORK_RIVAL], 0);	//��\��

		//��
		for(i=0;i<BIRD_ACT_MAX;i++){
			MakeClActHeader( ACT_ID_BIRD, wk, 0, &add, &cl_act_header );
			add.mat.x = FX32_ONE * bird_pos_x[i];
			add.mat.y = FX32_ONE * bird_pos_y[i];
			wk->ClActWork[ bird_act[i] ] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->ClActWork[ bird_act[i] ],1);
			CLACT_SetDrawFlag(wk->ClActWork[ bird_act[i] ], 1);	//��\��
		}
	}	
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[���Z�b�g(�L���L��)
 *
 * @param	wk		OBJ���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_SetKiraActor( OPD_OBJ_PTR wk, OPD_KIRA_DATLST_PTR pKiraDataListPtr )
{
	int i;
	CLACT_HEADER			cl_act_header;
	CLACT_ADD add;

	CLACT_WORK_PTR *act_work;

	{
		//�Z���A�N�^�[�\���J�n
		// ����(�T�u���)
		
		//�L���L��
		MakeClActHeader( ACT_ID_KIRA, wk, 0, &add, &cl_act_header);
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;

		for (i=0;i<KIRA_ACT_MAX;i++){
///			add.mat.x = FX32_ONE * (gf_rand()%256);
///			add.mat.y = FX32_ONE * (192+gf_rand()%192);
			
			act_work = OPDKira_GetActWorkPtrFromList( pKiraDataListPtr, i );
			(*act_work) = CLACT_Add(&add);
			CLACT_SetAnmFlag(*act_work,0);
			CLACT_SetDrawFlag(*act_work, 0);	//��\��
		}
	}	
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�`��
 *
 * @param	wk	OBJ���[�N	
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_DrawActor( OPD_OBJ_PTR wk )
{
	CLACT_Draw( wk->ClactSet );
}

//--------------------------------------------------------------------------------------------
/**
 * OBJ�̕\���E��\��
 *
 * @param	wk				OBJ���[�N
 * @param	inActWorkNo		�A�N�^�[���[�N�i���o�[
 * @param	inFlg			�\���t���O
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_DispOnOff( OPD_OBJ_PTR wk, const u8 inActWorkNo, const u8 inFlg )
{
	CLACT_SetDrawFlag(wk->ClActWork[inActWorkNo], inFlg);
}

//--------------------------------------------------------------------------------------------
/**
 * OBJ�̈ʒu�ύX
 *
 * @param	wk				OBJ���[�N
 * @param	inActWorkNo		�A�N�^�[���[�N�i���o�[
 * @param	inFlg			�\���t���O
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_ChangePos( OPD_OBJ_PTR wk, const u8 inActWorkNo, const int inX, const int inY )
{
	VecFx32 vec;
	
	vec =  *CLACT_GetMatrix( wk->ClActWork[inActWorkNo] );
	vec.x = inX;
	vec.y = inY;
	CLACT_SetMatrix( wk->ClActWork[inActWorkNo], &vec );
}

//--------------------------------------------------------------------------------------------
/**
 * �q���C��OBJ�̈ʒu�ύX
 *
 * @param	wk				OBJ���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_ChangeHeroinePos( OPD_OBJ_PTR wk )
{
	OPD_Obj_ChangePos( wk, ACT_WORK_HEROINE, FX32_ONE*HEROINE_POS_X, FX32_ONE*HEROINE_POS_Y );
}

//--------------------------------------------------------------------------------------------
/**
 * �q�[���[�E�q���C��OBJ�̃A�j���ύX
 *
 * @param	wk				OBJ���[�N
 * @param	inNo			�A�j���i���o�[
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_ChangeHeroHeroineAnime( OPD_OBJ_PTR wk, const u8 inNo )
{
	CLACT_AnmChg( wk->ClActWork[ACT_WORK_HERO], inNo );
	CLACT_AnmChg( wk->ClActWork[ACT_WORK_HEROINE], inNo );
}

//--------------------------------------------------------------------------------------------
/**
 * �q�[���[�E�q���C��OBJ�̃A�j���J�n�E��~
 *
 * @param	wk				OBJ���[�N
 * @param	inNo			�A�j���i���o�[
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_OnOffHeroHeroineAnime( OPD_OBJ_PTR wk, const u8 inAnime )
{
	CLACT_SetAnmFlag(wk->ClActWork[ACT_WORK_HERO],inAnime);
	CLACT_SetAnmFlag(wk->ClActWork[ACT_WORK_HEROINE],inAnime);
}

//--------------------------------------------------------------------------------------------
/**
 * ���C�o���X���C�h�C��
 *
 * @param	wk	OBJ���[�N	
 *
 * @return	BOOL	TRUE�ŃX���C�h�I��
 */
//--------------------------------------------------------------------------------------------
BOOL OPD_Obj_SlideInRival(OPD_OBJ_PTR wk)
{
	VecFx32 vec;
	
	vec =  *CLACT_GetMatrix( wk->ClActWork[ACT_WORK_RIVAL] );
	vec.x -= RIVAL_SLIDE_SPEED;

	if (vec.x <= RIVAL_POS_END_X){
		vec.x = RIVAL_POS_END_X;
		CLACT_SetMatrix( wk->ClActWork[ACT_WORK_RIVAL], &vec );
		return TRUE;
	}
	CLACT_SetMatrix( wk->ClActWork[ACT_WORK_RIVAL], &vec );
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * OBJ�̐F�ύX�i����==�����̐F�j
 *
 * @param	wk				OBJ���[�N
 * @param	inActWorkNo		�A�N�^�[���[�N�i���o�[
 * @param	inColChgMode	�F�ύX���[�h
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPD_Obj_ChangeCollor(OPD_OBJ_PTR wk, const int inActWorkNo, const u8 inColChgMode)
{
	NNSG2dImagePaletteProxy *proxy = CLACT_PaletteProxyGet( wk->ClActWork[inActWorkNo] );
	u32 palette_vram = NNS_G2dGetImagePaletteLocation( proxy, NNS_G2D_VRAM_TYPE_2DMAIN );
	if (inColChgMode == CHG_MODE_BLACK){	
		GX_LoadOBJPltt( BlackPalette, palette_vram, 16*2 );	//32byte 1Palette
	}else{
		NNSG2dPaletteData *data;
		data = CLACT_U_ResManagerGetResObjResPltt(wk->ResObjTbl[ ActIDTbl[inActWorkNo] ][CLACT_U_PLTT_RES]);
		GX_LoadOBJPltt( data->pRawData, palette_vram, 16*2 );	//32byte 1Palette
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ���X���C�h�C��
 *
 * @param	wk				OBJ���[�N
 * @param	inCounter		�t���[���J�E���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void  OPD_Obj_SlideInBird(OPD_OBJ_PTR wk, const int inCounter)
{	
	u8 i;
	VecFx32 vec;

	const int bird_act1[3] = {
		ACT_WORK_BIRD_1,
		ACT_WORK_BIRD_2,
		ACT_WORK_BIRD_3,
	};
	const int bird_act2[3] = {
		ACT_WORK_BIRD_4,
		ACT_WORK_BIRD_5,
		ACT_WORK_BIRD_6,
	};

	if (inCounter >= FM_BIRD_IN_1){
		for (i=0;i<3;i++){
			vec =  *CLACT_GetMatrix( wk->ClActWork[ bird_act1[i] ] );
			vec.x -= BirdXSpeed1[i];
			vec.y -= (FX32_ONE*4);
			CLACT_SetMatrix( wk->ClActWork[ bird_act1[i] ], &vec );
		}
	}

	if (inCounter >= FM_BIRD_IN_2){
		for (i=0;i<3;i++){
			vec =  *CLACT_GetMatrix( wk->ClActWork[ bird_act2[i] ] );
			vec.x -= BirdXSpeed2[i];
			vec.y -= (FX32_ONE*4);
			CLACT_SetMatrix( wk->ClActWork[ bird_act2[i] ], &vec );
		}
	}
}
