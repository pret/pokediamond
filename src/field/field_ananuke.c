//******************************************************************************
/**
 *
 * @file	field_ananuke.c
 * @brief	�t�B�[���h�@���Ȃʂ��̂Ђ��@���Ȃق�@�e���|�[�g
 * @author	kagaya
 * @data	05.08.03
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"
#include "player.h"
#include "ev_mapchange.h"
#include "system/wipe.h"
#include "system/brightness.h"		//fieldmap.h�ł�ok
#include "field/situation_local.h"
#include "field_cutin.h"
#include "mapdata_warp.h"
#include "zonedata.h"
#include "field_zoom.h"

#include "field_ananuke.h"

#include "savedata/fnote_mem.h"
#include "system/snd_tool.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
///	����������֐��߂�l
//--------------------------------------------------------------
enum
{
	RET_NON = 0,	///<���ɖ���
	RET_CONT,		///<�ċA
	RET_END,		///<�I��
};

//--------------------------------------------------------------
///	�J�����Y�[��
//--------------------------------------------------------------
#define ANAZOOM_IN (NUM_FX32(-150))

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
//	ANA_WORK
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int acmd_count;
	ANATYPE ana_type;
	TCB_PTR tcb_acmd;
	TCB_PTR tcb_cutin;
	TCB_PTR tcb_zoom;
	FIELD_OBJ_PTR fldobj;
	FIELDSYS_WORK *fsys;
	POKEMON_PARAM *param;
}ANA_WORK;

//==============================================================================
//	static
//==============================================================================
int (* const DATA_AnaMoveTbl[])( GMEVENT_CONTROL *, FIELDSYS_WORK *, ANA_WORK * );

int (* const DATA_AnaInMoveTbl[])( GMEVENT_CONTROL *, FIELDSYS_WORK *, ANA_WORK * );

int (* const DATA_AnahoriMoveTbl[])( GMEVENT_CONTROL *, FIELDSYS_WORK *, ANA_WORK * );

static void * Anap_AllocMemory( u32 heap_id, u32 size );
static void AnaInMove_FnoteMake( FIELDSYS_WORK *fsys, ANA_WORK * work );

const FIELD_OBJ_ACMD_LIST DATA_AnaHeroAcmdTbl_0[];
const FIELD_OBJ_ACMD_LIST DATA_AnaHeroAcmdTbl_1[];
const FIELD_OBJ_ACMD_LIST DATA_AnaHeroAcmdTbl_2[];


//==============================================================================
//	���Ȃʂ��̂Ђ��@�E�o
//==============================================================================
//--------------------------------------------------------------
/**
 * �������̕R�g�p�C�x���g���[�N�Z�b�g
 * @param	fsys	FIELDSYS_WORK *
 * @param	heap_id	���[�N���m�ۂ���HEAP ID
 * @retval	void*	�������̕R�Ŏg�p����C�x���g���[�N *
 */
//--------------------------------------------------------------
void * EventWorkSet_AnanukeMapChange( FIELDSYS_WORK *fsys, u32 heap_id )
{
	ANA_WORK *work = Anap_AllocMemory( heap_id, sizeof(ANA_WORK) );
	work->ana_type = ANATYPE_ANA;
	work->fsys = fsys;
	work->fldobj = Player_FieldOBJGet( fsys->player );
	return( work );
}

//--------------------------------------------------------------
/**
 * �������̕R�g�p�C�x���g���}�b�v�J��
 * @param	event	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=�I��
 */
//--------------------------------------------------------------
BOOL GMEVENT_AnanukeMapChange( GMEVENT_CONTROL *event )
{
	int ret;
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	ANA_WORK *work = FieldEvent_GetSpecialWork( event );
	
	do{
		ret = DATA_AnaMoveTbl[work->seq_no]( event, fsys, work );
		
		if( ret == RET_END ){
			sys_FreeMemoryEz( work );
		}
	}while( ret == RET_CONT );
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �������@�J�n
 * @param	event	GMEVENT_CONTROL
 * @param	fsys	FIELDSYS_WORK
 * @param	work	ANA_WORK
 * @retval	int		RET_NON��
 */
//--------------------------------------------------------------
static int AnaMove_Start( GMEVENT_CONTROL *event, FIELDSYS_WORK *fsys, ANA_WORK *work )
{
	work->tcb_zoom = FieldZoom_Init( fsys, HEAPID_FIELD );
	FieldZoom_TypeChange( work->tcb_zoom, ZOOMTYPE_ZOOM, ANAZOOM_IN, 15 );
	
	work->tcb_acmd = FieldOBJ_AcmdListSet( work->fldobj, DATA_AnaHeroAcmdTbl_0 );
	work->seq_no++;
	
	switch( work->ana_type ){
	case ANATYPE_ANA:		Snd_SePlay( SE_ANANUKENOHIMO ); break;
	case ANATYPE_ANAHORI:	Snd_SePlay( SE_ANAWOHORU ); break;
	case ANATYPE_TEL:		Snd_SePlay( SE_TELEPORT ); break;
	}
	
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �������@���@�A�j���I���҂� 0
 * @param	event	GMEVENT_CONTROL
 * @param	fsys	FIELDSYS_WORK
 * @param	work	ANA_WORK
 * @retval	int		RET_NON��
 */
//--------------------------------------------------------------
static int AnaMove_JikiAnimeWait0( GMEVENT_CONTROL *event, FIELDSYS_WORK *fsys, ANA_WORK *work)
{
	if( FieldOBJ_AcmdListEndCheck(work->tcb_acmd) == FALSE ){
		return( RET_NON );
	}
	
	FieldOBJ_AcmdListEnd( work->tcb_acmd );
	work->tcb_acmd = FieldOBJ_AcmdListSet( work->fldobj, DATA_AnaHeroAcmdTbl_1 );
	work->acmd_count++;
	
	if( work->acmd_count < 8 ){
		return( RET_NON );
	}
	
	if( work->ana_type == ANATYPE_TEL ){
		WIPE_SYS_Start(
			WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
			WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD );
	}else{
		WIPE_SYS_Start(
			WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
			WIPE_TYPE_FADEOUT, WIPE_FADE_WHITE, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD );
	}
	
	work->seq_no++;
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �������@�t�F�[�h�A�E�g
 * @param	event	GMEVENT_CONTROL
 * @param	fsys	FIELDSYS_WORK
 * @param	work	ANA_WORK
 * @retval	int		RET_NON��
 */
//--------------------------------------------------------------
static int AnaMove_FadeOut( GMEVENT_CONTROL *event, FIELDSYS_WORK *fsys, ANA_WORK *work)
{
	if( FieldOBJ_AcmdListEndCheck(work->tcb_acmd) == TRUE ){
		FieldOBJ_AcmdListEnd( work->tcb_acmd );
		work->tcb_acmd = FieldOBJ_AcmdListSet( work->fldobj, DATA_AnaHeroAcmdTbl_1 );
	}
	
	if( WIPE_SYS_EndCheck() == 0 ){
		return( RET_NON );
	}
	
	FieldOBJ_AcmdListEnd( work->tcb_acmd );
	FieldZoom_Delete( work->tcb_zoom );
	work->seq_no++;
	return( RET_CONT );
}

//--------------------------------------------------------------
/**
 * �������@�I��
 * @param	event	GMEVENT_CONTROL
 * @param	fsys	FIELDSYS_WORK
 * @param	work	ANA_WORK
 * @retval	int		RET_NON��
 */
//--------------------------------------------------------------
static int AnaMove_End( GMEVENT_CONTROL *event, FIELDSYS_WORK *fsys, ANA_WORK *work )
{
	SITUATION *sit = SaveData_GetSituation( fsys->savedata );
	
	if( work->ana_type == ANATYPE_TEL ){
		u16 warp_id;
		LOCATION_WORK escape;
		warp_id = Situation_GetWarpID( sit );
		WARPDATA_GetWarpLocation( warp_id, &escape );
		EventChange_MapChangeByAnanuke( event, &escape, work->ana_type ); 
	}else{
		LOCATION_WORK *escape = Situation_GetEscapeLocation( sit );
		EventChange_MapChangeByAnanuke( event, escape, work->ana_type ); 
	}
	
	return( RET_END );
}

//--------------------------------------------------------------
///	�������@����e�[�u��
//--------------------------------------------------------------
static int (* const DATA_AnaMoveTbl[])( GMEVENT_CONTROL *, FIELDSYS_WORK *, ANA_WORK * ) =
{
	AnaMove_Start,
	AnaMove_JikiAnimeWait0,
	AnaMove_FadeOut,
	AnaMove_End,
};

//==============================================================================
//	���Ȃʂ��̂Ђ��@�o��
//==============================================================================
//--------------------------------------------------------------
/**
 * �������̕R�g�p��̏o���C�x���g���[�N�Z�b�g
 * @param	fsys	FIELDSYS_WORK *
 * @param	heap_id	���[�N���m�ۂ���HEAP ID
 * @param	type	ANATYPE
 * @retval	void*	�������̕R�Ŏg�p����C�x���g���[�N *
 */
//--------------------------------------------------------------
void * EventWorkSet_AnanukeMapIn( FIELDSYS_WORK *fsys, u32 heap_id, ANATYPE type )
{
	ANA_WORK *work = Anap_AllocMemory( heap_id, sizeof(ANA_WORK) );
	work->ana_type = type;
	work->fsys = fsys;
	work->fldobj = Player_FieldOBJGet( fsys->player );
	return( work );
}

//--------------------------------------------------------------
/**
 * �������̕R�g�p��}�b�v�o���C�x���g
 * @param	event	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=�I��
 */
//--------------------------------------------------------------
BOOL GMEVENT_AnanukeMapIn( GMEVENT_CONTROL *event )
{
	int ret;
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	ANA_WORK *work = FieldEvent_GetSpecialWork( event );
	
	do{
		ret = DATA_AnaInMoveTbl[work->seq_no]( event, fsys, work );
		
		if( ret == RET_END ){
			AnaInMove_FnoteMake( fsys, work );
			sys_FreeMemoryEz( work );
			return( TRUE );
		}
	}while( ret == RET_CONT );
	
	return( FALSE );
}

static void AnaInMove_FnoteMake( FIELDSYS_WORK * fsys, ANA_WORK * work )
{
	void * buf;

	if( work->ana_type == ANATYPE_TEL ){
		buf = FNOTE_ActionSkillDataMake( FNOTE_TELEPORT, fsys->location->zone_id, HEAPID_FIELD );
	}else{
		return;
	}
	FNOTE_DataSave( fsys->fnote, buf, FNOTE_TYPE_ACTION );
}



//--------------------------------------------------------------
/**
 * �������}�b�v�o���@�J�n
 * @param	event	GMEVENT_CONTROL
 * @param	fsys	FIELDSYS_WORK
 * @param	work	ANA_WORK
 * @retval	int		RET_NON��
 */
//--------------------------------------------------------------
static int AnaInMove_Start( GMEVENT_CONTROL *event, FIELDSYS_WORK *fsys, ANA_WORK *work )
{
	if( work->ana_type == ANATYPE_TEL ){
		WIPE_SYS_Start(
			WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
			WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD );
	}else{
		WIPE_SYS_Start(
			WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
			WIPE_TYPE_FADEIN, WIPE_FADE_WHITE, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD );
	}
	
	work->tcb_zoom = FieldZoom_Init( fsys, HEAPID_FIELD );
	FieldZoom_TypeChange( work->tcb_zoom, ZOOMTYPE_ZOOM, ANAZOOM_IN, 1 );
	
	work->tcb_acmd = FieldOBJ_AcmdListSet( work->fldobj, DATA_AnaHeroAcmdTbl_1 );
	work->seq_no++;
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �������}�b�v�o���@�z���C�g�C��
 * @param	event	GMEVENT_CONTROL
 * @param	fsys	FIELDSYS_WORK
 * @param	work	ANA_WORK
 * @retval	int		RET_NON��
 */
//--------------------------------------------------------------
static int AnaInMove_WhiteIn( GMEVENT_CONTROL *event, FIELDSYS_WORK *fsys, ANA_WORK *work)
{
	if( FieldOBJ_AcmdListEndCheck(work->tcb_acmd) == TRUE ){
		FieldOBJ_AcmdListEnd( work->tcb_acmd );
		work->tcb_acmd = FieldOBJ_AcmdListSet( work->fldobj, DATA_AnaHeroAcmdTbl_1 );
	}
	
	if( WIPE_SYS_EndCheck() == 0 ){
		return( RET_NON );
	}
	
	FieldZoom_TypeChange( work->tcb_zoom, ZOOMTYPE_BACK, 0, 60 );
	
	work->seq_no++;
	return( RET_CONT );
}

//--------------------------------------------------------------
/**
 * �������@���@�A�j���I���҂� 1
 * @param	event	GMEVENT_CONTROL
 * @param	fsys	FIELDSYS_WORK
 * @param	work	ANA_WORK
 * @retval	int		RET_NON��
 */
//--------------------------------------------------------------
static int AnaInMove_JikiAnimeWait0(GMEVENT_CONTROL *event, FIELDSYS_WORK *fsys, ANA_WORK *work)
{
	if( FieldOBJ_AcmdListEndCheck(work->tcb_acmd) == FALSE ){
		return( RET_NON );
	}
	
	FieldOBJ_AcmdListEnd( work->tcb_acmd );
	work->acmd_count++;
	
	if( work->acmd_count < 4 ){
		work->tcb_acmd = FieldOBJ_AcmdListSet( work->fldobj, DATA_AnaHeroAcmdTbl_1 );
		return( RET_NON );
	}
	
	work->tcb_acmd = FieldOBJ_AcmdListSet( work->fldobj, DATA_AnaHeroAcmdTbl_2 );
	work->seq_no++;
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * �������@���@�A�j���I���҂� 1
 * @param	event	GMEVENT_CONTROL
 * @param	fsys	FIELDSYS_WORK
 * @param	work	ANA_WORK
 * @retval	int		RET_NON��
 */
//--------------------------------------------------------------
static int AnaInMove_JikiAnimeWait1(GMEVENT_CONTROL *event, FIELDSYS_WORK *fsys, ANA_WORK *work)
{
	if( FieldOBJ_AcmdListEndCheck(work->tcb_acmd) == FALSE ){
		return( RET_NON );
	}
	
	if( FieldZoom_EndCheck(work->tcb_zoom) == FALSE ){
		return( RET_NON );
	}
	
	FieldZoom_Delete( work->tcb_zoom );
	FieldOBJ_AcmdListEnd( work->tcb_acmd );
	return( RET_END );
}

//--------------------------------------------------------------
///	�������@����e�[�u��
//--------------------------------------------------------------
static int (* const DATA_AnaInMoveTbl[])( GMEVENT_CONTROL *, FIELDSYS_WORK *, ANA_WORK * ) =
{
	AnaInMove_Start,
	AnaInMove_WhiteIn,
	AnaInMove_JikiAnimeWait0,
	AnaInMove_JikiAnimeWait1,
};

//==============================================================================
//	���Ȃ��ق�@�E�o
//	�J�b�g�C���Ăяo���������������
//==============================================================================
//--------------------------------------------------------------
/**
 * �����@��p�C�x���g���[�N�Z�b�g
 * @param	fsys	FIELDSYS_WORK *
 * @param	param	�J�b�g�C���ɕ\������POKEMON_PARAM
 * @param	heap_id	���[�N���m�ۂ���HEAP ID
 * @retval	void*	�����@��Ŏg�p����C�x���g���[�N *
 */
//--------------------------------------------------------------
void * EventWorkSet_AnawohoruMapChange( FIELDSYS_WORK *fsys, POKEMON_PARAM *param, u32 heap_id)
{
	ANA_WORK *work = Anap_AllocMemory( heap_id, sizeof(ANA_WORK) );
	work->ana_type = ANATYPE_ANAHORI;
	work->fsys = fsys;
	work->fldobj = Player_FieldOBJGet( fsys->player );
	work->param = param;
	return( work );
}

//--------------------------------------------------------------
/**
 * �����@��g�p�C�x���g���}�b�v�J��
 * @param	event	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=�I��
 */
//--------------------------------------------------------------
BOOL GMEVENT_AnawohoruMapChange( GMEVENT_CONTROL *event )
{
	int ret;
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	ANA_WORK *work = FieldEvent_GetSpecialWork( event );
	
	do{
		ret = DATA_AnahoriMoveTbl[work->seq_no]( event, fsys, work );
		
		if( ret == RET_END ){
			sys_FreeMemoryEz( work );
		}
	}while( ret == RET_CONT );
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���@��@�J�b�g�C���J�n
 * @param	event	GMEVENT_CONTROL
 * @param	fsys	FIELDSYS_WORK
 * @param	work	ANA_WORK
 * @retval	int		RET_NON��
 */
//--------------------------------------------------------------
static int AnahoriMove_CutInStart( GMEVENT_CONTROL *event, FIELDSYS_WORK *fsys, ANA_WORK *work )
{
	int sex = Player_SexGet( fsys->player );
	work->tcb_cutin = FieldCutIn_Init( fsys, CUTIN_TYPE_HIDEN, work->param, sex );
	work->seq_no++;
	return( RET_NON );
}

//--------------------------------------------------------------
/**
 * ���@��@�J�b�g�C���I���҂�
 * @param	event	GMEVENT_CONTROL
 * @param	fsys	FIELDSYS_WORK
 * @param	work	ANA_WORK
 * @retval	int		RET_NON��
 */
//--------------------------------------------------------------
static int AnahoriMove_CutInWait( GMEVENT_CONTROL *event, FIELDSYS_WORK *fsys, ANA_WORK *work )
{
	if( FieldCutIn_EndCheck(work->tcb_cutin) == FALSE ){
		return( RET_NON );
	}
	
	FieldCutIn_End( work->tcb_cutin );
	work->seq_no++;
	return( RET_CONT );
}

//--------------------------------------------------------------
///	���@��@����e�[�u��
//--------------------------------------------------------------
static int (* const DATA_AnahoriMoveTbl[])( GMEVENT_CONTROL *, FIELDSYS_WORK *, ANA_WORK * ) =
{
	AnahoriMove_CutInStart,
	AnahoriMove_CutInWait,
	AnaMove_Start,
	AnaMove_JikiAnimeWait0,
	AnaMove_FadeOut,
	AnaMove_End,
};

//==============================================================================
//	�e���|�[�g
//	�����암���͌��@��
//==============================================================================
//--------------------------------------------------------------
/**
 * �e���|�[�g�p�C�x���g���[�N�Z�b�g
 * @param	fsys	FIELDSYS_WORK *
 * @param	param	�J�b�g�C���ɕ\������POKEMON_PARAM
 * @param	heap_id	���[�N���m�ۂ���HEAP ID
 * @retval	void*	�e���|�[�g�Ŏg�p����C�x���g���[�N *
 */
//--------------------------------------------------------------
void * EventWorkSet_TeleportMapChange( FIELDSYS_WORK *fsys, POKEMON_PARAM *param, u32 heap_id)
{
	ANA_WORK *work = Anap_AllocMemory( heap_id, sizeof(ANA_WORK) );
	work->ana_type = ANATYPE_TEL;
	work->fsys = fsys;
	work->fldobj = Player_FieldOBJGet( fsys->player );
	work->param = param;
	return( work );
}

//--------------------------------------------------------------
/**
 * �e���|�[�g�g�p�C�x���g���}�b�v�J��
 * @param	event	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=�I��
 */
//--------------------------------------------------------------
BOOL GMEVENT_TeleportMapChange( GMEVENT_CONTROL *event )
{
	int ret;
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	ANA_WORK *work = FieldEvent_GetSpecialWork( event );
	
	do{
		ret = DATA_AnahoriMoveTbl[work->seq_no]( event, fsys, work );
		
		if( ret == RET_END ){
			sys_FreeMemoryEz( work );
		}
	}while( ret == RET_CONT );
	
	return( FALSE );
}

//==============================================================================
//	�������@�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * ���[�N�m��
 * @param	heap_id		�q�[�vID
 * @param	size		�m�ۃT�C�Y
 * @retval	void*		�m�ۂ����̈�
 */
//--------------------------------------------------------------
static void * Anap_AllocMemory( u32 heap_id, u32 size )
{
	void *mem = sys_AllocMemoryLo( heap_id, size );
	GF_ASSERT( mem != NULL && "Ana_AllocMemory() heap error" );
	memset( mem, 0, size );
	return( mem );
}

#if 0		//�I�[�o�[���C�ŃA�N�Z�X�s�ɂȂ�̂ŁA�폜	20060712 saito
//--------------------------------------------------------------
/**
 * �������@���@�肪�o���邩�ǂ���
 * @param	zone_id	�]�[��ID
 * @retval	BOOL	TRUE=�\ FALSE=�s��
 */
//--------------------------------------------------------------
BOOL EventCheck_Ananuke( int zone_id )
{
	if( ZoneData_IsDungeon(zone_id) == TRUE &&
		ZoneData_GetEnableEscapeFlag(zone_id) == TRUE ){
		return( TRUE );
	}
	
	return( FALSE );
}
#endif

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
//	�������@���@�A�j�� 0
//--------------------------------------------------------------
static const FIELD_OBJ_ACMD_LIST DATA_AnaHeroAcmdTbl_0[] =
{
	{ AC_DIR_D, 1 },{ AC_WAIT_1F, 2 },	//0
	{ AC_DIR_L, 1 },{ AC_WAIT_1F, 2 },
	{ AC_DIR_U, 1 },{ AC_WAIT_1F, 2 },
	{ AC_DIR_R, 1 },{ AC_WAIT_1F, 2 },
	{ AC_DIR_D, 1 },{ AC_WAIT_1F, 1 },	//1
	{ AC_DIR_L, 1 },{ AC_WAIT_1F, 1 },
	{ AC_DIR_U, 1 },{ AC_WAIT_1F, 1 },
	{ AC_DIR_R, 1 },{ AC_WAIT_1F, 1 },
	{ AC_DIR_D, 1 },					//2
	{ AC_DIR_L, 1 },
	{ AC_DIR_U, 1 },
	{ AC_DIR_R, 1 },
	{ AC_DIR_D, 1 },					//3
	{ AC_DIR_L, 1 },
	{ AC_DIR_U, 1 },
	{ AC_DIR_R, 1 },
	{ ACMD_END, 0 },
};

//--------------------------------------------------------------
//	�������@���@�A�j�� 1
//--------------------------------------------------------------
static const FIELD_OBJ_ACMD_LIST DATA_AnaHeroAcmdTbl_1[] =
{
	{ AC_DIR_U, 1 },
	{ AC_DIR_R, 1 },
	{ AC_DIR_D, 1 },
	{ AC_DIR_L, 1 },
	{ ACMD_END, 0 },
};

//--------------------------------------------------------------
///	�������@���@�A�j�� 2
//--------------------------------------------------------------
static const FIELD_OBJ_ACMD_LIST DATA_AnaHeroAcmdTbl_2[] =
{
	{ AC_DIR_D, 1 },					//0
	{ AC_DIR_L, 1 },
	{ AC_DIR_U, 1 },
	{ AC_DIR_R, 1 },
	{ AC_DIR_D, 1 },					//1
	{ AC_DIR_L, 1 },
	{ AC_DIR_U, 1 },
	{ AC_DIR_R, 1 },
	{ AC_DIR_D, 1 },{ AC_WAIT_1F, 1 },	//2
	{ AC_DIR_L, 1 },{ AC_WAIT_1F, 1 },
	{ AC_DIR_U, 1 },{ AC_WAIT_1F, 1 },
	{ AC_DIR_R, 1 },{ AC_WAIT_1F, 1 },
	{ AC_DIR_D, 1 },{ AC_WAIT_1F, 2 },	//3
	{ AC_DIR_L, 1 },{ AC_WAIT_1F, 3 },
	{ AC_DIR_U, 1 },{ AC_WAIT_1F, 4 },
	{ AC_DIR_R, 1 },{ AC_WAIT_1F, 5 },
	
	{ AC_DIR_D, 1 },
	{ ACMD_END, 0 },
};
