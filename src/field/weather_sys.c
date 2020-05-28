//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		weather_sys.c
 *@brief	���V�C�V�X�e��
 *@author	tomoya takahashi
 *@data		2005.04.25
 *
 *	���̃V�X�e���́AOAM�@�t�H�O�@BG�Q�@���g�p���܂��B
 *
 *	�V�V��o�^�菇
 *	�P�F�w�b�_�̗񋓑̂ɐV�V��̒萔����ǉ�
 *	�Q�F�O���t�B�b�N�i�Z���ABG�j��ǉ�����Ƃ��́A�V�C�O���t�B�b�N�t�@�C���e�[�u���ɒǉ�
 *	�R�F�R���g���[���^�X�N�֐����쐬���AWeatherSysData�e�[�u���Ƀf�[�^��ݒ�
 *	�S�F�R���g���[���^�X�N�֐����́A�V�[�P���X�ŊǗ����邱�Ƃ����܂�ɂ��Ă���̂ŁA
 *	�@�@�������A�t�F�[�h�C���A���C���A�t�F�[�h�A�E�g�A�j���̃V�[�P���X�ɕ����ēV����쐬
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include "common.h"
#include "fieldsys.h"
#include "fieldmap.h"
#include "fieldmap_work.h"
#include "field_glb_state.h"

#include "system/clact_util.h"
#include "system/render_oam.h"

#include "field/weather_sys.naix"

#include "system/arc_util.h"
#include "field_hblank.h"

#include "system/snd_tool.h"
#include "system/laster.h"

#define __WEATHER_SYS_H_GLOBAL
#include "weather_sys.h"


#define USE_HEAPID	( HEAPID_FIELD )
//#define USE_HEAPID	( HEAPID_WEATHER )



//-----------------------------------------------------------------------------
/**
 *
 *					�V�C�Ǘ��V�X�e��
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *			�萔��`
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//		�V�C�ύX�^�X�N�萔
//=====================================
enum{
	WEATHER_CHENGE_NOW_FADEOUT_START,
	WEATHER_CHENGE_NOW_FADEOUT,
	WEATHER_CHENGE_NEXT_INIT_START,
	WEATHER_CHENGE_NEXT_INIT,
	WEATHER_CHENGE_NEXT_FADEIN_START,
	WEATHER_CHENGE_END,
	
	WEATHER_CHENGE_NONE,		// ���N�G�X�g�������
};

//-------------------------------------
//		�V�C�ύX�^�X�N�萔
//=====================================
enum{
	WEATHER_CHENGE_WL_NEXT_INIT_START,
	WEATHER_CHENGE_WL_NEXT_INIT,
	WEATHER_CHENGE_WL_NOW_FADEOUTIN_START,
	WEATHER_CHENGE_WL_NOW_FADEOUTIN,
	WEATHER_CHENGE_WL_END,
};

//-------------------------------------
//	�V�C�ύX���
//=====================================
enum{
	WEATHER_CHANGE_SINGLE_TASK,
	WEATHER_CHANGE_MULTI_TASK,
};


#define WEATHER_TCB_CHG_PRI			( 0 )
#define WEATHER_TCB_DIV_LOAD_PRI	( 1 )
#define WEATHER_TCB_CIRCLEINIT_PRI	( 120 )
#define WEATHER_TCB_CIRCLEEND_PRI	( 128 )


#define WEATHER_SND_FADE_OUT_SYNC	( 0 )


//-----------------------------------------------------------------------------
/**
 *			�\���̐錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�V�C�Ǘ��V�X�e��
//	
//=====================================
typedef struct _WEATHER_MANAGER{
	// �V�C�V�X�e��
	WEATHER_CONT_PTR	weather_sys;

	// �Ǘ��f�[�^
	int now_play_weather;	// ���s���̓V�C

	// �ύX�t�F�[�h�p�f�[�^
	int next_play_weather;	// ���Ɏ��s����V�C
	int chenge_seq;			// �V�C�ύX�V�[�P���X
	int booking_weather;		// �ύX��ݒ�V�C	�i�V�C�ύX���ɓV�C�ύX���N�G�X�g�������Ƃ��Ɋi�[�j
	TCB_PTR tcb;			// �V�C�ύXTCB
} WEATHER_MANAGER;

//-----------------------------------------------------------------------------
/**
 *			�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
static void WEATHER_ChangeTcb( TCB_PTR tcb, void* work );
static void WEATHER_ChangeWithLastTcb( TCB_PTR tcb, void* work );
static int WEATHER_ChangeReqFuncNoGet( int now_weather, int next_weather );

//-----------------------------------------------------------------------------
/**
 *		������
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	�V�C�Ŏg�p����q�[�v�̈�̍쐬
 *
 *	@param	heapid	�e�q�[�v
 */
//-----------------------------------------------------------------------------
void WEATHER_CreateHeap( u32 heapid )
{
	//sys_CreateHeap( heapid, HEAPID_WEATHER, 0xa000 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�C�Ŏg�p����q�[�v�̈�̔j��
 */
//-----------------------------------------------------------------------------
void WEATHER_DeleteHeap( void )
{
	//sys_DeleteHeap( HEAPID_WEATHER );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�V�C�Ǘ��V�X�e���쐬
 *
 *	@param	fsys		�t�B�[���h�V�X�e�����[�N
 *
 *	@return	�V�C�Ǘ��V�X�e��
 *
 *
 */
//-----------------------------------------------------------------------------
WEATHER_MANAGER_PTR WEATHER_Init( FIELDSYS_WORK * fsys )
{
	WEATHER_MANAGER_PTR	wmp;	

	// �V�C�Ǘ��V�X�e���������m��
	wmp = sys_AllocMemory( USE_HEAPID, sizeof(WEATHER_MANAGER) );
	memset( wmp, 0, sizeof(WEATHER_MANAGER) );

	// �V�C�V�X�e���쐬
	wmp->weather_sys = InitWeatherSys( fsys );

	// �Ǘ��f�[�^������
	wmp->now_play_weather = WEATHER_SYS_SUNNY;

	// �V�C�ύX�^�X�N�f�[�^
	wmp->next_play_weather = WEATHER_SYS_SUNNY;
	wmp->chenge_seq = WEATHER_CHENGE_NONE;
	wmp->tcb = NULL;
	wmp->booking_weather = WEATHER_SYS_NUM;

	// OAM�`��
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );


	return wmp;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�V�C�Ǘ��V�X�e���j��
 *
 *	@param	pWes	�V�C�Ǘ��V�X�e��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WEATHER_Delete( WEATHER_MANAGER_PTR pWes )
{
	// �ύXTCB�j��
	if( pWes->tcb ){
		TCB_Delete( pWes->tcb );
	}
	
	// �V�C�V�X�e���j��
	DestWeatherSys( &pWes->weather_sys );

	memset( pWes, 0, sizeof(WEATHER_MANAGER) );
	sys_FreeMemoryEz( pWes );
	pWes = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�V�C�ݒ�@�����Ɏw�肵���V�C�ɂȂ�܂��B
 *
 *	@param	pWes	�V�C�Ǘ��V�X�e��
 *	@param	no		�V�C�i���o�[
 *
 *	@return	none
 *
 */
//-----------------------------------------------------------------------------
void WEATHER_Set( WEATHER_MANAGER_PTR pWes, int no )
{
	BOOL check;

	// �ύX��
	GF_ASSERT( pWes->chenge_seq == WEATHER_CHENGE_NONE );

	if( pWes->now_play_weather == no ){
		return ;
	}
	
	// ���̓V�C�j��
	check = ControlWeatherSys( pWes->weather_sys, WEATHER_SYS_DEST, pWes->now_play_weather );
	GF_ASSERT( check );	// �j�����s

	// ���̓V�C�J�n
	check = ControlWeatherSys( pWes->weather_sys, WEATHER_SYS_INIT, no );
	GF_ASSERT( check );	// ���������s
	check = ControlWeatherSys( pWes->weather_sys, WEATHER_SYS_START_NOFADE, no );
	GF_ASSERT( check );	// �J�n���s

	// ���s�V�C�ݒ�
	pWes->now_play_weather = no;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�V�C�ύX���N�G�X�g�@���܂ł̓V�C���t�F�[�h�A�E�g�����A���X�Ɏw�肵���V�C�ɂȂ�܂��B
 *
 *	@param	pWes		�V�C�Ǘ��V�X�e��
 *	@param	no			�V�C�i���o�[
 *
 *	@retval	TRUE		���N�G�X�g����
 *	@retval	FALSE		���N�G�X�g���s	���s���̃��N�G�X�g������
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WEATHER_ChengeReq( WEATHER_MANAGER_PTR pWes, int no )
{
	int change_mode;

	// ���s���̃��N�G�X�g�����邩�`�F�b�N
	if( pWes->chenge_seq != WEATHER_CHENGE_NONE ){
		pWes->booking_weather = no;	// �\��
		return TRUE;
	}

	// ���̓V�C���ꏏ�Ȃ牽�����Ȃ�
	if( pWes->now_play_weather == no ){
		return TRUE;
	}

	GF_ASSERT( pWes->tcb == NULL );
	
	// ���̓V�C�̃f�[�^�ݒ�
	pWes->next_play_weather = no;

	change_mode = WEATHER_ChangeReqFuncNoGet( pWes->now_play_weather ,pWes->next_play_weather );

	if( change_mode == WEATHER_CHANGE_SINGLE_TASK ){
		pWes->chenge_seq = WEATHER_CHENGE_NOW_FADEOUT_START;
		// �^�X�N�o�^
		pWes->tcb = TCB_Add( WEATHER_ChangeTcb, pWes, WEATHER_TCB_CHG_PRI );
	}else{
		pWes->chenge_seq = WEATHER_CHENGE_WL_NEXT_INIT_START;
		// �^�X�N�o�^
		pWes->tcb = TCB_Add( WEATHER_ChangeWithLastTcb, pWes, WEATHER_TCB_CHG_PRI );
	}


	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ݎ��s���̓V�C
 *
 *	@param	pWes	���[�N
 *
 *	@return	�V�C�i���o�[
 */
//-----------------------------------------------------------------------------
u32 WEATHER_GetNow( WEATHER_MANAGER_PTR pWes )
{
	return pWes->now_play_weather;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�O�̂��̂��o�����̕����o��
 *
 *	@param	pWes	�V�󃏁[�N
 *	@param	no		�ύX�i���o�[
 *
 *	@retval	TRUE		���N�G�X�g����
 *	@retval	FALSE		���N�G�X�g���s	���s���̃��N�G�X�g������
 */
//-----------------------------------------------------------------------------
BOOL WEATHER_ChengeReqWithLast( WEATHER_MANAGER_PTR pWes, int no )
{

	// ���s���̃��N�G�X�g�����邩�`�F�b�N
	if( pWes->chenge_seq != WEATHER_CHENGE_NONE ){
		pWes->booking_weather = no;	// �\��
		return TRUE;
	}

	// ���̓V�C���ꏏ�Ȃ牽�����Ȃ�
	if( pWes->now_play_weather == no ){
		return TRUE;
	}

	GF_ASSERT( pWes->tcb == NULL );
	
	// ���̓V�C�̃f�[�^�ݒ�
	pWes->next_play_weather = no;
	pWes->chenge_seq = WEATHER_CHENGE_WL_NEXT_INIT_START;

	// �^�X�N�o�^
	pWes->tcb = TCB_Add( WEATHER_ChangeWithLastTcb, pWes, WEATHER_TCB_CHG_PRI );

	return TRUE;
}


//-----------------------------------------------------------------------------
/**
 *		�V�C�Ǘ��V�X�e��	�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�V�C�ύX�^�X�N
 *
 *	@param	tcb		�^�X�N���[�N
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WEATHER_ChangeTcb( TCB_PTR tcb, void* work )
{
	WEATHER_MANAGER_PTR wmp = work;
	BOOL check;

	switch( wmp->chenge_seq ){
	// ���̓V�C�t�F�[�h�A�E�g	�J�n
	case WEATHER_CHENGE_NOW_FADEOUT_START:
		check = ControlWeatherSys( wmp->weather_sys, WEATHER_SYS_END, wmp->now_play_weather );
		GF_ASSERT( check );		// �t�F�[�h�A�E�g�����J�n���s
		wmp->chenge_seq++;
		break;
		
	// ���̓V�C�t�F�[�h�A�E�g	�I���҂�
	case WEATHER_CHENGE_NOW_FADEOUT:
		check = CheckMoveWeatherSys( wmp->weather_sys, wmp->now_play_weather );
		if( check != WEATHER_SYS_MOVE_DO ){
			check = ControlWeatherSys( wmp->weather_sys, WEATHER_SYS_DEST, wmp->now_play_weather );
			GF_ASSERT( check );	// �j�����s
			wmp->chenge_seq++;
		}
		break;

	// �����������X�^�[�g
	case WEATHER_CHENGE_NEXT_INIT_START:
		OS_Printf( "�t�F�[�h�C���J�n\n" );
		check = ControlWeatherSys( wmp->weather_sys, WEATHER_SYS_INIT_DIV, wmp->next_play_weather );
		GF_ASSERT( check );		// ���������s
		wmp->chenge_seq++;
		break;
		
	// �����������I���҂�
	case WEATHER_CHENGE_NEXT_INIT:
		check = CheckMoveWeatherSys( wmp->weather_sys, wmp->next_play_weather );
		if( check != WEATHER_SYS_MOVE_INIT ){
			wmp->chenge_seq++;
		}
		break;
		
	// ���̓V�C�t�F�[�h�C��		�J�n
	case WEATHER_CHENGE_NEXT_FADEIN_START:
		check = ControlWeatherSys( wmp->weather_sys, WEATHER_SYS_START, wmp->next_play_weather );
		GF_ASSERT( check );		// �t�F�[�h�C���J�n���s
		wmp->chenge_seq++;

		wmp->now_play_weather = wmp->next_play_weather;
		wmp->next_play_weather = WEATHER_SYS_SUNNY;
		
		break;
		
	// �^�X�N�I��
	case WEATHER_CHENGE_END:
		wmp->chenge_seq = WEATHER_CHENGE_NONE;	// ���N�G�X�g�Ȃ���Ԃɂ���
		wmp->tcb = NULL;
		TCB_Delete( tcb );

		// �\��`�F�b�N
		if( wmp->booking_weather != WEATHER_SYS_NUM ){
			// wmp->booking_weather�̓V�C�ɕύX����
			WEATHER_ChengeReq( wmp, wmp->booking_weather );
			wmp->booking_weather = WEATHER_SYS_NUM;
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�V�C�ύX�^�X�N		WithLast
 *
 *	@param	tcb		�^�X�N���[�N
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WEATHER_ChangeWithLastTcb( TCB_PTR tcb, void* work )
{
	WEATHER_MANAGER_PTR wmp = work;
	BOOL check;

	switch( wmp->chenge_seq ){
	// �����ǂݍ��݊J�n
	case WEATHER_CHENGE_WL_NEXT_INIT_START:
		check = ControlWeatherSys( wmp->weather_sys, WEATHER_SYS_INIT_DIV, wmp->next_play_weather );
		GF_ASSERT( check );		// ���������s
		wmp->chenge_seq++;
		break;

	// �����ǂݍ��ݏI���`�F�b�N
	case WEATHER_CHENGE_WL_NEXT_INIT:
		check = CheckMoveWeatherSys( wmp->weather_sys, wmp->next_play_weather );
		if( check != WEATHER_SYS_MOVE_INIT ){
			wmp->chenge_seq++;
		}
		break;
		
	// �t�F�[�h�J�n
	case WEATHER_CHENGE_WL_NOW_FADEOUTIN_START:
		check = ControlWeatherSys( wmp->weather_sys, WEATHER_SYS_END_NOFOG, wmp->now_play_weather );
		GF_ASSERT( check );		// �t�F�[�h�A�E�g�����J�n���s
		check = ControlWeatherSys( wmp->weather_sys, WEATHER_SYS_START_WITHFOG, wmp->next_play_weather );
		GF_ASSERT( check );		// �t�F�[�h�C���J�n���s
		wmp->chenge_seq++;
		break;
		
	// �t�F�[�h�I���`�F�b�N
	case WEATHER_CHENGE_WL_NOW_FADEOUTIN:
		check = CheckMoveWeatherSys( wmp->weather_sys, wmp->now_play_weather );
		if( check != WEATHER_SYS_MOVE_DO ){
			check = ControlWeatherSys( wmp->weather_sys, WEATHER_SYS_DEST, wmp->now_play_weather );
			GF_ASSERT( check );	// �j�����s
			wmp->chenge_seq++;
		}
		break;
		
	case WEATHER_CHENGE_WL_END:
		wmp->now_play_weather = wmp->next_play_weather;
		wmp->next_play_weather = WEATHER_SYS_SUNNY;
		
		wmp->chenge_seq = WEATHER_CHENGE_NONE;	// ���N�G�X�g�Ȃ���Ԃɂ���
		wmp->tcb = NULL;
		TCB_Delete( tcb );


		// �\��`�F�b�N
		if( wmp->booking_weather != WEATHER_SYS_NUM ){
			// wmp->booking_weather�̓V�C�ɕύX����
			WEATHER_ChengeReq( wmp, wmp->booking_weather );
			wmp->booking_weather = WEATHER_SYS_NUM;
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�C�ύX
 *
 *	@param	now_weather		���̓V�C
 *	@param	next_weather	���̓V�C
 *
 *	@retval	WEATHER_CHANGE_SINGLE_TASK	SINGLE�^�X�N�ł̕ύX
 *	@ratval WEATHER_CHANGE_MULTI_TASK	MULTI�^�X�N�ł̕ύX
 */
//----------------------------------	-------------------------------------------
static int WEATHER_ChangeReqFuncNoGet( int now_weather, int next_weather )
{
	int ret = WEATHER_CHANGE_SINGLE_TASK;
	
	switch( now_weather ){
	case WEATHER_SYS_SNOW:		// ��		OAM FOG
		if( (next_weather == WEATHER_SYS_SNOWSTORM) ||
			(next_weather == WEATHER_SYS_SNOW_STORM_BG) ||
			(next_weather == WEATHER_SYS_SNOWSTORM_H) ){
			ret = WEATHER_CHANGE_MULTI_TASK;
		}
		break;

	case WEATHER_SYS_SNOWSTORM:	// ����		OAM FOG
		if( (next_weather == WEATHER_SYS_SNOW) ||
			(next_weather == WEATHER_SYS_SNOW_STORM_BG) ||
			(next_weather == WEATHER_SYS_SNOWSTORM_H) ){
			ret = WEATHER_CHANGE_MULTI_TASK;
		}
		break;
		
	case WEATHER_SYS_SNOW_STORM_BG:// BG�g�p����	OAM FOG BG
		if( (next_weather == WEATHER_SYS_SNOW) ||
			(next_weather == WEATHER_SYS_SNOWSTORM) ||
			(next_weather == WEATHER_SYS_SNOWSTORM_H) ){
		
			ret = WEATHER_CHANGE_MULTI_TASK;
		}
		break;
		
	case WEATHER_SYS_SNOWSTORM_H:	// �k�C����	OAM FOG BG
		if( (next_weather == WEATHER_SYS_SNOW) ||
			(next_weather == WEATHER_SYS_SNOW_STORM_BG) ||
			(next_weather == WEATHER_SYS_SNOWSTORM) ){
			ret = WEATHER_CHANGE_MULTI_TASK;
		}
		break;
	
	default:
		break;
	}

	return ret;
}




//-----------------------------------------------------------------------------
/**
 *
 *		�V�C�V�X�e��
 *
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
 */
//-----------------------------------------------------------------------------
#define		WEATHER_RES_NUM	(4)		// �Ǘ����郊�\�[�X�̐�
#define		WEATEHR_OBJ_MAX	(64)	// �I�u�W�F�N�g�ő吔
#define		WEATEHR_OBJDATA_MAX	(64)// �I�u�W�F�N�g�f�[�^�ő吔
#define		WEATHER_RENDER_X		(0)	// �����_����
#define		WEATHER_RENDER_Y		(0)	// �����_���c
#define		WEATHER_RENDER_WIDTH	(255<< FX32_SHIFT)	// �����_����
#define		WEATHER_RENDER_HEIGHT	(192 << FX32_SHIFT)	// �����_������

#define WEATHER_OBJ_MINTURN_X	(-64*FX32_ONE)
#define WEATHER_OBJ_MINTURN_Y	(-64*FX32_ONE)
#define WEATHER_OBJ_MAXTURN_X	(WEATHER_RENDER_WIDTH + 64*FX32_ONE)
#define WEATHER_OBJ_MAXTURN_Y	(WEATHER_RENDER_HEIGHT + 64*FX32_ONE)

#define		WEATHER_CONTROL_PRI	(4)		// �V�C�Ǘ��^�X�N�̗D��x
#define		WEATHER_CLACT_DRAW_TCB_PRI	(10)	// �V�C�A�N�^�[�`��^�X�N
#define		WEATHER_OBJ_PRI		(5)		// �V�C�I�u�W�F�^�X�N�̗D��x
#define		WEATHER_SYS_BG_2_DRAW_PRI	(1)	// ���V�C�V�X�e��BG�\������
#define		WEATHER_GRAPHIC_NONE	(0xffffffff)	// �O���t�B�b�N�Ȃ�

#define		SCREEN_SIZE (32 * 32)
#define		WEATHER_PLTT_OFS	(6)		// �g�p����p���b�g
#define		WEATHER_LIGHT		(2)		// �V�C�p���C�g

#define		WEATHER_FOG_DEPTH_DEFAULT	( 0x6F6F )	// �t�H�O�f�t�H���g�l
#define		WEATHER_FOG_SLOPE_DEFAULT	( 3 )

#define WH_COLOR_R(x)	( ((x) >> GX_RGB_R_SHIFT) & 0x1f )
#define WH_COLOR_G(x)	( ((x) >> GX_RGB_G_SHIFT) & 0x1f )
#define WH_COLOR_B(x)	( ((x) >> GX_RGB_B_SHIFT) & 0x1f )

// �t�H�O�t�F�[�h�p
#define FOG_DEPTH_COUNT_MAX		(127)
#define FOG_TBL_SUB_FADEIN	( 1 )
#define FOG_TBL_SUB_FADEOUT	( -1 )

//-------------------------------------
//	BG�f�[�^
//=====================================
#define WEATHER_BG_CONTROL_NUM	( 9 )


//-------------------------------------
//		�f�t�H���g�V�[�P���X
//=====================================
enum{
	WEATHER_SEQ_INIT=0,		// ������
	WEATHER_SEQ_FADEIN,		// �t�F�[�h�C��
	WEATHER_SEQ_NO_FADE,	// �t�F�[�h�������̏�����
	WEATHER_SEQ_MAIN,		// ���C������
	WEATHER_SEQ_FADEOUT,	// �t�F�[�h�A�E�g
	WEATHER_SEQ_DEST,		// ���S�j��
};

//-------------------------------------
//	�t�H�O�ݒ�萔
//=====================================
enum{
	WEATHER_FOG_NONE,		// �t�H�O�̐ݒ�Ȃ�
	WEATEHR_FOG_NEW,		// �t�H�O��V�������������ĊJ�n
	WEATHER_FOG_WITH,		// �O�̃t�H�O�ݒ���c���J�n
};


//-------------------------------------
//	�J�Ǘ��֐��萔
//=====================================
#define	WEATHER_RAIN_TIMING_MIN		(1)							// �J���o���^�C�~���O�ŏ�
#define WEATHER_RAIN_TIMING_MAX		(8)						// �J���o���^�C�~���O�ő�
#define WEATHER_RAIN_TIMING_ADD		(1)							// �^�C�~���O�����炷��
#define WEATHER_RAIN_ADD_START		(1)							// �ŏ��̓����ɉJ��o�^���鐔
#define WEATHER_RAIN_ADD_TIMING		(1)							// �J�̃^�C�~���O�������ύX������P�񑝂₷
#define WEATHER_RAIN_ADD			(2)							// �o�^���鐔�𑝂₷��
#define	WEATHER_RAIN_ADD_MAIN		(20)						// ���C���V�[�P���X�ł̓o�^���鐔

/*== �t�F�[�h�����J�n�̎� ==*/
#define WEATHER_RAIN_NOFADE_OBJ_START_NUM	( 20 )				// �J�n���̎U�z����I�u�W�F�N�g�̐�
#define	WEATHER_RAIN_NOFADE_OBJ_START_DUST_NUM	( 10 )			// ���P�ʂŕω������邩
#define	WEATHER_RAIN_NOFADE_OBJ_START_DUST_MOVE	( 1 )			// ���炵�ē��삳����l

/*== �t�H�O ==*/
#define	WEATHER_RAIN_FOG_TIMING		(1)							// �ɂP��t�H�O�e�[�u���𑀍�
#define	WEATHER_RAIN_FOG_TIMING_END	(1)							// �ɂP��t�H�O�e�[�u���𑀍�
#define WEATHER_RAIN_FOG_START		(0)						// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_RAIN_FOG_START_END	(0)						// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_RAIN_FOG_OFS		(0x300)

/*== �J�I�u�W�F�N�g ==*/
#define WEATHER_RAIN_SPEED_X		(-5)						// ���ɐi�ރX�s�[�h
#define WEATHER_RAIN_SPEED_Y		(10)						// ���Ăɐi�ރX�s�[�h�x�[�X
#define	WEATHER_RAIN_END_MIN		(1)							// �I���J�E���^�ŏ�
#define WEATHER_RAIN_END_MAX		(3)							// �I���J�E���^�ő�
#define	WEATHER_RAIN_START_X_BASE	(0)							// �x�[�X�ɂȂ�X�J�n���W
#define	WEATHER_RAIN_MUL_X			(15)						// �x�[�X�ɉJ�̎�ޕ������l
#define	WEATHER_RAIN_START_X_MAX	(270)						// X�J�n���W�����̍ő�l
#define	WEATHER_RAIN_START_Y		(-96)						// Y�J�n���W
#define	WEATHER_RAIN_SPEED_ERR		(20)						// �X�s�[�h�␳�l

/*== �J�O���t�B�b�N�\���f�[�^ ==*/
#define WEATHER_RAIN_GRAPHIC_CELL	( 0 )
#define WEATHER_RAIN_GRAPHIC_BG		( WEATHER_GRAPHIC_NONE )

//-------------------------------------
//	��Ǘ��֐��萔
//=====================================
#define	WEATHER_SNOW_TIMING_MIN		(8)				// ����o���^�C�~���O�ŏ�
#define WEATHER_SNOW_TIMING_MAX		(20)				// ����o���^�C�~���O�ő�
#define WEATHER_SNOW_TIMING_ADD		(5)					// �^�C�~���O�����炷��
#define	WEATHER_SNOW_ADD_TIMING		(1)					// �P�x�̃I�u�W�F�o�^���𑝂₷�^�C�~���O
#define	WEATHER_SNOW_ADD			(0)					// �I�u�W�F�o�^���𑫂��l
#define WEATHER_SNOW_MAIN			(1)					// ���C���ł͂��ꂾ���o�^

/*== �t�F�[�h�����J�n�̎� ==*/
#define WEATHER_SNOW_NOFADE_OBJ_START_NUM	( 20 )				// �J�n���̎U�z����I�u�W�F�N�g�̐�
#define	WEATHER_SNOW_NOFADE_OBJ_START_DUST_NUM	( 2 )			// �������炷��
#define	WEATHER_SNOW_NOFADE_OBJ_START_DUST_MOVE	( 24 )			// ���炵�ē��삳����l

/*== �t�H�O ==*/
#define	WEATHER_SNOW_FOG_TIMING		(1)							// �ɂP��t�H�O�e�[�u���𑀍�
#define	WEATHER_SNOW_FOG_TIMING_END	(2)							// �ɂP��t�H�O�e�[�u���𑀍�
#define WEATHER_SNOW_FOG_START		(16)						// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_SNOW_FOG_START_END	(32)						// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_SNOW_FOG_OFS		(0x300)

/*== ��I�u�W�F�N�g ==*/
#define	WEATHER_SNOW_ADD_TMG_X_BASE	(4)					// ��̃X�s�[�h�𑫂��^�C�~���O
#define	WEATHER_SNOW_ADD_TMG_X_RAN	(2)					// ��̃X�s�[�h�𑫂��^�C�~���O�����l
#define	WEATHER_SNOW_ADD_TMG_Y_BASE	(1)					// ��̃X�s�[�h�𑫂��^�C�~���O
#define	WEATHER_SNOW_ADD_TMG_Y_RAN	(2)					// ��̃X�s�[�h�𑫂��^�C�~���O�����l

#define	WEATHER_SNOW_START_X_BASE	(-32)						// �x�[�X�ɂȂ�X�J�n���W
#define	WEATHER_SNOW_START_X_MAX	(414)						// X�J�n���W�����̍ő�l
#define WEATHER_SNOW_OBJ_NUM		(4)					// �I�u�W�F���

#define WEATHER_SNOW_OBJ_AUTODEST_TIMING_MAX ( 60 )	// ���Ń^�C���@�ő�
#define WEATHER_SNOW_OBJ_AUTODEST_TIMING_MIN ( 4 )	// ���Ń^�C���@�ŏ�

/*== ��O���t�B�b�N�\���f�[�^ ==*/
#define WEATHER_SNOW_GRAPHIC_CELL	( 3 )
#define WEATHER_SNOW_GRAPHIC_BG		( WEATHER_GRAPHIC_NONE )


//-------------------------------------
//	����Ǘ��֐��萔
//=====================================
#define	WEATHER_SSNOW_TIMING_MIN		(3)							// �J���o���^�C�~���O�ŏ�
#define WEATHER_SSNOW_TIMING_MAX		(30)						// �J���o���^�C�~���O�ő�
#define WEATHER_SSNOW_TIMING_ADD		(5)							// �^�C�~���O�����炷��
#define WEATHER_SSNOW_ADD_START			(1)							// �ŏ��̓����ɉJ��o�^���鐔
#define WEATHER_SSNOW_ADD_TIMING		(2)							// �J�̃^�C�~���O�������ύX������P�񑝂₷
#define WEATHER_SSNOW_ADD				(1)							// �o�^���鐔�𑝂₷��
#define WEATHER_SSNOW_ADD_END			(-3)							// �o�^���鐔�𑝂₷��
#define	WEATHER_SSNOW_ADD_MAIN			(6)							// ���C���V�[�P���X�ł̓o�^���鐔

/*== �t�F�[�h�����J�n�̎� ==*/
#define WEATHER_SSNOW_NOFADE_OBJ_START_NUM	( 20 )				// �J�n���̎U�z����I�u�W�F�N�g�̐�
#define	WEATHER_SSNOW_NOFADE_OBJ_START_DUST_NUM		( 2 )			// �������炷��
#define	WEATHER_SSNOW_NOFADE_OBJ_START_DUST_MOVE	( 3 )			// ���炵�ē��삳����l

/*== �t�H�O ==*/
#define	WEATHER_SSNOW_FOG_TIMING		(2)							// �ɂP��t�H�O�e�[�u���𑀍�
#define	WEATHER_SSNOW_FOG_TIMING_END	(1)							// �ɂP��t�H�O�e�[�u���𑀍�
#define WEATHER_SSNOW_FOG_START			(8)						// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_SSNOW_FOG_START_END		(0)						// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_SSNOW_FOG_OFS			(-0x200)

/*== ��I�u�W�F�N�g ==*/
#define WEATHER_SSNOW_SPEED_X		(-1)						// ���ɐi�ރX�s�[�h
#define	WEATHER_SSNOW_END_MIN		(4)							// �I���J�E���^�ŏ�
#define WEATHER_SSNOW_END_MAX		(46)						// �I���J�E���^�ő�
#define WEATHER_SSNOW_END_NUM		(WEATHER_SSNOW_END_MAX - WEATHER_SSNOW_END_MIN)	// �J�E���^�̒l�̐�
#define	WEATHER_SSNOW_END_DIV		((WEATHER_SSNOW_END_NUM / 3)+1)	// �I�u�W�F�N�g�̎�ނ��v�Z����Ƃ�����l
#define	WEATHER_SSNOW_START_X_BASE	(-20)						// �x�[�X�ɂȂ�X�J�n���W
#define	WEATHER_SSNOW_MUL_X			(20)						// �x�[�X�ɐ�̎�ޕ������l
#define	WEATHER_SSNOW_START_X_MAX	(420)						// X�J�n���W�����̍ő�l
#define	WEATHER_SSNOW_START_Y		(-8)						// Y�J�n���W
#define	WEATHER_SSNOW_SPEED_ADD_TMG	(20)						// X���W�̃X�s�[�h���グ��^�C�~���O

#define	WEATHER_SSNOW_ADD_SP_TMG_NUM (4)						// �X�s�[�h��ύX����^�C�~���O�̐�
#define	WEATHER_SSNOW_ADD_SP_TMG_TMG (200)						// �X�s�[�h��ύX����^�C�~���O�̃^�C�~���O

/*== ����O���t�B�b�N�\���f�[�^ ==*/
#define WEATHER_SSNOW_GRAPHIC_CELL	( 1 )
#define WEATHER_SSNOW_GRAPHIC_BG	( WEATHER_GRAPHIC_NONE )

/*== ����BG�O���t�B�b�N�\���f�[�^ ==*/
#define WEATHER_SSNOW_BG_GRAPHIC_CELL	( 1 )
#define WEATHER_SSNOW_BG_GRAPHIC_BG	( 0 )


//-----------------------
// �k�C����
//=======================
#define	WEATHER_SNOW_S_TIMING_MIN		(1)							// ����o���^�C�~���O�ŏ�
#define WEATHER_SNOW_S_TIMING_MAX		(12)						// ����o���^�C�~���O�ő�
#define WEATHER_SNOW_S_TIMING_ADD		(4)							// �^�C�~���O�����炷��
#define WEATHER_SNOW_S_ADD_START		(4)							// �ŏ��̓����ɐ��o�^���鐔
#define WEATHER_SNOW_S_ADD_TIMING		(2)							// ��̃^�C�~���O�������ύX������P�񑝂₷
#define WEATHER_SNOW_S_ADD				(3)							// �o�^���鐔�𑝂₷��
#define WEATHER_SNOW_S_ADD_END			(-4)							// �o�^���鐔�𑝂₷��
#define	WEATHER_SNOW_S_ADD_MAIN			(10)						// ���C���V�[�P���X�ł̓o�^���鐔

/*== �t�F�[�h�����J�n�̎� ==*/
#define WEATHER_SNOW_S_NOFADE_OBJ_START_NUM	( 20 )				// �J�n���̎U�z����I�u�W�F�N�g�̐�
#define	WEATHER_SNOW_S_NOFADE_OBJ_START_DUST_NUM	( 2 )		// �P�����炵�ē��삳����
#define	WEATHER_SNOW_S_NOFADE_OBJ_START_DUST_MOVE	( 2 )		// �P�����炵�ē��삳����

/*== �t�H�O ==*/
#define	WEATHER_SNOW_S_FOG_TIMING		(1)							// �ɂP��t�H�O�e�[�u���𑀍�
#define	WEATHER_SNOW_S_FOG_TIMING_END	(1)							// �ɂP��t�H�O�e�[�u���𑀍�
#define WEATHER_SNOW_S_FOG_START		(16)						// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_SNOW_S_FOG_START_END	(20)						// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_SNOW_S_FOG_OFS	(-0x400)

/*== BG ==*/
#define WEATHER_SNOW_S_BG_ALP_TIM_S	(6)		// �A���t�@���P�グ��^�C�~���O
#define WEATHER_SNOW_S_BG_ALP_TIM_E	(8)		// �A���t�@���P������^�C�~���O

// �I�u�W�F 
#define	WEATHER_SNOW_S_END_MIN		(18)						// �I���J�E���^�ŏ�
#define WEATHER_SNOW_S_END_MAX		(24)						// �I���J�E���^�ő�
#define WEATHER_SNOW_S_START_X		(256)						// ������o���Ƃ���X���W
#define WEATHER_SNOW_S_START_X_RAN	(24)						// ������o���Ƃ���X���W
#define	WEATHER_SNOW_S_START_Y_BASE	(-32)							// �x�[�X�ɂȂ�Y�J�n���W
#define	WEATHER_SNOW_S_START_Y_MAX	(168)						// X�J�n���W�����̍ő�l

#define	WEATHER_SNOW_S_SPEED_ADD_TMG (10)						// X���W�̃X�s�[�h���グ��^�C�~���O

#define	WEATHER_SNOW_S_ADD_SP_TMG_NUM (4)						// �X�s�[�h��ύX����^�C�~���O�̐�
#define	WEATHER_SNOW_S_ADD_SP_CHG_TMG (512)						// �X�s�[�h��ύX����^�C�~���O�̃^�C�~���O

#define WEATHER_SNOW_S_ADD_SP_TMG		(4)						// �X�s�[�h��ύX����^�C�~���O
#define WEATHER_SNOW_S_SP_UP			(8)						// ���̒l�ȏ�̉��X�s�[�h�̂Ƃ��͔h��ɂ���
static const int WEATHER_SSNOW_SPEED_X_SML[WEATHER_SNOW_S_ADD_SP_TMG_NUM] = {-4,-6,-8,-10};
static const int WEATHER_SSNOW_SPEED_Y_SML[WEATHER_SNOW_S_ADD_SP_TMG_NUM] = {2,4,2,4};	// ���Ăɐi�ރX�s�[�h

//#define WEATHER_SNOW_S_BG_ALPHA0	(4)
//#define WEATHER_SNOW_S_BG_ALPHA1	(8)
//#define WEATHER_SNOE_S_BG_ALPHA_DEF	(16)

/*== �Ґ���BG�O���t�B�b�N�\���f�[�^ ==*/
#define WEATHER_SNOW_S_GRAPHIC_CELL	( 9 )
#define WEATHER_SNOW_S_GRAPHIC_BG	( 0 )


//-------------------------------------
//	�����Ǘ��֐��萔
//=====================================
#define	WEATHER_STORM_TIMING_MIN		(1)							// �����o���^�C�~���O�ŏ�
#define WEATHER_STORM_TIMING_MAX		(15)						// �����o���^�C�~���O�ő�
#define WEATHER_STORM_TIMING_ADD		(2)							// �^�C�~���O�����炷��
#define WEATHER_STORM_TIMING_ADD_END	(1)							// �^�C�~���O�����炷��
#define WEATHER_STORM_ADD_START			(1)							// �ŏ��̓����ɉJ��o�^���鐔
#define WEATHER_STORM_ADD_TIMING		(4)							// ���̃^�C�~���O�������ύX������P�񑝂₷
#define WEATHER_STORM_ADD				(2)							// �o�^���鐔�𑝂₷��
#define WEATHER_STORM_ADD_END			(-3)							// �o�^���鐔�𑝂₷��
#define	WEATHER_STORM_ADD_MAIN			(8)							// ���C���V�[�P���X�ł̓o�^���鐔

/*== �t�F�[�h�����J�n�̎� ==*/
#define WEATHER_STORM_NOFADE_OBJ_START_NUM	( 24 )				// �J�n���̎U�z����I�u�W�F�N�g�̐�
#define	WEATHER_STORM_NOFADE_OBJ_START_DUST_NUM		( 2 )			// �������炵�ē��삳���邩
#define	WEATHER_STORM_NOFADE_OBJ_START_DUST_MOVE	( 2 )			// �P�����炵�ē��삳����

/*== �t�H�O ==*/
#define	WEATHER_STORM_FOG_TIMING		(1)							// �ɂP��t�H�O�e�[�u���𑀍�
#define	WEATHER_STORM_FOG_TIMING_END	(1)							// �ɂP��t�H�O�e�[�u���𑀍�
#define WEATHER_STORM_FOG_START			(0)							// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_STORM_FOG_START_END		(31)						// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_STORM_FOG_OFS	( 28399 )
#define WEATHER_STORM_FOG_SLOPE	( 3 )								// �����X���[�v


/*== BG ==*/
#define WEATHER_STORM_BG_ALP_TIM_S	(32)		// �A���t�@���P�グ��^�C�~���O
#define WEATHER_STORM_BG_ALP_TIM_E	(24)		// �A���t�@���P������^�C�~���O
#define WEATHER_STORM_BG_ALP_S_END	( 3 )
#define WEATHER_STORM_BG_ALP_E_END	( 0 )
#define WEATHER_STORM_BG_ALP_DEF	( 16 )

#define WEATHER_STORM_BG_ALP_STRONG_WIND	(4)	// ���������̂Ƃ��̃��l


/*== ���I�u�W�F�N�g ==*/
#define	WEATHER_STORM_END_MIN		(15)						// �I���J�E���^�ŏ�
#define WEATHER_STORM_END_MAX		(35)						// �I���J�E���^�ő�
#define WEATHER_STORM_END_NUM		(WEATHER_STORM_END_MAX - WEATHER_STORM_END_MIN)	// �J�E���^�̒l�̐�
#define	WEATHER_STORM_END_DIV		((WEATHER_STORM_END_NUM / 4)+1)	// �I�u�W�F�N�g�̎�ނ��v�Z����Ƃ�����l
#define	WEATHER_STORM_START_X1		(262)						// �x�[�X�ɂȂ�X�J�n���W	�悱�p
#define	WEATHER_STORM_START_X1_RAN	(24)						// �x�[�X�ɂȂ�X�J�n���W	�悱�p
#define WEATHER_STORM_START_Y1_MIN	( -64 )						//  Y�J�n���W�ŏ�
#define	WEATHER_STORM_START_Y1_MAX	(192)						// Y�J�n���W�ő�
#define	WEATHER_STORM_SPEED_NUM		(8)							// �������̐�
#define	WEATHER_STORM_SPEED_CNG_NUM	(40)						// �ς���^�C�~���O
#define WEATHER_STORM_SPEED_ADD_TMG (5)						// ���̐�����ς���^�C�~���O

#define WEATHER_STORM_STRONG_CHG	(6)						// �������̒l�ȏ�ɂȂ�������������������


/*== ���Ȃ��炵�O���t�B�b�N�\���f�[�^ ==*/
#define WEATHER_STORM_GRAPHIC_CELL	( 2 )
#define WEATHER_STORM_GRAPHIC_BG	( WEATHER_GRAPHIC_NONE )

#define WEATHER_STORMBG_GRAPHIC_CELL	( 2 )
#define WEATHER_STORMBG_GRAPHIC_BG	( 1 )


//-------------------------------------
//	���Ǘ��֐��萔
//=====================================
/*== �t�H�O ==*/
#define	WEATHER_FOG_TIMING		(2)							// �ɂP��t�H�O�e�[�u���𑀍�
#define	WEATHER_FOG_TIMING_END	(2)							// �ɂP��t�H�O�e�[�u���𑀍�
#define WEATHER_FOG_START		(16)						// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_FOG_START_END	(16)						// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�

#define WEATHER_FOG0_OFS	( 0x200 )
#define WEATHER_FOG1_OFS	( -0x9E0 )	
#define WEATHER_FOG1_SLOPE	( 3 )
#define WEATHER_FOG2_OFS	( 0xAA0 )
#define WEATHER_FOG2_SLOPE	( 5 )


/*== FOG2 BG�ݒ� ==*/
#define WEATHER_FOG2_GRAPHIC_BG	( 6 )
#define WEATHER_FOG2_GRAPHIC_CELL	( WEATHER_GRAPHIC_NONE )
#define WEATHER_FOG2_FADE_COUNT_MAX	( 30 )
#define WEATHER_FOG2_FADE_END_ALPHA	( 16 )


//-------------------------------------
//	�X�m�[�_�X�g�֌W
//====================================
#define	WEATHER_SNOW_D_TIMING_MIN		(2)							// �o���^�C�~���O�ŏ�
#define WEATHER_SNOW_D_TIMING_MAX		(16)						// �o���^�C�~���O�ő�
#define WEATHER_SNOW_D_TIMING_ADD		(2)							// �^�C�~���O�����炷��
#define WEATHER_SNOW_D_TIMING_ADD_END	(6)							// �^�C�~���O�����炷��
#define WEATHER_SNOW_D_ADD_START		(2)							// �ŏ��̓����ɓo�^���鐔
#define WEATHER_SNOW_D_ADD_TIMING		(4)							// �^�C�~���O�������ύX������P�񑝂₷
#define WEATHER_SNOW_D_ADD				(2)							// �o�^���鐔�𑝂₷��
#define WEATHER_SNOW_D_ADD_END			(10)							// �o�^���鐔�𑝂₷��
#define	WEATHER_SNOW_D_ADD_MAIN			(20)						// ���C���V�[�P���X�ł̓o�^���鐔

/*== �t�F�[�h�����J�n�̎� ==*/
#define WEATHER_SNOW_D_NOFADE_OBJ_START_NUM	( 20 )				// �J�n���̎U�z����I�u�W�F�N�g�̐�
#define	WEATHER_SNOW_D_NOFADE_OBJ_START_DUST_NUM	( 10 )		// �������쐔�������邩
#define	WEATHER_SNOW_D_NOFADE_OBJ_START_DUST_MOVE	( 1 )		// ���炵�ē��삳����l


/*== �t�H�O ==*/
#define	WEATHER_SNOW_D_FOG_TIMING		(1)							// �ɂP��t�H�O�e�[�u���𑀍�
#define	WEATHER_SNOW_D_FOG_TIMING_END	(1)							// �ɂP��t�H�O�e�[�u���𑀍�
#define WEATHER_SNOW_D_FOG_START		(0)							// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_SNOW_D_FOG_START_END	(0)							// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_SNOW_D_FOG_OFS			(0x200)

// �I�u�W�F�N�g
#define WEATHER_SNOW_D_START_X_MIN		(-64)					// �J�n���W
#define	WEATHER_SNOW_D_START_X_DIS		(384)					// �����ŋ��߂�J�n���W�̒l
#define WEATHER_SNOW_D_START_Y			(-8)					// ��������o��
#define WEATHER_SNOW_D_START_Y_MAX		(256)					// ��������o��
#define WEATHER_SNOW_D_SPARK_NUM_MIN	(7)						// ���ꂾ���o�Ă�ŏ�
#define WEATHER_SNOW_D_SPARK_NUM_RAN	(5)						// �����ŋ��߂�l
#define WEATHER_SNOW_D_SPARK_NO			(0x14)					// ���̐�

#define WEATHER_SNOW_D_SP_ADD_TMG_X_MIN	(3)						//�@�I�u�W�F�N�g�̃X�s�[�h�𑫂��^�C�~���O
#define WEATHER_SNOW_D_SP_ADD_TMG_X_MAX	(6)					//�@�I�u�W�F�N�g�̃X�s�[�h�𑫂��^�C�~���O
#define WEATHER_SNOW_D_SP_ADD_TMG_Y_MIN	(4)						// �I�u�W�F�N�g�̃X�s�[�h�𑫂��^�C�~���O
#define WEATHER_SNOW_D_SP_ADD_TMG_Y_MAX	(5)					// �I�u�W�F�N�g�̃X�s�[�h�𑫂��^�C�~���O	

/*== �X�m�[�_�X�g�O���t�B�b�N�\���f�[�^ ==*/
#define WEATHER_SNOW_D_GRAPHIC_CELL	( 4 )
#define WEATHER_SNOW_D_GRAPHIC_BG	( WEATHER_GRAPHIC_NONE )


//-------------------------------------
//	��
//=====================================
/*== ���O���t�B�b�N�\���f�[�^ ==*/
#define WEATHER_RAINBOW_GRAPHIC_CELL	( WEATHER_GRAPHIC_NONE  )
#define WEATHER_RAINBOW_GRAPHIC_BG		( 2 )

/*== ���[�N�T�C�Y ==*/
#define WEATHER_RAINBOW_WORK_SIZE		(sizeof(int)*10)


//-------------------------------------
//	��J
//=====================================
#define	WEATHER_STRAIN_TIMING_MIN		(1)					// �J���o���^�C�~���O�ŏ�
#define WEATHER_STRAIN_TIMING_MAX		(15)				// �J���o���^�C�~���O�ő�
#define WEATHER_STRAIN_TIMING_ADD		(3)					// �^�C�~���O�����炷��
#define WEATHER_STRAIN_ADD_START		(1)					// �ŏ��̓����ɉJ��o�^���鐔
#define WEATHER_STRAIN_ADD_TIMING		(2)					// �J�̃^�C�~���O�������ύX������P�񑝂₷
#define WEATHER_STRAIN_ADD			(4)						// �o�^���鐔�𑝂₷��
#define WEATHER_STRAIN_ADD_END			(-10)				// �o�^���鐔�𑝂₷��
#define	WEATHER_STRAIN_ADD_MAIN		(24)					// ���C���V�[�P���X�ł̓o�^���鐔

/*== �t�F�[�h�����J�n�̎� ==*/
#define WEATHER_STRAIN_NOFADE_OBJ_START_NUM	( 20 )				// �J�n���̎U�z����I�u�W�F�N�g�̐�
#define	WEATHER_STRAIN_NOFADE_OBJ_START_DUST_NUM	( 5 )		// �������쐔��ύX���邩
#define	WEATHER_STRAIN_NOFADE_OBJ_START_DUST_MOVE	( 1 )		// ���炷���쐔�̒l

/*== �t�H�O ==*/
#define	WEATHER_STRAIN_FOG_TIMING		(1)						// �ɂP��t�H�O�e�[�u���𑀍�
#define	WEATHER_STRAIN_FOG_TIMING_END	(1)						// �ɂP��t�H�O�e�[�u���𑀍�
#define WEATHER_STRAIN_FOG_START		(0)					// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_STRAIN_FOG_START_END	(0)					// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�


/*== �J�I�u�W�F�N�g ==*/
#define WEATHER_STRAIN_SPEED_X		(-24)						// ���ɐi�ރX�s�[�h
#define WEATHER_STRAIN_SPEED_Y		(24)							// ���Ăɐi�ރX�s�[�h�x�[�X
#define	WEATHER_STRAIN_END_MIN		(0)							// �I���J�E���^�ŏ�
#define WEATHER_STRAIN_END_MAX		(4)							// �I���J�E���^�ő�
#define	WEATHER_STRAIN_START_X		(0)							// �x�[�X�ɂȂ�X�J�n���W
#define	WEATHER_STRAIN_START_X_MAX	(512)						// X�J�n���W�����l
#define	WEATHER_STRAIN_START_Y		(-80)						// Y�J�n���W
#define	WEATHER_STRAIN_START_Y_MAX	(48)						// Y�J�n���W�����l

#define WEATHER_STRAIN_OBJ_MUL_NUM	(5)							// �I�u�W�F�̃X�s�[�h��ω�������l
#define WEATHER_STRAIN_OBJ_MUL_CHG	(60)						// �ύX�^�C�~���O

/*== ��J�O���t�B�b�N�\���f�[�^ ==*/
#define WEATHER_STRAIN_GRAPHIC_CELL	( 5 )
#define WEATHER_STRAIN_GRAPHIC_BG	( WEATHER_GRAPHIC_NONE )

//-------------------------------------
//	�ΎR�D�Ǘ��֐��萔
//=====================================
#define	WEATHER_VOLCANO_TIMING_MIN	(6)		// �ΎR�D���o���^�C�~���O�ŏ�
#define WEATHER_VOLCANO_TIMING_MAX	(12)		// �ΎR�D���o���^�C�~���O�ő�
#define WEATHER_VOLCANO_TIMING_ADD	(1)			// �^�C�~���O�����炷��
#define	WEATHER_VOLCANO_ADD_TIMING	(4)			// �P�x�̃I�u�W�F�o�^���𑝂₷�^�C�~���O
#define	WEATHER_VOLCANO_ADD			(0)			// �I�u�W�F�o�^���𑫂��l
#define WEATHER_VOLCANO_MAIN		(1)			// ���C���ł͂��ꂾ���o�^

/*== �t�F�[�h�����J�n�̎� ==*/
#define WEATHER_VOLCANO_NOFADE_OBJ_START_NUM	( 20 )				// �J�n���̎U�z����I�u�W�F�N�g�̐�
#define	WEATHER_VOLCANO_NOFADE_OBJ_START_DUST_NUM	( 2 )		// ���I�u�W�F�����쐔���ւ񂱂����邩
#define	WEATHER_VOLCANO_NOFADE_OBJ_START_DUST_MOVE	( 16 )		// ���炷���쐔�̒l

/*== �t�H�O ==*/
#define	WEATHER_VOLCANO_FOG_TIMING		(1)		// �ɂP��t�H�O�e�[�u���𑀍�
#define	WEATHER_VOLCANO_FOG_TIMING_END	(1)		// �ɂP��t�H�O�e�[�u���𑀍�
#define WEATHER_VOLCANO_FOG_START		(0)	// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_VOLCANO_FOG_START_END	(9)	// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_VOLCANO_FOG_OFS			(-0x40)
#define WEATHER_VOLCANO_FOG_SLOPE		( 0 )

/*== BG ==*/
#define WEATHER_VOLCANO_BG_ALP_TIM_S	(6)		// �A���t�@���P�グ��^�C�~���O
#define WEATHER_VOLCANO_BG_ALP_TIM_E	(8)		// �A���t�@���P������^�C�~���O
#define WEATHER_VOLCANO_BG_ALP_S_END	( 15 )
#define WEATHER_VOLCANO_BG_ALP_E_END	( 0 )
#define WEATHER_VOLCANO_BG_ALP_DEF		( 16 )

/*== �ΎR�D�I�u�W�F�N�g ==*/
#define	WEATHER_VOLCANO_ADD_TMG_Y_BASE	(1)			// �ΎR�D�̃X�s�[�h�𑫂��^�C�~���O
#define	WEATHER_VOLCANO_ADD_TMG_Y_RAN	(1)			// �ΎR�D�̃X�s�[�h�𑫂��^�C�~���O�����l
#define	WEATHER_VOLCANO_START_X_BASE	(-32)		// �x�[�X�ɂȂ�X�J�n���W
#define	WEATHER_VOLCANO_START_X_MAX		(414)		// X�J�n���W�����̍ő�l
#define WEATHER_VOLCANO_OBJ_NUM			(4)			// �I�u�W�F���
#define WEATEHR_VOLCANO_DEL_COUNT_MIN	(10)			// �j������J�E���g�l
#define WEATEHR_VOLCANO_DEL_COUNT_MAX	(20)			// �j���J�E���g�l

/*== �ΎR�D�O���t�B�b�N�\���f�[�^ ==*/
#define WEATHER_VOLCANO_GRAPHIC_CELL	( 6 )
#define WEATHER_VOLCANO_GRAPHIC_BG	( 3 )

//-------------------------------------
//	���Ǘ��֐��萔
//=====================================
#define WEATHER_SPARK_NUM		(2)	// ���C�g���J�E���g
#define WEATHER_SPARK_POWER_MIN	(200)	// ��POWER�ŏ�	(�����_�v�Z�̂��߂P�O�O�������l)
#define WEATHER_SPARK_POWER_RAN	(480)	// ��POWER����	(�����_�v�Z�̂��߂P�O�O�������l)

#define WEATHER_SPARK_SPARK_MUL	(50)	// ���̗��܂ł̊Ԋu��POWER���������{�Ԋu�Ƃ��ċ��߁A
										//	�����̒l�ŗ����v�f�t��(�P�P�ʁ[���P�O�O)
#define WEATHER_SPARK_SPARK_RAN	(120)	// ���̗��܂ł̊Ԋu����
#define WEATHER_SPARK_SPARK_RAN_HIGH	(15)	// ���������o���Ƃ��̎��̗��܂ł̊Ԋu����
#define	WEATHER_SPARK_FOG_TIMING		(1)		// �ɂP��t�H�O�e�[�u���𑀍�
#define	WEATHER_SPARK_FOG_TIMING_END	(1)		// �ɂP��t�H�O�e�[�u���𑀍�
#define WEATHER_SPARK_SUB_NUM			(36)	// ���l�����炷�l
#define WEATHER_SPARK_SUB_NUM_HIGH		(200)	// �����A���t�@�����炷

/*== ���O���t�B�b�N�\���f�[�^ ==*/
#define WEATHER_SPARK_GRAPHIC_CELL	( WEATHER_GRAPHIC_NONE )
#define WEATHER_SPARK_GRAPHIC_BG	( 4 )
/*== ���[�N�T�C�Y ==*/
#define WEATHER_SPARK_WORK_SIZE		(sizeof(int)*10)

//-------------------------------------
//	�C���Ǘ��֐��萔
//=====================================
#define	WEATHER_SPIRIT_TIMING_MIN	(15)		// �J���o���^�C�~���O�ŏ�
#define WEATHER_SPIRIT_TIMING_MAX	(35)		// �J���o���^�C�~���O�ő�
#define WEATHER_SPIRIT_TIMING_ADD	(2)			// �^�C�~���O�����炷��
#define	WEATHER_SPIRIT_ADD_TIMING	(5)			// �P�x�̃I�u�W�F�o�^���𑝂₷�^�C�~���O
#define	WEATHER_SPIRIT_ADD			(1)			// �I�u�W�F�o�^���𑫂��l
#define	WEATHER_SPIRIT_ADD_END		(-3)			// �I�u�W�F�o�^���𑫂��l
#define WEATHER_SPIRIT_MAIN			(4)			// ���C���ł͂��ꂾ���o�^

#define WEATHER_SPIRIT_S_MOVE_NUM	(2)			// �����݂ɗh��鋗��(��)
#define WEATHER_SPIRIT_S_MOVE_TMG	(1)			// �����݂ɗh���^�C�~���O

#define WEATHER_SPIRIT_OBJ_NUM		(0xe)		// �I�u�W�F�N�g��
#define WEATHER_SPIRIT_BIG_DIV		(4)			// ����Ŋ���ƁA�傫���ɂȂ�
#define	WEATHER_SPIRIT_SHIFT_UP		(8)			// �����傫��idx�ł�����
#define WEATHER_SPIRIT_SHIFT_UP_RAN	(25)		// �����l
#define	WEATHER_SPIRIT_ADD_SPEED	(16)		// �����n�i�X�s�[�h�͂P�O�O�{��ԁj

/*== �t�F�[�h�����J�n�̎� ==*/
#define WEATHER_SPIRIT_NOFADE_OBJ_START_NUM	( 16 )				// �J�n���̎U�z����I�u�W�F�N�g�̐�
#define	WEATHER_SPIRIT_NOFADE_OBJ_START_DUST_NUM	( 2 )		// ���I�u�W�F�����삷�鐔��ύX���邩
#define	WEATHER_SPIRIT_NOFADE_OBJ_START_DUST_MOVE	( 1 )		// ���炵�ē��삳����l

/*== �I�u�W�F�N�g ==*/
#define WEATHER_SPIRIT_MAT_X_MIN	(-128)		// X���W�ŏ��l
#define WEATHER_SPIRIT_MAT_X_RAN	(512)		// X���W����

#define WEATHER_SPIRIT_MAT_Y_S_MIN	(8)			// Y���W	�������̂����Ă����ꏊ(0,1)
#define WEATHER_SPIRIT_MAT_Y_S_RAN	(192)		// Y���W	�������̂����Ă����ꏊ
#define WEATHER_SPIRIT_MAT_Y_M_MIN	(64)		// Y���W	�����炢�����Ă����ꏊ(2)
#define WEATHER_SPIRIT_MAT_Y_M_RAN	(128)		// Y���W	�����炢�����Ă����ꏊ
#define WEATHER_SPIRIT_MAT_Y_L_MIN	(160)		// Y���W	�傫���̂����Ă����ꏊ(3)
#define WEATHER_SPIRIT_MAT_Y_L_RAN	(32)		// Y���W	�傫���̂����Ă����ꏊ


/*== �C���O���t�B�b�N�\���f�[�^ ==*/
#define WEATHER_SPIRIT_GRAPHIC_CELL	( 7 )
#define WEATHER_SPIRIT_GRAPHIC_BG	( WEATHER_GRAPHIC_NONE  )

//-------------------------------------
//	�_��
//=====================================
#define WEATHER_MYSTIC_GRAPHIC_BG	( 8 )
#define WEATHER_MYSTIC_GRAPHIC_CELL	( WEATHER_GRAPHIC_NONE )

#define WEATHER_MYSTIC_FADE_COUNT_MAX	( 8 )
#define WEATHER_MYSTIC_FADE_END_ALPHA	( 16 )

/*== �t�H�O ==*/
#define	WEATHER_MYSTIC_FOG_TIMING		(1)		// �ɂP��t�H�O�e�[�u���𑀍�
#define	WEATHER_MYSTIC_FOG_TIMING_END	(1)		// �ɂP��t�H�O�e�[�u���𑀍�
#define WEATHER_MYSTIC_FOG_START		(0)		// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_MYSTIC_FOG_START_END	(48)	// ���̃J�E���g�����Ă���t�H�O�e�[�u���𑀍�
#define WEATHER_MYSTIC_FOG_OFS			(32175)
#define WEATHER_MYSTIC_FOG_SLOPE		(7)


#if 0
#define	WEATHER_MYSTIC_TIMING_MIN	(10)		// �o���^�C�~���O�ŏ�
#define WEATHER_MYSTIC_TIMING_MAX	(40)		// �o���^�C�~���O�ő�
#define WEATHER_MYSTIC_TIMING_ADD	(3)			// �^�C�~���O�����炷��
#define	WEATHER_MYSTIC_ADD_TIMING	(8)			// �P�x�̃I�u�W�F�o�^���𑝂₷�^�C�~���O
#define WEATHER_MYSTIC_ADD_START	(1)
#define	WEATHER_MYSTIC_ADD			(0)			// �I�u�W�F�o�^���𑫂��l
#define	WEATHER_MYSTIC_ADD_END		(1)			// �I�u�W�F�o�^���𑫂��l
#define WEATHER_MYSTIC_ADD_MAIN		(1)			// ���C���ł͂��ꂾ���o�^

/*== �t�F�[�h�����J�n�̎� ==*/
#define WEATHER_MYSTIC_NOFADE_OBJ_START_NUM	( 4 )				// �J�n���̎U�z����I�u�W�F�N�g�̐�
#define	WEATHER_MYSTIC_NOFADE_OBJ_START_DUST_NUM	( 1 )		// ���I�u�W�F�����쐔��ύX���邩
#define	WEATHER_MYSTIC_NOFADE_OBJ_START_DUST_MOVE	( 10 )		// ���炵�ē��삳����l


// �I�u�W�F�N�g
#define WEATHER_MYSTIC_M_Y			(60)		// �ړ��l
#define WEATHER_MYSTIC_M_Y_MUL		(20)		// �傫���ɂ�葝�₷�l
#define WEATHER_MYSTIC_M_X			(0)			// �ړ��l��

#define WEATHER_MYSTIC_MH_X			(50)		// ���V���Ă���悤�Ɍ�����A�⏕����ړ��l
#define WEATHER_MYSTIC_MH_Y			(50)		// ���V���Ă���悤�Ɍ�����A�⏕����ړ��l
#define WEATHER_MYSTIC_MH_COUNT		(2)			// �J�E���g�l
#define WEATHER_MYSTIC_MH_COUNT_RAN	(6)			// �J�E���g�l����


#define WEATHER_MYSTIC_DES_TM		(32)		// ���S�J�E���g
#define WEATHER_MYSTIC_DES_RAN		(16)		// ���S�J�E���g�����_��

#define WEATHER_MYSTIC_NUM			(4)			// �I�u�W�F�N�g��
#define WEATHER_MYSTIC_RAN			(100)		// �ǂ̑傫���ɂ��邩�����߂鎞�̒l
#define WEATHER_MYSTIC_RAN_0		(40)		// ���I�u�W�F�̊���
#define WEATHER_MYSTIC_RAN_1		(30)		// ���I�u�W�F�̊���
#define WEATHER_MYSTIC_RAN_2		(20)		// ����I�u�W�F�̊���
#define WEATHER_MYSTIC_RAN_3		(10)		// ��I�u�W�F�̊���

#define WEATHER_MYSTIC_MAT_X		(0)			// �J�n���W
#define WEAHTER_MYSTIC_MAT_X_RAN	(512)		// �J�n���W�������l
#define WEAHTER_MYSTIC_MAT_Y		(0)			// �J�n���W
#define WEATHER_MYSTIC_MAT_Y_MUL	(48)		// �J�n���W��傫���ɂ��ς���l
#define WEAHTER_MYSTIC_MAT_Y_RAN	(64)		// �J�n���W�������l

/*== �_��O���t�B�b�N�\���f�[�^ ==*/
#define WEATHER_MYSTIC_GRAPHIC_CELL	( 8 )
#define WEATHER_MYSTIC_GRAPHIC_BG	( WEATHER_GRAPHIC_NONE  )
#endif


//-------------------------------------
//	�܂�
//=====================================
#define WEATHER_CLOUDINESS_GRAPHIC_BG	( 5 )
#define WEATHER_CLOUDINESS_GRAPHIC_CELL	( WEATHER_GRAPHIC_NONE )

#define WEATHER_CLOUDINESS_FADE_COUNT_MAX	( 8 )
#define WEATHER_CLOUDINESS_FADE_END_ALPHA	( 4 )

//-------------------------------------
//	����͂炢
//=====================================
#define WEATHER_KIRI_HARAI_GRAPHIC_BG	( 6 )
#define WEATHER_KIRI_HARAI_GRAPHIC_CELL	( WEATHER_GRAPHIC_NONE )

#define WEATHER_KIRI_HARAI_FADE_COUNT_MAX	( 30 )
#define WEATHER_KIRI_HARAI_FADE_END_ALPHA	( 9 )

/*== �t�H�O ==*/
#define	WEATHER_KIRI_HARAI_FOG_TIMING		(1)							// �ɂP��t�H�O�e�[�u���𑀍�
#define	WEATHER_KIRI_HARAI_FOG_TIMING_END	(1)							// �ɂP��t�H�O�e�[�u���𑀍�
#define WEATHER_KIRI_HARAI_FOG_COLOR		(GX_RGB(0,0,0))
#define WEATHER_KIRI_HARAI_FOG_OFS			( 30287 )
#define WEATHER_KIRI_HARAI_FOG_SLOPE		( 7 )

//-------------------------------------
//	����͂炢	����
//=====================================
#define WEATHER_KIRI_HARAI_WHITE_GRAPHIC_BG	( 6 )
#define WEATHER_KIRI_HARAI_WHITE_GRAPHIC_CELL	( WEATHER_GRAPHIC_NONE )

#define WEATHER_KIRI_HARAI_WHITE_FADE_COUNT_MAX	( 30 )
#define WEATHER_KIRI_HARAI_WHITE_FADE_END_ALPHA	( 9 )

/*== �t�H�O ==*/
#define	WEATHER_KIRI_HARAI_WHITE_FOG_TIMING		(1)							// �ɂP��t�H�O�e�[�u���𑀍�
#define	WEATHER_KIRI_HARAI_WHITE_FOG_TIMING_END	(1)							// �ɂP��t�H�O�e�[�u���𑀍�
#define WEATHER_KIRI_HARAI_WHITE_FOG_COLOR		(GX_RGB(31,31,31))
#define WEATHER_KIRI_HARAI_WHITE_FOG_OFS			( 30037 )
#define WEATHER_KIRI_HARAI_WHITE_FOG_SLOPE		( 6 )

//-------------------------------------
//	�t���b�V��
//=====================================
#define WEATHER_FLASH_START_R	( FX32_CONST( 32 ) )
#define WEATHER_FLASH_END_R		( FX32_CONST( 256 ) )
#define WEATHER_FLASH_SYNC		( 30 )
#define WEATHER_FLASH_CX		( 128 )
#define WEATHER_FLASH_CY		( 84 )

#define WEATHER_FLASH_GRAPHIC_BG	( 7 )		// �g�p����BG

#define WEATHER_FLASH_WND_MSK			( GX_BLEND_ALL )
#define WEATHER_FLASH_OUTSIDE_WND_MSK	( GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD )


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�V�C�O���t�B�b�N�t�@�C���p�X�f�[�^
//
//	�ǂݍ��ޓV�C�̃O���t�B�b�N�t�@�C����
//	�܂Ƃ߂�\����
//=====================================

// BG
typedef struct{
	int pltt_arc;
	int char_arc;
	int screen_arc;
	/*char	pltt_path[50];	// �p���b�g�p�X
	char	char_path[50];	// �L�����N�^�p�X
	char	screen_path[50];// �X�N���[���p�X//*/
} WEATHER_BG_DATA;

//-------------------------------------
//	�V�C�O���t�B�b�N�f�[�^�\����
//-------------------------------------
// �Z��
typedef struct{
	CLACT_U_RES_OBJ_PTR res_obj[ WEATHER_RES_NUM ];
	CLACT_ADD add;				// �Z���A�N�^�[�o�^�f�[�^
	CLACT_HEADER head;			// �Z���A�N�^�[�w�b�_�[�f�[�^
} WATHER_GRAPHIC_FILE_DATA;

// BG
typedef struct{
	char*			pPlttBuff;		// �p���b�g�f�[�^
	char*			pCharBuff;		// �L�����N�^�f�[�^
	char*			pScreenBuff;	// �X�N���[���f�[�^
	NNSG2dScreenData*		pScreen;// �X�N���[���f�[�^
	NNSG2dCharacterData*	pChar;	// BG�̃L�����N�^�f�[�^
	NNSG2dPaletteData*		pPltt;	// BG�̃p���b�g�f�[�^

} WATHER_BG_FILE_DATA;

#define WEATHER_OBJ_DATA_WORK_NUM	( 10 )
#define WEATHER_OBJ_DATA_WORK_SIZE	( sizeof(s32)*WEATHER_OBJ_DATA_WORK_NUM )
//-------------------------------------
//
//		�X�̃I�u�W�F�N�g�̍\����
//	
//	�J��A��̃I�u�W�F�N�g
//=====================================
typedef struct WAETHER_OBJ_DATA_tag{
	WEATHER_CONT_PTR	pWSysCont;	// �V�C�f�[�^
	CLACT_WORK_PTR	clact_w;	// �Z���A�N�^�[���[�N
	void*	work;					// ��Ɨ̈�		AllocObjWork() FreeObjWork()�ō쐬�A�j�����邱��
	s32	work_buff[WEATHER_OBJ_DATA_WORK_NUM];					// ��Ɨ̈�		AllocObjWork() FreeObjWork()�ō쐬�A�j�����邱��

	struct WAETHER_OBJ_DATA_tag* pNext;	// ����
	struct WAETHER_OBJ_DATA_tag* pPrev;	// �O��
} WAETHER_OBJ_DATA;

//------------------------------------
//		�V�C�Ǘ��f�[�^�\����
//	
//	�V�C���Ǘ�����֐����ł̃��[�N�̈�\����
//=====================================
typedef struct{
	WEATHER_CONT_PTR	pWSysCont;			// �V�C�V�X�e���R���g���[���̃|�C���^
	void*			pWSD;				// �����̐e��WEATHER_SYS_DATA�f�[�^
	const WATHER_GRAPHIC_FILE_DATA*	pCell;		// �g�p����Z���f�[�^
	WAETHER_OBJ_DATA	Dummy;				// �I�u�W�F���X�g�̃_�~�[�f�[�^
	WAETHER_OBJ_DATA	ObjArray[WEATEHR_OBJDATA_MAX];// �I�u�W�F���X�g�z��
	TCB_PTR tcb;							// �����̃^�X�N�|�C���^
	
	VecFx32		CameraTarget;				// �P�O�̃J�����^�[�Q�b�g�X�N���[���p
	void*		work;						// ���[�N�̈� �e���쐬	


	// ����炵�Ă��邩?
	BOOL snd_play;
	u16 snd_no;
	u16		Sequence;						// �����V�[�P���X

	// �t�H�O�����ONOFFF
	u16 fog_use;

	u16		ContFlag;						// �O���R���g���[���t���O		

} WEATHER_SYS_WORK;

//-------------------------------------
//		�V�C�f�[�^�\����
//
//	�g�p����t�@�C����֐��̃f�[�^�S
//=====================================
typedef struct{
	int		GraphicNo;					// �O���t�B�b�N�f�[�^�z��i���o�[
	int		BGNo;						// BG�f�[�^�z��i���o�[
	int		WorkByte;					// ���[�N�̈�̃o�C�g�T�C�Y
	WEATHER_SYS_WORK* pWork;			// ���s��:�V�C�Ǘ��֐��̃��[�N�̈�	���������Ă��Ȃ��Ƃ�:NULL
	WATHER_GRAPHIC_FILE_DATA*	pCell;	// �g�p����Z���f�[�^	���������Ă��Ȃ��Ƃ�:NULL
	int		MoveFlag;					// ������
			  /*WEATHER_SYS_MOVE_NONE,	// �����Ă��Ȃ�
				WEATHER_SYS_MOVE_INIT,	// ��������
				WEATHER_SYS_MOVE_READY,	// �J�n�҂�
				WEATHER_SYS_MOVE_DO,*/	// ���s��
	
	int		DivInitSeq;					// �����ǂݍ��݃V�[�P���X
	TCB_PTR	DivInitTcb;					// �����ǂݍ���TCB
	
	void	(*cont)(TCB_PTR tcb, void* data);		// �V�C���Ǘ�����֐�
} WEATHER_SYS_DATA;

typedef void (*objFunc)(WAETHER_OBJ_DATA*);		// �I�u�W�F�N�g����֐��^

//-------------------------------------
//	
//	�QD�`��V�X�e���\����
//	
//=====================================
typedef struct {
	
	CLACT_U_RES_MANAGER_PTR	resMan[ WEATHER_RES_NUM ];	// ���\�[�X�}�l�[�W��
	CLACT_U_RES_HEADER_PTR	resHeader;					// ���\�[�X�w�b�_

	// ���C����ʗp�����_���[�f�[�^
	NNSG2dRendererInstance	Render;		// �����_��
	NNSG2dRenderSurface		Surface;	// �T�[�t�F�[�X
	CLACT_SET_PTR	clactSet;			// �Z���A�N�^�Z�b�g
	TCB_PTR	clactDrawTcb;				// �A�N�^�[�`��TCB
	
} WEATHER_SYS_DRAWSYS;


//---------------------------------------------------------
//
//		���V�C�V�X�e������I�u�W�F
//			�V�C�V�X�e���̃I�u�W�F�N�g
//
//=========================================================
typedef struct _WEATHER_SYS_CONTROL{
	WEATHER_SYS_DATA*		pWSD;		// �V�C�V�X�e���f�[�^
	const WEATHER_BG_DATA*	pWSBG;		// �V�C�V�X�e��BG�f�[�^

	WEATHER_SYS_DRAWSYS		Draw;		// �`��V�X�e��
		
	FIELDSYS_WORK* fsys;					// �t�B�[���h�V�X�e���|�C���^

	ARCHANDLE*	ArcHandle;		// �A�[�J�C�u�t�@�C���n���h��
} WEATHER_SYS_CONTROL;

//-----------------------------------------------
//	���̑���Ɨp�\����
//==============================================
//-------------------------------------
//	�I�u�W�F�N�g�t�F�[�h�f�[�^
//-------------------------------------
typedef struct{
	// ���[�N
	WEATHER_SYS_WORK* pWork;	// ���[�N

	// �J�E���^
	s16 objAddNum;		// �I�u�W�F�N�g�o�^��
	s16 objAddTmg;		// �o�^�^�C�~���O�J�E���^
	s16 objAddTmgMax;	// �o�^�^�C�~���O
	s16 objAddNumSum;	// �I�u�W�F�N�g�o�^�������J�E���^
	
	// �萔
	s16	OBJ_ADD_NUM_END;		// �I�u�W�F�N�g�P��̓o�^���@�I���l
	s16	OBJ_ADD_TMG_END;		// �o�^�^�C�~���O�J�E���^�@�I���l
	s16	OBJ_ADD_TMG_SUM;		// �o�^�^�C�~���O�J�E���^�ύX�l
	s16 OBJ_ADD_NUM_SUM_TMG;	// �I�u�W�F�N�g�P��̓o�^����ύX����^�C�~���O
	s32 OBJ_ADD_NUM_SUM;		// �ύX����l

	// �֐�
	void	(*add)(WEATHER_SYS_WORK* pWork, int num);		// OBJ�o�^
} WEATHER_SYS_OBJ_FADE;
typedef void (*OBJADD_FUNC)(WEATHER_SYS_WORK* pWork, int num);// OBJ�o�^


//-------------------------------------
//	���샏�[�N
//=====================================
typedef struct {
	int x;
	int s_x;
	int dis_x;
	int count;
	int count_max;
} WEATHER_SYS_MOVE_WORK;

//-------------------------------------
//	�����R�Q���샏�[�N
//=====================================
typedef struct {
	fx32 x;
	fx32 s_x;
	fx32 dis_x;
	s16 count;
	s16 count_max;
} WEATHER_SYS_MOVE_WORK_FX;

//-------------------------------------
//	�t�H�O�f�v�X�@�J���[�@�X���[�v�ύX
//=====================================
typedef struct {
	FOG_DATA_PTR	Fog;		// �t�F�[�h����t�H�O�f�[�^
	WEATHER_SYS_MOVE_WORK fog_depth;
	WEATHER_SYS_MOVE_WORK r;
	WEATHER_SYS_MOVE_WORK g;
	WEATHER_SYS_MOVE_WORK b;
	WEATHER_SYS_MOVE_WORK slope;
} WEATHER_SYS_CHG_FOG_DATA;

//-------------------------------------
//	�t�H�O�t�F�[�h�f�[�^
//-------------------------------------
typedef struct{
	FOG_DATA_PTR	Fog;		// �t�F�[�h����t�H�O�f�[�^
	char			fog_tbl[32];// �t�H�O�e�[�u��

	// �J�E���^
	s32	fogDepth;		// �t�H�O�[�x
	s32	fogCount;		// �t�H�O�J�E���^

	// �萔
	s16	FOG_CHG_TMG;		// �t�H�O�e�[�u���ύX�^�C�~���O
	s16	FOG_TBL_SUM;		// �ύX�l
} WEATHER_SYS_FOG_FADE;

//-------------------------------------
//	�V�X�e�����[�N�f�[�^
//-------------------------------------

// Normal
typedef struct{
	WEATHER_SYS_OBJ_FADE	objFade;
	WEATHER_SYS_FOG_FADE	fogFade;
	WEATHER_SYS_CHG_FOG_DATA fogWithFade;
	s32	work[10];
} WEATHER_SYSW_NORMAL;

// �I�u�W�F�t�F�[�h�̂�
typedef struct{
	WEATHER_SYS_OBJ_FADE	objFade;
	s32	work[10];
} WEATHER_SYSW_OBJFADE;

// �t�H�O�t�F�[�h�̂�
typedef struct{
	WEATHER_SYS_FOG_FADE	fogFade;
	WEATHER_SYS_CHG_FOG_DATA fogWithFade;
	s32	work[10];
} WEATHER_STSW_FOGFADE;

// �܂�悤���[�N
typedef struct{
	WEATHER_SYS_MOVE_WORK alpha;
} WEATHER_CLOUDINESS_WORK;

// ���͂炢
typedef struct{
	WEATHER_SYS_MOVE_WORK alpha;
	WEATHER_SYS_FOG_FADE	fogFade;
	WEATHER_SYS_CHG_FOG_DATA fogWithFade;
} WEATHER_KIRI_HARAI_WORK;

// �T�[�N��
typedef struct {
	s16 x;						// ���S�����W
	s16 y;						// ���S�����W
	WEATHER_SYS_MOVE_WORK_FX r;	// ���a
	FIELD_HBLANK_SYS* p_fldhblksys;	// hblank�V�X�e��
	FIELD_HBLANK_OBJ* p_hblank;	// hblank���[�N
	LASTER_SYS_PTR p_laster[2];	// ���X�^�[�V�X�e��
	TCB_PTR vblank_tcb;
	u32 status;				// �X�e�[�^�X
	u16	wnd_data[4][192];	// wnd�f�[�^
} WEATHER_CIRCLE_WORK;
enum{	// status
	WEATHER_CIRCLE_STATUS_INIT,
	WEATHER_CIRCLE_STATUS_DO,
};
#define WEATHER_CIRCLE_VBLANKTCB_PRI	( 1024 )


// �t���b�V��
typedef struct {
	WEATHER_CIRCLE_WORK circle;
} WEATHER_FLASH_WORK;


//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	���̑��v���C�x�[�g�֐�
//=====================================
static void WeatherLoopSndPlay( WEATHER_SYS_WORK* p_work, int snd_no );
static void WeatherLoopSndStop( WEATHER_SYS_WORK* p_work );
static void WeatherBGAlphaDef( int alpha1, int alpha2 );
static void WeatherMoveReq( WEATHER_SYS_MOVE_WORK* p_work, int s_x, int e_x, int count_max );
static BOOL	WeatherMoveMain( WEATHER_SYS_MOVE_WORK* p_work );
static void WeatherMoveReqFx( WEATHER_SYS_MOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, int count_max );
static BOOL	WeatherMoveMainFx( WEATHER_SYS_MOVE_WORK_FX* p_work );
static void load2DGraphicFile(WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell);	// �G�̃f�[�^�̓ǂݍ���
static void setUpBG( WEATHER_SYS_CONTROL* cont, int BGNo );
static void destGraphicFile(WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell);	// �G�̃f�[�^�̔j��

static CLACT_U_RES_OBJ_PTR	loadRes(CLACT_U_RES_HEADER_PTR res_head, int res_type, int head_no, CLACT_U_RES_MANAGER_PTR resMan, ARCHANDLE* arcHandle, u32 alloc_type);

static void init2DDrawSys(WEATHER_SYS_DRAWSYS* draw);
static void loadResHeader(CLACT_U_RES_HEADER_PTR head, int no, int arc_data);
static void delete2DDrawSys(WEATHER_SYS_DRAWSYS* draw);
static void clactSetDrawTcb( TCB_PTR tcb, void* p_work );

//	�V�C�f�[�^����֐�
static void setSysData(WEATHER_SYS_DATA* pData, int CellNo, int BGNo, int WorkSize, TCB_FUNC func);
static void setBGData(WEATHER_BG_DATA* pData, int pltt_arc, int char_arc, int screen_arc );

// ���W�ݒ��p�֐�
static void setClactMatrix( CLACT_WORK_PTR act, VecFx32* matrix );

//-------------------------------------
//	�V�C�Ǘ��֐��p�֐�
//=====================================
static void destObj(WAETHER_OBJ_DATA* pData);							// �I�u�W�F�̔j��
static void destObjAll(WAETHER_OBJ_DATA* pDummy);						// �S�I�u�W�F�̔j��
static WAETHER_OBJ_DATA* addObj(WEATHER_SYS_WORK* pWork, int w_byte);	// �I�u�W�F���A�b�h
static void getHeader(CLACT_HEADER_PTR head, WEATHER_SYS_CONTROL* cont, WATHER_GRAPHIC_FILE_DATA* pcell,int vram_trans, int priority );
static BOOL setUpCell( WEATHER_SYS_CONTROL* cont, WEATHER_SYS_DATA* w_sys );
static void moveFuncObj(WAETHER_OBJ_DATA* pDummy, objFunc pFunc);		// �S�I�u�W�F�N�g�𓮂���
static void drawObj(WEATHER_SYS_WORK* pData);							// �I�u�W�F�̕`��
static VecFx32 getObjMat( WAETHER_OBJ_DATA* obj );
static int getMaxOamNum(NNSG2dCellDataBank* pCell);						// �Z���f�[�^�o���N���̃Z����OAM�̍ő吔�擾
static void getScrollNum(fx32* x, fx32* y, WEATHER_SYS_WORK* pWork);		// �X�N���[�����W�擾
static void scrollObj(WEATHER_SYS_WORK* pWork, int* x, int* y);			// �S�I�u�W�F�N�g�̍��W��scroll�ɂ��킹��
static void allocObjWork(WAETHER_OBJ_DATA* pData, int byte);			// ���[�N�̈���쐬
static void freeObjWork(WAETHER_OBJ_DATA* pData);						// ���[�N�̈��j��
static void weatherSysObjFadeInit( WEATHER_SYS_OBJ_FADE* data, WEATHER_SYS_WORK* pWork, s32 objAddTmgMax, s32 objAddNum, s32 OBJ_ADD_NUM_END, s32 OBJ_ADD_TMG_END, s32 OBJ_ADD_TMG_SUM, s32 OBJ_ADD_NUM_SUM_TMG, s32 OBJ_ADD_NUM_SUM, OBJADD_FUNC add );
static void weatherSysObjFadeOutSet( WEATHER_SYS_OBJ_FADE* data, s32 OBJ_ADD_NUM_END, s32 OBJ_ADD_TMG_END, s32 OBJ_ADD_TMG_SUM, s32 OBJ_ADD_NUM_SUM );
static int weatherSysObjFade(WEATHER_SYS_OBJ_FADE* data);				// �I�u�W�F�N�g�t�F�[�h
static void weatherSysFogFadeInInitPack( WEATHER_SYS_CHG_FOG_DATA* fogParam, WEATHER_SYS_FOG_FADE* fogData, FOG_DATA_PTR Fog, int fog_slope, int fog_offs, GXRgb color, int timing, u32 fog_use_flg );
static int weatherSysFogFadeInMainPack( WEATHER_SYS_CHG_FOG_DATA* fogParam, WEATHER_SYS_FOG_FADE* fogData, u32 fog_use_flg );
static void weatherSysFogParamSet( FOG_DATA_PTR Fog, int fog_slope, int fog_offs, GXRgb color );
static void weatherSysFogParamFadeInit( WEATHER_SYS_CHG_FOG_DATA* data, FOG_DATA_PTR fog, int fogslope, int offs, GXRgb color, int count_max );
static BOOL weatherSysFogParamFadeMain( WEATHER_SYS_CHG_FOG_DATA* data );
static void weatherSysFogTblInit( WEATHER_SYS_FOG_FADE* data );
static void weatherSysFogFadeInit( WEATHER_SYS_FOG_FADE* data, int timing, BOOL fade_inout );
static int weatherSysFogFade(WEATHER_SYS_FOG_FADE* data);				// �t�H�O�t�F�[�h
static int weatherSysFogFadeNoReflect(WEATHER_SYS_FOG_FADE* data);		// �t�H�O�t�F�[�h�@�t�H�O�e�[�u���̔��f���s��Ȃ��o�[�W����
static void weatherSysFogSet(WEATHER_SYS_FOG_FADE* data);				// �t�H�O�t�F�[�h�C����̃e�[�u�����쐬����
static void calcWeatherFogTbl( WEATHER_SYS_FOG_FADE* data );			// �t�H�O�e�[�u���쐬�v�Z���s��
//static BOOL weatherBGFade( s32* now_alpha, const int end_alpha, const int add_alpha, s32* timing_count, const int add_timing );
static void weatherDustObj( WEATHER_SYS_WORK* pWork, OBJADD_FUNC add_func, int num, int dust_div_num, int dust_div_move, objFunc move_func );	// �V�C�̃I�u�W�F�N�g���U�z������
static WAETHER_OBJ_DATA* getCleanObjData( WEATHER_SYS_WORK* pWork );


//-------------------------------------
//	�V�C�Ǘ��֐�����֐�
//=====================================
static BOOL initWeatherSys(WEATHER_SYS_CONTROL* cont,int no);				// �Ǘ��֐�������
static BOOL divInitWeatherSysCall(WEATHER_SYS_CONTROL* cont,int no);
static BOOL startWeatherSys(WEATHER_SYS_CONTROL* cont,int no, int init_seq, u32 fog_use);// �Ǘ��֐��X�^�[�g
static void stopReqWeatherSys(WEATHER_SYS_CONTROL* cont,int no, u32 fog_use);				// �Ǘ��֐��I��
static void stopWeatherSys( WEATHER_SYS_CONTROL* cont,int no );				// �����I��
static void destWeatherSys(WEATHER_SYS_CONTROL* cont,int no);				// �Ǘ��֐����S�j��
static void stopWeatherWork(WEATHER_SYS_CONTROL* cont,int no);				// �Ǘ��f�[�^�j��
static void stopWeatherWork_local(WEATHER_SYS_DATA* w_sys);				// �Ǘ��f�[�^�j��

// ���������������֐�
static void divInitWeatherSysTcb( TCB_PTR tcb, void* work );
static BOOL initWeatherSysWork( WEATHER_SYS_CONTROL* cont, WEATHER_SYS_DATA* w_sys );

static void initClactSet( WEATHER_SYS_CONTROL* cont, WEATHER_SYS_DATA* w_sys );
static BOOL initCellDataMemory( WEATHER_SYS_DATA* w_sys );
static void loadCell_CellData( WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell );
static void loadCell_CellAnmData( WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell );
static void loadCell_CharData( WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell );
static void loadCell_PlttData( WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell );
static void initClactAddData( WEATHER_SYS_CONTROL* cont, WEATHER_SYS_DATA* w_sys );

static void initBgPltt( WEATHER_SYS_CONTROL* cont, int BGNo );
static void initBgChar( WEATHER_SYS_CONTROL* cont, int BGNo );
static void initBgScr( WEATHER_SYS_CONTROL* cont, int BGNo );

//-------------------------------------
//	�V�C�Ǘ��֐�
//=====================================
static void contWeatherDummy(TCB_PTR tcb, void* work);		// �_�~�[
static void contWeatherRain(TCB_PTR tcb, void* work);		// �J
static void contWeatherSnow(TCB_PTR tcb, void* work);		// ��
static void contWeatherSnowStorm(TCB_PTR tcb, void* work);	// ����
static void contWeatherSnowStormBG(TCB_PTR tcb, void* work);// BG�g�p����
static void contWeatherFog00(TCB_PTR tcb, void* work);		// ����
static void contWeatherFog01(TCB_PTR tcb, void* work);		// ����
static void contWeatherFog02(TCB_PTR tcb, void* work);		// ����
static void contWeatherStorm(TCB_PTR tcb, void* work);		// ����
static void contWeatherStormBG(TCB_PTR tcb, void* work);	// BG�g�p����
static void contWeatherSnowSML(TCB_PTR tcb, void* work);	// �k�C����
static void contWeatherSnowD(TCB_PTR tcb, void* work);		// �X�m�[�_�X�g
static void contWeatherRainbow(TCB_PTR tcb, void* work);	// ��
static void contWeatherSTRain(TCB_PTR tcb, void* work);		// ��J
static void contWeatherSTRainSpark(TCB_PTR tcb, void* work);// ��J�{��
static void contWeatherVolcano(TCB_PTR tcb, void* work);	// �ΎR�D
static void contWeatherSpark(TCB_PTR tcb, void* work);		// ��
static void contWeatherSpirit(TCB_PTR tcb, void* work);		// �C��
static void contWeatherMystic(TCB_PTR tcb, void* work);		// �_��
static void contWeatherCloudiness(TCB_PTR tcb, void* work);	// �܂�
static void contWeatherKiriHarai(TCB_PTR tcb, void* work);	// ����͂炢
static void contWeatherKiriHarai_White(TCB_PTR tcb, void* work);	// ����͂炢
static void contWeatherFlash(TCB_PTR tcb, void* work);		// �t���b�V��




//-------------------------------------
//	�V�C�I�u�W�F�N�g�o�^�֐�
//=====================================
static void addWeatherRain(WEATHER_SYS_WORK* pWork, int num);		// �J
static void addWeatherSnow(WEATHER_SYS_WORK* pWork, int num);		// ��
static void addWeatherSnowStorm(WEATHER_SYS_WORK* pWork, int num);	// ����
static void addWeatherStorm(WEATHER_SYS_WORK* pWork, int num);		// ����
static void addWeatherSnowSML(WEATHER_SYS_WORK* pWork, int num);	// �k�C����
static void addWeatherSnowD(WEATHER_SYS_WORK* pWork, int num);		// �X�m�[�_�X�g
static void addWeatherSTRain(WEATHER_SYS_WORK* pWork, int num);		// ��J
static void addWeatherVolcano(WEATHER_SYS_WORK* pWork, int num);	// �ΎR�D
static void addWeatherSpirit(WEATHER_SYS_WORK* pWork, int num);		// �C��
static void addWeatherMystic(WEATHER_SYS_WORK* pWork, int num);		// �_��

//-------------------------------------
//	�V�C�̃I�u�W�F�֐�
//=====================================
static void objWeatherRain(WAETHER_OBJ_DATA* work);			// �J�̗�
static void objWeatherSnow(WAETHER_OBJ_DATA* work);			// ��̗�
static void objWeatherSnowStorm(WAETHER_OBJ_DATA* work);	// ����̗�
static void objWeatherStorm(WAETHER_OBJ_DATA* work);		// ����
static void objWeatherSnowSML(WAETHER_OBJ_DATA* work);		// �k�C����
static void objWeatherSnowD(WAETHER_OBJ_DATA* work);		// �X�m�[�_�X�g
static void objWeatherSTRain(WAETHER_OBJ_DATA* work);		// ��J
static void objWeatherVolcano(WAETHER_OBJ_DATA* work);		// �ΎR�D
static void objWeatherSpirit(WAETHER_OBJ_DATA* work);		// �C��
static void objWeatherMystic(WAETHER_OBJ_DATA* work);		// �_��


//-------------------------------------
//	�V�C�̊e�������ׂ����p�b�N�����֐��S
//=====================================
static void contWeatherSTRain_Init( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w );
static BOOL contWeatherSTRain_FadeIn( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w );
static void contWeatherSTRain_NoFade( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w );
static void contWeatherSTRain_Main( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w );
static void contWeatherSTRain_FadeOutInit( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w );
static BOOL contWeatherSTRain_FadeOut( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w );
static void contWeatherSTRain_Dest( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w );
static void contWeatherSTRain_Draw( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w );

//-------------------------------------
//	HBlank�g�p�~�`��V�X�e��
//=====================================
static void drawWeatherCircleInit( WEATHER_CIRCLE_WORK* p_circle, FIELD_HBLANK_SYS* p_fldhblksys );
static void drawWeatherCircleEnd( WEATHER_CIRCLE_WORK* p_circle );
static void drawWeatherCircleStart( WEATHER_CIRCLE_WORK* p_circle, fx32 s_r, fx32 e_r, int c_x, int c_y, int sync );
static BOOL drawWeatherCircleMain( WEATHER_CIRCLE_WORK* p_circle );
static void drawWeatherCircleHblankCall( FIELD_HBLANK_OBJ* p_hbw, void* p_work );
static void drawWeatherCircleVblankCall( TCB_PTR tcb, void* p_work );
static void drawWeatherCircleEndReq( WEATHER_CIRCLE_WORK* p_circle );
static void drawWeatherCircleEndVblank( TCB_PTR tcb, void* p_work );
static void drawWeatherCircleInitHblankTcb( TCB_PTR tcb, void* p_work );


static void CalcWeatherCircle( WEATHER_CIRCLE_WORK* p_circle );
static void CalcWeatherCircleCopyBuff( WEATHER_CIRCLE_WORK* p_circle );
static void CalcWeatherCircleSub( fx32 c_r, int c_x, int c_y, int n_h, int* st, int* ed );




//----------------------------------------------------------------------------
/**
 *					�O���[�o���ϐ��錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	BG�e�[�u��
//=====================================
static const WEATHER_BG_DATA WSBG[ WEATHER_BG_CONTROL_NUM ] = {
	{ NARC_WEATHER_SYS_SNOW_NCLR,		NARC_WEATHER_SYS_STORM_BG_NCGR,		NARC_WEATHER_SYS_STORM_SC_NSCR },
	{ NARC_WEATHER_SYS_STORM_BG_NCLR,	NARC_WEATHER_SYS_STORM_BG_NCGR,		NARC_WEATHER_SYS_STORM_SC_NSCR },
	{ NARC_WEATHER_SYS_RAINBOW_NCLR,	NARC_WEATHER_SYS_RAINBOW_NCGR,		NARC_WEATHER_SYS_RAINBOW_SC_NSCR },
	{ NARC_WEATHER_SYS_VOLCANO_NCLR,	NARC_WEATHER_SYS_VOLCANO_BG_NCGR,	NARC_WEATHER_SYS_VOLCANO_NSCR },
	{ NARC_WEATHER_SYS_SPARK_NCLR,		NARC_WEATHER_SYS_SPARK_NCGR,		NARC_WEATHER_SYS_SPARK_NSCR },
	{ NARC_WEATHER_SYS_CLOUDINESS_NCLR, NARC_WEATHER_SYS_CLOUDINESS_NCGR,	NARC_WEATHER_SYS_CLOUDINESS_NSCR },
	{ NARC_WEATHER_SYS_FOG_BG_NCLR,		NARC_WEATHER_SYS_CLOUDINESS_NCGR,	NARC_WEATHER_SYS_CLOUDINESS_NSCR },
	{ NARC_WEATHER_SYS_FLASH_NCLR,		NARC_WEATHER_SYS_FLASH_NCGR,		NARC_WEATHER_SYS_FLASH_NSCR },
	{ NARC_WEATHER_SYS_MYSTIC_NCLR,		NARC_WEATHER_SYS_MYSTIC_NCGR,		NARC_WEATHER_SYS_MYSTIC_NSCR },
};

//-------------------------------------
//	�V�C�I�u�W�F�N�g�e�[�u��
//=====================================
static WEATHER_SYS_DATA WSD[ WEATHER_SYS_NUM ] = {
	{	// SUNNY
		WEATHER_GRAPHIC_NONE, 
		WEATHER_GRAPHIC_NONE,
		sizeof(u32),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherDummy
	},
	{	// CLOUDINESS
		WEATHER_CLOUDINESS_GRAPHIC_CELL,
		WEATHER_CLOUDINESS_GRAPHIC_BG,
		sizeof(WEATHER_CLOUDINESS_WORK),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherCloudiness
	},
	{	// RAIN
		WEATHER_RAIN_GRAPHIC_CELL,
		WEATHER_RAIN_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherRain
	},
	{	// STRAIN 
		WEATHER_STRAIN_GRAPHIC_CELL,
		WEATHER_STRAIN_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSTRain
	},
	{	// SPARK 
		WEATHER_STRAIN_GRAPHIC_CELL,
		WEATHER_STRAIN_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSTRainSpark
	},
	{	// SNOW
		WEATHER_SNOW_GRAPHIC_CELL,
		WEATHER_SNOW_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSnow
	},
	{	// SNOW_STORM
		WEATHER_SSNOW_GRAPHIC_CELL, 
		WEATHER_SSNOW_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSnowStorm
	},
	{	// SNOW_SML
		WEATHER_SNOW_S_GRAPHIC_CELL, 
		WEATHER_SNOW_S_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSnowSML
	},
	{	// FOGL
		WEATHER_FOG2_GRAPHIC_CELL,
		WEATHER_FOG2_GRAPHIC_BG,
		sizeof(WEATHER_KIRI_HARAI_WORK),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherFog02
	},
	{	// VOLCANO
		WEATHER_VOLCANO_GRAPHIC_CELL,
		WEATHER_VOLCANO_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherVolcano
	},
	{	// STORM_BG
		WEATHER_STORMBG_GRAPHIC_CELL,
		WEATHER_STORMBG_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherStormBG
	},
	{	// SNOW_D
		WEATHER_SNOW_D_GRAPHIC_CELL,
		WEATHER_SNOW_D_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSnowD
	},
	{	// SPIRIT
		WEATHER_SPIRIT_GRAPHIC_CELL,
		WEATHER_SPIRIT_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_OBJFADE),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSpirit
	},
	{	// MYSTIC
		WEATHER_MYSTIC_GRAPHIC_CELL,
		WEATHER_MYSTIC_GRAPHIC_BG,
		sizeof(WEATHER_KIRI_HARAI_WORK),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherMystic
	},
#if 0
	{	// MYSTIC
		WEATHER_MYSTIC_GRAPHIC_CELL,
		WEATHER_MYSTIC_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherMystic
	},
#endif
	{	// MIST1
		WEATHER_KIRI_HARAI_GRAPHIC_CELL,
		WEATHER_KIRI_HARAI_GRAPHIC_BG,
		sizeof(WEATHER_KIRI_HARAI_WORK),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherKiriHarai_White
	},
	{	// MIST2
		WEATHER_KIRI_HARAI_GRAPHIC_CELL,
		WEATHER_KIRI_HARAI_GRAPHIC_BG,
		sizeof(WEATHER_KIRI_HARAI_WORK),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherKiriHarai
	},
	{	// FLASH
		WEATHER_GRAPHIC_NONE,
		WEATHER_FLASH_GRAPHIC_BG,
		sizeof(WEATHER_FLASH_WORK),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherFlash
	},
	{	// SPARK_EFF
		WEATHER_SPARK_GRAPHIC_CELL,
		WEATHER_SPARK_GRAPHIC_BG,
		WEATHER_SPARK_WORK_SIZE,
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSpark
	},
	{	// FOGS
		WEATHER_GRAPHIC_NONE,
		WEATHER_GRAPHIC_NONE,
		sizeof(WEATHER_STSW_FOGFADE),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherFog00
	},
	{	// FOGM
		WEATHER_GRAPHIC_NONE, 
		WEATHER_GRAPHIC_NONE,
		sizeof(WEATHER_STSW_FOGFADE),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherFog01
	},
	{	// RAINBOW
		WEATHER_RAINBOW_GRAPHIC_CELL,
		WEATHER_RAINBOW_GRAPHIC_BG,
		WEATHER_RAINBOW_WORK_SIZE,
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherRainbow
	},
	{	// SNOW_STORM_BG
		WEATHER_SSNOW_BG_GRAPHIC_CELL,
		WEATHER_SSNOW_BG_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSnowStormBG
	},
	{	// STORM
		WEATHER_STORM_GRAPHIC_CELL, 
		WEATHER_STORM_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherStorm
	},
};



//----------------------------------------------------------------------------
/**
 *
 *@brief	�`��V�X�e���̏�����
 *
 *@param	draw	�`��V�X�e��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void init2DDrawSys(WEATHER_SYS_DRAWSYS* draw)
{
	NNSG2dViewRect rect;		// �T�[�t�F�[�X��`
	int i;						// ���[�v�p
	int size;					// �w�b�_�T�C�Y�擾�p
	
	// �����_��������
	RNDP_InitRenderer(&draw->Render, -FX32_ONE);

	// �T�[�t�F�[�X������
	rect.posTopLeft.x	= WEATHER_RENDER_X;
	rect.posTopLeft.y	= WEATHER_RENDER_Y;
	rect.sizeView.x		= WEATHER_RENDER_WIDTH;
	rect.sizeView.y		= WEATHER_RENDER_HEIGHT;
	REND_OAM_SetSurface(&draw->Surface, &rect, NNS_G2D_SURFACETYPE_MAIN2D, &draw->Render);

	// ���\�[�X�}�l�[�W���쐬
	for(i=0;i<WEATHER_RES_NUM;i++){
		draw->resMan[i] = CLACT_U_ResManagerInit(WEATHER_SYS_NUM, i, USE_HEAPID);
	}

	// ���\�[�X�}�l�[�W���w�b�_�쐬
	size = CLACT_U_ResManagerGetHeaderSize();
	draw->resHeader = sys_AllocMemory(USE_HEAPID, size * WEATHER_RES_NUM);
	
	// ���\�[�X�w�b�_�[�ǂݍ���
	loadResHeader(draw->resHeader, CLACT_U_CHAR_RES, NARC_WEATHER_SYS_WEATHER_CHAR_RESDAT );
	loadResHeader(draw->resHeader, CLACT_U_PLTT_RES, NARC_WEATHER_SYS_WEATHER_PLTT_RESDAT);
	loadResHeader(draw->resHeader, CLACT_U_CELL_RES, NARC_WEATHER_SYS_WEATHER_CELL_RESDAT);
	loadResHeader(draw->resHeader, CLACT_U_CELLANM_RES, NARC_WEATHER_SYS_WEATHER_CELLANM_RESDAT);

	// �Z���A�N�^�[�Z�b�g�쐬
	{
		CLACT_SETDATA	set;	// �Z���A�N�^�[�Z�b�g�쐬�f�[�^
		// �Z���A�N�^�[�Z�b�g�쐬
		set.WorkNum = WEATEHR_OBJ_MAX;
		set.pRender	= &draw->Render;
		set.heap	= USE_HEAPID;
		draw->clactSet = CLACT_InitSet( &set );

		// �`��^�X�N����
		draw->clactDrawTcb = TCB_Add( clactSetDrawTcb, draw, WEATHER_CLACT_DRAW_TCB_PRI );
	} 
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�^�[�`��^�X�N
 */
//-----------------------------------------------------------------------------
static void clactSetDrawTcb( TCB_PTR tcb, void* p_work )
{
	WEATHER_SYS_DRAWSYS* p_draw = p_work;
	CLACT_Draw( p_draw->clactSet );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�w�b�_���P�ǂݍ���
 *
 *@param	head		�w�b�_�f�[�^�z��
 *@param	no			�ǂݍ��ރw�b�_�z��v�f
 *@param	arc_data	�A�[�J�C�u�t�@�C���f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadResHeader(CLACT_U_RES_HEADER_PTR head, int no, int arc_data)
{
	CLACT_U_RES_HEADER_PTR	w_head;		// ��Ɨp�w�b�_
	void* file;

	w_head = CLACT_U_ResManagerGetHeaderNoData(head, no);
//	CLACT_U_ResManagerHeaderLoad(path, w_head, USE_HEAPID);
	file = ArcUtil_Load( ARC_WEATHER_SYS_GRA, arc_data, FALSE, USE_HEAPID, ALLOC_BOTTOM );
	CLACT_U_ResManagerHeaderLoadBinary( file, w_head, USE_HEAPID );
	sys_FreeMemoryEz( file );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�`��V�X�e���f�[�^�j��
 *
 *@param	draw	�`��V�X�e���f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void delete2DDrawSys(WEATHER_SYS_DRAWSYS* draw)
{
	int i;
	CLACT_U_RES_HEADER_PTR	res_head;
	

	// ���\�[�X�w�b�_�j��
	// ���\�[�X�}�l�[�W���j��
	for(i=0;i < WEATHER_RES_NUM;i++){
		res_head = CLACT_U_ResManagerGetHeaderNoData(draw->resHeader, i);
		CLACT_U_ResManagerHeaderFree(res_head);		// �w�b�_�j��

		CLACT_U_ResManagerDelete(draw->resMan[i]);	// �}�l�[�W���j��
	}

	sys_FreeMemoryEz(draw->resHeader);
	draw->resHeader = NULL;

	// �Z���A�N�^�[�Z�b�g�j��
	CLACT_DestSet(draw->clactSet);
	draw->clactSet = NULL;

	TCB_Delete( draw->clactDrawTcb );
	draw->clactDrawTcb = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�V�C�f�[�^����֐�
 *
 *	@param	pData		�ݒ��
 *	@param	CellNo		�Z���f�[�^�̔z��v�f��
 *	@param	BGNo		BG�f�[�^�̔z��v�f��
 *	@param	WorkSize	���[�N�T�C�Y
 *	@param	func		�R���g���[���֐�
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setSysData(WEATHER_SYS_DATA* pData, int CellNo, int BGNo, int WorkSize, TCB_FUNC func)
{
	pData->GraphicNo	= CellNo;		// �Z��No
	pData->BGNo			= BGNo;			// BGNo
	pData->WorkByte		= WorkSize;		// �V�C�V�X�e�����[�N�T�C�Y
	pData->pWork		= NULL;			// �V�X�e�����[�N����
	pData->pCell		= NULL;			// �ǂݍ��񂾃Z���f�[�^
	pData->cont			= func;			// CONTROL�֐�
	pData->MoveFlag		= WEATHER_SYS_MOVE_NONE;	// ������
	pData->DivInitSeq	= 0;			// �����������V�[�P���X
	pData->DivInitTcb	= NULL;			// �����ǂݍ���TCB
}
//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�f�[�^�ݒ�֐�
 *
 *	@param	pData			�f�[�^�i�[��
 *	@param	PlttPath		�p���b�g�p�X
 *	@param	CharPath		�L�����N�^�p�X
 *	@param	ScreenPath		�X�N���[���f�[�^�p�X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setBGData(WEATHER_BG_DATA* pData, int pltt_arc, int char_arc, int screen_arc )
{
	pData->pltt_arc = pltt_arc;
	pData->char_arc = char_arc;
	pData->screen_arc = screen_arc;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�N�^�[�ɍ��W��ݒ�
 *
 *	@param	act			�A�N�^�[
 *	@param	matrix		���W
 *
 *	@return	none
 *
 * �T�[�t�F�[�X���̍��W�Ő܂�Ԃ��悤�ɕ␳���s���Ă���
 * �o�^���Ă��܂��B
 *
 */
//-----------------------------------------------------------------------------
static void setClactMatrix( CLACT_WORK_PTR act, VecFx32* matrix )
{
	// �܂�Ԃ�����
	if(matrix->x > WEATHER_OBJ_MAXTURN_X){
		matrix->x %= WEATHER_OBJ_MAXTURN_X;
	}else{

		if( matrix->x < WEATHER_OBJ_MINTURN_X ){	
			matrix->x += WEATHER_OBJ_MAXTURN_X;
		}
	}

	if(matrix->y > WEATHER_OBJ_MAXTURN_Y){
		matrix->y %= WEATHER_OBJ_MAXTURN_Y;
	}else{

		if( matrix->y < WEATHER_OBJ_MINTURN_Y ){	
			matrix->y += WEATHER_OBJ_MAXTURN_Y;
		}
	}

	
	CLACT_SetMatrix( act, matrix );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	���V�C�V�X�e����������
 *
 *@param	fsys		�t�B�[���h�V�X�e�����[�N
 *
 *@return	WEATHER_CONT_PTR	�V�C�V�X�e������f�[�^
 *
 *	���e
 *		�V�C�V�X�e���̐���f�[�^���쐬
 *		fast_cell�V�X�e����OAM�o�b�t�@�쐬
 *		�L�����N�^�A�p���b�g��ENTRY�f�[�^�ǂݍ���
 *
 */
//-----------------------------------------------------------------------------
WEATHER_CONT_PTR InitWeatherSys(FIELDSYS_WORK* fsys)
{
	WEATHER_CONT_PTR pWSYSCONT;

	pWSYSCONT = sys_AllocMemory( USE_HEAPID, sizeof(WEATHER_SYS_CONTROL) );
	// �t�H�O�f�[�^�i�[���ۑ�
	pWSYSCONT->fsys = fsys;

	// �`��V�X�e��������
	init2DDrawSys(&pWSYSCONT->Draw);

	// �V�C�V�X�e���f�[�^�쐬
	pWSYSCONT->pWSD = WSD;
	pWSYSCONT->pWSBG = WSBG;

	// �A�[�J�C�u�t�@�C���n���h���I�[�v��
	 pWSYSCONT->ArcHandle = ArchiveDataHandleOpen( ARC_WEATHER_SYS_GRA, USE_HEAPID );
	
	return pWSYSCONT;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���V�C�V�X�e����j��
 *
 *@param	pWes		�V�C����f�[�^�|�C���^
 *
 *@return	none
 *
 *	���e
 *		���삵�Ă���V�C�Ǘ��֐��^�X�N�̋����I��---�����Ă���I�u�W�F�N�g�^�X�N�������I��
 *		�L�����N�^�A�p���b�g��ENTRY�f�[�^�j��
 *
 */
//-----------------------------------------------------------------------------
void DestWeatherSys(WEATHER_CONT_PTR* pWes)
{
	int i;		// ���[�v�p
	
	if(*pWes != NULL){
		
		// ���삵�Ă���V�C�Ǘ��^�X�N�̋����I��
		for(i=0;i<WEATHER_SYS_NUM;i++){
			destWeatherSys(*pWes, i);
		}
		
		SetFogData((*pWes)->fsys->fog_data, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
		
		G2_SetBG0Priority(1);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );

		// �O���t�B�b�N�`��V�X�e���j��
		delete2DDrawSys(&(*pWes)->Draw);

		// �A�[�J�C�u�t�@�C���n���h���j��
		ArchiveDataHandleClose( (*pWes)->ArcHandle );
		
		// �Ǘ��f�[�^�j��
		sys_FreeMemory(USE_HEAPID,*pWes);
		*pWes = NULL;
	}
} 

//----------------------------------------------------------------------------
/**
 *
 *@brief	���V�C�V�X�e���R���g���[���֐�
 *
 *@param	Wes			���V�C����f�[�^
 *@param	cont		�R���g���[���i���o�[
 *@param	no			���V�C�i���o�[
 *
 *@return	BOOL	����:TRUE	���s:FALSE
 *
 *	����
 *		cont
 *			WEATHER_SYS_START=0				// ����J�n
 *			WEATHER_SYS_END=1				// ����I��(�t�F�[�h���ďI���)
 *			WEATHER_SYS_COMPULSION_END=2	// �����I��
 *		
 *		cont�̃i���o�[�ɂ�肨�V�C�Ǘ��^�X�N�𑀍삷��
 * 
 */
//-----------------------------------------------------------------------------
BOOL ControlWeatherSys(WEATHER_CONT_PTR Wes, int cont, int no)
{
	BOOL ret = TRUE;

	// �V�C�i���o�[�`�F�b�N
	if( no > WEATHER_SYS_NUM ){
		return FALSE;
	}
	
	
	switch(cont){
	case WEATHER_SYS_INIT:		// ���V�C�Ǘ��^�X�N������
		ret = initWeatherSys(Wes, no);
		break;
	case WEATHER_SYS_INIT_DIV:	// ���V�C�����������^�X�N�o�^
		ret = divInitWeatherSysCall( Wes, no );
		break;
	case WEATHER_SYS_START:		// ���V�C�Ǘ��^�X�N�o�^
		ret = startWeatherSys(Wes, no, WEATHER_SEQ_INIT, WEATEHR_FOG_NEW);
		break;

	case WEATHER_SYS_START_NOFADE:	// �t�F�[�h�C�����΂�
		ret = startWeatherSys( Wes, no, WEATHER_SEQ_NO_FADE, WEATEHR_FOG_NEW );
		break;

	case WEATHER_SYS_START_WITHFOG:	// �t�F�[�h�C�����΂�
		// ��������FOG�ݒ肳��Ă��Ȃ���΁A�ʏ�̃t�H�O�t�F�[�h�ɂ���
		if( GetFogFlag( Wes->fsys->fog_data ) == TRUE ){
			ret = startWeatherSys( Wes, no, WEATHER_SEQ_INIT, WEATHER_FOG_WITH );
		}else{
			ret = startWeatherSys(Wes, no, WEATHER_SEQ_INIT, WEATEHR_FOG_NEW);
		}
		break;

	case WEATHER_SYS_END:		// ���V�C�Ǘ��^�X�N����I��
		stopReqWeatherSys(Wes, no, WEATEHR_FOG_NEW);
		break;

	case WEATHER_SYS_END_NOFADE:// �t�F�[�h�A�E�g�Ȃ��I��
		stopWeatherSys(Wes, no);
		break;

	case WEATHER_SYS_END_NOFOG:
		stopReqWeatherSys(Wes, no, WEATHER_FOG_NONE);
		break;

	case WEATHER_SYS_DEST:		// ���V�C�Ǘ��^�X�N�j��
		destWeatherSys(Wes, no);
		break;

	default:
		break;
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�V�C���I�����Ă����Ԃ��`�F�b�N����
 *
 *	@param	Wes			�V�C
 *	@param	no			�V�C�i���o�[
 *
 *	@retval	WEATHER_SYS_MOVE_NONE   	��������
 *	@retval	WEATHER_SYS_MOVE_INIT		��������
 *  @retval WEATHER_SYS_MOVE_READY		�J�n�ҋ@��
 *  @retval WEATHER_SYS_MOVE_DO			���쒆
 */
//-----------------------------------------------------------------------------
int CheckMoveWeatherSys(WEATHER_CONT_PTR Wes, int no)
{
	WEATHER_SYS_DATA* w_sys;

	// �V�C�i���o�[�`�F�b�N
	if(no >= WEATHER_SYS_NUM){
		return WEATHER_SYS_MOVE_NONE;
	}
	
	w_sys = Wes->pWSD+no;

	// �V�C���̂����邩�`�F�b�N
	return w_sys->MoveFlag;
}


//-----------------------------------------------------------------------------
//	�v���C�x�[�g�֐�
//		���̑�
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	BG�f�t�H���g���ݒ�
 *
 *	@param	alpha1		���W���P
 *	@param	alpha2		���W���Q
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void WeatherBGAlphaDef( int alpha1, int alpha2 )
{
	G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BD, alpha1, alpha2);
}

//----------------------------------------------------------------------------
/**
 *	@brief	���쏉����
 *
 *	@param	p_work			���샏�[�N
 *	@param	s_x				�J�nx���W
 *	@param	e_x				�I��x���W
 *	@param	count_max		�J�E���g�ő�l
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void WeatherMoveReq( WEATHER_SYS_MOVE_WORK* p_work, int s_x, int e_x, int count_max )
{
	p_work->x = s_x;

	p_work->s_x = s_x;
	p_work->dis_x = e_x - s_x;
	p_work->count_max = count_max;
	p_work->count = 0;
}
//----------------------------------------------------------------------------
/**
 *	@brief	���상�C��
 *
 *	@param	p_work	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL	WeatherMoveMain( WEATHER_SYS_MOVE_WORK* p_work )
{
	int w_x;

	// ���ݍ��W�擾
	w_x = p_work->dis_x * p_work->count;
	w_x = w_x / p_work->count_max;

	
	p_work->x = w_x + p_work->s_x;

	if( (p_work->count + 1) <= p_work->count_max ){
		p_work->count++;
		return FALSE;
	}

	p_work->count = p_work->count_max;
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�C�@�ėp���샏�[�N���N�G�X�g
 *
 *	@param	p_work		���[�N
 *	@param	s_x			�J�n�l
 *	@param	e_x			�I���l
 *	@param	count_max	�J�E���g�ő吔
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void WeatherMoveReqFx( WEATHER_SYS_MOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, int count_max )
{
	p_work->x = s_x;

	p_work->s_x = s_x;
	p_work->dis_x = e_x - s_x;
	p_work->count_max = count_max;
	p_work->count = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�C�@�ėp�v�Z�@���C������
 *
 *	@param	p_work ���[�N
 *
 *	@retval	TRUE		�I��
 *	@retval	FALSE		�r��
 */
//-----------------------------------------------------------------------------
static BOOL	WeatherMoveMainFx( WEATHER_SYS_MOVE_WORK_FX* p_work )
{
	fx32 w_x;

	// ���ݍ��W�擾
	w_x = FX_Mul( p_work->dis_x, p_work->count );
	w_x = FX_Div( w_x, p_work->count_max );

	
	p_work->x = w_x + p_work->s_x;

	if( (p_work->count + 1) <= p_work->count_max ){
		p_work->count++;
		return FALSE;
	}

	p_work->count = p_work->count_max;
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�O���t�B�b�N�f�[�^�ǂݍ���
 *
 *@param	cont			�V�C�R���g���[��
 *@param	GraphicNo		�Z���p�X�f�[�^
 *@param	pCell			�i�[��
 *
 *@return	none
 *
 *	���e
 *		GraphicNo�̊G�̃f�[�^��ǂݍ���
 *		pCell�̃����o�Ɋi�[����
 *
 */
//-----------------------------------------------------------------------------
static void load2DGraphicFile(WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell)
{
	// �Z���ǂݍ���
	loadCell_CellData( cont, GraphicNo, pCell );

	// �Z���A�j���ǂݍ���
	loadCell_CellAnmData( cont, GraphicNo, pCell );

	// �L�����N�^�ǂݍ���
	loadCell_CharData( cont, GraphicNo, pCell );

	// �p���b�g�ǂݍ���
	loadCell_PlttData( cont, GraphicNo, pCell );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�}�l�[�W���ɓo�^
 *	
 *@param	res_head	���\�[�X�w�b�_
 *@param	res_type	���\�[�X�^�C�v
 *@param	head_no		�w�b�_�i���o�[
 *@param	resMan		���\�[�X�}�l�[�W��
 *@param	arcHandle	�A�[�J�C�u�t�@�C���n���h��
 *
 *@return	CLACT_U_RES_OBJ_PTR		�ǂݍ��܂ꂽ���\�[�X���
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_U_RES_OBJ_PTR	loadRes(CLACT_U_RES_HEADER_PTR res_head, int res_type, int head_no, CLACT_U_RES_MANAGER_PTR resMan, ARCHANDLE* arcHandle, u32 alloc_type)
{
	CLACT_U_RES_HEADER_PTR	w_head;	// ��Ɨp�w�b�_
	CLACT_U_RES_OBJ_PTR		res_obj;
	int data_idx;
	BOOL comp_flg;
	int vram_type;
	int pltt_num;
	int data_id;

	// ���\�[�X�̃w�b�_�擾
	w_head = CLACT_U_ResManagerGetHeaderNoData(res_head, res_type);

	// �w�b�_�[�f�[�^�擾
	data_idx	= CLACT_U_ResManagerHeaderDataIdxGet( w_head, head_no );
	comp_flg	= CLACT_U_ResManagerHeaderCompFlagGet( w_head, head_no );
	vram_type	= CLACT_U_ResManagerHeaderVramTypeGet( w_head, head_no );
	pltt_num	= CLACT_U_ResManagerHeaderPlttNumGet( w_head, head_no );
	data_id		= CLACT_U_ResManagerHeaderDataIDGet( w_head, head_no );

	switch( res_type ){
	case CLACT_U_CHAR_RES:		// �L�����N�^���\�[�X���Ǘ�
		res_obj = CLACT_U_ResManagerResAddArcChar_ArcHandle_AllocType( resMan, arcHandle, data_idx, comp_flg, data_id, vram_type, USE_HEAPID, alloc_type );
		break;
		
	case CLACT_U_PLTT_RES:		// �p���b�g���\�[�X���Ǘ�
		res_obj = CLACT_U_ResManagerResAddArcPltt_ArcHandle_AllocType( resMan, arcHandle, data_idx, comp_flg, data_id, vram_type, pltt_num, USE_HEAPID, alloc_type );
		break;
		
	case CLACT_U_CELL_RES:		// �Z�����\�[�X���Ǘ�
		res_obj = CLACT_U_ResManagerResAddArcKindCell_ArcHandle( resMan, arcHandle, data_idx, comp_flg, data_id, CLACT_U_CELL_RES, USE_HEAPID );
		break;
		
	case CLACT_U_CELLANM_RES:	// �Z���A�j�����\�[�X���Ǘ�
		res_obj = CLACT_U_ResManagerResAddArcKindCell_ArcHandle( resMan, arcHandle, data_idx, comp_flg, data_id, CLACT_U_CELLANM_RES, USE_HEAPID );
		break;
	}
	
	// ���\�[�X�ǂݍ���
	return res_obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�O���t�B�b�N�f�[�^�j��
 *
 *@param	cont			�V�C�R���g���[��
 *@param	GraphicNo		�O���t�B�b�N�i���o�[
 *@param	pCell			�O���t�B�b�N�f�[�^�i�[�ʒu
 *
 *@return	none
 *
 *	���e
 *		GraphicNo�̊G�̃f�[�^��j������
 *
 */
//-----------------------------------------------------------------------------
static void destGraphicFile(WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell)
{
	int i;	

	if(GraphicNo != WEATHER_GRAPHIC_NONE){
		// �L�����N�^�f�[�^�j��
		if( pCell->res_obj[ CLACT_U_CHAR_RES ] ){
			CLACT_U_CharManagerDelete(pCell->res_obj[ CLACT_U_CHAR_RES ]);
		}

		// �p���b�g�f�[�^�j��
		if( pCell->res_obj[ CLACT_U_PLTT_RES ] ){
			CLACT_U_PlttManagerDelete(pCell->res_obj[ CLACT_U_PLTT_RES ]);
		}

		// ���\�[�X�j��
		for(i=0;i<WEATHER_RES_NUM;i++){
			if( pCell->res_obj[ i ] ){
				CLACT_U_ResManagerResDelete(cont->Draw.resMan[ i ], pCell->res_obj[ i ]);
			}
		}
	}
}


//-----------------------------------------------------------------------------
//	�v���C�x�[�g�֐�
//		���V�C�Ǘ��^�X�N���O�����瑀�삷��֐��S
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	���V�C�Ǘ��^�X�N������
 *
 *
 *@param	cont	�V�C�R���g���[��
 *@param	no		�V�C�i���o�[
 *
 *@return	BOOL	����:TRUE	���s:FALSE
 *
 *	���e
 *		�O���t�B�b�N�t�@�C���̓ǂݍ��ݏ���
 *
 */
//-----------------------------------------------------------------------------
static BOOL initWeatherSys(WEATHER_SYS_CONTROL* cont,int no)
{
	WEATHER_SYS_DATA* w_sys = cont->pWSD+no;
	BOOL ret;
	
	
	// �쐬����Ă��邩�`�F�b�N
	if(w_sys->pWork == NULL){
		// ���[�N�̍쐬
		ret = initWeatherSysWork( cont, w_sys );
		if( ret == FALSE ){
			return FALSE;
		}
	
		// �Z���A�N�^�[���g�p�ł����Ԃɂ���
		ret = setUpCell( cont, w_sys );
		if( ret == FALSE ){
			sys_FreeMemoryEz( w_sys->pWork );
			w_sys->pWork = NULL;
			return FALSE;
		}
		w_sys->pWork->pCell = w_sys->pCell;		// �Z���f�[�^�R�s�[

		// BG�Z�b�g�A�b�v
		setUpBG( cont, w_sys->BGNo );

		w_sys->MoveFlag = WEATHER_SYS_MOVE_READY;	// �J�n�ҋ@��
	}


	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���V�C�Ǘ��^�X�N�h�����h�������^�X�N�R�[��
 *
 *
 *@param	cont	�V�C�R���g���[��
 *@param	no		�V�C�i���o�[
 *
 *@return	BOOL	����:TRUE	���s:FALSE
 *
 *	���e
 *		�O���t�B�b�N�t�@�C���̓ǂݍ��ݏ���
 *
 */
//-----------------------------------------------------------------------------
static BOOL divInitWeatherSysCall(WEATHER_SYS_CONTROL* cont,int no)
{
	WEATHER_SYS_DATA* w_sys = cont->pWSD+no;
	
	// �쐬�ς݂��`�F�b�N
	if( w_sys->pWork ){
		return TRUE;
	}

	// ���[�N���쐬����
	if( initWeatherSysWork( cont, w_sys ) == FALSE ){
		return FALSE;
	}

	// �^�X�N�o�^
	w_sys->DivInitTcb = TCB_Add( divInitWeatherSysTcb, w_sys, WEATHER_TCB_DIV_LOAD_PRI );

	// ���������ɂ���
	w_sys->MoveFlag		= WEATHER_SYS_MOVE_INIT;

	// �������V�[�P���X������
	w_sys->DivInitSeq	= 0;
	

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���V�C�Ǘ��^�X�N�J�n
 *
 *@param	cont		�V�C�R���g���[��
 *@param	no			�V�C�i���o�[
 *@param	init_seq	�V�[�P���X�������l
 *@param	fog_use		�t�H�O�g�p�t���O
 *
 *@return	BOOL	����:TRUE	���s:FALSE
 *
 *	���e
 *		�i���o�[�̂��V�C�Ǘ��^�X�N���J�n���܂��B
 *
 */
//-----------------------------------------------------------------------------
static BOOL startWeatherSys(WEATHER_SYS_CONTROL* cont,int no, int init_seq, u32 fog_use)
{
	WEATHER_SYS_DATA* w_sys = cont->pWSD+no;
	
	// �G���ǂݍ��܂�Ă��邩�`�F�b�N
	if(w_sys->GraphicNo != WEATHER_GRAPHIC_NONE){
		if(w_sys->pCell == NULL){
			return FALSE;
		}
	}

	// �^�X�N���[�N���쐬����Ă��邩�`�F�b�N
	if(w_sys->pWork == NULL){
		return FALSE;
	}

	// �J�n�҂���Ԃ��`�F�b�N
	if(w_sys->MoveFlag != WEATHER_SYS_MOVE_READY){
		return FALSE;
	}

	// �^�X�N�o�^
	w_sys->pWork->tcb = TCB_Add(w_sys->cont, w_sys->pWork, WEATHER_CONTROL_PRI);

	// �^�X�N�o�^�ɐ����������`�F�b�N
	if(w_sys->pWork->tcb == NULL){
		return FALSE;
	}

	// ���s
	w_sys->MoveFlag = WEATHER_SYS_MOVE_DO;
	
	// �f�[�^�ݒ�
	w_sys->pWork->Sequence = init_seq;		// ��ƃV�[�P���X������
	w_sys->pWork->ContFlag = 0;				// �O���R���g���[���t���O
	w_sys->pWork->Dummy.pNext = &w_sys->pWork->Dummy;
	w_sys->pWork->Dummy.pPrev = &w_sys->pWork->Dummy;
	w_sys->pWork->fog_use	= fog_use;		// �t�H�O�g�p�t���O
	w_sys->pWork->snd_play		= FALSE;

	w_sys->pWork->CameraTarget = *(NNS_G3dGlbGetCameraTarget());
	if(w_sys->WorkByte > 0){
		w_sys->pWork->work = sys_AllocMemory(USE_HEAPID, w_sys->WorkByte);	// ���[�N�̈�
		memset( w_sys->pWork->work, 0, w_sys->WorkByte );
	}else{
		w_sys->pWork->work = NULL;
	}

	// BG�Z�b�g�A�b�v
	if(w_sys->BGNo != WEATHER_GRAPHIC_NONE){
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		G2_SetBG2Priority(1);
		G2_SetBG0Priority(2);
//		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���V�C�Ǘ��^�X�N�I��	�t�F�[�h�A�E�g���Ă���I��
 *
 *@param	cont	�V�C�R���g���[��
 *@param	no		�V�C�i���o�[
 *@param	fog_use	�t�H�O�g�p�t���O
 *
 *@return	none
 *
 *	���e
 *		�i���o�[�̂��V�C�Ǘ��^�X�N���t�F�[�h�A�E�g�I�������܂�
 *		*��F���񂾂�J���~��ŏI���Ȃ�
 *
 */
//-----------------------------------------------------------------------------
static void stopReqWeatherSys(WEATHER_SYS_CONTROL* cont,int no, u32 fog_use)
{
	WEATHER_SYS_DATA* w_sys = cont->pWSD+no;

	// ���V�C�Ǘ��^�X�N�������Ă��邩�`�F�b�N
	if(w_sys->MoveFlag == WEATHER_SYS_MOVE_DO){
		w_sys->pWork->ContFlag = WEATHER_SYS_END;	// �I���t���O�𗧂Ă�
		w_sys->pWork->fog_use = fog_use;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�V�C�I��	�t�F�[�h�A�E�g�Ȃ�
 *
 *	@param	cont	�V�C�R���g���[��
 *	@param	no		�V�C�i���o�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void stopWeatherSys( WEATHER_SYS_CONTROL* cont,int no )
{
	WEATHER_SYS_DATA* w_sys = cont->pWSD+no;
	
	if( CheckMoveWeatherSys( cont, no ) == WEATHER_SYS_MOVE_DO ){
		// �V�C�̃V�[�P���X��WEATHER_SEQ_DEST�ɂ��ăR���g���[���֐����R�[��
		w_sys->pWork->Sequence = WEATHER_SEQ_DEST;
	
		w_sys->cont( NULL, w_sys->pWork );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���V�C�Ǘ��^�X�N�����I��
 *
 *@param	cont	�V�C�R���g���[��
 *@param	no		�V�C�i���o�[
 *
 *@return	none
 *
 *	���e
 *		�Ǘ����Ă���I�u�W�F��S�Ĕj��
 *		�G�̃f�[�^��j��
 *		������j��
 *
 */
//-----------------------------------------------------------------------------
static void destWeatherSys(WEATHER_SYS_CONTROL* cont,int no)
{
	WEATHER_SYS_DATA* w_sys = cont->pWSD+no;
	
	// BG�ʂ̕\����OFF
	if(w_sys->BGNo != WEATHER_GRAPHIC_NONE ){
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		G2_SetBG2Priority(3);
		G2_SetBG0Priority(1);

		//�@���u�����h�j��
		G2_BlendNone();
	}
	
	// �G�̃f�[�^�j��
	if(w_sys->pCell != NULL){
		// �G�̃f�[�^�j��
		destGraphicFile(cont, w_sys->GraphicNo, w_sys->pCell);
		sys_FreeMemory(USE_HEAPID, w_sys->pCell);
		w_sys->pCell = NULL;

		// �����ǂݍ��݃^�X�N�j��
		if( w_sys->DivInitTcb != NULL ){
			TCB_Delete( w_sys->DivInitTcb );
			w_sys->DivInitTcb = NULL;
		}
	}
	
	// ���V�C�Ǘ��^�X�N�������Ă��邩�`�F�b�N
	if(w_sys->pWork != NULL){
		// �Ǘ����Ă���I�u�W�F��j��
		destObjAll(&w_sys->pWork->Dummy);

		// �������Ă���Ȃ�j��
		if( w_sys->pWork->snd_play == TRUE ){
			WeatherLoopSndStop( w_sys->pWork );
		}

		// ���[�N�̈�
		if(w_sys->pWork->work != NULL){
			sys_FreeMemory(USE_HEAPID, w_sys->pWork->work);
			w_sys->pWork->work = NULL;
		}
/*	CLACT_SET_DELETE
		// �A�N�^�[�Z�b�g�j��
		if( w_sys->pWork->clactSet ){
			CLACT_DestSet(w_sys->pWork->clactSet);
		}
//*/
		// �������^�X�N��j��
		if( w_sys->MoveFlag == WEATHER_SYS_MOVE_INIT ){
			
			if( w_sys->DivInitTcb ){
				TCB_Delete(w_sys->DivInitTcb);					// TCB�j��
			}
		}else{
			
			// ����^�X�N��j��
			if(w_sys->MoveFlag == WEATHER_SYS_MOVE_DO){
				
				TCB_Delete(w_sys->pWork->tcb);					// TCB�j��
			}
		}
		sys_FreeMemory(USE_HEAPID, w_sys->pWork);	// ���[�N�j��
		w_sys->pWork = NULL;
	}
}


// �V�X�e������T�u�֐�
//----------------------------------------------------------------------------
/**
 *
 *	@brief	no�̓V�C�̓V�C�V�X�e���f�[�^��j��
 *
 *	@param	cont		�V�C����V�X�e��
 *	@param	no			�V�Cno
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void stopWeatherWork(WEATHER_SYS_CONTROL* cont,int no)
{
	WEATHER_SYS_DATA* w_sys = cont->pWSD+no;
	stopWeatherWork_local( w_sys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�C�V�X�e���f�[�^��j��
 *	@param	w_sys
 *	@return
 */
//-----------------------------------------------------------------------------
static void stopWeatherWork_local(WEATHER_SYS_DATA* w_sys)
{
	// BG�ʂ̕\����OFF
	if(w_sys->BGNo != WEATHER_GRAPHIC_NONE ){
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		G2_SetBG2Priority(3);
		G2_SetBG0Priority(1);
		//�@���u�����h�j��
		G2_BlendNone();
	}

	// ���V�C�Ǘ��^�X�N�������Ă��邩�`�F�b�N
	if(w_sys->pWork != NULL){
		// �Ǘ����Ă���I�u�W�F��j��
		destObjAll(&w_sys->pWork->Dummy);

		// �������Ă���Ȃ�j��
		if( w_sys->pWork->snd_play == TRUE ){
			WeatherLoopSndStop( w_sys->pWork );
		}
		
		// �^�X�N��j��
		if(w_sys->MoveFlag == WEATHER_SYS_MOVE_DO){
			
			TCB_Delete(w_sys->pWork->tcb);					// TCB�j��
			w_sys->MoveFlag = WEATHER_SYS_MOVE_READY;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�f�[�^�Z�b�g�A�b�v
 *
 *	@param	cont	�V�C�R���g���[���f�[�^
 *	@param	BGNo	BG�i���o�[
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setUpBG( WEATHER_SYS_CONTROL* cont, int BGNo )
{
	// �p���b�g�ǂݍ���
	initBgPltt( cont, BGNo );
	
	// �L�����N�^�ǂݍ���
	initBgChar( cont, BGNo );

	// �X�N���[���f�[�^
	initBgScr( cont, BGNo );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�N�^�[���g�p�ł����Ԃɂ���
 *
 *	@param	cont		�R���g���[���f�[�^
 *	@param	w_sys		�f�[�^�S
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL setUpCell( WEATHER_SYS_CONTROL* cont, WEATHER_SYS_DATA* w_sys )
{
	BOOL ret;

	// �Z���f�[�^���K�v���`�F�b�N
	if( w_sys->GraphicNo  != WEATHER_GRAPHIC_NONE ){
		
/*	CLACT_SET_DELETE
		// �Z���A�N�^�[�Z�b�g������
		initClactSet( cont, w_sys );
//*/

		// �Z���f�[�^�쐬�ς݂��`�F�b�N
		if( w_sys->pCell == NULL ){

			// �Z���f�[�^�i�[�������m��
			ret = initCellDataMemory( w_sys );
			if( ret == FALSE ){
/*	CLACT_SET_DELETE
				// �A�N�^�[�Z�b�g�j��
				CLACT_DestSet(w_sys->pWork->clactSet);
//*/
				return FALSE;
			}

			// �Z���A�N�^�[�o�^�f�[�^�쐬
			// �ǂݍ���
			load2DGraphicFile(cont, w_sys->GraphicNo, w_sys->pCell);

			// �Z���A�N�^�[�o�^�f�[�^�쐬
			initClactAddData( cont, w_sys );
		}
	}

	return TRUE;
}


// ���������������֐�
//----------------------------------------------------------------------------
/**
 *
 *	@brief	��������TCB
 *
 *	@param	tcb		�^�X�N�|�C���^
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void divInitWeatherSysTcb( TCB_PTR tcb, void* work )
{
	WEATHER_SYS_DATA* w_sys = work;
	WEATHER_SYS_CONTROL* cont = w_sys->pWork->pWSysCont;
	BOOL check;

	switch( w_sys->DivInitSeq ){
	case 0:

/*	CLACT_SET_DELETE
		// �Z���A�N�^�[�Z�b�g������
		initClactSet( cont, w_sys );
//*/

		// �Z���f�[�^�i�[�惁�����m��
		check = initCellDataMemory( w_sys );
		GF_ASSERT( check );
		w_sys->DivInitSeq++;
		break;

	case 1:
		// �Z���f�[�^�ǂݍ���
		loadCell_CellData( cont, w_sys->GraphicNo, w_sys->pCell );
		w_sys->DivInitSeq++;
		break;

	case 2:
		// �p���b�g�ǂݍ���
		initBgPltt( cont, w_sys->BGNo );
		w_sys->DivInitSeq++;
		break;

	case 3:
		// �Z���A�j���f�[�^�ǂݍ���
		loadCell_CellAnmData( cont, w_sys->GraphicNo, w_sys->pCell );
		w_sys->DivInitSeq++;
		break;

	case 4:
		// �L�����N�^�ǂݍ���
		initBgChar( cont, w_sys->BGNo );
		w_sys->DivInitSeq++;
		break;

	case 5:
		// �L�����N�^�f�[�^�ǂݍ���
		loadCell_CharData( cont, w_sys->GraphicNo, w_sys->pCell );
		w_sys->DivInitSeq++;
		break;
		
	case 6:
		// �X�N���[���ǂݍ���
		initBgScr( cont, w_sys->BGNo );
		w_sys->DivInitSeq++;
		break;

	case 7:
		// �p���b�g�f�[�^�ǂݍ���
		loadCell_PlttData( cont, w_sys->GraphicNo, w_sys->pCell );
		w_sys->DivInitSeq++;
		break;
	
	case 8:
		// �Z���A�N�^�[�ǉ��f�[�^�쐬
		initClactAddData( cont, w_sys );
		w_sys->pWork->pCell = w_sys->pCell;		// �Z���f�[�^�R�s�[

		w_sys->MoveFlag = WEATHER_SYS_MOVE_READY;	// �J�n�ҋ@��
		w_sys->DivInitSeq = 0;
		w_sys->DivInitTcb = NULL;
		TCB_Delete( tcb );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���[�N�̃������m��
 *
 *	@param	cont	�R���g���[��
 *	@param	w_sys	���[�N�̊i�[��
 *
 *	@retval	TRUE	����
 *	@retval	FALSE	���s
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL initWeatherSysWork( WEATHER_SYS_CONTROL* cont, WEATHER_SYS_DATA* w_sys )
{
	if( w_sys->pWork ){
		// �m�ۍς�
		return TRUE;
	}
	
	// ���[�N�̍쐬
	w_sys->pWork = sys_AllocMemory(USE_HEAPID, sizeof(WEATHER_SYS_WORK));
	if(w_sys->pWork == NULL){
		return FALSE;
	}
	memset( w_sys->pWork, 0, sizeof(WEATHER_SYS_WORK) );

	// �f�[�^�ݒ�
	w_sys->pWork->pWSysCont= cont;	// �R���g���[���|�C���g
	w_sys->pWork->Sequence = 0;		// ��ƃV�[�P���X������
	w_sys->pWork->ContFlag = 0;		// �O���R���g���[���t���O
	w_sys->pWork->Dummy.pNext = &w_sys->pWork->Dummy;
	w_sys->pWork->Dummy.pPrev = &w_sys->pWork->Dummy;
	w_sys->pWork->work	= NULL;		// ���[�N�̈�
	w_sys->pWork->pWSD	= w_sys;	// �������q���ɂ������Ă���

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�N�^�[�Z�b�g�̍쐬
 *
 *	@param	cont		�R���g���[��
 *	@param	w_sys		�V�C�f�[�^�i�[��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initClactSet( WEATHER_SYS_CONTROL* cont, WEATHER_SYS_DATA* w_sys )
{

/*	CLACT_SET_DELETE
	CLACT_SETDATA	set;	// �Z���A�N�^�[�Z�b�g�쐬�f�[�^


	if( w_sys->GraphicNo != WEATHER_GRAPHIC_NONE){
		
		if( w_sys->pWork->clactSet ){
			// �m�ۍς�
			return;
		}

		// �Z���A�N�^�[�Z�b�g�쐬
		set.WorkNum = WEATEHR_OBJ_MAX;
		set.pRender	= &cont->Draw.Render;
		set.heap	= USE_HEAPID;
		w_sys->pWork->clactSet = CLACT_InitSet( &set );
	}
//*/
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���f�[�^�i�[�惁�����̈�m��
 *
 *	@param	w_sys	�V�C�f�[�^�i�[��
 *
 *	@retval TRUE	����
 *	@retval FALSE	���s
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL initCellDataMemory( WEATHER_SYS_DATA* w_sys )
{
	if( w_sys->GraphicNo != WEATHER_GRAPHIC_NONE){
		if( w_sys->pCell ){

			return TRUE;	// �m�ۍς�
		}
		
		// �O���t�B�b�N�t�B�b�N�t�@�C����ǂݍ��ޗ̈���쐬
		w_sys->pCell = sys_AllocMemory(USE_HEAPID, sizeof(WATHER_GRAPHIC_FILE_DATA));
		if(w_sys->pCell == NULL){
			return FALSE;
		}
		memset( w_sys->pCell, 0, sizeof(WATHER_GRAPHIC_FILE_DATA) );
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�N�^�[�f�[�^�@�@�Z���ǂݍ���
 *
 *	@param	cont			�R���g���[��
 *	@param	GraphicNo		�O���t�B�b�N�i���o�[
 *	@param	pCell			�Z���f�[�^�i�[��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadCell_CellData( WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell )
{
	if(GraphicNo != WEATHER_GRAPHIC_NONE){
	
		// �Z���f�[�^�ǂݍ���
		pCell->res_obj[ CLACT_U_CELL_RES ] = loadRes(
				cont->Draw.resHeader, CLACT_U_CELL_RES, 
				GraphicNo,
				cont->Draw.resMan[ CLACT_U_CELL_RES ],
				cont->ArcHandle, ALLOC_TOP );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�N�^�[�f�[�^	�Z���A�j���ǂݍ���
 *
 *	@param	cont			�R���g���[��
 *	@param	GraphicNo		�O���t�B�b�N�t�@�C���i���o�[
 *	@param	pCell			�Z���f�[�^�i�[��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadCell_CellAnmData( WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell )
{
	if(GraphicNo != WEATHER_GRAPHIC_NONE){
	
		// �Z���A�j���f�[�^�ǂݍ���
		pCell->res_obj[ CLACT_U_CELLANM_RES ] = loadRes(
				cont->Draw.resHeader, CLACT_U_CELLANM_RES, 
				GraphicNo,
				cont->Draw.resMan[ CLACT_U_CELLANM_RES ],
				cont->ArcHandle, ALLOC_TOP );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�N�^�[�f�[�^�ǂݍ���	�L�����N�^�f�[�^
 *
 *	@param	cont			�R���g���[��
 *	@param	GraphicNo		�O���t�B�b�N�f�[�^�i���o�[
 *	@param	pCell			�Z���f�[�^�i�[��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadCell_CharData( WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell )
{
	if(GraphicNo != WEATHER_GRAPHIC_NONE){
	
		// �L�����N�^�f�[�^�ǂݍ���
		pCell->res_obj[ CLACT_U_CHAR_RES ] = loadRes(
				cont->Draw.resHeader, CLACT_U_CHAR_RES, 
				GraphicNo,
				cont->Draw.resMan[ CLACT_U_CHAR_RES ],
				cont->ArcHandle, ALLOC_BOTTOM );
		
		// Vram�]��
		CLACT_U_CharManagerSetAreaCont( pCell->res_obj[ CLACT_U_CHAR_RES ] );
		// �L�����N�^�̓ǂݍ���ł����f�[�^�̂ݔj��
		CLACT_U_ResManagerResOnlyDelete( pCell->res_obj[ CLACT_U_CHAR_RES ] );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�N�^�[�f�[�^	�p���b�g�ǂݍ���
 *
 *	@param	cont			�R���g���[��
 *	@param	GraphicNo		�O���t�B�b�N�t�@�C���i���o�[
 *	@param	pCell			�Z���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadCell_PlttData( WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell )
{
	if(GraphicNo != WEATHER_GRAPHIC_NONE){
	
		// �p���b�g�f�[�^�ǂݍ���
		pCell->res_obj[ CLACT_U_PLTT_RES ] = loadRes(
				cont->Draw.resHeader, CLACT_U_PLTT_RES, 
				GraphicNo,
				cont->Draw.resMan[ CLACT_U_PLTT_RES ],
				cont->ArcHandle, ALLOC_BOTTOM );
		
		// Vram�]��
		CLACT_U_PlttManagerSetCleanArea( pCell->res_obj[ CLACT_U_PLTT_RES ] );
		// �p���b�g�̓ǂݍ���ł����f�[�^�̂ݔj��
		CLACT_U_ResManagerResOnlyDelete( pCell->res_obj[ CLACT_U_PLTT_RES ] );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�N�^�[�o�^�f�[�^�쐬
 *
 *	@param	cont		�R���g���[��
 *	@param	w_sys		�V�C�f�[�^�i�[��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initClactAddData( WEATHER_SYS_CONTROL* cont, WEATHER_SYS_DATA* w_sys )
{
	if( w_sys->GraphicNo != WEATHER_GRAPHIC_NONE){
		// �Z���A�N�^�[�o�^�f�[�^�쐬
		getHeader(&w_sys->pCell->head, cont, w_sys->pCell, 0, WEATHER_SYS_BG_2_DRAW_PRI);
		memset(&w_sys->pCell->add, 0, sizeof(CLACT_ADD));
		w_sys->pCell->add.ClActSet		= cont->Draw.clactSet;
		w_sys->pCell->add.ClActHeader	= &w_sys->pCell->head;
		w_sys->pCell->add.sca.x			= FX32_ONE;
		w_sys->pCell->add.sca.y			= FX32_ONE;
		w_sys->pCell->add.sca.z			= FX32_ONE;
		w_sys->pCell->add.DrawArea		= 1;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG	�p���b�g�ǂݍ���
 *
 *	@param	cont		�R���g���[��
 *	@param	BGNo		�ǂݍ���BG�f�[�^�i���o�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initBgPltt( WEATHER_SYS_CONTROL* cont, int BGNo )
{
	WATHER_BG_FILE_DATA	BG;		// BG�t�@�C���f�[�^�ǂݍ��ݗ̈�

	if(BGNo != WEATHER_GRAPHIC_NONE){
		// �p���b�g�ǂݍ���
		BG.pPlttBuff = ArchiveDataLoadAllocByHandle( cont->ArcHandle, cont->pWSBG[BGNo].pltt_arc, USE_HEAPID );
		// �A���p�b�N
		NNS_G2dGetUnpackedPaletteData( BG.pPlttBuff, &BG.pPltt );
		// BG�̓ǂݍ���			
		GF_BGL_PaletteSet(FLD_MBGFRM_EFFECT2,
				BG.pPltt->pRawData,
				32,
				32 * (WEATHER_PLTT_OFS));
		sys_FreeMemoryEz( BG.pPlttBuff );
		BG.pPlttBuff = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG		�L�����N�^�f�[�^�ǂݍ���
 *
 *	@param	cont		�R���g���[��
 *	@param	BGNo		BG�f�[�^�i���o�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initBgChar( WEATHER_SYS_CONTROL* cont, int BGNo )
{
	WATHER_BG_FILE_DATA	BG;		// BG�t�@�C���f�[�^�ǂݍ��ݗ̈�

	if(BGNo != WEATHER_GRAPHIC_NONE){
		// �t�@�C���ǂݍ���
		BG.pCharBuff = ArchiveDataLoadAllocByHandle( cont->ArcHandle, cont->pWSBG[BGNo].char_arc, USE_HEAPID );
		// �A���p�b�N
		NNS_G2dGetUnpackedCharacterData( BG.pCharBuff, &BG.pChar );

		GF_BGL_LoadCharacter( cont->fsys->bgl, FLD_MBGFRM_EFFECT2,
				BG.pChar->pRawData,
				BG.pChar->szByte,
				0 );
		sys_FreeMemoryEz( BG.pCharBuff );
		BG.pCharBuff = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG		�X�N���[���f�[�^�ǂݍ���
 *
 *	@param	cont		�R���g���[��
 *	@param	BGNo		BG�f�[�^�i���o�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initBgScr( WEATHER_SYS_CONTROL* cont, int BGNo )
{
	WATHER_BG_FILE_DATA	BG;		// BG�t�@�C���f�[�^�ǂݍ��ݗ̈�

	if(BGNo != WEATHER_GRAPHIC_NONE){
		// BGOFF
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		
		// �X�N���[���f�[�^
		BG.pScreenBuff = ArchiveDataLoadAllocByHandle( cont->ArcHandle, cont->pWSBG[BGNo].screen_arc, USE_HEAPID );
		GF_ASSERT(BG.pScreenBuff);
		// �A���p�b�N
		NNS_G2dGetUnpackedScreenData( BG.pScreenBuff, &BG.pScreen );
		GF_BGL_LoadScreen(cont->fsys->bgl, FLD_MBGFRM_EFFECT2,
				(void*)BG.pScreen->rawData,
				BG.pScreen->szByte,
				0 );

		GF_BGL_ScreenBufSet(cont->fsys->bgl, FLD_MBGFRM_EFFECT2, (void*)BG.pScreen->rawData,
				BG.pScreen->szByte );
		
		GF_BGL_ScrPalChange(
				cont->fsys->bgl, FLD_MBGFRM_EFFECT2,
				0, 0,
				32, 32,
				WEATHER_PLTT_OFS
				);
		GF_BGL_LoadScreenReq( cont->fsys->bgl, FLD_MBGFRM_EFFECT2 );

		sys_FreeMemoryEz( BG.pScreenBuff );
		BG.pScreenBuff = NULL;
	}
}


//-----------------------------------------------------------------------------
//	�v���C�x�[�g�֐�
//		���V�C�Ǘ��^�X�N�������p�֐��S	
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�u�W�F�̃��[�N�̈���m��
 *
 *@param	pData		�m�ۂ���I�u�W�F�f�[�^
 *@param	Byte		�m�ۂ���o�C�g�T�C�Y
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void allocObjWork(WAETHER_OBJ_DATA* pData, int byte)
{
	GF_ASSERT( pData->work == NULL );
	GF_ASSERT( byte > 0 );
	GF_ASSERT( byte <= WEATHER_OBJ_DATA_WORK_SIZE );
	
//	pData->work = sys_AllocMemory(USE_HEAPID, byte);
	pData->work = pData->work_buff;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�u�W�F�̃��[�N�̈��j��
 *
 *@param	pData		�j������I�u�W�F�f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void freeObjWork(WAETHER_OBJ_DATA* pData)
{
	pData->work = NULL;
	memset( pData->work_buff, 0, WEATHER_OBJ_DATA_WORK_SIZE );
/*	if(pData->work != NULL){
		sys_FreeMemory(USE_HEAPID, pData->work);
		pData->work = NULL;
	}//*/
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�u�W�F�^�X�N��o�^
 *
 *@param	pWork		�o�^����I�u�W�F�̊Ǘ��֐����[�N
 *@param	w_byte		���[�N�o�C�g�T�C�Y
 *
 *@return	WAETHER_OBJ_DATA*	����:�I�u�W�F�N�g�̃|�C���^	���s:NULL
 *
 *	���e
 *		�Ǘ��֐����[�N����I�u�W�F���쐬���ă��X�g�o�^
 *
 */
//-----------------------------------------------------------------------------
static WAETHER_OBJ_DATA* addObj(WEATHER_SYS_WORK* pWork, int w_byte)
{
	WAETHER_OBJ_DATA* p_obj;		// �I�u�W�F�f�[�^
	WEATHER_SYS_CONTROL* cont = (WEATHER_SYS_CONTROL*)pWork->pWSysCont;	// �R���g���[��
	
	// �I�u�W�F�N�g�f�[�^�쐬
	p_obj = getCleanObjData( pWork );
	if(p_obj == NULL){
		return NULL;
	}

	// �f�[�^�Z�b�g
	p_obj->pWSysCont				= cont;			// �e�̓V�C�Ǘ��f�[�^
	
	// ���X�g�ɓo�^
	p_obj->pNext				= &pWork->Dummy;
	p_obj->pPrev				= pWork->Dummy.pPrev;
	pWork->Dummy.pPrev->pNext	= p_obj;
	pWork->Dummy.pPrev			= p_obj;

	p_obj->clact_w = CLACT_Add(&pWork->pCell->add);
	if(p_obj->clact_w == NULL){
		destObj(p_obj);
		return NULL;
	}

	// ���[�N�쐬
	allocObjWork(p_obj, w_byte);
	if(p_obj->work == NULL){
		destObj(p_obj);
		return NULL;
	}
	
	return p_obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�N�^�[�w�b�_�쐬
 *	
 *@param	head	�w�b�_
 *@param	cont	�V�C�Ǘ��f�[�^
 *@param	pcell	�Z���f�[�^
 *@param	vram_trans	Vram�]����
 *@param	priority	�D�揇��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void getHeader(CLACT_HEADER_PTR head, WEATHER_SYS_CONTROL* cont, WATHER_GRAPHIC_FILE_DATA* pcell,int vram_trans, int priority )
{
	int id[ WEATHER_RES_NUM ];		// ���\�[�X����ID�i�[�o�b�t�@
	int i;							// ���[�v�p

	// ID���擾
	for(i=0;i<WEATHER_RES_NUM;i++){
		id[ i ] = CLACT_U_ResManagerGetResObjID( pcell->res_obj[ i ] );
	}

	// �w�b�_�쐬
	CLACT_U_MakeHeader( 
			head,
			id[ CLACT_U_CHAR_RES ], id[ CLACT_U_PLTT_RES ], 
			id[ CLACT_U_CELL_RES ], id[ CLACT_U_CELLANM_RES ],
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
			vram_trans, priority,
			cont->Draw.resMan[ CLACT_U_CHAR_RES ], cont->Draw.resMan[ CLACT_U_PLTT_RES ],
			cont->Draw.resMan[ CLACT_U_CELL_RES ], cont->Draw.resMan[ CLACT_U_CELLANM_RES ],
			NULL, NULL);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�^�I�u�W�F�^�X�N�j��
 *
 *@param	pData		�j������I�u�W�F�N�g�f�[�^
 *
 *@return	none
 *
 *	���e
 *		�I�u�W�F�N�g�f�[�^��j������
 *
 */
//-----------------------------------------------------------------------------
static void destObj(WAETHER_OBJ_DATA* pData)
{
//	WEATHER_SYS_CONTROL* cont = (WEATHER_SYS_CONTROL*)pData->pWSysCont;	// �R���g���[��

	// ���X�g����j��
	pData->pPrev->pNext	= pData->pNext;
	pData->pNext->pPrev	= pData->pPrev;

	// �Z���A�N�^�[����j��
	if(pData->clact_w){
		CLACT_Delete(pData->clact_w);
		pData->clact_w = NULL;
	}

	// ���[�N�j��
	freeObjWork(pData);	
		
	// �j��
	memset( pData, 0, sizeof(WAETHER_OBJ_DATA) );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�^�I�u�W�F�^�X�N�S�j��
 *
 *@param	pDummy		�j������I�u�W�F�N�g���X�g�̐擪�f�[�^
 *
 *@return	none
 *
 *	���e
 *		�I�u�W�F�N�g�f�[�^��S�Ĕj������
 *
 */
//-----------------------------------------------------------------------------
static void destObjAll(WAETHER_OBJ_DATA* pDummy)
{
	WAETHER_OBJ_DATA* p_work;		// �j����Ɨp
	WAETHER_OBJ_DATA* p_next;		// ���̃I�u�W�F�N�g
	
	// �S�j��
	p_work = pDummy->pNext;
	while(p_work != pDummy){
		p_next = p_work->pNext;
		destObj(p_work);		// �j��
		p_work = p_next;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�^���ꂽ�S�I�u�W�F�N�g�𓮂���
 *
 *@param	pDummy		�������I�u�W�F�N�g���X�g
 *@param	pFunc		�������֐�
 *
 *@return	none
 *
 *	���e
 *		�I�u�W�F�N�g�f�[�^�𓮂���
 *
 */
//-----------------------------------------------------------------------------
static void moveFuncObj(WAETHER_OBJ_DATA* pDummy, objFunc pFunc)
{
	WAETHER_OBJ_DATA* p_work;		// ��Ɨp
	WAETHER_OBJ_DATA* p_work_next;	// ��Ɨp

	// �S��������
	p_work = pDummy->pNext;
	p_work_next = p_work->pNext;
	while(p_work != pDummy){
		pFunc(p_work);		// ������
		
		p_work = p_work_next;
		p_work_next = p_work->pNext;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�u�W�F�N�g�̕`��
 *
 *@param	pData		�V�C�P�̃f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void drawObj(WEATHER_SYS_WORK* pData)
{
/*	CLACT_SET_DELETE
	CLACT_Draw(pData->clactSet);
//*/
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�u�W�F�N�g���W���擾
 *
 *@param	obj		�擾����I�u�W�F
 *
 *@return	���W
 *
 *
 */
//-----------------------------------------------------------------------------
static VecFx32 getObjMat( WAETHER_OBJ_DATA* obj )
{
	const VecFx32* mat = CLACT_GetMatrix(obj->clact_w);

	return *mat;
}

// �X�N���[�����W�擾
static void getScrollNum(fx32* x, fx32* y, WEATHER_SYS_WORK* pWork)
{
	
	VecFx32	now_mat;				// ���̍��W
	fx32 scl_x, scl_y;				// Scroll���W
	fx32 d_x, d_y;					// 2d�łP�̂R���̒l
	fx32 dist_x, dist_y;			// �ړ������l
	int	mark;						// ����
	fx32 aspect;					// �A�X�y�N�g��
	
	
	// ���̃J������2d��1�̂R���̒l�����߂�
	aspect = FX_Div(4*FX32_ONE, 3*FX32_ONE);
	GetPerspectiveScreenSize( 
			GFC_GetCameraPerspWay( pWork->pWSysCont->fsys->camera_ptr ),
			GFC_GetCameraDistance(pWork->pWSysCont->fsys->camera_ptr),
			aspect,
			&d_x, &d_y);
	d_x = FX_Div(d_x, 256*FX32_ONE);
	d_y = FX_Div(d_y, 192*FX32_ONE);
	


	// �������瓮���������ɂO�D�T�����i�����_�̌덷�Œl���ς��Ȃ����߁j
	now_mat = *(NNS_G3dGlbGetCameraTarget());
	
	dist_x = (now_mat.x - pWork->CameraTarget.x);
	dist_y = (now_mat.z - pWork->CameraTarget.z);

	// �v���X�Ōv�Z����
	mark = FX32_ONE;
	if(dist_x < 0){		// �[�̎��́{�̒l�ɂ���
		mark = -FX32_ONE;
		dist_x = FX_Mul( dist_x, -FX32_ONE );
	}
	scl_x = FX_Div(dist_x, d_x);	// �X�N���[�����W���v�Z
	if( mark < 0 ){		// ���̕����ɖ߂�
		scl_x = FX_Mul( scl_x, mark );	// ���̕����ɖ߂�
	}

	mark = FX32_ONE;
	if(dist_y < 0){		// �[�̎��́{�̒l�ɂ���
		mark = -FX32_ONE;
		dist_y = FX_Mul( dist_y, -FX32_ONE );
	}	
	scl_y = FX_Div(dist_y, d_y);	// �X�N���[�����W�����߂�
	if( mark < 0 ){
		scl_y = FX_Mul( scl_y, mark );	// ���̕����ɖ߂�
	}
		
	// ���̍��W���擾
	if((scl_x + scl_y) != 0){
		pWork->CameraTarget = now_mat;
	}

	*x = scl_x;
	*y = scl_y;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�^���ꂽ�S�I�u�W�F�N�g�̍��W��scroll�ɂ��킹��
 *
 *@param	pWork		Scroll������V�C�R���g���[���̖{��
 *@param	x, y		�X�N���[�����W(����Ȃ��Ƃ���NULL)
 *
 *@return	none
 *
 *	���e
 *		�I�u�W�F�N�g�̍��W�����̃^�[���ł̃J�����̃^�[�Q�b�g�̈ړ��n�ɍ��킹��
 *
 */
//-----------------------------------------------------------------------------
static void scrollObj(WEATHER_SYS_WORK* pWork,int* x, int* y)
{
	WAETHER_OBJ_DATA* p_work;		// ��Ɨp
	fx32 scl_x, scl_y;		// �X�N���[�����W	
	VecFx32 mat;			// ���W
	

	getScrollNum(&scl_x,&scl_y, pWork);
	
	
	// �S���I�u�W�F�N�g�ɔ��f
	p_work = pWork->Dummy.pNext;
	while(p_work != &pWork->Dummy){
		// ���̍��W�擾
		mat = getObjMat(p_work);
		
		mat.x -= scl_x;
		mat.y -= scl_y;

		// ���W�ݒ�
		setClactMatrix(p_work->clact_w, &mat);
		
		p_work = p_work->pNext;
	}

	if(x != NULL){
		*x = scl_x >> FX32_SHIFT;
		if( *x < 0 ){
			*x += 1;	// �}�C�i�X�̂Ƃ�-1���̌덷���o�邽��
		}
	}
	if(y != NULL){
		*y = scl_y >> FX32_SHIFT;
		if( *y < 0 ){
			*y += 1;	// �}�C�i�X�̂Ƃ�-1���̌덷���o�邽��
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F�N�g�t�F�[�h�p�����[�^�̏�����
 *
 *	@param	data					�I�u�W�F�t�F�[�h���[�N
 *	@param	pWork					�V�C�V�X�e�����[�N
 *	@param	objAddNum				�I�u�W�F�N�g�o�^��
 *	@param	objAddTmgMax			�o�^�^�C�~���O
 *	@param	OBJ_ADD_NUM_END			�I�u�W�F�N�g�o�^���@�I���l
 *	@param	OBJ_ADD_TMG_END			�I�u�W�F�N�g�P��̓o�^���@�I���l
 *	@param	OBJ_ADD_TMG_SUM         �o�^�^�C�~���O�J�E���^�@�I���l
 *	@param	OBJ_ADD_NUM_SUM_TMG     �o�^�^�C�~���O�J�E���^�ύX�l
 *	@param	OBJ_ADD_NUM_SUM         �I�u�W�F�N�g�P��̓o�^����ύX����^�C�~���O
 *	@param	add						�o�^�֐�
 */
//-----------------------------------------------------------------------------
static void weatherSysObjFadeInit( WEATHER_SYS_OBJ_FADE* data, WEATHER_SYS_WORK* pWork, s32 objAddNum, s32 objAddTmgMax, s32 OBJ_ADD_NUM_END, s32 OBJ_ADD_TMG_END, s32 OBJ_ADD_TMG_SUM, s32 OBJ_ADD_NUM_SUM_TMG, s32 OBJ_ADD_NUM_SUM, OBJADD_FUNC add )
{
	data->pWork				= pWork;
	data->objAddNum			= objAddNum;	
	data->objAddTmg			= 0;						
	data->objAddTmgMax		= objAddTmgMax;	
	data->objAddNumSum		= 0;						
	data->OBJ_ADD_NUM_END	= OBJ_ADD_NUM_END;
	data->OBJ_ADD_TMG_END	= OBJ_ADD_TMG_END;
	data->OBJ_ADD_TMG_SUM	= OBJ_ADD_TMG_SUM;
	data->OBJ_ADD_NUM_SUM_TMG = OBJ_ADD_NUM_SUM_TMG;
	data->OBJ_ADD_NUM_SUM	= OBJ_ADD_NUM_SUM;
	data->add				= add;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�A�E�g�̂��߂̐ݒ�
 *
 *	@param	data				���[�N
 *	@param	OBJ_ADD_NUM_END			�I�u�W�F�N�g�o�^���@�I���l
 *	@param	OBJ_ADD_TMG_END			�I�u�W�F�N�g�P��̓o�^���@�I���l
 *	@param	OBJ_ADD_TMG_SUM         �o�^�^�C�~���O�J�E���^�@�I���l
 *	@param	OBJ_ADD_NUM_SUM         �I�u�W�F�N�g�P��̓o�^����ύX����^�C�~���O
 */
//-----------------------------------------------------------------------------
static void weatherSysObjFadeOutSet( WEATHER_SYS_OBJ_FADE* data, s32 OBJ_ADD_NUM_END, s32 OBJ_ADD_TMG_END, s32 OBJ_ADD_TMG_SUM, s32 OBJ_ADD_NUM_SUM )
{
	data->OBJ_ADD_NUM_END	= OBJ_ADD_NUM_END;
	data->OBJ_ADD_TMG_END	= OBJ_ADD_TMG_END;
	data->OBJ_ADD_TMG_SUM	= OBJ_ADD_TMG_SUM;
	data->OBJ_ADD_NUM_SUM	= OBJ_ADD_NUM_SUM;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�u�W�F�N�g�t�F�[�h
 *
 *@param	data		�I�u�W�F�N�g�̃t�F�[�h�f�[�^
 *
 *@retval	0			�t�F�[�h���I��
 *@retval	1			�o�^�^�C�~���O�J�E���^�t�F�[�h�I��
 *@retval	2			�o�^���t�F�[�h�I��
 *@retval	3			���S�I��
 *
 * �e�J�E���^�̏����������O�ɂ��Ă����K�v������܂��B
 * �J�E���^�̓|�C���^�Q�ƂȂ̂ŁA���������Ȃ��悤�ɂ��Ă����K�v������܂��B
 * 
 * 
 */
//-----------------------------------------------------------------------------
static int weatherSysObjFade(WEATHER_SYS_OBJ_FADE* data)
{
	int fade_flag;
	int ret = 0;
	

	// �t�F�[�h�I���`�F�b�N
	// �^�C�~���O-------------------------------------------
	// �����l���O�Ȃ�^�C�~���O�t�F�[�h�I��
	if(data->OBJ_ADD_TMG_SUM == 0){
		ret |= 1;
	}else{
		// �t�F�[�h�C���A�A�E�g�`�F�b�N
		if(data->OBJ_ADD_TMG_SUM > 0){
			fade_flag = 0;		// �ύX�l���v���X�Ȃ̂Ńt�F�[�h�C��
		}else{
			fade_flag = 1;		// �ύX�l���}�C�i�X�Ȃ̂Ńt�F�[�h�A�E�g
		}
		// �o�^�^�C�~���O�I���_�ɂ��Ă��Ȃ����`�F�b�N
		if(((data->objAddTmgMax >= data->OBJ_ADD_TMG_END)&&(fade_flag == 0)) ||
			((data->objAddTmgMax <= data->OBJ_ADD_TMG_END)&&(fade_flag == 1))){
			ret |= 1;

			data->objAddTmgMax = data->OBJ_ADD_TMG_END;
		}
	}

	// �o�^��---------------------------------------------------
	// �����l���O�Ȃ�o�^���t�F�[�h�I��
	if(data->OBJ_ADD_NUM_SUM == 0){
		ret |= 2;
	}else{
		
		// �t�F�[�h�C���A�A�E�g�`�F�b�N
		if(data->OBJ_ADD_NUM_SUM > 0){
			fade_flag = 0;		// �ύX�l���v���X�Ȃ̂Ńt�F�[�h�C��
		}else{
			fade_flag = 1;		// �ύX�l���}�C�i�X�Ȃ̂Ńt�F�[�h�A�E�g
		}
		// �I�u�W�F�N�g�o�^�I���_�ɂ��Ă��Ȃ����`�F�b�N
		if(((data->objAddNum >= data->OBJ_ADD_NUM_END)&&(fade_flag == 0)) ||
			((data->objAddNum <= data->OBJ_ADD_NUM_END)&&(fade_flag == 1))){
		
			ret |= 2;
			data->objAddNum = data->OBJ_ADD_NUM_END;
		}
	}
	

	// �^�C�~���O�J�E���^���ŏ��ɂȂ�܂ŃJ�E���g���
	(data->objAddTmg)--;
	if(data->objAddTmg <= 0){

		// �o�^
		data->add(data->pWork, data->objAddNum);

		data->objAddTmg = data->objAddTmgMax;			// �o�^�^�C�~���O�Z�b�g
		
		// �^�C�~���O-------------------------------------------
		if((ret & 1) == 0){
			data->objAddTmgMax += data->OBJ_ADD_TMG_SUM;	// �J�^�C�~���O�v�Z
		}
		
	
		// �o�^��---------------------------------------------------
		if((ret & 2) == 0){
			(data->objAddNumSum)++;
			if(data->objAddNumSum >= data->OBJ_ADD_NUM_SUM_TMG){
				data->objAddNumSum = 0;
				data->objAddNum += data->OBJ_ADD_NUM_SUM;	// �o�^���A�b�h
			}
		}
	}

	return ret;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�t�H�O�t�F�[�h�C���@�����������@�p�b�N
 *
 *	@param	fogParam		�t�H�O�p�����[�^���[�N
 *	@param	fogData			�t�H�O�e�[�u�����[�N
 *	@param	Fog				�t�H�O�f�[�^
 *	@param	fog_slope		�t�H�O�X���[�v
 *	@param	fog_offs		�t�H�O�I�t�Z�b�g
 *	@param	color			�J���[
 *	@param	timing			�^�C�~���O
 *	@param	fog_use_flg		�t�H�O����t���O
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void weatherSysFogFadeInInitPack( WEATHER_SYS_CHG_FOG_DATA* fogParam, WEATHER_SYS_FOG_FADE* fogData, FOG_DATA_PTR Fog, int fog_slope, int fog_offs, GXRgb color, int timing, u32 fog_use_flg )
{
	fogData->Fog = Fog;
	
	if( fog_use_flg != WEATHER_FOG_NONE ){

		if( fog_use_flg == WEATEHR_FOG_NEW ){
			weatherSysFogParamSet( Fog, fog_slope, fog_offs, color );
			weatherSysFogTblInit( fogData );
			weatherSysFogFadeInit( fogData, timing, TRUE );
		}else if( fog_use_flg == WEATHER_FOG_WITH ){
			weatherSysFogParamFadeInit( fogParam, 
					Fog,
					fog_slope, 
					fog_offs,
					color, timing * FOG_DEPTH_COUNT_MAX );
					// �������@�t�H�O��timing�ɂP��f�v�X�l��ύX����
					// �̂ł���ɂ��킹�Ă��̃J�E���g�l�ɂ���
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H�O�t�F�[�h���C��
 *
 *	@param	fogParam	�t�H�O�p�����[�^�t�F�[�h�f�[�^
 *	@param	fogData		�t�H�O�e�[�u���t�F�[�h�f�[�^
 *
 *	@retval	1	�I��
 *	@retval	0	�r��
 */
//-----------------------------------------------------------------------------
static int weatherSysFogFadeInMainPack( WEATHER_SYS_CHG_FOG_DATA* fogParam, WEATHER_SYS_FOG_FADE* fogData, u32 fog_use_flg )
{
	BOOL result_bool;
	int result_int = 1;
	
	if( fog_use_flg != WEATHER_FOG_NONE ){

		if( fog_use_flg == WEATEHR_FOG_NEW ){
			result_int = weatherSysFogFade(fogData);	
		}else if( fog_use_flg == WEATHER_FOG_WITH ){
			result_bool = weatherSysFogParamFadeMain( fogParam );
			if( result_bool == FALSE ){
				result_int = 0;
			}
		}
	}
	return result_int;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H�O�̒l�ݒ�
 *
 *	@param	Fog			�t�H�O�f�[�^
 *	@param	fog_slope	�t�H�O�X���[�v
 *	@param	fog_offs	�t�H�O�I�t�Z�b�g
 *	@param	color		�J���[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void weatherSysFogParamSet( FOG_DATA_PTR Fog, int fog_slope, int fog_offs, GXRgb color )
{
	SetFogData(Fog, FOG_SYS_ALL, TRUE, GX_FOGBLEND_COLOR_ALPHA, fog_slope, fog_offs);		// �t�H�O�f�[�^
	SetFogColor(Fog, FOG_SYS_ALL, color, 31);	// �t�H�O�J���[
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H�O�@�p�����[�^�l�t�F�[�h
 *
 *	@param	data		�i�[�惏�[�N
 *	@param	fog			�t�H�O�l�o�b�t�@
 *	@param	fogslope	�ύX��̃t�H�O�̌W��
 *	@param	offs		�I�t�Z�b�g�l
 *	@param	color		�J���[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void weatherSysFogParamFadeInit( WEATHER_SYS_CHG_FOG_DATA* data, FOG_DATA_PTR fog, int fogslope, int offs, GXRgb color, int count_max )
{
	int fog_slope;
	int fog_offs;
	GXRgb fog_color;

	// ���݂̃p�����[�^�擾
	fog_slope = GetFogSlope( fog );
	fog_offs = GetFogOffset( fog );
	fog_color = GetFogColor( fog );
	
	data->Fog = fog;

	WeatherMoveReq( &data->fog_depth, fog_offs, offs, count_max );
	WeatherMoveReq( &data->r, WH_COLOR_R(fog_color), WH_COLOR_R(color), count_max );
	WeatherMoveReq( &data->g, WH_COLOR_G(fog_color), WH_COLOR_G(color), count_max );
	WeatherMoveReq( &data->b, WH_COLOR_B(fog_color), WH_COLOR_B(color), count_max );
	WeatherMoveReq( &data->slope, fog_slope, fogslope, count_max );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�������C��
 *
 *	@param	data	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL weatherSysFogParamFadeMain( WEATHER_SYS_CHG_FOG_DATA* data )
{
	BOOL check;
	
	// �v�Z
	check = WeatherMoveMain( &data->fog_depth );
	WeatherMoveMain( &data->r );
	WeatherMoveMain( &data->g );
	WeatherMoveMain( &data->b );
	WeatherMoveMain( &data->slope );

	// �l�ݒ�
	weatherSysFogParamSet( data->Fog,
		data->slope.x, data->fog_depth.x, GX_RGB(data->r.x,data->g.x,data->b.x)	);
	
	return check;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�t�H�O�e�[�u��������
 *
 *	@param	data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void weatherSysFogTblInit( WEATHER_SYS_FOG_FADE* data )
{
	int i;
	for(i=0;i<32;i++){						// �t�H�O�e�[�u��
		data->fog_tbl[i] = 0;
	}
	SetFogTbl(data->Fog, data->fog_tbl);				// �t�H�O�e�[�u��
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H�O�t�F�[�h�e�[�u���p�����[�^�ݒ�
 *
 *	@param	data			�f�[�^�i�[��
 *	@param	timing			�ύX�^�C�~���O
 *	@param	fade_inout		�t�F�[�h�C���A�E�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void weatherSysFogFadeInit( WEATHER_SYS_FOG_FADE* data, int timing, BOOL fade_inout )
{
	data->fogDepth		= FOG_DEPTH_COUNT_MAX;
	data->fogCount		= 0;
	data->FOG_CHG_TMG	= timing;

	if( fade_inout == TRUE ){
		data->FOG_TBL_SUM	= FOG_TBL_SUB_FADEIN;
	}else{
		data->FOG_TBL_SUM	= FOG_TBL_SUB_FADEOUT;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�t�H�O�t�F�[�h
 *
 *@param	data		�I�u�W�F�N�g�̃t�F�[�h�f�[�^
 *
 *@retval	0			�t�F�[�h���I��
 *@retval	1			�t�F�[�h�I��
 *
 * �e�J�E���^�̏����������O�ɂ��Ă����K�v������܂��B
 * �J�E���^�̓|�C���^�Q�ƂȂ̂ŁA���������Ȃ��悤�ɂ��Ă����K�v������܂��B
 * 
 * 
 */
//-----------------------------------------------------------------------------
static int weatherSysFogFade(WEATHER_SYS_FOG_FADE* data)
{
	int ret;		// �߂�l
	
	ret = weatherSysFogFadeNoReflect( data );

	// fogCount��0���e�[�u���f�[�^��ύX�����^�C�~���O
	// �Ȃ̂Ŕ��f
	if( data->fogCount == 0 ){
		SetFogTbl(data->Fog, data->fog_tbl);	// �t�H�O�e�[�u���Z�b�g
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�t�F�[�h�C����ɍ쐬����Ă���t�H�O�f�[�^���쐬����
 *
 *	@param	data		�t�H�O�t�F�[�h�f�[�^
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void weatherSysFogSet(WEATHER_SYS_FOG_FADE* data)
{
	int i;
	int result;
	
	data->fogDepth		= 1;
	data->fogCount		= 0;
	data->FOG_CHG_TMG	= 0;
	data->FOG_TBL_SUM	= 1;

	// �e�[�u���v�Z
	calcWeatherFogTbl( data );
/*	do{
		result = weatherSysFogFadeNoReflect( data );	// �t�H�O�e�[�u���쐬
	}while( result != TRUE );//*/
	SetFogTbl(data->Fog, data->fog_tbl);	// �t�H�O�e�[�u���Z�b�g
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�t�H�O�t�F�[�h		�t�H�O�f�[�^�̔��f���s��Ȃ��o�[�W����
 *
 *@param	data		�I�u�W�F�N�g�̃t�F�[�h�f�[�^
 *
 *@retval	0			�t�F�[�h���I��
 *@retval	1			�t�F�[�h�I��
 *
 * �e�J�E���^�̏����������O�ɂ��Ă����K�v������܂��B
 * �J�E���^�̓|�C���^�Q�ƂȂ̂ŁA���������Ȃ��悤�ɂ��Ă����K�v������܂��B
 * 
 * 
 */
//-----------------------------------------------------------------------------
static int weatherSysFogFadeNoReflect(WEATHER_SYS_FOG_FADE* data)
{
	int ret = 0;		// �߂�l
	
	if(data->FOG_TBL_SUM == 0){
		ret = 1;
	}else{
	
		// �I�����Ă��邩�`�F�b�N
		if(data->fogDepth <= 0){
			ret = 1;
		}else{
			
			data->fogCount++;
			if(data->fogCount >= data->FOG_CHG_TMG){
				data->fogCount = 0;

				// �e�[�u���v�Z
				calcWeatherFogTbl( data );
				
				data->fogDepth--;
				if(data->fogDepth <= 0){		// �I���`�F�b�N
					ret = 1;
				}
//				SetFogTbl(data->Fog, data->fog_tbl);	// �t�H�O�e�[�u���Z�b�g
			}
		}
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�t�H�O�e�[�u���쐬�v�Z
 *
 *	@param	data	�t�H�O�t�F�[�h�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void calcWeatherFogTbl( WEATHER_SYS_FOG_FADE* data )
{
	int i;
	int fog_num;		// �t�H�O�e�[�u���v�Z�p
	int fog_calc;

	if( data->FOG_TBL_SUM < 0 ){
		fog_calc = FOG_DEPTH_COUNT_MAX - data->fogDepth;
	}else{
		fog_calc = data->fogDepth;
	}

	// �t�H�O�𓮂���		(y=(x*x)/(4*x))
	fog_num = fog_calc/4;
	for(i=31;i>fog_num;i--){
		data->fog_tbl[i] = ((i-fog_num)*4);

		// 127�ȏ�ɂ��Ȃ�
		if( data->fog_tbl[i] > 127 ){
			data->fog_tbl[i] = 127;
		}
	}
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG���t�F�[�h�v�Z�֐�
 *
 *	@param	now_alpha		���݂̃��l
 *	@param	end_alpha		�t�F�[�h�I�����l
 *	@param	add_alpha		�������l
 *	@param	timing_count	�^�C�~���O�J�E���^
 *	@param	add_timing		�����^�C�~���O
 *
 *	@retval	TRUE		����
 *	@retval	FALSE		�t�F�[�h�I��
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL weatherBGFade( s32* now_alpha, const int end_alpha, const int add_alpha, s32* timing_count, const int add_timing )
{
	BOOL ret = TRUE;
	
	// BG
	(*timing_count)++;
	if((*timing_count) > add_timing){
		(*timing_count) = 0;

		if( add_alpha > 0 ){
			if(((*now_alpha) + add_alpha) <= end_alpha){
				(*now_alpha) += add_alpha;
			}else{
				(*now_alpha) = end_alpha;
				ret = FALSE;
			}
		}else{
			if(((*now_alpha) + add_alpha) >= end_alpha){
				(*now_alpha) += add_alpha;
			}else{
				(*now_alpha) = end_alpha;
				ret = FALSE;
			}
		}
	}

	return ret;
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�V�C�̃I�u�W�F�N�g�𕪕z������
 *
 *	@param	pWork			���[�N
 *	@param	add_func		�I�u�W�F�N�g�o�^�֐��|�C���^
 *	@param	num				�o�^��
 *	@param	dust_div_num	���I�u�W�F�N�g���Ƃɓ��쐔��ύX���邩
 *	@param	dust_div_move	�e�I�u�W�F�N�g�̓��쐔���ǂ̂��炢������
 *	@param	move_func		����֐�
 *
 *	@return	none
 *
 * num���̃I�u�W�F�N�g��o�^���A0�Ԗڂ̃I�u�W�F�N�g����dust_div_move�񐔕�
 * �����I�u�W�F�N�g�𓮍삳����
 * 0�Ԗڂ̃I�u�W�F�N�g�@0
 * 1�Ԗڂ̃I�u�W�F�N�g	dust_div_move
 * 2�Ԗڂ̃I�u�W�F�N�g	dust_div_move * 2
 * ....
 *
 */
//-----------------------------------------------------------------------------
static void weatherDustObj( WEATHER_SYS_WORK* pWork, OBJADD_FUNC add_func, int num, int dust_div_num, int dust_div_move, objFunc move_func )

{
	int i, j;
	int move_num;
	WAETHER_OBJ_DATA* obj;
	WAETHER_OBJ_DATA* obj_next;
	
	// �I�u�W�F�N�g�o�^
	add_func( pWork, num );


	// �I�u�W�F�N�g��i�߂�
	move_num = 0;
	obj = pWork->Dummy.pNext;
	obj_next = obj->pNext;
	for( i=0; i<num; i++ ){	
		
		// �o�^���s���Ă���Ƃ���num���̃I�u�W�F�N�g���o�^����Ă��Ȃ�
		if( obj == &pWork->Dummy ){
			break;
		}
		
		for( j=0; j<move_num; j++ ){
			move_func( obj );

			// �j�����ꂽ��I���
			if( obj->work == NULL ){
				break;
			}
		}

		// ����
		obj = obj_next;
		obj_next = obj->pNext;	// move_func���ŃI�u�W�F�N�g���j������邱�Ƃ����邽�߁A���̃I�u�W�F�N�g�|�C���^��ۑ����Ă���

		// ���쐔�ύX�v�Z
		if( i >= dust_div_num ){
			if( (i % dust_div_num) == 0 ){
				move_num += dust_div_move;
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�J���̃I�u�W�F�N�g�f�[�^�z��v�f���擾
 *
 *	@param	pWork	�V�C�V�X�e�����[�N
 *
 *	@return	WAETHER_OBJ_DATA	�I�u�W�F�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static WAETHER_OBJ_DATA* getCleanObjData( WEATHER_SYS_WORK* pWork )
{
	int i;

	for( i=0; i<WEATEHR_OBJDATA_MAX; i++ ){

		if( pWork->ObjArray[ i ].pWSysCont == NULL ){	//(NULL�`�F�b�N�͂ǂ̃����o�ł�OK)
			return &pWork->ObjArray[ i ];
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
//	�v���C�x�[�g�֐�
//		���V�C�Ǘ��^�X�N�S	
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�_�~�[�V�C
 *	@param	tcb
 *	@param	work
 *	@return
 */
//-----------------------------------------------------------------------------
static void contWeatherDummy(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;

	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;

	case WEATHER_SEQ_NO_FADE:	// �t�F�[�h�C���Ȃ�������
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
		
	case WEATHER_SEQ_MAIN:		// ���C��
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g
		sys_work->Sequence = WEATHER_SEQ_DEST;
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�J�Ǘ��^�X�N
 *
 *@param	tcb		�����̃^�X�N
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherRain(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ���[�v�p
	WEATHER_SYSW_NORMAL*	sys_w;	// �V�X�e�����[�N
	int		result;		// �֐�����
	int	fog_result;	// �t�H�O����

	// ���[�N�|�C���^�Z�b�g
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;
	
	
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		
		// ��Ɨ̈�̏�����
		// �I�u�W�F�N�g�t�F�[�h�p
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_RAIN_ADD_START,
			WEATHER_RAIN_TIMING_MAX,
			WEATHER_RAIN_ADD_MAIN,
			WEATHER_RAIN_TIMING_MIN,
			-WEATHER_RAIN_TIMING_ADD,
			WEATHER_RAIN_ADD_TIMING,
			WEATHER_RAIN_ADD,
			addWeatherRain );

		// �t�H�O�̐ݒ�
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_RAIN_FOG_OFS, 
				GX_RGB(26,26,26),
				WEATHER_RAIN_FOG_TIMING,
				sys_work->fog_use );

		sys_w->work[0] = WEATHER_RAIN_FOG_START;	// �������t�H�O�p

		// ��
		WeatherLoopSndPlay( sys_work, SEQ_SE_DP_T_AME );	
		
		// �A���t�@�u�����h
//		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG0, 4,16);
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		
		result = weatherSysObjFade(&sys_w->objFade);	// ���s
	
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
			
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// �^�C�~���O���ŏ��ɂȂ����烁�C����
			if((fog_result == 1) && (result == 3)){		// �t�F�[�h���U���g�������Ȃ�΃��C����
				// �V�[�P���X�ύX
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
		}
		break;

	case WEATHER_SEQ_NO_FADE:	// �t�F�[�h�C���Ȃ�������
		// ��Ɨ̈�̏�����
		// �I�u�W�F�N�g�t�F�[�h�p
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_RAIN_ADD_MAIN,
			WEATHER_RAIN_TIMING_MIN,
			WEATHER_RAIN_ADD_MAIN,
			WEATHER_RAIN_TIMING_MIN,
			-WEATHER_RAIN_TIMING_ADD,
			WEATHER_RAIN_ADD_TIMING,
			WEATHER_RAIN_ADD,
			addWeatherRain );

		// �t�H�O�f�[�^�ݒ�
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// �f�[�^��ݒ�
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// �t�H�O�ۑ�����
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_RAIN_FOG_OFS, GX_RGB(26,26,26) );
			// �e�[�u���f�[�^���쐬���Ĕ��f
			weatherSysFogSet( &sys_w->fogFade );
		}
		
		// �A���t�@�u�����h
//		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG0, 4,16);

		// �J�I�u�W�F�N�g���U��΂�
		weatherDustObj( sys_work, addWeatherRain, WEATHER_RAIN_NOFADE_OBJ_START_NUM, WEATHER_RAIN_NOFADE_OBJ_START_DUST_NUM, WEATHER_RAIN_NOFADE_OBJ_START_DUST_MOVE, objWeatherRain );

		// ��
		WeatherLoopSndPlay( sys_work, SEQ_SE_DP_T_AME );	
		
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
		
	case WEATHER_SEQ_MAIN:		// ���C��
		
		// �J�E���^��0�����ɂȂ�����J�o�^
		if(sys_w->objFade.objAddTmg-- <= 0){

			// �J�o�^
			addWeatherRain(sys_work, sys_w->objFade.objAddNum);
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// �o�^�^�C�~���O�Z�b�g	
		}

		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			// �t�F�[�h�A�E�g�ݒ�
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_RAIN_TIMING_MAX,
					WEATHER_RAIN_TIMING_ADD,
					-WEATHER_RAIN_ADD );
			
			// �t�H�O
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_RAIN_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_RAIN_FOG_START_END;	// �������t�H�O�p

			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��

			// ��
			WeatherLoopSndStop( sys_work );
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g

		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s
	
		// �t�H�O����
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
		
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
		
			if((fog_result == 1) && (result == 3)){
				// �o�^�����O�ɂȂ�����I�����邩�`�F�b�N
				// �����̊Ǘ����邠�߂��S�Ĕj�����ꂽ��I��
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					
					// �V�[�P���X�ύX
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;


	default:
		break;
	}

	// �������A�j���ȊO�̂Ƃ��̓I�u�W�F�N�g�𓮍삳����
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherRain);
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�J�I�u�W�F�N�g�o�^�֐�
 *
 *@param	pWork		�o�^����I�u�W�F�̊Ǘ��֐����[�N
 *@param	num			�o�^���鐔
 *
 *@return	none
 *
 *	���e
 *		num���I�u�W�F�N�g��o�^
 *		�J�p�Ƀ��[�N�̈��������
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherRain(WEATHER_SYS_WORK* pWork, int num)
{
	int i;		// ���[�v�p
	WAETHER_OBJ_DATA* add_obj;		// �o�^�I�u�W�F
	int	err;	// �␳�l
	s32* obj_w;	// �I�u�W�F�N�g���[�N
	int frame;	// �`��t���[��
	VecFx32	mat;	// �ݒ���W
	
	// num���I�u�W�F�N�g��o�^
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*8);		// �o�^
		if(add_obj == NULL){			// ���s������I��
			break;
		}
		obj_w = (s32*)add_obj->work;		// �I�u�W�F���[�N�쐬
		
		// �̈��������
		obj_w[0] = 0;			// �J�E���^
		frame = gf_mtRand()%3;	// �J�̎��
		CLACT_AnmFrameSet(add_obj->clact_w, frame);

		err = (gf_mtRand() % WEATHER_RAIN_SPEED_ERR);
		obj_w[2] = WEATHER_RAIN_SPEED_Y * (frame+1) + err;
		if(frame == 2){		// ��ԑO�̉J�̓X�s�[�h���P�i�K�グ��
			obj_w[2] += WEATHER_RAIN_SPEED_Y;
		}
		
		err /= WEATHER_RAIN_SPEED_X;
		obj_w[4] = WEATHER_RAIN_SPEED_X * (frame+1) + err;
		if(frame == 2){		// ��ԑO�̉J�̓X�s�[�h���P�i�K�グ��
			obj_w[4] += WEATHER_RAIN_SPEED_X;
		}
		obj_w[3] = 0;			// �j���A�j���t���O
		
		// �j���^�C�~���O	�S�����ʂ͈̔͂̒l
		obj_w[1] = WEATHER_RAIN_END_MIN  + (gf_mtRand() % WEATHER_RAIN_END_MAX);
		
		// ���W��ݒ�
		mat.x = ( WEATHER_RAIN_START_X_BASE + (frame * WEATHER_RAIN_MUL_X) + (gf_mtRand() % WEATHER_RAIN_START_X_MAX) ) << FX32_SHIFT;
		mat.y = WEATHER_RAIN_START_Y << FX32_SHIFT;
		mat.z = 0;	
		setClactMatrix(add_obj->clact_w, &mat);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�J�I�u�W�F�N�g����֐�
 *
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherRain(WAETHER_OBJ_DATA* work)
{
	int i;
	WAETHER_OBJ_DATA* p_obj = work;
	s32*	obj_w = (s32*)p_obj->work;
	VecFx32 mat;	// ���W

	mat = getObjMat(p_obj);
	
	// ����t���O���`�F�b�N
	switch(obj_w[3]){
	case 0:		// ����
		// �������������ߊԂ�␳����@���@�Ƃ��ĂP�t���[���ɂQ�񓮂����A�P�D�T�̕`����s��
		for(i=0;i<2;i++){
			// ������
			mat.x += obj_w[4] << FX32_SHIFT;
			mat.y += obj_w[2] << FX32_SHIFT;
		
			// �j�����邩�`�F�b�N
			if(obj_w[0]++ > obj_w[1]){
				// �A�j���[�V���������邩�`�F�b�N
				if((gf_mtRand() % 10) < 7){		// 7/10�͔j��
					// �j��
					obj_w[3] = 2;
				}else{
				
					// �j���A�j��
					obj_w[3] = 1;		
					obj_w[0] = 4;			// �j���A�j���J�E���^
					CLACT_AnmFrameSet(p_obj->clact_w, 3);
				}
			}
		}
		// ���W�ݒ�
		setClactMatrix(p_obj->clact_w, &mat);

		break;
	case 1:		// �j���A�j��
		if(obj_w[0]-- <= 0){
			obj_w[3] = 2;		// �j��
		}
		break;

	case 2:		// �j��
		destObj(p_obj);
		break;
	}		
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	��Ǘ��^�X�N
 *
 *@param	tcb		�����̃^�X�N
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherSnow(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ���[�v�p
	int		tmp_y;		// y���W�ۑ��p
	WEATHER_SYSW_NORMAL*	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;
	int		result;		// �֐�����
	int		fog_result;	// �t�H�O����
	

	
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			1,
			WEATHER_SNOW_TIMING_MAX,
			WEATHER_SNOW_MAIN,
			WEATHER_SNOW_TIMING_MIN,
			-WEATHER_SNOW_TIMING_ADD,
			WEATHER_SNOW_ADD_TIMING,
			WEATHER_SNOW_ADD,
			addWeatherSnow );
		
		sys_w->work[1] = 0;							// �Ⴊ�P�񉺂܂ōs�������̃t���O
		
		// �t�H�O�̐ݒ�
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_SNOW_FOG_OFS, 
				GX_RGB(26,26,26),
				WEATHER_SNOW_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_SNOW_FOG_START;	// �������t�H�O�p
	
//		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG0, 8, 16);
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s

		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
			
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// �^�C�~���O���ŏ��ɂȂ����烁�C����
			if((fog_result == 1) && (result == 3)){		// �t�F�[�h���U���g�������Ȃ�΃��C����
				// �V�[�P���X�ύX
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
		}
		break;
	case WEATHER_SEQ_NO_FADE:
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SNOW_MAIN,
			WEATHER_SNOW_TIMING_MIN,
			WEATHER_SNOW_MAIN,
			WEATHER_SNOW_TIMING_MIN,
			-WEATHER_SNOW_TIMING_ADD,
			WEATHER_SNOW_ADD_TIMING,
			WEATHER_SNOW_ADD,
			addWeatherSnow );
		
		sys_w->work[1] = 0;							// �Ⴊ�P�񉺂܂ōs�������̃t���O
		sys_w->work[2] = 0;							// �����j���t���O
		
		// �t�H�O�̐ݒ�
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// �f�[�^��ݒ�
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// �t�H�O�ۑ�����
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_SNOW_FOG_OFS, GX_RGB(26,26,26) );

			// �e�[�u���f�[�^���쐬���Ĕ��f
			weatherSysFogSet( &sys_w->fogFade );
		}

//		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG0, 8, 16);
		// �I�u�W�F�N�g���U��΂�
		weatherDustObj( sys_work, addWeatherSnow, WEATHER_SNOW_NOFADE_OBJ_START_NUM, WEATHER_SNOW_NOFADE_OBJ_START_DUST_NUM, WEATHER_SNOW_NOFADE_OBJ_START_DUST_MOVE, objWeatherSnow );
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// ���C��
		
		// �J�E���^��0�����ɂȂ�����J�o�^
		if(sys_w->objFade.objAddTmg-- <= 0){

			// ��o�^
			addWeatherSnow(sys_work, sys_w->objFade.objAddNum);
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// �o�^�^�C�~���O�Z�b�g	
		}
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_SNOW_TIMING_MAX,
					WEATHER_SNOW_TIMING_ADD,
					-1 );
			// fog
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_SNOW_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_SNOW_FOG_START_END;	// �������t�H�O�p
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g

		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s
		
		// �t�H�O����
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N���O�ɂȂ�����t�H�O�𓮂���
		}else{
		
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
		
			if((fog_result == 1) && (result == 3)){

				// �I�u�W�F�j���t���OON
				sys_w->work[2] = 1;
				
				// �o�^�����O�ɂȂ�����I�����邩�`�F�b�N
				// �����̊Ǘ����邠�߂��S�Ĕj�����ꂽ��I��
				if(sys_work->Dummy.pNext == &sys_work->Dummy){//*/
					
					// �V�[�P���X�ύX
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// �������A�j���ȊO�̂Ƃ��͓���֐��𓮂���
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherSnow);
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	��I�u�W�F�N�g�o�^�֐�
 *
 *@param	pWork		�o�^����I�u�W�F�̊Ǘ��֐����[�N
 *@param	num			�o�^���鐔
 *
 *@return	none
 *
 *	���e
 *		num���I�u�W�F�N�g��o�^
 *		��p�Ƀ��[�N�̈��������
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherSnow(WEATHER_SYS_WORK* pWork, int num)
{
	int i;		// ���[�v�p
	int rand;	// ����
	WAETHER_OBJ_DATA* add_obj;		// �o�^�I�u�W�F
	WEATHER_SYSW_NORMAL*	sys_w;	// �V�X�e�����[�N
	s32*	obj_w;		// �I�u�W�F�N�g���[�N
	int	frame;		// �t���[��
	VecFx32	mat;	// ���W

	sys_w = (WEATHER_SYSW_NORMAL*)pWork->work;
	
	if(sys_w->work[1] == 1){
		num *= 2;
	}
	
	// num���I�u�W�F�N�g��o�^
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*10);		// �o�^
		if(add_obj == NULL){			// ���s������I��
			break;
		}
		obj_w = (s32*)add_obj->work;
		
		frame = gf_mtRand() % WEATHER_SNOW_OBJ_NUM;
		CLACT_AnmFrameSet(add_obj->clact_w, frame);
		
		obj_w[4] = 10;	// ���̓��������ύX�J�E���^	
		obj_w[5] = 0;
		obj_w[6] = 0;	// �P���J�E���^
		obj_w[8] = 0;							// �V�[�P���X
		
		rand = gf_mtRand();

		obj_w[9] = WEATHER_SNOW_OBJ_AUTODEST_TIMING_MIN + (rand % WEATHER_SNOW_OBJ_AUTODEST_TIMING_MAX);		// ���Ŷ���
	
		// �X�s�[�h
		if((rand % 2) == 0){
			obj_w[1] = 1;
		}else{
			obj_w[1] = -1;
		}
		obj_w[2] = WEATHER_SNOW_ADD_TMG_X_BASE + (gf_mtRand() % WEATHER_SNOW_ADD_TMG_X_RAN);
		obj_w[3] = WEATHER_SNOW_ADD_TMG_Y_BASE + (gf_mtRand() % WEATHER_SNOW_ADD_TMG_Y_RAN);

		obj_w[0] = (s32)&sys_w->work[1];		// ���܂ōs������t���O�𗧂Ă�|�C���^��ۑ�
		obj_w[7] = (s32)&sys_w->work[2];		// �j���t���O�|�C���^ON
		
		// ���W��ݒ�
		mat.x = ( WEATHER_SNOW_START_X_BASE + (gf_mtRand() % WEATHER_SNOW_START_X_MAX) ) << FX32_SHIFT;
		
		if((sys_w->work[1] == 1) &&
			(i >= (num /2)) ){	// �����o��
			mat.y = ( -40 - (gf_mtRand() % 20)) << FX32_SHIFT;
		}else{
			mat.y = ( -8 - (gf_mtRand() % 20) ) <<FX32_SHIFT;
		}
		setClactMatrix(add_obj->clact_w, &mat);
	}
}

static void objWeatherSnowObjNormal( WAETHER_OBJ_DATA* p_obj, s32* obj_w )
{
	VecFx32 mat;	// ���W
	s32*	p_flg;	// �Ⴊ��ʊO�֍s�������̃t���O

	mat = getObjMat(p_obj);

	// ������
	// X���W�ړ�
	if(((obj_w[5] & 0xffff) >= obj_w[2])){
		mat.x	+= obj_w[1] << FX32_SHIFT;
		obj_w[4]++;
		obj_w[5] &= 0xffff0000;
		// �X�s�[�h�`�F���W���[
		if(obj_w[4] < 10){
			obj_w[2]--;
		}else{
			obj_w[2]++;
		}
		if(obj_w[4] >= 20){	// ����ō��E�ɂ����
			obj_w[4] = 0;
			obj_w[1]*=-1;
		}//*/
	}
	// Y���W�ړ�
	if(((obj_w[5] >> 16) >= obj_w[3])){
		mat.y += FX32_ONE;
		obj_w[5] &= 0x0000ffff;
	} 

	// ���W�ݒ�
	setClactMatrix( p_obj->clact_w, &mat );

	mat.x >>= FX32_SHIFT;
	mat.y >>= FX32_SHIFT;
	
	// �J�E���g�ݒ�
	obj_w[6] = (obj_w[6] + 1) % 100;
	obj_w[5]++;
	obj_w[5]+=0x10000;

	// �j���]�[���ɂ�����j��  
	if(((mat.y < -284) && (mat.y > -296)) ||
		((mat.y > 212) && (mat.y < 232))){
		p_flg = (s32*)(obj_w[0]);
		*p_flg = 1;
		destObj(p_obj);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�ᓮ��֐�
 *
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherSnow(WAETHER_OBJ_DATA* work)
{
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	s32*	obj_w = (s32*)p_obj->work;
	s32* p_flg = (s32*)obj_w[7];	// ���g�̓|�C���^

	switch( obj_w[8] ){
	case 0:
		// �����@�j���t���O�������Ă����玩���j��������
		if( *p_flg == 1 ){
			obj_w[8] ++;
		}
		break;

	case 1:	// ������0�ɂȂ�����j��
		obj_w[9] --;
		if( obj_w[9] < 0 ){
			destObj(p_obj);
			return ;
		}
		break;
	}
	
	// �ʏ퓮��
	objWeatherSnowObjNormal( p_obj, obj_w );
}


//-------------------------------------
//	����
//=====================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	����Ǘ��^�X�N
 *
 *@param	tcb		�����̃^�X�N
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherSnowStorm(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ���[�v�p
	WEATHER_SYSW_NORMAL*	sys_w;		// �V�X�e�����[�N�̈�
	int		result;		// �֐�����
	int		fog_result;	// �t�H�O����	
	
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;
	

	
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SSNOW_ADD_START,
			WEATHER_SSNOW_TIMING_MAX,
			WEATHER_SSNOW_ADD_MAIN,
			WEATHER_SSNOW_TIMING_MIN,
			-WEATHER_SSNOW_TIMING_ADD,
			WEATHER_SSNOW_ADD_TIMING,
			WEATHER_SSNOW_ADD,
			addWeatherSnowStorm );

		// �t�H�O�̐ݒ�		
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_SSNOW_FOG_OFS, 
				GX_RGB(24,24,24),
				WEATHER_SSNOW_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_SSNOW_FOG_START;	// �������t�H�O�p
	
		
		sys_w->work[1] = 0;					// �I�u�W�F���J�E���^
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s	
		
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N���O�ɂȂ�����t�H�O�𓮂���
		}else{
			
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// �^�C�~���O���ŏ��ɂȂ����烁�C����
			if((fog_result == 1) && (result == 3)){		// �t�F�[�h���U���g�������Ȃ�΃��C����
				// �V�[�P���X�ύX
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
		}	
		break;

	case WEATHER_SEQ_NO_FADE:	// �t�F�[�h�C���Ȃ�������
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SSNOW_ADD_MAIN,  
			WEATHER_SSNOW_TIMING_MIN,
			WEATHER_SSNOW_ADD_MAIN,
			WEATHER_SSNOW_TIMING_MIN,
			-WEATHER_SSNOW_TIMING_ADD,
			WEATHER_SSNOW_ADD_TIMING,
			WEATHER_SSNOW_ADD,
			addWeatherSnowStorm );

		// �t�H�O�̐ݒ�		
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// �f�[�^��ݒ�
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// �t�H�O�ۑ�����
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_SSNOW_FOG_OFS, GX_RGB(24,24,24) );
			// �e�[�u���f�[�^���쐬���Ĕ��f
			weatherSysFogSet( &sys_w->fogFade );
		}

		sys_w->work[1] = 0;					// �I�u�W�F���J�E���^

		// �I�u�W�F�N�g���U��΂�
		weatherDustObj( sys_work, addWeatherSnowStorm, WEATHER_SSNOW_NOFADE_OBJ_START_NUM, WEATHER_SSNOW_NOFADE_OBJ_START_DUST_NUM, WEATHER_SSNOW_NOFADE_OBJ_START_DUST_MOVE, objWeatherSnowStorm );
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;

	case WEATHER_SEQ_MAIN:		// ���C��
		
		// �J�E���^��0�����ɂȂ�����J�o�^
		if(sys_w->objFade.objAddTmg-- <= 0){

			// ����o�^
			addWeatherSnowStorm(sys_work, sys_w->objFade.objAddNum);
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// �o�^�^�C�~���O�Z�b�g	
		}
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_SSNOW_TIMING_MAX,
					WEATHER_SSNOW_TIMING_ADD,
					WEATHER_SSNOW_ADD_END );
			// fog
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_SSNOW_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_SSNOW_FOG_START_END;	// �������t�H�O�p
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g
		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s

		// �t�H�O����
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N���O�ɂȂ�����t�H�O�𓮂���
		}else{
		
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
		
			if((fog_result == 1) && (result == 3)){
				// �o�^�����O�ɂȂ�����I�����邩�`�F�b�N
				// �����̊Ǘ����邠�߂��S�Ĕj�����ꂽ��I��
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					
					// �V�[�P���X�ύX
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// �������A�j���ȊO�̂Ƃ��͓���֐��𓮂���
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherSnowStorm);
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	����I�u�W�F�N�g�o�^�֐�
 *
 *@param	pWork		�o�^����I�u�W�F�̊Ǘ��֐����[�N
 *@param	num			�o�^���鐔
 *
 *@return	none
 *
 *	���e
 *		num���I�u�W�F�N�g��o�^
 *		�J�p�Ƀ��[�N�̈��������
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherSnowStorm(WEATHER_SYS_WORK* pWork, int num)
{
	int i;		// ���[�v�p
	WAETHER_OBJ_DATA* add_obj;		// �o�^�I�u�W�F
	int tbl_num;
	WEATHER_SYSW_NORMAL* sys_w;		// �V�X�e�����[�N
	s32* obj_w;			// �I�u�W�F�N�g���[�N
	int WEATHER_SSNOW_ADD_SP_TMG[WEATHER_SSNOW_ADD_SP_TMG_NUM] = {16,32,16,10};
	int WEATHER_SSNOW_SPEED_Y[WEATHER_SSNOW_ADD_SP_TMG_NUM] = {2,2,2,2};	// ���Ăɐi�ރX�s�[�h
	int frame;	// �t���[����
	
	sys_w = (WEATHER_SYSW_NORMAL*)pWork->work;
	
	

	// num���I�u�W�F�N�g��o�^
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*8);		// �o�^
		if(add_obj == NULL){			// ���s������I��
			break;
		}

		obj_w = (s32*)add_obj->work;

		// ���̒l�����߂�
		sys_w->work[1]++;
		if(sys_w->work[1] >= (WEATHER_SSNOW_ADD_SP_TMG_TMG * WEATHER_SSNOW_ADD_SP_TMG_NUM)){
			sys_w->work[1] = 0;
		}
		tbl_num = (sys_w->work[1] / WEATHER_SSNOW_ADD_SP_TMG_TMG);
		obj_w[5] = WEATHER_SSNOW_ADD_SP_TMG[ tbl_num ];
		
	
		
		// �̈��������
		obj_w[0] = 0;			// �J�E���^
		obj_w[1] = WEATHER_SSNOW_END_MIN + (gf_mtRand() % (WEATHER_SSNOW_END_MAX - WEATHER_SSNOW_END_MIN));	// �I���J�E���^
		frame = (obj_w[1] - WEATHER_SSNOW_END_MIN) / WEATHER_SSNOW_END_DIV;	// ����̎��
		CLACT_AnmFrameSet(add_obj->clact_w, frame);
		
		obj_w[4] = WEATHER_SSNOW_SPEED_X * (frame+1);
		obj_w[2] = WEATHER_SSNOW_SPEED_Y[tbl_num] * (frame+1);	// ���ăX�s�[�h
		obj_w[3] = 0;			// �j���A�j���t���O
		
		// ���W��ݒ�
		{
			VecFx32	mat = getObjMat( add_obj );
			mat.x = WEATHER_SSNOW_START_X_BASE + (frame * WEATHER_SSNOW_MUL_X) + (gf_mtRand() % WEATHER_SSNOW_START_X_MAX);
			mat.y = WEATHER_SSNOW_START_Y;
			mat.z = 0;
			mat.x <<= FX32_SHIFT;
			mat.y <<= FX32_SHIFT;
			
			setClactMatrix(add_obj->clact_w, &mat);	
		}
	
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	����I�u�W�F�N�g����֐�
 *
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherSnowStorm(WAETHER_OBJ_DATA* work)
{
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	s32* obj_w = (s32*)p_obj->work;
	VecFx32 mat = getObjMat( p_obj );
	
	// ����t���O���`�F�b�N
	switch(obj_w[3]){
	case 0:		// ����

		// ������
		mat.x += obj_w[4] << FX32_SHIFT;
		mat.y += obj_w[2] << FX32_SHIFT;

		// �j�����邩�`�F�b�N
		if(obj_w[0]++ > obj_w[1]){
			// �j��
			obj_w[3] = 1;
		}
		// �J�E���^�œ������l��ω�
		if((obj_w[0] % obj_w[5]) == 0){
			obj_w[4]--;
			
			
			if(obj_w[2] > 1){
				obj_w[2]--;
			}//*/
		}

		setClactMatrix(p_obj->clact_w, &mat);
	
		break;
	case 1:		// �j��
		destObj(p_obj);
		break;
	}		
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	BG�g�p����Ǘ��^�X�N
 *
 *@param	tcb		�����̃^�X�N
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherSnowStormBG(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ���[�v�p
	WEATHER_SYSW_NORMAL* sys_w;			// �V�X�e�����[�N
	int		result;		// �֐�����
	int		fog_result;	// �t�H�O����
	
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
	
		
	
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		
//		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG0, 0, 16);
		
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SSNOW_ADD_START,
			WEATHER_SSNOW_TIMING_MAX,
			WEATHER_SSNOW_ADD_MAIN,
			WEATHER_SSNOW_TIMING_MIN,
			-WEATHER_SSNOW_TIMING_ADD,
			WEATHER_SSNOW_ADD_TIMING,
			WEATHER_SSNOW_ADD,
			addWeatherSnowStorm );

		

		// �t�H�O�̐ݒ�
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT, 
				WEATHER_FOG_DEPTH_DEFAULT, 
				GX_RGB(24,24,24),
				WEATHER_SSNOW_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_SSNOW_FOG_START;	// �������t�H�O�p
	
		
		sys_w->work[1] = 0;					// �I�u�W�F���J�E���^
		sys_w->work[2] = 0;					// BG�J�E���^
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		
		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s

		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
			if(sys_w->work[0] == 0){
//				G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG0, 1, 16);
			}
		}else{
			
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// �^�C�~���O���ŏ��ɂȂ����烁�C����
			if((fog_result == 1) && (result == 3)){		// �t�F�[�h���U���g�������Ȃ�΃��C����
				// �V�[�P���X�ύX
				sys_work->Sequence = WEATHER_SEQ_MAIN;
//				G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG0, 2, 16);
			}
		}
		break;

	case WEATHER_SEQ_NO_FADE:
//		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG0, 2, 16);
		
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SSNOW_ADD_MAIN,  
			WEATHER_SSNOW_TIMING_MIN,
			WEATHER_SSNOW_ADD_MAIN,
			WEATHER_SSNOW_TIMING_MIN,
			-WEATHER_SSNOW_TIMING_ADD,
			WEATHER_SSNOW_ADD_TIMING,
			WEATHER_SSNOW_ADD,
			addWeatherSnowStorm );
		

		// �t�H�O�̐ݒ�
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// �f�[�^��ݒ�
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// �t�H�O�ۑ�����
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT, GX_RGB(24,24,24) );
			// �e�[�u���f�[�^���쐬���Ĕ��f
			weatherSysFogSet( &sys_w->fogFade );
		}
	
		
		sys_w->work[1] = 0;					// �I�u�W�F���J�E���^
		sys_w->work[2] = 0;					// BG�J�E���^

		// �I�u�W�F�N�g���U��΂�
		weatherDustObj( sys_work, addWeatherSnowStorm, WEATHER_SSNOW_NOFADE_OBJ_START_NUM, WEATHER_SSNOW_NOFADE_OBJ_START_DUST_NUM, WEATHER_SSNOW_NOFADE_OBJ_START_DUST_MOVE, objWeatherSnowStorm );
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
		
	case WEATHER_SEQ_MAIN:		// ���C��
		
		// �J�E���^��0�����ɂȂ�����J�o�^
		if(sys_w->objFade.objAddTmg-- <= 0){

			// ����o�^
			addWeatherSnowStorm(sys_work, sys_w->objFade.objAddNum);
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// �o�^�^�C�~���O�Z�b�g	
		}
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_SSNOW_TIMING_MAX,
					WEATHER_SSNOW_TIMING_ADD,
					WEATHER_SSNOW_ADD_END );
			
			// fog
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_SSNOW_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_SSNOW_FOG_START_END;	// �������t�H�O�p
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g

		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s

		// �t�H�O����
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
			if(sys_w->work[0] == 0){
//				G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG0, 1, 16);
			}
		}else{
		
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
		
			if((fog_result == 1) && (result == 3)){
				// �o�^�����O�ɂȂ�����I�����邩�`�F�b�N
				// �����̊Ǘ����邠�߂��S�Ĕj�����ꂽ��I��
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					
//					G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG0, 0, 16);
					// �V�[�P���X�ύX
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// �������A�j���ȊO�̂Ƃ��͓���֐��𓮂���
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherSnowStorm);
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);

		// BG�ʂ��΂ߏ�ɓ�����
		sys_w->work[2] = (sys_w->work[2] + 6) % 256;
		G2_SetBG2Offset(sys_w->work[2],-sys_w->work[2]);

	}
}



//---------------------------------------------------------
//		��
//=========================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	���Ǘ��^�X�N
 *
 *@param	tcb		�����̃^�X�N
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherFog00(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ���[�v�p
	WEATHER_STSW_FOGFADE* sys_w;	// �V�X�e�����[�N
	int		fog_result;	// �t�H�O����
	sys_w = (WEATHER_STSW_FOGFADE*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
	

	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		// �t�H�O�̐ݒ�
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_FOG0_OFS, 
				GX_RGB(26,26,26),
				WEATHER_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_FOG_START;	// �������t�H�O�p
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
			
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// �^�C�~���O���ŏ��ɂȂ����烁�C����
			if((fog_result == 1)){		// �t�F�[�h���U���g�������Ȃ�΃��C����
				// �V�[�P���X�ύX
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
		}	
		break;
	case WEATHER_SEQ_NO_FADE:
		// �t�H�O�̐ݒ�
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// �f�[�^��ݒ�
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// �t�H�O�ۑ�����
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_FOG0_OFS, GX_RGB(26,26,26) );
			// �e�[�u���f�[�^���쐬���Ĕ��f
			weatherSysFogSet( &sys_w->fogFade );
		}
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// ���C��
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_FOG_START_END;	// �������t�H�O�p
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}
		break;
		
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
			
			// �^�C�~���O���ŏ��ɂȂ����烁�C����
			if((fog_result == 1)){		// �t�F�[�h���U���g�������Ȃ�ΏI����
				// �V�[�P���X�ύX
				sys_work->Sequence = WEATHER_SEQ_DEST;
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���Ǘ��^�X�N
 *
 *@param	tcb		�����̃^�X�N
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherFog01(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ���[�v�p
	WEATHER_STSW_FOGFADE* sys_w;	// �V�X�e�����[�N
	int		fog_result;	// �t�H�O����
	sys_w = (WEATHER_STSW_FOGFADE*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
	
		
	
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		// �t�H�O�̐ݒ�
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG1_SLOPE, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_FOG1_OFS, 
				GX_RGB(26,26,26),
				WEATHER_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_FOG_START;	// �������t�H�O�p
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
			
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// �^�C�~���O���ŏ��ɂȂ����烁�C����
			if((fog_result == 1)){		// �t�F�[�h���U���g�������Ȃ�΃��C����
				// �V�[�P���X�ύX
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
		}
		break;
	case WEATHER_SEQ_NO_FADE:
		// �t�H�O�̐ݒ�
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// �f�[�^��ݒ�
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// �t�H�O�ۑ�����
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG1_SLOPE, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_FOG1_OFS, GX_RGB(26,26,26) );

			// �e�[�u���f�[�^���쐬���Ĕ��f
			weatherSysFogSet( &sys_w->fogFade );
		}
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// ���C��
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_FOG_START_END;	// �������t�H�O�p
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}
		break;
		
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g

		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);	
			}else{
				fog_result = 1;
			}
			
			// �^�C�~���O���ŏ��ɂȂ����烁�C����
			if((fog_result == 1)){		// �t�F�[�h���U���g�������Ȃ�ΏI����
				// �V�[�P���X�ύX
				sys_work->Sequence = WEATHER_SEQ_DEST;
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���Ǘ��^�X�N
 *
 *@param	tcb		�����̃^�X�N
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherFog02(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	WEATHER_KIRI_HARAI_WORK* sys_w;	// �V�X�e�����[�N
	int		fog_result;	// �t�H�O����
	BOOL	alpha_result;
	sys_w = (WEATHER_KIRI_HARAI_WORK*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
	
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		// �t�H�O�̐ݒ�
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG2_SLOPE, 
				WEATHER_FOG_DEPTH_DEFAULT+WEATHER_FOG2_OFS, 
				GX_RGB(31,31,31),
				WEATHER_FOG_TIMING,
				sys_work->fog_use );

		WeatherMoveReq( &sys_w->alpha, 0, WEATHER_FOG2_FADE_END_ALPHA, WEATHER_FOG2_FADE_COUNT_MAX );
		WeatherBGAlphaDef(0, 16);
		G2_SetBG2Priority(3);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );

		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		
		fog_result = weatherSysFogFade(&sys_w->fogFade);

		alpha_result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);
		
		// �^�C�~���O���ŏ��ɂȂ����烁�C����
		if((fog_result == 1) && (alpha_result == TRUE)){		// �t�F�[�h���U���g�������Ȃ�΃��C����
			// �V�[�P���X�ύX
			sys_work->Sequence = WEATHER_SEQ_MAIN;
		}
		break;
	case WEATHER_SEQ_NO_FADE:
		// �t�H�O�̐ݒ�
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// �f�[�^��ݒ�
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// �t�H�O�ۑ�����
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG2_SLOPE, WEATHER_FOG_DEPTH_DEFAULT+WEATHER_FOG2_OFS, GX_RGB(31,31,31) );

			// �e�[�u���f�[�^���쐬���Ĕ��f
			weatherSysFogSet( &sys_w->fogFade );
		}

		WeatherBGAlphaDef(WEATHER_FOG2_FADE_END_ALPHA, 16 - WEATHER_FOG2_FADE_END_ALPHA);
		G2_SetBG2Priority(3);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// ���C��
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_KIRI_HARAI_WHITE_FOG_TIMING_END, FALSE );
			}

			WeatherMoveReq( &sys_w->alpha, WEATHER_FOG2_FADE_END_ALPHA, 0, WEATHER_FOG2_FADE_COUNT_MAX );
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}
		break;
		
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g

		if(sys_work->fog_use != WEATHER_FOG_NONE){
			fog_result = weatherSysFogFade(&sys_w->fogFade);
		}else{
			fog_result = 1;
		}

		alpha_result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);
		
		// �^�C�~���O���ŏ��ɂȂ����烁�C����
		if((fog_result == 1) && (alpha_result == TRUE)){		// �t�F�[�h���U���g�������Ȃ�ΏI����
			// �V�[�P���X�ύX
			sys_work->Sequence = WEATHER_SEQ_DEST;
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�����Ǘ��^�X�N
 *
 *@param	tcb		�����̃^�X�N
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherStorm(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ���[�v�p
	WEATHER_SYSW_NORMAL* sys_w;			// �V�X�e�����[�N
	int		result;		// �֐�����
	int		fog_result;	// �t�H�O����
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
		

	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_STORM_ADD_START,	// obj�o�^��
			WEATHER_STORM_TIMING_MAX,	// �o�^�^�C�~���O
			WEATHER_STORM_ADD_MAIN,
			WEATHER_STORM_TIMING_MIN,
			-WEATHER_STORM_TIMING_ADD,
			WEATHER_STORM_ADD_TIMING,
			WEATHER_STORM_ADD,
			addWeatherStorm );
		
		// �t�H�O�̐ݒ�
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_STORM_FOG_SLOPE, 
				WEATHER_STORM_FOG_OFS, 
				GX_RGB(26,20,5),
				WEATHER_STORM_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_STORM_FOG_START;	// �������t�H�O�p
		sys_w->work[1] = 0;			// �I�u�W�F�N�g�ǉ����J�E���^
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s
		
		
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// �^�C�~���O���ŏ��ɂȂ����烁�C����
			if((fog_result == 1) && (result == 3)){		// �t�F�[�h���U���g�������Ȃ�΃��C����
				// �V�[�P���X�ύX
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// �t�F�[�h�C���Ȃ�������
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_STORM_ADD_MAIN,	// obj�o�^��
			WEATHER_STORM_TIMING_MIN,	// �o�^�^�C�~���O
			WEATHER_STORM_ADD_MAIN,
			WEATHER_STORM_TIMING_MIN,
			-WEATHER_STORM_TIMING_ADD,
			WEATHER_STORM_ADD_TIMING,
			WEATHER_STORM_ADD,
			addWeatherStorm );
		
		// �t�H�O�̐ݒ�
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// �f�[�^��ݒ�
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// �t�H�O�ۑ�����
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_STORM_FOG_SLOPE, WEATHER_STORM_FOG_OFS, GX_RGB(26,20,5) );
			// �e�[�u���f�[�^���쐬���Ĕ��f
			weatherSysFogSet( &sys_w->fogFade );
		}
		sys_w->work[1] = 0;			// �I�u�W�F�N�g�ǉ����J�E���^

		// �I�u�W�F�N�g���U��΂�
		weatherDustObj( sys_work, addWeatherStorm, WEATHER_STORM_NOFADE_OBJ_START_NUM, WEATHER_STORM_NOFADE_OBJ_START_DUST_NUM, WEATHER_STORM_NOFADE_OBJ_START_DUST_MOVE, objWeatherStorm );
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// ���C��
		
		// �J�E���^��0�����ɂȂ�����J�o�^
		if(sys_w->objFade.objAddTmg-- <= 0){

			// �����o�^
			addWeatherStorm(sys_work, sys_w->objFade.objAddNum);
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// �o�^�^�C�~���O�Z�b�g	
		}
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_STORM_TIMING_MAX,
					WEATHER_STORM_TIMING_ADD,
					WEATHER_STORM_ADD_END );
			
			// fog
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_STORM_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_STORM_FOG_START_END;	// �������t�H�O�p
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g

		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s
		
		// �t�H�O����
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
		
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
		
			if((fog_result == 1) && (result == 3)){
				// �o�^�����O�ɂȂ�����I�����邩�`�F�b�N
				// �����̊Ǘ����邠�߂��S�Ĕj�����ꂽ��I��
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					
					// �V�[�P���X�ύX
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// �������A�j���ȊO�̂Ƃ��͓���֐��𓮂���
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherStorm);
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�����I�u�W�F�N�g�o�^�֐�
 *
 *@param	pWork		�o�^����I�u�W�F�̊Ǘ��֐����[�N
 *@param	num			�o�^���鐔
 *
 *@return	none
 *
 *	���e
 *		num���I�u�W�F�N�g��o�^
 *		�J�p�Ƀ��[�N�̈��������
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherStorm(WEATHER_SYS_WORK* pWork, int num)
{
	int i;		// ���[�v�p
	WAETHER_OBJ_DATA* add_obj;		// �o�^�I�u�W�F
	int	wind;	// ������
	int	rand;
	WEATHER_SYSW_NORMAL* sys_w;	// �V�X�e�����[�N
	s32* obj_w;	// �I�u�W�F���[�N
	int frame;	// �t���[����
	
	static const int	STORM_SPEED_X_TBL[WEATHER_STORM_SPEED_NUM] = {-3,-5,-5,-4,-5,-6,-10,-6};
	static const int	STORM_SPEED_Y_TBL[WEATHER_STORM_SPEED_NUM] = { 2, 2, 2, 4, 4, 2, 2, 2};
	
	sys_w = (WEATHER_SYSW_NORMAL*)pWork->work;

	
	
	// ���ύX�J�E���g
	sys_w->work[1] = (sys_w->work[1]+1) % (WEATHER_STORM_SPEED_CNG_NUM*WEATHER_STORM_SPEED_NUM);
		
	// �����������߂�
	wind = sys_w->work[1] / WEATHER_STORM_SPEED_CNG_NUM;
	
	// num���I�u�W�F�N�g��o�^
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*8);		// �o�^
		if(add_obj == NULL){			// ���s������I��
			break;
		}

		// �I�u�W�F���[�N
		obj_w = add_obj->work;
		
		
		// �̈��������
		obj_w[0] = 0;			// �J�E���^
		obj_w[1] = WEATHER_STORM_END_MIN + (gf_mtRand() % (WEATHER_STORM_END_MAX - WEATHER_STORM_END_MIN));	// �I���J�E���^
		
		frame = 3 - ((obj_w[1] - WEATHER_STORM_END_MIN) / WEATHER_STORM_END_DIV);	// ����̎��
		
		obj_w[2] = (STORM_SPEED_Y_TBL[wind]) * (frame+1);
		obj_w[4] = (STORM_SPEED_X_TBL[wind]) * (frame+1);
		obj_w[3] = 0;			// �j���A�j���t���O
		obj_w[5] = STORM_SPEED_X_TBL[wind];	// �X�s�[�h���グ�Ă����l

		// �ق�Ƃɂ��܂ɃT�{�e��
		rand = gf_mtRand() % 1000;
		if(rand == 777){
			frame = 4;
			obj_w[2] += obj_w[2] / 2;
		}
		
		CLACT_AnmFrameSet(add_obj->clact_w, frame);
		
		{
			VecFx32 mat;
			mat = getObjMat( add_obj );
			mat.x = WEATHER_STORM_START_X1 + (gf_mtRand() % WEATHER_STORM_START_X1_RAN);
			mat.x <<= FX32_SHIFT;
			mat.y = WEATHER_STORM_START_Y1_MIN + (gf_mtRand() % WEATHER_STORM_START_Y1_MAX);
			mat.y <<= FX32_SHIFT;
			setClactMatrix(add_obj->clact_w, &mat);
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�����I�u�W�F�N�g����֐�
 *
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherStorm(WAETHER_OBJ_DATA* work)
{
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	s32* obj_w = (s32*)p_obj->work;		// �I�u�W�F���[�N
	VecFx32 mat = getObjMat( p_obj );
	
	// ����t���O���`�F�b�N
	switch(obj_w[3]){
	case 0:		// ����

		// ������
		mat.x += obj_w[4] << FX32_SHIFT;
		mat.y += obj_w[2] << FX32_SHIFT;

		if((obj_w[0] % WEATHER_STORM_SPEED_ADD_TMG) == 0){
			obj_w[4] += obj_w[5];
		}

		// �j�����邩�`�F�b�N
		if(obj_w[0]++ > obj_w[1]){
			// �j��
			obj_w[3] = 1;
		}

		setClactMatrix(p_obj->clact_w, &mat);
			
		break;
	case 1:		// �j��
		destObj(p_obj);
		break;
	}		
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�����Ǘ��^�X�N		BG�g�p
 *
 *@param	tcb		�����̃^�X�N
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherStormBG(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ���[�v�p
	int		wind;		// ���e�[�u���̒l
	int		scl_x, scl_y;// �X�N���[�����W
	WEATHER_SYSW_NORMAL* sys_w;	// �V�X�e�����[�N
	int		result;		// �֐�����
	int		fog_result;	// �t�H�O����
	static const int STORM_SPEED_X_TBL[WEATHER_STORM_SPEED_NUM] = {-3,-5,-5,-3,-5,-6,-10,-6};
	static const int STORM_SPEED_Y_TBL[WEATHER_STORM_SPEED_NUM] = { 2, 2, 2, 4, 4, 2, 2, 2};	
	
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ���[�N�|�C���^�Z�b�g


	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		

		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_STORM_ADD_START,	// obj�o�^��
			WEATHER_STORM_TIMING_MAX,	// �o�^�^�C�~���O
			WEATHER_STORM_ADD_MAIN,
			WEATHER_STORM_TIMING_MIN,
			-WEATHER_STORM_TIMING_ADD,
			WEATHER_STORM_ADD_TIMING,
			WEATHER_STORM_ADD,
			addWeatherStorm );
	
		// �t�H�O�̐ݒ�
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_STORM_FOG_SLOPE, 
				WEATHER_STORM_FOG_OFS, 
				GX_RGB(26,20,5),
				WEATHER_STORM_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_STORM_FOG_START;	// �������t�H�O�p
		sys_w->work[1] = 0;		// �I�u�W�F�N�g�ǉ����J�E���^
		sys_w->work[2] = 0;		// BG�J�E���^
		sys_w->work[3] = 0;		// ���̃X�s�[�h
		

		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		
		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s
		
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
			
			// fog
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// �^�C�~���O���ŏ��ɂȂ����烁�C����
			if((fog_result == 1) && (result == 3)){		// �t�F�[�h���U���g�������Ȃ�΃��C����
				// �V�[�P���X�ύX
				sys_work->Sequence = WEATHER_SEQ_MAIN;

				// BGON
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
			}
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// �t�F�[�h�C���Ȃ�������
		

		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_STORM_ADD_MAIN,	// obj�o�^��
			WEATHER_STORM_TIMING_MIN,	// �o�^�^�C�~���O
			WEATHER_STORM_ADD_MAIN,
			WEATHER_STORM_TIMING_MIN,
			-WEATHER_STORM_TIMING_ADD,
			WEATHER_STORM_ADD_TIMING,
			WEATHER_STORM_ADD,
			addWeatherStorm );
	
		// �t�H�O�̐ݒ�
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// �f�[�^��ݒ�
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// �t�H�O�ۑ�����
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_STORM_FOG_SLOPE, WEATHER_STORM_FOG_OFS, GX_RGB(26,20,5) );
			// �e�[�u���f�[�^���쐬���Ĕ��f
			weatherSysFogSet( &sys_w->fogFade );
		}

		
		sys_w->work[1] = 0;		// �I�u�W�F�N�g�ǉ����J�E���^
		sys_w->work[2] = 0;		// BG�J�E���^
		sys_w->work[3] = 0;		// ���̃X�s�[�h
		
		// �I�u�W�F�N�g���U��΂�
		weatherDustObj( sys_work, addWeatherStorm, WEATHER_STORM_NOFADE_OBJ_START_NUM, WEATHER_STORM_NOFADE_OBJ_START_DUST_NUM, WEATHER_STORM_NOFADE_OBJ_START_DUST_MOVE, objWeatherStorm );
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;

		// BGON
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		break;
	case WEATHER_SEQ_MAIN:		// ���C��
		
		// �J�E���^��0�����ɂȂ�����J�o�^
		if(sys_w->objFade.objAddTmg-- <= 0){

			// ���e�[�u�����擾
			wind = sys_w->work[1] / WEATHER_STORM_SPEED_CNG_NUM;
			// ����ݒ肷��
			sys_w->work[3] = STORM_SPEED_X_TBL[wind];
			
			// ���l�ƃI�u�W�F�̏o���ʂ𕗂̋����ŕς���
			if(sys_w->work[3] <= -WEATHER_STORM_STRONG_CHG){
				// �����o�^
				addWeatherStorm(sys_work, sys_w->objFade.objAddNum*2);
			
			}else{
				// �����o�^
				addWeatherStorm(sys_work, sys_w->objFade.objAddNum);
			}
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// �o�^�^�C�~���O�Z�b�g	
		}
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			// �t�F�[�h�A�E�g�ݒ�
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_STORM_TIMING_MAX,
					WEATHER_STORM_TIMING_ADD,
					WEATHER_STORM_ADD_END );

			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_STORM_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_STORM_FOG_START_END;	// �������t�H�O�p
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
			// BGOFF
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		}

		break;
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g

		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s

		// �t�H�O����
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
		
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result;
			}
		
			if((fog_result == 1) && (result == 3)){
				// �o�^�����O�ɂȂ�����I�����邩�`�F�b�N
				// �����̊Ǘ����邠�߂��S�Ĕj�����ꂽ��I��
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					
					// �V�[�P���X�ύX
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// �������A�j���ȊO�̂Ƃ��͓���֐��𓮂���
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherStorm);
		scrollObj(sys_work, &scl_x, &scl_y);
		drawObj(sys_work);

		// BG�ʂ��΂ߏ�ɓ�����
		sys_w->work[2] = (sys_w->work[2] + 6) % 256;
		G2_SetBG2Offset(sys_w->work[2]*2 - scl_x,-sys_w->work[2] + scl_y);
	}
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	�k�C����Ǘ��^�X�N
 *
 *@param	tcb		�����̃^�X�N
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherSnowSML(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ���[�v�p
	int		wind;		// ��
	int		scl_x, scl_y;// �X�N���[�����W
	WEATHER_SYSW_NORMAL* sys_w;	// �V�X�e�����[�N
	int		result;		// �֐�����
	int		fog_result;	// �t�H�O����
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
	
		

	
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		
		
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SSNOW_ADD_START,	// obj�o�^��
			WEATHER_SSNOW_TIMING_MAX,	// �o�^�^�C�~���O
			WEATHER_SNOW_S_ADD_MAIN,
			WEATHER_SNOW_S_TIMING_MIN,
			-WEATHER_SNOW_S_TIMING_ADD,
			WEATHER_SNOW_S_ADD_TIMING,
			WEATHER_SNOW_S_ADD,
			addWeatherSnowSML );
		
		// �t�H�O�̐ݒ�
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_SNOW_S_FOG_OFS, 
				GX_RGB(24,24,24),
				WEATHER_SNOW_S_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_SNOW_S_FOG_START;	// �������t�H�O�p
		
		sys_w->work[1] = 0;				// �I�u�W�F���J�E���^
		sys_w->work[2] = 0;				// BG�J�E���^

		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s	
	
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{

			// fog
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// �^�C�~���O���ŏ��ɂȂ����烁�C����
			if((fog_result == 1) && (result == 3)){		// �t�F�[�h���U���g�������Ȃ�΃��C����
				// �V�[�P���X�ύX
				sys_work->Sequence = WEATHER_SEQ_MAIN;
				// BGON
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
			}
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// �t�F�[�h�C���Ȃ�������
		
		
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SNOW_S_ADD_MAIN,	// obj�o�^��
			WEATHER_SNOW_S_TIMING_MIN,	// �o�^�^�C�~���O
			WEATHER_SNOW_S_ADD_MAIN,
			WEATHER_SNOW_S_TIMING_MIN,
			-WEATHER_SNOW_S_TIMING_ADD,
			WEATHER_SNOW_S_ADD_TIMING,
			WEATHER_SNOW_S_ADD,
			addWeatherSnowSML );
		
		// �t�H�O�̐ݒ�
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// �f�[�^��ݒ�
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// �t�H�O�ۑ�����
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_SNOW_S_FOG_OFS, GX_RGB(24,24,24) );
			// �e�[�u���f�[�^���쐬���Ĕ��f
			weatherSysFogSet( &sys_w->fogFade );
		}

		sys_w->work[1] = 0;				// �I�u�W�F���J�E���^
		sys_w->work[2] = 0;				// BG�J�E���^


		// �I�u�W�F�N�g���U��΂�
		weatherDustObj( sys_work, addWeatherSnowSML, WEATHER_SNOW_S_NOFADE_OBJ_START_NUM, WEATHER_SNOW_S_NOFADE_OBJ_START_DUST_NUM, WEATHER_SNOW_S_NOFADE_OBJ_START_DUST_MOVE, objWeatherSnowSML );
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		
		// BGON
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		break;
	case WEATHER_SEQ_MAIN:		// ���C��
		
		// �J�E���^��0�����ɂȂ�����J�o�^
		if(sys_w->objFade.objAddTmg-- <= 0){

			wind = sys_w->work[1] / WEATHER_SNOW_S_ADD_SP_CHG_TMG;
			wind = WEATHER_SSNOW_SPEED_X_SML[wind];
			
			if(wind <= -WEATHER_SNOW_S_SP_UP){
				// ����o�^
				addWeatherSnowSML(sys_work, sys_w->objFade.objAddNum*2);
			}else{
				// ����o�^
				addWeatherSnowSML(sys_work, sys_w->objFade.objAddNum);
			}
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// �o�^�^�C�~���O�Z�b�g	
		}
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_SNOW_S_TIMING_MAX,
					WEATHER_SNOW_S_TIMING_ADD,
					WEATHER_SNOW_S_ADD_END );
			
			// fog
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_SNOW_S_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_SNOW_S_FOG_START_END;	// �������t�H�O�p
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
			
			// BGOFF
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g

		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s

		// �t�H�O����
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
		
			// fog
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
		
			if((fog_result == 1) && (result == 3)){
				// �o�^�����O�ɂȂ�����I�����邩�`�F�b�N
				// �����̊Ǘ�����Ⴊ�S�Ĕj�����ꂽ��I��
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					// �V�[�P���X�ύX
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}		
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}	
		break;

	default:
		break;
	}

	// �������A�j���ȊO�̂Ƃ��͓���֐��𓮂���
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherSnowSML);
//		scrollObj(sys_work, &scl_x, &scl_y);
		drawObj(sys_work);

		// BG�ʂ��΂ߏ�ɓ�����
		sys_w->work[2] = (sys_w->work[2] + 12) % 256;
		G2_SetBG2Offset(sys_w->work[2]*2,-sys_w->work[2]);

	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�k�C����I�u�W�F�N�g�o�^�֐�
 *
 *@param	pWork		�o�^����I�u�W�F�̊Ǘ��֐����[�N
 *@param	num			�o�^���鐔
 *
 *@return	none
 *
 *	���e
 *		num���I�u�W�F�N�g��o�^
 *		�J�p�Ƀ��[�N�̈��������
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherSnowSML(WEATHER_SYS_WORK* pWork, int num)
{
	int i;		// ���[�v�p
	WAETHER_OBJ_DATA* add_obj;		// �o�^�I�u�W�F
	int tbl_num;
	WEATHER_SYSW_NORMAL* sys_w;	// �V�X�e�����[�N
	s32* obj_w;	// �I�u�W�F�N�g���[�N
	int		frame;		// �t���[����
	
	sys_w = (WEATHER_SYSW_NORMAL*)pWork->work;

		
	// ���̒l�����߂�
	sys_w->work[1]++;
	if(sys_w->work[1] >= (WEATHER_SNOW_S_ADD_SP_CHG_TMG  * WEATHER_SNOW_S_ADD_SP_TMG_NUM)){
		sys_w->work[1] = 0;
	}
	tbl_num = (sys_w->work[1] / WEATHER_SNOW_S_ADD_SP_CHG_TMG );

	
	// num���I�u�W�F�N�g��o�^
	for(i=0;i<num*4;i++){

		add_obj = addObj(pWork, sizeof(s32)*8);		// �o�^
		if(add_obj == NULL){			// ���s������I��
			break;
		}

		obj_w = (s32*)add_obj->work;
		
		// �̈��������
		obj_w[0] = 0;			// �J�E���^
		obj_w[1] = WEATHER_SNOW_S_END_MIN + (gf_mtRand() % (WEATHER_SNOW_S_END_MAX - WEATHER_SNOW_S_END_MIN));	// �I���J�E���^
		frame = gf_mtRand()%4;	// ����̎��
		CLACT_AnmFrameSet( add_obj->clact_w, frame );
		
		obj_w[4] = WEATHER_SSNOW_SPEED_X_SML[tbl_num] * ((frame)+1);
		obj_w[2] = WEATHER_SSNOW_SPEED_Y_SML[tbl_num] * ((frame)+1);	// ���ăX�s�[�h
		obj_w[3] = 0;			// �j���A�j���t���O
		if(frame == 3){
			obj_w[4] += WEATHER_SSNOW_SPEED_X_SML[tbl_num];
			obj_w[2] += WEATHER_SSNOW_SPEED_Y_SML[tbl_num];
		}
		obj_w[5] = WEATHER_SSNOW_SPEED_X_SML[tbl_num];
		
		// ���W��ݒ�
		{
			VecFx32 mat = getObjMat( add_obj );
			mat.x = WEATHER_SNOW_S_START_X + (gf_mtRand() % WEATHER_SNOW_S_START_X_RAN);
			mat.y = WEATHER_SNOW_S_START_Y_BASE + (gf_mtRand() % WEATHER_SNOW_S_START_Y_MAX);
			mat.x <<= FX32_SHIFT;
			mat.y <<= FX32_SHIFT;
			mat.z = 0;

			setClactMatrix(add_obj->clact_w, &mat);
		}
	
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	����I�u�W�F�N�g����֐�
 *
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherSnowSML(WAETHER_OBJ_DATA* work)
{
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	s32* obj_w = (s32*)p_obj->work;
	VecFx32 mat = getObjMat( p_obj );
	
	// ����t���O���`�F�b�N
	switch(obj_w[3]){
	case 0:		// ����

		// ������
		mat.x += obj_w[4] << FX32_SHIFT;
		mat.y += obj_w[2] << FX32_SHIFT;

		// �j�����邩�`�F�b�N
		if(obj_w[0]++ > obj_w[1]){
			// �j��
			obj_w[3] = 1;
		}
		// �J�E���^�œ������l��ω�
		if((obj_w[0] % WEATHER_SNOW_S_ADD_SP_TMG) == 0){
			obj_w[4] += obj_w[5];
			
			if(obj_w[2] > 1){
				obj_w[2]--;
			}
		}
	
		setClactMatrix( p_obj->clact_w, &mat );
		break;
	case 1:		// �j��
		destObj(p_obj);
		break;
	}		
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�X�m�[�_�X�g�Ǘ��^�X�N
 *
 *@param	tcb		�����̃^�X�N
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherSnowD(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ���[�v�p
	WEATHER_SYSW_NORMAL* sys_w;		// �V�X�e�����[�N
	int		result;		// �֐�����
	int		fog_result;	// �t�H�O����
	
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
	

		
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������

	
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SNOW_D_ADD_START,	// obj�o�^��
			WEATHER_SNOW_D_TIMING_MAX,// �o�^�^�C�~���O
			WEATHER_SNOW_D_ADD_MAIN,
			WEATHER_SNOW_D_TIMING_MIN,
			-WEATHER_SNOW_D_TIMING_ADD,
			WEATHER_SNOW_D_ADD_TIMING,
			WEATHER_SNOW_D_ADD,
			addWeatherSnowD );
		
		// �t�H�O�ݒ�
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_SNOW_D_FOG_OFS, 
				GX_RGB(26,26,26),
				WEATHER_SNOW_D_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_SNOW_D_FOG_START;	// �������t�H�O�p
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s	
		

		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// �^�C�~���O���ŏ��ɂȂ����烁�C����
			if((fog_result == 1) && (result == 3)){		// �t�F�[�h���U���g�������Ȃ�΃��C����
				// �V�[�P���X�ύX
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// �t�F�[�h�C���Ȃ�������

	
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SNOW_D_ADD_MAIN,	// obj�o�^��
			WEATHER_SNOW_D_TIMING_MIN,// �o�^�^�C�~���O
			WEATHER_SNOW_D_ADD_MAIN,
			WEATHER_SNOW_D_TIMING_MIN,
			-WEATHER_SNOW_D_TIMING_ADD,
			WEATHER_SNOW_D_ADD_TIMING,
			WEATHER_SNOW_D_ADD,
			addWeatherSnowD );
		
		// �t�H�O�ݒ�
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// �t�H�O�ۑ�����
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_SNOW_D_FOG_OFS, GX_RGB(26,26,26) );
			// �e�[�u���f�[�^���쐬���Ĕ��f
			weatherSysFogSet( &sys_w->fogFade );
		}

		// �I�u�W�F�N�g���U��΂�
		weatherDustObj( sys_work, addWeatherSnowD, WEATHER_SNOW_D_NOFADE_OBJ_START_NUM, WEATHER_SNOW_D_NOFADE_OBJ_START_DUST_NUM, WEATHER_SNOW_D_NOFADE_OBJ_START_DUST_MOVE, objWeatherSnowD );
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// ���C��
		
		// �J�E���^��0�����ɂȂ�����J�o�^
		if(sys_w->objFade.objAddTmg-- <= 0){
			
			
			// �_�C�������h�_�X�g�o�^
			addWeatherSnowD(sys_work, sys_w->objFade.objAddNum);
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// �o�^�^�C�~���O�Z�b�g	
		}
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){

			// �t�F�[�h�A�E�g�ݒ�
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_SNOW_D_TIMING_MAX,
					WEATHER_SNOW_D_TIMING_ADD_END,
					-WEATHER_SNOW_D_ADD_END );
			
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_SNOW_D_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_SNOW_S_FOG_START_END;	// �������t�H�O�p	
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g

		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s
		

		// �t�H�O����
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
		
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
		
			if((fog_result == 1) && (result == 3)){
				// �o�^�����O�ɂȂ�����I�����邩�`�F�b�N
				// �����̊Ǘ����邠�߂��S�Ĕj�����ꂽ��I��
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					
					// �V�[�P���X�ύX
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// �������A�j���ȊO�̂Ƃ��͓���֐��𓮂���
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherSnowD);
		
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);

	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�X�m�[�_�X�g�I�u�W�F�N�g�o�^�֐�
 *
 *@param	pWork		�o�^����I�u�W�F�̊Ǘ��֐����[�N
 *@param	num			�o�^���鐔
 *
 *@return	none
 *
 *	���e
 *		num���I�u�W�F�N�g��o�^
 *		�J�p�Ƀ��[�N�̈��������
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherSnowD(WEATHER_SYS_WORK* pWork, int num)
{
	int i;		// ���[�v�p
	WAETHER_OBJ_DATA* add_obj;		// �o�^�I�u�W�F
	int	rand;
	int sum_y;	// y���W�v�Z
	int	big_d;	// �傫���_�C�������h�_�X�g�ɂ��邩�`�F�b�N
	int frame;	// �t���[����
	VecFx32 mat;	// ���W
	s32* obj_w;	// �I�u�W�F�N�g���[�N
	
	// num���I�u�W�F�N�g��o�^
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*8);		// �o�^
		if(add_obj == NULL){			// ���s������I��
			break;
		}

		obj_w = (s32*)add_obj->work;
		
		obj_w[0] = 0;		// �J�E���^
		obj_w[1] = WEATHER_SNOW_D_SPARK_NUM_MIN + (gf_mtRand() % WEATHER_SNOW_D_SPARK_NUM_RAN);
		rand = gf_mtRand() % 1000;

		
		if((rand % 2) == 0){			// ���̈ړ��̃v���X�}�C�i�X
			obj_w[2] = 1;
		}else{
			obj_w[2] = -1;
		}
		obj_w[3] = 1;
		

		obj_w[4] = WEATHER_SNOW_D_SP_ADD_TMG_X_MIN + (gf_mtRand() % WEATHER_SNOW_D_SP_ADD_TMG_X_MAX);
		obj_w[5] = WEATHER_SNOW_D_SP_ADD_TMG_Y_MIN + (gf_mtRand() % WEATHER_SNOW_D_SP_ADD_TMG_Y_MAX);
		
	
		// �����������o��
		frame = gf_mtRand() % WEATHER_SNOW_D_SPARK_NO;
		
		// ���W
		{
			mat = getObjMat( add_obj );
			mat.x = WEATHER_SNOW_D_START_X_MIN + (gf_mtRand() % WEATHER_SNOW_D_START_X_DIS);
			mat.y = WEATHER_SNOW_D_START_Y + (gf_mtRand() % WEATHER_SNOW_D_START_Y_MAX);
			mat.x <<= FX32_SHIFT;
			mat.y <<= FX32_SHIFT;
			mat.z = 0;
			setClactMatrix( add_obj->clact_w, &mat );
			mat.x >>= FX32_SHIFT;
			mat.y >>= FX32_SHIFT;
		}
		
		
		// X�̒l����������ŋ��߂�
		sum_y = 50 - (mat.x/3);
		rand = 206 - (mat.x/3);
		if(rand < 0){
			rand*=-1;
			big_d = sum_y - (gf_mtRand()%rand);		
		}else{
			big_d = sum_y + (gf_mtRand()%rand);		
		}
		if((sum_y <= mat.y) &&
			(big_d >= mat.y)){
			
			obj_w[1] *= 2;
//			obj_w[6] = 4;		// �����_��
		}else{
			// ���������ɂ���
			frame = gf_mtRand() % 4;
//			obj_w[6] = 1;		// ������
		}
		CLACT_AnmFrameSet( add_obj->clact_w, frame );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�X�m�[�_�X�g�I�u�W�F�N�g����֐�
 *
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherSnowD(WAETHER_OBJ_DATA* work)
{
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	int		rand;
	s32* obj_w = (s32*)p_obj->work;
	VecFx32 mat = getObjMat( p_obj );


	// �Ԃ��
	obj_w[0]++;
	
	if((obj_w[0] % obj_w[4]) == 0){
		mat.x += obj_w[2] << FX32_SHIFT;
	}
	
	if((obj_w[0] % obj_w[5]) == 0){
		mat.y += obj_w[3] << FX32_SHIFT;
	}
	
	// �j�����邩�`�F�b�N
	if(obj_w[0] >= obj_w[1]){
		destObj(p_obj);
		return ;
	}
		
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	���Ǘ��^�X�N
 *
 *@param	tcb		�����̃^�X�N
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherRainbow(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ���[�v�p
	s32* sys_w;			// �V�X�e�����[�N

	sys_w = (s32*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
	

		
	
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������

		sys_w[0] = 0;	// �A���t�@�J�E���^
		sys_w[1] = 0;	// �A���t�@�l
		
		WeatherBGAlphaDef(0, 16);
		G2_SetBG2Offset(0,32);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��

		sys_w[0]++;
		
		if(sys_w[0] >= 10){
			sys_w[0] = 0;
			sys_w[1]++;
		
			WeatherBGAlphaDef(sys_w[1], 16);
			if(sys_w[1] >= 10){
				sys_w[2] = 10 + (gf_mtRand() % 20);	// �l��ύX����^�C�~���O
				sys_w[3] = 5 + (gf_mtRand() % 3);		// �A���t�@�𗎂Ƃ����x
				sys_w[4] = 1;							// �A���t�@�����炷��
				
				// �V�[�P���X�ύX
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
			
		}
		
		
		break;

	case WEATHER_SEQ_NO_FADE:	// �t�F�[�h�C���Ȃ�������

		sys_w[0] = 0;	// �A���t�@�J�E���^
		sys_w[1] = 10;	// �A���t�@�l
		G2_SetBG2Offset(0,32);
		
		WeatherBGAlphaDef(sys_w[1], 16);
		
		sys_w[2] = 10 + (gf_mtRand() % 20);	// �l��ύX����^�C�~���O
		sys_w[3] = 5 + (gf_mtRand() % 3);		// �A���t�@�𗎂Ƃ����x
		sys_w[4] = 1;							// �A���t�@�����炷��
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	
	case WEATHER_SEQ_MAIN:		// ���C��
		sys_w[0]++;
		

		if(sys_w[0] >= sys_w[2]){
			sys_w[0] = 0;

			if(sys_w[4] == 1){
				sys_w[1]--;
				if(sys_w[1] <= sys_w[3]){
					sys_w[2] = 10 + (gf_mtRand() % 15);		// �l��ύX����^�C�~���O
					sys_w[3] = 7 + (gf_mtRand() % 3);		// �A���t�@�𗎂Ƃ����x
					sys_w[4] = 0;							// �A���t�@�����炷��
				}
			}else{
				sys_w[1]++;
				if(sys_w[1] >= sys_w[3]){
					sys_w[2] = 10 + (gf_mtRand() % 20);	// �l��ύX����^�C�~���O
					sys_w[3] = 5 + (gf_mtRand() % 3);		// �A���t�@�𗎂Ƃ����x
					sys_w[4] = 1;							// �A���t�@�����炷��
				}
			}
		}
		WeatherBGAlphaDef(sys_w[1], 16);
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}
		break;
	
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g
		sys_w[0]++;
		
		if(sys_w[0] >= 10){
			sys_w[0] = 0;
			sys_w[1]--;
		
			WeatherBGAlphaDef(sys_w[1], 16);
			if(sys_w[1] <= 0){
				// �V�[�P���X�ύX
				sys_work->Sequence = WEATHER_SEQ_DEST;
			}
			
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}	
		break;

	default:
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	��J����������
 *	@param	sys_work
 *	@param	sys_w 
 *	@return
 */
//-----------------------------------------------------------------------------
static void contWeatherSTRain_Init( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w )
{
	// ��Ɨ̈�̏�����
	weatherSysObjFadeInit( &sys_w->objFade, sys_work,
		WEATHER_STRAIN_ADD_START,	// obj�o�^��
		WEATHER_STRAIN_TIMING_MAX,// �o�^�^�C�~���O
		WEATHER_STRAIN_ADD_MAIN,
		WEATHER_STRAIN_TIMING_MIN,
		-WEATHER_STRAIN_TIMING_ADD,
		WEATHER_STRAIN_ADD_TIMING,
		WEATHER_STRAIN_ADD,
		addWeatherSTRain );
	

	// �t�H�O�̐ݒ�
	weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
			sys_work->pWSysCont->fsys->fog_data,
			WEATHER_FOG_SLOPE_DEFAULT, 
			WEATHER_FOG_DEPTH_DEFAULT, 
			GX_RGB(26,26,26),
			WEATHER_STRAIN_FOG_TIMING,
			sys_work->fog_use );
	sys_w->work[0] = WEATHER_STRAIN_FOG_START;	// �������t�H�O�p
	sys_w->work[1] = 0;
	sys_w->work[2] = 0;							// ���J�E���^

	// ��
	WeatherLoopSndPlay( sys_work, SEQ_SE_DP_T_OOAME );	

//*/
}

//----------------------------------------------------------------------------
/**
 *	@brief	��J�t�F�[�h�C������
 *	@param	sys_work
 *	@param	sys_w 
 *
 *	@retval	TRUE	�t�F�[�h����
 *	@retval	FALSE	�t�F�[�h�r��
 */
//-----------------------------------------------------------------------------
static BOOL contWeatherSTRain_FadeIn( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w )
{
	int		result;		// �֐�����
	int		fog_result;	// �t�H�O����

	// �I�u�W�F�N�g�t�F�[�h
	result = weatherSysObjFade(&sys_w->objFade);	// ���s	

	if(sys_w->work[0] > 0){
		sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		
	}else{
		fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
		

		// �^�C�~���O���ŏ��ɂȂ����烁�C����
		if((fog_result == 1) && (result == 3)){		// �t�F�[�h���U���g�������Ȃ�΃��C����
			return TRUE;
		}
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	��J�@�t�F�[�h�Ȃ�������
 *
 *	@param	sys_work	
 *	@param	sys_w 
 */
//-----------------------------------------------------------------------------
static void contWeatherSTRain_NoFade( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w )
{
	// ��Ɨ̈�̏�����
	weatherSysObjFadeInit( &sys_w->objFade, sys_work,
		WEATHER_STRAIN_ADD_MAIN,	// obj�o�^��
		WEATHER_STRAIN_TIMING_MIN,// �o�^�^�C�~���O
		WEATHER_STRAIN_ADD_MAIN,
		WEATHER_STRAIN_TIMING_MIN,
		-WEATHER_STRAIN_TIMING_ADD,
		WEATHER_STRAIN_ADD_TIMING,
		WEATHER_STRAIN_ADD,
		addWeatherSTRain );
	

	// �t�H�O�̐ݒ�
	if(sys_work->fog_use != WEATHER_FOG_NONE){
		// �f�[�^��ݒ�
		sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// �t�H�O�ۑ�����
		weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT, GX_RGB(26,26,26) );
		// �e�[�u���f�[�^���쐬���Ĕ��f
		weatherSysFogSet( &sys_w->fogFade );
	}

	sys_w->work[1] = 0;
	sys_w->work[2] = 0;							// ���J�E���^

	// �I�u�W�F�N�g���U��΂�
	weatherDustObj( sys_work, addWeatherSTRain, WEATHER_STRAIN_NOFADE_OBJ_START_NUM, WEATHER_STRAIN_NOFADE_OBJ_START_DUST_NUM, WEATHER_STRAIN_NOFADE_OBJ_START_DUST_MOVE, objWeatherSTRain );


	// ��
	WeatherLoopSndPlay( sys_work, SEQ_SE_DP_T_OOAME );	
}

//----------------------------------------------------------------------------
/**
 *	@brief	��J���C������
 *
 *	@param	sys_work
 *	@param	sys_w 
 */
//-----------------------------------------------------------------------------
static void contWeatherSTRain_Main( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w )
{
	sys_w->work[2] = (sys_w->work[2] + 1) % (WEATHER_STRAIN_OBJ_MUL_CHG*WEATHER_STRAIN_OBJ_MUL_NUM);		// �J�o�^���ύX�J�E���^
	// �J�E���^��0�����ɂȂ�����J�o�^
	if(sys_w->objFade.objAddTmg-- <= 0){
						
		// �J�o�^
		addWeatherSTRain(sys_work, sys_w->objFade.objAddNum);

		sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// �o�^�^�C�~���O�Z�b�g	
	}
}
//----------------------------------------------------------------------------
/**
 *	@brief	��J�t�F�[�h�A�E�g����������
 *	@param	sys_work
 *	@param	sys_w 
 */
//-----------------------------------------------------------------------------
static void contWeatherSTRain_FadeOutInit( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w )
{
	// obj
	// �t�F�[�h�A�E�g�ݒ�
	weatherSysObjFadeOutSet( &sys_w->objFade,
			0,
			WEATHER_STRAIN_TIMING_MAX,
			WEATHER_STRAIN_TIMING_ADD,
			WEATHER_STRAIN_ADD_END );
	
	// fog
	if(sys_work->fog_use != WEATHER_FOG_NONE){
		weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_STRAIN_FOG_TIMING_END, FALSE );
	}
	sys_w->work[0] = WEATHER_STRAIN_FOG_START_END;	// �������t�H�O�p

	// ��
	WeatherLoopSndStop( sys_work );	
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	��J�t�F�[�h�A�E�g����
 *
 *	@param	sys_work
 *	@param	sys_w 
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL contWeatherSTRain_FadeOut( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w )
{
	int		result;		// �֐�����
	int		fog_result;	// �t�H�O����

	// �I�u�W�F�N�g�t�F�[�h
	result = weatherSysObjFade(&sys_w->objFade);	// ���s
	
	// �t�H�O����
	if(sys_w->work[0] > 0){
		sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		
	}else{
	
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			fog_result = weatherSysFogFade(&sys_w->fogFade);
		}else{
			fog_result = 1;
		}

		if((fog_result == 1) && (result == 3)){
			// �o�^�����O�ɂȂ�����I�����邩�`�F�b�N
			// �����̊Ǘ����邠�߂��S�Ĕj�����ꂽ��I��
			if(sys_work->Dummy.pNext == &sys_work->Dummy){
				
				return TRUE;
			}
		}
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	��J�@�j������
 *
 *	@param	sys_work
 *	@param	sys_w 
 */
//-----------------------------------------------------------------------------
static void contWeatherSTRain_Dest( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w )
{
	if(sys_work->fog_use != WEATHER_FOG_NONE){
		SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
	}
	{
		WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
		stopWeatherWork_local(p_wsd);

	}

}

//----------------------------------------------------------------------------
/**
 *	@brief	��J�@�`�揈��
 *
 *	@param	sys_work
 *	@param	sys_w 
 */
//-----------------------------------------------------------------------------
static void contWeatherSTRain_Draw( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w )
{
	// �������A�j���ȊO�̂Ƃ��͓���֐��𓮂���
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherSTRain);
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	��J�{��
 *
 *	@param	tcb		TCB���[�N
 *	@param	work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void contWeatherSTRainSpark(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	WEATHER_SYSW_NORMAL* sys_w;	// �V�X�e�����[�N
	
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
	
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		// ����������
		contWeatherSTRain_Init( sys_work, sys_w );
		// ���𔭓�
		ControlWeatherSys( sys_work->pWSysCont, WEATHER_SYS_INIT, WEATHER_SYS_SPARK_EFF );
		ControlWeatherSys( sys_work->pWSysCont, WEATHER_SYS_START_NOFADE, WEATHER_SYS_SPARK_EFF );
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		if( contWeatherSTRain_FadeIn( sys_work, sys_w ) ){
			// �V�[�P���X�ύX
			sys_work->Sequence = WEATHER_SEQ_MAIN;
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// �t�F�[�h�C���Ȃ�������
		contWeatherSTRain_NoFade( sys_work, sys_w );
		// ���𔭓�
		ControlWeatherSys( sys_work->pWSysCont, WEATHER_SYS_INIT, WEATHER_SYS_SPARK_EFF );
		ControlWeatherSys( sys_work->pWSysCont, WEATHER_SYS_START_NOFADE, WEATHER_SYS_SPARK_EFF );//*/
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;

		break;
	case WEATHER_SEQ_MAIN:		// ���C��
		contWeatherSTRain_Main( sys_work, sys_w );
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			contWeatherSTRain_FadeOutInit( sys_work, sys_w );
			// ���I��
			ControlWeatherSys( sys_work->pWSysCont, WEATHER_SYS_END, WEATHER_SYS_SPARK_EFF );//*/

			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}

		break;
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g
		if( contWeatherSTRain_FadeOut( sys_work, sys_w ) ){
			// �V�[�P���X�ύX
			sys_work->Sequence = WEATHER_SEQ_DEST;
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		contWeatherSTRain_Dest( sys_work, sys_w );
		// �������I��
		ControlWeatherSys( sys_work->pWSysCont, WEATHER_SYS_DEST, WEATHER_SYS_SPARK_EFF );//*/

		break;

	default:
		break;
	}
	// �`�揈��
	contWeatherSTRain_Draw( sys_work, sys_w );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�J�Ǘ��^�X�N
 *
 *@param	tcb		�����̃^�X�N
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherSTRain(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	WEATHER_SYSW_NORMAL* sys_w;	// �V�X�e�����[�N
	
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
	
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		// ����������
		contWeatherSTRain_Init( sys_work, sys_w );
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;

		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		if( contWeatherSTRain_FadeIn( sys_work, sys_w ) ){
			// �V�[�P���X�ύX
			sys_work->Sequence = WEATHER_SEQ_MAIN;
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// �t�F�[�h�C���Ȃ�������
		contWeatherSTRain_NoFade( sys_work, sys_w );
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// ���C��
		contWeatherSTRain_Main( sys_work, sys_w );
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			contWeatherSTRain_FadeOutInit( sys_work, sys_w );

			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}

		break;
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g
		if( contWeatherSTRain_FadeOut( sys_work, sys_w ) ){
			// �V�[�P���X�ύX
			sys_work->Sequence = WEATHER_SEQ_DEST;
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		contWeatherSTRain_Dest( sys_work, sys_w );
		break;

	default:
		break;
	}
	// �`�揈��
	contWeatherSTRain_Draw( sys_work, sys_w );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�J�I�u�W�F�N�g�o�^�֐�
 *
 *@param	pWork		�o�^����I�u�W�F�̊Ǘ��֐����[�N
 *@param	num			�o�^���鐔
 *
 *@return	none
 *
 *	���e
 *		num���I�u�W�F�N�g��o�^
 *		�J�p�Ƀ��[�N�̈��������
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherSTRain(WEATHER_SYS_WORK* pWork, int num)
{
	int i;		// ���[�v�p
	WAETHER_OBJ_DATA* add_obj;		// �o�^�I�u�W�F
	int	err;	// �␳�l
	s32* obj_w;	// �I�u�W�F�N�g���[�N
	WEATHER_SYSW_NORMAL* sys_w;	// �V�X�e�����[�N
	int speed_m;	// �X�s�[�h�ɂ�����l�e�[�u���̗v�f��
	int frame;		// �t���[����
	static const int WEATHER_STRAIN_OBJ_MUL[ WEATHER_STRAIN_OBJ_MUL_NUM ] = {100, 100, 200, 100, 300};

	sys_w = (WEATHER_SYSW_NORMAL*)pWork->work;
	
	// num���I�u�W�F�N�g��o�^
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*8);		// �o�^
		if(add_obj == NULL){			// ���s������I��
			break;
		}
		obj_w = (s32*)add_obj->work;
		
		// �̈��������
		obj_w[0] = 0;			// �J�E���^
		frame = gf_mtRand()%3;	// �J�̎��
		CLACT_AnmFrameSet( add_obj->clact_w, frame );

		obj_w[4] = WEATHER_STRAIN_SPEED_X * (frame+1);
		obj_w[2] = WEATHER_STRAIN_SPEED_Y * (frame+1);
		obj_w[4] *= WEATHER_STRAIN_OBJ_MUL[sys_w->work[2]/WEATHER_STRAIN_OBJ_MUL_CHG];
		obj_w[2] *= WEATHER_STRAIN_OBJ_MUL[sys_w->work[2]/WEATHER_STRAIN_OBJ_MUL_CHG];
		obj_w[4] /= 100;
		obj_w[2] /= 100;
		
		obj_w[3] = 0;			// �j���A�j���t���O
		
		// �j���^�C�~���O	�S�����ʂ͈̔͂̒l
		obj_w[1] = WEATHER_STRAIN_END_MIN  + (gf_mtRand() % WEATHER_STRAIN_END_MAX);
		obj_w[1] *= 100;
		obj_w[1] /= WEATHER_STRAIN_OBJ_MUL[sys_w->work[2]/WEATHER_STRAIN_OBJ_MUL_CHG];
		
		// ���W��ݒ�
		{
			VecFx32 mat = getObjMat( add_obj );
			mat.x = WEATHER_STRAIN_START_X + (gf_mtRand() % WEATHER_STRAIN_START_X_MAX);
			mat.y = WEATHER_STRAIN_START_Y + (gf_mtRand() % WEATHER_STRAIN_START_Y_MAX);
			mat.z = 0;

			mat.x <<= FX32_SHIFT;
			mat.y <<= FX32_SHIFT;
			setClactMatrix(add_obj->clact_w, &mat);
		}
		
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�J�I�u�W�F�N�g����֐�
 *
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherSTRain(WAETHER_OBJ_DATA* work)
{
	int i;
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	s32* obj_w = (s32*)p_obj->work;
	VecFx32 mat = getObjMat( p_obj );
	
	// ����t���O���`�F�b�N
	switch(obj_w[3]){
	case 0:		// ����
		// �J�̂Ƃ�����������邽��1�t���[����2��̕`����s���A�P�D�T�̈ʒu��������
		for(i=0;i<2;i++){
			// ������
			mat.x += obj_w[4] << FX32_SHIFT;
			mat.y += obj_w[2] << FX32_SHIFT;
		
			// �j�����邩�`�F�b�N
			if(obj_w[0]++ > obj_w[1]){
				// �A�j���[�V���������邩�`�F�b�N
				if((gf_mtRand() % 10) < 5){		// 7/10�͔j��
					// �j��
					obj_w[3] = 2;
				}else{
				
					// �j���A�j��
					obj_w[3] = 1;		
					obj_w[0] = 4;			// �j���A�j���J�E���^
					CLACT_AnmFrameSet(p_obj->clact_w, 3);// �j���A�j���̊G
				}
			}
			setClactMatrix(p_obj->clact_w, &mat);
		}
		break;
	case 1:		// �j���A�j��
		if(obj_w[0]-- <= 0){
			obj_w[3] = 2;		// �j��
		}
		break;

	case 2:		// �j��
		destObj(p_obj);
		break;
	}		
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�ΎR�D�Ǘ��^�X�N
 *
 *@param	tcb		�����̃^�X�N
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherVolcano(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ���[�v�p
	int		tmp_y;		// y���W�ۑ��p
	int		scl_x, scl_y;	// �X�N���[�����W
	short		sc_w_x, sc_w_y;	// �X�N���[�����[�N
	WEATHER_SYSW_NORMAL* sys_w;			// �V�X�e�����[�N
	int		result;		// �֐�����
	int		fog_result;	// �t�H�O����
	
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
	


	
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			1,	// obj�o�^��
			WEATHER_VOLCANO_TIMING_MAX,	// �o�^�^�C�~���O
			WEATHER_VOLCANO_MAIN,
			WEATHER_VOLCANO_TIMING_MIN,
			-WEATHER_VOLCANO_TIMING_ADD,
			WEATHER_VOLCANO_ADD_TIMING,
			WEATHER_VOLCANO_ADD,
			addWeatherVolcano );
		
		sys_w->work[1] = 0;						// �ΎR�D���P�񉺂܂ōs�������̃t���O
		sys_w->work[2] = 0;						// BG���W	��16bit X	��16bit Y
		sys_w->work[4] = 0;						// BG���J�E���^

		sys_w->work[5] = 0;						// �I�u�W�F�N�g�j���t���O
		
		// �t�H�O�̐ݒ�
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT + WEATHER_VOLCANO_FOG_SLOPE, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_VOLCANO_FOG_OFS, 
				GX_RGB(20,20,14),
				WEATHER_VOLCANO_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_VOLCANO_FOG_START;	// �������t�H�O�p
		
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s
		
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
			// FOG
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// �^�C�~���O���ŏ��ɂȂ����烁�C����
			if((fog_result == 1) && (result == 3)){		// �t�F�[�h���U���g�������Ȃ�΃��C����
				// �V�[�P���X�ύX
				sys_work->Sequence = WEATHER_SEQ_MAIN;
				// BGON
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
			}
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// �t�F�[�h�C���Ȃ�������
		
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_VOLCANO_MAIN,	// obj�o�^��
			WEATHER_VOLCANO_TIMING_MIN,	// �o�^�^�C�~���O
			WEATHER_VOLCANO_MAIN,
			WEATHER_VOLCANO_TIMING_MIN,
			-WEATHER_VOLCANO_TIMING_ADD,
			WEATHER_VOLCANO_ADD_TIMING,
			WEATHER_VOLCANO_ADD,
			addWeatherVolcano );
		
		sys_w->work[1] = 0;						// �ΎR�D���P�񉺂܂ōs�������̃t���O
		sys_w->work[2] = 0;						// BG���W	��16bit X	��16bit Y
		sys_w->work[4] = 0;						// BG���J�E���^
		sys_w->work[5] = 0;						// �I�u�W�F�N�g�j���t���O
		
		// �t�H�O�̐ݒ�
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// �f�[�^��ݒ�
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// �t�H�O�ۑ�����
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_VOLCANO_FOG_OFS, GX_RGB(20,20,14) );
			// �e�[�u���f�[�^���쐬���Ĕ��f
			weatherSysFogSet( &sys_w->fogFade );
		}
		

		// �I�u�W�F�N�g���U��΂�
		weatherDustObj( sys_work, addWeatherVolcano, WEATHER_VOLCANO_NOFADE_OBJ_START_NUM, WEATHER_VOLCANO_NOFADE_OBJ_START_DUST_NUM, WEATHER_VOLCANO_NOFADE_OBJ_START_DUST_MOVE, objWeatherVolcano );
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;

		// BGON
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		break;
	case WEATHER_SEQ_MAIN:		// ���C��
		
		// �J�E���^��0�����ɂȂ�����J�o�^
		if(sys_w->objFade.objAddTmg-- <= 0){

			// �ΎR�D�o�^
			addWeatherVolcano(sys_work, sys_w->objFade.objAddNum);
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// �o�^�^�C�~���O�Z�b�g	
		}
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			// �t�F�[�h�A�E�g�ݒ�
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_VOLCANO_TIMING_MAX,
					WEATHER_VOLCANO_TIMING_ADD,
					-1 );
			
			// fog
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_VOLCANO_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_VOLCANO_FOG_START_END;	// �������t�H�O�p
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��

			sys_w->work[5] = 1;						// �I�u�W�F�N�g�j���t���O
			
			// BGOFF
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g
		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s

		// �t�H�O����
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
			// �t�H�O
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
		
			if((fog_result == 1) && (result == 3)){
				// �o�^�����O�ɂȂ�����I�����邩�`�F�b�N
				// �����̊Ǘ����邠�߂��S�Ĕj�����ꂽ��I��
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					
					// �V�[�P���X�ύX
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// �������A�j���ȊO�̂Ƃ��͓���֐��𓮂���
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherVolcano);
		scrollObj(sys_work, &scl_x, &scl_y);
		drawObj(sys_work);


		// BG�X�N���[��
		sc_w_x = sys_w->work[2] >> 16;	// �X�N���[�����W���o��
		sc_w_y = sys_w->work[2] & 0xffff;
		sc_w_x += scl_x;
		sc_w_y -= scl_y*5;
		if(sc_w_x < 0){
			sc_w_x += 256;
		}else{
			if(sc_w_x >= 256){
				sc_w_x -= 256;
			}
		}
		if(sc_w_y < 0){
			sc_w_y += 2048;
		}

		// BG�ʂ̉��͈��Ԋu�ł��炷�i���炿���\���j
		sys_w->work[4]+=2;
		if(sys_w->work[4] > 60){
			sys_w->work[4] = 0;

			sc_w_x = (sc_w_x + 32) % 256;
		}
		
		// BG�ʂ��΂ߏ�ɓ�����
		sc_w_y = (sc_w_y + 2) % 2048;
		G2_SetBG2Offset(sc_w_x, -sc_w_y/5);
		sys_w->work[2] = sc_w_x << 16;	// �X�N���[�����W�i�[
		sys_w->work[2] |= sc_w_y & 0xffff;
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�ΎR�D�I�u�W�F�N�g�o�^�֐�
 *
 *@param	pWork		�o�^����I�u�W�F�̊Ǘ��֐����[�N
 *@param	num			�o�^���鐔
 *
 *@return	none
 *
 *	���e
 *		num���I�u�W�F�N�g��o�^
 *		�ΎR�D�p�Ƀ��[�N�̈��������
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherVolcano(WEATHER_SYS_WORK* pWork, int num)
{
	int i;		// ���[�v�p
	int rand;	// ����
	WAETHER_OBJ_DATA* add_obj;		// �o�^�I�u�W�F
	WEATHER_SYSW_NORMAL* sys_w;	// �V�X�e�����[�N
	int frame;	// �t���[����
	s32* obj_w;	// �I�u�W�F�N�g���[�N
	sys_w = pWork->work;


	if(sys_w->work[1] == 1){
		num *= 2;
	}
	
	// num���I�u�W�F�N�g��o�^
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*8);		// �o�^
		if(add_obj == NULL){			// ���s������I��
			break;
		}

		obj_w = (s32*)add_obj->work;
		
		frame = gf_mtRand() % WEATHER_VOLCANO_OBJ_NUM;
		CLACT_AnmFrameSet( add_obj->clact_w, frame );
		
		obj_w[4] = 10;	// ���̓��������ύX�J�E���^	
		obj_w[5] = 0;
		
		rand = gf_mtRand();
	
		// �X�s�[�h
		if((rand % 2) == 0){
			obj_w[1] = 1;
		}else{
			obj_w[1] = -1;
		}
		obj_w[3] = WEATHER_VOLCANO_ADD_TMG_Y_BASE + (gf_mtRand() % WEATHER_VOLCANO_ADD_TMG_Y_RAN);

		obj_w[0] = (s32)&sys_w->work[1];		// ���܂ōs������t���O�𗧂Ă�|�C���^��ۑ�
		obj_w[6] = (s32)&sys_w->work[5];		// �j���t���O
		obj_w[7] = WEATEHR_VOLCANO_DEL_COUNT_MIN + (gf_mtRand() % WEATEHR_VOLCANO_DEL_COUNT_MAX);					// �j������
		
		// ���W��ݒ�
		{
			VecFx32 mat = getObjMat( add_obj );
			mat.x = WEATHER_VOLCANO_START_X_BASE + (gf_mtRand() % WEATHER_VOLCANO_START_X_MAX);
		
			if((sys_w->work[1] == 1) &&
				(i >= (num /2)) ){	// �����o��
				mat.y = -40 - (gf_mtRand() % 20);
			}else{
				mat.y = -8 - (gf_mtRand() % 20);
			}
			mat.x <<= FX32_SHIFT;
			mat.y <<= FX32_SHIFT;
			mat.z = 0;

			setClactMatrix( add_obj->clact_w, &mat );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�ΎR�D����֐�
 *
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherVolcano(WAETHER_OBJ_DATA* work)
{
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	s32* obj_w = (s32*)p_obj->work;
	VecFx32 mat = getObjMat( p_obj );
	BOOL del_flg = FALSE;

	// ������
	if((obj_w[5] >= obj_w[3])){
		mat.y += FX32_ONE;
		obj_w[5] = 0;

		setClactMatrix( p_obj->clact_w, &mat );
	} 
	
	obj_w[5]++;

	mat.y >>= FX32_SHIFT;

	// �j���t���O�������Ă�����A�j��
	if( *((s32*)obj_w[6]) == 1 ){

		// �j�������������Ȃ�����j��
		obj_w[7] --;
		if( obj_w[7] <= 0 ){
			del_flg = TRUE;
		}
	}
	
	// �j���]�[���ɂ�����j��  
	if(((mat.y < -284) && (mat.y > -296)) ||
		((mat.y > 212) && (mat.y < 232))){
		del_flg = TRUE;
	}

	if( del_flg == TRUE ){
		*((s32*)obj_w[0]) = 1;
		destObj(p_obj);
		return ;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���Ǘ��^�X�N
 *
 *@param	tcb		�����̃^�X�N
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherSpark(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	s32* sys_w;			// �V�X�e�����[�N
	int	num;
	int rand;
	
	sys_w = (s32*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
	

	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
	case WEATHER_SEQ_NO_FADE:	// �t�F�[�h�C���Ȃ�������
		
		// ��Ɨ̈�̏�����
		sys_w[0] = 0;		// ���C�g�t�F�[�h�J�E���^
		sys_w[4] = 0;
		sys_w[1] = 0;
		WeatherBGAlphaDef(0,31);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		

		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// ���C��
		if(sys_w[4] >= 0){
			sys_w[4]--;
		}else{
			switch(sys_w[1]){
			case 0:
				sys_w[1] = 1;		// ���C�g�t�F�[�h��
				sys_w[5] = 0;
				sys_w[6] = WEATHER_SPARK_POWER_MIN+(gf_mtRand() % WEATHER_SPARK_POWER_RAN);	// ���̑��₷�l�����߂�
				sys_w[7] = 0;		// ���̃A���t�@

				// �_�ł̗��ɂ��邩�@���������ɂ��邩�`�F�b�N
				if((gf_mtRand()%3) != 0){
					sys_w[2] = WEATHER_SPARK_SUB_NUM;

					// ���뗋
					Snd_SePlay( SEQ_SE_DP_T_KAMI2 );
				}else{
					sys_w[2] = WEATHER_SPARK_SUB_NUM_HIGH;

					// �s�J��
					Snd_SePlay( SEQ_SE_DP_T_KAMI );
				}
				break;
			case 1:
				sys_w[5]++;
				sys_w[7] += sys_w[6];	
				if(sys_w[5] >= WEATHER_SPARK_NUM){	// �I���`�F�b�N
					sys_w[1] = 2;		// �Â�����
				}
				WeatherBGAlphaDef(sys_w[7]/100,31);
				break;
			case 2:
				sys_w[7] -= sys_w[2];	
				if(sys_w[7] <= 0){	// �I���`�F�b�N
					sys_w[1] = 0;
					sys_w[7] = 0;

					// ���̗��܂ł̃J�E���^��ݒ�
					// ������̂������Ƃ��͂�����x�o��
					if(sys_w[2] == WEATHER_SPARK_SUB_NUM_HIGH){
						sys_w[4] = (gf_mtRand() % WEATHER_SPARK_SPARK_RAN_HIGH);
					}else{
						sys_w[4] = ((sys_w[6] * WEATHER_SPARK_SPARK_MUL)/100) + (gf_mtRand()%WEATHER_SPARK_SPARK_RAN);
					}
				}
				WeatherBGAlphaDef(sys_w[7]/100,31);
				break;
			}
		}
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
				
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g
		
		sys_work->Sequence = WEATHER_SEQ_DEST;
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�C���Ǘ��^�X�N
 *
 *@param	tcb		�����̃^�X�N
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherSpirit(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ���[�v�p
	WEATHER_SYSW_OBJFADE* sys_w;			// �V�X�e�����[�N
	int		result;		// �֐�����
	
	sys_w = (WEATHER_SYSW_OBJFADE*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
	

			
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			1,	// obj�o�^��
			WEATHER_SPIRIT_TIMING_MAX,	// �o�^�^�C�~���O
			WEATHER_SPIRIT_MAIN,
			WEATHER_SPIRIT_TIMING_MIN,
			-WEATHER_SPIRIT_TIMING_ADD,
			WEATHER_SPIRIT_ADD_TIMING,
			WEATHER_SPIRIT_ADD,
			addWeatherSpirit );
		
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s
		
		// �^�C�~���O���ŏ��ɂȂ����烁�C����
		if(result == 3){		// �t�F�[�h���U���g�������Ȃ�΃��C����
			// �V�[�P���X�ύX
			sys_work->Sequence = WEATHER_SEQ_MAIN;
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// �t�F�[�h�C���Ȃ�������
		
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			1,	// obj�o�^��
			WEATHER_SPIRIT_MAIN,	// obj�o�^��
			WEATHER_SPIRIT_TIMING_MIN,	// �o�^�^�C�~���O
			WEATHER_SPIRIT_TIMING_MIN,
			-WEATHER_SPIRIT_TIMING_ADD,
			WEATHER_SPIRIT_ADD_TIMING,
			WEATHER_SPIRIT_ADD,
			addWeatherSpirit );

		// �I�u�W�F�N�g���U��΂�
		weatherDustObj( sys_work, addWeatherSpirit, WEATHER_SPIRIT_NOFADE_OBJ_START_NUM, WEATHER_SPIRIT_NOFADE_OBJ_START_DUST_NUM, WEATHER_SPIRIT_NOFADE_OBJ_START_DUST_MOVE, objWeatherSpirit );
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// ���C��
		
		// �J�E���^��0�����ɂȂ�����o�^
		if(sys_w->objFade.objAddTmg-- <= 0){

			// ��o�^
			addWeatherSpirit(sys_work, sys_w->objFade.objAddNum);
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// �o�^�^�C�~���O�Z�b�g	
		}
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			// �t�F�[�h�A�E�g�ݒ�
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_SPIRIT_TIMING_MAX,
					WEATHER_SPIRIT_TIMING_ADD,
					WEATHER_SPIRIT_ADD_END );
			
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}

		break;
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g
		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s

		if(result == 3){
			// �o�^�����O�ɂȂ�����I�����邩�`�F�b�N
			// �����̊Ǘ����邠�߂��S�Ĕj�����ꂽ��I��
			if(sys_work->Dummy.pNext == &sys_work->Dummy){
				
				// �V�[�P���X�ύX
				sys_work->Sequence = WEATHER_SEQ_DEST;
			
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// �������A�j���ȊO�̂Ƃ��͓���֐��𓮂���
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherSpirit);
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�C���I�u�W�F�N�g�o�^�֐�
 *
 *@param	pWork		�o�^����I�u�W�F�̊Ǘ��֐����[�N
 *@param	num			�o�^���鐔
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherSpirit(WEATHER_SYS_WORK* pWork, int num)
{
	int i;			// ���[�v�p
	WAETHER_OBJ_DATA* add_obj;		// �o�^�I�u�W�F
	s32* obj_w;		// �I�u�W�F�N�g���[�N
	int obj_num;	// �I�u�W�F�N�g��
	int frame;		// �t���[����
	VecFx32 mat;	// ���W

		
	// num���I�u�W�F�N�g��o�^
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*8);		// �o�^
		if(add_obj == NULL){			// ���s������I��
			break;
		}

		obj_w = (s32*)add_obj->work;

		// ��ނ����߂�
		frame = gf_mtRand() % WEATHER_SPIRIT_OBJ_NUM;
		CLACT_AnmFrameSet( add_obj->clact_w, frame );

		// ��ނ������J�E���^�A�����l�����߂�
		obj_num = frame / WEATHER_SPIRIT_BIG_DIV;	// �I�u�W�F�̑傫��idx
		obj_num++;	// 0->1�ɂ���
		obj_w[0] = WEATHER_SPIRIT_SHIFT_UP+(gf_mtRand()%WEATHER_SPIRIT_SHIFT_UP_RAN);	// �͉���J�E���^
		obj_w[0] *= obj_num;
		obj_w[1] = WEATHER_SPIRIT_ADD_SPEED / obj_num;	// �����l//*/
		obj_w[2] = 0;									// ���̑��x

		// �����݂ɉ��ɓ���
		obj_w[3] = gf_mtRand() % 2;		// 0:�E	1:��
		obj_w[4] = WEATHER_SPIRIT_S_MOVE_TMG;	// ����^�C�~���O

		
		// ���W
		switch(obj_num){
		case 1:
		case 2:
				
			mat.x = WEATHER_SPIRIT_MAT_X_MIN + (gf_mtRand() % WEATHER_SPIRIT_MAT_X_RAN);
			mat.y = WEATHER_SPIRIT_MAT_Y_S_MIN + (gf_mtRand() % WEATHER_SPIRIT_MAT_Y_S_RAN);
			break;
		case 3:
			mat.x = WEATHER_SPIRIT_MAT_X_MIN + (gf_mtRand() % WEATHER_SPIRIT_MAT_X_RAN);
			mat.y = WEATHER_SPIRIT_MAT_Y_M_MIN + (gf_mtRand() % WEATHER_SPIRIT_MAT_Y_M_RAN);
			break;
		case 4:
			mat.x = WEATHER_SPIRIT_MAT_X_MIN + (gf_mtRand() % WEATHER_SPIRIT_MAT_X_RAN);
			mat.y = WEATHER_SPIRIT_MAT_Y_L_MIN + (gf_mtRand() % WEATHER_SPIRIT_MAT_Y_L_RAN);
			break;
		}
		mat.z = 0;
		mat.x <<= FX32_SHIFT;
		mat.y <<= FX32_SHIFT;
		setClactMatrix( add_obj->clact_w, &mat );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�C������֐�
 *
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherSpirit(WAETHER_OBJ_DATA* work)
{
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	s32* obj_w = (s32*)p_obj->work;
	VecFx32 mat = getObjMat( p_obj );

	// �������Ȃ���ړ�
	obj_w[2] += obj_w[1];
	if(obj_w[0] > 0){
		obj_w[0]--;		// �͉���J�E���g	0�ɂȂ����瑬�x���Q

		mat.y -= (obj_w[2]/100) << FX32_SHIFT;
	}else{
		mat.y -= (obj_w[2]/50) << FX32_SHIFT;
	}

	// �����݂ɗh���
	obj_w[4]--;
	if(obj_w[4] <= 0){
		obj_w[4] = WEATHER_SPIRIT_S_MOVE_TMG;

		if(obj_w[3] == 0){
			mat.x += WEATHER_SPIRIT_S_MOVE_NUM << FX32_SHIFT;
			obj_w[3] = 1;
		}else{
			mat.x -= WEATHER_SPIRIT_S_MOVE_NUM << FX32_SHIFT;
			obj_w[3] = 0;
		}
	}

	setClactMatrix( p_obj->clact_w, &mat );
	

	//�@��܂ōs������I���
	if( (mat.y >> FX32_SHIFT) <= -16){
		destObj(p_obj);
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�_��Ǘ��^�X�N
 *
 *@param	tcb		�����̃^�X�N
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherMystic(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	WEATHER_KIRI_HARAI_WORK* sys_w;			// �V�X�e�����[�N
	BOOL result;
	BOOL fog_result;
	sys_w = (WEATHER_KIRI_HARAI_WORK*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
	
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		WeatherMoveReq( &sys_w->alpha, 0, WEATHER_MYSTIC_FADE_END_ALPHA, WEATHER_MYSTIC_FADE_COUNT_MAX );
		WeatherBGAlphaDef(0, 16);

		// �\���D�揇�ʕύX
		G2_SetBG2Priority(3);
		
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );

/*
		// �t�H�O�̐ݒ�
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_MYSTIC_FOG_SLOPE, 
				WEATHER_MYSTIC_FOG_OFS, 
				GX_RGB(0,0,0),
				WEATHER_MYSTIC_FOG_TIMING,
				sys_work->fog_use );
//*/		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��

//		fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
		fog_result = TRUE;

		result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);

		if( (result == TRUE) && (fog_result == TRUE) ){
			// �V�[�P���X�ύX
			sys_work->Sequence = WEATHER_SEQ_MAIN;
		}
		break;

	case WEATHER_SEQ_NO_FADE:	// �t�F�[�h�C���Ȃ�������

		WeatherBGAlphaDef(WEATHER_MYSTIC_FADE_END_ALPHA, 16 - WEATHER_MYSTIC_FADE_END_ALPHA);

		// �\���D�揇�ʕύX
		G2_SetBG2Priority(3);
		
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );


		// �t�H�O�̐ݒ�
/*		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// �f�[�^��ݒ�
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// �t�H�O�ۑ�����
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_MYSTIC_FOG_SLOPE, WEATHER_MYSTIC_FOG_OFS, GX_RGB(0,0,0) );
			// �e�[�u���f�[�^���쐬���Ĕ��f
			weatherSysFogSet( &sys_w->fogFade );
		}//*/
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	
	case WEATHER_SEQ_MAIN:		// ���C��
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			WeatherMoveReq( &sys_w->alpha, WEATHER_MYSTIC_FADE_END_ALPHA, 0, WEATHER_MYSTIC_FADE_COUNT_MAX );

			// fog
/*			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_MYSTIC_FOG_TIMING_END, FALSE );
			}//*/
			
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}
		break;
	
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g
		result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);

/*		if(sys_work->fog_use != WEATHER_FOG_NONE){
			fog_result = weatherSysFogFade(&sys_w->fogFade);
		}else{
			fog_result = 1;
		}//*/
		fog_result = TRUE;

		if( (result == TRUE) && (fog_result == TRUE) ){
			// �V�[�P���X�ύX
			sys_work->Sequence = WEATHER_SEQ_DEST;
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
/*		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
		}//*/
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}	
		break;

	default:
		break;
	}

#if 0
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ���[�v�p
	WEATHER_SYSW_NORMAL* sys_w;			// �V�X�e�����[�N
	int		result;		// �֐�����
	int		fog_result;	// �t�H�O����
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
		

		
	
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		
		
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_MYSTIC_ADD_START,	// obj�o�^��
			WEATHER_MYSTIC_TIMING_MAX,	// �o�^�^�C�~���O
			WEATHER_MYSTIC_ADD_MAIN,
			WEATHER_MYSTIC_TIMING_MIN,
			-WEATHER_MYSTIC_TIMING_ADD,
			WEATHER_MYSTIC_ADD_TIMING,
			WEATHER_MYSTIC_ADD,
			addWeatherMystic );
		
		// �t�H�O�̐ݒ�
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_MYSTIC_FOG_OFS, 
				GX_RGB(31,31,31),
				WEATHER_MYSTIC_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_MYSTIC_FOG_START;	// �������t�H�O�p
		
		sys_w->work[1] = 0;			// �I�u�W�F�N�g�ǉ����J�E���^
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s
		
		
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// �^�C�~���O���ŏ��ɂȂ����烁�C����
			if((fog_result == 1) && (result == 3)){		// �t�F�[�h���U���g�������Ȃ�΃��C����
				// �V�[�P���X�ύX
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// �t�F�[�h�C���Ȃ�������
		
		
		// ��Ɨ̈�̏�����
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_MYSTIC_ADD_MAIN,	// obj�o�^��
			WEATHER_MYSTIC_TIMING_MIN,	// �o�^�^�C�~���O
			WEATHER_MYSTIC_ADD_MAIN,
			WEATHER_MYSTIC_TIMING_MIN,
			-WEATHER_MYSTIC_TIMING_ADD,
			WEATHER_MYSTIC_ADD_TIMING,
			WEATHER_MYSTIC_ADD,
			addWeatherMystic );
		
		// �t�H�O�̐ݒ�
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// �f�[�^��ݒ�
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// �t�H�O�ۑ�����
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_MYSTIC_FOG_OFS, GX_RGB(31,31,31) );
			// �e�[�u���f�[�^���쐬���Ĕ��f
			weatherSysFogSet( &sys_w->fogFade );
		}
		
		sys_w->work[1] = 0;			// �I�u�W�F�N�g�ǉ����J�E���^

		// �I�u�W�F�N�g���U��΂�
		weatherDustObj( sys_work, addWeatherMystic, WEATHER_MYSTIC_NOFADE_OBJ_START_NUM, WEATHER_MYSTIC_NOFADE_OBJ_START_DUST_NUM, WEATHER_MYSTIC_NOFADE_OBJ_START_DUST_MOVE, objWeatherMystic );
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// ���C��
		
		// �J�E���^��0�����ɂȂ�����J�o�^
		if(sys_w->objFade.objAddTmg-- <= 0){

			// �_��o�^
			addWeatherMystic(sys_work, sys_w->objFade.objAddNum);
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// �o�^�^�C�~���O�Z�b�g	
		}
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			// �t�F�[�h�A�E�g�ݒ�
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_MYSTIC_TIMING_MAX,
					WEATHER_MYSTIC_TIMING_ADD,
					-WEATHER_MYSTIC_ADD_END );
			
			// fog
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_MYSTIC_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_MYSTIC_FOG_START_END;	// �������t�H�O�p
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g

		// �I�u�W�F�N�g�t�F�[�h
		result = weatherSysObjFade(&sys_w->objFade);	// ���s
		
		// �t�H�O����
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ���[�N6���O�ɂȂ�����t�H�O�𓮂���
		}else{
		
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
		
			if((fog_result == 1) && (result == 3)){
				// �o�^�����O�ɂȂ�����I�����邩�`�F�b�N
				// �����̊Ǘ����邠�߂��S�Ĕj�����ꂽ��I��
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					
					// �V�[�P���X�ύX
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// �������A�j���ȊO�̂Ƃ��͓���֐��𓮂���
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherMystic);
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);
	}
#endif
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *@brief	�_��I�u�W�F�N�g�o�^�֐�
 *
 *@param	pWork		�o�^����I�u�W�F�̊Ǘ��֐����[�N
 *@param	num			�o�^���鐔
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherMystic(WEATHER_SYS_WORK* pWork, int num)
{
	int i;			// ���[�v�p
	WAETHER_OBJ_DATA* add_obj;		// �o�^�I�u�W�F
	s32* obj_w;		// �I�u�W�F�N�g���[�N
	int obj_num;	// �I�u�W�F�N�g�̑傫�������Ă��悤
	int ch_num;		// �I�u�W�F�N�g�̑傫�������Ă��悤
	int frame;		// �t���[����
	VecFx32 mat;	// ���W
	
	
	// num���I�u�W�F�N�g��o�^
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*10);		// �o�^
		if(add_obj == NULL){			// ���s������I��
			break;
		}

		obj_w = (s32*)add_obj->work;
		// �傫�������߂�
		obj_num = gf_mtRand()%WEATHER_MYSTIC_RAN;
		ch_num = 0;
		for(i=0;i<WEATHER_MYSTIC_NUM;i++){
			switch(i){
			case 0:
				ch_num += WEATHER_MYSTIC_RAN_0;
				break;
			case 1:
				ch_num += WEATHER_MYSTIC_RAN_1;
				break;
			case 2:
				ch_num += WEATHER_MYSTIC_RAN_2;
				break;
			case 3:
				ch_num += WEATHER_MYSTIC_RAN_3;
				break;
			}
			
			if(obj_num < ch_num){
				frame = i;
				break;
			}	
		}
		CLACT_AnmFrameSet( add_obj->clact_w, frame );
	 	
		// �j���J�E���^������
		obj_w[0] = WEATHER_MYSTIC_DES_TM+(gf_mtRand()%WEATHER_MYSTIC_DES_RAN);
		
		// �X�s�[�h�����߂�
		obj_w[2] = WEATHER_MYSTIC_M_Y + (WEATHER_MYSTIC_M_Y_MUL*frame);

		// �t���ړ��i���V�������R�ɔ��ł���悤�Ɍ����邽�߁Asin.cos�œ������j
		obj_w[4] = gf_mtRand() % 360;
		obj_w[5] = gf_mtRand() % 360;
		obj_w[6] = gf_mtRand() % WEATHER_MYSTIC_MH_X;
		obj_w[7] = gf_mtRand() % WEATHER_MYSTIC_MH_Y;
		obj_w[8] = WEATHER_MYSTIC_MH_COUNT + (gf_mtRand() % WEATHER_MYSTIC_MH_COUNT_RAN);
		
		// ���W�����߂�
		obj_w[1] = 0;
		obj_w[3] = 0;
		mat.x = WEATHER_MYSTIC_MAT_X+(gf_mtRand()%WEAHTER_MYSTIC_MAT_X_RAN);	// X���W
		mat.y = WEAHTER_MYSTIC_MAT_Y+(WEATHER_MYSTIC_MAT_Y_MUL*frame);
		mat.y += (gf_mtRand()%WEAHTER_MYSTIC_MAT_Y_RAN);
		mat.z = 0;
		mat.x <<= FX32_SHIFT;
		mat.y <<= FX32_SHIFT;

		setClactMatrix( add_obj->clact_w, &mat );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�_�铮��֐�
 *
 *@param	work	���[�N�̈�
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherMystic(WAETHER_OBJ_DATA* work)
{
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	s32* obj_w = (s32*)p_obj->work;
	int hm_num;		// �⏕�ړ��l
	fx32 hm_par;	// �ړ��␳�l�̒l�ɂ�����l
	int sc_ch;		// �X�N���[�������p
	VecFx32 mat = getObjMat( p_obj );

	mat.x >>= FX32_SHIFT;
	mat.y >>= FX32_SHIFT;

	// �X�N���[���`�F�b�N	�X�N���[�������œ��������W���e�������W�ɂ���
	sc_ch = obj_w[1] % 100;
	obj_w[1] = mat.y * 100;
	obj_w[1] += sc_ch;
	sc_ch = obj_w[3] % 100;
	obj_w[3] = mat.x * 100;
	obj_w[3] += sc_ch;
	
	// �ړ�
	obj_w[1] -= obj_w[2];
	
	// �⏕�ړ�
	hm_par = FX_SinIdx(obj_w[4]*182);
	hm_num = FX_Mul(hm_par, obj_w[6]<<FX32_SHIFT) >> FX32_SHIFT;
	obj_w[3] += hm_num;		// X���W�␳
	hm_par = FX_SinIdx(obj_w[5]*182);
	hm_num = FX_Mul(hm_par, obj_w[7]<<FX32_SHIFT) >> FX32_SHIFT;
	obj_w[1] += hm_num;		// Y���W�␳
	obj_w[4] = (obj_w[4]+obj_w[8]) % 360;	// �p�x�ύX
	obj_w[5] = (obj_w[5]+obj_w[8]) % 360;	// �p�x�ύX
	
	// ���W��ݒ�
	mat.y = obj_w[1]/100;
	mat.x = obj_w[3]/100;


	mat.x <<= FX32_SHIFT;
	mat.y <<= FX32_SHIFT;
	setClactMatrix( p_obj->clact_w, &mat );
	
	// �j��
	if(obj_w[0] <= 0){
		destObj(p_obj);
	}else{
		obj_w[0]--;
	}

}
#endif

//----------------------------------------------------------------------------
/**
 *	@brief	�܂�@�R���g���[���֐�
 *
 *	@param	tcb		TCB���[�N
 *	@param	work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void contWeatherCloudiness(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	WEATHER_CLOUDINESS_WORK* sys_w;			// �V�X�e�����[�N
	BOOL result;
	sys_w = (WEATHER_CLOUDINESS_WORK*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
	
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		WeatherMoveReq( &sys_w->alpha, 0, WEATHER_CLOUDINESS_FADE_END_ALPHA, WEATHER_CLOUDINESS_FADE_COUNT_MAX );
		WeatherBGAlphaDef(0, 16);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��

		result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);

		if( result ){
			// �V�[�P���X�ύX
			sys_work->Sequence = WEATHER_SEQ_MAIN;
		}
		break;

	case WEATHER_SEQ_NO_FADE:	// �t�F�[�h�C���Ȃ�������

		WeatherBGAlphaDef(WEATHER_CLOUDINESS_FADE_END_ALPHA, 16 - WEATHER_CLOUDINESS_FADE_END_ALPHA);

		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	
	case WEATHER_SEQ_MAIN:		// ���C��
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			WeatherMoveReq( &sys_w->alpha, WEATHER_CLOUDINESS_FADE_END_ALPHA, 0, WEATHER_CLOUDINESS_FADE_COUNT_MAX );
			
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}
		break;
	
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g
		result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);

		if( result ){
			// �V�[�P���X�ύX
			sys_work->Sequence = WEATHER_SEQ_DEST;
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}	
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	������
 *
 *	@param	tcb
 *	@param	work
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void contWeatherKiriHarai(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	WEATHER_KIRI_HARAI_WORK* sys_w;	// �V�X�e�����[�N
	int		fog_result;	// �t�H�O����
	BOOL	alpha_result;
	sys_w = (WEATHER_KIRI_HARAI_WORK*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
	
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		// �t�H�O�̐ݒ�
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_KIRI_HARAI_FOG_SLOPE, 
				WEATHER_KIRI_HARAI_FOG_OFS, 
				WEATHER_KIRI_HARAI_FOG_COLOR,
				WEATHER_KIRI_HARAI_FOG_TIMING,
				sys_work->fog_use );

		WeatherMoveReq( &sys_w->alpha, 0, WEATHER_KIRI_HARAI_FADE_END_ALPHA, WEATHER_KIRI_HARAI_FADE_COUNT_MAX );
		WeatherBGAlphaDef(0, 16);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );

		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		
		fog_result = weatherSysFogFade(&sys_w->fogFade);

		alpha_result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);
		
		// �^�C�~���O���ŏ��ɂȂ����烁�C����
		if((fog_result == 1) && (alpha_result == TRUE)){		// �t�F�[�h���U���g�������Ȃ�΃��C����
			// �V�[�P���X�ύX
			sys_work->Sequence = WEATHER_SEQ_MAIN;
		}
		break;
	case WEATHER_SEQ_NO_FADE:
		// �t�H�O�̐ݒ�
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// �f�[�^��ݒ�
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// �t�H�O�ۑ�����
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_KIRI_HARAI_FOG_SLOPE, WEATHER_KIRI_HARAI_FOG_OFS, WEATHER_KIRI_HARAI_FOG_COLOR );

			// �e�[�u���f�[�^���쐬���Ĕ��f
			weatherSysFogSet( &sys_w->fogFade );
		}

		WeatherBGAlphaDef(WEATHER_KIRI_HARAI_FADE_END_ALPHA, 16 - WEATHER_KIRI_HARAI_FADE_END_ALPHA);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// ���C��
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_KIRI_HARAI_FOG_TIMING_END, FALSE );
			}

			WeatherMoveReq( &sys_w->alpha, WEATHER_KIRI_HARAI_FADE_END_ALPHA, 0, WEATHER_KIRI_HARAI_FADE_COUNT_MAX );
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}
		break;
		
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g

		if(sys_work->fog_use != WEATHER_FOG_NONE){
			fog_result = weatherSysFogFade(&sys_w->fogFade);
		}else{
			fog_result = 1;
		}

		alpha_result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);
		
		// �^�C�~���O���ŏ��ɂȂ����烁�C����
		if((fog_result == 1) && (alpha_result == TRUE)){		// �t�F�[�h���U���g�������Ȃ�ΏI����
			// �V�[�P���X�ύX
			sys_work->Sequence = WEATHER_SEQ_DEST;
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	������	����
 *
 *	@param	tcb
 *	@param	work
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void contWeatherKiriHarai_White(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	WEATHER_KIRI_HARAI_WORK* sys_w;	// �V�X�e�����[�N
	int		fog_result;	// �t�H�O����
	BOOL	alpha_result;
	sys_w = (WEATHER_KIRI_HARAI_WORK*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
	
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		// �t�H�O�̐ݒ�
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_KIRI_HARAI_WHITE_FOG_SLOPE, 
				WEATHER_KIRI_HARAI_WHITE_FOG_OFS, 
				WEATHER_KIRI_HARAI_WHITE_FOG_COLOR,
				WEATHER_KIRI_HARAI_WHITE_FOG_TIMING,
				sys_work->fog_use );

		WeatherMoveReq( &sys_w->alpha, 0, WEATHER_KIRI_HARAI_WHITE_FADE_END_ALPHA, WEATHER_KIRI_HARAI_WHITE_FADE_COUNT_MAX );
		WeatherBGAlphaDef(0, 16);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );

		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		
		fog_result = weatherSysFogFade(&sys_w->fogFade);

		alpha_result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);
		
		// �^�C�~���O���ŏ��ɂȂ����烁�C����
		if((fog_result == 1) && (alpha_result == TRUE)){		// �t�F�[�h���U���g�������Ȃ�΃��C����
			// �V�[�P���X�ύX
			sys_work->Sequence = WEATHER_SEQ_MAIN;
		}
		break;
	case WEATHER_SEQ_NO_FADE:
		// �t�H�O�̐ݒ�
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// �f�[�^��ݒ�
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// �t�H�O�ۑ�����
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_KIRI_HARAI_WHITE_FOG_SLOPE, WEATHER_KIRI_HARAI_WHITE_FOG_OFS, WEATHER_KIRI_HARAI_WHITE_FOG_COLOR );

			// �e�[�u���f�[�^���쐬���Ĕ��f
			weatherSysFogSet( &sys_w->fogFade );
		}

		WeatherBGAlphaDef(WEATHER_KIRI_HARAI_WHITE_FADE_END_ALPHA, 16 - WEATHER_KIRI_HARAI_WHITE_FADE_END_ALPHA);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// ���C��
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_KIRI_HARAI_WHITE_FOG_TIMING_END, FALSE );
			}

			WeatherMoveReq( &sys_w->alpha, WEATHER_KIRI_HARAI_WHITE_FADE_END_ALPHA, 0, WEATHER_KIRI_HARAI_WHITE_FADE_COUNT_MAX );
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}
		break;
		
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g

		if(sys_work->fog_use != WEATHER_FOG_NONE){
			fog_result = weatherSysFogFade(&sys_w->fogFade);
		}else{
			fog_result = 1;
		}

		alpha_result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);
		
		// �^�C�~���O���ŏ��ɂȂ����烁�C����
		if((fog_result == 1) && (alpha_result == TRUE)){		// �t�F�[�h���U���g�������Ȃ�ΏI����
			// �V�[�P���X�ύX
			sys_work->Sequence = WEATHER_SEQ_DEST;
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// �t�H�O���I�t
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�C�t���b�V��
 *
 *	@param	tcb		�^�X�N���[�N
 *	@param	work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void contWeatherFlash(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	WEATHER_FLASH_WORK* sys_w;	// �V�X�e�����[�N
	WEATHER_SYS_CONTROL* sys_cont = sys_work->pWSysCont;
	FIELDSYS_WORK* fsys = sys_cont->fsys;
	sys_w = (WEATHER_FLASH_WORK*)sys_work->work;	// ���[�N�|�C���^�Z�b�g
	
	// �V�[�P���X�`�F�b�N
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// ����������
		// �t���b�V��
		drawWeatherCircleInit( &sys_w->circle, fsys->fldmap->hblanksys );
		drawWeatherCircleStart( &sys_w->circle, WEATHER_FLASH_END_R, WEATHER_FLASH_START_R, WEATHER_FLASH_CX, WEATHER_FLASH_CY, WEATHER_FLASH_SYNC );
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// �t�F�[�h�C��
		if( drawWeatherCircleMain( &sys_w->circle ) == TRUE ){	

			// BG�\��
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );


			// H�u�����N�����j��
			drawWeatherCircleEndReq( &sys_w->circle );
			
			// �V�[�P���X�ύX
			sys_work->Sequence = WEATHER_SEQ_MAIN;	
		}
		break;

	case WEATHER_SEQ_NO_FADE:
		// BG�\��
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		
		// �V�[�P���X�ύX
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;

	case WEATHER_SEQ_MAIN:		// ���C��
		// �I���`�F�b�N
		if(sys_work->ContFlag == WEATHER_SYS_END){
			drawWeatherCircleInit( &sys_w->circle, fsys->fldmap->hblanksys );
			drawWeatherCircleStart( &sys_w->circle, WEATHER_FLASH_START_R, WEATHER_FLASH_END_R, WEATHER_FLASH_CX, WEATHER_FLASH_CY, WEATHER_FLASH_SYNC );

			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// ����I��
		}
		break;
		
	case WEATHER_SEQ_FADEOUT:	// �t�F�[�h�A�E�g

		// ���t���[��OFF���Ă��邱�ƂɂȂ邪�A
		// �������Ȃ��Ə�̊֐���H�u�����N�ݒ肷��u�ԕςȂ��̂��o�Ă��܂�
		// BGOFF
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		

		if( drawWeatherCircleMain( &sys_w->circle ) == TRUE ){	
			// �V�[�P���X�ύX
			sys_work->Sequence = WEATHER_SEQ_DEST;
		}
		break;

	case WEATHER_SEQ_DEST:		// �^�X�N�j��
		drawWeatherCircleEnd( &sys_w->circle );
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�v����T�E���h�Đ�
 *
 *	@param	p_work
 *	@param	snd_no 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void WeatherLoopSndPlay( WEATHER_SYS_WORK* p_work, int snd_no )
{
	// �����Ȃ��Ă��I
	GF_ASSERT( p_work->snd_play == FALSE );
	p_work->snd_play = TRUE;
	p_work->snd_no = snd_no;

	Snd_SePlay( snd_no );	
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�v�Đ�SE��~����
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void WeatherLoopSndStop( WEATHER_SYS_WORK* p_work )
{
	Snd_SeStopBySeqNo( p_work->snd_no, WEATHER_SND_FADE_OUT_SYNC );
	p_work->snd_play = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	circle�v�Z
 *
 *	@param	p_circle	circle���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void CalcWeatherCircle( WEATHER_CIRCLE_WORK* p_circle )
{
	int i;			// ���[�v�p
	int st;			// �E�B���h�E�J�n�_
	int ed;			// �E�B���h�E�I���_
	u16* p_start_buff;
	u16* p_end_buff;

	// �J�n�ʒu�i�[��
	p_start_buff = LASTER_GetWriteBuff( p_circle->p_laster[0] );
	p_end_buff = LASTER_GetWriteBuff( p_circle->p_laster[1] );

	// ���a����ʓ��ɂ���Ƃ���
	// ���S�܂ŕ������߂��牺�����̓R�s�[����悤�ɂ���
	for(i=0;i < 192;i++){
		if(i <= p_circle->y){		// ���a�܂ł͕��ʂ̋��߂�
			CalcWeatherCircleSub(p_circle->r.x, p_circle->x, p_circle->y, i, &st, &ed);
		}else{
			if(i <= (p_circle->y*2)){		// ���a���甼�a�̂Q�{�܂ł�,�R�s�[
				st = p_start_buff[(p_circle->y*2)-i];
				ed = p_end_buff[(p_circle->y*2)-i];
			}else{				// ���̑��͕��ʂɋ��߂�
				CalcWeatherCircleSub(p_circle->r.x, p_circle->x, p_circle->y, i, &st, &ed);
			}
		}
		
		p_start_buff[i] = st;
		p_end_buff[i] = ed;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�~�̕��v�Z
 *
 *	@param	c_r		���a
 *	@param	c_x		���S�����W
 *	@param	c_y		���S�����W
 *	@param	n_h		���݂̍���
 *	@param	st		���J�n�_�i�[��
 *	@param	ed		���I���_�i�[��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void CalcWeatherCircleSub( fx32 c_r, int c_x, int c_y, int n_h, int* st, int* ed )
{
	fx32 r;			// ���a
	fx32 height;	// ����
	fx32 width;		// ��

	r = c_r;

	height = n_h - c_y;
	if(height < 0){
		height = -height;
	}
	
	if(height >= r){
		*st = 0;
		*ed = 0;
	}else{
		// ���a���畝�����߂�
		height <<= FX32_SHIFT;
		width = FX_Sqrt(FX_Mul(r,r) - FX_Mul(height,height));
		width >>= FX32_SHIFT;

		// �E�B���h�E�̊J�n�_��ݒ�
		*st = c_x - width;
		if(*st < 0){
			*st = 0;
		}
		*ed = *st + (width*2);
		if(*ed > 255){
			*ed = 255;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�C�@�~�`��V�X�e��
 *	
 *	@param	p_circle		���[�N
 *	@param	p_fldhblksys	H�u�����N�V�X�e��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void drawWeatherCircleInit( WEATHER_CIRCLE_WORK* p_circle, FIELD_HBLANK_SYS* p_fldhblksys )
{
	int i;
	
	// ���[�N������
	// H�u�����N�^�X�N
	// V�u�����N�^�X�N�o�^
	memset( p_circle, 0, sizeof(WEATHER_CIRCLE_WORK) );	

	p_circle->p_laster[0] = LASTER_Init( USE_HEAPID, p_circle->wnd_data[0], p_circle->wnd_data[1] );
	p_circle->p_laster[1] = LASTER_Init( USE_HEAPID, p_circle->wnd_data[2], p_circle->wnd_data[3] );
	for( i=0; i<192; i++ ){
		p_circle->wnd_data[2][i] = 255;
		p_circle->wnd_data[3][i] = 255;
	}

/*	
	// �w�i��
	{
		u16 color = 0;
		GX_LoadBGPltt( &color, 0, 32 );
	}
//*/	

	// ��ʂɉ����o�Ȃ��悤��VBlank���Ԓ���H�u�����N�֐���o�^����
	p_circle->p_fldhblksys = p_fldhblksys;
	VWaitTCB_Add( drawWeatherCircleInitHblankTcb, p_circle, WEATHER_TCB_CIRCLEINIT_PRI );
	
	p_circle->vblank_tcb = VWaitTCB_Add( drawWeatherCircleVblankCall, p_circle, WEATHER_CIRCLE_VBLANKTCB_PRI );
	
	p_circle->status = WEATHER_CIRCLE_STATUS_INIT;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�~�g�I��
 *
 *	@param	p_circle	�~���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void drawWeatherCircleEnd( WEATHER_CIRCLE_WORK* p_circle )
{
	int visi = GX_GetVisibleWnd();
	// �E�B���h�E�j��
	GX_SetVisibleWnd( visi & (~GX_WNDMASK_W1) );
	
	// h�u�����N�j��
	FLDHBLANK_OBJ_Delete( p_circle->p_hblank );
	// V�u�����N
	TCB_Delete( p_circle->vblank_tcb );

	LASTER_Delete( p_circle->p_laster[0] );
	LASTER_Delete( p_circle->p_laster[1] );

	memset( p_circle, 0, sizeof(WEATHER_CIRCLE_WORK) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�̪�ĊJ�n
 *
 *	@param	p_circle	�~���[�N
 *	@param	s_r			�J�n���a
 *	@param	e_r			�I�����a
 *	@param	c_x			���S�����W
 *	@param	c_y			���S�����W
 *	@param	sync		�V���N
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void drawWeatherCircleStart( WEATHER_CIRCLE_WORK* p_circle, fx32 s_r, fx32 e_r, int c_x, int c_y, int sync )
{
	WeatherMoveReqFx( &p_circle->r, s_r, e_r, sync );
	p_circle->x = c_x;
	p_circle->y = c_y;
	p_circle->status = WEATHER_CIRCLE_STATUS_DO;

	CalcWeatherCircle( p_circle );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�~���[�N���C��
 *
 *	@param	p_circle	�~���[�N
 *
 *	@retval	TRUE	�I��	
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL drawWeatherCircleMain( WEATHER_CIRCLE_WORK* p_circle )
{
	BOOL result;

	if( p_circle->status == WEATHER_CIRCLE_STATUS_INIT ){

		// �I����Ă���̂ŁA�Q�Ɛ���������ݐ��
		// �R�s�[���J��Ԃ�
		CalcWeatherCircleCopyBuff( p_circle );

		return TRUE;
	}
	
	result = WeatherMoveMainFx( &p_circle->r );
	CalcWeatherCircle( p_circle );

	if( result == TRUE ){
		p_circle->status = WEATHER_CIRCLE_STATUS_INIT;
	}

	return result;
}

//----------------------------------------------------------------------------
/**
 *	@brief	H�u�����N���ԃR�[���o�b�N�֐�
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void drawWeatherCircleHblankCall( FIELD_HBLANK_OBJ* p_hbw, void* p_work )
{
	WEATHER_CIRCLE_WORK* p_circle = p_work;
	const u16* cp_buff[2];
	int count;
	int i;
	
	count = GX_GetVCount();
	
	for( i=0; i<2; i++ ){
		cp_buff[i] = LASTER_GetReadBuff( p_circle->p_laster[i] );
	}
	
	if( count < 192 ){
		count++;	// ���̍����̃f�[�^��ݒ�
		if( count >= 192 ){
			count -= 192;
		}
		// BG1�ʂ�H�����X�N���[���ݒ�
		if( GX_IsHBlank() ){
			G2_SetWnd1Position( cp_buff[ 0 ][ count ], 0, cp_buff[ 1 ][ count ], 192 );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	V�u�����N�R�[���o�b�N�֐�
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void drawWeatherCircleVblankCall( TCB_PTR tcb, void* p_work )
{
	WEATHER_CIRCLE_WORK* p_circle = p_work;
	int i;
	
	for( i=0; i<2; i++ ){
		LASTER_VBlank( p_circle->p_laster[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	VBlank���Ԓ��ɃE�B���h�E�ł̉~�`�揈����j������
 *
 *	@param	p_circle	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void drawWeatherCircleEndReq( WEATHER_CIRCLE_WORK* p_circle )
{
	VWaitTCB_Add( drawWeatherCircleEndVblank, p_circle, WEATHER_TCB_CIRCLEEND_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	VBlank���Ԓ��ɃE�B���h�E�ł̉~�`�揈����j������
 *
 *	@param	tcb		TCB���[�N
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void drawWeatherCircleEndVblank( TCB_PTR tcb, void* p_work )
{
	drawWeatherCircleEnd( p_work );

	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	circle��������J���A�j���I����́A�_�u���o�b�t�@�̏������ݐ��
 *	�@�Q�Ɛ�̃f�[�^���R�s�[���邽�߂̊֐�
 *
 *	@param	p_circle	�~���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void CalcWeatherCircleCopyBuff( WEATHER_CIRCLE_WORK* p_circle )
{
	const u16* cp_read;
	u16* p_write;
	int i;
	
	for( i=0; i<2; i++ ){

		cp_read = LASTER_GetReadBuff( p_circle->p_laster[i] );
		p_write = LASTER_GetWriteBuff( p_circle->p_laster[i] );
		memcpy( p_write, cp_read, sizeof(u16) * 192 );
	}

}

//----------------------------------------------------------------------------
/**
 *	@brief	H�u�����N���荞�݃R�[���o�b�N�֐���o�^
 *
 *	@param	tcb			TCB���[�N
 *	@param	p_work		���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void drawWeatherCircleInitHblankTcb( TCB_PTR tcb, void* p_work )
{
	WEATHER_CIRCLE_WORK* p_circle = p_work;
	GXWndPlane outside = G2_GetWndOutsidePlane();
	int visi = GX_GetVisibleWnd();

	// �E�B���h�E�ݒ�
	G2_SetWnd1InsidePlane( WEATHER_FLASH_WND_MSK, TRUE );
//	G2_SetWndOutsidePlane( outside.planeMask | WEATHER_FLASH_OUTSIDE_WND_MSK, outside.effect );
	G2_SetWndOutsidePlane( WEATHER_FLASH_OUTSIDE_WND_MSK, outside.effect );
	G2_SetWnd1Position( 0,0,255,192 );
	GX_SetVisibleWnd( visi | GX_WNDMASK_W1 );

	p_circle->p_hblank = FLDHBLANK_OBJ_Add( p_circle->p_fldhblksys, drawWeatherCircleHblankCall, p_circle );

	TCB_Delete( tcb );
}

