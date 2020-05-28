//============================================================================================
/**
 * @file	plist_sys.h
 * @brief	�|�P�������X�g�֘A�t�@�C���̋��ʒ�`
 * @author	Hiroyuki Nakamura
 * @date	05.09.29
 */
//============================================================================================
#ifndef PLIST_SYS_H
#define PLIST_SYS_H


#define	PL_HP_DOTTO_MAX		( 48 )	// HP�Q�[�W�̃h�b�g�T�C�Y

#define	PL_PANEL_HPGAGE_CLEAR_CHR	( 0x17 )	// �p�l������HP�Q�[�WX�ʒu
#define	PL_PANEL_HPGAGE_PX			( 6 )		// �p�l������HP�Q�[�WX�ʒu
#define	PL_PANEL_HPGAGE_PY			( 3 )		// �p�l������HP�Q�[�WY�ʒu
#define	PL_PANEL_HPGAGE_SX			( 9 )		// �p�l������HP�Q�[�WX�T�C�Y
#define	PL_PANEL_HPGAGE_SY			( 1 )		// �p�l������HP�Q�[�WY�T�C�Y

#define	PL_MENU_WIN_CGX		( 1 )
#define	PL_TALK_WIN_CGX		( PL_MENU_WIN_CGX + MENU_WIN_CGX_SIZ )

#define	TMP_MSG_SIZE		( 256 )		// ���b�Z�[�W�W�J�̈�T�C�Y�i�������j
#define	MENU_STR_SIZE		( 32 )		// ���j���[������W�J�̈�T�C�Y�i�������j

// �V�[�P���X
enum {
	SEQ_IN = 0,
	SEQ_MAIN,
	SEQ_MENU,

	SEQ_MENUWAZA_ERR,		// �Z�g�p�G���[

	SEQ_ITEMUSE_SEL,
	SEQ_ITEMUSE_WAIT,

	SEQ_WAZAMENU_SEL,		// �Z�I�����j���[

	SEQ_ITEMUSE_ALLDEATHRCV,	// �S�̕m����

	// �o�b�O����́u��������v
	SEQ_ITEMSET_SEL,
	SEQ_ITEMSET_YN_INIT,
	SEQ_ITEMSET_YN_MAIN,
	SEQ_ITEMSET_WAIT,

	SEQ_MAILSET_END,

	SEQ_ITEM_MENU,
	SEQ_ITEM_MENU_SET_RET,	// �o�b�O����߂�
	SEQ_ITEM_MENU_GET,

	SEQ_ITEMGET_END,

	SEQ_WAZASET_SEL,		// �Z�o��
	SEQ_WAZASET_RET_SET,	// �Z�o���F�Y��Ċo����

	SEQ_BTLIN_ERR,			// �퓬�Q���G���[

	SEQ_MSG_WAIT,		// ���b�Z�[�W�E�F�C�g
	SEQ_ENDTRG_WAIT,	// �g���K�[�E�F�C�g -> �I��
	SEQ_YESNO_INIT,		// �͂��E�������\��
	SEQ_YESNO_MAIN,		// �͂��E�������I��

	SEQ_ROW_SEL,
	SEQ_FUNC_WAIT,

	SEQ_MILKNOMI,		// �~���N�̂݁E�^�}�S����

	SEQ_OUT_SET,
	SEQ_OUT,
};

// BG�p���b�g
enum {
	PAL_FONT = 0,
	PAL_BG,

	PAL_PANEL_0 = PL_PANEL_PAL_START,
	PAL_PANEL_1,
	PAL_PANEL_2,
	PAL_PANEL_3,
	PAL_PANEL_4,
	PAL_PANEL_5,

	PAL_TALK_FONT = 13,
	PAL_MENU_WIN,
	PAL_TALK_WIN
};

// BMP�E�B���h�E�C���f�b�N�X
enum {
	WIN_POKE1_NAME = 0,
	WIN_POKE1_LV,
	WIN_POKE1_HP,
	WIN_POKE1_HPBAR,
	WIN_POKE1_COMM,
	WIN_POKE2_NAME,
	WIN_POKE2_LV,
	WIN_POKE2_HP,
	WIN_POKE2_HPBAR,
	WIN_POKE2_COMM,
	WIN_POKE3_NAME,
	WIN_POKE3_LV,
	WIN_POKE3_HP,
	WIN_POKE3_HPBAR,
	WIN_POKE3_COMM,
	WIN_POKE4_NAME,
	WIN_POKE4_LV,
	WIN_POKE4_HP,
	WIN_POKE4_HPBAR,
	WIN_POKE4_COMM,
	WIN_POKE5_NAME,
	WIN_POKE5_LV,
	WIN_POKE5_HP,
	WIN_POKE5_HPBAR,
	WIN_POKE5_COMM,
	WIN_POKE6_NAME,
	WIN_POKE6_LV,
	WIN_POKE6_HP,
	WIN_POKE6_HPBAR,
	WIN_POKE6_COMM,

	WIN_ENTER,			// �u�����Ă��v
	WIN_EXIT,			// �u���ǂ�v

	WIN_S_MSG,			// �P�s���b�Z�[�W
	WIN_M_MSG,			// �P�s���b�Z�[�W�i���j���[�\�����j
	WIN_L_MSG,			// �Q�s���b�Z�[�W�i�ʏ�j
	WIN_ITEM_MENU,		// �A�C�e�����j���[
	WIN_WAZA_MENU,		// �Z���j���[

	WIN_MAX
};

// �ǉ�BMP�E�B���h�E�C���f�b�N�X
enum {
	ADD_WIN_MENU = 0,

	ADD_WIN_MAX
};

// OBJ��`
enum {
	PLIST_ACT_BALL1 = 0,
	PLIST_ACT_BALL2,
	PLIST_ACT_BALL3,
	PLIST_ACT_BALL4,
	PLIST_ACT_BALL5,
	PLIST_ACT_BALL6,
	PLIST_ACT_CURSOR1,
	PLIST_ACT_CURSOR2,
	PLIST_ACT_ENTER,
	PLIST_ACT_EXIT,

	PLIST_ACT_ST1,
	PLIST_ACT_ST2,
	PLIST_ACT_ST3,
	PLIST_ACT_ST4,
	PLIST_ACT_ST5,
	PLIST_ACT_ST6,

	PLIST_ACT_ITEM1,
	PLIST_ACT_ITEM2,
	PLIST_ACT_ITEM3,
	PLIST_ACT_ITEM4,
	PLIST_ACT_ITEM5,
	PLIST_ACT_ITEM6,

	PLIST_ACT_CB1,
	PLIST_ACT_CB2,
	PLIST_ACT_CB3,
	PLIST_ACT_CB4,
	PLIST_ACT_CB5,
	PLIST_ACT_CB6,

	PLIST_ACT_BUTTON_EF,

	PLIST_ACT_MAX
};

enum {
	MENU_ROW = 0,		// mes_pokelist_05_01	�Ȃ�т���
	MENU_STATUS,		// mes_pokelist_05_02	�悳���݂�
	MENU_ITEM,			// mes_pokelist_05_03	��������
	MENU_ITEM_S,		// mes_pokelist_05_03	�������̃��j���[�F��������
	MENU_ITEM_G,		// mes_pokelist_05_03	�������̃��j���[�F��������
	MENU_MAIL,			// mes_pokelist_05_04	���[��
	MENU_MAIL_R,		// mes_pokelist_05_05	���[�����@���
	MENU_MAIL_G,		// mes_pokelist_05_06	���[�����@�Ƃ�
	MENU_AZUKERU,		// mes_pokelist_05_07	��������
	MENU_CANCEL,		// mes_pokelist_05_08	��߂�
	MENU_CHANGE,		// mes_pokelist_05_09	���ꂩ����
	MENU_BATTLE_IN,		// mes_pokelist_05_10	���񂩂���i�퓬�Q���I���j
	MENU_OUT,			// mes_pokelist_05_11	���񂩂��Ȃ�
	MENU_CONTEST_IN,	// mes_pokelist_05_10	���񂩂���i�R���e�X�g�Q���j
	MENU_KAPSEL_SET,	// mes_pokelist_05_22	�Z�b�g����

	MENU_W_IAIGIRI,		// �Z�F����������
	MENU_W_SORAWOTOBU,	// �Z�F������Ƃ�
	MENU_W_NAMINORI,	// �Z�F�Ȃ݂̂�
	MENU_W_KAIRIKI,		// �Z�F�����肫
	MENU_W_KIRIBARAI,	// �Z�F����΂炢
	MENU_W_IWAKUDAKI,	// �Z�F���킭����
	MENU_W_TAKINOBORI,	// �Z�F�����̂ڂ�
	MENU_W_ROCKCLIMB,	// �Z�F���b�N�N���C��

	MENU_W_FLASH,		// �Z�F�t���b�V��
	MENU_W_TELEPORT,	// �Z�F�e���|�[�g
	MENU_W_ANAWOHORU,	// �Z�F���Ȃ��ق�
	MENU_W_AMAIKAORI,	// �Z�F���܂�������
	MENU_W_OSYABERI,	// �Z�F������ׂ�
	MENU_W_MILKNOMI,	// �Z�F�~���N�̂�
	MENU_W_TAMAGOUMI,	// �Z�F�^�}�S����

	MENU_STR_MAX = MENU_W_IAIGIRI+4
};


typedef int (*STRCV_FUNC)(void*);
typedef int (*YESNO_FUNC)(void*);

// �͂��E���������[�N
typedef struct {
	YESNO_FUNC	yes;
	YESNO_FUNC	no;
}YESNO_WORK;


// �|�P�����f�[�^
typedef struct {
	STRBUF * name;			// �j�b�N�l�[��

	u16	mons;			// �|�P�����ԍ�
	u16	hp;				// HP
	u16	mhp;			// �ő�HP
	u16	lv;				// ���x��
	u16	item;			// �A�C�e���ԍ�
	u16	st:12;			// ��Ԉُ�
	u16	sex_put:1;		// ���ʕ\���i�j�h�����p�j0=ON, 1=OFF
	u16	sex:2;			// ����
	u16	contest:1;		// �R���e�X�g�ɎQ���ł��邩
	u8	egg;			// �^�}�S�t���O
	u8	form;			// �t�H����No
	u16	cb;				// �J�X�^���{�[��

	s8	plate_px;
	s8	plate_py;

	s16	mons_px;
	s16	mons_py;

	s16	st_px;
	s16	st_py;

	s16	item_px;
	s16	item_py;

	CLACT_WORK_PTR	icon_cwp;
//	CLACT_WORK_PTR	item_cwp;
	u8	anm_cnt;
	u8	flg;
}PL_PANEL_DATA;

// �Ȃ�т����p���[�N
typedef struct {
	u16	plate_bg[2][PL_PANEL_SX*PL_PANEL_SY];
	u16	str_bg[2][PL_PANEL_SX*PL_PANEL_SY];
	u8	pos[2];
	u8	mv[2];
	u8	flg;
	u8	seq;
	u8	cnt;
}MENU_NARABIKAE_WORK;

// �|�P�������X�g���[�N
typedef struct {
	GF_BGL_INI * bgl;						// BGL�f�[�^

	GF_BGL_BMPWIN	win[WIN_MAX];			// BMP�E�B���h�E�f�[�^�i�ʏ�j
	GF_BGL_BMPWIN	add_win[ADD_WIN_MAX];	// BMP�E�B���h�E�f�[�^�i�ǉ��j

	u16	plate_top[PL_PANEL_SX*PL_PANEL_SY];
	u16	plate_normal[PL_PANEL_SX*PL_PANEL_SY];
	u16	plate_none[PL_PANEL_SX*PL_PANEL_SY];

	u16	pal[16*8];							// �p���b�g�ۑ�

	PLIST_DATA * dat;

	CATS_SYS_PTR	csp;
	CATS_RES_PTR	crp;
	CLACT_WORK_PTR	act_work[PLIST_ACT_MAX];
	CATS_ACT_PTR	cap[PLIST_ACT_MAX];

	NUMFONT * num_font;					// 8x8�t�H���g
	MSGDATA_MANAGER * msg_man;			// ���b�Z�[�W�f�[�^�}�l�[�W��
	WORDSET * wset;						// �P��Z�b�g
	STRBUF * msg_buf;					// ���b�Z�[�W�W�J�̈�
	STRBUF * str_buf;					// ���b�Z�[�W�W�J�̈�
	STRBUF * menu_str[MENU_STR_MAX];	// ���j���[������W�J�̈�

	BMP_MENULIST_DATA * md;			// BMP���j���[�f�[�^
	BMPMENU_WORK * mw;				// BMP���j���[���[�N

	PL_PANEL_DATA	panel[6];

	const POINTER_WORK * mv_tbl;

	MENU_NARABIKAE_WORK	chg_wk;

//	TCB_PTR		vtask;
//	INTR_FUNC	vblank_func;

	STRCV_FUNC	strcv_func;

	YESNO_WORK	yesno;

	u8	sub_button_seq;	// �T�u�{�^���A�j���V�[�P���X
	u8	sub_button_pos;	// �T�u�{�^���A�j���ʒu

	u8	next_seq;		// ���̃V�[�P���X

	u8	chg_pos:6;
	u8	chg_flg:1;

	u8	cancel_flg:1;

	u8	msg_index;

	u8	pos;
	u8	old_pos;

	u8	lv_seq;			// ���x���A�b�v�V�[�P���X
	u16	tmp[6];			// �e���|�������[�N

	ZKN_HEIGHT_GRAM_PTR	zkn;	// �}�Ӄf�[�^�i���M�����[�V�����ŕK�v�j

}PLIST_WORK;



//---------------------------------------------------------------------------------------------
/**
 * �|�P���������邩�`�F�b�N
 *
 * @param	wk		�|�P�������X�g���[�N
 * @param	pos		�ʒu
 *
 * @retval	"TRUE = ����"
 * @retval	"FALSE = ���Ȃ�"
 */
//---------------------------------------------------------------------------------------------
extern u8 PokeListDataCheck( PLIST_WORK * wk, u8 pos );

//---------------------------------------------------------------------------------------------
/**
 * �|�P�����p�����[�^�擾
 *
 * @param	wk		�|�P�������X�g���[�N
 *
 * @retval	"TRUE = ����"
 * @retval	"FALSE = ���Ȃ�"
 */
//---------------------------------------------------------------------------------------------
extern u8 PokeList_PanelPPDataMake( PLIST_WORK * wk, u8 pos );


extern void PokeListPanelPaletteSet( PLIST_WORK * wk, u8 num );

extern u8 PokeListSelCursorCheck( u8 type, u8 pos );

extern const u16 * PokeList_HPGageCharGet( PLIST_WORK * wk );

extern u8 PokeList_BattleInCheck( PLIST_WORK * wk, u8 num );

extern void PokeList_CursorMoveAuto( PLIST_WORK * wk, u8 mv_pos );


#endif	/* PLIST_SYS_H */
