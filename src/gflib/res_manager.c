//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		res_manager.c
 *@brief	���\�[�X�Ǘ��}�l�[�W���[
 *@author	tomoya takahashi
 *@data		2005.08.29
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "nnsys.h"
#include "system.h"
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define __RES_MANAGER_H_GLOBAL
#include "res_manager.h"

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
//	���\�[�X�w�b�_�[�X�̃f�[�^
//
//	�o�^�f�[�^���܂Ƃ߂��f�[�^�ł�
//	
//=====================================
typedef struct _RES_HEADER_SUB{
	int		id;				// �Ǘ�ID
	char	file_path[64];	// �t�@�C���p�X
} RES_HEADER_SUB;

//-------------------------------------
//	
//	���\�[�X�w�b�_�[�̃f�[�^
//
//	�X�̃f�[�^���܂Ƃ߂��f�[�^
//	
//=====================================
typedef struct _RES_HEADER{
	RES_HEADER_SUB* tbl;	// �X�̃f�[�^�e�[�u��
	int				num;	// �e�[�u����
} RES_HEADER;


//-------------------------------------
//	
//	�ǂݍ��܂ꂽ���\�[�X�̃f�[�^
//	
//=====================================
typedef struct _RES_OBJ{
	int		id;		// �Ǘ�ID
	void*	p_res;	// ���\�[�X�|�C���^
} RES_OBJ;

//-------------------------------------
//	
//	���\�[�X�Ǘ��}�l�[�W���[
//	�Ǘ��f�[�^�\����
//	
//=====================================
typedef struct _RES_MANAGER{
	RES_OBJ*	p_work;		// ���\�[�X�i�[�e�[�u��
	int			max;		// �\�i�[��
	int			now;		// ���݊i�[��
} RES_MANAGER;





//-----------------------------------------------------------------------------
/**
*		�e�N�X�`�����\�[�X����}�l�[�W��
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�e�N�X�`�����\�[�X�I�u�W�F
//	
//=====================================
typedef struct _TEXRES_OBJ{
	RES_OBJ*		resobj;		// ���\�[�X�I�u�W�F
	NNSGfdTexKey	texKey;		// �e�N�X�`���L�[
	NNSGfdTexKey	tex4x4Key;	// 4x4�e�N�X�`���L�[
	NNSGfdPlttKey	plttKey;	// �p���b�g�L�[
	void*			p_cutTex;	// �e�N�X�`�����f�[�^�j���p���\�[�X
	u16				cut_flag;	// �e�N�X�`�����f�[�^��j��������
	u16				cuttex_flag;// �e�N�X�`���J�b�g�̗L��
} TEXRES_OBJ;

//-------------------------------------
//	
//	�e�N�X�`�����\�[�X�}�l�[�W��
//	
//=====================================
typedef struct _TEXRES_MANAGER{
	RES_MANAGER*	resm;	// ���\�[�X�}�l�[�W��
	TEXRES_OBJ*		tobj;	// �e�N�X�`���I�u�W�F�f�[�^
} TEXRES_MANAGER;





//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static RES_OBJ_PTR getCleanRES_OBJ(RES_MANAGER_PTR resm);
static void clean_RES_OBJ(RES_OBJ* data);
static int getHeaderNum(char* buff);
static void getHeaderData(char* buff, RES_HEADER_SUB* data, int num);
static void getOneData(char* buff, char** file_path, char** id);
static void setOneData(char* file_path, char* id, RES_HEADER_SUB* data);
static char* makeCopyStr(const char* buff, int heap);
static void delCopyStr(char* copy);


//-----------------------------------------------------------------------------
/**
*	�e�N�X�`������}�l�[�W��
*/
//-----------------------------------------------------------------------------
static TEXRES_OBJ_PTR getCleanTEXRES_OBJ(CONST_TEXRES_MANAGER_PTR resm);
static void cleanTEXRES_OBJ(TEXRES_OBJ_PTR obj);
static void getVramkey( const NNSG3dResTex* res, NNSGfdTexKey* tex, NNSGfdTexKey* tex4x4, NNSGfdPlttKey* pltt );
static NNSG3dResTex* getTexRes( CONST_TEXRES_OBJ_PTR r_obj );
static NNSG3dResTex* getTexRes_CheckCutTex( CONST_TEXRES_OBJ_PTR r_obj );
static void loadTexRes( NNSG3dResTex* res, TEXRES_OBJ_PTR r_obj );
static void setTexkeyRes( NNSG3dResTex* res, NNSGfdTexKey tex, NNSGfdTexKey tex4x4, NNSGfdPlttKey pltt );
static void releaseTexkeyRes( NNSG3dResTex* res );

// �e�N�X�`�����\�[�X���폜����NNSG3dResTex���쐬����֐��S
static void* MakeCutTexWork( void* p_cuttex, u32 heap );
static u32 GetCutTexDataSize( const void* p_cuttex );

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�Ǘ��}�l�[�W���[���ԕ��쐬
 *
 *@param	num		�f�[�^�Ǘ��e�[�u����
 *
 *@return	RES_MANAGER_PTR		�Ǘ��f�[�^�|�C���^
 *
 * ���Ǘ��e�[�u���̈�̊m��
 * ���Ǘ��e�[�u���̈�̏�����
 *
 */
//-----------------------------------------------------------------------------
RES_MANAGER_PTR RESM_Init(int num, int heap)
{
	RES_MANAGER_PTR resm;
	int i;		// ���[�v�p

	// ���\�[�X�Ǘ��}�l�[�W���[�쐬
	resm = sys_AllocMemory(heap, sizeof(RES_MANAGER));
	GF_ASSERT(resm);
	
	// �Ǘ��e�[�u���쐬
	resm->p_work = sys_AllocMemory(heap, sizeof(RES_OBJ)*num);
	GF_ASSERT(resm->p_work);
	for(i=0;i<num;i++){
		clean_RES_OBJ( (resm->p_work + i) );
	}


	resm->max	= num;		// �ő吔
	resm->now	= 0;		// ���ݓo�^��

	return resm;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�Ǘ��f�[�^�j��
 *
 *@param	resm	���\�[�X�Ǘ��f�[�^
 *
 *@return	none
 *
 *	���ǂݍ��񂾃��\�[�X��j��
 *	���Ǘ��e�[�u���̈��j��
 */
//-----------------------------------------------------------------------------
void RESM_Delete(RES_MANAGER_PTR resm)
{
	GF_ASSERT(resm);
	
	// �o�^����Ă��郊�\�[�X��S�Ĕj��
	RESM_DeleteAllRes(resm);

	// �������j��
	sys_FreeMemoryEz(resm->p_work);
	sys_FreeMemoryEz(resm);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�c��o�^�\�����擾
 *
 *@param	resm	�擾���郊�\�[�X�Ǘ��f�[�^
 *
 *@return	int		�c��o�^�\��
 *
 *
 */
//-----------------------------------------------------------------------------
int RESM_GetRest(RES_MANAGER_PTR resm)
{
	GF_ASSERT(resm);

	return ( resm->max - resm->now );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ID���d�����Ȃ������擾
 *
 *@param	resm	�擾���郊�\�[�X�Ǘ��f�[�^
 *@param	id		�`�F�b�N����ID
 *
 *@retval	TRUE	�d�����Ȃ�
 *@retval	FALSE	�d������
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL RESM_CheckID(RES_MANAGER_PTR resm, int id)
{
	int i;		// ���[�v�p
	
	GF_ASSERT(resm);

	// ID�������e�[�u�������邩�`�F�b�N
	if( RESM_GetResObj(resm, id) == NULL ){
		// �����e�[�u���������̂�,�d�����Ȃ�
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	
 *@brief	���\�[�X�̓o�^
 *
 *@param	resm	�o�^���郊�\�[�X�Ǘ��f�[�^�|�C���^
 *@param	res		���\�[�X
 *@param	id		�o�^ID	�i���d�����Ӂj
 *
 *@retval	RES_OBJ_PTR	�o�^����
 *@retval	NULL		�o�^���s	�o�^�e�[�u�������t
 *
 * ���p�X�̃��\�[�X��ǂݍ���ŁA�Ǘ��f�[�^�ɐݒ�
 *
 */
//-----------------------------------------------------------------------------
RES_OBJ_PTR RESM_AddResNormal(RES_MANAGER_PTR resm, void* res, int id)
{
	RES_OBJ_PTR r_obj;
	
	GF_ASSERT(resm);

	// �󂢂Ă���e�[�u�����擾
	r_obj = getCleanRES_OBJ(resm);
	GF_ASSERT(r_obj && ("�e�[�u���ɋ󂫂�����"));

	// ID���d�����Ȃ����`�F�b�N
	GF_ASSERT( (RESM_CheckID(resm, id) == TRUE) );

	// ���\�[�X�ǂݍ���
	r_obj->p_res = res;

	r_obj->id = id;	// �o�^ID

	resm->now++;	// �e�[�u���o�^���ǉ�

	return r_obj;
}

//----------------------------------------------------------------------------
/**
 *	
 *@brief	���\�[�X�̓o�^
 *
 *@param	resm	�o�^���郊�\�[�X�Ǘ��f�[�^�|�C���^
 *@param	p_path	���\�[�X�̃p�X
 *@param	id		�o�^ID	�i���d�����Ӂj
 *@param	heap	���\�[�X�ǂݍ��݂Ɏg�p����q�[�v
 *
 *@retval	RES_OBJ_PTR	�o�^����
 *
 * ���p�X�̃��\�[�X��ǂݍ���ŁA�Ǘ��f�[�^�ɐݒ�
 *
 */
//-----------------------------------------------------------------------------
RES_OBJ_PTR RESM_AddRes(RES_MANAGER_PTR resm, const char* p_path, int id, int heap)
{
	RES_OBJ_PTR r_obj;
	
	GF_ASSERT(resm);
	GF_ASSERT(p_path);

	// �󂢂Ă���e�[�u�����擾
	r_obj = getCleanRES_OBJ(resm);
	GF_ASSERT(r_obj && ("�e�[�u���ɋ󂫂�����"));

	// ID���d�����Ȃ����`�F�b�N
	GF_ASSERT( (RESM_CheckID(resm, id) == TRUE) );

	// ���\�[�X�ǂݍ���
	r_obj->p_res = sys_LoadFile(heap, p_path);
	GF_ASSERT(r_obj->p_res && ("�p�X���Ԉ���Ă��܂�"));

	r_obj->id = id;	// �o�^ID

	resm->now++;	// �e�[�u���o�^���ǉ�

	return r_obj;
}

//----------------------------------------------------------------------------
/**
 *	
 *@brief	�w�b�_�[���g�p�������\�[�X�̓o�^�i�P���j
 *
 *@param	resm	�o�^���郊�\�[�X�Ǘ��f�[�^�|�C���^
 *@param	header	���\�[�X�w�b�_�[�|�C���^
 *@param	no		���Ԗڂ�o�^���邩
 *@param	heap	���\�[�X�ǂݍ��݂Ɏg�p����q�[�v
 *
 *@retval	RES_OBJ_PTR	�o�^����
 *
 * ���p�X�̃��\�[�X��ǂݍ���ŁA�Ǘ��f�[�^�ɐݒ�
 *
 */
//-----------------------------------------------------------------------------
RES_OBJ_PTR RESM_AddResHd(RES_MANAGER_PTR resm, const RES_HEADER_PTR header, int no, int heap)
{
	GF_ASSERT(resm);
	GF_ASSERT(header);

	// �v�f���ȉ����`�F�b�N
	GF_ASSERT(header->num > no);
	
	return RESM_AddRes(resm, header->tbl[no].file_path, header->tbl[no].id, heap);
}

//----------------------------------------------------------------------------
/**
 *	
 *@brief	�w�b�_�[���g�p�������\�[�X�̓o�^�i�����j
 *
 *@param	resm	�o�^���郊�\�[�X�Ǘ��f�[�^�|�C���^
 *@param	header	���\�[�X�w�b�_�[�|�C���^
 *@param	heap	���\�[�X�ǂݍ��݂Ɏg�p����q�[�v
 *
 *@return	none
 *
 * ���p�X�̃��\�[�X��ǂݍ���ŁA�Ǘ��f�[�^�ɐݒ�
 *
 */
//-----------------------------------------------------------------------------
void RESM_AddResHds(RES_MANAGER_PTR resm, const RES_HEADER_PTR header, int heap)
{
	GF_ASSERT(resm);
	GF_ASSERT(header);
	
	RESM_AddResHdsEx(resm, header, 0, header->num, heap);
}

//----------------------------------------------------------------------------
/**
 *	
 *@brief	�w�b�_�[���g�p�������\�[�X�̓o�^�i�����j
 *			�w�b�_�[�̊J�n�v�f�A�I���v�f���w��
 *
 *@param	resm	�o�^���郊�\�[�X�Ǘ��f�[�^�|�C���^
 *@param	header	���\�[�X�w�b�_�[�|�C���^
 *@param	start	�J�n�v�f��
 *@param	num		�o�^�v�f��
 *@param	heap	���\�[�X�ǂݍ��݂Ɏg�p����q�[�v
 *
 *@return	noen
 *
 * ���p�X�̃��\�[�X��ǂݍ���ŁA�Ǘ��f�[�^�ɐݒ�
 *
 */
//-----------------------------------------------------------------------------
void RESM_AddResHdsEx(RES_MANAGER_PTR resm, const RES_HEADER_PTR header, int start, int num, int heap)
{
	int i;
	
	GF_ASSERT(resm);
	GF_ASSERT(header);

	// �v�f���I�[�o�[���Ȃ����`�F�b�N
	GF_ASSERT((start+num) <= header->num)

	for(i=start;i<(start+num);i++){
		RESM_AddResHd(resm, header, i, heap);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�̔j��
 *
 *@param	resm	�j�����郊�\�[�X���o�^����Ă���Ǘ��f�[�^�|�C���^
 *@param	r_obj	�j�����郊�\�[�X�I�u�W�F
 *
 * ���ǂݍ��񂾃��\�[�X��j�����A�Ǘ��f�[�^��������
 */
//-----------------------------------------------------------------------------
void RESM_DeleteRes(RES_MANAGER_PTR resm, RES_OBJ_PTR r_obj)
{
	GF_ASSERT(resm);
	GF_ASSERT(r_obj);

	if( r_obj->p_res ){
		sys_FreeMemoryEz(r_obj->p_res);
		r_obj->p_res = NULL;
	}
	r_obj->id = RES_MANAGER_ID_NONE;

	resm->now--;	// �e�[�u���o�^�����Z
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ID�Ń��\�[�X�̔j��
 *
 *@param	resm	�j�����郊�\�[�X���o�^����Ă���Ǘ��f�[�^�|�C���^
 *@param	id		�j�����郊�\�[�X��ID
 *
 * ���ǂݍ��񂾃��\�[�X��j�����A�Ǘ��f�[�^��������
 */
//-----------------------------------------------------------------------------
void RESM_DeleteResID(RES_MANAGER_PTR resm, int id)
{
	RES_OBJ_PTR	data;

	GF_ASSERT(resm);
	data = RESM_GetResObj(resm, id);
	GF_ASSERT( data && ("ID�̃f�[�^�͂���܂���B"));

	// �j��
	RESM_DeleteRes(resm, data);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�S���\�[�X�̔j��
 *
 *@param	resm	�j�����郊�\�[�X���o�^����Ă���Ǘ��f�[�^�|�C���^
 *
 * ���ǂݍ��񂾃��\�[�X��j�����A�Ǘ��f�[�^��������
 */
//-----------------------------------------------------------------------------
void RESM_DeleteAllRes(RES_MANAGER_PTR resm)
{
	int i;	// ���[�v�p
	
	GF_ASSERT(resm);
	GF_ASSERT(resm->p_work);
	
	for(i=0; i<resm->max;i++){
		if( resm->p_work[i].id != RES_MANAGER_ID_NONE ){
			RESM_DeleteRes(resm, (resm->p_work + i));
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�N�g�f�[�^�|�C���^���擾
 *
 *@param	resm		���\�[�X�Ǘ��f�[�^
 *@param	id			���\�[�X��ID
 *
 *@retval	NULL		�o�^����Ă��Ȃ�
 *@retval	RES_OBJ_PTR	�o�^����Ă��郊�\�[�X�I�u�W�F�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
RES_OBJ_PTR RESM_GetResObj(RES_MANAGER_PTR resm, int id)
{
	int i;	// ���[�v�p
	GF_ASSERT(resm);

	for(i = 0;i < resm->max; i++){
		if(resm->p_work[i].id == id){
			return (resm->p_work + i);
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�^����Ă��郊�\�[�X�f�[�^���擾
 *
 *@param	r_obj		���\�[�X�I�u�W�F
 *
 *@retval	NULL		�o�^����Ă��Ȃ�
 *@retval	NULL�ȊO	�o�^����Ă��郊�\�[�X�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
void* RESM_GetRes(RES_OBJ_PTR r_obj)
{
	GF_ASSERT(r_obj);

	return r_obj->p_res;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�^����Ă��郊�\�[�X�f�[�^��ύX
 *
 *@param	r_obj		���\�[�X�I�u�W�F
 *
 *@param	�o�^����Ă��郊�\�[�X�f�[�^�ύX
 *
 */
//-----------------------------------------------------------------------------
void RESM_SetRes(RES_OBJ_PTR r_obj, void* res)
{
	GF_ASSERT(r_obj);

	if( r_obj->p_res ){
		sys_FreeMemoryEz(r_obj->p_res);
	}
	r_obj->p_res = res;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�^����Ă���ID���擾
 *
 *@param	r_obj		���\�[�X�I�u�W�F
 *
 *@retval	int			ID
 *
 *
 */
//-----------------------------------------------------------------------------
int RESM_GetID(RES_OBJ_PTR r_obj)
{
	GF_ASSERT(r_obj);

	return r_obj->id;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�^����Ă���ID��ݒ�
 *
 *@param	r_obj		���\�[�X�I�u�W�F
 *@param	id			�ݒ肷��ID
 *
 *@retval	none
 *
 *
 */
//-----------------------------------------------------------------------------
void RESM_SetID(RES_MANAGER_PTR resm, RES_OBJ_PTR r_obj, int id)
{
	GF_ASSERT(resm);
	GF_ASSERT(r_obj);
	GF_ASSERT( RESM_CheckID(resm, id) );	// �d�����Ȃ����`�F�b�N

	r_obj->id = id;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�󂢂Ă���I�u�W�F���擾
 *	
 *@param	none
 *
 *@retval	RES_OBJ_PTR	�󂢂Ă���I�u�W�F
 *@retval	NULL		�󂢂Ă��Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
static RES_OBJ_PTR getCleanRES_OBJ(RES_MANAGER_PTR resm)
{
	int i;
	GF_ASSERT(resm);

	for(i=0;i<resm->max;i++){
		if(resm->p_work[i].id == RES_MANAGER_ID_NONE){
			return resm->p_work + i;
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�̏�����
 *
 *@param	data	�f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void clean_RES_OBJ(RES_OBJ* data)
{
	GF_ASSERT(data);
	data->id	= RES_MANAGER_ID_NONE;
	data->p_res = NULL;
}

//-----------------------------------------------------------------------------
//
//		*********** �w�b�_�[�p�֐� **************
//
//=============================================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	�w�b�_�[�T�C�Y���擾
 *
 *@param	none	
 *
 *@return	int		�w�b�_�[�̃o�C�g�T�C�Y
 *
 *
 */
//-----------------------------------------------------------------------------
int RESM_GetHeaderSize(void)
{
	return sizeof(RES_HEADER);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�w�b�_�[�z�񂩂�v�f���̃f�[�^��Ԃ�
 *
 *@param	tbl		�z��ɂȂ��Ă���w�b�_�[
 *@param	no		�v�f��
 *
 *@return	RES_HEADER_PTR data[no] �̃A�h���X
 *
 *
 */
//-----------------------------------------------------------------------------
RES_HEADER_PTR RESM_GetTbl(RES_HEADER_PTR tbl, int no)
{
	GF_ASSERT(tbl);
	return ( tbl + no );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�w�b�_�[�̓ǂݍ���
 *
 *@param	header			�w�b�_�[�f�[�^�i�[��
 *@param	rom_path		�w�b�_�[�t�@�C���p�X
 *@param	heap			�Ё[��ID 
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void RESM_HeaderLoad(RES_HEADER_PTR header, const char* rom_path, int heap)
{
	char* tmp;				// ����p
	char* buff;				// �t�@�C���f�[�^
	int	i;					// ���[�v�p

	GF_ASSERT(header);		// �w�b�_�[�̈���m�ۂ��Ă�������
	GF_ASSERT(rom_path);


	// �t�@�C���I�[�v��
	tmp = sys_LoadFile(heap, rom_path);
	GF_ASSERT(tmp&&("�w�b�_�[�ǂݍ��ݎ��s"))

	// ���[�N�o�b�t�@
	buff = makeCopyStr(tmp, heap);
	
	// �t�@�C�������擾
	header->num = getHeaderNum(buff);

	// �������m��
	header->tbl = sys_AllocMemory(heap, sizeof(RES_HEADER_SUB)*header->num);
	GF_ASSERT(header->tbl);

	// ���[�N�o�b�t�@�ɑ��
	delCopyStr(buff);	// ��������j��
	buff = makeCopyStr(tmp, heap);

	// �f�[�^�ǂݍ���
	getHeaderData(buff, header->tbl, header->num);

	// �ǂݍ��݃t�@�C���j��
	delCopyStr(buff);
	sys_FreeMemoryEz(tmp);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�w�b�_�[�̔j��
 *
 *@param	header			�w�b�_�[�f�[�^�f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void RESM_HeaderFree(RES_HEADER_PTR header)
{
	GF_ASSERT(header);
	GF_ASSERT(header->tbl);
	
	sys_FreeMemoryEz(header->tbl);
	header->tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�^�f�[�^�����擾
 *
 *@param	buff	�o�b�t�@
 *
 *@return	int		�f�[�^��
 *
 *
 */
//-----------------------------------------------------------------------------
static int getHeaderNum(char* buff)
{
	int count;			// �f�[�^���J�E���g
	char* file_path;	// �t�@�C���p�X
	char* id;			// �t�@�C���p�X


	count = 0;
	getOneData(buff, &file_path, &id);	// �P�̃f�[�^�i�[
	// �p�X��'0'�̃f�[�^���I�[
	while(file_path[0] != '0'){
		count++;

		getOneData(NULL, &file_path, &id);	// �P��ڈȍ~��NULL��OK

		if(file_path == NULL){
			GF_ASSERT(0);		// �I�[�R�[�h������
		}
	}

	return count;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�f�[�^�i�[
 *
 *@param	buff	���݂̃t�@�C���|�C���^
 *@param	data	�f�[�^�i�[��
 *@param	num		��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void getHeaderData(char* buff, RES_HEADER_SUB* data, int num)
{
	int i;		// ���[�v�p
	char* file_path;	// �t�@�C���p�X
	char* id;			// �t�@�C���p�X

	getOneData(buff, &file_path, &id);	// �P�̃f�[�^�i�[
	setOneData(file_path, id, &data[0]);
	for(i=1;i<num;i++){
		getOneData(NULL, &file_path, &id);	// �P�̃f�[�^�i�[
		setOneData(file_path, id, &data[i]);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�P�̃f�[�^�擾
 *
 *@param	buff		�ŏ��ȊO��NULL
 *@param	file_path	�t�@�C���p�X
 *@param	id			ID
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void getOneData(char* buff, char** file_path, char** id)
{
	*file_path	= strtok(buff, ", \n");
	*id			= strtok(NULL, ", \n");
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�P�̃f�[�^��ݒ�
 *
 *@param	fiel_path	�t�@�C���p�X
 *@param	id			id
 *@param	data		�i�[��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setOneData(char* file_path, char* id, RES_HEADER_SUB* data)
{
	data->id		= atoi(id);
	strcpy(data->file_path, file_path);
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
static char* makeCopyStr(const char* buff, int heap)
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
static void delCopyStr(char* copy)
{
	sys_FreeMemoryEz(copy);
}






//-----------------------------------------------------------------------------
/**
*
*	�e�N�X�`���Ǘ����\�[�X�}�l�[�W��
* 
*/
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�Ǘ��}�l�[�W���[���ԕ��쐬
 *
 *@param	num		�f�[�^�Ǘ��e�[�u����
 *
 *@return	TEXRES_MANAGER_PTR		�Ǘ��f�[�^�|�C���^
 *
 * ���Ǘ��e�[�u���̈�̊m��
 * ���Ǘ��e�[�u���̈�̏�����
 *
 */
	//-----------------------------------------------------------------------------
TEXRES_MANAGER_PTR TEXRESM_Init(int num, int heap)
{
	TEXRES_MANAGER_PTR resm;
	int i;
	
	resm		= sys_AllocMemory( heap, sizeof(TEXRES_MANAGER) );
	
	resm->resm	= RESM_Init( num, heap );

	resm->tobj	= sys_AllocMemory( heap, sizeof(TEXRES_OBJ) * num );

	for(i=0;i<num;i++){
		cleanTEXRES_OBJ( resm->tobj + i );
	}

	return resm;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�Ǘ��f�[�^�j��
 *
 *@param	resm	���\�[�X�Ǘ��f�[�^
 *
 *@return	none
 *
 *	���ǂݍ��񂾃��\�[�X��j��
 *	���Ǘ��e�[�u���̈��j��
 */
//-----------------------------------------------------------------------------
void TEXRESM_Delete(TEXRES_MANAGER_PTR resm)
{
	GF_ASSERT(resm);
	
	// �o�^����Ă��郊�\�[�X�j��
	TEXRESM_DeleteAllRes( resm );
	
	// �g�p���Ă������\�[�X�}�l�[�W���j��
	RESM_Delete( resm->resm );
	
	sys_FreeMemoryEz( resm->tobj );
	sys_FreeMemoryEz( resm );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�c��o�^�\�����擾
 *
 *@param	resm	�擾���郊�\�[�X�Ǘ��f�[�^
 *
 *@return	int		�c��o�^�\��
 *
 *
 */
//-----------------------------------------------------------------------------
int TEXRESM_GetRest(CONST_TEXRES_MANAGER_PTR resm)
{
	GF_ASSERT(resm);

	return RESM_GetRest( resm->resm );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ID���d�����Ȃ������擾
 *
 *@param	resm	�擾���郊�\�[�X�Ǘ��f�[�^
 *@param	id		�`�F�b�N����ID
 *
 *@retval	TRUE	�d�����Ȃ�
 *@retval	FALSE	�d������
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL TEXRESM_CheckID(CONST_TEXRES_MANAGER_PTR resm, int id)
{
	GF_ASSERT(resm);

	return RESM_CheckID( resm->resm, id );
}

//----------------------------------------------------------------------------
/**
 *	
 *@brief	���\�[�X�̓o�^
 *
 *@param	resm	�o�^���郊�\�[�X�Ǘ��f�[�^�|�C���^
 *@param	res		���\�[�X
 *@param	id		�o�^ID	�i���d�����Ӂj
 *@param	texcut_flg	�e�N�X�`���J�b�g�@�L���@�t���O
 *@param	heap		�e�N�X�`���J�b�g���[�N�@�q�[�v
 *
 *@retval	TEXRES_OBJ_PTR	�o�^����
 *@retval	NULL		�o�^���s	�o�^�e�[�u�������t
 *
 * ���p�X�̃��\�[�X��ǂݍ���ŁA�Ǘ��f�[�^�ɐݒ�
 *
 */
//-----------------------------------------------------------------------------
TEXRES_OBJ_PTR TEXRESM_AddResNormal(CONST_TEXRES_MANAGER_PTR resm, void* res, int id, u32 texcut_flg, u32 heap)
{
	TEXRES_OBJ_PTR tobj;
	void * buff;

	GF_ASSERT(resm);	
	tobj = getCleanTEXRES_OBJ( resm );

	// �e�N�X�`�����f�[�^�j���L���t���O
	tobj->cuttex_flag = texcut_flg;
	
	// �e�N�X�`�����f�[�^�j���̗L������
	// �e�N�X�`�����f�[�^�j����̃f�[�^�T�C�Y�̃��[�N���쐬
	if( tobj->cuttex_flag == TEXRESM_TEX_CUT_TRUE ){
		// �e�N�X�`�����f�[�^�j�����ꂽ�e�N�X�`�����\�[�X�f�[�^���쐬
		buff = MakeCutTexWork( res, heap );
		tobj->p_cutTex = res;
	}else{
		// �e�N�X�`���j�����Ȃ��Ƃ���res�����̂܂ܐݒ�
		buff = res;
		tobj->p_cutTex = NULL;
	}
	tobj->resobj = RESM_AddResNormal( resm->resm, buff, id );

	return tobj;
}

//----------------------------------------------------------------------------
/**
 *	
 *@brief	���\�[�X�̓o�^��VramKey�̎擾���s��
 *
 *@param	resm	�o�^���郊�\�[�X�Ǘ��f�[�^�|�C���^
 *@param	res		���\�[�X
 *@param	id		�o�^ID	�i���d�����Ӂj
 *@param	texcut_flg	�e�N�X�`���J�b�g�@�L���@�t���O
 *@param	heap	���\�[�X�ǂݍ��݂Ɏg�p����q�[�v
 *
 *@retval	TEXRES_OBJ_PTR	�o�^����
 *@retval	NULL		�o�^���s	�o�^�e�[�u�������t
 *
 * �������̗���
 *	�P�F�p�X�̃��\�[�X��ǂݍ���
 *	�Q�FVramKey���擾
 */
//-----------------------------------------------------------------------------
TEXRES_OBJ_PTR TEXRESM_AddAndAllocVramKeyResNormal(TEXRES_MANAGER_PTR resm, void* res, int id, u32 texcut_flg, int heap)
{
	TEXRES_OBJ_PTR tobj;

	// ���\�[�X�}�l�[�W���ɓo�^
	tobj = TEXRESM_AddResNormal( resm, res, id, texcut_flg, heap );

	// VramKey�̎擾
	TEXRESM_AllocVramKeyPTR( tobj );
	
	return tobj;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�̔j��
 *
 *@param	resm	�j�����郊�\�[�X���o�^����Ă���Ǘ��f�[�^�|�C���^
 *@param	r_obj	�j�����郊�\�[�X�I�u�W�F
 *
 * ���ǂݍ��񂾃��\�[�X��j�����A�Ǘ��f�[�^��������
 */
//-----------------------------------------------------------------------------
void TEXRESM_DeleteRes(TEXRES_MANAGER_PTR resm, TEXRES_OBJ_PTR r_obj)
{
	int check;
	
	GF_ASSERT(resm);	
	GF_ASSERT(r_obj);

	// �e�N�X�`���J�b�g�p�̃��\�[�X�Ȃ̂Ƀe�N�X�`���J�b�g����Ă��Ȃ��Ƃ�
	// �̏���
	if( (r_obj->cuttex_flag == TEXRESM_TEX_CUT_TRUE) &&
		(r_obj->cut_flag == FALSE) ){
		sys_FreeMemoryEz( r_obj->p_cutTex );
		r_obj->cuttex_flag = NULL;
	}
	
	if(r_obj->resobj){
		RESM_DeleteRes( resm->resm, r_obj->resobj );
	}

	// �e�N�X�`���L�[������Ƃ��͔j��
	if(r_obj->texKey != NNS_GFD_ALLOC_ERROR_TEXKEY){
		check = NNS_GfdFreeTexVram( r_obj->texKey );
		GF_ASSERT_MSG(check == 0, "�e�N�X�`���L�[�j�����s");
	}
	if(r_obj->tex4x4Key != NNS_GFD_ALLOC_ERROR_TEXKEY){
		check = NNS_GfdFreeTexVram( r_obj->tex4x4Key );
		GF_ASSERT_MSG(check == 0, "�e�N�X�`���L�[�j�����s");
	}
	// �p���b�g�L�[�j��
	if(r_obj->plttKey != NNS_GFD_ALLOC_ERROR_PLTTKEY){
		check = NNS_GfdFreePlttVram( r_obj->plttKey );
		GF_ASSERT_MSG(check == 0, "�p���b�g�L�[�j�����s");
	}

	cleanTEXRES_OBJ( r_obj );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ID�Ń��\�[�X�̔j��
 *
 *@param	resm	�j�����郊�\�[�X���o�^����Ă���Ǘ��f�[�^�|�C���^
 *@param	id		�j�����郊�\�[�X��ID	(�Ǘ�ID)
 *
 * ���ǂݍ��񂾃��\�[�X��j�����A�Ǘ��f�[�^��������
 */
//-----------------------------------------------------------------------------
void TEXRESM_DeleteResID(TEXRES_MANAGER_PTR resm, int id)
{
	TEXRES_OBJ_PTR tobj;
	GF_ASSERT( resm );

	tobj = TEXRESM_GetResObj( resm, id );

	TEXRESM_DeleteRes( resm, tobj );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�S���\�[�X�̔j��
 *
 *@param	resm	�j�����郊�\�[�X���o�^����Ă���Ǘ��f�[�^�|�C���^
 *
 * ���ǂݍ��񂾃��\�[�X��j�����A�Ǘ��f�[�^��������
 */
//-----------------------------------------------------------------------------
void TEXRESM_DeleteAllRes(TEXRES_MANAGER_PTR resm)
{
	int i;		// ���[�v�p
	GF_ASSERT(resm);
	GF_ASSERT(resm->tobj);
	
	for( i = 0; i < resm->resm->max; i++ ){
		if(resm->tobj[ i ].resobj){
			TEXRESM_DeleteRes( resm, resm->tobj + i );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�N�g�f�[�^�|�C���^���擾
 *
 *@param	resm		���\�[�X�Ǘ��f�[�^
 *@param	id			���\�[�X��ID	(�Ǘ�ID)
 *
 *@retval	NULL		�o�^����Ă��Ȃ�
 *@retval	TEXRES_OBJ_PTR	�o�^����Ă��郊�\�[�X�I�u�W�F�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
TEXRES_OBJ_PTR TEXRESM_GetResObj(CONST_TEXRES_MANAGER_PTR resm, int id)
{
	int i;
	int res_id;
	
	GF_ASSERT( resm );

	for(i=0;i<resm->resm->max;i++){
		
		if( resm->tobj[ i ].resobj ){
			res_id = TEXRESM_GetID( resm->tobj + i );
			if( res_id == id ){
				return resm->tobj + i;
			}
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�^����Ă���ID���擾
 *
 *@param	r_obj		���\�[�X�I�u�W�F
 *
 *@retval	int			�Ǘ�ID
 *
 *
 */
//-----------------------------------------------------------------------------
int TEXRESM_GetID(CONST_TEXRES_OBJ_PTR r_obj)
{
	GF_ASSERT( r_obj );

	return RESM_GetID( r_obj->resobj );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�^����Ă���ID��ݒ�
 *
 *@param	resm		���\�[�X�}�l�[�W��
 *@param	r_obj		���\�[�X�I�u�W�F
 *@param	id			�ݒ肷��ID
 *
 *@retval	none
 *
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_SetID(TEXRES_MANAGER_PTR resm, TEXRES_OBJ_PTR r_obj, int id)
{
	GF_ASSERT( resm );
	GF_ASSERT( r_obj );

	RESM_SetID( resm->resm, r_obj->resobj, id );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�^����Ă���e�N�X�`�����\�[�X�f�[�^���擾
 *
 *@param	r_obj		�e�N�X�`�����\�[�X�I�u�W�F
 *
 *@retval	NULL		�o�^����Ă��Ȃ�
 *@retval	NULL�ȊO	�o�^����Ă���e�N�X�`�����\�[�X�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG3dResTex* TEXRESM_GetResPTR(CONST_TEXRES_OBJ_PTR r_obj)
{
	GF_ASSERT( r_obj );

	return getTexRes( r_obj );
}

//----------------------------------------------------------------------------
/**
 * ID�Ŏ擾
 *
 *@brief	�o�^����Ă���e�N�X�`�����\�[�X�f�[�^���擾
 *
 *@param	resm		�e�N�X�`�����\�[�X�}�l�[�W��
 *@param	id			�o�^ID
 *
 *@retval	NULL		�o�^����Ă��Ȃ�
 *@retval	NULL�ȊO	�o�^����Ă���e�N�X�`�����\�[�X�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG3dResTex* TEXRESM_GetResID(CONST_TEXRES_MANAGER_PTR resm, int id)
{
	TEXRES_OBJ_PTR resobj;
	resobj = TEXRESM_GetResObj( resm, id );

	return getTexRes( resobj );
}

//----------------------------------------------------------------------------
/**
 * ���I�u�W�F�N�g�|�C���^
 *
 *	@brief	�e�N�X�`�����\�[�X��Vram�ɓ]��
 *
 *	@param	r_obj	�e�N�X�`�����\�[�X�I�u�W�F
 *
 *	@return	none
 *
 * ���̊֐����ĂԂ�VramKey���쐬����܂��B
 * �m�ۂ���VramKey��TEXRESM_DeleteRes�n�֐��Ń��\�[�X�ƈꏏ�ɔj������܂�
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_TexLoadPTR( TEXRES_OBJ_PTR r_obj )
{
	NNSG3dResTex* tex_res;
	
	GF_ASSERT(r_obj);
	GF_ASSERT_MSG( r_obj->cut_flag == FALSE, "�e�N�X�`�����f�[�^�j���ς݂Ȃ̂œ]���͂ł��܂���B" );
	
	// VramKey���擾�����f�[�^���`�F�b�N
	if( r_obj->plttKey == NNS_GFD_ALLOC_ERROR_PLTTKEY ){
		GF_ASSERT_MSG(0, "VramKey���擾���Ă��Ȃ��̂ɓ]�����悤�Ƃ��Ă��܂��BTEXRESM_AllocVramKey�֐������s���Ă���TEXRESM_TexLoad�֐������s���Ă��������B");
		return ;
	}

	// TexCut�������Ƃ��͂��̂܂܃��\�[�X���擾
	// TexCut����Ƃ���,p_cutTex���擾
	tex_res = getTexRes_CheckCutTex( r_obj );
	
	// Vram�̈�ɓ]��
	loadTexRes( tex_res, r_obj );
}

//----------------------------------------------------------------------------
/**
 * ��ID
 *
 *	@brief	�e�N�X�`�����\�[�X��Vram�ɓ]��
 *
 *	@param	resm		�e�N�X�`�����\�[�X�}�l�[�W��
 *	@param	id			�o�^ID
 *
 *	@return	none
 *
 * ���̊֐����ĂԂ�VramKey���쐬����܂��B
 * �m�ۂ���VramKey��TEXRESM_DeleteRes�n�֐��Ń��\�[�X�ƈꏏ�ɔj������܂�
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_TexLoadID( TEXRES_MANAGER_PTR resm, int id )
{
	TEXRES_OBJ_PTR resobj;
	
	GF_ASSERT( resm );
	resobj = TEXRESM_GetResObj( resm, id );


	TEXRESM_TexLoadPTR( resobj );
}

//----------------------------------------------------------------------------
/**
 * ���I�u�W�F�N�g�|�C���^
 *
 *	@brief	�e�N�X�`�����\�[�X�̎��f�[�^��j��
 *
 *	@param	r_obj	�e�N�X�`�����\�[�X�I�u�W�F
 *
 *	@return	none
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_CutTexPTR( TEXRES_OBJ_PTR r_obj )
{
	void* buff;
	
	GF_ASSERT(r_obj);

	// �J�b�g���ėǂ��I�u�W�F�N�g���`�F�b�N
	if( r_obj->cuttex_flag == TEXRESM_TEX_CUT_FALSE ){
		// "�e�N�X�`�����f�[�^�j���ł��Ȃ��I�u�W�F�N�g�ł�"
		GF_ASSERT(0);
		return ;
	}
	
	//  �j���ς݂łȂ����`�F�b�N
	if( r_obj->cut_flag ){
		// "�j���ς݂ł�"
		GF_ASSERT(0);
		return ;
	}

	// �e�N�X�`�����\�[�X����
	// �e�N�X�`���L�[��j��
	releaseTexkeyRes( getTexRes_CheckCutTex( r_obj ) );
	setTexkeyRes( getTexRes( r_obj ), r_obj->texKey, r_obj->tex4x4Key, r_obj->plttKey );

	// �������j��
	sys_FreeMemoryEz( r_obj->p_cutTex );
	r_obj->p_cutTex = NULL;
	
	// �e�N�X�`�����f�[�^�j������
	r_obj->cut_flag = TRUE;
}

//----------------------------------------------------------------------------
/**
 * ��ID
 *
 *	@brief	�e�N�X�`�����\�[�X�̎��f�[�^��j��
 *
 *	@param	resm		�e�N�X�`�����\�[�X�}�l�[�W��
 *	@param	id			�o�^ID
 *
 *	@return	none
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_CutTexID( TEXRES_MANAGER_PTR resm, int id )
{
	TEXRES_OBJ_PTR resobj;
	GF_ASSERT( resm );
	resobj = TEXRESM_GetResObj( resm, id );

	TEXRESM_CutTexPTR( resobj );
}

//----------------------------------------------------------------------------
/**
 * ���I�u�W�F�N�g�|�C���^�Ŋm��
 *
 *	@brief	�e�N�X�`���L�[��VramManager����m�ۂ��܂�
 *
 *	@param	r_obj		���\�[�X�I�u�W�F
 *
 *	@return none
 *
 * �m�ۂ���VramKey�i�e�N�X�`���L�[�@�p���b�g�L�[�j
 * ��TEXRESM_Delete�`�֐��Ŕj������܂��B
 *
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_AllocVramKeyPTR( TEXRES_OBJ_PTR r_obj )
{
	NNSG3dResTex* tex_res;

	GF_ASSERT( r_obj );
	GF_ASSERT_MSG( r_obj->cut_flag == FALSE, "�e�N�X�`�����f�[�^�j���ς݂Ȃ̂�VramKey�m�ۂł��܂���B" );
	
	// VramKey�擾�ς݂łȂ����`�F�b�N
	if( r_obj->plttKey != NNS_GFD_ALLOC_ERROR_PLTTKEY ){
		GF_ASSERT_MSG(0, "VramKey�擾�ς݂ł�");
		return ;
	}

	// TexCut�������Ƃ��͂��̂܂܃��\�[�X���擾
	// TexCut����Ƃ���,p_cutTex���擾
	tex_res = getTexRes_CheckCutTex( r_obj );
	
	// Vramkey�̎擾
	getVramkey( tex_res, &r_obj->texKey, &r_obj->tex4x4Key, &r_obj->plttKey );
}

//----------------------------------------------------------------------------
/**
 * ��ID�Ŋm��
 *
 *	@brief	�e�N�X�`���L�[��VramManager����m�ۂ��܂�
 *
 *	@param	resm		�e�N�X�`�����\�[�X�}�l�[�W��
 *	@param	id			�o�^ID
 *
 *	@return none
 *
 * �m�ۂ���VramKey�i�e�N�X�`���L�[�@�p���b�g�L�[�j
 * ��TEXRESM_Delete�`�֐��Ŕj������܂��B
 *
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_AllocVramKeyID( CONST_TEXRES_MANAGER_PTR resm, int id )
{
	TEXRES_OBJ_PTR resobj;
	
	GF_ASSERT( resm );
	resobj = TEXRESM_GetResObj( resm, id );


	TEXRESM_AllocVramKeyPTR( resobj );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�e�N�X�`�����\�[�X��Vram�ɓ]��
 *
 *	@param	r_obj		�e�N�X�`�����\�[�X�I�u�W�F
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_TexLoadAndCutTexPTR( TEXRES_OBJ_PTR r_obj )
{
	TEXRESM_TexLoadPTR( r_obj );
	TEXRESM_CutTexPTR( r_obj );
}

//----------------------------------------------------------------------------
/**
 * ID�Ŏ擾
 *
 *	@brief	�e�N�X�`�����\�[�X��Vram�ɓ]��
 *
 *	@param	resm		�e�N�X�`�����\�[�X�}�l�[�W��
 *	@param	id			�o�^ID
 *
 *	@return	none
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_TexLoadAndCutTexID( TEXRES_MANAGER_PTR resm, int id )
{
	TEXRES_OBJ_PTR resobj;
	GF_ASSERT( resm );
	resobj = TEXRESM_GetResObj( resm, id );

	TEXRESM_TexLoadAndCutTexPTR( resobj );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�e�N�X�`���L�[�̎擾
 *
 *	@param	r_obj	�e�N�X�`�����\�[�X�I�u�W�F
 *
 *	@return	�e�N�X�`���L�[
 *
 *
 */
//-----------------------------------------------------------------------------
NNSGfdTexKey TEXRESM_GetTexKeyPTR( CONST_TEXRES_OBJ_PTR r_obj )
{
	GF_ASSERT(r_obj);

	return r_obj->texKey;
}

//----------------------------------------------------------------------------
/**
 * ID�Ŏ擾
 *
 *	@brief	�e�N�X�`���L�[�̎擾
 *
 *	@param	resm		�e�N�X�`�����\�[�X�}�l�[�W��
 *	@param	id			�o�^ID
 *
 *	@return	�e�N�X�`���L�[
 *
 *
 */
//-----------------------------------------------------------------------------
NNSGfdTexKey TEXRESM_GetTexKeyID( CONST_TEXRES_MANAGER_PTR resm, int id )
{
	TEXRES_OBJ_PTR resobj;
	GF_ASSERT( resm );
	resobj = TEXRESM_GetResObj( resm, id );

	return TEXRESM_GetTexKeyPTR( resobj );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�e�N�X�`��4x4�L�[�̎擾
 *
 *	@param	r_obj	�e�N�X�`�����\�[�X�I�u�W�F
 *
 *	@return	�e�N�X�`���L�[
 *
 *
 */
//-----------------------------------------------------------------------------
NNSGfdTexKey TEXRESM_GetTex4x4KeyPTR( CONST_TEXRES_OBJ_PTR r_obj )
{
	GF_ASSERT(r_obj);

	return r_obj->tex4x4Key;
}

//----------------------------------------------------------------------------
/**
 * ID�Ŏ擾
 *
 *	@brief	�e�N�X�`��4x4�L�[�̎擾
 *
 *	@param	resm		�e�N�X�`�����\�[�X�}�l�[�W��
 *	@param	id			�o�^ID
 *
 *	@return	�e�N�X�`���L�[
 *
 *
 */
//-----------------------------------------------------------------------------
NNSGfdTexKey TEXRESM_GetTex4x4KeyID( CONST_TEXRES_MANAGER_PTR resm, int id )
{
	TEXRES_OBJ_PTR resobj;
	GF_ASSERT( resm );
	resobj = TEXRESM_GetResObj( resm, id );

	return TEXRESM_GetTex4x4KeyPTR( resobj );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�L�[�̎擾
 *
 *	@param	r_obj	�e�N�X�`�����\�[�X�I�u�W�F
 *
 *	@return	�p���b�g�L�[
 *
 *
 */
//-----------------------------------------------------------------------------
NNSGfdPlttKey TEXRESM_GetPlttKeyPTR( CONST_TEXRES_OBJ_PTR r_obj )
{
	GF_ASSERT(r_obj);

	return r_obj->plttKey;
}

//----------------------------------------------------------------------------
/**
 * ID�Ŏ擾
 *
 *	@brief	�p���b�g�L�[�̎擾
 *
 *	@param	resm		�e�N�X�`�����\�[�X�}�l�[�W��
 *	@param	id			�o�^ID
 *
 *	@return	�p���b�g�L�[
 *
 *
 */
//-----------------------------------------------------------------------------
NNSGfdPlttKey TEXRESM_GetPlttKeyID( CONST_TEXRES_MANAGER_PTR resm, int id )
{
	TEXRES_OBJ_PTR resobj;
	GF_ASSERT( resm );
	resobj = TEXRESM_GetResObj( resm, id );

	return TEXRESM_GetPlttKeyPTR( resobj );
}

//----------------------------------------------------------------------------
/**
 * ���I�u�W�F�N�g�|�C���^
 *
 *	@brief	�w�肳�ꂽVramKey�ʒu�Ƀe�N�X�`����]�����܂��B
 *
 *	@param	r_obj		�e�N�X�`�����\�[�X�I�u�W�F
 *	@param	texkey		�e�N�X�`���L�[
 *	@param	tex4x4key	�e�N�X�`��4x4�L�[
 *	@param	plttkey		�p���b�g�L�[
 *
 *	@return	none
 *
 * ������texkey�Eplttkey�f�[�^�̓e�N�X�`�����\�[�X�}�l�[�W���ł�
 * �Ǘ����܂���̂ŁA�e���m�ہA�j�����Ă��������B
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_TexLoadOfKeyPTR( TEXRES_OBJ_PTR r_obj, NNSGfdTexKey texkey, NNSGfdTexKey tex4x4key, NNSGfdPlttKey plttkey )
{
	NNSG3dResTex* res;
	
	GF_ASSERT( r_obj );
	GF_ASSERT_MSG( r_obj->cut_flag == FALSE, "�e�N�X�`�����f�[�^���폜����Ă���̂œ]���ł��܂���B" );

	// TexCut�������Ƃ��͂��̂܂܃��\�[�X���擾
	// TexCut����Ƃ���,p_cutTex���擾
	res = getTexRes_CheckCutTex( r_obj );
	
	NNS_G3dTexSetTexKey(res, texkey, tex4x4key);
	NNS_G3dPlttSetPlttKey(res, plttkey);

	DC_FlushRange( res, res->header.size );
	// VRAM�ւ̃��[�h
	NNS_G3dTexLoad(res, TRUE);
	NNS_G3dPlttLoad(res, TRUE);
}

//----------------------------------------------------------------------------
/**
 *	��ID
 * 
 *	@brief	�w�肳�ꂽVramKey�ʒu�Ƀe�N�X�`����]�����܂��B
 *
 *	@param	resm		�e�N�X�`�����\�[�X�}�l�[�W��
 *	@param	id			�o�^ID
 *	@param	texkey		�e�N�X�`���L�[
 *	@param	tex4x4key	�e�N�X�`��4x4�L�[
 *	@param	plttkey		�p���b�g�L�[
 *
 *	@return	none
 *
 * ������texkey�Eplttkey�f�[�^�̓e�N�X�`�����\�[�X�}�l�[�W���ł�
 * �Ǘ����܂���̂ŁA�e���m�ہA�j�����Ă��������B
 *
 */
//-----------------------------------------------------------------------------
void TEXRESM_TexLoadOfKeyID( TEXRES_MANAGER_PTR resm, int id, NNSGfdTexKey texkey, NNSGfdTexKey tex4x4key, NNSGfdPlttKey plttkey )
{
	TEXRES_OBJ_PTR resobj;
	GF_ASSERT( resm );
	resobj = TEXRESM_GetResObj( resm, id );

	TEXRESM_TexLoadOfKeyPTR( resobj, texkey, tex4x4key, plttkey );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�󂢂Ă���e�N�X�`�����\�[�X�I�u�W�F�̎擾
 *
 *	@param	resm	���\�[�X�}�l�[�W��
 *
*	@return	�󂢂Ă���e�N�X�`�����\�[�X�I�u�W�F
 *
 *
 */
//-----------------------------------------------------------------------------
static TEXRES_OBJ_PTR getCleanTEXRES_OBJ(CONST_TEXRES_MANAGER_PTR resm)
{
	int i;

	for(i=0;i<resm->resm->max;i++){
		if(resm->tobj[i].resobj == NULL){
			return resm->tobj + i;
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�e�N�X�`�����\�[�X�I�u�W�F��������
 *
 *	@param	obj		�e�N�X�`�����\�[�X�I�u�W�F
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanTEXRES_OBJ(TEXRES_OBJ_PTR obj)
{
	obj->resobj		= NULL;
	obj->texKey		= NNS_GFD_ALLOC_ERROR_TEXKEY;
	obj->tex4x4Key	= NNS_GFD_ALLOC_ERROR_TEXKEY;
	obj->plttKey	= NNS_GFD_ALLOC_ERROR_PLTTKEY;
	obj->cut_flag	= FALSE;
	obj->p_cutTex	= NULL;
	obj->cut_flag	= FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�e�N�X�`�����\�[�X�̎擾
 *
 *	@param	r_obj	�e�N�X�`�����\�[�X�I�u�W�F
 *
 *	@return	�e�N�X�`�����\�[�X
 *
 *
 */
//-----------------------------------------------------------------------------
static NNSG3dResTex* getTexRes( CONST_TEXRES_OBJ_PTR r_obj )
{
	void* buff;
	NNSG3dResTex* o_tex;

	buff = RESM_GetRes( r_obj->resobj );

	o_tex = NNS_G3dGetTex(buff);

	return o_tex;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e�N�X�`�����f�[�^�̓����Ă���@�e�N�X�`�����\�[�X�擾
 *
 *	@param	r_obj	�e�N�X�`�����\�[�X�I�u�W�F
 *
 *	@return	�e�N�X�`�����\�[�X
 */
//-----------------------------------------------------------------------------
static NNSG3dResTex* getTexRes_CheckCutTex( CONST_TEXRES_OBJ_PTR r_obj )
{
	void* buff;
	NNSG3dResTex* o_tex;

	// TexCut�������Ƃ��͂��̂܂܃��\�[�X���擾
	// TexCut����Ƃ���,p_cutTex���擾
	if( r_obj->cuttex_flag == TEXRESM_TEX_CUT_FALSE ){
		// �e�N�X�`�����\�[�X�̎擾
		buff = RESM_GetRes( r_obj->resobj );
	}else{
		buff = r_obj->p_cutTex;
	}
	o_tex = NNS_G3dGetTex(buff);
	return o_tex;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�e�N�X�`�����\�[�X�f�[�^�p��Vramkey���擾
 *
 *	@param	res		�e�N�X�`�����\�[�X
 *	@param	tex		�e�N�X�`���L�[
 *	@param	tex4x4	4x4���k�e�N�X�`��
 *	@param	pltt	�p���b�g�L�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void getVramkey( const NNSG3dResTex* res, NNSGfdTexKey* tex, NNSGfdTexKey* tex4x4, NNSGfdPlttKey* pltt )
{
	u32 tex_size;
	u32 tex_4x4_size;
	u32 pltt_size;

	tex_size = NNS_G3dTexGetRequiredSize( res );
	tex_4x4_size = NNS_G3dTex4x4GetRequiredSize(res);
	pltt_size = NNS_G3dPlttGetRequiredSize( res );


	if(tex_size != 0){
		*tex = NNS_GfdAllocTexVram( tex_size, FALSE, 0 );
		// �e�N�X�`���L�[�m�ێ��s
//		GF_ASSERT(*tex != NNS_GFD_ALLOC_ERROR_TEXKEY );
	}
	if(tex_4x4_size != 0){
		*tex4x4 = NNS_GfdAllocTexVram( tex_4x4_size, TRUE, 0 );
		// �e�N�X�`���L�[�m�ێ��s
//		GF_ASSERT(*tex4x4 != NNS_GFD_ALLOC_ERROR_TEXKEY );
	}
	if(pltt_size != 0){
		*pltt = NNS_GfdAllocPlttVram( pltt_size, 
			res->tex4x4Info.flag & NNS_G3D_RESPLTT_USEPLTT4, 0 );
		// �p���b�g�L�[�m�ێ��s
//		GF_ASSERT(*pltt != NNS_GFD_ALLOC_ERROR_PLTTKEY );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�e�N�X�`�����\�[�X�ǂݍ���
 *
 *	@param	res		�e�N�X�`�����\�[�X
 *	@param	r_obj	�e�N�X�`�����\�[�X�I�u�W�F
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadTexRes( NNSG3dResTex* res, TEXRES_OBJ_PTR r_obj )
{
	setTexkeyRes( res, r_obj->texKey, r_obj->tex4x4Key, r_obj->plttKey );

	DC_FlushRange( res, res->header.size );
	// VRAM�ւ̃��[�h
	NNS_G3dTexLoad(res, TRUE);
	NNS_G3dPlttLoad(res, TRUE);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e�N�X�`���L�[���e�N�X�`�����\�[�X�ɐݒ�
 *
 *	@param	res			�e�N�X�`�����\�[�X
 *	@param	tex			�e�N�X�`���L�[
 *	@param	tex4x4		�e�N�X�`���L�[	4x4
 *	@param	pltt		�p���b�g�L�[
 */
//-----------------------------------------------------------------------------
static void setTexkeyRes( NNSG3dResTex* res, NNSGfdTexKey tex, NNSGfdTexKey tex4x4, NNSGfdPlttKey pltt )
{
	NNS_G3dTexSetTexKey(res, tex, tex4x4);
	NNS_G3dPlttSetPlttKey(res, pltt);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e�N�X�`���L�[���e�N�X�`�����\�[�X������
 *
 *	@param	res		�e�N�X�`�����\�[�X
 */
//-----------------------------------------------------------------------------
static void releaseTexkeyRes( NNSG3dResTex* res )
{
	NNSGfdTexKey	texKey;		// �e�N�X�`���L�[
	NNSGfdTexKey	tex4x4Key;	// 4x4�e�N�X�`���L�[
	NNSGfdPlttKey	plttKey;	// �p���b�g�L�[

	// VramKey��t���ւ���
	NNS_G3dTexReleaseTexKey( res, &texKey, &tex4x4Key );
	plttKey = NNS_G3dPlttReleasePlttKey( res );	
}

// �e�N�X�`�����\�[�X���폜����NNSG3dResTex���쐬����֐��S
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�e�N�X�`�����f�[�^��j�������T�C�Y�̃e�N�X�`�����\�[�X�쐬
 *
 *	@param	p_cuttex	�e�N�X�`�����f�[�^��j������e�N�X�`�����\�[�X
 *
 *	@return	none	
 *
 *
 */
//-----------------------------------------------------------------------------
static void* MakeCutTexWork( void* p_cuttex, u32 heap )
{
	u32	data_size;		// �e�N�X�`�����f�[�^�����Ȃ��e�N�X�`�����\�[�X�T�C�Y
	void* buff;
	// �e�N�X�`�����f�[�^�����Ȃ��e�N�X�`�����\�[�X�T�C�Y�擾
	data_size = GetCutTexDataSize( p_cuttex );

	buff = sys_AllocMemory( heap, data_size );

	// �擪����buff���R�s�[����
	memcpy( buff, p_cuttex, data_size );
	return buff;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�e�N�X�`�����f�[�^�����Ȃ��e�N�X�`�����\�[�X�T�C�Y�̌v�Z
 *
 *	@param	p_cuttex	�v�Z����e�N�X�`�����\�[�X�f�[�^
 *
 *	@return	�e�N�X�`�����f�[�^�����Ȃ��e�N�X�`�����\�[�X�̃T�C�Y
 *
 *
 */
//-----------------------------------------------------------------------------
static u32 GetCutTexDataSize( const void* p_cuttex )
{
	NNSG3dResTex* p_tex;
	u8* tex_top;		// �e�N�X�`���f�[�^�擪�f�[�^
	u32 new_size;		// �V�����f�[�^�T�C�Y

	p_tex = NNS_G3dGetTex( p_cuttex );
	GF_ASSERT_MSG( p_tex, "���̃��\�[�X�ɂ̓e�N�X�`���f�[�^������܂���B" );

	// �e�N�X�`���̐擪�A�h���X�v�Z
	tex_top = (u8*)p_tex + p_tex->texInfo.ofsTex;

	// �q�[�v�̐擪����e�N�X�`���C���[�W�܂ł̃T�C�Y
    new_size = (u32)(tex_top - (u8*)p_cuttex);

	return new_size;
}
