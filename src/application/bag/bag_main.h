//============================================================================================
/**
 * @file	bag_main.h
 * @brief	�o�b�O��ʏ���
 * @author	Hiroyuki Nakamura
 * @date	06.04.17
 */
//============================================================================================
#ifndef BAG_MAIN_H
#define BAG_MAIN_H
#undef GLOBAL
#ifdef BAG_MAIN_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


#include "itemtool/myitem.h"

//============================================================================================
//	�萔��`
//============================================================================================
#define	BAG_LARGE_POKE_MAX		( BAG_NORMAL_ITEM_MAX )		// �ő�T�C�Y�̃|�P�b�g

#define	P_ICON_SIZ_X	( 10 )		// �|�P�b�g�A�C�R����X�T�C�Y
#define	P_ICON_SIZ_Y	( 10 )		// �|�P�b�g�A�C�R����Y�T�C�Y
#define	P_ICON_DEF_PX	( 6 )		// �|�P�b�g�A�C�R���̕\��X���W
#define	P_ICON_DEF_SX	( 90 )		// �|�P�b�g�A�C�R���̕\���̈��X�T�C�Y


// �E�B���h�E�C���f�b�N�X
enum {
	WIN_LIST = 0,
	WIN_INFO,
	WIN_POCKET,
	WIN_MENU_INFO,
	WIN_MENU_INFO2,
	WIN_P_ICON,
	WIN_TALK,

	WIN_SALE_NUM,
	WIN_GOLD,
	WIN_SUB,

	WIN_PORUTO,

	WIN_MAX
};


enum {
	ADD_WIN_MENU = 0,

	ADD_WIN_MAX
};

// ���j���[����
enum {
	BAG_MENU_TSUKAU = 0,	// ����
	BAG_MENU_ORIRU,			// �����
	BAG_MENU_MIRU,			// �݂�
	BAG_MENU_UMERU,			// ���߂�
	BAG_MENU_HIRAKU,		// �Ђ炭
	BAG_MENU_SUTERU,		// ���Ă�
	BAG_MENU_TOUROKU,		// �Ƃ��낭
	BAG_MENU_KAIZYO,		// ��������
	BAG_MENU_MOTASERU,		// ��������
	BAG_MENU_TAGUWOMIRU,	// �^�O���݂�
	BAG_MENU_KETTEI,		// �����Ă�
	BAG_MENU_YAMERU,		// ��߂�

	BAG_MENU_MAX
};

// �Z���A�N�^�[�Ǘ��ԍ�
enum {
	ACT_BAG = 0,
	ACT_POKE_CURSOR,
	ACT_POKE_ARROW_LEFT,
	ACT_POKE_ARROW_RIGHT,
	ACT_LIST_SEL_CURSOR,
	ACT_LIST_SEL_CHANGE,

	ACT_BUTTON_ANM,
	ACT_ITEMICON,

	ACT_NUM_ARROW_UP,
	ACT_NUM_ARROW_DOWN,

	ACT_TYPE,
	ACT_KIND,

	BAG_ACT_MAX
};


// �y�[�W�؂�ւ��p���[�N
typedef struct {
	u8	next;			// ���̃y�[�W
	u8	move;			// �ړ�����

	u8	cur_seq;		// �|�P�b�g�J�[�\���ړ��V�[�P���X
	u8	cur_cnt;		// �|�P�b�g�J�[�\���ړ��J�E���^

	u8	tp_seq;			// �^�b�`�p�l�������V�[�P���X
	u8	tp_cnt;			// �^�b�`�p�l�������J�E���^
	u8	tp_button;		// �{�^���ԍ�
	u8	tp_chg:4;		// �Ⴄ�{�^���������ꂽ��
	u8	tp_push:3;		// �^�b�`�p�l���ɐG��Ă��邩
	u8	tp_mode:1;		// �^�b�`�p�l���ł̕ύX���ǂ���
}PAGE_CHG_WORK;



// �o�b�O�ŎQ�Ƃ���f�[�^
typedef struct {
	MINEITEM * item;	// �Q�Ƃ���A�C�e���f�[�^
	u16	cur;			// �J�[�\���ʒu
	u16	scr;			// �X�N���[���J�E���^
//	u16	pos;			// ���ݒl ( cur + scr )
	u8	type;			// �|�P�b�g�^�C�v
	u8	max;			// �A�C�e���ő吔
}POCKET_DATA;

struct _BAG_DATA {
	SAVEDATA * sv;		// �Z�[�u�f�[�^

	POCKET_DATA	p_data[BAG_POKE_MAX];	// �|�P�b�g���Ƃ̃f�[�^
	u8	p_now;							// ���݂̃|�P�b�g
	u8	mode;							// �o�b�O��ʂ̖���
	u16	ret_item;						// �I���A�C�e��
	u16	ret_mode;						// �I�����[�h

	void * bag_cursor;		// �J�[�\���ʒu�̊O���L���̈�

	void * icwk;			// �A�C�e���g�p�`�F�b�N���[�N

	u8	use_poke;			// �A�C�e�����g�p�����|�P����

	u8	fnote_sale_cnt;		// �`���m�[�g�p��������

	u16	cycle_flg:1;		// ���]�ԃt���O ( 0=off, 1=on )
	u16	map_mode:15;		// �}�b�v���[�h
};

typedef struct {
	u8	req;
	u8	mv;
	u8	next;
	u8	cnt;
	fx32 tbl[8];	// �y�[�W�J�[�\���ړ��e�[�u��
}POCKET_CURSOR_MOVE;

typedef struct {
	GF_BGL_INI * bgl;						// BGL�f�[�^

	GF_BGL_BMPWIN	win[WIN_MAX];			// BMP�E�B���h�E�f�[�^�i�ʏ�j
	GF_BGL_BMPWIN	add_win[ADD_WIN_MAX];	// BMP�E�B���h�E�f�[�^�i�ǉ��j

	BAG_DATA * dat;							// �o�b�O�f�[�^

	MYITEM * myitem;		// �莝���A�C�e���f�[�^
	MYSTATUS * myst;		// �v���[���[�f�[�^
	CONFIG * cfg;			// �R���t�B�O�f�[�^

	ARCHANDLE * gra_h;		// �O���t�B�b�N�̃A�[�J�C�u�n���h��

	CATS_SYS_PTR	csp;
	CATS_RES_PTR	crp;
	CATS_ACT_PTR	cap[BAG_ACT_MAX];

	NUMFONT * num_font;			// 8x8�t�H���g
	MSGDATA_MANAGER * msg_man;	// ���b�Z�[�W�f�[�^�}�l�[�W��
	WORDSET * wset;				// �P��Z�b�g

	MSGDATA_MANAGER * item_man;	// ���b�Z�[�W�f�[�^�}�l�[�W��
	MSGDATA_MANAGER * waza_man;	// ���b�Z�[�W�f�[�^�}�l�[�W��

	STRBUF * menu_str[BAG_MENU_MAX];	// ���j���[����
	BMP_MENULIST_DATA * md;				// BMP���j���[�f�[�^
	BMPMENU_WORK * mw;					// BMP���j���[���[�N

	BMPLIST_WORK * lw;			// BMP���X�g�f�[�^
	BMP_MENULIST_DATA * ld;		// BMP���X�g�f�[�^
	STRBUF * itemname[BAG_LARGE_POKE_MAX];					// �A�C�e�����W�J�ꏊ

	STRBUF * expb;			// ���b�Z�[�W�W�J�ꏊ

	STRBUF * num_str1;		// ���\���E"x"
	STRBUF * num_str2;		// ���\���E��

	STRBUF * pocket_name[BAG_POKE_MAX];	// �|�P�b�g���W�J�ꏊ�|�C���^
	u8	p_max;				// �|�P�b�g��

	u8	sex;				// ����

	u8	midx;				// ���b�Z�[�W�C���f�b�N�X

	u8	p_icon_gx;			// �y�[�W�O�̃A�C�R����X���W
	u8	p_icon_sx;			// �A�C�R���̊Ԋu

	PAGE_CHG_WORK	page_work;
	fx32 p_mv_tbl[8];		// �y�[�W�J�[�\���ړ��e�[�u��

	POCKET_CURSOR_MOVE	pcmv;
	u8	p_next;

	u8	info_put;			// �A�C�e�����Z�b�g

	u8	irekae_flg;
	u8	irekae_pos;
	u32	irekae_param;

	u8	arrow_mv;
	u8	arrow_cnt;

	u8	se_type;		// ���X�g�I������SE

	u8	sub_seq;		// �T�u�V�[�P���X
	u32	use_func;		// �o�b�O���g�p�֐�

	s16	sel_num;		// ���I���F�I��
	u16	sel_max;		// ���I���F�ő吔
	u32	sel_price;		// �I�����ꂽ�A�C�e���̒l�i

	u8	enter_anm_flg;	// �T�u��ʌ���{�^���A�j��
	u8	enter_anm_cnt;	// �T�u��ʌ���{�^���J�E���g

	u8	wheel_flg;
//	s16	wheel_pos;
	s32	wheel_pos;
	s16	wheel_mv;
	s16	wheel_rot;
	s16	wheel_start;
	u16	backup_tpx;
	u16	backup_tpy;

}BAG_WORK;

typedef int (*pBagFunc)(BAG_WORK *);	// �֐��|�C���^�^


#define	POS_GET_ID		( 0 )		// �A�C�e���ԍ�
#define	POS_GET_NUM		( 1 )		// ������


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ���݂̃|�P�b�g�̎w��ʒu�̃A�C�e�����擾
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 * @param	pos		�ʒu
 * @param	id		�擾ID
 *
 * @return	�w��ʒu�̃A�C�e��
 *
 * @li	id = POS_GET_ID : �A�C�e���ԍ�
 * @li	id = POS_GET_NUM : ������
 */
//--------------------------------------------------------------------------------------------
extern u16 Bag_PosItemGet( BAG_WORK * wk, u16 pos, u16 id );


extern const u32 Bag_MenuParamGet( u32 menu_num );



#undef GLOBAL
#endif	/* BAG_MAIN_H */
