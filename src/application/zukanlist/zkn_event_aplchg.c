//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_event_aplchg.c
 *	@brief		�A�v���P�[�V�����ύX�C�x���g
 *	@author		tomoya takahashi 
 *	@data		2006.01.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#include "include/application/zukanlist/zkn_event_func.h"

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

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void ZknAplStart( ZKN_APL_DATA* p_apl, ZKN_EVENT_SYS_PTR p_event, ZKN_PROC_SYS_PTR p_proc );

//-----------------------------------------------------------------------------
/**
 *		���������[���A�v���P�[�V�����J�n
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief		�A�v���P�[�V�����J�n
 *
 *	@param		p_work	���[�N
 *
 *	@retval		TRUE	�C�x���g�I��
 *	@retval		FALSE	�C�x���g���s
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL ZKN_EVENT_AplStart( ZKN_EVENT_WORK* p_work )
{
	ZKN_EVENT_APL_START*	p_data = p_work->p_data;

	switch( p_work->seq ){
	case 0:
		// �A�v���P�[�V�����J�n
		ZknAplStart( p_data->p_apl, p_data->p_event, p_data->p_proc );
		p_work->seq++;
		break;

	case 1:
		// ����J�n���m�F
		if( ZKN_PROC_MainMoveCheck( p_data->p_proc ) == TRUE ){
			p_work->seq++;
		}
		break;
		
	case 2:
		return TRUE;
	}

	return FALSE;
}



//-----------------------------------------------------------------------------
/**
 *		�O�̃A�v���P�[�V�����I���[�����̃A�v���P�[�V�����J�n
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief		�A�v���P�[�V�����ύX
 *
 *	@param		p_work	���[�N
 *
 *	@retval		TRUE	�C�x���g�I��
 *	@retval		FALSE	�C�x���g���s
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL ZKN_EVENT_AplChange( ZKN_EVENT_WORK* p_work )
{
	ZKN_EVENT_APL_CHANGE*	p_data = p_work->p_data;

	switch( p_work->seq ){
	//-------------------------------------
	//		���̃v���Z�X�I��
	//=====================================
	case 0:
		ZKN_PROC_EndReq( p_data->p_proc );
		p_work->seq++;
		break;

	//-------------------------------------
	//		�I���`�F�b�N
	//=====================================
	case 1:
		if( ZKN_PROC_EndCheck( p_data->p_proc ) == TRUE ){
			p_work->seq++;
		}
		break;

	//-------------------------------------
	//		���J�n
	//=====================================
	case 2:
		// �A�v���P�[�V�����J�n
		ZknAplStart( p_data->p_apl, p_data->p_event, p_data->p_proc );
		p_work->seq++;
		break;

	//-------------------------------------
	//		�J�n�`�F�b�N
	//=====================================
	case 3:
		if( ZKN_PROC_MainMoveCheck( p_data->p_proc ) == TRUE ){
			return TRUE;
		}
		break;

	default:
		// �����ɂ���̂͂�������
		GF_ASSERT( 0 );
		break;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 *		���̃A�v���P�[�V�����I���[���}�Ӕj��
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	���̃A�v���P�[�V�������I�������}�ӂ̏I��
 *
 *	@param	p_work	���[�N
 *
 *	@retval		TRUE	�C�x���g�I��
 *	@retval		FALSE	�C�x���g���s
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL ZKN_EVENT_AplEndZknDelete( ZKN_EVENT_WORK* p_work )
{
	ZKN_EVENT_APL_END_ZKN_DELETE*	p_data = p_work->p_data;
	BOOL check[4];
	int i;

	switch( p_work->seq ){
	//-------------------------------------
	//		���̃v���Z�X�I��
	//=====================================
	case 0:
		ZKN_PROC_EndReq( p_data->p_proc_m );
		ZKN_PROC_EndReq( p_data->p_proc_s );
		ZKN_PROC_EndReq( p_data->p_proc_mc );
		ZKN_PROC_EndReq( p_data->p_proc_sc );
		p_work->seq++;
		break;

	//-------------------------------------
	//		�I���`�F�b�N
	//=====================================
	case 1:
		check[0] = ZKN_PROC_EndCheck( p_data->p_proc_m );
		check[1] = ZKN_PROC_EndCheck( p_data->p_proc_s );
		check[2] = ZKN_PROC_EndCheck( p_data->p_proc_mc );
		check[3] = ZKN_PROC_EndCheck( p_data->p_proc_sc );
		for( i=0; i<4; i++ ){
			if( check[ i ] == FALSE ){
				break;
			}
		}
		if( i >= 4 ){
			p_work->seq++;
		}
		break;

	//-------------------------------------
	//		�j���t���O�𗧂Ă�
	//=====================================
	case 2:
		*p_data->p_delete_flag = TRUE;
		return TRUE;

	default:
		// �����ɂ���̂͂�������
		GF_ASSERT( 0 );
		break;
	}

	return FALSE;
}



//-----------------------------------------------------------------------------
/**
 *	���̃A�v���P�[�V�����I��
 */
//-----------------------------------------------------------------------------
BOOL ZKN_EVENT_AplEnd( ZKN_EVENT_WORK* p_work )
{
	ZKN_EVENT_APL_END* p_data = p_work->p_data;

	switch( p_work->seq ){
	//-------------------------------------
	//		���̃v���Z�X�I��
	//=====================================
	case 0:
		ZKN_PROC_EndReq( p_data->p_proc );
		p_work->seq++;
		break;

	//-------------------------------------
	//		�I���`�F�b�N
	//=====================================
	case 1:
		
		if( ZKN_PROC_EndCheck( p_data->p_proc ) ){
			p_work->seq++;
		}
		break;

	//-------------------------------------
	//		�j���t���O�𗧂Ă�
	//=====================================
	case 2:
		// �C�x���g�f�[�^�j��
		ZKN_EVENT_Init( p_data->p_event, NULL, 0 );
		return TRUE;

	default:
		// �����ɂ���̂͂�������
		GF_ASSERT( 0 );
		break;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 *		main��ʃT�u��ʑS�ύX
 */
//-----------------------------------------------------------------------------
BOOL ZKN_EVENT_AplAllChange( ZKN_EVENT_WORK* p_work )
{
	ZKN_EVENT_APL_AllCHANGE*	p_data = p_work->p_data;
	BOOL check[4];
	int i;

	switch( p_work->seq ){
	//-------------------------------------
	//		���̃v���Z�X�I��
	//=====================================
	case 0:
		ZKN_PROC_EndReq( p_data->p_proc_m );
		ZKN_PROC_EndReq( p_data->p_proc_s );
		ZKN_PROC_EndReq( p_data->p_proc_mc );
		ZKN_PROC_EndReq( p_data->p_proc_sc );
		p_work->seq++;
		break;

	//-------------------------------------
	//		�I���`�F�b�N
	//=====================================
	case 1:
		check[0] = ZKN_PROC_EndCheck( p_data->p_proc_m );
		check[1] = ZKN_PROC_EndCheck( p_data->p_proc_s );
		check[2] = ZKN_PROC_EndCheck( p_data->p_proc_mc );
		check[3] = ZKN_PROC_EndCheck( p_data->p_proc_sc );
		for( i=0; i<4; i++ ){
			if( check[ i ] == FALSE ){
				break;
			}
		}
		if( i >= 4 ){
			p_work->seq++;
		}
		break;

	//-------------------------------------
	//		���J�n
	//=====================================
	case 2:
		// �A�v���P�[�V�����J�n
		ZknAplStart( p_data->p_apl_m, p_data->p_event_m, p_data->p_proc_m );
		ZknAplStart( p_data->p_apl_s, p_data->p_event_s, p_data->p_proc_s );
		ZknAplStart( p_data->p_apl_mc, p_data->p_event_mc, p_data->p_proc_mc );
		ZknAplStart( p_data->p_apl_sc, p_data->p_event_sc, p_data->p_proc_sc );
		p_work->seq++;
		break;

	//-------------------------------------
	//		�A�v���P�[�V�����J�n���`�F�b�N	
	//=====================================
	case 3:
		if( p_data->p_apl_m ){
			check[0] = ZKN_PROC_MainMoveCheck( p_data->p_proc_m );
		}else{
			check[0] = TRUE;
		}
		if( p_data->p_apl_s ){
			check[1] = ZKN_PROC_MainMoveCheck( p_data->p_proc_s );
		}
		if( p_data->p_apl_mc ){
			check[2] = ZKN_PROC_MainMoveCheck( p_data->p_proc_mc );
		}else{
			check[2] = TRUE;
		}
		if( p_data->p_apl_sc ){
			check[3] = ZKN_PROC_MainMoveCheck( p_data->p_proc_sc );
		}else{
			check[3] = TRUE;
		}
		
		for( i=0; i<4; i++ ){
			if( check[ i ] == FALSE ){
				break;
			}
		}
		if( i >= 4 ){
			return TRUE;
		}
		break;

	default:
		// �����ɂ���̂͂�������
		GF_ASSERT( 0 );
		break;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 *		main��ʃT�u���	�Q�ύX
 */
//-----------------------------------------------------------------------------
BOOL ZKN_EVENT_AplDoubleChange( ZKN_EVENT_WORK* p_work )
{
	ZKN_EVENT_APL_DOUBLE_CHANGE*	p_data = p_work->p_data;
	BOOL check[2];
	int i;

	switch( p_work->seq ){
	//-------------------------------------
	//		���̃v���Z�X�I��
	//=====================================
	case 0:
		ZKN_PROC_EndReq( p_data->p_proc_m );
		ZKN_PROC_EndReq( p_data->p_proc_s );
		p_work->seq++;
		break;

	//-------------------------------------
	//		�I���`�F�b�N
	//=====================================
	case 1:
		check[0] = ZKN_PROC_EndCheck( p_data->p_proc_m );
		check[1] = ZKN_PROC_EndCheck( p_data->p_proc_s );
		for( i=0; i<2; i++ ){
			if( check[ i ] == FALSE ){
				break;
			}
		}
		if( i >= 2 ){
			p_work->seq++;
		}
		break;

	//-------------------------------------
	//		���J�n
	//=====================================
	case 2:
		// �A�v���P�[�V�����J�n
		ZknAplStart( p_data->p_apl_m, p_data->p_event_m, p_data->p_proc_m );
		ZknAplStart( p_data->p_apl_s, p_data->p_event_s, p_data->p_proc_s );
		p_work->seq++;
		break;

	//-------------------------------------
	//		�A�v���P�[�V�����J�n�`�F�b�N
	//=====================================
	case 3:
		if( p_data->p_apl_m ){
			check[0] = ZKN_PROC_MainMoveCheck( p_data->p_proc_m );
		}else{
			check[0] = TRUE;
		}
		if( p_data->p_apl_s ){
			check[1] = ZKN_PROC_MainMoveCheck( p_data->p_proc_s );
		}else{
			check[1] = TRUE;
		}
		
		for( i=0; i<2; i++ ){
			if( check[ i ] == FALSE ){
				break;
			}
		}
		if( i >= 2 ){
			return TRUE;
		}
		break;

	default:
		// �����ɂ���̂͂�������
		GF_ASSERT( 0 );
		break;
	}

	return FALSE;
}




//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�v���P�[�V�����̊J�n
 *
 *	@param	p_apl		�A�v���P�[�V�����f�[�^
 *	@param	p_event		�C�x���g�V�X�e��
 *	@param	p_proc		�v���Z�X�V�X�e��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknAplStart( ZKN_APL_DATA* p_apl, ZKN_EVENT_SYS_PTR p_event, ZKN_PROC_SYS_PTR p_proc )
{
	ZKN_PROC_INIT			proc_init;

	// �A�v���P�[�V�����f�[�^�����邩�`�F�b�N
	if( p_apl ){

		// �v���Z�X�ɓo�^
		proc_init.p_glb_data	= p_apl->p_glb_data;
		proc_init.p_glb_draw	= p_apl->p_glb_draw;
		proc_init.cp_do_func	= p_apl->do_func;
		proc_init.cp_draw_func	= p_apl->draw_func;
		ZKN_PROC_Init( p_proc, &proc_init );

		// �C�x���g�o�^
		ZKN_EVENT_Init( p_event, p_apl->p_event_data, p_apl->event_num );
	}
}








//-----------------------------------------------------------------------------
/**
 *		�e�A�v���P�[�V�����ɕύX����C�x���g�f�[�^�쐬�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�C�x���g�f�[�^�j���֐�
 *
 *	@param	p_event_data	�f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_DeleteData( ZKN_EVENT_DATA* p_event_data )
{
	GF_ASSERT( p_event_data->work.p_data );

	sys_FreeMemoryEz( p_event_data->work.p_data );
	p_event_data->work.p_data = NULL;
}

// �\�[�g���
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����\�[�g�ɕύX����C�x���g����
 *
 *	@param	heap				�q�[�v
 *	@param	p_event_data		�C�x���g�f�[�^
 *	@param	zkn_sys				�}�ӃV�X�e��
 *	@param	event_key			�C�x���g�L�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeSortSearch( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_AllCHANGE* p_e_data;
	
	p_event_data->key_msk	= event_key;
	p_event_data->func		= ZKN_EVENT_AplAllChange;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// �v���b�N�V�X�e��
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// �v���b�N�V�X�e��
	p_e_data->p_proc_mc	= ZKN_SYS_GetProcSysMainCommon( zkn_sys );		// �v���b�N�V�X�e��
	p_e_data->p_proc_sc	= ZKN_SYS_GetProcSysSubCommon( zkn_sys );		// �v���b�N�V�X�e��
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_mc= ZKN_SYS_GetEventSysMainCommon( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_sc= ZKN_SYS_GetEventSysSubCommon( zkn_sys );		// �C�x���g�V�X�e��

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_SORTSEARCH );		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_SORTSEARCH );		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_mc	= NULL;		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_sc	= NULL;		// �n�߂�A�v���P�[�V�����f�[�^
	
	p_event_data->work.p_data = p_e_data;
}

// �}�ӃV�X�e���I��
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӏI���C�x���g�̐���
 *
 *	@param	heap			�q�[�vID
 *	@param	p_event_data	�C�x���g�f�[�^
 *	@param	zkn_sys			�}�ӃV�X�e��
 *	@param	event_key			�C�x���g�L�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeZukanEnd( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_END_ZKN_DELETE* p_e_data;
	
	p_event_data->key_msk	= event_key;
	p_event_data->func		= ZKN_EVENT_AplEndZknDelete;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_END_ZKN_DELETE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_END_ZKN_DELETE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );
	p_e_data->p_proc_mc	= ZKN_SYS_GetProcSysMainCommon( zkn_sys );
	p_e_data->p_proc_sc	= ZKN_SYS_GetProcSysSubCommon( zkn_sys );
	p_e_data->p_delete_flag	= ZKN_SYS_GetZknDeleteFlag( zkn_sys );
	
	p_event_data->work.p_data = p_e_data;
}


// �}�Ӊ��
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӂɕύX����C�x���g����
 *
 *	@param	heap				�q�[�v
 *	@param	p_event_data		�C�x���g�f�[�^
 *	@param	zkn_sys				�}�ӃV�X�e��
 *	@param	event_key			�C�x���g�L�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeZukan( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_AllCHANGE* p_e_data;
	
	p_event_data->key_msk	= event_key;
	p_event_data->func		= ZKN_EVENT_AplAllChange;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// �v���b�N�V�X�e��
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// �v���b�N�V�X�e��
	p_e_data->p_proc_mc	= ZKN_SYS_GetProcSysMainCommon( zkn_sys );		// �v���b�N�V�X�e��
	p_e_data->p_proc_sc	= ZKN_SYS_GetProcSysSubCommon( zkn_sys );		// �v���b�N�V�X�e��
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_mc= ZKN_SYS_GetEventSysMainCommon( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_sc= ZKN_SYS_GetEventSysSubCommon( zkn_sys );		// �C�x���g�V�X�e��

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN );		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN );		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_mc	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_COMMON );		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_sc	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_COMMON );		// �n�߂�A�v���P�[�V�����f�[�^
	
	p_event_data->work.p_data = p_e_data;
}

// �|�P�������X�g���
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g�Ɉړ�
 *
 *	@param	heap		�q�[�v
 *	@param	p_data		�C�x���g�f�[�^
 *	@param	zkn_sys		�}�ӃV�X�e��
 *	@param	event_key			�C�x���g�L�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangePokeList( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_AllCHANGE* p_e_data;
	
	p_data->key_msk	= event_key;
	p_data->func		= ZKN_EVENT_AplAllChange;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// �v���b�N�V�X�e��
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// �v���b�N�V�X�e��
	p_e_data->p_proc_mc	= ZKN_SYS_GetProcSysMainCommon( zkn_sys );		// �v���b�N�V�X�e��
	p_e_data->p_proc_sc	= ZKN_SYS_GetProcSysSubCommon( zkn_sys );		// �v���b�N�V�X�e��
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_mc= ZKN_SYS_GetEventSysMainCommon( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_sc= ZKN_SYS_GetEventSysSubCommon( zkn_sys );		// �C�x���g�V�X�e��

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_POKELIST );		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_POKELIST );		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_mc	= NULL;		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_sc	= NULL;		// �n�߂�A�v���P�[�V�����f�[�^
	
	p_data->work.p_data = p_e_data;
}

// �|�P�������X�g�̏��ʂ̂ݕύX
//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������X�g���ăX�^�[�g
 *
 *	@param	p_event		�C�x���g�i�[��
 *	@param	zkn_sys		�}�ӃV�X�e��
 *	@param	heap		�q�[�v
 *	@param	event_key			�C�x���g�L�[
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeStartMainPokeList( ZKN_EVENT_DATA* p_event, ZKN_SYS_PTR zkn_sys, int heap, int event_key )
{
	ZKN_EVENT_APL_CHANGE* p_aplchg;
	
	p_event->key_msk	= event_key;
	p_event->func		= ZKN_EVENT_AplChange;

	// �C�x���g���[�N�쐬
	p_aplchg = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_CHANGE) );
	GF_ASSERT( p_aplchg );
	p_aplchg->p_apl		= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_POKELIST );
	p_aplchg->p_proc	= ZKN_SYS_GetProcSysMain( zkn_sys );
	p_aplchg->p_event	= ZKN_SYS_GetEventSysMain( zkn_sys );
	
	// �C�x���g���[�N�ݒ�
	p_event->work.p_data = p_aplchg;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���z�}�ړ�
 *
 *	@param	heap		�q�[�v
 *	@param	p_data		�C�x���g�f�[�^
 *	@param	zkn_sys		�}�ӃV�X�e��
 *	@param	event_key	�C�x���g�L�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeRange( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_DOUBLE_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplDoubleChange;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// �v���b�N�V�X�e��
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// �v���b�N�V�X�e��
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// �C�x���g�V�X�e��

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_RANGE );		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_RANGE );		// �n�߂�A�v���P�[�V�����f�[�^
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���z�̃��C����ʂ����ύX
 *
 *	@param	heap		�q�[�v
 *	@param	p_data		�C�x���g�f�[�^
 *	@param	zkn_sys		�}�ӃV�X�e��
 *	@param	event_key	�C�x���g�L�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeRangeMain( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplChange;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_CHANGE) );
	p_e_data->p_proc	= ZKN_SYS_GetProcSysMain( zkn_sys );			// �v���b�N�V�X�e��
		
	p_e_data->p_event	= ZKN_SYS_GetEventSysMain( zkn_sys );		// �C�x���g�V�X�e��

	p_e_data->p_apl	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_RANGE );		// �n�߂�A�v���P�[�V�����f�[�^
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������ړ�
 *
 *	@param	heap		�q�[�v
 *	@param	p_data		�C�x���g�f�[�^
 *	@param	zkn_sys		�}�ӃV�X�e��
 *	@param	event_key	�C�x���g�L�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeSound( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_DOUBLE_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplDoubleChange;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// �v���b�N�V�X�e��
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// �v���b�N�V�X�e��
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// �C�x���g�V�X�e��

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_SOUND );		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_SOUND );		// �n�߂�A�v���P�[�V�����f�[�^
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������ړ�
 *
 *	@param	heap		�q�[�v
 *	@param	p_data		�C�x���g�f�[�^
 *	@param	zkn_sys		�}�ӃV�X�e��
 *	@param	event_key	�C�x���g�L�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeSoundMain( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplChange;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_CHANGE) );
	p_e_data->p_proc	= ZKN_SYS_GetProcSysMain( zkn_sys );			// �v���b�N�V�X�e��
		
	p_e_data->p_event	= ZKN_SYS_GetEventSysMain( zkn_sys );		// �C�x���g�V�X�e��

	p_e_data->p_apl	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_SOUND );		// �n�߂�A�v���P�[�V�����f�[�^
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�傫����׈ړ�
 *
 *	@param	heap		�q�[�v
 *	@param	p_data		�C�x���g�f�[�^
 *	@param	zkn_sys		�}�ӃV�X�e��
 *	@param	event_key	�C�x���g�L�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeBig( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_DOUBLE_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplDoubleChange;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// �v���b�N�V�X�e��
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// �v���b�N�V�X�e��
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// �C�x���g�V�X�e��

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_BIG );		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_BIG );		// �n�߂�A�v���P�[�V�����f�[�^
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�傫����׈ړ�	
 *
 *	@param	heap		�q�[�v
 *	@param	p_data		�C�x���g�f�[�^
 *	@param	zkn_sys		�}�ӃV�X�e��
 *	@param	event_key	�C�x���g�L�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeBigMain( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplChange;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_CHANGE) );
	p_e_data->p_proc	= ZKN_SYS_GetProcSysMain( zkn_sys );			// �v���b�N�V�X�e��
		
	p_e_data->p_event	= ZKN_SYS_GetEventSysMain( zkn_sys );		// �C�x���g�V�X�e��

	p_e_data->p_apl	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_BIG );		// �n�߂�A�v���P�[�V�����f�[�^
	
	p_data->work.p_data = p_e_data;
}


//----------------------------------------------------------------------------
//
/**
 *
 *	@brief	�傫����׈ړ�	
 *
 *	@param	heap		�q�[�v
 *	@param	p_data		�C�x���g�f�[�^
 *	@param	zkn_sys		�}�ӃV�X�e��
 *	@param	event_key	�C�x���g�L�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeBigWeightMain( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplChange;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_CHANGE) );
	p_e_data->p_proc	= ZKN_SYS_GetProcSysMain( zkn_sys );			// �v���b�N�V�X�e��
		
	p_e_data->p_event	= ZKN_SYS_GetEventSysMain( zkn_sys );		// �C�x���g�V�X�e��

	p_e_data->p_apl	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_BIG_WEIGHT );		// �n�߂�A�v���P�[�V�����f�[�^
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�ӂ̂ݍ쐬����
 *
 *	@param	heap			�q�[�v
 *	@param	p_event_data	�C�x���g�f�[�^
 *	@param	zkn_sys			�}�ӃV�X�e��
 *	@param	event_key		�C�x���g�L�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeZukanOnly(  int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key  )
{
	ZKN_EVENT_APL_DOUBLE_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplDoubleChange;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// �v���b�N�V�X�e��
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// �v���b�N�V�X�e��
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// �C�x���g�V�X�e��

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN );		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN );		// �n�߂�A�v���P�[�V�����f�[�^
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄf�[�^���C����ʂ̂ݍ쐬����
 *
 *	@param	heap			�q�[�v
 *	@param	p_event_data	�C�x���g�f�[�^
 *	@param	zkn_sys			�}�ӃV�X�e��
 *	@param	event_key		�C�x���g�L�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeZukanNormalMainOnly(  int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key  )
{
	ZKN_EVENT_APL_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplChange;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_CHANGE) );
	p_e_data->p_proc	= ZKN_SYS_GetProcSysMain( zkn_sys );			// �v���b�N�V�X�e��
		
	p_e_data->p_event	= ZKN_SYS_GetEventSysMain( zkn_sys );		// �C�x���g�V�X�e��

	p_e_data->p_apl	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN );		// �n�߂�A�v���P�[�V�����f�[�^
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄf�[�^�O���t�B�b�N�o�[�W����
 *
 *	@param	heap			�q�[�v
 *	@param	p_event_data	�C�x���g�f�[�^
 *	@param	zkn_sys			�}�ӃV�X�e��
 *	@param	event_key		�C�x���g�L�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeZukanGraphic(  int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key  )
{
	ZKN_EVENT_APL_DOUBLE_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplDoubleChange;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// �v���b�N�V�X�e��
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// �v���b�N�V�X�e��
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// �C�x���g�V�X�e��

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_GRA );		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_GRA );		// �n�߂�A�v���P�[�V�����f�[�^
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄf�[�^����o�[�W�������C����ʂ̂ݍ쐬����
 *
 *	@param	heap			�q�[�v
 *	@param	p_event_data	�C�x���g�f�[�^
 *	@param	zkn_sys			�}�ӃV�X�e��
 *	@param	event_key		�C�x���g�L�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeZukanTextMainOnly(  int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key  )
{
	ZKN_EVENT_APL_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplChange;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_CHANGE) );
	p_e_data->p_proc	= ZKN_SYS_GetProcSysMain( zkn_sys );			// �v���b�N�V�X�e��
		
	p_e_data->p_event	= ZKN_SYS_GetEventSysMain( zkn_sys );		// �C�x���g�V�X�e��

	p_e_data->p_apl	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_TEXT );		// �n�߂�A�v���P�[�V�����f�[�^
	
	p_data->work.p_data = p_e_data;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�}�ӃT�u�R�����̂ݕύX
 *
 *	@param	heap			�q�[�v
 *	@param	p_event_data	�C�x���g�f�[�^�i�[��
 *	@param	zkn_sys			�}�ӃV�X�e��
 *	@param	event_key		�C�x���g�L�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeZukanCommonSubOnly( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_CHANGE* p_e_data;
	
	p_event_data->key_msk		= event_key;
	p_event_data->func		= ZKN_EVENT_AplChange;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_CHANGE) );
	p_e_data->p_proc	= ZKN_SYS_GetProcSysSubCommon( zkn_sys );			// �v���b�N�V�X�e��
		
	p_e_data->p_event	= ZKN_SYS_GetEventSysSubCommon( zkn_sys );		// �C�x���g�V�X�e��

	p_e_data->p_apl	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_COMMON );		// �n�߂�A�v���P�[�V�����f�[�^
	
	p_event_data->work.p_data = p_e_data;
}

#ifdef PM_DEBUG
// �������DEBUG�A�v����
void ZKN_EVENT_BigHeightDebugApl( ZKN_EVENT_DATA* p_event, ZKN_SYS_PTR zkn_sys, int heap, int event_key )
{
	ZKN_EVENT_APL_AllCHANGE* p_e_data;
	
	p_event->key_msk	= event_key;
	p_event->func		= ZKN_EVENT_AplAllChange;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// �v���b�N�V�X�e��
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// �v���b�N�V�X�e��
	p_e_data->p_proc_mc	= ZKN_SYS_GetProcSysMainCommon( zkn_sys );		// �v���b�N�V�X�e��
	p_e_data->p_proc_sc	= ZKN_SYS_GetProcSysSubCommon( zkn_sys );		// �v���b�N�V�X�e��
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_mc= ZKN_SYS_GetEventSysMainCommon( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_sc= ZKN_SYS_GetEventSysSubCommon( zkn_sys );		// �C�x���g�V�X�e��

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_BIG );		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_HEIGHT_DEBUG );		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_mc	= NULL;		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_sc	= NULL;		// �n�߂�A�v���P�[�V�����f�[�^
	
	p_event->work.p_data = p_e_data;
}

// �������DEBUG�A�v�����獂����ׂɕ��A
void ZKN_EVENT_BigHeightDebugAplReturn( ZKN_EVENT_DATA* p_event, ZKN_SYS_PTR zkn_sys, int heap, int event_key )
{
	ZKN_EVENT_APL_AllCHANGE* p_e_data;
	
	p_event->key_msk	= event_key;
	p_event->func		= ZKN_EVENT_AplAllChange;
	
	// �C�x���g�f�[�^�쐬
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// �v���b�N�V�X�e��
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// �v���b�N�V�X�e��
	p_e_data->p_proc_mc	= ZKN_SYS_GetProcSysMainCommon( zkn_sys );		// �v���b�N�V�X�e��
	p_e_data->p_proc_sc	= ZKN_SYS_GetProcSysSubCommon( zkn_sys );		// �v���b�N�V�X�e��
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_mc= ZKN_SYS_GetEventSysMainCommon( zkn_sys );		// �C�x���g�V�X�e��
	p_e_data->p_event_sc= ZKN_SYS_GetEventSysSubCommon( zkn_sys );		// �C�x���g�V�X�e��

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_BIG );		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_BIG );		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_mc	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_COMMON );		// �n�߂�A�v���P�[�V�����f�[�^
	p_e_data->p_apl_sc	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_COMMON );		// �n�߂�A�v���P�[�V�����f�[�^
	
	p_event->work.p_data = p_e_data;
}
#endif

