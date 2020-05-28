//=============================================================================
/**
 * @file	opening_kira_obj.c
 * @brief	�I�[�v�j���O�f���n�a�i
 * @author	Nozomu Saito
 * @date    2006.06.03
 */
//=============================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "op_demo.naix"
#include "opening_kira_obj.h"

#include "op_frame_def.h"

#define RESOURCE_NUM	(4)
#define OPD_KIRA_ACT_MAX	(10)
#define GENERATER_MAX	(3)
#define PALETTE_NUM	(1)		//�p���b�g�P�{

enum {
	ACT_ID_KIRA,
	ACT_ID_MAX,
};

enum {
	GENE_TYPE_FIRST,
	GENE_TYPE_SEC
};

#define OPD_KIRA_CHAR_CONT_NUM				(ACT_ID_MAX)
#define OPD_KIRA_CHAR_VRAMTRANS_MAIN_SIZE	(0)
#define OPD_KIRA_CHAR_VRAMTRANS_SUB_SIZE	(0)
#define OPD_KIRA_PLTT_CONT_NUM				(ACT_ID_MAX)

#define OPD_KIRA_X_BASE		(64)
#define OPD_KIRA_Y_BASE1	(64)
#define OPD_KIRA_Y_BASE2	(32)
#define OPD_KIRA_W	(128)
#define OPD_KIRA_H	(64)

#define KIRA_MOVE_MAX	(80)

#define OPD_KIRA2_X_BASE	(16-6)
#define OPD_KIRA2_Y_BASE	(64-6)
#define OPD_KIRA2_W	(224)
#define OPD_KIRA2_H	(56)
#define SCENE2_KIRA_MOVE_MAX	(8)


typedef struct OPD_KIRA_DATA_tag
{
	u8 Valid;		//�f�[�^�L���t���O
	u8 MoveCounter; //����J�E���^
	CLACT_WORK_PTR ActWorkPtr;
	TCB_PTR	Tcb;		//����^�X�N�|�C���^
}OPD_KIRA_DATA;

typedef struct OPD_KIRA_DATA_LIST_tag
{
	int Num;
	OPD_KIRA_DATA *Data;
}OPD_KIRA_DATA_LIST;

typedef struct KIRA_GENERATE_PARAM_tag
{
	u8 Num;
	u8 Margin;
	u8 LoopMax;
	u8 Loop;
	u8 Count;
	u8 Type;
	u8 dummy[2];
}KIRA_GENERATE_PARAM;

typedef struct OPD_KIRA_GENERATER_tag
{
	KIRA_GENERATE_PARAM GeneParam;
	TCB_PTR GeneTcb;
	OPD_KIRA_DATA *KiraDataListPtr;	//�}�l�[�W���̎��L���f�[�^�̃|�C���^
}OPD_KIRA_GENERATER;

typedef struct OP_DEMO_OBJ_WORK_tag
{
	CLACT_SET_PTR 			ClactSet;								// �Z���A�N�^�[�Z�b�g
	CLACT_U_EASYRENDER_DATA	RendData;								// �ȈՃ����_�[�f�[�^
	CLACT_U_RES_MANAGER_PTR	ResMan[RESOURCE_NUM];				// ���\�[�X�}�l�[�W��
	CLACT_U_RES_OBJ_PTR 	ResObjTbl[RESOURCE_NUM];		// ���\�[�X�I�u�W�F�e�[�u��
	OPD_KIRA_DATA KiraData[OPD_KIRA_ACT_MAX];
}OPD_KIRA_OBJ_WORK;

typedef struct OPD_KIRA_GENERATE_MNG_tag
{
	OPD_KIRA_OBJ_WORK KiraObjWork;					//�L���R���g���[�����[�N
	OPD_KIRA_GENERATER Generater[GENERATER_MAX];	//�W�F�l���[�^�[��
}OPD_KIRA_GENERATE_MNG;

//=========================================================================================
static void InitCellActor( OPD_KIRA_OBJ_WORK *wk );
static void EndCellActor( OPD_KIRA_OBJ_WORK *wk );
static void SetActor( OPD_KIRA_OBJ_WORK *wk );
static void DrawActor( OPD_KIRA_OBJ_WORK *wk );

static void CreateKiraGenerater(OPD_KIRA_GENERATER *pGenerater, OPD_K_G_MNG_PTR ptr, 
								const u8 inNum, const u8 inMargin, const u8 inLoop,
								const u8 inType);
static void TCB_GenerateFunc( TCB_PTR tcb, void* work );
static OPD_KIRA_DATA *GetInvalidKiraData(OPD_KIRA_DATA *pKiraDataList, const int inMax);
static void TCB_KiraFunc( TCB_PTR tcb, void* work );

static void Scene2_GenerateKira( OPD_KIRA_DATLST_PTR pKiraDataListPtr, const u8 inNum);
static void TCB_Scene2KiraFunc( TCB_PTR tcb, void* work );

//���\�[�X�}�l�[�W���[�o�^���e�[�u��
static const u8 ResEntryNumTbl[RESOURCE_NUM] = {
	ACT_ID_MAX,			//�L�������\�[�X
	ACT_ID_MAX,			//�p���b�g���\�[�X
	ACT_ID_MAX,			//�Z�����\�[�X
	ACT_ID_MAX,			//�Z���A�j�����\�[�X
};

//-------------------------------------
//
//	�L�����N�^�}�l�[�W���[
//	�p���b�g�}�l�[�W���[�̏�����
//
//=====================================
static void OpdKira_InitCharPlttManager()
{
	const int heapid = HEAPID_OP_DEMO;
	// �L�����N�^�}�l�[�W���[������
	{
		CHAR_MANAGER_MAKE cm = {
			OPD_KIRA_CHAR_CONT_NUM,
			OPD_KIRA_CHAR_VRAMTRANS_MAIN_SIZE,
			OPD_KIRA_CHAR_VRAMTRANS_SUB_SIZE,
			heapid
		};
		InitCharManager(&cm);
	}
	// �p���b�g�}�l�[�W���[������
	InitPlttManager(OPD_KIRA_PLTT_CONT_NUM, heapid);

	// �ǂݍ��݊J�n�ʒu��������
	CharLoadStartAll();
	PlttLoadStartAll();

}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�w�b�_�쐬
 *
 * @param	wk				�I�[�v�j���O�n�a�i�f�[�^�|�C���^
 * @param	outAdd			�A�N�^�[�w�b�_�i�[�ꏊ
 * @param	outClActHeader	�A�N�^�[�w�b�_�[�|�C���^
 * 
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void MakeClActHeader( OPD_KIRA_OBJ_WORK *wk,
								CLACT_ADD *outAdd, CLACT_HEADER *outClActHeader  )
{
	// �Z���A�N�^�[�w�b�_�쐬	
	CLACT_U_MakeHeader(	outClActHeader,
						ACT_ID_KIRA, ACT_ID_KIRA, ACT_ID_KIRA, ACT_ID_KIRA,
						CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
						0, 0,
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
 * �W�F�l���[�^�[�}�l�[�W���f�[�^�쐬�֐�
 *
 * @param	void
 *
 * @return	int		�T�C�Y
 */
//--------------------------------------------------------------------------------------------
OPD_K_G_MNG_PTR OPDKira_AllocGeneMng( void )
{
	int size = sizeof(OPD_KIRA_GENERATE_MNG);
	OPD_K_G_MNG_PTR ptr = sys_AllocMemory(HEAPID_OP_DEMO, size);
	memset(ptr, 0, size);
	
	InitCellActor( &ptr->KiraObjWork );
	SetActor( &ptr->KiraObjWork );
	return ptr;
}

//--------------------------------------------------------------------------------------------
/**
 * �L���f�[�^���X�g�A���P�[�V����
 *
 * @param	inNum		�m�ې�
 *
 * @return	OPD_KIRA_DATLST_PTR	���X�g�|�C���^
 */
//--------------------------------------------------------------------------------------------
OPD_KIRA_DATLST_PTR OPDKira_CreateList(const int inNum)
{
	int data_size;
	OPD_KIRA_DATLST_PTR lst_ptr;
	lst_ptr = sys_AllocMemory(HEAPID_OP_DEMO, sizeof(OPD_KIRA_DATA_LIST));
	data_size = sizeof(OPD_KIRA_DATA)*inNum;
	lst_ptr->Data = sys_AllocMemory( HEAPID_OP_DEMO, data_size );
	memset(lst_ptr->Data , 0, data_size);
	lst_ptr->Num = inNum;

	return lst_ptr;
}

//--------------------------------------------------------------------------------------------
/**
 * �L���f�[�^���X�g���
 *
 * @param	
 *
 * @return	OPD_KIRA_DATLST_PTR	���X�g�|�C���^
 */
//--------------------------------------------------------------------------------------------
void OPDKira_FreeList(OPD_KIRA_DATLST_PTR pKiraDataListPtr)
{
	int i;
	for(i=0;i<pKiraDataListPtr->Num;i++){
		if ( pKiraDataListPtr->Data[i].Tcb != NULL ){
			TCB_Delete(pKiraDataListPtr->Data[i].Tcb);
		}
	}
	sys_FreeMemoryEz(pKiraDataListPtr->Data);
	sys_FreeMemoryEz(pKiraDataListPtr);
}

//--------------------------------------------------------------------------------------------
/**
 * �L���f�[�^���X�g�̎w��C���f�b�N�X�̃A�N�^�[���[�N��Ԃ�
 *
 * @param	pKiraDataListPtr	�f�[�^���X�g�|�C���^
 * @param	inIndex				�w��C���f�b�N�X
 *
 * @return	CLACT_WORK_PTR		�A�N�^�[���[�N�|�C���^
 */
//--------------------------------------------------------------------------------------------
CLACT_WORK_PTR *OPDKira_GetActWorkPtrFromList( OPD_KIRA_DATLST_PTR pKiraDataListPtr,
											  const int inIndex)
{
	GF_ASSERT(inIndex<pKiraDataListPtr->Num);

	return &pKiraDataListPtr->Data[inIndex].ActWorkPtr;
}

//--------------------------------------------------------------------------------------------
/**
 * �W�F�l���[�^�[���
 *
 * @param	ptr		�L���W�F�l���[�^�[�}�l�[�W��
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OPDKira_FreeGeneMng(OPD_K_G_MNG_PTR ptr)
{
	u8 i;
	
	//�A�N�^�[�I��
	EndCellActor(&ptr->KiraObjWork);
	
	//�ғ����̂s�b�a���폜
	for(i=0;i<GENERATER_MAX;i++){
		if (ptr->Generater[i].GeneTcb != NULL){
			TCB_Delete(ptr->Generater[i].GeneTcb);
		}
	}
	for(i=0;i<OPD_KIRA_ACT_MAX;i++){
		if (ptr->KiraObjWork.KiraData[i].Tcb != NULL){
			TCB_Delete(ptr->KiraObjWork.KiraData[i].Tcb);
		}
	}
	sys_FreeMemoryEz(ptr);
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
static void InitCellActor( OPD_KIRA_OBJ_WORK *wk )
{
	int i;
	const int heapid = HEAPID_OP_DEMO;

	//�}�b�s���O���[�h�ݒ�
	GX_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);
	GXS_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);	
	
	OpdKira_InitCharPlttManager();
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
	wk->ClactSet = CLACT_U_SetEasyInit( OPD_KIRA_ACT_MAX, &wk->RendData, heapid );
	
	//���\�[�X�}�l�[�W���[������
	for(i=0;i<RESOURCE_NUM;i++){		//���\�[�X�}�l�[�W���[�쐬
		wk->ResMan[i] = CLACT_U_ResManagerInit(ResEntryNumTbl[i], i, heapid);
	}

	//--chara�ǂݍ���
										
	wk->ResObjTbl[CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
										wk->ResMan[CLACT_U_CHAR_RES],
										ARC_OP_DEMO, NARC_op_demo_op_demoBG0_obj_NCGR,
										FALSE, ACT_ID_KIRA, NNS_G2D_VRAM_TYPE_MAX, heapid);
	
	//--pal�ǂݍ���

	wk->ResObjTbl[CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
										wk->ResMan[CLACT_U_PLTT_RES],
										ARC_OP_DEMO, NARC_op_demo_op_demoBG_obj_NCLR,
										FALSE, ACT_ID_KIRA, NNS_G2D_VRAM_TYPE_MAX, PALETTE_NUM, heapid);
		
	//--cell�ǂݍ���
										
	wk->ResObjTbl[CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELL_RES],
										ARC_OP_DEMO, NARC_op_demo_op_demoBG0_obj_NCER,
										FALSE, ACT_ID_KIRA, CLACT_U_CELL_RES, heapid);
	
	//--�����֐���anim�ǂݍ���
										
	wk->ResObjTbl[CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELLANM_RES],
										ARC_OP_DEMO, NARC_op_demo_op_demoBG0_obj_NANR,
										FALSE, ACT_ID_KIRA, CLACT_U_CELLANM_RES, heapid);
	// ���\�[�X�}�l�[�W���[����]��
	
	// Chara�]��
	CLACT_U_CharManagerSet( wk->ResObjTbl[CLACT_U_CHAR_RES] );
	// �p���b�g�]��
	CLACT_U_PlttManagerSet( wk->ResObjTbl[CLACT_U_PLTT_RES] );

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );		// MAIN DISP OBJ ON
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );		// MAIN DISP OBJ ON
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
static void EndCellActor( OPD_KIRA_OBJ_WORK *wk )
{
	u8 i;
	// �L�����]���}�l�[�W���[�j��
	CLACT_U_CharManagerDelete(wk->ResObjTbl[CLACT_U_CHAR_RES]);
	// �p���b�g�]���}�l�[�W���[�j��
	CLACT_U_PlttManagerDelete(wk->ResObjTbl[CLACT_U_PLTT_RES]);
	
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
static void SetActor( OPD_KIRA_OBJ_WORK *wk )
{
	int i;
	CLACT_HEADER			cl_act_header;
	CLACT_ADD add;

	for(i=0;i<OPD_KIRA_ACT_MAX;i++){
		MakeClActHeader( wk, &add, &cl_act_header );
		add.mat.x = FX32_ONE * i*2;
		add.mat.y = FX32_ONE * i*2;
		wk->KiraData[i].ActWorkPtr = CLACT_Add(&add);
		
		CLACT_SetAnmFlag(wk->KiraData[i].ActWorkPtr, 0);
		CLACT_SetDrawFlag(wk->KiraData[i].ActWorkPtr, 0);	//��\��
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
static void DrawActor( OPD_KIRA_OBJ_WORK *wk )
{
	CLACT_Draw( wk->ClactSet );
}

//--------------------------------------------------------------------------------------------
/**
 * �W�F�l���[�^�[���C��
 *
 * @param	ptr			�}�l�[�W���|�C���^
 * @param	inCounter	�t���[���J�E���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void KiraGenerateMain(OPD_K_G_MNG_PTR ptr, const int inCounter)
{
	if (inCounter == FM_KIRA_SATRT1){
		//�W�F�l���[�^�[����
		CreateKiraGenerater(&ptr->Generater[0], ptr, 3, 3, 3, GENE_TYPE_FIRST);
	}else if (inCounter == FM_KIRA_SATRT2){
		//�W�F�l���[�^�[����
		CreateKiraGenerater(&ptr->Generater[1], ptr, 3, 3, 3, GENE_TYPE_SEC);
	}

	DrawActor( &ptr->KiraObjWork );
}

//--------------------------------------------------------------------------------------------
/**
 * �W�F�l���[�^�[����
 *
 * @param	pGenerater	�W�F�l���[�^�[
 * @param	ptr			�}�l�[�W���|�C���^
 * @param	inNum		������
 * @param	inMargin	�����Ԋu
 * @param	inLoop		���[�v��
 * @param	inType		�����^�C�v
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CreateKiraGenerater(OPD_KIRA_GENERATER *pGenerater, OPD_K_G_MNG_PTR ptr, 
								const u8 inNum, const u8 inMargin, const u8 inLoop,
								const u8 inType)
{
	pGenerater->GeneParam.Num = inNum;
	pGenerater->GeneParam.Margin = inMargin;
	pGenerater->GeneParam.LoopMax = inLoop;
	pGenerater->GeneParam.Count = 0;
	pGenerater->GeneParam.Loop = 0;
	pGenerater->KiraDataListPtr = ptr->KiraObjWork.KiraData;
	pGenerater->GeneParam.Type = inType;
	
	pGenerater->GeneTcb = TCB_Add(TCB_GenerateFunc, pGenerater, 10);
}

//--------------------------------------------------------------------------------------------
/**
 * �L���G�t�F�N�g����
 *
 * @param	pKiraDataListPtr	�f�[�^���X�g
 * @param	inNum				������
 * @param	intype				�����^�C�v
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void GenerateKira( OPD_KIRA_DATA *pKiraDataListPtr, const u8 inNum, const u8 inType)
{
	u8 i;
	OPD_KIRA_DATA *kira_data;
	int base_y;

	if(inType == GENE_TYPE_FIRST){
		base_y = OPD_KIRA_Y_BASE1;
	}else{
		base_y = OPD_KIRA_Y_BASE2;
	}
	
	for(i=0;i<inNum;i++){
		//���g�p�f�[�^����
		kira_data = GetInvalidKiraData(pKiraDataListPtr, OPD_KIRA_ACT_MAX);
		
		//���W����
		{
			VecFx32 vec;
			vec =  *CLACT_GetMatrix( kira_data->ActWorkPtr );
			vec.x = FX32_ONE * ( OPD_KIRA_X_BASE+(gf_rand()%OPD_KIRA_W) );
			vec.y = FX32_ONE * ( base_y+(gf_rand()%OPD_KIRA_H) );
			CLACT_SetMatrix( kira_data->ActWorkPtr, &vec );
		}
		//�o�j�b�V���I�t
		CLACT_SetAnmFlag(kira_data->ActWorkPtr, 1);
		CLACT_SetDrawFlag(kira_data->ActWorkPtr, 1);
		//�}�l�[�W���̎��󂫃^�X�N���擾
		kira_data->Tcb = TCB_Add(TCB_KiraFunc, kira_data, 20);
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �󂢂Ă���L���f�[�^��Ԃ�
 *
 * @param	pKiraDataList	�f�[�^���X�g
 * @param	inMax			���X�g���ڍő吔
 *
 * @return	OPD_KIRA_DATA *	�L���f�[�^�|�C���^
 */
//--------------------------------------------------------------------------------------------
static OPD_KIRA_DATA *GetInvalidKiraData(OPD_KIRA_DATA *pKiraDataList, const int inMax)
{
	u8 i;
	OPD_KIRA_DATA *data;
	for (i=0;i<OPD_KIRA_ACT_MAX;i++){
		if (!pKiraDataList[i].Valid){
			data = &pKiraDataList[i];
			data->Valid = 1;
			data->MoveCounter = 0;
			return data;
		}
	}
	GF_ASSERT(0&&"no_acter");
	return NULL;
}

//--------------------------------------------------------------------------------------------
/**
 * �L���G�t�F�N�g�W�F�l���[�^�[�^�X�N
 *
 * @param	tcb		�^�X�N�|�C���^
 * @param	work	���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TCB_GenerateFunc( TCB_PTR tcb, void* work )
{
	OPD_KIRA_GENERATER * generater = work;
	KIRA_GENERATE_PARAM* param = &generater->GeneParam;
	//�����^�C�~���O��������A�����J�n
	if(param->Count++ >= param->Margin){
		GenerateKira(generater->KiraDataListPtr, param->Num, param->Type);
		param->Count = 0;
		if (++param->Loop >= param->LoopMax){
			//�^�X�N�I��
			TCB_Delete(tcb);
			generater->GeneTcb = NULL;
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �L���G�t�F�N�g����^�X�N
 *
 * @param	tcb		�^�X�N�|�C���^
 * @param	work	���[�N	
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TCB_KiraFunc( TCB_PTR tcb, void* work )
{
	OPD_KIRA_DATA *kira_data = work;
	//�����ŉ��Ɉړ����āA������
	{
		VecFx32 vec;
		vec =  *CLACT_GetMatrix( kira_data->ActWorkPtr );
		vec.y += (FX32_ONE*3);
		CLACT_SetMatrix( kira_data->ActWorkPtr, &vec );
	}

	kira_data->MoveCounter++;

	if (kira_data->MoveCounter >= KIRA_MOVE_MAX){
		TCB_Delete(tcb);
		kira_data->Tcb = NULL;
		kira_data->Valid = 0;
		//�A�N�^�[�o�j�b�V��
		CLACT_SetAnmFlag(kira_data->ActWorkPtr, 0);
		CLACT_SetDrawFlag(kira_data->ActWorkPtr, 0);
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �T�u��ʏ풓�L���G�t�F�N�g���C��
 *
 * @param	pKiraDataListPtr	�f�[�^���X�g�|�C���^	
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Scene2_KiraGenerateMain(OPD_KIRA_DATLST_PTR pKiraDataListPtr)
{
	Scene2_GenerateKira( pKiraDataListPtr, 2);
}


//--------------------------------------------------------------------------------------------
/**
 * �T�u��ʏ풓�L���G�t�F�N�g����
 *
 * @param	pKiraDataListPtr	�f�[�^���X�g�|�C���^	
 * @param	inNum	������
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void Scene2_GenerateKira( OPD_KIRA_DATLST_PTR pKiraDataListPtr, const u8 inNum)
{
	u8 i;
	OPD_KIRA_DATA *list_top;
	OPD_KIRA_DATA *kira_data;

	list_top = pKiraDataListPtr->Data;

	for(i=0;i<inNum;i++){
		//���g�p�f�[�^����
		kira_data = GetInvalidKiraData(list_top, pKiraDataListPtr->Num);
		
		//���W����
		{
			VecFx32 vec;
			vec =  *CLACT_GetMatrix( kira_data->ActWorkPtr );
			vec.x = FX32_ONE * ( OPD_KIRA2_X_BASE+(gf_rand()%OPD_KIRA2_W) );
			vec.y = FX32_ONE * ( 192+OPD_KIRA2_Y_BASE+(gf_rand()%OPD_KIRA2_H) );
			CLACT_SetMatrix( kira_data->ActWorkPtr, &vec );
		}
		//�o�j�b�V���I�t
		CLACT_SetAnmFlag(kira_data->ActWorkPtr, 1);
		CLACT_SetDrawFlag(kira_data->ActWorkPtr, 1);
		//�}�l�[�W���̎��󂫃^�X�N���擾
		kira_data->Tcb = TCB_Add(TCB_Scene2KiraFunc, kira_data, 20);
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �L���G�t�F�N�g����^�X�N
 *
 * @param	tcb		�^�X�N�|�C���^
 * @param	work	���[�N	
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TCB_Scene2KiraFunc( TCB_PTR tcb, void* work )
{
	OPD_KIRA_DATA *kira_data = work;

	kira_data->MoveCounter++;

	if (kira_data->MoveCounter >= SCENE2_KIRA_MOVE_MAX){
		TCB_Delete(tcb);
		kira_data->Tcb = NULL;
		kira_data->Valid = 0;
		//�A�N�^�[�o�j�b�V��
		CLACT_SetAnmFlag(kira_data->ActWorkPtr, 0);
		CLACT_SetDrawFlag(kira_data->ActWorkPtr, 0);
	}
}
