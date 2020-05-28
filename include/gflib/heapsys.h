//==============================================================================
/**
 *
 *@file		heapsys.h
 *@brief	�q�[�v�̈�Ǘ�
 *@author	taya
 *@data		2005.08.25
 *
 */
//==============================================================================
#ifndef __HEAPSYS_H__
#define __HEAPSYS_H__

#include <nnsys.h>

//==============================================================
/**
 *	��{�q�[�v�쐬�p�����[�^�\����
 */
//==============================================================
typedef struct {
	u32        size;		///< �q�[�v�T�C�Y
	OSArenaId  arenaID;		///< �쐬��A���[�iID
}HEAP_INIT_HEADER;



//------------------------------------------------------------------
/**
 * �q�[�v�V�X�e���������i�v���O�����N�����ɂP�x�����Ă΂��j
 *
 * @param   header			��{�q�[�v�������\���̂ւ̃|�C���^
 * @param   baseHeapMax		��{�q�[�v����
 * @param   heapMax			��{�q�[�v�E���[�U�[�q�[�v���v��
 * @param   startOffset		�q�[�v�̈�J�n�I�t�Z�b�g�i�v�S�o�C�g�A���C���j
 *
 */
//------------------------------------------------------------------
extern void sys_InitHeapSystem(const HEAP_INIT_HEADER* header, u32 baseHeapMax, u32 totalHeapMax, u32 startOffset);


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
extern BOOL sys_CreateHeap( u32 parentHeapID, u32 childHeapID, u32 size );


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
extern BOOL sys_CreateHeapLo( u32 parentHeapID, u32 childHeapID, u32 size );

//------------------------------------------------------------------
/**
 * �q�[�v�j��
 *
 * @param   heapID		�q�[�vID
 *
 */
//------------------------------------------------------------------
extern void sys_DeleteHeap( u32 heapID );


//------------------------------------------------------------------
/*
 * 	�������m��
 *
 *	sys_AllocMemory �̓q�[�v�̐擪����󂫗̈��T���ă����������蓖�Ă�B
 *	sys_AllocMemoryLo �̓q�[�v�̌������󂫗̈��T���ă����������蓖�Ă�B
 *
 *	VRAM�]���O�̃O���t�B�b�N�f�[�^�ꎞ�I�ǂݍ��ݗ̈�ȂǁA�����ɉ������̈��
 *	sys_AllocMemoryLo �Ŋm�ۂ���Η̈�̒f�Љ����N����Â炭�Ȃ�͂��B
 */
//------------------------------------------------------------------

#ifndef PM_DEBUG
extern void* sys_AllocMemory( u32 heap, u32 size );
extern void* sys_AllocMemoryLo( u32 heap, u32 size );
#else


// �f�o�b�O�r���h���ɂ̓}�N���Ń��b�v���ČĂяo���\�[�X����n���Ă���

extern void* sys_AllocMemoryDebug( u32 heap, u32 size, const char* filename, u32 line_num );
extern void* sys_AllocMemoryLoDebug( u32 heap, u32 size, const char* filename, u32 line_num );
#define sys_AllocMemory(h,s)	sys_AllocMemoryDebug((h),(s),__FILE__,__LINE__);
#define sys_AllocMemoryLo(h,s)	sys_AllocMemoryLoDebug((h),(s),__FILE__,__LINE__);

#endif


//------------------------------------------------------------------
/*
 * 	���������
 *
 *  �m�ێ���u32���w�b�_�ɕۑ����邽�߁A������ɂ͕s�v�B
 *  �ʏ�� sys_FreeMemoryEz ���g���Ζ��Ȃ��B
 *
 *  sys_FreeMemory �̕��́A�ꉞ���̂܂܂̃C���^�[�t�F�[�X�Ŏc���Ă���
 *
 */
//------------------------------------------------------------------
extern void sys_FreeMemoryEz( void* memory );
extern void sys_FreeMemory( u32 heap, void* memory );


//------------------------------------------------------------------
/*
 * 	�q�[�v���擾
 */
//------------------------------------------------------------------
extern u32 sys_GetHeapFreeSize( u32 heap );
extern u32 sys_GetHeapAllocatedSize( u32 heap );

//------------------------------------------------------------------
/*
 * 	�A���P�[�^�[�쐬�iNitroSystem ���C�u�����n�֐����v������ꍇ������j
 */
//------------------------------------------------------------------
extern void sys_InitAllocator( NNSFndAllocator* pAllocator, u32 heap, int alignment);


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
extern void sys_CutMemoryBlockSize( void* memBlock, u32 newSize );


//------------------------------------------------------------------
/*
 * 	�q�[�v���擾�i�f�o�b�O���̂ݗL���j
 */
//------------------------------------------------------------------
extern BOOL sys_CheckHeapSafe( u32 heap );

#ifdef PM_DEBUG
extern void sys_PrintHeapFreeSize( u32 heapID );
extern void sys_PrintHeapExistMemoryInfo( u32 heapID );
extern u64 sys_GetHeapState( u32 heapID );
extern void sys_PrintHeapConflict( u32 heap, u32 assertionMemSize ); 
extern u32 sys_GetMemoryBlockSize( const void* memBlock );
extern void sys_CheckHeapFullReleased( u32 heapID );
#else
#define sys_PrintHeapFreeSize(h)		/* */
#define sys_PrintHeapExistMemoryInfo(h)	/* */
#define sys_GetHeapState(h)				/* */
#define sys_PrintHeapConflict(h, s)		/* */
#define sys_GetMemoryBlockSize(b)		/* */
#define sys_CheckHeapFullReleased(h)	/* */
#endif


//------------------------------------------------------------------
/*
 * 	�q�[�v���擾�i�f�o�b�O���̂ݗL���j
 */
//------------------------------------------------------------------
typedef struct _HEAP_STATE_STACK	HEAP_STATE_STACK;

#ifdef PM_DEBUG
extern HEAP_STATE_STACK*  HSS_Create( u32 heapID, u32 stackNum );
extern void HSS_Push( HEAP_STATE_STACK* hss );
extern void HSS_Pop( HEAP_STATE_STACK* hss );
extern void HSS_Delete( HEAP_STATE_STACK* hss );
#else
#define HSS_Create(a,b,c)	((void)0);
#define HSS_Push(p)			((void)0);
#define HSS_Pop(p)			((void)0);
#define HSS_Delete(p)		((void)0);
#endif



//------------------------------------------------------------------
/*
 * 	�ȒP���������[�N�`�F�b�N�i���݂͖����j
 */
//------------------------------------------------------------------
#define HeapStatePush()		/* */
#define HeapStatePop()		/* */
#define HeapStateCheck(h)	/* */




#endif	// __HEAPSYS_H__
