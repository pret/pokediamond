// ���C���V�[�P���X
enum {
	SHOP_SEQ_INIT = 0,		// ������
	SHOP_SEQ_MENU,			// ���j���[�I��

	SHOP_SEQ_BUY_INIT,		// �w����ʏ�����
	SHOP_SEQ_BUY_SCROLL,	// �w���ʒu�փX�N���[��
	SHOP_SEQ_BUY_SELECT,	// �A�C�e���I��
	SHOP_SEQ_BUYSEL_WAIT,	// �u�����`�v�\���E�F�C�g
	SHOP_SEQ_BUYNUM_SEL,	// ���I��
	SHOP_SEQ_BUYNUM_WAIT,	// �u���v�`�Ȃ�܂����v�\���E�F�C�g
	SHOP_SEQ_BUY_YESNO,		// �͂��E�������I��
	SHOP_SEQ_BUY_CMP,		// �w��
	SHOP_SEQ_BUYCMP_WAIT,	// �A�C�e���I����
	SHOP_SEQ_BUYOMAKE_WAIT,	// �v���~�A�{�[���҂�
	SHOP_SEQ_BUY_END,		// �w����ʏI��

	SHOP_SEQ_MENU_RET,		// ���j���[�I���֖߂�҂�

	SHOP_SEQ_SALE_INIT,		// �u����v������
	SHOP_SEQ_SALE_CALL,		// �u����v�Ăяo��
	SHOP_SEQ_SALE_WAIT,		// �u����v�I���҂�
	SHOP_SEQ_SALE_RET,		// �u����v�I�� -> �t�F�[�h�C��
	SHOP_SEQ_SALE_MENU_RET,	// �t�F�[�h�C�� -> ���j���[��

	SHOP_SEQ_EXIT,
	SHOP_SEQ_END
};

// �E�B���h�E�C���f�b�N�X
enum {
	WIN_IDX_NENU = 0,	// ���j���[
	WIN_IDX_FLDTALK,	// �t�B�[���h��b

	WIN_IDX_LIST = 0,	// �A�C�e�����X�g
	WIN_IDX_INFO,		// �A�C�e������
	WIN_IDX_GOLD,		// ����������
	WIN_IDX_NUM,		// ���I��
	WIN_IDX_MINE,		// �����Ă��鐔
	WIN_IDX_TALK,		// ��b

	WIN_IDX_MAX
};

enum {
	SHOP_CLA_ARROW_U = 0,
	SHOP_CLA_ARROW_D,
	SHOP_CLA_CURSOR,
	SHOP_CLA_ITEMICON,
	SHOP_CLA_MAX
};

typedef struct {
	GF_BGL_INI * bgl;		// BGL�f�[�^

	void * bag_wk;			// �o�b�O�̃��[�N

	GF_BGL_BMPWIN	win[WIN_IDX_MAX];	// BMP�E�B���h�E
	GF_BGL_BMPWIN	yn_win;				// BMP�E�B���h�E�i�͂��E�������j

	BMPLIST_WORK * lw;		// BMP���j���[���[�N
	BMP_MENULIST_DATA * ld;	// BMP���X�g�f�[�^

	BMPMENU_WORK * mw;		// BMP���j���[���[�N
	BMP_MENULIST_DATA * md;	// BMP���j���[�f�[�^

	MSGDATA_MANAGER * mman;	// ���b�Z�[�W�f�[�^�}�l�[�W��
	WORDSET * wset;			// �P��Z�b�g

	GF_CAMERA_PTR	camera;

	FIELD_CLACT	fcat;
	CLACT_WORK_PTR	cwp[SHOP_CLA_MAX];
	u16	scr_draw[2];

	MYSTATUS * my;
	void * myitem;
	CONFIG * cfg;

	FNOTE_DATA * fnote;

	RECORD * rec;

	EVENTWORK * evwk;	// �C�x���g���[�N
	BOOL	dp_flg;		// �f�p�[�g�t���O

	u16 * item;
	u8	max;
	u8	pos;
	u8	scr;
	u8	seq;

	STRBUF * msgb;	// ��b�̈�
	u8	pri[4];
	int	disp;
	u8	midx;		// ���b�Z�[�W�C���f�b�N�X
	u8	cm_cnt;		// �J�����ړ��J�E���^
	u8	cm_max;		// �J�����ړ��J�E���g��

	u8	fnote_buy_cnt;
	u8	fnote_sale_cnt;

	u8	shop_type;	// �V���b�v�^�C�v

	u16	sel_item;
	s16	sel_num;
	u16	sel_max;
	u32	sel_price;

}SHOP_WORK;


extern BOOL GMEVENT_Shop( GMEVENT_CONTROL * event );
extern BOOL GMEVENT_ShopSale( GMEVENT_CONTROL * event );
