//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_sortsearch_sub.c
 *	@brief		�����\�[�g�T�u��ʃT�u���		���ʕ���
 *	@author		tomoya takahashi 
 *	@data		2006.01.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"

#include "include/system/brightness.h"
#include "include/system/arc_tool.dat"
#include "include/system/arc_util.h"
#include "include/system/clact_util.h"
#include "include/application/zukanlist/zukan.naix"
#include "include/gflib/button_man.h"
#include "include/gflib/calctool.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"
#include "include/application/zukanlist/zkn_snd_def.h"

#include "include/application/zukanlist/zukan.naix"
#include "include/application/zukanlist/zkn_sortsearch.h"

#define	__ZKN_SORTSEARCHSUB_SUB_H_GLOBAL
#include "include/application/zukanlist/zkn_sortsearch_sub.h"

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
#define ZKN_SORTSEARCHSUB_EVENT_NUM ( 0 )	// �C�x���g��


//-------------------------------------
//	�V�[�P���X
//=====================================
enum{
	ZKN_SORTSEARCHSUB_SEQINIT_ALLOC,
	ZKN_SORTSEARCHSUB_SEQINIT_LOAD,
	ZKN_SORTSEARCHSUB_SEQINIT_FADEIN,
	ZKN_SORTSEARCHSUB_SEQINIT_END,
};
enum{
	ZKN_SORTSEARCHSUB_SEQDELETE_FADEOUT_INIT,
	ZKN_SORTSEARCHSUB_SEQDELETE_FADEOUT,
	ZKN_SORTSEARCHSUB_SEQDELETE_RELEASE,
	ZKN_SORTSEARCHSUB_SEQDELETE_FREE,
	ZKN_SORTSEARCHSUB_SEQDELETE_END,
};


//�A�j���V�[�P���X
enum{
	ZKN_SORTSEARCHSUB_MAIN_BUTTON,
	ZKN_SORTSEARCHSUB_ACTION_BUTTON,
	ZKN_SORTSEARCHSUB_SELECT_BUTTON,
	ZKN_SORTSEARCHSUB_RET_BUTTON,
	ZKN_SORTSEARCHSUB_PAGE_SUB_BUTTON,
	ZKN_SORTSEARCHSUB_PAGE_ADD_BUTTON,
	ZKN_SORTSEARCHSUB_FORM_BUTTON,
};
enum{
	// FORM
	ZKN_SORTSEARCHSUB_CIRCLE_BUTTON,
	ZKN_SORTSEARCHSUB_ARM_BUTTON,
	ZKN_SORTSEARCHSUB_LEGS_BUTTON,
	ZKN_SORTSEARCHSUB_MANY_LEGS_BUTTON,
	ZKN_SORTSEARCHSUB_FOURWING_BUTTON,
	ZKN_SORTSEARCHSUB_HARABAI_BUTTON,
	ZKN_SORTSEARCHSUB_STRAIGHT_BUTTON,
	ZKN_SORTSEARCHSUB_HAITSUKUBARI_BUTTON,
	ZKN_SORTSEARCHSUB_COMP_BUTTON,
	ZKN_SORTSEARCHSUB_FOURLEGS_BUTTON,
	ZKN_SORTSEARCHSUB_WATER_BUTTON,
	ZKN_SORTSEARCHSUB_TAIL_BUTTON,
	ZKN_SORTSEARCHSUB_TWO_WING_BUTTON,
	ZKN_SORTSEARCHSUB_TWO_LEGS_BUTTON,
	ZKN_SORTSEARCHSUB_FORM_NONE,
};

// �����t���O�̏�������
#define ZKN_SORTSEARCHSUB_DO_FLAG_INIT ( 0xffff )

//-----------------------------------------------------------------------------
/**
 *		�{�^���J�[�\���ް����ʕ���
 */
//-----------------------------------------------------------------------------
// ���ʈȊO�̃{�^���̍ő吔
#define ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX	( 15 )


// �c���̐�
#define ZKN_SORTSEARCHSUB_BUTTON_Y_NUM		( 6 )


// Y���W�ʒu
#define ZKN_SORTSEARCHSUB_BUTTON_00_Y		( 16 )	
#define ZKN_SORTSEARCHSUB_BUTTON_01_Y		( 48 )	
#define ZKN_SORTSEARCHSUB_BUTTON_02_Y		( 80 )
#define ZKN_SORTSEARCHSUB_BUTTON_03_Y		( 112 )	
#define ZKN_SORTSEARCHSUB_BUTTON_04_Y		( 144 )
#define ZKN_SORTSEARCHSUB_BUTTON_05_Y		( 176 )

// �Ȃ�с@�Ȃ܂��@�����Ջ���X���W
#define ZKN_SORTSEARCHSUB_BUTTONDEF_00_X	( 48 )
#define ZKN_SORTSEARCHSUB_BUTTONDEF_01_X	( 128 )


// �ӂ����OAM�̕�������OFSET
#define ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_2_X		( -12 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X		( -18 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X		( -24 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_5_X		( -30 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_6_X		( -36 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y		( -6 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_PLTOFS	( 3 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_KETTEI_PLTOFS	( 1 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_PUSHPLTOFS	( 5 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_OTHER_PLTOFS	( 0xB )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_OTHER_PUSHPLTOFS	( 6 )

// �J�[�\��Y����
#define ZKN_SORTSEARCHSUB_CURSOR_MAX_Y	( ZKN_SORTSEARCHSUB_BUTTON_Y_NUM )

// ���s�Ɗ�{�{�^���̃T�C�Y
#define ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX	( 80 )
#define ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZY	( 32 )
#define ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX	( 60 )
#define ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY	( 16 )

// ����1������2�̃y�[�W�؂�ւ��{�^���T�C�Y
#define ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZX	( 32 )
#define ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZY	( 32 )
#define ZKN_SORTSEARCHSUB_CURSOR_PAGE_SIZX	( 16 )
#define ZKN_SORTSEARCHSUB_CURSOR_PAGE_SIZY	( 16 )


//-------------------------------------
//	�J�[�\������ID	�J�[�\��ID�͂��Ԃ�Ȃ��悤�ɂ���
//=====================================
enum{
	ZKN_SORTSEARCHSUB_CURSOR_ID_BACK,
	ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI,
	ZKN_SORTSEARCHSUB_CURSOR_ID_NAME,
	ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE,
	ZKN_SORTSEARCHSUB_CURSOR_ID_FORM,
	ZKN_SORTSEARCHSUB_CURSOR_ID_ACTION,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_01,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_02,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_03,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_04,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_05,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_06,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_07,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_08,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_09,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_10,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_11,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_12,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_13,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_14,
	ZKN_SORTSEARCHSUB_SURSOR_ID_NUM,
};

// �J�[�\���̖����Ƃ���ɓ����ID
#define ZKN_SORTSEARCHSUB_CURSOR_ID_NONE	( 0xff )

//-----------------------------------------------------------------------------
/**
 *		���ʕ����{�^���J�[�\���ް�
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�T�u�R�����{�^����
//=====================================
enum{
	ZKN_SORTSEARCHSUB_BUTTON_BACK,
	ZKN_SORTSEARCHSUB_BUTTON_NARABI,
	ZKN_SORTSEARCHSUB_BUTTON_NAME,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE,
	ZKN_SORTSEARCHSUB_BUTTON_FORM,
	ZKN_SORTSEARCHSUB_BUTTON_ACTION,
	ZKN_SORTSEARCHSUB_BUTTON_NUM,
};
#define ZKN_SORTSEARCHSUB_BUTTON_SIZX		( 64 )
#define ZKN_SORTSEARCHSUB_BUTTON_SIZY		( 32 )
#define ZKN_SORTSEARCHSUB_BUTTON_BACK_SIZX		( 48 )
#define ZKN_SORTSEARCHSUB_BUTTON_BACK_SIZY		( 32 )
#define ZKN_SORTSEARCHSUB_BUTTON_X			( 224 )
#define ZKN_SORTSEARCHSUB_BUTTON_ACTION_X	( 212 )
#define ZKN_SORTSEARCHSUB_BUTTON_BACK_X		( 212 )
#define ZKN_SORTSEARCHSUB_BUTTON_BACK_Y		( ZKN_SORTSEARCHSUB_BUTTON_00_Y )	
#define ZKN_SORTSEARCHSUB_BUTTON_NARABI_Y	( ZKN_SORTSEARCHSUB_BUTTON_01_Y )	
#define ZKN_SORTSEARCHSUB_BUTTON_NAME_Y		( ZKN_SORTSEARCHSUB_BUTTON_02_Y )
#define ZKN_SORTSEARCHSUB_BUTTON_TYPE_Y		( ZKN_SORTSEARCHSUB_BUTTON_03_Y )	
#define ZKN_SORTSEARCHSUB_BUTTON_FORM_Y		( ZKN_SORTSEARCHSUB_BUTTON_04_Y )
#define ZKN_SORTSEARCHSUB_BUTTON_ACTION_Y	(ZKN_SORTSEARCHSUB_BUTTON_05_Y  )

// FONTOAM
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CX	( 8 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CY	( 2 )

// �J�[�\��
#define ZKN_SORTSEARCHSUB_CURSOR_SIZX		( 44 )
#define ZKN_SORTSEARCHSUB_CURSOR_SIZY		( 16 )
#define ZKN_SORTSEARCHSUB_CURSOR_BACK_SIZX	( 28 )
#define ZKN_SORTSEARCHSUB_CURSOR_BACK_SIZY	( 16 )



//-----------------------------------------------------------------------------
/**
 *		�Ȃ�щ�ʃ{�^���z�u�ް�
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�T�u�{�^����
//=====================================
enum{
	ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUMBER,
	ZKN_SORTSEARCHSUB_BUTTON_NARABI_AIUEO,
	ZKN_SORTSEARCHSUB_BUTTON_NARABI_HEAVY,
	ZKN_SORTSEARCHSUB_BUTTON_NARABI_LIGHT,
	ZKN_SORTSEARCHSUB_BUTTON_NARABI_TALL,
	ZKN_SORTSEARCHSUB_BUTTON_NARABI_SHORT,
	ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUM,
};

// FONTOAM
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_NARABI_SIZE_CX	( 10 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_NARABI_SIZE_CY	( 2 )

// �J�[�\��
#define ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X	( 3 )

//-----------------------------------------------------------------------------
/**
 *		�Ȃ܂���ʃ{�^���z�u�ް�
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�T�u�{�^����
//=====================================
enum{
	ZKN_SORTSEARCHSUB_BUTTON_NAME_A,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_HA,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_KA,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_MA,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_SA,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_RA,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_TA,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_YAWA,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_NA,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_NONE,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_NUM,
};

// FONTOAM
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_NAME_SIZE_CX	( 10 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_NAME_SIZE_CY	( 2 )

// �J�[�\��
#define ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X	( 3 )


//-----------------------------------------------------------------------------
/**
 *		����1��ʃ{�^���z�u�ް�
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�T�u�{�^����
//=====================================
enum{
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_AKU,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KOORI,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_IWA,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_GHOST,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_SP,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_JIMEN,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_BATTLE,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_ELEC,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KUSA,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_NONE,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_NUM,
};

// FONTOAM
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_TYPE1_SIZE_CX	( 10 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_TYPE1_SIZE_CY	( 2 )

// ���ւ̃{�^���ʒu
#define ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2_X	( ZKN_SORTSEARCHSUB_BUTTONDEF_00_X - 24 )

// �J�[�\��
#define ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X	( 3 )

//-----------------------------------------------------------------------------
/**
 *		����2��ʃ{�^���z�u�ް�
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�T�u�{�^����
//=====================================
enum{
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DOKU,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HIKOR,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DRAGON,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_FIRE,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NORMAL,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_WATER,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HAGANE,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_MUSHI,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NONE,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NUM,
};
// FONTOAM
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_TYPE2_SIZE_CX	( 10 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_TYPE2_SIZE_CY	( 2 )

// ���ւ̃{�^���ʒu
#define ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1_X	( ZKN_SORTSEARCHSUB_BUTTONDEF_00_X - 24 )

// �J�[�\��
#define ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X	( 3 )


//-----------------------------------------------------------------------------
/**
 *		�`��ʃ{�^���z�u�ް�
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�T�u�{�^����
//=====================================
enum{
	ZKN_SORTSEARCHSUB_BUTTON_FORM_CIRCLE,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_HARABAI,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_WATER,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_ARM,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_STRAIGHT,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_TAIL,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_LEGS,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_LEGS,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_WING,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_MANY_LEGS,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_COMP,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_LEGS,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_WING,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_HAITSUKUBARI,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_NONE,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_NUM,
};

#define ZKN_SORTSEARCHSUB_BUTTON_FORM_SIZX		( 48 )
#define ZKN_SORTSEARCHSUB_BUTTON_FORM_SIZY		( 32 )

#define ZKN_SORTSEARCHSUB_BUTTON_FORM_DEF_X			( 28 )
#define ZKN_SORTSEARCHSUB_BUTTON_FORM_OFS_X			( 56 )

// �J�[�\��
#define ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X	( 4 )
#define ZKN_SORTSEARCHSUB_CURSOR_FORM_SIZX		( 32 )
#define ZKN_SORTSEARCHSUB_CURSOR_FORM_SIZY		( 20 )

// �{�^���t�F�[�h���
enum{
	ZKN_SORTSEARCH_SUB_BUTTON_FADE_NONE,
	ZKN_SORTSEARCH_SUB_BUTTON_FADE_IN,
	ZKN_SORTSEARCH_SUB_BUTTON_FADE_OUT,
};
#define ZKN_SORTSEARCHSUB_BUTTON_FADE_SYNC	(2)

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
	ZKN_APL_DATA*		p_main_apl;			// ���C����ʃA�v���f�[�^

	// �����̃A�v���P�[�V�����ް�
	ZKN_APL_DATA*		p_my_apl;			// �`��Ƃ̘A�g�����K�v�����邽��
} ZKN_SORTSEARCHSUB_GLB;

//-------------------------------------
//	�����\�[�g��ʁ@�`��O���[�o���ϐ�
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// �`��O���[�o���f�[�^

	// �{�^���t�F�[�h�p
	int button_fade_req;
	BOOL* button_fade;
} ZKN_SORTSEARCHSUB_DRAWGLB;

//-------------------------------------
//	�{�^���p���[�N
//=====================================
typedef struct {
	void* p_glb;
	void* p_work;
} ZKN_SORTSEARCHSUB_BUTTON_WORK;

//-------------------------------------
//	�����\�[�g��ʁ@�������[�N
//=====================================
typedef struct {
	// �{�^���}�l�[�W��
	BUTTON_MAN* p_button_man;
	TP_HIT_TBL *hit_tbl;	// �{�^���f�[�^
	// �T�u�{�^���}�l�[�W��
	BUTTON_MAN* p_button_man_sub;
	TP_HIT_TBL *hit_tbl_sub;	// �{�^���f�[�^
	ZKN_SORTSEARCHSUB_BUTTON_WORK button_work;


	// �J�[�\���V�X�e��
	ZKN_CURSOR* p_cursor;
	ZKN_CURSOR_ONEDATA* p_cursor_tbl;


	int type_page;			// ���߃y�[�W

	// ���[�N���[�J�����̑I������
	int local_select;	
	int local_type_page;			// ���f�`�F�b�N�p���߃y�[�W

	// �{�^�������ް�
	int button_event[ ZKN_SORTSEARCHSUB_BUTTON_NUM ];	// �{�^���C�x���g�f�[�^
	int button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX ];	// �{�^���C�x���g�f�[�^

	// �������s�ް�
	int do_flag_common;		// �������s�ް�	�����ꂽ�{�^�����ް���i�[
	int do_flag_select;		// �������s�ް������ꂽ�{�^�����ް���i�[

	int type_set_no;		// �ݒ肷���������ް

	BOOL cursor_no_touch;
	BOOL tp_no_touch;
	

	int req_count;	// �������ςȂ����̂Q��ڂ���TRUE������

	// �{�^���t�F�[�h�����҂��t���O
	BOOL button_fade_flag;
} ZKN_SORTSEARCHSUB_WORK;

//-------------------------------------
//	�����\�[�g��ʁ@�`�惏�[�N
//=====================================
typedef struct {
	CLACT_WORK_PTR clact[ ZKN_SORTSEARCHSUB_BUTTON_NUM ];
	ZKN_FONTOAM_DATA* p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_NUM ];

	CLACT_WORK_PTR clact_sub[ ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX ];
	ZKN_FONTOAM_DATA* p_fontoam_sub[ ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX ];
	CLACT_WORK_PTR clact_sub_form[ ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX ];

	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// Resource�I�u�W�F�|�C���^
	CLACT_U_RES_OBJ_PTR res_obj_form[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// Resource�I�u�W�F�|�C���^

	// ���[�N���[�J�����̑I������
	int local_select;	
	int local_type_page;			// ���߃y�[�W


	// �{�^���t�F�[�h����
	ZKN_UTIL_MOVE_WORK fade_work;
	int do_fade;
	int do_fade_seq;
	BOOL* end_flag;
} ZKN_SORTSEARCHSUB_DRAW;

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
static ZKN_SORTSEARCHSUB_GLB* MakeSortSearchSubGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_SORTSEARCHSUB_DRAWGLB* MakeSortSearchSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeSortSearchSubEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteSortSearchSubGlb( ZKN_SORTSEARCHSUB_GLB* p_glb );
static void DeleteSortSearchSubDrawGlb( ZKN_SORTSEARCHSUB_DRAWGLB* p_glb );
static void DeleteSortSearchSubEvent( ZKN_EVENT_DATA* p_event );


static int SortSearchSubEventDataNumGet( void );

//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
static int ZknSortSearchSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSortSearchSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSortSearchSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSortSearchSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknSortSearchSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknSortSearchSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// �t�F�[�h����
static void ZknSortSearchSubSortFadeSys( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_GLB* cp_glb );

// Resource�ǂݍ���
static void ZknSortSearchSubLoadRes( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_GLB* cp_glb, const ZKN_SORTSEARCHSUB_WORK* cp_datawork, int heap );
static void ZknSortSearchSubDeleteRes( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb );
static void ZknSortSearchSubSetUpBg( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_GLB* cp_glb, int heap );
static void ZknSortSearchSubLoadOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap );
static void ZknSortSearchSubReleaseOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb );
static void ZknSortSearchSubLoadOamForm( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap );
static void ZknSortSearchSubReleaseOamForm( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb );


// �{�^���t�F�[�h����
static void ZknSortSearchSubButtonFadeCont( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb );
static void ZknSortSearchSubButtonFade( ZKN_SORTSEARCHSUB_DRAW* p_draw );
static void ZknSortSearchSubButtonFadeOamModeSet_Pack( ZKN_SORTSEARCHSUB_DRAW* p_draw, int mode, int select_type, int type_page );
static void ZknSortSearchSubButtonFadeOamModeSet( ZKN_SORTSEARCHSUB_DRAW* p_draw, int mode );
static void ZknSortSearchSubButtonFadeOamModeSet_Type1Ver( ZKN_SORTSEARCHSUB_DRAW* p_draw, int mode );
static void ZknSortSearchSubButtonFadeOamModeSet_Type2Ver( ZKN_SORTSEARCHSUB_DRAW* p_draw, int mode );

//-----------------------------------------------------------------------------
/**
 *	�Z���A�N�^�[�o�^
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClact( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap );
static void ZknSortSearchSubDeleteClact( ZKN_SORTSEARCHSUB_DRAW* p_draw );
static void ZknSortSearchSubAddSubClact( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add, int select_type, int local_type_page );
static void ZknSortSearchSubChgClact( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap );

// ���ʃ{�^���o�^
static void ZknSortSearchSubAddClactCommon( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add );
static void ZknSortSearchSubDeleteClactCommon( ZKN_SORTSEARCHSUB_DRAW* p_draw );
// �j������
static void ZknSortSearchSubDeleteClactSub( ZKN_SORTSEARCHSUB_DRAW* p_draw );
// ��ĉ�ʓo�^
static void ZknSortSearchSubAddClactSort( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add );
// �Ȃ܂���ʓo�^
static void ZknSortSearchSubAddClactName( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add );
// ����1��ʓo�^
static void ZknSortSearchSubAddClactType1( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add );
// ����2��ʓo�^
static void ZknSortSearchSubAddClactType2( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add );
// �t�H�[����ʓo�^
static void ZknSortSearchSubAddClactForm( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add );
static void ZknSortSearchSubAddClactForm_Gra( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap );
static void ZknSortSearchSubDeleteClactForm_Gra( ZKN_SORTSEARCHSUB_DRAW* p_draw );

//-----------------------------------------------------------------------------
/**
 *	FONTOAM�쐬
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddFontOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap );
static void ZknSortSearchSubDeleteFontOam( ZKN_SORTSEARCHSUB_DRAW* p_draw );
static void ZknSortSearchSubAddSubFontOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys, int select_type, int local_type_page );
static void ZknSortSearchSubChgFontOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap );
// ���ʃ{�^��
static void ZknSortSearchSubAddFontCommon( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys );
static void ZknSortSearchSubDeleteFontCommon( ZKN_SORTSEARCHSUB_DRAW* p_draw );
// �j������
static void ZknSortSearchSubDeleteFontSub( ZKN_SORTSEARCHSUB_DRAW* p_draw );
// ��ă{�^��
static void ZknSortSearchSubAddFontSort( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys );
// ���O�{�^��
static void ZknSortSearchSubAddFontName( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys );
// ����1�{�^��
static void ZknSortSearchSubAddFontType1( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys );
// ����2�{�^��
static void ZknSortSearchSubAddFontType2( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys );

//-----------------------------------------------------------------------------
/**
 *		�{�^������
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonInit( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap );
static void ZknSortSearchSubButtonAllDelete( ZKN_SORTSEARCHSUB_WORK* p_work );
static void ZknSortSearchSubButtonChgMake( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap );
static void ZknSortSearchSubButtonMakeSub( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap, int select_type, int type_page );
static void ZknSortSearchSubButtonMoveAll( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubButtonMoveSub( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int select_type, int type_page );

static void ZknSortSearchSubButtonEventBuffInit( ZKN_SORTSEARCHSUB_WORK* p_work );

//�@���ʃ{�^���p
static void ZknSortSearchSubButtonMake( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap );
static void ZknSortSearchSubButtonMove( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubButtonDelete( ZKN_SORTSEARCHSUB_WORK* p_work );
static void ZknSortSearchSubButtonCallBack( u32 button_no, u32 event, void* p_work );
static void ZknSortSearchSubButtonEventInit( ZKN_SORTSEARCHSUB_WORK* p_work );
static void ZknSortSearchSubButtonSelectEventSet( ZKN_SORTSEARCHSUB_WORK* p_work, int select_type );

// �T�u�{�^���p�j��
static void ZknSortSearchSubButtonSubDelete( ZKN_SORTSEARCHSUB_WORK* p_work );
// �T�u�{�^���C�x���g�z�񏉊���
static void ZknSortSearchSubButtonSubEventInit( ZKN_SORTSEARCHSUB_WORK* p_work );
// �\�[�g���
static void ZknSortSearchSubButtonMakeSort( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap );
static void ZknSortSearchSubButtonMoveSort( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubButtonCallBackSort( u32 button_no, u32 event, void* p_work );
// ���O���
static void ZknSortSearchSubButtonMakeName( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap );
static void ZknSortSearchSubButtonMoveName( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubButtonCallBackName( u32 button_no, u32 event, void* p_work );
// ����1���
static void ZknSortSearchSubButtonMakeType1( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap );
static void ZknSortSearchSubButtonMoveType1( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubButtonCallBackType1( u32 button_no, u32 event, void* p_work );
static void ZknSortSearchSubButtonSelectSetType1( ZKN_SORTSEARCHSUB_WORK* p_work, int type );
// ����2���
static void ZknSortSearchSubButtonMakeType2( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap );
static void ZknSortSearchSubButtonMoveType2( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubButtonCallBackType2( u32 button_no, u32 event, void* p_work );
static void ZknSortSearchSubButtonSelectSetType2( ZKN_SORTSEARCHSUB_WORK* p_work, int type );
// ���������
static void ZknSortSearchSubButtonMakeForm( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap );
static void ZknSortSearchSubButtonMoveForm( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubButtonCallBackForm( u32 button_no, u32 event, void* p_work );

//-----------------------------------------------------------------------------
/**
 *	�J�[�\������
 */
//-----------------------------------------------------------------------------
//�@���ʔj��
static void ZknSortSearchSubCursorDelete( ZKN_SORTSEARCHSUB_WORK* p_work );

// �J�[�\�����실��
static void ZknSortSearchSubCursorMake( ZKN_SORTSEARCHSUB_WORK* p_work, int heap );
static void ZknSortSearchSubCursorMakeSub( ZKN_SORTSEARCHSUB_WORK* p_work, int heap, int select_type, int type_page );
static void ZknSortSearchSubCursorInit( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubCursorMove( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubCursorMoveSub( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int select_type, int type_page );
static void ZknSortSearchSubCursorChg( ZKN_SORTSEARCHSUB_WORK* p_work, int heap );
static void ZknSortSearchSubCursorCommonSet( ZKN_CURSOR_ONEDATA* p_data, int id );
static void ZknSortSearchSubCursorMoveCommon( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );

// ��ĉ��
static void ZknSortSearchSubCursorMakeSort( ZKN_SORTSEARCHSUB_WORK* p_work, int heap );
static void ZknSortSearchSubCursorMoveSort( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
// ���O���
static void ZknSortSearchSubCursorMakeName( ZKN_SORTSEARCHSUB_WORK* p_work, int heap );
static void ZknSortSearchSubCursorMoveName( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
// ����1���
static void ZknSortSearchSubCursorMakeType1( ZKN_SORTSEARCHSUB_WORK* p_work, int heap );
static void ZknSortSearchSubCursorMoveType1( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
// ����2���
static void ZknSortSearchSubCursorMakeType2( ZKN_SORTSEARCHSUB_WORK* p_work, int heap );
static void ZknSortSearchSubCursorMoveType2( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
// �`���
static void ZknSortSearchSubCursorMakeForm( ZKN_SORTSEARCHSUB_WORK* p_work, int heap );
static void ZknSortSearchSubCursorMoveForm( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );

// �`�揈��
static void ZknSortSearchSubCursorDrawInit( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_WORK* cp_work, const ZKN_SORTSEARCHSUB_GLB* cp_glb );
static void ZknSortSearchSubCursorDrawPack( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_WORK* cp_work, const ZKN_SORTSEARCHSUB_GLB* cp_glb );
static void ZknSortSearchSubCursorDraw( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_WORK* cp_work );
static BOOL ZknSortSearchSubCursorOnOff( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb,  BOOL flag );


//-----------------------------------------------------------------------------
/**
 *		���s����
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoInit( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubDoMain( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubDoSelect( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int select_type, int type_page );

// ���ʃ{�^���̎��s
static void ZknSortSearchSubDoCommon( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
// ��ă{�^���̎��s
static void ZknSortSearchSubDoSort( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
// ���O�{�^���̎��s
static void ZknSortSearchSubDoName( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
// ����1�{�^���̎��s
static void ZknSortSearchSubDoType1( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
// ����2�{�^���̎��s
static void ZknSortSearchSubDoType2( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubDoTypeSetCommon( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int set_num );
// �`�{�^���̎��s
static void ZknSortSearchSubDoForm( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );


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
void ZKN_SortSearchSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_SORTSEARCHSUB_GLB*	p_glb;
	ZKN_SORTSEARCHSUB_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeSortSearchSubGlb( heap, zkn_sys );
	p_drawglb = MakeSortSearchSubDrawGlb( heap, zkn_sys );
	p_event = MakeSortSearchSubEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= SortSearchSubEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknSortSearchSubProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknSortSearchSubProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknSortSearchSubProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknSortSearchSubProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknSortSearchSubProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknSortSearchSubProcDrawFuncDelete;
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
void ZKN_SortSearchSubAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteSortSearchSubGlb( p_data->p_glb_data ); 
	DeleteSortSearchSubDrawGlb( p_data->p_glb_draw ); 
	DeleteSortSearchSubEvent( p_data->p_event_data );
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
static ZKN_SORTSEARCHSUB_GLB* MakeSortSearchSubGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_SORTSEARCHSUB_GLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_SORTSEARCHSUB_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_SORTSEARCHSUB_GLB) );

	// main��ʂ���̃C�x���g�L�[
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrMain( zkn_sys ); 

	// �O���[�o���f�[�^
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );


	// ���C����ʃA�v���ް�
	p_glb->p_main_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_SORTSEARCH );

	// �����̃A�v���ް�
	p_glb->p_my_apl = ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_SORTSEARCH );
	
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
static ZKN_SORTSEARCHSUB_DRAWGLB* MakeSortSearchSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_SORTSEARCHSUB_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_SORTSEARCHSUB_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_SORTSEARCHSUB_DRAWGLB) );

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
static ZKN_EVENT_DATA* MakeSortSearchSubEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	return NULL;
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
static void DeleteSortSearchSubGlb( ZKN_SORTSEARCHSUB_GLB* p_glb )
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
static void DeleteSortSearchSubDrawGlb( ZKN_SORTSEARCHSUB_DRAWGLB* p_glb )
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
static void DeleteSortSearchSubEvent( ZKN_EVENT_DATA* p_event )
{
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
static int SortSearchSubEventDataNumGet( void )
{
	return ZKN_SORTSEARCHSUB_EVENT_NUM;
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
static int ZknSortSearchSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SORTSEARCHSUB_GLB* p_glb = p_glbdata;
	ZKN_SORTSEARCHSUB_WORK* p_work;
	int i;

	// ���[�N�쐬
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_SORTSEARCHSUB_WORK) );
	GF_ASSERT( p_work );
	memset( p_work, 0, sizeof(ZKN_SORTSEARCHSUB_WORK) );
	p_dodata->p_work = p_work;


	// ���򏈗�������
	p_work->do_flag_common = ZKN_SORTSEARCHSUB_DO_FLAG_INIT;
	ZknSortSearchSubDoInit( p_work, p_glb );


	// �{�^���J�[�\�����쐬
	ZknSortSearchSubButtonInit( p_work, p_glb, p_dodata->heap );
	ZknSortSearchSubCursorMake( p_work, p_dodata->heap );
	ZknSortSearchSubCursorInit( p_work, p_glb );


	// �{�^���C�x���g�f�[�^
	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_NUM; i++ ){
		p_work->button_event[ i ] = ZKN_UTIL_BUTTON_PUSH_NONE;	// �{�^���C�x���g�f�[�^
	}
	
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
static int ZknSortSearchSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SORTSEARCHSUB_GLB* p_glb = p_glbdata;
	ZKN_SORTSEARCHSUB_WORK*	p_work = p_dodata->p_work;
	ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb = p_glb->p_my_apl->p_glb_draw;
	int select_type;
	int old_local_select;
	
	// �I����
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}


	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	// �t�F�[�h�������͓���֎~�I�I
	if( ZKN_SortSearchAplFadeModeGet( p_glb->p_main_apl ) != ZKN_SORTSEARCH_FADENONE ){
		return ZKN_PROC_FALSE;
	}

	select_type = ZKN_SortSearchAplSelectTypeGet( p_glb->p_main_apl );
	
	switch( p_dodata->seq ){
	// ���쏈��
	case 0:	

		// �I�����ߕ���
		if( (p_work->local_select != select_type) ||
			(p_work->local_type_page != p_work->type_page ) ){

			// �{�^���t�F�[�h���N�G�X�g
			p_work->button_fade_flag = FALSE;
			p_drawglb->button_fade_req = ZKN_SORTSEARCH_SUB_BUTTON_FADE_OUT;
			p_drawglb->button_fade = &p_work->button_fade_flag;

			// �{�^���C�x���g��������
			ZknSortSearchSubButtonEventInit( p_work );
			// �`��̂��߂Ƀ{�^���C�x���g�̒l��ݒ�
			ZknSortSearchSubButtonSelectEventSet( p_work, select_type );


			// �{�^������ύX��
			p_dodata->seq++;
			break;
		}

		// �{�^������
		ZknSortSearchSubButtonMoveAll( p_work, p_glb );

		// �J�[�\������
		if( (ZKN_GLBDATA_TouchCursorFlagGet( p_glb->p_glb ) == TRUE) ){

			ZknSortSearchSubCursorMove( p_work, p_glb );
		}


		// ���상�C��
		ZknSortSearchSubDoMain( p_work, p_glb );
		break;

	// �{�^���t�F�[�h�A�E�g�҂�
	case 1:
		if( p_work->button_fade_flag ){
			p_dodata->seq ++;

		}
		break;

	// �{�^���ύX
	case 2:
		old_local_select = p_work->local_select;	// �J�[�\���ʒu�������̂��ߕۑ�
		p_work->local_select = select_type;
		p_work->local_type_page = p_work->type_page;
		
		ZknSortSearchSubButtonChgMake( p_work, p_glb, p_dodata->heap );
		ZknSortSearchSubCursorChg( p_work, p_dodata->heap );
		ZknSortSearchSubDoInit( p_work, p_glb );

		// �I�����߂̕ύX���������Ƃ��̂݃J�[�\���ʒu��������
		if( old_local_select != p_work->local_select ){
			ZknSortSearchSubCursorInit( p_work, p_glb );
		}

		// �{�^���t�F�[�h���N�G�X�g
		p_work->button_fade_flag = FALSE;
		p_drawglb->button_fade_req = ZKN_SORTSEARCH_SUB_BUTTON_FADE_IN;
		p_drawglb->button_fade = &p_work->button_fade_flag;


		// �T�u�{�^��������
		ZknSortSearchSubButtonSubEventInit( p_work );
		
		p_dodata->seq++;
		break;

	// �{�^���t�F�[�h�C���҂�
	case 3:
		if( p_work->button_fade_flag ){
			p_dodata->seq ++;
		}
		break;

	// ���C�����쏈���ɖ߂�
	case 4:
		p_dodata->seq = 0;
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
static int ZknSortSearchSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SORTSEARCHSUB_WORK* p_work = p_dodata->p_work;

	// �{�^���J�[�\���j��
	ZknSortSearchSubButtonAllDelete( p_work );
	ZknSortSearchSubCursorDelete( p_work );

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
static int ZknSortSearchSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SORTSEARCHSUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SORTSEARCHSUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SORTSEARCHSUB_DRAW* p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_SORTSEARCHSUB_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_SORTSEARCHSUB_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_SORTSEARCHSUB_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_SORTSEARCHSUB_SEQINIT_LOAD:
		ZknSortSearchSubLoadRes( p_drawwork, p_drawglb, cp_dataglb, cp_datawork, p_drawdata->heap );
		
		// �t�F�[�h������
		ChangeBrightnessRequest( ZKN_FADE_SYNC_COMMON,
				BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_SUB_DISPLAY );

		// �J�[�\���`�揉����
		ZknSortSearchSubCursorDrawInit( p_drawglb, cp_datawork, cp_dataglb );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_SORTSEARCHSUB_SEQINIT_FADEIN:
		// �t�F�[�h
		if( IsFinishedBrightnessChg( MASK_SUB_DISPLAY  ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_SORTSEARCHSUB_SEQINIT_END:
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
static int ZknSortSearchSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SORTSEARCHSUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SORTSEARCHSUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SORTSEARCHSUB_DRAW* p_drawwork = p_drawdata->p_work;
	int i;
	int old_select;
	int old_type_page;
	int pltt_ofs;


	if( ZKN_SortSearchAplFadeModeGet( cp_dataglb->p_main_apl ) != ZKN_SORTSEARCH_FADENONE ){

		// �t�F�[�h�V�X�e��
		ZknSortSearchSubSortFadeSys( p_drawwork, p_drawglb, cp_dataglb );


	}else{

		// �t�F�[�h�C���A�E�g����
		ZknSortSearchSubButtonFadeCont( p_drawwork, p_drawglb );

		// �A�N�^�[�@�t�H���gOAM�̕ύX����
		if( (p_drawwork->local_select != cp_datawork->local_select) || 
			(p_drawwork->local_type_page != cp_datawork->local_type_page) ){
			old_select = p_drawwork->local_select;
			old_type_page = p_drawwork->local_type_page;

			p_drawwork->local_select = cp_datawork->local_select;
			p_drawwork->local_type_page = cp_datawork->local_type_page;

			// ����old_select���`��̂Ƃ��̓��\�[�X�j��
			if( old_select == ZKN_SORTSEARCH_SELECT_FORM ){
				ZknSortSearchSubReleaseOamForm( p_drawwork, p_drawglb );
				ZknSortSearchSubDeleteClactForm_Gra( p_drawwork );
			}

			ZknSortSearchSubChgClact( p_drawwork, p_drawglb, p_drawdata->heap );
			ZknSortSearchSubChgFontOam( p_drawwork, p_drawglb, p_drawdata->heap );

			// �����`��̂Ƃ��̓��\�[�X�ǂݍ���
			if( p_drawwork->local_select == ZKN_SORTSEARCH_SELECT_FORM ){
				ZknSortSearchSubLoadOamForm( p_drawwork, p_drawglb, p_drawdata->heap );
				ZknSortSearchSubAddClactForm_Gra( p_drawwork, p_drawglb, p_drawdata->heap );
			} 

			// OAM�𔼓����ݒ�
			ZknSortSearchSubButtonFadeOamModeSet_Pack( p_drawwork, GX_OAM_MODE_XLU, p_drawwork->local_select, p_drawwork->local_type_page );
		}
		
		// �J�[�\������
		ZknSortSearchSubCursorDrawPack( p_drawglb, cp_datawork, cp_dataglb );
	}

	// �{�^������
	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_NUM; i++ ){
		ZKN_UTIL_ButtonMove( p_drawwork->clact[ i ],
				cp_datawork->button_event[ i ] );

		// �{�^���t�H���g�A�j��
		if( p_drawwork->p_fontoam[ i ] ){
			if( i==ZKN_SORTSEARCHSUB_BUTTON_ACTION ){
				pltt_ofs = ZKN_SORTSEARCHSUB_BUTTONFONT_KETTEI_PLTOFS;		
			}else{
				pltt_ofs = ZKN_SORTSEARCHSUB_BUTTONFONT_PLTOFS;	
			}
			ZKN_UTIL_ButtonFontMove_Col( p_drawwork->clact[ i ],
					p_drawwork->p_fontoam[ i ],
					ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y,
					pltt_ofs,
					ZKN_SORTSEARCHSUB_BUTTONFONT_PUSHPLTOFS );
		}
	}

	// �T�u�{�^������
	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		if( p_drawwork->clact_sub[ i ] ){
			ZKN_UTIL_ButtonMove( p_drawwork->clact_sub[ i ],
					cp_datawork->button_event_sub[ i ] );
		}

		// �{�^���t�H���g�A�j��
		if( p_drawwork->p_fontoam_sub[ i ] ){
			ZKN_UTIL_ButtonFontMove_Col( p_drawwork->clact_sub[ i ],
					p_drawwork->p_fontoam_sub[ i ],
					ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y,
					ZKN_SORTSEARCHSUB_BUTTONFONT_OTHER_PLTOFS,
					ZKN_SORTSEARCHSUB_BUTTONFONT_OTHER_PUSHPLTOFS );
		}

		// �`��{�^��
		if( p_drawwork->clact_sub_form[i] ){
			ZKN_UTIL_ButtonMove( p_drawwork->clact_sub_form[ i ],
					cp_datawork->button_event_sub[ i ] );
		}
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
static int ZknSortSearchSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SORTSEARCHSUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SORTSEARCHSUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SORTSEARCHSUB_DRAW* p_drawwork = p_drawdata->p_work;
	BOOL check;


	switch( p_drawdata->seq ){
	case ZKN_SORTSEARCHSUB_SEQDELETE_FADEOUT_INIT:

		if( ZKN_SortSearchAplSortDoFlagGet( cp_dataglb->p_main_apl ) == TRUE ){
			p_drawdata->seq = ZKN_SORTSEARCHSUB_SEQDELETE_RELEASE;
		}else{
		
			ChangeBrightnessRequest( COMM_BRIGHTNESS_SYNC, 
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, PLANEMASK_ALL, MASK_SUB_DISPLAY );
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_SORTSEARCHSUB_SEQDELETE_FADEOUT:
		if( IsFinishedBrightnessChg( MASK_SUB_DISPLAY  ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_SORTSEARCHSUB_SEQDELETE_RELEASE:
		
		ZknSortSearchSubDeleteRes( p_drawwork, p_drawglb );

		// �����`��̂Ƃ��̓��\�[�X�j��
		if( p_drawwork->local_select == ZKN_SORTSEARCH_SELECT_FORM ){
			ZknSortSearchSubReleaseOamForm( p_drawwork, p_drawglb );
			ZknSortSearchSubDeleteClactForm_Gra( p_drawwork );
		}
		
		p_drawdata->seq++;
		break;
		
	case ZKN_SORTSEARCHSUB_SEQDELETE_FREE:

		sys_FreeMemoryEz(p_drawdata->p_work);
		p_drawdata->p_work = NULL;
		p_drawdata->seq++;
		break;
		
		
	case ZKN_SORTSEARCHSUB_SEQDELETE_END:
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
static void ZknSortSearchSubLoadRes( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_GLB* cp_glb, const ZKN_SORTSEARCHSUB_WORK* cp_datawork, int heap )
{
	// BG�ݒ�
	ZknSortSearchSubSetUpBg( p_drawglb, cp_glb, heap );

	// ���\�[�X�ǂݍ���
	ZknSortSearchSubLoadOam( p_draw, p_drawglb, heap );

	// OAM�o�^
	ZknSortSearchSubAddClact( p_draw, p_drawglb, heap );


	// FONTOAM
	ZknSortSearchSubAddFontOam( p_draw, p_drawglb, heap );

	// OAM�𔼓����ݒ�
	ZknSortSearchSubButtonFadeOamModeSet_Pack( p_draw, GX_OAM_MODE_XLU, p_draw->local_select, p_draw->local_type_page );

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
static void ZknSortSearchSubDeleteRes( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb )
{
	// FOMTOAM	
	ZknSortSearchSubDeleteFontOam( p_draw );

	// OAM
	ZknSortSearchSubDeleteClact( p_draw );

	// OAM���\�[�X
	ZknSortSearchSubReleaseOam( p_draw, p_drawglb );

	// �J�[�\���\����OFF
	ZKN_UTIL_CursorSetDrawFlag( &p_drawglb->p_drawglb->cursor, FALSE );
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
static void ZknSortSearchSubSetUpBg( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_GLB* cp_glb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// �L�����N�^�f�[�^�]
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_list_sub_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S, 0, 0, TRUE, heap );
	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_sort_bg_sub2_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S );
}



//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���ް��������쐬
 *
 *	@param	p_work		�ް����[�N
 *	@param	p_glb		�ް��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonInit( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap )
{
	// ���ʃ{�^���쐬
	ZknSortSearchSubButtonMake( p_work, p_glb, heap );

	// �T�u�ʃ{�^���쐬
	ZknSortSearchSubButtonMakeSub( p_work, p_glb, heap, p_work->local_select, p_work->local_type_page );

	// �{�^���C�x���g�o�b�t�@������
	ZknSortSearchSubButtonEventBuffInit( p_work );
}
// �{�^���C�x���g�o�b�t�@������
static void ZknSortSearchSubButtonEventBuffInit( ZKN_SORTSEARCHSUB_WORK* p_work )
{
	int i;
	
	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_NUM; i++ ){
		p_work->button_event[ i ] = BMN_EVENT_SLIDEOUT;
	}

	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		p_work->button_event_sub[ i ] = BMN_EVENT_SLIDEOUT;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�S�{�^���ް��j��
 *
 *	@param	p_work	�ް����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonAllDelete( ZKN_SORTSEARCHSUB_WORK* p_work )
{
	// ���ʃ{�^��
	ZknSortSearchSubButtonDelete( p_work );

	// �T�u�ʃ{�^��
	ZknSortSearchSubButtonSubDelete( p_work );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u�ʃ{�^���ް��̕ύX
 *
 *	@param	p_work	�ް����[�N
 *	@param	p_glb	�ް��O���[�o��
 *	@param	heap	�q�[�v 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonChgMake( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap )
{
	// ���܂ł̂�j��
	ZknSortSearchSubButtonSubDelete( p_work );


	// �č쐬
	ZknSortSearchSubButtonMakeSub( p_work, p_glb, heap, p_work->local_select, p_work->local_type_page );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u�ʃ{�^���쐬
 *
 *	@param	p_work		�ް����[�N
 *	@param	p_glb		�ް��O���[�o��
 *	@param	heap		�q�[�v
 *	@param	select_type	�I������
 *	@param	type_page	���߃y�[�W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMakeSub( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap, int select_type, int type_page )
{
	switch( select_type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		ZknSortSearchSubButtonMakeSort( p_work, p_glb, heap );
		break;
		
	case ZKN_SORTSEARCH_SELECT_NEME:
		ZknSortSearchSubButtonMakeName( p_work, p_glb, heap );
		break;
		
	case ZKN_SORTSEARCH_SELECT_TYPE:
		if( type_page == 0 ){
			ZknSortSearchSubButtonMakeType1( p_work, p_glb, heap );
		}else{
			ZknSortSearchSubButtonMakeType2( p_work, p_glb, heap );
		}
		break;
		
	case ZKN_SORTSEARCH_SELECT_FORM:
		ZknSortSearchSubButtonMakeForm( p_work, p_glb, heap );
		break;
		
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���̓���
 *
 *	@param	p_work	�ް����[�N
 *	@param	p_glb	�ް��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMoveAll( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	// ���ʃ{�^������
	ZknSortSearchSubButtonMove( p_work, p_glb );


	//�@�I�����ߕʓ���
	ZknSortSearchSubButtonMoveSub( p_work, p_glb, p_work->local_select, p_work->local_type_page );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u�ʃ{�^������
 *
 *	@param	p_work			�ް����[�N
 *	@param	p_glb			�ް��O���[�o��
 *	@param	select_type		�I������
 *	@param	type_page		���߃y�[�W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMoveSub( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int select_type, int type_page )
{
	switch( select_type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		ZknSortSearchSubButtonMoveSort( p_work, p_glb );
		break;
		
	case ZKN_SORTSEARCH_SELECT_NEME:
		ZknSortSearchSubButtonMoveName( p_work, p_glb );
		break;
		
	case ZKN_SORTSEARCH_SELECT_TYPE:
		if( type_page == 0 ){
			ZknSortSearchSubButtonMoveType1( p_work, p_glb );
		}else{
			ZknSortSearchSubButtonMoveType2( p_work, p_glb );
		}
		break;
		
	case ZKN_SORTSEARCH_SELECT_FORM:
		ZknSortSearchSubButtonMoveForm( p_work, p_glb );
		break;
		
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���^�b�`�f�[�^�쐬
 *
 *	@param	p_work	���[�N
 *	@param	p_glb	�O���[�o���f�[�^
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMake( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap )
{
	// �e�[�u���쐬
	p_work->hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_SORTSEARCHSUB_BUTTON_NUM );

	// �e�[�u���f�[�^�ݒ�
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_SORTSEARCHSUB_BUTTON_NARABI ],
			ZKN_SORTSEARCHSUB_BUTTON_NARABI_Y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_NARABI_Y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_X - (ZKN_SORTSEARCHSUB_BUTTON_SIZX/2),
			ZKN_SORTSEARCHSUB_BUTTON_X + (ZKN_SORTSEARCHSUB_BUTTON_SIZX/2) );
	
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_SORTSEARCHSUB_BUTTON_BACK ],
			ZKN_SORTSEARCHSUB_BUTTON_BACK_Y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_BACK_Y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_BACK_X - (ZKN_SORTSEARCHSUB_BUTTON_BACK_SIZX/2),
			ZKN_SORTSEARCHSUB_BUTTON_BACK_X + (ZKN_SORTSEARCHSUB_BUTTON_BACK_SIZX/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_SORTSEARCHSUB_BUTTON_NAME ],
			ZKN_SORTSEARCHSUB_BUTTON_NAME_Y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_NAME_Y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_X - (ZKN_SORTSEARCHSUB_BUTTON_SIZX/2),
			ZKN_SORTSEARCHSUB_BUTTON_X + (ZKN_SORTSEARCHSUB_BUTTON_SIZX/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_SORTSEARCHSUB_BUTTON_TYPE ],
			ZKN_SORTSEARCHSUB_BUTTON_TYPE_Y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_TYPE_Y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_X - (ZKN_SORTSEARCHSUB_BUTTON_SIZX/2),
			ZKN_SORTSEARCHSUB_BUTTON_X + (ZKN_SORTSEARCHSUB_BUTTON_SIZX/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_SORTSEARCHSUB_BUTTON_FORM ],
			ZKN_SORTSEARCHSUB_BUTTON_FORM_Y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_FORM_Y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_X - (ZKN_SORTSEARCHSUB_BUTTON_SIZX/2),
			ZKN_SORTSEARCHSUB_BUTTON_X + (ZKN_SORTSEARCHSUB_BUTTON_SIZX/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_SORTSEARCHSUB_BUTTON_ACTION ],
			ZKN_SORTSEARCHSUB_BUTTON_ACTION_Y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_ACTION_Y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_ACTION_X - (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2),
			ZKN_SORTSEARCHSUB_BUTTON_ACTION_X + (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2) );

	p_work->button_work.p_glb = p_glb;
	p_work->button_work.p_work = p_work;

	// �{�^���}�l�[�W���쐬
	p_work->p_button_man = BMN_Create( 
			p_work->hit_tbl,
			ZKN_SORTSEARCHSUB_BUTTON_NUM,
			ZknSortSearchSubButtonCallBack,
			&p_work->button_work,
			heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^������
 *
 *	@param	p_work	���[�N
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMove( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	// �{�^���C�x���g������
	ZknSortSearchSubButtonEventInit( p_work );
	
	BMN_Main( p_work->p_button_man );

	// ���I�𒆂̍��ڂ̃{�^���͉������ςȂ�
	ZknSortSearchSubButtonSelectEventSet( p_work, p_work->local_select );
}

// �C�x���g����
static void ZknSortSearchSubButtonEventInit( ZKN_SORTSEARCHSUB_WORK* p_work )
{
	int i;
	
	// �����ꂽ��S�Ẵ{�^�������̊G�ɖ߂�
	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_NUM; i++ ){
		p_work->button_event[ i ] = BMN_EVENT_SLIDEOUT;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���̃Z���N�g���ߐݒ�
 *
 *	@param	p_work 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonSelectEventSet( ZKN_SORTSEARCHSUB_WORK* p_work, int select_type )
{
	switch( select_type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		if( p_work->button_event[ ZKN_SORTSEARCHSUB_BUTTON_NARABI ] != BMN_EVENT_HOLD ){
			p_work->button_event[ ZKN_SORTSEARCHSUB_BUTTON_NARABI ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_SORTSEARCH_SELECT_NEME:
		if( p_work->button_event[ ZKN_SORTSEARCHSUB_BUTTON_NAME ] != BMN_EVENT_HOLD ){
			p_work->button_event[ ZKN_SORTSEARCHSUB_BUTTON_NAME ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_SORTSEARCH_SELECT_TYPE:
		if( p_work->button_event[ ZKN_SORTSEARCHSUB_BUTTON_TYPE ] != BMN_EVENT_HOLD ){
			p_work->button_event[ ZKN_SORTSEARCHSUB_BUTTON_TYPE ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_SORTSEARCH_SELECT_FORM:
		if( p_work->button_event[ ZKN_SORTSEARCHSUB_BUTTON_FORM ] != BMN_EVENT_HOLD ){
			p_work->button_event[ ZKN_SORTSEARCHSUB_BUTTON_FORM ] = BMN_EVENT_RELEASE;
		}
		break;
	default:
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���j��
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonDelete( ZKN_SORTSEARCHSUB_WORK* p_work )
{
	BMN_Delete( p_work->p_button_man );

	// �e�[�u�����[�N�j��
	sys_FreeMemoryEz( p_work->hit_tbl );
	p_work->hit_tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���C�x���g�R�[���o�b�N
 *
 *	@param	button_no	�{�^���i���o�[
 *	@param	event		�C�x���g�^�C�v
 *	@param	p_work		���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_SORTSEARCHSUB_BUTTON_WORK* p_button_work = p_work;
	ZKN_SORTSEARCHSUB_GLB* p_glb = p_button_work->p_glb;
	ZKN_SORTSEARCHSUB_WORK* p_subwork = p_button_work->p_work;

	// �{�^���C�x���g�i�[
	p_subwork->button_event[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_HOLD:
		p_subwork->do_flag_common = button_no;
		p_subwork->req_count ++;
		break;

	default:
		p_subwork->req_count = 0;
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u�{�^���p�j��
 *
 *	@param	p_work
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonSubDelete( ZKN_SORTSEARCHSUB_WORK* p_work )
{
	BMN_Delete( p_work->p_button_man_sub );

	// �e�[�u�����[�N�j��
	sys_FreeMemoryEz( p_work->hit_tbl_sub );
	p_work->hit_tbl_sub = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u�{�^���C�x���g������
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonSubEventInit( ZKN_SORTSEARCHSUB_WORK* p_work )
{
	int i;
	
	// �����ꂽ��S�Ẵ{�^�������̊G�ɖ߂�
	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		p_work->button_event_sub[ i ] = BMN_EVENT_SLIDEOUT;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�\�[�g���
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMakeSort( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap )
{
	int i, j;
	int x, y;
	// �e�[�u���쐬
	p_work->hit_tbl_sub = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUM );


	// �e���W��OAM���쐬����
	for( i=0; i<3; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_01_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		for( j=0; j<2; j++ ){
			x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));

			// �e�[�u���f�[�^�ݒ�
			ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl_sub[ (i*2)+j ],
					y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
					y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
					x - (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2),
					x + (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2) );
		}
	}
	

	p_work->button_work.p_glb = p_glb;
	p_work->button_work.p_work = p_work;

	// �{�^���}�l�[�W���쐬
	p_work->p_button_man_sub = BMN_Create( 
			p_work->hit_tbl_sub,
			ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUM,
			ZknSortSearchSubButtonCallBackSort,
			&p_work->button_work,
			heap );
}
static void ZknSortSearchSubButtonMoveSort( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int i;
	
	// �����ꂽ��S�Ẵ{�^�������̊G�ɖ߂�
	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUM; i++ ){
		p_work->button_event_sub[ i ] = BMN_EVENT_SLIDEOUT;
	}
	
	BMN_Main( p_work->p_button_man_sub );

	// ���I�𒆂̃{�^�����������ςȂ��ɂ���
	switch( ZKN_SortSearchAplSortTypeGet( p_glb->p_main_apl ) ){
	case ZKN_POKELIST_SORT_NORMAL:		// �|�P�����i���o�[
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUMBER ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUMBER ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SORT_GOZYUUON:		// �܏\��
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_AIUEO ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_AIUEO ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SORT_GRAM_L:		// �d��
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_HEAVY ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_HEAVY ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SORT_GRAM_S:		// �y��
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_LIGHT ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_LIGHT ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SORT_HIGH_L:		// ����
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_TALL ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_TALL ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELSIT_SOTT_HIGH_S:		// �Ⴂ
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_SHORT ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_SHORT ] = BMN_EVENT_RELEASE;
		}
		break;
	}
}
static void ZknSortSearchSubButtonCallBackSort( u32 button_no, u32 event, void* p_work )
{
	ZKN_SORTSEARCHSUB_BUTTON_WORK* p_button_work = p_work;
	ZKN_SORTSEARCHSUB_GLB* p_glb = p_button_work->p_glb;
	ZKN_SORTSEARCHSUB_WORK* p_subwork = p_button_work->p_work;

	// �{�^���C�x���g�i�[
	p_subwork->button_event_sub[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_HOLD:
		p_subwork->do_flag_select = button_no;
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���O���
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMakeName( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap )
{
	int i, j;
	int x, y;
	// �e�[�u���쐬
	p_work->hit_tbl_sub = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_SORTSEARCHSUB_BUTTON_NAME_NUM );

	// �e���W��OAM���쐬����
	for( i=0; i<5; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		for( j=0; j<2; j++ ){
			x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));

			// �e�[�u���f�[�^�ݒ�
			ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl_sub[ (i*2)+j ],
					y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
					y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
					x - (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2),
					x + (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2) );
		}
	}

	p_work->button_work.p_glb = p_glb;
	p_work->button_work.p_work = p_work;

	// �{�^���}�l�[�W���쐬
	p_work->p_button_man_sub = BMN_Create( 
			p_work->hit_tbl_sub,
			ZKN_SORTSEARCHSUB_BUTTON_NAME_NUM,
			ZknSortSearchSubButtonCallBackName,
			&p_work->button_work,
			heap );
}
static void ZknSortSearchSubButtonMoveName( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int i;
	
	// �����ꂽ��S�Ẵ{�^�������̊G�ɖ߂�
	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_NAME_NUM; i++ ){
		p_work->button_event_sub[ i ] = BMN_EVENT_SLIDEOUT;
	}
	
	BMN_Main( p_work->p_button_man_sub );

	switch( ZKN_SortSearchAplNameTypeGet( p_glb->p_main_apl ) ){
	case ZKN_POKELIST_SEARCH_NAME_A:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_A ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_A ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SEARCH_NAME_KA:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_KA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_KA ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SEARCH_NAME_SA:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_SA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_SA ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SEARCH_NAME_TA:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_TA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_TA ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SEARCH_NAME_NA:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_NA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_NA ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SEARCH_NAME_HA:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_HA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_HA ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SEARCH_NAME_MA:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_MA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_MA ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SEARCH_NAME_RA:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_RA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_RA ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SEARCH_NAME_YAWA:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_YAWA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_YAWA ] = BMN_EVENT_RELEASE;
		}
		break;

	default:
		break;
	}
}
static void ZknSortSearchSubButtonCallBackName( u32 button_no, u32 event, void* p_work )
{
	ZKN_SORTSEARCHSUB_BUTTON_WORK* p_button_work = p_work;
	ZKN_SORTSEARCHSUB_GLB* p_glb = p_button_work->p_glb;
	ZKN_SORTSEARCHSUB_WORK* p_subwork = p_button_work->p_work;

	// �{�^���C�x���g�i�[
	p_subwork->button_event_sub[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_HOLD:
		p_subwork->do_flag_select = button_no;
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	����1���
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMakeType1( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap )
{
	int i, j;
	int x, y;
	// �e�[�u���쐬
	p_work->hit_tbl_sub = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_SORTSEARCHSUB_BUTTON_TYPE1_NUM );

	// �e���W��OAM���쐬����
	for( i=0; i<5; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		for( j=0; j<2; j++ ){
			x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));

			// �e�[�u���f�[�^�ݒ�
			ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl_sub[ (i*2)+j ],
					y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
					y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
					x - (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2),
					x + (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2) );
		}
	}
	
	// �y�[�W����{�^��
	y = ZKN_SORTSEARCHSUB_BUTTON_05_Y;
	x = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2_X;
	// �e�[�u���f�[�^�ݒ�
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2 ],
			y - (ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZY/2),
			y + (ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZY/2),
			x - (ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZX/2),
			x + (ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZX/2) );

	p_work->button_work.p_glb = p_glb;
	p_work->button_work.p_work = p_work;

	// �{�^���}�l�[�W���쐬
	p_work->p_button_man_sub = BMN_Create( 
			p_work->hit_tbl_sub,
			ZKN_SORTSEARCHSUB_BUTTON_TYPE1_NUM,
			ZknSortSearchSubButtonCallBackType1,
			&p_work->button_work,
			heap );
}
static void ZknSortSearchSubButtonMoveType1( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int i;
	
	// �����ꂽ��S�Ẵ{�^�������̊G�ɖ߂�
	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_TYPE1_NUM; i++ ){
		p_work->button_event_sub[ i ] = BMN_EVENT_SLIDEOUT;
	}
	
	BMN_Main( p_work->p_button_man_sub );

	// �I�𒆂̍��ڂ��������ςȂ���
	ZknSortSearchSubButtonSelectSetType1( p_work, ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, ZKN_SORTSEARCH_TYPE1 ) );
	ZknSortSearchSubButtonSelectSetType1( p_work, ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, ZKN_SORTSEARCH_TYPE2 ) );

}
static void ZknSortSearchSubButtonSelectSetType1( ZKN_SORTSEARCHSUB_WORK* p_work, int type )
{
	switch( type ){
	case ZKN_POKELIST_SEARCH_TYPE_BATTLE:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_BATTLE ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_BATTLE ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_JIMEN:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_JIMEN ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_JIMEN ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_IWA:		
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_IWA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_IWA ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_GHOST:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_GHOST ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_GHOST ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_KUSA:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KUSA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KUSA ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_ELECTRIC:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_ELEC ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_ELEC ] = BMN_EVENT_RELEASE;
			}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_SP:		
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_SP ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_SP ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_KOORI:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KOORI ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KOORI ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_AKU:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_AKU ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_AKU ] = BMN_EVENT_RELEASE;
		}
		break;
	default:
		break;
	}
}
static void ZknSortSearchSubButtonCallBackType1( u32 button_no, u32 event, void* p_work )
{
	ZKN_SORTSEARCHSUB_BUTTON_WORK* p_button_work = p_work;
	ZKN_SORTSEARCHSUB_GLB* p_glb = p_button_work->p_glb;
	ZKN_SORTSEARCHSUB_WORK* p_subwork = p_button_work->p_work;

	// �{�^���C�x���g�i�[
	p_subwork->button_event_sub[ button_no ] = event;

	switch( event ){
	case BMN_EVENT_HOLD:
		if( p_subwork->tp_no_touch == FALSE ){
			p_subwork->do_flag_select = button_no;
			p_subwork->tp_no_touch = TRUE;
		}
		break;

	default:
		p_subwork->tp_no_touch = FALSE;
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	����2���
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMakeType2( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap )
{
	int i, j;
	int x, y;
	// �e�[�u���쐬
	p_work->hit_tbl_sub = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NUM );

	// �e���W��OAM���쐬����
	for( i=0; i<4; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		for( j=0; j<2; j++ ){
			x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));

			// �e�[�u���f�[�^�ݒ�
			ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl_sub[ (i*2)+j ],
					y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
					y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
					x - (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2),
					x + (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2) );
		}
	}

	// �[�[�[�[�[�{�^��
	y = ZKN_SORTSEARCHSUB_BUTTON_04_Y;
	x = ZKN_SORTSEARCHSUB_BUTTONDEF_01_X;
	// �e�[�u���f�[�^�ݒ�
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NONE ],
			y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			x - (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2),
			x + (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2) );
	
	// �y�[�W����{�^��
	y = ZKN_SORTSEARCHSUB_BUTTON_05_Y;
	x = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1_X;
	// �e�[�u���f�[�^�ݒ�
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1 ],
			y - (ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZY/2),
			y + (ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZY/2),
			x - (ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZX/2),
			x + (ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZX/2) );


	p_work->button_work.p_glb = p_glb;
	p_work->button_work.p_work = p_work;

	// �{�^���}�l�[�W���쐬
	p_work->p_button_man_sub = BMN_Create( 
			p_work->hit_tbl_sub,
			ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NUM,
			ZknSortSearchSubButtonCallBackType2,
			&p_work->button_work,
			heap );
}
static void ZknSortSearchSubButtonMoveType2( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int i;
	
	// �����ꂽ��S�Ẵ{�^�������̊G�ɖ߂�
	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NUM; i++ ){
		p_work->button_event_sub[ i ] = BMN_EVENT_SLIDEOUT;
	}
	
	BMN_Main( p_work->p_button_man_sub );

	// �I�𒆂̍��ڂ��������ςȂ���
	ZknSortSearchSubButtonSelectSetType2( p_work, ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, ZKN_SORTSEARCH_TYPE1 ) );
	ZknSortSearchSubButtonSelectSetType2( p_work, ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, ZKN_SORTSEARCH_TYPE2 ) );
}
static void ZknSortSearchSubButtonCallBackType2( u32 button_no, u32 event, void* p_work )
{
	ZKN_SORTSEARCHSUB_BUTTON_WORK* p_button_work = p_work;
	ZKN_SORTSEARCHSUB_GLB* p_glb = p_button_work->p_glb;
	ZKN_SORTSEARCHSUB_WORK* p_subwork = p_button_work->p_work;

	// �{�^���C�x���g�i�[
	p_subwork->button_event_sub[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_HOLD:
		if( p_subwork->tp_no_touch == FALSE ){
			p_subwork->do_flag_select = button_no;
			p_subwork->tp_no_touch = TRUE;
		}
		break;

	default:
		p_subwork->tp_no_touch = FALSE;
		break;
	}
}
static void ZknSortSearchSubButtonSelectSetType2( ZKN_SORTSEARCHSUB_WORK* p_work, int type )
{
	switch( type ){
	case ZKN_POKELIST_SEARCH_TYPE_NORMAL:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NORMAL ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NORMAL ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_HIKOU:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HIKOR ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HIKOR ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_POISON:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DOKU ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DOKU ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_MUSHI:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_MUSHI ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_MUSHI ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_METAL:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HAGANE ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HAGANE ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_FIRE:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_FIRE ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_FIRE ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_WATER:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_WATER ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_WATER ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_DRAGON:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DRAGON ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DRAGON ] = BMN_EVENT_RELEASE;
		}
		break;
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���������
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMakeForm( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap )
{
	int i, j;
	int x, y;
	// �e�[�u���쐬
	p_work->hit_tbl_sub = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_SORTSEARCHSUB_BUTTON_FORM_NUM );

	// �e���W��OAM���쐬����
	for( i=0; i<5; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		for( j=0; j<3; j++ ){
			x = ZKN_SORTSEARCHSUB_BUTTON_FORM_DEF_X + (j * ZKN_SORTSEARCHSUB_BUTTON_FORM_OFS_X);

			// �e�[�u���f�[�^�ݒ�
			ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl_sub[ (i*3)+j ],
					y - (ZKN_SORTSEARCHSUB_BUTTON_FORM_SIZY/2),
					y + (ZKN_SORTSEARCHSUB_BUTTON_FORM_SIZY/2),
					x - (ZKN_SORTSEARCHSUB_BUTTON_FORM_SIZX/2),
					x + (ZKN_SORTSEARCHSUB_BUTTON_FORM_SIZX/2) );
		}
	}
	
	p_work->button_work.p_glb = p_glb;
	p_work->button_work.p_work = p_work;

	// �{�^���}�l�[�W���쐬
	p_work->p_button_man_sub = BMN_Create( 
			p_work->hit_tbl_sub,
			ZKN_SORTSEARCHSUB_BUTTON_FORM_NUM,
			ZknSortSearchSubButtonCallBackForm,
			&p_work->button_work,
			heap );
}
static void ZknSortSearchSubButtonMoveForm( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int i;
	
	// �����ꂽ��S�Ẵ{�^�������̊G�ɖ߂�
	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_FORM_NUM; i++ ){
		p_work->button_event_sub[ i ] = BMN_EVENT_SLIDEOUT;
	}
	
	BMN_Main( p_work->p_button_man_sub );

	switch( ZKN_SortSearchAplFormTypeGet( p_glb->p_main_apl ) ){
	case ZKN_POKELIST_SEARCH_FORM_FOUR_LEGS:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_LEGS ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_LEGS ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_TWO_LEGS:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_LEGS ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_LEGS ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_TAIL:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_TAIL ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_TAIL ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_HARABAI:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_HARABAI ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_HARABAI ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_FOUR_WING:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_WING ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_WING ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_TWO_WING:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_WING ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_WING ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_HAITSUKUBARI:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_HAITSUKUBARI ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_HAITSUKUBARI ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_STRAIGHT:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_STRAIGHT ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_STRAIGHT ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_ARM:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_ARM ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_ARM ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_LEGS:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_LEGS ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_LEGS ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_MANY_LEGS:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_MANY_LEGS ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_MANY_LEGS ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_WATER:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_WATER ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_WATER ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_CIRCLE:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_CIRCLE ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_CIRCLE ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_COMP:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_COMP ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_COMP ] = BMN_EVENT_RELEASE;
		}
		break;

	default:
		break;
	}
}
static void ZknSortSearchSubButtonCallBackForm( u32 button_no, u32 event, void* p_work )
{
	ZKN_SORTSEARCHSUB_BUTTON_WORK* p_button_work = p_work;
	ZKN_SORTSEARCHSUB_GLB* p_glb = p_button_work->p_glb;
	ZKN_SORTSEARCHSUB_WORK* p_subwork = p_button_work->p_work;

	// �{�^���C�x���g�i�[
	p_subwork->button_event_sub[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_HOLD:
		p_subwork->do_flag_select = button_no;
		break;

	default:
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���f�[�^�쐬
 *	
 *	@param	p_work	���[�N
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\������
 *
 *	@param	p_work	���[�N
 *	@param	p_glb	�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
// ���ʃ{�^��
static void ZknSortSearchSubCursorCommonSet( ZKN_CURSOR_ONEDATA* p_data, int id )
{
	int x, y;
	int size_x, size_y;

	switch( id ){
	case ZKN_SORTSEARCHSUB_CURSOR_ID_BACK:
		x = ZKN_SORTSEARCHSUB_BUTTON_BACK_X;
		y = ZKN_SORTSEARCHSUB_BUTTON_BACK_Y;
		size_x = ZKN_SORTSEARCHSUB_CURSOR_BACK_SIZX;
		size_y = ZKN_SORTSEARCHSUB_CURSOR_BACK_SIZY;
		break;
		
	case ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI:
		x = ZKN_SORTSEARCHSUB_BUTTON_X;
		y = ZKN_SORTSEARCHSUB_BUTTON_NARABI_Y;
		size_x = ZKN_SORTSEARCHSUB_CURSOR_SIZX;
		size_y = ZKN_SORTSEARCHSUB_CURSOR_SIZY;
		break;
		
	case ZKN_SORTSEARCHSUB_CURSOR_ID_NAME:
		x = ZKN_SORTSEARCHSUB_BUTTON_X;
		y = ZKN_SORTSEARCHSUB_BUTTON_NAME_Y;
		size_x = ZKN_SORTSEARCHSUB_CURSOR_SIZX;
		size_y = ZKN_SORTSEARCHSUB_CURSOR_SIZY;
		break;
		
	case ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE:
		x = ZKN_SORTSEARCHSUB_BUTTON_X;
		y = ZKN_SORTSEARCHSUB_BUTTON_TYPE_Y;
		size_x = ZKN_SORTSEARCHSUB_CURSOR_SIZX;
		size_y = ZKN_SORTSEARCHSUB_CURSOR_SIZY;
		break;
		
	case ZKN_SORTSEARCHSUB_CURSOR_ID_FORM:
		x = ZKN_SORTSEARCHSUB_BUTTON_X;
		y = ZKN_SORTSEARCHSUB_BUTTON_FORM_Y;
		size_x = ZKN_SORTSEARCHSUB_CURSOR_SIZX;
		size_y = ZKN_SORTSEARCHSUB_CURSOR_SIZY;
		break;
		
	case ZKN_SORTSEARCHSUB_CURSOR_ID_ACTION:
		x = ZKN_SORTSEARCHSUB_BUTTON_ACTION_X;
		y = ZKN_SORTSEARCHSUB_BUTTON_ACTION_Y;
		size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
		size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
		break;
	}
	// �J�[�\���ړ��f�[�^�ݒ�
	ZKN_CURSOR_SetOneData( 
			p_data,
			x, 
			y,
			size_x,
			size_y,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_CURSOR_MOVE_NORMAL,
			id );

}
//----------------------------------------------------------------------------
/**
 *	@brief	���ʃ{�^������
 *
 *	@param	p_work	�ް����[�N
 *	@param	p_glb	�ް��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorMoveCommon( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	// �J�[�\���ʒu�̋@�\�����s
	// ���ʕ����������ꂽ�����͈ꏏ
	if( sys.cont & PAD_BUTTON_A ){

		if( p_work->cursor_no_touch == FALSE ){

			switch( ZKN_CURSOR_GetContID( p_work->p_cursor ) ){
			case ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI:
				p_work->do_flag_common = ZKN_SORTSEARCHSUB_BUTTON_NARABI;
				p_work->button_event[ p_work->do_flag_common ] = BMN_EVENT_HOLD;
				break;
				
			case ZKN_SORTSEARCHSUB_CURSOR_ID_NAME:
				p_work->do_flag_common = ZKN_SORTSEARCHSUB_BUTTON_NAME;
				p_work->button_event[ p_work->do_flag_common ] = BMN_EVENT_HOLD;
				break;
				
			case ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE:
				p_work->do_flag_common = ZKN_SORTSEARCHSUB_BUTTON_TYPE;
				p_work->button_event[ p_work->do_flag_common ] = BMN_EVENT_HOLD;
				break;
				
			case ZKN_SORTSEARCHSUB_CURSOR_ID_FORM:
				p_work->do_flag_common = ZKN_SORTSEARCHSUB_BUTTON_FORM;
				p_work->button_event[ p_work->do_flag_common ] = BMN_EVENT_HOLD;
				break;

			case ZKN_SORTSEARCHSUB_CURSOR_ID_ACTION:
				p_work->do_flag_common = ZKN_SORTSEARCHSUB_BUTTON_ACTION;
				p_work->button_event[ p_work->do_flag_common ] = BMN_EVENT_HOLD;
				break;
				
			case ZKN_SORTSEARCHSUB_CURSOR_ID_BACK:
				p_work->do_flag_common = ZKN_SORTSEARCHSUB_BUTTON_BACK;
				p_work->button_event[ p_work->do_flag_common ] = BMN_EVENT_HOLD;
				break;

			default:
				break;
			}

			p_work->req_count ++;
		}

	}else{
		p_work->req_count = 0;

		p_work->cursor_no_touch = FALSE;	// PAD_BUTTON_A���͂Ȃ���
	}

	// B�{�^���Ń|�P���X�g�ɖ߂�
	if(sys.trg & PAD_BUTTON_B){
		p_work->do_flag_common = ZKN_SORTSEARCHSUB_BUTTON_BACK;
		p_work->button_event[ p_work->do_flag_common ] = BMN_EVENT_HOLD;
	}

}

// ��ĉ��
static void ZknSortSearchSubCursorMakeSort( ZKN_SORTSEARCHSUB_WORK* p_work, int heap )
{
	int i, j;
	int x, y;
	int move_type;
	int id;

	p_work->p_cursor_tbl = sys_AllocMemory( heap, sizeof(ZKN_CURSOR_ONEDATA) * (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X * ZKN_SORTSEARCHSUB_CURSOR_MAX_Y) );

	//�@�J�[�\���ް��쐬
	for( i=0; i<ZKN_SORTSEARCHSUB_CURSOR_MAX_Y; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		
		for( j=0; j<ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X; j++ ){	
		
			x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));
			id = ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00 + (i * (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X - 1)) + j;

			// �s�ɂ��i�[�f�[�^���ύX����
			switch( i ){
			case ZKN_SORTSEARCHSUB_BUTTON_BACK:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_BACK;
				}else{
					move_type = ZKN_CURSOR_MOVE_STOP;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NARABI:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NAME:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NAME;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_TYPE:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_FORM;
				}else{
					move_type = ZKN_CURSOR_MOVE_STOP;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_ACTION:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_ACTION;
				}else{
					move_type = ZKN_CURSOR_MOVE_STOP;
				}
				break;
			}

			// �I�����߃{�^��
			if( j < (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X - 1) ){
				// �J�[�\���ړ��f�[�^�ݒ�
				ZKN_CURSOR_SetOneData( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X) + j ],
						x, y,
						ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX, 
						ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY,
						move_type, move_type,
						id );
			}else{
				// ���p�{�^��
				ZknSortSearchSubCursorCommonSet( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X) + j ],
						id );
			}
		}
	}


	// �J�[�\���f�[�^�ݒ�
	p_work->p_cursor = ZKN_CURSOR_Alloc( heap );
	ZKN_CURSOR_Init( p_work->p_cursor, p_work->p_cursor_tbl,
			ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X,
			ZKN_SORTSEARCHSUB_CURSOR_MAX_Y );
}
static void ZknSortSearchSubCursorMoveSort( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	if( sys.cont & PAD_BUTTON_A ){

		if( p_work->cursor_no_touch == FALSE ){

			switch( ZKN_CURSOR_GetContID( p_work->p_cursor ) ){
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_02:		// 0��1�̓_�~�[
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUMBER;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_03:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NARABI_AIUEO;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_04:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NARABI_HEAVY;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_05:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NARABI_LIGHT;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_06:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NARABI_TALL;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_07:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NARABI_SHORT;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
				
			default:
				break;
			}
		}

	}else{
		p_work->cursor_no_touch = FALSE;	// PAD_BUTTON_A���͂Ȃ���
	}
}

// ���O���
static void ZknSortSearchSubCursorMakeName( ZKN_SORTSEARCHSUB_WORK* p_work, int heap )
{
	int i, j;
	int x, y;
	int move_type;
	int id;
	p_work->p_cursor_tbl = sys_AllocMemory( heap, sizeof(ZKN_CURSOR_ONEDATA) * (ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X * ZKN_SORTSEARCHSUB_CURSOR_MAX_Y) );

	//�@�J�[�\���ް��쐬
	for( i=0; i<ZKN_SORTSEARCHSUB_CURSOR_MAX_Y; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		
		for( j=0; j<ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X; j++ ){	
		
			x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));
			id = ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00 + (i * 2) + j;

			// �s�ɂ��i�[�f�[�^���ύX����
			switch( i ){
			case ZKN_SORTSEARCHSUB_BUTTON_BACK:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_BACK;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NARABI:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NAME:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NAME;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_TYPE:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_FORM;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_ACTION:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_ACTION;
				}else{
					move_type = ZKN_CURSOR_MOVE_STOP;
				}
				break;
			}

			// �I�����߃{�^��
			if( j < (ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X - 1) ){
				// �J�[�\���ړ��f�[�^�ݒ�
				ZKN_CURSOR_SetOneData( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X) + j ],
						x, y,
						ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX, 
						ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY,
						move_type, move_type,
						id );
			}else{
				// ���p�{�^��
				ZknSortSearchSubCursorCommonSet( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X) + j ],
						id );
			}
		}
	}

	// �J�[�\���f�[�^�ݒ�
	p_work->p_cursor = ZKN_CURSOR_Alloc( heap );
	ZKN_CURSOR_Init( p_work->p_cursor, p_work->p_cursor_tbl,
			ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X,
			ZKN_SORTSEARCHSUB_CURSOR_MAX_Y );
}
static void ZknSortSearchSubCursorMoveName( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	if( sys.cont & PAD_BUTTON_A ){
		if( p_work->cursor_no_touch == FALSE ){

			switch( ZKN_CURSOR_GetContID( p_work->p_cursor ) ){
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_A;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_01:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_HA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_02:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_KA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_03:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_MA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_04:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_SA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_05:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_RA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_06:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_TA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_07:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_YAWA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_08:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_NA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_09:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_NONE;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			default:
				break;
			}
		}

	}else{

		p_work->cursor_no_touch = FALSE;
	}
}

// ����1���
static void ZknSortSearchSubCursorMakeType1( ZKN_SORTSEARCHSUB_WORK* p_work, int heap )
{
	int i, j;
	int x, y;
	int size_x, size_y;
	int move_type;
	int id;
	p_work->p_cursor_tbl = sys_AllocMemory( heap, sizeof(ZKN_CURSOR_ONEDATA) * (ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X * ZKN_SORTSEARCHSUB_CURSOR_MAX_Y) );

	//�@�J�[�\���ް��쐬
	for( i=0; i<ZKN_SORTSEARCHSUB_CURSOR_MAX_Y; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		
		for( j=0; j<ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X; j++ ){	
		
			x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));
			id = ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00 + (i * 2) + j;

			// �s�ɂ��i�[�f�[�^���ύX����
			switch( i ){
			case ZKN_SORTSEARCHSUB_BUTTON_BACK:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_BACK;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NARABI:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NAME:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NAME;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_TYPE:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_FORM;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_ACTION:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_ACTION;
				}else{
					if( j == 0 ){
						move_type = ZKN_CURSOR_MOVE_NORMAL;
						size_x = ZKN_SORTSEARCHSUB_CURSOR_PAGE_SIZX;
						size_y = ZKN_SORTSEARCHSUB_CURSOR_PAGE_SIZY;
						x = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2_X;	
					}else{
						move_type = ZKN_CURSOR_MOVE_STOP;
						size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
						size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
					}
				}
				break;
			}

			// �I�����߃{�^��
			if( j < (ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X - 1) ){
				// �J�[�\���ړ��f�[�^�ݒ�
				ZKN_CURSOR_SetOneData( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X) + j ],
						x, y,
						size_x, 
						size_y,
						move_type, move_type,
						id );
			}else{
				// ���p�{�^��
				ZknSortSearchSubCursorCommonSet( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X) + j ],
						id );
			}
		}
	}

	// �J�[�\���f�[�^�ݒ�
	p_work->p_cursor = ZKN_CURSOR_Alloc( heap );
	ZKN_CURSOR_Init( p_work->p_cursor, p_work->p_cursor_tbl,
			ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X,
			ZKN_SORTSEARCHSUB_CURSOR_MAX_Y );
}
static void ZknSortSearchSubCursorMoveType1( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	if( sys.cont & PAD_BUTTON_A ){

		if( p_work->cursor_no_touch == FALSE ){

			switch( ZKN_CURSOR_GetContID( p_work->p_cursor ) ){
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_AKU;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_01:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KOORI;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_02:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_IWA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_03:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_GHOST;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_04:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_SP;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_05:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_JIMEN;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_06:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_BATTLE;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_07:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_ELEC;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_08:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KUSA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_09:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_NONE;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				p_work->cursor_no_touch = TRUE;	// �������Ă��������Ȃ�
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_10:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			default:
				break;
			}
		}

	}else{

		p_work->cursor_no_touch = FALSE;
	}
}

// ����2���
static void ZknSortSearchSubCursorMakeType2( ZKN_SORTSEARCHSUB_WORK* p_work, int heap )
{
	int i, j;
	int x, y;
	int size_x, size_y;
	int move_typex, move_typey;
	int id;
	p_work->p_cursor_tbl = sys_AllocMemory( heap, sizeof(ZKN_CURSOR_ONEDATA) * (ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X * ZKN_SORTSEARCHSUB_CURSOR_MAX_Y) );

	//�@�J�[�\���ް��쐬
	for( i=0; i<ZKN_SORTSEARCHSUB_CURSOR_MAX_Y; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		
		for( j=0; j<ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X; j++ ){	
		
			x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));
			id = ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00 + (i * 2) + j;

			// �s�ɂ��i�[�f�[�^���ύX����
			switch( i ){
			case ZKN_SORTSEARCHSUB_BUTTON_BACK:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_BACK;
				}else{
					move_typex = ZKN_CURSOR_MOVE_NORMAL;
					move_typey = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NARABI:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI;
				}else{
					move_typex = ZKN_CURSOR_MOVE_NORMAL;
					move_typey = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NAME:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NAME;
				}else{
					move_typex = ZKN_CURSOR_MOVE_NORMAL;
					move_typey = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_TYPE:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE;
				}else{
					move_typex = ZKN_CURSOR_MOVE_NORMAL;
					move_typey = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_FORM;
				}else{
					if( j==0 ){
						move_typex = ZKN_CURSOR_MOVE_STOP;
						move_typey = ZKN_CURSOR_MOVE_SKIP;
						size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
						size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
					}else{
						move_typex = ZKN_CURSOR_MOVE_NORMAL;
						move_typey = ZKN_CURSOR_MOVE_NORMAL;
						size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
						size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
					}
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_ACTION:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_ACTION;
				}else{
					if( j == 0 ){
						move_typex = ZKN_CURSOR_MOVE_NORMAL;
						move_typey = ZKN_CURSOR_MOVE_NORMAL;
						size_x = ZKN_SORTSEARCHSUB_CURSOR_PAGE_SIZX;
						size_y = ZKN_SORTSEARCHSUB_CURSOR_PAGE_SIZY;
						x = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1_X;
					}else{
						move_typex = ZKN_CURSOR_MOVE_STOP;
						move_typey = ZKN_CURSOR_MOVE_STOP;
						size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
						size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
					}
				}
				break;
			}

			// �I�����߃{�^��
			if( j < (ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X - 1) ){
				// �J�[�\���ړ��f�[�^�ݒ�
				ZKN_CURSOR_SetOneData( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X) + j ],
						x, y,
						size_x, 
						size_y,
						move_typex, move_typey,
						id );
			}else{
				// ���p�{�^��
				ZknSortSearchSubCursorCommonSet( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X) + j ],
						id );
			}
		}
	}

	// �J�[�\���f�[�^�ݒ�
	p_work->p_cursor = ZKN_CURSOR_Alloc( heap );
	ZKN_CURSOR_Init( p_work->p_cursor, p_work->p_cursor_tbl,
			ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X,
			ZKN_SORTSEARCHSUB_CURSOR_MAX_Y );
}
static void ZknSortSearchSubCursorMoveType2( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	if( sys.cont & PAD_BUTTON_A ){
		if( p_work->cursor_no_touch == FALSE ){

			switch( ZKN_CURSOR_GetContID( p_work->p_cursor ) ){
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DOKU;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_01:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HIKOR;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_02:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DRAGON;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_03:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_FIRE;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_04:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NORMAL;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_05:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_WATER;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_06:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HAGANE;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_07:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_MUSHI;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_09:		// �W�̓_�~�[
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NONE;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				p_work->cursor_no_touch = TRUE;	// �������Ă��������Ȃ�
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_10:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			default:
				break;
			}
		}

	}else{

		p_work->cursor_no_touch = FALSE;
	}
}

// �`���
static void ZknSortSearchSubCursorMakeForm( ZKN_SORTSEARCHSUB_WORK* p_work, int heap )
{
	int i, j;
	int x, y;
	int move_type;
	int id;
	p_work->p_cursor_tbl = sys_AllocMemory( heap, sizeof(ZKN_CURSOR_ONEDATA) * (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X * ZKN_SORTSEARCHSUB_CURSOR_MAX_Y) );


	//�@�J�[�\���ް��쐬
	for( i=0; i<ZKN_SORTSEARCHSUB_CURSOR_MAX_Y; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		
		for( j=0; j<ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X; j++ ){	
		
			x = ZKN_SORTSEARCHSUB_BUTTON_FORM_DEF_X + (j * ZKN_SORTSEARCHSUB_BUTTON_FORM_OFS_X);
			id = ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00 + (i * (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X - 1)) + j;

			// �s�ɂ��i�[�f�[�^���ύX����
			switch( i ){
			case ZKN_SORTSEARCHSUB_BUTTON_BACK:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_BACK;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NARABI:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NAME:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NAME;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_TYPE:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_FORM;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_ACTION:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_ACTION;
				}else{
					move_type = ZKN_CURSOR_MOVE_STOP;
				}
				break;
			}

			// �I�����߃{�^��
			if( j < (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X - 1) ){
				// �J�[�\���ړ��f�[�^�ݒ�
				ZKN_CURSOR_SetOneData( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X) + j ],
						x, y,
						ZKN_SORTSEARCHSUB_CURSOR_FORM_SIZX, 
						ZKN_SORTSEARCHSUB_CURSOR_FORM_SIZY,
						move_type, move_type,
						id );
			}else{
				// ���p�{�^��
				ZknSortSearchSubCursorCommonSet( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X) + j ],
						id );
			}
		}
	}

	// �J�[�\���f�[�^�ݒ�
	p_work->p_cursor = ZKN_CURSOR_Alloc( heap );
	ZKN_CURSOR_Init( p_work->p_cursor, p_work->p_cursor_tbl,
			ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X,
			ZKN_SORTSEARCHSUB_CURSOR_MAX_Y );
}
static void ZknSortSearchSubCursorMoveForm( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	if( sys.cont & PAD_BUTTON_A ){
		if( p_work->cursor_no_touch == FALSE ){

			switch( ZKN_CURSOR_GetContID( p_work->p_cursor ) ){
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_CIRCLE;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_01:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_HARABAI;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_02:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_WATER;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_03:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_ARM;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_04:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_STRAIGHT;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_05:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_TAIL;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_06:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_LEGS;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_07:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_LEGS;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_08:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_WING;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_09:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_MANY_LEGS;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_10:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_COMP;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_11:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_LEGS;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_12:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_WING;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_13:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_HAITSUKUBARI;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_14:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_NONE;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			default:
				break;
			}
		}
	}else{
		p_work->cursor_no_touch = FALSE;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\�����ʓ���
 *
 *	@param	p_work
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorMove( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	
	if( sys.trg & PAD_KEY_RIGHT ){
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_ADD_X, 1 );
		p_work->cursor_no_touch = TRUE;	// PAD_BUTTON_A�������Ă��������Ȃ�
		//		Snd_SePlay( ZKN_SND_SELECT );
	}

	if( sys.trg & PAD_KEY_LEFT ){
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_ADD_X, -1 );
		p_work->cursor_no_touch = TRUE;	// PAD_BUTTON_A�������Ă��������Ȃ�
//		Snd_SePlay( ZKN_SND_SELECT );
	}

	if( sys.trg & PAD_KEY_UP ){
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_ADD_Y, -1 );
		p_work->cursor_no_touch = TRUE;	// PAD_BUTTON_A�������Ă��������Ȃ�
//		Snd_SePlay( ZKN_SND_SELECT );
	}

	if( sys.trg & PAD_KEY_DOWN ){
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_ADD_Y, 1 );
		p_work->cursor_no_touch = TRUE;	// PAD_BUTTON_A�������Ă��������Ȃ�
//		Snd_SePlay( ZKN_SND_SELECT );
	}

	// ���ʓ���
	ZknSortSearchSubCursorMoveCommon( p_work, p_glb );


	// �I��ʓ���
	ZknSortSearchSubCursorMoveSub( p_work, p_glb, p_work->local_select, p_work->local_type_page );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�����ߕʃJ�[�\������
 *
 *	@param	p_work			���[�N�ް�
 *	@param	p_glb			�O���[�o���ް�
 *	@param	select_type		�Z���N�g����
 *	@param	type_page		���߂̃y�[�W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorMoveSub( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int select_type, int type_page )
{
	switch( select_type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		ZknSortSearchSubCursorMoveSort( p_work, p_glb );
		break;
		
	case ZKN_SORTSEARCH_SELECT_NEME:
		ZknSortSearchSubCursorMoveName( p_work, p_glb );
		break;
		
	case ZKN_SORTSEARCH_SELECT_TYPE:
		if( type_page == 0 ){
			ZknSortSearchSubCursorMoveType1( p_work, p_glb );
		}else{
			ZknSortSearchSubCursorMoveType2( p_work, p_glb );
		}
		break;
		
	case ZKN_SORTSEARCH_SELECT_FORM:
		ZknSortSearchSubCursorMoveForm( p_work, p_glb );
		break;
		
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���f�[�^�j��
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorDelete( ZKN_SORTSEARCHSUB_WORK* p_work )
{
	sys_FreeMemoryEz( p_work->p_cursor_tbl );
	ZKN_CURSOR_Free( p_work->p_cursor );
	p_work->p_cursor = NULL;
	p_work->p_cursor_tbl = NULL;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���̏����쐬
 *
 *	@param	p_work	���[�N
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorMake( ZKN_SORTSEARCHSUB_WORK* p_work, int heap )
{
	ZknSortSearchSubCursorMakeSub( p_work, heap, p_work->local_select, p_work->local_type_page );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�����ߕʍ쐬
 *
 *	@param	p_work			���[�N
 *	@param	heap			�q�[�v
 *	@param	select_type		�I������
 *	@param	type_page		���߃y�[�W
 *
 *	@return	none
 */	
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorMakeSub( ZKN_SORTSEARCHSUB_WORK* p_work, int heap, int select_type, int type_page )
{
	switch( select_type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		ZknSortSearchSubCursorMakeSort( p_work, heap );
		break;
		
	case ZKN_SORTSEARCH_SELECT_NEME:
		ZknSortSearchSubCursorMakeName( p_work, heap );
		break;
		
	case ZKN_SORTSEARCH_SELECT_TYPE:
		if( type_page == 0 ){
			ZknSortSearchSubCursorMakeType1( p_work, heap );
		}else{
			ZknSortSearchSubCursorMakeType2( p_work, heap );
		}
		break;
		
	case ZKN_SORTSEARCH_SELECT_FORM:
		ZknSortSearchSubCursorMakeForm( p_work, heap );
		break;
		
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\������������
 *
 *	@param	p_work
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorInit( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int cursor_id; 
	
	switch( p_work->local_select ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		cursor_id = ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI;
		break;
		
	case ZKN_SORTSEARCH_SELECT_NEME:
		cursor_id = ZKN_SORTSEARCHSUB_CURSOR_ID_NAME;
		break;
		
	case ZKN_SORTSEARCH_SELECT_TYPE:
		cursor_id = ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE;
		break;
		
	case ZKN_SORTSEARCH_SELECT_FORM:
		cursor_id = ZKN_SORTSEARCHSUB_CURSOR_ID_FORM;
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	
	ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_SET_CONTID, cursor_id );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���ύX
 *
 *	@param	p_work
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorChg( ZKN_SORTSEARCHSUB_WORK* p_work, int heap )
{
	// ���܂ł̃J�[�\���ް��j��
	ZknSortSearchSubCursorDelete( p_work );

	// �쐬
	ZknSortSearchSubCursorMakeSub( p_work, heap, p_work->local_select, p_work->local_type_page );
}




//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\��������
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_work		�f�[�^���[�N
 *	@param	cp_glb		�f�[�^�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorDrawInit( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_WORK* cp_work, const ZKN_SORTSEARCHSUB_GLB* cp_glb )
{
	// �J�[�\�����������W�ݒ�
	ZKN_UTIL_CursorSetMatrixCursorSysNotAnm( cp_work->p_cursor, p_drawglb->p_drawglb );
	// �J�[�\������
	ZknSortSearchSubCursorDrawPack( p_drawglb, cp_work, cp_glb );
}



//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���`�揈���p�b�N�֐�
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_work		�f�[�^���[�N
 *	@param	cp_glb		�f�[�^�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorDrawPack( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_WORK* cp_work, const ZKN_SORTSEARCHSUB_GLB* cp_glb )
{
	BOOL check;
	
	//�@�\���n�m�n�e�e�ƃJ�[�\������
	if( (ZKN_GLBDATA_TouchCursorFlagGet( cp_glb->p_glb ) == TRUE) ){

		check = ZknSortSearchSubCursorOnOff( p_drawglb, TRUE );

		if( check ){
			// �ĕ`�悳�ꂽ�Ƃ���,�J�[�\���`����W��������
			// �J�[�\�����������W�ݒ�
			ZKN_UTIL_CursorSetMatrixCursorSysNotAnm( cp_work->p_cursor, p_drawglb->p_drawglb );
		}

		ZknSortSearchSubCursorDraw( p_drawglb, cp_work );
	}else{
		ZknSortSearchSubCursorOnOff( p_drawglb, FALSE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�ӃJ�[�\���`�揈��
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	p_work		�f�[�^���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorDraw( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_WORK* cp_work )
{
	ZKN_GLB_DRAWDATA* p_draw = p_drawglb->p_drawglb;
	
	ZKN_UTIL_CursorSetMatrixCursorSys( cp_work->p_cursor, p_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���`��ONOFF
 *
 *	@param	p_draw	�`�惏�[�N
 *	@param	flag	ONOFF�t���O
 *	
 *	@retval	TRUE	�l�ύX
 *	@retval	FALSE	�ύX���Ȃ�����
 */
//-----------------------------------------------------------------------------
static BOOL ZknSortSearchSubCursorOnOff( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb,  BOOL flag )
{
	ZKN_GLB_DRAWDATA* p_draw = p_drawglb->p_drawglb;
	
	if( ZKN_UTIL_CursorGetDrawFlag( &p_draw->cursor ) != flag ){
		ZKN_UTIL_CursorSetDrawFlag( &p_draw->cursor, flag );
		return TRUE;
	}
	
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u���OAMResource�ǂݍ���
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�΂�
 *	@param	heap			�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubLoadOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_sort_oam_sub_lzh_NCGR, TRUE,
			NARC_zukan_zkn_sort_oam_sub_lzh_NCGR + ZKN_SORTSEARCHSUB_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// �p���b�g�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_list_oam_NCLR, FALSE, 
			NARC_zukan_zkn_list_oam_NCLR + ZKN_SORTSEARCHSUB_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DSUB, 
			ZKN_ZUKAN_COMMON_PLTT_SUB_LOAD, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// �Z���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_sort_oam_sub_lzh_NCER, TRUE,
			NARC_zukan_zkn_sort_oam_sub_lzh_NCER + ZKN_SORTSEARCHSUB_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_sort_oam_sub_lzh_NANR, TRUE,
			NARC_zukan_zkn_sort_oam_sub_lzh_NANR + ZKN_SORTSEARCHSUB_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u���OAMResource�j��
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubReleaseOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb )
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
 *	@brief	�`��OAM�ǂݍ���
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubLoadOamForm( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->res_obj_form[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_sort_oam_sub2_lzh_NCGR, TRUE,
			NARC_zukan_zkn_sort_oam_sub2_lzh_NCGR + ZKN_SORTSEARCHSUB_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj_form[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj_form[ CLACT_U_CHAR_RES ] );


	// �Z���f�[�^�ǂݍ���
	p_draw->res_obj_form[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_sort_oam_sub2_lzh_NCER, TRUE,
			NARC_zukan_zkn_sort_oam_sub2_lzh_NCER + ZKN_SORTSEARCHSUB_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->res_obj_form[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_sort_oam_sub2_lzh_NANR, TRUE,
			NARC_zukan_zkn_sort_oam_sub2_lzh_NANR + ZKN_SORTSEARCHSUB_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��OMA�j��
 *
 *	@param	p_draw
 *	@param	p_drawglb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubReleaseOamForm( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;


	CLACT_U_CharManagerDelete( p_draw->res_obj_form[ CLACT_U_CHAR_RES ] );

	// ���\�[�X�j��
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_obj_form[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_obj_form[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->res_obj_form[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�^�[�o�^
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClact( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i;
	
	// �e�{�^����o�^
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_sort_oam_sub_lzh_NCGR + ZKN_SORTSEARCHSUB_RES_ID,
			NARC_zukan_zkn_list_oam_NCLR + ZKN_SORTSEARCHSUB_RES_ID, 
			NARC_zukan_zkn_sort_oam_sub_lzh_NCER + ZKN_SORTSEARCHSUB_RES_ID,
			NARC_zukan_zkn_sort_oam_sub_lzh_NANR + ZKN_SORTSEARCHSUB_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 32;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;

	// �����ް��o�^
	ZknSortSearchSubAddClactCommon( p_draw, &add );

	// �T�u�ް��o�^
	ZknSortSearchSubAddSubClact( p_draw, &add, p_draw->local_select, p_draw->local_type_page );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�^�[�j��
 *
 *	@param	p_draw		�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDeleteClact( ZKN_SORTSEARCHSUB_DRAW* p_draw )
{
	ZknSortSearchSubDeleteClactCommon( p_draw );

	// �I�����ߕʃA�N�^�[�j��
	ZknSortSearchSubDeleteClactSub( p_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���N�g���߂��ύX���ꂽ�̂ŁA�Z���A�N�^�[��ύX
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubChgClact( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i;
	
	// �e�{�^����o�^
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_sort_oam_sub_lzh_NCGR + ZKN_SORTSEARCHSUB_RES_ID,
			NARC_zukan_zkn_list_oam_NCLR + ZKN_SORTSEARCHSUB_RES_ID, 
			NARC_zukan_zkn_sort_oam_sub_lzh_NCER + ZKN_SORTSEARCHSUB_RES_ID,
			NARC_zukan_zkn_sort_oam_sub_lzh_NANR + ZKN_SORTSEARCHSUB_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 32;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;


	// ���܂ł̂��̂�j��
	ZknSortSearchSubDeleteClactSub( p_draw );

	// �T�u�ް��o�^
	ZknSortSearchSubAddSubClact( p_draw, &add, p_draw->local_select, p_draw->local_type_page );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u�Z���A�N�^�[�o�^�֐�
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_add		�o�^�ް�
 *	@param	select_type	�Z���N�g����
 *	@param	local_type_page	���߂�page��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddSubClact( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add, int select_type, int local_type_page )
{
	switch( select_type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		ZknSortSearchSubAddClactSort( p_draw, p_add );
		break;
	case ZKN_SORTSEARCH_SELECT_NEME:
		ZknSortSearchSubAddClactName( p_draw, p_add );
		break;
	case ZKN_SORTSEARCH_SELECT_TYPE:
		if( local_type_page == 0 ){
			ZknSortSearchSubAddClactType1( p_draw, p_add );
		}else{
			ZknSortSearchSubAddClactType2( p_draw, p_add );
		}
		break;
	case ZKN_SORTSEARCH_SELECT_FORM:
		ZknSortSearchSubAddClactForm( p_draw, p_add );
		break;
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ʕ����̃O���t�B�b�N�Z���A�N�^�[�o�^
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_add		�o�^�ް��@�K�{�ް��i�[�ς�
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClactCommon( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add )
{
	int i;
	
	
	// �{�^���쐬
	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_NUM; i++ ){
		// �o�^���W�ݒ�
		switch( i ){
		case ZKN_SORTSEARCHSUB_BUTTON_BACK:
			p_add->mat.y		= (ZKN_SORTSEARCHSUB_BUTTON_BACK_Y * FX32_ONE) + SUB_SURFACE_Y;
			p_add->mat.x		= ZKN_SORTSEARCHSUB_BUTTON_BACK_X * FX32_ONE;
			break;

		case ZKN_SORTSEARCHSUB_BUTTON_NARABI:
			p_add->mat.y		= (ZKN_SORTSEARCHSUB_BUTTON_NARABI_Y * FX32_ONE) + SUB_SURFACE_Y;
			p_add->mat.x		= ZKN_SORTSEARCHSUB_BUTTON_X * FX32_ONE;
			break;
			
		case ZKN_SORTSEARCHSUB_BUTTON_NAME:
			p_add->mat.y		= (ZKN_SORTSEARCHSUB_BUTTON_NAME_Y * FX32_ONE) + SUB_SURFACE_Y;
			p_add->mat.x		= ZKN_SORTSEARCHSUB_BUTTON_X * FX32_ONE;
			break;
			
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE:
			p_add->mat.y		= (ZKN_SORTSEARCHSUB_BUTTON_TYPE_Y * FX32_ONE) + SUB_SURFACE_Y;
			p_add->mat.x		= ZKN_SORTSEARCHSUB_BUTTON_X * FX32_ONE;
			break;
			
		case ZKN_SORTSEARCHSUB_BUTTON_FORM:
			p_add->mat.y		= (ZKN_SORTSEARCHSUB_BUTTON_FORM_Y * FX32_ONE) + SUB_SURFACE_Y;
			p_add->mat.x		= ZKN_SORTSEARCHSUB_BUTTON_X * FX32_ONE;
			break;

		case ZKN_SORTSEARCHSUB_BUTTON_ACTION:
			p_add->mat.y		= (ZKN_SORTSEARCHSUB_BUTTON_ACTION_Y * FX32_ONE) + SUB_SURFACE_Y;
			p_add->mat.x		= ZKN_SORTSEARCHSUB_BUTTON_ACTION_X * FX32_ONE;
			break;
		}

		// �o�^�@�A�j���[�V�����ݒ�
		p_draw->clact[ i ] = CLACT_AddSimple( p_add );
		
		// �A�j���V�[�P���X�ݒ�
		switch( i ){
		case ZKN_SORTSEARCHSUB_BUTTON_BACK:
			CLACT_AnmChg( p_draw->clact[ i ], ZKN_SORTSEARCHSUB_RET_BUTTON );
			break;

		case ZKN_SORTSEARCHSUB_BUTTON_NARABI:
		case ZKN_SORTSEARCHSUB_BUTTON_NAME:
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE:
		case ZKN_SORTSEARCHSUB_BUTTON_FORM:
			CLACT_AnmChg( p_draw->clact[ i ], ZKN_SORTSEARCHSUB_SELECT_BUTTON );
			break;

		case ZKN_SORTSEARCHSUB_BUTTON_ACTION:
			CLACT_AnmChg( p_draw->clact[ i ], ZKN_SORTSEARCHSUB_ACTION_BUTTON );
			break;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ʕ�����OAM�j��
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDeleteClactCommon( ZKN_SORTSEARCHSUB_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_NUM; i++ ){
		CLACT_Delete( p_draw->clact[i] );
	}
}

//-----------------------------------------------------------------------------
/**
 *	@brief	�T�u�{�^���A�N�^�[�j������
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDeleteClactSub( ZKN_SORTSEARCHSUB_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		if( p_draw->clact_sub[i] ){
			CLACT_Delete( p_draw->clact_sub[i] );
			p_draw->clact_sub[i] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
/**
 *	@brief	��ĉ�ʓo�^
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClactSort( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add )
{
	int i, j;
	
	// �e���W��OAM���쐬����
	for( i=0; i<3; i++ ){
		p_add->mat.y = ZKN_SORTSEARCHSUB_BUTTON_01_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		p_add->mat.y = (p_add->mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
		for( j=0; j<2; j++ ){
			p_add->mat.x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));

			p_add->mat.x <<= FX32_SHIFT;
			p_draw->clact_sub[ (i*2) + j ] = CLACT_AddSimple( p_add );
			CLACT_AnmChg( p_draw->clact_sub[ (i*2) + j ], ZKN_SORTSEARCHSUB_MAIN_BUTTON );
		}
	}
}

//-----------------------------------------------------------------------------
/**
 *	@brief	�Ȃ܂���ʓo�^
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClactName( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add )
{
	int i, j;
	
	// �e���W��OAM���쐬����
	for( i=0; i<5; i++ ){
		p_add->mat.y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		p_add->mat.y = (p_add->mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
		for( j=0; j<2; j++ ){
			p_add->mat.x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));

			p_add->mat.x <<= FX32_SHIFT;
			p_draw->clact_sub[ (i*2) + j ] = CLACT_AddSimple( p_add );
			CLACT_AnmChg( p_draw->clact_sub[ (i*2) + j ], ZKN_SORTSEARCHSUB_MAIN_BUTTON );
		}
	}
}

//-----------------------------------------------------------------------------
/**
 *	@brief	����1��ʓo�^
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClactType1( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add )
{
	int i, j;
	
	// �e���W��OAM���쐬����
	for( i=0; i<5; i++ ){
		p_add->mat.y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		p_add->mat.y = (p_add->mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
		for( j=0; j<2; j++ ){
			p_add->mat.x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));

			p_add->mat.x <<= FX32_SHIFT;
			p_draw->clact_sub[ (i*2) + j ] = CLACT_AddSimple( p_add );
			CLACT_AnmChg( p_draw->clact_sub[ (i*2) + j ], ZKN_SORTSEARCHSUB_MAIN_BUTTON );
		}
	}
	
	// �y�[�W����{�^��
	p_add->mat.y = ZKN_SORTSEARCHSUB_BUTTON_05_Y;
	p_add->mat.x = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2_X;
	p_add->mat.x <<= FX32_SHIFT;
	p_add->mat.y = (p_add->mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
	p_draw->clact_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2 ] = CLACT_AddSimple( p_add );
	CLACT_AnmChg( p_draw->clact_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2 ], ZKN_SORTSEARCHSUB_PAGE_ADD_BUTTON );
}

//-----------------------------------------------------------------------------
/**
 *	@brief	����2��ʓo�^
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClactType2( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add )
{
	int i, j;
	
	// �e���W��OAM���쐬����
	for( i=0; i<4; i++ ){
		p_add->mat.y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		p_add->mat.y = (p_add->mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
		for( j=0; j<2; j++ ){
			p_add->mat.x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));

			p_add->mat.x <<= FX32_SHIFT;
			p_draw->clact_sub[ (i*2) + j ] = CLACT_AddSimple( p_add );
			CLACT_AnmChg( p_draw->clact_sub[ (i*2) + j ], ZKN_SORTSEARCHSUB_MAIN_BUTTON );
		}
	}

	// �[�[�[�[�[�{�^��
	p_add->mat.y = ZKN_SORTSEARCHSUB_BUTTON_04_Y;
	p_add->mat.x = ZKN_SORTSEARCHSUB_BUTTONDEF_01_X;
	p_add->mat.x <<= FX32_SHIFT;
	p_add->mat.y = (p_add->mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
	p_draw->clact_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NONE ] = CLACT_AddSimple( p_add );
	CLACT_AnmChg( p_draw->clact_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NONE ], ZKN_SORTSEARCHSUB_MAIN_BUTTON );
	
	// �y�[�W����{�^��
	p_add->mat.y = ZKN_SORTSEARCHSUB_BUTTON_05_Y;
	p_add->mat.x = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1_X;
	p_add->mat.x <<= FX32_SHIFT;
	p_add->mat.y = (p_add->mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
	p_draw->clact_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1 ] = CLACT_AddSimple( p_add );
	CLACT_AnmChg( p_draw->clact_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1 ], ZKN_SORTSEARCHSUB_PAGE_SUB_BUTTON );
}

//-----------------------------------------------------------------------------
/**
 *	@brief	�t�H�[����ʓo�^
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClactForm( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add )
{
	int i, j;
	
	// �e���W��OAM���쐬����
	for( i=0; i<5; i++ ){
		p_add->mat.y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		p_add->mat.y = (p_add->mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
		for( j=0; j<3; j++ ){
			p_add->mat.x = ZKN_SORTSEARCHSUB_BUTTON_FORM_DEF_X + (j * ZKN_SORTSEARCHSUB_BUTTON_FORM_OFS_X);

			p_add->mat.x <<= FX32_SHIFT;
			p_draw->clact_sub[ (i*3) + j ] = CLACT_AddSimple( p_add );

			CLACT_AnmChg( p_draw->clact_sub[ (i*3) + j ], ZKN_SORTSEARCHSUB_FORM_BUTTON );
		}
	}
}
//----------------------------------------------------------------------------
/**
 *	@brief	�`��OAM�̊G������OAM�쐬
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClactForm_Gra( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i, j;
	
	// �e�{�^����o�^
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_sort_oam_sub2_lzh_NCGR + ZKN_SORTSEARCHSUB_RES_ID,
			NARC_zukan_zkn_list_oam_NCLR + ZKN_SORTSEARCHSUB_RES_ID, 
			NARC_zukan_zkn_sort_oam_sub2_lzh_NCER + ZKN_SORTSEARCHSUB_RES_ID,
			NARC_zukan_zkn_sort_oam_sub2_lzh_NANR + ZKN_SORTSEARCHSUB_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 15;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;


	// �e���W��OAM���쐬����
	for( i=0; i<5; i++ ){
		add.mat.y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		add.mat.y = (add.mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
		for( j=0; j<3; j++ ){
			add.mat.x = ZKN_SORTSEARCHSUB_BUTTON_FORM_DEF_X + (j * ZKN_SORTSEARCHSUB_BUTTON_FORM_OFS_X);

			add.mat.x <<= FX32_SHIFT;
			p_draw->clact_sub_form[ (i*3) + j ] = CLACT_AddSimple( &add );

			switch( (i*3) + j ){
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_CIRCLE:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_CIRCLE_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_HARABAI:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_HARABAI_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_WATER:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_WATER_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_ARM:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_ARM_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_STRAIGHT:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_STRAIGHT_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_TAIL:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_TAIL_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_LEGS:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_LEGS_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_LEGS:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_FOURLEGS_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_WING:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_TWO_WING_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_MANY_LEGS:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_MANY_LEGS_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_COMP:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_COMP_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_LEGS:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_TWO_LEGS_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_WING:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_FOURWING_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_HAITSUKUBARI:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_HAITSUKUBARI_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_NONE:
				CLACT_SetDrawFlag( p_draw->clact_sub_form[ (i*3) + j ], FALSE );
				break;
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��@�O���t�B�b�N�A�N�^�[�j��
 *
 *	@param	p_draw 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDeleteClactForm_Gra( ZKN_SORTSEARCHSUB_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		if( p_draw->clact_sub_form[ i ] ){
			CLACT_Delete( p_draw->clact_sub_form[ i ] );
			p_draw->clact_sub_form[ i ] = NULL;
		}
	}
}



//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�쐬
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddFontOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR res_obj;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;

	// �p���b�g�̃��\�[�X�f�[�^�擾
	// �p���b�g�v���N�V�擾�p
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_glb_draw->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_list_oam_NCLR + ZKN_SORTSEARCHSUB_RES_ID );

	// �������f�[�^�̋��ʕ������쐬
	// ���ʃf�[�^���
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( res_obj, NULL );
	fontoam_init.bg_pri		 = 0;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DSUB;
	fontoam_init.heap		 = heap;

	// ���ʃ{�^���̃t�H���gOAM
	ZknSortSearchSubAddFontCommon( p_draw, &fontoam_init, p_glb_draw->fontoam_sys );


	// �I�����߂̃t�H���gOAM�o�^
	ZknSortSearchSubAddSubFontOam( p_draw, &fontoam_init, p_glb_draw->fontoam_sys, p_draw->local_select, p_draw->local_type_page );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�j��
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDeleteFontOam( ZKN_SORTSEARCHSUB_DRAW* p_draw )
{
	ZknSortSearchSubDeleteFontCommon( p_draw );

	// �I���t�H���gOAM�̔j��
	ZknSortSearchSubDeleteFontSub( p_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�ύX����
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 *	�ύX���ԂƂ��Ă�ZknSortSearchSubChgClact�̌�ɍs��
 *
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubChgFontOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR res_obj;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;

	// �p���b�g�̃��\�[�X�f�[�^�擾
	// �p���b�g�v���N�V�擾�p
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_glb_draw->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_list_oam_NCLR + ZKN_SORTSEARCHSUB_RES_ID );

	// �������f�[�^�̋��ʕ������쐬
	// ���ʃf�[�^���
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( res_obj, NULL );
	fontoam_init.bg_pri		 = 0;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DSUB;
	fontoam_init.heap		 = heap;

	// ���܂ł�FONTOAM�j��
	ZknSortSearchSubDeleteFontSub( p_draw );


	// �o�^
	ZknSortSearchSubAddSubFontOam( p_draw, &fontoam_init, p_glb_draw->fontoam_sys, p_draw->local_select, p_draw->local_type_page );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u�ʃt�H���gOAM�̓o�^
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_fontoam_init	�t�H���gOAM�o�^�f�[�^
 *	@param	fontoam_sys		�t�H���gOAM�V�X�e��
 *	@param	select_type		�I������
 *	@param	local_type_page	���߂̃y�[�W��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddSubFontOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys, int select_type, int local_type_page )
{
	switch( select_type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		ZknSortSearchSubAddFontSort( p_draw, p_fontoam_init, fontoam_sys );
		break;
		
	case ZKN_SORTSEARCH_SELECT_NEME:
		ZknSortSearchSubAddFontName( p_draw, p_fontoam_init, fontoam_sys );
		break;
		
	case ZKN_SORTSEARCH_SELECT_TYPE:
		if( local_type_page == 0 ){
			ZknSortSearchSubAddFontType1( p_draw, p_fontoam_init, fontoam_sys );
		}else{
			ZknSortSearchSubAddFontType2( p_draw, p_fontoam_init, fontoam_sys );
		}
		break;
		
	default:
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���t�H���g�@���ʃ{�^���p
 *
 *	@param	p_draw
 *	@param	p_fontoam_init	�K�{�ް��i�[�ς�
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddFontCommon( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys )
{
	GF_BGL_BMPWIN* win;	// �����񏑂����ݐ�
	int pltt_ofs;	// �p���b�g�A�h���X


	// �p���b�g�]����A�h���X�擾
	pltt_ofs = GetPlttProxyOffset( p_fontoam_init->pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	//-------------------------------------
	//	�Ȃ��
	//=====================================
	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CY );
	ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_SORTSEARCH_03, 0, 0 );
	p_fontoam_init->p_bmp		 = win;
	p_fontoam_init->parent = p_draw->clact[ ZKN_SORTSEARCHSUB_BUTTON_NARABI ];
	p_fontoam_init->x			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
	p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_NARABI ] = ZKN_FONTOAM_Make( p_fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_NARABI ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_PLTOFS );
	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( win );

	//-------------------------------------
	//	�Ȃ܂�
	//=====================================
	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CY );
	ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_SORTSEARCH_00, 0, 0 );
	p_fontoam_init->p_bmp		 = win;
	p_fontoam_init->parent = p_draw->clact[ ZKN_SORTSEARCHSUB_BUTTON_NAME ];
	p_fontoam_init->x			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
	p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_NAME ] = ZKN_FONTOAM_Make( p_fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_NAME ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_PLTOFS );
	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( win );

	//-------------------------------------
	//	����
	//=====================================
	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CY );
	ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_SORTSEARCH_01, 0, 0 );
	p_fontoam_init->p_bmp		 = win;
	p_fontoam_init->parent = p_draw->clact[ ZKN_SORTSEARCHSUB_BUTTON_TYPE ];
	p_fontoam_init->x			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
	p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_TYPE ] = ZKN_FONTOAM_Make( p_fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_TYPE ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_PLTOFS );
	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( win );

	//-------------------------------------
	//�@������
	//=====================================
	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CY );
	ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_SORTSEARCH_02, 0, 0 );
	p_fontoam_init->p_bmp		 = win;
	p_fontoam_init->parent = p_draw->clact[ ZKN_SORTSEARCHSUB_BUTTON_FORM ];
	p_fontoam_init->x			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
	p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_FORM ] = ZKN_FONTOAM_Make( p_fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_FORM ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_PLTOFS );
	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( win );

	//-------------------------------------
	//	����
	//=====================================
	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CY );
	ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_SORTSEARCH_04, 0, 0 );
	p_fontoam_init->p_bmp		 = win;
	p_fontoam_init->parent = p_draw->clact[ ZKN_SORTSEARCHSUB_BUTTON_ACTION ];
	p_fontoam_init->x			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
	p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_ACTION ] = ZKN_FONTOAM_Make( p_fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_ACTION ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_KETTEI_PLTOFS );
	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( win );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���t�H���g�j��
 *
 *	@param	p_draw 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDeleteFontCommon( ZKN_SORTSEARCHSUB_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_NUM; i++ ){
		if( p_draw->p_fontoam[ i ] ){
			ZKN_FONTOAM_Delete( p_draw->p_fontoam[ i ] );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief		�T�u�ʂ̃{�^���t�H���g�ݒ�
 */
//-----------------------------------------------------------------------------
// �j������
static void ZknSortSearchSubDeleteFontSub( ZKN_SORTSEARCHSUB_DRAW* p_draw )
{
	int i;
	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		if( p_draw->p_fontoam_sub[ i ] ){
			ZKN_FONTOAM_Delete( p_draw->p_fontoam_sub[ i ] );
			p_draw->p_fontoam_sub[ i ] = NULL;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	��ă{�^��
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddFontSort( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys )
{
	GF_BGL_BMPWIN* win;	// �����񏑂����ݐ�
	int pltt_ofs;	// �p���b�g�A�h���X
	int i;
	int msg_idx;
	int x;

	// �p���b�g�]����A�h���X�擾
	pltt_ofs = GetPlttProxyOffset( p_fontoam_init->pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUM; i++ ){
		// �r�b�g�}�b�v�E�B���h�E�쐬
		win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
				ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_NARABI_SIZE_CX,
				ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_NARABI_SIZE_CY );
		
		
		switch( i ){
		case ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUMBER:
			msg_idx = ZNK_SORTSEARCH_SORT_00;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X;
			break;
			
		case ZKN_SORTSEARCHSUB_BUTTON_NARABI_AIUEO:
			msg_idx = ZNK_SORTSEARCH_SORT_01;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_6_X;
			break;
			
		case ZKN_SORTSEARCHSUB_BUTTON_NARABI_HEAVY:
			msg_idx = ZNK_SORTSEARCH_SORT_02;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
			
		case ZKN_SORTSEARCHSUB_BUTTON_NARABI_LIGHT:
			msg_idx = ZNK_SORTSEARCH_SORT_03;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
			
		case ZKN_SORTSEARCHSUB_BUTTON_NARABI_TALL:
			msg_idx = ZNK_SORTSEARCH_SORT_04;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
			
		case ZKN_SORTSEARCHSUB_BUTTON_NARABI_SHORT:
			msg_idx = ZNK_SORTSEARCH_SORT_05;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
		}
		
		ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
				NARC_msg_zkn_dat, msg_idx, 0, 0 );
		p_fontoam_init->x			 = x;
		p_fontoam_init->p_bmp		 = win;
		p_fontoam_init->parent = p_draw->clact_sub[ i ];
		p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	
		p_draw->p_fontoam_sub[ i ] = ZKN_FONTOAM_Make( p_fontoam_init );
		FONTOAM_SetPaletteNo( p_draw->p_fontoam_sub[ i ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_OTHER_PLTOFS );
		// �r�b�g�}�b�v�E�B���h�E�j��
		ZKN_FONTOAM_DeleteBmp( win );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���O�{�^��
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddFontName( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys )
{
	GF_BGL_BMPWIN* win;	// �����񏑂����ݐ�
	int pltt_ofs;	// �p���b�g�A�h���X
	int i, j;
	int msg_idx;

	// �p���b�g�]����A�h���X�擾
	pltt_ofs = GetPlttProxyOffset( p_fontoam_init->pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_NAME_NUM; i++ ){
		// �r�b�g�}�b�v�E�B���h�E�쐬
		win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
				ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_NAME_SIZE_CX,
				ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_NAME_SIZE_CY );
		
		
		switch( i ){
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_A:
			msg_idx = ZNK_SORTSEARCH_NAME_01;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_HA:
			msg_idx = ZNK_SORTSEARCH_NAME_06;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_KA:
			msg_idx = ZNK_SORTSEARCH_NAME_02;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_MA:
			msg_idx = ZNK_SORTSEARCH_NAME_07;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_SA:
			msg_idx = ZNK_SORTSEARCH_NAME_03;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_RA:
			msg_idx = ZNK_SORTSEARCH_NAME_09;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_TA:
			msg_idx = ZNK_SORTSEARCH_NAME_04;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_YAWA:
			msg_idx = ZNK_SORTSEARCH_NAME_08;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_NA:
			msg_idx = ZNK_SORTSEARCH_NAME_05;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_NONE:
			msg_idx = ZNK_SORTSEARCH_NAME_00;
			break;
		}
		
		if( msg_idx == ZNK_SORTSEARCH_NAME_00 ){
			for( j=0; j<5; j++ ){
				ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
						NARC_msg_zkn_dat, msg_idx, j * 12, 0 );
			}
		}else{
			ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
					NARC_msg_zkn_dat, msg_idx, 0, 0 );
		}

		p_fontoam_init->x			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_5_X;
		p_fontoam_init->p_bmp		 = win;
		p_fontoam_init->parent		 = p_draw->clact_sub[ i ];
		p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	
		p_draw->p_fontoam_sub[ i ] = ZKN_FONTOAM_Make( p_fontoam_init );
		FONTOAM_SetPaletteNo( p_draw->p_fontoam_sub[ i ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_OTHER_PLTOFS );
		// �r�b�g�}�b�v�E�B���h�E�j��
		ZKN_FONTOAM_DeleteBmp( win );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	����1�{�^��
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddFontType1( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys )
{
	GF_BGL_BMPWIN* win;	// �����񏑂����ݐ�
	int pltt_ofs;	// �p���b�g�A�h���X
	int i, j;
	int msg_idx;
	int x;

	// �p���b�g�]����A�h���X�擾
	pltt_ofs = GetPlttProxyOffset( p_fontoam_init->pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2; i++ ){
		// �r�b�g�}�b�v�E�B���h�E�쐬
		win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
				ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_TYPE1_SIZE_CX,
				ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_TYPE1_SIZE_CY );
		
		
		switch( i ){
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_AKU:
			msg_idx = ZNK_SORTSEARCH_TYPE_15;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_2_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KOORI:
			msg_idx = ZNK_SORTSEARCH_TYPE_05;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_IWA:
			msg_idx = ZNK_SORTSEARCH_TYPE_12;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_2_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_GHOST:
			msg_idx = ZNK_SORTSEARCH_TYPE_13;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_SP:
			msg_idx = ZNK_SORTSEARCH_TYPE_10;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_JIMEN:
			msg_idx = ZNK_SORTSEARCH_TYPE_08;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_BATTLE:
			msg_idx = ZNK_SORTSEARCH_TYPE_06;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_ELEC:
			msg_idx = ZNK_SORTSEARCH_TYPE_03;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KUSA:
			msg_idx = ZNK_SORTSEARCH_TYPE_04;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_2_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_NONE:
			msg_idx = ZNK_SORTSEARCH_NAME_00;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X;
			break;
		}
		
		if( msg_idx == ZNK_SORTSEARCH_NAME_00 ){
			for( j=0; j<4; j++ ){
				ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
						NARC_msg_zkn_dat, msg_idx, j * 12, 0 );
			}
		}else{
			ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
					NARC_msg_zkn_dat, msg_idx, 0, 0 );
		}
		p_fontoam_init->x			 = x;
		p_fontoam_init->p_bmp		 = win;
		p_fontoam_init->parent = p_draw->clact_sub[ i ];
		p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	
		p_draw->p_fontoam_sub[ i ] = ZKN_FONTOAM_Make( p_fontoam_init );
		FONTOAM_SetPaletteNo( p_draw->p_fontoam_sub[ i ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_OTHER_PLTOFS );
		// �r�b�g�}�b�v�E�B���h�E�j��
		ZKN_FONTOAM_DeleteBmp( win );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	����2�{�^��
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddFontType2( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys )
{
	GF_BGL_BMPWIN* win;	// �����񏑂����ݐ�
	int pltt_ofs;	// �p���b�g�A�h���X
	int i, j;
	int msg_idx;
	int x;

	// �p���b�g�]����A�h���X�擾
	pltt_ofs = GetPlttProxyOffset( p_fontoam_init->pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1; i++ ){
		// �r�b�g�}�b�v�E�B���h�E�쐬
		win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
				ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_TYPE2_SIZE_CX,
				ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_TYPE2_SIZE_CY );
		
		
		switch( i ){
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DOKU:
			msg_idx = ZNK_SORTSEARCH_TYPE_07;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_2_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HIKOR:
			msg_idx = ZNK_SORTSEARCH_TYPE_09;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DRAGON:
			msg_idx = ZNK_SORTSEARCH_TYPE_14;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_FIRE:
			msg_idx = ZNK_SORTSEARCH_TYPE_01;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NORMAL:
			msg_idx = ZNK_SORTSEARCH_TYPE_00;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_WATER:
			msg_idx = ZNK_SORTSEARCH_TYPE_02;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_2_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HAGANE:
			msg_idx = ZNK_SORTSEARCH_TYPE_16;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_MUSHI:
			msg_idx = ZNK_SORTSEARCH_TYPE_11;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_2_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NONE:
			msg_idx = ZNK_SORTSEARCH_NAME_00;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X;
			break;
		}
		
		if( msg_idx == ZNK_SORTSEARCH_NAME_00 ){
			for( j=0; j<4; j++ ){
				ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
						NARC_msg_zkn_dat, msg_idx, j * 12, 0 );
			}
		}else{
			ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
					NARC_msg_zkn_dat, msg_idx, 0, 0 );
		}
		p_fontoam_init->x			 = x;
		p_fontoam_init->p_bmp		 = win;
		p_fontoam_init->parent = p_draw->clact_sub[ i ];
		p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	
		p_draw->p_fontoam_sub[ i ] = ZKN_FONTOAM_Make( p_fontoam_init );
		FONTOAM_SetPaletteNo( p_draw->p_fontoam_sub[ i ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_OTHER_PLTOFS );
		// �r�b�g�}�b�v�E�B���h�E�j��
		ZKN_FONTOAM_DeleteBmp( win );
	}
}





//----------------------------------------------------------------------------
/**
 *	@brief	�������s�@������
 *
 *	@param	p_work	�ް����[�N
 *	@param	p_glb	�ް��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoInit( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int select_type = p_work->local_select;
	p_work->do_flag_select = ZKN_SORTSEARCHSUB_DO_FLAG_INIT;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����̎��s����
 *
 *	@param	p_work		�ް����[�N
 *	@param	p_glb		�ް��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoMain( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	// ���ʓ���
	ZknSortSearchSubDoCommon( p_work, p_glb );


	// �I�����ߕʓ���
	ZknSortSearchSubDoSelect( p_work, p_glb, p_work->local_select, p_work->local_type_page  );
}
static void ZknSortSearchSubDoSelect( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int select_type, int type_page )
{
	switch( select_type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		ZknSortSearchSubDoSort( p_work, p_glb );
		break;
		
	case ZKN_SORTSEARCH_SELECT_NEME:
		ZknSortSearchSubDoName( p_work, p_glb );
		break;
		
	case ZKN_SORTSEARCH_SELECT_TYPE:
		if( type_page == 0 ){
			ZknSortSearchSubDoType1( p_work, p_glb );
		}else{
			ZknSortSearchSubDoType2( p_work, p_glb );
		}
		break;

	case ZKN_SORTSEARCH_SELECT_FORM:
		ZknSortSearchSubDoForm( p_work, p_glb );
		break;
		
	default:
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	���ʃ{�^���̎��s
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoCommon( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	switch( p_work->do_flag_common ){
	case ZKN_SORTSEARCHSUB_BUTTON_BACK:
		// �|�P���X�g�ɉ��������ɖ߂�
		ZKN_SortSearchAplReqListFade( p_glb->p_main_apl, FALSE );
		// �{�^����
		Snd_SePlay( ZKN_SND_BUTTON );
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NARABI:
		if( ZKN_SortSearchAplSelectTypeGet( p_glb->p_main_apl ) != ZKN_SORTSEARCH_SELECT_SORT ){
			// ��đI�����[�h��
			ZKN_SortSearchAplSelectTypeSet( p_glb->p_main_apl, ZKN_SORTSEARCH_SELECT_SORT );
			// �{�^����
			Snd_SePlay( ZKN_SND_BUTTON );
		}
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME:
		if( ZKN_SortSearchAplSelectTypeGet( p_glb->p_main_apl ) != ZKN_SORTSEARCH_SELECT_NEME ){
			// �Ȃ܂��I�����[�h��
			ZKN_SortSearchAplSelectTypeSet( p_glb->p_main_apl, ZKN_SORTSEARCH_SELECT_NEME );
			// �{�^����
			Snd_SePlay( ZKN_SND_BUTTON );
		}
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE:
		if( ZKN_SortSearchAplSelectTypeGet( p_glb->p_main_apl ) != ZKN_SORTSEARCH_SELECT_TYPE ){
			// ���ߑI�����[�h��
			ZKN_SortSearchAplSelectTypeSet( p_glb->p_main_apl, ZKN_SORTSEARCH_SELECT_TYPE );
			// �{�^����
			Snd_SePlay( ZKN_SND_BUTTON );
			p_work->type_set_no = ZKN_SORTSEARCH_TYPE1;
		}
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM:
		if( ZKN_SortSearchAplSelectTypeGet( p_glb->p_main_apl ) != ZKN_SORTSEARCH_SELECT_FORM ){
			// �`�I�����[�h��
			ZKN_SortSearchAplSelectTypeSet( p_glb->p_main_apl, ZKN_SORTSEARCH_SELECT_FORM );
			// �{�^����
			Snd_SePlay( ZKN_SND_BUTTON );
		}
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_ACTION:
		if( p_work->req_count <= 1 ){	// �ŏ��̃��N�G�X�g�ɂ����������Ȃ�
			//�@��Ď��s 
			ZKN_SortSearchAplReqListFade( p_glb->p_main_apl, TRUE );
			// �{�^����
			Snd_SePlay( ZKN_SND_BUTTON );
		}
		break;

	default:
		break;
	}
	p_work->do_flag_common = ZKN_SORTSEARCHSUB_DO_FLAG_INIT;
}

//----------------------------------------------------------------------------
/**
 *	@brief	��ă{�^���̎��s
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoSort( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int set_num = 100;
	
	switch( p_work->do_flag_select ){
	case ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUMBER:
		set_num = ZKN_POKELIST_SORT_NORMAL;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NARABI_AIUEO:
		set_num =  ZKN_POKELIST_SORT_GOZYUUON;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NARABI_HEAVY:
		set_num =  ZKN_POKELIST_SORT_GRAM_L;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NARABI_LIGHT:
		set_num =  ZKN_POKELIST_SORT_GRAM_S;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NARABI_TALL:
		set_num =  ZKN_POKELIST_SORT_HIGH_L;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NARABI_SHORT:
		set_num =  ZKN_POKELSIT_SOTT_HIGH_S;
		break;
	default:
		break;
	}
	if( set_num != 100 ){

		if( ZKN_SortSearchAplSortTypeGet( p_glb->p_main_apl ) != set_num ){
			// �{�^����
			Snd_SePlay( ZKN_SND_BUTTON );
			ZKN_SortSearchAplSortTypeSet( p_glb->p_main_apl, set_num );	
		}
	}
	
	p_work->do_flag_select = ZKN_SORTSEARCHSUB_DO_FLAG_INIT; 
}

//----------------------------------------------------------------------------
/**
 *	@brief	���O�{�^���̎��s
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoName( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int set_num = 100;
	
	switch( p_work->do_flag_select ){
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_A:
		set_num = ZKN_POKELIST_SEARCH_NAME_A;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_HA:
		set_num = ZKN_POKELIST_SEARCH_NAME_HA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_KA:
		set_num = ZKN_POKELIST_SEARCH_NAME_KA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_MA:
		set_num = ZKN_POKELIST_SEARCH_NAME_MA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_SA:
		set_num = ZKN_POKELIST_SEARCH_NAME_SA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_RA:
		set_num = ZKN_POKELIST_SEARCH_NAME_RA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_TA:
		set_num = ZKN_POKELIST_SEARCH_NAME_TA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_YAWA:
		set_num = ZKN_POKELIST_SEARCH_NAME_YAWA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_NA:
		set_num = ZKN_POKELIST_SEARCH_NAME_NA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_NONE:
		set_num = ZKN_POKELIST_SEARCH_NAME_NONE;
		break;
	default:
		break;
	}

	if( set_num != 100 ){
		if( ZKN_SortSearchAplNameTypeGet( p_glb->p_main_apl ) !=set_num  ){
			// �{�^����
			Snd_SePlay( ZKN_SND_BUTTON );

			ZKN_SortSearchAplNameTypeSet( p_glb->p_main_apl, set_num );
		}
	}
	p_work->do_flag_select = ZKN_SORTSEARCHSUB_DO_FLAG_INIT; 
}

//----------------------------------------------------------------------------
/**
 *	@brief	����1�{�^���̎��s
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoType1( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int set_num = 100;
	
	switch( p_work->do_flag_select ){
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_AKU:
		set_num = ZKN_POKELIST_SEARCH_TYPE_AKU;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KOORI:
		set_num = ZKN_POKELIST_SEARCH_TYPE_KOORI;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_IWA:
		set_num = ZKN_POKELIST_SEARCH_TYPE_IWA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_GHOST:
		set_num = ZKN_POKELIST_SEARCH_TYPE_GHOST;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_SP:
		set_num = ZKN_POKELIST_SEARCH_TYPE_SP;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_JIMEN:
		set_num = ZKN_POKELIST_SEARCH_TYPE_JIMEN;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_BATTLE:
		set_num = ZKN_POKELIST_SEARCH_TYPE_BATTLE;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_ELEC:
		set_num = ZKN_POKELIST_SEARCH_TYPE_ELECTRIC;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KUSA:
		set_num = ZKN_POKELIST_SEARCH_TYPE_KUSA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_NONE:
		set_num = ZKN_POKELIST_SEARCH_TYPE_NONE;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2:
		p_work->type_page = 1;
		// �{�^����
		Snd_SePlay( ZKN_SND_BUTTON );
		break;
	default:
		break;
	}

	if( set_num != 100 ){
		ZknSortSearchSubDoTypeSetCommon( p_work, p_glb, set_num );
	}
	p_work->do_flag_select = ZKN_SORTSEARCHSUB_DO_FLAG_INIT; 
}

//----------------------------------------------------------------------------
/**
 *	@brief	����2�{�^���̎��s
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoType2( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int set_num = 100;
	
	switch( p_work->do_flag_select ){
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DOKU:
		set_num = ZKN_POKELIST_SEARCH_TYPE_POISON;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HIKOR:
		set_num = ZKN_POKELIST_SEARCH_TYPE_HIKOU;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DRAGON:
		set_num = ZKN_POKELIST_SEARCH_TYPE_DRAGON;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_FIRE:
		set_num = ZKN_POKELIST_SEARCH_TYPE_FIRE;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NORMAL:
		set_num = ZKN_POKELIST_SEARCH_TYPE_NORMAL;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_WATER:
		set_num = ZKN_POKELIST_SEARCH_TYPE_WATER;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HAGANE:
		set_num = ZKN_POKELIST_SEARCH_TYPE_METAL;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_MUSHI:
		set_num = ZKN_POKELIST_SEARCH_TYPE_MUSHI;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NONE:
		set_num = ZKN_POKELIST_SEARCH_TYPE_NONE;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1:
		p_work->type_page = 0;
		// �{�^����
		Snd_SePlay( ZKN_SND_BUTTON );
		break;
	default:
		break;
	}

	if( set_num != 100 ){
		ZknSortSearchSubDoTypeSetCommon( p_work,p_glb, set_num );
	}
	p_work->do_flag_select = ZKN_SORTSEARCHSUB_DO_FLAG_INIT; 
}
static void ZknSortSearchSubDoTypeSetCommon( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int set_num )
{
	if( set_num != ZKN_POKELIST_SEARCH_TYPE_NONE ){

		// �����̒l�ƈ���Ă�����ݒ�
		if( (ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, ZKN_SORTSEARCH_TYPE1 ) != set_num) &&
			(ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, ZKN_SORTSEARCH_TYPE2 ) != set_num) ){
		
			if( ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, p_work->type_set_no ) != set_num ){
				
				ZKN_SortSearchAplTypeTypeSet( p_glb->p_main_apl, set_num, p_work->type_set_no );
				p_work->type_set_no = (p_work->type_set_no + 1) % ZKN_SORTSEARCH_TYPENUM;
				// �{�^����
				Snd_SePlay( ZKN_SND_BUTTON );
			}
		}
	}else{
		// �󔒂ɂ���Ƃ�
		// �󔒈ȊO�������Ă���ق�������������
		if( ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, ZKN_SORTSEARCH_TYPE1 ) != ZKN_POKELIST_SEARCH_TYPE_NONE ){
			ZKN_SortSearchAplTypeTypeSet( p_glb->p_main_apl, set_num, ZKN_SORTSEARCH_TYPE1 );
			// �{�^����
			Snd_SePlay( ZKN_SND_BUTTON );
		}else{
			if( ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, ZKN_SORTSEARCH_TYPE2 ) != ZKN_POKELIST_SEARCH_TYPE_NONE ){
				ZKN_SortSearchAplTypeTypeSet( p_glb->p_main_apl, set_num, ZKN_SORTSEARCH_TYPE2 );
				// �{�^����
				Snd_SePlay( ZKN_SND_BUTTON );
			}
		}
		p_work->type_set_no = ZKN_SORTSEARCH_TYPE1;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�{�^���̎��s
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoForm( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int set_num = 100;
	
	switch( p_work->do_flag_select ){
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_CIRCLE:
		set_num = ZKN_POKELIST_SEARCH_FORM_CIRCLE;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_HARABAI:
		set_num = ZKN_POKELIST_SEARCH_FORM_HARABAI;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_WATER:
		set_num = ZKN_POKELIST_SEARCH_FORM_WATER;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_ARM:
		set_num = ZKN_POKELIST_SEARCH_FORM_ARM;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_STRAIGHT:
		set_num = ZKN_POKELIST_SEARCH_FORM_STRAIGHT;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_TAIL:
		set_num = ZKN_POKELIST_SEARCH_FORM_TAIL;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_LEGS:
		set_num = ZKN_POKELIST_SEARCH_FORM_LEGS;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_LEGS:
		set_num = ZKN_POKELIST_SEARCH_FORM_FOUR_LEGS;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_WING:
		set_num = ZKN_POKELIST_SEARCH_FORM_TWO_WING;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_MANY_LEGS:
		set_num = ZKN_POKELIST_SEARCH_FORM_MANY_LEGS;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_COMP:
		set_num = ZKN_POKELIST_SEARCH_FORM_COMP;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_LEGS:
		set_num = ZKN_POKELIST_SEARCH_FORM_TWO_LEGS;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_WING:
		set_num = ZKN_POKELIST_SEARCH_FORM_FOUR_WING;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_HAITSUKUBARI:
		set_num = ZKN_POKELIST_SEARCH_FORM_HAITSUKUBARI;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_NONE:
		set_num = ZKN_POKELIST_SEARCH_FORM_NONE;
		break;
	default:
		break;
	}

	if( set_num != 100 ){
		if( ZKN_SortSearchAplFormTypeGet( p_glb->p_main_apl ) != set_num ){
			// �{�^����
			Snd_SePlay( ZKN_SND_BUTTON );

			ZKN_SortSearchAplFormTypeSet( p_glb->p_main_apl, set_num );
		}
	}
	p_work->do_flag_select = ZKN_SORTSEARCHSUB_DO_FLAG_INIT; 
}


//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���t�F�[�h�R���g���[��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonFadeCont( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb )
{
	// ���t�F�[�h�����`�F�b�N
	if( p_draw->do_fade == ZKN_SORTSEARCH_SUB_BUTTON_FADE_NONE ){
		
		// ���N�G�X�g����������t�F�[�h�J�n
		if( p_drawglb->button_fade_req > ZKN_SORTSEARCH_SUB_BUTTON_FADE_NONE ){
			p_draw->do_fade = p_drawglb->button_fade_req;
			p_draw->do_fade_seq = 0;
			p_draw->end_flag = p_drawglb->button_fade;
			*p_draw->end_flag = FALSE;

			// ���N�G�X�g�ް�������
			p_drawglb->button_fade_req = ZKN_SORTSEARCH_SUB_BUTTON_FADE_NONE;
		}
	}else{

		// �t�F�[�h���s
		ZknSortSearchSubButtonFade( p_draw );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���t�F�[�h����
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonFade( ZKN_SORTSEARCHSUB_DRAW* p_draw )
{
	BOOL check;


	// ���s�t�F�[�h���߂�NONE�Ȃ�Ȃɂ����Ȃ�
	if( p_draw->do_fade == ZKN_SORTSEARCH_SUB_BUTTON_FADE_NONE ){
		return ;
	}
	
	switch( p_draw->do_fade_seq ){
	case 0:
		// ���쏉����
		if( p_draw->do_fade == ZKN_SORTSEARCH_SUB_BUTTON_FADE_IN ){
			ZKN_UTIL_MoveReq( &p_draw->fade_work, 0, 16, 0, 0, ZKN_SORTSEARCHSUB_BUTTON_FADE_SYNC );
		}else{
			ZKN_UTIL_MoveReq( &p_draw->fade_work, 16, 0, 0, 0, ZKN_SORTSEARCHSUB_BUTTON_FADE_SYNC );
		}

		G2S_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE, GX_BLEND_PLANEMASK_BG2, p_draw->fade_work.x, 16 - p_draw->fade_work.x );
		p_draw->do_fade_seq ++;
		break;

	case 1:
		check = ZKN_UTIL_MoveMain( &p_draw->fade_work );	
		G2S_ChangeBlendAlpha( p_draw->fade_work.x, 16 - p_draw->fade_work.x );
		if( check == TRUE ){
			// OAM�𔼓�������
			if( p_draw->do_fade == ZKN_SORTSEARCH_SUB_BUTTON_FADE_IN ){
				G2S_BlendNone();
			}
			
			*p_draw->end_flag = TRUE;
			p_draw->do_fade_seq = 0;
			p_draw->do_fade = ZKN_SORTSEARCH_SUB_BUTTON_FADE_NONE;
		}
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	��Ļ��OAMӰ�ސݒ�p�b�N�֐�
 *
 *	@param	p_draw
 *	@param	mode
 *	@param	select_type
 *	@param	type_page 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonFadeOamModeSet_Pack( ZKN_SORTSEARCHSUB_DRAW* p_draw, int mode, int select_type, int type_page )
{
	if( select_type == ZKN_SORTSEARCH_SELECT_TYPE ){
		if( type_page == 0 ){
			// TYPE1
			ZknSortSearchSubButtonFadeOamModeSet_Type1Ver( p_draw, mode );
		}else{
			// TYPE2
			ZknSortSearchSubButtonFadeOamModeSet_Type2Ver( p_draw, mode );
		}
	}else{
		ZknSortSearchSubButtonFadeOamModeSet( p_draw, mode );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h����I�u�W�F�����[�h�ݒ�
 *
 *	@param	p_draw
 *	@param	mode 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonFadeOamModeSet( ZKN_SORTSEARCHSUB_DRAW* p_draw, int mode )
{
	int i;

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		if( p_draw->clact_sub[i] ){
			CLACT_ObjModeSet( p_draw->clact_sub[i], mode );
		}
		if( p_draw->p_fontoam_sub[i] ){
			FONTOAM_ObjModeSet( p_draw->p_fontoam_sub[i]->p_fontoam, mode );
		}
		if( p_draw->clact_sub_form[i] ){
			CLACT_ObjModeSet( p_draw->clact_sub_form[i], mode );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�������ݒ�@���߂P�o�[�W����
 *
 *	@param	p_draw
 *	@param	mode 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonFadeOamModeSet_Type1Ver( ZKN_SORTSEARCHSUB_DRAW* p_draw, int mode )
{
	int i;

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		if( i != ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2 ){
			if( p_draw->clact_sub[i] ){
				CLACT_ObjModeSet( p_draw->clact_sub[i], mode );
			}
			if( p_draw->p_fontoam_sub[i] ){
				FONTOAM_ObjModeSet( p_draw->p_fontoam_sub[i]->p_fontoam, mode );
			}
		}
	}
}
// ���߂Q�o�[�W����
static void ZknSortSearchSubButtonFadeOamModeSet_Type2Ver( ZKN_SORTSEARCHSUB_DRAW* p_draw, int mode )
{
	int i;

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		if( i != ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1 ){
			if( p_draw->clact_sub[i] ){
				CLACT_ObjModeSet( p_draw->clact_sub[i], mode );
			}
			if( p_draw->p_fontoam_sub[i] ){
				FONTOAM_ObjModeSet( p_draw->p_fontoam_sub[i]->p_fontoam, mode );
			}
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	��ăt�F�[�h�V�X�e��
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	cp_glb			�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubSortFadeSys( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_GLB* cp_glb )
{
	// ���쏈��������
	if( ZKN_SortSearchAplFadeModeCountGet( cp_glb->p_main_apl ) == ZKN_SORTSEARCH_FADECOUNT_MAX ){
		
		if( ZKN_SortSearchAplFadeModeGet( cp_glb->p_main_apl ) == ZKN_SORTSEARCH_FADEIN ){
			ChangeBrightnessRequest( ZKN_SORTSEARCH_FADECOUNT_MAX,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_SUB_DISPLAY );
		}else if( ZKN_SortSearchAplFadeModeGet( cp_glb->p_main_apl ) == ZKN_SORTSEARCH_FADEOUT ){
			ChangeBrightnessRequest( ZKN_SORTSEARCH_FADECOUNT_MAX,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, PLANEMASK_ALL, MASK_SUB_DISPLAY );
		}
	}
}

