//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_sys_static.h
 *	@brief		�}�ӃV�X�e���̓������J�f�[�^	(�}�ӂ̃V�X�e�������include�o����)
 *	@author		tomoya takahashi
 *	@data		2006.01.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_SYS_STATIC_H__
#define __ZKN_SYS_STATIC_H__

#include "include/gflib/touchpanel.h"

// �f�[�^�֌W
#include "include/application/zukanlist/zkn_glbdata.h"


// �`��֌W
#include "include/application/zukanlist/zkn_drawglb.h"


// ��������֌W
#include "include/application/zukanlist/zkn_proc_sys.h"
#include "include/application/zukanlist/zkn_event.h"

#undef GLOBAL
#ifdef	__ZKN_SYS_STATIC_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�A�v���P�[�V�������
//=====================================
//���C��
enum {
	ZKN_SYS_APLMAIN_POKELIST,		// �|�P�������X�g
	ZKN_SYS_APLMAIN_SORTSEARCH,		// �����\�[�g
	ZKN_SYS_APLMAIN_ZUKAN,			// �}�Ӊ��
	ZKN_SYS_APLMAIN_ZUKAN_GRA,		// �}�Ӊ�ʃO���t�B�b�N�o�[�W����
	ZKN_SYS_APLMAIN_ZUKAN_TEXT,		// �}�Ӊ�ʌ���o�[�W����
	ZKN_SYS_APLMAIN_ZUKAN_COMMON,	// �}�Ӊ�ʋ���
	ZKN_SYS_APLMAIN_RANGE,			// ���z�}
	ZKN_SYS_APLMAIN_SOUND,			// ������
	ZKN_SYS_APLMAIN_BIG,			// �傫�����	 ����
	ZKN_SYS_APLMAIN_BIG_WEIGHT,		// �傫�����    �d��
	ZKN_SYS_APLMAIN_NUM,			// �A�v���P�[�V���������̓A�v���P�[�V��������
} ;
// �T�u
enum {
	ZKN_SYS_APLSUB_POKELIST,				// �|�P�������X�g
	ZKN_SYS_APLSUB_SORTSEARCH,				// �����\�[�g
	ZKN_SYS_APLSUB_ZUKAN,					// �}�Ӊ��
	ZKN_SYS_APLSUB_ZUKAN_COMMON,			// �}�Ӊ�ʋ���
	ZKN_SYS_APLSUB_RANGE,					// ���z�}
	ZKN_SYS_APLSUB_SOUND,					// ������
	ZKN_SYS_APLSUB_BIG,						// �傫�����    
	ZKN_SYS_APLSUB_ZUKAN_GRA,				// �}�Ӊ�ʃO���t�B�b�N�o�[�W����


#ifdef PM_DEBUG
	ZKN_SYS_APLSUB_HEIGHT_DEBUG,			// �������DEBUG�A�v��
#endif 
	
	ZKN_SYS_APLSUB_NUM,						// �A�v���P�[�V���������̓A�v���P�[�V��������
} ;



//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�e�A�v���P�[�V�����f�[�^�\����
//=====================================
typedef struct {
	void* p_glb_data;								// �O���[�o���f�[�^
	void* p_glb_draw;								// �O���[�o���f�[�^
	ZKN_PROC_DO_FUNC	do_func[ZKN_PROC_FUNC_NUM];// �e�����֐�
	ZKN_PROC_DRAW_FUNC	draw_func[ZKN_PROC_FUNC_NUM];// �e�����֐�
	ZKN_EVENT_DATA*		p_event_data;			// �C�x���g�f�[�^
	int	event_num;									// �C�x���g��
} ZKN_APL_DATA;

typedef struct _ZKN_SYS* ZKN_SYS_PTR;
typedef const struct _ZKN_SYS* CONST_ZKN_SYS_PTR;
//-------------------------------------
//	�A�v���P�[�V�����f�[�^�쐬�֐�
//=====================================
typedef void (*ZKN_APL_DATA_MAKE_FUNC)( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
typedef void (*ZKN_APL_DATA_DELETE_FUNC)( ZKN_APL_DATA* p_data );



//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
// �O���[�o���f�[�^�A�N�Z�X�֐�
GLOBAL ZKN_PROC_SYS_PTR	ZKN_SYS_GetProcSysMain( ZKN_SYS_PTR zkn );
GLOBAL ZKN_PROC_SYS_PTR	ZKN_SYS_GetProcSysSub( ZKN_SYS_PTR zkn );
GLOBAL ZKN_PROC_SYS_PTR	ZKN_SYS_GetProcSysMainCommon( ZKN_SYS_PTR zkn );
GLOBAL ZKN_PROC_SYS_PTR	ZKN_SYS_GetProcSysSubCommon( ZKN_SYS_PTR zkn );

GLOBAL ZKN_EVENT_SYS_PTR ZKN_SYS_GetEventSysMain( ZKN_SYS_PTR zkn );
GLOBAL ZKN_EVENT_SYS_PTR ZKN_SYS_GetEventSysSub( ZKN_SYS_PTR zkn );
GLOBAL ZKN_EVENT_SYS_PTR ZKN_SYS_GetEventSysMainCommon( ZKN_SYS_PTR zkn );
GLOBAL ZKN_EVENT_SYS_PTR ZKN_SYS_GetEventSysSubCommon( ZKN_SYS_PTR zkn );

GLOBAL int* ZKN_SYS_GetEventKeyPtrMain( ZKN_SYS_PTR zkn );
GLOBAL int* ZKN_SYS_GetEventKeyPtrSub( ZKN_SYS_PTR zkn );
GLOBAL int* ZKN_SYS_GetEventKeyPtrMainCommon( ZKN_SYS_PTR zkn );
GLOBAL int* ZKN_SYS_GetEventKeyPtrSubCommon( ZKN_SYS_PTR zkn );

GLOBAL BOOL* ZKN_SYS_GetZknDeleteFlag( ZKN_SYS_PTR zkn );

GLOBAL ZKN_GLB_DATA* ZKN_SYS_GetGlbData( ZKN_SYS_PTR zkn );
GLOBAL ZKN_GLB_DRAWDATA* ZKN_SYS_GetGlbDrawData( ZKN_SYS_PTR zkn );

GLOBAL ZKN_APL_DATA* ZKN_GetAplDataMain( ZKN_SYS_PTR zkn, int apl_no );
GLOBAL ZKN_APL_DATA* ZKN_GetAplDataSub( ZKN_SYS_PTR zkn, int apl_no );


//-----------------------------------------------------------------------------
//
/**
 *		�����ȃA�v���P�[�V���������ʂ��Ďg�p�ł������
 */
//-----------------------------------------------------------------------------
#define ZKN_UTIL_BUTTON_PUSH_NONE	(BMN_EVENT_SLIDEOUT + 1)
enum{
	ZKN_UTIL_BUTTON_FRAME_NONE,		// ����
	ZKN_UTIL_BUTTON_FRAME_PUSH1,	// �v�b�V���A�j���P�t���[����
	ZKN_UTIL_BUTTON_FRAME_PUSH2,	// �v�b�V���A�j���Q�t���[����
	ZKN_UTIL_BUTTON_FRAME_SELECT,	// �I��
};
GLOBAL void ZKN_UTIL_ButtonMove( CLACT_WORK_PTR act, int button_event );
GLOBAL void ZKN_UTIL_ButtonFontMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y );
GLOBAL void ZKN_UTIL_ButtonFontMove_Col( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt );

GLOBAL void ZKN_UTIL_HitTblDataSet( TP_HIT_TBL* p_tbl, int top, int bottom, int left, int right );

//-------------------------------------
//	BG�X�N���[��Shutter�t�F�[�h�\����
//=====================================
typedef struct {
	GF_BGL_INI* p_bg;			// BG�f�[�^
	NNSG2dScreenData* p_scrn;	// �X�N���[���f�[�^
	int frm;					// �t���[����

	int top_start;			// ��̊J�nY�L�����N�^�ʒu
	int bottom_start;		// ���̊J�nY�L�����N�^�ʒu
	int top_dis;			// ��̓��싗��
	int bottom_dis;			// ���̓��싗��
	
	int move_count;			// �J�E���^
	int move_count_max;		// �ő吔
} ZKN_UTIL_BGSHTTER_DADE;
GLOBAL void ZKN_UTIL_BgShutterFadeInit( ZKN_UTIL_BGSHTTER_DADE* p_data, GF_BGL_INI* p_bg, int frm, NNSG2dScreenData* p_scrn, int top_cs, int top_ce, int bottom_cs, int bottom_ce, int count_max );
GLOBAL BOOL ZKN_UTIL_BgShutterFade( ZKN_UTIL_BGSHTTER_DADE* p_data );


//-------------------------------------
//	�|�P���������X�g�쐬�֐��S
//=====================================
// ������OAM
#define ZKN_POKELIST_POKENAME_BMP_SIZE_CX	( 15 )	// �������ݗ̈�̃r�b�g�}�b�v�T�C�Y
#define ZKN_POKELIST_POKENAME_BMP_SIZE_CY	( 2 )	// �������ݗ̈�̃r�b�g�}�b�v�T�C�Y
#define ZKN_POKELIST_POKENAME_BMP_SIZE_X	( 128 )	// �������ݗ̈�̃r�b�g�}�b�v�T�C�Y
#define ZKN_POKELIST_POKENAME_BMP_SIZE_Y	( 16 )	// �������ݗ̈�̃r�b�g�}�b�v�T�C�Y
#define ZKN_POKELIST_POKENAME_NO_NUM		( 4 )	// STRBUF�̗̈�擾��
#define ZKN_POKELIST_POKENAME_NO_KETA		( 3 )	// �����̌�
#define ZKN_POKELIST_POKENAME_MAT_Y			( 0 )
#define ZKN_POKELIST_POKENAME_NO_MAT_X		( 18 )
#define ZKN_POKELIST_POKENAME_NAME_MAT_X	( 52 )

// �A�C�R���萔
#define ZKN_POKELIST_ICON_X_OFS		( -54 * FX32_ONE )	// ���I������Ă���|�P�����e�[�u����X���W����̋���

GLOBAL void ZKN_UTIL_PokeListPokeNameBmpMake( GF_BGL_BMPWIN* p_bmp, int num, int monsno, int heap );
GLOBAL GF_BGL_BMPWIN* ZKN_UTIL_PokeListPokeNameTblBmpMake( ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_GLB_DATA* cp_glb, int heap, int mons_no );
GLOBAL void ZKN_UTIL_PokeListPokeNameMakeGlb( ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_GLB_DATA* cp_glb, int heap, int poke_tbl_no, fx32 x, fx32 y );
GLOBAL void ZKN_UTIL_PokeListPokeNameGlbMatrixSet(  ZKN_GLB_DRAWDATA* p_drawglb, int x, int y );

GLOBAL GF_BGL_BMPWIN* ZKN_UTIL_PokeListPokeNameTblBmpMake_Zenkoku( ZKN_FONTOAM_SYS_PTR fontoam_sys, int heap, int mons_no );
GLOBAL GF_BGL_BMPWIN* ZKN_UTIL_PokeListPokeNameTblBmpMake_Shinou( ZKN_FONTOAM_SYS_PTR fontoam_sys, int heap, int mons_no );
GLOBAL void ZKN_UTIL_PokeListPokeNameGlbMatrixSet_Minute(  ZKN_POKELIST_DATA_OAM_DATA* p_data, int x, int y );

//-------------------------------------
//	�|�P�����O���t�B�b�N�ݒ�֐�
//=====================================
GLOBAL void  ZKN_UTIL_PokemonGraphicSet( ZKN_GLB_DRAWDATA* p_draw, ZKN_GLB_DATA* p_glb, int mons_no, int dir, int x, int y );

GLOBAL u32 ZKN_UTIL_PokemonGraphicSet_FS_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int mons_no, int dir, int x, int y, int count, int idx );
GLOBAL u32 ZKN_UTIL_PokemonGraphicSet_Anoon_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx );
GLOBAL u32 ZKN_UTIL_PokemonGraphicSet_Siiusi_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx );
GLOBAL u32 ZKN_UTIL_PokemonGraphicSet_Siidorugo_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx );
GLOBAL u32 ZKN_UTIL_PokemonGraphicSet_Minomutti_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx );
GLOBAL u32 ZKN_UTIL_PokemonGraphicSet_Minomesu_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx );
GLOBAL u32 ZKN_UTIL_PokemonGraphicSet_Deokisisu_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx );



//-------------------------------------
//	�|�P�����}�Ӄ��b�Z�[�W�ް�STRBUF�擾
//=====================================
GLOBAL STRBUF* ZKN_UTIL_ZknGmmGet( int data_idx, int heap );


#undef	GLOBAL
#endif		// __ZKN_SYS_STATIC_H__

