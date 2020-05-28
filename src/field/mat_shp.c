#include "mat_shp.h"

#if 0
//tree01
const MAT_SHP tree01_ms[] = {
	{0,0}
};

//fence01
const MAT_SHP fence01_ms[] = {
	{0,0}
};

//kanban01
const MAT_SHP kanban01_ms[] = {
	{0,0}
};

//house01
const MAT_SHP house01_ms[] = {
	{0,0},
	///{0,1}
};

//house02
const MAT_SHP house02_ms[] = {
	{0,0},
	///{0,1}
};

//house03
const MAT_SHP house03_ms[] = {
	{0,0},
};

//house04
const MAT_SHP house04_ms[] = {
	{0,0},
	{1,1}
};

//build01
const MAT_SHP build01_ms[] = {
	{0,0},
	{1,1},
	{2,2}
};

//bush01
const MAT_SHP bush01_ms[] = {
	{0,0},
};

//bush02
const MAT_SHP bush02_ms[] = {
	{0,0},
};

//pc
const MAT_SHP pc_ms[] = {
	{1,0},
	{2,1},
	{0,2},
	{0,3},
};
//fs
const MAT_SHP fs_ms[] = {
	{1,1},
	{2,0},
	{0,2},
};
//ectgr01～03
const MAT_SHP ectgr[] = {
	{0,0},
	{1,1},
};
//build02
const MAT_SHP build02_ms[] = {
	{0,0},
	{1,1},
	{2,2},
	{3,3},
	{4,4},
	{5,5}
};
//f_iwa_00
const MAT_SHP f_iwa_00_ms[] = {
	{0,0},
};
//gym_00
const MAT_SHP gym00_ms[] = {
	{0,1},
	{1,0},
};
//c1_b01a
const MAT_SHP c1_b01a_ms[] = {
	{0,0},
	{1,1},
	{2,2},
};
//c1_b01b
const MAT_SHP c1_b01b_ms[] = {
	{0,0},
	{1,1},
	{2,2},
};
//c1_b01c
const MAT_SHP c1_b01c_ms[] = {
	{0,0},
	{1,1},
	{2,2},
};
//c1_s01
const MAT_SHP c1_s01_ms[] = {
	{0,0},
	{1,1},
	{2,2},
	{3,3},
};
//c1_s02
const MAT_SHP c1_s02_ms[] = {
	{0,0},
	{1,1},
	{2,2},
};
//c1_s03
const MAT_SHP c1_s03_ms[] = {
	{0,0},
	{1,1},
};
//c1_o01
const MAT_SHP c1_o01_ms[] = {
	{0,0},
};
//c1_o02
const MAT_SHP c1_o02_ms[] = {
	{0,0},
	{1,1},
};
//c1_school
const MAT_SHP c1_school_ms[] = {
	{0,0},
	{1,1},
};
//c1_h01a
const MAT_SHP c1_h01a_ms[] = {
	{0,1},
	{1,0},
};
//c1_h02a
const MAT_SHP c1_h01b_ms[] = {
	{0,1},
	{1,0},
};
//c1_b02a
const MAT_SHP c1_b02a_ms[] = {
	{0,1},
	{1,0},
};
//c1_b02b
const MAT_SHP c1_b02b_ms[] = {
	{0,1},
	{1,0},
};
//door01
const MAT_SHP door01_ms[] = {
	{0,0},
};

const MAT_SHP_LIST MatShpList[] = {
	{0,NULL},	//NO DATA
	{1,tree01_ms},	//tree01
	{1,fence01_ms},	//fence01
	{1,kanban01_ms},	//kanban01
	{1,house01_ms},	//house01
	{1,house02_ms},	//house02
	{1,house03_ms},	//house03
	{2,house04_ms},	//house04
	{3,build01_ms},	//build01
	{1,bush01_ms},	//bush01
	{1,bush02_ms},	//bush02
	{0,NULL},	//funnsui
	{4,pc_ms},
	{3,fs_ms},
	{0,NULL},	//fs_kanban
	{2,ectgr},
	{2,ectgr},
	{2,ectgr},
	{6,build02_ms},	//build01
	{1,f_iwa_00_ms},//f_iwa_00
	{2,gym00_ms},//gym00
	{3,c1_b01a_ms},//c1_b01a
	{3,c1_b01b_ms},//c1_b01b
	{3,c1_b01c_ms},//c1_b01c
	{4,c1_s01_ms},//c1_s01
	{3,c1_s02_ms},//c1_s02
	{2,c1_s03_ms},//c1_s03
	{1,c1_o01_ms},//c1_o01
	{2,c1_o02_ms},//c1_o02
	{2,c1_school_ms},//c1_school
	{2,c1_h01a_ms},//c1_h01a
	{2,c1_h01b_ms},//c1_h01b
	{2,c1_b02a_ms},//c1_b02a
	{2,c1_b02b_ms},//c1_b02b
	{0,NULL},//door01
};
#endif

//1mat1shape対応データ　バイナリフォーマット



typedef struct MAT_SHP_HEADER_tag
{
	u16 Num;	//オブジェクトがもつMAT_SHPの要素数
	u16	Idx;	//MAT_SHP配列の参照IndexNo
}MAT_SHP_HEADER;

typedef struct MAT_SHP_DATA_tag
{
	MAT_SHP_HEADER	*Header;
	MAT_SHP			*MatShp;
}MAT_SHP_DATA;
/*
struct _MAT_SHP_LIST_tag

{

	u16	objNum;	//オブジェクトモデルの数

	u16	matshpNum;	//1ファイルに含まれるMAT_SHP配列の全要素数



	MAT_SHP_HEADER header[objNum];	//ヘッダ配列



	MAT_SHP	data[matshpNum];		//MAT_SHPデータ配列

}MAT_SHP_LIST;
*/

MSD_PTR AllocMatShpData(void)
{
	MSD_PTR data;
	data = sys_AllocMemory( HEAPID_FIELD, sizeof(MAT_SHP_DATA) );
	GF_ASSERT( data != NULL && "ERROR:mat_shp no enough memory" );
	return data;
}

void LoadMatShape(const char * inName, MSD_PTR outData)
{
	FSFile file;
	u16 obj_num;
	u16 mat_shp_num;
	int header_size;
	int mat_shp_size;

	FS_InitFile(&file);
	if (FS_OpenFile(&file, inName)){
		int ret;
		ret = FS_ReadFile(&file, &obj_num, 2);
		GF_ASSERT( ret >= 0 && "ERROR:mat_shp can not read" );
		
		ret = FS_ReadFile(&file, &mat_shp_num, 2);
		GF_ASSERT( ret >= 0 && "ERROR:mat_shp can not read" );
		
		//メモリ確保
		header_size = sizeof(MAT_SHP_HEADER)*obj_num;
		mat_shp_size = sizeof(MAT_SHP)*mat_shp_num;

		outData->Header = sys_AllocMemory( HEAPID_FIELD, header_size );
		GF_ASSERT( outData->Header != NULL&& "ERROR:mat_shp no enough memory" );
		outData->MatShp = sys_AllocMemory( HEAPID_FIELD, mat_shp_size );
		GF_ASSERT( outData->MatShp != NULL&& "ERROR:mat_shp no enough memory" );

		ret = FS_ReadFile(&file, outData->Header, header_size);
		GF_ASSERT( ret >= 0 && "ERROR:mat_shp can not read" );
		ret = FS_ReadFile(&file, outData->MatShp, mat_shp_size);
		GF_ASSERT( ret >= 0 && "ERROR:mat_shp can not read" );

		(void)FS_CloseFile(&file);
	}else{
		OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n",inName);
		GF_ASSERT(0);
	}
}

void FreeMatShpData(MSD_PTR outData)
{
	sys_FreeMemoryEz(outData->MatShp);
	sys_FreeMemoryEz(outData->Header);
	sys_FreeMemoryEz(outData);
}

void GetMatShpNum(const int inObjIdx,
						MSD_CONST_PTR inData,
						u16 *outNum)
{
	*outNum = inData->Header[inObjIdx].Num;
}

void GetMatShpNumAndIdx(const int inObjIdx,
						MSD_CONST_PTR inData,
						u16 *outNum,
						u16 *outIdx)
{
	*outNum = inData->Header[inObjIdx].Num;
	*outIdx = inData->Header[inObjIdx].Idx;
}

MAT_SHP const *GetMatShp(const u16 inIdx, MSD_CONST_PTR inData)
{
	return &inData->MatShp[inIdx];
}

