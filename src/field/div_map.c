//============================================================================================
/**
 * @file	div_map.c
 * @brief	�����}�b�v
 * @author	Nozomu Saito
 * @date	2005.05.06
 */
//============================================================================================
#include "common.h"
#include "div_map_cont_def.h"
#include "fieldsys.h"
#include "worldmap.h"	//<<20060113add
#include "fieldmap_mem.h"
//#include "sp_attribute_def.h"

#include "debug_saito.h"
#include "fld_debug.h"

#include "system/arc_tool.h"
#include "communication/communication.h" // �ʐM�G���[�֌W

#define BLOCK_GRID_SIZE_X	(BLOCK_GRID_W)	//1�u���b�N�̉��O���b�h��
#define BLOCK_GRID_SIZE_Z	(BLOCK_GRID_H)	//1�u���b�N�̏c�O���b�h��

#define HARF_GRID_SIZE	(ONE_GRID_SIZE/2)
#define NON_BLOCK	(-1)

#define MODEL_SET_DIV_SIZE	( 0xe000 )
#define MAP_ARC_NO_DATA		( 0xffff )

#define DIV_CALL_BACK

enum {
	MODELSET_TASK_SEQ_INIT = 0,
	MODELSET_TASK_SEQ_MODEL_LOAD,
	MODELSET_TASK_SEQ_TEXTURE_BIND,
	MODELSET_TASK_SEQ_RESOUCE_SET,
	MODELSET_TASK_SEQ_RENDER_OBJ,
	MODELSET_TASK_SEQ_EXIT
};

typedef struct DIV_FUNC_LIST_tag const * DFL_CONST_PTR;

typedef struct MAP_LOAD_TASK_COUNTER_tag
{
	int BlockLoadTaskCounter;
	int BlockHeightLoadTaskCounter;
	
}MAP_LOAD_TASK_COUNTER;

//�u���b�N���X�g�f�[�^
typedef struct BLOCK_NODE_tag{
	u16 Attribute[32*32];
	NNSG3dRenderObj		FloorData;
	NNSG3dResFileHeader	*FloorResFile;
	u8				*HeightMem;
	MHI_PTR			MapHeightInfo;
	int BlockIndex;
	BOOL DrawOKFlg;
	M3DOL_PTR	ObjDataList;
}BLOCK_NODE;

typedef struct MAP_LOAD_BLOCK_ST_tag
{
	BLOCK_NODE *Node[2];
	
	TCB_PTR	RandTask;		//�n�`���[�h�^�X�N�|�C���^
	TCB_PTR	HeightTask;		//�������[�h�^�X�N�|�C���^
	MAP_LOAD_TASK_COUNTER	TaskCnter;	//�n�`���[�h�^�X�N�A�������[�h�^�X�N�̃J�E���^
	int Block[2];
	u8 Index[2];

	u8 TotalCount;
	BOOL BlockLoadOK;
	
}MAP_LOAD_BLOCK_ST;

typedef void (*DIV_FIRST_FUNC)(	DMC_PTR outDivMapCont,
								const int inGridX, 
								const int inGridZ,
								const int inMapGridW);
typedef void (*DIV_LOAD_FUNC)(	const u8 inCount,
								const MAP_RESOURCE_PTR inMapResource,
								const WORLD_MAP_PTR inWorld,
								const int inMapW,
								const int inMapH,
								DMC_PTR inDivMapCont,
								MAP_LOAD_BLOCK_ST *ioMLBS);


typedef struct DIV_FUNC_LIST_tag{
	DIV_FIRST_FUNC	DivFirstFunc;
	DIV_LOAD_FUNC	DivLoadFunc;
}DIV_FUNC_LIST;

typedef struct BLOCK_LOAD_tag
{
	MAP_LOAD_BLOCK_ST	MLBS;
	BOOL	Moving;		//�ғ����t���O
	u8		LoadDir;	//���[�h����
}MAP_LOAD_BLOCK_CONT;

typedef struct STOCK_LOAD_DATA_tag
{
	BLOCK_NODE *Node[2];
	BOOL	Valid;
	u8		LoadDir;	//���[�h����
	int Block[2];
	u8 Index[2];
}STOCK_LOAD_DATA;

typedef struct DIV_MAP_CHECK_tag
{
	VecFx32 OldPoint;
	VecFx32 const *TargetPoint;
	fx32 const *LargeVal;
	fx32 const *SmallVal;
	BOOL Moving;
	u8 Dir;
	BOOL Valid;
}DIV_MAP_CHECK;

typedef struct DIV_MAP_LOAD_CONT_tag
{
	FMM_PTR FldMapMem;
	MAP_LOAD_BLOCK_CONT MLBC[2];		//���[�h���N�G�X�g�Ǘ��f�[�^
	STOCK_LOAD_DATA Stock;				//���[�h���N�G�X�g�X�g�b�N
	BOOL LocalFreeIndexTable[4];		//����\��e�[�u��
	BLOCK_NODE *BlockNodeList[4];		//���@�̎����4�u���b�N�̃f�[�^�ւ̃|�C���^

	u8 MovingNum;	//�ғ���
	u8 BlankNo;			//0or1			���[�h���N�G�X�g�Ǘ��󂫔ԍ�
	u8 NowMovingNo;		//0or1			���[�h���N�G�X�g�Ǘ��ԍ�
	u32 NowBlockIndex;		
	u32 NowGridNo;				//��0�̎��@�O���b�h�i���o�[
	u8 NowLocalIndex;			//���݃��[�J���C���f�b�N�X
	u8 NowPosInBlock;	//0�`3
	BOOL FreeRequest;
	int LoadSeq;
	MAP_RESOURCE_PTR MapResource;
	WORLD_MAP_PTR World;
	//���L3�̕ϐ���world�\���̂̃|�C���^����擾�\�ł����A�A�N�Z�X���p�ɂɔ������邽�߁A
	//�������̒i�K�ł����ɒl���i�[���A������g���܂��B
	//���̕ϐ��̒l�̓}�b�v���؂�ւ��Ȃ�����ύX�͂���܂���B(�����������s��Ȃ�)
	int MapW;
	int MapH;
	int MapGridW;

	DIV_MAP_CHECK MapCheck;
	FLD_3D_ANM_MNG_PTR Field3DAnmPtr;
	DFL_CONST_PTR	FuncList;
	ARCHANDLE *ArcHandle;		//�A�[�J�C�u�n���h��
#ifdef DIV_CALL_BACK
	//�R�[���o�b�N�֐�
	DIV_LOAD_CALL_BACK CallBack;
	//�R�[���o�b�N���[�N
	void *CallBackWork;
#endif	
}DIV_MAP_LOAD_CONT;

typedef struct DATA_OFS_SIZE_tsg
{
	int AttrSize;
	int MapSize;
	int HeightSize;
	int ObjSize;
}DATA_OFS_SIZE;

#ifdef PM_DEBUG
static BOOL DebugOutRangeFlg = TRUE;
#endif


//////////////////////////////////////////////////////////////////////////////////
//	�O���錾
//////////////////////////////////////////////////////////////////////////////////
static TCB_PTR Set3DModelTask(	ARCHANDLE *inHandle,
								const int inSize,
								NNSG3dRenderObj* object_p,
								NNSG3dResFileHeader** resFile,
								NNSG3dResTex* pTexture,
								BOOL *ioDrawOKFlg,
								int *inEndFlg);
static NNSG3dResMdl* Set3DModel(	ARCHANDLE *ioHandle,
									const int inSize,
									NNSG3dRenderObj* object_p,
									NNSG3dResFileHeader** resFile,
									NNSG3dResTex* pTexture);
static void StopMapLoadTaskRequest(TCB_PTR tcb);
static void InitMapLoadCont(DMC_PTR outDivMapCont);
static void LoadFirstBlock(	DMC_PTR outDivMapCont,
							const int inGridX, 
							const int inGridZ,
							const int inMapGridW);
static void LoadFirstBlockForUnder(	DMC_PTR outDivMapCont,
									const int inGridX, 
									const int inGridZ,
									const int inMapGridW);
static void AllocBlockList(DMC_PTR outDivMapCont);
static void AllocBlockListForUnder(DMC_PTR outDivMapCont);
static void	LoadStopReqest(DMC_PTR ioDivMapCont,const u8 inNo);
static BOOL BlockLoadReqest( DMC_PTR ioDivMapCont,
								const int inBlock1,
								const int inBlock2,
								const u8 inIdx1,
								const u8 inIdx2,
								const u8 inBlankNo,
								const u8 inDir);
static void GetMapArcLoadOffset(ARCHANDLE *ioHandle, const int inArcIndex, DATA_OFS_SIZE *outData);
static void LoadBlock(const u8 inCount,
		const MAP_RESOURCE_PTR inMapResource,
		const WORLD_MAP_PTR inWorld,
		const int inMapW,
		const int inMapH,
		DMC_PTR inDivMapCont,
		MAP_LOAD_BLOCK_ST *ioMLBS);
static void LoadBlockForUnder(const u8 inCount,
		const MAP_RESOURCE_PTR inMapResource,
		const WORLD_MAP_PTR inWorld,
		const int inMapW,
		const int inMapH,
		DMC_PTR inDivMapCont,
		MAP_LOAD_BLOCK_ST *ioMLBS);
static void LoadBlockQuick(	const int inBlockIndex,
							const u8 inLocalIndex,
							const MAP_RESOURCE_PTR inMapResource,
							const WORLD_MAP_PTR inWorld,
							const int inMapW,
							const int inMapH,
							const BOOL inLightValid,
							DMC_PTR outDivMapCont);
static void LoadBlockQuickForUnder(	const int inBlockIndex,
									const u8 inLocalIndex,
									const MAP_RESOURCE_PTR inMapResource,
									const WORLD_MAP_PTR inWorld,
									const int inMapW,
									const int inMapH,
									const BOOL inLightValid,
									DMC_PTR outDivMapCont);
static void UpdateBlockList(const int inBlockIndex, const u8 inDirection, DMC_PTR ioDivMapCont);
static void FreeAndMoveNode(const u8 inFreeNo1,
							const u8 inFreeNo2,
							const u8 inMoveNo1,
							const u8 inMoveNo2,
							DMC_PTR ioDivMapCont);
static void FreeBlock(const u8 inLocalIndex, DMC_PTR outDivMapCont);

static void DrawBlock(	const u8 inLocalIndex,
						DMC_CONST_PTR inDivMapCont,
						const GLST_DATA_PTR	glst_data);
static BOOL CompLoadDirection(const u8 inDir, DMC_CONST_PTR inDivMapCont, u8* outNo);
static BOOL BlockLoadReqestForStock(DMC_PTR ioDivMapCont);
static BOOL IsFinishedLoadBlock(DMC_CONST_PTR inDivMapCont);
static void ClearLocalFreeIndexTable(DMC_PTR outDivMapCont);
static void MarkLocalFreeIndexTableByDir(const u8 inDir,DMC_PTR outDivMapCont);



static u8 CalcLocalIdxFromPosInBlock(const u8 inPosInBlock);
static u32 GetNextGridNo(	const u8 inDirection,
							const int inMapH,
							const int inMapGridW,
							const int inNowGridNo);

static u8 GetNextPosInBlock(const u8 inDirection, const int inNowPosInBlock);
static void UpdateNowLocalIndexForAfterLoad(const u8 inDirection,
											const int inNowPosInBlock,
											u8 *outNowLocalIndex);

static void AddMapLoad(const int inBlock1,
					const int inBlock2,
					const u8 inIdx1,
					const u8 inIdx2,
					const u8 inDir,
					DMC_PTR ioDivMapCont);
static int CalcGridNoFromGridXZ(const int inGridX, const int inGridZ, const int inMapGridW);
static void AddMapLoadForStock(DMC_PTR ioDivMapCont);
							
static void UpdateNowData(const int inGridX, const int inGridZ, DMC_PTR outDivMapCont);
static void CalcMapOffset3D(	const int inBlockIndex,
								const int inMapW,
								const WORLD_MAP_PTR inWorld,
								VecFx32 *outTrans);

///////////////////////////////////////////////////////
//	�X�^�e�B�b�N�ϐ�
///////////////////////////////////////////////////////

static const DIV_FUNC_LIST DivGroundFunc = 
{
	LoadFirstBlock,
	LoadBlock
};

static const DIV_FUNC_LIST DivUnderFunc = 
{
	LoadFirstBlockForUnder,
	LoadBlockForUnder
};

//--------------------------------------------------------------------------------------------
/**
 * �������`�F�b�N�c
 *
 * @param	inBlockIdx1		�u���b�N�C���f�b�N�X1
 * @param	inBlockIdx2		�u���b�N�C���f�b�N�X2
 * @param	inMapW			�}�b�v��
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL CheckColumnBlockIndex(const int inBlockIdx1,
								const int inBlockIdx2,
								const int inMapW)
{
	if (inBlockIdx1%inMapW != inBlockIdx2%inMapW){
		return FALSE;
	}else{
		return TRUE;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �������`�F�b�N��
 *
 * @param	inBlockIdx1		�u���b�N�C���f�b�N�X1
 * @param	inBlockIdx2		�u���b�N�C���f�b�N�X2
 * @param	inMapW			�}�b�v��
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL CheckRowBlockIndex(const int inBlockIdx1,
								const int inBlockIdx2,
								const int inMapW)
{
	if (inBlockIdx1/inMapW != inBlockIdx2/inMapW){
		return FALSE;
	}else{
		return TRUE;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ���[�h�^�X�N�̃i���o�[(0or1)���g�p�����^�X�N��~���N�G�X�g
 *
 * @param	ioDivMapCont	�����}�b�v�\���̃|�C���^
 * @param	inNo			���~���N�G�X�g�i���o�[�i0�n�q1�j
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void	LoadStopReqest(DMC_PTR ioDivMapCont,const u8 inNo)
{
	u8 idx;
	u8 i;

	if (ioDivMapCont->MLBC[inNo].MLBS.TaskCnter.BlockLoadTaskCounter != 0){
		//�n�`�f�[�^���[�h���~���N�G�X�g
		StopMapLoadTaskRequest(ioDivMapCont->MLBC[inNo].MLBS.RandTask);
#ifdef DIV_MAP_LOAD_DEBUG		
		OS_Printf("�n�`���\n");
#endif		
	}
	if (ioDivMapCont->MLBC[inNo].MLBS.TaskCnter.BlockHeightLoadTaskCounter != 0){
		//�����f�[�^���[�h���~���N�G�X�g
		StopHeightLoadTaskRequest(ioDivMapCont->MLBC[inNo].MLBS.HeightTask);
#ifdef DIV_MAP_LOAD_DEBUG
		OS_Printf("�������\n");
#endif
	}
	ioDivMapCont->MLBC[inNo].MLBS.BlockLoadOK = TRUE;
#if 0
	//�A�[�J�C�u�n���h�������
	if (ioDivMapCont->ArcHandle != NULL){
		ArchiveDataHandleClose( ioDivMapCont->ArcHandle );
		ioDivMapCont->ArcHandle = NULL;
	}
#endif	
}

//--------------------------------------------------------------------------------------------
/**
 * �u���b�N�f�[�^���g�p�����A�^�X�N�̒�~���N�G�X�g
 *
 * @param	*inMLBS		���[�h�u���b�N�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void	LoadTaskStopReqestByMLBS(MAP_LOAD_BLOCK_ST *inMLBS)
{
	if (inMLBS->TaskCnter.BlockLoadTaskCounter != 0){
		//�n�`�f�[�^���[�h���~���N�G�X�g
		StopMapLoadTaskRequest(inMLBS->RandTask);
	}
	if (inMLBS->TaskCnter.BlockHeightLoadTaskCounter != 0){
		//�����f�[�^���[�h���~���N�G�X�g
		StopHeightLoadTaskRequest(inMLBS->HeightTask);
	}

	//���̃^�X�N�������ɉ��悤�ɁA�����ŃJ�E���^���N���A���Ă���
	inMLBS->TaskCnter.BlockLoadTaskCounter = 0;
	inMLBS->TaskCnter.BlockHeightLoadTaskCounter = 0;
	
	//inMLBS->StopFlg = TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �����u���b�N���O���b�h���犄��o��
 *
 * @param	inGridX			�O���b�h�w���W
 * @param	inGridZ			�O���b�h�y���W
 * @param	inMapW			�}�b�v����
 * @param	inMapH			�}�b�v�c��
 * @param	inMapGridW		�}�b�v�O���b�h��
 * @param	*outBlockTbl	�����u���b�N�e�[�u��
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void MakeStartBlockTbl(	const int inGridX,
								const int inGridZ,
								const int inMapW,
								const int inMapH,
								const int inMapGridW,
								int *outBlockTbl)
{
	int grid_no;
	u8 pos_in_block;
	int block_index;
	int block_w, block_h;
	//4�u���b�N�̍���̃C���f�b�N�X���Z�o
	block_w = (inGridX / BLOCK_GRID_SIZE_X);
	block_h = (inGridZ / BLOCK_GRID_SIZE_Z);

	grid_no = CalcGridNoFromGridXZ(inGridX,inGridZ,inMapGridW);
	pos_in_block = CalcPositionInBlockFromGridNo(grid_no,inMapGridW);

	block_index = (block_h*inMapW)+block_w;
	
	switch(pos_in_block){
	case 0:		//����
		//�����̓��[�J��3
		outBlockTbl[3] = block_index;
		outBlockTbl[0] = block_index-inMapW-1;
		outBlockTbl[1] = block_index-inMapW;
		outBlockTbl[2] = block_index-1;
		//���ׂ̃u���b�N�𒲂ׂ�
		if(block_w-1<0){
			//���͔͈͊O
			//���̏���͈͊O�̂͂�
			outBlockTbl[0] = NON_BLOCK;
			outBlockTbl[2] = NON_BLOCK;
		}
		//��̃u���b�N�𒲂ׂ�
		if(block_h-1<0){
			//��͔͈͊O
			outBlockTbl[1] = NON_BLOCK;
		}
///		block_w--;
///		block_h--;
		break;
	case 1:		//�E��
		//�����̓��[�J��2
		outBlockTbl[2] = block_index;
		outBlockTbl[0] = block_index-inMapW;
		outBlockTbl[1] = block_index-inMapW+1;
		outBlockTbl[3] = block_index+1;
		//�E�ׂ̃u���b�N�𒲂ׂ�
		if(block_w+1>=inMapW){
			//�E�͔͈͊O
			//���̏���͈͊O�̂͂�
			outBlockTbl[1] = NON_BLOCK;
			outBlockTbl[3] = NON_BLOCK;
		}
		//��̃u���b�N�𒲂ׂ�
		if(block_h-1<0){
			//��͔͈͊O
			outBlockTbl[0] = NON_BLOCK;
		}
///		block_h--;
		break;
	case 2:		//����
		//�����̓��[�J��1
		outBlockTbl[1] = block_index;
		outBlockTbl[0] = block_index-1;
		outBlockTbl[2] = block_index+inMapW-1;
		outBlockTbl[3] = block_index+inMapW;
		//���ׂ̃u���b�N�𒲂ׂ�
		if(block_w-1<0){
			//���͔͈͊O
			//���̉����͈͊O�̂͂�
			outBlockTbl[0] = NON_BLOCK;
			outBlockTbl[2] = NON_BLOCK;
		}
		//���̃u���b�N�𒲂ׂ�
		if(block_h+1>inMapH){
			//���͔͈͊O
			outBlockTbl[3] = NON_BLOCK;
		}
///		block_w--;
		break;
	case 3:		//�E��
		//�����̓��[�J��0
		outBlockTbl[0] = block_index;
		outBlockTbl[1] = block_index+1;
		outBlockTbl[2] = block_index+inMapW;
		outBlockTbl[3] = block_index+inMapW+1;
		//�E�ׂ̃u���b�N�𒲂ׂ�
		if(block_w+1>=inMapW){
			//�E�͔͈͊O
			//���̉����͈͊O�̂͂�
			outBlockTbl[1] = NON_BLOCK;
			outBlockTbl[3] = NON_BLOCK;
		}
		//���̃u���b�N�𒲂ׂ�
		if(block_h+1>inMapH){
			//���͔͈͊O
			outBlockTbl[0] = NON_BLOCK;
		}
		break;
	default:
		GF_ASSERT(0&&"ERROR:POS_IN_BLOCK");
	}
	
#ifdef DEBUG_ONLY_FOR_saitou
	OS_Printf("local_print block_wh=%d,%d\n",block_w,block_h);
	OS_Printf("local_print start_blocks=%d,%d,%d,%d\n",
			outBlockTbl[0],outBlockTbl[1],outBlockTbl[2],outBlockTbl[3]);
#endif //DEBUG_ONLY_FOR_saitou	
}

//--------------------------------------------------------------------------------------------
/**
 * 4�u���b�N���̃������m��
 *
 * @param	outDivMapCont	�����}�b�v�\���̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void AllocBlockList(DMC_PTR outDivMapCont)
{
	u8 i;
	for (i=0;i<4;i++){
		BLOCK_NODE *node = NULL;
		node = sys_AllocMemory( HEAPID_FIELD, sizeof(BLOCK_NODE) );
		outDivMapCont->BlockNodeList[i] = node;
		outDivMapCont->BlockNodeList[i]->DrawOKFlg = FALSE;

		//�m�ۂ���������(�n�`)�ƃ|�C���^���o�C���h
		BindGroundMem(i, outDivMapCont->FldMapMem, (void**)&(outDivMapCont->BlockNodeList[i]->FloorResFile));
		BindHeightMem(i, outDivMapCont->FldMapMem, (void**)&(outDivMapCont->BlockNodeList[i]->HeightMem));

		//3DOBJ�̃A���P�[�V����
		outDivMapCont->BlockNodeList[i]->ObjDataList =  M3DO_AllocMap3DObjList(HEAPID_FIELD);
		outDivMapCont->BlockNodeList[i]->BlockIndex = NON_BLOCK;
		//�A�g���r���[�g�N���A
		MI_CpuFillFast(outDivMapCont->BlockNodeList[i]->Attribute, 0xffffffff, 2*32*32 );
	}
	
	//BlockNodeList = sys_AllocMemory( HEAPID_FIELD, sizeof(BLOCK_NODE)*9 );
}

//--------------------------------------------------------------------------------------------
/**
 * 4�u���b�N���̃������m�ہi�n���j
 *
 * @param	outDivMapCont	�����}�b�v�\���̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void AllocBlockListForUnder(DMC_PTR outDivMapCont)
{
	u8 i;
	for (i=0;i<4;i++){
		BLOCK_NODE *node = NULL;
		node = sys_AllocMemory( HEAPID_FIELD, sizeof(BLOCK_NODE) );
		outDivMapCont->BlockNodeList[i] = node;
		outDivMapCont->BlockNodeList[i]->DrawOKFlg = FALSE;
		//�m�ۂ���������(�n�`)�ƃ|�C���^���o�C���h
		BindGroundMem(i, outDivMapCont->FldMapMem, (void**)&(outDivMapCont->BlockNodeList[i]->FloorResFile));
		///BindHeightMem(i, outDivMapCont->FldMapMem, (void**)&(outDivMapCont->BlockNodeList[i]->HeightMem));
		//3DOBJ�̃A���P�[�V����
		outDivMapCont->BlockNodeList[i]->ObjDataList =  M3DO_AllocMap3DObjList(HEAPID_FIELD);
		outDivMapCont->BlockNodeList[i]->BlockIndex = NON_BLOCK;
		//�n���͐�p�ɃA�g���r���[�g�f�[�^�����̂ŁA�N���A�������Ȃ�
	}
	
	//BlockNodeList = sys_AllocMemory( HEAPID_FIELD, sizeof(BLOCK_NODE)*9 );
}

//--------------------------------------------------------------------------------------------
/**
 * �A�[�J�C�u�I�t�Z�b�g�擾
 *
 * @param	ioHandle		�A�[�J�C�u�n���h��
 * @param	inArcIndex		�A�[�J�C�u�C���f�b�N�X
 * @param	outData			�擾�f�[�^�i�[�o�b�t�@
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void GetMapArcLoadOffset(ARCHANDLE *ioHandle, const int inArcIndex, DATA_OFS_SIZE *outData)
{
	void *raw_data;
	int *data;
	int size = sizeof(int)*4;	//4�o�C�g�S����
	

	if (ioHandle != NULL){
		raw_data = sys_AllocMemoryLo(HEAPID_FIELD, size);
		ArchiveDataLoadOfsByHandle( ioHandle, inArcIndex, 0, size, raw_data );
	}else{
		GF_ASSERT(0&&"ERROR:ArcHandle is NULL!\n");
		raw_data = ArchiveDataLoadMallocOfsLo(ARC_FIELD_MAP_DATA,inArcIndex,HEAPID_FIELD,0,size);
	}
	
	data = &((int*)(raw_data))[0];
	
	outData->AttrSize = *data;
	data++;
	outData->ObjSize = *data;
	data++;
	outData->MapSize = *data;
	data++;
	outData->HeightSize = *data;
	
	
	sys_FreeMemoryEz(raw_data);
#ifdef DEBUG_ONLY_FOR_saitou
	OS_Printf("local_print arc_size = %x,%x,%x,%x\n",
			outData->AttrSize,outData->ObjSize,outData->MapSize,outData->HeightSize);
#endif
}

//--------------------------------------------------------------------------------------------
/**
 * �u���b�N�f�[�^���[�h�̓o�^
 *
 * @param	inCount			�o�^�ꏊ�i0�n�q1�j
 * @param	inMapResource	�}�b�v���\�[�X
 * @param	inWorld			���[���h�|�C���^
 * @param	inMapW			�}�b�v����
 * @param	inMapH			�}�b�v�c��
 * @param	inDivMapCont	�����}�b�v�\���̃|�C���^
 * @param	*ioMLBS			���[�h�u���b�N�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void LoadBlock(	const u8 inCount,
						const MAP_RESOURCE_PTR inMapResource,
						const WORLD_MAP_PTR inWorld,
						const int inMapW,
						const int inMapH,
						DMC_PTR inDivMapCont,
						MAP_LOAD_BLOCK_ST *ioMLBS)
{
	int block_index;
	u8 local_index;
	int arc_index;
	DATA_OFS_SIZE data;
	block_index = ioMLBS->Block[inCount];
	
	if (block_index<0 || block_index>=inMapW*inMapH){
#ifdef DEBUG_ONLY_FOR_saitou		
		OS_Printf("BLOCK_LOAD_ERROR:INDEX_OVER %d\n",block_index);
#endif		
		return;
	}


	//�A�[�J�C�u�C���f�b�N�X���擾
	arc_index = GetWorldMapArcIdx(block_index, inWorld);
#ifdef DEBUG_ONLY_FOR_saitou	
	OS_Printf("local_print �A�[�J�C�u�ԍ�%d\n",arc_index);
#endif	
	if (arc_index == MAP_ARC_NO_DATA){
		return;
	}
#if 0
	GF_ASSERT(inDivMapCont->ArcHandle==NULL&&"�n���h������Y��");
	//�A�[�J�C�u�n���h���̎擾
	inDivMapCont->ArcHandle = ArchiveDataHandleOpen( ARC_FIELD_MAP_DATA, HEAPID_FIELD );
#endif	
	GetMapArcLoadOffset(inDivMapCont->ArcHandle, arc_index, &data);

	//�A�g���r���[�g���[�h
	{
		void *mem;
		mem = &(ioMLBS->Node[inCount]->Attribute[0]);
		ArchiveDataLoadByHandleContinue( inDivMapCont->ArcHandle, data.AttrSize, mem );
#ifdef DEBUG_ONLY_FOR_saitou
		OS_Printf("local_print �A�g���r���[�g���[�h\n");
#endif
	}

	//3DOBJ���[�h
	M3DO_LoadArc3DObjData(	inDivMapCont->ArcHandle,
							data.ObjSize,
							inMapResource,
							ioMLBS->Node[inCount]->ObjDataList,
							inDivMapCont->Field3DAnmPtr);
	
	//�n�`���[�h
	{
		//�ғ��^�X�N�ǉ�
		ioMLBS->TaskCnter.BlockLoadTaskCounter++;
#ifdef PM_DEBUG
		{
			if (data.MapSize > 0xf000){
				OS_Printf("�A�[�J�C�u%d:�n�`���f�����������T�C�Y�I�[�o�[�ł�:%d\n",arc_index,data.MapSize);
				GF_ASSERT(0);
			}
		}
#endif			
		ioMLBS->RandTask = Set3DModelTask(	inDivMapCont->ArcHandle,
											data.MapSize,
											&ioMLBS->Node[inCount]->FloorData,
											&(ioMLBS->Node[inCount]->FloorResFile),
											GetMapResourceTexturePTR(inMapResource),
											&(ioMLBS->Node[inCount]->DrawOKFlg),
											&ioMLBS->TaskCnter.BlockLoadTaskCounter);

		
	}

	//�������[�h	
	{
		//�ғ��^�X�N�ǉ�
		ioMLBS->TaskCnter.BlockHeightLoadTaskCounter++;
		ioMLBS->HeightTask = SetupHeightDataArcTask(inDivMapCont->ArcHandle,
													data.HeightSize,
													ioMLBS->Node[inCount]->MapHeightInfo,
													&ioMLBS->TaskCnter.BlockHeightLoadTaskCounter,
													&ioMLBS->Node[inCount]->HeightMem,
													&ioMLBS->TaskCnter.BlockLoadTaskCounter);
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �u���b�N�f�[�^���[�h�̓o�^�i�n���j
 *
 * @param	inCount			�o�^�ꏊ�i0�n�q1�j
 * @param	inMapResource	�}�b�v���\�[�X
 * @param	inWorld			���[���h�|�C���^
 * @param	inMapW			�}�b�v����
 * @param	inMapH			�}�b�v�c��
 * @param	inDivMapCont	�����}�b�v�\���̃|�C���^
 * @param	*ioMLBS			���[�h�u���b�N�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void LoadBlockForUnder(	const u8 inCount,
								const MAP_RESOURCE_PTR inMapResource,
								const WORLD_MAP_PTR inWorld,
								const int inMapW,
								const int inMapH,
								DMC_PTR inDivMapCont,
								MAP_LOAD_BLOCK_ST *ioMLBS)
{
	int block_index;
	u8 local_index;
	int arc_index;
	DATA_OFS_SIZE data;
	block_index = ioMLBS->Block[inCount];
	
	if (block_index<0 || block_index>=inMapW*inMapH){
#ifdef	DIV_MAP_LOAD_BORDER_PRINT_ON
		OS_Printf("BLOCK_LOAD_ERROR:INDEX_OVER %d\n",block_index);
#endif
		return;
	}

	//�A�[�J�C�u�C���f�b�N�X���擾
	arc_index = GetWorldMapArcIdx(block_index, inWorld);
#ifdef DEBUG_ONLY_FOR_saitou	
	OS_Printf("local_print �A�[�J�C�u�ԍ�%d\n",arc_index);
#endif	
	if (arc_index == MAP_ARC_NO_DATA){
		return;
	}
#if 0	
	GF_ASSERT(inDivMapCont->ArcHandle==NULL&&"�n���h������Y��");
	//�A�[�J�C�u�n���h���̎擾
	inDivMapCont->ArcHandle = ArchiveDataHandleOpen( ARC_FIELD_MAP_DATA, HEAPID_FIELD );
#endif	
	GetMapArcLoadOffset(inDivMapCont->ArcHandle, arc_index, &data);

	{
		u8 temp[0x800];
		//�A�g���r���[�g�͔�΂�
		///ArchiveDataSeekByHandle( inDivMapCont->ArcHandle, 0x800+0x10 );
		ArchiveDataLoadByHandleContinue( inDivMapCont->ArcHandle, 0x800, temp );
	}
	//3DOBJ���[�h
	M3DO_LoadArc3DObjData(	inDivMapCont->ArcHandle,
							data.ObjSize,
							inMapResource,
							ioMLBS->Node[inCount]->ObjDataList,
							inDivMapCont->Field3DAnmPtr);
	
	//�n�`���[�h
	{
		//�ғ��^�X�N�ǉ�
		ioMLBS->TaskCnter.BlockLoadTaskCounter++;
#ifdef PM_DEBUG
		{
			if (data.MapSize > 0xf000){
				OS_Printf("�A�[�J�C�u%d:�n�`���f�����������T�C�Y�I�[�o�[�ł�:%d\n",arc_index,data.MapSize);
				GF_ASSERT(0);
			}
		}
#endif			
		ioMLBS->RandTask = Set3DModelTask(	inDivMapCont->ArcHandle,
											data.MapSize,
											&ioMLBS->Node[inCount]->FloorData,
											&(ioMLBS->Node[inCount]->FloorResFile),
											GetMapResourceTexturePTR(inMapResource),
											&(ioMLBS->Node[inCount]->DrawOKFlg),
											&ioMLBS->TaskCnter.BlockLoadTaskCounter);

		
	}
	//�����͓ǂ܂Ȃ�		
}

//--------------------------------------------------------------------------------------------
/**
 * �u���b�N�̃��[�h1sync�^(�ꊇ�ǂݍ��݂̂��߁A�u���b�N�A�E�g���Ɏg�p����)
 *
 * @param	inBlockIndex	�u���b�N�C���f�b�N�X
 * @param	inLocalIndex	0�`3���[�J���C���f�b�N�X
 * @param	inMapResource	�}�b�v���\�[�X
 * @param	inWorld			���[���h�|�C���^
 * @param	inMapW			�}�b�v����
 * @param	inMapH			�}�b�v�c��
 * @param	inLightValid	���C�g�t���O
 * @param	outDivMapCont	�����}�b�v�\���̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void LoadBlockQuick(	const int inBlockIndex,
							const u8 inLocalIndex,
							const MAP_RESOURCE_PTR inMapResource,
							const WORLD_MAP_PTR inWorld,
							const int inMapW,
							const int inMapH,
							const BOOL inLightValid,
							DMC_PTR outDivMapCont)
{
	int arc_index;
	NNSG3dResMdl* model;			// ���f��
	DATA_OFS_SIZE data;
	
	if (inBlockIndex<0 || inBlockIndex>=inMapW*inMapH){
#ifdef	DIV_MAP_LOAD_BORDER_PRINT_ON		
		OS_Printf("BLOCK_LOAD_ERROR:INDEX_OVER\n");
#endif		
		return;
	}

	//�A�[�J�C�u�C���f�b�N�X���擾
	arc_index = GetWorldMapArcIdx(inBlockIndex, inWorld);
#ifdef DEBUG_ONLY_FOR_saitou
	OS_Printf("local_print �A�[�J�C�u�ԍ�%d\n",arc_index);
#endif	
	if (arc_index == MAP_ARC_NO_DATA){
		return;
	}
	//�A�[�J�C�u�n���h���̎擾
///	outDivMapCont->ArcHandle = ArchiveDataHandleOpen( ARC_FIELD_MAP_DATA, HEAPID_FIELD );
	
	GetMapArcLoadOffset(outDivMapCont->ArcHandle, arc_index, &data);

	//�A�g���r���[�g���[�h
	{
		void *mem;
		mem = &(outDivMapCont->BlockNodeList[inLocalIndex]->Attribute[0]);

		ArchiveDataLoadByHandleContinue( outDivMapCont->ArcHandle, data.AttrSize, mem );
	}

	//3DOBJ���[�h
	M3DO_LoadArc3DObjData(	outDivMapCont->ArcHandle,
							data.ObjSize,
							inMapResource,
							outDivMapCont->BlockNodeList[inLocalIndex]->ObjDataList,
							outDivMapCont->Field3DAnmPtr);
	
	//�n�`���[�h
	{
		model = Set3DModel(	outDivMapCont->ArcHandle,
							data.MapSize,
							&outDivMapCont->BlockNodeList[inLocalIndex]->FloorData,
							&(outDivMapCont->BlockNodeList[inLocalIndex]->FloorResFile),
							GetMapResourceTexturePTR(inMapResource));

		if (inLightValid == TRUE){
			//�O���[�o���X�e�[�g�g�p
			SetGlbLightMdl(model);
		}

		outDivMapCont->BlockNodeList[inLocalIndex]->DrawOKFlg = TRUE;	
	}

	//�������[�h
	{
		SetupHeightDataArc(	outDivMapCont->ArcHandle,
							data.HeightSize,
							outDivMapCont->BlockNodeList[inLocalIndex]->MapHeightInfo,
							outDivMapCont->BlockNodeList[inLocalIndex]->HeightMem);
	}
#if 0
	//�A�[�J�C�u�n���h���̉��
	ArchiveDataHandleClose( outDivMapCont->ArcHandle );
	outDivMapCont->ArcHandle = NULL;
#endif	
	outDivMapCont->BlockNodeList[inLocalIndex]->BlockIndex = inBlockIndex;

	//�R�[���o�b�N�Ăяo��
	if (outDivMapCont->CallBack!=NULL){
		outDivMapCont->CallBack(	outDivMapCont->CallBackWork,
									inBlockIndex,
									outDivMapCont->BlockNodeList[inLocalIndex]->ObjDataList);
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �u���b�N�̃��[�h1sync�^(�ꊇ�ǂݍ��݂̂��߁A�u���b�N�A�E�g���Ɏg�p����)�n���p
 *
 * @param	inBlockIndex	�u���b�N�C���f�b�N�X
 * @param	inLocalIndex	0�`3�@���[�J���C���f�b�N�X
 * @param	inMapResource	�}�b�v���\�[�X
 * @param	inWorld			���[���h�|�C���^
 * @param	inMapW			�}�b�v����
 * @param	inMapH			�}�b�v�c��
 * @param	inLightValid	���C�g�t���O
 * @param	outDivMapCont	�����}�b�v�\���̃|�C���^
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void LoadBlockQuickForUnder(	const int inBlockIndex,
									const u8 inLocalIndex,
									const MAP_RESOURCE_PTR inMapResource,
									const WORLD_MAP_PTR inWorld,
									const int inMapW,
									const int inMapH,
									const BOOL inLightValid,
									DMC_PTR outDivMapCont)
{
	int arc_index;
	DATA_OFS_SIZE data;
	NNSG3dResMdl* model;			// ���f��
	if (inBlockIndex<0 || inBlockIndex>=inMapW*inMapH){
		return;
	}

	//�A�[�J�C�u�C���f�b�N�X���擾
	arc_index = GetWorldMapArcIdx(inBlockIndex, inWorld);
#ifdef DEBUG_ONLY_FOR_saitou
	OS_Printf("local_print �A�[�J�C�u�ԍ�%d\n",arc_index);
#endif
	if (arc_index == MAP_ARC_NO_DATA){
		return;
	}
	//�A�[�J�C�u�n���h���̎擾
///	outDivMapCont->ArcHandle = ArchiveDataHandleOpen( ARC_FIELD_MAP_DATA, HEAPID_FIELD );
	
	GetMapArcLoadOffset(outDivMapCont->ArcHandle, arc_index, &data);

	{
		u8 temp[0x800];
		//�A�g���r���[�g�͔�΂�
		///ArchiveDataSeekByHandle( outDivMapCont->ArcHandle, 0x800+0x10 );
		ArchiveDataLoadByHandleContinue( outDivMapCont->ArcHandle, 0x800, temp );
	}

	//3DOBJ���[�h
	M3DO_LoadArc3DObjData(	outDivMapCont->ArcHandle,
							data.ObjSize,
							inMapResource,
							outDivMapCont->BlockNodeList[inLocalIndex]->ObjDataList,
							outDivMapCont->Field3DAnmPtr);
	
	//�n�`���[�h
	{
		model = Set3DModel(	outDivMapCont->ArcHandle,
							data.MapSize,
							&outDivMapCont->BlockNodeList[inLocalIndex]->FloorData,
							&(outDivMapCont->BlockNodeList[inLocalIndex]->FloorResFile),
							GetMapResourceTexturePTR(inMapResource));

		if (inLightValid == TRUE){
			//�O���[�o���X�e�[�g�g�p
			SetGlbLightMdl(model);
		}

		outDivMapCont->BlockNodeList[inLocalIndex]->DrawOKFlg = TRUE;	
	}

	//�����ǂ܂Ȃ�
#if 0
	//�A�[�J�C�u�n���h���̉��
	ArchiveDataHandleClose( outDivMapCont->ArcHandle );
	outDivMapCont->ArcHandle = NULL;
#endif	
	outDivMapCont->BlockNodeList[inLocalIndex]->BlockIndex = inBlockIndex;
}

//--------------------------------------------------------------------------------------------
/**
 * �u���b�N���[�h�^�X�N���ғ��������`�F�b�N
 *
 * @param	*inTaskCnter	�^�X�N�J�E���^
 *
 * @return	BOOL		TRUE:�I��	FALSE:�ғ���
 */
//--------------------------------------------------------------------------------------------
static BOOL CheckBlockLoadTaskCounter(const MAP_LOAD_TASK_COUNTER *inTaskCnter)
{
	if ((inTaskCnter->BlockLoadTaskCounter == 0)&&(inTaskCnter->BlockHeightLoadTaskCounter == 0) ){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �}�b�v���[�h���N�G�X�g�֐�
 *
 * @param	inBlock1	��1���[�h�u���b�N�C���f�b�N�X
 * @param	inBlock2	��2���[�h�u���b�N�C���f�b�N�X
 * @param	inIdx1		��1���[�h���[�J���C���f�b�N�X(0�`3)
 * @param	inIdx2		��2���[�h���[�J���C���f�b�N�X(0�`3)
 * @param	inBlankNo	�o�^�󂫏ꏊ�i0�n�q1�j
 * @param	inDir		���[�h����
 *
 * @return	BOOL		�o�^�����L��	TRUE:����	FALSE:���s
 */
//--------------------------------------------------------------------------------------------
static BOOL BlockLoadReqest( DMC_PTR ioDivMapCont,
								const int inBlock1,
								const int inBlock2,
								const u8 inIdx1,
								const u8 inIdx2,
								const u8 inBlankNo,
								const u8 inDir)
{
	//�ғ����ɓo�^���悤�Ƃ��Ă���̂ŃG���[�Ƃ���
	GF_ASSERT((ioDivMapCont->MLBC[inBlankNo].Moving == FALSE)&&"ERROR:�ғ����Ȃ̂ɓo�^���悤�Ƃ��Ă���");
	
	//�ғ����ɂ���
	ioDivMapCont->MLBC[inBlankNo].Moving = TRUE;

	//���[�h�����ۑ�
	ioDivMapCont->MLBC[inBlankNo].LoadDir = inDir;
	
	ioDivMapCont->MLBC[inBlankNo].MLBS.Block[0] = inBlock1;
	ioDivMapCont->MLBC[inBlankNo].MLBS.Block[1] = inBlock2;
	ioDivMapCont->MLBC[inBlankNo].MLBS.Index[0] = inIdx1;
	ioDivMapCont->MLBC[inBlankNo].MLBS.Index[1] = inIdx2;
	
	ioDivMapCont->MLBC[inBlankNo].MLBS.Node[0] = ioDivMapCont->BlockNodeList[inIdx1];
	ioDivMapCont->MLBC[inBlankNo].MLBS.Node[1] = ioDivMapCont->BlockNodeList[inIdx2];

	ioDivMapCont->MLBC[inBlankNo].MLBS.TotalCount = 0;
	ioDivMapCont->MLBC[inBlankNo].MLBS.BlockLoadOK = FALSE;

	//�ғ����[�_�[���Ȃ��Ȃ烍�[�h�����N�G�X�g����
	//�ғ����[�_�[������Ȃ�A�o�^��������
	if (ioDivMapCont->MovingNum == 0){		
		ioDivMapCont->LoadSeq = DML_LOAD_BLOCK;
	}

	ioDivMapCont->BlockNodeList[inIdx1]->BlockIndex = inBlock1;
	ioDivMapCont->BlockNodeList[inIdx2]->BlockIndex = inBlock2;
	
	ioDivMapCont->MovingNum++;
	ioDivMapCont->BlankNo = (ioDivMapCont->BlankNo+1)%2;
	
	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�֐�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void DivMapLoadMain(FIELDSYS_WORK *fsys, DMC_PTR ioDivMapCont)
{
#ifdef DEBUG_ONLY_FOR_saitou
static test_sync_count_flg = FALSE;
static test_sync_counter = 0;
#endif
	u8 my_dir;
	MAP_LOAD_BLOCK_ST *mlbs;
	DIV_MAP_CHECK	*dmc;
	mlbs = &ioDivMapCont->MLBC[ioDivMapCont->NowMovingNo].MLBS;
	dmc = &ioDivMapCont->MapCheck;
#ifdef DEBUG_ONLY_FOR_saitou	
if (test_sync_count_flg){
	test_sync_counter++;
}
#endif
	if (dmc->Valid == TRUE){

		//���݈ړ���
		if (dmc->Moving){	//�����W�ƌ��ݍ��W�̍������A1�O���b�h�ɂȂ������𔻒�
			
			GF_ASSERT((*dmc->SmallVal)<=(*dmc->LargeVal)&&"ERROR:�l�s��");

			if ( (*dmc->LargeVal) - (*dmc->SmallVal) >= (FX32_ONE *ONE_GRID_SIZE) ){
				int grid_x,grid_z;
				//�����͊O���l��M�p���čs���܂�
				//1�O���b�h�ړ�����
				GetGridXZ(dmc->TargetPoint->x, dmc->TargetPoint->z, &grid_x, &grid_z);	
				UpdateNowData(grid_x, grid_z, ioDivMapCont);//�����f�[�^�X�V
				dmc->OldPoint = *dmc->TargetPoint;
                if(!(dmc->OldPoint.z%(FX32_ONE*8)==0)){  // �ʐM���ɂ̓G���[�ɂ���
                    if(CommStateSetError(COMM_ERROR_RESET_SAVEPOINT)){
                        return;
                    }
                }
				GF_ASSERT(dmc->OldPoint.z%(FX32_ONE*8)==0&&"�O���b�h�P�ʂ̈ړ����Ȃ���Ă��Ȃ�");
				dmc->Moving = FALSE;
				dmc->LargeVal = NULL;
				dmc->SmallVal = NULL;
			}
		}else{	//�o�C���h����Ă�����W�̓����n�߂����o
			if ( (dmc->OldPoint.x != dmc->TargetPoint->x)&&
					(dmc->OldPoint.z != dmc->TargetPoint->z) ){
				//���A�������ω��̓G���[�Ƃ���
				GF_ASSERT(0&&"ERROR�FXZ�����ω�������");				
			}else if ( (dmc->OldPoint.x == dmc->TargetPoint->x)&&
						(dmc->OldPoint.z == dmc->TargetPoint->z) ){
				;//�������Ȃ�
			}else{	//XZ�ǂ��炩����̕ω����������ꍇ
				dmc->Moving = TRUE;
				if (dmc->OldPoint.x != dmc->TargetPoint->x){	//X���ω�
					if (dmc->OldPoint.x > dmc->TargetPoint->x){
						//�����W�̂ق����傫���������Ɉړ�
						dmc->LargeVal = &dmc->OldPoint.x;
						dmc->SmallVal = &dmc->TargetPoint->x;
						dmc->Dir = MAP_LOAD_LEFT;
					}else{
						//�E�Ɉړ�
						dmc->LargeVal = &dmc->TargetPoint->x;
						dmc->SmallVal = &dmc->OldPoint.x;
						dmc->Dir = MAP_LOAD_RIGHT;
					}
                    if(!(dmc->OldPoint.x%(FX32_ONE*8)==0)){  // �ʐM���ɂ̓G���[�ɂ���
                        if(CommStateSetError(COMM_ERROR_RESET_SAVEPOINT)){
                            return;
                        }
                    }
                    GF_ASSERT(dmc->OldPoint.x%(FX32_ONE*8)==0&&"��x���W���O���b�h�P�ʂ̈ړ��ł͂Ȃ�");
				}
				else{	//Z���ω�
					if (ioDivMapCont->MapCheck.OldPoint.z >	ioDivMapCont->MapCheck.TargetPoint->z){
						//�����W�̂ق����傫��������Ɉړ�
						dmc->LargeVal = &dmc->OldPoint.z;
						dmc->SmallVal = &dmc->TargetPoint->z;
						dmc->Dir = MAP_LOAD_UP;
					}else{
						//���Ɉړ�
						dmc->LargeVal = &dmc->TargetPoint->z;
						dmc->SmallVal = &dmc->OldPoint.z;
						dmc->Dir = MAP_LOAD_DOWN;
					}
                    if(!(dmc->OldPoint.z%(FX32_ONE*8)==0)){  // �ʐM���ɂ̓G���[�ɂ���
                        if(CommStateSetError(COMM_ERROR_RESET_SAVEPOINT)){
                            return;
                        }
                    }
					GF_ASSERT(dmc->OldPoint.z%(FX32_ONE*8)==0&&"��z���W���O���b�h�P�ʂ̈ړ��ł͂Ȃ�");
				}
				//���[�h���N�G�X�g
				DivMapLoad_UpdateBlockData(dmc->Dir,ioDivMapCont);
			}
		}
	
	}//end if(dmc->Valid == TRUE)
	
	switch(ioDivMapCont->LoadSeq){
	case DML_LOAD_BLOCK:	//�u���b�N�̃��[�h
#ifdef DIV_MAP_LOAD_DEBUG
		OS_Printf("���[�h�J�n\n");
#endif
		///OS_Printf("���~�m�F%d\n",mlbs->Index[mlbs->TotalCount]);
		//���N�G�X�g���~���������Ă��Ȃ��Ȃ�A���[�h
		if (ioDivMapCont->LocalFreeIndexTable[mlbs->Index[mlbs->TotalCount]] == TRUE){
#ifdef DIV_MAP_LOAD_DEBUG			
			OS_Printf("������N�G�X�g���������Ă���̂ŁA���[�h���Ȃ�\n");
#endif
			;
		}else{
#ifdef DIV_MAP_LOAD_DEBUG
			OS_Printf("�g�[�^��%d��,���[�J���C���f�b�N�X%d:���[�h\n",mlbs->TotalCount+1,mlbs->Index[mlbs->TotalCount]);
			OS_Printf("%d:���ݓǂݍ��݈ʒu\n",ioDivMapCont->NowMovingNo);
#endif
			ioDivMapCont->FuncList->DivLoadFunc(	mlbs->TotalCount,
												ioDivMapCont->MapResource,
												ioDivMapCont->World,
												ioDivMapCont->MapW,
												ioDivMapCont->MapH,
												ioDivMapCont,
												mlbs);
#ifdef DEBUG_ONLY_FOR_saitou			
			test_sync_count_flg = TRUE;
			test_sync_counter = 1;
#endif
		}
		mlbs->TotalCount++;
		
		ioDivMapCont->LoadSeq = DML_LOAD_WAIT;
		break;
	case DML_LOAD_WAIT:		//�u���b�N���[�h�I���҂�
		if (ioDivMapCont->LocalFreeIndexTable[mlbs->Index[mlbs->TotalCount-1]] == TRUE){
#ifdef DIV_MAP_LOAD_DEBUG
			OS_Printf("%d,%d:������N�G�X�g���������Ă���̂ŁA�������\n",mlbs->Index[mlbs->TotalCount-1],mlbs->TotalCount);
#endif
			LoadTaskStopReqestByMLBS(mlbs);
			ioDivMapCont->LocalFreeIndexTable[mlbs->Index[mlbs->TotalCount-1]] = FALSE;
		}
		if ((mlbs->TotalCount <=2)&&(CheckBlockLoadTaskCounter(&mlbs->TaskCnter) == TRUE)){
			if (mlbs->TotalCount>=2){
#ifdef DIV_MAP_LOAD_DEBUG
				OS_Printf("%d:2�ߓǂݍ��ݏI���\n",mlbs->TotalCount);
#endif
				mlbs->BlockLoadOK = TRUE;	//�ǂݍ��ݏI��
				//2�̃u���b�N���[�h���I�������̂ŁA�ςݍ��܂�Ă���u���b�N���[�h�����邩�𒲂ׂ�
				//�ς܂�Ă���ꍇ�͏���������
///		MapLoadCont.MLBC[MapLoadCont.NowMovingTaskNo].MLBS.Node[0]->DrawOKFlg = TRUE;
///		MapLoadCont.MLBC[MapLoadCont.NowMovingTaskNo].MLBS.Node[1]->DrawOKFlg = TRUE;
				
			}else{
#ifdef DIV_MAP_LOAD_DEBUG
				OS_Printf("%d:1�ߓǂݍ��ݏI���\n",mlbs->TotalCount);
#endif
				ioDivMapCont->LoadSeq = DML_LOAD_BLOCK;
#ifdef DIV_MAP_LOAD_DEBUG	
				OS_Printf("1�ڃ��[�h�I�@mlbs->LoadTime = %d\n",mlbs->DebugLoadTimer);
#endif				
			}
#if 0			
			//�ǂݍ��݂��I�������̂ŃA�[�J�C�u�n���h�������
			if (ioDivMapCont->ArcHandle != NULL){
				ArchiveDataHandleClose( ioDivMapCont->ArcHandle );
				ioDivMapCont->ArcHandle = NULL;
			}
#endif			
			if (/*mlbs->Node[mlbs->TotalCount-1]->FloorResFile != NULL*/mlbs->Node[mlbs->TotalCount-1]->DrawOKFlg == TRUE){
				NNSG3dResMdlSet* pMdlSet = NNS_G3dGetMdlSet(mlbs->Node[mlbs->TotalCount-1]->FloorResFile);
				NNSG3dResMdl* model = NNS_G3dGetMdlByIdx(pMdlSet, 0);
				if (MAPRES_IsValidLight(ioDivMapCont->MapResource) == TRUE){
					//�O���[�o���X�e�[�g�g�p
					SetGlbLightMdl(model);
				}
			}
#ifdef DIV_CALL_BACK	
			//�����ŃR�[���o�b�N
			if (ioDivMapCont->CallBack!=NULL){
				//�}�g���b�N�X�T�C�Y�����āA�I�[�o�[���Ă�����R�[�����Ȃ�
				if (0<=mlbs->Node[mlbs->TotalCount-1]->BlockIndex &&
					mlbs->Node[mlbs->TotalCount-1]->BlockIndex<ioDivMapCont->MapW*ioDivMapCont->MapH){
					ioDivMapCont->CallBack(	ioDivMapCont->CallBackWork,
											mlbs->Node[mlbs->TotalCount-1]->BlockIndex,
											mlbs->Node[mlbs->TotalCount-1]->ObjDataList);
				}
			}
#endif
#ifdef DEBUG_ONLY_FOR_saitou			
			//���������V���N����\��
			OS_Printf("local_print ���[�h���v�V���N��%d\n",test_sync_counter);
			test_sync_counter = 0;
			test_sync_count_flg = FALSE;
#endif			
		}
		break;
	case DML_NONE:			//���������
		break;
	case DML_FREE_WAIT:		//�u���b�N���[�h����҂�
		if ( CheckBlockLoadTaskCounter(&mlbs->TaskCnter)==TRUE ){
			//�������[�h���Ď�����΁A�^�X�N�I�����m�F�ł���
			ioDivMapCont->MovingNum = 0;
#if 0			
			//�ǂݍ��݂��I�������̂ŃA�[�J�C�u�n���h�������
			if (ioDivMapCont->ArcHandle != NULL){
				ArchiveDataHandleClose( ioDivMapCont->ArcHandle );
				ioDivMapCont->ArcHandle = NULL;
			}
#endif			
		}
		break;
	}

	//�ғ����Ă�����̂��Ȃ��Ȃ��
	if (ioDivMapCont->MovingNum == 0){
		ioDivMapCont->NowMovingNo = 0;
		ioDivMapCont->BlankNo = 0;
		ioDivMapCont->LoadSeq = DML_NONE;		//�������V�[�P���X
		return;
	}

	//�u���b�N���[�h�I���Ď�
	if ( IsFinishedLoadBlock(ioDivMapCont) == TRUE){
		//�ғ��t���O�����Ƃ�
		ioDivMapCont->MLBC[ioDivMapCont->NowMovingNo].Moving = FALSE;

		//����u���b�N�}�[�L���O���N���A
		ClearLocalFreeIndexTable(ioDivMapCont);
		
		ioDivMapCont->MovingNum--;		//�Ǘ������Z
	
		ioDivMapCont->NowMovingNo = (ioDivMapCont->NowMovingNo+1)%2;	//�ғ��ԍ��X�V

		//�ғ��҂��u���b�N���[�h������Ȃ�A���[�h�J�n
		if (ioDivMapCont->MovingNum != 0){
#ifdef DIV_MAP_LOAD_DEBUG
			OS_Printf("�����[�h�J�n\n");
#endif
			//MapLoadCont.MLBC[MapLoadCont.NowMovingNo].MLBS.ReadStartOK = TRUE;

			ioDivMapCont->LoadSeq = DML_LOAD_BLOCK;		//���[�h�V�[�P���X

		}else{
			ioDivMapCont->NowMovingNo = 0;
			ioDivMapCont->BlankNo = 0;
			ioDivMapCont->LoadSeq = DML_NONE;		//�������V�[�P���X
		}

		//�X�g�b�N������ꍇ�͗D��I�ɓo�^
		if (ioDivMapCont->Stock.Valid == TRUE){
			BOOL rc;
			ioDivMapCont->Stock.Valid = FALSE;
			//�X�g�b�N��������A�ǂݍ��܂Ȃ��Ă������[�J���C���f�b�N�X�����肷��
			MarkLocalFreeIndexTableByDir(ioDivMapCont->Stock.LoadDir,ioDivMapCont);
			
			AddMapLoadForStock(ioDivMapCont);
		}
		
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �}�b�v���[�h�ǉ�
 *
 * @param	inBlock1	��1���[�h�u���b�N�C���f�b�N�X
 * @param	inBlock2	��2���[�h�u���b�N�C���f�b�N�X
 * @param	inIdx1		��1���[�h���[�J���C���f�b�N�X(0�`3)
 * @param	inIdx2		��2���[�h���[�J���C���f�b�N�X(0�`3)
 * @param	inDir		���[�h����
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void AddMapLoad( const int inBlock1,
						const int inBlock2,
						const u8 inIdx1,
						const u8 inIdx2,
						const u8 inDir,
						DMC_PTR ioDivMapCont)
{
	int i;
	u8 no;
	BOOL rc;
	
#ifdef DEBUG_ONLY_FOR_saitou
	if (ioDivMapCont->MovingNum>=2){
		OS_Printf("local_print 3��\n");
	}
#endif
	GF_ASSERT((ioDivMapCont->Stock.Valid != TRUE)&&"�X�g�b�N�����܂��Ă�");
	//���݃��N�G�X�g�̂������Ă��郍�[�h�����Ɖғ����^�X�N�̕������r
	if ( CompLoadDirection(inDir, ioDivMapCont, &no) == TRUE ){
		//���[�h�����ƃ��N�G�X�g�����������΂Ȃ�΁A���[�h���~
#ifdef DIV_MAP_LOAD_DEBUG
		OS_Printf("no:%d",no);
#endif
		LoadStopReqest(ioDivMapCont,no);
		//�󂫂��Ȃ��ꍇ
		if (ioDivMapCont->MovingNum>=2){
			ioDivMapCont->Stock.Valid = TRUE;
			ioDivMapCont->Stock.Block[0] = inBlock1;
			ioDivMapCont->Stock.Block[1] = inBlock2;
			ioDivMapCont->Stock.Index[0] = inIdx1;
			ioDivMapCont->Stock.Index[1] = inIdx2;
			ioDivMapCont->Stock.Node[0] = ioDivMapCont->BlockNodeList[inIdx1];
			ioDivMapCont->Stock.Node[1] = ioDivMapCont->BlockNodeList[inIdx2];
			ioDivMapCont->Stock.LoadDir = inDir;
			
			ioDivMapCont->BlockNodeList[inIdx1]->BlockIndex = inBlock1;
			ioDivMapCont->BlockNodeList[inIdx2]->BlockIndex = inBlock2;

		}else{
			rc = BlockLoadReqest(ioDivMapCont,inBlock1,inBlock2,inIdx1,inIdx2,ioDivMapCont->BlankNo,inDir);
			if (rc == FALSE){
				//�󂫂��Ȃ��ꍇ�i���N�G�X�g�����~�^�X�N���܂�3�ځj�A���N�G�X�g�ҋ@��Ԃɂ��Ƃ�
#ifdef DEBUG_ONLY_FOR_saitou
				OS_Printf("local_print ERROR:3��\n");
#endif				
			}
		}
	}else{
		//�����΂łȂ��ꍇ�A���N�G�X�g�ǉ�
		//�󂢂Ă���Ǘ��^�X�N�ɓo�^
		rc = BlockLoadReqest(ioDivMapCont,inBlock1,inBlock2,inIdx1,inIdx2,ioDivMapCont->BlankNo,inDir);
#ifdef DIV_MAP_LOAD_DEBUG
		OS_Printf("%d�Ƀ^�X�N�o�^\n",MapLoadCont.BlankNo);
#endif
		//�Ǘ��^�X�N�������ς��Ȃ̂ɁA���N�G�X�g�����������ꍇ�A�G���[�Ƃ��Ƃ�
		GF_ASSERT((rc==TRUE)&&"ERROR:�Ǘ��^�X�N�������ς�");
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �u���b�N�f�[�^�̉��(�ړ���)
 *
 * @param	inLocalIndex	//������郍�[�J���C���f�b�N�X�i0�`3�j
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FreeBlock(const u8 inLocalIndex, DMC_PTR outDivMapCont)
{
	outDivMapCont->BlockNodeList[inLocalIndex]->DrawOKFlg = FALSE;
	SetInvalidHeightData(outDivMapCont->BlockNodeList[inLocalIndex]->MapHeightInfo);
//	ClearFldMapMem(inLocalIndex, outDivMapCont->FldMapMem);
	
	//3DOBJ�f�[�^���(���ۂɂ́A�f�[�^����ł͂Ȃ��A�Ǘ����̃N���A)
	M3DO_CleanMap3DObjList(outDivMapCont->BlockNodeList[inLocalIndex]->ObjDataList);
	outDivMapCont->BlockNodeList[inLocalIndex]->BlockIndex = NON_BLOCK;

	//�A�g���r���[�g�N���A
	MI_CpuFillFast(outDivMapCont->BlockNodeList[inLocalIndex]->Attribute, 0xffffffff, 2*32*32 );
	
	//����u���b�N�}�[�L���O
	outDivMapCont->LocalFreeIndexTable[inLocalIndex] = TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �u���b�N�f�[�^���[�h�̓o�^
 *
 * @param	inCount		�o�^�ꏊ�i0�n�q1�j
 * @param	*ioMLBS		���[�h�u���b�N�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FreeAndMoveNode(const u8 inFreeNo1,
							const u8 inFreeNo2,
							const u8 inMoveNo1,
							const u8 inMoveNo2,
							DMC_PTR ioDivMapCont)
{
	BLOCK_NODE *TempNode[2];
	//inFreeNo1,inFreeNo2�����
	FreeBlock(inFreeNo1,ioDivMapCont);
	FreeBlock(inFreeNo2,ioDivMapCont);
	//��������m�[�h��1���ދ�
	TempNode[0] = ioDivMapCont->BlockNodeList[inFreeNo1];
	TempNode[1] = ioDivMapCont->BlockNodeList[inFreeNo2];
	//�c���2�̃e�[�u�����ړ�
	ioDivMapCont->BlockNodeList[inFreeNo1] = ioDivMapCont->BlockNodeList[inMoveNo1];
	ioDivMapCont->BlockNodeList[inFreeNo2] = ioDivMapCont->BlockNodeList[inMoveNo2];
	//�ދ������m�[�h��V�ǂݍ��݈ʒu�ɖ߂�
	ioDivMapCont->BlockNodeList[inMoveNo1] = TempNode[0];
	ioDivMapCont->BlockNodeList[inMoveNo2] = TempNode[1];
}

//--------------------------------------------------------------------------------------------
/**
 * �u���b�N�X�V
 *
 * @param	inBlockIndex	�u���b�N�C���f�b�N�X
 * @param	inDirection		�X�V����
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void UpdateBlockList(const int inBlockIndex, const u8 inDirection, DMC_PTR ioDivMapCont)
{
	u8 i,j;
	int block1,block2;
	int old_block;
	int idx1,idx2;
	switch(inDirection){
	case MAP_LOAD_UP:	//���@����Ɉړ�(2��0�A3��1)
		//2,3���������0,1���ړ�
		FreeAndMoveNode(2,3,0,1,ioDivMapCont);

		//���@�̂���u���b�N�C���f�b�N�X���L�[�ɂ��āA0,1�ɂ͂���u���b�N���Z�o
		//2��0�A3��1�ŏꍇ����

		if (/*�����ɂ����ꍇ*/ioDivMapCont->NowPosInBlock == 2){
			block1 = inBlockIndex - ioDivMapCont->MapW;
			block2 = inBlockIndex - ioDivMapCont->MapW - 1;
			idx1 = 1;
			idx2 = 0;
			//�������`�F�b�N
			if (block1<0){	//�͈͊O
				//�^��̃u���b�N�̓}�g���b�N�X���ɂ���͂�
				block1 = NON_BLOCK;
				block2 = NON_BLOCK;
			}else{
				//�Q�ڂ̃u���b�N�̓}�g���N�X���A���ǂݍ��񂾂Q�u���b�N�́A�����s�ɂ���͂�
				if ( (block2<0)||(!CheckRowBlockIndex(block1,block2,ioDivMapCont->MapW)) ){	//�͈͊O
					block2 = NON_BLOCK;
				}
			}
		}else if(/*�E���ɂ����ꍇ*/ioDivMapCont->NowPosInBlock == 3){
			block1 = inBlockIndex - ioDivMapCont->MapW;
			block2 = inBlockIndex - ioDivMapCont->MapW + 1;
			idx1 = 0;
			idx2 = 1;
			//�������`�F�b�N
			if (block1<0){	//�͈͊O
				//�^��̃u���b�N�̓}�g���b�N�X���ɂ���͂�
				block1 = NON_BLOCK;
				block2 = NON_BLOCK;
			}else{
				//�ǂݍ��񂾂Q�u���b�N�́A�����s�ɂ���͂�
				if ( !CheckRowBlockIndex(block1,block2,ioDivMapCont->MapW) ){	//�͈͊O
					block2 = NON_BLOCK;
				}
			}
		}else{
			GF_ASSERT(0&&"ERROR:��ړ��u���b�N�v�Z���s");
		}
/**
		//�������`�F�b�N
		if ( (block1<0)||(ioDivMapCont->MapW*ioDivMapCont->MapH<=block1) ){
			//�͈͊O
			block1 = -1;
			block2 = -2;
		}
*/
		//0,1�̐V�K���[�h
		AddMapLoad(block1,block2,idx1,idx2,inDirection,ioDivMapCont);
		
		break;
	case MAP_LOAD_LEFT:	//���@�����Ɉړ�
		//1,3���������0,2���ړ�
		FreeAndMoveNode(1,3,0,2,ioDivMapCont);
		
		//���@�̂���u���b�N�C���f�b�N�X���L�[�ɂ��āA0,2�ɂ͂���u���b�N���Z�o
		//1��0�A3��2�ŏꍇ����

		if (/*�E��ɂ����ꍇ*/ioDivMapCont->NowPosInBlock == 1){
			block1 = inBlockIndex - 1;
			block2 = inBlockIndex - ioDivMapCont->MapW - 1;
			idx1 = 2;
			idx2 = 0;
			//���@�̂���c�̃u���b�N�C���f�b�N�X��ۑ�(���ړ��̂�)
///			old_block = ioDivMapCont->BlockNodeList[3]->BlockIndex;
			//�������`�F�b�N
			if ( (block1<0)||(!CheckRowBlockIndex(block1,inBlockIndex,ioDivMapCont->MapW)) ){
				//�ǂݍ��񂾍��ׂ̃u���b�N�́A�}�g���N�X���A�����܂ł����u���b�N�Ɠ����s�̂͂�
				block1 = NON_BLOCK;
				block2 = NON_BLOCK;
			}
			if ( (block2<0)||
					(!CheckColumnBlockIndex(block1,block2,ioDivMapCont->MapW)) ){
				//2�ڂ̃u���b�N�́A�}�g���N�X���A���ǂݍ��񂾂Q�u���b�N�́A������ɂ���͂�
				block2 = NON_BLOCK;
			}
		}else if(/*�E���ɂ����ꍇ*/ioDivMapCont->NowPosInBlock == 3){
			block1 = inBlockIndex - 1;
			block2 = inBlockIndex + ioDivMapCont->MapW - 1;
			idx1 = 0;
			idx2 = 2;
			//���@�̂���c�̃u���b�N�C���f�b�N�X��ۑ�(���ړ��̂�)
///			old_block = ioDivMapCont->BlockNodeList[1]->BlockIndex;
			//�������`�F�b�N
			if ( (block1<0)||(!CheckRowBlockIndex(block1,inBlockIndex,ioDivMapCont->MapW)) ){
				//�ǂݍ��񂾍��ׂ̃u���b�N�́A�}�g���N�X���A�����܂ł����u���b�N�Ɠ����s�̂͂�
				block1 = NON_BLOCK;
				block2 = NON_BLOCK;
			}
			if ( (ioDivMapCont->MapW*ioDivMapCont->MapH<=block2)||
					(!CheckColumnBlockIndex(block1,block2,ioDivMapCont->MapW)) ){
				//2�ڂ̃u���b�N�́A�}�g���N�X���A���ǂݍ��񂾂Q�u���b�N�́A������ɂ���͂�
				block2 = NON_BLOCK;
			}
		}else{
			GF_ASSERT(0&&"ERROR:���ړ��u���b�N�v�Z���s");
		}
		AddMapLoad(block1,block2,idx1,idx2,inDirection,ioDivMapCont);
/**		
#ifdef DIV_MAP_LOAD_DEBUG
		OS_Printf("load_block:%d,%d\nold:%d,%d\n",block1,block2,old_block1,old_block2);
#endif
		//�V�K�ǂݍ��݃u���b�N�̐��������`�F�b�N(���ړ��̂�)
		if (CheckSideBlockIndex(block1,old_block,ioDivMapCont->MapW)==TRUE){
			AddMapLoad(block1,block2,idx1,idx2,inDirection,ioDivMapCont);
		}else{
#ifdef	DEBUG_ONLY_FOR_saitou			
			OS_Printf("local_print ��ʍ��[�Ȃ̂Ń��[�h���Ȃ�\n");
#endif			
			ioDivMapCont->LocalFreeIndexTable[1] = FALSE;
			ioDivMapCont->LocalFreeIndexTable[3] = FALSE;
		}
*/		
		break;
	case MAP_LOAD_RIGHT: //���@���E�Ɉړ�
		//0,2���������1,3���ړ�
		FreeAndMoveNode(0,2,1,3,ioDivMapCont);
		
		//���@�̂���u���b�N�C���f�b�N�X���L�[�ɂ��āA1,3�ɂ͂���u���b�N���Z�o
		//0��1�A2��3�ŏꍇ����

		if (/*����ɂ����ꍇ*/ioDivMapCont->NowPosInBlock == 0){
			block1 = inBlockIndex + 1;
			block2 = inBlockIndex - ioDivMapCont->MapW + 1;
			idx1 = 3;
			idx2 = 1;
			//���@�̂���c�̃u���b�N�C���f�b�N�X��ۑ�(���ړ��̂�)
///			old_block = ioDivMapCont->BlockNodeList[2]->BlockIndex;
			//�������`�F�b�N
			if ( (ioDivMapCont->MapW*ioDivMapCont->MapH<=block1)||
					(!CheckRowBlockIndex(block1,inBlockIndex,ioDivMapCont->MapW)) ){
				//�ǂݍ��񂾉E�ׂ̃u���b�N�́A�}�g���N�X���A�����܂ł����u���b�N�Ɠ����s�̂͂�
				block1 = NON_BLOCK;
				block2 = NON_BLOCK;
			}
			if ( (ioDivMapCont->MapW*ioDivMapCont->MapH<=block2)||
					(!CheckColumnBlockIndex(block1,block2,ioDivMapCont->MapW)) ){
				//2�ڂ̃u���b�N�̓}�g���N�X���A���ǂݍ��񂾂Q�u���b�N�́A������ɂ���͂�
				block2 = NON_BLOCK;
			}
		}else if(/*�����ɂ����ꍇ*/ioDivMapCont->NowPosInBlock == 2){
			block1 = inBlockIndex + 1;
			block2 = inBlockIndex + ioDivMapCont->MapW + 1;
			idx1 = 1;
			idx2 = 3;
			//���@�̂���c�̃u���b�N�C���f�b�N�X��ۑ�(���ړ��̂�)
///			old_block = ioDivMapCont->BlockNodeList[0]->BlockIndex;
			//�������`�F�b�N
			if ( (ioDivMapCont->MapW*ioDivMapCont->MapH<=block1)||
					(!CheckRowBlockIndex(block1,inBlockIndex,ioDivMapCont->MapW)) ){
				//�ǂݍ��񂾉E�ׂ̃u���b�N�́A�}�g���N�X���A�����܂ł����u���b�N�Ɠ����s�̂͂�
				block1 = NON_BLOCK;
				block2 = NON_BLOCK;
			}
			if ( (block2<0)||
					(!CheckColumnBlockIndex(block1,block2,ioDivMapCont->MapW)) ){
				//2�ڂ̃u���b�N�̓}�g���N�X���A���ǂݍ��񂾂Q�u���b�N�́A������ɂ���͂�
				block2 = NON_BLOCK;
			}
		}else{
			OS_Printf("ERROR:�E�ړ��u���b�N�v�Z���s\n");
		}
		AddMapLoad(block1,block2,idx1,idx2,inDirection,ioDivMapCont);
/**		
		//�V�K�ǂݍ��݃u���b�N�̐��������`�F�b�N(���ړ��̂�)
#ifdef DIV_MAP_LOAD_DEBUG
		OS_Printf("load_block:%d,%d\nold:%d,%d\n",block1,block2,old_block1,old_block2);
#endif
		
		if (CheckSideBlockIndex(block1,old_block,ioDivMapCont->MapW)==TRUE){
			AddMapLoad(block1,block2,idx1,idx2,inDirection,ioDivMapCont);
		}else{
#ifdef	DEBUG_ONLY_FOR_saitou		
			OS_Printf("local_print ��ʉE�[�Ȃ̂Ń��[�h���Ȃ�\n");
#endif			
			ioDivMapCont->LocalFreeIndexTable[0] = FALSE;
			ioDivMapCont->LocalFreeIndexTable[2] = FALSE;
		}
*/		
		break;
	case MAP_LOAD_DOWN: //���@�����Ɉړ�
		//0,1���������2,3���ړ�
		FreeAndMoveNode(0,1,2,3,ioDivMapCont);
		
		//���@�̂���u���b�N�C���f�b�N�X���L�[�ɂ��āA2,3�ɂ͂���u���b�N���Z�o
		//0��2�A1��3�ŏꍇ����

		if (/*����ɂ����ꍇ*/ioDivMapCont->NowPosInBlock == 0){
			block1 = inBlockIndex + ioDivMapCont->MapW;
			block2 = inBlockIndex + ioDivMapCont->MapW - 1;
			idx1 = 3;
			idx2 = 2;
			//�������`�F�b�N
			if (ioDivMapCont->MapW*ioDivMapCont->MapH<=block1){	//�͈͊O
				//�^���u���b�N�̓}�g���N�X���ɂ���͂�
				block1 = NON_BLOCK;
				block2 = NON_BLOCK;
			}else{
				//�ǂݍ��񂾂Q�u���b�N�́A�����s�ɂ���͂�
				if ( !CheckRowBlockIndex(block1,block2,ioDivMapCont->MapW) ){	//�͈͊O
					block2 = NON_BLOCK;
				}
			}
		}else if(/*�E��ɂ����ꍇ*/ioDivMapCont->NowPosInBlock == 1){
			block1 = inBlockIndex + ioDivMapCont->MapW;
			block2 = inBlockIndex + ioDivMapCont->MapW + 1;
			idx1 = 2;
			idx2 = 3;
			//�������`�F�b�N
			if (ioDivMapCont->MapW*ioDivMapCont->MapH<=block1){	//�͈͊O
				//�^���u���b�N�̓}�g���N�X���ɂ���͂�
				block1 = NON_BLOCK;
				block2 = NON_BLOCK;
			}else{
				//2�߂̃u���b�N�̓}�g���N�X���ŁA���ǂݍ��񂾂Q�u���b�N�́A�����s�ɂ���͂�
				if ( (ioDivMapCont->MapW*ioDivMapCont->MapH<=block2)||
						(!CheckRowBlockIndex(block1,block2,ioDivMapCont->MapW)) ){	//�͈͊O
					block2 = NON_BLOCK;
				}
			}
		}else{
			GF_ASSERT(0&&"ERROR:���ړ��u���b�N�v�Z���s");
		}
/**		
		//�������`�F�b�N
		if ( (block1<0)||(ioDivMapCont->MapW*ioDivMapCont->MapH<=block1) ){
			//�͈͊O
			block1 = -1;
			block2 = -2;
		}
*/
		//2,3�̐V�K���[�h
		AddMapLoad(block1,block2,idx1,idx2,inDirection,ioDivMapCont);
		break;
	default:
		GF_ASSERT(0&&"ERROR:�u���b�N�̉���ƍ쐬�Ɏ��s");
		break;
	};
#ifdef DEBUG_ONLY_FOR_saitou
	OS_Printf("local_print_new_4_block:%d,%d,%d,%d",
			ioDivMapCont->BlockNodeList[0]->BlockIndex,
			ioDivMapCont->BlockNodeList[1]->BlockIndex,
			ioDivMapCont->BlockNodeList[2]->BlockIndex,
			ioDivMapCont->BlockNodeList[3]->BlockIndex );
#endif	
}

//--------------------------------------------------------------------------------------------
/**
 * �u���b�N�`��
 *
 * @param	inLocalIndex	�`�惍�[�J���C���f�b�N�X(0�`3)
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void DrawBlock(	const u8 inLocalIndex,
						DMC_CONST_PTR inDivMapCont,
						const GLST_DATA_PTR	glst_data)
{
	VecFx32 trans = {0, 0, 0};
	CalcMapOffset3D(	inDivMapCont->BlockNodeList[inLocalIndex]->BlockIndex,
						inDivMapCont->MapW,
						inDivMapCont->World,
						&trans);

//���R�c�`��
	if (inDivMapCont->BlockNodeList[inLocalIndex]->DrawOKFlg == TRUE){
		VecFx32 scale = {FX32_ONE, FX32_ONE, FX32_ONE};
		MtxFx33 rot	  = {FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};
#ifdef PM_DEBUG		
		if (DebugOutRangeFlg == TRUE){
			simple_3DModelDraw(&(inDivMapCont->BlockNodeList[inLocalIndex]->FloorData),
								&trans,
								&rot,
								&scale);
		}else{
			if (GetInvalidHeightDataFlg(inDivMapCont->BlockNodeList[inLocalIndex]->MapHeightInfo)
																						== TRUE){
				simple_3DModelDraw(&(inDivMapCont->BlockNodeList[inLocalIndex]->FloorData),
									&trans,
									&rot,
									&scale);
			}
		}
#else
		simple_3DModelDraw(&(inDivMapCont->BlockNodeList[inLocalIndex]->FloorData),
							&trans,
							&rot,
							&scale);
#endif
	}

	if(inDivMapCont->BlockNodeList[inLocalIndex]->DrawOKFlg == TRUE){
			M3DO_DrawMap3DObj(	&trans,
								inDivMapCont->MapResource,
								MAPRES_IsValidLight(inDivMapCont->MapResource),
								glst_data,
								inDivMapCont->BlockNodeList[inLocalIndex]->ObjDataList);
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �O���b�h�i���o�[����u���b�N�C���f�b�N�X���擾
 *
 * @param	inGridNo	�O���b�h�i���o�[
 *
 * @return	int			�u���b�N�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
static int GetBlockIdxFromGridNo(const u32 inGridNo, const int inMapW, const int inMapGridW)
{
	u32	grid_x,grid_z;
	u32 block_x,block_z;
	int block_index;
	
	grid_x = inGridNo%inMapGridW;
	grid_z = inGridNo/inMapGridW;
	block_x = grid_x / BLOCK_GRID_SIZE_X;
	block_z = grid_z / BLOCK_GRID_SIZE_Z;

	block_index = block_x+block_z*inMapW;
	return block_index;
}

//--------------------------------------------------------------------------------------------
/**
 * �O���b�h���W�����ɁA���ݗ����Ă���O���b�h�i���o�[��Ԃ�
 *
 * @param	inGeidX		�O���b�h���W�w
 * @param	inGridZ		�O���b�h���W�y
 *
 * @return	int	�O���b�h�i���o�[
 */
//--------------------------------------------------------------------------------------------
static int CalcGridNoFromGridXZ(const int inGridX, const int inGridZ, const int inMapGridW)
{
	int grid_no;
	grid_no = inGridX + (inGridZ * inMapGridW);
	return grid_no;
}

//--------------------------------------------------------------------------------------------
/**
 * �G���A�O���b�h�i���o�[����G���A�u���b�N�C���f�b�N�X���Z�o
 *
 * @param	inGridIndex		�O���b�h�i���o�[
 *
 * @return	u32				�u���b�N�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
static u32 GetBlockIndexFromGridNo(const u32 inGridNo, const int inMapW, const int inMapGridW)
{
	u32	grid_x,grid_z;
	u32 block_x,block_z;
	u32 block_index;
	
	grid_x = inGridNo%inMapGridW;
	grid_z = inGridNo/inMapGridW;
	block_x = grid_x / BLOCK_GRID_SIZE_X;
	block_z = grid_z / BLOCK_GRID_SIZE_Z;

	block_index = block_x+block_z*inMapW;
	return block_index;
}

//--------------------------------------------------------------------------------------------
/**
 * �u���b�N���ʒu���烍�[�J���C���f�b�N�X���v�Z�i0�`3�j
 *
 * @param	inPosInBlock	�u���b�N���ʒu(0�`3)
 *
 * @return	u8				���[�J���C���f�b�N�X�i0�`3�j
 */
//--------------------------------------------------------------------------------------------
static u8 CalcLocalIdxFromPosInBlock(const u8 inPosInBlock)
{
	//
	if (inPosInBlock == 0){
		return 3;
	}else if (inPosInBlock == 1){
		return 2;
	}else if(inPosInBlock == 2){
		return 1;
	}else if (inPosInBlock == 3){
		return 0;
	}else{
		GF_ASSERT(0&&"ERROR:�u���b�N���ʒu���s��");
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �i�����Ƃ��Ă��������1�O���b�h��̃O���b�h�i���o�[���擾����
 *
 * @param	inDirection		����
 *
 * @return	u32				�O���b�h�i���o�[
 */
//--------------------------------------------------------------------------------------------
static u32 GetNextGridNo(	const u8 inDirection,
							const int inMapH,
							const int inMapGridW,
							const int inNowGridNo)
{
	u32 grid_next;
	u32 next_block;
	int check;
	
	//���݃O���b�h��������ɂ��킹�āA���O���b�h���v�Z
	switch(inDirection){
	case  MAP_LOAD_RIGHT:		//�E
		check = (inNowGridNo%inMapGridW)+1;
		if ( check >= inMapGridW ){
			OS_Printf("ERROR:EREA_RIGHT_OVER!!\n");
			return inNowGridNo;
		}
		grid_next = inNowGridNo + 1;	
		break;
	case MAP_LOAD_DOWN:			//��
		check = inNowGridNo+inMapGridW;
		if (check >= inMapH*BLOCK_GRID_SIZE_Z*inMapGridW){
			OS_Printf("ERROR:EREA_DOWN_OVER!!\n");
			return inNowGridNo;
		}
		grid_next = inNowGridNo + inMapGridW;
		break;
	case MAP_LOAD_LEFT:			//��
		check = (inNowGridNo%inMapGridW)-1;
		if ( check < 0 ){
			OS_Printf("ERROR:EREA_LEFT_OVER!!\n");
			return inNowGridNo;
		}
		grid_next = inNowGridNo - 1;
		break;
	case MAP_LOAD_UP:			//��
		check = inNowGridNo-inMapGridW;
		if (check < 0 ){
			OS_Printf("ERROR:EREA_UP_OVER!!\n");
			return inNowGridNo;
		}
		grid_next = inNowGridNo - inMapGridW;
		break;
	default:
		GF_ASSERT(0&&"ERROR:NO_DIRECTION!!");
		return 0;
	}
	
	return  grid_next;
}


//--------------------------------------------------------------------------------------------
/**
 * �i�s�������疢���̃u���b�N���ʒu���擾(�u���b�N�ȓ��ɂ���Ƃ��̂ݎg�p)
 *
 * @param	inDirection		����
 *
 * @return	u8				�u���b�N���ʒu(0�`3)
 */
//--------------------------------------------------------------------------------------------
static u8 GetNextPosInBlock(const u8 inDirection, const int inNowPosInBlock)
{
	u8 pos;
	switch(inDirection){
	case MAP_LOAD_UP:
		pos = inNowPosInBlock-2;
		break;
	case MAP_LOAD_DOWN:
		pos = inNowPosInBlock+2;
		break;
	case MAP_LOAD_LEFT:
		pos = inNowPosInBlock-1;
		break;
	case MAP_LOAD_RIGHT:
		pos = inNowPosInBlock+1;
		break;
	}
	return pos;
}

//--------------------------------------------------------------------------------------------
/**
 * ���[�J���C���f�b�N�X���X�V
 *
 * @param	inDirection		�X�V����
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void UpdateNowLocalIndexForAfterLoad(const u8 inDirection,
											const int inNowPosInBlock,
											u8 *outNowLocalIndex)
{
	u8 pos;
	u8 local_index;
	
	pos = GetNextPosInBlock(inDirection,inNowPosInBlock);
	
	if (inNowPosInBlock<pos){
		if (pos - inNowPosInBlock == 1){
			local_index = (*outNowLocalIndex)-1;			//�E
		}else if(pos - inNowPosInBlock == 2){
			local_index = (*outNowLocalIndex)-2;			//��
		}else{
			GF_ASSERT(0&&"ERROR:LOCAL_INDEX_ERROR!");
		}
	}else if(inNowPosInBlock>pos){
		if (inNowPosInBlock - pos == 1){
			local_index = (*outNowLocalIndex)+1;			//�E
		}else if(inNowPosInBlock - pos == 2){
			local_index = (*outNowLocalIndex)+2;			//��
		}else{
			GF_ASSERT(0&&"ERROR:LOCAL_INDEX_ERROR!");
		}
	}else{
		//���[�J���C���f�b�N�X�̍X�V�Ȃ�;
		GF_ASSERT(0&&"ERROR:LOCAL_INDEX_NO_UPDATE!");
	}

	(*outNowLocalIndex) = local_index;
}

//--------------------------------------------------------------------------------------------
/**
 * �����΂̕�����Ԃ�
 *
 * @param	inDir	�w�����
 *
 * @return	u8		�w��̋t����
 */
//--------------------------------------------------------------------------------------------
static u8 GetRevDir(const u8 inDir)
{
	switch(inDir){
	case MAP_LOAD_UP:
		return MAP_LOAD_DOWN;
	case MAP_LOAD_DOWN:
		return MAP_LOAD_UP;
	case MAP_LOAD_RIGHT:
		return MAP_LOAD_LEFT;
	case MAP_LOAD_LEFT:
		return MAP_LOAD_RIGHT;
	default:
		GF_ASSERT(0&&"ERROR:�����͎��ʂł��Ȃ�");
		return 0;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ���[�h�����Ɖғ������[�_�̕������r
 *
 * @param	inDir	����
 * @param	*outNo	�o�^�ԍ��i0�n�q1�j
 *
 * @return	BOOL	�Ε����̗L��
 */
//--------------------------------------------------------------------------------------------
static BOOL CompLoadDirection(const u8 inDir, DMC_CONST_PTR inDivMapCont, u8* outNo)
{
	int i;
#ifdef DIV_MAP_LOAD_DEBUG	
	OS_Printf("��r����%d\n",inDir);
#endif	
	//���݃��N�G�X�g�̂������Ă��郍�[�h�����Ɖғ����^�X�N�̕������r
	for (i=0;i<2;i++){
#ifdef DIV_MAP_LOAD_DEBUG		
		OS_Printf("�^�X�N�Ǘ�����%d",inDivMapCont->MLBC[i].LoadDir);
#endif
		//�^�X�N�ғ����H
		if (inDivMapCont->MLBC[i].Moving == TRUE){
			if (GetRevDir(inDir) == inDivMapCont->MLBC[i].LoadDir){
				*outNo = i;
				return TRUE;	//�Ε�����������
			}
		}
	}

	//�Ε������Ȃ�����
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �X�g�b�N�p�u���b�N���[�h���N�G�X�g
 * ���[�h���E�Ńu���b�N�f�[�^��o�^�����ہA�������ς܂�Ă��āA���[�h�������ɂł��Ȃ��Ƃ��f�[�^���X�g�b�N����܂�
 * ���̃X�g�b�N���ꂽ�f�[�^���������鏈��
 * 
 *
 * @param	*inStock	�X�g�b�N�f�[�^
 * @param	inBlankNo	�o�^�󂫔ԍ�
 *
 * @return	BOOL	�o�^�����L��	TRUE:�����@FALSE:���s
 */
//--------------------------------------------------------------------------------------------
static BOOL BlockLoadReqestForStock(DMC_PTR ioDivMapCont)
{
	STOCK_LOAD_DATA *stock = &ioDivMapCont->Stock;
	
	if (ioDivMapCont->MLBC[ioDivMapCont->BlankNo].Moving != FALSE){
		//�ғ����^�X�N�ɓo�^���悤�Ƃ��Ă���̂ŃG���[�Ƃ���
		GF_ASSERT(0&&"ERROR:�ғ����Ȃ̂ɓo�^���悤�Ƃ��Ă���");
	}

	//�ғ����ɂ���
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].Moving = TRUE;

	//���[�h�����ۑ�
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].LoadDir = stock->LoadDir;
	
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].MLBS.Block[0] = stock->Block[0];
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].MLBS.Block[1] = stock->Block[1];
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].MLBS.Index[0] = stock->Index[0];
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].MLBS.Index[1] = stock->Index[1];
	
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].MLBS.Node[0] = stock->Node[0];
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].MLBS.Node[1] = stock->Node[1];

	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].MLBS.TotalCount = 0;
	ioDivMapCont->MLBC[ioDivMapCont->BlankNo].MLBS.BlockLoadOK = FALSE;
	
	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �X�g�b�N�p�}�b�v���[�h
 *
 * @param	*inStock
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void AddMapLoadForStock(DMC_PTR ioDivMapCont)
{
	int i;
	BOOL rc;
	STOCK_LOAD_DATA *stock = &ioDivMapCont->Stock;
	if (ioDivMapCont->MovingNum>=2){
		GF_ASSERT(0&&"ERROR:3��");
	}
	rc = BlockLoadReqestForStock(ioDivMapCont/*stock,ioDivMapCont->BlankNo*/);
#ifdef DIV_MAP_LOAD_DEBUG	
	OS_Printf("�X�g�b�N��%d�Ƀ^�X�N�o�^\n",ioDivMapCont->BlankNo);
#endif
	//�Ǘ��^�X�N�������ς��Ȃ̂ɁA���N�G�X�g�����������ꍇ�A�G���[�Ƃ��Ƃ�
	GF_ASSERT((rc == TRUE)&&"ERROR:�Ǘ��^�X�N�������ς�");
	
	stock->Node[0]->BlockIndex = stock->Block[0];
	stock->Node[1]->BlockIndex = stock->Block[1];
		
	ioDivMapCont->MovingNum++;
	ioDivMapCont->BlankNo = (ioDivMapCont->BlankNo+1)%2;
}

//--------------------------------------------------------------------------------------------
/**
 * ���[�h�I���Ď��֐�
 *
 * @param	inNo		�o�^�ԍ�(0�n�q1)
 *
 * @return	BOOL		TRUE:�I���@FALSE:���[�h�p��
 */
//--------------------------------------------------------------------------------------------
static BOOL IsFinishedLoadBlock(DMC_CONST_PTR inDivMapCont)
{
	return inDivMapCont->MLBC[inDivMapCont->NowMovingNo].MLBS.BlockLoadOK;
}

//--------------------------------------------------------------------------------------------
/**
 * �t���[�u���b�N�Ǘ��e�[�u�����N���A����
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ClearLocalFreeIndexTable(DMC_PTR outDivMapCont)
{
	u8 i;
	for(i=0;i<4;i++){
		outDivMapCont->LocalFreeIndexTable[i] = FALSE;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ��������t���[�u���b�N���}�[�L���O����
 *
 * @param	inDir	����
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void MarkLocalFreeIndexTableByDir(const u8 inDir, DMC_PTR outDivMapCont)
{
	switch(inDir){
	case MAP_LOAD_UP:
		outDivMapCont->LocalFreeIndexTable[2] = TRUE;
		outDivMapCont->LocalFreeIndexTable[3] = TRUE;
		break;
	case MAP_LOAD_RIGHT:
		outDivMapCont->LocalFreeIndexTable[0] = TRUE;
		outDivMapCont->LocalFreeIndexTable[2] = TRUE;
		break;
	case MAP_LOAD_DOWN:
		outDivMapCont->LocalFreeIndexTable[0] = TRUE;
		outDivMapCont->LocalFreeIndexTable[1] = TRUE;
		break;
	case MAP_LOAD_LEFT:
		outDivMapCont->LocalFreeIndexTable[1] = TRUE;
		outDivMapCont->LocalFreeIndexTable[3] = TRUE;
		break;
	}
}

//==============================================================================
/**
 * �G���A�f�[�^�̃��[�h
 *
 * @param   inGridX		�O���b�h���W�w
 * @param	inGridZ		�O���b�h���W�y
 * 
 * @retval  none		
 */
//==============================================================================
static void LoadFirstBlock(	DMC_PTR outDivMapCont,
							const int inGridX, 
							const int inGridZ,
							const int inMapGridW)
{
	u8 i;
	int start_block[4];

	//4�u���b�N�̃f�[�^�Ǎ�����m��
	AllocBlockList(outDivMapCont);

	//�����u���b�N���O���b�h���犄��o��
	MakeStartBlockTbl(	inGridX, inGridZ,
						outDivMapCont->MapW,
						outDivMapCont->MapH,
						inMapGridW, start_block	);

	for(i=0;i<4;i++){
		//�����f�[�^�Ǘ��\���̃������m��
		outDivMapCont->BlockNodeList[i]->MapHeightInfo = AllocMapHeightInfo();
		InitHeightData(outDivMapCont->BlockNodeList[i]->MapHeightInfo);	//�����f�[�^�Ǘ��\���̏�����
		LoadBlockQuick(	start_block[i],
						i,
						outDivMapCont->MapResource,
						outDivMapCont->World,
						outDivMapCont->MapW,
						outDivMapCont->MapH,
						MAPRES_IsValidLight(outDivMapCont->MapResource),
						outDivMapCont);//4�u���b�N���̃f�[�^�ǂݍ���
		/**
		//�R�[���o�b�N�Ăяo��
		if (outDivMapCont->CallBack!=NULL){
			outDivMapCont->CallBack(	outDivMapCont->CallBackWork,
										start_block[i],
										outDivMapCont->BlockNodeList[i]->ObjDataList);
		}*/
	}
}

//==============================================================================
/**
 * �G���A�f�[�^�̃��[�h
 *
 * @param   inGridX		�O���b�h���W�w
 * @param	inGridZ		�O���b�h���W�y
 * 
 * @retval  none		
 */
//==============================================================================
static void LoadFirstBlockForUnder(	DMC_PTR outDivMapCont,
									const int inGridX, 
									const int inGridZ,
									const int inMapGridW)
{
	u8 i;
	int start_block[4];
	
	//4�u���b�N�̃f�[�^�Ǎ�����m��
	AllocBlockListForUnder(outDivMapCont);

	//�����u���b�N���O���b�h���犄��o��
	MakeStartBlockTbl(	inGridX, inGridZ,
						outDivMapCont->MapW,
						outDivMapCont->MapH,
						inMapGridW, start_block);

	for(i=0;i<4;i++){
		//�����f�[�^�Ǘ��\����NULL�Z�b�g
		outDivMapCont->BlockNodeList[i]->MapHeightInfo = NULL;
		LoadBlockQuickForUnder(	start_block[i],
								i,
								outDivMapCont->MapResource,
								outDivMapCont->World,
								outDivMapCont->MapW,
								outDivMapCont->MapH,
								MAPRES_IsValidLight(outDivMapCont->MapResource),
								outDivMapCont);//4�u���b�N���̃f�[�^�ǂݍ���
	}
}


//==============================================================================
/**
 * ������
 *
 * @param	outDivMapCont	�����}�b�v�\���̃|�C���^
 *
 * @return	none
 */
//==============================================================================
static void InitMapLoadCont(DMC_PTR outDivMapCont)
{
	int i;

	outDivMapCont->NowMovingNo = 0;
	outDivMapCont->BlankNo = 0;
	outDivMapCont->MovingNum = 0;
	for(i=0;i<2;i++){
		outDivMapCont->MLBC[i].Moving = FALSE;
		outDivMapCont->MLBC[i].MLBS.BlockLoadOK = TRUE;
	}
	ClearLocalFreeIndexTable(outDivMapCont);
}

//==============================================================================
/**
 * ���W�Ō��ݏ����X�V
 *
 * @param   inGridX		�O���b�h���W�w
 * @param	inGridZ		�O���b�h���W�y
 *
 * @return	none
 */
//==============================================================================
static void UpdateNowData(const int inGridX, const int inGridZ, DMC_PTR outDivMapCont)
{
	outDivMapCont->NowGridNo = CalcGridNoFromGridXZ(inGridX,inGridZ,outDivMapCont->MapGridW);
	outDivMapCont->NowPosInBlock = CalcPositionInBlockFromGridNo(outDivMapCont->NowGridNo,
													outDivMapCont->MapGridW);
	outDivMapCont->NowLocalIndex = CalcLocalIdxFromPosInBlock(outDivMapCont->NowPosInBlock);
	outDivMapCont->NowBlockIndex = GetBlockIndexFromGridNo(outDivMapCont->NowGridNo,
															outDivMapCont->MapW,
															outDivMapCont->MapGridW);
#ifdef DIV_MAP_LOAD_DEBUG
	OS_Printf("Now=%d,%d,%d,%d\n",	outDivMapCont->NowGridNo,
									outDivMapCont->NowPosInBlock,
									outDivMapCont->NowLocalIndex,
									outDivMapCont->NowBlockIndex);
#endif
}

//==============================================================================
/**
 * �u���b�N�C���f�b�N�X����n�`�I�t�Z�b�g���v�Z(�����x�[�X�����߂�)
 *
 * @param   inBlockIndex	�u���b�N�C���f�b�N�X
 * @param	inMapW			�}�b�v��
 * @param	inWorld			���[���h�\���̂ւ̃|�C���^
 * @param	outTrans		�i�[���W
 * 
 * @return	none
 */
//==============================================================================
static void CalcMapOffset3D(	const int inBlockIndex,
								const int inMapW,
								const WORLD_MAP_PTR inWorld,
								VecFx32 *outTrans)
{
	u16 x_ofs;
	u16 z_ofs;
	outTrans->x = (BLOCK_GRID_SIZE_X/2)*ONE_GRID_SIZE*FX32_ONE;
	outTrans->z = (BLOCK_GRID_SIZE_Z/2)*ONE_GRID_SIZE*FX32_ONE;

	if (inBlockIndex == NON_BLOCK){
		return ;
	}
	
	x_ofs = inBlockIndex % inMapW;
	z_ofs = inBlockIndex / inMapW;
	{
		int height_base;
		int w;
		u16 matrix_id;
		w = GetWorldMapMatrixW(inWorld);
		matrix_id = GetWorldMatrixID(inWorld);
		height_base = GetHeightBaseFromMatrixID(inWorld, matrix_id, x_ofs, z_ofs, w);
		outTrans->y = height_base*HARF_GRID_SIZE*FX32_ONE;
	}
	outTrans->x += x_ofs*BLOCK_GRID_SIZE_X*ONE_GRID_SIZE*FX32_ONE;
	outTrans->z += z_ofs*BLOCK_GRID_SIZE_Z*ONE_GRID_SIZE*FX32_ONE;
}


//-----------------------------------------------------------------------------------------
//	�A�N�Z�X�֐�
//-----------------------------------------------------------------------------------------
//==============================================================================
/**
 * ������
 *
 * @param   world	���[���h�\���̃|�C���^	
 * @retval  none		
 */
//==============================================================================
DMC_PTR InitDivMap(	WORLD_MAP_PTR world,
					MAP_RESOURCE_PTR mapresource,
					FLD_3D_ANM_MNG_PTR inFld3DAnmPtr,
					const DIV_MAP_MODE inMode )
///					DFL_CONST_PTR ioFuncList,
///					const int inGroundMemSize,
///					const int inHeightMemSize)
{
	DMC_PTR map_cont_ptr;
	BOOL height_data_valid;

	//�}�b�v�R���g���[���f�[�^�m��
	map_cont_ptr = sys_AllocMemory( HEAPID_FIELD, sizeof(DIV_MAP_LOAD_CONT) );
	//�m�ۗ̈�̃N���[��
	MI_CpuClear8( map_cont_ptr, sizeof(DIV_MAP_LOAD_CONT));

	//���[�h����
	if (inMode == DIV_MAP_MODE_GROUND){				//�n��
		map_cont_ptr->FuncList = &DivGroundFunc;
		height_data_valid = TRUE;
	}else if(inMode == DIV_MAP_MODE_UNDER){			//�n��
		map_cont_ptr->FuncList = &DivUnderFunc;
		height_data_valid = FALSE;
	}else{
		GF_ASSERT(0&&"ERROR:�}�b�v������ł��Ȃ�");
	}
	
	//�}�b�v���g�p���郁�����i�n�`�f�[�^���j���m��
	map_cont_ptr->FldMapMem = AllocFldMapMem(height_data_valid);
	//�t�B�[���h���ʃ��\�[�X�̃|�C���^���Z�b�g
	map_cont_ptr->MapResource = mapresource;
	map_cont_ptr->World = world;
	
	//�}�b�v�c�����Z�b�g
	map_cont_ptr->MapW = GetWorldMapMatrixW(world);
	map_cont_ptr->MapH = GetWorldMapMatrixH(world);
	map_cont_ptr->MapGridW = map_cont_ptr->MapW*BLOCK_GRID_W;

	//�t�B�[���h3�c�A�j���}�l�[�W���|�C���^�Z�b�g
	map_cont_ptr->Field3DAnmPtr = inFld3DAnmPtr;

	map_cont_ptr->MapCheck.Valid = TRUE;
		
	//�}�b�v�Ǘ��^�X�N������
	InitMapLoadCont(map_cont_ptr);
/**
	//�����}�b�v�Z�b�g�A�b�v�A���[�h��������������������炤
	map_cont_ptr->FuncList = ioFuncList;
*/	

	map_cont_ptr->FreeRequest = FALSE;

	map_cont_ptr->LoadSeq = DML_NONE;
	//�A�[�J�C�u�n���h���̎擾
	map_cont_ptr->ArcHandle = ArchiveDataHandleOpen( ARC_FIELD_MAP_DATA, HEAPID_FIELD );

#ifdef DIV_CALL_BACK
	//�R�[���o�b�N������
	map_cont_ptr->CallBack = NULL;
#endif
	
#ifdef PM_DEBUG
	DebugOutRangeFlg = TRUE;
#endif
	
	return map_cont_ptr; 
}

//==============================================================================
/**
 * �}�b�v�ǂݍ���
 *
 * @param   none		
 * @retval  none		
 */
//==============================================================================
void LoadDivMap(DMC_PTR outDivMapCont, const int x, const int z)
{
	//4�u���b�N���[�h
/*
	DivMapLoad_LoadErea(outDivMapCont,
						x,
						z,
						outDivMapCont->MapW,
						outDivMapCont->MapGridW,
						inLightValid);<<table_func	
*/
	outDivMapCont->FuncList->DivFirstFunc(	outDivMapCont,
											x,
											z,
											outDivMapCont->MapGridW);
	//���@�̏����O���b�h��o�^
	UpdateNowData(x,z,outDivMapCont);
}

//==============================================================================
/**
 * �u���b�N�f�[�^�̍X�V�i���@���A�����o�����Ƃ��ɌĂԁj
 *
 * @param	inDirection		����
 *
 * @return	none
 */
//==============================================================================
void DivMapLoad_UpdateBlockData(const u8 inDirection, DMC_PTR ioDivMapCont)
{
	int next_block;
	u32 next_grid;
	u8 pos;
	
	next_grid = GetNextGridNo(	inDirection,
								ioDivMapCont->MapH,
								ioDivMapCont->MapGridW,
								ioDivMapCont->NowGridNo);

	next_block = GetBlockIdxFromGridNo(next_grid,ioDivMapCont->MapW, ioDivMapCont->MapGridW);
	pos = CalcPositionInBlockFromGridNo(next_grid,ioDivMapCont->MapGridW);
	//�u���b�N�Ԉړ����s���邩���`�F�b�N
	if (ioDivMapCont->NowBlockIndex != next_block){
		return;	//�u���b�N�Ԉړ��̏ꍇ�̓��[�h�Ȃ�
	}else{	//�u���b�N���ړ�
		if (ioDivMapCont->NowPosInBlock != pos){	//�u���b�N���ʒu���قȂ�
			//�u���b�N���[�h
			UpdateBlockList(next_block, inDirection, ioDivMapCont);
			//�u���b�N�X�V���s����̂ŁA���[�J���C���f�b�N�X���X�V����
			UpdateNowLocalIndexForAfterLoad(inDirection,
											ioDivMapCont->NowPosInBlock,
											&(ioDivMapCont->NowLocalIndex));
		}
	}
}

//==============================================================================
/**
 * �u���b�N�`��֐�
 *
 * @param	none
 *
 * @return	none
 */
//==============================================================================
void DrawAroundBlock(	DMC_CONST_PTR inDivMapCont,
						const GLST_DATA_PTR glst_data)
{
	static u8 debug_trg_alias = 0;
	
	u8 i;
	u8 draw = 0;	//�`�悷�郍�[�J���u���b�N�C���f�b�N�X��z��Ƃ��Ď��e�[�u���̎Q�ƃC���f�b�N�X

	//4�u���b�N�̕`��
	for(i=0;i<4;i++){
		///debag_count_b[i] = 0;
		if (inDivMapCont->BlockNodeList[i]->BlockIndex != NON_BLOCK){
			DrawBlock(i,inDivMapCont,glst_data);
		}
	}
	
#ifdef DEBUG_ONLY_FOR_saitou	
	
	if (sys.trg & PAD_BUTTON_L){
/**		
		OS_Printf("ALL_MODEL:%d\n",debag_all_count);
		OS_Printf("DRAW_MODEL:%d\n",debag_draw_count);		
		OS_Printf("DRAW_MODEL_B:%d,%d,%d,%d\n",
				debag_count_b[0],debag_count_b[1],debag_count_b[2],debag_count_b[3]);
*/
//�f�o�b�O�p�v�����g
		OS_Printf("0:WorldHeap = %ld\n",sys_GetHeapFreeSize(HEAPID_WORLD));
		OS_Printf("1:FieldHeap = %ld\n",sys_GetHeapFreeSize(HEAPID_FIELD));
	}

#endif
}

//==============================================================================
/**
 * �i�����Ƃ��Ă��������1�O���b�h��̃O���b�h���G���A�����𔻒肷��
 *
 * @param	inDirction	����
 * @param	*outGrid	�i�����Ƃ��Ă��������1�O���b�h��̃O���b�h
 * @return	none
 */
//==============================================================================
BOOL CheckNextGridIO(const u8 inDirection, DMC_CONST_PTR inDivMapCont, int *outGrid)
{
	int next_grid;
	
	//���݃O���b�h��������ɂ��킹�āA���O���b�h���v�Z
	switch(inDirection){
	case  MAP_LOAD_RIGHT:		//�E
		next_grid = (inDivMapCont->NowGridNo%inDivMapCont->MapGridW)+1;
		if ( next_grid >= inDivMapCont->MapGridW ){
			return FALSE;
		}
		*outGrid = inDivMapCont->NowGridNo+1;
		break;
	case MAP_LOAD_DOWN:			//��
		*outGrid = inDivMapCont->NowGridNo+inDivMapCont->MapGridW;
		if (*outGrid >= inDivMapCont->MapH*BLOCK_GRID_SIZE_Z*inDivMapCont->MapGridW){
			return FALSE;
		}
		break;
	case MAP_LOAD_LEFT:			//��
		next_grid = (inDivMapCont->NowGridNo%inDivMapCont->MapGridW)-1;
		if ( next_grid < 0 ){
			return FALSE;
		}
		*outGrid = inDivMapCont->NowGridNo-1;
		break;
	case MAP_LOAD_UP:			//��
		*outGrid = inDivMapCont->NowGridNo-inDivMapCont->MapGridW;
		if (*outGrid < 0 ){
			return FALSE;
		}
		break;
	default:
		GF_ASSERT(0&&"ERROR:NO_DIRECTION!!");
	}
	return  TRUE;
}

//==============================================================================
/**
 * ���W�����ɁA���ݗ����Ă���O���b�hXZ��Ԃ�
 *
 * @param   inX				���W�w
 * @param	inZ				���W�y
 * @param   outGridX		�O���b�h���W�w
 * @param	outGridZ		�O���b�h���W�y
 *
 * @return	none
 */
//==============================================================================
void GetGridXZ(fx32 inX, fx32 inZ, int *outGridX, int *outGridZ)
{
	*outGridX = inX/(ONE_GRID_SIZE*FX32_ONE);
	*outGridZ = inZ/(ONE_GRID_SIZE*FX32_ONE);
}

//==============================================================================
/**
 * �m�ۃ������̉��
 *
 * @param	none
 *
 * @return	none
 */
//==============================================================================
void DivMapLoad_FreeMap(DMC_PTR ioDivMapCont)
{
	u8 i;

	//�L���b�V���N���A
	ClearFileCache();
	
#ifdef LINK_VRAM_MANAGER
	NNS_GfdResetLnkTexVramState();
	NNS_GfdResetLnkPlttVramState();
#else
	//�e�N�X�`���A�p���b�g�J��
	NNS_GfdResetFrmTexVramState();
	NNS_GfdResetFrmPlttVramState();
#endif

	//���[�h�^�X�N���~���N�G�X�g
	for(i=0;i<2;i++){
		LoadTaskStopReqestByMLBS(&ioDivMapCont->MLBC[i].MLBS);
	}
#if 0
	//�A�[�J�C�u�n���h�������
	if (ioDivMapCont->ArcHandle != NULL){
		ArchiveDataHandleClose( ioDivMapCont->ArcHandle );
		ioDivMapCont->ArcHandle = NULL;
	}
#endif
	//�u���b�N�f�[�^���(�n�`�f�[�^�̉���A�}�b�v�����f�[�^�J�����܂�)
	for (i=0;i<4;i++){
		ioDivMapCont->BlockNodeList[i]->DrawOKFlg = FALSE;

		FreeMapHeightInfo(ioDivMapCont->BlockNodeList[i]->MapHeightInfo);
		//3DOBJ���
		M3DO_FreeMap3DObjList(ioDivMapCont->BlockNodeList[i]->ObjDataList );
		sys_FreeMemoryEz( ioDivMapCont->BlockNodeList[i] );
		ioDivMapCont->BlockNodeList[i] = NULL;
	}

	ioDivMapCont->LoadSeq = DML_FREE_WAIT;
	ioDivMapCont->FreeRequest = TRUE;

	ioDivMapCont->MapCheck.Valid = FALSE;
}

//==============================================================================
/**
 * �m�ۃ������̉��
 *
 * @param	none
 *
 * @return	none
 */
//==============================================================================
void FreeDivMapCont(DMC_PTR outDivMapCont)
{
	//�A�[�J�C�u�n���h���N���[�Y
	ArchiveDataHandleClose( outDivMapCont->ArcHandle );	
	//�}�b�v���������
	FreeFldMapMem(outDivMapCont->FldMapMem);
	//�}�b�v�Ǘ��f�[�^���
	sys_FreeMemoryEz( (void *)outDivMapCont );
	///outDivMapCont = NULL;
}

//==============================================================================
/**
 * �m�ۃ������̉���҂�
 *
 * @param	none
 *
 * @return	none
 */
//==============================================================================
BOOL WaitMapFree(DMC_CONST_PTR inDivMapCont)
{
	if ( (inDivMapCont->FreeRequest == TRUE) && (inDivMapCont->MovingNum == 0) ){
		return TRUE;
	}else{
		return FALSE;
	}
}

//==============================================================================
/**
 * ���W�̃o�C���h
 *
 * @param	*inTarget	���W
 * @param   outDivMapCont�@�����}�b�v�\����
 *
 * @return	none
 */
//==============================================================================
void DivMapBindTarget(VecFx32 const *inTarget, DMC_PTR outDivMapCont)
{
	outDivMapCont->MapCheck.OldPoint = *inTarget;
	outDivMapCont->MapCheck.TargetPoint = inTarget;
}

//==============================================================================
/**
 * ���W�̐؂藣��
 *
 * @param   outDivMapCont�@�����}�b�v�\����
 *
 * @return	none
 */
//==============================================================================
void DivMapPurgeTarget(DMC_PTR outDivMapCont)
{
	outDivMapCont->MapCheck.TargetPoint = NULL;
}

//==============================================================================
/**
 * �w�胍�[�J���u���b�N�C���f�b�N�X����I�u�W�F�N�g�\���̃��X�g��Ԃ�
 *
 * @param   outDivMapCont�@�����}�b�v�\����
 *
 * @return	none
 */
//==============================================================================
void Get3DObjListFromLocalIdx(const u8 inIdx, DMC_CONST_PTR inDivMapCont, M3DOL_PTR *outObjList)
{
	*outObjList = inDivMapCont->BlockNodeList[inIdx]->ObjDataList;
}

//==============================================================================
/**
 * ���݂̃u���b�N���[�J���C���f�b�N�X���擾
 *
 * @param   outDivMapCont�@�����}�b�v�\����
 *
 * @return	none
 */
//==============================================================================
u8 GetNowLocalIndex(DMC_CONST_PTR inDivMapCont)
{
	return inDivMapCont->NowLocalIndex;
}

//==============================================================================
/**
 * ���݂̃u���b�N�C���f�b�N�X���擾
 *
 * @param   outDivMapCont�@�����}�b�v�\����
 *
 * @return	none
 */
//==============================================================================
int GetNowBlockIndex(DMC_CONST_PTR inDivMapCont)
{
	return inDivMapCont->NowBlockIndex;
}

//--------------------------------------------------------------------------------------------
/**
 * ���݃O���b�h�C���f�b�N�X����A�u���b�N�̂ǂ̈ʒu�i4���������Ƃ��j�ɂ��邩���v�Z
 *
 * @param	inGridNo	�O���b�h�i���o�[
 *
 * @return	u8			�u���b�N���ʒu(0�`3)
 */
//--------------------------------------------------------------------------------------------
u8 CalcPositionInBlockFromGridNo(const u32 inGridNo, const int inMapGridW)
{
	u8 pos;
	int pos_x,pos_z;
	int line_z;
	pos_x = inGridNo%BLOCK_GRID_SIZE_X;
	line_z = inGridNo/inMapGridW;
	pos_z = line_z%BLOCK_GRID_SIZE_Z;
	if (pos_x < BLOCK_GRID_SIZE_X/2){
		if (pos_z < BLOCK_GRID_SIZE_Z/2){
			pos = 0;	//�u���b�N����
		}else{
			pos = 2;	//�u���b�N����
		}
	}else{
		if (pos_z < BLOCK_GRID_SIZE_Z/2){
			pos = 1;	//�u���b�N�E��
		}else{
			pos = 3;	//�u���b�N�E��
		}
	}
	return pos;
}

//--------------------------------------------------------------------------------------------
/**
 * �u���b�N�C���f�b�N�X���烍�[�J���C���f�b�N�X���v�Z�i�㉺���E�̂݁j
 *
 * @param	inBlockIndex		�u���b�N�C���f�b�N�X
 * @param	inPosInBlock		�u���b�N���ʒu(0�`3)
 *
 * @return	u8					���[�J���C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u8 CalcLocalIdxFromBlockIdx(const int inBlockIndex, const u8 inPosInBlock, DMC_CONST_PTR inDivMapCont)
{
	u8 local_index;
#ifdef DIV_MAP_LOAD_DEBUG	
	OS_Printf("inPosInBlock=%d\n",inPosInBlock);
#endif
	if (inDivMapCont->NowBlockIndex == inBlockIndex){
		return inDivMapCont->NowLocalIndex;
	}

	GF_ASSERT(inBlockIndex!=NON_BLOCK);
	
	switch (inDivMapCont->NowLocalIndex){
	case 0:															//���@������ɂ���Ƃ�
		//MapW���P�̂Ƃ����l���D�悵�Ĕ��肷��
		if(inBlockIndex - inDivMapCont->NowBlockIndex == inDivMapCont->MapW){
			local_index = inDivMapCont->NowLocalIndex+2;			//��
		}else if ( (inBlockIndex - inDivMapCont->NowBlockIndex == 1) &&
				(CheckRowBlockIndex( inDivMapCont->NowBlockIndex, inBlockIndex, inDivMapCont->MapW)) ){
			//�����тł���΁A�n�j
			local_index = inDivMapCont->NowLocalIndex+1;			//�E
		}else if ( (inBlockIndex - inDivMapCont->NowBlockIndex == inDivMapCont->MapW+1) &&
				(!CheckRowBlockIndex( inDivMapCont->NowBlockIndex, inBlockIndex, inDivMapCont->MapW)) ){
			//�����тłȂ���΁@�n�j
			local_index = inDivMapCont->NowLocalIndex+3;			//�E��
		}else{
			local_index = 4;		//���ʕs��
		}
		break;
	case 1:															//���@���E��ɂ���Ƃ�
		//MapW���P�̂Ƃ����l���D�悵�Ĕ��肷��
		if(inBlockIndex - inDivMapCont->NowBlockIndex == inDivMapCont->MapW){
			local_index = inDivMapCont->NowLocalIndex+2;			//��
		}else if ( (inDivMapCont->NowBlockIndex - inBlockIndex == 1) &&
				(CheckRowBlockIndex( inDivMapCont->NowBlockIndex, inBlockIndex, inDivMapCont->MapW)) ){
			//�����тł���΁A�n�j
			local_index = inDivMapCont->NowLocalIndex-1;			//��
		}else if ( (inBlockIndex - inDivMapCont->NowBlockIndex == inDivMapCont->MapW-1) &&
				(!CheckRowBlockIndex( inDivMapCont->NowBlockIndex, inBlockIndex, inDivMapCont->MapW)) ){
			//�����тłȂ���΁@�n�j
			local_index = inDivMapCont->NowLocalIndex+1;			//����
		}else{
			local_index = 4;		//���ʕs��

		}
		break;
	case 2:															//���@�������ɂ���Ƃ�
		//MapW���P�̂Ƃ����l���D�悵�Ĕ��肷��
		if (inDivMapCont->NowBlockIndex - inBlockIndex == inDivMapCont->MapW){
			local_index = inDivMapCont->NowLocalIndex-2;			//��
		}else if( (inDivMapCont->NowBlockIndex - inBlockIndex == inDivMapCont->MapW-1) &&
				(!CheckRowBlockIndex( inDivMapCont->NowBlockIndex, inBlockIndex, inDivMapCont->MapW)) ){
			//�����тłȂ���΁A�n�j
			local_index = inDivMapCont->NowLocalIndex-1;			//�E��
		}else if ( (inBlockIndex - inDivMapCont->NowBlockIndex == 1) &&
				(CheckRowBlockIndex( inDivMapCont->NowBlockIndex, inBlockIndex, inDivMapCont->MapW)) ){
			//�����тł���΂n�j
			local_index = inDivMapCont->NowLocalIndex+1;			//�E
		}else{
			local_index = 4;		//���ʕs��

		}
		break;
	case 3:															//���@���E���ɂ���Ƃ�
		//MapW���P�̂Ƃ����l���D�悵�Ĕ��肷��
		if(inDivMapCont->NowBlockIndex - inBlockIndex == inDivMapCont->MapW){
			local_index = inDivMapCont->NowLocalIndex-2;			//��
		}else if ( (inDivMapCont->NowBlockIndex - inBlockIndex == inDivMapCont->MapW+1) &&
				(!CheckRowBlockIndex( inDivMapCont->NowBlockIndex, inBlockIndex, inDivMapCont->MapW)) ){
			//�����тłȂ���΁A�n�j
			local_index = inDivMapCont->NowLocalIndex-3;			//����
		}else if ( (inDivMapCont->NowBlockIndex- inBlockIndex == 1) &&
				(CheckRowBlockIndex( inDivMapCont->NowBlockIndex, inBlockIndex, inDivMapCont->MapW)) ){
			//�����тł���΂n�j
			local_index = inDivMapCont->NowLocalIndex-1;			//��
		}else{
			local_index = 4;		//���ʕs��

		}
		break;
	default:
		local_index = 4;		//���ʕs��

	}
	
	return local_index;
}

//==============================================================================
/**
 * ���[�J���C���f�b�N�X����u���b�N�C���f�b�N�X���擾
 *
 * @param   inDivMapCont�@�����}�b�v�\����
 *
 * @return	int		�u���b�N�C���f�b�N�X
 */
//==============================================================================
int GetBlockIndexFromLocalIndex(DMC_CONST_PTR inDivMapCont, const u8 inLocalIndex)
{
	GF_ASSERT(inLocalIndex<4);
	return inDivMapCont->BlockNodeList[inLocalIndex]->BlockIndex;
}

//==============================================================================
/**
 * �u���b�N���O����
 *
 * @param   outDivMapCont�@�����}�b�v�\����
 *
 * @return	none
 */
//==============================================================================
BOOL CheckFourBlockIO(DMC_CONST_PTR inDivMapCont, const int inGridX, const int inGridZ, u8 *outLocalIndex)
{
	u32 block_x,block_z;
	u32 block_index;
	u32 local_index;

	u32 grid_no;
	u8 pos_in_block;
	
	block_x = inGridX / BLOCK_GRID_W;
	block_z = inGridZ / BLOCK_GRID_H;
	block_index = block_x+(block_z*inDivMapCont->MapW);

    if(!(block_index < inDivMapCont->MapW*inDivMapCont->MapH)){
        if(CommStateSetError(COMM_ERROR_RESET_SAVEPOINT)){
            return FALSE;
        }
    }
	GF_ASSERT(block_index < inDivMapCont->MapW*inDivMapCont->MapH);
	
	grid_no = inGridX+(inGridZ*inDivMapCont->MapGridW);
	pos_in_block = CalcPositionInBlockFromGridNo(grid_no,inDivMapCont->MapGridW);
	local_index = CalcLocalIdxFromBlockIdx(block_index,pos_in_block,inDivMapCont);

	if (outLocalIndex != NULL){
		*outLocalIndex = local_index;
	}
	
	if (local_index>3){
		return FALSE;
	}else{
		return TRUE;
	}
}

//==============================================================================
/**
 * �����}�b�v�\���̂���āA�������擾
 *
 * @param   outDivMapCont�@�����}�b�v�\����
 *
 * @return	none
 */
//==============================================================================
MHI_CONST_PTR GetDivMapHeightInfo(DMC_CONST_PTR inDivMapCont, const u8 inLocalIndex)
{
	return inDivMapCont->BlockNodeList[inLocalIndex]->MapHeightInfo;
}

//==============================================================================
/**
 * �����}�b�v�\���̂���āA�A�g���r���[�g�擾
 *
 * @param   outDivMapCont�@�����}�b�v�\����
 *
 * @return	none
 */
//==============================================================================
u16 const *GetDivMapAttribute(DMC_CONST_PTR inDivMapCont, const u8 inLocalIndex)
{
	return inDivMapCont->BlockNodeList[inLocalIndex]->Attribute;
}

/**
void SetUpDivFuncList(FIELDSYS_WORK *fsys, const u8 inMode)
{
	if (inMode == DIV_MAP_MODE_GROUND){
		fsys->div_func_list = &DivGroundFunc;
	}else if (inMode == DIV_MAP_MODE_UNDER){
		fsys->div_func_list = &DivUnderFunc;
	}else{
		GF_ASSERT( 0 && "Mapmode unknown " );
	}
}
*/
#ifdef DIV_CALL_BACK
void DIVM_SetLoadCallBack( DMC_PTR outDivMapCont, DIV_LOAD_CALL_BACK call_back, void *work )
{
	outDivMapCont->CallBack = call_back;
	outDivMapCont->CallBackWork = work;
}
#endif

typedef struct MODEL_SET_DAT_tsg
{
	ARCHANDLE *ArcHandle;
	int DataSize;
	NNSG3dRenderObj* Object_p;
	NNSG3dResFileHeader** ResFile;
	NNSG3dResTex*        Texture;
	u8 SetSeq;
	BOOL	*DrawOK;
	BOOL	StopFlg;
	int * EndFlg;

	u32 data_trans_offset;
}MODEL_SET_DAT;

static void StopMapLoadTaskRequest(TCB_PTR tcb)
{
	MODEL_SET_DAT *model_set_dat;
	model_set_dat = (MODEL_SET_DAT*)TCB_GetWork(tcb);
	model_set_dat->StopFlg = TRUE;
}


static void SetModel(TCB_PTR tcb,void* work)
{
	int i;
	MODEL_SET_DAT *model_set_dat;
	BOOL status;
	int read_size;
	void *mem;
	
	model_set_dat = (MODEL_SET_DAT*)work;
	

	if (model_set_dat->StopFlg == TRUE){
		//�������f
		model_set_dat->SetSeq = MODELSET_TASK_SEQ_EXIT;
	}
	switch(model_set_dat->SetSeq){

	case MODELSET_TASK_SEQ_INIT:

		model_set_dat->data_trans_offset = 0;
		if (model_set_dat->DataSize<=MODEL_SET_DIV_SIZE){
			//�����ʈȉ��̏ꍇ
			read_size = model_set_dat->DataSize;
			model_set_dat->SetSeq = MODELSET_TASK_SEQ_TEXTURE_BIND;
		}else{
			//�����ʂ��傫���ꍇ
			read_size = MODEL_SET_DIV_SIZE;
			model_set_dat->SetSeq = MODELSET_TASK_SEQ_MODEL_LOAD;
		}

		mem = &((u8*)(*model_set_dat->ResFile))[model_set_dat->data_trans_offset];
		ArchiveDataLoadByHandleContinue( model_set_dat->ArcHandle, read_size, mem );
		model_set_dat->data_trans_offset+=read_size;
		
		break;

	case MODELSET_TASK_SEQ_MODEL_LOAD:
		{
			int end;
			read_size = model_set_dat->DataSize-model_set_dat->data_trans_offset;
			if (read_size>MODEL_SET_DIV_SIZE){
				//�����ʂ��傫���ꍇ
				read_size = MODEL_SET_DIV_SIZE;
				//�������p��
				end = 0;
			}else{
				//�ǂݍ���ŏI��
				end = 1;
			}
			mem = &((u8*)(*model_set_dat->ResFile))[model_set_dat->data_trans_offset];
			ArchiveDataLoadByHandleContinue( model_set_dat->ArcHandle, read_size, mem );

			if (end){
				model_set_dat->SetSeq = MODELSET_TASK_SEQ_TEXTURE_BIND;
			}else{
				model_set_dat->data_trans_offset+=read_size;
			}
		}
		
		break;

	case MODELSET_TASK_SEQ_TEXTURE_BIND:
		if(model_set_dat->Texture != NULL){
			// �e�N�X�`����Vram�ɓW�J����Ă��邩�`�F�b�N
			if(TexKeyLive(model_set_dat->Texture) == TRUE){	
				//�e�N�X�`���o�C���h
				status = BindTexture(*model_set_dat->ResFile, model_set_dat->Texture);
				NNS_G3D_ASSERTMSG(status, "BindTexture failed");
			}else{
				OS_Printf("�e�N�X�`�����W�J����Ă��Ȃ�");
			}
		}
		model_set_dat->SetSeq = MODELSET_TASK_SEQ_RESOUCE_SET;
		break;

	case MODELSET_TASK_SEQ_RESOUCE_SET:
		{
#if 0			
			NNSG3dResMdlSet* pMdlSet = NNS_G3dGetMdlSet(*model_set_dat->ResFile);
			model_set_dat->EntryModelNum = pMdlSet->dict.numEntry; 
			for(i=0;i<model_set_dat->EntryModelNum;i++){
				model_set_dat->Model = NNS_G3dGetMdlByIdx(pMdlSet, i);
				SDK_ASSERTMSG(model_set_dat->Model, "load failed");
				NNS_G3dRenderObjInit(&model_set_dat->Object_p[i], model_set_dat->Model);
			}
#else
			NNSG3dResMdlSet* pMdlSet = NNS_G3dGetMdlSet(*model_set_dat->ResFile);
			NNSG3dResMdl *model;
			
			GF_ASSERT(pMdlSet->dict.numEntry==1&&"���f���Z�b�g�̒��ɕ������f��������");
			
			model = NNS_G3dGetMdlByIdx(pMdlSet, 0);
			GF_ASSERT(model&&"load failed");
			NNS_G3dRenderObjInit(model_set_dat->Object_p, model);
#endif			
		}
		*model_set_dat->DrawOK = TRUE;

		model_set_dat->SetSeq = MODELSET_TASK_SEQ_EXIT;
		break;
	case MODELSET_TASK_SEQ_EXIT:
		*model_set_dat->EndFlg = 0;
		sys_FreeMemoryEz( (void*)(work) );
		TCB_Delete(tcb);
		return;
	}
}

//�}�b�v���[�h�^�X�N
TCB_PTR Set3DModelTask(	ARCHANDLE *inHandle,
						const int inSize,
						NNSG3dRenderObj* object_p,
						NNSG3dResFileHeader** resFile,
						NNSG3dResTex* pTexture,
						BOOL *ioDrawOKFlg,
						int *inEndFlg) 
{
	TCB_PTR	_tcb;
	MODEL_SET_DAT *work;
	work = (MODEL_SET_DAT *)sys_AllocMemoryLo( HEAPID_FIELD, sizeof(MODEL_SET_DAT) );
	
	work->ArcHandle = inHandle;
	work->DataSize = inSize;
	
	work->Object_p = &object_p[0];
	work->ResFile = resFile;
	work->Texture = pTexture;
	work->SetSeq = 0;
	work->DrawOK = ioDrawOKFlg;
	*work->DrawOK = FALSE;
	work->EndFlg = inEndFlg;
	work->StopFlg = FALSE;
	
	_tcb = TCB_Add(SetModel, work, 1);
	return _tcb;
}

//�f�t�H���g�Z�b�g�A�b�v���s��Ȃ����f���ǂݍ��݊֐�
NNSG3dResMdl* Set3DModel(	ARCHANDLE *ioHandle,
							const int inSize,
							NNSG3dRenderObj* object_p,
							NNSG3dResFileHeader** resFile,
							NNSG3dResTex* pTexture)
{
	BOOL status;
	NNSG3dResMdl* model;

	ArchiveDataLoadByHandleContinue( ioHandle, inSize, *(resFile) );
	
	if(pTexture != NULL){
		if(TexKeyLive(pTexture) == TRUE){	// �e�N�X�`����Vram�ɓW�J����Ă��邩�`�F�b�N
			//�e�N�X�`���o�C���h
			status = BindTexture(*resFile, pTexture);
			NNS_G3D_ASSERTMSG(status, "BindTexture failed");
			GF_ASSERT(status&&"BindTexture failed");
		}else{
			OS_Printf("�e�N�X�`�����W�J����Ă��Ȃ�");
		}
	}

	{
		u8 i;
		u16 entry_model_num;
		NNSG3dResMdlSet* pMdlSet = NNS_G3dGetMdlSet(*resFile);

		GF_ASSERT(pMdlSet->dict.numEntry==1&&"���f���Z�b�g�̒��ɕ������f��������");

		model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*resFile), 0);
		GF_ASSERT(model&&"load failed");
		NNS_G3dRenderObjInit(object_p, model);
/**		
		entry_model_num = pMdlSet->dict.numEntry;
		for(i=0;i<entry_model_num;i++){
			model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*resFile), i);
			SDK_ASSERTMSG(model, "load failed");
			GF_ASSERT(model&&"load failed");
			NNS_G3dRenderObjInit(&object_p[i], model);
		}
*/		
	}

	return model;
}

#ifdef PM_DEBUG
void SetDebugOutRangeFlg(void)
{
	DebugOutRangeFlg = (DebugOutRangeFlg+1)%2;
}
#endif
