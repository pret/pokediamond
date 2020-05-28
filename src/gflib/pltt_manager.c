//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *	@file		pltt_manager.c
 *	@brief		�p���b�g�}�l�[�W���[�̎��ԕ�
 *	@author		tomoya takahashi
 *	@data		2004.11.22
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]*/

#include "system.h"
#define PLTT_MANAGER_H_GLOBAL
#include "pltt_manager.h"
#include "gflib_os_print.h"
#include "assert.h"
#include "vram_transfer_manager.h"
#include <string.h>


//-----------------------------------------------------------------------------
/**
 *					�萔�錾
 */
//-----------------------------------------------------------------------------

#define		PLTT_ONE_SIZE	(32)			// �P�U�F�p���b�g�P�̃T�C�Y
#define		PLTT_AREA_NONE	(0xffffffff)	// �p���b�g�p�G���A�Ȃ�

#define		PLTT_EX_SIZE	(32*16*16)		// �g���p���b�g�T�C�Y
#define		PLTT_NORMAL_SIZE (32*16)		// �W���p���b�g�T�C�Y

#define		PLT_DATA_ID_NONE	(0xffffffff)

//----------------------------------------------------------------------------
/**
 *					�\���̐錾
 */
//----------------------------------------------------------------------------
//-------------------------------------
///	�p���b�g�f�[�^�e�[�u��
//
typedef struct
{
	NNSG2dPaletteData*	pPlttData;			// �p���b�g�f�[�^�\����(��{�f�[�^�̕ێ�)
	NNS_G2D_VRAM_TYPE	type;				// VramType
											// main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN = 1
											// sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB = 2
											// �����ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAX = 3
	u32			load_size;					// �ǂݍ��݃T�C�Y
	u32			act_num;					// �o�^�@����ID
	NNSG2dImagePaletteProxy	PaletteProxy;	// �C���[�W�v���N�V	
	u32			offset;						// �����̃x�[�X�A�h���X
	u32			sub_offset;					// �����̃x�[�X�A�h���X
	u8			flag;						// �g�p���Ă��邩�̃t���O
} PLTT_DATA_TBL;


//-------------------------------------
//
//	�p���b�g�}�l�[�W���[�\����	
//
//=====================================
typedef struct{
	PLTT_DATA_TBL*	plttDataTbl;					// �p���b�g�f�[�^�e�[�u��
	int				plttDataNum;					// �p���b�g�f�[�^��
	int				plttDataNow;					// ���̃p���b�g�ǂݍ��ݐ�
	u32				Offset;							// �ǂݍ��ݎ��̃I�t�Z�b�g
	u32				SubOffset;						// �T�uVram�̃I�t�Z�b�g
	u32				OffsetEx;						// �g���p���b�g�I�t�Z�b�g
	u32				SubOffsetEx;					// �T�u�̊g���p���b�g�I�t�Z�b�g
	u32				MainExPlttVramSize;				// ���C���̊g���p���b�gVram�T�C�Y
	u32				SubExPlttVramSize;				// �T�u�̊g���p���b�gVram�T�C�Y
	u16				main16VramArea;					// ���C���̂P�U�FVram�G���A
	u16				sub16VramArea;					// �T�u�̂P�U�FVram�G���A
}PLTT_MANAGER_DATA;


//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
static void cleanPlttData(PLTT_DATA_TBL* data);						// �p���b�g�f�[�^������
static BOOL TransPlttData(const PLTT_MANAGER_HEADER* pPlttData, PLTT_DATA_TBL* tbl);							// �p���b�g�f�[�^�]��
static BOOL TransPlttDataCleanVram(const PLTT_MANAGER_HEADER* pPlttData, PLTT_DATA_TBL* tbl);							// �p���b�g�f�[�^�]��
static BOOL LoadPlttData(const PLTT_MANAGER_HEADER* pPlttData, PLTT_DATA_TBL* tbl);		// �p���b�g�f�[�^�ǂݍ���
static void setTransPltt( PLTT_DATA_TBL* pPlttData );
static void transVramPltt( void* p_data );		// �p���b�g
static void setVramPlttSize( void );			// Vram�̃T�C�Y���Z�b�g
static void dellPlttData( PLTT_DATA_TBL* pPlttData );	// �p���b�g�f�[�^��j������
static PLTT_DATA_TBL* getPlttDataPtr( int id );	// ID�̃p���b�g�f�[�^�擾
static PLTT_DATA_TBL* getPlttDataClean( void );	// �󂢂Ă���p���b�g�f�[�^�擾

// �]���G���A�̐ݒ�
static void transAreaSet( u16* data, int num, int start );
static void transAreaClean( u16* data, int num, int start );
static int transAreaCheck( u16 data, int num );
static void transAreaInit( PLTT_MANAGER_DATA* data );
static void transAreaSetTbl( PLTT_DATA_TBL* data );
static void transAreaCleanTbl( PLTT_DATA_TBL* data );

// �I�t�Z�b�g�ړ��̎��̓]���G���A�擾
static BOOL transAreaCheckOffset( PLTT_DATA_TBL* data, u32 m_offs, u32 s_offs, u32 m_limit, u32 s_limit );
static void transAreaSetOffset( PLTT_DATA_TBL* data, u32* m_offs, u32* s_offs );


// �O���[�o���ϐ�
static PLTT_MANAGER_DATA* PlttManagerData = NULL;
// ��X�S�֐��͂��̃f�[�^�̃|�C���^�������ɂ���悤�ɕύX���s��
// ���͂��̃f�[�^���ǂ��ŕێ�����΂悢�̂��킩��Ȃ����߁A
// �����Ŏ���



//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�}�l�[�W���[������
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void InitPlttManager(int PlttDataNum, int heap)
{
	int i;
	
	// �p���b�g�}�l�[�W���[�V�X�e���̃f�[�^���쐬
	if(PlttManagerData == NULL){
		PlttManagerData = sys_AllocMemory(heap, sizeof(PLTT_MANAGER_DATA));
		MI_CpuClear32(PlttManagerData, sizeof(PLTT_MANAGER_DATA));
		
		PlttManagerData->plttDataNum = PlttDataNum;	// �Ǘ��p���b�g������

		// �p���b�g�Ǘ������̊Ǘ��̈���쐬
		PlttManagerData->plttDataTbl = sys_AllocMemory(heap, sizeof(PLTT_DATA_TBL)*PlttDataNum);
		
		for(i=0;i<PlttDataNum;i++){	
			cleanPlttData(PlttManagerData->plttDataTbl + i);
		}
		
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	CleanArea�֐��g�p�֎~�p���b�g�ݒ�
 *
 *	@param	msk		�g�p�֎~�p���b�g�}�X�N
 *	@param	disp	���
 *
 *	@return	none
 *
 *	disp
 *		main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN = 1
 *		sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB = 2
 *
 *	�}�X�N�萔
	// �p���b�gVRAM�\��}�X�N
	PLTTMAN_RESERVE_PLT0  =1 << 0,	
	PLTTMAN_RESERVE_PLT1  =1 << 1,	
	PLTTMAN_RESERVE_PLT2  =1 << 2,	
	PLTTMAN_RESERVE_PLT3  =1 << 3,	
	PLTTMAN_RESERVE_PLT4  =1 << 4,	
	PLTTMAN_RESERVE_PLT5  =1 << 5,	
	PLTTMAN_RESERVE_PLT6  =1 << 6,	
	PLTTMAN_RESERVE_PLT7  =1 << 7,	
	PLTTMAN_RESERVE_PLT8  =1 << 8,	
	PLTTMAN_RESERVE_PLT9  =1 << 9,	
	PLTTMAN_RESERVE_PLT10  =1 << 10,	
	PLTTMAN_RESERVE_PLT11  =1 << 11,	
	PLTTMAN_RESERVE_PLT12  =1 << 12,	
	PLTTMAN_RESERVE_PLT13  =1 << 13,	
	PLTTMAN_RESERVE_PLT14  =1 << 14,	
	PLTTMAN_RESERVE_PLT15  =1 << 15,	


 *	�ʐM�pOAM�\���p�p���b�g�̈�̊m�ۂȂǂɎg�p���Ă��������B
 *
 *	���g�p�㒍��
	GLOBAL void PlttLoadStartAll( void );
	GLOBAL void PlttLoadStart( u32 start_offset );
	GLOBAL void PlttLoadStartSub( u32 start_offset );
	GLOBAL void PlttLoadStartEx( u32 start_offset );
	GLOBAL void PlttLoadStartSubEx( u32 start_offset );
 *	���g�p������ɂ��̐ݒ�����Ă��������B
 *	��̂T�̊֐��̒��ŁA�֎~�̈�̏��������s���Ă��܂��܂�
 */
//-----------------------------------------------------------------------------
void SetReserveCleanAreaPlttManager( u16 msk, u32 disp )
{
	if( disp == NNS_G2D_VRAM_TYPE_2DMAIN ){
		PlttManagerData->main16VramArea |= msk;
	}else if( disp == NNS_G2D_VRAM_TYPE_2DSUB ){
		PlttManagerData->sub16VramArea |= msk;
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�}�l�[�W���[�j��
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void DeletePlttManager(void)
{
	if(PlttManagerData != NULL){
		DelPlttAll();		// �S�p���b�g�f�[�^��j��
		sys_FreeMemoryEz(PlttManagerData->plttDataTbl);	// �p���b�g�Ǘ��̈��j��
		sys_FreeMemoryEz(PlttManagerData);				// �p���b�g�}�l�[�W���[�V�X�e���̈��j��
		PlttManagerData = NULL;
	}
}

/*-----------------------------------------------------------------------------
 *
 *					
 *
 *	����
 *		
 *
 *	�߂�l
 *		
 *					
 *
 ----------------------------------------------------------------------------*/
static void now_debug_draw( void )
{
#ifdef PLTT_MANAGER_OS_PRINTF_ON
	OS_Printf( "���̃I�t�Z�b�g\n" );
	OS_Printf( "���C��[%d] �T�u[%d]\n", PlttManagerData->Offset, PlttManagerData->SubOffset );
	OS_Printf( "�g�����C��[%d] �g���T�u[%d]\n", PlttManagerData->OffsetEx, PlttManagerData->SubOffsetEx );
#endif
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	���[�h���J�n����֐�
 *
 *@param	start_offset�F�ǂݍ��݊J�noffset
 *
 *@return	none
 *	(�����Ǘ��̃I�t�Z�b�g��������)
 */
//-----------------------------------------------------------------------------
/// ���C����ʁ@�W���p���b�g
void PlttLoadStart( u32 start_offset )
{
	PlttManagerData->Offset = start_offset;
	setVramPlttSize();

	transAreaInit( PlttManagerData );
}
/// �T�u��ʁ@�W���p���b�g
void PlttLoadStartSub( u32 start_offset )
{
	PlttManagerData->SubOffset = start_offset;
	setVramPlttSize();
	transAreaInit( PlttManagerData );
}

/// ���C����ʁ@�g���p���b�g
void PlttLoadStartEx( u32 start_offset )
{
	PlttManagerData->OffsetEx = start_offset;
	setVramPlttSize();
	transAreaInit( PlttManagerData );
}

/// �T�u��ʁ@�g���p���b�g
void PlttLoadStartSubEx( u32 start_offset )
{
	PlttManagerData->SubOffsetEx = start_offset;
	setVramPlttSize();
	transAreaInit( PlttManagerData );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g���Ǘ����Ă�������I�t�Z�b�g�l���擾����
 *
 *	@param	none 
 *
 *	@return	int		�I�t�Z�b�g�l
 *
 *
 */
//-----------------------------------------------------------------------------
/// ���C����ʁ@�W���p���b�g
int PlttLoadOffsetGetMain( void )
{
	return PlttManagerData->Offset;
}
/// �T�u��ʁ@�W���p���b�g
int PlttLoadOffsetGetSub( void )
{
	return PlttManagerData->SubOffset;
}

/// ���C����ʁ@�g���p���b�g
int PlttLoadOffsetGetMainEx( void )
{
	return PlttManagerData->OffsetEx;
}

/// �T�u��ʁ@�g���p���b�g
int PlttLoadOffsetGetSubEx( void )
{
	return PlttManagerData->SubOffsetEx;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���[�h���J�n����֐�
 *							�S�Ă��O�ŏ���������
 *
 *@param	none	
 *
 *@return	none
 *					(�����Ǘ��̃I�t�Z�b�g��������)
 *
 */
//-----------------------------------------------------------------------------
void PlttLoadStartAll( void )
{
	PlttManagerData->Offset			= 0;					// �ǂݍ��ݎ��̃I�t�Z�b�g
	PlttManagerData->SubOffset		= 0;					// �T�uVram�̃I�t�Z�b�g
	PlttManagerData->OffsetEx		= 0;					// �g���p���b�g�I�t�Z�b�g
	PlttManagerData->SubOffsetEx	= 0;					// �T�u�̊g���p���b�g�I�t�Z�b�g
	setVramPlttSize();										// VramBank�̊��蓖�Ă���Vram���g�p�ł���ʂ��v�Z
	transAreaInit( PlttManagerData );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^�P�̂��Z�b�g���ă��[�h
 *
 *@param	pPlttData�F�p���b�g�f�[�^
 *
 *@retval	TRUE �F�Z�b�g�ł���
 *@retval	FALSE�F�Z�b�g�ł��Ȃ�����
 *
 */
//-----------------------------------------------------------------------------
BOOL PlttSet( const PLTT_MANAGER_HEADER* pPlttData )
{
	PLTT_DATA_TBL* tbl;

	// �󂢂Ă���e�[�u�����擾
	tbl = getPlttDataClean();

	// �e�[�u���������肽���`�F�b�N
	if( tbl == NULL ){
		GF_ASSERT(0&&("�e�[�u������t�œo�^�ł��܂���"))
		return FALSE;		// �o�^�s�\
	}
	
	// �p���b�g�f�[�^�ǂݍ���
	if(LoadPlttData(pPlttData, tbl) == FALSE){
		return FALSE;
	}
		

	// �p���b�g�f�[�^�]��
	if( TransPlttData(pPlttData, tbl) == FALSE ){
		//���s�����Ƃ��͔j��
		//���s�����Ƃ���Vram�ɂ��܂�̃T�C�Y���Ȃ�
		DelPltt( pPlttData->id );
		return FALSE;
	}

	// Vram�G���A�ݒ�
	transAreaSetTbl( tbl );

	return TRUE;
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^�𕡐��Z�b�g
 *
 *@param	pPlttData�F�p���b�g�f�[�^
 *@param	num			�Z�b�g��
 *
 *@return	�����o�^����������
 *
 */
//-----------------------------------------------------------------------------
u16 PlttSets( const PLTT_MANAGER_HEADER* pPlttData, int num )
{
	int i;			// ���[�v�p
	
	//
	// PLTT_END������܂œǂݍ���
	//
	for(i=0;i<num;i++){
		// �ǂݍ��݁��Z�b�g����
		if( PlttSet( pPlttData + i ) == FALSE ){
			// ���s
			break;
		}
	}

	return i;
}


// �r�b�g���`�F�b�N����
// ���󂢂Ă���ꏊ�ɓ]�����܂��B
// OFFSET�w�肵�ē]���������Ƃ��͏�̓]���֐����g�p���Ă�������
//----------------------------------------------------------------------------
/**
 *@brief	�p���b�g�f�[�^�P�̂��Z�b�g���ă��[�h
 *
 *@param	pPlttData�F�p���b�g�f�[�^
 *
 *@retval	TRUE �F�Z�b�g�ł���
 *			FALSE�F�Z�b�g�ł��Ȃ�����
 */
//-----------------------------------------------------------------------------
BOOL PlttSetCleanArea( const PLTT_MANAGER_HEADER* pPlttData )
{
	PLTT_DATA_TBL* tbl;

	// �󂢂Ă���e�[�u�����擾
	tbl = getPlttDataClean();

	// �e�[�u���������肽���`�F�b�N
	if( tbl == NULL ){
		GF_ASSERT(0&&("�e�[�u������t�œo�^�ł��܂���"))
		return FALSE;		// �o�^�s�\
	}
	
	// �p���b�g�f�[�^�ǂݍ���
	if(LoadPlttData(pPlttData, tbl) == FALSE){
		return FALSE;
	}
		

	// �p���b�g�f�[�^�]��
	if( TransPlttDataCleanVram(pPlttData, tbl) == FALSE ){
		//���s�����Ƃ��͔j��
		//���s�����Ƃ���Vram�ɂ��܂�̃T�C�Y���Ȃ�
		DelPltt( pPlttData->id );
		return FALSE;
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^�𕡐��Z�b�g
 *
 *@param	pPlttData	�p���b�g�f�[�^
 *@param	num			�Z�b�g���鐔
 *
 *@return	�����o�^����������
 */
//-----------------------------------------------------------------------------
u16 PlttSetsCleanArea( const PLTT_MANAGER_HEADER* pPlttData, int num )
{
	int i;			// ���[�v�p
	
	//
	// PLTT_END������܂œǂݍ���
	//
	for(i=0;i<num;i++){
		// �ǂݍ��݁��Z�b�g����
		if( PlttSetCleanArea( pPlttData + i ) == FALSE ){
			// ���s
			break;
		}
	}

	return i;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�f�[�^�]��
 *
 *	@param	id			�]����̃p���b�gID
 *	@param	pPlttData	�p���b�g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void PlttDataChg( int id, NNSG2dPaletteData* pPlttData )
{
	PLTT_DATA_TBL* tbl;
	
	GF_ASSERT( pPlttData );

	// id�̃f�[�^�擾
	tbl = getPlttDataPtr(id);
	GF_ASSERT( tbl );
	
	
	tbl->pPlttData = pPlttData;
	
	if( tbl->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		// Vram
		// �]���}�l�[�W���œ]��
		AddVramTransferManager(
			NNS_GFD_DST_2D_OBJ_PLTT_MAIN,
			tbl->offset,
			pPlttData->pRawData,
			tbl->load_size * PLTT_ONE_SIZE
			);
	}
	if( tbl->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		// Vram
		// �]���}�l�[�W���œ]��
		AddVramTransferManager(
			NNS_GFD_DST_2D_OBJ_PLTT_SUB,
			tbl->sub_offset,
			pPlttData->pRawData,
			tbl->load_size * PLTT_ONE_SIZE
			);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	id�̃p���b�g�f�[�^�������o�^����Ă��邩�`�F�b�N
 *
 *@param	id		�`�F�b�N����id
 *
 *@retval	TRUE	�o�^����Ă���
 *@retval	FALSE	�o�^����Ă��Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CheckPlttID(int id)
{
	PLTT_DATA_TBL* tbl;

	tbl = getPlttDataPtr(id);
	if(tbl){		// �o�^�ς�
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���Ƃ����o�^�ł���̂���Ԃ�
 *
 *@param	none
 *
 *@return	int		�c��o�^�\��
 *
 *
 */
//-----------------------------------------------------------------------------
int CheckPlttRest(void)
{
	return PlttManagerData->plttDataNum - PlttManagerData->plttDataNow;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^��j
 *
 *@param	p_str�F�p���b�g�t�@�C����
 *	
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DelPltt( int id )
{
	PLTT_DATA_TBL* tbl;			// �v�f���擾�p

	// �v�f�����擾
	tbl = getPlttDataPtr(id);
	
	// �ő吔���`�F�b�N
	GF_ASSERT(tbl);
	
	// �L�����N�^�f�[�^��j������
	// �ғ������`�F�b�N
	if( tbl->flag == 1 ){
		// Vram�G���A�j��
		transAreaCleanTbl( tbl );
		// �f�[�^�j��
		dellPlttData( tbl );	
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�S�p���b�g�f�[�^��j��
 *
 *@param	none
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DelPlttAll( void )
{
	int i;

	//
	// �S�p���b�g�f�[�^��j��
	//
	// �p���b�gID�̃e�[�u����T��
	for( i = 0; i < PlttManagerData->plttDataNum; i++ ){
		// �ғ������`�F�b�N
		if( PlttManagerData->plttDataTbl[ i ].flag == 1 ){
			// Vram�G���A�j��
			transAreaCleanTbl( &PlttManagerData->plttDataTbl[ i ] );
			// �f�[�^�j��
			dellPlttData( &PlttManagerData->plttDataTbl[ i ] );

		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ID�̃p���b�g�v���N�V���擾
 *
 *@param	id		�p���b�gID
 *
 *@return	ID�̃v���N�V
 *
 */
//-----------------------------------------------------------------------------
NNSG2dImagePaletteProxy* GetPlttIDProxy( int id )
{
	PLTT_DATA_TBL* tbl;			// �v�f�f�[�^

	// �v�f�����擾
	tbl = getPlttDataPtr(id);
	if( tbl == NULL ){
		GF_ASSERT(tbl);
		return NULL;
	}

	// �ғ����Ȃ�Ԃ�
	if(tbl->flag == 1){
		return &tbl->PaletteProxy;
	}
	
	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�v���N�V�̎擾
 *			�p���b�g�̃��[�h�i�g���p���b�g�j�ɃC���[�W�v���N�V���œK������
 *					�p���b�g�v���N�V�擾�֐�
 *
 *@param	id		�p���b�gID
 *@param	pImage�F�C���[�W�v���N�V
 *
 *@return	�p���b�g�v���N�V
 *
 */
//-----------------------------------------------------------------------------
NNSG2dImagePaletteProxy* GetPlttIDProxyJoin( int id, NNSG2dImageProxy* pImage )
{
	PLTT_DATA_TBL* tbl;			// �v�f�f�[�^

	// �v�f�����擾
	tbl = getPlttDataPtr(id);
	if( tbl == NULL ){
		GF_ASSERT(tbl);
		return NULL;
	}
	// �ғ������`�F�b�N
	if( tbl->flag != 1 ){
		return NULL;
	}

	// �g���p���b�g���`�F�b�N
	if( tbl->pPlttData->bExtendedPlt ){
		// �C���[�W�v���N�V�Ɋg���p���b�g�����悤����悤�ɐݒ�
		NNS_G2dSetImageExtPaletteFlag( pImage, TRUE );
	}
	
	return &tbl->PaletteProxy;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�v���N�V�̂���p���b�g�i���o�[���擾����
 *
 *@param	pPltt�F�p���b�g�i���o�[���擾����p���b�g�v���N�V
 *@param	vramType�F���C���ʂ��T�u�ʂ�
 *
 *@return	�p���b�g�i���o�[
 *
 */
//-----------------------------------------------------------------------------
u32 GetPlttProxyOffset( const NNSG2dImagePaletteProxy* pPltt, u32 vramType )
{
	u32 size;			// �P�p���b�g�T�C�Y
	u32 pltt_offset;	// �p���b�g�i���o�[�v�Z�����p
	
	// �g���p���b�g���`�F�b�N
	if( pPltt->bExtendedPlt ){
		size = PLTT_ONE_SIZE * 16;
	}else{
		// �W����256�łȂ����`�F�b�N
		if( pPltt->fmt == GX_TEXFMT_PLTT256 ){
			// 256�̎��̓T�C�Y���O�ɂ��Čv�Z���Ȃ�
			size = 0;
		}else{
			size = PLTT_ONE_SIZE;
		}
	}

	// �W���Q�T�U�F�ȊO���`�F�b�N
	if( size != 0 ){
		// ���炷�l�擾
		pltt_offset = NNS_G2dGetImagePaletteLocation( pPltt, vramType );
		pltt_offset /= size;			// ���炷�l�ɂ���(���p���b�g���炷��)
	}else{
		pltt_offset = 0;
	}

	return pltt_offset;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�i���o�[�̃v���N�V���擾����
 *
 *@param	pltt_offset�F���̃p���b�g�i���o�[�̃v���N�V����������Ԃ�
 *@param	type�F�P�U�F�A�g���p���b�g���̃t���O()
 *@param	vramType�F�p���b�g�i���o�[�����킹��Vram�̃^�C�v		�P�F���C���@�Q�F�T�u
 *
 *@return	���������v���N�V
 *@retval	������Ȃ��Ƃ���NULL
 *
 */
//-----------------------------------------------------------------------------
NNSG2dImagePaletteProxy* GetPlttNumProxy( u32 pltt_offset, u32 type, u32 vramType )
{
	int i;			// ���[�v�p
	u32	now_idx;	// ���̃p���b�g�i���o�[
	u32 end_idx;	// �I���p���b�g�i���o�[
	
	
	//
	// �o�^����Ă���A�p���b�g����pltt_offset�̃p���b�g��
	// �o�^����Ă���p���b�g�v���N�V��Ԃ�
	//
	for( i = 0; i < PlttManagerData->plttDataNum; i++ ){
		// �ғ������`�F�b�N
		if( PlttManagerData->plttDataTbl[ i ].flag == 1 ){
			// Type���ꏏ���`�F�b�N
			if( ((type == 1) && (PlttManagerData->plttDataTbl[ i ].pPlttData->bExtendedPlt > 0 )) ||
				((type == 0) && (PlttManagerData->plttDataTbl[ i ].pPlttData->bExtendedPlt == 0 )) ){
				
				// Vram�I�t�Z�b�g�擾
				now_idx = NNS_G2dGetImagePaletteLocation( &PlttManagerData->plttDataTbl[ i ].PaletteProxy, vramType );

				// �T�C�Y����I���I�t�Z�b�g���v�Z
				end_idx = now_idx + (PlttManagerData->plttDataTbl[ i ].load_size * PLTT_ONE_SIZE);
		
				// �e�N�X�`��Type�̃T�C�Y�Ŋ���
				if(type == 1){
					now_idx /= PLTT_ONE_SIZE * 16;		// �g��
					end_idx /= PLTT_ONE_SIZE * 16;		// �g��
				}else{	
					now_idx /= PLTT_ONE_SIZE;			// �W�� �P�U�F
					end_idx /= PLTT_ONE_SIZE;			// �W�� �P�U�F
				}

				// now_idx��end_idx�̒���pltt_offset�����邩�`�F�b�N
				if( (now_idx <= pltt_offset) && (end_idx >= pltt_offset) ){
					break;		// ���̃p���b�g�v���N�V�̃f�[�^���ɂ���
				}

				// ����now_idx����pltt_offset���������Ȃ��������
				// ���̈ʒu�ɑΉ�����p���b�g�f�[�^�͂Ȃ����ƂɂȂ�
				if( now_idx > pltt_offset ){
					return NULL;
				}
			}
		}
	}

	// �Ō�܂ōs������NULL��Ԃ�
	if(i == PlttManagerData->plttDataNum){
		return NULL;
	}

	return &PlttManagerData->plttDataTbl[ i ].PaletteProxy;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�����삳��Ă���p���b�g�v���N�V�̒��Ɉ����̃v���N�V�����邩��������
 *
 *@param	pPltt	��������v���N�V
 *
 *@return	BOOL	TRUE	����	FALSE	�Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL SearchPlttProxy( const  NNSG2dImagePaletteProxy* pPltt)
{
	int i;
	BOOL ret = FALSE;

	for(i=0;i<PlttManagerData->plttDataNum;i++){
		// �ғ������`�F�b�N
		if( PlttManagerData->plttDataTbl[ i ].flag == 1 ){
			// ID���`�F�b�N
			if( &PlttManagerData->plttDataTbl[ i ].PaletteProxy == pPltt ){
				ret = TRUE;
				break;
			}	
		}
	}

	return ret;
}

//
// �v���C�x�[�g�֐�
//
//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^��j������
 *
 *@param	pPlttData�F�j������p���b�g�f�[�^
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void dellPlttData( PLTT_DATA_TBL* pPlttData )
{
	// �j������
	cleanPlttData(pPlttData);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^�̓ǂݍ���
 *
 *@param	pPlttData	�p���b�gENTRY�f�[�^
 *@param	tbl			�ǂݍ��ރe�[�u���|�C���^
 *
 *@return	BOOL	�ǂݍ��ݐ���:TRUE	�ǂݍ��ݎ��s:FALSE
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL LoadPlttData(const PLTT_MANAGER_HEADER* pPlttData, PLTT_DATA_TBL* tbl)
{
	// �p���b�g�f�[�^�ݒ�
	tbl->pPlttData = pPlttData->res_file;
	
	// ID���d�����Ȃ����`�F�b�N
	if(CheckPlttID(pPlttData->id) == TRUE){
		GF_ASSERT(0);
		return FALSE;
	}
	
	// ID���t�@�C��������擾
	tbl->act_num = pPlttData->id;
	
	// �e�[�u���Z�b�g
	tbl->type	= pPlttData->type;			// Vramtype
	tbl->flag			= 1;						// �g�p��
	tbl->load_size = pPlttData->pltt_num;	// �ǂݍ��ރp���b�g��	

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^������
 *
 *@param	data		�p���b�g�f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanPlttData(PLTT_DATA_TBL* data)
{
	memset( data, 0, sizeof(PLTT_DATA_TBL) );
	data->act_num	= PLT_DATA_ID_NONE;
	NNS_G2dInitImagePaletteProxy( &data->PaletteProxy );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^�̓]��
 *
 *@param	tbl	�]������p���b�g�f�[�^
 *
 *@return	BOOL	�]������:TRUE	�]�����s:FALSE
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL TransPlttData(const PLTT_MANAGER_HEADER* pPlttData, PLTT_DATA_TBL* tbl)
{
	u32* p_offset;
	u32* p_offset_sub;
	BOOL dell_flag = TRUE;		// �̈�I�[�o�[�̂Ƃ�FALSE�ɂȂ�t���O
	u32 vram_limit;				// ���C����Vram�̈��limit
	u32 vram_limit_sub;			// �T�u��Vram�̈��limit
	
	// �g���p���b�g���`�F�b�N
	if( tbl->pPlttData->bExtendedPlt ){
		// �I�t�Z�b�g�l�̃|�C���^���Z�b�g
		p_offset		= &PlttManagerData->OffsetEx;
		p_offset_sub	= &PlttManagerData->SubOffsetEx; 
		vram_limit = PlttManagerData->MainExPlttVramSize;			// Vram�̗̈�̃T�C�Y
		vram_limit_sub = PlttManagerData->SubExPlttVramSize;			// Vram�̗̈�̃T�C�Y
	}else{	
		// �I�t�Z�b�g�l�̃|�C���^���Z�b�g
		p_offset		= &PlttManagerData->Offset;
		p_offset_sub	= &PlttManagerData->SubOffset;
		vram_limit = PLTT_NORMAL_SIZE;		// Vram�̗̈�̃T�C�Y
		vram_limit_sub = PLTT_NORMAL_SIZE;	// Vram�̗̈�̃T�C�Y
	}
	
	// �]�����ݒ�
	transAreaCheckOffset( tbl, *p_offset, *p_offset_sub, vram_limit, vram_limit_sub );

	// offset�ʒu�Ƀ��[�h
	setTransPltt( tbl );

	// �I�t�Z�b�g�����炷
	transAreaSetOffset( tbl, p_offset, p_offset_sub );

	return dell_flag;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�󂢂Ă���̈��T���ăp���b�g�f�[�^��]������
 *
 *	@param	pPlttData		�p���b�gENTRY�f�[�^
 *	@param	tbl				�e�[�u��
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL TransPlttDataCleanVram(const PLTT_MANAGER_HEADER* pPlttData, PLTT_DATA_TBL* tbl)
{
	int offset_m, offset_s;		// ���C���ƃT�u�̃I�t�Z�b�g
	
	// �g���p���b�g���`�F�b�N
	if( tbl->pPlttData->bExtendedPlt ){
		// �g���p���b�g�͖����ł�
		GF_ASSERT(0);
	}

	// �G���A�T��
	if( tbl->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		offset_m = transAreaCheck( PlttManagerData->main16VramArea, tbl->load_size );

		if(offset_m == PLTT_AREA_NONE){
			return FALSE;
		}
	}
	if( tbl->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		offset_s = transAreaCheck( PlttManagerData->sub16VramArea, tbl->load_size );
		
		if(offset_s == PLTT_AREA_NONE){
			return FALSE;
		}
	}

	// �I�t�Z�b�g��ݒ�
	if( tbl->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		tbl->offset = offset_m;
	}
	if( tbl->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		tbl->sub_offset = offset_s;
	}

	// �p���b�g�T�C�Y�ݒ�
	tbl->pPlttData->szByte = tbl->load_size * PLTT_ONE_SIZE;
	
	// �]��
	transVramPltt( tbl );

	// Vram�G���A�ݒ�
	transAreaSetTbl( tbl );
	

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p�X�̃p���b�g�f�[�^�̗v�f�����擾����
 *
 *@param	id		�p���b�gID
 *
 *@return	PLTT_DATA_TBL*	�p���b�g�f�[�^�e�[�u���|�C���^
 *
 */
//-----------------------------------------------------------------------------
static PLTT_DATA_TBL*	getPlttDataPtr( int id )
{
	int i;			// ���[�v�p

	
	
	// ID�̃f�[�^���������ăv���N�V��Ԃ�
	for( i = 0; i < PlttManagerData->plttDataNum; i++ ){
		// ID���`�F�b�N
		if( PlttManagerData->plttDataTbl[ i ].act_num == id ){
			return PlttManagerData->plttDataTbl + i;
		}	
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�󂢂Ă���e�[�u�����擾
 *
 *@param	none
 *
 *@return	PLTT_DATA_TBL* �󂢂Ă���e�[�u��
 *
 *
 */
//-----------------------------------------------------------------------------
static PLTT_DATA_TBL* getPlttDataClean( void )
{
	int i;
	
	// �p���b�g�f�[�^���e�[�u���ɃZ�b�g
	for( i = 0; i < PlttManagerData->plttDataNum; i++ ){
		// �����Ă���Ƃ�����T�[�`
		if( PlttManagerData->plttDataTbl[ i ].flag == 0 ){
			return PlttManagerData->plttDataTbl + i;
		}
	}
	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g��Vram�T�C�Y���Z�b�g
 *
 *@param	none
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void setVramPlttSize( void )
{
	GXVRamOBJExtPltt	vram_bank;		// ���C��Vram�o���N�擾�p
	GXVRamSubOBJExtPltt	sub_vram_bank;	// �T�uVram�o���N�擾�p
	
	
	//
	// Vram�̃p���b�g�T�C�Y���Z�b�g
	//
	// ���C�����
	vram_bank = GX_GetBankForOBJExtPltt();
	switch( vram_bank ){
	case GX_VRAM_OBJEXTPLTT_0_F:	// ���C����ʊg���p���b�g�g�p
	case GX_VRAM_OBJEXTPLTT_0_G:	// ���C����ʊg���p���b�g�g�p
		PlttManagerData->MainExPlttVramSize = PLTT_EX_SIZE;
		break;

	default:
		PlttManagerData->MainExPlttVramSize = 0;	
		break;
	}

	// �T�u���
	sub_vram_bank = GX_GetBankForSubOBJExtPltt();
	switch( sub_vram_bank ){
	case GX_VRAM_SUB_OBJEXTPLTT_0_I:	// ���C����ʊg���p���b�g�g�p
		PlttManagerData->SubExPlttVramSize = PLTT_EX_SIZE;
		break;

	default:
		PlttManagerData->SubExPlttVramSize = 0;	
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^�]��������V�u�����N�����^�X�N�ɃZ�b�g
 *
 *@param	pPlttData�F�p���b�g�f�[�^
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void setTransPltt( PLTT_DATA_TBL* pPlttData )
{

	// ���\�[�X�̃T�C�Y���ύX
	pPlttData->pPlttData->szByte = pPlttData->load_size * PLTT_ONE_SIZE;
	
	transVramPltt( pPlttData);

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vblank���ōs���p���b�g�f�[�^��Vram�ւ̓]��
 *
 *@param	p_data�F�]������p���b�g�f�[�^
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void transVramPltt( void* p_data )
{
	PLTT_DATA_TBL* p_pltt_data = (PLTT_DATA_TBL*)p_data;		// �L���X�g���ăf�[�^�擾

	NNS_G2dInitImagePaletteProxy(&p_pltt_data->PaletteProxy);
	
	// Vram�֓ǂݍ���
	if(p_pltt_data->type & NNS_G2D_VRAM_TYPE_2DMAIN){
		// �����ɓo�^
		NNS_G2dLoadPalette(
				p_pltt_data->pPlttData,// �L�����N�^�f�[�^
				p_pltt_data->offset,			// �L�����N�^�x�[�X�A�h���X
				NNS_G2D_VRAM_TYPE_2DMAIN,		// VramType
				&p_pltt_data->PaletteProxy );	// �C���[�W�v���N�V
	}

	if(p_pltt_data->type & NNS_G2D_VRAM_TYPE_2DSUB){
		NNS_G2dLoadPalette(
				p_pltt_data->pPlttData,// �L�����N�^�f�[�^
				p_pltt_data->sub_offset,		// �L�����N�^�x�[�X�A�h���X
				NNS_G2D_VRAM_TYPE_2DSUB,		// VramType
				&p_pltt_data->PaletteProxy );	// �C���[�W�v���N�V
	}
}



// �]���G���A�̐ݒ�
static void transAreaSet( u16* data, int num, int start )
{
	int i;		// ���[�v�p
	
	for(i=0;i<num;i++){

		*data |= 1 << (start + i);
	}
}

static void transAreaClean( u16* data, int num, int start )
{
	int i;		// ���[�v�p
	
	for(i=0;i<num;i++){

		*data &= ~( 1 << (start + i) );
	}
}

static int transAreaCheck( u16 data, int num )
{
	int i, j;		// ���[�v�p
	
	for(i = 0; i < 16; i++ ){
		
		j = 0;
		// �r�b�g�������Ă��Ȃ��ā@�J�E���^��num��菬�����Ƃ�
		while( ( (data & (1 << ( i + j))) == 0 ) && (j < num) ){

			// �T�C�Y�I�[�o�[������I���
			if( (i + j) >= 16 ){
				break;
			}

			j++;
		}
	
		// �T�C�Y���̗̈悪���������`�F�b�N
		if(j >= num){
			break;
		}

		i += j;		// ���߂�������Ԃ��΂�
	}

	// �Ō�܂�for��������Ă��������Ȃ��̂�err��Ԃ�
	if( i >= 16 )
	{
		return PLTT_AREA_NONE;
	}

	return i * PLTT_ONE_SIZE;
}

static void transAreaInit( PLTT_MANAGER_DATA* data )
{
	data->main16VramArea = 0;
	data->sub16VramArea = 0;
}

static void transAreaSetTbl( PLTT_DATA_TBL* data )
{
	if( data->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		transAreaSet( &PlttManagerData->main16VramArea, data->load_size, data->offset / PLTT_ONE_SIZE );
	}
	if( data->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		transAreaSet( &PlttManagerData->sub16VramArea, data->load_size, data->sub_offset / PLTT_ONE_SIZE );
	}
}

static void transAreaCleanTbl( PLTT_DATA_TBL* data )
{
	if( data->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		transAreaClean( &PlttManagerData->main16VramArea, data->load_size, data->offset / PLTT_ONE_SIZE );
	}
	if( data->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		transAreaClean( &PlttManagerData->sub16VramArea, data->load_size, data->sub_offset / PLTT_ONE_SIZE );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�t�Z�b�g���[�h�̓]���G���A����
 *
 *	@param	data	�p���b�g�f�[�^
 *	@param	m_offs	���̃I�t�Z�b�g�ʒu
 *	@param	s_offs	���̃I�t�Z�b�g�ʒu
 *
 *	@retval	TRUE		�擾����
 *	@retval	FALSE		�擾���s
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL transAreaCheckOffset( PLTT_DATA_TBL* data, u32 m_offs, u32 s_offs, u32 m_limit, u32 s_limit )
{
	BOOL dell_flag = TRUE;
	
	// ���C����ʂɓǂݍ��ނ��`�F�b�N
	if( data->type & NNS_G2D_VRAM_TYPE_2DMAIN ){

		// �T�C�Y�I�[�o�[�`�F�b�N
		if( (m_offs + (data->load_size * PLTT_ONE_SIZE) > m_limit) ){

			// �o�^���Ȃ�
			GF_ASSERT(0&&("�T�C�Y�I�[�o�["));
			now_debug_draw();		// ���̏󋵂�`��
			dell_flag = FALSE;
		}else{
			data->offset = m_offs;	
		}
		
	}

	// �T�u��ʂɓǂݍ��ނ��`�F�b�N
	if( data->type & NNS_G2D_VRAM_TYPE_2DSUB ){

		// �T�C�Y�I�[�o�[�`�F�b�N
		if( (s_offs + (data->load_size * PLTT_ONE_SIZE) > s_limit) ){

			// �o�^���Ȃ�
			GF_ASSERT(0&&("�T�C�Y�I�[�o�["));
			now_debug_draw();		// ���̏󋵂�`��
			dell_flag = FALSE;
		}else{
			data->sub_offset = s_offs;
		}
	}

	return dell_flag;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�t�Z�b�g���ړ�������
 *
 *	@param	data		�p���b�g�f�[�^
 *	@param	m_offs		���C���I�t�Z�b�g�̃|�C���^
 *	@param	s_offs		�T�u�I�t�Z�b�g�̃|�C���^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void transAreaSetOffset( PLTT_DATA_TBL* data, u32* m_offs, u32* s_offs )
{
	// ���炷
	if( data->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		*m_offs		+= data->load_size * PLTT_ONE_SIZE;
	}

	if( data->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		*s_offs		+= data->load_size * PLTT_ONE_SIZE;
	}
}
