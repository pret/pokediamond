#ifndef _MAT_SHP_H_
#define _MAT_SHP_H_

#include "common.h"

typedef struct MAT_SHP_tag
{
	u16 matID;
	u16 shpID;
}MAT_SHP;
/**
typedef struct MAT_SHP_LIST_tag
{
	u8 num;
	const MAT_SHP	*mat_shp;
	
}MAT_SHP_LIST;
*/

typedef struct MAT_SHP_DATA_tag *MSD_PTR;
typedef struct MAT_SHP_DATA_tag const *MSD_CONST_PTR;

//extern const MAT_SHP_LIST MatShpList[];

extern MSD_PTR AllocMatShpData(void);
extern void LoadMatShape(const char * inName, MSD_PTR outData);
extern void FreeMatShpData(MSD_PTR outData);
extern void GetMatShpNum(	const int inObjIdx,
							MSD_CONST_PTR inData,
							u16 *outNum);
extern void GetMatShpNumAndIdx(	const int inObjIdx,
								MSD_CONST_PTR inData,
								u16 *outNum,
								u16 *outIdx);
extern MAT_SHP const *GetMatShp(const u16 inIdx, MSD_CONST_PTR inData);

#endif //_MAT_SHP_H_
