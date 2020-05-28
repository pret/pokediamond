//=============================================================================
/**
 * @file	paso_anm.h
 * @bfief	パソコンアニメ
 * @author	Nozomu Saito
 *
 */
//=============================================================================

#ifndef	__PASO_ANM_H__
#define	__PASO_ANM_H__

#include "field_common.h"

extern void FLD_SCR_ANM_PASO_Setup(FIELDSYS_WORK * fsys, const u8 inEntryID );
extern void FLD_SCR_ANM_PASO_PasoOnAnm(	FIELDSYS_WORK * fsys, const u8 inEntryID );
extern void FLD_SCR_ANM_PASO_PasoOffAnm( FIELDSYS_WORK * fsys, const u8 inEntryID );

#endif	//__PASO_ANM_H__
