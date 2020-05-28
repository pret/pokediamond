//******************************************************************************
/**
 *
 * @file	localres.c
 * @brief	�m�ۂ������\�[�X�̈���X�ɔz�����čė��p���܂���B
 * @author	kagaya
 * @data	05.07.25
 *
 */
//******************************************************************************
#include "common.h"
#include "localres.h"

//==============================================================================
//	define
//==============================================================================
#define LRES_SEEK_SIZE (sizeof(u32))

//==============================================================================
//	typedef
//==============================================================================
//--------------------------------------------------------------
///	LRESID��`
//--------------------------------------------------------------
typedef struct _RESID		RESID;

//--------------------------------------------------------------
///	LRES�\����
//--------------------------------------------------------------
typedef struct _LRES
{
	u32 main_heap_id;								//�m�ۂ���HEAP ID
	u32 reg_heap_id;								//�o�^����HEAP ID
	u32 resid_max;									//ID�o�^�ő吔
	u32 total_size;									//�m�ۂ����T�C�Y
	u32 resid_total_size;							//���[�J�����\�[�X�Ǘ��p���[�N�ő�T�C�Y
	RESID *resid_ptr;								//���[�J�����\�[�X�Ǘ����[�N *
};

#define LRES_SIZE (sizeof(LRES))	//LRES�T�C�Y

//--------------------------------------------------------------
///	RESID�\����
//--------------------------------------------------------------
typedef struct _RESID
{
	void *alloc_ptr;								//�m�ۂ��Ă��郊�\�[�X *�@���m��=NULL
	u32 alloc_id;									//�o�^ID
};

#define RESID_SIZE (sizeof(RESID))	//RESID�T�C�Y

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void * lRes_AllocHeap( LRES *lres, u32 size, ALLOCTYPE type );
static void lRes_FreeHeap( void *alloc );
static RESID * lRes_IDSearch( LRES *lres, u32 id );
static RESID * lRes_IDSpaceSearch( LRES *lres );
static RESID * lRes_IDAllocSearch( LRES *lres, void *alloc );
static void lRes_ResIDInit( RESID *resid, u32 id, void *alloc );
static void lRes_ResIDDelete( RESID *resid );

#ifdef PM_DEBUG
#endif

//==============================================================================
//	local resource
//==============================================================================
//--------------------------------------------------------------
/**
 * LRES������
 * @param	main_heap_id	�m�ۂ���HEAP ID
 * @param	reg_heap_id		�m�ۂ����̈�����ʂ���HEAP ID
 * @param	size			�m�ۂ���T�C�Y
 * @param	regid_max		�o�^����ID�ő吔�BID�Ǘ��v��Ȃ��ꍇ��0�w��
 * @retval	LRES*			�m�ۂ���LRES *
 */
//--------------------------------------------------------------
LRES * LRes_Init( u32 main_heap_id, u32 reg_heap_id, u32 size, u32 resid_max )
{
	u32 resid_size,total_size;
	LRES *lres;
	
	resid_size = RESID_SIZE * resid_max;
	total_size = size + resid_size + LRES_SIZE;
	
	{
		BOOL ret = sys_CreateHeap( main_heap_id, reg_heap_id, total_size );
		GF_ASSERT( ret == TRUE && "LRes_Init()�̈�m�ێ��s" );
	}
	
	size = total_size - size;
	lres = sys_AllocMemory( reg_heap_id, size );
	GF_ASSERT( lres != NULL && "LRes_Init()�̈�m�ێ��s" );
	memset( lres, 0, size );
	
	lres->main_heap_id = main_heap_id;
	lres->reg_heap_id = reg_heap_id;
	lres->resid_max = resid_max;
	lres->total_size = total_size;
	lres->resid_total_size = resid_size;
	lres->resid_ptr = (void*)((u32)lres + LRES_SIZE);
	
	return( lres );
}

//--------------------------------------------------------------
/**
 * LRES�폜
 * @param	lres	LRES *
 * @retval	nothing
 */
//--------------------------------------------------------------
void LRes_Delete( LRES *lres )
{
	{
		u32 max = lres->resid_max;
		RESID *resid = lres->resid_ptr;
	
		while( max ){
			if( resid->alloc_ptr != NULL ){
				LRes_FreeID( lres, resid->alloc_id );
			}
			
			max--; resid++;
		}
	}
	
	{
		u32 reg_heap_id = lres->reg_heap_id;
		sys_FreeMemoryEz( lres );
		sys_DeleteHeap( reg_heap_id );
	}
}

//--------------------------------------------------------------
/**
 * LRES �̈�m��
 * @param	lres	LRES *
 * @param	size	�m�ۂ���T�C�Y
 * @param	type	ALLOCTYPE
 * @retval	void*	�m�ۂ����̈� NULL=�m�ۏo���Ȃ��B �m�ۏo���Ȃ��ꍇ�AASSERT
 */
//--------------------------------------------------------------
void * LRes_Alloc( LRES *lres, u32 size, ALLOCTYPE type )
{
	void *alloc = lRes_AllocHeap( lres, size, type );
	return( alloc );
}

//--------------------------------------------------------------
/**
 * LRES �̈�m�ہ@ID�o�^�A��
 * @param	lres	LRES *
 * @param	id		�o�^����ID
 * @param	size	�m�ۂ���T�C�Y
 * @param	type	ALLOCTYPE
 * @retval	void*	�m�ۂ����̈� NULL=�m�ۏo���Ȃ��B �m�ۏo���Ȃ��ꍇ�AASSERT
 */
//--------------------------------------------------------------
void * LRes_AllocID( LRES *lres, u32 id, u32 size, ALLOCTYPE type )
{
	RESID *resid = lRes_IDSpaceSearch( lres );
	GF_ASSERT( resid != NULL && "LRes_AllocID()�o�^���ő�\n" );
	
	{
		void *alloc = lRes_AllocHeap( lres, size, type );
		lRes_ResIDInit( resid, id, alloc );
		return( alloc );
	}
}

//--------------------------------------------------------------
/**
 * LRES �̈�J���Balloc��ID�o�^����Ă����ꍇ�A����ID���폜����
 * @param	lres		LRES
 * @param	alloc		LRes_Alloc�Ŋm�ۂ����̈�
 * @retval	nothing
 */
//--------------------------------------------------------------
void LRes_Free( LRES *lres, void *alloc )
{
	RESID *resid = lRes_IDAllocSearch( lres, alloc );
	if( resid != NULL ){ lRes_ResIDDelete( resid ); }
	lRes_FreeHeap( alloc );
}

//--------------------------------------------------------------
/**
 * LRES �̈�J�� ID��
 * @param	lres		LRES
 * @param	id			LRes_AllocID�Ŏw�肵��ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void LRes_FreeID( LRES *lres, u32 id )
{
	RESID *resid = lRes_IDSearch( lres, id );
	GF_ASSERT( resid != NULL && "LRes_FreeID()id�o�^����\n" );
	lRes_FreeHeap( resid->alloc_ptr );
	lRes_ResIDDelete( resid );
}

//--------------------------------------------------------------
/**
 * LRES ID�w��̈�擾�B
 * @param	lres		LRES *
 * @param	id			LRes_AllocID�Ŏw�肵��ID
 * @retval	void*		LRes_AllocID(id)�Ŏ擾�����̈�
 */
//--------------------------------------------------------------
void * LRes_IDResGet( LRES *lres, u32 id )
{
	RESID *resid = lRes_IDSearch( lres, id );
	GF_ASSERT( resid != NULL && "LRes_IDResGet()id�o�^����\n" );
	return( resid->alloc_ptr );
}

//--------------------------------------------------------------
/**
 * LRES ID�o�^�ς݃`�F�b�N
 * @param	lres		LRES
 * @param	id			LRes_AllocID�Ŏw�肵��ID
 * @retval	int			TRUE=�o�^�ς݁@FALSE=�o�^���Ă��Ȃ�
 */
//--------------------------------------------------------------
int LRes_IDResCheck( LRES *lres, u32 id )
{
	RESID *resid = lRes_IDSearch( lres, id );
	if( resid != NULL ){ return( TRUE ); }
	return( FALSE );
}

//==============================================================================
//	LRES �c�[��
//==============================================================================
//--------------------------------------------------------------
/**
 * LRES_Alloc()+ArchiveDataLoadByHandle()�B
 * LRES_Alloc()�Ŋm�ۂ����̈�փA�[�J�C�u�f�[�^�]���B
 * datId�̃T�C�Y���A�m�ۂ���B
 * @param	lres		LRES *
 * @param	handle		ARCHANDLE*
 * @param	datId		�f�[�^�C���f�b�N�XID
 * @param	type		ALLOCTYPE
 * @retval	void*		�m�ہA�f�[�^�]���ς݂̗̈�
 */
//--------------------------------------------------------------
void * LResUtil_AllocArcLoad( LRES *lres, ARCHANDLE *handle, u32 datId, ALLOCTYPE type )
{
	u32 size = ArchiveDataSizeGetByHandle( handle, datId );
	void *alloc = LRes_Alloc( lres, size, type );
	ArchiveDataLoadByHandle( handle, datId, alloc );
	return( alloc );
}

//--------------------------------------------------------------
/**
 * LRES_AllocID()+ArchiveDataLoadByHandle()�B
 * LRES_AllocID()�Ŋm�ۂ����̈�փA�[�J�C�u�f�[�^�]���B
 * datId�̃T�C�Y���A�m�ۂ���B
 * @param	lres		LRES *
 * @param	id			�o�^ID
 * @param	handle		ARCHANDLE*
 * @param	datId		�f�[�^�C���f�b�N�XID
 * @param	type		ALLOCTYPE
 * @retval	void*		�m�ہA�f�[�^�]���ς݂̗̈�
 */
//--------------------------------------------------------------
void * LResUtil_AllocIDArcLoad(
		LRES *lres, u32 id, ARCHANDLE *handle, u32 datId, ALLOCTYPE type )
{
	u32 size = ArchiveDataSizeGetByHandle( handle, datId );
	void *alloc = LRes_AllocID( lres, id, size, type );
	ArchiveDataLoadByHandle( handle, datId, alloc );
	return( alloc );
}

//==============================================================================
//	�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * �̈�m��
 * @param	lress		LRES *
 * @param	size		�m�ۂ���T�C�Y
 * @param	type		ALLOCTYPE
 * @retval	void*		�m�ۂ����̈�
 */
//--------------------------------------------------------------
static void * lRes_AllocHeap( LRES *lres, u32 size, ALLOCTYPE type )
{
	void *alloc;
	
	if( type == ALLOC_FR ){ alloc = sys_AllocMemory( lres->reg_heap_id, size ); }
	else{ alloc = sys_AllocMemoryLo( lres->reg_heap_id, size ); }
	
	GF_ASSERT( alloc != NULL && "lRes_AllocHeap()�m�ێ��s\n" );
	return( alloc );
}

//--------------------------------------------------------------
/**
 * �̈�J��
 * @param	lress		LRES *
 * @param	alloc		lRes_AllocHeap()�Ŋm�ۂ����̈�
 * @retval	nothing
 */
//--------------------------------------------------------------
static void lRes_FreeHeap( void *alloc )
{
	sys_FreeMemoryEz( alloc );
}

//--------------------------------------------------------------
/**
 * ID����
 * @param	lres		LRES *
 * @param	id			����ID
 * @retval	RESID*		��v����RESID *�@��v���Ȃ�=NULL
 */
//--------------------------------------------------------------
static RESID * lRes_IDSearch( LRES *lres, u32 id )
{
	u32 max = lres->resid_max;
	RESID *resid = lres->resid_ptr;
	
	while( max ){
		if( resid->alloc_ptr != NULL && resid->alloc_id == id ){
			return( resid );
		}
		
		resid++; max--;
	};
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * RESID�󂫒T��
 * @param	lres		LRES *
 * @retval	RESID*		��RESID�@�󂫖���=NULL
 */
//--------------------------------------------------------------
static RESID * lRes_IDSpaceSearch( LRES *lres )
{
	u32 max = lres->resid_max;
	RESID *resid = lres->resid_ptr;
	
	while( max ){
		if( resid->alloc_ptr == NULL ){
			return( resid );
		}
		
		resid++; max--;
	}
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * RESID�@�w�肳�ꂽ�̈悪�o�^����Ă��邩
 * @param	lres		LRES *
 * @param	alloc		�m�ۂ����̈�
 * @retval	RESID*		�Y������RESID�@�Y������=NULL
 */
//--------------------------------------------------------------
static RESID * lRes_IDAllocSearch( LRES *lres, void *alloc )
{
	u32 max = lres->resid_max;
	RESID *resid = lres->resid_ptr;
	
	while( max ){
		if( resid->alloc_ptr == alloc ){
			return( resid );
		}
		
		resid++; max--;
	}
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * RESID������
 * @param	resid		����������RESID *
 * @param	id			�o�^����ID
 * @param	alloc		�m�ۂ��Ă���̈�
 * @retval	nothing
 */
//--------------------------------------------------------------
static void lRes_ResIDInit( RESID *resid, u32 id, void *alloc )
{
	resid->alloc_ptr = alloc;
	resid->alloc_id = id;
}

//--------------------------------------------------------------
/**
 * RESID�폜
 * @param	resid		�폜����RESID *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void lRes_ResIDDelete( RESID *resid )
{
	resid->alloc_ptr = NULL;
	resid->alloc_id = 0;
}

//==============================================================================
//	�f�o�b�O
//==============================================================================
//----
#ifdef PM_DEBUG
//----
//----
#endif //PM_DEBUG
//----
