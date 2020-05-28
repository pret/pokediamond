//******************************************************************************
/**
 * 
 * @file	eoa.c
 * @brief	�G�t�F�N�g�I�u�W�F�N�g�A�N�^�[
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "eoa.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
//	debug
//--------------------------------------------------------------
#ifdef PM_DEBUG
//#define DEBUG_EOA_USE_COUNT		//��`��EOA�g�p����OS_Print()�f���o��
#endif

//--------------------------------------------------------------
//	EOA�X�e�[�^�X�r�b�g
//--------------------------------------------------------------
#define EOA_STA_BIT_NON (0)									///<����
#define EOA_STA_BIT_USE (1<<0)								///<�g�p��

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	EOA�\����
//--------------------------------------------------------------
typedef struct _TAG_EOA
{
	u32 status_bit;
	int add_param;
	int answer;
	const void *add_ptr;
	TCB_PTR tcb;
	CONST_EOA_SYS_PTR es;
	int x;
	int y;
	int z;
	VecFx32 matrix;
	
	u8 work[EOA_LOCAL_WORK_SIZE];
	
	EOA_PROC_INIT proc_init;
	EOA_PROC_MOVE proc_move;
	EOA_PROC_DRAW proc_draw;
	EOA_PROC_DEL  proc_del;
	EOA_PROC_PUSH proc_push;
	EOA_PROC_POP  proc_pop;
}EOA;

#define EOA_SIZE (sizeof(EOA))	///<EOA�T�C�Y

//--------------------------------------------------------------
///	EOA_SYS�\����
//--------------------------------------------------------------
typedef struct _TAG_EOA_SYS
{
	int max;
	int add_count;
	int heap_id;
	EOA_PTR eoa;
}EOA_SYS;

#define EOA_SYS_SIZE (sizeof(EOA_SYS))	///<EOA_SYS�T�C�Y

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static TCB_PTR eoa_MoveProcTCBAdd( EOA_PTR eoa, int pri );
static void eoa_MoveProcTCB( TCB_PTR tcb, void *wk );

static EOA_SYS_PTR eoa_SysAllocMemory( int heap_id );
static void eoa_SysFreeMemory( EOA_SYS_PTR es );
static EOA_PTR eoa_AllocMemory( int heap_id, int max );
static void eoa_FreeMemory( EOA_SYS_PTR es );
static void eoa_Clear( EOA_PTR eoa );

static int eoa_SysEoaMaxGet( CONST_EOA_SYS_PTR es );
static EOA_PTR eoa_SysEoaGet( CONST_EOA_SYS_PTR es );

static void eoa_StatusBit_UseSet( EOA_PTR eoa );
static void eoa_StatusBit_Set( EOA_PTR eoa, u32 bit );
static void eoa_AddParamSet( EOA_PTR eoa, int prm );
static void eoa_AddPtrSet( EOA_PTR eoa, const void *ptr );
static void eoa_TCBSet( EOA_PTR eoa, TCB_PTR tcb );
static TCB_PTR eoa_TCBGet( EOA_PTR eoa );
static void eoa_EoaSysSet( EOA_PTR eoa, CONST_EOA_SYS_PTR es );

//==============================================================================
//	eoa	�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA������
 * @param	heap_id		EOA���[�N�Ɏg�p����q�[�vID
 * @param	max			EOA�ő吔
 * @retval	EOA_SYS_PTR	�ǉ����ꂽEOA_SYS_PTR
 */
//--------------------------------------------------------------
EOA_SYS_PTR EOA_SysInit( int heap_id, int max )
{
	EOA_SYS_PTR es;
	
	es = eoa_SysAllocMemory( heap_id );
	es->eoa = eoa_AllocMemory( heap_id, max );
	
	es->max = max;
	es->heap_id = heap_id;
	
	return( es );
}

//--------------------------------------------------------------
/**
 * EOA�V�X�e���폜
 * @param	es		EOA_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_SysDelete( EOA_SYS_PTR es )
{
	eoa_FreeMemory( es );
	eoa_SysFreeMemory( es );
}

//--------------------------------------------------------------
/**
 * EOA�S�폜&EOA�V�X�e���폜
 * @param	es		EOA_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_SysDeleteAll( EOA_SYS_PTR es )
{
	EOA_DeleteAll( es );
	EOA_SysDelete( es );
}

//==============================================================================
//	eoa	�ǉ��폜
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA�ǉ�
 * @param	es			EOA_SYS_PTR
 * @param	EOA_H		�ǉ�������񂪓Z�߂�ꂽEOA_H
 * @param	mtx			�����ʒu
 * @param	prm			�ǉ�����EOA�֎w�肷��p�����^
 * @param	ptr			�ǉ�����EOA�֎w�肷��|�C���^
 * @param	pri			�ǉ�����EOA�̓���v���C�I���e�B
 * @retval	EOA_PTR		�ǉ����ꂽEOA_PTR NULL=�ǉ����s
 */
//--------------------------------------------------------------
EOA_PTR EOA_Add( EOA_SYS_PTR es, const EOA_H *head,
		const VecFx32 *mtx, int prm, const void *ptr, int pri )
{
	int i,max;
	EOA_PTR eoa;
	TCB_PTR tcb;
	
	i = 0;
	max = eoa_SysEoaMaxGet( es );
	eoa = eoa_SysEoaGet( es );
	
	do{
		if( EOA_StatusBit_UseCheck(eoa) == FALSE ){
			break;
		}
		
		i++;
		eoa++;
	}while( i < max );
	
	if( i >= max ){
		OS_Printf( "EOA MAX!! EOA USE COUNT 0x%x\n", es->add_count );
		return( NULL );
	}
	
	eoa_StatusBit_UseSet( eoa );
	eoa_AddParamSet( eoa, prm );
	eoa_AddPtrSet( eoa, ptr );
	eoa_EoaSysSet( eoa, es );
	EOA_MatrixSet( eoa, mtx );
	EOA_LocalWorkInit( eoa, head->work_size );
	
	EOA_InitProcSet( eoa, head->proc_init );
	EOA_DeleteProcSet( eoa, head->proc_del );
	EOA_MoveProcSet( eoa, head->proc_move );
	EOA_DrawProcSet( eoa, head->proc_draw );
	EOA_PushProcSet( eoa, head->proc_push );
	EOA_PopProcSet( eoa, head->proc_pop );
	
	tcb = eoa_MoveProcTCBAdd( eoa, pri );
	
	if( tcb == NULL ){
		eoa_Clear( eoa );
		return( NULL );
	}
	
	eoa_TCBSet( eoa, tcb );
	
	if( EOA_InitProcCall(eoa) == FALSE ){
		TCB_Delete( tcb );
		eoa_Clear( eoa );
		return( NULL );
	}
	
	es->add_count++;

#ifdef DEBUG_EOA_USE_COUNT
	{
		int space = es->max - es->add_count;
		OS_Printf("EOA���ǉ�����܂���...");
		OS_Printf("EOA�g�p��=%d, EOA��=%d, EOA�ő吔=%d\n",es->add_count,space,es->max);
	}
#endif
	
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA�ǉ� EOA_H_NPP�^ �ޔ��A���A�֐��̓_�~�[�֐��ɂȂ�
 * @param	es			EOA_SYS_PTR
 * @param	EOA_H_NPP	�ǉ�������񂪓Z�߂�ꂽEOA_H_NPP
 * @param	mtx			�����ʒu
 * @param	prm			�ǉ�����EOA�֎w�肷��p�����^
 * @param	ptr			�ǉ�����EOA�֎w�肷��|�C���^
 * @param	pri			�ǉ�����EOA�̓���v���C�I���e�B
 * @retval	EOA_PTR		�ǉ����ꂽEOA_PTR NULL=�ǉ����s
 */
//--------------------------------------------------------------
EOA_PTR EOA_Add_NPP( EOA_SYS_PTR es, const EOA_H_NPP *head,
		const VecFx32 *mtx, int prm, const void *ptr, int pri )
{
	EOA_H eh;
	
	*(EOA_H_NPP *)&eh = *head;
	eh.proc_push = EOA_PushProcDummy;
	eh.proc_pop = EOA_PopProcDummy;
	
	return( EOA_Add(es,&eh,mtx,prm,ptr,pri) );
}

//--------------------------------------------------------------
/**
 * EOA�폜
 * @param	eoa			�폜����EOA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_Delete( EOA_PTR eoa )
{
	GF_ASSERT( eoa != NULL && "EOA_Delete()eoa==NULL���n����܂���" );
	
	if( EOA_StatusBit_UseCheck(eoa) == FALSE ){
		return;
	}
	
	EOA_DeleteProcCall( eoa );
	
	{
		EOA_SYS_PTR es = (EOA_SYS_PTR)eoa->es;
		es->add_count--;
	}
	
#ifdef DEBUG_EOA_USE_COUNT
	{
		EOA_SYS_PTR es = (EOA_SYS_PTR)eoa->es;
		int space = es->max - es->add_count;
		OS_Printf("EOA���폜����܂���...");
		OS_Printf("EOA�g�p��=%d, EOA��=%d, EOA�ő吔=%d\n",es->add_count,space,es->max);
	}
#endif
	
	{
		TCB_PTR tcb = eoa_TCBGet( eoa );
		
		if( tcb != NULL ){
			TCB_Delete( tcb );
		}
	}
	
	eoa_Clear( eoa );
}

//old eoa�̒l�����̂܂ܐM�p
#if 0
void EOA_Delete( EOA_PTR eoa )
{
	GF_ASSERT( eoa != NULL && "EOA_Delete()eoa==NULL���n����܂���" );
	
	EOA_DeleteProcCall( eoa );
	
	{
		EOA_SYS_PTR es = (EOA_SYS_PTR)eoa->es;
		es->add_count--;
	}
	
#ifdef DEBUG_EOA_USE_COUNT
	{
		EOA_SYS_PTR es = (EOA_SYS_PTR)eoa->es;
		int space = es->max - es->add_count;
		OS_Printf("EOA���폜����܂���...");
		OS_Printf("EOA�g�p��=%d, EOA��=%d, EOA�ő吔=%d\n",es->add_count,space,es->max);
	}
#endif
	
	TCB_Delete( eoa_TCBGet(eoa) );
	eoa_Clear( eoa );
}
#endif

//--------------------------------------------------------------
/**
 * �������Ă���S�Ă�EOA�ɍ폜����
 * @param	es		EOA_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_DeleteAll( EOA_SYS_PTR es )
{
	int max;
	EOA_PTR eoa;
	
	max = eoa_SysEoaMaxGet( es );
	eoa = eoa_SysEoaGet( es );
	
	do{
		if( EOA_StatusBit_UseCheck(eoa) == TRUE ){
			EOA_Delete( eoa );
		}
		
		eoa++; max--;
	}while( max );
}

//==============================================================================
//	eoa �`��
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA �`��֐��Ăяo��
 * @param	es		EOA_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_SysDraw( EOA_SYS_PTR es )
{
	int max;
	EOA_PTR eoa;
	
	max = eoa_SysEoaMaxGet( es );
	eoa = eoa_SysEoaGet( es );
	
	do{
		if( EOA_StatusBit_UseCheck(eoa) == TRUE ){
			EOA_DrawProcCall( eoa );
		}
		
		eoa++;
		max--;
	}while( max );
}

//==============================================================================
//	eoa	TCB����
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA TCB����֐��Z�b�g
 * @param	eoa		EOA_PTR
 * @param	pri		TCB�v���C�I���e�B
 * @retval	nothing
 */
//--------------------------------------------------------------
static TCB_PTR eoa_MoveProcTCBAdd( EOA_PTR eoa, int pri )
{
	TCB_PTR tcb;
	
	tcb = TCB_Add( eoa_MoveProcTCB, eoa, pri );
	GF_ASSERT( tcb != NULL && "eoa_MoveProcTCBAdd TCB��t" );
	
	return( tcb );
}

//--------------------------------------------------------------
/**
 * EOA TCB����֐�
 * @param	tcb	TCB_PTR
 * @param	wk	tcb work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoa_MoveProcTCB( TCB_PTR tcb, void *wk )
{
	EOA_PTR eoa;
	
	eoa = wk;
	EOA_MoveProcCall( eoa );
}

//==============================================================================
//	eoa	�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA�V�X�e���������m��
 * @param	heap_id			HEAP ID
 * @retval	EOA_SYS_PTR		�m�ۂ���EOA_SYS_PTR
 */
//--------------------------------------------------------------
static EOA_SYS_PTR eoa_SysAllocMemory( int heap_id )
{
	EOA_SYS_PTR es;
	
	es = sys_AllocMemory( heap_id, EOA_SYS_SIZE );
	GF_ASSERT( es != NULL && "eoa_SysAllocMemory�������m�ۃG���[" );
	
	memset( es, 0, EOA_SYS_SIZE );
	return( es );
}

//--------------------------------------------------------------
/**
 * EOA�V�X�e���������J��
 * @param	es			EOA_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoa_SysFreeMemory( EOA_SYS_PTR es )
{
	sys_FreeMemory( es->heap_id, es );
}

//--------------------------------------------------------------
/**
 * EOA�������m��
 * @param	heap_id		HEAP ID
 * @param	max			EOA�ő吔
 * @retval	eoa			�m�ۂ���EOA_PTR
 */
//--------------------------------------------------------------
static EOA_PTR eoa_AllocMemory( int heap_id, int max )
{
	EOA_PTR eoa;
	
	max *= EOA_SIZE;
	eoa = sys_AllocMemory( heap_id, max );
	GF_ASSERT( eoa != NULL && "eoa_AllocMemory�������m�ۃG���[" );
	
	memset( eoa, 0, max );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA�������J��
 * @param	es			EOA_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoa_FreeMemory( EOA_SYS_PTR es )
{
	sys_FreeMemory( es->heap_id, es->eoa );
}

//--------------------------------------------------------------
/**
 * EOA�N���A
 * @param	eoa			EOA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoa_Clear( EOA_PTR eoa )
{
	memset( eoa, 0, EOA_SIZE );
	EOA_InitProcSet( eoa, EOA_InitProcDummy );
	EOA_DeleteProcSet( eoa, EOA_DeleteProcDummy );
	EOA_MoveProcSet( eoa, EOA_MoveProcDummy );
	EOA_DrawProcSet( eoa, EOA_DrawProcDummy );
	EOA_PushProcSet( eoa, EOA_PushProcDummy );
	EOA_PopProcSet( eoa, EOA_PopProcDummy );
}

//old 0 clear�̂�
#if 0
static void eoa_Clear( EOA_PTR eoa )
{
	memset( eoa, 0, EOA_SIZE );
}
#endif

//==============================================================================
//	EOA_SYS�Q��
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA�ő吔�擾
 * @param	es		EOA_SYS_PTR
 * @retval	int		�ő吔
 */
//--------------------------------------------------------------
static int eoa_SysEoaMaxGet( CONST_EOA_SYS_PTR es )
{
	return( es->max );
}

//--------------------------------------------------------------
/**
 * EOA���[�N�|�C���^�擾
 * @param	es		EOA_SYS_PTR
 * @retval	EOA_PTR	EOA_PTR
 */
//--------------------------------------------------------------
static EOA_PTR eoa_SysEoaGet( CONST_EOA_SYS_PTR es )
{
	return( es->eoa );
}

//==============================================================================
//	eoa	�Q��
//==============================================================================
//--------------------------------------------------------------
/**
 * eoa �g�p���`�F�b�N
 * @param	eoa		EOA_PTR
 * @retval	int		TRUE=�g�p���BFALSE=���g�p
 */
//--------------------------------------------------------------
int EOA_StatusBit_UseCheck( CONST_EOA_PTR eoa )
{
	if( (eoa->status_bit & EOA_STA_BIT_USE) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * eoa �X�e�[�^�X�r�b�g�@�g�p���Z�b�g
 * @param	eoa		EOA_PTR
 * @retval	int		TRUE=�g�p���BFALSE=���g�p
 */
//--------------------------------------------------------------
static void eoa_StatusBit_UseSet( EOA_PTR eoa )
{
	eoa->status_bit |= EOA_STA_BIT_USE;
}

//--------------------------------------------------------------
/**
 * eoa �X�e�[�^�X�r�b�g�@�Z�b�g
 * @param	eoa		EOA_PTR
 * @param	bit		EOA_STA_BIT_NON��
 * @retval	int		TRUE=�g�p���BFALSE=���g�p
 */
//--------------------------------------------------------------
static void eoa_StatusBit_Set( EOA_PTR eoa, u32 bit )
{
	eoa->status_bit = bit;
}

//--------------------------------------------------------------
/**
 * �������֐��Z�b�g
 * @param	eoa		EOA_PTR
 * @param	proc	EOA_PROC_INIT
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_InitProcSet( EOA_PTR eoa, EOA_PROC_INIT proc )
{
	eoa->proc_init = proc;
}

//--------------------------------------------------------------
/**
 * �������֐��Ăяo��
 * @param	eoa		EOA_PTR
 * @retval	int		TRUE=���평�����@FALSE=���������s
 */
//--------------------------------------------------------------
int EOA_InitProcCall( EOA_PTR eoa )
{
	void *work = EOA_LocalWorkGet( eoa );
	return( eoa->proc_init(eoa,work) );
}

//--------------------------------------------------------------
/**
 * ����֐��Z�b�g
 * @param	eoa		EOA_PTR
 * @param	proc	EOA_PROC_MOVE
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_MoveProcSet( EOA_PTR eoa, EOA_PROC_MOVE proc )
{
	eoa->proc_move = proc;
}

//--------------------------------------------------------------
/**
 * ����֐��Ăяo��
 * @param	eoa		EOA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_MoveProcCall( EOA_PTR eoa )
{
	void *work = EOA_LocalWorkGet( eoa );
	eoa->proc_move( eoa, work );
}

//--------------------------------------------------------------
/**
 * �`��֐��Z�b�g
 * @param	eoa		EOA_PTR
 * @param	proc	EOA_PROC_MOVE
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_DrawProcSet( EOA_PTR eoa, EOA_PROC_DRAW proc )
{
	eoa->proc_draw = proc;
}

//--------------------------------------------------------------
/**
 * �`��֐��Ăяo��
 * @param	eoa		EOA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_DrawProcCall( EOA_PTR eoa )
{
	void *work = EOA_LocalWorkGet( eoa );
	eoa->proc_draw( eoa, work );
}

//--------------------------------------------------------------
/**
 * �폜�֐��Z�b�g
 * @param	eoa		EOA_PTR
 * @param	proc	EOA_PROC_DEL
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_DeleteProcSet( EOA_PTR eoa, EOA_PROC_DEL proc )
{
	eoa->proc_del = proc;
}

//--------------------------------------------------------------
/**
 * �폜�֐��Ăяo��
 * @param	eoa		EOA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_DeleteProcCall( EOA_PTR eoa )
{
	void *work = EOA_LocalWorkGet( eoa );
	eoa->proc_del( eoa, work );
}

//--------------------------------------------------------------
/**
 * �ޔ��֐��Z�b�g
 * @param	eoa		EOA_PTR
 * @param	proc	EOA_PROC_PUSH
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_PushProcSet( EOA_PTR eoa, EOA_PROC_PUSH proc )
{
	eoa->proc_push = proc;
}

//--------------------------------------------------------------
/**
 * �ޔ��֐��Ăяo��
 * @param	eoa		EOA_PTR
 * @param	proc	EOA_PROC_PUSH
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_PushProcCall( EOA_PTR eoa )
{
	void *work = EOA_LocalWorkGet( eoa );
	eoa->proc_push( eoa, work );
}

//--------------------------------------------------------------
/**
 * ���A�֐��Z�b�g
 * @param	eoa		EOA_PTR
 * @param	proc	EOA_PROC_POP
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_PopProcSet( EOA_PTR eoa, EOA_PROC_POP proc )
{
	eoa->proc_pop = proc;
}

//--------------------------------------------------------------
/**
 * �ޔ��֐��Ăяo��
 * @param	eoa		EOA_PTR
 * @param	proc	EOA_PROC_POP
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_PopProcCall( EOA_PTR eoa )
{
	void *work = EOA_LocalWorkGet( eoa );
	eoa->proc_pop( eoa, work );
}

//--------------------------------------------------------------
/**
 * ���[�J�����[�N�擾
 * @param	eoa		EOA_PTR
 * @retval	void*	���[�N*
 */
//--------------------------------------------------------------
void * EOA_LocalWorkGet( EOA_PTR eoa )
{
	return( eoa->work );
}

//--------------------------------------------------------------
/**
 * ���[�J�����[�N������
 * @param	eoa		EOA_PTR
 * @param	size	�������T�C�Y�@EOA_LOCAL_WORK_SIZE�ȏ�=ASSERT
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_LocalWorkInit( EOA_PTR eoa, int size )
{
	void *work;
	
#ifdef PM_DEBUG
	if( size > EOA_LOCAL_WORK_SIZE ){
		OS_Printf( "EOA ���[�N�T�C�Y�I�[�o�[" );
		OS_Printf( "�ő�T�C�Y=0x%x, �w��T�C�Y=0x%x\n", EOA_LOCAL_WORK_SIZE, size );
		GF_ASSERT( 0 );
	}
#endif
	
	work = EOA_LocalWorkGet( eoa );
	memset( work, 0, size );
}

//--------------------------------------------------------------
/**
 * �ǉ��w��p�����^�Z�b�g
 * @param	eoa		EOA_PTR
 * @param	prm		�p�����^
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoa_AddParamSet( EOA_PTR eoa, int prm )
{
	eoa->add_param = prm;
}

//--------------------------------------------------------------
/**
 * �ǉ��w��p�����^�擾 
 * @param	eoa		EOA_PTR
 * @retval	int		EOA_Add()���Ɏw�肳�ꂽ�p�����^
 */
//--------------------------------------------------------------
int EOA_AddParamGet( CONST_EOA_PTR eoa )
{
	return( eoa->add_param );
}

//--------------------------------------------------------------
/**
 * �ǉ��w��|�C���^�Z�b�g
 * @param	eoa		EOA_PTR
 * @param	ptr		�|�C���^
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoa_AddPtrSet( EOA_PTR eoa, const void *ptr )
{
	eoa->add_ptr = ptr;
}

//--------------------------------------------------------------
/**
 * �ǉ��w��|�C���^�擾
 * @param	eoa		EOA_PTR
 * @retval	void*	EOA_Add()���Ɏw�肳�ꂽ�|�C���^
 */
//--------------------------------------------------------------
const void * EOA_AddPtrGet( CONST_EOA_PTR eoa )
{
	return( eoa->add_ptr );
}

//--------------------------------------------------------------
/**
 * �񓚃Z�b�g
 * @param	eoa			EOA_PTR
 * @param	answer		����
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_AnswerSet( EOA_PTR eoa, int answer )
{
	eoa->answer = answer;
}

//--------------------------------------------------------------
/**
 * �񓚎擾
 * @param	eoa			EOA_PTR
 * @retval	int			��
 */
//--------------------------------------------------------------
int EOA_AnswerGet( CONST_EOA_PTR eoa )
{
	return( eoa->answer );
}

//--------------------------------------------------------------
/**
 * tcb�|�C���^�Z�b�g
 * @param	eoa			EOA_PTR
 * @param	tcb			TCB_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoa_TCBSet( EOA_PTR eoa, TCB_PTR tcb )
{
	eoa->tcb = tcb;
}

//--------------------------------------------------------------
/**
 * tcb�|�C���^�擾
 * @param	eoa			EOA_PTR
 * @retval	tcb			TCB_PTR
 */
//--------------------------------------------------------------
static TCB_PTR eoa_TCBGet( EOA_PTR eoa )
{
	return( eoa->tcb );
}

//--------------------------------------------------------------
/**
 * EOA_SYS_PTR�Z�b�g
 * @param	eoa		EOA_PTR
 * @param	es		EOA_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoa_EoaSysSet( EOA_PTR eoa, CONST_EOA_SYS_PTR es )
{
	eoa->es = es;
}

//--------------------------------------------------------------
/**
 * EOA_SYS_PTR�擾
 * @param	eoa		EOA_PTR
 * @retval	es		EOA_SYS_PTR
 */
//--------------------------------------------------------------
CONST_EOA_SYS_PTR EOA_EoaSysGet( EOA_PTR eoa )
{
	return( eoa->es );
}

//--------------------------------------------------------------
/**
 * X���W�Z�b�g
 * @param	eoa		EOA_PTR
 * @param	x		���W
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_XSet( EOA_PTR eoa, int x )
{
	eoa->x = x;
}

//--------------------------------------------------------------
/**
 * X���W�擾
 * @param	eoa		EOA_PTR
 * @retval	int		���W
 */
//--------------------------------------------------------------
int EOA_XGet( EOA_PTR eoa )
{
	return( eoa->x );
}

//--------------------------------------------------------------
/**
 * Y���W�Z�b�g
 * @param	eoa		EOA_PTR
 * @param	y		���W
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_YSet( EOA_PTR eoa, int y )
{
	eoa->y = y;
}

//--------------------------------------------------------------
/**
 * Y���W�擾
 * @param	eoa		EOA_PTR
 * @retval	int		���W
 */
//--------------------------------------------------------------
int EOA_YGet( EOA_PTR eoa )
{
	return( eoa->y );
}

//--------------------------------------------------------------
/**
 * Z���W�Z�b�g
 * @param	eoa		EOA_PTR
 * @param	z		���W
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_ZSet( EOA_PTR eoa, int z )
{
	eoa->z = z;
}

//--------------------------------------------------------------
/**
 * Z���W�擾
 * @param	eoa		EOA_PTR
 * @retval	int		���W
 */
//--------------------------------------------------------------
int EOA_ZGet( EOA_PTR eoa )
{
	return( eoa->z );
}

//--------------------------------------------------------------
/**
 * �}�g���N�X���W�Z�b�g
 * @param	eoa		EOA_PTR
 * @param	mtx		�Z�b�g������W
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_MatrixSet( EOA_PTR eoa, const VecFx32 *mtx )
{
	eoa->matrix = *mtx;
}

//--------------------------------------------------------------
/**
 * �}�g���N�X���W�擾
 * @param	eoa		EOA_PTR
 * @param	mtx		�Z�b�g������W
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_MatrixGet( EOA_PTR eoa, VecFx32 *mtx )
{
	*mtx = eoa->matrix;
}

//==============================================================================
//	�_�~�[�֐�
//==============================================================================
//--------------------------------------------------------------
/**
 * �������֐��@�_�~�[
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE
 */
//--------------------------------------------------------------
int EOA_InitProcDummy( EOA_PTR eoa, void *wk )
{
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * ����֐��@�_�~�[
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_MoveProcDummy( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * �`��֐��@�_�~�[
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_DrawProcDummy( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * �폜�֐��@�_�~�[
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_DeleteProcDummy( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * �ޔ��֐��@�_�~�[
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_PushProcDummy( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * ���A�֐��@�_�~�[
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
void EOA_PopProcDummy( EOA_PTR eoa, void *wk )
{
}

