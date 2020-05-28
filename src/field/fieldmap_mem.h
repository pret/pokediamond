#ifndef _FIELDMAP_MEM_H_
#define _FIELDMAP_MEM_H_

#include "fieldmap_mem_def.h"


#define	FIELD_GROUND_DATA_SIZE (0xf000)		///<地形データ1ブロックあたりのメモリサイズ
#define	FIELD_HEIGHT_DATA_SIZE (0x9000)		///<高さデータ1ブロックあたりのメモリサイズ


extern FMM_PTR AllocFldMapMem(const BOOL inHeightDataValid);
extern void FreeFldMapMem(FMM_PTR mem);
extern void BindGroundMem(const u8 inIdx, FMM_CONST_PTR mem, void **outPtr);
extern void BindHeightMem(const u8 inIdx, FMM_CONST_PTR mem, void **outPtr);


#endif	//_FIELDMAP_MEM_H_
