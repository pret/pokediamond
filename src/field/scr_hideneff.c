//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		scr_hideneff.c
 *	@brief		�q�f���Z�G�t�F�N�g�X�N���v�g�Ǘ�
 *	@author		tomoya takahshi
 *	@data		2006.06.27
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "fieldsys.h"
#include "fieldmap_work.h"
#include "field_hideneff.h"

#define __FIELD_HIDENEFF_H_GLOBAL
#include "scr_hideneff.h"

//-----------------------------------------------------------------------------
/**
 *					�R�[�f�B���O�K��
 *		���֐���
 *				�P�����ڂ͑啶������ȍ~�͏������ɂ���
 *		���ϐ���
 *				�E�ϐ�����
 *						const�ɂ� c_ ��t����
 *						static�ɂ� s_ ��t����
 *						�|�C���^�ɂ� p_ ��t����
 *						�S�č��킳��� csp_ �ƂȂ�
 *				�E�O���[�o���ϐ�
 *						�P�����ڂ͑啶��
 *				�E�֐����ϐ�
 *						�������Ɓh�Q�h�Ɛ������g�p���� �֐��̈���������Ɠ���
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�q�f���Z�Ǘ����[�N
//=====================================
typedef struct {
	FLDMAPFUNC_WORK* p_work;
	u16* p_retwk;
	u32 seq;
	u32 effect_type;
} FLD_HIDENEFF_CONT;

typedef FLDMAPFUNC_WORK* (*pInitFunc)( FIELDSYS_WORK* fsys );
typedef void (*pDeleteFunc)( FLDMAPFUNC_WORK* p_demo );
typedef BOOL (*pEndCheckFunc)( FLDMAPFUNC_WORK* p_demo );


static const pInitFunc	HideInitFunc[ SCR_HIDENEFF_NUM ] = {
	FLD_HIDENEFF_Iaigiri_Start,
	FLD_HIDENEFF_Iwakudaki_Start,
	FLD_HIDENEFF_Iwakudaki_KuroganeL_Start,
};

static const pDeleteFunc	HideDeleteFunc[ SCR_HIDENEFF_NUM ] = {
	FLD_HIDENEFF_Iaigiri_End,
	FLD_HIDENEFF_Iwakudaki_End,
	FLD_HIDENEFF_Iwakudaki_End,
};

static const pEndCheckFunc	HideEndCheckFunc[ SCR_HIDENEFF_NUM ] = {
	FLD_HIDENEFF_Iaigiri_EndCheck,
	FLD_HIDENEFF_Iwakudaki_EndCheck,
	FLD_HIDENEFF_Iwakudaki_EndCheck,
};

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�q�f���Z�I���Ǘ��^�X�N
 */
//-----------------------------------------------------------------------------
static void ScrCmd_HidenEffContTask( TCB_PTR tcb, void* p_work )
{
	FLD_HIDENEFF_CONT* p_cont = p_work;

	switch( p_cont->seq ){
	case 0:
		if( HideEndCheckFunc[ p_cont->effect_type ]( p_cont->p_work ) == TRUE ){
			p_cont->seq ++;
		}
		break;
	
	case 1:
		HideDeleteFunc[ p_cont->effect_type ]( p_cont->p_work );
		*p_cont->p_retwk = 1;
		sys_FreeMemoryEz( p_cont );
		TCB_Delete( tcb );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�q�f���G�t�F�N�g�Ǘ��^�X�N����
 *
 *	@param	p_retwk			�����t���O�ݒ��
 *	@param	effect_type		�G�t�F�N�g�^�C�v
 *
 *	effect_type
 *		SCR_HIDENEFF_IAIGIRI
 *      SCR_HIDENEFF_IWAKUDAKI
 */
//-----------------------------------------------------------------------------
void ScrCmd_HidenEffContStart( FIELDSYS_WORK* fsys, u16* p_retwk, u32 effect_type, u32 heap )
{
	FLD_HIDENEFF_CONT* p_cont = sys_AllocMemory( heap, sizeof(FLD_HIDENEFF_CONT) );
	memset( p_cont, 0, sizeof(FLD_HIDENEFF_CONT) );
	p_cont->p_work = HideInitFunc[ effect_type ]( fsys );
	p_cont->p_retwk = p_retwk;
	p_cont->effect_type = effect_type;
	*p_retwk = 0;
	TCB_Add( ScrCmd_HidenEffContTask, p_cont, 0 );
}

