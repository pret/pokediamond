//============================================================================================
/**
 * @file	pms_input_param.h
 * @bfief	簡易会話入力画面（外部から引き渡されるパラメータオブジェクトの操作処理）
 * @author	taya
 * @date	06.01.24
 */
//============================================================================================
#ifndef __PMS_INPUT_PARAM_H__
#define __PMS_INPUT_PARAM_H__

#include "savedata\zukanwork.h"
#include "application\pms_input.h"
#include "system\pms_word.h"

extern u32 PMSI_PARAM_GetInputMode( const PMSI_PARAM* p );
extern u32 PMSI_PARAM_GetGuidanceType( const PMSI_PARAM* p );
extern int PMSI_PARAM_GetWindowType( const PMSI_PARAM* p );
extern const ZUKAN_WORK*  PMSI_PARAM_GetZukanSaveData( const PMSI_PARAM* p );
extern const PMSW_SAVEDATA* PMSI_PARAM_GetPMSW_SaveData( const PMSI_PARAM* p );
extern BOOL PMSI_PARAM_GetGameClearFlag( const PMSI_PARAM* p );
extern void PMSI_PARAM_GetInitializeData( const PMSI_PARAM* p, PMS_WORD* word, PMS_DATA* pms );
extern BOOL PMSI_PARAM_CheckModifiedByEditDatas( const PMSI_PARAM* p, const PMS_WORD* word, const PMS_DATA* pms );
extern void PMSI_PARAM_WriteBackData( PMSI_PARAM* p, const PMS_WORD* word, const PMS_DATA* pms );
extern BOOL PMSI_PARAM_GetNotEditEgnoreFlag( const PMSI_PARAM* p );



#endif
