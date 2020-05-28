//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *	@file		char_manager.c
 *	@brief		�L�����N�^�}�l�[�W���[�̎��ԕ�
 *	@author		tomoya takahashi
 *	@data		2004.11.22
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#define __CHAR_MANAGER_H_GLOBAL
#include "char_manager.h"
#include "system.h"
#include "gflib_os_print.h"
#include "assert.h"
#include "vram_transfer_manager.h"
#include <string.h>



//-----------------------------------------------------------------------------
/**
 *					�萔�錾
 */
//-----------------------------------------------------------------------------
#define		CHAR_VRAM_TRANS_SHIFT	(8)		// Vram���[�h���̃t���O�ɃV�t�g

#define	CHAR_DATA_ID_NONE	(0xffffffff)

// Vram�̈�Ǘ��萔
#define CHAR_VRAM_BANK_GET_ERR	(0xffffffff)				// �T�C�Y���Ȃ��Ƃ��̖߂�l
#define CHAR_ONE_SIZE	(32)		// �P�L�����N�^�T�C�Y


/// �t���O�̐ݒ�
enum
{
	CHAR_MAN_NONE,			// ����Ȃ�
	CHAR_MAN_DO_NORMAL,		// NORMAL���쒆
	CHAR_MAN_WAIT_VRAM_ORIG,// Vram�]���̃I���W�i���f�[�^�҂����
	CHAR_MAN_DO_VRAM_ORIG,	// Vram�]���̃I���W�i���f�[�^���쒆
	CHAR_MAN_DO_VRAM_COPY,	// Vram�]����Copy�f�[�^���쒆
};

// �L�����N�^���E�v�Z�p
enum{
	CHAR_MAN_LIM_SUB,		// ���܂��؂���
	CHAR_MAN_LIM_ADD		// ���܂�𖄂߂�
};
//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
///	�L�����N�^�f�[�^�e�[�u��
//
typedef struct
{
	NNSG2dCharacterData*	pCharData;	// �L�����N�^�f�[�^�\����(��{�f�[�^�̕ێ�)
	NNS_G2D_VRAM_TYPE		type;		// VramType
										// main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN = 1
										// sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB = 2
										// �����ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAX = 3
	u8			vramType;				// Vram�]�����̃t���O	�P�FVram�]��
	u32			act_num;				// �o�^�@����ID
	NNSG2dImageProxy	ImageProxy;		// �C���[�W�v���N�V
	u32			offset;					// �����̃x�[�X�A�h���X
	u32			sub_offset;				// �T�u�̃I�t�Z�b�g
	u8			flag;					// �g�p���Ă��邩�̃t���O
	BOOL		mapModeAdjust;			// �L�����N�^�}�b�s���O���[�h�����̏�Ԃɍ��킹�邩
	u32			cont_type;				// Vram�R���g���[���^�C�v
	
	BOOL		have_area;				// Vram�G���A��ێ����Ă��邩
	u32			have_szByte;			// Vram�m�ۃT�C�Y���C��
	u32			have_szByteSub;			// Vram�m�ۃT�C�Y�T�u
} CHAR_DATA_TBL;



//-------------------------------------
//	
//	�L�����N�^�}�l�[�W���[�\����
//	
//=====================================
typedef struct {
	CHAR_DATA_TBL*	charDataTbl;	// �L�����N�^�f�[�^�e�[�u��
	int		charDataNum;			// �L�����N�^�f�[�^��
	int		charDataNow;			// �L�����N�^�f�[�^�o�^�� 
	u32		Offset;					// �ǂݍ��ݎ��̃I�t�Z�b�g
	u32		SubOffset;				// �T�uVram�̃I�t�Z�b�g
	s32		MainObjVramSize;		// ���C����ʂ�VramBank�̃T�C�Y
	s32		SubObjVramSize;			// �T�u��ʂ�VramBank�̃T�C�Y
	s32		MainVramTransStart;		// ���C����ʂ�Vram�Ǘ��̈�̃X�^�[�g�ʒu
	s32		SubVramTransStart;		// �T�u��ʂ�Vram�Ǘ��̈�̃X�^�[�g�ʒu
	u32		TransAreaMainSize;		// ���C����ʂ�Vram�Ǘ��̈�	�i1024�̓�������]���Ɏg�������w�肵�܂��j
	u32		TransAreaSubSize;		// ���C����ʂ�Vram�Ǘ��̈�	�i1024�̓�������]���Ɏg�������w�肵�܂��j
	u32		MainModeCharLimit;		// ���C����ʂ̃L�����N�^���E
	u32		SubModeCharLimit;		// �T�u��ʂ̃L�����N�^���E
	u8*		TransAreaFlagMain;		// VramBank�����̃t���O���C����ʗp
	u8*		TransAreaFlagSub;		// VramBank�����̃t���O�T�u��ʗp
} CHAR_MANAGER_DATA;


//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
static void cleanCharData(CHAR_DATA_TBL* data);		// ������
static BOOL LoadCharData(const CHAR_MANAGER_HEADER* pEntData, CHAR_DATA_TBL* pCharData);		// �L�����N�^�f�[�^��ǂݍ���
static CHAR_DATA_TBL* getImageProxyTbl(const NNSG2dImageProxy* pImage);
static BOOL TransCharData(CHAR_DATA_TBL* tbl);		// �L�����N�^�f�[�^��]������
static BOOL TransCharOffset(CHAR_DATA_TBL* tbl);	// Offset�]�����[�h
static BOOL TransCharAreaCont(CHAR_DATA_TBL* tbl);	// areaCont�]�����[�h

static void setTransChar( CHAR_DATA_TBL* pCharData, u32 p_offset, u32 p_sub_offset );	// �]���}�l�[�W���[�ɃZ�b�g

static BOOL getvramTransOffset(int type, u32* main, u32* sub, u32 szByte, u32* get_size, u32* get_size_sub);
static void setvramTransOffsetProxy(CHAR_DATA_TBL* data, u32 main, u32 sub);
static void setvramTransBitData(int type, u32 main, u32 sub, u32 szByte, u32 szByteSub);

static void transVramChar( void* p_data );				// �L�����N�^
static void transVramCharCore( CHAR_DATA_TBL* data, int vram_type);
static void transVramCharVramMode( void* p_data );		// Vram�]���A�j�����[�h�̃L�����N�^
static void transVramCharVramModeCore( CHAR_DATA_TBL* data, int vram_type);
static u32 getTransAreaSize( u8* p_trans_flag );		// Vram�]��Vram�Ǘ��̈�̃T�C�Y�擾�p

static CHAR_DATA_TBL* getCharData( void );				// ��̃f�[�^�e�[�u�����擾
static void setObjVramSize( void );						// Vram�o���N�̃T�C�Y���Z�b�g
static void dellCharData( CHAR_DATA_TBL* pCharData );	// �L�����N�^�f�[�^��j��
static void delCharTblTransArea( CHAR_DATA_TBL* pCharData );	// �L�����N�^�f�[�^��Vram�G���A���J��
static CHAR_DATA_TBL* getCharDataPtr( int id );			// id�̃L�����N�^�f�[�^���擾
static void MakeTransArea( u32 main_size, u32 sub_size, int heap );		// Vram�]���pVram�G���A�̍쐬
static void DellTransArea( u8* p_trans_flag );					// Vram�]���pVram�G���A�̔j��
static void TransAreaInit( u8* p_trans_flag );			// Vram�]���pVram�G���A�̏�����

static void TransBitSet( u32 num, u32 size, u8* p_trans_flag );	// �]�������G���A�̃r�b�g��ݒ�
static u32 TransBitCheck( u32 size, u8* p_trans_flag );	// �]�������T�C�Y�̃G���A���c���Ă��邩�`�F�b�N
static void TransBitClean( u32 start_num, u32 size, u8* p_trans_flag );	// �ԋp�����G���A������������

static int charModeAdjust( CHAR_DATA_TBL* pCharData, int type );


// �]�����ׂ��I�t�Z�b�g�l���擾����֐�
static BOOL modeNormOffsetGet( u32 szByte, int type, u32* offs_main, u32* offs_sub );
static void modeNormOffsetMove( u32 szByte, int type );

static void byte8_byte1_Get( int num, u32* byte8, u8* byte1 );


static int getCharModeLimNum( int num, int limit, int flag );
static int getCharModeNum( int szByte, int limit );
static int getCharModeNum_byte( int szChar, int limit );

static void getReserveAreaContData( u32 areacont_start, u32 offset, u32 size, int* start_offset, int* set_size );

//----------------------------------------------------------------------------
/**
 *					�O���[�o���ϐ��錾
 */
//-----------------------------------------------------------------------------
static CHAR_MANAGER_DATA*	CharManager = NULL;
// ��X�͂��̃f�[�^���O���̎����A
// �e�֐��̈����ɂ��̃f�[�^��n���ē��삷��悤�ɂ���
// ���͒N�Ɏ�������΂悢�̂��킩��Ȃ����߁A�����Ŏ���


//
// �O���[�o���֐�
//
//----------------------------------------------------------------------------
/**
 *
 *@brief	  �L�����N�^�}�l�[�W���[��������
 *
 *@param	CharMakeData	�L�����N�^�}�l�[�W���[�쐬�f�[�^
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void InitCharManager( const CHAR_MANAGER_MAKE* CharMakeData )
{
	// ������
	InitCharManagerReg( CharMakeData, GX_GetOBJVRamModeChar(), GXS_GetOBJVRamModeChar() );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�}�l�[�W����������
 *
 *	@param	CharMakeData	�L�����N�^�}�l�[�W���쐬�f�[�^
 *	@param	modeMain		�L�����N�^�}�b�s���O���[�h�@���C�����
 *	@param	modeSub			�L�����N�^�}�b�s���O���[�h�@�T�u���
 *
 *	@return	none
 *
 */
//-----------------------------------------------------------------------------
void InitCharManagerReg( const CHAR_MANAGER_MAKE* CharMakeData, GXOBJVRamModeChar modeMain, GXOBJVRamModeChar modeSub )
{
	int i;
	int main_size_cm;
	int sub_size_cm;
	
	if(CharManager == NULL){
		CharManager = sys_AllocMemory(CharMakeData->heap, sizeof(CHAR_MANAGER_DATA));
		MI_CpuClear32(CharManager, sizeof(CHAR_MANAGER_DATA));

		CharManager->charDataNum = CharMakeData->CharDataNum;
		CharManager->charDataTbl = sys_AllocMemory(CharMakeData->heap, sizeof(CHAR_DATA_TBL)*CharManager->charDataNum);


		for(i=0;i<CharMakeData->CharDataNum;i++){
			cleanCharData(CharManager->charDataTbl + i);	
		}

		// �L�����N�^���E�擾
		CharManager->MainModeCharLimit = CharModeMinNum( modeMain );
		CharManager->SubModeCharLimit = CharModeMinNum( modeSub );
		// ���W�X�^�ɐݒ�
		GX_SetOBJVRamModeChar( modeMain );
		GXS_SetOBJVRamModeChar( modeSub );


		// �L�����N�^���E�T�C�Y����Vram���Ǘ�����̈���쐬
		main_size_cm = getCharModeNum( CharMakeData->VramTransAreaMain,
										CharManager->MainModeCharLimit );
		sub_size_cm = getCharModeNum( CharMakeData->VramTransAreaSub,
										CharManager->SubModeCharLimit );
		MakeTransArea(main_size_cm, sub_size_cm, CharMakeData->heap);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�[�W���[�����S�ɔj�����܂��B
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void DeleteCharManager(void)
{
	if(CharManager != NULL){
		DellTransArea(CharManager->TransAreaFlagMain);
		DellTransArea(CharManager->TransAreaFlagSub);
		
		DelCharAll();
		sys_FreeMemoryEz(CharManager->charDataTbl);
		sys_FreeMemoryEz(CharManager);
		CharManager = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	  ���[�h���J�n����֐�	(�����Ǘ��̃I�t�Z�b�g��������)
 *
 *@param	  start_offset�F�ǂݍ��݊J�noffset
 *
 *@return	  none
 *
 */
//-----------------------------------------------------------------------------
///���C����
void CharLoadStart( u32 start_offset )
{
	CharManager->Offset = start_offset;
	setObjVramSize();			// Vram�̃T�C�Y���Z�b�g
}

/// �T�u��
void CharLoadStartSub( u32 start_offset )
{
	CharManager->SubOffset = start_offset;
	setObjVramSize();			// Vram�̃T�C�Y���Z�b�g
}

/// �S��
void CharLoadStartAll( void )
{
	CharManager->Offset    = 0;
	CharManager->SubOffset = 0;
	TransAreaInit( CharManager->TransAreaFlagMain );
	TransAreaInit( CharManager->TransAreaFlagSub );
	setObjVramSize();			// Vram�̃T�C�Y���Z�b�g
}

//----------------------------------------------------------------------------
/**
 *	@brief	AreaCont�֐��p	�g�p�֎~�̈�ݒ�
 *
 *	@param	offset		�g�p�֎~�I�t�Z�b�g�ʒu
 *	@param	size		�g�p�֎~�T�C�Y
 *	@param	disp		���
 *
 *	disp
 *		main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN = 1
 *		sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB = 2
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void SetReserveAreaContCharManager( u32 offset, u32 size, u32 disp )
{
	int start_offset;
	int set_size;
	
	// �Ǘ��r�b�g�ݒ�
	if( disp == NNS_G2D_VRAM_TYPE_2DMAIN ){
		// offset���Ǘ��̈�ȉ��̂Ƃ�������̂ŁA�P�A���Ă���
		getReserveAreaContData( 
				CharManager->MainVramTransStart,
				offset, size,
				&start_offset, &set_size );
		
		if( set_size > 0 ){
			setvramTransBitData( NNS_G2D_VRAM_TYPE_2DMAIN, start_offset, 0, set_size, 0 );
		}
	}else{

		// offset���Ǘ��̈�ȉ��̂Ƃ�������̂ŁA�P�A���Ă���
		getReserveAreaContData( 
				CharManager->SubVramTransStart,
				offset, size,
				&start_offset, &set_size );
		
		if( set_size > 0 ){
			setvramTransBitData( NNS_G2D_VRAM_TYPE_2DSUB, 0, start_offset, 0, set_size );
		}
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief		�L�����N�^�f�[�^�P�̂��Z�b�g���ă��[�h
 *
 *@param		pChatData�F�L�����N�^ENTRY�f�[�^
 *
 *@retval		TRUE �F�Z�b�g�ł���  
 *@retval		FALSE�F�Z�b�g�ł��Ȃ�����
 *
 */
//-----------------------------------------------------------------------------
BOOL CharSet( const CHAR_MANAGER_HEADER* pCharData )
{
	CHAR_DATA_TBL* tbl;
	u32* p_offset;
	u8 dell_flag = 0;		// �j���t���O
	u32	vram_limit;			// Vram�̍ő�T�C�Y	

	if(CheckCharID(pCharData->id) == TRUE){
		GF_ASSERT(0&&("ID���d�����Ă��܂�"));
	}

	//
	// �L�����N�^�f�[�^���e�[�u���ɃZ�b�g
	//
	tbl = getCharData();
	if( tbl == NULL ){
		GF_ASSERT(0&&("�f�[�^�o�^�e�[�u��MAX�ł��B�����o�^�ł��܂���B"));
		return FALSE;		// �o�^�s�\
	}


	// �L�����N�^�f�[�^�ǂݍ���
	if(LoadCharData(pCharData, tbl) == FALSE){
		return FALSE;
	}

	// Vram�ɓ]������
	if( TransCharData(tbl) == FALSE ){
		DelChar( tbl->act_num );
		return FALSE;
	}

	// �o�^���A�b�h
	CharManager->charDataNow++;

	return TRUE;
}




//----------------------------------------------------------------------------
/**
 *
 *@brief		�L�����N�^�f�[�^�𕡐��Z�b�g
 *
 *@param		pChatData�F�L�����N�^�f�[�^
 *@param		num			�z��v�f��
 *
 *@return		�����o�^����������
 *
 */
//-----------------------------------------------------------------------------
u16 CharSets( const CHAR_MANAGER_HEADER* pCharData, int num )
{
	int i;	// ���[�v�p

	// CHAR_END������܂œǂݍ���
	for(i=0;i<num;i++){
		// �ǂݍ��݁��Z�b�g����
		if( CharSet( pCharData + i ) == FALSE ){
			// ���s
			break;
		}
	}

	return i;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief		�L�����N�^�f�[�^�P�̂��Z�b�g���ă��[�h
 *				�}�b�s���O���[�h�����̏�ԂɕύX���郂�[�h
 *
 *@param		pChatData�F�L�����N�^ENTRY�f�[�^
 *
 *@retval		TRUE �F�Z�b�g�ł���  
 *@retval		FALSE�F�Z�b�g�ł��Ȃ�����
 *
 */
//-----------------------------------------------------------------------------
BOOL CharSetCharModeAdjust( const CHAR_MANAGER_HEADER* pCharData )
{
	CHAR_DATA_TBL* tbl;
	u32* p_offset;
	u8 dell_flag = 0;		// �j���t���O
	u32	vram_limit;			// Vram�̍ő�T�C�Y	

	if(CheckCharID(pCharData->id) == TRUE){
		GF_ASSERT(0&&("ID���d�����Ă��܂�"));
	}

	//
	// �L�����N�^�f�[�^���e�[�u���ɃZ�b�g
	//
	tbl = getCharData();
	if( tbl == NULL ){
		GF_ASSERT(0&&("�f�[�^�o�^�e�[�u��MAX�ł��B�����o�^�ł��܂���B"));
		return FALSE;		// �o�^�s�\
	}


	// �L�����N�^�f�[�^�ǂݍ���
	if(LoadCharData(pCharData, tbl) == FALSE){
		return FALSE;
	}

	// �L�����N�^�f�[�^�̃��[�h�����̏�ԂɕύX����
	tbl->mapModeAdjust = TRUE;
	

	// Vram�ɓ]������
	if( TransCharData(tbl) == FALSE ){
		DelChar( tbl->act_num );
		return FALSE;
	}

	// �o�^���A�b�h
	CharManager->charDataNow++;

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief		�L�����N�^�f�[�^�𕡐��Z�b�g
 *				�}�b�s���O���[�h�����̏�ԂɕύX���郂�[�h
 *
 *@param		pChatData	�L�����N�^�f�[�^�z��
 *@param		num			�z��v�f��
 *
 *@return		�����o�^����������
 */
//-----------------------------------------------------------------------------
u16 CharSetsCharModeAdjust( const CHAR_MANAGER_HEADER* pCharData, int num )
{
	int i;	// ���[�v�p

	// CHAR_END������܂œǂݍ���
	for(i=0;i<num;i++){
		// �ǂݍ��݁��Z�b�g����
		if( CharSetCharModeAdjust( pCharData + i ) == FALSE ){
			// ���s
			break;
		}
	}

	return i;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	id�̃L�����N�^�f�[�^�������o�^����Ă��邩�`�F�b�N
 *
 *@param	id		�`�F�b�N����id
 *
 *@retval	TRUE	�o�^����Ă���
 *@retval	FALSE	�o�^����Ă��Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CheckCharID(int id)
{
	int i;

	for(i=0;i<CharManager->charDataNum;i++){
		if(CharManager->charDataTbl[i].act_num == id){
			return TRUE;
		}
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Ǘ�ID��Vram�ɃL�����N�^�f�[�^��]������
 *
 *	@param	id				�]����̃f�[�^id
 *	@param	pCharData		�]������L�����N�^�f�[�^
 *
 *	@return	none
 *
 * �L�����N�^�f�[�^�̃T�C�Y���ꏏ�ł���K�v������܂�
 *
 */
//-----------------------------------------------------------------------------
void CharDataChg( int id, NNSG2dCharacterData* pCharData )
{
	CHAR_DATA_TBL* tbl;	// �L�����N�^�e�[�u��

	GF_ASSERT( pCharData );
	
	tbl = getCharDataPtr(id);
	GF_ASSERT(tbl);
	tbl->pCharData	= pCharData;

	if( (tbl->type & NNS_G2D_VRAM_TYPE_2DMAIN) ){
		// Vram
		// �]���}�l�[�W���œ]��
		AddVramTransferManager(
			NNS_GFD_DST_2D_OBJ_CHAR_MAIN,
			tbl->offset,
			pCharData->pRawData,
			pCharData->szByte
			);
	}
	if( tbl->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		// Vram
		// �]���}�l�[�W���œ]��
		AddVramTransferManager(
			NNS_GFD_DST_2D_OBJ_CHAR_SUB,
			tbl->sub_offset,
			pCharData->pRawData,
			pCharData->szByte
			);
	}

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
int CheckCharRest(void)
{
	return CharManager->charDataNum - CharManager->charDataNow;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�f�[�^��j��
 *
 *@param	id		�L�����N�^id
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DelChar( int id )
{
	CHAR_DATA_TBL* tbl;		// �L�����N�^�f�[�^
	int flag = 1;
	do{
		// �L�����N�^�f�[�^�̗v�f�����擾
		tbl = getCharDataPtr(id);
		GF_ASSERT(tbl);
	
		// �R�s�[�͔j��
		if(tbl->flag == CHAR_MAN_DO_VRAM_COPY){
			DelVramTransData( &tbl->ImageProxy );	
		}else{
			// �I���W�i���f�[�^�̎��j���ɍs��
			flag = 0;
		}
	}while( flag );
	
	// �L�����N�^�f�[�^��j������
	// �ғ������`�F�b�N
	if( (tbl->flag != CHAR_MAN_NONE) ){
		// �j��
		dellCharData( tbl );
		CharManager->charDataNow--;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�S�L�����N�^�f�[�^��j��
 *
 *@param	none
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DelCharAll( void )
{
	int i;

	//
	// �S�L�����N�^�f�[�^��j��
	//
	// �L�����N�^ID�̃e�[�u����T��
	for( i = 0; i < CharManager->charDataNum; i++ ){
		// �ғ������`�F�b�N
		if( CharManager->charDataTbl[ i ].flag != CHAR_MAN_NONE ){
			// �f�[�^�j��
			dellCharData( &CharManager->charDataTbl[ i ] );
			CharManager->charDataNow--;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ID�̃C���[�W�v���N�V���擾
 *
 *@param	id			�L�����N�^ID
 *
 *@return	ID�̃v���N�V
 *
 */
//-----------------------------------------------------------------------------
NNSG2dImageProxy* GetCharIDProxy( int id )
{
	CHAR_DATA_TBL* tbl;

	// �L�����N�^�f�[�^�̗v�f�����擾
	tbl = getCharDataPtr(id);
	GF_ASSERT(tbl);

	// �ғ����łȂ����NULL��Ԃ�
	if( tbl->flag == CHAR_MAN_NONE ){
		return NULL;
	}
	
	return &tbl->ImageProxy;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ID�̃L�����N�^�f�[�^���擾
 *
 *@param	pImage�F�C���[�W�v���N�V�|�C���^
 *
 *@return	�L�����N�^�f�[�^
 *
 */
//-----------------------------------------------------------------------------
NNSG2dCharacterData* GetCharIDData( const NNSG2dImageProxy* pImage )
{
	CHAR_DATA_TBL* data;
	
	data = getImageProxyTbl(pImage);

	return data->pCharData;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z��Vram�]���A�j���[�V�����p�̃L�����N�^�v���N�V���擾
 *
 *@param	id			�L�����N�^ID
 *@param	szByte		�g�p�T�C�Y
 *
 *@retval	�C���[�W�v���N�V
 *@retval	NULL			�I���W�i���͎g�p���Ȃ̂ŃR�s�[���쐬���Ă�������
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dImageProxy* GetCharVramTransData( int id, u32 szByte )
{
	u32	offset, offset_sub;		// �I�t�Z�b�g
	CHAR_DATA_TBL* now_tbl;	// ���o�^�ς݃e�[�u��
	CHAR_DATA_TBL* pTbl;	// �o�^����e�[�u��
	u32	size_m, size_s;		// ���ۂɊm�ۂ���Vram�T�C�Y

	// �L�����N�^�f�[�^�̗v�f�����擾
	now_tbl = getCharDataPtr(id);
	GF_ASSERT(now_tbl);
	
	// �ғ����łȂ����NULL��Ԃ�
	if( now_tbl->flag == CHAR_MAN_NONE ){
		return NULL;
	}
	
	//
	// Vram�̃T�C�Y�����悤�����ʂ�Vram�ɂ��邩�`�F�b�N
	//
	getvramTransOffset(now_tbl->type, &offset, &offset_sub, szByte, &size_m, &size_s);

	// �I���W�i���f�[�^���g�p���Ȃ�G���[��Ԃ�
	if( now_tbl->flag == CHAR_MAN_DO_VRAM_ORIG ){
		
		return NULL;
		
	}else{
		// �I���W�i�����g����Ȃ�I���W�i�����g�p
		// �t���O�����s�ɂ���
		now_tbl->flag = CHAR_MAN_DO_VRAM_ORIG;
		pTbl = now_tbl;
	}

	// �v���N�V���Z�b�g
	setvramTransOffsetProxy(pTbl, offset, offset_sub);

	// Vram�G���A�ێ�
	pTbl->have_area = TRUE;
	pTbl->have_szByte		= size_m;
	pTbl->have_szByteSub	= size_s;

	// �]��
	transVramCharVramMode(pTbl);

	//
	// Vram�̈�t���O���g�p���ɂ���
	//
	setvramTransBitData(pTbl->type, offset, offset_sub, size_m, size_s);

	return &pTbl->ImageProxy;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z��Vram�]���A�j���[�V�����p�̃L�����N�^�v���N�V���R�s�[���Ď擾
 *
 *@param	Orig	�I���W�i���C���[�W�v���N�V
 *
 *@return	�R�s�[����Vram�]���I�t�Z�b�g���擾�����C���[�W�v���N�V
 *@return	NULL	�I���W�i�����g�p���łȂ��\��������܂��B
 */
//-----------------------------------------------------------------------------
NNSG2dImageProxy* GetCharVramTransProxyCopy( const NNSG2dImageProxy* Orig )
{
	CHAR_DATA_TBL* data;
	CHAR_DATA_TBL* copy;
	u32 main, sub;		// �I�t�Z�b�g
	u32	size_m, size_s;	// ���ۂɊm�ۂ���Vram�T�C�Y
	u32 data_size;
	

	// �C���[�W�v���N�V�̃e�[�u���擾
	data = getImageProxyTbl(Orig);
	GF_ASSERT(data);
	
	// �R�s�[��擾
	copy = getCharData();
	GF_ASSERT(copy);

	// �t���O���`�F�b�N
	if(data->flag != CHAR_MAN_DO_VRAM_ORIG){
		return NULL;
	}

	// �R�s�[
	*copy = *data;

	// �t���O���R�s�[�ɂ���
	copy->flag = CHAR_MAN_DO_VRAM_COPY;

	if( copy->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		data_size = copy->have_szByte;
	}else{
		data_size = copy->have_szByteSub;
	}
	
	// �I�t�Z�b�g�擾
	getvramTransOffset(copy->type, &main, &sub, data_size, &size_m, &size_s);

	// �v���N�V�ɐݒ�
	setvramTransOffsetProxy(copy, main, sub);

	// Vram�G���A�ێ�
	copy->have_area = TRUE;
	copy->have_szByte = size_m;
	copy->have_szByteSub = size_s;
	
	transVramCharVramMode( (void*)copy );

	// Vram�̈�t���O���g�p���ɂ���
	setvramTransBitData(copy->type, main, sub, size_m, size_s );

	return &copy->ImageProxy;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z��Vram�]���A�j����Vram�̈���J��
 *
 *@param	pImage�F�j������L�����N�^�̈��
 *			�C���[�W�v���N�V
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DelVramTransData( const NNSG2dImageProxy* pImage )
{
	int i;			// ���[�v�p
	
	//
	// �v���N�V�̃|�C���^�Ɠ����v���N�V��T��
	// 
	for( i = 0; i < CharManager->charDataNum; i++ )
	{
		// �ғ������`�F�b�N
		if( (CharManager->charDataTbl[ i ].flag == CHAR_MAN_DO_VRAM_ORIG) || 
			(CharManager->charDataTbl[ i ].flag == CHAR_MAN_DO_VRAM_COPY) ){
			// ID���`�F�b�N
			if( &CharManager->charDataTbl[ i ].ImageProxy == pImage ){
				break;
			}	
		}
	}

	if( i >= CharManager->charDataNum ){
		return ;
	}

	// Vram�G���A�̉��
	delCharTblTransArea( CharManager->charDataTbl + i );

	//
	// �t���O���`�F��
	// �I���W�i�����`�F�b�N
	if( CharManager->charDataTbl[ i ].flag == CHAR_MAN_DO_VRAM_ORIG ){
		// �҂���Ԃɂ���
		CharManager->charDataTbl[ i ].flag = CHAR_MAN_WAIT_VRAM_ORIG;
	}else{
		// Copy�̎��̓f�[�^�Ȃ���Ԃɂ���
		CharManager->charDataTbl[ i ].flag = CHAR_MAN_NONE;
		cleanCharData( &CharManager->charDataTbl[ i ] );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	NNSG2dCharacterData���g�p���Ȃ��Ƃ���Vram�G���A�m�ۗp
 *
 *	@param	szByte		�L�����N�^�f�[�^�T�C�Y
 *	@param	cont_type	Vram�R���g���[���^�C�v
 *	@param	type		�o�^���
 *	@param	allocData	�m�ۃf�[�^�i�[��
 *
 *	@retval	TRUE	�̈�m�ۂł���
 *	@retval	FALSE	�̈�m�ۂł��Ȃ�����
 *
 *	cont_type
 *		CHARM_CONT_OFFSET	�I�t�Z�b�g�^�C�v
 *		CHARM_CONT_AREACONT	�G���A�R���g���[���^�C�v
 *
 *	type
 *		NNS_G2D_VRAM_TYPE_2DMAIN	���C�����VRAM
 *		NNS_G2D_VRAM_TYPE_2DSUB		�T�u���VRAM
 *
 */
//-----------------------------------------------------------------------------
BOOL CharVramAreaAlloc( int szByte, int cont_type, int type, CHAR_MANAGER_ALLOCDATA* allocData )
{
	u32 offs_m, offs_s;
	u32 size_m, size_s;
	BOOL check;
	
	if( cont_type == CHARM_CONT_OFFSET ){
		
		// �]���ł��邩�`�F�b�N
		check = modeNormOffsetGet( szByte, type, &offs_m, &offs_s );

		if(check){

			// �I�t�Z�b�g�����炷
			modeNormOffsetMove( szByte, type );

			// �m�ۃf�[�^�쐬
			allocData->type = type;
			allocData->alloc_size	= szByte;
			if( type == NNS_G2D_VRAM_TYPE_2DMAIN ){
				allocData->alloc_ofs	= offs_m;
			}else{
				allocData->alloc_ofs	= offs_s;
			}
		}

	}else{
		
		// �]���ł��邩�`�F�b�N
		check = getvramTransOffset(type, &offs_m, &offs_s, szByte, &size_m, &size_s);
		if(check){

			// Vram�̈�t���O���g�p���ɂ���
			setvramTransBitData(type, offs_m, offs_s, size_m, size_s);

			// �m�ۃf�[�^�쐬
			allocData->type = type;
			if( type == NNS_G2D_VRAM_TYPE_2DMAIN ){
				allocData->alloc_size	= size_m;
				allocData->alloc_ofs	= offs_m;
			}else{
				allocData->alloc_size	= size_s;
				allocData->alloc_ofs	= offs_s;
			}
		}
	}

	return check;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	NNSG2dCharacterData���g�p���Ȃ��Ƃ���Vram�G���A�j���p
 *			cont_type = CHARM_CONT_AREACONT�̂Ƃ��悤
 *
 *	@param	allocData	�o�^�f�[�^
 * 
 *	@return	none
 *
 * �I�t�Z�b�g���炵���[�h�Ŋm�ۂ������͉̂���ł��܂���
 *
 */
//-----------------------------------------------------------------------------
void CharVramAreaFree( CHAR_MANAGER_ALLOCDATA* allocData )
{
	int cm_s;		// �L�����N�^���E�P�ʂ̃T�C�Y
	int cm_ofs;		// �L�����N�^���E�P�ʂ̃I�t�Z�b�g
	
	
	// �Z��Vram�A�j���̗̈���J��
	if( allocData->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		cm_s = getCharModeNum( allocData->alloc_size ,CharManager->MainModeCharLimit);
		cm_ofs = getCharModeNum( allocData->alloc_ofs - CharManager->MainVramTransStart, CharManager->MainModeCharLimit );
		TransBitClean( cm_ofs,
				cm_s,
				CharManager->TransAreaFlagMain );

	}
	
	if( allocData->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		cm_s = getCharModeNum( allocData->alloc_size ,CharManager->SubModeCharLimit);
		cm_ofs = getCharModeNum( allocData->alloc_ofs - CharManager->SubVramTransStart, CharManager->SubModeCharLimit );

		TransBitClean( cm_ofs,
				cm_s,
				CharManager->TransAreaFlagSub );
	}

}


//----------------------------------------------------------------------------
/**
 *	@brief	�L�����N�^�}�l�[�W���|�C���^�̎擾
 *
 *	@param	none
 *
 *	@return	�L�����N�^�}�l�[�W���|�C���^
 */
//-----------------------------------------------------------------------------
void* CharManagerPtrGet( void )
{
	void* buff;
	
	// �j���ς݂̃L�����N�^�}�l�[�W���ł�
	GF_ASSERT( CharManager );

	buff = CharManager;
	CharManager = NULL;
	return buff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�L�����N�^�}�l�[�W���|�C���^��ݒ�
 *
 *	@param	pdata	�L�����N�^�}�l�[�W���|�C���^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void CharManagerPtrSet( void* pdata )
{
	// �܂��j������Ă��Ȃ��̂ɏ㏑�����悤�Ƃ��Ă��܂�
	GF_ASSERT( CharManager == NULL );

	CharManager = pdata;
}


//
// �v���C�x�[�g�֐�
//
//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�f�[�^��������
 *
 *@param	data	�f�[�^
 *
 *@return	void
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanCharData(CHAR_DATA_TBL* data)
{
	data->pCharData		= NULL;
	data->type			= 0;
	data->vramType		= 0;
	data->act_num		= CHAR_DATA_ID_NONE;
	data->offset		= 0;
	data->sub_offset	= 0;
	data->flag			= 0;
	data->mapModeAdjust = 0;
	NNS_G2dInitImageProxy( &data->ImageProxy );
	
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�f�[�^��ǂݍ���
 *
 *@param	pEntData		ENTRY�f�[�^
 *@param	pCharData		�L�����N�^�f�[�^�ǂݍ��݃e�[�u��
 *
 *@return	BOOL	�����FTRUE	���s�FFALSE	(�p�X�������Ă��Ȃ��@���̓�����������Ȃ�)
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL LoadCharData(const CHAR_MANAGER_HEADER* pEntData, CHAR_DATA_TBL* pCharData)
{
	// �f�[�^�ݒ�
	pCharData->pCharData = pEntData->res_file;
	
	// ID��ݒ�
	pCharData->act_num = pEntData->id;
	
	// �e�[�u���Z�b�g
	pCharData->type		= pEntData->type;	// VramType���Z�b�g
	pCharData->vramType	= pCharData->pCharData->characterFmt >> CHAR_VRAM_TRANS_SHIFT;

	// �R���g���[���^�C�v�ݒ�
	pCharData->cont_type = pEntData->cont_type;

	// Vram�Ǘ��f�[�^
	pCharData->have_area = FALSE;
	pCharData->have_szByte		= 0;
	pCharData->have_szByteSub	= 0;

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�C���[�W�v���N�V�Ɠ����e�[�u����T��
 *
 *@param	pImage		�T���e�[�u���̃C���[�W�v���N�V
 *
 *@return	CHAR_DATA_TBL*	���������e�[�u��
 *
 *
 */
//-----------------------------------------------------------------------------
static CHAR_DATA_TBL* getImageProxyTbl(const NNSG2dImageProxy* pImage)
{
	int i;			// ���[�v�p

	//
	// �v���N�V�̃|�C���^�Ɠ����v���N�V��T�����̃L�����N�^�f�[�^��Ԃ�
	// 
	for( i = 0; i < CharManager->charDataNum; i++ ){
		// �ғ������`�F�b�N
		if( CharManager->charDataTbl[ i ].flag != CHAR_MAN_NONE ){
			// ID���`�F�b�N
			if( &CharManager->charDataTbl[ i ].ImageProxy == pImage ){
				break;
			}	
		}
	}

	if( i >= CharManager->charDataNum ){
		return NULL;
	}

	return (CharManager->charDataTbl + i);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�f�[�^�]��
 *
 *@param	pCharData	�G���g���[�f�[�^
 *@param	tbl			�L�����N�^�f�[�^
 *
 *@return	BOOL	�����FTRUE	���s�FFALSE	�iVram�T�C�Y������Ȃ��j
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL TransCharData(CHAR_DATA_TBL* tbl)
{
	BOOL dell_flag = TRUE;	// Vram�ɓ���Ȃ��Ƃ�FALSE�ɂȂ�
	
	// Vram�]�����`�F�b�N
	if( tbl->vramType ){
		tbl->flag = CHAR_MAN_WAIT_VRAM_ORIG;// Vram�]���ҋ@��
	}else{
		tbl->flag = CHAR_MAN_DO_NORMAL;		// �ʏ�g�p��

		if(tbl->cont_type == CHARM_CONT_OFFSET){
			// �I�t�Z�b�g���炵���[�h
			dell_flag = TransCharOffset( tbl );
		}else{
			// �G���A�R���g���[�����[�h
			dell_flag = TransCharAreaCont( tbl );
		}
	}

	return dell_flag;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Ǘ��^�C�v�I�t�Z�b�g�œ]��
 *
 *	@param	tbl		�e�[�u��
 *
 *	@retval	TRUE	�]������
 *	@retval	FALSE	�]�����s
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL TransCharOffset(CHAR_DATA_TBL* tbl)
{
	BOOL dell_flag = TRUE;	// Vram�ɓ���Ȃ��Ƃ�FALSE�ɂȂ�
	u32 offs_m, offs_s;		// ���C���T�u�I�t�Z�b�g

	// �I�t�Z�b�g�擾
	dell_flag = modeNormOffsetGet( tbl->pCharData->szByte, tbl->type, &offs_m, &offs_s );
	
	if( dell_flag ){
		
		// �]��
		setTransChar( tbl, offs_m, offs_s );
		
		// �I�t�Z�b�g�ړ�
		modeNormOffsetMove( tbl->pCharData->szByte, tbl->type );
	}

	return dell_flag;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Ǘ��^�C�v�G���A�R���g���[���œ]��
 *
 *	@param	tbl		�L�����N�^�e�[�u��
 *
 *	@retval	TRUE	�]������
 *	@retval	FALSE	�]�����s
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL TransCharAreaCont(CHAR_DATA_TBL* tbl)
{
	u32	offset, offset_sub;		// �I�t�Z�b�g
	u32 size_m, size_s;			// ���ۂɊm�ۂ���Vram�T�C�Y
	BOOL check;

	//
	// Vram�̃T�C�Y�����悤�����ʂ�Vram�ɂ��邩�`�F�b�N
	//
	check = getvramTransOffset(tbl->type, &offset, &offset_sub, tbl->pCharData->szByte, &size_m, &size_s);
	// �̈�m�ێ��s
	if( check == FALSE ){
		return FALSE;
	}

	// �I�t�Z�b�g���Z�b�g
	setvramTransOffsetProxy(tbl, offset, offset_sub);

	// Vram�G���A�ێ�
	tbl->have_area = TRUE;
	tbl->have_szByte = size_m;
	tbl->have_szByteSub = size_s;

	// �]��
	transVramChar(tbl);

	// Vram�̈�t���O���g�p���ɂ���
	setvramTransBitData(tbl->type, offset, offset_sub, size_m, size_s);

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�f�[�^��j������
 *
 *@param	pCharData�F�L�����N�^�f�[�^
 *
 *@return	 none
 *
 */
//-----------------------------------------------------------------------------
static void dellCharData( CHAR_DATA_TBL* pCharData )
{
	// Vram�G���A��ێ����Ă���Ƃ��͕Ԃ�
	if(pCharData->have_area){		
		delCharTblTransArea( pCharData );	
	}
	
	// �f�[�^�j��
	cleanCharData(pCharData);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���̃p�X�̃L�����N�^�f�[�^�̗v�f�����擾
 *
 *@param	id		�L�����N�^�f�[�^id
 *
 *@return	CHAR_DATA_TBL* �L�����N�^�f�[�^�e�[�u��
 *
 */
//-----------------------------------------------------------------------------
static CHAR_DATA_TBL* getCharDataPtr( int id )
{
	int	i;		// ���[�v�p
	
	// ID�̃f�[�^���������ăv���N�V��Ԃ�
	for( i = 0; i < CharManager->charDataNum; i++ ){
		// ID���`�F�b�N
		if( CharManager->charDataTbl[i].act_num == id ){
			return &CharManager->charDataTbl[i];
		}	
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^���[�h�����킹��
 *
 *	@param	pCharData	�L�����N�^�f�[�^
 *	@param	type		Vram�^�C�v
 *
 *	@return	int		�}�b�s���O���[�h
 *
 *
 */
//-----------------------------------------------------------------------------
static int charModeAdjust( CHAR_DATA_TBL* pCharData, int type )
{
	if(type == NNS_G2D_VRAM_TYPE_2DMAIN){
		pCharData->pCharData->mapingType = GX_GetOBJVRamModeChar();
	}else{
		pCharData->pCharData->mapingType = GXS_GetOBJVRamModeChar();
	}

	return pCharData->pCharData->mapingType;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�f�[�^�]��������V�u�����N�����^�X�N�ɃZ�b�g
 *
 *@param	pCharData�F�L�����N�^�f�[�^
 *@param	p_offset�F�I�t�Z�b�g�l
 *@param	p_sub_offset�F�T�u��ʂ̃I�t�Z�b�g�l
	*
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void setTransChar( CHAR_DATA_TBL* pCharData, u32 p_offset, u32 p_sub_offset )
{
	//
	// offset�l���Z�b�g���ăT�C�Y�����炷
	//
	pCharData->offset		= p_offset;
	pCharData->sub_offset	= p_sub_offset;

	// ���炷
	// Vram�]�����`�F�b�N
	if( !pCharData->vramType )
	{
		// Vram�]��
		transVramChar((void*)pCharData);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vram�ɓ]������]���I�t�Z�b�g���擾
 *
 *@param	type		�\����
 *@param	main		���C���I�t�Z�b�g�i�[��
 *@param	sub			�T�u�I�t�Z�b�g�i�[��
 *@param	szByte		�T�C�Y
 *@param	get_size	���C�����ۂɊm�ۂ����T�C�Y
 *@param	get_size_sub�T�u���ۂɊm�ۂ����T�C�Y
 *
 *@retval	TRUE	�̈�m�ې���
 *@retval	FALSE	�̈�m�ێ��s
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL getvramTransOffset(int type, u32* main, u32* sub, u32 szByte, u32* get_size, u32* get_size_sub)
{
	u32 size_cm;
	
	
	if( type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		// �T�C�Y���L�����N�^���E�T�C�Y�Ŋ���؂��l�ɂ���
		*get_size = getCharModeLimNum( szByte, CharManager->MainModeCharLimit, CHAR_MAN_LIM_ADD );
		
		
		// �L�����N�^���E�T�C�Y�̒P�ʂɂ���
		size_cm = getCharModeNum( *get_size, CharManager->MainModeCharLimit );	

		// ���C����ʑ�
		*main = TransBitCheck( size_cm, CharManager->TransAreaFlagMain );
		
		// �G���[���A���Ă������������
		if( *main == CHAR_VRAM_BANK_GET_ERR ){
			GF_ASSERT(0&&("Vram�]���Z���̗̈�擾�I�[�o�["));
			return FALSE;
		}

		// �I�t�Z�b�g�l���L�����N�^���E�T�C�Y����o�C�g�T�C�Y�ɕύX
		*main = getCharModeNum_byte( *main, CharManager->MainModeCharLimit );
	}

	if( type & NNS_G2D_VRAM_TYPE_2DSUB ){
		// �T�C�Y���L�����N�^���E�T�C�Y�Ŋ���؂��l�ɂ���
		*get_size_sub = getCharModeLimNum( szByte, CharManager->SubModeCharLimit, CHAR_MAN_LIM_ADD );
		
		// �L�����N�^���E�T�C�Y�̒P�ʂɂ���
		size_cm = getCharModeNum( *get_size_sub, CharManager->SubModeCharLimit );	
		
		// �T�u��ʑ�
		*sub = TransBitCheck( size_cm, CharManager->TransAreaFlagSub );

		// �G���[���A���Ă������������
		if( *sub == CHAR_VRAM_BANK_GET_ERR ){
			GF_ASSERT(0&&("Vram�]���Z���̗̈�擾�I�[�o�["));
			return FALSE;
		}

		// �I�t�Z�b�g�l���L�����N�^���E�T�C�Y����o�C�g�T�C�Y�ɕύX
		*sub = getCharModeNum_byte( *sub, CharManager->SubModeCharLimit );
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�v���N�V��Vram�]���p�I�t�Z�b�g��ݒ�
 *
 *@param	data	�L�����N�^�f�[�^�e�[�u��
 *@param	main	���C���I�t�Z�b�g
 *@param	sub		�T�u�I�t�Z�b�g
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setvramTransOffsetProxy(CHAR_DATA_TBL* data, u32 main, u32 sub)
{
	if( data->type & NNS_G2D_VRAM_TYPE_2DMAIN ){		// ���C����ʕ\���̎�
		data->offset = main + CharManager->MainVramTransStart;
	}
	if( data->type & NNS_G2D_VRAM_TYPE_2DSUB ){			// �T�u��ʕ\���̎�
		data->sub_offset = sub + CharManager->SubVramTransStart;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�v���N�V��Vram�]���p�I�t�Z�b�g��ݒ�
 *
 *@param	type	��ʃ^�C�v
 *@param	main	���C���I�t�Z�b�g
 *@param	sub		�T�u�I�t�Z�b�g
 *@param	szByte		���C���T�C�Y
 *@param	szByteSub	�T�u�T�C�Y
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setvramTransBitData(int type, u32 main, u32 sub, u32 szByte, u32 szByteSub)
{
	int size_cm;
	int offs_cm;
	
	
	if( type & NNS_G2D_VRAM_TYPE_2DMAIN ){		// ���C����ʕ\���̎�
		size_cm = getCharModeNum( szByte, CharManager->MainModeCharLimit );	
		offs_cm = getCharModeNum( main, CharManager->MainModeCharLimit );	
		TransBitSet( offs_cm, size_cm, CharManager->TransAreaFlagMain );

	}
	if( type & NNS_G2D_VRAM_TYPE_2DSUB ){			// �T�u��ʕ\���̎�
		size_cm = getCharModeNum( szByteSub, CharManager->SubModeCharLimit );	
		offs_cm = getCharModeNum( sub, CharManager->SubModeCharLimit );	
		TransBitSet( offs_cm, size_cm, CharManager->TransAreaFlagSub );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vblank���ōs���L�����N�^�f�[�^��Vram�ւ̓]��
 *
 *@param	p_data�F�]������L�����N�^�f�[�^
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void transVramChar( void* p_data )
{
	CHAR_DATA_TBL* p_char_data = (CHAR_DATA_TBL*)p_data;		// �L���X�g���ăf�[�^�擾
	int mapping_mode;		// �}�b�s���O���[�h

	// �v���N�V�̏�����
	NNS_G2dInitImageProxy(&p_char_data->ImageProxy);
	
	//
	// Vram�֓ǂݍ���
	//
	if( p_char_data->type != NNS_G2D_VRAM_TYPE_MAX )
	{
		
		transVramCharCore( p_char_data, p_char_data->type);
	}
	else
	{
		// �����ɓo�^
		transVramCharCore( p_char_data, NNS_G2D_VRAM_TYPE_2DMAIN);
		
		transVramCharCore( p_char_data, NNS_G2D_VRAM_TYPE_2DSUB);
		
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�]���R�A�֐�
 *
 *	@param	data			�L�����N�^�f�[�^
 *	@param	vram_type		Vram�^�C�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void transVramCharCore( CHAR_DATA_TBL* data, int vram_type)
{
	int mapping_mode;
	int offset;
	u32 before_mapping;
	
	if(data->mapModeAdjust){
		mapping_mode = charModeAdjust( data, vram_type );
	}else{
		mapping_mode = vram_type;
	}

	if(vram_type == NNS_G2D_VRAM_TYPE_2DMAIN){
		offset = data->offset;
		before_mapping = GX_GetOBJVRamModeChar();
	}else{
		offset = data->sub_offset;
		before_mapping = GXS_GetOBJVRamModeChar();
	}
	
	if(mapping_mode == GX_OBJVRAMMODE_CHAR_2D){
		NNS_G2dLoadImage2DMapping( 
				data->pCharData,		// �L�����N�^�f�[�^
				offset,					// �L�����N�^�x�[�X�A�h���X
				vram_type,					// VramType
				&data->ImageProxy );	// �C���[�W�v���N�V
	}else{
		NNS_G2dLoadImage1DMapping( 
				data->pCharData,		// �L�����N�^�f�[�^
				offset,					// �L�����N�^�x�[�X�A�h���X
				vram_type,					// VramType
				&data->ImageProxy );	// �C���[�W�v���N�V
		
	}

	if(vram_type == NNS_G2D_VRAM_TYPE_2DMAIN){
		if(GX_GetOBJVRamModeChar() != before_mapping){
			OS_Printf("�L�����]���ɂ��OBJ�}�b�s���O���[�h���ύX����܂���\n");
		}
	}
	else{
		if(GXS_GetOBJVRamModeChar() != before_mapping){
			OS_Printf("�L�����]���ɂ��OBJ�}�b�s���O���[�h���ύX����܂���\n");
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vblank���ōs���L�����N�^�f�[�^��Vram�ւ̓]��
 *						Vram�]���A�j�����[�h�̃L�����N�^
 *
 *@param	p_data�F�]������L�����N�^�f�[�^
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void transVramCharVramMode( void* p_data )
{
	CHAR_DATA_TBL* p_char_data = (CHAR_DATA_TBL*)p_data;		// �L���X�g���ăf�[�^�擾

	// �v���N�V�̏�����
	NNS_G2dInitImageProxy(&p_char_data->ImageProxy);
	
	//
	// Vram�֓ǂݍ���
	//
	if( p_char_data->type != NNS_G2D_VRAM_TYPE_MAX )
	{
		transVramCharVramModeCore( p_char_data, p_char_data->type );
	}
	else
	{
		// �����ɓo�^
		transVramCharVramModeCore( p_char_data, NNS_G2D_VRAM_TYPE_2DMAIN );
		transVramCharVramModeCore( p_char_data, NNS_G2D_VRAM_TYPE_2DSUB );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	VRAM�]��Core
 */
//-----------------------------------------------------------------------------
static void transVramCharVramModeCore( CHAR_DATA_TBL* data, int vram_type)
{
	int mapping_mode;
	int offset;
	u32 before_mapping;
	
	if(data->mapModeAdjust){
		mapping_mode = charModeAdjust( data, vram_type );
	}else{
		mapping_mode = vram_type;
	}

	if(vram_type == NNS_G2D_VRAM_TYPE_2DMAIN){
		offset = data->offset;
		before_mapping = GX_GetOBJVRamModeChar();
	}else{
		offset = data->sub_offset;
		before_mapping = GXS_GetOBJVRamModeChar();
	}
	
	NNS_G2dLoadImageVramTransfer( 
			data->pCharData,		// �L�����N�^�f�[�^
			offset,					// �L�����N�^�x�[�X�A�h���X
			vram_type,				// VramType
			&data->ImageProxy );	// �C���[�W�v���N�V

	if(vram_type == NNS_G2D_VRAM_TYPE_2DMAIN){
		if(GX_GetOBJVRamModeChar() != before_mapping){
			OS_Printf("�L�����]���ɂ��OBJ�}�b�s���O���[�h���ύX����܂���\n");
		}
	}
	else{
		if(GXS_GetOBJVRamModeChar() != before_mapping){
			OS_Printf("�L�����]���ɂ��OBJ�}�b�s���O���[�h���ύX����܂���\n");
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	��̃f�[�^�e�[�u�����擾
 *
 *@param	none
 *	
 *@return	CHAR_DATA_TBL* �^�F����̃e�[�u��	NULL�̎��͂�����̃e�[�u�����Ȃ�
 *
 */
//-----------------------------------------------------------------------------
static CHAR_DATA_TBL* getCharData( void )
{
	int i;		// ���[�v�p
	
	//
	// ��̃f�[�^�e�[�u�����擾
	//
	for( i = 0; i < CharManager->charDataNum; i++ ){
		// �����Ă���Ƃ�����T�[�`
		if( CharManager->charDataTbl[ i ].flag == CHAR_MAN_NONE ){
			return &CharManager->charDataTbl[ i ];
		}
	}

	return NULL;		// �o�^�s�\
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	  �I�u�W�F��Vram�T�C�Y���Z�b�g
 *
 *@param	 none
 *
 *@return	 none
 *
 */
//-----------------------------------------------------------------------------
static void setObjVramSize( void )
{
	GXVRamOBJ vram_bank;			// Vram�o���N�擾�p
	GXVRamSubOBJ sub_vram_bank;		// �T�u��ʂ�Vram�o���N�擾�p
	int vram_cont_area_size;
	
	//
	// Vram�o���N�̏�Ԃ��擾����
	// Vram�T�C�Y�Z�b�g
	//
	// ���C����
	vram_bank = GX_GetBankForOBJ();
	switch( vram_bank ){
	case GX_VRAM_OBJ_NONE:		// �Ȃ�
		CharManager->MainObjVramSize = 0;
		break;

	case GX_VRAM_OBJ_16_F:		// 16KByte
	case GX_VRAM_OBJ_16_G:
		CharManager->MainObjVramSize = 16 * 1024;
		break;

	case GX_VRAM_OBJ_32_FG:		// 32KByte
		CharManager->MainObjVramSize = 32 * 1024;
		break;

	case GX_VRAM_OBJ_64_E:		// 64KByte
		CharManager->MainObjVramSize = 64 * 1024;
		break;

	case GX_VRAM_OBJ_80_EF:		// 80KByte
	case GX_VRAM_OBJ_80_EG:
		CharManager->MainObjVramSize = 80 * 1024;
		break;

	case GX_VRAM_OBJ_96_EFG:	// 96KByte
		CharManager->MainObjVramSize = 96 * 1024;
		break;

	case GX_VRAM_OBJ_128_A:		// 128KByte
	case GX_VRAM_OBJ_128_B:
		CharManager->MainObjVramSize = 128 * 1024;	
		break;

	case GX_VRAM_OBJ_256_AB:	// 256KByte
		CharManager->MainObjVramSize = 256 * 1024;
		break;

	default:
		CharManager->MainObjVramSize = 0;
		break;
	}
	
	// �T�u��
	sub_vram_bank = GX_GetBankForSubOBJ();
	switch( sub_vram_bank ){
	case GX_VRAM_SUB_OBJ_NONE:		// �Ȃ�
		CharManager->SubObjVramSize = 0;
		break;

	case GX_VRAM_SUB_OBJ_16_I:		// 16KByte
		CharManager->SubObjVramSize = 16 * 1024;
		break;

	case GX_VRAM_SUB_OBJ_128_D:		// 128KByte
		CharManager->SubObjVramSize = 128 * 1024;	
		break;

	default:
		CharManager->SubObjVramSize = 0;
		break;
	}

	//
	// Vram�]���p�Ǘ��̈�X�^�[�g�ʒu 
	//
	vram_cont_area_size = getCharModeNum_byte( CharManager->TransAreaMainSize, CharManager->MainModeCharLimit );
	CharManager->MainVramTransStart = CharManager->MainObjVramSize - vram_cont_area_size;
	
	vram_cont_area_size = getCharModeNum_byte( CharManager->TransAreaSubSize, CharManager->SubModeCharLimit );
	CharManager->SubVramTransStart = CharManager->SubObjVramSize - vram_cont_area_size;

	//
	// Vram�]���p�Ǘ��̈�X�^�[�g�ʒu���O�����ɂȂ�����G���[���v�����g����
	//
	GF_ASSERT_MSG( ((CharManager->MainVramTransStart >= 0)&&(CharManager->SubVramTransStart >= 0)),
				"warning�FVram�]���p�Z����Vram�̈�Ǘ��̈�̃T�C�Y���AVram�o���N�̊��蓖�Ă����Ȃ��ł��B\n" );
	GF_ASSERT_MSG( ((CharManager->MainVramTransStart >= 0)&&(CharManager->SubVramTransStart >= 0)),
				"warning�FVram�]���p�Z����Vram�̈�̓��C��[byte] �T�u[byte]�ł��B\n" );
}

//
// Vram�̈�Ǘ��p
//
// ���̊Ǘ��̈��"InitCharManager()�֐�"�ɓn�����AVram�p�̈�T�C�Y���m�ۂ���܂��B
//�@�z�u�ʒu��"CharManager->MainVramTransStart""CharManager->SubVramTransStart"
//	����"CharManager->TransAreaMainSize","CharManager->TransAreaSubSize"���ł��B
//
//----------------------------------------------------------------------------
/**
 *
 *@brief	���C���A�T�u�̗��Ǘ��̈��������
 *
 *@param	none
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void TransAreaInitAll( void )
{
	TransAreaInit( CharManager->TransAreaFlagMain );
	TransAreaInit( CharManager->TransAreaFlagSub );
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	  Vram�]���Z���pVram�Ǘ��̈���쐬
 *
 *@param	main_size�F���C����ʑ��̃T�C�Y(�L�����N�^���E�T�C�Y)
 *@param	sub_size�F�T�u��ʑ��̃T�C�Y(�L�����N�^���E�T�C�Y)
 *@param	main_limit	���C����ʃL�����N�^���E
 *@param	sub_limit	�T�u��ʃL�����N�^���E
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void MakeTransArea( u32 main_size, u32 sub_size, int heap )
{
	//
	// �T�C�Y��ϐ��Ɋi�[���A�Ǘ��̈���Ď擾����
	//
	CharManager->TransAreaMainSize = main_size;
	CharManager->TransAreaSubSize = sub_size;

	// �̈���
	if(CharManager->TransAreaFlagMain != NULL){
		sys_FreeMemoryEz( CharManager->TransAreaFlagMain );
	}
	if(CharManager->TransAreaFlagSub != NULL){
		sys_FreeMemoryEz( CharManager->TransAreaFlagSub );
	}

	// �̈�m��
	if(CharManager->TransAreaMainSize != 0){
		CharManager->TransAreaFlagMain = sys_AllocMemory( heap, sizeof(u8) * (main_size / 8) );
	}
	if(CharManager->TransAreaSubSize != 0){
		CharManager->TransAreaFlagSub = sys_AllocMemory( heap, sizeof(u8) * (sub_size / 8) );
	}

	// �̈��������
	TransAreaInitAll();
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	  Vram�]���Z���pVram�Ǘ��̈��j��
 *
 *@param	p_trans_flag�F���C����ʂ��T�u��ʂ��̃t���O
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void DellTransArea( u8* p_trans_flag )
{	
	// NULL �`�F�b�N
	if(p_trans_flag != NULL){
		//
		// ���C����ʃT�u��ʂǂ������`�F�b�N
		//
		if( p_trans_flag == CharManager->TransAreaFlagMain ){
			CharManager->TransAreaMainSize = 0;

			// �j��
			sys_FreeMemoryEz( p_trans_flag );	
		}else{
			CharManager->TransAreaSubSize = 0;

			// �j��
			sys_FreeMemoryEz( p_trans_flag );
		}

		p_trans_flag = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���C���A�T�u�̗��Ǘ��̈�̃T�C�Y���擾
 *
 *@param	p_trans_flag�F���C�����T�u�̃t���O
 *
 *@return	�L�����N�^�T�C�Y
 *
 * 
 */
//-----------------------------------------------------------------------------
static u32 getTransAreaSize( u8* p_trans_flag )
{
	//
	// ���C���ʂ��T�u�ʂ��`�F�b�N
	//
	if( p_trans_flag == CharManager->TransAreaFlagMain ){
		return 	CharManager->TransAreaMainSize;
	}
	
	return CharManager->TransAreaSubSize;
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	�]����G���A�̃t���O�̏�����
 *
 *@param	p_trans_flag�F���C�����T�u�̃t���O
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void TransAreaInit( u8* p_trans_flag )
{
	int i;					// ���[�v�p
	u32	char_vram_max;		// �̈�ő吔�Z�b�g�p

	// NULL�`�F�b�N
	if( p_trans_flag != NULL ){
	
		// �T�C�Y�擾
		char_vram_max = getTransAreaSize( p_trans_flag );

		
		//
		// �̈�̏�����
		memset( p_trans_flag, 0, sizeof(u8) * (char_vram_max / 8) );
/*		for( i = 0; i < char_vram_max / 8; i++ )
		{
			p_trans_flag[ i ] = 0;
		}//*/
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�C�g���w�肵�Ďg�p�����Z�b�g
 *
 *@param	num		�J�n�o�C�g
 *@param	size	�g�p�T�C�Y		�P�ʁi�L�����N�^���E�T�C�Y�j
 *@param	p_trans_flag�F���C�����T�u�̃t���O
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void TransBitSet( u32 num, u32 size, u8* p_trans_flag )
{
	int i;			// ���[�v�p
	u32	char_vram_max;		// �̈�ő吔�Z�b�g�p


	
	// NULL �`�F�b�N
	if(p_trans_flag != NULL){
		
		// �T�C�Y�擾
		char_vram_max = getTransAreaSize( p_trans_flag );
		
		//
		// �]���t���O�ɂP���Z�b�g���Ă���
		//
		for( i = num; i < num + size; i++ )
		{
			u32 byte8;
			u8 byte1, mask;
			
			// �I�[�o�[�����甲����
			if( i >= char_vram_max )
			{
				break;
			}
				
			// �Z�b�g
			byte8_byte1_Get( i, &byte8, &byte1 );

			// �����炽������Ƃ��낪���łɂ�������Ă���
			GF_ASSERT( (p_trans_flag[ byte8 ] & (1 << byte1)) == 0 );

			mask = (1 << byte1);
			p_trans_flag[ byte8 ] |= mask;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�T�C�Y���̗̈悪�J���Ă��邩�`�F�b�N
 *
 *@param	size�F�T�C�Y	�P�ʁi�L�����N�^���E�T�C�Y�j
 *@param	p_trans_flag	���C�����T�u�̃t���O
 *
 *@return	�I�t�Z�b�g	�P�ʁi�L�����N�^���E�T�C�Y�j
 *				���߂ȂƂ���0xffffffff(CHAR_VRAM_BANK_GET_ERR)
 *
 */
//-----------------------------------------------------------------------------
static u32 TransBitCheck( u32 size, u8* p_trans_flag )
{
	int i, j;			// ���[�v�p
	u32	char_vram_max;		// �̈�ő吔�Z�b�g�p
	
	// NULL �`�F�b�N
	if(p_trans_flag != NULL){

		// �T�C�Y�擾
		char_vram_max = getTransAreaSize( p_trans_flag );
		
		// �]���T�C�Y�������Ă��邩�`�F�b�N
		for( i = 0; i < char_vram_max; i++ )
		{
			u32 byte8;
			u8 byte1, mask;
			// �����Ă��邩�`�F�b�N
			byte8_byte1_Get( i, &byte8, &byte1 );
			mask = (1 << byte1);

			// �`�F�b�N
			j = 0;
			while( ((p_trans_flag[ byte8 ] & mask) == 0) && (j <= size) ){
				int num = i + j;
				byte8_byte1_Get( num, &byte8, &byte1 );
				mask = (1 << byte1);

				// num��char_vram_max�ȏ�Ȃ甲����
				if( num >= char_vram_max ){
					return CHAR_VRAM_BANK_GET_ERR;
				}
				
				j++;
			}

			// size�ɂȂ����甲����
			if( j > size ){
				return i;
			}

			i += j;
		}
	}
	return CHAR_VRAM_BANK_GET_ERR;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�w�肳�ꂽ�]����G���A�̃t���O�̏�����
 *
 *@param	start_num		�������J�n�o�C�g��	�P�ʁi�L�����N�^���E�T�C�Y�j
 *@param	size			�������T�C�Y		�P�ʁi�L�����N�^���E�T�C�Y�j
 *@param	limit			�L�����N�^���E
 *@param	p_trans_flag	���C�����T�u�̃t���O
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void TransBitClean( u32 start_num, u32 size, u8* p_trans_flag )
{
	int i;			// ���[�v�p


	// NULL �`�F�b�N
	if(p_trans_flag != NULL){
		// �̈�̏�����
		for( i = start_num; i < start_num + size; i++ )
		{
			u32 byte8;
			u8 byte1, mask;
			
			// ������
			byte8_byte1_Get( i, &byte8, &byte1 );

			// ����������Ƃ��낪���łɏ�����Ă���
			GF_ASSERT( (p_trans_flag[ byte8 ] & (1 << byte1)) );

			mask = (1 << byte1) ^ 0xff;
			p_trans_flag[ byte8 ] &= mask;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�e�[�u���̓]���G���A���J��
 *
 *	@param	pCharData	�L�����N�^�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void delCharTblTransArea( CHAR_DATA_TBL* pCharData )
{
	u32	offs_cm;
	u32 size_cm;
	
	//
	// �Z��Vram�A�j���̗̈���J��
	//
	if( pCharData->type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		offs_cm = getCharModeNum( NNS_G2dGetImageLocation(&pCharData->ImageProxy,NNS_G2D_VRAM_TYPE_2DMAIN ) - CharManager->MainVramTransStart, CharManager->MainModeCharLimit );
		size_cm = getCharModeNum( pCharData->have_szByte, CharManager->MainModeCharLimit  );
		TransBitClean( offs_cm,
				size_cm,
				CharManager->TransAreaFlagMain );

	}
	
	if( pCharData->type & NNS_G2D_VRAM_TYPE_2DSUB ){
		offs_cm = getCharModeNum( NNS_G2dGetImageLocation(&pCharData->ImageProxy,NNS_G2D_VRAM_TYPE_2DSUB ) - CharManager->SubVramTransStart, CharManager->SubModeCharLimit );
		size_cm = getCharModeNum( pCharData->have_szByteSub, CharManager->SubModeCharLimit );
		TransBitClean( offs_cm,
				size_cm,
				CharManager->TransAreaFlagSub );
	}
	pCharData->have_area = FALSE;	// Vram�G���A��������̂�
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^���[�h���牽�L�������]������ׂ����擾
 *
 *	@param	mode		�L�����N�^���[�h
 *
 *	@return	int			�]������ׂ��L�����N�^��
 *
 *
 */
//-----------------------------------------------------------------------------
int CharModeMinNum( int mode )
{
	int char_num;
	
	switch(mode){
	case GX_OBJVRAMMODE_CHAR_1D_32K:
		char_num = 1;
		break;
	case GX_OBJVRAMMODE_CHAR_1D_64K:
		char_num = 2;
		break;
	case GX_OBJVRAMMODE_CHAR_1D_128K:
		char_num = 4;
		break;
	case GX_OBJVRAMMODE_CHAR_1D_256K:
		char_num = 8;
		break;
	default:
		char_num = 1;
		break;
	}

	return char_num;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���~�b�g�̒l�ɂ��킹��
 *
 *	@param	num		���~�b�g�ɂ��킹��l
 *	@param	limit	���~�b�g
 *	@param	flag	�؂��肩���߂邩�̃t���O
 *
 *	@return	int		���~�b�g�ɂ��킹���l
 *
 *flag
 *	CHAR_MAN_LIM_SUB,		// ���܂��؂���
 *	CHAR_MAN_LIM_ADD		// ���܂�𖄂߂�
 *
 */
//-----------------------------------------------------------------------------
static int getCharModeLimNum( int num, int limit, int flag )
{
	if( num % limit ){
		num -= (num % limit);
		if( flag == CHAR_MAN_LIM_ADD ){
			num += limit;
		}
	}

	return num;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^���E�ł̃T�C�Y���擾
 *
 *	@param	szByte	�o�C�g�T�C�Y
 *	@param	limit	�L�����N�^���E
 *
 *	@return	int		�L�����N�^���E�ł̃T�C�Y
 *
 *
 */
//-----------------------------------------------------------------------------
static int getCharModeNum( int szByte, int limit )
{
	szByte /= CHAR_ONE_SIZE;
	szByte /= limit;
	
	return szByte; 
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^���E�T�C�Y����o�C�g�T�C�Y�ɕύX
 *
 *	@param	szChar	�L�����N�^���E�T�C�Y�̒l
 *	@param	limit	�L�����N�^���E��
 *
 *	@return	int		�o�C�g�T�C�Y
 *
 *
 */
//-----------------------------------------------------------------------------
static int getCharModeNum_byte( int szChar, int limit )
{
	szChar *= limit;
	szChar *= CHAR_ONE_SIZE;
	return szChar; 
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�m�[�}���R���g���[���^�C�v���̍��]�����ׂ��I�t�Z�b�g�l���擾
 *
 *	@param	szByte		�]���f�[�^�T�C�Y
 *	@param	type		�]����
 *	@param	offs_main	���C���]����i�[��
 *	@param	offs_sub	�T�u�]����i�[��
 *
 *	@retval	TRUE	�]������̈悪������
 *	@retval	FALSE	�̈�Ȃ�	offs_main offs_sub�̒l����
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL modeNormOffsetGet( u32 szByte, int type, u32* offs_main, u32* offs_sub )
{
	BOOL ret = TRUE;
	
	// ���C����ʂ��T�u��ʂ��`�F�b�N
	if( type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		// Vram���~�b�g�`�F�b�N
		if( (CharManager->Offset + szByte) > CharManager->MainVramTransStart ){
			GF_ASSERT(0);
			ret = FALSE;
		}else{

			*offs_main = CharManager->Offset;
		}
	}
	if( type & NNS_G2D_VRAM_TYPE_2DSUB ){
		// Vram���~�b�g�`�F�b�N
		if( (CharManager->SubOffset + szByte) > CharManager->SubVramTransStart ){
			GF_ASSERT(0);
			ret = FALSE;
		}else{

			*offs_sub = CharManager->SubOffset;
		}
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�O���[�o���̃I�t�Z�b�g���T�C�Y�����炷
 *
 *	@param	szByte		�o�C�g�T�C�Y
 *	@param	type		�\������
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void modeNormOffsetMove( u32 szByte, int type )
{
	// ���C����ʂ��T�u��ʂ��`�F�b�N
	if( type & NNS_G2D_VRAM_TYPE_2DMAIN ){
		CharManager->Offset += szByte;

		// �I�t�Z�b�g���L�����N�^���E�Ŋ���؂��l�ɂ���
		CharManager->Offset = getCharModeLimNum( CharManager->Offset, CharManager->MainModeCharLimit, CHAR_MAN_LIM_ADD );
	}
	if( type & NNS_G2D_VRAM_TYPE_2DSUB ){
		CharManager->SubOffset += szByte;

		CharManager->SubOffset = getCharModeLimNum( CharManager->SubOffset, CharManager->SubModeCharLimit, CHAR_MAN_LIM_ADD );
	}

}

//----------------------------------------------------------------------------
/**
 *	@brief	�o�C�g8�o�C�g1�̒l���擾
 *
 *	@param	num		�l
 *	@param	byte8	8�r�b�g�P�ʂ̒l
 *	@param	byte1	8�r�b�g�P�ʓ���1�r�b�g�P�ʂ̒l
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void byte8_byte1_Get( int num, u32* byte8, u8* byte1 )
{
	*byte8 = num >> 3;
	*byte1 = num & 7;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Ǘ��̈�̋֎~�ݒ��ް��쐬
 *
 *	@param	areacont_start	�Ǘ��̈�J�n�I�t�Z�b�g
 *	@param	offset			�֎~�ݒ�I�t�Z�b�g
 *	@param	size			�T�C�Y
 *	@param	start_offset	�J�n�I�t�Z�b�g�i�[��
 *	@param	set_size		�T�C�Y�i�[��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void getReserveAreaContData( u32 areacont_start, u32 offset, u32 size, int* start_offset, int* set_size )
{
	*start_offset = offset - areacont_start;
	if( *start_offset < 0 ){
		// �I�t�Z�b�g��0�ɂ��đ���Ȃ����̃T�C�Y��size���������
		// ���傤�Ǘǂ��Ȃ�
		*set_size = size + *start_offset;
		*start_offset = 0;
	}else{
		*set_size = size;
	}
	
}
