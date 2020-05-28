
//============================================================================================
/**
 * @file	arc_tool.c
 * @bfief	�A�[�J�C�o�p�c�[���v���O����
 * @author	HisashiSogabe
 * @date	05.05.30
 */
//============================================================================================

#include "common.h"
#define	 __ARC_TOOL_DAT_TBL_	//�A�[�J�C�o�t�@�C���e�[�u�����L���ɂ��邽�߂̒�`
#include "system/arc_tool.h"
#include "arc_tool_def.h"

static	void	ArchiveDataLoadIndex(void *data,const char *name,int index,int ofs,int ofs_size);
static	void	*ArchiveDataLoadIndexMalloc(const char *name,int index,int heap_id,int ofs,int ofs_size,int flag);

void	ArchiveDataLoad(void *data,int file_kind,int index);
void	*ArchiveDataLoadMalloc(int file_kind,int index,int heap_id);
void	*ArchiveDataLoadMallocLo(int file_kind,int index,int heap_id);
void	ArchiveDataLoadOfs(void *data,int file_kind,int index,int ofs,int size);
void	*ArchiveDataLoadMallocOfs(int file_kind,int index,int heap_id,int ofs,int size);
void	*ArchiveDataLoadMallocOfsLo(int file_kind,int index,int heap_id,int ofs,int size);
u16		ArchiveDataFileCntGet(int file_kind,int index);
u32		ArchiveDataSizeGet(int file_kind,int index);

void	ArchiveDataLoadByHandleContinue( ARCHANDLE* handle, u32 size, void* buffer );

#define	ALLOC_HEAD	(0)		//�̈���m�ۂ���Ƃ��擪����m��
#define	ALLOC_TAIL	(1)		//�̈���m�ۂ���Ƃ���납��m��

//============================================================================================
/**
 *
 *	nnsarc�ō쐬�����A�[�J�C�u�t�@�C���ɑ΂���Index���w�肵�ĔC�ӂ̃f�[�^�����o��
 *
 * @param[in]	data		�ǂݍ��񂾃f�[�^���i�[���郏�[�N�̃|�C���^
 * @param[in]	name		�ǂݍ��ރA�[�J�C�u�t�@�C����
 * @param[in]	index		�ǂݍ��ރf�[�^�̃A�[�J�C�u��̃C���f�b�N�X�i���o�[
 * @param[in]	ofs			�ǂݍ��ރf�[�^�̐擪����̃I�t�Z�b�g
 * @param[in]	ofs_size	�ǂݍ��ރf�[�^�T�C�Y
 *
 */
//============================================================================================
static	void	ArchiveDataLoadIndex(void *data,const char *name,int index,int ofs,int ofs_size)
{
	FSFile		p_file;
	u32			size=0;
	u32			fat_top=0;
	u32			fnt_top=0;
	u32			img_top=0;
	u32			top=0;
	u32			bottom=0;
	u16			file_cnt=0;

	FS_InitFile(&p_file);
	FS_OpenFile(&p_file,name);
	FS_SeekFile(&p_file,ARC_HEAD_SIZE_POS,FS_SEEK_SET);				///<�A�[�J�C�u�w�b�_�̃T�C�Y�i�[�ʒu�Ɉړ�
	FS_ReadFile(&p_file,&size,2);									///<�A�[�J�C�u�w�b�_�T�C�Y�����[�h
	fat_top=size;
	FS_SeekFile(&p_file,fat_top+SIZE_OFFSET,FS_SEEK_SET);			///<FAT�̃T�C�Y�i�[�ʒu�Ɉړ�
	FS_ReadFile(&p_file,&size,4);									///<FAT�T�C�Y�����[�h
	FS_ReadFile(&p_file,&file_cnt,2);								///<FileCount�����[�h
	GF_ASSERT_MSG(file_cnt>index,"ServerArchiveDataLoadIndex file=%s, fileCnt=%d, index=%d", name, file_cnt, index);
	fnt_top=fat_top+size;
	FS_SeekFile(&p_file,fnt_top+SIZE_OFFSET,FS_SEEK_SET);			///<FNT�̃T�C�Y�i�[�ʒu�Ɉړ�
	FS_ReadFile(&p_file,&size,4);									///<FNT�T�C�Y�����[�h
	img_top=fnt_top+size;
	
	FS_SeekFile(&p_file,fat_top+FAT_HEAD_SIZE+index*8,FS_SEEK_SET);	///<���o������FAT�e�[�u���Ɉړ�
	FS_ReadFile(&p_file,&top,4);									///<FAT�e�[�u��top�����[�h
	FS_ReadFile(&p_file,&bottom,4);									///<FAT�e�[�u��bottom�����[�h

	FS_SeekFile(&p_file,img_top+IMG_HEAD_SIZE+top+ofs,FS_SEEK_SET);	///<���o������IMG�̐擪�Ɉړ�
	
	if(ofs_size){
		size=ofs_size;
	}
	else{
		size=bottom-top;
	}

	GF_ASSERT_MSG(size!=0,"ServerArchiveDataLoadIndex:ReadDataSize=0!");
	FS_ReadFile(&p_file,data,size);									///<�f�[�^�����[�h

	FS_CloseFile(&p_file);
}


//============================================================================================
/**
 *
 *	nnsarc�ō쐬�����A�[�J�C�u�t�@�C���ɑ΂���Index���w�肵�ĔC�ӂ̃f�[�^�����o��
 *	�ǂݍ��񂾃f�[�^���i�[���郏�[�N�����̊֐����Ŋm�ۂ��āA�|�C���^��Ԃ�
 *
 * @param[in]	name		�ǂݍ��ރA�[�J�C�u�t�@�C����
 * @param[in]	index		�ǂݍ��ރf�[�^�̃A�[�J�C�u��̃C���f�b�N�X�i���o�[
 * @param[in]	heap_id		���������m�ۂ���q�[�v�̈��ID
 * @param[in]	ofs			�ǂݍ��ރf�[�^�̐擪����̃I�t�Z�b�g
 * @param[in]	ofs_size	�ǂݍ��ރf�[�^�T�C�Y
 * @param[in]	flag		�̈�̑O��ǂ��炩��m�ۂ��邩�t���O
 *
 */
//============================================================================================
static	void	*ArchiveDataLoadIndexMalloc(const char *name,int index,int heap_id,int ofs,int ofs_size,int flag)
{
	FSFile		p_file;
	u32			size=0;
	u32			fat_top=0;
	u32			fnt_top=0;
	u32			img_top=0;
	u32			top=0;
	u32			bottom=0;
	void		*data;
	u16			file_cnt=0;

	FS_InitFile(&p_file);
	FS_OpenFile(&p_file,name);
	FS_SeekFile(&p_file,ARC_HEAD_SIZE_POS,FS_SEEK_SET);				///<�A�[�J�C�u�w�b�_�̃T�C�Y�i�[�ʒu�Ɉړ�
	FS_ReadFile(&p_file,&size,2);									///<�A�[�J�C�u�w�b�_�T�C�Y�����[�h
	fat_top=size;
	FS_SeekFile(&p_file,fat_top+SIZE_OFFSET,FS_SEEK_SET);			///<FAT�̃T�C�Y�i�[�ʒu�Ɉړ�
	FS_ReadFile(&p_file,&size,4);									///<FAT�T�C�Y�����[�h
	FS_ReadFile(&p_file,&file_cnt,2);								///<FileCount�����[�h
	GF_ASSERT_MSG(file_cnt>index,"ServerArchiveDataLoadIndex file=%s, fileCnt=%d, index=%d", name, file_cnt, index);
	fnt_top=fat_top+size;
	FS_SeekFile(&p_file,fnt_top+SIZE_OFFSET,FS_SEEK_SET);			///<FNT�̃T�C�Y�i�[�ʒu�Ɉړ�
	FS_ReadFile(&p_file,&size,4);									///<FNT�T�C�Y�����[�h
	img_top=fnt_top+size;
	
	FS_SeekFile(&p_file,fat_top+FAT_HEAD_SIZE+index*8,FS_SEEK_SET);	///<���o������FAT�e�[�u���Ɉړ�
	FS_ReadFile(&p_file,&top,4);									///<FAT�e�[�u��top�����[�h
	FS_ReadFile(&p_file,&bottom,4);									///<FAT�e�[�u��bottom�����[�h

	FS_SeekFile(&p_file,img_top+IMG_HEAD_SIZE+top+ofs,FS_SEEK_SET);		///<���o������IMG�̐擪�Ɉړ�

	if(ofs_size){
		size=ofs_size;
	}
	else{
		size=bottom-top;
	}
	GF_ASSERT_MSG(size!=0,"ServerArchiveDataLoadIndex:ReadDataSize=0!");
	if(flag==ALLOC_HEAD){
		data=sys_AllocMemory(heap_id,size);
	}
	else{
		data=sys_AllocMemoryLo(heap_id,size);
	}
	FS_ReadFile(&p_file,data,size);									///<�f�[�^�����[�h

	FS_CloseFile(&p_file);

	return data;
}

//============================================================================================
/**
 * �A�[�J�C�u�t�@�C���f�[�^���[�h
 *
 * @param[in]	data		�ǂݍ��񂾃f�[�^���i�[���郏�[�N�̃|�C���^
 * @param[in]	arcID		�ǂݍ��ރA�[�J�C�u�t�@�C���̎�ރC���f�b�N�X�i���o�[�iarc_tool.h�ɋL�q�j
 * @param[in]	datID		�ǂݍ��ރf�[�^�̃A�[�J�C�u�t�@�C����̃C���f�b�N�X�i���o�[
 */
//============================================================================================
void	ArchiveDataLoad(void *data, int arcID, int datID)
{
	ArchiveDataLoadIndex(data, ArchiveFileTable[arcID], datID, OFS_NO_SET, SIZE_NO_SET);
}

//============================================================================================
/**
 * �A�[�J�C�u�t�@�C���f�[�^���[�h�i�ǂݍ��񂾃f�[�^���i�[���郏�[�N���֐����Ŋm�ۂ���o�[�W�����j
 *
 * ���֐����Ń��[�N��Alloc����̂ŁA���O�ŊJ������������K�v������܂�(sys_FreeMemoryEz(�̈�|�C���^)�ŊJ���j
 *
 * @param[in]	arcID		�ǂݍ��ރA�[�J�C�u�t�@�C���̎�ރC���f�b�N�X�i���o�[�iarc_tool.h�ɋL�q�j
 * @param[in]	datID		�ǂݍ��ރf�[�^�̃A�[�J�C�u�t�@�C����̃C���f�b�N�X�i���o�[
 * @param[in]	heap_id		���������m�ۂ���q�[�v�̈��ID
 *
 * @retval	�֐����Ŋm�ۂ����f�[�^�i�[���[�N�̃A�h���X
 */
//============================================================================================
void* ArchiveDataLoadMalloc(int arcID, int datID, int heapID)
{
	return	ArchiveDataLoadIndexMalloc(ArchiveFileTable[arcID],datID,heapID,OFS_NO_SET,SIZE_NO_SET,ALLOC_HEAD);
}

//============================================================================================
/**
 * �A�[�J�C�u�t�@�C���f�[�^���[�h�i�ǂݍ��񂾃f�[�^���i�[���郏�[�N���֐����Ŋm�ۂ���o�[�W�����i�̈�̌�납��m�ہj�j
 *
 * ���֐����Ń��[�N��Alloc����̂ŁA���O�ŊJ������������K�v������܂�(sys_FreeMemoryEz(�̈�|�C���^)�ŊJ���j
 *
 * @param[in]	arcID		�ǂݍ��ރA�[�J�C�u�t�@�C���̎�ރC���f�b�N�X�i���o�[�iarc_tool.h�ɋL�q�j
 * @param[in]	datID		�ǂݍ��ރf�[�^�̃A�[�J�C�u�t�@�C����̃C���f�b�N�X�i���o�[
 * @param[in]	heapID		���������m�ۂ���q�[�v�̈��ID
 *
 * @retval	�֐����Ŋm�ۂ����f�[�^�i�[���[�N�̃A�h���X
 */
//============================================================================================
void* ArchiveDataLoadMallocLo(int arcID, int datID, int heapID)
{
	return	ArchiveDataLoadIndexMalloc(ArchiveFileTable[arcID], datID, heapID, OFS_NO_SET, SIZE_NO_SET, ALLOC_TAIL);
}

//============================================================================================
/**
 * �A�[�J�C�u�t�@�C���f�[�^���[�h�i�I�t�Z�b�g�w�肠��j
 *
 * @param[in]	data		�ǂݍ��񂾃f�[�^���i�[���郏�[�N�̃|�C���^
 * @param[in]	arcID		�ǂݍ��ރA�[�J�C�u�t�@�C���̎�ރC���f�b�N�X�i���o�[�iarc_tool.h�ɋL�q�j
 * @param[in]	datID		�ǂݍ��ރf�[�^�̃A�[�J�C�u�t�@�C����̃C���f�b�N�X�i���o�[
 * @param[in]	ofs			�ǂݍ��ރf�[�^�̐擪����̃I�t�Z�b�g
 * @param[in]	size		�ǂݍ��ރf�[�^�T�C�Y
 */
//============================================================================================
void ArchiveDataLoadOfs(void *data, int arcID, int datID, int ofs, int size)
{
	ArchiveDataLoadIndex(data, ArchiveFileTable[arcID], datID, ofs, size);
}

//============================================================================================
/**
 * �A�[�J�C�u�t�@�C���f�[�^���[�h�i�ǂݍ��񂾃f�[�^���i�[���郏�[�N���֐����Ŋm�ۂ���o�[�W�����ƃI�t�Z�b�g�w�肠��j
 *
 * ���֐����Ń��[�N��Alloc����̂ŁA���O�ŊJ������������K�v������܂�(sys_FreeMemoryEz(�̈�|�C���^)�ŊJ���j
 *
 * @param[in]	arcID		�ǂݍ��ރA�[�J�C�u�t�@�C���̎�ރC���f�b�N�X�i���o�[�iarc_tool.h�ɋL�q�j
 * @param[in]	datID		�ǂݍ��ރf�[�^�̃A�[�J�C�u�t�@�C����̃C���f�b�N�X�i���o�[
 * @param[in]	heapID		���������m�ۂ���q�[�v�̈��ID
 * @param[in]	ofs			�ǂݍ��ރf�[�^�̐擪����̃I�t�Z�b�g
 * @param[in]	size		�ǂݍ��ރf�[�^�T�C�Y
 *
 * @retval	�֐����Ŋm�ۂ����f�[�^�i�[���[�N�̃A�h���X
 */
//============================================================================================
void* ArchiveDataLoadMallocOfs(int arcID, int datID, int heapID, int ofs, int size)
{
	return	ArchiveDataLoadIndexMalloc(ArchiveFileTable[arcID],datID,heapID,ofs,size,ALLOC_HEAD);
}

//============================================================================================
/**
 * �A�[�J�C�u�t�@�C���f�[�^���[�h�i�ǂݍ��񂾃f�[�^���i�[���郏�[�N���֐����Ŋm�ۂ���o�[�W�����ƃI�t�Z�b�g�w�肠��j
 *
 * ���֐����Ń��[�N��Alloc����̂ŁA���O�ŊJ������������K�v������܂�(sys_FreeMemoryEz(�̈�|�C���^)�ŊJ���j
 *
 * @param[in]	arcID		�ǂݍ��ރA�[�J�C�u�t�@�C���̎�ރC���f�b�N�X�i���o�[�iarc_tool.h�ɋL�q�j
 * @param[in]	datID		�ǂݍ��ރf�[�^�̃A�[�J�C�u�t�@�C����̃C���f�b�N�X�i���o�[
 * @param[in]	heapID		���������m�ۂ���q�[�v�̈��ID
 * @param[in]	ofs			�ǂݍ��ރf�[�^�̐擪����̃I�t�Z�b�g
 * @param[in]	size		�ǂݍ��ރf�[�^�T�C�Y
 *
 * @retval	�֐����Ŋm�ۂ����f�[�^�i�[���[�N�̃A�h���X
 */
//============================================================================================
void	*ArchiveDataLoadMallocOfsLo(int arcID, int datID, int heapID, int ofs, int size)
{
	return	ArchiveDataLoadIndexMalloc(ArchiveFileTable[arcID],datID,heapID,ofs,size,ALLOC_TAIL);
}

//============================================================================================
/**
 * �A�[�J�C�u�t�@�C���f�[�^�̃t�@�C�������擾
 *
 * @param[in]	arcID	�ǂݍ��ރA�[�J�C�u�t�@�C���̎�ރC���f�b�N�X�i���o�[�iarc_tool.h�ɋL�q�j
 * @param[in]	datID		�ǂݍ��ރf�[�^�̃A�[�J�C�u�t�@�C����̃C���f�b�N�X�i���o�[
 */
//============================================================================================
u16		ArchiveDataFileCntGet(int arcID, int datID)
{
	FSFile		p_file;
	u32			size=0;
	u32			fat_top=0;
	u16			file_cnt=0;

	FS_InitFile(&p_file);
	FS_OpenFile(&p_file,ArchiveFileTable[arcID]);
	FS_SeekFile(&p_file,ARC_HEAD_SIZE_POS,FS_SEEK_SET);				///<�A�[�J�C�u�w�b�_�̃T�C�Y�i�[�ʒu�Ɉړ�
	FS_ReadFile(&p_file,&size,2);									///<�A�[�J�C�u�w�b�_�T�C�Y�����[�h
	fat_top=size;
	FS_SeekFile(&p_file,fat_top+SIZE_OFFSET,FS_SEEK_SET);			///<FAT�̃T�C�Y�i�[�ʒu�Ɉړ�
	FS_ReadFile(&p_file,&size,4);									///<FAT�T�C�Y�����[�h
	FS_ReadFile(&p_file,&file_cnt,2);								///<FileCount�����[�h

	return	file_cnt;
}

//============================================================================================
/**
 * �A�[�J�C�u�t�@�C���f�[�^�̃T�C�Y���擾
 *
 *	ArchiveDataLoad���g�p���鎞�A�m�ۂ��郁�����T�C�Y���擾����̂Ɏg�p���܂�
 *
 * @param[in]	arcID		�ǂݍ��ރA�[�J�C�u�t�@�C���̎�ރC���f�b�N�X�i���o�[�iarc_tool.h�ɋL�q�j
 * @param[in]	datID		�ǂݍ��ރf�[�^�̃A�[�J�C�u�t�@�C����̃C���f�b�N�X�i���o�[
 */
//============================================================================================
u32		ArchiveDataSizeGet(int arcID,int datID)
{
	FSFile		p_file;
	u32			size=0;
	u32			fat_top=0;
	u32			fnt_top=0;
	u32			img_top=0;
	u32			top=0;
	u32			bottom=0;
	void		*data;
	u16			file_cnt=0;

	FS_InitFile(&p_file);
	FS_OpenFile(&p_file,ArchiveFileTable[arcID]);
	FS_SeekFile(&p_file,ARC_HEAD_SIZE_POS,FS_SEEK_SET);				///<�A�[�J�C�u�w�b�_�̃T�C�Y�i�[�ʒu�Ɉړ�
	FS_ReadFile(&p_file,&size,2);									///<�A�[�J�C�u�w�b�_�T�C�Y�����[�h
	fat_top=size;
	FS_SeekFile(&p_file,fat_top+SIZE_OFFSET,FS_SEEK_SET);			///<FAT�̃T�C�Y�i�[�ʒu�Ɉړ�
	FS_ReadFile(&p_file,&size,4);									///<FAT�T�C�Y�����[�h
	FS_ReadFile(&p_file,&file_cnt,2);								///<FileCount�����[�h
	GF_ASSERT_MSG(file_cnt>datID,"ServerArchiveDataLoadIndex:FileCnt<Index");
	fnt_top=fat_top+size;
	FS_SeekFile(&p_file,fnt_top+SIZE_OFFSET,FS_SEEK_SET);			///<FNT�̃T�C�Y�i�[�ʒu�Ɉړ�
	FS_ReadFile(&p_file,&size,4);									///<FNT�T�C�Y�����[�h
	img_top=fnt_top+size;
	
	FS_SeekFile(&p_file,fat_top+FAT_HEAD_SIZE+datID*8,FS_SEEK_SET);	///<���o������FAT�e�[�u���Ɉړ�
	FS_ReadFile(&p_file,&top,4);									///<FAT�e�[�u��top�����[�h
	FS_ReadFile(&p_file,&bottom,4);									///<FAT�e�[�u��bottom�����[�h

	FS_SeekFile(&p_file,img_top+IMG_HEAD_SIZE+top,FS_SEEK_SET);		///<���o������IMG�̐擪�Ɉړ�
	size=bottom-top;
	GF_ASSERT_MSG(size!=0,"ServerArchiveDataLoadIndex:ReadDataSize=0!");

	return	size;
}




//--------------------------------------------------------
/**
 * �A�[�J�C�u�t�@�C���̃n���h���Ǘ��\����
 */
//--------------------------------------------------------
struct _ARCHANDLE{
	FSFile  file;
	u32     fat_top;
	u32     img_top;
	u16		file_cnt;
};


//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�̃t�@�C���n���h���I�[�v��
 *
 * @param   arcId		�A�[�J�C�u�f�[�^�C���f�b�N�X
 * @param   heapId		�Ǘ��p�q�[�v�h�c
 *
 * @retval  ARCHANDLE	�I�[�v�����ꂽ�n���h���̃|�C���^�i���s�Ȃ�NULL�j
 */
//------------------------------------------------------------------
ARCHANDLE* ArchiveDataHandleOpen( u32 arcId, u32 heapId )
{
	ARCHANDLE* handle = sys_AllocMemory( heapId, sizeof(ARCHANDLE) );
	if( handle )
	{
		u32 fnt_top, tmp;

		// �Q�o�C�g��ǂݍ��񂾎��ɃS�~������Ȃ��悤�ɂ��Ă���
		handle->fat_top = 0;

		FS_InitFile( &(handle->file) );
		FS_OpenFile( &(handle->file), ArchiveFileTable[arcId] );
		FS_SeekFile( &(handle->file), ARC_HEAD_SIZE_POS, FS_SEEK_SET );
		FS_ReadFile( &(handle->file), &(handle->fat_top), 2 );
		FS_SeekFile( &(handle->file), handle->fat_top+SIZE_OFFSET, FS_SEEK_SET );
		FS_ReadFile( &(handle->file), &tmp, 4 );
		FS_ReadFile( &(handle->file), &(handle->file_cnt), 2 );
		fnt_top = handle->fat_top + tmp;
		FS_SeekFile( &(handle->file), fnt_top+SIZE_OFFSET, FS_SEEK_SET );
		FS_ReadFile( &(handle->file), &tmp, 4 );
		handle->img_top = fnt_top + tmp;

	}
	return handle;
}

//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�̃n���h���N���[�Y
 *
 * @param   handle			�n���h���|�C���^
 *
 */
//------------------------------------------------------------------
void ArchiveDataHandleClose( ARCHANDLE* handle )
{
	FS_CloseFile( &(handle->file) );
	sys_FreeMemoryEz( handle );
}

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
void* ArchiveDataLoadAllocByHandle( ARCHANDLE* handle, u32 datId, u32 heapID )
{
	u32 top, bottom;
	void* buf;

	GF_ASSERT_MSG(handle->file_cnt>datId, "DatCount=%d, DatID=%d", handle->file_cnt, datId);

	FS_SeekFile( &(handle->file), handle->fat_top+FAT_HEAD_SIZE+datId*8, FS_SEEK_SET );
	FS_ReadFile( &(handle->file), &top, 4 );
	FS_ReadFile( &(handle->file), &bottom, 4 );
	FS_SeekFile( &(handle->file), handle->img_top+IMG_HEAD_SIZE+top, FS_SEEK_SET );

	buf = sys_AllocMemory(heapID, bottom-top);
	if( buf )
	{
		FS_ReadFile( &(handle->file), buf, bottom-top );
	}

	return buf;
}

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
void ArchiveDataLoadByHandle( ARCHANDLE* handle, u32 datId, void* buffer )
{
	u32 top, bottom;
	
	GF_ASSERT_MSG(handle->file_cnt>datId, "DatCount=%d, DatID=%d", handle->file_cnt, datId);
	
	FS_SeekFile( &(handle->file), handle->fat_top+FAT_HEAD_SIZE+datId*8, FS_SEEK_SET );
	FS_ReadFile( &(handle->file), &top, 4 );
	FS_ReadFile( &(handle->file), &bottom, 4 );
	FS_SeekFile( &(handle->file), handle->img_top+IMG_HEAD_SIZE+top, FS_SEEK_SET );
	
	FS_ReadFile( &(handle->file), buffer, bottom-top );
}

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
u32 ArchiveDataSizeGetByHandle( ARCHANDLE* handle, u32 datId )
{
	u32 top, bottom;
	
	GF_ASSERT_MSG(handle->file_cnt>datId, "DatCount=%d, DatID=%d", handle->file_cnt, datId);
	
	FS_SeekFile( &(handle->file), handle->fat_top+FAT_HEAD_SIZE+datId*8, FS_SEEK_SET );
	FS_ReadFile( &(handle->file), &top, 4 );
	FS_ReadFile( &(handle->file), &bottom, 4 );
	
	return( bottom-top );
}

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
void ArchiveDataLoadOfsByHandle( ARCHANDLE* handle, u32 datId, u32 ofs, u32 size, void* buffer )
{
	u32 top;

	GF_ASSERT_MSG(handle->file_cnt>datId, "DatCount=%d, DatID=%d", handle->file_cnt, datId);

	FS_SeekFile( &(handle->file), handle->fat_top+FAT_HEAD_SIZE+datId*8, FS_SEEK_SET );
	FS_ReadFile( &(handle->file), &top, 4 );
	FS_SeekFile( &(handle->file), handle->img_top+IMG_HEAD_SIZE+top+ofs, FS_SEEK_SET );

	FS_ReadFile( &(handle->file), buffer, size );
}

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
void ArchiveDataLoadImgofsByHandle( ARCHANDLE* handle, u32 datId, u32* offset )
{
	u32 top;

	GF_ASSERT_MSG(handle->file_cnt>datId, "DatCount=%d, DatID=%d", handle->file_cnt, datId);

	FS_SeekFile( &(handle->file), handle->fat_top+FAT_HEAD_SIZE+datId*8, FS_SEEK_SET );
	FS_ReadFile( &(handle->file), &top, 4 );
	
	*offset = handle->img_top+IMG_HEAD_SIZE+top;
}

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
void ArchiveDataLoadByHandleContinue( ARCHANDLE* handle, u32 size, void* buffer )
{
	FS_ReadFile( &(handle->file), buffer, size );
}

//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�n���h������ăt�@�C���V�[�N
 *
 * @param   handle		�n���h���|�C���^
 * @param   size
 *
 */
//------------------------------------------------------------------
void ArchiveDataSeekByHandle( ARCHANDLE* handle, u32 size )
{
	FS_SeekFile( &(handle->file), size, FS_SEEK_SET );
}

//============================================================================================
/**
 * �A�[�J�C�u�t�@�C���f�[�^�̃t�@�C�������擾(�n���h���g�p)
 *
 * @param	handle			�n���h���|�C���^
 * @retval	u16				�t�@�C����	
 */
//============================================================================================
u16		ArchiveDataFileCntGetByHandle(ARCHANDLE* handle)
{
	return	handle->file_cnt;
}
