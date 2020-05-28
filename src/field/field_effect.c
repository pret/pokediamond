//******************************************************************************
/**
 * 
 * @file	field_effect.c
 * @brief	�t�B�[���h�G�t�F�N�g
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"

//==============================================================================
//	define
//==============================================================================
//debug
#ifdef PM_DEBUG
#define DEBUG_FE_EOA_USE_CHECK			//�L����EOA�ǉ��Ď�
#endif

///�r���{�[�h�e�N�X�`���]��TCB�v���C�I���e�B
#define TCBPRI_VINTR_BLACT_TEX_LOAD (0xff)
#define TCBPRI_VWAIT_BLACT_TEX_LOAD (0xff)

//�V�X�e���S�̂̏������j���^�X�N
#define FLD_3DOBJ_TEXTRANS_TCB_PRI	( 1024 )

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	�\���̖���`
//--------------------------------------------------------------
///FE_SUBPROC_REGDATA
typedef struct _TAG_SUBPROC_REGDATA SUBPROC_REGDATA;
///FE_BLACT
typedef struct _TAG_FE_BLACT FE_BLACT;
///FE_BLACT_H_ID
typedef struct _TAG_FE_BLACT_H_ID FE_BLACT_H_ID;

//--------------------------------------------------------------
///	FE_SYS�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_SYS
{
	u32 heap_id;								///<�q�[�vID
	u32 fe_heap_id;								///<�t�B�[���h�G�t�F�N�g��p�q�[�vID
	u32 reg_max;								///<�G�t�F�N�g�o�^�ő吔
	u32 eoa_max;								///<EOA�ő吔
	u32 blact_max;								///<�r���{�[�h�A�N�^�[�ő吔
	
	LRES *lres;									///<LRES *
	FIELDSYS_WORK *fsys;						///<FIELDSYS_WORK *
	SUBPROC_REGDATA *subproc_regdata;			///<FE_SUBPROC_REGDATA
	
	ARCHANDLE *arc_handle;						///<�t�B�[���h�G�t�F�N�g�A�[�J�C�u�f�[�^�n���h��
	EOA_SYS_PTR eoa_sys;						///<EOA_SYS_PTR
	FE_BLACT *fe_blact;							///<FE_BLACT *
}FE_SYS;

#define FE_SYS_SIZE (sizeof(FE_SYS))			///<FE_SYS�T�C�Y

//--------------------------------------------------------------
///	SUBPROC_REGDATA�\����
//--------------------------------------------------------------
typedef struct _TAG_SUBPROC_REGDATA
{
	u32 id;						///<�T�u�v���Z�X�o�^ID FE_PROC_MAX=����
	void *subproc_work;			///<�T�u�v���Z�X�Ŏg�p���郏�[�N* NULL=����
};

#define SUBPROC_REGDATA_SIZE (sizeof(SUBPROC_REGDATA))	///<SUBPROC_REGDATA SIZE

//--------------------------------------------------------------
///	FE_BLACT�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_BLACT
{
	u32 gp_heap_id;								///<�O���t�B�b�N�p�q�[�v�̈���쐬����q�[�vID
	u16 blact_max;										///<�r���{�[�h�A�N�^�[�ő吔
	u16 mdl_max;										///<���f�����O�f�[�^�ő吔
	u16 anm_max;										///<�A�j���f�[�^�ő吔
	u16 tex_max;										///<�e�N�X�`���f�[�^�ő吔
	BLACT_SET_PTR set_ptr;								///<BLACT_SET_PTR
	LRES *lres_mdl;										///<���f���pLRES *
	LRES *lres_anm;										///<�A�j���pLRES *
	TEXRES_MANAGER_PTR resm_tex;						///<TEXRES_MANAGER_PTR
	FE_BLACT_H_ID *head_manage;							///<FE_BLACT_H_ID
	BLACT_HEADER *head_tbl;								///<BLACT_HEADER
};

#define FE_BLACT_SIZE (sizeof(FE_BLACT))				///<FE_BLACT SIZE

//--------------------------------------------------------------
///	FE_BLACT_HEADER_ID�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_BLACT_H_ID
{
	u32 id;														///<�o�^ID
	BLACT_HEADER *head;											///<�w�b�_�[*
};

#define FE_BLACT_H_ID_SIZE (sizeof(FE_BLACT_H_ID))				///<FE_BLACT_H_ID SIZE

//--------------------------------------------------------------
///	FE_VINTR_TEX_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	u32 trans_end;												///<VRAM�]���I���t���O
	u32 id;														///<�o�^����ID
	TEXRES_MANAGER_PTR resm_tex;								///<�]������TEXRES_MANAGER_PTR
}FE_VINTR_TEX_WORK;

#define FE_VINTR_TEX_WORK_SIZE (sizeof(FE_VINTR_TEX_WORK))

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static u32 fe_HeapIDGet( const FE_SYS *fes );

static void fe_ArcHandleOpen( FE_SYS *fes );
static void fe_ArcHandleClose( FE_SYS *fes );

static void fe_SubProcRegDataInitAll( FE_SYS *fes );
static void fe_SubProcRegDataIDSet( FE_SYS *fes, u32 id );
static void fe_SubProcRegDataDelete( FE_SYS *fes, SUBPROC_REGDATA *subproc );
static void fe_SubProcRegDataIDDelete( FE_SYS *fes, u32 id );
static void fe_SubProcRegDataDeleteAll( FE_SYS *fes );
static SUBPROC_REGDATA * fe_SubProcRegDataSpaceSearch( FE_SYS *fes );
static SUBPROC_REGDATA * fe_SubProcRegDataIDSearch( FE_SYS *fes, u32 id );
static void SubProcRegDataInit( SUBPROC_REGDATA *subproc );
static void SubProcRegDataSet( SUBPROC_REGDATA *subproc, u32 id, void *work );
static int SubProcRegDataSpaceCheck( const SUBPROC_REGDATA *subproc );
static const FE_SUBPROC_DATA * SubProcIDDataGet( u32 id );

static void fe_EoaInit( FE_SYS *fes );
static void fe_EoaDelete( FE_SYS *fes );
static void fe_EoaDraw( FE_SYS *fes );

static void fe_BlActInit(
		FE_SYS *fes, u32 gp_heap_id,  u32 act_max,
		u32 mdl_max, u32 anm_max, u32 tex_max,
		u32 mdl_size, u32 anm_size, u32 tex_size );
static void fe_BlActDelete( FE_SYS *fes );

static void fe_BlActHeaderManageInit( FE_SYS *fes, FE_BLACT *fba, u32 max );
static void fe_BlActHeaderManageDelete( FE_BLACT *fba );
static BLACT_HEADER * fe_BlActHeaderManageGet( FE_BLACT *fba, u32 id );
static void fe_BlActHeaderManageFree( FE_BLACT *fba, u32 id );
static BLACT_HEADER * fe_BlActHeaderManageAdd( FE_BLACT *fba, u32 id,
	void *mdl, TEXANM_DATATBL *anm, void *tex, TEXRES_OBJ_PTR tex_key,
	const BLACT_ANIME_TBL *anm_tbl );

static void fe_VIntrWaitTexLoadSet( FE_SYS *fes, u32 id, TEXRES_MANAGER_PTR resm_tex );
static void fe_VIntrTCB_TexLoad( TCB_PTR tcb, void *wk );
static void fe_VWaitTCB_TexLoad( TCB_PTR tcb, void *wk );

//debug
#ifdef DEBUG_FE_EOA_USE_CHECK
static void DEBUG_FeEoaUseCheck_Init( FE_SYS *fes );
static void DEBUG_FeEoaUseCheck_Add( EOA_PTR eoa, const EOA_H_NPP *head );
static void DEBUG_FeEoaUseCheck_Del( EOA_PTR eoa );
#endif

//==============================================================================
//	�t�B�[���h�G�t�F�N�g�@�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g�@�V�X�e��������
 * @param	fsys		FIELDSYS_WORK *
 * @param	reg_max		�o�^����G�t�F�N�g�ő吔
 * @param	heap_id		���[�N�Ɏg�p����q�[�vID
 * @param	worksize	�t�B�[���h�G�t�F�N�g�Ŋm�ۂ��郏�[�N�̈�ő�T�C�Y
 * @retval	FE_SYS_PTR	FE_SYS_PTR
 * 
 * worksize�͓o�^�����G�t�F�N�g�AEOA�A�r���{�[�h���A
 * �t�B�[���h�G�t�F�N�g�S�̂Ŏg�p�����ʂ��l�����Ă�������
 */
//--------------------------------------------------------------
FE_SYS * FE_Init( FIELDSYS_WORK *fsys, u32 reg_max, u32 heap_id, u32 worksize )
{
	LRES *lres;
	FE_SYS *fes;
	
	lres = LRes_Init( heap_id, HEAPID_FIELD_FE, worksize, 0 );
	
	fes = LRes_Alloc( lres, FE_SYS_SIZE, ALLOC_FR );
	memset( fes, 0, FE_SYS_SIZE );
	
	fes->heap_id = heap_id;
	fes->fe_heap_id = HEAPID_FIELD_FE;
	fes->reg_max = reg_max;
	fes->lres = lres;
	fes->fsys = fsys;
	
	fes->subproc_regdata = LRes_Alloc( lres, SUBPROC_REGDATA_SIZE * reg_max, ALLOC_FR );
	fe_SubProcRegDataInitAll( fes );
	fe_ArcHandleOpen( fes );
	
#ifdef DEBUG_FE_EOA_USE_CHECK
	DEBUG_FeEoaUseCheck_Init( fes );
#endif
	
	return( fes );
}

//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g �p�����^������ EOA
 * @param	fes			FE_SYS_PTR
 * @param	eoa_max		EOA�ő吔
 * @param	blact_max	�r���{�[�h�A�N�^�[�ő吔
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_ParamInit_EOA( FE_SYS *fes, u32 eoa_max )
{
	fes->eoa_max = eoa_max;
	fe_EoaInit( fes );
}

//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g �p�����^������ �r���{�[�h�A�N�^�[
 * @param	fes			FE_SYS_PTR
 * @param	gp_heap_id		�O���t�B�b�N�p�̈���m�ۂ���q�[�v�̈���쐬����q�[�vID
 * @param	act_max			�r���{�[�h�A�N�^�[�ő吔
 * @param	mdl_max			���f�����O�f�[�^�ő吔
 * @param	anm_max			�A�j���[�V�����f�[�^�ő吔
 * @param	tex_max			�e�N�X�`���f�[�^�ő吔
 * @param	mdl_size		���f�����O�f�[�^�p�Ɋm�ۂ���̈�T�C�Y
 * @param	anm_size		�A�j���f�[�^�p�Ɋm�ۂ���̈�T�C�Y
 * @param	tex_size		�e�N�X�`���f�[�^�p�Ɋm�ۂ���̈�T�C�Y
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_ParamInit_BlAct(
		FE_SYS *fes, u32 gp_heap_id,  u32 act_max,
		u32 mdl_max, u32 anm_max, u32 tex_max,
		u32 mdl_size, u32 anm_size, u32 tex_size )
{
	fe_BlActInit( fes, gp_heap_id, act_max,
		mdl_max, anm_max, tex_max,
		mdl_size, anm_size, tex_size );
}

//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g�@�G�t�F�N�g�o�^
 * @param	fes		FE_SYS *
 * @param	id		�o�^����G�t�F�N�gID FE_FLD_SHADOW��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_EffectRegist( FE_SYS *fes, u32 id )
{
	if( fe_SubProcRegDataIDSearch(fes,id) != NULL ){
		GF_ASSERT( 0 && "FE_EffectRegist()���ɂ���ID�͓o�^�ς݂ł�" );
		return;
	}
	
	fe_SubProcRegDataIDSet( fes, id );
}

//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g�@�G�t�F�N�g�����o�^
 * @param	fes		FE_SYS *
 * @param	id_tbl	�o�^����G�t�F�N�gID���܂Ƃ߂�u32�^�̔z��B�I�[��FE_PROC_MAX
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_EffectRegistMore( FE_SYS *fes, const u32 *id_tbl )
{
	while( (*id_tbl) != FE_PROC_MAX ){
		FE_EffectRegist( fes, (*id_tbl) );
		id_tbl++;
	}
}

//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g�@�G�t�F�N�g�o�^�`�F�b�N
 * @param	fes		FE_SYS *
 * @param	id		�o�^�`�F�b�N����G�t�F�N�gID FE_FLD_SHADOW��
 * @retval	int		TRUE=�o�^�ς� FALSE=�o�^����Ă��Ȃ�
 */
//--------------------------------------------------------------
int FE_EffectRegistCheck( FE_SYS *fes, u32 id )
{
	if( fe_SubProcRegDataIDSearch(fes,id) == NULL ){
		return( FALSE );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g�@�G�t�F�N�g�폜
 * @param	fes		FE_SYS *
 * @param	id		�폜����G�t�F�N�gID FE_FLD_SHADOW��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_EffectDelete( FE_SYS *fes, u32 id )
{
	fe_SubProcRegDataIDDelete( fes, id );
}

//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g�@�`��
 * @param	fes	FE_SYS *
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Draw( FE_SYS *fes )
{
	fe_EoaDraw( fes );
}

//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g�V�X�e���폜
 * @param	fes			FE_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Delete( FE_SYS *fes )
{
	LRES *lres = fes->lres;
	
	fe_EoaDelete( fes );
	fe_SubProcRegDataDeleteAll( fes );
	fe_BlActDelete( fes );
	fe_ArcHandleClose( fes );
	
	LRes_Free( lres, fes->subproc_regdata );
	LRes_Free( lres, fes );
	LRes_Delete( lres );
}

//==============================================================================
//	�t�B�[���h�G�t�F�N�g�@�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g��p�̈悩�烁�����m��
 * @param	fes		FE_SYS_PTR
 * @param	size	�m�ۂ���T�C�Y
 * @param	type	ALLOCTYPE
 * @retval	void*	�m�ۂ����T�C�Y�@NULL=�m�ۏo���Ȃ�(ASSERT�B
 */
//--------------------------------------------------------------
void * FE_AllocMemory( const FE_SYS *fes, u32 size, ALLOCTYPE type )
{
	void *alloc = LRes_Alloc( fes->lres, size, type );
	return( alloc );
}

//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g��p�̈悩�烁�����m�ہB�m�ۂ����̈�͎w��l�ŃN���A�����B
 * @param	fes		FE_SYS_PTR
 * @param	size	�m�ۂ���T�C�Y�B
 * @param	type	ALLOCTYPE
 * @param	clear	���ߐs�����l
 * @retval	void*	�m�ۂ����T�C�Y�@NULL=�m�ۏo���Ȃ�(ASSERT�B
 */
//--------------------------------------------------------------
void * FE_AllocClearMemory( const FE_SYS *fes, u32 size, ALLOCTYPE type, u32 clear )
{
	void *alloc = FE_AllocMemory( fes, size, type );
	memset( alloc, clear, size );
	return( alloc );
}

//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g��p�̈悩��擾�������������J��
 * @param	alloc	FE_AllocMemory()�Ŋm�ۂ���������
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_FreeMemory( void *alloc )
{
	sys_FreeMemoryEz( alloc );
}

//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g�@�G�t�F�N�g�Ŏg�p���Ă��郏�[�N���擾
 * @param	fes		FE_SYS *
 * @param	id		�擾����G�t�F�N�gID FE_FLD_SHADOW��
 * @retval	void*	id�Ŏg�p���Ă��郏�[�N�@NULL=�o�^����Ă��Ȃ� NULL���AASSERT()
 */
//--------------------------------------------------------------
void * FE_EffectWorkGet( FE_SYS *fes, u32 id )
{
	SUBPROC_REGDATA *subproc = fe_SubProcRegDataIDSearch( fes, id );
	
	if( subproc == NULL ){
		GF_ASSERT( 0 && "FE_EffectWorkGet()����ID�͓o�^����Ă��܂���" );
		return( NULL );
	}
	
	return( subproc->subproc_work );
}

//--------------------------------------------------------------
/**
 * FIELDSYS_WORK�擾
 * @param	fes				FE_SYS_PTR
 * @retval	FIELDSYS_WORK	FIELDSYS_WORK *
 */
//--------------------------------------------------------------
FIELDSYS_WORK * FE_FieldSysWorkGet( const FE_SYS *fes )
{
	return( fes->fsys );
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_PTR����FE_SYS *�擾
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	FE_SYS*		FE_SYS *
 */
//--------------------------------------------------------------
FE_SYS * FE_FieldOBJ_FE_SYS_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
	return( (FE_SYS *)fsys->fes );
}

//==============================================================================
//	�t�B�[���h�G�t�F�N�g�@�p�[�c�@���[�J��
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g��p�q�[�vID�擾
 * @param	fes		FE_SYS_PTR
 * @retval	u32		�q�[�vID
 */
//--------------------------------------------------------------
static u32 fe_HeapIDGet( const FE_SYS *fes )
{
	return( fes->fe_heap_id );
}

//==============================================================================
//	�t�B�[���h�G�t�F�N�g�@�A�[�J�C�u�f�[�^
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g�p�A�[�J�C�u�f�[�^�I�[�v��
 * @param	fes		FE_SYS *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_ArcHandleOpen( FE_SYS *fes )
{
	fes->arc_handle = ArchiveDataHandleOpen( ARC_FLDEFF, fe_HeapIDGet(fes) );
}

//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g�p�A�[�J�C�u�f�[�^�N���[�Y
 * @param	fes		FE_SYS *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_ArcHandleClose( FE_SYS *fes )
{
	ArchiveDataHandleClose( fes->arc_handle );
}

//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g�p�A�[�J�C�u�f�[�^�̃T�C�Y���擾
 * @param	fes		FE_SYS *
 * @param	datid	�f�[�^�C���f�b�N�XID
 * @retval	u32		datid�f�[�^�T�C�Y
 */
//--------------------------------------------------------------
u32 FE_ArcDataSizeGet( FE_SYS *fes, u32 datid )
{
	u32 size = ArchiveDataSizeGetByHandle( fes->arc_handle, datid );
	return( size );
}

//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g�p�A�[�J�C�u�f�[�^���擾
 * @param	fes		FE_SYS *
 * @param	datid	�f�[�^�C���f�b�N�XID
 * @param	buf		datid���[�h��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_ArcDataLoad( FE_SYS *fes, u32 datid, void *buf )
{
	ArchiveDataLoadByHandle( fes->arc_handle, datid, buf );
}

//--------------------------------------------------------------
/**
 * �t�B�[���h�G�t�F�N�g�p�A�[�J�C�u�f�[�^��W�J��̗̈���m�ۂ��A�擾�B
 * �̈�̓t�B�[���h�G�t�F�N�g�p�q�[�v�̈�B�J����FE_FreeMemory()
 * @param	fes		FE_SYS *
 * @param	datid	�f�[�^�C���f�b�N�XID
 * @retval	void*	�A�[�J�C�u�f�[�^��ǂݍ��񂾗̈� *
 */
//--------------------------------------------------------------
void * FE_ArcDataLoadAlloc( FE_SYS *fes, u32 datid, ALLOCTYPE type )
{
	void *alloc = LResUtil_AllocArcLoad( fes->lres, fes->arc_handle, datid, type );
	return( alloc );
}

//==============================================================================
//	SUBPROC_REGDATA�֘A
//==============================================================================
//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA �S������
 * @param	fes		FE_SYS
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_SubProcRegDataInitAll( FE_SYS *fes )
{
	u32 max = fes->reg_max;
	SUBPROC_REGDATA *subproc = fes->subproc_regdata;
	
	while( max ){
		SubProcRegDataInit( subproc );
		subproc++; max--;
	}
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA �w��ID�̏������֐��Ăяo���A�o�^
 * @param	fes		FE_SYS
 * @param	id		FE_FLD_SHADOW��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_SubProcRegDataIDSet( FE_SYS *fes, u32 id )
{
	const FE_SUBPROC_DATA *procdata = SubProcIDDataGet( id );
	void *work;
	SUBPROC_REGDATA *subproc;

	OS_Printf("FE_SYS *fes = %08x, procdata = %08x, proc_init = %08x\n", fes, procdata, procdata->proc_init);

	work = procdata->proc_init( fes );
	subproc = fe_SubProcRegDataSpaceSearch( fes );
	SubProcRegDataSet( subproc, id, work );
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA �w��SUBPROC_REGDATA�̍폜�֐��Ăяo���A�폜
 * @param	fes		FE_SYS
 * @param	subproc	SUBPROC_REGDATA *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_SubProcRegDataDelete( FE_SYS *fes, SUBPROC_REGDATA *subproc )
{
	const FE_SUBPROC_DATA *procdata = SubProcIDDataGet( subproc->id );
	procdata->proc_del( subproc->subproc_work );
	SubProcRegDataInit( subproc );
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA �w��ID�̍폜�֐��Ăяo���A�폜
 * @param	fes		FE_SYS
 * @param	id		FE_FLD_SHADOW��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_SubProcRegDataIDDelete( FE_SYS *fes, u32 id )
{
	SUBPROC_REGDATA *subproc = fe_SubProcRegDataIDSearch( fes, id );
	GF_ASSERT( subproc != NULL && "fe_SubProcRegDataIDDelete()ID��v����\n" );
	fe_SubProcRegDataDelete( fes, subproc );
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA �o�^����Ă���ID��S�č폜
 * @param	fes		FE_SYS
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_SubProcRegDataDeleteAll( FE_SYS *fes )
{
	u32 max = fes->reg_max;
	SUBPROC_REGDATA *subproc = fes->subproc_regdata;
	
	while( max ){
		if( SubProcRegDataSpaceCheck(subproc) == FALSE ){
			fe_SubProcRegDataDelete( fes, subproc );
		}
		
		subproc++; max--;
	}
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA �󂫒T��
 * @param	fes		FE_SYS
 * @retval	SUBPROC_REGDATA* �󂢂Ă���SUBPROC_REGDATA*�@NULL=�󂫖���
 */
//--------------------------------------------------------------
static SUBPROC_REGDATA * fe_SubProcRegDataSpaceSearch( FE_SYS *fes )
{
	u32 max = fes->reg_max;
	SUBPROC_REGDATA *subproc = fes->subproc_regdata;
	
	while( max ){
		if( SubProcRegDataSpaceCheck(subproc) == TRUE ){
			return( subproc );
		}
		
		subproc++; max--;
	}
	
	GF_ASSERT( 0 && "fe_SubProcRegDataSpaceSearch()�󂫖���" );
	return( NULL );
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA ��vID�T��
 * @param	fes		FE_SYS
 * @param	id		����ID FE_FLD_SHADOW��
 * @retval	SUBPROC_REGDATA* �󂢂Ă���SUBPROC_REGDATA*�@NULL=�󂫖���
 */
//--------------------------------------------------------------
static SUBPROC_REGDATA * fe_SubProcRegDataIDSearch( FE_SYS *fes, u32 id )
{
	u32 max = fes->reg_max;
	SUBPROC_REGDATA *subproc = fes->subproc_regdata;
	
	while( max ){
		if( subproc->id  == id ){
			return( subproc );
		}
		
		subproc++; max--;
	}
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA ������
 * @param	subproc	SUBPROC_REGDATA
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SubProcRegDataInit( SUBPROC_REGDATA *subproc )
{
	subproc->id = FE_PROC_MAX;
	subproc->subproc_work = NULL;
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA �Z�b�g
 * @param	subproc	SUBPROC_REGDATA
 * @param	id		FE_FLD_SHADOW��
 * @param	work	�w��id�֐��Ŏg�p���郏�[�N
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SubProcRegDataSet( SUBPROC_REGDATA *subproc, u32 id, void *work )
{
	subproc->id = id;
	subproc->subproc_work = work;
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA�@�󂫃`�F�b�N
 * @param	subproc	SUBPROC_REGDATA
 * @retval	int	TRUE=�󂫁@FALSE=�󂢂Ă��Ȃ�
 */
//--------------------------------------------------------------
static int SubProcRegDataSpaceCheck( const SUBPROC_REGDATA *subproc )
{
	if( subproc->id == FE_PROC_MAX ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �G�t�F�N�gID -> FE_SUBPROC_DATA�擾
 * @param	id		FE_FLD_SHADOW��
 * @retval	FE_SUBPROC_DATA FE_SUBPROC_DATA *
 */
//--------------------------------------------------------------
static const FE_SUBPROC_DATA * SubProcIDDataGet( u32 id )
{
	const FE_SUBPROC_DATA *tbl = DATA_FE_SubProcDataTbl;
	
	while( tbl->id != FE_PROC_MAX ){
		if( tbl->id == id ){
			return( tbl );
		}
		
		tbl++;
	}
	
	GF_ASSERT( 0 && "SubProcDataGet()�o�^����Ă��Ȃ�ID�ł�" );
	return( NULL );
}

//==============================================================================
//	�t�B�[���h�G�t�F�N�g�@EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA������
 * @param	fes		FE_SYS
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_EoaInit( FE_SYS *fes )
{
	fes->eoa_sys = EOA_SysInit( fes->fe_heap_id, fes->eoa_max );
}

//--------------------------------------------------------------
/**
 * EOA�폜
 * @param	fes		FE_SYS
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_EoaDelete( FE_SYS *fes )
{
	if( fes->eoa_sys != NULL ){
		EOA_SysDeleteAll( fes->eoa_sys );
		fes->eoa_sys = NULL;
	}
}

//--------------------------------------------------------------
/**
 * EOA�`��
 * @param	fes	FE_SYS *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_EoaDraw( FE_SYS *fes )
{
	if( fes->eoa_sys != NULL ){
		EOA_SysDraw( fes->eoa_sys );
	}
}

//==============================================================================
//	�t�B�[���h�G�t�F�N�g�@EOA�@�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA�ǉ��@���̂�EOA_Add_NPP()
 * @param	fes		FE_SYS_PTR
 * @param	EOA_H_NPP	�ǉ�������񂪓Z�߂�ꂽEOA_H_NPP
 * @param	mtx			�����ʒu
 * @param	prm			�ǉ�����EOA�֎w�肷��p�����^
 * @param	ptr			�ǉ�����EOA�֎w�肷��|�C���^
 * @param	pri			�ǉ�����EOA�̓���v���C�I���e�B
 * @retval	EOA_PTR		�ǉ����ꂽEOA_PTR �ǉ����s���@�����I��
 */
//--------------------------------------------------------------
EOA_PTR FE_EoaAddNpp( const FE_SYS *fes, const EOA_H_NPP *head,
		const VecFx32 *mtx, int prm, const void *ptr, int pri )
{
	EOA_PTR eoa;
	EOA_SYS_PTR es;
	
	es = fes->eoa_sys;
	eoa = EOA_Add_NPP( es, head, mtx, prm, ptr, pri );
	
	GF_ASSERT( eoa != NULL && "FE_EoaAddNpp() EOA�̒ǉ��Ɏ��s�c" );
	
#ifdef DEBUG_FE_EOA_USE_CHECK
	DEBUG_FeEoaUseCheck_Add( eoa, head );
#endif
	
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA�폜�@���̂�EOA_Delete()
 * ���t�B�[���h�G�t�F�N�g�Ŏg�p���Ă���EOA�c���ׁ̈A�폜�̍ہA��������g��
 * @param	eoa		EOA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_EoaDelete( EOA_PTR eoa )
{
#ifdef DEBUG_FE_EOA_USE_CHECK
	DEBUG_FeEoaUseCheck_Del( eoa );
#endif
	
	EOA_Delete( eoa );
}

//==============================================================================
//	�t�B�[���h�G�t�F�N�g�@�r���{�[�h�A�N�^�[
//==============================================================================
//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�������@���C��
 * @param	fes				FE_SYS *
 * @param	gp_heap_id		�O���t�B�b�N�p�̈���m�ۂ���q�[�v�̈���쐬����q�[�vID
 * @param	act_max			�r���{�[�h�A�N�^�[�ő吔
 * @param	mdl_max			���f�����O�f�[�^�ő吔
 * @param	anm_max			�A�j���[�V�����f�[�^�ő吔
 * @param	tex_max			�e�N�X�`���f�[�^�ő吔
 * @param	mdl_size		���f�����O�f�[�^�p�Ɋm�ۂ���̈�T�C�Y
 * @param	anm_size		�A�j���f�[�^�p�Ɋm�ۂ���̈�T�C�Y
 * @param	tex_size		�e�N�X�`���f�[�^�p�Ɋm�ۂ���̈�T�C�Y
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_BlActInit(
		FE_SYS *fes, u32 gp_heap_id,  u32 act_max,
		u32 mdl_max, u32 anm_max, u32 tex_max,
		u32 mdl_size, u32 anm_size, u32 tex_size )
{
	FE_BLACT *fba;
	BLACT_SETDATA set;
	
	fba = FE_AllocClearMemory( fes, FE_BLACT_SIZE, ALLOC_FR, 0 );
	fes->fe_blact = fba;
	
	fba->gp_heap_id = gp_heap_id;
	fba->blact_max = act_max;
	fba->mdl_max = mdl_max;
	fba->anm_max = anm_max;
	fba->tex_max = tex_max;
	
	fba->lres_mdl = LRes_Init(
		gp_heap_id, HEAPID_FIELD_FE_BLACT_MDL, mdl_size, mdl_max );
	fba->lres_anm = LRes_Init(
		gp_heap_id, HEAPID_FIELD_FE_BLACT_ANM, anm_size, anm_max );
	
	fba->resm_tex = TEXRESM_Init( tex_max, gp_heap_id );		//�ǂ����悤��
	
	fe_BlActHeaderManageInit( fes, fba, act_max );
	
	set.WorkNum = act_max;
	set.heap = fe_HeapIDGet( fes );
	fba->set_ptr = BLACT_InitSet( &set );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�폜
 * @param	fes				FE_SYS *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_BlActDelete( FE_SYS *fes )
{
	FE_BLACT *fba = fes->fe_blact;
	
	if( fba != NULL ){
		BLACT_DestSet( fba->set_ptr );
		fe_BlActHeaderManageDelete( fba );
		
		LRes_Delete( fba->lres_mdl );
		LRes_Delete( fba->lres_anm );
		TEXRESM_Delete( fba->resm_tex );
	
		FE_FreeMemory( fba );
		fes->fe_blact = NULL;
	}
}

//==============================================================================
//	�t�B�[���h�G�t�F�N�g�p�r���{�[�h�A�N�^�[�@�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�ǉ��@���̂�BLACT_Add()
 * @param	fes			FE_SYS
 * @param	head		BLACT_HEADER *
 * @param	vec			���W
 * @retval	BLACT_WORK	BLACT_WORK_PTR ���s=�����I��
 */
//--------------------------------------------------------------
BLACT_WORK_PTR FE_BlActAdd( FE_SYS *fes, 
		const BLACT_HEADER *head, const VecFx32 *vec )
{
	BLACT_ADD add;
	BLACT_WORK_PTR act;
	BLACT_SET_PTR set;
	VecFx32 scale = { FX32_ONE,FX32_ONE,FX32_ONE };
	
	set = fes->fe_blact->set_ptr;
	
	add.blact_s = set;
	add.pHeader = head;
	add.matrix	= *vec;
	add.scale	= scale;
	
	act = BLACT_Add( &add );
	GF_ASSERT( act != NULL && "FE_BlActAdd()�A�N�^�[�ǉ����s �A�N�^�[�e���s����?" );
	
	if( act != NULL ){
		NNS_G3dMdlSetMdlFogEnableFlagAll( BLACT_MdlResGet(act), TRUE );
		SetGlbLightMdl( BLACT_MdlResGet(act) );
	}
	
	return( act );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�ǉ��@���̂�BLACT_Add()�B
 * �w�b�_�[�w���FE_BlActHeaderManageAdd()�Ŏw�肵��ID�B
 * @param	fes			FE_SYS
 * @param	id			�w�b�_�[�o�^ID
 * @param	vec			���W
 * @retval	BLACT_WORK	BLACT_WORK_PTR ���s=�����I��
 */
//--------------------------------------------------------------
BLACT_WORK_PTR FE_BlActAddID( FE_SYS *fes, u32 id, const VecFx32 *vec )
{
	BLACT_HEADER *head;
	head = fe_BlActHeaderManageGet( fes->fe_blact, id );
	return( FE_BlActAdd(fes,head,vec) );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�w�b�_�[�o�^
 * @param	fes			FE_SYS *
 * @param	id			�o�^ID
 * @param	mdl				���f�����\�[�X�ւ�*
 * @param	anm				�A�j�����\�[�X�ւ�*
 * @param	tex				�e�N�X�`�����\�[�X�ւ�*
 * @param	tex_key			�풓�^�̏ꍇ�̓L�[�擾�pTEXRES_OBJ_PTR���w��BNULL=�]���^�ŃZ�b�g
 * @param	anm_tbl			�r���{�[�h�A�j�� const BLACT_ANIME_TBL *
 * @retval	BLACT_HEADER �o�^���ꂽBLACT_HEADER * �ǉ��ς݂̏ꍇ�͂��̗̈��Ԃ� �ǉ����s=ASSERT
 */
//--------------------------------------------------------------
BLACT_HEADER * FE_BlActHeaderManageAdd( FE_SYS *fes, u32 id,
	void *mdl, TEXANM_DATATBL *anm, void *tex, TEXRES_OBJ_PTR tex_key,
	const BLACT_ANIME_TBL *anm_tbl )
{
	BLACT_HEADER *head;
	head = fe_BlActHeaderManageAdd( fes->fe_blact, id, mdl, anm, tex, tex_key, anm_tbl );
	return( head );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�w�b�_�[�o�^ ���\�[�X�}�l�[�W���[���p
 * @param	fes			FE_SYS *
 * @param	id			�o�^ID
 * @param	mdl_id		FE_BlActResAdd_Mdl()�œo�^����ID
 * @param	anm_id		FE_BlActResAdd_Anm()�œo�^����ID
 * @param	tex_id		FE_BlActResAdd_Tex()�œo�^����ID
 * @param	tex_flag	FE_BLACT_TEX_VRAM��
 * @param	anm_tbl		�r���{�[�h�A�j�� const BLACT_ANIME_TBL *
 * @retval	BLACT_HEADER �o�^���ꂽBLACT_HEADER * �ǉ��ς݂̏ꍇ�͂��̗̈��Ԃ� �ǉ����s=ASSERT
 */
//--------------------------------------------------------------
BLACT_HEADER * FE_BlActHeaderManageAddResmID(
		FE_SYS *fes, u32 id, u32 mdl_id, u32 anm_id, u32 tex_id, int tex_flag,
		const BLACT_ANIME_TBL *anm_tbl )
{
	void *mdl,*tex,*anm;
	TEXANM_DATATBL anmdata;
	TEXRES_OBJ_PTR tex_obj;
	BLACT_HEADER *head;
	FE_BLACT *fba;
	
	fba = fes->fe_blact;
	
	mdl = LRes_IDResGet( fba->lres_mdl, mdl_id );
	anm = LRes_IDResGet( fba->lres_anm, anm_id );
	TEXANM_UnPackLoadFile( anm, &anmdata );
	
	tex_obj = TEXRESM_GetResObj( fba->resm_tex, tex_id );
	GF_ASSERT( tex_obj != NULL && "FE_BlActHeaderManageAddResmID()�e�N�X�`�����o�^ID�w��" );
	tex = TEXRESM_GetResPTR( tex_obj );
	
	if( tex_flag == FE_BLACT_TEX_TRANS ){
		tex_obj = NULL;
	}
	
	head = fe_BlActHeaderManageAdd( fba, id, mdl, &anmdata, tex, tex_obj, anm_tbl );
	GF_ASSERT( head != NULL && "FE_BlActHeaderManageAdd()�o�^���I�[�o�[�ɂ��ǉ����s" );
	
	return( head );
}

//==============================================================================
//	�t�B�[���h�G�t�F�N�g�p�r���{�[�h�A�N�^�[�@�w�b�_�[�}�l�[�W��
//==============================================================================
//--------------------------------------------------------------
/**
 * �w�b�_�[�̈�m�ہ@�̈��FE_AllocMemory()�Ŋm��
 * @param	fes		FE_SYS
 * @param	fba		FE_BLACT
 * @param	max		�w�b�_�[�ő吔
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_BlActHeaderManageInit( FE_SYS *fes, FE_BLACT *fba, u32 max )
{
	BLACT_HEADER *head;
	FE_BLACT_H_ID *hm;
	
	head = FE_AllocMemory( fes, sizeof(BLACT_HEADER)*max, ALLOC_FR );
	fba->head_tbl = head;
	
	hm = FE_AllocMemory( fes, FE_BLACT_H_ID_SIZE*max, ALLOC_FR );
	fba->head_manage = hm;
	
	do{
		hm->id = FE_BLACT_H_ID_NOT;
		hm->head = head;
		hm++;
		head++;
		max--;
	}while( max );
}

//--------------------------------------------------------------
/**
 * �w�b�_�[�̈�폜
 * @param	fba		FE_BLACT
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_BlActHeaderManageDelete( FE_BLACT *fba )
{
	FE_FreeMemory( fba->head_manage );
	FE_FreeMemory( fba->head_tbl );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�w�b�_�[�Ǘ��̈�J��
 * @param	fba			FE_BLACT *
 * @param	id			�J������ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_BlActHeaderManageFree( FE_BLACT *fba, u32 id )
{
	u32 max = fba->blact_max;
	FE_BLACT_H_ID *ma = fba->head_manage;
	
	do{
		if( ma->id == id ){ ma->id = FE_BLACT_H_ID_NOT; return; }
		ma++; max--;
	}while( max );	
	
	GF_ASSERT( 0 && "fe_BlActHeaderManageFree()�o�^����Ă��Ȃ��w�b�_�[ID�ł�" );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�w�b�_�[�Ǘ��̈�փw�b�_�[�ǉ�
 * @param	fba				FE_BLACT *
 * @param	id				�o�^����ID
 * @param	mdl				���f�����\�[�X�ւ�*
 * @param	anm				�A�j�����\�[�X�ւ�*
 * @param	tex				�e�N�X�`�����\�[�X�ւ�*
 * @param	tex_key			�풓�^�̏ꍇ�̓L�[�擾�pTEXRES_OBJ_PTR���w��BNULL=�]���^�ŃZ�b�g
 * @param	anm_tbl			�r���{�[�h�A�j�� BLACT_ANIME_TBL *
 * @retval	BLACT_HEADER	�w�b�_�[�̈�ւ�*�BNULL=���s
 */
//--------------------------------------------------------------
static BLACT_HEADER * fe_BlActHeaderManageAdd( FE_BLACT *fba, u32 id,
	void *mdl, TEXANM_DATATBL *anm, void *tex, TEXRES_OBJ_PTR tex_key,
	const BLACT_ANIME_TBL *anm_tbl )
{
	BLACT_HEADER *head;
	
	head = NULL;
	
	{
		u32 max = fba->blact_max;
		FE_BLACT_H_ID *ma = fba->head_manage;
		
		do{ if(ma->id==id){ return(ma->head); }					//�o�^�ς�
			ma++; max--;
		}while( max );
		
		ma = fba->head_manage;
		max = fba->blact_max;
		
		do{ if(ma->id==FE_BLACT_H_ID_NOT){ ma->id=id; head=ma->head; break; }
			ma++; max--;
		}while( max );
	}
	
	GF_ASSERT( head != NULL && "fe_BlActHeaderManageAdd() �r���{�[�h�w�b�_�[���t"  );
	
	memset( head, 0, sizeof(BLACT_HEADER) );
	
	head->ImdRes = mdl;
	head->texanm = *anm;
	head->ItxRes = tex;
	
	if( tex_key != NULL ){
		head->texKey = TEXRESM_GetTexKeyPTR( tex_key );
		head->tex4x4Key = TEXRESM_GetTex4x4KeyPTR( tex_key );
		head->plttKey = TEXRESM_GetPlttKeyPTR( tex_key );
	}
	
	head->anm = anm_tbl;
	return( head );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�w�b�_�[�Ǘ��̈�@�w�b�_�[�擾
 * @param	fba				FE_BLACT *
 * @param	id				�擾���邷��ID
 * @retval	BLACT_HEADER	�w�b�_�[�̈�ւ�*�BNULL=���s
 */
//--------------------------------------------------------------
static BLACT_HEADER * fe_BlActHeaderManageGet( FE_BLACT *fba, u32 id )
{
	u32 max = fba->blact_max;
	FE_BLACT_H_ID *ma = fba->head_manage;
		
	do{ if(ma->id==id){ return(ma->head); }
		ma++; max--;
	}while( max );
	
	GF_ASSERT( 0 && "fe_BlActHeaderManageGet()ID�o�^����"  );
	return( NULL );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�w�b�_�[�Ǘ��̈�w�b�_�[�擾
 * @param	fes				FE_SYS *
 * @param	id				�擾����ID
 * @retal	BLACT_HEADER	�w�b�_�[�̈�ւ�*�BNULL=�o�^����Ă��Ȃ�
 */
//--------------------------------------------------------------
BLACT_HEADER * FE_BlActHeaderManageGet( FE_SYS *fes, u32 id )
{
	FE_BLACT *fba = fes->fe_blact;
	return( fe_BlActHeaderManageGet(fba,id) );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�w�b�_�[�Ǘ��̈�J��
 * @param	fes			FE_SYS *
 * @param	id			�J������ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActHeaderManageFree( FE_SYS *fes, u32 id )
{
	FE_BLACT *fba = fes->fe_blact;
	fe_BlActHeaderManageFree( fba, id );
}

//==============================================================================
//	�t�B�[���h�G�t�F�N�g�@�r���{�[�h���\�[�X�@�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * ���\�[�X�z�u�@���f�����O�f�[�^
 * @param	fes		FE_SYS *
 * @param	id		�o�^����ID
 * @param	data	�z�u����f�[�^
 * @param	size	data�T�C�Y
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResAdd_Mdl( FE_SYS *fes, u32 id, const void *data, u32 size )
{
	FE_BLACT *fba = fes->fe_blact;
	void *alloc = LRes_AllocID( fba->lres_mdl, id, size, ALLOC_FR );
	MI_CpuCopy8( data, alloc, size );
}

//--------------------------------------------------------------
/**
 * ���\�[�X�z�u�@���f�����O�f�[�^�@�A�[�J�C�u
 * @param	fes		FE_SYS *
 * @param	id		�o�^����ID
 * @param	datid	�o�^����A�[�J�C�u�f�[�^�C���f�b�N�XID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResAdd_MdlArc( FE_SYS *fes, u32 id, u32 datid ) 
{
	FE_BLACT *fba = fes->fe_blact;
	LResUtil_AllocIDArcLoad( fba->lres_mdl, id, fes->arc_handle, datid, ALLOC_FR );
}

//--------------------------------------------------------------
/**
 * ���\�[�X�擾�@���f���f�[�^
 * @param	fes		FE_SYS *
 * @param	id		�擾����ID
 * @retval	void*	id���\�[�X
 */
//--------------------------------------------------------------
void * FE_BlActResGet_Mdl( FE_SYS *fes, u32 id )
{
	FE_BLACT *fba = fes->fe_blact;
	void *mdl = LRes_IDResGet( fba->lres_mdl, id );
	return( mdl );
}

//--------------------------------------------------------------
/**
 * ���\�[�X�폜�@���f�����O�f�[�^
 * @param	fes		FE_SYS *
 * @param	id		�폜����ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResDelete_Mdl( FE_SYS *fes, u32 id )
{
	FE_BLACT *fba = fes->fe_blact;
	LRes_FreeID( fba->lres_mdl, id );
}

//--------------------------------------------------------------
/**
 * ���\�[�X�z�u�@�A�j���f�[�^
 * @param	fes		FE_SYS *
 * @param	id		�o�^����ID
 * @param	data	�z�u����f�[�^
 * @param	size	data�T�C�Y
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResAdd_Anm( FE_SYS *fes, u32 id, const void *data, u32 size )
{
	FE_BLACT *fba = fes->fe_blact;
	void *alloc = LRes_AllocID( fba->lres_anm, id, size, ALLOC_FR );
	MI_CpuCopy8( data, alloc, size );
}

//--------------------------------------------------------------
/**
 * ���\�[�X�z�u�@�A�j���[�V�����f�[�^�@�A�[�J�C�u
 * @param	fes		FE_SYS *
 * @param	id		�o�^����ID
 * @param	datid	�o�^����A�[�J�C�u�f�[�^�C���f�b�N�XID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResAdd_AnmArc( FE_SYS *fes, u32 id, u32 datid ) 
{
	FE_BLACT *fba = fes->fe_blact;
	LResUtil_AllocIDArcLoad( fba->lres_anm, id, fes->arc_handle, datid, ALLOC_FR );
}

//--------------------------------------------------------------
/**
 * ���\�[�X�擾�@�A�j���f�[�^
 * @param	fes		FE_SYS *
 * @param	id		�擾����ID
 * @retval	void*	id���\�[�X
 */
//--------------------------------------------------------------
void * FE_BlActResGet_Anm( FE_SYS *fes, u32 id )
{
	FE_BLACT *fba = fes->fe_blact;
	void *anm = LRes_IDResGet( fba->lres_anm, id );
	return( anm );
}

//--------------------------------------------------------------
/**
 * ���\�[�X�폜�@�A�j���f�[�^
 * @param	fes		FE_SYS *
 * @param	id		�폜����ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResDelete_Anm( FE_SYS *fes, u32 id )
{
	FE_BLACT *fba = fes->fe_blact;
	LRes_FreeID( fba->lres_anm, id );
}

//--------------------------------------------------------------
/**
 * ���\�[�X�z�u�@�e�N�X�`���f�[�^
 * @param	fes		FE_SYS *
 * @param	id		�o�^����ID
 * @param	data	�z�u����f�[�^
 * @param	size	data�T�C�Y
 * @param	texcut	TEXRESM_TEX_CUT_FALSE��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResAdd_Tex( FE_SYS *fes, u32 id, void *data, u32 texcut )
{
	FE_BLACT *fba = fes->fe_blact;
	TEXRES_OBJ_PTR obj = TEXRESM_AddAndAllocVramKeyResNormal( fba->resm_tex, data, id, texcut, fe_HeapIDGet(fes) );
	GF_ASSERT( obj != NULL && "FE_BlActResAdd_Tex()�ǉ����s" );
	fe_VIntrWaitTexLoadSet( fes, id, fba->resm_tex );
}

//--------------------------------------------------------------
/**
 * ���\�[�X�z�u�@�e�N�X�`���f�[�^�A�A�[�J�C�u�B
 * @param	fes		FE_SYS *
 * @aram	id		�o�^����ID
 * @param	dataid	�A�[�J�C�u�f�[�^�C���f�b�N�XID
 * @param	texcut	TEXRESM_TEX_CUT_FALSE��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResAdd_TexArc( FE_SYS *fes, u32 id, u32 datid, u32 texcut )
{
	FE_BLACT *fba = fes->fe_blact;
	void *buf = FE_ArcDataLoadAlloc( fes, datid, ALLOC_LO );
	TEXRES_OBJ_PTR obj = TEXRESM_AddAndAllocVramKeyResNormal( fba->resm_tex, buf, id, texcut, fe_HeapIDGet(fes) );
	GF_ASSERT( obj != NULL && "FE_BlActResAdd_Tex()�ǉ����s" );
	fe_VIntrWaitTexLoadSet( fes, id, fba->resm_tex );
}

//--------------------------------------------------------------
/**
 * ���\�[�X�擾�@�e�N�X�`���f�[�^
 * @param	fes		FE_SYS *
 * @param	id		�擾����ID
 * @retval	void*	id���\�[�X
 */
//--------------------------------------------------------------
void * FE_BlActResGet_Tex( FE_SYS *fes, u32 id )
{
	FE_BLACT *fba = fes->fe_blact;
	TEXRES_OBJ_PTR tex_obj = TEXRESM_GetResObj( fba->resm_tex, id );
	void *tex = TEXRESM_GetResPTR( tex_obj );
	return( tex );
}

//--------------------------------------------------------------
/**
 * ���\�[�X�폜�@�e�N�X�`���f�[�^
 * @param	fes		FE_SYS *
 * @param	id		�o�^����ID
 * @param	data	�z�u����f�[�^
 * @param	size	data�T�C�Y
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResDelete_Tex( FE_SYS *fes, u32 id )
{
	FE_BLACT *fba = fes->fe_blact;
	TEXRESM_DeleteResID( fba->resm_tex, id );
}

//--------------------------------------------------------------
/**
 * �e�N�X�`���f�[�^V�u�����N�]���쐬
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_VIntrWaitTexLoadSet( FE_SYS *fes, u32 id, TEXRES_MANAGER_PTR resm_tex )
{
	FE_VINTR_TEX_WORK *work = FE_AllocMemory( fes, FE_VINTR_TEX_WORK_SIZE, ALLOC_LO );
	work->trans_end = TRUE;
	work->id = id;
	work->resm_tex = resm_tex;
	VIntrTCB_Add( fe_VIntrTCB_TexLoad, work, TCBPRI_VINTR_BLACT_TEX_LOAD );
	VWaitTCB_Add( fe_VWaitTCB_TexLoad, work, TCBPRI_VWAIT_BLACT_TEX_LOAD );
}

//--------------------------------------------------------------
/**
 * �e�N�X�`���f�[�^V�u�����N�]�� tcb
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_VIntrTCB_TexLoad( TCB_PTR tcb, void *wk )
{
	FE_VINTR_TEX_WORK *work = wk;
	TEXRESM_TexLoadID( work->resm_tex, work->id );
	work->trans_end = TRUE;
	TCB_Delete( tcb );
}

//--------------------------------------------------------------
/**
 * �e�N�X�`���f�[�^V�u�����N��̊J�� tcb
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_VWaitTCB_TexLoad( TCB_PTR tcb, void *wk )
{
	FE_VINTR_TEX_WORK *work = wk;
	
	if( work->trans_end == TRUE ){
		TEXRESM_CutTexID( work->resm_tex, work->id );
		FE_FreeMemory( work );
		TCB_Delete( tcb );
	}
}

//==============================================================================
//	3dmdl
//==============================================================================
//--------------------------------------------------------------
/**
 * simple_3DModelSet�@�t�B�[���h�G�t�F�N�g��
 * @param	
 * @retval
 */
//--------------------------------------------------------------
void FE_simple3DModelInitOnly( FE_SYS *fes,
	NNSG3dRenderObj *object_p, NNSG3dResMdl **model, NNSG3dResFileHeader **resFile )
{
    NNSG3dResTex *texture = NULL;
    BOOL status;
	
	texture = NNS_G3dGetTex( *resFile );						//�e�N�X�`�����\�[�X�擾
	
	if( texture != NULL ){
		if( TexKeyLive(texture) == FALSE ){		// �e�N�X�`����Vram�ɓW�J����Ă��Ȃ����`�F�b�N
			DC_FlushRange( *resFile, (*resFile)->fileSize );
			
			// �f�t�H���g�̏������֐����R�[�����ăZ�b�g�A�b�v����
			status = NNS_G3dResDefaultSetup( *resFile );
			GF_ASSERT( status && "NNS_G3dResDefaultSetup failed" );
		}
	}
 	 
    // G3D: ���f���̎擾
    // nsbmd�̓��f���𕡐��܂ނ��Ƃ��ł���̂ŁA�C���f�b�N�X(���f�����P�̏ꍇ��0)
    // ���w�肵�ĂP�̃��f���ւ̃|�C���^���擾����B
    *model = NNS_G3dGetMdlByIdx( NNS_G3dGetMdlSet(*resFile), 0 );
	GF_ASSERT( model && "NNS_G3dGetMdlByIdx() failed" );
	NNS_G3dRenderObjInit( object_p, *model );
}

//--------------------------------------------------------------
/**
 * simple_3DModelSet�@�t�B�[���h�G�t�F�N�g��
 * @param	
 * @retval
 */
//--------------------------------------------------------------
void FE_simple3DModelInit( FE_SYS *fes, u32 dataid, ALLOCTYPE type,
	NNSG3dRenderObj *object_p, NNSG3dResMdl **model, NNSG3dResFileHeader **resFile )
{
    *resFile = FE_ArcDataLoadAlloc( fes, dataid, type );
	FE_simple3DModelInitOnly( fes, object_p, model, resFile );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���f���]���^�X�N
 */
//-----------------------------------------------------------------------------
static void FLD_3DObjMdlTransTcb( TCB_PTR tcb, void* p_work )
{
	FLD_3DOBJ_MDL* p_mdl = p_work;
	LoadVRAMTexture( p_mdl->pMdlTex );
	BindTexture( p_mdl->pResMdl, p_mdl->pMdlTex );
	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�RD���f���ǂݍ���
 */
//-----------------------------------------------------------------------------
void FE_3DObjMdlLoad( FE_SYS *fes, FLD_3DOBJ_MDL *p_mdl, u32 dataid, ALLOCTYPE type )
{
	p_mdl->pResMdl = FE_ArcDataLoadAlloc( fes, dataid, type );
	p_mdl->pModelSet	= NNS_G3dGetMdlSet( p_mdl->pResMdl );
	p_mdl->pModel		= NNS_G3dGetMdlByIdx( p_mdl->pModelSet, 0 );
	p_mdl->pMdlTex		= NNS_G3dGetTex( p_mdl->pResMdl );
	
	if( p_mdl->pMdlTex ){
		// �e�N�X�`���f�[�^�]��
		VIntrTCB_Add( FLD_3DObjMdlTransTcb, p_mdl, FLD_3DOBJ_TEXTRANS_TCB_PRI );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�RD�A�j���f�[�^�ǂݍ���
 */
//-----------------------------------------------------------------------------
void FE_3DObjAnmLoad(
		FE_SYS *fes,
		FLD_3DOBJ_ANM *p_anm,
		const FLD_3DOBJ_MDL *cp_mdl,
		NNSFndAllocator* pallocator,
		u32 dataid, ALLOCTYPE type )
{
	p_anm->pResAnm = FE_ArcDataLoadAlloc( fes, dataid, type );
	p_anm->pOneResAnm = NNS_G3dGetAnmByIdx(p_anm->pResAnm,0);
	p_anm->pAnmObj = NNS_G3dAllocAnmObj( pallocator, p_anm->pOneResAnm, cp_mdl->pModel );
	
	NNS_G3dAnmObjInit(
		p_anm->pAnmObj,
		p_anm->pOneResAnm,
		cp_mdl->pModel,
		cp_mdl->pMdlTex );
}

//------------------------------------------------------------------
/**
 * NitroSystem ���C�u�����n�֐����v������A���P�[�^���쐬����
 */
//------------------------------------------------------------------
void FE_InitAllocator( FE_SYS *fes, NNSFndAllocator *pAllocator )
{
	sys_InitAllocator( pAllocator, fe_HeapIDGet(fes), 32 );
}

//==============================================================================
//	debug
//==============================================================================
#ifdef DEBUG_FE_EOA_USE_CHECK

#define DB_FE_EOA_USE_CHECK_MAX (80)

FIELDSYS_WORK *DebugFeEoaUseCheck_FieldSysWork;
u32 DebugFeEoaUseCheck_ZoneIDTbl[DB_FE_EOA_USE_CHECK_MAX];
u32 DebugFeEoaUseCheck_HeadTbl[DB_FE_EOA_USE_CHECK_MAX];
u32 DebugFeEoaUseCheck_EoaTbl[DB_FE_EOA_USE_CHECK_MAX];

//--------------------------------------------------------------
//	eoa �ǉ��`�F�b�N�@������
//--------------------------------------------------------------
static void DEBUG_FeEoaUseCheck_Init( FE_SYS *fes )
{
	int i;
	DebugFeEoaUseCheck_FieldSysWork = fes->fsys;
	
	for( i = 0; i < DB_FE_EOA_USE_CHECK_MAX; i++ ){
		DebugFeEoaUseCheck_ZoneIDTbl[i] = 0xffffffff;
		DebugFeEoaUseCheck_HeadTbl[i] = 0;
		DebugFeEoaUseCheck_EoaTbl[i] = 0;
	}
}

//--------------------------------------------------------------
//	eoa �ǉ��`�F�b�N�@�ǉ�
//--------------------------------------------------------------
static void DEBUG_FeEoaUseCheck_Add( EOA_PTR eoa, const EOA_H_NPP *head )
{
	int i;
	FIELDSYS_WORK *fsys = DebugFeEoaUseCheck_FieldSysWork;
	u32 zone_id = fsys->location->zone_id;
	
	for( i = 0; i < DB_FE_EOA_USE_CHECK_MAX; i++ ){
		if( DebugFeEoaUseCheck_EoaTbl[i] == (u32)NULL ){
			DebugFeEoaUseCheck_ZoneIDTbl[i] = zone_id;
			DebugFeEoaUseCheck_HeadTbl[i] = (u32)head;
			DebugFeEoaUseCheck_EoaTbl[i] = (u32)eoa;
			return;
		}
	}
}

//--------------------------------------------------------------
//	eoa �ǉ��`�F�b�N�@�폜
//--------------------------------------------------------------
static void DEBUG_FeEoaUseCheck_Del( EOA_PTR eoa )
{
	int i;
	
	for( i = 0; i < DB_FE_EOA_USE_CHECK_MAX; i++ ){
		if( DebugFeEoaUseCheck_EoaTbl[i] == (u32)eoa ){
			DebugFeEoaUseCheck_ZoneIDTbl[i] = 0xffffffff;
			DebugFeEoaUseCheck_HeadTbl[i] = 0;
			DebugFeEoaUseCheck_EoaTbl[i] = 0;
			return;
		}
	}
}
#endif
