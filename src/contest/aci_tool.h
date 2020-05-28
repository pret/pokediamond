//==============================================================================
/**
 * @file	aci_tool.h
 * @brief	actin_input.cで使用するツール(actin_input.cのシステムに依存しないもの限定)のヘッダ
 * @author	matsuda
 * @date	2005.12.02(金)
 */
//==============================================================================
#ifndef __ACI_TOOL_H__
#define __ACI_TOOL_H__


//==============================================================================
//	外部関数宣言
//==============================================================================
extern void ACIT_SubHeartJudgeResourceSet(CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern CATS_ACT_PTR ACIT_SubHeartJudgeActorAdd(CATS_SYS_PTR csp, CATS_RES_PTR crp, int judge_no);
extern void ACIT_SubHeartJudgeResourceFree(CATS_RES_PTR crp);
extern void ACIT_SubHeartJudgeActorDel(CATS_ACT_PTR sub_heart_judge_cap);
extern void ACIT_AppHeartResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp);
extern CATS_ACT_PTR ACIT_AppHeartActorSet(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	int x, int y, int ap_point);
extern void ACIT_AppHeartActorDel(CATS_ACT_PTR heart_cap);
extern void ACIT_AppHeartResourceFree(CATS_RES_PTR crp);


#endif	//__ACI_TOOL_H__

