/**
 *	@file	porudemo.c
 *	@brief	�|���g�f��
 *	@author	Miyuki Iwasawa
 *	@date	06.03.27
 */

#include "common.h"
#include "system/procsys.h"
#include "system/arc_util.h"
#include "system/arc_tool.h"
#include "system/snd_tool.h"
#include "system/fontproc.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/pm_str.h"
#include "system/msgdata.h"
#include "system/buflen.h"
#include "system/window.h"
#include "system/brightness.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/render_oam.h"
#include "system/wipe.h"
#include "system/window.h"
#include "system/poruto_name.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/poruto_name.h"
#include "system/wordset.h"
#include "gflib/calctool.h"
#include "communication/communication.h"

#include "application/app_tool.h"
#include "application/poru_tool.h"
#include "savedata/poruto_util.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_poruto_select.h"
#include "porudemo.h"
#include "poru_3d.h"
#include "poru_oam.h"
#include "porudemo.naix"
#include "poru_snd_def.h"

typedef enum{
 TALK_WIN,
 WIN_MAX,
};

#define WORDSET_PORUDEMO_BUFLEN	(64)
#define PORUD_MSG_NUM	(3)	
#define DEMO_TALK_FCOL	(GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE))

#define PORUD_CGX_START		(1)
#define BMPL_TALK_WIN_FRAME	(GF_BGL_FRAME1_M)
#define BMPL_TALK_WIN_PAL	(14)
#define BMPL_TALK_FONT_PAL	(15)
#define BMPL_TALK_WIN_CGX	(PORUD_CGX_START)

#define BMPL_TALK_PX	(2)
#define BMPL_TALK_PY	(19)
#define BMPL_TALK_SX	(27)
#define BMPL_TALK_SY	(4)
#define BMPL_TALK_FRM	(BMPL_TALK_WIN_FRAME)
#define BMPL_TALK_PAL	(BMPL_TALK_FONT_PAL)
#define BMPL_TALK_CGX	(BMPL_TALK_WIN_CGX+TALK_WIN_CGX_SIZ)

#define WINCLR_COL(col)	(((col)<<4)|(col))

#define PRA_SX	(128)
#define PRA_SY	(192+32)
#define PRA_EX	(128)
#define PRA_EY	(96)
#define PRA_SAX	(0x00001000)
#define PRA_SAY	(0x00001000)
#define PRA_EAX	(0x00000800)
#define PRA_EAY	(0x00000800)

#define PKA_SX	(POKEA_INI_PX)
#define PKA_SY	(POKEA_INI_PY)
#define PKA_EX	(128)
#define PKA_EY	(112)
#define PKA_SY2	(96)
#define PKA_SAX	(0x0001000)
#define PKA_SAY	(0x0001000)
#define PKA_EAX	(0x0001800)
#define PKA_EAY	(0x0001800)

#define PKA_TIME_WAIT	(4)	///�|���g���L���b�`��������̃E�F�C�g

#define ANM_PORU_TIME01	(24)
#define ANM_PORU_TIME	(ANM_PORU_TIME01)

#define TASK_MAX	(4)
//======================================================
//�\���̒�`
///======================================================

typedef struct _PORUDEMO_MSG{
	WORDSET* wset;		//���[�N
	STRBUF	*tmp;		//�ėp
	STRBUF	*mbuf[PORUD_MSG_NUM];	//
}PORUDEMO_MSG;

typedef struct _PORUDEMO_OBJ{
	VecFx32	sv;
	VecFx32	ev;
	VecFx32	dv;
	VecFx32	asv;
	VecFx32	aev;
	VecFx32	adv;
	fx32	r;
	fx32	df;
	u16		ct01;
	u16		ct02;
	fx32	frm;
	int	time;
}PORUDEMO_OBJ;

//�v���g�^�C�v
typedef struct _PORUDEMO_ANM PORUDEMO_ANM;
typedef struct _PORUDEMO_TASK{
	int		id;
	int		time;
	int		next;
	fx32	frm;
	fx32	nfrm;
	PORUDEMO_ANM*	prm;
	TCB_PTR	tcb;
}PORUDEMO_TASK;

typedef struct _PORUDEMO_ANM{
	int	time;
	int	tnum;
	int	favolite;

	PORUDEMO_OBJ	poru;
	PORUDEMO_OBJ	poke;

	CLACT_WORK_PTR	poruAct;
	SOFT_SPRITE		*pokeAct;

	PORUDEMO_TASK	task[TASK_MAX];
}_PORUDEMO_ANM;

typedef struct _PORU_DEMO_WORK{
	int	heapID;
	int	seq;
	int	wipe_f;
	u16	msgIdx;
	u16	counter;

	PORUDEMO_PARAM* param;

	///�|���g���擾�}�l�[�W��
	PORUTO_NAME_MAN	*nameMan;
	MSGDATA_MANAGER *msgMan;
	PORUDEMO_MSG	msgDat;
	PORUDEMO_POKE	poke;
	PORU3D_WORK		p3d;
	PORUOAM_MAN		*oamMan;
	PORUTO_OAM		*pOam[2];
	
	///�O���t�B�b�N���\�[�X
	GF_BGL_INI *bgl;	///<BGL�f�[�^
	GF_BGL_BMPWIN	win;

	CATS_SYS_PTR	pActSys;	///<�Z���A�N�^�[�V�X�e��

	//�A�j�����[�N
	PORUDEMO_ANM	anm;
}PORU_DEMO_WORK;

//======================================================
//�v���g�^�C�v
//======================================================
PROC_RESULT PoruDemo_Init(PROC* proc,int *seq);
PROC_RESULT PoruDemo_Main(PROC* proc,int *seq);
PROC_RESULT PoruDemo_End(PROC* proc,int *seq);

static int	PoruDemo_AnmMain(PORU_DEMO_WORK* wk);
static void PoruDemoVBlank( void * work );

static int PoruDemo_ResInit(PORU_DEMO_WORK* wk);
static int PoruDemo_ResRelease(PORU_DEMO_WORK* wk);

static void PoruDemo_BGLInit(PORU_DEMO_WORK* wk);
static void PoruDemo_BGLRelease(PORU_DEMO_WORK* wk);
static void PoruDemo_2DGraInit(PORU_DEMO_WORK* wk);
static void PoruDemo_2DGraRelease(PORU_DEMO_WORK* wk);
static void PoruDemo_BmpWinAdd(PORU_DEMO_WORK* wk);
static void PoruDemo_BmpWinRelease(PORU_DEMO_WORK* wk);

static void PoruDemo_MsgManagerGet(PORU_DEMO_WORK* wk);
static void PoruDemo_MsgManagerRelease(PORU_DEMO_WORK* wk);
static void PoruDemo_PokeParaGet(PORU_DEMO_WORK* wk);
static void PoruDemo_PokeParaRelease(PORU_DEMO_WORK* wk);
static void PoruDemo_OamInit(PORU_DEMO_WORK* wk);
static void PoruDemo_OamRelease(PORU_DEMO_WORK* wk);


//====================================================================
//
enum{
 ANMSEQ_PORUINIT,
 ANMSEQ_PORUWAIT,
 ANMSEQ_VOICESET,
 ANMSEQ_VOICEWAIT,
 ANMSEQ_REACTSET,
 ANMSEQ_REACTWAIT,
 ANMSEQ_MSGSET,
 ANMSEQ_MSGWAIT,
 ANMSEQ_END,
};
static int panm_PoruInit(PORU_DEMO_WORK* wk,PORUDEMO_ANM* anm);
static int panm_PoruWait(PORU_DEMO_WORK* wk,PORUDEMO_ANM* anm);
static int panm_PokeVoiceSet(PORU_DEMO_WORK* wk,PORUDEMO_ANM* anm);
static int panm_PokeVoiceWait(PORU_DEMO_WORK* wk,PORUDEMO_ANM* anm);
static int panm_PokeReactionSet(PORU_DEMO_WORK* wk,PORUDEMO_ANM* anm);
static int panm_PokeReactionWait(PORU_DEMO_WORK* wk,PORUDEMO_ANM* anm);
static int panm_EatMsgSet(PORU_DEMO_WORK* wk);
static int panm_EatMsgWait(PORU_DEMO_WORK* wk);

//====================================================================
//
static VecFx32	Vec_Div(VecFx32* vec,VecFx32* src,fx32 val)
{
	VecFx32	tmp = {0,0,0};

	vec->x = FX_Div(src->x,val);
	vec->y = FX_Div(src->y,val);
	vec->z = FX_Div(src->z,val);
	return tmp;
}

//======================================================
//�I�[�o�[���C�v���Z�X��`
//======================================================

/**
 *	@brief	�|���g�f���Ăяo��������
 */
PROC_RESULT PoruDemo_Init(PROC* proc,int *seq)
{
	PORUDEMO_PARAM* pp = PROC_GetParentWork(proc);
	PORU_DEMO_WORK* wk;

	HeapStatePush();

	//�q�[�v�쐬
	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_PORUTO_DEMO,0x10000);
	
	wk = PROC_AllocWork(proc,sizeof(PORU_DEMO_WORK),HEAPID_PORUTO_DEMO);
	MI_CpuClear8(wk,sizeof(PORU_DEMO_WORK));

	wk->heapID = HEAPID_PORUTO_DEMO;
	wk->param = pp;
	return PROC_RES_FINISH;
}

/**
 *	@brief	�|���g�f���@���C���v���Z�X
 */
PROC_RESULT PoruDemo_Main(PROC* proc,int* seq)
{
	PORU_DEMO_WORK* wk = (PORU_DEMO_WORK*)PROC_GetWork(proc);

	if(*seq >= 2 && *seq <= 5){
		PoruDemo_3DMain(&wk->p3d);
		PoruOam_DrawMain(wk->oamMan);
	}
	switch(*seq){
	case 0:
		//Blank�֐����Z�b�g
		sys_VBlankFuncChange(NULL, NULL);
		sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane(0);
		GXS_SetVisiblePlane(0);	
		WIPE_SetBrightness(WIPE_DISP_MAIN,WIPE_FADE_BLACK);
		WIPE_SetBrightness(WIPE_DISP_SUB,WIPE_FADE_BLACK);
		WIPE_ResetWndMask(WIPE_DISP_MAIN);
		WIPE_ResetWndMask(WIPE_DISP_SUB);
		break;
	case 1:
		if(!PoruDemo_ResInit(wk)){
			return PROC_RES_CONTINUE;	
		}
		sys_VBlankFuncChange(PoruDemoVBlank,wk);
		break;
	case 2:
		if(wk->seq++ < 4){
			return PROC_RES_CONTINUE;
		}
		wk->seq = 0;
		WIPE_SYS_Start(WIPE_PATTERN_WMS,
				WIPE_TYPE_FADEIN,
				WIPE_TYPE_FADEIN,0x0000,COMM_BRIGHTNESS_SYNC,1,wk->heapID
				);
		break;
	case 3:
		if(!WIPE_SYS_EndCheck()){
			return PROC_RES_CONTINUE;	
		}
		break;
	case 4:
		if(!PoruDemo_AnmMain(wk)){
			return PROC_RES_CONTINUE;
		}
		WIPE_SYS_Start(WIPE_PATTERN_WMS,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,0x0000,COMM_BRIGHTNESS_SYNC,1,wk->heapID
				);
		break;
	case 5:
		if(!WIPE_SYS_EndCheck()){
			return PROC_RES_CONTINUE;	
		}
		break;
	case 6:
		if(!PoruDemo_ResRelease(wk)){
			return PROC_RES_CONTINUE;
		}
		break;
	case 7:
		WIPE_SetBrightness(WIPE_DISP_MAIN,WIPE_FADE_BLACK);
		WIPE_SetBrightness(WIPE_DISP_SUB,WIPE_FADE_BLACK);
		sys_VBlankFuncChange(NULL, NULL);
		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane(0);
		GXS_SetVisiblePlane(0);	
		break;
	default:
		return PROC_RES_FINISH; 
	}
	*seq += 1;
	return PROC_RES_CONTINUE;
}

/**
 *	@brief	�|���g�f���@�v���Z�X���
 */
PROC_RESULT PoruDemo_End(PROC* proc,int* seq)
{
	PORU_DEMO_WORK* wk = (PORU_DEMO_WORK*)PROC_GetWork(proc);

	//���[�N���
	PROC_FreeWork(proc);
	
	HeapStatePop();
	HeapStateCheck(wk->heapID);
	
	sys_DeleteHeap(wk->heapID);
	return PROC_RES_FINISH;
}

/**
 *	@brief	�|���g�f���@���\�[�X������
 */
static int PoruDemo_ResInit(PORU_DEMO_WORK* wk)
{
	switch(wk->seq){
	case 0:
		PoruDemo_BGLInit(wk);
		PoruDemo_2DGraInit(wk);
		break;
	case 1:
		PoruDemo_MsgManagerGet(wk);
		PoruDemo_BmpWinAdd(wk);
		break;
	case 2:
		PoruDemo_PokeParaGet(wk);
		PoruDemo_3DInit(&wk->p3d,&wk->poke,wk->heapID);
		PoruDemo_OamInit(wk);
//		break;
//	case 3:
		wk->seq = 0;
		return TRUE;
	}
	wk->seq++;
	return FALSE;
}

/**
 *	@brief	�|���g�f���@���\�[�X���
 */
static int PoruDemo_ResRelease(PORU_DEMO_WORK* wk)
{
	switch(wk->seq){
	case 0:
		PoruDemo_OamRelease(wk);
		PoruDemo_3DRelease(&wk->p3d);
		PoruDemo_PokeParaRelease(wk);
		break;
	case 1:
		PoruDemo_BmpWinRelease(wk);
		PoruDemo_MsgManagerRelease(wk);
		break;
	case 2:
		PoruDemo_BGLRelease(wk);
		break;
	case 3:
		wk->seq = 0;
		return TRUE;
	}
	wk->seq++;
	return FALSE;
}

static void PoruDemoVBlank( void * work )
{
	PORU_DEMO_WORK * wk = work;

	GF_BGL_VBlankFunc( wk->bgl );
	SoftSpriteTextureTrans( wk->p3d.ssm );

	CATS_RenderOamTrans();
	DoVramTransferManager();	// Vram�]���}�l�[�W���[���s
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}


/**
 *	@brief	�|���g�f��VramBank�ݒ�
 */
static void PoruDemo_VBankSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_C,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_32_H,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_16_G,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_01_AB,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_0_F				// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &vramSetTable );
}

/**
 *	@brief	�|���g�f���@BGL������
 */
static void PoruDemo_BGLInit(PORU_DEMO_WORK* wk)
{
	int i = 0,frame;

	//VramBank�Z�b�g
	PoruDemo_VBankSet();

	//BGL������
	wk->bgl = GF_BGL_BglIniAlloc(wk->heapID);
	
	{	//BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0,GX_BG0_AS_3D
		};
		GF_BGL_InitBG(&BGsys_data);
	}
	
	{
	GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
		{	//MAIN BG1
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000,GX_BG_CHARBASE_0x10000,GX_BG_EXTPLTT_01,
			0,0,0,FALSE},
		{	//MAIN BG2
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			2,0,0,FALSE},
		{	//SUB BG1
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x7800,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			0,0,0,FALSE},
	};
	u8	frm_id[] = {GF_BGL_FRAME1_M,GF_BGL_FRAME2_M,GF_BGL_FRAME0_S};
		for(i = 0;i < 3;i++){
			frame = frm_id[i];
			GF_BGL_BGControlSet(wk->bgl,frame,&(TextBgCntDat[i]),GF_BGL_MODE_TEXT);
			GF_BGL_ScrClear(wk->bgl,frame);
			GF_BGL_ClearCharSet(frame,32,0,wk->heapID);
		}
	}
}

/**
 *	@brief	�|���g�f�� BGL���
 */
static void PoruDemo_BGLRelease(PORU_DEMO_WORK* wk)
{
	int i;

	for(i = GF_BGL_FRAME1_M;i < GF_BGL_FRAME3_M;i++){
		GF_BGL_BGControlExit(wk->bgl,i);
	}
	GF_BGL_BGControlExit(wk->bgl,GF_BGL_FRAME0_S);
	sys_FreeMemoryEz(wk->bgl);
}

/**
 *	@brief	�|���g�f���@2D���\�[�X������
 */
static void PoruDemo_2DGraInit(PORU_DEMO_WORK* wk)
{
	ARCHANDLE* handle;

	//�A�[�J�C�u�n���h���擾
	handle = ArchiveDataHandleOpen(ARC_PORUDEMO_GRA,wk->heapID);

	//�L�����N�^�]��
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,
		handle,ARC_PORUDEMO_GRA,NARC_porudemo_poru_demo_ncgr,
		GF_BGL_FRAME2_M,0,0,0);
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,
		handle,ARC_PORUDEMO_GRA,NARC_porudemo_poru_demo2_ncgr,
		GF_BGL_FRAME0_S,0,0,0);
	
	//�p���b�g�]��
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,
		handle,ARC_PORUDEMO_GRA,NARC_porudemo_poru_demo_nclr,
		GF_BGL_FRAME2_M,2,0x20*0x01,0);
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,
		handle,ARC_PORUDEMO_GRA,NARC_porudemo_poru_demo2_nclr,
		GF_BGL_FRAME0_S,2,0x20*0x05,0);

	//�X�N���[���]��
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,
		handle,ARC_PORUDEMO_GRA,NARC_porudemo_poru_demo_nscr,
		GF_BGL_FRAME2_M,1,0,0);
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,
		handle,ARC_PORUDEMO_GRA,NARC_porudemo_poru_demo2_nscr,
		GF_BGL_FRAME0_S,1,0,0);

	//�n���h������
	ArchiveDataHandleClose( handle );
	
	//�X�N���[���]��
	GF_BGL_LoadScreenV_Req(wk->bgl,GF_BGL_FRAME2_M);
	GF_BGL_LoadScreenV_Req(wk->bgl,GF_BGL_FRAME0_S);
}

/**
 *	@brief	�|���g�f���@2D���\�[�X���
 */
static void PoruDemo_2DResRelease(PORU_DEMO_WORK* wk)
{
	return;
}

/**
 *	@brief	�|���g�f���@BMPWIN������
 */
static void PoruDemo_BmpWinAdd(PORU_DEMO_WORK* wk)
{
	static const BMPWIN_DAT bmp = {
		BMPL_TALK_FRM,BMPL_TALK_PX, BMPL_TALK_PY,
		BMPL_TALK_SX, BMPL_TALK_SY, BMPL_TALK_PAL, BMPL_TALK_CGX
	};
	//�E�B���h�E�쐬
	GF_BGL_BmpWinAddEx(wk->bgl,&(wk->win),&bmp);
	GF_BGL_BmpWinDataFill(&wk->win,WINCLR_COL(FBMP_COL_NULL));

	//�E�B���h�E�p�L�����N�^�]��
	TalkWinGraphicSet(wk->bgl,BMPL_TALK_WIN_FRAME,
			BMPL_TALK_WIN_CGX, BMPL_TALK_WIN_PAL,wk->param->win_type, wk->heapID);
	
	//�E�B���h�E�p�t�H���g�p���b�g�]��
	TalkFontPaletteLoad(PALTYPE_MAIN_BG,BMPL_TALK_PAL*32,wk->heapID);
}

/**
 *	@brief	�|���g�f���@BMP�E�B���h�E���
 */
static void PoruDemo_BmpWinRelease(PORU_DEMO_WORK* wk)
{
	GF_BGL_BmpWinOff(&wk->win);
	GF_BGL_BmpWinDel(&wk->win);
}

/**
 *	@brief	�|���g�f���@���b�Z�[�W�}�l�[�W��������
 */
static void PoruDemo_MsgManagerGet(PORU_DEMO_WORK* wk)
{
	int i = 0;
	
	wk->msgMan = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
			NARC_msg_poruto_demo_dat,wk->heapID);
	
	wk->msgDat.wset = WORDSET_CreateEx(1,WORDSET_PORUDEMO_BUFLEN,wk->heapID);
	
	//�f�t�H���g������擾
	wk->msgDat.tmp = STRBUF_Create(WORDSET_PORUDEMO_BUFLEN,wk->heapID);

	for(i = 0;i < PORUD_MSG_NUM;i++){
		wk->msgDat.mbuf[i] = MSGMAN_AllocString(wk->msgMan,i);
	}
}

/**
 *	@brief	�|���g�f���@���b�Z�[�W�}�l�[�W�����
 */
static void PoruDemo_MsgManagerRelease(PORU_DEMO_WORK* wk)
{
	int i = 0;
	
	for(i = 0;i < PORUD_MSG_NUM;i++){
		STRBUF_Delete(wk->msgDat.mbuf[i]);
	}
	STRBUF_Delete(wk->msgDat.tmp);
	
	WORDSET_Delete(wk->msgDat.wset);
	MSGMAN_Delete(wk->msgMan);
}

/**
 *	@brief	�|���g�f���@�|�P�����p�����[�^�擾
 */
static void PoruDemo_PokeParaGet(PORU_DEMO_WORK* wk)
{
	wk->poke.pp = wk->param->pp;
	wk->poke.monsno = PokeParaGet(wk->param->pp,ID_PARA_monsno,NULL);
	wk->poke.sex = PokeSexGet(wk->param->pp);
	wk->poke.seikaku = PokeSeikakuGet(wk->param->pp);
	wk->poke.flip = PokePersonalParaGet( wk->poke.monsno, ID_PER_reverse ) ^ 1;

	wk->poke.name = STRBUF_Create(BUFLEN_POKEMON_NAME,wk->heapID);
	PokeParaGet(wk->param->pp,ID_PARA_nickname_buf,wk->poke.name);

	//�D�������擾
	wk->poke.favolite = PoruSys_IsFavolite(wk->param->poruto,wk->poke.seikaku);
}

/**
 *	@brief	�|���g�f���@�|�P�����p�����[�^���
 */
static void PoruDemo_PokeParaRelease(PORU_DEMO_WORK* wk)
{
	STRBUF_Delete(wk->poke.name);
}

/**
 *	@brief	�|���g�f���@�|���gOAM������
 */
static void PoruDemo_OamInit(PORU_DEMO_WORK* wk)
{
	initVramTransferManagerHeap(32,wk->heapID);

	//�Z���A�N�^�[�V�X�e��������
	wk->pActSys = CATS_AllocMemory(wk->heapID);

	{
		TCATS_OAM_INIT	coi = {
			0,128,		///< ���C��	OAM�Ǘ��̈�E�J�n/�I��
			0,31,		///< ���C��	�A�t�B���Ǘ��̈�E�J�n/�I��
			0,1,		///< �T�u	OAM�Ǘ��̈�E�J�n/�I��
			0,31,		///< �T�u	�A�t�B���Ǘ��̈�E�J�n/�I��
		};
		TCATS_CHAR_MANAGER_MAKE ccmm = {
			3,	//ID���䐔
			/*0x20*2048*/0,	//���C����ʃT�C�Y(byte�P��)
			0,		//�T�u��ʃT�C�Y(byte�P��)
			GX_OBJVRAMMODE_CHAR_1D_32K,	//���C��OBJ���[�h�w��
			GX_OBJVRAMMODE_CHAR_1D_32K,	//�T�uOBJ���[�h�w��
		};
		CATS_SystemInit( wk->pActSys, &coi, &ccmm, 32 );
		REND_OAM_UtilOamRamClear_Main(wk->heapID);
	}

	
	wk->oamMan = PoruOam_SysInit(wk->heapID,2,2,PORUOAM_DRAW_MAIN,PORUOAM_CGXOFS_AUTO);

	wk->pOam[0] = PoruOam_Add(wk->oamMan,wk->param->flavor,
		100,90,0,1,0,PORUOAM_VT_MAIN);

	//��U��\��
	CATS_ObjectEnableCap(wk->pOam[0]->act,FALSE);

	//�ʐM���Ȃ�ʐM�A�C�R���\��
	if(CommIsInitialize()){
		WirelessIconEasy();
	}

	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,VISIBLE_ON);
}

/**
 *	@brief	�|���g�f���@�|���gOAM���
 */
static void PoruDemo_OamRelease(PORU_DEMO_WORK* wk)
{
	PoruOam_Del(wk->oamMan,wk->pOam[0]);
	
	PoruOam_SysRelease(wk->oamMan);

	CATS_FreeMemory(wk->pActSys);
	DellVramTransferManager();	
}

//=============================================================
//����
//=============================================================
static int	PoruDemo_AnmMain(PORU_DEMO_WORK* wk)
{
#if 0
	if(sys.trg & PAD_BUTTON_START){
		return TRUE;	
	}
#endif
	switch(wk->seq){
	case ANMSEQ_PORUINIT:
		wk->seq = panm_PoruInit(wk,&wk->anm);
		break;
	case ANMSEQ_PORUWAIT:
		wk->seq = panm_PoruWait(wk,&wk->anm);
		break;
	case ANMSEQ_VOICESET:
		wk->seq = panm_PokeVoiceSet(wk,&wk->anm);
		break;
	case ANMSEQ_VOICEWAIT:
		wk->seq = panm_PokeVoiceWait(wk,&wk->anm);
		break;
	case ANMSEQ_REACTSET:
		wk->seq = panm_PokeReactionSet(wk,&wk->anm);
		break;
	case ANMSEQ_REACTWAIT:
		wk->seq = panm_PokeReactionWait(wk,&wk->anm);
		break;
	case ANMSEQ_MSGSET:
		wk->seq = panm_EatMsgSet(wk);
		break;
	case ANMSEQ_MSGWAIT:
		wk->seq = panm_EatMsgWait(wk);
		break;
	case ANMSEQ_END:
	default:
		wk->seq = 0;
		return TRUE;
	}
	return FALSE;
}

//=============================================================
//�A�j���V�[�P���X
//=============================================================
static void TPoruAnm01_00(TCB_PTR tcb,void* work);
static void TPoruAnm01_01(TCB_PTR tcb,void* work);
static void TPoruAnm02_00(TCB_PTR tcb,void* work);
static void TPoruAnm02_01(TCB_PTR tcb,void* work);

static void TPokeAnm01_00(TCB_PTR tcb,void* work);
static void TPokeAnm01_01(TCB_PTR tcb,void* work);
static void TPokeAnm02_00(TCB_PTR tcb,void* work);
static void TPokeAnm02_01(TCB_PTR tcb,void* work);
static void TPokeAnm02_02(TCB_PTR tcb,void* work);
static void TPokeAnm03_00(TCB_PTR tcb,void* work);
static void TPokeAnm03_01(TCB_PTR tcb,void* work);
static void TPokeAnm04_00(TCB_PTR tcb,void* work);
static void TPokeAnm04_01(TCB_PTR tcb,void* work);
static void TPokeAnm04_02(TCB_PTR tcb,void* work);
static void TPokeAnm05_00(TCB_PTR tcb,void* work);
static void TPokeAnm05_01(TCB_PTR tcb,void* work);
static void TPokeAnm06_00(TCB_PTR tcb,void* work);
static void TPokeAnm06_01(TCB_PTR tcb,void* work);

/**
 *	@brief	�^�X�N�o�^
 */
static int panm_TaskSet(PORUDEMO_ANM* wk,int idx,TCB_FUNC func)
{
	PORUDEMO_TASK* tp = &(wk->task[idx]);

	MI_CpuClear8(tp,sizeof(PORUDEMO_TASK));

	tp->prm = wk;	//�e�|�C���^�Q�b�g
	tp->tcb = TCB_Add(func,tp,0);

	wk->tnum++;
	return wk->tnum;
}
static int panm_TaskDel(PORUDEMO_TASK* tp)
{
	TCB_Delete(tp->tcb);
	tp->prm->tnum--;

	MI_CpuClear8(tp,sizeof(PORUDEMO_TASK));
	return  0;
}

/**
 *	@brief	�����X�e�[�^�X�Z�b�g
 */
static int panm_PoruInit(PORU_DEMO_WORK* wk,PORUDEMO_ANM* anm)
{
	VecFx32	tmp;
	MI_CpuClear8(anm,sizeof(PORUDEMO_ANM));
	
	//�A�N�^�[�|�C���^�擾
	anm->poruAct = wk->pOam[0]->act->act;
	//�X�v���C�g�|�C���^�擾
	anm->pokeAct = wk->p3d.ss;
	anm->favolite = wk->poke.favolite;

	//�^�C���Z�b�g
	anm->time = ANM_PORU_TIME;

	//�������W�Z�b�g
	anm->poru.sv.x = FX32_CONST(PRA_SX);
	anm->poru.sv.y = FX32_CONST(PRA_SY);
	anm->poru.ev.x = FX32_CONST(PRA_EX);
	anm->poru.ev.y = FX32_CONST(PRA_EY);
	anm->poru.asv.x =PRA_SAX;
	anm->poru.asv.y = PRA_SAY;
	anm->poru.aev.x = PRA_EAX;
	anm->poru.aev.y = PRA_EAY;


	anm->poru.time = ANM_PORU_TIME;
	anm->poru.frm = 0;

	//�����ʒu�Z�b�g
	CLACT_SetMatrix(anm->poruAct, &anm->poru.sv);
	VEC_Subtract(&anm->poru.sv,&anm->poru.ev,&tmp);
	Vec_Div(&anm->poru.adv,&tmp,FX32_CONST(ANM_PORU_TIME01));
	
	//�A�t�B���Z�b�g
	CLACT_SetAffineParam(anm->poruAct,CLACT_AFFINE_NORMAL);
	CLACT_SetScale(anm->poruAct,&anm->poru.asv);
	
	
	//�A�j���[�V�����^�X�N�o�^
	panm_TaskSet(anm,0,TPoruAnm01_00);
	panm_TaskSet(anm,1,TPoruAnm02_00);
	panm_TaskSet(anm,2,TPokeAnm01_00);
	panm_TaskSet(anm,3,TPokeAnm02_00);
	return ANMSEQ_PORUWAIT; 
}

/**
 *	@brief	�|���g�A�j���@�E�F�C�g
 */
static int panm_PoruWait(PORU_DEMO_WORK* wk,PORUDEMO_ANM* anm)
{
	int i,end_f = 0;

	if(anm->tnum){
		return ANMSEQ_PORUWAIT;
	}
	return ANMSEQ_VOICESET;
}

/**
 *	@brief	�|�P�����@�����Đ�
 */
static int panm_PokeVoiceSet(PORU_DEMO_WORK* wk,PORUDEMO_ANM* anm)
{
	switch(wk->poke.favolite){
	case PORU_FAVOLITE_KIRAI:
		Snd_PMVoicePlayEx( PV_PINCHNORMAL,wk->poke.monsno, 0, 127,wk->heapID);
		break;
	default:
		Snd_PMVoicePlayEx( PV_NORMAL,wk->poke.monsno, 0, 127,wk->heapID);
		break;
	}

	return ANMSEQ_VOICEWAIT;
}

/**
 *	@brief	�|�P���������Đ��E�F�C�g
 */
static int panm_PokeVoiceWait(PORU_DEMO_WORK* wk,PORUDEMO_ANM* anm)
{
	if(Snd_PMVoicePlayCheck()){
		return ANMSEQ_VOICEWAIT;
	}
	//��~����
	Snd_PMVoiceStop(0);
	return ANMSEQ_REACTSET;
}

/**
 *	@brief	�|���g�A�j���@���A�N�V�����Z�b�g
 */
static int panm_PokeReactionSet(PORU_DEMO_WORK* wk,PORUDEMO_ANM* anm)
{
	//�A�j���[�V�����^�X�N�o�^
	MI_CpuClear8(&anm->poke,sizeof(PORUDEMO_OBJ));
	panm_TaskSet(anm,0,TPokeAnm03_00);
	panm_TaskSet(anm,1,TPokeAnm04_00);
	return ANMSEQ_REACTWAIT;
}

/**
 *	@brief	�|���g�A�j���@���A�N�V�����E�F�C�g
 */
static int panm_PokeReactionWait(PORU_DEMO_WORK* wk,PORUDEMO_ANM* anm)
{
	if(anm->tnum){
		return ANMSEQ_REACTWAIT;
	}
	return ANMSEQ_MSGSET;
}

/**
 *	@brief	�|���g��H�ׂ��������b�Z�[�W�\��
 */
static int panm_EatMsgSet(PORU_DEMO_WORK* wk)
{
	BmpTalkWinWrite( &wk->win, WINDOW_TRANS_OFF, BMPL_TALK_WIN_CGX, BMPL_TALK_WIN_PAL);	
	GF_BGL_BmpWinDataFill(&wk->win,WINCLR_COL(FBMP_COL_WHITE));

	STRBUF_Clear(wk->msgDat.tmp);
	WORDSET_RegisterWord( wk->msgDat.wset,0,
			wk->poke.name,PM_NEUTRAL,TRUE,PM_LANG);
	WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,wk->msgDat.mbuf[wk->poke.favolite]);

	wk->msgIdx = GF_STR_PrintColor(
		&wk->win,FONT_TALK,wk->msgDat.tmp,
		0,0,wk->param->msg_spd,DEMO_TALK_FCOL,NULL);

	wk->counter = 0;
	return ANMSEQ_MSGWAIT;
}

/**
 *	@brief	�|���g��H�ׂ��������b�Z�[�W�\���҂�
 */
static int panm_EatMsgWait(PORU_DEMO_WORK* wk)
{
	if( GF_MSG_PrintEndCheck( wk->msgIdx )){
		return ANMSEQ_MSGWAIT;
	}
	if(	(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)) == 0 &&  
		(wk->counter++ < 90)){
		return ANMSEQ_MSGWAIT;
	}
	
	BmpTalkWinClear( &wk->win,WINDOW_TRANS_OFF);
	GF_BGL_BmpWinOff(&wk->win);

	return ANMSEQ_END;
}

//======================================================
//
//======================================================
/**
 *	@brief	�|���g�A�j���@�A�t�B��������
 */
static void TPoruAnm01_00(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	PORUDEMO_ANM* anm = tp->prm;
	PORUDEMO_OBJ*	poru = &anm->poru;
	VecFx32	tmp;


	tp->time = ANM_PORU_TIME;
	
	poru->asv.x =PRA_SAX;
	poru->asv.y = PRA_SAY;
	poru->aev.x = PRA_EAX;
	poru->aev.y = PRA_EAY;

	VEC_Subtract(&poru->asv,&poru->aev,&tmp);
	Vec_Div(&poru->adv,&tmp,FX32_CONST(tp->time));
	
	//�`��J�n
	CLACT_SetDrawFlag(anm->poruAct,TRUE);
	CLACT_SetAffineParam(anm->poruAct,CLACT_AFFINE_NORMAL);
	CLACT_SetScale(anm->poruAct,&poru->asv);

	TCB_ChangeFunc(tcb,TPoruAnm01_01);
}

/**
 *	@brief �|���g�A�j���@�A�t�B��	
 */
static void TPoruAnm01_01(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	PORUDEMO_ANM* anm = tp->prm;
	PORUDEMO_OBJ*	poru = &anm->poru;
	VecFx32	atmp = {0,0,0};

	//�X�P�[���l�X�V
	atmp.x = poru->asv.x-FX_Mul(poru->adv.x,tp->frm);
	atmp.y = poru->asv.y-FX_Mul(poru->adv.y,tp->frm);
	CLACT_SetScale(anm->poruAct,&atmp);

	tp->frm += FX32_ONE;
	tp->time--;
	if(tp->time == 0){
		CLACT_SetDrawFlag(anm->poruAct,FALSE);
		panm_TaskDel(tp);
	}
}

/**
 *	@brief�@�|���g�A�j���@�ړ�������
 */
static void TPoruAnm02_00(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	PORUDEMO_ANM* anm = tp->prm;
	PORUDEMO_OBJ*	poru = &anm->poru;
	VecFx32	tmp = {0,0,0};
	
	tp->time = ANM_PORU_TIME01;

	//�����ʒu�Z�b�g
	poru->sv.x = FX32_CONST(PRA_SX);
	poru->sv.y = FX32_CONST(PRA_SY);
	poru->ev.x = FX32_CONST(PRA_EX);
	poru->ev.y = FX32_CONST(PRA_EY);
	
	VEC_Subtract(&poru->ev,&poru->sv,&tmp);
	Vec_Div(&poru->dv,&tmp,FX32_CONST(tp->time));

	poru->r = FX_Div(FX32_CONST(180),FX32_CONST(tp->time));
	poru->df = FX_Div(FX32_CONST(1),FX32_CONST(tp->time));

	CLACT_SetMatrix(anm->poruAct, &poru->sv);
	
	TCB_ChangeFunc(tcb,TPoruAnm02_01);
}

/**
 *	@brief	�|���g�A�j���@�ړ��P
 */
static void TPoruAnm02_01(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	PORUDEMO_ANM* anm = tp->prm;
	PORUDEMO_OBJ*	poru = &anm->poru;
	VecFx32	tmp;
	fx32	dy,per;

	//�ړ��l�X�V
	tmp.x = poru->sv.x+FX_Mul(poru->dv.x,tp->frm);
	tmp.y = poru->sv.y+FX_Mul(poru->dv.y,tp->frm);
	
	//�I�t�Z�b�g�Z�o
	dy = FX_Mul(poru->r,tp->frm);
	dy = FX_Mul(Sin360R(dy>>12),FX32_CONST(-64));
//	per = FX_Mul(poru->df,tp->frm);
	per = FX32_ONE;
	tmp.y += FX_Mul(dy,per);
	
	CLACT_SetMatrix(anm->poruAct, &tmp);

	tp->frm += FX32_ONE;
	tp->time--;
	if(tp->time){
		return;
	}
	panm_TaskDel(tp);
}

/**
 *	@brief	�|�P���� �A�t�B�����쏉����
 */
static void TPokeAnm01_00(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	PORUDEMO_ANM* anm = tp->prm;
	PORUDEMO_OBJ*	poke = &anm->poke;
	VecFx32	tmp;

	tp->time = ANM_PORU_TIME;
	
	poke->asv.x = PKA_SAX;
	poke->asv.y = PKA_SAY;
	poke->aev.x = PKA_EAX;
	poke->aev.y = PKA_EAY;

	VEC_Subtract(&poke->aev,&poke->asv,&tmp);
	Vec_Div(&poke->adv,&tmp,FX32_CONST(tp->time));
	
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_AFF_X,PKA_SAX>>4);
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_AFF_Y,PKA_SAY>>4);
	TCB_ChangeFunc(tcb,TPokeAnm01_01);
}

/**
 *	@brief	�|�P�������� �A�t�B��
 */
static void TPokeAnm01_01(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	PORUDEMO_ANM* anm = tp->prm;
	PORUDEMO_OBJ*	poke = &anm->poke;
	VecFx32	tmp;

	//�X�P�[���l�X�V
	tmp.x = poke->asv.x+FX_Mul(poke->adv.x,tp->frm);
	tmp.y = poke->asv.y+FX_Mul(poke->adv.y,tp->frm);
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_AFF_X,tmp.x >> 4);
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_AFF_Y,tmp.y >> 4);

	tp->frm += FX32_ONE;
	tp->time--;
	if(tp->time == 0){
		SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_X,PKA_SX);
		SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_Y,PKA_SY);
		panm_TaskDel(tp);
	}
}

/**
 *	@brief	�|�P��������@�W�����v���Ȃ���߂Â�������
 */
static void TPokeAnm02_00(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	PORUDEMO_ANM* anm = tp->prm;
	PORUDEMO_OBJ*	poke = &anm->poke;
	VecFx32	tmp;

	tp->time = ANM_PORU_TIME;
	
	poke->sv.x = FX32_CONST(PKA_SX);
	poke->sv.y = FX32_CONST(PKA_SY);
	poke->ev.x = FX32_CONST(PKA_EX);
	poke->ev.y = FX32_CONST(PKA_EY);
	
	VEC_Subtract(&poke->ev,&poke->sv,&tmp);
	Vec_Div(&poke->dv,&tmp,FX32_CONST(tp->time));
	
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_X,poke->sv.x>>12);
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_Y,poke->sv.y>>12);
	TCB_ChangeFunc(tcb,TPokeAnm02_01);
}

/**
 *	@brief	�|�P��������@�W�����v���Ȃ���߂Â�
 */
static void TPokeAnm02_01(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	PORUDEMO_ANM* anm = tp->prm;
	PORUDEMO_OBJ*	poke = &anm->poke;
	VecFx32	tmp;
	fx32	dy;
	int	kx;
	
	tmp.x = poke->sv.x+FX_Mul(poke->dv.x,tp->frm);
	tmp.y = poke->sv.y+FX_Mul(poke->dv.y,tp->frm);
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_X,tmp.x>>12);
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_Y,tmp.y>>12);

	kx = poke->ct01-4;
	kx = -(kx*kx)+16;
	dy = FX32_CONST(-kx);
	dy = FX_Mul(dy,FX32_CONST(1.4));
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_OY,dy>>12);

	poke->ct01++;
	if(poke->ct01 > 8){
		poke->ct01 = 0;
	}	
	tp->frm += FX32_ONE;
	if(tp->time--){
		return;
	}
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_OY,0);
	poke->ct01 = 0;

	TCB_ChangeFunc(tcb,TPokeAnm02_02);
}

static void TPokeAnm02_02(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	PORUDEMO_ANM* anm = tp->prm;
	PORUDEMO_OBJ*	poke = &anm->poke;
	
	if(poke->ct01++ < PKA_TIME_WAIT){
		return;
	}
	panm_TaskDel(tp);
}
/**
 *	@brief	�|�P��������@���̑傫���ɖ߂�������
 */
static void TPokeAnm03_00(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	PORUDEMO_ANM* anm = tp->prm;
	PORUDEMO_OBJ*	poke = &anm->poke;
	VecFx32	tmp;

	tp->time = ANM_PORU_TIME/3;
	
	poke->asv.x = PKA_EAX;
	poke->asv.y = PKA_EAY;
	poke->aev.x = PKA_SAX;
	poke->aev.y = PKA_SAY;

	VEC_Subtract(&poke->aev,&poke->asv,&tmp);
	Vec_Div(&poke->adv,&tmp,FX32_CONST(tp->time));
	
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_AFF_X,PKA_EAX>>4);
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_AFF_Y,PKA_EAY>>4);
	TCB_ChangeFunc(tcb,TPokeAnm03_01);
}

/**
 *	@brief	�|�P�������� �A�t�B�����ɖ߂�
 */
static void TPokeAnm03_01(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	PORUDEMO_ANM* anm = tp->prm;
	PORUDEMO_OBJ*	poke = &anm->poke;
	VecFx32	tmp;

	//�X�P�[���l�X�V
	tmp.x = poke->asv.x+FX_Mul(poke->adv.x,tp->frm);
	tmp.y = poke->asv.y+FX_Mul(poke->adv.y,tp->frm);
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_AFF_X,tmp.x >> 4);
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_AFF_Y,tmp.y >> 4);

	tp->frm += FX32_ONE;
	tp->time--;
	if(tp->time){
		return;
	}
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_AFF_X,0x0100);
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_AFF_Y,0x0100);
	panm_TaskDel(tp);
}

/**
 *	@brief	�|�P��������@�����֖߂�������
 */
static void TPokeAnm04_00(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	PORUDEMO_ANM* anm = tp->prm;
	PORUDEMO_OBJ*	poke = &anm->poke;
	VecFx32	tmp;

	tp->time = ANM_PORU_TIME/3;
	
	poke->sv.x = FX32_CONST(PKA_EX);
	poke->sv.y = FX32_CONST(PKA_EY);
	poke->ev.x = FX32_CONST(PKA_SX);
	poke->ev.y = FX32_CONST(PKA_SY2);
	
	VEC_Subtract(&poke->ev,&poke->sv,&tmp);
	Vec_Div(&poke->dv,&tmp,FX32_CONST(tp->time));

	poke->r = FX_Div(FX32_CONST(180),FX32_CONST(tp->time));
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_X,poke->sv.x>>12);
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_Y,poke->sv.y>>12);
	TCB_ChangeFunc(tcb,TPokeAnm04_01);
}

/**
 *	@brief	�|�P��������@�����֖߂�@
 */
static void TPokeAnm04_01(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	PORUDEMO_ANM* anm = tp->prm;
	PORUDEMO_OBJ*	poke = &anm->poke;
	VecFx32	tmp;
	fx32	dy;
	int	kx;
	
	tmp.x = poke->sv.x+FX_Mul(poke->dv.x,tp->frm);
	tmp.y = poke->sv.y+FX_Mul(poke->dv.y,tp->frm);
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_X,tmp.x>>12);
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_Y,tmp.y>>12);

	dy = FX_Mul(poke->r,tp->frm);
	dy = FX_Mul(Sin360R(dy>>12),FX32_CONST(-6));
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_OY,dy>>12);
	
	tp->frm += FX32_ONE;
	tp->time--;

	if(tp->time){
		return;
	}
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_OY,0);

	TCB_ChangeFunc(tcb,TPokeAnm04_02);
}

/**
 *	@brief	�|�P��������@�����֖߂�E�F�C�g
 */
static void TPokeAnm04_02(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	
	if(tp->time++ < PKA_TIME_WAIT){
		return;
	}

	//���A�N�V������
	switch(tp->prm->favolite){
	case PORU_FAVOLITE_SUKI:
		TCB_ChangeFunc(tcb,TPokeAnm05_00);
		break;
	case PORU_FAVOLITE_KIRAI:
		TCB_ChangeFunc(tcb,TPokeAnm06_00);
		break;
	default:
		panm_TaskDel(tp);
		break;
	}
}

/**
 *	@brief	�|�P��������@��ԏ�����
 */
static void TPokeAnm05_00(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	PORUDEMO_ANM* anm = tp->prm;
	PORUDEMO_OBJ*	poke = &anm->poke;
	VecFx32	tmp;

	MI_CpuClear8(poke,sizeof(PORUDEMO_OBJ));
	tp->time = 3;
	TCB_ChangeFunc(tcb,TPokeAnm05_01);
}

/**
 *	@brief	�|�P��������@���
 */
static void TPokeAnm05_01(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	PORUDEMO_ANM* anm = tp->prm;
	PORUDEMO_OBJ*	poke = &anm->poke;
	VecFx32	tmp;
	fx32	dy,x;
	int	kx;

	kx = poke->ct01-4;
	kx = -(kx*kx)+16;
	dy = FX32_CONST(-kx);
	dy = FX_Mul(dy,FX32_CONST(1.4));
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_OY,dy>>12);

	poke->ct02 = 0;
	poke->ct01++;
	if(poke->ct01 > 8){
		poke->ct01 = 0;
		tp->time--;
	}

	if(tp->time == 0){
		SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_OY,0);
		panm_TaskDel(tp);
	}
}

/**
 *	@brief	�|�P��������@�����鏉����
 */
static void TPokeAnm06_00(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	PORUDEMO_ANM* anm = tp->prm;
	PORUDEMO_OBJ*	poke = &anm->poke;
	VecFx32	tmp;

	MI_CpuClear8(poke,sizeof(PORUDEMO_OBJ));
	tp->time = 32;

	TCB_ChangeFunc(tcb,TPokeAnm06_01);
}

/**
 *	@brief	�|�P��������@������
 */
static void TPokeAnm06_01(TCB_PTR tcb,void* work)
{
	PORUDEMO_TASK* tp = (PORUDEMO_TASK*)work;
	PORUDEMO_ANM* anm = tp->prm;
	PORUDEMO_OBJ*	poke = &anm->poke;
	VecFx32	tmp;
	fx32	rot,dx;

	rot = Sin360R(poke->ct01);
	dx = FX_Mul(rot,FX32_CONST(2));
	if(poke->ct01 > 359){
		poke->ct01 = 0;
	}else{
		poke->ct01 += 90;
	}
	SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_OX,dx>>12);
	
	tp->time--;
	if(tp->time == 0){
		SoftSpriteParaSet( anm->pokeAct, SS_PARA_POS_OX,0);
		panm_TaskDel(tp);
	}
}
