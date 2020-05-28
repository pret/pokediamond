//=============================================================================
/**
 * @file	�v���Z�X�Ǘ��V�X�e��
 * @brief
 * @date	2005.07.25
 */
//=============================================================================

#include "common.h"
#include "system\pm_overlay.h"

#include "system/procsys.h"


//------------------------------------------------------------------
/**
 * @brief	�v���Z�X�����̓���V�[�P���X
 */
//------------------------------------------------------------------
enum {
	SEQ_OVERLAY_LOAD = 0,
	SEQ_INIT,
	SEQ_MAIN,
	SEQ_END,
	SEQ_OVERLAY_UNLOAD,
};


//------------------------------------------------------------------
/**
 * @brief	�v���Z�X�\���̒�`
 */
//------------------------------------------------------------------
struct _PROC{
	PROC_DATA data;				///<�v���Z�X��`�f�[�^�ւ̃|�C���^
	int proc_seq;				///<�v���Z�X�����V�[�P���X
	int subseq;					///<�v���Z�X�֐��̓���V�[�P���X
	void * parent_work;			///<��ʃ��[�N�ւ̃|�C���^
	void * work;				///<�v���Z�X�������[�N�ւ̃|�C���^
	PROC * parent;				///<��ʃv���Z�X�ւ̃|�C���^
	PROC * child;				///<���ʃv���Z�X�ւ̃|�C���^
};


//===========================================================================
//
//		�֐�
//
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	�v���Z�X��������
 * @param	func		�v���Z�X����֐�
 * @param	parent_work	��ʂ�������n�����[�N�ւ̃|�C���^
 * @param	heap_id	�g�p����q�[�v
 * @return	PROC		���������v���Z�X�ւ̃|�C���^
 */
//------------------------------------------------------------------
PROC * PROC_Create(const PROC_DATA * data, void * parent_work, const int heap_id)
{
	PROC * proc;
	proc = sys_AllocMemory(heap_id, sizeof(PROC));
	proc->data = *data;
	proc->proc_seq = 0;
	proc->subseq = 0;
	proc->parent_work = parent_work;
	proc->work = NULL;
	proc->parent = NULL;
	proc->child = NULL;
	return proc;
}

//------------------------------------------------------------------
/**
 * @brief	�q�v���Z�X�𐶐�����
 * @param	proc		���݂̓���v���Z�X�ւ̃|�C���^
 * @param	func		�v���Z�X����֐�
 * @param	parent_work	��ʂ�������n�����[�N�ւ̃|�C���^
 * @param	heap_id	�g�p����q�[�v
 * @return	PROC		���������v���Z�X�ւ̃|�C���^
 */
//------------------------------------------------------------------
PROC * PROC_CreateChild(PROC * proc, const PROC_DATA * data, void * parent_work, const int heap_id)
{
	PROC * child;
	child = PROC_Create(data, parent_work, heap_id);
	proc->child = child;
	child->parent = proc;
	return child;
}
//------------------------------------------------------------------
/**
 * @brief	�v���Z�X���폜����
 * @param	proc	�v���Z�X�ւ̃|�C���^
 */
//------------------------------------------------------------------
void PROC_Delete(PROC * proc)
{
	SDK_ASSERT(proc->work == NULL);
	sys_FreeMemoryEz(proc);
}

//------------------------------------------------------------------
/**
 * @brief	�v���Z�X�����[�N�̊m��
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	size	�m�ۂ��郏�[�N�T�C�Y
 * @param	heap_id	�g�p����q�[�v
 * @return	void *	�m�ۂ����v���Z�X�����[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
void * PROC_AllocWork(PROC * proc, int size, int heap_id)
{
	proc->work = sys_AllocMemory(heap_id, size);
	return proc->work;
}

//------------------------------------------------------------------
/**
 * @brief	�v���Z�X�����[�N�̃|�C���^�擾
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @return	void *	�v���Z�X�����[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
void * PROC_GetWork(PROC * proc)
{
	SDK_ASSERT(proc->work != NULL);
	return proc->work;
}

//------------------------------------------------------------------
/**
 * @brief	�v���Z�X�����[�N�̉��
 * @param	proc	�v���Z�X�ւ̃|�C���^
 */
//------------------------------------------------------------------
void PROC_FreeWork(PROC * proc)
{
	SDK_ASSERT(proc->work != NULL);
	sys_FreeMemoryEz(proc->work);
	proc->work = NULL;
}

//------------------------------------------------------------------
/**
 * @brief	��ʃ��[�N�ւ̃|�C���^�擾
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @return	void *	��ʃ��[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
void * PROC_GetParentWork(PROC * proc)
{
	SDK_ASSERT(proc->parent_work != NULL);
	return proc->parent_work;
}

//------------------------------------------------------------------
/**
 * @brief	�v���Z�X���쏈�����C��
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @retval	TRUE	�v���Z�X����I��
 * @retval	FALSE	�v���Z�X����p����
 */
//------------------------------------------------------------------
BOOL ProcMain(PROC * proc)
{
	PROC_RESULT result;

	switch (proc->proc_seq) {
	case SEQ_OVERLAY_LOAD:
		if(proc->data.overlay_id != NO_OVERLAY_ID){
			TPRINTF("OVERLAY ID = %d\n", proc->data.overlay_id);
			Overlay_Load( proc->data.overlay_id, OVERLAY_LOAD_NOT_SYNCHRONIZE);
		}
		proc->proc_seq = SEQ_INIT;

		/* fallthru */
			
	case SEQ_INIT:
		result = proc->data.init_func(proc, &proc->subseq);
		if (result == PROC_RES_FINISH) {
			proc->proc_seq = SEQ_MAIN;
			proc->subseq = 0;
		}
		break;
	case SEQ_MAIN:
		result = proc->data.main_func(proc, &proc->subseq);
		if (result == PROC_RES_FINISH) {
			proc->proc_seq = SEQ_END;
			proc->subseq = 0;
		}
		break;
	case SEQ_END:
		result = proc->data.end_func(proc, &proc->subseq);
		if (result == PROC_RES_FINISH) {
			if(proc->data.overlay_id != NO_OVERLAY_ID){
				Overlay_UnloadID( proc->data.overlay_id );
			}
			return TRUE;
		}
		break;
	}
	return FALSE;
}


