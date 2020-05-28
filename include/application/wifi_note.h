//============================================================================================
/**
 * @file	wifi_note.h
 * @bfief	WIFI�F�B�蒠
 * @author	k.ohno
 * @date	06.04.05
 */
//============================================================================================
#ifndef __WIFI_NOTE_H__
#define __WIFI_NOTE_H__

//============================================================================================
//	��`
//============================================================================================

//------------------------------------------------------
/**
 * WIFI�Ƃ��������X�gPROC�p�����[�^
 */
//------------------------------------------------------
typedef struct {
	SAVEDATA*  savedata;
}WIFINOTE_PROC_PARAM;


// �v���Z�X��`�f�[�^
extern PROC_RESULT WifiNoteProc_Init( PROC * proc, int * seq );
extern PROC_RESULT WifiNoteProc_Main( PROC * proc, int * seq );
extern PROC_RESULT WifiNoteProc_End( PROC * proc, int * seq );

// �o�^�p�v���Z�X��`�f�[�^
extern PROC_RESULT WifiNoteEntryProc_Init( PROC * proc, int * seq );

// �|�C���^�Q�Ƃ����ł��郌�R�[�h�R�[�i�[���[�N�\����
typedef struct _WIFINOTE_WORK WIFINOTE_WORK;	



#endif //__WIFI_NOTE_H__
