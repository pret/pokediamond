//============================================================================================
/**
 * @file	quick_sand.c
 * @brief	�����Ď��A�A�j���Ăяo���֘A�t�@�C��
 * @author	Nozomu Saito
 * @date	2006.03.16
 */
//============================================================================================
#include "quick_sand.h"
#include "fieldsys.h"
#include "fieldmap_work.h"
#include "fieldmap_func.h"
#include "field_3d_anime_ev.h"

typedef struct QUICK_SAND_POS_INFO_tag
{
	int GridX;
	int GridZ;
}QUICK_SAND_POS_INFO;

//==============================================================================
/**
 * �����^�X�N�N���G�C�g�֐��@���[�N������
 * 
 * @param	*fwk		�t�B�[���h�}�b�v�t�@���N�V�����|�C���^
 * @param	*fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	*work		���[�N
 *
 * @retval  none
 */
//==============================================================================
static void QuickSand_Create(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work)
{
	//���@���W�Ď��p���[�N��������
	QUICK_SAND_POS_INFO *info = (QUICK_SAND_POS_INFO*)work;
	info->GridX = 0;
	info->GridZ = 0;
}

//==============================================================================
/**
 * �����^�X�N�f���[�g�֐��@�������܂���
 * 
 * @param	*fwk		�t�B�[���h�}�b�v�t�@���N�V�����|�C���^
 * @param	*fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	*work		���[�N
 *
 * @retval  none
 */
//==============================================================================
static void QuickSand_Delete(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work)
{
	;
}

//==============================================================================
/**
 * �����^�X�N�A�b�v�f�[�g�֐��@�����`�F�b�N���s���܂�
 * 
 * @param	*fwk		�t�B�[���h�}�b�v�t�@���N�V�����|�C���^
 * @param	*fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	*work		���[�N
 *
 * @retval  none
 */
//==============================================================================
static void QuickSand_Update(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work)
{
	u8 attr;
	int x,z;
	u8 anime_no;
	QUICK_SAND_POS_INFO *info = (QUICK_SAND_POS_INFO*)work;
	
	//���@�̈ʒu�擾
	x = Player_NowGPosXGet(fsys->player);
	z = Player_NowGPosZGet(fsys->player);

	//���W��r
	if ((info->GridX == x)&&(info->GridZ == z)){
		return;
	}

	info->GridX = x;
	info->GridZ = z;
	
	//�A�g���r���[�g�擾
	attr = GetAttributeLSB(fsys, x, z);
	
	if (MATR_IsShiftingSandLower(attr)){
		anime_no = 0;	//������
	}else if (MATR_IsShiftingSandUpper(attr)){
		anime_no = 1;	//������
	}else{
		return;
	}
	Fld3DAnm_StartQuickSandAnime(x, z, anime_no, fsys);
}

static const FLDMAPFUNC_DATA QuickSandData = {
	FLDMAP_PRI_QUICK_SAND,
	sizeof(QUICK_SAND_POS_INFO),
	QuickSand_Create,
	QuickSand_Delete,
	QuickSand_Update,
	NULL
};

//==============================================================================
/**
 * �����^�X�N�쐬�֐�
 * 
 * @param	*fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @retval  none
 */
//==============================================================================
void QuickSand_CheckTask(FIELDSYS_WORK * fsys)
{
	FLDMAPFUNC_Create(fsys->fldmap->fmapfunc_sys, &QuickSandData);
}
