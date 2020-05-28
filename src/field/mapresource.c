//=============================================================================
/**
 * @file	mapresource.c
 * @bfief	�t�B�[���h�}�b�v���\�[�X�\�z����
 * @author	mori         GAME FREAK inc.
 *
 *
 */
//=============================================================================

#include "common.h"
#include "height_def.h"
#include "calctool.h"
#include "str_tool.h"

#include "fieldsys.h"
#include "worldmap.h"
#include "mapresource.h"
#include "debug_saito.h"

#include "mapdefine.h"
#include "zonedata.h"
#include "mat_shp.h"
//#include "field_camera.h"
#include "system/arc_tool.h"
#include "situation_local.h"

#define BUILD_MODEL_MAX	(550)

//�G�b�W�}�[�L���O�e�[�u��
static const GXRgb gEdgeColorField[8] = {
    GX_RGB(0, 0, 0),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4)
};
//�G�b�W�}�[�L���O�e�[�u��
static const GXRgb gEdgeColorOther[8] = {
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4)
};
enum {
	CAMERA_TYPE1,
	CAMERA_TYPE2,
	CAMERA_TYPE3,
}CAMERA_TYPE;

typedef struct MAP_RES_SETUP_WORK_tag
{
	int AreaID;
	FLD_3D_ANM_MNG_PTR FldAnmMng;
	u16  Num;
	int Seq;
}MAP_RES_SETUP_WORK;

typedef struct RESOURCE_PARAM_tag
{
	u16 model_set;			//���f���Z�b�g�C���f�b�N�X
	u16 tex_set;		//�n�`�e�N�X�`���Z�b�g�C���f�b�N�X
	u16 move_model_set;		//���샂�f���Z�b�g�C���f�b�N�X
	u16 light;				//���C�g�t���O
}RESOURCE_PARAM;

//-�}�b�v���\�[�X�\����(worldmap���番��)------------------------------------------------------
typedef struct _MAP_RESOURCE{
	int 				modelTableNum;	///< modelTable�������f�����O�f�[�^�̐�
	NNSG3dResFileHeader	*model[BUILD_MODEL_MAX];	///< ���f�����O�f�[�^�̃|�C���^�̃e�[�u��
	void*				pTexFile;		///< �e�N�X�`���[�t�@�C�����̂ւ̃|�C���^
	void*				pBmTexFile;		///< �z�u���f���e�N�X�`���[�t�@�C�����̂ւ̃|�C���^
	NNSG3dResTex		*Tex;			///< �e�N�X�`�����\�[�X
	NNSG3dResTex		*BmTex;			///< �z�u���f���e�N�X�`�����\�[�X

	MSD_PTR				MatShpData;		///< 3�c�n�a�i�̃}�e���A���A�V�F�C�v�Ή��f�[�^
	
	RESOURCE_PARAM ResourceParam;

	MAP_RES_SETUP_WORK *SetupWork;

	u16 *ModelFile;

}MAP_RESOURCE;


#ifdef PM_DEBUG
///#define DEBUG_TEX_INFO		//�e�N�X�`�����\��
static void DebugPrintTexInfo(NNSG3dResTex *pTex);
#endif

//==============================================================================
/**
 * �e�N�X�`�����̂�j��
 *
 * @param   memBlock	�������u���b�N
 * @param	texture		�e�N�X�`�����\�[�X
 *
 * @retval  none
 */
//==============================================================================
static void CollapseResourceMemory(void* memBlock, NNSG3dResTex* texture)
{
    u8* texImgStartAddr;
    u32 newSize;

    // �e�N�X�`���^�p���b�g�́A4x4COMP�ȊO�̃e�N�X�`���E4x4COMP�̃e�N�X�`���E�p���b�g
    // �̏��ԂŊi�[����Ă��܂��B�����4x4COMP�ȊO�̃e�N�X�`���̊J�n�A�h���X�ȍ~��
    // �s�v�ɂȂ�܂��B�Ȃ��A4x4COMP�t�H�[�}�b�g�ȊO�̃e�N�X�`���C���[�W�����݂��Ȃ�
    // �ꍇ�ł�texture->texInfo.ofsTex�ɂ͓K�؂Ȓl�������Ă��܂��B
    SDK_ASSERT(texture->texInfo.ofsTex != 0);
    texImgStartAddr = (u8*)texture + texture->texInfo.ofsTex;

    // �q�[�v�̐擪����e�N�X�`���C���[�W�܂ł̃T�C�Y
    newSize = (u32)(texImgStartAddr - (u8*)memBlock);

    // �������u���b�N���k�����܂��B
    // ���̌��ʁA�e�N�X�`���C���[�W���̃������̓q�[�v�ɕԋp����܂��B
    ///(void)NNS_FndResizeForMBlockExpHeap(G3DDemo_AppHeap, memBlock, newSize);
	sys_CutMemoryBlockSize( memBlock, newSize );
}

//==============================================================================
/**
 * MAP_RESOURCE�̃A���P�[�V����
 *
 * @param   area_id		�G���AID
 * @param	field_3d_anime	3�c�A�j��
 *
 * @retval  MAP_RESOURCE_PTR	�m�ۂ���MAPRESOURCE�̃|�C���^
 */
//==============================================================================
MAP_RESOURCE_PTR AllocMapResource(const int area_id, FLD_3D_ANM_MNG_PTR field_3d_anime)
{
	MAP_RESOURCE_PTR mapresource;
	mapresource	= sys_AllocMemory(HEAPID_FIELD,sizeof(MAP_RESOURCE));
#ifdef DEBUG_ONLY_FOR_saitou	
	OS_Printf("local_print AREA_ID:%d\n",area_id);
#endif
	//���[�N�̊m��
	mapresource->SetupWork = sys_AllocMemoryLo(HEAPID_FIELD,sizeof(MAP_RES_SETUP_WORK));
	mapresource->SetupWork->AreaID = area_id;
	mapresource->SetupWork->FldAnmMng = field_3d_anime;
	mapresource->SetupWork->Seq = 0;
	return mapresource;
}

//==============================================================================
/**
 * �}�b�v���\�[�X�Z�b�g�A�b�v
 *
 * @param   outMapResource		MAPRESOURCE�̃|�C���^
 *
 * @retval  none	
 */
//==============================================================================
void SetupMapResource(MAP_RESOURCE_PTR outMapResource)
{
	ARCHANDLE* model_handle;
#ifdef PM_DEBUG
	static int debug_tex_size;
#endif
	MAP_RES_SETUP_WORK *work = outMapResource->SetupWork;
	
	//�A�[�J�C�u����G���A�f�[�^���擾
	ArchiveDataLoad(&outMapResource->ResourceParam, ARC_AREA_DATA, work->AreaID);
	
#ifdef DEBUG_ONLY_FOR_saitou	
	OS_Printf("local_print TEX_LOAD:%d\n",outMapResource->ResourceParam.tex_set);
#endif

	//�G���A�����f�����O�f�[�^���X�g�ǂݍ���
	outMapResource->ModelFile = ArchiveDataLoadMalloc(	ARC_AREA_BUILD_MODEL,
														outMapResource->ResourceParam.model_set,
														HEAPID_FIELD );
	work->Num = outMapResource->ModelFile[0];

	GF_ASSERT(work->Num<BUILD_MODEL_MAX&&"�z�u���f���o�^���I�[�o�[");
	
	//�n�`�p���ʃe�N�X�`���ǂݍ���
	outMapResource->Tex = NULL;
	//AreaID�ɑΉ��������ʃe�N�X�`���t�@�C����ǂݍ���
	outMapResource->pTexFile = ArchiveDataLoadMalloc(	ARC_AREA_TEX_SET,
														outMapResource->ResourceParam.tex_set,
														HEAPID_FIELD );
	//�z�u���f���e�N�X�`���Z�b�g��ǂݍ���
	outMapResource->pBmTexFile = ArchiveDataLoadMalloc(	ARC_BM_TEX_SET,
														outMapResource->ResourceParam.model_set,
														HEAPID_FIELD );
	// �e�N�X�`���t�@�C�����擾
	outMapResource->Tex = NNS_G3dGetTex((NNSG3dResFileHeader*) outMapResource->pTexFile );
	if (work->Num != 0){
		outMapResource->BmTex = NNS_G3dGetTex((NNSG3dResFileHeader*) outMapResource->pBmTexFile );
	}else{
		outMapResource->BmTex = NULL;
	}

	{
		BOOL rc;
#ifdef DEBUG_TEX_INFO
		DebugPrintTexInfo(outMapResource->Tex);
#endif
		//�e�N�X�`�����u�q�`�l�փ��[�h
		rc = LoadVRAMTexture(outMapResource->Tex);
		GF_ASSERT(rc && "�e�N�X�`����VRAM�m�ێ��s");
	}
	//���̂�j��
	CollapseResourceMemory(outMapResource->pTexFile, outMapResource->Tex);
	
	if (outMapResource->BmTex != NULL){
		BOOL rc;
#ifdef DEBUG_TEX_INFO
		DebugPrintTexInfo(outMapResource->BmTex);
#endif		
		//�e�N�X�`�����u�q�`�l�փ��[�h
		rc = LoadVRAMTexture(outMapResource->BmTex);
		GF_ASSERT(rc && "�e�N�X�`����VRAM�m�ێ��s");
		//���̂�j��
		CollapseResourceMemory(outMapResource->pBmTexFile, outMapResource->BmTex);
	}
	
	{
		int i;
		//������
		for(i=0;i<BUILD_MODEL_MAX;i++){
			outMapResource->model[i] = NULL;
		}
		outMapResource->MatShpData = NULL;
		
#ifdef DEBUG_ONLY_FOR_saitou
		OS_Printf("local_print objct_num = %d\n",work->Num);
#endif
#ifdef PM_DEBUG
		debug_tex_size = 0;	
#endif
	}

	//3D���f���A�[�J�C�u�n���h���I�[�v��
	model_handle = ArchiveDataHandleOpen( ARC_3D_STRUCT, HEAPID_FIELD );
	{
		int i;
		u16 no;
		int anime_num;

		anime_num = F3DA_GetAnimeArcObjNum(work->FldAnmMng);
		//�|�C���^�unow�v�͊���1�s�ǂݔ�΂��ꂽmodelTable�̓��e���w���Ă���̂Ŏ�����StrTok�̓p�X���擾�ɂȂ�
		for(i=0;i<work->Num;i++){
			no = outMapResource->ModelFile[i+1];//�f�[�^�̓�������1�Ԗڂ���i0�Ԗڂ͌��j
#ifdef DEBUG_ONLY_FOR_saitou
			OS_Printf("local_print model_no = %d\n",no);
#endif
			GF_ASSERT_MSG(outMapResource->model[no]==NULL,"�z�u���f��(%d)�̂Q�d�o�^�̉\������",no);
			outMapResource->model[no] = ArchiveDataLoadAllocByHandle( model_handle, no, HEAPID_FIELD );
			
			{
				//�A�j���Z�b�g
				NNSG3dResMdl* model;
				if (no < anime_num){
					model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(outMapResource->model[no]), 0);

					F3DA_AddField3DAnimeEasy(	no,
												model,
												outMapResource->BmTex,
												work->FldAnmMng	);
				}
			}
			//�e�N�X�`���o�C���h
			{
				BOOL rc;
				rc = BindTexture(outMapResource->model[no], outMapResource->BmTex);
				GF_ASSERT(rc && "3�c�n�a�i�e�N�X�`���o�C���h���s");
			}
#ifdef DEBUG_TEX_INFO				
			{
				NNSG3dResTex *tex;
				// �e�N�X�`���t�@�C�����擾
				tex = NNS_G3dGetTex((NNSG3dResFileHeader*) outMapResource->model[no] );
				if(tex != NULL){
					DebugPrintTexInfo(tex);
				}
			}
#endif
		}//end for
	}
	//�_�~�[�f�[�^�͏풓�����Ƃ�
	if (outMapResource->model[0] == NULL){
		BOOL rc;
		NNSG3dResTex *tex;
//		outMapResource->model[0] = ArchiveDataLoadMalloc( ARC_3D_STRUCT, 0, HEAPID_FIELD );
		outMapResource->model[0] = ArchiveDataLoadAllocByHandle( model_handle, 0, HEAPID_FIELD );
		OS_Printf("�����u����Ă��Ȃ��̂ŁA�_�~�[��o�^\n");
		
		// �e�N�X�`���t�@�C�����擾
		tex = NNS_G3dGetTex((NNSG3dResFileHeader*) outMapResource->model[0] );
		if(tex != NULL){
			//�e�N�X�`�����u�q�`�l�փ��[�h
			rc = LoadVRAMTexture(tex);
			GF_ASSERT(rc && "�e�N�X�`����VRAM�m�ێ��s");
			//�e�N�X�`���o�C���h
			rc = BindTexture(outMapResource->model[0], tex);
			GF_ASSERT(rc && "3�c�n�a�i�e�N�X�`���o�C���h���s");
		}
	}

	//3D���f���A�[�J�C�u�n���h���N���[�Y
	ArchiveDataHandleClose( model_handle );
#if	1
		G3X_EdgeMarking(TRUE);
		if (outMapResource->ResourceParam.light == 0) {
			G3X_SetEdgeColorTable(gEdgeColorField);
		} else {
			G3X_SetEdgeColorTable(gEdgeColorOther);
		}
#endif
	///sys_FreeMemoryEz(work->ModelFile);
	{
		char name[256];
		//�}�e���A���A�V�F�C�v�Ή��f�[�^���[�h
		outMapResource->MatShpData = AllocMatShpData();
		sprintf(name,"fielddata/build_model/build_model_matshp.dat");
		LoadMatShape(name, outMapResource->MatShpData);
	}
	
///	OS_Printf("model_tex_size_total=%d\n",debug_tex_size);
	
	//���[�N�̉��
	sys_FreeMemoryEz(outMapResource->SetupWork);
	outMapResource->SetupWork = NULL;
}

//==============================================================================
/**
 * �G���A�ɑΉ��������f�����O�f�[�^�t�@�C�����̎擾
 *
 * @param   index		���f��ID
 * @param   mapresource		WORLD_MAP�̃|�C���^
 *
 * @retval  NNSG3dResFileHeader**		���f�����O�f�[�^�̃|�C���^
 */
//==============================================================================
NNSG3dResFileHeader** GetMapResourceModelRes(const int index, const MAP_RESOURCE_PTR mapresource)
{
	GF_ASSERT((mapresource!=NULL) && "mapresourcemap�����m��");

	if (mapresource->model[index] == NULL){
//		OS_Printf("index = %d �z�u���f���o�^�G���[ �_�~�[��\�����܂�\n",index);
		GF_ASSERT(mapresource->model[0]!=NULL&&"�_�~�[���o�^����Ă��Ȃ�\n");
		//NULL�f�[�^��������A�_�~�[�{�b�N�X��Ԃ��悤�ɂ��Ă���
		return &(mapresource->model[0]);	
	}
	
	///GF_ASSERT((mapresource->model[index] != NULL)&&"���f�����O�f�[�^���o�^����Ă��܂���");
	return &(mapresource->model[index]);	
	
}

//==============================================================================
/**
 * MAP_RESOURCE�̉��
 *
 * @param   mapresource		MAP_RESOURCE�̃|�C���^
 *
 * @retval  none		
 */
//==============================================================================
void ReleaseMapResource(MAP_RESOURCE_PTR *mapresource)
{
	int i;

	//�}�e���A���A�V�F�C�v�Ή��f�[�^���
	if ((*mapresource)->MatShpData != NULL){
		FreeMatShpData((*mapresource)->MatShpData);
	}

	for(i=0;i<BUILD_MODEL_MAX;i++){
		if((*mapresource)->model[i]!=NULL){
			sys_FreeMemoryEz((*mapresource)->model[i]);
		}
	}

	sys_FreeMemoryEz((*mapresource)->ModelFile);
	
	sys_FreeMemoryEz((*mapresource)->pTexFile);			// �t�B�[���h���ʃe�N�X�`�����
	(*mapresource)->pTexFile   = NULL;
	sys_FreeMemoryEz((*mapresource)->pBmTexFile);			// �z�u���f���e�N�X�`�����
	(*mapresource)->pBmTexFile   = NULL;
	sys_FreeMemoryEz((*mapresource));						// ���[���h�}�b�v���
	(*mapresource) = NULL;
}

//==============================================================================
/**
 * �e�N�X�`���t�@�C���̎��̂̃|�C���^��Ԃ�
 *
 * @param   mapresource		WORLD_MAP�̃|�C���^
 *
 * @retval  NNSG3dResTex *		�e�N�X�`���f�[�^�̃|�C���^
 */
//==============================================================================
NNSG3dResTex *GetMapResourceTexturePTR(const MAP_RESOURCE_PTR mapresource)
{
	GF_ASSERT((mapresource!=NULL) && "mapresourcemap�����m��");

	return mapresource->Tex;	
}

//==============================================================================
/**
 * �e�N�X�`���t�@�C���̎��̂̃|�C���^��Ԃ�
 *
 * @param   mapresource		WORLD_MAP�̃|�C���^
 *
 * @retval  NNSG3dResTex *		�e�N�X�`���f�[�^�̃|�C���^
 */
//==============================================================================
NNSG3dResTex *GetMapResourceBmTexturePTR(const MAP_RESOURCE_PTR mapresource)
{
	GF_ASSERT((mapresource!=NULL) && "mapresourcemap�����m��");

	return mapresource->BmTex;	
}

//==============================================================================
/**
 * �}�e���A���A�V�F�C�v�Ή��f�[�^�ւ̃|�C���^�擾�֐�
 *
 * @param   mapresource		�}�b�v���\�[�X�̃|�C���^
 *
 * @retval  MSD_CONST_PTR	�}�e���A���A�V�F�C�v�Ή��f�[�^�ւ̃|�C���^
 */
//==============================================================================

MSD_CONST_PTR GetMatShpDataPtr(const MAP_RESOURCE_PTR mapresource)
{
	return mapresource->MatShpData;
}

//==============================================================================
/**
 * ���C�g�L�����ǂ����̎擾�֐�
 *
 * @param   mapresource		�}�b�v���\�[�X�̃|�C���^
 *
 * @retval  BOOL	TRUE:���C�g�L��		FALSE:���C�g����
 */
//==============================================================================
BOOL MAPRES_IsValidLight(const MAP_RESOURCE_PTR mapresource)
{
	if (mapresource->ResourceParam.light){
		return TRUE;
	}else{
		return FALSE;
	}
}

//==============================================================================
/**
 * ���C�g�C���f�b�N�X���擾
 *
 * @param   mapresource		�}�b�v���\�[�X�̃|�C���^
 *
 * @retval  light_idx	���C�g�C���f�b�N�X
 */
//==============================================================================
u8 MAPRES_GetLightIndex(const MAP_RESOURCE_PTR mapresource)
{
	u8 light_idx; 
	if (mapresource->ResourceParam.light == 0 ){
		light_idx = LIGHT_TYPE2;
	}else{
		light_idx = LIGHT_TYPE1;
	}
	return light_idx;
}

//==============================================================================
/**
 * ���f���t�@�C������OBJID���擾
 *
 * @param   mapresource		�}�b�v���\�[�X�̃|�C���^
 * @param	inIndex			���X�g�C���f�b�N�X
 *
 * @retval  obj_id				OBJID�i�C���f�b�N�X0�Ԗڂ͌��j
 */
//==============================================================================
int MAPRES_GetObjIDFromModelFile(const MAP_RESOURCE_PTR inMapResource, const int inIndex)
{
	int obj_id;
	obj_id = inMapResource->ModelFile[inIndex];
	return obj_id;
}

//==============================================================================
/**
 * ���\�[�X�̃G���g���[�`�F�b�N
 *
 * @param   mapresource		�}�b�v���\�[�X�̃|�C���^
 * @param	inID			OBJID
 *
 * @retval  TRUE:�o�^�ς�	FALSE:���o�^
 */
//==============================================================================
BOOL CheckResourceEntry(const MAP_RESOURCE_PTR mapresource, const int inID)
{
	if ( mapresource->model[inID] == NULL ){
		return FALSE;
	}else{
		return TRUE;
	}
}

#ifdef PM_DEBUG
static void DebugPrintTexInfo(NNSG3dResTex *pTex)
{
	int szTex,numTex;
	// �K�v�ȃT�C�Y���擾
	szTex    = NNS_G3dTexGetRequiredSize(pTex);
	numTex = pTex->dict.numEntry;
	OS_Printf("texsize = %d\n",szTex);
	OS_Printf("texnum = %d\n",numTex);
	{
		u32 fmt;
		int w,h;
		int i;
		int size;
		int total;
		total = 0;
		for(i=0;i<numTex;i++){
			const NNSG3dResName* name = NNS_G3dGetResNameByIdx(&pTex->dict, i);
			const NNSG3dResDictTexData* texData = NNS_G3dGetTexDataByName(pTex, name);
			fmt = (texData->texImageParam >> 26) & 7;
			size = (texData->extraParam & 0x3ff) * ( (texData->extraParam >> 11) & 0x3ff );
			switch(fmt){
			case 1:
				//RES_PRINTF("a3i5");
				break;
			case 2:
				//RES_PRINTF("palette4");
				size/=4;
				break;
			case 3:
				//RES_PRINTF("palette16");
				size/=2;
				break;
			case 4:
				//RES_PRINTF("palette256");
				break;
			case 5:
				//RES_PRINTF("tex4x4");
				break;
			case 6:
				//RES_PRINTF("a5i3");
				break;
			case 7:
				//RES_PRINTF("direct");
				break;
			}
			total+=size;
			OS_Printf("fmt=%d\n",fmt );
			OS_Printf("Addr=%d\n",(texData->texImageParam & 0xffff) << 3 );
		}//end for
	}
}

#endif //PM_DEBUG

