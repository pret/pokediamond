//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		encount_effect_sub.c
 *	@brief		�G���J�E���g�G�t�F�N�g
 *	@author		tomoya takahshi
 *	@data		2006.05.07
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "system/lib_pack.h"
#include "system/brightness.h"
#include "fieldsys.h"
#include "fieldmap_work.h"
#include "field_event.h"
#include "fld_motion_bl.h"
#include "encount_effect_def.h"
#include "system/wipe.h"
#include "system/laster.h"
#include "field_encounteffect.naix"
#include "savedata/mystatus.h"
#include "include/battle/trtype_def.h"

#define	__ECNT_TOMO_H_GLOBAL
#include "encount_effect_sub.h"

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
 *	�W�����v�I
 *
 *	�쐶		[ FIELD ]		
 *	�g���[�i�[	[ TRAINER ]
 *	����		[ SPECIAL ]
 *	��͒c		[ GINGA ]
 *	�`���|�P����[ LEGEND ]
 *	����g���[�i�[[ SP_TR ]
 * 
 *
 */
//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------
/**
 * 
 *		�t�B�[���h�@�쐶�G���J�E���g [ FIELD ]
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	���X�^�[�X�N���[���@�^�X�N�D�揇��
//=====================================
#define ENCOUNT_EFF_LASTER_SCRLL_VWAIT_BUFF_SWITCH_TASK_PRI	( 1024 )
#define ENCOUNT_EFF_LASTER_SCRLL_VINTR_DMA_SET_TASK_PRI	( 1024 )


//-------------------------------------
//	�쐶�@���@���x������
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_GRASS_HIGH_START,
	ENCOUNT_GRASS_HIGH_FLASH_INI,
	ENCOUNT_GRASS_HIGH_FLASH_WAIT,
	ENCOUNT_GRASS_HIGH_MOVE00,
	ENCOUNT_GRASS_HIGH_MOVE01,
	ENCOUNT_GRASS_HIGH_END,
};
#define ENCOUNT_GRASS_HIGH_MOVE00_SYNC	( 6 )		// �V���N��
#define ENCOUNT_GRASS_HIGH_MOVE01_SYNC	( 6 )

#define ENCOUNT_GRASS_HIGH_MOVE00_CAMERA_MOVE	( FX32_ONE * 50 )	// �J��������
#define ENCOUNT_GRASS_HIGH_MOVE00_CAMERA_SS		( FX32_ONE * 30 )	// �J��������
#define ENCOUNT_GRASS_HIGH_MOVE00_BGSL_SS	( FX32_ONE * -12 )	// �����x
#define ENCOUNT_GRASS_HIGH_MOVE00_BGSL_X	( -3 * FX32_ONE )	// ������

#define ENCOUNT_GRASS_HIGH_MOVE01_CAMERA_MOVE	( -FX32_ONE * 50 )
#define ENCOUNT_GRASS_HIGH_MOVE01_CAMERA_SS	( -FX32_ONE * 255 )
#define ENCOUNT_GRASS_HIGH_MOVE01_BGSL_SS	( FX32_ONE * 30 )		// �����x
#define ENCOUNT_GRASS_HIGH_MOVE01_BGSL_X	( 255 * FX32_ONE )	// ������
#define ENCOUNT_GRASS_HIGH_DOT			( 2 )

//-------------------------------------
//	�쐶�@���@���x���Ⴂ
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_GRASS_LOW_START,
	ENCOUNT_GRASS_LOW_FLASH_INI,
	ENCOUNT_GRASS_LOW_FLASH_WAIT,
	ENCOUNT_GRASS_LOW_MOVE00,
	ENCOUNT_GRASS_LOW_MOVE01,
	ENCOUNT_GRASS_LOW_END,
};
#define ENCOUNT_GRASS_LOW_MOVE00_SYNC	( 6 )		// �V���N��
#define ENCOUNT_GRASS_LOW_MOVE01_SYNC	( 6 )

#define ENCOUNT_GRASS_LOW_MOVE00_CAMERA_MOVE	( FX32_ONE * 50 )	// �J��������
#define ENCOUNT_GRASS_LOW_MOVE00_CAMERA_SS		( FX32_ONE * 30 )	// �J��������
#define ENCOUNT_GRASS_LOW_MOVE00_BGSL_SS	( FX32_ONE * -12 )	// �����x
#define ENCOUNT_GRASS_LOW_MOVE00_BGSL_X	( -2 * FX32_ONE )	// ������

#define ENCOUNT_GRASS_LOW_MOVE01_CAMERA_MOVE	( -FX32_ONE * 30 )
#define ENCOUNT_GRASS_LOW_MOVE01_CAMERA_SS	( -FX32_ONE * 100 )
#define ENCOUNT_GRASS_LOW_MOVE01_BGSL_SS	( FX32_ONE *30 )		// �����x
#define ENCOUNT_GRASS_LOW_MOVE01_BGSL_X	( 255 * FX32_ONE )	// ������
#define ENCOUNT_GRASS_LOW_DOT			( 5 )

//-------------------------------------
//	�쐶�@���@���x���Ⴂ
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_WATER_LOW_START,
	ENCOUNT_WATER_LOW_FLASH_INI,
	ENCOUNT_WATER_LOW_FLASH_WAIT,
	ENCOUNT_WATER_LOW_MOVE,
	ENCOUNT_WATER_LOW_WIPE,
	ENCOUNT_WATER_LOW_WIPE_WAIT,
	ENCOUNT_WATER_LOW_END,
};

#define ENCOUNT_WATER_LOW_FLASH_DO_WAIT	( 10 )
#define ENCOUNT_WATER_LOW_MOVE_SYNC	( 9 )
#define ENCOUNT_WATER_LOW_MOVE_WAIT	( 12 )
#define ENCOUNT_WATER_LOW_SIN_R		( FX32_CONST( 12 ) )	// ���a
#define ENCOUNT_WATER_LOW_LASTER_SP	( 800 )	// ���X�^�[�X�s�[�h
#define ENCOUNT_WATER_LOW_SIN_ADDR	( (0xffff/192) * 2 )// ���X�^�[�p�x�X�s�[�h
#define ENCOUNT_WATER_LOW_LASTER_TASK_PRI	( TCB_TSK_PRI - 1 )
#define ENCOUNT_WATER_LOW_WIPE_SYNC	( 8 )

#define ENCOUNT_WATER_LOW_MOVE_Y_S	( 192 )
#define ENCOUNT_WATER_LOW_MOVE_Y_E	( 0 )


//-------------------------------------
//	�쐶�@���@���x������
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_WATER_HIGH_START,
	ENCOUNT_WATER_HIGH_FLASH_INI,
	ENCOUNT_WATER_HIGH_FLASH_WAIT,
	ENCOUNT_WATER_HIGH_MOVE,
	ENCOUNT_WATER_HIGH_WIPE,
	ENCOUNT_WATER_HIGH_WIPE_WAIT,
	ENCOUNT_WATER_HIGH_END,
};

#define ENCOUNT_WATER_HIGH_FLASH_DO_WAIT	( 10  )
#define ENCOUNT_WATER_HIGH_MOVE_SYNC	( 9 )
#define ENCOUNT_WATER_HIGH_MOVE_WAIT	( 12 )
#define ENCOUNT_WATER_HIGH_SIN_R		( FX32_CONST( 15 ) )	// ���a
#define ENCOUNT_WATER_HIGH_LASTER_SP	( 800 )	// ���X�^�[�X�s�[�h
#define ENCOUNT_WATER_HIGH_SIN_ADDR	( (0xffff/192) * 3 )// ���X�^�[�p�x�X�s�[�h
#define ENCOUNT_WATER_HIGH_WIPE_SYNC	( 8 )
#define ENCOUNT_WATER_HIGH_LASTER_TASK_PRI	( TCB_TSK_PRI - 1 )

#define ENCOUNT_WATER_HIGH_MOVE_Y_S	( 192 )
#define ENCOUNT_WATER_HIGH_MOVE_Y_E	( 0 )
#define ENCOUNT_WATER_HIGH_LASTER_X_MUL	( 3 )
#define ENCOUNT_WATER_HIGH_LASTER_Y_MUL	( 1 )

//-------------------------------------
//	�쐶�@�_���W�����@���x����
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_DAN_LOW_START,
	ENCOUNT_DAN_LOW_FLASH_INI,
	ENCOUNT_DAN_LOW_FLASH_WAIT,
	ENCOUNT_DAN_LOW_WIPE,
	ENCOUNT_DAN_LOW_WIPE_WAIT,
	ENCOUNT_DAN_LOW_END,
};

#define ENCOUNT_DAN_LOW_MOVE_SYNC	( 12 )
#define ENCOUNT_DAN_LOW_MOVE00_CAMERA_MOVE		( -FX32_ONE * 400 )	// �J��������
#define ENCOUNT_DAN_LOW_MOVE00_CAMERA_SS		( -FX32_ONE * 2 )	// �J��������

//-------------------------------------
//	�쐶�@�_���W�����@���x����
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_DAN_HIGH_START,
	ENCOUNT_DAN_HIGH_FLASH_INI,
	ENCOUNT_DAN_HIGH_FLASH_WAIT,
	ENCOUNT_DAN_HIGH_WIPE,
	ENCOUNT_DAN_HIGH_WIPE_WAIT,
	ENCOUNT_DAN_HIGH_END,
};

#define ENCOUNT_DAN_HIGH_MOVE_SYNC	( 12 )
#define ENCOUNT_DAN_HIGH_MOVE00_CAMERA_MOVE		( -FX32_ONE * 800 )	// �J��������
#define ENCOUNT_DAN_HIGH_MOVE00_CAMERA_SS		( -FX32_ONE * 5 )	// �J��������




//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�쐶�@���@���x������
//=====================================
typedef struct{
	GF_CAMERA_PTR	camera;				// �J�����f�[�^
	ENC_ADDMOVE_WORK_FX camera_dist;
	ENC_HB_BG_SLICE* p_slice;
} ENCOUNT_GRASS_HIGH;

//-------------------------------------
//	�쐶�@���@���x���Ⴂ
//=====================================
typedef struct{
	GF_CAMERA_PTR	camera;				// �J�����f�[�^
	ENC_ADDMOVE_WORK_FX camera_dist;
	ENC_HB_BG_SLICE* p_slice;
} ENCOUNT_GRASS_LOW;

//-------------------------------------
//	p_laster�X�N���[�����[�N
//=====================================
typedef struct {
	LASTER_SCROLL_PTR p_laster;
	TCB_PTR VDma;
	u32 dmacount;
} ENCOUNT_LASTER_SCROLL;


//-------------------------------------
//	�쐶�@���@���x���Ⴂ
//=====================================
typedef struct{
	ENCOUNT_LASTER_SCROLL laster;
//	ENC_MOVE_WORK move_y;
	s32 wait;
} ENCOUNT_WATER_LOW;

//-------------------------------------
//	�쐶�@���@���x������
//=====================================
typedef struct{
	ENCOUNT_LASTER_SCROLL laster;
//	ENC_MOVE_WORK move_y;
	s32 wait;
} ENCOUNT_WATER_HIGH;

//-------------------------------------
//	�쐶�@�_���W�����@���x���Ⴂ
//=====================================
typedef struct{
	GF_CAMERA_PTR	camera;				// �J�����f�[�^
	ENC_ADDMOVE_WORK_FX camera_dist;
} ENCOUNT_DAN_LOW;

//-------------------------------------
//	�쐶�@�_���W�����@���x������
//=====================================
typedef struct{
	GF_CAMERA_PTR	camera;				// �J�����f�[�^
	ENC_ADDMOVE_WORK_FX camera_dist;
} ENCOUNT_DAN_HIGH;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static TCB_PTR EncountEffect_LasterScroll_VDmaTaskReq( ENCOUNT_LASTER_SCROLL* p_lstscr );
static void EncountEffect_LasterScroll_VDmaTCB( TCB_PTR tcb, void* p_work );
static void EF_Laster_Init( ENCOUNT_LASTER_SCROLL* p_laster, u32 heapID );
static void EF_Laster_Delete( ENCOUNT_LASTER_SCROLL* p_laster );
static void EF_Laster_Start( ENCOUNT_LASTER_SCROLL* p_laster, u8 start, u8 end, u16 add_r, fx32 r_w, s16 scr_sp, u32 bg_no, u32 init_num, u32 tsk_pri );

static void EF_Laster_BuffYSet( ENCOUNT_LASTER_SCROLL* p_laster, s16 start_y );
static void EF_Laster_BuffXFlip( ENCOUNT_LASTER_SCROLL* p_laster, u32 dot );

//----------------------------------------------------------------------------
/**
 *	@brief	�쐶�@���@���x������
 *
 *	@param	tcb		�^�X�N���[�N
 *	@param	work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void EncountEffect_Field_GrassLevelHigh(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_GRASS_HIGH* task_w = eew->work;
	fx32 distans;
	BOOL result;

	switch(eew->seq){
	case ENCOUNT_GRASS_HIGH_START:
		eew->work = sys_AllocMemory(HEAPID_FIELD, sizeof(ENCOUNT_GRASS_HIGH));
		memset( eew->work, 0, sizeof(ENCOUNT_GRASS_HIGH) );
		task_w = eew->work;

		// �X���C�X���[�N�쐬
		task_w->p_slice = ENC_BG_Slice_Alloc();

		eew->seq++;
		break;
		
	case ENCOUNT_GRASS_HIGH_FLASH_INI:
		EncountFlashTask(MASK_MAIN_DISPLAY, 16, -16,  &eew->wait, 2);

		eew->seq++;
		break;
		
	case ENCOUNT_GRASS_HIGH_FLASH_WAIT:
		if(eew->wait){
			eew->wait = 0;
			eew->seq++;

			// ����J�n
			ENC_BG_Slice_Start( eew, task_w->p_slice, 
					ENCOUNT_GRASS_HIGH_DOT,
					ENCOUNT_GRASS_HIGH_MOVE00_SYNC + 1, 
					0, ENCOUNT_GRASS_HIGH_MOVE00_BGSL_X,
					ENCOUNT_GRASS_HIGH_MOVE00_BGSL_SS );
			// ���샏�[�N������
			task_w->camera = eew->fsw->camera_ptr;
			distans = GFC_GetCameraDistance( task_w->camera );
			ENC_AddMoveReqFx( &task_w->camera_dist, distans, distans + ENCOUNT_GRASS_HIGH_MOVE00_CAMERA_MOVE, ENCOUNT_GRASS_HIGH_MOVE00_CAMERA_SS, ENCOUNT_GRASS_HIGH_MOVE00_SYNC );
		}
		break;
	
	case ENCOUNT_GRASS_HIGH_MOVE00:
		result = ENC_AddMoveMainFx( &task_w->camera_dist );
		GFC_SetCameraDistance( task_w->camera_dist.x, task_w->camera );

		if( result == TRUE ){
			eew->seq++;
			// ����J�n
			ENC_BG_Slice_Change( eew, task_w->p_slice, ENCOUNT_GRASS_HIGH_DOT, ENCOUNT_GRASS_HIGH_MOVE01_SYNC, ENCOUNT_GRASS_HIGH_MOVE00_BGSL_X, ENCOUNT_GRASS_HIGH_MOVE01_BGSL_X, ENCOUNT_GRASS_HIGH_MOVE01_BGSL_SS );
			// ���샏�[�N������
			task_w->camera = eew->fsw->camera_ptr;
			distans = GFC_GetCameraDistance( task_w->camera );
			ENC_AddMoveReqFx( &task_w->camera_dist, distans, distans + ENCOUNT_GRASS_HIGH_MOVE01_CAMERA_MOVE, ENCOUNT_GRASS_HIGH_MOVE01_CAMERA_SS, ENCOUNT_GRASS_HIGH_MOVE01_SYNC );
		}
		break;

	case ENCOUNT_GRASS_HIGH_MOVE01:
		result = ENC_AddMoveMainFx( &task_w->camera_dist );
		GFC_SetCameraDistance( task_w->camera_dist.x, task_w->camera );

		if( (result == TRUE) && (ENC_HBlankEndCheck( eew ) == TRUE) ){
			eew->seq++;
		}
		break;

	case ENCOUNT_GRASS_HIGH_END:
		WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );

		G2_SetBG0Offset(0, 0);
		G2_SetBG1Offset(0, 0);
		G2_SetBG2Offset(0, 0);
		G2_SetBG3Offset(0, 0);

		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		ENC_BG_Slice_Delete( task_w->p_slice );
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		break;

	default:
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�쐶�@���@���x���Ⴂ
 *
 *	@param	tcb		�^�X�N���[�N
 *	@param	work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void EncountEffect_Field_GrassLevelLow(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_GRASS_LOW* task_w = eew->work;
	fx32 distans;
	BOOL result;

	switch(eew->seq){
	case ENCOUNT_GRASS_LOW_START:
		eew->work = sys_AllocMemory(HEAPID_FIELD, sizeof(ENCOUNT_GRASS_LOW));
		memset( eew->work, 0, sizeof(ENCOUNT_GRASS_LOW) );
		task_w = eew->work;

		// �X���C�X���[�N�쐬
		task_w->p_slice = ENC_BG_Slice_Alloc();

		eew->seq++;
		break;
		
	case ENCOUNT_GRASS_LOW_FLASH_INI:
		EncountFlashTask(MASK_MAIN_DISPLAY, -16, -16,  &eew->wait, 2);

		eew->seq++;
		break;
		
	case ENCOUNT_GRASS_LOW_FLASH_WAIT:
		if(eew->wait){
			eew->wait = 0;
			eew->seq++;

			// ����J�n
			ENC_BG_Slice_Start( eew, task_w->p_slice, 
					ENCOUNT_GRASS_LOW_DOT,
					ENCOUNT_GRASS_LOW_MOVE00_SYNC + 1,	///<���œ��쒆�ɒl�ύX���邽��
					0, ENCOUNT_GRASS_LOW_MOVE00_BGSL_X,
					ENCOUNT_GRASS_LOW_MOVE00_BGSL_SS );
			// ���샏�[�N������
			task_w->camera = eew->fsw->camera_ptr;
			distans = GFC_GetCameraDistance( task_w->camera );
			ENC_AddMoveReqFx( &task_w->camera_dist, distans, distans + ENCOUNT_GRASS_LOW_MOVE00_CAMERA_MOVE, ENCOUNT_GRASS_LOW_MOVE00_CAMERA_SS, ENCOUNT_GRASS_LOW_MOVE00_SYNC );
		}
		break;
	
	case ENCOUNT_GRASS_LOW_MOVE00:
		result = ENC_AddMoveMainFx( &task_w->camera_dist );
		GFC_SetCameraDistance( task_w->camera_dist.x, task_w->camera );

		if( (result == TRUE) ){
			eew->seq++;
			// ����J�n
			ENC_BG_Slice_Change( eew, task_w->p_slice, ENCOUNT_GRASS_LOW_DOT, ENCOUNT_GRASS_LOW_MOVE01_SYNC, ENCOUNT_GRASS_LOW_MOVE00_BGSL_X, ENCOUNT_GRASS_LOW_MOVE01_BGSL_X, ENCOUNT_GRASS_LOW_MOVE01_BGSL_SS );
			// ���샏�[�N������
			task_w->camera = eew->fsw->camera_ptr;
			distans = GFC_GetCameraDistance( task_w->camera );
			ENC_AddMoveReqFx( &task_w->camera_dist, distans, distans + ENCOUNT_GRASS_LOW_MOVE01_CAMERA_MOVE, ENCOUNT_GRASS_LOW_MOVE01_CAMERA_SS, ENCOUNT_GRASS_LOW_MOVE01_SYNC );
		}
		break;

	case ENCOUNT_GRASS_LOW_MOVE01:
		result = ENC_AddMoveMainFx( &task_w->camera_dist );
		GFC_SetCameraDistance( task_w->camera_dist.x, task_w->camera );

		if( (result == TRUE) && (ENC_HBlankEndCheck( eew ) == TRUE) ){
			eew->seq++;
		}
		break;

	case ENCOUNT_GRASS_LOW_END:
		WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );

		G2_SetBG0Offset(0, 0);
		G2_SetBG1Offset(0, 0);
		G2_SetBG2Offset(0, 0);
		G2_SetBG3Offset(0, 0);

		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		ENC_BG_Slice_Delete( task_w->p_slice );
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����G���J�E���g�G�t�F�N�g
 *
 *	@param	tcb		�^�X�N���[�N
 *	@param	work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void EncountEffect_Field_WaterLevelLow(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_WATER_LOW* task_w = eew->work;

	switch(eew->seq){
	case ENCOUNT_WATER_LOW_START:
		eew->work = sys_AllocMemory(HEAPID_FIELD, sizeof(ENCOUNT_WATER_LOW));
		memset( eew->work, 0, sizeof(ENCOUNT_WATER_LOW) );
		task_w = eew->work;

		// ���X�^�[������
		EF_Laster_Init( &task_w->laster, HEAPID_FIELD );
		
		// �t�B�[���hH�u�����NOFF
		FLDHBLANK_SYS_Stop( eew->fsw->fldmap->hblanksys );

		eew->seq++;
		break;
		
	case ENCOUNT_WATER_LOW_FLASH_INI:
		EncountFlashTask(MASK_MAIN_DISPLAY, -16, -16,  &eew->wait, 2);
		task_w->wait = ENCOUNT_WATER_LOW_FLASH_DO_WAIT;
		eew->seq++;
		break;
		
	case ENCOUNT_WATER_LOW_FLASH_WAIT:
		task_w->wait --;
		if(task_w->wait < 0){
			eew->seq++;
			task_w->wait = ENCOUNT_WATER_LOW_MOVE_WAIT;
			EF_Laster_Start( &task_w->laster,
					0, 191, ENCOUNT_WATER_LOW_SIN_ADDR, 
					ENCOUNT_WATER_LOW_SIN_R, ENCOUNT_WATER_LOW_LASTER_SP,
					LASTER_SCROLL_MBG0, 0, ENCOUNT_WATER_LOW_LASTER_TASK_PRI );

/*			ENC_MoveReq( &task_w->move_y, 
					ENCOUNT_WATER_LOW_MOVE_Y_S,
					ENCOUNT_WATER_LOW_MOVE_Y_E,
					ENCOUNT_WATER_LOW_MOVE_SYNC );//*/
		}
		break;
		
	case ENCOUNT_WATER_LOW_MOVE:
//		ENC_MoveMain( &task_w->move_y );
//		EF_Laster_BuffYSet( &task_w->laster, task_w->move_y.x );
		task_w->wait --;
		if( task_w->wait < 0 ){
			eew->seq++;
		}
		break;
		
	case ENCOUNT_WATER_LOW_WIPE:
		//�u���b�N�A�E�g
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_BLINDOUT_H, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, ENCOUNT_WATER_LOW_WIPE_SYNC, 1, HEAPID_FIELD );
		eew->seq++;
		break;
		
	case ENCOUNT_WATER_LOW_WIPE_WAIT:
		if( WIPE_SYS_EndCheck() ){
			eew->seq++;
		}
		break;
		
	case ENCOUNT_WATER_LOW_END:

		// ���X�^�[�j��
		EF_Laster_Delete( &task_w->laster );
		
		// �t�B�[���hH�u�����NON
		FLDHBLANK_SYS_Start( eew->fsw->fldmap->hblanksys );

		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����G���J�E���g
 *
 *	@param	tcb		�^�X�N���[�N
 *	@param	work	���[�N
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void EncountEffect_Field_WaterLevelHigh(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_WATER_HIGH* task_w = eew->work;

	switch(eew->seq){
	case ENCOUNT_WATER_HIGH_START:
		eew->work = sys_AllocMemory(HEAPID_FIELD, sizeof(ENCOUNT_WATER_HIGH));
		memset( eew->work, 0, sizeof(ENCOUNT_WATER_HIGH) );
		task_w = eew->work;

		// ���X�^�[������
		EF_Laster_Init( &task_w->laster, HEAPID_FIELD );

		// �t�B�[���hH�u�����NOFF
		FLDHBLANK_SYS_Stop( eew->fsw->fldmap->hblanksys );

		eew->seq++;
		break;
		
	case ENCOUNT_WATER_HIGH_FLASH_INI:
		EncountFlashTask(MASK_MAIN_DISPLAY, 16, -16,  &eew->wait, 2);
		task_w->wait = ENCOUNT_WATER_HIGH_FLASH_DO_WAIT;
		eew->seq++;
		break;
		
	case ENCOUNT_WATER_HIGH_FLASH_WAIT:
		task_w->wait --;
		if(task_w->wait < 0){
			eew->seq++;
			task_w->wait = ENCOUNT_WATER_HIGH_MOVE_WAIT;
			EF_Laster_Start( &task_w->laster,
					0, 191, ENCOUNT_WATER_HIGH_SIN_ADDR, 
					ENCOUNT_WATER_HIGH_SIN_R, ENCOUNT_WATER_HIGH_LASTER_SP,
					LASTER_SCROLL_MBG0, 0, ENCOUNT_WATER_HIGH_LASTER_TASK_PRI );
		}
		break;
		
	case ENCOUNT_WATER_HIGH_MOVE:

		task_w->wait --;
		if( task_w->wait < 0 ){
			eew->seq++;
		}
		break;
		
	case ENCOUNT_WATER_HIGH_WIPE:

		//�u���b�N�A�E�g
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_BLINDOUT_H, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, ENCOUNT_WATER_HIGH_WIPE_SYNC, 1, HEAPID_FIELD );
		eew->seq++;
		break;
		
	case ENCOUNT_WATER_HIGH_WIPE_WAIT:

		if( WIPE_SYS_EndCheck() ){
			eew->seq++;
		}
		break;
		
	case ENCOUNT_WATER_HIGH_END:
		// ���X�^�[�j��
		EF_Laster_Delete( &task_w->laster );

		// �t�B�[���hH�u�����NON
		FLDHBLANK_SYS_Start( eew->fsw->fldmap->hblanksys );

		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		break;
	}
}



//----------------------------------------------------------------------------
/**
 *	@brief	���X�^�[�X�N���[���V�X�e���@V�u�����NDMA�]�����N�G�X�g�^�X�N
 *
 *	@param	p_lstscr	���X�^�[�X�N���[���V�X�e��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static TCB_PTR EncountEffect_LasterScroll_VDmaTaskReq( ENCOUNT_LASTER_SCROLL* p_lstscr )
{
	return VIntrTCB_Add( EncountEffect_LasterScroll_VDmaTCB,
			p_lstscr, ENCOUNT_EFF_LASTER_SCRLL_VINTR_DMA_SET_TASK_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	DMA�]���^�X�N
 *
 *	@param	tcb		�^�X�N���[�N
 *	@param	p_work	���[�N
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void EncountEffect_LasterScroll_VDmaTCB( TCB_PTR tcb, void* p_work )
{
	ENCOUNT_LASTER_SCROLL* p_lstscr = p_work;

	if( p_lstscr->dmacount >= 2 ){
		LASTER_ScrollVBuffSwitch( p_lstscr->p_laster );
		p_lstscr->dmacount = 0;
	}

	LASTER_ScrollVDma( p_lstscr->p_laster );
	p_lstscr->dmacount ++;
}


//----------------------------------------------------------------------------
/**
 *	@brief	���X�^�[������
 *
 *	@param	p_laster	���X�^�[���[�N
 *	@param	heapID		�q�[�vID
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EF_Laster_Init( ENCOUNT_LASTER_SCROLL* p_laster, u32 heapID )
{
	p_laster->p_laster = LASTER_ScrollInit( heapID );
	p_laster->dmacount = 0;
	p_laster->VDma = EncountEffect_LasterScroll_VDmaTaskReq( p_laster );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���X�^�[�j��
 *
 *	@param	p_laster	���X�^�[���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EF_Laster_Delete( ENCOUNT_LASTER_SCROLL* p_laster )
{
	TCB_Delete( p_laster->VDma );
	LASTER_ScrollEnd( p_laster->p_laster );
	LASTER_ScrollDelete( p_laster->p_laster );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���X�^�[�J�n
 *
 *	@param	p_laster	���[�N
 *	@param	start		���X�^�[�X�N���[��������J�n�����W
 *	@param	end			���X�^�[�X�N���[��������I�������W
 *	@param	add_r		sin�J�[�u�e�[�u���쐬���̊p�x�𑫂��Ă����l(0�`65535)
 *	@param	r_w			sin�J�[�u�̔��a
 *	@param	scr_sp		���X�^�[�X�N���[���X�s�[�h	����*100�����l	�}�C�i�X�L��
 *	@param	bg_no		���X�^�[��������BG�̔ԍ�
 *	@param	init_num	���[�N������������l
 *	@param	tsk_pri		�^�X�N�D�揇��
 *
 *	@return	none
 *
 * bg_no
 * 		LASTER_SCROLL_MBG0,
 *		LASTER_SCROLL_MBG1,
 *		LASTER_SCROLL_MBG2,
 *		LASTER_SCROLL_MBG3,
 *		LASTER_SCROLL_SBG0,
 *		LASTER_SCROLL_SBG1,
 *		LASTER_SCROLL_SBG2,
 *		LASTER_SCROLL_SBG3
 */
//-----------------------------------------------------------------------------
static void EF_Laster_Start( ENCOUNT_LASTER_SCROLL* p_laster, u8 start, u8 end, u16 add_r, fx32 r_w, s16 scr_sp, u32 bg_no, u32 init_num, u32 tsk_pri )
{
	LASTER_ScrollStart( p_laster->p_laster,
			start, end, add_r, 
			r_w, scr_sp,
			bg_no, init_num, tsk_pri );
}


//----------------------------------------------------------------------------
/**
 *	@brief	���X�^�[�J�nY�ʒu�ݒ�
 *
 *	@param	p_laster
 *	@param	start_y 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void EF_Laster_BuffYSet( ENCOUNT_LASTER_SCROLL* p_laster, s16 start_y )
{
	u32* p_buff;
	u32* p_write;
	int i;
	u32 num;

	p_write = sys_AllocMemory( HEAPID_FIELD, sizeof(u32) * LASTER_SCROLL_BUFF_SIZE );
	memset( p_write, 9, sizeof(u32) * LASTER_SCROLL_BUFF_SIZE );

	p_buff = LASTER_GetScrollWriteBuff( p_laster->p_laster );
	
	for( i=0; i<192; i++ ){
		if( ((-start_y + i) >= 0) &&
			((-start_y + i) < 192 ) ){
			num = p_buff[ (-start_y + i) ];
		}else{
			num = 0;
		}
		p_write[i] = num;
	}

	memcpy( p_buff, p_write, sizeof(u32) * LASTER_SCROLL_BUFF_SIZE );
	
	sys_FreeMemoryEz( p_write );	
}

//----------------------------------------------------------------------------
/**
 *	@brief	���X�^�[�̉����W��dot���Ƃɔ��]������
 *
 *	@param	p_laster	���X�^�[���[�N
 *	@param	dot			�h�b�g��
 */
//-----------------------------------------------------------------------------
static void EF_Laster_BuffXFlip( ENCOUNT_LASTER_SCROLL* p_laster, u32 dot )
{
	u32* p_buff;
	int i;
	s16 x;
	
	p_buff = LASTER_GetScrollWriteBuff( p_laster->p_laster );

	for( i=0; i<192; i++ ){
		x = p_buff[i] & 0xffff;
		if( ((i / dot) % 2) == 0 ){
			p_buff[i] = (x & 0xffff);
		}else{
			p_buff[i] = (-x & 0xffff);
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�쐶�@�_���W�����@���x����
 *
 *	@param	tcb		�^�X�N���[�N
 *	@param	work	���[�N
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void EncountEffect_Field_DanLevelLow(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_DAN_LOW* task_w = eew->work;
	fx32 distans;
	
	switch( eew->seq ){
	case ENCOUNT_DAN_LOW_START:
		eew->work = sys_AllocMemory(HEAPID_FIELD, sizeof(ENCOUNT_DAN_LOW));
		memset( eew->work, 0, sizeof(ENCOUNT_DAN_LOW) );
		task_w = eew->work;
		eew->seq++;
		break;
		
	case ENCOUNT_DAN_LOW_FLASH_INI:
		EncountFlashTask(MASK_MAIN_DISPLAY, -16, -16,  &eew->wait, 2);
		eew->seq++;
		break;
		
	case ENCOUNT_DAN_LOW_FLASH_WAIT:
		if( eew->wait ){
			eew->seq++;
		}
		break;
		
	case ENCOUNT_DAN_LOW_WIPE:
		// �t�B�[���hH�u�����NON
		FLDHBLANK_SYS_Stop( eew->fsw->fldmap->hblanksys );

		// �J�����߂Â��Ȃ��烏�C�v
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_HOLEOUT, WIPE_TYPE_HOLEOUT, WIPE_FADE_BLACK, ENCOUNT_DAN_LOW_MOVE_SYNC, 1, HEAPID_FIELD );

		task_w->camera = eew->fsw->camera_ptr;
		distans = GFC_GetCameraDistance( task_w->camera );

		ENC_AddMoveReqFx( &task_w->camera_dist, distans, distans + ENCOUNT_DAN_LOW_MOVE00_CAMERA_MOVE, ENCOUNT_DAN_LOW_MOVE00_CAMERA_SS, ENCOUNT_DAN_LOW_MOVE_SYNC );

		eew->seq++;
		break;
		
	case ENCOUNT_DAN_LOW_WIPE_WAIT:
		ENC_AddMoveMainFx( &task_w->camera_dist );
		GFC_SetCameraDistance( task_w->camera_dist.x, task_w->camera );
		if( WIPE_SYS_EndCheck() ){
			eew->seq ++;
		}
		break;
		
	case ENCOUNT_DAN_LOW_END:
		// �t�B�[���hH�u�����NON
		FLDHBLANK_SYS_Start( eew->fsw->fldmap->hblanksys );

		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�쐶	�_���W����	���x����
 *
 *	@param	tcb		�^�X�N���[�N
 *	@param	work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void EncountEffect_Field_DanLevelHigh(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_DAN_HIGH* task_w = eew->work;
	fx32 distans;
	
	switch( eew->seq ){
	case ENCOUNT_DAN_HIGH_START:
		eew->work = sys_AllocMemory(HEAPID_FIELD, sizeof(ENCOUNT_DAN_HIGH));
		memset( eew->work, 0, sizeof(ENCOUNT_DAN_HIGH) );
		task_w = eew->work;
		eew->seq++;
		break;
		
	case ENCOUNT_DAN_HIGH_FLASH_INI:
		EncountFlashTask(MASK_MAIN_DISPLAY, 16, -16,  &eew->wait, 2);
		eew->seq++;
		break;
		
	case ENCOUNT_DAN_HIGH_FLASH_WAIT:
		if( eew->wait ){
			eew->seq++;
		}
		break;
		
	case ENCOUNT_DAN_HIGH_WIPE:
		// �t�B�[���hH�u�����NON
		FLDHBLANK_SYS_Stop( eew->fsw->fldmap->hblanksys );

		// �J�����߂Â��Ȃ��烏�C�v
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_HOLEOUT, WIPE_TYPE_HOLEOUT, WIPE_FADE_BLACK, ENCOUNT_DAN_HIGH_MOVE_SYNC, 1, HEAPID_FIELD );

		task_w->camera = eew->fsw->camera_ptr;
		distans = GFC_GetCameraDistance( task_w->camera );

		ENC_AddMoveReqFx( &task_w->camera_dist, distans, distans + ENCOUNT_DAN_HIGH_MOVE00_CAMERA_MOVE, ENCOUNT_DAN_HIGH_MOVE00_CAMERA_SS, ENCOUNT_DAN_HIGH_MOVE_SYNC );

		eew->seq++;
		break;
		
	case ENCOUNT_DAN_HIGH_WIPE_WAIT:
		ENC_AddMoveMainFx( &task_w->camera_dist );
		GFC_SetCameraDistance( task_w->camera_dist.x, task_w->camera );
		if( WIPE_SYS_EndCheck() ){
			eew->seq ++;
		}
		break;
		
	case ENCOUNT_DAN_HIGH_END:
		// �t�B�[���hH�u�����NON
		FLDHBLANK_SYS_Start( eew->fsw->fldmap->hblanksys );

		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		break;
	}
}




//-----------------------------------------------------------------------------
/**
 * 
 *		�y�t�B�[���h�@�g���[�i�[�G���J�E���g�z [ TRAINER ]
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�g���[�i�[�@���@���x����
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_TR_GRASS_LOW_START,
	ENCOUNT_TR_GRASS_LOW_FLASH_INI,
	ENCOUNT_TR_GRASS_LOW_FLASH_WAIT,
	ENCOUNT_TR_GRASS_LOW_BGSCALE,
	ENCOUNT_TR_GRASS_LOW_BGSCALE_WAIT,
	ENCOUNT_TR_GRASS_LOW_BGCUT,
	ENCOUNT_TR_GRASS_LOW_BGCUTWAIT,
	ENCOUNT_TR_GRASS_LOW_END,
};
// OAM�f�[�^
// �A�N�^�[�f�[�^��
enum{
	ENCOUNT_TR_GRASS_LOW_CELL_BIG,
	ENCOUNT_TR_GRASS_LOW_CELL_BOTTOM,
	ENCOUNT_TR_GRASS_LOW_CELL_NUM,
};
#define ENCOUNT_TR_GRASS_LOW_CELL_RES_NUM	( 1 )	// ���\�[�X��
#define ENCOUNT_TR_GRASS_LOW_CELL_CONT_ID	( 600000 )

// �����p�����[�^	�i�G���Ă悢�����j
#define ENCOUNT_TR_GRASS_LOW_BALL_MAT_X		( 128*FX32_ONE )	// �J�n���W
#define ENCOUNT_TR_GRASS_LOW_BALL_MAT_Y		( 96*FX32_ONE )	// �J�n���W
#define ENCOUNT_TR_GRASS_LOW_SCALE_SYNC		( 10 )		// �g��V���N��

#define ENCOUNT_TR_GRASS_LOW_SLICE_SYNC		( 6 )		// ��ʊ���V���N��

#define ENCOUNT_TR_GRASS_LOW_SCALE_S		( FX32_CONST(0.01f) )	// �g��J�n
#define ENCOUNT_TR_GRASS_LOW_SCALE_E		( FX32_CONST(1.0f) )	// �g��I��
#define ENCOUNT_TR_GRASS_LOW_SCALE_SS		( 2 )		// �����x

#define ENCOUNT_TR_GRASS_LOW_SLICE_BGSL_SS	( FX32_ONE * 10 )		// �����x
#define ENCOUNT_TR_GRASS_LOW_SLICE_BGSL_X	( 255 * FX32_ONE )	// ������
#define ENCOUNT_TR_GRASS_LOW_DOT			( 96 )

#define ENCOUNT_TR_GRASS_LOW_CAMERA_DIST	( -FX32_CONST( 500 ) )	// �J�����ړ�����
#define ENCOUNT_TR_GRASS_LOW_CAMERA_SS		( -FX32_CONST( 10 ) )	// �J���������x

#define ENCOUNT_TR_GRASS_LOW_ROTA_SCALE		( 0xffff * 1 )	// �g�厞�̉�]�p


//-------------------------------------
//	�g���[�i�[�@���@���x����
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_TR_GRASS_HIGH_START,
	ENCOUNT_TR_GRASS_HIGH_FLASH_INI,
	ENCOUNT_TR_GRASS_HIGH_FLASH_WAIT,
	ENCOUNT_TR_GRASS_HIGH_OAM_MOVE,
	ENCOUNT_TR_GRASS_HIGH_OAM_MOVEWAIT,
	ENCOUNT_TR_GRASS_HIGH_BGCUT,
	ENCOUNT_TR_GRASS_HIGH_BGCUTWAIT,
	ENCOUNT_TR_GRASS_HIGH_END,
};
// OAM�f�[�^
// �A�N�^�[�f�[�^��
enum{
	ENCOUNT_TR_GRASS_HIGH_CELL_UP,
	ENCOUNT_TR_GRASS_HIGH_CELL_DOWN,
	ENCOUNT_TR_GRASS_HIGH_CELL_NUM,
};
#define ENCOUNT_TR_GRASS_HIGH_CELL_RES_NUM	( 1 )	// ���\�[�X��
#define ENCOUNT_TR_GRASS_HIGH_CELL_CONT_ID	( 600000 )

// �����p�����[�^	�i�G���Ă悢�����j
#define ENCOUNT_TR_GRASS_HIGH_BALL_MAT_X		( 128*FX32_ONE )// �J�n���W
#define ENCOUNT_TR_GRASS_HIGH_BALL_MAT_Y_UP		( 64*FX32_ONE )	// �J�n���W
#define ENCOUNT_TR_GRASS_HIGH_BALL_MAT_Y_DOWN	( 128*FX32_ONE )	// �J�n���W
#define ENCOUNT_TR_GRASS_HIGH_MOVE_SYNC			( 8 )		// OAM�����V���N��

#define ENCOUNT_TR_GRASS_HIGH_SLICE_SYNC		( 8 )		// ��ʊ��胏�C�v�V���N��

#define ENCOUNT_TR_GRASS_HIGH_BALLMOVE_S		( -192 * FX32_ONE )		// BALL������
#define ENCOUNT_TR_GRASS_HIGH_BALLMOVE_E		( 192 * FX32_ONE )		// BALL������

#define ENCOUNT_TR_GRASS_HIGH_SLICE_BGSL_SS_X	( FX32_ONE * 1 )	// �����x
#define ENCOUNT_TR_GRASS_HIGH_SLICE_BGSL_SS_Y	( FX32_ONE * 1 )	// �����x

#define ENCOUNT_TR_GRASS_HIGH_CAMERA_DIST	( -FX32_CONST( 500 ) )	// �J�����ړ�����
#define ENCOUNT_TR_GRASS_HIGH_CAMERA_SS		( -FX32_CONST( 10 ) )	// �J���������x

#define ENCOUNT_TR_GRASS_HIGH_ROTA			( 0xffff *2)			// ��]�p


//-------------------------------------
//	�g���[�i�[�@���@���x����
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_TR_WATER_LOW_START,
	ENCOUNT_TR_WATER_LOW_FLASH_INI,
	ENCOUNT_TR_WATER_LOW_FLASH_WAIT,
	ENCOUNT_TR_WATER_LOW_OAM_FADEIN,
	ENCOUNT_TR_WATER_LOW_OAM_FADEINWAIT,
	ENCOUNT_TR_WATER_LOW_OAM_SCALE,
	ENCOUNT_TR_WATER_LOW_OAM_SCALEWAIT,
	ENCOUNT_TR_WATER_LOW_END,
};
// OAM�f�[�^
#define ENCOUNT_TR_WATER_LOW_CELL_NUM		( 2 )
#define ENCOUNT_TR_WATER_LOW_CELL_RES_NUM	( 1 )	// ���\�[�X��
#define ENCOUNT_TR_WATER_LOW_CELL_CONT_ID	( 600000 )

// �����p�����[�^	�i�G���Ă悢�����j
#define ENCOUNT_TR_WATER_LOW_MOVE_WAIT	( 12 )			// ���X�^�[�|����^�C�~���O

#define ENCOUNT_TR_WATER_LOW_BALL_MAT_X		( 128*FX32_ONE )// �J�n���W
#define ENCOUNT_TR_WATER_LOW_BALL_MAT_Y		( 96*FX32_ONE )	// �J�n���W

#define ENCOUNT_TR_WATER_LOW_ALPHA_SYNC		( 8 )		// OAM�����V���N��

#define ENCOUNT_TR_WATER_LOW_SCALE_SYNC		( 8 )		// �g�k�V���N��

#define ENCOUNT_TR_WATER_LOW_ALPHA_S		( 0 )	// ���J�n
#define ENCOUNT_TR_WATER_LOW_ALPHA_E		( 16 )	// ���I��

#define ENCOUNT_TR_WATER_LOW_SCALE_S		( FX32_CONST( 1.0f ) )	// �g�k�J�n
#define ENCOUNT_TR_WATER_LOW_SCALE_E		( FX32_CONST( 0.01f ) )	// �g�k�I��

#define ENCOUNT_TR_WATER_LOW_SCALE_SS		( FX32_CONST( 0.1f ) )	// �g�k�����x
#define ENCOUNT_TR_WATER_LOW_SIN_R		( FX32_CONST( 12 ) )	// ���a
#define ENCOUNT_TR_WATER_LOW_LASTER_SP	( 800 )	// ���X�^�[�X�s�[�h
#define ENCOUNT_TR_WATER_LOW_SIN_ADDR	( (0xffff/192) * 2 )// ���X�^�[�p�x�X�s�[�h

#define ENCOUNT_TR_WATER_LOW_LASTER_TASK_PRI	( TCB_TSK_PRI - 1 )
#define ENCOUNT_TR_WATER_LOW_LASTER_FLIP_DOT	( 2 )

#define ENCOUNT_TR_WATER_LOW_CAMERA_DIST	( -FX32_CONST( 500 ) )	// �J�����ړ�����
#define ENCOUNT_TR_WATER_LOW_CAMERA_SS		( -FX32_CONST( 10 ) )	// �J���������x
#define ENCOUNT_TR_WATER_LOW_ROTA			( 0xffff )	// ��]�p



//-------------------------------------
//	�g���[�i�[�@���@���x����
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_TR_WATER_HIGH_START,
	ENCOUNT_TR_WATER_HIGH_FLASH_INI,
	ENCOUNT_TR_WATER_HIGH_FLASH_WAIT,
	ENCOUNT_TR_WATER_HIGH_OAM_0_S,
	ENCOUNT_TR_WATER_HIGH_OAM_1_S,
	ENCOUNT_TR_WATER_HIGH_OAM_2_S,
	ENCOUNT_TR_WATER_HIGH_OAM_WAIT,
	ENCOUNT_TR_WATER_HIGH_END,
};
// OAM�f�[�^
#define ENCOUNT_TR_WATER_HIGH_CELL_NUM		( 3 )
#define ENCOUNT_TR_WATER_HIGH_CELL_RES_NUM	( 1 )	// ���\�[�X��
#define ENCOUNT_TR_WATER_HIGH_CELL_CONT_ID	( 600000 )

// �����p�����[�^	�i�G���Ă悢�����j
#define ENCOUNT_TR_WATER_HIGH_MOVE_WAIT		( 14 )		// ���X�^�[��������܂ł̃E�G�C�g
#define ENCOUNT_TR_WATER_HIGH_CELLMOVE_SYNC	( 6 )		// �����V���N��
#define ENCOUNT_TR_WATER_HIGH_CELL0_WAIT	( 6 )		// �Z�������E�G�C�g
#define ENCOUNT_TR_WATER_HIGH_CELL1_WAIT	( 4 )		// �Z�������E�G�C�g
#define ENCOUNT_TR_WATER_HIGH_CELL2_WAIT	( 2 )		// �Z�������E�G�C�g
#define ENCOUNT_TR_WATER_HIGH_CELL0_X		( 43 )
#define ENCOUNT_TR_WATER_HIGH_CELL1_X		( 215 )
#define ENCOUNT_TR_WATER_HIGH_CELL2_X		( 129 )
#define ENCOUNT_TR_WATER_HIGH_CELL_Y		( 231 )		// OBJ�����J�n���W
#define ENCOUNT_TR_WATER_HIGH_BMP_Y			( 312 )		// BMP�����J�n���W
#define ENCOUNT_TR_WATER_HIGH_CELL_Y_E		( -32 )		// OBJ�����I�����W
#define ENCOUNT_TR_WATER_HIGH_BMP_Y_E		( 0 )		// BMP�����J�n���W

#define ENCOUNT_TR_WATER_HIGH_BMP_FILL_WIDTH	( 86 )	// �h��Ԃ���
#define ENCOUNT_TR_WATER_HIGH_BMP_FILL_HEIGHT	( 64 )	// �h��Ԃ�����
#define ENCOUNT_TR_WATER_HIGH_BMP_FILL_PLTT		( 0 )	// �p���b�g�O�Ԗڂ��g�p����
#define ENCOUNT_TR_WATER_HIGH_BMP_FILL_COL		( 15 )	// �h��Ԃ��J���[

#define ENCOUNT_TR_WATER_HIGH_SIN_R		( FX32_CONST( 12 ) )	// ���a
#define ENCOUNT_TR_WATER_HIGH_LASTER_SP	( 800 )	// ���X�^�[�X�s�[�h
#define ENCOUNT_TR_WATER_HIGH_SIN_ADDR	( (0xffff/192) * 2 )// ���X�^�[�p�x�X�s�[�h
#define ENCOUNT_TR_WATER_HIGH_LASTER_TASK_PRI	( TCB_TSK_PRI - 1 )
#define ENCOUNT_TR_WATER_HIGH_LASTER_FLIP_DOT	( 2 )

#define ENCOUNT_TR_WATER_HIGH_CAMERA_SYNC	( 16 )	// �J�����ړ�����
#define ENCOUNT_TR_WATER_HIGH_CAMERA_DIST	( -FX32_CONST( 500 ) )	// �J�����ړ�����
#define ENCOUNT_TR_WATER_HIGH_CAMERA_SS		( -FX32_CONST( 10 ) )	// �J���������x

#define ENCOUNT_TR_WATER_LOW_CELL0_ROTA	( 0xffff * 1 )	// ��]�p
#define ENCOUNT_TR_WATER_LOW_CELL1_ROTA	( 0xffff * -1 )	// ��]�p
#define ENCOUNT_TR_WATER_LOW_CELL2_ROTA	( 0xffff * 1 )	// ��]�p


//-------------------------------------
//	�g���[�i�[�@�_���@���x����
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_TR_DAN_LOW_START,
	ENCOUNT_TR_DAN_LOW_FLASH_INI,
	ENCOUNT_TR_DAN_LOW_FLASH_WAIT,
	ENCOUNT_TR_DAN_LOW_MOVE_Y,
	ENCOUNT_TR_DAN_LOW_MOVE_YWAIT,
	ENCOUNT_TR_DAN_LOW_WIPE,
	ENCOUNT_TR_DAN_LOW_WIPEWAIT,
	ENCOUNT_TR_DAN_LOW_END,
};
// OAM�f�[�^
#define ENCOUNT_TR_DAN_LOW_CELL_NUM		( 1 )
#define ENCOUNT_TR_DAN_LOW_CELL_RES_NUM	( 1 )	// ���\�[�X��
#define ENCOUNT_TR_DAN_LOW_CELL_CONT_ID	( 600000 )

// �����p�����[�^	�i�G���Ă悢�����j
#define ENCOUNT_TR_DAN_LOW_BALL_MOVE_SYNC	( 12 )	// �ړ��V���N
#define ENCOUNT_TR_DAN_LOW_BALL_WIPE_SYNC	( 8 )	// ���C�v�V���N
#define ENCOUNT_TR_DAN_LOW_BALL_MAT_X		( 128*FX32_ONE )// �J�n���W
#define ENCOUNT_TR_DAN_LOW_BALL_MAT_Y		( -32*FX32_ONE )	// �J�n���W
#define ENCOUNT_TR_DAN_LOW_BALL_MOVE_Y		( 256*FX32_ONE )	// �ړ�����
#define ENCOUNT_TR_DAN_LOW_BALL_MOVE_Y_SS	( 2*FX32_ONE )	// �����x
#define ENCOUNT_TR_DAN_LOW_BALL_SCALE_X_S	( FX32_CONST(0.10f) )// �g��J�n
#define ENCOUNT_TR_DAN_LOW_BALL_SCALE_X_E	( FX32_CONST(2.0f) )// �g��I��
#define ENCOUNT_TR_DAN_LOW_BALL_SCALE_X_SS	( FX32_CONST(0.0f) )// ���g�嗦
#define ENCOUNT_TR_DAN_LOW_BALL_SCALE_Y_S	( FX32_CONST(0.10f) )// �g��J�n
#define ENCOUNT_TR_DAN_LOW_BALL_SCALE_Y_E	( FX32_CONST(2.0f) )// �g��I��
#define ENCOUNT_TR_DAN_LOW_BALL_SCALE_Y_SS	( FX32_CONST(0.0f)	)// ���g�嗦

#define ENCOUNT_TR_DAN_LOW_CAMERA_DIST	( -FX32_CONST( 1000 ) )	// �J�����ړ�����
#define ENCOUNT_TR_DAN_LOW_CAMERA_SS		( FX32_CONST( 10 ) )	// �J���������x

#define ENCOUNT_TR_DAN_LOW_ROTA		( 0xffff * 1 )	// ��]�p

//-------------------------------------
//	�g���[�i�[�@�_���@���x����
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_TR_DAN_HIGH_START,
	ENCOUNT_TR_DAN_HIGH_FLASH_INI,
	ENCOUNT_TR_DAN_HIGH_FLASH_WAIT,
	ENCOUNT_TR_DAN_HIGH_MOVE_0Y,
	ENCOUNT_TR_DAN_HIGH_MOVE_1Y,
	ENCOUNT_TR_DAN_HIGH_MOVE_2Y,
	ENCOUNT_TR_DAN_HIGH_MOVE_YWAIT,
	ENCOUNT_TR_DAN_HIGH_WIPE,
	ENCOUNT_TR_DAN_HIGH_WIPE_WAIT,
	ENCOUNT_TR_DAN_HIGH_END,
};
// OAM�f�[�^
#define ENCOUNT_TR_DAN_HIGH_CELL_NUM		( 3 )
#define ENCOUNT_TR_DAN_HIGH_CELL_RES_NUM	( 1 )	// ���\�[�X��
#define ENCOUNT_TR_DAN_HIGH_CELL_CONT_ID	( 600000 )

#define ENCOUNT_TR_DAN_HIGH_BLOCK_FILLCOLOR	( 15 )	// �h��Ԃ�

// �����p�����[�^	�i�G���Ă悢�����j
#define ENCOUNT_TR_DAN_HIGH_BALL_MOVE_SYNC	( 5 )	// �ړ��V���N
#define ENCOUNT_TR_DAN_HIGH_BLOCK_SYNC		( 1 )	// ���C�v�V���N
#define ENCOUNT_TR_DAN_HIGH_BLOCK_START_SYNC	( 1 )	// ���C�v�V���N

#define ENCOUNT_TR_DAN_HIGH_BALL_WAIT_0		( 0 )// �J�n�҂�
#define ENCOUNT_TR_DAN_HIGH_BALL_WAIT_1		( 1 )// �J�n�҂�
#define ENCOUNT_TR_DAN_HIGH_BALL_WAIT_2		( 3 )// �J�n�҂�

#define ENCOUNT_TR_DAN_HIGH_BALL_MAT_0X		( 128 )// �J�n���W
#define ENCOUNT_TR_DAN_HIGH_BALL_MAT_1X		( 208 )// �J�n���W
#define ENCOUNT_TR_DAN_HIGH_BALL_MAT_2X		( 48 )// �J�n���W
#define ENCOUNT_TR_DAN_HIGH_BALL_MAT_Y		( -32 )// �J�n���W
#define ENCOUNT_TR_DAN_HIGH_BALL_MOVE_Y		( 224 )	// �ړ�����

#define ENCOUNT_TR_DAN_HIGH_CAMERA_SYNC	( 64 )	// �J�����ړ��V���N��48
#define ENCOUNT_TR_DAN_HIGH_CAMERA_DIST	( -FX32_CONST( 1000 ) )	// �J�����ړ�����
#define ENCOUNT_TR_DAN_HIGH_CAMERA_SS		( FX32_CONST( 10 ) )	// �J���������x

#define ENCOUNT_TR_DAN_HIGH_BALL0_ROTA	( 0xffff * 1 )
#define ENCOUNT_TR_DAN_HIGH_BALL1_ROTA	( 0xffff * -1 )
#define ENCOUNT_TR_DAN_HIGH_BALL2_ROTA	( 0xffff * 1 )


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�g���[�i�[�@���@���x����
//=====================================
typedef struct{
	ENC_ADDMOVE_WORK_FX oam_scale;
	ENC_MOVE_WORK	oam_rota;
	ENC_ADDMOVE_WORK_FX oam_slice;
	ENC_HB_BG_SLICE* p_slice;

	ENC_CLACT_SYS	clact_sys;
	ENC_CLACT_RES_WORK clact_res;
	CLACT_WORK_PTR clact[ ENCOUNT_TR_GRASS_LOW_CELL_NUM ];

	GF_CAMERA_PTR	camera;				// �J�����f�[�^
	ENC_ADDMOVE_WORK_FX camera_dist;

	s32 wait;
} ENCOUNT_TR_GRASS_LOW;

//-------------------------------------
//	�g���[�i�[�@���@���x����
//=====================================
typedef struct{
	ENC_MOVE_WORK_FX oam_slice;
	ENC_MOVE_WORK	oam_rota;
	ENC_HB_BG_WND_SLANT* p_slice;

	ENC_CLACT_SYS	clact_sys;
	ENC_CLACT_RES_WORK clact_res;
	CLACT_WORK_PTR clact[ ENCOUNT_TR_GRASS_HIGH_CELL_NUM ];

	GF_CAMERA_PTR	camera;				// �J�����f�[�^
	ENC_ADDMOVE_WORK_FX camera_dist;

	s32 wait;
} ENCOUNT_TR_GRASS_HIGH;

//-------------------------------------
//	�g���[�i�[�@���@���x����
//=====================================
typedef struct{
	ENC_ADDMOVE_WORK_FX oam_scale;
	ENC_MOVE_WORK		oam_alpha;
	ENC_MOVE_WORK	oam_rota;

	ENCOUNT_LASTER_SCROLL laster;
	BOOL laster_flg;

	ENC_CLACT_SYS	clact_sys;
	ENC_CLACT_RES_WORK clact_res;
	CLACT_WORK_PTR clact[ENCOUNT_TR_WATER_LOW_CELL_NUM];

	GF_CAMERA_PTR	camera;				// �J�����f�[�^
	ENC_ADDMOVE_WORK_FX camera_dist;

	s32 wait;
} ENCOUNT_TR_WATER_LOW;

//-------------------------------------
//	�g���[�i�[�@���@���x����
//=====================================
typedef struct{
	ENC_CLACT_SYS	clact_sys;
	ENC_CLACT_RES_WORK clact_res;
	CLACT_WORK_PTR clact[ ENCOUNT_TR_WATER_HIGH_CELL_NUM ];
	ENC_MOVE_WORK obj_move[ ENCOUNT_TR_WATER_HIGH_CELL_NUM ];
	ENC_MOVE_WORK	oam_rota[ ENCOUNT_TR_WATER_HIGH_CELL_NUM ];
	ENC_BMP_FILL_OBJ* p_bmp_fill[ ENCOUNT_TR_WATER_HIGH_CELL_NUM ];
	BOOL		obj_move_flg[ ENCOUNT_TR_WATER_HIGH_CELL_NUM ];
	GF_BGL_BMPWIN* p_bmp;

	ENCOUNT_LASTER_SCROLL laster;
	BOOL laster_flg;

	GF_CAMERA_PTR	camera;				// �J�����f�[�^
	ENC_ADDMOVE_WORK_FX camera_dist;

	s32 wait;
} ENCOUNT_TR_WATER_HIGH;

//-------------------------------------
//	�g���[�i�[�@�_���@���x����
//=====================================
typedef struct{
	ENC_ADDMOVE_WORK_FX		oam_move;
	ENC_ADDMOVE_WORK_FX		oam_scale_x;
	ENC_ADDMOVE_WORK_FX		oam_scale_y;
	ENC_MOVE_WORK			oam_rota;

	ENC_CLACT_SYS	clact_sys;
	ENC_CLACT_RES_WORK clact_res;
	CLACT_WORK_PTR clact;

	GF_CAMERA_PTR	camera;				// �J�����f�[�^
	ENC_ADDMOVE_WORK_FX camera_dist;

	s32 wait;
} ENCOUNT_TR_DAN_LOW;

//-------------------------------------
//	�g���[�i�[�@�_���@���x����
//=====================================
typedef struct{
	ENC_CLACT_SYS	clact_sys;
	ENC_CLACT_RES_WORK clact_res;
	CLACT_WORK_PTR clact[ ENCOUNT_TR_DAN_HIGH_CELL_NUM ];
	ENC_MOVE_WORK oam_move[ ENCOUNT_TR_DAN_HIGH_CELL_NUM ];
	ENC_MOVE_WORK oam_rota[ ENCOUNT_TR_DAN_HIGH_CELL_NUM ];
	BOOL oam_move_flg[ ENCOUNT_TR_DAN_HIGH_CELL_NUM ];
	
	GF_BGL_BMPWIN* p_bmp;
	ENC_BMP_FILL_BLOCK_MOVE* p_block;

	GF_CAMERA_PTR	camera;				// �J�����f�[�^
	ENC_ADDMOVE_WORK_FX camera_dist;

	s16 wait;
} ENCOUNT_TR_DAN_HIGH;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	�g���[�i�[�@���@���x����
 */
//-----------------------------------------------------------------------------
void EncountEffect_Trainer_GrassLevelLow(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_TR_GRASS_LOW* task_w = eew->work;
	BOOL result;
	fx32 dist;
	int i;
	VecFx32 scale;
	u16 last_rota;

	switch( eew->seq ){
	case ENCOUNT_TR_GRASS_LOW_START:
		eew->work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENCOUNT_TR_GRASS_LOW) );	
		memset( eew->work, 0, sizeof(ENCOUNT_TR_GRASS_LOW) );
		task_w = eew->work;

		// �J�����|�C���^�擾
		task_w->camera = eew->fsw->camera_ptr;

		// �X���C�X���[�N�쐬
		task_w->p_slice = ENC_BG_Slice_Alloc();

		// �Z���A�N�^�[�Z�b�g�쐬
		ENC_CLACT_Init( &task_w->clact_sys, ENCOUNT_TR_GRASS_LOW_CELL_NUM, ENCOUNT_TR_GRASS_LOW_CELL_RES_NUM );

		// �O���t�B�b�N�ݒ�
		ENC_CLACT_ResLoadEasy(
				&task_w->clact_sys,
				&task_w->clact_res,
				NARC_field_encounteffect_monsterball_NCLR, 1,
				NARC_field_encounteffect_monstarballbig_oam_NCGR,
				NARC_field_encounteffect_monsterballbig_oam_NCER,
				NARC_field_encounteffect_monsterballbig_oam_NANR,
				ENCOUNT_TR_GRASS_LOW_CELL_CONT_ID
				);

		// �A�N�^�[�o�^
		for( i=0; i<ENCOUNT_TR_GRASS_LOW_CELL_NUM; i++ ){
			task_w->clact[i] = ENC_CLACT_Add( 
					&task_w->clact_sys, &task_w->clact_res,
					ENCOUNT_TR_GRASS_LOW_BALL_MAT_X, 
					ENCOUNT_TR_GRASS_LOW_BALL_MAT_Y,0, 0);
			CLACT_SetDrawFlag( task_w->clact[i], FALSE );
			CLACT_DrawPriorityChg( task_w->clact[i], i*2 );
		}
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

		eew->seq ++;
		break;
		
	case ENCOUNT_TR_GRASS_LOW_FLASH_INI:

		EncountFlashTask(MASK_MAIN_DISPLAY, -16, -16,  &eew->wait, 2);
		eew->seq++;
		break;
		
	case ENCOUNT_TR_GRASS_LOW_FLASH_WAIT:
		if( eew->wait ){
			eew->seq++;
		}
		break;
		
	case ENCOUNT_TR_GRASS_LOW_BGSCALE:
		ENC_AddMoveReqFx( &task_w->oam_scale, 
				ENCOUNT_TR_GRASS_LOW_SCALE_S,
				ENCOUNT_TR_GRASS_LOW_SCALE_E,
				ENCOUNT_TR_GRASS_LOW_SCALE_SS,
				ENCOUNT_TR_GRASS_LOW_SCALE_SYNC );

		scale = ENC_MakeVec( task_w->oam_scale.x, 
				task_w->oam_scale.x, task_w->oam_scale.x );
		for( i=0; i<ENCOUNT_TR_GRASS_LOW_CELL_NUM; i++ ){
			CLACT_SetDrawFlag(
					task_w->clact[i],
					TRUE );
			CLACT_SetAffineParam(
					task_w->clact[i], 
					CLACT_AFFINE_DOUBLE );
			CLACT_SetScale( 
					task_w->clact[i], 
					&scale );
		}
		// ��]����
		ENC_MoveReq( &task_w->oam_rota, 
				0,
				ENCOUNT_TR_GRASS_LOW_ROTA_SCALE, 
				ENCOUNT_TR_GRASS_LOW_SCALE_SYNC );
		eew->seq++;
		break;

	case ENCOUNT_TR_GRASS_LOW_BGSCALE_WAIT:
		result = ENC_AddMoveMainFx( &task_w->oam_scale );
		scale = ENC_MakeVec( task_w->oam_scale.x, 
					task_w->oam_scale.x, task_w->oam_scale.x );

		// �P�O�̉�]�p
		last_rota = task_w->oam_rota.x;
		
		ENC_MoveMain( &task_w->oam_rota );

		for( i=0; i<ENCOUNT_TR_GRASS_LOW_CELL_NUM; i++ ){
			CLACT_SetScale( 
					task_w->clact[i], 
					&scale );
		}
		CLACT_SetRotation( 
				task_w->clact[ENCOUNT_TR_GRASS_LOW_CELL_BIG],
				0xffff & task_w->oam_rota.x );

		CLACT_SetRotation( 
				task_w->clact[ENCOUNT_TR_GRASS_LOW_CELL_BOTTOM],
				0xffff & (task_w->oam_rota.x - 0x100) );	// �����_�h�~�̈�-0x100
  
		if( result == TRUE ){
			eew->seq ++;
		}
		break;
		
	case ENCOUNT_TR_GRASS_LOW_BGCUT:
		// ����J�n
		ENC_BG_Slice_Start( eew, task_w->p_slice, 
				ENCOUNT_TR_GRASS_LOW_DOT,
				ENCOUNT_TR_GRASS_LOW_SLICE_SYNC, 
				0, ENCOUNT_TR_GRASS_LOW_SLICE_BGSL_X,
				ENCOUNT_TR_GRASS_LOW_SLICE_BGSL_SS );

		// �J�b�g�O���t�B�b�N��OAM��ύX
		CLACT_AnmChg( 
				task_w->clact[ENCOUNT_TR_GRASS_LOW_CELL_BIG], 
				1 );
		CLACT_AnmChg( 
				task_w->clact[ENCOUNT_TR_GRASS_LOW_CELL_BOTTOM], 
				2 );

		// OAM�X���C�h�����p�����[�^�쐬
		ENC_AddMoveReqFx( &task_w->oam_slice, 
				0,
				ENCOUNT_TR_GRASS_LOW_SLICE_BGSL_X,
				ENCOUNT_TR_GRASS_LOW_SLICE_BGSL_SS,
				ENCOUNT_TR_GRASS_LOW_SLICE_SYNC );
		
		// �J���������쐬
		dist = GFC_GetCameraDistance( task_w->camera );
		ENC_AddMoveReqFx( &task_w->camera_dist,
				dist,
				dist + ENCOUNT_TR_GRASS_LOW_CAMERA_DIST,
				ENCOUNT_TR_GRASS_LOW_CAMERA_SS,
				ENCOUNT_TR_GRASS_LOW_SLICE_SYNC );
		
		CLACT_SetRotation( 
				task_w->clact[ENCOUNT_TR_GRASS_LOW_CELL_BIG],
				0xffff & 0 );
		CLACT_SetRotation( 
				task_w->clact[ENCOUNT_TR_GRASS_LOW_CELL_BOTTOM],
				0xffff & 0 );

		eew->seq ++;
		break;
		
	case ENCOUNT_TR_GRASS_LOW_BGCUTWAIT:
		// OAM����
		result = ENC_AddMoveMainFx( &task_w->oam_slice );
		{
			VecFx32 mat = ENC_MakeVec( ENCOUNT_TR_GRASS_LOW_BALL_MAT_X - task_w->oam_slice.x, 
					ENCOUNT_TR_GRASS_LOW_BALL_MAT_Y, 0 );
			VecFx32 ret_mat = ENC_MakeVec( ENCOUNT_TR_GRASS_LOW_BALL_MAT_X + task_w->oam_slice.x, 
					ENCOUNT_TR_GRASS_LOW_BALL_MAT_Y, 0 );
			CLACT_SetMatrix( 
					task_w->clact[ENCOUNT_TR_GRASS_LOW_CELL_BIG], 
					&mat );
			CLACT_SetMatrix( 
					task_w->clact[ENCOUNT_TR_GRASS_LOW_CELL_BOTTOM], 
					&ret_mat );
		}

		// �J��������
		ENC_AddMoveMainFx( &task_w->camera_dist );
		GFC_SetCameraDistance( task_w->camera_dist.x, task_w->camera );

		if( ENC_HBlankEndCheck( eew ) ){
			eew->seq ++;
		}
		break;
		
	case ENCOUNT_TR_GRASS_LOW_END:
		WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		// OAM�j��
		{
			int i;
			for( i=0; i<ENCOUNT_TR_GRASS_LOW_CELL_NUM; i++ ){
				CLACT_Delete( task_w->clact[i] );
			}
		}
		ENC_CLACT_ResDeleteEasy( &task_w->clact_sys, &task_w->clact_res );
		ENC_CLACT_Delete( &task_w->clact_sys );
		ENC_BG_Slice_Delete( task_w->p_slice );
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		break;
	}

	if( eew->seq != ENCOUNT_TR_GRASS_LOW_END ){
		CLACT_Draw( task_w->clact_sys.cas );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�g���[�i�[�@���@���x����
 */
//-----------------------------------------------------------------------------
void EncountEffect_Trainer_GrassLevelHigh(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_TR_GRASS_HIGH* task_w = eew->work;
	BOOL result;
	fx32 dist;

	switch( eew->seq ){
	case ENCOUNT_TR_GRASS_HIGH_START:
		eew->work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENCOUNT_TR_GRASS_HIGH) );	
		memset( eew->work, 0, sizeof(ENCOUNT_TR_GRASS_HIGH) );
		task_w = eew->work;

		// �J�����|�C���^�擾
		task_w->camera = eew->fsw->camera_ptr;

		// �X���C�X���[�N�쐬
		task_w->p_slice = ENC_BG_WndSlant_Alloc();

		// �Z���A�N�^�[�Z�b�g�쐬
		ENC_CLACT_Init( &task_w->clact_sys, ENCOUNT_TR_GRASS_HIGH_CELL_NUM, ENCOUNT_TR_GRASS_HIGH_CELL_RES_NUM );

		// �O���t�B�b�N�ݒ�
		ENC_CLACT_ResLoadEasy(
				&task_w->clact_sys,
				&task_w->clact_res,
				NARC_field_encounteffect_monsterball_NCLR, 1,
				NARC_field_encounteffect_monstaerball_oam_NCGR,
				NARC_field_encounteffect_monsterball_oam_NCER,
				NARC_field_encounteffect_monsterball_oam_NANR,
				ENCOUNT_TR_GRASS_HIGH_CELL_CONT_ID
				);

		// �A�N�^�[�o�^
		{
			int i;
			for( i=0; i<ENCOUNT_TR_GRASS_HIGH_CELL_NUM; i++ ){
				task_w->clact[i] = ENC_CLACT_Add( 
						&task_w->clact_sys, &task_w->clact_res,
						ENCOUNT_TR_GRASS_HIGH_BALL_MAT_X, 
						0,0, 0);
				CLACT_SetDrawFlag( task_w->clact[i], FALSE );
				CLACT_SetAffineParam( task_w->clact[i], CLACT_AFFINE_DOUBLE );
			}
		}
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

		eew->seq ++;
		break;
		
	case ENCOUNT_TR_GRASS_HIGH_FLASH_INI:

		EncountFlashTask(MASK_MAIN_DISPLAY, 16, -16,  &eew->wait, 2);
		eew->seq++;
		break;
		
	case ENCOUNT_TR_GRASS_HIGH_FLASH_WAIT:
		if( eew->wait ){
			eew->seq++;
		}
		break;
		
	case ENCOUNT_TR_GRASS_HIGH_OAM_MOVE:
		ENC_MoveReqFx( &task_w->oam_slice, 
				ENCOUNT_TR_GRASS_HIGH_BALLMOVE_S,
				ENCOUNT_TR_GRASS_HIGH_BALLMOVE_E,
				ENCOUNT_TR_GRASS_HIGH_MOVE_SYNC );
		CLACT_SetDrawFlag(
				task_w->clact[ENCOUNT_TR_GRASS_HIGH_CELL_UP],
				TRUE );
		CLACT_SetDrawFlag(
				task_w->clact[ENCOUNT_TR_GRASS_HIGH_CELL_DOWN],
				TRUE );

		{
			VecFx32 mat = ENC_MakeVec( ENCOUNT_TR_GRASS_HIGH_BALL_MAT_X - task_w->oam_slice.x, 
					ENCOUNT_TR_GRASS_HIGH_BALL_MAT_Y_UP, 0 );
			VecFx32 ret_mat = ENC_MakeVec( ENCOUNT_TR_GRASS_HIGH_BALL_MAT_X + task_w->oam_slice.x, 
					ENCOUNT_TR_GRASS_HIGH_BALL_MAT_Y_DOWN, 0 );
			CLACT_SetMatrix( 
					task_w->clact[ENCOUNT_TR_GRASS_HIGH_CELL_UP], 
					&mat );
			CLACT_SetMatrix( 
					task_w->clact[ENCOUNT_TR_GRASS_HIGH_CELL_DOWN], 
					&ret_mat );
		}

		// ��]����
		ENC_MoveReq( &task_w->oam_rota,
				0, ENCOUNT_TR_GRASS_HIGH_ROTA,
				ENCOUNT_TR_GRASS_HIGH_MOVE_SYNC );
		
		eew->seq++;
		break;

	case ENCOUNT_TR_GRASS_HIGH_OAM_MOVEWAIT:
		result = ENC_MoveMainFx( &task_w->oam_slice );

		{
			VecFx32 mat = ENC_MakeVec( ENCOUNT_TR_GRASS_HIGH_BALL_MAT_X - task_w->oam_slice.x, 
					ENCOUNT_TR_GRASS_HIGH_BALL_MAT_Y_UP, 0 );
			VecFx32 ret_mat = ENC_MakeVec( ENCOUNT_TR_GRASS_HIGH_BALL_MAT_X + task_w->oam_slice.x, 
					ENCOUNT_TR_GRASS_HIGH_BALL_MAT_Y_DOWN, 0 );
			CLACT_SetMatrix( 
					task_w->clact[ENCOUNT_TR_GRASS_HIGH_CELL_UP], 
					&mat );
			CLACT_SetMatrix( 
					task_w->clact[ENCOUNT_TR_GRASS_HIGH_CELL_DOWN], 
					&ret_mat );
		}

		ENC_MoveMain( &task_w->oam_rota );
		CLACT_SetRotation( 
				task_w->clact[ENCOUNT_TR_GRASS_HIGH_CELL_UP],
				task_w->oam_rota.x );
		CLACT_SetRotation( 
				task_w->clact[ENCOUNT_TR_GRASS_HIGH_CELL_DOWN],
				-task_w->oam_rota.x );

		if( result == TRUE ){
			eew->seq ++;
		}
		break;
		
	case ENCOUNT_TR_GRASS_HIGH_BGCUT:
		// ����J�n
		ENC_BG_WndSlant_Start( eew, task_w->p_slice, 
				 ENCOUNT_TR_GRASS_HIGH_SLICE_SYNC,
				 ENCOUNT_TR_GRASS_HIGH_SLICE_BGSL_SS_X,
				 ENCOUNT_TR_GRASS_HIGH_SLICE_BGSL_SS_Y);

		// �J���������쐬
		dist = GFC_GetCameraDistance( task_w->camera );
		ENC_AddMoveReqFx( &task_w->camera_dist,
				dist,
				dist + ENCOUNT_TR_GRASS_HIGH_CAMERA_DIST,
				ENCOUNT_TR_GRASS_HIGH_CAMERA_SS,
				ENCOUNT_TR_GRASS_HIGH_SLICE_SYNC );

		eew->seq ++;
		break;
		
	case ENCOUNT_TR_GRASS_HIGH_BGCUTWAIT:

		// �J��������
		ENC_AddMoveMainFx( &task_w->camera_dist );
		GFC_SetCameraDistance( task_w->camera_dist.x, task_w->camera );

		if( ENC_HBlankEndCheck( eew ) == TRUE ){
			eew->seq ++;
		}
		break;
		
	case ENCOUNT_TR_GRASS_HIGH_END:
		WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		// OAM�j��
		{
			int i;
			for( i=0; i<ENCOUNT_TR_GRASS_HIGH_CELL_NUM; i++ ){
				CLACT_Delete( task_w->clact[i] );
			}
		}
		ENC_CLACT_ResDeleteEasy( &task_w->clact_sys, &task_w->clact_res );
		ENC_CLACT_Delete( &task_w->clact_sys );
		ENC_BG_WndSlant_Delete( task_w->p_slice );
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		break;
	}

	if( eew->seq != ENCOUNT_TR_GRASS_HIGH_END ){
		CLACT_Draw( task_w->clact_sys.cas );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�g���[�i�[�@���@���x����
 */
//-----------------------------------------------------------------------------
void EncountEffect_Trainer_WaterLevelLow(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_TR_WATER_LOW* task_w = eew->work;
	BOOL result;
	BOOL result2;
	fx32 dist;
	int i;
	u16 last_rota;


	switch( eew->seq ){
	case ENCOUNT_TR_WATER_LOW_START:
		eew->work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENCOUNT_TR_WATER_LOW) );	
		memset( eew->work, 0, sizeof(ENCOUNT_TR_WATER_LOW) );
		task_w = eew->work;

		// �J�����|�C���^�擾
		task_w->camera = eew->fsw->camera_ptr;

		// ���X�^�[������
		EF_Laster_Init( &task_w->laster, HEAPID_FIELD );
		task_w->wait = ENCOUNT_TR_WATER_LOW_MOVE_WAIT;

		// �Z���A�N�^�[�Z�b�g�쐬
		ENC_CLACT_Init( &task_w->clact_sys, ENCOUNT_TR_WATER_LOW_CELL_NUM, ENCOUNT_TR_WATER_LOW_CELL_RES_NUM );

		// �O���t�B�b�N�ݒ�
		ENC_CLACT_ResLoadEasy(
				&task_w->clact_sys,
				&task_w->clact_res,
				NARC_field_encounteffect_monsterball_NCLR, 1,
				NARC_field_encounteffect_monstarballbig_oam_NCGR,
				NARC_field_encounteffect_monsterballbig_oam_NCER,
				NARC_field_encounteffect_monsterballbig_oam_NANR,
				ENCOUNT_TR_WATER_LOW_CELL_CONT_ID
				);

		// �A�N�^�[�o�^
		for( i=0; i<ENCOUNT_TR_WATER_LOW_CELL_NUM; i++ ){
			task_w->clact[i] = ENC_CLACT_Add( 
					&task_w->clact_sys, &task_w->clact_res,
					ENCOUNT_TR_WATER_LOW_BALL_MAT_X, 
					ENCOUNT_TR_WATER_LOW_BALL_MAT_Y, 0, 0);
			CLACT_SetDrawFlag( task_w->clact[i], FALSE );
			CLACT_DrawPriorityChg( task_w->clact[i], i );
		}
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

		eew->seq ++;
		break;
		
	case ENCOUNT_TR_WATER_LOW_FLASH_INI:

		EncountFlashTask(MASK_MAIN_DISPLAY, -16, -16,  &eew->wait, 2);
		eew->seq++;
		break;
		
	case ENCOUNT_TR_WATER_LOW_FLASH_WAIT:
		task_w->wait--;
		if( task_w->wait == 0 ){
			EF_Laster_Start( &task_w->laster,
					0, 191, ENCOUNT_TR_WATER_LOW_SIN_ADDR, 
					ENCOUNT_TR_WATER_LOW_SIN_R, ENCOUNT_TR_WATER_LOW_LASTER_SP,
					LASTER_SCROLL_MBG0, 0, ENCOUNT_TR_WATER_LOW_LASTER_TASK_PRI );
			task_w->laster_flg = TRUE;
		}
		if( eew->wait ){
			eew->seq++;
		}
		break;

	case ENCOUNT_TR_WATER_LOW_OAM_FADEIN:
		ENC_MoveReq( &task_w->oam_alpha, 
				ENCOUNT_TR_WATER_LOW_ALPHA_S, ENCOUNT_TR_WATER_LOW_ALPHA_E,
				ENCOUNT_TR_WATER_LOW_ALPHA_SYNC );
		G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE, 
				GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3,
				task_w->oam_alpha.x, 16 - task_w->oam_alpha.x );

		for( i=0; i<ENCOUNT_TR_WATER_LOW_CELL_NUM; i++ ){
			CLACT_SetDrawFlag(
					task_w->clact[i],
					TRUE );

			CLACT_SetAffineParam(
					task_w->clact[i], 
					CLACT_AFFINE_DOUBLE );
			CLACT_ObjModeSet( task_w->clact[i], GX_OAM_MODE_XLU );
		}

		// ��]
		ENC_MoveReq( &task_w->oam_rota,
				0,
				ENCOUNT_TR_WATER_LOW_ROTA,
				ENCOUNT_TR_WATER_LOW_SCALE_SYNC );

		eew->seq++;
		break;
		
	case ENCOUNT_TR_WATER_LOW_OAM_FADEINWAIT:
		result = ENC_MoveMain( &task_w->oam_alpha );
		G2_ChangeBlendAlpha( task_w->oam_alpha.x, 16 - task_w->oam_alpha.x );

		last_rota = task_w->oam_rota.x;
		result2 = ENC_MoveMain( &task_w->oam_rota );

		if( result2 == FALSE ){
			CLACT_SetRotation( task_w->clact[0], 0xffff & task_w->oam_rota.x );
			CLACT_SetRotation( task_w->clact[1], 0xffff & last_rota );
		}else{
			CLACT_SetRotation( task_w->clact[0], 0 );
			CLACT_SetRotation( task_w->clact[1], 0 );
		}

		if( result == TRUE ){
			G2_BlendNone();
			for( i=0; i<ENCOUNT_TR_WATER_LOW_CELL_NUM; i++ ){
				CLACT_ObjModeSet( task_w->clact[i], GX_OAM_MODE_NORMAL );
			}
			eew->seq++;
		}
		break;

	case ENCOUNT_TR_WATER_LOW_OAM_SCALE:

		ENC_AddMoveReqFx( &task_w->oam_scale, 
				ENCOUNT_TR_WATER_LOW_SCALE_S,
				ENCOUNT_TR_WATER_LOW_SCALE_E,
				ENCOUNT_TR_WATER_LOW_SCALE_SS,
				ENCOUNT_TR_WATER_LOW_SCALE_SYNC );

		{
			VecFx32 scale = ENC_MakeVec( task_w->oam_scale.x, 
					task_w->oam_scale.x, task_w->oam_scale.x );
			for( i=0; i<ENCOUNT_TR_WATER_LOW_CELL_NUM; i++ ){
				CLACT_SetScale( 
						task_w->clact[i], 
						&scale );
			}
		}


		// �J���������쐬
		dist = GFC_GetCameraDistance( task_w->camera );
		ENC_AddMoveReqFx( &task_w->camera_dist,
				dist,
				dist + ENCOUNT_TR_WATER_LOW_CAMERA_DIST,
				ENCOUNT_TR_WATER_LOW_CAMERA_SS,
				ENCOUNT_TR_WATER_LOW_SCALE_SYNC );

		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_BOXOUT_INSIDE, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, ENCOUNT_TR_WATER_LOW_SCALE_SYNC, 1, HEAPID_FIELD );
		eew->seq++;
		break;
		
	case ENCOUNT_TR_WATER_LOW_OAM_SCALEWAIT:
		result = ENC_AddMoveMainFx( &task_w->oam_scale );
		{
			VecFx32 scale = ENC_MakeVec( task_w->oam_scale.x, 
					task_w->oam_scale.x, task_w->oam_scale.x );
			for( i=0; i<ENCOUNT_TR_WATER_LOW_CELL_NUM; i++ ){
				CLACT_SetScale( 
						task_w->clact[i], 
						&scale );
			}
		}

		// �J��������
		ENC_AddMoveMainFx( &task_w->camera_dist );
		GFC_SetCameraDistance( task_w->camera_dist.x, task_w->camera );

		if( (result == TRUE) && ( WIPE_SYS_EndCheck() == TRUE ) ){
			eew->seq ++;
		}
		break;
		
	case ENCOUNT_TR_WATER_LOW_END:
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}

		// ���X�^�[�j��
		EF_Laster_Delete( &task_w->laster );
		task_w->laster_flg = FALSE;
		
		// OAM�j��
		for( i=0; i<ENCOUNT_TR_WATER_LOW_CELL_NUM; i++ ){
			CLACT_Delete( task_w->clact[i] );
		}
		ENC_CLACT_ResDeleteEasy( &task_w->clact_sys, &task_w->clact_res );
		ENC_CLACT_Delete( &task_w->clact_sys );
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		return ;
	}

	// ���X�^�[�t���b�v�@�\
	if( task_w->laster_flg == TRUE ){
		EF_Laster_BuffXFlip( &task_w->laster, ENCOUNT_TR_WATER_LOW_LASTER_FLIP_DOT );
	}


	if( eew->seq != ENCOUNT_TR_WATER_LOW_END ){
		CLACT_Draw( task_w->clact_sys.cas );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�g���[�i�[�@���@���x����
 */
//-----------------------------------------------------------------------------
void EncountEffect_Trainer_WaterLevelHigh(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_TR_WATER_HIGH* task_w = eew->work;
	BOOL result;
	int i;
	VecFx32 matrix;
	fx32 dist;


	switch( eew->seq ){
	case ENCOUNT_TR_WATER_HIGH_START:
		eew->work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENCOUNT_TR_WATER_HIGH) );	
		memset( eew->work, 0, sizeof(ENCOUNT_TR_WATER_HIGH) );
		task_w = eew->work;

		// �J�����|�C���^�擾
		task_w->camera = eew->fsw->camera_ptr;

		// ���X�^�[������
		EF_Laster_Init( &task_w->laster, HEAPID_FIELD );
		task_w->wait = ENCOUNT_TR_WATER_HIGH_MOVE_WAIT;

		// �Z���A�N�^�[�Z�b�g�쐬
		ENC_CLACT_Init( &task_w->clact_sys, ENCOUNT_TR_WATER_HIGH_CELL_NUM, ENCOUNT_TR_WATER_HIGH_CELL_RES_NUM );

		// �O���t�B�b�N�ݒ�
		ENC_CLACT_ResLoadEasy(
				&task_w->clact_sys,
				&task_w->clact_res,
				NARC_field_encounteffect_monsterball_NCLR, 1,
				NARC_field_encounteffect_monstaerball_oam_NCGR,
				NARC_field_encounteffect_monsterball_oam_NCER,
				NARC_field_encounteffect_monsterball_oam_NANR,
				ENCOUNT_TR_WATER_HIGH_CELL_CONT_ID
				);

		// �A�N�^�[�o�^��BMP�h��Ԃ��I�u�W�F
		for( i=0; i<ENCOUNT_TR_WATER_HIGH_CELL_NUM; i++ ){
			task_w->clact[i] = ENC_CLACT_Add( 
					&task_w->clact_sys, &task_w->clact_res,
					0, 0, 0, 0);
			CLACT_SetDrawFlag( task_w->clact[i], FALSE );
			CLACT_SetAffineParam( task_w->clact[i], CLACT_AFFINE_DOUBLE );

			task_w->p_bmp_fill[i] = ENC_BMP_FillObjAlloc( HEAPID_FIELD );
		}
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

		// �r�b�g�}�b�v�쐬
		task_w->p_bmp = GF_BGL_BmpWinAllocGet( HEAPID_FIELD, 1 );
		GF_BGL_BmpWinAdd( eew->fsw->bgl, task_w->p_bmp, GF_BGL_FRAME3_M, 0, 0, 32, 32, 0, 0 );

		// �J���[�p���b�g�]��
		{
			GXRgb color = 0;
			GF_BGL_PaletteSet( GF_BGL_FRAME3_M, &color, sizeof(short), 2*ENCOUNT_TR_WATER_HIGH_BMP_FILL_COL );
		}

		GF_BGL_BmpWinDataFill( task_w->p_bmp, 0 );
		GF_BGL_BmpWinOnVReq( task_w->p_bmp );

		eew->seq ++;
		break;
		
	case ENCOUNT_TR_WATER_HIGH_FLASH_INI:

		EncountFlashTask(MASK_MAIN_DISPLAY, 16, -16,  &eew->wait, 2);
		eew->seq++;
		break;
		
	case ENCOUNT_TR_WATER_HIGH_FLASH_WAIT:
		task_w->wait--;
		if( task_w->wait == 0 ){
			EF_Laster_Start( &task_w->laster,
					0, 191, ENCOUNT_TR_WATER_HIGH_SIN_ADDR, 
					ENCOUNT_TR_WATER_HIGH_SIN_R, ENCOUNT_TR_WATER_HIGH_LASTER_SP,
					LASTER_SCROLL_MBG0, 0, ENCOUNT_TR_WATER_HIGH_LASTER_TASK_PRI );
			task_w->laster_flg = TRUE;
		}
		if( eew->wait ){
			task_w->wait = ENCOUNT_TR_WATER_HIGH_CELL0_WAIT;
			eew->seq++;
		}
		break;

	case ENCOUNT_TR_WATER_HIGH_OAM_0_S:
		task_w->wait --;
		if( task_w->wait >= 0 ){
			// wait���}�C�i�X�ɂȂ�̂�҂�
			break;
		}

		// �J���������쐬
		dist = GFC_GetCameraDistance( task_w->camera );
		ENC_AddMoveReqFx( &task_w->camera_dist,
				dist,
				dist + ENCOUNT_TR_WATER_HIGH_CAMERA_DIST,
				ENCOUNT_TR_WATER_HIGH_CAMERA_SS,
				ENCOUNT_TR_WATER_HIGH_CAMERA_SYNC );

		// ��]����
		ENC_MoveReq( &task_w->oam_rota[0], 
				0,
				ENCOUNT_TR_WATER_LOW_CELL0_ROTA,
				ENCOUNT_TR_WATER_HIGH_CELLMOVE_SYNC );
		
		ENC_MoveReq( &task_w->obj_move[0], ENCOUNT_TR_WATER_HIGH_CELL_Y, ENCOUNT_TR_WATER_HIGH_CELL_Y_E, ENCOUNT_TR_WATER_HIGH_CELLMOVE_SYNC );
		
		ENC_BMP_FillObjStart( task_w->p_bmp_fill[0], 
				ENCOUNT_TR_WATER_HIGH_CELL0_X, ENCOUNT_TR_WATER_HIGH_CELL0_X,
				ENCOUNT_TR_WATER_HIGH_BMP_Y, ENCOUNT_TR_WATER_HIGH_BMP_Y_E,
				ENCOUNT_TR_WATER_HIGH_CELLMOVE_SYNC,
				task_w->p_bmp, 
				ENCOUNT_TR_WATER_HIGH_BMP_FILL_WIDTH,
				ENCOUNT_TR_WATER_HIGH_BMP_FILL_HEIGHT,
				ENCOUNT_TR_WATER_HIGH_BMP_FILL_COL );

		matrix = ENC_MakeVec( 
				ENCOUNT_TR_WATER_HIGH_CELL0_X * FX32_ONE, 
				ENCOUNT_TR_WATER_HIGH_CELL_Y * FX32_ONE, 0 );
		CLACT_SetMatrix( task_w->clact[0], &matrix );
		CLACT_SetDrawFlag( task_w->clact[0], TRUE );
		task_w->obj_move_flg[0] = TRUE;
		eew->seq ++;
		task_w->wait = ENCOUNT_TR_WATER_HIGH_CELL1_WAIT;
		break;
		
	case ENCOUNT_TR_WATER_HIGH_OAM_1_S:
		task_w->wait --;
		if( task_w->wait >= 0 ){
			// wait���}�C�i�X�ɂȂ�̂�҂�
			break;
		}
		
		ENC_MoveReq( &task_w->obj_move[1], ENCOUNT_TR_WATER_HIGH_CELL_Y, ENCOUNT_TR_WATER_HIGH_CELL_Y_E, ENCOUNT_TR_WATER_HIGH_CELLMOVE_SYNC );

		// ��]����
		ENC_MoveReq( &task_w->oam_rota[1], 
				0,
				ENCOUNT_TR_WATER_LOW_CELL1_ROTA,
				ENCOUNT_TR_WATER_HIGH_CELLMOVE_SYNC );

		ENC_BMP_FillObjStart( task_w->p_bmp_fill[1], 
				ENCOUNT_TR_WATER_HIGH_CELL1_X, ENCOUNT_TR_WATER_HIGH_CELL1_X,
				ENCOUNT_TR_WATER_HIGH_BMP_Y, ENCOUNT_TR_WATER_HIGH_BMP_Y_E,
				ENCOUNT_TR_WATER_HIGH_CELLMOVE_SYNC,
				task_w->p_bmp, 
				ENCOUNT_TR_WATER_HIGH_BMP_FILL_WIDTH,
				ENCOUNT_TR_WATER_HIGH_BMP_FILL_HEIGHT,
				ENCOUNT_TR_WATER_HIGH_BMP_FILL_COL );
		matrix = ENC_MakeVec( 
				ENCOUNT_TR_WATER_HIGH_CELL1_X * FX32_ONE, 
				ENCOUNT_TR_WATER_HIGH_CELL_Y * FX32_ONE, 1 );
		CLACT_SetMatrix( task_w->clact[1], &matrix );
		CLACT_SetDrawFlag( task_w->clact[1], TRUE );
		task_w->obj_move_flg[1] = TRUE;
		eew->seq ++;
		task_w->wait = ENCOUNT_TR_WATER_HIGH_CELL2_WAIT;
		break;
		
	case ENCOUNT_TR_WATER_HIGH_OAM_2_S:
		task_w->wait --;
		if( task_w->wait >= 0 ){
			// wait���}�C�i�X�ɂȂ�̂�҂�
			break;
		}
		
		ENC_MoveReq( &task_w->obj_move[2], ENCOUNT_TR_WATER_HIGH_CELL_Y, ENCOUNT_TR_WATER_HIGH_CELL_Y_E, ENCOUNT_TR_WATER_HIGH_CELLMOVE_SYNC );

		// ��]����
		ENC_MoveReq( &task_w->oam_rota[2], 
				0,
				ENCOUNT_TR_WATER_LOW_CELL2_ROTA,
				ENCOUNT_TR_WATER_HIGH_CELLMOVE_SYNC );

		ENC_BMP_FillObjStart( task_w->p_bmp_fill[2], 
				ENCOUNT_TR_WATER_HIGH_CELL2_X, ENCOUNT_TR_WATER_HIGH_CELL2_X,
				ENCOUNT_TR_WATER_HIGH_BMP_Y, ENCOUNT_TR_WATER_HIGH_BMP_Y_E,
				ENCOUNT_TR_WATER_HIGH_CELLMOVE_SYNC,
				task_w->p_bmp, 
				ENCOUNT_TR_WATER_HIGH_BMP_FILL_WIDTH,
				ENCOUNT_TR_WATER_HIGH_BMP_FILL_HEIGHT,
				ENCOUNT_TR_WATER_HIGH_BMP_FILL_COL );
		matrix = ENC_MakeVec( 
				ENCOUNT_TR_WATER_HIGH_CELL2_X * FX32_ONE, 
				ENCOUNT_TR_WATER_HIGH_CELL_Y * FX32_ONE, 2 );
		CLACT_SetMatrix( task_w->clact[2], &matrix );
		CLACT_SetDrawFlag( task_w->clact[2], TRUE );
		task_w->obj_move_flg[2] = TRUE;

		eew->seq ++;
		break;
		
	case ENCOUNT_TR_WATER_HIGH_OAM_WAIT:

		// �J��������
		ENC_AddMoveMainFx( &task_w->camera_dist );
		GFC_SetCameraDistance( task_w->camera_dist.x, task_w->camera );
		
		// �S���������`�F�b�N
		if( (task_w->obj_move_flg[0] == FALSE) &&
			(task_w->obj_move_flg[1] == FALSE) &&
			(task_w->obj_move_flg[2] == FALSE)	){
			eew->seq ++;
		}
		break;
		
	case ENCOUNT_TR_WATER_HIGH_END:
		WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}

		// ���X�^�[�j��
		EF_Laster_Delete( &task_w->laster );
		task_w->laster_flg = FALSE;
		
		// OAM�j��	�r�b�g�}�b�v�h��Ԃ��I�u�W�F�j��
		for( i=0; i<ENCOUNT_TR_WATER_HIGH_CELL_NUM; i++ ){
			CLACT_Delete( task_w->clact[i] );
			ENC_BMP_FillObjDelete( task_w->p_bmp_fill[i] );	
		}
		ENC_CLACT_ResDeleteEasy( &task_w->clact_sys, &task_w->clact_res );
		ENC_CLACT_Delete( &task_w->clact_sys );

		// �r�b�g�}�b�v�j��
		GF_BGL_BmpWinOff( task_w->p_bmp );
		GF_BGL_BmpWinDel( task_w->p_bmp );
		GF_BGL_BmpWinFree( task_w->p_bmp, 1 );

		// �X�N���[���N���[��
		GF_BGL_ClearCharSet( GF_BGL_FRAME3_M, 32, 0, HEAPID_FIELD );
		GF_BGL_ScrClear( eew->fsw->bgl, GF_BGL_FRAME3_M );
		
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		return ;
	}

	// ���X�^�[�t���b�v�@�\
	if( task_w->laster_flg == TRUE ){
		EF_Laster_BuffXFlip( &task_w->laster, ENCOUNT_TR_WATER_HIGH_LASTER_FLIP_DOT );
	}

	// �I�u�W�F�N�g����
	for( i=0; i<ENCOUNT_TR_WATER_HIGH_CELL_NUM; i++ ){
		
		if( task_w->obj_move_flg[i] == TRUE ){
			const VecFx32* cp_mat;
			VecFx32 mat;
			
			result = ENC_BMP_FillObjMain( task_w->p_bmp_fill[i] );
			if( result ){
				task_w->obj_move_flg[i] = FALSE;
			}
			ENC_MoveMain( &task_w->obj_move[i] );
			ENC_MoveMain( &task_w->oam_rota[i] );

			CLACT_SetRotation( task_w->clact[i], task_w->oam_rota[i].x );
			
			cp_mat = CLACT_GetMatrix( task_w->clact[i] );
			mat = *cp_mat;
			mat.y = task_w->obj_move[i].x * FX32_ONE;
			CLACT_SetMatrix( task_w->clact[i], &mat );
		}
	}
	// �]�����N�G�X�g
	GF_BGL_BmpWinOnVReq( task_w->p_bmp );

	if( eew->seq != ENCOUNT_TR_WATER_HIGH_END ){
		CLACT_Draw( task_w->clact_sys.cas );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�g���[�i�[�@�_���W�����@���x����
 */
//-----------------------------------------------------------------------------
void EncountEffect_Trainer_DanLevelLow(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_TR_DAN_LOW* task_w = eew->work;
	BOOL result;
	fx32 dist;
	VecFx32 scale;

	switch( eew->seq ){
	case ENCOUNT_TR_DAN_LOW_START:
		eew->work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENCOUNT_TR_DAN_LOW) );	
		memset( eew->work, 0, sizeof(ENCOUNT_TR_DAN_LOW) );
		task_w = eew->work;

		// �J�����|�C���^�擾
		task_w->camera = eew->fsw->camera_ptr;

		// �Z���A�N�^�[�Z�b�g�쐬
		ENC_CLACT_Init( &task_w->clact_sys, ENCOUNT_TR_DAN_LOW_CELL_NUM, ENCOUNT_TR_DAN_LOW_CELL_RES_NUM );

		// �O���t�B�b�N�ݒ�
		ENC_CLACT_ResLoadEasy(
				&task_w->clact_sys,
				&task_w->clact_res,
				NARC_field_encounteffect_monsterball_NCLR, 1,
				NARC_field_encounteffect_monstaerball_oam_NCGR,
				NARC_field_encounteffect_monsterball_oam_NCER,
				NARC_field_encounteffect_monsterball_oam_NANR,
				ENCOUNT_TR_DAN_LOW_CELL_CONT_ID
				);

		// �A�N�^�[�o�^
		task_w->clact = ENC_CLACT_Add( 
				&task_w->clact_sys, &task_w->clact_res,
				ENCOUNT_TR_DAN_LOW_BALL_MAT_X, 
				ENCOUNT_TR_DAN_LOW_BALL_MAT_Y, 0, 0);
		CLACT_SetDrawFlag( task_w->clact, FALSE );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

		eew->seq ++;
		break;
		
	case ENCOUNT_TR_DAN_LOW_FLASH_INI:

		EncountFlashTask(MASK_MAIN_DISPLAY, -16, -16,  &eew->wait, 2);
		eew->seq++;
		break;
		
	case ENCOUNT_TR_DAN_LOW_FLASH_WAIT:
		if( eew->wait ){
			eew->seq++;
		}
		break;

	case ENCOUNT_TR_DAN_LOW_MOVE_Y:
		ENC_AddMoveReqFx( &task_w->oam_move, 0, 
				ENCOUNT_TR_DAN_LOW_BALL_MOVE_Y, 
				ENCOUNT_TR_DAN_LOW_BALL_MOVE_Y_SS,
				ENCOUNT_TR_DAN_LOW_BALL_MOVE_SYNC );
		CLACT_SetDrawFlag(
				task_w->clact,
				TRUE );

		ENC_AddMoveReqFx( &task_w->oam_scale_x,
				ENCOUNT_TR_DAN_LOW_BALL_SCALE_X_S, 
				ENCOUNT_TR_DAN_LOW_BALL_SCALE_X_E, 
				ENCOUNT_TR_DAN_LOW_BALL_SCALE_X_SS,
				ENCOUNT_TR_DAN_LOW_BALL_MOVE_SYNC );

		ENC_AddMoveReqFx( &task_w->oam_scale_y,
				ENCOUNT_TR_DAN_LOW_BALL_SCALE_Y_S, 
				ENCOUNT_TR_DAN_LOW_BALL_SCALE_Y_E, 
				ENCOUNT_TR_DAN_LOW_BALL_SCALE_Y_SS,
				ENCOUNT_TR_DAN_LOW_BALL_MOVE_SYNC );

		scale = ENC_MakeVec( task_w->oam_scale_x.x, 
					task_w->oam_scale_y.x,
					0 );
		CLACT_SetScaleAffine( task_w->clact, &scale, CLACT_AFFINE_DOUBLE );

		// ��]
		ENC_MoveReq( &task_w->oam_rota,
				0, 
				ENCOUNT_TR_DAN_LOW_ROTA,
				ENCOUNT_TR_DAN_LOW_BALL_MOVE_SYNC );
		eew->seq++;
		break;
		
	case ENCOUNT_TR_DAN_LOW_MOVE_YWAIT:
		result = ENC_AddMoveMainFx( &task_w->oam_move );
		{
			VecFx32 mat = ENC_MakeVec( ENCOUNT_TR_DAN_LOW_BALL_MAT_X, 
					ENCOUNT_TR_DAN_LOW_BALL_MAT_Y + (task_w->oam_move.x),
					0 );
			CLACT_SetMatrix( 
					task_w->clact, 
					&mat );
		}
		ENC_AddMoveMainFx( &task_w->oam_scale_x );
		ENC_AddMoveMainFx( &task_w->oam_scale_y );
		scale = ENC_MakeVec( task_w->oam_scale_x.x, 
					task_w->oam_scale_y.x,
					0 );
		CLACT_SetScale( task_w->clact, &scale );

		ENC_MoveMain( &task_w->oam_rota );
		CLACT_SetRotation( task_w->clact, task_w->oam_rota.x );

		if( result == TRUE ){
			CLACT_SetDrawFlag( 
					task_w->clact, 
					FALSE );
			eew->seq++;
		}
		break;
		
	case ENCOUNT_TR_DAN_LOW_WIPE:
		// �t�B�[���hH�u�����NOFF
		FLDHBLANK_SYS_Stop( eew->fsw->fldmap->hblanksys );

		// �J���������쐬
		dist = GFC_GetCameraDistance( task_w->camera );
		ENC_AddMoveReqFx( &task_w->camera_dist,
				dist,
				dist + ENCOUNT_TR_DAN_LOW_CAMERA_DIST,
				ENCOUNT_TR_DAN_LOW_CAMERA_SS,
				ENCOUNT_TR_DAN_LOW_BALL_WIPE_SYNC );

		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_TUNNELOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, ENCOUNT_TR_DAN_LOW_BALL_WIPE_SYNC, 1, HEAPID_FIELD );
		eew->seq++;
		break;
		
	case ENCOUNT_TR_DAN_LOW_WIPEWAIT:
		// �J��������
		ENC_AddMoveMainFx( &task_w->camera_dist );
		GFC_SetCameraDistance( task_w->camera_dist.x, task_w->camera );
		
		if( WIPE_SYS_EndCheck() ){
			eew->seq++;
		}
		break;
		
	case ENCOUNT_TR_DAN_LOW_END:
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		// �t�B�[���hH�u�����NON
		FLDHBLANK_SYS_Start( eew->fsw->fldmap->hblanksys );
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		// OAM�j��
		CLACT_Delete( task_w->clact );
		ENC_CLACT_ResDeleteEasy( &task_w->clact_sys, &task_w->clact_res );
		ENC_CLACT_Delete( &task_w->clact_sys );
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		break;
	}

	if( eew->seq != ENCOUNT_TR_DAN_LOW_END ){
		CLACT_Draw( task_w->clact_sys.cas );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�g���[�i�[�@�_���W�����@���x����
 */
//-----------------------------------------------------------------------------
void EncountEffect_Trainer_DanLevelHigh(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_TR_DAN_HIGH* task_w = eew->work;
	VecFx32 matrix;
	BOOL result;
	int i;
	fx32 dist;

	switch( eew->seq ){
	case ENCOUNT_TR_DAN_HIGH_START:
		eew->work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENCOUNT_TR_DAN_HIGH) );	
		memset( eew->work, 0, sizeof(ENCOUNT_TR_DAN_HIGH) );
		task_w = eew->work;

		// �J�����|�C���^�擾
		task_w->camera = eew->fsw->camera_ptr;

		// �Z���A�N�^�[�Z�b�g�쐬
		ENC_CLACT_Init( &task_w->clact_sys, ENCOUNT_TR_DAN_HIGH_CELL_NUM, ENCOUNT_TR_DAN_HIGH_CELL_RES_NUM );

		// �O���t�B�b�N�ݒ�
		ENC_CLACT_ResLoadEasy(
				&task_w->clact_sys,
				&task_w->clact_res,
				NARC_field_encounteffect_monsterball_NCLR, 1,
				NARC_field_encounteffect_monstaerball_oam_NCGR,
				NARC_field_encounteffect_monsterball_oam_NCER,
				NARC_field_encounteffect_monsterball_oam_NANR,
				ENCOUNT_TR_DAN_HIGH_CELL_CONT_ID
				);

		// �A�N�^�[�o�^
		for( i=0; i<ENCOUNT_TR_DAN_HIGH_CELL_NUM; i++ ){
			task_w->clact[i] = ENC_CLACT_Add( 
					&task_w->clact_sys, &task_w->clact_res,
					0, 
					ENCOUNT_TR_DAN_HIGH_BALL_MAT_Y, 0, 0);
			CLACT_SetDrawFlag( task_w->clact[i], FALSE );
		}

		GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

		// �r�b�g�}�b�v�E�B���h�E�쐬
		task_w->p_bmp = GF_BGL_BmpWinAllocGet( HEAPID_FIELD, 1 );
		GF_BGL_BmpWinAdd( eew->fsw->bgl, task_w->p_bmp, GF_BGL_FRAME3_M, 0, 0, 32, 32, 0, 0 );

		// �J���[�p���b�g�]��
		{
			GXRgb color = 0;
			GF_BGL_PaletteSet( GF_BGL_FRAME3_M, &color, sizeof(short), 2*ENCOUNT_TR_DAN_HIGH_BLOCK_FILLCOLOR );
		}

		GF_BGL_BmpWinDataFill( task_w->p_bmp, 0 );
		GF_BGL_BmpWinOnVReq( task_w->p_bmp );

		// �u���b�N�I�u�W�F�N�g�쐬
		task_w->p_block = ENC_BMP_FillBlockMoveAlloc( HEAPID_FIELD );

		eew->seq ++;
		break;
		
	case ENCOUNT_TR_DAN_HIGH_FLASH_INI:

		EncountFlashTask(MASK_MAIN_DISPLAY, 16, -16,  &eew->wait, 2);
		eew->seq++;
		break;
		
	case ENCOUNT_TR_DAN_HIGH_FLASH_WAIT:
		if( eew->wait ){
			eew->seq++;
			task_w->wait = ENCOUNT_TR_DAN_HIGH_BALL_WAIT_0;
		}
		break;

	case ENCOUNT_TR_DAN_HIGH_MOVE_0Y:
		task_w->wait --;
		if( task_w->wait > 0 ){
			break;
		}
		
		ENC_MoveReq( &task_w->oam_move[0], 
				ENCOUNT_TR_DAN_HIGH_BALL_MAT_Y, 
				ENCOUNT_TR_DAN_HIGH_BALL_MOVE_Y, 
				ENCOUNT_TR_DAN_HIGH_BALL_MOVE_SYNC );
		matrix = ENC_MakeVec( 
				ENCOUNT_TR_DAN_HIGH_BALL_MAT_0X * FX32_ONE, 
				ENCOUNT_TR_DAN_HIGH_BALL_MAT_Y * FX32_ONE, 0 );
		CLACT_SetMatrix( task_w->clact[0], &matrix );
		CLACT_SetDrawFlag(
				task_w->clact[0],
				TRUE );

		// ��]
		ENC_MoveReq( &task_w->oam_rota[0], 
				0, 
				ENCOUNT_TR_DAN_HIGH_BALL0_ROTA, 
				ENCOUNT_TR_DAN_HIGH_BALL_MOVE_SYNC );
		CLACT_SetAffineParam( task_w->clact[0], CLACT_AFFINE_DOUBLE );
		
		task_w->oam_move_flg[0] = TRUE;
		eew->seq++;
		task_w->wait = ENCOUNT_TR_DAN_HIGH_BALL_WAIT_1;
		break;

	case ENCOUNT_TR_DAN_HIGH_MOVE_1Y:
		task_w->wait --;
		if( task_w->wait > 0 ){
			break;
		}

		ENC_MoveReq( &task_w->oam_move[1], 
				ENCOUNT_TR_DAN_HIGH_BALL_MAT_Y, 
				ENCOUNT_TR_DAN_HIGH_BALL_MOVE_Y, 
				ENCOUNT_TR_DAN_HIGH_BALL_MOVE_SYNC );
		matrix = ENC_MakeVec( 
				ENCOUNT_TR_DAN_HIGH_BALL_MAT_1X * FX32_ONE, 
				ENCOUNT_TR_DAN_HIGH_BALL_MAT_Y * FX32_ONE, 0 );
		CLACT_SetMatrix( task_w->clact[1], &matrix );
		CLACT_SetDrawFlag(
				task_w->clact[1],
				TRUE );

		// ��]
		ENC_MoveReq( &task_w->oam_rota[1], 
				0, 
				ENCOUNT_TR_DAN_HIGH_BALL1_ROTA, 
				ENCOUNT_TR_DAN_HIGH_BALL_MOVE_SYNC );

		CLACT_SetAffineParam( task_w->clact[1], CLACT_AFFINE_DOUBLE );
		task_w->oam_move_flg[1] = TRUE;
		eew->seq++;
		task_w->wait = ENCOUNT_TR_DAN_HIGH_BALL_WAIT_2;
		break;

	case ENCOUNT_TR_DAN_HIGH_MOVE_2Y:
		task_w->wait --;
		if( task_w->wait > 0 ){
			break;
		}

		ENC_MoveReq( &task_w->oam_move[2], 
				ENCOUNT_TR_DAN_HIGH_BALL_MAT_Y, 
				ENCOUNT_TR_DAN_HIGH_BALL_MOVE_Y, 
				ENCOUNT_TR_DAN_HIGH_BALL_MOVE_SYNC );
		matrix = ENC_MakeVec( 
				ENCOUNT_TR_DAN_HIGH_BALL_MAT_2X * FX32_ONE, 
				ENCOUNT_TR_DAN_HIGH_BALL_MAT_Y * FX32_ONE, 0 );
		CLACT_SetMatrix( task_w->clact[2], &matrix );
		CLACT_SetDrawFlag(
				task_w->clact[2],
				TRUE );

		// ��]
		ENC_MoveReq( &task_w->oam_rota[2], 
				0, 
				ENCOUNT_TR_DAN_HIGH_BALL2_ROTA, 
				ENCOUNT_TR_DAN_HIGH_BALL_MOVE_SYNC );
		CLACT_SetAffineParam( task_w->clact[2], CLACT_AFFINE_DOUBLE );

		task_w->oam_move_flg[2] = TRUE;
		eew->seq++;
		break;
		
	case ENCOUNT_TR_DAN_HIGH_MOVE_YWAIT:

		if( (task_w->oam_move_flg[0] == FALSE) &&
			(task_w->oam_move_flg[1] == FALSE) &&
			(task_w->oam_move_flg[2] == FALSE) ){
			for( i=0; i<ENCOUNT_TR_DAN_HIGH_CELL_NUM; i++ ){
				CLACT_SetDrawFlag( 
						task_w->clact[i], 
						FALSE );
			}
			eew->seq++;
		}
		break;
		
	case ENCOUNT_TR_DAN_HIGH_WIPE:
		ENC_BMP_FillBlockMoveStart( task_w->p_block, 
				ENCOUNT_TR_DAN_HIGH_BLOCK_SYNC,
				ENCOUNT_TR_DAN_HIGH_BLOCK_START_SYNC,
				task_w->p_bmp, ENCOUNT_TR_DAN_HIGH_BLOCK_FILLCOLOR );	

		// �J���������쐬
		dist = GFC_GetCameraDistance( task_w->camera );
		ENC_AddMoveReqFx( &task_w->camera_dist,
				dist,
				dist + ENCOUNT_TR_DAN_HIGH_CAMERA_DIST,
				ENCOUNT_TR_DAN_HIGH_CAMERA_SS,
				ENCOUNT_TR_DAN_HIGH_CAMERA_SYNC );

		eew->seq++;
		break;

	case ENCOUNT_TR_DAN_HIGH_WIPE_WAIT:
		result = ENC_BMP_FillBlockMoveMain( task_w->p_block );
		GF_BGL_BmpWinOnVReq( task_w->p_bmp );

		// �J��������
		ENC_AddMoveMainFx( &task_w->camera_dist );
		GFC_SetCameraDistance( task_w->camera_dist.x, task_w->camera );
		
		if( result == TRUE ){
			eew->seq ++;
		}
		break;
		
	case ENCOUNT_TR_DAN_HIGH_END:
		WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}

		// OAM�j��
		for( i=0; i<ENCOUNT_TR_DAN_HIGH_CELL_NUM; i++ ){
			CLACT_Delete( task_w->clact[i] );
		}
		ENC_CLACT_ResDeleteEasy( &task_w->clact_sys, &task_w->clact_res );
		ENC_CLACT_Delete( &task_w->clact_sys );

		// �u���b�N���[�N�j��
		ENC_BMP_FillBlockMoveDelete( task_w->p_block );

		// �r�b�g�}�b�v�j��
		GF_BGL_BmpWinOff( task_w->p_bmp );
		GF_BGL_BmpWinDel( task_w->p_bmp );
		GF_BGL_BmpWinFree( task_w->p_bmp, 1 );

		// �X�N���[���N���[��
		GF_BGL_ClearCharSet( GF_BGL_FRAME3_M, 32, 0, HEAPID_FIELD );
		GF_BGL_ScrClear( eew->fsw->bgl, GF_BGL_FRAME3_M );
		
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		break;
	}


	// �I�u�W�F�N�g����
	for( i=0; i<ENCOUNT_TR_DAN_HIGH_CELL_NUM; i++ ){
		
		if( task_w->oam_move_flg[i] == TRUE ){
			const VecFx32* cp_mat;
			VecFx32 mat;
			
			result = ENC_MoveMain( &task_w->oam_move[i] );
			ENC_MoveMain( &task_w->oam_rota[i] );
			if( result ){
				task_w->oam_move_flg[i] = FALSE;
			}
			cp_mat = CLACT_GetMatrix( task_w->clact[i] );
			mat = *cp_mat;
			mat.y = task_w->oam_move[i].x * FX32_ONE;
			CLACT_SetMatrix( task_w->clact[i], &mat );
			CLACT_SetRotation( task_w->clact[i], (0xffff & task_w->oam_rota[i].x) );
		}
	}

	if( eew->seq != ENCOUNT_TR_DAN_HIGH_END ){
		CLACT_Draw( task_w->clact_sys.cas );
	}
}




//-----------------------------------------------------------------------------
/**
 * 
 *		�y����z [ SPECIAL ]
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�o�g���^���[�@�t�@�N�g���[
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_SP_TOWER_START,
	ENCOUNT_SP_TOWER_FLASH_INI,
	ENCOUNT_SP_TOWER_FLASH_WAIT,
	ENCOUNT_SP_TOWER_ALPHA,
	ENCOUNT_SP_TOWER_ALPHAWAIT,
	ENCOUNT_SP_TOWER_WIPE,
	ENCOUNT_SP_TOWER_WIPEWAIT,
	ENCOUNT_SP_TOWER_END,
};
// OAM�f�[�^
// �A�N�^�[�f�[�^��
#define ENCOUNT_SP_TOWER_CELL_NUM		( 1 )	// ���[�N��
#define ENCOUNT_SP_TOWER_CELL_RES_NUM	( 1 )	// ���\�[�X��
#define ENCOUNT_SP_TOWER_CELL_CONT_ID	( 600000 )

// �����p�����[�^	�i�G���Ă悢�����j
#define ENCOUNT_SP_TOWER_BALL_MAT_X		( 128*FX32_ONE )	// �J�n���W
#define ENCOUNT_SP_TOWER_BALL_MAT_Y		( 96*FX32_ONE )	// �J�n���W
#define ENCOUNT_SP_TOWER_FADE_SYNC		( 12 )		// �t�F�[�h�V���N��
#define ENCOUNT_SP_TOWER_SCALE_SYNC		( 6 )		// �g��V���N��
#define ENCOUNT_SP_TOWER_SCALE_S		( FX32_CONST(1.0f) )	// �g��J�n
#define ENCOUNT_SP_TOWER_SCALE_E		( FX32_CONST(0.1f) )	// �g��I��
#define ENCOUNT_SP_TOWER_SCALE_SS		( 1 )		// �����x
#define ENCOUNT_SP_TOWER_FADE_S			( 0 )		// �t�F�[�h�J�n
#define ENCOUNT_SP_TOWER_FADE_E			( 16 )		// �t�F�[�h�I��





//-------------------------------------
//	�_�u���o�g��
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_SP_DOUBLE_START,
	ENCOUNT_SP_DOUBLE_FLASH_INI,
	ENCOUNT_SP_DOUBLE_FLASH_WAIT,
	ENCOUNT_SP_DOUBLE_OAM_MOVE,
	ENCOUNT_SP_DOUBLE_OAM_MOVEWAIT,
	ENCOUNT_SP_DOUBLE_WIPE,
	ENCOUNT_SP_DOUBLE_WIPEWAIT,
	ENCOUNT_SP_DOUBLE_END,
};
// OAM�f�[�^
// �A�N�^�[�f�[�^��
#define ENCOUNT_SP_DOUBLE_CELL_NUM		( 4 )	// ���[�N��
#define ENCOUNT_SP_DOUBLE_CELL_RES_NUM	( 1 )	// ���\�[�X��
#define ENCOUNT_SP_DOUBLE_CELL_CONT_ID	( 600000 )

// �����p�����[�^	�i�G���Ă悢�����j
#define ENCOUNT_SP_DOUBLE_BALL_MAT_X		( 128*FX32_ONE )	// �J�n���W
#define ENCOUNT_SP_DOUBLE_BALL_MAT_Y		( 96*FX32_ONE )	// �J�n���W
#define ENCOUNT_SP_DOUBLE_MOVE_SYNC		( 4 )		// �S���������V���N��
#define ENCOUNT_SP_DOUBLE_WIPE_SYNC		( 8 )		// ���C�v�V���N��
#define ENCOUNT_SP_DOUBLE_MOVE_X	( 160*FX32_ONE )	// ��������
#define ENCOUNT_SP_DOUBLE_MOVE_Y	( 128*FX32_ONE )	// ��������
#define ENCOUNT_SP_DOUBLE_MOVE_SS		(  FX32_CONST( 0.1f ) )	// �����x


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�o�g���^���[�@�t�@�N�g���[
//=====================================
typedef struct {
	ENC_MOVE_WORK	oam_alpha;
	ENC_ADDMOVE_WORK_FX oam_scale;

	ENC_CLACT_SYS	clact_sys;
	ENC_CLACT_RES_WORK clact_res;
	CLACT_WORK_PTR clact;

	s32 wait;
} ENCOUNT_SP_TOWER;

//-------------------------------------
//	�_�u���o�g��
//=====================================
typedef struct {

	ENC_CLACT_SYS	clact_sys;
	ENC_CLACT_RES_WORK clact_res;
	CLACT_WORK_PTR clact[ ENCOUNT_SP_DOUBLE_CELL_NUM ];
	ENC_ADDMOVE_WORK_FX oam_move[ 2 ];
} ENCOUNT_SP_DOUBLE;




//----------------------------------------------------------------------------
/**
 *	@brief	�o�g��TOWER�@�o�g���t�@�N�g���[
 */
//-----------------------------------------------------------------------------
void EncountEffect_Special_Tower(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_SP_TOWER* task_w = eew->work;
	BOOL result;

	switch( eew->seq ){
	case ENCOUNT_SP_TOWER_START:
		eew->work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENCOUNT_SP_TOWER) );	
		memset( eew->work, 0, sizeof(ENCOUNT_SP_TOWER) );
		task_w = eew->work;

		// �Z���A�N�^�[�Z�b�g�쐬
		ENC_CLACT_Init( &task_w->clact_sys, ENCOUNT_SP_TOWER_CELL_NUM, ENCOUNT_SP_TOWER_CELL_RES_NUM );

		// �O���t�B�b�N�ݒ�
		ENC_CLACT_ResLoadEasy(
				&task_w->clact_sys,
				&task_w->clact_res,
				NARC_field_encounteffect_monsterball_NCLR, 1,
				NARC_field_encounteffect_monstarballbig_oam_NCGR,
				NARC_field_encounteffect_monsterballbig_oam_NCER,
				NARC_field_encounteffect_monsterballbig_oam_NANR,
				ENCOUNT_TR_GRASS_LOW_CELL_CONT_ID
				);

		// �A�N�^�[�o�^
		task_w->clact = ENC_CLACT_Add( 
				&task_w->clact_sys, &task_w->clact_res,
				ENCOUNT_SP_TOWER_BALL_MAT_X, 
				ENCOUNT_SP_TOWER_BALL_MAT_Y,0, 0);
		CLACT_SetDrawFlag( task_w->clact, FALSE );
		CLACT_ObjModeSet( task_w->clact, GX_OAM_MODE_XLU );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

		eew->seq ++;
		break;
		
	case ENCOUNT_SP_TOWER_FLASH_INI:

		EncountFlashTask(MASK_MAIN_DISPLAY, 16, -16,  &eew->wait, 2);
		eew->seq++;
		break;
		
	case ENCOUNT_SP_TOWER_FLASH_WAIT:
		if( eew->wait ){
			eew->seq++;
		}
		break;

	case ENCOUNT_SP_TOWER_ALPHA:
		ENC_MoveReq( &task_w->oam_alpha, 
				ENCOUNT_SP_TOWER_FADE_S, ENCOUNT_SP_TOWER_FADE_E,
				ENCOUNT_SP_TOWER_FADE_SYNC );
		G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE, 
				GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3,
				task_w->oam_alpha.x, 16 - task_w->oam_alpha.x );

		CLACT_SetDrawFlag(
				task_w->clact,
				TRUE );
		eew->seq ++;
		break;
		
	case ENCOUNT_SP_TOWER_ALPHAWAIT:
		result = ENC_MoveMain( &task_w->oam_alpha );
		G2_ChangeBlendAlpha( task_w->oam_alpha.x, 16 - task_w->oam_alpha.x );
		if( result == TRUE ){
			G2_BlendNone();
			CLACT_ObjModeSet( task_w->clact, GX_OAM_MODE_NORMAL );
			eew->seq++;
		}
		break;
		
	case ENCOUNT_SP_TOWER_WIPE:
		ENC_AddMoveReqFx( &task_w->oam_scale, 
				ENCOUNT_SP_TOWER_SCALE_S,
				ENCOUNT_SP_TOWER_SCALE_E,
				ENCOUNT_SP_TOWER_SCALE_SS,
				ENCOUNT_SP_TOWER_SCALE_SYNC );

		CLACT_SetAffineParam(
				task_w->clact, 
				CLACT_AFFINE_DOUBLE );
		{
			VecFx32 scale = ENC_MakeVec( task_w->oam_scale.x, 
					task_w->oam_scale.x, task_w->oam_scale.x );
			CLACT_SetScale( 
					task_w->clact, 
					&scale );
		}

		// �t�B�[���hH�u�����NOFF
		FLDHBLANK_SYS_Stop( eew->fsw->fldmap->hblanksys );
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_HOLEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, ENCOUNT_SP_TOWER_SCALE_SYNC, 1, HEAPID_FIELD );
		eew->seq++;
		break;
		
	case ENCOUNT_SP_TOWER_WIPEWAIT:
		result = ENC_AddMoveMainFx( &task_w->oam_scale );
		{
			VecFx32 scale = ENC_MakeVec( task_w->oam_scale.x, 
					task_w->oam_scale.x, task_w->oam_scale.x );
			CLACT_SetScale( 
					task_w->clact, 
					&scale );
		}
		if( (result == TRUE) && ( WIPE_SYS_EndCheck() == TRUE ) ){
			eew->seq ++;
		}
		break;
		
	case ENCOUNT_SP_TOWER_END:
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		
		// �t�B�[���hH�u�����NON
		FLDHBLANK_SYS_Start( eew->fsw->fldmap->hblanksys );
		
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		// OAM�j��
		CLACT_Delete( task_w->clact );
		ENC_CLACT_ResDeleteEasy( &task_w->clact_sys, &task_w->clact_res );
		ENC_CLACT_Delete( &task_w->clact_sys );
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		break;
	}

	if( eew->seq != ENCOUNT_SP_TOWER_END ){
		CLACT_Draw( task_w->clact_sys.cas );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�_�u���o�g��
 */
//-----------------------------------------------------------------------------
void EncountEffect_Special_Double(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_SP_DOUBLE* task_w = eew->work;
	BOOL result;
	int i;
	VecFx32 matrix;

	switch( eew->seq ){
	case ENCOUNT_SP_DOUBLE_START:
		eew->work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENCOUNT_SP_DOUBLE) );	
		memset( eew->work, 0, sizeof(ENCOUNT_SP_DOUBLE) );
		task_w = eew->work;

		// �Z���A�N�^�[�Z�b�g�쐬
		ENC_CLACT_Init( &task_w->clact_sys, ENCOUNT_SP_DOUBLE_CELL_NUM, ENCOUNT_SP_DOUBLE_CELL_RES_NUM );

		// �O���t�B�b�N�ݒ�
		ENC_CLACT_ResLoadEasy(
				&task_w->clact_sys,
				&task_w->clact_res,
				NARC_field_encounteffect_monsterball_NCLR, 1,
				NARC_field_encounteffect_monstaerball_oam_NCGR,
				NARC_field_encounteffect_monsterball_oam_NCER,
				NARC_field_encounteffect_monsterball_oam_NANR,
				ENCOUNT_TR_GRASS_LOW_CELL_CONT_ID
				);

		// �A�N�^�[�o�^
		for( i=0; i<ENCOUNT_SP_DOUBLE_CELL_NUM; i++ ){
			task_w->clact[i] = ENC_CLACT_Add( 
					&task_w->clact_sys, &task_w->clact_res,
					ENCOUNT_SP_DOUBLE_BALL_MAT_X, 
					ENCOUNT_SP_DOUBLE_BALL_MAT_Y,0, 0);
			CLACT_SetDrawFlag( task_w->clact[i], FALSE );
		}
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

		eew->seq ++;
		break;
		
	case ENCOUNT_SP_DOUBLE_FLASH_INI:

		EncountFlashTask(MASK_MAIN_DISPLAY, 16, -16,  &eew->wait, 2);
		eew->seq++;
		break;
		
	case ENCOUNT_SP_DOUBLE_FLASH_WAIT:
		if( eew->wait ){
			eew->seq++;
		}
		break;

	case ENCOUNT_SP_DOUBLE_OAM_MOVE:
		ENC_AddMoveReqFx( &task_w->oam_move[0],
				0, ENCOUNT_SP_DOUBLE_MOVE_Y,
				ENCOUNT_SP_DOUBLE_MOVE_SS, ENCOUNT_SP_DOUBLE_MOVE_SYNC );
		ENC_AddMoveReqFx( &task_w->oam_move[1],
				0, ENCOUNT_SP_DOUBLE_MOVE_X,
				ENCOUNT_SP_DOUBLE_MOVE_SS, ENCOUNT_SP_DOUBLE_MOVE_SYNC );

		for( i=0; i<ENCOUNT_SP_DOUBLE_CELL_NUM; i++ ){
			CLACT_SetDrawFlag( task_w->clact[i], TRUE );
		}
		eew->seq++;
		break;
		
	case ENCOUNT_SP_DOUBLE_OAM_MOVEWAIT:
		for( i=0; i<2; i++ ){
			result = ENC_AddMoveMainFx( &task_w->oam_move[i] );
		}
		// �g�b�v
		matrix = ENC_MakeVec( 
				ENCOUNT_SP_DOUBLE_BALL_MAT_X,
				ENCOUNT_SP_DOUBLE_BALL_MAT_Y - task_w->oam_move[0].x,
				0 );
		CLACT_SetMatrix( task_w->clact[0], &matrix );

		// �{�g��
		matrix = ENC_MakeVec( 
				ENCOUNT_SP_DOUBLE_BALL_MAT_X,
				ENCOUNT_SP_DOUBLE_BALL_MAT_Y + task_w->oam_move[0].x,
				0 );
		CLACT_SetMatrix( task_w->clact[1], &matrix );

		// ���t��
		matrix = ENC_MakeVec( 
				ENCOUNT_SP_DOUBLE_BALL_MAT_X - task_w->oam_move[1].x,
				ENCOUNT_SP_DOUBLE_BALL_MAT_Y,
				0 );
		CLACT_SetMatrix( task_w->clact[2], &matrix );

		// LIGHT
		matrix = ENC_MakeVec( 
				ENCOUNT_SP_DOUBLE_BALL_MAT_X + task_w->oam_move[1].x,
				ENCOUNT_SP_DOUBLE_BALL_MAT_Y,
				0 );
		CLACT_SetMatrix( task_w->clact[3], &matrix );

		if( result == TRUE ){
			eew->seq ++;
		}
		break;
		
	case ENCOUNT_SP_DOUBLE_WIPE:
		// �t�B�[���hH�u�����NOFF
		FLDHBLANK_SYS_Stop( eew->fsw->fldmap->hblanksys );
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FLASHOUT_FOREWAY, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, ENCOUNT_SP_DOUBLE_WIPE_SYNC, 1, HEAPID_FIELD );
		eew->seq++;
		break;
		
	case ENCOUNT_SP_DOUBLE_WIPEWAIT:
		if( WIPE_SYS_EndCheck() == TRUE ){
			eew->seq ++;
		}
		break;
		
	case ENCOUNT_SP_DOUBLE_END:
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		
		// �t�B�[���hH�u�����NON
		FLDHBLANK_SYS_Start( eew->fsw->fldmap->hblanksys );
		
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		// OAM�j��
		for( i=0; i<ENCOUNT_SP_DOUBLE_CELL_NUM; i++ ){
			CLACT_Delete( task_w->clact[i] );
		}
		ENC_CLACT_ResDeleteEasy( &task_w->clact_sys, &task_w->clact_res );
		ENC_CLACT_Delete( &task_w->clact_sys );
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		break;
	}

	if( eew->seq != ENCOUNT_SP_DOUBLE_END ){
		CLACT_Draw( task_w->clact_sys.cas );
	}
}



//-----------------------------------------------------------------------------
/**
 * 
 *		��͒c	�G���J�E���g [ GINGA ]
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	��͒c�ʏ�
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_GINGA_NORMAL_START,
	ENCOUNT_GINGA_NORMAL_FLASH_INI,
	ENCOUNT_GINGA_NORMAL_FLASH_WAIT,
	ENCOUNT_GINGA_NORMAL_OAM,
	ENCOUNT_GINGA_NORMAL_OAM_WAIT,
	ENCOUNT_GINGA_NORMAL_FLASHOUT,
	ENCOUNT_GINGA_NORMAL_FLASHOUT_WAIT,
	ENCOUNT_GINGA_NORMAL_END,
};
// OAM�f�[�^
// �A�N�^�[�f�[�^��
#define ENCOUNT_GINGA_NORMAL_CELL_NUM		( 6 )	// ���[�N��
#define ENCOUNT_GINGA_NORMAL_CELL_RES_NUM	( 1 )	// ���\�[�X��
#define ENCOUNT_GINGA_NORMAL_CELL_CONT_ID	( 600000 )

// �����p�����[�^	�i�G���Ă悢�����j
#define ENCOUNT_GINGA_NORMAL_OAM_MOVE_SYNC	( 8 )	// OAM1�����V���N
#define ENCOUNT_GINGA_NORMAL_FLASHOUT_SYNC	( 12 )	// �t���b�V���A�E�g�V���N

#define ENCOUNT_GINGA_NORMAL_OAM_S_SCA	( FX32_CONST(2.0f) )	//	�J�n�X�P�[��
#define ENCOUNT_GINGA_NORMAL_OAM_E_SCA	( FX32_CONST(0.01f) )	//	�I���X�P�[��
#define ENCOUNT_GINGA_NORMAL_OAM_SS_SCA	( -FX32_CONST(0.40f) )	//	�����x�X�P�[��

enum{
	ENCOUNT_GINGA_NORMAL_OAM_PARAM_SX,
	ENCOUNT_GINGA_NORMAL_OAM_PARAM_EX,
	ENCOUNT_GINGA_NORMAL_OAM_PARAM_SSX,
	ENCOUNT_GINGA_NORMAL_OAM_PARAM_SY,
	ENCOUNT_GINGA_NORMAL_OAM_PARAM_EY,
	ENCOUNT_GINGA_NORMAL_OAM_PARAM_SSY,
	ENCOUNT_GINGA_NORMAL_OAM_PARAM_WAIT,
	ENCOUNT_GINGA_NORMAL_OAM_PARAM_ROTA,
	ENCOUNT_GINGA_NORMAL_OAM_PARAM_NUM,
};

// �{�[�������p�����[�^
// ENCOUNT_GINGA_NORMAL_CELL_NUM�@�Ɖ��̃e�[�u�������ꏏ�Ȃ�
// ���ɂł��o���܂�
static const s32 ENCOUNT_GINGA_NORMAL_OAM_Param[ ENCOUNT_GINGA_NORMAL_CELL_NUM ][ ENCOUNT_GINGA_NORMAL_OAM_PARAM_NUM ] = {
	{	// 0
		FX32_CONST( 260 ),		// �J�nX���W
        FX32_CONST( 128 ),		// �I��X���W
        -FX32_CONST( 30 ),		// �����xX
		FX32_CONST( 0 ),		// �J�nY���W
		FX32_CONST( 100 ),		// �I��Y���W
		FX32_CONST( 20 ),		// �����xY
		4,						// �J�n�E�G�C�g
		0xffff * 2				// ��]��
	},
	{// 1
		FX32_CONST( -16 ),		// �J�nX���W
		FX32_CONST( 128 ),      // �I��X���W
		FX32_CONST( 30 ),       // �����xX
		FX32_CONST(160),        // �J�nY���W
		FX32_CONST(100),        // �I��Y���W
		-FX32_CONST(20),		// �����xY
		3,						// �J�n�E�G�C�g
		0xffff * 1				// ��]��
	},                         
	{// 2
		FX32_CONST(0),			// �J�nX���W
		FX32_CONST(128),         // �I��X���W
		FX32_CONST(30),         // �����xX
		FX32_CONST(-16),        // �J�nY���W
		FX32_CONST(100),         // �I��Y���W
		FX32_CONST(20),         // �����xY
		4,                       // �J�n�E�G�C�g
		-0xffff * 3				// ��]��
	},
	{// 3
		FX32_CONST(140),			// �J�nX���W
		FX32_CONST(128),         // �I��X���W
		-FX32_CONST(10),         // �����xX
		FX32_CONST(160),        // �J�nY���W
		FX32_CONST(100),         // �I��Y���W
		-FX32_CONST(20),         // �����xY
		2,                       // �J�n�E�G�C�g
		-0xffff * 2				// ��]��
	},
	{// 4
		FX32_CONST(260),			// �J�nX���W
		FX32_CONST(128),         // �I��X���W
		-FX32_CONST(30),         // �����xX
		FX32_CONST(80),        // �J�nY���W
		FX32_CONST(100),         // �I��Y���W
		FX32_CONST(1),         // �����xY
		3,                       // �J�n�E�G�C�g
		-0xffff * 3				// ��]��
	},
	{// 5
		FX32_CONST(0),			// �J�nX���W
		FX32_CONST(128),         // �I��X���W
		FX32_CONST(30),         // �����xX
		FX32_CONST(160),        // �J�nY���W
		FX32_CONST(100),         // �I��Y���W
		-FX32_CONST(20),         // �����xY
		3,                       // �J�n�E�G�C�g
		0xffff * 1				// ��]��
	},
};






//-------------------------------------
//	��͒c�@�����N���X
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_GINGA_SPECIAL_START,
	ENCOUNT_GINGA_SPECIAL_FLASH_INI,
	ENCOUNT_GINGA_SPECIAL_FLASH_WAIT,
	ENCOUNT_GINGA_SPECIAL_ALPHA_IN,
	ENCOUNT_GINGA_SPECIAL_ALPHA_INWAIT,
	ENCOUNT_GINGA_SPECIAL_FLASHOUT,
	ENCOUNT_GINGA_SPECIAL_FLASHOUT_WAIT,
	ENCOUNT_GINGA_SPECIAL_END,
};
// OAM�f�[�^
// �A�N�^�[�f�[�^��
#define ENCOUNT_GINGA_SPECIAL_CELL_NUM		( 1 )	// ���[�N��
#define ENCOUNT_GINGA_SPECIAL_CELL_RES_NUM	( 1 )	// ���\�[�X��
#define ENCOUNT_GINGA_SPECIAL_CELL_CONT_ID	( 600000 )

// �r�b�g�}�b�v�֌W
#define ENCOUNT_GINGA_SPECIAL_BMP_COL	( 15 )

// �����p�����[�^	�i�G���Ă悢�����j
#define ENCOUNT_GINGA_SPECIAL_MAT_X		( 128*FX32_ONE )	// �J�n���W
#define ENCOUNT_GINGA_SPECIAL_MAT_Y		( 96*FX32_ONE )	// �J�n���W

#define ENCOUNT_GINGA_SPECIAL_OAM_ALPHA_SYNC	( 15 )	// ���V���N
#define ENCOUNT_GINGA_SPECIAL_FLASHMOSAIC_WAIT		( 16 )	// ���U�C�N�ƃt���b�V���A�E�g�̊J�n�E�G�C�g
#define ENCOUNT_GINGA_SPECIAL_OAM_MOSAIC_SYNC	( 16 )	// ���U�C�N�V���N��

#define ENCOUNT_GINGA_SPECIAL_FLASHOUT_SYNC	( 16 )		// �t���b�V���A�E�g�V���N
#define ENCOUNT_GINGA_SPECIAL_ALPHA_S	( 0 )	// ���J�n
#define ENCOUNT_GINGA_SPECIAL_ALPHA_E	( 16 )	// ���I��	(0�`16)

#define ENCOUNT_GINGA_SPECIAL_MOSAIC_S	( 0 )	// ���U�C�N�J�n
#define ENCOUNT_GINGA_SPECIAL_MOSAIC_E	( 14 )	// ���U�C�N�I��(0�`15)


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	��͒c�ʏ�
//=====================================
typedef struct {
	ENC_CLACT_SYS	clact_sys;
	ENC_CLACT_RES_WORK clact_res;
	CLACT_WORK_PTR clact[ ENCOUNT_GINGA_NORMAL_CELL_NUM ];
	ENC_ADDMOVE_WORK_FX oam_scale[ ENCOUNT_GINGA_NORMAL_CELL_NUM ];
	ENC_ADDMOVE_WORK_FX oam_move_x[ ENCOUNT_GINGA_NORMAL_CELL_NUM ];
	ENC_ADDMOVE_WORK_FX oam_move_y[ ENCOUNT_GINGA_NORMAL_CELL_NUM ];
	ENC_MOVE_WORK		oam_rota[ ENCOUNT_GINGA_NORMAL_CELL_NUM ];
	BOOL oam_move_flg[ ENCOUNT_GINGA_NORMAL_CELL_NUM ];

	s32 count;
	s32 wait;
} ENCOUNT_GINGA_NORMAL;

//-------------------------------------
//	��͒c�@�����N���X
//=====================================
typedef struct {
	GF_BGL_BMPWIN* p_bmp;
	ENC_BMP_FLASH_OUT* p_flashout;

	ENC_CLACT_SYS	clact_sys;
	ENC_CLACT_RES_WORK clact_res;
	CLACT_WORK_PTR clact;
	ENC_MOVE_WORK mosaic;
	ENC_MOVE_WORK alpha;
	ENC_MOVE_WORK rota;

	s32 wait;
} ENCOUNT_GINGA_SPECIAL;



//----------------------------------------------------------------------------
/**
 *	@brief	��͒c�@�ʏ�
 */
//-----------------------------------------------------------------------------
void EncountEffect_Ginga_Normal(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_GINGA_NORMAL* task_w = eew->work;
	BOOL result;
	int i;
	VecFx32 matrix;
	VecFx32 scale;

	switch( eew->seq ){
	case ENCOUNT_GINGA_NORMAL_START:
		eew->work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENCOUNT_GINGA_NORMAL) );	
		memset( eew->work, 0, sizeof(ENCOUNT_GINGA_NORMAL) );
		task_w = eew->work;

		// �Z���A�N�^�[�Z�b�g�쐬
		ENC_CLACT_Init( &task_w->clact_sys, ENCOUNT_GINGA_NORMAL_CELL_NUM, ENCOUNT_GINGA_NORMAL_CELL_RES_NUM );

		// �O���t�B�b�N�ݒ�
		ENC_CLACT_ResLoadEasy(
				&task_w->clact_sys,
				&task_w->clact_res,
				NARC_field_encounteffect_monsterball_NCLR, 1,
				NARC_field_encounteffect_monstaerball_oam_NCGR,
				NARC_field_encounteffect_monsterball_oam_NCER,
				NARC_field_encounteffect_monsterball_oam_NANR,
				ENCOUNT_TR_GRASS_LOW_CELL_CONT_ID
				);

		// �A�N�^�[�o�^
		for( i=0; i<ENCOUNT_GINGA_NORMAL_CELL_NUM; i++ ){
			task_w->clact[i] = ENC_CLACT_Add( 
					&task_w->clact_sys, &task_w->clact_res,
					0, 
					0,0, 0);
			CLACT_SetDrawFlag( task_w->clact[i], FALSE );
		}
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

		eew->seq ++;
		break;
		
	case ENCOUNT_GINGA_NORMAL_FLASH_INI:

		EncountFlashTask(MASK_MAIN_DISPLAY, -16, -16,  &eew->wait, 2);
		eew->seq++;
		break;
		
	case ENCOUNT_GINGA_NORMAL_FLASH_WAIT:
		if( eew->wait ){
			eew->seq++;
			task_w->count = 0;
			task_w->wait = ENCOUNT_GINGA_NORMAL_OAM_Param[task_w->count][ENCOUNT_GINGA_NORMAL_OAM_PARAM_WAIT];
		}
		break;

	case ENCOUNT_GINGA_NORMAL_OAM:
		task_w->wait --;
		if( task_w->wait < 0 ){
			ENC_AddMoveReqFx( &task_w->oam_move_x[task_w->count], 
					ENCOUNT_GINGA_NORMAL_OAM_Param[task_w->count][ENCOUNT_GINGA_NORMAL_OAM_PARAM_SX],
					ENCOUNT_GINGA_NORMAL_OAM_Param[task_w->count][ENCOUNT_GINGA_NORMAL_OAM_PARAM_EX],
					ENCOUNT_GINGA_NORMAL_OAM_Param[task_w->count][ENCOUNT_GINGA_NORMAL_OAM_PARAM_SSX],
					ENCOUNT_GINGA_NORMAL_OAM_MOVE_SYNC );

			ENC_AddMoveReqFx( &task_w->oam_move_y[task_w->count], 
					ENCOUNT_GINGA_NORMAL_OAM_Param[task_w->count][ENCOUNT_GINGA_NORMAL_OAM_PARAM_SY],
					ENCOUNT_GINGA_NORMAL_OAM_Param[task_w->count][ENCOUNT_GINGA_NORMAL_OAM_PARAM_EY],
					ENCOUNT_GINGA_NORMAL_OAM_Param[task_w->count][ENCOUNT_GINGA_NORMAL_OAM_PARAM_SSY],
					ENCOUNT_GINGA_NORMAL_OAM_MOVE_SYNC );

			ENC_AddMoveReqFx( &task_w->oam_scale[task_w->count], 
					ENCOUNT_GINGA_NORMAL_OAM_S_SCA,
					ENCOUNT_GINGA_NORMAL_OAM_E_SCA,
					ENCOUNT_GINGA_NORMAL_OAM_SS_SCA,
					ENCOUNT_GINGA_NORMAL_OAM_MOVE_SYNC );

			ENC_MoveReq( &task_w->oam_rota[task_w->count], 
					0,
					ENCOUNT_GINGA_NORMAL_OAM_Param[ task_w->count ][ENCOUNT_GINGA_NORMAL_OAM_PARAM_ROTA],
					ENCOUNT_GINGA_NORMAL_OAM_MOVE_SYNC );

			CLACT_SetDrawFlag( task_w->clact[task_w->count], TRUE );
			matrix = ENC_MakeVec( 
					ENCOUNT_GINGA_NORMAL_OAM_Param[task_w->count][ENCOUNT_GINGA_NORMAL_OAM_PARAM_SX], 
					ENCOUNT_GINGA_NORMAL_OAM_Param[task_w->count][ENCOUNT_GINGA_NORMAL_OAM_PARAM_SY], 0 );
			CLACT_SetMatrix( task_w->clact[task_w->count], &matrix );
			scale = ENC_MakeVec( 
					ENCOUNT_GINGA_NORMAL_OAM_S_SCA, 
					ENCOUNT_GINGA_NORMAL_OAM_S_SCA, 0 );
			CLACT_SetScaleAffine( task_w->clact[task_w->count], &scale, CLACT_AFFINE_DOUBLE );

			task_w->oam_move_flg[task_w->count] = TRUE;

			task_w->count++;

			if( task_w->count >= ENCOUNT_GINGA_NORMAL_CELL_NUM ){
				eew->seq++;
			}else{
				task_w->wait = ENCOUNT_GINGA_NORMAL_OAM_Param[task_w->count][ENCOUNT_GINGA_NORMAL_OAM_PARAM_WAIT];
			}
		}
		break;

	case ENCOUNT_GINGA_NORMAL_OAM_WAIT:
		// �S���������`�F�b�N
		if( task_w->oam_move_flg[ ENCOUNT_GINGA_NORMAL_CELL_NUM - 1 ] == FALSE ){
			eew->seq ++;
		}
		break;

	case ENCOUNT_GINGA_NORMAL_FLASHOUT:
		// �t�B�[���hH�u�����NOFF
		FLDHBLANK_SYS_Stop( eew->fsw->fldmap->hblanksys );

		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FLASHOUT_FOREWAY, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, ENCOUNT_GINGA_NORMAL_FLASHOUT_SYNC, 1, HEAPID_FIELD );
		eew->seq++;
		break;
		
	case ENCOUNT_GINGA_NORMAL_FLASHOUT_WAIT:
		if( WIPE_SYS_EndCheck() ){
			eew->seq++;
		}
		break;
		
	case ENCOUNT_GINGA_NORMAL_END:
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );

		// �t�B�[���hH�u�����NON
		FLDHBLANK_SYS_Start( eew->fsw->fldmap->hblanksys );
		
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		// OAM�j��
		for( i=0; i<ENCOUNT_GINGA_NORMAL_CELL_NUM; i++ ){
			CLACT_Delete( task_w->clact[i] );
		}
		ENC_CLACT_ResDeleteEasy( &task_w->clact_sys, &task_w->clact_res );
		ENC_CLACT_Delete( &task_w->clact_sys );
		
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		break;
	}


	// �I�u�W�F�N�g����
	for( i=0; i<ENCOUNT_GINGA_NORMAL_CELL_NUM; i++ ){
		
		if( task_w->oam_move_flg[i] == TRUE ){
			
			result = ENC_AddMoveMainFx( &task_w->oam_move_x[i] );
			ENC_AddMoveMainFx( &task_w->oam_move_y[i] );
			ENC_AddMoveMainFx( &task_w->oam_scale[i] );
			ENC_MoveMain( &task_w->oam_rota[i] );
			if( result ){
				task_w->oam_move_flg[i] = FALSE;
				CLACT_SetDrawFlag( task_w->clact[i], FALSE );
			}
			matrix = ENC_MakeVec( 
					task_w->oam_move_x[i].x, 
					task_w->oam_move_y[i].x, 0 );
			CLACT_SetMatrix( task_w->clact[i], &matrix );
			scale = ENC_MakeVec( 
					task_w->oam_scale[i].x, 
					task_w->oam_scale[i].x, 0 );
			CLACT_SetScale( task_w->clact[i], &scale );
			CLACT_SetRotation( task_w->clact[i], task_w->oam_rota[i].x );
		}
	}

	if( eew->seq != ENCOUNT_GINGA_NORMAL_END ){
		CLACT_Draw( task_w->clact_sys.cas );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	��͒c�@�����N���X
 */
//-----------------------------------------------------------------------------
void EncountEffect_Ginga_Special(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_GINGA_SPECIAL* task_w = eew->work;
	BOOL result;

	switch( eew->seq ){
	case ENCOUNT_GINGA_SPECIAL_START:
		eew->work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENCOUNT_GINGA_SPECIAL) );	
		memset( eew->work, 0, sizeof(ENCOUNT_GINGA_SPECIAL) );
		task_w = eew->work;

		// �Z���A�N�^�[�Z�b�g�쐬
		ENC_CLACT_Init( &task_w->clact_sys, ENCOUNT_GINGA_SPECIAL_CELL_NUM, ENCOUNT_GINGA_SPECIAL_CELL_RES_NUM );

		// �O���t�B�b�N�ݒ�
		ENC_CLACT_ResLoadEasy(
				&task_w->clact_sys,
				&task_w->clact_res,
				NARC_field_encounteffect_ginga_NCLR, 1,
				NARC_field_encounteffect_ginga_NCGR,
				NARC_field_encounteffect_ginga_NCER,
				NARC_field_encounteffect_ginga_NANR,
				ENCOUNT_TR_GRASS_LOW_CELL_CONT_ID
				);

		// �A�N�^�[�o�^
		task_w->clact = ENC_CLACT_Add( 
				&task_w->clact_sys, &task_w->clact_res,
				ENCOUNT_GINGA_SPECIAL_MAT_X, 
				ENCOUNT_GINGA_SPECIAL_MAT_Y, 0, 0);
		CLACT_SetDrawFlag( task_w->clact, FALSE );
		CLACT_ObjModeSet( task_w->clact, GX_OAM_MODE_XLU );
		CLACT_BGPriorityChg( task_w->clact, 1 );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

		// �t���b�V���A�E�g�I�u�W�F�쐬
		task_w->p_flashout = ENC_BMP_FlashOutAlloc( HEAPID_FIELD );

		// �r�b�g�}�b�v�E�B���h�E�쐬
		task_w->p_bmp = GF_BGL_BmpWinAllocGet( HEAPID_FIELD, 1 );
		GF_BGL_BmpWinAdd( eew->fsw->bgl, task_w->p_bmp, GF_BGL_FRAME3_M, 0, 0, 32, 32, 0, 0 );

		// �J���[�p���b�g�]��
		{
			GXRgb color = 0;
			GF_BGL_PaletteSet( GF_BGL_FRAME3_M, &color, sizeof(short), 2*ENCOUNT_GINGA_SPECIAL_BMP_COL );
		}

		GF_BGL_BmpWinDataFill( task_w->p_bmp, 0 );
		GF_BGL_BmpWinOnVReq( task_w->p_bmp );

		eew->seq ++;
		break;
		
	case ENCOUNT_GINGA_SPECIAL_FLASH_INI:

		EncountFlashTask(MASK_MAIN_DISPLAY, 16, -16,  &eew->wait, 2);
		eew->seq++;
		break;
		
	case ENCOUNT_GINGA_SPECIAL_FLASH_WAIT:
		if( eew->wait ){
			eew->seq++;
		}
		break;

	case ENCOUNT_GINGA_SPECIAL_ALPHA_IN:
		ENC_MoveReq( &task_w->alpha, ENCOUNT_GINGA_SPECIAL_ALPHA_S, ENCOUNT_GINGA_SPECIAL_ALPHA_E, ENCOUNT_GINGA_SPECIAL_OAM_ALPHA_SYNC );
		CLACT_SetDrawFlag( task_w->clact, TRUE );
		G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE, 
				GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3,
				task_w->alpha.x, 16 - task_w->alpha.x );
		eew->seq++;
		break;
		
	case ENCOUNT_GINGA_SPECIAL_ALPHA_INWAIT:
		result = ENC_MoveMain( &task_w->alpha );
		G2_ChangeBlendAlpha( task_w->alpha.x, 16 - task_w->alpha.x );
		if( result == TRUE ){
			G2_BlendNone();
			CLACT_ObjModeSet( task_w->clact, GX_OAM_MODE_NORMAL );
			eew->seq++;
			task_w->wait = ENCOUNT_GINGA_SPECIAL_FLASHMOSAIC_WAIT;
		}
		break;

	case ENCOUNT_GINGA_SPECIAL_FLASHOUT:
		task_w->wait --;
		if( task_w->wait > 0 ){
			break;
		}
		
		ENC_MoveReq( &task_w->mosaic, ENCOUNT_GINGA_SPECIAL_MOSAIC_S, ENCOUNT_GINGA_SPECIAL_MOSAIC_E, ENCOUNT_GINGA_SPECIAL_OAM_MOSAIC_SYNC );
		ENC_BMP_FlashOutStart( task_w->p_flashout, ENCOUNT_GINGA_SPECIAL_FLASHOUT_SYNC, task_w->p_bmp, ENCOUNT_GINGA_SPECIAL_BMP_COL );
		eew->seq++;
		break;
		
	case ENCOUNT_GINGA_SPECIAL_FLASHOUT_WAIT:
		ENC_MoveMain( &task_w->mosaic );
		G2_SetOBJMosaicSize( task_w->mosaic.x, task_w->mosaic.x );
		if( ENC_BMP_FlashOutMain( task_w->p_flashout ) ){
			eew->seq++;
		}
		GF_BGL_BmpWinOnVReq( task_w->p_bmp );
		break;
		
	case ENCOUNT_GINGA_SPECIAL_END:
		WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		
		// �t���b�V���A�E�g�I�u�W�F�j��
		ENC_BMP_FlashOutDelete( task_w->p_flashout );
		
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		// OAM�j��
		CLACT_Delete( task_w->clact );
		ENC_CLACT_ResDeleteEasy( &task_w->clact_sys, &task_w->clact_res );
		ENC_CLACT_Delete( &task_w->clact_sys );

		// �r�b�g�}�b�v�j��
		GF_BGL_BmpWinOff( task_w->p_bmp );
		GF_BGL_BmpWinDel( task_w->p_bmp );
		GF_BGL_BmpWinFree( task_w->p_bmp, 1 );

		// �X�N���[���N���[��
		GF_BGL_ClearCharSet( GF_BGL_FRAME3_M, 32, 0, HEAPID_FIELD );
		GF_BGL_ScrClear( eew->fsw->bgl, GF_BGL_FRAME3_M );
		
		G2_SetOBJMosaicSize( 0, 0 );
		
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		break;
	}


	if( eew->seq != ENCOUNT_GINGA_SPECIAL_END ){
		CLACT_Draw( task_w->clact_sys.cas );
	}
}


//-----------------------------------------------------------------------------
/**
 * 
 *		�`���|�P�����@�G���J�E���g [ LEGEND ]
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�`���|�P����
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_LEGEND_NORMAL_START,
	ENCOUNT_LEGEND_NORMAL_FLASH_INI,
	ENCOUNT_LEGEND_NORMAL_FLASH_WAIT,
	ENCOUNT_LEGEND_NORMAL_MOTIONBL_S,
	ENCOUNT_LEGEND_NORMAL_CAMERA_SET,
	ENCOUNT_LEGEND_NORMAL_FADE,
	ENCOUNT_LEGEND_NORMAL_FADEWAIT,
	ENCOUNT_LEGEND_NORMAL_END,
};

// �J�����e�[�u��
typedef struct{
	u32 dist;		// ����
	u16 angle_x;	// Angle
	u16 angle_y;
	u16 purse;		// �p�[�X
	u16 wait;
} ENCOUNT_LEGEND_CAMERA_TBL;


// �J�����e�[�u��	(�G���Ă悢)
#define ENCOUNT_LEGEND_CAMERA_TBL_NUM	( 16 )	// �����𑝂₵�A���̃e�[�u���̐������킹��ƁA�e�[�u���̐����ύX�ł��܂��B
static const ENCOUNT_LEGEND_CAMERA_TBL EncLegendNormalCamera[ ENCOUNT_LEGEND_CAMERA_TBL_NUM ] = {
	{	// 0
		0x29AEC1,		// ����
		0xD602,			// AngleX
		0x0,			// AngleY
		0x5C1,			// �p�[�X
		4,				// �E�G�C�g
	},
	{	// 1
		0x29AEC1,		// ����
		0xcf02,			// AngleX
		0xff00,			// AngleY
		0x601,			// �p�[�X
		4,				// �E�G�C�g
	},
	{	// 2
		0x29AEC1,		// ����
		0xe602,			// AngleX
		0x1000,			// AngleY
		0x691,			// �p�[�X
		4,				// �E�G�C�g
	},
	{	// 3
		0x29AEC1,		// ����
		0xD602,			// AngleX
		0xa00,			// AngleY
		0x711,			// �p�[�X
		3,				// �E�G�C�g
	},
	{	// 4
		0x29AEC1,		// ����
		0xe102,			// AngleX
		0xf000,			// AngleY
		0x780,			// �p�[�X
		3,				// �E�G�C�g
	},
	{	// 5
		0x29AEC1,		// ����
		0xc602,			// AngleX
		0x0000,			// AngleY
		0x751,			// �p�[�X
		3,				// �E�G�C�g
	},
	{	// 6
		0x29AEC1,		// ����
		0xe002,			// AngleX
		0xf000,			// AngleY
		0x800,			// �p�[�X
		3,				// �E�G�C�g
	},
	{	// 7
		0x29AEC1,		// ����
		0xD602,			// AngleX
		0,				// AngleY
		0x802,			// �p�[�X
		3,				// �E�G�C�g
	},
	{	// 8
		0x29AEC1,		// ����
		0xD002,			// AngleX
		0x1000,			// AngleY
		0x800,			// �p�[�X
		3,				// �E�G�C�g
	},
	{	// 9
		0x29AEC1,		// ����
		0xD902,			// AngleX
		0xf500,			// AngleY
		0x751,			// �p�[�X
		3,				// �E�G�C�g
	},
	{	// 10
		0x29AEC1,		// ����
		0xD002,			// AngleX
		0xa00,			// AngleY
		0x4C1,			// �p�[�X
		2,				// �E�G�C�g
	},
	{	// 11
		0x29AEC1,		// ����
		0xe002,			// AngleX
		0xf000,			// AngleY
		0x3C1,			// �p�[�X
		2,				// �E�G�C�g
	},
	{	// 12
		0x29AEC1,		// ����
		0xD002,			// AngleX
		0xf000,			// AngleY
		0x650,			// �p�[�X
		1,				// �E�G�C�g
	},
	{	// 13
		0x29AEC1,		// ����
		0xe002,			// AngleX
		0xa000,			// AngleY
		0x241,			// �p�[�X
		1,				// �E�G�C�g
	},
	{	// 14
		0x29AEC1,		// ����
		0xe1a2,			// AngleX
		0x500,			// AngleY
		0x500,			// �p�[�X
		1,				// �E�G�C�g
	},
	{	// 15
		0x29AEC1,		// ����
		0xD602,			// AngleX
		0,				// AngleY
		0x241,			// �p�[�X
		1,				// �E�G�C�g
	},
};

// �����p�����[�^	�i�G���Ă悢�����j
#define ENCOUNT_LEGEND_NORMAL_FADE_SYNC		( 10 )	// �t�F�[�h�V���N
#define ENCOUNT_LEGEND_NORMAL_MOTIONBL_EVA	( 3 )	// ���[�V�����u���[�W���@�V�����u�����h�����G
#define ENCOUNT_LEGEND_NORMAL_MOTIONBL_EAB	( 15 )	// ���[�V�����u���[�W���@���łɃo�b�t�@����Ă���G


//-------------------------------------
//	�p�b�P�[�W�|�P����
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_LEGEND_PACKAGE_START,
	ENCOUNT_LEGEND_PACKAGE_FLASH_INI,
	ENCOUNT_LEGEND_PACKAGE_FLASH_WAIT,
	ENCOUNT_LEGEND_PACKAGE_MOTIONBL_S,
	ENCOUNT_LEGEND_PACKAGE_PURSE,
	ENCOUNT_LEGEND_PACKAGE_CAMERA,
	ENCOUNT_LEGEND_PACKAGE_CAMERAWAIT,
	ENCOUNT_LEGEND_PACKAGE_FADE,
	ENCOUNT_LEGEND_PACKAGE_FADEWAIT,
	ENCOUNT_LEGEND_PACKAGE_END,
};

// �����p�����[�^	�i�G���Ă悢�����j
#define ENCOUNT_LEGEND_PACKAGE_PURSE_SYNC	( 40 )		// �p�[�X�V���N
#define ENCOUNT_LEGEND_PACKAGE_CAMERA_MOVE_WAIT		( 5 )	// �J�����҂��V���N
#define ENCOUNT_LEGEND_PACKAGE_CAMERA_SYNC	( 8 )	// �J�����V���N

#define ENCOUNT_LEGEND_PACKAGE_FADE_SYNC	( 60 )	// �t�F�[�h�V���N

#define ENCOUNT_LEGEND_PACKAGE_PURSE_MOVE	( 0x100 )	// �p�[�X�ϓ��l 0b0

#define ENCOUNT_LEGEND_PACKAGE_CAMERA_MOVE	( -FX32_CONST( 2350 ) )	// �J��������l 200
#define ENCOUNT_LEGEND_PACKAGE_CAMERA_SS	( FX32_CONST( 0.5 ) ) //0.0f

#define ENCOUNT_LEGEND_PACKAGE_MOTIONBL_EVA	( 5 )	// ���[�V�����u���[�W���@�V�����u�����h�����G
#define ENCOUNT_LEGEND_PACKAGE_MOTIONBL_EAB	( 13 )	// ���[�V�����u���[�W���@���łɃo�b�t�@����Ă���G




//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�`���|�P����
//=====================================
typedef struct {
	FLD_MOTION_BL_DATA_PTR	motion;
	GF_CAMERA_PTR	camera;		// �J�����f�[�^
	u32 camera_count;
	s32 wait;
} ENCOUNT_LEGEND_NORMAL;

//-------------------------------------
//	PACKAGE�|�P����
//=====================================
typedef struct {
	FLD_MOTION_BL_DATA_PTR	motion;
	GF_CAMERA_PTR	camera;		// �J�����f�[�^
	ENC_MOVE_WORK purse;
	ENC_ADDMOVE_WORK_FX camra_zoom;
	s32 wait;
} ENCOUNT_LEGEND_PACKAGE;



// �J�����f�[�^�ݒ�
static void ENC_LegendCameraSet( FIELDSYS_WORK* fsys, const ENCOUNT_LEGEND_CAMERA_TBL* cp_data )
{
	CAMERA_ANGLE angle;
	
	// �J�����p�����[�^�ݒ�
	GFC_SetCameraPerspWay( cp_data->purse, fsys->camera_ptr );	
	GFC_SetCameraDistance( cp_data->dist, fsys->camera_ptr );
	angle.x = cp_data->angle_x;
	angle.y = cp_data->angle_y;
	angle.z = 0;
	GFC_SetCameraAngleRev( &angle, fsys->camera_ptr );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�`���|�P�����@�G���J�E���g
 */
//-----------------------------------------------------------------------------
void EncountEffect_Legend_Normal(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_LEGEND_NORMAL* task_w = eew->work;

	switch(eew->seq){
	case ENCOUNT_LEGEND_NORMAL_START:	// ����������
		eew->work = sys_AllocMemory(HEAPID_FIELD, sizeof(ENCOUNT_LEGEND_NORMAL));
		memset( eew->work, 0, sizeof(ENCOUNT_LEGEND_NORMAL) );
		
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_OFF);
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG2, VISIBLE_OFF);
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG3, VISIBLE_OFF);
		
		eew->seq++;
		break;
		
	case ENCOUNT_LEGEND_NORMAL_FLASH_INI:
		EncountFlashTask(MASK_MAIN_DISPLAY, 16, 16,  &eew->wait, 1);

		eew->seq++;
		break;

	case ENCOUNT_LEGEND_NORMAL_FLASH_WAIT:
		if(eew->wait){
			eew->seq++;
		}
		break;

	case ENCOUNT_LEGEND_NORMAL_MOTIONBL_S:	// ���[�V�����u���[���g�p���鏀��
		task_w->motion = FLDMotionBl_Init(ENCOUNT_LEGEND_NORMAL_MOTIONBL_EVA, ENCOUNT_LEGEND_NORMAL_MOTIONBL_EAB);
		task_w->camera_count = 0;
		task_w->wait = EncLegendNormalCamera[ task_w->camera_count ].wait;
		eew->seq++;
		break;

	case ENCOUNT_LEGEND_NORMAL_CAMERA_SET:
		task_w->wait --;
		if( task_w->wait < 0 ){

			// �J�����ݒ�
			ENC_LegendCameraSet( eew->fsw, &EncLegendNormalCamera[ task_w->camera_count ] );	

			task_w->camera_count++;
			if( task_w->camera_count >= ENCOUNT_LEGEND_CAMERA_TBL_NUM ){
				eew->seq++;
			}else{
				task_w->wait = EncLegendNormalCamera[ task_w->camera_count ].wait;
			}
		}
		break;
		
	case ENCOUNT_LEGEND_NORMAL_FADE:
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_WHITE, ENCOUNT_LEGEND_NORMAL_FADE_SYNC, 1, HEAPID_FIELD );
		eew->seq++;
		break;
		
	case ENCOUNT_LEGEND_NORMAL_FADEWAIT:
		if( WIPE_SYS_EndCheck() ){
			eew->wait = 0;

			eew->seq++;
		}
		break;

	
	case ENCOUNT_LEGEND_NORMAL_END:		// ��n��
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );

		// ���ɖ߂�
		FLDMotionBl_Delete(&task_w->motion);

		// �u���C�g�l�X����
		G2_BlendNone();
		
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		break;
	}	
}


//----------------------------------------------------------------------------
/**
 *	@brief	�߯���ރ|�P�����@�G���J�E���g
 */
//-----------------------------------------------------------------------------
void EncountEffect_Legend_Package(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	ENCOUNT_LEGEND_PACKAGE* task_w = eew->work;
	BOOL result;

	switch(eew->seq){
	case ENCOUNT_LEGEND_PACKAGE_START:	// ����������
		eew->work = sys_AllocMemory(HEAPID_FIELD, sizeof(ENCOUNT_LEGEND_PACKAGE));
		memset( eew->work, 0, sizeof(ENCOUNT_LEGEND_PACKAGE) );
		
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_OFF);
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG2, VISIBLE_OFF);
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG3, VISIBLE_OFF);
		
		eew->seq++;
		break;
		
	case ENCOUNT_LEGEND_PACKAGE_FLASH_INI:
		EncountFlashTask(MASK_MAIN_DISPLAY, 16, 16,  &eew->wait, 1);

		eew->seq++;
		break;

	case ENCOUNT_LEGEND_PACKAGE_FLASH_WAIT:
		if(eew->wait){
			eew->seq++;
		}
		break;

	case ENCOUNT_LEGEND_PACKAGE_MOTIONBL_S:	// ���[�V�����u���[���g�p���鏀��
		task_w->motion = FLDMotionBl_Init(ENCOUNT_LEGEND_PACKAGE_MOTIONBL_EVA, ENCOUNT_LEGEND_PACKAGE_MOTIONBL_EAB);

		// �p�[�X�ݒ�
		{
			u16 pers = GFC_GetCameraPerspWay( eew->fsw->camera_ptr );
			ENC_MoveReq( &task_w->purse, pers, pers + ENCOUNT_LEGEND_PACKAGE_PURSE_MOVE, ENCOUNT_LEGEND_PACKAGE_PURSE_SYNC );
		}
		
		eew->seq++;
		break;

	case ENCOUNT_LEGEND_PACKAGE_PURSE:
		result = ENC_MoveMain( &task_w->purse );
		GFC_SetCameraPerspWay( task_w->purse.x, eew->fsw->camera_ptr );	
		if( result == TRUE ){
			eew->seq++;
			task_w->wait = ENCOUNT_LEGEND_PACKAGE_CAMERA_MOVE_WAIT;
		}
		break;

	case ENCOUNT_LEGEND_PACKAGE_CAMERA:
		task_w->wait --;
		if( task_w->wait < 0 ){
			fx32 dist = GFC_GetCameraDistance( eew->fsw->camera_ptr );	
			ENC_AddMoveReqFx( &task_w->camra_zoom, 
					dist, 
					dist + ENCOUNT_LEGEND_PACKAGE_CAMERA_MOVE,
					ENCOUNT_LEGEND_PACKAGE_CAMERA_SS, 
					ENCOUNT_LEGEND_PACKAGE_CAMERA_SYNC );

			eew->seq ++;
		}
		break;
		
	case ENCOUNT_LEGEND_PACKAGE_CAMERAWAIT:
		result = ENC_AddMoveMainFx( &task_w->camra_zoom );
		GFC_SetCameraDistance( task_w->camra_zoom.x, eew->fsw->camera_ptr );
		if( result == TRUE ){
			eew->seq++;
		}
		break;
		
	case ENCOUNT_LEGEND_PACKAGE_FADE:
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_WHITE, ENCOUNT_LEGEND_PACKAGE_FADE_SYNC, 1, HEAPID_FIELD );
		eew->seq++;
		break;
		
	case ENCOUNT_LEGEND_PACKAGE_FADEWAIT:
		if( WIPE_SYS_EndCheck() ){
			eew->wait = 0;

			eew->seq++;
		}
		break;

	
	case ENCOUNT_LEGEND_PACKAGE_END:		// ��n��
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );

		// ���ɖ߂�
		FLDMotionBl_Delete(&task_w->motion);

		// �u���C�g�l�X����
		G2_BlendNone();
		
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		break;
	}	
}

//-----------------------------------------------------------------------------
/**
 * 
 *			����g���[�i�[�@�G���J�E���g[ SP_TR ]
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�W�����[�_�[
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_SPTR_GYM_START,
	ENCOUNT_SPTR_GYM_FLASH_INI,
	ENCOUNT_SPTR_GYM_FLASH_WAIT,
	ENCOUNT_SPTR_GYM_BG_IN,
	ENCOUNT_SPTR_GYM_BG_INWAIT,
	ENCOUNT_SPTR_GYM_OAM_IN,
	ENCOUNT_SPTR_GYM_OAM_INWAIT,
	ENCOUNT_SPTR_GYM_OAM_FLASH_OUT,
	ENCOUNT_SPTR_GYM_OAM_FLASH_OUT_WAIT,
	ENCOUNT_SPTR_GYM_OAM_FLASH_IN,
	ENCOUNT_SPTR_GYM_OAM_FLASH_IN_WAIT,
	ENCOUNT_SPTR_GYM_WAIT,
	ENCOUNT_SPTR_GYM_WIPE,
	ENCOUNT_SPTR_GYM_WIPEWAIT,
	ENCOUNT_SPTR_GYM_END,
};
// OAM�f�[�^
// �A�N�^�[�f�[�^��
#define ENCOUNT_SPTR_GYM_CELL_NUM		( 1 )	// ���[�N��
#define ENCOUNT_SPTR_GYM_CELL_RES_NUM	( 1 )	// ���\�[�X��
#define ENCOUNT_SPTR_GYM_CELL_CONT_ID	( 600000 )
#define ENCOUNT_SPTR_GYM_LEADER_SCALE_DEF	( FX32_CONST( 2.0f ) )	// ���[�_�[�̊�{�̊g��l
#define ENCOUNT_SPTR_GYM_LEADER_DRAW_BOTTOM	( 30 )	// ���͂��̃T�C�Y�܂ŕ\������
#define ENCOUNT_SPTR_GYM_LEADER_COLOR_FADE		( GX_RGB( 0,0,0 ) )
#define ENCOUNT_SPTR_GYM_LEADER_COLOR_FADE_EVY	( 10 )
#define ENCOUNT_SPTR_GYM_LEADER_CHAR_OFS_CX	(0)	// �L�����N�^�f�[�^�����o�����́AX�L�����N�^�I�t�Z�b�g�l

#define ENCOUNT_SPTR_GYM_ZIGUZAGU_IN_WND ( GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_BG1|GX_WND_PLANEMASK_BG2|GX_WND_PLANEMASK_BG3|GX_WND_PLANEMASK_OBJ)				// �W�O�U�O�����E�B���h�E��
#define ENCOUNT_SPTR_GYM_ZIGUZAGU_OUT_WND ( GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_BG1|GX_WND_PLANEMASK_BG2|GX_WND_PLANEMASK_OBJ)				// �W�O�U�O�����E�B���h�E�O

// �����p�����[�^	�i�G���Ă悢�����j
#define ENCOUNT_SPTR_GYM_OAM_START_X	( -32*FX32_ONE )	// OAM�����J�nX
#define ENCOUNT_SPTR_GYM_OAM_X_SS		( 64*FX32_ONE )		// �������x
#define ENCOUNT_SPTR_GYM_OAM_START_Y	( 68*FX32_ONE )		// OAMY���W
#define ENCOUNT_SPTR_GYM_OAM_MOVE_SYNC	( 4 )				// OAM�����V���N
#define ENCOUNT_SPTR_GYM_ZIGUZAGU_DOT	( 8 )				// �W�O�U�O��؂�Y�h�b�g��
#define ENCOUNT_SPTR_GYM_ZIGUZAGU_WIDTH	( 16 )				// �W�O�U�O��
#define ENCOUNT_SPTR_GYM_ZIGUZAGU_SYNC	( 8 )				// �W�O�U�O�����V���N
#define ENCOUNT_SPTR_GYM_BG_CY			( 68 )	// BG�̒��S
#define ENCOUNT_SPTR_GYM_BG_AUTOMOVE_X	( -15 )	// AUTO�����X�s�[�h
#define ENCOUNT_SPTR_GYM_BG_AFTER_WAIT	( 10 )				// BG������E�G�C�g
#define	ENCOUNT_SPTR_GYM_FLASHOUT_SYNC	( 3 )				// �t���b�V���A�E�g�V���N��
#define	ENCOUNT_SPTR_GYM_FLASHIN_SYNC	( 3 )				// �t���b�V���C���V���N��
#define ENCOUNT_SPTR_GYM_FLASH_AFTER_WAIT	( 26 )			// �t���b�V����̃E�G�C�g
#define ENCOUNT_SPTR_GYM_SCALE_S			( FX32_CONST(1.0f) )	// �g��J�n
#define ENCOUNT_SPTR_GYM_SCALE_E			( FX32_CONST(1.0f) )	// �g��J�n
#define ENCOUNT_SPTR_GYM_FADEOUT_SYNC		( 15 )			// �t�F�[�h�A�E�g�V���N

	
// ���ꂼ��ŕς��Ƃ���
typedef struct {
	fx32 end_x;
	u16 type;
	u16 tr_oam_chr_ofs_cx;
} ENCOUNT_SPTR_GYM_PARAM;
// ���ꂼ��̒萔
static const ENCOUNT_SPTR_GYM_PARAM ENCOUNT_SPTR_GymDef[ 8 ] = {
	{	// ��
		176*FX32_ONE,			// ��������X���W
		TRTYPE_LEADER1,			// ���[�_�[�^�C�v
		ENC_OAM_TR_CHAR_CUT_CX,	// OAM�L�����̃I�t�Z�b�g
	},
	{	// ��
		176*FX32_ONE,			// ��������X���W
		TRTYPE_LEADER2,			// ���[�_�[�^�C�v
		ENC_OAM_TR_CHAR_CUT_CX,	// OAM�L�����̃I�t�Z�b�g
	},
	{	// ��
		192*FX32_ONE,			// ��������X���W
		TRTYPE_LEADER3,			// ���[�_�[�^�C�v
		ENCOUNT_SPTR_GYM_LEADER_CHAR_OFS_CX,// OAM�L�����̃I�t�Z�b�g�l	��{�I�ɐ��������AENCOUNT_SPTR_GYM_LEADER_CHAR_OFS_CX
	},
	{	// �i��
		176*FX32_ONE,			// ��������X���W
		TRTYPE_LEADER4,			// ���[�_�[�^�C�v
		ENC_OAM_TR_CHAR_CUT_CX,	// OAM�L�����̃I�t�Z�b�g
	},
	{	// �S�[�X�g
		192*FX32_ONE,			// ��������X���W
		TRTYPE_LEADER5,			// ���[�_�[�^�C�v
		ENC_OAM_TR_CHAR_CUT_CX,	// OAM�L�����̃I�t�Z�b�g
	},
	{	// �X
		176*FX32_ONE,			// ��������X���W
		TRTYPE_LEADER6,			// ���[�_�[�^�C�v
		ENC_OAM_TR_CHAR_CUT_CX,	// OAM�L�����̃I�t�Z�b�g
	},
	{	// �|
		176*FX32_ONE,			// ��������X���W
		TRTYPE_LEADER7,			// ���[�_�[�^�C�v
		ENC_OAM_TR_CHAR_CUT_CX,	// OAM�L�����̃I�t�Z�b�g
	},
	{	// �d�C
		176*FX32_ONE,			// ��������X���W
		TRTYPE_LEADER8,			// ���[�_�[�^�C�v
		ENC_OAM_TR_CHAR_CUT_CX,	// OAM�L�����̃I�t�Z�b�g
	},
};


//-------------------------------------
//	�l�V���@�`�����s�I���@���[�_�[
//=====================================
// �V�[�P���X
enum{
	ENCOUNT_SPTR_CHANP_START,
	ENCOUNT_SPTR_CHANP_FLASH_INI,
	ENCOUNT_SPTR_CHANP_FLASH_WAIT,
	ENCOUNT_SPTR_CHANP_HERO_IN,
	ENCOUNT_SPTR_CHANP_HERO_INWAIT,
	ENCOUNT_SPTR_CHANP_HERO_FLASHOUT,
	ENCOUNT_SPTR_CHANP_HERO_FLASHOUTWAIT,
	ENCOUNT_SPTR_CHANP_HERO_FLASHIN,
	ENCOUNT_SPTR_CHANP_HERO_FLASHINWAIT,
	ENCOUNT_SPTR_CHANP_ENEMY_IN,
	ENCOUNT_SPTR_CHANP_ENEMY_INWAIT,
	ENCOUNT_SPTR_CHANP_ENEMY_FLASHOUT,
	ENCOUNT_SPTR_CHANP_ENEMY_FLASHOUTWAIT,
	ENCOUNT_SPTR_CHANP_ENEMY_FLASHIN,
	ENCOUNT_SPTR_CHANP_ENEMY_FLASHINWAIT,
	ENCOUNT_SPTR_CHANP_CAMERA_MOVE,
	ENCOUNT_SPTR_CHANP_CAMERA_MOVE_WAIT,
	ENCOUNT_SPTR_CHANP_WIPE,
	ENCOUNT_SPTR_CHANP_WIPEWAIT,
	ENCOUNT_SPTR_CHANP_END,
};
// OAM�f�[�^
// �A�N�^�[�f�[�^��
#define ENCOUNT_SPTR_CHANP_CELL_NUM		( 4 )	// ���[�N��
#define ENCOUNT_SPTR_CHANP_CELL_RES_NUM	( 3 )	// ���\�[�X��
#define ENCOUNT_SPTR_CHANP_CELL_CONT_ID	( 600000 )
#define ENCOUNT_SPTR_CHANP_CELL_SCALE	( FX32_CONST( 2.0f ) )
#define ENCOUNT_SPTR_CHANP_LEADER_DRAW_BOTTOM	( 30 )	// ���͂��̃T�C�Y�܂ŕ\������
#define ENCOUNT_SPTR_CHANP_COLOR_FADE	( GX_RGB( 0,0,0 ) )
#define ENCOUNT_SPTR_CHANP_COLOR_FADE_EVY	(10)

// �����p�����[�^	�i�G���Ă悢�����j
//�@�l�V���ƃ`�����s�I���ňႤ�Ƃ���
#define ENCOUNT_SPTR_CHANP_SITEN_ANGLE_X_MOVE	( 1500 )	// �l�V���@�J����Angle�ϓ��l
#define ENCOUNT_SPTR_CHANP_SITEN_ANGLE_SYNC		( 15 )		// �l�V���@�J����Angle�ύX�V���N��
#define ENCOUNT_SPTR_CHANP_CHANP_ANGLE_X_MOVE	( 3000 )	// �`�����s�I���@�J����Angle�ϓ��l
#define ENCOUNT_SPTR_CHANP_CHANP_ANGLE_SYNC		( 30 )			// �`�����s�I���@�J����Angle�ύX�V���N��

// ��l������
#define ENCOUNT_SPTR_CHANP_HERO_MOVE_SX		( -80*FX32_ONE )	// ��l���@�o��J�nX���W
#define ENCOUNT_SPTR_CHANP_HERO_MOVE_SS		( 64*FX32_ONE )		// ��l���@�o�ꏉ���x
#define ENCOUNT_SPTR_CHANP_HERO_MOVE_EX		( 46*FX32_ONE )		// ��l���@�o��I��X���W
#define ENCOUNT_SPTR_CHANP_HERO_Y			( 114*FX32_ONE )	// ��l���@Y���W
#define ENCOUNT_SPTR_CHANP_HERO_Y_WAKU_OFS	( 36*FX32_ONE )		// �g���������W
#define ENCOUNT_SPTR_CHANP_HERO_X_WAKU_OFS	( 16*FX32_ONE )		// �g���������W
#define ENCOUNT_SPTR_CHANP_HERO_MOVE_SYNC	( 6 )				// ��l���@�o��V���N��
#define ENCOUNT_SPTR_CHANP_HERO_FLASHOUT_SYNC	( 3 )		// ��l���t���b�V���A�E�g�@�V���N��
#define ENCOUNT_SPTR_CHANP_HERO_FLASHIN_SYNC	( 3 )		// ��l���t���b�V���C���@�V���N��

// �l�V���@�`�����s�I������
#define ENCOUNT_SPTR_CHANP_ENEMY_MOVE_SX		( 336*FX32_ONE )	// ��l���@�o��J�nX���W
#define ENCOUNT_SPTR_CHANP_ENEMY_MOVE_SS		( -64*FX32_ONE )		// ��l���@�o�ꏉ���x
#define ENCOUNT_SPTR_CHANP_ENEMY_MOVE_EX		( 208*FX32_ONE )		// ��l���@�o��I��X���W
#define ENCOUNT_SPTR_CHANP_ENEMY_Y			( 68*FX32_ONE )	// ��l���@Y���W
#define ENCOUNT_SPTR_CHANP_ENEMY_Y_WAKU_OFS	( 36*FX32_ONE )		// �g���������W
#define ENCOUNT_SPTR_CHANP_ENEMY_X_WAKU_OFS	( -16*FX32_ONE )		// �g���������W
#define ENCOUNT_SPTR_CHANP_ENEMY_MOVE_SYNC	( 6 )				// ��l���@�o��V���N��
#define ENCOUNT_SPTR_CHANP_ENEMY_FLASHOUT_SYNC	( 3 )		// ��l���t���b�V���A�E�g�@�V���N��
#define ENCOUNT_SPTR_CHANP_ENEMY_FLASHIN_SYNC	( 3 )		// ��l���t���b�V���C���@�V���N��

// �Ō�̔����Ȃ�Ƃ�
#define ENCOUNT_SPTR_CHANP_WIPE_OUT_SYNC		( 30 )	// ���C�v�A�E�g�V���N��
#define ENCOUNT_SPTR_CHANP_CAMERA_MOVE_X		( -FX32_CONST( 250 ) )	// �J�����ϓ��l
#define ENCOUNT_SPTR_CHANP_CAMERA_SS			( FX32_CONST( 0.0f ) )	// �����x
#define ENCOUNT_SPTR_CHANP_OMA_MOVE_X			( FX32_CONST( 96.0f ) )	// OAM��������
#define ENCOUNT_SPTR_CHANP_OMA_MOVE_Y			( FX32_CONST( 96.0f ) )	// OAM��������
#define ENCOUNT_SPTR_CHANP_OAM_MOVE_XSS			( FX32_CONST( 0.0f ) )	// OAM���������x
#define ENCOUNT_SPTR_CHANP_OAM_MOVE_YSS			( FX32_CONST( 0.0f ) )	// OAM���������x
  

// ���ꂼ��̒萔
typedef struct{
	s32 angle_x_move;
	u8 angle_move_sync;
	u8 enemy_tr_type;
	u8 waku_oam_cl;
} ENCOUNT_SPTR_CHANP_PARAM;

static const ENCOUNT_SPTR_CHANP_PARAM EncountSpTr_ChanpParam[ 5 ] = {
	{	// �l�V���P
		ENCOUNT_SPTR_CHANP_SITEN_ANGLE_X_MOVE,
		ENCOUNT_SPTR_CHANP_SITEN_ANGLE_SYNC,
		TRTYPE_BIGFOUR1,
		NARC_field_encounteffect_cutin_chanpion00_NCLR,
	},
	{	// �l�V���Q
		ENCOUNT_SPTR_CHANP_SITEN_ANGLE_X_MOVE,
		ENCOUNT_SPTR_CHANP_SITEN_ANGLE_SYNC,
		TRTYPE_BIGFOUR2,
		NARC_field_encounteffect_cutin_chanpion01_NCLR,
	},
	{	// �l�V���R
		ENCOUNT_SPTR_CHANP_SITEN_ANGLE_X_MOVE,
		ENCOUNT_SPTR_CHANP_SITEN_ANGLE_SYNC,
		TRTYPE_BIGFOUR3,
		NARC_field_encounteffect_cutin_chanpion02_NCLR,
	},
	{	// �l�V���S
		ENCOUNT_SPTR_CHANP_SITEN_ANGLE_X_MOVE,
		ENCOUNT_SPTR_CHANP_SITEN_ANGLE_SYNC,
		TRTYPE_BIGFOUR4,
		NARC_field_encounteffect_cutin_chanpion03_NCLR,
	},
	{	// �`�����s�I��
		ENCOUNT_SPTR_CHANP_CHANP_ANGLE_X_MOVE,
		ENCOUNT_SPTR_CHANP_CHANP_ANGLE_SYNC,
		TRTYPE_CHAMPION,
		NARC_field_encounteffect_cutin_chanpion04_NCLR,
	},

};

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�W�����[�_�[
//=====================================
typedef struct {
	ENC_ADDMOVE_WORK_FX oam_move_x;
	ENC_MOVE_WORK flash;
	ENC_MOVE_WORK_FX scale;

	ENC_HB_BG_WND_ZIGUZAGU* p_ziguzagu;
	
	ENC_CLACT_SYS	clact_sys;
	ENC_CLACT_RES_WORK clact_res;
	CLACT_WORK_PTR clact;
	ENC_WND_SETPOSITION wnd_posi;
	ENC_BG_SET_AFFINEPARAM bg_affine;

	BOOL bg_auto_move;
	s32 auto_move_x;

	s32 wait;
} ENCOUNT_SPTR_GYM;

//-------------------------------------
//	�l�V���@�`�����s�I��
//=====================================
typedef struct {
	ENC_ADDMOVE_WORK_FX oam_move_x;
	ENC_ADDMOVE_WORK_FX oam_move_y;
	ENC_MOVE_WORK flash;

	ENC_CLACT_SYS	clact_sys;
	ENC_CLACT_RES_WORK clact_res[ENCOUNT_SPTR_CHANP_CELL_RES_NUM];
	CLACT_WORK_PTR clact[ENCOUNT_SPTR_CHANP_CELL_NUM];

	GF_CAMERA_PTR	camera;			// �J�����f�[�^
	ENC_ADDMOVE_WORK_FX camera_dist;
	CAMERA_ANGLE		angle;
	ENC_MOVE_WORK		camera_angle;

	u32 hero_type;	// ��l���^�C�v

	s32 wait;
} ENCOUNT_SPTR_CHANP;




//----------------------------------------------------------------------------
/**
 *	@brief	�W����p�G���J�E���g�G�t�F�N�g
 *
 *	@param	eew		�G�t�F�N�g���[�N
 *	@param	heapID	�q�[�vID
 *	@param	cp_def	�f�t�@�C����`
 *
 *	@retval	TRUE		�I��
 *	@retval	FALSE		�r��
 */
//-----------------------------------------------------------------------------
static BOOL EncountEffect_SpTr_GymMain( ENCOUNT_EFFECT_WORK *eew, u32 heapID, const ENCOUNT_SPTR_GYM_PARAM* cp_def )
{
	ENCOUNT_SPTR_GYM* task_w = eew->work;
	BOOL result;
	const VecFx32* cp_matrix;
	VecFx32 matrix;
	VecFx32 scale;
	int bottom_y;

	switch( eew->seq ){
	case ENCOUNT_SPTR_GYM_START:
		eew->work = sys_AllocMemory( heapID, sizeof(ENCOUNT_SPTR_GYM) );	
		memset( eew->work, 0, sizeof(ENCOUNT_SPTR_GYM) );
		task_w = eew->work;

		// �Z���A�N�^�[�Z�b�g�쐬
		ENC_CLACT_Init( &task_w->clact_sys, ENCOUNT_SPTR_GYM_CELL_NUM, ENCOUNT_SPTR_GYM_CELL_RES_NUM );

		// �O���t�B�b�N�ݒ�
		ENC_CLACT_ResLoadEasy(
				&task_w->clact_sys,
				&task_w->clact_res,
				NARC_field_encounteffect_cutin_dummy_char00_NCLR, 1,
				NARC_field_encounteffect_cutin_dummy_char00_NCGR,
				NARC_field_encounteffect_cutin_dummy_char00_NCER,
				NARC_field_encounteffect_cutin_dummy_char00_NANR,
				ENCOUNT_SPTR_GYM_CELL_CONT_ID
				);

		// �A�N�^�[�o�^
		task_w->clact = ENC_CLACT_Add( 
				&task_w->clact_sys, &task_w->clact_res,
				ENCOUNT_SPTR_GYM_OAM_START_X, 
				ENCOUNT_SPTR_GYM_OAM_START_Y,0, 0);
		CLACT_SetDrawFlag( task_w->clact, FALSE );
		CLACT_SetAffineParam( task_w->clact, CLACT_AFFINE_DOUBLE );


		// �W�����[�_�[�L�����N�^�p���b�g�]��
		ENC_CLACT_ResSetSoftSpriteDataTrOam( task_w->clact, heapID, cp_def->type, ENCOUNT_SPTR_GYM_LEADER_COLOR_FADE_EVY, ENCOUNT_SPTR_GYM_LEADER_COLOR_FADE, cp_def->tr_oam_chr_ofs_cx );

		// �A�t�B��BG�ݒ�
		ENC_BG_SetAffineCont( eew->fsw->bgl );

		// �W�O�U�O�E�B���h�E������
		task_w->p_ziguzagu = ENC_BG_WndZiguzagu_Alloc();

		eew->seq ++;
		break;
		
	case ENCOUNT_SPTR_GYM_FLASH_INI:

		EncountFlashTask(MASK_MAIN_DISPLAY, 16, 16,  &eew->wait, 1);
		eew->seq++;
		break;
		
	case ENCOUNT_SPTR_GYM_FLASH_WAIT:
		if( eew->wait ){
			eew->seq++;
		}
		break;

	case ENCOUNT_SPTR_GYM_BG_IN:
		
		// BG�ݒ�
		ENC_BG_SetAffineBG(
				NARC_field_encounteffect_cutin_gym00_NSCR,
				NARC_field_encounteffect_cutin_gym00_NCGR,
				NARC_field_encounteffect_cutin_gym00_NCLR,
				eew->fsw->bgl );
		task_w->bg_auto_move = TRUE;	// BGAUTO����

		// �W�O�U�O�E�B���h�E�X�^�[�g
		ENC_BG_WndZiguzagu_Start( eew, task_w->p_ziguzagu, 
				ENCOUNT_SPTR_GYM_ZIGUZAGU_SYNC,
				ENCOUNT_SPTR_GYM_ZIGUZAGU_DOT,
				ENCOUNT_SPTR_GYM_ZIGUZAGU_WIDTH,
				ENCOUNT_SPTR_GYM_ZIGUZAGU_IN_WND,
				ENCOUNT_SPTR_GYM_ZIGUZAGU_OUT_WND );

		// BGAUTO�����̂��߂Ɋg��p�����[�^�������ō쐬
		ENC_MoveReqFx( &task_w->scale,
				ENCOUNT_SPTR_GYM_SCALE_S,
				ENCOUNT_SPTR_GYM_SCALE_E,
				ENCOUNT_SPTR_GYM_FADEOUT_SYNC );
		
		// BG�ʕ\��
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG3, VISIBLE_ON);
		
		eew->seq++;
		break;
		
	case ENCOUNT_SPTR_GYM_BG_INWAIT:

		if( ENC_HBlankEndCheck( eew ) ){
			eew->seq++;
			// �E�B���h�E�G�t�F�N�g�j��
			ENC_BG_WndZiguzagu_Delete( task_w->p_ziguzagu );
		
			task_w->wait = ENCOUNT_SPTR_GYM_BG_AFTER_WAIT;
		}
		break;
		
	case ENCOUNT_SPTR_GYM_OAM_IN:
		task_w->wait --;
		if( task_w->wait >= 0 ){
			break;
		}

		// �W�����[�_�[��{�g��l�ݒ�
		scale = ENC_MakeVec( 
				ENCOUNT_SPTR_GYM_LEADER_SCALE_DEF, 
				ENCOUNT_SPTR_GYM_LEADER_SCALE_DEF, 0 );
		CLACT_SetScale( task_w->clact, &scale );
		
		// �͂��E�B���h�E�ݒ�
		ENC_WND_SetScaleWnd( 
				ENCOUNT_SPTR_GYM_OAM_START_Y,
				ENCOUNT_SPTR_GYM_BG_CY+ENCOUNT_SPTR_GYM_LEADER_DRAW_BOTTOM,
				ENCOUNT_SPTR_GYM_LEADER_SCALE_DEF,
				64, 0, &task_w->wnd_posi );
		G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_BG1|GX_WND_PLANEMASK_BG2|GX_WND_PLANEMASK_BG3|GX_WND_PLANEMASK_OBJ, TRUE );
		G2_SetWndOutsidePlane( GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_BG1|GX_WND_PLANEMASK_BG2|GX_WND_PLANEMASK_BG3, TRUE );
		GX_SetVisibleWnd(GX_WNDMASK_W0);
		
		ENC_AddMoveReqFx( &task_w->oam_move_x, 
				ENCOUNT_SPTR_GYM_OAM_START_X,
				cp_def->end_x,
				ENCOUNT_SPTR_GYM_OAM_X_SS,
				ENCOUNT_SPTR_GYM_OAM_MOVE_SYNC );
		CLACT_SetDrawFlag( task_w->clact, TRUE );
		CLACT_BGPriorityChg( task_w->clact, 0 );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

		matrix = ENC_MakeVec( 
				task_w->oam_move_x.x, 
				ENCOUNT_SPTR_GYM_OAM_START_Y, 0 );
		CLACT_SetMatrix( task_w->clact, &matrix );
		eew->seq++;
		break;
		
	case ENCOUNT_SPTR_GYM_OAM_INWAIT:

		result = ENC_AddMoveMainFx( &task_w->oam_move_x );
		matrix = ENC_MakeVec( 
				task_w->oam_move_x.x, 
				ENCOUNT_SPTR_GYM_OAM_START_Y, 0 );
		CLACT_SetMatrix( task_w->clact, &matrix );

		// �͂��E�B���h�E�ݒ�	OAM�͔��f��1�V���N�x��
		cp_matrix = CLACT_GetMatrix( task_w->clact );
		ENC_WND_SetScaleWnd( 
				cp_matrix->y,
				ENCOUNT_SPTR_GYM_BG_CY+ENCOUNT_SPTR_GYM_LEADER_DRAW_BOTTOM,
				ENCOUNT_SPTR_GYM_LEADER_SCALE_DEF,
				64, 0, &task_w->wnd_posi);

		if( result == TRUE ){
			eew->seq++;
		}
		break;
		
	case ENCOUNT_SPTR_GYM_OAM_FLASH_OUT:
		ENC_MoveReq( &task_w->flash, 0, 16, ENCOUNT_SPTR_GYM_FLASHOUT_SYNC );
		eew->seq++;
		break;
		
	case ENCOUNT_SPTR_GYM_OAM_FLASH_OUT_WAIT:
		result = ENC_MoveMain( &task_w->flash );
		ENC_SetMasterBrightnessVblank( &task_w->flash.x );
		if( result == TRUE ){
			// OAM�̃J���[�p���b�g�ύX
			ENC_CLACT_ResColorChange( task_w->clact, heapID, cp_def->type, 0, ENCOUNT_SPTR_GYM_LEADER_COLOR_FADE );
			eew->seq++;
		}
		break;
		
	case ENCOUNT_SPTR_GYM_OAM_FLASH_IN:
		ENC_MoveReq( &task_w->flash, 16, 0, ENCOUNT_SPTR_GYM_FLASHIN_SYNC );
		eew->seq++;
		break;
		
	case ENCOUNT_SPTR_GYM_OAM_FLASH_IN_WAIT:
		result = ENC_MoveMain( &task_w->flash );
		ENC_SetMasterBrightnessVblank( &task_w->flash.x );
		if( result == TRUE ){
			eew->seq++;
			task_w->wait = ENCOUNT_SPTR_GYM_FLASH_AFTER_WAIT;
		}
		break;
		
	case ENCOUNT_SPTR_GYM_WAIT:
		task_w->wait --;
		if( task_w->wait < 0 ){
			eew->seq ++;
		}
		break;
		
	case ENCOUNT_SPTR_GYM_WIPE:

		// �z���C�g�A�E�g
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_WHITE, ENCOUNT_SPTR_GYM_FADEOUT_SYNC, 1, HEAPID_FIELD );
		eew->seq ++;
		break;
		
	case ENCOUNT_SPTR_GYM_WIPEWAIT:
		ENC_MoveMainFx( &task_w->scale );
		// FX32_ONE�����̂́Ascale�̊J�n��1���炾����
		scale = ENC_MakeVec( 
				ENCOUNT_SPTR_GYM_LEADER_SCALE_DEF + task_w->scale.x - FX32_ONE, 
				ENCOUNT_SPTR_GYM_LEADER_SCALE_DEF + task_w->scale.x - FX32_ONE, 0 );
		CLACT_SetScale( task_w->clact, &scale );

		cp_matrix = CLACT_GetMatrix( task_w->clact );

		// ��ӂ̍��W�����߂�
		bottom_y = ENC_WND_SetScaleWndToolMakeBottomY( task_w->scale.x, ENCOUNT_SPTR_GYM_BG_CY, ENCOUNT_SPTR_GYM_LEADER_DRAW_BOTTOM );
		// �͂��E�B���h�E�ݒ�
		ENC_WND_SetScaleWnd( 
				cp_matrix->y,
				bottom_y,
				scale.y, 64, 0, &task_w->wnd_posi);
		
		
		if( WIPE_SYS_EndCheck() ) {
			eew->seq ++;
		}
		break;
		
	case ENCOUNT_SPTR_GYM_END:
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_WHITE );
		
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		// OAM�j��
		CLACT_Delete( task_w->clact );
		ENC_CLACT_ResDeleteEasy( &task_w->clact_sys, &task_w->clact_res );
		ENC_CLACT_Delete( &task_w->clact_sys );

		// �E�B���h�E�j��
		GX_SetVisibleWnd(GX_WNDMASK_NONE);

		sys_FreeMemory(HEAPID_FIELD, eew->work);
		return TRUE;
	}

	if( task_w->bg_auto_move == TRUE ){
		ENC_BG_SetAffineMtx( &task_w->bg_affine, eew->fsw->bgl, ENC_BG_AFFINE_FRAME, 
				task_w->scale.x, task_w->scale.x, 0,
				128, ENCOUNT_SPTR_GYM_BG_CY,
				task_w->auto_move_x );

		task_w->auto_move_x = (task_w->auto_move_x + ENCOUNT_SPTR_GYM_BG_AUTOMOVE_X) % 512;
	}

	if( eew->seq != ENCOUNT_SPTR_GYM_END ){
		CLACT_Draw( task_w->clact_sys.cas );
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief		�e�W��
 */
//-----------------------------------------------------------------------------
void EncountEffect_SPTR_IwaGym(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	BOOL result;
	result = EncountEffect_SpTr_GymMain( eew, HEAPID_FIELD, &ENCOUNT_SPTR_GymDef[0] );
	if( result == TRUE ){
		PMDS_taskDel(tcb);	//�^�X�N�I��
	}
}
void EncountEffect_SPTR_KusaGym(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	BOOL result;
	result = EncountEffect_SpTr_GymMain( eew, HEAPID_FIELD, &ENCOUNT_SPTR_GymDef[1] );
	if( result == TRUE ){
		PMDS_taskDel(tcb);	//�^�X�N�I��
	}
}
void EncountEffect_SPTR_MizuGym(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	BOOL result;
	result = EncountEffect_SpTr_GymMain( eew, HEAPID_FIELD, &ENCOUNT_SPTR_GymDef[2] );
	if( result == TRUE ){
		PMDS_taskDel(tcb);	//�^�X�N�I��
	}
}
void EncountEffect_SPTR_KakutouGym(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	BOOL result;
	result = EncountEffect_SpTr_GymMain( eew, HEAPID_FIELD, &ENCOUNT_SPTR_GymDef[3] );
	if( result == TRUE ){
		PMDS_taskDel(tcb);	//�^�X�N�I��
	}
}
void EncountEffect_SPTR_GoosutoGym(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	BOOL result;
	result = EncountEffect_SpTr_GymMain( eew, HEAPID_FIELD, &ENCOUNT_SPTR_GymDef[4] );
	if( result == TRUE ){
		PMDS_taskDel(tcb);	//�^�X�N�I��
	}
}
void EncountEffect_SPTR_KooriGym(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	BOOL result;
	result = EncountEffect_SpTr_GymMain( eew, HEAPID_FIELD, &ENCOUNT_SPTR_GymDef[5] );
	if( result == TRUE ){
		PMDS_taskDel(tcb);	//�^�X�N�I��
	}
}
void EncountEffect_SPTR_HaganeGym(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	BOOL result;
	result = EncountEffect_SpTr_GymMain( eew, HEAPID_FIELD, &ENCOUNT_SPTR_GymDef[6] );
	if( result == TRUE ){
		PMDS_taskDel(tcb);	//�^�X�N�I��
	}
}
void EncountEffect_SPTR_DenkiGym(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	BOOL result;
	result = EncountEffect_SpTr_GymMain( eew, HEAPID_FIELD, &ENCOUNT_SPTR_GymDef[7] );
	if( result == TRUE ){
		PMDS_taskDel(tcb);	//�^�X�N�I��
	}
}



//----------------------------------------------------------------------------
/**
 *	@brief	���ʎ擾
 */
//-----------------------------------------------------------------------------
static u32 EncountEffect_SPTR_ChanpSexCheck( FIELDSYS_WORK* p_fsys )
{	
	MYSTATUS* p_mystatus = SaveData_GetMyStatus( p_fsys->savedata );
	return MyStatus_GetMySex( p_mystatus );
}
//----------------------------------------------------------------------------
/**
 *	@brief	�l�V���@�`�����s�I����p�G���J�E���g�G�t�F�N�g
 *
 *	@param	eew		�G�t�F�N�g���[�N
 *	@param	heapID	�q�[�vID
 *	@param	cp_def	�f�t�@�C����`
 *
 *	@retval	TRUE		�I��
 *	@retval	FALSE		�r��
 */
//-----------------------------------------------------------------------------
static BOOL EncountEffect_SpTr_ChanpMain( ENCOUNT_EFFECT_WORK *eew, u32 heapID, const ENCOUNT_SPTR_CHANP_PARAM* cp_def )
{
	ENCOUNT_SPTR_CHANP* task_w = eew->work;
	BOOL result;
	VecFx32 matrix;
	VecFx32 scale;
	int i;
	fx32 dist;
	ENC_CLACT_RES_WORK* p_clact_res;
	int seq;

	switch( eew->seq ){
	case ENCOUNT_SPTR_CHANP_START:
		eew->work = sys_AllocMemory( heapID, sizeof(ENCOUNT_SPTR_CHANP) );	
		memset( eew->work, 0, sizeof(ENCOUNT_SPTR_CHANP) );
		task_w = eew->work;

		// �Z���A�N�^�[�Z�b�g�쐬
		ENC_CLACT_Init( &task_w->clact_sys, ENCOUNT_SPTR_CHANP_CELL_NUM, ENCOUNT_SPTR_CHANP_CELL_RES_NUM );

		// �O���t�B�b�N�ݒ�
		// ��l���j���`�F�b�N
		ENC_CLACT_ResLoadEasy(
				&task_w->clact_sys,
				&task_w->clact_res[0],
				NARC_field_encounteffect_cutin_dummy_char00_NCLR, 1,
				NARC_field_encounteffect_cutin_dummy_char00_NCGR,
				NARC_field_encounteffect_cutin_dummy_char00_NCER,
				NARC_field_encounteffect_cutin_dummy_char00_NANR,
				ENCOUNT_TR_GRASS_LOW_CELL_CONT_ID
				);

		// �G�ǂݍ���
		ENC_CLACT_ResLoadEasy(
				&task_w->clact_sys,
				&task_w->clact_res[1],
				NARC_field_encounteffect_cutin_dummy_char00_NCLR, 1,
				NARC_field_encounteffect_cutin_dummy_char00_NCGR,
				NARC_field_encounteffect_cutin_dummy_char00_NCER,
				NARC_field_encounteffect_cutin_dummy_char00_NANR,
				ENCOUNT_TR_GRASS_LOW_CELL_CONT_ID + 1
				);

		// �w�i�ǂݍ���
		ENC_CLACT_ResLoadEasy(
				&task_w->clact_sys,
				&task_w->clact_res[2],
				cp_def->waku_oam_cl, 0xC,
				NARC_field_encounteffect_cutin_chanpion00_NCGR,
				NARC_field_encounteffect_cutin_chanpion00_NCER,
				NARC_field_encounteffect_cutin_chanpion00_NANR,
				ENCOUNT_TR_GRASS_LOW_CELL_CONT_ID + 2
				);

		// �A�N�^�[�o�^
		scale = ENC_MakeVec( 
				ENCOUNT_SPTR_GYM_LEADER_SCALE_DEF, 
				ENCOUNT_SPTR_GYM_LEADER_SCALE_DEF, 0 );
		for( i=0; i<ENCOUNT_SPTR_CHANP_CELL_NUM; i++ ){
			if( i < (ENCOUNT_SPTR_CHANP_CELL_NUM - 1) ){
				p_clact_res = &task_w->clact_res[i];
				seq = 0;
			}else{
				p_clact_res = &task_w->clact_res[i - 1];
				seq = 1;
			}

			task_w->clact[i] = ENC_CLACT_Add( 
					&task_w->clact_sys, p_clact_res,
					0, 0, 0, 0);
			CLACT_SetDrawFlag( task_w->clact[i], FALSE );
			CLACT_AnmChg( task_w->clact[i], seq );
		}

		// ��l���O���t�B�b�N�o�^
		if( EncountEffect_SPTR_ChanpSexCheck( eew->fsw ) == 0 ){
			// �j
			ENC_CLACT_ResSetSoftSpriteDataTrOam( task_w->clact[0], heapID, TRTYPE_BOY, ENCOUNT_SPTR_CHANP_COLOR_FADE_EVY, ENCOUNT_SPTR_CHANP_COLOR_FADE, ENC_OAM_TR_CHAR_CUT_CX );
			task_w->hero_type  = TRTYPE_BOY;
		}else{
			// ��
			ENC_CLACT_ResSetSoftSpriteDataTrOam( task_w->clact[0], heapID, TRTYPE_GIRL, ENCOUNT_SPTR_CHANP_COLOR_FADE_EVY, ENCOUNT_SPTR_CHANP_COLOR_FADE, ENC_OAM_TR_CHAR_CUT_CX );
			task_w->hero_type  = TRTYPE_GIRL;
		}
		CLACT_SetAffineParam( task_w->clact[0], CLACT_AFFINE_DOUBLE );
		CLACT_SetScale( task_w->clact[0], &scale );

		// �l�V���O���t�B�b�N�o�^
		ENC_CLACT_ResSetSoftSpriteDataTrOam( task_w->clact[1], heapID, cp_def->enemy_tr_type, ENCOUNT_SPTR_CHANP_COLOR_FADE_EVY, ENCOUNT_SPTR_CHANP_COLOR_FADE, ENC_OAM_TR_CHAR_CUT_CX );
		CLACT_SetAffineParam( task_w->clact[1], CLACT_AFFINE_DOUBLE );
		CLACT_SetScale( task_w->clact[1], &scale );

		// BG�ʕ\��
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);

		eew->seq ++;
		break;
		
	case ENCOUNT_SPTR_CHANP_FLASH_INI:

		EncountFlashTask(MASK_MAIN_DISPLAY, 16, 16,  &eew->wait, 1);
		eew->seq++;
		break;
		
	case ENCOUNT_SPTR_CHANP_FLASH_WAIT:
		if( eew->wait ){
			eew->seq++;
		}
		break;

	case ENCOUNT_SPTR_CHANP_HERO_IN:
		ENC_AddMoveReqFx( &task_w->oam_move_x,
				ENCOUNT_SPTR_CHANP_HERO_MOVE_SX,
				ENCOUNT_SPTR_CHANP_HERO_MOVE_EX,
				ENCOUNT_SPTR_CHANP_HERO_MOVE_SS,
				ENCOUNT_SPTR_CHANP_HERO_MOVE_SYNC );
		matrix = ENC_MakeVec( 
				task_w->oam_move_x.x, 
				ENCOUNT_SPTR_CHANP_HERO_Y, 0 );
		CLACT_SetMatrix( task_w->clact[0], &matrix );
		matrix.y += ENCOUNT_SPTR_CHANP_HERO_Y_WAKU_OFS;
		matrix.x += ENCOUNT_SPTR_CHANP_HERO_X_WAKU_OFS;
		CLACT_SetMatrix( task_w->clact[2], &matrix );
		CLACT_SetDrawFlag( task_w->clact[0], TRUE );
		CLACT_SetDrawFlag( task_w->clact[2], TRUE );
		CLACT_SetAnmFlag( task_w->clact[2], TRUE );
		CLACT_SetAnmFrame( task_w->clact[2], FX32_ONE );
		eew->seq ++;
		break;
		
	case ENCOUNT_SPTR_CHANP_HERO_INWAIT:
		result = ENC_AddMoveMainFx( &task_w->oam_move_x );
		matrix = ENC_MakeVec( 
				task_w->oam_move_x.x, 
				ENCOUNT_SPTR_CHANP_HERO_Y, 0 );
		CLACT_SetMatrix( task_w->clact[0], &matrix );
		matrix.y += ENCOUNT_SPTR_CHANP_HERO_Y_WAKU_OFS;
		matrix.x += ENCOUNT_SPTR_CHANP_HERO_X_WAKU_OFS;
		CLACT_SetMatrix( task_w->clact[2], &matrix );

		if( result == TRUE ){
			eew->seq ++;
		}
		break;
		
	case ENCOUNT_SPTR_CHANP_HERO_FLASHOUT:
		ENC_MoveReq( &task_w->flash,
				0, 16,
				ENCOUNT_SPTR_CHANP_HERO_FLASHOUT_SYNC);
		eew->seq++;
		break;
		
	case ENCOUNT_SPTR_CHANP_HERO_FLASHOUTWAIT:
		result = ENC_MoveMain( &task_w->flash );
		ENC_SetMasterBrightnessVblank( &task_w->flash.x );
		if( result == TRUE ){
			// ��l���̃J���[�p���b�g�ύX
			// OAM�̃J���[�p���b�g�ύX
			ENC_CLACT_ResColorChange( task_w->clact[0], heapID, task_w->hero_type, 0, ENCOUNT_SPTR_CHANP_COLOR_FADE );
			eew->seq++;
		}
		break;

	case ENCOUNT_SPTR_CHANP_HERO_FLASHIN:
		ENC_MoveReq( &task_w->flash,
				16,0,
				ENCOUNT_SPTR_CHANP_HERO_FLASHIN_SYNC);
		eew->seq++;
		break;
		
	case ENCOUNT_SPTR_CHANP_HERO_FLASHINWAIT:
		result = ENC_MoveMain( &task_w->flash );
		ENC_SetMasterBrightnessVblank( &task_w->flash.x );
		if( result == TRUE ){
			eew->seq++;
		}
		break;
		
	case ENCOUNT_SPTR_CHANP_ENEMY_IN:
		ENC_AddMoveReqFx( &task_w->oam_move_x,
				ENCOUNT_SPTR_CHANP_ENEMY_MOVE_SX,
				ENCOUNT_SPTR_CHANP_ENEMY_MOVE_EX,
				ENCOUNT_SPTR_CHANP_ENEMY_MOVE_SS,
				ENCOUNT_SPTR_CHANP_ENEMY_MOVE_SYNC );
		matrix = ENC_MakeVec( 
				task_w->oam_move_x.x, 
				ENCOUNT_SPTR_CHANP_ENEMY_Y, 0 );
		CLACT_SetMatrix( task_w->clact[1], &matrix );
		matrix.y += ENCOUNT_SPTR_CHANP_ENEMY_Y_WAKU_OFS;
		matrix.x += ENCOUNT_SPTR_CHANP_ENEMY_X_WAKU_OFS;
		CLACT_SetMatrix( task_w->clact[3], &matrix );
		CLACT_SetDrawFlag( task_w->clact[1], TRUE );
		CLACT_SetDrawFlag( task_w->clact[3], TRUE );
		CLACT_SetAnmFlag( task_w->clact[3], TRUE );
		CLACT_SetAnmFrame( task_w->clact[3], FX32_ONE );
		
		eew->seq ++;
		break;
		
	case ENCOUNT_SPTR_CHANP_ENEMY_INWAIT:
		result = ENC_AddMoveMainFx( &task_w->oam_move_x );
		matrix = ENC_MakeVec( 
				task_w->oam_move_x.x, 
				ENCOUNT_SPTR_CHANP_ENEMY_Y, 0 );
		CLACT_SetMatrix( task_w->clact[1], &matrix );
		matrix.y += ENCOUNT_SPTR_CHANP_ENEMY_Y_WAKU_OFS;
		matrix.x += ENCOUNT_SPTR_CHANP_ENEMY_X_WAKU_OFS;
		CLACT_SetMatrix( task_w->clact[3], &matrix );

		if( result == TRUE ){
			eew->seq ++;
		}
		break;
		
	case ENCOUNT_SPTR_CHANP_ENEMY_FLASHOUT:
		ENC_MoveReq( &task_w->flash,
				0, 16,
				ENCOUNT_SPTR_CHANP_ENEMY_FLASHOUT_SYNC);
		eew->seq++;
		break;
		
	case ENCOUNT_SPTR_CHANP_ENEMY_FLASHOUTWAIT:
		result = ENC_MoveMain( &task_w->flash );
		ENC_SetMasterBrightnessVblank( &task_w->flash.x );
		if( result == TRUE ){
			// ��l���̃J���[�p���b�g�ύX
			// OAM�̃J���[�p���b�g�ύX
			ENC_CLACT_ResColorChange( task_w->clact[1], heapID, cp_def->enemy_tr_type, 0,ENCOUNT_SPTR_CHANP_COLOR_FADE );
			eew->seq++;
		}
		break;

	case ENCOUNT_SPTR_CHANP_ENEMY_FLASHIN:
		ENC_MoveReq( &task_w->flash,
				16, 0,
				ENCOUNT_SPTR_CHANP_ENEMY_FLASHIN_SYNC);
		eew->seq++;
		break;
		
	case ENCOUNT_SPTR_CHANP_ENEMY_FLASHINWAIT:
		result = ENC_MoveMain( &task_w->flash );
		ENC_SetMasterBrightnessVblank( &task_w->flash.x );
		if( result == TRUE ){
			eew->seq++;
		}
		break;
		
	case ENCOUNT_SPTR_CHANP_CAMERA_MOVE:
		task_w->camera = eew->fsw->camera_ptr;
		task_w->angle = GFC_GetCameraAngle( task_w->camera );


		ENC_MoveReq( &task_w->camera_angle, 
				task_w->angle.x,
				task_w->angle.x + cp_def->angle_x_move,
				cp_def->angle_move_sync );
		eew->seq++;
		break;
		
	case ENCOUNT_SPTR_CHANP_CAMERA_MOVE_WAIT:
		result = ENC_MoveMain( &task_w->camera_angle );
		task_w->angle.x = task_w->camera_angle.x;
		GFC_SetCameraAngleRev( &task_w->angle, task_w->camera );
		if( result == TRUE ){
			eew->seq++;
		}
		break;

	case ENCOUNT_SPTR_CHANP_WIPE:
		// �J����
		dist = GFC_GetCameraDistance( task_w->camera );
		ENC_AddMoveReqFx( &task_w->camera_dist, 
				dist,
				dist + ENCOUNT_SPTR_CHANP_CAMERA_MOVE_X,
				ENCOUNT_SPTR_CHANP_CAMERA_SS,
				ENCOUNT_SPTR_CHANP_WIPE_OUT_SYNC );

		// OAM
		ENC_AddMoveReqFx( &task_w->oam_move_x,
				0, ENCOUNT_SPTR_CHANP_OMA_MOVE_X,
				ENCOUNT_SPTR_CHANP_OAM_MOVE_XSS,
				ENCOUNT_SPTR_CHANP_WIPE_OUT_SYNC );	
		ENC_AddMoveReqFx( &task_w->oam_move_y,
				0, ENCOUNT_SPTR_CHANP_OMA_MOVE_Y,
				ENCOUNT_SPTR_CHANP_OAM_MOVE_YSS,
				ENCOUNT_SPTR_CHANP_WIPE_OUT_SYNC );	

		// �z���C�g�A�E�g
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_WHITE, ENCOUNT_SPTR_CHANP_WIPE_OUT_SYNC, 1, HEAPID_FIELD );
		eew->seq ++;
		break;
		
	case ENCOUNT_SPTR_CHANP_WIPEWAIT:
		ENC_AddMoveMainFx( &task_w->camera_dist );
		ENC_AddMoveMainFx( &task_w->oam_move_x );
		ENC_AddMoveMainFx( &task_w->oam_move_y );
		GFC_SetCameraDistance( task_w->camera_dist.x, task_w->camera );

		// ��l����
		matrix = ENC_MakeVec( 
				ENCOUNT_SPTR_CHANP_HERO_MOVE_EX - task_w->oam_move_x.x,
				ENCOUNT_SPTR_CHANP_HERO_Y + task_w->oam_move_y.x, 0 );
		CLACT_SetMatrix( task_w->clact[0], &matrix );
		matrix.y += ENCOUNT_SPTR_CHANP_HERO_Y_WAKU_OFS;
		matrix.x += ENCOUNT_SPTR_CHANP_HERO_X_WAKU_OFS;
		CLACT_SetMatrix( task_w->clact[2], &matrix );

		// �G����
		matrix = ENC_MakeVec( 
				ENCOUNT_SPTR_CHANP_ENEMY_MOVE_EX + task_w->oam_move_x.x,
				ENCOUNT_SPTR_CHANP_ENEMY_Y - task_w->oam_move_y.x, 0 );
		CLACT_SetMatrix( task_w->clact[1], &matrix );
		matrix.y += ENCOUNT_SPTR_CHANP_ENEMY_Y_WAKU_OFS;
		matrix.x += ENCOUNT_SPTR_CHANP_ENEMY_X_WAKU_OFS;
		CLACT_SetMatrix( task_w->clact[3], &matrix );


		if( WIPE_SYS_EndCheck() ) {
			eew->seq ++;
		}
		break;
		
	case ENCOUNT_SPTR_CHANP_END:
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_WHITE );
		
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		// OAM�j��
		for( i=0; i<ENCOUNT_SPTR_CHANP_CELL_NUM; i++ ){
			CLACT_Delete( task_w->clact[i] );
		}
		for( i=0; i<ENCOUNT_SPTR_CHANP_CELL_RES_NUM; i++ ){
			ENC_CLACT_ResDeleteEasy( &task_w->clact_sys, &task_w->clact_res[i] );
		}
		ENC_CLACT_Delete( &task_w->clact_sys );

		sys_FreeMemory(HEAPID_FIELD, eew->work);
		return TRUE;
	}

	if( eew->seq != ENCOUNT_SPTR_CHANP_END ){
		CLACT_Draw( task_w->clact_sys.cas );
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�l�V���@�`�����s�I��
 */
//-----------------------------------------------------------------------------
void EncountEffect_SPTR_Siten00(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	BOOL result;
	result = EncountEffect_SpTr_ChanpMain( eew, HEAPID_FIELD, &EncountSpTr_ChanpParam[0] );
	if( result == TRUE ){
		PMDS_taskDel(tcb);	//�^�X�N�I��
	}
}
void EncountEffect_SPTR_Siten01(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	BOOL result;
	result = EncountEffect_SpTr_ChanpMain( eew, HEAPID_FIELD, &EncountSpTr_ChanpParam[1] );
	if( result == TRUE ){
		PMDS_taskDel(tcb);	//�^�X�N�I��
	}
}
void EncountEffect_SPTR_Siten02(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	BOOL result;
	result = EncountEffect_SpTr_ChanpMain( eew, HEAPID_FIELD, &EncountSpTr_ChanpParam[2] );
	if( result == TRUE ){
		PMDS_taskDel(tcb);	//�^�X�N�I��
	}
}
void EncountEffect_SPTR_Siten03(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	BOOL result;
	result = EncountEffect_SpTr_ChanpMain( eew, HEAPID_FIELD, &EncountSpTr_ChanpParam[3] );
	if( result == TRUE ){
		PMDS_taskDel(tcb);	//�^�X�N�I��
	}
}
void EncountEffect_SPTR_Chanpion(TCB_PTR tcb, void* work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	BOOL result;
	result = EncountEffect_SpTr_ChanpMain( eew, HEAPID_FIELD, &EncountSpTr_ChanpParam[4] );
	if( result == TRUE ){
		PMDS_taskDel(tcb);	//�^�X�N�I��
	}
}
