//============================================================================================
/**
 * @file	field_matrix.h
 * @brief	�}�g���N�X�擾
 * @author	Saito
 * @date	05.12.01
 */
//============================================================================================
#ifndef	__FIELD_MATRIX_H__
#define	__FIELD_MATRIX_H__

typedef struct FIELD_MAT_ZONE_ID_tag * FMZ_PTR;
typedef struct FIELD_MAT_ZONE_ID_tag  const * FMZ_CONST_PTR;

//���̂́Aworldmap.c
extern FMZ_PTR InitFMZ(const u32 inHeapID);
extern void FreeFMZ(FMZ_PTR fmzp);
extern int GetFieldMatrixZoneID(FMZ_CONST_PTR fmdp,
								const u32 inBlockX,
								const u32 inBlockZ);
#ifdef PM_DEBUG 
//==============================================================================
/**
 * @brief	�w�肵���]�[���̍���u���b�N���W���擾����
 *
 * @param	zoneID		�]�[��ID
 * @param   px			�擾�����u���b�NX���W���i�[����|�C���^
 * @param   pz			�擾�����u���b�NZ���W���i�[����|�C���^
 *
 * @retval  none		
 */
//==============================================================================
extern int GetBlockPosFromZoneID(int zoneID,u16* px,u16* pz);
#endif

#endif //__FIELD_MATRIX_H__

