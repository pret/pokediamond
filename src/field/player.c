//******************************************************************************
/**
 *
 * @file	player.c
 * @brief	���@
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
///	����r�b�g
//--------------------------------------------------------------
#define JIKI_MOVE_BIT_NON				(0)			///<��������
#define JIKI_MOVE_BIT_FORCE 			(1<<0)		///<�����ړ���
#define JIKI_MOVE_BIT_UNDER_OFF			(1<<1)		///<����������
#define JIKI_MOVE_BIT_CYCLE_BRAKE		(1<<2)		///<���]�ԃu���[�L
#define JIKI_MOVE_BIT_CYCLING_ROAD		(1<<3)		///<���]�ԃT�C�N�����O���[�h
#define JIKI_MOVE_BIT_DEEPSWAMP_OFF		(1<<4)		///<���Ƃ薳��
#define JIKI_MOVE_BIT_SAND_FLOAT		(1<<5)		///<�����ŗ����
#define JIKI_MOVE_BIT_STEP				(1<<6)		///<����ړ�
#define JIKI_MOVE_BIT_FORCE_SAVE_SPEED	(1<<7)		///<�����ړ����@�ړ���̑��x�N���A����

//--------------------------------------------------------------
///	�t�B�[���hOBJ���������Ɏw�肷��X�e�[�^�X�r�b�g
//--------------------------------------------------------------
///�������A���[�h���ɗ��Ă�r�b�g
#define JIKI_FLDOBJ_INIT_STA_BIT_ON \
(FLDOBJ_STA_BIT_ZONE_DEL_NOT|FLDOBJ_STA_BIT_HEIGHT_VANISH_OFF)
///�������A���[�h���ɉ��낷�r�b�g
#define JIKI_FLDOBJ_INIT_STA_BIT_OFF \
(FLDOBJ_STA_BIT_PAUSE_DIR|FLDOBJ_STA_BIT_PAUSE_ANM)

//==============================================================================
//	struct
//==============================================================================
//--------------------------------------------------------------
//	PLAYER_STATE�\����
//--------------------------------------------------------------
struct _TAG_PLAYER_STATE
{
	u32 move_bit;											///<����t���O
	u32 request_bit;										///<���N�G�X�g
	u32 set_ac;												///<�Z�b�g�A�j���[�V�����R�[�h
	u32 se_walk_lr;											///<�������E
	int move_value;											///<������ OBJ_MOVE_VALUE_STOP��
	int move_state;											///<����� OBJ_MOVE_STATE_OFF��
	int form;												///<�`�� HERO_FORM_NORMAL��
	int sex;												///<���� PM_MALE��
	int speed;												///<���@�X�s�[�h
	int input_key_dir_x;									///<�L�[���͕���
	int input_key_dir_z;									///<�L�[���͕���
	FIELD_OBJ_PTR fldobj;									///<���@�p�t�B�[���hOBJ *
	EOA_PTR joint_eoa;										///<�ڑ�EOA
	PLAYER_SAVE_DATA *savedata;
	const PLAYER_SAVE_DATA *save;							///<�Z�[�u�f�[�^�Q��*
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
//	���@
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@������
 * @param	fos			CONST_FIELD_OBJ_SYS_PTR
 * @param	x			�ǉ�����O���b�hX���W
 * @param	z			�ǉ�����O���b�hY���W
 * @param	dir			�������� DIR_UP��
 * @param	form		���@�`�ԁ@HERO_FORM_NORMAL��
 * @param	sex			���ʁ@PM_MALE��
 * @param	save		PLAYER_SAVE_DATA * NULL=�Q�Ƃ��Ȃ�
 * @retval	PLAYER_STATE_PTR	�ǉ����ꂽPLAYER_STATE_PTR
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
 * ���@�@�t�B�[���hOBJ���g�p���ĕ���
 * @param	fos			CONST_FIELD_OBJ_SYS_PTR
 * @param	save		PLAYER_SAVE_DATA *
 * @retval	PLAYER_STATE_PTR	�ǉ����ꂽPLAYER_STATE_PTR
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
 * ���@�@�`�揉����
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
	GF_ASSERT( fldobj != NULL && "Player_DrawInit() ���@�t�B�[���hOBJ������܂���" );
	
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
 * ���@�폜
 * @param	player			�J������PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_Delete( PLAYER_STATE_PTR jiki )
{
	sys_FreeMemoryEz( jiki );
}

//--------------------------------------------------------------
/**
 * ���@���ׂč폜
 * @param	player			�J������PLAYER_STATE_PTR
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
 * ���@�p���[�N�������m��
 * @param	nothing
 * @retval	PLAYER_STATE_PTR	�m�ۂ���PLAYER_STATE_PTR
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
 * ���@���[�N������
 * @param	jiki	PLAYER_STATE_PTR
 * @param	form	HERO_FORM_NORMAL��
 * @param	sex		PM_MALE��
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
 * ���@�t�B�[���hOBJ�ǉ�
 * @param	jiki		PLAYER_STATE_PTR
 * @param	fos			FIELD_OBJ_SYS_PTR
 * @param	obj			OBJ�R�[�h�BHERO��
 * @param	dir			���������BDIR_UP��
 * @param	x			�O���b�hX���W
 * @param	y			�O���b�hY���W
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
 * �t�B�[���hOBJ���玩�@�t�B�[���hOBJ�����@�O��
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	FIELD_OBJ_PTR	���@�t�B�[���hOBJ
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
 * �t�B�[���hOBJ���玩�@�t�B�[���hOBJ����
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	FIELD_OBJ_PTR	���@�t�B�[���hOBJ
 */
//--------------------------------------------------------------
static FIELD_OBJ_PTR Jiki_FieldOBJSearch( CONST_FIELD_OBJ_SYS_PTR fos )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJSearch( fos );
	GF_ASSERT( fldobj != NULL && "Jiki_FieldOBJSearch()���@�t�B�[���hOBJ������" );
	return( fldobj );
}

//==============================================================================
//	PLAYER_STATE�@�Q��
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@�̌������擾
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		DIR_UP��
 */
//--------------------------------------------------------------
int Player_DirGet( const PLAYER_STATE_PTR jiki )
{
	return( FieldOBJ_DirDispGet(Player_FieldOBJGet(jiki)) );
}

//--------------------------------------------------------------
/**
 * ���@�̌������Z�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		DIR_UP��
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_DirSet( PLAYER_STATE_PTR jiki, int dir )
{
	FieldOBJ_DirDispCheckSet( Player_FieldOBJGet(jiki), dir );
}

//--------------------------------------------------------------
/**
 * ���@�̈ړ��������擾
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		DIR_UP��
 */
//--------------------------------------------------------------
int Player_DirMoveGet( const PLAYER_STATE_PTR jiki )
{
	return( FieldOBJ_DirMoveGet(Player_FieldOBJGet(jiki)) );
}

//--------------------------------------------------------------
/**
 * ���@���݃O���b�hX���W���擾
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		�O���b�hX���W
 */
//--------------------------------------------------------------
int Player_NowGPosXGet( const PLAYER_STATE_PTR jiki )
{
	return( FieldOBJ_NowPosGX_Get(Player_FieldOBJGet(jiki)) );
}

//--------------------------------------------------------------
/**
 * ���@���݃O���b�hZ���W���擾
 * @param	jiki		PLAYER_STATE_PTR
 * @retval	int		�O���b�hZ���W
 */
//--------------------------------------------------------------
int Player_NowGPosZGet( const PLAYER_STATE_PTR jiki )
{
	return( FieldOBJ_NowPosGZ_Get(Player_FieldOBJGet(jiki)) );
}

//--------------------------------------------------------------
/**
 * ���@�ߋ��O���b�hX���W���擾
 * @param	jiki		PLAYER_STATE_PTR
 * @retval	int		�O���b�hX���W
 */
//--------------------------------------------------------------
int Player_OldGPosXGet( const PLAYER_STATE_PTR jiki )
{
	return( FieldOBJ_OldPosGX_Get(Player_FieldOBJGet(jiki)) );
}

//--------------------------------------------------------------
/**
 * ���@�ߋ��O���b�hZ���W���擾
 * @param	jiki		PLAYER_STATE_PTR
 * @retval	int		�O���b�hZ���W
 */
//--------------------------------------------------------------
int Player_OldGPosZGet( const PLAYER_STATE_PTR jiki )
{
	return( FieldOBJ_OldPosGZ_Get(Player_FieldOBJGet(jiki)) );
}

//--------------------------------------------------------------
/**
 * ���@3D���W���擾
 * @param	jiki	PLAYER_STATE_PTR
 * @param	vec		���W�i�[��
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_VecPosGet( const PLAYER_STATE_PTR jiki, VecFx32 *vec )
{
	FieldOBJ_VecPosGet( Player_FieldOBJGet(jiki), vec );
}

//--------------------------------------------------------------
/**
 * ���@3D���W�|�C���^���擾
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	VecFx32	���@���W*
 */
//--------------------------------------------------------------
const VecFx32 * Player_VecPosPtrGet( const PLAYER_STATE_PTR jiki )
{
	return( FieldOBJ_VecPosPtrGet(Player_ConstFieldOBJGet(jiki)) );
}

//--------------------------------------------------------------
/**
 * ���@3D�I�t�Z�b�g���W�|�C���^���擾
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	VecFx32	���@���W*
 */
//--------------------------------------------------------------
VecFx32 * Player_VecDrawOffsPtrGet( PLAYER_STATE_PTR jiki )
{
	return( FieldOBJ_VecDrawOffsPtrGet(Player_FieldOBJGet(jiki)) );
}

//--------------------------------------------------------------
/**
 * ���@�����Ԃ��Z�b�g
 * @param	jiki		PLAYER_STATE_PTR
 * @param	val		OBJ_MOVE_VALUE_STOP��
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveValueSet( PLAYER_STATE_PTR jiki, int val )
{
	jiki->move_value = val;
}

//--------------------------------------------------------------
/**
 * ���@�����Ԃ��擾
 * @param	jiki		PLAYER_STATE_PTR
 * @retval	int		OBJ_MOVE_VALUE_STOP��
 */
//--------------------------------------------------------------
int Player_MoveValueGet( const PLAYER_STATE_PTR jiki )
{
	return( jiki->move_value );
}

//--------------------------------------------------------------
/**
 * ���@����󋵂��Z�b�g
 * @param	jiki		PLAYER_STATE_PTR
 * @param	state OBJ_MOVE_STATE_OFF��
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveStateSet( PLAYER_STATE_PTR jiki, int state )
{
	jiki->move_state = state;
}

//--------------------------------------------------------------
/**
 * ���@����󋵂��擾
 * @param	jiki		PLAYER_STATE_PTR
 * @retval	int		OBJ_MOVE_STATE_OFF��
 */
//--------------------------------------------------------------
int Player_MoveStateGet( const PLAYER_STATE_PTR jiki )
{
	return( jiki->move_state );
}

//--------------------------------------------------------------
/**
 * ���@�̕\��ON,OFF���w��
 * @param	jiki		PLAYER_STATE_PTR
 * @param	flag		TRUE=�\���AFALSE=��\��
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
 * ���@�̕\��ON,OFF�t���O���擾
 * @param	jiki		PLAYER_STATE_PTR
 * @retval	int			TRUE=�\���AFALSE=��\��
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
 * ���@�̃t�B�[���hOBJ *�Z�b�g
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
 * ���@�̃t�B�[���hOBJ *���擾
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
 * ���@�̃t�B�[���hOBJ *���擾 const
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
 * ���@�̌`�ԃZ�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	form	HERO_FORM_NORMAL��
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
 * ���@�̌`�Ԃ��擾
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		HERO_FORM_NORMAL��
 */
//--------------------------------------------------------------
int Player_FormGet( PLAYER_STATE_PTR jiki )
{
	GF_ASSERT( jiki != NULL && "Player_FormGet()���@���������s���Ă��Ȃ�" );
	return( jiki->form );
}

//--------------------------------------------------------------
/**
 * ���@���N�G�X�g�r�b�gON
 * @param	jiki	PLAYER_STATE_PTR
 * @param	bit		HERO_REQBIT_NORMAL��
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_RequestBit_ON( PLAYER_STATE_PTR jiki, u32 bit )
{
	jiki->request_bit |= bit;
}

//--------------------------------------------------------------
/**
 * ���@���N�G�X�g�r�b�g�Z�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	bit		HERO_REQBIT_NORMAL��
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_RequestBit_Set( PLAYER_STATE_PTR jiki, u32 bit )
{
	jiki->request_bit = bit;
}

//--------------------------------------------------------------
/**
 * ���@���N�G�X�g�r�b�g�擾
 * @param	jiki	PLAYER_STATE_PTR
 * @param	bit		HERO_REQBIT_NORMAL��
 * @retval	nothing
 */
//--------------------------------------------------------------
u32 Player_RequestBit_Get( PLAYER_STATE_PTR jiki )
{
	return( jiki->request_bit );
}

//--------------------------------------------------------------
/**
 * ���ʃZ�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	sex		PM_MALE��
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_SexSet( PLAYER_STATE_PTR jiki, int sex )
{
	jiki->sex = sex;
}

//--------------------------------------------------------------
/**
 * ���ʎ擾
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		PM_MALE��
 */
//--------------------------------------------------------------
int Player_SexGet( PLAYER_STATE_PTR jiki )
{
	return( jiki->sex );
}

//--------------------------------------------------------------
/**
 * ���@����r�b�g�@�Z�b�g
 * @param	jiki	PLYAER_STATE_PTR
 * @param	bit		�Z�b�g����l JIKI_MOVE_BIT_NON��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveBitSet( PLAYER_STATE_PTR jiki, u32 bit )
{
	jiki->move_bit = bit;
}

//--------------------------------------------------------------
/**
 * ���@����r�b�g��ON
 * @param	jiki	PLAYER_STATE_PTR
 * @param	bit		JIKI_MOVE_BIT_FORCE��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveBitON( PLAYER_STATE_PTR jiki, u32 bit )
{
	jiki->move_bit |= bit;
}

//--------------------------------------------------------------
/**
 * ���@����r�b�g��OFF
 * @param	jiki	PLAYER_STATE_PTR
 * @param	bit		JIKI_MOVE_BIT_FORCE��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveBitOFF( PLAYER_STATE_PTR jiki, u32 bit )
{
	jiki->move_bit &= ~bit;
}

//--------------------------------------------------------------
/**
 * ���@����r�b�g�̃`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @param	bit		JIKI_MOVE_BIT_FORCE��
 * @retval	u32		����r�b�g&bit
 */
//--------------------------------------------------------------
static u32 Jiki_MoveBitCheck( PLAYER_STATE_PTR jiki, u32 bit )
{
	return( (jiki->move_bit&bit) );
}

//--------------------------------------------------------------
/**
 * ���@���x���擾
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		JIKI_SPEED_0��
 */
//--------------------------------------------------------------
int Player_MoveSpeedGet( PLAYER_STATE_PTR jiki )
{
	return( jiki->speed );
}

//--------------------------------------------------------------
/**
 * ���@���x���Z�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	speed	JIKI_SPEED_0��
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveSpeedSet( PLAYER_STATE_PTR jiki, int speed )
{
	jiki->speed = speed;
}

//--------------------------------------------------------------
/**
 * ���@���x���Z�b�g���u���[�L�N���A
 * @param	jiki	PLAYER_STATE_PTR
 * @param	speed	JIKI_SPEED_0��
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
 * ���@���x�̑����@�ő�l�w��
 * @param	jiki	PLAYER_STATE_PTR
 * @param	add		�����l
 * @param	max		���x�ő�
 * @retval	int		������̑��x
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
 * ���@�L�[����X�����Z�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		DIR_UP��
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_InputKeyDirXSet( PLAYER_STATE_PTR jiki, int dir )
{
	jiki->input_key_dir_x = dir;
}

//--------------------------------------------------------------
/**
 * ���@�L�[����X�����擾
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		DIR_UP��
 */
//--------------------------------------------------------------
int Player_InputKeyDirXGet( PLAYER_STATE_PTR jiki )
{
	return( jiki->input_key_dir_x );
}

//--------------------------------------------------------------
/**
 * ���@�L�[����Z�����Z�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		DIR_UP��
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_InputKeyDirZSet( PLAYER_STATE_PTR jiki, int dir )
{
	jiki->input_key_dir_z = dir;
}

//--------------------------------------------------------------
/**
 * ���@�L�[����Z�����擾
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		DIR_UP��
 */
//--------------------------------------------------------------
int Player_InputKeyDirZGet( PLAYER_STATE_PTR jiki )
{
	return( jiki->input_key_dir_z );
}

//--------------------------------------------------------------
/**
 * ���@�L�[����X,Z�����Z�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir_x	DIR_UP��
 * @param	dir_z	DIR_UP��
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
 * ���@�ڑ�EOA�Z�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	eoa		�ڑ�EOA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_JointEoaSet( PLAYER_STATE_PTR jiki, EOA_PTR eoa )
{
	jiki->joint_eoa = eoa;
}

//--------------------------------------------------------------
/**
 * ���@�ڑ�EOA�擾
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	EOA_PTR	�ڑ�EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR Player_JointEoaGet( PLAYER_STATE_PTR jiki )
{
	return( jiki->joint_eoa );
}

//--------------------------------------------------------------
/**
 * PLAYER_SAVE_DATA�Z�b�g
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
 * PLAYER_SAVE_DATA�擾
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
 * ���@�A�j���[�V�����R�}���h�R�[�h�Z�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	ac		�A�j���R�[�hAC_DIR_U��
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_AcmdCodeSet( PLAYER_STATE_PTR jiki, u32 ac )
{
	jiki->set_ac = ac;
}

//--------------------------------------------------------------
/**
 * ���@�A�j���[�V�����R�}���h�R�[�h�擾
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	u32		�A�j���R�[�h AC_DIR_U��
 */
//--------------------------------------------------------------
u32 Player_AcmdCodeGet( PLAYER_STATE_PTR jiki )
{
	return( jiki->set_ac );
}

//--------------------------------------------------------------
/**
 * ���@�����ԍ����擾
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
 * ���@�����ԍ��i�s
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	u32		0,1
 */
//--------------------------------------------------------------
void Player_SEWalkLRNumInc( PLAYER_STATE_PTR jiki )
{
	jiki->se_walk_lr = (jiki->se_walk_lr + 1) & 0x01;
}

//==============================================================================
//	�v���C���[�Z�[�u�f�[�^
//==============================================================================
//--------------------------------------------------------------
/**
 * PLAYER_SAVE_DATA������
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
 * PLAYER_SAVE_DATA����_�b�V���`�F�b�N
 * @param	jikisave	PLAYER_SAVE_DATA *
 * @retval	int			TRUE=�_�b�V���ł���@FALSE=�o���Ȃ�
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
 * PLAYER_SAVE_DATA����_�b�V���t���O���Z�b�g
 * @param	jikisave	PLAYER_SAVE_DATA *
 * @param	flag		TRUE=�_�b�V���ł��� FALSE=�o���Ȃ�
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
 * PLAYER_SAVE_DATA����M�A�^�C�v�擾
 * @param	jikisave	PLAYER_SAVE_DATA *
 * @retval	int			GEAR_3,GEAR4��
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
 * PLAYER_SAVE_DATA����M�A�^�C�v�Z�b�g
 * @param	jikisave	PLAYER_SAVE_DATA *
 * @param	gear		GEAR_3,GEAR4��
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
 * ���@����Z�[�u�f�[�^�M�A�Z�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	gear	GEAR_3��
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
 * ���@����Z�[�u�f�[�^�M�A�擾
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		GEAR_3��
 */
//--------------------------------------------------------------
int Player_SaveDataGetGearGet( PLAYER_STATE_PTR jiki )
{
	PLAYER_SAVE_DATA *save = Player_SaveDataPtrGet( jiki );
	return( Player_SaveDataGearCheck(save) );
}

//--------------------------------------------------------------
/**
 * PLAYER_SAVE_DATA���玩�@�`�Ԃ��擾
 * @param	jikisave	PLAYER_SAVE_DATA *
 * @retval	u32			HERO_FORM_NORMAL��
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
 * PLAYER_SAVE_DATA���玩�@�`�Ԃ��Z�b�g
 * @param	jikisave	PLAYER_SAVE_DATA *
 * @param	form		HERO_FORM_NORMAL��
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
 * ���@����Z�[�u�f�[�^�`�Ԃ��Z�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	form	HERO_FORM_NORMAL��
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
 * ���@����Z�[�u�f�[�^�`�Ԏ擾
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		GEAR_3��
 */
//--------------------------------------------------------------
u32 Player_SaveDataGetFormGet( PLAYER_STATE_PTR jiki )
{
	PLAYER_SAVE_DATA *save = Player_SaveDataPtrGet( jiki );
	return( Player_SaveDataFormGet(save) );
}

//==============================================================================
//	�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@���W�X�V	���݈ʒu�ōX�V
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
 * ���@���W�X�V	����
 * @param	jiki			PLAYER_STATE_PTR
 * @param	dir			�ړ��������
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_GPosAddDir( PLAYER_STATE_PTR jiki, int dir )
{
	FieldOBJ_NowGPosDirAdd( Player_FieldOBJGet(jiki), dir );
}

//--------------------------------------------------------------
/**
 * ���@���W�A�������������@FX32�^
 * @param	jiki	PLAYER_STATE_PTR
 * @param	vec		���������W
 * @param	dir		���� DIR_UP��
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
 * ���@���W�A������������ �O���b�h���W�^
 * @param	jiki	PLAYER_STATE_PTR
 * @param	x		�O���b�hX���W
 * @param	z		�O���b�hZ���W
 * @param	dir		���� DIR_UP��
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
 * ���@��Y���W���Z�b�g����B�����W��
 * @param	jiki	PLAYER_STATE_PTR
 * @param	y		����
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
 * ���@�̍��������擾��ON OFF���s��
 * @param	jiki	PLAYER_STATE_PTR
 * @param	flag	TRUE=�����擾�@FALSE=�擾���Ȃ�
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
 * ���@�̍��������擾��ON OFF���s���BON�̏ꍇ�͑����f
 * @param	jiki	PLAYER_STATE_PTR
 * @param	flag	TRUE=�����擾�@FALSE=�擾���Ȃ�
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
 * OBJ�R�[�h���琫�ʎ擾
 * @param	code	HERO��
 * @retval	int		PM_MALE��
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
 * �`�ԂƐ��ʂ��玩�@OBJ�R�[�h���擾
 * @param	form	HERO_FORM_NORMAL��
 * @param	sex		PM_MALE��
 * @retval	int		HERO��
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
	
	GF_ASSERT( 0 && "Player_FormSexOBJCodeGet() form�s��" );
	return( HERO );
}

//--------------------------------------------------------------
/**
 * �`�Ԃ��烊�N�G�X�g���擾
 * @param	form	HERO_FORM_NORMAL��
 * @retval	u32		HERO_REQBIT_NORMAL��
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
 * OBJ�R�[�h���玩�@�`�Ԃ��擾
 * @param	code	HERO��
 * @retval	int		HERO_FORM_NORMAL��
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
		
	GF_ASSERT( 0 && "Player_OBJCodeFormGet() code�s��" );
	return( HERO_FORM_NORMAL );
}

//--------------------------------------------------------------
/**
 * FIELDSYS_WORK����PLAYER_STATE_PTR�擾
 * @param	fsys	FIELDSYS_WORK *
 * @retval	PLAYER_STATE_PTR	PLAYER_STATE_PTR
 */
//--------------------------------------------------------------
PLAYER_STATE_PTR Player_FieldSysWorkPlayerGet( FIELDSYS_WORK *fsys )
{
	return( fsys->player );
}

//==============================================================================
//	���@����r�b�g
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@����r�b�g�@�����ړ��𑀍삷��
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
 * ���@����r�b�g�@�����ړ��`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=�����ړ���
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
 * ���@����r�b�g�@���������𑀍삷��
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
 * ���@����r�b�g�@���������`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=��������
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
 * ���@����r�b�g�@���]�ԃu���[�L�Z�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	flag	TRUE=�u���[�L�@FALSE=����
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
 * ���@����r�b�g�@���]�ԃu���[�L�`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=�u���[�L�A���@FALSE=�u���[�L����
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
 * ���@����r�b�g�@�T�C�N�����O���[�h�Z�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	flag	TRUE=�T�C�N�����O���[�h�@FALSE=����
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
 * ���@����r�b�g�@���]�ԃT�C�N�����O���[�h�`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=�T�C�N�����O���[�h�@FALSE=����
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
 * ���@����r�b�g�@�[�����𑀍삷��
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
 * ���@����r�b�g�@���]�ԃT�C�N�����O���[�h�`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=�T�C�N�����O���[�h�@FALSE=����
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
 * ���@����r�b�g�@�����ړ�
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
 * ���@����r�b�g�@�����ړ��`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=�����ړ�
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
 * ���@����r�b�g�@����ړ��Z�b�g
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
 * ���@����r�b�g�@����ړ�OFF
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
 * ���@����r�b�g�@����ړ�
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=����ړ�
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
 * ���@����r�b�g�@�����ړ��@���x�ۑ��Z�b�g
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
 * ���@����r�b�g�@�����ړ��@���x�ۑ��`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=ON
 */
//--------------------------------------------------------------
int Player_MoveBitCheck_ForceSaveSpeed( PLAYER_STATE_PTR jiki )
{
	return( Jiki_MoveBitCheck(jiki,JIKI_MOVE_BIT_FORCE_SAVE_SPEED) );
}
