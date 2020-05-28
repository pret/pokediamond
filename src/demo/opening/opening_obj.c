//==============================================================================================
/**
 * @file	opneing_obj.c
 * @brief	�I�[�v�j���O OBJ
 * @author	Satoshi Nohara
 * @date	2005.12.08
 */
//==============================================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "opening.naix"
#include "opening_obj.h"


//==============================================================================================
//
//	��`
//
//==============================================================================================
//�L�����N�^�[�}�l�[�W���[
#define OP_CHAR_CONT_NUM					(2)
#define OP_CHAR_VRAMTRANS_MAIN_SIZE			(2048)
#define OP_CHAR_VRAMTRANS_SUB_SIZE			(0)

//�p���b�g�}�l�[�W���[
//#define OP_PLTT_CONT_NUM					(2)						//�Ǘ��p���b�g��
#define OP_PLTT_CONT_NUM					(3)						//�Ǘ��p���b�g��


//==============================================================================================
//
//	�\���̐錾
//
//==============================================================================================
typedef struct _POS_tag{
	int x;
	int y;
}_POS;


//==============================================================================================
//
//	�f�[�^
//
//==============================================================================================
//���\�[�X�^�C�v�񋓂ɍ��킹��(include/system/clact_util_res.h)
//���\�[�X�}�l�[�W���[�o�^���e�[�u��
static const u8 ResEntryNumTbl[RESOURCE_NUM] = {
	2,			//�L�������\�[�X
	3,			//�p���b�g���\�[�X
	2,			//�Z�����\�[�X
	2,			//�Z���A�j�����\�[�X
};

static const _POS obj_pos[] = {
	{86,30},	//�I�[�L�h
	//{86,30},	//���C�o��
	{86,46},	//���C�o��
	{92,96},	//�e
};


//==============================================================================================
//
//	�v���g�^�C�v�錾
//
//==============================================================================================
void OpeningInitCellActor( OPENING_OBJ_WORK *wk );
void OpeningSetActor( OPENING_OBJ_WORK *wk, u32 index, u32 data_no, u32 anm_no );
static void OpeningInitCharPlttManager( void );
void OpeningRereaseCellObject( OPENING_OBJ_WORK *wk );
void OpeningClactVanish(OPENING_OBJ_WORK *wk, int no, int flag);
VecFx32 OpeningClactMove(OPENING_OBJ_WORK *wk, int no, int spd);
void OpeningClactMoveInit(OPENING_OBJ_WORK *wk, int no );
void OpeningClactPosSet(OPENING_OBJ_WORK *wk, int no, int x, int y );


//==============================================================================================
//
//	�֐�
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�Z���A�N�^�[������
 *
 * @param	wk		OPENING_OBJ_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningInitCellActor( OPENING_OBJ_WORK *wk )
{
	int i;

	OpeningInitCharPlttManager();

	//OAM�}�l�[�W���[�̏�����
	NNS_G2dInitOamManagerModule();

	//���LOAM�}�l�[�W���쐬
	//�����_���pOAM�}�l�[�W���쐬
	//�����ō쐬����OAM�}�l�[�W�����݂�Ȃŋ��L����
	REND_OAMInit( 
			0, 128,				//���C�����OAM�Ǘ��̈�
			0, 32,				//���C����ʃA�t�B���Ǘ��̈�
			0, 128,				//�T�u���OAM�Ǘ��̈�
			0, 32,				//�T�u��ʃA�t�B���Ǘ��̈�
			HEAPID_OPENING);
	
	//�Z���A�N�^�[�Z�b�g�̊ȒP������(�쐬���ꂽ�Z���A�N�^�[�Z�b�g���Ԃ�)
	wk->ClactSet = CLACT_U_SetEasyInit( OPENING_ACT_MAX, &wk->RendData, HEAPID_OPENING );
	
	//���\�[�X�}�l�[�W���[������
	for(i=0;i<RESOURCE_NUM;i++){		//���\�[�X�}�l�[�W���[�쐬
		wk->ResMan[i] = CLACT_U_ResManagerInit(ResEntryNumTbl[i], i, HEAPID_OPENING);
	}

	/***************/
	//	�n�J�Z	
	/***************/
	//chara�ǂݍ���
//	wk->ResObjTbl[OP_RES_OBJ_HAKASE][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
//					wk->ResMan[CLACT_U_CHAR_RES],
//					ARC_OPENING_GRA, NARC_opening_op_hakase_NCGR,
//					FALSE, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_OPENING);

	//pal�ǂݍ���
	wk->ResObjTbl[OP_RES_OBJ_HAKASE][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
					wk->ResMan[CLACT_U_PLTT_RES],
					ARC_OPENING_GRA, NARC_opening_op_hakase_NCLR,
					FALSE, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 2, HEAPID_OPENING);

	//cell�ǂݍ���
	wk->ResObjTbl[OP_RES_OBJ_HAKASE][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
					wk->ResMan[CLACT_U_CELL_RES],
					ARC_OPENING_GRA, NARC_opening_op_hakase_NCER,
					FALSE, 0, CLACT_U_CELL_RES, HEAPID_OPENING);

	//�����֐���anim�ǂݍ���
	wk->ResObjTbl[OP_RES_OBJ_HAKASE][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
					wk->ResMan[CLACT_U_CELLANM_RES],
					ARC_OPENING_GRA, NARC_opening_op_hakase_NANR,
					FALSE, 0, CLACT_U_CELLANM_RES, HEAPID_OPENING);

	/***************/
	//	���C�o��
	/***************/
	//chara�ǂݍ���
//	wk->ResObjTbl[OP_RES_OBJ_RIVAL][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
//					wk->ResMan[CLACT_U_CHAR_RES],
//					ARC_OPENING_GRA, NARC_opening_op_rival_NCGR,
//					FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_OPENING);

	//pal�ǂݍ���
	wk->ResObjTbl[OP_RES_OBJ_RIVAL][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
					wk->ResMan[CLACT_U_PLTT_RES],
					ARC_OPENING_GRA, NARC_opening_op_rival_NCLR,
					FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 1, HEAPID_OPENING);

	//cell�ǂݍ���
	wk->ResObjTbl[OP_RES_OBJ_RIVAL][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
					wk->ResMan[CLACT_U_CELL_RES],
					ARC_OPENING_GRA, NARC_opening_op_rival_NCER,
					FALSE, 1, CLACT_U_CELL_RES, HEAPID_OPENING);

	//�����֐���anim�ǂݍ���
	wk->ResObjTbl[OP_RES_OBJ_RIVAL][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
					wk->ResMan[CLACT_U_CELLANM_RES],
					ARC_OPENING_GRA, NARC_opening_op_rival_NANR,
					FALSE, 1, CLACT_U_CELLANM_RES, HEAPID_OPENING);
	
	//���\�[�X�}�l�[�W���[����]��
	for( i=0; i < OP_RES_OBJ_MAX ;i++ ){
		CLACT_U_CharManagerSet( wk->ResObjTbl[i][CLACT_U_CHAR_RES] );	//Chara�]��
		CLACT_U_PlttManagerSet( wk->ResObjTbl[i][CLACT_U_PLTT_RES] );	//�p���b�g�]��
	}

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );			//MAIN DISP OBJ ON

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�Z���A�N�^�[���Z�b�g
 *
 * @param	wk		OPENING_OBJ_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningSetActor( OPENING_OBJ_WORK *wk, u32 index, u32 data_no, u32 anm_no )
{
	int i;
	CLACT_HEADER			cl_act_header;
	
	// �Z���A�N�^�[�w�b�_�쐬	
	CLACT_U_MakeHeader(	&cl_act_header,
						data_no, data_no, data_no, data_no,
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
		add.mat.y		= 0;//FX32_CONST(96) ;		//��ʂ͏㉺�A�����Ă���iMAIN����ASUB�����j
		add.mat.z		= 0;
		add.sca.x		= FX32_ONE;
		add.sca.y		= FX32_ONE;
		add.sca.z		= FX32_ONE;
		add.rot			= 0;
		add.pri			= 2;
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		add.heap		= HEAPID_OPENING;

		//�Z���A�N�^�[�\���J�n

		add.mat.x = FX32_ONE * obj_pos[index].x;
		add.mat.y = FX32_ONE * obj_pos[index].y;
		wk->ClActWork[index] = CLACT_Add(&add);
		CLACT_SetAnmFlag( wk->ClActWork[index], 0 );
		CLACT_AnmChg( wk->ClActWork[index], anm_no );
	}	
}

//--------------------------------------------------------------
/**
 * @brief	�L�����N�^�[�E�p���b�g�}�l�[�W���[������
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void OpeningInitCharPlttManager(void)
{
	//�L�����N�^�}�l�[�W���[������
	{
		CHAR_MANAGER_MAKE cm = {
			OP_CHAR_CONT_NUM,					//�L�����N�^���䐔
			OP_CHAR_VRAMTRANS_MAIN_SIZE,		//���C����ʂ�Vram�]���p�ɗp�ӂ���Vram�T�C�Y
			OP_CHAR_VRAMTRANS_SUB_SIZE,			//�T�u��ʂ�Vram�]���p�ɗp�ӂ���Vram�T�C�Y
			HEAPID_OPENING						//�g�p����q�[�v
		};
		InitCharManager(&cm);
	}

	//�p���b�g�}�l�[�W���[������
	InitPlttManager( OP_PLTT_CONT_NUM, HEAPID_OPENING );

	//�ǂݍ��݊J�n�ʒu��������
	CharLoadStartAll();
	PlttLoadStartAll();

	return;
}

//--------------------------------------------------------------
/**
 * @brief	2D�Z���I�u�W�F�N�g���
 *
 * @param	wk		OPENING_OBJ_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningRereaseCellObject(OPENING_OBJ_WORK *wk)
{
	u8 i;

	//�Z���A�N�^�[���\�[�X���
	for( i=0; i < OP_RES_OBJ_MAX ;i++ ){
		CLACT_U_CharManagerDelete( wk->ResObjTbl[i][CLACT_U_CHAR_RES] );//char�]���}�l�[�W���[�j��
		CLACT_U_PlttManagerDelete( wk->ResObjTbl[i][CLACT_U_PLTT_RES] );//pltt�]���}�l�[�W���[�j��
	}
		
	//�L�����E�p���b�g�E�Z���E�Z���A�j���̃��\�[�X�}�l�[�W���[�j��
	for( i=0; i < RESOURCE_NUM ;i++ ){
		CLACT_U_ResManagerDelete( wk->ResMan[i] );
	}

	//�Z���A�N�^�[�Z�b�g�j��
	CLACT_DestSet(wk->ClactSet);

	//OAM�����_���[�j��
	REND_OAM_Delete();

	DeleteCharManager();
	DeletePlttManager();

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�o�j�b�V������
 *
 * @param	wk		OPENING_OBJ_WORK�^�̃|�C���^
 * @param	flag	�`��t���O	0:��`��	1:�����_���`��	
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningClactVanish(OPENING_OBJ_WORK *wk, int no, int flag)
{
	CLACT_SetDrawFlag( wk->ClActWork[no], flag );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�ړ�
 *
 * @param	wk		OPENING_OBJ_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
VecFx32 OpeningClactMove(OPENING_OBJ_WORK *wk, int no, int spd)
{
	VecFx32	vec;

	vec = *( CLACT_GetMatrix(wk->ClActWork[no]) );
	vec.x += (spd * FX32_ONE);
	CLACT_SetMatrix( wk->ClActWork[no], &vec );
	return *( CLACT_GetMatrix(wk->ClActWork[no]) );
}

//--------------------------------------------------------------
/**
 * @brief	�������W�Z�b�g
 *
 * @param	wk		OPENING_OBJ_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningClactMoveInit(OPENING_OBJ_WORK *wk, int no )
{
	VecFx32	vec;

	vec.x = (obj_pos[no].x * FX32_ONE);
	vec.y = (obj_pos[no].y * FX32_ONE);
	CLACT_SetMatrix( wk->ClActWork[no], &vec );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	���W�Z�b�g
 *
 * @param	wk		OPENING_OBJ_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningClactPosSet(OPENING_OBJ_WORK *wk, int no, int x, int y )
{
	VecFx32	vec;

	vec.x = (x * FX32_ONE);
	vec.y = (y * FX32_ONE);
	CLACT_SetMatrix( wk->ClActWork[no], &vec );
	return;
}


