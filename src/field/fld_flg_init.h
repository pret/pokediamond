//============================================================================================
/**
 * @file	fld_flg_init.h
 * @brief	フィールド移動でのフラグオフ・値クリアとか（気付いたやつだけ入れときます）
 * @date	2006.05.23
 * @author	Nozomu Saito
 *
 */
//============================================================================================

#ifndef __FLD_FLG_INIT_H__
#define __FLD_FLG_INIT_H__

#include "field_common.h"

extern void FldFlgInit_Walk(FIELDSYS_WORK * fsys);
extern void FldFlgInit_MapJump(FIELDSYS_WORK * fsys);
extern void FldFlgInit_FlySky(FIELDSYS_WORK * fsys);
extern void FldFlgInit_Teleport(FIELDSYS_WORK * fsys);
extern void FldFlgInit_Escape(FIELDSYS_WORK * fsys);
extern void FldFlgInit_GameOver(FIELDSYS_WORK * fsys);
extern void FldFlgInit_Continue(FIELDSYS_WORK * fsys);
extern void FldFlgInit_UnderGround(FIELDSYS_WORK * fsys);

extern void FldFlg_SetScopeMode(FIELDSYS_WORK * fsys, BOOL flag);

#endif //__FLD_FLG_INIT_H__
