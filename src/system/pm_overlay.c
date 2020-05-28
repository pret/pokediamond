//==============================================================================
/**
 * @file	pm_overlay.c
 * @brief	�I�[�o�[���C����
 * @author	matsuda
 * @date	2005.06.16(��)
 */
//==============================================================================
#include <nitro.h>
#include <nitro/fs.h>
#include "common.h"
#include "pm_overlay.h"


#if 0
NitroStaticInit���g�p����ɂ�
/*
 * NitroStaticInit() �� static initializer �Ɏw�肷��ɂ�
 * ���̃w�b�_���C���N���[�h���܂�.
 */
#include <nitro/sinit.h>

#endif


//==============================================================================
//	�萔��`
//==============================================================================
///�e�������G���A�ŁA��x�ɃI�[�o�[���C�o���鐔
#define AREA_WORK_MAX		(8)

//--------------------------------------------------------------
//	�f�o�b�O�p��`
//--------------------------------------------------------------
#ifdef PM_DEBUG
///��`���L���̏ꍇ�̓I�[�o�[���C�̃A�����[�h���s���ɃA�����[�h�����̈���N���A����
#define DEBUG_OVELAY_UNLOAD_CLEAR
#endif


//==============================================================================
//	�\���̒�`
//==============================================================================
typedef struct{
	FSOverlayID loaded_id;
	BOOL loaded;
}OVERLAY_WORK;

typedef struct{
	OVERLAY_WORK main[AREA_WORK_MAX];
	OVERLAY_WORK itcm[AREA_WORK_MAX];
	OVERLAY_WORK dtcm[AREA_WORK_MAX];
}OVERLAY_SYSTEM;

//==============================================================================
//	�O���[�o���ϐ��錾
//==============================================================================
static OVERLAY_SYSTEM OverlaySys;


//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static void Overlay_Unload(OVERLAY_WORK *ovwork);
static BOOL Overlay_CrossAreaCheck(const FSOverlayID id);
static OVERLAY_WORK * Overlay_AreaOverlayWorkPtrGet(int memory_area);
static BOOL Overlay_RamStartEndAdressGet(const FSOverlayID id, u32 *start, u32 *end);
static BOOL load_overlay_high(MIProcessor target, FSOverlayID id);
static BOOL load_overlay_middle(MIProcessor target, FSOverlayID id);
static BOOL load_overlay_low(MIProcessor target, FSOverlayID id);
void Overlay_SystemWorkInit(void);
void Overlay_Init(void);
void Overlay_UnloadID(const FSOverlayID id);
void Overlay_UnloadMain(void);
void Overlay_UnloadItcm(void);
void Overlay_UnloadDtcm(void);
void Overlay_UnloadAll(void);
int Overlay_MemoryAreaGet(const FSOverlayID id);
BOOL Overlay_Load(const FSOverlayID id, int load_type);
BOOL Overlay_Call(const FSOverlayID id, int load_type, void(*func)(void *), void * work);

//--------------------------------------------------------------
/**
 * @brief   �I�[�o�[���C����̃V�X�e�����[�N���N���A����
 */
//--------------------------------------------------------------
void Overlay_SystemWorkInit(void)
{
	MI_CpuClear32(&OverlaySys, sizeof(OVERLAY_SYSTEM));
}

//--------------------------------------------------------------
/**
 * @brief   ���ݓǂݍ���ł���S�ẴI�[�o�[���C���A�����[�h���Ă���A�V�X�e�����[�N���N���A����
 */
//--------------------------------------------------------------
void Overlay_Init(void)
{
	Overlay_UnloadAll();
	Overlay_SystemWorkInit();
}

//--------------------------------------------------------------
/**
 * @brief   �I�[�o�[���C���A�����[�h���܂�
 * @param   ovwork		�I�[�o�[���C���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Overlay_Unload(OVERLAY_WORK *ovwork)
{
	//���ݓǂݍ��܂�Ă���I�[�o�[���C���W���[�����A�����[�h���܂�
	BOOL ret;
#ifdef DEBUG_OVELAY_UNLOAD_CLEAR
	u32 start, end;
#endif

	GF_ASSERT(ovwork->loaded == TRUE);

#ifdef DEBUG_OVELAY_UNLOAD_CLEAR
	//�A�����[�h�����I�[�o�[���C�̈��0�N���A���邽�߂ɉ������O�ɃA�h���X�擾
	Overlay_RamStartEndAdressGet(ovwork->loaded_id, &start, &end);
#endif

	ret = FS_UnloadOverlay(MI_PROCESSOR_ARM9, ovwork->loaded_id);
	OS_Printf("overlay ������܂��� id = 0x%08X(10�i���F%d)\n", 
		ovwork->loaded_id, ovwork->loaded_id);
	GF_ASSERT(ret == TRUE);
	ovwork->loaded = FALSE;

#ifdef DEBUG_OVELAY_UNLOAD_CLEAR
	//�A�����[�h�����I�[�o�[���C�̈���N���A����
	OS_TPrintf("overlay unloade start address = 0x%08X\n", start);
	OS_TPrintf("overlay unloade end address = 0x%08X\n", end);
	//MI_CpuClear8((void*)start, end - start);
	MI_CpuFill8((void*)start, 0xff, end - start);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   �w�肵���I�[�o�[���CID�̃I�[�o�[���C���A�����[�h���܂�
 *
 * @param   id		�I�[�o�[���CID
 *
 * ���[�h����Ă��Ȃ��ꍇ�͉������܂���
 */
//--------------------------------------------------------------
void Overlay_UnloadID(const FSOverlayID id)
{
	OVERLAY_WORK *ovwork;
	int memory_area;
	int i;
	
	memory_area = Overlay_MemoryAreaGet(id);
	ovwork = Overlay_AreaOverlayWorkPtrGet(memory_area);
	
	for(i = 0; i < AREA_WORK_MAX; i++){
		if(ovwork[i].loaded == TRUE && ovwork[i].loaded_id == id){
			//���ݓǂݍ��܂�Ă���I�[�o�[���C���W���[�����A�����[�h���܂�
			Overlay_Unload(&ovwork[i]);
			return;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���C���������ɓW�J����Ă���I�[�o�[���C��S�ăA�����[�h���܂�
 */
//--------------------------------------------------------------
void Overlay_UnloadMain(void)
{
	int i;
	
	for(i = 0; i < AREA_WORK_MAX; i++){
		if(OverlaySys.main[i].loaded == TRUE){
			Overlay_Unload(&OverlaySys.main[i]);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   ITCM�ɓW�J����Ă���I�[�o�[���C��S�ăA�����[�h���܂�
 */
//--------------------------------------------------------------
void Overlay_UnloadItcm(void)
{
	int i;
	
	for(i = 0; i < AREA_WORK_MAX; i++){
		if(OverlaySys.itcm[i].loaded == TRUE){
			Overlay_Unload(&OverlaySys.itcm[i]);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   DTCM�ɓW�J����Ă���I�[�o�[���C��S�ăA�����[�h���܂�
 */
//--------------------------------------------------------------
void Overlay_UnloadDtcm(void)
{
	int i;
	
	for(i = 0; i < AREA_WORK_MAX; i++){
		if(OverlaySys.dtcm[i].loaded == TRUE){
			Overlay_Unload(&OverlaySys.dtcm[i]);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �w�肵���I�[�o�[���CID�Ɠ����������G���A�ɓW�J����Ă���I�[�o�[���C�̈��
 *          �S�ăA�����[�h���܂�
 *
 * @param   id		�I�[�o�[���CID
 */
//--------------------------------------------------------------
void Overlay_UnloadSameArea(const FSOverlayID id)
{
	int memory_area;
	
	memory_area = Overlay_MemoryAreaGet(id);
	switch(memory_area){
	case OVERLAY_AREA_MAIN:
		Overlay_UnloadMain();
		break;
	case OVERLAY_AREA_ITCM:
		Overlay_UnloadItcm();
		break;
	case OVERLAY_AREA_DTCM:
		Overlay_UnloadDtcm();
		break;
	default:
		GF_ASSERT(0);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���ݓǂݍ���ł���I�[�o�[���C�ւ̃A�����[�h���A�S�Ă̗̈�ɑ΂��čs��
 */
//--------------------------------------------------------------
void Overlay_UnloadAll(void)
{
	Overlay_UnloadMain();
	Overlay_UnloadItcm();
	Overlay_UnloadDtcm();
}

//--------------------------------------------------------------
/**
 * @brief   �w��I�[�o�[���CID�̓W�J�惁�����G���A���擾����
 * @param   id		�I�[�o�[���CID
 * @retval  �W�J�惁�����G���A(OVERLAY_AREA_???)
 */
//--------------------------------------------------------------
int Overlay_MemoryAreaGet(const FSOverlayID id)
{
	FSOverlayInfo info;
	BOOL ret;
	u32 ram_address;
	
	ret = FS_LoadOverlayInfo(&info, MI_PROCESSOR_ARM9, id);
	GF_ASSERT(ret == TRUE);
	
	ram_address = (u32)FS_GetOverlayAddress(&info);
	if(ram_address <= HW_ITCM_END && ram_address >= HW_ITCM_IMAGE){
		return OVERLAY_AREA_ITCM;
	}
	else if(ram_address <= HW_DTCM_END && ram_address >= HW_DTCM){
		return OVERLAY_AREA_DTCM;
	}
	return OVERLAY_AREA_MAIN;
}

//--------------------------------------------------------------
/**
 * @brief   �w�肵���I�[�o�[���C�����[�h����
 *
 * @param   id				���[�h����I�[�o�[���CID
 * @param   load_type		���[�h�^�C�v(OVERLAY_LOAD_???)
 *
 * @retval  TRUE:����
 * @retval  FALSE:���s
 *
 * �����̃I�[�o�[���C�����s���Ă��鎞�A�̈悪������ꍇ�̓I�[�o�[���C�͎��s���܂��B
 * (�f�o�b�O����GF_ASSERT�Œ�~���܂�)
 *
 * ���[�h��FS_SetDefaultDMA(or FS_Init)�Őݒ肳��Ă�����@�ōs���܂��B
 * �g�p����DMA,CPU��ύX�������ꍇ�́A���̊֐����s�O��FS_SetDefaultDMA�Őݒ���s���Ă��������B
 * ITCM,DTCM�ւ̃��[�h�͓����ňꎞ�I��CPU�ɕύX���ă��[�h���s���܂��B(���[�h��͌��̐ݒ�ɖ߂��܂�)
 */
//--------------------------------------------------------------
BOOL Overlay_Load(const FSOverlayID id, int load_type)
{
	BOOL ret;
	int memory_area;
	u32 dma_bak = FS_DMA_NOT_USE;
	OVERLAY_WORK *ovwork;
	int i;
	
//	Overlay_Unload(memory_area);	//���̈���g�p���Ă���I�[�o�[���C���A�����[�h
	if(Overlay_CrossAreaCheck(id) == FALSE){
		return FALSE;
	}

	//�󂫃��[�N�T�[�`
	memory_area = Overlay_MemoryAreaGet(id);
	ovwork = Overlay_AreaOverlayWorkPtrGet(memory_area);
	for(i = 0; i < AREA_WORK_MAX; i++){
		if(ovwork[i].loaded == FALSE){
			ovwork = &ovwork[i];
			ovwork->loaded = TRUE;
			ovwork->loaded_id = id;
			break;
		}
	}
	if(i >= AREA_WORK_MAX){
		GF_ASSERT(0);	//���������G���A���ɃI�[�o�[���C�o���鐔�𒴂��Ă���
		return FALSE;
	}
	
	if(memory_area == OVERLAY_AREA_ITCM || memory_area == OVERLAY_AREA_DTCM){
		//TCM�ւ̏������݂�DMA�ł͏o���Ȃ��̂ňꎞ�I��CPU�֕ύX
		dma_bak = FS_SetDefaultDMA(FS_DMA_NOT_USE);
	}
	
	switch(load_type){
	case OVERLAY_LOAD_SYNCHRONIZE:
		ret = load_overlay_high(MI_PROCESSOR_ARM9, id);
		break;
	case OVERLAY_LOAD_SYNCHRONIZE_2:
		ret = load_overlay_middle(MI_PROCESSOR_ARM9, id);
		break;
	case OVERLAY_LOAD_NOT_SYNCHRONIZE:
		ret = load_overlay_low(MI_PROCESSOR_ARM9, id);
		break;
	default:		//�s���ȃ��[�h�^�C�v
		GF_ASSERT(0);
		return FALSE;
	}

	if(memory_area == OVERLAY_AREA_ITCM || memory_area == OVERLAY_AREA_DTCM){
		//�ꎞ�I�ɕύX�����̂����ɖ߂�
		FS_SetDefaultDMA(dma_bak);
	}

	if(ret == FALSE){	//���[�h���s
		OS_Printf("overlay 0x%08X is not available!\n", id);
		GF_ASSERT(0);
		return FALSE;
	}

	OS_Printf("overlay ���[�h���܂��� id = 0x%08X(10�i��:%d)\n", id, id);
	
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �w�肵���I�[�o�[���CID�̗̈悪���ݓW�J����Ă���I�[�o�[���C�̈�ƃA�h���X��
 *          ����Ă��Ȃ����`�F�b�N����
 *
 * @param   id		�I�[�o�[���CID
 *
 * @retval  TRUE:����Ă��Ȃ��B�@FALSE:����Ă���(�G���[�̏ꍇ���L)
 */
//--------------------------------------------------------------
static BOOL Overlay_CrossAreaCheck(const FSOverlayID id)
{
	int memory_area;
	u32 start, end, c_start, c_end;
	BOOL ret;
	OVERLAY_WORK *ovwork;
	int i;
	
	ret = Overlay_RamStartEndAdressGet(id, &start, &end);
	if(ret == FALSE){
		return FALSE;
	}
	
	memory_area = Overlay_MemoryAreaGet(id);
	ovwork = Overlay_AreaOverlayWorkPtrGet(memory_area);
	for(i = 0; i < AREA_WORK_MAX; i++){
		if(ovwork[i].loaded == TRUE){
			ret = Overlay_RamStartEndAdressGet(ovwork[i].loaded_id, &c_start, &c_end);
			if(ret == TRUE){
				if((start >= c_start && start < c_end) || (end > c_start && end <= c_end)
						|| (start <= c_start && end >= c_end)){
					OS_Printf("�I�[�o�[���C�̈�ɏd�����������܂����I\n");
					OS_Printf("�W�J�ς�ID=%d�A�V�K�ɓW�J���悤�Ƃ���ID=%d\n", 
						ovwork[i].loaded_id, id);
					GF_ASSERT(0);
					return FALSE;
				}
			}
		}
	}
	
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �w�胁�����G���A���Q�Ƃ���I�[�o�[���C���[�N�̐擪�A�h���X���擾����
 * @param   memory_area		�������G���A(OVERLAY_AREA_???)
 * @retval  �w�胁�����ɑΉ������I�[�o�[���C���[�N�̐擪�A�h���X
 */
//--------------------------------------------------------------
static OVERLAY_WORK * Overlay_AreaOverlayWorkPtrGet(int memory_area)
{
	OVERLAY_WORK *ovwork;
	
	switch(memory_area){
	case OVERLAY_AREA_MAIN:
	default:
		ovwork = OverlaySys.main;
		break;
	case OVERLAY_AREA_ITCM:
		ovwork = OverlaySys.itcm;
		break;
	case OVERLAY_AREA_DTCM:
		ovwork = OverlaySys.dtcm;
		break;
	}
	return ovwork;
}

//--------------------------------------------------------------
/**
 * @brief   �w��I�[�o�[���CID�̃��[�h�J�n�A�h���X�ƃ��[�h�I���A�h���X���擾����
 *
 * @param   id			�I�[�o�[���CID
 * @param   start		�擾�������[�h�J�n�A�h���X�����
 * @param   end			�擾�������[�h�I���A�h���X�����
 *
 * @retval  TRUE:����I���B�@FALSE:���s
 */
//--------------------------------------------------------------
static BOOL Overlay_RamStartEndAdressGet(const FSOverlayID id, u32 *start, u32 *end)
{
	FSOverlayInfo info;
	BOOL ret;
	
	ret = FS_LoadOverlayInfo(&info, MI_PROCESSOR_ARM9, id);
	if(ret == FALSE){
		GF_ASSERT(0);
		return FALSE;
	}
	
	*start = (u32)FS_GetOverlayAddress(&info);
	*end = *start + FS_GetOverlayTotalSize(&info);
	
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �S�Ă𓯊��I�Ɏ��s
 *
 * @param   target		���[�h����ΏہiARM9�v���Z�b�T/ARM7�v���Z�b�T�j
 * @param   id			�I�[�o�[���CID
 *
 * @retval  TRUE:����
 * @retval  FALSE:���s
 */
//--------------------------------------------------------------
static BOOL load_overlay_high(MIProcessor target, FSOverlayID id)
{
	return FS_LoadOverlay(target, id);
}

//--------------------------------------------------------------
/**
 * @brief   �����I�Ɏ��ƂŎ��s (�����I)
 *
 * @param   target		���[�h����ΏہiARM9�v���Z�b�T/ARM7�v���Z�b�T�j
 * @param   id			�I�[�o�[���CID
 *
 * @retval  TRUE:����
 * @retval  FALSE:���s
 */
//--------------------------------------------------------------
static BOOL load_overlay_middle(MIProcessor target, FSOverlayID id)
{
	FSOverlayInfo info;

	if(!FS_LoadOverlayInfo(&info, target, id)){
		return FALSE;
	}
	if(!FS_LoadOverlayImage(&info)){
		return FALSE;
	}
	FS_StartOverlay(&info);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �S�Ă����ƂŎ��s (�񓯊��I)
 *
 * @param   target		���[�h����ΏہiARM9�v���Z�b�T/ARM7�v���Z�b�T�j
 * @param   id			�I�[�o�[���CID
 *
 * @retval  TRUE:����
 * @retval  FALSE:���s
 */
//--------------------------------------------------------------
static BOOL load_overlay_low(MIProcessor target, FSOverlayID id)
{
	FSOverlayInfo info;
	
	//�I�[�o�[���C���W���[���̏������[�h���܂�
	if (!FS_LoadOverlayInfo(&info, target, id)){
		return FALSE;
	}
	
	{
		FSFile file;
		
		//FSFile�\���̂����������܂�
		FS_InitFile(&file);
		(void)FS_LoadOverlayImageAsync(&info, &file);
		(void)FS_WaitAsync(&file);
		(void)FS_CloseFile(&file);
	}
	FS_StartOverlay(&info);
	return TRUE;
}

//--------------------------------------------------------------
/**
 */
//--------------------------------------------------------------
BOOL Overlay_Call(const FSOverlayID id, int load_type, void(*func)(void *), void * work)
{
	if (!Overlay_Load(id, load_type)) {
		return FALSE;
	}
	func(work);

	Overlay_UnloadID(id);
	return TRUE;
}

