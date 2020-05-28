//============================================================================================
/**
 * @file	pms_input_prv.h
 * @bfief	�ȈՉ�b���͉�ʁiprivate �w�b�_�j
 * @author	taya
 * @date	06.01.24
 */
//============================================================================================
#ifndef __PMS_INPUT_PRV_H__
#define __PMS_INPUT_PRV_H__

#include "application\pms_input.h"
#include "application\pms_input_data.h"
#include "pms_input_param.h"

//------------------------------------------------------
/**
 * �`��R�}���h
 */
//------------------------------------------------------
enum {
	VCMD_INIT,					///< ��ʏ����\�z
	VCMD_QUIT,					///< �`��I��
	VCMD_FADEIN,				///< �t�F�[�h�C��

	VCMD_UPDATE_EDITAREA,		///< �ҏW�̈�X�V
	VCMD_EDITAREA_TO_BUTTON,	///< �ҏW�̈悩��R�}���h�{�^����
	VCMD_BUTTON_TO_EDITAREA,	///< �R�}���h�{�^������ҏW�̈��
	VCMD_EDITAREA_TO_CATEGORY,	///< �ҏW�̈悩��J�e�S���I����
	VCMD_CATEGORY_TO_EDITAREA,	///< �J�e�S���I������ҏW�̈��
	VCMD_CATEGORY_TO_WORDWIN,	///< �J�e�S���I������P��I����
	VCMD_WORDWIN_TO_CATEGORY,	///< �P��I������J�e�S���I���ցi�P��I���L�����Z����j
	VCMD_WORDTIN_TO_EDITAREA,	///< �P��I������ҏW�̈�ցi�P�ꌈ���j
	VCMD_WORDTIN_TO_BUTTON,		///< �P��I������R�}���h�{�^���ցi�P�ꌈ���j

	VCMD_MOVE_EDITAREA_CURSOR,	///< �ҏW�̈�J�[�\���ړ�
	VCMD_MOVE_BUTTON_CURSOR,	///< �{�^���J�[�\���ړ�
	VCMD_MOVE_CATEGORY_CURSOR,	///< �J�e�S���I���J�[�\���ړ�
	VCMD_MOVE_WORDWIN_CURSOR,	///< �P��I���J�[�\���ړ�
	VCMD_SCROLL_WORDWIN,		///< �P��E�B���h�E�X�N���[��

	VCMD_DISP_MESSAGE_DEFAULT,	///< �������b�Z�[�W�\��
	VCMD_DISP_MESSAGE_OK,		///< ����ł����ł����H���b�Z�[�W�����j���[
	VCMD_DISP_MESSAGE_CANCEL,	///< ��߂܂����H���b�Z�[�W�����j���[
	VCMD_DISP_MESSAGE_WARN,		///< �Ȃɂ����Ƃ΂�����Ă��������I���b�Z�[�W
	VCMD_MOVE_MENU_CURSOR,		///< ���j���[�J�[�\���ړ�
	VCMD_ERASE_MENU,			///< ���j���[�\������

	VCMD_CHANGE_CATEGORY_MODE_DISABLE,	///< �J�e�S�����[�h�ؑւ��A�J�e�S���I����Ԃֈڍs���Ȃ�
	VCMD_CHANGE_CATEGORY_MODE_ENABLE,	///< �J�e�S�����[�h�ؑւ��A�J�e�S���I����Ԃֈڍs����

	VCMD_BUTTON_UP_HOLD,
	VCMD_BUTTON_DOWN_HOLD,
	VCMD_BUTTON_UP_RELEASE,
	VCMD_BUTTON_DOWN_RELEASE,


};


//------------------------------------------------------
/**
 * �{�^���A�N�^�[���C�A�E�g
 */
//------------------------------------------------------
enum {

	BUTTON_GROUP_SCRN_XPOS = 3,
	BUTTON_GROUP_SCRN_YPOS = 3,
	BUTTON_INITIAL_SCRN_XPOS = 3,
	BUTTON_INITIAL_SCRN_YPOS = 14,

	MODEBUTTON_SCRN_WIDTH = 11,
	MODEBUTTON_SCRN_HEIGHT = 7,

	BUTTON_GROUP_TOUCH_TOP		= BUTTON_GROUP_SCRN_YPOS*8,
	BUTTON_GROUP_TOUCH_BOTTOM	= BUTTON_GROUP_TOUCH_TOP+(MODEBUTTON_SCRN_HEIGHT*8),
	BUTTON_GROUP_TOUCH_LEFT		= BUTTON_GROUP_SCRN_XPOS*8,
	BUTTON_GROUP_TOUCH_RIGHT	= BUTTON_GROUP_TOUCH_LEFT+(MODEBUTTON_SCRN_WIDTH*8),

	BUTTON_INITIAL_TOUCH_TOP	= BUTTON_INITIAL_SCRN_YPOS*8,
	BUTTON_INITIAL_TOUCH_BOTTOM	= BUTTON_INITIAL_TOUCH_TOP+(MODEBUTTON_SCRN_HEIGHT*8),
	BUTTON_INITIAL_TOUCH_LEFT	= BUTTON_INITIAL_SCRN_XPOS*8,
	BUTTON_INITIAL_TOUCH_RIGHT	= BUTTON_INITIAL_TOUCH_LEFT+(MODEBUTTON_SCRN_WIDTH*8),



	BUTTON_UP_XPOS = 192,
	BUTTON_UP_YPOS = 56,
	BUTTON_DOWN_XPOS = 192,
	BUTTON_DOWN_YPOS = 136,

	BUTTON_ARROW_TOUCH_WIDTH = 32,
	BUTTON_ARROW_TOUCH_HEIGHT = 32,

	BUTTON_UP_TOUCH_TOP		= BUTTON_UP_YPOS-(BUTTON_ARROW_TOUCH_HEIGHT/2),
	BUTTON_UP_TOUCH_BOTTOM	= BUTTON_UP_YPOS+(BUTTON_ARROW_TOUCH_HEIGHT/2),
	BUTTON_UP_TOUCH_LEFT	= BUTTON_UP_XPOS-(BUTTON_ARROW_TOUCH_WIDTH/2),
	BUTTON_UP_TOUCH_RIGHT	= BUTTON_UP_XPOS+(BUTTON_ARROW_TOUCH_WIDTH/2),


	BUTTON_DOWN_TOUCH_TOP		= BUTTON_DOWN_YPOS-(BUTTON_ARROW_TOUCH_HEIGHT/2),
	BUTTON_DOWN_TOUCH_BOTTOM	= BUTTON_DOWN_YPOS+(BUTTON_ARROW_TOUCH_HEIGHT/2),
	BUTTON_DOWN_TOUCH_LEFT	= BUTTON_DOWN_XPOS-(BUTTON_ARROW_TOUCH_WIDTH/2),
	BUTTON_DOWN_TOUCH_RIGHT	= BUTTON_DOWN_XPOS+(BUTTON_ARROW_TOUCH_WIDTH/2),



};






//------------------------------------------------------
/**
 * ���C�����[�N�^�錾
 */
//------------------------------------------------------
typedef struct _PMS_INPUT_WORK	PMS_INPUT_WORK;

//------------------------------------------------------
/**
 * �`�惏�[�N�^�錾
 */
//------------------------------------------------------
typedef struct _PMS_INPUT_VIEW	PMS_INPUT_VIEW;

//------------------------------------------------------
/**
 * �^�X�N�v���C�I���e�B
 */
//------------------------------------------------------
enum {
	TASKPRI_MAIN,
	TASKPRI_VIEW_COMMAND,
	TASKPRI_VIEW_MAIN,
};

enum {
	VTASKPRI_COMMAND,
	VTASKPRI_MAIN,
};

enum {
	PMSIV_MSG_GUIDANCE,
	PMSIV_MSG_WARN_INPUT,
	PMSIV_MSG_CONFIRM_DECIDE,
	PMSIV_MSG_CONFIRM_CANCEL,
};

enum {
	BUTTON_POS_DECIDE,
	BUTTON_POS_CANCEL,
};

enum {
	CATEGORY_MODE_GROUP,
	CATEGORY_MODE_INITIAL,
};

//------------------------------------------------------
/**
 * �V�X�e���֘A�֐��v���g�^�C�v
 */
//------------------------------------------------------
extern u32 PMSI_GetInputMode( const PMS_INPUT_WORK* wk );
extern u32 PMSI_GetSentenceType( const PMS_INPUT_WORK* wk );
extern u32 PMSI_GetCategoryMode( const PMS_INPUT_WORK* wk );
extern PMS_WORD  PMSI_GetEditWord( const PMS_INPUT_WORK* wk, int pos );
extern STRBUF* PMSI_GetEditSourceString( const PMS_INPUT_WORK* wk, u32 heapID );
extern u32 PMSI_GetGuidanceType( const PMS_INPUT_WORK* wk );
extern u32 PMSI_GetEditAreaCursorPos( const PMS_INPUT_WORK* wk );
extern u32 PMSI_GetButtonCursorPos( const PMS_INPUT_WORK* wk );
extern u32 PMSI_GetCategoryCursorPos( const PMS_INPUT_WORK* wk );
extern u32 PMSI_GetCategoryWordMax( const PMS_INPUT_WORK* wk );
extern void PMSI_GetCategoryWord( const PMS_INPUT_WORK* wk, u32 word_num, STRBUF* buf );
extern u32 PMSI_GetWordWinCursorPos( const PMS_INPUT_WORK* wk );
extern int PMSI_GetWordWinScrollVector( const PMS_INPUT_WORK* wk );
extern BOOL PMSI_GetWordWinUpArrowVisibleFlag( const PMS_INPUT_WORK* wk );
extern BOOL PMSI_GetWordWinDownArrowVisibleFlag( const PMS_INPUT_WORK* wk );
extern int PMSI_GetTalkWindowType( const PMS_INPUT_WORK* wk );
extern u32 PMSI_GetMenuCursorPos( const PMS_INPUT_WORK* wk );

//------------------------------------------------------
/**
 * �`��֘A�֐��v���g�^�C�v
 */
//------------------------------------------------------
extern PMS_INPUT_VIEW*  PMSIView_Create(const PMS_INPUT_WORK* wk, const PMS_INPUT_DATA* dwk);
extern void PMSIView_Delete( PMS_INPUT_VIEW* vwk );
extern void PMSIView_SetCommand( PMS_INPUT_VIEW* vwk, int cmd );
extern BOOL PMSIView_WaitCommand( PMS_INPUT_VIEW* vwk, int cmd );
extern BOOL PMSIView_WaitCommandAll( PMS_INPUT_VIEW* vwk );
extern u32 PMSIView_GetSentenceEditPosMax( PMS_INPUT_VIEW* wk );

#endif
