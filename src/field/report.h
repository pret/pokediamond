//============================================================================================
/**
 * @file	report.h
 * @brief	フィールドでのセーブ補助関数
 * @date	2005.12.13
 * @author	tamada GAME FREAK inc.
 *
 * 「レポートをかく」の情報ウィンドウなど
 */
//============================================================================================
#ifndef	__REPORT_H__
#define	__REPORT_H__

#include "field_common.h"
//--------------------------------------------------------------------
/**
 * @brief	レポート情報ウィンドウへの不完全型ポインタ
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
