//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_world_text_sys.c
 *	@brief		�}�ӂ̊O����e�L�X�g�A�N�Z�X
 *	@author		tomoya takahashi 
 *	@data		2006.02.28
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/system/fontproc.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"

#include "include/application/zukanlist/zkn_world_text_data.h"
#include "src/application/zukanlist/zkn_worldtext.h"

#include "include/application/zukanlist/zkn_version.h"

#define	__ZKN_WORLD_TEXT_SYS_H_GLOBAL
#include "include/application/zukanlist/zkn_world_text_sys.h"

//-----------------------------------------------------------------------------
/**
 *					�R�[�f�B���O�K��
 *		���֐���
 *				�P�����ڂ͑啶������ȍ~�͏������ɂ���
 *		���ϐ���
 *				�E�ϐ�����
 *						const�ɂ� c_ ��t����
 *						static�ɂ� s_ ��t����
 *						�|�C���^�ɂ� p_ ��t����
 *						�S�č��킳��� csp_ �ƂȂ�
 *				�E�O���[�o���ϐ�
 *						�P�����ڂ͑啶��
 *				�E�֐����ϐ�
 *						�������Ɓh�Q�h�Ɛ������g�p���� �֐��̈���������Ɠ���
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define ZKN_WT_ALLOC_STR_NUM		( 256 )		// �m�ۂ��镶����


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
 *					�O���[�o���f�[�^
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�|�P�����O����e�L�X�g�p���R�[�h��
//	���ۂ�GMM�t�@�C���ɓ����Ă���f�[�^�̊O���ꍀ�ڐ�
//	�Ή��f�[�^
//	IDX�͊O����e�L�X�g�p���R�[�h
//
//	zukan_data.xls�ɂ͉��̐����̏����ް����i�[���Ă���
//=====================================
static const u8 ZKN_WORLD_TEXT_GmmIdx[ ZKN_WORLD_TEXT_NUM ] = {
/* ���{ */
#if( PM_LANG == LANG_JAPAN )
	ZKN_WORLD_TEXT_NUM,	// ����
	0,		// �A�����J
	1,		// �t�����X
	2,		// �h�C�c		
	3,		// �C�^���A	
	4		// �X�y�C��
#endif
/* �A�����J */
#if( PM_LANG == LANG_ENGLISH )
	0,
	ZKN_WORLD_TEXT_NUM,
	1,
	2,
	3,
	4
#endif
/* �t�����X */
#if( PM_LANG == LANG_FRANCE )
	0,
	1,
	ZKN_WORLD_TEXT_NUM,
	2,
	3,
	4
#endif
/* �C�^���A */
#if( PM_LANG == LANG_ITALY )
	0,
	1,
	2,
	ZKN_WORLD_TEXT_NUM,
	3,
	4
#endif
/* �h�C�c */
#if( PM_LANG == LANG_GERMANY )
	0,
	1,
	2,
	3,
	ZKN_WORLD_TEXT_NUM,
	4
#endif
/* �X�y�C�� */
#if( PM_LANG == LANG_SPAIN )
	0,
	1,
	2,
	3,
	4,
	ZKN_WORLD_TEXT_NUM
#endif
};


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static inline int ZknWt_GetGmmIdx( int zkn_text_code );
static inline BOOL ZknWt_CheckWorldData( int textverpokenum, int gmm_idx );
static STRBUF* ZknWt_GetSTRData( int file_idx, int data_idx, int heap );
static void ZknWt_GetCountryPokeData( int monsno, int country, int* p_country_poke_num, int* p_country_text_code, int* p_country_gmm_idx );

//----------------------------------------------------------------------------
/**
 *	@brief	������o�b�t�@��j������
 *
 *	@param	buf		�o�b�t�@
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_WT_DeleteStrBuf( STRBUF* buf )
{
	STRBUF_Delete( buf );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���R�[�h����Ή�����O����GMM�C���f�b�N�X���擾
 *
 *	@param	country	���R�[�h
 *
 *	@return	�O����ԍ�
 */
//-----------------------------------------------------------------------------
int ZKN_WT_LANG_Code_WORLD_TEXT_GMM_Idx( int country )
{
	int country_text_code;
	int country_gmm_idx;
	
	// �O����e�L�X�g�p���R�[�h�ɕϊ�
	country_text_code = ZKN_WT_GetLANG_Code_ZKN_WORLD_TEXT_Code( country );
	GF_ASSERT( country_text_code < ZKN_WORLD_TEXT_NUM );	// �����Ƃ������Ƃ̓f�[�^������
	// �O����e�L�X�g�p���R�[�h����GMM�f�[�^�O���ꍀ�ڐ��擾
	country_gmm_idx = ZknWt_GetGmmIdx( country_text_code );

	return country_gmm_idx;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O����ԍ�����Ή����鍑�R�[�h���擾����
 *
 *	@param	county	�O����ԍ�	(gmm�t�@�C���ɕ���ł���ԍ�)
 *
 *	@return	���R�[�h		// ����������Ȃ��Ƃ��̓z�[���^�E����Ԃ�
 */
//-----------------------------------------------------------------------------
int ZKN_WT_WORLD_TEXT_GMM_Idx_LANG_Code( int country )
{
	int i;

	// country�̃i���o�[��GmmIdx�e�[�u���C���f�b�N�X�����߂�
	// (���ꂪ�O����p���R�[�h)
	for( i=0; i<ZKN_WORLD_TEXT_NUM; i++ ){
		if( ZKN_WORLD_TEXT_GmmIdx[i] == country ){
			break;
		}
	}
	if( i== ZKN_WORLD_TEXT_NUM ){
		return PM_LANG;
	}

	// ���̊O���p���R�[�h�̃Q�[�������R�[�h���擾
	return ZKN_WT_GetZKN_WORLD_TEXT_Code_LANG_Code( i );
}


//----------------------------------------------------------------------------
/**
 *	@brief	���̃|�P��������Ԃ�
 *
 *	@param	monsno		�����X�^�[�i���o�[
 *	@param	country		�Q�[�������R�[�h
 *	@param	heap		�q�[�v
 *
 *	@return	������f�[�^
 */
//-----------------------------------------------------------------------------
STRBUF* ZKN_WT_GetPokeName( int monsno, int country, int heap )
{
	int country_poke_num;
	int country_text_code;
	int country_gmm_idx;
	int gmm_file_idx;

	// �����X�^�[�i���o�[�ƃQ�[�������R�[�h����
	// �O����e�L�X�g�f�[�^���ڐ�
	// �O����e�L�X�g�f�[�^�p���R�[�h
	// �O����e�L�X�g�f�[�^GMM�O�����ڐ��擾
	ZknWt_GetCountryPokeData( monsno, country, &country_poke_num, &country_text_code, &country_gmm_idx );

	// �����`�F�b�N
	if( country_gmm_idx == ZKN_WORLD_TEXT_NUM ){
		// ����
		// GMM�̒��̃f�[�^idx��monsno
		return MSGDAT_UTIL_GetMonsName( monsno, heap );
	}else{
		// �O��
		// GMM�̒��̃f�[�^�C���f�b�N�X�����߂�
		// �O���|�P������GMM�̃f�[�^�\��
		// �O����P��A�|�P������, �O����Q��A�|�P������,�O����R��A�|�P������,�O����S��A�|�P������,�O����T��A�|�P������
		// �O����P��B�|�P������, �O����Q��B�|�P������,�O����R��B�|�P������,�O����S��B�|�P������,�O����T��B�|�P������
		country_gmm_idx += country_poke_num * ZKN_WORLD_TEXT_OUTWORLD_NUM;
		gmm_file_idx = NARC_msg_zkn_worldname_dat;
	}

	// gmm_file_idx��country_gmm_idx����STRBUF���擾����
	return ZknWt_GetSTRData( gmm_file_idx, country_gmm_idx, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���̃|�P�����^�C�v��Ԃ�
 *
 *	@param	monsno		�����X�^�[�i���o�[
 *	@param	country		�Q�[�������R�[�h
 *	@param	heap		�q�[�v
 *
 *	@return	������f�[�^
 */
//-----------------------------------------------------------------------------
STRBUF* ZKN_WT_GetPokeType( int monsno, int country, int heap )
{
	int country_poke_num;
	int country_text_code;
	int country_gmm_idx;
	int gmm_file_idx;

	// �����X�^�[�i���o�[�ƃQ�[�������R�[�h����
	// �O����e�L�X�g�f�[�^���ڐ�
	// �O����e�L�X�g�f�[�^�p���R�[�h
	// �O����e�L�X�g�f�[�^GMM�O�����ڐ��擾
	ZknWt_GetCountryPokeData( monsno, country, &country_poke_num, &country_text_code, &country_gmm_idx );

	// �����`�F�b�N
	if( country_gmm_idx == ZKN_WORLD_TEXT_NUM ){
		// ����
		// GMM�̒��̃f�[�^idx��monsno
		country_gmm_idx = monsno;
		gmm_file_idx = NARC_msg_zkn_type_dat;
	}else{
		// �O��
		// GMM�̒��̃f�[�^�C���f�b�N�X�����߂�
		// �O���|�P������GMM�̃f�[�^�\��
		// �O����P��A�|�P����, �O����Q��A�|�P����,�O����R��A�|�P����,�O����S��A�|�P����,�O����T��A�|�P����
		// �O����P��B�|�P����, �O����Q��B�|�P����,�O����R��B�|�P����,�O����S��B�|�P����,�O����T��B�|�P����
		country_gmm_idx += country_poke_num * ZKN_WORLD_TEXT_OUTWORLD_NUM;
		gmm_file_idx = NARC_msg_zkn_worldtype_dat;
	}

	// gmm_file_idx��country_gmm_idx����STRBUF���擾����
	return ZknWt_GetSTRData( gmm_file_idx, country_gmm_idx, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���̃e�L�X�g�f�[�^��Ԃ�
 *
 *	@param	monsno		�����X�^�[�i���o�[
 *	@param	country		�Q�[�������R�[�h
 *	@param	page		�y�[�W
 *	@param	heap		�q�[�v
 *	
 *	@return	������f�[�^
 */
//-----------------------------------------------------------------------------
STRBUF* ZKN_WT_GetText( int monsno, int country, int page, int heap )
{
	int country_poke_num;
	int country_text_code;
	int country_gmm_idx;
	int gmm_file_idx;

	// �����X�^�[�i���o�[�ƃQ�[�������R�[�h����
	// �O����e�L�X�g�f�[�^���ڐ�
	// �O����e�L�X�g�f�[�^�p���R�[�h
	// �O����e�L�X�g�f�[�^GMM�O�����ڐ��擾
	ZknWt_GetCountryPokeData( monsno, country, &country_poke_num, &country_text_code, &country_gmm_idx );

	// �����`�F�b�N
	if( country_gmm_idx == ZKN_WORLD_TEXT_NUM ){

		// �y�[�W���`�F�b�N
		GF_ASSERT( page < ZKN_WT_HOME_TEXT_PAGE_NUM );
		// ����
		// GMM�̒��̃f�[�^idx��monsno
		country_gmm_idx = (monsno * ZKN_WT_HOME_TEXT_PAGE_NUM) + page;
		gmm_file_idx = ZKN_TEXT_DAT;
	}else{

		// �y�[�W���`�F�b�N
		GF_ASSERT( page < ZKN_WT_WORLD_TEXT_PAGE_NUM );
		// �O��
		// GMM�̒��̃f�[�^�C���f�b�N�X�����߂�
		// �O���|�P������GMM�̃f�[�^�\��
		// �O����P��A�|�P����1�y�[�W,�O����Q��A�|�P����1�y�[�W,�O����R��A�|�P����1�y�[�W,�O����S��A�|�P����1�y�[�W,�O����T��A�|�P����1�y�[�W,
		// �O����P��B�|�P����1�y�[�W,�O����Q��B�|�P����1�y�[�W,�O����R��B�|�P����1�y�[�W,�O����S��B�|�P����1�y�[�W,�O����T��B�|�P����1�y�[�W,
		country_gmm_idx = (country_gmm_idx * ZKN_WT_WORLD_TEXT_PAGE_NUM) + page + (country_poke_num * (ZKN_WORLD_TEXT_OUTWORLD_NUM * ZKN_WT_WORLD_TEXT_PAGE_NUM));
		gmm_file_idx = NARC_msg_zkn_comment_02_dat;
	}

	// gmm_file_idx��country_gmm_idx����STRBUF���擾����
	return ZknWt_GetSTRData( gmm_file_idx, country_gmm_idx, heap );
}


//-----------------------------------------------------------------------------
/**
 *			�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	�֐��ł̖߂�l[�O����GMM���̃f�[�^����][GMM�f�[�^�O���ꍀ�ڐ�]���炻�̃f�[�^������̂��`�F�b�N����
 *
 *	@param	textverpokenum
 *	@param	gmm_idx 
 *
 *	@retval	TRUE	�f�[�^������
 *	@retval	FALSE	���̃|�P�����̂��̍��̃f�[�^�͂Ȃ�
 */
//-----------------------------------------------------------------------------
static inline BOOL ZknWt_CheckWorldData( int textverpokenum, int gmm_idx )
{
	// �����̃f�[�^�����߂Ă��Ȃ��̂ɂ��̃|�P�����̊O����f�[�^�������Ƃ�
	// �̓f�[�^���Ȃ��Ƃ������ƂɂȂ�
	if( (textverpokenum == ZKN_WORLD_TEXT_POKE_NUM) && (gmm_idx != ZKN_WORLD_TEXT_NUM) ){
		return FALSE;
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�@�C���C���f�b�N�X���當����f�[�^���擾����
 *
 *	@param	file_idx
 *	@param	data_idx
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static STRBUF* ZknWt_GetSTRData( int file_idx, int data_idx, int heap )
{
	MSGDATA_MANAGER* man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, file_idx, heap );
	if( man )
	{
		STRBUF* buf = STRBUF_Create(ZKN_WT_ALLOC_STR_NUM, heap );
		if( buf )
		{
			MSGMAN_GetString(man, data_idx, buf);
		}
		MSGMAN_Delete(man);
		return buf;
	}
	return NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����X�^�[�i���o�[�ƃQ�[�������R�[�h����
 *			�O����e�L�X�g�f�[�^���ڐ�
 *			�O����e�L�X�g�f�[�^�p���R�[�h
 *			�O����e�L�X�g�f�[�^GMM�O�����ڐ�
 *			�擾
 *
 *	@param	monsno				�����X�^�[�i���o�[
 *	@param	country				�Q�[�������R�[�h
 *	@param	p_country_poke_num	�O����e�L�X�g�f�[�^���ڐ�
 *	@param	p_country_text_code	�O����e�L�X�g�f�[�^�p���R�[�h
 *	@param	p_country_gmm_idx	�O����e�L�X�g�f�[�^GMM�O�����ڐ�
 */
//-----------------------------------------------------------------------------
static void ZknWt_GetCountryPokeData( int monsno, int country, int* p_country_poke_num, int* p_country_text_code, int* p_country_gmm_idx )
{
	// �O����e�L�X�g�p���R�[�h�ɕϊ�
	*p_country_text_code = ZKN_WT_GetLANG_Code_ZKN_WORLD_TEXT_Code( country );
	GF_ASSERT( *p_country_text_code < ZKN_WORLD_TEXT_NUM );	// �����Ƃ������Ƃ̓f�[�^������
	// �����X�^�[�i���o�[����O����GMM���̃f�[�^���ڐ������߂�
	*p_country_poke_num = ZKN_WT_GetMonsNo_TEXTVERPokeNum( monsno );

	// �O����e�L�X�g�p���R�[�h����GMM�f�[�^�O���ꍀ�ڐ��擾
	*p_country_gmm_idx = ZknWt_GetGmmIdx( *p_country_text_code );

	// �f�[�^�����邩�`�F�b�N
	GF_ASSERT( ZknWt_CheckWorldData( *p_country_poke_num, *p_country_gmm_idx ) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�ӊO����e�L�X�g�p���R�[�h����O����e�L�X�gGMM�f�[�^�̊O���ꍀ�ڐ����擾
 *
 *	@param	zkn_text_code	�}�ӊO����e�L�X�g�p���R�[�h
 *
 *	@retval	�O����e�L�X�gGMM�f�[�^�O���ꍀ�ڐ�
 *	@retval ZKN_WORLD_TEXT_NUM�̎��͎���GMM�Ƀf�[�^������
 */
//-----------------------------------------------------------------------------
static inline int ZknWt_GetGmmIdx( int zkn_text_code )
{
	GF_ASSERT( zkn_text_code < ZKN_WORLD_TEXT_NUM );
	
	return ZKN_WORLD_TEXT_GmmIdx[ zkn_text_code ];
}

