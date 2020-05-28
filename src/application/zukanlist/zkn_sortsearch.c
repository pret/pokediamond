//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_sortsearch.c
 *	@brief		�����\�[�g�A�v���P�[�V����
 *	@author		tomoya takahashi
 *	@data		2006.01.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"

#include "include/gflib/calctool.h"

#include "include/system/brightness.h"
#include "include/system/arc_util.h"
#include "include/system/fontproc.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"
#include "include/application/zukanlist/zkn_snd_def.h"

#include "include/application/zukanlist/zukan.naix"

#include "include/application/zukanlist/zkn_pokelist_sub.h"
#include "include/application/zukanlist/zkn_pokelist.h"

#define	__ZKN_SORTSEARCH_H_GLOBAL
#include "include/application/zukanlist/zkn_sortsearch.h"


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
#define ZKN_SORTSEARCH_EVENT_NUM ( 1 )	// �C�x���g��
#define ZKN_SORTSEARCH_CHANGE_POKELIST	( 0x1 << 1 )	// �|�P���X�g�ֈړ�

#define ZKN_SORTSEARCH_OAM_BG_PRI	( 2 )
#define ZKN_SORTSEARCH_OAM_PRI		( 31 )

//-------------------------------------
//	�V�[�P���X
//=====================================
enum{
	ZKN_SORTSEARCH_SEQINIT_ALLOC,
	ZKN_SORTSEARCH_SEQINIT_LOAD,
	ZKN_SORTSEARCH_SEQINIT_FADEIN,
	ZKN_SORTSEARCH_SEQINIT_END,
};
enum{
	ZKN_SORTSEARCH_SEQDELETE_FADEOUT_INIT,
	ZKN_SORTSEARCH_SEQDELETE_FADEOUT,
	ZKN_SORTSEARCH_SEQDELETE_RELEASE,
	ZKN_SORTSEARCH_SEQDELETE_FREE,
	ZKN_SORTSEARCH_SEQDELETE_END,
};

// BG
#define ZKN_SORTSEARCH_BG_X			( 6 )
#define ZKN_SORTSEARCH_BG_SORT_Y	( 6 )
#define ZKN_SORTSEARCH_BG_NAME_Y	( 9 )
#define ZKN_SORTSEARCH_BG_TYPE_Y	( 12 )
#define ZKN_SORTSEARCH_BG_FORM_Y	( 17 )


// FONT BG
#define ZKN_SORTSEARCH_PLTT				( 7 )
#define ZKN_SORTSEARCH_STR_NUM			( 64 )
#define ZKN_SORTSEARCH_FONT_BG_X		( 104 )
#define ZKN_SORTSEARCH_FONT_BG_SORT_Y	( 52 )
#define ZKN_SORTSEARCH_FONT_BG_NAME_Y	( 76 )
#define ZKN_SORTSEARCH_FONT_BG_TYPE1_Y	( 102 )
#define ZKN_SORTSEARCH_FONT_BG_TYPE2_Y	( 120 )
#define ZKN_SORTSEARCH_FONT_BG_AREA_X	( 80 )
#define ZKN_SORTSEARCH_FONT_BG_AREA_Y	( 16 )

#define ZKN_SORTSEARCH_FONT_BG_SELECT_X	( 32 )
#define ZKN_SORTSEARCH_FONT_BG_SELECT_Y	( 8 )
#define ZKN_SORTSEARCH_FONT_BG_SELECT_AREA_X	( 208 )
#define ZKN_SORTSEARCH_FONT_BG_SELECT_AREA_Y	( 32 )

#define ZKN_SORTSEARCH_FONT_BG_NAME_BOU_NUM	( 5 ) 
#define ZKN_SORTSEARCH_FONT_BG_TYPE_BOU_NUM	( 4 ) 
#define ZKN_SORTSEARCH_FONT_BG_BOU_SIZE_X	( 16 )

// FORM�@OAM
#define ZKN_SORTSEARCH_FORM_OAM_X	( 128 )
#define ZKN_SORTSEARCH_FORM_OAM_Y	( 164 )
#define ZKN_SORTSEARCH_FORM_OAM_ANM	( 3 )
enum{
	ZKN_SORTSEARCH_FORM_OAM_FOUR_LEGS = ZKN_SORTSEARCH_FORM_OAM_ANM,
	ZKN_SORTSEARCH_FORM_OAM_TWO_LEGS,
	ZKN_SORTSEARCH_FORM_OAM_TAIL,
	ZKN_SORTSEARCH_FORM_OAM_HARABAI,
	ZKN_SORTSEARCH_FORM_OAM_FOUR_WING,
	ZKN_SORTSEARCH_FORM_OAM_TWO_WING,
	ZKN_SORTSEARCH_FORM_OAM_HAITSUKUBARI,
	ZKN_SORTSEARCH_FORM_OAM_STRAIGHT,
	ZKN_SORTSEARCH_FORM_OAM_ARM,
	ZKN_SORTSEARCH_FORM_OAM_LEGS,
	ZKN_SORTSEARCH_FORM_OAM_MANY_LEGS,
	ZKN_SORTSEARCH_FORM_OAM_WATER,
	ZKN_SORTSEARCH_FORM_OAM_CIRCLE,
	ZKN_SORTSEARCH_FORM_OAM_COMP,
};

// ��Ď��s�e�L�X�g�`��J�E���g
#define ZKN_SORTSEARCH_ERR_DRAW_COUNT	( 64 )


// ��Ĵ̪��
#define ZKN_SORTSEARCH_EFECT_ACT_X		( 128 )
#define ZKN_SORTSEARCH_EFECT_ACT_Y		( 96 )
#define ZKN_SORTSEARCH_EFECT_ACT_ANM	( 17 )
#define ZKN_SORTSEARCH_EFECT_FONT_X		( 96 )
#define ZKN_SORTSEARCH_EFECT_FONT_Y		( 128 )

#define ZKN_SORTSEARCH_EFECT_OAM_ROTA	( FX_GET_ROTA_NUM(180) )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�����\�[�g��ʁ@�O���[�o���ϐ�
//=====================================
typedef struct {
	int*				p_event_key;		// �C�x���g�L�[
	ZKN_GLB_DATA*		p_glb;				// �O���[�o���f�[�^
	ZKN_POKELIST_GLB_DATA* p_pokelist;		// �|�P���X�g

	int					now_select;			// ���݂̃Z���N�g����
	int					sort_type;			// �������
	int					search_name;		// �Ȃ܂��T�[�`����
	int					search_type1;		// ���߃T�[�`����
	int					search_type2;		// ���߃T�[�`����
	int					search_form;		// �������T�[�`����
	BOOL				list_chg_flag;// ���X�g��ʂ�
	BOOL				sort_flag;		// ��Ď��s�t���O
	BOOL				sort_err;		// ��Ď��s���s

	// ���[�h
	int		fade_mode;			// �t�F�[�h���[�h
	int		fade_count;			// �t�F�[�h����J�E���g	
								// ���̶����őS���삷��
} ZKN_SORTSEARCH_GLB;

//-------------------------------------
//	�����\�[�g��ʁ@�`��O���[�o���ϐ�
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// �`��O���[�o���f�[�^
} ZKN_SORTSEARCH_DRAWGLB;

//-------------------------------------
//	�����\�[�g��ʁ@�������[�N
//=====================================
typedef struct {
	int dummy;
} ZKN_SORTSEARCH_WORK;

//-------------------------------------
//	�����\�[�g��ʁ@�`�惏�[�N
//=====================================
typedef struct {
	int		now_select;			// ���݂̃Z���N�g����
	int		sort_type;			// �������
	int		search_name;		// �Ȃ܂��T�[�`����
	int		search_type1;		// ���߃T�[�`����
	int		search_type2;		// ���߃T�[�`����
	int		search_form;		// �������T�[�`����

	BOOL				sort_err;		// ��Ď��s���s
	int					sort_err_draw_count;	// ��Ď��s���s�`�涳��

	// �t�H�[��OAM
	CLACT_WORK_PTR search_form_act;
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// Resource�I�u�W�F�|�C���^
	// �V���b�^�[�t�F�[�h
	ZKN_UTIL_BGSHTTER_DADE shutter;

	// �������A�j���p
	CLACT_WORK_PTR sort_act;

	void* p_scrn_buff;
	NNSG2dScreenData* p_scrn;	// �X�N���[���f�[�^
} ZKN_SORTSEARCH_DRAW;

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
static ZKN_SORTSEARCH_GLB* MakeSortSearchGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_SORTSEARCH_DRAWGLB* MakeSortSearchDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeSortSearchEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteSortSearchGlb( ZKN_SORTSEARCH_GLB* p_glb );
static void DeleteSortSearchDrawGlb( ZKN_SORTSEARCH_DRAWGLB* p_glb );
static void DeleteSortSearchEvent( ZKN_EVENT_DATA* p_event );


static int SortSearchEventDataNumGet( void );

//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
static int ZknSortSearchProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSortSearchProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSortSearchProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSortSearchProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknSortSearchProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknSortSearchProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// �t�F�[�h����
static void ZknSortSearchFadeSys( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap );

// �������G�t�F�N�g����
static void ZknSortSearchSortEffSys( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap );
static void ZknSortSearchSortEffFontSet( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int heap );
static void ZknSortSearchSortEffFontReset( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, ZKN_SORTSEARCH_DRAW* p_draw, int heap );

// Resource�ǂݍ���
static void ZknSortSearchLoadRes( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, const ZKN_SORTSEARCH_WORK* cp_datawork, int heap );
static void ZknSortSearchDeleteRes( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb );
static void ZknSortSearchSetUpBg( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap );
static void ZknSortSearchOamResLoad( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int heap );
static void ZknSortSearchOamResDelete( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb );
static void ZknSortSearchOamInit( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap );
static void ZknSortSearchOamDelete( ZKN_SORTSEARCH_DRAW* p_draw );
static void ZknSortSearchUtilBgLoad( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap, int zkn_mode );
static void ZknSortSearchUtilBgDelete( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb );



// �`�揈��
static void ZknSortSearchSelectDraw( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb,  int heap );

static void ZknSortSearchBgSelectType( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap );
static void ZknSortSearchFontSelectType( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap );
static void ZKnSortSearchFontSortType( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap );
static void ZKnSortSearchFontSearchName( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap );
static void ZKnSortSearchFontSearchType1( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap );
static void ZKnSortSearchFontSearchType2( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap );
static void ZKnSortSearchFontSearchType_Core( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap, int y );
static void ZKnSortSearchOamSearchForm( ZKN_SORTSEARCH_DRAW* p_draw, int type );
static void ZknSortSearchFontNotHitPokemon( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int heap );


static void ZknSortSearchPokeGraDrawOff( ZKN_SORTSEARCH_DRAWGLB* p_drawglb );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����\�[�g�@�A�v���쐬
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
void ZKN_SortSearchAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_SORTSEARCH_GLB*	p_glb;
	ZKN_SORTSEARCH_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeSortSearchGlb( heap, zkn_sys );
	p_drawglb = MakeSortSearchDrawGlb( heap, zkn_sys );
	p_event = MakeSortSearchEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= SortSearchEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknSortSearchProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknSortSearchProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknSortSearchProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknSortSearchProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknSortSearchProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknSortSearchProcDrawFuncDelete;
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
void ZKN_SortSearchAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteSortSearchGlb( p_data->p_glb_data ); 
	DeleteSortSearchDrawGlb( p_data->p_glb_draw ); 
	DeleteSortSearchEvent( p_data->p_event_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ݑI�����Ă������߂�ݒ�
 *
 *	@param	p_data	�A�v���ް�
 *	@param	type	����
 *
 *	@return	none
 *	typoe
	ZKN_SORTSEARCH_SELECT_SORT,
	ZKN_SORTSEARCH_SELECT_NEME,
	ZKN_SORTSEARCH_SELECT_TYPE,
	ZKN_SORTSEARCH_SELECT_FORM,
 */
//-----------------------------------------------------------------------------
void ZKN_SortSearchAplSelectTypeSet( ZKN_APL_DATA* p_data, int type )
{
	ZKN_SORTSEARCH_GLB* p_glb = p_data->p_glb_data;

	GF_ASSERT( type < ZKN_SORTSEARCH_SELECT_NUM );
	p_glb->now_select = type;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ݑI�����Ă������߂��擾
 *
 *	@param	cp_data		�A�v���P�[�V�����ް�
 *
 *	@return	�I������
 */
//-----------------------------------------------------------------------------
int ZKN_SortSearchAplSelectTypeGet( const ZKN_APL_DATA* cp_data )
{
	const ZKN_SORTSEARCH_GLB* cp_glb = cp_data->p_glb_data;

	return cp_glb->now_select;
}

//----------------------------------------------------------------------------
/**
 *	@brief	������ߐݒ�
 *
 *	@param	p_data	�A�v���ް�
 *	@param	type	����
 *
 *	@return	none
 *
 *	type
	ZKN_POKELIST_SORT_NORMAL,		// �|�P�����i���o�[
	ZKN_POKELIST_SORT_GOZYUUON,		// �܏\��
	ZKN_POKELIST_SORT_GRAM_L,		// �d��
	ZKN_POKELIST_SORT_GRAM_S,		// �y��
	ZKN_POKELIST_SORT_HIGH_L,		// ����
	ZKN_POKELSIT_SOTT_HIGH_S,		// �Ⴂ
 *
 */
//-----------------------------------------------------------------------------
void ZKN_SortSearchAplSortTypeSet( ZKN_APL_DATA* p_data, int type )
{
	ZKN_SORTSEARCH_GLB* p_glb = p_data->p_glb_data;

	GF_ASSERT( type < ZKN_POKELIST_SORT_NUM );
	p_glb->sort_type = type;
}

//----------------------------------------------------------------------------
/**
 *	@brief	������߂��擾
 *
 *	@param	cp_data		�A�v���ް�
 *
 *	@return	�������
 */
//-----------------------------------------------------------------------------
int ZKN_SortSearchAplSortTypeGet( const ZKN_APL_DATA* cp_data )
{
	const ZKN_SORTSEARCH_GLB* cp_glb = cp_data->p_glb_data;

	return cp_glb->sort_type;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Ȃ܂����ߐݒ�
 *
 *	@param	p_data	�A�v���ް�
 *	@param	type	���O����
 *
 * type
	ZKN_POKELIST_SEARCH_NAME_NONE,
	ZKN_POKELIST_SEARCH_NAME_A,
	ZKN_POKELIST_SEARCH_NAME_KA,
	ZKN_POKELIST_SEARCH_NAME_SA,
	ZKN_POKELIST_SEARCH_NAME_TA,
	ZKN_POKELIST_SEARCH_NAME_NA,
	ZKN_POKELIST_SEARCH_NAME_HA,
	ZKN_POKELIST_SEARCH_NAME_MA,
	ZKN_POKELIST_SEARCH_NAME_RA,
	ZKN_POKELIST_SEARCH_NAME_YAWA,
 * 
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_SortSearchAplNameTypeSet( ZKN_APL_DATA* p_data, int type )
{
	ZKN_SORTSEARCH_GLB* p_glb = p_data->p_glb_data;

	GF_ASSERT( type < ZKN_POKELIST_SEARCH_NAME_NUM );
	p_glb->search_name = type;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ϴ���ߎ擾
 *
 *	@param	cp_data		�A�v���ް�
 *
 *	@return	�ϴ����
 */
//-----------------------------------------------------------------------------
int ZKN_SortSearchAplNameTypeGet( const ZKN_APL_DATA* cp_data )
{
	const ZKN_SORTSEARCH_GLB* cp_glb = cp_data->p_glb_data;

	return cp_glb->search_name;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�������ߐݒ�
 *	
 *	@param	p_data		�A�v���f�[�^
 *	@param	type		����
 *	@param	no			�������ް 0or1
 *
 * type
	ZKN_POKELIST_SEARCH_TYPE_NONE,
	ZKN_POKELIST_SEARCH_TYPE_NORMAL,
	ZKN_POKELIST_SEARCH_TYPE_BATTLE,	
	ZKN_POKELIST_SEARCH_TYPE_HIKOU,	
	ZKN_POKELIST_SEARCH_TYPE_POISON,	
	ZKN_POKELIST_SEARCH_TYPE_JIMEN,	
	ZKN_POKELIST_SEARCH_TYPE_IWA,		
	ZKN_POKELIST_SEARCH_TYPE_MUSHI,	
	ZKN_POKELIST_SEARCH_TYPE_GHOST,	
	ZKN_POKELIST_SEARCH_TYPE_METAL,	
	ZKN_POKELIST_SEARCH_TYPE_FIRE,	
	ZKN_POKELIST_SEARCH_TYPE_WATER,	
	ZKN_POKELIST_SEARCH_TYPE_KUSA,	
	ZKN_POKELIST_SEARCH_TYPE_ELECTRIC,
	ZKN_POKELIST_SEARCH_TYPE_SP,		
	ZKN_POKELIST_SEARCH_TYPE_KOORI,	
	ZKN_POKELIST_SEARCH_TYPE_DRAGON,	
	ZKN_POKELIST_SEARCH_TYPE_AKU,	
 * 
 * no
	ZKN_SORTSEARCH_TYPE1,
	ZKN_SORTSEARCH_TYPE2

 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_SortSearchAplTypeTypeSet( ZKN_APL_DATA* p_data, int type, int no )
{
	ZKN_SORTSEARCH_GLB* p_glb = p_data->p_glb_data;

	GF_ASSERT( type < ZKN_POKELIST_SEARCH_TYPE_NUM );

	if( no == ZKN_SORTSEARCH_TYPE1 ){
		p_glb->search_type1 = type;
	}else{
		p_glb->search_type2 = type;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�������߂̎擾
 *
 *	@param	cp_data		�A�v���ް�
 *	@param	no			�������ް
 *
 *	@return	��������
 */
//-----------------------------------------------------------------------------
int ZKN_SortSearchAplTypeTypeGet( const ZKN_APL_DATA* cp_data, int no )
{
	const ZKN_SORTSEARCH_GLB* cp_glb = cp_data->p_glb_data;

	if( no == ZKN_SORTSEARCH_TYPE1 ){
		return cp_glb->search_type1;
	}

	return cp_glb->search_type2;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�����߂̐ݒ�
 *
 *	@param	p_data		�A�v���ް�
 *	@param	type		����
 *
 *	@return	none
 *	type
	ZKN_POKELIST_SEARCH_FORM_NONE,
	ZKN_POKELIST_SEARCH_FORM_FOUR_LEGS,
	ZKN_POKELIST_SEARCH_FORM_TWO_LEGS,
	ZKN_POKELIST_SEARCH_FORM_TAIL,
	ZKN_POKELIST_SEARCH_FORM_HARABAI,
	ZKN_POKELIST_SEARCH_FORM_FOUR_WING,
	ZKN_POKELIST_SEARCH_FORM_TWO_WING,
	ZKN_POKELIST_SEARCH_FORM_HAITSUKUBARI,
	ZKN_POKELIST_SEARCH_FORM_STRAIGHT,
	ZKN_POKELIST_SEARCH_FORM_ARM,
	ZKN_POKELIST_SEARCH_FORM_LEGS,
	ZKN_POKELIST_SEARCH_FORM_MANY_LEGS,
	ZKN_POKELIST_SEARCH_FORM_WATER,
	ZKN_POKELIST_SEARCH_FORM_CIRCLE,
	ZKN_POKELIST_SEARCH_FORM_COMP,
 */
//-----------------------------------------------------------------------------
void ZKN_SortSearchAplFormTypeSet( ZKN_APL_DATA* p_data, int type )
{
	ZKN_SORTSEARCH_GLB* p_glb = p_data->p_glb_data;

	GF_ASSERT( type < ZKN_POKELIST_SEARCH_FORM_NUM );
	p_glb->search_form = type;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�����߂̎擾
 *	
 *	@param	cp_data		�A�v���ް�
 *
 *	@return	�`������
 */
//-----------------------------------------------------------------------------
int ZKN_SortSearchAplFormTypeGet( const ZKN_APL_DATA* cp_data )
{
	const ZKN_SORTSEARCH_GLB* cp_glb = cp_data->p_glb_data;

	return cp_glb->search_form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���X�g��ʂ֍s��
 *
 *	@param	p_data
 *	@param	do_sort	TRUE	��Ă��s��
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_SortSearchAplReqListFade( ZKN_APL_DATA* p_data, BOOL do_sort )
{
	ZKN_SORTSEARCH_GLB* p_glb = p_data->p_glb_data;

	p_glb->list_chg_flag = TRUE;
	p_glb->sort_flag = do_sort;
}

//----------------------------------------------------------------------------
/**
 *	@brief	��ď������s�����̃t���O
 *
 *	@param	p_data	�A�v���ް�
 *
 *	@retval	TRUE	�s��
 *	@retval	FALSE	�s��Ȃ�
 */
//-----------------------------------------------------------------------------
BOOL ZKN_SortSearchAplSortDoFlagGet( const ZKN_APL_DATA* cp_data )
{
	const ZKN_SORTSEARCH_GLB* cp_glb = cp_data->p_glb_data;

	return cp_glb->sort_flag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���샂�[�h�擾
 *	
 *	@param	cp_data 
 *
 *	@return	���샂�[�h
	ZKN_SORTSEARCH_MOVE_MODE_SELECT,	�p�����[�^�ݒ蒆
	ZKN_SORTSEARCH_MOVE_MODE_DO_SORT,	������
 */
//-----------------------------------------------------------------------------
int ZKN_SortSearchAplFadeModeGet( const ZKN_APL_DATA* cp_data )
{
	const ZKN_SORTSEARCH_GLB* cp_glb = cp_data->p_glb_data;

	return cp_glb->fade_mode;
}
//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�J�E���g�l�擾
 *
 *	@param	cp_data		�A�v���ް�
 *
 *	@return	�t�F�[�h�J�E���g�l
 */
//-----------------------------------------------------------------------------
int ZKN_SortSearchAplFadeModeCountGet( const ZKN_APL_DATA* cp_data )
{
	const ZKN_SORTSEARCH_GLB* cp_glb = cp_data->p_glb_data;

	return cp_glb->fade_count;
}



//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����\�[�g�@�O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_SORTSEARCH_GLB* MakeSortSearchGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_SORTSEARCH_GLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_SORTSEARCH_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_SORTSEARCH_GLB) );

	// main��ʂ���̃C�x���g�L�[
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrMain( zkn_sys ); 

	// �O���[�o���f�[�^
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	// �|�P���X�g
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_POKELIST );
	p_glb->p_pokelist = p_apl->p_glb_data;

	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����\�[�g�@�O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_SORTSEARCH_DRAWGLB* MakeSortSearchDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_SORTSEARCH_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_SORTSEARCH_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_SORTSEARCH_DRAWGLB) );

	// �`��f�[�^
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����\�[�g�@�C�x���g�쐬
 *
 *	@param	heap		�g�p����q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�C�x���g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeSortSearchEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = SortSearchEventDataNumGet();

	// �C�x���g�f�[�^�e�[�u���쐬
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_MakeChangePokeList( heap, &p_event_tbl[0], zkn_sys, ZKN_SORTSEARCH_CHANGE_POKELIST );

	return p_event_tbl;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����\�[�g�@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSortSearchGlb( ZKN_SORTSEARCH_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����\�[�g�@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSortSearchDrawGlb( ZKN_SORTSEARCH_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����\�[�g�@�C�x���g�f�[�^�j��
 *
 *	@param	p_event	�C�x���g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSortSearchEvent( ZKN_EVENT_DATA* p_event )
{
	GF_ASSERT( p_event );
	
	ZKN_EVENT_DeleteData( &p_event[0] );

	sys_FreeMemoryEz( p_event );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����\�[�g�A�v���@�C�x���g���擾
 *	
 *	@param	none	
 *
 *	@return	�����\�[�g�A�v���@�C�x���g��
 *
 *
 */
//-----------------------------------------------------------------------------
static int SortSearchEventDataNumGet( void )
{
	return ZKN_SORTSEARCH_EVENT_NUM;
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
static int ZknSortSearchProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SORTSEARCH_GLB* p_glb = p_glbdata;
	ZKN_SORTSEARCH_WORK* p_work;

	// ���[�N�쐬
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_SORTSEARCH_WORK) );
	GF_ASSERT( p_work );
	memset( p_work, 0, sizeof(ZKN_SORTSEARCH_WORK) );
	p_dodata->p_work = p_work;


	//�@�O���[�o���ް�������
	p_glb->now_select = ZKN_SORTSEARCH_SELECT_SORT;
	p_glb->sort_type  = ZKN_POKELIST_SORT_NORMAL;
	p_glb->search_name = ZKN_POKELIST_SEARCH_NAME_NONE;
	p_glb->search_type1 = ZKN_POKELIST_SEARCH_TYPE_NONE;
	p_glb->search_type2 = ZKN_POKELIST_SEARCH_TYPE_NONE;
	p_glb->search_form = ZKN_POKELIST_SEARCH_FORM_NONE;
	
	p_glb->list_chg_flag = FALSE;
	p_glb->sort_flag = FALSE;

	p_glb->fade_mode = ZKN_SORTSEARCH_FADENONE;
	
	
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
static int ZknSortSearchProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SORTSEARCH_GLB* p_glb = p_glbdata;
	ZKN_SORTSEARCH_WORK*	p_work = p_dodata->p_work;
	BOOL check;
	
	// �I����
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	switch( p_dodata->seq ){
	case 0:
		// ��Ď��s����
		if( p_glb->sort_err ){
			p_glb->sort_err = FALSE;
		}

		if( p_glb->list_chg_flag == TRUE ){

			// ��Č������s�`�F�b�N
			if( p_glb->sort_flag == FALSE ){
				// B�{�^���Ń|�P�������X�g��
				*p_glb->p_event_key |= ZKN_SORTSEARCH_CHANGE_POKELIST;
				p_glb->fade_mode = ZKN_SORTSEARCH_END_FADE;	
			}else{
				p_glb->fade_mode = ZKN_SORTSEARCH_FADEOUT;
				p_glb->fade_count = ZKN_SORTSEARCH_FADECOUNT_MAX;
				p_dodata->seq++;
			}
		}
		break;

	case 1:
		// �t�F�[�h�J�E���g
		p_glb->fade_count --;
		if( p_glb->fade_count < 0 ){
			p_dodata->seq++;
			
			p_glb->fade_mode = ZKN_SORTSEARCH_DO_MAIN;
			p_glb->fade_count = ZKN_SORTSEARCH_DO_MAIN_EFF_COUNT_MAX;

			
			Snd_SePlay( ZKN_SND_SEARCH );
		}
		break;

	case 2:
		// �����G�t�F�N�g�J�E���g
		p_glb->fade_count --;
		if( p_glb->fade_count < 0 ){
			p_dodata->seq++;
		}
		break;
		
	case 3:			// ��Ļ������
		check = TRUE;
	
		// ��Ď��s����Ȃ炷��
		// �߹��ؽĕύX
		check = ZKN_GLBDATA_PokeListTblMake_DummyListCutFlg( p_glb->p_glb, p_glb->sort_type,
				p_glb->search_name, p_glb->search_type1, 
				p_glb->search_type2, p_glb->search_form, 
				ZKN_GLBDATA_PokeZknModeGet( p_glb->p_glb ), p_dodata->heap, TRUE );

		if( check == TRUE ){
			// B�{�^���Ń|�P�������X�g��
			*p_glb->p_event_key |= ZKN_SORTSEARCH_CHANGE_POKELIST;

			// ���X�g�擪�ʒu��ݒ�
			ZKN_GLBDATA_PokeListDrawTblNoSet( p_glb->p_glb, 0 );

			// �|�P���X�g��Ļ�����[�h�ŊJ��
			p_glb->p_glb->sort_search_flag = ZKN_SORTSEARCH_SORT;
			p_glb->p_pokelist->fade_sort_data = TRUE;
		}else{

			p_glb->sort_flag = FALSE;
			p_glb->list_chg_flag = FALSE;
			// ��Ď��s
			p_glb->sort_err = TRUE;
			// ������@�ύX
			p_glb->fade_mode = ZKN_SORTSEARCH_FADEIN;
			p_glb->fade_count = ZKN_SORTSEARCH_FADECOUNT_MAX;

			p_dodata->seq ++;

		}
		break;
		
	// �t�F�[�h�C��
	case 4:
		// �t�F�[�h�J�E���g
		p_glb->fade_count --;
		if( p_glb->fade_count < 0 ){
			p_glb->fade_mode = ZKN_SORTSEARCH_FADENONE;
			p_glb->fade_count = 0;
			p_dodata->seq = 0;
		}
		break;

	default:
		GF_ASSERT( 0 );
		break;
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
static int ZknSortSearchProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SORTSEARCH_WORK* p_work = p_dodata->p_work;
	ZKN_SORTSEARCH_GLB* p_glb = p_glbdata;



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
static int ZknSortSearchProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SORTSEARCH_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SORTSEARCH_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SORTSEARCH_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SORTSEARCH_DRAW* p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_SORTSEARCH_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_SORTSEARCH_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_SORTSEARCH_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_SORTSEARCH_SEQINIT_LOAD:
		ZknSortSearchLoadRes( p_drawwork, p_drawglb, cp_dataglb, cp_datawork, p_drawdata->heap );

		
		// �t�F�[�h������
		ChangeBrightnessRequest( ZKN_FADE_SYNC_COMMON,
				BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_MAIN_DISPLAY );
		p_drawdata->seq++;
		break;
		
	case ZKN_SORTSEARCH_SEQINIT_FADEIN:
		// �t�F�[�h
		if( IsFinishedBrightnessChg( MASK_MAIN_DISPLAY  ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_SORTSEARCH_SEQINIT_END:
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
static int ZknSortSearchProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SORTSEARCH_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SORTSEARCH_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SORTSEARCH_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SORTSEARCH_DRAW* p_drawwork = p_drawdata->p_work;


	if( cp_dataglb->fade_mode == ZKN_SORTSEARCH_FADENONE ){
		
		// �I���������̓����@
		ZknSortSearchSelectDraw( p_drawwork, p_drawglb, cp_dataglb, p_drawdata->heap );
		
	}else if( (cp_dataglb->fade_mode == ZKN_SORTSEARCH_FADEOUT) || 
			(cp_dataglb->fade_mode == ZKN_SORTSEARCH_FADEIN) ){

		// �t�F�[�h����
		ZknSortSearchFadeSys( p_drawwork, p_drawglb, cp_dataglb, p_drawdata->heap );
	}else if( cp_dataglb->fade_mode != ZKN_SORTSEARCH_END_FADE ){
  
		// �������G�t�F�N�g
		ZknSortSearchSortEffSys( p_drawwork, p_drawglb, cp_dataglb, p_drawdata->heap );
	}


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
static int ZknSortSearchProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SORTSEARCH_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SORTSEARCH_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SORTSEARCH_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SORTSEARCH_DRAW* p_drawwork = p_drawdata->p_work;
	BOOL check;


	switch( p_drawdata->seq ){
	case ZKN_SORTSEARCH_SEQDELETE_FADEOUT_INIT:
		if( cp_dataglb->sort_flag == FALSE ){
			ChangeBrightnessRequest( COMM_BRIGHTNESS_SYNC, 
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, PLANEMASK_ALL, MASK_MAIN_DISPLAY );
			p_drawdata->seq++;
		}else{
			p_drawdata->seq = ZKN_SORTSEARCH_SEQDELETE_RELEASE;
		}
		break;
		
	case ZKN_SORTSEARCH_SEQDELETE_FADEOUT:
		if( IsFinishedBrightnessChg( MASK_MAIN_DISPLAY  ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_SORTSEARCH_SEQDELETE_RELEASE:
		
		ZknSortSearchDeleteRes( p_drawwork, p_drawglb );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_SORTSEARCH_SEQDELETE_FREE:

		sys_FreeMemoryEz(p_drawdata->p_work);
		p_drawdata->p_work = NULL;
		p_drawdata->seq++;
		break;
		
		
	case ZKN_SORTSEARCH_SEQDELETE_END:
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
static void ZknSortSearchLoadRes( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, const ZKN_SORTSEARCH_WORK* cp_datawork, int heap )
{
	// ���[�e�B���e�B�ʃX�N���[���j��
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M );
	// �t�H���g�ʃX�N���[���j��
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );

	// ���̉�ʂł�FONT�J���[��7�ɂ���
	GF_BGL_BmpWinSet_Pal( &p_drawglb->p_drawglb->bmp_mfont, ZKN_SORTSEARCH_PLTT );

	// �|�P�O���\��OFF
	ZknSortSearchPokeGraDrawOff( p_drawglb );
	
	// BG�ݒ�
	ZknSortSearchSetUpBg( p_drawglb, cp_glb, heap );

	// ���[�e�B���e�B��
	ZknSortSearchUtilBgLoad( p_draw, p_drawglb, cp_glb, heap, ZKN_GLBDATA_PokeZknModeGet( cp_glb->p_glb ) );

	//OAM�ǂݍ���
	ZknSortSearchOamResLoad( p_draw, p_drawglb, heap );

	// OAM�o�^
	ZknSortSearchOamInit( p_draw, p_drawglb, cp_glb, heap );

	// �\���̏����ݒ�
	ZknSortSearchFontSelectType( p_drawglb, cp_glb->now_select, heap );
	ZknSortSearchBgSelectType( p_drawglb, cp_glb->now_select, heap );
	ZKnSortSearchFontSortType( p_drawglb, cp_glb->sort_type, heap );
	ZKnSortSearchFontSearchName( p_drawglb, cp_glb->search_name, heap );
	ZKnSortSearchFontSearchType1( p_drawglb, cp_glb->search_type1, heap );
	ZKnSortSearchFontSearchType2( p_drawglb, cp_glb->search_type2, heap );
	ZKnSortSearchOamSearchForm( p_draw, cp_glb->search_form );


	// �\���D�揇�ʂ�ύX
	GF_BGL_PrioritySet( ZKN_BG_FRM_FONT_M, 1 );
	GF_BGL_PrioritySet( ZKN_BG_FRM_UTIL_M, 0 );
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
static void ZknSortSearchDeleteRes( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb )
{
	// OAM�j��
	ZknSortSearchOamDelete( p_draw );

	// OAM���\�[�X�j��
	ZknSortSearchOamResDelete( p_draw, p_drawglb );

	// ���[�e�B�e�B�ʔj��
	ZknSortSearchUtilBgDelete( p_draw, p_drawglb );


	// �t�H���g�ʃX�N���[���j��
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );

	// ���̉�ʂł�FONT�J���[�����ǂ�
	GF_BGL_BmpWinSet_Pal( &p_drawglb->p_drawglb->bmp_mfont, ZKN_BG_FONT_COLOR );

	// �\���D�揇�ʂ�ύX
	GF_BGL_PrioritySet( ZKN_BG_FRM_FONT_M, 0 );
	GF_BGL_PrioritySet( ZKN_BG_FRM_UTIL_M, 1 );
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
static void ZknSortSearchSetUpBg( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap )
{
	void* p_buff;

	
	// �L�����N�^�f�[�^�]
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_list_main_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, 0, 0, TRUE, heap );


	// �J���[�p���b�g��]��
	ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_sort2_NCLR, PALTYPE_MAIN_BG, 0, 32, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�e�B���e�B�ʕ`��ݒ�
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o��
 *	@param	heap		�q�[�v
 *	@param	zkn_mode	�}�Ӄ��[�h
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchUtilBgLoad( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap, int zkn_mode )
{
	int dataidx;
	
	// �L�����N�^�f�[�^�]��
//	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_list_main_lzh_NCGR, p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M, 0, 0, TRUE, heap );

	// �S���ƃV���I�E�Ńf�[�^idx��ύX
	if( zkn_mode == ZKN_MODE_ZENKOKU ){
		dataidx = NARC_zukan_zkn_list_bg_zen_lzh_NSCR;
	}else{
		dataidx = NARC_zukan_zkn_list_bg_sin_lzh_NSCR;
	}
	
	// �X�N���[���f�[�^�ǂݍ���
	p_draw->p_scrn_buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, dataidx, TRUE, &p_draw->p_scrn, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�e�B�e�BBG�ʂ͂�
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchUtilBgDelete( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb )
{
	sys_FreeMemoryEz( p_draw->p_scrn_buff );
	p_draw->p_scrn_buff = NULL;
	p_draw->p_scrn = NULL;
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
static void ZknSortSearchPokeGraDrawOff( ZKN_SORTSEARCH_DRAWGLB* p_drawglb )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );

	// �\��OFF
	SoftSpriteParaSet( p_pokegra, SS_PARA_VANISH, TRUE );

	// �\�t�g�p���b�g�t�F�[�h���������Ă���\��������̂�OFF
	SoftSpritePalFadeOff( p_pokegra );
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
static void ZknSortSearchOamResLoad(  ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_draw_glb );
	
	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_list_oam_main_lzh_NCGR, TRUE,
			NARC_zukan_zkn_list_oam_main_lzh_NCGR + ZKN_SORTSEARCH_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// �p���b�g�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_list_oam_NCLR, FALSE, 
			NARC_zukan_zkn_list_oam_NCLR + ZKN_SORTSEARCH_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_POKELIST_TBL_PLTT_LOAD, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// �Z���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_list_oam_main_lzh_NCER, TRUE,
			NARC_zukan_zkn_list_oam_main_lzh_NCER + ZKN_SORTSEARCH_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_list_oam_main_lzh_NANR, TRUE,
			NARC_zukan_zkn_list_oam_main_lzh_NANR + ZKN_SORTSEARCH_RES_ID,
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
static void ZknSortSearchOamResDelete( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;


	CLACT_U_CharManagerDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );

	// ���\�[�X�j��
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw->res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->res_obj[ CLACT_U_CELLANM_RES ] );
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
static void ZknSortSearchOamInit( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;

	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_list_oam_main_lzh_NCGR + ZKN_SORTSEARCH_RES_ID,
			NARC_zukan_zkn_list_oam_NCLR + ZKN_SORTSEARCH_RES_ID, 
			NARC_zukan_zkn_list_oam_main_lzh_NCER + ZKN_SORTSEARCH_RES_ID,
			NARC_zukan_zkn_list_oam_main_lzh_NANR + ZKN_SORTSEARCH_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_SORTSEARCH_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_SORTSEARCH_OAM_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	
	//form
	add.mat.x = ZKN_SORTSEARCH_FORM_OAM_X << FX32_SHIFT;
	add.mat.y = ZKN_SORTSEARCH_FORM_OAM_Y << FX32_SHIFT;
	p_draw->search_form_act = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_ANM );


	// ��Ĵ̪�ėp�A�N�^�[
	add.mat.x = ZKN_SORTSEARCH_EFECT_ACT_X << FX32_SHIFT;
	add.mat.y = ZKN_SORTSEARCH_EFECT_ACT_Y << FX32_SHIFT;
	p_draw->sort_act = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->sort_act, ZKN_SORTSEARCH_EFECT_ACT_ANM );
	CLACT_SetDrawFlag( p_draw->sort_act, FALSE );
	CLACT_SetAffineParam( p_draw->sort_act, CLACT_AFFINE_NORMAL );
	CLACT_BGPriorityChg( p_draw->sort_act, 0 );
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
static void ZknSortSearchOamDelete( ZKN_SORTSEARCH_DRAW* p_draw )
{
	CLACT_Delete( p_draw->search_form_act );

	CLACT_Delete( p_draw->sort_act );
}


//----------------------------------------------------------------------------
/**
 *	@brief	���I�𒆂̉�ʂ̐���
 *
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	type			����
 *	@param	heap			˰��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchFontSelectType( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	STRBUF* str;
	int msg_idx;
	
	// �������ޗ̈�N���[��
	GF_BGL_BmpWinFill( &p_draw_glb->bmp_mfont, 0, 
			ZKN_SORTSEARCH_FONT_BG_SELECT_X, ZKN_SORTSEARCH_FONT_BG_SELECT_Y,
			ZKN_SORTSEARCH_FONT_BG_SELECT_AREA_X, ZKN_SORTSEARCH_FONT_BG_SELECT_AREA_Y );

	// ������
	switch( type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		msg_idx = ZNK_SORTSEARCH_TEXT_03;
		break;
	case ZKN_SORTSEARCH_SELECT_NEME:
		msg_idx = ZNK_SORTSEARCH_TEXT_00;
		break;
	case ZKN_SORTSEARCH_SELECT_TYPE:
		msg_idx = ZNK_SORTSEARCH_TEXT_01;
		break;
	case ZKN_SORTSEARCH_SELECT_FORM:
		msg_idx = ZNK_SORTSEARCH_TEXT_02;
		break;
	default:
		break;
	}


	// ���������������
	str = ZKN_UTIL_ZknGmmGet( msg_idx, heap );
	GF_STR_PrintColor( &p_draw_glb->bmp_mfont, FONT_SYSTEM, str, 
			ZKN_SORTSEARCH_FONT_BG_SELECT_X, ZKN_SORTSEARCH_FONT_BG_SELECT_Y,
			0, ZKN_BG_FONT_COLOR_MSK, NULL );

	STRBUF_Delete(str);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ݒ�Ƀq�b�g�����|�P���������Ȃ�����
 *
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	heap			�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchFontNotHitPokemon( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	STRBUF* str;
	
	// �������ޗ̈�N���[��
	GF_BGL_BmpWinFill( &p_draw_glb->bmp_mfont, 0, 
			ZKN_SORTSEARCH_FONT_BG_SELECT_X, ZKN_SORTSEARCH_FONT_BG_SELECT_Y,
			ZKN_SORTSEARCH_FONT_BG_SELECT_AREA_X, ZKN_SORTSEARCH_FONT_BG_SELECT_AREA_Y );


	// ���������������
	str = ZKN_UTIL_ZknGmmGet( ZNK_SORTSEARCH_TEXT_06, heap );
	GF_STR_PrintColor( &p_draw_glb->bmp_mfont, FONT_SYSTEM, str, 
			ZKN_SORTSEARCH_FONT_BG_SELECT_X, ZKN_SORTSEARCH_FONT_BG_SELECT_Y,
			0, ZKN_BG_FONT_COLOR_MSK, NULL );

	STRBUF_Delete(str);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�����̕`�惁�C���֐�
 *
 *	@param	p_draw
 *	@param	p_drawglb
 *	@param	cp_glb
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSelectDraw( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb,  int heap )
{
	// ������ăG���[�`��
	if( cp_glb->sort_err != p_draw->sort_err ){

		p_draw->sort_err = cp_glb->sort_err;
		if( p_draw->sort_err == TRUE ){
			p_draw->sort_err_draw_count = ZKN_SORTSEARCH_ERR_DRAW_COUNT;
			ZknSortSearchFontNotHitPokemon( p_drawglb, heap );
		}
	}
	if( p_draw->sort_err_draw_count > 0 ){		// ���Ԋu���������������
		p_draw->sort_err_draw_count--;
	}else if( p_draw->sort_err_draw_count == 0 ){
		ZknSortSearchFontSelectType( p_drawglb, cp_glb->now_select, heap );
		p_draw->sort_err_draw_count--;
	}

	if( p_draw->now_select != cp_glb->now_select ){
		ZknSortSearchBgSelectType( p_drawglb, cp_glb->now_select, heap );
		ZknSortSearchFontSelectType( p_drawglb, cp_glb->now_select, heap );
		p_draw->now_select =  cp_glb->now_select;
	}

	if( p_draw->sort_type != cp_glb->sort_type ){
		ZKnSortSearchFontSortType( p_drawglb, cp_glb->sort_type, heap );
		p_draw->sort_type =  cp_glb->sort_type;
	}

	if( p_draw->search_name != cp_glb->search_name ){
		ZKnSortSearchFontSearchName( p_drawglb, cp_glb->search_name, heap );
		p_draw->search_name =  cp_glb->search_name;
	}

	if( p_draw->search_type1 != cp_glb->search_type1 ){
		ZKnSortSearchFontSearchType1( p_drawglb, cp_glb->search_type1, heap );
		p_draw->search_type1 =  cp_glb->search_type1;
	}

	if( p_draw->search_type2 != cp_glb->search_type2 ){
		ZKnSortSearchFontSearchType2( p_drawglb, cp_glb->search_type2, heap );
		p_draw->search_type2 =  cp_glb->search_type2;
	}

	if( p_draw->search_form != cp_glb->search_form ){
		ZKnSortSearchOamSearchForm( p_draw, cp_glb->search_form );
		p_draw->search_form =  cp_glb->search_form;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�I�𒆂̍��ڂ�BG��ݒ�
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	type		����
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchBgSelectType( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;
	int x, y;
	int data_idx;

	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_sort_bg_main1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	x = ZKN_SORTSEARCH_BG_X;
	switch( type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		y = ZKN_SORTSEARCH_BG_SORT_Y;
		data_idx = NARC_zukan_zkn_sort_bg_main1_a_lzh_NSCR;
		break;
	case ZKN_SORTSEARCH_SELECT_NEME:
		y = ZKN_SORTSEARCH_BG_NAME_Y;
		data_idx = NARC_zukan_zkn_sort_bg_main1_b_lzh_NSCR;
		break;
	case ZKN_SORTSEARCH_SELECT_TYPE:
		y = ZKN_SORTSEARCH_BG_TYPE_Y;
		data_idx = NARC_zukan_zkn_sort_bg_main1_c_lzh_NSCR;
		break;
	case ZKN_SORTSEARCH_SELECT_FORM:
		y = ZKN_SORTSEARCH_BG_FORM_Y;
		data_idx = NARC_zukan_zkn_sort_bg_main1_d_lzh_NSCR;
		break;
	default:
		break;
	}

	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, data_idx, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
			p_scrn->rawData, x, y,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );


	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	������߂̕����ް���������
 *
 *	@param	p_drawglb	�`��
 *	@param	type		����
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZKnSortSearchFontSortType( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	STRBUF* str;
	int msg_idx;
	
	// �������ޗ̈�N���[��
	GF_BGL_BmpWinFill( &p_draw_glb->bmp_mfont, 0, 
			ZKN_SORTSEARCH_FONT_BG_X, ZKN_SORTSEARCH_FONT_BG_SORT_Y,
			ZKN_SORTSEARCH_FONT_BG_AREA_X, ZKN_SORTSEARCH_FONT_BG_AREA_Y );

	// ������
	msg_idx = ZNK_SORTSEARCH_SORT_00 + type;


	// ���������������
	str = ZKN_UTIL_ZknGmmGet( msg_idx, heap );
	GF_STR_PrintColor( &p_draw_glb->bmp_mfont, FONT_SYSTEM, str, 
			ZKN_SORTSEARCH_FONT_BG_X, ZKN_SORTSEARCH_FONT_BG_SORT_Y,
			0, ZKN_BG_FONT_COLOR2_MSK, NULL );

	STRBUF_Delete(str);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Ȃ܂��T�[�`���ߕ`��
 *
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	type			�T�[�`����
 *	@param	heap			�q�[�v
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZKnSortSearchFontSearchName( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	STRBUF* str;
	int msg_idx;
	int i;
	
	// �������ޗ̈�N���[��
	GF_BGL_BmpWinFill( &p_draw_glb->bmp_mfont, 0, 
			ZKN_SORTSEARCH_FONT_BG_X, ZKN_SORTSEARCH_FONT_BG_NAME_Y,
			ZKN_SORTSEARCH_FONT_BG_AREA_X, ZKN_SORTSEARCH_FONT_BG_AREA_Y );

	// ������
	switch( type ){
	case ZKN_POKELIST_SEARCH_NAME_NONE:
		msg_idx = ZNK_SORTSEARCH_NAME_00;
		break;
	case ZKN_POKELIST_SEARCH_NAME_A:
		msg_idx = ZNK_SORTSEARCH_NAME_01;
		break;
	case ZKN_POKELIST_SEARCH_NAME_KA:
		msg_idx = ZNK_SORTSEARCH_NAME_02;
		break;
	case ZKN_POKELIST_SEARCH_NAME_SA:
		msg_idx = ZNK_SORTSEARCH_NAME_03;
		break;
	case ZKN_POKELIST_SEARCH_NAME_TA:
		msg_idx = ZNK_SORTSEARCH_NAME_04;
		break;
	case ZKN_POKELIST_SEARCH_NAME_NA:
		msg_idx = ZNK_SORTSEARCH_NAME_05;
		break;
	case ZKN_POKELIST_SEARCH_NAME_HA:
		msg_idx = ZNK_SORTSEARCH_NAME_06;
		break;
	case ZKN_POKELIST_SEARCH_NAME_MA:
		msg_idx = ZNK_SORTSEARCH_NAME_07;
		break;
	case ZKN_POKELIST_SEARCH_NAME_RA:
		msg_idx = ZNK_SORTSEARCH_NAME_09;
		break;
	case ZKN_POKELIST_SEARCH_NAME_YAWA:
		msg_idx = ZNK_SORTSEARCH_NAME_08;
		break;
	}


	// ���������������
	str = ZKN_UTIL_ZknGmmGet( msg_idx, heap );


	if( type == 0 ){
		for( i=0; i<ZKN_SORTSEARCH_FONT_BG_NAME_BOU_NUM; i++ ){
			GF_STR_PrintColor( &p_draw_glb->bmp_mfont, FONT_SYSTEM, str, 
					ZKN_SORTSEARCH_FONT_BG_X + (ZKN_SORTSEARCH_FONT_BG_BOU_SIZE_X * i),
					ZKN_SORTSEARCH_FONT_BG_NAME_Y,
					0, ZKN_BG_FONT_COLOR2_MSK, NULL );
		}
	}else{
		GF_STR_PrintColor( &p_draw_glb->bmp_mfont, FONT_SYSTEM, str, 
				ZKN_SORTSEARCH_FONT_BG_X, ZKN_SORTSEARCH_FONT_BG_NAME_Y,
				0, ZKN_BG_FONT_COLOR2_MSK, NULL );
	}

	STRBUF_Delete(str);
}

//----------------------------------------------------------------------------
/**
 *	@brief	���߁@�������ߕ`��		���ʕ���
 *
 *	@param	p_drawglb
 *	@param	type
 *	@param	heap
 *	@param	y 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZKnSortSearchFontSearchType_Core( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap, int y )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	STRBUF* str;
	int msg_idx;
	int i;
	
	// �������ޗ̈�N���[��
	GF_BGL_BmpWinFill( &p_draw_glb->bmp_mfont, 0, 
			ZKN_SORTSEARCH_FONT_BG_X, y,
			ZKN_SORTSEARCH_FONT_BG_AREA_X, ZKN_SORTSEARCH_FONT_BG_AREA_Y );

	// ������
	switch( type ){
	case ZKN_POKELIST_SEARCH_TYPE_NONE:
		msg_idx = ZNK_SORTSEARCH_NAME_00;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_NORMAL:
		msg_idx = ZNK_SORTSEARCH_TYPE_00;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_BATTLE:	
		msg_idx = ZNK_SORTSEARCH_TYPE_06;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_HIKOU:	
		msg_idx = ZNK_SORTSEARCH_TYPE_09;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_POISON:	
		msg_idx = ZNK_SORTSEARCH_TYPE_07;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_JIMEN:	
		msg_idx = ZNK_SORTSEARCH_TYPE_08;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_IWA:		
		msg_idx = ZNK_SORTSEARCH_TYPE_12;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_MUSHI:	
		msg_idx = ZNK_SORTSEARCH_TYPE_11;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_GHOST:	
		msg_idx = ZNK_SORTSEARCH_TYPE_13;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_METAL:	
		msg_idx = ZNK_SORTSEARCH_TYPE_16;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_FIRE:	
		msg_idx = ZNK_SORTSEARCH_TYPE_01;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_WATER:	
		msg_idx = ZNK_SORTSEARCH_TYPE_02;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_KUSA:	
		msg_idx = ZNK_SORTSEARCH_TYPE_04;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_ELECTRIC:
		msg_idx = ZNK_SORTSEARCH_TYPE_03;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_SP:		
		msg_idx = ZNK_SORTSEARCH_TYPE_10;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_KOORI:	
		msg_idx = ZNK_SORTSEARCH_TYPE_05;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_DRAGON:	
		msg_idx = ZNK_SORTSEARCH_TYPE_14;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_AKU:	
		msg_idx = ZNK_SORTSEARCH_TYPE_15;
		break;
	}

	// ���������������
	str = ZKN_UTIL_ZknGmmGet( msg_idx, heap );


	if( type == 0 ){
		for( i=0; i<ZKN_SORTSEARCH_FONT_BG_TYPE_BOU_NUM; i++ ){
			GF_STR_PrintColor( &p_draw_glb->bmp_mfont, FONT_SYSTEM, str, 
					ZKN_SORTSEARCH_FONT_BG_X + (ZKN_SORTSEARCH_FONT_BG_BOU_SIZE_X * i),
					y,
					0, ZKN_BG_FONT_COLOR2_MSK, NULL );
		}
	}else{
		GF_STR_PrintColor( &p_draw_glb->bmp_mfont, FONT_SYSTEM, str, 
				ZKN_SORTSEARCH_FONT_BG_X, y,
				0, ZKN_BG_FONT_COLOR2_MSK, NULL );
	}

	STRBUF_Delete(str);
}


//----------------------------------------------------------------------------
/**
 *	@brief	����1�@�������߂�\��
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	type		����
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZKnSortSearchFontSearchType1( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap )
{
	ZKnSortSearchFontSearchType_Core( p_drawglb, type, heap, ZKN_SORTSEARCH_FONT_BG_TYPE1_Y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	����1�@�������߂�\��
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	type		����
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZKnSortSearchFontSearchType2( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap )
{
	ZKnSortSearchFontSearchType_Core( p_drawglb, type, heap, ZKN_SORTSEARCH_FONT_BG_TYPE2_Y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�������傤�@�������߂�\��
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	type		����
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZKnSortSearchOamSearchForm( ZKN_SORTSEARCH_DRAW* p_draw, int type )
{
	if( type == 0 ){
		CLACT_SetDrawFlag( p_draw->search_form_act, FALSE );
	}else{
		CLACT_SetDrawFlag( p_draw->search_form_act, TRUE );

		switch( type ){
		case ZKN_POKELIST_SEARCH_FORM_FOUR_LEGS:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_FOUR_LEGS );
			break;
		case ZKN_POKELIST_SEARCH_FORM_TWO_LEGS:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_TWO_LEGS );
			break;
		case ZKN_POKELIST_SEARCH_FORM_TAIL:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_TAIL );
			break;
		case ZKN_POKELIST_SEARCH_FORM_HARABAI:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_HARABAI );
			break;
		case ZKN_POKELIST_SEARCH_FORM_FOUR_WING:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_FOUR_WING );
			break;
		case ZKN_POKELIST_SEARCH_FORM_TWO_WING:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_TWO_WING );
			break;
		case ZKN_POKELIST_SEARCH_FORM_HAITSUKUBARI:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_HAITSUKUBARI );
			break;
		case ZKN_POKELIST_SEARCH_FORM_STRAIGHT:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_STRAIGHT );
			break;
		case ZKN_POKELIST_SEARCH_FORM_ARM:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_ARM );
			break;
		case ZKN_POKELIST_SEARCH_FORM_LEGS:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_LEGS );
			break;
		case ZKN_POKELIST_SEARCH_FORM_MANY_LEGS:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_MANY_LEGS );
			break;
		case ZKN_POKELIST_SEARCH_FORM_WATER:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_WATER );
			break;
		case ZKN_POKELIST_SEARCH_FORM_CIRCLE:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_CIRCLE );
			break;
		case ZKN_POKELIST_SEARCH_FORM_COMP:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_COMP );
			break;
		default:
			break;
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	��Ļ���t�F�[�h�V�X�e��
 *	
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���ް�
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchFadeSys( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap )
{
	// �t�F�[�h����������
	if( cp_glb->fade_count == ZKN_SORTSEARCH_FADECOUNT_MAX ){

		if( cp_glb->fade_mode == ZKN_SORTSEARCH_FADEOUT ){
			ZKN_UTIL_BgShutterFadeInit( &p_draw->shutter,
					p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M,
					p_draw->p_scrn, 
					ZKN_POKELIST_BGSHUTTER_FADE00_TOP_S, ZKN_POKELIST_BGSHUTTER_FADE01_TOP_S, 
					ZKN_POKELIST_BGSHUTTER_FADE00_BOTTOM_S, ZKN_POKELIST_BGSHUTTER_FADE01_BOTTOM_S, ZKN_SORTSEARCH_FADECOUNT_MAX );
		}else{
			
			// �t�F�[�h�C���̂Ƃ���FONTBG�ݒ��ύX
			ZknSortSearchSortEffFontReset( p_drawglb, p_draw, heap );
			
			ZKN_UTIL_BgShutterFadeInit( &p_draw->shutter,
					p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M,
					p_draw->p_scrn, 
					ZKN_POKELIST_BGSHUTTER_FADE01_TOP_S, ZKN_POKELIST_BGSHUTTER_FADE00_TOP_S, 
					ZKN_POKELIST_BGSHUTTER_FADE01_BOTTOM_S, ZKN_POKELIST_BGSHUTTER_FADE00_BOTTOM_S, ZKN_SORTSEARCH_FADECOUNT_MAX );
		}
		
	}

	// ����
	ZKN_UTIL_BgShutterFade( &p_draw->shutter );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�������G�t�F�N�g����
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�ް��O���[�o�� 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSortEffSys( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap )
{
	int set_rota;
	int  count;
	
	// ���쏈��������
	if( cp_glb->fade_count == ZKN_SORTSEARCH_DO_MAIN_EFF_COUNT_MAX ){
		
		CLACT_SetDrawFlag( p_draw->sort_act, TRUE );
		// �t�H���gBG�ݒ�
		ZknSortSearchSortEffFontSet( p_drawglb, heap );
		
	}else if( cp_glb->fade_count == 0 ){		// �j������
		
		CLACT_SetDrawFlag( p_draw->sort_act, FALSE );
		// �t�H���gBG�j��
		GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );
	}

	// OAM����]������
	count = ZKN_SORTSEARCH_FADECOUNT_MAX - cp_glb->fade_count;
	set_rota = ZKN_SORTSEARCH_EFECT_OAM_ROTA * count;
	set_rota = set_rota / ZKN_SORTSEARCH_FADECOUNT_MAX;

	CLACT_SetRotation( p_draw->sort_act, (u16)set_rota );
}

//----------------------------------------------------------------------------
/**
 *	@brief	������������\��
 *	
 *	@param	p_drawglb	�`��O���[�o��
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSortEffFontSet( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	STRBUF* str;
	int msg_idx;
	
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );


	// ���������������
	str = ZKN_UTIL_ZknGmmGet( ZNK_SORTSEARCH_MSG_00, heap );
	GF_STR_PrintColor( &p_draw_glb->bmp_mfont, FONT_SYSTEM, str, 
			ZKN_SORTSEARCH_EFECT_FONT_X, ZKN_SORTSEARCH_EFECT_FONT_Y,
			0, ZKN_BG_FONT_COLOR_MSK, NULL );

	STRBUF_Delete(str);

	// �\���D�揇�ʂ�ύX
	GF_BGL_PrioritySet( ZKN_BG_FRM_FONT_M, 0 );
	GF_BGL_PrioritySet( ZKN_BG_FRM_UTIL_M, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gBG�����ɖ߂�
 *
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	cp_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSortEffFontReset( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, ZKN_SORTSEARCH_DRAW* p_draw, int heap )
{
	// �\���D�揇�ʂ�ύX
	GF_BGL_PrioritySet( ZKN_BG_FRM_FONT_M, 1 );
	GF_BGL_PrioritySet( ZKN_BG_FRM_UTIL_M, 0 );

	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );
	ZknSortSearchBgSelectType( p_drawglb, p_draw->now_select, heap );
	ZknSortSearchFontSelectType( p_drawglb, p_draw->now_select, heap );
	ZKnSortSearchFontSortType( p_drawglb, p_draw->sort_type, heap );
	ZKnSortSearchFontSearchName( p_drawglb, p_draw->search_name, heap );
	ZKnSortSearchFontSearchType1( p_drawglb, p_draw->search_type1, heap );
	ZKnSortSearchFontSearchType2( p_drawglb, p_draw->search_type2, heap );
	ZKnSortSearchOamSearchForm( p_draw, p_draw->search_form );
}
