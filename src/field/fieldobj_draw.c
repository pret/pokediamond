//******************************************************************************
/**
 *
 * @file	fieldobj_draw.c
 * @brief	�t�B�[���hOBJ �`��n
 * @author	kagaya
 * @data	05.07.25
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"
#include "field_effect.h"

//==============================================================================
//	define
//==============================================================================
#ifdef PM_DEBUG
//#define DEBUG_DRAW
#endif

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void FldOBJSys_ArcHandleOpen( FIELD_OBJ_SYS_PTR fos );
static void FldOBJSys_ArcHandleClose( FIELD_OBJ_SYS_PTR fos );

static const OBJCODE_STATE * FldOBJ_OBJCodeDrawStateGet( int code );

#ifdef DEBUG_DRAW
static void DEBUG_Print( void );
#endif

//==============================================================================
//	�t�B�[���hOBJ�@�`��V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * FIELD OBJ �`��n������
 * @param	fos			FIELD_OBJ_SYS_PTR
 * @param	tex_max		�e�N�X�`����o�^�ł���ő�l��
 * @param	reg_tex_max	tex_max���A��ɏ풓����ő�l��
 * @param	tex_tbl		��ɏ풓����l�����܂Ƃ߂��e�[�u�� BABYBOY1��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_DrawInit( FIELD_OBJ_SYS_PTR fos,
		int tex_max, int reg_tex_max, const int *tex_tbl )
{
	int max,pri;
	FIELD_OBJ_BLACT_CONT *cont;
	
	GF_ASSERT( FieldOBJSys_StatusBit_Check(fos,FLDOBJSYS_STA_BIT_DRAW_INIT_COMP) == 0 &&
			"FieldOBJSys_DrawInit()���d�˂ČĂяo��Ă��܂�\n" );
	
	FldOBJSys_ArcHandleOpen( fos );
	
	max = FieldOBJSys_OBJMaxGet( fos );
	pri = FieldOBJSys_TCBStandardPriorityGet( fos ) - 1; //�Q�X�g�r���{�[�h�ǉ������͕W������
	cont = FieldOBJSys_BlActContGet( fos );
	
	FieldOBJ_BlActCont_Init( cont, fos, max, pri, tex_max, reg_tex_max, tex_tbl );
	
	{
		FIELD_OBJ_RENDER_CONT_PTR rdcont = FieldOBJ_RenderCont_Init( fos, HEAPID_FIELD );
		FieldOBJSys_RenderContSet( fos, rdcont );
		FieldOBJ_RenderCont_RegistInit( rdcont, DATA_FIELDOBJ_RenderOBJMax );
	}
	
	FieldOBJSys_StatusBit_ON( fos, FLDOBJSYS_STA_BIT_DRAW_INIT_COMP );
	
	OS_Printf( "�t�B�[���hOBJ �`�揈�������������܂���\n" );
	
#ifdef DEBUG_DRAW	
	DEBUG_Print();
#endif
}

//--------------------------------------------------------------
/**
 * FIELD OBJ �`�揈�����폜
 * @param	fos		FIELD_OBJ_SYS_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_DrawDelete( FIELD_OBJ_SYS_PTR fos )
{
	int ret;
	
	ret = FieldOBJSys_DrawInitCompCheck( fos );
	GF_ASSERT( ret == TRUE && "�t�B�[���hOBJ �`�揈���폜����d�ɌĂяo����Ă��܂�\n" );
	
	FieldOBJ_BlActCont_Delete( FieldOBJSys_BlActContGet(fos) );
	
	{
		FIELD_OBJ_RENDER_CONT_PTR rdcont = FieldOBJSys_RenderContGet( fos );
		FieldOBJ_RenderCont_Delete( rdcont );
		FieldOBJSys_RenderContSet( fos, NULL );
	}
	
	FieldOBJSys_StatusBit_OFF( fos, FLDOBJSYS_STA_BIT_DRAW_INIT_COMP );
	FldOBJSys_ArcHandleClose( fos );
	
	OS_Printf( "�t�B�[���hOBJ �`�揈�����폜���܂���\n" );
}

//==============================================================================
//	�A�[�J�C�u
//==============================================================================
//--------------------------------------------------------------
/**
 * �A�[�J�C�u�n���h���Z�b�g
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJSys_ArcHandleOpen( FIELD_OBJ_SYS_PTR fos )
{
	ARCHANDLE *handle = ArchiveDataHandleOpen( ARC_MMODEL, HEAPID_FIELD );
	FieldOBJSys_ArcHandleSet( fos, handle );
}

//--------------------------------------------------------------
/**
 * �A�[�J�C�u�n���h���N���[�Y
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJSys_ArcHandleClose( FIELD_OBJ_SYS_PTR fos )
{
	ARCHANDLE *handle = FieldOBJSys_ArcHandleGet( fos );
	ArchiveDataHandleClose( handle );
}

//==============================================================================
//	�t�B�[���hOBJ �`�揈��
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�`��
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_Draw( FIELD_OBJ_PTR fldobj )
{
	CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet( fldobj );
	
	if( FieldOBJSys_StatusBit_Check(fos,FLDOBJSYS_STA_BIT_DRAW_PROC_STOP) ){
		return;
	}
	
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP) == FALSE ){
		return;
	}
	
	if( FieldOBJ_MovePauseCheck(fldobj) == FALSE || FieldOBJ_StatusBitCheck_Acmd(fldobj) ){
		FieldOBJ_DrawProcCall( fldobj );
	}
}

//==============================================================================
//	�t�B�[���hOBJ �`��X�e�[�^�X
//==============================================================================
//--------------------------------------------------------------
/**
 * OBJ�R�[�h����`��X�e�[�^�X�擾
 * @param	fldobj	 FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
const OBJCODE_STATE * FieldOBJ_OBJCodeDrawStateGet( CONST_FIELD_OBJ_PTR fldobj )
{
	int code = FieldOBJ_OBJCodeGet( fldobj );
	const OBJCODE_STATE *state = FldOBJ_OBJCodeDrawStateGet( code );
	return( state );
}

//--------------------------------------------------------------
/**
 * DATA_FieldOBJCodeDrawStateTbl[]�擾
 * @param	code	HERO��
 * @retval	OBJCODE_STATE code�ɑΉ�����OBJCODE_STATE
 */
//--------------------------------------------------------------
static const OBJCODE_STATE * FldOBJ_OBJCodeDrawStateGet( int code )
{
	const OBJCODE_STATE *state = DATA_FieldOBJCodeDrawStateTbl;
	do{ if(state->code==code){return(state);} state++; }while( state->code != OBJCODEMAX );
	OS_Printf( "FldOBJ_OBJCodeDrawStateGet() OBJ CODE ERROR!! CODE = 0x%x\n", code );
	GF_ASSERT( 0 );
	return( NULL );
}

//==============================================================================
//	�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ �`��|�[�Y�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=�`��|�[�Y
 */
//--------------------------------------------------------------
int FieldOBJ_DrawPauseCheck( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_MovePauseCheck(fldobj) == TRUE ){
		if( FieldOBJ_StatusBitCheck_Acmd(fldobj) == FALSE ){
			return( TRUE );
		}
	}
	
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_PAUSE_ANM) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^���[�h
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	datID	�A�[�J�C�u�f�[�^ID
 * @param	fb		TRUE=sys_AllocMemory() FALSE=sys_AllocMemoryLo()
 * @retval	void*	�擾�����f�[�^
 */
//--------------------------------------------------------------
void * FieldOBJ_DrawArcDataAlloc( CONST_FIELD_OBJ_SYS_PTR fos, u32 datID, int fb )
{
	void *buf;
	ARCHANDLE *handle = FieldOBJSys_ArcHandleGet( fos );
	u32 size = ArchiveDataSizeGetByHandle( handle, datID );
	
	if( fb == TRUE ){
		buf = sys_AllocMemory( HEAPID_FIELD, size );
	}else{
		buf = sys_AllocMemoryLo( HEAPID_FIELD, size );
	}
	
	ArchiveDataLoadByHandle( handle, datID, buf );
	return( buf );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�@��{���W�{�I�t�Z�b�g���擾
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	vec		���W�i�[��
 * @retval	void*	�擾�����f�[�^
 */
//--------------------------------------------------------------
void FieldOBJ_DrawVecPosTotalGet( CONST_FIELD_OBJ_PTR fldobj, VecFx32 *vec )
{
	VecFx32 vec_pos,vec_offs,vec_out,vec_attr;
	
	FieldOBJ_VecPosGet( fldobj, &vec_pos );
	FieldOBJ_VecDrawOffsGet( fldobj, &vec_offs );
	FieldOBJ_VecDrawOffsOutSideGet( fldobj, &vec_out );
	FieldOBJ_VecAttrOffsGet( fldobj, &vec_attr );
	
	vec->x = vec_pos.x + vec_offs.x + vec_out.x + vec_attr.x;
	vec->y = vec_pos.y + vec_offs.y + vec_out.y + vec_attr.y;
	vec->z = vec_pos.z + vec_offs.z + vec_out.z + vec_attr.z;
}

//--------------------------------------------------------------
/**
 * �������Z�b�g����B�`��n�������čX�V
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		�����ADIR_UP��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DirDispDrawSet( FIELD_OBJ_PTR fldobj, int dir )
{
	FieldOBJ_DirDispCheckSet( fldobj, dir );
	
	if( FieldOBJ_StatusBitCheck_DrawProcInitComp(fldobj) == TRUE ){
		FieldOBJ_DrawProcCall( fldobj );
	}
}

//==============================================================================
//	�`�斳��
//==============================================================================
//--------------------------------------------------------------
/**
 * �`�斳���@������
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawNon_Init( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBitSet_Vanish( fldobj, TRUE );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_SHADOW_VANISH );
}

//--------------------------------------------------------------
/**
 * �`�斳���@�`��
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawNon_Draw( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * �`�斳���@�폜
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawNon_Delete( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * �`�斳���@�ޔ�
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=����������
 */
//--------------------------------------------------------------
void FieldOBJ_DrawNon_Push( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * �`�斳���@���A
 * �ޔ������������ɍĕ`��B
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=����������
 */
//--------------------------------------------------------------
void FieldOBJ_DrawNon_Pop( FIELD_OBJ_PTR fldobj )
{
}

//==============================================================================
//	debug
//==============================================================================
#ifdef DEBUG_DRAW
#include "fieldobj_test.c"

static void DEBUG_Print( void )
{
	u32 i;
	
	OS_Printf( "const OBJCODE_STATE DATA_FieldOBJCodeStateTbl[] =\n" );
	OS_Printf( "{\r\n" );
	
	for( i = 0; i <= KOIKING; i++ ){
		OS_Printf( " {" );
		OS_Printf( "%s,", DEBUGDATA_CharTbl[i] );
		OS_Printf( "FLDOBJ_DRAWTYPE_BLACT," );
		OS_Printf( "FLDOBJ_SHADOW_ON," );
		OS_Printf( "FLDOBJ_FOOTMARK_NORMAL," );
		OS_Printf( "FLDOBJ_REFLECT_BLACT," );
		OS_Printf( "0},\r\n" );
		{ u32 f; for( f = 0; f < 0xffffffff; f++ ){}; }
	}
	
	{
		int j;
		for( j = 0; j < 2; j++ ){};
	}
}
#endif	//DEBUG_DRAW
