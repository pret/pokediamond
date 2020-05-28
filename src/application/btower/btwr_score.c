/**
 *	@file	btwr_score.c
 *	@brief	�o�g���^���[���у��j�^
 *	
 */

#include "common.h"
#include "system/procsys.h"
#include "system/arc_util.h"
#include "system/arc_tool.h"
#include "system/brightness.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/window.h"
#include "system/pm_str.h"
#include "system/msgdata.h"
#include "system/fontproc.h"
#include "system/snd_tool.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/render_oam.h"
#include "system/wipe.h"
#include "system/wordset.h"
#include "system/buflen.h"
#include "gflib/msg_print.h"
#include "gflib/strbuf_family.h"
#include "application/app_tool.h"
#include "application/pms_input.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_btower_app.h"

#include "application/pms_input.h"
#include "application/btwr_app.h"
//#include "savedata/savedata_def.h"
#include "savedata/config.h"
#include "savedata/b_tower.h"
#include "savedata/record.h"

#include "system/gamedata.h"
#include "battle/battle_common.h"
#include "battle/b_tower_data.h"

#include "btower.naix"

#define BTOWER_APP_ACTRES_MAX	(1)
#define ACT_CUR_PALT		(0)
#define ACT_CUR_PALF		(1)

enum{
 ACT_CURSOR,
 ACT_RET,
 ACT_UP,
 ACT_DOWN,
 ACT_MAX,
};

#define ACT_CUR_PX	(54)
#define ACT_CUR_PY	(68)
#define ACT_RET_PX	(204)
#define ACT_RET_PY	(114)
#define ACT_RET_SX	(40)
#define ACT_RET_HSX	(20)
#define ACT_UP_PX	(128)
#define ACT_UP_PY	(52)
#define ACT_DOWN_PX	(128)
#define ACT_DOWN_PY	(132)

#define LIST_SIDE_WIDTH	(72)
#define LINE_RET		(10)
#define LINE_SCR_MAX	(LINE_RET-2)

#define FCOLS_BLACK	(GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL))
#define FCOLS_WHITE	(GF_PRINTCOLOR_MAKE(FBMP_COL_WHITE,FBMP_COL_BLK_SDW,FBMP_COL_NULL))
#define FCOL_BLUE	(GF_PRINTCOLOR_MAKE(FBMP_COL_WHITE,FBMP_COL_BLK_SDW,FBMP_COL_NULL))
#define FCOL_RED	(GF_PRINTCOLOR_MAKE(FBMP_COL_WHITE,FBMP_COL_BLK_SDW,FBMP_COL_NULL))
#define FCOLA_BLACK	(GF_PRINTCOLOR_MAKE(1,2,FBMP_COL_NULL))
#define FCOLA_WHITE	(GF_PRINTCOLOR_MAKE(3,4,FBMP_COL_NULL))
#define FCOLA_ORANGE (GF_PRINTCOLOR_MAKE(5,6,FBMP_COL_NULL))
#define FCOLA_GRAY (GF_PRINTCOLOR_MAKE(7,8,FBMP_COL_NULL))
#define FCOLA_BLUE	(GF_PRINTCOLOR_MAKE(9,10,FBMP_COL_NULL))
#define FCOLA_RED	(GF_PRINTCOLOR_MAKE(11,12,FBMP_COL_NULL))

#define FONT_APP_PAL	(1)
#define FONT_SYS_PAL	(2)

#define BMPCHAR_BASE01	(192)
#define BMPCHAR_BASE02	(1)

#define WORDSET_BTOWER_APP_BUFLEN	((18+1)*4)

//120
#define BMPL_TITLE_PX	(4)
#define BMPL_TITLE_PY	(1)
#define BMPL_TITLE_SX	(24)
#define BMPL_TITLE_SY	(5)
#define BMPL_TITLE_CGX_NUM	(BMPL_TITLE_SX*BMPL_TITLE_SY)
#define BMPL_TITLE_CGX	(BMPCHAR_BASE01)
#define BMPL_TITLE_FRM	(GF_BGL_FRAME0_M)
#define BMPL_TITLE_PAL	(FONT_SYS_PAL)

//40
#define BMPL_ST01_PX	(1)
#define BMPL_ST01_PY	(9)
#define BMPL_ST01_SX	(8)
#define BMPL_ST01_SY	(5)
#define BMPL_ST01_CGX_NUM	(BMPL_ST01_SX*BMPL_ST01_SY)
#define BMPL_ST01_CGX	(BMPCHAR_BASE01+BMPL_TITLE_CGX_NUM)
#define BMPL_ST01_FRM	(GF_BGL_FRAME0_M)
#define BMPL_ST01_PAL	(FONT_APP_PAL)
//40
#define BMPL_ST02_PX	(1)
#define BMPL_ST02_PY	(17)
#define BMPL_ST02_SX	(8)
#define BMPL_ST02_SY	(5)
#define BMPL_ST02_CGX_NUM	(BMPL_ST02_SX*BMPL_ST02_SY)
#define BMPL_ST02_CGX	(BMPL_ST01_CGX+BMPL_ST01_CGX_NUM)
#define BMPL_ST02_FRM	(GF_BGL_FRAME0_M)
#define BMPL_ST02_PAL	(FONT_APP_PAL)

//105
#define BMPL_REC01_PX	(10)
#define BMPL_REC01_PY	(9)
#define BMPL_REC01_SX	(21)
#define BMPL_REC01_SY	(5)
#define BMPL_REC01_CGX_NUM	(BMPL_REC01_SX*BMPL_REC01_SY)
#define BMPL_REC01_CGX	(BMPL_ST02_CGX+BMPL_ST02_CGX_NUM)
#define BMPL_REC01_FRM	(GF_BGL_FRAME0_M)
#define BMPL_REC01_PAL	(FONT_APP_PAL)
//105
#define BMPL_REC02_PX	(10)
#define BMPL_REC02_PY	(17)
#define BMPL_REC02_SX	(21)
#define BMPL_REC02_SY	(5)
#define BMPL_REC02_CGX_NUM	(BMPL_REC02_SX*BMPL_REC02_SY)
#define BMPL_REC02_CGX	(BMPL_REC01_CGX+BMPL_REC01_CGX_NUM)
#define BMPL_REC02_FRM	(GF_BGL_FRAME0_M)
#define BMPL_REC02_PAL	(FONT_APP_PAL)

//
#define BMPL_NAME_PX	(3)
#define BMPL_NAME_PY	(7)
#define BMPL_NAME_SX	(26)
#define BMPL_NAME_SY	(9)
#define BMPL_NAME_CGX_NUM	(BMPL_NAME_SX*BMPL_NAME_SY)
#define BMPL_NAME_CGX	(BMPCHAR_BASE02)
#define BMPL_NAME_FRM	(GF_BGL_FRAME2_M)
#define BMPL_NAME_PAL	(FONT_APP_PAL)

//
#define BMPL_TALK_PX	(3)
#define BMPL_TALK_PY	(18)
#define BMPL_TALK_SX	(26)
#define BMPL_TALK_SY	(5)
#define BMPL_TALK_CGX_NUM	(BMPL_TALK_SX*BMPL_TALK_SY)
#define BMPL_TALK_CGX	(BMPCHAR_BASE01+BMPL_TITLE_CGX_NUM)
#define BMPL_TALK_FRM	(GF_BGL_FRAME0_M)
#define BMPL_TALK_PAL	(FONT_SYS_PAL)

enum{
 WINS_TITLE,
 WINS_ST01,
 WINS_ST02,
 WINS_REC01,
 WINS_REC02,
 WINS_MAX
};

enum{
 WINL_TITLE,
 WINL_NAME,
 WINL_TALK,
 WINL_MAX,
};

typedef struct _APP_MSG{
	MSGDATA_MANAGER*	pMan;

	WORDSET* wset;	//���[�N
	STRBUF*	tmp;	//�ėp
	STRBUF* ebuf;	//���ǂ�
	STRBUF* tbuf;	//�^�C�g��
	STRBUF*	nbuf;	//���O
	STRBUF*	a1buf;	//�n��(�����ƒn�於)
	STRBUF*	a2buf;	//�n��(�����̂�)
	STRBUF*	cbuf;	//�n��NG�R�[�h
	STRBUF*	rbuf[6];
	STRBUF*	def_name[2];	///<�f�t�H���g�l�[���W�J
}APP_MSG;

//���[�_�[�f�[�^
typedef struct _LEADER_DATA{
	STRBUF*	name;	//���O
	u8		sex;	//����
	u8		country;	//���R�[�h
	u8		area;		//�n��R�[�h
	u8		ngname_f;	//NG�l�[���t���O
	PMS_DATA	msg;		//�ȈՉ�b���b�Z�[�W
}LEADER_DATA;

typedef struct _BTOWER_APP_WORK{
	int	heapID;
	int	seq;
	u16	mainMode;
	u8	subMode;

	u8	line;
	u8	side;
	u8	state;
	u8	upLine;
	u8	viewLine;

	GF_BGL_INI			*bgl;
	BTOWER_APP_PARAM	*param;
	CONFIG				*configSave;
	RECORD				*recordSave;
	BTLTOWER_SCOREWORK	*scoreSave;
	BTLTOWER_WIFI_DATA	*wifiSave;

	///���b�Z�[�W���\�[�X
	APP_MSG			msgDat;
	GF_BGL_BMPWIN	win[WINS_MAX];	///<BMP�E�B���h�E�f�[�^

	//���[�_�[�f�[�^
	LEADER_DATA		leader[BTOWER_STOCK_WIFI_LEADER_MAX];

	CATS_SYS_PTR	pActSys;	///<�Z���A�N�^�[�V�X�e��
	CATS_RES_PTR	pActRes;	///<�Z���A�N�^�[���\�[�X
	CLACT_WORK_PTR	pAct[ACT_MAX];		///<�A�N�g
}BTOWER_APP_WORK;

//=========================================================
//�T�u�v���Z�X�v���g�^�C�v
//=========================================================
static int BTowerApp_InitCommon(BTOWER_APP_WORK* wk);
static int BTowerApp_ReleaseCommon(BTOWER_APP_WORK* wk);

static void BTowerAppVramBankSet(void);
static void BTowerAppVBlank(void * work);
static int BTowerApp_KeyInScore(BTOWER_APP_WORK* wk);
static int BTowerApp_KeyInLeader(BTOWER_APP_WORK* wk);
static void BTowerAppBGLInit(BTOWER_APP_WORK* wk);
static void BTowerAppBGLRelease(BTOWER_APP_WORK* wk);
static void BTowerApp_2DGraInit(BTOWER_APP_WORK* wk);
static void BTowerApp_BmpWinAdd(BTOWER_APP_WORK* wk);
static void BTowerApp_BmpWinRelease(BTOWER_APP_WORK* wk);
static void BTowerApp_MsgManagerGet(BTOWER_APP_WORK* wk);
static void BTowerApp_MsgManagerRelease(BTOWER_APP_WORK* wk);
static void BTowerApp_MsgWriteScore(BTOWER_APP_WORK* wk);
static void BTowerApp_GetLeaderData(BTOWER_APP_WORK* wk);
static void BTowerApp_ReleaseLeaderData(BTOWER_APP_WORK* wk);

static void BTowerApp_MsgWriteLeader(BTOWER_APP_WORK* wk);
static void BTowerApp_WritePlayerList(LEADER_DATA* leader,
		GF_BGL_BMPWIN* win,STRBUF* retBuf,u8 up,u8 line,u8 side);
static void BTowerApp_PlayerAreaMsgWrite(BTOWER_APP_WORK* wk);
static void BTowerApp_PlayerMsgWrite(BTOWER_APP_WORK* wk);
static void BTowerApp_PlayerMsgClear(BTOWER_APP_WORK* wk);


static void BTowerApp_ActorInit(BTOWER_APP_WORK *wk);
static void BTowerApp_ActorRelease(BTOWER_APP_WORK *wk);
static void BTowerApp_ActorMain(BTOWER_APP_WORK *wk);
static void BTowerApp_ActorTrans(void);
static void BTowerApp_MakeLeaderViewAct(BTOWER_APP_WORK* wk);
static void BTowerApp_DelLeaderViewAct(BTOWER_APP_WORK* wk);
static void Act_CursorChg(BTOWER_APP_WORK* wk,BOOL mode);
static void Act_CursorPosSet(BTOWER_APP_WORK* wk,u8 line,u8 side,u8 viewLine);


//--------------------------------------------------
///�v���O�����G���A
//----------------------------------------------------------------
/**
 *	@brief	�o�g���^���[�A�v�� �v���Z�X������
 *	@param	proc	�v���Z�X�f�[�^
 *	@param	seq		�V�[�P���X
 *
 *	@return	������
 */
PROC_RESULT BTowerAppProc_Init( PROC *proc,int *seq)
{
	BTOWER_APP_WORK *wk = NULL;
	BTOWER_APP_PARAM * sp;
	
	sp = (BTOWER_APP_PARAM*)PROC_GetParentWork(proc);

	//���[�N�G���A�擾
	HeapStatePush();

	//�q�[�v�쐬
	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_BTOWER_APP,0x10000);
	
	wk = PROC_AllocWork( proc,sizeof(BTOWER_APP_WORK),HEAPID_BTOWER_APP);
	memset(wk,0,sizeof(BTOWER_APP_WORK));
	
	//�p�����[�^���p��
	wk->mainMode = sp->mainMode;
	wk->subMode = sp->subMode;
	wk->configSave = SaveData_GetConfig(sp->save);
	wk->recordSave = SaveData_GetRecord(sp->save);
	wk->scoreSave = SaveData_GetTowerScoreData(sp->save);
	wk->wifiSave = SaveData_GetTowerWifiData(sp->save);
//	wk->param.msg_spd		= CONFIG_GetMsgSpeed(sp);
//	wk->param.win_type		= CONFIG_GetWindowType(sp);
	
	wk->heapID = HEAPID_BTOWER_APP;

	return PROC_RES_FINISH;
}

/**
 *	@brief	�^���[�A�v�� �v���Z�X�I��
 *	@param	proc	�v���Z�X�f�[�^
 *	@param	seq		�V�[�P���X
 *
 *	@return	������
 */
PROC_RESULT BTowerAppProc_End( PROC *proc,int *seq)
{
	BTOWER_APP_WORK* wk = PROC_GetWork(proc);

	//���[�N�G���A���
	PROC_FreeWork(proc);

	HeapStatePop();
	HeapStateCheck(wk->heapID);
	sys_DeleteHeap(wk->heapID);

	return PROC_RES_FINISH;
}


/***
 *	@brief	�^���[�A�v���@���C���v���Z�X
 */
PROC_RESULT	BTowerAppProc_Main( PROC *proc,int* seq)
{
	int end_f = 0;
	BTOWER_APP_WORK* wk = PROC_GetWork(proc);	

	switch(*seq){
	case 0:
		if(!BTowerApp_InitCommon(wk)){
			break;
		}
		WIPE_SYS_Start(WIPE_PATTERN_M,
				WIPE_TYPE_FADEIN,
				WIPE_TYPE_FADEIN,0x0000,COMM_BRIGHTNESS_SYNC,1,wk->heapID
				);
		(*seq)++;
		break;
	case 1:
		if(!WIPE_SYS_EndCheck()){
			break;
		}
		(*seq)++;
		break;
	case 2:
		if(wk->mainMode==0){
			end_f = BTowerApp_KeyInScore(wk);
		}else{
			end_f = BTowerApp_KeyInLeader(wk);
		}
		if(!end_f){
			break;
		}
		WIPE_SYS_Start(WIPE_PATTERN_M,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,0x0000,COMM_BRIGHTNESS_SYNC,1,wk->heapID
				);
		(*seq)++;
		break;
	case 3:
		if(!WIPE_SYS_EndCheck()){
			break;
		}
		(*seq)++;
		break;
	case 4:
		if(!BTowerApp_ReleaseCommon(wk)){
			break;
		}
		return PROC_RES_FINISH;
	}
	if(*seq >= 1 && 3 >= *seq ){
		BTowerApp_ActorMain(wk);
	}
	return PROC_RES_CONTINUE;
}

/**
 *	@brief	��ʏ�����
 */
static int BTowerApp_InitCommon(BTOWER_APP_WORK* wk)
{
	switch(wk->seq){
	case 0:
		sys_VBlankFuncChange(NULL,NULL);	
		sys_HBlankIntrStop();
	
		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane(0);
		GXS_SetVisiblePlane(0);

		//Bank�Z�b�g
		BTowerAppVramBankSet();
		WIPE_ResetWndMask(WIPE_DISP_MAIN);
		WIPE_ResetWndMask(WIPE_DISP_SUB);

		//BGL�Z�b�g
		BTowerAppBGLInit(wk);
		break;
	case 1:
		//2D���\�[�X�擾
		BTowerApp_2DGraInit(wk);
		//���b�Z�[�W���\�[�X�擾
		BTowerApp_MsgManagerGet(wk);
		break;
	case 2:
		//Bmp�E�B���h�E�擾
		BTowerApp_BmpWinAdd(wk);
		if(wk->mainMode == 0){
			//���b�Z�[�W�����`��
			BTowerApp_MsgWriteScore(wk);
			wk->seq++;	//�A�N�^�[�쐬�͔�΂�
		}else{
			//���[�_�[�f�[�^�擾
			BTowerApp_GetLeaderData(wk);
			//�������b�Z�[�W�`��
			BTowerApp_MsgWriteLeader(wk);
		}
		break;
	case 3:
		//�A�N�^�[������
		BTowerApp_ActorInit(wk);
		BTowerApp_MakeLeaderViewAct(wk);
		break;
	case 4:
		sys_VBlankFuncChange(BTowerAppVBlank,wk);	
		wk->seq = 0;
		return TRUE;
	}
	wk->seq++;
	return FALSE;
}

/**
 *	@brief	��ʉ��
 */
static int BTowerApp_ReleaseCommon(BTOWER_APP_WORK* wk)
{
	switch(wk->seq){
	case 0:
		//�A�N�^�[���
		if(wk->mainMode){
			BTowerApp_DelLeaderViewAct(wk);
			BTowerApp_ActorRelease(wk);
			BTowerApp_ReleaseLeaderData(wk);
		}
		//Bmp�E�B���h�E���
		BTowerApp_BmpWinRelease(wk);
		//���b�Z�[�W���\�[�X���
		BTowerApp_MsgManagerRelease(wk);
		//2D���\�[�X���
		BTowerAppBGLRelease(wk);
		break;
	case 1:
		sys_VBlankFuncChange(NULL,NULL);	
		sys_HBlankIntrStop();
	
		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane(0);
		GXS_SetVisiblePlane(0);
		wk->seq = 0;
		return TRUE;
	}
	wk->seq++;
	return FALSE;
}

/**
 *	@brief	�^���[�A�v�����VramBank�Z�b�g
 */
static void BTowerAppVramBankSet(void)
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
 *	@brief	�^���[�A�v�����VBlank
 */
static void BTowerAppVBlank(void * work)
{
	BTOWER_APP_WORK* wk = work;
	
	BTowerApp_ActorTrans();

	NNS_GfdDoVramTransfer();	//VRam�]���}�l�[�W�����s
//	CLACT_VBlankSys();	//OAM�}�l�[�W�����Z�b�g
	GF_BGL_VBlankFunc( wk->bgl );
	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

/**
 *	@brief	�L�[�擾
 */
static int BTowerApp_KeyInScore(BTOWER_APP_WORK* wk)
{
	if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
		return TRUE;
	}
	return FALSE;
}

static inline u8 line_up(BTOWER_APP_WORK* wk)
{
	if(wk->line == 0){
		return 0;
	}
	--wk->line;
	if(wk->viewLine == 0){
		--wk->upLine;
		return 1;
	}
	--wk->viewLine;
	return 1;
}

static inline u8 line_down(BTOWER_APP_WORK* wk)
{
	if(wk->line >= LINE_RET){
		return 0;
	}
	++wk->line;
	if(wk->viewLine > 1){
		++wk->upLine;
		return 1;
	}
	++wk->viewLine;
	return 1;
}

//�ʏ��ԃL�[�擾
static int leader_KeyInNormal(BTOWER_APP_WORK *wk)
{
	int update = 0;
	if(sys.trg & PAD_BUTTON_CANCEL){
		return TRUE;
	}
	if(sys.trg & PAD_BUTTON_DECIDE){
		if(wk->line >= LINE_RET){
			return TRUE;
		}
		//�I�����ꂽ
		wk->state++;
		BTowerApp_PlayerAreaMsgWrite(wk);
		return FALSE;
	}

	if(sys.trg & PAD_KEY_UP){
		update = line_up(wk);
	}else if(sys.trg & PAD_KEY_DOWN){
		update = line_down(wk);
	}else if(sys.trg & PAD_KEY_LEFT){
		wk->side = (wk->side+2)%3;
		update = 1;
	}else if(sys.trg & PAD_KEY_RIGHT){
		wk->side = (wk->side + 1)%3;
		update = 1;
	}
	if(wk->line == LINE_RET){
		wk->side = 2;	//����
	}

	if(!update){
		return FALSE;
	}
	//�J�[�\���y�у��X�g�X�V
	Act_CursorPosSet(wk,wk->line,wk->side,wk->viewLine);
	BTowerApp_WritePlayerList(wk->leader,&wk->win[WINL_NAME],
			wk->msgDat.ebuf,wk->upLine,wk->line,wk->side);
	return FALSE;
}

static int leader_KeyInArea(BTOWER_APP_WORK* wk)
{
	if(sys.trg & PAD_BUTTON_DECIDE){
		BTowerApp_PlayerMsgWrite(wk);
		++wk->state;
	}else if(sys.trg & PAD_BUTTON_CANCEL){
		BTowerApp_PlayerMsgClear(wk);
		wk->state = 0;
	}
	return FALSE;
}

static int leader_KeyInMsg(BTOWER_APP_WORK* wk)
{
	if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
		BTowerApp_PlayerMsgClear(wk);
		wk->state = 0;
	}
	return FALSE;
}

/**
 *	@brief	�L�[�擾
 */
static int BTowerApp_KeyInLeader(BTOWER_APP_WORK* wk)	
{
	switch(wk->state){
	case 0:	//�m�[�}��
		return leader_KeyInNormal(wk);
	case 1:	//�G���A�`��
		return leader_KeyInArea(wk);
	case 2:	//���b�Z�[�W�`��
		return leader_KeyInMsg(wk);
	}
	return FALSE;
}

/**
 *	@brief	�^���[���BGL�V�X�e��������
 */
static void BTowerAppBGLInit(BTOWER_APP_WORK* wk)
{
	int i,frame;

	wk->bgl = GF_BGL_BglIniAlloc(wk->heapID);

	{	//BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0,GX_BG0_AS_2D
		};
		GF_BGL_InitBG(&BGsys_data);
	}
	
	{
	GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
		{	//MAIN BG0 �ŏ�ʃe�L�X�g��
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			0,0,0,FALSE},
		{	//MAIN BG1 ���BG��
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			1,0,0,FALSE},
		{	//MAIN BG2 ���ʃe�L�X�g��
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800,GX_BG_CHARBASE_0x10000,GX_BG_EXTPLTT_01,
			2,0,0,FALSE},
	};
		frame = GF_BGL_FRAME0_M;
		for(i = 0;i < 2+wk->mainMode;i++){
			GF_BGL_BGControlSet(wk->bgl,frame,&(TextBgCntDat[i]),GF_BGL_MODE_TEXT);
			GF_BGL_ScrClear(wk->bgl,frame);
			frame++;
		}
	}
	GF_BGL_ClearCharSet(GF_BGL_FRAME0_M,32,0,wk->heapID);
	if(wk->mainMode){
		GF_BGL_ClearCharSet(GF_BGL_FRAME2_M,32,0,wk->heapID);
	}
}

/**
 *	@brief	�^���[���BGL�V�X�e���j��
 */
static void BTowerAppBGLRelease(BTOWER_APP_WORK* wk)
{
	int i,frame;
	
	frame = GF_BGL_FRAME0_M;
	for(i = 0;i < 2+wk->mainMode;i++){
		GF_BGL_BGControlExit(wk->bgl,frame++);
	}
	sys_FreeMemoryEz(wk->bgl);
}

/**
 *	@brief	�^���[�A�v���@2D���\�[�X������
 */
static void BTowerApp_2DGraInit(BTOWER_APP_WORK* wk)
{
	int id;
	ARCHANDLE* handle;

	//�A�[�J�C�u�n���h���擾
	handle = ArchiveDataHandleOpen(ARC_BTOWER_APP,wk->heapID);

	//�L�����N�^�]��
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,
		handle,ARC_BTOWER_APP,NARC_btower_btwr_bg_ncgr,
		GF_BGL_FRAME1_M,0,0,0);
	
	//�p���b�g�]��
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,
		handle,ARC_BTOWER_APP,NARC_btower_btwr_bg_nclr,
		GF_BGL_FRAME1_M,2,0x20*0x02,0);

	//�X�N���[���]��
	if(wk->mainMode == 1){
		id = NARC_btower_btwr_bg02_nscr;
	}else{
		if(wk->subMode == 2){
			id = NARC_btower_btwr_bg03_nscr;
		}else{
			id = NARC_btower_btwr_bg01_nscr;
		}
	}
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,handle,ARC_BTOWER_APP,id,
				GF_BGL_FRAME1_M,1,0,0);

	//�n���h������
	ArchiveDataHandleClose( handle );
	
	//�X�N���[���]��
	GF_BGL_LoadScreenV_Req(wk->bgl,GF_BGL_FRAME1_M);
}

/**
 *	@brief	�^���[�A�v���@BMPWIN������
 */
static void BTowerApp_BmpWinAdd(BTOWER_APP_WORK* wk)
{
	int i;
	static const BMPWIN_DAT bmp01[] = {
	  {	BMPL_TITLE_FRM,BMPL_TITLE_PX, BMPL_TITLE_PY,
		BMPL_TITLE_SX, BMPL_TITLE_SY, BMPL_TITLE_PAL, BMPL_TITLE_CGX },
	  {	BMPL_ST01_FRM,BMPL_ST01_PX, BMPL_ST01_PY,
		BMPL_ST01_SX, BMPL_ST01_SY, BMPL_ST01_PAL, BMPL_ST01_CGX },
	  {	BMPL_ST02_FRM,BMPL_ST02_PX, BMPL_ST02_PY,
		BMPL_ST02_SX, BMPL_ST02_SY, BMPL_ST02_PAL, BMPL_ST02_CGX },
	  {	BMPL_REC01_FRM,BMPL_REC01_PX, BMPL_REC01_PY,
		BMPL_REC01_SX, BMPL_REC01_SY, BMPL_REC01_PAL, BMPL_REC01_CGX },
	  {	BMPL_REC02_FRM,BMPL_REC02_PX, BMPL_REC02_PY,
		BMPL_REC02_SX, BMPL_REC02_SY, BMPL_REC02_PAL, BMPL_REC02_CGX },
	  {	BMPL_TALK_FRM,BMPL_TALK_PX, BMPL_TALK_PY,
		BMPL_TALK_SX, BMPL_TALK_SY, BMPL_TALK_PAL, BMPL_TALK_CGX },
	};
	static const BMPWIN_DAT bmp02[] = {
	  {	BMPL_TITLE_FRM,BMPL_TITLE_PX, BMPL_TITLE_PY,
		BMPL_TITLE_SX, BMPL_TITLE_SY, BMPL_TITLE_PAL, BMPL_TITLE_CGX },
	  {	BMPL_NAME_FRM,BMPL_NAME_PX, BMPL_NAME_PY,
		BMPL_NAME_SX, BMPL_NAME_SY, BMPL_NAME_PAL, BMPL_NAME_CGX },
	  {	BMPL_TALK_FRM,BMPL_TALK_PX, BMPL_TALK_PY,
		BMPL_TALK_SX, BMPL_TALK_SY, BMPL_TALK_PAL, BMPL_TALK_CGX },
	};

	//�E�B���h�E�쐬
	if(wk->mainMode == 0){
		for(i = 0;i < WINS_MAX;i++){
			GF_BGL_BmpWinAddEx(wk->bgl,&(wk->win[i]),&(bmp01[i]));
			GF_BGL_BmpWinDataFill(&wk->win[i],APP_WINCLR_COL(FBMP_COL_NULL));
		}
	}else{
		for(i = 0;i < WINL_MAX;i++){
			GF_BGL_BmpWinAddEx(wk->bgl,&(wk->win[i]),&(bmp02[i]));
			GF_BGL_BmpWinDataFill(&wk->win[i],APP_WINCLR_COL(FBMP_COL_NULL));
		}
	}
	//�V�X�e���p�t�H���g�p���b�g�]��
	SystemFontPaletteLoad(PALTYPE_MAIN_BG,FONT_SYS_PAL*32,wk->heapID);
}

/**
 *	@brief	�^���[�A�v���@BMP�E�B���h�E���
 */
static void BTowerApp_BmpWinRelease(BTOWER_APP_WORK* wk)
{
	int i,size;
	if(wk->mainMode == 0){
		size = WINS_MAX;
	}else{
		size = WINL_MAX;
	}
	for(i = 0;i < size;i++){
		GF_BGL_BmpWinOff(&wk->win[i]);
		GF_BGL_BmpWinDel(&wk->win[i]);
	}
}

/**
 *	@brief	�^���[�A�v���@���b�Z�[�W�}�l�[�W��������
 */
static void BTowerApp_MsgManagerGet(BTOWER_APP_WORK* wk)
{
	int i = 0;
	
	wk->msgDat.pMan = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
			NARC_msg_btower_app_dat,wk->heapID);
	
	wk->msgDat.wset = WORDSET_CreateEx(2,WORDSET_BTOWER_APP_BUFLEN,wk->heapID);
	
	//�f�t�H���g������擾
	wk->msgDat.tmp = STRBUF_Create(WORDSET_BTOWER_APP_BUFLEN,wk->heapID);

	for(i = 0;i < 6;i++){
		wk->msgDat.rbuf[i] = MSGMAN_AllocString(wk->msgDat.pMan,msg_btwr_score_r01+i);
	}
	wk->msgDat.tbuf = MSGMAN_AllocString(wk->msgDat.pMan,msg_btwr_leader_t01);
	wk->msgDat.nbuf = MSGMAN_AllocString(wk->msgDat.pMan,msg_btwr_leader_name);
	wk->msgDat.ebuf = MSGMAN_AllocString(wk->msgDat.pMan,msg_btwr_leader_return);
	wk->msgDat.a1buf = MSGMAN_AllocString(wk->msgDat.pMan,msg_btwr_leader_area01);
	wk->msgDat.a2buf = MSGMAN_AllocString(wk->msgDat.pMan,msg_btwr_leader_area02);
	wk->msgDat.cbuf = MSGMAN_AllocString(wk->msgDat.pMan,msg_btwr_leader_area03);

	//�v���C���[�f�t�H���g���W�J
	wk->msgDat.def_name[0] = MSGMAN_AllocString(wk->msgDat.pMan,msg_def_player_name01);
	wk->msgDat.def_name[1] = MSGMAN_AllocString(wk->msgDat.pMan,msg_def_player_name02);
}

/**
 *	@brief	�^���[�A�v���@���b�Z�[�W�}�l�[�W�����
 */
static void BTowerApp_MsgManagerRelease(BTOWER_APP_WORK* wk)
{
	int i = 0;

	STRBUF_Delete(wk->msgDat.def_name[1]);
	STRBUF_Delete(wk->msgDat.def_name[0]);
	STRBUF_Delete(wk->msgDat.cbuf);
	STRBUF_Delete(wk->msgDat.a2buf);
	STRBUF_Delete(wk->msgDat.a1buf);
	STRBUF_Delete(wk->msgDat.ebuf);
	STRBUF_Delete(wk->msgDat.nbuf);
	STRBUF_Delete(wk->msgDat.tbuf);
	for(i = 0;i < 6;i++){
		STRBUF_Delete(wk->msgDat.rbuf[i]);
	}
	STRBUF_Delete(wk->msgDat.tmp);
	
	WORDSET_Delete(wk->msgDat.wset);
	MSGMAN_Delete(wk->msgDat.pMan);
}

static void tapp_ScoreRenshouWrite(BTOWER_APP_WORK* wk,GF_BGL_BMPWIN* win,u8 mode,u8 recid,u8 yofs)
{
	u16 flag,recmax,recnow;
	int	xofs;

	//�L�^
	recmax = RECORD_Get(wk->recordSave,recid);
	recnow = RECORD_Get(wk->recordSave,recid+1);
	
	//�O��or����
	flag = TowerScoreData_SetFlags(wk->scoreSave,
			BTWR_SFLAG_SINGLE_RECORD+mode,BTWR_DATA_get);
	
	GF_STR_PrintColor(win,FONT_SYSTEM,wk->msgDat.rbuf[flag],4,yofs,MSG_NO_PUT,FCOLA_WHITE,NULL);
	
	WORDSET_RegisterNumber(wk->msgDat.wset,0,recnow,4,
				NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);	
	WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,wk->msgDat.rbuf[4]);

	xofs = BMPL_REC01_SX*8-FontProc_GetPrintStrWidth(FONT_SYSTEM,wk->msgDat.tmp,0)-4;
	GF_STR_PrintColor(win,FONT_SYSTEM,wk->msgDat.tmp,
						xofs,yofs,MSG_NO_PUT,FCOLA_BLACK,NULL);

	//�ō�
	yofs += 24;
	GF_STR_PrintColor(win,FONT_SYSTEM,wk->msgDat.rbuf[2],4,yofs,MSG_NO_PUT,FCOLA_WHITE,NULL);
	
	WORDSET_RegisterNumber(wk->msgDat.wset,0,recmax,4,
				NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);	
	WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,wk->msgDat.rbuf[4]);
	
	xofs = BMPL_REC01_SX*8-FontProc_GetPrintStrWidth(FONT_SYSTEM,wk->msgDat.tmp,0)-4;
	GF_STR_PrintColor(win,FONT_SYSTEM,wk->msgDat.tmp,xofs,yofs,MSG_NO_PUT,FCOLA_BLACK,NULL);

	GF_BGL_BmpWinOn(win);
}

/**
 *	���у��j�^��ʕ�����`��
 */
static void BTowerApp_MsgWriteScore(BTOWER_APP_WORK* wk)
{
	int xofs;
	u16	flag,rec;
	
	//�^�C�g��
	MSGMAN_GetString(wk->msgDat.pMan,msg_btwr_score_t01+wk->subMode,wk->msgDat.tmp);
	xofs = FontProc_GetPrintStrWidth(FONT_SYSTEM,wk->msgDat.tmp,0);
	xofs = (BMPL_TITLE_SX*8)-xofs;
	GF_STR_PrintColor(&wk->win[WINS_TITLE],FONT_SYSTEM,wk->msgDat.tmp,
			xofs/2,8,MSG_ALLPUT,FCOLS_WHITE,NULL);

	//�T�u�^�C�g��
	MSGMAN_GetString(wk->msgDat.pMan,msg_btwr_score_s01+wk->subMode,wk->msgDat.tmp);
	GF_STR_PrintColor(&wk->win[WINS_ST01],FONT_SYSTEM,wk->msgDat.tmp,
						0,0,MSG_ALLPUT,FCOLA_WHITE,NULL);
	
	MSGMAN_GetString(wk->msgDat.pMan,msg_btwr_score_s04+wk->subMode,wk->msgDat.tmp);
	GF_STR_PrintColor(&wk->win[WINS_ST02],FONT_SYSTEM,wk->msgDat.tmp,
						0,3,MSG_ALLPUT,FCOLA_WHITE,NULL);

	//�L�^
	switch(wk->subMode){
	case 0:	//�V���O���E�_�u��
		tapp_ScoreRenshouWrite(wk,&wk->win[WINS_REC01],0,RECID_RENSHOU_SINGLE,0);
		tapp_ScoreRenshouWrite(wk,&wk->win[WINS_REC02],1,RECID_RENSHOU_DOUBLE,3);
		break;
	case 1:	//�}���`�E�ʐM�}���`
		tapp_ScoreRenshouWrite(wk,&wk->win[WINS_REC01],2,RECID_RENSHOU_MULTI,0);
		tapp_ScoreRenshouWrite(wk,&wk->win[WINS_REC02],3,RECID_RENSHOU_COMM_MULTI,3);
		break;
	case 2:	//wifi
		//�����N�\��
		MSGMAN_GetString(wk->msgDat.pMan,msg_btwr_score_r04,wk->msgDat.tmp);
		GF_STR_PrintColor(&wk->win[WINS_REC01],FONT_SYSTEM,wk->msgDat.tmp,
						4,10,MSG_ALLPUT,FCOLA_WHITE,NULL);
	
		WORDSET_RegisterNumber(wk->msgDat.wset,0,
				TowerScoreData_SetWifiRank(wk->scoreSave,BTWR_DATA_get),
				2,NUMBER_DISPTYPE_LEFT,NUMBER_CODETYPE_DEFAULT);	
		WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,wk->msgDat.rbuf[5]);
		
		xofs = 64-FontProc_GetPrintStrWidth(FONT_SYSTEM,wk->msgDat.tmp,0);
		xofs  = xofs/2+64;
		GF_STR_PrintColor(&wk->win[WINS_REC01],FONT_SYSTEM,wk->msgDat.tmp,
						xofs,10,MSG_ALLPUT,FCOLA_ORANGE,NULL);
		
		tapp_ScoreRenshouWrite(wk,&wk->win[WINS_REC02],4,RECID_RENSHOU_WIFI,3);
		break;
	}
}

/**
 *	@brief	��ナ�[�_�[�f�[�^�擾
 */
static void BTowerApp_GetLeaderData(BTOWER_APP_WORK* wk)
{
	int i;
	B_TOWER_LEADER_DATA* bp;
	LEADER_DATA* lp;
	
	//�܂��̓��[�_�[�Z�[�u�f�[�^���擾
	bp = TowerWifiData_GetLeaderDataAlloc(wk->wifiSave,wk->heapID);
	
	for(i = 0;i < BTOWER_STOCK_WIFI_LEADER_MAX;i++){
		lp = &wk->leader[i];

		lp->sex = bp[i].gender;
		lp->country = bp[i].country_code;
		lp->area = bp[i].address;
		lp->ngname_f = bp[i].ngname_f;
	
		MI_CpuCopy8(bp[i].leader_word,&lp->msg,8);

		//�v���C���[���pSTRBUF�I�u�W�F�N�g�̈�m��
		lp->name = STRBUF_Create(BUFLEN_PERSON_NAME,wk->heapID);

		//������NG�l�[���Ȃ�f�t�H���g���ŕ\������
		if(lp->ngname_f){
			STRBUF_Copy(lp->name,wk->msgDat.def_name[lp->sex]);
		}else{
			STRBUF_SetStringCode( lp->name, bp[i].name);
		}
	}
	//�R�s�[����������v��Ȃ��̂ŉ��
	sys_FreeMemoryEz(bp);
}

/**
 *	@brief	��ナ�[�_�[�f�[�^���
 */
static void BTowerApp_ReleaseLeaderData(BTOWER_APP_WORK * wk)
{
	int i = 0;

	for(i = 0;i < BTOWER_STOCK_WIFI_LEADER_MAX;i++){
		STRBUF_Delete(wk->leader[i].name);
	}
}

/**
 *	@brief	��ナ�[�_�[��ʁ@�v���C���[���X�g�`��
 */
static void BTowerApp_WritePlayerList(LEADER_DATA* leader,
		GF_BGL_BMPWIN* win,STRBUF* retBuf,u8 up,u8 line,u8 side)
{
	LEADER_DATA* lp;
	int i,j,pos,lmax,xofs;
	GF_PRINTCOLOR	col;
	
	GF_BGL_BmpWinDataFill(win,APP_WINCLR_COL(FBMP_COL_NULL));
	
	if(up >= LINE_SCR_MAX){
		lmax = 2;
		xofs = (ACT_RET_SX-FontProc_GetPrintStrWidth(FONT_SYSTEM,retBuf,0))/2;
		GF_STR_PrintColor(win,FONT_SYSTEM,retBuf,
				2*LIST_SIDE_WIDTH+16+xofs,2*24+4,MSG_NO_PUT,FCOLS_BLACK,NULL);
	}else{
		lmax = 3;
	}
	pos = up*3;
	for(i = 0;i < lmax;i++){
		for(j = 0;j < 3;j++){
			lp = &leader[i*3+j+pos];
			if(lp->sex){
				col = FCOLA_RED; 
			}else{
				col = FCOLA_BLUE;
			}
			GF_STR_PrintColor(win,FONT_SYSTEM,lp->name,
					j*LIST_SIDE_WIDTH,i*24+4,MSG_NO_PUT,col,NULL);
		}
	}
	GF_BGL_BmpWinOn(win);
}

/**
 *	@brief	��ナ�[�_�[��ʕ����񏉊��`��
 */
static void BTowerApp_MsgWriteLeader(BTOWER_APP_WORK* wk)
{
	BTOWER_ROOMID roomid;
	int xofs;
	
	//�����N�����@���[������
	TowerWifiData_GetLeaderDataRoomID(wk->wifiSave,&roomid);
	
	STRBUF_Clear(wk->msgDat.tmp);
	WORDSET_RegisterNumber(wk->msgDat.wset,0,roomid.rank,2,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_RegisterNumber(wk->msgDat.wset,1,roomid.no,3,
			NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,wk->msgDat.tbuf);		
		
	xofs = BMPL_TITLE_SX*8-FontProc_GetPrintStrWidth(FONT_SYSTEM,wk->msgDat.tmp,0);
	GF_STR_PrintColor(&wk->win[WINL_TITLE],FONT_SYSTEM,wk->msgDat.tmp,
						xofs/2,4,MSG_NO_PUT,FCOLS_WHITE,NULL);
	
	//�^�C�g��
	MSGMAN_GetString(wk->msgDat.pMan,msg_btwr_leader_t02+wk->subMode,wk->msgDat.tmp);
	xofs = BMPL_TITLE_SX*8-FontProc_GetPrintStrWidth(FONT_SYSTEM,wk->msgDat.tmp,0);
	GF_STR_PrintColor(&wk->win[WINL_TITLE],FONT_SYSTEM,wk->msgDat.tmp,
						xofs/2,20,MSG_ALLPUT,FCOLS_WHITE,NULL);
	
	//���O�����񏉊��`��
	BTowerApp_WritePlayerList(wk->leader,&wk->win[WINL_NAME],wk->msgDat.ebuf,0,0,0);
}

/**
 *	@brief	��ナ�[�_�[��� �v���C���[�G���A�R�[�h�`��
 */
static void BTowerApp_PlayerAreaMsgWrite(BTOWER_APP_WORK* wk)
{
	LEADER_DATA* lp = &(wk->leader[wk->line*3+wk->side]);

	if(lp->country  == 0 ){	//�Z��ł���ꏊ���o�^��
		GF_STR_PrintColor(&wk->win[WINL_TALK],FONT_SYSTEM,wk->msgDat.cbuf,
							0,4,MSG_ALLPUT,FCOLS_BLACK,NULL);
	}else if(lp->area == 0){
		//���R�[�h�̂ݓo�^��
		WORDSET_RegisterCountryName(wk->msgDat.wset,0,lp->country);
		WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,wk->msgDat.a2buf);
		
		GF_STR_PrintColor(&wk->win[WINL_TALK],FONT_SYSTEM,wk->msgDat.tmp,
							0,4,MSG_ALLPUT,FCOLS_BLACK,NULL);
	}else{
		//���R�[�h�ƃG���A�R�[�h��W�J
		WORDSET_RegisterCountryName(wk->msgDat.wset,0,lp->country);
		WORDSET_RegisterLocalPlaceName(wk->msgDat.wset,1,lp->country,lp->area);
		WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,wk->msgDat.a1buf);
	
		GF_STR_PrintColor(&wk->win[WINL_TALK],FONT_SYSTEM,wk->msgDat.tmp,
							0,4,MSG_ALLPUT,FCOLS_BLACK,NULL);
	}
	GF_BGL_BmpWinOn(&wk->win[WINL_TALK]);

	//�I���J�[�\���̃X�e�[�g�ύX
	Act_CursorChg(wk,FALSE);
	
}

/**
 *	@brief	��ナ�[�_�[��� �v���C���[���b�Z�[�W�`��
 */
static void BTowerApp_PlayerMsgWrite(BTOWER_APP_WORK* wk)
{
	STRBUF* str;
	LEADER_DATA* lp = &(wk->leader[wk->line*3+wk->side]);
	
	//�ȈՉ�b��W�J
	str = PMSDAT_ToString(&lp->msg,wk->heapID);
	
	GF_BGL_BmpWinDataFill(&wk->win[WINL_TALK],APP_WINCLR_COL(FBMP_COL_NULL));
	GF_STR_PrintColor(&wk->win[WINL_TALK],FONT_SYSTEM,str,
						0,4,MSG_ALLPUT,FCOLS_BLACK,NULL);
	STRBUF_Delete(str);

}

/**
 *	@brief	��ナ�[�_�[��ʁ@�v���C���[���b�Z�[�W�N���A
 */
static void BTowerApp_PlayerMsgClear(BTOWER_APP_WORK* wk)
{
	GF_BGL_BmpWinDataFill(&wk->win[WINL_TALK],APP_WINCLR_COL(FBMP_COL_NULL));
	GF_BGL_BmpWinOff(&wk->win[WINL_TALK]);
	
	//�I���J�[�\���̃X�e�[�g�ύX
	Act_CursorChg(wk,TRUE);	
}
#if 1

static void BTowerApp_ActorInit(BTOWER_APP_WORK *wk)
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
			BTOWER_APP_ACTRES_MAX,	//ID���䐔
			2048,	//���C����ʃT�C�Y(byte�P��)
			2048,	//�T�u��ʃT�C�Y(byte�P��)
			GX_OBJVRAMMODE_CHAR_1D_32K,	//���C��OBJ���[�h�w��
			GX_OBJVRAMMODE_CHAR_1D_32K,	//�T�uOBJ���[�h�w��
		};

		CATS_SystemInit( wk->pActSys, &coi, &ccmm, 32 );
		CATS_ClactSetInit( wk->pActSys, wk->pActRes,ACT_MAX );

		//OAM������
		REND_OAM_UtilOamRamClear_Main(wk->heapID);
		REND_OAM_UtilOamRamClear_Sub(wk->heapID);
	}

	{
		TCATS_RESOURCE_FILE_LIST list = {
			"data/btower_chr.resdat",		// �L�����N�^
			"data/btower_pal.resdat",		// �p���b�g
			"data/btower_cell.resdat",	// �Z��
			"data/btower_canm.resdat",	// �Z���A�j��
			NULL,						// �}���`�Z��
			NULL,						// �}���`�Z���A�j��
			"data/btower_celact.cldat"		// �w�b�_�[		
		};
		CATS_ResourceLoadBinary( wk->pActSys, wk->pActRes, &list );
	}
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,VISIBLE_ON);
//	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ,VISIBLE_ON);
}

static void BTowerApp_ActorRelease(BTOWER_APP_WORK *wk)
{
	CATS_ResourceDestructor(wk->pActSys,wk->pActRes);
	CATS_FreeMemory(wk->pActSys);
	DellVramTransferManager();	
}

static void BTowerApp_ActorMain(BTOWER_APP_WORK *wk)
{
	if(wk->pActRes == NULL){
		return;
	}
	CATS_Draw(wk->pActRes);
}

static void BTowerApp_ActorTrans(void)
{
	CATS_RenderOamTrans();
}

/**
 *	@brief	��ナ�[�_�[��ʃA�N�^�[�o�^
 */
static void BTowerApp_MakeLeaderViewAct(BTOWER_APP_WORK* wk)
{
	int i;
	
	static const TCATS_OBJECT_ADD_PARAM	ActAddParam[] =
	{
		{	// �I���J�[�\��
			0,	//ID
			ACT_CUR_PX, ACT_CUR_PY, 0,	//x,y,z
			ACT_CURSOR, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN,	//anmNO,pri,pal,d_area
			0, 0, 0, 0	//prm1,prm2,prm3,prm4
		},
		{	// �߂�p�l�� 
			0,	//ID
			ACT_RET_PX, ACT_RET_PY, 0,	//x,y,z
			ACT_RET, 2, 0, NNS_G2D_VRAM_TYPE_2DMAIN,	//anmNO,pri,pal,d_area
			0, 0, 0, 0	//prm1,prm2,prm3,prm4
		},
		{	// ���� 
			0,	//ID
			ACT_UP_PX, ACT_UP_PY, 0,	//x,y,z
			ACT_UP, 3, 0, NNS_G2D_VRAM_TYPE_2DMAIN,	//anmNO,pri,pal,d_area
			0, 0, 0, 0	//prm1,prm2,prm3,prm4
		},
		{	// ����� 
			0,	//ID
			ACT_DOWN_PX, ACT_DOWN_PY, 0,	//x,y,z
			ACT_DOWN, 4, 0, NNS_G2D_VRAM_TYPE_2DMAIN,	//anmNO,pri,pal,d_area
			0, 0, 0, 0	//prm1,prm2,prm3,prm4
		},
	};
	for(i = 0;i < ACT_MAX;i++){
		wk->pAct[i] = CATS_ObjectAdd( wk->pActSys,
				wk->pActRes,
				&ActAddParam[i] );
	}
	CLACT_SetDrawFlag(wk->pAct[ACT_UP], 0);
	CLACT_SetDrawFlag(wk->pAct[ACT_RET], 0);
	
	CLACT_SetAnmFlag(wk->pAct[ACT_CURSOR], TRUE);
	CLACT_SetAnmFlag(wk->pAct[ACT_UP], TRUE);
	CLACT_SetAnmFlag(wk->pAct[ACT_DOWN], TRUE);
	
	CLACT_BGPriorityChg(wk->pAct[ACT_RET], 3);
}

/**
 *	@brief	��ナ�[�_�[��ʁ@�A�N�^�[�폜
 */
static void BTowerApp_DelLeaderViewAct(BTOWER_APP_WORK* wk)
{
	int i;

	for(i = 0;i < ACT_MAX;i++){
		CATS_ObjectDel(wk->pAct[i]);
	}
}

/**
 *	@brief	��ナ�[�_�[��ʁ@�J�[�\���A�N�^�[��ԃ`�F���W
 */
static void Act_CursorChg(BTOWER_APP_WORK* wk,BOOL mode)
{
	BOOL flag;
	if(mode == FALSE){
		CLACT_PaletteNoChg(wk->pAct[ACT_CURSOR],ACT_CUR_PALF);
		flag = FALSE;
	}else{
		CLACT_PaletteNoChg(wk->pAct[ACT_CURSOR],ACT_CUR_PALT);
		flag = TRUE;
	}
	CLACT_SetAnmFlag(wk->pAct[ACT_CURSOR],flag);
	CLACT_SetAnmFlag(wk->pAct[ACT_UP],flag);
	CLACT_SetAnmFlag(wk->pAct[ACT_DOWN],flag);
}

/**
 *	@brief	�A�N�^�[�J�[�\���ʒu�Z�b�g
 */
static void Act_CursorPosSet(BTOWER_APP_WORK* wk,u8 line,u8 side,u8 viewLine)
{
	u16 x,y;
	if(wk->upLine == LINE_RET-2){
		CLACT_SetDrawFlag(wk->pAct[ACT_RET], 1 );
		if(line == LINE_RET){
			CLACT_AnmFrameSet(wk->pAct[ACT_RET],1);
			CLACT_SetDrawFlag(wk->pAct[ACT_CURSOR], 0 );
		}else{
			CLACT_AnmFrameSet(wk->pAct[ACT_RET],0);
			CLACT_SetDrawFlag(wk->pAct[ACT_CURSOR], 1 );
		}
	}else{
		CLACT_SetDrawFlag(wk->pAct[ACT_CURSOR], 1 );
		CLACT_SetDrawFlag(wk->pAct[ACT_RET], 0 );
	}

	switch(wk->upLine){
	case 0:
		CLACT_SetDrawFlag(wk->pAct[ACT_UP], 0 );
		break;
	case LINE_SCR_MAX:
		CLACT_SetDrawFlag(wk->pAct[ACT_DOWN], 0 );
		break;
	default:
		CLACT_SetDrawFlag(wk->pAct[ACT_UP], 1 );
		CLACT_SetDrawFlag(wk->pAct[ACT_DOWN], 1 );
		break;
	}
	CATS_ObjectPosSet(wk->pAct[ACT_CURSOR],
			side*LIST_SIDE_WIDTH+ACT_CUR_PX,viewLine*24+ACT_CUR_PY);
}
#endif
