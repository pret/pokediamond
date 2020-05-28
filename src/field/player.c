//******************************************************************************
/**
 *
 * @file	player.c
 * @brief	自機
 * @author	kagaya
 * @data	05.08.03
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"
#include "player.h"
#include "div_map.h"
#include "field_effect.h"

#include "mapdefine.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
///	動作ビット
//--------------------------------------------------------------
#define JIKI_MOVE_BIT_NON				(0)			///<何も無し
#define JIKI_MOVE_BIT_FORCE 			(1<<0)		///<強制移動中
#define JIKI_MOVE_BIT_UNDER_OFF			(1<<1)		///<足元無効化
#define JIKI_MOVE_BIT_CYCLE_BRAKE		(1<<2)		///<自転車ブレーキ
#define JIKI_MOVE_BIT_CYCLING_ROAD		(1<<3)		///<自転車サイクリングロード
#define JIKI_MOVE_BIT_DEEPSWAMP_OFF		(1<<4)		///<沼嵌り無効
#define JIKI_MOVE_BIT_SAND_FLOAT		(1<<5)		///<流砂で流れる
#define JIKI_MOVE_BIT_STEP				(1<<6)		///<一歩移動
#define JIKI_MOVE_BIT_FORCE_SAVE_SPEED	(1<<7)		///<強制移動中　移動後の速度クリア無し

//--------------------------------------------------------------
///	フィールドOBJ初期化時に指定するステータスビット
//--------------------------------------------------------------
///初期化、ロード時に立てるビット
#define JIKI_FLDOBJ_INIT_STA_BIT_ON \
(FLDOBJ_STA_BIT_ZONE_DEL_NOT|FLDOBJ_STA_BIT_HEIGHT_VANISH_OFF)
///初期化、ロード時に下ろすビット
#define JIKI_FLDOBJ_INIT_STA_BIT_OFF \
(FLDOBJ_STA_BIT_PAUSE_DIR|FLDOBJ_STA_BIT_PAUSE_ANM)

//==============================================================================
//	struct
//==============================================================================
//--------------------------------------------------------------
//	PLAYER_STATE構造体
//--------------------------------------------------------------
struct _TAG_PLAYER_STATE
{
	u32 move_bit;											///<動作フラグ
	u32 request_bit;										///<リクエスト
	u32 set_ac;												///<セットアニメーションコード
	u32 se_walk_lr;											///<足音左右
	int move_value;											///<動作状態 OBJ_MOVE_VALUE_STOP等
	int move_state;											///<動作状況 OBJ_MOVE_STATE_OFF等
	int form;												///<形態 HERO_FORM_NORMAL等
	int sex;												///<性別 PM_MALE等
	int speed;												///<自機スピード
	int input_key_dir_x;									///<キー入力方向
	int input_key_dir_z;									///<キー入力方向
	FIELD_OBJ_PTR fldobj;									///<自機用フィールドOBJ *
	EOA_PTR joint_eoa;										///<接続EOA
	PLAYER_SAVE_DATA *savedata;
	const PLAYER_SAVE_DATA *save;							///<セーブデータ参照*
}PLAYER_STATE;

#define PLAYER_STATE_SIZE (sizeof(PLAYER_STATE))

//==============================================================================
//	static
//==============================================================================
static PLAYER_STATE_PTR Jiki_WorkAlloc( void );
static void Jiki_WorkInit( PLAYER_STATE_PTR jiki, int form, int sex, PLAYER_SAVE_DATA *save );
static void Jiki_FieldOBJAdd(
		PLAYER_STATE_PTR jiki, CONST_FIELD_OBJ_SYS_PTR fos, int obj, int dir, int x, int z );
static FIELD_OBJ_PTR Jiki_FieldOBJSearch( CONST_FIELD_OBJ_SYS_PTR fos );

static void Jiki_MoveBitSet( PLAYER_STATE_PTR jiki, u32 bit );
static void Jiki_MoveBitON( PLAYER_STATE_PTR jiki, u32 bit );
static void Jiki_MoveBitOFF( PLAYER_STATE_PTR jiki, u32 bit );
static u32 Jiki_MoveBitCheck( PLAYER_STATE_PTR jiki, u32 bit );
static void Jiki_SaveDataPtrSet( PLAYER_STATE_PTR jiki, PLAYER_SAVE_DATA *save );

//==============================================================================
//	debug
//==============================================================================

//==============================================================================
//	自機
//==============================================================================
//--------------------------------------------------------------
/**
 * 自機初期化
 * @param	fos			CONST_FIELD_OBJ_SYS_PTR
 * @param	x			追加するグリッドX座標
 * @param	z			追加するグリッドY座標
 * @param	dir			初期方向 DIR_UP等
 * @param	form		自機形態　HERO_FORM_NORMAL等
 * @param	sex			性別　PM_MALE等
 * @param	save		PLAYER_SAVE_DATA * NULL=参照しない
 * @retval	PLAYER_STATE_PTR	追加されたPLAYER_STATE_PTR
 */
//--------------------------------------------------------------
PLAYER_STATE_PTR Player_Init( CONST_FIELD_OBJ_SYS_PTR fos,
		int x, int z, int dir, int form, int sex, PLAYER_SAVE_DATA *save )
{
	PLAYER_STATE_PTR jiki;
	
	jiki = Jiki_WorkAlloc();
	Jiki_WorkInit( jiki, form, sex, save );
	
	{
		int code = Player_FormSexOBJCodeGet( form, sex );
		Jiki_FieldOBJAdd( jiki, fos, code, dir, x, z );
	}
	
#ifdef PLAYER_DEBUG
	DEBUG_Player_Init( jiki );
#endif
	
	return( jiki );
}

//--------------------------------------------------------------
/**
 * 自機　フィールドOBJを使用して復元
 * @param	fos			CONST_FIELD_OBJ_SYS_PTR
 * @param	save		PLAYER_SAVE_DATA *
 * @retval	PLAYER_STATE_PTR	追加されたPLAYER_STATE_PTR
 */
//--------------------------------------------------------------
PLAYER_STATE_PTR Player_FieldOBJUseRecover(
		CONST_FIELD_OBJ_SYS_PTR fos, PLAYER_SAVE_DATA *save, int sex )
{
	int form;
	PLAYER_STATE_PTR jiki;
	FIELD_OBJ_PTR fldobj;
	
	jiki = Jiki_WorkAlloc();
	form = Player_SaveDataFormGet( save );
	Jiki_WorkInit( jiki, form, sex, save );
	
	fldobj = Jiki_FieldOBJSearch( fos );
	FieldOBJ_OBJCodeSet( fldobj, Player_FormSexOBJCodeGet(form,sex) );
	FieldOBJ_StatusBit_ON( fldobj, JIKI_FLDOBJ_INIT_STA_BIT_ON );
	FieldOBJ_StatusBit_OFF( fldobj, JIKI_FLDOBJ_INIT_STA_BIT_OFF );
	FieldOBJ_StatusBitSet_HeightExpand( fldobj, TRUE );
	Player_FieldOBJSet( jiki, fldobj );
	
#ifdef PLAYER_DEBUG
	DEBUG_Player_Init( jiki );
#endif
	
	return( jiki );
}

//--------------------------------------------------------------
/**
 * 自機　描画初期化
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_DrawInit( PLAYER_STATE_PTR jiki )
{
	int code,ret;
	FIELD_OBJ_PTR fldobj;
	CONST_FIELD_OBJ_SYS_PTR fos;
	
	fldobj = Player_FieldOBJGet( jiki );
	GF_ASSERT( fldobj != NULL && "Player_DrawInit() 自機フィールドOBJがありません" );
	
	fos = FieldOBJ_FieldOBJSysGet( fldobj );
	
//	code = FieldOBJ_OBJCodeGet( fldobj );
//	FieldOBJ_BlActResmRegularAdd_Tex( fos, code );
//	ret = FieldOBJ_BlActOBJCodeAnmIDGet( code );
//	FieldOBJ_BlActResmRegularAdd_Anm( fos, ret );
	
	FE_PlayerExitArrow_Add( jiki );
	
	if( Player_FormGet(jiki) == HERO_FORM_SWIM ){
		int gx = Player_NowGPosXGet( jiki );
		int gz = Player_NowGPosZGet( jiki );
		int dir = Player_DirGet( jiki );
		EOA_PTR eoa =  FE_FldOBJNamiPokeSet( fldobj, gx, gz, dir, TRUE );
		Player_JointEoaSet( jiki, eoa );
	}
}

//--------------------------------------------------------------
/**
 * 自機削除
 * @param	player			開放するPLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_Delete( PLAYER_STATE_PTR jiki )
{
	sys_FreeMemoryEz( jiki );
}

//--------------------------------------------------------------
/**
 * 自機すべて削除
 * @param	player			開放するPLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_DeleteAll( PLAYER_STATE_PTR jiki )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	FieldOBJ_Delete( fldobj );
	Player_Delete( jiki );
}

//--------------------------------------------------------------
/**
 * 自機用ワークメモリ確保
 * @param	nothing
 * @retval	PLAYER_STATE_PTR	確保したPLAYER_STATE_PTR
 */
//--------------------------------------------------------------
static PLAYER_STATE_PTR Jiki_WorkAlloc( void )
{
	PLAYER_STATE_PTR jiki;
	
	jiki = sys_AllocMemory( HEAPID_WORLD, PLAYER_STATE_SIZE );
	GF_ASSERT( jiki != NULL && "player init work alloc error" );
	memset( jiki, 0, PLAYER_STATE_SIZE );
	
	return( jiki );
}

//--------------------------------------------------------------
/**
 * 自機ワーク初期化
 * @param	jiki	PLAYER_STATE_PTR
 * @param	form	HERO_FORM_NORMAL等
 * @param	sex		PM_MALE等
 * @param	save	PLAYER_SAVE_DATA *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_WorkInit( PLAYER_STATE_PTR jiki, int form, int sex, PLAYER_SAVE_DATA *save )
{
	Jiki_SaveDataPtrSet( jiki, save );
	
	Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_STOP );
	Player_MoveStateSet( jiki, OBJ_MOVE_STATE_OFF );
	Player_FormSet( jiki, form );
	Player_SexSet( jiki, sex );
	Player_RequestBit_Set( jiki, HERO_REQBIT_NON );
	Player_MoveSpeedClear( jiki );
	Player_InputKeyDirXSet( jiki, DIR_NOT );
	Player_InputKeyDirZSet( jiki, DIR_NOT );
	Player_AcmdCodeSet( jiki, ACMD_NOT );
	
	Player_MoveBitSet_UnderOFF( jiki, TRUE );
	Player_MoveBitSet_DeepSwampOFF( jiki, TRUE );
}

//--------------------------------------------------------------
/**
 * 自機フィールドOBJ追加
 * @param	jiki		PLAYER_STATE_PTR
 * @param	fos			FIELD_OBJ_SYS_PTR
 * @param	obj			OBJコード。HERO等
 * @param	dir			初期方向。DIR_UP等
 * @param	x			グリッドX座標
 * @param	y			グリッドY座標
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_FieldOBJAdd(
		PLAYER_STATE_PTR jiki, CONST_FIELD_OBJ_SYS_PTR fos, int obj, int dir, int x, int z )
{
	FIELD_OBJ_PTR fldobj;
	
	fldobj = FieldOBJ_AddHMake( fos, x, z, dir, obj, MV_PLAYER, ZONE_ID_NOTHING );
	GF_ASSERT( fldobj != NULL && "player init obj add error" );
	
	FieldOBJ_OBJIDSet( fldobj, FLDOBJ_ID_PLAYER );
	FieldOBJ_EventTypeSet( fldobj, 0 );
	FieldOBJ_EventFlagSet( fldobj, 0 );
	FieldOBJ_EventIDSet( fldobj, 0 );
	FieldOBJ_ParamSet( fldobj, 0, FLDOBJ_PARAM_0 );
	FieldOBJ_ParamSet( fldobj, 0, FLDOBJ_PARAM_1 );
	FieldOBJ_ParamSet( fldobj, 0, FLDOBJ_PARAM_2 );
	FieldOBJ_MoveLimitXSet( fldobj, MOVE_LIMIT_NOT );
	FieldOBJ_MoveLimitZSet( fldobj, MOVE_LIMIT_NOT );
	FieldOBJ_StatusBit_ON( fldobj, JIKI_FLDOBJ_INIT_STA_BIT_ON );
	FieldOBJ_StatusBit_OFF( fldobj, JIKI_FLDOBJ_INIT_STA_BIT_OFF );
	FieldOBJ_StatusBitSet_HeightExpand( fldobj, TRUE );
	
	Player_FieldOBJSet( jiki, fldobj );
}

//--------------------------------------------------------------
/**
 * フィールドOBJから自機フィールドOBJ検索　外部
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	FIELD_OBJ_PTR	自機フィールドOBJ
 */
//--------------------------------------------------------------
FIELD_OBJ_PTR Player_FieldOBJSearch( CONST_FIELD_OBJ_SYS_PTR fos )
{
	int i = 0;
	FIELD_OBJ_PTR fldobj = NULL;
	
	while( FieldOBJSys_FieldOBJSearch(fos,&fldobj,&i,FLDOBJ_STA_BIT_USE) ){
		if( FieldOBJ_MoveCodeGet(fldobj) == MV_PLAYER ){
			break;
		}
	}
	
	return( fldobj );
}

//--------------------------------------------------------------
/**
 * フィールドOBJから自機フィールドOBJ検索
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	FIELD_OBJ_PTR	自機フィールドOBJ
 */
//--------------------------------------------------------------
static FIELD_OBJ_PTR Jiki_FieldOBJSearch( CONST_FIELD_OBJ_SYS_PTR fos )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJSearch( fos );
	GF_ASSERT( fldobj != NULL && "Jiki_FieldOBJSearch()自機フィールドOBJが無い" );
	return( fldobj );
}

//==============================================================================
//	PLAYER_STATE　参照
//==============================================================================
//--------------------------------------------------------------
/**
 * 自機の向きを取得
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		DIR_UP等
 */
//--------------------------------------------------------------
int Player_DirGet( const PLAYER_STATE_PTR jiki )
{
	return( FieldOBJ_DirDispGet(Player_FieldOBJGet(jiki)) );
}

//--------------------------------------------------------------
/**
 * 自機の向きをセット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_DirSet( PLAYER_STATE_PTR jiki, int dir )
{
	FieldOBJ_DirDispCheckSet( Player_FieldOBJGet(jiki), dir );
}

//--------------------------------------------------------------
/**
 * 自機の移動方向を取得
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		DIR_UP等
 */
//--------------------------------------------------------------
int Player_DirMoveGet( const PLAYER_STATE_PTR jiki )
{
	return( FieldOBJ_DirMoveGet(Player_FieldOBJGet(jiki)) );
}

//--------------------------------------------------------------
/**
 * 自機現在グリッドX座標を取得
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		グリッドX座標
 */
//--------------------------------------------------------------
int Player_NowGPosXGet( const PLAYER_STATE_PTR jiki )
{
	return( FieldOBJ_NowPosGX_Get(Player_FieldOBJGet(jiki)) );
}

//--------------------------------------------------------------
/**
 * 自機現在グリッドZ座標を取得
 * @param	jiki		PLAYER_STATE_PTR
 * @retval	int		グリッドZ座標
 */
//--------------------------------------------------------------
int Player_NowGPosZGet( const PLAYER_STATE_PTR jiki )
{
	return( FieldOBJ_NowPosGZ_Get(Player_FieldOBJGet(jiki)) );
}

//--------------------------------------------------------------
/**
 * 自機過去グリッドX座標を取得
 * @param	jiki		PLAYER_STATE_PTR
 * @retval	int		グリッドX座標
 */
//--------------------------------------------------------------
int Player_OldGPosXGet( const PLAYER_STATE_PTR jiki )
{
	return( FieldOBJ_OldPosGX_Get(Player_FieldOBJGet(jiki)) );
}

//--------------------------------------------------------------
/**
 * 自機過去グリッドZ座標を取得
 * @param	jiki		PLAYER_STATE_PTR
 * @retval	int		グリッドZ座標
 */
//--------------------------------------------------------------
int Player_OldGPosZGet( const PLAYER_STATE_PTR jiki )
{
	return( FieldOBJ_OldPosGZ_Get(Player_FieldOBJGet(jiki)) );
}

//--------------------------------------------------------------
/**
 * 自機3D座標を取得
 * @param	jiki	PLAYER_STATE_PTR
 * @param	vec		座標格納先
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_VecPosGet( const PLAYER_STATE_PTR jiki, VecFx32 *vec )
{
	FieldOBJ_VecPosGet( Player_FieldOBJGet(jiki), vec );
}

//--------------------------------------------------------------
/**
 * 自機3D座標ポインタを取得
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	VecFx32	自機座標*
 */
//--------------------------------------------------------------
const VecFx32 * Player_VecPosPtrGet( const PLAYER_STATE_PTR jiki )
{
	return( FieldOBJ_VecPosPtrGet(Player_ConstFieldOBJGet(jiki)) );
}

//--------------------------------------------------------------
/**
 * 自機3Dオフセット座標ポインタを取得
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	VecFx32	自機座標*
 */
//--------------------------------------------------------------
VecFx32 * Player_VecDrawOffsPtrGet( PLAYER_STATE_PTR jiki )
{
	return( FieldOBJ_VecDrawOffsPtrGet(Player_FieldOBJGet(jiki)) );
}

//--------------------------------------------------------------
/**
 * 自機動作状態をセット
 * @param	jiki		PLAYER_STATE_PTR
 * @param	val		OBJ_MOVE_VALUE_STOP等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveValueSet( PLAYER_STATE_PTR jiki, int val )
{
	jiki->move_value = val;
}

//--------------------------------------------------------------
/**
 * 自機動作状態を取得
 * @param	jiki		PLAYER_STATE_PTR
 * @retval	int		OBJ_MOVE_VALUE_STOP等
 */
//--------------------------------------------------------------
int Player_MoveValueGet( const PLAYER_STATE_PTR jiki )
{
	return( jiki->move_value );
}

//--------------------------------------------------------------
/**
 * 自機動作状況をセット
 * @param	jiki		PLAYER_STATE_PTR
 * @param	state OBJ_MOVE_STATE_OFF等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveStateSet( PLAYER_STATE_PTR jiki, int state )
{
	jiki->move_state = state;
}

//--------------------------------------------------------------
/**
 * 自機動作状況を取得
 * @param	jiki		PLAYER_STATE_PTR
 * @retval	int		OBJ_MOVE_STATE_OFF等
 */
//--------------------------------------------------------------
int Player_MoveStateGet( const PLAYER_STATE_PTR jiki )
{
	return( jiki->move_state );
}

//--------------------------------------------------------------
/**
 * 自機の表示ON,OFFを指定
 * @param	jiki		PLAYER_STATE_PTR
 * @param	flag		TRUE=表示、FALSE=非表示
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_DispON_OFF_Set( PLAYER_STATE_PTR jiki, int flag )
{
	FIELD_OBJ_PTR fldobj;
	
	fldobj = Player_FieldOBJGet( jiki );
	
	if( flag == TRUE ){
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_VANISH );
	}else{
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_VANISH );
	}
}

//--------------------------------------------------------------
/**
 * 自機の表示ON,OFFフラグを取得
 * @param	jiki		PLAYER_STATE_PTR
 * @retval	int			TRUE=表示、FALSE=非表示
 */
//--------------------------------------------------------------
int Player_DispON_OFF_Get( const PLAYER_STATE_PTR jiki )
{
	int ret;
	
	ret = FieldOBJ_StatusBit_CheckEasy( Player_FieldOBJGet(jiki), FLDOBJ_STA_BIT_VANISH );
	
	if( ret == TRUE ){
		return( FALSE );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * 自機のフィールドOBJ *セット
 * @param	jiki			PLAYER_STATE_PTR
 * @param	fldobj			FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_FieldOBJSet( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	jiki->fldobj = fldobj;
}

//--------------------------------------------------------------
/**
 * 自機のフィールドOBJ *を取得
 * @param	jiki			PLAYER_STATE_PTR
 * @retval	FIELD_OBJ_PTR 	FIELD_OBJ_PTR
 */
//--------------------------------------------------------------
FIELD_OBJ_PTR Player_FieldOBJGet( PLAYER_STATE_PTR jiki )
{
	return( jiki->fldobj );
}

//--------------------------------------------------------------
/**
 * 自機のフィールドOBJ *を取得 const
 * @param	jiki			PLAYER_STATE_PTR
 * @retval	FIELD_OBJ_PTR 	FIELD_OBJ_PTR
 */
//--------------------------------------------------------------
CONST_FIELD_OBJ_PTR Player_ConstFieldOBJGet( const PLAYER_STATE_PTR jiki )
{
	return( jiki->fldobj );
}

//--------------------------------------------------------------
/**
 * 自機の形態セット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	form	HERO_FORM_NORMAL等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_FormSet( PLAYER_STATE_PTR jiki, int form )
{
	GF_ASSERT( form < HERO_FORM_MAX && "Player_FormSet() form error" );
	jiki->form = form;
	Player_SaveDataGetFormSet( jiki, form );
}

//--------------------------------------------------------------
/**
 * 自機の形態を取得
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		HERO_FORM_NORMAL等
 */
//--------------------------------------------------------------
int Player_FormGet( PLAYER_STATE_PTR jiki )
{
	GF_ASSERT( jiki != NULL && "Player_FormGet()自機初期化が行われていない" );
	return( jiki->form );
}

//--------------------------------------------------------------
/**
 * 自機リクエストビットON
 * @param	jiki	PLAYER_STATE_PTR
 * @param	bit		HERO_REQBIT_NORMAL等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_RequestBit_ON( PLAYER_STATE_PTR jiki, u32 bit )
{
	jiki->request_bit |= bit;
}

//--------------------------------------------------------------
/**
 * 自機リクエストビットセット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	bit		HERO_REQBIT_NORMAL等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_RequestBit_Set( PLAYER_STATE_PTR jiki, u32 bit )
{
	jiki->request_bit = bit;
}

//--------------------------------------------------------------
/**
 * 自機リクエストビット取得
 * @param	jiki	PLAYER_STATE_PTR
 * @param	bit		HERO_REQBIT_NORMAL等
 * @retval	nothing
 */
//--------------------------------------------------------------
u32 Player_RequestBit_Get( PLAYER_STATE_PTR jiki )
{
	return( jiki->request_bit );
}

//--------------------------------------------------------------
/**
 * 性別セット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	sex		PM_MALE等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_SexSet( PLAYER_STATE_PTR jiki, int sex )
{
	jiki->sex = sex;
}

//--------------------------------------------------------------
/**
 * 性別取得
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		PM_MALE等
 */
//--------------------------------------------------------------
int Player_SexGet( PLAYER_STATE_PTR jiki )
{
	return( jiki->sex );
}

//--------------------------------------------------------------
/**
 * 自機動作ビット　セット
 * @param	jiki	PLYAER_STATE_PTR
 * @param	bit		セットする値 JIKI_MOVE_BIT_NON等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveBitSet( PLAYER_STATE_PTR jiki, u32 bit )
{
	jiki->move_bit = bit;
}

//--------------------------------------------------------------
/**
 * 自機動作ビットをON
 * @param	jiki	PLAYER_STATE_PTR
 * @param	bit		JIKI_MOVE_BIT_FORCE等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveBitON( PLAYER_STATE_PTR jiki, u32 bit )
{
	jiki->move_bit |= bit;
}

//--------------------------------------------------------------
/**
 * 自機動作ビットをOFF
 * @param	jiki	PLAYER_STATE_PTR
 * @param	bit		JIKI_MOVE_BIT_FORCE等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveBitOFF( PLAYER_STATE_PTR jiki, u32 bit )
{
	jiki->move_bit &= ~bit;
}

//--------------------------------------------------------------
/**
 * 自機動作ビットのチェック
 * @param	jiki	PLAYER_STATE_PTR
 * @param	bit		JIKI_MOVE_BIT_FORCE等
 * @retval	u32		動作ビット&bit
 */
//--------------------------------------------------------------
static u32 Jiki_MoveBitCheck( PLAYER_STATE_PTR jiki, u32 bit )
{
	return( (jiki->move_bit&bit) );
}

//--------------------------------------------------------------
/**
 * 自機速度を取得
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		JIKI_SPEED_0等
 */
//--------------------------------------------------------------
int Player_MoveSpeedGet( PLAYER_STATE_PTR jiki )
{
	return( jiki->speed );
}

//--------------------------------------------------------------
/**
 * 自機速度をセット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	speed	JIKI_SPEED_0等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveSpeedSet( PLAYER_STATE_PTR jiki, int speed )
{
	jiki->speed = speed;
}

//--------------------------------------------------------------
/**
 * 自機速度をセット＆ブレーキクリア
 * @param	jiki	PLAYER_STATE_PTR
 * @param	speed	JIKI_SPEED_0等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveSpeedClear( PLAYER_STATE_PTR jiki )
{
	jiki->speed = JIKI_SPEED_0;
	Player_MoveBitSet_CycleBrake( jiki, FALSE );
}

//--------------------------------------------------------------
/**
 * 自機速度の増減　最大値指定
 * @param	jiki	PLAYER_STATE_PTR
 * @param	add		増減値
 * @param	max		速度最大
 * @retval	int		増減後の速度
 */
//--------------------------------------------------------------
int Player_MoveSpeedAdd( PLAYER_STATE_PTR jiki, int add, int max )
{
	jiki->speed += add;
	if( jiki->speed > max ){ jiki->speed = max; }
	return( jiki->speed );
}

//--------------------------------------------------------------
/**
 * 自機キー入力X方向セット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_InputKeyDirXSet( PLAYER_STATE_PTR jiki, int dir )
{
	jiki->input_key_dir_x = dir;
}

//--------------------------------------------------------------
/**
 * 自機キー入力X方向取得
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		DIR_UP等
 */
//--------------------------------------------------------------
int Player_InputKeyDirXGet( PLAYER_STATE_PTR jiki )
{
	return( jiki->input_key_dir_x );
}

//--------------------------------------------------------------
/**
 * 自機キー入力Z方向セット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_InputKeyDirZSet( PLAYER_STATE_PTR jiki, int dir )
{
	jiki->input_key_dir_z = dir;
}

//--------------------------------------------------------------
/**
 * 自機キー入力Z方向取得
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		DIR_UP等
 */
//--------------------------------------------------------------
int Player_InputKeyDirZGet( PLAYER_STATE_PTR jiki )
{
	return( jiki->input_key_dir_z );
}

//--------------------------------------------------------------
/**
 * 自機キー入力X,Z方向セット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir_x	DIR_UP等
 * @param	dir_z	DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_InputKeyDirSet( PLAYER_STATE_PTR jiki, int dir_x, int dir_z )
{
	Player_InputKeyDirXSet( jiki, dir_x );
	Player_InputKeyDirZSet( jiki, dir_z );
}

//--------------------------------------------------------------
/**
 * 自機接続EOAセット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	eoa		接続EOA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_JointEoaSet( PLAYER_STATE_PTR jiki, EOA_PTR eoa )
{
	jiki->joint_eoa = eoa;
}

//--------------------------------------------------------------
/**
 * 自機接続EOA取得
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	EOA_PTR	接続EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR Player_JointEoaGet( PLAYER_STATE_PTR jiki )
{
	return( jiki->joint_eoa );
}

//--------------------------------------------------------------
/**
 * PLAYER_SAVE_DATAセット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	save	PLAYER_SAVE_DATA *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_SaveDataPtrSet( PLAYER_STATE_PTR jiki, PLAYER_SAVE_DATA *save )
{
	jiki->savedata = save;
}

//--------------------------------------------------------------
/**
 * PLAYER_SAVE_DATA取得
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	PLAYER_SAVE_DATA PLAYER_SAVE_DATA*
 */
//--------------------------------------------------------------
PLAYER_SAVE_DATA * Player_SaveDataPtrGet( PLAYER_STATE_PTR jiki )
{
	return( jiki->savedata );
}

//--------------------------------------------------------------
/**
 * 自機アニメーションコマンドコードセット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	ac		アニメコードAC_DIR_U等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_AcmdCodeSet( PLAYER_STATE_PTR jiki, u32 ac )
{
	jiki->set_ac = ac;
}

//--------------------------------------------------------------
/**
 * 自機アニメーションコマンドコード取得
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	u32		アニメコード AC_DIR_U等
 */
//--------------------------------------------------------------
u32 Player_AcmdCodeGet( PLAYER_STATE_PTR jiki )
{
	return( jiki->set_ac );
}

//--------------------------------------------------------------
/**
 * 自機足音番号を取得
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	u32		0,1
 */
//--------------------------------------------------------------
u32 Player_SEWalkLRNumGet( PLAYER_STATE_PTR jiki )
{
	return( jiki->se_walk_lr );
}

//--------------------------------------------------------------
/**
 * 自機足音番号進行
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	u32		0,1
 */
//--------------------------------------------------------------
void Player_SEWalkLRNumInc( PLAYER_STATE_PTR jiki )
{
	jiki->se_walk_lr = (jiki->se_walk_lr + 1) & 0x01;
}

//==============================================================================
//	プレイヤーセーブデータ
//==============================================================================
//--------------------------------------------------------------
/**
 * PLAYER_SAVE_DATA初期化
 * @param	jikisave	PLAYER_SAVE_DATA *
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_SaveDataInit( PLAYER_SAVE_DATA *save )
{
	save->gear_type = GEAR_3;
	save->shoes_flag = FALSE;
	save->form = HERO_FORM_NORMAL;
}

//--------------------------------------------------------------
/**
 * PLAYER_SAVE_DATAからダッシュチェック
 * @param	jikisave	PLAYER_SAVE_DATA *
 * @retval	int			TRUE=ダッシュできる　FALSE=出来ない
 */
//--------------------------------------------------------------
int Player_SaveDataDashCheck( PLAYER_SAVE_DATA *save )
{
	if( save != NULL ){
		if( save->shoes_flag == TRUE ){
			return( TRUE );
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * PLAYER_SAVE_DATAからダッシュフラグをセット
 * @param	jikisave	PLAYER_SAVE_DATA *
 * @param	flag		TRUE=ダッシュできる FALSE=出来ない
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_SaveDataDashSet( PLAYER_SAVE_DATA *save, int flag )
{
	if( flag == TRUE ){
		save->shoes_flag = TRUE;
	}else{
		save->shoes_flag = FALSE;
	}
}

//--------------------------------------------------------------
/**
 * PLAYER_SAVE_DATAからギアタイプ取得
 * @param	jikisave	PLAYER_SAVE_DATA *
 * @retval	int			GEAR_3,GEAR4等
 */
//--------------------------------------------------------------
int Player_SaveDataGearCheck( PLAYER_SAVE_DATA *save )
{
	if( save == NULL ){
		return( GEAR_3 );
	}
	
	return( save->gear_type );
}

//--------------------------------------------------------------
/**
 * PLAYER_SAVE_DATAからギアタイプセット
 * @param	jikisave	PLAYER_SAVE_DATA *
 * @param	gear		GEAR_3,GEAR4等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_SaveDataGearSet( PLAYER_SAVE_DATA *save, int gear )
{
	if( save != NULL ){
		save->gear_type = gear;
	}
}

//--------------------------------------------------------------
/**
 * 自機からセーブデータギアセット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	gear	GEAR_3等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_SaveDataGetGearSet( PLAYER_STATE_PTR jiki, int gear )
{
	PLAYER_SAVE_DATA *save = Player_SaveDataPtrGet( jiki );
	Player_SaveDataGearSet( save, gear );
}

//--------------------------------------------------------------
/**
 * 自機からセーブデータギア取得
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		GEAR_3等
 */
//--------------------------------------------------------------
int Player_SaveDataGetGearGet( PLAYER_STATE_PTR jiki )
{
	PLAYER_SAVE_DATA *save = Player_SaveDataPtrGet( jiki );
	return( Player_SaveDataGearCheck(save) );
}

//--------------------------------------------------------------
/**
 * PLAYER_SAVE_DATAから自機形態を取得
 * @param	jikisave	PLAYER_SAVE_DATA *
 * @retval	u32			HERO_FORM_NORMAL等
 */
//--------------------------------------------------------------
u32 Player_SaveDataFormGet( PLAYER_SAVE_DATA *save )
{
	if( save != NULL ){
		return( save->form );
	}
	
	return( HERO_FORM_NORMAL );
}

//--------------------------------------------------------------
/**
 * PLAYER_SAVE_DATAから自機形態をセット
 * @param	jikisave	PLAYER_SAVE_DATA *
 * @param	form		HERO_FORM_NORMAL等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_SaveDataFormSet( PLAYER_SAVE_DATA *save, u32 form )
{
	if( save != NULL ){
		save->form = form;
	}
}

//--------------------------------------------------------------
/**
 * 自機からセーブデータ形態をセット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	form	HERO_FORM_NORMAL等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_SaveDataGetFormSet( PLAYER_STATE_PTR jiki, u32 form )
{
	PLAYER_SAVE_DATA *save = Player_SaveDataPtrGet( jiki );
	Player_SaveDataFormSet( save, form );
}

//--------------------------------------------------------------
/**
 * 自機からセーブデータ形態取得
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		GEAR_3等
 */
//--------------------------------------------------------------
u32 Player_SaveDataGetFormGet( PLAYER_STATE_PTR jiki )
{
	PLAYER_SAVE_DATA *save = Player_SaveDataPtrGet( jiki );
	return( Player_SaveDataFormGet(save) );
}

//==============================================================================
//	パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * 自機座標更新	現在位置で更新
 * @param	jiki			PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_GPosNowUpdate( const PLAYER_STATE_PTR jiki )
{
	FieldOBJ_GPosUpdate( Player_FieldOBJGet(jiki) );
}

//--------------------------------------------------------------
/**
 * 自機座標更新	方向
 * @param	jiki			PLAYER_STATE_PTR
 * @param	dir			移動する方向
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_GPosAddDir( PLAYER_STATE_PTR jiki, int dir )
{
	FieldOBJ_NowGPosDirAdd( Player_FieldOBJGet(jiki), dir );
}

//--------------------------------------------------------------
/**
 * 自機座標、方向を初期化　FX32型
 * @param	jiki	PLAYER_STATE_PTR
 * @param	vec		初期化座標
 * @param	dir		方向 DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_VecPosInit( PLAYER_STATE_PTR jiki, const VecFx32 *vec, int dir )
{
	FIELD_OBJ_PTR fldobj;
	
	fldobj = Player_FieldOBJGet( jiki );
	FieldOBJ_VecPosDirInit( fldobj, vec, dir );
	
	Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_STOP );
	Player_MoveStateSet( jiki, OBJ_MOVE_STATE_OFF );
}

//--------------------------------------------------------------
/**
 * 自機座標、方向を初期化 グリッド座標型
 * @param	jiki	PLAYER_STATE_PTR
 * @param	x		グリッドX座標
 * @param	z		グリッドZ座標
 * @param	dir		方向 DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_GPosInit( PLAYER_STATE_PTR jiki, int x, int z, int dir )
{
	FIELD_OBJ_PTR fldobj;
	
	fldobj = Player_FieldOBJGet( jiki );
	FieldOBJ_GPosDirInit( fldobj, x, 0, z, dir );
	
	Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_STOP );
	Player_MoveStateSet( jiki, OBJ_MOVE_STATE_OFF );
}

//--------------------------------------------------------------
/**
 * 自機のY座標をセットする。実座標で
 * @param	jiki	PLAYER_STATE_PTR
 * @param	y		高さ
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_VecPosYSet( PLAYER_STATE_PTR jiki, fx32 y )
{
	VecFx32 vec;
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	
	FieldOBJ_VecPosGet( fldobj, &vec );
	
	vec.y = y;
	FieldOBJ_VecPosSet( fldobj, &vec );
}

//--------------------------------------------------------------
/**
 * 自機の高さ自動取得のON OFFを行う
 * @param	jiki	PLAYER_STATE_PTR
 * @param	flag	TRUE=自動取得　FALSE=取得しない
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_HeightGet_ON_OFF( PLAYER_STATE_PTR jiki, int flag )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	
	if( flag == TRUE ){
		FieldOBJ_StatusBitSet_HeightGetOFF( fldobj, FALSE );
	}else{
		FieldOBJ_StatusBitSet_HeightGetOFF( fldobj, TRUE );
	}
}

//--------------------------------------------------------------
/**
 * 自機の高さ自動取得のON OFFを行う。ONの場合は即反映
 * @param	jiki	PLAYER_STATE_PTR
 * @param	flag	TRUE=自動取得　FALSE=取得しない
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_HeightGetSet_ON_OFF( PLAYER_STATE_PTR jiki, int flag )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	
	if( flag == TRUE ){
		FieldOBJ_StatusBitSet_HeightGetOFF( fldobj, FALSE );
		FieldOBJ_VecPosNowHeightGetSet( fldobj );
	}else{
		FieldOBJ_StatusBitSet_HeightGetOFF( fldobj, TRUE );
	}
}

//--------------------------------------------------------------
/**
 * OBJコードから性別取得
 * @param	code	HERO等
 * @retval	int		PM_MALE等
 */
//--------------------------------------------------------------
int Player_OBJCodeSexGet( int code )
{
	switch( code ){
	case HERO:
	case CYCLEHERO:
		return( PM_MALE );
	}
	
	return( PM_FEMALE );
}

//--------------------------------------------------------------
/**
 * 形態と性別から自機OBJコードを取得
 * @param	form	HERO_FORM_NORMAL等
 * @param	sex		PM_MALE等
 * @retval	int		HERO等
 */
//--------------------------------------------------------------
int Player_FormSexOBJCodeGet( int form, int sex )
{
	if( sex == PM_MALE ){
		switch( form ){
		case HERO_FORM_NORMAL:	return( HERO );
		case HERO_FORM_CYCLE:	return( CYCLEHERO );
		case HERO_FORM_SWIM:	return( SWIMHERO );
		case HERO_DRAWFORM_SP:		return( SPHERO );
		case HERO_DRAWFORM_WATER:	return( WATERHERO );
		case HERO_DRAWFORM_CONTEST:	return( CONTESTHERO );
		case HERO_DRAWFORM_FISHING:	return( FISHINGHERO );
		case HERO_DRAWFORM_POKETCH:	return( POKEHERO );
		case HERO_DRAWFORM_SAVE:	return( SAVEHERO );
		case HERO_DRAWFORM_BANZAI:	return( BANZAIHERO );
		}
	}else{
		switch( form ){
		case HERO_FORM_NORMAL:	return( HEROINE );
		case HERO_FORM_CYCLE:	return( CYCLEHEROINE );
		case HERO_FORM_SWIM:	return( SWIMHEROINE );
		case HERO_DRAWFORM_SP:		return( SPHEROINE );
		case HERO_DRAWFORM_WATER:	return( WATERHEROINE );
		case HERO_DRAWFORM_CONTEST:	return( CONTESTHEROINE );
		case HERO_DRAWFORM_FISHING:	return( FISHINGHEROINE );
		case HERO_DRAWFORM_POKETCH:	return( POKEHEROINE );
		case HERO_DRAWFORM_SAVE:	return( SAVEHEROINE );
		case HERO_DRAWFORM_BANZAI:	return( BANZAIHEROINE );
		}
	}
	
	GF_ASSERT( 0 && "Player_FormSexOBJCodeGet() form不正" );
	return( HERO );
}

//--------------------------------------------------------------
/**
 * 形態からリクエストを取得
 * @param	form	HERO_FORM_NORMAL等
 * @retval	u32		HERO_REQBIT_NORMAL等
 */
//--------------------------------------------------------------
u32 Player_FormRequestGet( int form )
{
	switch( form ){
	case HERO_FORM_NORMAL:	return( HERO_REQBIT_NORMAL );
	case HERO_FORM_CYCLE:	return( HERO_REQBIT_CYCLE );
	case HERO_FORM_SWIM:	return( HERO_REQBIT_SWIM );
	case HERO_DRAWFORM_WATER:	return( HERO_REQBIT_WATER );
	case HERO_DRAWFORM_FISHING:	return( HERO_REQBIT_FISHING );
	case HERO_DRAWFORM_POKETCH:	return( HERO_REQBIT_POKETCH );
	case HERO_DRAWFORM_SAVE:	return( HERO_REQBIT_SAVE );
	case HERO_DRAWFORM_BANZAI:	return( HERO_REQBIT_BANZAI );
	}
	
	GF_ASSERT( 0 );
	return( HERO_REQBIT_NORMAL );
}

//--------------------------------------------------------------
/**
 * OBJコードから自機形態を取得
 * @param	code	HERO等
 * @retval	int		HERO_FORM_NORMAL等
 */
//--------------------------------------------------------------
int Player_OBJCodeFormGet( int code )
{
	switch( code ){
	case HERO:
	case HEROINE:
		return( HERO_FORM_NORMAL );
	case CYCLEHERO:
	case CYCLEHEROINE:			return( HERO_FORM_CYCLE );
	}
		
	GF_ASSERT( 0 && "Player_OBJCodeFormGet() code不正" );
	return( HERO_FORM_NORMAL );
}

//--------------------------------------------------------------
/**
 * FIELDSYS_WORKからPLAYER_STATE_PTR取得
 * @param	fsys	FIELDSYS_WORK *
 * @retval	PLAYER_STATE_PTR	PLAYER_STATE_PTR
 */
//--------------------------------------------------------------
PLAYER_STATE_PTR Player_FieldSysWorkPlayerGet( FIELDSYS_WORK *fsys )
{
	return( fsys->player );
}

//==============================================================================
//	自機動作ビット
//==============================================================================
//--------------------------------------------------------------
/**
 * 自機動作ビット　強制移動を操作する
 * @param	jiki	PLAYER_STATE_PTR
 * @param	flag	TRUE=ON,FALSE=OFF
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveBitSet_Force( PLAYER_STATE_PTR jiki, int flag )
{
	if( flag == TRUE ){
		Jiki_MoveBitON( jiki, JIKI_MOVE_BIT_FORCE );
	}else{
		Jiki_MoveBitOFF( jiki, JIKI_MOVE_BIT_FORCE );
	}
}

//--------------------------------------------------------------
/**
 * 自機動作ビット　強制移動チェック
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=強制移動中
 */
//--------------------------------------------------------------
int Player_MoveBitCheck_Force( PLAYER_STATE_PTR jiki )
{
	if( Jiki_MoveBitCheck(jiki,JIKI_MOVE_BIT_FORCE) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 自機動作ビット　足元無効を操作する
 * @param	jiki	PLAYER_STATE_PTR
 * @param	flag	TRUE=ON,FALSE=OFF
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveBitSet_UnderOFF( PLAYER_STATE_PTR jiki, int flag )
{
	if( flag == TRUE ){
		Jiki_MoveBitON( jiki, JIKI_MOVE_BIT_UNDER_OFF );
	}else{
		Jiki_MoveBitOFF( jiki, JIKI_MOVE_BIT_UNDER_OFF );
	}
}

//--------------------------------------------------------------
/**
 * 自機動作ビット　足元無効チェック
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=足元無効
 */
//--------------------------------------------------------------
int Player_MoveBitCheck_UnderOFF( PLAYER_STATE_PTR jiki )
{
	if( Jiki_MoveBitCheck(jiki,JIKI_MOVE_BIT_UNDER_OFF) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 自機動作ビット　自転車ブレーキセット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	flag	TRUE=ブレーキ　FALSE=無し
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveBitSet_CycleBrake( PLAYER_STATE_PTR jiki, int flag )
{
	if( flag == TRUE ){
		Jiki_MoveBitON( jiki, JIKI_MOVE_BIT_CYCLE_BRAKE );
	}else{
		Jiki_MoveBitOFF( jiki, JIKI_MOVE_BIT_CYCLE_BRAKE );
	}
}

//--------------------------------------------------------------
/**
 * 自機動作ビット　自転車ブレーキチェック
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=ブレーキアリ　FALSE=ブレーキ無し
 */
//--------------------------------------------------------------
int Player_MoveBitCheck_CycleBrake( PLAYER_STATE_PTR jiki )
{
	if( Jiki_MoveBitCheck(jiki,JIKI_MOVE_BIT_CYCLE_BRAKE) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 自機動作ビット　サイクリングロードセット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	flag	TRUE=サイクリングロード　FALSE=無し
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveBitSet_CyclingRoad( PLAYER_STATE_PTR jiki, int flag )
{
	if( flag == TRUE ){
		Jiki_MoveBitON( jiki, JIKI_MOVE_BIT_CYCLING_ROAD );
	}else{
		Jiki_MoveBitOFF( jiki, JIKI_MOVE_BIT_CYCLING_ROAD );
	}
}

//--------------------------------------------------------------
/**
 * 自機動作ビット　自転車サイクリングロードチェック
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=サイクリングロード　FALSE=無し
 */
//--------------------------------------------------------------
int Player_MoveBitCheck_CyclingRoad( PLAYER_STATE_PTR jiki )
{
	if( Jiki_MoveBitCheck(jiki,JIKI_MOVE_BIT_CYCLING_ROAD ) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 自機動作ビット　深い沼を操作する
 * @param	jiki	PLAYER_STATE_PTR
 * @param	flag	TRUE=ON,FALSE=OFF
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveBitSet_DeepSwampOFF( PLAYER_STATE_PTR jiki, int flag )
{
	if( flag == TRUE ){
		Jiki_MoveBitON( jiki, JIKI_MOVE_BIT_DEEPSWAMP_OFF );
	}else{
		Jiki_MoveBitOFF( jiki, JIKI_MOVE_BIT_DEEPSWAMP_OFF );
	}
}

//--------------------------------------------------------------
/**
 * 自機動作ビット　自転車サイクリングロードチェック
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=サイクリングロード　FALSE=無し
 */
//--------------------------------------------------------------
int Player_MoveBitCheck_DeepSwampOFF( PLAYER_STATE_PTR jiki )
{
	if( Jiki_MoveBitCheck(jiki,JIKI_MOVE_BIT_DEEPSWAMP_OFF ) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 自機動作ビット　流砂移動
 * @param	jiki	PLAYER_STATE_PTR
 * @param	flag	TRUE=ON,FALSE=OFF
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveBitSet_SandFloatSet( PLAYER_STATE_PTR jiki, int flag )
{
	if( flag == TRUE ){
		Jiki_MoveBitON( jiki, JIKI_MOVE_BIT_SAND_FLOAT );
	}else{
		Jiki_MoveBitOFF( jiki, JIKI_MOVE_BIT_SAND_FLOAT );
	}
}

//--------------------------------------------------------------
/**
 * 自機動作ビット　流砂移動チェック
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=流砂移動
 */
//--------------------------------------------------------------
int Player_MoveBitCheck_SandFloat( PLAYER_STATE_PTR jiki )
{
	if( Jiki_MoveBitCheck(jiki,JIKI_MOVE_BIT_SAND_FLOAT) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 自機動作ビット　一歩移動セット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	flag	TRUE=ON,FALSE=OFF
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveBitSet_StepON( PLAYER_STATE_PTR jiki )
{
	Jiki_MoveBitON( jiki, JIKI_MOVE_BIT_STEP );
}

//--------------------------------------------------------------
/**
 * 自機動作ビット　一歩移動OFF
 * @param	jiki	PLAYER_STATE_PTR
 * @param	flag	TRUE=ON,FALSE=OFF
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveBitSet_StepOFF( PLAYER_STATE_PTR jiki )
{
	Jiki_MoveBitOFF( jiki, JIKI_MOVE_BIT_STEP );
}

//--------------------------------------------------------------
/**
 * 自機動作ビット　一歩移動
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=一歩移動
 */
//--------------------------------------------------------------
int Player_MoveBitCheck_Step( PLAYER_STATE_PTR jiki )
{
	if( Jiki_MoveBitCheck(jiki,JIKI_MOVE_BIT_STEP) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 自機動作ビット　強制移動　速度保存セット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	flag	TRUE=ON,FALSE=OFF
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveBitSet_ForceSaveSpeed( PLAYER_STATE_PTR jiki, int flag )
{
	if( flag == TRUE ){
		Jiki_MoveBitON( jiki, JIKI_MOVE_BIT_FORCE_SAVE_SPEED );
	}else{
		Jiki_MoveBitOFF( jiki, JIKI_MOVE_BIT_FORCE_SAVE_SPEED );
	}
}

//--------------------------------------------------------------
/**
 * 自機動作ビット　強制移動　速度保存チェック
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=ON
 */
//--------------------------------------------------------------
int Player_MoveBitCheck_ForceSaveSpeed( PLAYER_STATE_PTR jiki )
{
	return( Jiki_MoveBitCheck(jiki,JIKI_MOVE_BIT_FORCE_SAVE_SPEED) );
}
