//******************************************************************************
/**
 *
 * @file	fieldobj_blact.c
 * @brief	�t�B�[���hOBJ �r���{�[�h�A�N�^�[�֘A
 * @author	kagaya
 * @data	05.07.25
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
///	
//--------------------------------------------------------------
#ifdef PM_DEBUG
//#define BLACT_TEXUSE_OLD
#endif

//--------------------------------------------------------------
///	�o�^����
//--------------------------------------------------------------
typedef enum
{
	ADDRES_REGIST = 0,										///<�o�^�ς�
	ADDRES_RESERVE,											///<�o�^��\��
	ADDRES_NOTBLACT,										///<�r���{�[�h�ł͂Ȃ�
}ADDRES_TYPE;

//==============================================================================
//	typedef struct
//==============================================================================
#if 0
//--------------------------------------------------------------
///	GUEST_BLACT_ADD_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int code;												///<�\������OBJ�R�[�h
	FIELD_OBJ_PTR	fldobj;									///<�ǉ�����Ώۂ�FIELD_OBJ_PTR
	BLACT_WORK_PTR	*act;									///<�ǉ����ꂽ�r���{�[�h *�i�[��
}GUEST_BLACT_ADD_WORK;

///GUEST_BLACT_ADD_WORK�T�C�Y
#define GUEST_BLACT_ADD_WORK_SIZE (sizeof(GUEST_BLACT_ADD_WORK))
///BLACT_ADD_TBL���T�C�Y
#define GUEST_BLACT_ADD_WORK_ALL_SIZE (GUEST_BLACT_ADD_WORK_SIZE*FLDOBJ_RESM_MAX_TEX)
#endif

#if 0
//--------------------------------------------------------------
///	VINTR_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	vu32 access_flag;										///<�A�N�Z�X���t���O
	int max;
	FIELD_OBJ_BLACT_CONT *cont;								///<FIELD_OBJ_BLACT_CONT *
	TEXRES_MANAGER_PTR *resm_tex_tbl;						///<�]���e�N�X�`���e�[�u��
	int *resm_tex_id_tbl;									///<�]��ID�e�[�u��
}VINTR_WORK;

#define VINTR_WORK_SIZE (sizeof(VINTR_WORK))				///<VINTR_WORK�T�C�Y
#endif

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void FldOBJ_BlActAdd_GuestCancel( CONST_FIELD_OBJ_PTR fldobj );
	
#if 0 //�s�v
static void FldOBJ_BlActGuestAddTcbAdd( FIELD_OBJ_BLACT_CONT *cont, int pri );
static void FldOBJ_BlActGuestAddTcbDelete( FIELD_OBJ_BLACT_CONT *cont );
static void FldOBJ_GuestBlActAddTcb( TCB_PTR tcb, void *wk );
//static void FldOBJ_BlActAdd_GuestCancel( CONST_FIELD_OBJ_PTR fldobj );

static void FldOBJ_BlActVIntrTcbAdd( FIELD_OBJ_BLACT_CONT *cont, int max, int pri );
static void FldOBJ_BlActVIntrTcbDelete( FIELD_OBJ_BLACT_CONT *cont );
static void FldOBJ_VIntrTcb( TCB_PTR tcb, void *wk );
static void FldOBJ_VIntrTcb_TexLoadAdd(
		FIELD_OBJ_BLACT_CONT *cont, TEXRES_MANAGER_PTR resm, int id );
static void FldOBJ_VIntrTcb_TexLoadCancel( FIELD_OBJ_BLACT_CONT *cont, int id );
#endif

static void FldOBJ_BlActHeaderManageInit( FIELD_OBJ_BLACT_CONT *cont, int max );
static void FldOBJ_BlActHeaderManageDelete( FIELD_OBJ_BLACT_CONT *cont );
static BLACT_HEADER * FldOBJ_BlActHeaderManageGet( FIELD_OBJ_BLACT_CONT *cont, u32 code );
static void FldOBJ_BlActHeaderManageFree( FIELD_OBJ_BLACT_CONT *cont, u32 code );
static void FldOBJ_BlActHeaderManageFreeForce( FIELD_OBJ_BLACT_CONT *cont );
static int FldOBJ_OBJCodeUseSearch(
		CONST_FIELD_OBJ_SYS_PTR sys, CONST_FIELD_OBJ_PTR fldobj, int code );

static void FldOBJ_BlActResManageInit( FIELD_OBJ_BLACT_CONT *cont,
		int mdl_max, int mdl_reg_max,
		int anm_max, int anm_reg_max,
		int tex_max, int tex_reg_max );
static void FldOBJ_BlActResManageDelete( FIELD_OBJ_BLACT_CONT *cont );
static const FIELD_OBJ_RESMH * FldOBJ_BlActResmH_Search( int id, const FIELD_OBJ_RESMH *tbl );
static const FIELD_OBJ_RESMNARC * FldOBJ_BlActResmNArc_Search(
					int id, int max_id, const FIELD_OBJ_RESMNARC *tbl );

static int FldOBJ_BlActResmNArc_AddResTbl( FIELD_OBJ_BLACT_CONT *cont,
		RES_MANAGER_PTR resm, int id, int max, const FIELD_OBJ_RESMNARC *tbl );

static int FldOBJ_BlActLResNArc_AddResTbl(
		FIELD_OBJ_BLACT_CONT *cont,
		LRES *lres_sys, int id, int max, const FIELD_OBJ_RESMNARC *tbl );

static int FldOBJ_BlActResm_AddResTbl(
	RES_MANAGER_PTR resm, int id, const FIELD_OBJ_RESMH *tbl );
static int FldOBJ_BlActResm_AddResNormalTbl(
		RES_MANAGER_PTR resm, int id, const FIELD_OBJ_RESMH *tbl );
static ADDRES_TYPE FldOBJ_BlActTexResmNArc_AddResTbl( FIELD_OBJ_BLACT_CONT *cont,
		REGULAR_GUEST reg_type, int id, const FIELD_OBJ_RESMNARC *tbl );

static ADDRES_TYPE FldOBJ_BlActResm_RegularAdd_Tex( FIELD_OBJ_BLACT_CONT *cont, int id );
static ADDRES_TYPE FldOBJ_BlActResm_GuestAdd_Tex( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_BlActResm_RegularAddTbl_Tex( FIELD_OBJ_BLACT_CONT *cont, const int *tbl );
static void FldOBJ_BlActResm_RegularAdd_Mdl( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_BlActResm_GuestAdd_Mdl( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_BlActResm_RegularAddTbl_Mdl( FIELD_OBJ_BLACT_CONT *cont, const int *tbl );
static void FldOBJ_BlActResm_RegularAdd_Anm( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_BlActResm_GuestAdd_Anm( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_BlActResm_RegularAddTbl_Anm( FIELD_OBJ_BLACT_CONT *cont, const int *tbl );
static void FldOBJ_BlActResm_RegularAdd_All(
	FIELD_OBJ_BLACT_CONT *cont, const int *tex_tbl, const int *mdl_tbl, const int *anm_tbl );
static void FldOBJ_BlActResm_IDTblInit( int *tbl, int init_id, int max );
static int FldOBJ_BlActResm_IDTblReg( int *tbl, int reg_id, int spc_id, int max );
static int FldOBJ_BlActResm_IDTblSearch( int *tbl, int chk_id, int max );
static int FldOBJ_BlActResm_IDTblDel( int *tbl, int del_id, int spc_id, int max );
static void FldOBJ_BlActResm_MdlIDInit( FIELD_OBJ_BLACT_CONT *cont );
static void FldOBJ_BlActResm_MdlIDReg_Regular( FIELD_OBJ_BLACT_CONT *cont, int id );
static int FldOBJ_BlActResm_MdlIDSearch_Regular( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_BlActResm_MdlIDReg_Guest( FIELD_OBJ_BLACT_CONT *cont, int id );
static int FldOBJ_BlActResm_MdlIDSearch_Guest( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_BlActResm_MdlIDDelete_Guest( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_BlActResm_MdlIDDelete_GuestAll(
		FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_BLACT_CONT *cont );
static void FldOBJ_BlActResm_AnmIDInit( FIELD_OBJ_BLACT_CONT *cont );
static void FldOBJ_BlActResm_AnmIDReg_Regular( FIELD_OBJ_BLACT_CONT *cont, int id );
static int FldOBJ_BlActResm_AnmIDSearch_Regular( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_BlActResm_AnmIDReg_Guest( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_BlActResm_AnmIDDelete_Guest( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_BlActResm_AnmIDDelete_GuestAll(
		FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_BLACT_CONT *cont );
static void FldOBJ_BlActResm_TexIDInit( FIELD_OBJ_BLACT_CONT *cont );
static void FldOBJ_BlActResm_TexIDReg_Regular( FIELD_OBJ_BLACT_CONT *cont, int id );
static int FldOBJ_BlActResm_TexIDSearch_Regular( FIELD_OBJ_BLACT_CONT *cont, int id );
static TEXREG_TYPE FldOBJ_BlActResm_TexIDSearchAll( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_BlActResm_TexIDReg_Guest( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_BlActResm_TexIDDelete_Guest( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_BlActResm_TexIDDelete_GuestAll(
		FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_BLACT_CONT *cont );
static int FldOBJ_BlActResm_TexIDSearch_Guest( FIELD_OBJ_BLACT_CONT *cont, int id );
static int FldOBJ_BlActResManage_OBJCodeRegistCheck( FIELD_OBJ_BLACT_CONT *cont, int code );
static int FldOBJ_BlActResManage_MdlIDRegistCheck( FIELD_OBJ_BLACT_CONT *cont, int id );
static int FldOBJ_BlActResManage_AnmIDRegistCheck( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_BlActResManage_OBJCodeRegist( FIELD_OBJ_BLACT_CONT *cont, int code );
static void FldOBJ_BlActResManage_MdlIDRegist( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_BlActResManage_AnmIDRegist( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_BlActResManage_AllIDRegist( FIELD_OBJ_BLACT_CONT *cont, int code );
static int FldOBJ_BlActCont_FldOBJSearch_OBJCode(
	CONST_FIELD_OBJ_SYS_PTR fos, int code, CONST_FIELD_OBJ_PTR ignore_obj );
static int FldOBJ_BlActCont_FldOBJSearch_MdlID(
	CONST_FIELD_OBJ_SYS_PTR fos, int mdl_id, CONST_FIELD_OBJ_PTR ignore_obj );
static int FldOBJ_BlActCont_FldOBJSearch_AnmID(
	CONST_FIELD_OBJ_SYS_PTR fos, int anm_id, CONST_FIELD_OBJ_PTR ignore_obj );

static int * FldOBJ_BlActCont_ResmTexIDTblGet( FIELD_OBJ_BLACT_CONT *cont );
static int * FldOBJ_BlActCont_ResmMdlIDTblGet( FIELD_OBJ_BLACT_CONT *cont );
static int * FldOBJ_BlActCont_ResmAnmIDTblGet( FIELD_OBJ_BLACT_CONT *cont );
static void FldOBJ_BlActCont_RegularMdlMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max );
static int FldOBJ_BlActCont_RegularMdlMaxGet( const FIELD_OBJ_BLACT_CONT *cont );
static void FldOBJ_BlActCont_GuestMdlMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max );
static int FldOBJ_BlActCont_GuestMdlMaxGet( const FIELD_OBJ_BLACT_CONT *cont );
static void FldOBJ_BlActCont_RegularAnmMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max );
static int FldOBJ_BlActCont_RegularAnmMaxGet( const FIELD_OBJ_BLACT_CONT *cont );
static void FldOBJ_BlActCont_GuestAnmMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max );
static int FldOBJ_BlActCont_GuestAnmMaxGet( const FIELD_OBJ_BLACT_CONT *cont );
static void FldOBJ_BlActCont_RegularTexMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max );
static int FldOBJ_BlActCont_RegularTexMaxGet( const FIELD_OBJ_BLACT_CONT *cont );
static void FldOBJ_BlActCont_GuestTexMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max );
static int FldOBJ_BlActCont_GuestTexMaxGet( const FIELD_OBJ_BLACT_CONT *cont );
//static void FldOBJ_BlActGuestAddTcbPtrSet( FIELD_OBJ_BLACT_CONT *cont, TCB_PTR tcb );	//iran
//static TCB_PTR FldOBJ_BlActGuestAddTcbPtrGet( FIELD_OBJ_BLACT_CONT *cont );	//iran
//static void FldOBJ_BlActContVIntrTcbPtrSet( FIELD_OBJ_BLACT_CONT *cont, TCB_PTR tcb ); //iran
//static TCB_PTR FldOBJ_BlActContVIntrTcbPtrGet( FIELD_OBJ_BLACT_CONT *cont );	//iran
static void * FldOBJ_BlActContArcDataAlloc( FIELD_OBJ_BLACT_CONT *cont, u32 datID, int fb );

static const FIELD_OBJ_BLACT_HEADER_ID * FldOBJ_BlActHeaderPathIDTblGet( int code );
static int FldOBJ_BlActH_OBJCode_MdlID( int code );
static int FldOBJ_BlActH_OBJCode_AnmID( int code );
static const BLACT_ANIME_TBL * FldOBJ_BlActH_OBJCode_AnmTbl( int code );

static void FldOBJ_BlActInit( FIELD_OBJ_BLACT_CONT *cont, int max);
static void FldOBJ_BlActDestSet( BLACT_SET_PTR set );
static BLACT_WORK_PTR FldOBJ_BlActAdd(
		BLACT_SET_PTR set, const BLACT_HEADER *head, const VecFx32 *vec );
static void FldOBJ_BlActHeaderLoad( FIELD_OBJ_BLACT_CONT * cont, u32 code, BLACT_HEADER *head );
static const FIELD_OBJ_BLACT_CONT * FldOBJ_BlActContGet( CONST_FIELD_OBJ_PTR fldobj );
static FIELD_OBJ_BLACT_CONT * FldOBJ_BlActContGetLocal( CONST_FIELD_OBJ_PTR fldobj );


//----
static int FldOBJ_TexLoadTransSet(
	FIELD_OBJ_BLACT_CONT *cont, int tex_id, u32 arc_id, REGULAR_GUEST reg_type );
static void FldOBJ_TexLoadReserveCancel( FIELD_OBJ_BLACT_CONT *cont, int tex_id );
static TEXREG_TYPE FldOBJ_TexLoadReserveCheck( FIELD_OBJ_BLACT_CONT *cont, int tex_id );
static void FldOBJ_TexLoadReserveTCB( TCB_PTR tcb, void *wk );
static void FldOBJ_TexBufTransSet(
	FIELD_OBJ_BLACT_CONT *cont, int tex_id, void *buf, REGULAR_GUEST reg_type );

static void FldOBJ_TexTransAdd( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_TexTransCancel( FIELD_OBJ_BLACT_CONT *cont, int id );
static void FldOBJ_TexTransVIntrTCB( TCB_PTR tcb, void *wk );
static void FldOBJ_TexFreeVWaitTCB( TCB_PTR tcb, void *wk );

static void FldOBJ_BlActAddReserveSet(
	FIELD_OBJ_BLACT_CONT *cont, FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR *act, int code );
static void FldOBJ_BlActAddReserveCancel(
	FIELD_OBJ_BLACT_CONT *cont, CONST_FIELD_OBJ_PTR fldobj );
static void FldOBJ_BlActAddReserveTCB( TCB_PTR tcb, void *wk );
static void FldOBJ_BlActAddReserve( FIELD_OBJ_BLACT_CONT *cont );
static void FldOBJ_BlActAddReserve_Add(
		FIELD_OBJ_BLACT_CONT *cont, BLACTADD_RESERVE *res );

static void FldOBJ_BlActVTransWorkInit( FIELD_OBJ_BLACT_CONT *cont, int max, int load_max );
static void FldOBJ_BlActVTransWorkDelete( FIELD_OBJ_BLACT_CONT *cont );
//----

//==============================================================================
//	�r���{�[�h�A�N�^�[�֘A
//==============================================================================
//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�R���g���[��������
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	max		�A�N�^�[�ő吔
 * @param	pri		�Q�X�g�r���{�[�h�A�N�^�[�ǉ��Ǘ�TCB�����v���C�I���e�B
 * @param	tex_max		�e�N�X�`���ő吔
 * @param	reg_tex_max	���M�����[�e�N�X�`���o�^�ő吔
 * @param	rg_tex_tbl	���M�����[�e�N�X�`���e�[�u��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActCont_Init(
		FIELD_OBJ_BLACT_CONT *cont,
		CONST_FIELD_OBJ_SYS_PTR fos,
		int max, int pri,
		int tex_max, int reg_tex_max, const int *rg_tex_tbl )
{
	cont->fos = fos;
	
	FldOBJ_BlActInit( cont, max );
	
	FldOBJ_BlActVTransWorkInit( cont, max, 10 );
	
	FldOBJ_BlActResManageInit( cont,
			FLDOBJ_RESM_MAX_MDL, FLDOBJ_RESM_REG_MAX_MDL,
			FLDOBJ_RESM_MAX_ANM, FLDOBJ_RESM_REG_MAX_ANM,
			tex_max, reg_tex_max );
	
	FldOBJ_BlActHeaderManageInit( cont, max );
	
	FldOBJ_BlActResm_RegularAdd_All(
			cont,
			rg_tex_tbl,
			DATA_FieldOBJ_Regular_Mdl,
			DATA_FieldOBJ_Regular_Anm );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�R���g���[���폜
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActCont_Delete( FIELD_OBJ_BLACT_CONT *cont )
{
	FldOBJ_BlActVTransWorkDelete( cont );
	
	FldOBJ_BlActHeaderManageDelete( cont );
	FldOBJ_BlActDestSet( FieldOBJ_BlActCont_SetPtrGet(cont) );
	FldOBJ_BlActResManageDelete( cont );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ����r���{�[�h�A�N�^�[�ǉ��B
 * fldobj�Ɋi�[����Ă���\���R�[�h�A���W����A�N�^�[�ǉ�����B
 * ���M�����[�A�Q�X�g�`�F�b�N���s���A�Q�X�g�̏ꍇ�̓Q�X�g�ǉ��e�[�u���֒ǉ��\��B
 * ���̊֐����Ă񂾍ہAact��NULL�ŏ����������B
 * �ǉ����ꎟ��Aact�֒ǉ����ꂽBLACT_WORK_PTR���i�[�����B
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	act			BLACT_WORK_PTR�i�[��
 * @param	code		�\������R�[�h�BHERO��
 * @retval	TEXREG_TYPE TEX_REGULAR���BTEX_REGULAR,TEX_GUEST�ȊO=�ǉ��e�[�u���֗\��B
 */
//--------------------------------------------------------------
TEXREG_TYPE FieldOBJ_BlActAddRegularGuestCode(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR *act, int code )
{
	TEXREG_TYPE ret;
	FIELD_OBJ_BLACT_CONT *cont;
	
	*act = NULL;
	cont = FldOBJ_BlActContGetLocal( fldobj );
	ret = FldOBJ_BlActResm_TexIDSearchAll( cont, code );
	
	if( ret == TEX_NON ){											//���O�o�^��������
		FieldOBJ_BlActAdd_Guest( fldobj, act, code );
		return( ret );
	}
	
	if( ret == TEX_REGULAR_RESERVE || ret == TEX_GUEST_RESERVE ){	//�e�N�X�`���]���\��A��
		FldOBJ_BlActAddReserveSet( cont, fldobj, act, code );
		return( ret );
	}
	
	*act = FieldOBJ_BlActAddCode( fldobj, code );
	return( ret );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ����r���{�[�h�A�N�^�[�ǉ��B
 * fldobj�Ɋi�[����Ă���\���R�[�h�A���W����A�N�^�[�ǉ�����B
 * OBJ�R�[�h�̓t�B�[���hOBJ������擾�B
 * ���M�����[�A�Q�X�g�`�F�b�N���s���A�Q�X�g�̏ꍇ�̓Q�X�g�ǉ��e�[�u���֒ǉ��\��B
 * ���̊֐����Ă񂾍ہAact��NULL�ŏ����������B
 * �ǉ����ꎟ��Aact�֒ǉ����ꂽBLACT_WORK_PTR���i�[�����B
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	act			BLACT_WORK_PTR�i�[��
 * @retval	TEXREG_TYPE TEX_REGULAR���BTEX_REGULAR,TEX_GUEST�ȊO=�ǉ��e�[�u���֗\��B 
 */
//--------------------------------------------------------------
TEXREG_TYPE FieldOBJ_BlActAddRegularGuest( FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR *act )
{
	int code = FieldOBJ_OBJCodeGet( fldobj );
	TEXREG_TYPE ret = FieldOBJ_BlActAddRegularGuestCode( fldobj, act, code );
	return( ret );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ����r���{�[�h�A�N�^�[�ǉ��B�\���R�[�h�w��B
 * fldobj�Ɋi�[����Ă���\���R�[�h�A���W����A�N�^�[�ǉ�
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	code		�\������R�[�h�BHERO��
 * @retval	BLACT_WORK 	NULL=�ǉ����s
 */
//--------------------------------------------------------------
BLACT_WORK_PTR FieldOBJ_BlActAddCode( FIELD_OBJ_PTR fldobj, int code )
{
	VecFx32 vec;
	BLACT_SET_PTR set;
	BLACT_WORK_PTR work;
	BLACT_HEADER *head;
	FIELD_OBJ_BLACT_CONT *cont;
	
	cont = FldOBJ_BlActContGetLocal( fldobj );
	set = FieldOBJ_BlActCont_SetPtrGet( cont );
	
	FldOBJ_BlActResManage_AllIDRegist( cont, code );
	head = FldOBJ_BlActHeaderManageGet( cont, code );
	GF_ASSERT( head != NULL && "FieldOBJ_BlActAddCode() HEADER MAKE ERROR" );
	
	FieldOBJ_DrawVecPosTotalGet( fldobj, &vec );
	
	work = FldOBJ_BlActAdd( set, head, &vec );
	GF_ASSERT( work != NULL && "FieldOBJ_BlActAddCode() BLACT ADD ERROR" );
	
	return( work );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�폜
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_HEADER
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActDeleteCode( CONST_FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR *act, int code )
{
	int ret;
	
	BLACT_Delete( *act );
	*act = NULL;
	
	ret = FldOBJ_OBJCodeUseSearch( FieldOBJ_FieldOBJSysGet(fldobj), fldobj, code );
	
	if( ret == FALSE ){
		FldOBJ_BlActHeaderManageFree( FldOBJ_BlActContGetLocal(fldobj), code );
	}
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�폜
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_HEADER
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActDelete( CONST_FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR *act )
{
	FldOBJ_BlActAdd_GuestCancel( fldobj );
	
	if( (*act) != NULL ){
		int code = FieldOBJ_OBJCodeGet( fldobj );
	
		if( FieldOBJ_OBJCodeSeedCheck(code) == TRUE ){
			code = FieldOBJ_OBJCodeSeedGet( fldobj );
		}
	
		FieldOBJ_BlActDeleteCode( fldobj, act, code );
	}
}	

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�폜
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_HEADER
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActDeleteCodeCancel( CONST_FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR *act, int code )
{
	int ret;
	
	FldOBJ_BlActAdd_GuestCancel( fldobj );
	
	if( (*act) != NULL ){
		BLACT_Delete( *act );
		*act = NULL;
	}
	
	if( code != OBJCODEMAX ){
		ret = FldOBJ_OBJCodeUseSearch( FieldOBJ_FieldOBJSysGet(fldobj), fldobj, code );
		
		if( ret == FALSE ){
			FldOBJ_BlActHeaderManageFree( FldOBJ_BlActContGetLocal(fldobj), code );
		}
	}
}	

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�A�j���ޔ��B
 * �A�j���[�V�������A�\���A��\���X�C�b�`�̑ޔ����s��
 * @param	act		BLACT_WORK_PTR 
 * @param	push	FIELD_OBJ_BLACTANM_PUSH *
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActAnmPush( BLACT_WORK_PTR act, FIELD_OBJ_BLACTANM_PUSH *push )
{
	push->vanish = BLACT_ObjDrawFlagGet( act );
	push->anm_offs = BLACT_AnmOffsGet( act );
	push->frame = BLACT_AnmFrameGet( act );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�A�j�����A�B
 * FieldOBJ_BlActAnmPush()�őޔ����������A�N�^�[�ɔ��f
 * @param	act		BLACT_WORK_PTR 
 * @param	push	FIELD_OBJ_BLACTANM_PUSH *
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActAnmPop( BLACT_WORK_PTR act, FIELD_OBJ_BLACTANM_PUSH *push )
{
	BLACT_ObjDrawFlagSet( act, push->vanish );
	BLACT_AnmOffsChg( act, push->anm_offs );
	BLACT_AnmFrameSet( act, push->frame );
}

//==============================================================================
//	�r���{�[�h�A�N�^�[�@�Q�X�g�ǉ�
//==============================================================================
//--------------------------------------------------------------
/**
 * �Q�X�g�r���{�[�h�A�N�^�[�ǉ��Ǘ��֗\��B
 * �Ă񂾍ہAact��NULL�ŏ������B
 * �Ǘ����Ńr���{�[�h�A�N�^�[���ǉ������Ƃ��̃A�h���X���i�[�����B
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		�ǉ����ꂽ�A�N�^�[�i�[��
 * @param	code	�\������OBJ�R�[�h HERO��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActAdd_Guest( FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR *act, int code )
{
	FIELD_OBJ_BLACT_CONT *cont = FldOBJ_BlActContGetLocal( fldobj );
	
	if( FldOBJ_BlActResm_GuestAdd_Tex(cont,code) == ADDRES_REGIST ){
		*act = FieldOBJ_BlActAddCode( fldobj, code );
	}else{
		FldOBJ_BlActAddReserveSet( cont, fldobj, act, code );
	}
}

//--------------------------------------------------------------
/**
 * �Q�X�g�r���{�[�h�A�N�^�[�ǉ��Ǘ��\��L�����Z��
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	code	�\������OBJ�R�[�h HERO��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActAdd_GuestCancel( CONST_FIELD_OBJ_PTR fldobj )
{
	FIELD_OBJ_BLACT_CONT *cont = FldOBJ_BlActContGetLocal( fldobj );
	FldOBJ_BlActAddReserveCancel( cont, fldobj );
}

#if 0
//--------------------------------------------------------------
/**
 * �Q�X�g�r���{�[�h�A�N�^�[�ǉ��Ǘ�TCB�ǉ�
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	pri		�ǉ��Ǘ�TCB�����v���C�I���e�B
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActGuestAddTcbAdd( FIELD_OBJ_BLACT_CONT *cont, int pri )
{
	TCB_PTR tcb;
	GUEST_BLACT_ADD_WORK *work;
	
	work = sys_AllocMemory( HEAPID_FIELD, GUEST_BLACT_ADD_WORK_ALL_SIZE );
	GF_ASSERT( work != NULL && "FldOBJ_BlActGuestAddTcbAdd alloc memory Error" );
	memset( work, NULL, GUEST_BLACT_ADD_WORK_ALL_SIZE );
	
	tcb = TCB_Add( FldOBJ_GuestBlActAddTcb, work, pri );
	GF_ASSERT( tcb != NULL && "FldOBJ_BlActGuestAddTcbAdd TCB_Add Error" );
	
	FldOBJ_BlActGuestAddTcbPtrSet( cont, tcb );
}
#endif

#if 0
//--------------------------------------------------------------
/**
 * �Q�X�g�r���{�[�h�A�N�^�[�ǉ��Ǘ�TCB�폜
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActGuestAddTcbDelete( FIELD_OBJ_BLACT_CONT *cont )
{
	TCB_PTR tcb;
	GUEST_BLACT_ADD_WORK *work;
	
	tcb = FldOBJ_BlActGuestAddTcbPtrGet( cont );
	
	if( tcb == NULL ){
		return;
	}
	
	work = TCB_GetWork( tcb );
	sys_FreeMemory( HEAPID_FIELD, work );
	
	TCB_Delete( tcb );
	
	FldOBJ_BlActGuestAddTcbPtrSet( cont, NULL );
}
#endif

#if 0
//--------------------------------------------------------------
/**
 * TCB �Q�X�g�r���{�[�h�A�N�^�[�ǉ��Ǘ�����
 * @param	tcb		TCB_PTR
 * @param	wk		work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_GuestBlActAddTcb( TCB_PTR tcb, void *wk )
{
	int i = 0,count = 0,i2,code;
	GUEST_BLACT_ADD_WORK *work = wk, *work2;
	
	do{
		if( work->fldobj != NULL ){
			*(work->act) = FieldOBJ_BlActAddCode( work->fldobj, work->code );
			GF_ASSERT(*(work->act)!=NULL&&"FldOBJ_GuestBlActAddTcb()Error");
			FieldOBJ_BlActAddPracFlagSet( work->fldobj, FALSE );
			
			if( FieldOBJ_StatusBit_CheckEasy(work->fldobj,FLDOBJ_STA_BIT_DRAW_PUSH) == TRUE ){
				FieldOBJ_DrawPopProcCall( work->fldobj );
			}else{
				FieldOBJ_DrawProcCall( work->fldobj );
			}
			
			{	//�ǉ�����OBJ�R�[�h�Ɠ���̂��̂𒼌�ɒǉ�
				i2 = i + 1;
				code = work->code;
				work2 = &work[1];
				
				while( i2 < FLDOBJ_RESM_MAX_TEX ){
					if( work2->fldobj != NULL && code == work2->code ){
						*(work2->act) = FieldOBJ_BlActAddCode( work2->fldobj, work2->code );
						GF_ASSERT(*(work2->act)!=NULL&&"FldOBJ_GuestBlActAddTcb()Error");
						FieldOBJ_BlActAddPracFlagSet( work2->fldobj, FALSE );
						
						if( FieldOBJ_StatusBit_CheckEasy(
							work2->fldobj,FLDOBJ_STA_BIT_DRAW_PUSH) == TRUE ){
							FieldOBJ_DrawPopProcCall( work2->fldobj );
						}else{
							FieldOBJ_DrawProcCall( work->fldobj );
						}
							
						work2->fldobj = NULL;
						work2->act = NULL;
					}
					
					work2++;
					i2++;
				}
			}
			
			work->fldobj = NULL;
			work->act = NULL;
			count++;
			
			if( count >= FLDOBJ_GUEST_BLACT_ADD_ONE_FRAME_MAX ){
				return;
			}
		}
		
		work++;
		i++;
	}while( i < FLDOBJ_RESM_MAX_TEX );
}
#endif

//==============================================================================
//	�r���{�[�h�A�N�^�[�w�b�_�[�Ǘ�
//==============================================================================
//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�w�b�_�[�Ǘ��̈�m��
 * @param	cont		FIELD_OBJ_BLACT_CONT*
 * @param	max			�w�b�_�[�ő吔
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActHeaderManageInit( FIELD_OBJ_BLACT_CONT *cont, int max )
{
	int i,head_size;
	BLACT_HEADER *head;
	FIELD_OBJ_BLACT_HEADER *manage;
	
	i = sizeof(BLACT_HEADER) * max;
	head = sys_AllocMemory( HEAPID_FIELD, i );
	cont->blact_head_tbl = head;
	GF_ASSERT( head != NULL && "fldobj blact header alloc memory error" );
	
	i = FIELD_OBJ_BLACT_HEADER_SIZE * max;
	manage = sys_AllocMemory( HEAPID_FIELD, i );
	cont->head_manage = manage;
	GF_ASSERT( manage != NULL && "fldobj blact header alloc memory error" );
	
	head_size = sizeof(BLACT_HEADER);
	
	do{
		manage->obj_code = OBJCODEMAX;
		manage->head = head;
		manage++;
		(u8 *)head += head_size;
		max--;
	}while( max );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�w�b�_�[�Ǘ��̈�폜
 * @param	cont		FIELD_OBJ_BLACT_CONT*
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActHeaderManageDelete( FIELD_OBJ_BLACT_CONT *cont )
{
	FldOBJ_BlActHeaderManageFreeForce( cont );
	
	sys_FreeMemory( HEAPID_FIELD, cont->blact_head_tbl );
	sys_FreeMemory( HEAPID_FIELD, cont->head_manage );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�w�b�_�[�Ǘ��̈�擾
 * @param	cont			FIELD_OBJ_BLACT_CONT
 * @param	code			�擾����OBJ�R�[�h�BHERO��
 * @retval	BLACT_HEADER	�w�b�_�[�̈�ւ�*�BNULL=���s
 */
//--------------------------------------------------------------
static BLACT_HEADER * FldOBJ_BlActHeaderManageGet( FIELD_OBJ_BLACT_CONT *cont, u32 code )
{
	int max;
	FIELD_OBJ_BLACT_HEADER *ma;
	
	ma = cont->head_manage;
	max = cont->max;
	
	do{
		if( ma->obj_code == code ){
			return( ma->head );
		}
		
		ma++;
		max--;
	}while( max );
	
	ma = cont->head_manage;
	max = cont->max;
	
	do{
		if( ma->obj_code == OBJCODEMAX ){
			ma->obj_code = code;
			FldOBJ_BlActHeaderLoad( cont, code, ma->head );
			return( ma->head );
		}
		
		ma++;
		max--;
	}while( max );
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�w�b�_�[�Ǘ��̈�擾�B�O���[�o��
 * @param	cont			FIELD_OBJ_BLACT_CONT
 * @param	code			�擾����OBJ�R�[�h�BHERO��
 * @param	head			�w�b�_�[���i�[��
 * @retval	int				TRUE=�i�[�����BFALSE=�o�^����Ă��Ȃ�
 */
//--------------------------------------------------------------
int FieldOBJ_BlActHeaderGetOBJCode( CONST_FIELD_OBJ_SYS_PTR fos, u32 code, BLACT_HEADER *head )
{
	int max;
	const FIELD_OBJ_BLACT_CONT *cont;
	FIELD_OBJ_BLACT_HEADER *ma;
	
	cont = FieldOBJSys_BlActContGet( fos );
	ma = cont->head_manage;
	max = cont->max;
	
	do{
		if( ma->obj_code == code ){
			*head = *(ma->head);
			return( TRUE );
		}
		
		ma++;
		max--;
	}while( max );
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�w�b�_�[�Ǘ��̈�J��
 * @param	cont			FIELD_OBJ_BLACT_CONT
 * @param	code			�J������OBJ�R�[�h�BHERO��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActHeaderManageFree( FIELD_OBJ_BLACT_CONT *cont, u32 code )
{
	int max;
	FIELD_OBJ_BLACT_HEADER *ma;
	
	ma = cont->head_manage;
	max = cont->max;
	
	do{
		if( ma->obj_code == code ){
			ma->obj_code = OBJCODEMAX;
//			BLACT_HeaderFree( ma->head );					//DEBUG_FLDOBJ_NEW_BLACT_HOOK
			OS_Printf( "FLDOBJ BLACT HEADER DELETE CODE = 0x%x\n", code );
			return;
		}
		
		ma++;
		max--;
	}while( max );	
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�w�b�_�[�Ǘ��̈拭���J��
 * @param	cont			FIELD_OBJ_BLACT_CONT
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActHeaderManageFreeForce( FIELD_OBJ_BLACT_CONT *cont )
{
	int max;
	FIELD_OBJ_BLACT_HEADER *ma;
	
	ma = cont->head_manage;
	max = cont->max;
	
	do{
		if( ma->obj_code != OBJCODEMAX ){
			ma->obj_code = OBJCODEMAX;
//			BLACT_HeaderFree( ma->head );						//DEBUG_FLDOBJ_NEW_BLACT_HOOK
		}
		
		ma++;
		max--;
	}while( max );
}

//--------------------------------------------------------------
/**
 * ���ݔ������Ă���t�B�[���hOBJ��OBJ�R�[�h���Q��
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	code		�`�F�b�N����R�[�h�BHERO��
 * @retval	int			TRUE=fldobj�ȊO�ɂ�code�������Ă���z������
 */
//--------------------------------------------------------------
static int FldOBJ_OBJCodeUseSearch(
		CONST_FIELD_OBJ_SYS_PTR sys, CONST_FIELD_OBJ_PTR fldobj, int code )
{
	int i,check_code;
	CONST_FIELD_OBJ_PTR fieldobj;
	
	i = FieldOBJSys_OBJMaxGet( sys );
	fieldobj = FieldOBJSys_FieldOBJWorkGet( sys );
	
	do{
		if( fieldobj != fldobj ){
			if( FieldOBJ_StatusBitCheck_Use(fieldobj) == TRUE ){
				check_code = FieldOBJ_OBJCodeGet( fieldobj );
					
				if( FieldOBJ_OBJCodeSeedCheck(check_code) == TRUE ){
					check_code = FieldOBJ_OBJCodeSeedGet( fieldobj );
				}
				
				if( check_code != OBJCODEMAX && check_code == code ){
					return( TRUE );
				}
			}
		}
		
		FieldOBJSys_FieldOBJWorkInc( &fieldobj );
		i--;
	}while( i );
	
	return( FALSE );
}

//==============================================================================
//	���\�[�X�}�l�[�W���ݒ�
//==============================================================================
//--------------------------------------------------------------
/**
 * ���\�[�X�}�l�[�W��������
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	mdl_max		���f���Ǘ��ő吔
 * @param	mdl_reg_max	���f���Ǘ����M�����[�ő吔
 * @param	anm_max		�A�j���Ǘ��ő吔
 * @param	anm_reg_max	�A�j���Ǘ����M�����[�ő吔
 * @param	tex_max		�e�N�X�`���Ǘ��ő吔
 * @param	tex_reg_max	�e�N�X�`�����M�����[�Ǘ��ő吔
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResManageInit( FIELD_OBJ_BLACT_CONT *cont,
		int mdl_max, int mdl_reg_max,
		int anm_max, int anm_reg_max,
		int tex_max, int tex_reg_max )
{
	
	{
		cont->lres_mdl = LRes_Init(
				HEAPID_FIELD,HEAPID_FIELD_FLDOBJ_MDL,
				FLDOBJ_LRES_SIZE_MDL * mdl_max,	mdl_max );
		
		FldOBJ_BlActResm_MdlIDInit( cont );
		FldOBJ_BlActCont_RegularMdlMaxSet( cont, mdl_reg_max );
		FldOBJ_BlActCont_GuestMdlMaxSet( cont, mdl_max - mdl_reg_max );
	}
	
	{
		cont->lres_anm = LRes_Init(
				HEAPID_FIELD, HEAPID_FIELD_FLDOBJ_ANM,
				FLDOBJ_LRES_SIZE_ANM * anm_max, anm_max );
	
		FldOBJ_BlActResm_AnmIDInit( cont );
		FldOBJ_BlActCont_RegularAnmMaxSet( cont, anm_reg_max );
		FldOBJ_BlActCont_GuestAnmMaxSet( cont, anm_max - anm_reg_max );
	}
	
	{
		TEXRES_MANAGER_PTR res;
			
		res = TEXRESM_Init( tex_max, HEAPID_FIELD );
		
		FieldOBJ_BlActCont_TexResManageSet( cont, res );
		FldOBJ_BlActResm_TexIDInit( cont );
		FldOBJ_BlActCont_RegularTexMaxSet( cont, tex_reg_max );
		FldOBJ_BlActCont_GuestTexMaxSet( cont, tex_max - tex_reg_max );
	}
}

//--------------------------------------------------------------
/**
 * ���\�[�X�}�l�[�W���S�폜
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	mdl_max	���f���Ǘ��ő吔
 * @param	anm_max	�A�j���Ǘ��ő吔
 * @param	tex_max	�e�N�X�`���Ǘ��ő吔
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResManageDelete( FIELD_OBJ_BLACT_CONT *cont )
{
	LRes_Delete( cont->lres_mdl );
	LRes_Delete( cont->lres_anm );
	TEXRESM_Delete( FieldOBJ_BlActCont_TexResManageGet(cont) );
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_RESMH����
 * @param	id				����ID
 * @param	tbl				�����e�[�u��
 * @retval	FIELD_OBJ_RESMH	��v����f�[�^�BNULL=��v����
 */
//--------------------------------------------------------------
static const FIELD_OBJ_RESMH * FldOBJ_BlActResmH_Search( int id, const FIELD_OBJ_RESMH *tbl )
{
	do{
		if( tbl->id == id ){
			return( tbl );
		}
		
		tbl++;
	}while( tbl->path != NULL );
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_RESMNARC����
 * @param	id				����ID
 * @param	max_id			�I�[ID
 * @param	tbl				�����e�[�u��
 * @retval	FIELD_OBJ_RESMNARC	��v����f�[�^�BNULL=��v����
 */
//--------------------------------------------------------------
static const FIELD_OBJ_RESMNARC * FldOBJ_BlActResmNArc_Search(
					int id, int max_id, const FIELD_OBJ_RESMNARC *tbl )
{
	do{
		if( tbl->id == id ){
			return( tbl );
		}
		
		tbl++;
	}while( tbl->id != max_id );
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * �w�肳�ꂽRES_MANAGER_PTR�AID�AFIELD_OBJ_RESMNARC����o�^
 * @param	resm	RES_MANAGER_PTR
 * @param	id		�o�^����ID
 * @param	max		tbl�I�[ID
 * @param	tbl		FIELD_OBJ_RESMH
 * @retval	int		TRUE=�o�^�BFALSE=�o�^�ς�
 */
//--------------------------------------------------------------
static int FldOBJ_BlActResmNArc_AddResTbl(
		FIELD_OBJ_BLACT_CONT *cont,
		RES_MANAGER_PTR resm, int id, int max, const FIELD_OBJ_RESMNARC *tbl )
{
	RES_OBJ_PTR res;
	const FIELD_OBJ_RESMNARC *head;
	
	if( RESM_CheckID(resm,id) == FALSE ){
		return( FALSE );
	}
	
	head = FldOBJ_BlActResmNArc_Search( id, max, tbl );
	GF_ASSERT( head != NULL && "fldobj resm add res search error" );
	
	{
		void *arc_ptr = FldOBJ_BlActContArcDataAlloc( cont, head->narc_id, TRUE );
		res = RESM_AddResNormal( resm, arc_ptr, id );
		GF_ASSERT( res != NULL && "fldobj resm add error" );
	}
	
	return( TRUE );
}

static int FldOBJ_BlActLResNArc_AddResTbl(
		FIELD_OBJ_BLACT_CONT *cont,
		LRES *lres_sys, int id, int max, const FIELD_OBJ_RESMNARC *tbl )
{
	const FIELD_OBJ_RESMNARC *head;
	
	if( LRes_IDResCheck(lres_sys,id) == TRUE ){
		return( FALSE );
	}
	
	head = FldOBJ_BlActResmNArc_Search( id, max, tbl );
	GF_ASSERT( head != NULL && "fldobj resm add res search error" );
	
	{
		ARCHANDLE *handle = FieldOBJSys_ArcHandleGet( cont->fos );
		LResUtil_AllocIDArcLoad( lres_sys, id, handle, head->narc_id, ALLOC_FR );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �w�肳�ꂽRES_MANAGER_PTR�AID�AFIELD_OBJ_RESMH����o�^
 * @param	resm	RES_MANAGER_PTR
 * @param	id		�o�^����ID
 * @param	tbl		FIELD_OBJ_RESMH
 * @retval	int		TRUE=�o�^�BFALSE=�o�^�ς�
 */
//--------------------------------------------------------------
static int FldOBJ_BlActResm_AddResTbl(
		RES_MANAGER_PTR resm, int id, const FIELD_OBJ_RESMH *tbl )
{
	RES_OBJ_PTR res;
	const FIELD_OBJ_RESMH *head;
	
	if( RESM_CheckID(resm,id) == FALSE ){
		return( FALSE );
	}
	
	head = FldOBJ_BlActResmH_Search( id, tbl );
	GF_ASSERT( head != NULL && "fldobj resm add res search error" );
	
	res = RESM_AddRes( resm, head->path, id, HEAPID_FIELD );
	GF_ASSERT( res != NULL && "fldobj resm add error" );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �w�肳�ꂽRES_MANAGER_PTR�AID�AFIELD_OBJ_RESMH����o�^ Noraml
 * @param	resm	RES_MANAGER_PTR
 * @param	id		�o�^����ID
 * @param	tbl		FIELD_OBJ_RESMH
 * @retval	int		TRUE=�o�^�BFALSE=�o�^�ς�
 */
//--------------------------------------------------------------
static int FldOBJ_BlActResm_AddResNormalTbl(
		RES_MANAGER_PTR resm, int id, const FIELD_OBJ_RESMH *tbl )
{
	void *file_ram;
	RES_OBJ_PTR res;
	const FIELD_OBJ_RESMH *head;
	
	if( RESM_CheckID(resm,id) == FALSE ){
		return( FALSE );
	}
	
	head = FldOBJ_BlActResmH_Search( id, tbl );
	GF_ASSERT( head != NULL && "fldobj resm add res search error" );
	
	file_ram = sys_LoadFile( HEAPID_FIELD, head->path );
	res = RESM_AddResNormal( resm, file_ram, id );
	GF_ASSERT( res != NULL && "fldobj resm add error" );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �w�肳�ꂽ�e�N�X�`��ID�AFIELD_OBJ_RESMNARC����o�^
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	reg_type	REGULAR_GUEST
 * @param	id			�o�^����ID
 * @param	tbl			FIELD_OBJ_RESMNARC
 * @retval	int			ADDRES_FALSE��
 */
//--------------------------------------------------------------
static ADDRES_TYPE FldOBJ_BlActTexResmNArc_AddResTbl( FIELD_OBJ_BLACT_CONT *cont,
		REGULAR_GUEST reg_type, int id, const FIELD_OBJ_RESMNARC *tbl )
{
	TEXRES_MANAGER_PTR resm = cont->tex_res_manage;
	
	if( TEXRESM_CheckID(resm,id) == FALSE ){						//�o�^�ς�
		return( ADDRES_REGIST );
	}
	
	if( FldOBJ_TexLoadReserveCheck(cont,id) != TEX_NON ){			//�\��A��
		return( ADDRES_RESERVE );
	}
	
	{
		TEXRES_OBJ_PTR res;
		const FIELD_OBJ_RESMNARC *head = FldOBJ_BlActResmNArc_Search( id, OBJCODEMAX, tbl );
		
		if( head == NULL ){
			return( ADDRES_NOTBLACT );
		}
		
		if( FldOBJ_TexLoadTransSet(cont,id,head->narc_id,reg_type) == TRUE ){
			return( ADDRES_REGIST );								//���̏�œo�^�ł���
		}
		
		return( ADDRES_RESERVE );									//�o�^�\��
	}
}

//--------------------------------------------------------------
/**
 * ���M�����[�e�N�X�`���o�^
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		�o�^����ID
 * @retval	ADDRES_TYPE ADDRES_TYPE
 */
//--------------------------------------------------------------
static ADDRES_TYPE FldOBJ_BlActResm_RegularAdd_Tex( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	return( FldOBJ_BlActTexResmNArc_AddResTbl(cont,REGULAR,id,DATA_FieldOBJ_ResmNArcTbl_Tex) );
}

//--------------------------------------------------------------
/**
 * ���M�����[�e�N�X�`���o�^�@�O���[�o��
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	id		�o�^����ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActResmRegularAdd_Tex( CONST_FIELD_OBJ_SYS_PTR fos, int id )
{
	RES_MANAGER_PTR resm;
	FIELD_OBJ_BLACT_CONT *cont;
	
	cont = (FIELD_OBJ_BLACT_CONT *)FieldOBJSys_BlActContGet( fos );
	
	if( FldOBJ_BlActResm_TexIDSearchAll(cont,id) == TEX_NON ){
		FldOBJ_BlActResm_RegularAdd_Tex( cont, id );
	}
}

//--------------------------------------------------------------
/**
 * ���M�����[�e�N�X�`���폜
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	id		�폜����ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActResmRegularDelete_Tex( CONST_FIELD_OBJ_SYS_PTR fos, int id )
{
	int max;
	int *tbl;
	FIELD_OBJ_BLACT_CONT *cont;
	
	cont = (FIELD_OBJ_BLACT_CONT *)FieldOBJSys_BlActContGet( fos );
	TEXRESM_DeleteResID( FieldOBJ_BlActCont_TexResManageGet(cont), id );
	
	tbl = FldOBJ_BlActCont_ResmTexIDTblGet( cont );
	max = FldOBJ_BlActCont_RegularTexMaxGet( cont );
	FldOBJ_BlActResm_IDTblDel( tbl, id, OBJCODEMAX, max );
	
	FldOBJ_TexLoadReserveCancel( cont, id );
	FldOBJ_TexTransCancel( cont, id );
}

//--------------------------------------------------------------
/**
 * �Q�X�g�e�N�X�`���o�^
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		�o�^����ID
 * @retval	ADDRES_TYPE ADDRES_TYPE
 */
//--------------------------------------------------------------
static ADDRES_TYPE FldOBJ_BlActResm_GuestAdd_Tex( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	return( FldOBJ_BlActTexResmNArc_AddResTbl(cont,GUEST,id,DATA_FieldOBJ_ResmNArcTbl_Tex) );
}

//--------------------------------------------------------------
/**
 * ���M�����[�e�N�X�`�������o�^
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	tbl		�o�^����ID���Z�߂�ꂽ�e�[�u��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_RegularAddTbl_Tex( FIELD_OBJ_BLACT_CONT *cont, const int *tbl )
{
	while( (*tbl) != OBJCODEMAX ){
		FldOBJ_BlActResm_RegularAdd_Tex( cont, (*tbl) );
		tbl++;
	}
//	sys_PrintHeapExistMemoryInfo( HEAPID_FIELD );
}

//--------------------------------------------------------------
/**
 * ���M�����[���f���o�^
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		�o�^����ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_RegularAdd_Mdl( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	RES_MANAGER_PTR resm;
	
	resm = FieldOBJ_BlActCont_MdlResManageGet( cont );
	FldOBJ_BlActLResNArc_AddResTbl(
			cont, cont->lres_mdl, id, BLACT_MDLID_MAX, DATA_FieldOBJ_ResmNArcTbl_Mdl );
	FldOBJ_BlActResm_MdlIDReg_Regular( cont, id );
}

//--------------------------------------------------------------
/**
 * �Q�X�g���f���o�^
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		�o�^����ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_GuestAdd_Mdl( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	RES_MANAGER_PTR resm;
	
#ifdef PM_DEBUG
	OS_Printf( "FldOBJ Mdl Add Guest ID=0x%x\n", id );
#endif
	
	resm = FieldOBJ_BlActCont_MdlResManageGet( cont );
	
	FldOBJ_BlActLResNArc_AddResTbl(
			cont, cont->lres_mdl, id, BLACT_MDLID_MAX, DATA_FieldOBJ_ResmNArcTbl_Mdl );
	FldOBJ_BlActResm_MdlIDReg_Guest( cont, id );
}

//--------------------------------------------------------------
/**
 * ���M�����[���f�������o�^
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	tbl		�o�^����ID���Z�߂�ꂽ�e�[�u��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_RegularAddTbl_Mdl( FIELD_OBJ_BLACT_CONT *cont, const int *tbl )
{
	while( (*tbl) != BLACT_MDLID_MAX ){
		FldOBJ_BlActResm_RegularAdd_Mdl( cont, (*tbl) );
		tbl++;
	}
}

//--------------------------------------------------------------
/**
 * ���M�����[�A�j���o�^
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		�o�^����ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_RegularAdd_Anm( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	RES_MANAGER_PTR resm;
	
	resm = FieldOBJ_BlActCont_AnmResManageGet( cont );
	
	FldOBJ_BlActLResNArc_AddResTbl(
		cont, cont->lres_anm, id, BLACT_ANMID_MAX, DATA_FieldOBJ_ResmNArcTbl_Anm );
	
	FldOBJ_BlActResm_AnmIDReg_Regular( cont, id );
}

//--------------------------------------------------------------
/**
 * ���M�����[�A�j���o�^�@�O���[�o��
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	id		�o�^����ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActResmRegularAdd_Anm( CONST_FIELD_OBJ_SYS_PTR fos, int id )
{
	RES_MANAGER_PTR resm;
	FIELD_OBJ_BLACT_CONT *cont = (FIELD_OBJ_BLACT_CONT *)FieldOBJSys_BlActContGet( fos );
	
	if( FldOBJ_BlActResm_AnmIDSearch_Regular(cont,id) == FALSE ){
		FldOBJ_BlActResm_RegularAdd_Anm( cont, id );
	}else{
		OS_Printf( "FieldOBJ_BlActResmRegularAdd_Anm() Add Settled\n" );
	}
}

//--------------------------------------------------------------
/**
 * ���M�����[�A�j���폜
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	id		�폜����ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActResmRegularDelete_Anm( CONST_FIELD_OBJ_SYS_PTR fos, int id )
{
	int max;
	int *tbl;
	FIELD_OBJ_BLACT_CONT *cont;
	
	cont = (FIELD_OBJ_BLACT_CONT *)FieldOBJSys_BlActContGet( fos );
	
	LRes_FreeID( cont->lres_anm, id );
	
	tbl = FldOBJ_BlActCont_ResmAnmIDTblGet( cont );
	max = FldOBJ_BlActCont_RegularAnmMaxGet( cont );
	FldOBJ_BlActResm_IDTblDel( tbl, id, BLACT_ANMID_MAX, max );
}

//--------------------------------------------------------------
/**
 * �Q�X�g�A�j���o�^
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		�o�^����ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_GuestAdd_Anm( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	RES_MANAGER_PTR resm;
	
#ifdef PM_DEBUG
	OS_Printf( "FldOBJ Anm Add Guest ID=0x%x\n", id );
#endif
	
	resm = FieldOBJ_BlActCont_AnmResManageGet( cont );
	
	FldOBJ_BlActLResNArc_AddResTbl(
		cont, cont->lres_anm, id, BLACT_ANMID_MAX, DATA_FieldOBJ_ResmNArcTbl_Anm );
	
	FldOBJ_BlActResm_AnmIDReg_Guest( cont, id );
}

//--------------------------------------------------------------
/**
 * ���M�����[�A�j�������o�^
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	tbl		�o�^����ID���Z�߂�ꂽ�e�[�u��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_RegularAddTbl_Anm( FIELD_OBJ_BLACT_CONT *cont, const int *tbl )
{
	while( (*tbl) != BLACT_ANMID_MAX ){
		FldOBJ_BlActResm_RegularAdd_Anm( cont, (*tbl) );
		tbl++;
	}
}

//--------------------------------------------------------------
/**
 * ���M�����[����ēo�^
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	tex_tbl	���M�����[�e�N�X�`��
 * @param	mdl_tbl	���M�����[�e�N�X�`��
 * @param	anm_tbl	���M�����[�e�N�X�`��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_RegularAdd_All(
	FIELD_OBJ_BLACT_CONT *cont, const int *tex_tbl, const int *mdl_tbl, const int *anm_tbl )
{
	FldOBJ_BlActResm_RegularAddTbl_Tex( cont, tex_tbl );
	FldOBJ_BlActResm_RegularAddTbl_Mdl( cont, mdl_tbl );
	FldOBJ_BlActResm_RegularAddTbl_Anm( cont, anm_tbl );
}

//--------------------------------------------------------------
/**
 * ���\�[�XID�Ǘ��@������
 * @param	tbl		ID�e�[�u���@*
 * @param	init_id	������ID
 * @param	max		��������
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_IDTblInit( int *tbl, int init_id, int max )
{
	do{
		*tbl = init_id;
		tbl++;
		max--;
	}while( max );
}

//--------------------------------------------------------------
/**
 * ���\�[�XID�Ǘ��@�o�^
 * @param	tbl		ID�e�[�u���@*
 * @param	reg_id	�o�^ID
 * @param	spc_id�@��ID
 * @param	max		������
 * @retval	int		TRUE=�o�^�@FALSE=�󂫖���
 */
//--------------------------------------------------------------
static int FldOBJ_BlActResm_IDTblReg( int *tbl, int reg_id, int spc_id, int max )
{
	do{
		if( (*tbl) == spc_id ){
			*tbl = reg_id;
			return( TRUE );
		}
		
		tbl++;
		max--;
	}while( max );
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���\�[�XID�Ǘ��@����
 * @param	tbl		ID�e�[�u���@*
 * @param	chk_id	����ID
 * @param	max		������
 * @retval	int		TRUE=�o�^�A���@FALSE=�o�^�i�V
 */
//--------------------------------------------------------------
static int FldOBJ_BlActResm_IDTblSearch( int *tbl, int chk_id, int max )
{
	do{
		if( (*tbl) == chk_id ){
			return( TRUE );
		}
		
		tbl++;
		max--;
	}while( max );
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���\�[�XID�Ǘ��@�폜
 * @param	tbl		ID�e�[�u���@*
 * @param	del_id		�폜����ID
 * @param	spc_id	�폜��̋�ID
 * @param	max		������
 * @retval	int		TRUE=�폜�����@FALSE=�o�^�i�V
 */
//--------------------------------------------------------------
static int FldOBJ_BlActResm_IDTblDel( int *tbl, int del_id, int spc_id, int max )
{
	do{
		if( (*tbl) == del_id ){
			*tbl = spc_id;
			return( TRUE );
		}
		
		tbl++;
		max--;
	}while( max );
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���f�����\�[�XID�Ǘ��@�e�[�u��������
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_MdlIDInit( FIELD_OBJ_BLACT_CONT *cont )
{
	int *tbl;
	
	tbl = FldOBJ_BlActCont_ResmMdlIDTblGet( cont );
	FldOBJ_BlActResm_IDTblInit( tbl, BLACT_MDLID_MAX, FLDOBJ_RESM_MAX_MDL );
}

//--------------------------------------------------------------
/**
 * ���f�����\�[�XID�Ǘ��@���M�����[�o�^�B
 * �󂫂������ꍇ��GF_ASSERT()
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			�o�^ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_MdlIDReg_Regular( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int max,ret;
	int *tbl;
	
	max = FldOBJ_BlActCont_RegularMdlMaxGet( cont );
	tbl = FldOBJ_BlActCont_ResmMdlIDTblGet( cont );
	
	ret = FldOBJ_BlActResm_IDTblReg( tbl, id, BLACT_MDLID_MAX, max );
	GF_ASSERT( ret != FALSE && "fldobj FldOBJ_BlActResm_RegRegID MAX" );
}

//--------------------------------------------------------------
/**
 * ���f�����\�[�XID�Ǘ��@���M�����[����
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			����ID
 * @retval	int			TRUE=�o�^�ς�ID FALSE=��v����
 */
//--------------------------------------------------------------
static int FldOBJ_BlActResm_MdlIDSearch_Regular( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int max;
	int *tbl;
	
	max = FldOBJ_BlActCont_RegularMdlMaxGet( cont );
	tbl = FldOBJ_BlActCont_ResmMdlIDTblGet( cont );
	return( FldOBJ_BlActResm_IDTblSearch(tbl,id,max) );
}

//--------------------------------------------------------------
/**
 * ���f�����\�[�XID�Ǘ��@�Q�X�g�o�^�B
 * �󂫂������ꍇ��GF_ASSERT()
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			�o�^ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_MdlIDReg_Guest( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int ret,max;
	int *tbl;
	
	tbl = FldOBJ_BlActCont_ResmMdlIDTblGet( cont );
	tbl = &tbl[FldOBJ_BlActCont_RegularMdlMaxGet(cont)];
	max = FldOBJ_BlActCont_GuestMdlMaxGet( cont );
	ret = FldOBJ_BlActResm_IDTblReg( tbl, id, BLACT_MDLID_MAX, max );
	
	GF_ASSERT( ret != FALSE && "fldobj FldOBJ_BlActResm_RegIDGuest MAX" );
}

//--------------------------------------------------------------
/**
 * ���f�����\�[�XID�Ǘ��@�Q�X�g����
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			����ID
 * @retval	int			TRUE=�o�^�ς�ID FALSE=��v����
 */
//--------------------------------------------------------------
static int FldOBJ_BlActResm_MdlIDSearch_Guest( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int max;
	int *tbl;
	
	tbl = FldOBJ_BlActCont_ResmMdlIDTblGet( cont );
	tbl = &tbl[FldOBJ_BlActCont_RegularMdlMaxGet(cont)];
	max = FldOBJ_BlActCont_GuestMdlMaxGet( cont );
	
	return( FldOBJ_BlActResm_IDTblSearch(tbl,id,max) );
}

//--------------------------------------------------------------
/**
 * ���f�����\�[�XID�Ǘ��@�Q�X�g�폜
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			�폜ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_MdlIDDelete_Guest( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int max;
	int *tbl;
	
	tbl = FldOBJ_BlActCont_ResmMdlIDTblGet( cont );
	tbl = &tbl[FldOBJ_BlActCont_RegularMdlMaxGet(cont)];
	max = FldOBJ_BlActCont_GuestMdlMaxGet( cont );
	
	FldOBJ_BlActResm_IDTblDel( tbl, id, BLACT_MDLID_MAX, max );
}

//--------------------------------------------------------------
/**
 * ���f�����\�[�XID�Ǘ��@�S�Q�X�g�폜�B��������OBJ���Ŏg�p���Ă���ꍇ�͍폜����
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_MdlIDDelete_GuestAll(
		FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_BLACT_CONT *cont )
{
	int max;
	int *tbl;
	RES_MANAGER_PTR resm;
	
	resm = FieldOBJ_BlActCont_MdlResManageGet( cont );
	tbl = FldOBJ_BlActCont_ResmMdlIDTblGet( cont );
	tbl = &tbl[FldOBJ_BlActCont_RegularMdlMaxGet(cont)];
	max = FldOBJ_BlActCont_GuestMdlMaxGet( cont );
	
	do{
		if( (*tbl) != BLACT_MDLID_MAX ){
			if( FldOBJ_BlActCont_FldOBJSearch_MdlID(fos,(*tbl),NULL) == FALSE ){
				OS_Printf( "FldOBJ Mdl Delete Guest ID=0x%x\n", *tbl );
				LRes_FreeID( cont->lres_mdl, *tbl );
				*tbl = BLACT_MDLID_MAX;
			}
		}
		
		tbl++;
		max--;
	}while( max );
}

//--------------------------------------------------------------
/**
 * ���f�����\�[�XID�Ǘ��@�Q�X�g�폜�B��������OBJ���Ŏg�p���Ă���ꍇ�͍폜����
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_MdlIDCheckDelete_Guest(
		CONST_FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_BLACT_CONT *cont, int id )
{
	if( FldOBJ_BlActCont_FldOBJSearch_MdlID(fos,id,NULL) == FALSE ){
		OS_Printf( "FldOBJ Mdl Delete Guest ID=0x%x\n", id );
		LRes_FreeID( cont->lres_mdl, id );
		FldOBJ_BlActResm_MdlIDDelete_Guest( cont, id );
	}
}

//--------------------------------------------------------------
/**
 * ���f�����\�[�XID�Ǘ��@�Q�X�g�폜�B��������OBJ���Ŏg�p���Ă���ꍇ�͍폜�����B�O���[�o��
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActResm_MdlIDCheckDelete_Guest( CONST_FIELD_OBJ_SYS_PTR fos, int id )
{
	FIELD_OBJ_BLACT_CONT *cont = FieldOBJSys_BlActContGet( fos );
	FldOBJ_BlActResm_MdlIDCheckDelete_Guest( fos, cont, id );
}

//--------------------------------------------------------------
/**
 * �A�j�����\�[�XID�Ǘ��@�e�[�u��������
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_AnmIDInit( FIELD_OBJ_BLACT_CONT *cont )
{
	int *tbl;
	
	tbl = FldOBJ_BlActCont_ResmAnmIDTblGet( cont );
	FldOBJ_BlActResm_IDTblInit( tbl, BLACT_ANMID_MAX, FLDOBJ_RESM_MAX_ANM );
}

//--------------------------------------------------------------
/**
 * �A�j�����\�[�XID�Ǘ��@���M�����[�o�^�B
 * �󂫂������ꍇ��GF_ASSERT()
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			�o�^ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_AnmIDReg_Regular( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int max,ret;
	int *tbl;
	
	max = FldOBJ_BlActCont_RegularAnmMaxGet( cont );
	tbl = FldOBJ_BlActCont_ResmAnmIDTblGet( cont );
	
	ret = FldOBJ_BlActResm_IDTblReg( tbl, id, BLACT_ANMID_MAX, max );
	GF_ASSERT( ret != FALSE && "fldobj FldOBJ_BlActResm_RegRegID MAX" );
}

//--------------------------------------------------------------
/**
 * �A�j�����\�[�XID�Ǘ��@���M�����[����
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			����ID
 * @retval	int			TRUE=�o�^�ς�ID FALSE=��v����
 */
//--------------------------------------------------------------
static int FldOBJ_BlActResm_AnmIDSearch_Regular( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int max;
	int *tbl;
	
	max = FldOBJ_BlActCont_RegularAnmMaxGet( cont );
	tbl = FldOBJ_BlActCont_ResmAnmIDTblGet( cont );
	return( FldOBJ_BlActResm_IDTblSearch(tbl,id,max) );
}

//--------------------------------------------------------------
/**
 * �A�j�����\�[�XID�Ǘ��@�Q�X�g�o�^�B
 * �󂫂������ꍇ��GF_ASSERT()
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			�o�^ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_AnmIDReg_Guest( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int ret,max;
	int *tbl;
	
	tbl = FldOBJ_BlActCont_ResmAnmIDTblGet( cont );
	tbl = &tbl[FldOBJ_BlActCont_RegularAnmMaxGet(cont)];
	max = FldOBJ_BlActCont_GuestAnmMaxGet( cont );
	ret = FldOBJ_BlActResm_IDTblReg( tbl, id, BLACT_ANMID_MAX, max );
	
	GF_ASSERT( ret != FALSE && "fldobj FldOBJ_BlActResm_RegIDGuest MAX" );
}

//--------------------------------------------------------------
/**
 * �A�j�����\�[�XID�Ǘ��@�Q�X�g����
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			����ID
 * @retval	int			TRUE=�o�^�ς�ID FALSE=��v����
 */
//--------------------------------------------------------------
static int FldOBJ_BlActResm_AnmIDSearch_Guest( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int max;
	int *tbl;
	
	tbl = FldOBJ_BlActCont_ResmAnmIDTblGet( cont );
	tbl = &tbl[FldOBJ_BlActCont_RegularAnmMaxGet(cont)];
	max = FldOBJ_BlActCont_GuestAnmMaxGet( cont );
	return( FldOBJ_BlActResm_IDTblSearch(tbl,id,max) );
}

//--------------------------------------------------------------
/**
 * �A�j�����\�[�XID�Ǘ��@�Q�X�g�폜
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			�폜ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_AnmIDDelete_Guest( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int max;
	int *tbl;
	
	tbl = FldOBJ_BlActCont_ResmAnmIDTblGet( cont );
	tbl = &tbl[FldOBJ_BlActCont_RegularAnmMaxGet(cont)];
	max = FldOBJ_BlActCont_GuestAnmMaxGet( cont );
	FldOBJ_BlActResm_IDTblDel( tbl, id, BLACT_ANMID_MAX, max );
}

//--------------------------------------------------------------
/**
 * �A�j�����\�[�XID�Ǘ��@�S�Q�X�g�폜�@��������OBJ�Ŏg�p���Ă���ꍇ�͍폜���Ȃ�
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_AnmIDDelete_GuestAll(
		FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_BLACT_CONT *cont )
{
	int max;
	int *tbl;
	RES_MANAGER_PTR resm;
	
	resm = FieldOBJ_BlActCont_AnmResManageGet( cont );
	tbl = FldOBJ_BlActCont_ResmAnmIDTblGet( cont );
	tbl = &tbl[FldOBJ_BlActCont_RegularAnmMaxGet(cont)];
	max = FldOBJ_BlActCont_GuestAnmMaxGet( cont );
	
	do{
		if( (*tbl) != BLACT_ANMID_MAX ){
			if( FldOBJ_BlActCont_FldOBJSearch_AnmID(fos,(*tbl),NULL) == FALSE ){
				OS_Printf( "FldOBJ Anm Delete Guest ID=0x%x\n", *tbl );
				LRes_FreeID( cont->lres_anm, *tbl );
				*tbl = BLACT_ANMID_MAX;
			}
		}
		
		tbl++;
		max--;
	}while( max );
}

//--------------------------------------------------------------
/**
 * �e�N�X�`�����\�[�XID�Ǘ��@�e�[�u��������
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_TexIDInit( FIELD_OBJ_BLACT_CONT *cont )
{
	int *tbl;
	
	tbl = FldOBJ_BlActCont_ResmTexIDTblGet( cont );
	FldOBJ_BlActResm_IDTblInit( tbl, OBJCODEMAX, FLDOBJ_RESM_MAX_TEX );
}

//--------------------------------------------------------------
/**
 * �e�N�X�`�����\�[�XID�Ǘ��@���M�����[�o�^�B
 * �󂫂������ꍇ��GF_ASSERT()
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			�o�^ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_TexIDReg_Regular( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int max,ret;
	int *tbl;
	
	max = FldOBJ_BlActCont_RegularTexMaxGet( cont );
	tbl = FldOBJ_BlActCont_ResmTexIDTblGet( cont );
	
	ret = FldOBJ_BlActResm_IDTblReg( tbl, id, OBJCODEMAX, max );
	GF_ASSERT( ret != FALSE && "fldobj FldOBJ_BlActResm_RegRegID MAX" );
}

//--------------------------------------------------------------
/**
 * �e�N�X�`�����\�[�X�\�[�XID�Ǘ��@���M�����[����
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			����ID
 * @retval	int			TRUE=�o�^�ς�ID FALSE=��v����
 */
//--------------------------------------------------------------
static int FldOBJ_BlActResm_TexIDSearch_Regular( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int max;
	int *tbl;
	
	max = FldOBJ_BlActCont_RegularTexMaxGet( cont );
	tbl = FldOBJ_BlActCont_ResmTexIDTblGet( cont );
	return( FldOBJ_BlActResm_IDTblSearch(tbl,id,max) );
}

//--------------------------------------------------------------
/**
 * �e�N�X�`�����\�[�X�\�[�XID�Ǘ��@��������
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			����ID
 * @retval	TEXREG_TYPE	TEXREG_TYPE
 */
//--------------------------------------------------------------
static TEXREG_TYPE FldOBJ_BlActResm_TexIDSearchAll( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	if( FldOBJ_BlActResm_TexIDSearch_Regular(cont,id) == TRUE ){
		return( TEX_REGULAR );
	}
	
	if( FldOBJ_BlActResm_TexIDSearch_Guest(cont,id) == TRUE ){
		return( TEX_GUEST );
	}
	
	return( FldOBJ_TexLoadReserveCheck(cont,id) );
}

//--------------------------------------------------------------
/**
 * �e�N�X�`�����\�[�XID�Ǘ��@�Q�X�g�o�^�B
 * �󂫂������ꍇ��GF_ASSERT()
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			�o�^ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_TexIDReg_Guest( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int ret,max;
	int *tbl;
	
	tbl = FldOBJ_BlActCont_ResmTexIDTblGet( cont );
	tbl = &tbl[FldOBJ_BlActCont_RegularTexMaxGet(cont)];
	max = FldOBJ_BlActCont_GuestTexMaxGet( cont );
	ret = FldOBJ_BlActResm_IDTblReg( tbl, id, OBJCODEMAX, max );
	
	GF_ASSERT( ret != FALSE && "fldobj FldOBJ_BlActResm_RegIDGuest MAX" );
}

//--------------------------------------------------------------
/**
 * �e�N�X�`�����\�[�XID�Ǘ��@�Q�X�g�폜
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			�폜ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_TexIDDelete_Guest( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int max;
	int *tbl;
	
	tbl = FldOBJ_BlActCont_ResmTexIDTblGet( cont );
	tbl = &tbl[FldOBJ_BlActCont_RegularTexMaxGet(cont)];
	max = FldOBJ_BlActCont_GuestTexMaxGet( cont );
	
	FldOBJ_BlActResm_IDTblDel( tbl, id, OBJCODEMAX, max );
}

//--------------------------------------------------------------
/**
 * �e�N�X�`�����\�[�XID�Ǘ��@�S�Q�X�g�폜�B�������Ă���OBJ�Ŏg�p���Ă���ꍇ�͍폜���Ȃ�
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResm_TexIDDelete_GuestAll(
		FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_BLACT_CONT *cont )
{
	int max,id;
	int *tbl;
	TEXRES_MANAGER_PTR resm;
	
	resm = FieldOBJ_BlActCont_TexResManageGet( cont );
	tbl = FldOBJ_BlActCont_ResmTexIDTblGet( cont );
	tbl = &tbl[FldOBJ_BlActCont_RegularTexMaxGet(cont)];
	max = FldOBJ_BlActCont_GuestTexMaxGet( cont );
	
	do{
		id = *tbl;
		
		if( id != OBJCODEMAX ){
			if( FldOBJ_BlActCont_FldOBJSearch_OBJCode(fos,id,NULL) == FALSE ){
				TEXRESM_DeleteResID( resm, id );
				FldOBJ_TexLoadReserveCancel( cont, id );
				FldOBJ_TexTransCancel( cont, id );
				OS_Printf( "FldOBJ Tex Delete Guest ID=0x%x\n", *tbl );
				*tbl = OBJCODEMAX;
			}
		}
		
		tbl++;
		max--;
	}while( max );
}

//--------------------------------------------------------------
/**
 * �e�N�X�`�����\�[�X�\�[�XID�Ǘ��@�Q�X�g����
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			����ID
 * @retval	int			TRUE=�o�^�ς�ID FALSE=��v����
 */
//--------------------------------------------------------------
static int FldOBJ_BlActResm_TexIDSearch_Guest( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int max;
	int *tbl;
	
	tbl = FldOBJ_BlActCont_ResmTexIDTblGet( cont );
	tbl = &tbl[FldOBJ_BlActCont_RegularTexMaxGet(cont)];
	max = FldOBJ_BlActCont_GuestTexMaxGet( cont );
	
	return( FldOBJ_BlActResm_IDTblSearch(tbl,id,max) );
}

//--------------------------------------------------------------
/**
 * �w�肳�ꂽOBJ�R�[�h�̃��M�����[�A�Q�X�g�o�^�ς݃`�F�b�N
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	code	OBJ�R�[�h�BHERO��
 * @retval	int		REGULAR��
 */
//--------------------------------------------------------------
static int FldOBJ_BlActResManage_OBJCodeRegistCheck( FIELD_OBJ_BLACT_CONT *cont, int code )
{
	if( FldOBJ_BlActResm_TexIDSearch_Regular(cont,code) == TRUE ){
		return( REGULAR );
	}
	
	if( FldOBJ_BlActResm_TexIDSearch_Guest(cont,code) == TRUE ){
		return( GUEST );
	}
	
	return( NOT_REGULAR_GUEST );
}

//--------------------------------------------------------------
/**
 * �w�肳�ꂽ���f��ID�̃��M�����[�A�Q�X�g�o�^�ς݃`�F�b�N
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		BLACT_MDLID_32x32��
 * @retval	int		REGULAR��
 */
//--------------------------------------------------------------
static int FldOBJ_BlActResManage_MdlIDRegistCheck( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	if( FldOBJ_BlActResm_MdlIDSearch_Regular(cont,id) == TRUE ){
		return( REGULAR );
	}
	
	if( FldOBJ_BlActResm_MdlIDSearch_Guest(cont,id) == TRUE ){
		return( GUEST );
	}
	
	return( NOT_REGULAR_GUEST );
}

//--------------------------------------------------------------
/**
 * �w�肳�ꂽ���f��ID�̃��M�����[�A�Q�X�g�o�^�ς݃`�F�b�N
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		BLACT_MDLID_32x32��
 * @retval	int		REGULAR��
 */
//--------------------------------------------------------------
int FieldOBJ_BlActResManage_MdlIDRegistCheck( CONST_FIELD_OBJ_SYS_PTR fos, int id )
{
	FIELD_OBJ_BLACT_CONT *cont = FieldOBJSys_BlActContGet( fos );
	return( FldOBJ_BlActResManage_MdlIDRegistCheck(cont,id) );
}

//--------------------------------------------------------------
/**
 * �w�肳�ꂽ�A�j��ID�̃��M�����[�A�Q�X�g�o�^�ς݃`�F�b�N
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		BLACT_ANMID_32x32��
 * @retval	int		REGULAR��
 */
//--------------------------------------------------------------
static int FldOBJ_BlActResManage_AnmIDRegistCheck( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	if( FldOBJ_BlActResm_AnmIDSearch_Regular(cont,id) == TRUE ){
		return( REGULAR );
	}
	
	if( FldOBJ_BlActResm_AnmIDSearch_Guest(cont,id) == TRUE ){
		return( GUEST );
	}
	
	return( NOT_REGULAR_GUEST );
}

//--------------------------------------------------------------
/**
 * �w�肳�ꂽOBJ�R�[�h�̓o�^�B
 * ���M�����[�A�Q�X�g�`�F�b�N���s���A���M�����[�Ŗ����ꍇ�̓Q�X�g�Ƃ��ēo�^
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	code	OBJ�R�[�h�BHERO��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResManage_OBJCodeRegist( FIELD_OBJ_BLACT_CONT *cont, int code )
{
	TEXREG_TYPE ret = FldOBJ_BlActResm_TexIDSearchAll( cont, code );
	
	if( ret == TEX_NON ){
		FldOBJ_BlActResm_GuestAdd_Tex( cont, code );
	}
}

//--------------------------------------------------------------
/**
 * �w�肳�ꂽ���f��ID�̓o�^�B
 * ���M�����[�A�Q�X�g�`�F�b�N���s���A���M�����[�Ŗ����ꍇ�̓Q�X�g�Ƃ��ēo�^
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		BLACT_MDLID_32x32��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResManage_MdlIDRegist( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	if( FldOBJ_BlActResManage_MdlIDRegistCheck(cont,id) == NOT_REGULAR_GUEST ){
		FldOBJ_BlActResm_GuestAdd_Mdl( cont, id );
	}
}

//--------------------------------------------------------------
/**
 * �w�肳�ꂽ�A�j��ID�̓o�^�B
 * ���M�����[�A�Q�X�g�`�F�b�N���s���A���M�����[�Ŗ����ꍇ�̓Q�X�g�Ƃ��ēo�^
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		BLACT_ANMID_NORMAL_0��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResManage_AnmIDRegist( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	if( FldOBJ_BlActResManage_AnmIDRegistCheck(cont,id) == NOT_REGULAR_GUEST ){
		FldOBJ_BlActResm_GuestAdd_Anm( cont, id );
	}
}

//--------------------------------------------------------------
/**
 * OBJ�R�[�h����A���f���A�e�N�X�`���A�A�j���̃��M�����[�A�Q�X�g�`�F�b�N�B
 * �o�^����Ă��Ȃ��ӏ�����΃Q�X�g�Ƃ��ēo�^�B
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	code	OBJ�R�[�h�BHERO��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActResManage_AllIDRegist( FIELD_OBJ_BLACT_CONT *cont, int code )
{
	int ret;
	
	ret = FldOBJ_BlActH_OBJCode_MdlID( code );
	FldOBJ_BlActResManage_MdlIDRegist( cont, ret );
	
	ret = FldOBJ_BlActH_OBJCode_AnmID( code );
	FldOBJ_BlActResManage_AnmIDRegist( cont, ret );
	
	FldOBJ_BlActResManage_OBJCodeRegist( cont, code );
}

//--------------------------------------------------------------
/**
 * �Q�X�g�e�N�X�`���A���f���A�A�j����S�č폜
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActCont_ResmGuestDeleteAll( FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_BLACT_CONT *cont )
{
	FldOBJ_BlActResm_MdlIDDelete_GuestAll( fos, cont );
	FldOBJ_BlActResm_AnmIDDelete_GuestAll( fos, cont );
	FldOBJ_BlActResm_TexIDDelete_GuestAll( fos, cont );
}

//--------------------------------------------------------------
/**
 * ��������t�B�[���hOBJ��OBJ�R�[�h����
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	code	OBJ�R�[�h
 * @retval	int		TRUE=��v�A�� FALSE=��v����
 */
//--------------------------------------------------------------
static int FldOBJ_BlActCont_FldOBJSearch_OBJCode(
	CONST_FIELD_OBJ_SYS_PTR fos, int code, CONST_FIELD_OBJ_PTR ignore_obj )
{
	int no = 0,check_code;
	FIELD_OBJ_PTR fldobj = NULL;
	
	while( FieldOBJSys_FieldOBJSearch(fos,&fldobj,&no,FLDOBJ_STA_BIT_USE) == TRUE ){
		if( ignore_obj != NULL && ignore_obj == fldobj ){
			continue;
		}
		
		check_code = FieldOBJ_OBJCodeGet( fldobj );
		
		if( FieldOBJ_OBJCodeSeedCheck(check_code) == TRUE ){
			check_code = FieldOBJ_OBJCodeSeedGet( fldobj );
		}
			
		if( check_code == code ){
			return( TRUE );
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ��������t�B�[���hOBJ��OBJ�R�[�h�����@�O���[�o��
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	code	OBJ�R�[�h
 * @retval	int		TRUE=��v�A�� FALSE=��v����
 */
//--------------------------------------------------------------
int FieldOBJ_BlActCont_FldOBJSearch_OBJCode(
	FIELD_OBJ_SYS_PTR fos, int code, CONST_FIELD_OBJ_PTR ignore_obj )
{
	return( FieldOBJ_BlActCont_FldOBJSearch_OBJCode(fos,code,ignore_obj) );
}

//--------------------------------------------------------------
/**
 * ��������t�B�[���hOBJ�̃��f��ID����
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	mdl_id	���f�� ID
 * @param	ignore_obj	��������FIELD_OBJ_PTR �����ꍇ��NULL
 * @retval	int		TRUE=��v�A�� FALSE=��v����
 */
//--------------------------------------------------------------
static int FldOBJ_BlActCont_FldOBJSearch_MdlID(
	CONST_FIELD_OBJ_SYS_PTR fos, int mdl_id, CONST_FIELD_OBJ_PTR ignore_obj )
{
	int code,no = 0;
	FIELD_OBJ_PTR fldobj = NULL;
	
	while( FieldOBJSys_FieldOBJSearch(fos,&fldobj,&no,FLDOBJ_STA_BIT_USE) == TRUE ){
		if( ignore_obj != NULL && ignore_obj == fldobj ){
			continue;
		}
		
		code = FieldOBJ_OBJCodeGet( fldobj );
		
		if( code == OBJCODEMAX ){
			continue;
		}
		
		{
			const OBJCODE_STATE *state = FieldOBJ_OBJCodeDrawStateGet( fldobj );
			if( state->type_draw != FLDOBJ_DRAWTYPE_BLACT ){ continue; }
		}
			
		if( FieldOBJ_OBJCodeSeedCheck(code) == TRUE ){
			code = FieldOBJ_OBJCodeSeedGet( fldobj );
		}
			
		if( code != OBJCODEMAX ){
			if( FldOBJ_BlActH_OBJCode_MdlID(code) == mdl_id ){
				return( TRUE );
			}
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ��������t�B�[���hOBJ�̃��f��ID�����@�O���[�o��
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	mdl_id	���f�� ID
 * @param	ignore_obj	��������FIELD_OBJ_PTR �����ꍇ��NULL
 * @retval	int		TRUE=��v�A�� FALSE=��v����
 */
//--------------------------------------------------------------
int FieldOBJ_BlActCont_FldOBJSearch_MdlID(
	CONST_FIELD_OBJ_SYS_PTR fos, int mdl_id, CONST_FIELD_OBJ_PTR ignore_obj )
{
	return( FldOBJ_BlActCont_FldOBJSearch_MdlID(fos,mdl_id,ignore_obj) );
}

//--------------------------------------------------------------
/**
 * ��������t�B�[���hOBJ�̃A�j��ID����
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	anm_id	�A�j�� ID
 * @param	ignore_obj	��������FIELD_OBJ_PTR NULL=����
 * @retval	int		TRUE=��v�A�� FALSE=��v����
 */
//--------------------------------------------------------------
static int FldOBJ_BlActCont_FldOBJSearch_AnmID(
	CONST_FIELD_OBJ_SYS_PTR fos, int anm_id, CONST_FIELD_OBJ_PTR ignore_obj )
{
	int code,no = 0;
	FIELD_OBJ_PTR fldobj = NULL;
	
	while( FieldOBJSys_FieldOBJSearch(fos,&fldobj,&no,FLDOBJ_STA_BIT_USE) == TRUE ){
		if( ignore_obj != NULL && fldobj == ignore_obj ){
			continue;
		}
		
		if( code == OBJCODEMAX ){
			continue;
		}
		
		{
			const OBJCODE_STATE *state = FieldOBJ_OBJCodeDrawStateGet( fldobj );
			if( state->type_draw != FLDOBJ_DRAWTYPE_BLACT ){ continue; }
		}
		
		code = FieldOBJ_OBJCodeGet( fldobj );
		
		if( FieldOBJ_OBJCodeSeedCheck(code) == TRUE ){
			code = FieldOBJ_OBJCodeSeedGet( fldobj );
		}
			
		if( code != OBJCODEMAX ){
			if( FldOBJ_BlActH_OBJCode_AnmID(code) == anm_id ){
				return( TRUE );
			}
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ��������t�B�[���hOBJ�̃A�j��ID�����@�O���[�o��
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	anm_id	�A�j�� ID
 * @param	ignore_obj	��������FIELD_OBJ_PTR NULL=����
 * @retval	int		TRUE=��v�A�� FALSE=��v����
 */
//--------------------------------------------------------------
int FieldOBJ_BlActCont_FldOBJSearch_AnmID(
	FIELD_OBJ_SYS_PTR fos, int anm_id, CONST_FIELD_OBJ_PTR ignore_obj )
{
	return( FldOBJ_BlActCont_FldOBJSearch_AnmID(fos,anm_id,ignore_obj) );
}

//--------------------------------------------------------------
/**
 * ���\�[�XID�Ǘ��@�Q�X�g�폜�@��������OBJ���Ŏg�p���Ă��鍀�ڂ͍폜����
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	code	OBJ�R�[�h
 * @param	fldobj	ignore
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActResm_ResIDGuestUseCheckDelete(
		CONST_FIELD_OBJ_SYS_PTR fos, int code, FIELD_OBJ_PTR fldobj )
{
	int id;
	FIELD_OBJ_BLACT_CONT *cont = FieldOBJSys_BlActContGet( fos );
	
	id = FldOBJ_BlActH_OBJCode_MdlID( code );
	
	if( FldOBJ_BlActResManage_MdlIDRegistCheck(cont,id) == GUEST ){
		if( FldOBJ_BlActCont_FldOBJSearch_MdlID(fos,id,fldobj) == FALSE ){
			OS_Printf( "FldOBJ Mdl Delete Guest ID=0x%x\n", id );
			LRes_FreeID( cont->lres_mdl, id );
			FldOBJ_BlActResm_MdlIDDelete_Guest( cont, id );
		}
	}
	
	id = FldOBJ_BlActH_OBJCode_AnmID( code );
	
	if( FldOBJ_BlActResManage_AnmIDRegistCheck(cont,id) == GUEST ){
		if( FldOBJ_BlActCont_FldOBJSearch_AnmID(fos,id,fldobj) == FALSE ){
			OS_Printf( "FldOBJ Anm Delete Guest ID=0x%x\n", id );
			LRes_FreeID( cont->lres_anm, id );
			FldOBJ_BlActResm_AnmIDDelete_Guest( cont, id );
		}
	}
	
	if( FldOBJ_BlActResManage_OBJCodeRegistCheck(cont,code) == GUEST ){
		if( FldOBJ_BlActCont_FldOBJSearch_OBJCode(fos,code,fldobj) == FALSE ){
			TEXRES_MANAGER_PTR resm = FieldOBJ_BlActCont_TexResManageGet( cont );
			TEXRESM_DeleteResID( resm, code );
			FldOBJ_BlActResm_TexIDDelete_Guest( cont, code );
			
			FldOBJ_TexLoadReserveCancel( cont, code );
			FldOBJ_TexTransCancel( cont, code );
			OS_Printf( "FldOBJ Tex Delete Guest ID=0x%x\n", code );
		}
	}
}

//==============================================================================
//	VIntr�^�X�N
//==============================================================================
#if 0
//--------------------------------------------------------------
/**
 * VIntr TCB�ǉ�
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	max		V�u�����N���荞�ݒ��ɓ]���o����񐔍ő�
 * @param	pri		VIntrTCB�����v���C�I���e�B
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActVIntrTcbAdd( FIELD_OBJ_BLACT_CONT *cont, int max, int pri )
{
	int size;
	TCB_PTR tcb;
	VINTR_WORK *work;
	
	{
		TCB_PTR check_tcb = FldOBJ_BlActContVIntrTcbPtrGet( cont );
		GF_ASSERT( check_tcb == NULL &&						//NULL�̂͂�
			"FldOBJ_BlActVIntrTcbAdd() �`��폜���ς�ł��Ȃ��̂� �t�B�[���hOBJ�`�揉����?\n" );
	}
	
	work = sys_AllocMemory( HEAPID_FIELD, VINTR_WORK_SIZE );
	GF_ASSERT( work != NULL && "FldOBJ_BlActVIntrTcbAdd()�������m�ێ��s" );
	memset( work, 0, VINTR_WORK_SIZE );
	
	work->max = max;
	work->cont = cont;
	
	size = sizeof( TEXRES_MANAGER_PTR ) * max;
	work->resm_tex_tbl = sys_AllocMemory( HEAPID_FIELD, size );
	GF_ASSERT( work->resm_tex_tbl != NULL && "FldOBJ_BlActVIntrTcbAdd()TEX�e�[�u���m�ێ��s" );
	memset( work->resm_tex_tbl, NULL, size );
	
	size = sizeof( int ) * max;
	work->resm_tex_id_tbl = sys_AllocMemory( HEAPID_FIELD, size );
	GF_ASSERT( work->resm_tex_id_tbl != NULL && "FldOBJ_BlActVIntrTcbAdd()ID�e�[�u���m�ێ��s" );
	memset( work->resm_tex_id_tbl, 0, size );
	
	tcb = VIntrTCB_Add( FldOBJ_VIntrTcb, work, pri );
	GF_ASSERT( tcb != NULL && "FldOBJ_BlActVIntrTcbAdd()TCB�ǉ����s" );
	
	FldOBJ_BlActContVIntrTcbPtrSet( cont, tcb );
}
#endif

#if 0
//--------------------------------------------------------------
/**
 * VIntr TCB�폜
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActVIntrTcbDelete( FIELD_OBJ_BLACT_CONT *cont )
{
	TCB_PTR tcb;
	VINTR_WORK *work;
	
	tcb = FldOBJ_BlActContVIntrTcbPtrGet( cont );
	
	if( tcb == NULL ){
		return;
	}
	
	work = TCB_GetWork( tcb );
	TCB_Delete( tcb );
	
	sys_FreeMemory( HEAPID_FIELD, work->resm_tex_id_tbl );
	sys_FreeMemory( HEAPID_FIELD, work->resm_tex_tbl );
	sys_FreeMemory( HEAPID_FIELD, work );
	
	FldOBJ_BlActContVIntrTcbPtrSet( cont, NULL );
}
#endif

#if 0
//--------------------------------------------------------------
/**
 * TCB V�u�����N����
 * @param	tcb		TCB_PTR
 * @param	work	tcb work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_VIntrTcb( TCB_PTR tcb, void *wk )
{
	int i,count;
	VINTR_WORK *work;
	
	work = wk;
	GF_ASSERT( work != NULL && "FldOBJ_VIntrTcb()���[�N�ُ�" );
	
	if( work->access_flag == TRUE ){
		OS_Printf( "FldOBJ_VIntrTcb()�A�N�Z�X���Ɋ��荞�ݏ������������܂���\n" );
		OS_Printf( "���̃��b�Z�[�W�������ɂȂ������͂��萔�ł�������J�܂ŘA��������\n" );
		return;
	}
	
	i = 0;
	count = 0;
	
	do{
		if( work->resm_tex_tbl[i] != NULL ){
			TEXRESM_TexLoadAndCutTexID( work->resm_tex_tbl[i], work->resm_tex_id_tbl[i] );
			work->resm_tex_tbl[i] = NULL;						//���
			count++;
			
			if( count >= FLDOBJ_BLACT_VINTR_TEX_LOAD_MAX ){		//1sync�]���ʍő�
				break;
			}
		}
		
		i++;
	}while( i < work->max );
}
#endif

#if 0
//--------------------------------------------------------------
/**
 * TEXRESM_TexLoad() V�u�����N�����֓o�^
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	resm	TEXRES_MANAGER_PTR
 * @param	id		�]������e�N�X�`��ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_VIntrTcb_TexLoadAdd(
		FIELD_OBJ_BLACT_CONT *cont, TEXRES_MANAGER_PTR resm, int id )
{
	int i;
	TCB_PTR tcb;
	VINTR_WORK *work;
	
	tcb = FldOBJ_BlActContVIntrTcbPtrGet( cont );
	
	GF_ASSERT( tcb != NULL && "FldOBJ_VIntrTcb_TexLoadAdd()TCB���ǉ��Ŏ��s" );
	
	work = TCB_GetWork( tcb );
	
	work->access_flag = TRUE;
	
	i = 0;
	
	do{
		if( work->resm_tex_tbl[i] == NULL ){
			work->resm_tex_tbl[i] = resm;
			work->resm_tex_id_tbl[i] = id;
			break;
		}
		
		i++;
	}while( i < work->max );
	
	GF_ASSERT( i < work->max && "FldOBJ_VIntrTcb_TexLoadAdd()�e�N�X�`���]���ő吔�z��" );
	work->access_flag = FALSE;
}
#endif

#if 0
//--------------------------------------------------------------
/**
 * TEXRESM_TexLoad() V�u�����N�����֓o�^���Ă������m���L�����Z������
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		�o�^�����e�N�X�`��ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_VIntrTcb_TexLoadCancel( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int i;
	TCB_PTR tcb;
	VINTR_WORK *work;
	
	tcb = FldOBJ_BlActContVIntrTcbPtrGet( cont );
	
	GF_ASSERT( tcb != NULL && "FldOBJ_VIntrTcb_TexLoadCancel()TCB���ǉ��Ŏ��s" );
	
	work = TCB_GetWork( tcb );
	work->access_flag = TRUE;
	
	i = 0;
	
	do{
		if( work->resm_tex_tbl[i] != NULL ){
			if( work->resm_tex_id_tbl[i] == id ){
				TEXRESM_Delete( work->resm_tex_tbl[i] );
				work->resm_tex_tbl[i] = NULL;
				break;
			}
		}
		
		i++;
	}while( i < work->max );
	
	work->access_flag = FALSE;
}
#endif

//==============================================================================
//	FIELD_OBJ_BLACT_CONT�Q��
//==============================================================================
//--------------------------------------------------------------
/**
 * BLACT_SET_PTR�Z�b�g
 * @param	cont		FIELD_OBJ_BLACT_CONT
 * @param	set			BLACT_SET_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActCont_SetPtrSet( FIELD_OBJ_BLACT_CONT *cont, BLACT_SET_PTR set )
{
	cont->blact_setptr = set;
}

//--------------------------------------------------------------
/**
 * BLACT_SET_PTR�擾
 * @param	cont		FIELD_OBJ_BLACT_CONT
 * @retval	BLACT_SET_PTR	BLACT_SET_PTR
 */
//--------------------------------------------------------------
BLACT_SET_PTR FieldOBJ_BlActCont_SetPtrGet( FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->blact_setptr );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�ő吔�Z�b�g
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	max		�ő吔
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActCont_MaxSet( FIELD_OBJ_BLACT_CONT *cont, int max )
{
	cont->max = max;
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�ő吔�擾
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	int		�C���f�b�N�X
 */
//--------------------------------------------------------------
int FieldOBJ_BlActCont_MaxGet( const FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->max );
}

//--------------------------------------------------------------
/**
 * ���f�����\�[�X�}�l�[�W���ݒ�
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	mdl		RES_MANAGER_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActCont_MdlResManageSet( FIELD_OBJ_BLACT_CONT *cont, RES_MANAGER_PTR mdl )
{
	cont->mdl_res_manage = mdl;
}

//--------------------------------------------------------------
/**
 * ���f�����\�[�X�}�l�[�W���擾
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	RES_MANAGER_PTR	RES_MANAGER_PTR
 */
//--------------------------------------------------------------
RES_MANAGER_PTR FieldOBJ_BlActCont_MdlResManageGet( const FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->mdl_res_manage );
}

//--------------------------------------------------------------
/**
 * �A�j�����\�[�X�}�l�[�W���ݒ�
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	anm		RES_MANAGER_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActCont_AnmResManageSet( FIELD_OBJ_BLACT_CONT *cont, RES_MANAGER_PTR anm )
{
	cont->anm_res_manage = anm;
}

//--------------------------------------------------------------
/**
 * �A�j�����\�[�X�}�l�[�W���擾
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	RES_MANAGER_PTR	RES_MANAGER_PTR
 */
//--------------------------------------------------------------
RES_MANAGER_PTR FieldOBJ_BlActCont_AnmResManageGet( const FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->anm_res_manage );
}

//--------------------------------------------------------------
/**
 * �e�N�X�`�����\�[�X�}�l�[�W���ݒ�
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	anm		RES_MANAGER_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActCont_TexResManageSet( FIELD_OBJ_BLACT_CONT *cont, TEXRES_MANAGER_PTR tex )
{
	cont->tex_res_manage = tex;
}

//--------------------------------------------------------------
/**
 * �e�N�X�`�����\�[�X�}�l�[�W���擾
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	RES_MANAGER_PTR	RES_MANAGER_PTR
 */
//--------------------------------------------------------------
TEXRES_MANAGER_PTR FieldOBJ_BlActCont_TexResManageGet( const FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->tex_res_manage );
}

//--------------------------------------------------------------
/**
 * ���\�[�XID �e�N�X�`���ւ�*���擾
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	int		ID�e�[�u�� int �T�C�Y��FLDOBJ_RESM_MAX_TEX
 */
//--------------------------------------------------------------
static int * FldOBJ_BlActCont_ResmTexIDTblGet( FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_tbl_tex );
}

//--------------------------------------------------------------
/**
 * ���\�[�XID ���f���ւ�*���擾
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	int		ID�e�[�u�� int �T�C�Y��FLDOBJ_RESM_MAX_TEX
 */
//--------------------------------------------------------------
static int * FldOBJ_BlActCont_ResmMdlIDTblGet( FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_tbl_mdl );
}

//--------------------------------------------------------------
/**
 * ���M�����[ID �A�j���ւ�*���擾
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	int		ID�e�[�u�� int �T�C�Y��FLDOBJ_RESM_MAX_TEX
 */
//--------------------------------------------------------------
static int * FldOBJ_BlActCont_ResmAnmIDTblGet( FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_tbl_anm );
}

//--------------------------------------------------------------
/**
 * ���M�����[ID �ő�Ǘ����ݒ�@���f��
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	max		�ő吔
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActCont_RegularMdlMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max )
{
	cont->resm_id_reg_max_mdl = max;
}

//--------------------------------------------------------------
/**
 * ���M�����[ID �ő�Ǘ����擾�@���f��
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	max		�ő吔
 */
//--------------------------------------------------------------
static int FldOBJ_BlActCont_RegularMdlMaxGet( const FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_reg_max_mdl );
}

//--------------------------------------------------------------
/**
 * �Q�X�gID �ő�Ǘ����ݒ�@���f��
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	max		�ő吔
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActCont_GuestMdlMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max )
{
	cont->resm_id_gst_max_mdl = max;
}

//--------------------------------------------------------------
/**
 * �Q�X�gID �ő�Ǘ����擾�@���f��
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	int		�ő吔
 */
//--------------------------------------------------------------
static int FldOBJ_BlActCont_GuestMdlMaxGet( const FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_gst_max_mdl );
}

//--------------------------------------------------------------
/**
 * ���M�����[ID �ő�Ǘ����ݒ�@�A�j��
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	max		�ő吔
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActCont_RegularAnmMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max )
{
	cont->resm_id_reg_max_anm = max;
}

//--------------------------------------------------------------
/**
 * ���M�����[ID �ő�Ǘ����擾�@�A�j��
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	max		�ő吔
 */
//--------------------------------------------------------------
static int FldOBJ_BlActCont_RegularAnmMaxGet( const FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_reg_max_anm );
}

//--------------------------------------------------------------
/**
 * �Q�X�gID �ő�Ǘ����ݒ�@�A�j��
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	max		�ő吔
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActCont_GuestAnmMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max )
{
	cont->resm_id_gst_max_anm = max;
}

//--------------------------------------------------------------
/**
 * �Q�X�gID �ő�Ǘ����擾�@�A�j��
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	int		�ő吔
 */
//--------------------------------------------------------------
static int FldOBJ_BlActCont_GuestAnmMaxGet( const FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_gst_max_anm );
}

//--------------------------------------------------------------
/**
 * ���M�����[ID �ő�Ǘ����ݒ�@�e�N�X�`��
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	max		�ő吔
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActCont_RegularTexMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max )
{
	cont->resm_id_reg_max_tex = max;
}

//--------------------------------------------------------------
/**
 * ���M�����[ID �ő�Ǘ����擾�@�e�N�X�`��
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	max		�ő吔
 */
//--------------------------------------------------------------
static int FldOBJ_BlActCont_RegularTexMaxGet( const FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_reg_max_tex );
}

//--------------------------------------------------------------
/**
 * �Q�X�gID �ő�Ǘ����ݒ�@�e�N�X�`��
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	max		�ő吔
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActCont_GuestTexMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max )
{
	cont->resm_id_gst_max_tex = max;
}

//--------------------------------------------------------------
/**
 * �Q�X�gID �ő�Ǘ����擾�@�e�N�X�`��
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	int		�ő吔
 */
//--------------------------------------------------------------
static int FldOBJ_BlActCont_GuestTexMaxGet( const FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_gst_max_tex );
}

#if 0
//--------------------------------------------------------------
/**
 * �Q�X�g�ǉ��Ǘ�TCB_PTR�Z�b�g
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	tcb		TCB_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActGuestAddTcbPtrSet( FIELD_OBJ_BLACT_CONT *cont, TCB_PTR tcb )
{
	cont->tcb_ptr_blact_add = tcb;
}
#endif

#if 0
//--------------------------------------------------------------
/**
 * �Q�X�g�ǉ��Ǘ�TCB_PTR�擾
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @retval	TCB_PTR	TCB_PTR
 */
//--------------------------------------------------------------
static TCB_PTR FldOBJ_BlActGuestAddTcbPtrGet( FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->tcb_ptr_blact_add );
}
#endif

#if 0
//--------------------------------------------------------------
/**
 * V�u�����N���荞��TCB_PTR�Z�b�g
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	tcb		TCB_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActContVIntrTcbPtrSet( FIELD_OBJ_BLACT_CONT *cont, TCB_PTR tcb )
{
	cont->tcb_ptr_vintr = tcb;
}
#endif

#if 0
//--------------------------------------------------------------
/**
 * V�u�����N���荞��TCB_PTR�擾
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @retval	TCB_PTR	TCB_PTR
 */
//--------------------------------------------------------------
static TCB_PTR FldOBJ_BlActContVIntrTcbPtrGet( FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->tcb_ptr_vintr );
}
#endif

//--------------------------------------------------------------
/**
 * FIELD_OBJ_BLACT_CONT����A�[�J�C�u�f�[�^�擾
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	dataID	�A�[�J�C�u�f�[�^�C���f�b�N�XID
 * @param	fb		TRUE=sys_AllocMemory() FALSE=sys_AllocMemoryLo()
 * @retval	void*	dataID�̃f�[�^
 */
//--------------------------------------------------------------
static void * FldOBJ_BlActContArcDataAlloc( FIELD_OBJ_BLACT_CONT *cont, u32 datID, int fb )
{	
	return( FieldOBJ_DrawArcDataAlloc(cont->fos,datID,fb) );
}

//==============================================================================
//	DATA_FieldOBJ_BlActHeaderPathIDTbl�Q��
//==============================================================================
//--------------------------------------------------------------
/**
 * DATA_FieldOBJ_BlActHeaderPathIDTbl�擾
 * @param	code	OBJ�R�[�h�BHERO��
 * @retval	FIELD_OBJ_BLACT_HEADER_ID* DATA_FieldOBJ_BlActHeaderPathIDTbl *
 */
//--------------------------------------------------------------
static const FIELD_OBJ_BLACT_HEADER_ID * FldOBJ_BlActHeaderPathIDTblGet( int code )
{
	const FIELD_OBJ_BLACT_HEADER_ID *head = DATA_FieldOBJ_BlActHeaderPathIDTbl;
	do{ if(head->tex_id == code){return(head);} head++; }while( head->tex_id != OBJCODEMAX );
	OS_Printf( "OBJ CODE ERROR code = 0x%x", code );
	GF_ASSERT( 0 && "FldOBJ_BlActHeaderPathIDTblGet() OBJCODEMAX" );
	return( NULL );
}

//--------------------------------------------------------------
/**
 * OBJ�R�[�h���烂�f��ID���擾
 * @param	code	HERO��
 * @retval	int		BLACT_MDLID_32x32��
 */
//--------------------------------------------------------------
static int FldOBJ_BlActH_OBJCode_MdlID( int code )
{
	const FIELD_OBJ_BLACT_HEADER_ID *tbl;
	
	tbl = FldOBJ_BlActHeaderPathIDTblGet( code );
	return( tbl->mdl_id );
}

//--------------------------------------------------------------
/**
 * OBJ�R�[�h���烂�f��ID���擾�@�O���[�o��
 * @param	code	HERO��
 * @retval	int		BLACT_MDLID_32x32��
 */
//--------------------------------------------------------------
int FieldOBJ_BlActOBJCodeMdlIDGet( int code )
{
	return( FldOBJ_BlActH_OBJCode_MdlID(code) );
}

//--------------------------------------------------------------
/**
 * OBJ�R�[�h����A�j��ID���擾
 * @param	code	HERO��
 * @retval	int		BLACT_ANMID_32x32��
 */
//--------------------------------------------------------------
static int FldOBJ_BlActH_OBJCode_AnmID( int code )
{
	const FIELD_OBJ_BLACT_HEADER_ID *tbl;
	
	tbl = FldOBJ_BlActHeaderPathIDTblGet( code );
	return( tbl->anm_id );
}

//--------------------------------------------------------------
/**
 * OBJ�R�[�h����A�j��ID���擾�@�O���[�o��
 * @param	code	HERO��
 * @retval	int		BLACT_ANMID_32x32��
 */
//--------------------------------------------------------------
int FieldOBJ_BlActOBJCodeAnmIDGet( int code )
{
	return( FldOBJ_BlActH_OBJCode_AnmID(code) );
}

//--------------------------------------------------------------
/**
 * OBJ�R�[�h����A�j���e�[�u�����擾
 * @param	code	HERO��
 * @retval	char*	�w�b�_�[�t�@�C���p�X
 */
//--------------------------------------------------------------
static const BLACT_ANIME_TBL * FldOBJ_BlActH_OBJCode_AnmTbl( int code )
{
	const FIELD_OBJ_BLACT_HEADER_ID *tbl;
	
	tbl = FldOBJ_BlActHeaderPathIDTblGet( code );
	return( tbl->anm_tbl );
};

//==============================================================================
//	�r���{�[�h�A�N�^�[�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�ǉ����t���O���Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=�ǉ��� FALSE=�ǉ�����
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActAddPracFlagSet( FIELD_OBJ_PTR fldobj, int flag )
{
	if( flag == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_BLACT_ADD_PRAC );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_BLACT_ADD_PRAC );
	}
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�ǉ����t���O�̃`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=�ǉ��� FALSE=�ǉ��ς�
 */
//--------------------------------------------------------------
int FieldOBJ_BlActAddPracFlagCheck( FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_BLACT_ADD_PRAC) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[������
 * @param	cont			FIELD_OBJ_BLACT_CONT *
 * @param	max				�A�N�^�[�ő吔
 * @retval	BLACT_SET_PTR	�A�N�^�[�Z�b�g�|�C���^
 */
//--------------------------------------------------------------
static void FldOBJ_BlActInit( FIELD_OBJ_BLACT_CONT *cont, int max )
{
	BLACT_SETDATA set;
	BLACT_SET_PTR setptr;
	
	set.WorkNum = max;
	set.heap	= HEAPID_FIELD;
	
	setptr = BLACT_InitSet( &set );
	FieldOBJ_BlActCont_SetPtrSet( cont, setptr );
	FieldOBJ_BlActCont_MaxSet( cont, max );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�@�C���f�b�N�X�폜
 * @param	set		BLACT_SET_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActDestSet( BLACT_SET_PTR set )
{
	BLACT_DestSet( set );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�̒ǉ�
 * @param	set			BLACT_SET_PTR
 * @param	head		BLACT_HEADER *
 * @param	vec			���W
 * @retval	BLACT_WORK	BLACT_WORK_PTR , NULL=�ǉ����s
 */
//--------------------------------------------------------------
static BLACT_WORK_PTR FldOBJ_BlActAdd(
		BLACT_SET_PTR set, const BLACT_HEADER *head, const VecFx32 *vec )
{
	int no;
	BLACT_ADD add;
	BLACT_WORK_PTR act;
	VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
	
	add.blact_s = set;
	add.pHeader = head;
	add.matrix	= *vec;
	add.scale	= scale;
	
	act = BLACT_Add( &add );
	
	if( act != NULL ){
		BLACT_ObjDrawFlagSet( act, FALSE );					//���S�ɏ�������������܂Ŕ�\��
		BLACT_AnmOffsChg( act, 0 );
		BLACT_AnmFrameSetOffs( act, 0 );
		NNS_G3dMdlSetMdlFogEnableFlagAll( BLACT_MdlResGet(act), TRUE );
		SetGlbLightMdl( BLACT_MdlResGet(act) );
	}
	
	return( act );
}

//--------------------------------------------------------------
/**
 * �w�b�_�[�e�[�u������w�b�_�[�ǂݍ���
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	code		HERO��
 * @param	head		�ǂݍ��ݐ�BLACT_HEADER *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActHeaderLoad(
		FIELD_OBJ_BLACT_CONT *cont, u32 code, BLACT_HEADER *head )
{
	{
		int id = FldOBJ_BlActH_OBJCode_MdlID( code );
		void *reso = LRes_IDResGet( cont->lres_mdl, id );
		head->ImdRes = reso;
	}
	
	{
		int id = FldOBJ_BlActH_OBJCode_AnmID( code );
		void *reso = LRes_IDResGet( cont->lres_anm, id );
		TEXANM_UnPackLoadFile( reso, &head->texanm );
	}
	
	{
		TEXRES_MANAGER_PTR resm = FieldOBJ_BlActCont_TexResManageGet( cont );
		TEXRES_OBJ_PTR reso = TEXRESM_GetResObj( resm, code );
		
#ifdef PM_DEBUG
		if( reso == NULL ){ 
			OS_Printf( "FldOBJ_BlActHeaderLoad() �o�^����Ă��Ȃ��e�N�X�`��" );
			OS_Printf( "OBJ�R�[�h = 0x%x\n", code );
			GF_ASSERT( 0 );
		}
#endif
		
		head->ItxRes = TEXRESM_GetResPTR( reso );
		
		{	//���ݏ풓�̂�	�]���^�̏ꍇ��NULL������
			head->texKey = TEXRESM_GetTexKeyPTR( reso );
			head->tex4x4Key = TEXRESM_GetTex4x4KeyPTR( reso );
			head->plttKey = TEXRESM_GetPlttKeyPTR( reso );
		}
	}
	
	{
		head->anm = FldOBJ_BlActH_OBJCode_AnmTbl( code );
	}
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ����FIELD_OBJ_BLACT_CONT�擾
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	FIELD_OBJ_BLACT_CONT	FIELD_OBJ_BLACT_CONT *
 */
//--------------------------------------------------------------
static const FIELD_OBJ_BLACT_CONT * FldOBJ_BlActContGet( CONST_FIELD_OBJ_PTR fldobj )
{
	CONST_FIELD_OBJ_SYS_PTR sys;
	
	sys = FieldOBJ_FieldOBJSysGet( fldobj );
	return( FieldOBJSys_BlActContGet(sys) );
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ����FIELD_OBJ_BLACT_CONT�擾�@���[�J�������
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	FIELD_OBJ_BLACT_CONT	FIELD_OBJ_BLACT_CONT *
 */
//--------------------------------------------------------------
static FIELD_OBJ_BLACT_CONT * FldOBJ_BlActContGetLocal( CONST_FIELD_OBJ_PTR fldobj )
{
	CONST_FIELD_OBJ_SYS_PTR sys;
	
	sys = FieldOBJ_FieldOBJSysGet( fldobj );
	return( (FIELD_OBJ_BLACT_CONT *)FieldOBJSys_BlActContGet(sys) );
}

//==============================================================================
//	�A�N�^�[�@�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�Ɋi�[����Ă���3D���W���A�N�^�[�ɔ��f�B
 * @param	dir		DIR_UP��
 * @retval	BOOL	FALSE=�����擾���s
 */
//--------------------------------------------------------------
BOOL FieldOBJ_BlActPosSet( FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act )
{
	BOOL ret;
	VecFx32 vec_pos;
	
	FieldOBJ_DrawVecPosTotalGet( fldobj, &vec_pos );
	
	vec_pos.x += FLDOBJ_BLACT_X_GROUND_OFFS_FX32;
	vec_pos.y += FLDOBJ_BLACT_Y_GROUND_OFFS_FX32;
	vec_pos.z += FLDOBJ_BLACT_Z_GROUND_OFFS_FX32;
	
	BLACT_MatrixSet( act, &vec_pos );
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�X�e�[�^�X�����ĕ\���A��\���Z�b�g
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActFlagVanishSet( FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act )
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

//==============================================================================
//	�A�j���[�V�����i���o�[�@�p�[�c
//==============================================================================
//--------------------------------------------------------------
//	�����@�㉺���E�e�[�u��	������
//--------------------------------------------------------------
static const int DATA_BlActAnmOffsNo_WalkTbl[] =
{ 0, 1, 2, 3 };

//--------------------------------------------------------------
/**
 * ������������A�j���I�t�Z�b�g�ԍ��擾
 * @param	dir		DIR_UP��
 * @retval	int		�A�j���I�t�Z�b�g�ԍ�
 */
//--------------------------------------------------------------
int FieldOBJ_BlActAnmOffsNo_DirWalkGet( int dir )
{
	return( DATA_BlActAnmOffsNo_WalkTbl[dir] );
}

//--------------------------------------------------------------
//	�_�b�V���@�㉺���E�e�[�u��	������
//--------------------------------------------------------------
static const int DATA_BlActAnmOffsNo_DashTbl[] =
{ 4, 5, 6, 7 };

//--------------------------------------------------------------
/**
 * ��������_�b�V���A�j���I�t�Z�b�g�ԍ��擾
 * @param	dir		DIR_UP��
 * @retval	int		�A�j���I�t�Z�b�g�ԍ�
 */
//--------------------------------------------------------------
int FieldOBJ_BlActAnmOffsNo_DirDashGet( int dir )
{
	return( DATA_BlActAnmOffsNo_DashTbl[dir] );
}

//--------------------------------------------------------------
//	�W�����v��@�㉺���E�e�[�u��	������
//--------------------------------------------------------------
static const int DATA_BlActAnmOffsNo_TakeOFFTbl[] =
{ 4, 5, 4, 5 };

//--------------------------------------------------------------
/**
 * ��������W�����v��A�j���I�t�Z�b�g�ԍ��擾
 * @param	dir		DIR_UP��
 * @retval	int		�A�j���I�t�Z�b�g�ԍ�
 */
//--------------------------------------------------------------
int FieldOBJ_BlActAnmOffsNo_DirTakeOFFGet( int dir )
{
	return( DATA_BlActAnmOffsNo_TakeOFFTbl[dir] );
}

//==============================================================================
//	�V�d�l�@�r���{�[�h�@�e�N�X�`��
//==============================================================================
#if 0
//--------------------------------------------------------------
/**
 * �e�N�X�`�����[�h
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	tex_id	�}�l�[�W���o�^ID
 * @param	arc_id	�A�[�J�C�uID
 * @param	reg_type	�o�^�^�C�v REGULAR? GUEST?
 * @retval	int		TRUE=���̏�Ń��[�h�BFALSE=���[�h�ő�A�\��։�
 */
//--------------------------------------------------------------
static int FldOBJ_TexLoadTransSet(
	FIELD_OBJ_BLACT_CONT *cont, int tex_id, u32 arc_id, REGULAR_GUEST reg_type )
{
	BLACT_VTRANS_WORK *work = cont->vtrans_work;
	
#ifdef PM_DEBUG
	if( work->load_count < work->load_max ){
	 	if(reg_type == REGULAR ){OS_Printf("FldOBJ TexLoad Regular ID=0x%x\n",tex_id);}
		else{OS_Printf("FldOBJ TexLoad Guest ID=0x%x\n",tex_id);}
	 }else{
		if(reg_type == REGULAR){OS_Printf("FldOBJ TexLoad Regular ID=0x%x Reserve\n",tex_id);}
		else{OS_Printf("FldOBJ TexLoad Guest ID=0x%x Reserve\n",tex_id);}
	 }
#endif
	
	if( work->load_count >= work->load_max ){
		int i = 0;
		TEXLOAD_WORK *load = work->tex_load_work_tbl;
	
		while( i < work->max ){
			if( load->resm_tex == NULL ){
				load->resm_tex = cont->tex_res_manage;
				load->reg_type = reg_type;
				load->resm_tex_id = tex_id;
				load->arc_id = arc_id;
				return( FALSE );
			}
			
			i++;
			load++;
		}
		
		GF_ASSERT( 0 && "FldOBJ_TexLoadTransSet() TEX LOAD RESERVE ERROR" );
		return( FALSE );
	}
	
	{
		void *buf = FldOBJ_BlActContArcDataAlloc( cont, arc_id, FALSE );
		FldOBJ_TexBufTransSet( cont, tex_id, buf, reg_type );
		work->load_count++;
		return( TRUE );
	}
}
#endif

#if 1
//--------------------------------------------------------------
/**
 * �e�N�X�`�����[�h
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	tex_id	�}�l�[�W���o�^ID
 * @param	arc_id	�A�[�J�C�uID
 * @param	reg_type	�o�^�^�C�v REGULAR? GUEST?
 * @retval	int		TRUE=���̏�Ń��[�h�BFALSE=���[�h�ő�A�\��։�
 */
//--------------------------------------------------------------
static int FldOBJ_TexLoadTransSet(
	FIELD_OBJ_BLACT_CONT *cont, int tex_id, u32 arc_id, REGULAR_GUEST reg_type )
{
	BLACT_VTRANS_WORK *work = cont->vtrans_work;
	
#ifdef PM_DEBUG
	if( work->load_count < work->load_max ){
	 	if(reg_type == REGULAR ){OS_Printf("FldOBJ TexLoad Regular ID=0x%x\n",tex_id);}
		else{OS_Printf("FldOBJ TexLoad Guest ID=0x%x\n",tex_id);}
	 }else{
		if(reg_type == REGULAR){OS_Printf("FldOBJ TexLoad Regular ID=0x%x Reserve\n",tex_id);}
		else{OS_Printf("FldOBJ TexLoad Guest ID=0x%x Reserve\n",tex_id);}
	 }
#endif
	
	if( work->load_count >= work->load_max ||
		BLACT_DelObjRefCheck(cont->blact_setptr) == TRUE ){
		int i = 0;
		TEXLOAD_WORK *load = work->tex_load_work_tbl;
	
		while( i < work->max ){
			if( load->resm_tex == NULL ){
				load->resm_tex = cont->tex_res_manage;
				load->reg_type = reg_type;
				load->resm_tex_id = tex_id;
				load->arc_id = arc_id;
				return( FALSE );
			}
			
			i++;
			load++;
		}
		
		GF_ASSERT( 0 && "FldOBJ_TexLoadTransSet() TEX LOAD RESERVE ERROR" );
		return( FALSE );
	}
	
	{
		void *buf = FldOBJ_BlActContArcDataAlloc( cont, arc_id, FALSE );
		FldOBJ_TexBufTransSet( cont, tex_id, buf, reg_type );
		work->load_count++;
		return( TRUE );
	}
}
#endif

#if 0	//old
static int FldOBJ_TexLoadTransSet(
	FIELD_OBJ_BLACT_CONT *cont, int tex_id, u32 arc_id, REGULAR_GUEST reg_type )
{
	BLACT_VTRANS_WORK *work = cont->vtrans_work;
	
#ifdef PM_DEBUG
	if( work->load_count < work->load_max ){
	 	if(reg_type == REGULAR ){OS_Printf("FldOBJ TexLoad Regular ID=0x%x\n",tex_id);}
		else{OS_Printf("FldOBJ TexLoad Guest ID=0x%x\n",tex_id);}
	 }else{
		if(reg_type == REGULAR){OS_Printf("FldOBJ TexLoad Regular ID=0x%x Reserve\n",tex_id);}
		else{OS_Printf("FldOBJ TexLoad Guest ID=0x%x Reserve\n",tex_id);}
	 }
#endif
	
	{
		if( BLACT_DelObjRefCheck(cont->blact_setptr) == TRUE ){
			return;
		}
	}
	
	if( work->load_count >= work->load_max ){
		int i = 0;
		TEXLOAD_WORK *load = work->tex_load_work_tbl;
	
		while( i < work->max ){
			if( load->resm_tex == NULL ){
				load->resm_tex = cont->tex_res_manage;
				load->reg_type = reg_type;
				load->resm_tex_id = tex_id;
				load->arc_id = arc_id;
				return( FALSE );
			}
			
			i++;
			load++;
		}
		
		GF_ASSERT( 0 && "FldOBJ_TexLoadTransSet() TEX LOAD RESERVE ERROR" );
		return( FALSE );
	}
	
	{
		void *buf = FldOBJ_BlActContArcDataAlloc( cont, arc_id, FALSE );
		FldOBJ_TexBufTransSet( cont, tex_id, buf, reg_type );
		work->load_count++;
		return( TRUE );
	}
}
#endif

//--------------------------------------------------------------
/**
 * �e�N�X�`�����[�h�L�����Z��
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	tex_id	�L�����Z������}�l�[�W���o�^ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_TexLoadReserveCancel( FIELD_OBJ_BLACT_CONT *cont, int tex_id )
{
	int i = 0;
	BLACT_VTRANS_WORK *work = cont->vtrans_work;
	TEXLOAD_WORK *load = work->tex_load_work_tbl;
	
	while( i < work->max ){
		if( load->resm_tex_id == tex_id && load->resm_tex != NULL ){
			load->resm_tex = NULL;
			return;
		}
		
		i++;
		load++;
	}
}

//--------------------------------------------------------------
/**
 * �e�N�X�`�����[�h�\��`�F�b�N
 * @param	cont			FIELD_OBJ_BLACT_CONT
 * @param	tex_id			�`�F�b�N����}�l�[�W���o�^ID
 * @retval	TEXREG_TYPE		TEX_REGULAR_RESERVE,TEX_GUEST_RESERVE,TEX_NON
 */
//--------------------------------------------------------------
static TEXREG_TYPE FldOBJ_TexLoadReserveCheck( FIELD_OBJ_BLACT_CONT *cont, int tex_id )
{
	int i = 0;
	BLACT_VTRANS_WORK *work = cont->vtrans_work;
	TEXLOAD_WORK *load = work->tex_load_work_tbl;
	
	while( i < work->max ){
		if( load->resm_tex_id == tex_id && load->resm_tex != NULL ){
			if( load->reg_type == REGULAR ){
				return( TEX_REGULAR_RESERVE );
			}
			
			return( TEX_GUEST_RESERVE );
		}
		
		i++;
		load++;
	}
	
	return( TEX_NON );
}

//--------------------------------------------------------------
/**
 * TCB �e�N�X�`�����[�h�\�����
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	tex_id	�}�l�[�W���o�^ID
 * @param	arc_id	�A�[�J�C�uID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_TexLoadReserveTCB( TCB_PTR tcb, void *wk )
{
	int i = 0;
	FIELD_OBJ_BLACT_CONT *cont = wk;
	BLACT_VTRANS_WORK *work = cont->vtrans_work;
	TEXLOAD_WORK *load = work->tex_load_work_tbl;
	
#if 1
	{
		if( BLACT_DelObjRefCheck(cont->blact_setptr) == TRUE ){
			return;
		}
	}
#endif
	
	while( (work->load_count < work->load_max) && i < work->max ){
		if( load->resm_tex != NULL ){
			void *buf = FldOBJ_BlActContArcDataAlloc( cont, load->arc_id, FALSE );
			FldOBJ_TexBufTransSet( cont, load->resm_tex_id, buf, load->reg_type );
			load->resm_tex = NULL;
			work->load_count++;
		}
		
		load++;
		i++;
	}
	
	{															//�\���������
		int j;
		load = work->tex_load_work_tbl;
		
		for( i = 0; i < (work->max - 1); i++ ){
			if( load[i].resm_tex == NULL ){
				for( j = i + 1; j < work->max; j++ ){
					if( load[j].resm_tex != NULL ){
						load[i] = load[j];
						load[j].resm_tex = NULL;
						break;
					}
				}
			}
		}	
	}
	
	work->load_count = 0;
}

//--------------------------------------------------------------
/**
 * �e�N�X�`�����[�h�@���[�h�����e�N�X�`��ID�̓��M�����[�Q�X�g�Ǘ��֓o�^
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	tex_id	�}�l�[�W���o�^ID
 * @param	buf		�]������e�N�X�`���o�b�t�@
 * @param	reg_type	�o�^�^�C�v REGULAR? GUEST?
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_TexBufTransSet(
	FIELD_OBJ_BLACT_CONT *cont, int tex_id, void *buf, REGULAR_GUEST reg_type )
{
	TEXRES_OBJ_PTR res =
		TEXRESM_AddAndAllocVramKeyResNormal(
			cont->tex_res_manage, buf, tex_id, TEXRESM_TEX_CUT_TRUE, HEAPID_FIELD );
	
	GF_ASSERT( res != NULL && "FldOBJ_TexBufTransSet() TEXRESM ADD ERROR" );
	
	FldOBJ_TexTransAdd( cont, tex_id );
	
	if( reg_type == REGULAR ){
		FldOBJ_BlActResm_TexIDReg_Regular( cont, tex_id );
	}else{
		FldOBJ_BlActResm_TexIDReg_Guest( cont, tex_id );
	}
}

//--------------------------------------------------------------
/**
 * VTRANS �e�N�X�`���o�^
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	id		�o�^ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_TexTransAdd( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int i = 0;
	BLACT_VTRANS_WORK *work = cont->vtrans_work;
	VTEX_WORK *tex = work->vtex_work_tbl;
	
	work->access_flag = TRUE;
	
	while( i < work->max ){
		if( tex->resm_tex == NULL ){
			tex->resm_tex = cont->tex_res_manage;
			tex->resm_tex_id = id;
			tex->trans_end = FALSE;
			
			work->access_flag = FALSE;
			return;
		}
		
		tex++;
		i++;
	}
	
	GF_ASSERT( 0 && "FldOBJ_TexTransAdd() TEX ADD MAX ERROR" );
}

//--------------------------------------------------------------
/**
 * VTRANS �e�N�X�`���o�^�L�����Z��
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	id		�L�����Z������o�^ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_TexTransCancel( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int i = 0;
	BLACT_VTRANS_WORK *work = cont->vtrans_work;
	VTEX_WORK *tex = work->vtex_work_tbl;
	
	work->access_flag = TRUE;
	
	while( i < work->max ){
		if( tex->resm_tex != NULL && tex->resm_tex_id == id ){
			tex->resm_tex = NULL;
			tex->trans_end = FALSE;
			break;
		}
		
		tex++;
		i++;
	}
	
	work->access_flag = FALSE;
}

//--------------------------------------------------------------
/**
 * VIntr TCB �e�N�X�`��VRAM�]��
 * @param	tcb			TCB_PTR
 * @param	wk			tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_TexTransVIntrTCB( TCB_PTR tcb, void *wk )
{
	FIELD_OBJ_BLACT_CONT *cont = wk;
	BLACT_VTRANS_WORK *work = cont->vtrans_work;
	
	if( work->access_flag == TRUE ){
		return;
	}
	
	{
		int i = 0;
		VTEX_WORK *tex = work->vtex_work_tbl;
		
		while( i < work->max ){
			if( tex->trans_end == FALSE && tex->resm_tex != NULL ){
				TEXRESM_TexLoadID( tex->resm_tex, tex->resm_tex_id );
				tex->trans_end = TRUE;
			}
			
			tex++;
			i++;
		}
	}
}

//--------------------------------------------------------------
/**
 * VWait TCB �e�N�X�`�����\�[�X�j��
 * @param	tcb			TCB_PTR
 * @param	wk			tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_TexFreeVWaitTCB( TCB_PTR tcb, void *wk )
{
	int i = 0;
	FIELD_OBJ_BLACT_CONT *cont = wk;
	BLACT_VTRANS_WORK *work = cont->vtrans_work;
	VTEX_WORK *tex = work->vtex_work_tbl;
	
	work->access_flag = TRUE;
	
	while( i < work->max ){
		if( tex->trans_end == TRUE && tex->resm_tex != NULL ){
			TEXRESM_CutTexID( tex->resm_tex, tex->resm_tex_id );
			tex->trans_end = FALSE;
			tex->resm_tex = NULL;
		}
		
		tex++;
		i++;
	}
	
	work->access_flag = FALSE;
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�ǉ��\��B
 * �Ă񂾍ہAact��NULL�ŏ������B
 * �Ǘ����Ńr���{�[�h�A�N�^�[���ǉ������Ƃ��̃A�h���X���i�[�����B
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	code	�\���R�[�h
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActAddReserveSet(
	FIELD_OBJ_BLACT_CONT *cont, FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR *act, int code )
{
	int i = 0;
	BLACT_VTRANS_WORK *work = cont->vtrans_work;
	BLACTADD_RESERVE *res = work->blact_reserve_work_tbl;
	
	while( i < work->max ){
		if( res->fldobj == NULL ){
			res->fldobj = fldobj;
			res->act = act;
			res->code = code;
			
			*(res->act) = NULL;
			FieldOBJ_BlActAddPracFlagSet( fldobj, TRUE );
			return;
		}
		
		res++;
		i++;
	}
	
	GF_ASSERT( 0 && "FldOBJ_BlActAddReserveSet() TABLE MAX ERROR" );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�ǉ��\��L�����Z��
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	code	�\���R�[�h
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActAddReserveCancel( FIELD_OBJ_BLACT_CONT *cont, CONST_FIELD_OBJ_PTR fldobj )
{
	int i = 0;
	BLACT_VTRANS_WORK *work = cont->vtrans_work;
	BLACTADD_RESERVE *res = work->blact_reserve_work_tbl;
	
	while( i < work->max ){
		if( res->fldobj == fldobj ){
			res->fldobj = NULL;
			res->act = NULL;
			
			OS_Printf( "FieldOBJ BlAct Add Cancel\n" );
			return;
		}
		
		res++;
		i++;
	}
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�ǉ��\�����
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActAddReserve( FIELD_OBJ_BLACT_CONT *cont )
{
	int i = 0;
	BLACT_VTRANS_WORK *work = cont->vtrans_work;
	BLACTADD_RESERVE *res = work->blact_reserve_work_tbl;
	
	while( i < work->max ){
		if( res->fldobj != NULL ){
			FldOBJ_BlActAddReserve_Add( cont, res );
		}
		
		res++;
		i++;
	}
}

//--------------------------------------------------------------
/**
 * TCB �r���{�[�h�A�N�^�[�ǉ��\�����
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActAddReserveTCB( TCB_PTR tcb, void *wk )
{
	FIELD_OBJ_BLACT_CONT *cont = wk;
	FldOBJ_BlActAddReserve( cont );
}

//--------------------------------------------------------------
/**
 * �r���{�[�h�A�N�^�[�ǉ��\������@�ǉ�����
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	res		BLACTADD_RESERVE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActAddReserve_Add(
		FIELD_OBJ_BLACT_CONT *cont, BLACTADD_RESERVE *res )
{
	if( FldOBJ_BlActResManage_OBJCodeRegistCheck(cont,res->code) != NOT_REGULAR_GUEST ){
		*(res->act) = FieldOBJ_BlActAddCode( res->fldobj, res->code );
		GF_ASSERT(*(res->act)!=NULL&&"FldOBJ_BlActAddReserve_CodeCheckAdd()ERROR");
		
		FieldOBJ_BlActAddPracFlagSet( res->fldobj, FALSE );
		
		if( FieldOBJ_StatusBit_CheckEasy(res->fldobj,FLDOBJ_STA_BIT_DRAW_PUSH) == TRUE ){
			FieldOBJ_DrawPopProcCall( res->fldobj );
		}else{
			FieldOBJ_DrawProcCall( res->fldobj );
		}
		
		res->fldobj = NULL;
		res->act = NULL;
	}
}

//--------------------------------------------------------------
/**
 * BLACT_VTRANS_WORK������
 * @param	cont		FIELD_OBJ_BLACT_CONT
 * @param	max			�e�v�f�ő吔
 * @param	load_max	1�t���[���e�N�X�`�����[�h�񐔍ő�
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActVTransWorkInit( FIELD_OBJ_BLACT_CONT *cont, int max, int load_max )
{
	u32 ret,size,vtex_size,texload_size,blactadd_size;
	BLACT_VTRANS_WORK *work;
	
	blactadd_size = BLACTADD_RESERVE_SIZE * max;
	texload_size = TEXLOAD_WORK_SIZE * max;
	vtex_size = VTEX_WORK_SIZE * max;
	size = BLACT_VTRANS_WORK_SIZE + vtex_size + texload_size + blactadd_size;
	
	work = sys_AllocMemory( HEAPID_FIELD, size );
	GF_ASSERT( work != NULL );
	
	memset( work, 0, size );
	
	work->max = max;
	work->load_max = load_max;
	
	ret = (u32)work + BLACT_VTRANS_WORK_SIZE;
	work->blact_reserve_work_tbl = (void *)ret;
	
	ret += blactadd_size;
	work->tex_load_work_tbl = (void *)ret;
	
	ret += texload_size;
	work->vtex_work_tbl = (void *)ret;
	
	cont->vtrans_work = work;
	
	ret = FieldOBJSys_TCBStandardPriorityGet( cont->fos );
	work->tcb_load = TCB_Add( FldOBJ_TexLoadReserveTCB, cont, ret + 1 );
	work->tcb_blactadd = TCB_Add( FldOBJ_BlActAddReserveTCB, cont, ret + 2 );
	work->tcb_vintr = VIntrTCB_Add( FldOBJ_TexTransVIntrTCB, cont, 0xff );
	work->tcb_vwait = VWaitTCB_Add( FldOBJ_TexFreeVWaitTCB, cont, 0xff );
}

//--------------------------------------------------------------
/**
 * BLACT_VTRANS_WORK�폜
 * @param	cont		FIELD_OBJ_BLACT_CONT
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActVTransWorkDelete( FIELD_OBJ_BLACT_CONT *cont )
{
	BLACT_VTRANS_WORK *work = cont->vtrans_work;
	
	work->access_flag = TRUE;
	
	TCB_Delete( work->tcb_load );
	TCB_Delete( work->tcb_blactadd );
	TCB_Delete( work->tcb_vintr );
	TCB_Delete( work->tcb_vwait );
	
	sys_FreeMemoryEz( work );
	cont->vtrans_work = NULL;
}

//==============================================================================
///	�_�~�[�A�N�^�[�ǉ���A���K�A�N�^�[�ǉ�
//==============================================================================
typedef struct
{
	int code;
	int seq_no;
	void *res_mdl;
	void *res_anm;
	void *res_tex;
	TEXANM_DATATBL data_anm;
	BLACT_WORK_PTR act;
	BLACT_HEADER head;
	FIELD_OBJ_PTR fldobj;
	EOA_PTR eoa_reflect;
}BLACTDMY_WORK;

static void FldOBJ_BlActDummyDrawResetSet( FIELD_OBJ_PTR fldobj, int code );
static void BlActDummyActDeleteTCB( TCB_PTR tcb, void *wk );

//--------------------------------------------------------------
/**
 * �_�~�[�A�N�^�[��\�������Ȃ��琳�K�A�N�^�[�֕ύX
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	code	�ύX����R�[�h HERO��
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActDummyDrawReset( FIELD_OBJ_PTR fldobj, int code )
{
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ||
		FieldOBJ_DrawBlAct00_BlActPtrGet(fldobj) == NULL ){
		int old = FieldOBJ_OBJCodeGet( fldobj );
		CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet( fldobj );
		FieldOBJ_DrawDelete( fldobj );
		FieldOBJ_BlActResm_ResIDGuestUseCheckDelete( fos, old, fldobj );
		FieldOBJ_DrawResetAlone( fldobj, code );
		return;
	}
	
	FldOBJ_BlActDummyDrawResetSet( fldobj, code );
}

//--------------------------------------------------------------
/**
 * �_�~�[�A�N�^�[��\�������Ȃ��琳�K�A�N�^�[�֕ύX�@�Z�b�g����
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	code	�ύX����R�[�h HERO��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActDummyDrawResetSet( FIELD_OBJ_PTR fldobj, int code  )
{
	VecFx32 vec;
	int i,old,id,pri;
	TEXRES_OBJ_PTR texobj;
	const FIELD_OBJ_RESMNARC *tbl;
	FIELD_OBJ_BLACT_CONT *cont =  FldOBJ_BlActContGetLocal( fldobj );
	BLACT_SET_PTR set = FieldOBJ_BlActCont_SetPtrGet( cont );
	BLACT_WORK_PTR oldact = FieldOBJ_DrawBlAct00_BlActPtrGet( fldobj );
	BLACTDMY_WORK *work = sys_AllocMemoryLo( HEAPID_FIELD, sizeof(BLACTDMY_WORK) );
	
	memset( work, 0, sizeof(BLACTDMY_WORK) ); 
	
	work->code = code;
	work->fldobj = fldobj;
	
	old = FieldOBJ_OBJCodeGet( fldobj );
	OS_Printf( "FLDOBJ DUMMY BLACT ADD OLD CODE=0x%x,NEW CODE=0x%x\n", old, code );
	
	{
		i = 0;
		id = FldOBJ_BlActH_OBJCode_MdlID( old );
		tbl = DATA_FieldOBJ_ResmNArcTbl_Mdl;
		do{ if( tbl->id == id ){ break; } tbl++; i++; }while( tbl->id != BLACT_MDLID_MAX );
		GF_ASSERT( tbl->id != BLACT_MDLID_MAX && "ERROR" );
		work->res_mdl = FldOBJ_BlActContArcDataAlloc( cont, tbl->narc_id, FALSE );
	}
	
	{
		i = 0;
		id = FldOBJ_BlActH_OBJCode_AnmID( old );
		tbl = DATA_FieldOBJ_ResmNArcTbl_Anm;
		do{ if( tbl->id == id ){ break; } tbl++; i++; }while( tbl->id != BLACT_ANMID_MAX );
		GF_ASSERT( tbl->id != BLACT_ANMID_MAX && "ERROR" );
		work->res_anm = FldOBJ_BlActContArcDataAlloc( cont, tbl->narc_id, FALSE );
		TEXANM_UnPackLoadFile( work->res_anm, &work->data_anm );
	}
	
	{
		i = 0;
		id = old;
		tbl = DATA_FieldOBJ_ResmNArcTbl_Tex;
		do{ if( tbl->id == id ){ break; } tbl++; i++; }while( tbl->id != OBJCODEMAX );
		GF_ASSERT( tbl->id != OBJCODEMAX && "ERROR" );
		work->res_tex = FldOBJ_BlActContArcDataAlloc( cont, tbl->narc_id, FALSE );
	}
	
	BLACT_MakeHeaderVramAnm( &work->head,
		work->res_mdl,
		NNS_G3dGetTex(work->res_tex),
		FldOBJ_BlActH_OBJCode_AnmTbl(old), &work->data_anm );
	
	{
		const VecFx32 *actvec = BLACT_MatrixGet( oldact );
		vec = *actvec;
//		vec.z += GRID_FX32*2;
		work->act = FldOBJ_BlActAdd( set, &work->head, &vec );
		GF_ASSERT( work->act != NULL && "ERROR" );
	}
	
	BLACT_AnmOffsChg( work->act, BLACT_AnmOffsGet(oldact) );
	BLACT_AnmFrameSetOffs( work->act, BLACT_AnmFrameGetOffs(oldact) );
	BLACT_AnmFrameSet( work->act, BLACT_AnmFrameGet(oldact) );
	BLACT_AnmFrameChg( work->act, 0 );
	BLACT_ObjDrawFlagSet( work->act, TRUE );
	BLACT_VramAnmTransUserReq( work->act );
	
	{	//�f�荞�݃A��
		if( FieldOBJ_StatusBitCheck_Reflect(fldobj) == TRUE ){
			VecFx32 mtx;
			int pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
			MATR attr = FieldOBJ_NextDirAttrGet( fldobj, DIR_DOWN );
			REFTYPE type = REFTYPE_POOL;
			
			if( MATR_IsPoolCheck(attr) == FALSE ){
				type = REFTYPE_POND;
			}
			
			FieldOBJ_VecPosGet( fldobj, &mtx );
			
			work->eoa_reflect = FE_EoaReflectSole_Add(
				FE_FieldOBJ_FE_SYS_Get(fldobj), &work->head, work->act, &mtx, type, pri );
		}
	}
	
	FieldOBJ_DrawDelete( fldobj );
	FieldOBJ_BlActResm_ResIDGuestUseCheckDelete( cont->fos, old, fldobj );
	FieldOBJ_DrawResetAlone( fldobj, code );
	
	{
		int pri = FieldOBJSys_TCBStandardPriorityGet( cont->fos );
		TCB_PTR tcb = VWaitTCB_Add( BlActDummyActDeleteTCB, work, 0xff );
		GF_ASSERT( tcb != NULL && "ERROR" );
		BlActDummyActDeleteTCB( tcb, work );	//�O�̈׌Ă�ł݂�
	}
}

//--------------------------------------------------------------
/**
 * TCB �_�~�[�A�N�^�[����
 * @param	tcb	TCB_PTR
 * @param	wk	tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void BlActDummyActDeleteTCB( TCB_PTR tcb, void *wk )
{
	BLACTDMY_WORK *work = wk;
	FIELD_OBJ_PTR fldobj = work->fldobj;
	
	switch( work->seq_no ){
	case 0:
		if( FieldOBJ_StatusBitCheck_Use(fldobj) == FALSE 	||
			FieldOBJ_BlActAddPracFlagCheck(fldobj) == FALSE ){
			if( work->eoa_reflect != NULL ){
				EOA_Delete( work->eoa_reflect );
			}
			
			BLACT_Delete( work->act );
			sys_FreeMemoryEz( work->res_mdl );
			sys_FreeMemoryEz( work->res_anm );
			sys_FreeMemoryEz( work->res_tex );
			sys_FreeMemoryEz( work );
			TCB_Delete( tcb );
			return;
		}
		
		if( FieldOBJ_OBJCodeGet(fldobj) != work->code ){
			work->seq_no++;
		}
		
		break;
	case 1:
		if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == FALSE ){
			if( work->eoa_reflect != NULL ){
				EOA_Delete( work->eoa_reflect );
			}
			
			BLACT_Delete( work->act );
			sys_FreeMemoryEz( work->res_mdl );
			sys_FreeMemoryEz( work->res_anm );
			sys_FreeMemoryEz( work->res_tex );
			sys_FreeMemoryEz( work );
			TCB_Delete( tcb );
		}
	}
}

