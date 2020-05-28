//============================================================================================
/**
 * @file	report.h
 * @brief	�t�B�[���h�ł̃Z�[�u�⏕�֐�
 * @date	2005.12.13
 * @author	tamada GAME FREAK inc.
 *
 * �u���|�[�g�������v�̏��E�B���h�E�Ȃ�
 */
//============================================================================================
#ifndef	__REPORT_H__
#define	__REPORT_H__

#include "field_common.h"
//--------------------------------------------------------------------
/**
 * @brief	���|�[�g���E�B���h�E�ւ̕s���S�^�|�C���^
 */
//--------------------------------------------------------------------
typedef struct REPORT_INFO REPORT_INFO;

//--------------------------------------------------------------------
//--------------------------------------------------------------------
extern REPORT_INFO * ReportInfo_Create(FIELDSYS_WORK * fsys, int heapID, u8 frame_no);
extern void ReportInfo_Delete(REPORT_INFO * riw);
extern void ReportInfo_WriteWindow(REPORT_INFO * riw);
extern void ReportInfo_EraseWindow(REPORT_INFO * riw);


//--------------------------------------------------------------------
//--------------------------------------------------------------------
extern BOOL Field_Save(FIELDSYS_WORK * fsys);

#endif	//__REPORT_H__
