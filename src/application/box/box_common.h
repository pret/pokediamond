//============================================================================================
/**
 * @file	box_common.h
 * @brief	�{�b�N�X�����ʋ��L�w�b�_
 * @author	taya
 * @date	2005.09.05
 */
//============================================================================================
#ifndef __BOX_COMMON_H__
#define __BOX_COMMON_H__

#include "gflib\msg_print.h"	// STRCODE�̂���
#include "gflib\strbuf.h"
#include "system\wordset.h"
#include "system\msgdata.h"
#include "system\buflen.h"
#include "itemtool\item.h"
#include "msgdata\msg_boxmes.h"
#include "poketool\boxdata.h"
#include "poketool\pokeparty.h"

#include "application\box.h"

#include "box_sound_def.h"

//----------------------------------------------------------------------
/**
 *  �`��R�}���h
 */
//----------------------------------------------------------------------
enum {
	CMD_INIT,
	CMD_NORMAL_IN,			///< ��ʍ\�z��̃t�F�[�h�C���G�t�F�N�g�i�t�B�[���h�������j
	CMD_FADEIN,				///< ����ʂ��畜�A���鎞�̃t�F�[�h�C��
	CMD_FADEOUT,			///< ����ʈȍ~�O�̃t�F�[�h�A�E�g

	CMD_TRAY_CHANGE,		///< �{�b�N�X�g���C�؂�ւ�
	CMD_CURSOR_MOVE,		///< �J�[�\���ړ�
	CMD_STATUS_UPDATE,		///< �X�e�[�^�X�\���|�P�����̐؂�ւ�
	CMD_STATUS_MARK_UPDATE,	///< �X�e�[�^�X�\���|�P�����̃}�[�L���O�\���̂ݍX�V
	CMD_STATUS_CLEAR,		///< �X�e�[�^�X�\�������N���A

	CMD_POKE_CATCH,			///< �|�P��������
	CMD_POKE_PUT,			///< �|�P��������
	CMD_POKE_CHANGE,		///< �|�P�������ꂩ����
	CMD_AZUKERU_CATCHPOKE,	///< �|�P������������i����ł�|�P�����j
	CMD_AZUKERU_POINTPOKE,	///< �|�P������������i�w���Ă���|�P�����j
	CMD_NIGASU_CATCHPOKE,	///< �|�P�����ɂ����i����ł�|�P�����j
	CMD_NIGASU_TRAYPOKE,	///< �|�P�����ɂ����i�{�b�N�X�g���C�̃|�P�����j
	CMD_NIGASU_PARTYPOKE,	///< �|�P�����ɂ����i�莝���̃|�P�����j
	CMD_ITEMINFO_DISP,		///< �A�C�e�������̕\��
	CMD_ITEMINFO_CLEAR,		///< �A�C�e�������̏���
	CMD_ITEM_WITHDRAW,		///< �A�C�e���u��������v
	CMD_ITEM_SET,			///< �A�C�e���u��������v�i����ł���A�C�e������������j
	CMD_ITEM_SWAP,			///< �A�C�e���u�Ƃ肩����v
	CMD_ITEM_POKE_UPDATE,	///< �A�C�e�������󋵂ɉ����ă|�P�����������\���؂�ւ�
	CMD_ITEMICON_RESTORE,	///< �A�C�e���A�C�R�����o�b�O�ɖ߂��G�t�F�N�g

	CMD_MSG_DISP,			///< ���b�Z�[�W�̂�
	CMD_MENU_DISP,			///< ���b�Z�[�W�����j���[
	CMD_MSG_CLEAR,			///< ���b�Z�[�W�����j���[�N���A
	CMD_MENU_CLEAR,			///< ���j���[�̂݃N���A

	CMD_MENUCURSOR_UPDATE,	///< ���j���[�J�[�\���ʒu�X�V
	CMD_MENUMARK_UPDATE,	///< ���j���[�}�[�N��ԍX�V�i�}�[�L���O���j���[�̂݁j
	CMD_JUMPWIN_DISP,
	CMD_JUMPWIN_UPDATE,
	CMD_JUMPWIN_CLEAR,

	CMD_WALLPAPER_CHANGE,	///< �J�����g�ǎ��ύX
	CMD_BUTTON_PUSH_ACTION,	///< �w�J�[�\���������̃{�^���������悤�ȓ���
	CMD_PARTYTRAY_OPEN,		///< �莝���g���C�J��
	CMD_PARTYTRAY_CLOSE,	///< �莝���g���C����

	CMD_PARTYICON_CLOSEUP,	///< �莝���g���C�̃A�C�R���󂫋l�߁i�͂񂾌�E����������j
	CMD_PARTYLASTICON_CLOSEUP,	///< �莝���g���C�̃A�C�R���󂫋l�߁i�u������j
	CMD_ICON_LIMITMODE_UPDATE,	///< �A�C�R���̍i�荞�݃��[�h�\���X�V

	CMD_SUBLCD_MODECHANGE,
	CMD_SUBLCD_MOVEICON,
	CMD_SUBLCD_MARKICON_UPDATE,	///< �i�荞�݃A�C�R���̕\���X�V

	CMD_CHANGE_EXPERTMODE,		///< ����Ă�l���[�h�̐؂�ւ�
	CMD_START_AREASELECT,		///< �|�P�����A�C�R���͈̔͑I���J�n
	CMD_END_AREASELECT,			///< �|�P�����A�C�R���͈̔͑I���I��
	CMD_UPDATE_AREASELECT,		///< �|�P�����A�C�R���͈̔͑I���X�V
	CMD_CATCH_AREASELECT_POKE,	///< �͈͑I�𒆂̃|�P�����A�C�R����͂�

	CMD_SWITCH_COMPARE_SIDE,			///< �悳����ׂ̍X�V����T�C�h��ύX
	CMD_SWITCH_COMPARE_SIDE_BY_BUTTON,	///< �悳����ׂ̍X�V����T�C�h��ύX�i�{�^�������G�t�F�N�g�𔺂��j
	CMD_CHANGE_COMPARE_PAGE,

	CMD_BOXCLOSE,
};

//----------------------------------------------------------------------
/**
 *  �^�X�N�v���C�I���e�B
 */
//----------------------------------------------------------------------
enum BOXTASK{
	TASKPRI_VIEW_COMMAND_SUB,
	TASKPRI_VIEW_COMMAND,
	TASKPRI_VIEW_TRANS,
};

enum BOX_VTASK {
	TASKPRI_V_SUB,
	TASKPRI_V_MAIN,
};

//----------------------------------------------------------------------
/**
 *  ���j���[�h�c
 */
//----------------------------------------------------------------------
typedef enum {
	BOXMENU_TRAY_JUMP,		///< �{�b�N�X�̐؂�ւ�
	BOXMENU_TRAY_WALLPAPER,	///< �ǎ��ύX
	BOXMENU_TRAY_NAME,		///< �{�b�N�X���ύX
	BOXMENU_TRAYMENU_QUIT,	///< �g���C���j���[�u��߂�v
	BOXMENU_WP_CATEGORY1,	///< �ǎ��J�e�S���P
	BOXMENU_WP_CATEGORY2,	///< �ǎ��J�e�S���Q
	BOXMENU_WP_CATEGORY3,	///< �ǎ��J�e�S���R
	BOXMENU_WP_CATEGORY4,	///< �ǎ��J�e�S���S
	BOXMENU_WP_CATEGORY_EX1,///< �ǎ��J�e�S���B���P
	BOXMENU_WP_CATEGORY_EX2,///< �ǎ��J�e�S���B���Q
	BOXMENU_WP_NAME1_1,		///< �ǎ����P-�P
	BOXMENU_WP_NAME1_2,		///< �ǎ����P-�Q
	BOXMENU_WP_NAME1_3,		///< �ǎ����P-�R
	BOXMENU_WP_NAME1_4,		///< �ǎ����P-�S
	BOXMENU_WP_NAME2_1,		///< �ǎ����Q-�P
	BOXMENU_WP_NAME2_2,		///< �ǎ����Q-�Q
	BOXMENU_WP_NAME2_3,		///< �ǎ����Q-�R
	BOXMENU_WP_NAME2_4,		///< �ǎ����Q-�S
	BOXMENU_WP_NAME3_1,		///< �ǎ����R-�P
	BOXMENU_WP_NAME3_2,		///< �ǎ����R-�Q
	BOXMENU_WP_NAME3_3,		///< �ǎ����R-�R
	BOXMENU_WP_NAME3_4,		///< �ǎ����R-�S
	BOXMENU_WP_NAME4_1,		///< �ǎ����S-�P
	BOXMENU_WP_NAME4_2,		///< �ǎ����S-�Q
	BOXMENU_WP_NAME4_3,		///< �ǎ����S-�R
	BOXMENU_WP_NAME4_4,		///< �ǎ����S-�S
	BOXMENU_WP_NAME_EX_1,	///< �ǎ����B���P
	BOXMENU_WP_NAME_EX_2,	///< �ǎ����B���Q
	BOXMENU_WP_NAME_EX_3,	///< �ǎ����B���R
	BOXMENU_WP_NAME_EX_4,	///< �ǎ����B���S
	BOXMENU_WP_NAME_EX_5,	///< �ǎ����B���T
	BOXMENU_WP_NAME_EX_6,	///< �ǎ����B���U
	BOXMENU_WP_NAME_EX_7,	///< �ǎ����B���V
	BOXMENU_WP_NAME_EX_8,	///< �ǎ����B���W
	BOXMENU_POKE_TUKAMU,	///< �|�P�����u���ށv
	BOXMENU_POKE_OKU,		///< �|�P�����u�����ɂ����v
	BOXMENU_POKE_IREKAERU,	///< �|�P�����u���ꂩ����v
	BOXMENU_POKE_YOUSU,		///< �|�P�����u�悤�����݂�v
	BOXMENU_POKE_TURETEIKU,	///< �|�P�����u��Ă����v
	BOXMENU_POKE_AZUKERU,	///< �|�P�����u��������v
	BOXMENU_POKE_MOTIMONO,	///< �|�P�����u�������́v
	BOXMENU_POKE_MARKING,	///< �|�P�����u�}�[�L���O�v
	BOXMENU_POKE_NIGASU,	///< �|�P�����u�ɂ����v
	BOXMENU_POKEMENU_QUIT,	///< �|�P�������j���[�u��߂�v
	BOXMENU_MARKING_DECIDE,	///< �}�[�L���O�u�����Ă��v
	BOXMENU_MARKING_CANCEL,	///< �}�[�L���O�u��߂�v�i�L�����Z���j
	BOXMENU_ITEM_SET,		///< �A�C�e���u��������v
	BOXMENU_ITEM_WITHDRAW,	///< �A�C�e���u��������v
	BOXMENU_ITEM_INFO,		///< �A�C�e���u���߂��v
	BOXMENU_ITEM_SWAP,		///< �A�C�e���u�Ƃ肩����v
	BOXMENU_ITEM_TO_BAG,	///< �A�C�e���u�o�b�O�ցv
	BOXMENU_ITEM_QUIT,		///< �A�C�e���u��߂�v
	BOXMENU_COMPARE_HOLD_LEFT,	///< �悳����ׁu�Ђ���ɂ��Ă��v
	BOXMENU_COMPARE_HOLD_RIGHT,	///< �悳����ׁu�݂��ɂ��Ă��v
	BOXMENU_YES,			///< �͂�
	BOXMENU_NO,				///< ������

	BOXMENU_MARK1,
	BOXMENU_MARK2,
	BOXMENU_MARK3,
	BOXMENU_MARK4,
	BOXMENU_MARK5,
	BOXMENU_MARK6,
}BOX_MENU_ID;


enum {
	BOX_MARK_MAX = 6,	// BOXMENU_MARK1�`6�Ɛ������킹��
};

//----------------------------------------------------------------------
/**
 *  ���C�����[�N�^��`
 */
//----------------------------------------------------------------------
typedef struct _BOXAPP_WORK  BOXAPP_WORK;

//----------------------------------------------------------------------
/**
 *  �`�惏�[�N�^��`
 */
//----------------------------------------------------------------------
typedef struct _BOXAPP_VIEW_WORK  BOXAPP_VIEW_WORK;

//----------------------------------------------------------------------
/**
 *  �J�[�\���ړ��G���A
 */
//----------------------------------------------------------------------
enum CURSOR_AREA {
	CURSOR_AREA_TRAY,			///< �g���C
	CURSOR_AREA_PARTY,			///< �莝���E�B���h�E
	CURSOR_AREA_TRAY_TAB,		///< �g���C�̃^�u
	CURSOR_AREA_PARTY_BUTTON,	///< �w�Ă����|�P�����x�̃{�^��
	CURSOR_AREA_EXIT_BUTTON,	///< �w�Ƃ���x�{�^��
};

//----------------------------------------------------------------------
/**
 *  �i�荞�݃��[�h�A�C�R��ID
 */
//----------------------------------------------------------------------
enum {
	LIMITMODE_ICON_ALLOFF,
	LIMITMODE_ICON_ITEM,
	LIMITMODE_ICON_MARK1,
	LIMITMODE_ICON_MARK2,
	LIMITMODE_ICON_MARK3,
	LIMITMODE_ICON_MARK4,
	LIMITMODE_ICON_MARK5,
	LIMITMODE_ICON_MARK6,

	LIMITMODE_ICON_MAX,
};

//----------------------------------------------------------------------
/**
 *  �i�荞�݃��[�h�r�b�g�t���O
 */
//----------------------------------------------------------------------
enum {
	LIMITMODE_BIT_OFF = 0x0000,
	LIMITMODE_BIT_ITEM = 0x0001,
	LIMITMODE_BIT_MARK1 = 0x0002,
	LIMITMODE_BIT_MARK2 = 0x0004,
	LIMITMODE_BIT_MARK3 = 0x0008,
	LIMITMODE_BIT_MARK4 = 0x0010,
	LIMITMODE_BIT_MARK5 = 0x0020,
	LIMITMODE_BIT_MARK6 = 0x0040,
};

//----------------------------------------------------------------------
/**
 *  �|�P�������ݏ��
 */
//----------------------------------------------------------------------
enum {
	CURSOR_CATCH_NONE = 0x01,		///< ����ł��Ȃ�
	CURSOR_CATCH_SINGLE = 0x02,		///< �P�̂ł���ł���
	CURSOR_CATCH_AREA_POINT = 0x04,	///< �͈͑I���ł���ł��āA�|�P�������J�[�\���̒����ɂ�����
	CURSOR_CATCH_AREA_FREE = 0x08,	///< �͈͑I���ł���ł��āA�|�P�������J�[�\���̒����ɂȂ����

	CURSOR_CATCH_AREA_MASK = (CURSOR_CATCH_AREA_POINT | CURSOR_CATCH_AREA_FREE),
	CUROSR_CATCH_STATUS_HOLD_MASK = (CURSOR_CATCH_SINGLE | CURSOR_CATCH_AREA_POINT ),
	
	
};

//----------------------------------------------------------------------
/**
 *  �T�uLCD�\�����
 */
//----------------------------------------------------------------------
typedef enum {
	SUBLCD_STATE_NORMAL,	// �ʏ펞
	SUBLCD_STATE_TRAY,		// �g���C�I��
	SUBLCD_STATE_MARK,		// �}�[�N�I��
}DISP_STATE;

//----------------------------------------------------------------------
/**
 *  ���̂��萔
 */
//----------------------------------------------------------------------
enum {
	TRAY_XPOS_MAX = BOX_MAX_COLUMN-1,
	TRAY_YPOS_MAX = BOX_MAX_RAW-1,

	CURSOR_PARTYTRAY_CLOSEBUTTON_POS = TEMOTI_POKEMAX,
};

//----------------------------------------------------------------------
/**
 *  �X�e�[�^�X�\�����邽�߂̃|�P�����f�[�^
 */
//----------------------------------------------------------------------
typedef struct {
	void*	poke_data;
	u16		monsno;
	u16		itemno;
	u16		zukan_no;
	u8		level;
	u8		mark;
	u8		type1;	// �^�C�v���Ă̂́u�݂��v�Ƃ��u�͂��ˁv�Ƃ��B
	u8		type2;	// �A�C�R���\������̂ŕ�����͕s�v�B
	u8		sex;
	u8		tamago_flag;
	u8		update_flag;

	STRBUF*	nickname;
	STRBUF*	monsname;
	STRBUF*	itemname;
	STRBUF*	character;
	STRBUF*	ability;

}BOXAPP_STATUS_POKE;


//----------------------------------------------------------------------
/**
 *  ������חp�|�P�����f�[�^
 */
//----------------------------------------------------------------------
enum {
	BOXAPP_COMPARE_SIDE_LEFT,
	BOXAPP_COMPARE_SIDE_RIGHT,
};
enum {
	BOXAPP_COMPARE_PAGE_STATUS,
	BOXAPP_COMPARE_PAGE_CONDITION,
	BOXAPP_COMPARE_PAGE_SKILL,

	BOXAPP_COMPARE_PAGE_MAX,
};

typedef struct {
	void*	poke_data;
	u16		monsno;
	u8		tamago_flag;
	u8		form_number;

	// ���̕��т͕ς�����_��
	u16		level;
	u16		hp_max;
	u16		attack;
	u16		defence;
	u16		sp_attack;
	u16		sp_defence;
	u16		agility;

	u16		style;
	u16		beauty;
	u16		cute;
	u16		clever;
	u16		strong;

	u16		skill[4];

	STRBUF*	nickname;
	STRBUF*	character;

}BOXAPP_COMPARE_POKE_STATUS;

typedef struct {
	u8		updateSide;
	u8		page;
	u8		updateSideFlag[2];
	BOOL	pageButtonPushFlag;

	BOXAPP_COMPARE_POKE_STATUS      status[2];

}BOXAPP_COMPARE;

//----------------------------------------------------------------------
/**
 *  �J�[�\����ԃf�[�^
 */
//----------------------------------------------------------------------
typedef struct {
	void*	point_poke;			///< �w���Ă���|�P����

	u8   area;					///< �{�b�N�X�g���C�A�莝���g���C�A�Ƃ���{�^����
	s8   tray_xpos;				///< �{�b�N�X�g���C���ł̂w�ʒu
	s8   tray_ypos;				///< �{�b�N�X�g���C���ł̂x�ʒu
	s8   tray_pos;				///< �{�b�N�X�g���C���ł̃f�[�^�ʒu

	s8   partytray_pos;			///< �莝���g���C���ł̃f�[�^�ʒu
	s8   partytray_prev_area;	///< �莝���g���C���ֈȍ~����܂��� area 

	u8  poke_point_flag;		///< �|�P�������w���Ă���t���O
	u8  poke_catch_flag;		///< �|�P������͂�ł���t���O

}BOXAPP_CURSOR;

//----------------------------------------------------------------------
/**
 *  ����ł�|�P�����̃f�[�^
 */
//----------------------------------------------------------------------
typedef struct {
	POKEMON_PASO_PARAM*		ppp;	///< �͂ݒ��|�P�f�[�^
	u8			areaStartX;			///< �͈͑I���J�n�w���W�i�g���C���ʒu�j
	u8			areaStartY;			///< �͈͑I���J�n�x���W�i�g���C���ʒu�j
	u8			areaEndX;			///< �͈͑I���I���w���W�i�g���C���ʒu�j
	u8			areaEndY;			///< �͈͑I���I���x���W�i�g���C���ʒu�j

	u8			areaPokeCount;
	u8			areaTopPos;
	u8			areaSpaceCatchFlag;			///< �͈͑I�����A�󔒈ʒu��͂�
	u8			fromPartyFlag;				///< �莝���ɂ����|�P������͂�
	s8			areaPokePos[BOX_MAX_POS];	///< �g���C���̂ǂ̈ʒu����擾�����|�P�����������Ă���

}BOXAPP_CATCH_POKE;


//----------------------------------------------------------------------
/**
 *  �\�����̃g���C�f�[�^
 */
//----------------------------------------------------------------------
typedef struct {
	u8			number;		///< �\�����g���C�i���o�[
	u8			wallPaper;	///< ���̕ǎ��i���o�[
	STRBUF*		name;
}BOXAPP_TRAY;

//----------------------------------------------------------------------
/**
 * ���j���[���f�[�^
 */
//----------------------------------------------------------------------
#define BOXAPP_MENU_ELEMS_MAX	(8)
typedef struct {
	BOX_MENU_ID	id[ BOXAPP_MENU_ELEMS_MAX ];
	u8			pos;		///< �I�����Ă��郁�j���[�ʒu
	u8			cnt;		///< �o�^����Ă��郁�j���[��
	u8			mark;		///< �}�[�L���O���
	u8			type;		///< �\���^�C�v�i���ݖ��g�p�j
}BOXAPP_MENU;

//----------------------------------------------------------------------
/**
 *  �{�b�N�X�I���E�B���h�E�f�[�^
 */
//----------------------------------------------------------------------
typedef struct {
	u32		center_trayno;		///< ���S�̃g���C�i���o�[
}BOXAPP_JUMPWIN;

//----------------------------------------------------------------------
/**
 *  �T�uLCD�\���f�[�^
 */
//----------------------------------------------------------------------
typedef struct {
	u8		state;				///< �\�����
	u8      limit_pos;			///< �i�肱�݃��[�h�A�C�R���ʒu
	u8		pos;				///< �g���C���[�h�A�C�R���ʒu
	s16		move;				///< �ړ���
}BOXAPP_SUBLCD;

//----------------------------------------------------------------------
/**
 *  �{�b�N�X�V�X�e���f�[�^
 */
//----------------------------------------------------------------------
typedef struct {
	u8		boxMode;			///< �{�b�N�X���샂�[�h�i��������E��Ă����E������E�ǂ����j
	u8		expertModeFlag;		///< ����Ă�l���[�h�t���O
	u16		limitModeBitFlag;	///< �i�荞�݃��[�h�r�b�g�t���O
}BOXAPP_SYSTEM;


//----------------------------------------------------------------------
/**
 *  �{�b�N�X�`��p�p�����[�^
 *
 *  �������� box.c �����삵�Aboxv.c �ȉ��̕`��֐��Q�͎Q�Ƃ̂ݍs���B
 */
//----------------------------------------------------------------------
typedef struct {
	const BOX_DATA*			boxData;
	const POKEPARTY*		partyData;
	BOXAPP_CURSOR			cursor;
	BOXAPP_CATCH_POKE		catchPoke;
	BOXAPP_TRAY				tray;
	BOXAPP_SYSTEM			system;
	BOXAPP_STATUS_POKE		statusPoke;
	BOXAPP_MENU				menu;
	BOXAPP_JUMPWIN			jumpWin;
	BOXAPP_SUBLCD			subLCD;
	BOXAPP_COMPARE			compare;
	u32						message_id;
	u16						azukeruTrayNumber;
	u16						catch_item;
}BOXAPP_VPARAM;



extern BOOL BoxAppView_Init( BOXAPP_VIEW_WORK** vwk, const BOXAPP_VPARAM* vpara, const BOXAPP_WORK* mainwk );
extern void BoxAppView_SetCommand( BOXAPP_VIEW_WORK* vwk,  u32 cmd );
extern BOOL BoxAppView_WaitCommand( BOXAPP_VIEW_WORK* vwk, u32 cmd );
extern BOOL BoxAppView_WaitCommandAll( BOXAPP_VIEW_WORK* vwk );
extern void BoxAppView_Main( BOXAPP_VIEW_WORK* wk );
extern void BoxAppView_End( BOXAPP_VIEW_WORK* wk );

/*===================================================================================*/
/*  �`��p�����[�^�֘A                                                               */
/*===================================================================================*/
extern MSGDATA_MANAGER* BoxApp_GetMsgManager( const BOXAPP_WORK* wk );
extern const WORDSET* BoxApp_GetWordSet( const BOXAPP_WORK* wk );
extern u32 BoxAppVPara_GetBoxMode( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetCursorArea( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetCursorTrayPosX( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetCursorTrayPosY( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetCursorTrayPos( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetCursorPartyPos( const BOXAPP_VPARAM* vpara );
extern BOOL BoxAppVPara_GetCursorPointPokeFlag( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetCursorCatchPokeFlag(const BOXAPP_VPARAM* vpara );
extern BOOL BoxAppVPara_GetCursorCatchPokeFromPartyFlag( const BOXAPP_VPARAM* vpara );
extern BOOL BoxAppVPara_GetCursorStatusEnableFlag(const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetTrayBoxNumber( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetMessageID( const BOXAPP_VPARAM* vpara );
extern POKEMON_PASO_PARAM* BoxAppVPara_GetStatusPokePara( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetStatusPokeItemNumber( const BOXAPP_VPARAM* vpara );
extern const BOXAPP_STATUS_POKE* BoxAppVpara_GetStatusPokeData( const BOXAPP_VPARAM* vpara );
extern const BOXAPP_TRAY* BoxAppVpara_GetTrayData( const BOXAPP_VPARAM* vpara );
extern const BOX_DATA* BoxAppVPara_GetBoxData( const BOXAPP_VPARAM* vpara );
extern s32 BoxAppVPara_GetSubLCDMove( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetSubLCDPos( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetSubLCDLimitPos( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetJumpWinCenterTrayNumber( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetLimitModeBitFlag( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetStatusPokeMarkBit( const BOXAPP_VPARAM* vpara );
extern BOOL BoxAppVPara_GetExpertModeFlag( const  BOXAPP_VPARAM* vpara );
extern void BoxAppVPara_GetAreaSelectParam( const BOXAPP_VPARAM* vpara, u32* left, u32* right, u32* top, u32* bottom );
extern BOOL BoxAppVPara_CheckAreaSelectSinglePoke( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetAreaSelectCursorTopPos( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetAreaSelectIconOfsPos( const BOXAPP_VPARAM* vpara, u32 idx );
extern BOOL BoxAppVPara_GetAreaSelectCatchSpaceFlag( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetCatchItemNumber( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetInfoItemNumber( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetCompareUpdateSide( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetComparePage( const BOXAPP_VPARAM* vpara );
extern const BOXAPP_COMPARE_POKE_STATUS* BoxAppVPara_GetCompareStatus( const BOXAPP_VPARAM* vpara, int side );
extern BOOL BoxAppVPara_GetCompareUpdatedSideFlag( const BOXAPP_VPARAM* vpara, int side );
extern BOOL BoxAppVPara_GetComparePageButtonPushFlag( const BOXAPP_VPARAM* vpara );
extern int BoxApp_GetTalkWinType( const BOXAPP_WORK* wk );
extern BOOL BoxAppVPara_GetStatusPokeTamagoFlag( const BOXAPP_VPARAM* vpara );


/*===================================================================================*/
/*  �|�P�����𓦂������̃��U�`�F�b�N�֘A                                             */
/*===================================================================================*/
extern BOOL BoxApp_ReleaseWazaCheckDone( const BOXAPP_WORK* mainWk );
extern BOOL BoxApp_ReleaseWazaCheckOK( const BOXAPP_WORK* mainWk );

#endif
