//============================================================================================
/**
 * @file	sp_attribute.c
 * @brief	����}�g���b�N�X�֘A
 * @author	Nozomu Saito
 * @date	2006.02.17
 */
//============================================================================================
#include "common.h"
#include "fieldsys.h"
#include "worldmap.h"
#include "sp_attribute_def.h"

#include "system/arc_tool.h"

#define SP_MAP_SIZE			(15)

typedef struct SP_MATRIX_DATA_tag{
	u8 Matrix[SP_MAP_SIZE*SP_MAP_SIZE];
	u16 GroundAttr[GROUND_ATTR_SIZE];
}SP_MATRIX_DATA;

static void MakeSpMatrix(WORLD_MAP_PTR inWorld, SMD_PTR outUgMatrixData, const u8 inNum);
static const u8 AddSpArcList(const u16 inArcIndex, u16 *outList, u8 *ioListPos);

//--------------------------------------------------------------------------------------------
/**
 * ����A�g���r���[�g�Z�b�g�A�b�v
 *
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	inNum			�f�[�^��
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SPATTR_SetUpGroundAttr(FIELDSYS_WORK *fsys, const u8 inNum)
{
	int i;
	void *mem;	
	//�������A���P�[�V����
	if (fsys->SpMatData == NULL){
		fsys->SpMatData = sys_AllocMemory( HEAPID_WORLD, sizeof(SP_MATRIX_DATA) );
		//����}�g���N�X�쐬
		MakeSpMatrix(fsys->World, fsys->SpMatData, inNum);
		
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ����A�g���r���[�g���
 *
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SPATTR_FreeGroundAttr(FIELDSYS_WORK *fsys)
{
	if (fsys->SpMatData != NULL){
		sys_FreeMemoryEz(  fsys->SpMatData );
		fsys->SpMatData = NULL;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ����A�g���r���[�g�u���b�N���擾
 *
 * @param	inBlockindex	�u���b�N�C���f�b�N�X 
 * @param	inSpMatrixData	����}�g���N�X�f�[�^
 *
 * @return	block_attr	�u���b�N�A�g���r���[�g�擪�|�C���^
 */
//--------------------------------------------------------------------------------------------
u16 const * SPATTR_GetSpBlockAttribute(const u32 inBlockindex, SMD_CONST_PTR inSpMatrixData)
{
	u16 const *block_attr;
	u8 list_idx;
	list_idx = inSpMatrixData->Matrix[inBlockindex];
	block_attr = (u16 const *)&(inSpMatrixData->GroundAttr[BLOCK_ATTR_SIZE*list_idx]);
	return block_attr;
}

//--------------------------------------------------------------------------------------------
/**
 * ����}�g���N�X���쐬
 *
 * @param	inWorld			���[���h�|�C���^
 * @param	outSpMatrixData	����}�g���N�X�f�[�^
 * @param	inNum			�f�[�^��
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void MakeSpMatrix(WORLD_MAP_PTR inWorld, SMD_PTR outSpMatrixData, const u8 inNum)
{
	u8 list_pos;
	u16 arc_idx;
	u8 list_idx;
	u16 idx;
	int i,j;
	int h,w;
	u16 list[SP_ATTR_DATA_NUM_MAX];
	void *mem;
	ARCHANDLE *arc_handle;

	list_pos = 0;

	//���݃}�b�v�}�g���N�X���擾
	w = GetWorldMapMatrixW(inWorld);
	h = GetWorldMapMatrixH(inWorld);

	//�A�g���r���[�g�擾�p�Ƀ}�g���N�X���쐬
	for(j=0;j<h;j++){
		for(i=0;i<w;i++){
			idx = j*w+i;
			arc_idx = GetArcIndexFromBlockIndex(idx,inWorld);
#ifdef DEBUG_ONLY_FOR_saitou			
			OS_Printf("local_print %d:arc_idx:%d\n",idx,arc_idx);
#endif			
			//����}�g���b�N�X�̃A�[�J�C�u�C���f�b�N�X�����X�g�ɒǉ�
			list_idx = AddSpArcList(arc_idx, list, &list_pos);
			outSpMatrixData->Matrix[idx] = list_idx;
		}
	}
	//�A�g���r���[�g���܂Ƃ߂ă��[�h����
	//�A�[�J�C�u�n���h���̎擾
	arc_handle = ArchiveDataHandleOpen( ARC_FIELD_MAP_DATA, HEAPID_WORLD );

	for(i=0;i<inNum;i++){
		arc_idx = list[i];
		mem = &(outSpMatrixData->GroundAttr[BLOCK_ATTR_SIZE*i]);
		//�A�g���r���[�g�̓A�[�J�C�u�f�[�^�̐擪����Œ�o�C�g�T�C�Y�Ȃ̂ŁA�I�t�Z�b�g�A�T�C�Y�擾�͏Ȃ�
		ArchiveDataLoadOfsByHandle( arc_handle, arc_idx, 0x10, 0x800,  mem);
	}
	//�A�[�J�C�u�n���h���̉��
	ArchiveDataHandleClose( arc_handle );
}

//--------------------------------------------------------------------------------------------
/**
 * ���X�g�ɓo�^
 *
 * @param	inArcIndex	�A�[�J�C�u�C���f�b�N�X
 * @param	outList		���X�g
 * @param	ioListPos	���X�g�ʒu
 *
 * @return	u8			�o�^���Ă���i�����j���X�g�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
static const u8 AddSpArcList(const u16 inArcIndex, u16 *outList, u8 *ioListPos)
{
	u8 i;
	//�w�肵���A�[�J�C�u�C���f�b�N�X�����X�g�ɓo�^����Ă��Ȃ���Βǉ�
	for(i=0;i<(*ioListPos);i++){
		if (outList[i] == inArcIndex){
			return i;	//���łɓo�^�ς�
		}
	}
	//�V�K�o�^
	GF_ASSERT( i<SP_ATTR_DATA_NUM_MAX && "�f�[�^�����I�[�o�[���Ă܂�" );
	outList[i] = inArcIndex;
	(*ioListPos)++;
	return i;
	
}
