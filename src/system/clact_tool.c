//==============================================================================
/**
 * @file	clact_tool.c
 * @brief	clact��ʊ֐��Q
 * @author	goto
 * @date	2005.09.12(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

#include "common.h"
#include "system/lib_pack.h"
#include "system/bmp_list.h"

#include "clact_tool.h"
#include "system/palanm.h"


//
//
//	�����p���[�h
//
//	[ CATS_SINGLE ]		�P�̓o�^�֐��S
//
//	[ ACTOR_TOOL ]		�A�N�^�[����n�c�[��
//
//
//
//


//	���V����

// -----------------------------------------
//
//	��CLACT�̃V�X�e���{��(�A�v���ɂP�p�ӂ�������)
//
// -----------------------------------------
typedef struct _TCATS_SYSTEM {
	
	int							heap_area;			///< �q�[�v�̈�
	
	int							resource_num;		///< �V�X�e�����Ǘ����Ă��郊�\�[�X�̐�
	
	int							render_use;			///< �����_�[���g����
	
	NNSG2dCellTransferState*	cellTransArray;		///< �Z��Vram�]���}�l�[�W���[�̈�
	
	CLACT_U_EASYRENDER_DATA		renddata;			///< �����_���[�f�[�^
	
} TCATS_SYSTEM;



// -----------------------------------------
//
//	���P�ʓo�^�p�\����(�G�t�F�N�g�P�ɂP�p�ӂ�������)
//
// -----------------------------------------
typedef struct _TCATS_RESOURCE {

	CLACT_SET_PTR				ca_sp;						///< �Z���A�N�^�[�Z�b�g
	CLACT_HEADER_TBL_PTR		ca_htp;						///< �Z���A�N�^�[�w�b�_�[
	CLACT_U_RES_HEADER_PTR		resHeader;					///< ���\�[�X�w�b�_�[

	CLACT_U_RES_MANAGER_PTR		resManager[CLACT_U_RES_MAX];///< ���\�[�X�}�l�[�W���[
	CLACT_U_RES_OBJ_TBL*		resObjTbl[CLACT_U_RES_MAX];	///< ���\�[�X�e�[�u��(��ޕ�)

	int							resObjNum[CLACT_U_RES_MAX];	///< ���\�[�X�Ǘ���
	int							resTypeNum;					///< ���\�[�X��(4or6)
	
} TCATS_RESOURCE;


// =============================================================================
//
//
//	���v���g�^�C�v
//
//
// =============================================================================




// =============================================================================
//
//
//	���O���Q��
//
//
// =============================================================================
// =============================================================================
//
//
//	�����ʊ֐� �P�̓o�^ �w�b�_�[�o�^���p
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	�V�X�e���̃������m��
 *
 * @param	heap_area			�q�[�v�̈�w��
 *
 * @retval	CATS_SYS_PTR		�m�ۂ����������̃|�C���^
 *
 */
//--------------------------------------------------------------
CATS_SYS_PTR CATS_AllocMemory(int heap_area)
{
	CATS_SYS_PTR csp = NULL;
	
	csp = sys_AllocMemory(heap_area, sizeof(TCATS_SYSTEM));
	
	if (csp == NULL){
		return NULL;
	}
	
	csp->heap_area		= heap_area;
	
	csp->resource_num	= 0;
	
	csp->render_use		= CATS_RENDER_USE_ON;
	
	return csp;
}


//--------------------------------------------------------------
/**
 * @brief	���\�[�X�p�̃������m��
 *
 * @param	csp					�V�X�e���|�C���^
 *
 * @retval	CATS_RES_PTR		�m�ۂ����������̃|�C���^
 *
 */
//--------------------------------------------------------------
CATS_RES_PTR CATS_ResourceCreate(CATS_SYS_PTR csp)
{
	int i;

	CATS_RES_PTR crp = NULL;

	GF_ASSERT(csp != NULL);

	crp = sys_AllocMemory(csp->heap_area, sizeof(TCATS_RESOURCE));
	
	if (crp == NULL){
		return NULL;
	}
	
	csp->resource_num++;
	
	for (i = 0; i < CLACT_U_RES_MAX; i++){
		crp->resManager[i] = NULL;
	}
	
	return crp;
}


//--------------------------------------------------------------
/**
 * @brief	���\�[�X�̐����擾
 *
 * @param	csp					�V�X�e��
 *
 * @retval	int					��
 *
 */
//--------------------------------------------------------------
int CATS_ResourceNumGet(CATS_SYS_PTR csp)
{
	return csp->resource_num;
}


//--------------------------------------------------------------
/**
 * @brief	�����_���[�f�[�^���擾
 *
 * @param	csp					�V�X�e��
 *
 * @retval	int					�����_���[
 *
 */
//--------------------------------------------------------------
CLACT_U_EASYRENDER_DATA * CATS_EasyRenderGet(CATS_SYS_PTR csp)
{
	return &csp->renddata;
}


//--------------------------------------------------------------
/**
 * @brief	�V�X�e���̏�����
 *
 * @param	csp					�V�X�e���|�C���^
 * @param	coi					OAM�������\���̂̃|�C���^
 * @param	ccmm				�L�����}�l�[�W�����C�N�\���̂̃|�C���^
 * @param	pal_num				�p���b�g�̐�
 *
 * @retval	BOOL				TRUE = ����
 *
 */
//--------------------------------------------------------------
BOOL CATS_SystemInit(CATS_SYS_PTR csp, const TCATS_OAM_INIT* coi, const TCATS_CHAR_MANAGER_MAKE* ccmm, int pal_num)
{
	///< �V�X�e���̃��������m�ۂ���Ă��Ȃ��ꍇ
	GF_ASSERT(csp != NULL);
	if (csp == NULL){
		return FALSE;
	}

	///< �L�����N�^�}�l�[�W���[������
	{
		CHAR_MANAGER_MAKE cmm;
		cmm.CharDataNum			= ccmm->num;
		cmm.VramTransAreaMain	= ccmm->m_size;
		cmm.VramTransAreaSub	= ccmm->s_size;
		cmm.heap				= csp->heap_area;

		InitCharManagerReg(&cmm, ccmm->main_mode, ccmm->sub_mode);

//		InitCharManager(&cmm);
	}
	
	///< �p���b�g�}�l�[�W���[������
	InitPlttManager(pal_num, csp->heap_area);
	
	///< OAM �}�l�[�W���[�̏�����
	NNS_G2dInitOamManagerModule();

	///< �����_���̏�����
#ifdef CATS_RENDER_USE

	if (csp->render_use == CATS_RENDER_USE_ON){

		REND_OAMInit(coi->mos, coi->moe,
					 coi->mas, coi->mae,
					 coi->sos, coi->soe,
					 coi->sas, coi->sae,
					 csp->heap_area);

	}
#endif

	///< �Z��Vram�]���}�l�[�W���쐬
	csp->cellTransArray = InitCellTransfer(32, csp->heap_area);
	
	///< �ǂݍ��݊J�n�I�t�Z�b�g������
	CharLoadStartAll();
	PlttLoadStartAll();
	
	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	�����_�[���g�����ǂ���
 *
 * @param	csp	
 * @param	flag	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_RenderUseSet(CATS_SYS_PTR csp, int flag)
{
	GF_ASSERT(csp != NULL);
	
	csp->render_use = flag;
}


//--------------------------------------------------------------
/**
 * @brief	�Z���A�N�^�[�Z�b�g�̍쐬
 *
 * @param	csp					�V�X�e���|�C���^
 * @param	crp					���\�[�X�|�C���^
 * @param	num					�o�^OBJ�̐�
 *
 * @retval	BOOL				TRUE = ����
 *
 */
//--------------------------------------------------------------
BOOL CATS_ClactSetInit(CATS_SYS_PTR csp, CATS_RES_PTR crp, int num)
{
	///< �V�X�e���E���\�[�X�ǂ��炩���������m�ۂ���Ă��Ȃ�
	if (csp == NULL || crp == NULL){
		return FALSE;
	}
	
	///< �Z���A�N�^�[�Z�b�g�̍쐬
	crp->ca_sp = CLACT_U_SetEasyInit(num,
									 &csp->renddata,
									 csp->heap_area);
	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	OBJ�̍폜
 *
 * @param	act					OBJ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectDel(CLACT_WORK_PTR act)
{
	CLACT_Delete(act);
}


//--------------------------------------------------------------
/**
 * @brief	�`��
 *
 * @param	crp					���\�[�X�|�C���^
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_Draw(CATS_RES_PTR crp)
{
	GF_ASSERT(crp != NULL);
	
	CLACT_Draw(crp->ca_sp);
}


//--------------------------------------------------------------
/**
 * @brief	OAM�̓]��		��VBlank���ԂɌĂ�
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_RenderOamTrans(void)
{
#ifdef CATS_RENDER_USE

	REND_OAMTrans();

#endif
}


//--------------------------------------------------------------
/**
 * @brief	OAM�̓]��		��VBlank���ԂɌĂ�
 *
 * @param	csp	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_RenderOamTransEx(CATS_SYS_PTR csp)
{
	if (csp->render_use == CATS_RENDER_USE_ON){
		REND_OAMTrans();
	}
}


//--------------------------------------------------------------
/**
 * @brief	Vram�]���o�^
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_UpdateTransfer(void)
{
	UpdateCellTransfer();
}


//--------------------------------------------------------------
/**
 * @brief	�Z���A�N�^�[�Z�b�g�j��
 *
 * @param	crp					���\�[�X�|�C���^
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ClactSetDelete(CATS_RES_PTR crp)
{
	CLACT_DestSet(crp->ca_sp);
}


//--------------------------------------------------------------
/**
 * @brief	�w�b�_�[�e�[�u���j��
 *
 * @param	crp					���\�[�X�|�C���^
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_HeaderTblDelete(CATS_RES_PTR crp)
{
	if (crp->ca_htp == NULL){ return; }
	
	CLACT_U_CLACT_HeaderTblDelete(crp->ca_htp);
}


//--------------------------------------------------------------
/**
 * @brief	���\�[�X�̔j��
 *
 * @param	crp					���\�[�X�|�C���^
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ResourceDelete(CATS_RES_PTR crp)
{
	int i;
	CLACT_U_RES_HEADER_PTR res_head;
	
	for (i = 0; i < crp->resTypeNum; i++){
		
		///< ���\�[�X�w�b�_�[�j��
		res_head = CLACT_U_ResManagerGetHeaderNoData(crp->resHeader, i);
		CLACT_U_ResManagerHeaderFree(res_head);

	}
	sys_FreeMemoryEz(crp->resHeader);
	
	///< �f�[�^�j��
	CLACT_U_CharManagerDeletes(crp->resObjTbl[0]);
	CLACT_U_PlttManagerDeletes(crp->resObjTbl[1]);
	
	
	for (i = 0; i < crp->resTypeNum; i++){
		
		///< ���\�[�X�I�u�W�F�e�[�u���j��
		CLACT_U_ResManagerResObjTblDelete(crp->resObjTbl[i]);
		
		///< ���\�[�X�}�l�[�W���[�j��
		CLACT_U_ResManagerDelete(crp->resManager[i]);
	}	
}


//--------------------------------------------------------------
/**
 * @brief	�}�l�[�W���[�j��
 *
 * @param	csp					�V�X�e���|�C���^
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ManagerDelete(CATS_SYS_PTR csp)
{
	DeleteCellTransfer(csp->cellTransArray);
	
	DeleteCharManager();
	
	DeletePlttManager();

#ifdef CATS_RENDER_USE

	if (csp->render_use == CATS_RENDER_USE_ON){

		REND_OAM_Delete();
		
	}

#endif
}


//--------------------------------------------------------------
/**
 * @brief	���\�[�X�̃��������
 *
 * @param	crp					���\�[�X�|�C���^
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ResourceFree(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	csp->resource_num--;
	sys_FreeMemoryEz(crp);
}


//--------------------------------------------------------------
/**
 * @brief	�f�X�g���N�^�[ ������������ɍs�Ȃ��܂�
 *
 * @param	csp					�V�X�e���|�C���^
 * @param	crp					���\�[�X�|�C���^
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ResourceDestructor(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	CATS_ClactSetDelete(crp);		///< �Z���Z�b�g�j��
	CATS_HeaderTblDelete(crp);		///< �w�b�_�[�e�[�u���j��
	CATS_ResourceDelete(crp);		///< ���\�[�X�j��
//	CATS_ManagerDelete(csp);		///< �}�l�[�W���j��
	CATS_ResourceFree(csp, crp);	///< ���\�[�X�̃������j��
//	CATS_FreeMemory(csp);			///< �V�X�e���{�̂̃������j��
}


//--------------------------------------------------------------
/**
 * @brief	�V�X�e���̃������j��
 *
 * @param	csp					�V�X�e���̃������j��
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_FreeMemory(CATS_SYS_PTR csp)
{
	GF_ASSERT(csp->resource_num == 0);
	
	CATS_ManagerDelete(csp);
	sys_FreeMemoryEz(csp);
}






// =============================================================================
//
//
//	���w�b�_�[�o�^�p
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	���\�[�X�̓ǂݍ���
 *
 * @param	csp					�V�X�e���|�C���^
 * @param	crp					���\�[�X�|�C���^
 * @param	res_list			���\�[�X���X�g�\���̃|�C���^
 *
 * @retval	BOOL				TRUE = ����
 *
 */
//--------------------------------------------------------------
BOOL CATS_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_RESOURCE_FILE_LIST* res_list)
{
	int i;
	int num = CLACT_U_RES_MAX;	
	int size;
	CLACT_U_RES_HEADER_PTR res_head;
	
	///< �V�X�e���E���\�[�X�ǂ��炩���������m�ۂ���Ă��Ȃ�
	if (csp == NULL || crp == NULL){
		return FALSE;
	}
	
	///< �}���`�Z���������ꍇ
	if (res_list->resource.mcell_path == NULL){
		num = CLACT_U_RES_MAX - 2;
	}
	crp->resTypeNum = num;
	
	///< ���\�[�X�}�l�[�W���[�p�w�b�_�[�̈�̍쐬
	size = CLACT_U_ResManagerGetHeaderSize();
	crp->resHeader = sys_AllocMemory(csp->heap_area, size * num);
	
	///< ���\�[�X�}�l�[�W���[�p�w�b�_�[�ǂݍ���
	for (i = 0; i < num; i++){
		res_head = CLACT_U_ResManagerGetHeaderNoData(crp->resHeader, i);
		CLACT_U_ResManagerHeaderLoad(res_list->res_file[i], res_head, csp->heap_area);
	}

	///< ���\�[�X�}�l�[�W���[�쐬
	for (i = 0; i < num; i++){
		res_head = CLACT_U_ResManagerGetHeaderNoData(crp->resHeader, i);
		size    		  = CLACT_U_ResManagerHeaderSetDataNum(res_head);
		crp->resManager[i] = CLACT_U_ResManagerInit(size, i, csp->heap_area);
	}

	///< ���\�[�X�}�l�[�W���[�ɓo�^����f�[�^�ǂݍ���
	for (i = 0; i < num; i++){
		res_head		  = CLACT_U_ResManagerGetHeaderNoData(crp->resHeader, i);
		size    		  = CLACT_U_ResManagerHeaderSetDataNum(res_head);
		crp->resObjTbl[i] = CLACT_U_ResManagerResObjTblMake(size, csp->heap_area);
		crp->resObjNum[i] = CLACT_U_ResManagerResAddsHd(crp->resManager[i],
														res_head,
														crp->resObjTbl[i],
														csp->heap_area);
	}
	
	///< �}�l�[�W���ɓo�^
	CLACT_U_CharManagerSets(crp->resObjTbl[0]);
	CLACT_U_PlttManagerSets(crp->resObjTbl[1]);
	
	///< �Z���A�N�^�[�w�b�_�[�ǂݍ���
	crp->ca_htp = CLACT_U_LoadHeaderTbl(res_list->resource.clact_header_path,
										csp->heap_area,
										crp->resManager[0], crp->resManager[1],
										crp->resManager[2],	crp->resManager[3],
										crp->resManager[4], crp->resManager[5]);
	return TRUE;
}

BOOL CATS_ResourceLoadBinary(
			CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_RESOURCE_FILE_LIST* res_list )
{
	int i;
	int num = CLACT_U_RES_MAX;	
	int size;
	CLACT_U_RES_HEADER_PTR res_head;
	void * buf;
	
	///< �V�X�e���E���\�[�X�ǂ��炩���������m�ۂ���Ă��Ȃ�
	if (csp == NULL || crp == NULL){
		return FALSE;
	}
	
	///< �}���`�Z���������ꍇ
	if (res_list->resource.mcell_path == NULL){
		num = CLACT_U_RES_MAX - 2;
	}
	crp->resTypeNum = num;
	
	///< ���\�[�X�}�l�[�W���[�p�w�b�_�[�̈�̍쐬
	size = CLACT_U_ResManagerGetHeaderSize();
	crp->resHeader = sys_AllocMemory(csp->heap_area, size * num);
	
	///< ���\�[�X�}�l�[�W���[�p�w�b�_�[�ǂݍ���
	for (i = 0; i < num; i++){
		res_head = CLACT_U_ResManagerGetHeaderNoData(crp->resHeader, i);
//		CLACT_U_ResManagerHeaderLoad(res_list->res_file[i], res_head, csp->heap_area);
		buf = sys_LoadFile( csp->heap_area, res_list->res_file[i] );
		CLACT_U_ResManagerHeaderLoadBinary( buf, res_head, csp->heap_area );
		sys_FreeMemoryEz( buf );
	}

	///< ���\�[�X�}�l�[�W���[�쐬
	for (i = 0; i < num; i++){
		res_head = CLACT_U_ResManagerGetHeaderNoData(crp->resHeader, i);
		size    		  = CLACT_U_ResManagerHeaderSetDataNum(res_head);
		crp->resManager[i] = CLACT_U_ResManagerInit(size, i, csp->heap_area);
	}

	///< ���\�[�X�}�l�[�W���[�ɓo�^����f�[�^�ǂݍ���
	for (i = 0; i < num; i++){
		res_head		  = CLACT_U_ResManagerGetHeaderNoData(crp->resHeader, i);
		size    		  = CLACT_U_ResManagerHeaderSetDataNum(res_head);
		crp->resObjTbl[i] = CLACT_U_ResManagerResObjTblMake(size, csp->heap_area);
		crp->resObjNum[i] = CLACT_U_ResManagerResAddsHd(crp->resManager[i],
														res_head,
														crp->resObjTbl[i],
														csp->heap_area);
	}
	
	///< �}�l�[�W���ɓo�^
	CLACT_U_CharManagerSets(crp->resObjTbl[0]);
	CLACT_U_PlttManagerSets(crp->resObjTbl[1]);
	
	///< �Z���A�N�^�[�w�b�_�[�ǂݍ���
/*
	crp->ca_htp = CLACT_U_LoadHeaderTbl(res_list->resource.clact_header_path,
										csp->heap_area,
										crp->resManager[0], crp->resManager[1],
										crp->resManager[2],	crp->resManager[3],
										crp->resManager[4], crp->resManager[5]);
*/
	buf = sys_LoadFile( csp->heap_area, res_list->resource.clact_header_path );
	crp->ca_htp = CLACT_U_MakeHeaderBinary(
						buf, csp->heap_area,
						crp->resManager[0], crp->resManager[1],
						crp->resManager[2],	crp->resManager[3],
						crp->resManager[4], crp->resManager[5] );
	sys_FreeMemoryEz( buf );

	return TRUE;
}

/*
GLOBAL CLACT_HEADER_TBL_PTR CLACT_U_MakeHeaderBinary(
		const CLACT_U_HEADER_MAKE_BINDATA* bindata,
		int heap,
		CLACT_U_RES_MANAGER_PTR charResMan,
		CLACT_U_RES_MANAGER_PTR plttResMan,
		CLACT_U_RES_MANAGER_PTR cellResMan,
		CLACT_U_RES_MANAGER_PTR cellAnmResMan,
		CLACT_U_RES_MANAGER_PTR multiCellResMan,
		CLACT_U_RES_MANAGER_PTR multiCellAnmResMan);
*/


//--------------------------------------------------------------
/**
 * @brief	�ψ����Ń��\�[�X��ǂݍ���
 *
 * @param	csp					�V�X�e���|�C���^
 * @param	crp					���\�[�X�|�C���^
 * @param	...					�t�@�C���p�X�ό� ��{5-7
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
#ifdef CATS_CBP_RES_LOAD		///< �ψ���

BOOL CATS_ResourceLoad_FileName(CATS_SYS_PTR csp, CATS_RES_PTR crp, ...)
{
	int i;
	int num;
	va_list ap;
	char* file;
	TCATS_RESOURCE_FILE_LIST list;
	
	va_start(ap, crp);
	
	num = 0;
	for (i = 0; i < CLACT_U_RES_MAX + 1; i++){
		file = va_arg(ap, char*);
		list.res_file[i] = file;
		
		if (file == NULL){
			break;
		}
		num++;
	}
	
	if (num != 5 && num != 7){
		return FALSE;
	}
	
	if (list.resource.clact_header_path == NULL
	||	list.resource.mcell_path != NULL){
		list.resource.clact_header_path = list.resource.mcell_path;
		list.resource.mcell_path		= NULL;
	}
	
	va_end(ap);
	
	return CATS_ResourceLoad(csp, crp, &list);;
}

#endif	///< �ψ���


//--------------------------------------------------------------
/**
 * @brief	OBJ�o�^
 *
 * @param	csp					�V�X�e���|�C���^
 * @param	crp					���\�[�X�|�C���^
 * @param	coap				OBJ�o�^�p�\���̃|�C���^
 *
 * @retval	CLACT_WORK_PTR	�o�^����OBJ�̃|�C���^
 *
 */
//--------------------------------------------------------------
CLACT_WORK_PTR CATS_ObjectAdd(CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_OBJECT_ADD_PARAM* coap)
{
	CLACT_WORK_PTR act = NULL;
	
	act = CATS_ObjectAdd_EX(csp, crp,
							coap->no,
							coap->x, coap->y, coap->x,
							coap->anm, coap->pri, coap->pal, coap->d_area,
							coap->param1, coap->param2, coap->param3, coap->param4);
	return act;
}


//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	csp					�V�X�e���|�C���^
 * @param	crp					���\�[�X�|�C���^
 * @param	no					�w�b�_�[���̓o�^�ԍ�
 * @param	x					���W x
 * @param	y					���W y
 * @param	z					���W z
 * @param	anm					�A�j��
 * @param	pri					�D��x
 * @param	pal					�p���b�g�ԍ�
 * @param	d_area				�`��G���A
 * @param	param1				�\��1
 * @param	param2				�\��2
 * @param	param3				�\��3
 * @param	param4				�\��4
 *
 * @retval	CLACT_WORK_PTR	�o�^����OBJ�̃|�C���^
 *
 */
//--------------------------------------------------------------
CLACT_WORK_PTR CATS_ObjectAdd_EX(CATS_SYS_PTR csp, CATS_RES_PTR crp, int no,
									 s16 x, s16 y, s16 z, u16 anm, int pri, int pal, int d_area,
									 int param1, int param2, int param3, int param4)
{
	CLACT_WORK_PTR act = NULL;
	CLACT_ADD add;
	
	add.ClActSet	= crp->ca_sp;				///< �Z���A�N�^�[�Z�b�g
	add.ClActHeader = &crp->ca_htp->tbl[no];	///< �w�b�_�[������o��
	
	add.mat.x		= FX32_CONST(x);			///< ���W
	add.mat.y		= FX32_CONST(y);
	add.mat.z		= FX32_CONST(z);
	if(d_area == NNS_G2D_VRAM_TYPE_2DSUB){
		add.mat.y += SUB_SURFACE_Y;
	}
	
	add.sca.x		= FX32_ONE;					///< �g�k��
	add.sca.y		= FX32_ONE;
	add.sca.z		= FX32_ONE;
	
	add.rot			= 0;						///< ��]�p
	add.pri			= pri;						///< �D��x
	add.DrawArea	= d_area;					///< �`���
	add.heap		= csp->heap_area;			///< �q�[�v�̈�
	
	act = CLACT_Add(&add);					///< �o�^
	
	if (act != NULL){
		CLACT_AnmChg(act, anm);				///< �A�j���[�V�����w��
		CLACT_PaletteNoChg(act, pal);		///< �p���b�g�w��
	}
	
	return act;	
}










// =============================================================================
//
//
//
//	���P�̂ŔC�ӂ̃��\�[�X��o�^���Ă����֐��S	[ CATS_SINGLE ]
//
//
//
// =============================================================================
// ----------------------------------------------------------------------------
//
//	�P�̂œǂݍ��ޏꍇ
//
static BOOL CATS_LoadResourceCell_Private(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int type, int id);
static BOOL CATS_LoadResourceCellArc_Private(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int type, int id);
static BOOL	CATS_LoadResourceTable_Private(CLACT_U_RES_OBJ_TBL* tbl, CLACT_U_RES_OBJ_PTR obj);
static BOOL CATS_DeleteResourceCharData_Private(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_TBL* tbl, int id);
static BOOL CATS_DeleteResourcePlttData_Private(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_TBL* tbl, int id);
static BOOL CATS_DeleteResourceData_Private(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_TBL* tbl, int id);

//--------------------------------------------------------------
/**
 * @brief	���\�[�X�}�l�[�W���̏�����
 *
 * @param	csp					�V�X�e��
 * @param	crp					���\�[�X
 * @param	crnl				���\�[�X�Ǘ����e�[�u��
 *
 * @retval	BOOL				TRUE = ����
 *
 */
//--------------------------------------------------------------
BOOL CATS_ResourceManagerInit(CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_RESOURCE_NUM_LIST* crnl)
{
	int i;
	int j;
	int num = CLACT_U_RES_MAX;
	int size;
	CLACT_U_RES_HEADER_PTR res_head;
	
	///< �V�X�e���E���\�[�X�ǂ��炩���������m�ۂ���Ă��Ȃ�
	if (csp == NULL || crp == NULL){
		return FALSE;
	}
	
	///< �}���`�Z���𗘗p���Ȃ��ꍇ�͊Ǘ��}�l�[�W���̐������炷
	if (crnl->resource_num.mcell_num == 0
	||	crnl->resource_num.mcell_anm_num == 0){
		num = CLACT_U_RES_MAX - 2;
	}
	crp->resTypeNum = num;
	
	///< ���\�[�X�}�l�[�W���[�쐬
	for (i = 0; i < num; i++){
		crp->resManager[i] = CLACT_U_ResManagerInit(crnl->res_num[i], i, csp->heap_area);
	}
	
	///< ���\�[�X�}�l�[�W���[�ɓo�^����f�[�^�ǂݍ���
	for (i = 0; i < num; i++){
		size = crnl->res_num[i];
		
		if (size == 0){ continue; }
		
		crp->resObjTbl[i] = CLACT_U_ResManagerResObjTblMake(size, csp->heap_area);
		crp->resObjNum[i] = 0;
		
		for (j = 0; j < crp->resObjTbl[i]->tbl_num; j++){
			crp->resObjTbl[i]->tbl[j] = NULL;
		}
	}

	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	�L�����̓o�^	�p�X
 *
 * @param	csp	
 * @param	crp	
 * @param	path	
 * @param	id					�Ǘ�ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceChar(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int trans_mode, int id)
{
	CLACT_U_RES_OBJ_PTR obj;

	if (CLACT_U_ResManagerCheckID(crp->resManager[0], id) == FALSE){
		return FALSE;
	}
	
	obj = CLACT_U_ResManagerResAddChar(crp->resManager[0], path, id, trans_mode, csp->heap_area);

	if (obj != NULL){
		CLACT_U_CharManagerSetAreaCont(obj);
		
		CATS_LoadResourceTable_Private(crp->resObjTbl[0], obj);
		
		return TRUE;
	}
	
	GF_ASSERT(0);
	
	return obj == NULL ? FALSE : TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	�L�����̓o�^	�A�[�J�C�u
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				�A�[�J�C�uIndex
 * @param	data_id				�f�[�^Index
 * @param	comp				���k�t���O
 * @param	id					�Ǘ�ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceCharArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int trans_mode, int id)
{
	CLACT_U_RES_OBJ_PTR obj;

	if (CLACT_U_ResManagerCheckID(crp->resManager[0], id) == FALSE){
		return FALSE;
	}
	
	obj = CLACT_U_ResManagerResAddArcChar(crp->resManager[0], arc_id, data_id, comp, id, trans_mode, csp->heap_area);

	if (obj != NULL){
		CLACT_U_CharManagerSetAreaCont(obj);
		
		CATS_LoadResourceTable_Private(crp->resObjTbl[0], obj);	
		
		return TRUE;
	}
	
	GF_ASSERT(0);
	
	return obj == NULL ? FALSE : TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	�p���b�g�o�^	�p�X
 *
 * @param	csp	
 * @param	crp	
 * @param	path				�p�X
 * @param	num					�o�^��
 * @param	id					�Ǘ�ID
 *
 * @retval	�o�^�����ʒu�̃p���b�g�ԍ�(���s����ASSERT�Œ�~���܂�)
 *
 */
//--------------------------------------------------------------
u8 CATS_LoadResourcePltt(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int num, int trans_mode, int id)
{
	CLACT_U_RES_OBJ_PTR obj;
	int ret;
	
	if (CLACT_U_ResManagerCheckID(crp->resManager[1], id) == FALSE){
		return FALSE;
	}
	
	obj = CLACT_U_ResManagerResAddPltt(crp->resManager[1], path, id, trans_mode, num, csp->heap_area);

	if (obj != NULL){
//		CLACT_U_PlttManagerSet(obj);
		ret = CLACT_U_PlttManagerSetCleanArea(obj);
		GF_ASSERT(ret == TRUE && "�p���b�g�o�^���s");
		
		CATS_LoadResourceTable_Private(crp->resObjTbl[1], obj);	
		
		return CLACT_U_PlttManagerGetPlttNo(obj, trans_mode);	//�o�^���̃p���b�g�ԍ���Ԃ�
	}
	
	GF_ASSERT(0);
	
	return 0;
}


//--------------------------------------------------------------
/**
 * @brief	�p���b�g�o�^	�A�[�J�C�u
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				�A�[�J�C�uIndex
 * @param	data_id				�f�[�^Index
 * @param	comp				���k�t���O
 * @param	num					�o�^��
 * @param	id					�Ǘ�ID
 *
 * @retval	�o�^�����ʒu�̃p���b�g�ԍ�(���s����ASSERT�Œ�~���܂�)
 *
 */
//--------------------------------------------------------------
s8 CATS_LoadResourcePlttArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int num, int trans_mode, int id)
{
	CLACT_U_RES_OBJ_PTR obj;
	int ret;
	
	if (CLACT_U_ResManagerCheckID(crp->resManager[1], id) == FALSE){
		return -1;
	}
	
	obj = CLACT_U_ResManagerResAddArcPltt(crp->resManager[1], arc_id, data_id, comp, id, trans_mode, num, csp->heap_area);

	if (obj != NULL){
		//CLACT_U_PlttManagerSet(obj);
		ret = CLACT_U_PlttManagerSetCleanArea(obj);
		GF_ASSERT(ret == TRUE && "�p���b�g�o�^���s");
		
		CATS_LoadResourceTable_Private(crp->resObjTbl[1], obj);	
		return CLACT_U_PlttManagerGetPlttNo(obj, trans_mode);	//�o�^���̃p���b�g�ԍ���Ԃ�
	}
	
	GF_ASSERT(0);
	
	return -1;
}

//--------------------------------------------------------------
/**
 * @brief   �p���b�g�o�^���A�p���b�g���[�N�ɂ��W�J���s��
 *
 * @param   PALETTE_FADE_PTR		�p���b�g�t�F�[�h�V�X�e���ւ̃|�C���^
 * @param   req						���N�G�X�g�f�[�^�ԍ�(FADE_MAIN_BG��)
 * @param   csp						
 * @param   crp						
 * @param	arc_id					�A�[�J�C�uIndex
 * @param	data_id					�f�[�^Index
 * @param	comp					���k�t���O
 * @param	num						�o�^��
 * @param   trans_mode				NNS_G2D_VRAM_TYPE_2DMAIN��
 * @param	id						�Ǘ�ID
 *
 * @retval  �Z�b�g�����p���b�g�ʒu(���s����ASSERT�Œ�~���܂�)
 */
//--------------------------------------------------------------
u8 CATS_LoadResourcePlttWork(PALETTE_FADE_PTR pfd, FADEREQ req, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, const char* path, int num, int trans_mode, int id)
{
	int pal_no;
	
	pal_no = CATS_LoadResourcePltt(csp, crp, path, num, trans_mode, id);
	PaletteWorkSet_VramCopy(pfd, req, pal_no * 16, num * 0x20);
	return pal_no;
}

//--------------------------------------------------------------
/**
 * @brief   �p���b�g�o�^���A�p���b�g���[�N�ɂ��W�J���s��
 *
 * @param   PALETTE_FADE_PTR		�p���b�g�t�F�[�h�V�X�e���ւ̃|�C���^
 * @param   req						���N�G�X�g�f�[�^�ԍ�(FADE_MAIN_BG��)
 * @param   csp						
 * @param   crp						
 * @param	arc_id					�A�[�J�C�uIndex
 * @param	data_id					�f�[�^Index
 * @param	comp					���k�t���O
 * @param	num						�o�^��
 * @param   trans_mode				NNS_G2D_VRAM_TYPE_2DMAIN��
 * @param	id						�Ǘ�ID
 *
 * @retval  �Z�b�g�����p���b�g�ʒu(���s����ASSERT�Œ�~���܂�)
 */
//--------------------------------------------------------------
u8 CATS_LoadResourcePlttWorkArc(PALETTE_FADE_PTR pfd, FADEREQ req, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, int arc_id, int data_id, int comp, int num, int trans_mode, int id)
{
	int pal_no;

	pal_no = CATS_LoadResourcePlttArc(csp, crp, arc_id, data_id, comp, num, trans_mode, id);

	if (pal_no != -1){
		PaletteWorkSet_VramCopy(pfd, req, pal_no * 16, num * 0x20);
	}
	return pal_no;
}

//--------------------------------------------------------------
/**
 * @brief	�Z���o�^	�p�X
 *
 * @param	csp	
 * @param	crp	
 * @param	path				�p�X
 * @param	id					�Ǘ�ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceCell(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int id)
{
	return CATS_LoadResourceCell_Private(csp, crp, path, 2, id);
}


//--------------------------------------------------------------
/**
 * @brief	�Z���o�^			�A�[�J�C�u
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				�A�[�J�C�uIndex
 * @param	data_id				�f�[�^Index
 * @param	comp				���k�t���O
 * @param	id					�Ǘ�ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceCellArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int id)
{
	return CATS_LoadResourceCellArc_Private(csp, crp, arc_id, data_id, comp, 2, id);
}


//--------------------------------------------------------------
/**
 * @brief	�Z���A�j���o�^	�p�X
 *
 * @param	csp	
 * @param	crp	
 * @param	path				�p�X
 * @param	id					�Ǘ�ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceCellAnm(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int id)
{
	return CATS_LoadResourceCell_Private(csp, crp, path, 3, id);
}


//--------------------------------------------------------------
/**
 * @brief	�Z���A�j���o�^	�A�[�J�C�u
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				�A�[�J�C�uIndex
 * @param	data_id				�f�[�^Index
 * @param	comp				���k�t���O
 * @param	id					�Ǘ�ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceCellAnmArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int id)
{
	return CATS_LoadResourceCellArc_Private(csp, crp, arc_id, data_id, comp, 3, id);
}


//--------------------------------------------------------------
/**
 * @brief	�}���`�Z���o�^			�A�[�J�C�u
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				�A�[�J�C�uIndex
 * @param	data_id				�f�[�^Index
 * @param	comp				���k�t���O
 * @param	id					�Ǘ�ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceMCell(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int id)
{
	return CATS_LoadResourceCell_Private(csp, crp, path, 4, id);
}


//--------------------------------------------------------------
/**
 * @brief	�}���`�Z���o�^			�A�[�J�C�u
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				�A�[�J�C�uIndex
 * @param	data_id				�f�[�^Index
 * @param	comp				���k�t���O
 * @param	id					�Ǘ�ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceMCellArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int id)
{
	return CATS_LoadResourceCellArc_Private(csp, crp, arc_id, data_id, comp, 4, id);
}


//--------------------------------------------------------------
/**
 * @brief	�}���`�Z���A�j��	�p�X
 *
 * @param	csp	
 * @param	crp	
 * @param	path				�p�X
 * @param	id					�Ǘ�ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceMCellAnm(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int id)
{
	return CATS_LoadResourceCell_Private(csp, crp, path, 5, id);
}


//--------------------------------------------------------------
/**
 * @brief	�}���`�Z���A�j��	�A�[�J�C�u
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				�A�[�J�C�uIndex
 * @param	data_id				�f�[�^Index
 * @param	comp				���k�t���O
 * @param	id					�Ǘ�ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceMCellAnmArc(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int id)
{
	return CATS_LoadResourceCellArc_Private(csp, crp, arc_id, data_id, comp, 5, id);
}


//--------------------------------------------------------------
/**
 * @brief	�A�N�^�[�o�^	���\�[�XID�w��
 *
 * @param	csp					�V�X�e��
 * @param	crp					���\�[�X
 * @param	coap_s				�o�^�p�����[�^�[
 *
 * @retval	CATS_ACT_PTR		�A�N�^�[�Ǘ����[�N�|�C���^
 *
 */
//--------------------------------------------------------------
CATS_ACT_PTR CATS_ObjectAdd_S(CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_OBJECT_ADD_PARAM_S* coap_s)
{
	int i;
	int def_palno;
	CATS_ACT_PTR cap = NULL;
	CLACT_ADD	 add;
	int id_list[CLACT_U_RES_MAX];
	
	cap = sys_AllocMemory(csp->heap_area, sizeof(TCATS_ACT));
	
	if (cap == NULL){
		return NULL;
	}
	
#if 1

	///< �w�b�_�[�̃������m��
	cap->act_htp = sys_AllocMemory(csp->heap_area, sizeof(CLACT_HEADER_TBL));
	
	if (cap->act_htp == NULL){
		return NULL;
	}
	
	cap->act_htp->tbl = sys_AllocMemory(csp->heap_area, sizeof(CLACT_HEADER));
	cap->act_hd = cap->act_htp->tbl;
	
	if (cap->act_htp->tbl == NULL){
		if (cap->act_htp){
			sys_FreeMemoryEz(cap->act_htp);
		}
		return NULL;
	}

#else
	
	cap->act_hd = sys_AllocMemory(csp->heap_area, sizeof(CLACT_HEADER));
	
#endif

	///< ���\�[�XID������������
	for (i = 0; i < CLACT_U_RES_MAX; i++){
		id_list[i] = coap_s->id[i];
	}
	
	if (crp->resManager[4] == NULL
	||	crp->resManager[5] == NULL){
		///< �}�l�[�W���[�������ꍇ�́A�f�[�^�w�薳��
		id_list[4] = CLACT_U_HEADER_DATA_NONE;
		id_list[5] = CLACT_U_HEADER_DATA_NONE;
	}
	else {	
		///< �f�[�^�w�肳��Ă��Ă��A�w��ID�̃��\�[�X�������ꍇ���f�[�^����
		if (id_list[4] != CLACT_U_HEADER_DATA_NONE
		&&  CLACT_U_ResManagerCheckID(crp->resManager[4], id_list[4]) == FALSE){
			id_list[4] = CLACT_U_HEADER_DATA_NONE;
		}

		if (id_list[5] != CLACT_U_HEADER_DATA_NONE
		&&  CLACT_U_ResManagerCheckID(crp->resManager[5], id_list[5]) == FALSE){
			id_list[5] = CLACT_U_HEADER_DATA_NONE;
		}	
	}
	
	///< ���ۂɃw�b�_�[���쐬
	CLACT_U_MakeHeader(cap->act_hd,
					   id_list[0], id_list[1],
					   id_list[2], id_list[3],
					   id_list[4], id_list[5],
					   coap_s->vram_trans,
					   coap_s->bg_pri,
					   crp->resManager[0], crp->resManager[1],
					   crp->resManager[2], crp->resManager[3],
					   crp->resManager[4], crp->resManager[5]);
	
	///< OBJ �̓o�^
	add.ClActSet	= crp->ca_sp;					///< �Z���A�N�^�[�Z�b�g
	add.ClActHeader = cap->act_hd;					///< �w�b�_�[������o��
	
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
	add.heap		= csp->heap_area;				///< �q�[�v�̈�
	
	cap->act = CLACT_Add(&add);						///< �o�^
	
	cap->vram_trans = coap_s->vram_trans;
	
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


//--------------------------------------------------------------
/**
 * @brief   �o�^�ς݂̃p���b�g��ImageProxy���擾
 *
 * @param   crp			
 * @param   pltt_id		
 *
 * @retval  
 */
//--------------------------------------------------------------
const NNSG2dImagePaletteProxy* CATS_PlttProxy( CATS_RES_PTR crp, int pltt_id )
{
	CLACT_U_RES_OBJ_PTR res = CLACT_U_ResManagerGetIDResObjPtr( crp->resManager[1], pltt_id );
	return CLACT_U_PlttManagerGetProxy( res, NULL );
}

//--------------------------------------------------------------
/**
 * @brief   �o�^�ς݂̃p���b�g�Ǘ�ID����A�]����̃p���b�g�ԍ����t��������
 *
 * @param   crp			
 * @param   pltt_id		�p���b�g�Ǘ�ID
 * @param   vram_type	VRAM�]���^�C�v(NNS_G2D_VRAM_TYPE_2DMAIN or NNS_G2D_VRAM_TYPE_2DSUB)
 *
 * @retval  �p���b�g�ԍ�
 */
//--------------------------------------------------------------
u32 CATS_PlttID_NoGet(CATS_RES_PTR crp, int pltt_id, NNS_G2D_VRAM_TYPE vram_type)
{
	CLACT_U_RES_OBJ_PTR res = CLACT_U_ResManagerGetIDResObjPtr( crp->resManager[1], pltt_id );
	return CLACT_U_PlttManagerGetPlttNo(res, vram_type );
}


//--------------------------------------------------------------
/**
 * @brief	���\�[�X���
 *
 * @param	crp	
 * @param	id	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_FreeResourceChar(CATS_RES_PTR crp, int id)
{
	return CATS_DeleteResourceCharData_Private(crp->resManager[0], crp->resObjTbl[0], id);		
}


//--------------------------------------------------------------
/**
 * @brief	���\�[�X���
 *
 * @param	crp	
 * @param	id	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_FreeResourcePltt(CATS_RES_PTR crp, int id)
{
	return CATS_DeleteResourcePlttData_Private(crp->resManager[1], crp->resObjTbl[1], id);
}


//--------------------------------------------------------------
/**
 * @brief	���\�[�X���
 *
 * @param	crp	
 * @param	id	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_FreeResourceCell(CATS_RES_PTR crp, int id)
{
	return CATS_DeleteResourceData_Private(crp->resManager[2], crp->resObjTbl[2], id);
}


//--------------------------------------------------------------
/**
 * @brief	���\�[�X���
 *
 * @param	crp	
 * @param	id	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_FreeResourceCellAnm(CATS_RES_PTR crp, int id)
{
	return CATS_DeleteResourceData_Private(crp->resManager[3], crp->resObjTbl[3], id);
}


//--------------------------------------------------------------
/**
 * @brief	���\�[�X���
 *
 * @param	crp	
 * @param	id	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_FreeResourceMCell(CATS_RES_PTR crp, int id)
{
	return CATS_DeleteResourceData_Private(crp->resManager[4], crp->resObjTbl[4], id);
}


//--------------------------------------------------------------
/**
 * @brief	���\�[�X���
 *
 * @param	crp	
 * @param	id	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CATS_FreeResourceMCellAnm(CATS_RES_PTR crp, int id)
{
	return CATS_DeleteResourceData_Private(crp->resManager[5], crp->resObjTbl[5], id);
}


//--------------------------------------------------------------
/**
 * @brief	���\�[�X�̔j��
 *
 * @param	csp					�V�X�e��
 * @param	crp					���\�[�X
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ResourceDestructor_S(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	int i;
	
	CATS_ClactSetDelete(crp);		///< �Z���Z�b�g�j��

	///< �f�[�^�j��
	CLACT_U_CharManagerDeletes(crp->resObjTbl[0]);
	CLACT_U_PlttManagerDeletes(crp->resObjTbl[1]);
	
	for (i = 0; i < crp->resTypeNum; i++){
		
		///< ���\�[�X�I�u�W�F�e�[�u���j��
		CLACT_U_ResManagerResObjTblDelete(crp->resObjTbl[i]);
		
		///< ���\�[�X�}�l�[�W���[�j��
		CLACT_U_ResManagerDelete(crp->resManager[i]);
	}

	CATS_ResourceFree(csp, crp);	///< ���\�[�X�̃������j��
}


//--------------------------------------------------------------
/**
 * @brief	�A�N�^�[�|�C���^�̍폜
 *
 * @param	cap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ActorPointerDelete_S(CATS_ACT_PTR cap)
{
	if (cap->vram_trans){
		CLACT_U_CharManagerDeleteVramTransferProxy(cap->act_hd->pImageProxy);
	}
	
	CLACT_Delete(cap->act);
	CLACT_U_CLACT_HeaderTblDelete(cap->act_htp);
	
	sys_FreeMemoryEz(cap);
}






// =============================================================================
//
//
//	�������Q�Ɗ֐��S
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	�Z���̓o�^	�p�X
 *
 * @param	csp	
 * @param	crp	
 * @param	path		�p�X
 * @param	type		�Z���̎��
 * @param	id			�Ǘ�ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL CATS_LoadResourceCell_Private(CATS_SYS_PTR csp, CATS_RES_PTR crp, const char* path, int type, int id)
{
	CLACT_U_RES_OBJ_PTR obj;
	int ret;
	
	obj = CLACT_U_ResManagerResAddKindCell(crp->resManager[type], path, id, type, csp->heap_area);

	if (obj != NULL){		
		ret = CATS_LoadResourceTable_Private(crp->resObjTbl[type], obj);
		
		GF_ASSERT(ret == TRUE && "�Z���o�^���s");
		
		return ret;
	}
	
	return obj == NULL ? FALSE : TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	�Z���̓o�^		�A�[�J�C�u
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				�A�[�J�C�uIndex
 * @param	data_id				�f�[�^Index
 * @param	comp				���k�t���O
 * @param	type				�Z���̎��
 * @param	id					�Ǘ�ID
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL CATS_LoadResourceCellArc_Private(CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, int comp, int type, int id)
{
	CLACT_U_RES_OBJ_PTR obj;
	int ret;

	if (CLACT_U_ResManagerCheckID(crp->resManager[type], id) == FALSE){
		return FALSE;
	}
	
	obj = CLACT_U_ResManagerResAddArcKindCell(crp->resManager[type], arc_id, data_id, comp, id, type, csp->heap_area);

	if (obj != NULL){
		ret = CATS_LoadResourceTable_Private(crp->resObjTbl[type], obj);
		
		GF_ASSERT(ret == TRUE && "�Z���o�^���s");
		
		return ret;
	}
	
	GF_ASSERT(0);
	
	return obj == NULL ? FALSE : TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	���\�[�X�e�[�u���̊J���Ă���ꏊ�ɁA���\�[�X�I�u�W�F�̃��[�h
 *
 * @param	tbl					���\�[�X�e�[�u���̃|�C���^
 * @param	obj					���\�[�XOBJ�̃|�C���^
 *
 * @retval	BOOL				TRUE = ����
 *
 */
//--------------------------------------------------------------
static BOOL CATS_LoadResourceTable_Private(CLACT_U_RES_OBJ_TBL* tbl, CLACT_U_RES_OBJ_PTR obj)
{
	int i;
	
	for (i = 0; i < tbl->tbl_num; i++){
		
		if (tbl->tbl[i] != NULL){ continue; }
		
		tbl->tbl[i] = obj;
		tbl->tbl_now++;
		
		return TRUE;
	}
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	���\�[�X�e�[�u������A���\�[�XID���������Ĉ�v�������\�[�X��j��
 *
 * @param	tbl					���\�[�X�e�[�u���̃|�C���^
 * @param	id					�폜ID
 *
 * @retval	BOOL				TRUE = ����	
 *
 */
//--------------------------------------------------------------
static BOOL CATS_DeleteResourceData_Private(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_TBL* tbl, int id)
{
	int i;
	int hid;
	
	for (i = 0; i < tbl->tbl_num; i++){
		
		if (tbl->tbl[i] == NULL){ continue; }
		
		hid = CLACT_U_ResManagerGetResObjID(tbl->tbl[i]);
		
		if (hid == id){
			CLACT_U_ResManagerResDelete(resm, tbl->tbl[i]);
			tbl->tbl[i] = NULL;
			tbl->tbl_now--;
						
			return TRUE;
		}
	}
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	���\�[�X�e�[�u������A���\�[�XID���������Ĉ�v�������\�[�X��j��
 *
 * @param	resm	
 * @param	tbl	
 * @param	id	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL CATS_DeleteResourceCharData_Private(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_TBL* tbl, int id)
{
	int i;
	int hid;
	
	for (i = 0; i < tbl->tbl_num; i++){
		
		if (tbl->tbl[i] == NULL){ continue; }
		
		hid = CLACT_U_ResManagerGetResObjID(tbl->tbl[i]);
		
		if (hid == id){
			DelChar(id);
			CLACT_U_ResManagerResDelete(resm, tbl->tbl[i]);
			tbl->tbl[i] = NULL;
			tbl->tbl_now--;
						
			return TRUE;
		}
	}
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	���\�[�X�e�[�u������A���\�[�XID���������Ĉ�v�������\�[�X��j��
 *
 * @param	resm	
 * @param	tbl	
 * @param	id	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL CATS_DeleteResourcePlttData_Private(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_TBL* tbl, int id)
{

	int i;
	int hid;
	
	for (i = 0; i < tbl->tbl_num; i++){
		
		if (tbl->tbl[i] == NULL){ continue; }
		
		hid = CLACT_U_ResManagerGetResObjID(tbl->tbl[i]);
		
		if (hid == id){
			DelPltt(id);
			CLACT_U_ResManagerResDelete(resm, tbl->tbl[i]);
			tbl->tbl[i] = NULL;
			tbl->tbl_now--;
						
			return TRUE;
		}
	}
	
	return FALSE;
}

















// =============================================================================
//
//
//	��OBJ����֘A�܂Ƃ�			[ ACTOR_TOOL ]
//
//
// =============================================================================
// =============================================================================
//
//	���\������
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	OBJ�̃A�j���X�V
 *
 * @param	act					OBJ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectUpdate(CLACT_WORK_PTR act)
{
	CLACT_AnmFrameChg(act, FX32_ONE);
}

//--------------------------------------------------------------
/**
 * @brief	OBJ�̃A�j���X�V
 *
 * @param	cap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectUpdateCap(CATS_ACT_PTR cap)
{
	CATS_ObjectUpdate(cap->act);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�t���[����i�߂�
 *
 *	@param	cap
 *	@param	frame	�i�߂�l
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectUpdateNumCap(CATS_ACT_PTR cap, fx32 frame)
{
	CLACT_AnmFrameChg(cap->act, frame);
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�j���[�V�����V�[�P���X�ݒ�@�A�j���̐؂�ւ�
 *
 *	@param	cap
 *	@param	seq		�V�[�P���X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectAnimeSeqSetCap( CATS_ACT_PTR cap, u32 seq )
{
	CLACT_AnmChg( cap->act, seq );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�j���[�V�����V�[�P���X�擾
 *
 *	@param	cap 
 *
 *	@return	�V�[�P���X
 *
 *
 */
//-----------------------------------------------------------------------------
u32 CATS_ObjectAnimeSeqGetCap( CATS_ACT_PTR cap )
{
	return CLACT_AnmGet( cap->act );
}


//--------------------------------------------------------------
/**
 * @brief	�I�[�g�A�j���ݒ�
 *
 * @param	act	
 * @param	flag				CATS_ANM_AUTO_ON / CATS_ANM_AUTO_OFF
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectAutoAnimeSet(CLACT_WORK_PTR act, int flag)
{
	CLACT_SetAnmFlag(act, flag);
}

//--------------------------------------------------------------
/**
 * @brief	�I�[�g�A�j���ݒ�
 *
 * @param	cap	
 * @param	flag	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectAutoAnimeSetCap(CATS_ACT_PTR cap, int flag)
{
	CATS_ObjectAutoAnimeSet(cap->act, flag);
}


//--------------------------------------------------------------
/**
 * @brief	�I�[�g�A�j���擾
 *
 * @param	act	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int CATS_ObjectAutoAnimeGet(CLACT_WORK_PTR act)
{
	return CLACT_GetAnmFlag(act);
}


//--------------------------------------------------------------
/**
 * @brief	�I�[�g�A�j���擾
 *
 * @param	cap	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int CATS_ObjectAutoAnimeGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectAutoAnimeGet(cap->act);
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�[�g�A�j���X�s�[�h�ݒ�
 *
 *	@param	act			
 *	@param	speed	�A�j���X�s�[�h
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectAutoAnimeSpeedSet(CLACT_WORK_PTR act, fx32 speed)
{
	CLACT_SetAnmFrame( act, speed );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�[�g�A�j���X�s�[�h�ݒ�
 *
 *	@param	cap
 *	@param	speed	�A�j���X�s�[�h
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectAutoAnimeSpeedSetCap(CATS_ACT_PTR cap, fx32 speed)
{
	CATS_ObjectAutoAnimeSpeedSet( cap->act, speed );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�[�g�A�j���X�s�[�h�擾
 *
 *	@param	act	
 *
 *	@return	�A�j���X�s�[�h
 *
 *
 */
//-----------------------------------------------------------------------------
fx32 CATS_ObjectAutoAnimeSpeedGet(CLACT_WORK_PTR act)
{
	return CLACT_GetAnmFrame( act );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�[�g�A�j���X�s�[�h�擾
 *
 *	@param	cap
 *
 *	@return	�A�j���X�s�[�h
 *
 *
 */
//-----------------------------------------------------------------------------
fx32 CATS_ObjectAutoAnimeSpeedGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectAutoAnimeSpeedGet( cap->act );
}


//--------------------------------------------------------------
/**
 * @brief	�A�j������`�F�b�N
 *
 * @param	act	
 *
 * @retval	TRUE	�A�j���[�V������
 * @retval	FALSE	��~��
 *
 */
//--------------------------------------------------------------
BOOL CATS_ObjectAnimeActiveCheck(CLACT_WORK_PTR act)
{
	return CLACT_AnmActiveCheck(act);
}

//--------------------------------------------------------------
/**
 * @brief	�I�[�g�A�j���擾
 *
 * @param	cap	
 *
 * @retval	TRUE	�A�j���[�V������
 * @retval	FALSE	��~��
 *
 */
//--------------------------------------------------------------
BOOL CATS_ObjectAnimeActiveCheckCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectAnimeActiveCheck(cap->act);
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�j���[�V�����t���[���ݒ�
 *
 *	@param	act		�A�N�^�[
 *	@param	frame	�ݒ�t���[��
 *
 *	@retval	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectAnimeFrameSet(CLACT_WORK_PTR act, u16 frame)
{
	CLACT_AnmFrameSet( act, frame );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�j���[�V�����t���[���ݒ�@�R�}��i�߂�
 *
 *	@param	cap
 *	@param	frame	�ݒ�t���[��
 *
 *	@retval	none	
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectAnimeFrameSetCap(CATS_ACT_PTR cap, u16 frame)
{
	CATS_ObjectAnimeFrameSet( cap->act, frame );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�j���[�V�����t���[�����擾
 *
 *	@param	act	�A�N�^�[
 *
 *	@return	�t���[��
 *
 *
 */
//-----------------------------------------------------------------------------
u16 CATS_ObjectAnimeFrameGet(CLACT_WORK_PTR act)
{
	return CLACT_AnmFrameGet( act );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�j���[�V�����t���[�����擾
 *
 *	@param	cap	�A�N�^�[
 *
 *	@return	�t���[��
 *
 *
 */
//-----------------------------------------------------------------------------
u16 CATS_ObjectAnimeFrameGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectAnimeFrameGet( cap->act );
}


//--------------------------------------------------------------
/**
 * @brief	OBJ�̕\���ݒ�
 *
 * @param	act					OBJ
 * @param	enable				CATS_ENABLE_TRUE	= �\��
 *								CATS_ENABLE_FALSE	= ��\��
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectEnable(CLACT_WORK_PTR act, int enable)
{
	CLACT_SetDrawFlag(act, enable);
}

//--------------------------------------------------------------
/**
 * @brief	OBJ�̕\���ݒ�
 *
 * @param	cap	
 * @param	enable	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectEnableCap(CATS_ACT_PTR cap, int enable)
{
	CATS_ObjectEnable(cap->act, enable);
}


//--------------------------------------------------------------
/**
 * @brief	OBJ�̕\���ݒ�擾
 *
 * @param	act	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	CATS_ObjectEnableGet(CLACT_WORK_PTR act)
{
	return CLACT_GetDrawFlag(act);
}


//--------------------------------------------------------------
/**
 * @brief	OBJ�̕\���ݒ�擾
 *
 * @param	cap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	CATS_ObjectEnableGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectEnableGet(cap->act);
}


//--------------------------------------------------------------
/**
 * @brief	�p���b�g�ύX
 *
 * @param	act	
 * @param	pal	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPaletteSet(CLACT_WORK_PTR act, int pal)
{
	CLACT_PaletteNoChg(act, pal);
}

//--------------------------------------------------------------
/**
 * @brief	�p���b�g�ύX
 *
 * @param	cap	
 * @param	pal	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPaletteSetCap(CATS_ACT_PTR cap, int pal)
{
	CATS_ObjectPaletteSet(cap->act, pal);	
}

//--------------------------------------------------------------
/**
 * @brief   �p���b�g�I�t�Z�b�g�ύX
 *
 * @param   act			
 * @param   pal_ofs		
 */
//--------------------------------------------------------------
void CATS_ObjectPaletteOffsetSet(CLACT_WORK_PTR act, int pal_ofs)
{
	CLACT_PaletteOffsetChg(act, pal_ofs);
}

//--------------------------------------------------------------
/**
 * @brief   �p���b�g�I�t�Z�b�g�ύX
 *
 * @param   cap		
 * @param   pal_ofs		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPaletteOffsetSetCap(CATS_ACT_PTR cap, int pal_ofs)
{
	CATS_ObjectPaletteOffsetSet(cap->act, pal_ofs);	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�I�t�Z�b�g�̎擾
 *
 *	@param	cap		���[�N
 *
 *	@return	�p���b�g�I�t�Z�b�g
 *
 *
 */
//-----------------------------------------------------------------------------
int CATS_ObjectPaletteOffsetGetCap(CATS_ACT_PTR cap)
{
	return CLACT_PaletteOffsetGet(cap->act);
}


//--------------------------------------------------------------
/**
 * @brief	BG�Ƃ̗D��x�̕ύX
 *
 * @param	act	
 * @param	pri	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectBGPriSet(CLACT_WORK_PTR act, int pri)
{
	CLACT_BGPriorityChg(act, pri);
}


//--------------------------------------------------------------
/**
 * @brief	BG �Ƃ̗D��x
 *
 * @param	cap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	CATS_ObjectBGPriGetCap(CATS_ACT_PTR cap)
{
	return CLACT_BGPriorityGet(cap->act);
}


//--------------------------------------------------------------
/**
 * @brief	BG�Ƃ̗D��x�̕ύX
 *
 * @param	cap	
 * @param	pri	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectBGPriSetCap(CATS_ACT_PTR cap, int pri)
{
	CATS_ObjectBGPriSet(cap->act, pri);
}


//--------------------------------------------------------------
/**
 * @brief	�D��x�̕ύX
 *
 * @param	act	
 * @param	pri	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPriSet(CLACT_WORK_PTR act, int pri)
{
	CLACT_DrawPriorityChg(act, pri);
}

//--------------------------------------------------------------
/**
 * @brief	�D��x�̕ύX
 *
 * @param	cap	
 * @param	pri	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPriSetCap(CATS_ACT_PTR cap, int pri)
{
	CATS_ObjectPriSet(cap->act, pri);
}

//--------------------------------------------------------------
/**
 * @brief	�D��x�擾
 *
 * @param	act	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
u32 CATS_ObjectPriGet(CLACT_WORK_PTR act)
{
	return CLACT_DrawPriorityGet(act);
}

//--------------------------------------------------------------
/**
 * @brief	�D��x�擾
 *
 * @param	cap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
u32 CATS_ObjectPriGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectPriGet(cap->act);
}


// =============================================================================
//
//	�����W����
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	OBJ�̍��W�ύX
 *
 * @param	act					OBJ
 * @param	x	
 * @param	y	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosSet(CLACT_WORK_PTR act, s16 x, s16 y)
{
	VecFx32 vec;
		
	vec.x = x * FX32_ONE;
	vec.y = y * FX32_ONE;
	if(CLACT_VramTypeGet(act) == NNS_G2D_VRAM_TYPE_2DSUB){
		vec.y += SUB_SURFACE_Y;
	}
	vec.z = 0;
	
	CLACT_SetMatrix(act, &vec);	
}

//--------------------------------------------------------------
/**
 * @brief	OBJ�̍��W�ύX
 *
 * @param	cap	
 * @param	x	
 * @param	y	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosSetCap(CATS_ACT_PTR cap, s16 x, s16 y)
{
	CATS_ObjectPosSet(cap->act, x, y);
}

//--------------------------------------------------------------
/**
 * @brief	OBJ�̍��W�ύX(SUB_SURFACE_Y�ɑ������ޒl���O������w��)
 *
 * @param	act					OBJ
 * @param	x	
 * @param	y	
 * @param   sub_surface_y		�T�u��ʂɏo��OBJ�̏ꍇ�A��������SURFACE�l
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosSet_SubSurface(CLACT_WORK_PTR act, s16 x, s16 y, fx32 sub_surface_y)
{
	VecFx32 vec;
		
	vec.x = x * FX32_ONE;
	vec.y = y * FX32_ONE;
	if(CLACT_VramTypeGet(act) == NNS_G2D_VRAM_TYPE_2DSUB){
		vec.y += sub_surface_y;
	}
	vec.z = 0;
	
	CLACT_SetMatrix(act, &vec);	
}

//--------------------------------------------------------------
/**
 * @brief	OBJ�̍��W�ύX(SUB_SURFACE_Y�ɑ������ޒl���O������w��)
 *
 * @param	cap	
 * @param	x	
 * @param	y	
 * @param   sub_surface_y		�T�u��ʂɏo��OBJ�̏ꍇ�A��������SURFACE�l
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosSetCap_SubSurface(CATS_ACT_PTR cap, s16 x, s16 y, fx32 sub_surface_y)
{
	CATS_ObjectPosSet_SubSurface(cap->act, x, y, sub_surface_y);
}

//--------------------------------------------------------------
/**
 * @brief	OBJ�̍��W�擾
 *
 * @param	act					OBJ
 * @param	x					�擾X���W�����
 * @param	y					�擾Y���W�����
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosGet(CLACT_WORK_PTR act, s16 *x, s16 *y)
{
	const VecFx32 *p_vec;
	
	p_vec = CLACT_GetMatrix(act);
	*x = p_vec->x / FX32_ONE;
	if(CLACT_VramTypeGet(act) == NNS_G2D_VRAM_TYPE_2DSUB){
		*y = (p_vec->y - SUB_SURFACE_Y) / FX32_ONE;
	}
	else {
		*y = p_vec->y / FX32_ONE;
	}
}

//--------------------------------------------------------------
/**
 * @brief	OBJ�̍��W�擾
 *
 * @param	cap	
 * @param	x	
 * @param	y	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosGetCap(CATS_ACT_PTR cap, s16 *x, s16 *y)
{
	CATS_ObjectPosGet(cap->act, x, y);
}

//--------------------------------------------------------------
/**
 * @brief	OBJ�̍��W�擾(SUB_SURFACE_Y���O������w��)
 *
 * @param	act					OBJ
 * @param	x					�擾X���W�����
 * @param	y					�擾Y���W�����
 * @param   sub_surface_y		�T�u��ʂɏo��OBJ�̏ꍇ�A��������SURFACE�l
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosGet_SubSurface(CLACT_WORK_PTR act, s16 *x, s16 *y, fx32 sub_surface_y)
{
	const VecFx32 *p_vec;
	
	p_vec = CLACT_GetMatrix(act);
	*x = p_vec->x / FX32_ONE;
	if(CLACT_VramTypeGet(act) == NNS_G2D_VRAM_TYPE_2DSUB){
		*y = (p_vec->y - sub_surface_y) / FX32_ONE;
	}
	else {
		*y = p_vec->y / FX32_ONE;
	}
}

//--------------------------------------------------------------
/**
 * @brief	OBJ�̍��W�擾(SUB_SURFACE_Y���O������w��)
 *
 * @param	cap	
 * @param	x	
 * @param	y	
 * @param   sub_surface_y		�T�u��ʂɏo��OBJ�̏ꍇ�A��������SURFACE�l
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosGetCap_SubSurface(CATS_ACT_PTR cap, s16 *x, s16 *y, fx32 sub_surface_y)
{
	CATS_ObjectPosGet_SubSurface(cap->act, x, y, sub_surface_y);
}


//--------------------------------------------------------------
/**
 * @brief	OBJ�̈ړ�
 *
 * @param	act					OBJ
 * @param	x	
 * @param	y	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosMove(CLACT_WORK_PTR act, s16 x, s16 y)
{
	const VecFx32* p_vec;
	VecFx32 p_vec2;
	
	p_vec = CLACT_GetMatrix(act);
	
	p_vec2.x = p_vec->x + (x * FX32_ONE);
	p_vec2.y = p_vec->y + (y * FX32_ONE);
	p_vec2.z = p_vec->z;
	
	CLACT_SetMatrix(act, &p_vec2);
}

//--------------------------------------------------------------
/**
 * @brief	OBJ�̈ړ�
 *
 * @param	cap	
 * @param	x	
 * @param	y	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectPosMoveCap(CATS_ACT_PTR cap, s16 x, s16 y)
{
	CATS_ObjectPosMove(cap->act, x, y);
}


// =============================================================================
//
//	���A�t�B������ �t���b�v����
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	OBJ�̃A�t�B���p�����[�^�[�ݒ�
 *
 * @param	act					OBJ
 * @param	affine				�A�t�B���p�����[�^�[
 *		CLACT_AFFINE_NONE,		// �A�t�B���ϊ��Ȃ�
 *		CLACT_AFFINE_NORMAL,	// �A�t�B���ϊ�
 *		CLACT_AFFINE_DOUBLE,	// �{�p�A�t�B���ϊ�
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectAffineSet(CLACT_WORK_PTR act, int affine)
{
	CLACT_SetAffineParam(act, affine);
}

//--------------------------------------------------------------
/**
 * @brief	OBJ�̃A�t�B���p�����[�^�[�ݒ�
 *
 * @param	cap	
 * @param	affine	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectAffineSetCap(CATS_ACT_PTR cap, int affine)
{
	CATS_ObjectAffineSet(cap->act, affine);
}


//--------------------------------------------------------------
/**
 * @brief	OBJ�̃A�t�B���p�����[�^�[�擾
 *
 * @param	act					OBJ
 *
 * @retval	int
 *
 */
//--------------------------------------------------------------
int CATS_ObjectAffineGet(CLACT_WORK_PTR act)
{
	return CLACT_GetAffineParam(act);
}

//--------------------------------------------------------------
/**
 * @brief	OBJ�̃A�t�B���p�����[�^�[�擾
 *
 * @param	cap	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int CATS_ObjectAffineGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectAffineGet(cap->act);
}


//--------------------------------------------------------------
/**
 * @brief	OBJ�̊g�k���̕ύX
 *
 * @param	act					OBJ
 * @param	sx	
 * @param	sy	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectScaleSet(CLACT_WORK_PTR act, f32 sx, f32 sy)
{
	const VecFx32* p_vec;
	VecFx32* p_vec2;
	
	p_vec = CLACT_GetScale(act);
	
	p_vec2 = (VecFx32*)p_vec;
	
	p_vec2->x = (sx * FX32_ONE);
	p_vec2->y = (sy * FX32_ONE);
	
	CLACT_SetScale(act, p_vec2);
}

//--------------------------------------------------------------
/**
 * @brief	OBJ�̊g�k���̕ύX
 *
 * @param	cap	
 * @param	sx	
 * @param	sy	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectScaleSetCap(CATS_ACT_PTR cap, f32 sx, f32 sy)
{
	CATS_ObjectScaleSet(cap->act, sx, sy);
}


//--------------------------------------------------------------
/**
 * @brief	OBJ�̊g�k���̉��Z
 *
 * @param	act					OBJ
 * @param	sx	
 * @param	sy	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectScaleAdd(CLACT_WORK_PTR act, f32 sx, f32 sy)
{
	const VecFx32* p_vec;
	VecFx32* p_vec2;
	
	p_vec = CLACT_GetScale(act);
	
	p_vec2 = (VecFx32*)p_vec;
	
	p_vec2->x = p_vec->x + (sx * FX32_ONE);
	p_vec2->y = p_vec->y + (sy * FX32_ONE);
	
	CLACT_SetScale(act, p_vec2);
}

//--------------------------------------------------------------
/**
 * @brief	OBJ�̊g�k���̉��Z
 *
 * @param	cap	
 * @param	sx	
 * @param	sy	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectScaleAddCap(CATS_ACT_PTR cap, f32 sx, f32 sy)
{
	CATS_ObjectScaleAdd(cap->act, sx, sy);
}


//--------------------------------------------------------------
/**
 * @brief	OBJ�̊g�k�����擾
 *
 * @param	act	
 * @param	sx	
 * @param	sy	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectScaleGet(CLACT_WORK_PTR act, f32* sx, f32* sy)
{
	const VecFx32* p_vec;
	VecFx32* p_vec2;
	
	p_vec = CLACT_GetScale(act);
	
	*sx = p_vec->x / FX32_ONE;
	*sy = p_vec->y / FX32_ONE;
}

//--------------------------------------------------------------
/**
 * @brief	OBJ�̊g�k�����擾
 *
 * @param	cap	
 * @param	sx	
 * @param	sy	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectScaleGetCap(CATS_ACT_PTR cap, f32* sx, f32* sy)
{
	CATS_ObjectScaleGet(cap->act, sx, sy);
}


//--------------------------------------------------------------
/**
 * @brief	OBJ�̉�]�e�ݒ�
 *
 * @param	act	
 * @param	rot	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectRotationSet(CLACT_WORK_PTR act, u16 rot)
{
	CLACT_SetRotation(act, rot);
}

//--------------------------------------------------------------
/**
 * @brief	OBJ�̉�]�e�ݒ�
 *
 * @param	cap	
 * @param	rot	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectRotationSetCap(CATS_ACT_PTR cap, u16 rot)
{
	CATS_ObjectRotationSet(cap->act, rot);
}


//--------------------------------------------------------------
/**
 * @brief	OBJ�̉�]�������Z
 *
 * @param	act					OBJ
 * @param	rot	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectRotationAdd(CLACT_WORK_PTR act, s32 rot)
{
	u16 nrot;
	
	nrot = CLACT_GetRotation(act);
	
	nrot += rot;
	
	CLACT_SetRotation(act, nrot);
}

//--------------------------------------------------------------
/**
 * @brief	OBJ�̉�]�������Z
 *
 * @param	cap	
 * @param	rot	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectRotationAddCap(CATS_ACT_PTR cap, s32 rot)
{
	CATS_ObjectRotationAdd(cap->act, rot);
}


//--------------------------------------------------------------
/**
 * @brief	��]���擾
 *
 * @param	act					OBJ
 *
 * @retval	u16
 *
 */
//--------------------------------------------------------------
u16	CATS_ObjectRotationGet(CLACT_WORK_PTR act)
{
	return CLACT_GetRotation(act);
}

//--------------------------------------------------------------
/**
 * @brief	��]���擾
 *
 * @param	cap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
u16	CATS_ObjectRotationGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectRotationGet(cap->act);
}


//--------------------------------------------------------------
/**
 * @brief	�t���b�v����
 *
 * @param	act					OBJ
 * @param	flip				�t���b�v����
 * 		CLACT_FLIP_NONE,		// �t���b�v�Ȃ�
 * 		CLACT_FLIP_H,			// �t���b�v��������
 *		CLACT_FLIP_V,			// �t���b�v��������
 *		CLACT_FLIP_HV,			// �������t���b�v
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectFlipSet(CLACT_WORK_PTR act, int flip)
{
	CLACT_SetFlip(act, flip);
}

//--------------------------------------------------------------
/**
 * @brief	�t���b�v����
 *
 * @param	cap	
 * @param	flip	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectFlipSetCap(CATS_ACT_PTR cap, int flip)
{
	CATS_ObjectFlipSet(cap->act, flip);
}


//--------------------------------------------------------------
/**
 * @brief	�t���b�v�擾
 *
 * @param	act					OBJ
 *
 * @retval	int					�t���b�v���
 *
 */
//--------------------------------------------------------------
int CATS_ObjectFlipGet(CLACT_WORK_PTR act)
{
	return CLACT_GetFlip(act);
}

//--------------------------------------------------------------
/**
 * @brief	�t���b�v�擾
 *
 * @param	cap	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int CATS_ObjectFlipGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectFlipGet(cap->act);
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�t�B�����W��ݒ�
 *
 *	@param	cap		�A�N�^�[
 *	@param	x		X���W
 *	@param	y		Y���W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectAffinePosSetCap(CATS_ACT_PTR cap, s16 x, s16 y)
{
	VecFx32	matrix;

	matrix.x = x << FX32_SHIFT;
	matrix.y = y << FX32_SHIFT;
	matrix.z = 0;

	CLACT_SetAffineMatrix( cap->act, &matrix );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�t�B���ϊ����W���擾
 *
 *	@param	cap		�A�N�^�[
 *	@param	x		x���W�i�[��
 *	@param	y		y���W�i�[��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectAffinePosGetCap(CATS_ACT_PTR cap, s16 *x, s16 *y)
{
	const VecFx32* cp_matrix;

	cp_matrix = CLACT_GetAffineMatrix( cap->act );
	*x = cp_matrix->x >> FX32_SHIFT;
	*y = cp_matrix->y >> FX32_SHIFT;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�t�B���ϊ����W�𓮂���
 *
 *	@param	cap		�A�N�^�[
 *	@param	x		������x�l
 *	@param	y		������y�l
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CATS_ObjectAffinePosMoveCap(CATS_ACT_PTR cap, s16 x, s16 y)
{
	const VecFx32* cp_matrix;
	VecFx32 matrix;
	
	cp_matrix = CLACT_GetAffineMatrix( cap->act );
	matrix = *cp_matrix;

	matrix.x += x << FX32_SHIFT;
	matrix.y += y << FX32_SHIFT;

	CLACT_SetAffineMatrix( cap->act, &matrix );
}


//--------------------------------------------------------------
/**
 * @brief	���U�C�N�ݒ�
 *
 * @param	cap	
 * @param	flag	TRUE = ON
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CATS_ObjectMosaicSet(CATS_ACT_PTR cap, BOOL flag)
{
	CLACT_MosaicSet(cap->act, flag);
}

//--------------------------------------------------------------
/**
 * @brief	OBJ���[�h�ݒ�
 *
 * @param	act		OBJ
 * @param	objmode	OBJ���[�h
 *
 * @return	none
 *
 * objmode
 *	GX_OAM_MODE_NORMAL		�m�[�}��OBJ 
 * 	GX_OAM_MODE_XLU			������OBJ 
 *	GX_OAM_MODE_OBJWND		OBJ�E�B���h�E 
 *	GX_OAM_MODE_BITMAPOBJ	�r�b�g�}�b�vOBJ 
 *
 */
//--------------------------------------------------------------
void CATS_ObjectObjModeSet(CLACT_WORK_PTR act, GXOamMode objmode)
{
	CLACT_ObjModeSet( act, objmode );
}

//--------------------------------------------------------------
/**
 * @brief	OBJ���[�h�ݒ�
 *
 * @param	cap		
 * @param	objmode	OBJ���[�h
 *
 * @return	none
 *
 * objmode
 *	GX_OAM_MODE_NORMAL		�m�[�}��OBJ 
 * 	GX_OAM_MODE_XLU			������OBJ 
 *	GX_OAM_MODE_OBJWND		OBJ�E�B���h�E 
 *	GX_OAM_MODE_BITMAPOBJ	�r�b�g�}�b�vOBJ 
 *
 */
//--------------------------------------------------------------
void CATS_ObjectObjModeSetCap(CATS_ACT_PTR cap, GXOamMode objmode)
{
	CATS_ObjectObjModeSet( cap->act, objmode );
}

//--------------------------------------------------------------
/**
 * @brief	OBJ���[�h�擾
 *
 * @param	act					OBJ
 *
 *	@retval	GX_OAM_MODE_NORMAL		�m�[�}��OBJ 
 *	@retval	GX_OAM_MODE_XLU			������OBJ 
 *	@retval	GX_OAM_MODE_OBJWND		OBJ�E�B���h�E 
 *	@retval	GX_OAM_MODE_BITMAPOBJ	�r�b�g�}�b�vOBJ 
 *
 *	OBJ���[�h��GX_OAM_MODE_NORMAL�̎���NitroCharacter�Őݒ肵��
 *	OBJ���[�h�ŕ`�悳��܂��B
 *
 */
//--------------------------------------------------------------
GXOamMode CATS_ObjectObjModeGet(CLACT_WORK_PTR act)
{
	return CLACT_ObjModeGet( act );
}

//--------------------------------------------------------------
/**
 * @brief	OBJ���[�h�擾
 *
 * @param	cap
 *
 *	@retval	GX_OAM_MODE_NORMAL		�m�[�}��OBJ 
 *	@retval	GX_OAM_MODE_XLU			������OBJ 
 *	@retval	GX_OAM_MODE_OBJWND		OBJ�E�B���h�E 
 *	@retval	GX_OAM_MODE_BITMAPOBJ	�r�b�g�}�b�vOBJ 
 *
 *	OBJ���[�h��GX_OAM_MODE_NORMAL�̎���NitroCharacter�Őݒ肵��
 *	OBJ���[�h�ŕ`�悳��܂��B
 *
 */
//--------------------------------------------------------------
GXOamMode CATS_ObjectObjModeGetCap(CATS_ACT_PTR cap)
{
	return CATS_ObjectObjModeGet( cap->act );
}




//--------------------------------------------------------------
/**
 * @brief	�L�����̓o�^	�A�[�J�C�u
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				�A�[�J�C�uIndex
 * @param	data_id				�f�[�^Index
 * @param	comp				���k�t���O
 * @param	id					�Ǘ�ID
 *
 * @retval	BOOL	
 *
 *	�}�b�s���O���[�h�����̏�ԂɕύX����
 */
//--------------------------------------------------------------
BOOL CATS_LoadResourceCharArcModeAdjust(
		CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int trans_mode, int id)
{
	CLACT_U_RES_OBJ_PTR obj;

	if (CLACT_U_ResManagerCheckID(crp->resManager[0], id) == FALSE){
		return FALSE;
	}
	
	obj = CLACT_U_ResManagerResAddArcChar(crp->resManager[0], arc_id, data_id, comp, id, trans_mode, csp->heap_area);

	if (obj != NULL){
//		CLACT_U_CharManagerSetAreaCont(obj);
//		CLACT_U_CharManagerSetCharModeAdjustAreaCont( obj );
		CLACT_U_CharManagerSetCharModeAdjust( obj );
//		CLACT_U_CharManagerSetCharModeAdjustAreaCont( obj );
		
		CATS_LoadResourceTable_Private(crp->resObjTbl[0], obj);	
		
		return TRUE;
	}
	
	GF_ASSERT(0);
	
	return obj == NULL ? FALSE : TRUE;
}

BOOL CATS_LoadResourceCharArcModeAdjustAreaCont(
		CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int trans_mode, int id)
{
	CLACT_U_RES_OBJ_PTR obj;

	if (CLACT_U_ResManagerCheckID(crp->resManager[0], id) == FALSE){
		return FALSE;
	}
	
	obj = CLACT_U_ResManagerResAddArcChar(crp->resManager[0], arc_id, data_id, comp, id, trans_mode, csp->heap_area);

	if (obj != NULL){
//		CLACT_U_CharManagerSetAreaCont(obj);
//		CLACT_U_CharManagerSetCharModeAdjustAreaCont( obj );
		CLACT_U_CharManagerSetCharModeAdjustAreaCont( obj );
		
		CATS_LoadResourceTable_Private(crp->resObjTbl[0], obj);	
		
		return TRUE;
	}
	
	GF_ASSERT(0);
	
	return obj == NULL ? FALSE : TRUE;
}

//--------------------------------------------------------------
/**
 * @brief	�L�����̃��[�\�[�X��ύX����	�A�[�J�C�u
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				�A�[�J�C�uIndex
 * @param	data_id				�f�[�^Index
 * @param	comp				���k�t���O
 * @param	id					�Ǘ�ID
 *
 * @retval	BOOL	
 */
//--------------------------------------------------------------
void CATS_ChangeResourceCharArc(
		CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int id )
{
	CLACT_U_RES_OBJ_PTR	obj;
	
	obj = CLACT_U_ResManagerGetIDResObjPtr( crp->resManager[0], id );

	CLACT_U_ResManagerResChgArcChar(
		crp->resManager[0], obj, arc_id, data_id, comp, csp->heap_area );

	CLACT_U_CharManagerReTrans( obj );
}


//--------------------------------------------------------------
/**
 * @brief	�p���b�g�̃��[�\�[�X��ύX����	�A�[�J�C�u
 *
 * @param	csp	
 * @param	crp	
 * @param	arc_id				�A�[�J�C�uIndex
 * @param	data_id				�f�[�^Index
 * @param	comp				���k�t���O
 * @param	id					�Ǘ�ID
 *
 * @retval	BOOL	
 */
//--------------------------------------------------------------
void CATS_ChangeResourcePlttArc(
		CATS_SYS_PTR csp, CATS_RES_PTR crp, int arc_id, int data_id, BOOL comp, int id )
{
	CLACT_U_RES_OBJ_PTR	obj;
	
	obj = CLACT_U_ResManagerGetIDResObjPtr( crp->resManager[1], id );

	CLACT_U_ResManagerResChgArcPltt(
		crp->resManager[1], obj, arc_id, data_id, comp, csp->heap_area );

	CLACT_U_PlttManagerReTrans( obj );
}

//--------------------------------------------------------------
/**
 * @brief	CLACT_SET_PTR���擾����
 *
 * @param	crp					���\�[�X�|�C���^
 *
 * @retval	CLACT_SET_PTR
 */
//--------------------------------------------------------------
CLACT_SET_PTR CATS_GetClactSetPtr(CATS_RES_PTR crp)
{
	return crp->ca_sp;
}


#if 0
// =============================================================================
//
//
//	���摜�ϊ�
//
//
// =============================================================================
#include "system/arc_tool.h"

static void CharCopy1(const u8* src, u8* dst, int* ofs, int* bofs, int cs, int len);

//--------------------------------------------------------------
/**
 * @brief	2D��1D��1�L�����ϊ�
 *
 * @param	src			���f�[�^
 * @param	dst			�W�J��
 * @param	ofs			���f�[�^�̃R�s�[�J�n�ʒu
 * @param	bofs		�W�J��o�b�t�@�̏������݈ʒu
 * @param	cs			�R�s�[�T�C�Y
 * @param	len			2D�f�[�^�̕�
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void CharCopy1(const u8* src, u8* dst, int* ofs, int* bofs, int cs, int len)
{
	int i;
	u32 dat;
	
	for (i = 0; i < 8; i++){
		memcpy(&dst[ *bofs ], &src[ *ofs ], cs);
		*ofs  += len;
		*bofs += cs;
	}
}


//--------------------------------------------------------------
/**
 * @brief	2D��1D�ɕϊ�����
 *
 * @param	arc_id				�A�[�J�C�u�C���f�b�N�X
 * @param	index_no			�t�@�C���C���f�b�N�X
 * @param	heap_id				�q�[�vID
 * @param	x					�ϊ��Ώۋ�`:x
 * @param	y					�ϊ��Ώۋ�`:y
 * @param	w					�ϊ��Ώۋ�`:w
 * @param	h					�ϊ��Ώۋ�`:h
 * @param	buff				�W�J��o�b�t�@
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ChangesInto_1D_from_2D(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff)
{
	void* aw = NULL;
	u8* p_data = NULL;
	u8* p_buff = NULL;
	NNSG2dCharacterData* ch_data = NULL;

	int size;
	int cs;
	int ofs;
	int bofs;
	int len;
	BOOL res;
	
	///< �f�[�^�̓W�J
	aw = ArchiveDataLoadMalloc(arc_id, index_no, heap_id);
	
	GF_ASSERT(aw != NULL);
	
	///< �L�����f�[�^�̎擾
	res = NNS_G2dGetUnpackedCharacterData(aw, &ch_data);
	
	GF_ASSERT(res != FALSE);

	GF_ASSERT(ch_data->W >= (x + w));		///< �T�C�Y�`�F�b�N
	GF_ASSERT(ch_data->H >= (y + h));
	
	///< ����
	cs     = (sizeof(u8) * 4);				///< �R�s�[�T�C�Y 8dot = 4Byte
	p_data = ch_data->pRawData;				///< �L�����f�[�^
	p_buff = (u8*)buff;						///< �W�J�o�b�t�@
	
	len = (ch_data->W * cs);				///< ����(���摜�̕�)
	ofs = (x * cs) + (y * len);				///< �J�n�ʒu
	bofs = 0;								///< �o�b�t�@�̏������݈ʒu
	
	//�S�̺�߰
	{
		int i;
		int j;

		for (j = y; j < (y + h); j++){
			for (i = x; i < (x + w); i++){
				ofs = (i * cs) + (j * len * CHAR_DOT_Y);			///< �J�n�ʒu
				CharCopy1(p_data, p_buff, &ofs, &bofs, cs, len);	///< 1�L�����R�s�[
			}
		}
	}
	
	sys_FreeMemoryEz(aw);
}


//--------------------------------------------------------------
/**
 * @brief	2D��1D�ɕϊ�����
 *
 * @param	arc_id				�A�[�J�C�u�C���f�b�N�X
 * @param	index_no			�t�@�C���C���f�b�N�X
 * @param	heap_id				�q�[�vID
 * @param	rc					��`
 * @param	buff				�o�b�t�@
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  ChangesInto_1D_from_2D_RC(int arc_id, int index_no, int heap_id, CHANGES_INTO_DATA_RECT* rc, void* buff)
{
	ChangesInto_1D_from_2D(arc_id, index_no, heap_id, rc->x, rc->y, rc->h, rc->w, buff);
}


//--------------------------------------------------------------
/**
 * @brief	2D��1D�ɓW�J�o�b�t�@��Alloc���ĕϊ�����
 *
 * @param	arc_id				�A�[�J�C�u�C���f�b�N�X
 * @param	index_no			�t�@�C���C���f�b�N�X
 * @param	heap_id				�q�[�vID
 * @param	x					�ϊ��Ώۋ�`:x
 * @param	y					�ϊ��Ώۋ�`:y
 * @param	w					�ϊ��Ώۋ�`:w
 * @param	h					�ϊ��Ώۋ�`:h
 *
 * @retval	void*				�W�J�����o�b�t�@�̃|�C���^
 *
 */
//--------------------------------------------------------------
void* ChangesInto_1D_from_2D_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h)
{
	void* buff;
	
	int size;
	
	size = ((w-x)*(h-y)*CHAR_BYTE);
	
	buff = sys_AllocMemory(heap_id, size);
	
	ChangesInto_1D_from_2D(arc_id, index_no, heap_id, x, y, w, h, buff);
	
	return buff;	
}


//--------------------------------------------------------------
/**
 * @brief	2D��1D�ɓW�J�o�b�t�@��Alloc���ĕϊ�����
 *
 * @param	arc_id				�A�[�J�C�u�C���f�b�N�X
 * @param	index_no			�t�@�C���C���f�b�N�X
 * @param	heap_id				�q�[�vID
 * @param	rc					��`
 *
 * @retval	void*				�W�J�����o�b�t�@�̃|�C���^
 *
 */
//--------------------------------------------------------------
void* ChangesInto_1D_from_2D_Alloc_RC(int arc_id, int index_no, int heap_id, CHANGES_INTO_DATA_RECT* rc)
{
	return ChangesInto_1D_from_2D_Alloc(arc_id, index_no, heap_id, rc->x, rc->y, rc->w, rc->h);
}


//--------------------------------------------------------------
/**
 * @brief	1D��OAM�`��ɕϊ�
 *
 * @param	sx				�ϊ��Ώۃf�[�^�̃T�C�Y X	
 * @param	sy				�ϊ��Ώۃf�[�^�̃T�C�Y Y
 * @param	x				�؂蔲���J�n X
 * @param	y				�؂蔲���J�n Y
 * @param	w				�؂蔲���T�C�Y W
 * @param	h				�؂蔲���T�C�Y H
 * @param	bofs			�I�t�Z�b�g
 * @param	src				���f�[�^
 * @param	dst				�W�J��
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ChangesInto_OAM_from_1D(int sx, int sy, int x, int y, int w, int h, int* bofs, const void* src, void* dst)
{
	int i, j;
	u8* p_data;
	u8* p_buff;
	int ofs;
	
	int lx;
	int ly;
	
	p_data = (u8*)src;
	p_buff = (u8*)dst;
	
	lx = x + w;
	ly = y + h;

	for (j = y; j < ly; j++){
		for (i = x; i < lx; i++){
			ofs = (i * CHAR_BYTE) + (j * CHAR_BYTE * sx);
			memcpy(&p_buff[ *bofs ], &p_data[ ofs ], CHAR_BYTE);
			*bofs += CHAR_BYTE;
		}
	}
}


//--------------------------------------------------------------
/**
 * @brief	1D��OAM�`��ɕϊ� ��`�ŃT�C�Y�w��
 *
 * @param	sx				�ϊ��Ώۃf�[�^�̃T�C�Y X	
 * @param	sy				�ϊ��Ώۃf�[�^�̃T�C�Y Y
 * @param	rc				��`
 * @param	bofs			�I�t�Z�b�g
 * @param	src				�f�[�^
 * @param	dst				�W�J��
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  ChangesInto_OAM_from_1D_RC(int sx, int sy, CHANGES_INTO_DATA_RECT* rc, int* bofs, const void* src, void* dst)
{
	ChangesInto_OAM_from_1D(sx, sy, rc->x, rc->y, rc->w, rc->h, bofs, src, dst);
}


//--------------------------------------------------------------
/**
 * @brief	�|�P�����̃f�[�^��2D��1D��OAM�ɕϊ�
 *
 * @param	arc_id			�A�[�J�C�uID
 * @param	index_no		�C���f�b�N�X�ԍ�
 * @param	heap_id			�q�[�vID
 * @param	x
 * @param	y
 * @param	w
 * @param	h
 * @param	buff			�W�J��o�b�t�@
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ChangesInto_OAM_from_PokeTex(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff)
{
	int i;
	int num;
	int ofs;
	void* temp = NULL;
	
	CHANGES_INTO_DATA_RECT rc[] = {
		{ 0, 0, 8, 8 },
		{ 8, 0, 2, 4 },
		{ 8, 4, 2, 4 },
		{ 0, 8, 4, 2 },
		{ 4, 8, 4, 2 },
		{ 8, 8, 2, 2 },
	};
	
	num = NELEMS(rc);
	ofs = 0;
	
	temp = ChangesInto_1D_from_2D_Alloc(arc_id, index_no, heap_id, x, y, w, h);		///< 1D����2D�֕ϊ�

	for (i = 0; i < num; i++){
		ChangesInto_OAM_from_1D_RC(w, h, &rc[i], &ofs, temp, buff);
	}
	
	sys_FreeMemoryEz(temp);
}


//--------------------------------------------------------------
/**
 * @brief	�|�P�����̃f�[�^��2D��1D��OAM�ɕϊ�
 *
 * @param	arc_id			�A�[�J�C�uID
 * @param	index_no		�C���f�b�N�X�ԍ�
 * @param	heap_id			�q�[�vID
 * @param	rc				��`
 * @param	buff			�o�b�t�@
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  ChangesInto_OAM_from_PokeTex_RC(int arc_id, int index_no, int heap_id, CHANGES_INTO_DATA_RECT* rc, void* buff)
{
	ChangesInto_OAM_from_PokeTex(arc_id, index_no, heap_id, rc->x, rc->y, rc->w, rc->h, buff);
}


//--------------------------------------------------------------
/**
 * @brief	�|�P�����̃f�[�^��2D��1D��OAM�ɕϊ�
 *
 * @param	arc_id			�A�[�J�C�uID
 * @param	index_no		�C���f�b�N�X�ԍ�
 * @param	heap_id			�q�[�vID
 * @param	x
 * @param	y
 * @param	w
 * @param	h
 *
 * @retval	void*	
 *
 */
//--------------------------------------------------------------
void* ChangesInto_OAM_from_PokeTex_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h)
{
	void* buff = NULL;
	
	int size;
	
	size = ((w-x)*(h-y)*CHAR_BYTE);

	buff = sys_AllocMemory(heap_id, size);
	
	ChangesInto_OAM_from_PokeTex(arc_id, index_no, heap_id, x, y, w, h, buff);
	
	return buff;
}


//--------------------------------------------------------------
/**
 * @brief	�|�P�����̃f�[�^��2D��1D��OAM�ɕϊ�
 *
 * @param	arc_id			�A�[�J�C�uID
 * @param	index_no		�C���f�b�N�X�ԍ�
 * @param	heap_id			�q�[�vID
 * @param	rc				��`
 *
 * @retval	void*	
 *
 */
//--------------------------------------------------------------
void* ChangesInto_OAM_from_PokeTex_Alloc_RC(int arc_id, int index_no, int heap_id, CHANGES_INTO_DATA_RECT* rc)
{
	return ChangesInto_OAM_from_PokeTex_Alloc(arc_id, index_no, heap_id, rc->x, rc->y, rc->w, rc->h);
}


//--------------------------------------------------------------
/**
 * @brief	�|�P�����f�[�^��퓬�p�ɕϊ�
 *
 * @param	arc_id	
 * @param	index_no	
 * @param	heap_id	
 * @param	buff	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  ChangesInto_BattlePokeData(int arc_id, int index_no, int heap_id, void* buff)
{
	CHANGES_INTO_DATA_RECT rc = {
		POKE_TEX_SX,
		POKE_TEX_SY,
		POKE_TEX_EX,
		POKE_TEX_EY
	};
	
	ChangesInto_OAM_from_PokeTex_RC(arc_id, index_no, heap_id, &rc, buff);
}


//--------------------------------------------------------------
/**
 * @brief	�|�P�����f�[�^��퓬�p�ɕϊ�
 *
 * @param	arc_id	
 * @param	index_no	
 * @param	heap_id	
 *
 * @retval	void*	
 *
 */
//--------------------------------------------------------------
void* ChangesInto_BattlePokeData_Alloc(int arc_id, int index_no, int heap_id)
{
	void* buff = NULL;
	
	int size;
	
	size = POKE_TEX_SIZE;
	
	buff = sys_AllocMemory(heap_id, size);
	
	ChangesInto_BattlePokeData(arc_id, index_no, heap_id, buff);
	
	return buff;	
}
#endif
