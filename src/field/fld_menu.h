//============================================================================================
/**
 * @file	fld_menu.h
 * @brief	�t�B�[���h���j���[�����p�w�b�_
 * @author	Hiroyuki Nakamura
 */
//============================================================================================
#ifndef FLD_MENU_H
#define FLD_MENU_H

#include "field/itemuse.h"
#include "field/field_skill.h"
#include "field_skill_local.h"

#undef GLOBAL
#ifdef FLD_MENU_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================
#define	FIELD_MENU_MAX		( 7 )					// ���ڍő吔
#define	FLDMENU_CLACT_MAX	( FIELD_MENU_MAX + 1 )	// �Z���A�N�^�[�ő吔�i���ځ{�J�[�\���j

#define FLD_MENU_VANISH_ZUKAN	( 0x00000001 )		// �}�ӂ��B��
#define FLD_MENU_VANISH_PLIST	( 0x00000002 )		// �|�P�������X�g���B��
#define FLD_MENU_VANISH_BAG		( 0x00000004 )		// �o�b�O���B��
#define FLD_MENU_VANISH_TRCARD	( 0x00000008 )		// �g���[�i�[�J�[�h���B��
#define FLD_MENU_VANISH_REPORT	( 0x00000010 )		// ���|�[�g���B��
#define FLD_MENU_VANISH_CONFIG	( 0x00000020 )		// �ݒ���B��
#define FLD_MENU_VANISH_CLOSE	( 0x00000040 )		// �u����v���B��
#define FLD_MENU_VANISH_CHAT	( 0x00000080 )		// �`���b�g���B��
#define FLD_MENU_VANISH_RETIRE	( 0x00000100 )		// ���^�C�A���B��


// �t�B�[���h���j���[���[�N
typedef struct {
	GF_BGL_BMPWIN	win;		// BMP�E�B���h�E�i���j���[�j
	GF_BGL_BMPWIN	ball_win;	// BMP�E�B���h�E�i�{�[�����j

	BMPMENU_WORK * mw;
	BMP_MENULIST_DATA * ld;	// BMP���X�g�f�[�^
	u16	pos;				// ���j���[�ʒu
	u16	seq;				// �V�[�P���X
	u32	ret;				// �߂�l

	u8	list[ FIELD_MENU_MAX ];		// ���j���[���X�g

	FIELD_CLACT	fcat;		// �Z���A�N�^�[�ݒ�f�[�^
	CATS_ACT_PTR	cap[FLDMENU_CLACT_MAX];
	u32	clact_max;			// �Z���A�N�^�[�o�^��

	u32	ev_flg;				// ���j���[����t���O
	u32	union_flg;			// ���j�I�����[���t���O

	GMEVENT_FUNC	app_func;

	ITEMCHECK_WORK	item_check;		// �A�C�e���g�p�`�F�b�N���[�N
	SKILLCHECK_WORK	skill_check;	// �Z�g�p�`�F�b�N���[�N

	void * app_wk;			// �ėp���[�N�|�C���^
	void * tmp_wk;			// �ėp���[�N�|�C���^�Q�i�e��ʂ��s��������ꍇ�Ɏg�p�j
}FLD_MENU;

// �t�B�[���h���j���[�V�[�P���X
enum {
	FLD_MENU_SEQ_INIT = 0,		// ������
	FLD_MENU_SEQ_SELECT,		// ���j���[�I��

	FLD_MENU_SEQ_APP_CALL,		// �A�v���Ăяo��
	FLD_MENU_SEQ_APP_WAIT,		// �A�v���I���҂�

	FLD_MENU_SEQ_REPORT_CALL,
	FLD_MENU_SEQ_REPORT_WAIT,

	FLD_MENU_SEQ_SHINKA_INIT,	// �i����ʌĂяo��
	FLD_MENU_SEQ_SHINKA_MAIN,	// �i����ʑ҂�

	FLD_MENU_SEQ_BLACK_IN_END,
	FLD_MENU_SEQ_BLACK_IN_END_WAIT,

	FLD_MENU_SEQ_BLACK_IN_EVCHG,
	FLD_MENU_SEQ_BLACK_IN_EVCHG_WAIT,

	FLD_MENU_SEQ_AGAIN,
	FLD_MENU_SEQ_END,
	FLD_MENU_SEQ_WAIT_BLACK_IN,
	FLD_MENU_SEQ_END_NOMENU,
};


// ���[����ʂ̃��[�h
#define	FM_MAIL_MODE_VIEW		( 3 )		// ���[��������
#define	FM_MAIL_MODE_READ		( 2 )		// ���[����ǂ�
#define	FM_MAIL_MODE_MAKE_LIST	( 0 )		// ���[������������i�|�P�������X�g����j
#define	FM_MAIL_MODE_MAKE_BAG	( 1 )		// ���[������������i�o�b�O����j


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
GLOBAL void FieldMenuInit( struct _FIELDSYS_WORK * repw );
GLOBAL void FieldMenuInitUnion( struct _FIELDSYS_WORK * repw );
GLOBAL void FieldMenuInitVS( FIELDSYS_WORK * repw );
GLOBAL void FieldMenuEvChg( FIELDSYS_WORK * repw );
GLOBAL void FieldMenuEvChgUnion( FIELDSYS_WORK * repw );

GLOBAL void FldMenu_AppWaitFuncSet( FLD_MENU * wk, void * func );

GLOBAL BOOL FldMenu_PokeListEnd( GMEVENT_CONTROL * event );

GLOBAL void * FieldMenu_MailWorkMake( u16 item, u8 mode, u8 poke_pos );

GLOBAL BOOL FldMenu_MailEnd( GMEVENT_CONTROL * event );
GLOBAL BOOL FldMenu_TownMapEnd( GMEVENT_CONTROL * event );
GLOBAL BOOL FldMenu_FantasyNoteEnd( GMEVENT_CONTROL * event );
GLOBAL BOOL FldMenu_PorutoCaseEnd( GMEVENT_CONTROL * event );
GLOBAL BOOL FldMenu_FriendBookEnd( GMEVENT_CONTROL * event );
GLOBAL BOOL FldMenu_SorawotobuEnd( GMEVENT_CONTROL * event );

//==============================================================================
//	�f�[�^
//==============================================================================
GLOBAL const u8 PST_PageTbl_Normal[];


#undef GLOBAL
#endif	/* FLD_MENU_H */
