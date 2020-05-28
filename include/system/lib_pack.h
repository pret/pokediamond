//=============================================================================
/**
 * @file	lib_pack.h	
 * @bfief	ライブラリパッケージ
 * @author	GAME FREAK inc.
 */
//=============================================================================
#undef GLOBAL
#ifdef __LIBPACK_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif

GLOBAL TCB_PTR	PMDS_taskAdd(TCB_FUNC func, int work_size, u32 pri, const u32 heap_id);
GLOBAL void		PMDS_taskDel(TCB_PTR tcb);

#undef GLOBAL
