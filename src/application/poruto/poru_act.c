/**
 *	@brief	�|���g�@�A�N�^�[�V�X�e��
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
#include "system/bmp_list.h"
#include "system/pm_str.h"
#include "system/buflen.h"
#include "system/window.h"
#include "communication/communication.h"

#include "application/poru_tool.h"
#include "porusys.h"

#define PORUC_ACTRES_MAX	(3)

///�v���g�^�C�v
void PoruCase_ActorInit(PORU_CASE_WORK *wk);
void PoruCase_ActorRelease(PORU_CASE_WORK *wk);
void PoruCase_ActorMain(PORU_CASE_WORK *wk);
void PoruCase_ActorTrans(PORU_CASE_WORK* wk);

void PoruCase_ActorInit(PORU_CASE_WORK *wk)
{
	initVramTransferManagerHeap(32,wk->heapID);

	//�Z���A�N�^�[�V�X�e��������
	wk->pActSys = CATS_AllocMemory(wk->heapID);
	wk->pActRes = CATS_ResourceCreate(wk->pActSys);

	{
		TCATS_OAM_INIT	coi = {
			0,128,		///< ���C��	OAM�Ǘ��̈�E�J�n/�I��
			0,32,		///< ���C��	�A�t�B���Ǘ��̈�E�J�n/�I��
			0,128,		///< �T�u	OAM�Ǘ��̈�E�J�n/�I��
			0,32,		///< �T�u	�A�t�B���Ǘ��̈�E�J�n/�I��
		};
		TCATS_CHAR_MANAGER_MAKE ccmm = {
			PORUC_ACTRES_MAX,	//ID���䐔
			1024,	//���C����ʃT�C�Y(byte�P��)
			1024,	//�T�u��ʃT�C�Y(byte�P��)
			GX_OBJVRAMMODE_CHAR_1D_32K,	//���C��OBJ���[�h�w��
			GX_OBJVRAMMODE_CHAR_1D_32K,	//�T�uOBJ���[�h�w��
		};

		CATS_SystemInit( wk->pActSys, &coi, &ccmm, 32 );
		CATS_ClactSetInit( wk->pActSys, wk->pActRes,PORUCASE_ACTMAX );

		//OAM������
		REND_OAM_UtilOamRamClear_Main(wk->heapID);
		REND_OAM_UtilOamRamClear_Sub(wk->heapID);
	}

	{
		TCATS_RESOURCE_FILE_LIST list = {
			"data/porucase_chr.resdat",		// �L�����N�^
			"data/porucase_pal.resdat",		// �p���b�g
			"data/porucase_cell.resdat",	// �Z��
			"data/porucase_canm.resdat",	// �Z���A�j��
			NULL,						// �}���`�Z��
			NULL,						// �}���`�Z���A�j��
			"data/porucase_celact.cldat"		// �w�b�_�[		
		};
		CATS_ResourceLoadBinary( wk->pActSys, wk->pActRes, &list );
	}

	///�|���gOAM�}�l�[�W��������
	wk->poruMan = PoruOam_SysInit(wk->heapID,1,1,PORUOAM_DRAW_MAIN,PORUOAM_CGXOFS_AUTO);

	//�ʐM���Ȃ�ʐM�A�C�R�����A
	if(CommIsInitialize()){
		WirelessIconEasy();
	}

	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,VISIBLE_ON);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ,VISIBLE_ON);
}

void PoruCase_ActorRelease(PORU_CASE_WORK *wk)
{
	PoruOam_SysRelease(wk->poruMan);
	CATS_ResourceDestructor(wk->pActSys,wk->pActRes);
	CATS_FreeMemory(wk->pActSys);
	DellVramTransferManager();	
}

void PoruCase_ActorMain(PORU_CASE_WORK *wk)
{
	CATS_Draw(wk->pActRes);
	PoruOam_DrawMain(wk->poruMan);
}

void PoruCase_ActorTrans(PORU_CASE_WORK* wk)
{
	CATS_RenderOamTrans();
}

void NAct_CursorChg(PORU_CASE_WORK* wk,BOOL mode)
{
	if(mode == FALSE){
		CLACT_PaletteNoChg(wk->pAct[NACT_CURSOR],NACT_CUR_PALF);
		CLACT_SetAnmFlag(wk->pAct[NACT_UP],TRUE);
		CLACT_SetAnmFlag(wk->pAct[NACT_DOWN],TRUE);
	}else{
		CLACT_PaletteNoChg(wk->pAct[NACT_CURSOR],NACT_CUR_PALT);
		CLACT_SetAnmFlag(wk->pAct[NACT_UP],FALSE);
		CLACT_SetAnmFlag(wk->pAct[NACT_DOWN],FALSE);
	}
}
