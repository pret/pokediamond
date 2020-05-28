/**
 *	@file	townmap.c
 *	@brief	���[���h�}�b�v���W���[���@���C��
 *	@outhor	Miyuki Iwasawa
 *	@date	05.09.07
 */
#include "common.h"
#include "system/procsys.h"
#include "system/arc_util.h"
#include "system/arc_tool.h"
#include "system/brightness.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/pm_str.h"
#include "system/msgdata.h"
#include "system/fontproc.h"
#include "system/snd_tool.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/render_oam.h"
#include "system/wipe.h"
#include "system/buflen.h"
#include "gflib/touchpanel.h"
#include "field/field_matrix.h"
#include "field/field_place_name.h"
#include "application/app_tool.h"
#include "application/townmap.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_place_name.h"
#include "msgdata/msg_townmap.h"
#include "tmap.h"
#include "tmap_act.h"
#include "tmap_snd_def.h"

#define OSP_TMAP_HEAP_SIZE	0	//�q�[�v�g�p��OS�v�����g�L��

//================================================================
///�f�[�^�^��`�G���A
//================================================================
enum{
 MSEQ_MAININIT,
 MSEQ_SUBINIT,
 MSEQ_FADEIN,
 MSEQ_FADEINWAIT,
 MSEQ_MAIN,
 MSEQ_FADEOUT,
 MSEQ_FADEOUTWAIT,
 MSEQ_PROC_END,
 MSEQ_END,
};

//�v���g�^�C�v�錾�@�O���[�o��
//================================================================
///���C���Ăяo��

//�v���g�^�C�v�錾�@���[�J��
//================================================================
///�I�[�o�[���C�v���Z�X
PROC_RESULT TMapProc_Init( PROC *proc,int *seq);
PROC_RESULT TMapProc_Main( PROC *proc,int *seq);
PROC_RESULT TMapProc_End( PROC *proc,int *seq);

///VBlank�֘A
static void TMapVBlank(void * work);
///VRAM�o���N��`
static void TMapVramBankSet(void);
///�v���Z�X
static int TMapInitCommon(TMAP_MAIN_DAT* wk);
static void TMapBGLSet(TMAP_MAIN_DAT* wk,GF_BGL_INI *ini);
static void TMapBgGrapSet(TMAP_MAIN_DAT* wk);
static void TMapBgGrapRelease(TMAP_MAIN_DAT* wk);
static void TMapEndCommon(TMAP_MAIN_DAT* wk);
static void TMapMainDraw(TMAP_MAIN_DAT* wk);


static int TMapSeq_MainInit(TMAP_MAIN_DAT* wk);
static int TMapSeq_SubInit(TMAP_MAIN_DAT* wk);
static int TMapSeq_FadeInWait(TMAP_MAIN_DAT* wk);
static int TMapSeq_Main(TMAP_MAIN_DAT* wk);
static int TMapSeq_FadeOutWait(TMAP_MAIN_DAT* wk);
static int TMapSeq_End(TMAP_MAIN_DAT* wk);

//================================================================
///�f�[�^��`�G���A
//================================================================

///���[�h�ʐ���֐���`
extern int	TMapNormal_Init(TMAP_MAIN_DAT* pMain);
extern int	TMapNormal_Build(TMAP_MAIN_DAT* pMain);
extern int	TMapNormal_FadeInSet(TMAP_MAIN_DAT* pMain);
extern int	TMapNormal_FadeOutSet(TMAP_MAIN_DAT* pMain);
extern int	TMapNormal_KeyIn(TMAP_MAIN_DAT* pMain);
extern int	TMapNormal_Main(TMAP_MAIN_DAT* pMain);
extern int	TMapNormal_Draw(TMAP_MAIN_DAT* pMain);
extern int	TMapNormal_Release(TMAP_MAIN_DAT* pMain);
extern int	TMapNormal_VBlank(TMAP_MAIN_DAT* pMain);
extern int	TMapJump_KeyIn(TMAP_MAIN_DAT* pMain);

extern int	TMapBG_FadeInSet(TMAP_MAIN_DAT* pMain);
extern int	TMapBG_FadeOutSet(TMAP_MAIN_DAT* pMain);
extern int	TMapBG_KeyIn(TMAP_MAIN_DAT* pMain);

const TMAP_SUB_PROC TMapSubProcData[TMAP_MODE_MAX] = {
 {
	TMapNormal_Init,
	TMapNormal_Build,
	TMapNormal_FadeInSet,
	TMapNormal_FadeOutSet,
	TMapNormal_KeyIn,
	TMapNormal_Main,
	TMapNormal_Draw,
	TMapNormal_Release,
	TMapNormal_VBlank,
 },
 {
	TMapNormal_Init,
	TMapNormal_Build,
	TMapNormal_FadeInSet,
	TMapNormal_FadeOutSet,
	TMapJump_KeyIn,
	TMapNormal_Main,
	TMapNormal_Draw,
	TMapNormal_Release,
	TMapNormal_VBlank,
 },
 {
	TMapNormal_Init,
	TMapNormal_Build,
	TMapBG_FadeInSet,
	TMapBG_FadeOutSet,
	TMapBG_KeyIn,
	TMapNormal_Main,
	TMapNormal_Draw,
	TMapNormal_Release,
	TMapNormal_VBlank,
 },
};

//--------------------------------------------------
///�v���O�����G���A
//----------------------------------------------------------------
/**
 *	@brief	���[���h�}�b�v �v���Z�X������
 *	@param	proc	�v���Z�X�f�[�^
 *	@param	seq		�V�[�P���X
 *
 *	@return	������
 */
PROC_RESULT TMapProc_Init( PROC *proc,int *seq)
{
	TMAP_IO_DAT dat;
	TMAP_MAIN_DAT *wk = NULL;
	TOWNMAP_PARAM * param = (TOWNMAP_PARAM*)PROC_GetParentWork(proc);

	//���[�N�G���A�擾
	HeapStatePush();

	//�q�[�v�쐬
	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_TOWNMAP,0x20000);
	TMAP_HEAP_PRINT("�v���Z�X�������J�n");
	
	wk = PROC_AllocWork( proc,sizeof(TMAP_MAIN_DAT),HEAPID_TOWNMAP);
	memset(wk,0,sizeof(TMAP_MAIN_DAT));
	
	//�p�����[�^���p��
	wk->param = param;
	if(param->mode < TMAP_MODE_MAX){
		wk->mode = param->mode;
	}else{
		wk->mode = TMAP_MNORMAL;
	}
	wk->mapView = param->view_f;	//�z�z�}�b�v�`��t���O���p��
	wk->heapID = HEAPID_TOWNMAP;

	//�T�E���h���p���ݒ�
	Snd_DataSetByScene( SND_SCENE_SUB_TOWNMAP, 0, 0 );

	TMAP_HEAP_PRINT("�v���Z�X�������I��");
	return PROC_RES_FINISH;
}

/**
 *	@brief	���[���h�}�b�v �v���Z�X���C��
 *	@param	proc	�v���Z�X�f�[�^
 *	@param	seq		�V�[�P���X
 *
 *	@return	������
 */
PROC_RESULT TMapProc_Main( PROC *proc,int *seq)
{
	TMAP_MAIN_DAT *wk = PROC_GetWork(proc);

	switch(wk->main_seq){
	case MSEQ_MAININIT:
		wk->main_seq = TMapSeq_MainInit(wk);
		break;
	case MSEQ_SUBINIT:
		wk->main_seq = TMapSeq_SubInit(wk);
		break;
	case MSEQ_FADEINWAIT:
		wk->main_seq = TMapSeq_FadeInWait(wk);
		TMapMainDraw(wk);
		break;
	case MSEQ_MAIN:
		wk->main_seq = TMapSeq_Main(wk);
		TMapMainDraw(wk);
		break;
	case MSEQ_FADEOUTWAIT:
		wk->main_seq = TMapSeq_FadeOutWait(wk);
		TMapMainDraw(wk);
		break;
	case MSEQ_END:
		wk->main_seq = TMapSeq_End(wk);
		break;
	case MSEQ_PROC_END:
		return PROC_RES_FINISH;	
	}
	return PROC_RES_CONTINUE;
}

/**
 *	@brief	���[���h�}�b�v �v���Z�X�I��
 *	@param	proc	�v���Z�X�f�[�^
 *	@param	seq		�V�[�P���X
 *
 *	@return	������
 */
PROC_RESULT TMapProc_End( PROC *proc,int *seq)
{
	int i = 0;

	TMAP_MAIN_DAT *wk = PROC_GetWork(proc);
	
	//���[�N�G���A���
	PROC_FreeWork(proc);

	HeapStatePop();
	HeapStateCheck(wk->heapID);
	
	TMAP_HEAP_PRINT("�v���Z�X�I��");
	sys_DeleteHeap(HEAPID_TOWNMAP);
	return PROC_RES_FINISH;
}

/**
 *	@brief �^�E���}�b�v���W���[��
 */
static void TMapVBlank(void * work)
{
	TMAP_MAIN_DAT* wk = work;

	//�T�u�V�[�P���X�������s
	if(TMapSubProcData[wk->mode].vBlank != NULL){
		(TMapSubProcData[wk->mode].vBlank)(wk);	
	}
	
	NNS_GfdDoVramTransfer();	//VRam�]���}�l�[�W�����s
	TMapCellActorTrans(wk);
	GF_BGL_VBlankFunc( wk->bgl );
	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

/**
 *	@brief �^�E���}�b�v���W���[�� VRAM BANK Set
 */
static void TMapVramBankSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_A,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_NONE,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_NONE			// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &vramSetTable );
}


/**
 *	@brief �^�E���}�b�v���ʏ�����
 *
 *	@param	wk	TMAP_MAIN_DAT*
 */
static int TMapInitCommon(TMAP_MAIN_DAT* wk)
{
	switch(wk->sub_seq){
	case 0:
		//Blank�֐����Z�b�g
		sys_VBlankFuncChange(NULL, NULL);
		sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane(0);
		GXS_SetVisiblePlane(0);
		
		//���@�ʒu�擾
		if(wk->param->player_x == 0 && wk->param->player_z == 0){
			wk->gx = 3;
			wk->gz = 27;
		}else{
			wk->gx = wk->param->player_x/32;
			wk->gz = wk->param->player_z/32;
		}
		wk->cposX = wk->gx;
		wk->cposZ = wk->gz;

		//���b�Z�[�W���\�[�X�擾
		wk->pMsgMap = MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,
				NARC_msg_place_name_dat,wk->heapID);
		wk->pMsgTMap = MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,
				NARC_msg_townmap_dat,wk->heapID);
		wk->placeName = STRBUF_Create(BUFLEN_PLACE_NAME,wk->heapID);
		
		//�]�[�����\�[�X�擾
		wk->pZone = InitFMZ(wk->heapID);

		//�u���b�N�f�[�^�擾
		wk->pBDat = TMapBlockDataLoad("data/tmap_block.dat",wk->heapID);
		break;
	case 1:
		//Bank�Z�b�g
		TMapVramBankSet();

		//BG�֘A�Z�b�g
		wk->bgl = GF_BGL_BglIniAlloc(wk->heapID);

		TMapBGLSet(wk,wk->bgl);
		TMapBgGrapSet(wk);
		
		//�^�b�`�p�l��������
		InitTPSystem();
		InitTPNoBuff(4);

		//�Z���A�N�^�[������
		TMapCellActorInit(wk);
		break;
	case 2:
		sys_VBlankFuncChange(TMapVBlank, wk);	//VBlankSet

		//�f�t�H���g�L�[�擾�֐��Z�b�g
		wk->keyFunc = TMapSubProcData[wk->mode].keyIO;
		wk->sub_seq = 0;
		return TMAP_SEQ_FINISH;
	}
	wk->sub_seq++;
	return TMAP_SEQ_CONTINUE;
}
/**
 *	@brief	�^�E���}�b�v���ʏI������
 *	@param	wk	TMAP_MAIN_DAT*
 */
static void TMapEndCommon(TMAP_MAIN_DAT* wk)
{
	int i;

	//�^�b�`�p�l���I��
	StopTP();

	GF_Disp_GX_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 |
		GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ, VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 |
		GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ, VISIBLE_OFF);
	
	sys_VBlankFuncChange(NULL, NULL);
	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

	//�Z���A�N�^�[�I��
	TMapCellActorRelease(wk);

	TMapBgGrapRelease(wk);
	for(i = 0;i < 8;i++){
		GF_BGL_BGControlExit( wk->bgl, i);
	}

	sys_FreeMemoryEz(wk->bgl);

	//�u���b�N�f�[�^���
	TMapBlockDataRelease(wk->pBDat);
	//�]�[���f�[�^���
	FreeFMZ(wk->pZone);
	//���b�Z�[�W�}�l�[�W���[���
	STRBUF_Delete(wk->placeName);
	MSGMAN_Delete(wk->pMsgTMap);
	MSGMAN_Delete(wk->pMsgMap);
}

/**
 *	@brief	�^�E���}�b�vDraw
 */
static void TMapMainDraw(TMAP_MAIN_DAT* wk)
{
	//�T�uDraw
	(TMapSubProcData[wk->mode].draw)(wk);
	
	//�A�N�^�[
	TMapCellActorMain(wk);
}
/**
 *	@brief	�^�E���}�b�v BGL�ݒ�
 */
static void TMapBGLSet(TMAP_MAIN_DAT* wk,GF_BGL_INI *ini)
{
	int i,frame;
	
	{	//BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0,GX_BG0_AS_2D
		};
		GF_BGL_InitBG(&BGsys_data);
	}
	
	{
	GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
		{	//MAIN BG0
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			0,0,0,FALSE},
		{	//MAIN BG1
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			1,0,0,FALSE},
		{	//MAIN BG2
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			2,0,0,FALSE},
		{	//MAIN BG3
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			3,0,0,FALSE},
		{	//SUB BG0
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			0,0,0,FALSE},
		{	//SUB BG1
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			1,0,0,FALSE},
		{	//SUB BG2
			0,0,0x2000,0,GF_BGL_SCRSIZ_512x512,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd000,GX_BG_CHARBASE_0x10000,GX_BG_EXTPLTT_01,
			2,0,0,FALSE},
		{	//SUB BG3
			0,0,0x2000,0,GF_BGL_SCRSIZ_512x512,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xb000,GX_BG_CHARBASE_0x10000,GX_BG_EXTPLTT_01,
			3,0,0,FALSE},
	};
	frame = GF_BGL_FRAME0_M;
	for(i = 0;i < 8;i++){
		GF_BGL_BGControlSet(ini,frame,&(TextBgCntDat[i]),GF_BGL_MODE_TEXT);
		GF_BGL_ScrClear(ini,frame++);
	}
	}
	GF_BGL_ClearCharSet(GF_BGL_FRAME0_M,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME1_M,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME2_M,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME3_M,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME0_S,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME1_S,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME2_S,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME3_S,32,0,wk->heapID);
}

/**
 *	@brief	�^�E���}�b�v�@2D���\�[�X�t�@�C���擾
 */
#define GRA_M01_NCGR	(NARC_tmap_gra_tmap01_ncgr)
#define GRA_S01_NCGR	(NARC_tmap_gra_tmap02_ncgr)
#define GRA_S02_NCGR	(NARC_tmap_gra_tmap02_sw_ncgr)

#define GRA_M01_NCLR	(NARC_tmap_gra_tmap01_nclr)
#define GRA_S01_NCLR	(NARC_tmap_gra_tmap02_nclr)

#define GRA_M_MLOAD	(NARC_tmap_gra_tmap01_mload_nscr)
#define GRA_M_BACK	(NARC_tmap_gra_tmap01_back_nscr)
#define GRA_M_DIS	(NARC_tmap_gra_tmap01_dis_nscr)
#define GRA_S_DM	(NARC_tmap_gra_tmap02_dm_nscr)
#define GRA_S_DR	(NARC_tmap_gra_tmap02_dr_nscr)
#define GRA_S_DSWM	(NARC_tmap_gra_tmap02_dswm_nscr)
#define GRA_S_SW	(NARC_tmap_gra_tmap02_sw_nscr)
#define GRA_S_DIS	(NARC_tmap_gra_tmap02_dis_nscr)

//#define GRA_
static void TMapBgGrapSet(TMAP_MAIN_DAT* wk)
{
	void* tmp;
	u32	size,arcID;
	ARCHANDLE* handle;

	arcID = ARC_TMAP_GRA;

	//�A�[�J�C�u�̃n���h�����擾
	handle = ArchiveDataHandleOpen(ARC_TMAP_GRA,wk->heapID);

	//�L�����N�^�f�[�^�]��
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,handle,
		arcID,GRA_M01_NCGR,GF_BGL_FRAME1_M,0,0,0);
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,handle,
		arcID,GRA_S01_NCGR,GF_BGL_FRAME2_S,0,0,0);
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,handle,
		arcID,GRA_S02_NCGR,GF_BGL_FRAME1_S,0,0,0);
	
	//�p���b�g�]��
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,handle,
		arcID,GRA_M01_NCLR,PALTYPE_MAIN_BG,2,0,0);
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,handle,
		arcID,GRA_S01_NCLR,PALTYPE_SUB_BG,2,0,0);

	//�X�N���[��
	wk->pScrBuf01 = APP_ArcScrFileUnpack(handle,arcID,GRA_M_MLOAD,&wk->pScr01,wk->heapID);
	wk->pScrBuf01_back = APP_ArcScrFileUnpack(handle,arcID,GRA_M_BACK,&wk->pScr01_back,wk->heapID);
	wk->pScrBuf01_dis = APP_ArcScrFileUnpack(handle,arcID,GRA_M_DIS,&wk->pScr01_dis,wk->heapID);

	wk->pScrBuf02_dm = APP_ArcScrFileUnpack(handle,arcID,GRA_S_DM,&wk->pScr02_dm,wk->heapID);
	wk->pScrBuf02_dr = APP_ArcScrFileUnpack(handle,arcID,GRA_S_DR,&wk->pScr02_dr,wk->heapID);
	wk->pScrBuf02_dswm = APP_ArcScrFileUnpack(handle,arcID,GRA_S_DSWM,&wk->pScr02_dswm,wk->heapID);
	wk->pScrBuf02_sw = APP_ArcScrFileUnpack(handle,arcID,GRA_S_SW,&wk->pScr02_sw,wk->heapID);
	wk->pScrBuf02_dis = APP_ArcScrFileUnpack(handle,arcID,GRA_S_DIS,&wk->pScr02_dis,wk->heapID);
	
	//�N���[�Y
	ArchiveDataHandleClose( handle );
	
	//�t�H���g�p�p���b�g�Z�b�g
	SystemFontPaletteLoad(PALTYPE_MAIN_BG,FONT_SYS_PAL*32,wk->heapID);
	SystemFontPaletteLoad(PALTYPE_SUB_BG,FONT_SYS_PAL*32,wk->heapID);
}

/**
 *	@brief	���C��2D�O���t�B�b�N���\�[�X���
 */
static void TMapBgGrapRelease(TMAP_MAIN_DAT* wk)
{
	sys_FreeMemoryEz(wk->pScrBuf02_dis);
	sys_FreeMemoryEz(wk->pScrBuf02_sw);
	sys_FreeMemoryEz(wk->pScrBuf02_dswm);
	sys_FreeMemoryEz(wk->pScrBuf02_dr);
	sys_FreeMemoryEz(wk->pScrBuf02_dm);
	sys_FreeMemoryEz(wk->pScrBuf01_dis);
	sys_FreeMemoryEz(wk->pScrBuf01_back);
	sys_FreeMemoryEz(wk->pScrBuf01);
}

//============================================================================================
//	�V�[�P���X
//============================================================================================

/**
 *	@brief	���C��/�T�u������������
 */
static int TMapSeq_MainInit(TMAP_MAIN_DAT* wk)
{
	//���C��������
	if(TMapInitCommon(wk) != TMAP_SEQ_FINISH){
		return PROC_RES_CONTINUE;	
	}
//	TMAP_HEAP_PRINT("���C���������I��");

	//�T�u�����������擾
	(TMapSubProcData[wk->mode].init)(wk);
	return MSEQ_SUBINIT;
}

/**
 *	@brief	���[�h�ʃ��\�[�X������
 */
static int TMapSeq_SubInit(TMAP_MAIN_DAT* wk)
{
	//���[�h�ʏ�����
	if((TMapSubProcData[wk->mode].build)(wk) != TMAP_SEQ_FINISH){
		return MSEQ_SUBINIT;	
	}
	
	//���[�h�ʃt�F�[�h�C���Ăяo��
	TMapSubProcData[wk->mode].fadein(wk);
	return MSEQ_FADEINWAIT;
}

/**
 *	@brief	�t�F�[�h�C���҂�
 */
static int TMapSeq_FadeInWait(TMAP_MAIN_DAT* wk)
{
	if(!WIPE_SYS_EndCheck()){
		return MSEQ_FADEINWAIT;
	}
	return MSEQ_MAIN;
}

/**
 *	@brief	���[�h�ʃ��C���V�[�P���X�I���҂�
 */
static int TMapSeq_Main(TMAP_MAIN_DAT* wk)
{
	//�L�[�擾
	if( (wk->keyFunc)(wk) != TMAP_SEQ_FINISH){
		//�T�u���C������
		TMapSubProcData[wk->mode].main(wk);
		return MSEQ_MAIN;
	}
	//���[�h�ʃt�F�[�h�A�E�g���N�G�X�g
	TMapSubProcData[wk->mode].fadeout(wk);
	return MSEQ_FADEOUTWAIT;
}

/**
 *	@brief	�t�F�[�h�A�E�g�I���҂�
 */
static int TMapSeq_FadeOutWait(TMAP_MAIN_DAT* wk)
{
	if(WIPE_SYS_EndCheck()){
		//��ʂ������ݒ�
		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE,GX_BLEND_PLANEMASK_NONE,31,0);
		WIPE_SetBrightness(WIPE_DISP_MAIN,WIPE_FADE_BLACK);
		WIPE_SetBrightness(WIPE_DISP_SUB,WIPE_FADE_BLACK);
		WIPE_ResetWndMask(WIPE_DISP_MAIN);
		WIPE_ResetWndMask(WIPE_DISP_SUB);
		return MSEQ_END;
	}

	TMapSubProcData[wk->mode].main(wk);
	return MSEQ_FADEOUTWAIT;
}

/**
 *	@brief	���C��/�T�u�@�������������
 */
static int TMapSeq_End(TMAP_MAIN_DAT* wk)
{
	//���[�h�ʉ��
	(TMapSubProcData[wk->mode].release)(wk);
	
	//���C�����������
	TMapEndCommon(wk);
//	TMAP_HEAP_PRINT("��������I��");
	return MSEQ_PROC_END;	
}

//============================================================================================
//	�f�o�b�O
//============================================================================================
