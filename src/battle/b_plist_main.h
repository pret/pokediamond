//============================================================================================
/**
 * @file	b_plist_main.h
 * @brief	�퓬�p�|�P�������X�g���
 * @author	Hiroyuki Nakamura
 * @date	05.02.01
 */
//============================================================================================
#ifndef B_PLIST_MAIN_H
#define B_PLIST_MAIN_H
#undef GLOBAL
#ifdef B_PLIST_MAIN_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================
// �p���b�g��`
#define	BPL_PAL_NN_PLATE	( 0 )		///< �p���b�g00�F�v���[�g�i�ʏ�j
#define	BPL_PAL_MN_PLATE	( 1 )		///< �p���b�g01�F�v���[�g�i�}���`�j
#define	BPL_PAL_DN_PLATE	( 2 )		///< �p���b�g02�F�v���[�g�i�m���j
#define	BPL_PAL_HPGAGE		( 9 )		///< �p���b�g09�FHP�Q�[�W

#define	BPL_PAL_B_RED		( 10 )		///< �p���b�g09�F�{�^���i�ԁj
#define	BPL_PAL_B_GREEN		( 12 )		///< �p���b�g09�F�{�^���i�΁j

#define	BPL_PAL_SYS_FONT	( 13 )		///< �p���b�g13�F�V�X�e���t�H���g
#define	BPL_PAL_TALK_WIN	( 14 )		///< �p���b�g14�F��b�E�B���h�E
#define	BPL_PAL_TALK_FONT	( 15 )		///< �p���b�g15�F��b�t�H���g

#define	BPL_HP_DOTTO_MAX	( 48 )		///< HP�Q�[�W�̃h�b�g�T�C�Y

// �E�B���h�E�C���f�b�N�X
enum {
	WIN_COMMENT = 0,	///< �R�����g�p�E�B���h�E
	WIN_TALK,			///< ��b�p�E�B���h�E
	WIN_MAX
};

// �y�[�W�P�̒ǉ��E�B���h�E�C���f�b�N�X
enum {
	WIN_P1_POKE1 = 0,	// �|�P�����P
	WIN_P1_POKE2,		// �|�P�����Q
	WIN_P1_POKE3,		// �|�P�����R
	WIN_P1_POKE4,		// �|�P�����S
	WIN_P1_POKE5,		// �|�P�����T
	WIN_P1_POKE6,		// �|�P�����U
	WIN_P1_MAX
};

// ����ւ��y�[�W�̒ǉ��E�B���h�E�C���f�b�N�X
enum {
	WIN_CHG_NAME = 0,	// ���O
	WIN_CHG_IREKAE,		// �u���ꂩ����v
	WIN_CHG_STATUS,		// �u�悳���݂�v
	WIN_CHG_WAZACHECK,	// �u�킴���݂�v
	WIN_CHG_MAX
};

// �Z�I���y�[�W�̒ǉ��E�B���h�E�C���f�b�N�X
enum {
	WIN_STW_NAME = 0,		// ���O
	WIN_STW_SKILL1,			// �Z�P
	WIN_STW_SKILL2,			// �Z�Q
	WIN_STW_SKILL3,			// �Z�R
	WIN_STW_SKILL4,			// �Z�S

	WIN_STW_STATUS,			// �u�悳���݂�v

	// ���X���b�v�p
	WIN_STW_NAME_S,			// ���O�i�X���b�v�j
	WIN_STW_SKILL1_S,		// �Z�P�i�X���b�v�j
	WIN_STW_SKILL2_S,		// �Z�Q�i�X���b�v�j
	WIN_STW_SKILL3_S,		// �Z�R�i�X���b�v�j
	WIN_STW_SKILL4_S,		// �Z�S�i�X���b�v�j

	WIN_STW_MAX
};

// �X�e�[�^�X���C���y�[�W�̒ǉ��E�B���h�E�C���f�b�N�X
enum {
	WIN_P3_NAME = 0,	// ���O
	WIN_P3_SPANAME,		// ������
	WIN_P3_SPAINFO,		// ��������
	WIN_P3_ITEMNAME,	// ���
	WIN_P3_HPNUM,		// HP�l
	WIN_P3_POWNUM,		// �U���l
	WIN_P3_DEFNUM,		// �h��l
	WIN_P3_AGINUM,		// �f�����l
	WIN_P3_SPPNUM,		// ���U�l
	WIN_P3_SPDNUM,		// ���h�l
	WIN_P3_HPGAGE,		// HP�Q�[�W
	WIN_P3_LVNUM,		// ���x���l
	WIN_P3_NEXTNUM,		// ���̃��x���l

	WIN_P3_HP,			// �uHP�v
	WIN_P3_POW,			// �u���������v
	WIN_P3_DEF,			// �u�ڂ�����v
	WIN_P3_AGI,			// �u���΂₳�v
	WIN_P3_SPP,			// �u�Ƃ������v
	WIN_P3_SPD,			// �u�Ƃ��ڂ��v
	WIN_P3_LV,			// �uLv.�v
	WIN_P3_NEXT,		// �u���̃��x���܂Łv
	WIN_P3_WAZACHECK,	// �u�킴���݂�v

	// ���X���b�v�p
	WIN_P3_NAME_S,		// ���O�i�X���b�v�j
	WIN_P3_SPANAME_S,	// �������i�X���b�v�j
	WIN_P3_SPAINFO_S,	// ���������i�X���b�v�j
	WIN_P3_ITEMNAME_S,	// ����i�X���b�v�j
	WIN_P3_HPNUM_S,		// HP�l�i�X���b�v�j
	WIN_P3_POWNUM_S,	// �U���l�i�X���b�v�j
	WIN_P3_DEFNUM_S,	// �h��l�i�X���b�v�j
	WIN_P3_AGINUM_S,	// �f�����l�i�X���b�v�j
	WIN_P3_SPPNUM_S,	// ���U�l�i�X���b�v�j
	WIN_P3_SPDNUM_S,	// ���h�l�i�X���b�v�j
	WIN_P3_HPGAGE_S,	// HP�Q�[�W�i�X���b�v�j
	WIN_P3_LVNUM_S,		// ���x���l�i�X���b�v�j
	WIN_P3_NEXTNUM_S,	// ���̃��x���l�i�X���b�v�j
	WIN_P3_MAX
};

// �X�e�[�^�X�Z�ڍ׃y�[�W�̒ǉ��E�B���h�E�C���f�b�N�X
enum {
	WIN_P4_SKILL = 0,	// �Z��
	WIN_P4_PPNUM,		// PP/PP
	WIN_P4_HITNUM,		// �����l
	WIN_P4_POWNUM,		// �З͒l
	WIN_P4_INFO,		// �Z����
	WIN_P4_BRNAME,		// ���ޖ�

	WIN_P4_NAME,		// ���O
	WIN_P4_PP,			// PP
	WIN_P4_HIT,			// �u�߂����イ�v
	WIN_P4_POW,			// �u����傭�v
	WIN_P4_BUNRUI,		// �u�Ԃ�邢�v

	// ���X���b�v�p
	WIN_P4_SKILL_S,		// �Z��
	WIN_P4_PPNUM_S,		// PP/PP
	WIN_P4_HITNUM_S,	// �����l
	WIN_P4_POWNUM_S,	// �З͒l
	WIN_P4_INFO_S,		// �Z����
	WIN_P4_BRNAME_S,	// ���ޖ�
	WIN_P4_MAX
};

// �Z�Y��I���y�[�W�̒ǉ��E�B���h�E�C���f�b�N�X
enum {
	WIN_P5_NAME = 0,	// ���O
	WIN_P5_SKILL1,		// �Z�P
	WIN_P5_SKILL2,		// �Z�Q
	WIN_P5_SKILL3,		// �Z�R
	WIN_P5_SKILL4,		// �Z�S
	WIN_P5_SKILL5,		// �Z�T
	WIN_P5_MAX
};

// �y�[�W�U�̒ǉ��E�B���h�E�C���f�b�N�X
enum {
	WIN_P6_NAME = 0,	// ���O
	WIN_P6_SKILL,		// �Z��
	WIN_P6_PP,			// PP
	WIN_P6_PPNUM,		// PP/PP
	WIN_P6_HIT,			// �u�߂����イ�v
	WIN_P6_POW,			// �u����傭�v
	WIN_P6_HITNUM,		// �����l
	WIN_P6_POWNUM,		// �З͒l
	WIN_P6_INFO,		// �Z����
	WIN_P6_BUNRUI,		// �u�Ԃ�邢�v
	WIN_P6_BRNAME,		// ���ޖ�
	WIN_P6_WASURERU,	// �u�킷���v
	WIN_P6_MAX
};

// �Z�񕜑I���y�[�W�̒ǉ��E�B���h�E�C���f�b�N�X
enum {
	WIN_P7_NAME = 0,	// ���O
	WIN_P7_SKILL1,		// �Z�P
	WIN_P7_SKILL2,		// �Z�Q
	WIN_P7_SKILL3,		// �Z�R
	WIN_P7_SKILL4,		// �Z�S
	WIN_P7_MAX
};

// �y�[�W�W�̒ǉ��E�B���h�E�C���f�b�N�X
enum {
	WIN_P8_NAME = 0,	// ���O
	WIN_P8_SKILL,		// �Z��
	WIN_P8_PP,			// PP
	WIN_P8_PPNUM,		// PP/PP
	WIN_P8_APP,			// �u�A�s�[���|�C���g�v
	WIN_P8_INFO,		// �Z����
	WIN_P8_WASURERU,	// �u�킷���v
	WIN_P8_MAX
};

enum {
	BPL_CA_ITEM1 = 0,
	BPL_CA_ITEM2,
	BPL_CA_ITEM3,
	BPL_CA_ITEM4,
	BPL_CA_ITEM5,
	BPL_CA_ITEM6,

	BPL_CA_ITEM7,

	BPL_CA_POKE1,
	BPL_CA_POKE2,
	BPL_CA_POKE3,
	BPL_CA_POKE4,
	BPL_CA_POKE5,
	BPL_CA_POKE6,

	BPL_CA_STATUS1,
	BPL_CA_STATUS2,
	BPL_CA_STATUS3,
	BPL_CA_STATUS4,
	BPL_CA_STATUS5,
	BPL_CA_STATUS6,

	BPL_CA_POKETYPE1,
	BPL_CA_POKETYPE2,

	BPL_CA_WAZATYPE1,
	BPL_CA_WAZATYPE2,
	BPL_CA_WAZATYPE3,
	BPL_CA_WAZATYPE4,
	BPL_CA_WAZATYPE5,

	BPL_CA_BUNRUI,

	BPL_CA_CND1,
	BPL_CA_CND2,
	BPL_CA_CND3,
	BPL_CA_CND4,
	BPL_CA_CND5,

	BPL_CA_CB1,
	BPL_CA_CB2,
	BPL_CA_CB3,
	BPL_CA_CB4,
	BPL_CA_CB5,
	BPL_CA_CB6,

	BPL_CA_MAX
};

typedef struct {
	u16	id;		// �Z�ԍ�
	u8	pp;		// PP
	u8	mpp;	// �ő�PP

	u8	type;	// �^�C�v
	u8	kind;	// ����
	u8	hit;	// ����
	u8	pow;	// �З�
}BPL_POKEWAZA;

typedef struct {
	POKEMON_PARAM * pp;		// �|�P�����f�[�^

	u16	mons;		// �|�P�����ԍ�
	u16	pow;		// �U��

	u16	def;		// �h��
	u16	agi;		// �f����

	u16	spp;		// ���U
	u16	spd;		// ���h

	u16	hp;			// HP
	u16	mhp;		// �ő�HP

	u8	type1;		// �^�C�v�P
	u8	type2;		// �^�C�v�Q
	u8	lv:7;		// ���x��
	u8	sex_put:1;	// ���ʕ\���i�j�h�����p�j0=ON, 1=OFF
	u8	sex:3;		// ����
	u8	st:4;		// ��Ԉُ�
	u8	egg:1;		// �^�}�S

	u16	spa;		// ����
	u16	item;		// �A�C�e��

	u32	now_exp;		// ���݂̌o���l
	u32	now_lv_exp;		// ���݂̃��x���̌o���l
	u32	next_lv_exp;	// ���̃��x���̌o���l

	u8	style;			// �������悳
	u8	beautiful;		// ��������
	u8	cute;			// ���킢��
	u8	clever;			// ��������
	u8	strong;			// �����܂���

	u8	cb;				// �J�X�^���{�[��
	u8	form;			// �t�H����No

	BPL_POKEWAZA	waza[4];	// �Z�f�[�^

}BPL_POKEDATA;

#define	BPL_BANM_MAX_N	( 3 )		// �{�^���A�j���p�^�[�����i�ʏ�j
#define	BPL_BANM_MAX_E	( 4 )		// �{�^���A�j���p�^�[�����i�����Ȃ��{�^������j
// �v���[�g�{�^���T�C�Y
#define	BPL_BSX_PLATE	( 16 )
#define	BPL_BSY_PLATE	( 6 )
// ���߃{�^���T�C�Y
#define	BPL_BSX_COMMAND	( 13 )
#define	BPL_BSY_COMMAND	( 5 )
// �؂�ւ��{�^���T�C�Y
#define	BPL_BSX_UPDOWN	( 5 )
#define	BPL_BSY_UPDOWN	( 5 )
// �߂�{�^���T�C�Y
#define	BPL_BSX_RET		( 5 )
#define	BPL_BSY_RET		( 5 )
// ����ւ��{�^��
#define	BPL_BSX_CHG		( 30 )
#define	BPL_BSY_CHG		( 17 )
// �Z�{�^���T�C�Y
#define	BPL_BSX_WAZA	( 16 )
#define	BPL_BSY_WAZA	( 6 )
// �Y���{�^���T�C�Y
#define	BPL_BSX_DEL		( 26 )
#define	BPL_BSY_DEL		( 5 )
// �R���e�X�g�؂�ւ��{�^���T�C�Y
#define	BPL_BSX_CONTEST	( 9 )
#define	BPL_BSY_CONTEST	( 4 )
// �Z�ʒu�{�^��
#define	BPL_BSX_WP		( 5 )
#define	BPL_BSY_WP		( 2 )

typedef struct {
	BPLIST_DATA * dat;	// �O���Q�ƃf�[�^

	BPL_POKEDATA	poke[6];	// �|�P�����f�[�^

	GF_BGL_INI * bgl;		// BG�f�[�^

	PALETTE_FADE_PTR pfd;	// �p���b�g�t�F�[�h�f�[�^

	u16	btn_plate1[BPL_BANM_MAX_E][BPL_BSX_PLATE*BPL_BSY_PLATE];		// �퓬���̃v���[�g�{�^��
	u16	btn_plate2[BPL_BANM_MAX_E][BPL_BSX_PLATE*BPL_BSY_PLATE];		// �T���̃v���[�g�{�^��
	u16	btn_command[BPL_BANM_MAX_E][BPL_BSX_COMMAND*BPL_BSY_COMMAND];	// ���߃{�^��
	u16	btn_up[BPL_BANM_MAX_E][BPL_BSX_UPDOWN*BPL_BSY_UPDOWN];			// �؂�ւ��{�^���i��j
	u16	btn_down[BPL_BANM_MAX_E][BPL_BSX_UPDOWN*BPL_BSY_UPDOWN];		// �؂�ւ��{�^���i���j
	u16	btn_ret[BPL_BANM_MAX_E][BPL_BSX_RET*BPL_BSY_RET];				// �߂�{�^��
	u16	btn_chg[BPL_BANM_MAX_N][BPL_BSX_CHG*BPL_BSY_CHG];				// ����ւ��{�^��
	u16	btn_waza[BPL_BANM_MAX_E][BPL_BSX_WAZA*BPL_BSY_WAZA];			// �Z�{�^��
	u16	btn_del[BPL_BANM_MAX_N][BPL_BSX_DEL*BPL_BSY_DEL];				// �Y���{�^��
	u16	btn_contest[BPL_BANM_MAX_N][BPL_BSX_CONTEST*BPL_BSY_CONTEST];	// �R���e�X�g�؂�ւ��{�^��
	u16	btn_wp[BPL_BANM_MAX_N][BPL_BSX_WP*BPL_BSY_WP];					// �Z�ʒu�{�^��

	u16	wb_pal[16*2];	// �Z�{�^���̃p���b�g

	u8	btn_seq;
	u8	btn_cnt;
	u8	btn_id;
	u8	btn_mode:4;
	u8	btn_pat:3;
	u8	btn_flg:1;

	NUMFONT * nfnt;					// 8x8�t�H���g
	MSGDATA_MANAGER * mman;			// ���b�Z�[�W�f�[�^�}�l�[�W��
	WORDSET * wset;					// �P��Z�b�g
	STRBUF * msg_buf;				// ���b�Z�[�W�p�o�b�t�@

	CATS_RES_PTR	crp;				// ���\�[�X�Ǘ�
	CATS_ACT_PTR	cap[BPL_CA_MAX];	// OAM��CAP

	GF_BGL_BMPWIN	win[WIN_MAX];	// BMP�E�B���h�E�f�[�^�i�ʏ�j
	GF_BGL_BMPWIN * add_win;		// BMP�E�B���h�E�f�[�^�i�ǉ��j
	u8	bmp_add_max;				// �ǉ�����BMP�̐�
	u8	bmp_swap;					// �X���b�v�`��t���O

	u8	init_poke;		// ����ւ��Ώۂ̃|�P�����ʒu

	u8	bc_put:4;			// �Z�̕\�����퓬���R���e�X�g��
	u8	ev_contest:4;		// �R���e�X�g�\�����t���O

	u8	seq;			// ���C���V�[�P���X
	u8	ret_seq;		// ���A�V�[�P���X
	u8	page;			// ���݂̃y�[�W
	u8	midx;			// ���b�Z�[�W�C���f�b�N�X

	u8	rcv_seq;
	u8	rcv_st;
	u16	rcv_hp;
	u16	rcv_pp[4];

	BAPP_CURSOR_MVWK * cmv_wk;	// �J�[�\�����䃏�[�N
	u8	chg_page_cp;			// �|�P��������ւ��y�[�W�̃J�[�\���ʒu
	u8	wws_page_cp;			// �X�e�[�^�X�Z�Y��Z�I���y�[�W�̃J�[�\���ʒu
	u8	wwm_page_cp;			// �X�e�[�^�X�Z�Y��Z�ڍ׃y�[�W�̃J�[�\���ʒu

	u8	multi_pos;				// �}���`�o�g���̗����ʒu
}BPLIST_WORK;




//--------------------------------------------------------------------------------------------
/**
 * �w��ʒu�Ƀ|�P���������݂��邩
 *
 * @param	wk		���[�N
 * @param	pos		�ʒu
 *
 * @retval	"0 = ���Ȃ�"
 * @retval	"1 = �퓬��"
 * @retval	"2 = �T��"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 BattlePokeList_PokeSetCheck( BPLIST_WORK * wk, s32 pos );

//--------------------------------------------------------------------------------------------
/**
 * �_�u���o�g���`�F�b�N
 *
 * @param	wk		���[�N
 *
 * @retval	"TRUE = �_�u���o�g��"
 * @retval	"FALSE = �_�u���o�g���ȊO"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 BattlePokeList_DoubleCheck( BPLIST_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * �}���`�o�g���`�F�b�N
 *
 * @param	wk		���[�N
 *
 * @retval	"TRUE = �_�u���o�g��"
 * @retval	"FALSE = �_�u���o�g���ȊO"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 BattlePokeList_MultiCheck( BPLIST_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * �}���`�o�g���Ńp�[�g�i�[�̃|�P�������`�F�b�N
 *
 * @param	wk		���[�N
 * @param	pos		�ʒu
 *
 * @retval	"TRUE = �͂�"
 * @retval	"FALSE = ������"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 BattlePokeList_MultiPosCheck( BPLIST_WORK * wk, u8 pos );


#undef GLOBAL
#endif	// B_PLIST_MAIN_H
