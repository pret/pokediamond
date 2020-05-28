/**
 *  @file	fld_comact.h
 *	@brief	�t�B�[���h��ɋ��L�`�悳���J�[�\���A�N�^�[�̃R���g���[��
 *	@author	Miyuki iwasawa
 *	@date	06.03.23
 */

#ifndef __H_FLD_COMACT_H__
#define __H_FLD_COMACT_H__

/*
#include "system/procsys.h"
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/pm_str.h"
#include "system/window.h"
#include "fld_bmp.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "field_event.h"
#include "field_skill.h"
#include "ev_mapchange.h"
#include "field/field.h"
*/
#include "system/clact_tool.h"
#include "field_clact.h"

typedef enum{
 FCA_UCURSOR,
 FCA_DCURSOR,
 FCA_ACTMAX,
};

///�R���g���[���[���[�N
typedef struct _FLD_COMACT_WORK{
	FIELD_CLACT	fcat;
	CATS_ACT_PTR	act[FCA_ACTMAX];
}FLD_COMACT_WORK;


/**
 *	@brief	�t�B�[���h�C�x���g�@���ʃZ���A�N�^�[������
 */
extern FLD_COMACT_WORK* FComAct_Init(int heapID);

/**
 *	@brief	�R���g���[���[�j��
 */
extern void FComAct_Delete(FLD_COMACT_WORK* wk);

/**
 *	@brief	�Z���A�N�^�[���C���R���g���[��
 */
extern void FActCom_Main(FLD_COMACT_WORK* wk);

/**
 *	@brief	�J�[�\���|�W�V�����Z�b�g
 *
 *	@param	px	�J�[�\��X���W
 *	@param	uy	�A�b�v�J�[�\��Y���W
 *	@param	dy	�_�E���J�[�\��Y���W
 */
extern void FComAct_CursorPosSet(FLD_COMACT_WORK* wk,s16 px,s16 uy,s16 dy);

/**
 *	@brief	�`���ԃR���g���[��
 *
 *	@param	vanish	TRUE:�`��,FALSE:�o�j�b�V��
 */
extern void FComAct_SetDrawFlg(FLD_COMACT_WORK* wk,u16 idx,BOOL draw);

/**
 *	@brief	�I�[�g�A�j����ԃR���g���[��
 *
 *	@param	anm	TRUE:�I�[�g�A�j��,FALSE:�I�[�g�A�j��Off
 */
extern void FComAct_SetAutoAnmFlg(FLD_COMACT_WORK* wk,u16 idx,BOOL anm);


#endif //__H_FLD_COMACT_H__
