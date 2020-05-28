//******************************************************************************
/**
 *
 * @file	field_fishing.c
 * @brief	�t�B�[���h�@�C�x���g�@�ނ�
 * @author	kagaya
 * @data	05.08.03
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"
#include "fieldmap.h"
#include "player.h"
#include "field_event.h"
#include "talk_msg.h"
#include "script.h"
#include "field_effect.h"
#include "system\window.h"
#include "field_encount.h"
#include "encount_set.h"
#include "field_battle.h"
#include "field_fishing.h"
#include "tv_topic.h"

#include "msgdata\msg_common_scr.h"
#include "msgdata\msg.naix"

#include "savedata\record.h"

#include "system/snd_tool.h"

#include "itemtool/itemsym.h"

//==============================================================================
//	define
//==============================================================================
///�ނ蓮�� TCB�v���C�I���e�B
#define TCBPRI_FISHING	(128)

//--------------------------------------------------------------
///	�ނ蓮��V�[�P���X
//--------------------------------------------------------------
enum
{
	SEQNO_FISH_INIT = 0,
	
	SEQNO_FISH_START_JIKI_MOVE_END_WAIT,
	SEQNO_FISH_JIKI_START_ANIME_WAIT,
	
	SEQNO_FISH_ON_START,
	SEQNO_FISH_ON_COUNT,
	SEQNO_FISH_ON_TURIAGE,
	SEQNO_FISH_ON_HIT,
	SEQNO_FISH_ON_HIT_ANIME_WAIT,
	SEQNO_FISH_ON_HIT_MSG_WAIT,
	SEQNO_FISH_ON_HIT_END,
	
	SEQNO_FISH_HAYASUGI_START,
	SEQNO_FISH_NIGERARETA_START,
	
	SEQNO_FISH_NOHIT_START,
	SEQNO_FISH_NOHIT_WAIT,
	
	SEQNO_FISH_MISS_MSG_WAIT,
	
	SEQNO_FISH_DELETE,
	SEQNO_FISH_JIKI_FORM_BACK_WAIT,
	SEQNO_FISH_END,
};

//--------------------------------------------------------------
///	���b�Z�[�WID
//--------------------------------------------------------------
#define MSGFISH_TURENAI 	msg_fishing_01
#define MSGFISH_NIGERARETA	msg_fishing_02
#define MSGFISH_HAYASUGI	msg_fishing_03
#define MSGFISH_TURIAGETA	msg_fishing_04

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	EVFISHWORK GMEVENT_Fishing()����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	u32 rod_item_no;
	BOOL hit;
	FISHINGROD_TYPE rod_type;
	BATTLE_PARAM *bt_param;
	TCB_PTR tcb;
}EVFISHWORK;

//--------------------------------------------------------------
///	FISHWORK
//--------------------------------------------------------------
typedef struct
{
	BOOL hit;
	int end_flag;
	int result;
	int seq_no;
	int frame;
	int fishon_frame;
	int turiage_frame;
	FISHINGROD_TYPE rod_type;
	FIELDSYS_WORK *fsys;
	EOA_PTR eoa_gyoe;
	
	u8 msg_index;
	STRBUF *pbuf;
	STRBUF *ptmp;
	WORDSET *wordset;
	GF_BGL_BMPWIN msgwindat;
	MSGDATA_MANAGER *msgman;
}FISHWORK;

//==============================================================================
//	static
//==============================================================================
static void Fish_TCBUpdate( TCB_PTR tcb, void *wk );

int (* const DATA_FishMoveTbl[])(
	FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj );

static void * Fish_AllocMemory( u32 size );
static int Fish_AButtonPushCheck( void );
static int Fish_ABButtonPushCheck( void );

static void Fish_MsgManInit( FISHWORK *work );
static void Fish_MsgManDelete( FISHWORK *work );
static void Fish_MsgWinPut( FISHWORK *work );
static void Fish_TalkMsgStart( FISHWORK *work, u32 msg_id );
static int Fish_TalkMsgEndCheck( FISHWORK *work );

static u16 Fish_RodItemNoGet( FISHINGROD_TYPE type );

const int DATA_TuriageFrameTbl[];

//==============================================================================
//	�ނ�@�C�x���g�Ăяo��
//==============================================================================
//--------------------------------------------------------------
/**
 * �ނ�C�x���g�p���[�N�Z�b�g
 * @param	fsys		FIELDSYS_WORK *
 * @param	heap_id		���[�N���m�ۂ���q�[�vID
 * @param	type		FISHINGROD_TYPE
 * @retval	void*		�ނ�C�x���g���[�N *
 */
//--------------------------------------------------------------
void * EventWorkSet_Fishing( FIELDSYS_WORK *fsys, u32 heap_id, FISHINGROD_TYPE type )
{
	EVFISHWORK *work = sys_AllocMemoryLo( heap_id, sizeof(EVFISHWORK) );
	memset( work, 0, sizeof(EVFISHWORK) );
	work->rod_type = type;
	
	work->rod_item_no = Fish_RodItemNoGet(type);
	
	return( work );
}

//--------------------------------------------------------------
/**
 * �ނ�C�x���g
 * @param	event	GMEVENT_CONTROL *
 * @retval	int		TRUE=�I��
 */
//--------------------------------------------------------------
BOOL GMEVENT_Fishing( GMEVENT_CONTROL *event )
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	EVFISHWORK *work = FieldEvent_GetSpecialWork( event );
	
	switch( work->seq_no ){
	case 0:
		//�t�B�[���h�n�a�i�S�̃|�[�Y
		FieldOBJSys_MovePauseAll( fsys->fldobjsys );
		work->bt_param = NULL;
		work->hit = SetFishingEncount( fsys, work->rod_type, &work->bt_param );
		work->tcb = FieldFishing_Init( fsys, work->rod_type, work->hit );
		work->seq_no++;
		break;
	case 1:
		if( FieldFishing_EndCheck(work->tcb) == TRUE ){
			int result = FieldFishing_ResultGet( work->tcb );
			FieldFishing_Delete( work->tcb );
			
			if( result == TRUE ){	//�q�b�g���͒ނ��Ԃ̂܂�->�q�b�g���ɏ�Ԗ߂�060726
#if 0
				{
					PLAYER_STATE_PTR jiki = fsys->player;
					int form = Player_FormGet( jiki );
					u32 req_bit = Player_FormRequestGet( form );
					Player_RequestSet( jiki, req_bit );
				}
#endif				
				{
					POKEMON_PARAM *pp = PokeParty_GetMemberPointer(
							work->bt_param->poke_party[POKEPARTY_ENEMY], 0 );
					TVTOPIC_Entry_Watch_Fishing( fsys, TRUE, work->rod_item_no, pp );
				}
				
				{
					RECORD *rc = SaveData_GetRecord( fsys->savedata );
					RECORD_Inc( rc, RECID_FISHING_SUCCESS );
				}
				
				FieldEncount_Change( fsys, event, work->bt_param );
				sys_FreeMemoryEz( work );
				return( FALSE );
			}
			
			if( work->bt_param != NULL ){
				BattleParam_Delete( work->bt_param );
			}
			
			//�t�B�[���h�n�a�i�S�̃|�[�Y����
			FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
			sys_FreeMemoryEz( work );
			return( TRUE );
		}
		
		break;
	}
	
	return( FALSE );
}

//==============================================================================
//	�ނ�
//==============================================================================
//--------------------------------------------------------------
/**
 * �ނ�J�n
 * @param	fsys		FIELDSYS_WORK *
 * @param	type		FISHINGROD_TYPE
 * @retval	TCB_PTR		�ނ蓮��TCB_PTR
 */
//--------------------------------------------------------------
TCB_PTR FieldFishing_Init( FIELDSYS_WORK *fsys, FISHINGROD_TYPE type, BOOL hit )
{
	TCB_PTR tcb;
	FISHWORK *work = Fish_AllocMemory( sizeof(FISHWORK) );
	work->fsys = fsys;
	work->rod_type = type;
	work->hit = hit;
	
	tcb = TCB_Add( Fish_TCBUpdate, work, TCBPRI_FISHING );
	return( tcb );
}

//--------------------------------------------------------------
/**
 * �ނ�I���`�F�b�N
 * @param	tcb			FieldFishing_Init()�߂�l
 * @retval	int			TRUE=�I��
 */
//--------------------------------------------------------------
int FieldFishing_EndCheck( TCB_PTR tcb )
{
	FISHWORK *work = TCB_GetWork( tcb );
	return( work->end_flag );
}

//--------------------------------------------------------------
/**
 * �ނ萬�ێ擾�@FieldFishing_EndCheck()��ɌĂ�
 * @param	tcb			FieldFishing_Init()�߂�l
 * @retval	int			TRUE=���� FALSE=���s
 */
//--------------------------------------------------------------
int FieldFishing_ResultGet( TCB_PTR tcb )
{
	FISHWORK *work = TCB_GetWork( tcb );
	return( work->result );
}

//--------------------------------------------------------------
/**
 * �ނ�I��
 * @param	tcb			FieldFishing_Init()�߂�l
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldFishing_Delete( TCB_PTR tcb )
{
	FISHWORK *work = TCB_GetWork( tcb );
	sys_FreeMemoryEz( work );
	TCB_Delete( tcb );
}

//==============================================================================
//	�ނ蓮��
//==============================================================================
//--------------------------------------------------------------
/**
 * �ނ蓮�� tcb
 * @param	tcb		TCB_PTR
 * @param	wk		FISHWORK
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Fish_TCBUpdate( TCB_PTR tcb, void *wk )
{
	FISHWORK *work = wk;
	PLAYER_STATE_PTR jiki = work->fsys->player;
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	
	while( DATA_FishMoveTbl[work->seq_no](work,jiki,fldobj) ){};
}

//--------------------------------------------------------------
/**
 * �ނ�@������
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_Init(
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	Fish_MsgManInit( work );
	FieldOBJ_MovePauseClear( fldobj );
	work->seq_no = SEQNO_FISH_START_JIKI_MOVE_END_WAIT;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �ނ�@�ނ�J�n�A���@����I���҂�
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_StartJikiMoveEndWait(
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_AcmdSetCheck(fldobj) == TRUE ){
		FieldOBJ_AcmdEnd( fldobj );
		Player_RequestSet( jiki, HERO_REQBIT_FISHING );
		Player_Request( jiki );
		FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_FISH_START );
		work->seq_no = SEQNO_FISH_JIKI_START_ANIME_WAIT;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �ނ�@�ނ�J�n�A���@�ނ�A�j���I���҂�
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_JikiFishStartAnimeWait(
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	work->frame++;
	
	if( work->frame == 10 ){
		Snd_SePlay( SE_FISHING );
	}

	if( work->frame < 34 ){
		return( FALSE );
	}
	
	if( work->hit == TRUE ){
		work->seq_no = SEQNO_FISH_ON_START;
	}else{
		work->seq_no = SEQNO_FISH_NOHIT_START;
	}
	
	work->frame = 0;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �ނ�@�q�b�g�@�J�n
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_JikiFishONStart(
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	work->fishon_frame = ((gf_rand() % 4) + 1) * 30;			//30 = 1 frame
	work->turiage_frame = DATA_TuriageFrameTbl[work->rod_type];
	work->seq_no = SEQNO_FISH_ON_COUNT;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �ނ�@�J�E���g
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_JikiFishONCount(
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	work->fishon_frame--;
	
	if( Fish_AButtonPushCheck() == TRUE ){
		work->seq_no = SEQNO_FISH_HAYASUGI_START;
		return( TRUE );
	}
	
	if( work->fishon_frame > 0 ){
		return( FALSE );
	}
	
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_FISH_ON );
	work->eoa_gyoe = FE_FldOBJGyoe_Add( fldobj, GYOE_GYOE, TRUE );
	work->seq_no = SEQNO_FISH_ON_TURIAGE;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �ނ�@�݂�グ
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_JikiFishONTuriage(
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	work->turiage_frame--;
	
	if( Fish_AButtonPushCheck() == TRUE ){
		work->seq_no = SEQNO_FISH_ON_HIT;
		return( TRUE );
	}
	
	if( work->turiage_frame > 0 ){
		return( FALSE );
	}
	
	work->seq_no = SEQNO_FISH_NIGERARETA_START;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �ނ�@�݂�グ����
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_JikiFishONHit(
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	EOA_Delete( work->eoa_gyoe );
	work->eoa_gyoe = NULL;
	
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_FISH_HIT );
	work->frame = 0;
	work->seq_no = SEQNO_FISH_ON_HIT_ANIME_WAIT;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �ނ�@�݂�グ�����A�j���I���҂�
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_JikiFishONHitAnimeWait(
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	work->frame++;
	
	if( work->frame > 15 ){
		work->frame = 0;
		work->seq_no = SEQNO_FISH_ON_HIT_MSG_WAIT;
		Fish_TalkMsgStart( work, MSGFISH_TURIAGETA );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �ނ�@�݂�グ�������b�Z�[�W�\���҂�
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_JikiFishONHitMsgWait(
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	if( Fish_TalkMsgEndCheck(work) == FALSE ){
		return( FALSE );
	}
	
	work->seq_no = SEQNO_FISH_ON_HIT_END;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �ނ�@�݂�グ�����@�I��
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_JikiFishONHitEnd(
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	work->result = TRUE;
	work->seq_no = SEQNO_FISH_DELETE;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �ނ�@�������J�n
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_HayasugiStart( 
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_FISH_END );
	Fish_TalkMsgStart( work, MSGFISH_HAYASUGI );
	work->frame = 16;
	work->seq_no = SEQNO_FISH_MISS_MSG_WAIT;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �ނ�@������ꂽ�J�n
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_NigeStart( 
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_FISH_END );
	Fish_TalkMsgStart( work, MSGFISH_NIGERARETA );
	work->frame = 16;
	work->seq_no = SEQNO_FISH_MISS_MSG_WAIT;
	
	{
		RECORD *rc = SaveData_GetRecord( work->fsys->savedata );
		RECORD_Inc( rc, RECID_FISHING_FAILURE );
	}
	//�莸�s�e���r�g�s�b�N�쐬
	TVTOPIC_Entry_Watch_Fishing( work->fsys, FALSE,
			Fish_RodItemNoGet(work->rod_type), NULL);
	
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �ނ�@��Ȃ��J�n
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_JikiFishNoHitStart( 
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	work->frame = 30 * 4;
	work->seq_no = SEQNO_FISH_NOHIT_WAIT;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �ނ�@��Ȃ��҂�
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_JikiFishNoHitWait( 
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	work->frame--;
	
	if( Fish_AButtonPushCheck() == TRUE ){
		work->seq_no = SEQNO_FISH_HAYASUGI_START;
		return( TRUE );
	}
	
	if( work->frame ){
		return( FALSE );
	}
	
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_FISH_END );
	Fish_TalkMsgStart( work, MSGFISH_TURENAI ); 
	
	work->frame = 16;
	work->seq_no = SEQNO_FISH_MISS_MSG_WAIT;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �ނ�@�~�X���b�Z�[�W�\���҂��@���s�n����
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_JikiFishMissMsgWait( 
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	work->frame++;
	
	if( work->frame < 16 ){
		return( FALSE );
	}
	
	work->frame = 16;
	
	if( Fish_TalkMsgEndCheck(work) == FALSE ){
		return( FALSE );
	}
	
	work->seq_no = SEQNO_FISH_DELETE;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �ނ�@�폜
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_Delete(
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	if( work->eoa_gyoe != NULL ){
		EOA_Delete( work->eoa_gyoe );
		work->eoa_gyoe = NULL;
	}
	
	Fish_MsgManDelete( work );
	
	{
		int form = Player_FormGet( jiki );
		u32 req_bit = Player_FormRequestGet( form );
		Player_RequestSet( jiki, req_bit );
		Player_Request( jiki );
	}
	
	work->frame = 0;
	work->seq_no = SEQNO_FISH_JIKI_FORM_BACK_WAIT;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �ނ�@���@��߂�
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_JikiFormBackWait(
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	work->frame++;
	
	if( work->frame > 2 ){
		work->seq_no = SEQNO_FISH_END;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �ނ�@�I��
 * @param	work	FISHWORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	���@FIELD_OBJ_PTR
 * @retval	int		TRUE=�ċA�v��
 */
//--------------------------------------------------------------
static int FishMove_End(
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	work->end_flag = TRUE;
	return( FALSE );
}

//--------------------------------------------------------------
///	����e�[�u��
//--------------------------------------------------------------
static int (* const DATA_FishMoveTbl[])(
		FISHWORK *work, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj ) =
{
	FishMove_Init,
	
	FishMove_StartJikiMoveEndWait,
	FishMove_JikiFishStartAnimeWait,
	
	FishMove_JikiFishONStart,
	FishMove_JikiFishONCount,
	FishMove_JikiFishONTuriage,
	FishMove_JikiFishONHit,
	FishMove_JikiFishONHitAnimeWait,
	FishMove_JikiFishONHitMsgWait,
	FishMove_JikiFishONHitEnd,
	
	FishMove_HayasugiStart,
	FishMove_NigeStart,
	
	FishMove_JikiFishNoHitStart,
	FishMove_JikiFishNoHitWait,
	
	FishMove_JikiFishMissMsgWait,
	
	FishMove_Delete,
	FishMove_JikiFormBackWait,
	FishMove_End,
};

//==============================================================================
//	�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * �ނ�p�̈�m��
 * @param	size	�m�ۂ���T�C�Y	
 * @retval	void*	�m�ۂ����̈�
 */
//--------------------------------------------------------------
static void * Fish_AllocMemory( u32 size )
{
	void *alloc = sys_AllocMemoryLo( HEAPID_FIELD, size );
	GF_ASSERT( alloc != NULL );
	memset( alloc, 0, size );
	return( alloc );
}

//--------------------------------------------------------------
/**
 * A�{�^�����͎擾
 * @param	nothing	
 * @retval	int		TRUE=A�������ꂽ
 */
//--------------------------------------------------------------
static int Fish_AButtonPushCheck( void )
{
	if( (sys.trg & PAD_BUTTON_A) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * A�{�^�����͎擾
 * @param	nothing	
 * @retval	int		TRUE=A�������ꂽ
 */
//--------------------------------------------------------------
static int Fish_ABButtonPushCheck( void )
{
	if( (sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B)) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//==============================================================================
//	���b�Z�[�W�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * ���b�Z�[�W�}�l�[�W��������
 * @param	work	FISHWORK
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Fish_MsgManInit( FISHWORK *work )
{
	FIELDSYS_WORK *fsys = work->fsys;
	
	work->msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, 
								NARC_msg_common_scr_dat, HEAPID_FIELD ); 
	work->pbuf = STRBUF_Create( 0x0400, HEAPID_FIELD );
	work->ptmp = STRBUF_Create( 0x0400, HEAPID_FIELD );
	work->wordset = WORDSET_CreateEx( 8, 64, HEAPID_FIELD );
}

//--------------------------------------------------------------
/**
 * ���b�Z�[�W�}�l�[�W���폜
 * @param	work	FISHWORK
 * @retval	int		TRUE=�I��
 */
//--------------------------------------------------------------
static void Fish_MsgManDelete( FISHWORK *work )
{
	WORDSET_Delete( work->wordset );
	STRBUF_Delete( work->pbuf );
	STRBUF_Delete( work->ptmp );
	MSGMAN_Delete( work->msgman );
}

//--------------------------------------------------------------
/**
 * ���b�Z�[�W�E�B���h�E�`��
 * @param	work	
 * @retval
 */
//--------------------------------------------------------------
static void Fish_MsgWinPut( FISHWORK *work )
{
	FIELDSYS_WORK *fsys = work->fsys;
	FldTalkBmpAdd( fsys->bgl, &work->msgwindat, FLD_MBGFRM_FONT );
	FieldTalkWinPut( &work->msgwindat, SaveData_GetConfig(fsys->savedata) );
}

//--------------------------------------------------------------
/**
 * ���b�Z�[�W�\��
 * @param	work	
 * @retval
 */
//--------------------------------------------------------------
static void Fish_TalkMsgStart( FISHWORK *work, u32 msg_id )
{
	Fish_MsgWinPut( work );
	
	{
		FIELDSYS_WORK *fsys = work->fsys;
		MSGMAN_GetString( work->msgman, msg_id, work->ptmp );
		WORDSET_ExpandStr( work->wordset, work->pbuf, work->ptmp );
		work->msg_index = FieldTalkMsgStart( &work->msgwindat, work->pbuf, 
				SaveData_GetConfig(fsys->savedata), TRUE );
	}
}

//--------------------------------------------------------------
/**
 * ���b�Z�[�W�I���҂�
 * @param	work	FISHWORK
 * @retval	int		TRUE=�I��
 */
//--------------------------------------------------------------
static int Fish_TalkMsgEndCheck( FISHWORK *work )
{
	if( FldTalkMsgEndCheck(work->msg_index) == 1 && Fish_ABButtonPushCheck() == TRUE ){
		BmpTalkWinClear( &work->msgwindat, WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &work->msgwindat );
		return( TRUE );
	}
	
	return( FALSE );
}

//==============================================================================
//	�A�C�e���i���o�[�ϊ�
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief	type	FISHINGROD_TYPE
 * @return	u16		type�ɑΉ������A�C�e���i���o�[
 */
//--------------------------------------------------------------
static u16 Fish_RodItemNoGet( FISHINGROD_TYPE type )
{
	switch( type ){
	default:
		GF_ASSERT(0);
	case FISHINGROD_BAD:	return ITEM_BORONOTURIZAO;
	case FISHINGROD_GOOD:	return ITEM_IITURIZAO;
	case FISHINGROD_GREAT:	return ITEM_SUGOITURIZAO;
	}
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	�ފƕʁ@�݂�グ�t���[��
//--------------------------------------------------------------
static const int DATA_TuriageFrameTbl[] =
{
	45,	//1.5
	30,	//1
	15,	//0.5
};

//==============================================================================
//	debug
//==============================================================================

