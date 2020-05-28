//=============================================================================
/**
 * @file	worldmap.c
 * @bfief	���[���h�}�b�v�\�z����
 * @author	saitou, mori GAME FREAK inc.
 *
 *
 */
//=============================================================================
// �G���A���Ƀe�N�X�`���t�@�C����؂�ւ���̂ŁA�G���A�J�ڂ����ۂ�
// �e�N�X�`���t�@�C�����G���A�ԍ����琶�����ēǂݍ��ޏ����̒ǉ�����X�s��


#include "common.h"
#include "height_def.h"
#include "calctool.h"

#include "worldmap.h"

#include "fieldsys.h"
#include "debug_saito.h"

#include "mapdefine.h"
#include "zonedata.h"
#include "mapdefine.h"
#include "system/arc_tool.h"

#include "include/field/field_matrix.h"


//===========================================================================
// �萔
//===========================================================================
///#define	OLD_MAP_MATRIX
#define MAP_MATRIX_WIDTH_MAX	(30)
#define MAP_MATRIX_HEIGHT_MAX	(30)
#define MAP_MATRIX_MAX			(MAP_MATRIX_WIDTH_MAX*MAP_MATRIX_HEIGHT_MAX)
#define MAP_MATRIX_PREFIX_MAX	(16)

//===========================================================================
// �\���̒�`
//===========================================================================
//------------------------------------------------------------------
///	�}�b�v�}�g���b�N�X���ێ��p���[�N
//------------------------------------------------------------------
typedef struct MATRIX_TABLE_tag
{
	u8	size_h;							///<�}�b�v�}�g���b�N�X�̏c��
	u8	size_w;							///<�}�b�v�}�g���b�N�X�̉���
	u16	ZoneMat[MAP_MATRIX_MAX];		///<�]�[��ID�e�[�u��
	u8	HeightBase[MAP_MATRIX_MAX];		///<�����w��e�[�u��
	u16	ArcIndex[MAP_MATRIX_MAX];		///<�A�[�J�C�u�C���f�b�N�X�e�[�u��
	u8	Prefix[MAP_MATRIX_PREFIX_MAX];	///<�t�@�C�����̃v���t�B�b�N�X
}MATRIX_TABLE;

//------------------------------------------------------------------
///	���[���h�}�b�v�\����
//------------------------------------------------------------------
struct _WORLD_MAP{
	u8  MatrixW,MatrixH;						///< �G���A�̏c����
	u8 matrix_id;
	MATRIX_TABLE MapMatrix;
};




//============================================================================================
//============================================================================================
//------------------------------------------------------------------
//�A�[�J�C�o����}�g���b�N�X���擾
//------------------------------------------------------------------
static void SetupMapMatrix(MATRIX_TABLE * Mmtx, const u16 matrix_id, int zone_id)
{
	u8 zone_flg,height_flg;
	u8 prefix_size;
	void *mem;
	u8 *p;

	{
		int i;
		//�\���̏�����
		Mmtx->size_w = 0;
		Mmtx->size_h = 0;
	
		for(i=0;i<MAP_MATRIX_MAX;i++){
			Mmtx->ZoneMat[i] = 0;
			Mmtx->HeightBase[i] = 0;
			Mmtx->ArcIndex[i] = 0;
		}
		for(i=0;i<MAP_MATRIX_PREFIX_MAX;i++){
			Mmtx->Prefix[i] = 0;
		}
	}
	
	mem = ArchiveDataLoadMallocLo( ARC_MAP_MATRIX, matrix_id, HEAPID_WORLD );
	p = &((u8*)(mem))[0];
	Mmtx->size_w = *p;	//���T�C�Y
	p++;
	Mmtx->size_h = *p;	//�c�T�C�Y
	p++;
	zone_flg = *p;
	p++;
	height_flg = *p;
	p++;
	prefix_size = *p;					//�v���t�B�N�X������T�C�Y
	p++;

	GF_ASSERT(prefix_size <= MAP_MATRIX_PREFIX_MAX);
	MI_CpuCopy8(p,Mmtx->Prefix,prefix_size);
	p+=(prefix_size);

#ifdef	DEBUG_ONLY_FOR_saitou
	OS_Printf("data=%d,%d,%d,%d\n",Mmtx->size_w,Mmtx->size_h,zone_flg,height_flg);
	OS_Printf("prefix = %s,%d\n",Mmtx->Prefix,prefix_size);
#endif
	
	if (zone_flg){
		MI_CpuCopy8(p, Mmtx->ZoneMat, Mmtx->size_w * Mmtx->size_h * 2);
		p+=(Mmtx->size_w * Mmtx->size_h * 2);
	}else{
		//�]�[���w��̃}�g���b�N�X�\���Ȃ��ꍇ�́A�]�[��ID��~���l�߂Đ�������
		MI_CpuFill16(Mmtx->ZoneMat, zone_id, Mmtx->size_w * Mmtx->size_h * sizeof(u16));
	}
	if (height_flg){
		MI_CpuCopy8(p, Mmtx->HeightBase, Mmtx->size_w * Mmtx->size_h);
		p+=(Mmtx->size_w * Mmtx->size_h);
	}

	MI_CpuCopy8(p, Mmtx->ArcIndex, Mmtx->size_w * Mmtx->size_h*2);
	
	sys_FreeMemoryEz(mem);
}

//------------------------------------------------------------------
//------------------------------------------------------------------
WORLD_MAP_PTR WorldMapInit(void)
{
	WORLD_MAP_PTR world;

	// ���[���h�}�b�v�\���̃��[�N���m��
	world = sys_AllocMemory(HEAPID_WORLD,sizeof(WORLD_MAP));

	world->MatrixW = 0;
	world->MatrixH = 0;
	
	world->matrix_id = 0;
	
	return world;
}

//==============================================================================
/**
 * �]�[���h�c�����ɁA�}�b�v�}�g���b�N�X���쐬
 *
 * @param   zone_id	�]�[���h�c
 * @param   world	WORLD_MAP�\���̂̃|�C���^
 *
 * @retval  none		
 */
//==============================================================================
void SetUpWorldMatrix(const int zone_id, WORLD_MAP_PTR world)
{
	u16 matrix_id;

	matrix_id = ZoneData_GetMatrixID(zone_id);
	//�A�[�J�C�o����}�g���b�N�X���擾
	SetupMapMatrix(&world->MapMatrix,matrix_id,zone_id);
	world->matrix_id = matrix_id;
	world->MatrixH = world->MapMatrix.size_h;
	world->MatrixW = world->MapMatrix.size_w;
}


//==============================================================================
/**
 * ���[���h�}�b�v�\���̂̉��
 *
 * @param   world		WORLD_MAP�̃|�C���^
 *
 * @retval  none		
 */
//==============================================================================
void WorldMapRelease(const WORLD_MAP_PTR world)
{
	sys_FreeMemoryEz(world);						// ���[���h�}�b�v���
	
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//
//
// �������牺��WORLD_MAP�̃����o���Q�Ƃ��邽�߂̃C���^�[�t�F�[�X�֐��ł��B
//
//
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
u16 GetArcIndexFromBlockIndex(int index, const WORLD_MAP_PTR world)
{
	GF_ASSERT((index<(world->MatrixW*world->MatrixH)) && "�}�b�v�͈̔͂𒴂��Ă���");
	return world->MapMatrix.ArcIndex[index];
}

//==============================================================================
/**
 * ���ݓǂݍ���ł��郏�[���h�}�b�v�̉������擾����
 *
 * @param   world		WORLD_MAP�̃|�C���^
 *
 * @retval  int			����
 */
//==============================================================================
int  GetWorldMapMatrixW(const WORLD_MAP_PTR world)
{
	GF_ASSERT((world!=NULL) && "worldmap�����m��");

	return world->MatrixW;
}
//==============================================================================
/**
 * ���ݓǂݍ���ł��郏�[���h�}�b�v�̏c�����擾����
 *
 * @param   world		WORLD_MAP�̃|�C���^
 *
 * @retval  int			�c��
 */
//==============================================================================
int  GetWorldMapMatrixH(const WORLD_MAP_PTR world)
{
	GF_ASSERT((world!=NULL) && "worldmap�����m��");

	return world->MatrixH;

}


//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�u���b�N���W�����ƂɃ}�b�v�}�g���b�N�X����̃]�[��ID�擾
 * @param	world	WORLD_MAP�̃|�C���^
 * @param	gx		X�ʒu�i�n�`�u���b�N�P�ʁj
 * @param	gz		Z�ʒu�i�n�`�u���b�N�P�ʁj
 */
//------------------------------------------------------------------
u16 World_GetZoneIDFromMatrixXZ(const WORLD_MAP * world, int gx, int gz)
{
	int gw = world->MatrixW;
	int gh = world->MatrixH;
	GF_ASSERT(0 <= gx && gx < gw);
	GF_ASSERT(0 <= gz && gz < gh);
	return world->MapMatrix.ZoneMat[gx + gz * gw];
}

//------------------------------------------------------------------
/**
 * @brief	�u���b�N�C���f�b�N�X�����Ƀ}�b�v�}�g���b�N�X����̃]�[��ID�擾
 * @param	world	WORLD_MAP�̃|�C���^
 * @param	gx		X�ʒu�i�n�`�u���b�N�P�ʁj
 * @param	gz		Z�ʒu�i�n�`�u���b�N�P�ʁj
 */
//------------------------------------------------------------------
u16 World_GetZoneIDFromBlockIdx(const WORLD_MAP * world, const int inBlockIdx)
{
	int idx_max = world->MatrixW*world->MatrixH;
#ifdef	DEBUG_ONLY_FOR_saitou	
	OS_Printf("local_print idx=%d,%d",idx_max,inBlockIdx);
#endif	
	GF_ASSERT(0 <= inBlockIdx && inBlockIdx < idx_max);
	return world->MapMatrix.ZoneMat[inBlockIdx];
}

//==============================================================================
/**
 * �}�g���b�N�XID�擾
 *
 * @param   world	WORLD_MAP�̃|�C���^
 *
 * @retval  none		
 */
//==============================================================================

u8 GetWorldMatrixID(const WORLD_MAP_PTR world)
{
	return world->matrix_id;
}

//==============================================================================
/**
 * �}�g���N�XID����]�[��ID���擾
 *
 * @param   world		WORLD_MAP�̃|�C���^
 * @param   matrix_id	�}�g���N�XID
 * @param   gx			X���W(�u���b�N)
 * @param   gz			Z���W(�u���b�N)
 * @param   gw			��
 *
 * @retval  int			�]�[��ID		
 */
//==============================================================================
int GetZoneIDFromMatrixID(	const WORLD_MAP_PTR world,
							const int matrix_id,
							const int gx,
							const int gz,
							const int gw)
{
	GF_ASSERT(gx < gw);
	GF_ASSERT( (gx + gz * gw) < MAP_MATRIX_MAX );
	return world->MapMatrix.ZoneMat[gx + gz * gw];
}

//==============================================================================
/**
 * �}�g���N�XID���獂���x�[�X���擾
 *
 * @param   world		WORLD_MAP�̃|�C���^
 * @param   matrix_id	�}�g���N�XID
 * @param   gx			X���W
 * @param   gz			Z���W
 * @param   gw			��
 *
 * @retval  int			�����x�[�X		
 */
//==============================================================================
int GetHeightBaseFromMatrixID(	const WORLD_MAP_PTR world,
								const int matrix_id,
								const int gx,
								const int gz,
								const int gw)
{
	GF_ASSERT(gx < gw);
	GF_ASSERT( (gx + gz * gw) < MAP_MATRIX_MAX );
	return world->MapMatrix.HeightBase[gx + gz * gw];
}

//==============================================================================
//==============================================================================
//
//		�A�v���P�[�V�����p�A�N�Z�X�֐�
//
//==============================================================================
//==============================================================================
typedef struct FIELD_MAT_ZONE_ID_tag
{
	u16 ZoneMat[MAP_MATRIX_MAX];
}FIELD_MAT_ZONE_ID;

//==============================================================================
/**
 * �t�B�[���h�}�g���N�X�\���̍쐬
 *
 * @param   inHeapID	�q�[�vID
 *
 * @retval  FMZ_PTR		�\���̂ւ̃|�C���^		
 */
//==============================================================================
FMZ_PTR InitFMZ(const u32 inHeapID)
{
	int prefix_size;
	void *mem;
	u8 *p;
	FMZ_PTR fmz_p;
	fmz_p = sys_AllocMemory(inHeapID, sizeof(FIELD_MAT_ZONE_ID));

	mem = ArchiveDataLoadMallocLo( ARC_MAP_MATRIX, MATRIX_ID_SINOU, inHeapID );
	p = &((u8*)(mem))[0];
	//���T�C�Y
	p++;
	//�c�T�C�Y
	p++;
	//�]�[���t���O
	p++;
	//�n�C�g�t���O
	p++;
	prefix_size = *p;					//�v���t�B�N�X������T�C�Y
	p++;
	p+=(prefix_size);

	MI_CpuCopy8(p,fmz_p->ZoneMat,30*30*2);
	
	sys_FreeMemoryEz(mem);
	
	return fmz_p;
}

//==============================================================================
/**
 * �t�B�[���h�}�g���N�X�\���̉��
 *
 * @param   fmzp		�\���̂ւ̃|�C���^
 *
 * @retval  none		
 */
//==============================================================================
void FreeFMZ(FMZ_PTR fmzp)
{
	GF_ASSERT(fmzp!=NULL);
	sys_FreeMemoryEz(fmzp);
}

//==============================================================================
/**
 * �u���b�N���W����A�\�[��ID���擾
 *
 * @param   fmzp		�\���̂ւ̃|�C���^
 * @param   inBlockX	�u���b�NX���W
 * @param   inBlockZ	�u���b�NZ���W
 *
 * @retval  none		
 */
//==============================================================================
int GetFieldMatrixZoneID(const FMZ_CONST_PTR fmdp, const u32 inBlockX, const u32 inBlockZ)
{
	return fmdp->ZoneMat[inBlockX+inBlockZ*MAP_MATRIX_WIDTH_MAX];
}

#ifdef PM_DEBUG
//==============================================================================
/**
 * @brief	�w�肵���]�[���̍���u���b�N���W���擾����
 *
 * @param	zoneID		�]�[��ID
 * @param   px			�擾�����u���b�NX���W���i�[����|�C���^
 * @param   pz			�擾�����u���b�NZ���W���i�[����|�C���^
 *
 * @retval  none		
 */
//==============================================================================
int GetBlockPosFromZoneID(int zoneID,u16* px,u16* pz)
{
	MATRIX_TABLE	mData;
	u16	x,z;
	int	matrixID;
		
	matrixID = ZoneData_GetMatrixID(zoneID);
	SetupMapMatrix(&mData,matrixID,zoneID);

	for(z = 0;z < mData.size_h;z++){
		for(x = 0;x < mData.size_w;x++){
			if(mData.ZoneMat[z*mData.size_w+x] == zoneID){
				*px = x;
				*pz = z;
				return 1;
			}
		}
	}
	//������Ȃ�
	*px = 0;
	*pz = 0;
	return 0;
}
#endif

//==============================================================================
/**
 * @brief	�w�肵���}�g���b�N�X�h�c�̃u���b�N���W�ɑΉ�����]�[���h�c���擾
 * ���g���ꏊ�͌��肳��܂��B
 *
 * @param   matrixID	�}�g���N�XID
 * @param   x			�u���b�NX���W
 * @param   z			�u���b�NZ���W
 *
 * @retval  int			�]�[���h�c		
 */
//==============================================================================
int GetZoneIDFromMatID(const int inMatID, const u16 inX, const u16 inZ)
{
	MATRIX_TABLE	mData;
	u16	x,z;
		
	SetupMapMatrix(&mData,inMatID,0);

	GF_ASSERT(inX<mData.size_w);
	GF_ASSERT(inZ<mData.size_h);

	return mData.ZoneMat[inZ*mData.size_w+inX];

}

//==============================================================================
/**
 * �w��̃u���b�N�ɑΉ����Ă��鍂���f�[�^�A�[�J�C�u�C���f�b�N�X���擾
 *
 * @param   Block		�u���b�N
 * @param   mapresource		WORLD_MAP�̃|�C���^
 *
 * @retval  char *		�u���b�N�t�@�C�����̃|�C���^
 */
//==============================================================================
const u16 GetWorldMapArcIdx(const int Block, const WORLD_MAP_PTR world)
{
	u16 index;
	int ggx = Block % world->MatrixW;							//���݂̓]�[������񂪖����̂ŉ��\�z
	int ggz = Block / world->MatrixW;
	GF_ASSERT((world!=NULL) && "world�����m��");

	index = GetArcIndexFromBlockIndex(Block,world);
	return index;
}



//============================================================================================
//
//
//			�}�b�v�����������ꏈ��
//
//
//			���ėp���͂܂������Ȃ��B�_�C�������h���p�[����p���Ǝv����
//
//
//============================================================================================
#include "../fielddata/land_data/land_data.naix"

//------------------------------------------------------------------
/**
 * @brief	�N���A��̌΂��o��������
 * @param	world	WORLD_MAP�̃|�C���^
 */
//------------------------------------------------------------------
void World_Overwrite_L04(WORLD_MAP_PTR world)
{
	u16 * arc_tbl = world->MapMatrix.ArcIndex;
	u8 * height_tbl = world->MapMatrix.HeightBase;
	int map_h = world->MatrixH;
	int map_w = world->MatrixW;
	int i, j;
	if (world->matrix_id != MATRIX_ID_SINOU) {
		return;
	}
	arc_tbl[23 + map_w * 21] = NARC_land_data_ro_tree2_bin;
	arc_tbl[24 + map_w * 21] = NARC_land_data_ro_tree2_bin;
	arc_tbl[23 + map_w * 22] = NARC_land_data_ro_tree2_bin;
	arc_tbl[24 + map_w * 22] = NARC_land_data_ro_tree2_bin;
	height_tbl[23 + map_w * 21] = 2;
	height_tbl[24 + map_w * 21] = 2;
	height_tbl[23 + map_w * 22] = 2;
	height_tbl[24 + map_w * 22] = 2;
}

//------------------------------------------------------------------
/**
 * @brief	�Ԃ̊y���ւ̓����o��������
 * @param	world	WORLD_MAP�̃|�C���^
 */
//------------------------------------------------------------------
void World_Overwrite_R224(WORLD_MAP_PTR world)
{
	int i, j;
	u16 * arc_tbl = world->MapMatrix.ArcIndex;
	int map_h = world->MatrixH;
	int map_w = world->MatrixW;
	if (world->matrix_id != MATRIX_ID_SINOU) {
		return;
	}
	arc_tbl[map_w * 15 + 28] = NARC_land_data_sp28_15_bin;
	arc_tbl[map_w * 16 + 27] = NARC_land_data_sp27_16_bin;
	arc_tbl[map_w * 16 + 28] = NARC_land_data_sp28_16_bin;
	arc_tbl[map_w * 17 + 27] = NARC_land_data_sp27_17_bin;
}




