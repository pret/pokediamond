//============================================================================================
/**
 * @file	field_clact.c
 * @brief	�t�B�[���h�p�Z���A�N�^�[�ݒ菈��
 * @author	Hiroyuki Nakamura
 * @date	2005.01.13
 */
//============================================================================================
#include "common.h"
#include "system/clact_tool.h"

#define	FIELD_CLACT_H_GLOBAL
#include "field_clact.h"


static BOOL CATS_LoadResourceTable_Private( CLACT_U_RES_OBJ_TBL * tbl, CLACT_U_RES_OBJ_PTR obj );
static void CATS_LoadResourceCellArc_Private(
				FIELD_CLACT * fcat, int arc_id, int data_id, int comp, int type, int id );


//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�ݒ�
 *
 * @param	fcat	�ݒ�f�[�^�ۑ��ꏊ
 * @param	list	�ǂݍ��݃t�@�C�����X�g
 * @param	max		�Z���A�N�^�[�ő吔
 * @param	heap	�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldCellActSet(
		FIELD_CLACT * fcat, const TCATS_RESOURCE_FILE_LIST * list, u32 max, u32 heap )
{
	CLACT_U_RES_HEADER_PTR rhb;
	CLACT_U_RES_HEADER_PTR rht;
	void * buf;
	u32	siz;
	u32 i;

	fcat->cas  = CLACT_U_SetEasyInit( max, &fcat->renddata, heap );
	fcat->heap = heap;

	// �}���`�Z���������ꍇ
	if( list->resource.mcell_path == NULL ){
		fcat->res_max = CLACT_U_RES_MAX - 2;
	}else{
		fcat->res_max = CLACT_U_RES_MAX;
	}
	
	// ���\�[�X�}�l�[�W���[�p�w�b�_�[�̈�̍쐬
	rht = sys_AllocMemory( heap, CLACT_U_ResManagerGetHeaderSize() * fcat->res_max );

	// ���\�[�X�}�l�[�W���[�p�w�b�_�[�ǂݍ���
	for( i=0; i<fcat->res_max; i++ ){
		rhb = CLACT_U_ResManagerGetHeaderNoData( rht, i );
		buf = sys_LoadFile( heap, list->res_file[i] );
		CLACT_U_ResManagerHeaderLoadBinary( buf, rhb, heap );
		sys_FreeMemoryEz( buf );
	}

	// ���\�[�X�}�l�[�W���[�쐬
	for( i=0; i<fcat->res_max; i++ ){
		rhb = CLACT_U_ResManagerGetHeaderNoData( rht, i );
		siz = CLACT_U_ResManagerHeaderSetDataNum( rhb );
		fcat->resMan[i] = CLACT_U_ResManagerInit( siz, i, heap );
	}

	// ���\�[�X�}�l�[�W���[�ɓo�^����f�[�^�ǂݍ���
	for( i=0; i<fcat->res_max; i++ ){
		rhb = CLACT_U_ResManagerGetHeaderNoData( rht, i );
		siz = CLACT_U_ResManagerHeaderSetDataNum( rhb );
		fcat->resObjTbl[i] = CLACT_U_ResManagerResObjTblMake( siz, heap );
		CLACT_U_ResManagerResAddsHd( fcat->resMan[i], rhb, fcat->resObjTbl[i], heap );
	}

	for( i=0; i<fcat->res_max; i++ ){
		rhb = CLACT_U_ResManagerGetHeaderNoData( rht, i );
		CLACT_U_ResManagerHeaderFree( rhb );
	}
	sys_FreeMemoryEz( rht );

	// �}�l�[�W���ɓo�^
	CLACT_U_CharManagerSetsAreaCont( fcat->resObjTbl[0] );
	CLACT_U_PlttManagerSetsCleanArea( fcat->resObjTbl[1] );
	
	// �Z���A�N�^�[�w�b�_�[�ǂݍ���
	buf = sys_LoadFile( heap, list->resource.clact_header_path );
	fcat->clh = CLACT_U_MakeHeaderBinary(
					buf, heap,
					fcat->resMan[0], fcat->resMan[1],
					fcat->resMan[2], fcat->resMan[3],
					fcat->resMan[4], fcat->resMan[5] );
	sys_FreeMemoryEz( buf );
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�ݒ�j��
 *
 * @param	fcat	�ݒ�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldCellActDelete( FIELD_CLACT * fcat )
{
	u32	i;

	CLACT_DestSet( fcat->cas );							// �Z�b�g�̔j��
	CLACT_U_CLACT_HeaderTblDelete( fcat->clh );			// �Z���A�N�^�[�w�b�_�[�j��
	CLACT_U_CharManagerDeletes( fcat->resObjTbl[0] );	// �L�����N�^�f�[�^�j��
	CLACT_U_PlttManagerDeletes( fcat->resObjTbl[1] );	// �p���b�g�f�[�^�j��

	for( i=0; i<fcat->res_max; i++ ){
		// ���\�[�X�I�u�W�F�e�[�u����j��
		CLACT_U_ResManagerResObjTblDelete( fcat->resObjTbl[i] );
		// ���\�[�X�}�l�[�W���j��
		CLACT_U_ResManagerDelete( fcat->resMan[i] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�o�^
 *
 * @param	fcat	�ݒ�f�[�^
 * @param	prm		�ǉ��f�[�^
 *
 * @return	�o�^�����Z���A�N�^�[�̃|�C���^
 */
//--------------------------------------------------------------------------------------------
CLACT_WORK_PTR FieldCellActAdd( FIELD_CLACT * fcat, const TCATS_OBJECT_ADD_PARAM * prm )
{
	CLACT_ADD ca;
	CLACT_WORK_PTR cwp;
	VecFx32 sca = { FX32_ONE, FX32_ONE, FX32_ONE };
	VecFx32 pos;

	pos.x = prm->x * FX32_ONE;
	pos.y = prm->y * FX32_ONE;
	pos.z = prm->z * FX32_ONE;

	ca.ClActSet		= fcat->cas;
	ca.ClActHeader	= &fcat->clh->tbl[prm->no];
	ca.mat			= pos;
	ca.sca			= sca;
	ca.rot			= 0;
	ca.pri			= prm->pri;
	ca.DrawArea		= prm->d_area;
	ca.heap			= fcat->heap;

	cwp = CLACT_Add( &ca );
	GF_ASSERT( cwp && ("�Z���A�N�^�[�o�^���s\n") );

	CLACT_AnmChg( cwp, prm->anm );
	CLACT_PaletteNoChgAddTransPlttNo( cwp, prm->pal );

	return cwp;
}


//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�ݒ�i�P���p�j
 *
 * @param	fcat	�ݒ�f�[�^�ۑ��ꏊ
 * @param	crnl	
 * @param	max		�Z���A�N�^�[�ő吔
 * @param	heap	�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldCellActSet_S(
		FIELD_CLACT * fcat, TCATS_RESOURCE_NUM_LIST * crnl, u32 max, u32 heap )
{
	CLACT_U_RES_HEADER_PTR rhb;
	CLACT_U_RES_HEADER_PTR rht;
	void * buf;
	u32	siz;
	u32 i, j;

	fcat->cas  = CLACT_U_SetEasyInit( max, &fcat->renddata, heap );
	fcat->heap = heap;

	// �}���`�Z���������ꍇ
	if( crnl->resource_num.mcell_num == 0 || crnl->resource_num.mcell_anm_num == 0 ){
		fcat->res_max = CLACT_U_RES_MAX - 2;
		fcat->resMan[4] = NULL;
		fcat->resMan[5] = NULL;
	}else{
		fcat->res_max = CLACT_U_RES_MAX;
	}

	///< ���\�[�X�}�l�[�W���[�쐬
	for( i=0; i<fcat->res_max; i++ ){
		fcat->resMan[i] = CLACT_U_ResManagerInit( crnl->res_num[i], i, heap );
	}

	///< ���\�[�X�}�l�[�W���[�ɓo�^����f�[�^�ǂݍ���
	for( i=0; i<fcat->res_max; i++ ){
		if( crnl->res_num[i] == 0 ){ continue; }
		fcat->resObjTbl[i] = CLACT_U_ResManagerResObjTblMake( crnl->res_num[i], heap );
//		crp->resObjNum[i] = 0;
		for( j=0; j<fcat->resObjTbl[i]->tbl_num; j++ ){
			fcat->resObjTbl[i]->tbl[j] = NULL;
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g���\�[�X�ݒ�
 *
 * @param	fcat		�ݒ�f�[�^
 * @param	arc_id		�A�[�J�C�uID
 * @param	data_id		�f�[�^ID
 * @param	comp		���k�t���O
 * @param	num			�]���T�C�Y
 * @param	trans_mode	�]�����[�h
 * @param	id			���\�[�XID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FldClact_LoadResPlttArc(
		FIELD_CLACT * fcat, int arc_id, int data_id, int comp, int num, int trans_mode, int id )
{
	CLACT_U_RES_OBJ_PTR obj;
	int ret;
	
	if( CLACT_U_ResManagerCheckID( fcat->resMan[1], id ) == FALSE){
		GF_ASSERT(0);
		return;
	}

	obj = CLACT_U_ResManagerResAddArcPltt(
				fcat->resMan[1], arc_id, data_id, comp, id, trans_mode, num, fcat->heap );

	if( obj != NULL ){
		ret = CLACT_U_PlttManagerSetCleanArea( obj );
		GF_ASSERT(ret == TRUE && "�p���b�g�o�^���s");
	
		CATS_LoadResourceTable_Private( fcat->resObjTbl[1], obj );	
		CLACT_U_PlttManagerGetPlttNo( obj, trans_mode );
		return;
	}
	GF_ASSERT(0);
}

//--------------------------------------------------------------------------------------------
/**
 * �Z�����\�[�X�ݒ�
 *
 * @param	fcat		�ݒ�f�[�^
 * @param	arc_id		�A�[�J�C�uID
 * @param	data_id		�f�[�^ID
 * @param	comp		���k�t���O
 * @param	id			���\�[�XID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FldClact_LoadResCellArc( FIELD_CLACT * fcat, int arc_id, int data_id, int comp, int id )
{
	CATS_LoadResourceCellArc_Private( fcat, arc_id, data_id, comp, 2, id );
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�j�����\�[�X�ݒ�
 *
 * @param	fcat		�ݒ�f�[�^
 * @param	arc_id		�A�[�J�C�uID
 * @param	data_id		�f�[�^ID
 * @param	comp		���k�t���O
 * @param	id			���\�[�XID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FldClact_LoadResCellAnmArc( FIELD_CLACT * fcat, int arc_id, int data_id, int comp, int id )
{
	CATS_LoadResourceCellArc_Private( fcat, arc_id, data_id, comp, 3, id );
}

//--------------------------------------------------------------------------------------------
/**
 * �L�������\�[�X�ݒ�
 *
 * @param	fcat		�ݒ�f�[�^
 * @param	arc_id		�A�[�J�C�uID
 * @param	data_id		�f�[�^ID
 * @param	comp		���k�t���O
 * @param	trans_mode	�]�����[�h
 * @param	id			���\�[�XID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FldClact_LoadResourceCharArc(
		FIELD_CLACT * fcat, int arc_id, int data_id, BOOL comp, int trans_mode, int id )
{
	CLACT_U_RES_OBJ_PTR obj;

	if( CLACT_U_ResManagerCheckID( fcat->resMan[0], id ) == FALSE ){
		GF_ASSERT(0);
		return;
	}
	
	obj = CLACT_U_ResManagerResAddArcChar(
			fcat->resMan[0], arc_id, data_id, comp, id, trans_mode, fcat->heap );

	if( obj != NULL ){
		CLACT_U_CharManagerSetAreaCont(obj);
		
		CATS_LoadResourceTable_Private( fcat->resObjTbl[0], obj );	
		
		return;
	}
	
	GF_ASSERT(0);
}

//--------------------------------------------------------------------------------------------
/**
 * �L�����̃��[�\�[�X��ύX����
 *
 * @param	fcat		�ݒ�f�[�^
 * @param	arc_id		�A�[�J�C�uID
 * @param	data_id		�f�[�^ID
 * @param	comp		���k�t���O
 * @param	id			���\�[�XID
 *
 * @retval	BOOL	
 */
//--------------------------------------------------------------------------------------------
void FldClact_ChangeResourceCharArc(
					FIELD_CLACT * fcat, int arc_id, int data_id, BOOL comp, int id )
{
	CLACT_U_RES_OBJ_PTR	obj = CLACT_U_ResManagerGetIDResObjPtr( fcat->resMan[0], id );
	CLACT_U_ResManagerResChgArcChar( fcat->resMan[0], obj, arc_id, data_id, comp, fcat->heap );
	CLACT_U_CharManagerReTrans( obj );
}

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g�̃��[�\�[�X��ύX����
 *
 * @param	fcat		�ݒ�f�[�^
 * @param	arc_id		�A�[�J�C�uID
 * @param	data_id		�f�[�^ID
 * @param	comp		���k�t���O
 * @param	id			���\�[�XID
 *
 * @retval	BOOL	
 */
//--------------------------------------------------------------------------------------------
void FldClact_ChangeResourcePlttArc(
					FIELD_CLACT * fcat, int arc_id, int data_id, BOOL comp, int id )
{
	CLACT_U_RES_OBJ_PTR	obj = CLACT_U_ResManagerGetIDResObjPtr( fcat->resMan[1], id );
	CLACT_U_ResManagerResChgArcPltt( fcat->resMan[1], obj, arc_id, data_id, comp, fcat->heap );
	CLACT_U_PlttManagerReTrans( obj );
}

static BOOL CATS_LoadResourceTable_Private( CLACT_U_RES_OBJ_TBL * tbl, CLACT_U_RES_OBJ_PTR obj )
{
	int i;
	
	for( i=0; i<tbl->tbl_num; i++ ){
		if( tbl->tbl[i] != NULL ){ continue; }
		tbl->tbl[i] = obj;
		tbl->tbl_now++;
		return TRUE;
	}
	return FALSE;
}

static void CATS_LoadResourceCellArc_Private(
				FIELD_CLACT * fcat, int arc_id, int data_id, int comp, int type, int id )
{
	CLACT_U_RES_OBJ_PTR obj;
	int ret;

	if( CLACT_U_ResManagerCheckID( fcat->resMan[type], id ) == FALSE ){
		GF_ASSERT(0);
		return;
	}
	
	obj = CLACT_U_ResManagerResAddArcKindCell(
				fcat->resMan[type], arc_id, data_id, comp, id, type, fcat->heap );

	if (obj != NULL){
		ret = CATS_LoadResourceTable_Private( fcat->resObjTbl[type], obj );
		
		GF_ASSERT(ret == TRUE && "�Z���o�^���s");
		
		return;
	}
	
	GF_ASSERT(0);
}



//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�ǉ��i�P���p�j
 *
 * @param	fcat		�ݒ�f�[�^
 * @param	coap_s		�\���f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
CATS_ACT_PTR FieldCellActAdd_S(
				FIELD_CLACT * fcat, const TCATS_OBJECT_ADD_PARAM_S * coap_s )
{
	int i;
	int def_palno;
	CATS_ACT_PTR cap = NULL;
	CLACT_ADD	 add;
	int id_list[CLACT_U_RES_MAX];

	cap = sys_AllocMemory( fcat->heap, sizeof(TCATS_ACT) );

	///< �w�b�_�[�̃������m��
	cap->act_htp = sys_AllocMemory( fcat->heap, sizeof(CLACT_HEADER_TBL) );

	cap->act_htp->tbl = sys_AllocMemory( fcat->heap, sizeof(CLACT_HEADER) );
	cap->act_hd = cap->act_htp->tbl;

	///< ���\�[�XID������������
	for( i=0; i<CLACT_U_RES_MAX; i++ ){
		id_list[i] = coap_s->id[i];
	}
	
	if( fcat->resMan[4] == NULL || fcat->resMan[5] == NULL ){
		///< �}�l�[�W���[�������ꍇ�́A�f�[�^�w�薳��
		id_list[4] = CLACT_U_HEADER_DATA_NONE;
		id_list[5] = CLACT_U_HEADER_DATA_NONE;
	}else{	
		///< �f�[�^�w�肳��Ă��Ă��A�w��ID�̃��\�[�X�������ꍇ���f�[�^����
		if( id_list[4] != CLACT_U_HEADER_DATA_NONE &&
			CLACT_U_ResManagerCheckID( fcat->resMan[4], id_list[4] ) == FALSE ){
			id_list[4] = CLACT_U_HEADER_DATA_NONE;
		}

		if( id_list[5] != CLACT_U_HEADER_DATA_NONE &&
			CLACT_U_ResManagerCheckID( fcat->resMan[5], id_list[5] ) == FALSE ){
			id_list[5] = CLACT_U_HEADER_DATA_NONE;
		}	
	}
	
	///< ���ۂɃw�b�_�[���쐬
	CLACT_U_MakeHeader(
		cap->act_hd,
		id_list[0], id_list[1], id_list[2],
		id_list[3], id_list[4], id_list[5],
		coap_s->vram_trans, coap_s->bg_pri,
		fcat->resMan[0], fcat->resMan[1], fcat->resMan[2],
		fcat->resMan[3], fcat->resMan[4], fcat->resMan[5] );
	
	///< OBJ �̓o�^
	add.ClActSet	= fcat->cas;
	add.ClActHeader = cap->act_hd;

	add.mat.x		= FX32_CONST(coap_s->x);		///< ���W
	add.mat.y		= FX32_CONST(coap_s->y);
	add.mat.z		= FX32_CONST(coap_s->z);
	if(coap_s->d_area == NNS_G2D_VRAM_TYPE_2DSUB){
		add.mat.y += SUB_SURFACE_Y;
	}
	
	add.sca.x		= FX32_ONE;						///< �g�k��
	add.sca.y		= FX32_ONE;
	add.sca.z		= FX32_ONE;
	
	add.rot			= 0;							///< ��]�p
	add.pri			= coap_s->pri;					///< �D��x
	add.DrawArea	= coap_s->d_area;				///< �`���
	add.heap		= fcat->heap;				///< �q�[�v�̈�
	
	cap->act = CLACT_Add(&add);						///< �o�^
	
	if (cap->act != NULL){
		def_palno = CLACT_PaletteNoGet(cap->act);				///< ��{�p���b�g�ԍ��擾
		CLACT_AnmChg(cap->act, coap_s->anm);					///< �A�j���[�V�����w��
		CLACT_PaletteNoChg(cap->act, def_palno + coap_s->pal);	///< �p���b�g�w��
	}
	else{
		GF_ASSERT(0 && "�A�N�^�[�o�^���s");
	}
	return cap;		
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�폜�i�P���p�j
 *
 * @param	fcat		�ݒ�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldCellActDelete_S( FIELD_CLACT * fcat )
{
	u32	i;

	CLACT_DestSet( fcat->cas );							// �Z�b�g�̔j��
	CLACT_U_CharManagerDeletes( fcat->resObjTbl[0] );	// �L�����N�^�f�[�^�j��
	CLACT_U_PlttManagerDeletes( fcat->resObjTbl[1] );	// �p���b�g�f�[�^�j��

	for( i=0; i<fcat->res_max; i++ ){
		// ���\�[�X�I�u�W�F�e�[�u����j��
		CLACT_U_ResManagerResObjTblDelete( fcat->resObjTbl[i] );
		// ���\�[�X�}�l�[�W���j��
		CLACT_U_ResManagerDelete( fcat->resMan[i] );
	}
}
