
//============================================================================================
/**
 * @file	softsprite.h
 * @bfief	ソフトウエアスプライトを使用した表示プログラム
 * @author	HisashiSogabe
 * @date	05.06.08
 */
//============================================================================================

#ifndef __SOFTSPRITE_H_
#define __SOFTSPRITE_H_

#define	SOFT_SPRITE_MAX			(4)		//登録できる最大数
#define SOFT_SPRITE_SIZE_X		(80)	//読み込むソフトウエアスプライトのXサイズ
#define SOFT_SPRITE_SIZE_Y		(80)	//読み込むソフトウエアスプライトのYサイズ

#define SOFT_SPRITE_SHADOW_X	(64)	//影のXサイズ
#define SOFT_SPRITE_SHADOW_Y	(16)	//影のYサイズ

#define SOFT_SPRITE_SRC_X		(160)	//読み込むソフトウエアスプライトのXサイズ
#define SOFT_SPRITE_SRC_Y		(80)	//読み込むソフトウエアスプライトのYサイズ

#define SOFT_SPRITE_SRC_Y_OFS	(0x50)	//読み込むソフトウエアスプライトのYオフセット
#define SOFT_SPRITE_DEST_Y_OFS	(0x80)	//書き込むソフトウエアスプライトのYオフセット

#define SOFT_SPRITE_DEST_CHR_OFS	(0x2800)	//書き込むソフトウエアスプライトのYオフセット

#define SOFT_SPRITE_DEST_OFS	(0x50)			//書き込むソフトウエアスプライトのYオフセット
#define SOFT_SPRITE_DEST_OFS2	(0x2828)		//書き込むソフトウエアスプライトのYオフセット

#define	SOFT_SPRITE_SHADOW_OFS	(0x5050)		//影を書き込むアドレスのオフセット

#define SHADOW_OFS				(36)	///<ソフトスプライトの影のオフセット
#define SOFT_SPRITE_SHADOW_PRI	(-1000)	///<ソフトスプライトの影のプライオリティ

#define	SS_ANM_SEQ_MAX			(10)	//ソフトスプライトアニメMAX

#define	SOFT_SPRITE_CHR_SIZE		(32*32*0x20)	//256x256のBMP領域の大きさ分
#define	SOFT_SPRITE_COL_SIZE		(0x20*6)		//パレットサイズ
#define	SOFT_SPRITE_TRANS_COL_SIZE	(0x20*4)		//パレット転送サイズ（初期状態では、影の分は転送しない）
#define	SOFT_SPRITE_AREA_H_SIZE		(32)			//256x256のBMP領域のYサイズ（キャラ単位）
#define	SOFT_SPRITE_AREA_W_SIZE		(32)			//256x256のBMP領域のXサイズ（キャラ単位）

///<ソフトウエアスプライト描画モード
enum{
	SS_DRAW_MODE_NORMAL=0,
	SS_DRAW_MODE_NO_IDENTITY,		///<G3_Identity()を呼ばない	
};

///<VISIBLE_MODE ON/OFFフラグ
#define	VISIBLE_ON	(1)
#define	VISIBLE_OFF	(0)

///<ss_system_flag定義
#define	SS_SYSTEM_FLAG_SHADOW_OFF	(0x00000001)	//影の機能をオフにする

///<SoftSpriteParaCalc用パラメータ定数定義
enum{
	SS_PARA_POS_X=0,		// X座標
	SS_PARA_POS_Y,			// Y座標
	SS_PARA_POS_Z,			// Z座標
	SS_PARA_POS_OX,			// X座標オフセット
	SS_PARA_POS_OY,			// Y座標オフセット
	SS_PARA_POS_OZ,			// Z座標オフセット
	SS_PARA_VANISH,			// バニッシュフラグ（0:表示　1:非表示）
	SS_PARA_ROT_X,			// X方向回転角度
	SS_PARA_ROT_Y,			// Y方向回転角度
	SS_PARA_ROT_Z,			// Z方向回転角度
	SS_PARA_ROT_CX,			// 回転中心X座標オフセット
	SS_PARA_ROT_CY,			// 回転中心Y座標オフセット
	SS_PARA_AFF_X,			// X方向拡大縮小率
	SS_PARA_AFF_Y,			// Y方向拡大縮小率
	SS_PARA_VISIBLE,		// ビジブルモードフラグ（0:OFF　1:ON）
	SS_PARA_OFS_POS_X,		// テクスチャ可視範囲左上X座標
	SS_PARA_OFS_POS_Y,		// テクスチャ可視範囲左上Y座標
	SS_PARA_OFS_SIZE_X,		// テクスチャ可視範囲Xサイズ
	SS_PARA_OFS_SIZE_Y,		// テクスチャ可視範囲Yサイズ
	SS_PARA_SHADOW_X,		// 影X
	SS_PARA_SHADOW_Y,		// 影Y
	SS_PARA_SHADOW_OX,		// 影オフセットX
	SS_PARA_SHADOW_OY,		// 影オフセットY
	SS_PARA_ALPHA,			// Alpha値
	SS_PARA_DIFF_R,			// DiffR値
	SS_PARA_DIFF_G,			// DiffG値
	SS_PARA_DIFF_B,			// DiffB値
	SS_PARA_AMB_R,			// AmbR値
	SS_PARA_AMB_G,			// AmbG値
	SS_PARA_AMB_B,			// AmbB値
	SS_PARA_PAL_FADE,		// パレットフェードフラグ
	SS_PARA_PAL_RGB,		// パレットフェード RGB値
	SS_PARA_PAL_START_EVY,	// パレットフェード START_EVY値
	SS_PARA_PAL_END_EVY,	// パレットフェード END_EVY値
	SS_PARA_PAL_WAIT,		// パレットフェード WAIT値
	SS_PARA_H_FLIP,			// 左右反転フラグ
	SS_PARA_V_FLIP,			// 上下反転フラグ
	SS_PARA_DRAW_STOP,		// 強制描画ストップ
	SS_PARA_ANM_PAT,		// アニメーションパターンナンバー
	SS_PARA_ARC,			// アーカイバ構造体のアドレス
	SS_PARA_MOSAIC,			// モザイク値
	SS_PARA_SHADOW_HEIGHT,	// Y座標オフセット（影からどれだけ浮かすか）
	SS_PARA_SHADOW_REQ,		// 影の有無
	SS_PARA_SHADOW_X_REQ,	// 影のX方向の追従有無
	SS_PARA_SHADOW_Y_REQ,	// 影のY方向の追従有無
	SS_PARA_SHADOW_AFF_REQ,	// 影の拡縮の追従有無
	SS_PARA_SHADOW_SIZE,	// 影の大きさ

	SS_PARA_END
};

///<表示用マネージャ構造体
typedef struct soft_sprite_manager SOFT_SPRITE_MANAGER;

///<表示用構造体
typedef struct soft_sprite SOFT_SPRITE;

///<アニメーションテーブル構造体
typedef struct
{
	s8	patno;
	u8	wait;
}SOFT_SPRITE_ANIME;

///<アーカイバ構造体
typedef struct
{
	u16	arc_no;			///<キャラクタのアーカイバナンバー
	u16	index_chr;		///<読み込むキャラクタアーカイバ内のINDEX
	u16	index_pal;		///<読み込むパレットアーカイバ内のINDEX
	u16	strike_mons;	///<パッチールのぶちなどを生成するかフラグ（ポケモンのとき専用）
	u8	form_no;		///<形態変化No（ミノムッチ、ミノメス、デオキシスなど用）
	u8	dummy[3];
	u32	personal_rnd;	///<ぶちを生成するための個性乱数
}SOFT_SPRITE_ARC;

///<影構造体
typedef struct
{
	u16	shadow_req		:2;		///<影の有り／無し
	u16	shadow_x_req	:1;		///<影のX方向の追従ON/OFF
	u16	shadow_y_req	:1;		///<影のY方向の追従ON/OFF
	u16	shadow_aff_req	:1;		///<影の拡縮の追従ON/OFF
	u16	shadow_size		:2;		///<影の大きさ
	u16					:9;		///<あまり
	s8	shadow_height;			///<影からどれだけ浮かすか
	u8	dummy;

	s16	shadow_x;			///<影のX座標
	s16	shadow_y;			///<影のY座標

	s16	shadow_ox;			///<影のXオフセット
	s16	shadow_oy;			///<影のYオフセット
}SOFT_SPRITE_SHADOW;

///<ソフトウエアスプライトパラメータ構造体
typedef struct
{
	s16	pos_x;				///<表示X座標
	s16	pos_y;				///<表示Y座標

	int	pos_z;				///<表示Z座標

	s16	pos_ox;				///<表示X座標オフセット
	s16	pos_oy;				///<表示Y座標オフセット

	int	pos_oz;				///<表示Z座標オフセット

	s16	aff_x;				///<X方向拡縮値
	s16	aff_y;				///<Y方向拡縮値

	u16	rot_x;				///<X軸回転角度
	u16	rot_y;				///<y軸回転角度
	u16	rot_z;				///<z軸回転角度
	u16	seq_no;

	s16	rot_cx;				///<回転中心X座標オフセット
	s16	rot_cy;				///<回転中心Y座標オフセット

	u8	ofs_pos_x;			///<テクスチャ可視範囲指定左上X座標
	u8	ofs_pos_y;			///<テクスチャ可視範囲指定左上Y座標
	u8	ofs_size_x;			///<テクスチャ可視範囲指定Xサイズ
	u8	ofs_size_y;			///<テクスチャ可視範囲指定Yサイズ

	u8	pal_start_evy;		///<パレットフェード START_EVY値
	u8	pal_end_evy;		///<パレットフェード END_EVY値
	u8	pal_wait;			///<パレットフェード wait値
	u8	pal_wait_tmp;		///<パレットフェード wait_tmp値

	u32	pal_rgb;			///<パレットフェード RGB値

	u32	diff_r			:5;	///<DiffR値
	u32	diff_g			:5;	///<DiffG値
	u32	diff_b			:5;	///<DiffB値
	u32	amb_r			:5;	///<AmbR値
	u32	amb_g			:5;	///<AmbG値
	u32	amb_b			:5;	///<AmbB値
	u32					:2;

	u32	vanish_flag		:1;	///<バニッシュフラグ
	u32	visible_flag	:1;	///<可視モードフラグ（これがONになるとaff_*の指定が無効になります）
	u32	alpha			:5;	///<Alpha値
	u32	diff_amb_flag	:1;	///<Diffuse Ambient Flag
	u32	spec_emi_flag	:1;	///<Specular Emission Flag
	u32	h_flip			:1;	///<水平反転
	u32	v_flip			:1;	///<垂直反転
	u32	draw_stop		:1;	///<強制描画ストップ
	u32	pal_fade		:1;	///<パレットフェードモード
	u32	mosaic			:4; ///<モザイク値
	u32					:15;
}SOFT_SPRITE_PARAM;

typedef void (SOFT_SPRITE_MOVE_FUNC)(SOFT_SPRITE *ss,SOFT_SPRITE_PARAM *ssp);

///<extern宣言
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
 *	ソフトスプライトのアニメパターン解析を外部から行うための仕組み
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
