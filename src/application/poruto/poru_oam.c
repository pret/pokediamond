/**
 *	@file	poru_oam.c
 *	@brief	�|���g�A�N�^�[�@OAM�R���g���[��
 *	@author	Miyuki Iwasawa
 *	@date	06.03.28
 */

#include "common.h"
#include "system/clact_tool.h"

#define PORUTO_OAM_H_GLOBAL
#include "poru_oam.h"
#include "poruact.naix"

#define PORUOAM_PAL_MAX	(16)

#define RES_CHRID	(NARC_poruact_poru_act_ncgr)
#define RES_CELID	(NARC_poruact_poru_act_ncer)
#define RES_ANMID	(NARC_poruact_poru_act_nanr)
#define RES_PALID	(NARC_poruact_poru_001_nclr)
#define RES_NOCOMP	(0)
#define RES_NOTRANS	(0)
#define RES_HEADID (0xe000)

enum{
 RESTYPE_CHR,
 RESTYPE_PAL,
 RESTYPE_CEL,
 RESTYPE_ANM,
};

#define PORUOAM_CHR_RES_MAX	(1)
#define PORUOAM_PAL_RES_MAX	(1)
#define PORUOAM_CEL_RES_MAX	(1)
#define PORUOAM_ANM_RES_MAX	(1)


//======================================================
//�v���g�^�C�v
//======================================================
static void PoruOam_ResManagerInit(PORUOAM_MAN* wk);
static void PoruOam_ResManagerRelease(PORUOAM_MAN* wk);

static void poam_LoadResArc(PORUOAM_MAN* wk);
static s16 poam_GetNullWork(PORUOAM_MAN* wk,u8 flavor);

/**
 *	@brief	�|���g�A�N�^�[�@�}�l�[�W��������
 *
 *	@param	heapID	�q�[�vID
 *	@param	actmax	�m�ۂ���Z���A�N�^�[�̈�̌�
 *	@param	palmax	�|���g�p�ɐ�L����OBJ�p���b�g�̖{��
 *	@param	vramType	�`���ʎw��(PORUOAM_DRAW_MAIN/SUB/BOTH)
 *  @param	cgx_transofs	�L�����N�^�]���I�t�Z�b�g�w��
 *							(PORUOAM_CGXOFS_AREA���w�肵���ꍇ�A�󂫗̈挟�����[�h�ɂȂ�)	
 */
PORUOAM_MAN* PoruOam_SysInit(int heapID,u16 actmax,u16 palmax,
		u16 vramType,PORUOAM_CGXOFS cgx_transofs)
{
	PORUOAM_MAN* wk;

	wk = sys_AllocMemory(heapID,sizeof(PORUOAM_MAN));
	MI_CpuClear8(wk,sizeof(PORUOAM_MAN));

	//�p�����[�^�ۑ�
	wk->heapID = heapID;

	if(actmax > PORUOAM_PAL_MAX){
		wk->pal_num = PORUOAM_PAL_MAX;
	}else{
		wk->pal_num = palmax;
	}
	wk->act_max = actmax;
	wk->vramType = vramType;
	wk->cgx_transofs = cgx_transofs;
	
	PoruOam_ResManagerInit(wk);
	return wk;
}

/**
 *	@brief	�|���g�A�N�^�[�@�}�l�[�W�����
 */
void PoruOam_SysRelease(PORUOAM_MAN* wk)
{
	PoruOam_ResManagerRelease(wk);
	MI_CpuClear8(wk,sizeof(PORUOAM_MAN));
	sys_FreeMemoryEz(wk);
}


/**
 *	@brief	���\�[�X�}�l�[�W���쐬
 */
static void PoruOam_ResManagerInit(PORUOAM_MAN* wk)
{
	u32 i, j;
	u8	resnum[] = {PORUOAM_CHR_RES_MAX,1,PORUOAM_CEL_RES_MAX,PORUOAM_ANM_RES_MAX};

	wk->cas  = CLACT_U_SetEasyInit(wk->act_max, &wk->renddata,wk->heapID);

	// ���\�[�X�}�l�[�W���[�쐬&�e�[�u��������
	resnum[RESTYPE_PAL] = wk->pal_num;
	for( i=0; i< PORUOAM_RESMAX; i++ ){
		wk->resMan[i] = CLACT_U_ResManagerInit(resnum[i],i, wk->heapID );
		wk->resObjTbl[i] = CLACT_U_ResManagerResObjTblMake(resnum[i],wk->heapID);
		for( j=0; j<wk->resObjTbl[i]->tbl_num; j++ ){
			wk->resObjTbl[i]->tbl[j] = NULL;
		}
	}

	//���\�[�X���[�h
	poam_LoadResArc(wk);

	//�p���b�g���[�N�m��
	wk->work = sys_AllocMemory(wk->heapID,sizeof(PORUOAM_ACTWORK));
	MI_CpuClear8(wk->work,sizeof(PORUOAM_ACTWORK));
}

/**
 *	@brief	���\�[�X�}�l�[�W�����
 */
static void PoruOam_ResManagerRelease(PORUOAM_MAN* wk)
{
	u32	i;

	//�p���b�g���[�N�j��
	sys_FreeMemoryEz(wk->work);

	CLACT_DestSet( wk->cas );	// �Z�b�g�j��
	CLACT_U_CharManagerDeletes( wk->resObjTbl[RESTYPE_CHR] );	// �L�����f�[�^�j��
	CLACT_U_PlttManagerDeletes( wk->resObjTbl[RESTYPE_PAL] );	// �p���b�g�f�[�^�j��

	for( i=0; i<PORUOAM_RESMAX; i++ ){
		// ���\�[�X�I�u�W�F�e�[�u���j��
		CLACT_U_ResManagerResObjTblDelete( wk->resObjTbl[i] );
		// ���\�[�X�}�l�[�W���j��
		CLACT_U_ResManagerDelete( wk->resMan[i] );
	}
}

/**
 *	@brief	�|���gOAM�@�`�惁�C��
 */
void PoruOam_DrawMain(PORUOAM_MAN* wk)
{
	CLACT_Draw(wk->cas);
}

/**
 *	@brief	�|���gOAM�ǉ�
 *
 *	@param	flavor	�|���g�̎��ID
 *	@param	x		X���W
 *	@param	y		Y���W
 *	@param	z		Z���W
 *	@param	bg_pri	BG�v���C�I���e�B
 *	@param	spri	�\�t�g�E�F�A�v���C�I���e�B
 *	@param	vram_type	PORUOAM_VRAMTYPE�^
 *						PORUOAM_VT_MAIN:���C�����
 *						PORUOAM_VT_SUB:�T�u���
 *
 *	���K��PoruOam_Del�֐��Ŕj�����邱��
 */
PORUTO_OAM* PoruOam_Add(PORUOAM_MAN* wk,PORUTO_FLAVORID flavor,
		u16 x,u16 y,u16 z,u8 bg_pri,u8 spri,PORUOAM_VRAMTYPE vtype)
{
	u8	vram_type;
	s16	idx;
	u32	palid;
	PORUTO_OAM* oam;
	CATS_ACT_PTR cap = NULL;
	CLACT_ADD	 add;
	CLACT_U_RES_OBJ_PTR	obj;

	//���[�N�̋󂫗̈��T��
	idx = poam_GetNullWork(wk,flavor);
	if(idx < 0){
		//�󂫗̈悪�Ȃ�
		GF_ASSERT(0 && "PoruOam_Add->work was full");
		return NULL;
	}

	//OAM���[�N�m��
	oam = sys_AllocMemory(wk->heapID,sizeof(PORUTO_OAM));
	MI_CpuClear8(oam,sizeof(PORUTO_OAM));
	oam->workID = idx;
	
	if(vtype == PORUOAM_VT_MAIN){
		vram_type = NNS_G2D_VRAM_TYPE_2DMAIN;
	}else{
		vram_type = NNS_G2D_VRAM_TYPE_2DSUB;
	}

	obj = wk->resObjTbl[RESTYPE_PAL]->tbl[idx];
	//�p���b�g���\�[�X�ǂݑւ�
	CLACT_U_ResManagerResChgArcPltt(wk->resMan[RESTYPE_PAL],
		wk->resObjTbl[RESTYPE_PAL]->tbl[idx],
		ARC_PORUACT_GRA,RES_PALID+flavor,RES_NOCOMP,wk->heapID);
	CLACT_U_PlttManagerReTrans(wk->resObjTbl[RESTYPE_PAL]->tbl[idx]);

	//���[�N�������m��
	cap = sys_AllocMemory(wk->heapID, sizeof(TCATS_ACT) );

	//�w�b�_�[�������m��
	cap->act_htp = sys_AllocMemory(wk->heapID,sizeof(CLACT_HEADER_TBL));
	cap->act_htp->tbl = sys_AllocMemory(wk->heapID,sizeof(CLACT_HEADER));
	cap->act_hd = cap->act_htp->tbl;

	//�w�b�_�[����
	CLACT_U_MakeHeader(
		cap->act_hd,
		RES_HEADID,RES_HEADID+idx,
		RES_HEADID,RES_HEADID,
		CLACT_U_HEADER_DATA_NONE,CLACT_U_HEADER_DATA_NONE,
		RES_NOTRANS, bg_pri,
		wk->resMan[RESTYPE_CHR],wk->resMan[RESTYPE_PAL],
		wk->resMan[RESTYPE_CEL],wk->resMan[RESTYPE_ANM],
		NULL,NULL);	

	// OAM�o�^
	add.ClActSet	= wk->cas;
	add.ClActHeader = cap->act_hd;

	add.mat.x		= FX32_CONST(x);
	add.mat.y		= FX32_CONST(y);
	add.mat.z		= FX32_CONST(z);
	if(vram_type == NNS_G2D_VRAM_TYPE_2DSUB){
		add.mat.y += SUB_SURFACE_Y;
	}
	
	add.sca.x		= FX32_ONE;			// �g�k��
	add.sca.y		= FX32_ONE;
	add.sca.z		= FX32_ONE;
	
	add.rot			= 0;				// ��]�p
	add.pri			= spri;				// �D��x
	add.DrawArea	= vram_type;		// �`���
	add.heap		= wk->heapID;		// �q�[�vID
	
	cap->act = CLACT_Add(&add);			//�o�^����
	
	if (cap->act != NULL){
		CLACT_AnmChg(cap->act,0);		//�A�j���[�V�����w��
		palid = CLACT_U_PlttManagerGetPlttNo(
			obj,vram_type);
		CLACT_PaletteNoChg(cap->act,palid);		//�p���b�g�w��
	}
	else{
		GF_ASSERT(0 &&"poruto oam add failed");
	}
	oam->act = cap;
	return oam;		
}

/**
 *	@brief	�o�^�ς�OAM�̃|���g�̎�ނ�ύX����
 *	
 *	@param	flavor	�|���g�̎��ID
 */
void PoruOam_ChangeFlavor(PORUOAM_MAN*wk,PORUTO_OAM* oam,PORUTO_FLAVORID flavor)
{
	CLACT_U_RES_OBJ_PTR	obj;

	obj = wk->resObjTbl[RESTYPE_PAL]->tbl[oam->workID];

	//�p���b�g���\�[�X�ǂݑւ�
	CLACT_U_ResManagerResChgArcPltt(wk->resMan[RESTYPE_PAL],
		obj,ARC_PORUACT_GRA,RES_PALID+flavor,RES_NOCOMP,wk->heapID);
	CLACT_U_PlttManagerReTrans(obj);
}

/**
 *	@brief	�|���gOAM�폜
 */
void PoruOam_Del(PORUOAM_MAN* wk,PORUTO_OAM* oam)
{
	//�A�N�^�[�폜
	CATS_ActorPointerDelete_S(oam->act);
	
	//���[�N���
	wk->work[oam->workID].valid = 0;
	wk->work[oam->workID].resNo = 0;
	wk->work[oam->workID].flavor = 0;

	sys_FreeMemoryEz(oam);
}

/**
 *	@brief	���\�[�X�����ݒ�
 */
static void poam_LoadResArc(PORUOAM_MAN* wk)
{
	int i;
	CLACT_U_RES_MANAGER_PTR	res;
	CLACT_U_RES_OBJ_TBL* obj;
	CLACT_U_RES_OBJ_PTR tmp;

	//�L�����N�^���\�[�X�擾
	obj = wk->resObjTbl[RESTYPE_CHR];
	obj->tbl[0] = CLACT_U_ResManagerResAddArcChar(wk->resMan[RESTYPE_CHR],
		ARC_PORUACT_GRA,RES_CHRID,RES_NOCOMP,RES_HEADID,wk->vramType,wk->heapID);
	
	GF_ASSERT((obj->tbl[0]!=NULL)&&"poam char resload failed");

	switch(wk->cgx_transofs){
	case PORUOAM_CGXOFS_AREA:
		CLACT_U_CharManagerSetAreaCont(obj->tbl[0]);
		break;
	case PORUOAM_CGXOFS_ADJUST:
		CLACT_U_CharManagerSetCharModeAdjustAreaCont(obj->tbl[0]);
		break;
	case PORUOAM_CGXOFS_AUTO:
	default:
		CLACT_U_CharManagerSet(obj->tbl[0]);
		break;
	}

	//�Z��&�Z���A�j�����\�[�X�擾
	for(i = 0;i < 2;i++){
		obj = wk->resObjTbl[RESTYPE_CEL+i];
		obj->tbl[0] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[RESTYPE_CEL+i],
			ARC_PORUACT_GRA,RES_CELID+i,RES_NOCOMP,RES_HEADID,RESTYPE_CEL+i,wk->heapID);
	
		GF_ASSERT((obj->tbl[0]!=NULL)&&"poam cell&canm resload failed");
	}

	//�����p���b�g���\�[�X�擾(No.001�őS��������������)
	obj = wk->resObjTbl[RESTYPE_PAL];
	for(i = 0;i < wk->pal_num;i++){
		obj->tbl[i] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[RESTYPE_PAL],
			ARC_PORUACT_GRA,RES_PALID+1,RES_NOCOMP,RES_HEADID+i,wk->vramType,1,wk->heapID);
		
		GF_ASSERT((obj->tbl[i]!=NULL)&&"poam pal resload failed");
//		CLACT_U_PlttManagerSetCleanArea(obj->tbl[i]);
		CLACT_U_PlttManagerSet(obj->tbl[i]);
	}
}

/**
 *	@brief	�󂫃��[�N��T��
 */
static s16 poam_GetNullWork(PORUOAM_MAN* wk,u8 flavor)
{
	u16 i = 0;

	for(i = 0;i < wk->pal_num;i++){
		if(!wk->work[i].valid){
			wk->work[i].resNo = i;
			wk->work[i].flavor = flavor;
			wk->work[i].valid = 1;
			return i;
		}
	}
	return -1;
}
