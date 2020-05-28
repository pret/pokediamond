//=============================================================================
/**
 * @file	fld_lift.h
 * @bfief	ÉäÉtÉgëÄçÏ(ÉWÉÄèúÇ≠)
 * @author	Nozomu Saito
 *
 */
//=============================================================================
#ifndef __FLD_LIFT_H__
#define __FLD_LIFT_H__

#include "field_common.h"

extern void FLIFT_Setup(FIELDSYS_WORK *fsys);
extern void FLIFT_Init(FIELDSYS_WORK *fsys);
extern void FLIFT_MoveLift(FIELDSYS_WORK *fsys);
extern u8 FLIFT_CheckValid(FIELDSYS_WORK *fsys);

#endif //__FLD_LIFT_H__
