//============================================================================================
/**
 * @file	ug_base_layout.c
 * @brief	�閧��n�ɓ������ۂ̃��C�A�E�g����
 * @author	saito
 * @date	2006.03.03
 *
 */
//============================================================================================
#include "common.h"
#include "fieldsys.h"
#include "savedata/undergrounddata.h"
#include "comm_field_state.h"
#include "underground/ug_manager.h"
#include "underground/ug_secretbase.h"
#include "goods_data.h"

#include "ug_base_layout.h"

//---------------------------------------------------------------------------------------------------------
/**
 *	�n���閧��n�O�b�Y�Z�b�g�A�b�v
 *	@param	fsysl	�t�B�[���h�V�X�e���|�C���^
 *
 *	@retval	none
*/
//---------------------------------------------------------------------------------------------------------
void BaseLayout_SetupUGBaseGoodsObj(FIELDSYS_WORK * fsys)
{
	int i;
	int goods_no;
	SECRETBASEDATA *base_data;
	int block_x,block_z;
	int x,z;
	int w,d;
	VecFx32	trans;
	int obj_id;
	
	base_data = CommUgSetupSecretBaseData(fsys->savedata);
	if (base_data==NULL){
		return;	//�n��Ƃ݂Ȃ��A���^�[��
	}
	
	//�I�t�Z�b�g�擾
	block_x = UgManUgSetupSecretBaseBlockX();
	block_z = UgManUgSetupSecretBaseBlockZ();
	
	for(i=0;i<32;i++){
		goods_no = SecretBaseData_GetGoodsType(base_data, i);
		//�O�b�Y�i���o�[����c���T�C�Y���擾
		w = GOODS_GetGoodsSizeX(goods_no);
		d = GOODS_GetGoodsSizeZ(goods_no);
		if (goods_no != GOODS_INVALID){
			x = SecretBaseData_GetGoodsXPos(base_data, i);
			z = SecretBaseData_GetGoodsZPos(base_data, i);
			//Fx32�^�ɕϊ�
			trans.x = x*(FX32_ONE*16);
			trans.z = z*(FX32_ONE*16);
			trans.y = FX32_ONE;	//������Ƃ����Ƃ�
			//�I�t�Z�b�g�t��
			trans.x += (block_x*FX32_ONE*16*32);
			trans.z += (block_z*FX32_ONE*16*32);
			//�T�C�Y�ɂ��I�t�Z�b�g�t��
			trans.x += (w*FX32_ONE*8);
			trans.z += (d*FX32_ONE*8);
			obj_id = MAPRES_GetObjIDFromModelFile(fsys->MapResource, goods_no);
			//OBJ�o�^
			M3DO_SetMap3DObjExp(fsys->Map3DObjExp,
								fsys->MapResource,
								obj_id,
								&trans,	NULL,		//
								fsys->field_3d_anime);
		}
	}
}
