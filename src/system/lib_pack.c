/*---------------------------------------------------------------------------*
  Project:  PokemonDS
  File:     lib_pack.c

  ���C�u�����p�b�P�[�W

 *---------------------------------------------------------------------------*/
#include "common.h"

#define __LIBPACK_H_GLOBAL__
#include "system/lib_pack.h"

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
//===========================================================================
/**
 * 
 * �^�X�N�ݒ�
 *
 */
//===========================================================================
TCB_PTR	PMDS_taskAdd(TCB_FUNC func, int work_size, u32 pri, const u32 heap_id)
{
	void*	work_memory;

	if( work_size ){
		// �������m��
		work_memory = sys_AllocMemory( heap_id, work_size );
		if (work_memory == NULL){
			OS_Printf("cannot get RAM for task! no enough memory.\n");
			return NULL;
		}
		memset( work_memory, 0, work_size );
	}else{
		// �������m�ۂȂ�
		work_memory = NULL;
	}
	return TCB_Add( func, work_memory, pri);
}

//===========================================================================
/**
 * 
 * �^�X�N����
 *
 */
//===========================================================================
void	PMDS_taskDel(TCB_PTR tcb)
{
	void*	work_memory;

	work_memory = TCB_GetWork(tcb);
	if( work_memory != NULL ){
		// �������J��
		sys_FreeMemoryEz(work_memory);
	}
	TCB_Delete(tcb);
}


