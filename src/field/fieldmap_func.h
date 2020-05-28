//============================================================================================
/**
 * @file	fieldmap_func.h
 * @brief	�t�B�[���h�}�b�v��œ��삷�鐧��^�X�N�V�X�e��
 * @author	tamada GAME FREAK inc.
 * @date	2006.03.15
 */
//============================================================================================
#ifndef	__FIELDMAP_FUNC_H__
#define	__FIELDMAP_FUNC_H__

#include "fieldmap_func_def.h"

//------------------------------------------------------------------
/**
 * @brief	FLDMAPFUNC�̐��䃏�[�N�ւ̕s���S�^��`
 */
//------------------------------------------------------------------
typedef struct FLDMAPFUNC_WORK FLDMAPFUNC_WORK;

typedef void (*FLDMAPFUNC_UPDATE)(FLDMAPFUNC_WORK *, FIELDSYS_WORK *, void *);
typedef void (*FLDMAPFUNC_DRAW3D)(FLDMAPFUNC_WORK *, FIELDSYS_WORK *, void *);
typedef void (*FLDMAPFUNC_CREATE)(FLDMAPFUNC_WORK *, FIELDSYS_WORK *, void *);
typedef void (*FLDMAPFUNC_DELETE)(FLDMAPFUNC_WORK *, FIELDSYS_WORK *, void *);

//------------------------------------------------------------------
/**
 * @brief	FLDMAPFUNC�𐶐�����̂ɕK�v�ȃf�[�^��`
 */
//------------------------------------------------------------------
typedef struct {
	u32 pri;						///<����v���C�I���e�B
	u16 work_size;					///<�m�ۂ��郏�[�N�̃T�C�Y
	FLDMAPFUNC_CREATE create_func;	///<��������
	FLDMAPFUNC_DELETE delete_func;	///<��������
	FLDMAPFUNC_UPDATE update_func;	///<�X�V����
	FLDMAPFUNC_DRAW3D draw3d_func;	///<3D�`�揈��
}FLDMAPFUNC_DATA;

//------------------------------------------------------------------
//		�V�X�e���֐�
//------------------------------------------------------------------
extern FLDMAPFUNC_SYS * FLDMAPFUNC_Sys_Create(FIELDSYS_WORK * fsys, int heapID, int max);
extern void FLDMAPFUNC_Sys_Delete(FLDMAPFUNC_SYS * sys);
extern void FLDMAPFUNC_Sys_Draw3D(FLDMAPFUNC_SYS * sys);

//------------------------------------------------------------------
//		�ʏ����p�֐�
//------------------------------------------------------------------
extern FLDMAPFUNC_WORK * FLDMAPFUNC_Create(FLDMAPFUNC_SYS * sys, const FLDMAPFUNC_DATA * data);
extern void FLDMAPFUNC_Delete(FLDMAPFUNC_WORK * fwk);

//------------------------------------------------------------------
//		�c�[���֐�
//------------------------------------------------------------------
extern void * FLDMAPFUNC_GetFreeWork(FLDMAPFUNC_WORK * fwk);

#endif	/* __FIELDMAP_FUNC_H__ */
