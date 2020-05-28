
//============================================================================================
/**
 * @file	softsprite.c
 * @bfief	ソフトウエアスプライトを使用した表示プログラム
 * @author	HisashiSogabe
 * @date	05.06.08
 */
//============================================================================================

#include "common.h"
#include "system/arc_tool.h"
#include "system/palanm.h"
#include "system/softsprite.h"
#include "softsprite_def.h"

#include "poketool/pokegra/otherpoke.naix"

#include "patch.dat"	//パッチールのぶちデータ

void	*SoftSpriteInit(int heap_id);
void	SoftSpriteMain(SOFT_SPRITE_MANAGER *ssm_p);
void	SoftSpriteEnd(SOFT_SPRITE_MANAGER *ssm_p);
SOFT_SPRITE	*SoftSpriteAdd(SOFT_SPRITE_MANAGER *ssm_p,SOFT_SPRITE_ARC *ssa,
						   int pos_x,int pos_y,int pos_z,
						   int poly_id,
						   SOFT_SPRITE_ANIME *anm_tbl,
						   SOFT_SPRITE_MOVE_FUNC *move);

SOFT_SPRITE	*SoftSpriteAddNum(SOFT_SPRITE_MANAGER *ssm_p,SOFT_SPRITE_ARC *ssa,
						   int pos_x,int pos_y,int pos_z,
						   int poly_id,
						   int ss_no,
						   SOFT_SPRITE_ANIME *anm_tbl,
						   SOFT_SPRITE_MOVE_FUNC *move);

void	SoftSpriteDel(SOFT_SPRITE *ss);
void	SoftSpriteClear(SOFT_SPRITE_MANAGER *ssm_p);

void	SoftSpriteAnimeSet(SOFT_SPRITE *ss,int anm_no);
void	SoftSpriteAnimeDataSet(SOFT_SPRITE *ss,SOFT_SPRITE_ANIME *ssanm);
BOOL	SoftSpriteAnimeEndCheck(SOFT_SPRITE *ss);
void	SoftSpriteParaSet(SOFT_SPRITE *ss,int para,int data);
int		SoftSpriteParaGet(SOFT_SPRITE *ss,int para);
void	SoftSpriteParaCalc(SOFT_SPRITE *ss,int para,int data);
void	SoftSpriteVisibleSet(SOFT_SPRITE *ss,int ofs_x,int ofs_y,int size_x,int size_y);
void	SoftSpritePalFadeSet(SOFT_SPRITE *ss,int start_evy,int end_evy,int wait,int rgb);
void	SoftSpritePalFadeSetAll(SOFT_SPRITE_MANAGER *ssm_p,int start_evy,int end_evy,int wait,int rgb);
void	SoftSpritePalFadeOff(SOFT_SPRITE *ss);
BOOL	SoftSpritePalFadeExist(SOFT_SPRITE *ss);
void	SoftSpriteOYCalc(SOFT_SPRITE *ss,int height);

void	SoftSpriteRecover(SOFT_SPRITE_MANAGER *ssm_p);
void	SoftSpriteRecoverSS(SOFT_SPRITE *ss);

void	SoftSpriteSSAPush(SOFT_SPRITE *ss);
void	SoftSpriteSSAPop(SOFT_SPRITE *ss);

void	SoftSpriteTextureTransParamSet(SOFT_SPRITE_MANAGER *ssm_p,u32 ofs,u32 size);
void	SoftSpritePaletteTransParamSet(SOFT_SPRITE_MANAGER *ssm_p,u32 ofs,u32 size);

SOFT_SPRITE_ARC	*SoftSpriteArcPointerGet(SOFT_SPRITE_MANAGER *ssm_p,int num);
SOFT_SPRITE_ARC	*SoftSpriteArcPointerGetSS(SOFT_SPRITE *ss);

void	SoftSpriteArcSet(SOFT_SPRITE_MANAGER *ssm_p,int num,SOFT_SPRITE_ARC *ssa);
void	SoftSpriteArcSetSS(SOFT_SPRITE *ss,SOFT_SPRITE_ARC *ssa);

void	SoftSpriteTextureTrans(SOFT_SPRITE_MANAGER *ssm_p);

void	SoftSpriteDrawModeSet(SOFT_SPRITE_MANAGER *ssm_p,int mode);
BOOL	SoftSpriteExistCheck(SOFT_SPRITE *ss);

void	SoftSpriteSSSystemFlagSet(SOFT_SPRITE_MANAGER *ssm_p,u32 flag);
void	SoftSpriteSSSystemFlagReset(SOFT_SPRITE_MANAGER *ssm_p,u32 flag);

void	SoftSprite_MakeStrike( u8* buf, u32 rnd, BOOL animeFlag );

void	SoftSpriteChrMask(u8 *src);

static	void	SoftSpriteTextureFieldMake(SOFT_SPRITE_MANAGER *ssm_p);
static	void	SoftSpriteTexturePaletteMake(SOFT_SPRITE_MANAGER *ssm_p);
static	void	SoftSpriteAnime(SOFT_SPRITE *ss);

static	u8	BitReverse(u8 data);

static	void	SoftSpriteStrikeMake(SOFT_SPRITE *ss,u8 *buf);


//============================================================================================
/**
 *	ソフトウエアスプライトシステムの初期化
 *
 * @param[in]	heap_id		領域を確保するヒープ領域のID
 */
//============================================================================================
void	*SoftSpriteInit(int heap_id)
{
	SOFT_SPRITE_MANAGER *ssm_p;
	int					i,j,x,y;
	NNSG2dCharacterData	*cd_src;
	u8					*src;
	void				*buf;

	ssm_p=sys_AllocMemory(heap_id,sizeof(SOFT_SPRITE_MANAGER));

	ssm_p->heap_id=heap_id;
	ssm_p->cnt=0;
	ssm_p->texture_trans_ofs=0;								///<テクスチャの転送先アドレスのオフセット
	ssm_p->texture_trans_size=SOFT_SPRITE_CHR_SIZE;			///<テクスチャデータ転送サイズ
	ssm_p->palette_trans_ofs=0;								///<テクスチャパレットの転送先アドレスのオフセット
	ssm_p->palette_trans_size=SOFT_SPRITE_TRANS_COL_SIZE;	///<テクスチャパレットデータ転送サイズ

	ssm_p->dest_chr=sys_AllocMemory(heap_id,SOFT_SPRITE_CHR_SIZE);
	ssm_p->dest_col=sys_AllocMemory(heap_id,SOFT_SPRITE_COL_SIZE);
	MI_CpuClearFast(ssm_p->dest_col,sizeof(SOFT_SPRITE_COL_SIZE));
	ssm_p->dest_col_temp=sys_AllocMemory(heap_id,SOFT_SPRITE_COL_SIZE);
	MI_CpuClearFast(ssm_p->dest_col_temp,sizeof(SOFT_SPRITE_COL_SIZE));

	for(i=0;i<SOFT_SPRITE_MAX;i++){
		MI_CpuClearFast(&ssm_p->ss[i],sizeof(SOFT_SPRITE));
	}

	NNS_G2dSetupSoftwareSpriteCamera();

	ssm_p->mode=SS_DRAW_MODE_NORMAL;

	//影データ読み込み
	buf=ArchiveDataLoadMalloc(ARC_OTHER_POKE,NARC_otherpoke_kage_NCBR,ssm_p->heap_id);
	NNS_G2dGetUnpackedCharacterData(buf,&cd_src);
	ssm_p->cd_dest.pixelFmt=cd_src->pixelFmt;
	ssm_p->cd_dest.mapingType=cd_src->mapingType;
	ssm_p->cd_dest.characterFmt=cd_src->characterFmt;
	src=cd_src->pRawData;
	SoftSpriteChrMask(src);

	//透明色で塗りつぶし
	MI_CpuFill8(&ssm_p->dest_chr[0],src[0],SOFT_SPRITE_CHR_SIZE);

	for(y=0;y<SOFT_SPRITE_SRC_Y;y++){
		for(x=0;x<SOFT_SPRITE_SRC_X/4;x++){
			ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+SOFT_SPRITE_SHADOW_OFS]=src[y*SOFT_SPRITE_SRC_Y_OFS+x];
		}
	}
	
	sys_FreeMemoryEz(buf);

	ssm_p->texture_trans_req=1;
	ssm_p->palette_trans_req=1;

	return ssm_p;
}

//============================================================================================
/**
 * @param
 */
//============================================================================================

static const int SoftSpritePatTable[4][2][4]={
	//0
	{
		{SOFT_SPRITE_SIZE_X*0,SOFT_SPRITE_SIZE_Y*0,SOFT_SPRITE_SIZE_X*1,SOFT_SPRITE_SIZE_Y*1},
		{SOFT_SPRITE_SIZE_X*1,SOFT_SPRITE_SIZE_Y*0,SOFT_SPRITE_SIZE_X*2,SOFT_SPRITE_SIZE_Y*1},
	},
	//1
	{
		{SOFT_SPRITE_SIZE_X*0,SOFT_SPRITE_SIZE_Y*1,SOFT_SPRITE_SIZE_X*1,SOFT_SPRITE_SIZE_Y*2},
		{SOFT_SPRITE_SIZE_X*1,SOFT_SPRITE_SIZE_Y*1,SOFT_SPRITE_SIZE_X*2,SOFT_SPRITE_SIZE_Y*2},
	},
	//2
	{
		{SOFT_SPRITE_SIZE_X*0,SOFT_SPRITE_SIZE_Y*2,SOFT_SPRITE_SIZE_X*1,SOFT_SPRITE_SIZE_Y*3},
		{SOFT_SPRITE_SIZE_X*1,SOFT_SPRITE_SIZE_Y*2,SOFT_SPRITE_SIZE_X*2,SOFT_SPRITE_SIZE_Y*3},
	},
	//3
	{
		{SOFT_SPRITE_SIZE_X*2,SOFT_SPRITE_SIZE_Y*0,SOFT_SPRITE_SIZE_X*3,SOFT_SPRITE_SIZE_Y*1},
		{SOFT_SPRITE_SIZE_X*2,SOFT_SPRITE_SIZE_Y*1,SOFT_SPRITE_SIZE_X*3,SOFT_SPRITE_SIZE_Y*2},
	},
};

static const int SoftSpriteShadowTable[4][4]={
	//0：ダミーデータ（実際は表示されない）
	{SOFT_SPRITE_SIZE_X*2,SOFT_SPRITE_SIZE_Y*2+ 0,SOFT_SPRITE_SIZE_X*2+64,SOFT_SPRITE_SIZE_Y*2+16},
	//1
	{SOFT_SPRITE_SIZE_X*2,SOFT_SPRITE_SIZE_Y*2+ 0,SOFT_SPRITE_SIZE_X*2+64,SOFT_SPRITE_SIZE_Y*2+16},
	//2
	{SOFT_SPRITE_SIZE_X*2,SOFT_SPRITE_SIZE_Y*2+16,SOFT_SPRITE_SIZE_X*2+64,SOFT_SPRITE_SIZE_Y*2+32},
	//3
	{SOFT_SPRITE_SIZE_X*2,SOFT_SPRITE_SIZE_Y*2+32,SOFT_SPRITE_SIZE_X*2+64,SOFT_SPRITE_SIZE_Y*2+48},
};

//============================================================================================
/**
 *	ソフトウエアスプライトメインルーチン
 *
 * @param[in]	ssm_p	ソフトウエアスプライトマネージャシステムワークのポインタ
 */
//============================================================================================
void	SoftSpriteMain(SOFT_SPRITE_MANAGER *ssm_p)
{
	int	i;
	int	size_x,size_y;
	int	u0,v0,u1,v1;

	SoftSpriteTextureFieldMake(ssm_p);
	SoftSpriteTexturePaletteMake(ssm_p);

	NNS_G3dGeFlushBuffer();

	G3_PushMtx();

	G3_TexImageParam(ssm_p->imgp.attr.fmt,
					 GX_TEXGEN_TEXCOORD,
					 ssm_p->imgp.attr.sizeS,
					 ssm_p->imgp.attr.sizeT,
					 GX_TEXREPEAT_NONE,
					 GX_TEXFLIP_NONE,
					 ssm_p->imgp.attr.plttUse,
					 ssm_p->texture_trans_ofs);

	for(i=0;i<SOFT_SPRITE_MAX;i++){
		if((ssm_p->ss[i].exist)&&(ssm_p->ss[i].ssp.vanish_flag==0)&&(ssm_p->ss[i].ssp.draw_stop==0)){
			if(ssm_p->ss[i].move!=NULL){
				ssm_p->ss[i].move(&ssm_p->ss[i],&ssm_p->ss[i].ssp);
			}

			NNS_G3dGeFlushBuffer();

			if(ssm_p->mode!=SS_DRAW_MODE_NO_IDENTITY){
				// マトリクス初期化
				G3_Identity();
			}
			
			SoftSpriteAnime(&ssm_p->ss[i]);

			G3_TexPlttBase((u32)(ssm_p->palette_trans_ofs+32*i),ssm_p->imgp.attr.fmt);
			G3_Translate((ssm_p->ss[i].ssp.pos_x+ssm_p->ss[i].ssp.rot_cx)<<FX32_SHIFT,
						 (ssm_p->ss[i].ssp.pos_y+ssm_p->ss[i].ssp.rot_cy)<<FX32_SHIFT,
						 ssm_p->ss[i].ssp.pos_z<<FX32_SHIFT);
			G3_RotX(FX_SinIdx(ssm_p->ss[i].ssp.rot_x),FX_CosIdx(ssm_p->ss[i].ssp.rot_x));
			G3_RotY(FX_SinIdx(ssm_p->ss[i].ssp.rot_y),FX_CosIdx(ssm_p->ss[i].ssp.rot_y));
			G3_RotZ(FX_SinIdx(ssm_p->ss[i].ssp.rot_z),FX_CosIdx(ssm_p->ss[i].ssp.rot_z));
			G3_Translate(-((ssm_p->ss[i].ssp.pos_x+ssm_p->ss[i].ssp.rot_cx)<<FX32_SHIFT),
						 -((ssm_p->ss[i].ssp.pos_y+ssm_p->ss[i].ssp.rot_cy)<<FX32_SHIFT),
						 -(ssm_p->ss[i].ssp.pos_z<<FX32_SHIFT));

			G3_MaterialColorDiffAmb(GX_RGB(ssm_p->ss[i].ssp.diff_r,ssm_p->ss[i].ssp.diff_g,ssm_p->ss[i].ssp.diff_b),
									GX_RGB(ssm_p->ss[i].ssp.amb_r,ssm_p->ss[i].ssp.amb_g,ssm_p->ss[i].ssp.amb_b),TRUE);
			G3_MaterialColorSpecEmi(GX_RGB(16,16,16),GX_RGB( 0, 0, 0),FALSE);

			G3_PolygonAttr(GX_LIGHTMASK_NONE,			// no lights
						   GX_POLYGONMODE_MODULATE,		// modulation mode
						   GX_CULL_NONE,				// cull back
						   ssm_p->ss[i].poly_id,		// polygon ID(0 - 63)
						   ssm_p->ss[i].ssp.alpha,		// alpha(0 - 31)
						   0							// OR of GXPolygonAttrMisc's value
						   );

			if(ssm_p->ss[i].ssp.visible_flag){
				u0=SoftSpritePatTable[i][ssm_p->ss[i].anm_pat][0]+ssm_p->ss[i].ssp.ofs_pos_x;
				u1=SoftSpritePatTable[i][ssm_p->ss[i].anm_pat][0]+ssm_p->ss[i].ssp.ofs_pos_x+ssm_p->ss[i].ssp.ofs_size_x;
				v0=SoftSpritePatTable[i][ssm_p->ss[i].anm_pat][1]+ssm_p->ss[i].ssp.ofs_pos_y;
				v1=SoftSpritePatTable[i][ssm_p->ss[i].anm_pat][1]+ssm_p->ss[i].ssp.ofs_pos_y+ssm_p->ss[i].ssp.ofs_size_y;
				NNS_G2dDrawSpriteFast(ssm_p->ss[i].ssp.pos_x-SOFT_SPRITE_SIZE_X/2+
									  ssm_p->ss[i].ssp.ofs_pos_x+ssm_p->ss[i].ssp.pos_ox,
									  ssm_p->ss[i].ssp.pos_y-SOFT_SPRITE_SIZE_Y/2+
									  ssm_p->ss[i].ssp.ofs_pos_y+ssm_p->ss[i].ssp.pos_oy-ssm_p->ss[i].sss.shadow_height,
									  ssm_p->ss[i].ssp.pos_z+ssm_p->ss[i].ssp.pos_oz,
									  ssm_p->ss[i].ssp.ofs_size_x,
									  ssm_p->ss[i].ssp.ofs_size_y,
									  u0,v0,u1,v1);
			}
			else{
				size_x=(SOFT_SPRITE_SIZE_X*ssm_p->ss[i].ssp.aff_x)>>8;
				size_y=(SOFT_SPRITE_SIZE_Y*ssm_p->ss[i].ssp.aff_y)>>8;
				u0=SoftSpritePatTable[i][ssm_p->ss[i].anm_pat][0];
				u1=SoftSpritePatTable[i][ssm_p->ss[i].anm_pat][2];
				v0=SoftSpritePatTable[i][ssm_p->ss[i].anm_pat][1];
				v1=SoftSpritePatTable[i][ssm_p->ss[i].anm_pat][3];
				NNS_G2dDrawSpriteFast(ssm_p->ss[i].ssp.pos_x-size_x/2+ssm_p->ss[i].ssp.pos_ox,
									  ssm_p->ss[i].ssp.pos_y-size_y/2+ssm_p->ss[i].ssp.pos_oy-ssm_p->ss[i].sss.shadow_height,
									  ssm_p->ss[i].ssp.pos_z+ssm_p->ss[i].ssp.pos_oz,
									  size_x,
									  size_y,
									  u0,v0,u1,v1);
			}

			if((ssm_p->ss[i].sss.shadow_req)&&
			   (ssm_p->ss[i].sss.shadow_size)&&
			   (ssm_p->ss[i].ssp.visible_flag==0)&&
			   ((ssm_p->ss_system_flag&SS_SYSTEM_FLAG_SHADOW_OFF)==0)){
				if(ssm_p->mode!=SS_DRAW_MODE_NO_IDENTITY){
					// マトリクス初期化
					G3_Identity();
				}
				G3_TexPlttBase((u32)(ssm_p->palette_trans_ofs+32*(3+ssm_p->ss[i].sss.shadow_req)),ssm_p->imgp.attr.fmt);
				if(ssm_p->ss[i].sss.shadow_aff_req){
					size_x=(SOFT_SPRITE_SHADOW_X*ssm_p->ss[i].ssp.aff_x)>>8;
					size_y=(SOFT_SPRITE_SHADOW_Y*ssm_p->ss[i].ssp.aff_y)>>8;
				}
				else{
					size_x=SOFT_SPRITE_SHADOW_X;
					size_y=SOFT_SPRITE_SHADOW_Y;
				}
				if(ssm_p->ss[i].sss.shadow_x_req){
					ssm_p->ss[i].sss.shadow_x=ssm_p->ss[i].ssp.pos_x+
											  ssm_p->ss[i].ssp.pos_ox+ssm_p->ss[i].sss.shadow_ox;
				}
				if(ssm_p->ss[i].sss.shadow_y_req){
					ssm_p->ss[i].sss.shadow_y=ssm_p->ss[i].ssp.pos_y+
											  ssm_p->ss[i].ssp.pos_oy+ssm_p->ss[i].sss.shadow_oy;
				}
				u0=SoftSpriteShadowTable[ssm_p->ss[i].sss.shadow_size][0];
				v0=SoftSpriteShadowTable[ssm_p->ss[i].sss.shadow_size][1];
				u1=SoftSpriteShadowTable[ssm_p->ss[i].sss.shadow_size][2];
				v1=SoftSpriteShadowTable[ssm_p->ss[i].sss.shadow_size][3];
				NNS_G2dDrawSpriteFast(ssm_p->ss[i].sss.shadow_x-size_x/2,
									  ssm_p->ss[i].sss.shadow_y-size_y/2,
									  SOFT_SPRITE_SHADOW_PRI,
									  size_x,
									  size_y,
									  u0,v0,u1,v1);
			}
		}
	}
	G3_PopMtx(1);
}

//============================================================================================
/**
 *	ソフトウエアスプライトマネージャの終了
 *
 * @param[in]	ssm_p	ソフトウエアスプライトマネージャシステムワークのポインタ
 */
//============================================================================================
void	SoftSpriteEnd(SOFT_SPRITE_MANAGER *ssm_p)
{
	sys_FreeMemoryEz(ssm_p->dest_chr);
	sys_FreeMemoryEz(ssm_p->dest_col);
	sys_FreeMemoryEz(ssm_p->dest_col_temp);
	sys_FreeMemoryEz(ssm_p);
}

//============================================================================================
/**
 *	アニメーションをセット
 *
 * @param[in]	ss		アニメーションをセットするソフトウエアスプライト管理ワークポインタ
 * @param[in]	anm_no	セットするアニメーションナンバー
 */
//============================================================================================
void	SoftSpriteAnimeSet(SOFT_SPRITE *ss,int anm_no)
{
	int	i;

	//今回は、汎用性をなくして、anm_noをフラグとして処理（0:アニメしない　1:アニメする）
	ss->anm_seq=0;
	for(i=0;i<SS_ANM_SEQ_MAX;i++){
		ss->anm_loop[i]=0;
	}
	if(ss->ssanm[ss->anm_seq].patno==-1){
		ss->anm_pat=0;
	}
	else{
		ss->anm_no=1;
		ss->anm_pat=ss->ssanm[ss->anm_seq].patno;
		ss->anm_wait=ss->ssanm[ss->anm_seq].wait;
	}
}

//============================================================================================
/**
 *	アニメーションデータをセット
 *
 * @param[in]	ss		アニメーションをセットするソフトウエアスプライト管理ワークポインタ
 * @param[in]	ssanm	セットするアニメーションデータ
 */
//============================================================================================
void	SoftSpriteAnimeDataSet(SOFT_SPRITE *ss,SOFT_SPRITE_ANIME *ssanm)
{
	MI_CpuCopy8(ssanm,&ss->ssanm,sizeof(SOFT_SPRITE_ANIME)*10);
}

//============================================================================================
/**
 *	アニメーションの終了をチェック
 *
 * @param[in]	ss		アニメーションの終了をチェックするソフトウエアスプライト管理ワークポインタ
 *
 * @retval	FALSE:終了	TRUE:継続中
 */
//============================================================================================
BOOL	SoftSpriteAnimeEndCheck(SOFT_SPRITE *ss)
{
	return (ss->anm_no!=0);
}

//============================================================================================
/**
 *	ソフトウエアスプライトを登録する
 *
 * @param[in]	ssm_p	ソフトウエアスプライトマネージャシステムワークのポインタ
 * @param[in]	ssa		ソフトウエアスプライトヘッダーデータのポインタ
 * @param[in]	pos_x	ソフトウエアスプライト初期位置（X座標）
 * @param[in]	pos_y	ソフトウエアスプライト初期位置（Y座標）
 * @param[in]	pos_z	ソフトウエアスプライト初期位置（Z座標）
 * @param[in]	poly_id	描画するポリゴンID
 * @param[in]	anm_tbl	アニメーションテーブルのポインタ
 * @param[in]	move	動作関数のポインタ（SoftSpriteMainから呼ばれます）
 *
 * @retval		SOFT_SPRITE *	ソフトウエアスプライト管理ワークのポインタ
 *
 */
//============================================================================================
SOFT_SPRITE	*SoftSpriteAdd(SOFT_SPRITE_MANAGER *ssm_p,SOFT_SPRITE_ARC *ssa,
						   int pos_x,int pos_y,int pos_z,
						   int poly_id,
						   SOFT_SPRITE_ANIME *anm_tbl,
						   SOFT_SPRITE_MOVE_FUNC *move)
{
	int	ss_no;

	for(ss_no=0;ss_no<SOFT_SPRITE_MAX;ss_no++){
		if(ssm_p->ss[ss_no].exist==0){
			break;
		}
	}
	GF_ASSERT_MSG( ss_no != SOFT_SPRITE_MAX ,"SoftSpriteAdd:SOFT_SPRITE_MAX Over!");

	return SoftSpriteAddNum(ssm_p,ssa,pos_x,pos_y,pos_z,poly_id,ss_no,anm_tbl,move);
}

//============================================================================================
/**
 *	ソフトウエアスプライトを登録する（セットする場所の指定もあり）
 *
 * @param[in]	ssm_p	ソフトウエアスプライトマネージャシステムワークのポインタ
 * @param[in]	ssa		ソフトウエアスプライトヘッダーデータのポインタ
 * @param[in]	pos_x	ソフトウエアスプライト初期位置（X座標）
 * @param[in]	pos_y	ソフトウエアスプライト初期位置（Y座標）
 * @param[in]	pos_z	ソフトウエアスプライト初期位置（Z座標）
 * @param[in]	poly_id	描画するポリゴンID
 * @param[in]	ss_no	登録するSS構造体配列の添え字
 * @param[in]	anm_tbl	アニメーションテーブルのポインタ
 * @param[in]	move	動作関数のポインタ（SoftSpriteMainから呼ばれます）
 *
 * @retval		SOFT_SPRITE *	ソフトウエアスプライト管理ワークのポインタ
 *
 */
//============================================================================================
SOFT_SPRITE	*SoftSpriteAddNum(SOFT_SPRITE_MANAGER *ssm_p,SOFT_SPRITE_ARC *ssa,
						   int pos_x,int pos_y,int pos_z,
						   int poly_id,
						   int ss_no,
						   SOFT_SPRITE_ANIME *anm_tbl,
						   SOFT_SPRITE_MOVE_FUNC *move)
{
	GF_ASSERT_MSG( ssm_p->ss[ss_no].exist == 0 ,"ExistFlagAlreadySet");

	MI_CpuClearFast(&ssm_p->ss[ss_no],sizeof(SOFT_SPRITE));

	ssm_p->ss[ss_no].exist=1;
	ssm_p->ss[ss_no].make_req=1;
	ssm_p->ss[ss_no].pal_req=1;
	ssm_p->ss[ss_no].poly_id=poly_id;
	ssm_p->ss[ss_no].ssa=*ssa;
	ssm_p->ss[ss_no].ssa_push=*ssa;
	ssm_p->ss[ss_no].ssp.pos_x=pos_x;
	ssm_p->ss[ss_no].ssp.pos_y=pos_y;
	ssm_p->ss[ss_no].ssp.pos_z=pos_z;
	ssm_p->ss[ss_no].ssp.aff_x=0x100;
	ssm_p->ss[ss_no].ssp.aff_y=0x100;
	ssm_p->ss[ss_no].ssp.alpha=31;
	ssm_p->ss[ss_no].ssp.diff_r=31;
	ssm_p->ss[ss_no].ssp.diff_g=31;
	ssm_p->ss[ss_no].ssp.diff_b=31;
	ssm_p->ss[ss_no].ssp.amb_r=16;
	ssm_p->ss[ss_no].ssp.amb_g=16;
	ssm_p->ss[ss_no].ssp.amb_b=16;
	ssm_p->ss[ss_no].move=move;
	ssm_p->ss[ss_no].sss.shadow_x=pos_x;
	ssm_p->ss[ss_no].sss.shadow_y=pos_y;
	ssm_p->ss[ss_no].sss.shadow_x_req=1;
	ssm_p->ss[ss_no].sss.shadow_y_req=1;
	ssm_p->ss[ss_no].sss.shadow_aff_req=1;
	if(anm_tbl!=NULL){
		MI_CpuCopy8(anm_tbl,&ssm_p->ss[ss_no].ssanm,sizeof(SOFT_SPRITE_ANIME)*10);
	}
	return &ssm_p->ss[ss_no];
}

//============================================================================================
/**
 *	登録されているソフトウエアスプライトを削除
 *
 * @param[in]	ss		削除する対象のソフトスプライト構造体ポインタ
 */
//============================================================================================
void	SoftSpriteDel(SOFT_SPRITE *ss)
{
	ss->exist=0;
}

//============================================================================================
/**
 *	登録されているソフトウエアスプライトをすべて削除
 *
 * @param[in]	ssm_p	ソフトスプライトマネージャー構造体ポインタ
 */
//============================================================================================
void	SoftSpriteClear(SOFT_SPRITE_MANAGER *ssm_p)
{
	int	i;

	for(i=0;i<SOFT_SPRITE_MAX;i++){
		SoftSpriteDel(&ssm_p->ss[i]);
	}
}

//============================================================================================
/**
 *	ソフトスプライトのパラメータをセットする
 *
 * @param[in]	ss		セットする対象のソフトスプライト構造体ポインタ
 * @param[in]	para	セットするパラメータ（softsprite.hに定義）
 * @param[in]	data	セットする値
 */
//============================================================================================
void	SoftSpriteParaSet(SOFT_SPRITE *ss,int para,int data)
{
	switch(para){
	case SS_PARA_POS_X:
		ss->ssp.pos_x=data;
		break;
	case SS_PARA_POS_Y:
		ss->ssp.pos_y=data;
		break;
	case SS_PARA_POS_Z:
		ss->ssp.pos_z=data;
		break;
	case SS_PARA_POS_OX:			// X座標オフセット
		ss->ssp.pos_ox=data;
		break;
	case SS_PARA_POS_OY:			// Y座標オフセット
		ss->ssp.pos_oy=data;
		break;
	case SS_PARA_POS_OZ:			// Z座標オフセット
		ss->ssp.pos_oz=data;
		break;
	case SS_PARA_VANISH:
		ss->ssp.vanish_flag=data;
		break;
	case SS_PARA_ROT_X:
		ss->ssp.rot_x=data;
		break;
	case SS_PARA_ROT_Y:
		ss->ssp.rot_y=data;
		break;
	case SS_PARA_ROT_Z:
		ss->ssp.rot_z=data;
		break;
	case SS_PARA_ROT_CX:
		ss->ssp.rot_cx=data;
		break;
	case SS_PARA_ROT_CY:
		ss->ssp.rot_cy=data;
		break;
	case SS_PARA_AFF_X:
		ss->ssp.aff_x=data;
		break;
	case SS_PARA_AFF_Y:
		ss->ssp.aff_y=data;
		break;
	case SS_PARA_VISIBLE:
		ss->ssp.visible_flag=data;
		break;
	case SS_PARA_OFS_POS_X:
		ss->ssp.ofs_pos_x=data;
		break;
	case SS_PARA_OFS_POS_Y:
		ss->ssp.ofs_pos_y=data;
		break;
	case SS_PARA_OFS_SIZE_X:
		ss->ssp.ofs_size_x=data;
		break;
	case SS_PARA_OFS_SIZE_Y:
		ss->ssp.ofs_size_y=data;
		break;
	case SS_PARA_SHADOW_X:
		ss->sss.shadow_x=data;
		break;
	case SS_PARA_SHADOW_Y:
		ss->sss.shadow_y=data;
		break;
	case SS_PARA_SHADOW_OX:
		ss->sss.shadow_ox=data;
		break;
	case SS_PARA_SHADOW_OY:
		ss->sss.shadow_oy=data;
		break;
	case SS_PARA_ALPHA:
		ss->ssp.alpha=data;
		break;
	case SS_PARA_DIFF_R:		// DiffR値
		ss->ssp.diff_r=data;
		break;
	case SS_PARA_DIFF_G:		// DiffG値
		ss->ssp.diff_g=data;
		break;
	case SS_PARA_DIFF_B:		// DiffB値
		ss->ssp.diff_b=data;
		break;
	case SS_PARA_AMB_R:			// AmbR値
		ss->ssp.amb_r=data;
		break;
	case SS_PARA_AMB_G:			// AmbG値
		ss->ssp.amb_g=data;
		break;
	case SS_PARA_AMB_B:			// AmbB値
		ss->ssp.amb_b=data;
		break;
	case SS_PARA_PAL_FADE:		// パレットフェードフラグ
		ss->ssp.pal_fade=data;
		ss->pal_req=1;			//パレットフェード係数を操作した場合は、パレット生成リクエストを出す
		break;
	case SS_PARA_PAL_RGB:		// パレットフェード RGB値
		ss->ssp.pal_rgb=data;
		ss->pal_req=1;			//パレットフェード係数を操作した場合は、パレット生成リクエストを出す
		break;
	case SS_PARA_PAL_START_EVY:	// パレットフェード START_EVY値
		ss->ssp.pal_start_evy=data;
		ss->pal_req=1;			//パレットフェード係数を操作した場合は、パレット生成リクエストを出す
		break;
	case SS_PARA_PAL_END_EVY:	// パレットフェード END_EVY値
		ss->ssp.pal_end_evy=data;
		ss->pal_req=1;			//パレットフェード係数を操作した場合は、パレット生成リクエストを出す
		break;
	case SS_PARA_PAL_WAIT:		// パレットフェード wait値
		ss->ssp.pal_wait=data;
		break;
	case SS_PARA_H_FLIP:
		ss->ssp.h_flip=data;
		ss->make_req=1;				//フリップフラグを操作した場合は、テクスチャ生成リクエストを出す
		break;
	case SS_PARA_V_FLIP:
		ss->ssp.v_flip=data;
		ss->make_req=1;				//フリップフラグを操作した場合は、テクスチャ生成リクエストを出す
		break;
	case SS_PARA_DRAW_STOP:
		ss->ssp.draw_stop=data;
		break;
	case SS_PARA_ANM_PAT:
		ss->anm_pat=data;
		break;
	case SS_PARA_MOSAIC:
		ss->ssp.mosaic=data;
		ss->make_req=1;				//モザイク値を操作した場合は、テクスチャ生成リクエストを出す
		break;
	case SS_PARA_SHADOW_HEIGHT:
		ss->sss.shadow_height=data;
		break;
	case SS_PARA_SHADOW_REQ:
		ss->sss.shadow_req=data;
		ss->pal_req=1;				//影有無値を操作した場合は、パレット生成リクエストを出す
		break;
	case SS_PARA_SHADOW_X_REQ:
		ss->sss.shadow_x_req=data;
		break;
	case SS_PARA_SHADOW_Y_REQ:
		ss->sss.shadow_y_req=data;
		break;
	case SS_PARA_SHADOW_AFF_REQ:
		ss->sss.shadow_aff_req=data;
		break;
	case SS_PARA_SHADOW_SIZE:
		ss->sss.shadow_size=data;
		break;
	}
}

//============================================================================================
/**
 *	ソフトスプライトのパラメータを取得する
 *
 * @param[in]	ss		取得する対象のソフトスプライト構造体ポインタ
 * @param[in]	para	取得するパラメータ（softsprite.hに定義）
 */
//============================================================================================
int		SoftSpriteParaGet(SOFT_SPRITE *ss,int para)
{
	switch(para){
	case SS_PARA_POS_X:
		return ss->ssp.pos_x;
	case SS_PARA_POS_Y:
		return ss->ssp.pos_y;
	case SS_PARA_POS_Z:
		return ss->ssp.pos_z;
	case SS_PARA_POS_OX:
		return ss->ssp.pos_ox;
	case SS_PARA_POS_OY:
		return ss->ssp.pos_oy;
	case SS_PARA_POS_OZ:
		return ss->ssp.pos_oz;
	case SS_PARA_VANISH:
		return ss->ssp.vanish_flag;
	case SS_PARA_ROT_X:
		return ss->ssp.rot_x;
	case SS_PARA_ROT_Y:
		return ss->ssp.rot_y;
	case SS_PARA_ROT_Z:
		return ss->ssp.rot_z;
	case SS_PARA_ROT_CX:
		return ss->ssp.rot_cx;
	case SS_PARA_ROT_CY:
		return ss->ssp.rot_cy;
	case SS_PARA_AFF_X:
		return ss->ssp.aff_x;
	case SS_PARA_AFF_Y:
		return ss->ssp.aff_y;
	case SS_PARA_VISIBLE:
		return ss->ssp.visible_flag;
	case SS_PARA_OFS_POS_X:
		return ss->ssp.ofs_pos_x;
	case SS_PARA_OFS_POS_Y:
		return ss->ssp.ofs_pos_y;
	case SS_PARA_OFS_SIZE_X:
		return ss->ssp.ofs_size_x;
	case SS_PARA_OFS_SIZE_Y:
		return ss->ssp.ofs_size_y;
	case SS_PARA_SHADOW_X:
		return ss->sss.shadow_x;
	case SS_PARA_SHADOW_Y:
		return ss->sss.shadow_y;
	case SS_PARA_SHADOW_OX:
		return ss->sss.shadow_ox;
	case SS_PARA_SHADOW_OY:
		return ss->sss.shadow_oy;
	case SS_PARA_ALPHA:
		return ss->ssp.alpha;
	case SS_PARA_DIFF_R:		// DiffR値
		return ss->ssp.diff_r;
	case SS_PARA_DIFF_G:		// DiffG値
		return ss->ssp.diff_g;
	case SS_PARA_DIFF_B:		// DiffB値
		return ss->ssp.diff_b;
	case SS_PARA_AMB_R:			// AmbR値
		return ss->ssp.amb_r;
	case SS_PARA_AMB_G:			// AmbG値
		return ss->ssp.amb_g;
	case SS_PARA_AMB_B:			// AmbB値
		return ss->ssp.amb_b;
	case SS_PARA_PAL_FADE:		// パレットフェードフラグ
		return ss->ssp.pal_fade;
	case SS_PARA_PAL_RGB:		// パレットフェード RGB値
		return ss->ssp.pal_rgb;
	case SS_PARA_PAL_START_EVY:	// パレットフェード START_EVY値
		return ss->ssp.pal_start_evy;
	case SS_PARA_PAL_END_EVY:	// パレットフェード END_EVY値
		return ss->ssp.pal_end_evy;
	case SS_PARA_PAL_WAIT:		// パレットフェード wait値
		return ss->ssp.pal_wait;
	case SS_PARA_H_FLIP:
		return ss->ssp.h_flip;
	case SS_PARA_V_FLIP:
		return ss->ssp.v_flip;
	case SS_PARA_DRAW_STOP:
		return ss->ssp.draw_stop;
	case SS_PARA_ANM_PAT:
		return ss->anm_pat;
	case SS_PARA_MOSAIC:
		return ss->ssp.mosaic;
	case SS_PARA_SHADOW_HEIGHT:
		return ss->sss.shadow_height;
	case SS_PARA_SHADOW_REQ:
		return ss->sss.shadow_req;
	case SS_PARA_SHADOW_X_REQ:
		return ss->sss.shadow_x_req;
	case SS_PARA_SHADOW_Y_REQ:
		return ss->sss.shadow_y_req;
	case SS_PARA_SHADOW_AFF_REQ:
		return ss->sss.shadow_aff_req;
		break;
	case SS_PARA_SHADOW_SIZE:
		return ss->sss.shadow_size;
		break;
	}
	GF_ASSERT((0)&&"ここにくるのはおかしい");
	return 0;
}

//============================================================================================
/**
 *	ソフトスプライトのパラメータ計算をする
 *
 * @param[in]	ss		計算をする対象のソフトスプライト構造体ポインタ
 * @param[in]	para	計算をするパラメータ（softsprite.hに定義）
 * @param[in]	data	加減算する値
 *
 */
//============================================================================================
void	SoftSpriteParaCalc(SOFT_SPRITE *ss,int para,int data)
{
	switch(para){
	case SS_PARA_POS_X:
		ss->ssp.pos_x+=data;
		break;
	case SS_PARA_POS_Y:
		ss->ssp.pos_y+=data;
		break;
	case SS_PARA_POS_Z:
		ss->ssp.pos_z+=data;
		break;
	case SS_PARA_POS_OX:			// X座標オフセット
		ss->ssp.pos_ox+=data;
		break;
	case SS_PARA_POS_OY:			// Y座標オフセット
		ss->ssp.pos_oy+=data;
		break;
	case SS_PARA_POS_OZ:			// Z座標オフセット
		ss->ssp.pos_oz+=data;
		break;
	case SS_PARA_VANISH:
		ss->ssp.vanish_flag+=data;
		break;
	case SS_PARA_ROT_X:
		ss->ssp.rot_x+=data;
		break;
	case SS_PARA_ROT_Y:
		ss->ssp.rot_y+=data;
		break;
	case SS_PARA_ROT_Z:
		ss->ssp.rot_z+=data;
		break;
	case SS_PARA_ROT_CX:
		ss->ssp.rot_cx+=data;
		break;
	case SS_PARA_ROT_CY:
		ss->ssp.rot_cy+=data;
		break;
	case SS_PARA_AFF_X:
		ss->ssp.aff_x+=data;
		break;
	case SS_PARA_AFF_Y:
		ss->ssp.aff_y+=data;
		break;
	case SS_PARA_VISIBLE:
		ss->ssp.visible_flag+=data;
		break;
	case SS_PARA_OFS_POS_X:
		ss->ssp.ofs_pos_x+=data;
		break;
	case SS_PARA_OFS_POS_Y:
		ss->ssp.ofs_pos_y+=data;
		break;
	case SS_PARA_OFS_SIZE_X:
		ss->ssp.ofs_size_x+=data;
		break;
	case SS_PARA_OFS_SIZE_Y:
		ss->ssp.ofs_size_y+=data;
		break;
	case SS_PARA_SHADOW_X:
		ss->sss.shadow_x+=data;
		break;
	case SS_PARA_SHADOW_Y:
		ss->sss.shadow_y+=data;
		break;
	case SS_PARA_SHADOW_OX:
		ss->sss.shadow_ox+=data;
		break;
	case SS_PARA_SHADOW_OY:
		ss->sss.shadow_oy+=data;
		break;
	case SS_PARA_ALPHA:
		ss->ssp.alpha+=data;
		break;
	case SS_PARA_DIFF_R:		// DiffR値
		ss->ssp.diff_r+=data;
		break;
	case SS_PARA_DIFF_G:		// DiffG値
		ss->ssp.diff_g+=data;
		break;
	case SS_PARA_DIFF_B:		// DiffB値
		ss->ssp.diff_b+=data;
		break;
	case SS_PARA_AMB_R:			// AmbR値
		ss->ssp.amb_r+=data;
		break;
	case SS_PARA_AMB_G:			// AmbG値
		ss->ssp.amb_g+=data;
		break;
	case SS_PARA_AMB_B:			// AmbB値
		ss->ssp.amb_b+=data;
		break;
	case SS_PARA_PAL_FADE:		// パレットフェードフラグ
		ss->ssp.pal_fade+=data;
		ss->pal_req=1;			//パレットフェード係数を操作した場合は、パレット生成リクエストを出す
		break;
	case SS_PARA_PAL_RGB:		// パレットフェード RGB値
		ss->ssp.pal_rgb+=data;
		ss->pal_req=1;			//パレットフェード係数を操作した場合は、パレット生成リクエストを出す
		break;
	case SS_PARA_PAL_START_EVY:	// パレットフェード START_EVY値
		ss->ssp.pal_start_evy+=data;
		ss->pal_req=1;			//パレットフェード係数を操作した場合は、パレット生成リクエストを出す
		break;
	case SS_PARA_PAL_END_EVY:	// パレットフェード END_EVY値
		ss->ssp.pal_end_evy+=data;
		ss->pal_req=1;			//パレットフェード係数を操作した場合は、パレット生成リクエストを出す
		break;
	case SS_PARA_PAL_WAIT:		// パレットフェード wait値
		ss->ssp.pal_wait+=data;
		break;
	case SS_PARA_H_FLIP:
		ss->ssp.h_flip+=data;
		ss->make_req=1;				//フリップフラグを操作した場合は、テクスチャ生成リクエストを出す
		break;
	case SS_PARA_V_FLIP:
		ss->ssp.v_flip+=data;
		ss->make_req=1;				//フリップフラグを操作した場合は、テクスチャ生成リクエストを出す
		break;
	case SS_PARA_DRAW_STOP:
		ss->ssp.draw_stop+=data;
		break;
	case SS_PARA_ANM_PAT:
		ss->anm_pat+=data;
		break;
	case SS_PARA_MOSAIC:
		ss->ssp.mosaic+=data;
		ss->make_req=1;				//モザイク値を操作した場合は、テクスチャ生成リクエストを出す
		break;
	case SS_PARA_SHADOW_HEIGHT:
		ss->sss.shadow_height+=data;
		break;
	case SS_PARA_SHADOW_REQ:
		ss->sss.shadow_req+=data;
		ss->pal_req=1;				//影有無値を操作した場合は、パレット生成リクエストを出す
		break;
	case SS_PARA_SHADOW_X_REQ:
		ss->sss.shadow_x_req+=data;
		break;
	case SS_PARA_SHADOW_Y_REQ:
		ss->sss.shadow_y_req+=data;
		break;
	case SS_PARA_SHADOW_AFF_REQ:
		ss->sss.shadow_aff_req+=data;
		break;
	case SS_PARA_SHADOW_SIZE:
		ss->sss.shadow_size+=data;
		break;
	}
}

//============================================================================================
/**
 *	ソフトスプライトVISIBLEモードパラメータをセットする
 *
 * @param[in]	ss		セットする対象のソフトスプライト構造体ポインタ
 * @param[in]	ofs_x	セットするパラメータ（テクスチャ可視範囲指定左上X座標）
 * @param[in]	ofs_y	セットするパラメータ（テクスチャ可視範囲指定左上Y座標）
 * @param[in]	size_x	セットするパラメータ（テクスチャ可視範囲Xサイズ）
 * @param[in]	size_y	セットするパラメータ（テクスチャ可視範囲Yサイズ）
 */
//============================================================================================
void	SoftSpriteVisibleSet(SOFT_SPRITE *ss,int ofs_x,int ofs_y,int size_x,int size_y)
{
	ss->ssp.visible_flag=1;
	ss->ssp.ofs_pos_x=ofs_x;
	ss->ssp.ofs_pos_y=ofs_y;
	ss->ssp.ofs_size_x=size_x;
	ss->ssp.ofs_size_y=size_y;

}

//============================================================================================
/**
 *	ソフトスプライトパレットフェードモードパラメータをセットする
 *
 * @param[in]	ss			セットする対象のソフトスプライト構造体ポインタ
 * @param[in]	start_evy	セットするパラメータ（フェードさせる色に対する開始割合16段階）
 * @param[in]	end_evy		セットするパラメータ（フェードさせる色に対する終了割合16段階）
 * @param[in]	wait		セットするパラメータ（ウェイト）
 * @param[in]	rgb			セットするパラメータ（フェードさせる色）
 */
//============================================================================================
void	SoftSpritePalFadeSet(SOFT_SPRITE *ss,int start_evy,int end_evy,int wait,int rgb)
{
	ss->ssp.pal_fade=1;
	ss->ssp.pal_start_evy=start_evy;
	ss->ssp.pal_end_evy=end_evy;
	ss->ssp.pal_wait=0;
	ss->ssp.pal_wait_tmp=wait;
	ss->ssp.pal_rgb=rgb;
}

//============================================================================================
/**
 *	ソフトスプライトパレットフェードモードパラメータをセットする（登録されているスプライトすべて）
 *
 * @param[in]	ssm_p		ソフトスプライトマネージャー構造体へのポインタ
 * @param[in]	start_evy	セットするパラメータ（フェードさせる色に対する開始割合16段階）
 * @param[in]	end_evy		セットするパラメータ（フェードさせる色に対する終了割合16段階）
 * @param[in]	wait		セットするパラメータ（ウェイト）
 * @param[in]	rgb			セットするパラメータ（フェードさせる色）
 */
//============================================================================================
void	SoftSpritePalFadeSetAll(SOFT_SPRITE_MANAGER *ssm_p,int start_evy,int end_evy,int wait,int rgb)
{
	int	ss_no;

	for(ss_no=0;ss_no<SOFT_SPRITE_MAX;ss_no++){
		if(ssm_p->ss[ss_no].exist){
			ssm_p->ss[ss_no].ssp.pal_fade=1;
			ssm_p->ss[ss_no].ssp.pal_start_evy=start_evy;
			ssm_p->ss[ss_no].ssp.pal_end_evy=end_evy;
			ssm_p->ss[ss_no].ssp.pal_wait=0;
			ssm_p->ss[ss_no].ssp.pal_wait_tmp=wait;
			ssm_p->ss[ss_no].ssp.pal_rgb=rgb;
		}
	}
}

//============================================================================================
/**
 *	ソフトスプライトパレットフェードモードをオフにする
 *
 * @param[in]	ss		セットする対象のソフトスプライト構造体ポインタ
 */
//============================================================================================
void	SoftSpritePalFadeOff(SOFT_SPRITE *ss)
{
	ss->ssp.pal_fade=0;
	ss->ssp.pal_start_evy=0;
	ss->ssp.pal_end_evy=0;
	ss->ssp.pal_wait=0;
	ss->ssp.pal_wait_tmp=0;
	ss->ssp.pal_rgb=0;
	ss->pal_req=1;
}

//============================================================================================
/**
 *	ソフトスプライトパレットフェード中かチェックにする
 *
 * @param[in]	ss		チェック対象のソフトスプライト構造体ポインタ
 *
 * @retval	TRUE:フェード中　FALSE：フェード終了
 */
//============================================================================================
BOOL	SoftSpritePalFadeExist(SOFT_SPRITE *ss)
{
	return (ss->ssp.pal_fade==1);
}

//============================================================================================
/**
 *	ソフトスプライトの拡縮時のOYを計算する
 *	（ポケモン登場時に足位置を合わせて拡大、縮小させる）
 *
 * @param[in]	ss		計算対象のソフトスプライト構造体ポインタ
 */
//============================================================================================
void	SoftSpriteOYCalc(SOFT_SPRITE *ss,int height)
{
	ss->ssp.pos_oy=((SOFT_SPRITE_SIZE_Y/2)-height)-((((SOFT_SPRITE_SIZE_Y/2)-height)*ss->ssp.aff_y)>>8);
}

//============================================================================================
//		外部非公開関数群
//============================================================================================

//------------------------------------------------------------------
/**
 * アニメ進行処理
 *
 * @param   anm_flag[io]	アニメ中フラグワーク
 * @param   pat[out]		アニメパターンを受け取る変数ポインタ
 * @param   seq	[io]		シーケンス保存ワーク
 * @param   wait[io]		ウェイト保存ワーク
 * @param   loop_cnt[io]	ループカウンタ保存ワーク（u8 * SS_ANM_SEQ_MAX）
 * @param   anm_tbl[in]		アニメテーブルポインタ
 */
//------------------------------------------------------------------
static inline void SoftSpriteAnimeCore( u8* anm_flag, u8* pat, u8* seq, u8* wait, u8* loop_cnt, const SOFT_SPRITE_ANIME* anm_tbl )
{
	if(*anm_flag)
	{
		if( (*wait) == 0 )
		{
			(*seq)++;
			//ループ処理
			while( anm_tbl[*seq].patno < -1 )
			{
				loop_cnt[*seq]++;
				if(	(anm_tbl[*seq].wait == loop_cnt[*seq]) || (anm_tbl[*seq].wait == 0) )
				{
					loop_cnt[*seq] = 0;
					*seq++;
				}
				else
				{
					*seq = anm_tbl[*seq].patno*-1-2;
				}
			}
			if(	(anm_tbl[*seq].patno == -1) || ((*seq) >= SS_ANM_SEQ_MAX) )
			{
				(*pat) = 0;
				(*anm_flag) = 0;
				return;
			}
			(*pat) = anm_tbl[*seq].patno;
			(*wait) = anm_tbl[*seq].wait;
		}
		else{
			(*wait)--;
		}
	}
}

//============================================================================================
/**
 * @param
 */
//============================================================================================
static	void	SoftSpriteAnime(SOFT_SPRITE *ss)
{
	SoftSpriteAnimeCore( &(ss->anm_no), &(ss->anm_pat), &(ss->anm_seq), &(ss->anm_wait), ss->anm_loop, ss->ssanm );
}

//------------------------------------------------------------------
/**
 * アニメ進行処理を外部から行うためのワーク領域セットアップ
 *
 * @param   wk			進行処理ワークポインタ
 * @param   anim_tbl	アニメテーブル
 *
 */
//------------------------------------------------------------------
void SoftSprite_SetupAnimeWork( SOFT_SPRITE_ANIME_WORK* wk, const SOFT_SPRITE_ANIME* anim_tbl )
{
	int i;

	wk->flag = TRUE;
	wk->seq = 0;
	wk->pat = anim_tbl[0].patno;
	wk->wait = anim_tbl[0].wait;
	wk->anim_tbl = anim_tbl;
	for(i=0; i<SS_ANM_SEQ_MAX; i++)
	{
		wk->loop_cnt[i] = 0;
	}
}

//------------------------------------------------------------------
/**
 * アニメ進行処理（外部公開）
 *
 * @param   wk		進行処理ワークポインタ
 *
 * @retval  int		0～1  アニメパターン
 *					-1    アニメ終了
 */
//------------------------------------------------------------------
int SoftSprite_FwdAnime( SOFT_SPRITE_ANIME_WORK* wk )
{
	if( wk->flag )
	{
		SoftSpriteAnimeCore( &wk->flag, &wk->pat, &wk->seq, &wk->wait, wk->loop_cnt, wk->anim_tbl );
		return wk->pat;
	}

	return -1;
}

//============================================================================================
/**
 *	ソフトウエアスプライトのテクスチャ領域を復旧する
 *
 * @param[in]	ssm_p		ソフトスプライトマネージャーのポインタ
 */
//============================================================================================
void	SoftSpriteRecover(SOFT_SPRITE_MANAGER *ssm_p)
{
	int	i;

	for(i=0;i<SOFT_SPRITE_MAX;i++){
		if(ssm_p->ss[i].exist){
			SoftSpriteRecoverSS(&ssm_p->ss[i]);
		}
	}
}

//============================================================================================
/**
 *	ソフトウエアスプライトのテクスチャ領域を復旧する
 *
 * @param[in]	ss		ソフトスプライトのポインタ
 */
//============================================================================================
void	SoftSpriteRecoverSS(SOFT_SPRITE *ss)
{
	ss->make_req=1;
	ss->pal_req=1;
}

//============================================================================================
/**
 *	ソフトウエアスプライトのSSAをスタック領域に退避する
 *
 * @param[in]	ss		退避対象のソフトスプライト構造体ポインタ
 */
//============================================================================================
void	SoftSpriteSSAPush(SOFT_SPRITE *ss)
{
	ss->ssa_push=ss->ssa;
	ss->sss_push=ss->sss;
}

//============================================================================================
/**
 *	スタックに退避したソフトウエアスプライトのSSAを復旧する
 *
 * @param[in]	ss		復旧対象のソフトスプライト構造体ポインタ
 */
//============================================================================================
void	SoftSpriteSSAPop(SOFT_SPRITE *ss)
{
	ss->ssa=ss->ssa_push;
	ss->sss=ss->sss_push;
	ss->make_req=1;
	ss->pal_req=1;
}

//============================================================================================
/**
 *	ソフトウエアスプライトのテクスチャ転送の開始位置とサイズを変更する
 *
 * @param[in]	ssm_p		ソフトスプライトマネージャーのポインタ
 * @param[in]	ofs			転送開始位置のオフセット
 * @param[in]	size		転送サイズ
 */
//============================================================================================
void	SoftSpriteTextureTransParamSet(SOFT_SPRITE_MANAGER *ssm_p,u32 ofs,u32 size)
{
	ssm_p->texture_trans_ofs=ofs;
	ssm_p->texture_trans_size=size;
}

//============================================================================================
/**
 *	ソフトウエアスプライトのテクスチャパレット転送の開始位置とサイズを変更する
 *
 * @param[in]	ssm_p		ソフトスプライトマネージャーのポインタ
 * @param[in]	ofs			転送開始位置のオフセット
 * @param[in]	size		転送サイズ
 */
//============================================================================================
void	SoftSpritePaletteTransParamSet(SOFT_SPRITE_MANAGER *ssm_p,u32 ofs,u32 size)
{
	ssm_p->palette_trans_ofs=ofs;
	ssm_p->palette_trans_size=size;
}

//============================================================================================
/**
 *	ソフトウエアスプライトのアーカイバ情報のポインタを取得
 *
 * @param[in]	ssm_p		ソフトスプライトマネージャーのポインタ
 * @param[in]	num			何番目のスプライトのポインタを取得するか指定
 */
//============================================================================================
SOFT_SPRITE_ARC	*SoftSpriteArcPointerGet(SOFT_SPRITE_MANAGER *ssm_p,int num)
{
	return &ssm_p->ss[num].ssa;
}

//============================================================================================
/**
 *	ソフトウエアスプライトのアーカイバ情報のポインタを取得
 *
 * @param[in]	ss		ソフトスプライトのポインタ
 */
//============================================================================================
SOFT_SPRITE_ARC	*SoftSpriteArcPointerGetSS(SOFT_SPRITE *ss)
{
	return &ss->ssa;
}

//============================================================================================
/**
 *	ソフトウエアスプライトのアーカイバ情報を代入
 *
 * @param[in]	ssm_p		ソフトスプライトマネージャーのポインタ
 * @param[in]	num			何番目のスプライトのポインタに代入するか指定
 * @param[in]	ssa			代入するアーカイバ情報
 */
//============================================================================================
void	SoftSpriteArcSet(SOFT_SPRITE_MANAGER *ssm_p,int num,SOFT_SPRITE_ARC *ssa)
{
	ssm_p->ss[num].ssa=*ssa;
	ssm_p->ss[num].make_req=1;
	ssm_p->ss[num].pal_req=1;
}

//============================================================================================
/**
 *	ソフトウエアスプライトのアーカイバ情報を代入
 *
 * @param[in]	ss		ソフトスプライトのポインタ
 * @param[in]	ssa			代入するアーカイバ情報
 */
//============================================================================================
void	SoftSpriteArcSetSS(SOFT_SPRITE *ss,SOFT_SPRITE_ARC *ssa)
{
	ss->ssa=*ssa;
	ss->make_req=1;
	ss->pal_req=1;
}

//============================================================================================
/**
 *	仮想テクスチャ領域をテクスチャ領域に転送
 *
 * @param[in]	ssm_p		ソフトスプライトマネージャーのポインタ
 */
//============================================================================================
void	SoftSpriteTextureTrans(SOFT_SPRITE_MANAGER *ssm_p)
{
	if(ssm_p->texture_trans_req){
		ssm_p->texture_trans_req=0;

		NNS_G2dInitImageProxy(&ssm_p->imgp);

		ssm_p->cd_dest.H=SOFT_SPRITE_AREA_H_SIZE;
		ssm_p->cd_dest.W=SOFT_SPRITE_AREA_W_SIZE;
		ssm_p->cd_dest.szByte=ssm_p->texture_trans_size;
		ssm_p->cd_dest.pRawData=ssm_p->dest_chr;

		NNS_G2dLoadImage2DMapping(&ssm_p->cd_dest,
								  ssm_p->texture_trans_ofs,
								  NNS_G2D_VRAM_TYPE_3DMAIN,
								  &ssm_p->imgp);
	}

	if(ssm_p->palette_trans_req){
		ssm_p->palette_trans_req=0;

		NNS_G2dInitImagePaletteProxy(&ssm_p->pltp);

		ssm_p->pd_dest.szByte=ssm_p->palette_trans_size;
		ssm_p->pd_dest.pRawData=ssm_p->dest_col;
		NNS_G2dLoadPalette(&ssm_p->pd_dest,
						   ssm_p->palette_trans_ofs,
						   NNS_G2D_VRAM_TYPE_3DMAIN,
						   &ssm_p->pltp);
	}
}

//============================================================================================
/**
 *	ソフトウエアスプライトのDrawModeをセットする
 *
 * @param[in]	ssm_p		ソフトスプライトマネージャーのポインタ
 * @param[in]	mode		セットするモード
 */
//============================================================================================
void	SoftSpriteDrawModeSet(SOFT_SPRITE_MANAGER *ssm_p,int mode)
{
	ssm_p->mode=mode;
}

//============================================================================================
/**
 *	ソフトウエアスプライト使用チェックをする
 *
 * @param[in]	ss			ソフトスプライト構造体のポインタ
 *
 * @retval	FALSE:未使用　TRUE:使用中
 */
//============================================================================================
BOOL	SoftSpriteExistCheck(SOFT_SPRITE *ss)
{
	GF_ASSERT(ss!=NULL);
	return (ss->exist!=0);
}

//============================================================================================
/**
 *	ソフトウエアスプライトシステムフラグをセット
 *
 * @param[in]	ssm_p	ソフトスプライトマネージャー構造体のポインタ
 * @param[in]	flag	セットするフラグ
 */
//============================================================================================
void	SoftSpriteSSSystemFlagSet(SOFT_SPRITE_MANAGER *ssm_p,u32 flag)
{
	ssm_p->ss_system_flag|=flag;
}

//============================================================================================
/**
 *	ソフトウエアスプライトシステムフラグをリセット
 *
 * @param[in]	ssm_p	ソフトスプライトマネージャー構造体のポインタ
 * @param[in]	flag	リセットするフラグ
 */
//============================================================================================
void	SoftSpriteSSSystemFlagReset(SOFT_SPRITE_MANAGER *ssm_p,u32 flag)
{
	ssm_p->ss_system_flag&=(flag^0xffffffff);
}

//============================================================================================
/**
 *	ソフトウエアスプライトのテクスチャ領域を生成する
 *
 * @param[in]	ssm_p		ソフトスプライトマネージャーのポインタ
 */
//============================================================================================
static	void	SoftSpriteTextureFieldMake(SOFT_SPRITE_MANAGER *ssm_p)
{
	NNSG2dCharacterData	*cd_src;
	int		i,x,y;
	u8		*src;
	void	*buf;
	u8		req;

	req=0;

	for(i=0;i<SOFT_SPRITE_MAX;i++){
		if((ssm_p->ss[i].exist)&&(ssm_p->ss[i].make_req)){
			ssm_p->ss[i].make_req=0;
			req=1;
			//キャラデータ読み込み
			buf=ArchiveDataLoadMalloc(ssm_p->ss[i].ssa.arc_no,ssm_p->ss[i].ssa.index_chr,ssm_p->heap_id);
			NNS_G2dGetUnpackedCharacterData(buf,&cd_src);
			ssm_p->cd_dest.pixelFmt=cd_src->pixelFmt;
			ssm_p->cd_dest.mapingType=cd_src->mapingType;
			ssm_p->cd_dest.characterFmt=cd_src->characterFmt;
			src=cd_src->pRawData;
			SoftSpriteChrMask(src);
			SoftSpriteStrikeMake(&ssm_p->ss[i],src);
			if(i==3){
				for(y=0;y<SOFT_SPRITE_SRC_Y;y++){
					for(x=0;x<SOFT_SPRITE_SRC_X/2;x++){
						if(x<SOFT_SPRITE_SRC_X/4){
							if((ssm_p->ss[i].ssp.h_flip)&&(ssm_p->ss[i].ssp.v_flip)){
								ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+SOFT_SPRITE_DEST_OFS]=
								BitReverse(src[((SOFT_SPRITE_SRC_Y-1)-y)*SOFT_SPRITE_SRC_Y_OFS+((SOFT_SPRITE_SRC_X/4-1)-x)]);
							}
							else if(ssm_p->ss[i].ssp.h_flip){
								ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+SOFT_SPRITE_DEST_OFS]=
								BitReverse(src[y*SOFT_SPRITE_SRC_Y_OFS+((SOFT_SPRITE_SRC_X/4-1)-x)]);
							}
							else if(ssm_p->ss[i].ssp.v_flip){
								ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+SOFT_SPRITE_DEST_OFS]=
								src[((SOFT_SPRITE_SRC_Y-1)-y)*SOFT_SPRITE_SRC_Y_OFS+x];
							}
							else if(ssm_p->ss[i].ssp.mosaic){
								if(y%(ssm_p->ss[i].ssp.mosaic*2)){
									ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+SOFT_SPRITE_DEST_OFS]=
									ssm_p->dest_chr[(y-1)*SOFT_SPRITE_DEST_Y_OFS+x+SOFT_SPRITE_DEST_OFS];
								}
								else{
									if(x%(ssm_p->ss[i].ssp.mosaic)){
										ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+SOFT_SPRITE_DEST_OFS]=
											ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+(x-1)+SOFT_SPRITE_DEST_OFS];
									}
									else{
										ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+SOFT_SPRITE_DEST_OFS]=
											((src[y*SOFT_SPRITE_SRC_Y_OFS+x]&0x0f)|(src[y*SOFT_SPRITE_SRC_Y_OFS+x]&0x0f)<<4);
									}
								}
							}
							else{
								ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+SOFT_SPRITE_DEST_OFS]=
									src[y*SOFT_SPRITE_SRC_Y_OFS+x];
							}
						}
						else{
							if((ssm_p->ss[i].ssp.h_flip)&&(ssm_p->ss[i].ssp.v_flip)){
								ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+SOFT_SPRITE_DEST_OFS2]=
								BitReverse(src[((SOFT_SPRITE_SRC_Y-1)-y)*SOFT_SPRITE_SRC_Y_OFS+((SOFT_SPRITE_SRC_X/2-1)-(x-SOFT_SPRITE_SRC_X/4))]);
							}
							else if(ssm_p->ss[i].ssp.h_flip){
								ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+SOFT_SPRITE_DEST_OFS2]=
								BitReverse(src[y*SOFT_SPRITE_SRC_Y_OFS+((SOFT_SPRITE_SRC_X/2-1)-(x-SOFT_SPRITE_SRC_X/4))]);
							}
							else if(ssm_p->ss[i].ssp.v_flip){
								ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+SOFT_SPRITE_DEST_OFS2]=
								src[((SOFT_SPRITE_SRC_Y-1)-y)*SOFT_SPRITE_SRC_Y_OFS+x];
							}
							else if(ssm_p->ss[i].ssp.mosaic){
								if(y%(ssm_p->ss[i].ssp.mosaic*2)){
									ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+SOFT_SPRITE_DEST_OFS2]=
										ssm_p->dest_chr[(y-1)*SOFT_SPRITE_DEST_Y_OFS+x+SOFT_SPRITE_DEST_OFS2];
								}
								else{
									if(x%(ssm_p->ss[i].ssp.mosaic)){
										ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+SOFT_SPRITE_DEST_OFS2]=
										ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+(x-1)+SOFT_SPRITE_DEST_OFS2];
									}
									else{
										ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+SOFT_SPRITE_DEST_OFS2]=
										((src[y*SOFT_SPRITE_SRC_Y_OFS+x]&0x0f)|(src[y*SOFT_SPRITE_SRC_Y_OFS+x]&0x0f)<<4);
									}
								}
							}
							else{
								ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+SOFT_SPRITE_DEST_OFS2]=
								src[y*SOFT_SPRITE_SRC_Y_OFS+x];
							}
						}
					}
				}
			}
			else{
				for(y=0;y<SOFT_SPRITE_SRC_Y;y++){
					for(x=0;x<SOFT_SPRITE_SRC_X/2;x++){
						if((ssm_p->ss[i].ssp.h_flip)&&(ssm_p->ss[i].ssp.v_flip)){
							if(x<SOFT_SPRITE_SRC_X/4){
								ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+i*SOFT_SPRITE_DEST_CHR_OFS]=
								BitReverse(src[((SOFT_SPRITE_SRC_Y-1)-y)*SOFT_SPRITE_SRC_Y_OFS+((SOFT_SPRITE_SRC_X/4-1)-x)]);
							}
							else{
								ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+i*SOFT_SPRITE_DEST_CHR_OFS]=
								BitReverse(src[((SOFT_SPRITE_SRC_Y-1)-y)*SOFT_SPRITE_SRC_Y_OFS+((SOFT_SPRITE_SRC_X/2-1)-(x-SOFT_SPRITE_SRC_X/4))]);
							}
						}
						else if(ssm_p->ss[i].ssp.h_flip){
							if(x<SOFT_SPRITE_SRC_X/4){
								ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+i*SOFT_SPRITE_DEST_CHR_OFS]=
								BitReverse(src[y*SOFT_SPRITE_SRC_Y_OFS+((SOFT_SPRITE_SRC_X/4-1)-x)]);
							}
							else{
								ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+i*SOFT_SPRITE_DEST_CHR_OFS]=
								BitReverse(src[y*SOFT_SPRITE_SRC_Y_OFS+((SOFT_SPRITE_SRC_X/2-1)-(x-SOFT_SPRITE_SRC_X/4))]);
							}
						}
						else if(ssm_p->ss[i].ssp.v_flip){
							ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+i*SOFT_SPRITE_DEST_CHR_OFS]=
							src[((SOFT_SPRITE_SRC_Y-1)-y)*SOFT_SPRITE_SRC_Y_OFS+x];
						}
						else if(ssm_p->ss[i].ssp.mosaic){
							if(y%(ssm_p->ss[i].ssp.mosaic*2)){
								ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+i*SOFT_SPRITE_DEST_CHR_OFS]=
								ssm_p->dest_chr[(y-1)*SOFT_SPRITE_DEST_Y_OFS+x+i*SOFT_SPRITE_DEST_CHR_OFS];
							}
							else{
								if(x%(ssm_p->ss[i].ssp.mosaic)){
									ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+i*SOFT_SPRITE_DEST_CHR_OFS]=
									ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+(x-1)+i*SOFT_SPRITE_DEST_CHR_OFS];
								}
								else{
									ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+i*SOFT_SPRITE_DEST_CHR_OFS]=
									((src[y*SOFT_SPRITE_SRC_Y_OFS+x]&0x0f)|(src[y*SOFT_SPRITE_SRC_Y_OFS+x]&0x0f)<<4);
								}
							}
						}
						else{
							ssm_p->dest_chr[y*SOFT_SPRITE_DEST_Y_OFS+x+i*SOFT_SPRITE_DEST_CHR_OFS]=
							src[y*SOFT_SPRITE_SRC_Y_OFS+x];
						}
					}
				}
			}
			sys_FreeMemoryEz(buf);
		}
	}

	ssm_p->texture_trans_req=req;
}

//============================================================================================
/**
 *	ソフトウエアスプライトのテクスチャパレット領域を生成する
 *
 * @param[in]	ssm_p		ソフトスプライトマネージャーのポインタ
 */
//============================================================================================
static	void	SoftSpriteTexturePaletteMake(SOFT_SPRITE_MANAGER *ssm_p)
{
	NNSG2dPaletteData	*pd_src;
	int		i,x,y;
	u16		*src;
	void	*buf;
	u8		req;

	req=0;

	for(i=0;i<SOFT_SPRITE_MAX;i++){
		if((ssm_p->ss[i].exist)&&(ssm_p->ss[i].pal_req)){
			ssm_p->ss[i].pal_req=0;
			req=1;
			//パレットデータ読み込み
			buf=ArchiveDataLoadMalloc(ssm_p->ss[i].ssa.arc_no,ssm_p->ss[i].ssa.index_pal,ssm_p->heap_id);
			NNS_G2dGetUnpackedPaletteData(buf,&pd_src);
			ssm_p->pd_dest.fmt=pd_src->fmt;
			src=pd_src->pRawData;
			for(x=0;x<0x10;x++){
				ssm_p->dest_col[x+0x10*i]=src[x];
				ssm_p->dest_col_temp[x+0x10*i]=src[x];
			}
			sys_FreeMemoryEz(buf);
			if(ssm_p->ss[i].sss.shadow_req){
				//影パレットデータ読み込み
				buf=ArchiveDataLoadMalloc(ARC_OTHER_POKE,NARC_otherpoke_kage_NCLR,ssm_p->heap_id);
				NNS_G2dGetUnpackedPaletteData(buf,&pd_src);
				src=pd_src->pRawData;
				for(x=0;x<0x10;x++){
					ssm_p->dest_col[x+0x10*(3+ssm_p->ss[i].sss.shadow_req)]=src[x];
					ssm_p->dest_col_temp[x+0x10*(3+ssm_p->ss[i].sss.shadow_req)]=src[x];
				}
				sys_FreeMemoryEz(buf);
			}
		}
		if((ssm_p->ss[i].exist)&&(ssm_p->ss[i].ssp.pal_fade)){
			if(ssm_p->ss[i].ssp.pal_wait==0){
				req=1;
				ssm_p->ss[i].ssp.pal_wait=ssm_p->ss[i].ssp.pal_wait_tmp;
				SoftFade((void *)&ssm_p->dest_col_temp[0x10*i],(void *)&ssm_p->dest_col[0x10*i],16,
						 ssm_p->ss[i].ssp.pal_start_evy,ssm_p->ss[i].ssp.pal_rgb);
				if(ssm_p->ss[i].sss.shadow_req){
					SoftFade((void *)&ssm_p->dest_col_temp[0x10*(3+ssm_p->ss[i].sss.shadow_req)],
							 (void *)&ssm_p->dest_col[0x10*(3+ssm_p->ss[i].sss.shadow_req)],16,
							 ssm_p->ss[i].ssp.pal_start_evy,ssm_p->ss[i].ssp.pal_rgb);
				}
				if(ssm_p->ss[i].ssp.pal_start_evy==ssm_p->ss[i].ssp.pal_end_evy){
					ssm_p->ss[i].ssp.pal_fade=0;
				}
				else if(ssm_p->ss[i].ssp.pal_start_evy>ssm_p->ss[i].ssp.pal_end_evy){
					ssm_p->ss[i].ssp.pal_start_evy--;
				}
				else{
					ssm_p->ss[i].ssp.pal_start_evy++;
				}
			}
			else{
				ssm_p->ss[i].ssp.pal_wait--;
			}
		}
	}
	
	ssm_p->palette_trans_req=req;
}

//============================================================================================
/**
 *	データの上位4bitと下位4bitを反転する
 *
 * @param[in]	data	反転するデータ
 *
 * @retval	反転したデータ
 */
//============================================================================================
static	u8	BitReverse(u8 data)
{
	u8	ret;

	ret=(data&0xf0)>>4;
	ret|=(data&0x0f)<<4;

	return	ret;
}

//============================================================================================
/**
 *	ポケモングラフィックにぶちをつける
 *
 * @param[in]	ss		ぶちをつけるSoftSprite構造体データ
 * @param[in]	buf		キャラクタデータが展開されたワークへのポインタ
 */

//============================================================================================
static	void	SoftSpriteStrikeMake(SOFT_SPRITE *ss,u8 *buf)
{
	//ぶち生成フラグが立っていない時は処理なし
	if(ss->ssa.strike_mons==0){
		return;
	}

	SoftSprite_MakeStrike( buf, ss->ssa.personal_rnd, TRUE );
}

//============================================================================================
/**
 *	ポケモングラフィックにぶちをつける（外部公開版）
 *
 * @param[out]	buf			キャラクタデータが展開されたワークへのポインタ
 * @param[in]	rnd			個性乱数
 * @param[in]	animeFlag	TRUEならアニメ用に２コマ目も処理する
 */

//============================================================================================
void SoftSprite_MakeStrike( u8* buf, u32 rnd, BOOL animeFlag )
{
	const	PATCHEEL_STRIKE_DATA	*psd;
	int	i;
	u8	setx,sety,cnt;
	int	pos;
	u32	tmp_rnd;

	tmp_rnd=rnd;

	//1枚目
	for(i=0;i<4;i++){
		psd=psd_table[i];
		cnt=0;
		while(psd[cnt].posx!=0xff){
			setx=psd[cnt].posx+((rnd&0x0f)-8);
			sety=psd[cnt].posy+(((rnd&0xf0)>>4)-8);
			pos=setx/2+sety*80;
			if(setx&1){
				if(((buf[pos]&0xf0)>=0x10)&&((buf[pos]&0xf0)<=0x30)){
					buf[pos]+=0x50;
				}
			}
			else{
				if(((buf[pos]&0x0f)>=0x01)&&((buf[pos]&0x0f)<=0x03)){
					buf[pos]+=0x05;
				}
			}
			cnt++;
		}
		rnd=rnd>>8;
	}

	rnd=tmp_rnd;

	//2枚目
	if( animeFlag )
	{
		for(i=0;i<4;i++){
			psd=psd_table[i];
			cnt=0;
			while(psd[cnt].posx!=0xff){
				setx=(psd[cnt].posx-14)+((rnd&0x0f)-8)+80;
				sety=psd[cnt].posy+(((rnd&0xf0)>>4)-8);
				pos=setx/2+sety*80;
				if(setx&1){
					if(((buf[pos]&0xf0)>=0x10)&&((buf[pos]&0xf0)<=0x30)){
						buf[pos]+=0x50;
					}
				}
				else{
					if(((buf[pos]&0x0f)>=0x01)&&((buf[pos]&0x0f)<=0x03)){
						buf[pos]+=0x05;
					}
				}
				cnt++;
			}
			rnd=rnd>>8;
		}
	}

}

//============================================================================================
/**
 *	ポケモングラフィックにかけられたマスクの解除キーを算出
 *
 * @param[in/out]	code	解除キー
 */
//============================================================================================
static	u16 CodeRand(u32 *code)
{
    code[0] = code[0] * 1103515245L + 24691;
    return (u16)(code[0] / 65536L) ;
}

//============================================================================================
/**
 *	ポケモングラフィックにかけられたマスクを解除
 *
 * @param[in/out]	src		ポケモングラフィックが展開された領域のポインタ
 */
//============================================================================================
void	SoftSpriteChrMask(u8 *src)
{
	int	i;
	u16	*buf;
	u32	code;

	buf=(u16 *)src;

	code=buf[(20*10*0x20)/2-1];

	for(i=(20*10*0x20)/2-1;i>-1;i--){
		buf[i]^=code;
		CodeRand(&code);
	}
}

