//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		poison_effect.c
 *	@brief		�Ŵ̪��
 *	@author		tomoya takahashi
 *	@data		2006.04.10
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "include/system/laster.h"
#include "include/system/snd_tool.h"

#define	__POISON_EFFECT_H_GLOBAL
#include "poison_effect.h"

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
#define POISON_COUNT		( 3 )		// ���춳��

#ifdef PM_DEBUG
static int POISON2_X = (3);	// ���̒l�����炷
static int POISON2_Y = (10);	// ���ꂢ�P�������������
void DEBUG_Poison( void );
#else
#define POISON2_X (3)	// ���̒l�����炷
#define POISON2_Y (10)	// ���ꂢ�P�������������
#endif
//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	���[�N	
//=====================================
typedef struct _POISON_EFFECT_WORK{
	u32		status;
	int		count;
	int		seq;
	u16		HblBuff0[ 192 ];
	u16		HblBuff1[ 192 ];
	LASTER_SYS_PTR p_laster;
	FIELD_HBLANK_SYS* p_hblanksys;
	FIELD_HBLANK_OBJ* p_hblank;
	BOOL	HblRef;		// HBLANK�Œl��ݒ肷�邩
	TCB_PTR	do_tcb;
	TCB_PTR vblank_tcb;
	TCB_PTR vwaitblank_tcb;
} ;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void PoisonEffTcb( TCB_PTR tcb, void* p_work );
static void PoisonEffVblankTcb( TCB_PTR tcb, void* p_work );
static void PoisonEffVWaitblankTcb( TCB_PTR tcb, void* p_work );
static void PoisonEffHBlank( POISON_EFFECT_WORK* p_poison );
static void PoisonMakeBuff( u16* buff, int key, int key_max );
static void PoisonEffeHBlankCallBack( FIELD_HBLANK_OBJ* p_obj, void* p_work );
static void POISON_EFFE_HBlank( POISON_EFFECT_WORK* p_poison );
static void POISON_EFFE_VBlank( POISON_EFFECT_WORK* p_poison );
static void PoisonWorkDoEnd( POISON_EFFECT_WORK* p_poison );

//----------------------------------------------------------------------------
/**
 *	@brief	�Ŵ̪�ă��[�N�쐬
 *
 *	@param	heap	�q�[�v
 *	@param	p_sys	�t�B�[���hH�u�����N�Ǘ��V�X�e��
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
POISON_EFFECT_WORK* POISON_EFFE_Init( u32 heap, FIELD_HBLANK_SYS* p_sys )
{
	POISON_EFFECT_WORK* p_poison;

	p_poison = sys_AllocMemory( heap, sizeof(POISON_EFFECT_WORK) );
	memset( p_poison, 0, sizeof(POISON_EFFECT_WORK) );

	// STANDBY���
	p_poison->status = POISON_EFFE_STANDBY;

	// ���X�^�[���[�N�쐬
	p_poison->p_laster = LASTER_Init( heap, p_poison->HblBuff0, p_poison->HblBuff1 );

	// H�u�����N�V�X�e�����[�N�ێ�
	p_poison->p_hblanksys = p_sys;

	return p_poison;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Ŵ̪�ă��[�N�j��
 *
 *	@param	p_poison	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void POISON_EFFE_Delete( POISON_EFFECT_WORK* p_poison )
{
	// TCB�j��
	if( p_poison->status == POISON_EFFE_DO ){
		PoisonWorkDoEnd( p_poison );
	}

	// ���X�^�[�j��
	LASTER_Delete( p_poison->p_laster );

	// �������j��
	sys_FreeMemoryEz( p_poison );
}
//----------------------------------------------------------------------------
/**
 *	@brief	�Ŵ̪�ăX�^�[�g
 *	
 *	@param	p_poison	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void POISON_EFFE_Start( POISON_EFFECT_WORK* p_poison )
{
	// ���d�Ăяo���`�F�b�N
	GF_ASSERT( p_poison->status == POISON_EFFE_STANDBY );

	// H�u�����N	������
	p_poison->p_hblank = FLDHBLANK_OBJ_Add( p_poison->p_hblanksys, PoisonEffeHBlankCallBack, p_poison );
	
	// �^�X�N�Ăяo��
	// �o�b�t�@�Ȃ��f�[�^����^�X�N
	p_poison->do_tcb = TCB_Add( PoisonEffTcb, p_poison, POISON_TCB_PRI );
	// �o�b�t�@���f�X�C�b�`�^�X�N	V�u�����N����
	p_poison->vblank_tcb = VIntrTCB_Add( PoisonEffVblankTcb, p_poison, POISON_TCB_PRI );
	//	�_�u���o�b�t�@�X�C�b�`�����^�X�N	V�u�����N���ԏI����
	p_poison->vwaitblank_tcb = VIntrTCB_Add( PoisonEffVWaitblankTcb, p_poison, POISON_TCB_PRI );

	// ������
	memset( p_poison->HblBuff0, 0, sizeof(u16) * 192 );
	memset( p_poison->HblBuff1, 0, sizeof(u16) * 192 );
	p_poison->status = POISON_EFFE_DO;
	p_poison->seq = 0;

	// ���Đ�
	Snd_SePlay( SE_POISON );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Ŵ̪�ď�Ԏ擾
 *
 *	@param	cp_poison ���[�N
 *
 *	@retval	POISON_EFFE_STANDBY		�J�n�҂�
 *	@retval	POISON_EFFE_DO			���s��
 */         
//-----------------------------------------------------------------------------
u32 POISON_EFFE_GetStatus( const POISON_EFFECT_WORK* cp_poison )
{
	return cp_poison->status;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�^�X�N���[�N
 *
 *	@param	tcb		TCB�f�[�^
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PoisonEffTcb( TCB_PTR tcb, void* p_work )
{
	POISON_EFFECT_WORK* data = p_work;
	u16* buff;


	
	switch( data->seq ){
	case 0:		// ������
		data->count = POISON_COUNT;
		data->seq++;
		break;

	case 1:		// ���Z
		data->count --;
		buff = LASTER_GetWriteBuff( data->p_laster );
		PoisonMakeBuff( buff, POISON_COUNT - data->count, POISON_COUNT );
		if( data->count <= 0 ){
			data->count = POISON_COUNT;
			data->seq++;
		}
		break;
	
	case 2:		// ���Z
		data->count --;
		buff = LASTER_GetWriteBuff( data->p_laster );
		PoisonMakeBuff( buff, data->count, POISON_COUNT );
		if( data->count <= 0 ){
			data->seq++;
		}
		break;

	// �I��
	case 3:
		PoisonWorkDoEnd( data );
		// BG0�ʂ�H�����X�N���[���ݒ�
		G3X_SetHOffset( 0 );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	HBlank����
 *
 *	@param	p_poison ���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PoisonEffHBlank( POISON_EFFECT_WORK* p_poison )
{
	const u16* cp_buff;
	int count;
	count = GX_GetVCount();
	cp_buff = LASTER_GetReadBuff( p_poison->p_laster );
	if( count < 192 ){
		count++;	// ���̍����̃f�[�^��ݒ�
		if( count >= 192 ){
			count -= 192;
		}
		
		// BG0�ʂ�H�����X�N���[���ݒ�
		if( GX_IsHBlank() ){
			G3X_SetHOffset( cp_buff[ count ] );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	key�ɑΉ������l���o�b�t�@�ɒǉ�
 *
 *	@param	buff		�o�b�t�@
 *	@param	key			�L�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PoisonMakeBuff( u16* buff, int key, int key_max )
{
	int i;
	int calc_x;
	BOOL switch_f = TRUE;


	calc_x = POISON2_X * key;
	calc_x = calc_x / key_max;

	for( i=0; i<192; i++ ){

		if( (i % POISON2_Y) == 0 ){
			switch_f ^= 1;
		}

		if( switch_f ){
			buff[ i ] = calc_x;
		}else{
			buff[ i ] = -calc_x;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	VBlankTCB
 *
 *	@param	tcb		TCB���[�N
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PoisonEffVblankTcb( TCB_PTR tcb, void* p_work )
{
	POISON_EFFECT_WORK* data = p_work;

	// ���̎��_��1�񔽉f�������̂�
	// ����1�V���N�͔��f�����Ȃ�
	data->HblRef = FALSE;

	// BG0�ʂ�H�����X�N���[���ݒ�
	G3X_SetHOffset( 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	H�u�����N����
 *
 *	@param	p_obj		H�u�����N�I�u�W�F�N�g
 *	@param	p_work		���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PoisonEffeHBlankCallBack( FIELD_HBLANK_OBJ* p_obj, void* p_work )
{
	POISON_EFFECT_WORK* p_poison = p_work;
	POISON_EFFE_HBlank( p_poison );
}
//----------------------------------------------------------------------------
/**
 *	@brief	H�u�����N���ԏ���
 *
 *	@param	p_poison �Ń��[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void POISON_EFFE_HBlank( POISON_EFFECT_WORK* p_poison )
{
	if( p_poison->status == POISON_EFFE_DO ){

		// ���f��1�V���N���ɂ���
		// ���������ۂ��Ȃ���ʂ�_��
		if( p_poison->HblRef == TRUE ){
			PoisonEffHBlank( p_poison );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	V�u�����N�҂���^�X�N����
 *
 *	@param	tcb		�^�X�N���[�N
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PoisonEffVWaitblankTcb( TCB_PTR tcb, void* p_work )
{
	POISON_EFFECT_WORK* p_poison = p_work;
	POISON_EFFE_VBlank( p_poison );
}
//----------------------------------------------------------------------------
/**
 *	@brief	V�u�����N���ԏ���
 *
 *	@param	p_poison	�Ń��[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void POISON_EFFE_VBlank( POISON_EFFECT_WORK* p_poison )
{
	if( p_poison->status == POISON_EFFE_DO ){
		LASTER_VBlank( p_poison->p_laster );
		p_poison->HblRef = TRUE;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Ŵ̪�Ď��s��ԃN���A
 *
 *	@param	p_poison	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PoisonWorkDoEnd( POISON_EFFECT_WORK* p_poison )
{
	// H�u�����N�����j��
	FLDHBLANK_OBJ_Delete( p_poison->p_hblank );
	p_poison->p_hblank = NULL;
	
	TCB_Delete( p_poison->do_tcb );
	p_poison->do_tcb = NULL;
	TCB_Delete( p_poison->vblank_tcb );
	p_poison->vblank_tcb = NULL;
	TCB_Delete( p_poison->vwaitblank_tcb );
	p_poison->vwaitblank_tcb = NULL;
	p_poison->status = POISON_EFFE_STANDBY;

}


#ifdef PM_DEBUG
void DEBUG_Poison( void )
{
	if( sys.cont & PAD_BUTTON_R ){
		if( sys.trg & PAD_BUTTON_Y ){
			POISON2_X --;
			OS_Printf( "x�� %d \n", POISON2_X );
		}else if( sys.trg & PAD_BUTTON_A ){
			POISON2_X ++;
			OS_Printf( "x�� %d \n", POISON2_X );
		}
	}
	if( sys.cont & PAD_BUTTON_L ){
		if( sys.trg & PAD_BUTTON_Y ){
			POISON2_Y --;
			OS_Printf( "y�� %d \n", POISON2_Y );
		}else if( sys.trg & PAD_BUTTON_A ){
			POISON2_Y ++;
			OS_Printf( "y�� %d \n", POISON2_Y );
		}
	}
}
#endif

