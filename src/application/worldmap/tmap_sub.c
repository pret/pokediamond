/**
 *	@file	tmap_sub.c
 *	@brief	�^�E���}�b�v�@�T�u���W���[���Q
 *	@author	Miyuki Iwasawa
 *	@date	06.04.01
 */

#include "common.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/render_oam.h"
#include "system/procsys.h"
#include "application/townmap.h"
#include "tmap_act.dat"
#include "tmap_def.h"
#include "tmap_sub.h"
#include "town.dat"

//========================================================
//�^�E��View�֘A
//========================================================
/**
 *	@brief	�^�E��View���\�[�X�쐬
 *
 *	@param	actSys	�������ς݃Z���A�N�^�[�V�X�e��
 *	@param	actRes	�������ς݃Z���A�N�^�[���\�[�X
 *
 *	@param	dat_num	�f�[�^��
 *	@param	heapID	�q�[�vID
 */
TMAP_VIEW_DAT* TownViewDataCreate(CATS_SYS_PTR actSys,CATS_RES_PTR actRes,
		u8 *arrive,short dat_num,int heapID)
{
	TMAP_VIEW_DAT* wp;
	TMAP_VIEW_OBJ *pd;
	const TOWN_VIEW*	pView;
	short i;

	static const TCATS_OBJECT_ADD_PARAM	ActAddParam =
	{
		TMAP_ACTID_TVIEW,	//ID
		0, 0, 0,	//x,y,z
		0, TMAP_SPRI_TOWN, TMAP_APAL_NTOWN, NNS_G2D_VRAM_TYPE_2DMAIN,	//anmNO,pri,pal,d_area
		0, 0, 0, 0	//prm1,prm2,prm3,prm4
	};
	
	wp = sys_AllocMemory(heapID,sizeof(TMAP_VIEW_DAT));
	memset(wp,0,sizeof(TMAP_VIEW_DAT));

	wp->dat_num = dat_num;

	wp->pDat = sys_AllocMemory(heapID,sizeof(TMAP_VIEW_OBJ)*wp->dat_num);
	memset(wp->pDat,0,sizeof(TMAP_VIEW_OBJ)*wp->dat_num);

	//�^�E���r���[�f�[�^�擾
	pView = TownViewDat;
	for(i = 0;i < wp->dat_num;i++){
		pd = &wp->pDat[i];

		//�ǂݍ��݃p�����[�^
		pd->prm.zoneID = pView[i].zoneID;
		pd->prm.ptn = pView[i].ptn;
		pd->prm.typ = pView[i].typ;
		pd->prm.r = pView[i].r;
		pd->prm.x = pView[i].x;
		pd->prm.z = pView[i].z;
	
		//���B�t���O�`�F�b�N
		pd->flag = arrive[i];
	
		//�Z���ǉ�
		pd->pAct = CATS_ObjectAdd(actSys,actRes,&ActAddParam);
		CLACT_SetDrawFlag(pd->pAct, 1);

		//Town or City or park
		if(pd->flag){
			CLACT_PaletteNoChg( pd->pAct,TMAP_APAL_NTOWN+pd->prm.typ+pd->flag);
		}else{
			//�p�[�N/�`�����s�I�����[�h�͓������ĂȂ��ꍇ�B��		
			if(	pd->prm.r == TMAP_VIEW_FLAG_PARK ||
				pd->prm.r == TMAP_VIEW_FLAG_LOAD){
				CLACT_SetDrawFlag(pd->pAct, 0);
			}
		}
		
		//�p�^�[���ݒ�&�ʒu�ݒ�
		CLACT_AnmFrameChg(pd->pAct,FX32_CONST(pd->prm.ptn));
		CATS_ObjectPosSet(pd->pAct,
				pd->prm.x+TMAP_MDOT_OFSX,
				pd->prm.z+TMAP_MDOT_OFSZ);

	}
	return wp;
}

/**
 *	@brief	�^�E��View���\�[�X���
 */
void TownViewDataRelease(TMAP_VIEW_DAT* wp)
{
	TMAP_VIEW_OBJ *pd;
	short i;

	//�Z���j��
	for(i = 0;i < wp->dat_num;i++){
		pd = &wp->pDat[i];
		CLACT_SetRotationAffine(pd->pAct,0,CLACT_AFFINE_NONE);
		CLACT_Delete(pd->pAct);
	}
	sys_FreeMemoryEz(wp->pDat);
	sys_FreeMemoryEz(wp);
}

/**
 *	�^�E��View �f�[�^����������ZoneID�������̂�T��
 */
TMAP_VIEW_OBJ* TownViewDataSearchPos(TMAP_VIEW_DAT* wp,int zoneID,int x,int z)
{
	TMAP_VIEW_OBJ *pd;
	short i,flag;
	
	for(i = 0;i < wp->dat_num;i++){
		pd = &(wp->pDat[i]);
		if(pd->prm.zoneID != zoneID){
			continue;
		}
		switch(pd->prm.r){
		case TMAP_VIEW_FLAG_NRM:
			return pd;	//���W�`�F�b�N�͗v��Ȃ�
		case TMAP_VIEW_FLAG_PARK:	//�p�[�N
			if(TMAP_VIEW_PARK_X == x && TMAP_VIEW_PARK_Z == z){
				return pd;
			}
			break;
		case TMAP_VIEW_FLAG_LOAD:	//�`�����s�I�����[�h
			if(TMAP_VIEW_LOAD_X == x && TMAP_VIEW_LOAD_Z == z){
				return pd;
			}
			break;
		case TMAP_VIEW_FLAG_LEAG:	//���[�O(C10)
			if(TMAP_VIEW_LEAG_X == x && TMAP_VIEW_LEAG_Z == z){
				return pd;
			}
			break;
		}
	}
	return NULL;
}
/**
 *	@brief	�^�E��View
 */
int TownViewDataSelectPos(TMAP_VIEW_DAT* wp,int zoneID,int x,int z)
{
	TMAP_VIEW_OBJ *pd;
	short i,flag;
	
	flag = 0;
	if(wp == NULL){
		return 0;
	}
	pd = TownViewDataSearchPos(wp,zoneID,x,z);
	if(pd == NULL || pd->flag == 0){
		if(wp->selPos != NULL){
			CLACT_PaletteNoChg(wp->selPos->pAct,
				TMAP_APAL_NTOWN+wp->selPos->prm.typ+wp->selPos->flag);
		}
		wp->selPos = NULL;
		return 0;
	}
	if(wp->selPos == NULL){
		wp->selCount = 0;
		wp->selFrame = 0;
	}else{
		/*
		 * c10�ƃ`�����s�I�����[�h�͗אڂ��Ă��邽�߁A���NULL�`�F�b�N�ɂ�����Ȃ�
		 * ����āA���ӓI�ɑI���A�j����Off���Ă��
		 */	
		if(	pd->prm.r == TMAP_VIEW_FLAG_LOAD ||
			pd->prm.r == TMAP_VIEW_FLAG_LEAG){
			CLACT_PaletteNoChg(wp->selPos->pAct,
				TMAP_APAL_NTOWN+wp->selPos->prm.typ+wp->selPos->flag);
		}
	}
	wp->selPos = pd;
	return 1;
}

/**
 *	@brief	�^�E��View ��{�`��
 */
void TownViewDataDraw(TMAP_VIEW_DAT* wp,int mode)
{
	short i;
	TMAP_VIEW_OBJ *pd;

	if(wp->selPos == NULL || mode != TMAP_MJUMP){
		return;
	}

	if(wp->selFrame == 0){
		CLACT_PaletteNoChg( wp->selPos->pAct,TMAP_APAL_A1TOWN+wp->selPos->prm.typ);
	}else{
		CLACT_PaletteNoChg( wp->selPos->pAct,	//�I���W�i��
				TMAP_APAL_NTOWN+wp->selPos->prm.typ+wp->selPos->flag);
	}
	wp->selCount++;
	if(wp->selCount == TMAP_ACT_TANMF){
		wp->selCount = 0;
		wp->selFrame ^= 1;
	}
}

//============================================================
//�}�b�v�u���b�N�f�[�^�Q�Ɗ֘A
//============================================================
/**
 *	@brief	�}�b�v�u���b�N�f�[�^���[�h
 */
TMAP_GDAT_LIST* TMapBlockDataLoad(const char* path,int heapID)
{
	FSFile fp;
	int ret,i;
	int dat_num;
	TMAP_GDAT_LIST *pWork;
	TMAP_GDAT *wp;
	
	FS_InitFile(&fp);
	if(!FS_OpenFile(&fp,path)){
		OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n",path);
		GF_ASSERT(0);
		return NULL;
	}
	//�f�[�^���擾
	ret = FS_ReadFile(&fp,&dat_num,4);
	GF_ASSERT(ret >= 0 && "ERROR:tmap block data num can't read");
	
	//�������m��
	pWork = sys_AllocMemory(heapID,sizeof(TMAP_GDAT_LIST));
	memset(pWork,0,sizeof(TMAP_GDAT_LIST));
	pWork->pDat = sys_AllocMemory(heapID,sizeof(TMAP_GDAT)*dat_num);
	memset(pWork->pDat,0,sizeof(TMAP_GDAT)*dat_num);

	pWork->num = dat_num;	//����ۑ�

	for(i = 0;i < pWork->num;i++){
		wp = &(pWork->pDat[i]);
		ret = FS_ReadFile(&fp,wp,sizeof(TMAP_GDAT));
		wp->id = i;
	}
	(void)FS_CloseFile(&fp);

	return pWork;
}

/**
 *	@brief	�}�b�v�u���b�N�f�[�^���
 */
void TMapBlockDataRelease(TMAP_GDAT_LIST* pWork)
{
	sys_FreeMemoryEz(pWork->pDat);
	sys_FreeMemoryEz(pWork);
}

/**
 *	@brief	�}�b�v�u���b�N�f�[�^�@�u���b�N�f�[�^�擾
 *
 *	@param	pWork	�f�[�^���X�g�z��̐擪�|�C���^
 *	@param	x		��������u���b�N��X���W
 *	@param	z		��������u���b�N��Z���W
 *	@param	mapView	�z�z�}�b�v�`��t���O
 *	�u���b�N��x,z���W����u���b�N�f�[�^�ւ̃|�C���^���擾����
 *	������Ȃ������ꍇNULL��Ԃ�
 */
TMAP_GDAT* TMapBlockDataGet(TMAP_GDAT_LIST* pWork,int x,int z,u16 mapView)
{
	int i;
	TMAP_GDAT* wp;

	OS_Printf("TMapBlockNum = %d : get(%d,%d)\n",pWork->num,x,z);
	for(i = 0;i < pWork->num;i++){
		wp = &(pWork->pDat[i]);
//		OS_Printf("TMapBlockGet Search = %d (%d,%d)\n",i,wp->x,wp->z);
		if((wp->x == x) && (wp->z == z)){
			if(wp->view == 0 || (wp->view & mapView)){
//				OS_Printf("TMapBlockGet Index = %d\n",i);
				return wp;
			}else{
				return NULL;
			}
		}
	}
//	OS_Printf("TMapBlockGet Index = none\n");
	return NULL;
}


