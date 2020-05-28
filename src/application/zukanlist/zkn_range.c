//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_range.c
 *	@brief		���z�}�A�v���P�[�V����
 *	@author		tomoya takahashi
 *	@data		2006.01.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"

#include "src/application/zukanlist/zkn_data/zkn_hidemap.dat"

#include "include/gflib/display.h"
#include "include/system/brightness.h"
#include "include/system/arc_tool.dat"
#include "include/system/arc_util.h"
#include "include/system/clact_util.h"
#include "include/application/zukanlist/zukan.naix"
#include "include/gflib/button_man.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"

#include "include/application/zukanlist/zkn_encount_draw.h"
#include "include/application/zukanlist/zkn_range_data.h"

#include "include/system/timezone.h"

#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_zukan_common.h"

#define	__ZKN_RANGE_H_GLOBAL
#include "include/application/zukanlist/zkn_range.h"


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
#define ZKN_RANGE_EVENT_NUM ( 0 )			// �C�x���g��
//#define ZKN_RANGE_EVENT_CHANGE_SOUND ( 0x1 << 1 )	// ��������

#define ZKN_RANGE_OAM_BG_PRI	( 1 )
#define ZKN_RANGE_OAM_PRI	( 31 )

//-------------------------------------
//	�V�[�P���X
//=====================================
enum{
	ZKN_RANGE_SEQINIT_ALLOC,
	ZKN_RANGE_SEQINIT_LOAD,
	ZKN_RANGE_SEQINIT_FADEIN,
	ZKN_RANGE_SEQINIT_END,
};
enum{
	ZKN_RANGE_SEQDELETE_FADEOUT_INIT,
	ZKN_RANGE_SEQDELETE_FADEOUT,
	ZKN_RANGE_SEQDELETE_RELEASE,
	ZKN_RANGE_SEQDELETE_FREE,
	ZKN_RANGE_SEQDELETE_END,
};

// �����n�s��
#define ZKN_RANGE_NONE_OAM_X	( 160 )
#define ZKN_RANGE_NONE_OAM_Y	( 96 )
#define ZKN_RANGE_NONE_FONTOAM_OFS_X	( -53 )
#define ZKN_RANGE_NONE_FONTOAM_OFS_Y	( -8 )
#define ZKN_RANGE_NONE_FONTOAM_BMP_SIZX	( 16 )
#define ZKN_RANGE_NONE_FONTOAM_BMP_SIZY	( 2 )
#define ZKN_RANGE_NONE_OAM_SEQ	( 2 )

#define ZKN_RANGE_FONTOAM_PAL_OFS	(2)

// �B���}�b�v�z�u�ʒu
#define ZKN_RANGE_HIDEMAP_D15_X	( 13 )
#define ZKN_RANGE_HIDEMAP_D15_Y	( 8 )
#define ZKN_RANGE_HIDEMAP_D18_X	( 28 )
#define ZKN_RANGE_HIDEMAP_D18_Y	( 7 )
#define ZKN_RANGE_HIDEMAP_D30_X	( 11 )
#define ZKN_RANGE_HIDEMAP_D30_Y	( 8 )
#define ZKN_RANGE_HIDEMAP_L04_X	( 25 )
#define ZKN_RANGE_HIDEMAP_L04_Y	( 16 )



// ���z�}�O���b�h��
#define ZKN_RANGE_GRID_NUM_X	( 30 )
#define ZKN_RANGE_GRID_NUM_Y	( 30 )
#define ZKN_RANGE_GRID_ARRAY_SIZE	( ZKN_RANGE_GRID_NUM_X * ZKN_RANGE_GRID_NUM_Y )
#define ZKN_RANGE_GRAPHIC_GRID_SIZE	( 5 )
#define ZKN_RANGE_BMP_DRAW_X	( 89 )
#define ZKN_RANGE_BMP_DRAW_Y	( 30 )



// �_���W����OAM
#define ZKN_RANGE_DAN_OAMNORM_SP_SEQ	( 0 )
#define ZKN_RANGE_DAN_OAMSP_SP_SEQ		( 1 )
#define ZKN_RANGE_DAN_OAMNORM_NORM_SEQ	( 2 )
#define ZKN_RANGE_DAN_OAMSP_NORM_SEQ	( 3 )
#define ZKN_RANGE_DAN_OAM_BUFF_NUM		( ZKN_DAN_ID_MAX*2 )
#define ZKN_RANGE_DAN_DRAW_X	( 92 )
#define ZKN_RANGE_DAN_DRAW_Y	( 32 )
// �q���o�X�p
#define ZKN_RANGE_DAN_OAMNORM_HIN_SEQ	( 4 )	// �q���o�X�p
#define ZKN_RANGE_DAN_OAMSP_HIN_SEQ		( 5 )	// �q���o�X�p
#define ZKN_RANGE_DAN_HIN_DRAW_OFS_X	( 0 ) 
#define ZKN_RANGE_DAN_HIN_DRAW_OFS_Y	( -18 )

// �����@�Ђ�@���
#define ZKN_RANGE_TYPE_OAM_X	( 32 )
#define ZKN_RANGE_TYPE_OAM_Y	( 32 )
#define ZKN_RANGE_TYPE_FONTOAM_BMP_SIZX	( 9 )
#define ZKN_RANGE_TYPE_FONTOAM_BMP_SIZY	( 2 )


// �t�F�[�h�p
#define ZKN_RANGE_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

// �`�擮��p
#define ZKN_RANGE_DRAW_MOVE_COUNT_MAX	( 32 )
#define ZKN_RANGE_DRAW_MOVE_COUNT_HALF	( 16 )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	���z�}��ʁ@�O���[�o���ϐ�
//=====================================
typedef struct {
	ZKN_GLB_DATA*		p_glb;				// �O���[�o���f�[�^
	int					type;				// �\�����z�^�C�v

	// ���C���R�����O���[�o��
	ZKN_APL_DATA*	p_main_common;	// �A�v���f�[�^
} ZKN_RANGE_GLB;

//-------------------------------------
//	���z�}���	�`��O���[�o���ϐ�
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// �`��O���[�o���f�[�^

	int pokegra_move_x;
	int pokegra_move_y;

	int fade_mode;		// �t�F�[�h���[�h

	int move_sync;		// ����V���N��
} ZKN_RANGE_DRAWGLB;


//-------------------------------------
//	���z�}��ʁ@�������[�N
//=====================================
typedef struct {
	// ���[�J�����z�^�C�v
	int type;

	u8* p_hidemap_fld;
	u8* p_hidemap_dan;
	u32 hidemap_fld_num;
	u32 hidemap_dan_num;

	
	// �_���W�����@�t�B�[���h�@���z�f�[�^
	ZKN_RANGE_DATA_MONS dan_range;	// �ʏ�
	ZKN_RANGE_DATA_MONS fld_range;	// �ʏ�
	ZKN_RANGE_DATA_MONS dansp_range;	// ����
	ZKN_RANGE_DATA_MONS fldsp_range;	// ����

} ZKN_RANGE_WORK;

//-------------------------------------
//	���z�}��ʁ@�������[�N
//=====================================
typedef struct {
	// ���[�J�����z�^�C�v
	int type;

	// �_���W�����ʒuOAM
	CLACT_WORK_PTR danzyon_icon[ ZKN_RANGE_DAN_OAM_BUFF_NUM ];
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];
	int now_use;	
	
	// �����n�s��
	CLACT_WORK_PTR range_none;
	ZKN_FONTOAM_DATA* range_none_font;
	CLACT_U_RES_OBJ_PTR res_obj_other[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	// �����Ђ���
	ZKN_FONTOAM_DATA* range_mode_font[ ZKN_RANGE_TYPE_NUM ];

	// ���z�}�O���b�h�f�[�^
	u8 range_grid_data[ ZKN_RANGE_GRID_ARRAY_SIZE ];	// �ʏ�
	u8 range_grid_spdata[ ZKN_RANGE_GRID_ARRAY_SIZE ];	// ����

	// ���z�}�L�����N�^�f�[�^
	void * p_range_char_buff;			// �ʏ�
	NNSG2dCharacterData* p_range_char;
	void * p_rangesp_char_buff;			//�@����
	NNSG2dCharacterData* p_rangesp_char;

	// �_���W�����@�t�B�[���h�`��f�[�^
	ZKN_RANGE_DATA_DAN_GRID* p_dan_grid;
	ZKN_RANGE_DATA_FLD_GRID* p_fld_grid;

	// OAM��BG�����݂ɓ_�ł����郏�[�N
	int drawmove_count;	// �J�E���^
	int drawmove_flag;	// ����t���O

	// �|�P���X�g�t�F�[�h�p���샏�[�N
	ZKN_UTIL_MOVE_WORK pokegra_move;


	// �B���}�b�v�Ŕr�������\�������邽�߁A
	// ���ۂɑ��݂������z�f�[�^��
	u32 dan_range_num;
	u32 fld_range_num;
	u32 dansp_range_num;
	u32 fldsp_range_num;
} ZKN_RANGE_DRAW;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *		�A�v���P�[�V�����f�[�^�쐬�֌W
 */
//-----------------------------------------------------------------------------
static ZKN_RANGE_GLB* MakeRangeGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_RANGE_DRAWGLB* MakeRangeDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
//static ZKN_EVENT_DATA* MakeRangeEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteRangeGlb( ZKN_RANGE_GLB* p_glb );
static void DeleteRangeDrawGlb( ZKN_RANGE_DRAWGLB* p_glb );
//static void DeleteRangeEvent( ZKN_EVENT_DATA* p_event );


static int RangeEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
static int ZknRangeProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknRangeProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknRangeProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknRangeProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknRangeProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknRangeProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// �|�P�O��
static void ZknRangePokeGraOn( ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb );
static void ZknRangePokeGraOff( ZKN_RANGE_DRAWGLB* p_drawglb );

// �t�F�[�h����
static void ZknRangeOamFadeInit( ZKN_RANGE_DRAW* p_draw );
static void ZknRangeOamFadeDelete( ZKN_RANGE_DRAW* p_draw );
static void ZknRangeFadeInit( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknRangeFadeMain( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, BOOL fadein_out );
static void ZknRangeFadeOtherInit( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknRangeFadeOtherMain( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, BOOL fadein_out );

// Resource�ǂݍ���
static void ZknRangeLoadRes( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, const ZKN_RANGE_WORK* cp_datawork, int heap );
static void ZknRangeDeleteRes( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb );
static void ZknRangeSetUpBg( ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, int heap );
static void ZknRangeBgCharLoad( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, int heap );
static void ZknRangeBgCharDelete( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb );
static void ZknRangeOamResLoad( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, int heap );
static void ZknRangeOamResDelete( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb );
static void ZknRangeOamInit( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, int heap );
static void ZknRangeOamDelete( ZKN_RANGE_DRAW* p_draw );
static void ZknRangeFontOamInit( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, int heap );
static void ZknRangeFontOamDelete( ZKN_RANGE_DRAW* p_draw );

static void ZknRangeRangeNoneDrawSet( ZKN_RANGE_DRAW* p_draw, const ZKN_RANGE_WORK* p_work );
static void ZknRangeRangeTypeOn( ZKN_RANGE_DRAW* p_draw, int type );

static void ZknRangeGraphicChange( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, const ZKN_RANGE_WORK* cp_datawork, int heap );

// ���z�O���t�B�b�N�f�[�^�쐬
static void ZknRangeGraphicDataMake( ZKN_RANGE_DRAW* p_draw, const ZKN_RANGE_GLB* cp_glb, const ZKN_RANGE_WORK* cp_datawork, int heapID );
static void ZknRangeGraphicDataDelete( ZKN_RANGE_DRAW* p_draw );
static u8* ZknRangeGraphicDataFldHideMapTblGet( u32 heap, const ZKN_RANGE_GLB* cp_glb, u32* p_tbl_num );
static u8* ZknRangeGraphicDataDanHideMapTblGet( u32 heap, const ZKN_RANGE_GLB* cp_glb, u32* p_tbl_num );

static void ZknRangeGraphicDrawMain( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb );

// OAM��BG�����݂ɓ_�ł�����
static void ZknRangeGraphicDrawMoveInit( ZKN_RANGE_DRAW* p_draw );
static void ZknRangeGraphicDrawMoveStart( ZKN_RANGE_DRAW* p_draw );
static void ZknRangeGraphicDrawMoveMain( ZKN_RANGE_DRAW* p_draw );

// ���z�f�[�^�֌W
static void ZknRangeMonsRangeDataLoad( ZKN_RANGE_WORK* p_work, ZKN_RANGE_GLB* p_glb, int heap );
static void ZknRangeMonsRangeDataDelete( ZKN_RANGE_WORK* p_work );
//----------------------------------------------------------------------------
/**
 *
 *	@brief	���z�}�@�A�v���쐬
 *
 *	@param	p_data		�A�v���P�[�V�����f�[�^
 *	@param	zkn_sys		�}�ӃV�X�e��
 *	@param	heap		�g�p�q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_RangeAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_RANGE_GLB*	p_glb;
	ZKN_RANGE_DRAWGLB*	p_drawglb;
//	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeRangeGlb( heap, zkn_sys );
	p_drawglb = MakeRangeDrawGlb( heap, zkn_sys );
//	p_event = MakeRangeEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= NULL;
//	p_data->p_event_data	= p_event;
	p_data->event_num		= RangeEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknRangeProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknRangeProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknRangeProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknRangeProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknRangeProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknRangeProcDrawFuncDelete;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g	�T�u��ʁ@���j���[�A�v���j��
 *
 *	@param	p_data	�A�v���P�[�V�����f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_RangeAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteRangeGlb( p_data->p_glb_data ); 
	DeleteRangeDrawGlb( p_data->p_glb_draw ); 
//	DeleteRangeEvent( p_data->p_event_data );
}


// ���z�^�C�v�ݒ�
//----------------------------------------------------------------------------
/**
 *	@brief	���z�^�C�v�擾
 *	
 *	@param	p_data	���z�A�v���f�[�^
 *
 *	@return	���z�^�C�v
 */
//-----------------------------------------------------------------------------
int ZKN_RangeTypeGet( const ZKN_APL_DATA* p_data )
{
	const ZKN_RANGE_GLB* cp_glb = p_data->p_glb_data;

	return cp_glb->type;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄ^�C�v�ݒ�
 *
 *	@param	p_data	���z�A�v���f�[�^
 *	@param	type	���z�^�C�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_RangeTypeSet( ZKN_APL_DATA* p_data, int type )
{
	ZKN_RANGE_GLB* p_glb = p_data->p_glb_data;

	GF_ASSERT( type < ZKN_RANGE_TYPE_NUM );

	p_glb->type = type;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�O���t�F�[�h�A�E�g��ݒ�
 *
 *	@param	p_data	�A�v���P�[�V�����f�[�^
 *	@param	x		�w���W
 *	@param	y		�x���W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_RangePokeGraFadeOutSet( ZKN_APL_DATA* p_data, int x, int y )
{
	ZKN_RANGE_DRAWGLB* p_glb = p_data->p_glb_draw;

	p_glb->pokegra_move_x = x;
	p_glb->pokegra_move_y = y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h���[�h�ݒ�
 *
 *	@param	p_data		�A�v���P�[�V�����f�[�^
 *	@param	fade_mode	�t�F�[�h���[�h
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_RangeFadeModeSet( ZKN_APL_DATA* p_data, int fade_mode )
{
	ZKN_RANGE_DRAWGLB* p_glb = p_data->p_glb_draw;

	p_glb->fade_mode = fade_mode;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�V���N���ݒ�
 *
 *	@param	p_data		�A�v���P�[�V�����f�[�^
 *	@param	fade_sync	�t�F�[�h�V���N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_RangeFadeModeSync( ZKN_APL_DATA* p_data, int fade_sync )
{
	ZKN_RANGE_DRAWGLB* p_glb = p_data->p_glb_draw;

	p_glb->move_sync = fade_sync;
}



//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	���z�}�@�O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_RANGE_GLB* MakeRangeGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_RANGE_GLB* p_glb;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_RANGE_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_RANGE_GLB) );

	// �O���[�o���f�[�^
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	// �߂���O���[�o���A�v���f�[�^�擾
	p_glb->p_main_common = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_COMMON );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�쐬�����f�[�^
 */
//-----------------------------------------------------------------------------
static ZKN_RANGE_DRAWGLB* MakeRangeDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_RANGE_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_RANGE_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_RANGE_DRAWGLB) );

	// �`��f�[�^
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	���z�}�@�C�x���g�쐬
 *
 *	@param	heap		�g�p����q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�C�x���g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeRangeEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = RangeEventDataNumGet();

	// �C�x���g�f�[�^�e�[�u���쐬
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	MakeRangeChangeSound( heap, &p_event_tbl[0], zkn_sys );

	return p_event_tbl;
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���z�}�@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteRangeGlb( ZKN_RANGE_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���z�}�@�`��O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteRangeDrawGlb( ZKN_RANGE_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}
#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	���z�}�@�C�x���g�f�[�^�j��
 *
 *	@param	p_event	�C�x���g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteRangeEvent( ZKN_EVENT_DATA* p_event )
{
	GF_ASSERT( p_event );
	
	ZKN_EVENT_DeleteData( &p_event[0] );

	sys_FreeMemoryEz( p_event );
}
#endif


//----------------------------------------------------------------------------
/**
 *
 *	@brief	���z�}�A�v���@�C�x���g���擾
 *	
 *	@param	none	
 *
 *	@return	���z�}�A�v���@�C�x���g��
 *
 *
 */
//-----------------------------------------------------------------------------
static int RangeEventDataNumGet( void )
{
	return ZKN_RANGE_EVENT_NUM;
}


//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	[������]
 *	@brief	�A�v���P�[�V�����v���Z�X	�f�[�^�ύX
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknRangeProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_RANGE_GLB* p_glb = p_glbdata;
	ZKN_RANGE_WORK* p_work;
	
	// ���[�N�쐬
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_RANGE_WORK) );
	GF_ASSERT( p_work );
	memset( p_work, 0, sizeof(ZKN_RANGE_WORK) );
	p_dodata->p_work = p_work;
	
	
	// ���ݎ��Ԃ��珉�����z�f�[�^�^�C�v��ݒ�
	if( p_glb->p_glb->time_zone == TIMEZONE_MORNING ){
		p_glb->type = ZKN_RANGE_TYPE_MORNING;
	}else{
		if( (p_glb->p_glb->time_zone == TIMEZONE_NOON) ||
			(p_glb->p_glb->time_zone == TIMEZONE_EVENING) ){
			p_glb->type = ZKN_RANGE_TYPE_NOON;
		}else{
			p_glb->type = ZKN_RANGE_TYPE_NIGHT;
		}
	}

	// �B���}�b�v���쐬
	p_work->p_hidemap_fld = ZknRangeGraphicDataFldHideMapTblGet( p_dodata->heap, p_glb, &p_work->hidemap_fld_num );
	p_work->p_hidemap_dan = ZknRangeGraphicDataDanHideMapTblGet( p_dodata->heap, p_glb, &p_work->hidemap_dan_num );

	
	// ���z�f�[�^�쐬
	ZknRangeMonsRangeDataLoad( p_work, p_glb, p_dodata->heap );
	p_work->type = p_glb->type;	// ���[�J���ɂ����f
	
	return ZKN_PROC_TRUE;
}

//----------------------------------------------------------------------------
/**
 *	[���C��]
 *	@brief	�A�v���P�[�V�����v���Z�X	�f�[�^�ύX
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknRangeProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_RANGE_GLB* p_glb = p_glbdata;
	ZKN_RANGE_WORK* p_work = p_dodata->p_work;
	
	// �I����
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	// �^�C�v���ς�����番�z�f�[�^��ύX����
	if( p_work->type != p_glb->type ){
		ZknRangeMonsRangeDataDelete( p_work );
		ZknRangeMonsRangeDataLoad( p_work, p_glb, p_dodata->heap );
		p_work->type = p_glb->type;	// ���[�J���ɂ����f
	}

	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	[�j��]
 *	@brief	�A�v���P�[�V�����v���Z�X	�f�[�^�ύX
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknRangeProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_RANGE_WORK* p_work = p_dodata->p_work;

	// �B���}�b�v�e�[�u���j��
	if( p_work->p_hidemap_fld ){
		sys_FreeMemoryEz( p_work->p_hidemap_fld );
	}
	if( p_work->p_hidemap_dan ){
		sys_FreeMemoryEz( p_work->p_hidemap_dan );
	}

	// ���z�f�[�^�j��
	ZknRangeMonsRangeDataDelete( p_work );
	
	sys_FreeMemoryEz( p_work );
	p_dodata->p_work = NULL;
	
	return ZKN_PROC_TRUE;
}

//----------------------------------------------------------------------------
/**
 * [������]
 *
 *	@brief	�A�v���P�[�V�����v���Z�X	�`��
 *
 *	@param	p_glbdraw	�`��O���[�o���f�[�^
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *	@param	cp_dodata	���̏����̓������[�N�f�[�^
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknRangeProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_RANGE_GLB* cp_dataglb = cp_glbdata;
	const ZKN_RANGE_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_RANGE_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_RANGE_DRAW* p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_RANGE_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_RANGE_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_RANGE_DRAW) );

		p_drawwork = p_drawdata->p_work;
		p_drawwork->type = cp_dataglb->type;	// �������^�C�v�ݒ�

		// �O���b�h�f�[�^�擾
		p_drawwork->p_dan_grid = ZKN_RANGEDATA_GetDanGridOamData( p_drawdata->heap, NULL );		
		p_drawwork->p_fld_grid = ZKN_RANGEDATA_GetFldGridAraaData( p_drawdata->heap, NULL );		
		
		p_drawdata->seq++;
		break;
		
	case ZKN_RANGE_SEQINIT_LOAD:
		ZknRangeLoadRes( p_drawwork, p_drawglb, cp_dataglb, cp_datawork, p_drawdata->heap );

		// ���z�`��f�[�^�쐬
		ZknRangeGraphicDataMake( p_drawdata->p_work, cp_dataglb, cp_datawork, p_drawdata->heap );

		// �����n�s���\��
		ZknRangeRangeNoneDrawSet( p_drawdata->p_work, cp_datawork );


		// �`�擮�쏉����
		ZknRangeGraphicDrawMoveInit( p_drawwork );

		// ���z�f�[�^�`��
		ZknRangeGraphicDrawMain( p_drawwork, p_drawglb );
		
		// �t�F�[�h������
		if( p_drawglb->fade_mode == ZKN_RANGE_FADE_MODE_MY ){
			ZknRangeFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		}else{
			ZknRangeFadeOtherInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		}
		p_drawdata->seq++;
		break;
		
	case ZKN_RANGE_SEQINIT_FADEIN:
		if( p_drawglb->fade_mode == ZKN_RANGE_FADE_MODE_MY ){
			check = ZknRangeFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		}else{
			check = ZknRangeFadeOtherMain( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		}
		if( check ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_RANGE_SEQINIT_END:
		// ����J�n
		ZknRangeGraphicDrawMoveStart( p_drawwork );
		return ZKN_PROC_TRUE;
	}

	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 * [���C��]
 *
 *	@brief	�A�v���P�[�V�����v���Z�X	�`��
 *
 *	@param	p_glbdraw	�`��O���[�o���f�[�^
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *	@param	cp_dodata	���̏����̓������[�N�f�[�^
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknRangeProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_RANGE_GLB* cp_dataglb = cp_glbdata;
	const ZKN_RANGE_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_RANGE_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_RANGE_DRAW* p_drawwork = p_drawdata->p_work;


	// �`�擮�상�C��
	ZknRangeGraphicDrawMoveMain( p_drawwork );
	
	//���z�O���t�B�b�N�X�V
	ZknRangeGraphicChange( p_drawwork, p_drawglb, cp_dataglb, cp_datawork, p_drawdata->heap );

	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 * [�j��]
 *
 *	@brief	�A�v���P�[�V�����v���Z�X	�`��
 *
 *	@param	p_glbdraw	�`��O���[�o���f�[�^
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *	@param	cp_dodata	���̏����̓������[�N�f�[�^
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknRangeProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_RANGE_GLB* cp_dataglb = cp_glbdata;
	const ZKN_RANGE_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_RANGE_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_RANGE_DRAW* p_drawwork = p_drawdata->p_work;
	BOOL check;


	switch( p_drawdata->seq ){
	case ZKN_RANGE_SEQDELETE_FADEOUT_INIT:
		// �`�擮�쏉����
		ZknRangeGraphicDrawMoveInit( p_drawwork );

		if( p_drawglb->fade_mode == ZKN_RANGE_FADE_MODE_MY ){
			ZknRangeFadeInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		}else{
			ZknRangeFadeOtherInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		}
		p_drawdata->seq++;
		break;
		
	case ZKN_RANGE_SEQDELETE_FADEOUT:
		if( p_drawglb->fade_mode == ZKN_RANGE_FADE_MODE_MY ){
			check = ZknRangeFadeMain( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		}else{
			check = ZknRangeFadeOtherMain( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		}
		if( check ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_RANGE_SEQDELETE_RELEASE:
		
		// ���z�`��f�[�^�j��
		ZknRangeGraphicDataDelete( p_drawwork );
		
		ZknRangeDeleteRes( p_drawwork, p_drawglb );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_RANGE_SEQDELETE_FREE:
		// BG1OAM�͕\��
		GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG1, VISIBLE_ON );

		// �O���b�h�f�[�^�j��
		sys_FreeMemoryEz( p_drawwork->p_dan_grid );		
		sys_FreeMemoryEz( p_drawwork->p_fld_grid );		

		sys_FreeMemoryEz(p_drawdata->p_work);
		p_drawdata->p_work = NULL;
		p_drawdata->seq++;
		break;
		
		
	case ZKN_RANGE_SEQDELETE_END:
		return ZKN_PROC_TRUE;
	}

	return ZKN_PROC_FALSE;
}



//----------------------------------------------------------------------------
/**
 *	@brief	Resource�ǂݍ��݁���ʍ\�z
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	cp_datawork	�f�[�^���[�N
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeLoadRes( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, const ZKN_RANGE_WORK* cp_datawork, int heap )
{
	// BG�ݒ�
	ZknRangeSetUpBg( p_drawglb, cp_glb, heap );

	// �L�����N�^�f�[�^�ǂݍ���
	ZknRangeBgCharLoad( p_draw, p_drawglb, heap );

	// OAM���\�[�X�ǂݍ���
	ZknRangeOamResLoad( p_draw, p_drawglb, heap );

	// �A�N�^�[�o�^
	ZknRangeOamInit( p_draw, p_drawglb, heap );

	// FONTOAM
	ZknRangeFontOamInit( p_draw, p_drawglb, cp_glb, heap );

	// ���z�^�C�v�\��	
	ZknRangeRangeTypeOn( p_draw, cp_glb->type );

	// �|�P�O��ON
	ZknRangePokeGraOn( p_drawglb, cp_glb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	Resource�j��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeDeleteRes( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb )
{
	// �L�����N�^�f�[�^�j��
	ZknRangeBgCharDelete( p_draw, p_drawglb );

	// FONTOAM
	ZknRangeFontOamDelete( p_draw );
	
	// �A�N�^�[�j��
	ZknRangeOamDelete( p_draw );

	// OAM���\�[�X�j��
	ZknRangeOamResDelete( p_draw, p_drawglb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�w�i�ʃZ�b�g	
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 *
 * [�C�x���g�ŏo�Ă��铇�̃X�N���[���f�[�^�������������̒�]
 */
//-----------------------------------------------------------------------------
static void ZknRangeSetUpBg( ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// �L�����N�^�f�[�^�]
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_main_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, 0, 0, TRUE, heap );
	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_bg_main1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �t���O�����ăX�N���[���㏑��
	if( cp_glb->p_glb->hidemap_id_D30 ){

		// �X�N���[���f�[�^�ǂݍ���
		buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_bg_main2a_lzh_NSCR, TRUE, &p_scrn, heap );
		
		// �X�N���[���f�[�^��������
		GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
				p_scrn->rawData, 
				ZKN_RANGE_HIDEMAP_D15_X, 
				ZKN_RANGE_HIDEMAP_D15_Y,
				p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

		sys_FreeMemoryEz( buff );
	}
	if( cp_glb->p_glb->hidemap_id_D18 ){
		// �X�N���[���f�[�^�ǂݍ���
		buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_bg_main2b_lzh_NSCR, TRUE, &p_scrn, heap );
		
		// �X�N���[���f�[�^��������
		GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
				p_scrn->rawData, 
				ZKN_RANGE_HIDEMAP_D18_X, 
				ZKN_RANGE_HIDEMAP_D18_Y,
				p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

		sys_FreeMemoryEz( buff );
	}
	if( cp_glb->p_glb->hidemap_id_D15 ){
		// �X�N���[���f�[�^�ǂݍ���
		buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_bg_main2c_lzh_NSCR, TRUE, &p_scrn, heap );
		
		// �X�N���[���f�[�^��������
		GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
				p_scrn->rawData, 
				ZKN_RANGE_HIDEMAP_D30_X, 
				ZKN_RANGE_HIDEMAP_D30_Y,
				p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

		sys_FreeMemoryEz( buff );
	}
	if( cp_glb->p_glb->hidemap_id_L04 ){
		// �X�N���[���f�[�^�ǂݍ���
		buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_bg_main2d_lzh_NSCR, TRUE, &p_scrn, heap );
		
		// �X�N���[���f�[�^��������
		GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
				p_scrn->rawData, 
				ZKN_RANGE_HIDEMAP_L04_X, 
				ZKN_RANGE_HIDEMAP_L04_Y,
				p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

		sys_FreeMemoryEz( buff );
	}

	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M );

}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMResource�ǂݍ���
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeOamResLoad(  ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );

	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_map_dungeon_lzh_NCGR, TRUE,
			NARC_zukan_zkn_map_dungeon_lzh_NCGR + ZKN_RANGE_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );


	// �Z���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_map_dungeon_lzh_NCER, TRUE,
			NARC_zukan_zkn_map_dungeon_lzh_NCER + ZKN_RANGE_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_map_dungeon_lzh_NANR, TRUE,
			NARC_zukan_zkn_map_dungeon_lzh_NANR + ZKN_RANGE_RES_ID,
			CLACT_U_CELLANM_RES, heap );
	


	
	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->res_obj_other[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main3_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_main3_lzh_NCGR + ZKN_RANGE_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj_other[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj_other[ CLACT_U_CHAR_RES ] );

	// �p���b�g�f�[�^�ǂݍ���
	p_draw->res_obj_other[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_data_oam3_NCLR, FALSE, 
			NARC_zukan_zkn_data_oam3_NCLR + ZKN_RANGE_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_BIG_PLTT_LOAD, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj_other[ CLACT_U_PLTT_RES ] );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj_other[ CLACT_U_PLTT_RES ] );


	// �Z���f�[�^�ǂݍ���
	p_draw->res_obj_other[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main3_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_main3_lzh_NCER + ZKN_RANGE_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->res_obj_other[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_main3_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_main3_lzh_NANR + ZKN_RANGE_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMResource�j��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeOamResDelete( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;


	CLACT_U_CharManagerDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// ���\�[�X�j��
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->res_obj[ CLACT_U_CELLANM_RES ] );



	CLACT_U_CharManagerDelete( p_draw->res_obj_other[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_draw->res_obj_other[ CLACT_U_PLTT_RES ] );

	// ���\�[�X�j��
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_obj_other[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw->res_obj_other[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_obj_other[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->res_obj_other[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�A�N�^�[�o�b�t�@�쐬
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeOamInit( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i;
	
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_main3_lzh_NCGR + ZKN_RANGE_RES_ID,
			NARC_zukan_zkn_data_oam3_NCLR + ZKN_RANGE_RES_ID, 
			NARC_zukan_zkn_data_oam_main3_lzh_NCER + ZKN_RANGE_RES_ID,
			NARC_zukan_zkn_data_oam_main3_lzh_NANR + ZKN_RANGE_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_RANGE_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_RANGE_OAM_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	
	// �����n�s��OAM
	add.mat.x = ZKN_RANGE_NONE_OAM_X * FX32_ONE;
	add.mat.y = ZKN_RANGE_NONE_OAM_Y * FX32_ONE;
	p_draw->range_none = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->range_none, ZKN_RANGE_NONE_OAM_SEQ );



	// �_���W����OAM
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_map_dungeon_lzh_NCGR + ZKN_RANGE_RES_ID,
			NARC_zukan_zkn_data_oam3_NCLR + ZKN_RANGE_RES_ID, 
			NARC_zukan_zkn_map_dungeon_lzh_NCER + ZKN_RANGE_RES_ID,
			NARC_zukan_zkn_map_dungeon_lzh_NANR + ZKN_RANGE_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );
	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_RANGE_OAM_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	add.mat.x = 0;
	add.mat.y = 0;
	for( i=0; i<ZKN_RANGE_DAN_OAM_BUFF_NUM; i++ ){
		p_draw->danzyon_icon[i] = CLACT_AddSimple( &add );
		CLACT_SetDrawFlag( p_draw->danzyon_icon[i], FALSE );	// ��\����
		CLACT_ObjModeSet( p_draw->danzyon_icon[i], GX_OAM_MODE_XLU );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�A�N�^�[�o�b�t�@�j��
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeOamDelete( ZKN_RANGE_DRAW* p_draw )
{
	int i;

	CLACT_Delete( p_draw->range_none );
	p_draw->range_none = NULL;

	for( i=0; i<ZKN_RANGE_DAN_OAM_BUFF_NUM; i++ ){
		CLACT_Delete( p_draw->danzyon_icon[i] );
		p_draw->danzyon_icon[i] = NULL;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�쐬
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	p_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeFontOamInit( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, int heap )
{
	GF_BGL_BMPWIN* win;	// �����񏑂����ݐ�
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR res_obj;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;
	int pltt_ofs;	// �p���b�g�A�h���X
	int i;

	// ���CLACT��o�^���Ă���K�v������
	GF_ASSERT( p_draw->range_none );

	// �p���b�g�̃��\�[�X�f�[�^�擾
	// �p���b�g�v���N�V�擾�p
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_drawglb->p_drawglb->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_data_oam3_NCLR + ZKN_RANGE_RES_ID );

	// �������f�[�^�̋��ʕ������쐬
	// ���ʃf�[�^���
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( res_obj, NULL );
	fontoam_init.bg_pri		 = ZKN_RANGE_OAM_BG_PRI;
	fontoam_init.soft_pri	 = ZKN_RANGE_OAM_PRI - 1;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;

	// �p���b�g�]����A�h���X�擾
	pltt_ofs = GetPlttProxyOffset( fontoam_init.pltt, NNS_G2D_VRAM_TYPE_2DMAIN );

	
	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_RANGE_NONE_FONTOAM_BMP_SIZX,
			ZKN_RANGE_NONE_FONTOAM_BMP_SIZY );

	// ���z�ӂĂ�
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_RANGE_00, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent		 = p_draw->range_none;
	fontoam_init.x			 = ZKN_RANGE_NONE_FONTOAM_OFS_X;
	fontoam_init.y			 = ZKN_RANGE_NONE_FONTOAM_OFS_Y;
	p_draw->range_none_font  = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->range_none_font->p_fontoam, pltt_ofs + ZKN_RANGE_FONTOAM_PAL_OFS );

	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( win );


	// �r�b�g�}�b�v�E�B���h�E�쐬
	for( i=0; i<ZKN_RANGE_TYPE_NUM; i++ ){
		win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
				ZKN_RANGE_TYPE_FONTOAM_BMP_SIZX,
				ZKN_RANGE_TYPE_FONTOAM_BMP_SIZY );

		// ����
		ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
				NARC_msg_zkn_dat, ZNK_RANGE_01 + i, 0, 0 );
		fontoam_init.p_bmp		 = win;
		fontoam_init.parent		 = NULL;
		fontoam_init.x			 = ZKN_RANGE_TYPE_OAM_X;
		fontoam_init.y			 = ZKN_RANGE_TYPE_OAM_Y;
		p_draw->range_mode_font[i]  = ZKN_FONTOAM_Make( &fontoam_init );
		FONTOAM_SetPaletteNo( p_draw->range_mode_font[i]->p_fontoam, pltt_ofs + ZKN_RANGE_FONTOAM_PAL_OFS );

		// �r�b�g�}�b�v�E�B���h�E�j��
		ZKN_FONTOAM_DeleteBmp( win );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�j��
 *
 *	@param	p_draw �`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeFontOamDelete( ZKN_RANGE_DRAW* p_draw )
{
	int i;
	
	ZKN_FONTOAM_Delete( p_draw->range_none_font );

	for( i=0; i<ZKN_RANGE_TYPE_NUM; i++ ){
		ZKN_FONTOAM_Delete( p_draw->range_mode_font[i]  );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	OAM�t�F�[�h������
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeOamFadeInit( ZKN_RANGE_DRAW* p_draw )
{
	int i;
	
	CLACT_ObjModeSet( p_draw->range_none, GX_OAM_MODE_XLU );
	FONTOAM_ObjModeSet( p_draw->range_none_font->p_fontoam, GX_OAM_MODE_XLU );
	for( i=0; i<ZKN_RANGE_TYPE_NUM; i++ ){
		FONTOAM_ObjModeSet( p_draw->range_mode_font[i]->p_fontoam, GX_OAM_MODE_XLU );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�t�F�[�h���Z�b�g
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeOamFadeDelete( ZKN_RANGE_DRAW* p_draw )
{
	int i;
	
	CLACT_ObjModeSet( p_draw->range_none, GX_OAM_MODE_NORMAL );
	FONTOAM_ObjModeSet( p_draw->range_none_font->p_fontoam, GX_OAM_MODE_NORMAL );
	for( i=0; i<ZKN_RANGE_TYPE_NUM; i++ ){
		FONTOAM_ObjModeSet( p_draw->range_mode_font[ i ]->p_fontoam, GX_OAM_MODE_NORMAL );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h����������
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	fadein_out	�t�F�[�h�C���A�E�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeFadeInit( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, BOOL fadein_out )
{
	// ������OAM�ݒ�
	ZknRangeOamFadeInit( p_draw );

	// �u���C�g�l�X�������s���Ă悢��
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_RANGE_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_RANGE_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}
	}

	// �u���C�g�l�X�l�ݒ�
	ZKN_GLB_SpritePokeGraPalFade( p_drawglb->p_drawglb, &p_drawglb->p_drawglb->fade );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�������C��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	fadein_out	�t�F�[�h�C���A�E�g
 *
 *	@retval	TRUE	�t�F�[�h�I��
 *	@retval	FALSE	�t�F�[�h�r��
 */
//-----------------------------------------------------------------------------
static BOOL ZknRangeFadeMain( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check;

	// �u���C�g�l�X���悤���łĂ邩�`�F�b�N
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
		check = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade );
	}else{
		check = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade );
	}

	// �I�������I������
	if( check ){
		if( fadein_out ){
			// ������OAM�j��
			ZknRangeOamFadeDelete( p_draw );
		}

		return TRUE;
	}else{
		// �u���C�g�l�X�l�ݒ�
		ZKN_GLB_SpritePokeGraPalFade( p_drawglb->p_drawglb, &p_drawglb->p_drawglb->fade );
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���A�v���P�[�V�����ւ̃t�F�[�h����
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	fadein_out	�t�F�[�h�C���@�A�E�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeFadeOtherInit( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, BOOL fadein_out )
{
	// ������OAM�ݒ�
	ZknRangeOamFadeInit( p_draw );


	// �t�F�[�h�A�E�g�̎������̏���
	if( fadein_out == FALSE ){
		// �|�P�����O���t�B�b�N�t�F�[�h
		ZKN_UTIL_MoveReq( &p_draw->pokegra_move, ZKN_RANGE_POKEGRA_DRAW_X, p_drawglb->pokegra_move_x, ZKN_RANGE_POKEGRA_DRAW_Y, p_drawglb->pokegra_move_y, p_drawglb->move_sync);
	}

	// �u���C�g�l�X���g���ėǂ�������
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
		
		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, p_drawglb->move_sync,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_RANGE_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, p_drawglb->move_sync,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_RANGE_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}
	}
}
//----------------------------------------------------------------------------
/**
 *	@brief	���A�v���P�[�V�����ւ̃t�F�[�h�������C��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	fadein_out	�t�F�[�h�C���@�A�E�g
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL ZknRangeFadeOtherMain( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check[ 2 ];
	int i;
	

	// �t�F�[�h�A�E�g�̂Ƃ��݂̂̏���
	if( fadein_out == FALSE ){
		// �|�P�����O���t�B�b�N
		check[0] = ZKN_UTIL_MoveMain( &p_draw->pokegra_move );

		// ���W�ݒ�
		ZKN_GlbPokemonGraphicSetMatrix( p_drawglb->p_drawglb, p_draw->pokegra_move.x, p_draw->pokegra_move.y );

	}else{
		check[0] = TRUE;
	}
	
	// �u���C�g�l�X���g�p���Ă悢�Ƃ��͎�����fade�𓮂���
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
		check[1] = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade );
	}else{
		check[1] = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade );
	}

	for( i=0; i<2; i++ ){
		if( check[i] == FALSE ){
			break;
		}
	}

	if( i==2 ){

		// �t�F�[�h�C���̂Ƃ��͔������j��
		if( fadein_out == TRUE ){
			// OAM�������ݒ�j��
			ZknRangeOamFadeDelete( p_draw );
		}
		return TRUE;
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	���z�������݃L�����N�^�`�b�v�ǂݍ���
 *
 *	@param	p_draw	�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeBgCharLoad( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, int heap )
{
	// �����ʃr�b�g�}�b�v������
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );

	// �L�����N�^���\�[�X�ǂݍ���
	p_draw->p_range_char_buff = ZKN_GLBDATA_CharDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_chip_lzh_NCGR, TRUE, &p_draw->p_range_char, heap );

	// �L�����N�^���\�[�X�ǂݍ���
	p_draw->p_rangesp_char_buff = ZKN_GLBDATA_CharDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_chip2_lzh_NCGR, TRUE, &p_draw->p_rangesp_char, heap );

	// �p���b�g�i���o�[�ݒ�
	GF_BGL_BmpWinSet_Pal( &p_drawglb->p_drawglb->bmp_mfont, 8 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���z�������݃L�����N�^�`�b�v�j��
 *
 *	@param	p_draw �`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeBgCharDelete( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb ) 
{
	// �����ʃr�b�g�}�b�v������
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );

	sys_FreeMemoryEz( p_draw->p_range_char_buff );
	p_draw->p_range_char_buff = NULL;
	p_draw->p_range_char = NULL;

	sys_FreeMemoryEz( p_draw->p_rangesp_char_buff );
	p_draw->p_rangesp_char_buff = NULL;
	p_draw->p_rangesp_char = NULL;

	// �p���b�g�i���o�[�ݒ�
	GF_BGL_BmpWinSet_Pal( &p_drawglb->p_drawglb->bmp_mfont, ZKN_BG_FONT_COLOR );
}

// ���z�O���t�B�b�N�f�[�^�쐬
//----------------------------------------------------------------------------
/**
 *	@brief	���z�O���t�B�b�N�f�[�^�쐬
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	cp_glb			�O���[�o���f�[�^
 *	@param	cp_datawork		�f�[�^���[�N
 *	@param	heap			�q�[�v
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeGraphicDataMake( ZKN_RANGE_DRAW* p_draw, const ZKN_RANGE_GLB* cp_glb, const ZKN_RANGE_WORK* cp_datawork, int heapID )
{
	int i,j;
	int norm_oam, sp_oam;
	int draw_ofs_x, draw_ofs_y;
	int monsno;
	u8* p_rem_appy;	// �r���z��
	int rem_appy_num;

	ZknRangeGraphicDataDelete( p_draw );

	// ���z�f�[�^����
	// �O���b�h�f�[�^���쐬

	// �O���b�h�f�[�^�ɏ�������
	//�@�ʏ�
	p_draw->fld_range_num = ZKN_RANGE_DATA_FldGridDataWriteMonsRangeData( p_draw->range_grid_data, ZKN_RANGE_GRID_NUM_X, ZKN_RANGE_GRID_NUM_Y, p_draw->p_fld_grid, &cp_datawork->fld_range, cp_datawork->p_hidemap_fld, cp_datawork->hidemap_fld_num );

	// ���ꂩ��r�����镪�zID����쐬����
	rem_appy_num = (cp_datawork->fld_range.num - 1) + cp_datawork->hidemap_fld_num;
	p_rem_appy = sys_AllocMemoryLo( heapID, rem_appy_num );
	for( i=0; i<rem_appy_num; i++ ){
		if( i < cp_datawork->hidemap_fld_num ){
			p_rem_appy[i] = cp_datawork->p_hidemap_fld[i];
		}else{
			p_rem_appy[i] = cp_datawork->fld_range.p_rangeid[i - cp_datawork->hidemap_fld_num ];
		}
	}
	//�@����
	p_draw->fldsp_range_num = ZKN_RANGE_DATA_FldGridDataWriteMonsRangeData( p_draw->range_grid_spdata, ZKN_RANGE_GRID_NUM_X, ZKN_RANGE_GRID_NUM_Y, p_draw->p_fld_grid, &cp_datawork->fldsp_range, p_rem_appy, rem_appy_num );

	// ���ꂩ��r�����镪�zID���j��
	sys_FreeMemoryEz( p_rem_appy );
	

	// �ۂ߃L�����N�^����
	ZKN_ENCOUNTDRAW_MakeMuddyData( p_draw->range_grid_data, ZKN_RANGE_GRID_NUM_X, ZKN_RANGE_GRID_NUM_Y );
	ZKN_ENCOUNTDRAW_MakeMuddyData( p_draw->range_grid_spdata, ZKN_RANGE_GRID_NUM_X, ZKN_RANGE_GRID_NUM_Y );


	// �q���o�X�̂Ƃ���OAM������Ȃ��̂ɂȂ�
	monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	if( monsno == MONSNO_HINBASU ){
		norm_oam = ZKN_RANGE_DAN_OAMNORM_HIN_SEQ;
		sp_oam = ZKN_RANGE_DAN_OAMSP_HIN_SEQ;
		draw_ofs_x = ZKN_RANGE_DAN_DRAW_X + ZKN_RANGE_DAN_HIN_DRAW_OFS_X;
		draw_ofs_y = ZKN_RANGE_DAN_DRAW_Y + ZKN_RANGE_DAN_HIN_DRAW_OFS_Y;
	}else{
		norm_oam = ZKN_RANGE_DAN_OAMNORM_SP_SEQ;
		sp_oam = ZKN_RANGE_DAN_OAMSP_SP_SEQ;
		draw_ofs_x = ZKN_RANGE_DAN_DRAW_X;
		draw_ofs_y = ZKN_RANGE_DAN_DRAW_Y;
	}

	// �_���W�����f�[�^�ݒ�
	p_draw->now_use = 0;
	p_draw->now_use = ZKN_RANGE_DATA_DanGridDataSetMonsRangeData(
			p_draw->danzyon_icon, p_draw->now_use, ZKN_RANGE_DAN_OAM_BUFF_NUM, 
			draw_ofs_x, draw_ofs_y,
			ZKN_RANGE_GRAPHIC_GRID_SIZE, ZKN_RANGE_GRAPHIC_GRID_SIZE,
			p_draw->p_dan_grid, &cp_datawork->dan_range, 
			ZKN_RANGE_DAN_OAMNORM_NORM_SEQ, norm_oam,
			cp_datawork->p_hidemap_dan, cp_datawork->hidemap_dan_num,
			&p_draw->dan_range_num );

	// ���ꂩ��r�����镪�zID����쐬����
	rem_appy_num = (cp_datawork->dan_range.num - 1) + cp_datawork->hidemap_dan_num;
	p_rem_appy = sys_AllocMemoryLo( heapID, rem_appy_num );
	for( i=0; i<rem_appy_num; i++ ){
		if( i < cp_datawork->hidemap_dan_num ){
			p_rem_appy[i] = cp_datawork->p_hidemap_dan[i];
		}else{
			p_rem_appy[i] = cp_datawork->dan_range.p_rangeid[i - cp_datawork->hidemap_dan_num];
		}
	}

	p_draw->now_use = ZKN_RANGE_DATA_DanGridDataSetMonsRangeData(
			p_draw->danzyon_icon, p_draw->now_use, ZKN_RANGE_DAN_OAM_BUFF_NUM, 
			draw_ofs_x, draw_ofs_y,
			ZKN_RANGE_GRAPHIC_GRID_SIZE, ZKN_RANGE_GRAPHIC_GRID_SIZE,
			p_draw->p_dan_grid, &cp_datawork->dansp_range, 
			ZKN_RANGE_DAN_OAMSP_NORM_SEQ, sp_oam,
			p_rem_appy, rem_appy_num,
			&p_draw->dansp_range_num  );//*/

	// ���ꂩ��r�����镪�zID���j��
	sys_FreeMemoryEz( p_rem_appy );
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O���b�h�f�[�^�j��
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeGraphicDataDelete(  ZKN_RANGE_DRAW* p_draw )
{
	int i;
	
	memset( p_draw->range_grid_data, 0, sizeof(u8) * ZKN_RANGE_GRID_ARRAY_SIZE );
	memset( p_draw->range_grid_spdata, 0, sizeof(u8) * ZKN_RANGE_GRID_ARRAY_SIZE );

	// OAM��\��
	for( i=0; i<p_draw->now_use; i++ ){
		CLACT_SetDrawFlag( p_draw->danzyon_icon[i], FALSE );
	}
	p_draw->now_use = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�B�[���h�B���}�b�v�]�[��ID�e�[�u���쐬
 *
 *	@param	heap	�q�[�v
 *	@param	cp_glb	�O���[�o���f�[�^
 *	@param	p_tbl_num �e�[�u�����i�[��
 *
 *	@return	�e�[�u���@�j���̕K�v����
 */
//-----------------------------------------------------------------------------
static u8* ZknRangeGraphicDataFldHideMapTblGet( u32 heap, const ZKN_RANGE_GLB* cp_glb, u32* p_tbl_num )
{
	u32 tbl_num;
	int i;
	u8* p_tbl;

	tbl_num = 0;
	
	// �e�[�u���쐬�̂��ߐ��𐔂���K�v������
	if( cp_glb->p_glb->hidemap_id_D15 == FALSE ){
		i = 0;
		while( ZKN_FLD_ZONE_ID_D15_IDTBL[ i ] != 0xffff ){
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_D18 == FALSE ){
		i = 0;
		while( ZKN_FLD_ZONE_ID_D18_IDTBL[ i ] != 0xffff ){
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_D30 == FALSE ){
		i = 0;
		while( ZKN_FLD_ZONE_ID_D30_IDTBL[ i ] != 0xffff ){
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_L04 == FALSE ){
		i = 0;
		while( ZKN_FLD_ZONE_ID_L04_IDTBL[ i ] != 0xffff ){
			tbl_num++;
			i++;
		}
	}
	if( tbl_num > 0 ){
		p_tbl = sys_AllocMemory( heap, sizeof(u8) * tbl_num );
	}else{
		p_tbl = NULL;
	}
	*p_tbl_num = tbl_num;


	// �e�[�u���ݒ�
	if( cp_glb->p_glb->hidemap_id_D15 == FALSE ){
		i = 0;
		while( ZKN_FLD_ZONE_ID_D15_IDTBL[ i ] != 0xffff ){
			p_tbl[ i ] = ZKN_FLD_ZONE_ID_D15_IDTBL[ i ];
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_D18 == FALSE ){
		i = 0;
		while( ZKN_FLD_ZONE_ID_D18_IDTBL[ i ] != 0xffff ){
			p_tbl[ i ] = ZKN_FLD_ZONE_ID_D18_IDTBL[ i ];
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_D30 == FALSE ){
		i = 0;
		while( ZKN_FLD_ZONE_ID_D30_IDTBL[ i ] != 0xffff ){
			p_tbl[ i ] = ZKN_FLD_ZONE_ID_D30_IDTBL[ i ];
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_L04 == FALSE ){
		i = 0;
		while( ZKN_FLD_ZONE_ID_L04_IDTBL[ i ] != 0xffff ){
			p_tbl[ i ] = ZKN_FLD_ZONE_ID_L04_IDTBL[ i ];
			tbl_num++;
			i++;
		}
	}

	return p_tbl;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�_���W�����B���}�b�v�]�[��ID�e�[�u���쐬
 *
 *	@param	heap	�q�[�v
 *	@param	cp_glb	�O���[�o���f�[�^
 *	@param	p_tbl_num �e�[�u�����i�[��
 *
 *	@return	�e�[�u���@�j���̕K�v����
 */
//-----------------------------------------------------------------------------
static u8* ZknRangeGraphicDataDanHideMapTblGet( u32 heap, const ZKN_RANGE_GLB* cp_glb, u32* p_tbl_num )
{
	u32 tbl_num;
	int i;
	u8* p_tbl;

	tbl_num = 0;
	
	// �e�[�u���쐬�̂��ߐ��𐔂���K�v������
	if( cp_glb->p_glb->hidemap_id_D15 == FALSE ){
		i = 0;
		while( ZKN_DAN_ZONE_ID_D15_IDTBL[ i ] != 0xffff ){
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_D18 == FALSE ){
		i = 0;
		while( ZKN_DAN_ZONE_ID_D18_IDTBL[ i ] != 0xffff ){
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_D30 == FALSE ){
		i = 0;
		while( ZKN_DAN_ZONE_ID_D30_IDTBL[ i ] != 0xffff ){
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_L04 == FALSE ){
		i = 0;
		while( ZKN_DAN_ZONE_ID_L04_IDTBL[ i ] != 0xffff ){
			tbl_num++;
			i++;
		}
	}

	if( tbl_num > 0 ){
		p_tbl = sys_AllocMemory( heap, sizeof(u8) * tbl_num );
		
	}else{
		p_tbl = NULL;
	}

	*p_tbl_num = tbl_num;


	//�@�e�[�u����ݒ肷��
	tbl_num = 0;
	if( cp_glb->p_glb->hidemap_id_D15 == FALSE ){
		i=0;
		while( ZKN_DAN_ZONE_ID_D15_IDTBL[ i ] != 0xffff ){
			p_tbl[ tbl_num ] = ZKN_DAN_ZONE_ID_D15_IDTBL[ i ];
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_D18 == FALSE ){
		i = 0;
		while( ZKN_DAN_ZONE_ID_D18_IDTBL[ i ] != 0xffff ){
			p_tbl[ tbl_num ] = ZKN_DAN_ZONE_ID_D18_IDTBL[ i ];
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_D30 == FALSE ){
		i = 0;
		while( ZKN_DAN_ZONE_ID_D30_IDTBL[ i ] != 0xffff ){
			p_tbl[ tbl_num ] = ZKN_DAN_ZONE_ID_D30_IDTBL[ i ];
			tbl_num++;
			i++;
		}
	}
	if( cp_glb->p_glb->hidemap_id_L04 == FALSE ){
		i = 0;
		while( ZKN_DAN_ZONE_ID_L04_IDTBL[ i ] != 0xffff ){
			p_tbl[ tbl_num ] = ZKN_DAN_ZONE_ID_L04_IDTBL[ i ];
			tbl_num++;
			i++;
		}
	}

	return p_tbl;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O���b�h�f�[�^�`�惁�C������
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeGraphicDrawMain( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb )
{
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );

	// ����
	ZKN_ENCOUNTDRAW_PrintChar(
			&p_drawglb->p_drawglb->bmp_mfont,
			p_draw->p_rangesp_char->pRawData,
			p_draw->p_rangesp_char->W * 8, p_draw->p_rangesp_char->H * 8,
			ZKN_RANGE_GRAPHIC_GRID_SIZE,
			p_draw->range_grid_spdata,
			ZKN_RANGE_GRID_NUM_X, ZKN_RANGE_GRID_NUM_Y,
			ZKN_RANGE_BMP_DRAW_X, ZKN_RANGE_BMP_DRAW_Y );

	
	// �ʏ�
	ZKN_ENCOUNTDRAW_PrintChar(
			&p_drawglb->p_drawglb->bmp_mfont,
			p_draw->p_range_char->pRawData,
			p_draw->p_range_char->W * 8, p_draw->p_range_char->H * 8,
			ZKN_RANGE_GRAPHIC_GRID_SIZE,
			p_draw->range_grid_data,
			ZKN_RANGE_GRID_NUM_X, ZKN_RANGE_GRID_NUM_Y,
			ZKN_RANGE_BMP_DRAW_X, ZKN_RANGE_BMP_DRAW_Y );

	// �\��ON
	GF_BGL_BmpWinOn( &p_drawglb->p_drawglb->bmp_mfont );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�����n�ӂ߂��`��ONOFF
 *
 *	@param	p_draw	�`�惏�[�N
 *	@param	p_work	���[�N
 * 
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeRangeNoneDrawSet( ZKN_RANGE_DRAW* p_draw, const ZKN_RANGE_WORK* p_work )
{
	// �_���W�������t�B�[���h�����z�f�[�^�������Ƃ���W�� ���̑��\��
	if( (p_draw->dan_range_num <= 0) &&
		(p_draw->fld_range_num <= 0) &&
		(p_draw->dansp_range_num <= 0) &&
		(p_draw->fldsp_range_num <= 0) ){
		
		CLACT_SetDrawFlag( p_draw->range_none, TRUE );
		FONTOAM_SetDrawFlag( p_draw->range_none_font->p_fontoam, TRUE );
	}else{

		CLACT_SetDrawFlag( p_draw->range_none, FALSE );
		FONTOAM_SetDrawFlag( p_draw->range_none_font->p_fontoam, FALSE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���z�^�C�v�\���ؑ�
 *
 *	@param	p_draw	�`�惏�[�N
 *	@param	type	���z�^�C�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeRangeTypeOn( ZKN_RANGE_DRAW* p_draw, int type )
{
	int i;

	for( i=0; i<ZKN_RANGE_TYPE_NUM; i++ ){
		if( i == type ){
			FONTOAM_SetDrawFlag( p_draw->range_mode_font[ i ]->p_fontoam, TRUE );
		}else{
			FONTOAM_SetDrawFlag( p_draw->range_mode_font[ i ]->p_fontoam, FALSE );
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	���z�`��f�[�^�X�V
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	cp_glb			�f�[�^�O���[�o��
 *	@param	cp_datawork		�f�[�^���[�N
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeGraphicChange( ZKN_RANGE_DRAW* p_draw, ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb, const ZKN_RANGE_WORK* cp_datawork, int heap )
{
	// �^�C�v���ύX���ꂽ�當����,�O���t�B�b�N�f�[�^�ύX
	if( p_draw->type != cp_datawork->type ){
		
		// ���z�`��f�[�^�쐬
		ZknRangeGraphicDataMake( p_draw, cp_glb, cp_datawork, heap );

		// ���z�f�[�^�`��
		ZknRangeGraphicDrawMain( p_draw, p_drawglb );

		// ���z�^�C�v�\��	
		ZknRangeRangeTypeOn( p_draw, cp_glb->type );

		// �����n�s���\��
		ZknRangeRangeNoneDrawSet( p_draw, cp_datawork );

		// ���z�X�V
		p_draw->type = cp_datawork->type;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������z�f�[�^�ǂݍ���
 *
 *	@param	p_work	���[�N
 *	@param	p_glb	�O���[�o���f�[�^
 *	@param	heap	�q�[�v
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeMonsRangeDataLoad( ZKN_RANGE_WORK* p_work, ZKN_RANGE_GLB* p_glb, int heap )
{
	int dan_type;
	int fld_type;
	int mons_no = ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb );
	
	switch( p_glb->type ){
	case ZKN_RANGE_TYPE_MORNING:// ��
		dan_type = ZKN_RANGEDATA_TYPE_DAN_MORNING;
		fld_type = ZKN_RANGEDATA_TYPE_FLD_MORNING;
		break;
		
	case ZKN_RANGE_TYPE_NOON:	// ��
		dan_type = ZKN_RANGEDATA_TYPE_DAN_NOON;
		fld_type = ZKN_RANGEDATA_TYPE_FLD_NOON;
		break;
		
	case ZKN_RANGE_TYPE_NIGHT:	// ��
		dan_type = ZKN_RANGEDATA_TYPE_DAN_NIGHT;
		fld_type = ZKN_RANGEDATA_TYPE_FLD_NIGHT;
		break;

	default:
		// ��������
		GF_ASSERT( 0 );
		break;
	}

	// �ʏ�_���W����
	ZKN_RANGEDATA_GetMonsNoRange( &p_work->dan_range, mons_no, dan_type, heap );

	// �ʏ�t�B�[���h
	ZKN_RANGEDATA_GetMonsNoRange( &p_work->fld_range, mons_no, fld_type, heap );
	
	// �}�ӕێ��ƕێ���Ł@����f�[�^�͕ύX����
	if( ZKN_GLBDATA_SaveData_ZenkokuZukanGet( p_glb->p_glb ) == FALSE ){
		
		// �}�ӕێ��O
		// ����_���W����
		ZKN_RANGEDATA_GetMonsNoRange( &p_work->dansp_range, mons_no, ZKN_RANGEDATA_TYPE_DAN_SPECIAL, heap );
		// ����t�B�[���h
		ZKN_RANGEDATA_GetMonsNoRange( &p_work->fldsp_range, mons_no, ZKN_RANGEDATA_TYPE_FLD_SPECIAL, heap );
	}else{
		
		// �}�ӕێ���
		// ����_���W����
		ZKN_RANGEDATA_GetMonsNoRange( &p_work->dansp_range, mons_no, ZKN_RANGEDATA_TYPE_DAN_SPECIAL_COMP, heap );
		// ����t�B�[���h
		ZKN_RANGEDATA_GetMonsNoRange( &p_work->fldsp_range, mons_no, ZKN_RANGEDATA_TYPE_FLD_SPECIAL_COMP, heap );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������z�f�[�^�j��
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeMonsRangeDataDelete( ZKN_RANGE_WORK* p_work )
{
	// �ʏ�_���W����
	ZKN_RANGEDATA_DeleteMonsNoRange( &p_work->dan_range );

	// �ʏ�t�B�[���h
	ZKN_RANGEDATA_DeleteMonsNoRange( &p_work->fld_range );
	
	// ����_���W����
	ZKN_RANGEDATA_DeleteMonsNoRange( &p_work->dansp_range );
	
	// ����t�B�[���h
	ZKN_RANGEDATA_DeleteMonsNoRange( &p_work->fldsp_range );
}


//----------------------------------------------------------------------------
/**
 *	@brief	���z�}�O���t�B�b�N�����݂ɕ\�����鏉����
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeGraphicDrawMoveInit( ZKN_RANGE_DRAW* p_draw )
{
	int i;
	p_draw->drawmove_count = 0;
	p_draw->drawmove_flag = 0;

	// BG1OAM�͔�W��
	GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG1, VISIBLE_OFF );
	for( i=0; i<p_draw->now_use; i++ ){
		CLACT_SetDrawFlag( p_draw->danzyon_icon[i], FALSE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�n
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeGraphicDrawMoveStart( ZKN_RANGE_DRAW* p_draw )
{
	int i;

	G2_SetBlendAlpha( GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3, GX_BLEND_PLANEMASK_BG3, 0, 16 );

	// BG��\�����AOAM�͔�W��
	GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG1, VISIBLE_ON );
	for( i=0; i<p_draw->now_use; i++ ){
		CLACT_SetDrawFlag( p_draw->danzyon_icon[i], FALSE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���z�}�O���t�B�b�N�����݂ɕ\������
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeGraphicDrawMoveMain( ZKN_RANGE_DRAW* p_draw )
{
	fx32 alpha;
	int count;
	int i;


	// �\������		���S�ɏ����Ă���\�������悤��
	// ��\�������[��VBLANK�|���\�������Ƃ����ӂ��ɂ��Ă��܂�
	if( p_draw->drawmove_count >= ZKN_RANGE_DRAW_MOVE_COUNT_MAX ){
		p_draw->drawmove_count = 0;	// �J�E���g������
		// 0�̂Ƃ�BG
		if( p_draw->drawmove_flag == 0 ){

			// OAM�\���ݒ�
			for( i=0; i<p_draw->now_use; i++ ){
				CLACT_SetDrawFlag( p_draw->danzyon_icon[ i ], TRUE );
			}
			p_draw->drawmove_flag = 1;
		}else{
			// BG�\���ݒ�
			GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG1, VISIBLE_ON );
			p_draw->drawmove_flag = 0;
		}
	}
	
	// ���l�ݒ�
	if( p_draw->drawmove_count < ZKN_RANGE_DRAW_MOVE_COUNT_HALF ){
		count = p_draw->drawmove_count;
	}else{
		count = ZKN_RANGE_DRAW_MOVE_COUNT_MAX - p_draw->drawmove_count;
	}
	alpha = FX_Mul( (16 << FX32_SHIFT), (count << FX32_SHIFT) );
	alpha = FX_Div( alpha, (ZKN_RANGE_DRAW_MOVE_COUNT_HALF << FX32_SHIFT) );
	G2_ChangeBlendAlpha( alpha >> FX32_SHIFT, 16 );
	
	// �J�E���g����
	p_draw->drawmove_count++;


	// ��\������
	if( p_draw->drawmove_count >= ZKN_RANGE_DRAW_MOVE_COUNT_MAX ){
		// 0�̂Ƃ�BG
		if( p_draw->drawmove_flag == 0 ){

			GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG1, VISIBLE_OFF );
		}else{
			// OAM��\���ݒ�
			for( i=0; i<p_draw->now_use; i++ ){
				CLACT_SetDrawFlag( p_draw->danzyon_icon[ i ], FALSE );
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�\��ON
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangePokeGraOn( ZKN_RANGE_DRAWGLB* p_drawglb, const ZKN_RANGE_GLB* cp_glb )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );

	// �|�P�����ݒ�
	ZKN_UTIL_PokemonGraphicSet( p_drawglb->p_drawglb, cp_glb->p_glb,
			monsno,
			PARA_FRONT, ZKN_RANGE_POKEGRA_DRAW_X, ZKN_RANGE_POKEGRA_DRAW_Y );
	
	// �\��
	SoftSpriteParaSet( p_pokegra, SS_PARA_VANISH, FALSE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�\��OFF
 *
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangePokeGraOff( ZKN_RANGE_DRAWGLB* p_drawglb )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );

	// �\��OFF
	SoftSpriteParaSet( p_pokegra, SS_PARA_VANISH, TRUE );

	// �\�t�g�p���b�g�t�F�[�h���������Ă���\��������̂�OFF
	SoftSpritePalFadeOff( p_pokegra );
}
