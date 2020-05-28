//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		nutmix_comm_pack.c
 *	@brief		�ʐMPACKAGE�V�X�e��
 *	@author		tomoya takahashi
 *	@data		2006.05.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"


#define __NUTMIX_COMM_PACK_H_GLOBAL
#include "nutmix_comm_pack.h"

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
#define NUTMIX_COMM_PACK_DATABUFF_SIZE	( 38 )	// byte

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�_�~�[�R�[���o�b�N���[�N
//=====================================
typedef struct {
	BOOL init;
	int command;
	u8 data[ NUTMIX_COMM_PACK_DATABUFF_SIZE ];
	int size;
} NUTMIX_COMMPACK_DUMMY_WORK;


//-------------------------------------
//	�_�~�[�R�[���o�b�N�V�X�e��
//=====================================
typedef struct {
	NUTMIX_COMMPACK_DUMMY_WORK	work[NUTMIX_COMM_PACK_DUMMY_WORK_NUM];	// ���[�N
	const CommPacketTbl* pCommPacketLocal;	// �R�}���h�e�[�u��
	int					 commtbl_num;		// �R�}���h�e�[�u����
	void*				 pCallBackWork;		// �R�[���o�b�N���[�N
	TCB_PTR				 tcb;				// �^�X�N���[�N
} NUTMIX_COMMPACK_DUMMY_SYS;


//-------------------------------------
//	�O���ێ��@�V�X�e�����[�N
//	comm_flg����pWork�̎g�p�p�r���ς��
//=====================================
typedef struct _NUTMIX_COMMPACK_WORK{
	int comm_flg;	// �ʐM�p�b�N�t���O
	void* pWork;	// ���[�N
} ;




//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static NUTMIX_COMMPACK_DUMMY_SYS* NutMix_CommPack_DummySys_Init( const CommPacketTbl* pCommPacketLocal,int listNum,void* pWork, int heapID );
static void NutMix_CommPack_DummySys_Main( TCB_PTR tcb, void* p_work );
static void NutMix_CommPack_DummySys_Delete( NUTMIX_COMMPACK_DUMMY_SYS* p_sys );
static BOOL NutMix_CommPack_DummySys_SendData( NUTMIX_COMMPACK_DUMMY_SYS* p_sys, int command, const void* data, int size );




//----------------------------------------------------------------------------
/**
 *	@brief	�R�}���h�e�[�u���ݒ�@�p�b�N�֐�
 *
 *	@param	pCommPacketLocal		�R�}���h�e�[�u��
 *	@param	listNum					���X�g��
 *	@param	pWork					�R�[���o�b�N���[�N
 *	@param	comm_flg				�ʐM�p�b�N�t���O
 *	@param	heapID					�q�[�vID
 *
 *	@retval	�R�}���h�p�b�N�V�X�e�����[�N
 */
//-----------------------------------------------------------------------------
NUTMIX_COMMPACK_WORK* NMIX_CommPack_CommandInitialize( const CommPacketTbl* pCommPacketLocal,int listNum,void* pWork, int comm_flg, int heapID )
{
	NUTMIX_COMMPACK_WORK* p_sys;

	// �������m��
	p_sys = sys_AllocMemory( heapID, sizeof(NUTMIX_COMMPACK_WORK) );
	p_sys->comm_flg = comm_flg;
	p_sys->pWork = NULL;
	
	if( comm_flg == NUTMIX_COMM_PACK_COMM ){
	    CommCommandInitialize( pCommPacketLocal, listNum, pWork );
		OS_Printf( "�ʐMӰ�ރZ�b�g�A�b�v\n" );
	}else{
		p_sys->pWork = NutMix_CommPack_DummySys_Init( pCommPacketLocal, listNum, pWork, heapID );
		OS_Printf( "��lӰ�ރZ�b�g�A�b�v\n" );
	}

	return p_sys;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R�}���h�]���@�p�b�N�֐�
 *
 *	@param	command				�R�}���h
 *	@param	data				�f�[�^
 *	@param	size				�T�C�Y
 *	@param	p_sys				�R�}���h�p�b�N�V�X�e��
 *
 *	@retval	TRUE	����
 *	@retval	FALSE	���s
 */
//-----------------------------------------------------------------------------
BOOL NMIX_CommPack_CommSendData( int command, const void* data, int size, NUTMIX_COMMPACK_WORK* p_sys )
{
	if( p_sys->comm_flg == NUTMIX_COMM_PACK_COMM ){
	    return CommSendData( command, data, size );
	}else{
		return NutMix_CommPack_DummySys_SendData( p_sys->pWork, command, data, size );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R�}���h�e�[�u������	�p�b�N�V�X�e���j��
 *
 *	@param	p_sys	�V�X�e��
 */
//-----------------------------------------------------------------------------
void NMIX_CommPack_CommDelete( NUTMIX_COMMPACK_WORK* p_sys )
{
	if( p_sys->comm_flg == NUTMIX_COMM_PACK_ONE ){
		NutMix_CommPack_DummySys_Delete( p_sys->pWork );
	}
	sys_FreeMemoryEz( p_sys );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�����̐ڑ�ID���擾
 *
 *	@param	p_sys	�V�X�e��
 *
 *	@return	�ڑ�ID
 */
//-----------------------------------------------------------------------------
int NMIX_CommPack_CommGetCurrentID( NUTMIX_COMMPACK_WORK* p_sys )
{
	if( p_sys->comm_flg == NUTMIX_COMM_PACK_COMM ){
	    return CommGetCurrentID();
	}else{
		return NUTMIX_COMM_PACK_DUMMY_NETID;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ʐM�\��ԂȂ̂��ǂ�����Ԃ� �������R�}���h�ɂ��l�S�V�G�[�V�������܂��̏��
 *
 *	@param	p_sys	�V�X�e��
 *	@param	netID	�ڑ�ID
 *
 *	@retval	TRUE	�ڑ����Ă���
 *	@retval	FALSE	�ڑ����Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
BOOL NMIX_CommPack_CommIsConnect( NUTMIX_COMMPACK_WORK* p_sys, u16 netID )
{
	if( p_sys->comm_flg == NUTMIX_COMM_PACK_COMM ){
	    return CommIsConnect( netID );
	}else{
		if( netID == NUTMIX_COMM_PACK_DUMMY_NETID ){
			return TRUE;
		}else{
			return FALSE;
		}
	}
}



//-----------------------------------------------------------------------------
/**
 * 
 *		�v���C�x�[�g�֐�
 * 
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	�_�~�[�R�[���o�b�N�V�X�e��
 *	
 *	@param	pCommPacketLocal	�R�}���h�e�[�u��
 *	@param	listNum				�e�[�u����
 *	@param	pWork				���[�N
 *	@param	heapID				�q�[�vID
 *
 *	@return	�쐬�����V�X�e�����[�N
 */
//-----------------------------------------------------------------------------
static NUTMIX_COMMPACK_DUMMY_SYS* NutMix_CommPack_DummySys_Init( const CommPacketTbl* pCommPacketLocal,int listNum,void* pWork, int heapID )
{
	NUTMIX_COMMPACK_DUMMY_SYS* p_sys;

	// �������m��
	p_sys = sys_AllocMemory( heapID, sizeof(NUTMIX_COMMPACK_DUMMY_SYS) );
	memset( p_sys, 0, sizeof(NUTMIX_COMMPACK_DUMMY_SYS) );

	p_sys->pCommPacketLocal	= pCommPacketLocal;
	p_sys->commtbl_num		= listNum;
	p_sys->pCallBackWork	= pWork;

	p_sys->tcb = VWaitTCB_Add( NutMix_CommPack_DummySys_Main, p_sys, NUTMIX_COMM_PACK_DUMMY_TCB_PRI );

	return p_sys;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C���@����
 */
//-----------------------------------------------------------------------------
static void NutMix_CommPack_DummySys_Main( TCB_PTR tcb, void* p_work )
{
	NUTMIX_COMMPACK_DUMMY_SYS* p_sys = p_work;
	int i;

	// �R�[���o�b�N����
	for( i=0; i<NUTMIX_COMM_PACK_DUMMY_WORK_NUM; i++ ){

		// �f�[�^�����邩�`�F�b�N
		if( p_sys->work[i].init == TRUE ){
			p_sys->pCommPacketLocal[ p_sys->work[i].command ].callbackFunc( 
					NUTMIX_COMM_PACK_DUMMY_NETID, p_sys->work[i].size, 
					p_sys->work[i].data, p_sys->pCallBackWork );
			// ���[�N�N���A
			memset( &p_sys->work[i], 0, sizeof(NUTMIX_COMMPACK_DUMMY_WORK) );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�_�~�[�R�[���o�b�N�V�X�e���j��
 *
 *	@param	p_sys	�V�X�e�����[�N 
 */
//-----------------------------------------------------------------------------
static void NutMix_CommPack_DummySys_Delete( NUTMIX_COMMPACK_DUMMY_SYS* p_sys )
{
	TCB_Delete( p_sys->tcb );
	sys_FreeMemoryEz( p_sys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R�}���h�o�^
 *
 *	@param	p_sys		�V�X�e��
 *	@param	command		�R�}���h
 *	@param	data		�f�[�^
 *	@param	size		�T�C�Y
 *
 *	@retval	TRUE	����
 *	@retval	FALSE	���s
 */
//-----------------------------------------------------------------------------
static BOOL NutMix_CommPack_DummySys_SendData( NUTMIX_COMMPACK_DUMMY_SYS* p_sys, int command, const void* data, int size )
{
	int i;
	int check_size;
	NUTMIX_COMMPACK_DUMMY_WORK* p_work;

	// �󂢂Ă��郏�[�N�擾
	p_work = NULL;
	for( i=0; i<NUTMIX_COMM_PACK_DUMMY_WORK_NUM; i++ ){
		if( p_sys->work[i].init == FALSE ){
			p_work = &p_sys->work[i];
			break;
		}
	}
	// �o�^���I�[�o�[
	GF_ASSERT( p_work );


	// �R�}���h�̋��ʕ�����������
	command -= CS_COMMAND_MAX;

	// �o�^����R�}���h�̃T�C�Y�ƃf�[�^�T�C�Y�����������`�F�b�N
	check_size = p_sys->pCommPacketLocal[ command ].getSizeFunc();
	GF_ASSERT( check_size == size );

	// �_�~�[�o�b�t�@�T�C�Y��菬�������`�F�b�N
	GF_ASSERT( size < NUTMIX_COMM_PACK_DATABUFF_SIZE );

	// �f�[�^�ݒ�
	p_work->command = command;
	if( size > 0 ){	// �T�C�Y����������R�s�[
		memcpy( p_work->data, data, size );
	}
	p_work->size	= size;
	p_work->init	= TRUE;
	return TRUE;
}
