//============================================================================================
/**
 * @file	msgdata_util.c
 * @brief	���b�Z�[�W�f�[�^�֘A�֗��֐�
 * @author	taya
 * @date	2005.12.05
 *
 * �|�P�������E���U���E�A�C�e�������A
 * �����̃v���O��������Q�Ƃ���A�Ǘ��҂��B���ȕ�����̎擾��������舵��
 *
 *
 */
//============================================================================================
#include "common.h"
#include "system/msgdata_util.h"
#include "system/buflen.h"

#include "msgdata/msg.naix"



//=================================================================================
// 
//=================================================================================
#define  EXPAND_BUFFER_SIZE		(1024)		/// �ǂ�ȕ�������W�J�ł���ł��낤�T�C�Y


//------------------------------------------------------------------
/**
 * ���b�Z�[�W�f�[�^���^�O�W�J����������o�b�t�@���쐬���ĕԂ��B
 * ���O�Ɍʂ̃^�O�ݒ菈�����s���Ă����K�v������B
 * �쐬���ꂽ������̉�������͊e���ōs���B
 *
 * @param   wordSet		�^�O���ݒ肳�ꂽ�P��Z�b�g���W���[��
 * @param   msgMan		�W�J�O��������Ǘ����Ă��郁�b�Z�[�W�}�l�[�W��
 * @param   strID		�W�J�O�������ID
 * @param   heapID		������o�b�t�@�쐬��̃q�[�vID
 *
 * @retval  STRBUF*		�쐬���ꂽ������o�b�t�@
 */
//------------------------------------------------------------------
STRBUF* MSGDAT_UTIL_AllocExpandString( WORDSET* wordSet, MSGDATA_MANAGER* msgMan, u32 strID, u32 heapID )
{
	STRBUF* retbuf = NULL;
	STRBUF* exbuf;

	exbuf = STRBUF_Create(EXPAND_BUFFER_SIZE, HEAPID_BASE_SYSTEM);
	if(exbuf)
	{
		STRBUF* srcbuf = MSGMAN_AllocString( msgMan, strID );
		if( srcbuf )
		{
			WORDSET_ExpandStr(wordSet, exbuf, srcbuf);
			retbuf = STRBUF_CreateBufferCopy( exbuf, heapID );
			STRBUF_Delete(srcbuf);
		}
		STRBUF_Delete(exbuf);
	}

	return retbuf;
}


//------------------------------------------------------------------
/**
 * ���U����������A�V�K�ɍ쐬����������o�b�t�@�ɃR�s�[���ĕԂ�
 * �i������o�b�t�@�̍폜�͊e���ōs���j
 *
 * @param   wazaID		���U�h�c
 * @param   heapID		�q�[�v�h�c
 *
 * @retval  STRBUF*		������o�b�t�@�i���s�Ȃ�NULL)
 */
//------------------------------------------------------------------
STRBUF* MSGDAT_UTIL_GetWazaName( u32 wazaID, u32 heapID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_wazaname_dat, heapID);
	if( man )
	{
		STRBUF* wazaname = STRBUF_Create(BUFLEN_WAZA_NAME, heapID);
		if( wazaname )
		{
			MSGMAN_GetString(man, wazaID, wazaname);
		}
		MSGMAN_Delete(man);
		return wazaname;
	}
	return NULL;
}


//------------------------------------------------------------------
/**
 * �|�P��������������A�V�K�ɍ쐬����������o�b�t�@�ɃR�s�[���ĕԂ�
 * �i������o�b�t�@�̍폜�͊e���ōs���j
 *
 * @param   monsno		�|�P�����i���o�[
 * @param   heapID		�q�[�v�h�c
 *
 * @retval  STRBUF*		������o�b�t�@�i���s�Ȃ�NULL)
 */
//------------------------------------------------------------------
STRBUF* MSGDAT_UTIL_GetMonsName( u32 monsno, u32 heapID )
{
	MSGDATA_MANAGER* man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_monsname_dat, heapID );
	if( man )
	{
		STRBUF* buf = MSGMAN_AllocString( man, monsno );
		MSGMAN_Delete(man);
		return buf;
	}
	return NULL;
}

