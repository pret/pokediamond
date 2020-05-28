//============================================================================================
/**
 * @file	ug_base_layout.c
 * @brief	秘密基地に入った際のレイアウト処理
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
 *	地下秘密基地グッズセットアップ
 *	@param	fsysl	フィールドシステムポインタ
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
		return;	//地上とみなし、リターン
	}
	
	//オフセット取得
	block_x = UgManUgSetupSecretBaseBlockX();
	block_z = UgManUgSetupSecretBaseBlockZ();
	
	for(i=0;i<32;i++){
		goods_no = SecretBaseData_GetGoodsType(base_data, i);
		//グッズナンバーから縦横サイズを取得
		w = GOODS_GetGoodsSizeX(goods_no);
		d = GOODS_GetGoodsSizeZ(goods_no);
		if (goods_no != GOODS_INVALID){
			x = SecretBaseData_GetGoodsXPos(base_data, i);
			z = SecretBaseData_GetGoodsZPos(base_data, i);
			//Fx32型に変換
			trans.x = x*(FX32_ONE*16);
			trans.z = z*(FX32_ONE*16);
			trans.y = FX32_ONE;	//ちょっとあげとく
			//オフセット付加
			trans.x += (block_x*FX32_ONE*16*32);
			trans.z += (block_z*FX32_ONE*16*32);
			//サイズによるオフセット付加
			trans.x += (w*FX32_ONE*8);
			trans.z += (d*FX32_ONE*8);
			obj_id = MAPRES_GetObjIDFromModelFile(fsys->MapResource, goods_no);
			//OBJ登録
			M3DO_SetMap3DObjExp(fsys->Map3DObjExp,
								fsys->MapResource,
								obj_id,
								&trans,	NULL,		//
								fsys->field_3d_anime);
		}
	}
}
