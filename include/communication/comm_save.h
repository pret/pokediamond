//=============================================================================
/**
 * @file	comm_save.h
 * @brief	�ʐM�����Z�[�u����
 * @author	Akito Mori
 * @date    2006.05.12
 */
//=============================================================================

#ifndef __COMM_SAVE_H__
#define __COMM_SAVE_H__

#include "savedata/savedata.h"

extern void CommSyncronizeSaveInit( int *seq );
extern int CommSyncronizeSave( SAVEDATA *savedata, int BlockID, int *seq );


#endif /* __COMM_COMMAND_H__*/

