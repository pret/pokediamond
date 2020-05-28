//=============================================================================
/**
 * @file	comm_regulation.h
 * @bfief	レギュレーションリスト呼び出し
 * @author	katsumi ohno
 * @date	06/05/24
 */
//=============================================================================

#ifndef __COMM_REGULATION_H__
#define __COMM_REGULATION_H__


extern void EventCmd_RegulationListSet(FIELDSYS_WORK * pFSys);
extern void EventCmd_RegulationListCall(GMEVENT_CONTROL * event,u16* work);

#endif //__COMM_REGULATION_H__
