//==============================================================================
/**
 *
 *@file		heapsys.c
 *@brief	�q�[�v�̈�Ǘ�
 *@author	taya
 *@date		2005.08.25
 *
 */
//==============================================================================
#include "common.h"
#include "system.h"
#include "gflib\heapsys.h"

#ifdef PM_DEBUG
#include  "system\heapdefine.h"
//#define  ALLOCINFO_PRINT_HEAPID   HEAPID_BASE_APP	// ���̃q�[�v�h�c�Ɋւ��Ă̂ݏڍׂȏ����o��
#endif



//----------------------------------------------------------------
/**
 *	�萔
 */
//----------------------------------------------------------------
#define DEFAULT_ALIGN					(4)		// �������m�ێ��̃A���C�����g�l
#define MEMBLOCK_FILENAME_AREASIZE		(12)	// �f�o�b�O�p�w�b�_�Ɋi�[����t�@�C�����̈�T�C�Y
#define USER_HEAP_MAX					(24)	// ��x�ɍ쐬�\�ȃ��[�U�[�q�[�v�̐�


//----------------------------------------------------------------
/**
 *	�}�N��
 */
//----------------------------------------------------------------
#define ASSERT_IRQ_ENABLED()		GF_ASSERT(OS_GetProcMode() != OS_PROCMODE_IRQ)


//----------------------------------------------------------------
/**
 *	���[�N��`
 */
//----------------------------------------------------------------
typedef struct {
	NNSFndHeapHandle*	handle;
	NNSFndHeapHandle*	parentHandle;
	void**              heapMemBlock;
	u16*				count;
	u8*					handleIdxTbl;

	u16     heapMax;
	u16     baseHeapMax;
	u16     usableHeapMax;
	u16     invalidHandleIdx;


}HEAP_SYS;


//----------------------------------------------------------------
/**
 *	�������u���b�N�w�b�_��`
 */
//----------------------------------------------------------------
typedef struct {
	char	filename[ MEMBLOCK_FILENAME_AREASIZE ];	///< �Ăяo����\�[�X��
	u32		heapID  : 8;							///< u32
	u32		lineNum : 24;							///< �Ăяo���\�[�X�s�ԍ�
}MEMORY_BLOCK_HEADER;


//----------------------------------------------------------------
/**
 *	�O���[�o��
 */
//----------------------------------------------------------------
static HEAP_SYS  HeapSys = { 0 };


//----------------------------------------------------------------
/**
 *	�n���h���擾�}�N��
 */
//----------------------------------------------------------------
#define GetHeapHandle(idx)			(HeapSys.handle[ HeapSys.handleIdxTbl[ (idx) ] ])
#define GetParentHeapHandle(idx)	(HeapSys.parentHandle[ HeapSys.handleIdxTbl[ (idx) ] ])
#define GetHeapMemBlock(idx)		(HeapSys.heapMemBlock[ HeapSys.handleIdxTbl[ (idx) ] ])

#define SetHeapHandle(idx,h)		(HeapSys.handle[ HeapSys.handleIdxTbl[ (idx) ] ] = (h))
#define SetParentHeapHandle(idx,h)	(HeapSys.parentHandle[ HeapSys.handleIdxTbl[ (idx) ] ] = (h))
#define SetHeapMemBlock(idx,m)		(HeapSys.heapMemBlock[ HeapSys.handleIdxTbl[ (idx) ] ] = (m))


//==============================================================
// Prototype
//==============================================================
static int SearchEmptyHandleIndex( void );
static BOOL CreateHeapCore( u32 parentHeapID, u32 childHeapID, u32 size, s32 align );
static void* AllocMemoryCore( NNSFndHeapHandle heapHandle, u32 size, s32 alignment, u32 heapID );
static void PrintAllocInfo( const MEMORY_BLOCK_HEADER* header, NNSFndHeapHandle handle, u32 size );
static void PrintFreeInfo( const MEMORY_BLOCK_HEADER* header, NNSFndHeapHandle handle);
static void HeaderDebugParamSet( MEMORY_BLOCK_HEADER* header, const char* filename, u32 line_no );
static void PrintShortHeap( u32 heapID, u32 size, const char* filename, u32 line_num );
static void PrintExistMemoryBlocks( u32 heapID );
static void HeapConflictVisitorFunc(void* memBlock, NNSFndHeapHandle heapHandle, u32 param);
static void CopyFileName( char* dst, const MEMORY_BLOCK_HEADER* header );
static void PrintUnreleasedMemoryInfo( u32 heapID );





#ifdef PM_DEBUG
static void HeaderDebugParamSet( MEMORY_BLOCK_HEADER* header, const char* filename, u32 line_no );
static void PrintExistMemoryBlocks( u32 heapID );
static void HeapConflictVisitorFunc(void* memBlock, NNSFndHeapHandle heapHandle, u32 param);
static void CopyFileName( char* dst, const MEMORY_BLOCK_HEADER* header );
static void PrintUnreleasedMemoryInfo( u32 heapID );
#endif

//------------------------------------------------------------------------------
/**
 * Description:  �V�X�e���q�[�v�ƃA�v���P�[�V�����q�[�v���쐬���܂��B���q�[�v
 * 				�ɂ�NITRO-System�̊g���q�[�v���g�p���Ă��܂��B
 *
 * 				�V�X�e���q�[�v�p�̃������Ƃ��āASYSTEM_HEAP_SIZE�������C���A
 * 				���[�i����m�ۂ��A���C���A���[�i�̎c���S�ăA�v���P�[�V����
 * 				�q�[�v�p�̃������Ɋm�ۂ��Ă��܂��B
 *
 * 				�V�X�e���q�[�v�́A�Q�[���V�X�e�����̃V�X�e���v���O�����Ŏg�p
 * 				���邱�Ƃ�z�肵�Ă��܂��B�A�v���P�[�V�����q�[�v�ɂ́A�Q�[��
 * 				�Ŏg�p����f�[�^�����[�h����ׂɎg�p���܂��B
 *
 * @param   header			���������
 * @param   baseHeapMax		��{�q�[�v�G���A��
 * @param   totalHeapMax	�S�q�[�v�G���A��
 * @param   startOffset		�^����ꂽ�o�C�g�������S�̂̊J�n�ʒu�����炷
 *
 */
//------------------------------------------------------------------------------
void sys_InitHeapSystem(const HEAP_INIT_HEADER* header, u32 baseHeapMax, u32 totalHeapMax, u32 startOffset)
{
	void *mem;
	u32  usableHeapMax, i;

	usableHeapMax = baseHeapMax + USER_HEAP_MAX;
	if( totalHeapMax < usableHeapMax )
	{
		totalHeapMax = usableHeapMax;
	}

	// �q�[�v�A�h���X�����炷
	if( startOffset )
	{
		while( startOffset & 3 )
		{
			startOffset++;
		}
		OS_AllocFromMainArenaLo( startOffset, DEFAULT_ALIGN );
	}

	/*
	 * �q�[�v�n���h���̈�́A�쐬�\�q�[�v���{�P�@�쐬�B
	 * �Ō�̂P�͖����l�����Ă����āA���쐬�q�[�v�̃C���f�b�N�X�e�[�u���͂������w���悤�ɂ���B
	 */
	HeapSys.handle = OS_AllocFromMainArenaLo(
									sizeof(NNSFndHeapHandle) * (usableHeapMax + 1)
								+	sizeof(NNSFndHeapHandle) * (usableHeapMax)
								+	sizeof(void*) * (usableHeapMax)
								+   sizeof(u16) * (totalHeapMax)
								+	totalHeapMax, DEFAULT_ALIGN);

	HeapSys.parentHandle = HeapSys.handle + (usableHeapMax + 1);
	HeapSys.heapMemBlock = (void**)((u8*)(HeapSys.parentHandle) + (sizeof(NNSFndHeapHandle) * usableHeapMax));
	HeapSys.count = (u16*)((u8*)(HeapSys.heapMemBlock) + (sizeof(void*) * usableHeapMax));
	HeapSys.handleIdxTbl = (u8*)(HeapSys.count) + (sizeof(u16) * (totalHeapMax));

	HeapSys.heapMax = totalHeapMax;
	HeapSys.baseHeapMax = baseHeapMax;
	HeapSys.invalidHandleIdx = usableHeapMax;
	HeapSys.usableHeapMax = usableHeapMax;


	// ��{�q�[�v���C���f�b�N�X�쐬
	for(i = 0; i < baseHeapMax; i++)
	{
        OS_TPrintf("remains of MainRAM = 0x%08x bytes.\n", (u32)(OS_GetMainArenaHi())-(u32)(OS_GetMainArenaLo()));
		switch( header[i].arenaID ){
		case OS_ARENA_MAIN:
		default:
			mem = OS_AllocFromMainArenaLo( header[i].size, DEFAULT_ALIGN );
			break;
		case OS_ARENA_MAINEX:
			mem = OS_AllocFromMainExArenaHi( header[i].size, DEFAULT_ALIGN );
			break;
		}

		if( mem != NULL )
		{
			HeapSys.handle[i] = NNS_FndCreateExpHeap( mem, header[i].size );
			HeapSys.handleIdxTbl[i] = i;
		}
		else
		{
			GF_ASSERT_MSG(0, "%x���m�ۂł��Ȃ����� size=%x\n" ,header[i].size, mem);
		}
	}

	// ���[�U�[�q�[�v�̈�͖����l�ŃN���A���Ă���
	for(i = baseHeapMax; i < (usableHeapMax + 1); i++ )
	{
		HeapSys.handle[i] = NNS_FND_HEAP_INVALID_HANDLE;
		HeapSys.handleIdxTbl[i] = HeapSys.invalidHandleIdx;
	}
	while( i < totalHeapMax )
	{
		HeapSys.handleIdxTbl[i++] = HeapSys.invalidHandleIdx;
	}

	// Alloc�J�E���^�N���A
	for(i = 0; i < totalHeapMax; i++)
	{
		HeapSys.count[i] = 0;
	}


}


//------------------------------------------------------------------
/**
 * �n���h���̈�̋󂫂�����
 *
 * @retval  int		�󂫂�����΃C���f�b�N�X�i���o�[�^�Ȃ����-1
 */
//------------------------------------------------------------------
static int SearchEmptyHandleIndex( void )
{
	int i;

	// ��{�q�[�v�͉������Ȃ��n�Y�Ȃ̂Łc
	for( i = HeapSys.baseHeapMax; i < HeapSys.usableHeapMax; i++ )
	{
		if(HeapSys.handle[i] == NNS_FND_HEAP_INVALID_HANDLE)
		{
			return i;
		}
	}
	return -1;
}

//------------------------------------------------------------------
/**
 * �q�[�v�쐬
 *
 * @param   parentHeapID		�������̈�m�ۗp�q�[�v�h�c�i���ɗL���ł���K�v������j
 * @param   childHeapID			�V�K�ɍ쐬����q�[�v�h�c
 * @param   size				�q�[�v�T�C�Y
 *
 * @retval	BOOL				TRUE�ō쐬�����^FALSE�Ŏ��s
 */
//------------------------------------------------------------------
BOOL sys_CreateHeap( u32 parentHeapID, u32 childHeapID, u32 size )
{
	return CreateHeapCore( parentHeapID, childHeapID, size, DEFAULT_ALIGN );
}

//------------------------------------------------------------------
/**
 * �q�[�v�쐬�i�������������m�ہj
 *
 * @param   parentHeapID		�������̈�m�ۗp�q�[�v�h�c�i���ɗL���ł���K�v������j
 * @param   childHeapID			�V�K�ɍ쐬����q�[�v�h�c
 * @param   size				�q�[�v�T�C�Y
 *
 * @retval	BOOL				TRUE�ō쐬�����^FALSE�Ŏ��s
 */
//------------------------------------------------------------------
BOOL sys_CreateHeapLo( u32 parentHeapID, u32 childHeapID, u32 size )
{
	return CreateHeapCore( parentHeapID, childHeapID, size, -DEFAULT_ALIGN );
}

//------------------------------------------------------------------
/**
 * �q�[�v�쐬������
 *
 * @param   parentHeapID	�������̈�m�ۗp�q�[�v�h�c�i���ɗL���ł���K�v������j
 * @param   childHeapID		�V�K�ɍ쐬����q�[�v�h�c
 * @param   size			�q�[�v�T�C�Y
 * @param   align			�A���C�����g�i�}�C�i�X�Ȃ烁�����������m�ہj
 *
 * @retval  BOOL		TRUE�ō쐬�����^FALSE�Ŏ��s
 */
//------------------------------------------------------------------
static BOOL CreateHeapCore( u32 parentHeapID, u32 childHeapID, u32 size, s32 align )
{
	GF_ASSERT_MSG((OS_GetProcMode() != OS_PROCMODE_IRQ), "Create Heap:%d size:%d", childHeapID, size);

	if( HeapSys.handleIdxTbl[childHeapID] == HeapSys.invalidHandleIdx )
	{
		NNSFndHeapHandle  parentHeap = GetHeapHandle(parentHeapID);
		if( parentHeap != NNS_FND_HEAP_INVALID_HANDLE )
		{
			void* mem = NNS_FndAllocFromExpHeapEx( parentHeap, size, align );
			if( mem != NULL )
			{
				int i = SearchEmptyHandleIndex();
				if( i >= 0 )
				{
					HeapSys.handle[i] = NNS_FndCreateExpHeap( mem, size );
					if( HeapSys.handle[i] != NNS_FND_HEAP_INVALID_HANDLE )
					{
						HeapSys.parentHandle[i] = parentHeap;
						HeapSys.heapMemBlock[i] = mem;
						HeapSys.handleIdxTbl[childHeapID] = i;

						#ifdef ALLOCINFO_PRINT_HEAPID
						if( ALLOCINFO_PRINT_HEAPID == childHeapID )
						{
							u32 freeSize = NNS_FndGetTotalFreeSizeForExpHeap( HeapSys.handle[i] );
							OS_TPrintf("[HEAP] CRE_C total:0x%05x, usable:0x%05x  parent's id=%d, rest=0x%05x\n",
									size, freeSize, parentHeapID, NNS_FndGetTotalFreeSizeForExpHeap( parentHeap ) );
						}
						if( ALLOCINFO_PRINT_HEAPID == parentHeapID )
						{
							u32 freeSize = NNS_FndGetTotalFreeSizeForExpHeap( parentHeap );
							OS_TPrintf("[HEAP] CRE_P parent:%d rest:%05x, child:%d size:0x%05x\n",
									parentHeapID, freeSize, childHeapID, size );
						}
						#endif
						return TRUE;
					}
					else
					{
						GF_ASSERT_MSG(0, "�q�[�v�쐬�Ɏ��s");
					}

				}
				else
				{
					GF_ASSERT_MSG(0, "�q�[�v�Ǘ��e�[�u���ɋ󂫂�����");
				}
			}
			else
			{
				GF_ASSERT_Printf("Heap(%d) Create FAILED (size:%x bytes)\n", childHeapID, size);
				GF_ASSERT_Printf("ParentHeap(%d) %x bytes\n", parentHeapID, NNS_FndGetTotalFreeSizeForExpHeap( parentHeap ) );
				GF_ASSERT(0);
			}
		}
		else
		{
			GF_ASSERT_MSG(0, "�쐬���q�[�v�h�c������");
		}
	}
	else
	{
		GF_ASSERT_MSG(0, "�q�[�v���Q�d�ɍ���悤�Ƃ���");
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * �q�[�v�j��
 *
 * @param   heapID		�q�[�vID
 *
 */
//------------------------------------------------------------------
void sys_DeleteHeap( u32 heapID )
{
	GF_ASSERT_MSG((OS_GetProcMode() != OS_PROCMODE_IRQ), "Delete Heap:%d", heapID);

	{
		NNSFndHeapHandle  handle, parentHandle;

		handle = GetHeapHandle(heapID);


		if(handle != NNS_FND_HEAP_INVALID_HANDLE)
		{
			NNSFndHeapHandle  parentHandle;
			void* heapMemBlock;

		// �f�o�b�O���͖�����������̏����o��
			#ifdef PM_DEBUG
			if( HeapSys.count[heapID] )
			{
				PrintUnreleasedMemoryInfo( heapID );
				GF_ASSERT(0);
			}
			#endif

			NNS_FndDestroyExpHeap( handle );

			parentHandle = GetParentHeapHandle(heapID);
			heapMemBlock = GetHeapMemBlock(heapID);
			if(	(parentHandle != NNS_FND_HEAP_INVALID_HANDLE)
			&&	(heapMemBlock != NULL)
			){
				NNS_FndFreeToExpHeap( parentHandle, heapMemBlock );
			}else{
				GF_ASSERT(0);
			}

			SetHeapHandle(heapID, NNS_FND_HEAP_INVALID_HANDLE);
			SetParentHeapHandle(heapID, NNS_FND_HEAP_INVALID_HANDLE);
			SetHeapMemBlock(heapID, NULL);
			HeapSys.handleIdxTbl[ heapID ] = HeapSys.invalidHandleIdx;

			#ifdef ALLOCINFO_PRINT_HEAPID
			if( heapID == ALLOCINFO_PRINT_HEAPID )
			{
				OS_TPrintf("[HEAP] DELETE Heap(%d), parent's rest=%05x\n",
					heapID, NNS_FndGetTotalFreeSizeForExpHeap(parentHandle) );
			}
			else
			{
				u32 parentID;

				for(parentID=0; parentID<HeapSys.usableHeapMax; parentID++)
				{
					if( HeapSys.handle[parentID] == parentHandle ){ break; }
				}
				if( parentID == ALLOCINFO_PRINT_HEAPID )
				{
					OS_TPrintf("[HEAP] DELETE Heap(%d), parentHeap(%d), parent's rest=%05x\n",
						heapID, parentID, NNS_FndGetTotalFreeSizeForExpHeap(parentHandle) );
				}
			}
			#endif
		}
	}
}

//------------------------------------------------------------------
/**
 * �������A���P�[�g�{�́i�f�o�b�O�ŁA���i�łƂ��R�C�c���Ăяo���j
 *
 * @param   heapHandle		�g���q�[�v�n���h��
 * @param   size			�A���P�[�g�T�C�Y
 * @param   alignment		�A���C�����g
 * @param   heapID			�w�b�_�ɕۑ�����q�[�vID
 *
 * @retval  void*			�m�ۂ����������i�w�b�_���͔�΂��Ă���j
 */
//------------------------------------------------------------------
static void* AllocMemoryCore( NNSFndHeapHandle heapHandle, u32 size, s32 alignment, u32 heapID )
{
	void* mem;
    OSIntrMode old;

	GF_ASSERT_MSG(heapHandle != NNS_FND_HEAP_INVALID_HANDLE, "heapID=%d", heapID);
    old = OS_DisableInterrupts();
	mem = NNS_FndAllocFromExpHeapEx( heapHandle, size + sizeof(MEMORY_BLOCK_HEADER), alignment );
    OS_RestoreInterrupts( old );

	if( mem != NULL )
	{
		((MEMORY_BLOCK_HEADER*)mem)->heapID = heapID;
		(u8*)mem += sizeof(MEMORY_BLOCK_HEADER);
	}

	return mem;
}



#ifndef PM_DEBUG

#include "system\assert_warning_reset.h"
#include "communication\comm_state.h"

//------------------------------------------------------------------
/**
 * �ʐM���Ƀ������m�ۂɎ��s�����ꍇ�A�����I�ɃG���[��ʂ֔�΂�
 *
 */
//------------------------------------------------------------------
static void WarningResetCall(void)
{
	if( CommStateIsInitialize() )
	{
		AssertWarningResetCall();
	}
}


//------------------------------------------------------------------
/**
 * �q�[�v���烁�������m�ۂ���
 *
 * @param   heapID		�q�[�v�h�c
 * @param   size		�m�ۃT�C�Y
 *
 * @retval  void*		�m�ۂ����̈�A�h���X�i���s�Ȃ�NULL�j
 */
//------------------------------------------------------------------
void* sys_AllocMemory( u32 heapID, u32 size )
{
	void* ret = NULL;

	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle  h = GetHeapHandle( heapID );
		ret = AllocMemoryCore( h, size, DEFAULT_ALIGN, heapID );
	}

	if( ret != NULL )
	{
		HeapSys.count[heapID]++;
	}
	else
	{
		WarningResetCall();
	}

	return ret;
}
//------------------------------------------------------------------
/**
 * �q�[�v������烁�������m�ۂ���i�e���|�����̈�p�j
 *
 * @param   heapID		�q�[�v�h�c
 * @param   size		�m�ۃT�C�Y
 *
 * @retval  void*		�m�ۂ����̈�A�h���X�i���s�Ȃ�NULL�j
 */
//------------------------------------------------------------------
void* sys_AllocMemoryLo( u32 heapID, u32 size )
{
	void* ret = NULL;

	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle  h = GetHeapHandle( heapID );
		ret = AllocMemoryCore( h, size, -DEFAULT_ALIGN, heapID );
	}

	if( ret != NULL )
	{
		HeapSys.count[heapID]++;
	}
	else
	{
		WarningResetCall();
	}

	return ret;
}
#else	// #ifndef PM_DEBUG

//------------------------------------------------------------------
/**
 * �������m�ێ��̏ڍ׏��\��
 *
 * @param   header		�������u���b�N�w�b�_
 * @param   handle		�������u���b�N���܂܂��q�[�v�̃n���h��
 * @param   size		�m�ۃT�C�Y�i���N�G�X�g���ꂽ�T�C�Y�j
 *
 */
//------------------------------------------------------------------
static void PrintAllocInfo( const MEMORY_BLOCK_HEADER* header, NNSFndHeapHandle handle, u32 size )
{
	char filename[MEMBLOCK_FILENAME_AREASIZE+1];

	CopyFileName( filename, header );

	OS_TPrintf("[HEAP] ALLOC count=%3d rest=0x%08x adrs:0x%08x size:0x%05x %s(%d)\n",
				HeapSys.count[header->heapID], NNS_FndGetTotalFreeSizeForExpHeap(handle), 
				(u32)header, size+sizeof(MEMORY_BLOCK_HEADER), filename, header->lineNum );
}

//------------------------------------------------------------------
/**
 * ������������̏ڍ׏��\��
 *
 * @param   heapID			�q�[�vID
 * @param   size			�m�ۂ����T�C�Y
 * @param   handle			�q�[�v�n���h��
 * @param   filename		�Ăяo�����\�[�X�t�@�C����
 * @param   line			�Ăяo�����\�[�X�t�@�C���s�ԍ�
 *
 */
//------------------------------------------------------------------
static void PrintFreeInfo( const MEMORY_BLOCK_HEADER* header, NNSFndHeapHandle handle)
{
	char filename[MEMBLOCK_FILENAME_AREASIZE+1];
	u32  blockSize, restSize;

	CopyFileName( filename, header );

	blockSize = NNS_FndGetSizeForMBlockExpHeap(header) + sizeof(NNSiFndExpHeapMBlockHead);

	// �c��T�C�Y�͌��T�C�Y�{���ꂩ�������悤�Ƃ��郁�����u���b�N�̃T�C�Y�ɂȂ�͂�
	restSize = NNS_FndGetTotalFreeSizeForExpHeap(handle) + blockSize;

	OS_TPrintf("[HEAP] FREE  count=%3d rest=0x%08x adrs:0x%08x size:0x%05x %s(%d)\n",
				HeapSys.count[header->heapID], restSize, (u32)header, blockSize,
				filename, header->lineNum );
}



//------------------------------------------------------------------
/**
 * sys_AllocMemory�̃f�o�b�O�p���b�p�[�֐�
 *
 * @param   heapID			�q�[�vID
 * @param   size			�m�ۃT�C�Y
 * @param   filename		�Ăяo���\�[�X�̃t�@�C����
 * @param   line_num		�Ăяo���\�[�X�̍s�ԍ�
 *
 * @retval  void*			�m�ۂ����̈�A�h���X�i���s�Ȃ�NULL�j
 */
//------------------------------------------------------------------
void* sys_AllocMemoryDebug( u32 heapID, u32 size, const char* filename, u32 line_num )
{
	GF_ASSERT_MSG((OS_GetProcMode() != OS_PROCMODE_IRQ), "Alloc in IRQ\n %s(%d)", filename, line_num);

	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle  h = GetHeapHandle( heapID );
		void* mem = AllocMemoryCore( h, size, DEFAULT_ALIGN, heapID );

		if( mem != NULL )
		{
			HeaderDebugParamSet((MEMORY_BLOCK_HEADER*)( (u8*)mem - sizeof(MEMORY_BLOCK_HEADER) ),
									filename, line_num);
			HeapSys.count[heapID]++;

			#ifdef ALLOCINFO_PRINT_HEAPID
			if( ALLOCINFO_PRINT_HEAPID == heapID )
			{
				const MEMORY_BLOCK_HEADER* mh = (const MEMORY_BLOCK_HEADER*)((u8*)mem - sizeof(MEMORY_BLOCK_HEADER));
				PrintAllocInfo( mh, h, size );
				GF_ASSERT( sys_CheckHeapSafe( heapID ) );
			}
			#endif
		}
		else
		{
			PrintShortHeap( heapID, size, filename, line_num );
			GF_ASSERT(0);
		}

		return mem;
	}
	else
	{
		GF_ASSERT_MSG(0, "heapID = %d\n", heapID);
		return NULL;
	}
}
//------------------------------------------------------------------
/**
 * sys_AllocMemoryLo�̃f�o�b�O�p���b�p�[�֐�
 *
 * @param   heapID			�q�[�vID
 * @param   size			�m�ۃT�C�Y
 * @param   filename		�Ăяo���\�[�X�̃t�@�C����
 * @param   line_num		�Ăяo���\�[�X�̍s�ԍ�
 *
 * @retval  void*			�m�ۂ����̈�A�h���X�i���s�Ȃ�NULL�j
 */
//------------------------------------------------------------------
void* sys_AllocMemoryLoDebug( u32 heapID, u32 size, const char* filename, u32 line_num )
{
	GF_ASSERT_MSG((OS_GetProcMode() != OS_PROCMODE_IRQ), "Alloc in IRQ\n %s(%d)", filename, line_num);

	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle  h = GetHeapHandle( heapID );
		void* mem = AllocMemoryCore( h, size, -DEFAULT_ALIGN, heapID );

		if( mem != NULL )
		{
			HeaderDebugParamSet((MEMORY_BLOCK_HEADER*)( (u8*)mem - sizeof(MEMORY_BLOCK_HEADER) ),
									filename, line_num);
			HeapSys.count[heapID]++;

			#ifdef ALLOCINFO_PRINT_HEAPID
			if( ALLOCINFO_PRINT_HEAPID == heapID )
			{
				const MEMORY_BLOCK_HEADER* mh = (const MEMORY_BLOCK_HEADER*)((u8*)mem - sizeof(MEMORY_BLOCK_HEADER));
				PrintAllocInfo( mh, h, size );
				GF_ASSERT( sys_CheckHeapSafe( heapID ) );
			}
			#endif
		}
		else
		{
			PrintShortHeap( heapID, size, filename, line_num );
			GF_ASSERT(0);
		}
		return mem;
	}
	else
	{
		GF_ASSERT(0);
		return NULL;
	}
}
//------------------------------------------------------------------
/**
 * �u���b�N�w�b�_�Ƀf�o�b�O������������
 *
 * @param   header		�w�b�_�A�h���X
 * @param   filename	�t�@�C����
 * @param   line_no		�s�ԍ�
 *
 */
//------------------------------------------------------------------
static void HeaderDebugParamSet( MEMORY_BLOCK_HEADER* header, const char* filename, u32 line_no )
{
	int i;
	for(i = 0; i < MEMBLOCK_FILENAME_AREASIZE; i++)
	{
		header->filename[i] = filename[i];
		if( filename[i] == '\0' ){ break; }
	}
	header->lineNum = line_no;
}

//------------------------------------------------------------------
/**
 * �c�胁�������s�����Ċm�ۂł��Ȃ����b�Z�[�W�擾
 *
 * @param   heapID		�q�[�v�h�c
 * @param   size		�m�ۂ��悤�Ƃ����T�C�Y
 *
 */
//------------------------------------------------------------------
static void PrintShortHeap( u32 heapID, u32 size, const char* filename, u32 line_num )
{
	NNSFndHeapHandle h;
	u32 freeAreaSize, allocatableMaxSize;

	h = GetHeapHandle(heapID);
	freeAreaSize = NNS_FndGetTotalFreeSizeForExpHeap( h );
	allocatableMaxSize = NNS_FndGetAllocatableSizeForExpHeapEx( h, DEFAULT_ALIGN );

	GF_ASSERT_Printf("Can't alloc %ldbytes memory from Heap(%d)\n", size, heapID);
	GF_ASSERT_Printf("This Heap have %ldbytes Free Area\n", freeAreaSize );
	GF_ASSERT_Printf("and %ldbytes Allocatable Area\n", allocatableMaxSize );
	GF_ASSERT_Printf("%s(%d)\n", filename, line_num);

	GF_ASSERT_Printf("these Memoryblocks haven't released\n");
	PrintExistMemoryBlocks( heapID );
}
#endif	// #ifndef PM_DEBUG #else


//------------------------------------------------------------------
/**
 * �q�[�v����m�ۂ������������������
 *
 * @param   memory		�m�ۂ����������A�h���X
 *
 */
//------------------------------------------------------------------
void sys_FreeMemoryEz( void* memory )
{
	#ifdef PM_DEBUG
	if( OS_GetProcMode() == OS_PROCMODE_IRQ )
	{
		char filename[MEMBLOCK_FILENAME_AREASIZE+1];
		MEMORY_BLOCK_HEADER* header;

		header = (MEMORY_BLOCK_HEADER*)((u8*)memory - sizeof(MEMORY_BLOCK_HEADER));
		CopyFileName( filename, header );
		GF_ASSERT_MSG(0, "Free in IRQ\n %s(%d) siz:%x", filename, header->lineNum, 
						NNS_FndGetSizeForMBlockExpHeap(header) );
	}
	#endif

	{
		u32 heapID;

		(u8*)memory -= sizeof(MEMORY_BLOCK_HEADER);
		heapID = ((MEMORY_BLOCK_HEADER*)memory)->heapID;

		if( heapID < HeapSys.heapMax )
		{
			NNSFndHeapHandle  h = HeapSys.handle[ HeapSys.handleIdxTbl[ heapID ] ];

			GF_ASSERT(h != NNS_FND_HEAP_INVALID_HANDLE);
			if( HeapSys.count[heapID] == 0 )
			{
				sys_CheckHeapSafe(heapID);
			}
			GF_ASSERT_MSG( HeapSys.count[heapID], "heapID = %d", heapID );

			HeapSys.count[ heapID ]--;

			#ifdef ALLOCINFO_PRINT_HEAPID
			if( ALLOCINFO_PRINT_HEAPID == heapID )
			{
				GF_ASSERT( sys_CheckHeapSafe(heapID) );
				PrintFreeInfo( (const MEMORY_BLOCK_HEADER*)memory, h );
			}
			#endif

			{
				OSIntrMode old;
				old = OS_DisableInterrupts();
				NNS_FndFreeToExpHeap( h, memory );
				OS_RestoreInterrupts( old );
			}

		}
		else
		{
			GF_ASSERT_MSG(0, "heapID = %d\n", heapID);
		}
	}
}
//------------------------------------------------------------------
/**
 * �q�[�v����m�ۂ������������������i�q�[�vID�w��Łj
 *
 * ��������������q�[�vID���w�肷�鍇���I�ȗ��R�����邩������Ȃ��̂�
 *   �c���Ă����B���ʂ� FreeMemoryEz ���g���Ζ��Ȃ��͂��B
 *
 * @param   heapID		�q�[�vID
 * @param   memory		�m�ۂ����������|�C���^
 *
 */
//------------------------------------------------------------------
void sys_FreeMemory( u32 heapID, void* memory )
{
	ASSERT_IRQ_ENABLED();

	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle h = GetHeapHandle(heapID);

		GF_ASSERT(h != NNS_FND_HEAP_INVALID_HANDLE);

		(u8*)memory -= sizeof(MEMORY_BLOCK_HEADER);
		if( ((MEMORY_BLOCK_HEADER*)memory)->heapID != heapID )
		{
			GF_ASSERT_MSG(0, "�m�ێ��ƈႤ�q�[�vID�ŉ������悤�Ƃ��Ă���\n");
		}
		NNS_FndFreeToExpHeap( h, memory );

		GF_ASSERT( HeapSys.count[ heapID ] );
		HeapSys.count[ heapID ]--;

		#ifdef ALLOCINFO_PRINT_HEAPID
		if( ALLOCINFO_PRINT_HEAPID == heapID )
		{
			GF_ASSERT( sys_CheckHeapSafe( heapID ) );
			PrintFreeInfo( (const MEMORY_BLOCK_HEADER*)memory, h );
		}
		#endif

	}
	else
	{
		GF_ASSERT(0);
	}
}
//------------------------------------------------------------------
/**
 * �q�[�v�̋󂫗̈�T�C�Y��Ԃ�
 *
 * @param   heapID	�q�[�vID
 *
 * @retval  u32		�󂫗̈�T�C�Y�i�o�C�g�P�ʁj
 */
//------------------------------------------------------------------
u32 sys_GetHeapFreeSize( u32 heapID )
{
	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle h = GetHeapHandle(heapID);
		return NNS_FndGetTotalFreeSizeForExpHeap( h );
	}
	GF_ASSERT(0);
	return 0;
}
//------------------------------------------------------------------
/**
 * NitroSystem ���C�u�����n�֐����v������A���P�[�^���쐬����
 *
 * @param   pAllocator		NNSFndAllocator�\���̂̃A�h���X
 * @param   heapID			�q�[�vID
 * @param   alignment		�m�ۂ��郁�����u���b�N�ɓK�p����A���C�����g
 *
 */
//------------------------------------------------------------------
void sys_InitAllocator( NNSFndAllocator* pAllocator, u32 heapID, int alignment)
{
	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle h = GetHeapHandle(heapID);
		NNS_FndInitAllocatorForExpHeap( pAllocator, h, alignment );
	}
	else
	{
		GF_ASSERT(0);
	}
}

//------------------------------------------------------------------
/**
 * �m�ۂ����������u���b�N�̃T�C�Y���k������B
 *
 * @param   memBlock		�������u���b�N�|�C���^
 * @param   newSize			�k����̃T�C�Y�i�o�C�g�P�ʁj
 *
 *
 * �k���́A�������u���b�N�̌��������烁������������邱�Ƃōs���B
 * ������ꂽ���̓V�X�e���ɕԊ҂���A�V���ȃA���P�[�g�̈�Ƃ��Ďg�p�ł���B
 *
 * �Ⴆ�΁y�w�b�_�{���́z�̂悤�Ȍ`���̃O���t�B�b�N�o�C�i�����q�`�l�ɓǂݍ��݁A
 * ���̕���VRAM�ɓ]��������A�w�b�_�݂̂��c�������Ƃ����P�[�X�ȂǂŎg�p���邱�Ƃ�
 * �z�肵�Ă���B�g�p�͐T�d�ɁB
 *
 */
//------------------------------------------------------------------
void sys_CutMemoryBlockSize( void* memBlock, u32 newSize )
{
	ASSERT_IRQ_ENABLED();

	{
		u32 oldSize;

		(u8*)memBlock -= sizeof(MEMORY_BLOCK_HEADER);
		oldSize = NNS_FndGetSizeForMBlockExpHeap( memBlock );
		newSize += sizeof(MEMORY_BLOCK_HEADER);	// �Ăяo�����̓w�b�_���ӎ����Ă��Ȃ��̂�

		if( oldSize >= newSize )
		{
			u32 heapID;
			NNSFndHeapHandle handle;

			heapID = ((MEMORY_BLOCK_HEADER*)memBlock)->heapID;
			handle = GetHeapHandle(heapID);

			NNS_FndResizeForMBlockExpHeap( handle, memBlock, newSize );
		}
		else
		{
			GF_ASSERT(0);
		}
	}
}



//------------------------------------------------------------------
/**
 * �q�[�v�̈悪�j�󂳂�Ă��Ȃ����`�F�b�N�i�f�o�b�O�p�j
 *
 * @param   heapID		�q�[�vID
 *
 * @retval  BOOL		�j�󂳂�Ă��Ȃ����TRUE���Ԃ�
 */
//------------------------------------------------------------------
BOOL sys_CheckHeapSafe( u32 heapID )
{
	#ifdef PM_DEBUG
	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle h = GetHeapHandle(heapID);
		if( h != NNS_FND_HEAP_INVALID_HANDLE )
		{
			return NNS_FndCheckExpHeap( h, NNS_FND_HEAP_ERROR_PRINT );
		}
	}
	return TRUE;
	#else

	// �{�����i�łɂ͑��݂��Ȃ��͂��̊֐������A
	// GF_ASSERT�𐻕i�łł��L���ɂ������߁AASSERT�`�F�b�N���ɌĂ΂�邱�Ƃ̂���
	// ���̊֐����폜�ł��Ȃ��Ȃ����B���̂��߁A���ASSERT���X���[�ł���悤��
	// TRUE��Ԃ��֐��Ƃ��Ďc���Ă����B
	return TRUE;
	#endif
}

#ifdef PM_DEBUG
//------------------------------------------------------------------
/**
 * �S�������u���b�N��������Ă��邩�`�F�b�N�i�f�o�b�O�p�j
 *�i�����̊֐����Ă΂ꂽ���ɂ܂��g�p���������c���Ă����ASSERT�Ŏ~�܂�j
 *
 * @param   heapID		�q�[�v�h�c
 *
 */
//------------------------------------------------------------------
void sys_CheckHeapFullReleased( u32 heapID )
{
	if( HeapSys.count[heapID] )
	{
		PrintUnreleasedMemoryInfo( heapID );
		GF_ASSERT(0);
	}
}
//------------------------------------------------------------------
/**
 * �q�[�v����m�ۂ����������u���b�N�̎��T�C�Y�擾�i�f�o�b�O�p�j
 *
 * @param   memBlock		
 *
 * @retval  u32		�������u���b�N�T�C�Y
 */
//------------------------------------------------------------------
u32 sys_GetMemoryBlockSize( const void* memBlock )
{
	((u8*)memBlock) -= sizeof(MEMORY_BLOCK_HEADER);
	return NNS_FndGetSizeForMBlockExpHeap( memBlock );
}

//------------------------------------------------------------------
/**
 * �w��q�[�v�̃������A���P�[�g�񐔁��󂫗̈�T�C�Y��64bit�Ƀp�b�N���ĕԂ�
 *�i�q�[�v�j�����Ƃ͕ʂɃ��[�N�`�F�b�N���s�����߁j
 *
 * @param   heapID		�q�[�vID
 *
 * @retval  u64		
 */
//------------------------------------------------------------------
u64 sys_GetHeapState( u32 heapID )
{
	if( heapID < HeapSys.heapMax )
	{
		u64  ret;
		NNSFndHeapHandle h;

		h = GetHeapHandle(heapID);
		ret = (HeapSys.count[heapID] << 32) | NNS_FndGetTotalFreeSizeForExpHeap(h);
		return ret;
	}
	GF_ASSERT(0);
	return 0;
}

/*---------------------------------------------------------------------------*
 * @brief	�f�o�b�O�p�������󋵕\��
*---------------------------------------------------------------------------*/

//------------------------------------------------------------------
/**
 * ����q�[�v�̃������󂫗e�ʍ��v��\��
 *
 * @param   heapID		
 *
 */
//------------------------------------------------------------------
void sys_PrintHeapFreeSize( u32 heapID )
{
	if( heapID < HeapSys.heapMax )
	{
		NNSFndHeapHandle h = GetHeapHandle(heapID);
		OS_TPrintf("HEAP(ID :%d) FreeArea = %ld bytes\n", heapID, NNS_FndGetTotalFreeSizeForExpHeap(h) );
	}
}
//------------------------------------------------------------------
/**
 * ����q�[�v�̎g�p���������u���b�N����\��
 *
 * @param   heapID		
 *
 */
//------------------------------------------------------------------
void sys_PrintHeapExistMemoryInfo( u32 heapID )
{
	PrintExistMemoryBlocks( heapID );
}
//------------------------------------------------------------------
/**
 * ����q�[�v�̑S�������u���b�N����\��
 *
 * @param   heapID				�q�[�vID
 *
 */
//------------------------------------------------------------------
static void PrintExistMemoryBlocks( u32 heapID )
{
	NNSFndHeapHandle h = GetHeapHandle(heapID);
	NNS_FndVisitAllocatedForExpHeap( h, HeapConflictVisitorFunc, 0 );
}
//------------------------------------------------------------------
/**
 * sys_PrintHeapConflict�̃`�F�b�N���ʂ��G���[�Ȃ�A
 * �S�������u���b�N���������ɂ��Ă��̊֐����Ă΂��
 *
 * @param   memBlock		
 * @param   heapHandle		
 * @param   param		
 *
 */
//------------------------------------------------------------------
static void HeapConflictVisitorFunc(void* memBlock, NNSFndHeapHandle heapHandle, u32 param)
{
	char  filename[MEMBLOCK_FILENAME_AREASIZE + 1];
	int i;

	MEMORY_BLOCK_HEADER* head = (MEMORY_BLOCK_HEADER*)memBlock;

	CopyFileName( filename, head );

	GF_ASSERT_Printf(filename);
	GF_ASSERT_Printf(" (%d)", head->lineNum );
	GF_ASSERT_Printf(" adr:%08x", (u8*)memBlock + sizeof(MEMORY_BLOCK_HEADER));
	GF_ASSERT_Printf(" siz:%05x\n", NNS_FndGetSizeForMBlockExpHeap(head));
}

//------------------------------------------------------------------
/**
 * �������u���b�N�w�b�_�ɕۑ�����Ă���t�@�C�������o�b�t�@�ɃR�s�[
 *
 * @param   dst			�R�s�[��o�b�t�@
 * @param   header		�������u���b�N�w�b�_
 *
 */
//------------------------------------------------------------------
static void CopyFileName( char* dst, const MEMORY_BLOCK_HEADER* header )
{
	int i;

	// �I�[�R�[�h�i�V�ŗ̈�߂����ς��t�@�C�����Ɏg���Ă邽��
	// ���������������K�v...
	for(i = 0; i < MEMBLOCK_FILENAME_AREASIZE; i++)
	{
		if( header->filename[i] == '\0' ){ break; }
		dst[i] = header->filename[i];
	}
	dst[i] = '\0';

}

//------------------------------------------------------------------
/**
 * ������������̏����v�����g
 *
 * @param   heapID		
 *
 */
//------------------------------------------------------------------
static void PrintUnreleasedMemoryInfo( u32 heapID )
{
	GF_ASSERT_Printf("these Memoryblocks haven't released\n");
	GF_ASSERT_Printf("HeapID:%d  restcnt = %d .....\n", heapID, HeapSys.count[heapID]);
	#ifdef PM_DEBUG
	{
		NNSFndHeapHandle  handle = GetHeapHandle(heapID);
		u32  siz = NNS_FndGetTotalFreeSizeForExpHeap( handle );
		GF_ASSERT_Printf(" ID %d  freesize = 0x%x bytes \n", heapID, siz );
	}
	#endif
	PrintExistMemoryBlocks( heapID );
}

//==============================================================================================
// �f�o�b�O�p�q�[�v��ԃX�^�b�N
//==============================================================================================

struct _HEAP_STATE_STACK {
	u16   sp;
	u16   stackNum;
	u32   heapID;
	u64   stack[0];
};

//------------------------------------------------------------------
/**
 * �q�[�v��ԃX�^�b�N��V�K�쐬
 *
 * @param   heapID			�`�F�b�N����q�[�vID
 * @param   stackNum		�X�^�b�N�v�f��
 *
 * @retval  HEAP_STATE_STACK*		�쐬�����X�^�b�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
HEAP_STATE_STACK*  HSS_Create( u32 heapID, u32 stackNum )
{
	HEAP_STATE_STACK* hss;
	u32 size;

	size = sizeof(HEAP_STATE_STACK) + sizeof(u64)*stackNum;
	hss = sys_AllocMemoryLo( HEAPID_BASE_DEBUG, size );
	hss->sp = 0;
	hss->heapID = heapID;
	return hss;
}

//------------------------------------------------------------------
/**
 * �q�[�v��� Push
 *
 * @param   hss		�X�^�b�N�ւ̃|�C���^
 *
 */
//------------------------------------------------------------------
void HSS_Push( HEAP_STATE_STACK* hss )
{
	GF_ASSERT( hss->sp < hss->stackNum );
	hss->stack[hss->sp++] = sys_GetHeapState( hss->heapID );
}

//------------------------------------------------------------------
/**
 * �q�[�v��� Pop
 *
 * @param   hss		�X�^�b�N�ւ̃|�C���^
 *
 */
//------------------------------------------------------------------
void HSS_Pop( HEAP_STATE_STACK* hss )
{
	GF_ASSERT( hss->sp );
	hss->sp--;
	GF_ASSERT( hss->stack[hss->sp] == sys_GetHeapState(hss->heapID) );
}


//------------------------------------------------------------------
/**
 * �q�[�v��ԃX�^�b�N��j������
 *
 * @param   hss		�X�^�b�N�ւ̃|�C���^
 *
 */
//------------------------------------------------------------------
void HSS_Delete( HEAP_STATE_STACK* hss )
{
	sys_FreeMemoryEz( hss );
}


#endif	// PM_DEBUG


