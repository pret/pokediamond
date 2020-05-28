//=============================================================================
/**
 * @file	paso_anm.c
 * @bfief	パソコンアニメ
 * @author	Nozomu Saito
 *
 */
//=============================================================================
#include "common.h"
#include "fieldsys.h"
#include "field_3d_anime.h"

#include "fielddata/build_model/build_model_id.h"

#include "paso_anm_def.h"

#include "paso_anm.h"

//==============================================================================
/**
 * パソコンアニメーションのセットアップ
 * 
 * @param	fsys		フィールドシステムポインタ
 * @param	inEntryID	登録ＩＤ
 *
 * @retval  none
 */
//=============================================================================
void FLD_SCR_ANM_PASO_Setup( FIELDSYS_WORK * fsys, const u8 inEntryID )
{
	BOOL rc;
	M3DO_PTR obj_ptr;
	TARGET_RECT rect;
	int obj_id;
	int list[] = {	BMID_PC01,BMID_TABLE_L01,BMID_TABLE_L02,BMID_TABLE_L03};

	rc = MPTL_CheckPluralMap3DObj(	fsys,
									list,
									4,//<<未定義命令でとまるので直値を入れておく
									&obj_ptr,
									&obj_id);
	if (rc){
		NNSG3dResTex *tex;
		tex = GetMapResourceBmTexturePTR(fsys->MapResource);
		F3DASub_SetUpAnimation(	fsys->field_3d_anime,
								fsys->AnimeContMng,
								inEntryID,
								obj_id,
								M3DO_GetRenderObj(obj_ptr),
								M3DO_GetObjModel(obj_ptr),
								tex,2,
								1,		//ループ1回
								FALSE);
	}else{
		GF_ASSERT_MSG(0,"パソコンありません");
	}
}

//==============================================================================
/**
 * パソコンアニメーション（パソコン起動）
 * 
 * @param	fsys		フィールドシステムポインタ
 * @param	inEntryID	登録ＩＤ
 *
 * @retval  none
 */
//==============================================================================
void FLD_SCR_ANM_PASO_PasoOnAnm( FIELDSYS_WORK * fsys, const u8 inEntryID )
{
	F3DASub_StartAnimation(fsys->AnimeContMng, inEntryID, PASO_ON);	//パソコン起動アニメ
}

//==============================================================================
/**
 * パソコンアニメーション（パソコン終了）
 * 
 * @param	fsys		フィールドシステムポインタ
 * @param	inEntryID	登録ＩＤ
 *
 * @retval  none
 */
//==============================================================================
void FLD_SCR_ANM_PASO_PasoOffAnm( FIELDSYS_WORK * fsys, const u8 inEntryID )
{
	F3DASub_StartAnimation(fsys->AnimeContMng, inEntryID, PASO_OFF);	//パソコン終了アニメ
}
