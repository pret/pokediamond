//============================================================================================
/**
 * @file	map3d_object.c
 * @bfief	�}�b�v3D�I�u�W�F�N�g�i�z�u���f���j����
 * @author	Nozomu Saitou
 *
 * 2005.12.18	field_encount.c����G���J�E���g���蕔�����ړ�
 */
//============================================================================================

//#define DEBUG_EXP_DISP

#include "common.h"
#include "map3d_object.h"
#include "mapresource.h"
#include "mat_shp.h"
#include "field_light.h"

#ifdef DEBUG_EXP_DISP

static u8 DebugExpAddCnt = 0;
static u8 DebugExpDrawCnt = 0;

#endif

static void SetMap3DModel(	const int inID,
							const MAP_RESOURCE_PTR inMapResource,
							NNSG3dRenderObj* object_p,
							NNSG3dResMdl** model);
static void DrawModelQuick(	const NNSG3dResMdl* pResMdl,
							VecFx32* trans_p,
							MtxFx33* rot_p,
							VecFx32* scale_p,
							MSD_CONST_PTR inMatShpData,
							const int inObjID);

typedef	struct	{
	int	id;			//�f�[�^�h�c

	VecFx32  global;	//�O���[�o�����W
	VecFx32  rotate;	//��]
	VecFx32  scale;		//�X�P�[��

	int		dummy[2];	//
}MAP3D_OBJECT_HEADER;

typedef	struct	MAP3D_OBJECT_DATA_tag{
	int	id;			//�f�[�^�h�c
	BOOL	valid;	//�f�[�^�̗L����
	BOOL	Vanish;	//�o�j�b�V���t���O
	BOOL	RotateFlg;	//��]���邩�t���O
	NNSG3dRenderObj	objectdata;
///	NNSG3dAnmObj*   objectanime;				//���f���A�j���f�[�^�|�C���^
	NNSG3dResMdl* 	objectmodel;				//���f�����O�f�[�^�|�C���^

	VecFx32  global;	//�O���[�o�����W
	VecFx32  rotate;	//��]
	VecFx32  scale;		//�X�P�[��
///	NNSG3dResTex*	p_defaultTex;	20060117del
}MAP3D_OBJECT_DATA;

typedef	struct	MAP3D_OBJECT_LIST_tag{
	MAP3D_OBJECT_DATA Map3DObjectData[MAP_READ_OBJ_3D_MAX];
}MAP3D_OBJECT_LIST;


//==============================================================================
/**
 * 3DOBJ������
 *
 * @param	inNum		�쐬��
 * @param	inHeapID	�q�[�vID
 *
 * @return	M3DO_PTR	�m�ۂ��ꂽ3DOBJ�̐擪�|�C���^
 */
//==============================================================================
M3DOL_PTR M3DO_AllocMap3DObjList(const u8 inHeapID)
{
	M3DOL_PTR obj_list_ptr;
	obj_list_ptr = sys_AllocMemory(inHeapID, sizeof(MAP3D_OBJECT_LIST));
	M3DO_CleanMap3DObjList(obj_list_ptr);
	return obj_list_ptr;
}

//==============================================================================
/**
 * 3DOBJ���
 *
 * @param	outMap3DObjList		3DOBJ���X�g�ւ̃|�C���^
 *
 * @return	none
 */
//==============================================================================
void M3DO_FreeMap3DObjList(M3DOL_PTR outMap3DObjList)
{
	sys_FreeMemoryEz(outMap3DObjList);
	outMap3DObjList = NULL;
}

//==============================================================================
/**
 * 3DOBJ�N���[��
 *
 * @param	outMap3DObjList		3DOBJ���X�g�ւ̃|�C���^
 *
 * @return	none
 */
//==============================================================================
void M3DO_CleanMap3DObjList(M3DOL_PTR outMap3DObjList)
{
	u8 i;
	for(i=0;i<MAP_READ_OBJ_3D_MAX;i++){
		VecFx32 init_data = {0,0,0};
		outMap3DObjList->Map3DObjectData[i].id			= 0;// =OFF
		outMap3DObjList->Map3DObjectData[i].valid		= FALSE;// �f�[�^����
		outMap3DObjList->Map3DObjectData[i].Vanish		= FALSE;
		outMap3DObjList->Map3DObjectData[i].RotateFlg	= FALSE;
		outMap3DObjList->Map3DObjectData[i].global		= init_data;
		outMap3DObjList->Map3DObjectData[i].rotate		= init_data;
		outMap3DObjList->Map3DObjectData[i].scale		= init_data;
		outMap3DObjList->Map3DObjectData[i].objectmodel	= NULL;
	}
}

//==============================================================================
/**
 * �w��C���f�b�N�X��3DOBJ�N���[��
 *
 * @param	inIndex				�o�^�C���f�b�N�X
 * @param	outMap3DObjList		3DOBJ���X�g�ւ̃|�C���^
 *
 * @return	none
 */
//==============================================================================
void M3DO_CleanMap3DObj(const int inIndex, M3DOL_PTR outMap3DObjList)
{
	GF_ASSERT(inIndex<MAP_READ_OBJ_3D_MAX&&"�C���f�b�N�X�I�[�o�[");
	{
		VecFx32 init_data = {0,0,0};
		outMap3DObjList->Map3DObjectData[inIndex].id		= 0;// =OFF
		outMap3DObjList->Map3DObjectData[inIndex].valid		= FALSE;// �f�[�^����
		outMap3DObjList->Map3DObjectData[inIndex].Vanish	= FALSE;
		outMap3DObjList->Map3DObjectData[inIndex].RotateFlg	= FALSE;
		outMap3DObjList->Map3DObjectData[inIndex].global	= init_data;
		outMap3DObjList->Map3DObjectData[inIndex].rotate	= init_data;
		outMap3DObjList->Map3DObjectData[inIndex].scale		= init_data;
		outMap3DObjList->Map3DObjectData[inIndex].objectmodel		= NULL;
	}
#ifdef DEBUG_EXP_DISP
	GF_ASSERT(DebugExpAddCnt!=0);
	DebugExpAddCnt--;
#endif
}


//==============================================================================
/**
 * 3DOBJ���[�h
 *
 * @param	inMapResource		�}�b�v���\�[�X�|�C���^
 * @param	inFileName			�t�@�C����
 * @param	outMap3DObjList		3DOBJ���X�g�ւ̃|�C���^
 * @param	field_3d_anime_ptr	3D�A�j���|�C���^
 *
 * @return	none
 */
//==============================================================================
void M3DO_LoadArc3DObjData(	ARCHANDLE *ioHandle,
							const int inDataSize,
							const MAP_RESOURCE_PTR inMapResource,
							M3DOL_PTR outMap3DObjList,
							FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	MAP3D_OBJECT_HEADER * obj_dat = NULL;
	u32	obj_max;
	int i;
	//�A�[�J�C�u�f�[�^�ǂݍ���
	if (inDataSize != 0){
		obj_dat = sys_AllocMemoryLo(HEAPID_FIELD, inDataSize);
		ArchiveDataLoadByHandleContinue( ioHandle, inDataSize, obj_dat );
		obj_max = inDataSize / sizeof(MAP3D_OBJECT_HEADER);
	}else{
		obj_max = 0;
	}
#ifdef DEBUG_ONLY_FOR_saitou
		OS_Printf("local_print obj_max = %d\n",obj_max);
#endif
#ifdef PM_DEBUG
	if (obj_max>MAP_READ_OBJ_3D_MAX){
		OS_Printf("ERROR:OBJ_MAX_OVER obj_num = %d\n",obj_max);
		OS_Printf("%d,%d\n",inDataSize,sizeof(MAP3D_OBJECT_HEADER));
		GF_ASSERT(0);
	}
#endif

	for(i=0;i<MAP_READ_OBJ_3D_MAX;i++){
		M3DO_PTR ptr;
		ptr = &(outMap3DObjList->Map3DObjectData[i]);
		if(i < obj_max){
			ptr->id		    = obj_dat[i].id;		//�h�c
			ptr->valid		= TRUE;					//�f�[�^�L��
			ptr->RotateFlg  = FALSE;				//��]����
			ptr->global	    = obj_dat[i].global;	//���W
			ptr->rotate	    = obj_dat[i].rotate;	//��]
			ptr->scale	    = obj_dat[i].scale;		//�X�P�[��
#ifdef DEBUG_ONLY_FOR_saitou
		///OS_Printf("local_print obj_id = %d\n",obj_dat[i].id);
#endif
			// �ǂݍ��񂾃e�N�X�`�����\�[�X���Z�b�g
			SetMap3DModel(
					ptr->id,
					inMapResource,
					&(ptr->objectdata),
					&(ptr->objectmodel) );
			if (CheckResourceEntry(inMapResource, ptr->id) == FALSE){
				OS_Printf("�_�~�[�\���̂��߁A�z�u���f��ID�����������܂�%d��0\n",ptr->id);
				ptr->id = 0;
			}
			
#ifdef FOG_MDL_SET_CHECK
			NNS_G3dMdlSetMdlFogEnableFlagAll(ptr->objectmodel, TRUE);
#endif
			{
/**				
				F3DA_SetFld3DAnime(	ptr->id, 0, FALSE,
									&(ptr->objectdata),
									field_3d_anime_ptr);
*/									
				F3DA_SetFld3DAnimeEasy(	ptr->id,
										&(ptr->objectdata),
										field_3d_anime_ptr);
			}
		}else{
			VecFx32 init_data = {0,0,0};

			ptr->id		    = 0;		// =OFF
			ptr->valid		= FALSE;	//�f�[�^����
			ptr->RotateFlg	= FALSE;
			ptr->global     = init_data;
			ptr->rotate     = init_data;
			ptr->scale	    = init_data;
		}
	}
	if( obj_dat != NULL ){
		sys_FreeMemoryEz( obj_dat );
	}

}

//==============================================================================
/**
 * 3DOBJ�`��
 *
 * @param	inOffset			�`��I�t�Z�b�g
 * @param	inMapResource		�}�b�v���\�[�X
 * @param	inLightValid		���C�g�L��
 * @param	glst_data			�O���[�o���X�e�[�g
 * @param	outMap3DObjList		3DOBJ���X�g�ւ̃|�C���^
 *
 * @return	none
 */
//==============================================================================
void M3DO_DrawMap3DObj(	const VecFx32 *inOffset,
						const MAP_RESOURCE_PTR inMapResource,
						const BOOL inLightValid,
						const GLST_DATA_PTR	glst_data,
						M3DOL_PTR ioMap3DObjList)
{
	//�I�u�W�F�N�g�R�c�`��
	
	int	i;
	VecFx32 obj_trans;
	MtxFx33 rot={FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};
	for(i=0;i<MAP_READ_OBJ_3D_MAX;i++){
		M3DO_PTR ptr;
		ptr = &(ioMap3DObjList->Map3DObjectData[i]);
		if( ptr->valid != FALSE ){
			if (ptr->Vanish){	//�o�j�b�V���`�F�b�N
				continue;
			}
			//
			// �J�����O�`�F�b�N
			// 
			// ���f���̃{�b�N�X�e�X�g�f�[�^�Z�b�g

			//����]�s��̌v�Z�͂��Ȃ����Ƃɂ���i��]�̓T�|�[�g���Ȃ��j
			///VecFx32_to_MtxFx33( &rot, &(inDivMapCont->BlockNodeList[inLocalIndex]->ObjData[i].rotate));
			obj_trans = ptr->global;
			obj_trans.x += inOffset->x;
			obj_trans.z += inOffset->z;
			//�J�����O�`�F�b�N
			if (BB_CullingCheck3DModel(	ptr->objectmodel,
										&(obj_trans),
										&rot,
										&(ptr->scale) ) ) 
			{
				MSD_CONST_PTR mat_shp_data;
				u16 num;
				mat_shp_data = GetMatShpDataPtr(inMapResource);
					
				if (inLightValid == TRUE){
					//�}�e���A���ύX
					GLST_ReflectMdl(glst_data,
									ptr->objectmodel,
									FIELD_LIGHT_MASK);
				}
				GetMatShpNum(	ptr->id,
								mat_shp_data,
								&num);
				if ( num == 0 ){
					simple_3DModelDraw( &(ptr->objectdata),
								    	&(obj_trans),
										&rot,
										&(ptr->scale));
				}else{
					DrawModelQuick( ptr->objectmodel,
									&obj_trans,
									&rot,
									&(ptr->scale),
									mat_shp_data,
									ptr->id);
				}
			}
		}
	}
}

//==============================================================================
/**
 * �擾�֐��@��]�x�N�g���ւ̃|�C���^
 *
 * @param	inMap3DObjData		3DOBJ�ւ̃|�C���^
 *
 * @return	VecFx32				��]�x�N�g���ւ̃|�C���^
 */
//==============================================================================
VecFx32 *M3DO_GetRotateVecPtr(M3DO_PTR inMap3DObjData)
{
	return (&inMap3DObjData->rotate);
}

//==============================================================================
/**
 * �擾�֐��@�O���[�o�����W
 *
 * @param	inMap3DObjData		3DOBJ�ւ̃|�C���^
 *
 * @return	VecFx32				�O���[�o�����W
 */
//==============================================================================
VecFx32 M3DO_GetGlobalVec(M3DO_CONST_PTR inMap3DObjData)
{
	return inMap3DObjData->global;
}
//==============================================================================
/**
 * �Z�b�g�֐��@�O���[�o�����W
 *
 * @param	outMap3DObjData		3DOBJ�ւ̃|�C���^
 * @param	inVec				�O���[�o�����W
 *
 * @return	none
 */
//==============================================================================
void M3DO_SetGlobalVec(M3DO_PTR outMap3DObjData, const VecFx32 *inVec)
{
	outMap3DObjData->global = (*inVec);
}

//==============================================================================
/**
 * �Z�b�g�֐��@�o�j�b�V���t���O�Z�b�g
 *
 * @param	outMap3DObjData		3DOBJ�ւ̃|�C���^
 * @param	inVanish				�o�j�b�V���t���O
 *
 * @return	none
 */
//==============================================================================
void M3DO_SetVanish(M3DO_PTR outMap3DObjData, const BOOL inVanish)
{
	outMap3DObjData->Vanish = inVanish;
}

//==============================================================================
/**
 * �擾�֐��@ID
 *
 * @param	inMap3DObjData		3DOBJ�ւ̃|�C���^
 *
 * @return	int					ID
 */
//==============================================================================
int M3DO_GetObjID(M3DO_CONST_PTR inMap3DObjData)
{
	return inMap3DObjData->id;
}

//==============================================================================
/**
 * �擾�֐��@�����_�[OBJ�f�[�^�ւ̃|�C���^
 *
 * @param	inMap3DObjData		3DOBJ�ւ̃|�C���^
 *
 * @return	NNSG3dRenderObj*	�����_�[OBJ�f�[�^�ւ̃|�C���^
 */
//==============================================================================
NNSG3dRenderObj *M3DO_GetRenderObj(M3DO_CONST_PTR inMap3DObjData)
{
	return (NNSG3dRenderObj *)(&(inMap3DObjData->objectdata));
}

//==============================================================================
/**
 * �擾�֐��@���f�����O�f�[�^�ւ̃|�C���^
 *
 * @param	inMap3DObjData		3DOBJ�ւ̃|�C���^
 *
 * @return	NNSG3dResMdl*		���f�����O�f�[�^�ւ̃|�C���^
 */
//==============================================================================
NNSG3dResMdl *M3DO_GetObjModel(M3DO_CONST_PTR inMap3DObjData)
{
	return inMap3DObjData->objectmodel;
}

//==============================================================================
/**
 * �C���f�b�N�X�Ŏw�肵���}�b�v3DOBJ�̃|�C���^��Ԃ�
 *
 * @param	inMap3DObjList		3DOBJ�̐擪�̃|�C���^
 * @param	inIndex				�C���f�b�N�X
 *
 * @return	NNSG3dResMdl*		���f�����O�f�[�^�ւ̃|�C���^
 */
//==============================================================================
M3DO_PTR M3DO_GetMap3DObjData(M3DOL_PTR inMap3DObjList, const u8 inIndex)
{
	return &inMap3DObjList->Map3DObjectData[inIndex];
}

//==============================================================================
/**
 * �w�肵��OBJID������3DOBJ��Ԃ��֐��i�n�߂Ƀq�b�g����1�̂ݕԂ��j
 *
 * @param	outMap3DObjList		3DOBJ���X�g�ւ̃|�C���^
 * @param	inObjID				OBJID
 *
 * @return	M3DO_PTR			�I�u�W�F�N�g�|�C���^
 */
//==============================================================================
M3DO_PTR M3DO_GetMap3DObjDataFromID(M3DOL_PTR inMap3DObjList, const int inObjID)
{
	M3DO_PTR ptr;
	int i;
	for(i=0;i<MAP_READ_OBJ_3D_MAX;i++){
		ptr = &inMap3DObjList->Map3DObjectData[i];
		if (ptr->id == inObjID){
			return ptr;
		}
	}
	return NULL;
}

//==============================================================================
/**
 * �w�肵���o�^�C���f�b�N�X��DOBJ��Ԃ��֐�
 *
 * @param	outMap3DObjList		3DOBJ���X�g�ւ̃|�C���^
 * @param	inIndex				�o�^�C���f�b�N�X
 *
 * @return	M3DO_PTR			�I�u�W�F�N�g�|�C���^
 */
//==============================================================================
M3DO_PTR M3DO_GetMap3DObjDataFromIndex(M3DOL_PTR inMap3DObjList, const int inIndex)
{
	M3DO_PTR ptr;
	GF_ASSERT(inIndex<MAP_READ_OBJ_3D_MAX&&"�C���f�b�N�X�I�[�o�[�ł�");
	
	ptr = &inMap3DObjList->Map3DObjectData[inIndex];
	
	GF_ASSERT(ptr->valid&&"�f�[�^�͖����ł�");

	return ptr;
}

//--------------------------------------------------------------------------------------------
/**
 * ���f���Z�b�g
 *
 * @param	inID			���f���h�c
 * @param	inMapResource	�}�b�v���\�[�X�|�C���^
 * @param	* object_p		���f���I�u�W�F�N�g�|�C���^
 * @param	** model		���f���f�[�^�ւ̃|�C���^�̃|�C���^
 * @param	** pp_res_tex	�e�N�X�`�����\�[�X�ւ̃|�C���^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void SetMap3DModel(	const int inID,
							const MAP_RESOURCE_PTR inMapResource,
							NNSG3dRenderObj* object_p,
							NNSG3dResMdl** model)
{
	///simple_3DModelSetResFileAlready(object_p,model,GetMapResourceModelRes(inID,inMapResource));
	NNSG3dResFileHeader** resFile = GetMapResourceModelRes(inID,inMapResource);
	*model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*resFile), 0);
	NNS_G3dRenderObjInit(object_p, *model);
}

//==============================================================================
/**
 * 3DOBJ�����`��
 *
 * @param	pResMdl			���\�[�X
 * @param	trans_p			�ړ����W
 * @param	rot_p			��]�}�g���N�X
 * @param	scale_p			�g�k�}�g���N�X
 * @param	inMatShpData	�}�b�g�V�F�C�v�f�[�^
 * @param	inObjID			OBJID
 *
 * @return	none
 */
//==============================================================================
static void DrawModelQuick(	const NNSG3dResMdl* pResMdl,
							VecFx32* trans_p,
							MtxFx33* rot_p,
							VecFx32* scale_p,
							MSD_CONST_PTR inMatShpData,
							const int inObjID)
{
	u8 i;
	u16 num;
	u16 idx;
	u8 mat_id;
	BOOL send_flg;
	MAT_SHP const *mat_shp;
	//���J�����O�`�F�b�N��ɂ����ɕ`�悷��Ȃ�΁A���łɃZ�b�g�ς݂Ȃ̂ŕs�v

	// �ʒu�ݒ�
	NNS_G3dGlbSetBaseTrans(trans_p);	
	// �p�x�ݒ�
	NNS_G3dGlbSetBaseRot(rot_p);
	// �X�P�[���ݒ�
	NNS_G3dGlbSetBaseScale(scale_p);
	
	NNS_G3dGlbFlush();	//�}�g���N�X���f

	GetMatShpNumAndIdx(	inObjID,
						inMatShpData,
						&num,
						&idx);
	mat_shp = GetMatShp(idx, inMatShpData);
	mat_id = 0xff;
	send_flg = TRUE;
	for(i=0;i<num;i++){
		if (mat_id != mat_shp[i].matID){
			mat_id = mat_shp[i].matID;
			send_flg = TRUE;
		}else{
			send_flg = FALSE;
		}
		NNS_G3dDraw1Mat1Shp(pResMdl,
							mat_id,//matID,
							mat_shp[i].shpID,//shpID,
							send_flg//sendMat
							);
		
	}
	//���W�I���g���R�}���h�o�b�t�@���ݒ肳��Ă��Ȃ��̂ŁA�s�v
	//NNS_G3dGeFlushBuffer();
}

//==============================================================================
/**
 * �g���}�b�v3DOBJ�̃Z�b�g
 *
 * @param	outMap3DObjList		3DOBJ���X�g�ւ̃|�C���^
 * @param	inMapResource		�}�b�v���\�[�X�|�C���^
 * @param	inObjID				OBJID
 * @param	inTrans				�ʒu���W
 * @param	inRotate			��]
 * @param	field_3d_anime_ptr	�A�j���|�C���^
 *
 * @return	u8				�o�^�C���f�b�N�X
 */
//==============================================================================
u8 M3DO_SetMap3DObjExp(	M3DOL_PTR outMap3DObjList,
						const MAP_RESOURCE_PTR inMapResource,
						const int inObjID,
						const VecFx32 *inTrans,
						const VecFx32 *inRotate,
						FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	u8 i;
	VecFx32 scale = {FX32_ONE,FX32_ONE,FX32_ONE};

	for(i=0;i<MAP_READ_OBJ_3D_MAX;i++){
		M3DO_PTR ptr;
		ptr = &(outMap3DObjList->Map3DObjectData[i]);
		if (ptr->valid == FALSE){
			ptr->valid = TRUE;	//�f�[�^�̗L����
			ptr->global = (*inTrans);	//�O���[�o�����W
			//��]
			if (inRotate != NULL){
				ptr->RotateFlg = TRUE;
				ptr->rotate = (*inRotate);
			}else{
				ptr->RotateFlg = FALSE;
			}
			ptr->scale = scale;		//�X�P�[��
			ptr->id = inObjID;
			SetMap3DModel(
					ptr->id,
					inMapResource,
					&(ptr->objectdata),
					&(ptr->objectmodel) );
			//�A�j���Z�b�g
			F3DA_SetFld3DAnime(	ptr->id, 0, FALSE,
								&(ptr->objectdata),
								field_3d_anime_ptr);
#ifdef DEBUG_EXP_DISP
			DebugExpAddCnt++;
#endif
			return i;
		}
	}
	
	GF_ASSERT(0&&"�o�^���s");
	return MAP_READ_OBJ_3D_MAX;
}

//==============================================================================
/**
 * �g���}�b�v3DOBJ�̕`��
 *
 * @param	inMap3DObjList	3DOBJ���X�g�ւ̃|�C���^
 * @param	inMapResource	�}�b�v���\�[�X�|�C���^
 *
 * @return	none
 */
//==============================================================================
void M3DO_DrawMap3DObjExp(M3DOL_PTR inMap3DObjList, const MAP_RESOURCE_PTR inMapResource)
{
	u8 i;
	MtxFx33 rot={FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};

#ifdef DEBUG_EXP_DISP
	DebugExpDrawCnt = 0;
#endif
	
	for(i=0;i<MAP_READ_OBJ_3D_MAX;i++){
		M3DO_PTR ptr;
		ptr = &(inMap3DObjList->Map3DObjectData[i]);
		if ( ptr->valid ){
			if (ptr->Vanish){	//�o�j�b�V���`�F�b�N
				continue;
			}
			{
				MSD_CONST_PTR mat_shp_data;
				u16 num;
				mat_shp_data = GetMatShpDataPtr(inMapResource);
					
				GetMatShpNum(	ptr->id,
								mat_shp_data,
								&num);
				if (ptr->RotateFlg){
						VecFx32_to_MtxFx33( &rot, &ptr->rotate);
					}
				if ( num == 0 ){	
					simple_3DModelDraw( &(ptr->objectdata),
								    	&(ptr->global),
										&rot,
										&(ptr->scale) );
				}else{
					DrawModelQuick( ptr->objectmodel,
									&ptr->global,
									&rot,
									&(ptr->scale),
									mat_shp_data,
									ptr->id);
				}
#ifdef DEBUG_EXP_DISP				
				DebugExpDrawCnt++;
#endif				
			}
		}
	}

#ifdef DEBUG_EXP_DISP
	if (sys.trg & PAD_BUTTON_L){
		OS_Printf("add_draw:%d,%d\n",DebugExpAddCnt,DebugExpDrawCnt);
	}
#endif
}
