/**
 *	@file	tmap_act.c
 *	@brief	�^�E���}�b�v���W���[���@�Z���A�N�^�[����
 *	@author	Miyuki Iwasawa
 *	@date	05.12.21
 */

#include "common.h"
#include "field/field_matrix.h"
#include "field/field_place_name.h"
#include "system/procsys.h"
#include "system/arc_util.h"
#include "system/arc_tool.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/render_oam.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/msgdata.h"

#include "application/townmap.h"
#include "tmap.h"

#define TMAPACT_CUR_NUM	(1)
#define TMAPACT_HERO_NUM	(1)
#define TMAPACT_BTN_NUM	(1)
#define TMAPACT_FOOT_MAX	(5)
#define TMAPACT_TVIEW_MAX	(TMAP_ARRIVEDATA_MAX)

#define TMAP_ACT_MAX	(\
 TMAPACT_CUR_NUM + \
 TMAPACT_HERO_NUM + \
 TMAPACT_BTN_NUM + \
 TMAPACT_FOOT_MAX + \
 TMAPACT_TVIEW_MAX)

#define TMAP_ACTRES_MAX	(5)


///�v���g�^�C�v
void TMapCellActorInit(TMAP_MAIN_DAT *pMain);
void TMapCellActorRelease(TMAP_MAIN_DAT *pMain);
void TMapCellActorMain(TMAP_MAIN_DAT *pMain);
void TMapCellActorTrans(TMAP_MAIN_DAT* pMain);


void TMapCellActorInit(TMAP_MAIN_DAT *pMain)
{
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,VISIBLE_ON);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ,VISIBLE_ON);

	initVramTransferManagerHeap(32,pMain->heapID);

	//�Z���A�N�^�[�V�X�e��������
	pMain->pCActSys = CATS_AllocMemory(pMain->heapID);
	pMain->pCActRes = CATS_ResourceCreate(pMain->pCActSys);

	{
		TCATS_OAM_INIT	coi = {
			0,128,		///< ���C��	OAM�Ǘ��̈�E�J�n/�I��
			0,32,		///< ���C��	�A�t�B���Ǘ��̈�E�J�n/�I��
			0,128,		///< �T�u	OAM�Ǘ��̈�E�J�n/�I��
			0,32,		///< �T�u	�A�t�B���Ǘ��̈�E�J�n/�I��
		};
		TCATS_CHAR_MANAGER_MAKE ccmm = {
			TMAP_ACTRES_MAX,	//ID���䐔
			1024,	//���C����ʃT�C�Y(byte�P��)
			1024,	//�T�u��ʃT�C�Y(byte�P��)
			GX_OBJVRAMMODE_CHAR_1D_32K,	//���C��OBJ���[�h�w��
			GX_OBJVRAMMODE_CHAR_1D_32K,	//�T�uOBJ���[�h�w��
		};

		CATS_SystemInit( pMain->pCActSys, &coi, &ccmm, 32 );
		CATS_ClactSetInit( pMain->pCActSys, pMain->pCActRes,TMAP_ACT_MAX );
	}

	{
#if 0
		TCATS_RESOURCE_FILE_LIST list = {
			"data/tmapn_res_chr.txt",		// �L�����N�^
			"data/tmapn_res_pal.txt",		// �p���b�g
			"data/tmapn_res_cell.txt",	// �Z��
			"data/tmapn_res_canm.txt",	// �Z���A�j��
			NULL,						// �}���`�Z��
			NULL,						// �}���`�Z���A�j��
			"data/tmapn_celact.txt"		// �w�b�_�[		
		};
		CATS_ResourceLoad(pMain->pCActSys,pMain->pCActRes,&list);
#else
		TCATS_RESOURCE_FILE_LIST list = {
			"data/tmapn_chr.resdat",		// �L�����N�^
			"data/tmapn_pal.resdat",		// �p���b�g
			"data/tmapn_cell.resdat",	// �Z��
			"data/tmapn_canm.resdat",	// �Z���A�j��
			NULL,						// �}���`�Z��
			NULL,						// �}���`�Z���A�j��
			"data/tmapn_celact.cldat"		// �w�b�_�[		
		};
		CATS_ResourceLoadBinary(pMain->pCActSys,pMain->pCActRes,&list);
#endif
		
	}
}

void TMapCellActorRelease(TMAP_MAIN_DAT *pMain)
{
	CATS_ResourceDestructor(pMain->pCActSys,pMain->pCActRes);
	CATS_FreeMemory(pMain->pCActSys);
	DellVramTransferManager();	
}

void TMapCellActorMain(TMAP_MAIN_DAT *pMain)
{
	CATS_Draw(pMain->pCActRes);
}

void TMapCellActorTrans(TMAP_MAIN_DAT* pMain)
{
	CATS_RenderOamTrans();
}


