//===========================================================================
/**
 * @file	field_poketch.h
 * @brief	フィールド・ポケッチ間 連絡関数群
 * @author	taya	GAME FREAK Inc.
 *
 */
//===========================================================================
#ifndef __FIELD_POKETCH_H__
#define __FIELD_POKETCH_H__

#include "field_common.h"
#include "field\poketch.h"


extern void Field_SendPoketchInfo( FIELDSYS_WORK* fsys, FIELD_POKETCH_SEND_ID id, u32 value );

extern  void FieldPoketch_Init( FIELDSYS_WORK * fsys );
extern  void FieldPoketch_QuitReq( FIELDSYS_WORK * fsys );
extern  u8 FieldPoketch_QuitWait( FIELDSYS_WORK * fsys );

extern void FieldBeforePoketch_Init( FIELDSYS_WORK * fsys );
extern void FieldBeforePoketch_QuitReq( FIELDSYS_WORK * fsys );
extern BOOL FieldBeforePoketch_QuitWait( FIELDSYS_WORK * fsys );

#endif
