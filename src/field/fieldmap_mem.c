#include "common.h"
#include "fieldmap_mem.h"

typedef struct FLD_MAP_MEM_tag
{
	void *GroundData[4];
	void *HeightData[4];
/**
	void *SeaAnm;
	void *Tex;
*/
}FLD_MAP_MEM;

static u8 FieldGroundData[4][FIELD_GROUND_DATA_SIZE];
//static u8 FieldHeightData[4][FIELD_HEIGHT_DATA_SIZE];

static void ClearFldMapMem( const u8 inIdx,
							const int inGroundMemSize,
							const int inHeightMemSize,
							FMM_PTR mem);


//�������m��
FMM_PTR AllocFldMapMem(const BOOL inHeightDataValid)
{
	u8 i;
	int height_mem_size;
	FMM_PTR mem;
	
	mem = sys_AllocMemory( HEAPID_FIELD, sizeof(FLD_MAP_MEM) );//�ǂݍ��݃G���A�m��

	//�������m��
	for(i=0;i<4;i++){
		//�n�`�f�[�^�������m��
		mem->GroundData[i] = (void*)&FieldGroundData[i][0];
		if (mem->GroundData[i] == NULL){
			OS_Printf("%d,�n�`�f�[�^�������m�ێ��s\n",i);
			return NULL;
		}
		if (inHeightDataValid){
			//�����f�[�^�������m��
			mem->HeightData[i] = sys_AllocMemory( HEAPID_FIELD, FIELD_HEIGHT_DATA_SIZE );
//			mem->HeightData[i] = (void*)&FieldHeightData[i][0];
			if (mem->HeightData[i] == NULL){
				OS_Printf("%d,�����f�[�^�������m�ێ��s\n",i);
				return NULL;
			}
			height_mem_size = FIELD_HEIGHT_DATA_SIZE;
		}else{
			mem->HeightData[i] = NULL;
			height_mem_size = 0;
		}
		ClearFldMapMem(i,FIELD_GROUND_DATA_SIZE,height_mem_size,mem);
	}
	
	//�C�A�j���f�[�^�������m��
	//�n�`�e�N�X�`���������m��
	
	return mem;
}

//���������
void FreeFldMapMem(FMM_PTR mem)
{
	u8 i;
	//���������
	for(i=0;i<4;i++){
		//�n�`�f�[�^���������
		//sys_FreeMemoryEz( (void *)mem->GroundData[i] );
		mem->GroundData[i] = NULL;
		//�����f�[�^�͂Ȃ��Ƃ��i�n���Ƃ��j������̂łm�t�k�k�`�F�b�N����
		if (mem->HeightData[i] != NULL){
			//�����f�[�^���������
			sys_FreeMemoryEz( (void *)mem->HeightData[i] );
			mem->HeightData[i] = NULL;
		}
	}
	sys_FreeMemoryEz((void *)mem);
	mem = NULL;
}

//�n�`�f�[�^�������ƃ|�C���^���o�C���h
void BindGroundMem(const u8 inIdx, FMM_CONST_PTR mem, void **outPtr)
{
	*outPtr = mem->GroundData[inIdx];
}

//�����f�[�^�������ƃ|�C���^���o�C���h
void BindHeightMem(const u8 inIdx, FMM_CONST_PTR mem, void **outPtr)
{
	*outPtr = mem->HeightData[inIdx];
}

static void ClearFldMapMem(	const u8 inIdx,
							const int inGroundMemSize,
							const int inHeightMemSize,
							FMM_PTR mem)
{
	MI_CpuClear8(mem->GroundData[inIdx],inGroundMemSize);
	MI_CpuClear8(mem->HeightData[inIdx],inHeightMemSize);
}

	
