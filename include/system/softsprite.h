
//============================================================================================
/**
 * @file	softsprite.h
 * @bfief	�\�t�g�E�G�A�X�v���C�g���g�p�����\���v���O����
 * @author	HisashiSogabe
 * @date	05.06.08
 */
//============================================================================================

#ifndef __SOFTSPRITE_H_
#define __SOFTSPRITE_H_

#define	SOFT_SPRITE_MAX			(4)		//�o�^�ł���ő吔
#define SOFT_SPRITE_SIZE_X		(80)	//�ǂݍ��ރ\�t�g�E�G�A�X�v���C�g��X�T�C�Y
#define SOFT_SPRITE_SIZE_Y		(80)	//�ǂݍ��ރ\�t�g�E�G�A�X�v���C�g��Y�T�C�Y

#define SOFT_SPRITE_SHADOW_X	(64)	//�e��X�T�C�Y
#define SOFT_SPRITE_SHADOW_Y	(16)	//�e��Y�T�C�Y

#define SOFT_SPRITE_SRC_X		(160)	//�ǂݍ��ރ\�t�g�E�G�A�X�v���C�g��X�T�C�Y
#define SOFT_SPRITE_SRC_Y		(80)	//�ǂݍ��ރ\�t�g�E�G�A�X�v���C�g��Y�T�C�Y

#define SOFT_SPRITE_SRC_Y_OFS	(0x50)	//�ǂݍ��ރ\�t�g�E�G�A�X�v���C�g��Y�I�t�Z�b�g
#define SOFT_SPRITE_DEST_Y_OFS	(0x80)	//�������ރ\�t�g�E�G�A�X�v���C�g��Y�I�t�Z�b�g

#define SOFT_SPRITE_DEST_CHR_OFS	(0x2800)	//�������ރ\�t�g�E�G�A�X�v���C�g��Y�I�t�Z�b�g

#define SOFT_SPRITE_DEST_OFS	(0x50)			//�������ރ\�t�g�E�G�A�X�v���C�g��Y�I�t�Z�b�g
#define SOFT_SPRITE_DEST_OFS2	(0x2828)		//�������ރ\�t�g�E�G�A�X�v���C�g��Y�I�t�Z�b�g

#define	SOFT_SPRITE_SHADOW_OFS	(0x5050)		//�e���������ރA�h���X�̃I�t�Z�b�g

#define SHADOW_OFS				(36)	///<�\�t�g�X�v���C�g�̉e�̃I�t�Z�b�g
#define SOFT_SPRITE_SHADOW_PRI	(-1000)	///<�\�t�g�X�v���C�g�̉e�̃v���C�I���e�B

#define	SS_ANM_SEQ_MAX			(10)	//�\�t�g�X�v���C�g�A�j��MAX

#define	SOFT_SPRITE_CHR_SIZE		(32*32*0x20)	//256x256��BMP�̈�̑傫����
#define	SOFT_SPRITE_COL_SIZE		(0x20*6)		//�p���b�g�T�C�Y
#define	SOFT_SPRITE_TRANS_COL_SIZE	(0x20*4)		//�p���b�g�]���T�C�Y�i������Ԃł́A�e�̕��͓]�����Ȃ��j
#define	SOFT_SPRITE_AREA_H_SIZE		(32)			//256x256��BMP�̈��Y�T�C�Y�i�L�����P�ʁj
#define	SOFT_SPRITE_AREA_W_SIZE		(32)			//256x256��BMP�̈��X�T�C�Y�i�L�����P�ʁj

///<�\�t�g�E�G�A�X�v���C�g�`�惂�[�h
enum{
	SS_DRAW_MODE_NORMAL=0,
	SS_DRAW_MODE_NO_IDENTITY,		///<G3_Identity()���Ă΂Ȃ�	
};

///<VISIBLE_MODE ON/OFF�t���O
#define	VISIBLE_ON	(1)
#define	VISIBLE_OFF	(0)

///<ss_system_flag��`
#define	SS_SYSTEM_FLAG_SHADOW_OFF	(0x00000001)	//�e�̋@�\���I�t�ɂ���

///<SoftSpriteParaCalc�p�p�����[�^�萔��`
enum{
	SS_PARA_POS_X=0,		// X���W
	SS_PARA_POS_Y,			// Y���W
	SS_PARA_POS_Z,			// Z���W
	SS_PARA_POS_OX,			// X���W�I�t�Z�b�g
	SS_PARA_POS_OY,			// Y���W�I�t�Z�b�g
	SS_PARA_POS_OZ,			// Z���W�I�t�Z�b�g
	SS_PARA_VANISH,			// �o�j�b�V���t���O�i0:�\���@1:��\���j
	SS_PARA_ROT_X,			// X������]�p�x
	SS_PARA_ROT_Y,			// Y������]�p�x
	SS_PARA_ROT_Z,			// Z������]�p�x
	SS_PARA_ROT_CX,			// ��]���SX���W�I�t�Z�b�g
	SS_PARA_ROT_CY,			// ��]���SY���W�I�t�Z�b�g
	SS_PARA_AFF_X,			// X�����g��k����
	SS_PARA_AFF_Y,			// Y�����g��k����
	SS_PARA_VISIBLE,		// �r�W�u�����[�h�t���O�i0:OFF�@1:ON�j
	SS_PARA_OFS_POS_X,		// �e�N�X�`�����͈͍���X���W
	SS_PARA_OFS_POS_Y,		// �e�N�X�`�����͈͍���Y���W
	SS_PARA_OFS_SIZE_X,		// �e�N�X�`�����͈�X�T�C�Y
	SS_PARA_OFS_SIZE_Y,		// �e�N�X�`�����͈�Y�T�C�Y
	SS_PARA_SHADOW_X,		// �eX
	SS_PARA_SHADOW_Y,		// �eY
	SS_PARA_SHADOW_OX,		// �e�I�t�Z�b�gX
	SS_PARA_SHADOW_OY,		// �e�I�t�Z�b�gY
	SS_PARA_ALPHA,			// Alpha�l
	SS_PARA_DIFF_R,			// DiffR�l
	SS_PARA_DIFF_G,			// DiffG�l
	SS_PARA_DIFF_B,			// DiffB�l
	SS_PARA_AMB_R,			// AmbR�l
	SS_PARA_AMB_G,			// AmbG�l
	SS_PARA_AMB_B,			// AmbB�l
	SS_PARA_PAL_FADE,		// �p���b�g�t�F�[�h�t���O
	SS_PARA_PAL_RGB,		// �p���b�g�t�F�[�h RGB�l
	SS_PARA_PAL_START_EVY,	// �p���b�g�t�F�[�h START_EVY�l
	SS_PARA_PAL_END_EVY,	// �p���b�g�t�F�[�h END_EVY�l
	SS_PARA_PAL_WAIT,		// �p���b�g�t�F�[�h WAIT�l
	SS_PARA_H_FLIP,			// ���E���]�t���O
	SS_PARA_V_FLIP,			// �㉺���]�t���O
	SS_PARA_DRAW_STOP,		// �����`��X�g�b�v
	SS_PARA_ANM_PAT,		// �A�j���[�V�����p�^�[���i���o�[
	SS_PARA_ARC,			// �A�[�J�C�o�\���̂̃A�h���X
	SS_PARA_MOSAIC,			// ���U�C�N�l
	SS_PARA_SHADOW_HEIGHT,	// Y���W�I�t�Z�b�g�i�e����ǂꂾ�����������j
	SS_PARA_SHADOW_REQ,		// �e�̗L��
	SS_PARA_SHADOW_X_REQ,	// �e��X�����̒Ǐ]�L��
	SS_PARA_SHADOW_Y_REQ,	// �e��Y�����̒Ǐ]�L��
	SS_PARA_SHADOW_AFF_REQ,	// �e�̊g�k�̒Ǐ]�L��
	SS_PARA_SHADOW_SIZE,	// �e�̑傫��

	SS_PARA_END
};

///<�\���p�}�l�[�W���\����
typedef struct soft_sprite_manager SOFT_SPRITE_MANAGER;

///<�\���p�\����
typedef struct soft_sprite SOFT_SPRITE;

///<�A�j���[�V�����e�[�u���\����
typedef struct
{
	s8	patno;
	u8	wait;
}SOFT_SPRITE_ANIME;

///<�A�[�J�C�o�\����
typedef struct
{
	u16	arc_no;			///<�L�����N�^�̃A�[�J�C�o�i���o�[
	u16	index_chr;		///<�ǂݍ��ރL�����N�^�A�[�J�C�o����INDEX
	u16	index_pal;		///<�ǂݍ��ރp���b�g�A�[�J�C�o����INDEX
	u16	strike_mons;	///<�p�b�`�[���̂Ԃ��Ȃǂ𐶐����邩�t���O�i�|�P�����̂Ƃ���p�j
	u8	form_no;		///<�`�ԕω�No�i�~�m���b�`�A�~�m���X�A�f�I�L�V�X�ȂǗp�j
	u8	dummy[3];
	u32	personal_rnd;	///<�Ԃ��𐶐����邽�߂̌�����
}SOFT_SPRITE_ARC;

///<�e�\����
typedef struct
{
	u16	shadow_req		:2;		///<�e�̗L��^����
	u16	shadow_x_req	:1;		///<�e��X�����̒Ǐ]ON/OFF
	u16	shadow_y_req	:1;		///<�e��Y�����̒Ǐ]ON/OFF
	u16	shadow_aff_req	:1;		///<�e�̊g�k�̒Ǐ]ON/OFF
	u16	shadow_size		:2;		///<�e�̑傫��
	u16					:9;		///<���܂�
	s8	shadow_height;			///<�e����ǂꂾ����������
	u8	dummy;

	s16	shadow_x;			///<�e��X���W
	s16	shadow_y;			///<�e��Y���W

	s16	shadow_ox;			///<�e��X�I�t�Z�b�g
	s16	shadow_oy;			///<�e��Y�I�t�Z�b�g
}SOFT_SPRITE_SHADOW;

///<�\�t�g�E�G�A�X�v���C�g�p�����[�^�\����
typedef struct
{
	s16	pos_x;				///<�\��X���W
	s16	pos_y;				///<�\��Y���W

	int	pos_z;				///<�\��Z���W

	s16	pos_ox;				///<�\��X���W�I�t�Z�b�g
	s16	pos_oy;				///<�\��Y���W�I�t�Z�b�g

	int	pos_oz;				///<�\��Z���W�I�t�Z�b�g

	s16	aff_x;				///<X�����g�k�l
	s16	aff_y;				///<Y�����g�k�l

	u16	rot_x;				///<X����]�p�x
	u16	rot_y;				///<y����]�p�x
	u16	rot_z;				///<z����]�p�x
	u16	seq_no;

	s16	rot_cx;				///<��]���SX���W�I�t�Z�b�g
	s16	rot_cy;				///<��]���SY���W�I�t�Z�b�g

	u8	ofs_pos_x;			///<�e�N�X�`�����͈͎w�荶��X���W
	u8	ofs_pos_y;			///<�e�N�X�`�����͈͎w�荶��Y���W
	u8	ofs_size_x;			///<�e�N�X�`�����͈͎w��X�T�C�Y
	u8	ofs_size_y;			///<�e�N�X�`�����͈͎w��Y�T�C�Y

	u8	pal_start_evy;		///<�p���b�g�t�F�[�h START_EVY�l
	u8	pal_end_evy;		///<�p���b�g�t�F�[�h END_EVY�l
	u8	pal_wait;			///<�p���b�g�t�F�[�h wait�l
	u8	pal_wait_tmp;		///<�p���b�g�t�F�[�h wait_tmp�l

	u32	pal_rgb;			///<�p���b�g�t�F�[�h RGB�l

	u32	diff_r			:5;	///<DiffR�l
	u32	diff_g			:5;	///<DiffG�l
	u32	diff_b			:5;	///<DiffB�l
	u32	amb_r			:5;	///<AmbR�l
	u32	amb_g			:5;	///<AmbG�l
	u32	amb_b			:5;	///<AmbB�l
	u32					:2;

	u32	vanish_flag		:1;	///<�o�j�b�V���t���O
	u32	visible_flag	:1;	///<�����[�h�t���O�i���ꂪON�ɂȂ��aff_*�̎w�肪�����ɂȂ�܂��j
	u32	alpha			:5;	///<Alpha�l
	u32	diff_amb_flag	:1;	///<Diffuse Ambient Flag
	u32	spec_emi_flag	:1;	///<Specular Emission Flag
	u32	h_flip			:1;	///<�������]
	u32	v_flip			:1;	///<�������]
	u32	draw_stop		:1;	///<�����`��X�g�b�v
	u32	pal_fade		:1;	///<�p���b�g�t�F�[�h���[�h
	u32	mosaic			:4; ///<���U�C�N�l
	u32					:15;
}SOFT_SPRITE_PARAM;

typedef void (SOFT_SPRITE_MOVE_FUNC)(SOFT_SPRITE *ss,SOFT_SPRITE_PARAM *ssp);

///<extern�錾
extern	void		*SoftSpriteInit(int heap_id);
extern	void		SoftSpriteMain(SOFT_SPRITE_MANAGER *ssm_p);
extern	void		SoftSpriteEnd(SOFT_SPRITE_MANAGER *ssm_p);
extern	void		SoftSpriteAnimeSet(SOFT_SPRITE *ss,int anm_no);
extern	void		SoftSpriteAnimeDataSet(SOFT_SPRITE *ss,SOFT_SPRITE_ANIME *ssanm);
extern	BOOL		SoftSpriteAnimeEndCheck(SOFT_SPRITE *ss);
extern	SOFT_SPRITE	*SoftSpriteAdd(SOFT_SPRITE_MANAGER *ssm_p,
								   SOFT_SPRITE_ARC *ssa,
								   int pos_x,int pos_y,int pos_z,
								   int poly_id,
								   SOFT_SPRITE_ANIME *anm_tbl,
								   SOFT_SPRITE_MOVE_FUNC *move);
extern	SOFT_SPRITE	*SoftSpriteAddNum(SOFT_SPRITE_MANAGER *ssm_p,
								   SOFT_SPRITE_ARC *ssa,
								   int pos_x,int pos_y,int pos_z,
								   int poly_id,
								   int ss_no,
								   SOFT_SPRITE_ANIME *anm_tbl,
								   SOFT_SPRITE_MOVE_FUNC *move);

extern	void		SoftSpriteDel(SOFT_SPRITE *ss);
extern	void		SoftSpriteClear(SOFT_SPRITE_MANAGER *ssm_p);

extern	void		SoftSpriteParaSet(SOFT_SPRITE *ss,int para,int data);
extern	int			SoftSpriteParaGet(SOFT_SPRITE *ss,int para);
extern	void		SoftSpriteParaCalc(SOFT_SPRITE *ss,int para,int data);
extern	void		SoftSpriteVisibleSet(SOFT_SPRITE *ss,int ofs_x,int ofs_y,int size_x,int size_y);
extern	void		SoftSpritePalFadeSet(SOFT_SPRITE *ss,int start_evy,int end_evy,int wait,int rgb);
extern	void		SoftSpritePalFadeSetAll(SOFT_SPRITE_MANAGER *ssm_p,int start_evy,int end_evy,int wait,int rgb);
extern	void		SoftSpritePalFadeOff(SOFT_SPRITE *ss);
extern	BOOL		SoftSpritePalFadeExist(SOFT_SPRITE *ss);
extern	void		SoftSpriteOYCalc(SOFT_SPRITE *ss,int height);

extern	void		SoftSpriteRecover(SOFT_SPRITE_MANAGER *ssm_p);
extern	void		SoftSpriteRecoverSS(SOFT_SPRITE *ss);
extern	void		SoftSpriteSSAPush(SOFT_SPRITE *ss);
extern	void		SoftSpriteSSAPop(SOFT_SPRITE *ss);
extern	void		SoftSpriteTextureTransParamSet(SOFT_SPRITE_MANAGER *ssm_p,u32 ofs,u32 size);
extern	void		SoftSpritePaletteTransParamSet(SOFT_SPRITE_MANAGER *ssm_p,u32 ofs,u32 size);
extern	SOFT_SPRITE_ARC	*SoftSpriteArcPointerGet(SOFT_SPRITE_MANAGER *ssm_p,int num);
extern	SOFT_SPRITE_ARC	*SoftSpriteArcPointerGetSS(SOFT_SPRITE *ss);
extern	void		SoftSpriteArcSet(SOFT_SPRITE_MANAGER *ssm_p,int num,SOFT_SPRITE_ARC *ssa);
extern	void		SoftSpriteArcSetSS(SOFT_SPRITE *ss,SOFT_SPRITE_ARC *ssa);
extern	void		SoftSpriteTextureTrans(SOFT_SPRITE_MANAGER *ssm_p);
extern	void		SoftSpriteDrawModeSet(SOFT_SPRITE_MANAGER *ssm_p,int mode);
extern	BOOL		SoftSpriteExistCheck(SOFT_SPRITE *ss);

extern	void		SoftSpriteSSSystemFlagSet(SOFT_SPRITE_MANAGER *ssm_p,u32 flag);
extern	void		SoftSpriteSSSystemFlagReset(SOFT_SPRITE_MANAGER *ssm_p,u32 flag);

extern void			SoftSprite_MakeStrike( u8* buf, u32 rnd, BOOL animeFlag );

extern void			SoftSpriteChrMask(u8* src);


//----------------------------------------------------------------------
/*
 *	�\�t�g�X�v���C�g�̃A�j���p�^�[����͂��O������s�����߂̎d�g��
 */
//----------------------------------------------------------------------

typedef struct {
	u8  flag;
	u8  pat;
	u8  seq;
	u8  wait;
	u8  loop_cnt[ SS_ANM_SEQ_MAX ];

	const SOFT_SPRITE_ANIME* anim_tbl;
}SOFT_SPRITE_ANIME_WORK;

extern void SoftSprite_SetupAnimeWork( SOFT_SPRITE_ANIME_WORK* wk, const SOFT_SPRITE_ANIME* anim_tbl );
extern int SoftSprite_FwdAnime( SOFT_SPRITE_ANIME_WORK* wk );


#endif __SOFTSPRITE_H_
