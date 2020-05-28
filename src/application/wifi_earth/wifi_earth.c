//============================================================================================
/**
 *	
 */
//============================================================================================
#include "common.h"

#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "savedata/savedata_def.h"
#include "savedata/config.h"

#define __WIFIEARTH_H_GLOBAL__
#include "application/wifi_earth.h"

#include "system/lib_pack.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/fontproc.h"
#include "msgdata/msg.naix"
#include "system/pm_str.h"
#include "system/palanm.h"
#include "system/wipe.h"
#include "system/window.h"
#include "system/arc_util.h"
#include "system/snd_tool.h"
#include "system/wordset.h"

#include "msgdata/msg_earth.h"
#include "msgdata/msg_wifi_place_msg_world.h"
#include "savedata/wifihistory.h"
#include "wifi_earth_place.naix"
#include "wifi_earth.naix"

#include "application/wifi_country.h"

//============================================================================================
//	�萔��`
//============================================================================================
//#define WIFI_ERATH_DEBUG

//�n�_�o�^�ő吔
#define WORLD_PLACE_NUM_MAX	(0x400)	//���������P�O�O�O�����炢�Ƃ�

//���b�Z�[�W�o�b�t�@�T�C�Y
#define EARTH_STRBUF_SIZE	(0x400)
#define EARTH_NAME_SIZE		(64)

//�a�f�����p���b�g
#define EARTH_NULL_PALETTE		(0x4753)

//�a�f�R���g���[���萔
#define EARTH_TEXT_PLANE		(GF_BGL_FRAME2_S)
#define EARTH_ICON_PLANE		(GF_BGL_FRAME2_M)
#define EARTH_BACK_S_PLANE		(GF_BGL_FRAME3_S)
#define EARTH_BACK_M_PLANE		(GF_BGL_FRAME3_M)
#define PALSIZE					(2*16)
#define DOTSIZE					(8)

// �p���b�g�]���ʒu
#define	EARTH_BACK_PAL			(0)	//�S�{��
#define	EARTH_SYSFONT_PAL		(4)
#define EARTH_ICONWIN_PAL		(5)
#define EARTH_TALKWIN_PAL		(6)
#define EARTH_MENUWIN_PAL		(7)

// ��b�E�B���h�E�L�����iwindow.h�Q�Ɓj
#define EARTH_TALKWINCHR_SIZ	(TALK_WIN_CGX_SIZ)
#define EARTH_TALKWINCHR_NUM	(512-EARTH_TALKWINCHR_SIZ)

// ���j���[�E�B���h�E�L�����iwindow.h�Q�Ɓj
#define EARTH_MENUWINCHR_SIZ	(MENU_WIN_CGX_SIZ)
#define EARTH_MENUWINCHR_NUM	(EARTH_TALKWINCHR_NUM - EARTH_MENUWINCHR_SIZ)

// ���b�Z�[�W�E�B���h�E�ifldbmp.h�Q�ƁA�b�f�w�ȊO�t�B�[���h�Ɠ����F�R�����g�͐��l�j
#define	EARTH_MSG_WIN_PX		(2)
#define	EARTH_MSG_WIN_PY		(19)
#define	EARTH_MSG_WIN_SX		(27)
#define	EARTH_MSG_WIN_SY		(4)
#define	EARTH_MSG_WIN_PAL		(EARTH_SYSFONT_PAL)
#define	EARTH_MSG_WIN_CGX		(EARTH_MENUWINCHR_NUM-(EARTH_MSG_WIN_SX*EARTH_MSG_WIN_SY))

// �͂�/�������E�B���h�E�ifldbmp.h�Q�ƁA�b�f�w�ȊO�t�B�[���h�Ɠ����F�R�����g�͐��l�j
#define	EARTH_YESNO_WIN_PX		(25)
#define	EARTH_YESNO_WIN_PY		(13)
#define	EARTH_YESNO_WIN_SX		(6)
#define	EARTH_YESNO_WIN_SY		(4)
#define	EARTH_YESNO_WIN_PAL		(EARTH_SYSFONT_PAL)
#define	EARTH_YESNO_WIN_CGX		(EARTH_MSG_WIN_CGX-(EARTH_YESNO_WIN_SX*EARTH_YESNO_WIN_SY))

// ���C�����j���[�E�B���h�E
#define	EARTH_MENU_WIN_PX		(19)
#define	EARTH_MENU_WIN_PY		(11)
#define	EARTH_MENU_WIN_SX		(12)
#define	EARTH_MENU_WIN_SY		(6)
#define	EARTH_MENU_WIN_PAL		(EARTH_SYSFONT_PAL)
#define	EARTH_MENU_WIN_CGX		(EARTH_MSG_WIN_CGX-(EARTH_MENU_WIN_SX*EARTH_MENU_WIN_SY))

// �����X�g�E�B���h�E
#define	EARTH_PLACE_WIN_PX		(3)
#define	EARTH_PLACE_WIN_PY		(2)
#define	EARTH_PLACE_WIN_SX		(26)
#define	EARTH_PLACE_WIN_SY		(14)
#define	EARTH_PLACE_WIN_PAL		(EARTH_SYSFONT_PAL)
#define	EARTH_PLACE_WIN_CGX		(EARTH_MSG_WIN_CGX-(EARTH_PLACE_WIN_SX*EARTH_PLACE_WIN_SY))

// ���E�B���h�E
#define	EARTH_INFO_WIN_PX		(2)
#define	EARTH_INFO_WIN_PY		(1)
#define	EARTH_INFO_WIN_SX		(27)
#define	EARTH_INFO_WIN_SY		(6)
#define	EARTH_INFO_WIN_PAL		(EARTH_SYSFONT_PAL)
#define	EARTH_INFO_WIN_CGX		(EARTH_YESNO_WIN_CGX-(EARTH_INFO_WIN_SX*EARTH_INFO_WIN_SY))

// �A�C�R���E�B���h�E
#define	EARTH_ICON_WIN_PX		(25)
#define	EARTH_ICON_WIN_PY		(21)
#define	EARTH_ICON_WIN_SX		(6)
#define	EARTH_ICON_WIN_SY		(2)
#define	EARTH_ICON_WIN_PAL		(EARTH_SYSFONT_PAL)
#define	EARTH_ICON_WIN_CGX		(EARTH_MENUWINCHR_NUM-(EARTH_ICON_WIN_SX*EARTH_ICON_WIN_SY))

//�n�����f����������`
#define INIT_EARTH_TRANS_XVAL	(0)
#define INIT_EARTH_TRANS_YVAL	(0)
#define INIT_EARTH_TRANS_ZVAL	(0)
#define INIT_EARTH_SCALE_XVAL	(FX32_ONE)
#define INIT_EARTH_SCALE_YVAL	(FX32_ONE)
#define INIT_EARTH_SCALE_ZVAL	(FX32_ONE)
#define INIT_EARTH_ROTATE_XVAL	(0x1980)	//�������f�t�H���g�ʒu�ɂ���
#define INIT_EARTH_ROTATE_YVAL	(0xcfe0)	//�������f�t�H���g�ʒu�ɂ���
#define INIT_EARTH_ROTATE_ZVAL	(0)

//�J������������`
#define INIT_CAMERA_TARGET_XVAL	(0)
#define INIT_CAMERA_TARGET_YVAL	(0)
#define INIT_CAMERA_TARGET_ZVAL	(0)
#define INIT_CAMERA_POS_XVAL	(0)
#define INIT_CAMERA_POS_YVAL	(0)
#define INIT_CAMERA_POS_ZVAL	(0x128000)
#define INIT_CAMERA_DISTANCE_NEAR	(0x050000)
#define INIT_CAMERA_DISTANCE_FAR	(0x128000)
#define INIT_CAMERA_PERSPWAY	(0x05c1)
#define INIT_CAMERA_CLIP_NEAR	(0)
#define INIT_CAMERA_CLIP_FAR	(FX32_ONE*100)
#define CAMERA_ANGLE_MIN		(-0x4000+0x200)
#define CAMERA_ANGLE_MAX		(0x4000-0x200)

//���C�g��������`
#define USE_LIGHT_NUM			(0)
#define LIGHT_VECDEF			(FX32_ONE-1)
#define INIT_LIGHT_ANGLE_XVAL	(0)
#define INIT_LIGHT_ANGLE_YVAL	(0)
#define INIT_LIGHT_ANGLE_ZVAL	(-LIGHT_VECDEF)

//���쏈���p�萔
#define CAMERA_MOVE_SPEED_NEAR	(0x20)	//�J�����ߋ������㉺���E�ړ��X�s�[�h	
#define CAMERA_MOVE_SPEED_FAR	(0x200)	//�J�������������㉺���E�ړ��X�s�[�h
#define CAMERA_INOUT_SPEED	(0x8000)	//�J�������߈ړ��X�s�[�h
#define MARK_SCALE_INCDEC	(0x80)		//�n�_�}�[�N���߈ړ����g�k�䗦
#define EARTH_LIMIT_ROTATE_XMIN	(0x1300)	//���{�g��n�}�̏c��]���~�b�g�����i����j
#define EARTH_LIMIT_ROTATE_XMAX	(0x2020)	//���{�g��n�}�̏c��]���~�b�g����i�k�C���t���j
#define EARTH_LIMIT_ROTATE_YMIN	(0xcc80)	//���{�g��n�}�̉���]���~�b�g�����i�k�C�����H�j
#define EARTH_LIMIT_ROTATE_YMAX	(0xd820)	//���{�g��n�}�̉���]���~�b�g����i����j

//���C���֐��V�[�P���X�i���o�[��`
enum{
	EARTHDEMO_SEQ_MODELLOAD = 0,					//���f���f�[�^���[�h
	EARTHDEMO_SEQ_DISPON,							//�`��n�m
	EARTHDEMO_SEQ_WELCOME_MSG,						//�u�悤�����v
	EARTHDEMO_SEQ_MAINMENU,							//���C�����j���[�ݒ�
	EARTHDEMO_SEQ_MAINMENU_SELECT,					//���C�����j���[�I�����[�h
	EARTHDEMO_SEQ_REGISTRATIONMENU,					//�o�^���j���[�ݒ�
	EARTHDEMO_SEQ_REGISTRATIONMENU_SELECT,			//�o�^���j���[�I�����[�h
	EARTHDEMO_SEQ_REGISTRATIONLIST_NATION,			//���ʓo�^���X�g�ݒ�
	EARTHDEMO_SEQ_REGISTRATIONLIST_NATION_SELECT,	//���ʓo�^���X�g�I�����[�h
	EARTHDEMO_SEQ_REGISTRATIONLIST_AREA,			//�n��ʓo�^���X�g�ݒ�
	EARTHDEMO_SEQ_REGISTRATIONLIST_AREA_SELECT,		//�n��ʓo�^���X�g�I�����[�h
	EARTHDEMO_SEQ_FINAL_REGISTRATION,				//�o�^�ŏI�m�F�ݒ�
	EARTHDEMO_SEQ_FINAL_REGISTRATION_YESNO,			//�o�^�ŏI�m�F
	EARTHDEMO_SEQ_FINAL_REGISTRATION_SELECT,		//�o�^�ŏI�m�F�I�����[�h
	EARTHDEMO_SEQ_EARTH_DISPON,						//�R�c�n���V���[�h�n�m
	EARTHDEMO_SEQ_MOVE_EARTH,						//���C������
	EARTHDEMO_SEQ_MOVE_CAMERA,						//�J�������߈ړ�
	EARTHDEMO_SEQ_END,								//�I�������J�n
	EARTHDEMO_SEQ_EXIT,								//�I��
};

//���b�Z�[�W�֐��V�[�P���X�i���o�[��`
enum{
	MSGSET = 0,
	MSGDRAW,
	MSGWAIT,
};

//���b�Z�[�W�֐�����w���`
enum {
	A_BUTTON_WAIT = 0,
	A_BUTTON_NOWAIT,
};

//�o�^���j���[�h�c�i���o�[��`
enum{
	MENU_WORLD = 0,
	MENU_REGISTRATION,
	MENU_END,
};

//�n����]���[�h��`
enum {
	JAPAN_MODE = 0,
	GLOBAL_MODE,
};

//�J���������t���O��`
enum {
	CAMERA_FAR = 0,
	CAMERA_NEAR,
};

//�R�c�`��t���O��`
enum {
	DRAW3D_DISABLE = 0,
	DRAW3D_ENABLE,
	DRAW3D_BANISH,
};

//�n�_�f�[�^�\���J���[��`�i���f���I���ɂ���ĐF�ւ��Fwifihistory��`�ɉ������Ԃɂ���j
enum {
	MARK_NULL = 0,	//���ʐM�ꏊ
	MARK_BLUE,		//�{���͂��߂ĒʐM����
	MARK_YELLOW,	//�ʐM��
	MARK_RED,		//�����̓o�^�ꏊ
	MARK_GREEN,		//�J�[�\��
};

//============================================================================================
//	�\���̒�`
//============================================================================================
//�f�[�^�ݒ�\���́i���o�C�i���f�[�^�j
typedef struct EARTH_DATA_NATION_tag
{
	u16 flag;
	s16 x;
	s16 y;
}EARTH_DATA_NATION;

//�f�[�^�ݒ�\���́i�n��o�C�i���f�[�^�j
typedef struct EARTH_DATA_AREA_tag
{
	s16 x;
	s16 y;
}EARTH_DATA_AREA;

//�f�[�^�\���́i���n��e�[�u���f�[�^�j
typedef struct EARTH_AREATABLE_tag
{
	u16		nationID;
	u16		msg_arcID;
	const char* place_dataID;
}EARTH_AREATABLE;

//���X�g�f�[�^�\���́i�o�C�i���f�[�^�����ۂɎg�p���郊�X�g�p�f�[�^�ɕϊ��j
typedef struct EARTH_DEMO_LIST_DATA_tag
{
	s16 x;
	s16 y;
	MtxFx33 rotate;	//���Ή�]�s������炩���ߌv�Z���ĕۑ�
	u16	col;
	u16	nationID;
	u16	areaID;
}EARTH_DEMO_LIST_DATA;

//���X�g�f�[�^�\���́i�o�C�i���f�[�^�����ۂɎg�p���郊�X�g�p�f�[�^�ɕϊ��j
typedef struct EARTH_DEMO_LIST_tag
{
	u32	listcount;
	EARTH_DEMO_LIST_DATA	place[WORLD_PLACE_NUM_MAX];
}EARTH_DEMO_LIST;

//���[�N�\����
typedef struct EARTH_DEMO_WORK_tag
{
	//�q�[�v�ݒ胏�[�N
	int	heapID;

	//�Z�[�u�f�[�^�|�C���^
	WIFI_HISTORY*	wifi_sv;
	CONFIG*			config;	

	//�n�_���X�g���[�N
	EARTH_DEMO_LIST	placelist;

	//�a�f�V�X�e���|�C���^
	GF_BGL_INI*			bgl;
	GF_BGL_BMPWIN		msgwin;
	GF_BGL_BMPWIN		listwin;
	GF_BGL_BMPWIN		iconwin;
	GF_BGL_BMPWIN		infowin;
	BMPLIST_WORK*		bmplist;
	BMP_MENULIST_DATA*	bmplistdata;
	BMPMENU_WORK*		yesnowin;

	//���b�Z�[�W�}�l�[�W���|�C���^
	MSGDATA_MANAGER*	msg_man;
	int		msgseq;
	int		msgID;
	STRBUF* msgstr;
	WORDSET*			wordset;

	//���f�����[�h���[�N
	NNSG3dRenderObj			renderobj;			//�I�����v�q�[�v�J��
	NNSG3dResMdl*			resmodel;
	NNSG3dResFileHeader* 	resfileheader;

	NNSG3dRenderObj			mark_renderobj[5];	//�I�����v�q�[�v�J��
	NNSG3dResMdl*			mark_resmodel[5];
	NNSG3dResFileHeader* 	mark_resfileheader[5];

	//���f���ݒ胏�[�N
	VecFx32 trans;
	VecFx32 scale;
	VecFx32	rotate;

	VecFx32	mark_scale;

	//�J�����ݒ胏�[�N
	GF_CAMERA_PTR camera_p;
	CAMERA_ANGLE camera_angle;
	u16 camera_status;

	//���C�g�ݒ胏�[�N
	VecFx32	light_vec;

	//���쏈�����[�N
	int		Draw3Dsw;
	BOOL	fade_end_flag;
	BOOL	Japan_ROM_mode;
	u16		earth_mode;
	u16		rotate_speed;

	//�^�b�`�p�l�����o�ۑ����[�N
	int tp_result;
	int tp_seq;
	int tp_x;
	int tp_y;
	int tp_lenx;
	int tp_leny;
	int tp_count;

	//�n�_�o�^�e���|����
	int		my_nation;
	int		my_area;
	int		my_nation_tmp;
	int		my_area_tmp;
	BOOL	my_worldopen_flag;

	int		info_mode;

#ifdef WIFI_ERATH_DEBUG
	int debug_work[8];
#endif	

}EARTH_DEMO_WORK;

//�r�b�g�}�b�v���X�g�\����
typedef struct EARTH_BMPLIST_tag
{
	u32 msgID;
	u32 retID;
}EARTH_BMPLIST;

//============================================================================================
//	�O���[�o���֐���`
//============================================================================================
void	WIFI_RegistratonInit(SAVEDATA* savedata);
BOOL	WIFI_NationAreaNameGet(int nationID,int areaID,
								STRBUF* nation_str,STRBUF* area_str,int heapID);
BOOL	WIFI_LocalAreaExistCheck(int nationID);

//============================================================================================
//	���[�J���֐���`
//============================================================================================
PROC_RESULT Earth_Demo_Init(PROC * proc, int * seq);
PROC_RESULT Earth_Demo_Main(PROC * proc, int * seq);
PROC_RESULT Earth_Demo_Exit(PROC * proc, int * seq);

static void Earth_VramBankSet(void);
static void Earth_BGsysSet(void);
static void Earth_BGdataLoad( EARTH_DEMO_WORK * wk );
static void Earth_BGdataRelease( EARTH_DEMO_WORK * wk );

static void EarthListLoad( EARTH_DEMO_WORK * wk );
static void EarthListSet( EARTH_DEMO_WORK * wk,u32 index, s16 x,s16 y,u16 nationID,u16 areaID );
static void EarthList_NationAreaListSet( EARTH_DEMO_WORK * wk );
static int	EarthAreaTableGet(int nationID);

static void Earth_TouchPanel( EARTH_DEMO_WORK * wk );
static void Earth_TouchPanelParamGet
	( int prevx,int prevy,int* dirx_p,int* lenx_p,int* diry_p,int* leny_p );

static BOOL Earth_MsgPrint( EARTH_DEMO_WORK * wk,u32 msgID,int button_mode );
static void Earth_BmpListAdd( EARTH_DEMO_WORK * wk,
							GF_BGL_BMPWIN* win,const BMPWIN_DAT* windata,
							const BMPLIST_HEADER* listheader,const EARTH_BMPLIST* list);
static void Earth_BmpListAddGmmAll( EARTH_DEMO_WORK * wk,
							GF_BGL_BMPWIN* win, const BMPWIN_DAT* windata,
							const BMPLIST_HEADER* listheader,u32 listarcID);
static void Earth_BmpListDel( EARTH_DEMO_WORK* wk );

static void Earth_MyPlaceInfoWinSet( EARTH_DEMO_WORK* wk );
static void Earth_MyPlaceInfoWinSet2( EARTH_DEMO_WORK* wk, int nation, int area );
static void Earth_MyPlaceInfoWinRelease( EARTH_DEMO_WORK* wk );
static void Earth_PosInfoPut( EARTH_DEMO_WORK* wk );

static void Earth_ModelLoad( EARTH_DEMO_WORK * wk );
static void Earth_ModelRelease( EARTH_DEMO_WORK * wk );
static void EarthDataInit( EARTH_DEMO_WORK * wk );
static void EarthCameraInit( EARTH_DEMO_WORK * wk );
static void EarthLightInit( EARTH_DEMO_WORK * wk );

static BOOL Earth3D_Control( EARTH_DEMO_WORK * wk,int keytrg,int keycont );
static BOOL Earth3D_CameraMoveNearFar( EARTH_DEMO_WORK * wk );
static void Earth3D_Draw( EARTH_DEMO_WORK * wk );
static void EarthVecFx32_to_MtxFx33( MtxFx33* dst, VecFx32* src );
static void EarthVecFx32_to_MtxFx33_place( MtxFx33* dst, VecFx32* src );

#ifdef WIFI_ERATH_DEBUG
static void EarthDebugWinRotateInfoWrite( EARTH_DEMO_WORK * wk );
static void EarthDebugWinNameInfoWrite( EARTH_DEMO_WORK * wk );
static void EarthDebugNationMarkSet( EARTH_DEMO_WORK * wk );
static void EarthDebugAreaMarkSet( EARTH_DEMO_WORK * wk );
#endif	

//============================================================================================
//	�O���֐���`
//============================================================================================
extern void	Main_SetNextProc(FSOverlayID ov_id, const PROC_DATA * proc_data);
extern u8 MsgSpeedGet(void);

#if	0	//�Ăяo�����ֈړ�
//============================================================================================
//	�o�q�n�b��`�f�[�^
//============================================================================================
const PROC_DATA Earth_Demo_proc_data = {
	Earth_Demo_Init,
	Earth_Demo_Main,
	Earth_Demo_Exit,
	NO_OVERLAY_ID,
};
#endif


//============================================================================================
//	�a�f��`�f�[�^
//============================================================================================
static const GF_BGL_BGCNT_HEADER Earth_Demo_BGtxt_header = {
	0,0,					//�����\���w�x�ݒ�
	0x800,0,				//�X�N���[���o�b�t�@�T�C�Y(0 = �g�p���Ȃ�)���I�t�Z�b�g
	GF_BGL_SCRSIZ_256x256,	//�X�N���[���T�C�Y
	GX_BG_COLORMODE_16,		//�J���[���[�h
	GX_BG_SCRBASE_0x7000, 	//�X�N���[���x�[�X�u���b�N
	GX_BG_CHARBASE_0x00000,	//�L�����N�^�x�[�X�u���b�N 
	GX_BG_EXTPLTT_01,		//�g���p���b�g�I��(�g�p���Ȃ��ݒ�̂Ƃ��͖��������)
	0,						//�\���v���C�I���e�B�[
	0,						//�G���A�I�[�o�[�t���O
	0,						//
	FALSE					//���U�C�N�ݒ�
};

static const GF_BGL_BGCNT_HEADER Earth_Demo_Back_header = {
	0,0,					//�����\���w�x�ݒ�
	0x800,0,				//�X�N���[���o�b�t�@�T�C�Y(0 = �g�p���Ȃ�)���I�t�Z�b�g
	GF_BGL_SCRSIZ_256x256,	//�X�N���[���T�C�Y
	GX_BG_COLORMODE_16,		//�J���[���[�h
	GX_BG_SCRBASE_0x7800, 	//�X�N���[���x�[�X�u���b�N
	GX_BG_CHARBASE_0x04000,	//�L�����N�^�x�[�X�u���b�N 
	GX_BG_EXTPLTT_01,		//�g���p���b�g�I��(�g�p���Ȃ��ݒ�̂Ƃ��͖��������)
	3,						//�\���v���C�I���e�B�[
	0,						//�G���A�I�[�o�[�t���O
	0,						//
	FALSE					//���U�C�N�ݒ�
};

static const BMPWIN_DAT EarthMsgWinData =
{
	EARTH_TEXT_PLANE,	//�E�C���h�E�g�p�t���[��
	EARTH_MSG_WIN_PX,EARTH_MSG_WIN_PY,//�E�C���h�E�̈�̍���XY���W�i�L�����P�ʎw��j
	EARTH_MSG_WIN_SX,EARTH_MSG_WIN_SY,//�E�C���h�E�̈��XY�T�C�Y�i�L�����P�ʎw��j
	EARTH_MSG_WIN_PAL,	//�E�C���h�E�̈�̃p���b�g�i���o�[ 
	EARTH_MSG_WIN_CGX,	//�E�C���h�E�L�����̈�̊J�n�L�����N�^�i���o�[
};

static const BMPWIN_DAT EarthYesNoWinData =
{
	EARTH_TEXT_PLANE,	//�E�C���h�E�g�p�t���[��
	EARTH_YESNO_WIN_PX,EARTH_YESNO_WIN_PY,//�E�C���h�E�̈�̍���XY���W�i�L�����P�ʎw��j
	EARTH_YESNO_WIN_SX,EARTH_YESNO_WIN_SY,//�E�C���h�E�̈��XY�T�C�Y�i�L�����P�ʎw��j
	EARTH_YESNO_WIN_PAL,	//�E�C���h�E�̈�̃p���b�g�i���o�[ 
	EARTH_YESNO_WIN_CGX,	//�E�C���h�E�L�����̈�̊J�n�L�����N�^�i���o�[
};

static const BMPWIN_DAT EarthMenuWinData =
{
	EARTH_TEXT_PLANE,	//�E�C���h�E�g�p�t���[��
	EARTH_MENU_WIN_PX,EARTH_MENU_WIN_PY,//�E�C���h�E�̈�̍���XY���W�i�L�����P�ʎw��j
	EARTH_MENU_WIN_SX,EARTH_MENU_WIN_SY,//�E�C���h�E�̈��XY�T�C�Y�i�L�����P�ʎw��j
	EARTH_MENU_WIN_PAL,	//�E�C���h�E�̈�̃p���b�g�i���o�[ 
	EARTH_MENU_WIN_CGX,	//�E�C���h�E�L�����̈�̊J�n�L�����N�^�i���o�[
};

static const BMPWIN_DAT EarthPlaceListWinData =
{
	EARTH_TEXT_PLANE,	//�E�C���h�E�g�p�t���[��
	EARTH_PLACE_WIN_PX,EARTH_PLACE_WIN_PY,//�E�C���h�E�̈�̍���XY���W�i�L�����P�ʎw��j
	EARTH_PLACE_WIN_SX,EARTH_PLACE_WIN_SY,//�E�C���h�E�̈��XY�T�C�Y�i�L�����P�ʎw��j
	EARTH_PLACE_WIN_PAL,	//�E�C���h�E�̈�̃p���b�g�i���o�[ 
	EARTH_PLACE_WIN_CGX,	//�E�C���h�E�L�����̈�̊J�n�L�����N�^�i���o�[
};

static const BMPWIN_DAT EarthInfoWinData =
{
	EARTH_TEXT_PLANE,	//�E�C���h�E�g�p�t���[��
	EARTH_INFO_WIN_PX,EARTH_INFO_WIN_PY,//�E�C���h�E�̈�̍���XY���W�i�L�����P�ʎw��j
	EARTH_INFO_WIN_SX,EARTH_INFO_WIN_SY,//�E�C���h�E�̈��XY�T�C�Y�i�L�����P�ʎw��j
	EARTH_INFO_WIN_PAL,	//�E�C���h�E�̈�̃p���b�g�i���o�[ 
	EARTH_INFO_WIN_CGX,	//�E�C���h�E�L�����̈�̊J�n�L�����N�^�i���o�[
};

static const BMPWIN_DAT EarthIconWinData =
{
	EARTH_ICON_PLANE,	//�E�C���h�E�g�p�t���[��
	EARTH_ICON_WIN_PX,EARTH_ICON_WIN_PY,//�E�C���h�E�̈�̍���XY���W�i�L�����P�ʎw��j
	EARTH_ICON_WIN_SX,EARTH_ICON_WIN_SY,//�E�C���h�E�̈��XY�T�C�Y�i�L�����P�ʎw��j
	EARTH_ICON_WIN_PAL,	//�E�C���h�E�̈�̃p���b�g�i���o�[ 
	EARTH_ICON_WIN_CGX,	//�E�C���h�E�L�����̈�̊J�n�L�����N�^�i���o�[
};

static const EARTH_BMPLIST MenuList[] =
{
	{mes_earth_02_05,MENU_WORLD},
	{mes_earth_02_06,MENU_REGISTRATION},
	{mes_earth_02_07,MENU_END},
};

static const BMPLIST_HEADER MenuListHeader = {
	/* �\�������f�[�^�|�C���^(�v���O�����ݒ�) */NULL,/* �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐� */NULL,
	/* ���\�����Ƃ̃R�[���o�b�N�֐� */NULL,/* �Ή��r�b�g�}�b�v(�v���O�����ݒ�) */NULL,
	/* ���X�g���ڐ� */NELEMS(MenuList),/* �\���ő區�ڐ� */NELEMS(MenuList),		
	/* ���x���\���w���W */0,/* ���ڕ\���w���W */12,/* �J�[�\���\���w���W */0,/* �\���x���W */0,
	/* �����F */FBMP_COL_BLACK,/* �w�i�F */FBMP_COL_WHITE,/* �����e�F */FBMP_COL_BLK_SDW,		
	/* �����Ԋu�w */0,/* �����Ԋu�x */16,/* �y�[�W�X�L�b�v�^�C�v */BMPLIST_NO_SKIP,		
	/* �����w�� */FONT_SYSTEM,/*�a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)*/0,						
};

static const BMPLIST_HEADER PlaceListHeader = {
	/* �\�������f�[�^�|�C���^(�v���O�����ݒ�) */NULL,/* �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐� */NULL,
	/* ���\�����Ƃ̃R�[���o�b�N�֐� */NULL,/* �Ή��r�b�g�}�b�v(�v���O�����ݒ�) */NULL,
	/* ���X�g���ڐ�(�v���O�����ݒ�) */0,/* �\���ő區�ڐ� */7,		
	/* ���x���\���w���W */0,/* ���ڕ\���w���W */12,/* �J�[�\���\���w���W */0,/* �\���x���W */0,
	/* �����F */FBMP_COL_BLACK,/* �w�i�F */FBMP_COL_WHITE,/* �����e�F */FBMP_COL_BLK_SDW,		
	/* �����Ԋu�w */0,/* �����Ԋu�x */16,/* �y�[�W�X�L�b�v�^�C�v */BMPLIST_LRKEY_SKIP,		
	/* �����w�� */FONT_SYSTEM,/*�a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)*/0,						
};

//============================================================================================
//
//	���C���֐�
//
//============================================================================================
//============================================================================================
//	�������v���Z�X
//============================================================================================
PROC_RESULT Earth_Demo_Init(PROC * proc, int * seq)
{
	EARTH_DEMO_WORK * wk;
	int	heapID = HEAPID_WIFIEARTH;

	//�u�g�֐���~
	sys_VBlankFuncChange( NULL, NULL );
	sys_HBlankIntrSet( NULL,NULL );

	//�a�f�\����~
	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );

	//�q�[�v�G���A�쐬
	sys_CreateHeap( HEAPID_BASE_APP, heapID, 0x080000 );

	//���[�N�G���A�擾
	wk = PROC_AllocWork( proc, sizeof(EARTH_DEMO_WORK), heapID );
	memset( wk, 0, sizeof(EARTH_DEMO_WORK) );
	wk->heapID = heapID;

	//���{��ł��ǂ����̔��ʃt���O
	if( CasetteLanguage == LANG_JAPAN ){
		// ���{��o�[�W�����ł͓��{�����o�^�ł��Ȃ�
		wk->Japan_ROM_mode = TRUE;
	} else {
		// ���{��o�[�W�����ȊO�͍ŏ�����n���V���S��������
		wk->Japan_ROM_mode = FALSE;
	}
#ifdef PM_DEBUG
	// �k�{�^���������Ă���Ɠ��͏����N���A������Ő��E������͂ł���
	if(sys.cont & PAD_BUTTON_L){
		SAVEDATA* sv = PROC_GetParentWork( proc );
		WIFI_RegistratonInit( sv );
		wk->Japan_ROM_mode = FALSE;
	}
#endif
	//�Z�[�u�f�[�^�|�C���^�쐬
	{
		SAVEDATA* sv = PROC_GetParentWork( proc );

		wk->wifi_sv = SaveData_GetWifiHistory( sv );
		wk->my_nation = WIFIHISTORY_GetMyNation( wk->wifi_sv );
		wk->my_area = WIFIHISTORY_GetMyArea( wk->wifi_sv );
		wk->my_worldopen_flag = WIFIHISTORY_GetWorldFlag( wk->wifi_sv );
		wk->config	= SaveData_GetConfig( sv );	
	}

	//�u�q�`�l�ݒ�
	Earth_VramBankSet();

	//�a�f���C�u�����ݒ�
	Earth_BGsysSet();
	simple_3DBGInit( wk->heapID );
	wk->bgl = GF_BGL_BglIniAlloc( wk->heapID );
	GF_Disp_DispOn();
	
	//���b�Z�[�W�\���V�X�e��������
	MSG_PrintInit();
	wk->wordset = WORDSET_CreateEx( WORDSET_DEFAULT_SETNUM, EARTH_NAME_SIZE, wk->heapID );

	//�J�������C�u�����ݒ�
	wk->camera_p = GFC_AllocCamera( wk->heapID );

	//�R�c�`��X�C�b�`�ݒ�
	wk->Draw3Dsw = DRAW3D_DISABLE;
	sys.disp3DSW = DISP_3D_TO_SUB;
	GF_Disp_DispSelect();

	//�L�[�V�X�e���ݒ�
	sys_KeyRepeatSpeedSet( 4, 8 );

	//�n�惊�X�g�f�[�^�쐬
	EarthListLoad(wk);

	return	PROC_RES_FINISH;
}

//============================================================================================
//	���C���v���Z�X
//============================================================================================
PROC_RESULT Earth_Demo_Main(PROC * proc, int * seq)
{
	EARTH_DEMO_WORK * wk  = PROC_GetWork( proc );
	PROC_RESULT sys_result = PROC_RES_CONTINUE;

	switch(*seq){
	//-----------------------------------------------------------
	case EARTHDEMO_SEQ_MODELLOAD://���f���f�[�^���[�h

		//���b�Z�[�W�f�[�^�ǂݍ���
		wk->msg_man = MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_earth_dat,wk->heapID );

		Earth_ModelLoad(wk);	//���f�����[�h���C��
		Earth_BGdataLoad(wk);	//�a�f�f�[�^���[�h

		//�P�x�ύX�Z�b�g�i�h�m�j
		wk->fade_end_flag = FALSE;
		WIPE_SYS_Start(	WIPE_PATTERN_WMS,WIPE_TYPE_FADEIN,WIPE_TYPE_FADEIN,
						WIPE_FADE_BLACK,WIPE_DEF_DIV,WIPE_DEF_SYNC,wk->heapID);

		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2 , VISIBLE_ON );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2 , VISIBLE_ON );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3 , VISIBLE_ON );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG3 , VISIBLE_ON );

		*seq = EARTHDEMO_SEQ_DISPON;
		break;

	//-----------------------------------------------------------
	case EARTHDEMO_SEQ_DISPON:	//�`��n�m

		if(WIPE_SYS_EndCheck() == TRUE){	//�P�x�ύX�҂�
			*seq = EARTHDEMO_SEQ_WELCOME_MSG;
		}
		break;

	//-----------------------------------------------------------
	case EARTHDEMO_SEQ_WELCOME_MSG:	//�u�悤�����v

		if(Earth_MsgPrint(wk,mes_earth_01_01,A_BUTTON_NOWAIT) == TRUE){
			//�Z��ł���ꏊ���͍ρH
			if(wk->my_nation == 0){
				//���o�^
				*seq = EARTHDEMO_SEQ_MAINMENU;	//���C�����j���[�ݒ��
			}else{
				//�o�^��
				*seq = EARTHDEMO_SEQ_EARTH_DISPON;	//�R�c�n���V���[�h�n�m��
			}
		}
		break;

	//-----------------------------------------------------------
	case EARTHDEMO_SEQ_MAINMENU:	//���C�����j���[�ݒ�

		if(Earth_MsgPrint(wk,mes_earth_01_02,A_BUTTON_NOWAIT) == TRUE){
			//�I�����X�g�\��
			Earth_BmpListAdd(wk,&wk->listwin,&EarthMenuWinData,&MenuListHeader,MenuList);
			*seq = EARTHDEMO_SEQ_MAINMENU_SELECT;	//�I�����[�h��
		}
		break;

	case EARTHDEMO_SEQ_MAINMENU_SELECT:	//���C�����j���[�I�����[�h
		{
			int list_result = BmpListMain(wk->bmplist);

			if(list_result == BMPLIST_NULL){
				break;
			}
			Earth_BmpListDel(wk);//�I�����X�g�폜����
			Snd_SePlay( SEQ_SE_DP_SELECT );

			switch(list_result){
			default:
			case MENU_WORLD:	//�u�������v
				*seq = EARTHDEMO_SEQ_EARTH_DISPON;	//�R�c�n���V���[�h�n�m��
				break;
			case MENU_REGISTRATION:	//�u�Ƃ��낭�v
				*seq = EARTHDEMO_SEQ_REGISTRATIONMENU;	//�o�^���j���[�ݒ��
				break;
			case BMPLIST_CANCEL:
			case MENU_END:	//�u��߂�v
				*seq = EARTHDEMO_SEQ_END;	//�I��������
				break;
			}
		}
		break;

	//-----------------------------------------------------------
	case EARTHDEMO_SEQ_REGISTRATIONMENU:	//�o�^���j���[�ݒ�

		if(Earth_MsgPrint(wk,mes_earth_01_03,A_BUTTON_NOWAIT) == TRUE){
			//�͂�/�������E�B���h�E�\��
			wk->yesnowin = BmpYesNoSelectInit(wk->bgl,&EarthYesNoWinData,
											EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL,
											wk->heapID);
			*seq = EARTHDEMO_SEQ_REGISTRATIONMENU_SELECT;	//�I�����[�h��
		}
		break;

	case EARTHDEMO_SEQ_REGISTRATIONMENU_SELECT:	//�o�^���j���[�I�����[�h
		{
			u32 list_result = BmpYesNoSelectMain(wk->yesnowin,wk->heapID);

			switch(list_result){
			case 0:		//�u�͂��v
				if(wk->Japan_ROM_mode == TRUE){
					wk->my_nation_tmp = country103;	//���{��Ō��菈���i�����̓X�L�b�v�j
					*seq = EARTHDEMO_SEQ_REGISTRATIONLIST_AREA;	//�n��ʓo�^���X�g�I����
				}else{
					*seq = EARTHDEMO_SEQ_REGISTRATIONLIST_NATION;//���ʓo�^���X�g�I����
				}
				break;
			case BMPMENU_CANCEL:	//�u�������v
				*seq = EARTHDEMO_SEQ_MAINMENU;
				break;
			}
		}
		break;

	case EARTHDEMO_SEQ_REGISTRATIONLIST_NATION:	//���ʓo�^���X�g�ݒ�

		if(Earth_MsgPrint(wk,mes_earth_01_04,A_BUTTON_NOWAIT) == TRUE){
		
			wk->my_nation_tmp = 0;//�o�^���e���|����������
			Earth_BmpListAddGmmAll(wk,&wk->listwin,&EarthPlaceListWinData,
								&PlaceListHeader,NARC_msg_wifi_place_msg_world_dat);

			*seq = EARTHDEMO_SEQ_REGISTRATIONLIST_NATION_SELECT;	//���ʓo�^���X�g�I����
		}
		break;

	case EARTHDEMO_SEQ_REGISTRATIONLIST_NATION_SELECT:	//���ʓo�^���X�g�I�����[�h
		{
			int list_result = BmpListMain(wk->bmplist);
#ifdef WIFI_ERATH_DEBUG
			EarthDebugNationMarkSet(wk);
#endif
			if(list_result == BMPLIST_NULL){
				break;
			}
			Earth_BmpListDel(wk);//�I�����X�g�폜����
			Snd_SePlay( SEQ_SE_DP_SELECT );

			switch(list_result){
			default:
				{
					wk->my_nation_tmp = list_result;	//���o�^

					if(WIFI_LocalAreaExistCheck(wk->my_nation_tmp) == TRUE){
						//�n�悪���݂���ꍇ
						*seq = EARTHDEMO_SEQ_REGISTRATIONLIST_AREA;	//�n��ʓo�^���X�g�I����
					}else{
						//�n�悪���݂��Ȃ��ꏊ�̓o�^
						wk->my_area_tmp = 0;				//�n��o�^�i�Ȃ��j
						*seq = EARTHDEMO_SEQ_FINAL_REGISTRATION;	//���n��o�^�ŏI�m�F��
					}
				}
				break;
			case BMPLIST_CANCEL:	//�u�������v�L�����Z��
				//*seq = EARTHDEMO_SEQ_REGISTRATIONMENU;	//�o�^���j���[��
				*seq = EARTHDEMO_SEQ_MAINMENU;
				break;
			}
		}
		break;

	case EARTHDEMO_SEQ_REGISTRATIONLIST_AREA:	//�n��ʓo�^���X�g�ݒ�

		if(Earth_MsgPrint(wk,mes_earth_01_05,A_BUTTON_NOWAIT) == TRUE){
			wk->my_area_tmp = 0;//�o�^���e���|����������
			Earth_BmpListAddGmmAll(wk,&wk->listwin,&EarthPlaceListWinData,&PlaceListHeader,
						WIFI_COUNTRY_CountryCodeToPlaceMsgDataID(wk->my_nation_tmp));

			*seq = EARTHDEMO_SEQ_REGISTRATIONLIST_AREA_SELECT;	//�n��ʓo�^���X�g�I����
		}
		break;

	case EARTHDEMO_SEQ_REGISTRATIONLIST_AREA_SELECT:	//�n��ʓo�^���X�g�I�����[�h
		{
			int list_result = BmpListMain(wk->bmplist);
#ifdef WIFI_ERATH_DEBUG
			EarthDebugAreaMarkSet(wk);
#endif
			if(list_result == BMPLIST_NULL){
				break;
			}
			Earth_BmpListDel(wk);//�I�����X�g�폜����
			Snd_SePlay( SEQ_SE_DP_SELECT );

			switch(list_result){
			default:
				wk->my_area_tmp = list_result;			//�n��o�^
				*seq = EARTHDEMO_SEQ_FINAL_REGISTRATION;	//���n��o�^�ŏI�m�F��
				break;
			case BMPLIST_CANCEL://�L�����Z��
				if(wk->Japan_ROM_mode == TRUE){
					//*seq = EARTHDEMO_SEQ_REGISTRATIONMENU;	//�o�^���j���[��(���{�ł̏ꍇ)
					*seq = EARTHDEMO_SEQ_MAINMENU;
				} else {
					*seq = EARTHDEMO_SEQ_REGISTRATIONLIST_NATION;	//���ʓo�^���X�g�ݒ��
				}
			}
		}
		break;

	case EARTHDEMO_SEQ_FINAL_REGISTRATION:	//�o�^�ŏI�m�F�ݒ�
		Earth_MyPlaceInfoWinSet2( wk, wk->my_nation_tmp, wk->my_area_tmp );//�o�^�n���\��
		*seq = EARTHDEMO_SEQ_FINAL_REGISTRATION_YESNO;	//�o�^�ŏI�m�F��
		break;

	case EARTHDEMO_SEQ_FINAL_REGISTRATION_YESNO:	//�o�^�ŏI�m�F

		if(Earth_MsgPrint(wk,mes_earth_01_06,A_BUTTON_NOWAIT) == TRUE){
			//�͂�/�������E�B���h�E�\��
			wk->yesnowin = BmpYesNoSelectInit(wk->bgl,&EarthYesNoWinData,
											EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL,
											wk->heapID);
			*seq = EARTHDEMO_SEQ_FINAL_REGISTRATION_SELECT;	//�o�^�ŏI�m�F�I�����[�h��
		}
		break;

	case EARTHDEMO_SEQ_FINAL_REGISTRATION_SELECT:	//�o�^�ŏI�m�F�I�����[�h
		{
			u32 list_result = BmpYesNoSelectMain(wk->yesnowin,wk->heapID);

			switch(list_result){
			case 0:		//�u�͂��v
				Earth_MyPlaceInfoWinRelease( wk );
				//�o�^�f�[�^�Z�[�u
				WIFIHISTORY_SetMyNationArea(wk->wifi_sv,wk->my_nation_tmp,wk->my_area_tmp);
				wk->my_nation = wk->my_nation_tmp;
				wk->my_area = wk->my_area_tmp;

				*seq = EARTHDEMO_SEQ_EARTH_DISPON;	//�R�c�n���V���[�h�n�m��
				break;
			case BMPMENU_CANCEL:	//�u�������v
				Earth_MyPlaceInfoWinRelease( wk );
				*seq = EARTHDEMO_SEQ_MAINMENU;
				break;
			}
		}
		break;

	//-----------------------------------------------------------
	case EARTHDEMO_SEQ_EARTH_DISPON:	//�R�c�n���V���[�h�n�m
		//���{��ŁH
		if((wk->Japan_ROM_mode == TRUE)&&(wk->my_worldopen_flag == FALSE)){
			//���{��łŊC�O�̃��[�h���J���Ă��Ȃ��ꍇ�͓��{����}�b�v
			wk->earth_mode = JAPAN_MODE;
		}else{
			//���̑��A���E�}�b�v
			wk->earth_mode = GLOBAL_MODE;
		}
		EarthDataInit(wk);					//�n���f�[�^������
		EarthList_NationAreaListSet(wk);	//�o�^�n��f�[�^�ݒ�
		EarthCameraInit(wk);				//�J����������
		EarthLightInit(wk);					//���C�g������

		//���b�Z�[�W��ʃN���A
		GF_BGL_BmpWinFill(&wk->msgwin,FBMP_COL_WHITE,0,0,
							EARTH_MSG_WIN_SX*DOTSIZE,EARTH_MSG_WIN_SY*DOTSIZE);
		//�u��߂�v�A�C�R���n�m
		BmpMenuWinWrite(&wk->iconwin,WINDOW_TRANS_ON,EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL);

		//�Z��ł���ꏊ���͍ρH
		if(wk->my_nation != 0){
			Earth_MyPlaceInfoWinSet( wk );//�o�^�n���\��
		}
		Earth_PosInfoPut( wk );
		wk->info_mode = 0;

		wk->Draw3Dsw = DRAW3D_ENABLE;//�R�c�`��X�C�b�`�ݒ�n�m

		*seq = EARTHDEMO_SEQ_MOVE_EARTH;
		break;

	//-----------------------------------------------------------
	case EARTHDEMO_SEQ_MOVE_EARTH:	//�n����]
		{
			u16 camera_status_backup = wk->camera_status;

			//�^�b�`�p�l���R���g���[��
			Earth_TouchPanel(wk);

			//�I������
			if((sys.trg & PAD_BUTTON_B)||(wk->tp_result & PAD_BUTTON_B)){
				//�u��߂�v�A�C�R���n�e�e
				BmpMenuWinClear(&wk->iconwin,WINDOW_TRANS_ON);
				Snd_SePlay( SEQ_SE_DP_DECIDE );

				GF_BGL_BmpWinFill(&wk->msgwin,FBMP_COL_WHITE,0,0,
							EARTH_MSG_WIN_SX*DOTSIZE,EARTH_MSG_WIN_SY*DOTSIZE);

				//�Z��ł���ꏊ���͍ρH
				if(wk->my_nation == 0){
					//���j���[��ʂ�
					wk->Draw3Dsw = DRAW3D_BANISH;//�R�c��ʏ������X�C�b�`�ݒ�n�e�e
					*seq = EARTHDEMO_SEQ_MAINMENU;
				}else{
					Earth_MyPlaceInfoWinRelease( wk );
					*seq = EARTHDEMO_SEQ_END;//�I��
				}
			}else{
				if( (sys.trg & PAD_BUTTON_X)&&(wk->info_mode == 0) ){
					wk->info_mode = 1;
					Earth_PosInfoPut( wk );
					if( wk->info_mode == 1 ){
						Snd_SePlay( SEQ_SE_DP_DECIDE );
					}
					break;
				}
				if((sys.trg & (PAD_BUTTON_X|PAD_BUTTON_A|PAD_BUTTON_B))&&(wk->info_mode == 1)){
					wk->info_mode = 0;
					Earth_PosInfoPut( wk );
					break;
				}
				{
					BOOL move_flag;
					//�n����]�R���g���[��
					move_flag = Earth3D_Control(wk, sys.trg, sys.cont);

					if( (move_flag == TRUE)&&(wk->info_mode == 1) ){
						wk->info_mode = 0;
						Earth_PosInfoPut( wk );
					}
				}
				//�J�������߈ړ�����
				if(camera_status_backup != wk->camera_status){
					*seq = EARTHDEMO_SEQ_MOVE_CAMERA;
					Snd_SePlay( SEQ_SE_DP_DECIDE );
				}
			}
		}
#ifdef WIFI_ERATH_DEBUG
		EarthDebugWinRotateInfoWrite(wk);//�f�o�b�O���\��
#endif
		break;

	case EARTHDEMO_SEQ_MOVE_CAMERA:	//�J���������ړ�
		{
			BOOL end_flag = Earth3D_CameraMoveNearFar(wk);

			if(end_flag == TRUE){
				*seq = EARTHDEMO_SEQ_MOVE_EARTH;
			}
		}
		break;

	//-----------------------------------------------------------
	case EARTHDEMO_SEQ_END:		//�I������
		wk->fade_end_flag = FALSE;//�P�x�ύX�҂��t���O���Z�b�g
		WIPE_SYS_Start(	WIPE_PATTERN_WMS,WIPE_TYPE_FADEOUT,WIPE_TYPE_FADEOUT,
						WIPE_FADE_BLACK,WIPE_DEF_DIV,WIPE_DEF_SYNC,wk->heapID);
		*seq = EARTHDEMO_SEQ_EXIT;
		break;

	case EARTHDEMO_SEQ_EXIT:	//�I��

		if(WIPE_SYS_EndCheck() == TRUE){	//�P�x�ύX�҂�

			wk->Draw3Dsw = DRAW3D_ENABLE;//�R�c�`��X�C�b�`�ݒ�n�e�e
			//�a�f�f�[�^�j��
			Earth_BGdataRelease(wk);
			//���f���f�[�^�j��
			Earth_ModelRelease(wk);
			//���b�Z�[�W�f�[�^�j��
			MSGMAN_Delete(wk->msg_man);

			(*seq) = 0;
			sys_result = PROC_RES_FINISH;	//�I���t���O
		}
		break;
	}
	Earth3D_Draw(wk);		//�R�c�`��G���W��

	return	sys_result;
}

//============================================================================================
//	�I���v���Z�X
//============================================================================================
PROC_RESULT Earth_Demo_Exit(PROC * proc, int * seq)
	
{
	EARTH_DEMO_WORK * wk  = PROC_GetWork( proc );
	int	heapID = wk->heapID;

	//�a�f�\����~
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2 , VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2 , VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3 , VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG3 , VISIBLE_OFF );

	//�e������m�ۃ��[�N�J��
	GFC_FreeCamera(wk->camera_p);
	WORDSET_Delete( wk->wordset );
	simple_3DBGExit();
	sys_FreeMemoryEz(wk->bgl);

	//�u�g�֐���~
	sys_VBlankFuncChange( NULL, NULL );		// VBlank�Z�b�g

	//���[�N�J��
	PROC_FreeWork( proc );

	//�q�[�v�J��
	sys_DeleteHeap( heapID );

	sys.disp3DSW = DISP_3D_TO_MAIN;

	return	PROC_RES_FINISH;
}

//============================================================================================
//
//	���[�J���֐��i���C���V�X�e���֘A�j
//
//============================================================================================
//----------------------------------
//�u�q�`�l�ݒ�
//----------------------------------
static void Earth_VramBankSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_C,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_32_H,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_16_F,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_01_AB,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_0123_E			// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &vramSetTable );
}

//----------------------------------
//�a�f�V�X�e���ݒ�
//----------------------------------
static void Earth_BGsysSet(void )
{
	GF_BGL_SYS_HEADER BGsys_data = {GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0,GX_BG0_AS_3D};

	GF_BGL_InitBG(&BGsys_data);
}


//============================================================================================
//
//	���[�J���֐��i�n��f�[�^�擾�֘A�j
//
//============================================================================================
//----------------------------------
//�n�_���X�g���[�h
//----------------------------------
static void EarthListLoad( EARTH_DEMO_WORK * wk )
{
	//�n�_���X�g����������
	wk->placelist.listcount = 0;

	{//�n�_�}�[�N��]�������i���f�[�^�o�C�i���f�[�^���[�h�j
		void* filep;
		EARTH_DATA_NATION* listp;
		u32	size;
		int	i,listcount;

		filep = ArcUtil_LoadEx( ARC_WIFI_EARCH_PLACE, NARC_wifi_earth_place_place_pos_wrd_dat, 
								FALSE, wk->heapID, ALLOC_TOP, &size );

		listp = (EARTH_DATA_NATION*)filep;	//�t�@�C���ǂݍ��ݗp�ɕϊ�
		listcount = size/6;				//�n�_���擾�i�f�[�^���F�P�n�_�ɂ��U�o�C�g�j

		listp++;	//1origin�̂��ߓǂݔ�΂�
		for(i=1;i<listcount;i++){
			if(listp->flag != 2){	//2�̏ꍇ�͒n�惊�X�g�����݂���
				EarthListSet(wk,wk->placelist.listcount,listp->x,listp->y,i,0);
				wk->placelist.listcount++;
			}
			listp++;
		}
		sys_FreeMemoryEz(filep);
	}
	{//�n�_�}�[�N��]�������i�n��f�[�^�o�C�i���f�[�^���[�h�j
		void* filep;
		EARTH_DATA_AREA* listp;
		u32	size, data_id;
		int	i,datLen,index,listcount;

		index = 1;	//1orgin
		datLen = WIFI_COUNTRY_GetDataLen();

		while(index < datLen){

			data_id = WIFI_COUNTRY_DataIndexToPlaceDataID( index );
			filep = ArcUtil_LoadEx( ARC_WIFI_EARCH_PLACE, data_id, FALSE, 
									wk->heapID, ALLOC_TOP, &size );

			listp = (EARTH_DATA_AREA*)filep;	//�t�@�C���ǂݍ��ݗp�ɕϊ�
			listcount = size/4;		//�n�_���擾�i�f�[�^���F�P�n�_�ɂ��S�o�C�g�j

			listp++;	//1origin�̂��ߓǂݔ�΂�
			for(i=1;i<listcount;i++){//1orgin
				EarthListSet(wk,wk->placelist.listcount,listp->x,listp->y,
								WIFI_COUNTRY_DataIndexToCountryCode(index),i);
				wk->placelist.listcount++;
				listp++;
			}
			sys_FreeMemoryEz(filep);
			index++;
		}
	}
}

//----------------------------------
//���X�g�o�^
//----------------------------------
static void EarthListSet( EARTH_DEMO_WORK * wk,u32 index,s16 x,s16 y,u16 nationID,u16 areaID )
{
	MtxFx33 rotMtx = {FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};
	VecFx32 rotVec;

	wk->placelist.place[index].x = x;	//�w��]�I�t�Z�b�g�擾
	wk->placelist.place[index].y = y;	//�x��]�I�t�Z�b�g�擾
	
	rotVec.x = x;
	rotVec.y = y;
	rotVec.z = INIT_EARTH_ROTATE_ZVAL;
	EarthVecFx32_to_MtxFx33_place(&rotMtx,&rotVec);	//�����ʒu����̑��΍��W�v�Z
	wk->placelist.place[index].rotate = rotMtx;

	//�}�[�N�F�ݒ�(wifihistory��`�ɉ�������)
	wk->placelist.place[index].col = WIFIHISTORY_GetStat(wk->wifi_sv,nationID,areaID);

	wk->placelist.place[index].nationID = nationID;	//�Y�����h�c
	wk->placelist.place[index].areaID = areaID;		//�Y���n��h�c
}

//----------------------------------
//�o�^�n����Z�b�g
//----------------------------------
static void EarthList_NationAreaListSet( EARTH_DEMO_WORK * wk )
{
	int	i;

	for(i=0;i<wk->placelist.listcount;i++){
		if((wk->placelist.place[i].nationID == wk->my_nation)	//�Y�����h�c
			&&(wk->placelist.place[i].areaID == wk->my_area)){	//�Y���n��h�c

			wk->placelist.place[i].col = MARK_RED;	//�}�[�N�F�ݒ�
			wk->rotate.x  = wk->placelist.place[i].x;	//�n���V�A��
			wk->rotate.y  = wk->placelist.place[i].y;	//�n���V�A��
		}
	}
}

//----------------------------------
//���[�J���G���A���݃`�F�b�N
//----------------------------------
static int	EarthAreaTableGet(int nationID)
{
	return WIFI_COUNTRY_CountryCodeToDataIndex( nationID );
}


//============================================================================================
//
//	���[�J���֐��i�^�b�`�p�l���֘A�j
//
//============================================================================================
static void Earth_TouchPanel( EARTH_DEMO_WORK * wk )
{
	int dirx,lenx,diry,leny;

	wk->tp_result = 0;

	if(sys.tp_trg){
		if(	(sys.tp_x >= ((EARTH_ICON_WIN_PX) * DOTSIZE))&&
			(sys.tp_x <= ((EARTH_ICON_WIN_PX + EARTH_ICON_WIN_SX) * DOTSIZE))&&
			(sys.tp_y >= ((EARTH_ICON_WIN_PY) * DOTSIZE))&&
			(sys.tp_y <= ((EARTH_ICON_WIN_PY + EARTH_ICON_WIN_SY) * DOTSIZE))){
			//�u��߂�v
			wk->tp_result = PAD_BUTTON_B;
			return;
		} else {
			wk->tp_seq = 0;
			wk->tp_lenx = 0;
			wk->tp_leny = 0;
			wk->tp_count = 0;
			wk->tp_result = 0;
			//����̌��o�ʒu��ۑ�
			wk->tp_x = sys.tp_x;
			wk->tp_y = sys.tp_y;
			wk->tp_count = 4;
		}
	}
	if(sys.tp_cont){
		switch(wk->tp_seq){
		case 0:
			//�ŏ��̃J�E���g�̓g���K�[�F���p�ɖ���
			if(!wk->tp_count){
				wk->tp_seq++;
			}else{
				wk->tp_count--;
			}
		case 1:
			Earth_TouchPanelParamGet(wk->tp_x,wk->tp_y,&dirx,&lenx,&diry,&leny);
			wk->tp_result = dirx | diry;
			wk->tp_lenx = lenx;
			wk->tp_leny = leny;
			wk->tp_x = sys.tp_x;
			wk->tp_y = sys.tp_y;
			break;
		}
	}else{
		if(wk->tp_count){
			wk->tp_result = PAD_BUTTON_A;
		}
		wk->tp_seq = 0;
		wk->tp_lenx = 0;
		wk->tp_leny = 0;
		wk->tp_count = 0;
	}
}

static void Earth_TouchPanelParamGet
	( int prevx,int prevy,int* dirx_p,int* lenx_p,int* diry_p,int* leny_p )
{
	int x_dir = 0;
	int y_dir = 0;
	int x_len = 0;
	int y_len = 0;

	//�w�������ړ����擾
	if(sys.tp_x != 0xffff){
		x_len = sys.tp_x - prevx;
		if(x_len < 0){
			x_len ^= -1;
			x_dir = PAD_KEY_RIGHT;
		}else{
			if(x_len > 0){
				x_dir = PAD_KEY_LEFT;
			}
		}
	}
	x_len &= 0x3f;	//���~�b�^�[
	*dirx_p = x_dir;
	*lenx_p = x_len;

	//�x�������ړ����擾
	if(sys.tp_y != 0xffff){
		y_len = sys.tp_y - prevy;
		if(y_len < 0){
			y_len ^= -1;
			y_dir = PAD_KEY_DOWN;
		}else{
			if(y_len > 0){
				y_dir = PAD_KEY_UP;
			}
		}
	}
	y_len &= 0x3f;	//���~�b�^�[
	*diry_p = y_dir;
	*leny_p = y_len;
}


//============================================================================================
//
//	���[�J���֐��i�Q�c�֘A�j
//
//============================================================================================
//----------------------------------
//�a�f�ݒ�
//----------------------------------
static void Earth_BGdataLoad( EARTH_DEMO_WORK * wk )
{
	//--------�T�u�a�f��-------------------------------------------
	//�e�L�X�g�a�f�ʃR���g���[���ݒ�
	GF_BGL_BGControlSet(wk->bgl,EARTH_TEXT_PLANE,&Earth_Demo_BGtxt_header,GF_BGL_MODE_TEXT);
	GF_BGL_ScrClear(wk->bgl,EARTH_TEXT_PLANE);//�e�L�X�g�a�f�ʃN���A
	//�w�i�a�f�ʃR���g���[���ݒ�
	GF_BGL_BGControlSet(wk->bgl,EARTH_BACK_S_PLANE,&Earth_Demo_Back_header,GF_BGL_MODE_TEXT);
	ArcUtil_BgCharSet(	ARC_WIFI_EARTH,NARC_wifi_earth_earth_bg_NCGR,wk->bgl,
						EARTH_BACK_S_PLANE,0,0,0,wk->heapID);
	ArcUtil_PalSet(		ARC_WIFI_EARTH,NARC_wifi_earth_earth_bg_NCLR,PALTYPE_SUB_BG,
						EARTH_BACK_PAL*PALSIZE,PALSIZE*4,wk->heapID);
	ArcUtil_ScrnSet(	ARC_WIFI_EARTH,NARC_wifi_earth_earth_bg_NSCR,wk->bgl,
						EARTH_BACK_S_PLANE,0,0,0,wk->heapID);

	//���b�Z�[�W�E�C���h�E�L�������p���b�g�ǂݍ��݁i�E�C���h�E�O���j
	TalkWinGraphicSet(	wk->bgl,EARTH_TEXT_PLANE,
						EARTH_TALKWINCHR_NUM,EARTH_TALKWIN_PAL,
						CONFIG_GetWindowType(wk->config),wk->heapID);
	//���j���[�E�C���h�E�L�������p���b�g�ǂݍ��݁i�E�C���h�E�O���j
	MenuWinGraphicSet(	wk->bgl,EARTH_TEXT_PLANE,
						EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL,0,wk->heapID);

	//�t�H���g�p���b�g�ǂݍ���
	SystemFontPaletteLoad( PALTYPE_SUB_BG, EARTH_SYSFONT_PAL*PALSIZE, wk->heapID );
	//NULL�L�������p���b�g�ݒ�
	GF_BGL_ClearCharSet( EARTH_TEXT_PLANE, 32, 0, wk->heapID );
	GF_BGL_BackGroundColorSet( EARTH_TEXT_PLANE,EARTH_NULL_PALETTE );

	//���b�Z�[�W�E�C���h�E�r�b�g�}�b�v�쐬�i�E�C���h�E�����j
	GF_BGL_BmpWinAddEx(wk->bgl,&wk->msgwin,&EarthMsgWinData );
	GF_BGL_BmpWinFill(&wk->msgwin,FBMP_COL_WHITE,0,0,//bmp,col,startX,startY,sizeX,sizeY
			EARTH_MSG_WIN_SX*DOTSIZE,EARTH_MSG_WIN_SY*DOTSIZE);
	//���b�Z�[�W�E�C���h�E�����\��
	BmpTalkWinWrite(&wk->msgwin,WINDOW_TRANS_ON,EARTH_TALKWINCHR_NUM,EARTH_TALKWIN_PAL);

	//���b�Z�[�W�V�X�e��������
	wk->msgseq = MSGSET;

	//--------���C���a�f��------------------------------------------
	//�A�C�R���a�f�ʃR���g���[���ݒ�
	GF_BGL_BGControlSet(wk->bgl,EARTH_ICON_PLANE,&Earth_Demo_BGtxt_header,GF_BGL_MODE_TEXT);
	GF_BGL_ScrClear(wk->bgl,EARTH_ICON_PLANE);//�A�C�R���a�f�ʃN���A
	//�w�i�a�f�ʃR���g���[���ݒ�
	GF_BGL_BGControlSet(wk->bgl,EARTH_BACK_M_PLANE,&Earth_Demo_Back_header,GF_BGL_MODE_TEXT);
	ArcUtil_BgCharSet(	ARC_WIFI_EARTH,NARC_wifi_earth_earth_bg_NCGR,wk->bgl,
						EARTH_BACK_M_PLANE,0,0,0,wk->heapID);
	ArcUtil_PalSet(		ARC_WIFI_EARTH,NARC_wifi_earth_earth_bg_NCLR,PALTYPE_MAIN_BG,
						EARTH_BACK_PAL*PALSIZE,PALSIZE*4,wk->heapID);
	ArcUtil_ScrnSet(	ARC_WIFI_EARTH,NARC_wifi_earth_earth_bg_NSCR,wk->bgl,
						EARTH_BACK_M_PLANE,0,0,0,wk->heapID);

	//���j���[�E�C���h�E�L�������p���b�g�ǂݍ��݁i�E�C���h�E�O���j
	MenuWinGraphicSet(	wk->bgl,EARTH_ICON_PLANE,
						EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL,0,wk->heapID);

	//�t�H���g�p���b�g�ǂݍ���
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, EARTH_SYSFONT_PAL*PALSIZE, wk->heapID );
	//NULL�L�������p���b�g�ݒ�
	GF_BGL_ClearCharSet( EARTH_ICON_PLANE, 32, 0, wk->heapID );
	GF_BGL_BackGroundColorSet( EARTH_ICON_PLANE,0x0000 );
	{
		STRBUF* back_str = STRBUF_Create(16, wk->heapID);

		//�{�^���t�H���g�̃��[�h
		FontProc_LoadFont( FONT_BUTTON, wk->heapID );
		//�{�^���t�H���g�p���b�g�̃��[�h
		{//�p���b�g�f�[�^���Ȃ��̂Œ��ڍ쐬
			u16 col1 = 0x4e56;
			u16 col2 = 0x3571;
			u16 col3 = 0x208c;
			u16 col4 = 0x7fff;

			GF_BGL_PaletteSet( EARTH_ICON_PLANE, &col1, 2, EARTH_SYSFONT_PAL*PALSIZE+1*2 );
			GF_BGL_PaletteSet( EARTH_ICON_PLANE, &col2, 2, EARTH_SYSFONT_PAL*PALSIZE+2*2 );
			GF_BGL_PaletteSet( EARTH_ICON_PLANE, &col3, 2, EARTH_SYSFONT_PAL*PALSIZE+3*2 );
			GF_BGL_PaletteSet( EARTH_ICON_PLANE, &col4, 2, EARTH_SYSFONT_PAL*PALSIZE+15*2 );
		}
		//���b�Z�[�W�E�C���h�E�r�b�g�}�b�v�쐬�i�E�C���h�E�����j
		GF_BGL_BmpWinAddEx(wk->bgl,&wk->iconwin,&EarthIconWinData );
		GF_BGL_BmpWinFill(&wk->iconwin,FBMP_COL_WHITE,0,0,
				EARTH_MSG_WIN_SX*DOTSIZE,EARTH_MSG_WIN_SY*DOTSIZE);
		//������̎擾�i��߂�j
		MSGMAN_GetString(wk->msg_man,mes_earth_02_07,back_str);
		//������̕\��
		GF_STR_PrintSimple(&wk->iconwin,FONT_BUTTON,back_str,0,0,MSG_NO_PUT,NULL);
		STRBUF_Delete(back_str);

		//�{�^���t�H���g�̔j��
		FontProc_UnloadFont( FONT_BUTTON );
	}
}

static void Earth_BGdataRelease( EARTH_DEMO_WORK * wk )
{
	GF_BGL_BmpWinDel(&wk->iconwin);
	GF_BGL_BmpWinDel(&wk->msgwin);
	GF_BGL_BGControlExit(wk->bgl,EARTH_ICON_PLANE);
	GF_BGL_BGControlExit(wk->bgl,EARTH_TEXT_PLANE);
	GF_BGL_BGControlExit(wk->bgl,EARTH_BACK_M_PLANE);
	GF_BGL_BGControlExit(wk->bgl,EARTH_BACK_S_PLANE);
}

//----------------------------------
//���b�Z�[�W�\��
//----------------------------------
static BOOL Earth_MsgPrint( EARTH_DEMO_WORK * wk,u32 msgID,int button_mode )
{
	BOOL result = FALSE;

	switch(wk->msgseq){
	case MSGSET:
		//�̈�N���A
		GF_BGL_BmpWinFill(&wk->msgwin,FBMP_COL_WHITE,0,0,//bmp,col,startX,startY,sizeX,sizeY
				EARTH_MSG_WIN_SX*DOTSIZE,EARTH_MSG_WIN_SY*DOTSIZE);

		//������o�b�t�@�̍쐬
		wk->msgstr = STRBUF_Create(EARTH_STRBUF_SIZE, wk->heapID);	

		//������̎擾
		MSGMAN_GetString(wk->msg_man,msgID,wk->msgstr);

		//������̕\��
		wk->msgID = GF_STR_PrintSimple(	&wk->msgwin,FONT_TALK,wk->msgstr,0,0,
										CONFIG_GetMsgPrintSpeed( wk->config ),NULL);

		wk->msgseq = MSGDRAW;
		break;

	case MSGDRAW:
		//������`��҂�
		if(!(GF_MSG_PrintEndCheck(wk->msgID))){
			STRBUF_Delete(wk->msgstr);
			wk->msgseq = MSGWAIT;
		}
		break;

	case MSGWAIT:
		//�I���҂�
		if((button_mode != A_BUTTON_WAIT)||(sys.trg & PAD_BUTTON_A)){
			wk->msgseq = MSGSET;
			result = TRUE;
		}
	}
	return result;
}

//----------------------------------
//���X�g�\���p�R�[���o�b�N
//----------------------------------
static void Earth_BmpListMoveSeCall(BMPLIST_WORK * wk,u32 param,u8 mode)
{
	if( mode == 0 ){//���������͖炳�Ȃ�
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}
}

//----------------------------------
//���X�g�\��:BmpList�ݒ�Q��
//----------------------------------
static void Earth_BmpListAdd( EARTH_DEMO_WORK * wk,
							GF_BGL_BMPWIN* win,const BMPWIN_DAT* windata,
							const BMPLIST_HEADER* listheader,const EARTH_BMPLIST* list)
{
	BMPLIST_HEADER	listheader_tmp;
	int	i;

	//���j���[�r�b�g�}�b�v�ǉ�
	GF_BGL_BmpWinAddEx(wk->bgl,win,windata);
	//���j���[���X�g�p������o�b�t�@�쐬
	wk->bmplistdata = BMP_MENULIST_Create(listheader->count,wk->heapID);
	//���j���[���X�g�p������o�b�t�@�擾
	for( i=0; i<listheader->count; i++ ){
		BMP_MENULIST_AddArchiveString(wk->bmplistdata,wk->msg_man,list[i].msgID,list[i].retID);
	}
	//���j���[�r�b�g�}�b�v���X�g�w�b�_�쐬
	listheader_tmp = *listheader;
	listheader_tmp.list = wk->bmplistdata;
	listheader_tmp.win  = win;
	listheader_tmp.call_back = Earth_BmpListMoveSeCall;
	//���j���[�r�b�g�}�b�v���X�g�쐬
	wk->bmplist = BmpListSet(&listheader_tmp,0,0,wk->heapID);

	//�E�C���h�E�i�O�g�j�`��
	BmpMenuWinWrite(listheader_tmp.win,WINDOW_TRANS_OFF,EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL);
	//�u�q�`�l�]��
	GF_BGL_BmpWinOn(win);
}

//----------------------------------
//���X�g�\���Q:gmm�t�@�C���ꊇ�A���X�g�I��Ԃ�l�̓��X�g�̏��ԂƓ���(1orgin)
//----------------------------------
static void Earth_BmpListAddGmmAll( EARTH_DEMO_WORK * wk,
							GF_BGL_BMPWIN* win, const BMPWIN_DAT* windata,
							const BMPLIST_HEADER* listheader,u32 listarcID)
{
	BMPLIST_HEADER	listheader_tmp;
	MSGDATA_MANAGER*	msg_man;
	u32	listcount;
	int	i;

	//���j���[�r�b�g�}�b�v�ǉ�
	GF_BGL_BmpWinAddEx(wk->bgl,win,windata);
		
	msg_man = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,listarcID,wk->heapID );
	//���b�Z�[�W�����擾
	listcount = MSGMAN_GetMessageCount(msg_man);

	//���j���[���X�g�p������o�b�t�@�쐬
	wk->bmplistdata = BMP_MENULIST_Create(listcount,wk->heapID);

	//���j���[���X�g�p������o�b�t�@�擾
	for( i=1; i<listcount; i++ ){	//1�I���W���̂���
		BMP_MENULIST_AddArchiveString(wk->bmplistdata,msg_man,i,i);//BMP,man,msgID,param
	}
	//���b�Z�[�W�f�[�^�j��
	MSGMAN_Delete(msg_man);

	//���j���[�r�b�g�}�b�v���X�g�w�b�_�쐬
	listheader_tmp = *listheader;
	listheader_tmp.list = wk->bmplistdata;
	listheader_tmp.count = listcount-1;	//1origin�̂��ߕ␳
	listheader_tmp.win  = win;
	listheader_tmp.call_back = Earth_BmpListMoveSeCall;
	//���j���[�r�b�g�}�b�v���X�g�쐬
	wk->bmplist = BmpListSet(&listheader_tmp,0,0,wk->heapID);

	//�E�C���h�E�i�O�g�j�`��
	BmpMenuWinWrite(listheader_tmp.win,WINDOW_TRANS_OFF,EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL);
	//�u�q�`�l�]��
	GF_BGL_BmpWinOn(win);
}

//----------------------------------
//���X�g�폜
//----------------------------------
static void Earth_BmpListDel( EARTH_DEMO_WORK* wk )
{
	//�I�����X�g�폜����
	BmpMenuWinClear(&wk->listwin,WINDOW_TRANS_ON);
	GF_BGL_BmpWinDel(&wk->listwin);
	BmpListExit(wk->bmplist,NULL,NULL);
	BMP_MENULIST_Delete(wk->bmplistdata);
}

//----------------------------------
//�o�^�n���\���E�C���h�E
//----------------------------------
static void Earth_MyPlaceInfoWinSet( EARTH_DEMO_WORK* wk )
{
	STRBUF* msgstr = STRBUF_Create(EARTH_STRBUF_SIZE, wk->heapID);	
	STRBUF* msgtmp = STRBUF_Create(EARTH_STRBUF_SIZE, wk->heapID);	

	GF_BGL_BmpWinAddEx(wk->bgl,&wk->infowin,&EarthInfoWinData );
	GF_BGL_BmpWinFill(	&wk->infowin,FBMP_COL_WHITE,0,0,
						EARTH_INFO_WIN_SX*DOTSIZE,EARTH_INFO_WIN_SY*DOTSIZE);
	BmpMenuWinWrite(&wk->infowin,WINDOW_TRANS_ON,EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL);

	WORDSET_RegisterCountryName( wk->wordset, 0, wk->my_nation );
	WORDSET_RegisterLocalPlaceName( wk->wordset, 1, wk->my_nation, wk->my_area );

	//������̎擾
	MSGMAN_GetString(wk->msg_man,mes_earth_03_01,msgtmp);
	WORDSET_ExpandStr( wk->wordset, msgstr, msgtmp );

	//������̕\��
	GF_STR_PrintSimple(	&wk->infowin, FONT_SYSTEM, msgstr, 0, 0, MSG_ALLPUT, NULL );

	STRBUF_Delete( msgtmp );
	STRBUF_Delete( msgstr );

	GF_BGL_BmpWinOn(&wk->infowin);
}

static void Earth_MyPlaceInfoWinSet2( EARTH_DEMO_WORK* wk, int nation, int area )
{
	STRBUF* str1 = STRBUF_Create(EARTH_NAME_SIZE, wk->heapID );
	STRBUF* str2 = STRBUF_Create(EARTH_NAME_SIZE, wk->heapID );

	GF_BGL_BmpWinAddEx(wk->bgl,&wk->infowin,&EarthInfoWinData );
	GF_BGL_BmpWinFill(	&wk->infowin,FBMP_COL_WHITE,0,0,
						EARTH_INFO_WIN_SX*DOTSIZE,EARTH_INFO_WIN_SY*DOTSIZE);
	BmpMenuWinWrite(&wk->infowin,WINDOW_TRANS_ON,EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL);

	WIFI_NationAreaNameGet(	nation, area, str1, str2, wk->heapID );
	if( area != 0 ){
		GF_STR_PrintSimple(&wk->infowin,FONT_SYSTEM,str2,0,16,MSG_NO_PUT,NULL);
	}
	GF_STR_PrintSimple(&wk->infowin,FONT_SYSTEM,str1,0,0,MSG_ALLPUT,NULL);
	STRBUF_Delete(str2);
	STRBUF_Delete(str1);

	GF_BGL_BmpWinOn(&wk->infowin);
}

static void Earth_MyPlaceInfoWinRelease( EARTH_DEMO_WORK* wk )
{
	BmpMenuWinClear(&wk->infowin,WINDOW_TRANS_ON);
	GF_BGL_BmpWinDel(&wk->infowin);
}

//----------------------------------
//�n���\��
//----------------------------------
static void Earth_PosInfoPut( EARTH_DEMO_WORK* wk )
{
	if( wk->info_mode == 0 ){
		{
			STRBUF* msgstr = STRBUF_Create(EARTH_STRBUF_SIZE, wk->heapID);	

			GF_BGL_BmpWinFill(	&wk->msgwin,FBMP_COL_WHITE,0,0,
								EARTH_INFO_WIN_SX*DOTSIZE,EARTH_INFO_WIN_SY*DOTSIZE);
			MSGMAN_GetString(wk->msg_man,mes_earth_03_02,msgstr);
			GF_STR_PrintSimple(	&wk->msgwin, FONT_TALK, msgstr, 0, 0, MSG_ALLPUT, NULL );
			STRBUF_Delete( msgstr );
		}
	} else {
		//�J�[�\���ʒu�n���\��
		{
			int		i;
			BOOL	search_result = FALSE;
			s16		minx = (s16)(wk->rotate.x - 0x30);
			s16		maxx = (s16)(wk->rotate.x + 0x30);
			s16		miny = (s16)(wk->rotate.y - 0x30);
			s16		maxy = (s16)(wk->rotate.y + 0x30);

			for(i=0;i<wk->placelist.listcount;i++){
				if( (wk->placelist.place[i].x > minx)&&(wk->placelist.place[i].x < maxx)
					&&(wk->placelist.place[i].y > miny)&&(wk->placelist.place[i].y < maxy)
					 &&(wk->placelist.place[i].col != MARK_NULL) ){
					{
						STRBUF* str1 = STRBUF_Create(EARTH_NAME_SIZE, wk->heapID );
						STRBUF* str2 = STRBUF_Create(EARTH_NAME_SIZE, wk->heapID );

						GF_BGL_BmpWinFill(	&wk->msgwin,FBMP_COL_WHITE,0,0,
											EARTH_INFO_WIN_SX*DOTSIZE,EARTH_INFO_WIN_SY*DOTSIZE);
						WIFI_NationAreaNameGet(	wk->placelist.place[i].nationID,
												wk->placelist.place[i].areaID,
												str1,str2,wk->heapID);
						if( wk->placelist.place[i].areaID != 0 ){
							GF_STR_PrintSimple(&wk->msgwin,FONT_TALK,str2,0,16,MSG_NO_PUT,NULL);
						}
						GF_STR_PrintSimple(&wk->msgwin,FONT_TALK,str1,0,0,MSG_ALLPUT,NULL);
						STRBUF_Delete(str2);
						STRBUF_Delete(str1);

						search_result = TRUE;
					}
				}
			}
			if( search_result == FALSE ){
				wk->info_mode = 0;
			}
		}
	}
}


//============================================================================================
//
//	���[�J���֐��i�R�c�֘A�j
//
//============================================================================================
//----------------------------------
//�R�c�f�[�^���[�h�֐����R�c�f�[�^�J���֐�
//----------------------------------
static void Earth_ModelLoad( EARTH_DEMO_WORK * wk )
{
	wk->resfileheader = ArchiveDataLoadMalloc	//�n�����f��
						( ARC_WIFI_EARTH, NARC_wifi_earth_wifi_earth_nsbmd, wk->heapID );
	simple_3DModelSetResFileAlready( &wk->renderobj, &wk->resmodel, &wk->resfileheader );
	
	wk->mark_resfileheader[MARK_RED] = ArchiveDataLoadMalloc	//�n�_�}�[�N���f���i�ԁj
						( ARC_WIFI_EARTH, NARC_wifi_earth_earth_mark_r_nsbmd, wk->heapID );
	simple_3DModelSetResFileAlready(	&wk->mark_renderobj[MARK_RED],
										&wk->mark_resmodel[MARK_RED],
										&wk->mark_resfileheader[MARK_RED]);

	wk->mark_resfileheader[MARK_GREEN] = ArchiveDataLoadMalloc	//�n�_�}�[�N���f���i�΁j
						( ARC_WIFI_EARTH, NARC_wifi_earth_earth_mark_g_nsbmd, wk->heapID );
	simple_3DModelSetResFileAlready(	&wk->mark_renderobj[MARK_GREEN],
										&wk->mark_resmodel[MARK_GREEN],
										&wk->mark_resfileheader[MARK_GREEN]);

	wk->mark_resfileheader[MARK_BLUE] = ArchiveDataLoadMalloc	//�n�_�}�[�N���f���i�j
						( ARC_WIFI_EARTH, NARC_wifi_earth_earth_mark_b_nsbmd, wk->heapID );
	simple_3DModelSetResFileAlready(	&wk->mark_renderobj[MARK_BLUE],
										&wk->mark_resmodel[MARK_BLUE],
										&wk->mark_resfileheader[MARK_BLUE]);

	wk->mark_resfileheader[MARK_YELLOW] = ArchiveDataLoadMalloc	//�n�_�}�[�N���f���i���j
						( ARC_WIFI_EARTH, NARC_wifi_earth_earth_mark_y_nsbmd, wk->heapID );
	simple_3DModelSetResFileAlready(	&wk->mark_renderobj[MARK_YELLOW],
										&wk->mark_resmodel[MARK_YELLOW],
										&wk->mark_resfileheader[MARK_YELLOW]);
}

static void Earth_ModelRelease( EARTH_DEMO_WORK * wk )
{
	sys_FreeMemoryEz(wk->mark_resfileheader[MARK_YELLOW]);
	sys_FreeMemoryEz(wk->mark_resfileheader[MARK_BLUE]);
	sys_FreeMemoryEz(wk->mark_resfileheader[MARK_GREEN]);
	sys_FreeMemoryEz(wk->mark_resfileheader[MARK_RED]);
	sys_FreeMemoryEz(wk->resfileheader);
}

//----------------------------------
//���f���֘A�f�[�^�������i�n�_�f�[�^���[�h����j
//----------------------------------
static void EarthDataInit( EARTH_DEMO_WORK * wk )
{
	{//�n���̍��W�������i�n�_�}�[�N�Ƌ��L�j
		
		wk->trans.x	= INIT_EARTH_TRANS_XVAL; 
		wk->trans.y	= INIT_EARTH_TRANS_YVAL; 
		wk->trans.z	= INIT_EARTH_TRANS_ZVAL; 
	}
	{//�n���̃X�P�[��������
		wk->scale.x	= INIT_EARTH_SCALE_XVAL;
		wk->scale.y	= INIT_EARTH_SCALE_YVAL;
		wk->scale.z	= INIT_EARTH_SCALE_ZVAL;
	}
	{//�n���̉�]������
		wk->rotate.x  = INIT_EARTH_ROTATE_XVAL;
		wk->rotate.y  = INIT_EARTH_ROTATE_YVAL;
		wk->rotate.z  = INIT_EARTH_ROTATE_ZVAL;
	}
	{//�n�_�}�[�N�X�P�[��������
		wk->mark_scale.x  = INIT_EARTH_SCALE_XVAL;
		wk->mark_scale.y  = INIT_EARTH_SCALE_YVAL;
		wk->mark_scale.z  = INIT_EARTH_SCALE_ZVAL;
	}
}

//----------------------------------
//�J����������
//----------------------------------
static void EarthCameraInit( EARTH_DEMO_WORK * wk )
{
	VecFx32	target_pos	= 	{ INIT_CAMERA_TARGET_XVAL,
							  INIT_CAMERA_TARGET_YVAL,
							  INIT_CAMERA_TARGET_ZVAL };
	VecFx32	camera_pos	=	{ INIT_CAMERA_POS_XVAL,
							  INIT_CAMERA_POS_YVAL,
							  INIT_CAMERA_POS_ZVAL };

	//�J�������C�u����������
	GFC_InitCameraTC(	&target_pos,&camera_pos,
						INIT_CAMERA_PERSPWAY,
						GF_CAMERA_PERSPECTIV,
						FALSE,
						wk->camera_p);

	//�N���b�v�֘A�ݒ�
	GFC_SetCameraClip(INIT_CAMERA_CLIP_NEAR,INIT_CAMERA_CLIP_FAR,wk->camera_p);
	GFC_SetCameraView(GF_CAMERA_PERSPECTIV,wk->camera_p);
	//�J�����n�m
	GFC_AttachCamera(wk->camera_p);

	if(wk->earth_mode == JAPAN_MODE){
		//�J���������t���O�������i�J�n���͋ߋ����j
		wk->camera_status = CAMERA_NEAR;
	}else{
		//�J���������t���O�������i�J�n���͉������j
		wk->camera_status = CAMERA_FAR;
	}
	while(1){
		//�J�����ݒ�
		if(Earth3D_CameraMoveNearFar(wk) == TRUE){
			break;
		}
	}
}

//----------------------------------
//���C�g������
//----------------------------------
static void EarthLightInit( EARTH_DEMO_WORK * wk )
{
	wk->light_vec.x = INIT_LIGHT_ANGLE_XVAL;
	wk->light_vec.y = INIT_LIGHT_ANGLE_YVAL;
	wk->light_vec.z = INIT_LIGHT_ANGLE_ZVAL;
	NNS_G3dGlbLightVector(USE_LIGHT_NUM,wk->light_vec.x,wk->light_vec.y,wk->light_vec.z);
	//NNS_G3dGlbLightVector(1,-LIGHT_VECDEF,-LIGHT_VECDEF,-LIGHT_VECDEF);
}

//----------------------------------
//�R�c��]�v�Z
//----------------------------------
static void  EarthVecFx32_to_MtxFx33( MtxFx33* dst, VecFx32* src )
{
	MtxFx33 tmp;

	MTX_RotY33(	dst,FX_SinIdx((u16)src->y),FX_CosIdx((u16)src->y));

	MTX_RotX33(	&tmp,FX_SinIdx((u16)src->x),FX_CosIdx((u16)src->x));
	MTX_Concat33(dst,&tmp,dst);

	MTX_RotZ33(	&tmp,FX_SinIdx((u16)src->z),FX_CosIdx((u16)src->z));
	MTX_Concat33(dst,&tmp,dst);
}

//----------------------------------
//�R�c��]�v�Z(����)
//----------------------------------
static void  EarthVecFx32_to_MtxFx33_place( MtxFx33* dst, VecFx32* src )
{
	MtxFx33 tmp;

	MTX_RotY33(	dst,FX_SinIdx((u16)src->x),FX_CosIdx((u16)src->x));

	MTX_RotX33(	&tmp,FX_SinIdx((u16)-src->y),FX_CosIdx((u16)-src->y));
	MTX_Concat33(dst,&tmp,dst);

	MTX_RotZ33(	&tmp,FX_CosIdx((u16)src->z),FX_SinIdx((u16)src->z));
	MTX_Concat33(dst,&tmp,dst);
}

//----------------------------------
//�n������֐�
//----------------------------------
static BOOL Earth3D_Control( EARTH_DEMO_WORK * wk,int keytrg,int keycont )
{
	u16 rotate_speed_x;
	u16 rotate_speed_y;
	s16 rotate_x;
	s16 rotate_y;
	BOOL result = FALSE;

	rotate_x = wk->rotate.x;
	rotate_y = wk->rotate.y;

	//�J�������߈ړ�����i���E�n���V���[�h�̂݁j
	if((keytrg & PAD_BUTTON_A)||(wk->tp_result & PAD_BUTTON_A)){
		if(wk->earth_mode == GLOBAL_MODE){
			if(wk->camera_status == CAMERA_FAR){
				wk->camera_status = CAMERA_NEAR;
			}else{
				wk->camera_status = CAMERA_FAR;
			}
		}
		result = TRUE;
		return result;
	}
	//�J�����ړ��X�s�[�h�����ݒ�
	if(wk->camera_status == CAMERA_FAR){
		//������
		if((wk->tp_lenx)||(wk->tp_leny)){ //�^�b�`�p�l�����͂���
			rotate_speed_x = CAMERA_MOVE_SPEED_FAR/8 * wk->tp_lenx;
			rotate_speed_y = CAMERA_MOVE_SPEED_FAR/8 * wk->tp_leny;
		}else{
			rotate_speed_x = CAMERA_MOVE_SPEED_FAR;
			rotate_speed_y = CAMERA_MOVE_SPEED_FAR;
		}
	}else{
		//�ߋ���
		if((wk->tp_lenx)||(wk->tp_leny)){ //�^�b�`�p�l�����͂���
			rotate_speed_x = CAMERA_MOVE_SPEED_NEAR/8 * wk->tp_lenx;
			rotate_speed_y = CAMERA_MOVE_SPEED_NEAR/8 * wk->tp_leny;
		}else{
			rotate_speed_x = CAMERA_MOVE_SPEED_NEAR;
			rotate_speed_y = CAMERA_MOVE_SPEED_NEAR;
		}
	}
	//�J�����㉺���E�ړ�����
	if((keycont & PAD_KEY_LEFT)||(wk->tp_result & PAD_KEY_LEFT)){
		if(wk->earth_mode == GLOBAL_MODE){
			wk->rotate.y += rotate_speed_x;
		}else{
			//if((u16)wk->rotate.y < EARTH_LIMIT_ROTATE_YMAX){
			if(rotate_y < (s16)EARTH_LIMIT_ROTATE_YMAX){
				wk->rotate.y += rotate_speed_x;
			}
		}
		result = TRUE;
	}
	if((keycont & PAD_KEY_RIGHT)||(wk->tp_result & PAD_KEY_RIGHT)){
		if(wk->earth_mode == GLOBAL_MODE){
			wk->rotate.y -= rotate_speed_x;
		}else{
			//if((u16)wk->rotate.y > EARTH_LIMIT_ROTATE_YMIN){
			if(rotate_y > (s16)EARTH_LIMIT_ROTATE_YMIN){
				wk->rotate.y -= rotate_speed_x;
			}
		}
		result = TRUE;
	}
	if((keycont & PAD_KEY_UP)||(wk->tp_result & PAD_KEY_UP)){
		if(wk->earth_mode == GLOBAL_MODE){
			//if(((u16)(wk->rotate.x + rotate_speed_y)) < CAMERA_ANGLE_MAX){
			if((rotate_x + rotate_speed_y) < CAMERA_ANGLE_MAX){
				wk->rotate.x += rotate_speed_y;
			}else{
				wk->rotate.x = CAMERA_ANGLE_MAX;
			}
		}else{
			//if((u16)wk->rotate.x < EARTH_LIMIT_ROTATE_XMAX){
			if(rotate_x < (s16)EARTH_LIMIT_ROTATE_XMAX){
				wk->rotate.x += rotate_speed_y;
			}
		}
		result = TRUE;
	}
	if((keycont & PAD_KEY_DOWN)||(wk->tp_result & PAD_KEY_DOWN)){
		if(wk->earth_mode == GLOBAL_MODE){
			//if(((u16)(wk->rotate.x - rotate_speed_y)) > CAMERA_ANGLE_MIN){
			if((rotate_x - rotate_speed_y) > CAMERA_ANGLE_MIN){
				wk->rotate.x -= rotate_speed_y;
			}else{
				wk->rotate.x = CAMERA_ANGLE_MIN;
			}
		}else{
			//if((u16)wk->rotate.x > EARTH_LIMIT_ROTATE_XMIN){
			if(rotate_x > (s16)EARTH_LIMIT_ROTATE_XMIN){
				wk->rotate.x -= rotate_speed_y;
			}
		}
		result = TRUE;
	}
	return result;
}

//----------------------------------
//�J�������߈ړ��֐�
//----------------------------------
static BOOL Earth3D_CameraMoveNearFar( EARTH_DEMO_WORK * wk )
{
	fx32 distance = GFC_GetCameraDistance(wk->camera_p);
	BOOL result = FALSE;

	switch(wk->camera_status){

	case CAMERA_NEAR://�߂Â�
		if(distance > (INIT_CAMERA_DISTANCE_NEAR + CAMERA_INOUT_SPEED)){
			distance -= CAMERA_INOUT_SPEED;
			wk->mark_scale.x -= MARK_SCALE_INCDEC;
			wk->mark_scale.y = wk->mark_scale.x;
		}else{
			distance = INIT_CAMERA_DISTANCE_NEAR;
			result = TRUE;
		}
		break;

	case CAMERA_FAR://��������
		if(distance < (INIT_CAMERA_DISTANCE_FAR - CAMERA_INOUT_SPEED)){
			distance += CAMERA_INOUT_SPEED;
			wk->mark_scale.x += MARK_SCALE_INCDEC;
			wk->mark_scale.y = wk->mark_scale.x;
		}else{
			distance = INIT_CAMERA_DISTANCE_FAR;
			result = TRUE;
		}
		break;
	}
	GFC_SetCameraDistance(distance,wk->camera_p);

	return result;
}

//----------------------------------
//�R�c�`��֐�
//----------------------------------
static void Earth3D_Draw( EARTH_DEMO_WORK * wk )
{
	MtxFx33 rotate_world = {FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};

	//�`��t���O����
	switch(wk->Draw3Dsw){

	case DRAW3D_DISABLE:
		break;

	case DRAW3D_BANISH:
		GF_G3X_Reset();
		GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO,GX_BUFFERMODE_W);
		wk->Draw3Dsw = DRAW3D_DISABLE;
		break;

	case DRAW3D_ENABLE:
		GF_G3X_Reset();
		GFC_CameraLookAt();
		{
			//�O���[�o����]�s��擾
			EarthVecFx32_to_MtxFx33(&rotate_world,&wk->rotate);
	
			//�n���`��
			simple_3DModelDraw(&wk->renderobj,&wk->trans,&rotate_world,&wk->scale);
			//GF_G3D_Draw_1mat1shape(&wk->renderobj,&wk->trans,&rotate_world,&wk->scale);
	
			//���S�}�[�N�`��i��_�̂��߉�]�Ȃ��j
			{
				MtxFx33 rotate_tmp = {FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};
				simple_3DModelDraw(&wk->mark_renderobj[MARK_GREEN],
						&wk->trans,&rotate_tmp,&wk->mark_scale);
				//GF_G3D_Draw_1mat1shape(&wk->mark_renderobj[MARK_GREEN],
				//		&wk->trans,&rotate_tmp,&wk->mark_scale);
			}
	
			//�n�_�}�[�N�`��
			{
				MtxFx33 rotate_tmp = {FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};
				int	i;
	
				for(i=0;i<wk->placelist.listcount;i++){
					MTX_Concat33(&wk->placelist.place[i].rotate,&rotate_world,&rotate_tmp);
	
					if(wk->placelist.place[i].col != MARK_NULL){
						simple_3DModelDraw(	&wk->mark_renderobj[wk->placelist.place[i].col],
											&wk->trans,&rotate_tmp,&wk->mark_scale);
						//GF_G3D_Draw_1mat1shape(	&wk->mark_renderobj[wk->placelist.place[i].col],
						//					&wk->trans,&rotate_tmp,&wk->mark_scale);
					}
				}
			}
		}
		GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO,GX_BUFFERMODE_W);
		break;
	}
}
	
//============================================================================================
//
//	�O���[�o���֐��i�n��f�[�^�擾�֘A�j
//
//============================================================================================
//============================================================================================
/**
 *	�n��f�[�^�������i�Z�[�u���[�N�̏������j
 *
 * @param	
 * @retval
 */
//============================================================================================
void	WIFI_RegistratonInit(SAVEDATA* savedata)
{
	WIFI_HISTORY* wh = SaveData_GetWifiHistory(savedata);

	WIFIHISTORY_SetMyNationArea(wh,0,0);
	WIFIHISTORY_SetWorldFlag(wh,FALSE);
}

//============================================================================================
/**
 *	�����擾
 *
 * @param[in]	nationID	���h�c
 * @param[in]	areaID		�n��h�c
 * @param[in]	nation_str	�����i�[�o�b�t�@�|�C���^
 * @param[in]	area_str	�n�於�i�[�o�b�t�@�|�C���^
 * @param[in]	heapID		�e���|�����q�[�v�h�c
 *
 * @retval	FALSE:�n�悪�Ȃ����@TRUE:�n�悪���鍑
 */
//============================================================================================
BOOL	WIFI_NationAreaNameGet(int nationID,int areaID,
								STRBUF* nation_str,STRBUF* area_str,int heapID)
{
	MSGDATA_MANAGER*	msg_man;
	int areaIndex = EarthAreaTableGet(nationID);	//�n��f�[�^�e�[�u���h�m�c�d�w�擾
	BOOL result;

	msg_man = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
							NARC_msg_wifi_place_msg_world_dat,heapID );

	MSGMAN_GetString(msg_man,nationID,nation_str);//�����擾

	MSGMAN_Delete(msg_man);

	if(areaIndex == 0){
		//�n�悪���݂��Ȃ����̏ꍇ�u�Ȃ��v�Ƃ�����������ꉞ�Z�b�g
		areaIndex = 1;
		areaID = 0;
		result = FALSE;
	}else{
		result = TRUE;
	}
	msg_man = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
							WIFI_COUNTRY_DataIndexToPlaceMsgDataID(areaIndex), heapID );

	MSGMAN_GetString(msg_man,areaID,area_str);//�n�於�擾
	
	MSGMAN_Delete(msg_man);

	return result;
}

//============================================================================================
/**
 *	���[�J���G���A���݃`�F�b�N
 *
 * @param[in]	nationID	���h�c
 *
 * @retval	FALSE:�n��Ȃ��@TRUE:�n�悠��
 */
//============================================================================================
BOOL	WIFI_LocalAreaExistCheck(int nationID)
{
	if(EarthAreaTableGet(nationID)){
		return TRUE;
	}else{
		return FALSE;
	}
}

//----------------------------------
// �f�o�b�O
//----------------------------------
#ifdef WIFI_ERATH_DEBUG
static void EarthDebugWinRotateInfoWrite( EARTH_DEMO_WORK * wk )
		
{
	STRBUF* str1 = STRBUF_Create(10, HEAPID_BASE_DEBUG);
	STRBUF* str2 = STRBUF_Create(10, HEAPID_BASE_DEBUG);

	STRBUF_SetHexNumber( str1, (u16)wk->rotate.x, 4, 
						NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	STRBUF_SetHexNumber( str2, (u16)wk->rotate.y, 4, 
						NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(&wk->msgwin, FONT_SYSTEM, str1, 0, 0, MSG_NO_PUT, NULL );
	GF_STR_PrintSimple(&wk->msgwin, FONT_SYSTEM, str2, 0, 16, MSG_ALLPUT, NULL );

	STRBUF_Delete(str2);
	STRBUF_Delete(str1);
}

static void EarthDebugWinNameInfoWrite( EARTH_DEMO_WORK * wk )
		
{
	STRBUF	*str1,*str2;
	int	i;

	if(!wk->debug_work[0]){
		for(i=0;i<wk->placelist.listcount;i++){
			if((wk->placelist.place[i].x == (s16)wk->rotate.x)
				&&(wk->placelist.place[i].y == (s16)wk->rotate.y)){
	
				str1 = STRBUF_Create(EARTH_NAME_SIZE, HEAPID_BASE_DEBUG);
				str2 = STRBUF_Create(EARTH_NAME_SIZE, HEAPID_BASE_DEBUG);

				WIFI_NationAreaNameGet(	wk->placelist.place[i].nationID,
										wk->placelist.place[i].areaID,
										str1,str2,wk->heapID);
				GF_STR_PrintSimple(&wk->msgwin, FONT_SYSTEM, str1, 16*4, 0, MSG_NO_PUT, NULL );
				GF_STR_PrintSimple(&wk->msgwin, FONT_SYSTEM, str2, 16*4, 16, MSG_ALLPUT, NULL );

				STRBUF_Delete(str2);
				STRBUF_Delete(str1);

				wk->debug_work[0] = 1;
			}
		}
	}else{
		str1 = STRBUF_Create(10, HEAPID_BASE_DEBUG);
		str2 = STRBUF_Create(10, HEAPID_BASE_DEBUG);

		GF_BGL_BmpWinFill(&wk->msgwin,FBMP_COL_WHITE,0,0,
							EARTH_MSG_WIN_SX*DOTSIZE,EARTH_MSG_WIN_SY*DOTSIZE);
		STRBUF_SetHexNumber( str1, (u16)wk->rotate.x, 4, 
							NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
		STRBUF_SetHexNumber( str2, (u16)wk->rotate.y, 4, 
							NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&wk->msgwin, FONT_SYSTEM, str1, 0, 0, MSG_NO_PUT, NULL );
		GF_STR_PrintSimple(&wk->msgwin, FONT_SYSTEM, str2, 0, 16, MSG_ALLPUT, NULL );

		STRBUF_Delete(str2);
		STRBUF_Delete(str1);

		wk->debug_work[0] = 0;
	}
}

static void EarthDebugNationMarkSet( EARTH_DEMO_WORK * wk )
{
	u16 pattern_flag = WIFIHIST_STAT_NODATA;
	u16 cursor_pos;
	int	nationID;

	if(sys.trg & PAD_BUTTON_SELECT){
		pattern_flag = WIFIHIST_STAT_NEW;
	}
	if(sys.trg & PAD_BUTTON_SELECT){
		pattern_flag = WIFIHIST_STAT_EXIST;
	}
	if(pattern_flag == WIFIHIST_STAT_NODATA){
		return;
	}
	BmpListDirectPosGet(wk->bmplist,&cursor_pos);

	nationID = cursor_pos+1;	//1origin

	if(WIFI_LocalAreaExistCheck(nationID) == FALSE){
		//�n�悪���݂��Ȃ��ꍇ�̂ݐݒ�
		WIFIHISTORY_SetStat(wk->wifi_sv,nationID,0,pattern_flag);
	}
	EarthListLoad(wk);	//reload
}

static void EarthDebugAreaMarkSet( EARTH_DEMO_WORK * wk )
{
	u16 pattern_flag = WIFIHIST_STAT_NODATA;
	u16 cursor_pos;
	int	areaID;

	if(sys.trg & PAD_BUTTON_SELECT){
		pattern_flag = WIFIHIST_STAT_NEW;
	}
	if(sys.trg & PAD_BUTTON_SELECT){
		pattern_flag = WIFIHIST_STAT_EXIST;
	}
	if(pattern_flag == WIFIHIST_STAT_NODATA){
		return;
	}
	BmpListDirectPosGet(wk->bmplist,&cursor_pos);

	areaID = cursor_pos+1;	//1origin

	WIFIHISTORY_SetStat(wk->wifi_sv,wk->my_nation_tmp,areaID,pattern_flag);
	EarthListLoad(wk);	//reload
}

#endif



















