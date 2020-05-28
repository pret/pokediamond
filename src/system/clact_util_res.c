//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		clact_util_res.c
 *@brief	�Z���A�N�^�[���[�e�B���e�B�V�X�e��
 *@author	tomoya takahashi	
 *@data		2005.09.01
 *
 *
 * ���̃V�X�e���́ACLACT���ȒP�Ɏg�p�ł���悤���\�[�X���Ǘ�����
 * �V�X�e�����܂Ƃ߂����ł��B
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "res_manager.h"
#include "include/system/arc_tool.h"
#include "include/system/arc_util.h"

#define __CLACT_UTIL_H_RES_GLOBAL
#include "include/system/clact_util_res.h"


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
//	
//	�Z���A�N�^�[���\�[�X�}�l�[�W��
//	�I�u�W�F
//	
//=====================================
typedef struct _CLACT_U_RES_OBJ{
	RES_OBJ_PTR		res_obj;		// ���\�[�X�I�u�W�F
	int				type;			// ���\�[�X�^�C�v
	void*			res_ex;			// �g���f�[�^	(�A���p�b�N��̃f�[�^���i�[������A
									// ���ꂼ��̃��\�[�X�ɈႤ�f�[�^���i�[)
} CLACT_U_RES_OBJ;

//-------------------------------------
//	
//	���\�[�X�}�l�[�W���[�Ǘ��\����
//	
//=====================================
typedef struct _CLACT_U_RES_MANAGER{
	RES_MANAGER_PTR res_manager;	// �g�p���郊�\�[�X�}�l�[�W���[
	CLACT_U_RES_OBJ*	resObj;		// ���\�[�X�I�u�W�F�N�g
	int					tbl_num;	// �e�[�u����
	int					tbl_now;	// ���̓o�^��
	int					type;		// ���\�[�X�^�C�v
} CLACT_U_RES_MANAGER;

//-------------------------------------
//	
//	�f�[�^�Ǘ��w�b�_�[
//	
//=====================================
typedef struct _CLACT_U_RES_HEADER_SUB{
	int		id;
	char	file_path[64];
	int		ex[2];			// �g���f�[�^
} CLACT_U_RES_HEADER_SUB;

//-------------------------------------
//	
//	�A�[�J�C�u�f�[�^�Ǘ��w�b�_�[
//	
//=====================================
typedef struct _CLACT_U_RES_HEADER_SUBARC{
	int		arcFile;		// �A�[�J�C�u�t�@�C��ID
	int		dataIdx;		// �f�[�^idx
	BOOL	compFlag;		// ���k�t���O
	int		id;
	int		ex[2];			// �g���f�[�^
} CLACT_U_RES_HEADER_SUBARC;

//-------------------------------------
//	
//	���\�[�X�}�l�[�W���[�w�b�_�[�\����
//	
//=====================================
typedef struct _CLACT_U_RES_HEADER{
	void*			tbl;			// �w�b�_�[�e�[�u��
	int				tbl_num;		// �e�[�u����
	int				type;			// ���\�[�X�^�C�v
	u8				arc_flag;		// �A�[�J�C�u���ꂽ�f�[�^��
} CLACT_U_RES_HEADER;

//-----------------------------------------------
//
//	�X�̊g���f�[�^
//
//==============================================
//-------------------------------------
//	
//	�L�����N�^
//	
//=====================================
typedef struct {
	NNSG2dCharacterData* pCharData;		// �L�����N�^�f�[�^
	int	vram_type;						// Vram�^�C�v
} CLACT_U_RES_EX_CHAR;

//-------------------------------------
//	
//	�p���b�g
//	
//=====================================
typedef struct {
	NNSG2dPaletteData* pPlttData;		// �p���b�g�f�[�^
	int	vram_type;						// Vram�^�C�v
	int	pltt_num;						// �p���b�g�i���o�[
} CLACT_U_RES_EX_PLTT;

//-------------------------------------
//	
//	�Z��
//	
//=====================================
typedef struct {
	NNSG2dCellDataBank* pCellData;		// �Z���f�[�^
} CLACT_U_RES_EX_CELL;

//-------------------------------------
//	
//	�Z���A�j��
//	
//=====================================
typedef struct {
	NNSG2dAnimBankData* pCellANMData;	// �Z���A�j���f�[�^
} CLACT_U_RES_EX_CELLANM;

//-------------------------------------
//	
//	�}���`�Z��
//	
//=====================================
typedef struct {
	NNSG2dMultiCellDataBank* pMultiData;	// �}���`�Z���f�[�^
} CLACT_U_RES_EX_MULTI;

//-------------------------------------
//	
//	�}���`�Z���A�j��
//	
//=====================================
typedef struct {
	NNSG2dAnimBankData* pMultiANMData;		// �}���`�Z���A�j���f�[�^
} CLACT_U_RES_EX_MULTIANM;
//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//	�e�[�u���p
static CLACT_U_RES_OBJ_PTR getCleanResObj(CLACT_U_RES_MANAGER_PTR resm);
static void loadOneData(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, const char* path, int id, int vram, int pltt_num, int type, int heap);
static void SetArcOneData(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int type, int heap, u32 alloc_type);
static void SetArcOneData_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int type, int heap, u32 alloc_type);
static void* ArcHandle_Load(ARCHANDLE* p_handle, u32 dataIdx, BOOL compressedFlag, u32 heapID, u32 alloc_type);


// ���ꂼ��̊g���f�[�^�쐬
static void makeExData(CLACT_U_RES_OBJ_PTR resObj, int type, int vram_type, int pltt_num, int heap);
static CLACT_U_RES_EX_CHAR* makeExChar(void* res, int vram_type, int heap);
static CLACT_U_RES_EX_PLTT* makeExPltt(void* res, int vram_type, int pltt_num, int heap);
static CLACT_U_RES_EX_CELL* makeExCell(void* res, int heap);
static CLACT_U_RES_EX_CELLANM*	makeExCellAnm(void* res, int heap);
static CLACT_U_RES_EX_MULTI*	makeExMulti(void* res, int heap);
static CLACT_U_RES_EX_MULTIANM* makeExMultiAnm(void* res, int heap);

static void* getExData( CONST_CLACT_U_RES_OBJ_PTR resObj );


// ���ꂼ��̊g���f�[�^�j��
static void delExData(CLACT_U_RES_OBJ_PTR resObj);


// �w�b�_�[�ǂݍ��݂悤
static int getHeaderType(char* buff);
static int getHeaderArc(char* buff);

static int getHeaderNum(char* buff, int type, int arcFlag);
static int getHeaderNumBinary( const CLACT_U_RES_HEADER_SUBARC* buff );
static void loadHeaderData(char* buff, int type, void* tbl, int num, int arcFlag);

static void loadHeaderCore(char* buff, char** file_path, char** id, char** vram, char** pltt, int type);
static void loadCharHeaderCore(char* buff, char** path, char** id, char** type);
static void loadPlttHeaderCore(char* buff, char** path, char** id, char** type, char** pltt_num);
static void loadKindCellHeaderCore(char* buff, char** path, char** id);
static void setDataHeader(CLACT_U_RES_HEADER_SUB* head, char* path, char* id, char* type, char* pltt_num);

static void loadHeaderCoreArc(char* buff, char** srcFile, char** dataIdx, char** compFlag, char** id, char** vram, char** pltt, int type);
static void loadCharHeaderCoreArc(char* buff, char** srcFile, char** dataIdx, char** compFlag, char** id, char** type);
static void loadPlttHeaderCoreArc(char* buff, char** srcFile, char** dataIdx, char** compFlag, char** id, char** type, char** pltt_num);
static void loadKindCellHeaderCoreArc(char* buff, char** srcFile, char** dataIdx, char** compFlag, char** id);
static void setDataHeaderArc(CLACT_U_RES_HEADER_SUBARC* head, char* arcFile, char* dataIdx, char* compFlag, char* id, char* type, char* pltt_num);

static char* makeCopyStr(const char* buff, int heap);
static void delCopyStr(char* copy);


//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�Ǘ��}�l�[�W���[������
 *
 *@param	tbl_num			�f�[�^�o�^��
 *@param	res_type		���\�[�X�^�C�v
 *@param	heap			�g�p����q�[�v
 *
 *@return	CLACT_RES_MANAGER_PTR	�Z���A�N�^�[���[�e�B���e�B���\�[�X�}�l�[�W���[�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_MANAGER_PTR CLACT_U_ResManagerInit(int tbl_num, int res_type, int heap)
{
	CLACT_U_RES_MANAGER_PTR	resm;
	int	i;	// ���[�v�p
	

	// ���\�[�X�Ǘ��f�[�^�i�[����쐬
	resm = sys_AllocMemory(heap, sizeof(CLACT_U_RES_MANAGER));
	
	// ���\�[�X�}�l�[�W���[�쐬
	resm->res_manager = RESM_Init(tbl_num, heap);

	// �I�u�W�F�o�^�e�[�u���쐬
	resm->resObj = sys_AllocMemory(heap, sizeof(CLACT_U_RES_OBJ)*tbl_num);
	memset(resm->resObj, 0, sizeof(CLACT_U_RES_OBJ)*tbl_num);
	
	resm->tbl_num = tbl_num;
	resm->tbl_now = 0;
	
	// ���\�[�X�^�C�v���
	resm->type	= res_type;
	
	return resm;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�}�l�[�W���[�̔j��
 *
 *@param	resm	���\�[�X�}�l�[�W���[
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerDelete(CLACT_U_RES_MANAGER_PTR resm)
{
	GF_ASSERT(resm);
	GF_ASSERT(resm->res_manager);
	GF_ASSERT(resm->resObj);
	
	// �o�^����Ă���f�[�^��S�Ĕj��
	CLACT_U_ResManagerResDeleteAll(resm);
	
	// �m�ۂ��������������
	// ���\�[�X�}�l�[�W���[�j��
	RESM_Delete(resm->res_manager);
	resm->res_manager = NULL;

	// �I�u�W�F�o�^�e�[�u���쐬
	sys_FreeMemoryEz(resm->resObj);
	resm->resObj = NULL;
	 
	// ���\�[�X�Ǘ��f�[�^�i�[����쐬
	sys_FreeMemoryEz(resm);
	resm = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�f�[�^���w�b�_�[����ǂݍ��ށi�P���j
 *
 *@param	resm	���\�[�X�}�l�[�W���[
 *@param	head	�w�b�_�[
 *@param	no		�w�b�_�[�̉��Ԗڂ�ǂݍ��ނ�
 *@param	heap	�g�p����q�[�v
 *
 *@return	�ǂݍ��񂾃f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddHd(CLACT_U_RES_MANAGER_PTR resm, const CLACT_U_RES_HEADER_PTR head, int no, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;
	CLACT_U_RES_HEADER_SUB*		hs;
	CLACT_U_RES_HEADER_SUBARC*	harc;
	

	GF_ASSERT(resm);
	GF_ASSERT(head);
	GF_ASSERT(head->tbl_num > no);
	GF_ASSERT_MSG(resm->type == head->type, "���\�[�X�^�C�v���Ⴂ�܂�" );
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj,  "�����󂫂̃e�[�u��������܂���" );
	if(head->arc_flag == 0){
		// ��A�[�J�C�u�p�w�b�_
		hs = (CLACT_U_RES_HEADER_SUB*)head->tbl + no;
		GF_ASSERT_MSG( (CLACT_U_ResManagerCheckID(resm, hs->id) == TRUE), "ID���d�����Ă��܂�")
		loadOneData(resm, obj, hs->file_path, hs->id, hs->ex[0], hs->ex[1], head->type, heap);
	}else{
		// �A�[�J�C�u�p�w�b�_
		harc = (CLACT_U_RES_HEADER_SUBARC*)head->tbl + no;
		GF_ASSERT_MSG( (CLACT_U_ResManagerCheckID(resm, harc->id) == TRUE), "ID���d�����Ă��܂�")
		SetArcOneData(resm, obj, harc->arcFile, harc->dataIdx, harc->compFlag, harc->id, harc->ex[0], harc->ex[1], head->type, heap, ALLOC_TOP);
	}
	resm->tbl_now++;

	return obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�f�[�^�̓o�^
 *
 *@param	resm			�L�����N�^�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	path			�t�@�C���p�X
 *@param	id				�Ǘ��h�c
 *@param	vram			�u�������^�C�v(NNS_G2D_VRAM_TYPE_2DMAIN,NNS_G2D_VRAM_TYPE_2DSUB,NNS_G2D_VRAM_TYPE_2DMAX)
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddChar(CLACT_U_RES_MANAGER_PTR resm, const char* path, int id, int vram, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG((resm->type == CLACT_U_CHAR_RES), "���\�[�X�^�C�v���Ⴂ�܂�");
	GF_ASSERT_MSG( CLACT_U_ResManagerCheckID(resm, id) == TRUE, "ID���d�����Ă��܂�")
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "�����󂫂̃e�[�u��������܂���");
	loadOneData(resm, obj, path, id, vram, 0, CLACT_U_CHAR_RES, heap);
	resm->tbl_now++;

	return obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^�̓o�^
 *
 *@param	resm			�p���b�g�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	path			�t�@�C���p�X
 *@param	id				�Ǘ��h�c
 *@param	vram			�u�������^�C�v(NNS_G2D_VRAM_TYPE_2DMAIN,NNS_G2D_VRAM_TYPE_2DSUB,NNS_G2D_VRAM_TYPE_2DMAX)
 *@param	pltt_num		�K�v�ȃp���b�g�i���o�[
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddPltt(CLACT_U_RES_MANAGER_PTR resm, const char* path, int id, int vram, int pltt_num, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_PLTT_RES , "���\�[�X�^�C�v���Ⴂ�܂�");
	GF_ASSERT_MSG( CLACT_U_ResManagerCheckID(resm, id) == TRUE, "ID���d�����Ă��܂�")
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "�����󂫂̃e�[�u��������܂���");
	loadOneData(resm, obj, path, id, vram, pltt_num, CLACT_U_PLTT_RES, heap);
	resm->tbl_now++;

	return obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�Z���A�j���A�}���`�Z���A�}���`�Z���A�j���f�[�^�̓o�^
 *
 *@param	resm			�p���b�g�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	path			�t�@�C���p�X
 *@param	id				�Ǘ��h�c
 *@param	type			���\�[�X�^�C�v
 *@param	heap			�g�p�q�[�v
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddKindCell(CLACT_U_RES_MANAGER_PTR resm, const char* path, int id, int type, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG( CLACT_U_ResManagerCheckID(resm, id) == TRUE , "ID���d�����Ă��܂�");
	GF_ASSERT(type == resm->type);
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "�����󂫂̃e�[�u��������܂���");
	loadOneData(resm, obj, path, id, 0, 0, type, heap);
	resm->tbl_now++;
	
	return obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�A�[�J�C�u���ꂽ�L�����N�^�f�[�^�̓o�^
 *
 *@param	resm			�L�����N�^�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	arcFile			�A�[�J�C�u�t�@�C��ID
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩
 *@param	id				�Ǘ��h�c
 *@param	vram			�u�������^�C�v(NNS_G2D_VRAM_TYPE_2DMAIN,NNS_G2D_VRAM_TYPE_2DSUB,NNS_G2D_VRAM_TYPE_2DMAX)
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcChar(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_CHAR_RES, "���\�[�X�^�C�v���Ⴂ�܂�");
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "�����󂫂̃e�[�u��������܂���");
	SetArcOneData(resm, obj, arcFile, dataIdx, compFlag, id, vram, 0, CLACT_U_CHAR_RES, heap, ALLOC_TOP);

	resm->tbl_now++;

	return obj;
}
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcChar_AllocType(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int heap, ALLOC_TYPE alloc_type)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_CHAR_RES, "���\�[�X�^�C�v���Ⴂ�܂�");
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "�����󂫂̃e�[�u��������܂���");
	SetArcOneData(resm, obj, arcFile, dataIdx, compFlag, id, vram, 0, CLACT_U_CHAR_RES, heap, alloc_type);

	resm->tbl_now++;

	return obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^�̓o�^
 *
 *@param	resm			�p���b�g�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	arcFile			�A�[�J�C�u�t�@�C��ID
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩
 *@param	id				�Ǘ��h�c
 *@param	vram			�u�������^�C�v(NNS_G2D_VRAM_TYPE_2DMAIN,NNS_G2D_VRAM_TYPE_2DSUB,NNS_G2D_VRAM_TYPE_2DMAX)
 *@param	pltt_num		�K�v�ȃp���b�g�̖{���i�P�{���P�U�F)
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcPltt(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_PLTT_RES, "���\�[�X�^�C�v���Ⴂ�܂�");
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "�����󂫂̃e�[�u��������܂���");
	SetArcOneData(resm, obj, arcFile, dataIdx, compFlag, id, vram, pltt_num, CLACT_U_PLTT_RES, heap, ALLOC_TOP);

	resm->tbl_now++;
	return obj;
}
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcPltt_AllocType(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int heap, ALLOC_TYPE alloc_type)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_PLTT_RES, "���\�[�X�^�C�v���Ⴂ�܂�");
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "�����󂫂̃e�[�u��������܂���");
	SetArcOneData(resm, obj, arcFile, dataIdx, compFlag, id, vram, pltt_num, CLACT_U_PLTT_RES, heap, alloc_type);

	resm->tbl_now++;
	return obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�Z���A�j���A�}���`�Z���A�}���`�Z���A�j���f�[�^�̓o�^
 *
 *@param	resm			�p���b�g�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	arcFile			�A�[�J�C�u�t�@�C��ID
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩
 *@param	id				�Ǘ��h�c
 *@param	type			���\�[�X�^�C�v(CLACT_U_CELL_RES��CLACT_U_CELLANM_RES)
 *@param	heap			�g�p�q�[�v
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcKindCell(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int type, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "�����󂫂̃e�[�u��������܂���");
	SetArcOneData(resm, obj, arcFile, dataIdx, compFlag, id, 0, 0, type, heap, ALLOC_TOP);

	resm->tbl_now++;
	return obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�A�[�J�C�u���ꂽ�L�����N�^�f�[�^�̃��\�[�X�ύX
 *
 *@param	resm			�L�����N�^�p���\�[�X�}�l�[�W���|�C���^
 *@param	resObj			�ύX���郊�\�[�X�I�u�W�F
 *@param	arcFile			�A�[�J�C�u�t�@�C��ID
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩
 *
 * @return none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResChgArcChar(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int arcFile, int dataIdx, BOOL compFlag, int heap)
{
	int vram_type;	// Vram�]����
	int id;			// ID
	
	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_CHAR_RES, "���\�[�X�^�C�v���Ⴂ�܂�");
	GF_ASSERT(resObj);
	GF_ASSERT_MSG(resObj->type == CLACT_U_CHAR_RES, "���\�[�X�^�C�v���Ⴂ�܂�");

	// ���܂ł̃f�[�^�ۑ�
	id = CLACT_U_ResManagerGetResObjID( resObj );
	vram_type =	CLACT_U_ResManagerGetResObjVramType( resObj );
	
	// ���܂ł̃f�[�^�j��
	CLACT_U_ResManagerResDelete( resm, resObj );

	// ���̃f�[�^�e�[�u���ɐV�����f�[�^�ǂݍ���
	SetArcOneData(resm, resObj, arcFile, dataIdx, compFlag, id, vram_type, 0, CLACT_U_CHAR_RES, heap, ALLOC_TOP);
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^�̃��\�[�X��ύX
 *
 *@param	resm			�p���b�g�p���\�[�X�}�l�[�W���|�C���^
 *@param	resObj			�ύX���郊�\�[�X�I�u�W�F
 *@param	arcFile			�A�[�J�C�u�t�@�C��ID
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩
 *@param	heap			�g�p����q�[�v
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResChgArcPltt(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int arcFile, int dataIdx, BOOL compFlag, int heap)
{
	int vram_type;	// Vram�]����
	int pltt_num;	// �p���b�g�]����
	int id;			// ID
	
	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_PLTT_RES, "���\�[�X�^�C�v���Ⴂ�܂�");
	GF_ASSERT(resObj);
	GF_ASSERT_MSG(resObj->type == CLACT_U_PLTT_RES, "���\�[�X�^�C�v���Ⴂ�܂�");

	// ���܂ł̃f�[�^�ۑ�
	id = CLACT_U_ResManagerGetResObjID( resObj );
	vram_type =	CLACT_U_ResManagerGetResObjVramType( resObj );
	pltt_num = CLACT_U_ResManagerGetResObjPlttNum( resObj );
	
	// ���܂ł̃f�[�^�j��
	CLACT_U_ResManagerResDelete( resm, resObj );

	// ���̃f�[�^�e�[�u���ɐV�����f�[�^�ǂݍ���
	SetArcOneData(resm, resObj, arcFile, dataIdx, compFlag, id, vram_type, pltt_num, CLACT_U_PLTT_RES, heap, ALLOC_TOP);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�Z���A�j���A�}���`�Z���A�}���`�Z���A�j���f�[�^�̃��\�[�X��ύX
 *
 *@param	resm			�ύX���郊�\�[�X�p���\�[�X�}�l�[�W���|�C���^
 *@param	resObj			�ύX���郊�\�[�X�I�u�W�F
 *@param	arcFile			�A�[�J�C�u�t�@�C��ID
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩
 *@param	type			���\�[�X�^�C�v
 *@param	heap			�g�p����q�[�v
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResChgArcKindCell(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int arcFile, int dataIdx, BOOL compFlag, int type, int heap)
{
	int id;			// ID
	
	GF_ASSERT(resm);
	GF_ASSERT(resObj);

	// ���܂ł̃f�[�^�ۑ�
	id = CLACT_U_ResManagerGetResObjID( resObj );
	
	// ���܂ł̃f�[�^�j��
	CLACT_U_ResManagerResDelete( resm, resObj );

	// ���̃f�[�^�e�[�u���ɐV�����f�[�^�ǂݍ���
	SetArcOneData(resm, resObj, arcFile, dataIdx, compFlag, id, 0, 0, type, heap, ALLOC_TOP);
}

//----------------------------------------------------------------------------
/**
 * ���A�[�J�C�u�n���h������
 *
 *@brief	�A�[�J�C�u���ꂽ�L�����N�^�f�[�^�̓o�^
 *
 *@param	resm			�L�����N�^�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	arcHandle		�A�[�J�C�u�t�@�C���n���h��
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	id				�Ǘ��h�c		�i�d�����Ȃ��悤�Ƀ��[�U�[���ݒ�j
 *@param	vram			�u�������^�C�v
 *@param	heap			�g�p�q�[�v
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 * Vram�^�C�v
	main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN
	sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB
	�����ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAX
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcChar_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_CHAR_RES, "���\�[�X�^�C�v���Ⴂ�܂�");
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "�����󂫂̃e�[�u��������܂���");
	
	SetArcOneData_ArcHandle(resm, obj, arcHandle, dataIdx, compFlag, id, vram, 0, CLACT_U_CHAR_RES, heap, ALLOC_TOP);

	resm->tbl_now++;

	return obj;
}
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcChar_ArcHandle_AllocType(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int heap, ALLOC_TYPE alloc_type)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_CHAR_RES, "���\�[�X�^�C�v���Ⴂ�܂�");
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "�����󂫂̃e�[�u��������܂���");
	
	SetArcOneData_ArcHandle(resm, obj, arcHandle, dataIdx, compFlag, id, vram, 0, CLACT_U_CHAR_RES, heap, alloc_type);

	resm->tbl_now++;

	return obj;
}

//----------------------------------------------------------------------------
/**
 * ���A�[�J�C�u�n���h������
 *
 *@brief	�p���b�g�f�[�^�̓o�^
 *
 *@param	resm			�p���b�g�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	arcHandle		�A�[�J�C�u�t�@�C���n���h��
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	id				�Ǘ��h�c		�i�d�����Ȃ��悤�Ƀ��[�U�[���ݒ�j
 *@param	vram			�u�������^�C�v
 *@param	pltt_num		�p���b�g�ǂݍ��ݖ{��
 *@param	heap			�g�p�q�[�v
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 * Vram�^�C�v
	main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN
	sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB
	�����ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAX
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcPltt_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_PLTT_RES, "���\�[�X�^�C�v���Ⴂ�܂�");
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "�����󂫂̃e�[�u��������܂���");
	SetArcOneData_ArcHandle(resm, obj, arcHandle, dataIdx, compFlag, id, vram, pltt_num, CLACT_U_PLTT_RES, heap, ALLOC_TOP);

	resm->tbl_now++;
	return obj;
}
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcPltt_ArcHandle_AllocType(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int heap, ALLOC_TYPE alloc_type )
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_PLTT_RES, "���\�[�X�^�C�v���Ⴂ�܂�");
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "�����󂫂̃e�[�u��������܂���");
	SetArcOneData_ArcHandle(resm, obj, arcHandle, dataIdx, compFlag, id, vram, pltt_num, CLACT_U_PLTT_RES, heap, alloc_type);

	resm->tbl_now++;
	return obj;
}

//----------------------------------------------------------------------------
/**
 * ���A�[�J�C�u�n���h������
 *
 *@brief	�Z���A�Z���A�j���A�}���`�Z���A�}���`�Z���A�j���f�[�^�̓o�^
 *
 *@param	resm			�p���b�g�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	arcHandle		�A�[�J�C�u�t�@�C���n���h��
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	id				�Ǘ��h�c		�i�d�����Ȃ��悤�Ƀ��[�U�[���ݒ�j
 *@param	type			���\�[�X�^�C�v
 *@param	heap			�g�p�q�[�v
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 * ���\�[�X�^�C�v
	enum{
		CLACT_U_CHAR_RES,		// �L�����N�^���\�[�X���Ǘ�
		CLACT_U_PLTT_RES,		// �p���b�g���\�[�X���Ǘ�
		CLACT_U_CELL_RES,		// �Z�����\�[�X���Ǘ�
		CLACT_U_CELLANM_RES,	// �Z���A�j�����\�[�X���Ǘ�
		CLACT_U_MULTI_RES,		// �}���`�Z�����\�[�X���Ǘ�
		CLACT_U_MULTIANM_RES,	// �}���`�Z���A�j�����\�[�X���Ǘ�
		CLACT_U_RES_MAX			// �ő�
	};
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcKindCell_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int type, int heap)
{
	CLACT_U_RES_OBJ_PTR obj;

	GF_ASSERT(resm);
	
	obj = getCleanResObj(resm);
	GF_ASSERT_MSG(obj, "�����󂫂̃e�[�u��������܂���");
	SetArcOneData_ArcHandle(resm, obj, arcHandle, dataIdx, compFlag, id, 0, 0, type, heap, ALLOC_TOP);

	resm->tbl_now++;
	return obj;
}

//----------------------------------------------------------------------------
/**
 * ���A�[�J�C�u�n���h������
 *
 *@brief	�A�[�J�C�u���ꂽ�L�����N�^�f�[�^�̃��\�[�X�ύX
 *
 *@param	resm			�L�����N�^�p���\�[�X�}�l�[�W���|�C���^
 *@param	resObj			�ύX���郊�\�[�X�I�u�W�F
 *@param	arcHandle		�A�[�J�C�u�t�@�C���n���h��
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	heap			�g�p�q�[�v
 *
 * @return none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResChgArcChar_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int heap)
{
	int vram_type;	// Vram�]����
	int id;			// ID
	
	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_CHAR_RES, "���\�[�X�^�C�v���Ⴂ�܂�");
	GF_ASSERT(resObj);
	GF_ASSERT_MSG(resObj->type == CLACT_U_CHAR_RES, "���\�[�X�^�C�v���Ⴂ�܂�");

	// ���܂ł̃f�[�^�ۑ�
	id = CLACT_U_ResManagerGetResObjID( resObj );
	vram_type =	CLACT_U_ResManagerGetResObjVramType( resObj );
	
	// ���܂ł̃f�[�^�j��
	CLACT_U_ResManagerResDelete( resm, resObj );

	// ���̃f�[�^�e�[�u���ɐV�����f�[�^�ǂݍ���
	SetArcOneData_ArcHandle(resm, resObj, arcHandle, dataIdx, compFlag, id, vram_type, 0, CLACT_U_CHAR_RES, heap, ALLOC_TOP);
}


//----------------------------------------------------------------------------
/**
 * ���A�[�J�C�u�n���h������
 *
 *@brief	�p���b�g�f�[�^�̃��\�[�X��ύX
 *
 *@param	resm			�p���b�g�p���\�[�X�}�l�[�W���|�C���^
 *@param	resObj			�ύX���郊�\�[�X�I�u�W�F
 *@param	arcHandle		�A�[�J�C�u�t�@�C���n���h��
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	heap			�g�p����q�[�v
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResChgArcPltt_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int heap)
{
	int vram_type;	// Vram�]����
	int pltt_num;	// �p���b�g�]����
	int id;			// ID
	
	GF_ASSERT(resm);
	GF_ASSERT_MSG(resm->type == CLACT_U_PLTT_RES, "���\�[�X�^�C�v���Ⴂ�܂�");
	GF_ASSERT(resObj);
	GF_ASSERT_MSG(resObj->type == CLACT_U_PLTT_RES, "���\�[�X�^�C�v���Ⴂ�܂�");

	// ���܂ł̃f�[�^�ۑ�
	id = CLACT_U_ResManagerGetResObjID( resObj );
	vram_type =	CLACT_U_ResManagerGetResObjVramType( resObj );
	pltt_num = CLACT_U_ResManagerGetResObjPlttNum( resObj );
	
	// ���܂ł̃f�[�^�j��
	CLACT_U_ResManagerResDelete( resm, resObj );

	// ���̃f�[�^�e�[�u���ɐV�����f�[�^�ǂݍ���
	SetArcOneData_ArcHandle(resm, resObj, arcHandle, dataIdx, compFlag, id, vram_type, pltt_num, CLACT_U_PLTT_RES, heap, ALLOC_TOP);
}

//----------------------------------------------------------------------------
/**
 * ���A�[�J�C�u�n���h������
 *
 *@brief	�Z���A�Z���A�j���A�}���`�Z���A�}���`�Z���A�j���f�[�^�̃��\�[�X��ύX
 *
 *@param	resm			�ύX���郊�\�[�X�p���\�[�X�}�l�[�W���|�C���^
 *@param	resObj			�ύX���郊�\�[�X�I�u�W�F
 *@param	arcHandle		�A�[�J�C�u�t�@�C���n���h��
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	type			���\�[�X�^�C�v
 *@param	heap			�g�p����q�[�v
 *
 *@return	none
 *
 * ���\�[�X�^�C�v
	enum{
		CLACT_U_CHAR_RES,		// �L�����N�^���\�[�X���Ǘ�
		CLACT_U_PLTT_RES,		// �p���b�g���\�[�X���Ǘ�
		CLACT_U_CELL_RES,		// �Z�����\�[�X���Ǘ�
		CLACT_U_CELLANM_RES,	// �Z���A�j�����\�[�X���Ǘ�
		CLACT_U_MULTI_RES,		// �}���`�Z�����\�[�X���Ǘ�
		CLACT_U_MULTIANM_RES,	// �}���`�Z���A�j�����\�[�X���Ǘ�
		CLACT_U_RES_MAX			// �ő�
	};
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResChgArcKindCell_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int type, int heap)
{
	int id;			// ID
	
	GF_ASSERT(resm);
	GF_ASSERT(resObj);

	// ���܂ł̃f�[�^�ۑ�
	id = CLACT_U_ResManagerGetResObjID( resObj );
	
	// ���܂ł̃f�[�^�j��
	CLACT_U_ResManagerResDelete( resm, resObj );

	// ���̃f�[�^�e�[�u���ɐV�����f�[�^�ǂݍ���
	SetArcOneData_ArcHandle(resm, resObj, arcHandle, dataIdx, compFlag, id, 0, 0, type, heap, ALLOC_TOP);
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�f�[�^���w�b�_�[����ǂݍ���
 *
 *@param	resm		���\�[�X�}�l�[�W���[�|�C���^
 *@param	head		�w�b�_�[
 *@param	p_ro_tbl	�������m�ۍς݃��\�[�X�I�u�W�F�e�[�u��
 *@param	heap		�g�p����q�[�v
 *
 *@return	int			�ǂݍ��ݐ�
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerResAddsHd(CLACT_U_RES_MANAGER_PTR resm, const CLACT_U_RES_HEADER_PTR head, CLACT_U_RES_OBJ_TBL* p_ro_tbl, int heap )
{
	GF_ASSERT(resm);
	GF_ASSERT(head);

	CLACT_U_ResManagerResAddsHdEx(resm, head, 0, head->tbl_num, p_ro_tbl, heap);
	return head->tbl_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�f�[�^���w�b�_�[����ǂݍ���(�ǂݍ��ސ����w��)
 *
 *@param	resm		���\�[�X�}�l�[�W���[�|�C���^
 *@param	head		�w�b�_�[
 *@param	start		�ǂݍ��݊J�n�e�[�u���i���o�[
 *@param	num			�ǂݍ��ݐ�
 *@param	p_ro_tbl	�������m�ۍς݃��\�[�X�I�u�W�F�e�[�u��
 *@param	heap		�g�p����q�[�v
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResAddsHdEx(CLACT_U_RES_MANAGER_PTR resm, const CLACT_U_RES_HEADER_PTR head, int start, int num, CLACT_U_RES_OBJ_TBL* p_ro_tbl,int heap)
{
	int i;
	CLACT_U_RES_OBJ_PTR obj;

	
	for(i=start;i<start+num;i++){
		obj = CLACT_U_ResManagerResAddHd(resm, head, i, heap);

		// �ǂݍ��񂾃��\�[�X���i�[
		if(p_ro_tbl != NULL){
			if(p_ro_tbl->tbl_num > p_ro_tbl->tbl_now){	// �o�^�\�Ȃ�o�^
				p_ro_tbl->tbl[ p_ro_tbl->tbl_now ] = obj;// �o�^�����I�u�W�F��ݒ�
				p_ro_tbl->tbl_now++;	// �o�^���J�E���g
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�e�[�u���쐬
 *
 *@param	num		�e�[�u����
 *@param	heap	�g�p�q�[�v
 *
 *@return	CLACT_U_RES_OBJ_TBL* �쐬�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_TBL* CLACT_U_ResManagerResObjTblMake(int num, int heap)
{
	CLACT_U_RES_OBJ_TBL* resTbl;

	// ���\�[�X�I�u�W�F�i�[�̈���쐬
	resTbl = sys_AllocMemory(heap, sizeof(CLACT_U_RES_OBJ_TBL));
	resTbl->tbl = sys_AllocMemory(heap, sizeof(CLACT_U_RES_OBJ_PTR)*num);
	resTbl->tbl_num = num;
	resTbl->tbl_now = 0;

	return resTbl;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�e�[�u���j��
 *
 *@param	tbl		�j���e�[�u��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResObjTblDelete(CLACT_U_RES_OBJ_TBL* tbl)
{
	sys_FreeMemoryEz(tbl->tbl);
	sys_FreeMemoryEz(tbl);
	tbl = NULL;
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	�c��o�^�\���擾
 *
 *@param	resm		���\�[�X�}�l�[�W���[�|�C���^
 *
 *@return	int		�c��o�^�\��
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerRest(CLACT_U_RES_MANAGER_PTR resm)
{
	GF_ASSERT(resm);
	return resm->tbl_num - resm->tbl_now;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ID�̃f�[�^�����邩�`�F�b�N
 *
 *@param	resm	���\�[�X�}�l�[�W��
 *@param	id		�`�F�b�N����ID
 *
 *@retval	TRUE	ID�̃f�[�^������
 *@retval	FALSE	ID�̃f�[�^������
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_U_ResManagerCheckID(CONST_CLACT_U_RES_MANAGER_PTR resm, int id)
{
	GF_ASSERT(resm);
	
	return RESM_CheckID(resm->res_manager, id);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���\�[�X�I�u�W�F���̓ǂݍ���ł����f�[�^�̂ݔj��
 *			ID�⃊�\�[�X�^�C�v�Ȃǂ̏��͕ێ������܂�
 *
 *	@param	res_obj		���\�[�X�I�u�W�F
 *
 *	@return	none
 *
 * ���̊֐����ĂԂ�Vram�ւ̃��\�[�X�̓]���Ȃǂ��s���Ȃ��Ȃ�܂��B
 * 
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResOnlyDelete( CLACT_U_RES_OBJ_PTR res_obj )
{
	GF_ASSERT( res_obj );
	
	// �g���f�[�^�j��
	delExData(res_obj);

	// ���\�[�X�̐��f�[�^�j��
	RESM_SetRes(res_obj->res_obj, NULL);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�j��
 *
 *@param	resm		�Z���A�N�^�[���[�e�B���e�B���\�[�X�}�l�[�W���[�|�C���^
 *@param	res_obj		���\�[�X�I�u�W�F
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResDelete(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR res_obj)
{
	GF_ASSERT(resm);
	GF_ASSERT(resm->resObj);

	// �g���f�[�^�j��
	delExData(res_obj);

	// ���\�[�X��j�����A�f�[�^�e�[�u������ɂ���
	RESM_DeleteRes(resm->res_manager, res_obj->res_obj);
	res_obj->res_obj = NULL;
	
	resm->tbl_now--;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�S�j��
 *
 *@param	resm		�Z���A�N�^�[���[�e�B���e�B���\�[�X�}�l�[�W���[�|�C���^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerResDeleteAll(CLACT_U_RES_MANAGER_PTR resm)
{
	int i;		// ���[�v�p

	for(i=0;i<resm->tbl_num;i++){
		if(resm->resObj[i].res_obj != NULL){
			CLACT_U_ResManagerResDelete(resm, resm->resObj + i);
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ID�̃��\�[�X���擾
 *
 *@param	id		�擾���郊�\�[�X�I�u�W�F�|�C���^�ɐݒ肳��Ă���Ǘ��h�c
 *	
 *@return	CLACT_U_RES_OBJ_PTR		���\�[�X�I�u�W�F�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerGetIDResObjPtr(CONST_CLACT_U_RES_MANAGER_PTR resm, int id)
{
	int i;		// ���[�v�p
	int ret_id;	// id

	GF_ASSERT(resm);

	for(i=0;i<resm->tbl_num;i++){
		if(resm->resObj[i].res_obj){
			ret_id = RESM_GetID(resm->resObj[i].res_obj);

			if(ret_id == id){
				return (resm->resObj + i);
			}
		}

	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F����h�c���擾
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *	
 *@return	int		�Ǘ��h�c
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerGetResObjID(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	GF_ASSERT(resObj);
	return RESM_GetID(resObj->res_obj);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F����h�c��ݒ�
 *
 *@param	resm	�ύX����I�u�W�F�̓o�^����Ă��郊�\�[�X�}�l�[�W��
 *@param	resObj	���\�[�X�I�u�W�F
 *@param	id		�ݒ肷��ID
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerSetResObjID(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int id)
{
	GF_ASSERT(resObj);

	RESM_SetID(resm->res_manager, resObj->res_obj, id);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�̃��\�[�X���擾
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *	
 *@return	void*	���\�[�X�|�C���^
 *
 * �A���p�b�N�֎~�ł��B
 * �A���p�b�N�ς݃t�@�C�����擾����֐���p�ӂ��Ă��邽�߁A
 * ��������g�p���Ă��������B
 *
 */
//-----------------------------------------------------------------------------
void* CLACT_U_ResManagerGetResObjRes(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	void* buff;
	
	GF_ASSERT(resObj);
	buff = RESM_GetRes(resObj->res_obj);

	// CLACT_U_ResManagerResOnlyDelete�Ńf�[�^��j�������ׁA
	// �f�[�^������܂���B
	GF_ASSERT( buff );
	
	return buff;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�f�[�^���擾	���\�[�X�f�[�^���A���p�b�N���Ă���擾
 *
 *@param	resObj	�L�����N�^���\�[�X�I�u�W�F
 *
 *@return	�L�����N�^���\�[�X�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dCharacterData* CLACT_U_ResManagerGetResObjResChar(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	CLACT_U_RES_EX_CHAR* data;
	
	GF_ASSERT(resObj->type == CLACT_U_CHAR_RES);

	data = (CLACT_U_RES_EX_CHAR*)getExData( resObj );

	return data->pCharData;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^���擾	���\�[�X�f�[�^���A���p�b�N���Ă���擾
 *
 *@param	resObj	�p���b�g���\�[�X�I�u�W�F
 *
 *@return	�p���b�g���\�[�X�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dPaletteData* CLACT_U_ResManagerGetResObjResPltt(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	CLACT_U_RES_EX_PLTT* data;
	
	GF_ASSERT(resObj->type == CLACT_U_PLTT_RES);

	data = (CLACT_U_RES_EX_PLTT*)getExData( resObj ); 

	return data->pPlttData;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���f�[�^���擾	���\�[�X�f�[�^���A���p�b�N���Ă���擾
 *
 *@param	resObj	�Z�����\�[�X�I�u�W�F
 *
 *@return	�Z�����\�[�X�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dCellDataBank* CLACT_U_ResManagerGetResObjResCell(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	CLACT_U_RES_EX_CELL* data;
	
	GF_ASSERT(resObj->type == CLACT_U_CELL_RES);

	data = (CLACT_U_RES_EX_CELL*)getExData( resObj );

	return data->pCellData;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�j���f�[�^���擾	���\�[�X�f�[�^���A���p�b�N���Ă���擾
 *
 *@param	resObj	�Z���A�j�����\�[�X�I�u�W�F
 *
 *@return	�Z���A�j�����\�[�X�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dCellAnimBankData* CLACT_U_ResManagerGetResObjResCellAnm(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	CLACT_U_RES_EX_CELLANM* data;
	
	GF_ASSERT(resObj->type == CLACT_U_CELLANM_RES);

	data = (CLACT_U_RES_EX_CELLANM*)getExData( resObj );

	return data->pCellANMData;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�}���`�Z���f�[�^���擾	���\�[�X�f�[�^���A���p�b�N���Ă���擾
 *
 *@param	resObj	�}���`�Z�����\�[�X�I�u�W�F
 *
 *@return	�}���`�Z�����\�[�X�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dMultiCellDataBank* CLACT_U_ResManagerGetResObjResMultiCell(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	CLACT_U_RES_EX_MULTI* data;
	
	GF_ASSERT(resObj->type == CLACT_U_MULTI_RES);

	data = (CLACT_U_RES_EX_MULTI*)getExData( resObj );

	return data->pMultiData;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�}���`�Z���A�j���f�[�^���擾	���\�[�X�f�[�^���A���p�b�N���Ă���擾
 *
 *@param	resObj	�}���`�Z���A�j�����\�[�X�I�u�W�F
 *
 *@return	�}���`�Z���A�j�����\�[�X�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dMultiCellAnimBankData* CLACT_U_ResManagerGetResObjResMultiCellAnim(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	CLACT_U_RES_EX_MULTIANM* data;
	
	GF_ASSERT(resObj->type == CLACT_U_MULTIANM_RES);

	data = (CLACT_U_RES_EX_MULTIANM*)getExData( resObj );

	return data->pMultiANMData;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�ɐݒ肳��Ă��郊�\�[�X�̃^�C�v���擾
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *	
 *@return	int		���\�[�X�^�C�v
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerGetResObjResType(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	GF_ASSERT(resObj);
	return resObj->type;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�ɐݒ肳��Ă���Vram�^�C�v���擾
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *	
 *@return	int		Vram�^�C�v�i�L�����N�^�B�p���b�g���̂݁j
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerGetResObjVramType(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	GF_ASSERT(resObj);

	if(resObj->type == CLACT_U_CHAR_RES){
		CLACT_U_RES_EX_CHAR* chardata;
		chardata = getExData( resObj );
		return chardata->vram_type;
	}
	
	if(resObj->type == CLACT_U_PLTT_RES){
		CLACT_U_RES_EX_PLTT* plttdata;
		plttdata = getExData( resObj );
		return plttdata->vram_type;
	}
	
	return 0;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�ɐݒ肳��Ă���p���b�g�ǂݍ��ݐ����擾
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *	
 *@return	int		Vram�^�C�v�i�p���b�g���̂݁j
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerGetResObjPlttNum(CONST_CLACT_U_RES_OBJ_PTR resObj)
{
	GF_ASSERT(resObj);

	if(resObj->type == CLACT_U_PLTT_RES){
		CLACT_U_RES_EX_PLTT* plttdata;
		plttdata = getExData( resObj );
		return plttdata->pltt_num;
	}
	
	return 0;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�ɐݒ肳��Ă���vram�^�C�v���擾
 *
 *@param	resobj	���\�[�X�I�u�W�F
 *@param	vram	vram�^�C�v	���C��:1	�T�u:2
 *	
 *@return	int		vram�^�C�v�i�L�����N�^�B�p���b�g���̂݁j
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerSetResObjVramType(CLACT_U_RES_OBJ_PTR resObj, int vram)
{
	GF_ASSERT(resObj);

	if(resObj->type == CLACT_U_CHAR_RES){
		CLACT_U_RES_EX_CHAR* chardata;
		chardata = getExData( resObj );
		chardata->vram_type = vram;
	}
	
	if(resObj->type == CLACT_U_PLTT_RES){
		CLACT_U_RES_EX_PLTT* plttdata;
		plttdata = getExData( resObj );
		plttdata->vram_type = vram;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�ɐݒ肳��Ă���p���b�g�ǂݍ��ݐ����擾
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *@param	pltt	�p���b�g�ǂݍ��ݐ�
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerSetResObjPlttNum(CLACT_U_RES_OBJ_PTR resObj, int pltt)
{
	GF_ASSERT(resObj);

	if(resObj->type == CLACT_U_PLTT_RES){
		CLACT_U_RES_EX_PLTT* plttdata;
		plttdata = getExData( resObj );
		plttdata->pltt_num = pltt;
	}
}






//----------------------------------------------------------------------------
/**
 *
 *@brief	�w�b�_�[�T�C�Y���擾
 *
 *@param	none
 *
 *@return	int		�T�C�Y
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerGetHeaderSize(void)
{
	return sizeof(CLACT_U_RES_HEADER);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�w�b�_�[��z��Ŋm�ۂ����Ƃ��̊e�v�f���̃f�[�^��
 *			�擾����֐�
 *
 *@param	head	�w�b�_�[�f�[�^�i�z��j
 *@param	no		�v�f��
 *
 *@return	CLACT_U_RES_HEADER_PTR
 *
 * no���z��̗v�f�����傫�����A�s���ȃ|�C���^��Ԃ��Ă��܂��܂��B
 *
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_HEADER_PTR CLACT_U_ResManagerGetHeaderNoData(CLACT_U_RES_HEADER_PTR head, int no)
{
	return (head + no);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�N�^�[���[�e�B���e�B���\�[�X�}�l�[�W���w�b�_�[�ǂݍ���
 *
 *@param	path		�w�b�_�[�t�@�C���p�X
 *@param	head		�w�b�_�[�i�[��
 *@param	heap		�g�p����q�[�v
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderLoad(const char* path, CLACT_U_RES_HEADER_PTR head,int heap)
{
	char* tmp;				// ����p
	char* buff;				// �t�@�C���f�[�^
	int	i;					// ���[�v�p

	GF_ASSERT(head);		// �w�b�_�[�̈���m�ۂ��Ă�������


	// �t�@�C���ǂݍ���
	tmp = sys_LoadFile(heap, path);
	GF_ASSERT_MSG(tmp, "�w�b�_�[�ǂݍ��ݎ��s");

	// ���[�N�o�b�t�@
	buff = makeCopyStr(tmp, heap);
	
	// ���\�[�X�^�C�v�擾
	head->type = getHeaderType(buff);
	delCopyStr(buff);			// ��������j��
	buff = makeCopyStr(tmp, heap);	// �ăR�s�[

	// �A�[�J�C�u�^�C�v�擾
	head->arc_flag = getHeaderArc(buff);
	delCopyStr(buff);			// ��������j��
	buff = makeCopyStr(tmp, heap);	// �ăR�s�[

	// �f�[�^���̎擾
	head->tbl_num = getHeaderNum(buff, head->type, head->arc_flag);
	delCopyStr(buff);			// ��������j��
	buff = makeCopyStr(tmp, heap);	// �ăR�s�[
	
	// �f�[�^���̗���̊m��
	if(head->tbl_num > 0){
		if(head->arc_flag == 0){
			head->tbl = sys_AllocMemory(heap, sizeof(CLACT_U_RES_HEADER_SUB)*head->tbl_num);
		}else{
			head->tbl = sys_AllocMemory(heap, sizeof(CLACT_U_RES_HEADER_SUBARC)*head->tbl_num);
		}
	}else{
		head->tbl = NULL;
	}
	
	// �f�[�^���i�[
	if(head->tbl){
		loadHeaderData(buff, head->type, head->tbl, head->tbl_num, head->arc_flag);	
	}
	
	// �ǂݍ��݃t�@�C����j��
	delCopyStr(buff);
	sys_FreeMemoryEz(tmp);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�N�^�[���[�e�B���e�B���\�[�X�}�l�[�W���o�C�i���w�b�_�[�ǂݍ���
 *
 *@param	cp_bindata		�o�C�i���f�[�^
 *@param	head			�w�b�_�[�i�[��
 *@param	heap			�g�p����q�[�v
 *
 *@return	none
 *
 * Binary�f�[�^����		�S�f�[�^4byte��؂�
 *	���\�[�X�^�C�v
 *	�A�[�J�C�u�t�@�C��idx
 *	�f�[�^idx
 *	���k�t���O
 *	�Ǘ�ID
 *	����Vram�^�C�v				����Ȃ��Ƃ��̓_�~�[�f�[�^
 *	  ���p���b�g�ǂݍ��ݖ{��	����Ȃ��Ƃ��̓_�~�[�f�[�^
 *
 * ���L�����N�^���\�[�X�̎�
 * ���p���b�g���\�[�X�̎�
 *	
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderLoadBinary(const void* cp_bindata, CLACT_U_RES_HEADER_PTR head,int heap)
{
	int	i;					// ���[�v�p
	const int* view;		// �o�C�i���f�[�^���Q�Ɨp

	GF_ASSERT(head);		// �w�b�_�[�̈���m�ۂ��Ă�������

	// �Q�Ƃł���悤��int*�^�Ō���
	view = cp_bindata;

	// ���\�[�X�^�C�v�擾
	head->type = view[0];		// �擪4byte ���\�[�X�^�C�v

	head->arc_flag = 1;			// �A�[�J�C�u�t�@�C���Œ�

	// �f�[�^���̎擾
	head->tbl_num = getHeaderNumBinary( (const CLACT_U_RES_HEADER_SUBARC*)(view + 1) );
	
	// �f�[�^���̗̈�̊m��
	if(head->tbl_num > 0){
		head->tbl = sys_AllocMemory(heap, sizeof(CLACT_U_RES_HEADER_SUBARC)*head->tbl_num);
	}else{
		head->tbl = NULL;
	}
	
	// �f�[�^���i�[
	if(head->tbl){
		memcpy( head->tbl, view + 1, sizeof(CLACT_U_RES_HEADER_SUBARC)*head->tbl_num );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�}�l�[�W���w�b�_�[�j��
 *
 *@param	head		�w�b�_�[�|�C���^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderFree(CLACT_U_RES_HEADER_PTR head)
{
	if(head->tbl){
		sys_FreeMemoryEz(head->tbl);
	}
	head->tbl = NULL;
	head->tbl_num = 0;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�}�l�[�W���[�w�b�_�[�ɓǂݍ��܂�Ă���f�[�^���擾
 *
 *@param	head		���\�[�X�w�b�_
 *
 *@return	int		�ǂݍ��܂�Ă���f�[�^��
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderSetDataNum(CONST_CLACT_U_RES_HEADER_PTR head)
{
	GF_ASSERT(head);
	return head->tbl_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�}�l�[�W���[�w�b�_�[�ɓǂݍ��܂�Ă���f�[�^�̃��\�[�X�^�C�v
 *
 *@param	head		���\�[�X�w�b�_
 *
 *@return	int		���\�[�X�^�C�v
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderSetDataResType(CONST_CLACT_U_RES_HEADER_PTR head)
{
	GF_ASSERT(head);
	return head->type;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�}�l�[�W���[�w�b�_�[�ɓǂݍ��܂�Ă���f�[�^�̓A�[�J�C�u����Ă��邩
 *
 *@param	head		���\�[�X�w�b�_
 *
 *@return	int			0�F����ĂȂ�	1�F����Ă�
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderSetDataArc(CONST_CLACT_U_RES_HEADER_PTR head)
{
	GF_ASSERT(head);
	return head->arc_flag;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�w�b�_�ɓo�^����Ă���f�[�^��ID��ύX����
 *
 *	@param	head		���\�[�X�w�b�_�[
 *	@param	no			���\�[�X�w�b�_�[���ɓo�^����Ă���f�[�^�i���o�[
 *	@param	param		�ݒ肷��ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderDataIDSet( CLACT_U_RES_HEADER_PTR head, int no, int param )
{
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 0){
		CLACT_U_RES_HEADER_SUB* data = head->tbl;

		data[ no ].id = param;
	}else{
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		data[ no ].id = param;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�w�b�_�ɓo�^����Ă���f�[�^��ID���擾����
 *
 *	@param	head		���\�[�X�w�b�_�[
 *	@param	no			���\�[�X�w�b�_�[���ɓo�^����Ă���f�[�^�i���o�[
 *
 *	@return	int		�Ǘ�ID
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderDataIDGet( CONST_CLACT_U_RES_HEADER_PTR head, int no )
{
	int ret_id;		// �߂�l�p
	
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 0){
		CLACT_U_RES_HEADER_SUB* data = head->tbl;

		ret_id = data[ no ].id;
	}else{
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		ret_id = data[ no ].id;
	}

	return ret_id;
}

//----------------------------------------------------------------------------
/**
 *	�A�[�J�C�u�t�@�C����p
 *
 *	@brief	�w�b�_�ɓo�^����Ă���A�[�J�C�u�t�@�C��ID��ύX����
 *
 *	@param	head		���\�[�X�w�b�_�[
 *	@param	no			���\�[�X�w�b�_�[���ɓo�^����Ă���f�[�^�i���o�[
 *	@param	param		�ݒ肷��A�[�J�C�u�t�@�C��ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderArcFileSet( CLACT_U_RES_HEADER_PTR head, int no, int param )
{
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 1){
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		data[ no ].arcFile = param;
	}
}

//----------------------------------------------------------------------------
/**
 *	�A�[�J�C�u�t�@�C����p
 *
 *	@brief	�w�b�_�ɓo�^����Ă���f�[�^�̃A�[�J�C�u�t�@�C��ID���擾����
 *
 *	@param	head		���\�[�X�w�b�_�[
 *	@param	no			���\�[�X�w�b�_�[���ɓo�^����Ă���f�[�^�i���o�[
 *
 *	@return	int		�A�[�J�C�u�t�@�C��ID
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderArcFileGet( CONST_CLACT_U_RES_HEADER_PTR head, int no )
{
	int ret_id;		// �߂�l�p
	
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 1){
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		ret_id = data[ no ].arcFile;
	}

	return ret_id;
}

//----------------------------------------------------------------------------
/**
 *	�A�[�J�C�u�t�@�C����p
 *
 *	@brief	�w�b�_�ɓo�^����Ă���A�[�J�C�uidx��ύX����
 *
 *	@param	head		���\�[�X�w�b�_�[
 *	@param	no			���\�[�X�w�b�_�[���ɓo�^����Ă���f�[�^�i���o�[
 *	@param	param		�ݒ肷��A�[�J�C�u�t�@�C��ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderDataIdxSet( CLACT_U_RES_HEADER_PTR head, int no, int param )
{
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 1){
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		data[ no ].dataIdx = param;
	}
}

//----------------------------------------------------------------------------
/**
 *	�A�[�J�C�u�t�@�C����p
 *
 *	@brief	�w�b�_�ɓo�^����Ă���f�[�^�̃f�[�^idx���擾����
 *
 *	@param	head		���\�[�X�w�b�_�[
 *	@param	no			���\�[�X�w�b�_�[���ɓo�^����Ă���f�[�^�i���o�[
 *
 *	@return	int			�f�[�^idx
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderDataIdxGet( CONST_CLACT_U_RES_HEADER_PTR head, int no )
{
	int ret_id;		// �߂�l�p
	
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 1){
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		ret_id = data[ no ].dataIdx;
	}

	return ret_id;
}

//----------------------------------------------------------------------------
/**
 *	�A�[�J�C�u�t�@�C����p
 *
 *	@brief	�w�b�_�ɓo�^����Ă��鈳�k�t�@�C���t���O��ύX����
 *
 *	@param	head		���\�[�X�w�b�_�[
 *	@param	no			���\�[�X�w�b�_�[���ɓo�^����Ă���f�[�^�i���o�[
 *	@param	param		�ݒ肷��t���O	�iTRUE�@FALSE�j
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderCompFlagSet( CLACT_U_RES_HEADER_PTR head, int no, int param )
{
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 1){
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		data[ no ].compFlag = param;
	}
}

//----------------------------------------------------------------------------
/**
 *	�A�[�J�C�u�t�@�C����p
 *
 *	@brief	�w�b�_�ɓo�^����Ă���f�[�^�̃f�[�^idx���擾����
 *
 *	@param	head		���\�[�X�w�b�_�[
 *	@param	no			���\�[�X�w�b�_�[���ɓo�^����Ă���f�[�^�i���o�[
 *
 *	@return	int			���k�t���O	�iTRUE�@FALSE�j
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderCompFlagGet( CONST_CLACT_U_RES_HEADER_PTR head, int no )
{
	int ret_id;		// �߂�l�p
	
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 1){
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		ret_id = data[ no ].compFlag;
	}

	return ret_id;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�w�b�_�ɓo�^����Ă���VRam�^�C�v��ύX����
 *
 *	@param	head		���\�[�X�w�b�_�[
 *	@param	no			���\�[�X�w�b�_�[���ɓo�^����Ă���f�[�^�i���o�[
 *	@param	param		�ݒ肷��VRam�^�C�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderVramTypeSet( CLACT_U_RES_HEADER_PTR head, int no, int param )
{
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 0){
		CLACT_U_RES_HEADER_SUB* data = head->tbl;

		data[ no ].ex[0]= param;
	}else{
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		data[ no ].ex[0] = param;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�w�b�_�ɓo�^����Ă���f�[�^��VramType���擾����
 *
 *	@param	head		���\�[�X�w�b�_�[
 *	@param	no			���\�[�X�w�b�_�[���ɓo�^����Ă���f�[�^�i���o�[
 *
 *	@return	int		VramType
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderVramTypeGet( CONST_CLACT_U_RES_HEADER_PTR head, int no )
{
	int ret_id;		// �߂�l�p
	
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 0){
		CLACT_U_RES_HEADER_SUB* data = head->tbl;

		ret_id = data[ no ].ex[0];
	}else{
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		ret_id = data[ no ].ex[0];
	}

	return ret_id;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�w�b�_�ɓo�^����Ă���p���b�g�ǂݍ��ݐ���ύX����
 *
 *	@param	head		���\�[�X�w�b�_�[
 *	@param	no			���\�[�X�w�b�_�[���ɓo�^����Ă���f�[�^�i���o�[
 *	@param	param		�ݒ肷��p���b�g�ǂݍ��ݐ�
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_ResManagerHeaderPlttNumSet( CLACT_U_RES_HEADER_PTR head, int no, int param )
{
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 0){
		CLACT_U_RES_HEADER_SUB* data = head->tbl;

		data[ no ].ex[1]= param;
	}else{
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		data[ no ].ex[1] = param;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�w�b�_�ɓo�^����Ă���f�[�^�̃p���b�g�ǂݍ��ݐ����擾����
 *
 *	@param	head		���\�[�X�w�b�_�[
 *	@param	no			���\�[�X�w�b�_�[���ɓo�^����Ă���f�[�^�i���o�[
 *
 *	@return	int		VramType
 *
 *
 */
//-----------------------------------------------------------------------------
int CLACT_U_ResManagerHeaderPlttNumGet( CONST_CLACT_U_RES_HEADER_PTR head, int no )
{
	int ret_id;		// �߂�l�p
	
	GF_ASSERT( head );
	GF_ASSERT( head->tbl_num > no );
	
	if(head->arc_flag == 0){
		CLACT_U_RES_HEADER_SUB* data = head->tbl;

		ret_id = data[ no ].ex[1];
	}else{
		CLACT_U_RES_HEADER_SUBARC* data = head->tbl;

		ret_id = data[ no ].ex[1];
	}

	return ret_id;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�󂢂Ă��郊�\�[�X�I�u�W�F�e�[�u�����擾
 *
 *@param	none
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_U_RES_OBJ_PTR getCleanResObj(CLACT_U_RES_MANAGER_PTR resm)
{
	int i;

	for(i=0;i<resm->tbl_num;i++){
		if(resm->resObj[i].res_obj == NULL){
			return resm->resObj + i;
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�g���f�[�^�쐬
 *
 *@param	resObj		���\�[�X�I�u�W�F
 *@param	type		���\�[�X�^�C�v
 *@param	vram_type	Vram�^�C�v
 *@param	pltt_num	�p���b�g��
 *@param	heap		�q�[�v�i���o�[
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void makeExData(CLACT_U_RES_OBJ_PTR resObj, int type, int vram_type, int pltt_num, int heap)
{
	void* res;

	res = RESM_GetRes(resObj->res_obj);		// ���\�[�X�擾
	
	switch(type){
	case CLACT_U_CHAR_RES:
		resObj->res_ex = makeExChar(res, vram_type, heap);
		break;
	case CLACT_U_PLTT_RES:
		resObj->res_ex = makeExPltt(res, vram_type, pltt_num, heap);
		break;
	case CLACT_U_CELL_RES:
		resObj->res_ex = makeExCell(res, heap);
		break;
	case CLACT_U_CELLANM_RES:
		resObj->res_ex = makeExCellAnm(res, heap);
		break;
	case CLACT_U_MULTI_RES:
		resObj->res_ex = makeExMulti(res, heap);
		break;
	case CLACT_U_MULTIANM_RES:
		resObj->res_ex = makeExMultiAnm(res, heap);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�g���f�[�^�쐬
 *
 *@param	res			���\�[�X�|�C���^
 *@param	vram_type	vram�^�C�v
 *@param	heap		�g�p�q�[�v
 *
 *@return	CLACT_U_RES_EX_CHAR*	�쐬�����f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_U_RES_EX_CHAR* makeExChar(void* res, int vram_type, int heap)
{
	CLACT_U_RES_EX_CHAR* data;

	data = sys_AllocMemory(heap, sizeof(CLACT_U_RES_EX_CHAR));
	NNS_G2dGetUnpackedCharacterData(res, &data->pCharData);
	data->vram_type = vram_type;
	
	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�g���f�[�^���쐬
 *
 *@param	res			���\�[�X�|�C���^
 *@param	vram_type	Vram�^�C�v
 *@param	pltt_num	�p���b�g��
 *@param	heap		�g�p�q�[�v
 *
 *@return	CLACT_U_RES_EX_PLTT* �쐬�����f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_U_RES_EX_PLTT* makeExPltt(void* res, int vram_type, int pltt_num, int heap)
{
	CLACT_U_RES_EX_PLTT* data;

	data = sys_AllocMemory(heap, sizeof(CLACT_U_RES_EX_PLTT));
	NNS_G2dGetUnpackedPaletteData(res, &data->pPlttData);
	data->vram_type = vram_type;
	data->pltt_num	= pltt_num;

	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���g���f�[�^���쐬
 *
 *@param	res		���\�[�X�|�C���^
 *@param	heap	�g�p�q�[�v
 *
 *@return	CLACT_U_RES_EX_CELL*	�쐬�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_U_RES_EX_CELL* makeExCell(void* res, int heap)
{
	CLACT_U_RES_EX_CELL* data;

	data = sys_AllocMemory(heap, sizeof(CLACT_U_RES_EX_CELL));
	NNS_G2dGetUnpackedCellBank(res, &data->pCellData);

	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�j���g���f�[�^�쐬
 *
 *@param	res		���\�[�X�|�C���^
 *@param	heap	�g�p�q�[�v
 *
 *@return	CLACT_U_RES_EX_CELLANM*	�쐬�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_U_RES_EX_CELLANM*	makeExCellAnm(void* res, int heap)
{
	CLACT_U_RES_EX_CELLANM* data;

	data = sys_AllocMemory(heap, sizeof(CLACT_U_RES_EX_CELLANM));
	NNS_G2dGetUnpackedAnimBank(res, &data->pCellANMData);

	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�}���`�Z���g���f�[�^�쐬
 *
 *@param	res		���\�[�X�|�C���^
 *@param	heap	�g�p�q�[�v
 *
 *@return	CLACT_U_RES_EX_MULTI*	�쐬�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_U_RES_EX_MULTI*	makeExMulti(void* res, int heap)
{
	CLACT_U_RES_EX_MULTI* data;

	data = sys_AllocMemory(heap, sizeof(CLACT_U_RES_EX_MULTI));
	NNS_G2dGetUnpackedMultiCellBank(res, &data->pMultiData);

	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�}���`�Z���A�j���g���f�[�^�쐬
 *
 *@param	res		���\�[�X�|�C���^
 *@param	heap	�g�p�q�[�v
 *
 *@return	CLACT_U_RES_EX_MULTIANM* �쐬�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_U_RES_EX_MULTIANM* makeExMultiAnm(void* res, int heap)
{
	CLACT_U_RES_EX_MULTIANM* data;

	data = sys_AllocMemory(heap, sizeof(CLACT_U_RES_EX_MULTIANM));
	NNS_G2dGetUnpackedMCAnimBank(res, &data->pMultiANMData);

	return data;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	���ꂼ��̊g���f�[�^��j��
 *
 *@param	���\�[�X�I�u�W�F	
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void delExData(CLACT_U_RES_OBJ_PTR resObj)
{
	if( resObj->res_ex ){
		sys_FreeMemoryEz(resObj->res_ex);
	}
	resObj->res_ex = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�g���f�[�^�擾
 *
 *	@param	resObj	���\�[�X�I�u�W�F
 *
 *	@return	�e�g���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static void* getExData( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	GF_ASSERT( resObj );

	// CLACT_U_ResManagerResOnlyDelete�Ńf�[�^��j�������ׁA
	// �f�[�^������܂���B
	GF_ASSERT( resObj->res_ex );
	
	return resObj->res_ex;
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	�P�̃f�[�^��ǂݍ���
 *
 *@param	resm	���\�[�X�}�l�[�W���[
 *@param	resObj	���\�[�X�I�u�W�F
 *@param	path	�t�@�C���p�X
 *@param	id		�Ǘ�ID
 *@param	vram	vram�^�C�v
 *@param	pltt_num�p���b�g�g�p��
 *@param	type	���\�[�X�^�C�v
 *@param	heap	�g�p�q�[�v
 *
 *@return	CLACT_U_RES_OBJ_PTR		���\�[�X�I�u�W�F�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadOneData(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, const char* path, int id, int vram, int pltt_num, int type, int heap)
{
	resObj->res_obj = RESM_AddRes(resm->res_manager, path, id, heap);	// ���\�[�X�ǂݍ���
	
	resObj->type = type;	// ���\�[�X�^�C�v
	
	// ���̑��f�[�^�ݒ�
	makeExData(resObj, type, vram, pltt_num, heap);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�P�̃A�[�J�C�u�f�[�^�����\�[�X�}�l�[�W���ɐݒ肷��
 *
 *@param	resm		���\�[�X�}�l�[�W���f�[�^
 *@param	resObj		�f�[�^�i�[�惊�\�[�X�I�u�W�F
 *@param	arcFile		�A�[�J�C�u�t�@�C��I����
 *@param	dataIdx		�f�[�^Idx	
 *@param	compFlag	���k�t���O
 *@param	id			�Ǘ�ID
 *@param	vram		Vram�^�C�v
 *@param	pltt_num	�p���b�g�ǂݍ��ݐ�
 *@param	type		���\�[�X�^�C�v
 *@param	heap		�g�p�q�[�v
 *@param	alloc_type	�A���P�[�g�^�C�v
 *	ALLOC_TOP = 0,			///< �q�[�v�̐擪����
 *	ALLOC_BOTTOM = 1,		///< �q�[�v�̏I�[����
 *
 *@return	none
 *	
 *
 */
//-----------------------------------------------------------------------------
static void SetArcOneData(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int type, int heap, u32 alloc_type)
{
	void* res;
	
	// ���\�[�X�ǂݍ���
	res = ArcUtil_Load(arcFile, dataIdx, compFlag, heap, alloc_type);

	// ���\�[�X�}�l�[�W���[�ɐݒ�
	resObj->res_obj = RESM_AddResNormal(resm->res_manager, res, id);

	// ���\�[�X�^�C�v
	resObj->type = type;
	
	// ���̑��f�[�^�ݒ�
	makeExData(resObj, type, vram, pltt_num, heap);
}

//----------------------------------------------------------------------------
/**
 *
 * ���A�[�J�C�u�n���h������
 *
 *@brief	�P�̃A�[�J�C�u�f�[�^�����\�[�X�}�l�[�W���ɐݒ肷��
 *
 *@param	resm		���\�[�X�}�l�[�W���f�[�^
 *@param	resObj		�f�[�^�i�[�惊�\�[�X�I�u�W�F
 *@param	arcHandle	�A�[�J�C�u�t�@�C���n���h��
 *@param	dataIdx		�f�[�^Idx	
 *@param	compFlag	���k�t���O
 *@param	id			�Ǘ�ID
 *@param	vram		Vram�^�C�v
 *@param	pltt_num	�p���b�g�ǂݍ��ݐ�
 *@param	type		���\�[�X�^�C�v
 *@param	heap		�g�p�q�[�v
 *@param	alloc_type	�������m�ۃ^�C�v
 *
 *@return	none
 *	
 *
 */
//-----------------------------------------------------------------------------
static void SetArcOneData_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int type, int heap, u32 alloc_type)
{
	void* res;
	
	res = ArcHandle_Load( arcHandle, dataIdx, compFlag, heap, alloc_type);

	// ���\�[�X�}�l�[�W���[�ɐݒ�
	resObj->res_obj = RESM_AddResNormal(resm->res_manager, res, id);

	// ���\�[�X�^�C�v
	resObj->type = type;
	
	// ���̑��f�[�^�ݒ�
	makeExData(resObj, type, vram, pltt_num, heap);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�f�[�^�^�C�v���擾
 *
 *@param	buff	�w�b�_�[�f�[�^
 *
 *@return	int		���\�[�X�^�C�v
 *
 *
 */
//-----------------------------------------------------------------------------
static int getHeaderType(char* buff)
{
	int no;
	char* tok;
	
	// �擪�ɂ���
	tok	= strtok(buff, ",");
	
	no = atoi(tok);

	return no;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�A�[�J�C�u���ꂽ�t�@�C���p�����擾
 *
 *@param	buff	�w�b�_�[�f�[�^
 *
 *@return	int		�A�[�J�C�u���ꂽ�f�[�^�悤��
 *
 *
 */
//-----------------------------------------------------------------------------
static int getHeaderArc(char* buff)
{
	int no;
	char* tok;
	
	// �擪����Q�Ԗ�
	tok	= strtok(buff, ",");
	tok	= strtok(NULL, ",");
	
	no = atoi(tok);

	return no;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�w�b�_�[�ɓo�^����Ă���f�[�^�����擾
 *
 *@param	buff	�w�b�_�[�f�[�^
 *@param	type	�w�b�_�[�^�C�v
 *@param	arcFlag	�A�[�J�C�u�t�@�C�����ǂ����̃t���O
 *
 *@return	int		�w�b�_�[��
 *
 *
 */
//-----------------------------------------------------------------------------
static int getHeaderNum(char* buff, int type, int arcFlag)
{
	int count;			// �f�[�^���J�E���g
	char* path_or_arc;	// �t�@�C���p�X���A�[�J�C�u�t�@�C��
	char* data_idx;		// �f�[�^�C���f�b�N�X
	char* commpFlag;	// ���k���ꂽ�f�[�^��
	char* id;			// ID
	char* vram;			// vram
	char* pltt;			// pltt

	// �ŏ��̂P�̓��\�[�X�̎�ނȂ̂Ŕ�΂�
	strtok(buff, ",");
	strtok(NULL, ",");
	strtok(NULL, "\n");
	
	count = 0;
	if(arcFlag == 0){
		loadHeaderCore(NULL, &path_or_arc,&id, &vram, &pltt, type);	// �P�̃f�[�^�i�[
	}else{
		loadHeaderCoreArc(NULL, &path_or_arc,&data_idx,&commpFlag,&id,&vram,&pltt,type);
	}
	
	// �p�X��'0'�̃f�[�^���I�[
	while(path_or_arc[0] != 'e'){
		count++;

		if(arcFlag == 0){
			loadHeaderCore(NULL, &path_or_arc, &id, &vram, &pltt, type);	// �P��ڈȍ~��NULL��OK
		}else{
			loadHeaderCoreArc(NULL, &path_or_arc,&data_idx,&commpFlag,&id,&vram,&pltt,type);
		}

		if(path_or_arc == NULL){
			GF_ASSERT(0);		// �I�[�R�[�h������
		}
	}

	return count;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�o�C�i���f�[�^�̃w�b�_�[�e�[�u�������擾
 *
 *	@param	buff	�o�C�i���f�[�^
 *
 *	@return	�I���R�[�h�����Ȃ��e�[�u����
 *
 *
 */
//-----------------------------------------------------------------------------
static int getHeaderNumBinary( const CLACT_U_RES_HEADER_SUBARC* buff )
{
	int count;

	count = 0;
	while( buff[count].arcFile != CLACT_U_RES_HEADER_MAKE_END_CODE ){
		count++;
	}

	return count;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�w�b�_�[�f�[�^��ǂݍ���
 *
 *@param	buff	�w�b�_�[�f�[�^
 *@param	type	���\�[�X�^�C�v
 *@param	tbl		�ǂݍ��ݐ�
 *@param	num		�ǂݍ��݂���
 *@param	arcFlag	�A�[�J�C�u�t�@�C�����ǂ���
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadHeaderData(char* buff, int type, void* tbl, int num, int arcFlag)
{
	int i;		// ���[�v�p
	char* path_or_arc;	// �t�@�C���p�X���A�[�J�C�u�t�@�C��
	char* data_idx;		// �f�[�^�C���f�b�N�X
	char* commpFlag;	// ���k���ꂽ�f�[�^��
	char* id;			// ID
	char* vram;			// vram
	char* pltt;			// pltt

	// �ŏ��̂P�̓��\�[�X�̎�ނȂ̂Ŕ�΂�
	strtok(buff, ",");
	strtok(NULL, ",");
	strtok(NULL, "\n");

	// �ǂݍ���
	for(i=0;i<num;i++){
		if(arcFlag == 0){
			loadHeaderCore(NULL, &path_or_arc, &id, &vram, &pltt, type);	// �P�̃f�[�^�i�[
			setDataHeader((CLACT_U_RES_HEADER_SUB*)tbl + i, path_or_arc, id, vram, pltt);
		}else{
			loadHeaderCoreArc(NULL, &path_or_arc,&data_idx,&commpFlag,&id,&vram,&pltt,type);
			setDataHeaderArc((CLACT_U_RES_HEADER_SUBARC*)tbl + i, path_or_arc, data_idx, commpFlag, id, vram, pltt);
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�P�̃f�[�^��ǂݍ���ł���
 *
 *@param	buff		�w�b�_�[�f�[�^
 *@param	file_path	�p�X�i�[��
 *@param	id			ID�i�[��
 *@param	vram		�u�������^�C�v(NNS_G2D_VRAM_TYPE_2DMAIN,NNS_G2D_VRAM_TYPE_2DSUB,NNS_G2D_VRAM_TYPE_2DMAX)
 *@param	pltt		�p���b�g�i�[��
 *@param	type		���\�[�X�^�C�v
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadHeaderCore(char* buff, char** file_path, char** id, char** vram, char** pltt, int type)
{
	switch(type){
	case CLACT_U_CHAR_RES:
		loadCharHeaderCore(buff, file_path, id, vram);
		*pltt = NULL;
		break;
	case CLACT_U_PLTT_RES:
		loadPlttHeaderCore(buff, file_path, id, vram, pltt);
		break;
	case CLACT_U_CELL_RES:
	case CLACT_U_CELLANM_RES:
	case CLACT_U_MULTI_RES:
	case CLACT_U_MULTIANM_RES:
		loadKindCellHeaderCore(buff, file_path, id);
		*vram = NULL;
		*pltt = NULL;
		break;
	default:
		GF_ASSERT_MSG(0, "�s���ȃt�H�[�}�b�g�ł�\n");
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�P�̃L�����N�^�f�[�^��ǂݍ���
 *
 *@param	buff	�w�b�_�[�f�[�^
 *@param	path	�p�X�i�[��
 *@param	id		ID�i�[��
 *@param	type	Vram�^�C�v�i�[��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadCharHeaderCore(char* buff, char** path, char** id, char** type)
{
	*path	= strtok(buff, ",");
	*id		= strtok(NULL, ",");
	*type	= strtok(NULL, ",");
	strtok(NULL, "\n");
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�̂P�̃f�[�^���擾
 *
 *@param	buff		�w�b�_�[�f�[�^
 *@param	path		�p�X�i�[��
 *@param	id			�h�c�i�[��
 *@param	type		�u�������^�C�v(NNS_G2D_VRAM_TYPE_2DMAIN,NNS_G2D_VRAM_TYPE_2DSUB,NNS_G2D_VRAM_TYPE_2DMAX)
 *@param	pltt_num	�p���b�g��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadPlttHeaderCore(char* buff, char** path, char** id, char** type, char** pltt_num)
{
	*path		= strtok(buff, ",");
	*id			= strtok(NULL, ",");
	*type		= strtok(NULL, ",");
	*pltt_num	= strtok(NULL, ",");
	strtok(NULL, "\n");
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���ނ̃w�b�_�[�f�[�^�i�[
 *	
 *@param	buff	�w�b�_�[�f�[�^
 *@param	path	�p�X�i�[��
 *@param	id		�h�c�i�[��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadKindCellHeaderCore(char* buff, char** path, char** id)
{
	*path		= strtok(buff, ",");
	*id			= strtok(NULL, ",");
	strtok(NULL, "\n");
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�f�[�^�ݒ�
 *
 *@param	head	�ݒ��
 *@param	path	�ݒ�p�X
 *@param	id		�ݒ�h�c
 *@param	vram	�ݒ�u�������^�C�v(NNS_G2D_VRAM_TYPE_2DMAIN,NNS_G2D_VRAM_TYPE_2DSUB,NNS_G2D_VRAM_TYPE_2DMAX)
 *@param	pltt	�ݒ�p���b�g�i���o�[
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setDataHeader(CLACT_U_RES_HEADER_SUB* head, char* path, char* id, char* vram, char* pltt)
{
	strcpy(head->file_path, path);
	head->id = atoi(id);
	if(vram != NULL){
		head->ex[0] = atoi(vram);
	}else{
		head->ex[0] = 0;
	}
	if(pltt != NULL){
		head->ex[1] = atoi(pltt);
	}else{
		head->ex[1] = 0;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�A�[�J�C�u�t�@�C���p�w�b�_�[�ǂݍ��݊֐�
 *
 *@param	buff		�w�b�_�[�f�[�^
 *@param	srcFile		�A�[�J�C�u�t�@�C��ID�i�[��
 *@param	dataIdx		�f�[�^�C���f�b�N�X�i�[��
 *@param	compFlag	���k�t���O�i�[��
 *@param	id			�Ǘ�ID�i�[��
 *@param	vram		Vram�^�C�v�i�[��
 *@param	pltt		�p���b�g�g�p�ʊi�[��
 *@param	type		���\�[�X�^�C�v
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadHeaderCoreArc(char* buff, char** srcFile, char** dataIdx, char** compFlag, char** id, char** vram, char** pltt, int type)
{
	switch(type){
	case CLACT_U_CHAR_RES:
		loadCharHeaderCoreArc(buff, srcFile, dataIdx, compFlag, id, vram);
		*pltt = NULL;
		break;
	case CLACT_U_PLTT_RES:
		loadPlttHeaderCoreArc(buff, srcFile, dataIdx, compFlag, id, vram, pltt);
		break;
	case CLACT_U_CELL_RES:
	case CLACT_U_CELLANM_RES:
	case CLACT_U_MULTI_RES:
	case CLACT_U_MULTIANM_RES:
		loadKindCellHeaderCoreArc(buff, srcFile, dataIdx, compFlag, id);
		*vram = NULL;
		*pltt = NULL;
		break;
	default:
		GF_ASSERT_MSG(0, "�s���ȃt�H�[�}�b�g�ł�\n");
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�f�[�^�ǂݍ���
 *
 *@param	buff		�w�b�_�[�f�[�^
 *@param	srcFile		�A�[�J�C�u�t�@�C��ID
 *@param	dataIdx		�f�[�^�C���f�b�N�X
 *@param	compFlag	���k�t���O
 *@param	id			�Ǘ�ID
 *@param	type		Vram�^�C�v
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadCharHeaderCoreArc(char* buff, char** srcFile, char** dataIdx, char** compFlag, char** id, char** type)
{
	*srcFile	= strtok(buff, ",");
	*dataIdx	= strtok(NULL, ",");
	*compFlag	= strtok(NULL, ",");
	*id			= strtok(NULL, ",");
	*type		= strtok(NULL, ",");
	strtok(NULL, "\n");
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�A�[�J�C�u�p�p���b�g�w�b�_�[�f�[�^�ǂݍ���
 *
 *@param	buff		�w�b�_�[�f�[�^
 *@param	srcFile		�A�[�J�C�u�t�@�C��ID
 *@param	dataIdx		�f�[�^�C���f�b�N�X
 *@param	compFlag	���k�t���O
 *@param	id			�Ǘ�ID
 *@param	type		Vram�^�C�v
 *@param	pltt_num	�p���b�g�g�p��
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadPlttHeaderCoreArc(char* buff, char** srcFile, char** dataIdx, char** compFlag, char** id, char** type, char** pltt_num)
{
	*srcFile	= strtok(buff, ",");
	*dataIdx	= strtok(NULL, ",");
	*compFlag	= strtok(NULL, ",");
	*id			= strtok(NULL, ",");
	*type		= strtok(NULL, ",");
	*pltt_num	= strtok(NULL, ",");
	strtok(NULL, "\n");
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�Z���A�j���A�}���`�Z���A�}���`�Z���A�j��
			�A�[�J�C�u�t�@�C���p�ǂݍ���
 *
 *@param	buff		�w�b�_�[�f�[�^
 *@param	srcFile		�A�[�J�C�u�t�@�C��ID
 *@param	dataIdx		�f�[�^�C���f�b�N�X
 *@param	compFlag	���k�t���O
 *@param	id			�Ǘ�ID
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadKindCellHeaderCoreArc(char* buff, char** srcFile, char** dataIdx, char** compFlag, char** id)
{
	*srcFile	= strtok(buff, ",");
	*dataIdx	= strtok(NULL, ",");
	*compFlag	= strtok(NULL, ",");
	*id			= strtok(NULL, ",");
	strtok(NULL, "\n");
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�w�b�_�Ƀf�[�^���i�[
 *
 *@param	head		�i�[��w�b�_
 *@param	srcFile		�A�[�J�C�u�t�@�C��ID
 *@param	dataIdx		�f�[�^�C���f�b�N�X
 *@param	compFlag	���k�t���O
 *@param	id			�Ǘ�ID
 *@param	type		Vram�^�C�v
 *@param	pltt_num	�p���b�g�g�p��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setDataHeaderArc(CLACT_U_RES_HEADER_SUBARC* head, char* arcFile, char* dataIdx, char* compFlag, char* id, char* type, char* pltt_num)
{
	head->arcFile	= atoi(arcFile);
	head->dataIdx	= atoi(dataIdx);
	head->compFlag	= atoi(compFlag);
	head->id		= atoi(id);
	if(type){
		head->ex[0]		= atoi(type);
	}else{
		head->ex[0]		= 0;
	}
	if(pltt_num){
		head->ex[1]		= atoi(pltt_num);
	}else{
		head->ex[1]		= 0;
	}
}

//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�̓ǂݏo���i�������m�ۂ���j
 *
 * @param	p_handle		�A�[�J�C�u�n���h��
 * @param   dataIdx			�A�[�J�C�u�f�[�^�C���f�b�N�X
 * @param   compressedFlag	���k����Ă��邩�H
 * @param	heapID			�g�p����q�[�v
 * @param	alloc_type		�A���b�N�^�C�v
 *
 * @retval  void*			�ǂݏo���̈�|�C���^
 */
//------------------------------------------------------------------
static void* ArcHandle_Load(ARCHANDLE* p_handle, u32 dataIdx, BOOL compressedFlag, u32 heapID, u32 alloc_type)
{
	void* arcData;
	
	arcData = ArchiveDataLoadAllocByHandle( p_handle, dataIdx, heapID );

	if( arcData != NULL )
	{
		if( compressedFlag )
		{
			void* data;

			if( alloc_type == ALLOC_TOP ){
				data = sys_AllocMemory( heapID, MI_GetUncompressedSize( arcData ) );
			}else{
				data = sys_AllocMemoryLo( heapID, MI_GetUncompressedSize( arcData ) );
			}

			if( data )
			{
				MI_UncompressLZ8( arcData, data );
				sys_FreeMemoryEz( arcData );
			}
			arcData = data;
		}
	}

	return arcData;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�b�t�@�̃R�s�[���쐬
 *
 *@param	buff	�R�s�[����o�b�t�@
 *@param	heap	�g�p����q�[�v
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
char* makeCopyStr(const char* buff, int heap)
{
	int size;
	char* copy;

	size = strlen(buff);
	size++;

	copy = sys_AllocMemoryLo(heap, size);
	strcpy(copy, buff);

	return copy;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�R�s�[��j��
 *
 *@param	copy	�R�s�[
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void delCopyStr(char* copy)
{
	sys_FreeMemoryEz(copy);
}
