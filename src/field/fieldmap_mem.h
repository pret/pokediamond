#ifndef _FIELDMAP_MEM_H_
#define _FIELDMAP_MEM_H_

#include "fieldmap_mem_def.h"


#define	FIELD_GROUND_DATA_SIZE (0xf000)		///<�n�`�f�[�^1�u���b�N������̃������T�C�Y
#define	FIELD_HEIGHT_DATA_SIZE (0x9000)		///<�����f�[�^1�u���b�N������̃������T�C�Y


extern FMM_PTR AllocFldMapMem(const BOOL inHeightDataValid);
extern void FreeFldMapMem(FMM_PTR mem);
extern void BindGroundMem(const u8 inIdx, FMM_CONST_PTR mem, void **outPtr);
extern void BindHeightMem(const u8 inIdx, FMM_CONST_PTR mem, void **outPtr);


#endif	//_FIELDMAP_MEM_H_
