//******************************************************************************
/**
 *
 * @file	fieldobj_blact.c
 * @brief	フィールドOBJ ビルボードアクター関連
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
///	登録結果
//--------------------------------------------------------------
typedef enum
{
	ADDRES_REGIST = 0,										///<登録済み
	ADDRES_RESERVE,											///<登録を予約
	ADDRES_NOTBLACT,										///<ビルボードではない
}ADDRES_TYPE;

//==============================================================================
//	typedef struct
//==============================================================================
#if 0
//--------------------------------------------------------------
///	GUEST_BLACT_ADD_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	int code;												///<表示するOBJコード
	FIELD_OBJ_PTR	fldobj;									///<追加する対象のFIELD_OBJ_PTR
	BLACT_WORK_PTR	*act;									///<追加されたビルボード *格納先
}GUEST_BLACT_ADD_WORK;

///GUEST_BLACT_ADD_WORKサイズ
#define GUEST_BLACT_ADD_WORK_SIZE (sizeof(GUEST_BLACT_ADD_WORK))
///BLACT_ADD_TBL総サイズ
#define GUEST_BLACT_ADD_WORK_ALL_SIZE (GUEST_BLACT_ADD_WORK_SIZE*FLDOBJ_RESM_MAX_TEX)
#endif

#if 0
//--------------------------------------------------------------
///	VINTR_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	vu32 access_flag;										///<アクセス中フラグ
	int max;
	FIELD_OBJ_BLACT_CONT *cont;								///<FIELD_OBJ_BLACT_CONT *
	TEXRES_MANAGER_PTR *resm_tex_tbl;						///<転送テクスチャテーブル
	int *resm_tex_id_tbl;									///<転送IDテーブル
}VINTR_WORK;

#define VINTR_WORK_SIZE (sizeof(VINTR_WORK))				///<VINTR_WORKサイズ
#endif

//==============================================================================
//	プロトタイプ
//==============================================================================
static void FldOBJ_BlActAdd_GuestCancel( CONST_FIELD_OBJ_PTR fldobj );
	
#if 0 //不要
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
//	ビルボードアクター関連
//==============================================================================
//--------------------------------------------------------------
/**
 * ビルボードアクターコントロール初期化
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	max		アクター最大数
 * @param	pri		ゲストビルボードアクター追加管理TCB処理プライオリティ
 * @param	tex_max		テクスチャ最大数
 * @param	reg_tex_max	レギュラーテクスチャ登録最大数
 * @param	rg_tex_tbl	レギュラーテクスチャテーブル
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
 * ビルボードアクターコントロール削除
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
 * フィールドOBJからビルボードアクター追加。
 * fldobjに格納されている表示コード、座標からアクター追加する。
 * レギュラー、ゲストチェックを行い、ゲストの場合はゲスト追加テーブルへ追加予約。
 * この関数を呼んだ際、actはNULLで初期化される。
 * 追加され次第、actへ追加されたBLACT_WORK_PTRが格納される。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	act			BLACT_WORK_PTR格納先
 * @param	code		表示するコード。HERO等
 * @retval	TEXREG_TYPE TEX_REGULAR等。TEX_REGULAR,TEX_GUEST以外=追加テーブルへ予約。
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
	
	if( ret == TEX_NON ){											//事前登録何も無し
		FieldOBJ_BlActAdd_Guest( fldobj, act, code );
		return( ret );
	}
	
	if( ret == TEX_REGULAR_RESERVE || ret == TEX_GUEST_RESERVE ){	//テクスチャ転送予約アリ
		FldOBJ_BlActAddReserveSet( cont, fldobj, act, code );
		return( ret );
	}
	
	*act = FieldOBJ_BlActAddCode( fldobj, code );
	return( ret );
}

//--------------------------------------------------------------
/**
 * フィールドOBJからビルボードアクター追加。
 * fldobjに格納されている表示コード、座標からアクター追加する。
 * OBJコードはフィールドOBJ内から取得。
 * レギュラー、ゲストチェックを行い、ゲストの場合はゲスト追加テーブルへ追加予約。
 * この関数を呼んだ際、actはNULLで初期化される。
 * 追加され次第、actへ追加されたBLACT_WORK_PTRが格納される。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	act			BLACT_WORK_PTR格納先
 * @retval	TEXREG_TYPE TEX_REGULAR等。TEX_REGULAR,TEX_GUEST以外=追加テーブルへ予約。 
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
 * フィールドOBJからビルボードアクター追加。表示コード指定。
 * fldobjに格納されている表示コード、座標からアクター追加
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	code		表示するコード。HERO等
 * @retval	BLACT_WORK 	NULL=追加失敗
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
 * ビルボードアクター削除
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
 * ビルボードアクター削除
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
 * ビルボードアクター削除
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
 * ビルボードアクターアニメ退避。
 * アニメーション情報、表示、非表示スイッチの退避を行う
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
 * ビルボードアクターアニメ復帰。
 * FieldOBJ_BlActAnmPush()で退避した情報をアクターに反映
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
//	ビルボードアクター　ゲスト追加
//==============================================================================
//--------------------------------------------------------------
/**
 * ゲストビルボードアクター追加管理へ予約。
 * 呼んだ際、actはNULLで初期化。
 * 管理側でビルボードアクターが追加されるとそのアドレスが格納される。
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		追加されたアクター格納先
 * @param	code	表示するOBJコード HERO等
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
 * ゲストビルボードアクター追加管理予約キャンセル
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	code	表示するOBJコード HERO等
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
 * ゲストビルボードアクター追加管理TCB追加
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	pri		追加管理TCB処理プライオリティ
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
 * ゲストビルボードアクター追加管理TCB削除
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
 * TCB ゲストビルボードアクター追加管理処理
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
			
			{	//追加したOBJコードと同一のものを直後に追加
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
//	ビルボードアクターヘッダー管理
//==============================================================================
//--------------------------------------------------------------
/**
 * ビルボードアクターヘッダー管理領域確保
 * @param	cont		FIELD_OBJ_BLACT_CONT*
 * @param	max			ヘッダー最大数
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
 * ビルボードアクターヘッダー管理領域削除
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
 * ビルボードアクターヘッダー管理領域取得
 * @param	cont			FIELD_OBJ_BLACT_CONT
 * @param	code			取得するOBJコード。HERO等
 * @retval	BLACT_HEADER	ヘッダー領域への*。NULL=失敗
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
 * ビルボードアクターヘッダー管理領域取得。グローバル
 * @param	cont			FIELD_OBJ_BLACT_CONT
 * @param	code			取得するOBJコード。HERO等
 * @param	head			ヘッダー情報格納先
 * @retval	int				TRUE=格納完了。FALSE=登録されていない
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
 * ビルボードアクターヘッダー管理領域開放
 * @param	cont			FIELD_OBJ_BLACT_CONT
 * @param	code			開放するOBJコード。HERO等
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
 * ビルボードアクターヘッダー管理領域強制開放
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
 * 現在発生しているフィールドOBJのOBJコードを参照
 * @param	sys			FIELD_OBJ_SYS_PTR 
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	code		チェックするコード。HERO等
 * @retval	int			TRUE=fldobj以外にもcodeを持っている奴がいる
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
//	リソースマネージャ設定
//==============================================================================
//--------------------------------------------------------------
/**
 * リソースマネージャ初期化
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	mdl_max		モデル管理最大数
 * @param	mdl_reg_max	モデル管理レギュラー最大数
 * @param	anm_max		アニメ管理最大数
 * @param	anm_reg_max	アニメ管理レギュラー最大数
 * @param	tex_max		テクスチャ管理最大数
 * @param	tex_reg_max	テクスチャレギュラー管理最大数
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
 * リソースマネージャ全削除
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	mdl_max	モデル管理最大数
 * @param	anm_max	アニメ管理最大数
 * @param	tex_max	テクスチャ管理最大数
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
 * FIELD_OBJ_RESMH検索
 * @param	id				検索ID
 * @param	tbl				検索テーブル
 * @retval	FIELD_OBJ_RESMH	一致するデータ。NULL=一致無し
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
 * FIELD_OBJ_RESMNARC検索
 * @param	id				検索ID
 * @param	max_id			終端ID
 * @param	tbl				検索テーブル
 * @retval	FIELD_OBJ_RESMNARC	一致するデータ。NULL=一致無し
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
 * 指定されたRES_MANAGER_PTR、ID、FIELD_OBJ_RESMNARCから登録
 * @param	resm	RES_MANAGER_PTR
 * @param	id		登録するID
 * @param	max		tbl終端ID
 * @param	tbl		FIELD_OBJ_RESMH
 * @retval	int		TRUE=登録。FALSE=登録済み
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
 * 指定されたRES_MANAGER_PTR、ID、FIELD_OBJ_RESMHから登録
 * @param	resm	RES_MANAGER_PTR
 * @param	id		登録するID
 * @param	tbl		FIELD_OBJ_RESMH
 * @retval	int		TRUE=登録。FALSE=登録済み
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
 * 指定されたRES_MANAGER_PTR、ID、FIELD_OBJ_RESMHから登録 Noraml
 * @param	resm	RES_MANAGER_PTR
 * @param	id		登録するID
 * @param	tbl		FIELD_OBJ_RESMH
 * @retval	int		TRUE=登録。FALSE=登録済み
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
 * 指定されたテクスチャID、FIELD_OBJ_RESMNARCから登録
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	reg_type	REGULAR_GUEST
 * @param	id			登録するID
 * @param	tbl			FIELD_OBJ_RESMNARC
 * @retval	int			ADDRES_FALSE等
 */
//--------------------------------------------------------------
static ADDRES_TYPE FldOBJ_BlActTexResmNArc_AddResTbl( FIELD_OBJ_BLACT_CONT *cont,
		REGULAR_GUEST reg_type, int id, const FIELD_OBJ_RESMNARC *tbl )
{
	TEXRES_MANAGER_PTR resm = cont->tex_res_manage;
	
	if( TEXRESM_CheckID(resm,id) == FALSE ){						//登録済み
		return( ADDRES_REGIST );
	}
	
	if( FldOBJ_TexLoadReserveCheck(cont,id) != TEX_NON ){			//予約アリ
		return( ADDRES_RESERVE );
	}
	
	{
		TEXRES_OBJ_PTR res;
		const FIELD_OBJ_RESMNARC *head = FldOBJ_BlActResmNArc_Search( id, OBJCODEMAX, tbl );
		
		if( head == NULL ){
			return( ADDRES_NOTBLACT );
		}
		
		if( FldOBJ_TexLoadTransSet(cont,id,head->narc_id,reg_type) == TRUE ){
			return( ADDRES_REGIST );								//その場で登録できた
		}
		
		return( ADDRES_RESERVE );									//登録予約
	}
}

//--------------------------------------------------------------
/**
 * レギュラーテクスチャ登録
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		登録するID
 * @retval	ADDRES_TYPE ADDRES_TYPE
 */
//--------------------------------------------------------------
static ADDRES_TYPE FldOBJ_BlActResm_RegularAdd_Tex( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	return( FldOBJ_BlActTexResmNArc_AddResTbl(cont,REGULAR,id,DATA_FieldOBJ_ResmNArcTbl_Tex) );
}

//--------------------------------------------------------------
/**
 * レギュラーテクスチャ登録　グローバル
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	id		登録するID
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
 * レギュラーテクスチャ削除
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	id		削除するID
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
 * ゲストテクスチャ登録
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		登録するID
 * @retval	ADDRES_TYPE ADDRES_TYPE
 */
//--------------------------------------------------------------
static ADDRES_TYPE FldOBJ_BlActResm_GuestAdd_Tex( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	return( FldOBJ_BlActTexResmNArc_AddResTbl(cont,GUEST,id,DATA_FieldOBJ_ResmNArcTbl_Tex) );
}

//--------------------------------------------------------------
/**
 * レギュラーテクスチャ複数登録
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	tbl		登録するIDが纏められたテーブル
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
 * レギュラーモデル登録
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		登録するID
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
 * ゲストモデル登録
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		登録するID
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
 * レギュラーモデル複数登録
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	tbl		登録するIDが纏められたテーブル
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
 * レギュラーアニメ登録
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		登録するID
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
 * レギュラーアニメ登録　グローバル
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	id		登録するID
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
 * レギュラーアニメ削除
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	id		削除するID
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
 * ゲストアニメ登録
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		登録するID
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
 * レギュラーアニメ複数登録
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	tbl		登録するIDが纏められたテーブル
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
 * レギュラー勢一斉登録
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	tex_tbl	レギュラーテクスチャ
 * @param	mdl_tbl	レギュラーテクスチャ
 * @param	anm_tbl	レギュラーテクスチャ
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
 * リソースID管理　初期化
 * @param	tbl		IDテーブル　*
 * @param	init_id	初期化ID
 * @param	max		初期化数
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
 * リソースID管理　登録
 * @param	tbl		IDテーブル　*
 * @param	reg_id	登録ID
 * @param	spc_id　空きID
 * @param	max		検索数
 * @retval	int		TRUE=登録　FALSE=空き無し
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
 * リソースID管理　検索
 * @param	tbl		IDテーブル　*
 * @param	chk_id	検索ID
 * @param	max		検索数
 * @retval	int		TRUE=登録アリ　FALSE=登録ナシ
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
 * リソースID管理　削除
 * @param	tbl		IDテーブル　*
 * @param	del_id		削除するID
 * @param	spc_id	削除後の空きID
 * @param	max		検索数
 * @retval	int		TRUE=削除完了　FALSE=登録ナシ
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
 * モデルリソースID管理　テーブル初期化
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
 * モデルリソースID管理　レギュラー登録。
 * 空きが無い場合はGF_ASSERT()
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			登録ID
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
 * モデルリソースID管理　レギュラー検索
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			検索ID
 * @retval	int			TRUE=登録済みID FALSE=一致無し
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
 * モデルリソースID管理　ゲスト登録。
 * 空きが無い場合はGF_ASSERT()
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			登録ID
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
 * モデルリソースID管理　ゲスト検索
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			検索ID
 * @retval	int			TRUE=登録済みID FALSE=一致無し
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
 * モデルリソースID管理　ゲスト削除
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			削除ID
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
 * モデルリソースID管理　全ゲスト削除。現存するOBJ内で使用している場合は削除せず
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
 * モデルリソースID管理　ゲスト削除。現存するOBJ内で使用している場合は削除せず
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
 * モデルリソースID管理　ゲスト削除。現存するOBJ内で使用している場合は削除せず。グローバル
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
 * アニメリソースID管理　テーブル初期化
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
 * アニメリソースID管理　レギュラー登録。
 * 空きが無い場合はGF_ASSERT()
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			登録ID
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
 * アニメリソースID管理　レギュラー検索
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			検索ID
 * @retval	int			TRUE=登録済みID FALSE=一致無し
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
 * アニメリソースID管理　ゲスト登録。
 * 空きが無い場合はGF_ASSERT()
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			登録ID
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
 * アニメリソースID管理　ゲスト検索
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			検索ID
 * @retval	int			TRUE=登録済みID FALSE=一致無し
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
 * アニメリソースID管理　ゲスト削除
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			削除ID
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
 * アニメリソースID管理　全ゲスト削除　現存するOBJで使用している場合は削除しない
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
 * テクスチャリソースID管理　テーブル初期化
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
 * テクスチャリソースID管理　レギュラー登録。
 * 空きが無い場合はGF_ASSERT()
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			登録ID
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
 * テクスチャリソースソースID管理　レギュラー検索
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			検索ID
 * @retval	int			TRUE=登録済みID FALSE=一致無し
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
 * テクスチャリソースソースID管理　総合検索
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			検索ID
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
 * テクスチャリソースID管理　ゲスト登録。
 * 空きが無い場合はGF_ASSERT()
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			登録ID
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
 * テクスチャリソースID管理　ゲスト削除
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			削除ID
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
 * テクスチャリソースID管理　全ゲスト削除。現存しているOBJで使用している場合は削除しない
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
 * テクスチャリソースソースID管理　ゲスト検索
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	id			検索ID
 * @retval	int			TRUE=登録済みID FALSE=一致無し
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
 * 指定されたOBJコードのレギュラー、ゲスト登録済みチェック
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	code	OBJコード。HERO等
 * @retval	int		REGULAR等
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
 * 指定されたモデルIDのレギュラー、ゲスト登録済みチェック
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		BLACT_MDLID_32x32等
 * @retval	int		REGULAR等
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
 * 指定されたモデルIDのレギュラー、ゲスト登録済みチェック
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		BLACT_MDLID_32x32等
 * @retval	int		REGULAR等
 */
//--------------------------------------------------------------
int FieldOBJ_BlActResManage_MdlIDRegistCheck( CONST_FIELD_OBJ_SYS_PTR fos, int id )
{
	FIELD_OBJ_BLACT_CONT *cont = FieldOBJSys_BlActContGet( fos );
	return( FldOBJ_BlActResManage_MdlIDRegistCheck(cont,id) );
}

//--------------------------------------------------------------
/**
 * 指定されたアニメIDのレギュラー、ゲスト登録済みチェック
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		BLACT_ANMID_32x32等
 * @retval	int		REGULAR等
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
 * 指定されたOBJコードの登録。
 * レギュラー、ゲストチェックを行い、レギュラーで無い場合はゲストとして登録
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	code	OBJコード。HERO等
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
 * 指定されたモデルIDの登録。
 * レギュラー、ゲストチェックを行い、レギュラーで無い場合はゲストとして登録
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		BLACT_MDLID_32x32等
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
 * 指定されたアニメIDの登録。
 * レギュラー、ゲストチェックを行い、レギュラーで無い場合はゲストとして登録
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		BLACT_ANMID_NORMAL_0等
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
 * OBJコードから、モデル、テクスチャ、アニメのレギュラー、ゲストチェック。
 * 登録されていない箇所あればゲストとして登録。
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	code	OBJコード。HERO等
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
 * ゲストテクスチャ、モデル、アニメを全て削除
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
 * 現存するフィールドOBJのOBJコード検索
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	code	OBJコード
 * @retval	int		TRUE=一致アリ FALSE=一致無し
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
 * 現存するフィールドOBJのOBJコード検索　グローバル
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	code	OBJコード
 * @retval	int		TRUE=一致アリ FALSE=一致無し
 */
//--------------------------------------------------------------
int FieldOBJ_BlActCont_FldOBJSearch_OBJCode(
	FIELD_OBJ_SYS_PTR fos, int code, CONST_FIELD_OBJ_PTR ignore_obj )
{
	return( FieldOBJ_BlActCont_FldOBJSearch_OBJCode(fos,code,ignore_obj) );
}

//--------------------------------------------------------------
/**
 * 現存するフィールドOBJのモデルID検索
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	mdl_id	モデル ID
 * @param	ignore_obj	無視するFIELD_OBJ_PTR 無い場合はNULL
 * @retval	int		TRUE=一致アリ FALSE=一致無し
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
 * 現存するフィールドOBJのモデルID検索　グローバル
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	mdl_id	モデル ID
 * @param	ignore_obj	無視するFIELD_OBJ_PTR 無い場合はNULL
 * @retval	int		TRUE=一致アリ FALSE=一致無し
 */
//--------------------------------------------------------------
int FieldOBJ_BlActCont_FldOBJSearch_MdlID(
	CONST_FIELD_OBJ_SYS_PTR fos, int mdl_id, CONST_FIELD_OBJ_PTR ignore_obj )
{
	return( FldOBJ_BlActCont_FldOBJSearch_MdlID(fos,mdl_id,ignore_obj) );
}

//--------------------------------------------------------------
/**
 * 現存するフィールドOBJのアニメID検索
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	anm_id	アニメ ID
 * @param	ignore_obj	無視するFIELD_OBJ_PTR NULL=無効
 * @retval	int		TRUE=一致アリ FALSE=一致無し
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
 * 現存するフィールドOBJのアニメID検索　グローバル
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	anm_id	アニメ ID
 * @param	ignore_obj	無視するFIELD_OBJ_PTR NULL=無効
 * @retval	int		TRUE=一致アリ FALSE=一致無し
 */
//--------------------------------------------------------------
int FieldOBJ_BlActCont_FldOBJSearch_AnmID(
	FIELD_OBJ_SYS_PTR fos, int anm_id, CONST_FIELD_OBJ_PTR ignore_obj )
{
	return( FldOBJ_BlActCont_FldOBJSearch_AnmID(fos,anm_id,ignore_obj) );
}

//--------------------------------------------------------------
/**
 * リソースID管理　ゲスト削除　現存するOBJ内で使用している項目は削除せず
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	code	OBJコード
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
//	VIntrタスク
//==============================================================================
#if 0
//--------------------------------------------------------------
/**
 * VIntr TCB追加
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	max		Vブランク割り込み中に転送出来る回数最大
 * @param	pri		VIntrTCB処理プライオリティ
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
		GF_ASSERT( check_tcb == NULL &&						//NULLのはず
			"FldOBJ_BlActVIntrTcbAdd() 描画削除が済んでいないのに フィールドOBJ描画初期化?\n" );
	}
	
	work = sys_AllocMemory( HEAPID_FIELD, VINTR_WORK_SIZE );
	GF_ASSERT( work != NULL && "FldOBJ_BlActVIntrTcbAdd()メモリ確保失敗" );
	memset( work, 0, VINTR_WORK_SIZE );
	
	work->max = max;
	work->cont = cont;
	
	size = sizeof( TEXRES_MANAGER_PTR ) * max;
	work->resm_tex_tbl = sys_AllocMemory( HEAPID_FIELD, size );
	GF_ASSERT( work->resm_tex_tbl != NULL && "FldOBJ_BlActVIntrTcbAdd()TEXテーブル確保失敗" );
	memset( work->resm_tex_tbl, NULL, size );
	
	size = sizeof( int ) * max;
	work->resm_tex_id_tbl = sys_AllocMemory( HEAPID_FIELD, size );
	GF_ASSERT( work->resm_tex_id_tbl != NULL && "FldOBJ_BlActVIntrTcbAdd()IDテーブル確保失敗" );
	memset( work->resm_tex_id_tbl, 0, size );
	
	tcb = VIntrTCB_Add( FldOBJ_VIntrTcb, work, pri );
	GF_ASSERT( tcb != NULL && "FldOBJ_BlActVIntrTcbAdd()TCB追加失敗" );
	
	FldOBJ_BlActContVIntrTcbPtrSet( cont, tcb );
}
#endif

#if 0
//--------------------------------------------------------------
/**
 * VIntr TCB削除
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
 * TCB Vブランク処理
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
	GF_ASSERT( work != NULL && "FldOBJ_VIntrTcb()ワーク異常" );
	
	if( work->access_flag == TRUE ){
		OS_Printf( "FldOBJ_VIntrTcb()アクセス中に割り込み処理が発生しました\n" );
		OS_Printf( "このメッセージをご覧になった方はお手数ですが加賀谷まで連絡下さい\n" );
		return;
	}
	
	i = 0;
	count = 0;
	
	do{
		if( work->resm_tex_tbl[i] != NULL ){
			TEXRESM_TexLoadAndCutTexID( work->resm_tex_tbl[i], work->resm_tex_id_tbl[i] );
			work->resm_tex_tbl[i] = NULL;						//空に
			count++;
			
			if( count >= FLDOBJ_BLACT_VINTR_TEX_LOAD_MAX ){		//1sync転送量最大
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
 * TEXRESM_TexLoad() Vブランク処理へ登録
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	resm	TEXRES_MANAGER_PTR
 * @param	id		転送するテクスチャID
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
	
	GF_ASSERT( tcb != NULL && "FldOBJ_VIntrTcb_TexLoadAdd()TCB未追加で実行" );
	
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
	
	GF_ASSERT( i < work->max && "FldOBJ_VIntrTcb_TexLoadAdd()テクスチャ転送最大数越え" );
	work->access_flag = FALSE;
}
#endif

#if 0
//--------------------------------------------------------------
/**
 * TEXRESM_TexLoad() Vブランク処理へ登録していたモノをキャンセルする
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	id		登録したテクスチャID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_VIntrTcb_TexLoadCancel( FIELD_OBJ_BLACT_CONT *cont, int id )
{
	int i;
	TCB_PTR tcb;
	VINTR_WORK *work;
	
	tcb = FldOBJ_BlActContVIntrTcbPtrGet( cont );
	
	GF_ASSERT( tcb != NULL && "FldOBJ_VIntrTcb_TexLoadCancel()TCB未追加で実行" );
	
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
//	FIELD_OBJ_BLACT_CONT参照
//==============================================================================
//--------------------------------------------------------------
/**
 * BLACT_SET_PTRセット
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
 * BLACT_SET_PTR取得
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
 * ビルボードアクター最大数セット
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	max		最大数
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_BlActCont_MaxSet( FIELD_OBJ_BLACT_CONT *cont, int max )
{
	cont->max = max;
}

//--------------------------------------------------------------
/**
 * ビルボードアクター最大数取得
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	int		インデックス
 */
//--------------------------------------------------------------
int FieldOBJ_BlActCont_MaxGet( const FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->max );
}

//--------------------------------------------------------------
/**
 * モデルリソースマネージャ設定
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
 * モデルリソースマネージャ取得
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
 * アニメリソースマネージャ設定
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
 * アニメリソースマネージャ取得
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
 * テクスチャリソースマネージャ設定
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
 * テクスチャリソースマネージャ取得
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
 * リソースID テクスチャへの*を取得
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	int		IDテーブル int サイズはFLDOBJ_RESM_MAX_TEX
 */
//--------------------------------------------------------------
static int * FldOBJ_BlActCont_ResmTexIDTblGet( FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_tbl_tex );
}

//--------------------------------------------------------------
/**
 * リソースID モデルへの*を取得
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	int		IDテーブル int サイズはFLDOBJ_RESM_MAX_TEX
 */
//--------------------------------------------------------------
static int * FldOBJ_BlActCont_ResmMdlIDTblGet( FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_tbl_mdl );
}

//--------------------------------------------------------------
/**
 * レギュラーID アニメへの*を取得
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	int		IDテーブル int サイズはFLDOBJ_RESM_MAX_TEX
 */
//--------------------------------------------------------------
static int * FldOBJ_BlActCont_ResmAnmIDTblGet( FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_tbl_anm );
}

//--------------------------------------------------------------
/**
 * レギュラーID 最大管理数設定　モデル
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	max		最大数
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActCont_RegularMdlMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max )
{
	cont->resm_id_reg_max_mdl = max;
}

//--------------------------------------------------------------
/**
 * レギュラーID 最大管理数取得　モデル
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	max		最大数
 */
//--------------------------------------------------------------
static int FldOBJ_BlActCont_RegularMdlMaxGet( const FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_reg_max_mdl );
}

//--------------------------------------------------------------
/**
 * ゲストID 最大管理数設定　モデル
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	max		最大数
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActCont_GuestMdlMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max )
{
	cont->resm_id_gst_max_mdl = max;
}

//--------------------------------------------------------------
/**
 * ゲストID 最大管理数取得　モデル
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	int		最大数
 */
//--------------------------------------------------------------
static int FldOBJ_BlActCont_GuestMdlMaxGet( const FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_gst_max_mdl );
}

//--------------------------------------------------------------
/**
 * レギュラーID 最大管理数設定　アニメ
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	max		最大数
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActCont_RegularAnmMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max )
{
	cont->resm_id_reg_max_anm = max;
}

//--------------------------------------------------------------
/**
 * レギュラーID 最大管理数取得　アニメ
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	max		最大数
 */
//--------------------------------------------------------------
static int FldOBJ_BlActCont_RegularAnmMaxGet( const FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_reg_max_anm );
}

//--------------------------------------------------------------
/**
 * ゲストID 最大管理数設定　アニメ
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	max		最大数
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActCont_GuestAnmMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max )
{
	cont->resm_id_gst_max_anm = max;
}

//--------------------------------------------------------------
/**
 * ゲストID 最大管理数取得　アニメ
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	int		最大数
 */
//--------------------------------------------------------------
static int FldOBJ_BlActCont_GuestAnmMaxGet( const FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_gst_max_anm );
}

//--------------------------------------------------------------
/**
 * レギュラーID 最大管理数設定　テクスチャ
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	max		最大数
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActCont_RegularTexMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max )
{
	cont->resm_id_reg_max_tex = max;
}

//--------------------------------------------------------------
/**
 * レギュラーID 最大管理数取得　テクスチャ
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	max		最大数
 */
//--------------------------------------------------------------
static int FldOBJ_BlActCont_RegularTexMaxGet( const FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_reg_max_tex );
}

//--------------------------------------------------------------
/**
 * ゲストID 最大管理数設定　テクスチャ
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	max		最大数
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_BlActCont_GuestTexMaxSet( FIELD_OBJ_BLACT_CONT *cont, int max )
{
	cont->resm_id_gst_max_tex = max;
}

//--------------------------------------------------------------
/**
 * ゲストID 最大管理数取得　テクスチャ
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @retval	int		最大数
 */
//--------------------------------------------------------------
static int FldOBJ_BlActCont_GuestTexMaxGet( const FIELD_OBJ_BLACT_CONT *cont )
{
	return( cont->resm_id_gst_max_tex );
}

#if 0
//--------------------------------------------------------------
/**
 * ゲスト追加管理TCB_PTRセット
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
 * ゲスト追加管理TCB_PTR取得
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
 * Vブランク割り込みTCB_PTRセット
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
 * Vブランク割り込みTCB_PTR取得
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
 * FIELD_OBJ_BLACT_CONTからアーカイブデータ取得
 * @param	cont	FIELD_OBJ_BLACT_CONT *
 * @param	dataID	アーカイブデータインデックスID
 * @param	fb		TRUE=sys_AllocMemory() FALSE=sys_AllocMemoryLo()
 * @retval	void*	dataIDのデータ
 */
//--------------------------------------------------------------
static void * FldOBJ_BlActContArcDataAlloc( FIELD_OBJ_BLACT_CONT *cont, u32 datID, int fb )
{	
	return( FieldOBJ_DrawArcDataAlloc(cont->fos,datID,fb) );
}

//==============================================================================
//	DATA_FieldOBJ_BlActHeaderPathIDTbl参照
//==============================================================================
//--------------------------------------------------------------
/**
 * DATA_FieldOBJ_BlActHeaderPathIDTbl取得
 * @param	code	OBJコード。HERO等
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
 * OBJコードからモデルIDを取得
 * @param	code	HERO等
 * @retval	int		BLACT_MDLID_32x32等
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
 * OBJコードからモデルIDを取得　グローバル
 * @param	code	HERO等
 * @retval	int		BLACT_MDLID_32x32等
 */
//--------------------------------------------------------------
int FieldOBJ_BlActOBJCodeMdlIDGet( int code )
{
	return( FldOBJ_BlActH_OBJCode_MdlID(code) );
}

//--------------------------------------------------------------
/**
 * OBJコードからアニメIDを取得
 * @param	code	HERO等
 * @retval	int		BLACT_ANMID_32x32等
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
 * OBJコードからアニメIDを取得　グローバル
 * @param	code	HERO等
 * @retval	int		BLACT_ANMID_32x32等
 */
//--------------------------------------------------------------
int FieldOBJ_BlActOBJCodeAnmIDGet( int code )
{
	return( FldOBJ_BlActH_OBJCode_AnmID(code) );
}

//--------------------------------------------------------------
/**
 * OBJコードからアニメテーブルを取得
 * @param	code	HERO等
 * @retval	char*	ヘッダーファイルパス
 */
//--------------------------------------------------------------
static const BLACT_ANIME_TBL * FldOBJ_BlActH_OBJCode_AnmTbl( int code )
{
	const FIELD_OBJ_BLACT_HEADER_ID *tbl;
	
	tbl = FldOBJ_BlActHeaderPathIDTblGet( code );
	return( tbl->anm_tbl );
};

//==============================================================================
//	ビルボードアクターパーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * ビルボードアクター追加中フラグをセット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	flag	TRUE=追加中 FALSE=追加完了
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
 * ビルボードアクター追加中フラグのチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=追加中 FALSE=追加済み
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
 * ビルボードアクター初期化
 * @param	cont			FIELD_OBJ_BLACT_CONT *
 * @param	max				アクター最大数
 * @retval	BLACT_SET_PTR	アクターセットポインタ
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
 * ビルボードアクター　インデックス削除
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
 * ビルボードアクターの追加
 * @param	set			BLACT_SET_PTR
 * @param	head		BLACT_HEADER *
 * @param	vec			座標
 * @retval	BLACT_WORK	BLACT_WORK_PTR , NULL=追加失敗
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
		BLACT_ObjDrawFlagSet( act, FALSE );					//完全に初期化完了するまで非表示
		BLACT_AnmOffsChg( act, 0 );
		BLACT_AnmFrameSetOffs( act, 0 );
		NNS_G3dMdlSetMdlFogEnableFlagAll( BLACT_MdlResGet(act), TRUE );
		SetGlbLightMdl( BLACT_MdlResGet(act) );
	}
	
	return( act );
}

//--------------------------------------------------------------
/**
 * ヘッダーテーブルからヘッダー読み込み
 * @param	cont		FIELD_OBJ_BLACT_CONT *
 * @param	code		HERO等
 * @param	head		読み込み先BLACT_HEADER *
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
			OS_Printf( "FldOBJ_BlActHeaderLoad() 登録されていないテクスチャ" );
			OS_Printf( "OBJコード = 0x%x\n", code );
			GF_ASSERT( 0 );
		}
#endif
		
		head->ItxRes = TEXRESM_GetResPTR( reso );
		
		{	//現在常駐のみ	転送型の場合はNULL初期化
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
 * FIELD_OBJからFIELD_OBJ_BLACT_CONT取得
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
 * FIELD_OBJからFIELD_OBJ_BLACT_CONT取得　ローカル操作版
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
//	アクター　パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJに格納されている3D座標をアクターに反映。
 * @param	dir		DIR_UP等
 * @retval	BOOL	FALSE=高さ取得失敗
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
 * フィールドOBJステータスを見て表示、非表示セット
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
//	アニメーションナンバー　パーツ
//==============================================================================
//--------------------------------------------------------------
//	歩き　上下左右テーブル	方向別
//--------------------------------------------------------------
static const int DATA_BlActAnmOffsNo_WalkTbl[] =
{ 0, 1, 2, 3 };

//--------------------------------------------------------------
/**
 * 方向から歩きアニメオフセット番号取得
 * @param	dir		DIR_UP等
 * @retval	int		アニメオフセット番号
 */
//--------------------------------------------------------------
int FieldOBJ_BlActAnmOffsNo_DirWalkGet( int dir )
{
	return( DATA_BlActAnmOffsNo_WalkTbl[dir] );
}

//--------------------------------------------------------------
//	ダッシュ　上下左右テーブル	方向別
//--------------------------------------------------------------
static const int DATA_BlActAnmOffsNo_DashTbl[] =
{ 4, 5, 6, 7 };

//--------------------------------------------------------------
/**
 * 方向からダッシュアニメオフセット番号取得
 * @param	dir		DIR_UP等
 * @retval	int		アニメオフセット番号
 */
//--------------------------------------------------------------
int FieldOBJ_BlActAnmOffsNo_DirDashGet( int dir )
{
	return( DATA_BlActAnmOffsNo_DashTbl[dir] );
}

//--------------------------------------------------------------
//	ジャンプ台　上下左右テーブル	方向別
//--------------------------------------------------------------
static const int DATA_BlActAnmOffsNo_TakeOFFTbl[] =
{ 4, 5, 4, 5 };

//--------------------------------------------------------------
/**
 * 方向からジャンプ台アニメオフセット番号取得
 * @param	dir		DIR_UP等
 * @retval	int		アニメオフセット番号
 */
//--------------------------------------------------------------
int FieldOBJ_BlActAnmOffsNo_DirTakeOFFGet( int dir )
{
	return( DATA_BlActAnmOffsNo_TakeOFFTbl[dir] );
}

//==============================================================================
//	新仕様　ビルボード　テクスチャ
//==============================================================================
#if 0
//--------------------------------------------------------------
/**
 * テクスチャロード
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	tex_id	マネージャ登録ID
 * @param	arc_id	アーカイブID
 * @param	reg_type	登録タイプ REGULAR? GUEST?
 * @retval	int		TRUE=その場でロード。FALSE=ロード最大、予約へ回す
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
 * テクスチャロード
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	tex_id	マネージャ登録ID
 * @param	arc_id	アーカイブID
 * @param	reg_type	登録タイプ REGULAR? GUEST?
 * @retval	int		TRUE=その場でロード。FALSE=ロード最大、予約へ回す
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
 * テクスチャロードキャンセル
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	tex_id	キャンセルするマネージャ登録ID
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
 * テクスチャロード予約チェック
 * @param	cont			FIELD_OBJ_BLACT_CONT
 * @param	tex_id			チェックするマネージャ登録ID
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
 * TCB テクスチャロード予約消化
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	tex_id	マネージャ登録ID
 * @param	arc_id	アーカイブID
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
	
	{															//予約溢れを昇順
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
 * テクスチャロード　ロードしたテクスチャIDはレギュラーゲスト管理へ登録
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	tex_id	マネージャ登録ID
 * @param	buf		転送するテクスチャバッファ
 * @param	reg_type	登録タイプ REGULAR? GUEST?
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
 * VTRANS テクスチャ登録
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	id		登録ID
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
 * VTRANS テクスチャ登録キャンセル
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	id		キャンセルする登録ID
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
 * VIntr TCB テクスチャVRAM転送
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
 * VWait TCB テクスチャリソース破棄
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
 * ビルボードアクター追加予約。
 * 呼んだ際、actはNULLで初期化。
 * 管理側でビルボードアクターが追加されるとそのアドレスが格納される。
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	code	表示コード
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
 * ビルボードアクター追加予約キャンセル
 * @param	cont	FIELD_OBJ_BLACT_CONT
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	code	表示コード
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
 * ビルボードアクター追加予約消化
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
 * TCB ビルボードアクター追加予約消化
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
 * ビルボードアクター追加予約消化　追加処理
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
 * BLACT_VTRANS_WORK初期化
 * @param	cont		FIELD_OBJ_BLACT_CONT
 * @param	max			各要素最大数
 * @param	load_max	1フレームテクスチャロード回数最大
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
 * BLACT_VTRANS_WORK削除
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
///	ダミーアクター追加後、正規アクター追加
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
 * ダミーアクターを表示させながら正規アクターへ変更
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	code	変更するコード HERO等
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
 * ダミーアクターを表示させながら正規アクターへ変更　セット部分
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	code	変更するコード HERO等
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
	
	{	//映り込みアリ
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
		BlActDummyActDeleteTCB( tcb, work );	//念の為呼んでみる
	}
}

//--------------------------------------------------------------
/**
 * TCB ダミーアクター消去
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

