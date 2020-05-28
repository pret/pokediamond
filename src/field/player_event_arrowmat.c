//******************************************************************************
/**
 *
 * @file	player_event_arrowmat.c
 * @brief	���@�C�x���g �ړ���
 * @author	k.ohno
 * @data	06.06.20
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"
#include "player.h"
#include "field_event.h"
#include "system/snd_tool.h"
#include "fld_bgm.h"
#include "field_cutin.h"

#include "player_event_arrowmat.h"

//==============================================================================
//	define
//==============================================================================
//#define DEBUG_KABE_COUNT

//--------------------------------------------------------------
//	�ċA�v��
//--------------------------------------------------------------
#define RET_FALSE	(FALSE)
#define RET_TRUE	(TRUE)
#define RET_AGAIN	(TRUE+1)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	�ړ����\����
//--------------------------------------------------------------
typedef struct
{
    int dir;
    int count;
    int seq_no;
	FIELDSYS_WORK *fsys;
	PLAYER_STATE_PTR jiki;
	FIELD_OBJ_PTR fldobj;
}ARROWMAT_WORK;

#define ARROWMAT_WORK_SIZE (sizeof(ARROWMAT_WORK))


//==============================================================================
//	static
//==============================================================================

static void JikiEvent_ArrowMatSet( FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki,int matDir );
static BOOL JikiEvent_ArrowMat( GMEVENT_CONTROL *ev );

static void * Jiki_EventWorkAlloc( int size );
static void Jiki_EventWorkFree( void *work );


//==============================================================================
//	�����}�b�g
//==============================================================================
//--------------------------------------------------------------
/**
 * �����}�b�g�`�F�b�N
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�i�s���� DIR_UP��
 * @retval	int		TRUE=�����}�b�g�C�x���g����
 */
//--------------------------------------------------------------
int JikiEventCheck_ArrowMat(
    FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir )
{
    FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
    MATR attr = FieldOBJ_NowMapAttrGet( fldobj );
    int matDir;
    
    if( MATR_IsForceMoveRight(attr) == TRUE ){
        matDir = DIR_RIGHT;
    }
    else if( MATR_IsForceMoveLeft(attr) == TRUE ){
        matDir = DIR_LEFT;
    }
    else if( MATR_IsForceMoveUp(attr) == TRUE ){
        matDir = DIR_UP;
    }
    else if( MATR_IsForceMoveDown(attr) == TRUE ){
        matDir = DIR_DOWN;
    }
    else{
        return FALSE;
    }
	
	JikiEvent_ArrowMatSet( fsys, jiki, matDir );
	return TRUE;
}

//--------------------------------------------------------------
/**
 * �������C�x���g����
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiEvent_ArrowMatSet( FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki,int matDir )
{
	ARROWMAT_WORK *work = Jiki_EventWorkAlloc( ARROWMAT_WORK_SIZE );
	
	work->fsys = fsys;
	work->jiki = jiki;
    work->dir = matDir;
    Snd_SePlay( SE_YAZIRUSI_FLOOR );
	FieldEvent_Set( fsys, JikiEvent_ArrowMat, work );
}

//--------------------------------------------------------------
/**
 * ���̉�]�����𓾂�
 * @param	dir
 * @retval	dir
 */
//--------------------------------------------------------------

static int _nextDir(int dir)
{
    switch(dir){
      case DIR_UP:
        return DIR_LEFT;
      case DIR_LEFT:
        return DIR_DOWN;
      case DIR_DOWN:
        return DIR_RIGHT;
      case DIR_RIGHT:
        return DIR_UP;
    }
    return DIR_UP;
}


//--------------------------------------------------------------
/**
 * �������C�x���g
 * @param ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=�C�x���g�I��
 */
//--------------------------------------------------------------
static BOOL JikiEvent_ArrowMat( GMEVENT_CONTROL *ev )
{
	ARROWMAT_WORK *work = FieldEvent_GetSpecialWork( ev );
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( work->jiki );
    MATR attr = FieldOBJ_NowMapAttrGet( fldobj );

    typedef enum{
        _MOVE_INIT,
        _MOVE_START,
        _MOVE_CHECK,
    };

	switch( work->seq_no ){
	case _MOVE_INIT:
        FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_ANM );
		work->seq_no++;
        break;
	case _MOVE_START:
        if( Player_AcmdSetCheck(work->jiki)){
            int code = AC_WALK_U_8F;
			code = FieldOBJ_AcmdCodeDirChange( work->dir, code );
			Player_AcmdSet( work->jiki, code );
            Player_DirSet(work->jiki,work->dir);
            work->seq_no++;
            work->count = 7;
		}
		break;
	case _MOVE_CHECK:
        switch(work->count){
          case 6:
          case 4:
          case 2:
            work->dir = _nextDir(work->dir);
            Player_DirSet(work->jiki,work->dir);
            break;
          default:
            break;
        }
        work->count--;
        if(work->count==0){
            if( MATR_IsForceMoveRight(attr) == TRUE ){
                work->dir = DIR_RIGHT;
            }
            else if( MATR_IsForceMoveLeft(attr) == TRUE ){
                work->dir = DIR_LEFT;
            }
            else if( MATR_IsForceMoveUp(attr) == TRUE ){
                work->dir = DIR_UP;
            }
            else if( MATR_IsForceMoveDown(attr) == TRUE ){
                work->dir = DIR_DOWN;
            }
            else{
                work->dir = _nextDir(work->dir);
            }
            {
                u32 hit = Player_MoveHitCheck(work->jiki, fldobj, work->dir);
                if( hit == JIKI_MOVE_HIT_BIT_NON ){
                    work->seq_no = _MOVE_START;
                }
                else{
                    FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR );
                    FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_PAUSE_ANM );
                    Player_DirSet(work->jiki,work->dir);
                    Jiki_EventWorkFree( work );
                    Snd_SeStopBySeqNo( SE_YAZIRUSI_FLOOR, 0 );
                    return( TRUE );
                }
            }
        }
		break;


    }
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �C�x���g�p���[�N�������m��
 * @param	size	���[�N�T�C�Y
 * @retval	void*	�m�ۂ������[�N
 */
//--------------------------------------------------------------
static void * Jiki_EventWorkAlloc( int size )
{
	void *work = sys_AllocMemoryLo( HEAPID_FIELD, size );
	GF_ASSERT( work != NULL && "Jiki_EventWorkAlloc()���[�N�m�ێ��s" );
	memset( work, 0, size );
	
	return( work );
}

//--------------------------------------------------------------
/**
 * �C�x���g�p���[�N�������J��
 * @param	work	�J�����郏�[�N
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_EventWorkFree( void *work )
{
	sys_FreeMemory( HEAPID_FIELD, work );
}

