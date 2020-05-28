//============================================================================================
/**
 * @file	sp_attribute_def.h
 * @brief	特殊アトリビュート関連
 * @author	Nozomu Saito
 * @date	06.04.22
 */
//============================================================================================
#ifndef _SP_ATTRIBUTE_DEF_H_
#define _SP_ATTRIBUTE_DEF_H_

typedef struct SP_MATRIX_DATA_tag * SMD_PTR;
typedef struct SP_MATRIX_DATA_tag  const * SMD_CONST_PTR;

#define BLOCK_ATTR_SIZE			(32*32)
#define SP_ATTR_DATA_NUM_MAX	(16)
#define GROUND_ATTR_SIZE		(BLOCK_ATTR_SIZE*SP_ATTR_DATA_NUM_MAX)

extern void SPATTR_SetUpGroundAttr(FIELDSYS_WORK *fsys,const u8 inNum);
extern void SPATTR_FreeGroundAttr(FIELDSYS_WORK *fsys);
extern u16 const * SPATTR_GetSpBlockAttribute(	const u32 inBlockindex,
										SMD_CONST_PTR inUgMatrixData);

#endif	//_SP_ATTRIBUTE_DEF_H_
