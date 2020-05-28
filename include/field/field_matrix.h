//============================================================================================
/**
 * @file	field_matrix.h
 * @brief	マトリクス取得
 * @author	Saito
 * @date	05.12.01
 */
//============================================================================================
#ifndef	__FIELD_MATRIX_H__
#define	__FIELD_MATRIX_H__

typedef struct FIELD_MAT_ZONE_ID_tag * FMZ_PTR;
typedef struct FIELD_MAT_ZONE_ID_tag  const * FMZ_CONST_PTR;

//実体は、worldmap.c
extern FMZ_PTR InitFMZ(const u32 inHeapID);
extern void FreeFMZ(FMZ_PTR fmzp);
extern int GetFieldMatrixZoneID(FMZ_CONST_PTR fmdp,
								const u32 inBlockX,
								const u32 inBlockZ);
#ifdef PM_DEBUG 
//==============================================================================
/**
 * @brief	指定したゾーンの左上ブロック座標を取得する
 *
 * @param	zoneID		ゾーンID
 * @param   px			取得したブロックX座標を格納するポインタ
 * @param   pz			取得したブロックZ座標を格納するポインタ
 *
 * @retval  none		
 */
//==============================================================================
extern int GetBlockPosFromZoneID(int zoneID,u16* px,u16* pz);
#endif

#endif //__FIELD_MATRIX_H__

