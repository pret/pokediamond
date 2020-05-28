//=============================================================================================
/**
 * @file	tcbman.h
 * @brief	�eTCB�V�X�e������ă^�X�N�������Ăяo��
 * @author	taya
 * @date	2005.10.07
 */
//=============================================================================================
#ifndef __TCBMAN_H__
#define __TCBMAN_H__

extern TCB_PTR TCB_Add(TCB_FUNC func, void* work, u32 pri);
extern TCB_PTR VIntrTCB_Add( TCB_FUNC func, void* work, u32 pri );
extern TCB_PTR VWaitTCB_Add( TCB_FUNC func, void* work, u32 pri );
extern TCB_PTR PrintTCB_Add( TCB_FUNC func, void* work, u32 pri );

extern void TCB_Delete(TCB_PTR tcb);

#endif
