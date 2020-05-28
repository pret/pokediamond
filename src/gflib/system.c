//==============================================================================
/**
 * @file	system.c
 * @brief	�V�X�e�����x���̊֐������߂�����
 * @author	GAME FREAK Inc.
 */
//==============================================================================

#define __SYSTEM_H_GLOBAL__
#include "standard.h" 
#include "system.h"
#include "system\wordset.h"
#include "gflib_os_print.h"
#include "assert.h"
#include "rebooter.h"

//==============================================================================
//
//			��`�A�֐��錾
//
//==============================================================================
//#define	FS_DMA_NUMBER	DEFAULT_DMA_NUMBER
#define		FS_DMA_NUMBER		(1)



static void HBlankIntrSetMain( BOOL func_flag );

#ifdef PM_DEBUG 
extern u32 sys_GetMemoryBlockSize( const void* memBlock );
#endif

//==============================================================================
//
//			�ϐ���`
//
//==============================================================================
SystemArea sys;						// �V�X�e�����\�[�X

//==============================================================================
//
//			�֐�
//
//==============================================================================

/*---------------------------------------------------------------------------*
  Name:         sys_VBlankIntr

  Description:  V�u�����N�̃R�[���o�b�N�����[�`���B

  Arguments:    �Ȃ��B
  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/
void sys_VBlankIntr(void)
{
	OS_SetIrqCheckFlag(OS_IE_V_BLANK);

	MI_WaitDma(GX_DEFAULT_DMAID);
	TCBSYS_Main( sys.vintrTCBSys );

	sys.vsync_flame_counter++;
}

//==============================================================================
/**
 * V�u�����N���ɌĂяo�����֐��̓o�^
 *
 * @param   func	�Ăяo���֐��|�C���^
 * @param	work	�w��֐����Ăяo���Ƃ��̈������[�N�ւ̃|�C���^
 *
 * @retval  none		
 */
//==============================================================================
void sys_VBlankFuncChange(INTR_FUNC func, void * work)
{
	sys.pVBlank = func;
	sys.pVBlankWork = work;
}


//==============================================================================
//
//
//			H�u�����N�֘A
//
//
//==============================================================================
//----------------------------------------------------------------
//----------------------------------------------------------------
void sys_HBlankIntrStop( void )
{
	HBlankIntrSetMain( FALSE );
	sys.pHBlank = NULL;
	sys.pHBlankWork = NULL;
}

//----------------------------------------------------------------
/**
 * @brief	H�u�����N�ݒ�
 * @param   func	�Ăяo���֐��|�C���^
 * @param	work	���荞�ݒ��Ɏg�p���郏�[�N�ւ̃|�C���^
 * @retval  "TRUE = �ݒ肵�܂���"
 * @retval	"FALSE = ���łɐݒ肳��Ă��܂�"
 *
 * @li	func = NULL �̏ꍇ�AH�u�����N�N���A
 */
//----------------------------------------------------------------
BOOL  sys_HBlankIntrSet( INTR_FUNC func, void * work )
{
#if 1
	if( func == NULL ){
		HBlankIntrSetMain( FALSE );
		sys.pHBlank = NULL;
		sys.pHBlankWork = NULL;
		return TRUE;
	} else {
		if( sys.pHBlank == NULL ){
			sys.pHBlankWork = work;
			sys.pHBlank = func;
			HBlankIntrSetMain( TRUE );
			return TRUE;
		} else {
			return FALSE;
		}
	}
#else
	if( sys.pHBlank == NULL ){
		if( func ){
			sys.pHBlankWork = work;
			sys.pHBlank = func;
			HBlankIntrSetMain( TRUE );
			return TRUE;
		} else {
			HBlankIntrSetMain( FALSE );
			sys.pHBlank = NULL;
			sys.pHBlankWork = NULL;
			return TRUE;
		}
	}else if( func == NULL ){
		HBlankIntrSetMain( FALSE );
		sys.pHBlank = NULL;
		sys.pHBlankWork = NULL;
		return TRUE;
	}
	return FALSE;
#endif
}

//----------------------------------------------------------------
/**
 */
//----------------------------------------------------------------
static void sys_HBlankIntr(void)
{
	if (sys.pHBlank) {
		sys.pHBlank(sys.pHBlankWork);
	}
}

//----------------------------------------------------------------
//----------------------------------------------------------------
static void HBlankIntrSetMain( BOOL func_flag )
{
	OSIrqMask irqmask;

	OS_DisableIrq( ); 	//���荞�݋֎~
	if(func_flag==FALSE){
		irqmask = OS_GetIrqMask();
		OS_DisableIrqMask(OS_IE_H_BLANK);
		(void)GX_HBlankIntr(FALSE);
	}else{
		irqmask = OS_GetIrqMask();
		//OS_SetIrqFunction( OS_IE_H_BLANK, func );
		OS_SetIrqFunction( OS_IE_H_BLANK, sys_HBlankIntr );
		OS_EnableIrqMask(OS_IE_H_BLANK);
	    (void)GX_HBlankIntr(TRUE);          // Rise a H-Blank interrupt
	}
	OS_EnableIrq( ); 	//���荞�݋���
}


//----------------------------------------------------------------
/**
 *	��{�q�[�v�������\����
 */
//----------------------------------------------------------------
#define HEAPSIZE_SYSTEM		(0x00d000)
#define HEAPSIZE_DEBUG		(0x001000)
#define HEAPSIZE_SAVE		(0x021000)
#define HEAPSIZE_APP		(0x106800+0x7000)	//VCT�p��2000�m�� 7.27

// BASE_HEAPID �Ə��Ԃ���v�����邱�ƁI 
static const HEAP_INIT_HEADER HeapInitHeader[] = {
	{ HEAPSIZE_SYSTEM,		OS_ARENA_MAIN   },
	{ HEAPSIZE_SAVE,		OS_ARENA_MAIN   },
	{ HEAPSIZE_DEBUG,		OS_ARENA_MAIN   },
	{ HEAPSIZE_APP,			OS_ARENA_MAIN   },
};


//----------------------------------------------------------------
/**
 *	TCB�V�X�e���쐬�p�����[�^
 */
//----------------------------------------------------------------
enum {
	TCB_MAIN_MAX = 160,
	TCB_VINTR_MAX = 16,
	TCB_VWAIT_MAX = 32,
	TCB_PRINT_MAX =  4,
};


//------------------------------------------------------------------
/**
 * �N�����Ƀq�[�v�쐬�ʒu�����炵�ď���������
 */
//------------------------------------------------------------------
static void InitHeapSystem( void )
{
	enum {
		HEAP_START_OFFSET_MAX = 256,
	};

	u32  led[8];
	u8   md5[MATH_MD5_DIGEST_SIZE];

	u32  offset, i;

	OS_GetLowEntropyData( led );
	MATH_CalcMD5( md5, led, sizeof(led) );

	offset = 0;
	for(i=0; i<MATH_MD5_DIGEST_SIZE; i++)
	{
		offset += md5[i];
	}
	offset %= HEAP_START_OFFSET_MAX;
	while( offset % 4 )
	{
		offset++;
	}

	sys_InitHeapSystem(HeapInitHeader, NELEMS(HeapInitHeader), HEAPID_MAX, offset);
}




/*---------------------------------------------------------------------------*
  Name:         sys_InitSystem

  Description:  NITRO�̏��������s���܂��B

  Arguments:    �Ȃ��B
  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/
void sys_InitSystem(void)
{
	#ifdef PM_DEBUG
	#ifndef EXHEAP_DISABLE
	OS_EnableMainExArena();
	#endif
	#endif

    OS_Init();
    FX_Init();
	GX_SetPower(GX_POWER_ALL);
    GX_Init();
	OS_InitTick();

	// �q�[�v�Ǘ��V�X�e��������
	InitHeapSystem();

	// �e��TCB�V�X�e���̍쐬
	sys.mainTCBSys = TCBSYS_Create( TCB_MAIN_MAX,  OS_AllocFromMainArenaLo(TCBSYS_CalcSystemWorkSize(TCB_MAIN_MAX),4) );
	sys.vintrTCBSys = TCBSYS_Create( TCB_VINTR_MAX, OS_AllocFromMainArenaLo(TCBSYS_CalcSystemWorkSize(TCB_VINTR_MAX),4) );
	sys.vwaitTCBSys = TCBSYS_Create( TCB_VWAIT_MAX, OS_AllocFromMainArenaLo(TCBSYS_CalcSystemWorkSize(TCB_VWAIT_MAX),4) );
	sys.printTCBSys = TCBSYS_Create( TCB_PRINT_MAX, OS_AllocFromMainArenaLo(TCBSYS_CalcSystemWorkSize(TCB_PRINT_MAX),4) );


    GX_DispOff();
    GXS_DispOff();

	GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);
	OS_SetIrqFunction(OS_IE_V_BLANK, sys_VBlankIntr);

    (void)OS_EnableIrqMask(OS_IE_V_BLANK);
    (void)OS_EnableIrqMask(OS_IE_FIFO_RECV);
    (void)OS_EnableIrq();

    (void)GX_VBlankIntr(TRUE);         // to generate VBlank interrupt request

	FS_Init(FS_DMA_NUMBER);
	rebooter_init();
	/* always preload FS table for faster directory access. */
	{
		u32 file_table_size = FS_GetTableSize();
		void* p_table = OS_AllocFromMainArenaLo( file_table_size, 4 );

		OS_TPrintf("FileTable Size     = 0x%08x bytes.\n", file_table_size);
		OS_TPrintf("remains of MainRAM = 0x%08x bytes.\n", (u32)(OS_GetMainArenaHi())-(u32)(OS_GetMainArenaLo()));

		GF_ASSERT(p_table != NULL);
		FS_LoadTable(p_table, file_table_size);
	}

	sys.pVBlank		= NULL;		// �u�u�����N�����ݓ��Ăяo���֐��|�C���^
	sys.pHBlank		= NULL;		// �g�u�����N�����ݓ��Ăяo���֐��|�C���^
	sys.pVCount		= NULL;		// �u�J�E���g�����ݓ��Ăяo���֐��|�C���^
	sys.pSio		= NULL;		// �r�h�n�����ݓ��Ăяo���֐��|�C���^

	sys.vsync_counter = 0;	
	sys.disp3DSW = DISP_3D_TO_MAIN;	
}

/*---------------------------------------------------------------------------*
  Name:         sys_InitVRAM

  Description:  �u�q�`�l�̏��������s���܂��B

  Arguments:    �Ȃ��B
  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/
void sys_InitVRAM(void)
{
    // �S�Ẵo���N��LCDC�Ɋ��蓖�Ă�
    GX_SetBankForLCDC(GX_VRAM_LCDC_ALL);

    // LCDC��ԑS�Ă��N���A
    MI_CpuClearFast( (void*)HW_LCDC_VRAM, HW_LCDC_VRAM_SIZE );
    
    // LCDC�Ɋ��蓖�Ă�ꂽ�o���N��Disable
    (void)GX_DisableBankForLCDC();

    MI_CpuFillFast ((void*)HW_OAM    , 192, HW_OAM_SIZE   );  // OAM �N���A
    MI_CpuFillFast ((void*)HW_DB_OAM , 192, HW_DB_OAM_SIZE);  // clear OAM

    MI_CpuClearFast((void*)HW_PLTT   , HW_PLTT_SIZE   );      // �p���b�g �N���A
    MI_CpuClearFast((void*)HW_DB_PLTT, HW_DB_PLTT_SIZE);	  // clear the standard palette
}



//==============================================================================
//
//
//
//==============================================================================
/*---------------------------------------------------------------------------*
  Name:         sys_LoadFile

  Description:  �ʏ�t�@�C���̓ǂݍ���
  
  Arguments:    mode	�w��q�[�v�̈��`
				path	�t�@�C���ւ̃p�X
  Returns:      �t�@�C���ǂݍ��ݐ�A�h���X
 *---------------------------------------------------------------------------*/
void* sys_LoadFile(int mode, const char *path)
{
	FSFile file;
	void*  memory;

	FS_InitFile(&file);
	if (FS_OpenFile(&file, path)){

		u32	fileSize = FS_GetLength(&file);		
		memory = sys_AllocMemory( mode, fileSize );

		if (memory == NULL){
			OS_Printf("no enough memory.\n");
		}else{
			if(FS_ReadFile(&file, memory, fileSize) != fileSize){
				// �t�@�C���T�C�Y���ǂݍ��߂Ă��Ȃ��ꍇ
				sys_FreeMemory( mode, memory );
				memory = NULL;
				OS_Printf("file reading failed.\n");
			}
		}
		(void)FS_CloseFile(&file);
	}else{
		OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n",path);
		memory = NULL;
	}
	return memory;
}

/*---------------------------------------------------------------------------*
  Name:         sys_LoadFileEx

  Description:  �ʏ�t�@�C���̓ǂݍ��� + �T�C�Y�擾
  
  Arguments:    mode	�w��q�[�v�̈��`
				path	�t�@�C���ւ̃p�X
				siz		�f�[�^�T�C�Y�i�[��
  Returns:      �t�@�C���ǂݍ��ݐ�A�h���X
 *---------------------------------------------------------------------------*/
void * sys_LoadFileEx( int mode, const char * path, u32 * siz )
{
	FSFile file;
	void * memory;

	FS_InitFile( &file );
	if( FS_OpenFile( &file, path ) ){

		*siz = FS_GetLength( &file );		
		memory = sys_AllocMemory( mode, *siz );

		if( memory == NULL ){
			OS_Printf( "no enough memory.\n" );
		}else{
			if( FS_ReadFile( &file, memory, *siz ) != *siz ){
				// �t�@�C���T�C�Y���ǂݍ��߂Ă��Ȃ��ꍇ
				sys_FreeMemory( mode, memory );
				memory = NULL;
				OS_Printf( "file reading failed.\n" );
			}
		}
		(void)FS_CloseFile( &file );
	}else{
		OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n",path);
	}
	return memory;
}

/*---------------------------------------------------------------------------*
  Name:         sys_LoadGraphFile

  Description:  �O���t�B�b�N�p�t�@�C���̓ǂݍ��݁i�L���b�V������j
  
  Arguments:    path        �t�@�C���ւ̃p�X
				side		���C���A�T�u�w��
  Returns:      �t�@�C���ǂݍ��ݐ�A�h���X
 *---------------------------------------------------------------------------*/
void sys_LoadFileNoMem(const char *path, void **mem)
{
	FSFile file;
	
	FS_InitFile(&file);
	if (FS_OpenFile(&file, path)){
		u32	fileSize = FS_GetLength(&file);
#ifdef PM_DEBUG
		{
			u32 size = sys_GetMemoryBlockSize(*mem)-(0x10);
			if (fileSize>size){
				OS_Printf("fileSize=%x,allocSize=%x\n",fileSize,size);
				GF_ASSERT( 0 && "sys_LoadFileNoMem ERROR:���������s�����Ă܂�");
			}
		}
#endif
		
#ifdef DEBUG_PRINT
		PrintAllocHeapSize(GRAPHIC_HEAP,path);
		
//		AddAllocHeapSize(GRAPHIC_HEAP);
#endif //DEBUG_PRINT
		if (*mem == NULL){
			OS_Printf("no memory.\n");
   	    }else{	// �t�@�C���T�C�Y���ǂݍ��߂Ă��Ȃ��ꍇ
			if (FS_ReadFile(&file, *mem, fileSize) != fileSize){
				OS_Printf("file reading failed.\n");
			}
		}
        (void)FS_CloseFile(&file);
	}else{
		OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n",path);
	}
}

/*---------------------------------------------------------------------------*
  Name:         sys_LoadFileDiv

  Description:  �ʏ�t�@�C���̓ǂݍ��ݕ��� 
  
  Arguments:    mode	�w��q�[�v�̈��`
				path	�t�@�C���ւ̃p�X
				memory	�t�@�C���ǂݍ��ݐ�A�h���X�i�[�|�C���^
				offset	�ǂݍ��݃I�t�Z�b�g�i�[�|�C���^
				divsiz	�ǂݍ��ݕ����T�C�Y
Returns:		0:�p���A1=�I��
 *---------------------------------------------------------------------------*/
int sys_LoadFileDiv( int mode, const char * path, void** memory, u32* offset, u16 divsiz )
{
	FSFile file;
	char   filename[32];

	if(path[0]=='!'){
		strcpy(filename,&path[1]);
	}else{
		strcpy(filename,path);
	}

	FS_InitFile(&file);
	if (FS_OpenFile(&file, filename))
	{
		u32	fileSize = FS_GetLength(&file);	//�t�@�C���T�C�Y�擾		
		u32	readSize = 0;
		if(*memory == NULL){	//memory�����Ɏ擾����Ă�Όp���Ɣ��f
			//������	
			*memory = sys_AllocMemory( mode, fileSize );//�ǂݍ��݃G���A�m��
			if (*memory == NULL){
				// �������m�ێ��s
				OS_Printf("no enough memory.\n");
				return 1;
			} else {	
				*offset = 0;	//�I�t�Z�b�g������
			}
#ifdef SYSTEM_DEBUG_PRINT_FILE_SIZE	
			OS_Printf("DIV_LOAD_PATH:%s\nDivFileSizeTotal=%x\n",path,fileSize);
#endif
		}
		if( FS_SeekFile( &file, *offset, FS_SEEK_SET ) == FALSE ){
			// �t�@�C���I�t�Z�b�g�ύX���s
			sys_FreeMemory( mode, memory );
			memory = NULL;
			OS_Printf("file div failed.\n");
			return 1;
		}
		{
			void*	read_p;
			read_p = &((u8*)*memory)[*offset];
			readSize = FS_ReadFile(&file, read_p, divsiz);
			(void)FS_CloseFile(&file);
			*offset = *offset + readSize;	//�I�t�Z�b�g����
		}
		if( *offset >= fileSize ){
			//�ǂݍ��ݏI��
			return 1;
		}
	}else{
		if(*memory != NULL){	//memory�����Ɏ擾����Ă�ΊJ��
			sys_FreeMemory( mode, *memory );
			*memory = NULL;
		}
		OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n",filename);
		return 1;
	}
	return 0;
}

/*---------------------------------------------------------------------------*
  Name:         sys_LoadFileDiv

  Description:  �ʏ�t�@�C���̓ǂݍ��ݕ��� 
  
  Arguments:    mode	�w��q�[�v�̈��`
				path	�t�@�C���ւ̃p�X
				memory	�t�@�C���ǂݍ��ݐ�A�h���X�i�[�|�C���^
				offset	�ǂݍ��݃I�t�Z�b�g�i�[�|�C���^
				divsiz	�ǂݍ��ݕ����T�C�Y
Returns:		0:�p���A1=�I��
 *---------------------------------------------------------------------------*/
int sys_LoadFileDivNoMem( const char * path, void** memory, u32* offset, u16 divsiz )
{
	FSFile file;
	char   filename[32];
	
	strcpy(filename,path);
	
	FS_InitFile(&file);
	if (FS_OpenFile(&file, filename))
	{
		u32	fileSize = FS_GetLength(&file);	//�t�@�C���T�C�Y�擾		
		u32	readSize = 0;
		if(*memory == NULL){	//memory���m�ۂ���Ă��Ȃ��Ȃ�΃G���[
			OS_Printf("NoMemory file div failed.\n");
			return 1;
		}
#ifdef PM_DEBUG
		{
			if (*offset == 0){
				u32 size = sys_GetMemoryBlockSize(*memory)-(0x10);
				if (fileSize>size){
					OS_Printf("fileSize=%x,allocSize=%x\n",fileSize,size);
					GF_ASSERT( 0 && "sys_LoadFileDivNoMem ERROR:���������s�����Ă܂�");
				}
			}
		}
#endif
		
		if( FS_SeekFile( &file, *offset, FS_SEEK_SET ) == FALSE ){
			// �t�@�C���I�t�Z�b�g�ύX���s
			OS_Printf("file div failed.\n");
			return 1;
		}
		{
			void*	read_p;
			read_p = &((u8*)*memory)[*offset];
			readSize = FS_ReadFile(&file, read_p, divsiz);
			(void)FS_CloseFile(&file);
			*offset = *offset + readSize;	//�I�t�Z�b�g����
		}
		if( *offset >= fileSize ){
			//�ǂݍ��ݏI��
			return 1;
		}
	}else{	//�t�@�C�����J���Ȃ�
		OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n",filename);
		return 1;
	}
	return 0;
}

//==============================================================================
#define FILE_CACHE_MAX	(128)
typedef struct{
	void *memory;
	u32  hash;
}FILE_CACHE;

FILE_CACHE FileCache[FILE_CACHE_MAX];

u16 debugcount=0;

/**
 * �t�@�C��������t�@�C���L���b�V���p�̃n�b�V���l���擾����
 *
 * @param   path	�t�@�C����������
 *
 * @retval  u32		
 */
//==============================================================================
u32 CreateFileHash(const char *path)
{
	int i,r;
	u32 work,result;
	u16 len;
	len = strlen(path);
	
	if (len%4){					//��������S�Ŋ������ۂ̌J��Ԃ��񐔂��擾
		len = (len /4)+1;
	}else{
		len = len/4;	
	}

	result = 0;
	for(i=0;i<len;i++){			//4���������long�^�Ƃ݂Ȃ��ĕ�����̒����^�S��
		work = 0;				//XOR���s��
		for(r=0;r<4;r++){
			if(path[i*4+r]!=0){
				work |= (path[i*4+r]<<(r*8));
			}else{
				break;
			}
		}
		result ^= work;
	}

	return result;
}

//==============================================================================
/**
 * ���ɃL���b�V���Ƃ��đ��݂��Ă��邢�邩��������
 *
 * @param   hash	�t�@�C��������擾�����n�b�V���l
 *
 * @retval  int		0�`:���������z��̗v�f	-1:������Ȃ�����
 */
//==============================================================================
int SearchFileCache(u32 hash)
{
	int i;
	for(i=0;i<FILE_CACHE_MAX;i++){
		if(FileCache[i].hash==hash){
			if(FileCache[i].memory!=NULL){
				return i;
			}
		}
	}
	return -1;
}

//==============================================================================
/**
 * �V�����ǂݍ��񂾃t�@�C�����L���b�V�����Ƃ��ēo�^����
 *
 * @param   memory		�V�����m�ۂ����������̃A�h���X
 * @param   hash		�t�@�C��������擾�����n�b�V���l
 *
 * @retval  int			�o�^�����ԍ�
 */
//==============================================================================
int SetBlankCache(void* memory, u32 hash)
{
	int i;
	for(i=0;i<FILE_CACHE_MAX;i++){
		if(FileCache[i].memory==NULL){
			FileCache[i].memory = memory;
			FileCache[i].hash   = hash;
			return i;
		}
	}
	return -1;
}

//==============================================================================
/**
 * �L���b�V���̑S����E�n�b�V�����̃N���A
 *
 * @param   none		
 *
 * @retval  none		
 */
//==============================================================================
void ClearFileCache(void)
{
	int i;
	for(i=FILE_CACHE_MAX-1;i>-1;i--){
		if(FileCache[i].memory!=NULL){
			//NNS_FndFreeToExpHeap(sys.appHeap,FileCache[i].memory);
			sys_FreeMemoryEz( FileCache[i].memory );
#ifdef DEBUG_PRINT
			PrintFreeHeapSize(GRAPHIC_HEAP, "�L���b�V���f�[�^�̊J��");
			OS_Printf(	"cache:graph3DHeap = %ld\n",
						NNS_FndGetTotalFreeSizeForExpHeap(sys.graph3DHeap));
#endif //DEBUG_PRINT
			FileCache[i].memory = NULL;
			FileCache[i].hash   = 0;
		}
	}
}

//==============================================================================
/**
 * @brief	�n�b�V���z���NULL����������
 */
//==============================================================================
void InitFileCache(void)
{
	u8 i = 0;
//	memset(FileCache,0,sizeof(FileCache)*FILE_CACHE_MAX);
	for(i=0;i < FILE_CACHE_MAX;i++){
		FileCache[i].memory = NULL;
		FileCache[i].hash   = 0;
	}
}

//==============================================================================
/**
 * @brief	����̃n�b�V�����N���A����(�L�[�w��)
 *
 * @param   hash	�t�@�C��������擾�����n�b�V���l
 *
 * @retval  int		0�`:�폜�����v�fIndex	-1:�폜���Ȃ�����
 */
//==============================================================================
int ClearFileCacheKey(u32 hash)
{
	int i;

	i = SearchFileCache(hash);
	if(i == -1){	//�o�^�f�[�^��������Ȃ�����
		return i;
	}

	//���������̂ō폜����
	NNS_G3dResDefaultRelease(FileCache[i].memory);	//���\�[�X�������
	sys_FreeMemoryEz( FileCache[i].memory );
	FileCache[i].memory = NULL;
	FileCache[i].hash   = 0;
	return i;
}

//==============================================================================
/**
 * @brief	����̃n�b�V�����N���A����(�A�h���X�w��)
 *
 * @param   addr	���\�[�X�̃A�h���X
 *
 * @retval  int		0�`:�폜�����v�fIndex	-1:�폜���Ȃ�����
 */
//==============================================================================
int ClearFileCacheAddr(void* addr)
{
	int	i = 0;
	
	if(addr == NULL){
		return 0xFF;
	}
	//�L���b�V�����𑖍�����
	for(i = 0;i < FILE_CACHE_MAX;i++){	
		if(FileCache[i].memory != addr){
			continue;
		}
		//�L���b�V����j��
		NNS_G3dResDefaultRelease(FileCache[i].memory);	//���\�[�X�������
		sys_FreeMemoryEz(FileCache[i].memory);
		FileCache[i].memory = NULL;
		FileCache[i].hash   = 0;
		return i;
	}
	return -1;
}

/*---------------------------------------------------------------------------*
  Name:         sys_LoadGraphFile

  Description:  �O���t�B�b�N�p�t�@�C���̓ǂݍ��݁i�L���b�V������j
  
  Arguments:    path        �t�@�C���ւ̃p�X
				side		���C���A�T�u�w��
  Returns:      �t�@�C���ǂݍ��ݐ�A�h���X
 *---------------------------------------------------------------------------*/
void* sys_LoadGraphFile(const char *path,const u8 inMode)
{
	FSFile file;
	char   filename[32];
	void*  memory;
	u32    hash;
	int	   result,flag=0;

	if(path[0]=='!'){
		strcpy(filename,&path[1]);
		flag = 1;
	}else{
		strcpy(filename,path);
	}
	hash = CreateFileHash(filename);

//	OS_Printf("\"%s\" = %08x\n",path,hash);
	
	if((result=SearchFileCache(hash))>=0 && flag==0){
		memory = FileCache[result].memory;
//		OS_Printf("cache hit! no %d : \"%s\" = %08x\n",result,path,hash);
	}else{
		FS_InitFile(&file);
		if (FS_OpenFile(&file, filename))
		{
			u32	fileSize = FS_GetLength(&file);		

			//memory = NNS_FndAllocFromExpHeapEx(sys.graph3DHeap, fileSize, 16);
			memory = sys_AllocMemory( inMode, fileSize );
#ifdef DEBUG_PRINT
			PrintAllocHeapSize(GRAPHIC_HEAP,path);
//			AddAllocHeapSize(GRAPHIC_HEAP);
#endif //DEBUG_PRINT
			if (memory == NULL)
   		     {
				OS_Printf("no enough memory.\n");
   	    	 }
   	     	else
			{	// �t�@�C���T�C�Y���ǂݍ��߂Ă��Ȃ��ꍇ
				if (FS_ReadFile(&file, memory, fileSize) != fileSize)  
				{
					//NNS_FndFreeToExpHeap(sys.graph3DHeap, memory);
					sys_FreeMemoryEz( memory );
					memory = NULL;
					OS_Printf("file reading failed.\n");
				}
			}
            (void)FS_CloseFile(&file);
            if(flag==0){
	            if(SetBlankCache(memory,hash)<0){
	                OS_Printf("file cache  over.\n");
                }
            }//			OS_Printf("cache set \"%s\" = %08x\n",path,hash);
		}
		else{
			OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n",path);
			memory = NULL;
		}
	}
	return memory;
}
#if 0
/*---------------------------------------------------------------------------*
  @brief	�O���t�B�b�N�p�t�@�C�����\�[�X�̉��

  @param	addr	(void*)������郊�\�[�X�A�h���X
  @param	free	TRUE�Ȃ�΁A�L���b�V���o�^����Ă��郊�\�[�X�ł��������
					FALSE�̏ꍇ�A�L���b�V���o�^����Ă���Ή�����Ȃ�
  @retval	0		������
  @retval	1		�L���b�V��������
  @retval	2		�L���b�V���o�^����Ă���̂Ŕ���
  @retval	0xFF	�p�����[�^���s��
 *---------------------------------------------------------------------------*/
s8 sys_FreeGraphFile(void* addr,u8 free)
{
	u8	i = 0;
	
	if(addr == NULL){
		return 0xFF;
	}
	//�L���b�V�����𑖍�����
	for(i = 0;i < FILE_CACHE_MAX;i++){	
		if(FileCache[i].memory != addr){
			continue;
		}
		//HIT����
		if(free){
			//�L���b�V����j��
			NNS_G3dResDefaultRelease(FileCache[i].memory);	//���\�[�X�������
			sys_FreeMemory(GRAPHIC3D_HEAP_AREA,FileCache[i].memory);
			FileCache[i].memory = NULL;
			FileCache[i].hash   = 0;
			return 1;
		}else{
			return 2;	//�L���b�V���ɓo�^����Ă���̂Ŕ���
		}
	}
	//�L���b�V���ɓo�^����Ă��Ȃ������̂ŕ��ʂɉ��
	NNS_G3dResDefaultRelease(FileCache[i].memory);	//���\�[�X�������
	sys_FreeMemory(GRAPHIC3D_HEAP_AREA,FileCache[i].memory);
	FileCache[i].memory = NULL;
	FileCache[i].hash = 0;

	return 0;
}
#endif


/*---------------------------------------------------------------------------*
  Name:         sys_KeyRead

  Description:  �L�[��ǂݍ��݁A�g���K�ƃ����[�X�g���K�����߂܂��B
				
  Arguments:    �Ȃ��B
  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/

//������
void sys_InitKeyRead(void)
{
	TPCalibrateParam calibrate;

	sys.key_control_mode = 0;	//�L�[�擾���[�h

	sys.cont_org	= 0;	// �L�[���
	sys.trg_org		= 0;	// �L�[�g���K�[
	sys.repeat_org	= 0;	// �L�[���s�[�g
	sys.cont		= 0;	// �L�[���(�Q�[���ݒ�ɂ��ϊ�����������)
	sys.trg			= 0;	// �L�[�g���K�[(�Q�[���ݒ�ɂ��ϊ�����������)
	sys.repeat      = 0;	// �L�[���s�[�g(�Q�[���ݒ�ɂ��ϊ�����������)
	sys.repeatWait_Count = 0;
	sys.repeatSpeed	= 8;
	sys.repeatWait	= 15;


	sys.tp_x		 = 0;	// �^�b�`�p�l��X���W
	sys.tp_y		 = 0;	// �^�b�`�p�l��Y���W
	sys.tp_trg		 = 0;	// �^�b�`�p�l���ڐG����g���K
	sys.tp_cont		 = 0;	// �^�b�`�p�l���ڐG������
	sys.tp_auto_samp = 0;	// �^�b�`�p�l���̃I�[�g�T���v�����O���s���Ă��邩�̃t���O
									
	// �^�b�`�p�l���̏������ƃL�����u���[�V�������Z�b�g
	TP_Init();

	// �}�V���̃L�����u���[�V�����l���擾
	if( TP_GetUserInfo( &calibrate ) == TRUE ){
		// �L�����u���[�V�����l�̐ݒ�
		TP_SetCalibrateParam( &calibrate );
		OS_Printf("Get Calibration Parameter from NVRAM\n");
	}
	else{
		// �擾�Ɏ��s�����̂Ńf�t�H���g�̃L�����u���[�V�����̐ݒ�
		calibrate.x0 = 0x02ae;
		calibrate.y0 = 0x058c;
		calibrate.xDotSize = 0x0e25;
		calibrate.yDotSize = 0x1208;
		TP_SetCalibrateParam( &calibrate );
		OS_Printf( "Warrning : TauchPanelInit( not found valid calibration data )\n" );
	}
}

/*---------------------------------------------------------------------------*
  @brief	�`�f�a�J�[�g���b�W������
 *---------------------------------------------------------------------------*/
void sys_InitAgbCasetteVer(int version)
{
	sys.AgbCasetteVersion = version;
}

/*---------------------------------------------------------------------------*
  @brief	�X���[�v��Ԃ��֎~����
 *---------------------------------------------------------------------------*/
void sys_SleepNG(u8 sleepTypeBit)
{
	sys.DontSleep |= sleepTypeBit;
}

/*---------------------------------------------------------------------------*
  @brief	�X���[�v��Ԃ�������
 *---------------------------------------------------------------------------*/
void sys_SleepOK(u8 sleepTypeBit)
{
	sys.DontSleep &= ~(sleepTypeBit);
}

//------------------------------------------------------------------
static void KeyConvert(void);

//�ǂݎ��

void sys_MainKeyRead(void)
{
	TPData	tpTemp;
	TPData	tpDisp;
	int	keyData;

	// �ӂ����܂��Ă���ꍇ�͑S�Ă̓��͂��Ȃ��ɂ���
	if(PAD_DetectFold()){
	  sys.trg	= 0;
	  sys.cont	= 0;
	  sys.repeat	= 0;
	  sys.tp_trg	= 0;
	  sys.tp_cont	= 0;
	  return;
	}

	keyData = PAD_Read();
	
	sys.trg_org		= keyData & (keyData ^ sys.cont_org);	// �g���K ����

    sys.repeat_org	=	keyData & (keyData ^ sys.cont_org);        // ���s�[�g ����

    if((keyData!=0)&&(sys.cont_org==keyData)){
		if(--sys.repeatWait_Count==0){
			sys.repeat_org				=	keyData;
			sys.repeatWait_Count	=	sys.repeatSpeed;
		}
	}
	else{
		sys.repeatWait_Count = sys.repeatWait;
	}


	sys.cont_org	= keyData;							// �x�^ ����

	sys.trg		= sys.trg_org;
	sys.cont	= sys.cont_org;
	sys.repeat	= sys.repeat_org;

	KeyConvert();

	// �^�b�`�p�l���f�[�^���擾
	if(sys.tp_auto_samp == 0){
		while( TP_RequestRawSampling( &tpTemp ) != 0 ){};	//�T���v�����O�ɐ�������܂ő҂�
	}else{
		TP_GetLatestRawPointInAuto( &tpTemp );	// �I�[�g�T���v�����O���̃f�[�^���擾
	}

	TP_GetCalibratedPoint( &tpDisp, &tpTemp );	// ���W����ʍ��W�i�O�`�Q�T�T�j�ɂ���

#if 0	// 2006.07.05	���W�擾���s��������ύX
	switch(tpDisp.validity){		// ���W�̗L�������`�F�b�N
	case TP_VALIDITY_INVALID_X:
		sys.tp_x = 0xffff;
		sys.tp_y = tpDisp.y;
		break;
	case TP_VALIDITY_INVALID_Y:
		sys.tp_x = tpDisp.x;			// ���W���Z�b�g
		sys.tp_y = 0xffff;
		break;
	case TP_VALIDITY_INVALID_XY:
		sys.tp_x = 0xffff;
		sys.tp_y = 0xffff;
		break;
	default:
		sys.tp_x = tpDisp.x;
		sys.tp_y = tpDisp.y;
	}

	sys.tp_trg	= (u16)(tpDisp.touch & (tpDisp.touch ^ sys.tp_cont));	// �g���K ����
	sys.tp_cont	= tpDisp.touch;										// �x�^ ����
	
#endif	/// 
	
	if( tpDisp.validity == TP_VALIDITY_VALID  ){		// ���W�̗L�������`�F�b�N
		// �^�b�`�p�l�����W�L��
		sys.tp_x = tpDisp.x;
		sys.tp_y = tpDisp.y;
	}else{
		// �^�b�`�p�l�����W����
		// 1�V���N�O�̍��W���i�[����Ă���Ƃ��̂ݍ��W�����̂܂܎󂯌p��
		if( sys.tp_cont ){
			switch(tpDisp.validity){
			case TP_VALIDITY_INVALID_X:
				sys.tp_y = tpDisp.y;
				break;
			case TP_VALIDITY_INVALID_Y:
				sys.tp_x = tpDisp.x;
				break;
			case TP_VALIDITY_INVALID_XY:
				break;
			default:	// ����
				break;
			}
		}else{
			// �g���K�̃^�C�~���O�Ȃ�A
			// �^�b�`�p�l���������Ă��Ȃ����Ƃɂ���
			tpDisp.touch = 0;
		}
	}
	sys.tp_trg	= (u16)(tpDisp.touch & (tpDisp.touch ^ sys.tp_cont));	// �g���K ����
	sys.tp_cont	= tpDisp.touch;										// �x�^ ����

}

//--------------------------------------------------------------------------------------------
/**
 * �L�[���̕ϊ�
 *
 * @param	none
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define KEYCONV( key, check_pat, set_pat )	{ if( key & check_pat ) key |= set_pat; }
#define KEYCONV_RESET( key, check_pat, set_pat ) {	\
	if( key & check_pat ){							\
		key |= set_pat;								\
		key &= ( check_pat^0xffff );				\
	}												\
}
#define KEYCONV_EXCHANGE( key, pat1, pat2 ) {	\
	int	tmp = 0;								\
	if( key & pat1 ){							\
		tmp |= pat2;							\
	}											\
	if( key & pat2 ){							\
		tmp |= pat1;							\
	}											\
	key &= ( (pat1 | pat2 )^0xffff );			\
	key |= tmp;									\
}
#define KEY_RESET( key, reset_pat ) {			\
	key &= ( reset_pat^0xffff );				\
}

static void KeyConvert(void)
{
	switch( sys.key_control_mode ){

	default:
	case KEYCONTROL_NORMAL:
		break;

	case KEYCONTROL_PATTERN1:

		KEYCONV( sys.trg, PAD_BUTTON_START, PAD_BUTTON_X )
		KEYCONV( sys.cont, PAD_BUTTON_START, PAD_BUTTON_X )
		KEYCONV( sys.repeat, PAD_BUTTON_START, PAD_BUTTON_X )
		break;

	case KEYCONTROL_PATTERN2:

		KEYCONV_EXCHANGE( sys.trg, PAD_BUTTON_X,PAD_BUTTON_Y )
		KEYCONV_EXCHANGE( sys.cont, PAD_BUTTON_X,PAD_BUTTON_Y )
		KEYCONV_EXCHANGE( sys.repeat, PAD_BUTTON_X,PAD_BUTTON_Y )
		break;

	case KEYCONTROL_PATTERN3:

		KEYCONV( sys.trg, PAD_BUTTON_L, PAD_BUTTON_A )
		KEYCONV( sys.cont, PAD_BUTTON_L, PAD_BUTTON_A )
		KEYCONV( sys.repeat, PAD_BUTTON_L, PAD_BUTTON_A )

		KEY_RESET( sys.trg, ( PAD_BUTTON_L | PAD_BUTTON_R ) )
		KEY_RESET( sys.cont, ( PAD_BUTTON_L | PAD_BUTTON_R ) )
		KEY_RESET( sys.repeat, ( PAD_BUTTON_L | PAD_BUTTON_R ) )
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �L�[���s�[�g�̑��x�ƃE�F�C�g���Z�b�g
 *
 * @param	speed	���x
 * @param	wait	�E�F�C�g
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void sys_KeyRepeatSpeedSet( int speed, int wait )
{
	sys.repeatSpeed	= speed;
	sys.repeatWait	= wait;
}


/*---------------------------------------------------------------------------*
  @brief	�\�t�g�E�G�A���Z�b�g��Ԃ��֎~����
 *---------------------------------------------------------------------------*/
void sys_SoftResetNG(u8 softResetBit)
{
	sys.DontSoftReset |= softResetBit;
}

/*---------------------------------------------------------------------------*
  @brief	�\�t�g�E�G�A���Z�b�g��Ԃ�������
 *---------------------------------------------------------------------------*/
void sys_SoftResetOK(u8 softResetBit)
{
	sys.DontSoftReset &= ~(softResetBit);
}

