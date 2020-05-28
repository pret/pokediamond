//============================================================================================
/**
 * @file	msgdata.c
 * @brief	�e�탁�b�Z�[�W�f�[�^��舵��
 * @author	taya
 * @date	2005.09.26
 */
//============================================================================================
#include "common.h"
#include "gflib\strbuf_family.h"
#include "system\arc_tool.h"
#include "system\pm_str.h"
#include "system\get_text.h"
#include "system\msgdata.h"

#include "msgdata\msg.naix"
#include "msgdata\msg_monsname.h"
#include "msgdata\msg_wazaname.h"
#include "msgdata\msg_typename.h"
#include "msgdata\msg_tokusei.h"
#include "msgdata\msg_status.h"
#include "msgdata\msg_condition.h"
#include "msgdata\msg_taste.h"
#include "msgdata\msg_itemname.h"
#include "msgdata\msg_iteminfo.h"


// ����define��L���ɂ���ƁA�Í������b�Z�[�W�Ή�
#define  MSGDATA_CODED	


/*------------------------------------------------------------*/
/** ������p�����[�^                                          */
/*------------------------------------------------------------*/
typedef struct {
	u32  offset;	///< �t�@�C���擪����̃o�C�g�I�t�Z�b�g
	u32  len;		///< �������iEOM���܂ށj
}MSG_PARAM_BLOCK;

/*------------------------------------------------------------*/
/** ������f�[�^�w�b�_                                        */
/*------------------------------------------------------------*/
struct _MSGDATA_HEADER{
	#ifdef MSGDATA_CODED
	u16					numMsgs;
	u16					randValue;
	#else
	union {
		u32				numMsgs;
		u32				randValue;
	};
	#endif
	MSG_PARAM_BLOCK		params[];
};


//==============================================================
// Prototype
//==============================================================
static void StrSet( STRCODE* dst, const STRCODE* src, const MSG_PARAM_BLOCK* param );


//------------------------------------------------------------------
/**
 * ���b�Z�[�W�f�[�^���A�[�J�C�u���烍�[�h����
 *
 * @param   arcID		�A�[�J�C�u�t�@�C���h�c
 * @param   datID		�A�[�J�C�u�t�@�C�����̃��b�Z�[�W�f�[�^�h�c
 * @param   heapID		�q�[�v�h�c
 *
 * @retval  MSGDATA_HEADER*		���b�Z�[�W�f�[�^�|�C���^
 */
//------------------------------------------------------------------
MSGDATA_HEADER* MSGDAT_Load( u32 arcID, u32 datID, u32 heapID )
{
	return ArchiveDataLoadMalloc( arcID, datID, heapID );
}
//------------------------------------------------------------------
/**
 * ���[�h�������b�Z�[�W�f�[�^���A�����[�h����
 *
 * @param   msgdat		���b�Z�[�W�f�[�^�|�C���^
 *
 */
//------------------------------------------------------------------
void MSGDAT_Unload( MSGDATA_HEADER* msgdat )
{
	sys_FreeMemoryEz( msgdat );
}




//------------------------------------------------------------------
/**
 * �����񂲂Ƃ̃p�����[�^�\���̃I�t�Z�b�g���v�Z
 *
 * @param   strID		
 *
 * @retval  inline int		
 */
//------------------------------------------------------------------
static inline int CalcParamBlockOfs( u32 strID )
{
	return sizeof(MSGDATA_HEADER) + sizeof(MSG_PARAM_BLOCK) * strID;
}



//===============================================================================================
//  �Í������ꂽ�f�[�^�̕�������
//===============================================================================================

//------------------------------------------------------------------
/**
 * �Í������ꂽ������p�����[�^�\���̂𕜍�����
 *
 * @param   param		�p�����[�^�\���̂ւ̃|�C���^
 * @param   strID		������ID
 * @param   rand		�Í��L�[����
 */
//------------------------------------------------------------------
static inline void DecodeParam( MSG_PARAM_BLOCK* param, u32 strID, u32 rand )
{
#ifdef MSGDATA_CODED
	rand = (rand * 765 * (strID+1)) & 0xffff;
	rand |= (rand << 16);

	param->offset ^= rand;
	param->len ^= rand;
#endif
}
//------------------------------------------------------------------
/**
 * �Í������ꂽ������𕜍�����
 *
 * @param   str			������|�C���^
 * @param   len			������
 * @param   strID		������ID
 * @param   rand		�Í��L�[����
 *
 */
//------------------------------------------------------------------
static inline void DecodeStr( STRCODE* str, u32 len, u32 strID, u16 rand )
{
#ifdef MSGDATA_CODED
	rand = (strID + 1) * 596947;
	while(len--)
	{
		*str ^= rand;
		str++;
		rand += 18749;
	}
#endif
}








//------------------------------------------------------------------
/**
 * ���[�h�������b�Z�[�W�f�[�^���當������R�s�[
 *
 * @param   msgdat		���b�Z�[�W�f�[�^�|�C���^
 * @param   strID		������h�c
 * @param   dst			������R�s�[��o�b�t�@
 *
 */
//------------------------------------------------------------------
void MSGDAT_Get( const MSGDATA_HEADER* msgdat, u32 strID, STRCODE* dst )
{
	if( strID < msgdat->numMsgs )
	{
		MSG_PARAM_BLOCK param;
		const STRCODE* str;

		param = msgdat->params[strID];
		DecodeParam( &param, strID, msgdat->randValue );
		str = (STRCODE*)(((u8*)msgdat) + param.offset);
		StrSet( dst, str, &param );
		DecodeStr( dst, param.len, strID, msgdat->randValue );
	}
	else
	{
		GF_ASSERT(0);
	}
}
//------------------------------------------------------------------
/**
 * ���[�h�������b�Z�[�W�f�[�^����w�蕶����T�C�Y���̃��������m�ہ��R�s�[
 *
 * @param   msgdat		���b�Z�[�W�f�[�^�|�C���^
 * @param   strID		������ID
 * @param   heapID		�������m�ۗp�̃q�[�vID
 *
 * @retval  �����񂪃R�s�[���ꂽ�������u���b�N�i���s����NULL�j
 *
 */
//------------------------------------------------------------------
STRCODE* MSGDAT_GetAlloc( const MSGDATA_HEADER* msgdat, u32 strID, u32 heapID )
{
	if( strID < msgdat->numMsgs )
	{
		MSG_PARAM_BLOCK param;
		const STRCODE* src;
		STRCODE *dst;

		param = msgdat->params[strID];
		DecodeParam( &param, strID, msgdat->randValue );
		src = (STRCODE*)(((u8*)msgdat) + param.offset);
		dst = sys_AllocMemory( heapID, param.len*sizeof(STRCODE) );
		if( dst )
		{
			StrSet( dst, src, &param );
			DecodeStr( dst, param.len, strID, msgdat->randValue );
		}
		return dst;
	}

	GF_ASSERT(0);
	return NULL;
}
//------------------------------------------------------------------
/**
 * �w�蕶����݂̂����[�h���w��o�b�t�@�ɃR�s�[
 *
 * @param   arcID		�A�[�J�C�u�t�@�C���h�c
 * @param   datID		�A�[�J�C�u�t�@�C�����̃��b�Z�[�W�f�[�^�h�c
 * @param   msgID		���b�Z�[�W�f�[�^���̕�����h�c
 * @param   heapID		�ꎞ�������m�ۗp�̃q�[�v�h�c
 * @param   dst			������R�s�[��o�b�t�@
 *
 */
//------------------------------------------------------------------
void MSGDAT_GetDirect( u32 arcID, u32 datID, u32 strID, u32 heapID, STRCODE* dst )
{
	ARCHANDLE* arc = ArchiveDataHandleOpen(arcID, heapID);

	if( arc )
	{
		MSGDATA_HEADER  header;
		MSG_PARAM_BLOCK  param;
		STRCODE*  str;
		u32 size;

		ArchiveDataLoadOfsByHandle( arc, datID, 0, sizeof(MSGDATA_HEADER), &header);
		ArchiveDataLoadOfsByHandle( arc, datID, CalcParamBlockOfs(strID), sizeof(MSG_PARAM_BLOCK), &param );
		DecodeParam( &param, strID, header.randValue );

		size = param.len * sizeof(STRCODE);
		ArchiveDataLoadOfsByHandle( arc, datID, param.offset, size, dst );
		DecodeStr( dst, param.len, strID, header.randValue );

		ArchiveDataHandleClose( arc );
	}
}
//------------------------------------------------------------------
/**
 * �w�蕶����݂̂����[�h��A�����ŃA���P�[�g�����������ɃR�s�[���ĕԂ�
 *
 * @param   arcID		�A�[�J�C�u�t�@�C���h�c
 * @param   datID		�A�[�J�C�u�t�@�C�����̃��b�Z�[�W�f�[�^�h�c
 * @param   msgID		���b�Z�[�W�f�[�^���̕�����h�c
 * @param   heapID		�ꎞ�������m�ۗp�̃q�[�v�h�c
 *
 * @retval  STRCODE*	�����񂪃R�s�[���ꂽ�������u���b�N�i���s����NULL�j
 */
//------------------------------------------------------------------
STRCODE* MSGDAT_GetDirectAlloc( u32 arcID, u32 datID, u32 strID, u32 heapID )
{
	ARCHANDLE* arc = ArchiveDataHandleOpen( arcID, heapID );

	if( arc )
	{
		MSGDATA_HEADER   header;
		MSG_PARAM_BLOCK  param;
		STRCODE*  str;
		u32 size;

		ArchiveDataLoadOfsByHandle( arc, datID, 0, sizeof(MSGDATA_HEADER), &header);
		ArchiveDataLoadOfsByHandle( arc, datID, CalcParamBlockOfs(strID), sizeof(MSG_PARAM_BLOCK), &param );
		DecodeParam( &param, strID, header.randValue );

		size = param.len * sizeof(STRCODE);
		str = sys_AllocMemory( heapID, size );
		if( str != NULL )
		{
			ArchiveDataLoadOfsByHandle( arc, datID, param.offset, size, str );
			DecodeStr( str, param.len, strID, header.randValue );
		}
		ArchiveDataHandleClose( arc );
		return str;
	}

	return NULL;
}
//------------------------------------------------------------------
/**
 * �R���o�[�g����Ă��镶������w��̃��[�J���o�b�t�@�ɃR�s�[
 *
 * @param   dst			�R�s�[��o�b�t�@
 * @param   src			�R�s�[��������
 * @param   param		�R�s�[��������̃p�����[�^
 *
 */
//------------------------------------------------------------------
static void StrSet( STRCODE* dst, const STRCODE* src, const MSG_PARAM_BLOCK* param )
{
	MI_CpuCopy16( src, dst, param->len*sizeof(STRCODE) );
}


//------------------------------------------------------------------
/**
 * ������o�b�t�@�^�I�u�W�F�N�g�ɁA�w�蕶������R�s�[
 *
 * @param   msgdat		���b�Z�[�W�f�[�^�|�C���^
 * @param   strID		������ID
 * @param   dst			������o�b�t�@�^
 *
 */
//------------------------------------------------------------------
void MSGDAT_GetStr( const MSGDATA_HEADER* msgdat, u32 strID, STRBUF* dst )
{
	if( strID < msgdat->numMsgs )
	{
		MSG_PARAM_BLOCK param;
		STRCODE* str;
		u32 size;

		param = msgdat->params[strID];
		DecodeParam( &param, strID, msgdat->randValue );

		size = param.len * sizeof(STRCODE);
		str = sys_AllocMemoryLo( HEAPID_BASE_SYSTEM, size );
		if( str )
		{
			MI_CpuCopy16( (((u8*)msgdat) + param.offset), str, size );
			DecodeStr( str, param.len, strID, msgdat->randValue );
			STRBUF_SetStringCodeOrderLength( dst, str, param.len );
			sys_FreeMemoryEz( str );
		}
	}
	else
	{
		GF_ASSERT_MSG(0, "strID:%d", strID);
		STRBUF_Clear( dst );
	}
}
//------------------------------------------------------------------
/**
 * ���[�h�������b�Z�[�W�f�[�^����w�蕶����T�C�Y���̃��������m�ہ��R�s�[
 *
 * @param   msgdat		���b�Z�[�W�f�[�^�|�C���^
 * @param   strID		������ID
 * @param   heapID		�������m�ۗp�̃q�[�vID
 *
 * @retval  �����񂪃R�s�[���ꂽ������o�b�t�@�^�I�u�W�F�N�g�ւ̃|�C���^
 *
 */
//------------------------------------------------------------------
STRBUF* MSGDAT_GetStrAlloc( const MSGDATA_HEADER* msgdat, u32 strID, u32 heapID )
{
	if( strID < msgdat->numMsgs )
	{
		MSG_PARAM_BLOCK param;
		STRCODE* str;
		u32 size;

		param = msgdat->params[strID];
		DecodeParam( &param, strID, msgdat->randValue );
		size = param.len * sizeof(STRCODE);
		str = sys_AllocMemoryLo( heapID, size );
		if( str )
		{
			STRBUF *dst;

			MI_CpuCopy16( (((u8*)msgdat) + param.offset), str, size );
			DecodeStr( str, param.len, strID, msgdat->randValue );

			dst = STRBUF_Create( param.len, heapID );
			if( dst )
			{
				STRBUF_SetStringCodeOrderLength( dst, str, param.len );
			}
			sys_FreeMemoryEz( str );
			return dst;
		}
		return NULL;
	}
	else
	{
		// ���݂��Ȃ��C���f�b�N�X�̗v����������󕶎����Ԃ��Ă���
		GF_ASSERT_MSG(0, "strID:%d", strID);
		return STRBUF_Create( 4, heapID );
	}
}
//------------------------------------------------------------------
/**
 * �w�蕶����݂̂����[�h���w��o�b�t�@�ɃR�s�[�i�A�[�J�C�uID�w��j
 *
 * @param   arcID		�A�[�J�C�u�t�@�C���h�c
 * @param   datID		�A�[�J�C�u�t�@�C�����̃��b�Z�[�W�f�[�^�h�c
 * @param   msgID		���b�Z�[�W�f�[�^���̕�����h�c
 * @param   heapID		�ꎞ�������m�ۗp�̃q�[�v�h�c
 * @param   dst			������R�s�[��o�b�t�@
 *
 */
//------------------------------------------------------------------
void MSGDAT_GetStrDirect( u32 arcID, u32 datID, u32 strID, u32 heapID, STRBUF* dst )
{
	ARCHANDLE*  arc;

	arc = ArchiveDataHandleOpen(arcID, heapID);
	if( arc )
	{
		MSGDAT_GetStrDirectByHandle( arc, datID, strID, heapID, dst );
		ArchiveDataHandleClose( arc );
	}
}

//------------------------------------------------------------------
/**
 * �w�蕶����݂̂����[�h���w��o�b�t�@�ɃR�s�[�i�A�[�J�C�u�n���h���g�p�j
 *
 * @param   arcHandle	�A�[�J�C�u�n���h��
 * @param   datID		�A�[�J�C�u�t�@�C�����̃��b�Z�[�W�f�[�^�h�c
 * @param   msgID		���b�Z�[�W�f�[�^���̕�����h�c
 * @param   heapID		�ꎞ�������m�ۗp�̃q�[�v�h�c
 * @param   dst			������R�s�[��o�b�t�@
 *
 */
//------------------------------------------------------------------
void MSGDAT_GetStrDirectByHandle( ARCHANDLE* arcHandle, u32 datID, u32 strID, u32 heapID, STRBUF* dst )
{
	MSGDATA_HEADER  header;
	MSG_PARAM_BLOCK  param;
	STRCODE*  str;
	u32 size;

	ArchiveDataLoadOfsByHandle( arcHandle, datID, 0, sizeof(MSGDATA_HEADER), &header );

	if( strID < header.numMsgs )
	{
		ArchiveDataLoadOfsByHandle( arcHandle, datID, CalcParamBlockOfs(strID), sizeof(MSG_PARAM_BLOCK), &param );
		DecodeParam( &param, strID, header.randValue );

		size = param.len * sizeof(STRCODE);
		str = sys_AllocMemoryLo( heapID, size );
		if( str )
		{
			ArchiveDataLoadOfsByHandle( arcHandle, datID, param.offset, size, str );
			DecodeStr( str, param.len, strID, header.randValue );
			STRBUF_SetStringCodeOrderLength( dst, str, param.len );
			sys_FreeMemoryEz( str );
		}
	}
	else
	{
		GF_ASSERT_MSG(0, "datID:%d strID:%d", datID, strID);
		STRBUF_Clear( dst );
	}
}


//------------------------------------------------------------------
/**
 * �w�蕶����݂̂����[�h��A�����ŃA���P�[�g�����������ɃR�s�[���ĕԂ�
 *�i�A�[�J�C�uID�w��j
 *
 * @param   arcID		�A�[�J�C�u�t�@�C���h�c
 * @param   datID		�A�[�J�C�u�t�@�C�����̃��b�Z�[�W�f�[�^�h�c
 * @param   msgID		���b�Z�[�W�f�[�^���̕�����h�c
 * @param   heapID		�ꎞ�������m�ۗp�̃q�[�v�h�c
 *
 * @retval  �����񂪃R�s�[���ꂽ������o�b�t�@�^�I�u�W�F�N�g�ւ̃|�C���^
 */
//------------------------------------------------------------------
STRBUF* MSGDAT_GetStrDirectAlloc( u32 arcID, u32 datID, u32 strID, u32 heapID )
{
	ARCHANDLE*  arc;
	STRBUF* ret;

	arc = ArchiveDataHandleOpen(arcID, heapID);
	if( arc )
	{
		ret = MSGDAT_GetStrDirectAllocByHandle( arc, datID, strID, heapID );
		ArchiveDataHandleClose( arc );
	}
	else
	{
		ret = STRBUF_Create( 4, heapID );
	}
	return ret;
}

//------------------------------------------------------------------
/**
 * �w�蕶����݂̂����[�h��A�����ŃA���P�[�g�����������ɃR�s�[���ĕԂ�
 *�i�A�[�J�C�u�n���h���g�p�j
 *
 * @param   arcHandle	�A�[�J�C�u�n���h��
 * @param   datID		�A�[�J�C�u�t�@�C�����̃��b�Z�[�W�f�[�^�h�c
 * @param   msgID		���b�Z�[�W�f�[�^���̕�����h�c
 * @param   heapID		�ꎞ�������m�ۗp�̃q�[�v�h�c
 *
 * @retval  �����񂪃R�s�[���ꂽ������o�b�t�@�^�I�u�W�F�N�g�ւ̃|�C���^
 */
//------------------------------------------------------------------
STRBUF* MSGDAT_GetStrDirectAllocByHandle( ARCHANDLE* arcHandle, u32 datID, u32 strID, u32 heapID )
{
	MSGDATA_HEADER   header;

	ArchiveDataLoadOfsByHandle( arcHandle, datID, 0, sizeof(MSGDATA_HEADER), &header );

	if( strID < header.numMsgs )
	{
		MSG_PARAM_BLOCK  param;
		STRBUF*   dst;

		ArchiveDataLoadOfsByHandle( arcHandle, datID, CalcParamBlockOfs(strID), sizeof(MSG_PARAM_BLOCK), &param );
		DecodeParam( &param, strID, header.randValue );

		dst = STRBUF_Create( param.len, heapID );
		if( dst )
		{
			STRCODE*  str;
			u32 size;

			size = param.len * sizeof(STRCODE);
			str = sys_AllocMemoryLo( heapID, size );
			if( str )
			{
				ArchiveDataLoadOfsByHandle( arcHandle, datID, param.offset, size, str );
				DecodeStr( str, param.len, strID, header.randValue );
				STRBUF_SetStringCodeOrderLength( dst, str, param.len );
				sys_FreeMemoryEz( str );
			}
		}
		return dst;
	}
	else
	{
		// ���݂��Ȃ��C���f�b�N�X�̗v����������󕶎����Ԃ��Ă���
		GF_ASSERT_MSG(0, "datID:%d strID:%d", datID, strID);
		return STRBUF_Create( 4, heapID );
	}
}


//------------------------------------------------------------------
/**
 * ���[�h�������b�Z�[�W�f�[�^����ɁA�i�[����Ă��郁�b�Z�[�W�̐���Ԃ�
 *
 * @param   msgdat		���b�Z�[�W�f�[�^�|�C���^
 *
 * @retval  u32			���b�Z�[�W��
 */
//------------------------------------------------------------------
u32 MSGDAT_GetMessageCount( const MSGDATA_HEADER* msgdat )
{
	return msgdat->numMsgs;
}
//------------------------------------------------------------------
/**
 * �A�[�J�C�u���f�[�^ID����ɁA�i�[����Ă��郁�b�Z�[�W�̐���Ԃ�
 *
 * @param   arcID		�A�[�J�C�uID
 * @param   datID		�f�[�^ID
 *
 * @retval  u32			���b�Z�[�W��
 */
//------------------------------------------------------------------
u32 MSGDAT_GetMessageCountDirect( u32 arcID, u32 datID )
{
	MSGDATA_HEADER  header;
	ArchiveDataLoadOfs( &header, arcID, datID, 0, sizeof(MSGDATA_HEADER) );
	return header.numMsgs;
}




/*============================================================================================*/
/*                                                                                            */
/*  ���b�Z�[�W�f�[�^�}�l�[�W��                                                                */
/*                                                                                            */
/*============================================================================================*/


//----------------------------------------------------
/**
 *  �}�l�[�W�����[�N�\����
 */
//----------------------------------------------------
struct _MSGDATA_MANAGER {

	u16		type;
	u16		heapID;
	u16		arcID;
	u16		datID;

	union {
		MSGDATA_HEADER*  msgData;
		ARCHANDLE*       arcHandle;
	};
};



//------------------------------------------------------------------
/**
 * ���b�Z�[�W�f�[�^�}�l�[�W���쐬
 *
 * @param   type		�}�l�[�W���^�C�v�w��
 * @param   arcID		���b�Z�[�W�f�[�^�̊܂܂��A�[�J�C�u�h�c
 * @param   datID		���b�Z�[�W�f�[�^�{�̂̃A�[�J�C�u���h�c
 * @param   heapID		�������m�ۗp�q�[�v�h�c
 *
 * @retval  MSGDATA_MANAGER*		�쐬�����}�l�[�W�����[�N�|�C���^
 */
//------------------------------------------------------------------
MSGDATA_MANAGER*  MSGMAN_Create( MSGMAN_TYPE type, u32 arcID, u32 datID, u32 heapID )
{
	// �}�l�[�W���쐬��������擾���}�l�[�W���p���c�̗��ꂪ�v������葽�����Ȃ̂�
	// �}�l�[�W�����[�N�̓������u���b�N�̌������擾����
	MSGDATA_MANAGER* man = sys_AllocMemoryLo( heapID, sizeof(MSGDATA_MANAGER) );
	if( man )
	{
		if( type == MSGMAN_TYPE_NORMAL )
		{
			man->msgData = MSGDAT_Load( arcID, datID, heapID );
			if( man->msgData == NULL )
			{
				sys_FreeMemoryEz( man );
				return NULL;
			}
		}
		else
		{
			man->arcHandle = ArchiveDataHandleOpen(arcID, heapID);
		}
		man->type = type;
		man->arcID = arcID;
		man->datID = datID;
		man->heapID = heapID;
	}
	return man;
}
//------------------------------------------------------------------
/**
 * ���b�Z�[�W�f�[�^�}�l�[�W���̔j��
 *
 * @param   man		�}�l�[�W�����[�N�|�C���^
 *
 */
//------------------------------------------------------------------
void MSGMAN_Delete( MSGDATA_MANAGER* man )
{
	if( man )
	{
		switch( man->type ){
		case MSGMAN_TYPE_NORMAL:
			MSGDAT_Unload( man->msgData );
			break;
		case MSGMAN_TYPE_DIRECT:
			ArchiveDataHandleClose( man->arcHandle );
			break;
		}
		sys_FreeMemoryEz( man );
	}
}
//------------------------------------------------------------------
/**
 * ���b�Z�[�W�f�[�^�}�l�[�W�����g���ĕ�������w��o�b�t�@�ɃR�s�[
 *
 * @param   man			�}�l�[�W�����[�N�|�C���^
 * @param   strID		������h�c
 * @param   dst			�R�s�[��o�b�t�@�|�C���^
 *
 */
//------------------------------------------------------------------
void MSGMAN_GetString( const MSGDATA_MANAGER* man, u32 strID, STRBUF* dst )
{
	switch( man->type ){
	case MSGMAN_TYPE_NORMAL:
		MSGDAT_GetStr( man->msgData, strID, dst );
		break;

	case MSGMAN_TYPE_DIRECT:
		MSGDAT_GetStrDirectByHandle( man->arcHandle, man->datID, strID, man->heapID, dst );
		break;
	}
}
//------------------------------------------------------------------
/**
 * ���b�Z�[�W�f�[�^�}�l�[�W�����g���ĕ�������擾
 *�i������STRBUF���쐬���ĕԂ��B�쐬���ꂽSTRBUF�̔j���͊e���ōs���j
 *
 * @param   man			�}�l�[�W�����[�N�|�C���^
 * @param   strID		������ID
 *
 * @retval  STRBUF*		�R�s�[��o�b�t�@�|�C���^
 */
//------------------------------------------------------------------
STRBUF* MSGMAN_AllocString( const MSGDATA_MANAGER* man, u32 strID )
{
	switch( man->type ){
	case MSGMAN_TYPE_NORMAL:
		return MSGDAT_GetStrAlloc( man->msgData, strID, man->heapID );

	case MSGMAN_TYPE_DIRECT:
		return MSGDAT_GetStrDirectAllocByHandle( man->arcHandle, man->datID, strID, man->heapID );
	}
	return NULL;
}

//------------------------------------------------------------------
/**
 * �i�[����Ă��郁�b�Z�[�W����Ԃ�
 *
 * @param   man		�}�l�[�W�����[�N�|�C���^
 *
 * @retval  u32		���b�Z�[�W��
 */
//------------------------------------------------------------------
u32 MSGMAN_GetMessageCount( const MSGDATA_MANAGER* man )
{
	switch( man->type ){
	case MSGMAN_TYPE_NORMAL:
		return MSGDAT_GetMessageCount( man->msgData );

	case MSGMAN_TYPE_DIRECT:
		return MSGDAT_GetMessageCountDirect( man->arcID, man->datID );
	}
	return 0;
}









//------------------------------------------------------------------
/**
 * �����@���̕����z����g�p���Ă���B����������̂Ŏg��Ȃ��悤�Ɂ@����
 *
 * ���b�Z�[�W�f�[�^�}�l�[�W�����g���ĕ�������w��o�b�t�@�ɃR�s�[
 */
//------------------------------------------------------------------
void MSGMAN_GetStr( const MSGDATA_MANAGER* man, u32 strID, STRCODE* dst )
{
	switch( man->type ){
	case MSGMAN_TYPE_NORMAL:
		MSGDAT_Get( man->msgData, strID, dst );
		break;

	case MSGMAN_TYPE_DIRECT:
		MSGDAT_GetDirect( man->arcID, man->datID, strID, man->heapID, dst );
		break;
	}
}
//------------------------------------------------------------------
/**
 * �����@���̕����z����g�p���Ă���B����������̂Ŏg��Ȃ��悤�Ɂ@����
 *
 * ���b�Z�[�W�f�[�^�}�l�[�W�����g���ĕ�������擾
 */
//------------------------------------------------------------------
STRCODE* MSGMAN_GetStrAlloc( const MSGDATA_MANAGER* man, u32 strID )
{
	switch( man->type ){
	case MSGMAN_TYPE_NORMAL:
		return MSGDAT_GetAlloc( man->msgData, strID, man->heapID );

	case MSGMAN_TYPE_DIRECT:
		return MSGDAT_GetDirectAlloc( man->arcID, man->datID, strID, man->heapID );
	}
	return NULL;
}




/*-------------------------------------------------------------------*/
/** �I�I�����ɂ��̎�̊֐�������ȏ�ǉ����Ȃ��悤�ɂ��肢���܂��I�I */
/*-------------------------------------------------------------------*/

//------------------------------------------------------------------
/**
 * �|�P�������擾
 *
 * @param   monsno		�|�P�����i���o�[
 * @param   heapID		�ꎞ�������m�ۗp�̃q�[�v�h�c
 * @param   dst			������R�s�[��o�b�t�@
 *
 */
//------------------------------------------------------------------
void MSGDAT_MonsNameGet( u32 monsno, u32 heapID, STRCODE* dst )
{
	MSGDATA_MANAGER* man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_monsname_dat, heapID );
	MSGMAN_GetStr( man, MONSNAME_000+monsno, dst );
	MSGMAN_Delete( man );
}

/*-------------------------------------------------------------------*/
/** �I�I�����ɂ��̎�̊֐�������ȏ�ǉ����Ȃ��悤�ɂ��肢���܂��I�I */
/*-------------------------------------------------------------------*/
