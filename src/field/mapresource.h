//=============================================================================
/**
 *	@brief	�}�b�v���\�[�X����w�b�_�t�@�C��
 *
 *	@param	none
 *	@retval	none
 */
//=============================================================================
 
#include "field_common.h" 
#include "mapresource_def.h"
#include "field_3d_anime.h"
#include "mat_shp.h"
/*** �֐��v���g�^�C�v ***/
extern MAP_RESOURCE_PTR AllocMapResource(int area_id,FLD_3D_ANM_MNG_PTR field_3d_anime);
extern void SetupMapResource(MAP_RESOURCE_PTR outMapResource);
extern void ReleaseMapResource(MAP_RESOURCE_PTR *mapresource);

extern NNSG3dResFileHeader** GetMapResourceModelRes(const int index, const MAP_RESOURCE_PTR mapresource);
extern NNSG3dResTex *GetMapResourceTexturePTR(const MAP_RESOURCE_PTR mapresource);
extern NNSG3dResTex *GetMapResourceBmTexturePTR(const MAP_RESOURCE_PTR mapresource);

//�}�e���A���A�V�F�C�v�Ή��f�[�^�ւ̃|�C���^�擾�֐�
extern MSD_CONST_PTR GetMatShpDataPtr(const MAP_RESOURCE_PTR mapresource);
extern BOOL MAPRES_IsValidLight(const MAP_RESOURCE_PTR mapresource);
extern u8 MAPRES_GetLightIndex(const MAP_RESOURCE_PTR mapresource);

extern int MAPRES_GetObjIDFromModelFile(const MAP_RESOURCE_PTR inMapResource, const int inIndex);

extern BOOL CheckResourceEntry(const MAP_RESOURCE_PTR mapresource, const int inID);

