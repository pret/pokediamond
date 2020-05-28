
//============================================================================================
/**
 * @file	softsprite.c
 * @bfief	�\�t�g�E�G�A�X�v���C�g���g�p�����\���v���O����
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

#include "patch.dat"	//�p�b�`�[���̂Ԃ��f�[�^

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
 *	�\�t�g�E�G�A�X�v���C�g�V�X�e���̏�����
 *
 * @param[in]	heap_id		�̈���m�ۂ���q�[�v�̈��ID
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
	ssm_p->texture_trans_ofs=0;								///<�e�N�X�`���̓]����A�h���X�̃I�t�Z�b�g
	ssm_p->texture_trans_size=SOFT_SPRITE_CHR_SIZE;			///<�e�N�X�`���f�[�^�]���T�C�Y
	ssm_p->palette_trans_ofs=0;								///<�e�N�X�`���p���b�g�̓]����A�h���X�̃I�t�Z�b�g
	ssm_p->palette_trans_size=SOFT_SPRITE_TRANS_COL_SIZE;	///<�e�N�X�`���p���b�g�f�[�^�]���T�C�Y

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

	//�e�f�[�^�ǂݍ���
	buf=ArchiveDataLoadMalloc(ARC_OTHER_POKE,NARC_otherpoke_kage_NCBR,ssm_p->heap_id);
	NNS_G2dGetUnpackedCharacterData(buf,&cd_src);
	ssm_p->cd_dest.pixelFmt=cd_src->pixelFmt;
	ssm_p->cd_dest.mapingType=cd_src->mapingType;
	ssm_p->cd_dest.characterFmt=cd_src->characterFmt;
	src=cd_src->pRawData;
	SoftSpriteChrMask(src);

	//�����F�œh��Ԃ�
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
	//0�F�_�~�[�f�[�^�i���ۂ͕\������Ȃ��j
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
 *	�\�t�g�E�G�A�X�v���C�g���C�����[�`��
 *
 * @param[in]	ssm_p	�\�t�g�E�G�A�X�v���C�g�}�l�[�W���V�X�e�����[�N�̃|�C���^
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
				// �}�g���N�X������
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
					// �}�g���N�X������
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
 *	�\�t�g�E�G�A�X�v���C�g�}�l�[�W���̏I��
 *
 * @param[in]	ssm_p	�\�t�g�E�G�A�X�v���C�g�}�l�[�W���V�X�e�����[�N�̃|�C���^
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
 *	�A�j���[�V�������Z�b�g
 *
 * @param[in]	ss		�A�j���[�V�������Z�b�g����\�t�g�E�G�A�X�v���C�g�Ǘ����[�N�|�C���^
 * @param[in]	anm_no	�Z�b�g����A�j���[�V�����i���o�[
 */
//============================================================================================
void	SoftSpriteAnimeSet(SOFT_SPRITE *ss,int anm_no)
{
	int	i;

	//����́A�ėp�����Ȃ����āAanm_no���t���O�Ƃ��ď����i0:�A�j�����Ȃ��@1:�A�j������j
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
 *	�A�j���[�V�����f�[�^���Z�b�g
 *
 * @param[in]	ss		�A�j���[�V�������Z�b�g����\�t�g�E�G�A�X�v���C�g�Ǘ����[�N�|�C���^
 * @param[in]	ssanm	�Z�b�g����A�j���[�V�����f�[�^
 */
//============================================================================================
void	SoftSpriteAnimeDataSet(SOFT_SPRITE *ss,SOFT_SPRITE_ANIME *ssanm)
{
	MI_CpuCopy8(ssanm,&ss->ssanm,sizeof(SOFT_SPRITE_ANIME)*10);
}

//============================================================================================
/**
 *	�A�j���[�V�����̏I�����`�F�b�N
 *
 * @param[in]	ss		�A�j���[�V�����̏I�����`�F�b�N����\�t�g�E�G�A�X�v���C�g�Ǘ����[�N�|�C���^
 *
 * @retval	FALSE:�I��	TRUE:�p����
 */
//============================================================================================
BOOL	SoftSpriteAnimeEndCheck(SOFT_SPRITE *ss)
{
	return (ss->anm_no!=0);
}

//============================================================================================
/**
 *	�\�t�g�E�G�A�X�v���C�g��o�^����
 *
 * @param[in]	ssm_p	�\�t�g�E�G�A�X�v���C�g�}�l�[�W���V�X�e�����[�N�̃|�C���^
 * @param[in]	ssa		�\�t�g�E�G�A�X�v���C�g�w�b�_�[�f�[�^�̃|�C���^
 * @param[in]	pos_x	�\�t�g�E�G�A�X�v���C�g�����ʒu�iX���W�j
 * @param[in]	pos_y	�\�t�g�E�G�A�X�v���C�g�����ʒu�iY���W�j
 * @param[in]	pos_z	�\�t�g�E�G�A�X�v���C�g�����ʒu�iZ���W�j
 * @param[in]	poly_id	�`�悷��|���S��ID
 * @param[in]	anm_tbl	�A�j���[�V�����e�[�u���̃|�C���^
 * @param[in]	move	����֐��̃|�C���^�iSoftSpriteMain����Ă΂�܂��j
 *
 * @retval		SOFT_SPRITE *	�\�t�g�E�G�A�X�v���C�g�Ǘ����[�N�̃|�C���^
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
 *	�\�t�g�E�G�A�X�v���C�g��o�^����i�Z�b�g����ꏊ�̎w�������j
 *
 * @param[in]	ssm_p	�\�t�g�E�G�A�X�v���C�g�}�l�[�W���V�X�e�����[�N�̃|�C���^
 * @param[in]	ssa		�\�t�g�E�G�A�X�v���C�g�w�b�_�[�f�[�^�̃|�C���^
 * @param[in]	pos_x	�\�t�g�E�G�A�X�v���C�g�����ʒu�iX���W�j
 * @param[in]	pos_y	�\�t�g�E�G�A�X�v���C�g�����ʒu�iY���W�j
 * @param[in]	pos_z	�\�t�g�E�G�A�X�v���C�g�����ʒu�iZ���W�j
 * @param[in]	poly_id	�`�悷��|���S��ID
 * @param[in]	ss_no	�o�^����SS�\���̔z��̓Y����
 * @param[in]	anm_tbl	�A�j���[�V�����e�[�u���̃|�C���^
 * @param[in]	move	����֐��̃|�C���^�iSoftSpriteMain����Ă΂�܂��j
 *
 * @retval		SOFT_SPRITE *	�\�t�g�E�G�A�X�v���C�g�Ǘ����[�N�̃|�C���^
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
 *	�o�^����Ă���\�t�g�E�G�A�X�v���C�g���폜
 *
 * @param[in]	ss		�폜����Ώۂ̃\�t�g�X�v���C�g�\���̃|�C���^
 */
//============================================================================================
void	SoftSpriteDel(SOFT_SPRITE *ss)
{
	ss->exist=0;
}

//============================================================================================
/**
 *	�o�^����Ă���\�t�g�E�G�A�X�v���C�g�����ׂč폜
 *
 * @param[in]	ssm_p	�\�t�g�X�v���C�g�}�l�[�W���[�\���̃|�C���^
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
 *	�\�t�g�X�v���C�g�̃p�����[�^���Z�b�g����
 *
 * @param[in]	ss		�Z�b�g����Ώۂ̃\�t�g�X�v���C�g�\���̃|�C���^
 * @param[in]	para	�Z�b�g����p�����[�^�isoftsprite.h�ɒ�`�j
 * @param[in]	data	�Z�b�g����l
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
	case SS_PARA_POS_OX:			// X���W�I�t�Z�b�g
		ss->ssp.pos_ox=data;
		break;
	case SS_PARA_POS_OY:			// Y���W�I�t�Z�b�g
		ss->ssp.pos_oy=data;
		break;
	case SS_PARA_POS_OZ:			// Z���W�I�t�Z�b�g
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
	case SS_PARA_DIFF_R:		// DiffR�l
		ss->ssp.diff_r=data;
		break;
	case SS_PARA_DIFF_G:		// DiffG�l
		ss->ssp.diff_g=data;
		break;
	case SS_PARA_DIFF_B:		// DiffB�l
		ss->ssp.diff_b=data;
		break;
	case SS_PARA_AMB_R:			// AmbR�l
		ss->ssp.amb_r=data;
		break;
	case SS_PARA_AMB_G:			// AmbG�l
		ss->ssp.amb_g=data;
		break;
	case SS_PARA_AMB_B:			// AmbB�l
		ss->ssp.amb_b=data;
		break;
	case SS_PARA_PAL_FADE:		// �p���b�g�t�F�[�h�t���O
		ss->ssp.pal_fade=data;
		ss->pal_req=1;			//�p���b�g�t�F�[�h�W���𑀍삵���ꍇ�́A�p���b�g�������N�G�X�g���o��
		break;
	case SS_PARA_PAL_RGB:		// �p���b�g�t�F�[�h RGB�l
		ss->ssp.pal_rgb=data;
		ss->pal_req=1;			//�p���b�g�t�F�[�h�W���𑀍삵���ꍇ�́A�p���b�g�������N�G�X�g���o��
		break;
	case SS_PARA_PAL_START_EVY:	// �p���b�g�t�F�[�h START_EVY�l
		ss->ssp.pal_start_evy=data;
		ss->pal_req=1;			//�p���b�g�t�F�[�h�W���𑀍삵���ꍇ�́A�p���b�g�������N�G�X�g���o��
		break;
	case SS_PARA_PAL_END_EVY:	// �p���b�g�t�F�[�h END_EVY�l
		ss->ssp.pal_end_evy=data;
		ss->pal_req=1;			//�p���b�g�t�F�[�h�W���𑀍삵���ꍇ�́A�p���b�g�������N�G�X�g���o��
		break;
	case SS_PARA_PAL_WAIT:		// �p���b�g�t�F�[�h wait�l
		ss->ssp.pal_wait=data;
		break;
	case SS_PARA_H_FLIP:
		ss->ssp.h_flip=data;
		ss->make_req=1;				//�t���b�v�t���O�𑀍삵���ꍇ�́A�e�N�X�`���������N�G�X�g���o��
		break;
	case SS_PARA_V_FLIP:
		ss->ssp.v_flip=data;
		ss->make_req=1;				//�t���b�v�t���O�𑀍삵���ꍇ�́A�e�N�X�`���������N�G�X�g���o��
		break;
	case SS_PARA_DRAW_STOP:
		ss->ssp.draw_stop=data;
		break;
	case SS_PARA_ANM_PAT:
		ss->anm_pat=data;
		break;
	case SS_PARA_MOSAIC:
		ss->ssp.mosaic=data;
		ss->make_req=1;				//���U�C�N�l�𑀍삵���ꍇ�́A�e�N�X�`���������N�G�X�g���o��
		break;
	case SS_PARA_SHADOW_HEIGHT:
		ss->sss.shadow_height=data;
		break;
	case SS_PARA_SHADOW_REQ:
		ss->sss.shadow_req=data;
		ss->pal_req=1;				//�e�L���l�𑀍삵���ꍇ�́A�p���b�g�������N�G�X�g���o��
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
 *	�\�t�g�X�v���C�g�̃p�����[�^���擾����
 *
 * @param[in]	ss		�擾����Ώۂ̃\�t�g�X�v���C�g�\���̃|�C���^
 * @param[in]	para	�擾����p�����[�^�isoftsprite.h�ɒ�`�j
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
	case SS_PARA_DIFF_R:		// DiffR�l
		return ss->ssp.diff_r;
	case SS_PARA_DIFF_G:		// DiffG�l
		return ss->ssp.diff_g;
	case SS_PARA_DIFF_B:		// DiffB�l
		return ss->ssp.diff_b;
	case SS_PARA_AMB_R:			// AmbR�l
		return ss->ssp.amb_r;
	case SS_PARA_AMB_G:			// AmbG�l
		return ss->ssp.amb_g;
	case SS_PARA_AMB_B:			// AmbB�l
		return ss->ssp.amb_b;
	case SS_PARA_PAL_FADE:		// �p���b�g�t�F�[�h�t���O
		return ss->ssp.pal_fade;
	case SS_PARA_PAL_RGB:		// �p���b�g�t�F�[�h RGB�l
		return ss->ssp.pal_rgb;
	case SS_PARA_PAL_START_EVY:	// �p���b�g�t�F�[�h START_EVY�l
		return ss->ssp.pal_start_evy;
	case SS_PARA_PAL_END_EVY:	// �p���b�g�t�F�[�h END_EVY�l
		return ss->ssp.pal_end_evy;
	case SS_PARA_PAL_WAIT:		// �p���b�g�t�F�[�h wait�l
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
	GF_ASSERT((0)&&"�����ɂ���̂͂�������");
	return 0;
}

//============================================================================================
/**
 *	�\�t�g�X�v���C�g�̃p�����[�^�v�Z������
 *
 * @param[in]	ss		�v�Z������Ώۂ̃\�t�g�X�v���C�g�\���̃|�C���^
 * @param[in]	para	�v�Z������p�����[�^�isoftsprite.h�ɒ�`�j
 * @param[in]	data	�����Z����l
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
	case SS_PARA_POS_OX:			// X���W�I�t�Z�b�g
		ss->ssp.pos_ox+=data;
		break;
	case SS_PARA_POS_OY:			// Y���W�I�t�Z�b�g
		ss->ssp.pos_oy+=data;
		break;
	case SS_PARA_POS_OZ:			// Z���W�I�t�Z�b�g
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
	case SS_PARA_DIFF_R:		// DiffR�l
		ss->ssp.diff_r+=data;
		break;
	case SS_PARA_DIFF_G:		// DiffG�l
		ss->ssp.diff_g+=data;
		break;
	case SS_PARA_DIFF_B:		// DiffB�l
		ss->ssp.diff_b+=data;
		break;
	case SS_PARA_AMB_R:			// AmbR�l
		ss->ssp.amb_r+=data;
		break;
	case SS_PARA_AMB_G:			// AmbG�l
		ss->ssp.amb_g+=data;
		break;
	case SS_PARA_AMB_B:			// AmbB�l
		ss->ssp.amb_b+=data;
		break;
	case SS_PARA_PAL_FADE:		// �p���b�g�t�F�[�h�t���O
		ss->ssp.pal_fade+=data;
		ss->pal_req=1;			//�p���b�g�t�F�[�h�W���𑀍삵���ꍇ�́A�p���b�g�������N�G�X�g���o��
		break;
	case SS_PARA_PAL_RGB:		// �p���b�g�t�F�[�h RGB�l
		ss->ssp.pal_rgb+=data;
		ss->pal_req=1;			//�p���b�g�t�F�[�h�W���𑀍삵���ꍇ�́A�p���b�g�������N�G�X�g���o��
		break;
	case SS_PARA_PAL_START_EVY:	// �p���b�g�t�F�[�h START_EVY�l
		ss->ssp.pal_start_evy+=data;
		ss->pal_req=1;			//�p���b�g�t�F�[�h�W���𑀍삵���ꍇ�́A�p���b�g�������N�G�X�g���o��
		break;
	case SS_PARA_PAL_END_EVY:	// �p���b�g�t�F�[�h END_EVY�l
		ss->ssp.pal_end_evy+=data;
		ss->pal_req=1;			//�p���b�g�t�F�[�h�W���𑀍삵���ꍇ�́A�p���b�g�������N�G�X�g���o��
		break;
	case SS_PARA_PAL_WAIT:		// �p���b�g�t�F�[�h wait�l
		ss->ssp.pal_wait+=data;
		break;
	case SS_PARA_H_FLIP:
		ss->ssp.h_flip+=data;
		ss->make_req=1;				//�t���b�v�t���O�𑀍삵���ꍇ�́A�e�N�X�`���������N�G�X�g���o��
		break;
	case SS_PARA_V_FLIP:
		ss->ssp.v_flip+=data;
		ss->make_req=1;				//�t���b�v�t���O�𑀍삵���ꍇ�́A�e�N�X�`���������N�G�X�g���o��
		break;
	case SS_PARA_DRAW_STOP:
		ss->ssp.draw_stop+=data;
		break;
	case SS_PARA_ANM_PAT:
		ss->anm_pat+=data;
		break;
	case SS_PARA_MOSAIC:
		ss->ssp.mosaic+=data;
		ss->make_req=1;				//���U�C�N�l�𑀍삵���ꍇ�́A�e�N�X�`���������N�G�X�g���o��
		break;
	case SS_PARA_SHADOW_HEIGHT:
		ss->sss.shadow_height+=data;
		break;
	case SS_PARA_SHADOW_REQ:
		ss->sss.shadow_req+=data;
		ss->pal_req=1;				//�e�L���l�𑀍삵���ꍇ�́A�p���b�g�������N�G�X�g���o��
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
 *	�\�t�g�X�v���C�gVISIBLE���[�h�p�����[�^���Z�b�g����
 *
 * @param[in]	ss		�Z�b�g����Ώۂ̃\�t�g�X�v���C�g�\���̃|�C���^
 * @param[in]	ofs_x	�Z�b�g����p�����[�^�i�e�N�X�`�����͈͎w�荶��X���W�j
 * @param[in]	ofs_y	�Z�b�g����p�����[�^�i�e�N�X�`�����͈͎w�荶��Y���W�j
 * @param[in]	size_x	�Z�b�g����p�����[�^�i�e�N�X�`�����͈�X�T�C�Y�j
 * @param[in]	size_y	�Z�b�g����p�����[�^�i�e�N�X�`�����͈�Y�T�C�Y�j
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
 *	�\�t�g�X�v���C�g�p���b�g�t�F�[�h���[�h�p�����[�^���Z�b�g����
 *
 * @param[in]	ss			�Z�b�g����Ώۂ̃\�t�g�X�v���C�g�\���̃|�C���^
 * @param[in]	start_evy	�Z�b�g����p�����[�^�i�t�F�[�h������F�ɑ΂���J�n����16�i�K�j
 * @param[in]	end_evy		�Z�b�g����p�����[�^�i�t�F�[�h������F�ɑ΂���I������16�i�K�j
 * @param[in]	wait		�Z�b�g����p�����[�^�i�E�F�C�g�j
 * @param[in]	rgb			�Z�b�g����p�����[�^�i�t�F�[�h������F�j
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
 *	�\�t�g�X�v���C�g�p���b�g�t�F�[�h���[�h�p�����[�^���Z�b�g����i�o�^����Ă���X�v���C�g���ׂāj
 *
 * @param[in]	ssm_p		�\�t�g�X�v���C�g�}�l�[�W���[�\���̂ւ̃|�C���^
 * @param[in]	start_evy	�Z�b�g����p�����[�^�i�t�F�[�h������F�ɑ΂���J�n����16�i�K�j
 * @param[in]	end_evy		�Z�b�g����p�����[�^�i�t�F�[�h������F�ɑ΂���I������16�i�K�j
 * @param[in]	wait		�Z�b�g����p�����[�^�i�E�F�C�g�j
 * @param[in]	rgb			�Z�b�g����p�����[�^�i�t�F�[�h������F�j
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
 *	�\�t�g�X�v���C�g�p���b�g�t�F�[�h���[�h���I�t�ɂ���
 *
 * @param[in]	ss		�Z�b�g����Ώۂ̃\�t�g�X�v���C�g�\���̃|�C���^
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
 *	�\�t�g�X�v���C�g�p���b�g�t�F�[�h�����`�F�b�N�ɂ���
 *
 * @param[in]	ss		�`�F�b�N�Ώۂ̃\�t�g�X�v���C�g�\���̃|�C���^
 *
 * @retval	TRUE:�t�F�[�h���@FALSE�F�t�F�[�h�I��
 */
//============================================================================================
BOOL	SoftSpritePalFadeExist(SOFT_SPRITE *ss)
{
	return (ss->ssp.pal_fade==1);
}

//============================================================================================
/**
 *	�\�t�g�X�v���C�g�̊g�k����OY���v�Z����
 *	�i�|�P�����o�ꎞ�ɑ��ʒu�����킹�Ċg��A�k��������j
 *
 * @param[in]	ss		�v�Z�Ώۂ̃\�t�g�X�v���C�g�\���̃|�C���^
 */
//============================================================================================
void	SoftSpriteOYCalc(SOFT_SPRITE *ss,int height)
{
	ss->ssp.pos_oy=((SOFT_SPRITE_SIZE_Y/2)-height)-((((SOFT_SPRITE_SIZE_Y/2)-height)*ss->ssp.aff_y)>>8);
}

//============================================================================================
//		�O������J�֐��Q
//============================================================================================

//------------------------------------------------------------------
/**
 * �A�j���i�s����
 *
 * @param   anm_flag[io]	�A�j�����t���O���[�N
 * @param   pat[out]		�A�j���p�^�[�����󂯎��ϐ��|�C���^
 * @param   seq	[io]		�V�[�P���X�ۑ����[�N
 * @param   wait[io]		�E�F�C�g�ۑ����[�N
 * @param   loop_cnt[io]	���[�v�J�E���^�ۑ����[�N�iu8 * SS_ANM_SEQ_MAX�j
 * @param   anm_tbl[in]		�A�j���e�[�u���|�C���^
 */
//------------------------------------------------------------------
static inline void SoftSpriteAnimeCore( u8* anm_flag, u8* pat, u8* seq, u8* wait, u8* loop_cnt, const SOFT_SPRITE_ANIME* anm_tbl )
{
	if(*anm_flag)
	{
		if( (*wait) == 0 )
		{
			(*seq)++;
			//���[�v����
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
 * �A�j���i�s�������O������s�����߂̃��[�N�̈�Z�b�g�A�b�v
 *
 * @param   wk			�i�s�������[�N�|�C���^
 * @param   anim_tbl	�A�j���e�[�u��
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
 * �A�j���i�s�����i�O�����J�j
 *
 * @param   wk		�i�s�������[�N�|�C���^
 *
 * @retval  int		0�`1  �A�j���p�^�[��
 *					-1    �A�j���I��
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
 *	�\�t�g�E�G�A�X�v���C�g�̃e�N�X�`���̈�𕜋�����
 *
 * @param[in]	ssm_p		�\�t�g�X�v���C�g�}�l�[�W���[�̃|�C���^
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
 *	�\�t�g�E�G�A�X�v���C�g�̃e�N�X�`���̈�𕜋�����
 *
 * @param[in]	ss		�\�t�g�X�v���C�g�̃|�C���^
 */
//============================================================================================
void	SoftSpriteRecoverSS(SOFT_SPRITE *ss)
{
	ss->make_req=1;
	ss->pal_req=1;
}

//============================================================================================
/**
 *	�\�t�g�E�G�A�X�v���C�g��SSA���X�^�b�N�̈�ɑޔ�����
 *
 * @param[in]	ss		�ޔ�Ώۂ̃\�t�g�X�v���C�g�\���̃|�C���^
 */
//============================================================================================
void	SoftSpriteSSAPush(SOFT_SPRITE *ss)
{
	ss->ssa_push=ss->ssa;
	ss->sss_push=ss->sss;
}

//============================================================================================
/**
 *	�X�^�b�N�ɑޔ������\�t�g�E�G�A�X�v���C�g��SSA�𕜋�����
 *
 * @param[in]	ss		�����Ώۂ̃\�t�g�X�v���C�g�\���̃|�C���^
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
 *	�\�t�g�E�G�A�X�v���C�g�̃e�N�X�`���]���̊J�n�ʒu�ƃT�C�Y��ύX����
 *
 * @param[in]	ssm_p		�\�t�g�X�v���C�g�}�l�[�W���[�̃|�C���^
 * @param[in]	ofs			�]���J�n�ʒu�̃I�t�Z�b�g
 * @param[in]	size		�]���T�C�Y
 */
//============================================================================================
void	SoftSpriteTextureTransParamSet(SOFT_SPRITE_MANAGER *ssm_p,u32 ofs,u32 size)
{
	ssm_p->texture_trans_ofs=ofs;
	ssm_p->texture_trans_size=size;
}

//============================================================================================
/**
 *	�\�t�g�E�G�A�X�v���C�g�̃e�N�X�`���p���b�g�]���̊J�n�ʒu�ƃT�C�Y��ύX����
 *
 * @param[in]	ssm_p		�\�t�g�X�v���C�g�}�l�[�W���[�̃|�C���^
 * @param[in]	ofs			�]���J�n�ʒu�̃I�t�Z�b�g
 * @param[in]	size		�]���T�C�Y
 */
//============================================================================================
void	SoftSpritePaletteTransParamSet(SOFT_SPRITE_MANAGER *ssm_p,u32 ofs,u32 size)
{
	ssm_p->palette_trans_ofs=ofs;
	ssm_p->palette_trans_size=size;
}

//============================================================================================
/**
 *	�\�t�g�E�G�A�X�v���C�g�̃A�[�J�C�o���̃|�C���^���擾
 *
 * @param[in]	ssm_p		�\�t�g�X�v���C�g�}�l�[�W���[�̃|�C���^
 * @param[in]	num			���Ԗڂ̃X�v���C�g�̃|�C���^���擾���邩�w��
 */
//============================================================================================
SOFT_SPRITE_ARC	*SoftSpriteArcPointerGet(SOFT_SPRITE_MANAGER *ssm_p,int num)
{
	return &ssm_p->ss[num].ssa;
}

//============================================================================================
/**
 *	�\�t�g�E�G�A�X�v���C�g�̃A�[�J�C�o���̃|�C���^���擾
 *
 * @param[in]	ss		�\�t�g�X�v���C�g�̃|�C���^
 */
//============================================================================================
SOFT_SPRITE_ARC	*SoftSpriteArcPointerGetSS(SOFT_SPRITE *ss)
{
	return &ss->ssa;
}

//============================================================================================
/**
 *	�\�t�g�E�G�A�X�v���C�g�̃A�[�J�C�o������
 *
 * @param[in]	ssm_p		�\�t�g�X�v���C�g�}�l�[�W���[�̃|�C���^
 * @param[in]	num			���Ԗڂ̃X�v���C�g�̃|�C���^�ɑ�����邩�w��
 * @param[in]	ssa			�������A�[�J�C�o���
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
 *	�\�t�g�E�G�A�X�v���C�g�̃A�[�J�C�o������
 *
 * @param[in]	ss		�\�t�g�X�v���C�g�̃|�C���^
 * @param[in]	ssa			�������A�[�J�C�o���
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
 *	���z�e�N�X�`���̈���e�N�X�`���̈�ɓ]��
 *
 * @param[in]	ssm_p		�\�t�g�X�v���C�g�}�l�[�W���[�̃|�C���^
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
 *	�\�t�g�E�G�A�X�v���C�g��DrawMode���Z�b�g����
 *
 * @param[in]	ssm_p		�\�t�g�X�v���C�g�}�l�[�W���[�̃|�C���^
 * @param[in]	mode		�Z�b�g���郂�[�h
 */
//============================================================================================
void	SoftSpriteDrawModeSet(SOFT_SPRITE_MANAGER *ssm_p,int mode)
{
	ssm_p->mode=mode;
}

//============================================================================================
/**
 *	�\�t�g�E�G�A�X�v���C�g�g�p�`�F�b�N������
 *
 * @param[in]	ss			�\�t�g�X�v���C�g�\���̂̃|�C���^
 *
 * @retval	FALSE:���g�p�@TRUE:�g�p��
 */
//============================================================================================
BOOL	SoftSpriteExistCheck(SOFT_SPRITE *ss)
{
	GF_ASSERT(ss!=NULL);
	return (ss->exist!=0);
}

//============================================================================================
/**
 *	�\�t�g�E�G�A�X�v���C�g�V�X�e���t���O���Z�b�g
 *
 * @param[in]	ssm_p	�\�t�g�X�v���C�g�}�l�[�W���[�\���̂̃|�C���^
 * @param[in]	flag	�Z�b�g����t���O
 */
//============================================================================================
void	SoftSpriteSSSystemFlagSet(SOFT_SPRITE_MANAGER *ssm_p,u32 flag)
{
	ssm_p->ss_system_flag|=flag;
}

//============================================================================================
/**
 *	�\�t�g�E�G�A�X�v���C�g�V�X�e���t���O�����Z�b�g
 *
 * @param[in]	ssm_p	�\�t�g�X�v���C�g�}�l�[�W���[�\���̂̃|�C���^
 * @param[in]	flag	���Z�b�g����t���O
 */
//============================================================================================
void	SoftSpriteSSSystemFlagReset(SOFT_SPRITE_MANAGER *ssm_p,u32 flag)
{
	ssm_p->ss_system_flag&=(flag^0xffffffff);
}

//============================================================================================
/**
 *	�\�t�g�E�G�A�X�v���C�g�̃e�N�X�`���̈�𐶐�����
 *
 * @param[in]	ssm_p		�\�t�g�X�v���C�g�}�l�[�W���[�̃|�C���^
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
			//�L�����f�[�^�ǂݍ���
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
 *	�\�t�g�E�G�A�X�v���C�g�̃e�N�X�`���p���b�g�̈�𐶐�����
 *
 * @param[in]	ssm_p		�\�t�g�X�v���C�g�}�l�[�W���[�̃|�C���^
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
			//�p���b�g�f�[�^�ǂݍ���
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
				//�e�p���b�g�f�[�^�ǂݍ���
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
 *	�f�[�^�̏��4bit�Ɖ���4bit�𔽓]����
 *
 * @param[in]	data	���]����f�[�^
 *
 * @retval	���]�����f�[�^
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
 *	�|�P�����O���t�B�b�N�ɂԂ�������
 *
 * @param[in]	ss		�Ԃ�������SoftSprite�\���̃f�[�^
 * @param[in]	buf		�L�����N�^�f�[�^���W�J���ꂽ���[�N�ւ̃|�C���^
 */

//============================================================================================
static	void	SoftSpriteStrikeMake(SOFT_SPRITE *ss,u8 *buf)
{
	//�Ԃ������t���O�������Ă��Ȃ����͏����Ȃ�
	if(ss->ssa.strike_mons==0){
		return;
	}

	SoftSprite_MakeStrike( buf, ss->ssa.personal_rnd, TRUE );
}

//============================================================================================
/**
 *	�|�P�����O���t�B�b�N�ɂԂ�������i�O�����J�Łj
 *
 * @param[out]	buf			�L�����N�^�f�[�^���W�J���ꂽ���[�N�ւ̃|�C���^
 * @param[in]	rnd			������
 * @param[in]	animeFlag	TRUE�Ȃ�A�j���p�ɂQ�R�}�ڂ���������
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

	//1����
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

	//2����
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
 *	�|�P�����O���t�B�b�N�ɂ�����ꂽ�}�X�N�̉����L�[���Z�o
 *
 * @param[in/out]	code	�����L�[
 */
//============================================================================================
static	u16 CodeRand(u32 *code)
{
    code[0] = code[0] * 1103515245L + 24691;
    return (u16)(code[0] / 65536L) ;
}

//============================================================================================
/**
 *	�|�P�����O���t�B�b�N�ɂ�����ꂽ�}�X�N������
 *
 * @param[in/out]	src		�|�P�����O���t�B�b�N���W�J���ꂽ�̈�̃|�C���^
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

