
#include "pokeanime/p_anm_sys.h"


#define	PST_PAL_SYSFONT		( 15 )
#define	PST_PAL_TALKFONT	( 14 )
#define	PST_PAL_TALKWIN		( 13 )

#define	PST_CGX_TALKWIN		( 1024-TALK_WIN_CGX_SIZ )

#define	PST_LIKE_TASTE_NONE	( 5 )		// �D���Ȗ��Ȃ�
#define	PST_KEDUYA_MAX		( 255 )		// �щ��ő�l


// OBJ ID
enum {
	PST_OBJ_TAB_INFO = 0,
	PST_OBJ_TAB_MEMO,
	PST_OBJ_TAB_PARAM,
	PST_OBJ_TAB_CONDITION,
	PST_OBJ_TAB_B_SKILL,
	PST_OBJ_TAB_C_SKILL,
	PST_OBJ_TAB_RIBBON,
	PST_OBJ_TAB_RET,

	PST_OBJ_BALL,

	PST_OBJ_WAZACURSOR1,
	PST_OBJ_WAZACURSOR2,

	PST_OBJ_TYPE_POKE1,
	PST_OBJ_TYPE_POKE2,
	PST_OBJ_TYPE_WAZA1,
	PST_OBJ_TYPE_WAZA2,
	PST_OBJ_TYPE_WAZA3,
	PST_OBJ_TYPE_WAZA4,
	PST_OBJ_TYPE_WAZA5,
	PST_OBJ_TYPE_KIND,

	PST_OBJ_POKEICON,

	PST_OBJ_STIZYO,
	PST_OBJ_ARROW_L,
	PST_OBJ_ARROW_R,

	PST_OBJ_MARK1,
	PST_OBJ_MARK2,
	PST_OBJ_MARK3,
	PST_OBJ_MARK4,
	PST_OBJ_MARK5,
	PST_OBJ_MARK6,

	PST_OBJ_FLASH1,
	PST_OBJ_FLASH2,
	PST_OBJ_FLASH3,
	PST_OBJ_FLASH4,
	PST_OBJ_FLASH5,
	PST_OBJ_FLASH6,
	PST_OBJ_FLASH7,
	PST_OBJ_FLASH8,
	PST_OBJ_FLASH9,
	PST_OBJ_FLASH10,
	PST_OBJ_FLASH11,
	PST_OBJ_FLASH12,

	PST_OBJ_BUTTON_EF,

	PST_OBJ_UP1,
	PST_OBJ_UP2,
	PST_OBJ_UP3,
	PST_OBJ_UP4,
	PST_OBJ_UP5,

	PST_OBJ_A_BUTTON,

	PST_OBJ_EZC_STYLE,
	PST_OBJ_EZC_BEAUTIFUL,
	PST_OBJ_EZC_CUTE,
	PST_OBJ_EZC_CLEVER,
	PST_OBJ_EZC_STRONG,

	PST_OBJ_RARE_MARK,
	PST_OBJ_POKERUS_MARK,

	PST_OBJ_RIBBON01,
	PST_OBJ_RIBBON02,
	PST_OBJ_RIBBON03,
	PST_OBJ_RIBBON04,
	PST_OBJ_RIBBON05,
	PST_OBJ_RIBBON06,
	PST_OBJ_RIBBON07,
	PST_OBJ_RIBBON08,
	PST_OBJ_RIBBON09,
	PST_OBJ_RIBBON10,
	PST_OBJ_RIBBON11,
	PST_OBJ_RIBBON12,
	PST_OBJ_RIBBON_CUR,

	PST_OBJ_RIBBON_AU,
	PST_OBJ_RIBBON_AD,
	PST_OBJ_RIBBON_FLASH,
	PST_OBJ_CON_FLASH1,
	PST_OBJ_CON_FLASH2,
	PST_OBJ_CON_FLASH3,
	PST_OBJ_CON_FLASH4,
	PST_OBJ_CON_FLASH5,

	PST_OBJ_CON_POKERUS,

	PST_OBJ_MAX
};

// ��{�������BMP�f�[�^
enum {
	WIN_P1_TITLE,		// �u�|�P�������傤�ق��v
	WIN_P2_TITLE,		// �u�g���[�i�[�����v
	WIN_P3_TITLE,		// �u�|�P�����̂���傭�v
	WIN_P4_TITLE,		// �u�R���f�B�V�����v
	WIN_P5_TITLE,		// �u���������킴�v
	WIN_P6_TITLE,		// �u�R���e�X�g�킴�v
	WIN_MOTIMONO,		// �u�������́v
	WIN_P1_ZUKANNO,		// �u������No.�v
	WIN_P1_NAME,		// �u�Ȃ܂��v
	WIN_P1_TYPE,		// �u�^�C�v�v
	WIN_P1_OYA,			// �u����v
	WIN_P1_IDNO,		// �uIDNo.�v
	WIN_P1_NOWEXP,		// �u���񂴂��́@�������񂿁v
	WIN_P1_NEXTLV,		// �u���̃��x���܂Łv
	WIN_P1_ATO,			// �u���Ɓv
	WIN_P3_HP,			// �uHP�v
	WIN_P3_POW,			// �u���������v
	WIN_P3_DEF,			// �u�ڂ�����v
	WIN_P3_SPP,			// �u�Ƃ������v
	WIN_P3_SPD,			// �u�Ƃ��ڂ��v
	WIN_P3_AGI,			// �u���΂₳�v
	WIN_P3_SPA,			// �u�Ƃ������v
	WIN_P4_KEDUYA,		// �u���Â�v
	WIN_P4_SEIKAKU,		// �u���������v
	WIN_P5_MODORU,		// �u���ǂ�v
	WIN_P5_BUNRUI,		// �u�Ԃ�邢�v
	WIN_P5_IRYOKU,		// �u����傭
	WIN_P5_HIT,			// �u�߂����イ�v
	WIN_P8_MODORIMASU,	// �u���ǂ�܂��v
	WIN_P6_AP_POINT,	// �u�A�s�[���|�C���g�v
	WIN_P7_MOTTEIRU,	// �u�����Ă��邩���v
	WIN_P7_TITLE,		// �u���˂񃊃{���v
	WIN_ITEMNAME,		// �A�C�e����
	WIN_LV,				// ���x��
	WIN_NICKNAME,		// �j�b�N�l�[��
	WIN_GUIDE,			// �K�C�h���b�Z�[�W
	WIN_MAX
};

// �y�[�W�P�i�|�P�������j
enum {
	ADD_WIN_P1_LIBNUM,	// �}��No.
	ADD_WIN_P1_NAME,	// ���O
	ADD_WIN_P1_OYANAME,	// �e��
	ADD_WIN_P1_IDNO,	// IDNo.
	ADD_WIN_P1_NOWEXP,	// ���݂̌o���l
	ADD_WIN_P1_NEXTEXP,	// ���̃��x���܂�@
	ADD_WIN_P1_MAX
};

// �y�[�W�Q�i�g���[�i�[�����j
enum {
	ADD_WIN_P2_TMEMO,	// �g���[�i�[����
	ADD_WIN_P2_MAX
};

// �y�[�W�R�i�|�P�����\�́j
enum {
	ADD_WIN_P3_HP,		// HP/MHP
	ADD_WIN_P3_POW,		// �U��
	ADD_WIN_P3_DEF,		// �h��
	ADD_WIN_P3_SPP,		// ���U
	ADD_WIN_P3_SPD,		// ���h
	ADD_WIN_P3_AGI,		// �f����
	ADD_WIN_P3_SPANAME,	// ������
	ADD_WIN_P3_SPAINFO,	// ��������
	ADD_WIN_P3_MAX
};

// �y�[�W�T�i�키�Z�j
enum {
	ADD_WIN_P5_WAZA1,		// �Z���P
	ADD_WIN_P5_WAZA2,		// �Z���Q
	ADD_WIN_P5_WAZA3,		// �Z���R
	ADD_WIN_P5_WAZA4,		// �Z���S
	ADD_WIN_P5_WAZA5,		// �Z���T
	ADD_WIN_P5_ATC,			// �З�
	ADD_WIN_P5_HIT,			// ����
	ADD_WIN_P5_INFO,		// �Z����
	ADD_WIN_P5_MAX
};

// �y�[�W�U�i�R���e�X�g�Z�j
enum {
	ADD_WIN_P6_WAZA1,	// �Z���P
	ADD_WIN_P6_WAZA2,	// �Z���Q
	ADD_WIN_P6_WAZA3,	// �Z���R
	ADD_WIN_P6_WAZA4,	// �Z���S
	ADD_WIN_P6_WAZA5,	// �Z���T
	ADD_WIN_P6_INFO,	// �Z����
	ADD_WIN_P6_MAX
};

// �y�[�W�V�i�L�O���{���j
enum {
	ADD_WIN_P7_NUM,		// ???��
	ADD_WIN_P7_MAXNUM,	// ???/???
	ADD_WIN_P7_NAME,	// ���{����
	ADD_WIN_P7_INFO,	// ���{������
	ADD_WIN_P7_MAX
};


// �|���g�֘A�̃R���f�B�V�����y�[�W
enum {
	ADD_WIN_COND_KETTEI,	// �u�����Ă��v
	ADD_WIN_COND_LIKE,		// �u�����Ȃ��ׂ��́v
	ADD_WIN_COND_MSG,		// ���b�Z�[�W
//	ADD_WIN_COND_MODORU,	// �u���ǂ�v
	ADD_WIN_COND_MAX
};


typedef struct {
	GF_CAMERA_PTR	camera;		// �J����

	void * ssm;					// �\�t�g�E�F�A�X�v���C�g�}�l�[�W��
	SOFT_SPRITE_ANIME	ssanm[SS_ANM_SEQ_MAX];
	POKE_ANM_SYS_PTR	poke_anm_sys;
	SOFT_SPRITE	* ss;
	u32	flip;
}PST_3D_DATA;

typedef struct {
	STRBUF * monsname;		// �|�P������
	STRBUF * nickname;		// �j�b�N�l�[��
	STRBUF * oya;			// �e��

	u16	mons;				// �|�P�����ԍ�
	u16	item;				// �A�C�e���ԍ�

	u8	type1;				// �^�C�v�P
	u8	type2;				// �^�C�v�Q
	u8	lv:7;				// ���x��
	u8	sex_put:1;			// ���ʕ\���i�j�h�����p�j0=ON, 1=OFF
	u8	sex:2;				// ����
	u8	ball:6;				// �ߊl�{�[��

	u32	id;					// IDNo
	u32	now_exp;			// ���݂̌o���l
//	u32	next_exp;			// ���x���A�b�v�܂ł̌o���l
	u32	now_lv_exp;
	u32	next_lv_exp;

	u16	hp;					// HP
	u16	mhp;				// �ő�HP

	u16	atc;				// �U��
	u16	def;				// �h��

	u16	spa;				// ���U
	u16	spd;				// ���h

	u16	agi;				// �f����
	u8	tokusei;			// ����
	u8	seikaku;			// ���i

	u16	waza[4];			// �Z

	u8	wpp[4];				// ���݂�PP

	u8	mpp[4];				// �ő�PP

	u8	oya_sex;			// �e�̐���
	u8	style;				// �������悳
	u8	beautiful;			// ��������
	u8	cute;				// ���킢��
	u8	clever;				// ��������
	u8	strong;				// �����܂���
	u8	fur;				// �щ�
	u8	like;				// �D���Ȗ�

	u16	mark;				// �{�b�N�X�}�[�N
	u16	form;				// �t�H����No

	u32	st:28;				// ��Ԉُ�
	u32	tamago:1;			// �^�}�S�t���O
	u32	rare:1;				// ���A�t���O
	u32	pokerus:2;			// �|�P���X 0=�����Ȃ�, 1=�������Ă���, 2=�R�̂���

	u32	ribbon[4];			// ���{��

}PST_POKEDATA;

typedef struct {
	VecFx16	lt;		// ����
	VecFx16	rt;		// �E��
	VecFx16	lu;		// ����
	VecFx16	ru;		// �E��
}PST_CONDISION_VTX;

typedef struct {
	GF_BGL_INI * bgl;						// BGL�f�[�^

	GF_BGL_BMPWIN	def_win[WIN_MAX];	// BMP�E�B���h�E�f�[�^�i�ʏ�j
	GF_BGL_BMPWIN * add_win;			// BMP�E�B���h�E�f�[�^�i�ǉ��j
	u32	add_win_max;

	PSTATUS_DATA * dat;

	PST_POKEDATA	pp;		// �|�P�����f�[�^

	PST_3D_DATA		p3d;	// 3D�f�[�^

	PST_CONDISION_VTX	cvtx[4];	// �\�����W
	PST_CONDISION_VTX	pvtx[4];	// �v���X�l
	PST_CONDISION_VTX	mvtx[4];	// �ő�l
	u32	con_mv_cnt;

	CATS_SYS_PTR	csp;
	CATS_RES_PTR	crp;
	CLACT_WORK_PTR	awp[PST_OBJ_MAX];
	CATS_ACT_PTR	cap[PST_OBJ_MAX];

	NUMFONT * num_font;			// 8x8�t�H���g
	MSGDATA_MANAGER * msg_man;	// ���b�Z�[�W�f�[�^�}�l�[�W��
	MSGDATA_MANAGER * rbn_man;	// ���b�Z�[�W�f�[�^�}�l�[�W��
	WORDSET * wset;				// �P��Z�b�g
	STRBUF * msg_buf;			// �e���|�������b�Z�[�W�o�b�t�@
	STRBUF * player_name;		// ���Ă���l�̖��O�W�J�ꏊ

	MSGDATA_MANAGER * wman;		// �Z�����b�Z�[�W�f�[�^�}�l�[�W��

//	BOOL	wipe_flg;

	s8	page;		// ���݂̃y�[�W
	u8	cur_pos:4;	// �J�[�\���ʒu
	u8	sub_cur:4;	// �J�[�\���ʒu�i���ꂩ���ʒu�j
	u8	sub_seq;	// �T�u�V�[�P���X
	u8	sub_type:4;	// �T�u��ʂ̃^�C�v
	u8	sub_end:4;	// �T�u��ʂ̂Łu�Ƃ���v

	u8	flash_seq;
	u8	flash_max;
	u8	flash_pos;
	u8	flash_cnt;

	u8	btn_cnt;
	u8	btn_seq;
	u8	btn_pos;

	u8	ribbon_pos;		// ���{���J�[�\���ʒu
	u8	ribbon_scr;		// ���{���X�N���[���J�E���^
	u8	ribbon_max;		// ���{��������
	u8	ribbon_num;		// �J�[�\���ʒu�̃��{��ID

}PST_WORK;




extern u8 PokeStatus_PageCheck( PST_WORK * wk, u32 pos );

extern u8 PokeStatus_PageNumGet( PST_WORK * wk );

extern void * PokeStatusPokeParamGet( PST_WORK * wk );

extern u8 PokeStatus_RibbonPosIDGet( PST_WORK * wk, u8 cur_pos );





