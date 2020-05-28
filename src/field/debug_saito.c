#ifdef PM_DEBUG

#include "common.h"
#include "system/pm_str.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/arc_util.h"
#include "system/bmp_cursor.h"
#include "fld_bmp.h"
#include "fieldmap.h"
#include "field_common.h"
#include "system/fontproc.h"

#include "debug_saito.h"

#include "system/brightness.h"

#include "camera_move_test.h"

#include "fieldsys.h"

#include "field_event.h"
#include "mapdefine.h"
#include "worldmap.h"
//#include "effect_uground.h"
#include "player.h"
#include "zonedata.h"

//#include "under_tp.h"
#include "comm_field_state.h"  // �n���ʐM�p

#include "ev_mapchange.h"
#include "eventdata.h"		//�]�[�����̃C�x���g�f�[�^�Q�Ƃ̂���

//���|�P�����֘A
#include "system/buflen.h"

#include "system/msgdata_util.h"

#include "sway_grass_enc.h"

#include "msgdata/msg_debug_saito.h"
#include "msgdata/msg.naix"

#include "encount_set.h"

#include "savedata/encount.h"
#include "move_pokemon_def.h"

#include "move_pokemon.h"
#include "field/field_place_name.h"
#include "system/snd_tool.h"

#include "generate_zone.h"

#include "encount_define.h"
#include "arc/encdata_ex.naix"
#include "system/zukanwork.h"

#include "sp_fishing_enc.h"
#include "safari_enc.h"

#define	FDBG_DEBUG_PL		(FLD_SYSFONT_PAL)	//�p���b�g�i���o�[

#define DISP_LINE_MAX	(9)

#define HEAPID_D_SAITO	(HEAPID_BASE_APP)



//----------------------------------------------------------------------------
//	�\���̒�`
//----------------------------------------------------------------------------
typedef struct _DEBUG_WINDOW_DATA{
//	u8	work;
	
	u16 debug_list;
	u16 debug_cursor;

	GF_BGL_BMPWIN	win;
	BMPLIST_WORK* lw;		// BMP���j���[���[�N
	struct _FIELDSYS_WORK * fsys;
	BMP_MENULIST_DATA 	*ld;
}DEBUG_WINDOW_DATA;

typedef struct _DEBUG_WORK_DATA{
	struct _FIELDSYS_WORK * fsys;
	GF_CAMERA_PTR camera;
	STRBUF	*StrBuf;
	u8 camera_tbl_no;
	
	GF_BGL_BMPWIN	win;
	s8	rod;
	u8	MovePokeInfoNo;	//0�`2
	s8	zone_idx;
	u8	SafariArea;
}DEBUG_WORK_DATA;

typedef void (*DRAW_FUNC)( DEBUG_WORK_DATA* );

static const GF_CAMERA_PARAM TestOrgCamera[] =
{
	{
		/*0x30aec1*/0x29aec1,
		{
			-0x29fe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x05c1,
		0	//dummy
	},								//0
	{
		0x189647,
		{
			-0x2ffe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x09c1,
		0	//dummy
	},								//1
	{
		0x23e93f,
		{
			-0x2cfe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x06c1,
		0	//dummy
	},								//2
	{
		0x1b8152,
		{
			-0x29fe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x08c1,
		0	//dummy
	},								//3
	{
		0x3346fe,
		{
			-0x29fe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x04c1,
		0	//dummy
	},								//4
	{
		0x298ec1,
		{
			-0x29fe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x05c1,
		0	//dummy
	},								//5
	{
		0x14aec0,
		{
			-0x29fe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x0B01,
		0	//dummy
	},								//6
	{
		0x411726,
		{
			-0x23be,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x03c1,
		1	//near_far
	},								//7
	{
		0x61b89b,
		{
			-0x239e,0,0
		},
		GF_CAMERA_ORTHO,
		0x0281,
		2	//near_far
	},								//8
};

//------------------------------------------------------------------------------
//	global
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//	extern
//------------------------------------------------------------------------------
extern u8 HC_DebugCheckHeight(const fx32 inX, const fx32 inZ, MHI_CONST_PTR inMap3DInfo, const BOOL inDetail);
//---------------------------------------------------------------------------
//	static �ϐ�
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//	static �֐�
//---------------------------------------------------------------------------
static void InitDebugWindow(DEBUG_WINDOW_DATA *wp);
static void DebugListFree(TCB_PTR tcb,void* work);
static void DebugWindowExit(TCB_PTR tcb,void* work);
static void DebugListControlTask(TCB_PTR tcb,void* work);

static void ChangeStressFlg(TCB_PTR tcb,void *work);
static void DebugWinSwayGrass(TCB_PTR tcb,void *work);
static void DispSwayGrassRec(TCB_PTR tcb,void *work);

static void MBMapSetExit(TCB_PTR tcb,void* work);


static void SetCameraDebugWindow(TCB_PTR tcb,void *work);
static void SetupCameraInfoWindow(TCB_PTR tcb,void *work);
static void SetupCameraListWindow(TCB_PTR tcb,void *work);

static void SetCamera(TCB_PTR tcb,void *work);
static void SetSwayGrass(TCB_PTR tcb,void *work);
///static void SetupPokeAnmWindow(TCB_PTR tcb,void *work);
static void DebugWinFishing(TCB_PTR tcb,void *work);
static void DebugWinMovePoke(TCB_PTR tcb,void *work);

static void SetupFishingRod(TCB_PTR tcb,void *work);
static void SetupFishingProb(TCB_PTR tcb,void *work);
static void SetupSpFishingPoint(TCB_PTR tcb,void *work);

static void SetupSwayGrassChain(TCB_PTR tcb,void *work);
static void DispSwayGrassInfo(TCB_PTR tcb,void *work);

static void SetupMovePokeInfo(TCB_PTR tcb,void *work);
static void DebugWinMovePokeName(TCB_PTR tcb,void *work);
static void SetupEntryMovePoke(TCB_PTR tcb,void *work);
static void SetupMovePokeZoneChgWin(TCB_PTR tcb,void *work);

//�����ύX
static void SetPlayerHeightChangeTask(TCB_PTR tcb,void *work);

//�����f�o�b�O
static void DebugCheckHeightGrid(TCB_PTR tcb,void *work);
static void DebugCheckHeightBlock(TCB_PTR tcb,void *work);

//��ʔ���
static void DebugGenerate(TCB_PTR tcb,void *work);
static void DebugStartGenerate(TCB_PTR tcb,void *work);
static void SetupGeneZoneInfoWin(TCB_PTR tcb,void *work);

//�T�t�@��
static void DebugSafari(TCB_PTR tcb,void *work);

//AGB
static void DebugSetAgbVer(TCB_PTR tcb,void *work);
static void DebugAgbVer(TCB_PTR tcb,void *work);

//----------------------------------------------------------------------------
//	���X�g���ږ�
//----------------------------------------------------------------------------

//--------------------------------------------------------------------------
//	���ڂƎ��s�֐��̃��X�g
//--------------------------------------------------------------------------
typedef struct ID_PARAM_tag
{
	u32  str_id;
	u32  param;
}ID_PARAM;

static const ID_PARAM DebugMenuMainList[] = {
	{ D_SAITO_MSG01, (u32)SetCamera },
	{ D_SAITO_MSG02, (u32)DebugWinSwayGrass, },
    { D_SAITO_MSG03, (u32)DebugCheckHeightBlock },
    { D_SAITO_MSG04, (u32)DebugCheckHeightGrid },
    { D_SAITO_MSG05, (u32)SetCameraDebugWindow },
    { D_SAITO_MSG06, (u32)SetPlayerHeightChangeTask },
///	{ D_SAITO_MSG09, (u32)SetupPokeAnmWindow },
	{ D_SAITO_MSG10, (u32)DebugWinFishing },
	{ D_SAITO_MSG11, (u32)DebugWinMovePoke },
	{ D_SAITO_MSG12, (u32)DebugGenerate },
	{ D_SAITO_MSG13, (u32)DebugSafari},
	{ D_SAITO_MSG14, (u32)DebugSetAgbVer },
};

static const ID_PARAM DebugCameraMenuList[] = {
	{ D_SAITO_MSG07, (u32)SetupCameraInfoWindow },
	{ D_SAITO_MSG08, (u32)SetupCameraListWindow },
};

static const ID_PARAM DebugSwayGrassMenuList[] = {
	{ D_SAITO_SWAY01, (u32)SetSwayGrass },
	{ D_SAITO_SWAY02, (u32)SetupSwayGrassChain },
	{ D_SAITO_SWAY03, (u32)DispSwayGrassInfo },
	{ D_SAITO_SWAY04, (u32)DispSwayGrassRec },
};

static const ID_PARAM DebugFishingMenuList[] = {
	{ D_SAITO_FISH01, (u32)SetupFishingRod },
	{ D_SAITO_FISH02, (u32)SetupFishingProb },
	{ D_SAITO_FISH03, (u32)SetupSpFishingPoint },
};

static const ID_PARAM DebugMovePokeMenuList[] = {
	{ D_SAITO_MP01, (u32)SetupMovePokeInfo },
	{ D_SAITO_MP02, (u32)DebugWinMovePokeName },
	{ D_SAITO_MP03, (u32)SetupEntryMovePoke },
};

static const ID_PARAM DebugMovePokeNameList[] = {
	{ D_SAITO_MP_AI, (u32)SetupMovePokeZoneChgWin },
	{ D_SAITO_MP_MUUBASU, (u32)SetupMovePokeZoneChgWin },
	{ D_SAITO_MP_DAAKU, (u32)SetupMovePokeZoneChgWin },
};

static const ID_PARAM DebugGeneMenuList[] = {
	{ D_SAITO_GENE01, (u32)DebugStartGenerate },
	{ D_SAITO_GENE02, (u32)SetupGeneZoneInfoWin },
};

static const ID_PARAM DebugAgbMenuList[] = {
	{ D_SAITO_AGB00, (u32)DebugAgbVer },
	{ D_SAITO_AGB01, (u32)DebugAgbVer },
	{ D_SAITO_AGB02, (u32)DebugAgbVer },
	{ D_SAITO_AGB03, (u32)DebugAgbVer },
	{ D_SAITO_AGB04, (u32)DebugAgbVer },
	{ D_SAITO_AGB05, (u32)DebugAgbVer },
};

//---------------------------------------------------------------------------
//  �E�B���h�E�ݒ�
//---------------------------------------------------------------------------
//���C���E�B���h�E
static const BMPWIN_DAT	MainDebugListWindowData = {
	GF_BGL_FRAME3_M,
	0,1,
	14,21,
	FDBG_DEBUG_PL,8
};

//�J�����E�B���h�E
static const BMPWIN_DAT	CameraDebugListWindowData = {
	GF_BGL_FRAME3_M,
	0,1,
	14,5,
	FDBG_DEBUG_PL,8
};
//�h�ꑐ
static const BMPWIN_DAT	SwayDebugListWindowData = {
	GF_BGL_FRAME3_M,
	0,1,
	8,10,
	FDBG_DEBUG_PL,8
};
//�ނ�
static const BMPWIN_DAT	FishingDebugListWindowData = {
	GF_BGL_FRAME3_M,
	0,1,
	16,7,
	FDBG_DEBUG_PL,8
};
//�ړ��|�P����
static const BMPWIN_DAT	MovePokeDebugListWindowData = {
	GF_BGL_FRAME3_M,
	0,1,
	12,7,
	FDBG_DEBUG_PL,8
};
//�ړ��|�P������
static const BMPWIN_DAT	MovePokeNameDebugListWindowData = {
	GF_BGL_FRAME3_M,
	0,1,
	8,8,
	FDBG_DEBUG_PL,8
};
//��ʔ���
static const BMPWIN_DAT	GeneDebugListWindowData = {
	GF_BGL_FRAME3_M,
	0,1,
	10,6,
	FDBG_DEBUG_PL,8
};
//AGB
static const BMPWIN_DAT	AgbDebugListWindowData = {
	GF_BGL_FRAME3_M,
	0,1,
	10,14,
	FDBG_DEBUG_PL,8
};



//���X�g�쐬
static void MakeBmpList(struct _FIELDSYS_WORK *fsys, const int inNum, ID_PARAM const *list, BMPWIN_DAT const * win_dat)
{
	TCB_PTR pTcb;
	DEBUG_WINDOW_DATA *wp;

	BMPLIST_HEADER bmplist_h = {
		//MainDebugList,		//�\�������f�[�^�|�C���^
		NULL,				//�\�������f�[�^�|�C���^
		NULL,				//�J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
		NULL,		//�P�s���Ƃ̃R�[���o�b�N�֐�
		NULL,		//GF_BGL_BMPWIN * 
		0,//���X�g���ڐ�
		0,//�\���ő區�ڐ�
		2,					//���x���\���w���W
		12,					//���ڕ\���w���W
		1,					//�J�[�\���\���w���W
		8,					//�\���x���W
		FBMP_COL_WHITE,		//�����F
		FBMP_COL_BLACK,		//�w�i�F
		FBMP_COL_BLK_SDW,	//�����e�F
		0,					//�����Ԋu�w
		1,					//�����Ԋu�x
		BMPLIST_LRKEY_SKIP,	//�y�[�W�X�L�b�v�^�C�v
		FONT_SYSTEM,			//�����w��
		0,					//�a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
		NULL,				//*work
	};
	
	wp = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WINDOW_DATA));
	if(wp == NULL){
		//���[�N�G���A���擾�ł��Ȃ���Ή������Ȃ�
		OS_Printf("map_num debug menu crate failed\n");
		return;
	}
	memset(wp,0,sizeof(DEBUG_WINDOW_DATA));

	wp->fsys = fsys;

	//�f�o�b�O���j���[�p�ϐ�������
	InitDebugWindow(wp);

	//���C�������^�X�N�ǉ�
	pTcb = TCB_Add(DebugListControlTask,wp,0);


	wp->ld = BMP_MENULIST_Create( inNum, HEAPID_D_SAITO );
	{
		MSGDATA_MANAGER* msgman;
		int i;

		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_saito_dat, HEAPID_D_SAITO);
		for(i=0; i<inNum; i++)
		{
			BMP_MENULIST_AddArchiveString( wp->ld, msgman,
					list[i].str_id, list[i].param );
		}
		MSGMAN_Delete(msgman);
	}

	//BITMAP���j���[�ǉ�
	GF_BGL_BmpWinAddEx(fsys->bgl,&wp->win,win_dat);
	//BMP���X�g�ݒ�
	bmplist_h.count = inNum;
	if (DISP_LINE_MAX < inNum){
		bmplist_h.line = DISP_LINE_MAX;
	}else{
		bmplist_h.line = inNum;
	}
	OS_Printf("disp=%d\n",inNum);
	bmplist_h.list = wp->ld;
	bmplist_h.win = &wp->win;
	wp->lw = BmpListSet(&bmplist_h,0,0,HEAPID_D_SAITO);
	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	return;
}

//�E�B���h�E�\�z
static void SetWindow(	struct _FIELDSYS_WORK * fsys, TCB_FUNC t_func, DRAW_FUNC d_func,
						u8 posx, u8 posy, u8 sizx, u8 sizy 	)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(2, HEAPID_D_SAITO);

	//���C�������^�X�N�ǉ�
	pTcb = TCB_Add(t_func,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, posx, posy, sizx, sizy, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//�m���t���O�\��
	d_func(d_work);

	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	return;
}

//===============================================================================
//	�E�B���h�E����
//===============================================================================
//������
static void InitDebugWindow(DEBUG_WINDOW_DATA *wp)
{
	wp->debug_list = 0;
	wp->debug_cursor = 0;
}
//���X�g�̊J������
static void DebugListFree(TCB_PTR tcb,void* work)
{
	DEBUG_WINDOW_DATA	*wp;

	wp = (DEBUG_WINDOW_DATA*)work;

	//BMP�E�B���h�EOFF
	GF_BGL_BmpWinOff(&wp->win);

	//BMP���X�g�j��
	BmpListExit( wp->lw,&wp->debug_list,&wp->debug_cursor );
	//BMPWindow����
	GF_BGL_BmpWinDel( &wp->win );
	return;
}
//�f�o�b�O�E�B���h�E�����
static void FreeDebugWindow(TCB_PTR tcb,void* work)
{
	//���X�g�̊J������
	DebugListFree(tcb,work);
	//���[�N�������J��
	sys_FreeMemoryEz(work);
}

//�f�o�b�O�E�B���h�E�����(�������������)
static void FreeDebugWindowNoFreeMem(TCB_PTR tcb,void* work)
{
	//���X�g�̊J������
	DebugListFree(tcb,work);
}
//�f�o�b�O�E�B���h�E�I��
static void DebugWindowExit(TCB_PTR tcb,void* work)
{
	//�E�B���h�E���
	FreeDebugWindow(tcb,work);
	//�^�X�N����
	TCB_Delete(tcb);
	//OBJ���̓����~����
	FieldSystemProc_SeqHoldEnd();//OBJ���̓����~����
	FieldSystemProc_SeqHoldEnd();
	return;
}
//���X�g�R���g���[��
static void DebugListControlTask(TCB_PTR tcb,void* work)
{
	s32	ret_code;
	TCB_FUNC	func;
	DEBUG_WINDOW_DATA	*wp;
	
	wp = (DEBUG_WINDOW_DATA*)work;

	ret_code = BmpListMain(wp->lw);
	//�L�[���씻��
	if(sys.trg & PAD_BUTTON_A){
		if(ret_code){
			BMP_MENULIST_Delete( wp->ld );	//�Ƃ肠����
			func = (TCB_FUNC)ret_code;
			func(tcb,work);
		}
		return;
	}
	//���j���[�L�����Z��
	if(sys.trg & PAD_BUTTON_B){
		BMP_MENULIST_Delete( wp->ld );	//�Ƃ肠����
		DebugWindowExit(tcb,work);
		return;
	}
}

//================================================================================
//	�J�������
//================================================================================
static void DrawCameraInfo(GF_CAMERA_PTR camera_ptr,GF_BGL_BMPWIN	*win, const u8 inNo)
{	
	u16 buff[10];
	CAMERA_ANGLE angle;
	u16 angle_x;
	STRBUF *str;
	STRBUF *msg_buf;
	MSGDATA_MANAGER* man;

	GF_BGL_BmpWinDataFill( win, 0x0f );

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_saito_dat, HEAPID_D_SAITO);
	str = STRBUF_Create(10, HEAPID_D_SAITO);
	msg_buf = STRBUF_Create(16,HEAPID_D_SAITO);
	
	MSGMAN_GetString(man, D_SAITO_CAM_INFO01 ,msg_buf);
	GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 0, MSG_ALLPUT, NULL );
	MSGMAN_GetString(man, D_SAITO_CAM_INFO02 ,msg_buf);
	GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 1*16, MSG_ALLPUT, NULL );
	MSGMAN_GetString(man, D_SAITO_CAM_INFO03 ,msg_buf);
	GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 2*16, MSG_ALLPUT, NULL );
	MSGMAN_GetString(man, D_SAITO_CAM_INFO04 ,msg_buf);
	GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 3*16, MSG_ALLPUT, NULL );
	MSGMAN_GetString(man, D_SAITO_CAM_INFO05 ,msg_buf);
	GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 4*16, MSG_ALLPUT, NULL );
	MSGMAN_GetString(man, D_SAITO_CAM_INFO06 ,msg_buf);
	GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 5*16, MSG_ALLPUT, NULL );

	STRBUF_SetHexNumber(	str, GFC_GetCameraDistance(camera_ptr), 8,
							NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(win, FONT_SYSTEM, str, 7*8, 0, MSG_ALLPUT, NULL );
	
	angle = GFC_GetCameraAngle(camera_ptr);
	//�p�˒n�ʂ���̌X���ɕϊ�
	angle_x = -angle.x;

	STRBUF_SetHexNumber(str, angle.x, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 1*16, MSG_ALLPUT, NULL );
	STRBUF_SetHexNumber(str, angle.y, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 2*16, MSG_ALLPUT, NULL );
	STRBUF_SetHexNumber(str, angle.z, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 3*16, MSG_ALLPUT, NULL );

	STRBUF_SetHexNumber(str, GFC_GetCameraPerspWay(camera_ptr), 8,
						NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 4*16, MSG_ALLPUT, NULL );

	if (GFC_GetCameraView(camera_ptr) == GF_CAMERA_PERSPECTIV){
		MSGMAN_GetString(man, D_SAITO_CAM_INFO07 ,msg_buf);
		GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 8*8, 5*16, MSG_ALLPUT, NULL );
	}else{
		MSGMAN_GetString(man, D_SAITO_CAM_INFO08 ,msg_buf);
		GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 8*8, 5*16, MSG_ALLPUT, NULL );
	}
	
	{
		//�j�A�E�t�@�[
		int near,far;
		near = GFC_GetCameraNear(camera_ptr)/FX32_ONE;
		far = GFC_GetCameraFar(camera_ptr)/FX32_ONE;
		
		MSGMAN_GetString(man, D_SAITO_CAM_INFO09 ,msg_buf);
		GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 6*16, MSG_ALLPUT, NULL );
		MSGMAN_GetString(man, D_SAITO_CAM_INFO10 ,msg_buf);
		GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 7*16, MSG_ALLPUT, NULL );
		STRBUF_SetNumber(str, near, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 6*16, MSG_ALLPUT, NULL );
		STRBUF_SetNumber(str, far, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 7*16, MSG_ALLPUT, NULL );
	}
	{
		//�����_
		VecFx32 look_at = GFC_GetLookTarget(camera_ptr);
		MSGMAN_GetString(man, D_SAITO_CAM_INFO11 ,msg_buf);
		GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 8*16, MSG_ALLPUT, NULL );
		MSGMAN_GetString(man, D_SAITO_CAM_INFO12 ,msg_buf);
		GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 9*16, MSG_ALLPUT, NULL );
		MSGMAN_GetString(man, D_SAITO_CAM_INFO13 ,msg_buf);
		GF_STR_PrintSimple(win, FONT_SYSTEM, msg_buf, 1*8, 10*16, MSG_ALLPUT, NULL );
		
		STRBUF_SetHexNumber(str, look_at.x, 8,
						NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 8*16, MSG_ALLPUT, NULL );
		STRBUF_SetHexNumber(str, look_at.y, 8,
						NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 9*16, MSG_ALLPUT, NULL );
		STRBUF_SetHexNumber(str, look_at.z, 8,
						NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 10*16, MSG_ALLPUT, NULL );
	}

	{
		//�J�����e�[�u���ԍ�
		STRBUF_SetNumber(str, inNo, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 11*16, MSG_ALLPUT, NULL );
	}
	
	STRBUF_Delete( msg_buf );
	STRBUF_Delete( str );
	MSGMAN_Delete( man );

	GF_BGL_BmpWinOn( win );
	
}

//�J�����p�E�B���h�E�Z�b�g
static void SetCameraDebugWindow(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	//�J�����E�B���h�E�\�z
	MakeBmpList(fsys, NELEMS(DebugCameraMenuList),DebugCameraMenuList, &CameraDebugListWindowData);
	
}
//�J�������X�g�E�B���h�E�\�����^�X�N
static void CameraListDispTask(TCB_PTR tcb,void* work)
{
	BOOL flg;
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	flg = FALSE;
	if ( sys.trg & PAD_KEY_RIGHT ){
		flg = TRUE;
		if (d_work->camera_tbl_no == NELEMS(TestOrgCamera)-1){
			d_work->camera_tbl_no=0;
		}else{
			d_work->camera_tbl_no++;
		}
	}else if (sys.trg & PAD_KEY_LEFT){
		flg = TRUE;
		if (d_work->camera_tbl_no == 0){
			d_work->camera_tbl_no = NELEMS(TestOrgCamera)-1;
		}else{
			d_work->camera_tbl_no--;
		}
	}
	
	if (flg == TRUE){
		//�J�����p�����[�^�ύX
		//�J�����Z�b�g
		{
			GFC_InitCameraTDA(
				Player_VecPosPtrGet(d_work->fsys->player),
				TestOrgCamera[d_work->camera_tbl_no].Distance,		// ����
				&TestOrgCamera[d_work->camera_tbl_no].Angle,		//
				TestOrgCamera[d_work->camera_tbl_no].PerspWay,		// ���ˉh�̊p�x
				TestOrgCamera[d_work->camera_tbl_no].View,
				TRUE,
				d_work->camera);
			if (TestOrgCamera[d_work->camera_tbl_no].dummy==1){
				GFC_SetCameraClip(FX32_ONE*150, FX32_ONE*1160,d_work->camera);
			}else if(TestOrgCamera[d_work->camera_tbl_no].dummy==2){
				GFC_SetCameraClip(FX32_ONE*150, FX32_ONE*1735,d_work->camera);
			}
			GFC_CopyCameraTracePtr(d_work->fsys->camera_ptr, d_work->camera);
		}
		//�J�������\��
		DrawCameraInfo(d_work->camera,&d_work->win,d_work->camera_tbl_no);
	}

	if (sys.trg & PAD_BUTTON_B){
		//�J�������f
		GFC_CopyCamera(d_work->camera,d_work->fsys->camera_ptr);
		//�J�����폜
		GFC_FreeCamera(d_work->camera);
		//�J�����A�^�b�`
		GFC_AttachCamera(d_work->fsys->camera_ptr);
		
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		sys_FreeMemoryEz((void *)work);
		//�^�X�N����
		TCB_Delete(tcb);
		//OBJ���̓����~����
		FieldSystemProc_SeqHoldEnd();
	}
}

//�J�������E�B���h�E�\�����^�X�N
static void CameraInfoDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	if (sys.trg & PAD_BUTTON_B){
		
		//�J�����폜
		GFC_FreeCamera(d_work->camera);
		//�J�����A�^�b�`
		GFC_AttachCamera(d_work->fsys->camera_ptr);
		
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		sys_FreeMemoryEz((void *)work);
		//�^�X�N����
		TCB_Delete(tcb);
		//OBJ���̓����~����
		FieldSystemProc_SeqHoldEnd();
	}
}

//�J�������p�E�B���h�E�\�z
static void SetCameraInfoWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->camera_tbl_no = 0;
	
	d_work->fsys = fsys;
	//�J��������
	d_work->camera = GFC_AllocCamera(HEAPID_D_SAITO);
	GFC_CopyCamera(d_work->fsys->camera_ptr, d_work->camera);
	GFC_AttachCamera(d_work->camera);
	//���C�������^�X�N�ǉ�
	pTcb = TCB_Add(CameraInfoDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 14, 24, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );
	//�J�������\��
	DrawCameraInfo(d_work->camera,&d_work->win, d_work->camera_tbl_no);

	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	return;
}

//�J�������X�g�p�E�B���h�E�\�z
static void SetCameraListWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->camera_tbl_no = 0;
	
	d_work->fsys = fsys;
	//�J��������
	d_work->camera = GFC_AllocCamera(HEAPID_D_SAITO);
	{
		GFC_InitCameraTDA(
				Player_VecPosPtrGet(fsys->player),
				TestOrgCamera[0].Distance,		// ����
				&TestOrgCamera[0].Angle,		//
				TestOrgCamera[0].PerspWay,		// ���ˉh�̊p�x
				TestOrgCamera[0].View,
				TRUE,
				d_work->camera);
		GFC_CopyCameraTracePtr(d_work->fsys->camera_ptr, d_work->camera);
	}
	GFC_AttachCamera(d_work->camera);
	//���C�������^�X�N�ǉ�
	pTcb = TCB_Add(CameraListDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 14, 24, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );
	//�J�������\��
	DrawCameraInfo(d_work->camera,&d_work->win, d_work->camera_tbl_no);

	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	return;
}

//�J�������p�E�B���h�E�Z�b�g
static void SetupCameraInfoWindow(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�J�������E�B���h�E�\�z
	SetCameraInfoWindow(fsys);
}

//�J�������X�g�p�E�B���h�E�Z�b�g
static void SetupCameraListWindow(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�J�������E�B���h�E�\�z
	SetCameraListWindow(fsys);
}

//�h�ꑐ���R�[�h�\��
static void DrawSwayGrassRec(struct _FIELDSYS_WORK * fsys, GF_BGL_BMPWIN	*win)
{
	int i;
	GF_BGL_BmpWinDataFill( win, 0x0f );

	for (i=0;i<3;i++){
		SWAY_GRASS_HIST * hist;
		int chain;
		int monsno;
		hist = EncDataSave_GetSwayGrassHist( EncDataSave_GetSaveDataPtr(fsys->savedata) );
		chain = hist->SwayGrassRec[i].Chain;
		monsno = hist->SwayGrassRec[i].MonsNo;
		{
			//�|�P�������擾�̂��߁A�|�P��������
			STRBUF *name_buf;
			name_buf = MSGDAT_UTIL_GetMonsName( monsno, HEAPID_D_SAITO );

			GF_STR_PrintSimple( win, FONT_SYSTEM, name_buf, 0, 16*i, MSG_ALLPUT, NULL );
			{
				STRBUF* str = STRBUF_Create(10, HEAPID_D_SAITO);
				STRBUF_SetNumber( str, chain, 5, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
				GF_STR_PrintSimple(win, FONT_SYSTEM, str, 10*8, 16*i, MSG_ALLPUT, NULL );
				STRBUF_Delete(str);
			}
			STRBUF_Delete(name_buf);
		}
	}
	
	GF_BGL_BmpWinOn( win );
	
}

//�h�ꑐ���R�[�h�E���E�B���h�E�\�����^�X�N
static void SwayGrassInfoDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	if (sys.trg & PAD_BUTTON_B){
		
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		sys_FreeMemoryEz((void *)work);
		//�^�X�N����
		TCB_Delete(tcb);
		//OBJ���̓����~����
		FieldSystemProc_SeqHoldEnd();
	}
}

//�h�ꑐ���R�[�h�p�E�B���h�E�\�z
static void SetSwayGrassRecWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	
	d_work->fsys = fsys;
	//���C�������^�X�N�ǉ�
	pTcb = TCB_Add(SwayGrassInfoDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 14, 6, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );
	//�h�ꑐ���R�[�h�\��
	DrawSwayGrassRec(fsys, &d_work->win);

	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	return;
}

//�h�ꑐ���R�[�h�\��
static void DispSwayGrassRec(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�h�ꑐ���E�B���h�E�\�z
	SetSwayGrassRecWindow(fsys);

}

static void CameraControlTask(TCB_PTR tcb,void *work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;
	(void)CameraInput(d_work->camera);


	if ( (sys.cont & PAD_BUTTON_B) && (sys.trg & PAD_BUTTON_X) ){

		//�J�����Z�b�g
		{
			GFC_InitCameraTDA(
				Player_VecPosPtrGet(d_work->fsys->player),
				TestOrgCamera[0].Distance,		// ����
				&TestOrgCamera[0].Angle,		//
				TestOrgCamera[0].PerspWay,		// ���ˉh�̊p�x
				TestOrgCamera[0].View,
				TRUE,
				d_work->camera);

			GFC_CopyCameraTracePtr(d_work->fsys->camera_ptr, d_work->camera);
		}
	}

	if (sys.cont & PAD_BUTTON_L){
		//�J�������f
		GFC_CopyCamera(d_work->camera,d_work->fsys->camera_ptr);
		//�J�����폜
		GFC_FreeCamera(d_work->camera);
		//�J�����A�^�b�`
		GFC_AttachCamera(d_work->fsys->camera_ptr);
		//���[�N�������J��
		sys_FreeMemoryEz(d_work);
		//�^�X�N����
		TCB_Delete(tcb);
		//OBJ���̓����~����
		FieldSystemProc_SeqHoldEnd();
	}
}

static void SetCamera(TCB_PTR tcb,void *work)
{
	DEBUG_WORK_DATA *d_work;
	
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;

	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	
	d_work->fsys = wp->fsys;
	//�J��������
	d_work->camera = GFC_AllocCamera(HEAPID_D_SAITO);
	GFC_CopyCamera(d_work->fsys->camera_ptr, d_work->camera);
	GFC_AttachCamera(d_work->camera);
	
	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	//�E�B���h�E���
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�^�X�N�Z�b�g
	TCB_Add(CameraControlTask,d_work,0);

}

//-----------------------------------------------------------------------------
//	�A�N�Z�X�֐�
//-----------------------------------------------------------------------------
//�f�o�b�O���C���E�B���h�E�\�z�֐�
void DBGSAI_MapNumDebugListSet(struct _FIELDSYS_WORK * fsys)
{
	MakeBmpList(fsys, NELEMS(DebugMenuMainList), DebugMenuMainList, &MainDebugListWindowData);
}

static int DebugPlayerHeightOfs = 0;

//������ς���
static void HeightChangeTask(TCB_PTR tcb,void* work)
{
	VecFx32 *ofs;
	const VecFx32 *vec;
	
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;
	
	ofs = Player_VecDrawOffsPtrGet( d_work->fsys->player );
	vec = Player_VecPosPtrGet(d_work->fsys->player);
//	BLACT_WORK* bl_w;
//	bl_w = BLACT_WorkGet(FldBlActIdx, map3Ddata->actor[0].actorno);
	
	if (sys.trg & PAD_KEY_UP){
		OS_Printf("�f�o�b�O�F����UP\n");
		DebugPlayerHeightOfs++;
		ofs->y += (FX32_ONE/4);
//		bl_w->Matrix.y+= (FX32_ONE/4);
	}else if (sys.trg & PAD_KEY_DOWN){
		OS_Printf("�f�o�b�O�F����DOWN\n");
		DebugPlayerHeightOfs--;
		ofs->y -= (FX32_ONE/4);
//		bl_w->Matrix.y-= (FX32_ONE/4);
	}

	if (sys.trg & PAD_BUTTON_X){
		//���Z�b�g
		OS_Printf("�f�o�b�O�F�������Z�b�g\n");
		DebugPlayerHeightOfs = 0;
		ofs->y = vec->y;
		ofs->y += (FX32_ONE*16);

//		bl_w->Matrix.y = map3Ddata->actor[0].global.y;
//		bl_w->Matrix.y+=(FX32_ONE*16);
	}
	
	if (sys.trg & PAD_BUTTON_B){
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		//OBJ���̓����~����
		FieldSystemProc_SeqHoldEnd();
	}
}

//�����ύX�^�X�N�Z�b�g
static void SetPlayerHeightChangeTask(TCB_PTR tcb,void *work)
{
	DEBUG_WORK_DATA *d_work;
	
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	
	d_work->fsys = wp->fsys;	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�^�X�N�Z�b�g
	TCB_Add(HeightChangeTask,d_work,0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
#define ATTR_DISP_W_NUM	(3)
#define ATTR_DISP_H_NUM	(3)
#define ATTR_ONE_DISP_SIZE (5)
typedef struct {
	GF_BGL_BMPWIN	win;//BMP
	GF_BGL_BMPWIN	win2;//BMP
	FIELDSYS_WORK * fsys;
}ATTR_CONT;

//�A�g���r���[�g���\��
static void DispAttrInfo(ATTR_CONT *work)
{	
	GF_BGL_BmpWinDataFill( &work->win, 0x0f );
	GF_BGL_BmpWinDataFill( &work->win2, 0x0f );
	
	//���@�̈ʒu�̃A�g���r���[�g��\��
	{
		int grid_x,grid_z,height;
		int base_x,base_z;
		int x,z;
		u8 i,j;
		u8 disp_ofs_x;
		BOOL rc;
		u8 attr;
		
		MSGDATA_MANAGER* man;
		STRBUF *msg_buf;
		STRBUF* str;
		
		man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_saito_dat, HEAPID_D_SAITO);
		msg_buf = STRBUF_Create(16,HEAPID_D_SAITO);
		str = STRBUF_Create(4, HEAPID_D_SAITO);

		//���@�O���b�h���W���擾
		grid_x = Player_NowGPosXGet( work->fsys->player );
		grid_z = Player_NowGPosZGet( work->fsys->player );
		{
			VecFx32 vec;
			Player_VecPosGet( work->fsys->player, &vec );
			height = vec.y/(FX32_ONE*16);
		}

		base_x = grid_x-1;
		base_z = grid_z-1;
		
		for (i=0;i<3;i++){
			z = base_z+i;
			for(j=0;j<3;j++){
				disp_ofs_x = ATTR_ONE_DISP_SIZE*j*8;
				x = base_x+j;
				//�A�g���r���[�g�擾
				rc = GetHitAttr(work->fsys, x, z);

				if (rc){
					MSGMAN_GetString(man, D_SAITO_ATTR01 ,msg_buf);
					GF_STR_PrintSimple(&work->win, FONT_SYSTEM, msg_buf, disp_ofs_x, i*16, MSG_ALLPUT, NULL );
				}else{
					MSGMAN_GetString(man, D_SAITO_ATTR02 ,msg_buf);
					GF_STR_PrintSimple(&work->win, FONT_SYSTEM, msg_buf, disp_ofs_x, i*16, MSG_ALLPUT, NULL );
				}
				
				attr = GetAttributeLSB(work->fsys, x, z);
				STRBUF_SetHexNumber( str, attr, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
				GF_STR_PrintSimple(&work->win, FONT_SYSTEM, str, disp_ofs_x+2*8, i*16, MSG_ALLPUT, NULL );
			}
		}
			
		//���@�O���b�h����A�u���b�N���W�A�u���b�N�����[�J�����W���v�Z
		{
			int block_x,block_z;
			u8 local_x,local_z;
			u8 ofs = 6*8;
			u8 item_ofs = 3*8;
			block_x = grid_x/32;
			block_z = grid_z/32;
			local_x = grid_x%32;
			local_z = grid_z%32;
			
			MSGMAN_GetString(man, D_SAITO_ATTR03 ,msg_buf);
			GF_STR_PrintSimple(&work->win2, FONT_SYSTEM, msg_buf, 0, 0, MSG_ALLPUT, NULL );
			MSGMAN_GetString(man, D_SAITO_ATTR04 ,msg_buf);
			GF_STR_PrintSimple(&work->win2, FONT_SYSTEM, msg_buf, 0, 16, MSG_ALLPUT, NULL );
			MSGMAN_GetString(man, D_SAITO_ATTR05 ,msg_buf);
			GF_STR_PrintSimple(&work->win2, FONT_SYSTEM, msg_buf, 0, 32, MSG_ALLPUT, NULL );

			STRBUF_SetNumber( str, block_x, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(&work->win2, FONT_SYSTEM, str, ofs+0, 0, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, block_z, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(&work->win2, FONT_SYSTEM, str, ofs+item_ofs, 0, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, local_x, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(&work->win2, FONT_SYSTEM, str, ofs+0, 16, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, local_z, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(&work->win2, FONT_SYSTEM, str, ofs+item_ofs, 16, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, height, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(&work->win2, FONT_SYSTEM, str, ofs+0, 32, MSG_ALLPUT, NULL );
			
		}
		STRBUF_Delete(str);
		STRBUF_Delete( msg_buf );
		MSGMAN_Delete( man );
	}
	
	GF_BGL_BmpWinOn( &work->win );
	GF_BGL_BmpWinOn( &work->win2 );
}

//�A�g���r���[�g�m�F�R���g���[��
static void DebugCheckAttrControlTask(TCB_PTR tcb,void* work)
{
	ATTR_CONT	*wp;
	wp = (ATTR_CONT*)work;
	//���j���[�L�����Z��
	if(sys.trg & PAD_BUTTON_B){
		GF_BGL_BmpWinOff( &wp->win );
		GF_BGL_BmpWinDel( &wp->win );
		GF_BGL_BmpWinOff( &wp->win2 );
		GF_BGL_BmpWinDel( &wp->win2 );
		//���[�N�������J��
		sys_FreeMemoryEz(work);
		//�^�X�N����
		TCB_Delete(tcb);
		//OBJ���̓����~����
		FieldSystemProc_SeqHoldEnd();
		return;
	}
}

//�A�g���r���[�g�m�F
void DBGSAI_CheckAttribute(struct _FIELDSYS_WORK * fsys)
{
	ATTR_CONT *d_work;
	int size_w,size_h;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(ATTR_CONT));
	d_work->fsys = fsys;
	
	size_w = ATTR_ONE_DISP_SIZE*ATTR_DISP_W_NUM;
	size_h =  2*ATTR_DISP_H_NUM;
	
	GF_BGL_BmpWinAdd( fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0,
			size_w,size_h, 1, 1 );

	GF_BGL_BmpWinAdd( fsys->bgl,&d_work->win2,GF_BGL_FRAME3_M, 0, 18,
			6+3*2, 3*2, 1, 1+size_w*size_h );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );
	//���C�������^�X�N�ǉ�
	TCB_Add(DebugCheckAttrControlTask,d_work,0);
	//���\��
	DispAttrInfo(d_work);
}

static BOOL DebugCheckHeightGridIn(	struct _FIELDSYS_WORK * fsys,
									const int inGridX,
									const int inGridZ,
									const BOOL inRoop,
									const BOOL inDetail)
{
	u8 idx;
	u8 rc;
	int i,j;
	fx32 base_x,x,base_z,z;
	MHI_CONST_PTR  height_info;
	fx32 x_ofs,z_ofs;
	int count;
	BOOL block_result;
	int non_height_count;
	
	//�O���b�h��fx32��
	base_x = inGridX*16*FX32_ONE;
	base_z = inGridZ*16*FX32_ONE;

	idx = GetNowLocalIndex(fsys->map_cont_dat);
	height_info = GetDivMapHeightInfo(fsys->map_cont_dat,idx);
	
	{
		//�u���b�N�I�t�Z�b�g�������Z
		x_ofs = (((inGridX/32)*BLOCK_GRID_W)+(BLOCK_GRID_W/2))*16*FX32_ONE;
		z_ofs = (((inGridZ/32)*BLOCK_GRID_H)+(BLOCK_GRID_H/2))*16*FX32_ONE;
		base_x -= x_ofs;
		base_z -= z_ofs;
	}

	count = 0;
	block_result = FALSE;
	non_height_count = 0;
	for(i=0;i<16;i++){
		x = base_x+(i*FX32_ONE);
		for(j=0;j<16;j++){
			z = base_z+(j*FX32_ONE);
			rc = HC_DebugCheckHeight(x, z, height_info, inDetail);
			if (rc==1){
				if (inRoop == FALSE){
					//return TRUE;
					block_result = TRUE;
				}else{
					OS_Printf("���j�b�g�����W%d,%d�͕����̍����������Ă��܂�\n",i,j);
					count++;
				}
			}else if(rc==2){
				if (inRoop == FALSE){
					if (block_result != TRUE){
						//return FALSE;
						block_result = FALSE;
					}
				}else{
					OS_Printf("���j�b�g�����W%d,%d�͓��������𕡐������Ă��܂�\n",i,j);
				}

			}else if(rc==3){
				non_height_count++;
				if (inRoop == FALSE){
					if (block_result != TRUE){
						//return FALSE;
						block_result = FALSE;
					}
				}else{
					OS_Printf("���j�b�g�����W%d,%d�͍����������Ă��܂���\n",i,j);
				}
			}
		}
	}
	if (inRoop == FALSE){
		if (non_height_count!=256){//�P�O���b�h�S�č��������������Ƃ��ȊO
			OS_Printf("�O���b�h���ɍ����̂Ȃ��ꏊ������܂�\n");
		}
		return block_result;
	}

	if (inDetail){
		OS_Printf("�O���b�h���ɂ́A�����̍����������j�b�g��%d�ӏ����݂��܂�\n",count);
	}
	
	if (count>0){
		return TRUE;
	}else{
		return FALSE;
	}
}

static void DebugCheckHeightGrid(TCB_PTR tcb,void *work)
{
	DEBUG_WINDOW_DATA *wp = (DEBUG_WINDOW_DATA *)work;
	//�����f�o�b�O
	{
		u8 idx;
		int i,j;
		int grid_x,grid_z;
		VecFx32 base,vec;
		fx32 x_ofs,z_ofs;
		MHI_CONST_PTR  height_info;
		BOOL rc;
		
		Player_VecPosGet(wp->fsys->player, &base);

		//��_
		base.x-=(8*FX32_ONE);
		base.z-=(8*FX32_ONE);

		grid_x = Player_NowGPosXGet( wp->fsys->player );
		grid_z = Player_NowGPosZGet( wp->fsys->player );
		{
			int local_x,local_z;
			local_x = grid_x%32;
			local_z = grid_z%32;

			OS_Printf("\n//�u���b�N���O���b�h���W%d,%d�̍������`�F�b�N\n",local_x,local_z);
		}

		DebugCheckHeightGridIn(wp->fsys,
				grid_x,
				grid_z,
				TRUE, TRUE);
		
	}
	DebugWindowExit(tcb,work);
}

static void DebugCheckHeightBlock(TCB_PTR tcb,void *work)
{
	DEBUG_WINDOW_DATA *wp = (DEBUG_WINDOW_DATA *)work;
	//�����f�o�b�O
	{
		int i,j;
		int block_x,block_z;
		int base_grid_x,base_grid_z;
		BOOL rc;
		int count;
		block_x = Player_NowGPosXGet( wp->fsys->player )/BLOCK_GRID_W;
		block_z = Player_NowGPosZGet( wp->fsys->player )/BLOCK_GRID_H;

		OS_Printf("\n//�u���b�N%d,%d�̍������`�F�b�N\n",block_x,block_z);

		count = 0;
		for(i=0;i<32;i++){
			base_grid_x = block_x*32+i;
			for(j=0;j<32;j++){
				base_grid_z = block_z*32+j;
				rc = DebugCheckHeightGridIn(wp->fsys, base_grid_x, base_grid_z, FALSE, FALSE);
				if (rc){
					OS_Printf("�����Q�w�ȏ�̃O���b�h�F%d,%d\n",i,j);
					count++;
				}
			}
		}
		OS_Printf("�Q�w�ȏ�̍��������O���b�h��%d����\n",count);
	}

	DebugWindowExit(tcb,work);
}

static void SetSwayGrass(TCB_PTR tcb,void *work)
{
	DEBUG_WORK_DATA *d_work;
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	{
		u8 *charge;
		charge = EncDataSave_GetPokeSearcherCharge(EncDataSave_GetSaveDataPtr(fsys->savedata));
		(*charge)=POKESEARCHER_CHARGE_MAX;
	}
	
	//�h�ꑐ�Z�b�g
	SwayGrass_Setup(wp->fsys);
	
	DebugWindowExit(tcb,work);
}

/////////////////////////////////////////////�h�ꑐ�֘A//////////////////////////////////////////

//�h�ꑐ���C��
static void DebugWinSwayGrass(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	//�E�B���h�E�\�z
	MakeBmpList(fsys, NELEMS(DebugSwayGrassMenuList), DebugSwayGrassMenuList, &SwayDebugListWindowData);
}

//�A�j���i���o�[�\��
static void DrawChain(DEBUG_WORK_DATA *d_work)
{
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );
	STRBUF_SetNumber( d_work->StrBuf, SwayGrass_GetChain(d_work->fsys), 3, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, d_work->StrBuf, 0, 0, MSG_ALLPUT, NULL );
}

//�h�ꑐ�`�F�[���\�����^�X�N
static void ChainDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	BOOL draw;

	draw = TRUE;
	if (sys.repeat & PAD_KEY_UP){
		SwayGrass_DebugIncChain(d_work->fsys,1);
	}else if(sys.repeat & PAD_KEY_DOWN){
		SwayGrass_DebugIncChain(d_work->fsys,-1);
	}else if (sys.repeat & PAD_KEY_RIGHT){
		SwayGrass_DebugIncChain(d_work->fsys,10);
	}else if(sys.repeat & PAD_KEY_LEFT){
		SwayGrass_DebugIncChain(d_work->fsys,-10);
	}else{
		draw = FALSE;
	}

	if (draw){
		DrawChain(d_work);
	}
	
	if ((sys.trg & PAD_BUTTON_B)||(sys.trg & PAD_BUTTON_A)){
		
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);

		sys_FreeMemoryEz((void *)work);
		//�^�X�N����
		TCB_Delete(tcb);
		//OBJ���̓����~����
		FieldSystemProc_SeqHoldEnd();
	}
}

//�`�F�[���p�E�B���h�E�\�z
static void SetChainWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(10, HEAPID_D_SAITO);
	//���C�������^�X�N�ǉ�
	pTcb = TCB_Add(ChainDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 4, 2, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//�`�F�[���\��
	DrawChain(d_work);

	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	return;
}

//�`�F�[���w��E�B���h�E�Z�b�g
static void SetupSwayGrassChain(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�E�B���h�E�\�z
	SetChainWindow(fsys);
}

//�h�ꑐ���\��
static void DrawSwayGrassInfo(struct _FIELDSYS_WORK * fsys, GF_BGL_BMPWIN	*win)
{
	int i;
	GF_BGL_BmpWinDataFill( win, 0x0f );

	for (i=0;i<4;i++){
		int x,z;
		u8 tbl;
		BOOL valid,chain,rare;
		
		SwayGrass_GetGrassInfo(fsys, i,
							&x, &z, &tbl,&valid, &chain, &rare);

		{
			STRBUF* str = STRBUF_Create(10, HEAPID_D_SAITO);
			STRBUF_SetNumber( str, x%32, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(win, FONT_SYSTEM, str, 0*8, 16*i, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, z%32, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(win, FONT_SYSTEM, str, 4*8, 16*i, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, tbl, 1, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(win, FONT_SYSTEM, str, 8*8, 16*i, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, valid, 1, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(win, FONT_SYSTEM, str, 10*8, 16*i, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, chain, 1, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(win, FONT_SYSTEM, str, 12*8, 16*i, MSG_ALLPUT, NULL );
			STRBUF_SetNumber( str, rare, 1, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
			GF_STR_PrintSimple(win, FONT_SYSTEM, str, 14*8, 16*i, MSG_ALLPUT, NULL );
			STRBUF_Delete(str);
		}
	}
	
	GF_BGL_BmpWinOn( win );
	
}

//�h�ꑐ���p�E�B���h�E�\�z
static void SetSwayGrassInfoWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	
	d_work->fsys = fsys;
	//���C�������^�X�N�ǉ�
	pTcb = TCB_Add(SwayGrassInfoDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 16, 8, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );
	//�h�ꑐ���R�[�h�\��
	DrawSwayGrassInfo(fsys, &d_work->win);

	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	return;
}

//�h�ꑐ���\��
static void DispSwayGrassInfo(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�h�ꑐ���E�B���h�E�\�z
	SetSwayGrassInfoWindow(fsys);

}

/////////////////////�ނ�
extern u8 DebugFishProbFlg;
static void DrawSpFishingPoint(DEBUG_WORK_DATA *d_work);
//�ނ胁�C��
static void DebugWinFishing(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	//�E�B���h�E�\�z
	MakeBmpList(fsys, NELEMS(DebugFishingMenuList), DebugFishingMenuList, &FishingDebugListWindowData);
}

//�ފƃi���o�[�\��
static void DrawFishingRod(DEBUG_WORK_DATA *d_work)
{
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );
	STRBUF_SetNumber( d_work->StrBuf, d_work->rod, 1, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, d_work->StrBuf, 0, 0, MSG_ALLPUT, NULL );
}

//���b�h�\�����^�X�N
static void RodDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	BOOL draw;

	draw = TRUE;
	if (sys.repeat & PAD_KEY_UP){
		d_work->rod++;
		if (d_work->rod>2){
			d_work->rod = 0;
		}
	}else if(sys.repeat & PAD_KEY_DOWN){
		d_work->rod--;
		if (d_work->rod<0){
			d_work->rod = 2;
		}
	}else{
		draw = FALSE;
	}

	if (draw){
		DrawFishingRod(d_work);
	}

	if (sys.trg & PAD_BUTTON_A){
		BOOL rc;

		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);
		
		//�^�X�N����
		TCB_Delete(tcb);
		//OBJ���̓����~����
		FieldSystemProc_SeqHoldEnd();
		rc = DebugSetFishingEncount( d_work->fsys, d_work->rod );
		OS_Printf("fishing = %d\n",rc);
		
		sys_FreeMemoryEz((void *)work);	
	}else if (sys.trg & PAD_BUTTON_B){
		struct _FIELDSYS_WORK * fsys;
		fsys = d_work->fsys;
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);

		sys_FreeMemoryEz((void *)work);
		//�^�X�N����
		TCB_Delete(tcb);
		MakeBmpList(fsys, NELEMS(DebugFishingMenuList), DebugFishingMenuList, &FishingDebugListWindowData);
	}
}

//�ނ�p�E�B���h�E�\�z
static void SetFishingRodWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(2, HEAPID_D_SAITO);
	d_work->rod = 0;
	//���C�������^�X�N�ǉ�
	pTcb = TCB_Add(RodDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 2, 2, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//���b�h�\��
	DrawFishingRod(d_work);

	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	return;
}
//�ނ�Ǝw��E�B���h�E�Z�b�g
static void SetupFishingRod(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�E�B���h�E�\�z
	SetFishingRodWindow(fsys);
}

//�ނ�m���t���O�\��
static void DrawFishingProb(DEBUG_WORK_DATA *d_work)
{
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );
	STRBUF_SetNumber( d_work->StrBuf, DebugFishProbFlg, 1, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, d_work->StrBuf, 0, 0, MSG_ALLPUT, NULL );
}

//�m���t���O�\�����^�X�N
static void FishProbDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	BOOL draw;

	draw = TRUE;
	if ( (sys.trg & PAD_KEY_UP) ||
			(sys.trg & PAD_KEY_DOWN)){
		DebugFishProbFlg = (DebugFishProbFlg+1)%2;
	}else{
		draw = FALSE;
	}

	if (draw){
		DrawFishingProb(d_work);
	}

	if ( (sys.trg & PAD_BUTTON_A) ||
			(sys.trg & PAD_BUTTON_B) ){
		struct _FIELDSYS_WORK * fsys;
		fsys = d_work->fsys;
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);

		sys_FreeMemoryEz((void *)work);
		//�^�X�N����
		TCB_Delete(tcb);
		MakeBmpList(fsys, NELEMS(DebugFishingMenuList), DebugFishingMenuList, &FishingDebugListWindowData);
	}
}

//�ނ�p�E�B���h�E�\�z
static void SetFishingProbWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(2, HEAPID_D_SAITO);

	//���C�������^�X�N�ǉ�
	pTcb = TCB_Add(FishProbDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 2, 2, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//�m���t���O�\��
	DrawFishingProb(d_work);

	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	return;
}

//�ނ�m���t���O�w��E�B���h�E�Z�b�g
static void SetupFishingProb(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�E�B���h�E�\�z
	SetFishingProbWindow(fsys);
}

//����ނ�|�C���g�\�����^�X�N
static void SpFishPointDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	if ( sys.trg & PAD_BUTTON_B) {
		struct _FIELDSYS_WORK * fsys;
		fsys = d_work->fsys;
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);

		sys_FreeMemoryEz((void *)work);
		//�^�X�N����
		TCB_Delete(tcb);
		MakeBmpList(fsys, NELEMS(DebugFishingMenuList), DebugFishingMenuList, &FishingDebugListWindowData);
	}
}

//����ނ�|�C���g�E�B���h�E�\�z
static void SetSpFishingPointWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(32, HEAPID_D_SAITO);

	//���C�������^�X�N�ǉ�
	pTcb = TCB_Add(SpFishPointDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 8, 10, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//�|�C���g�\��
	DrawSpFishingPoint(d_work);

	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	return;
}
//����ނ�|�C���g�E�B���h�E�Z�b�g
static void SetupSpFishingPoint(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�E�B���h�E�\�z
	SetSpFishingPointWindow(fsys);
}

//����ނ�|�C���g�\��
static void DrawSpFishingPoint(DEBUG_WORK_DATA *d_work)
{
	int pos[8];
	u32 rnd;
	STRBUF *str;
	MSGDATA_MANAGER* man;
	
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_saito_dat, HEAPID_D_SAITO);
	str = d_work->StrBuf;

	{

		DEBUGSpFishing_GetPoint(d_work->fsys, pos, &rnd);
		STRBUF_SetHexNumber(str, rnd, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 0*16, MSG_ALLPUT, NULL );
		
		STRBUF_SetNumber(str, pos[0], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 1*16, MSG_ALLPUT, NULL );
		STRBUF_SetNumber(str, pos[1], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 4*8, 1*16, MSG_ALLPUT, NULL );

		STRBUF_SetNumber(str, pos[2], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 2*16, MSG_ALLPUT, NULL );
		STRBUF_SetNumber(str, pos[3], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 4*8, 2*16, MSG_ALLPUT, NULL );

		STRBUF_SetNumber(str, pos[4], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 3*16, MSG_ALLPUT, NULL );
		STRBUF_SetNumber(str, pos[5], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 4*8, 3*16, MSG_ALLPUT, NULL );

		STRBUF_SetNumber(str, pos[6], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 4*16, MSG_ALLPUT, NULL );
		STRBUF_SetNumber(str, pos[7], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 4*8, 4*16, MSG_ALLPUT, NULL );
	}

	MSGMAN_Delete( man );

	GF_BGL_BmpWinOn( &d_work->win );
}


/////////////////////////////////////////////////////////////////////////////////////////
//�ړ��|�P����
static void SetMovePokeInfoWindow(struct _FIELDSYS_WORK * fsys);
static void DrawMovePokeInfo(DEBUG_WORK_DATA *d_work);
static void MovePokeInfoDispTask(TCB_PTR tcb,void* work);

static void SetEntryMovePokeWindow(struct _FIELDSYS_WORK * fsys);
static void DrawMovePokeName(DEBUG_WORK_DATA *d_work);
static void EntryMovePokeTask(TCB_PTR tcb,void* work);

static void SetMovePokeZoneChgWin(struct _FIELDSYS_WORK * fsys, const u16 inPos);
static void DrawMovePokeZone(DEBUG_WORK_DATA *d_work);
static void MovePokeZoneDispTask(TCB_PTR tcb,void* work);

//���C��
static void DebugWinMovePoke(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	//�E�B���h�E�\�z
	MakeBmpList(fsys, NELEMS(DebugMovePokeMenuList), DebugMovePokeMenuList, &MovePokeDebugListWindowData);
}

//���\���E�B���h�E�Z�b�g
static void SetupMovePokeInfo(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�E�B���h�E�\�z
	SetMovePokeInfoWindow(fsys);
}

//�ړ��|�P�������E�B���h�E�\�z
static void SetMovePokeInfoWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(32, HEAPID_D_SAITO);
	d_work->rod = 0;
	d_work->MovePokeInfoNo = 0;
	//���C�������^�X�N�ǉ�
	pTcb = TCB_Add(MovePokeInfoDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 16, 18, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//���\��
	DrawMovePokeInfo(d_work);

	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	return;
}

//�ړ��|�P�������\��
static void DrawMovePokeInfo(DEBUG_WORK_DATA *d_work)
{
	STRBUF *str;
	STRBUF *msg_buf;
	MSGDATA_MANAGER* man;
	MPD_PTR mpd;
	ENC_SV_PTR data;
	
	int poke_name_list[MOVE_POKE_MAX] = {	D_SAITO_MP_AI,
											D_SAITO_MP_MUUBASU,
											D_SAITO_MP_DAAKU	};	//�A�C�A���[�o�X�A�_�[�N
	
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_saito_dat, HEAPID_D_SAITO);
	str = d_work->StrBuf;
	msg_buf = d_work->StrBuf;

	//�Z�[�u�f�[�^�擾
	data = EncDataSave_GetSaveDataPtr(d_work->fsys->savedata);
	mpd = EncDataSave_GetMovePokeDataPtr(data, d_work->MovePokeInfoNo);


	{
		int zone_id = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_ZONE_ID);
		int monsno = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_MONSNO);
		u32 pow_rnd = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_POW_RND);
		u32 per_rnd = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_PER_RND);
		u8 hp = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_HP);
		u8 lv = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_LV);
		u8 cond = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_COND);
		u8 enc = EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_ENC);

		//�|�P������
		MSGMAN_GetString(man, poke_name_list[d_work->MovePokeInfoNo] ,msg_buf);		
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, msg_buf, 1*8, 0, MSG_ALLPUT, NULL );
		//�����X�^�[�i���o�[
		STRBUF_SetNumber(str, monsno, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 1*16, MSG_ALLPUT, NULL );
		//���x��
		STRBUF_SetNumber(str, lv, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 2*16, MSG_ALLPUT, NULL );
		//HP
		STRBUF_SetNumber(str, hp, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 3*16, MSG_ALLPUT, NULL );
		//�p���[����
		STRBUF_SetHexNumber(str, pow_rnd, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 4*16, MSG_ALLPUT, NULL );
		//������
		STRBUF_SetHexNumber(str, per_rnd, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 5*16, MSG_ALLPUT, NULL );
		//���
		STRBUF_SetNumber(str, cond, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 6*16, MSG_ALLPUT, NULL );
		//�ꏊ
		STRBUF_SetNumber(str, zone_id, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 7*16, MSG_ALLPUT, NULL );
		PNC_GetPlaceNameFromZoneID(zone_id, HEAPID_FIELD, msg_buf);
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, msg_buf, 4*8, 7*16, MSG_ALLPUT, NULL );
		//�G���J�E���g�t���O
		STRBUF_SetNumber(str, enc, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 8*16, MSG_ALLPUT, NULL );

		OS_Printf("pow=%u\n",pow_rnd);
		OS_Printf("per=%u\n",per_rnd);
	}
	
	MSGMAN_Delete( man );

	GF_BGL_BmpWinOn( &d_work->win );
}

//�ړ��|�P�������\���^�X�N
static void MovePokeInfoDispTask(TCB_PTR tcb,void* work)
{
	BOOL flg;
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	flg = FALSE;
	if ( sys.trg & PAD_KEY_RIGHT ){
		flg = TRUE;
		if (d_work->MovePokeInfoNo == MOVE_POKE_MAX-1){
			d_work->MovePokeInfoNo = 0;
		}else{
			d_work->MovePokeInfoNo++;
		}
	}else if (sys.trg & PAD_KEY_LEFT){
		flg = TRUE;
		if (d_work->MovePokeInfoNo == 0){
			d_work->MovePokeInfoNo = MOVE_POKE_MAX-1;
		}else{
			d_work->MovePokeInfoNo--;
		}
	}
	
	if (flg == TRUE){
		//�ړ��|�P�������\��
		DrawMovePokeInfo(d_work);
	}

	if (sys.trg & PAD_BUTTON_B){
		struct _FIELDSYS_WORK * fsys;
		fsys = d_work->fsys;	
		
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);

		sys_FreeMemoryEz((void *)work);
		//�^�X�N����
		TCB_Delete(tcb);
		//�ړ��|�P�������j���[���C����
		MakeBmpList(fsys, NELEMS(DebugMovePokeMenuList), DebugMovePokeMenuList, &MovePokeDebugListWindowData);
	}
}

static void SetupEntryMovePoke(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�E�B���h�E�\�z
	SetEntryMovePokeWindow(fsys);
}

//�ړ��|�P�����G���g���E�B���h�E�\�z
static void SetEntryMovePokeWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(16, HEAPID_D_SAITO); //�ړ��|�P��������\��
	d_work->rod = 0;
	d_work->MovePokeInfoNo = 0;
	//���C�������^�X�N�ǉ�
	pTcb = TCB_Add(EntryMovePokeTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 6, 2, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//���\��
	DrawMovePokeName(d_work);

	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	return;
}

//�ړ��|�P�������\��
static void DrawMovePokeName(DEBUG_WORK_DATA *d_work)
{
	MSGDATA_MANAGER* man;
	
	int poke_name_list[MOVE_POKE_MAX] = {	D_SAITO_MP_AI,
											D_SAITO_MP_MUUBASU,
											D_SAITO_MP_DAAKU	};	//�A�C�A���[�o�X�A�_�[�N
	
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_saito_dat, HEAPID_D_SAITO);

	//�|�P������
	MSGMAN_GetString(man, poke_name_list[d_work->MovePokeInfoNo] ,d_work->StrBuf);		
	GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, d_work->StrBuf, 1*8, 0, MSG_ALLPUT, NULL );
	
	MSGMAN_Delete( man );

	GF_BGL_BmpWinOn( &d_work->win );
}

//�G���g���ړ��|�P�����I���^�X�N
static void EntryMovePokeTask(TCB_PTR tcb,void* work)
{
	BOOL flg;
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	flg = FALSE;
	if ( sys.trg & PAD_KEY_RIGHT ){
		flg = TRUE;
		if (d_work->MovePokeInfoNo == MOVE_POKE_MAX-1){
			d_work->MovePokeInfoNo = 0;
		}else{
			d_work->MovePokeInfoNo++;
		}
	}else if (sys.trg & PAD_KEY_LEFT){
		flg = TRUE;
		if (d_work->MovePokeInfoNo == 0){
			d_work->MovePokeInfoNo = MOVE_POKE_MAX-1;
		}else{
			d_work->MovePokeInfoNo--;
		}
	}
	
	if (flg == TRUE){
		//�ړ��|�P�������\��
		DrawMovePokeName(d_work);
	}
	
	if (sys.trg & PAD_BUTTON_A){
		//�G���g��
		MP_AddMovePoke(d_work->fsys->savedata, d_work->MovePokeInfoNo);
		Snd_SePlay( SEQ_SE_DP_SELECT );		//�o�^������炵�Ƃ�
		
	}else if (sys.trg & PAD_BUTTON_B){
		struct _FIELDSYS_WORK * fsys;
		fsys = d_work->fsys;	
		
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		sys_FreeMemoryEz((void *)work);
		//�^�X�N����
		TCB_Delete(tcb);
		//�ړ��|�P�������j���[���C����
		MakeBmpList(fsys, NELEMS(DebugMovePokeMenuList), DebugMovePokeMenuList, &MovePokeDebugListWindowData);
	}
}

//�ړ��|�P���������C��
static void DebugWinMovePokeName(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	//�E�B���h�E�\�z
	MakeBmpList(fsys, NELEMS(DebugMovePokeNameList), DebugMovePokeNameList, &MovePokeNameDebugListWindowData);
}

//�]�[���ύX�E�B���h�E�Z�b�g
static void SetupMovePokeZoneChgWin(TCB_PTR tcb,void *work)
{
	u16 pos;
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������(���[�N�͎c��)
	FreeDebugWindowNoFreeMem(tcb,work);
	pos = wp->debug_cursor;
	//���[�N�������J��
	sys_FreeMemoryEz(work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�E�B���h�E�\�z
	SetMovePokeZoneChgWin(fsys,pos);
}

//�ړ��|�P�����]�[���E�B���h�E�\�z
static void SetMovePokeZoneChgWin(struct _FIELDSYS_WORK * fsys, const u16 inPos)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->MovePokeInfoNo = inPos;
	{
		ENC_SV_PTR data = EncDataSave_GetSaveDataPtr(fsys->savedata);
		if ( EncDataSave_IsMovePokeValid(data, d_work->MovePokeInfoNo) ){
			d_work->zone_idx = EncDataSave_GetMovePokeZoneIdx(data, d_work->MovePokeInfoNo);
		}else{
			d_work->zone_idx = LOCATION_MAX;
		}
	}
	d_work->StrBuf = STRBUF_Create(32, HEAPID_D_SAITO); //�]�[������\��
	//���C�������^�X�N�ǉ�
	pTcb = TCB_Add(MovePokeZoneDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 18, 2, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//���\��
	DrawMovePokeZone(d_work);

	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	return;
}

//�ړ��|�P�����]�[���\��
static void DrawMovePokeZone(DEBUG_WORK_DATA *d_work)
{
	int zone_id;
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );
	
	//�]�[�����擾
	if ((d_work->zone_idx>=0)&&(d_work->zone_idx<LOCATION_MAX)){
		zone_id = MP_GetMovePokeZone(d_work->zone_idx);
	}else{
		zone_id = 0;
	}
	PNC_GetPlaceNameFromZoneID(zone_id, HEAPID_FIELD, d_work->StrBuf);
	GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, d_work->StrBuf, 0, 0, MSG_ALLPUT, NULL );
}

//�ړ��|�P�����]�[���\�����^�X�N
static void MovePokeZoneDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	BOOL draw;

	draw = TRUE;
	if (sys.repeat & PAD_KEY_UP){
		d_work->zone_idx++;
		if (d_work->zone_idx>=LOCATION_MAX){
			d_work->zone_idx = 0;
		}
	}else if(sys.repeat & PAD_KEY_DOWN){
		d_work->zone_idx--;
		if (d_work->zone_idx<0){
			d_work->zone_idx = LOCATION_MAX-1;
		}
	}else{
		draw = FALSE;
	}

	if (draw){
		DrawMovePokeZone(d_work);
	}

	if ( sys.trg & PAD_BUTTON_A ){
		struct _FIELDSYS_WORK * fsys;
		fsys = d_work->fsys;
		Snd_SePlay( SEQ_SE_DP_SELECT );		//�ꏊ�ύX������炵�Ƃ�
		//�ꏊ�ύX
		MP_DebugUpdateData( EncDataSave_GetSaveDataPtr(fsys->savedata),
							d_work->MovePokeInfoNo, d_work->zone_idx);

		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);
		
		//�^�X�N����
		TCB_Delete(tcb);
		sys_FreeMemoryEz((void *)work);
		//�ړ��|�P�������j���[���C����
		MakeBmpList(fsys, NELEMS(DebugMovePokeMenuList), DebugMovePokeMenuList, &MovePokeDebugListWindowData);
	}else if(sys.trg & PAD_BUTTON_B){
		struct _FIELDSYS_WORK * fsys;
		fsys = d_work->fsys;

		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);
		
		//�^�X�N����
		TCB_Delete(tcb);
		sys_FreeMemoryEz((void *)work);
		//�ړ��|�P�������j���[���C����
		MakeBmpList(fsys, NELEMS(DebugMovePokeMenuList), DebugMovePokeMenuList, &MovePokeDebugListWindowData);
	}
}

//////////////////////////////////////////////////////////////////////////////
static void SetGeneZoneInfoWin(struct _FIELDSYS_WORK * fsys);
static void DrawGeneZone(DEBUG_WORK_DATA *d_work);
static void GeneInfoDispTask(TCB_PTR tcb,void* work);
//��ʔ���
static void DebugGenerate(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	//�E�B���h�E�\�z
	MakeBmpList(fsys, NELEMS(DebugGeneMenuList), DebugGeneMenuList, &GeneDebugListWindowData);	
}

//��ʔ������\���Z�b�g�A�b�v
static void SetupGeneZoneInfoWin(TCB_PTR tcb,void *work)
{
	u16 pos;
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�E�B���h�E�\�z
	SetGeneZoneInfoWin(fsys);
}

//��ʔ����J�n
static void DebugStartGenerate(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//OBJ���̓����~����
	FieldSystemProc_SeqHoldEnd();
	//��ʔ����J�n
	EncDataSave_StartGenerate( fsys->savedata );
	Snd_SePlay( SEQ_SE_DP_SELECT );		//������������炵�Ƃ�
}

//��ʔ������\���Z�b�g�A�b�v
static void SetGeneZoneInfoWin(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(32, HEAPID_D_SAITO); //�]�[������\��
	//���C�������^�X�N�ǉ�
	pTcb = TCB_Add(GeneInfoDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 18, 4, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//���\��
	DrawGeneZone(d_work);

	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	return;
}

//��ʔ����ꏊ�\��
static void DrawGeneZone(DEBUG_WORK_DATA *d_work)
{
	ENC_SV_PTR data;
	MSGDATA_MANAGER* man;

	int zone_id;
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_saito_dat, HEAPID_D_SAITO);

	data = EncDataSave_GetSaveDataPtr(d_work->fsys->savedata);
	
	//�]�[�����擾
	zone_id = GenerateZone_GetZone( EncDataSave_GetRandSeed(data,  ENC_RND_SEED_GENERATE) );
	PNC_GetPlaceNameFromZoneID(zone_id, HEAPID_FIELD, d_work->StrBuf);
	GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, d_work->StrBuf, 0, 0, MSG_ALLPUT, NULL );
	if(EncDataSave_IsGenerate( data )){
		MSGMAN_GetString(man, D_SAITO_GENE_ON ,d_work->StrBuf);		
	}else{
		MSGMAN_GetString(man, D_SAITO_GENE_OFF ,d_work->StrBuf);
	}
	GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, d_work->StrBuf, 0, 16, MSG_ALLPUT, NULL );
	MSGMAN_Delete( man );
}

//�����ꏊ�\�����^�X�N
static void GeneInfoDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = (DEBUG_WORK_DATA *)work;

	if (sys.trg & PAD_BUTTON_B){
		
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		sys_FreeMemoryEz((void *)work);
		//�^�X�N����
		TCB_Delete(tcb);
		//��ʔ������C��
		MakeBmpList(d_work->fsys, NELEMS(DebugGeneMenuList), DebugGeneMenuList, &GeneDebugListWindowData);
	}
}

////////////////////////////////////////////////////////////////////
static void DrawSafariInfo(DEBUG_WORK_DATA *d_work);
static void SetSafariInfoWindow(struct _FIELDSYS_WORK * fsys);
static void SafariInfoDispTask(TCB_PTR tcb,void* work);

static void DebugSafari(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();

	
	//�E�B���h�E�\�z
	SetSafariInfoWindow(fsys);
}

//�T�t�@�����E�B���h�E�\�z
static void SetSafariInfoWindow(struct _FIELDSYS_WORK * fsys)
{
	
	DEBUG_WORK_DATA *d_work = NULL;
	TCB_PTR	pTcb = NULL;
	d_work = sys_AllocMemory(HEAPID_D_SAITO,sizeof(DEBUG_WORK_DATA));
	d_work->fsys = fsys;
	d_work->StrBuf = STRBUF_Create(32, HEAPID_D_SAITO);
	d_work->rod = 0;
	d_work->MovePokeInfoNo = 0;
	d_work->SafariArea = 0;
	//���C�������^�X�N�ǉ�
	pTcb = TCB_Add(SafariInfoDispTask,d_work,0);

	GF_BGL_BmpWinAdd( d_work->fsys->bgl,&d_work->win,GF_BGL_FRAME3_M, 0, 0, 10, 6, 1, 1 );
	
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 16<<1, HEAPID_D_SAITO );

	//���\��
	DrawSafariInfo(d_work);

	return;
}

//�T�t�@�����\���^�X�N
static void SafariInfoDispTask(TCB_PTR tcb,void* work)
{
	DEBUG_WORK_DATA *d_work = work;

	BOOL draw = FALSE;
	if (sys.trg & PAD_KEY_UP){
		draw = TRUE;
		d_work->SafariArea = (d_work->SafariArea+1)%6;
	}else if (sys.trg & PAD_KEY_DOWN){
		draw = TRUE;
		if (d_work->SafariArea != 0){
			d_work->SafariArea--;
		}else {
			d_work->SafariArea = 5;
		}
	}

	if (draw){
		DrawSafariInfo(d_work);
	}

	
	if (sys.trg & PAD_BUTTON_B){
		struct _FIELDSYS_WORK * fsys;
		fsys = d_work->fsys;	
		
		GF_BGL_BmpWinOff( &d_work->win );
		GF_BGL_BmpWinDel( &d_work->win );

		STRBUF_Delete(d_work->StrBuf);

		sys_FreeMemoryEz((void *)work);
		//�^�X�N����
		TCB_Delete(tcb);
		//OBJ���̓����~����
		FieldSystemProc_SeqHoldEnd();
	}

}

//�T�t�@�����\��
static void DrawSafariInfo(DEBUG_WORK_DATA *d_work)
{
	STRBUF *str;
	MSGDATA_MANAGER* man;
	
	GF_BGL_BmpWinDataFill( &d_work->win, 0x0f );

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_saito_dat, HEAPID_D_SAITO);
	str = d_work->StrBuf;

	{
		u32 seed;
		int idx1;
		int mons1;
		
		seed = EncDataSave_GetRandSeed(
								EncDataSave_GetSaveDataPtr(d_work->fsys->savedata),ENC_RND_SEED_SAFARI);
		//�T�t�@������
		STRBUF_SetHexNumber(str, seed, 8, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 0*16, MSG_ALLPUT, NULL );
		
		//�G���g���e�[�u���C���f�b�N�X�\��
		SafariEnc_DebugGetSafariTbl(seed,
									ZukanWork_GetZenkokuZukanFlag(
										SaveData_GetZukanWork(GameSystem_GetSaveData(d_work->fsys))),
									d_work->SafariArea,
									&idx1, &mons1);
		STRBUF_SetNumber(str, d_work->SafariArea, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 1*16, MSG_ALLPUT, NULL );

		STRBUF_SetNumber(str, idx1, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 1*8, 2*16, MSG_ALLPUT, NULL );

		STRBUF_SetNumber(str, mons1, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&d_work->win, FONT_SYSTEM, str, 4*8, 2*16, MSG_ALLPUT, NULL );
	
	}

	MSGMAN_Delete( man );

	GF_BGL_BmpWinOn( &d_work->win );
}

//AGB
static void DebugSetAgbVer(TCB_PTR tcb,void *work)
{
	struct _FIELDSYS_WORK * fsys;
	DEBUG_WINDOW_DATA *wp;
	wp = (DEBUG_WINDOW_DATA *)work;
	fsys = wp->fsys;
	
	//���C���E�B���h�E������
	FreeDebugWindow(tcb,work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//�C�x���g�t�b�N
	FieldSystemProc_SeqHold();
	//�E�B���h�E�\�z
	MakeBmpList(fsys, NELEMS(DebugAgbMenuList), DebugAgbMenuList, &AgbDebugListWindowData);
}

//�`�f�a�X���b�g�o�[�W�����ύX
static void DebugAgbVer(TCB_PTR tcb,void *work)
{
	DEBUG_WINDOW_DATA *wp;
	//���C���E�B���h�E������(���[�N�͎c��)
	FreeDebugWindowNoFreeMem(tcb,work);
	
	wp = (DEBUG_WINDOW_DATA *)work;

	switch(wp->debug_cursor){
	case 0:
		sys.AgbCasetteVersion = 0;
		break;
	case 1:
		sys.AgbCasetteVersion = VERSION_SAPPHIRE;
		break;
	case 2:
		sys.AgbCasetteVersion = VERSION_RUBY;
		break;
	case 3:
		sys.AgbCasetteVersion = VERSION_EMERALD;
		break;
	case 4:
		sys.AgbCasetteVersion = VERSION_RED;
		break;
	case 5:
		sys.AgbCasetteVersion = VERSION_GREEN;
		break;
	}

	OS_Printf("ver:%d\n",sys.AgbCasetteVersion);

	Snd_SePlay( SEQ_SE_DP_SELECT );		//������������炵�Ƃ�

	//���[�N�������J��
	sys_FreeMemoryEz(work);
	//���C���E�B���h�E�^�X�N����
	TCB_Delete(tcb);
	//OBJ���̓����~����
	FieldSystemProc_SeqHoldEnd();
}

#endif	//#ifdef PM_DEBUG
