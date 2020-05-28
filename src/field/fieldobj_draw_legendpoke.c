//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		fieldobj_draw_legendpoke.c
 *	@brief		�`���|�P�����`��֌W
 *	@author		tomoya takahashi
 *	@data		2006.04.18	
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include "common.h"
#include "fieldsys.h"

#define	__FIELDOBJ_DRAW_LEGENDPOKE_H_GLOBAL
#include "fieldobj_draw_legendpoke.h"

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
//	LEGENDPOKE_WORK�\����
//=====================================
typedef struct _LEGENDPOKE_WORK{
	BLACT_WORK_PTR act;
	FIELD_OBJ_BLACTANM_PUSH act_push;
};

#define LEGENDPOKE_WORK_SIZE (sizeof(LEGENDPOKE_WORK))


// �`���|�P�����C�A�G�AY�I�t�Z�b�g
#define LEGENDPOKE_Y_OFS	( FX32_CONST( 0 ) )

// �`���|�P�����@���C�A�C�n�C�@Y�I�t�Z�b�g
#define LEGENDPOKE_RE_A_HA_I_Y_OFS	( FX32_CONST( 24 ) )

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void FldObj_LegendInit( FIELD_OBJ_PTR fldobj );
static void FldObj_LegendDraw( FIELD_OBJ_PTR fldobj );
static void FldObj_LegendDrawVanish( FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act );
static void FldObj_LegendDelete( FIELD_OBJ_PTR fldobj );

//--------------------------------------------------------------
/**
 * LEGENDPOKE�@�������B
 * �`��ׂ̈̏��������s���B
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawLegend_Init( FIELD_OBJ_PTR fldobj )
{
	VecFx32 ofs;
	
	// ����������
	FldObj_LegendInit( fldobj );

	// Y�I�t�Z�b�g�ݒ�
	ofs.x = 0;
	ofs.y = LEGENDPOKE_Y_OFS;
	ofs.z = 0;
	FieldOBJ_VecDrawOffsOutSideSet( fldobj, &ofs );
}

//--------------------------------------------------------------
/**
 * LEGENDPOKE �`��B
 * �t�B�[���hOBJ����`��ɕK�v�ȏ����擾���A�`�悷��B
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawLegend_Draw( FIELD_OBJ_PTR fldobj )
{
	LEGENDPOKE_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;

	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){		//�ǉ���
		return;
	}
	
	if( act == NULL ){
		return;
	}

	FldObj_LegendDraw( fldobj );

	// �A�j���[�V����
	BLACT_AnmFrameChg( act, FX32_ONE );		
}

//--------------------------------------------------------------
/**
 * LEGENDPOKE �폜�֐��B
 * �`��Ŏg�p�������m���폜
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawLegend_Delete( FIELD_OBJ_PTR fldobj )
{
	// �j������
	FldObj_LegendDelete( fldobj );
}

//----------------------------------------------------------------------------
/**
 *	@brief	LEGENDPOKE �ޔ�
 *	@param	fldobj ���[�N
 */
//-----------------------------------------------------------------------------
void FieldOBJ_DrawLegend_Push( FIELD_OBJ_PTR fldobj )
{
	LEGENDPOKE_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( work->act != NULL ){
		FieldOBJ_BlActAnmPush( work->act, &work->act_push );
	}
	
	FieldOBJ_BlActDelete( fldobj, &work->act );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_DRAW_PUSH );
}

//----------------------------------------------------------------------------
/**
 *	@brief	LEGENDPOKE ���A
 *	@param	fldobj	���[�N
 */
//-----------------------------------------------------------------------------
void FieldOBJ_DrawLegend_Pop( FIELD_OBJ_PTR fldobj )
{
	LEGENDPOKE_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){
		return;
	}
	
	if( work->act == NULL ){
		FieldOBJ_BlActAddRegularGuest( fldobj, &work->act );
	}
	
	if( work->act != NULL ){
		FieldOBJ_BlActAnmPop( work->act, &work->act_push );
		FieldOBJ_BlActPosSet( fldobj, work->act );
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_DRAW_PUSH );
	}
}

//--------------------------------------------------------------
/**
 * LEGENDPOKE�@�������B		���C�@�A�C�@�n�C
 * �`��ׂ̈̏��������s���B
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawReiAiHai_Init( FIELD_OBJ_PTR fldobj )
{
	VecFx32 ofs;
	
	// ����������
	FldObj_LegendInit( fldobj );

	// Y�I�t�Z�b�g�ݒ�
	ofs.x = 0;
	ofs.y = LEGENDPOKE_RE_A_HA_I_Y_OFS;
	ofs.z = 0;
	FieldOBJ_VecDrawOffsOutSideSet( fldobj, &ofs );
}

//--------------------------------------------------------------
/**
 * LEGENDPOKE �`��B		���C�@�A�C�@�n�C
 * �t�B�[���hOBJ����`��ɕK�v�ȏ����擾���A�`�悷��B
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawReiAiHai_Draw( FIELD_OBJ_PTR fldobj )
{
	LEGENDPOKE_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;

	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){		//�ǉ���
		return;
	}
	
	if( act == NULL ){
		return;
	}

	FldObj_LegendDraw( fldobj );
}

//--------------------------------------------------------------
/**
 * LEGENDPOKE �폜�֐��B
 * �`��Ŏg�p�������m���폜
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawReiAiHai_Delete( FIELD_OBJ_PTR fldobj )
{
	FldObj_LegendDelete( fldobj );
}



//----------------------------------------------------------------------------
/**
 *	@brief	�`���|�P�������[�N�̎擾
 *
 *	@param	fldobj	�t�B�[���h�I�u�W�F���[�N
 *
 *	@return	�`���|�P�������[�N�|�C���^
 */
//-----------------------------------------------------------------------------
LEGENDPOKE_WORK* FieldOBJ_DrawLegend_GetWrokPtr( FIELD_OBJ_PTR fldobj )
{
	return FieldOBJ_DrawProcWorkGet( fldobj );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`���|�P�����̃r���{�[�h�擾
 *
 *	@param	fldobj	�t�B�[���h�I�u�W�F���[�N
 *
 *	@return	BLACT_WORK_PTR
 */
//-----------------------------------------------------------------------------
BLACT_WORK_PTR FieldOBJ_DrawLegend_GetBlActWorkPtr( FIELD_OBJ_PTR fldobj )
{
	LEGENDPOKE_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	return( FieldOBJ_DrawLegend_GetBlactPtr(work) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�r���{�[�h�A�N�^�[���[�N�擾�֐�
 *
 *	@param	�`���|�P�������[�N
 *
 *	@return	���[�N�|�C���^
 */
//-----------------------------------------------------------------------------
BLACT_WORK_PTR FieldOBJ_DrawLegend_GetBlactPtr( LEGENDPOKE_WORK* p_obj )
{
	return p_obj->act;
}


//-----------------------------------------------------------------------------
/**
 *		���[�J���֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�`���|�P�����@����������
 *
 *	@param	fldobj 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldObj_LegendInit( FIELD_OBJ_PTR fldobj )
{
	LEGENDPOKE_WORK *work;
	// ���[�N�쐬
	work = FieldOBJ_DrawProcWorkInit( fldobj, LEGENDPOKE_WORK_SIZE );

	// �A�N�^�[�o�^
	FieldOBJ_BlActAddRegularGuest( fldobj, &work->act );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`���|�P�����`�揈��
 *
 *	@param	fldobj	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldObj_LegendDraw( FIELD_OBJ_PTR fldobj )
{
	LEGENDPOKE_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;
	
	FieldOBJ_BlActPosSet( fldobj, act );
	FldObj_LegendDrawVanish( fldobj, act );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`���|�P�����\���E��\���ݒ�
 *
 *	@param	fldobj	�t�B�[���h�I�u�W�F
 *	@param	act		�A�N�^�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldObj_LegendDrawVanish( FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act )
{
	int vanish = TRUE;
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_VANISH) == TRUE ){
		vanish = FALSE;
	}
	
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_HEIGHT_GET_ERROR) == TRUE ){
		if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_HEIGHT_VANISH_OFF) == FALSE){
			vanish = FALSE;
		}
	}
	BLACT_ObjDrawFlagSet( act, vanish );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�`���|�P�����j������
 *
 *	@param	fldobj	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldObj_LegendDelete( FIELD_OBJ_PTR fldobj )
{
	LEGENDPOKE_WORK *work;
	
	//�A�N�^�[�j������
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	FieldOBJ_BlActDelete( fldobj, &work->act );
}

