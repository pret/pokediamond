//============================================================================================
/**
 * @file	encount_effect.c
 * @bfief	�G���J�E���g����
 * @author	GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system/lib_pack.h"
#include "system/brightness.h"
#include "field_event.h"
#include "motion_bl.h"
#include "system/arc_util.h"

#include "fieldmap_work.h"
#include "fieldsys.h"

#include "battle/attr_def.h"
#include "ev_pokemon.h"

#include "system/palanm.h"


#define __ENCOUNT_EFFECT_H_GLOBAL__
#include "encount_effect.h"
#define __ECCOUNT_EFFECT_DEF_H_GLOBAL
#define __ECCOUNT_EFFECT_DEF_H_GLOBAL_VAL
#include "encount_effect_def.h"

#include "ecnt_tomo.h"
#include "encount_effect_sub.h"


//-----------------------------------------------------------------------------
//
// �G���J�E���g�p�֐��e�[�u��
//
//=============================================================================
static const TCB_FUNC EncountEffectTask[] ={

	EncountEffect_Field_GrassLevelLow,
	EncountEffect_Field_GrassLevelHigh,
	EncountEffect_Field_WaterLevelLow,
	EncountEffect_Field_WaterLevelHigh,
	EncountEffect_Field_DanLevelLow,
	EncountEffect_Field_DanLevelHigh,
	EncountEffect_Trainer_GrassLevelLow,
	EncountEffect_Trainer_GrassLevelHigh,
	EncountEffect_Trainer_WaterLevelLow,
	EncountEffect_Trainer_WaterLevelHigh,
	EncountEffect_Trainer_DanLevelLow,
	EncountEffect_Trainer_DanLevelHigh,

	EncountEffect_SPTR_IwaGym,			// �N���K�l�W��
	EncountEffect_SPTR_KusaGym,         // �n�N�^�C�W��
	EncountEffect_SPTR_MizuGym,         // �m���Z�W��
	EncountEffect_SPTR_KakutouGym,      // �g�o���W��
	EncountEffect_SPTR_GoosutoGym,      // ���X�K�g�W��
	EncountEffect_SPTR_KooriGym,        // �L�b�T�L�W��
	EncountEffect_SPTR_HaganeGym,       // �~�I�W��
	EncountEffect_SPTR_DenkiGym,        // �i�M�T�W��

	EncountEffect_SPTR_Siten00,
	EncountEffect_SPTR_Siten01,
	EncountEffect_SPTR_Siten02,
	EncountEffect_SPTR_Siten03,

	EncountEffect_SPTR_Chanpion,

	EncountEffect_Legend_Normal,
	EncountEffect_Legend_Package,
	
	EncountEffect_Ginga_Normal,
	EncountEffect_Ginga_Special,

	EncountEffect_Special_Tower,
	EncountEffect_Special_Double,

	
/*	EncountEffectMotionBl00,
	EncountEffectMotionBl01,//*/

};

//-------------------------------------
//	
//	�r�b�g�}�b�v����
//	
//=====================================
// �r�b�g�}�b�v�E�B���h�E�h��Ԃ��I�u�W�F�N�g
typedef struct _ENC_BMP_FILL_OBJ{
	ENC_MOVE_WORK move_x;
	ENC_MOVE_WORK move_y;
	GF_BGL_BMPWIN* p_bmp;
	u8 width;
	u8 height;
	u8 move_flg;
	u8 col;
} ;

// �r�b�g�}�b�v�E�B���h�E�u���b�N��h��Ԃ��I�u�W�F�N�g
typedef struct _ENC_BMP_FILL_BLOCK{
	ENC_MOVE_WORK move_x;
	ENC_MOVE_WORK move_y;
	GF_BGL_BMPWIN* p_bmp;
	u8 width;
	u8 height;
	u8 move_flg;
	u8 col;
} ;

static void ENC_BMP_Fill( GF_BGL_BMPWIN* p_bmp, s32 top, s32 bottom, s32 left, s32 right, u8 col );

// �r�b�g�}�b�v�u���b�N���ߐs�����V�X�e��
#define ENCOUNT_BLOCK_MOVE_WIDTH	( 32 )	// �u���b�N�T�C�Y
#define ENCOUNT_BLOCK_MOVE_HEIGHT	( 32 )	// �u���b�N�T�C�Y
#define ENCOUNT_BLOCK_MOVE_MAT_Y	( -16 )	// �J�n���W
#define ENCOUNT_BLOCK_MOVE_MOVE_Y	( 192 + ENCOUNT_BLOCK_MOVE_MAT_Y )	// �ړ�����
#define ENCOUNT_BLOCK_MOVE_OBJNUM	( 48 )	// x�u���b�N�Ŗ��߂�
#define ENCOUNT_BLOCK_MOVE_X_NUM	( 8 )	// ���̐�
#define ENCOUNT_BLOCK_MOVE_Y_NUM	( 6 )	// �c�̐�
static const u8 ENCOUNT_BLOCK_MOVE_MoveParam[ ENCOUNT_BLOCK_MOVE_X_NUM ] = {	// �o�Ă���x���W�̏��ԃe�[�u��
	 0, 2, 5, 7, 1, 6, 3, 4 
};
typedef struct _ENC_BMP_FILL_BLOCK_MOVE{
	GF_BGL_BMPWIN* p_bmp;
	ENC_BMP_FILL_BLOCK* p_block[ ENCOUNT_BLOCK_MOVE_OBJNUM ];
	u8	block_count;
	u8	block_end_count;
	u8	move_sync;
	u8	start_sync;
	s8	wait;
	u8	col;
	u8	init_flg;
	u8	dummy[1];
};

// �~�`�r�b�g�}�b�v�h��Ԃ�
typedef struct _ENC_BMP_CIRCLE_FILL{
	GF_BGL_BMPWIN* p_bmp;
	ENC_MOVE_WORK rota;
	u8 move_flg;
	u8 col;
	u8 dummy[2];
};
static void EncBmpCircleFill_Fill( GF_BGL_BMPWIN* p_bmp, u16 last_rota, u16 now_rota, u8 col );

// �t���b�V���A�E�g�@�I�u�W�F
#define ENC_BMP_FLASH_CIRCLE_NUM	( 8 )
static const u16 FlashOutParam[8][2] = {
	{ 0, 23 },
	{ 45, 22 },
	{ 45, 68 },
	{ 90, 67 },		// �����͌Œ�@���ꂶ��Ȃ��Ƃ��܂������Ȃ�
	{ 91, 113 },	// �����͌Œ�@���ꂶ��Ȃ��Ƃ��܂������Ȃ�
	{ 135, 112 },
	{ 135, 158 },
	{ 180, 157 },
};
typedef struct _ENC_BMP_FLASH_OUT {
	ENC_BMP_CIRCLE_FILL* p_circle[ ENC_BMP_FLASH_CIRCLE_NUM ];
	u8 move_flg;
	u8 dummy[3];
};


//-------------------------------------
//	
//	��ײ�Ƚ�֌W
//	
//=====================================

static void ENC_BrightnessVset( TCB_PTR tcb, void* work );

//-------------------------------------
//
//	�ŏ��̃s�J�s�J�̃^�X�N
//
//=====================================
typedef struct{
	int seq;
	u32 flash_num;
	int count;
	int disp;		// ��ʎw��
	u32 end_bright;
	u32 sub_bright;
	BR_BRIGHTNESS_FADE br_main;
	BR_BRIGHTNESS_FADE br_sub;
	BOOL* end;		// �I�������p
} BR_FLASH_TASK;
#define FLASH_EFF_SYNC_SUB	( 8 )
#define FLASH_EFF_SYNC_ONE	( 3 )

// �J�n�G�t�F�N�g�^�X�N�i�ŏ��̌�����̂Ȃǂ𐧌�j
static void BR_FlashTask(TCB_PTR tcb, void *work);
enum{
	FADE_SUB_EFFECT,
	FADE_EFFECT,
	FADE_WAIT,
	FADE_RET_EFFECT,
	FADE_RET_WAIT,
	END_EFFECT,
};

//-------------------------------------
//
//	H�u�����N�p
//
//=====================================
//---------------------------
// BG�����Ɋ���HBlank�p
//===========================
typedef struct {
	int x;			// ���̈ړ��ʒu
	int speed;		// ���x
	BOOL* end_check;// �I���`�F�b�N
} ENC_HB_BG_CUT;
#define ENC_HB_BG_CUT_ST	(100)		// �����x
#define ENC_HB_BG_CUT_END_X	(25000)
static void ENC_BG_Cut_HBlank(FIELD_HBLANK_OBJ* p_hobj, void* p_work);

//-------------------------------------
//	���h�b�g���Ƃɍ��E�ɕ����Ĉړ�
//=====================================
typedef struct _ENC_HB_BG_SLICE{
	ENC_ADDMOVE_WORK_FX move_x;
	u32 dot;
	u32 seq;
	FIELD_HBLANK_SYS* p_hsys;
	FIELD_HBLANK_OBJ* p_hobj;
	TCB_PTR tcb;
	BOOL* end_check;// �I���`�F�b�N
} ;
#define END_HB_BG_SLICE_TCB_PRI	( 1024 )
#define END_HB_BG_SLICE_INIT_TCB_PRI	( 1024 )
static void ENC_BG_Slice_SetUp_Tcb( TCB_PTR tcb, void* p_work );
static void ENC_BG_Slice_Tcb( TCB_PTR tcb, void* p_work );
static void ENC_BG_Slice_HBlank(FIELD_HBLANK_OBJ* p_hobj, void* p_work);
static void ENC_BG_Slice_End( ENC_HB_BG_SLICE* p_work );


//-------------------------------------
// �E�B���h�E�Ŏ΂߂ɉ�ʂ��B���Ă���
//=====================================
typedef struct _ENC_HB_BG_WND_SLANT{
	ENC_ADDMOVE_WORK_FX move_x;
	ENC_ADDMOVE_WORK_FX move_y;
	u32 cut_y;
	u32 seq;
	FIELD_HBLANK_SYS* p_hsys;
	FIELD_HBLANK_OBJ* p_hobj;
	TCB_PTR tcb;
	BOOL* end_check;// �I���`�F�b�N
};
#define END_HB_BG_WND_SLANT_TCB_PRI	( 1024 )
#define END_HB_BG_WND_SLANT_INIT_TCB_PRI	( 1024 )
#define END_HB_BG_WND_SLANT_CUT_Y	( 96 )
#define END_HB_BG_WND_SLANT_MOVE_X	( 255*FX32_ONE )
#define END_HB_BG_WND_SLANT_MOVE_Y	( 96*FX32_ONE )
static void ENC_BG_WndSlant_SetUp_Tcb( TCB_PTR tcb, void* p_work );
static void ENC_BG_WndSlant_Tcb( TCB_PTR tcb, void* p_work );
static void ENC_BG_WndSlant_HBlank(FIELD_HBLANK_OBJ* p_hobj, void* p_work);
static void ENC_BG_WndSlant_End( ENC_HB_BG_WND_SLANT* p_work );

// �J�b�g�C���p�@�W�O�U�O�E�B���h�E
typedef struct _ENC_HB_BG_WND_ZIGUZAGU{
	ENC_MOVE_WORK move_x;
	u32 seq;
	u8  ziguzagu_buf[ 192 ];
	FIELD_HBLANK_SYS* p_hsys;
	FIELD_HBLANK_OBJ* p_hobj;
	TCB_PTR tcb;
	BOOL* end_check;// �I���`�F�b�N
} ;
#define ENC_BG_WND_ZIGUZAGU_MOVE_S		( 0 )
#define ENC_BG_WND_ZIGUZAGU_MOVE_E		( 255 )
#define END_HB_BG_WND_ZIGUZAGU_TCB_PRI	( 1024 )
#define END_HB_BG_WND_ZIGUZAGU_INIT_TCB_PRI	( 1024 )
static void ENC_BG_WndZiguzagu_SetUp_Tcb( TCB_PTR tcb, void* p_work );
static void ENC_BG_WndZiguzagu_Tcb( TCB_PTR tcb, void* p_work );
static void ENC_BG_WndZiguzagu_HBlank(FIELD_HBLANK_OBJ* p_hobj, void* p_work);
static void ENC_BG_WndZiguzagu_End( ENC_HB_BG_WND_ZIGUZAGU* p_work );



//-------------------------------------
//	�O���t�B�b�N��
//=====================================
#define ENC_BG_AFFINCONT_TASK	( 1024 )
static void ENC_BG_AffinContSetTcb( TCB_PTR tcb, void* work );

// OAM
static void ENC_OAM_TransOamPltt( CLACT_WORK_PTR clact, void* data, u32 size );
static void ENC_OAM_TransOamChar( CLACT_WORK_PTR clact, void* data, u32 size );
#define ENC_OAM_TR_CHAR_SIZE_X	( 64 )	// OAM�L�����N�^�P�ʃT�C�Y
#define ENC_OAM_TR_CHAR_SIZE_Y	( 64 )	// OAM�L�����N�^�P�ʃT�C�Y
#define ENC_OAM_TR_CHAR_ONELINE	( 8*8 )
#define ENC_OAM_TR_CHAR_BUFF_SIZE 	( 0x800 )// �L�����N�^�o�b�t�@�T�C�Y
#define ENC_OAM_TR_CHAR_CUT_Y	( 0 )	// ���ꂾ�����炵���Ƃ��납�甲���o��
static void* ENC_OAM_TrCharMake( const NNSG2dCharacterData* cp_chardata, u32 heap, u32* p_size, u32 ofs_cx );

static void ENC_WND_SetWndPositionVWait( TCB_PTR tcb, void* p_work );


//----------------------------------------------------------------------------
/**
 *
 *@brief	�G���J�E���g�G�t�F�N�g�J�n
 *
 *@param	No		�G���J�E���g�G�t�F�N�gNO
 *@param	*fsw	�t�B�[���h�V�X�e�����[�N�̃|�C���^
 *@param	end		�I���`�F�b�N�p�@TRUE�F�I������ 
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void EncountEffectStart(int No, FIELDSYS_WORK *fsw, BOOL* end )
{
	TCB_PTR tcb;
	ENCOUNT_EFFECT_WORK *eew;
	tcb = PMDS_taskAdd(EncountEffectTask[No], sizeof(ENCOUNT_EFFECT_WORK), TCB_TSK_PRI, HEAPID_FIELD);
	eew = TCB_GetWork(tcb);
	eew->fsw = fsw;
	eew->end = end;		// �I���t���O�ݒ�
	if(eew->end != NULL){
		*(eew->end) = FALSE;
	}
	eew->hblank_flg = FALSE;
}





//-----------------------------------------------------------------------------
//
//	�ŏ��̃s�J�s�J�p�^�X�N�J�n�֐�
//
//=============================================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	�ŏ��̃t���b�V���̕\��������^�X�N�����s����
 *					
 *@param	disp	���C����ʂɂ�����:MASK_MAIN_DISPLAY
 *					�T�u��ʂɂ�����:MASK_SUB_DISPLAY
 *					����ʂɂ�����:MASK_DOUBLE_DISPLAY
 *
 *@param	end		�I��������TRUE��Ԃ��t���O
 *@param	flash_num	�t���b�V����
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void EncountFlashTask(int disp, u32 bright_color, u32 sub_bright_color, BOOL* end, u32 flash_num )
{
	TCB_PTR tcb;
	BR_FLASH_TASK *eew;

	eew = sys_AllocMemory( HEAPID_FIELD, sizeof(BR_FLASH_TASK) );
	memset( eew, 0, sizeof(BR_FLASH_TASK) );
	TCB_Add( BR_FlashTask, eew, TCB_TSK_PRI );
	
	eew->end = end;		// �I���t���O�ݒ�
	if(eew->end != NULL){
		*(eew->end) = FALSE;
	}
	eew->disp = disp;
	eew->end_bright = bright_color;
	eew->sub_bright = sub_bright_color;
	eew->flash_num	= flash_num;
}

//------------------------------------------------------------------
/**
 * 
 * �G�t�F�N�g
 *
 * �ŏ��̃s�J�s�J�\��
 * 
 * @param   tcb		�^�X�N�|�C���^
 * @param   work	���[�N�|�C���^
 *
 * @retval  none		
 *
 * �s�J�s�J�@20�V���N�g�p
 */
//------------------------------------------------------------------
static void BR_FlashTask(TCB_PTR tcb, void *work)
{
	BR_FLASH_TASK *eew = work;

	switch(eew->seq){
	case FADE_SUB_EFFECT:
		if(eew->disp == MASK_MAIN_DISPLAY){
			//�u���b�N�A�E�g
//			ChangeBrightnessRequest( 40,-16,0, eew->plane, MASK_SUB_DISPLAY);
			ENC_ChangeMstBrightness( &eew->br_sub, 0, eew->sub_bright, MASK_SUB_DISPLAY, FLASH_EFF_SYNC_SUB );
		}else{
			if(eew->disp == MASK_SUB_DISPLAY){
				//�u���b�N�A�E�g
//				ChangeBrightnessRequest(40,-16,0, eew->plane, MASK_MAIN_DISPLAY);
				ENC_ChangeMstBrightness( &eew->br_sub, 0, eew->sub_bright, MASK_MAIN_DISPLAY, FLASH_EFF_SYNC_SUB );
			}
		}
		eew->seq++;
		break;

	case FADE_EFFECT:
		//�z���C�g�A�E�g
//		ChangeBrightnessRequest(4,16,0,eew->plane,eew->disp);
		ENC_ChangeMstBrightness( &eew->br_main, 0, eew->end_bright, eew->disp, FLASH_EFF_SYNC_ONE );
		eew->seq++;
		break;
		
	case FADE_WAIT:
		if( ENC_ChangeMstBrightnessMain( &eew->br_main ) ){
			eew->seq++;
		}
		break;
	case FADE_RET_EFFECT:
		//�z���C�g�C��
//		ChangeBrightnessRequest(4,0,16,eew->plane,eew->disp);
		ENC_ChangeMstBrightness( &eew->br_main, eew->end_bright, 0, eew->disp, FLASH_EFF_SYNC_ONE );
		eew->seq++;
		break;
		
	case FADE_RET_WAIT:
		if( ENC_ChangeMstBrightnessMain( &eew->br_main ) ){
			
			eew->count++;
			if(eew->count==eew->flash_num){
				eew->seq = END_EFFECT;
			}else{
				eew->seq = FADE_EFFECT;
			}
		}
		break;
	case END_EFFECT:		// ���C���G�t�F�N�g�Ɉړ�
		eew->seq = 0;
		eew->count = 0;

		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}

		TCB_Delete(tcb);	//�^�X�N�I��
		sys_FreeMemoryEz( eew );
		return ;
	}

	// �T�u�ʃt�F�[�h
	ENC_ChangeMstBrightnessMain( &eew->br_sub );
}


//----------------------------------------------------------------------------
//
//
//	�G�t�F�N�g�pH�u�����N�֐��S
//
//
//============================================================================
// H�u�����N�I���`�F�b�N
//----------------------------------------------------------------------------
/**
 *	@brief	H�u�����N�I���`�F�b�N
 *	@param	p_work 
 *	@return
 */
//-----------------------------------------------------------------------------
BOOL ENC_HBlankEndCheck( ENCOUNT_EFFECT_WORK* p_work )
{
	return p_work->hblank_flg;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	BG�ʂ�S�ĉ��ɃJ�b�g�X�^�[�g
 *
 *@param	p_ew	�̪�ă��[�N
 *
 *@return	none
 */
//-----------------------------------------------------------------------------
void ENC_BG_Cut_Start(ENCOUNT_EFFECT_WORK* p_ew)
{
	ENC_HB_BG_CUT* p_work;

	p_work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENC_HB_BG_CUT) );
	memset( p_work, 0, sizeof(ENC_HB_BG_CUT) );
	FLDHBLANK_OBJ_Add( p_ew->fsw->fldmap->hblanksys, ENC_BG_Cut_HBlank, p_work );
	p_ew->hblank_flg = FALSE;
	p_work->end_check = &p_ew->hblank_flg;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	BG�ʂ�S�ĉ��ɃJ�b�g����
 *
 *@param	p_hobj	h�u�����N�I�u�W�F�N�g
 *@param	p_work	���[�N
 *
 *@return	none
 */
//-----------------------------------------------------------------------------
static void ENC_BG_Cut_HBlank(FIELD_HBLANK_OBJ* p_hobj, void* p_work)
{
	ENC_HB_BG_CUT* hbw = (ENC_HB_BG_CUT*)p_work;
	int v_count;		// V�J�E���g
	int	x_num;			// BG�I�t�Z�b�g�ɐݒ肷��l

	// V�J�E���^���擾���A�O�̎��͈ړ��l���v�Z����
	v_count = GX_GetVCount();
	if(v_count == 0){

		if((hbw->x + hbw->speed) <= ENC_HB_BG_CUT_END_X){
			hbw->x += hbw->speed;			// �ړ�
			hbw->speed += ENC_HB_BG_CUT_ST;	// ����
		}else{
			
			*hbw->end_check = TRUE;
			FLDHBLANK_OBJ_Delete( p_hobj );
			sys_FreeMemoryEz( p_work );
			return ;
		}
	}

	// 96���������A96�ȏ���E�Ɉړ�������
	x_num = hbw->x / 100;
	if(v_count >= 96){
		x_num = -x_num;
	}
	G2_SetBG0Offset(x_num, 0);
	G2_SetBG1Offset(x_num, 0);
	G2_SetBG2Offset(x_num, 0);
	G2_SetBG3Offset(x_num, 0);
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
void ENC_MoveReq( ENC_MOVE_WORK* p_work, int s_x, int e_x, int count_max )
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
BOOL ENC_MoveMain( ENC_MOVE_WORK* p_work )
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
void ENC_MoveReqFx( ENC_MOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, int count_max )
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
BOOL ENC_MoveMainFx( ENC_MOVE_WORK_FX* p_work )
{
	fx32 w_x;

	// ���ݍ��W�擾
	w_x = FX_Mul( p_work->dis_x, p_work->count << FX32_SHIFT );
	w_x = FX_Div( w_x, p_work->count_max << FX32_SHIFT );
	
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
 *	@brief	��������ėp�@������
 *
 *	@param	p_work	���[�N
 *	@param	s_x		�J�n���W
 *	@param	e_x		�I�����W
 *	@param	s_s		�J�n���x
 *	@param	count_max �����l
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_AddMoveReqFx( ENC_ADDMOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, fx32 s_s, int count_max )
{
	fx32 t_x_t;	// �^�C���̂Q��
	fx32 vot;	// �����x���^�C��
	fx32 dis;
	fx32 a;

	dis = e_x - s_x;
	
	// �����l�����߂�
	// a = 2(x - vot)/(t*t)
	t_x_t = (count_max * count_max) << FX32_SHIFT;
	vot = FX_Mul( s_s, count_max * FX32_ONE );
	vot = dis - vot;
	vot = FX_Mul( vot, 2*FX32_ONE );
	a = FX_Div( vot, t_x_t );

	p_work->x = s_x;
	p_work->s_x = s_x;
	p_work->s_s = s_s;
	p_work->s_a = a;
	p_work->count = 0;
	p_work->count_max = count_max;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�������상�C��
 *
 *	@param	p_work	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL ENC_AddMoveMainFx( ENC_ADDMOVE_WORK_FX* p_work )
{
	fx32 dis;
	fx32 t_x_t;
	fx32 calc_work;
	fx32 vot;
	
	// �������x�^��
	// dis = vot + 1/2( a*(t*t) )
	vot = FX_Mul( p_work->s_s, p_work->count << FX32_SHIFT );
	t_x_t = (p_work->count * p_work->count) << FX32_SHIFT;
	calc_work = FX_Mul( p_work->s_a, t_x_t );
	calc_work = FX_Div( calc_work, 2*FX32_ONE );	// 1/2(a*(t*t))
	dis = vot + calc_work;	///<�ړ�����

	p_work->x = p_work->s_x + dis;


	if( (p_work->count + 1) <= p_work->count_max ){
		p_work->count++;
		return FALSE;
	}

	p_work->count = p_work->count_max;
	return TRUE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	Ͻ���u���C�g�l�X�ݒ�
 *
 *	@param	disp	��
 *	@param	no		�l
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_SetMstBrightness( int disp, int no )
{
	// �u���C�g�l�X����
	if( disp == MASK_MAIN_DISPLAY ){
		GX_SetMasterBrightness(no);
	}else{
		GXS_SetMasterBrightness(no);
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	Ͻ���u���C�g�l�X�ύX�@�t�F�[�h�f�[�^�i�[
 *
 *	@param	p_data		�i�[��
 *	@param	start		�J�n�l
 *	@param	end			�I���l
 *	@param	disp		��
 *	@param	sync		�V���N��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_ChangeMstBrightness( BR_BRIGHTNESS_FADE* p_data, int start, int end, int disp, int sync )
{
	p_data->disp = disp;
	ENC_MoveReq( &p_data->brightness, start, end, sync );
}

//----------------------------------------------------------------------------
/**
 *	@brief	Ͻ���u���C�g�l�X�ύX�@�t�F�[�h���C��
 *
 *	@param	p_data	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL ENC_ChangeMstBrightnessMain( BR_BRIGHTNESS_FADE* p_data )
{
	BOOL result;
	result = ENC_MoveMain( &p_data->brightness );
	
	// V�u�����N���Ԓ��ɐݒ肵�Ȃ��Ƃ��ꂢ�Ƀt�F�[�h���Ȃ�
	VWaitTCB_Add( ENC_BrightnessVset, p_data, TCB_VWAIT_BR_TSK_PRI );
	return result;
}

//----------------------------------------------------------------------------
/**
 *	@brief	V�u�����N���Ԓ�����ײ�Ƚ�l��ݒ肷��^�X�N
 *
 *	@param	tcb		TCB���[�N
 *	@param	work	���[�N
 *
 *	@return	none
 *	V�u�����N���Ԓ��ɐݒ肵�Ȃ��Ƃ��ꂢ�Ƀt�F�[�h���Ȃ�
 */
//-----------------------------------------------------------------------------
static void ENC_BrightnessVset( TCB_PTR tcb, void* work )
{
	BR_BRIGHTNESS_FADE* p_data = work;
	ENC_SetMstBrightness( p_data->disp, p_data->brightness.x );
	TCB_Delete( tcb );
}


//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�쐬
 *
 *	@param	none
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
ENC_HB_BG_SLICE* ENC_BG_Slice_Alloc( void )
{
	ENC_HB_BG_SLICE* p_work;
	
	p_work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENC_HB_BG_SLICE) );
	memset( p_work, 0, sizeof(ENC_HB_BG_SLICE) );

	// �E�B���h�E�}�X�N�ݒ�
	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE );	
	G2_SetWnd1InsidePlane( GX_WND_PLANEMASK_NONE, FALSE );	

	return p_work;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�j��
 *
 *	@param	p_work 
 *
 *	@return none	
 */
//-----------------------------------------------------------------------------
void ENC_BG_Slice_Delete( ENC_HB_BG_SLICE* p_work )
{
	if( p_work->p_hobj != NULL ){
		ENC_BG_Slice_End( p_work );
	}

	// �E�B���h�E�}�X�N�j��
	GX_SetVisibleWnd( GX_WNDMASK_NONE );

	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BGSlice�J�n
 *
 *	@param	p_ew	�G�t�F�N�g���[�N
 *	@param	p_eff	BG�X���C�X
 *	@param	dot		�����h�b�g��	1�h�b�g���ƂȂ�1
 *	@param	sync	�G�t�F�N�g�����V���N��
 *	@param	s_x		�J�nx�l
 *	@param	e_x		�I��X�l
 *	@param	s_s		�����x
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
void ENC_BG_Slice_Start( ENCOUNT_EFFECT_WORK* p_ew, ENC_HB_BG_SLICE* p_eff, u8 dot, u32 sync, int s_x, int e_x, fx32 s_s )
{
	// �J�n�ς�
	GF_ASSERT( p_eff->p_hobj == NULL );
	
	p_ew->hblank_flg	= FALSE;
	p_eff->p_hsys		= p_ew->fsw->fldmap->hblanksys;
	p_eff->dot			= dot;
	p_eff->seq			= 0;
	p_eff->end_check	= &p_ew->hblank_flg;
	ENC_AddMoveReqFx( &p_eff->move_x, s_x, e_x, s_s, sync );

	if( s_x >= 0 ){
		G2_SetWnd0Position( 0, 0, 255 - s_x, 192 );
		G2_SetWnd1Position( 0, 0, 1 + s_x, 192 );	// +1���Ȃ��Ƃ���Ȃ�
	}else{
		G2_SetWnd0Position( 0, 0, 255 + s_x, 192 );
		G2_SetWnd1Position( 0, 0, 1 - s_x, 192 );	// +1���Ȃ��Ƃ���Ȃ�
	}
	
	// �����^�X�N�o�^�֐�
	VWaitTCB_Add( ENC_BG_Slice_SetUp_Tcb, p_eff, END_HB_BG_SLICE_INIT_TCB_PRI );
}

// �ݒ�֐�
static void ENC_BG_Slice_SetUp_Tcb( TCB_PTR tcb, void* p_work )
{
	ENC_HB_BG_SLICE* p_eff = p_work;

	p_eff->tcb = VWaitTCB_Add( ENC_BG_Slice_Tcb, p_eff, END_HB_BG_SLICE_TCB_PRI );
	p_eff->p_hobj = FLDHBLANK_OBJ_Add( p_eff->p_hsys, ENC_BG_Slice_HBlank, p_eff );

	TCB_Delete( tcb );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�J�b�g�p�����[�^�ύX�֐�
 *
 *	@param	p_ew	���[�N
 *	@param	p_work	���[�N
 *	@param	dot		�h�b�g��
 *	@param	sync	�V���N��
 *	@param	s_x		���J�n�ʒu
 *	@param	e_x		���I���ʒu
 *	@param	s_s		�����x
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_BG_Slice_Change( ENCOUNT_EFFECT_WORK* p_ew, ENC_HB_BG_SLICE* p_work, u8 dot, u32 sync, int s_x, int e_x, fx32 s_s )
{
	// �����I���ς݂Ȃ�G���[
	GF_ASSERT( ENC_HBlankEndCheck( p_ew ) == FALSE );	

	p_work->dot			= dot;
	p_work->seq			= 0;
	ENC_AddMoveReqFx( &p_work->move_x, s_x, e_x, s_s, sync );
}


//----------------------------------------------------------------------------
/**
 *	@brief	BG�X���C�X�^�X�N
 *
 *	@param	tcb		TCB���[�N
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ENC_BG_Slice_Tcb( TCB_PTR tcb, void* p_work )
{
	ENC_HB_BG_SLICE* p_data = p_work;
	s32 num;
	
	switch( p_data->seq ){
	case 0:
		if( ENC_AddMoveMainFx( &p_data->move_x ) ){
			p_data->seq ++;
		}
		num = p_data->move_x.x >> FX32_SHIFT;
		if( num >= 0 ){
			G2_SetWnd0Position( 0, 0, 255 - num, 192 );
			G2_SetWnd1Position( 0, 0, 1 + num, 192 );	// +1���Ȃ��Ƃ���Ȃ�
		}else{
			G2_SetWnd0Position( 0, 0, 255 + num, 192 );
			G2_SetWnd1Position( 0, 0, 1 - num, 192 );	// +1���Ȃ��Ƃ���Ȃ�
		}
		break;

	case 1:	// H�u�����N�ŏ�̒l�����f�����̂łP�V���N�҂@�I��
		ENC_BG_Slice_End( p_work );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG�X���C�X�I��
 *
 *	@param	p_work ���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ENC_BG_Slice_End( ENC_HB_BG_SLICE* p_work )
{
	// �E�B���h�E�}�X�N�ݒ�
	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE );	
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_NONE, FALSE );	
	G2_SetWnd0Position( 0,0,0,0 );
	GX_SetVisibleWnd( GX_WNDMASK_W0 );
	
	*(p_work->end_check) = TRUE;
	FLDHBLANK_OBJ_Delete( p_work->p_hobj );
	p_work->p_hobj = NULL;
	TCB_Delete( p_work->tcb );
	p_work->tcb = NULL;
}


//----------------------------------------------------------------------------
/**
 *	@brief	BG�X���C�X�@H�u�����N�R�[���o�b�N
 *
 *	@param	p_hobj	�I�u�W�F�N�g
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ENC_BG_Slice_HBlank(FIELD_HBLANK_OBJ* p_hobj, void* p_work)
{
	ENC_HB_BG_SLICE* p_data = p_work;
	int v_count;		// V�J�E���g
	int	x_num;			// BG�I�t�Z�b�g�ɐݒ肷��l

	// V�J�E���^���擾���A�O�̎��͈ړ��l���v�Z����
	v_count = GX_GetVCount();
	
	if( ((v_count / p_data->dot) % 2) == 0 ){
		x_num = p_data->move_x.x >> FX32_SHIFT;
	}else{
		x_num = -p_data->move_x.x >> FX32_SHIFT;
	}
	G2_SetBG0Offset(x_num, 0);
	G2_SetBG1Offset(x_num, 0);
	G2_SetBG2Offset(x_num, 0);
	G2_SetBG3Offset(x_num, 0);

	if( x_num >= 0 ){
		GX_SetVisibleWnd( GX_WNDMASK_W0 );
		G2_SetWndOutsidePlane( GX_WND_PLANEMASK_NONE, FALSE );	
	}else{
		GX_SetVisibleWnd( GX_WNDMASK_W1 );
		G2_SetWndOutsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE );	
	}
}


//----------------------------------------------------------------------------
/**
 *		�y�E�B���h�E�΂߃J�b�g�z
 *	@brief		���[�N�m��
 */
//-----------------------------------------------------------------------------
ENC_HB_BG_WND_SLANT* ENC_BG_WndSlant_Alloc( void )
{
	ENC_HB_BG_WND_SLANT* p_work;

	p_work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENC_HB_BG_WND_SLANT) );
	memset( p_work, 0, sizeof(ENC_HB_BG_WND_SLANT) );
	
	// �E�B���h�E�}�X�N�ݒ�
	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE );	
	G2_SetWnd1InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE );	
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_NONE, FALSE );	

	return p_work;
}

//----------------------------------------------------------------------------
/**
 *		�y�E�B���h�E�΂߃J�b�g�z
 *	@brief		���[�N�j��
 */
//-----------------------------------------------------------------------------
void ENC_BG_WndSlant_Delete( ENC_HB_BG_WND_SLANT* p_work )
{
	if( p_work->p_hobj != NULL ){
		ENC_BG_WndSlant_End( p_work );
	}

	// �E�B���h�E�}�X�N�j��
	GX_SetVisibleWnd( GX_WNDMASK_NONE );

	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *		�y�E�B���h�E�΂߃J�b�g�z
 *	@brief	�J�n
 *
 *	@param	p_ew		�G���J�E���g�G�t�F�N�g���[�N
 *	@param	p_eff		�G�t�F�N�g���[�N
 *	@param	sync		�V���N��
 *	@param	x_ss		X���������x
 *	@param	y_ss		Y���������x
 */
//-----------------------------------------------------------------------------
void ENC_BG_WndSlant_Start( ENCOUNT_EFFECT_WORK* p_ew, ENC_HB_BG_WND_SLANT* p_eff, u32 sync, fx32 x_ss, fx32 y_ss )
{
	// �J�n�ς�
	GF_ASSERT( p_eff->p_hobj == NULL );
	
	p_ew->hblank_flg	= FALSE;
	p_eff->p_hsys		= p_ew->fsw->fldmap->hblanksys;
	p_eff->cut_y		= END_HB_BG_WND_SLANT_CUT_Y;
	p_eff->seq			= 0;
	p_eff->end_check	= &p_ew->hblank_flg;
	ENC_AddMoveReqFx( &p_eff->move_x, 0, END_HB_BG_WND_SLANT_MOVE_X, x_ss, sync );
	ENC_AddMoveReqFx( &p_eff->move_y, 0, END_HB_BG_WND_SLANT_MOVE_Y, y_ss, sync );

	G2_SetWnd0Position( 0, 0, 255, 192 );
	G2_SetWnd1Position( 0, 0, 255, 192 );
	
	// �����^�X�N�o�^�֐�
	VWaitTCB_Add( ENC_BG_WndSlant_SetUp_Tcb, p_eff, END_HB_BG_WND_SLANT_INIT_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *		�y�E�B���h�E�΂߃J�b�g�z
 *	@brief	�Z�b�g�A�b�v�^�X�N
 */
//-----------------------------------------------------------------------------
static void ENC_BG_WndSlant_SetUp_Tcb( TCB_PTR tcb, void* p_work )
{
	ENC_HB_BG_WND_SLANT* p_eff = p_work;

	p_eff->tcb = VWaitTCB_Add( ENC_BG_WndSlant_Tcb, p_eff, END_HB_BG_WND_SLANT_TCB_PRI );
	p_eff->p_hobj = FLDHBLANK_OBJ_Add( p_eff->p_hsys, ENC_BG_WndSlant_HBlank, p_eff );

	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *		�y�E�B���h�E�΂߃J�b�g�z
 *	@brief	�����^�X�N
 */
//-----------------------------------------------------------------------------
static void ENC_BG_WndSlant_Tcb( TCB_PTR tcb, void* p_work )
{
	ENC_HB_BG_WND_SLANT* p_data = p_work;
	s32 x_num;
	s32 y_num;
	
	switch( p_data->seq ){
	case 0:
		ENC_AddMoveMainFx( &p_data->move_y );
		if( ENC_AddMoveMainFx( &p_data->move_x ) ){
			p_data->seq ++;
		}
		x_num = p_data->move_x.x >> FX32_SHIFT;
		y_num = p_data->move_y.x >> FX32_SHIFT;
		G2_SetWnd0Position( 0, 0, 255 - x_num, 96 - y_num );
		G2_SetWnd1Position( x_num, 96 + y_num, 255, 192);
		break;

	case 1:	// H�u�����N�ŏ�̒l�����f�����̂łP�V���N�҂@�I��
		ENC_BG_WndSlant_End( p_work );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *		�y�E�B���h�E�΂߃J�b�g�z
 *	@brief	H�u�����N�֐�
 */
//-----------------------------------------------------------------------------
static void ENC_BG_WndSlant_HBlank(FIELD_HBLANK_OBJ* p_hobj, void* p_work)
{
	ENC_HB_BG_WND_SLANT* p_data = p_work;
	int v_count;		// V�J�E���g
	int	x_num;			// BG�I�t�Z�b�g�ɐݒ肷��l
	int	y_num;			// BG�I�t�Z�b�g�ɐݒ肷��l

	// V�J�E���^���擾���A�O�̎��͈ړ��l���v�Z����
	v_count = GX_GetVCount();
	
	if( v_count <= p_data->cut_y ){
		GX_SetVisibleWnd( GX_WNDMASK_W0 );
	}else{
		GX_SetVisibleWnd( GX_WNDMASK_W1 );
	}
}

//----------------------------------------------------------------------------
/**
 *		�y�E�B���h�E�΂߃J�b�g�z
 *	@brief	�I���֐�
 */
//-----------------------------------------------------------------------------
static void ENC_BG_WndSlant_End( ENC_HB_BG_WND_SLANT* p_work )
{
	// �E�B���h�E�}�X�N�ݒ�
	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE );	
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_NONE, FALSE );	
	G2_SetWnd0Position( 0,0,0,0 );
	GX_SetVisibleWnd( GX_WNDMASK_W0 );
	
	*(p_work->end_check) = TRUE;
	FLDHBLANK_OBJ_Delete( p_work->p_hobj );
	p_work->p_hobj = NULL;
	TCB_Delete( p_work->tcb );
	p_work->tcb = NULL;
}




//----------------------------------------------------------------------------
/**
 *	@brief	�A�t�B��BG�ݒ�
 *
 *	@param	p_bgl	BGL
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_BG_SetAffineCont( GF_BGL_INI* p_bgl )
{
	VWaitTCB_Add( ENC_BG_AffinContSetTcb, p_bgl, ENC_BG_AFFINCONT_TASK );
}

//----------------------------------------------------------------------------
/**
 *	@brief		���ӂ���BG�ݒ�
 */
//-----------------------------------------------------------------------------
static void ENC_BG_AffinContSetTcb( TCB_PTR tcb, void* work )
{
	GF_BGL_INI* p_bgl = work;

	{
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_1,GX_BGMODE_0, GX_BG0_AS_3D
		};
		GF_BGL_InitBG(&BGsys_data);
	}

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );	

	{	// MAIN DISP�i�G�t�F�N�g�P�j
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlExit( p_bgl, GF_BGL_FRAME1_M );
		GF_BGL_BGControlSet( p_bgl, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME1_M, 32, 0, HEAPID_FIELD );
		GF_BGL_ScrClear( p_bgl, GF_BGL_FRAME1_M );
		// �\��OFF
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	}

	{	// MAIN DISP�i�G�t�F�N�g�Q�j
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_23,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlExit( p_bgl, GF_BGL_FRAME2_M );
		GF_BGL_BGControlSet( p_bgl, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME2_M, 32, 0, HEAPID_FIELD );
		GF_BGL_ScrClear( p_bgl, GF_BGL_FRAME2_M );
		// �\��OFF
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
	}

	{	// �A�t�B��BG
		GF_BGL_BGCNT_HEADER AffBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_23,
			0, TRUE, 0, FALSE
		};
		GF_BGL_BGControlExit( p_bgl, ENC_BG_AFFINE_FRAME );
		GF_BGL_BGControlSet( p_bgl, ENC_BG_AFFINE_FRAME, &AffBgCntDat, GF_BGL_MODE_AFFINE );
		GF_BGL_ClearCharSet( ENC_BG_AFFINE_FRAME, 32, 0, HEAPID_FIELD );
		GF_BGL_ScrClear( p_bgl, ENC_BG_AFFINE_FRAME );

		// �\��OFF
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
	}

	TCB_Delete( tcb );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�A�t�B��BG�ݒ�
 *
 *	@param	scrn_idx		�X�N���[���C���f�b�N�X
 *	@param	char_idx		�L�����N�^�C���f�b�N�X
 *	@param	pltt_idx		�p���b�g�C���f�b�N�X
 *	@param	p_bgl			BGL
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_BG_SetAffineBG( u32 scrn_idx, u32 char_idx, u32 pltt_idx, GF_BGL_INI* p_bgl )
{

	// �O���t�B�b�N�ǂݍ���
	ArcUtil_PalSet( ARC_ENCOUNTEFFECT, pltt_idx, PALTYPE_MAIN_BG, 0, 0, HEAPID_FIELD );
	ArcUtil_BgCharSet( ARC_ENCOUNTEFFECT, char_idx, p_bgl, ENC_BG_AFFINE_FRAME, 0, 0, FALSE, HEAPID_FIELD );
	ArcUtil_ScrnSet( ARC_ENCOUNTEFFECT, scrn_idx, p_bgl, ENC_BG_AFFINE_FRAME, 0, 0, FALSE, HEAPID_FIELD );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ʏ�BG�ݒ�
 *
 *	@param	scrn_idx	�X�N���[���C���f�b�N�X
 *	@param	char_idx	�L�����N�^�C���f�b�N�X
 *	@param	pltt_idx	�p���b�g�C���f�b�N�X
 *	@param	pltt_no		�p���b�g�i���o�[
 *	@param	pltt_num	�p���b�g��
 *	@param	p_bgl		BGL
 *	@param	frame		BG�t���[��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_BG_SetNormalBG( u32 scrn_idx, u32 char_idx, u32 pltt_idx, u32 pltt_no, u32 pltt_num, GF_BGL_INI* p_bgl, u32 frame )
{
	void* buff;
	NNSG2dScreenData* p_scrn;
	
	// �O���t�B�b�N�ǂݍ���
	ArcUtil_PalSet( ARC_ENCOUNTEFFECT, pltt_idx, PALTYPE_MAIN_BG, pltt_no*32, pltt_num*32, HEAPID_FIELD );
	ArcUtil_BgCharSet( ARC_ENCOUNTEFFECT, char_idx, p_bgl, frame, 0, 0, FALSE, HEAPID_FIELD );

	// �X�N���[���f�[�^�ǂݍ���
	buff = ArcUtil_ScrnDataGet( ARC_ENCOUNTEFFECT, scrn_idx, FALSE, &p_scrn, HEAPID_FIELD );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_bgl, frame,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	// �p���b�g�����킹��
	GF_BGL_ScrPalChange( p_bgl, frame,
			0, 0, 
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8,
			pltt_no );

	sys_FreeMemoryEz( buff );

	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req( p_bgl, frame );
}

//----------------------------------------------------------------------------
/**
 *	@brief		�A�t�B���X�N���[���ݒ�^�X�N
 */
//-----------------------------------------------------------------------------
static void ENC_BG_SetAffineMtxTcb( TCB_PTR tcb, void* p_work )
{
	ENC_BG_SET_AFFINEPARAM* p_data = p_work;

	GF_BGL_AffineScrollSet( p_data->p_bgl, p_data->frame, 
			GF_BGL_SCROLL_X_SET, p_data->sc_x,
			&p_data->mtx, p_data->cx, p_data->cy );

	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�t�B���f�[�^�ݒ�֐�
 *
 *	@param	p_bgl		BGL
 *	@param	frame		�t���[��
 *	@param	scale_x		�g�kx
 *	@param	scale_y		�g�ky
 *	@param	rota		��]
 *	@param	cx			���SX�@�i�h�b�g�P�ʁj
 *	@param	cy			���SY�@�i�h�b�g�P�ʁj
 *	@param	sc_x		�X�N���[�����W
 *	@param	sc_y		�X�N���[�����W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_BG_SetAffineMtx( ENC_BG_SET_AFFINEPARAM* p_work, GF_BGL_INI* p_bgl, u32 frame, fx32 scale_x, fx32 scale_y, u16 rota, int cx, int cy, int sc_x )
{
	
	MTX_Identity22( &p_work->mtx );

	// �g���]�s��쐬
	MTX_Rot22( &p_work->mtx, FX_SinIdx( rota ), FX_CosIdx( rota ) );
	MTX_ScaleApply22( &p_work->mtx, &p_work->mtx, FX_Div( FX32_ONE, scale_x ), FX_Div( FX32_ONE, scale_y ) );

	p_work->p_bgl	= p_bgl;
	p_work->frame	= frame;
	p_work->cx		= cx;
	p_work->cy		= cy;
	p_work->sc_x	= sc_x;
	VWaitTCB_Add( ENC_BG_SetAffineMtxTcb, p_work, ENC_BG_SET_AFFINE_MTX_PRI );
}


//-----------------------------------------------------------------------------
/**
 *
 *		OAM�ݒ�֘A
 *
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[�Z�b�g�ȂǍ쐬
 *
 *	@param	p_sys		���[�N
 *	@param	work_num	���[�N��
 *	@param	res_num		���\�[�X��
 */
//-----------------------------------------------------------------------------
void ENC_CLACT_Init( ENC_CLACT_SYS* p_sys, int work_num, int res_num )
{
	int i;
	
	// �Z���A�N�^�[�Z�b�g�쐬
	p_sys->cas = CLACT_U_SetEasyInit( work_num, &p_sys->renddata, HEAPID_FIELD );

	// ���\�[�X�}�l�[�W���쐬
	for( i=0; i<4; i++ ){
		p_sys->resMan[i] = CLACT_U_ResManagerInit( res_num, i, HEAPID_FIELD );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�X�e�����j��
 *
 *	@param	p_sys	�V�X�e�����[�N
 */
//-----------------------------------------------------------------------------
void ENC_CLACT_Delete( ENC_CLACT_SYS* p_sys )
{
	int i;
	
	CLACT_DestSet( p_sys->cas );
	
	for( i=0; i<4; i++ ){
		CLACT_U_ResManagerDelete( p_sys->resMan[i] );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�P���ȃ��\�[�X�ǂݍ���
 *
 *	@param	p_sys		�Ǘ��V�X�e��
 *	@param	p_work		�f�[�^�i�[��
 *	@param	pltt_idx	�p���b�g
 *	@param	pltt_num	�p���b�g�ǂݍ��ݐ�
 *	@param	char_idx	�L�����N�^
 *	@param	cel_idx		�Z��
 *	@param	anm_idx		�A�j��
 *	@param	cont_id		�Ǘ�ID
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_CLACT_ResLoadEasy( ENC_CLACT_SYS* p_sys, ENC_CLACT_RES_WORK* p_work, u32 pltt_idx, u32 pltt_num, u32 char_idx, u32 cel_idx, u32 anm_idx, u32 cont_id )
{
	// �L�����N�^
	p_work->resobj[0] = CLACT_U_ResManagerResAddArcChar_AllocType( p_sys->resMan[0],
			ARC_ENCOUNTEFFECT, char_idx, FALSE, cont_id,
			NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_FIELD, ALLOC_BOTTOM );

	// �p���b�g
	p_work->resobj[1] = CLACT_U_ResManagerResAddArcPltt( p_sys->resMan[1],
			ARC_ENCOUNTEFFECT, pltt_idx, FALSE, cont_id,
			NNS_G2D_VRAM_TYPE_2DMAIN, pltt_num, HEAPID_FIELD );

	// �Z��
	p_work->resobj[2] = CLACT_U_ResManagerResAddArcKindCell( p_sys->resMan[2],
			ARC_ENCOUNTEFFECT, cel_idx, FALSE, cont_id,
			CLACT_U_CELL_RES, HEAPID_FIELD );

	// �A�j��
	p_work->resobj[3] = CLACT_U_ResManagerResAddArcKindCell( p_sys->resMan[3],
			ARC_ENCOUNTEFFECT, anm_idx, FALSE, cont_id,
			CLACT_U_CELLANM_RES, HEAPID_FIELD );


	// Vram�]��
	CLACT_U_CharManagerSetAreaCont( p_work->resobj[0] );	
	CLACT_U_ResManagerResOnlyDelete( p_work->resobj[0] );
	CLACT_U_PlttManagerSetCleanArea( p_work->resobj[1] );	
//	CLACT_U_ResManagerResOnlyDelete( p_work->resobj[1] );
//	�p���b�g�͔j�����Ȃ��A�r���Ńp���b�g��ύX���邱�Ƃ����邽��

	// �w�b�_�[�쐬
	CLACT_U_MakeHeader( &p_work->head,
			cont_id, cont_id, cont_id, cont_id,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
			0, 0,
			p_sys->resMan[0], p_sys->resMan[1], 
			p_sys->resMan[2], p_sys->resMan[3], NULL, NULL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�P�����\�[�X�j��
 *
 *	@param	p_sys	�V�X�e�����[�N
 *	@param	p_work	���[�N
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_CLACT_ResDeleteEasy( ENC_CLACT_SYS* p_sys, ENC_CLACT_RES_WORK* p_work )
{
	int i;
	CLACT_U_CharManagerDelete( p_work->resobj[0] );
	CLACT_U_PlttManagerDelete( p_work->resobj[1] );

	// ���\�[�X���S�j��
	for( i=0; i<4; i++ ){
		CLACT_U_ResManagerResDelete( p_sys->resMan[i], p_work->resobj[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J���[�p���b�g�ύX
 *
 *	@param	clact		�Z���A�N�^�[���[�N
 *	@param	p_work		���[�N
 */
//-----------------------------------------------------------------------------
void ENC_CLACT_ResColorChange( CLACT_WORK_PTR clact, u32 heap, u32 tr_type, u8 evy, u16 next_rgb )
{
	SOFT_SPRITE_ARC ssa;
	NNSG2dPaletteData* p_pltt;
	void* p_pltt_buff;
	u16* dest;

	TrTypeGraArcDataGet( &ssa, tr_type );

	// �f�[�^�쐬��
	dest = sys_AllocMemory( heap, 32 );

	// �L�����N�^�ƃp���b�g�擾
	p_pltt_buff = ArcUtil_PalDataGet( ssa.arc_no, ssa.index_pal, &p_pltt, heap );

	SoftFade( p_pltt->pRawData, dest, 16, evy, next_rgb );

	// �p���b�g�]��
	ENC_OAM_TransOamPltt( clact, dest, 32 );

	sys_FreeMemoryEz( dest );
	sys_FreeMemoryEz( p_pltt_buff );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�^�[�o�^
 *
 *	@param	p_sys		�V�X�e�����[�N
 *	@param	p_work		���\�[�X���[�N
 *	@param	x			�����W
 *	@param	y			�����W
 *	@param	z			�����W
 *	@param	pri			�D�揇��
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
CLACT_WORK_PTR ENC_CLACT_Add( ENC_CLACT_SYS* p_sys, ENC_CLACT_RES_WORK* p_work, fx32 x, fx32 y, fx32 z, int pri )
{
	CLACT_ADD_SIMPLE add;
	CLACT_WORK_PTR act;

	add.ClActSet	= p_sys->cas;
	add.ClActHeader	= &p_work->head;
	add.mat.x		= x;
	add.mat.y		= y;
	add.mat.z		= z;
	add.pri			= pri;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= HEAPID_FIELD;

	act = CLACT_AddSimple( &add );
	GF_ASSERT( act );
	return act;
} 

//----------------------------------------------------------------------------
/**
 *	@brief	�x�N�g���쐬
 *
 *	@param	x	���l
 *	@param	y	���l
 *	@param	z	���l
 *
 *	@return	�x�N�g��
 */
//-----------------------------------------------------------------------------
VecFx32 ENC_MakeVec( fx32 x, fx32 y, fx32 z )
{
	VecFx32 vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�̃L�����N�^�ƃp���b�g���g���[�i�[�̎҂ɂ���
 *
 *	@param	clact		�Z���f�[�^
 *	@param	heap		�q�[�v
 *	@param	tr_type		�g���[�i�[�^�C�v
 *
 *	@param ofs_cx		�؂���X�L�����N�^�I�t�Z�b�g�l
 */
//-----------------------------------------------------------------------------
void ENC_CLACT_ResSetSoftSpriteDataTrOam( CLACT_WORK_PTR clact, u32 heap, u32 tr_type, u8 evy, u16 next_rgb, u32 ofs_cx )
{
	SOFT_SPRITE_ARC ssa;
	void* p_char;
	NNSG2dCharacterData* p_chardata;
	u32* p_charbuff; 
	u32 size;
		
	TrTypeGraArcDataGet( &ssa, tr_type );

	// �L�����N�^�ƃp���b�g�擾
	p_char = ArcUtil_CharDataGet( ssa.arc_no, ssa.index_chr, FALSE, &p_chardata, heap );

	// ����
	SoftSpriteChrMask( (u8*)p_chardata->pRawData );

	// �p���b�g�͂��̏����ōs��
	ENC_CLACT_ResColorChange( clact, heap, tr_type, evy, next_rgb );
	
	// OAM�p�L�����N�^�f�[�^����
	p_charbuff = ENC_OAM_TrCharMake( p_chardata, heap, &size, ofs_cx );

	// �L�����N�^�]��
	ENC_OAM_TransOamChar( clact, p_charbuff, size );

	sys_FreeMemoryEz( p_charbuff );
	sys_FreeMemoryEz( p_char );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�b�g���pOAM�L�����N�^�̐���
 *
 *	@param	p_chardata		�\�t�g�E�F�A�X�v���C�g�p�L�����N�^�f�[�^
 *	@param	heap			�q�[�v
 *	@param	ofs_cx			���ꂾ�����炵���Ƃ��납�甲���o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void* ENC_OAM_TrCharMake( const NNSG2dCharacterData* cp_chardata, u32 heap, u32* p_size, u32 ofs_cx )
{
	u32 * p_charbuff;
	int i, j;
	int char_idx;
	int raw_char_idx;
	const u32 * cp_char_raw = cp_chardata->pRawData; 

	p_charbuff = sys_AllocMemory( heap, ENC_OAM_TR_CHAR_BUFF_SIZE );


	for( i=0; i<ENC_OAM_TR_CHAR_SIZE_Y; i++ ){
		raw_char_idx = ((i+ENC_OAM_TR_CHAR_CUT_Y) * cp_chardata->W );
		char_idx = ((i/8)*ENC_OAM_TR_CHAR_ONELINE) + (i%8);

		for( j=0; j<ENC_OAM_TR_CHAR_SIZE_X / 8; j++ ){
			p_charbuff[ char_idx + (j*8) ] = cp_char_raw[ raw_char_idx + j + ofs_cx ];
		}
	}

	*p_size = ENC_OAM_TR_CHAR_BUFF_SIZE;

	return p_charbuff;
}

//----------------------------------------------------------------------------
/**
 *	@brief		OAM�̃p���b�g�ē]��
 *
 */
//-----------------------------------------------------------------------------
static void ENC_OAM_TransOamPltt( CLACT_WORK_PTR clact, void* data, u32 size )
{
	NNSG2dImagePaletteProxy * pltt;

	pltt = CLACT_PaletteProxyGet( clact );
	DC_FlushRange( data, size );
	GX_LoadOBJPltt( 
			data,
			NNS_G2dGetImagePaletteLocation( pltt, NNS_G2D_VRAM_TYPE_2DMAIN ),
			size );
}

//----------------------------------------------------------------------------
/**
 *	@brief		�L�����N�^�f�[�^�ē]��
 */
//-----------------------------------------------------------------------------
static void ENC_OAM_TransOamChar( CLACT_WORK_PTR clact, void* data, u32 size )
{
	NNSG2dImageProxy * p_char;

	p_char = CLACT_ImageProxyGet( clact );
	DC_FlushRange( data, size );
	GX_LoadOBJ( 
			data,
			NNS_G2dGetImageLocation( p_char, NNS_G2D_VRAM_TYPE_2DMAIN ),
			size );
}

//----------------------------------------------------------------------------
/**
 *		�y�r�b�g�}�b�v�E�B���h�E�h��Ԃ��I�u�W�F�N�g�z
 *	@brief	���[�N�̊m��
 *
 *	@param	heapID	�q�[�vID
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
ENC_BMP_FILL_OBJ* ENC_BMP_FillObjAlloc( u32 heapID )
{
	ENC_BMP_FILL_OBJ* p_work;

	p_work = sys_AllocMemory( heapID, sizeof(ENC_BMP_FILL_OBJ) );
	memset( p_work, 0, sizeof(ENC_BMP_FILL_OBJ) );
	return p_work;
}

//----------------------------------------------------------------------------
/**
 *		�y�r�b�g�}�b�v�E�B���h�E�h��Ԃ��I�u�W�F�N�g�z
 *	@brief	���[�N�j��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void ENC_BMP_FillObjDelete( ENC_BMP_FILL_OBJ* p_work )
{
	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *		�y�r�b�g�}�b�v�E�B���h�E�h��Ԃ��I�u�W�F�N�g�z
 *	@brief	�����J�n
 *
 *	@param	p_work		���[�N
 *	@param	s_x			�h��Ԃ��J�n�����W
 *	@param	e_x			�h��Ԃ��I�������W
 *	@param	s_y			�h��Ԃ��J�n�����W
 *	@param	e_y			�h��Ԃ��I�������W
 *	@param	sync		�V���N��
 *	@param	p_bmp		�r�b�g�}�b�v
 *	@param	width		��
 *	@param	height		����
 *	@param	col			�h��Ԃ��p���b�g�ԍ�
 */
//-----------------------------------------------------------------------------
void ENC_BMP_FillObjStart( ENC_BMP_FILL_OBJ* p_work, int s_x, int e_x, int s_y, int e_y, int sync, GF_BGL_BMPWIN* p_bmp, u32 width, u32 height, u8 col )
{
	GF_ASSERT( p_work->move_flg == FALSE );

	// �����p�����[�^
	ENC_MoveReq( &p_work->move_x, s_x, e_x, sync );
	ENC_MoveReq( &p_work->move_y, s_y, e_y, sync );

	// ���̑��p�����[�^
	p_work->p_bmp	= p_bmp;	// �h��Ԃ��r�b�g�}�b�v
	p_work->width	= width;	// �h��Ԃ���
	p_work->height	= height;	// �h��Ԃ�����
	p_work->col		= col;		// �h��Ԃ��J���[�ԍ�

	p_work->move_flg = TRUE;
}

//----------------------------------------------------------------------------
/**
 *		�y�r�b�g�}�b�v�E�B���h�E�h��Ԃ��I�u�W�F�N�g�z
 *	@brief	�������C��
 *
 *	@param	p_work	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL ENC_BMP_FillObjMain( ENC_BMP_FILL_OBJ* p_work )
{
	BOOL result;
	s16 top, bottom, left, right;
	if( p_work->move_flg == FALSE ){
		return TRUE;
	}
	
	result = ENC_MoveMain( &p_work->move_x );
	ENC_MoveMain( &p_work->move_y );

	left = p_work->move_x.x - (p_work->width/2);
	top = p_work->move_y.x - (p_work->height/2);
	right = left + p_work->width;
	bottom = top + p_work->height;

	// �r�b�g�}�b�v�h��Ԃ�
	ENC_BMP_Fill( p_work->p_bmp, top, bottom, left, right, p_work->col );

	return result;
}


//----------------------------------------------------------------------------
/**
 *		�y�r�b�g�}�b�v�u���b�N��h��Ԃ��I�u�W�F�N�g�z
 *	@brief	���[�N�̊m��
 *
 *	@param	heapID	�q�[�vID
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
ENC_BMP_FILL_BLOCK* ENC_BMP_FillBlockAlloc( u32 heapID )
{
	ENC_BMP_FILL_BLOCK* p_work;

	p_work = sys_AllocMemory( heapID, sizeof(ENC_BMP_FILL_BLOCK) );
	memset( p_work, 0, sizeof(ENC_BMP_FILL_BLOCK) );
	return p_work;
}

//----------------------------------------------------------------------------
/**
 *		�y�r�b�g�}�b�v�u���b�N��h��Ԃ��I�u�W�F�N�g�z
 *	@brief	���[�N�j��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void ENC_BMP_FillBlockDelete( ENC_BMP_FILL_BLOCK* p_work )
{
	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *		�y�r�b�g�}�b�v�u���b�N��h��Ԃ��I�u�W�F�N�g�z
 *	@brief	�����J�n
 *
 *	@param	p_work		���[�N
 *	@param	s_x			�h��Ԃ��J�n�����W
 *	@param	e_x			�h��Ԃ��I�������W
 *	@param	s_y			�h��Ԃ��J�n�����W
 *	@param	e_y			�h��Ԃ��I�������W
 *	@param	sync		�V���N��
 *	@param	p_bmp		�r�b�g�}�b�v
 *	@param	width		��
 *	@param	height		����
 *	@param	col			�h��Ԃ��p���b�g�ԍ�
 */
//-----------------------------------------------------------------------------
void ENC_BMP_FillBlockStart( ENC_BMP_FILL_BLOCK* p_work, int s_x, int e_x, int s_y, int e_y, int sync, GF_BGL_BMPWIN* p_bmp, u32 width, u32 height, u8 col )
{
	GF_ASSERT( p_work->move_flg == FALSE );

	// �����p�����[�^
	ENC_MoveReq( &p_work->move_x, s_x, e_x, sync );
	ENC_MoveReq( &p_work->move_y, s_y, e_y, sync );

	// ���̑��p�����[�^
	p_work->p_bmp	= p_bmp;	// �h��Ԃ��r�b�g�}�b�v
	p_work->width	= width;	// �h��Ԃ���
	p_work->height	= height;	// �h��Ԃ�����
	p_work->col		= col;		// �h��Ԃ��J���[�ԍ�

	p_work->move_flg = TRUE;
}

//----------------------------------------------------------------------------
/**
 *		�y�r�b�g�}�b�v�u���b�N��h��Ԃ��I�u�W�F�N�g�z
 *	@brief	�������C��
 *
 *	@param	p_work	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL ENC_BMP_FillBlockMain( ENC_BMP_FILL_BLOCK* p_work )
{
	BOOL result;
	s16 top, bottom, left, right;
	if( p_work->move_flg == FALSE ){
		return TRUE;
	}

	// 1�O������
	left = p_work->move_x.x - (p_work->width/2);
	top = p_work->move_y.x - (p_work->height/2);
	right = left + p_work->width;
	bottom = top + p_work->height;
	ENC_BMP_Fill( p_work->p_bmp, top, bottom, left, right, 0 );
	
	result = ENC_MoveMain( &p_work->move_x );
	ENC_MoveMain( &p_work->move_y );

	left = p_work->move_x.x - (p_work->width/2);
	top = p_work->move_y.x - (p_work->height/2);
	right = left + p_work->width;
	bottom = top + p_work->height;

	ENC_BMP_Fill( p_work->p_bmp, top, bottom, left, right, p_work->col );

	return result;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�r�b�g�}�b�v�E�B���h�E�h��Ԃ��@��`
 *
 *	@param	p_bmp		���[�N
 *	@param	top			��
 *	@param	bottom		��
 *	@param	left		��
 *	@param	right		�E
 *	@param	col			�J���[�ԍ�
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ENC_BMP_Fill( GF_BGL_BMPWIN* p_bmp, s32 top, s32 bottom, s32 left, s32 right, u8 col )
{
	// ��ʊO�`�F�b�N
	if( (right <= 0) || (bottom <= 0) ){
		return ;
	}

	// �ꏏ�Ȃ�`�悵�Ȃ�
	if( (left == right) || (top == bottom) ){
		return ;
	}
	
	if( left < 0 ){
		left = 0;
	}
	if( right > 256 ){
		right = 256;
	}
	if( top < 0 ){
		top = 0;
	}
	if( bottom > 256 ){
		bottom = 256;
	}

	// �r�b�g�}�b�v�h��Ԃ�
	GF_BGL_BmpWinFill( p_bmp, col,
			left,
			top,
			right - left,
			bottom - top );
}


//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�m��
 *
 *	@param	heapID	�q�[�v
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
ENC_BMP_FILL_BLOCK_MOVE* ENC_BMP_FillBlockMoveAlloc( u32 heapID )
{
	ENC_BMP_FILL_BLOCK_MOVE* p_work;
	int i;

	p_work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENC_BMP_FILL_BLOCK_MOVE) );
	memset( p_work, 0, sizeof(ENC_BMP_FILL_BLOCK_MOVE) );

	// �I�u�W�F�N�g�쐬
	for( i=0; i<ENCOUNT_BLOCK_MOVE_OBJNUM; i++ ){
		p_work->p_block[i] = ENC_BMP_FillBlockAlloc( heapID );
	}
	return p_work;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�j��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void ENC_BMP_FillBlockMoveDelete( ENC_BMP_FILL_BLOCK_MOVE* p_work )
{
	int i;
	
	// �u���b�N�I�u�W�F�j��
	for( i=0; i<ENCOUNT_BLOCK_MOVE_OBJNUM; i++ ){
		ENC_BMP_FillBlockDelete( p_work->p_block[i] );
	}
	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����J�n
 *	
 *	@param	p_work	���[�N
 *	@param	sync	�P�̃I�u�W�F�������V���N��
 *	@param	start	�P�̃I�u�W�F���˃^�C�~���O
 *	@param	p_bmp	�r�b�g�}�b�v
 *	@param	col		�J���[
 */
//-----------------------------------------------------------------------------
void ENC_BMP_FillBlockMoveStart( ENC_BMP_FILL_BLOCK_MOVE* p_work, u8 sync, u8 start, GF_BGL_BMPWIN* p_bmp, u8 col )
{
	p_work->p_bmp		= p_bmp;
	p_work->col			= col;
	p_work->move_sync	= sync;
	p_work->start_sync	= start;
	p_work->block_count = 0;
	p_work->block_end_count = 0;
	p_work->wait		= 0;
	p_work->init_flg	= 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C���֐�
 *
 *	@param	p_work	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL ENC_BMP_FillBlockMoveMain( ENC_BMP_FILL_BLOCK_MOVE* p_work )
{
	int x, s_y, e_y;
	int i;
	BOOL result;
	
	if( p_work->init_flg == 0 ){
		return TRUE;
	}
	
	// ���˕�
	if( p_work->block_count < ENCOUNT_BLOCK_MOVE_OBJNUM ){
		p_work->wait --;
		if( p_work->wait <= 0 ){
			p_work->wait = p_work->start_sync;

			x = ENCOUNT_BLOCK_MOVE_MoveParam[ p_work->block_count % ENCOUNT_BLOCK_MOVE_X_NUM ];
			x = (ENCOUNT_BLOCK_MOVE_WIDTH/2) + (x * ENCOUNT_BLOCK_MOVE_WIDTH);
			s_y = ENCOUNT_BLOCK_MOVE_MAT_Y - ((p_work->block_count/ENCOUNT_BLOCK_MOVE_X_NUM) * ENCOUNT_BLOCK_MOVE_HEIGHT);
			e_y = ENCOUNT_BLOCK_MOVE_MOVE_Y - ((p_work->block_count/ENCOUNT_BLOCK_MOVE_X_NUM) * ENCOUNT_BLOCK_MOVE_HEIGHT);
			// ����
			ENC_BMP_FillBlockStart( 
					p_work->p_block[ p_work->block_count ],
					x, x,
					s_y, e_y,
					p_work->move_sync, p_work->p_bmp,
					ENCOUNT_BLOCK_MOVE_WIDTH, ENCOUNT_BLOCK_MOVE_HEIGHT,
					p_work->col );

			p_work->block_count ++;
		}
	}
	

	// ������
	for( i=p_work->block_end_count; i<p_work->block_count; i++ ){
		result = ENC_BMP_FillBlockMain( p_work->p_block[i] );
		if( result == TRUE ){
			p_work->block_end_count++;
		}
	}

	// �S�����I���`�F�b�N
	if( (p_work->block_end_count >= ENCOUNT_BLOCK_MOVE_OBJNUM) &&
		(result == TRUE) ){
		p_work->init_flg = FALSE;
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *		�y�~�`�@BMP�@�h��Ԃ��I�u�W�F�z
 *	@brief	���[�N�m��
 *
 *	@param	heapID	�q�[�vID
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
ENC_BMP_CIRCLE_FILL* ENC_BMP_CircleFillAlloc( u32 heapID )
{
	ENC_BMP_CIRCLE_FILL* p_work;

	p_work = sys_AllocMemory( heapID, sizeof(ENC_BMP_CIRCLE_FILL) );
	memset( p_work, 0, sizeof(ENC_BMP_CIRCLE_FILL) );
	return p_work;
}

//----------------------------------------------------------------------------
/**
 *		�y�~�`�@BMP�@�h��Ԃ��I�u�W�F�z
 *	@brief	���[�N�j��
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void ENC_BMP_CircleFillDelete( ENC_BMP_CIRCLE_FILL* p_work )
{
	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *		�y�~�`�@BMP�@�h��Ԃ��I�u�W�F�z
 *	@brief	�G�t�F�N�g�J�n
 *
 *	@param	p_work	���[�N
 *	@param	sync	�V���N��
 *	@param	s_rota	�J�n��]�p		(���]���Ĕ��Α����쐬���邽�� 0�`179�̊p�x)
 *	@param	e_rota	�I����]�p		(���]���Ĕ��Α����쐬���邽�� 0�`179�̊p�x)
 *	@param	p_bmp	�r�b�g�}�b�v
 *	@param	col		�h��Ԃ��J���[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_BMP_CircleFillStart( ENC_BMP_CIRCLE_FILL* p_work, u8 sync, u16 s_rota, u16 e_rota, GF_BGL_BMPWIN* p_bmp, u8 col )
{
	p_work->p_bmp		= p_bmp;
	p_work->col			= col;
	p_work->move_flg	= 1;
	ENC_MoveReq( &p_work->rota, s_rota, e_rota, sync );
}

//----------------------------------------------------------------------------
/**
 *		�y�~�`�@BMP�@�h��Ԃ��I�u�W�F�z
 *	@brief	���C���֐�
 *
 *	@param	p_work	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL ENC_BMP_CircleFillMain( ENC_BMP_CIRCLE_FILL* p_work )
{
	BOOL result;
	u16 last_rota;
	
	if( p_work->move_flg == 0 ){
		return TRUE;
	}

	// �O�̊p�x
	last_rota = p_work->rota.x;

	// ���s
	result = ENC_MoveMain( &p_work->rota );

	// �`�揈��
	EncBmpCircleFill_Fill( p_work->p_bmp, last_rota, p_work->rota.x, p_work->col );	

	if( result == TRUE ){
		p_work->move_flg = 0;
		return TRUE;
	}
	return FALSE;
}

// �^���W�F���g�v�Z
static inline fx32 getTanX( u16 rota )
{
	return FX_Div(FX_SinIdx(rota), FX_CosIdx(rota));
}

//----------------------------------------------------------------------------
/**
 *		�y�~�`�@BMP�@�h��Ԃ��I�u�W�F�z
 *	@brief	�~�`�@�r�b�g�}�b�v�h��Ԃ��@������
 *
 *	@param	p_bmp		�r�b�g�}�b�v�E�B���h�E
 *	@param	last_rota	�O�̊p�x
 *	@param	now_rota	���̊p�x
 *	@param	col			�J���[
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EncBmpCircleFill_Fill( GF_BGL_BMPWIN* p_bmp, u16 last_rota, u16 now_rota, u8 col )
{
	int now_x, last_x, tmp;
	int re_now_x, re_last_x;	// �t���b�v
	int i;
	int y;
	fx32 now_tan_x, last_tan_x;

	// �^���W�F���g�l�����߂�
	now_tan_x = getTanX( now_rota );
	last_tan_x = getTanX( last_rota );

	// �e�����ł�X���W�����߂��̒l�œh��Ԃ�
	for( i=0; i<96; i++ ){

		y = 95 - i;

		now_x = FX_Mul( now_tan_x, y*FX32_ONE ) >> FX32_SHIFT;
		last_x = FX_Mul( last_tan_x, y*FX32_ONE ) >> FX32_SHIFT;

		// ���S���W����̒l�ɂ���
		re_now_x = 128 + now_x;
		re_last_x = 128 + last_x;
		now_x = 128 - now_x;
		last_x = 128 - last_x;

		//�@�������傤�𐮂���
		if( last_x > now_x ){
			tmp = last_x;
			last_x = now_x;
			now_x = tmp;
		}
		if( re_last_x > re_now_x ){
			tmp = re_last_x;
			re_last_x = re_now_x;
			re_now_x = tmp;
		}

//		OS_Printf( "left %d right %d now_rota %d last_rota %d\n", last_x, now_x, now_rota / 182, last_rota / 182 );

		
		
		ENC_BMP_Fill( p_bmp, i, i+1, last_x, now_x+1, col );
		ENC_BMP_Fill( p_bmp, 191 - i, 192 - i, re_last_x, re_now_x+1, col );
	}
}


//----------------------------------------------------------------------------
/**
 *		�y�t���b�V���A�E�g�z
 *	@brief	���[�N�m��
 *	
 *	@param	heapID	�q�[�vID
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
ENC_BMP_FLASH_OUT* ENC_BMP_FlashOutAlloc( u32 heapID )
{
	ENC_BMP_FLASH_OUT* p_work;
	int i;

	p_work = sys_AllocMemory( heapID, sizeof(ENC_BMP_FLASH_OUT) );
	memset( p_work, 0, sizeof(ENC_BMP_FLASH_OUT) );
	
	for( i=0; i<ENC_BMP_FLASH_CIRCLE_NUM; i++ ){
		p_work->p_circle[i] =  ENC_BMP_CircleFillAlloc( heapID );
	}
	
	return p_work;
}

//----------------------------------------------------------------------------
/**
 *		�y�t���b�V���A�E�g�z
 *	@brief	���[�N�j��
 *
 *	@param	p_work ���[�N
 */
//-----------------------------------------------------------------------------
void ENC_BMP_FlashOutDelete( ENC_BMP_FLASH_OUT* p_work )
{
	int i;

	for( i=0; i<ENC_BMP_FLASH_CIRCLE_NUM; i++ ){
		ENC_BMP_CircleFillDelete( p_work->p_circle[i] );
	}
	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *		�y�t���b�V���A�E�g�z
 *	@brief	�G�t�F�N�g�J�n
 *
 *	@param	p_work	���[�N
 *	@param	sync	�V���N��
 *	@param	p_bmp	�r�b�g�}�b�v
 *	@param	col		�h��Ԃ��J���[�ԍ�
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_BMP_FlashOutStart( ENC_BMP_FLASH_OUT* p_work, u8 sync, GF_BGL_BMPWIN* p_bmp, u8 col )
{
	int i;

	// �h��Ԃ��I�u�W�F�N�g������
	for( i=0; i<ENC_BMP_FLASH_CIRCLE_NUM; i++ ){
		ENC_BMP_CircleFillStart( p_work->p_circle[i],
				sync, 
				FX_GET_ROTA_NUM( FlashOutParam[i][0] ), 
				FX_GET_ROTA_NUM( FlashOutParam[i][1] ), 
				p_bmp,
				col );
	}
	p_work->move_flg = 1;

	// �ŏ���93  99�h�b�g��h��Ԃ�
	ENC_BMP_Fill( p_bmp, 93, 99, 0, 256, col );
}

//----------------------------------------------------------------------------
/**
 *		�y�t���b�V���A�E�g�z
 *	@brief	�t���b�V���A�E�g���C��
 *
 *	@param	p_work	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL ENC_BMP_FlashOutMain( ENC_BMP_FLASH_OUT* p_work )
{
	int i;
	BOOL result;
	
	if( p_work->move_flg == 0 ){
		return TRUE;
	}

	for( i=0; i<ENC_BMP_FLASH_CIRCLE_NUM; i++ ){
		result = ENC_BMP_CircleFillMain( p_work->p_circle[i] );
	}

	if( result == TRUE ){
		p_work->move_flg = 0;
		return TRUE;
	}
	return FALSE;
}



//----------------------------------------------------------------------------
/**
 *	�y�W�O�U�O�E�B���h�E�z
 *	@brief	���������E�B���h�E����
 */
//-----------------------------------------------------------------------------
ENC_HB_BG_WND_ZIGUZAGU* ENC_BG_WndZiguzagu_Alloc( void )
{
	ENC_HB_BG_WND_ZIGUZAGU* p_work;

	p_work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENC_HB_BG_WND_ZIGUZAGU) );
	memset( p_work, 0, sizeof(ENC_HB_BG_WND_ZIGUZAGU) );

	return p_work;
}

//----------------------------------------------------------------------------
/**
 *	�y�W�O�U�O�E�B���h�E�z
 *	@brief	���[�N�̔j��
 *
 *	@param	p_work 
 */
//-----------------------------------------------------------------------------
void ENC_BG_WndZiguzagu_Delete( ENC_HB_BG_WND_ZIGUZAGU* p_work )
{
	if( p_work->tcb != NULL ){
		ENC_BG_WndZiguzagu_End( p_work );	
	}
	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *	�y�W�O�U�O�E�B���h�E�z
 *	@brief	�֐��J�n
 *
 *	@param	p_ew		�G���J�E���g�G�t�F�N�g���[�N
 *	@param	p_eff		�G�t�F�N�g���[�N
 *	@param	sync		�V���N��
 *	@param	dot			���E�؂�ւ��h�b�g��
 *	@param	width		���E��
 *	@param	wnd_msgk_in		�E�B���h�E�}�X�N	��
 *	@param	wnd_msgk_out	�E�B���h�E�}�X�N	�O
 */
//-----------------------------------------------------------------------------
void ENC_BG_WndZiguzagu_Start( ENCOUNT_EFFECT_WORK* p_ew, ENC_HB_BG_WND_ZIGUZAGU* p_eff, u32 sync, u32 dot, u32 width, u32 wnd_msk_in, u32 wnd_msk_out )
{
	int i;
	int count;
	int set_w;
	
	// �J�n�ς�
	GF_ASSERT( p_eff->tcb == NULL );

	p_ew->hblank_flg	= FALSE;
	p_eff->p_hsys		= p_ew->fsw->fldmap->hblanksys;
	p_eff->seq			= 0;
	p_eff->end_check	= &p_ew->hblank_flg;
	ENC_MoveReq( &p_eff->move_x, ENC_BG_WND_ZIGUZAGU_MOVE_S, ENC_BG_WND_ZIGUZAGU_MOVE_E, sync );
	
	// �W�O�U�O�쐬
	for( i=0; i<192; i++ ){
		// �ݒ蕝�����߂�
		count = i % dot;
		set_w = count * width;
		set_w = set_w / dot;

		// �W�O�U�O�ɐݒ�
		if( ((i/dot) % 2) == 0 ){
			p_eff->ziguzagu_buf[ i ] = set_w;
		}else{
			p_eff->ziguzagu_buf[ i ] = width - set_w;
		}
	}

	// �E�B���h�E�}�X�N�ݒ�
	G2_SetWnd0InsidePlane( wnd_msk_in, TRUE );
	G2_SetWndOutsidePlane( wnd_msk_out, FALSE );	
	G2_SetWnd0Position( 0, 0, 0, 192 );
	GX_SetVisibleWnd( GX_WNDMASK_W0 );

	// �������^�X�N����
	VWaitTCB_Add( ENC_BG_WndZiguzagu_SetUp_Tcb, p_eff, END_HB_BG_WND_ZIGUZAGU_INIT_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *	�y�W�O�U�O�E�B���h�E�z
 *	@brief	�W�O�U�O�����^�X�N����
 */
//-----------------------------------------------------------------------------
static void ENC_BG_WndZiguzagu_SetUp_Tcb( TCB_PTR tcb, void* p_work )
{
	ENC_HB_BG_WND_ZIGUZAGU* p_eff = p_work;

	
	// H�u�����N�֐��o�^
	p_eff->p_hobj = FLDHBLANK_OBJ_Add( p_eff->p_hsys, ENC_BG_WndZiguzagu_HBlank, p_eff );

	
	p_eff->tcb = VWaitTCB_Add( ENC_BG_WndZiguzagu_Tcb, p_eff, END_HB_BG_WND_ZIGUZAGU_TCB_PRI );

	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *	�y�W�O�U�O�E�B���h�E�z
 *	@brief	���C�������^�X�N
 */
//-----------------------------------------------------------------------------
static void ENC_BG_WndZiguzagu_Tcb( TCB_PTR tcb, void* p_work )
{
	ENC_HB_BG_WND_ZIGUZAGU* p_eff = p_work;
	BOOL result;

	switch( p_eff->seq ){
	case 0:
		result = ENC_MoveMain( &p_eff->move_x );
		if( result == TRUE ){
			p_eff->seq++;
		}
		break;

	case 1:
		ENC_BG_WndZiguzagu_End( p_eff );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	�y�W�O�U�O�E�B���h�E�z
 *	@brief	H�u�����N�֐�
 */	
//-----------------------------------------------------------------------------
static void ENC_BG_WndZiguzagu_HBlank(FIELD_HBLANK_OBJ* p_hobj, void* p_work)
{
	ENC_HB_BG_WND_ZIGUZAGU* p_eff = p_work;
	int set_x;
	int v_count;		// V�J�E���g

	// V�J�E���^���擾���A�O�̎��͈ړ��l���v�Z����
	v_count = GX_GetVCount();
	
	if( v_count < 192 ){
		set_x = p_eff->ziguzagu_buf[v_count] + p_eff->move_x.x;
		if( set_x > 255 ){
			set_x = 255;
		}
		G2_SetWnd0Position( 0, 0, set_x, 192 );
	}
}

//----------------------------------------------------------------------------
/**
 *	�y�W�O�U�O�E�B���h�E�z
 *	@brief	�I������
 */
//-----------------------------------------------------------------------------
static void ENC_BG_WndZiguzagu_End( ENC_HB_BG_WND_ZIGUZAGU* p_work )
{
	// �E�B���h�E�}�X�N�j��
	GX_SetVisibleWnd( GX_WNDMASK_NONE );
	
	*(p_work->end_check) = TRUE;
	FLDHBLANK_OBJ_Delete( p_work->p_hobj );
	p_work->p_hobj = NULL;
	TCB_Delete( p_work->tcb );
	p_work->tcb = NULL;
}




//----------------------------------------------------------------------------
/**
 *	@brief	�G���J�E���g�G�t�F�N�g�i���o�[�擾�֐�
 *
 *	@param	data	�f�[�^
 *
 *	@return	�G���J�E���g�G�t�F�N�g�i���o�[
 *
 *
 *	�Ή�
 *		�ʐM�@�o�g���^���[
 *		�_�u���o�g��
 *		�쐶��
 *		�g���[�i�[��
 *
 *	���Ή�
 *		����g���[�i�[
 *		����|�P����
 */
//-----------------------------------------------------------------------------
#define ENCEFF_FIELD	(0)	// �쐶��
#define ENCEFF_TRAINER	(1)	// TRAINER��
#define ENCEFF_GRASS	(0)	// ��
#define ENCEFF_WATER	(1)	// ��
#define ENCEFF_DAN		(2)	// �_���W����
u32 ENCEFF_GetEffectNo( const BATTLE_PARAM * p_battleparam )
{
	int lv;
	int area;
	int type;
	POKEMON_PARAM* p_my_poke;
	POKEMON_PARAM* p_enemy_poke;
	int mypoke_lev, enemypoke_lev;

	// �o�g�����߂����̂𕪊򂳂���
	if( p_battleparam->fight_type & FIGHT_TYPE_TRAINER ){
		
		type = ENCEFF_TRAINER;
		
	}else if( (p_battleparam->fight_type & (FIGHT_TYPE_MOVE|FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK|FIGHT_TYPE_GET_DEMO)) ||
		(p_battleparam->fight_type == FIGHT_TYPE_YASEI) ){		// �쐶��0�Ȃ̂�&�Ŏ��Ȃ����߂�������
		
		type = ENCEFF_FIELD;
	}else{

		GF_ASSERT( 0 );	// �Ή����Ă��܂���B
		type = 0;
	}

	// �t�B�[���h�i�쐶�j�@�g���[�i�[�̂Ƃ��́A���x���ƒn�`����
	// �G�t�F�N�g���ς��
	// ���x���`�F�b�N
	p_my_poke = EvPoke_GetLivingPokemonTop( p_battleparam->poke_party[CLIENT_NO_MINE] );
	p_enemy_poke = EvPoke_GetLivingPokemonTop( p_battleparam->poke_party[CLIENT_NO_ENEMY] );
	mypoke_lev = PokeParaGet( p_my_poke, ID_PARA_level, NULL );
	enemypoke_lev = PokeParaGet( p_enemy_poke, ID_PARA_level, NULL );
	lv = enemypoke_lev - mypoke_lev;
	
	// �G���A�`�F�b�N
	switch( p_battleparam->ground_id ){
	case GROUND_ID_GRAVEL:
	case GROUND_ID_SANDS:
	case GROUND_ID_LAWN:
	case GROUND_ID_POOL:
	case GROUND_ID_ROCK:
	case GROUND_ID_SNOW:
	case GROUND_ID_ICE:
	case GROUND_ID_BOG:
	case GROUND_ID_BRIDGE:
	case GROUND_ID_FLOOR:
	case GROUND_ID_ALL:
		area = ENCEFF_GRASS * 2;	// low��hi�����邩��
		break;
	case GROUND_ID_WATER:
		area = ENCEFF_WATER * 2;	// low��hi�����邩��
		break;
	case GROUND_ID_CAVE:
		area = ENCEFF_DAN * 2;	// low��hi�����邩��
		break;
	}
	if( lv > 0 ){
		area ++;	// hi�Ȃ̂�
	}

	return (type*6) + area;
} 


//----------------------------------------------------------------------------
/**
 *	@brief	OAM�ʂ��E�B���h�E����`�Őݒ�@�g��k���\
 *
 *	@param	y		���S��
 *	@param	scale	�g�k�l
 *	@param	height�@����
 *	@param	bottom_y��ӂ܂ł̒���	��ӂ������̔�����菬�����Ƃ������邽��
 *	@param	wndno	�g�p�E�B���h�E
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_WND_SetScaleWnd( fx32 y, int bottom_y, fx32 scale, int height, int wndno, ENC_WND_SETPOSITION* p_work )
{
	int c_y;
	int set_height;

	c_y = (y>>FX32_SHIFT);

	set_height = FX_Mul( height*FX32_ONE, scale ) >> FX32_SHIFT;
	set_height /= 2;

	p_work->x1 = 0;
	p_work->x2 = 255;
	p_work->y1 = c_y - set_height;
	p_work->y2 = bottom_y;

	VWaitTCB_Add( ENC_WND_SetWndPositionVWait, p_work, ENC_SET_WND_SCALE_TCB_PRI );
}
//----------------------------------------------------------------------------
/**
 *	@brief	�c�[���@�g�嗦���̒�ӂ̍��������߂�
 *
 *	@param	scale			�g�k�l
 *	@param	c_y				���SY���W
 *	@param	half_height		��ӂւ̃T�C�Y
 *
 *	@return		��Ӎ��W
 */
//-----------------------------------------------------------------------------
int ENC_WND_SetScaleWndToolMakeBottomY( fx32 scale, int c_y, int half_height )
{
	half_height = FX_Mul( half_height * FX32_ONE, scale ) >> FX32_SHIFT;

	return c_y + half_height;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�E�B���h�E�|�W�V�����@V�u�����N�ݒ�
 */
//-----------------------------------------------------------------------------
static void ENC_WND_SetWndPositionVWait( TCB_PTR tcb, void* p_work )
{
	ENC_WND_SETPOSITION* p_data = p_work;

	if( p_data->wnd_no == 0 ){
		// V�u�����N���Ԃɐݒ�
		G2_SetWnd0Position( p_data->x1, p_data->y1, p_data->x2, p_data->y2  );
	}else{
		// V�u�����N���Ԃɐݒ�
		G2_SetWnd1Position( p_data->x1, p_data->y1, p_data->x2, p_data->y2  );
	}

	TCB_Delete( tcb );
}


//----------------------------------------------------------------------------
/**
 *	@brief	V�u�����NMaster�P�x�ݒ�֐�
 */
//-----------------------------------------------------------------------------
static void EncSetMstBrightnessSetVTcb( TCB_PTR tcb, void* p_work )
{
	int * p_data = p_work;
	GX_SetMasterBrightness( *p_data );
	TCB_Delete(tcb);
}

//----------------------------------------------------------------------------
/**
 *	@brief	V�u�����NMaster�P�x�ݒ�֐�
 *	@param	p_setnum	�ݒ萔�Q�ƃ|�C���^
 */
//-----------------------------------------------------------------------------
void ENC_SetMasterBrightnessVblank( int* p_setnum )
{
	VWaitTCB_Add( EncSetMstBrightnessSetVTcb, p_setnum, ENC_SET_MSTBRI_TCB_PRI );	
}
