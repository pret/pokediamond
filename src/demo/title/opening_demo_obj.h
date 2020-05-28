//=============================================================================
/**
 * @file	opening_demo_obj.h
 * @brief	オープニングデモＯＢＪ
 * @author	Nozomu Saito
 * @date    2006.06.03
 */
//=============================================================================
#ifndef __OPENING_DEMO_OBJ_H__
#define __OPENING_DEMO_OBJ_H__

#include "system/clact_tool.h"

typedef enum {
	ACT_WORK_HERO,
	ACT_WORK_HEROINE,
	ACT_WORK_RIVAL,
	ACT_WORK_BIRD_1,
	ACT_WORK_BIRD_2,
	ACT_WORK_BIRD_3,
	ACT_WORK_BIRD_4,
	ACT_WORK_BIRD_5,
	ACT_WORK_BIRD_6,
}ACT_WORK_NO;

typedef enum{
	CHG_MODE_BLACK,
	CHG_MODE_NORMAL,
}COL_CHG_MODE;

typedef struct OP_DEMO_OBJ_WORK_tag * OPD_OBJ_PTR;

extern const int OPD_Obj_GetWorkSize( void );
extern void OPD_Obj_InitCellActor( OPD_OBJ_PTR wk );
extern void OPD_Obj_EndCellActor( OPD_OBJ_PTR wk );
extern void OPD_Obj_SetActor( OPD_OBJ_PTR wk );
extern void OPD_Obj_SetKiraActor( OPD_OBJ_PTR wk,
								  OPD_KIRA_DATLST_PTR pKiraDataListPtr );
extern void OPD_Obj_DrawActor( OPD_OBJ_PTR wk );
extern void OPD_Obj_DispOnOff( OPD_OBJ_PTR wk, const u8 inActWorkNo, const u8 inFlg );
extern void OPD_Obj_ChangePos( OPD_OBJ_PTR wk, const u8 inActWorkNo, const int inX, const int inY );
extern void OPD_Obj_ChangeHeroinePos( OPD_OBJ_PTR wk );
extern void OPD_Obj_ChangeHeroHeroineAnime( OPD_OBJ_PTR wk, const u8 inNo );
extern void OPD_Obj_OnOffHeroHeroineAnime( OPD_OBJ_PTR wk, const u8 inAnime );
extern BOOL OPD_Obj_SlideInRival(OPD_OBJ_PTR wk);
extern void OPD_Obj_ChangeCollor(OPD_OBJ_PTR wk, const int inActWorkNo, const u8 inColChgMode);
extern void  OPD_Obj_SlideInBird(OPD_OBJ_PTR wk, const int inCounter);
#endif	//__OPENING_DEMO_OBJ_H__
