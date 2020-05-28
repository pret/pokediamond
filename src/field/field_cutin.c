//******************************************************************************
/**
 * 
 * @file	field_cutin.c
 * @brief	フィールド　カットイン
 * @author	kagaya
 * @data	05.07.13
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldmap.h"
#include "fieldobj.h"
#include "field_event.h"
#include "field_cutin.h"
#include "eoa.h"
#include "talk_msg.h"

#include "system/wipe.h"
#include "system/clact_util.h"
#include "system/arc_util.h"
#include "system/gra_tool.h"
#include "poketool/poke_tool.h"

#include "field_cutin.naix"

#include "field_zoom.h"

#include "system\snd_tool.h"

//==============================================================================
//	define
//==============================================================================
///num -> fx32
#define NUMFX32(a) (FX32_ONE*(a))
///fx32 -> num
#define FX32NUM(a) ((a)/FX32_ONE)

#define POKE_CHAR_SIZE ((32*10)*10) //1chara x10 y10
#define POKE_PLTT_SIZE (32)

#define CUTIN_ZOOM (NUM_FX32(120))

//--------------------------------------------------------------
///カットイン動作終了
//--------------------------------------------------------------
enum
{
	CUTIN_RET_RETURN = 0,
	CUTIN_RET_REPEAT,
	CUTIN_RET_END,
};

//--------------------------------------------------------------
//	tcb	プライオリティ
//--------------------------------------------------------------
enum
{
	TCBPRI_CUTIN_EOA_TOP = 128,
	TCBPRI_CUTIN_EOA_HERO,
	TCBPRI_CUTIN_EOA_BIRD,
	TCBPRI_CUTIN_EOA_CAMERA,
	TCBPRI_CUTIN_EOA_LIGHT,
	TCBPRI_CUTIN_UPDATE,
	TCBPRI_CUTIN_EOA_HERO_WIN_VANISH,
};

//--------------------------------------------------------------
///	アクタープライオリティ
//--------------------------------------------------------------
enum
{
	ACTPRI_CUTIN_LIGHT_1 = 128,
	ACTPRI_CUTIN_POKE,
	ACTPRI_CUTIN_BIRD_HI,
	ACTPRI_CUTIN_HERO,
	ACTPRI_CUTIN_BIRD_LOW,
	ACTPRI_CUTIN_LIGHT_0,
};

//--------------------------------------------------------------
///	自機アニメ番号
//--------------------------------------------------------------
enum
{
	JIKIANMNO_STOP_U = 0,
	JIKIANMNO_STOP_D,
	JIKIANMNO_STAY_U,
	JIKIANMNO_STAY_D,
	JIKIANMNO_JUMP_U,
	JIKIANMNO_JUMP_D,
	JIKIANMNO_HIDEN,
};

//--------------------------------------------------------------
//	BGフレーム
//--------------------------------------------------------------
///カットイン使用BGフレーム
#define CUTIN_BG_FRAME (FLD_MBGFRM_FONT)
///ウィンドウ指定BGフレーム
#define CUTIN_BG_WINMASK (GX_WND_PLANEMASK_BG3)
///ウィンドウ指定BGフレーム　マスク
#define CUTIN_BG_WINMASK_NOT (~CUTIN_BG_WINMASK)

///カットイン中心
#define CUTIN_SY (96-40)
#define CUTIN_CY (96)
#define CUTIN_EY (96+40)

//--------------------------------------------------------------
//	BGキャラクタ
//--------------------------------------------------------------
#define CUTIN_BG_SET_CHAR_OFFSET (0)			//カットインBGキャラ使用位置オフセット

//--------------------------------------------------------------
//	BGパレット
//--------------------------------------------------------------
///BG パレットサイズ
#define BG_PLTT_SIZE (32)
///カットインで使用するパレット番号
#define CUTIN_BG_PLTT_NO (12)
///カットインで使用するパレットサイズ
#define CUTIN_BG_PLTT_SIZE (BG_PLTT_SIZE*1)
///カットインBGパレット使用位置オフセット
#define	CUTIN_BG_SET_PLTT_OFFSET (BG_PLTT_SIZE*CUTIN_BG_PLTT_NO)

//--------------------------------------------------------------
//	ウィンドウ
//--------------------------------------------------------------
///使用ウィンドウ
#define CUTIN_WND (GX_WNDMASK_W0)

//--------------------------------------------------------------
//	アクター
//--------------------------------------------------------------
///セルアクター総数
#define CUTIN_CA_MAX (32)
///EOA総数
#define CUTIN_EOA_MAX (32)

//--------------------------------------------------------------
//	セルアクターリソース
//--------------------------------------------------------------
///キャラ使用数
enum
{
	CUTIN_CAUSE_CHAR_LIGHT,
	CUTIN_CAUSE_CHAR_ALWAYS_MAX,
	
	CUTIN_CAUSE_CHAR_HERO = CUTIN_CAUSE_CHAR_ALWAYS_MAX,
	CUTIN_CAUSE_CHAR_POKE,
	CUTIN_CAUSE_CHAR_BIRD,
	CUTIN_CAUSE_CHAR_MAX,
};

///キャラID
enum
{
	CUTIN_CAID_CHAR_BIRD = 0,
	CUTIN_CAID_CHAR_LIGHT,
	CUTIN_CAID_CHAR_HERO,
	CUTIN_CAID_CHAR_POKE,
	CUTIN_CAID_CHAR_MAX,
};

///パレット使用数
enum
{
	CUTIN_CAUSE_PLTT_HERO_BIRD = 0,
	CUTIN_CAUSE_PLTT_ALWAYS_MAX,
	
	CUTIN_CAUSE_PLTT_HEROINE = CUTIN_CAUSE_PLTT_ALWAYS_MAX,
	CUTIN_CAUSE_PLTT_POKE,
	CUTIN_CAUSE_PLTT_MAX,
};

///パレットID
enum
{
	CUTIN_CAID_PLTT_HERO_BIRD = 0,
	CUTIN_CAID_PLTT_HEROINE,
	CUTIN_CAID_PLTT_POKE,
	CUTIN_CAID_PLTT_MAX,
};

///セル使用数
enum
{
	CUTIN_CAUSE_CELL_LIGHT = 0,
	CUTIN_CAUSE_CELL_ALWAYS_MAX,
	
	CUTIN_CAUSE_CELL_HERO = CUTIN_CAUSE_CELL_ALWAYS_MAX,
	CUTIN_CAUSE_CELL_POKE,
	CUTIN_CAUSE_CELL_BIRD,
	CUTIN_CAUSE_CELL_MAX,
};

///セルID
enum
{
	CUTIN_CAID_CELL_BIRD = 0,
	CUTIN_CAID_CELL_LIGHT,
	CUTIN_CAID_CELL_HERO,
	CUTIN_CAID_CELL_POKE,
	CUTIN_CAID_CELL_MAX,
};

///アニメ使用数
enum
{
	CUTIN_CAUSE_ANM_LIGHT = 0,
	CUTIN_CAUSE_ANM_ALWAYS_MAX,
	
	CUTIN_CAUSE_ANM_HERO = CUTIN_CAUSE_ANM_ALWAYS_MAX,
	CUTIN_CAUSE_ANM_MAX,
};

///アニメID
enum
{
	CUTIN_CAID_ANM_LIGHT = 0, 
	CUTIN_CAID_ANM_HERO,
	CUTIN_CAID_ANM_MAX,
};

//--------------------------------------------------------------
//	光アニメ
//--------------------------------------------------------------
enum
{
	LIGHT_ANMNO_0= 0,
	LIGHT_ANMNO_1,
};

//--------------------------------------------------------------
//	光線消去フラグ
//--------------------------------------------------------------
enum
{
	LIGHT_ON = 0,
	LIGHT_OFF,
	LIGHT_WINDEL,
};

//--------------------------------------------------------------
///	鳥動作ステータス
//--------------------------------------------------------------
enum
{
	BIRD_MOVESTATE_NON = 0,
	BIRD_MOVESTATE_MOVE,
	BIRD_MOVESTATE_END,
	BIRD_MOVESTATE_RIDE_ON,
	BIRD_MOVESTATE_RIDE_ON_REQ_FADE,
};

//--------------------------------------------------------------
//	鳥動作タイプ
//--------------------------------------------------------------
enum
{
	BIRD_MOVETYPE_NON = 0,
	BIRD_MOVETYPE_START_UP,
	BIRD_MOVETYPE_RIDE_ON,
};

//--------------------------------------------------------------
//	自機動作タイプ
//--------------------------------------------------------------
enum
{
	JIKI_MOVETYPE_NON = 0,
	JIKI_MOVETYPE_JUMP,
	JIKI_MOVETYPE_LANDING,
};

//--------------------------------------------------------------
///	カメラ移動タイプ
//--------------------------------------------------------------
enum
{
	CAMERA_MOVETYPE_NON = 0,
	CAMERA_MOVETYPE_ZOOMIN,
	CAMERA_MOVETYPE_ZOOMOUT,
	CAMERA_MOVETYPE_ZOOMIN_LANDING,
	CAMERA_MOVETYPE_ZOOMOUT_LANDING,
};

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	CUTIN_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int end_flag;
	int wait;
	int sex;
	int draw_on;
	int windel_light_flag;
	int fade_flag;
	int winvanishoff_hero_flag;
	
	u32 cutin_type;
	u16 save_bg0pri;
	u16 save_bg2pri;
	
	int win_seqno;
	int win_setflag;
	u32 win0_visible;
	u32 win0_inside;
	u32 win0_inside_alpha;
	u32 win0_outside;
	u32 win0_outside_alpha;
	fx32 win_x0;
	fx32 win_x1;
	fx32 win_y0;
	fx32 win_y1;
	fx32 win_val;
	fx32 val;
	
	POKEMON_PARAM *poke_param;
	FIELDSYS_WORK *fsys;
	
	NNSG2dScreenData *pScreen;
	NNSG2dCharacterData *pChar;
	NNSG2dPaletteData *pPltt;
	
	CLACT_SET_PTR clact_set;
	CLACT_U_EASYRENDER_DATA clact_easydata;
	CLACT_U_RES_MANAGER_PTR clact_resm_char;
	CLACT_U_RES_MANAGER_PTR clact_resm_pltt;
	CLACT_U_RES_MANAGER_PTR clact_resm_cell;
	CLACT_U_RES_MANAGER_PTR clact_resm_anime;
	
	CLACT_U_RES_OBJ_PTR clact_resobj_char[CUTIN_CAUSE_CHAR_MAX];
	CLACT_U_RES_OBJ_PTR clact_resobj_pltt[CUTIN_CAUSE_PLTT_MAX];
	CLACT_U_RES_OBJ_PTR clact_resobj_cell[CUTIN_CAUSE_CELL_MAX];
	CLACT_U_RES_OBJ_PTR clact_resobj_anime[CUTIN_CAUSE_ANM_MAX];
	
	EOA_SYS_PTR cutin_eoa_sys;
	
	CLACT_WORK_PTR clact_hero;
	CLACT_WORK_PTR clact_poke;
	
	EOA_PTR eoa_bird;
	EOA_PTR eoa_herowinvanish;
	
	SOFT_SPRITE_ARC ssa;
	
	int tcb_vintr_seq;
	int tcb_vintr_end;
	void *poke_char_buf;
	void *poke_pal_buf;
	TCB_PTR tcb_vintr;
	TCB_PTR tcb_vintr_window;
}CUTIN_WORK;

#define CUTIN_WORK_SIZE (sizeof(CUTIN_WORK))

//--------------------------------------------------------------
//	NARC_ID構造体
//--------------------------------------------------------------
typedef struct
{
	u32 reg_id;
	u32 narc_id;
}NARC_ID;

//--------------------------------------------------------------
///	BIRD_ADD_H構造体
//--------------------------------------------------------------
typedef struct
{
	CUTIN_WORK *cutin;
}BIRD_ADD_H;

//--------------------------------------------------------------
///	BIRD_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	u8 move_type;
	u8 seq_no;
	u8 move_state;
	u8 jiki_seq_no;
	int frame;
	
	VecFx32 mtx;
	VecFx32 offs;
	VecFx32 val;
	VecFx32 scale;
	fx32 rot;
	fx32 rot_val;
	fx32 angle;
	fx32 angle_val;
	fx32 angle_scale;
	fx32 angle_scale_val;
	fx32 scale_val;
	fx32 joint_val;
	CLACT_WORK_PTR clact;
	BIRD_ADD_H head;
	EOA_PTR eoa_jikimove;
	TCB_PTR tcb_camera;
}BIRD_WORK;

#define BIRD_WORK_SIZE (sizeof(BIRD_WORK))

//--------------------------------------------------------------
///	JIKI_MOVE_H
//--------------------------------------------------------------
typedef struct
{
	CUTIN_WORK *cut;
	CLACT_WORK_PTR clact;
}JIKI_MOVE_H;

//--------------------------------------------------------------
///	JIKI_MOVE_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	int move_type;
	int seq_no;
	int end_flag;
	int frame;
	VecFx32 offs;
	CUTIN_WORK *cut;
	CLACT_WORK_PTR clact;
}JIKI_MOVE_WORK;

//==============================================================================
//	プロトタイプ
//==============================================================================
static CUTIN_WORK * CutIn_AllocMemory( FIELDSYS_WORK *fsys );
static void CutIn_FreeMemory( CUTIN_WORK *cut );

static void CutIn_UpdateTCB( TCB_PTR tcb, void *work );
int (* const DATA_CutInUpdateTbl[])( CUTIN_WORK *cut );

static void CutInSky_UpdateTCB( TCB_PTR tcb, void *work );
int (* const DATA_CutInSkyUpdateTbl[])( CUTIN_WORK *cut );

static void CutIn_VIntrInitTcbAdd( CUTIN_WORK *cut );
static void CutIn_VIntrBirdInitTcbAdd( CUTIN_WORK *cut );
static void CutIn_VIntrTcbDelete( CUTIN_WORK *cut );
static void CutIn_VIntrInitTcb( TCB_PTR tcb, void *wk );
static void CutIn_VWaitInitTcb( TCB_PTR tcb, void *wk );
static void CutIn_VIntrBirdInitTcb( TCB_PTR tcb, void *wk );
static void CutIn_VWaitBirdInitTcb( TCB_PTR tcb, void *wk );

static void CutIn_GraphicInit( CUTIN_WORK *cut );
static void CutIn_GraphicDelete( CUTIN_WORK *cut );
static ARCHANDLE * CutIn_ArcHandleOpen( void );

static void CutIn_ClactInit( CUTIN_WORK *cutin, ARCHANDLE *ahand );
static void CutIn_ClactDest( CUTIN_WORK *cutin );
static void CutIn_ClactDraw( CUTIN_WORK *cutin );
static CLACT_WORK_PTR CutIn_ClActAdd( CUTIN_WORK *cutin, const VecFx32 *vec,
		u32 char_id, u32 pltt_id, u32 cell_id, u32 cellanm_id, int bg_pri, int act_pri );
static CLACT_WORK_PTR CutIn_ClactAdd_Light(
		CUTIN_WORK *cutin, const VecFx32 *vec, int act_pri, int anm_no );
static CLACT_WORK_PTR CutIn_ClactAdd_Hero( CUTIN_WORK *cutin, const VecFx32 *vec );
static void CutIn_ClactAutoAnimeStart( CLACT_WORK_PTR act );
static CLACT_WORK_PTR CutIn_ClactAdd_Bird(
		CUTIN_WORK *cutin, const VecFx32 *vec, int act_pri, int anm_no );
static void CutIn_ClActBirdGraphicInit( CUTIN_WORK *cutin );

static void CutIn_BGPaletteInit( ARCHANDLE *ahand, u32 arc_id, NNSG2dPaletteData **pPltt );
static void CutIn_BGCharInit(
		GF_BGL_INI *ini, ARCHANDLE *ahand, u32 arc_id, NNSG2dCharacterData **pChar );
static void CutIn_BGScreenInit( 
		GF_BGL_INI *ini, ARCHANDLE *ahand, u32 arc_id, NNSG2dScreenData **pScr );
static void CutIn_BGScreenClear( GF_BGL_INI *ini );

static void CutIn_WndInit( CUTIN_WORK *cut );
static void CutIn_WndON( CUTIN_WORK *cut );
static void CutIn_WndOFF( CUTIN_WORK *cut );
static void CutIn_WndPlaneInit( CUTIN_WORK *cut );
static void CutIn_WndPlaneOutsideOBJ_ON( CUTIN_WORK *cut );
static void CutIn_WndPosSet( CUTIN_WORK *cut, fx32 x0, fx32 y0, fx32 x1, fx32 y1 );
static void Cip_VIntrTcbWindowInit( CUTIN_WORK *cut );
static void Cip_VIntrTcbWindowDelete( CUTIN_WORK *cut );
static void Cip_VIntrTcbWindow( TCB_PTR tcb, void *wk );

static void CutIn_PokeGraSoftSpriteArcMake( CUTIN_WORK *cut, SOFT_SPRITE_ARC *ssa );
static void * CutIn_PokeGraOamGet( POKEMON_PARAM *param, SOFT_SPRITE_ARC *ssa, u32 heap_id );
static void * CutIn_PokeGraPlttGet( SOFT_SPRITE_ARC *ssa, u32 heap_id );
static CLACT_U_RES_OBJ_PTR CutIn_PokeGraResmAddCharDummy( CUTIN_WORK *cutin, ARCHANDLE *ahand );
static void CutIn_PokeGraResmSetCleanAreaChar( CUTIN_WORK *cutin, void *buf );
static CLACT_U_RES_OBJ_PTR CutIn_PokeGraResmAddPlttDummy( CUTIN_WORK *cutin, ARCHANDLE *ahand );
static void CutIn_PokeGraResmSetCleanAreaPltt( CUTIN_WORK *cutin, void *buf );
static void CutIn_PokeGraResmDelete( CUTIN_WORK *cutin );
static CLACT_WORK_PTR CutIn_ClactAdd_Poke( CUTIN_WORK *cutin, const VecFx32 *vec );

static void CutIn_LightSet( CUTIN_WORK *cut, int windel );
static void CutIn_EoaLightAdd( CUTIN_WORK *cut,
		const VecFx32 *mtx, const VecFx32 *speed, int act_pri, int type, int windel );
static void CutIn_BirdInit( CUTIN_WORK *cut );

static void CutIn_BirdInit( CUTIN_WORK *cut );
static int CutIn_BirdMoveStateGet( CUTIN_WORK *cut );
static void CutIn_BirdDelete( CUTIN_WORK *cut );

static const EOA_H_NPP DATA_EoaH_Bird;
int (* const * const DATA_EoaBirdMoveTbl[])( BIRD_WORK * );

static void CutIn_BirdMoveChange_Non( CUTIN_WORK *cut );
int (* const DATA_EoaBirdMoveTbl_Non[])( BIRD_WORK * );

static void CutIn_BirdMoveChange_StartUp( CUTIN_WORK *cut );
int (* const DATA_EoaBirdMoveTbl_StartUp[])( BIRD_WORK * );

static void CutIn_BirdMoveChange_RideON( CUTIN_WORK *cut );
int (* const DATA_EoaBirdMoveTbl_RideON[])( BIRD_WORK * );

static EOA_PTR CutIn_EoaJikiMoveAdd( EOA_SYS_PTR eoa_sys, CLACT_WORK_PTR act );
static int CutIn_EoaJikiMoveEndCheck( EOA_PTR eoa );
static void CutIn_EoaJikiMoveChange_Non( EOA_PTR eoa );
static void CutIn_EoaJikiMoveChange_Jump( EOA_PTR eoa );
static void CutIn_EoaJikiMoveChange_Landing( EOA_PTR eoa );
static const EOA_H_NPP DATA_EoaH_JikiMove;

static EOA_PTR CutIn_EoaCutInCameraMoveAdd(
		EOA_SYS_PTR es, FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki );
static void EoaCutInCameraMoveChange_ZoomIn( EOA_PTR eoa );
static void EoaCutInCameraMoveChange_ZoomOut( EOA_PTR eoa );
static void EoaCutInCameraMoveChange_ZoomInLanding( EOA_PTR eoa );
static void EoaCutInCameraMoveChange_ZoomOutLanding( EOA_PTR eoa );

static void CutIn_PlayerVanishSet( CUTIN_WORK *cut, int flag );

static void Cip_HeroWinVanishSet( CUTIN_WORK *cutin );
static void Cip_HeroWinVanishDel( CUTIN_WORK *cutin );

static const NARC_ID DATA_NArcID_AlwaysChar[CUTIN_CAUSE_CHAR_ALWAYS_MAX];
static const NARC_ID DATA_NArcID_AlwaysPltt[CUTIN_CAUSE_PLTT_ALWAYS_MAX];
static const NARC_ID DATA_NArcID_AlwaysCell[CUTIN_CAUSE_CELL_ALWAYS_MAX];
static const NARC_ID DATA_NArcID_AlwaysAnime[CUTIN_CAUSE_ANM_ALWAYS_MAX];


//==============================================================================
//
//==============================================================================
//==============================================================================
//
//==============================================================================
//==============================================================================
//
//==============================================================================
//==============================================================================
//
//==============================================================================
//--------------------------------------------------------------
//	鳥動作タイプ
//--------------------------------------------------------------
enum
{
	NEW_BIRD_MOVETYPE_NON = 0,
	NEW_BIRD_MOVETYPE_LANDING_START,
};

//--------------------------------------------------------------
///	CIP_CLACT_RES_OBJ構造体
//--------------------------------------------------------------
typedef struct
{
	s16 id;
	s16 trans_flag;
	CLACT_U_RES_OBJ_PTR resobj;
}CIP_CLACT_RES_OBJ;

#define CIP_CLACT_RES_OBJ_SIZE (sizeof(CIP_CLACT_RES_OBJ))

//--------------------------------------------------------------
///	CIP_CLACT_SETDATA構造体
//--------------------------------------------------------------
typedef struct
{
	u8 resobj_char_max;
	u8 resobj_pltt_max;
	u8 resobj_cell_max;
	u8 resobj_anm_max;
	s8 resobj_char_nonid;
	s8 resobj_pltt_nonid;
	s8 resobj_cell_nonid;
	s8 resobj_anm_nonid;
	CLACT_SET_PTR clact_set;
	CLACT_U_EASYRENDER_DATA clact_easydata;
	CLACT_U_RES_MANAGER_PTR clact_resm_char;
	CLACT_U_RES_MANAGER_PTR clact_resm_pltt;
	CLACT_U_RES_MANAGER_PTR clact_resm_cell;
	CLACT_U_RES_MANAGER_PTR clact_resm_anm;
	CIP_CLACT_RES_OBJ *clact_resobj_char;
	CIP_CLACT_RES_OBJ *clact_resobj_pltt;
	CIP_CLACT_RES_OBJ *clact_resobj_cell;
	CIP_CLACT_RES_OBJ *clact_resobj_anm;
}CIP_CLACT_SETDATA;

//--------------------------------------------------------------
///	着陸使用キャラID
//--------------------------------------------------------------
enum
{
	SKYL_USE_CHAR_HERO = 0,
	SKYL_USE_CHAR_BIRD,
	SKYL_USE_CHAR_MAX,
};

//--------------------------------------------------------------
///	着陸使用パレットID
//--------------------------------------------------------------
enum
{
	SKYL_USE_PLTT_HEROINE = 0,
	SKYL_USE_PLTT_HERO_BIRD,
	SKYL_USE_PLTT_MAX,
};

//--------------------------------------------------------------
///	着陸使用セルID
//--------------------------------------------------------------
enum
{
	SKYL_USE_CELL_HERO = 0,
	SKYL_USE_CELL_BIRD,
	SKYL_USE_CELL_MAX,
};

//--------------------------------------------------------------
///	着陸使用アニメID
//--------------------------------------------------------------
enum
{
	SKYL_USE_ANM_HERO = 0,
	SKYL_USE_ANM_MAX,
};

//--------------------------------------------------------------
///	SKYL_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int end_flag;
	int frame;
	int sex;
	int draw_on;
	FIELDSYS_WORK *fsys;
	
	CIP_CLACT_SETDATA clactset;
	CLACT_WORK_PTR clact_hero;
	
	EOA_SYS_PTR eoa_sys;
	EOA_PTR eoa_bird;
	TCB_PTR tcb_vintr;
}SKYL_WORK;

#define SKYL_WORK_SIZE (sizeof(SKYL_WORK))

static void Cip_FadeInWhite( void );
static void Cip_FadeOutWhite( void );
static void * Cip_AllocMemory( u32 heap, int size );
static void Cip_PlayerVanishSet( FIELDSYS_WORK *fsys, int flag );

//==============================================================================
//	セルアクター
//==============================================================================
//--------------------------------------------------------------
/**
 * セルアクターセットデータ初期化
 * @param	clactset	CIP_CLACT_SETDATA
 * @param	actmax		アクター最大数
 * @param	charmax		キャラ登録最大数
 * @param	plttmax		パレット登録最大数
 * @param	cellmax		セル登録最大数
 * @param	anmmax		アニメ登録最大数
 * @param	charnonid	キャラ登録時に無しと判断するID
 * @param	plttnonid	パレット登録時に無しと判断するID
 * @param	cellnonid	セル登録時に無しと判断するID
 * @param	anmnonid	アニメ登録時に無しと判断するID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Cip_ClActSetDataInit(
		CIP_CLACT_SETDATA *set,
		int actmax,
		int charmax, int plttmax, int cellmax, int anmmax,
		int charnonid, int plttnonid, int cellnonid, int anmnonid )
{
	int i;
	
	//パラメタ初期化
	set->resobj_char_max = charmax;
	set->resobj_pltt_max = plttmax;
	set->resobj_cell_max = cellmax;
	set->resobj_anm_max = anmmax;
	set->resobj_char_nonid = charnonid;
	set->resobj_pltt_nonid = plttnonid;
	set->resobj_cell_nonid = cellnonid;
	set->resobj_anm_nonid = anmnonid;
	
	//セルアクター初期化
	set->clact_set = CLACT_U_SetEasyInit( actmax, &set->clact_easydata, HEAPID_FIELD );
	CLACT_U_SetSubSurfaceMatrix( &set->clact_easydata, 0, FX32_CONST(512) );

	//リソース初期化
	set->clact_resm_char = CLACT_U_ResManagerInit( charmax, CLACT_U_CHAR_RES, HEAPID_FIELD );
	set->clact_resm_pltt = CLACT_U_ResManagerInit( plttmax, CLACT_U_PLTT_RES, HEAPID_FIELD );
	set->clact_resm_cell = CLACT_U_ResManagerInit( cellmax, CLACT_U_CELL_RES, HEAPID_FIELD );
	set->clact_resm_anm = CLACT_U_ResManagerInit( anmmax, CLACT_U_CELLANM_RES, HEAPID_FIELD );
	
	//リソースOBJ初期化
	set->clact_resobj_char = Cip_AllocMemory( HEAPID_FIELD, CIP_CLACT_RES_OBJ_SIZE * charmax );
	set->clact_resobj_pltt = Cip_AllocMemory( HEAPID_FIELD, CIP_CLACT_RES_OBJ_SIZE * plttmax );
	set->clact_resobj_cell = Cip_AllocMemory( HEAPID_FIELD, CIP_CLACT_RES_OBJ_SIZE * cellmax );
	set->clact_resobj_anm = Cip_AllocMemory( HEAPID_FIELD, CIP_CLACT_RES_OBJ_SIZE * anmmax );
	
	for( i = 0; i < charmax; set->clact_resobj_char[i].id = charnonid, i++ ){};
	for( i = 0; i < plttmax; set->clact_resobj_pltt[i].id = plttnonid, i++ ){};
	for( i = 0; i < cellmax; set->clact_resobj_cell[i].id = cellnonid, i++ ){};
	for( i = 0; i < anmmax; set->clact_resobj_anm[i].id = anmnonid, i++ ){};
}

//--------------------------------------------------------------
/**
 * セルアクターセットデータ削除
 * @param	clactset	CIP_CLACT_SETDATA
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Cip_ClActSetDataDelete( CIP_CLACT_SETDATA *set )
{
	int i;
	
	//VRAMに展開されたキャラ、パレット削除
	for( i = 0; i < set->resobj_char_max; i++ ){
		if( set->clact_resobj_char[i].id != set->resobj_char_nonid ){
			CLACT_U_CharManagerDelete( set->clact_resobj_char[i].resobj );
		}
	}
	
	for( i = 0; i < set->resobj_pltt_max; i++ ){
		if( set->clact_resobj_pltt[i].id != set->resobj_pltt_nonid ){
			CLACT_U_PlttManagerDelete( set->clact_resobj_pltt[i].resobj );
		}
	}
	
	//セル、アニメ展開領域破棄
	for( i = 0; i < set->resobj_cell_max; i++ ){
		if( set->clact_resobj_cell[i].id != set->resobj_cell_nonid ){
			CLACT_U_ResManagerResOnlyDelete( set->clact_resobj_cell[i].resobj );
		}
	}
	
	for( i = 0; i < set->resobj_anm_max; i++ ){
		if( set->clact_resobj_anm[i].id != set->resobj_anm_nonid ){
			CLACT_U_ResManagerResOnlyDelete( set->clact_resobj_anm[i].resobj );
		}
	}
	
	CLACT_U_ResManagerDelete( set->clact_resm_char );
	CLACT_U_ResManagerDelete( set->clact_resm_pltt );
	CLACT_U_ResManagerDelete( set->clact_resm_cell );
	CLACT_U_ResManagerDelete( set->clact_resm_anm );
	
	sys_FreeMemoryEz( set->clact_resobj_char );
	sys_FreeMemoryEz( set->clact_resobj_pltt );
	sys_FreeMemoryEz( set->clact_resobj_cell );
	sys_FreeMemoryEz( set->clact_resobj_anm );
	
	//アクター全部削除
	CLACT_DelAllSet( set->clact_set );
	//セルアクター破棄
	CLACT_DestSet( set->clact_set );
}

//--------------------------------------------------------------
/**
 * キャラ登録
 * @param	set		CIP_CLACT_SETDATA
 * @param	hand	ARCHANDLE *
 * @param	arcid	アーカイブデータインデックス
 * @param	id 登録ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Cip_ClActCharAdd( CIP_CLACT_SETDATA *set, ARCHANDLE *hand, int arcid, int id )
{
	int i;
	
	for( i = 0; i < set->resobj_char_max; i++ ){
		if( set->clact_resobj_char[i].id == set->resobj_char_nonid ){
			set->clact_resobj_char[i].id = id;
			set->clact_resobj_char[i].trans_flag = FALSE;
			set->clact_resobj_char[i].resobj =
				CLACT_U_ResManagerResAddArcChar_ArcHandle(
					set->clact_resm_char, hand, arcid, FALSE, id,
					NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_FIELD );
			return;
		}
	}
	
	GF_ASSERT( 0 && "Cip_ClActCharAdd()登録できない" );
}

//--------------------------------------------------------------
/**
 * 指定されたキャラIDをVRAMエリアへセット
 * @param	set		CIP_CLACT_SETDATA
 * @param	id		登録ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Cip_ClActCharVramAreaSet( CIP_CLACT_SETDATA *set, int id )
{
	int i;
	
	for( i = 0; i < set->resobj_char_max; i++ ){
		if( set->clact_resobj_char[i].id == id ){
			CLACT_U_CharManagerSetAreaCont( set->clact_resobj_char[i].resobj );
			return;
		}
	}
	
	GF_ASSERT( 0 && "Cip_ClActCharAreaCont()ID異常" );
}

//--------------------------------------------------------------
/**
 * 指定されたキャラIDで展開した領域を破棄
 * @param	set		CIP_CLACT_SETDATA
 * @param	id		登録ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Cip_ClActCharResDelete( CIP_CLACT_SETDATA *set, int id )
{
	int i;
	
	for( i = 0; i < set->resobj_char_max; i++ ){
		if( set->clact_resobj_char[i].id == id ){
			CLACT_U_ResManagerResOnlyDelete( set->clact_resobj_char[i].resobj );
			return;
		}
	}
	
	GF_ASSERT( 0 && "Cip_ClActCharResDelete()ID異常" );
}

//--------------------------------------------------------------
/**
 * パレット登録
 * @param	set		CIP_CLACT_SETDATA
 * @param	hand	ARCHANDLE *
 * @param	arcid	アーカイブデータインデックス
 * @param	id	登録ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Cip_ClActPlttAdd( CIP_CLACT_SETDATA *set, ARCHANDLE *hand, int arcid, int id )
{
	int i;
	
	for( i = 0; i < set->resobj_char_max; i++ ){
		if( set->clact_resobj_pltt[i].id == set->resobj_pltt_nonid ){
			set->clact_resobj_pltt[i].id = id;
			set->clact_resobj_pltt[i].trans_flag = FALSE;
			set->clact_resobj_pltt[i].resobj =
				CLACT_U_ResManagerResAddArcPltt_ArcHandle(
					set->clact_resm_pltt, hand, arcid, FALSE, id,
					NNS_G2D_VRAM_TYPE_2DMAIN, 1, HEAPID_FIELD );
			return;
		}
	}
	
	GF_ASSERT( 0 && "Cip_ClActPlttAdd()登録できない" );
}

//--------------------------------------------------------------
/**
 * 指定されたパレットIDをVRAMエリアへセット
 * @param	set		CIP_CLACT_SETDATA
 * @param	id		登録ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Cip_ClActPlttVramAreaSet( CIP_CLACT_SETDATA *set, int id )
{
	int i;
	
	for( i = 0; i < set->resobj_pltt_max; i++ ){
		if( set->clact_resobj_pltt[i].id == id ){
			CLACT_U_PlttManagerSetCleanArea( set->clact_resobj_pltt[i].resobj );
			return;
		}
	}
	
	GF_ASSERT( 0 && "Cip_ClActPlttAreaCont()ID異常" );
}

//--------------------------------------------------------------
/**
 * 指定されたパレットIDで展開した領域を破棄
 * @param	set		CIP_CLACT_SETDATA
 * @param	id		登録ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Cip_ClActPlttResDelete( CIP_CLACT_SETDATA *set, int id )
{
	int i;
	
	for( i = 0; i < set->resobj_pltt_max; i++ ){
		if( set->clact_resobj_pltt[i].id == id ){
			CLACT_U_ResManagerResOnlyDelete( set->clact_resobj_pltt[i].resobj );
			return;
		}
	}
	
	GF_ASSERT( 0 && "Cip_ClActPlttResDelete()ID異常" );
}

//--------------------------------------------------------------
/**
 * セル登録
 * @param	set		CIP_CLACT_SETDATA
 * @param	hand	ARCHANDLE *
 * @param	arcid	アーカイブデータインデックス
 * @param	id	登録ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Cip_ClActCellAdd( CIP_CLACT_SETDATA *set, ARCHANDLE *hand, int arcid, int id )
{
	int i;
	
	for( i = 0; i < set->resobj_char_max; i++ ){
		if( set->clact_resobj_cell[i].id == set->resobj_cell_nonid ){
			set->clact_resobj_cell[i].id = id;
			set->clact_resobj_cell[i].trans_flag = FALSE;
			set->clact_resobj_cell[i].resobj =
				CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
					set->clact_resm_cell, hand, arcid, FALSE, id, 
					CLACT_U_CELL_RES, HEAPID_FIELD );
			return;
		}
	}
	
	GF_ASSERT( 0 && "Cip_ClActCellAdd()登録できない" );
}

//--------------------------------------------------------------
/**
 * アニメ登録
 * @param	set		CIP_CLACT_SETDATA
 * @param	hand	ARCHANDLE *
 * @param	arcid	アーカイブデータインデックス
 * @param	id	登録ID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Cip_ClActAnmAdd( CIP_CLACT_SETDATA *set, ARCHANDLE *hand, int arcid, int id )
{
	int i;
	
	for( i = 0; i < set->resobj_char_max; i++ ){
		if( set->clact_resobj_anm[i].id == set->resobj_anm_nonid ){
			set->clact_resobj_anm[i].id = id;
			set->clact_resobj_anm[i].trans_flag = FALSE;
			set->clact_resobj_anm[i].resobj =
				CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
					set->clact_resm_anm, hand, arcid, FALSE, id, 
					CLACT_U_CELLANM_RES, HEAPID_FIELD );
			return;
		}
	}
	
	GF_ASSERT( 0 && "Cip_ClActAnmAdd()登録できない" );
}

//--------------------------------------------------------------
/**
 * アクター追加
 * @param	set			CLACT_SETDATA
 * @param	mtx			表示座標
 * @param	char_id		キャラクタデータID
 * @param	pltt_id		パレットデータID
 * @param	cell_id		セルデータID
 * @param	cellanm_id	セルアニメーションID	無いときはCLACT_U_HEADER_DATA_NONE
 * @param	bg_pri		BGプライオリティ
 * @param	act_pri		アクタープライオリティ
 * @retval	CLACT_WORK_PTR	追加された
 */
//--------------------------------------------------------------
static CLACT_WORK_PTR Cip_ClActAdd( CIP_CLACT_SETDATA *set, const VecFx32 *vec,
		u32 char_id, u32 pltt_id, u32 cell_id, u32 cellanm_id, int bg_pri, int act_pri )
{
	CLACT_HEADER head;
	CLACT_ADD_SIMPLE add;
	CLACT_WORK_PTR act;
	
	if( cellanm_id == set->resobj_anm_nonid ){
		cellanm_id = CLACT_U_HEADER_DATA_NONE;
	}
	
	CLACT_U_MakeHeader(
		&head, char_id, pltt_id, cell_id, cellanm_id,
		CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
		FALSE,
		bg_pri,
		set->clact_resm_char,
		set->clact_resm_pltt,
		set->clact_resm_cell,
		set->clact_resm_anm,
		NULL, NULL );
	
	add.ClActSet = set->clact_set;
	add.ClActHeader = &head;
	add.mat = *vec;
	add.pri = act_pri;
	add.DrawArea = NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap = HEAPID_FIELD;
		
	act = CLACT_AddSimple( &add );
	GF_ASSERT( act != NULL && "CLACT_AddSimple() Error" );
	
	return( act );
}

//--------------------------------------------------------------
/**
 * セルアクターの座標を取得
 * @param	act		CLACT_WORK_PTR
 * @param	mtx		座標格納先
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Cip_ClActMatrixGet( CLACT_WORK_PTR act, VecFx32 *mtx )
{
	const VecFx32 *cmtx = CLACT_GetMatrix( act );
	*mtx = *cmtx;
}

//--------------------------------------------------------------
/**
 * セルアクターの拡縮率を取得
 * @param	act		CLACT_WORK_PTR
 * @param	mtx		座標格納先
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Cip_ClActScaleGet( CLACT_WORK_PTR act, VecFx32 *scale )
{
	const VecFx32 *cscale = CLACT_GetScale( act );
	*scale = *cscale;
}

//--------------------------------------------------------------
/**
 * アクター　鳥追加
 * @param	set		CIP_CLACT_SETDATA
 * @param	mtx		表示座標
 * @param	act_pri	アクター間プライオリティ
 * @retval	CLACT_WORK_PTR	CLACT_WORK_PTR
 */
//--------------------------------------------------------------
static CLACT_WORK_PTR Cip_ClActAdd_Bird( CIP_CLACT_SETDATA *set )
{
	CLACT_WORK_PTR act;
	VecFx32 mtx = { 0,0,0 };
	VecFx32 affoffs = { 0,0,0 };
	VecFx32 scale = { 0x1000,0x1000,0};
	
	act = Cip_ClActAdd( set, &mtx,
		CUTIN_CAID_CHAR_BIRD, CUTIN_CAID_PLTT_HERO_BIRD,
		CUTIN_CAID_CELL_BIRD, CUTIN_CAID_ANM_MAX, 0, ACTPRI_CUTIN_BIRD_LOW );
	
	CLACT_SetAffineParam( act, CLACT_AFFINE_DOUBLE );
	CLACT_SetAffineMatrix( act, &affoffs );
	CLACT_SetScale( act, &scale );
	CLACT_SetRotation( act, RotKeyR(0) );
	
	return( act );
}

//--------------------------------------------------------------
/**
 * アクター　自機追加
 * @param	set		CIP_CLACT_SETDATA
 * @param	sex		PM_MALE等
 * @retval	CLACT_WORK_PTR	CLACT_WORK_PTR
 */
//--------------------------------------------------------------
static CLACT_WORK_PTR Cip_ClActAdd_Hero( CIP_CLACT_SETDATA *set, int sex )
{
	VecFx32 mtx = { 0,0,0 };
	CLACT_WORK_PTR act;
	u32 pltt_id = CUTIN_CAID_PLTT_HERO_BIRD;
	
	if( sex == PM_FEMALE ){
		pltt_id = CUTIN_CAID_PLTT_HEROINE;
	}
	
	act = Cip_ClActAdd( set, &mtx,
		CUTIN_CAID_CHAR_HERO, pltt_id,
		CUTIN_CAID_CELL_HERO, CUTIN_CAID_ANM_HERO, 0, ACTPRI_CUTIN_HERO );
	
	CLACT_SetDrawFlag( act, 0 );
	CLACT_AnmChg( act, JIKIANMNO_HIDEN );
	return( act );
}

//==============================================================================
//	鳥
//==============================================================================
//--------------------------------------------------------------
///	NEW_BIRD_ADD_H構造体
//--------------------------------------------------------------
typedef struct
{
	EOA_SYS_PTR es;
	FIELDSYS_WORK *fsys;
	CLACT_WORK_PTR clact_jiki;
	CIP_CLACT_SETDATA *clactset;
}NEW_BIRD_ADD_H;

//--------------------------------------------------------------
///	NEW_BIRD_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	u8 move_type;
	u8 seq_no;
	u8 move_state;
	u8 jiki_seq_no;
	int frame;
	
	VecFx32 mtx;
	VecFx32 offs;
	VecFx32 val;
	VecFx32 scale;
	fx32 rot;
	fx32 rot_val;
	fx32 angle;
	fx32 angle_val;
	fx32 angle_scale;
	fx32 angle_scale_val;
	fx32 scale_val;
	fx32 joint_val;
	NEW_BIRD_ADD_H head;
	CLACT_WORK_PTR clact;
	EOA_PTR eoa_jikimove;
	TCB_PTR tcb_camera;
}NEW_BIRD_WORK;

#define NEW_BIRD_WORK_SIZE (sizeof(NEW_BIRD_WORK))

static const EOA_H_NPP NEW_DATA_EoaH_Bird;
int (* const * const NEW_DATA_EoaBirdMoveTbl[])( NEW_BIRD_WORK * );

//--------------------------------------------------------------
/**
 * EOA 鳥追加
 * @param
 * @retval
 */
//--------------------------------------------------------------
static EOA_PTR Bird_Init( FIELDSYS_WORK *fsys,
		EOA_SYS_PTR es, CIP_CLACT_SETDATA *clactset, CLACT_WORK_PTR jiki )
{
	EOA_PTR eoa;
	VecFx32 mtx = {0,0,0};
	NEW_BIRD_ADD_H head;
	
	head.fsys = fsys;
	head.es = es;
	head.clactset = clactset;
	head.clact_jiki = jiki;
	
	OS_Printf( "fsys = %x ", fsys );
	OS_Printf( "es = %x ", es );
	OS_Printf( "clactset = %x ", clactset );
	OS_Printf( "jiki = %x \n", jiki);
	
	eoa = EOA_Add_NPP(
		es, &NEW_DATA_EoaH_Bird, &mtx, 0, &head, TCBPRI_CUTIN_EOA_BIRD );
	
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA 鳥動作状態チェック
 * @param	eoa		EOA_PTR
 * @retval	int		BIRD_MOVESTATE_NON等
 */
//--------------------------------------------------------------
static int Bird_MoveStateGet( EOA_PTR eoa )
{
	NEW_BIRD_WORK *work = EOA_LocalWorkGet( eoa );
	return( work->move_state );
}

//--------------------------------------------------------------
/**
 * EOA 鳥　初期化
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int NEW_EoaBird_Init( EOA_PTR eoa, void *wk )
{
	NEW_BIRD_WORK *work = wk;
	const NEW_BIRD_ADD_H *head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	work->clact = Cip_ClActAdd_Bird( work->head.clactset );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 鳥削除
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void Bird_Delete( EOA_PTR eoa )
{
	NEW_BIRD_WORK *work = EOA_LocalWorkGet( eoa );
	if( work->eoa_jikimove ){ EOA_Delete( work->eoa_jikimove ); }
	if( work->tcb_camera ){ FieldZoom_Delete( work->tcb_camera ); }
	EOA_Delete( eoa );
}

//--------------------------------------------------------------
/**
 * EOA 鳥　削除
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void NEW_EoaBird_Delete( EOA_PTR eoa, void *wk )
{
	NEW_BIRD_WORK *work = wk;
	CLACT_Delete( work->clact );
}

//--------------------------------------------------------------
/**
 * EOA 鳥　動作
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void NEW_EoaBird_Move( EOA_PTR eoa, void *wk )
{
	NEW_BIRD_WORK *work = wk;
	int (* const *move)(NEW_BIRD_WORK*);
	
	move = NEW_DATA_EoaBirdMoveTbl[work->move_type];
	while( move[work->seq_no](work) == TRUE ){};
}

//--------------------------------------------------------------
///	EOA_H　鳥
//--------------------------------------------------------------
static const EOA_H_NPP NEW_DATA_EoaH_Bird =
{
	NEW_BIRD_WORK_SIZE,
	NEW_EoaBird_Init,
	NEW_EoaBird_Delete,
	NEW_EoaBird_Move,
	EOA_DrawProcDummy,
};

//==============================================================================
//	鳥動作
//==============================================================================
//--------------------------------------------------------------
/**
 * 鳥動作　何も無しへ変更
 * @param	eoa		EOA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Bird_MoveChange_Non( EOA_PTR eoa )
{
	NEW_BIRD_WORK *work = EOA_LocalWorkGet( eoa );
	work->move_type = NEW_BIRD_MOVETYPE_NON;
	work->seq_no = 0;
	work->move_state = BIRD_MOVESTATE_NON;
}

//--------------------------------------------------------------
/**
 * 鳥動作　無し
 * @param	work	BIRD_WORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int NEW_BirdMove_Non( NEW_BIRD_WORK *work )
{
	work->move_state = BIRD_MOVESTATE_NON;
	CLACT_SetDrawFlag( work->clact, 0 );
	return( FALSE );
}

//--------------------------------------------------------------
//	鳥動作　動作無し BIRD_MOVETYPE_NON
//--------------------------------------------------------------
static int (* const NEW_DATA_EoaBirdMoveTbl_Non[])( NEW_BIRD_WORK * ) =
{
	NEW_BirdMove_Non,
};

//==============================================================================
///	鳥動作　着地開始
//==============================================================================
//--------------------------------------------------------------
/**
 * 鳥動作　着地開始へ変更
 * @param	eoa		EOA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Bird_MoveChange_LandingStart( EOA_PTR eoa )
{
	VecFx32 mtx = {NUMFX32(128),NUMFX32(111),0};
	VecFx32 scale = { 0x2000,0x2000,0};
	
	NEW_BIRD_WORK *work = EOA_LocalWorkGet( eoa );
	work->move_type = NEW_BIRD_MOVETYPE_LANDING_START;
	work->move_state = BIRD_MOVESTATE_NON;
	
	work->seq_no = 0;
	work->frame = 0;
	
	work->mtx = mtx;
	work->offs.x = 0; work->offs.y = 0; work->offs.z = 0;
	work->rot = NUMFX32( 350 );
	work->scale = scale;
	work->scale_val = 0x0400;
	work->angle = NUMFX32( 45 );
	work->angle_scale = NUMFX32( 128+64 );
	work->angle_scale_val = NUMFX32( 32 );
	
	work->offs.x = Cos360R( 45 ) * FX32NUM( work->angle_scale );
	work->offs.y = Sin360R( FX32NUM(work->angle) ) * FX32NUM( work->angle_scale );
	mtx.x = work->mtx.x + work->offs.x;
	mtx.y = work->mtx.y + work->offs.y;
	
	CLACT_SetMatrix( work->clact, &mtx );
	CLACT_SetScale( work->clact, &scale );
	CLACT_SetRotation( work->clact, RotKeyR(FX32NUM(work->rot)) );
	CLACT_DrawPriorityChg( work->clact, ACTPRI_CUTIN_BIRD_LOW );
	
	CLACT_SetDrawFlag( work->clact, 1 );
	work->eoa_jikimove = CutIn_EoaJikiMoveAdd( work->head.es, work->head.clact_jiki );
	
	work->tcb_camera = FieldZoom_Init( work->head.fsys, HEAPID_FIELD );
	FieldZoom_TypeChange( work->tcb_camera, ZOOMTYPE_ZOOM, -CUTIN_ZOOM, 12 );
	
	{
		CLACT_WORK_PTR act_hero;
		VecFx32 affoffs = { 0,0,0 };
		VecFx32 scale = { 0x2000,0x2000,0};
	
		act_hero = work->head.clact_jiki;
		CLACT_SetAffineParam( act_hero, CLACT_AFFINE_DOUBLE );
	
		CLACT_SetAffineMatrix( act_hero, &affoffs );
		CLACT_SetScale( act_hero, &scale );
		CLACT_SetRotation( act_hero, RotKeyR(0) );
		CLACT_AnmChg( act_hero, JIKIANMNO_STAY_U );
	}
	
	Cip_FadeInWhite();
///	Cip_PlayerVanishSet( work->head.fsys, TRUE );<<20060704 del
}

//--------------------------------------------------------------
/**
 * 鳥動作　着地開始　初期移動
 * @param	work	BIRD_WORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int NEW_BirdMove_LandingStartInit( NEW_BIRD_WORK *work )
{
	VecFx32 mtx;
	CLACT_WORK_PTR actbird = work->clact, acthero = work->head.clact_jiki;
	
	work->angle_scale -= work->angle_scale_val;
	
	if( work->angle_scale < 0 ){
		work->angle_scale = 0;
	}
	
	if( work->angle_scale_val > 0x0800 ){
		work->angle_scale_val -= 0x1c00;
	}
	
	if( work->angle_scale_val < 0x1000 ){
		work->angle_scale_val = 0x1000;
	}
	
	work->offs.x = Cos360R( 45 ) * FX32NUM( work->angle_scale );
	work->offs.y = Sin360R( FX32NUM(work->angle) ) * FX32NUM( work->angle_scale );
	
	if( FX32NUM(work->angle) < 90 ){
		work->angle += 0x4000;
	}
	
	work->scale.x -= work->scale_val;
	if( work->scale.x < 0x1000 ){ work->scale.x = 0x1000; }
	work->scale.y -= work->scale_val;
	if( work->scale.y < 0x1000){ work->scale.y = 0x1000; }
	
	CLACT_SetScale( actbird, &work->scale );
	CLACT_SetScale( acthero, &work->scale );
	
	mtx.x = work->mtx.x + work->offs.x;
	mtx.y = work->mtx.y + work->offs.y;
	CLACT_SetMatrix( actbird, &mtx );
	
	mtx.y -= NUMFX32( 18 );
	CLACT_SetMatrix( acthero, &mtx );
	
	if( work->angle_scale == 0 ){
		work->frame = 0;
		work->seq_no++;
	}else{
		work->frame++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 鳥動作　着地　ターン初期化
 * @param	work	BIRD_WORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int NEW_BirdMove_LandingTurnInit( NEW_BIRD_WORK *work )
{
	CutIn_EoaJikiMoveChange_Landing( work->eoa_jikimove );
	FieldZoom_TypeChange( work->tcb_camera, ZOOMTYPE_BACK, 0, 12 );
	
	work->scale_val = 0x0400;
	work->angle = NUMFX32( 128 );
	work->angle_scale = 0;
	work->angle_scale_val = 0x1800;
	work->seq_no++;
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * 鳥動作　着地　ターン
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int NEW_BirdMove_LandingTurn( NEW_BIRD_WORK *work )
{
	VecFx32 mtx;
	CLACT_WORK_PTR act = work->clact;
	
	work->angle_scale += work->angle_scale_val;
	work->angle_scale_val += 0x1000;
	
	if( work->angle_scale_val > NUMFX32(16) ){
		work->angle_scale_val = NUMFX32( 16 );
	}
	
	work->offs.x = Cos360R( FX32NUM(work->angle) ) * FX32NUM( work->angle_scale );
	work->offs.y = Sin360R( 128 ) * FX32NUM( work->angle_scale );
	
	if( work->angle < NUMFX32(160) ){
		work->angle += 0x1000;
	}
	
	work->rot += 0x2000;
	CLACT_SetRotation( act, RotKeyR(FX32NUM(work->rot)) );
	
	work->scale.x += work->scale_val;
	if( work->scale.x > 0x1000 ){ work->scale.x = 0x1000; }
	work->scale.y += work->scale_val;
	if( work->scale.y > 0x1000 ){ work->scale.y = 0x1000; }
	
	CLACT_SetScale( act, &work->scale );
	
	mtx.x = work->mtx.x + work->offs.x;
	mtx.y = work->mtx.y - work->offs.y;
	CLACT_SetMatrix( act, &mtx );
	
	
	if( FX32NUM(mtx.y) <= (-16) ){
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 鳥動作　着地　ターン完了
 * @param	work	BIRD_WORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int NEW_BirdMove_LandingTurnEnd( NEW_BIRD_WORK *work )
{
	CLACT_SetDrawFlag( work->clact, 0 );
	CLACT_AnmChg( work->head.clact_jiki, JIKIANMNO_STOP_D );
	
	work->frame = 0;
	work->seq_no++;
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * 鳥動作　着地　ターン完了後の一寸待ち
 * @param	work	BIRD_WORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int NEW_BirdMove_LandingTurnEndWait( NEW_BIRD_WORK *work )
{
	work->frame++;
	
	if( work->frame < 20 ){
		return( FALSE );
	}
	
	{
		VecFx32 mtx = {NUMFX32(128+8),NUMFX32(111-32),0};
		VecFx32 scale = { 0x1000,0x1000,0};
		
		work->frame = 0;
		
		work->mtx = mtx;
		work->offs.x = 0; work->offs.y = 0; work->offs.z = 0;
		work->rot = NUMFX32( 0 );
		work->scale = scale;
		work->scale_val = 0x200;
		work->angle = NUMFX32( 315 );
		work->angle_scale = NUMFX32( 128 );
		work->angle_scale_val = 0x2000;
	
		CLACT_SetMatrix( work->clact, &mtx );
		CLACT_SetScale( work->clact, &scale );
		CLACT_SetRotation( work->clact, RotKeyR(FX32NUM(work->rot)) );
		CLACT_SetDrawFlag( work->clact, 1 );
		
		CLACT_AnmChg( work->head.clact_jiki, JIKIANMNO_HIDEN );
		CLACT_SetAnmFlag( work->head.clact_jiki, 1 );
	}
	
	work->seq_no++;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * 鳥動作　ボール格納
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int NEW_BirdMove_LandingBallIn( NEW_BIRD_WORK *work )
{
	VecFx32 mtx;
	CLACT_WORK_PTR act = work->clact;
	
	work->angle_scale -= work->angle_scale_val;
	
	if( work->angle_scale_val < NUMFX32(16) ){
		work->angle_scale_val += 0x2000;
	}
	
	if( work->angle_scale < 0 ){
		work->angle_scale = 0;
	}
	
	work->offs.x = Cos360R( 315 ) * FX32NUM( work->angle_scale );
	work->offs.y = Sin360R( FX32NUM(work->angle) ) * FX32NUM( work->angle_scale );
	
	if( FX32NUM(work->angle) < 180 ){
		work->angle -= 0x4000;
	}
	
	work->scale.x -= work->scale_val;
	if( work->scale.x < 0x0400 ){ work->scale.x = 0x0400; }
	work->scale.y -= work->scale_val;
	if( work->scale.y < 0x0400 ){ work->scale.y = 0x0400; }
	
	CLACT_SetScale( act, &work->scale );
	
	work->rot += 0x6000;
	
	if( FX32NUM(work->rot) > 60 ){
		work->rot = NUMFX32( 60 );
	}
	
	CLACT_SetRotation( act, RotKeyR(FX32NUM(work->rot)) );
	
	mtx.x = work->mtx.x + work->offs.x;
	mtx.y = work->mtx.y + work->offs.y;
	CLACT_SetMatrix( act, &mtx );
	
	if( work->angle_scale <= 0 ){
		CLACT_SetDrawFlag( act, FALSE );
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 鳥動作　着地開始　テスト終了
 * @param	work	BIRD_WORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int NEW_BirdMove_LandingBallInEndWait( NEW_BIRD_WORK *work )
{
	work->frame++;
	
	if( work->frame == 8 ){
		CLACT_AnmChg( work->head.clact_jiki, JIKIANMNO_STOP_D );
		Cip_PlayerVanishSet( work->head.fsys, FALSE );
	}
	
	if( work->frame == 10 ){
		CLACT_SetDrawFlag( work->head.clact_jiki, FALSE );
	}
	
	if( work->frame > 15 && FieldZoom_EndCheck(work->tcb_camera) == TRUE ){
		work->frame = 0;
		work->seq_no++;
		work->move_state = BIRD_MOVESTATE_END;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 鳥動作　着地開始　終了
 * @param	work	BIRD_WORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int NEW_BirdMove_LandingEnd( NEW_BIRD_WORK *work )
{
	return( FALSE );
}

//--------------------------------------------------------------
//	鳥動作　着地開始 BIRD_MOVETYPE_LANDING_START
//--------------------------------------------------------------
static int (* const NEW_DATA_EoaBirdMoveTbl_LandingStart[])( NEW_BIRD_WORK * ) =
{
	NEW_BirdMove_LandingStartInit,
	NEW_BirdMove_LandingTurnInit,
	NEW_BirdMove_LandingTurn,
	NEW_BirdMove_LandingTurnEnd,
	NEW_BirdMove_LandingTurnEndWait,
	NEW_BirdMove_LandingBallIn,
	NEW_BirdMove_LandingBallInEndWait,
	NEW_BirdMove_LandingEnd,
};

//--------------------------------------------------------------
///	鳥　動作テーブル
//--------------------------------------------------------------
static int (* const * const NEW_DATA_EoaBirdMoveTbl[])( NEW_BIRD_WORK * ) =
{
	NEW_DATA_EoaBirdMoveTbl_Non,
	NEW_DATA_EoaBirdMoveTbl_LandingStart,
};

//==============================================================================
//	パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * カットイン用アーカイブハンドルオープン
 * @param
 * @retval
 */
//--------------------------------------------------------------
static ARCHANDLE * Cip_ArcHandleOpen( void )
{
	return( ArchiveDataHandleOpen(ARC_FIELD_CUTIN_GRA,HEAPID_FIELD) );
}

//--------------------------------------------------------------
/**
 * フェードイン　ホワイト
 * @param	nothing
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Cip_FadeInWhite( void )
{
	WIPE_SYS_Start(
		WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
		WIPE_TYPE_FADEIN, WIPE_FADE_WHITE, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD );
}

//--------------------------------------------------------------
/**
 * フェードアウト　ホワイト
 * @param	nothing
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Cip_FadeOutWhite( void )
{
	WIPE_SYS_Start(
		WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
		WIPE_TYPE_FADEOUT, WIPE_FADE_WHITE, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD );
}

//--------------------------------------------------------------
/**
 * フェード終了チェック
 * @param	nothing
 * @retval	nothing
 */
//--------------------------------------------------------------
static int Cip_FadeEndCheck( void )
{
	if( WIPE_SYS_EndCheck() ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ 自機表示、非表示
 * @param	fsys	FIELDSYS_WORK
 * @param	flag	TRUE=非表示　FALSE=表示
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Cip_PlayerVanishSet( FIELDSYS_WORK *fsys, int flag )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( fsys->player );
	FieldOBJ_StatusBitSet_Vanish( fldobj, flag );
}

//==============================================================================
//	カットイン
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールド　カットイン 
 * @param	
 * @retval	TCB_PTR		カットイン動作TCB_PTR
 */
//--------------------------------------------------------------
TCB_PTR FieldCutIn_Init(
	FIELDSYS_WORK *fsys, u32 cutin_type, POKEMON_PARAM *param, int hero_sex )
{
	TCB_PTR tcb;
	CUTIN_WORK *cut = CutIn_AllocMemory( fsys );
	
	cut->poke_param = param;
	cut->sex = hero_sex;
	cut->cutin_type = cutin_type;
	
	if( cutin_type == CUTIN_TYPE_HIDEN ){	//秘伝技
		tcb = TCB_Add( CutIn_UpdateTCB, cut, TCBPRI_CUTIN_UPDATE );
	}else{									//空
		tcb = TCB_Add( CutInSky_UpdateTCB, cut, TCBPRI_CUTIN_UPDATE );
	}
	
	return( tcb );
}

//--------------------------------------------------------------
/**
 * カットイン終了チェック
 * @param
 * @retval
 */
//--------------------------------------------------------------
int FieldCutIn_EndCheck( TCB_PTR tcb )
{
	CUTIN_WORK *cut = TCB_GetWork( tcb );
	return( cut->end_flag );
}

//--------------------------------------------------------------
/**
 * カットイン終了
 * @param
 * @retval
 */
//--------------------------------------------------------------
void FieldCutIn_End( TCB_PTR tcb )
{
	CUTIN_WORK *cut = TCB_GetWork( tcb );
	CutIn_FreeMemory( cut );
	TCB_Delete( tcb );
}

//--------------------------------------------------------------
/**
 * カットインワーク確保
 * @param	
 * @retval
 */
//--------------------------------------------------------------
static CUTIN_WORK * CutIn_AllocMemory( FIELDSYS_WORK *fsys )
{
	CUTIN_WORK *cut = sys_AllocMemoryLo( HEAPID_FIELD, CUTIN_WORK_SIZE );
	memset( cut, 0, CUTIN_WORK_SIZE );
	cut->fsys = fsys;
	return( cut );
}

//--------------------------------------------------------------
/**
 * カットインワーク開放
 * @param	
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_FreeMemory( CUTIN_WORK *cut )
{
	sys_FreeMemoryEz( cut );
}

//==============================================================================
//	カットイン　マップイベント
//==============================================================================
//--------------------------------------------------------------
//	カットインフィールドイベント
//--------------------------------------------------------------
//void FieldEvent_Sorawotobu( 

//==============================================================================
//	カットイン　動作
//==============================================================================
//--------------------------------------------------------------
/**
 * カットイン動作
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_UpdateTCB( TCB_PTR tcb, void *work )
{
	int ret;
	CUTIN_WORK *cut = work;
	
	do{
		ret = DATA_CutInUpdateTbl[cut->seq_no]( cut );
	}while( ret == CUTIN_RET_REPEAT );
	
	if( cut->draw_on == TRUE ){
		if( cut->cutin_eoa_sys != NULL ){
			EOA_SysDraw( cut->cutin_eoa_sys );
		}
		
		CutIn_ClactDraw( cut );
	}
}

//--------------------------------------------------------------
/**
 * カットイン 0　グラフィック初期化
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_GraphicInit( CUTIN_WORK *cut )
{
	CutIn_GraphicInit( cut );
	CutIn_VIntrInitTcbAdd( cut );
	cut->seq_no++;
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン 0　グラフィック初期化完了待ち
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_GraphicInitWait( CUTIN_WORK *cut )
{
	if( cut->tcb_vintr_end == FALSE ){
		return( CUTIN_RET_RETURN );
	}
	
	{
		VecFx32 mtx0 = { NUMFX32(128), NUMFX32(96), 0 };
		VecFx32 mtx1 = { NUMFX32(256+40), NUMFX32(96), 0 };
		cut->clact_hero = CutIn_ClactAdd_Hero( cut, &mtx0 );
		cut->clact_poke = CutIn_ClactAdd_Poke( cut, &mtx1 );
		CutIn_LightSet( cut, TRUE );
	}
	
	CutIn_VIntrTcbDelete( cut );
	
	cut->draw_on = TRUE;
	cut->seq_no++;
	return( CUTIN_RET_REPEAT );
}

//--------------------------------------------------------------
/**
 * カットイン 0　ウィンドウ初期化
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_WndInit( CUTIN_WORK *cut )
{
	Cip_HeroWinVanishSet( cut );
	
	cut->win_setflag = FALSE;
	cut->win_val = NUMFX32( -64 );
	cut->win_x0 = NUMFX32( 254 );
	cut->win_x1 = NUMFX32( 255 );
	cut->win_y0 = NUMFX32( CUTIN_CY - 1 );
	cut->win_y1 = NUMFX32( CUTIN_CY + 1 );
	cut->win_setflag = TRUE;
	
	cut->seq_no++;
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン 1　ウィンドウ移動　横線
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_WndMove0( CUTIN_WORK *cut )
{
	cut->win_setflag = FALSE;
	cut->win_x0 += cut->win_val;
	
	if( cut->win_x0 <= 0 ){
		cut->win_x0 = 0;
		cut->win_val = 0x2000;
		cut->seq_no++;
	}
	
	CutIn_WndPosSet( cut, cut->win_x0, cut->win_y0, cut->win_x1, cut->win_y1 );
	cut->win_setflag = TRUE;
	
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン 1　ウィンドウ移動　縦に開く
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_WndMove1( CUTIN_WORK *cut )
{
	cut->win_setflag = FALSE;
	cut->win_y0 -= cut->win_val;
	cut->win_y1 += cut->win_val;
	
	cut->win_val += 0x2000;
	
	if( cut->win_val > NUMFX32(32) ){
		cut->win_val = NUMFX32(32);
	}
	
	if( cut->win_y0 < NUMFX32(CUTIN_SY) ){
		cut->win_y0 = NUMFX32( CUTIN_SY );
	}
	
	if( cut->win_y1 > NUMFX32(CUTIN_EY) ){
		cut->win_y1 = NUMFX32( CUTIN_EY );
	}
	
	CutIn_WndPosSet( cut, cut->win_x0, cut->win_y0, cut->win_x1, cut->win_y1 );
	cut->win_setflag = TRUE;
	
	if( cut->win_y0 == NUMFX32(CUTIN_SY) && cut->win_y1 == NUMFX32(CUTIN_EY) ){
		CutIn_ClactAutoAnimeStart( cut->clact_hero );	//自機アニメ開始
		cut->seq_no++;
	}
	
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン 1　自機手をかざすアニメ
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_HeroAnime( CUTIN_WORK *cut )
{
	cut->wait++;
		
	if( cut->wait >= 15 ){
		cut->wait = 0;
		cut->val = NUMFX32( -64 );
		cut->seq_no++;
	}
	
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン 1　ポケモン登場 0
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_PokeMove0( CUTIN_WORK *cut )
{
	const VecFx32 *cla_mtx;
	VecFx32 mtx;
	
	cla_mtx = CLACT_GetMatrix( cut->clact_poke );
	mtx = *cla_mtx;
	mtx.x += cut->val;
	
	if( mtx.x <= NUMFX32(128+32) ){
		mtx.x = NUMFX32( 128+64 );
		cut->seq_no++;
	}
	
	CLACT_SetMatrix( cut->clact_poke, &mtx );
	
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン 1　ポケモン登場 1　減速
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_PokeMove1( CUTIN_WORK *cut )
{
	const VecFx32 *cla_mtx;
	VecFx32 mtx;
	
	cut->val /= 2;
	
	if( cut->val > NUMFX32(-2) ){
		cut->val = NUMFX32( -2 );
		cut->seq_no++;
		
		{
			Snd_PMVoicePlay( PokeParaGet(cut->poke_param,ID_PARA_monsno,NULL) );
		}
	}
	
	cla_mtx = CLACT_GetMatrix( cut->clact_poke );
	mtx = *cla_mtx;
	mtx.x += cut->val;
	CLACT_SetMatrix( cut->clact_poke, &mtx );
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン 1　ポケモン登場 1　中心で一寸待ち
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_PokeMove2( CUTIN_WORK *cut )
{
	cut->wait++;
	
	if( cut->wait >= 8 ){
		cut->wait = 0;
		cut->val = NUMFX32( -1 );
		cut->seq_no++;
	}
	
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン 1　ポケモン登場 1　画面外へ
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_PokeMove3( CUTIN_WORK *cut )
{
	const VecFx32 *cla_mtx;
	VecFx32 mtx;
	
	cut->val *= 2;
	
	if( cut->val < NUMFX32(-64) ){
		cut->val = NUMFX32( -64 );
	}
	
	cla_mtx = CLACT_GetMatrix( cut->clact_poke );
	mtx = *cla_mtx;
	mtx.x += cut->val;
	CLACT_SetMatrix( cut->clact_poke, &mtx );
	
	if( mtx.x <= NUMFX32(-40) ){
		cut->win_val = 0x1000;
		cut->seq_no++;
	}
	
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン 1　ウィンドウ閉じる
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_WndClose( CUTIN_WORK *cut )
{
	cut->win_setflag = FALSE;
	cut->win_y0 += cut->win_val;
	cut->win_y1 -= cut->win_val;
	
	cut->win_val += 0x4000;
	
	if( cut->win_val > NUMFX32(32) ){
		cut->win_val = NUMFX32( 32 );
	}
	
	if( cut->win_y0 >= NUMFX32(CUTIN_CY-8) ){
		cut->win_y0 = NUMFX32( CUTIN_CY-8 );
	}
	
	if( cut->win_y1 <= NUMFX32(CUTIN_CY+8) ){
		cut->win_y1 = NUMFX32( CUTIN_CY+8 );
	}
	
	CutIn_WndPosSet( cut, cut->win_x0, cut->win_y0, cut->win_x1, cut->win_y1 );
	cut->win_setflag = TRUE;
	
	if( cut->win_y0 == NUMFX32(CUTIN_CY-8) && cut->win_y1 == NUMFX32(CUTIN_CY+8) ){
		Cip_HeroWinVanishDel( cut );
		cut->seq_no++;
	}
	
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン 1　グラフィック削除
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_GraphicDelete( CUTIN_WORK *cut )
{
	CutIn_GraphicDelete( cut );
	cut->draw_on = FALSE;
	cut->seq_no++;
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン 1　ウィンドウ消去
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_WndClear( CUTIN_WORK *cut )
{
	Cip_VIntrTcbWindowDelete( cut );
	cut->seq_no++;
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン 1　終了
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_End( CUTIN_WORK *cut )
{
	cut->end_flag = TRUE;
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
///	カットイン動作テーブル
//--------------------------------------------------------------
static int (* const DATA_CutInUpdateTbl[])( CUTIN_WORK *cut ) =
{
	CutInMove_GraphicInit,
	CutInMove_GraphicInitWait,
	CutInMove_WndInit,
	CutInMove_WndMove0,
	CutInMove_WndMove1,
	CutInMove_HeroAnime,
	CutInMove_PokeMove0,
	CutInMove_PokeMove1,
	CutInMove_PokeMove2,
	CutInMove_PokeMove3,
	CutInMove_WndClose,
	CutInMove_GraphicDelete,
	CutInMove_WndClear,
	CutInMove_End,
};

//==============================================================================
//	カットイン動作　空を飛ぶ
//==============================================================================
//--------------------------------------------------------------
/**
 * カットイン動作　空を飛ぶ
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutInSky_UpdateTCB( TCB_PTR tcb, void *work )
{
	int ret;
	CUTIN_WORK *cut = work;
	
	do{
		ret = DATA_CutInSkyUpdateTbl[cut->seq_no]( cut );
	}while( ret == CUTIN_RET_REPEAT );
	
	if( cut->draw_on == TRUE ){
		if( cut->cutin_eoa_sys != NULL ){
			EOA_SysDraw( cut->cutin_eoa_sys );
		}
		
		CutIn_ClactDraw( cut );
	}
}

//--------------------------------------------------------------
/**
 * カットイン グラフィック初期化完了待ち
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_SkyGraphicInitWait( CUTIN_WORK *cut )
{
	if( cut->tcb_vintr_end == FALSE ){
		return( CUTIN_RET_RETURN );
	}
	
	{
		VecFx32 mtx0 = { NUMFX32(128), NUMFX32(96), 0 };
		VecFx32 mtx1 = { NUMFX32(256+40), NUMFX32(96), 0 };
		cut->clact_hero = CutIn_ClactAdd_Hero( cut, &mtx0 );
		cut->clact_poke = CutIn_ClactAdd_Poke( cut, &mtx1 );
		CutIn_LightSet( cut, TRUE );
	}
	
	CutIn_VIntrTcbDelete( cut );
	
	cut->draw_on = TRUE;
	cut->seq_no++;
	return( CUTIN_RET_REPEAT );
}

//--------------------------------------------------------------
/**
 * カットイン　ポケモン絵削除
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int CutInMove_PokeGraphicDelete( CUTIN_WORK *cut )
{
	CutIn_PokeGraResmDelete( cut );
	cut->seq_no++;
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン　鳥グラフィック初期化
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int CutInMove_BirdGraphicInit( CUTIN_WORK *cut )
{
	CutIn_ClActBirdGraphicInit( cut );
	CutIn_VIntrBirdInitTcbAdd( cut );
	cut->seq_no++;
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン　鳥グラフィック初期化待ち
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int CutInMove_BirdGraphicInitWait( CUTIN_WORK *cut )
{
	if( cut->tcb_vintr_end == FALSE ){
		return( CUTIN_RET_RETURN );
	}
	
	CutIn_VIntrTcbDelete( cut );
	
	cut->seq_no++;
	return( CUTIN_RET_REPEAT );
}

//--------------------------------------------------------------
/**
 * カットイン 1　鳥スタート
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_BirdStartUp( CUTIN_WORK *cut )
{
	CutIn_BirdInit( cut );
	CutIn_BirdMoveChange_StartUp( cut );
	CutIn_WndPlaneOutsideOBJ_ON( cut );								//外側のOBJ表示ON
	CutIn_PlayerVanishSet( cut, TRUE );
	
	cut->seq_no++;
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン 1　鳥スタート　終了待ち
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_BirdStartUpWait( CUTIN_WORK *cut )
{
	if( CutIn_BirdMoveStateGet(cut) != BIRD_MOVESTATE_END ){
		return( CUTIN_RET_RETURN );
	}
	
	CLACT_AnmChg( cut->clact_hero, JIKIANMNO_STOP_D );
	cut->seq_no++;
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン 1　鳥スタート終了後の一寸待ちのち搭乗
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_BirdStartUpAfterWait( CUTIN_WORK *cut )
{
	cut->wait++;
	
	if( cut->wait >= 20 ){
		cut->wait = 0;
		cut->seq_no++;
		CutIn_BirdMoveChange_RideON( cut );
	}
	
	return( CUTIN_RET_REPEAT );
}

//--------------------------------------------------------------
/**
 * カットイン 1　鳥搭乗　搭乗待ち
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_BirdRideONWait( CUTIN_WORK *cut )
{
	if( CutIn_BirdMoveStateGet(cut) != BIRD_MOVESTATE_RIDE_ON ){
		return( CUTIN_RET_RETURN );
	}
	
	Snd_SePlay( SE_SORAWOTOBU );
	cut->win_val = 0x800;
	cut->windel_light_flag = LIGHT_WINDEL;
	
	cut->seq_no++;
	return( CUTIN_RET_REPEAT );
}

//--------------------------------------------------------------
/**
 * カットイン 1　ウィンドウ閉じる
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_BirdRideONWndClose( CUTIN_WORK *cut )
{
	cut->win_setflag = FALSE;
	cut->win_y0 += cut->win_val;
	cut->win_y1 -= cut->win_val;
	
	cut->win_val += 0x800;
	
	if( cut->win_val > NUMFX32(16) ){
		cut->win_val = NUMFX32( 16 );
	}
	
	if( cut->win_y0 >= NUMFX32(CUTIN_CY-1) ){
		cut->win_y0 = NUMFX32( CUTIN_CY-1  );
	}
	
	if( cut->win_y1 <= NUMFX32(CUTIN_CY+1) ){
		cut->win_y1 = NUMFX32( CUTIN_CY+1 );
	}
	
	CutIn_WndPosSet( cut, cut->win_x0, cut->win_y0, cut->win_x1, cut->win_y1 );
	cut->win_setflag = TRUE;
	
	if( cut->fade_flag == FALSE ){
		if( CutIn_BirdMoveStateGet(cut) == BIRD_MOVESTATE_RIDE_ON_REQ_FADE ){
			cut->fade_flag = TRUE;
#if 0			
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );
#else
			Cip_FadeOutWhite();
#endif
		}
	}
	
	if( cut->win_y0 == NUMFX32(CUTIN_CY-1) && cut->win_y1 == NUMFX32(CUTIN_CY+1) ){
		CutIn_BGScreenClear( cut->fsys->bgl );
		cut->windel_light_flag = LIGHT_OFF;
		CutIn_WndOFF( cut );
		cut->seq_no++;
	}
	
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン 1　鳥搭乗　画面外待ち
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_BirdRideONEndWait( CUTIN_WORK *cut )
{
	if( cut->fade_flag == FALSE ){
		if( CutIn_BirdMoveStateGet(cut) == BIRD_MOVESTATE_RIDE_ON_REQ_FADE ){
			cut->fade_flag = TRUE;
#if 0			
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );
#else
			Cip_FadeOutWhite();
#endif
		}
	}
	
	if( CutIn_BirdMoveStateGet(cut) != BIRD_MOVESTATE_END ){
		return( CUTIN_RET_RETURN );
	}
	
	if( cut->fade_flag == FALSE ){
		cut->fade_flag = TRUE;
#if 0			
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );
#else
			Cip_FadeOutWhite();
#endif
	}
	
	CutIn_BirdDelete( cut );
	cut->seq_no++;
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
/**
 * カットイン 1　フェードアウト待ち
 * @param	cut		CUTIN_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int CutInMove_BirdRideONFadeOutWait( CUTIN_WORK *cut )
{
	if( WIPE_SYS_EndCheck() ) {
		cut->seq_no++;
	}
	
	return( CUTIN_RET_RETURN );
}

//--------------------------------------------------------------
///	カットイン動作テーブル
//--------------------------------------------------------------
static int (* const DATA_CutInSkyUpdateTbl[])( CUTIN_WORK *cut ) =
{
	CutInMove_GraphicInit,
	CutInMove_SkyGraphicInitWait,
	CutInMove_WndInit,
	CutInMove_WndMove0,
	CutInMove_WndMove1,
	CutInMove_HeroAnime,
	CutInMove_PokeMove0,
	CutInMove_PokeMove1,
	CutInMove_PokeMove2,
	CutInMove_PokeMove3,
//---
	CutInMove_PokeGraphicDelete,
	CutInMove_BirdGraphicInit,
	CutInMove_BirdGraphicInitWait,
	CutInMove_BirdStartUp,
	CutInMove_BirdStartUpWait,
	CutInMove_BirdStartUpAfterWait,
	CutInMove_BirdRideONWait,
	
	CutInMove_BirdRideONWndClose,
	CutInMove_BirdRideONEndWait,
	CutInMove_BirdRideONFadeOutWait,
	
	CutInMove_GraphicDelete,
	CutInMove_WndClear,
	CutInMove_End,
};

//==============================================================================
//	Vブランク動作
//==============================================================================
//--------------------------------------------------------------
/**
 * Vブランク初期化関数追加
 * @param	
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_VIntrInitTcbAdd( CUTIN_WORK *cut )
{
	cut->tcb_vintr_seq = 0;
	cut->tcb_vintr_end = FALSE;
	cut->tcb_vintr = VIntrTCB_Add( CutIn_VIntrInitTcb, cut, 0x80 );
}

//--------------------------------------------------------------
/**
 * Vブランク鳥初期化関数追加
 * @param	
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_VIntrBirdInitTcbAdd( CUTIN_WORK *cut )
{
	cut->tcb_vintr_seq = 0;
	cut->tcb_vintr_end = FALSE;
	cut->tcb_vintr = VIntrTCB_Add( CutIn_VIntrBirdInitTcb, cut, 0x80 );
}

//--------------------------------------------------------------
/**
 * Vブランク動作関数削除
 * @param	
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_VIntrTcbDelete( CUTIN_WORK *cut )
{
	if( cut->tcb_vintr != NULL ){
		TCB_Delete( cut->tcb_vintr );
		cut->tcb_vintr = NULL;
	}
}

//--------------------------------------------------------------
/**
 * Vブランク　初期化関数
 * @param	
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_VIntrInitTcb( TCB_PTR tcb, void *wk )
{
	int i;
	CUTIN_WORK *cutin = wk;
	
	switch( cutin->tcb_vintr_seq ){
	case 0:
		for( i = 0; i < CUTIN_CAUSE_CHAR_MAX; i++ ){
			if( cutin->clact_resobj_char[i] != NULL ){
				CLACT_U_CharManagerSetAreaCont( cutin->clact_resobj_char[i] );
			}
		}
		
		for( i = 0; i < CUTIN_CAUSE_PLTT_MAX; i++ ){
			if( cutin->clact_resobj_pltt[i] != NULL ){
				CLACT_U_PlttManagerSetCleanArea( cutin->clact_resobj_pltt[i] );
			}
		}
		
		if( cutin->poke_char_buf != NULL ){
			CutIn_PokeGraResmSetCleanAreaChar( cutin, cutin->poke_char_buf );
		}
			
		if( cutin->poke_pal_buf != NULL ){
			CutIn_PokeGraResmSetCleanAreaPltt( cutin, cutin->poke_pal_buf );
		}
		
		cutin->tcb_vintr_seq++;
		VWaitTCB_Add( CutIn_VWaitInitTcb, cutin, 0x80 );
		break;
	}
}

//--------------------------------------------------------------
/**
 * VWait　初期化関数
 * @param	
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_VWaitInitTcb( TCB_PTR tcb, void *wk )
{
	int i;
	CUTIN_WORK *cutin = wk;
	
	if( cutin->tcb_vintr_seq == 1 ){
		//VRAMにキャラ、パレット配置後、ワークリソースを破棄
		for( i = 0; i < CUTIN_CAUSE_CHAR_MAX; i++ ){
			if( cutin->clact_resobj_char[i] != NULL ){
				CLACT_U_ResManagerResOnlyDelete( cutin->clact_resobj_char[i] );
			}
		}
	
		for( i = 0; i < CUTIN_CAUSE_PLTT_MAX; i++ ){
			if( cutin->clact_resobj_pltt[i] != NULL ){
				CLACT_U_ResManagerResOnlyDelete( cutin->clact_resobj_pltt[i] );
			}
		}
		
		if( cutin->poke_char_buf != NULL ){
			sys_FreeMemoryEz( cutin->poke_char_buf );
			cutin->poke_char_buf = NULL;
		}
		
		if( cutin->poke_pal_buf != NULL ){
			sys_FreeMemoryEz( cutin->poke_pal_buf );
			cutin->poke_pal_buf = NULL;
		}
		
		cutin->tcb_vintr_end = TRUE;
		TCB_Delete( tcb );
	}
}

//--------------------------------------------------------------
/**
 * Vブランク　鳥初期化関数
 * @param	
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_VIntrBirdInitTcb( TCB_PTR tcb, void *wk )
{
	CUTIN_WORK *cutin = wk;

	CLACT_U_RES_OBJ_PTR resobj_char =
		CLACT_U_ResManagerGetIDResObjPtr( cutin->clact_resm_char, CUTIN_CAID_CHAR_BIRD );
	
	switch( cutin->tcb_vintr_seq ){
	case 0:
		CLACT_U_CharManagerSetAreaCont( resobj_char );
		VWaitTCB_Add( CutIn_VWaitBirdInitTcb, cutin, 0x80 );
		cutin->tcb_vintr_seq++;
		break;
	}
}

//--------------------------------------------------------------
/**
 * VWait　鳥初期化関数
 * @param	
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_VWaitBirdInitTcb( TCB_PTR tcb, void *wk )
{
	CUTIN_WORK *cutin = wk;
	
	CLACT_U_RES_OBJ_PTR resobj_char =
		CLACT_U_ResManagerGetIDResObjPtr( cutin->clact_resm_char, CUTIN_CAID_CHAR_BIRD );
	
	if( cutin->tcb_vintr_seq == 1 ){
		CLACT_U_ResManagerResOnlyDelete( resobj_char );
		cutin->tcb_vintr_end = TRUE;
		TCB_Delete( tcb );
	}
}

//==============================================================================
//	グラフィック
//==============================================================================
//--------------------------------------------------------------
/**
 * カットイン　グラフィック初期化
 * @param	
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_GraphicInit( CUTIN_WORK *cut )
{
	ARCHANDLE *ahand = CutIn_ArcHandleOpen();
	
	CutIn_WndPosSet( cut, NUM_FX32(0), NUM_FX32(192), NUM_FX32(1), NUM_FX32(192) );
	CutIn_WndInit( cut );
	
	cut->save_bg0pri = GF_BGL_PriorityGet( cut->fsys->bgl, FLD_MBGFRM_MAP );
	cut->save_bg2pri = GF_BGL_PriorityGet( cut->fsys->bgl, CUTIN_BG_FRAME );
	
	G2_SetBG1Priority( 1 );
	G2_SetBG3Priority( 0 );
	
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
	
	CutIn_BGPaletteInit( ahand, NARC_field_cutin_hidenbg_NCLR, &cut->pPltt );
	CutIn_BGCharInit( cut->fsys->bgl , ahand, NARC_field_cutin_hidenbg01_NCGR, &cut->pChar );
	CutIn_BGScreenInit( cut->fsys->bgl, ahand, NARC_field_cutin_hidenbg01_NSCR, &cut->pScreen );
	
	CutIn_ClactInit( cut, ahand );
	ArchiveDataHandleClose( ahand );
	
	cut->cutin_eoa_sys = EOA_SysInit( HEAPID_FIELD, CUTIN_EOA_MAX );
	
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
}

//--------------------------------------------------------------
/**
 * カットイン　グラフィック削除
 * @param	
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_GraphicDelete( CUTIN_WORK *cut )
{
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
	
	EOA_SysDeleteAll( cut->cutin_eoa_sys );
	CutIn_BGScreenClear( cut->fsys->bgl );
	CutIn_ClactDest( cut );
	
	G2_SetBG0Priority( cut->save_bg0pri );
	G2_SetBG3Priority( cut->save_bg2pri );
	
	FieldMsgPrintInit( PALTYPE_MAIN_BG, MSG_PRINT_INIT_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
}

//--------------------------------------------------------------
/**
 * アーカイブハンドルオープン
 * @param
 * @retval
 */
//--------------------------------------------------------------
static ARCHANDLE * CutIn_ArcHandleOpen( void )
{
	return( ArchiveDataHandleOpen(ARC_FIELD_CUTIN_GRA,HEAPID_FIELD) );
}

//==============================================================================
//	セルアクター
//==============================================================================
//--------------------------------------------------------------
/**
 * セルアクター初期化
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_ClactInit( CUTIN_WORK *cutin, ARCHANDLE *ahand )
{
	int i;
	
	//ポケモンスプライトアーカイブ情報取得
	CutIn_PokeGraSoftSpriteArcMake( cutin, &cutin->ssa );
	
	//セルアクター初期化
	cutin->clact_set = CLACT_U_SetEasyInit(
			CUTIN_CA_MAX, &cutin->clact_easydata, HEAPID_FIELD );

	CLACT_U_SetSubSurfaceMatrix( &cutin->clact_easydata, 0, FX32_CONST(512) );


	//リソース初期化
	cutin->clact_resm_char =
		CLACT_U_ResManagerInit( CUTIN_CAUSE_CHAR_MAX, CLACT_U_CHAR_RES, HEAPID_FIELD );
	cutin->clact_resm_pltt =
		CLACT_U_ResManagerInit( CUTIN_CAUSE_PLTT_MAX, CLACT_U_PLTT_RES, HEAPID_FIELD );
	cutin->clact_resm_cell =
		CLACT_U_ResManagerInit( CUTIN_CAUSE_CELL_MAX, CLACT_U_CELL_RES, HEAPID_FIELD );
	cutin->clact_resm_anime =
		CLACT_U_ResManagerInit( CUTIN_CAUSE_ANM_MAX, CLACT_U_CELLANM_RES, HEAPID_FIELD );
	
	//キャラリソース展開
	for( i = 0; i < CUTIN_CAUSE_CHAR_ALWAYS_MAX; i++ ){
		cutin->clact_resobj_char[i] =
			CLACT_U_ResManagerResAddArcChar_ArcHandle(
				cutin->clact_resm_char, ahand,
				DATA_NArcID_AlwaysChar[i].narc_id, FALSE, DATA_NArcID_AlwaysChar[i].reg_id,
				NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_FIELD );
	}
	
	if( cutin->sex == PM_MALE ){	//hero
		cutin->clact_resobj_char[i] =
			CLACT_U_ResManagerResAddArcChar_ArcHandle(
				cutin->clact_resm_char, ahand,
				NARC_field_cutin_hidenhero_NCGR, FALSE, CUTIN_CAID_CHAR_HERO,
				NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_FIELD );
	}else{							//heroine
		cutin->clact_resobj_char[i] =
			CLACT_U_ResManagerResAddArcChar_ArcHandle(
				cutin->clact_resm_char, ahand,
				NARC_field_cutin_hidenheroine_NCGR, FALSE, CUTIN_CAID_CHAR_HERO,
				NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_FIELD );
	}
	
	i++;	//次のリソースOBJへ
	cutin->clact_resobj_char[i] = CutIn_PokeGraResmAddCharDummy( cutin, ahand );
	
	//パレットリソース展開
	for( i = 0; i < CUTIN_CAUSE_PLTT_ALWAYS_MAX; i++ ){
		cutin->clact_resobj_pltt[i] =
			CLACT_U_ResManagerResAddArcPltt_ArcHandle(
				cutin->clact_resm_pltt, ahand,
				DATA_NArcID_AlwaysPltt[i].narc_id, FALSE, DATA_NArcID_AlwaysPltt[i].reg_id,
				NNS_G2D_VRAM_TYPE_2DMAIN, 1, HEAPID_FIELD );
	}
	
	if( cutin->sex == PM_MALE ){	//hero
		//光線と同一
	}else{							//heroine
		cutin->clact_resobj_pltt[i] =
			CLACT_U_ResManagerResAddArcPltt_ArcHandle(
				cutin->clact_resm_pltt, ahand,
				NARC_field_cutin_heroine_NCLR, FALSE, CUTIN_CAID_PLTT_HEROINE,
				NNS_G2D_VRAM_TYPE_2DMAIN, 1, HEAPID_FIELD );
		
		i++;	//次のリソースOBJへ
	}
	
	cutin->clact_resobj_pltt[i] = CutIn_PokeGraResmAddPlttDummy( cutin, ahand );
	
	//セル展開
	for( i = 0; i < CUTIN_CAUSE_CELL_ALWAYS_MAX; i++ ){
		cutin->clact_resobj_cell[i] =
			CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
				cutin->clact_resm_cell, ahand,
				DATA_NArcID_AlwaysCell[i].narc_id, FALSE, DATA_NArcID_AlwaysCell[i].reg_id,
				CLACT_U_CELL_RES, HEAPID_FIELD );
	}
	
	if( cutin->sex == PM_MALE ){	//hero
		cutin->clact_resobj_cell[i] =
			CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
				cutin->clact_resm_cell, ahand,
				NARC_field_cutin_hidenhero_NCER, FALSE, CUTIN_CAID_CELL_HERO,
				CLACT_U_CELL_RES, HEAPID_FIELD );
	}else{							//heroine
		cutin->clact_resobj_cell[i] =
			CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
				cutin->clact_resm_cell, ahand,
				NARC_field_cutin_hidenheroine_NCER, FALSE, CUTIN_CAID_CELL_HERO,
				CLACT_U_CELL_RES, HEAPID_FIELD );
	}
	
	i++;	//次のリソースへ
	cutin->clact_resobj_cell[i] =
		CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			cutin->clact_resm_cell, ahand,
			NARC_field_cutin_poke_oam_NCER, FALSE, CUTIN_CAID_CELL_POKE,
			CLACT_U_CELL_RES, HEAPID_FIELD );
	
	//アニメ展開
	for( i = 0; i < CUTIN_CAUSE_ANM_ALWAYS_MAX; i++ ){
		cutin->clact_resobj_anime[i] =
			CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
				cutin->clact_resm_anime, ahand,
				DATA_NArcID_AlwaysAnime[i].narc_id, FALSE, DATA_NArcID_AlwaysAnime[i].reg_id,
				CLACT_U_CELLANM_RES, HEAPID_FIELD );
	}
	
	if( cutin->sex == PM_MALE ){	//hero
		cutin->clact_resobj_anime[i] =
			CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
				cutin->clact_resm_anime, ahand,
				NARC_field_cutin_hidenhero_NANR, FALSE, CUTIN_CAID_ANM_HERO,
				CLACT_U_CELLANM_RES, HEAPID_FIELD );
	}else{							//heroine
		cutin->clact_resobj_anime[i] =
			CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
				cutin->clact_resm_anime, ahand,
				NARC_field_cutin_hidenheroine_NANR, FALSE, CUTIN_CAID_ANM_HERO,
				CLACT_U_CELLANM_RES, HEAPID_FIELD );
	}
	
	cutin->poke_char_buf = CutIn_PokeGraOamGet( cutin->poke_param, &cutin->ssa, HEAPID_FIELD );
	cutin->poke_pal_buf = CutIn_PokeGraPlttGet( &cutin->ssa, HEAPID_FIELD );
}

//--------------------------------------------------------------
/**
 * セルアクター破棄
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_ClactDest( CUTIN_WORK *cutin )
{
	int i;
	
	//VRAMに展開されたキャラ、パレット削除
	for( i = 0; i < CUTIN_CAUSE_CHAR_MAX; i++ ){
		if( cutin->clact_resobj_char[i] != NULL ){
			CLACT_U_CharManagerDelete( cutin->clact_resobj_char[i] );
		}
	}
	
	for( i = 0; i < CUTIN_CAUSE_PLTT_MAX; i++ ){
		if( cutin->clact_resobj_pltt[i] != NULL ){
			CLACT_U_PlttManagerDelete( cutin->clact_resobj_pltt[i] );
		}
	}
	
	//セル、アニメ使用領域破棄
	for( i = 0; i < CUTIN_CAUSE_CELL_MAX; i++ ){
		if( cutin->clact_resobj_cell[i] != NULL ){
			CLACT_U_ResManagerResOnlyDelete( cutin->clact_resobj_cell[i] );
		}
	}
	
	for( i = 0; i < CUTIN_CAUSE_ANM_MAX; i++ ){
		if( cutin->clact_resobj_anime[i] != NULL ){
			CLACT_U_ResManagerResOnlyDelete( cutin->clact_resobj_anime[i] );
		}
	}
	
	CLACT_U_ResManagerDelete( cutin->clact_resm_char );
	CLACT_U_ResManagerDelete( cutin->clact_resm_pltt );
	CLACT_U_ResManagerDelete( cutin->clact_resm_cell );
	CLACT_U_ResManagerDelete( cutin->clact_resm_anime );
	
	//アクター全部削除
	CLACT_DelAllSet( cutin->clact_set );
	//セルアクター破棄
	CLACT_DestSet( cutin->clact_set );
}

//--------------------------------------------------------------
/**
 * セルアクター描画
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_ClactDraw( CUTIN_WORK *cutin )
{
	if( cutin->clact_set != NULL ){
		CLACT_Draw( cutin->clact_set );
	}
}

//--------------------------------------------------------------
/**
 * アクター追加
 * @param	char_id				キャラクタデータID
 * @param	pltt_id				パレットデータID
 * @param	cell_id				セルデータID
 * @param	cellanm_id			セルアニメーションID	無いときはCLACT_U_HEADER_DATA_NONE
 * @param	bg_pri				BGプライオリティ
 * @param	act_pri				アクタープライオリティ
 * @retval
 */
//--------------------------------------------------------------
static CLACT_WORK_PTR CutIn_ClActAdd( CUTIN_WORK *cutin, const VecFx32 *vec,
		u32 char_id, u32 pltt_id, u32 cell_id, u32 cellanm_id, int bg_pri, int act_pri )
{
	CLACT_HEADER head;
	CLACT_ADD_SIMPLE add;
	CLACT_WORK_PTR act;
	
	if( cellanm_id == CUTIN_CAUSE_CELL_MAX ){
		CLACT_U_MakeHeader(
				&head, char_id, pltt_id, cell_id, CLACT_U_HEADER_DATA_NONE,
				CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
				FALSE, bg_pri,
				cutin->clact_resm_char,
				cutin->clact_resm_pltt,
				cutin->clact_resm_cell,
				NULL,
				NULL, NULL );
	}else{
		CLACT_U_MakeHeader(
				&head, char_id, pltt_id, cell_id, cellanm_id,
				CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
				FALSE,
				bg_pri,
				cutin->clact_resm_char,
				cutin->clact_resm_pltt,
				cutin->clact_resm_cell,
				cutin->clact_resm_anime,
				NULL, NULL );
	}
	
	add.ClActSet = cutin->clact_set;
	add.ClActHeader = &head;
	add.mat = *vec;
	add.pri = act_pri;
	add.DrawArea = NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap = HEAPID_FIELD;
		
	act = CLACT_AddSimple( &add );
	GF_ASSERT( act != NULL && "CLACT_AddSimple() Error" );
	
	return( act );
}

//--------------------------------------------------------------
/**
 * アクター　ライト追加
 * @retval
 */
//--------------------------------------------------------------
static CLACT_WORK_PTR CutIn_ClactAdd_Light(
		CUTIN_WORK *cutin, const VecFx32 *vec, int act_pri, int anm_no )
{
	CLACT_WORK_PTR act;
	
	act = CutIn_ClActAdd( cutin, vec,
		CUTIN_CAID_CHAR_LIGHT, CUTIN_CAID_PLTT_HERO_BIRD,
		CUTIN_CAID_CELL_LIGHT, CUTIN_CAID_ANM_LIGHT, 0, act_pri );
	
	CLACT_AnmChg( act, anm_no );
	return( act );
}

//--------------------------------------------------------------
/**
 * アクター　自機追加
 * @retval
 */
//--------------------------------------------------------------
static CLACT_WORK_PTR CutIn_ClactAdd_Hero( CUTIN_WORK *cutin, const VecFx32 *vec )
{
	CLACT_WORK_PTR act;
	u32 pltt_id = CUTIN_CAID_PLTT_HERO_BIRD;
	
	if( cutin->sex == PM_FEMALE ){
		pltt_id = CUTIN_CAID_PLTT_HEROINE;
	}
	
	act = CutIn_ClActAdd( cutin, vec,
		CUTIN_CAID_CHAR_HERO, pltt_id,
		CUTIN_CAID_CELL_HERO, CUTIN_CAID_ANM_HERO, 0, ACTPRI_CUTIN_HERO );
	
	CLACT_SetDrawFlag( act, 0 );
	CLACT_AnmChg( act, JIKIANMNO_HIDEN );
	return( act );
}

//--------------------------------------------------------------
/**
 * アクター　自機オートアニメ開始
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_ClactAutoAnimeStart( CLACT_WORK_PTR act )
{
	CLACT_SetAnmFlag( act, 1 );
	CLACT_SetAnmFrame( act, FX32_ONE );
}

//--------------------------------------------------------------
/**
 * アクター　鳥追加
 * @retval
 */
//--------------------------------------------------------------
static CLACT_WORK_PTR CutIn_ClactAdd_Bird(
		CUTIN_WORK *cutin, const VecFx32 *vec, int act_pri, int anm_no )
{
	CLACT_WORK_PTR act;
	VecFx32 affoffs = { 0,0,0 };
	VecFx32 scale = { 0x1000,0x1000,0};
	
	act = CutIn_ClActAdd( cutin, vec,
		CUTIN_CAID_CHAR_BIRD, CUTIN_CAID_PLTT_HERO_BIRD,
		CUTIN_CAID_CELL_BIRD, CLACT_U_HEADER_DATA_NONE, 0, act_pri );
	CLACT_SetAffineParam( act, CLACT_AFFINE_DOUBLE );
	
	CLACT_SetAffineMatrix( act, &affoffs );
	CLACT_SetScale( act, &scale );
	CLACT_SetRotation( act, RotKeyR(0) );
	
	return( act );
}

//--------------------------------------------------------------
/**
 * 鳥グラフィック追加
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_ClActBirdGraphicInit( CUTIN_WORK *cutin )
{
	int i;
	ARCHANDLE *ahand = CutIn_ArcHandleOpen();
	
	for( i = 0; i < CUTIN_CAUSE_CHAR_MAX; i++ ){
		if( cutin->clact_resobj_char[i] == NULL ){
			cutin->clact_resobj_char[i] =
				CLACT_U_ResManagerResAddArcChar_ArcHandle(
					cutin->clact_resm_char, ahand,
					NARC_field_cutin_hidenbird_NCGR, FALSE, CUTIN_CAID_CHAR_BIRD,
					NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_FIELD );
			break;
		}
	}
	GF_ASSERT( i < CUTIN_CAUSE_CHAR_MAX );
	
	for( i = 0; i < CUTIN_CAUSE_CELL_MAX; i++ ){
		if( cutin->clact_resobj_cell[i] == NULL ){
			cutin->clact_resobj_cell[i] =
				CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
					cutin->clact_resm_cell, ahand,
					NARC_field_cutin_hidenbird_NCER, FALSE, CUTIN_CAID_CELL_BIRD,
					CLACT_U_CELL_RES, HEAPID_FIELD );
			break;
		}
	}
	GF_ASSERT( i < CUTIN_CAUSE_CELL_MAX );
	
	ArchiveDataHandleClose( ahand );
}

//==============================================================================
//	BG
//==============================================================================
//--------------------------------------------------------------
/**
 * BGパレット初期化
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_BGPaletteInit( ARCHANDLE *ahand, u32 arc_id, NNSG2dPaletteData **pPltt )
{
	void *buf;
	
	buf = ArchiveDataLoadAllocByHandle( ahand, arc_id, HEAPID_FIELD );
	NNS_G2dGetUnpackedPaletteData( buf, pPltt );
	GF_BGL_PaletteSet( CUTIN_BG_FRAME, (*pPltt)->pRawData, 
		CUTIN_BG_PLTT_SIZE, CUTIN_BG_SET_PLTT_OFFSET );
	sys_FreeMemoryEz( buf );
}

//--------------------------------------------------------------
/**
 * BGキャラ初期化
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_BGCharInit(
		GF_BGL_INI *ini, ARCHANDLE *ahand, u32 arc_id, NNSG2dCharacterData **pChar )
{
	void *buf;
	
	buf = ArchiveDataLoadAllocByHandle( ahand, arc_id, HEAPID_FIELD );
	NNS_G2dGetUnpackedCharacterData( buf, pChar );
	GF_BGL_LoadCharacter( ini, CUTIN_BG_FRAME,
		(*pChar)->pRawData, (*pChar)->szByte, CUTIN_BG_SET_CHAR_OFFSET );
	sys_FreeMemoryEz( buf );
}

//--------------------------------------------------------------
/**
 * BGスクリーン初期化
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_BGScreenInit( 
		GF_BGL_INI *ini, ARCHANDLE *ahand, u32 arc_id, NNSG2dScreenData **pScr )
{
	void *buf;
	
	GF_BGL_ScrollSet( ini, CUTIN_BG_FRAME, GF_BGL_SCROLL_X_SET, 0 );
	GF_BGL_ScrollSet( ini, CUTIN_BG_FRAME, GF_BGL_SCROLL_Y_SET, 0 );
	
	buf = ArchiveDataLoadAllocByHandle( ahand, arc_id, HEAPID_FIELD );
	NNS_G2dGetUnpackedScreenData( buf, pScr );
	GF_BGL_ScreenBufSet( ini, CUTIN_BG_FRAME, (void*)(*pScr)->rawData, (*pScr)->szByte );
	GF_BGL_ScrPalChange( ini, CUTIN_BG_FRAME, 0, 0, 32, 32, CUTIN_BG_PLTT_NO );
	GF_BGL_LoadScreenReq( ini, CUTIN_BG_FRAME );
	sys_FreeMemoryEz( buf );
}

//--------------------------------------------------------------
/**
 * BGスクリーンクリア
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_BGScreenClear( GF_BGL_INI *ini )
{
//	GF_BGL_ScrFill( ini, CUTIN_BG_FRAME, 0, 0, 0, 255, 255, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrClear( ini, CUTIN_BG_FRAME );
}

//==============================================================================
//	ウィンドウ
//==============================================================================
//--------------------------------------------------------------
/**
 * ウィンドウ初期化
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_WndInit( CUTIN_WORK *cut )
{
	Cip_VIntrTcbWindowInit( cut );
	
	cut->win_setflag = FALSE;
	CutIn_WndOFF( cut );
	CutIn_WndPlaneInit( cut );
//	CutIn_WndPosSet( cut, 0, 192, 1, 192 );
	CutIn_WndON( cut );
	cut->win_setflag = TRUE;
}

//--------------------------------------------------------------
/**
 * ウィンドウ表示ON
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_WndON( CUTIN_WORK *cut )
{
//	GX_SetVisibleWnd( CUTIN_WND );
	cut->win0_visible = CUTIN_WND;
}

//--------------------------------------------------------------
/**
 * ウィンドウ表示OFF
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_WndOFF( CUTIN_WORK *cut )
{
//	GX_SetVisibleWnd( GX_WNDMASK_NONE );
	cut->win0_visible = GX_WNDMASK_NONE;
}

//--------------------------------------------------------------
/**
 * ウィンドウ表示設定初期化
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_WndPlaneInit( CUTIN_WORK *cut )
{
#if 0
	G2_SetWnd0InsidePlane(											//内側
			CUTIN_BG_WINMASK|GX_WND_PLANEMASK_OBJ,					//BGとOBJ
			FALSE );												//α無効
	
	G2_SetWndOutsidePlane(
			(GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_BG1|			//OBJとカットインBG以外有効
			 GX_WND_PLANEMASK_BG2|GX_WND_PLANEMASK_BG3|
			 GX_WND_PLANEMASK_OBJ) &
			CUTIN_BG_WINMASK_NOT, TRUE );
#else
	cut->win0_inside =	CUTIN_BG_WINMASK|GX_WND_PLANEMASK_OBJ;		//BGとOBJ
	cut->win0_inside_alpha = FALSE;									//α無効
	cut->win0_outside =
			(GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_BG1|			//OBJとカットインBG以外有効
			 GX_WND_PLANEMASK_BG2|GX_WND_PLANEMASK_BG3|
			 GX_WND_PLANEMASK_OBJ) &
			CUTIN_BG_WINMASK_NOT;
	cut->win0_outside_alpha = TRUE;
#endif
}

//--------------------------------------------------------------
/**
 * ウィンドウ表示設定　外すべて有効
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_WndPlaneOutsideOBJ_ON( CUTIN_WORK *cut )
{
#if 0	
	G2_SetWndOutsidePlane(
			(GX_WND_PLANEMASK_OBJ|
			 GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_BG1|			//OBJとカットインBG以外有効
			 GX_WND_PLANEMASK_BG2|GX_WND_PLANEMASK_BG3) &
			CUTIN_BG_WINMASK_NOT, TRUE );
#else
	cut->win0_outside = 
			(GX_WND_PLANEMASK_OBJ|
			 GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_BG1|			//OBJとカットインBG以外有効
			 GX_WND_PLANEMASK_BG2|GX_WND_PLANEMASK_BG3) &
			CUTIN_BG_WINMASK_NOT;
	cut->win0_outside_alpha = TRUE;
#endif
}

//--------------------------------------------------------------
/**
 * ウィンドウ表示位置セット
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_WndPosSet( CUTIN_WORK *cut, fx32 x0, fx32 y0, fx32 x1, fx32 y1 )
{
//	G2_SetWnd0Position( x0/FX32_ONE, y0/FX32_ONE, x1/FX32_ONE, y1/FX32_ONE );
	cut->win_x0 = x0;
	cut->win_x1 = x1;
	cut->win_y0 = y0;
	cut->win_y1 = y1;
}

//--------------------------------------------------------------
/**
 *
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void Cip_VIntrTcbWindowInit( CUTIN_WORK *cut )
{
	GF_ASSERT( cut->tcb_vintr_window == NULL );
	cut->tcb_vintr_window = VIntrTCB_Add( Cip_VIntrTcbWindow, cut, 0x81 );
}

//--------------------------------------------------------------
/**
 *
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void Cip_VIntrTcbWindowDelete( CUTIN_WORK *cut )
{
	GF_ASSERT( cut->tcb_vintr_window != NULL );
	TCB_Delete( cut->tcb_vintr_window );
	GX_SetVisibleWnd( GX_WNDMASK_NONE );
}

//--------------------------------------------------------------
/**
 *
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void Cip_VIntrTcbWindow( TCB_PTR tcb, void *wk )
{
	CUTIN_WORK *cut = wk;
	
	if( cut->win_setflag == FALSE ){		//パラメタ弄り中
		return;
	}
	
	GX_SetVisibleWnd( cut->win0_visible );
	G2_SetWnd0InsidePlane( cut->win0_inside, cut->win0_inside_alpha );	//内側
	G2_SetWndOutsidePlane( cut->win0_outside, cut->win0_outside_alpha );	//外側
	G2_SetWnd0Position(
		cut->win_x0/FX32_ONE, cut->win_y0/FX32_ONE,
		cut->win_x1/FX32_ONE, cut->win_y1/FX32_ONE );
}

//==============================================================================
//	ポケモングラフィック
//==============================================================================
//--------------------------------------------------------------
/**
 * SOFT_SPRITE_ARC生成
 * @param	cut	
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_PokeGraSoftSpriteArcMake( CUTIN_WORK *cut, SOFT_SPRITE_ARC *ssa )
{
	PokeGraArcDataGetPP( ssa, cut->poke_param, PARA_FRONT );
}

//--------------------------------------------------------------
/**
 * ポケモン絵をOAM変換したバッファを取得
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void * CutIn_PokeGraOamGet( POKEMON_PARAM *param, SOFT_SPRITE_ARC *ssa, u32 heap_id )
{
	void *buf = sys_AllocMemory( HEAPID_FIELD, (32*10)*10 );
	GF_ASSERT( buf != NULL && "CutIn_PokeGraOamGet()バッファ取得失敗\n" );
	
#if 0	
	ChangesInto_BattlePokeData(	ssa->arc_no, ssa->index_chr, heap_id, buf );
#else
	{
		int rnd = PokeParaGet( param, ID_PARA_personal_rnd, NULL );
		Ex_ChangesInto_BattlePokeData(
			ssa->arc_no, ssa->index_chr, heap_id, buf, 
			rnd, FALSE, PARA_FRONT, ssa->strike_mons );
	}
#endif
	
	return( buf );
}

//--------------------------------------------------------------
/**
 * ポケモンパレットバッファを取得
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void * CutIn_PokeGraPlttGet( SOFT_SPRITE_ARC *ssa, u32 heap_id )
{
//	void *buf = ArchiveDataLoadMallocLo( ssa->arc_no, ssa->index_pal, heap_id );
	void *buf = ChangesInto_BattlePokePalData_Alloc( ssa->arc_no, ssa->index_pal, heap_id );
	return( buf );
}

//--------------------------------------------------------------
/**
 * リソースマネージャポケモンキャラダミー登録
 * @param
 * @retval
 */
//--------------------------------------------------------------
static CLACT_U_RES_OBJ_PTR CutIn_PokeGraResmAddCharDummy( CUTIN_WORK *cutin, ARCHANDLE *ahand )
{
	CLACT_U_RES_OBJ_PTR reso;
	
	reso = CLACT_U_ResManagerResAddArcChar_ArcHandle(
				cutin->clact_resm_char, ahand,
				NARC_field_cutin_poke_oam_NCGR, FALSE, CUTIN_CAID_CHAR_POKE,
				NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_FIELD );
	
	return( reso );
}

//--------------------------------------------------------------
/**
 * リソースマネージャポケモンキャラVRAM転送
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_PokeGraResmSetCleanAreaChar( CUTIN_WORK *cutin, void *buf )
{
	u32 vram;
	CLACT_U_RES_OBJ_PTR reso;
	const NNSG2dImageProxy *proxy;
	
	reso = CLACT_U_ResManagerGetIDResObjPtr( cutin->clact_resm_char, CUTIN_CAID_CHAR_POKE );
	proxy = CLACT_U_CharManagerGetProxy( reso );
	
	vram = NNS_G2dGetImageLocation( proxy, NNS_G2D_VRAM_TYPE_2DMAIN );
	DC_FlushRange( (void*)buf, POKE_CHAR_SIZE );
	GX_LoadOBJ( buf, vram, POKE_CHAR_SIZE );
}

//--------------------------------------------------------------
/**
 * リソースマネージャポケモンパレットダミー登録
 * @param
 * @retval
 */
//--------------------------------------------------------------
static CLACT_U_RES_OBJ_PTR CutIn_PokeGraResmAddPlttDummy( CUTIN_WORK *cutin, ARCHANDLE *ahand )
{
	CLACT_U_RES_OBJ_PTR reso;
	
	reso = CLACT_U_ResManagerResAddArcPltt_ArcHandle(
				cutin->clact_resm_pltt, ahand,
				NARC_field_cutin_dp_boy01_NCLR, FALSE, CUTIN_CAID_PLTT_POKE,
				NNS_G2D_VRAM_TYPE_2DMAIN, 1, HEAPID_FIELD );
	
	return( reso );
}

//--------------------------------------------------------------
/**
 * リソースマネージャポケモンキャラVRAM転送
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_PokeGraResmSetCleanAreaPltt( CUTIN_WORK *cutin, void *buf )
{
	u32 vram;
	CLACT_U_RES_OBJ_PTR reso_pltt,reso_char;
	NNSG2dImageProxy *proxy_image;
	const NNSG2dImagePaletteProxy *proxy_pltt;
	
	reso_char = CLACT_U_ResManagerGetIDResObjPtr(
					cutin->clact_resm_char, CUTIN_CAID_CHAR_POKE );
	proxy_image = CLACT_U_CharManagerGetProxy( reso_char );
	
	reso_pltt = CLACT_U_ResManagerGetIDResObjPtr(
					cutin->clact_resm_pltt, CUTIN_CAID_PLTT_POKE );
	proxy_pltt = CLACT_U_PlttManagerGetProxy( reso_pltt, proxy_image );
	
	vram = NNS_G2dGetImagePaletteLocation( proxy_pltt, NNS_G2D_VRAM_TYPE_2DMAIN );
	DC_FlushRange( (void*)buf, POKE_PLTT_SIZE );
	GX_LoadOBJPltt( buf, vram, POKE_PLTT_SIZE );
}

//--------------------------------------------------------------
/**
 * ポケモングラフィック削除
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_PokeGraResmDelete( CUTIN_WORK *cutin )
{
	int i;
	
	CLACT_U_RES_OBJ_PTR resobj =
		CLACT_U_ResManagerGetIDResObjPtr( cutin->clact_resm_char, CUTIN_CAID_CHAR_POKE );
	CLACT_U_CharManagerDelete( resobj );
	CLACT_U_ResManagerResDelete( cutin->clact_resm_char, resobj );
	
	for( i = 0; i < CUTIN_CAUSE_CHAR_MAX; i++ ){
		if( cutin->clact_resobj_char[i] == resobj ){
			cutin->clact_resobj_char[i] = NULL;
			break;
		}
	}
	GF_ASSERT( i < CUTIN_CAUSE_CHAR_MAX );
	
	resobj =
		CLACT_U_ResManagerGetIDResObjPtr( cutin->clact_resm_pltt, CUTIN_CAID_PLTT_POKE );
	CLACT_U_PlttManagerDelete( resobj );
	CLACT_U_ResManagerResDelete( cutin->clact_resm_pltt, resobj );
	
	for( i = 0; i < CUTIN_CAUSE_PLTT_MAX; i++ ){
		if( cutin->clact_resobj_pltt[i] == resobj ){
			cutin->clact_resobj_pltt[i] = NULL;
			break;
		}
	}
	GF_ASSERT( i < CUTIN_CAUSE_PLTT_MAX );
	
	resobj =
		CLACT_U_ResManagerGetIDResObjPtr( cutin->clact_resm_cell, CUTIN_CAID_CELL_POKE );
	CLACT_U_ResManagerResOnlyDelete( resobj );
	CLACT_U_ResManagerResDelete( cutin->clact_resm_cell, resobj );
	
	for( i = 0; i < CUTIN_CAUSE_CELL_MAX; i++ ){
		if( cutin->clact_resobj_cell[i] == resobj ){
			cutin->clact_resobj_cell[i] = NULL;
			break;
		}
	}
	GF_ASSERT( i < CUTIN_CAUSE_CELL_MAX );
}

//--------------------------------------------------------------
/**
 * ポケモン　セルアクター追加
 * @param
 * @retval
 */
//--------------------------------------------------------------
static CLACT_WORK_PTR CutIn_ClactAdd_Poke( CUTIN_WORK *cutin, const VecFx32 *vec )
{
	CLACT_WORK_PTR act;
	
	act = CutIn_ClActAdd( cutin, vec,
		CUTIN_CAID_CHAR_POKE, CUTIN_CAID_PLTT_POKE,
		CUTIN_CAID_CELL_POKE, CLACT_U_HEADER_DATA_NONE, 0, ACTPRI_CUTIN_POKE );
	
	return( act );
}

//==============================================================================
//	EOA 光線
//==============================================================================
typedef struct
{
	int act_pri;
	int windel;
	CUTIN_WORK *cutin;
	VecFx32 move_val;
}LIGHT_ADD_H;

typedef struct
{
	int seq_no;
	int type;
	CLACT_WORK_PTR clact;
	LIGHT_ADD_H head;
}LIGHT_WORK;

#define LIGHT_WORK_SIZE (sizeof(LIGHT_WORK))

typedef struct
{
	fx32 x;
	fx32 y;
	fx32 speed;
	int pri;
	int type;
}LIGHT_SET_POS;

static const EOA_H_NPP DATA_EoaH_Light;

#define LIGHT_SPEED_0 (NUMFX32(16))
#define LIGHT_SPEED_1 (NUMFX32(24))

#define LIGHT_MAX (13)

//--------------------------------------------------------------
///	追加テーブル
//--------------------------------------------------------------
static const LIGHT_SET_POS DATA_LightSetPosTbl[LIGHT_MAX] =
{
	{ NUMFX32(15), NUMFX32(63), LIGHT_SPEED_0, ACTPRI_CUTIN_LIGHT_0, LIGHT_ANMNO_0 },
	{ NUMFX32(76), NUMFX32(67), LIGHT_SPEED_0, ACTPRI_CUTIN_LIGHT_0, LIGHT_ANMNO_0 },
	{ NUMFX32(128), NUMFX32(61), LIGHT_SPEED_1, ACTPRI_CUTIN_LIGHT_1, LIGHT_ANMNO_1 },
	{ NUMFX32(240), NUMFX32(69), LIGHT_SPEED_0, ACTPRI_CUTIN_LIGHT_0, LIGHT_ANMNO_0 },
	
	{ NUMFX32(40), NUMFX32(78), LIGHT_SPEED_1, ACTPRI_CUTIN_LIGHT_1, LIGHT_ANMNO_1 },
	{ NUMFX32(72), NUMFX32(91), LIGHT_SPEED_0, ACTPRI_CUTIN_LIGHT_0, LIGHT_ANMNO_0 },
	{ NUMFX32(208), NUMFX32(86), LIGHT_SPEED_1, ACTPRI_CUTIN_LIGHT_1, LIGHT_ANMNO_1 },
	
	{ NUMFX32(56), NUMFX32(116), LIGHT_SPEED_0, ACTPRI_CUTIN_LIGHT_0, LIGHT_ANMNO_0 },
	{ NUMFX32(95), NUMFX32(109), LIGHT_SPEED_1, ACTPRI_CUTIN_LIGHT_1, LIGHT_ANMNO_1 },
	{ NUMFX32(159), NUMFX32(100), LIGHT_SPEED_0, ACTPRI_CUTIN_LIGHT_0, LIGHT_ANMNO_0 },
	
	{ NUMFX32(24), NUMFX32(126), LIGHT_SPEED_1, ACTPRI_CUTIN_LIGHT_1, LIGHT_ANMNO_1 },
	{ NUMFX32(140), NUMFX32(125), LIGHT_SPEED_1, ACTPRI_CUTIN_LIGHT_1, LIGHT_ANMNO_1 },
	{ NUMFX32(221), NUMFX32(124), LIGHT_SPEED_1, ACTPRI_CUTIN_LIGHT_1, LIGHT_ANMNO_1 },
};

//--------------------------------------------------------------
/**
 * 光線追加
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_LightSet( CUTIN_WORK *cut, int windel )
{
	int i,type,pri;
	VecFx32 mtx,speed;
	
	cut->windel_light_flag = LIGHT_WINDEL;
	
	for( i = 0; i < LIGHT_MAX; i++ ){
		mtx.x = DATA_LightSetPosTbl[i].x;
		mtx.y = DATA_LightSetPosTbl[i].y;
		mtx.z = 0;
		speed.x = DATA_LightSetPosTbl[i].speed;
		speed.y = 0;
		speed.z = 0;
		pri = DATA_LightSetPosTbl[i].pri;
		type = DATA_LightSetPosTbl[i].type;
		
		CutIn_EoaLightAdd( cut, &mtx, &speed, pri, type, windel );
		
		mtx.x += NUMFX32( 256 );
		CutIn_EoaLightAdd( cut, &mtx, &speed, pri, type, windel );
	}
}

//--------------------------------------------------------------
/**
 * EOA 光線追加
 * @param	
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_EoaLightAdd( CUTIN_WORK *cut,
		const VecFx32 *mtx, const VecFx32 *speed, int act_pri, int type, int windel )
{
	EOA_PTR eoa;
	LIGHT_ADD_H head;
	
	head.act_pri = act_pri;
	head.windel = windel;
	head.cutin = cut;
	head.move_val = *speed;
	eoa = EOA_Add_NPP(
		cut->cutin_eoa_sys, &DATA_EoaH_Light, mtx, type, &head, TCBPRI_CUTIN_EOA_LIGHT );
}

//--------------------------------------------------------------
/**
 * EOA 光線　初期化
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int EoaLight_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	LIGHT_WORK *work = wk;
	const LIGHT_ADD_H *head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	work->type = EOA_AddParamGet( eoa );
	
	EOA_MatrixGet( eoa, &mtx );
	
	work->clact = CutIn_ClactAdd_Light(
			work->head.cutin, &mtx, work->head.act_pri, work->type );
	CLACT_SetDrawFlag( work->clact, 0 );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 光線　削除
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void EoaLight_Delete( EOA_PTR eoa, void *wk )
{
	LIGHT_WORK *work = wk;
	CLACT_Delete( work->clact );
}

//--------------------------------------------------------------
/**
 * EOA 光線　動作
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void EoaLight_Move( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	LIGHT_WORK *work = wk;
	
	EOA_MatrixGet( eoa, &mtx );
	mtx.x += work->head.move_val.x;
	mtx.x %= NUMFX32( 512 );
	
	EOA_MatrixSet( eoa, &mtx );
	CLACT_SetMatrix( work->clact, &mtx );
	
	if( work->head.windel == TRUE ){
		CUTIN_WORK *cutin = work->head.cutin;
		
		if( cutin->windel_light_flag == LIGHT_WINDEL ){
			int draw = 0;
			fx32 y0 = cutin->win_y0, y1 = cutin->win_y1;
			
			if( (mtx.y-NUMFX32(2)) >= y0 && (mtx.y-NUMFX32(2)) <= y1 &&
				(mtx.y+NUMFX32(2)) >= y0 && (mtx.y+NUMFX32(2)) <= y1 ){
				draw = 1;
			}
			
			CLACT_SetDrawFlag( work->clact, draw );
		}else if( cutin->windel_light_flag == LIGHT_OFF ){
			CLACT_SetDrawFlag( work->clact, 0 );
		}
	}
}

//--------------------------------------------------------------
/**
 * EOA 光線　描画
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void EoaLight_Draw( EOA_PTR eoa, void *wk )
{
	LIGHT_WORK *work = wk;
}

//--------------------------------------------------------------
///	EOA_H　光線
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Light =
{
	LIGHT_WORK_SIZE,
	EoaLight_Init,
	EoaLight_Delete,
	EoaLight_Move,
	EoaLight_Draw,
};

//==============================================================================
//	EOA		鳥
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA 鳥追加
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_BirdInit( CUTIN_WORK *cut )
{
	VecFx32 mtx = {0,0,0};
	BIRD_ADD_H head;
	
	head.cutin = cut;
	
	cut->eoa_bird = EOA_Add_NPP(
		cut->cutin_eoa_sys, &DATA_EoaH_Bird, &mtx, 0, &head, TCBPRI_CUTIN_EOA_BIRD );
}

//--------------------------------------------------------------
/**
 * EOA 鳥終了チェック
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int CutIn_BirdMoveStateGet( CUTIN_WORK *cut )
{
	BIRD_WORK *work = EOA_LocalWorkGet( cut->eoa_bird );
	return( work->move_state );
}

//--------------------------------------------------------------
/**
 * EOA 鳥削除
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_BirdDelete( CUTIN_WORK *cut )
{
	BIRD_WORK *work = EOA_LocalWorkGet( cut->eoa_bird );
	if( work->eoa_jikimove ){ EOA_Delete( work->eoa_jikimove ); }
	if( work->tcb_camera ){ FieldZoom_Delete( work->tcb_camera ); }
	EOA_Delete( cut->eoa_bird );
}

//--------------------------------------------------------------
/**
 * EOA 鳥　初期化
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int EoaBird_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	BIRD_WORK *work = wk;
	const BIRD_ADD_H *head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	
	EOA_MatrixGet( eoa, &mtx );
	work->clact = CutIn_ClactAdd_Bird( work->head.cutin, &mtx, 0, 0 );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 鳥　削除
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void EoaBird_Delete( EOA_PTR eoa, void *wk )
{
	BIRD_WORK *work = wk;
	CLACT_Delete( work->clact );
}

//--------------------------------------------------------------
/**
 * EOA 鳥　動作
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void EoaBird_Move( EOA_PTR eoa, void *wk )
{
	BIRD_WORK *work = wk;
	int (* const *move)(BIRD_WORK*);
	
	move = DATA_EoaBirdMoveTbl[work->move_type];
	while( move[work->seq_no](work) == TRUE ){};
}

//--------------------------------------------------------------
/**
 * EOA 鳥　描画
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void EoaBird_Draw( EOA_PTR eoa, void *wk )
{
	BIRD_WORK *work = wk;
}

//--------------------------------------------------------------
///	EOA_H　鳥
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Bird =
{
	BIRD_WORK_SIZE,
	EoaBird_Init,
	EoaBird_Delete,
	EoaBird_Move,
	EoaBird_Draw,
};

//--------------------------------------------------------------
///	鳥　動作テーブル
//--------------------------------------------------------------
static int (* const * const DATA_EoaBirdMoveTbl[])( BIRD_WORK * ) =
{
	DATA_EoaBirdMoveTbl_Non,
	DATA_EoaBirdMoveTbl_StartUp,
	DATA_EoaBirdMoveTbl_RideON,
};

//==============================================================================
//	鳥動作　なし
//==============================================================================
//--------------------------------------------------------------
/**
 * とり動作　なしに変更
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_BirdMoveChange_Non( CUTIN_WORK *cut )
{
	BIRD_WORK *work = EOA_LocalWorkGet( cut->eoa_bird );
	work->move_type = BIRD_MOVETYPE_NON;
	work->seq_no = 0;
	work->move_state = BIRD_MOVESTATE_NON;
}

//--------------------------------------------------------------
/**
 * 鳥動作　なし
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int BirdMove_Non( BIRD_WORK *work )
{
	work->move_state = BIRD_MOVESTATE_NON;
	CLACT_SetDrawFlag( work->clact, 0 );
	return( FALSE );
}

//--------------------------------------------------------------
//	鳥　何もなし BIRD_MOVETYPE_NON
//--------------------------------------------------------------
static int (* const DATA_EoaBirdMoveTbl_Non[])( BIRD_WORK * ) =
{
	BirdMove_Non,
};

//==============================================================================
//	鳥動作　START_UP
//==============================================================================
//--------------------------------------------------------------
/**
 * 鳥動作　START_UPに変更
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_BirdMoveChange_StartUp( CUTIN_WORK *cut )
{
	VecFx32 mtx = {NUMFX32(128+8),NUMFX32(96-8),0};
	VecFx32 scale = { 0x0400,0x0400,0};
	
	BIRD_WORK *work = EOA_LocalWorkGet( cut->eoa_bird );
	work->move_type = BIRD_MOVETYPE_START_UP;
	work->seq_no = 0;
	work->move_state = BIRD_MOVESTATE_NON;
	
	work->mtx = mtx;
	work->offs.x = 0; work->offs.y = 0; work->offs.z = 0;
	work->rot = NUMFX32( 60 );
	work->scale = scale;
	work->scale_val = 0x200;
	work->angle = NUMFX32( 180 );
	work->angle_scale = 0;
	work->angle_scale_val = 0x2000;
	
	CLACT_SetMatrix( work->clact, &mtx );
	CLACT_SetScale( work->clact, &scale );
	CLACT_SetRotation( work->clact, RotKeyR(FX32NUM(work->rot)) );
	
	CLACT_SetDrawFlag( work->clact, 1 );
}

//--------------------------------------------------------------
/**
 * 鳥動作　START_UP 0
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int BirdMove_StartUp_0( BIRD_WORK *work )
{
	VecFx32 mtx;
	CLACT_WORK_PTR act = work->clact;
	
	work->angle_scale += work->angle_scale_val;
	
	if( work->angle_scale_val < NUMFX32(16) ){
		work->angle_scale_val += 0x4000;
	}
	
	work->offs.x = Cos360R( 315 ) * FX32NUM( work->angle_scale );
	work->offs.y = Sin360R( FX32NUM(work->angle) ) * FX32NUM( work->angle_scale );
	
	if( FX32NUM(work->angle) < 270 ){
		work->angle += 0x4000;
	}
	
	work->scale.x += work->scale_val;
	if( work->scale.x > 0x1000 ){ work->scale.x = 0x1000; }
	work->scale.y += work->scale_val;
	if( work->scale.y > 0x1000 ){ work->scale.y = 0x1000; }
	
	CLACT_SetScale( act, &work->scale );
	
	work->rot -= 0x6000;
	
	if( FX32NUM(work->rot) < 0 ){
		work->rot = 0;
	}
	
	CLACT_SetRotation( act, RotKeyR(FX32NUM(work->rot)) );
	
	mtx.x = work->mtx.x + work->offs.x;
	mtx.y = work->mtx.y + work->offs.y;
	CLACT_SetMatrix( act, &mtx );
	
	if( mtx.y < NUMFX32(-64) ){
		CLACT_SetDrawFlag( act, FALSE );
		work->move_state = BIRD_MOVESTATE_END;
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 鳥動作　START_UP 終了
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int BirdMove_StartUp_End( BIRD_WORK *work )
{
	return( FALSE );
}

//--------------------------------------------------------------
//	鳥　BIRD_MOVETYPE_START_UP
//--------------------------------------------------------------
static int (* const DATA_EoaBirdMoveTbl_StartUp[])( BIRD_WORK * ) =
{
	BirdMove_StartUp_0,
	BirdMove_StartUp_End,
};

//==============================================================================
//	鳥動作　
//==============================================================================
//--------------------------------------------------------------
/**
 * 鳥動作　RIDE_ONに変更
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_BirdMoveChange_RideON( CUTIN_WORK *cut )
{
	VecFx32 mtx = {NUMFX32(128),NUMFX32(104),0};
	VecFx32 scale = { 0x1400,0x1400,0};
	
	BIRD_WORK *work = EOA_LocalWorkGet( cut->eoa_bird );
	work->move_type = BIRD_MOVETYPE_RIDE_ON;
	work->seq_no = 0;
	work->move_state = BIRD_MOVESTATE_MOVE;
	work->frame = 0;
	
	work->mtx = mtx;
	work->offs.x = 0; work->offs.y = 0; work->offs.z = 0;
	work->rot = NUMFX32( 315 );
	work->scale = scale;
	work->scale_val = 0x0100;
//	work->angle = NUMFX32( 45 );
	work->angle = NUMFX32( 225 );
	work->angle_scale = NUMFX32( 128+64 );
	work->angle_scale_val = NUMFX32( 32 );
	
//	work->offs.x = Cos360R( 45 ) * FX32NUM( work->angle_scale );
	work->offs.x = Cos360R( 315 ) * FX32NUM( work->angle_scale );
	work->offs.y = Sin360R( FX32NUM(work->angle) ) * FX32NUM( work->angle_scale );
	mtx.x = work->mtx.x + work->offs.x;
	mtx.y = work->mtx.y + work->offs.y;
	
	CLACT_SetMatrix( work->clact, &mtx );
	CLACT_SetScale( work->clact, &scale );
	CLACT_SetRotation( work->clact, RotKeyR(FX32NUM(work->rot)) );
	
	CLACT_SetDrawFlag( work->clact, 1 );
	work->eoa_jikimove = CutIn_EoaJikiMoveAdd( cut->cutin_eoa_sys, cut->clact_hero );
	cut->winvanishoff_hero_flag = TRUE;
	
	work->tcb_camera = FieldZoom_Init( cut->fsys, HEAPID_FIELD );
	FieldZoom_TypeChange( work->tcb_camera, ZOOMTYPE_ZOOM, -CUTIN_ZOOM, 12 );
	
	{
		CLACT_WORK_PTR act_hero;
		VecFx32 affoffs = { 0,0,0 };
		VecFx32 scale = { 0x1000,0x1000,0};
	
		act_hero = work->head.cutin->clact_hero;
		CLACT_SetAffineParam( act_hero, CLACT_AFFINE_DOUBLE );
	
		CLACT_SetAffineMatrix( act_hero, &affoffs );
		CLACT_SetScale( act_hero, &scale );
		CLACT_SetRotation( act_hero, RotKeyR(0) );
	}
}

//--------------------------------------------------------------
/**
 * 鳥動作　RIDE_ON 0
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int BirdMove_RideON_0( BIRD_WORK *work )
{
	VecFx32 mtx;
	CLACT_WORK_PTR act = work->clact;
	
	work->angle_scale -= work->angle_scale_val;
	
	if( work->angle_scale < 0 ){
		work->angle_scale = 0;
	}
	
	if( work->angle_scale_val > 0x0800  ){
		work->angle_scale_val -= 0x1800;
	}
	
	if( work->angle_scale_val < 0x1000 ){
		work->angle_scale_val = 0x1000;
	}
	
	work->offs.x = Cos360R( 315 ) * FX32NUM( work->angle_scale );
	work->offs.y = Sin360R( FX32NUM(work->angle) ) * FX32NUM( work->angle_scale );
	
	if( FX32NUM(work->angle) < 270 ){
		work->angle += 0x4000;
	}
	
	work->scale.x += work->scale_val;
	if( work->scale.x > 0x1800 ){ work->scale.x = 0x1800; }
	work->scale.y += work->scale_val;
	if( work->scale.y > 0x1800){ work->scale.y = 0x1800; }
	
	CLACT_SetScale( act, &work->scale );
	
	work->rot += 0x8000;
	
	if( FX32NUM(work->rot) > 360 ){
		work->rot = NUMFX32( 360 );
	}
	
	CLACT_SetRotation( act, RotKeyR(FX32NUM(work->rot)) );
	
	mtx.x = work->mtx.x + work->offs.x;
	mtx.y = work->mtx.y + work->offs.y;
	CLACT_SetMatrix( act, &mtx );
	
	if( work->angle_scale == 0 ){
		work->frame = 0;
		work->seq_no++;
	}else{
		work->frame++;
	}

#if 0	
	if( work->frame == 16 ){
		CutIn_EoaJikiMoveChange_Jump( work->eoa_jikimove );
	}
#else
	if( work->frame == 12 ){
		CutIn_EoaJikiMoveChange_Jump( work->eoa_jikimove );
	}
#endif
	
	{
		CLACT_WORK_PTR act_hero = work->head.cutin->clact_hero;
		const VecFx32 *cas = CLACT_GetScale( act_hero );
		VecFx32 scale = *cas;
		
		scale.x += 0x0080;
		if( scale.x > 0x1400 ){ scale.x = 0x1400; }
		scale.y += 0x0080;
		if( scale.y > 0x1400 ){ scale.y = 0x1400; }
		
		CLACT_SetScale( act_hero, &scale );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 鳥動作　RIDE_ON 1
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int BirdMove_RideON_1( BIRD_WORK *work )
{
	CLACT_WORK_PTR act_hero = work->head.cutin->clact_hero;
	CLACT_AnmChg( act_hero, JIKIANMNO_STAY_D );
	
	{
		fx32 hy,by;
		const VecFx32 *cmtx = CLACT_GetMatrix( act_hero );
		hy = cmtx->y;
		cmtx = CLACT_GetMatrix( work->clact );
		by = cmtx->y;
		work->joint_val = hy - by;
	}
	
	CutIn_EoaJikiMoveChange_Non( work->eoa_jikimove );
	FieldZoom_TypeChange( work->tcb_camera, ZOOMTYPE_BACK, 0, 12 );
	
	work->scale_val = 0x0100;
	work->angle = NUMFX32( 128 );
	work->angle_scale = 0;
	work->angle_scale_val = 0x0800;
	
	work->move_state = BIRD_MOVESTATE_RIDE_ON;
	work->seq_no++;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * 鳥動作　RIDE_ON 2
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int BirdMove_RideON_2( BIRD_WORK *work )
{
	VecFx32 mtx;
	CLACT_WORK_PTR act = work->clact;
	
	work->angle_scale += work->angle_scale_val;
	work->angle_scale_val += 0x1000;
	
	if( work->angle_scale_val > NUMFX32(16) ){
		work->angle_scale_val = NUMFX32( 16 );
	}
	
	work->offs.x = Cos360R( FX32NUM(work->angle) ) * FX32NUM( work->angle_scale );
	work->offs.y = Sin360R( 128 ) * FX32NUM( work->angle_scale );
	
	if( work->angle < NUMFX32(135) ){
		work->angle += 0x1000;
	}
	
	work->scale.x += work->scale_val;
	if( work->scale.x > 0x2000 ){ work->scale.x = 0x2000; }
	work->scale.y += work->scale_val;
	if( work->scale.y > 0x2000 ){ work->scale.y = 0x2000; }
	
	CLACT_SetScale( act, &work->scale );
	
	mtx.x = work->mtx.x + work->offs.x;
	mtx.y = work->mtx.y + work->offs.y;
	CLACT_SetMatrix( act, &mtx );
	
	{
		CLACT_WORK_PTR act_hero = work->head.cutin->clact_hero;
		const VecFx32 *cas_hero = CLACT_GetScale( act_hero );
		VecFx32 mtx_hero = mtx,scale = *cas_hero;
		
		work->joint_val -= 0x1000;
		mtx_hero.y += work->joint_val;
		CLACT_SetMatrix( act_hero, &mtx_hero );
		
		scale.x += 0x0100;
		if( scale.x > 0x2000 ){ scale.x = 0x2000; }
		scale.y += 0x0100;
		if( scale.y > 0x2000 ){ scale.y = 0x2000; }
		
		CLACT_SetScale( act_hero, &scale );
	}
	
	if( FX32NUM(mtx.y) >= 240 ){
		work->move_state = BIRD_MOVESTATE_END;
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 鳥動作　RIDE_ON 終了
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int BirdMove_RideON_End( BIRD_WORK *work )
{
	return( FALSE );
}

//--------------------------------------------------------------
//	鳥　BIRD_MOVETYPE_RIDE_ON
//--------------------------------------------------------------
static int (* const DATA_EoaBirdMoveTbl_RideON[])( BIRD_WORK * ) =
{
	BirdMove_RideON_0,
	BirdMove_RideON_1,
	BirdMove_RideON_2,
	BirdMove_RideON_End,
};

//==============================================================================
//	EOA 自機動作
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA 自機操作追加
 * @param
 * @retval
 */
//--------------------------------------------------------------
static EOA_PTR CutIn_EoaJikiMoveAdd( EOA_SYS_PTR eoa_sys, CLACT_WORK_PTR act )
{
	EOA_PTR eoa;
	JIKI_MOVE_H head;
	VecFx32 mtx = {0,0,0};
	
	head.clact = act;
	eoa = EOA_Add_NPP(
		eoa_sys, &DATA_EoaH_JikiMove, &mtx, 0, &head, TCBPRI_CUTIN_EOA_HERO );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA 自機動作終了チェック
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int CutIn_EoaJikiMoveEndCheck( EOA_PTR eoa )
{
	JIKI_MOVE_WORK *work = EOA_LocalWorkGet( eoa );
	return( work->end_flag );
}

//--------------------------------------------------------------
/**
 * 自機動作　何もなしに変更
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_EoaJikiMoveChange_Non( EOA_PTR eoa )
{
	JIKI_MOVE_WORK *work = EOA_LocalWorkGet( eoa );
	work->move_type = JIKI_MOVETYPE_NON;
}

//--------------------------------------------------------------
/**
 * 自機動作　ジャンプ動作に変更
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_EoaJikiMoveChange_Jump( EOA_PTR eoa )
{
	VecFx32 mtx;
	const VecFx32 *cmtx;
	JIKI_MOVE_WORK *work = EOA_LocalWorkGet( eoa );
	
	work->move_type = JIKI_MOVETYPE_JUMP;
	work->seq_no = 0;
	work->frame = 0;
	work->end_flag = 0;
	work->offs.x = 0; work->offs.y = 0; work->offs.z = 0;
	cmtx = CLACT_GetMatrix( work->clact );
	mtx = *cmtx;
	EOA_MatrixSet( eoa, &mtx );
	CLACT_AnmChg( work->clact, JIKIANMNO_JUMP_D );
}

//--------------------------------------------------------------
/**
 * 自機動作　着地動作に変更
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutIn_EoaJikiMoveChange_Landing( EOA_PTR eoa )
{
	VecFx32 mtx;
	JIKI_MOVE_WORK *work = EOA_LocalWorkGet( eoa );
	
	work->move_type = JIKI_MOVETYPE_LANDING;
	work->seq_no = 0;
	work->frame = 0;
	work->end_flag = 0;
	work->offs.x = 0; work->offs.y = 0; work->offs.z = 0;
	
	Cip_ClActMatrixGet( work->clact, &mtx );
	EOA_MatrixSet( eoa, &mtx );
	CLACT_AnmChg( work->clact, JIKIANMNO_JUMP_U );
}

//--------------------------------------------------------------
/**
 * EOA 自機動作　初期化
 * @param	eoa
 * @param	wk	EOA work
 * @retval
 */
//--------------------------------------------------------------
static int EoaJikiMove_Init( EOA_PTR eoa, void *wk )
{
	JIKI_MOVE_WORK *work = wk;
	const JIKI_MOVE_H *head = EOA_AddPtrGet( eoa );
	
	work->cut = head->cut;
	work->clact = head->clact;
	return( TRUE );
}

#define JIKI_MOVE_JUMP_FRAME (12)
#define JIKI_MOVE_LANDING_FRAME (4)

//------------------------------------------
//	ｼﾞｬﾝﾌﾟｵﾌｾｯﾄﾃｰﾌﾞﾙ
//------------------------------------------
static const fx32 JikiJumpOffsTbl[JIKI_MOVE_JUMP_FRAME] =	
{
	 NUMFX32(-12),NUMFX32(-16),NUMFX32(-20),NUMFX32(-24),
	 NUMFX32(-26),NUMFX32(-28),NUMFX32(-28),NUMFX32(-28),
	 NUMFX32(-26),NUMFX32(-24),NUMFX32(-22),NUMFX32(-20),
};

static const fx32 JikiLandingOffsTbl[JIKI_MOVE_LANDING_FRAME] =	
{
	 NUMFX32(-4),NUMFX32(-6),NUMFX32(-7),NUMFX32(-8),
};

//--------------------------------------------------------------
/**
 * 自機動作　ジャンプ
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void JikiMove_Jump( EOA_PTR eoa, JIKI_MOVE_WORK *work )
{
	VecFx32 mtx;
	
	switch( work->seq_no ){
	case 0:
		work->offs.y = JikiJumpOffsTbl[work->frame];
		EOA_MatrixGet( eoa, &mtx );
		mtx.y += work->offs.y;
		CLACT_SetMatrix( work->clact, &mtx );
		
		work->frame++;
		
		if( work->frame >= JIKI_MOVE_JUMP_FRAME ){
			work->frame = 0;
			work->end_flag = TRUE;
			work->seq_no++;
		}
	}
}

//--------------------------------------------------------------
/**
 * 自機動作　着地
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void JikiMove_Landing( EOA_PTR eoa, JIKI_MOVE_WORK *work )
{
	VecFx32 mtx;
	
	switch( work->seq_no ){
	case 0:
		work->offs.y = JikiLandingOffsTbl[work->frame];
		EOA_MatrixGet( eoa, &mtx );
		mtx.y += work->offs.y;
		CLACT_SetMatrix( work->clact, &mtx );
		
		work->frame++;
		if( work->frame >= JIKI_MOVE_LANDING_FRAME ){
			work->frame = 0;
			work->end_flag = TRUE;
			work->seq_no++;
		}
	}
}

//--------------------------------------------------------------
/**
 * EOA 自機　動作
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void EoaJikiMove_Move( EOA_PTR eoa, void *wk )
{
	JIKI_MOVE_WORK *work = wk;
	
	switch( work->move_type ){
	case JIKI_MOVETYPE_JUMP: JikiMove_Jump( eoa, work ); break;
	case JIKI_MOVETYPE_LANDING: JikiMove_Landing( eoa, work ); break;
	}
}

//--------------------------------------------------------------
///	EOA_H 自機動作
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_JikiMove =
{
	sizeof(JIKI_MOVE_WORK),
	EoaJikiMove_Init,
	EOA_DeleteProcDummy,
	EoaJikiMove_Move,
	EOA_DrawProcDummy,
};

//==============================================================================
//	EOA カメラ
//==============================================================================
typedef struct
{
	CUTIN_WORK *cut;
	FIELDSYS_WORK *fsys;
	PLAYER_STATE_PTR jiki;
	FIELD_OBJ_PTR fldobj;
}CAMERA_ADD_H;

typedef struct
{
	int move_type;
	int seq_no;
	int end_flag;
	VecFx32 save_mtx;
	VecFx32 mtx;
	fx32 oy;
	fx32 y_value;
	FIELD_OBJ_PTR fldobj;
	CUTIN_WORK *cut;
}CAMERA_WORK;

static const EOA_H_NPP DATA_EoaH_CameraMove;

//--------------------------------------------------------------
/**
 * EOA　カメラ移動追加
 * @param
 * @retval
 */
//--------------------------------------------------------------
static EOA_PTR CutIn_EoaCutInCameraMoveAdd(
		EOA_SYS_PTR es, FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki )
{
	VecFx32 mtx = {0,0,0};
	CAMERA_ADD_H head;
	EOA_PTR eoa;
	
	head.cut = NULL;
	head.fsys = fsys;
	head.jiki = jiki;
	head.fldobj = Player_FieldOBJGet( jiki );
	
	eoa = EOA_Add_NPP(
		es, &DATA_EoaH_CameraMove, &mtx, 0, &head, TCBPRI_CUTIN_EOA_HERO );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA カメラ 初期化
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int EoaCutInCameraMove_Init( EOA_PTR eoa, void *wk )
{
	CAMERA_WORK *work = wk;
	const CAMERA_ADD_H *head = EOA_AddPtrGet( eoa );
	
	work->fldobj = head->fldobj;
	work->cut = head->cut;
	
	FieldOBJ_VecPosGet( work->fldobj, &work->save_mtx );
	work->mtx = work->save_mtx;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA カメラ ズームインに
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void EoaCutInCameraMoveChange_ZoomIn( EOA_PTR eoa )
{
	CAMERA_WORK *work = EOA_LocalWorkGet( eoa );
	work->move_type = CAMERA_MOVETYPE_ZOOMIN;
	work->end_flag = FALSE;
}

//--------------------------------------------------------------
/**
 * EOA カメラ ズームアウトに
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void EoaCutInCameraMoveChange_ZoomOut( EOA_PTR eoa )
{
	CAMERA_WORK *work = EOA_LocalWorkGet( eoa );
	work->move_type = CAMERA_MOVETYPE_ZOOMOUT;
	work->end_flag = FALSE;
}

//--------------------------------------------------------------
/**
 * EOA カメラ 着地用ズームインに
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void EoaCutInCameraMoveChange_ZoomInLanding( EOA_PTR eoa )
{
	CAMERA_WORK *work = EOA_LocalWorkGet( eoa );
	work->move_type = CAMERA_MOVETYPE_ZOOMIN_LANDING;
	work->end_flag = FALSE;
}

//--------------------------------------------------------------
/**
 * EOA カメラ 着地用ズームアウトに
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void EoaCutInCameraMoveChange_ZoomOutLanding( EOA_PTR eoa )
{
	CAMERA_WORK *work = EOA_LocalWorkGet( eoa );
	work->move_type = CAMERA_MOVETYPE_ZOOMOUT_LANDING;
	work->end_flag = FALSE;
}

//--------------------------------------------------------------
/**
 * カメラ動作　ズーム
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutInCameraMove_ZoomIn( CAMERA_WORK *work )
{
	if( work->oy > NUMFX32(-48) ){
		work->oy -= 0x2000;
	}else{
		work->end_flag = TRUE;
	}
	
	{
		VecFx32 vec = work->mtx;
		vec.y += work->oy;
		FieldOBJ_VecPosSet( work->fldobj, &vec );
	}
}

//--------------------------------------------------------------
/**
 * カメラ動作　ズームアウト
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutInCameraMove_ZoomOut( CAMERA_WORK *work )
{
	work->oy += 0x4000;
	
	if( work->oy > 0 ){
		work->oy = 0;
	}
	
	if( work->oy == 0 ){
		work->end_flag = TRUE;
	}
	
	{
		VecFx32 vec = work->mtx;
		vec.y += work->oy;
		FieldOBJ_VecPosSet( work->fldobj, &vec );
	}
}

//--------------------------------------------------------------
/**
 * カメラ動作　着地用ズーム
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutInCameraMove_ZoomInLanding( CAMERA_WORK *work )
{
	if( work->oy > NUMFX32(-64) ){
		work->oy -= 0x1000;
	}else{
		work->end_flag = TRUE;
	}
	
	{
		VecFx32 vec = work->mtx;
		vec.y += work->oy;
		FieldOBJ_VecPosSet( work->fldobj, &vec );
	}
}

//--------------------------------------------------------------
/**
 * カメラ動作　着地用ズームアウト
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void CutInCameraMove_ZoomOutLanding( CAMERA_WORK *work )
{
	work->oy += 0x2000;
	
	if( work->oy > 0 ){
		work->oy = 0;
	}
	
	if( work->oy == 0 ){
		work->end_flag = TRUE;
	}
	
	{
		VecFx32 vec = work->mtx;
		vec.y += work->oy;
		FieldOBJ_VecPosSet( work->fldobj, &vec );
	}
}

//--------------------------------------------------------------
/**
 * EOA カメラ移動　動作
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void EoaCutInCameraMove_Move( EOA_PTR eoa, void *wk )
{
	CAMERA_WORK *work = wk;
	
	switch( work->move_type ){
	case CAMERA_MOVETYPE_ZOOMIN:
		CutInCameraMove_ZoomIn( work );
		break;
	case CAMERA_MOVETYPE_ZOOMOUT:
		CutInCameraMove_ZoomOut( work );
		break;
	case CAMERA_MOVETYPE_ZOOMIN_LANDING:
		CutInCameraMove_ZoomInLanding( work );
		break;
	case CAMERA_MOVETYPE_ZOOMOUT_LANDING:
		CutInCameraMove_ZoomOutLanding( work );
		break;
	}
}

//--------------------------------------------------------------
///	
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_CameraMove =
{
	sizeof(CAMERA_WORK),
	EoaCutInCameraMove_Init,
	EOA_DeleteProcDummy,
	EoaCutInCameraMove_Move,
	EOA_DrawProcDummy,
};

//==============================================================================
//	そらをとぶ　着陸
//==============================================================================
static void SkyL_UpdateTCB( TCB_PTR tcb, void *wk );
int (* const DATA_SkyLUpdateTbl[])( SKYL_WORK *skyl );

//--------------------------------------------------------------
/**
 * そらをとぶ　着陸
 * @param	fsys	FIELDSYS_WORK
 * @param	sex		自機性別 PM_FEMAL等
 * @retval
 */
//--------------------------------------------------------------
TCB_PTR FieldHidenSkyLanding_Init( FIELDSYS_WORK *fsys, int sex )
{
	SKYL_WORK *skyl = Cip_AllocMemory( HEAPID_FIELD, SKYL_WORK_SIZE );
	skyl->sex = sex;
	skyl->fsys = fsys;
	
	{
		TCB_PTR tcb = TCB_Add( SkyL_UpdateTCB, skyl, TCBPRI_CUTIN_UPDATE );
		return( tcb );
	}
}

//--------------------------------------------------------------
/**
 * そらをとぶ　着陸終了チェック
 * @param	tcb		FieldHidenSkyLanding_Init()戻り値
 * @retval	int		TRUE=終了 FALSE=まだ
 */
//--------------------------------------------------------------
int FieldHidenSkyLanding_EndCheck( TCB_PTR tcb )
{
	SKYL_WORK *skyl = TCB_GetWork( tcb );
	return( skyl->end_flag );
}

//--------------------------------------------------------------
/**
 * そらをとぶ　着陸終了
 * @param	tcb		FieldHidenSkyLanding_Init()戻り値
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldHidenSkyLanding_End( TCB_PTR tcb )
{
	SKYL_WORK *skyl = TCB_GetWork( tcb );
	sys_FreeMemoryEz( skyl );
	TCB_Delete( tcb );
}

//--------------------------------------------------------------
/**
 * そらをとぶ　着陸動作 tcb
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SkyL_UpdateTCB( TCB_PTR tcb, void *wk )
{
	int ret;
	SKYL_WORK *skyl = wk;
	
	while( DATA_SkyLUpdateTbl[skyl->seq_no](skyl) == TRUE ){};
	
	if( skyl->draw_on ){
		if( skyl->eoa_sys != NULL ){ EOA_SysDraw( skyl->eoa_sys ); }
		if( skyl->clactset.clact_set != NULL ){ CLACT_Draw( skyl->clactset.clact_set ); }
	}
}

//--------------------------------------------------------------
/**
 * 空を飛ぶ着陸　自機を消す
 * @param	skyl	SKYL_WORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int SkyL_PlayerVanish( SKYL_WORK *skyl ){
	Cip_PlayerVanishSet( skyl->fsys, TRUE );	//<<20060704 move
	skyl->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 空を飛ぶ着陸　初期化
 * @param	skyl	SKYL_WORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int SkyL_Init( SKYL_WORK *skyl )
{
	skyl->eoa_sys = EOA_SysInit( HEAPID_FIELD, 32 );
	
	Cip_ClActSetDataInit( &skyl->clactset, 32,
			SKYL_USE_CHAR_MAX, SKYL_USE_PLTT_MAX, SKYL_USE_CELL_MAX, SKYL_USE_ANM_MAX, 
			CUTIN_CAID_CHAR_MAX, CUTIN_CAID_PLTT_MAX, CUTIN_CAID_CELL_MAX, CUTIN_CAID_ANM_MAX );
	
	{
		ARCHANDLE *hand = Cip_ArcHandleOpen();
		
		Cip_ClActCharAdd( &skyl->clactset, hand,
			NARC_field_cutin_hidenbird_NCGR, CUTIN_CAID_CHAR_BIRD );
		Cip_ClActPlttAdd( &skyl->clactset, hand,
			NARC_field_cutin_dp_boy01_NCLR, CUTIN_CAID_PLTT_HERO_BIRD );
		Cip_ClActCellAdd( &skyl->clactset, hand,
			NARC_field_cutin_hidenbird_NCER, CUTIN_CAID_CELL_BIRD );
		
		Cip_ClActCharVramAreaSet( &skyl->clactset, CUTIN_CAID_CHAR_BIRD );
		Cip_ClActPlttVramAreaSet( &skyl->clactset, CUTIN_CAID_PLTT_HERO_BIRD );
		Cip_ClActCharResDelete( &skyl->clactset, CUTIN_CAID_CHAR_BIRD );
		Cip_ClActPlttResDelete( &skyl->clactset, CUTIN_CAID_PLTT_HERO_BIRD );
		
		if( skyl->sex == PM_MALE ){	//hero
			Cip_ClActCharAdd( &skyl->clactset, hand,
				NARC_field_cutin_hidenhero_NCGR, CUTIN_CAID_CHAR_HERO );
			Cip_ClActCellAdd( &skyl->clactset, hand,
				NARC_field_cutin_hidenhero_NCER, CUTIN_CAID_CELL_HERO );
			Cip_ClActAnmAdd( &skyl->clactset, hand,
				NARC_field_cutin_hidenhero_NANR, CUTIN_CAID_ANM_HERO );
			
			Cip_ClActCharVramAreaSet( &skyl->clactset, CUTIN_CAID_CHAR_HERO );
			Cip_ClActCharResDelete( &skyl->clactset, CUTIN_CAID_CHAR_HERO );
		}else{
			Cip_ClActCharAdd( &skyl->clactset, hand,
				NARC_field_cutin_hidenheroine_NCGR, CUTIN_CAID_CHAR_HERO );
			Cip_ClActPlttAdd( &skyl->clactset, hand,
				NARC_field_cutin_heroine_NCLR, CUTIN_CAID_PLTT_HEROINE );
			Cip_ClActCellAdd( &skyl->clactset, hand,
				NARC_field_cutin_hidenheroine_NCER, CUTIN_CAID_CELL_HERO );
			Cip_ClActAnmAdd( &skyl->clactset, hand,
				NARC_field_cutin_hidenheroine_NANR, CUTIN_CAID_ANM_HERO );
			
			Cip_ClActCharVramAreaSet( &skyl->clactset, CUTIN_CAID_CHAR_HERO );
			Cip_ClActPlttVramAreaSet( &skyl->clactset, CUTIN_CAID_PLTT_HEROINE );
			Cip_ClActCharResDelete( &skyl->clactset, CUTIN_CAID_CHAR_HERO );
			Cip_ClActPlttResDelete( &skyl->clactset, CUTIN_CAID_PLTT_HEROINE );
		}
		
		ArchiveDataHandleClose( hand );
	}

	skyl->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 空を飛ぶ着陸　アクター初期化
 * @param	skyl	SKYL_WORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int SkyL_ActorInit( SKYL_WORK *skyl )
{
	skyl->clact_hero = Cip_ClActAdd_Hero( &skyl->clactset, skyl->sex );
	CLACT_SetDrawFlag( skyl->clact_hero, 1 );
	
	skyl->eoa_bird = Bird_Init( skyl->fsys, skyl->eoa_sys, &skyl->clactset, skyl->clact_hero );
	Bird_MoveChange_LandingStart( skyl->eoa_bird );
	
	skyl->seq_no++;
	skyl->draw_on = TRUE;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 空を飛ぶ着陸　鳥着陸終了待ち
 * @param	skyl	SKYL_WORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int SkyL_BirdLandingStartWait( SKYL_WORK *skyl )
{
	if( Bird_MoveStateGet(skyl->eoa_bird) != BIRD_MOVESTATE_END ){
		return( FALSE );
	}
	
	Bird_Delete( skyl->eoa_bird );
	skyl->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 空を飛ぶ着陸　終了 0
 * @param	skyl	SKYL_WORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int SkyL_End0( SKYL_WORK *skyl )
{
	EOA_SysDeleteAll( skyl->eoa_sys );
	Cip_ClActSetDataDelete( &skyl->clactset );
	skyl->draw_on = FALSE;
	skyl->end_flag = TRUE;
	skyl->seq_no++;
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 空を飛ぶ着陸　終了
 * @param	skyl	SKYL_WORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int SkyL_End1( SKYL_WORK *skyl )
{
	return( FALSE );
}

//--------------------------------------------------------------
//	空を飛ぶ着地動作テーブル
//--------------------------------------------------------------
static int (* const DATA_SkyLUpdateTbl[])( SKYL_WORK *skyl ) =
{
	SkyL_PlayerVanish,
	SkyL_Init,
	SkyL_ActorInit,
	SkyL_BirdLandingStartWait,
	
	SkyL_End0,
	SkyL_End1,
};

//==============================================================================
//	パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * メモリ確保
 * @param	size	確保するサイズ
 * @retval	void*	確保したメモリ
 */
//--------------------------------------------------------------
static void * Cip_AllocMemory( u32 heap, int size )
{
	void *mem = sys_AllocMemoryLo( heap, size );
	GF_ASSERT( mem != NULL && "cutin_AllocMemory()メモリ確保失敗" );
	memset( mem, 0, size );
	return( mem );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ 自機表示、非表示
 * @param	cut		CUTIN_WORK
 * @retval	nothing
 */
//--------------------------------------------------------------
static void CutIn_PlayerVanishSet( CUTIN_WORK *cut, int flag )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( cut->fsys->player );
	FieldOBJ_MovePauseClear( fldobj );
	FieldOBJ_StatusBitSet_Vanish( fldobj, flag );
}

//==============================================================================
//	EOA OAM自機表示監視
//==============================================================================
//--------------------------------------------------------------
//
//--------------------------------------------------------------
typedef struct
{
	CLACT_WORK_PTR clact;
	CUTIN_WORK *cutin;
}HEROWINVANISH;

//--------------------------------------------------------------
/**
 * @param
 * @retval
 */
//--------------------------------------------------------------
static int eoaHeroVanishWin_Init( EOA_PTR eoa, void *wk )
{
	const HEROWINVANISH *head = EOA_AddPtrGet( eoa );
	HEROWINVANISH *work = wk;
	*work = *head;
	return( TRUE );
}

static void eoaHeroVanishWin_Move( EOA_PTR eoa, void *wk )
{
	fx32 y,w0,w1;
	const VecFx32 *vec;
	HEROWINVANISH *work = wk;
	
	vec = CLACT_GetMatrix( work->clact );
	
	y = vec->y;
	w0 = work->cutin->win_y0;
	w1 = work->cutin->win_y1;
	
	if( work->cutin->winvanishoff_hero_flag == FALSE ){
		if( (y - NUMFX32(8)) >= w0 && (y + NUMFX32(8)) <= w1 ){
			CLACT_SetDrawFlag( work->clact, 1 );
		}else{
			CLACT_SetDrawFlag( work->clact, 0 );
		}
	}else{
		CLACT_SetDrawFlag( work->clact, 1 );
	}
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaHeroWinVanish =
{
	sizeof(HEROWINVANISH),
	eoaHeroVanishWin_Init,
	EOA_DeleteProcDummy,
	eoaHeroVanishWin_Move,
	EOA_DrawProcDummy,
};

//--------------------------------------------------------------
/**
 *
 * @param
 * @retval
 *
 */
//--------------------------------------------------------------
static void Cip_HeroWinVanishSet( CUTIN_WORK *cutin )
{
	VecFx32 mtx = {0,0,0};
	HEROWINVANISH add;
	add.clact = cutin->clact_hero;
	add.cutin = cutin;
	
	cutin->eoa_herowinvanish =
		EOA_Add_NPP( cutin->cutin_eoa_sys, &DATA_EoaHeroWinVanish,
				&mtx, 0, &add, TCBPRI_CUTIN_EOA_HERO_WIN_VANISH );
}

//--------------------------------------------------------------
/**
 *
 * @param
 * @retval
 *
 */
//--------------------------------------------------------------
static void Cip_HeroWinVanishDel( CUTIN_WORK *cutin )
{
	if( cutin->eoa_herowinvanish != NULL ){
		EOA_Delete( cutin->eoa_herowinvanish );
		cutin->eoa_herowinvanish = NULL;
	}
}

//==============================================================================
//	カットイン　ウィンドウ
//==============================================================================

//==============================================================================
//	data	セルアクター
//==============================================================================
//--------------------------------------------------------------
///	キャラ
//--------------------------------------------------------------
static const NARC_ID DATA_NArcID_AlwaysChar[CUTIN_CAUSE_CHAR_ALWAYS_MAX] =
{
	{ CUTIN_CAID_CHAR_LIGHT, NARC_field_cutin_hidenlight_NCGR },
};

//--------------------------------------------------------------
///	パレット
//--------------------------------------------------------------
static const NARC_ID DATA_NArcID_AlwaysPltt[CUTIN_CAUSE_PLTT_ALWAYS_MAX] =
{
	{ CUTIN_CAID_PLTT_HERO_BIRD, NARC_field_cutin_dp_boy01_NCLR },
};

//--------------------------------------------------------------
///	セル
//--------------------------------------------------------------
static const NARC_ID DATA_NArcID_AlwaysCell[CUTIN_CAUSE_CELL_ALWAYS_MAX] =
{
	{ CUTIN_CAID_CELL_LIGHT, NARC_field_cutin_hidenlight_NCER },
};

//--------------------------------------------------------------
///	アニメ
//--------------------------------------------------------------
static const NARC_ID DATA_NArcID_AlwaysAnime[CUTIN_CAUSE_ANM_ALWAYS_MAX] =
{
	{ CUTIN_CAID_ANM_LIGHT, NARC_field_cutin_hidenlight_NANR },
};

//==============================================================================
//	イベント呼び出し
//==============================================================================

#if 0
//--------------------------------------------------------------
/**
 * 秘伝技そらを飛ぶカットイン→マップ遷移イベント呼び出し
 * @param	fsys		FIELDSYS_WORK *
 * @param	param		表示するPOKEMON_PARAM *
 * @param	zone_id		遷移するゾーンID
 * @param	map_gx		遷移先出現位置グリッドX座標
 * @param	map_gz		遷移先出現位置グリッドZ座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void * EventSet_CutInSkyMapChange( FIELDSYS_WORK *fsys,
		POKEMON_PARAM *param,
		u16 zone_id, s16 map_gx, s16 map_gz )
{
	SORATOBI_WORK *work = Cip_AllocMemory( HEAPID_WORLD, SORATOBI_WORK_SIZE );
	
	work->fsys = fsys;
	work->poke_param = param;
	work->zone_id = zone_id;
	work->map_gx = map_gx;
	work->map_gz = map_gz;
	
//	FieldEvent_Set( fsys, GMEVENT_CutInSkyMapChange, work );
	return work;
}

//--------------------------------------------------------------
/**
 * 空を飛ぶカットイン→マップ遷移
 * @param	event	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=終了
 */
//--------------------------------------------------------------
BOOL GMEVENT_CutInSkyMapChange( GMEVENT_CONTROL *event )
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	SORATOBI_WORK *work = FieldEvent_GetSpecialWork( event );
	
	switch( work->seq_no ){
	case 0:
		work->tcb_cutin = FieldCutIn_Init(
			work->fsys, CUTIN_TYPE_SKY,
			work->poke_param, Player_SexGet(work->fsys->player) );
		
		work->seq_no++;
		break;
	case 1:
		if( FieldCutIn_EndCheck(work->tcb_cutin) == FALSE ){
			break;
		}
		
		FieldCutIn_End( work->tcb_cutin );
		
		EventChange_MapChangeBySky( event,
				work->zone_id, DOOR_ID_JUMP_CODE,
				work->map_gx, work->map_gz, DIR_DOWN );
		
		sys_FreeMemoryEz( work );
		return( FALSE );
	}
	
	return( FALSE );
}
#endif
