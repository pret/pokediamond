//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		amaikaori_eff.c
 *	@brief		�Â�����G�t�F�N�g
 *	@author		tomoya takahashi
 *	@data		2006.05.01
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "fieldmap_work.h"
#include "weather_sys.h"
#include "fieldmap.h"
#include "src/fielddata/script/common_scr_def.h"
#include "script.h"
#include "include/system/snd_tool.h"
#include "zonedata.h"

#define	__AMAIKAORI_EFF_H_GLOBAL
#include "amaikaori_eff.h"
#include "encount_set.h"

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
#define AMAIKAORI_USE_BG_MSK	( GX_PLANEMASK_BG2 )
#define AMAIKAORI_USE_BG_FRM	( FLD_MBGFRM_EFFECT2 )
#define AMAIKAORI_USE_PLTT		( 6 )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	���샏�[�N
//=====================================
typedef struct {
	int x;
	int s_x;
	int dis_x;
	int count;
	int count_max;
} AMAIKAORI_MOVE_WORK;

//-------------------------------------
//	�Â����胏�[�N
//=====================================
typedef struct {
	AMAIKAORI_MOVE_WORK alpha;
	BOOL end;
} AMAIKAORI_WORK;

#ifdef FIELD_AMAIKAORI_DEBUG
static int AMAIKAORI_ALPHA_S =		(0);
static int AMAIKAORI_ALPHA_E =		(10);
static int AMAIKAORI_ALPHA_COUNT =	( 19 );
static int AMAIKAORI_ALPHA_COUNT_END =	( 15 );
static int AMAIKAORI_EVENT_WEATHER_COMM_WAIT =	( 20 );
static int AMAIKAORI_EVENT_ALPHA_MAX_WAIT =	( 22 );
static int AMAIKAORI_DEBUG_SEQ = (0);
#else
#define AMAIKAORI_ALPHA_S			(0)
#define AMAIKAORI_ALPHA_E			(10)
#define AMAIKAORI_ALPHA_COUNT		( 19 )
#define AMAIKAORI_ALPHA_COUNT_END	( 15 )
#define AMAIKAORI_EVENT_WEATHER_COMM_WAIT	( 20 )
#define AMAIKAORI_EVENT_ALPHA_MAX_WAIT	( 22 )
#endif
#define AMAIKAORI_TSK_PRI			( 1024 )

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void Amaikaori_SetUpBG( GF_BGL_INI* bg_ini );
static void AmaikaoriMoveReq( AMAIKAORI_MOVE_WORK* p_work, int s_x, int e_x, int count_max );
static BOOL	AmaikaoriMoveMain( AMAIKAORI_MOVE_WORK* p_work );

#ifdef FIELD_AMAIKAORI_DEBUG
void AmaikaoriDebugMain( TCB_PTR tcb, void* p_work )
{
	if( sys.trg & PAD_BUTTON_SELECT ){
		AMAIKAORI_DEBUG_SEQ = (AMAIKAORI_DEBUG_SEQ + 1) % 6;
		switch( AMAIKAORI_DEBUG_SEQ ){
		case 0:
			OS_Printf( "�J�n���l\n" );
			break;

		case 1:
			OS_Printf( "�I�����l\n" );
			break;

		case 2:
			OS_Printf( "�����Z����\n" );
			break;

		case 3:
			OS_Printf( "�����Z����\n" );
			break;

		case 4:
			OS_Printf( "�V�C�ł��߂ȂƂ��̃R�����g�҂�\n" );
			break;
			
		case 5:
			OS_Printf( "���ő厞�̃E�G�C�g\n" );
			break;
		}
	}

	if( sys.trg & PAD_BUTTON_L ){
		OS_Printf( "�S�f�[�^�\��\n" );
		OS_Printf( "�J�n���l %d\n", AMAIKAORI_ALPHA_S );
		OS_Printf( "�I�����l %d\n", AMAIKAORI_ALPHA_E );
		OS_Printf( "�����Z���� %d\n", AMAIKAORI_ALPHA_COUNT );
		OS_Printf( "�����Z���� %d\n", AMAIKAORI_ALPHA_COUNT_END );
		OS_Printf( "�V�C�ł��߂ȂƂ��̃R�����g�҂� %d\n", AMAIKAORI_EVENT_WEATHER_COMM_WAIT );
	}
	
	switch( AMAIKAORI_DEBUG_SEQ ){
	case 0:
		if( sys.repeat & PAD_BUTTON_A ){
			AMAIKAORI_ALPHA_S ++;
			OS_Printf( "�J�n���l %d\n", AMAIKAORI_ALPHA_S );
		}else if( sys.repeat & PAD_BUTTON_Y ){
			AMAIKAORI_ALPHA_S --;
			OS_Printf( "�J�n���l %d\n", AMAIKAORI_ALPHA_S );
		}
		break;

	case 1:
		if( sys.repeat & PAD_BUTTON_A ){
			AMAIKAORI_ALPHA_E ++;
			OS_Printf( "�I�����l %d\n", AMAIKAORI_ALPHA_E );
		}else if( sys.repeat & PAD_BUTTON_Y ){
			AMAIKAORI_ALPHA_E --;
			OS_Printf( "�I�����l %d\n", AMAIKAORI_ALPHA_E );
		}
		break;

	case 2:
		if( sys.repeat & PAD_BUTTON_A ){
			AMAIKAORI_ALPHA_COUNT ++;
			OS_Printf( "�����Z���� %d\n", AMAIKAORI_ALPHA_COUNT );
		}else if( sys.repeat & PAD_BUTTON_Y ){
			AMAIKAORI_ALPHA_COUNT --;
			OS_Printf( "�����Z���� %d\n", AMAIKAORI_ALPHA_COUNT );
		}
		break;

	case 3:
		if( sys.repeat & PAD_BUTTON_A ){
			AMAIKAORI_ALPHA_COUNT_END ++;
			OS_Printf( "�����Z���� %d\n", AMAIKAORI_ALPHA_COUNT_END );
		}else if( sys.repeat & PAD_BUTTON_Y ){
			AMAIKAORI_ALPHA_COUNT_END --;
			OS_Printf( "�����Z���� %d\n", AMAIKAORI_ALPHA_COUNT_END );
		}
		break;

	case 4:
		if( sys.repeat & PAD_BUTTON_A ){
			AMAIKAORI_EVENT_WEATHER_COMM_WAIT ++;
			OS_Printf( "�V�C�ł��߂ȂƂ��̃R�����g�҂� %d\n", AMAIKAORI_EVENT_WEATHER_COMM_WAIT );
		}else if( sys.repeat & PAD_BUTTON_Y ){
			AMAIKAORI_EVENT_WEATHER_COMM_WAIT --;
			OS_Printf( "�V�C�ł��߂ȂƂ��̃R�����g�҂� %d\n", AMAIKAORI_EVENT_WEATHER_COMM_WAIT );
		}
		break;
	case 5:
		if( sys.repeat & PAD_BUTTON_A ){
			AMAIKAORI_EVENT_ALPHA_MAX_WAIT ++;
			OS_Printf( "���ő�l���̃E�G�C�g %d\n", AMAIKAORI_EVENT_ALPHA_MAX_WAIT );
		}else if( sys.repeat & PAD_BUTTON_Y ){
			AMAIKAORI_EVENT_ALPHA_MAX_WAIT --;
			OS_Printf( "���ő�l���̃E�G�C�g %d\n", AMAIKAORI_EVENT_ALPHA_MAX_WAIT );
		}
		break;
	}
}
#endif



//----------------------------------------------------------------------------
/**
 *	@brief	����������
 */
//-----------------------------------------------------------------------------
static void FLDMAP_Amaikaori_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	AMAIKAORI_WORK* p_data = p_work;
	
	Amaikaori_SetUpBG( p_fsys->bgl );
	AmaikaoriMoveReq( &p_data->alpha, AMAIKAORI_ALPHA_S, AMAIKAORI_ALPHA_E, AMAIKAORI_ALPHA_COUNT );
	p_data->end = FALSE;
	// Alpha�ݒ�
	G2_SetBlendAlpha( AMAIKAORI_USE_BG_MSK, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BD, AMAIKAORI_ALPHA_S, 16 - AMAIKAORI_ALPHA_S );

	
	GF_BGL_PrioritySet( AMAIKAORI_USE_BG_FRM, 0 );

	// BGON
	GF_Disp_GX_VisibleControl( AMAIKAORI_USE_BG_MSK, VISIBLE_ON );

	// ���Ȃ炷  
	Snd_SePlay( SE_AMAIKAORI );
}
static void FLDMAP_AmaikaoriEndEff_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	AMAIKAORI_WORK* p_data = p_work;
	
	Amaikaori_SetUpBG( p_fsys->bgl );
	AmaikaoriMoveReq( &p_data->alpha, AMAIKAORI_ALPHA_E, AMAIKAORI_ALPHA_S, AMAIKAORI_ALPHA_COUNT_END );
	p_data->end = FALSE;
	// Alpha�ݒ�
	G2_SetBlendAlpha( AMAIKAORI_USE_BG_MSK, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BD, AMAIKAORI_ALPHA_E, 16 - AMAIKAORI_ALPHA_E );

	
}

//----------------------------------------------------------------------------
/**
 *	@brief	�j������
 */
//-----------------------------------------------------------------------------
static void FLDMAP_Amaikaori_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{

}

//----------------------------------------------------------------------------
/**
 *	@brief	���C������
 */
//-----------------------------------------------------------------------------
static void FLDMAP_Amaikaori_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	BOOL result;
	AMAIKAORI_WORK* p_data = p_work;

	if( p_data->end == TRUE ){
		return ;
	}

	result = AmaikaoriMoveMain( &p_data->alpha );
	if( result ){
		p_data->end = TRUE;
	}
	G2_ChangeBlendAlpha( p_data->alpha.x, 16 - p_data->alpha.x );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�揈��
 */
//-----------------------------------------------------------------------------
static void FLDMAP_Amaikaori_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
}




//----------------------------------------------------------------------------
/**
 *	@brief	�Â�����G�t�F�N�g�J�n
 *
 *	@param	fsys	�t�B�[���h�V�X�e�����[�N
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLDMAP_Amaikaori_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FLDMAP_AmaikaoriData = {
		AMAIKAORI_TSK_PRI,
		sizeof(AMAIKAORI_WORK),
		FLDMAP_Amaikaori_Init,
		FLDMAP_Amaikaori_Delete,
		FLDMAP_Amaikaori_Main,
		FLDMAP_Amaikaori_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FLDMAP_AmaikaoriData );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Â����胏�[�N�j��
 *
 *	@param	p_eff	�G�t�F�N�g���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLDMAP_Amaikaori_End( FLDMAPFUNC_WORK* p_eff )
{
	FLDMAPFUNC_Delete( p_eff );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Â�����I���`�F�b�N
 *	
 *	@param	p_eff	�G�t�F�N�g���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL FLDMAP_Amaikaori_EndCheck( FLDMAPFUNC_WORK* p_eff )
{
	AMAIKAORI_WORK* p_data = FLDMAPFUNC_GetFreeWork( p_eff );
	return p_data->end;
}



//----------------------------------------------------------------------------
/**
 *	@brief	�Â�����I���G�t�F�N�g
 *
 *	@param	fsys �t�B�[���h�V�X�e�����[�N
 *
 *	@return
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLDMAP_AmaikaoriEndEff_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FLDMAP_AmaikaoriData = {
		AMAIKAORI_TSK_PRI,
		sizeof(AMAIKAORI_WORK),
		FLDMAP_AmaikaoriEndEff_Init,
		FLDMAP_Amaikaori_Delete,
		FLDMAP_Amaikaori_Main,
		FLDMAP_Amaikaori_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FLDMAP_AmaikaoriData );
	return p_fwk;
}


//----------------------------------------------------------------------------
/**
 *	@brief	BG�ݒ�
 */
//-----------------------------------------------------------------------------
static void Amaikaori_SetUpBG( GF_BGL_INI* bg_ini )
{
	GXRgb color = GX_RGB( 31, 10, 23 );
	u8* p_char_buff;
	
	// �J���[�p���b�g�]��
	GF_BGL_PaletteSet( AMAIKAORI_USE_BG_FRM, &color, sizeof(short), (AMAIKAORI_USE_PLTT * 32) + 2 );


	// �L�����N�^�f�[�^
	p_char_buff = sys_AllocMemory( HEAPID_FIELD, sizeof(u8)*32 );
	memset( p_char_buff, 0x11, sizeof(u8)*32 );
	GF_BGL_LoadCharacter( bg_ini, AMAIKAORI_USE_BG_FRM, p_char_buff, sizeof(u8)*32, 1 );
	sys_FreeMemoryEz( p_char_buff );

	// �X�N���[���f�[�^
	GF_BGL_ScrClearCode( bg_ini, AMAIKAORI_USE_BG_FRM, (AMAIKAORI_USE_PLTT << 12) | 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ėp���샊�N�G�X�g
 *	
 *	@param	p_work	���[�N
 *	@param	s_x		�J�n�l
 *	@param	e_x		�I���l
 *	@param	count_max	�J�E���g�ő�l
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void AmaikaoriMoveReq( AMAIKAORI_MOVE_WORK* p_work, int s_x, int e_x, int count_max )
{
	p_work->x = s_x;

	p_work->s_x = s_x;
	p_work->dis_x = e_x - s_x;
	p_work->count_max = count_max;
	p_work->count = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ėp���상�C��
 *
 *	@param	p_work	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL	AmaikaoriMoveMain( AMAIKAORI_MOVE_WORK* p_work )
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











//-----------------------------------------------------------------------------
/**
 *		�C�x���g
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�V�[�P���X
//=====================================
enum{
	FLDMAP_AMAIKAORI_WEATHER_CHECK,		// �V�C�`�F�b�N
	FLDMAP_AMAIKAORI_START_0,	// �G�t�F�N�g�J�n
	FLDMAP_AMAIKAORI_END_0,		// �I���`�F�b�N
	FLDMAP_AMAIKAORI_MAX_WAIT,	// �ō��ɂ���������Ԃ�weight
	FLDMAP_AMAIKAORI_START_1,	// �G���J�E���g���Ȃ��Ƃ��́@�G�t�F�N�g�J�n
	FLDMAP_AMAIKAORI_END_1,		// �G���J�E���g���Ȃ��Ƃ��́@�I���`�F�b�N
	FLDMAP_AMAIKAORI_ENCOUNT,	// �G���J�E���g�X�^�[�g
	FLDMAP_AMAIKAORI_WEATHER_END,		// �V�C�̂����ł��܂���������o���Ȃ������Ƃ�
	FLDMAP_AMAIKAORI_NOENCOUNT,	// �G���J�E���g���Ȃ������Ƃ�
	FLDMAP_AMAIKAORI_SCRPT_END,	// �X�N���v�g�I��
};

//-------------------------------------
//	�Â�����C�x���g���[�N
//=====================================
typedef struct _EVENT_AMAIKAORI_EFF_WORK{
	FLDMAPFUNC_WORK* p_fwk;
	BOOL bd_bg_flip;	// ���̂Ƃ�BD��BG��؂�ւ���
	u16 seq;
	s16 wait;
} ;

// ���̂Ƃ�BG��BD��؂�ւ���
#define AMAIKAORI_FOG_BG_PL	(6)
#define AMAIKAORI_FOG_BG_PL_OFS	((AMAIKAORI_FOG_BG_PL*32)+4)
#define AMAIKAORI_FOG_BG_PL_DAT	( 0x7fff )
#define AMAIKAORI_FOG_BG_CHR_OFS	(2)
#define AMAIKAORI_FOG_BG_CHR_DAT	(2)
#define AMAIKAORI_FOG_BG_SCR_DAT	( (AMAIKAORI_FOG_BG_PL<<12) | (AMAIKAORI_FOG_BG_CHR_OFS) )

//----------------------------------------------------------------------------
/**
 *	@brief	BD�����Ƀ��Z�b�g
 *
 *	@param	fsys 
 */
//-----------------------------------------------------------------------------
static void FLDMAP_Amaikaori_BDReset( FIELDSYS_WORK* fsys )
{
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME2_M, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	��BG��BD�Ƀt���b�v
 *
 *	@param	fsys 
 */
//-----------------------------------------------------------------------------
static void FLDMAP_Amaikaori_BGFlipBD( FIELDSYS_WORK* fsys )
{
	// �o�b�N�h���b�v��^������
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME2_M, AMAIKAORI_FOG_BG_PL_DAT );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BD��BG�Ƀt���b�v
 *
 *	@param	fsys 
 */
//-----------------------------------------------------------------------------

static void FLDMAP_Amaikaori_BDFlipBG( FIELDSYS_WORK* fsys )
{
	u16	col = AMAIKAORI_FOG_BG_PL_DAT;

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
	
	// BG��^������
	G2_SetBG2Priority(3);
	GF_BGL_PaletteSet( FLD_MBGFRM_EFFECT2, &col, 2, AMAIKAORI_FOG_BG_PL_OFS );
	GF_BGL_CharFill( fsys->bgl, FLD_MBGFRM_EFFECT2, AMAIKAORI_FOG_BG_CHR_DAT, 1, AMAIKAORI_FOG_BG_CHR_OFS );	// 1�L�����ڂ�^�����ɂ���
	GF_BGL_ScrClearCode( fsys->bgl, FLD_MBGFRM_EFFECT2, AMAIKAORI_FOG_BG_SCR_DAT );

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );

	// �o�b�N�h���b�v��
	FLDMAP_Amaikaori_BDReset( fsys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BD�����b�Z�[�WBG�Ƀt���b�v
 *
 *	@param	fsys 
 */
//-----------------------------------------------------------------------------

static void FLDMAP_Amaikaori_BDFlipMessegeBG( FIELDSYS_WORK* fsys )
{
	u16	col = AMAIKAORI_FOG_BG_PL_DAT;

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
	
	// BG��^������
	G2_SetBG3Priority(3);
	GF_BGL_PaletteSet( FLD_MBGFRM_FONT, &col, 2, AMAIKAORI_FOG_BG_PL_OFS );
	GF_BGL_CharFill( fsys->bgl, FLD_MBGFRM_FONT, AMAIKAORI_FOG_BG_CHR_DAT, 1, AMAIKAORI_FOG_BG_CHR_OFS );	// 1�L�����ڂ�^�����ɂ���

	GF_BGL_ScrClearCode( fsys->bgl, FLD_MBGFRM_FONT, AMAIKAORI_FOG_BG_SCR_DAT );

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );

	// �o�b�N�h���b�v��
	FLDMAP_Amaikaori_BDReset( fsys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BD�@�Ɓ@BG�ʂ�؂�Ԃ�@�ĉ��z��BG���o���Ă�����݂̂̂ł���
 *
 *	@param	fsys	�t�B�[���h�V�X�e��
 *
 *	@retval	TRUE	�؂�ւ���
 *	@retval	FALSE	�؂�ւ��Ȃ�
 */
//-----------------------------------------------------------------------------
#define FLDMAP_AMAIKAORI_DBG_CHG_WEATHER	(1)
static BOOL FLDMAP_Amaikaori_BD_BG_ChangeCheck( FIELDSYS_WORK* fsys )
{
	static const u32 FldmapAmaikaoriDBGWeather[ FLDMAP_AMAIKAORI_DBG_CHG_WEATHER ] = {
		WEATHER_SYS_FOG,
	};
	u32 weather_no;
	int i;
	weather_no = WEATHER_GetNow( fsys->fldmap->weather_data );

	for( i=0; i<FLDMAP_AMAIKAORI_DBG_CHG_WEATHER; i++ ){
		if( weather_no == FldmapAmaikaoriDBGWeather[i] ){
			return TRUE;
		}
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Â����肪�o����V�C���`�F�b�N
 *	@retval	TRUE	�o����
 *	@retval	FALSE	�o���Ȃ�
 */
//-----------------------------------------------------------------------------
#define FLDMAP_AMAIKAORI_NONE_WEATHER	( 16 )
static BOOL FLDMAP_Amaikaori_WeatherCheck( FIELDSYS_WORK* fsys )
{
	static const u32 FldmapAmaikaoriNoWeather[ FLDMAP_AMAIKAORI_NONE_WEATHER ] = {
		WEATHER_SYS_RAIN,
		WEATHER_SYS_STRAIN,
		WEATHER_SYS_SPARK,
		WEATHER_SYS_SNOW,
		WEATHER_SYS_SNOWSTORM,
		WEATHER_SYS_SNOWSTORM_H,
		WEATHER_SYS_SANDSTORM,
		WEATHER_SYS_SNOW_STORM_BG,// BG�g�p����	OAM FOG BG
		WEATHER_SYS_STORM,		// ����		OAM FOG
		WEATHER_SYS_MIST1,			// �������̖�	FOG	BG
		WEATHER_SYS_MIST2,			// �������̖�	FOG	BG
		WEATHER_SYS_FLASH,			// �t���b�V��		BG
		WEATHER_SYS_CLOUDINESS,		// �܂�		BG	
		WEATHER_SYS_VOLCANO,		// �ΎR�D	OAM FOG BG
		WEATHER_SYS_MYSTIC,
		WEATHER_SYS_SPARK_EFF,
	};
	u32 weather_no;
	int i;
	weather_no = WEATHER_GetNow( fsys->fldmap->weather_data );

	for( i=0; i<FLDMAP_AMAIKAORI_NONE_WEATHER; i++ ){
		
		if( weather_no == FldmapAmaikaoriNoWeather[i] ){
			return FALSE;
		}
	}
	return TRUE;
}

// �G�t�F�N�g�I���֐�
static void FLDMAP_Amaikaori_WorkDelete( EVENT_AMAIKAORI_EFF_WORK* p_work )
{
	if( p_work->p_fwk ){
		FLDMAP_Amaikaori_End( p_work->p_fwk );	
		p_work->p_fwk = NULL;
	}
	sys_FreeMemoryEz( p_work );
}


// ���[�N�T�C�Y
u32 FLDMAP_Amaikaori_WorkSize( void )
{
	return sizeof( EVENT_AMAIKAORI_EFF_WORK );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�Â�����C�x���g�@���䕔��	���[�N�̂͂������܂��@�m�ۂ͊O
 *
 *	@param	event	�C�x���g���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL FLDMAP_AmaikaoriEvent( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_AMAIKAORI_EFF_WORK* p_work = FieldEvent_GetSpecialWork(event);
	
	switch( p_work->seq ){
	case FLDMAP_AMAIKAORI_WEATHER_CHECK:		// �V�C�`�F�b�N
		if( FLDMAP_Amaikaori_WeatherCheck( fsys ) == TRUE ){
			p_work->seq = FLDMAP_AMAIKAORI_START_0;

			// ���̂Ƃ�BD��BG�����ւ�
			p_work->bd_bg_flip = FLDMAP_Amaikaori_BD_BG_ChangeCheck( fsys );
			if( p_work->bd_bg_flip ){
				FLDMAP_Amaikaori_BGFlipBD( fsys );
			}
			
		}else{
			p_work->seq = FLDMAP_AMAIKAORI_WEATHER_END;
			p_work->wait = AMAIKAORI_EVENT_WEATHER_COMM_WAIT;	// 1�b��weight
		}
		break;
		
	case FLDMAP_AMAIKAORI_START_0:	// �G�t�F�N�g�J�n
		p_work->p_fwk = FLDMAP_Amaikaori_Start( fsys );		
		p_work->seq  = FLDMAP_AMAIKAORI_END_0;
		// BGON
		GF_BGL_PrioritySet( AMAIKAORI_USE_BG_FRM, 0 );
		GF_Disp_GX_VisibleControl( AMAIKAORI_USE_BG_MSK, VISIBLE_ON );
		break;
		
	case FLDMAP_AMAIKAORI_END_0:		// �I���`�F�b�N
		if( FLDMAP_Amaikaori_EndCheck( p_work->p_fwk ) ){
			p_work->wait = AMAIKAORI_EVENT_ALPHA_MAX_WAIT;
			p_work->seq  = FLDMAP_AMAIKAORI_MAX_WAIT;
		}
		break;


	case FLDMAP_AMAIKAORI_MAX_WAIT:	// �ō��ɂ���������Ԃ�weight
		p_work->wait --;
		// �]�[�����G���J�E���gOK���`�F�b�N
		if( ZoneData_GetEncountFlag(fsys->location->zone_id) ){
			if( p_work->wait < 0 ){
				{
					//�A�g���r���[�g�`�F�b�N
					u8 attr;
					int x,z;

					x = Player_NowGPosXGet( fsys->player );
					z = Player_NowGPosZGet( fsys->player );
					attr = (u8)GetAttributeLSB( fsys, x, z );
					if (EncSet_CheckEncount( fsys, attr)){
						// �G���J�E���g����
						p_work->seq = FLDMAP_AMAIKAORI_ENCOUNT;
					}else{
						// �G���J�E���g���Ȃ�
						p_work->seq = FLDMAP_AMAIKAORI_START_1;
					}
				}
			}
		}else{
			// �G���J�E���g���Ȃ�
			p_work->seq = FLDMAP_AMAIKAORI_START_1;
		}
		break;
		
	case FLDMAP_AMAIKAORI_START_1:	// �G���J�E���g���Ȃ��Ƃ��́@�G�t�F�N�g�J�n
		FLDMAP_Amaikaori_End( p_work->p_fwk );	// ���܂ł̃G�t�F�N�g���[�N�j��
		p_work->p_fwk = FLDMAP_AmaikaoriEndEff_Start( fsys );
		p_work->seq = FLDMAP_AMAIKAORI_END_1;
		break;
		
	case FLDMAP_AMAIKAORI_END_1:		// �G���J�E���g���Ȃ��Ƃ��́@�I���`�F�b�N
		if( FLDMAP_Amaikaori_EndCheck( p_work->p_fwk ) ){
			// BGOFF
			GF_Disp_GX_VisibleControl( AMAIKAORI_USE_BG_MSK, VISIBLE_OFF );
			G2_BlendNone();
			GF_BGL_PrioritySet( AMAIKAORI_USE_BG_FRM, 3 );

			p_work->seq = FLDMAP_AMAIKAORI_NOENCOUNT;
		}
		break;
		
	case FLDMAP_AMAIKAORI_ENCOUNT:	// �G���J�E���g�X�^�[�g
		{
			BOOL rc;

			// ���[�N�j��
			FLDMAP_Amaikaori_WorkDelete( p_work );

			// ���G���J�E���g����̂ŁA���b�Z�[�W�ʂ�
			// ����BG���t���b�v����
			if( p_work->bd_bg_flip ){
				FLDMAP_Amaikaori_BDFlipMessegeBG( fsys );
			}

			rc = SetSweetEncount(fsys, event);
			GF_ASSERT(rc);
		}
		break;	// ��������́A�G���J�E���g�G�t�F�N�g�Ɉڍs�����
		
	case FLDMAP_AMAIKAORI_WEATHER_END:		// �V�C�̂����ł��܂���������o���Ȃ������Ƃ�
		p_work->wait --;
		if( p_work->wait < 0 ){
			// ���b�Z�[�W�\��
			EventCall_Script( event, SCRID_SWEET_WEATHER, NULL, NULL );
			p_work->seq = FLDMAP_AMAIKAORI_SCRPT_END;
		}
		break;
		
	case FLDMAP_AMAIKAORI_NOENCOUNT:	// �G���J�E���g���Ȃ������Ƃ�
		// ���b�Z�[�W�\��
		EventCall_Script( event, SCRID_SWEET_NO_ENC, NULL, NULL );

		p_work->seq = FLDMAP_AMAIKAORI_SCRPT_END;
		break;

	case FLDMAP_AMAIKAORI_SCRPT_END:
		// ���[�N�j��
		FLDMAP_Amaikaori_WorkDelete( p_work );

		// ���̂Ƃ�BG��BD��؂�ւ���
		if( p_work->bd_bg_flip ){
			FLDMAP_Amaikaori_BDFlipBG( fsys );
		}

		return TRUE;

	default:
		// ��������
		GF_ASSERT( 0 );
		break;
	}

	return FALSE;
}
