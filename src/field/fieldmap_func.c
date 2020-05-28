//============================================================================================
/**
 * @file	fieldmap_func.c
 * @brief	�t�B�[���h�}�b�v��œ��삷�鐧��^�X�N�V�X�e��
 * @author	tamada GAME FREAK inc.
 * @date	2006.03.15
 *
 */
//============================================================================================

#include "common.h"

#include "fieldsys.h"
#include "fieldmap_work.h"

#include "fieldmap_func_def.h"
#include "fieldmap_func.h"

//============================================================================================
//============================================================================================
typedef struct {
	u32 dmy[8];			///<�ėp���[�N
}FREE_WORK;

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�}�b�v�p����^�X�N�V�X�e���̃V�X�e�����[�N��`
 */
//------------------------------------------------------------------
struct FLDMAPFUNC_SYS{
	FIELDSYS_WORK * fsys;		///<�t�B�[���h����V�X�e���ւ̃|�C���^
	int heapID;					///<�g�p����q�[�v��ID
	int max;					///<FLDMAPFUNC�̍ő吔
	FLDMAPFUNC_WORK * array;	///<FLDMAPFUNC�p���[�N�̔z��ւ̃|�C���^
	TCBSYS * drawsys;			///<�`��pTCB
};

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�}�b�v�p����^�X�N�̐��䃏�[�N��`
 */
//------------------------------------------------------------------
struct FLDMAPFUNC_WORK{
	FLDMAPFUNC_SYS * sys;			///<����V�X�e���ւ̃|�C���^
	TCB_PTR tcb;					///<�ێ����Ă���TCB�ւ̃|�C���^
	TCB_PTR drawtcb;				///<�ێ����Ă���`��TCB�ւ̃|�C���^
	const FLDMAPFUNC_DATA * data;	///<��`�f�[�^�ւ̃|�C���^
	void * free_work;				///<���ꂼ��Ŏg�p���郏�[�N�ւ̃|�C���^
};

#define	DEFAULT_FREEWORK_SIZE	(sizeof(FREE_WORK))

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�}�b�v����^�X�N�F�V�X�e�������A������
 * @param	fsys			�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	heapID			�g�p����q�[�v�̎w��
 * @param	max
 * @return	FLDMAPFUNC_SYS	�t�B�[���h�}�b�v����^�X�N�V�X�e���̃V�X�e�����[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
FLDMAPFUNC_SYS * FLDMAPFUNC_Sys_Create(FIELDSYS_WORK * fsys, int heapID, int max)
{
	FLDMAPFUNC_SYS * sys;
	u32 drawtcb_work_size;
	sys = sys_AllocMemory(heapID, sizeof(FLDMAPFUNC_SYS));
	sys->fsys = fsys;
	sys->heapID = heapID;
	sys->max = max;
	sys->array = sys_AllocMemory(heapID, sizeof(FLDMAPFUNC_WORK) * max);
	MI_CpuClear32(sys->array, sizeof(FLDMAPFUNC_WORK) * max);

	///�`��pTCB����
	///�Ȃ�fieldmap_func���`��pTCB�����̂��̗��R
	///�`��p��TCB��fieldmap_work.c/h�Ŏ����Ă��Ă��ǂ��ł����A
	///�`��pTCB�S�̂̔j��������Ƃ��ɖ�肪����܂��B
	///�X�̃^�X�N���Ń��������m�ۂ��Ă���ƁA
	///�S�̔j�����Ƀ��������[�N�������Ă��܂��܂��B
	///�ł��̂ŁA�j���������ʂɗp�ӂ���Ă���
	///fieldmap_func�̒��ɕ`�揈����ǉ�����
	///���������[�N�̋N����Ȃ��悤�ɂ��܂��B
	drawtcb_work_size = TCBSYS_CalcSystemWorkSize( max );
	sys->drawsys = sys_AllocMemory( heapID, drawtcb_work_size );
	sys->drawsys = TCBSYS_Create( max, sys->drawsys );
	
	return sys;
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�}�b�v����^�X�N�F�V�X�e���I���A���
 * @return	sys		�t�B�[���h�}�b�v����^�X�N�V�X�e���̃V�X�e�����[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
void FLDMAPFUNC_Sys_Delete(FLDMAPFUNC_SYS * sys)
{
	int i;
	for (i = 0; i < sys->max; i++) {
		FLDMAPFUNC_Delete(&sys->array[i]);
	}
	sys_FreeMemoryEz(sys->array);
	sys_FreeMemoryEz( sys->drawsys );		///<�`��TCB�j��
	sys_FreeMemoryEz(sys);
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�}�b�v����^�X�N�F�V�X�e��3D�`��
 * @return	sys		�t�B�[���h�}�b�v����^�X�N�V�X�e���̃V�X�e�����[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
void FLDMAPFUNC_Sys_Draw3D(FLDMAPFUNC_SYS * sys)
{
	// �`��^�X�N���s
	TCBSYS_Main( sys->drawsys );
}

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�}�b�v����^�X�N�̌Ăяo������
 * @param	tcb		�g�p����TCB�ւ̃|�C���^
 * @param	work	�g�p���郏�[�N�ւ̃|�C���^�i���̏ꍇ�A�K��FLDMAPFUNC_WORK�ւ̃|�C���^�j
 */
//------------------------------------------------------------------
static void FLDMAPFUNC_Tcb(TCB_PTR tcb, void * work)
{
	FLDMAPFUNC_WORK * fwk = work;
	//�t�B�[���h���C�������삵�Ă���Ԃ������삷��
	if (GameSystem_CheckFieldMain(fwk->sys->fsys)) {
		if( fwk->data->update_func ){
			fwk->data->update_func(fwk, fwk->sys->fsys, fwk->free_work);
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�}�b�v�`��^�X�N�̌Ăяo������
 * @param	tcb		�g�p����TCB�ւ̃|�C���^
 * @param	work	�g�p���郏�[�N�ւ̃|�C���^�i���̏ꍇ�A�K��FLDMAPFUNC_WORK�ւ̃|�C���^�j
 */
//------------------------------------------------------------------
static void FLDMAPFUNC_DrawTcb(TCB_PTR tcb, void * work)
{
	FLDMAPFUNC_WORK * fwk = work;
	//�t�B�[���h���C�������삵�Ă���Ԃ������삷��
	if (GameSystem_CheckFieldMain(fwk->sys->fsys)) {
		if( fwk->data->draw3d_func ){
			fwk->data->draw3d_func(fwk, fwk->sys->fsys, fwk->free_work);
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�}�b�v����^�X�N�F����
 * @param	sys		�t�B�[���h�}�b�v����^�X�N�V�X�e���̃V�X�e�����[�N�ւ̃|�C���^
 * @param	data	�������悤�Ƃ��Ă��鐧��^�X�N�̒�`�f�[�^
 * @return	FLDMAPFUNC_WORK	������������^�X�N�̃��[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
FLDMAPFUNC_WORK * FLDMAPFUNC_Create(FLDMAPFUNC_SYS * sys, const FLDMAPFUNC_DATA * data)
{
	int i;
	FLDMAPFUNC_WORK * fwk;
	for (fwk = sys->array, i = 0; i < sys->max; fwk ++, i++) {
		if (fwk->tcb == NULL) {
			fwk->tcb = TCB_Add(FLDMAPFUNC_Tcb, fwk, data->pri);
			fwk->drawtcb = TCBSYS_AddTask(sys->drawsys, FLDMAPFUNC_DrawTcb, fwk, data->pri);
			fwk->sys = sys;
			fwk->data = data;
			GF_ASSERT(fwk->tcb != NULL);
			GF_ASSERT(fwk->drawtcb != NULL);
			if (data->work_size != 0) {
				fwk->free_work = sys_AllocMemory(sys->heapID, data->work_size);
			}
			if( data->create_func ){
				data->create_func(fwk, sys->fsys, fwk->free_work);
			}
			return fwk;
		}
	}
	GF_ASSERT_MSG(0, "FLDMAPFUNC:�V�K�ǉ��Ɏ��s���܂���\n");
	return NULL;
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�}�b�v����^�X�N�F����
 * @param	fwk		FLDMAPFUNC_WORK�ւ̃|�C���^
 */
//------------------------------------------------------------------
void FLDMAPFUNC_Delete(FLDMAPFUNC_WORK * fwk)
{
	if (fwk->tcb == NULL) {
		return;
	}
	//�ʏ��������Ăяo��
	if( fwk->data->delete_func ){
		fwk->data->delete_func(fwk, fwk->sys->fsys, fwk->free_work);	}
	if (fwk->data->work_size != 0) {
		sys_FreeMemoryEz(fwk->free_work);
	}
	TCB_Delete(fwk->tcb);
	TCB_Delete(fwk->drawtcb);
	MI_CpuClear32(fwk, sizeof(FLDMAPFUNC_WORK));
}


//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�}�b�v����^�X�N�F�t���[���[�N�|�C���^�擾
 * @param	fwk		FLDMAPFUNC_WORK�ւ̃|�C���^
 * @retval	�t���[���[�N�̃|�C���^
 *		�����t���O�𗧂Ă�ȂǍ��K�v�Ƃ���
 *		���ɂ��̊֐��ŁA���[�N���擾���邱�ƁB
 *		�����Ń��[�N���j�������̂ŁA�����ƕێ����Ȃ����ƁB
 */
//------------------------------------------------------------------
void * FLDMAPFUNC_GetFreeWork(FLDMAPFUNC_WORK * fwk)
{
	return fwk->free_work;
}

//------------------------------------------------------------------
//------------------------------------------------------------------


//------------------------------------------------------------------
//------------------------------------------------------------------
