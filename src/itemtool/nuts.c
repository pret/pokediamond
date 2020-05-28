//============================================================================================
/**
 * @file	nuts.c
 * @brief	�؂̎��f�[�^����
 * @author	Hiroyuki Nakamura
 * @date	06.01.27
 */
//============================================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "system/msgdata.h"
#include "msgdata\msg.naix"
#include "msgdata\msg_nuts_name.h"
#include "msgdata\msg_nuts_info.h"

#define	NUTS_H_GLOBAL
#include "itemtool/nuts.h"
#include "nuts_data.naix"


//============================================================================================
//	�萔��`
//============================================================================================
// �؂̎��f�[�^
struct _NUTS_DATA {
	u16 size;				// �傫��
	u8	hardness;			// ����
	u8	magnification;		// ���̔{��

	u8	speed;				// ����x
	u8	absorption;			// ���̋z����
	u8	karai;				// �h��
	u8	sibui;				// �a��

	u8	amai;				// �Â�
	u8	nigai;				// �ꂳ
	u8	suppai;				// �_���ς�
	u8	umai;				// �|��
};


//--------------------------------------------------------------------------------------------
/**
 * �؂̎��f�[�^�̃n���h���擾
 *
 * @param	id		�؂̎��ԍ�
 * @param	heap	�q�[�vID
 *
 * @return	�f�[�^�n���h��
 */
//--------------------------------------------------------------------------------------------
ARCHANDLE * Nuts_DataHandleGet( u32 heap )
{
	return ArchiveDataHandleOpen( ARC_NUTSDATA, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * �؂̎��f�[�^���[�h�i�n���h���g�p�j
 *
 * @param	handle	�f�[�^�n���h��
 * @param	id		�؂̎��ԍ�
 * @param	heap	�q�[�vID
 *
 * @return	�؂̎��f�[�^
 */
//--------------------------------------------------------------------------------------------
NUTSDATA * Nuts_DataLoadHandle( ARCHANDLE * handle, u32 id, u32 heap )
{
	return ArchiveDataLoadAllocByHandle( handle, NARC_nuts_data_nuts001_dat+id, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * �؂̎��f�[�^�n���h�������
 *
 * @param	handle	�f�[�^�n���h��
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Nuts_DataHandleClose( ARCHANDLE * handle )
{
	ArchiveDataHandleClose( handle );
}

//--------------------------------------------------------------------------------------------
/**
 * �؂̎��f�[�^���[�h
 *
 * @param	id		�؂̎��ԍ�
 * @param	heap	�q�[�vID
 *
 * @return	�؂̎��f�[�^
 */
//--------------------------------------------------------------------------------------------
NUTSDATA * Nuts_DataLoad( u32 id, u32 heap )
{
	return ArchiveDataLoadMalloc( ARC_NUTSDATA, NARC_nuts_data_nuts001_dat+id, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * �؂̎��f�[�^���[�h�i�A�C�e���ԍ�����j
 *
 * @param	item	�A�C�e���ԍ�
 * @param	heap	�q�[�vID
 *
 * @return	�؂̎��f�[�^
 */
//--------------------------------------------------------------------------------------------
NUTSDATA * Nuts_DataLoadItem( u32 item, u32 heap )
{
	return Nuts_DataLoad( item-NUTS_START_ITEMNUM, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * �؂̎��p�����[�^�擾
 *
 * @param	dat		�؂̎��f�[�^
 * @param	prm		�擾�p�����[�^ID
 *
 * @return	�擾�p�����[�^
 */
//--------------------------------------------------------------------------------------------
u32 Nuts_ParamGet( NUTSDATA * dat, u32 prm )
{
	switch( prm ){
	case NUTS_PRM_SIZE:				// �傫��
		return dat->size;
	case NUTS_PRM_HARDNESS:			// ����
		return dat->hardness;
	case NUTS_PRM_MAGNIFICATION:	// ���̔{��
		return dat->magnification;
	case NUTS_PRM_SPEED:			// ����x
		return dat->speed;
	case NUTS_PRM_ABSORPTION:		// ���̋z����
		return dat->absorption;
	case NUTS_PRM_KARAI:			// �h��
		return dat->karai;
	case NUTS_PRM_SIBUI:			// �a��
		return dat->sibui;
	case NUTS_PRM_AMAI:				// �Â�
		return dat->amai;
	case NUTS_PRM_NIGAI:			// �ꂳ
		return dat->nigai;
	case NUTS_PRM_SUPPAI:			// �_���ς�
		return dat->suppai;
	case NUTS_PRM_UMAI:				// �|��
		return dat->umai;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �؂̎����擾
 *
 * @param   buf			�i�[��
 * @param	id			�؂̎��ԍ�
 * @param   heap		�q�[�vID�i�e���|�����Ƃ��Ďg�p�j
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void NutsNameGet( STRBUF * buf, u16 id, u32 heap )
{
	MSGDATA_MANAGER * man;
	
	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_nuts_name_dat, heap );
	MSGMAN_GetString( man, id, buf );
	MSGMAN_Delete( man );
}

//--------------------------------------------------------------------------------------------
/**
 * �؂̎����擾�i�̈�m�ہj
 *
 * @param	id			�؂̎��ԍ�
 * @param   heap		�q�[�vID�i�e���|�����Ƃ��Ďg�p�j
 *
 * @return	�擾�����؂̎����̃o�b�t�@
 *
 * @li	����͊e����
 */
//--------------------------------------------------------------------------------------------
STRBUF * NutsNameGetAlloc( u16 id, u32 heap )
{
	MSGDATA_MANAGER * man;
	STRBUF * str;
	
	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_nuts_name_dat, heap );
	str = MSGMAN_AllocString( man, id );
	MSGMAN_Delete( man );
	return str;
}

//--------------------------------------------------------------------------------------------
/**
 * �؂̎����擾�i�A�C�e���ԍ�����j
 *
 * @param   buf			�i�[��
 * @param	item		�A�C�e���ԍ�
 * @param   heap		�q�[�vID�i�e���|�����Ƃ��Ďg�p�j
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void NutsNameGet_Item( STRBUF * buf, u16 item, u32 heap )
{
	NutsNameGet( buf, item-NUTS_START_ITEMNUM, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * �؂̎����擾�i�A�C�e���ԍ�����j�i�̈�m�ہj
 *
 * @param	item		�A�C�e���ԍ�
 * @param   heap		�q�[�vID�i�e���|�����Ƃ��Ďg�p�j
 *
 * @return	�擾�����؂̎����̃o�b�t�@
 *
 * @li	����͊e����
 */
//--------------------------------------------------------------------------------------------
STRBUF * NutsNameGetAlloc_Item( u16 item, u32 heap )
{
	return NutsNameGetAlloc( item-NUTS_START_ITEMNUM, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * �����擾
 *
 * @param   buf			�i�[��
 * @param	id			�؂̎��ԍ�
 * @param	heap		�q�[�vID�i�e���|�����Ƃ��Ďg�p�j
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void NutsInfoGet( STRBUF * buf, u16 id, u16 heap )
{
	MSGDATA_MANAGER * man;
	
	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_nuts_info_dat, heap );
	MSGMAN_GetString( man, id, buf );
	MSGMAN_Delete( man );
}

//--------------------------------------------------------------------------------------------
/**
 * �����擾�i�̈�m�ہj
 *
 * @param	id			�؂̎��ԍ�
 * @param	heap		�q�[�vID�i�e���|�����Ƃ��Ďg�p�j
 *
 * @return	�擾�����؂̎����̃o�b�t�@
 *
 * @li	����͊e����
 */
//--------------------------------------------------------------------------------------------
STRBUF * NutsInfoGetAlloc( u16 id, u16 heap )
{
	MSGDATA_MANAGER * man;
	STRBUF * str;
	
	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_nuts_info_dat, heap );
	str = MSGMAN_AllocString( man, id );
	MSGMAN_Delete( man );
	return str;
}

//--------------------------------------------------------------------------------------------
/**
 * �����擾�i�A�C�e���ԍ�����j
 *
 * @param   buf			�i�[��
 * @param	item		�A�C�e���ԍ�
 * @param	heap		�q�[�vID�i�e���|�����Ƃ��Ďg�p�j
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void NutsInfoGet_Item( STRBUF * buf, u16 item, u16 heap )
{
	NutsInfoGet( buf, item-NUTS_START_ITEMNUM, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * �����擾�i�A�C�e���ԍ�����j�i�̈�m�ہj
 *
 * @param	item		�A�C�e���ԍ�
 * @param	heap		�q�[�vID�i�e���|�����Ƃ��Ďg�p�j
 *
 * @return	�擾�����؂̎����̃o�b�t�@
 *
 * @li	����͊e����
 */
//--------------------------------------------------------------------------------------------
STRBUF * NutsInfoGetAlloc_Item( u16 item, u16 heap )
{
	return NutsInfoGetAlloc( item-NUTS_START_ITEMNUM, heap );
}
