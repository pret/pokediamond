//=============================================================================
/**
 * @file	opening_kira_obj.c
 * @brief	オープニングデモＯＢＪ
 * @author	Nozomu Saito
 * @date    2006.06.03
 */
//=============================================================================
#ifndef __OPENING_KIRA_OBJ_H__
#define __OPENING_KIRA_OBJ_H__

typedef struct OPD_KIRA_GENERATE_MNG_tag *OPD_K_G_MNG_PTR;
typedef struct OPD_KIRA_DATA_LIST_tag * OPD_KIRA_DATLST_PTR;

extern OPD_K_G_MNG_PTR OPDKira_AllocGeneMng( void );
extern OPD_KIRA_DATLST_PTR OPDKira_CreateList(const int inNum);
extern void OPDKira_FreeList(OPD_KIRA_DATLST_PTR pKiraDataListPtr);
extern CLACT_WORK_PTR *OPDKira_GetActWorkPtrFromList(OPD_KIRA_DATLST_PTR pKiraDataListPtr,
													 const int inIndex);
extern void OPDKira_FreeGeneMng(OPD_K_G_MNG_PTR ptr);
extern void KiraGenerateMain(OPD_K_G_MNG_PTR ptr, const int inCounter);

void Scene2_KiraGenerateMain(OPD_KIRA_DATLST_PTR pKiraDataListPtr);

#endif	//__OPENING_KIRA_OBJ_H__
