
//============================================================================================
/**
 * @file	arc_tool.h
 * @bfief	�A�[�J�C�o�p�c�[���v���O����
 * @author	HisashiSogabe
 * @date	05.05.30
 */
//============================================================================================

#ifndef	__ARC_TOOL_H_
#define	__ARC_TOOL_H_

#include	"system/arc_tool.dat"

//============================================================================================
//		�萔��`
//============================================================================================

#define	OFS_NO_SET		(0)		///<ArchiveDataLoadOfs,ArchiveDataLoadOfs�pOFS�l�Ȃ��̒萔
#define	SIZE_NO_SET		(0)		///<ArchiveDataLoadOfs,ArchiveDataLoadOfs�pSIZE�l�Ȃ��̒萔

extern	void	ArchiveDataLoad(void *data,int file_kind,int index);
extern	void	*ArchiveDataLoadMalloc(int file_kind,int index,int heap_id);
extern	void	*ArchiveDataLoadMallocLo(int file_kind,int index,int heap_id);
extern	void	ArchiveDataLoadOfs(void *data,int file_kind,int index,int ofs,int size);
extern	void	*ArchiveDataLoadMallocOfs(int file_kind,int index,int heap_id,int ofs,int size);
extern	void	*ArchiveDataLoadMallocOfsLo(int file_kind,int index,int heap_id,int ofs,int size);
extern	u16		ArchiveDataFileCntGet(int file_kind,int index);
extern	u32		ArchiveDataSizeGet(int file_kind,int index);





/*====================================================================================*/
/*
  �A�[�J�C�u�f�[�^�n���h������

    �P�̃A�[�J�C�u�t�@�C�����牽�x���f�[�^�擾���s���������A�t�@�C����
  �I�[�v���E�N���[�Y�񐔂����炷���Ƃŏ������ׂ��y�������邽�߂̎d�g�݁B
*/
/*====================================================================================*/


//--------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�n���h���\���̂̐錾
 */
//--------------------------------------------------
typedef struct _ARCHANDLE  ARCHANDLE;

//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�n���h���I�[�v��
 * �i�����Ńt�@�C�����I�[�v�����܂��j
 *
 * @param   arcId		�A�[�J�C�u�f�[�^�C���f�b�N�X
 * @param   heapId		�Ǘ��p�q�[�v�h�c
 *
 * @retval  ARCHANDLE	�I�[�v�����ꂽ�n���h���̃|�C���^�i���s�Ȃ�NULL�j
 */
//------------------------------------------------------------------
extern ARCHANDLE* ArchiveDataHandleOpen( u32 arcId, u32 heapId );

//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�n���h���N���[�Y
 * �i�����Ńt�@�C�����N���[�Y���܂��j
 *
 * @param   handle			�n���h���|�C���^
 *
 */
//------------------------------------------------------------------
extern void ArchiveDataHandleClose( ARCHANDLE* handle );


//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�n���h�����g���ăf�[�^�擾
 *
 * @param   handle		�n���h���|�C���^
 * @param   datId		�A�[�J�C�u���̃f�[�^�C���f�b�N�X
 * @param   buffer		�f�[�^�ǂݍ��ݐ�o�b�t�@
 *
 */
//------------------------------------------------------------------
extern void ArchiveDataLoadByHandle( ARCHANDLE* handle, u32 datId, void* buffer );

//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�n���h�����g���ăf�[�^�T�C�Y�擾
 *
 * @param   handle		�n���h���|�C���^
 * @param   datId		�A�[�J�C�u���̃f�[�^�C���f�b�N�X
 * @retval	u32			�C���f�b�N�X�̃f�[�^�T�C�Y
 *
 */
//------------------------------------------------------------------
extern u32 ArchiveDataSizeGetByHandle( ARCHANDLE* handle, u32 datId );

//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�n���h�����g���ăf�[�^�擾�i�ǂݍ��݊J�n�I�t�Z�b�g���T�C�Y�w��j
 *
 * @param   handle		�n���h���|�C���^
 * @param   datId		�A�[�J�C�u���̃f�[�^�C���f�b�N�X
 * @param   ofs			�ǂݍ��݊J�n�I�t�Z�b�g
 * @param   size		�ǂݍ��݃T�C�Y
 * @param   buffer		�f�[�^�ǂݍ��ݐ�o�b�t�@
 *
 */
//------------------------------------------------------------------
extern void ArchiveDataLoadOfsByHandle( ARCHANDLE* handle, u32 datId, u32 ofs, u32 size, void* buffer );

//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�n���h�����g���ăf�[�^�擾�i�����ŃA���P�[�g�����������Ɂj
 *
 * @param   handle			�n���h���|�C���^
 * @param   datID			�A�[�J�C�u���̃f�[�^�C���f�b�N�X
 * @param   heapID			�������A���P�[�g�p�̃q�[�v�h�c
 *
 * @retval  u32				�f�[�^�T�C�Y�i�o�C�g�j
 */
//------------------------------------------------------------------
extern void* ArchiveDataLoadAllocByHandle( ARCHANDLE* handle, u32 datID, u32 heapID );

//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�n���h�����g���ăC���[�W�f�[�^�I�t�Z�b�g�擾
 *
 * @param   handle		�n���h���|�C���^
 * @param   datId		�A�[�J�C�u���̃f�[�^�C���f�b�N�X
 * @param   offset		�I�t�Z�b�g�ǂݍ��ݐ�o�b�t�@
 *
 */
//------------------------------------------------------------------
extern void ArchiveDataLoadImgofsByHandle( ARCHANDLE* handle, u32 datId, u32* offset );

//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�n���h�����g���ăf�[�^�擾�i�t�@�C���n���h�������̑�������ǂݍ��݁j
 *
 * @param   handle		�n���h���|�C���^
 * @param   size		�ǂݍ��݃T�C�Y
 * @param   buffer		�f�[�^�ǂݍ��ݐ�o�b�t�@
 *
 */
//------------------------------------------------------------------
extern	void ArchiveDataLoadByHandleContinue( ARCHANDLE* handle, u32 size, void* buffer );

//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�n���h������ăt�@�C���V�[�N
 *
 * @param   handle		�n���h���|�C���^
 * @param   size
 *
 */
//------------------------------------------------------------------
void ArchiveDataSeekByHandle( ARCHANDLE* handle, u32 size );

//============================================================================================
/**
 * �A�[�J�C�u�t�@�C���f�[�^�̃t�@�C�������擾(�n���h���g�p)
 *
 * @param	handle			�n���h���|�C���^
 * @retval	u16				�t�@�C����	
 */
//============================================================================================
u16		ArchiveDataFileCntGetByHandle(ARCHANDLE* handle);
#endif	__ARC_TOOL_H_
