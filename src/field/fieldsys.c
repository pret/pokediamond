//===========================================================================
/**
 * @file	fieldsys.c
 * @brief	�Q�[�����C������
 * @author	tamada	GAME FREAK Inc.
 *
 */
//===========================================================================
#include "common.h"

#define __FIELDSYS_H_GLOBAL__
#include "fieldsys.h"

#include "field/field.h"
#include "system/main.h"
#include "system\render_oam.h"

#include "fieldmap.h"
#include "fieldmap_work.h"

#include "field_event.h"

#include "system/savedata.h"

#include "ev_mapchange.h"		//EventSet_FirstMapIn

#include "zonedata.h"
#include "fielddata/maptable/zone_id.h"

#include "system/pm_overlay.h"
#include "field/situation.h"
#include "field/situation_local.h"

#include "communication/communication.h"  // �ʐM�����̂���
#include "comm_player.h"  // �ʐM�����̂���
#include "comm_field_state.h"// �ʐM�����̂���

#include "ev_check.h"		//EV_REQUEST

#include "demo/title.h"


#include "field_poketch.h"
#include "eventdata.h"

#ifdef PM_DEBUG

#define WORLD_HEAP_LEAK_CHECK	//���[���h�q�[�v���[�N�`�F�b�N�p
#define	EVENT_HEAP_LEAK_CHECK	//�C�x���g�q�[�v���[�N�`�F�b�N�p
#define	SYSTEM_HEAP_LEAK_CHECK	//�V�X�e���q�[�v���[�N�`�F�b�N�p

static u32 SystemHeapFreeSize = 0;
static u32 WorldHeapFreeSize = 0;
static u32 EventHeapFreeSize = 0;

#endif


FS_EXTERN_OVERLAY( title );
FS_EXTERN_OVERLAY( fieldmap );
//FS_EXTERN_OVERLAY( fieldmap2 );

static FIELDSYS_WORK * GameSystem_Init(PROC * proc);
static BOOL GameSystem_Main(FIELDSYS_WORK * fsys);
static void GameSystem_End(PROC * proc);


static void FieldMap_Control(FIELDSYS_WORK * fsys);
/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/

//------------------------------------------------------------------
/**
 * @brief	���䃏�[�N�p�\���̒�`
 */
//------------------------------------------------------------------
typedef struct _CONTROL_WORK{
	PROC * mainproc;		///<���C���v���Z�X�ێ����[�N
	PROC * subproc;			///<�T�u�v���Z�X�ێ����[�N
	BOOL pause_flag;		///<�|�[�Y�t���O�i�f�o�b�O�p�j
	BOOL end_flag;			///<�I���t���O�i�f�o�b�O�p�H�j
};

//------------------------------------------------------------------
/**
 * @brief	���C�����䃏�[�N
 */
//------------------------------------------------------------------
static FIELDSYS_WORK	* FieldSysWork;


//===========================================================================
//
//
//		�Q�[�����C���v���Z�X�֐�
//
//
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	�Q�[�����C���v���Z�X�F�������F�R���e�B�j���[
 */
//------------------------------------------------------------------
static PROC_RESULT ContinueGameMainProc_Init(PROC * proc, int * seq)
{
	MAINWORK * main = PROC_GetParentWork(proc);

	FieldSysWork = GameSystem_Init(proc);
	if (main->comm_error_flag) {
		EventSet_ErrorContinueMapIn(FieldSysWork);
	} else {
		EventSet_ContinueMapIn(FieldSysWork);
	}
	main->comm_error_flag = FALSE;
	return PROC_RES_FINISH;
}

//------------------------------------------------------------------
/**
 * @brief	�Q�[�����C���v���Z�X�F�������F�������傩��
 */
//------------------------------------------------------------------
static PROC_RESULT FirstGameMainProc_Init(PROC * proc, int * seq)
{
	FieldSysWork = GameSystem_Init(proc);
	EventSet_FirstMapIn(FieldSysWork);
	return PROC_RES_FINISH;
}


//------------------------------------------------------------------
/**
 * @brief	�Q�[�����C���v���Z�X�F���C��
 */
//------------------------------------------------------------------
static PROC_RESULT GameMainProc_Main(PROC * proc, int * seq)
{
	FIELDSYS_WORK * fsys = PROC_GetWork(proc);

	if (GameSystem_Main(fsys)) {
		return PROC_RES_FINISH;
	} else {
		return PROC_RES_CONTINUE;
	}
}
//------------------------------------------------------------------
/**
 * @brief	�Q�[�����C���v���Z�X�F�I��
 *
 * ���ۂɂ͌Ă΂�邱�Ƃ͂Ȃ��ƍl������
 */
//------------------------------------------------------------------
static PROC_RESULT GameMainProc_End(PROC * proc, int * seq)
{
	GameSystem_End(proc);
	Main_SetNextProc(FS_OVERLAY_ID(title), &TitleProcData);
	return PROC_RES_FINISH;
}

//------------------------------------------------------------------
//------------------------------------------------------------------
const PROC_DATA FirstGameProcData = {
	FirstGameMainProc_Init,
	GameMainProc_Main,
	GameMainProc_End,
	NO_OVERLAY_ID
};

//------------------------------------------------------------------
//------------------------------------------------------------------
const PROC_DATA ContinueGameProcData = {
	ContinueGameMainProc_Init,
	GameMainProc_Main,
	GameMainProc_End,
	NO_OVERLAY_ID
};
//===========================================================================
//
//	����֐�
//
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�}�b�v���C������
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
void GameSystem_CreateFieldProc(FIELDSYS_WORK * fsys)
{
	GF_ASSERT(fsys->ctrl->subproc == NULL);
	GF_ASSERT(fsys->ctrl->mainproc == NULL);
	Overlay_Load( FS_OVERLAY_ID( fieldmap ), OVERLAY_LOAD_NOT_SYNCHRONIZE );
	//Overlay_Load( FS_OVERLAY_ID( fieldmap2 ), OVERLAY_LOAD_NOT_SYNCHRONIZE );
	fsys->main_mode_flag = FALSE;
	fsys->ctrl->pause_flag = FALSE;
	fsys->ctrl->mainproc = PROC_Create(&FieldProcData, fsys, HEAPID_WORLD);
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�}�b�v���C���I�����N�G�X�g
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
void GameSystem_FinishFieldProc(FIELDSYS_WORK * fsys)
{
	fsys->main_mode_flag = FALSE;
}
//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�}�b�v���C���̑��݃`�F�b�N
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @retval	TRUE	�t�B�[���h�}�b�v���C�������݂��Ă���
 * @retval	FALSE	�t�B�[���h�}�b�v���C���͑��݂��Ă��Ȃ�
 */
//------------------------------------------------------------------
BOOL GameSystem_CheckFieldProcExists(FIELDSYS_WORK * fsys)
{
	return (fsys->ctrl->mainproc != NULL);
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�}�b�v���C������`�F�b�N
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @retval	TRUE	�t�B�[���h�}�b�v���C�������삵�Ă���
 * @retval	FALSE	�t�B�[���h�}�b�v���C���͓��삵�Ă��Ȃ�
 *					�i�T�u�v���Z�X���쒆���A�������E�I���������j
 */
//------------------------------------------------------------------
BOOL GameSystem_CheckFieldMain(FIELDSYS_WORK * fsys)
{
	if (fsys->ctrl->mainproc != NULL && fsys->main_mode_flag) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�T�u�v���Z�X�̑��݃`�F�b�N
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @retval	TRUE	�t�B�[���h�T�u�v���Z�X�����݂��Ă���
 * @retval	FALSE	�t�B�[���h�T�u�v���Z�X�͑��݂��Ă��Ȃ�
 */
//------------------------------------------------------------------
BOOL GameSystem_CheckSubProcExists(FIELDSYS_WORK * fsys)
{
	return (fsys->ctrl->subproc != NULL);
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�T�u�v���Z�X�̐�������
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	pdata	�v���Z�X�f�[�^
 * @param	param	�v���Z�X�ɓn���p�����[�^
 */
//------------------------------------------------------------------
void GameSystem_StartSubProc(FIELDSYS_WORK * fsys, const PROC_DATA * pdata, void * param)
{
	GF_ASSERT(fsys->ctrl->subproc == NULL);
	GameSystem_FinishFieldProc(fsys);
	fsys->ctrl->subproc = PROC_Create(pdata, param, HEAPID_WORLD);
}

//------------------------------------------------------------------
/**
 * @brief	�Q�[�����C���̏I��
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
void GameSystem_FinishGame(FIELDSYS_WORK * fsys)
{
	fsys->ctrl->end_flag = TRUE;
}

//===========================================================================
//
//
//		�������֐�
//
//
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	�Q�[������������
 * @param	proc		�v���Z�X�ւ̃|�C���^
 * @return	FIELDSYS_WORK	�t�B�[���h���C�����䃏�[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
static FIELDSYS_WORK * GameSystem_Init(PROC * proc)
{
	MAINWORK * main;
	FIELDSYS_WORK * fsys;

	//���[���h�q�[�v�m��(�m�ۂ����ςȂ�)
	//sys_CreateHeap( HEAPID_BASE_APP, HEAPID_WORLD, 0x20000 );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_WORLD, 0x1c000 );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_EVENT, 0x04000 );
	sys_CreateHeap( HEAPID_BASE_SYSTEM, HEAPID_COMMICON, 0x300 );

	//�t�B�[���h���C�����䃏�[�N���m��
	fsys = PROC_AllocWork(proc, sizeof(FIELDSYS_WORK), HEAPID_WORLD);
	MI_CpuClear8(fsys, sizeof(FIELDSYS_WORK));

	//�t�B�[���h����p���[�N���m��
	fsys->ctrl = sys_AllocMemory(HEAPID_WORLD, sizeof(CONTROL_WORK));
	fsys->ctrl->mainproc = NULL;
	fsys->ctrl->subproc = NULL;
	fsys->ctrl->pause_flag = FALSE;
	fsys->ctrl->end_flag = FALSE;

	//�Z�[�u�f�[�^�ւ̃|�C���^�����蓖��
	main = PROC_GetParentWork(proc);
	fsys->savedata = main->savedata;

	fsys->event = NULL;

	fsys->location = Situation_GetNowLocation(SaveData_GetSituation(fsys->savedata));

	//�Q�[������p�̃��[�N�m��
	//�Q�[�����A��Ɋm�ۂ���Ă��郏�[�N�͂����Ŋm�ۂ���
	fsys->World = WorldMapInit();								//���[���h�}�b�v�\���̊m��
	EventData_Sys_Create(fsys, HEAPID_WORLD);					//�C�x���g�f�[�^���䐶��
	fsys->bag_cursor = MyItem_BagCursorAlloc(HEAPID_WORLD);		//�o�b�O�̃J�[�\�����
	fsys->SwayGrass = SwayGrass_AllocSwayGrass(HEAPID_WORLD);	//�h�ꑐ�\���̃������m��
	SwayGrass_InitSwayGrass(fsys->SwayGrass);	//�h�ꑐ������
	fsys->p_zukandata = ZKN_DW_Alloc( HEAPID_WORLD );	// �}�Ӄ��X�g�ʒu�ۑ��̈�


	return fsys;
}

//===========================================================================
//
//
//		�I���֐�
//
//
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	�Q�[���I������
 * @param	proc		�v���Z�X�ւ̃|�C���^
 */
//------------------------------------------------------------------
static void GameSystem_End(PROC * proc)
{
	FIELDSYS_WORK * fsys = PROC_GetWork(proc);

	//�Q�[������p�̃��[�N���
	//�Q�[�����A��Ɋm�ۂ���Ă��郏�[�N�͂����ŉ������
	WorldMapRelease(fsys->World);				// ���[���h�}�b�v�\���̉��
	EventData_Sys_Delete(fsys);					// �C�x���g�f�[�^������
	sys_FreeMemoryEz(fsys->bag_cursor);			// �o�b�O�̃J�[�\�����
	SwayGrass_FreeSwayGrass(fsys->SwayGrass);	//�h�ꑐ���[�N���
	ZKN_DW_Free( fsys->p_zukandata );			// �}�Ӄ��X�g�ʒu�ۑ��̈�

	sys_FreeMemoryEz(fsys->ctrl);
	PROC_FreeWork(proc);
	sys_DeleteHeap(HEAPID_COMMICON);
	sys_DeleteHeap(HEAPID_WORLD);
	sys_DeleteHeap(HEAPID_EVENT);
}


//===========================================================================
/**
 * 
 * ���C���֐�
 *
 */
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	�T�u�v���Z�X�Ăяo������
 * @param	proc	�T�u�v���Z�X�|�C���^��ێ����郏�[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
static void ProcCall(PROC ** proc)
{
	if (*proc) {
		if (ProcMain(*proc)) {
			PROC_Delete(*proc);
			*proc = NULL;
		}
	}
}
//------------------------------------------------------------------
/**
 * @brief	�Q�[�����C������
 * @param	fsys	�t�B�[���h���C�����䃏�[�N�ւ̃|�C���^
 * @retval	TRUE	�I��
 * @retval	FALSE	�p������
 */
//------------------------------------------------------------------
BOOL GameSystem_Main(FIELDSYS_WORK * fsys)
{
	BOOL event_end;

    FieldMap_Control(fsys);
	event_end = FieldEvent_Control(fsys);
	if(event_end == TRUE && fsys->fldmap != NULL)
	{
		//�|�P�b�`�X���[�v��������
		Field_SendPoketchInfo( fsys, POKETCH_SEND_SLEEP, FALSE );
	}


	if (fsys->ctrl->mainproc) {
		ProcCall(&fsys->ctrl->mainproc);
		if (fsys->ctrl->mainproc == NULL) {
			Overlay_UnloadID( FS_OVERLAY_ID(fieldmap) );
			//Overlay_UnloadID( FS_OVERLAY_ID(fieldmap2) );
		}
	} else if (fsys->ctrl->subproc) {
		ProcCall(&fsys->ctrl->subproc);
	}

	if (fsys->ctrl->end_flag && !fsys->event
			&& !fsys->ctrl->mainproc && !fsys->ctrl->subproc) {
		//�I�����N�G�X�g������A�C�x���g���T�u�v���Z�X�����C���v���Z�X��
		//�Ȃ���ΏI��������
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * ���@����A�C�x���g�`�F�b�N
 *
 * @param	fsys		FIELDSYS_WORK
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldMap_Control(FIELDSYS_WORK * fsys)
{
	int map_mode;
	EV_REQUEST	req;
    BOOL bMoveControl = FALSE;

    //�|�[�Y��ԂłȂ��A
    //�t�B�[���h���C�������삵�Ă���
    //�C�x���g���������Ă��Ȃ��ꍇ�A
    //	�e�폈�������s����
    if (!fsys->ctrl->pause_flag
        && fsys->main_mode_flag
        && FieldEvent_Check(fsys) == FALSE) {
        bMoveControl = TRUE;
    }

#ifdef	PM_DEBUG
	if (bMoveControl) {
		if (MAP_MODE_GROUND == fsys->MapMode){
#ifdef SYSTEM_HEAP_LEAK_CHECK
			if (SystemHeapFreeSize == 0) {
				SystemHeapFreeSize = sys_GetHeapFreeSize(HEAPID_BASE_SYSTEM);
			} else if (SystemHeapFreeSize != sys_GetHeapFreeSize(HEAPID_BASE_SYSTEM)) {
				sys_DeleteHeap(HEAPID_BASE_SYSTEM);
				GF_ASSERT_MSG(0, "SYSTEM HEAP SIZE %d < %d\n",
						SystemHeapFreeSize, sys_GetHeapFreeSize(HEAPID_BASE_SYSTEM));
			}
#endif

#ifdef WORLD_HEAP_LEAK_CHECK		
			if (WorldHeapFreeSize == 0) {
				WorldHeapFreeSize = sys_GetHeapFreeSize(HEAPID_WORLD);
			} else if (WorldHeapFreeSize != sys_GetHeapFreeSize(HEAPID_WORLD)){
				bMoveControl = FALSE;
			}
#endif	//WORLD_HEAP_LEAK_CHECK

#ifdef	EVENT_HEAP_LEAK_CHECK
			if (EventHeapFreeSize == 0) {
				EventHeapFreeSize = sys_GetHeapFreeSize(HEAPID_EVENT);
			} else if (EventHeapFreeSize != sys_GetHeapFreeSize(HEAPID_EVENT)) {
				bMoveControl = FALSE;
			}
#endif	//EVENT_HEAP_LEAK_CHECK

			if (bMoveControl == FALSE) {
				//�q�[�v�̃��[�N�����o������^�C�g���ɖ߂�
				//���^�C�g���Ńq�[�v���J������̂Ń��[�N�ӏ����킩��
				EventSet_ReturnToTitle(fsys);
			}
		}
	}
#endif

    if(bMoveControl){
		Player_MoveStateUpdate( fsys->player );
        SetRequest( &req, fsys, sys.trg, sys.cont );
    }
	map_mode = fsys->MapMode;

	if(fsys->location->zone_id == ZONE_ID_D31R0201){
		//�^���[��t�̃}�b�v���[�h��MAP_MODE_BTOWER����
		//�C�x���g�`�F�b�N�̓m�[�}���ɍs��
		map_mode = MAP_MODE_GROUND;
	}
    switch(map_mode){
      case MAP_MODE_UNDER:
        if(bMoveControl){
            if(CommPlayerIsControl()){
                if( CheckRequestUG( &req, fsys ) == TRUE ){  // �Y�z
                }
            }
        }
        CommPlayersMove(fsys, bMoveControl);  // �ʐM�ړ�
        break;
      case MAP_MODE_COLOSSEUM:
        if(bMoveControl){
            if(CommPlayerIsControl()){
                if( CheckRequestVSRoom( &req, fsys ) == TRUE ){  // �ΐ핔��
                    bMoveControl = FALSE;
                }
            }
            else{
                bMoveControl = FALSE;
            }
        }
        CommPlayersMove(fsys, bMoveControl);  // �ʐM�ړ�
        break;
      case MAP_MODE_UNION:
        if(bMoveControl){
            if( CheckRequestUnion( &req, fsys ) == TRUE ){
                //�C�x���g�N��������A�̏����������ɓ����
            }else{
                Player_MoveControl( fsys->player,
						fsys->map_cont_dat,DIR_NOT, req.trg, req.cont, FALSE );
            }
        }
        break;
	  case MAP_MODE_BTOWER:
        if(bMoveControl){
            if( CheckRequestBTower( &req, fsys ) == TRUE ){
                StopPlaceName(fsys->fldmap->place_name_cont);	//�n���\���L�����Z��
                BoardSetDirect( fsys, BOARD_REQ_DEL );	// �Ŕ����j���i�������j
				Player_EventPoketchCancel( fsys->player );	//���@�|�P�b�`��ԃL�����Z��
                //�|�P�b�`�X���[�v����
                Field_SendPoketchInfo( fsys, POKETCH_SEND_SLEEP, TRUE );
            }
            else{
                //�C�x���g���������Ȃ��Ă��A����{�^������������n���\���̓L�����Z������
                if (sys.trg & PAD_BUTTON_DECIDE){
                    StopPlaceName(fsys->fldmap->place_name_cont);	//�n���\���L�����Z��
                }
				
				{
					BOOL touch = FALSE;
					POKETCH_WORK *poketch = GetPoketchMainWorkPtr();
					if( poketch != NULL ){ touch = Poketch_CheckTouch( poketch ); }
					
                	Player_MoveControl(
						fsys->player, fsys->map_cont_dat, DIR_NOT, req.trg, req.cont, touch );
				}
            }
        }
		break;
      default: // �ʐM���Ă��Ȃ����ʂ̏��
        if(bMoveControl){
            if( CheckRequest( &req, fsys ) == TRUE ){
                StopPlaceName(fsys->fldmap->place_name_cont);	//�n���\���L�����Z��
                BoardSetDirect( fsys, BOARD_REQ_DEL );	// �Ŕ����j���i�������j
				Player_MoveStateClear( fsys->player );	//���@�����ԁi���]�ԑ��x�Ȃǁj�N���A
				Player_EventPoketchCancel( fsys->player );	//���@�|�P�b�`��ԃL�����Z��
                //�|�P�b�`�X���[�v����
                Field_SendPoketchInfo( fsys, POKETCH_SEND_SLEEP, TRUE );
            }
            else{
                //�C�x���g���������Ȃ��Ă��A����{�^������������n���\���̓L�����Z������
                if (sys.trg & PAD_BUTTON_DECIDE){
                    StopPlaceName(fsys->fldmap->place_name_cont);	//�n���\���L�����Z��
                }
				
				{
					BOOL touch = FALSE;
					POKETCH_WORK *poketch = GetPoketchMainWorkPtr();
					if( poketch != NULL ){ touch = Poketch_CheckTouch( poketch ); }
					
                	Player_MoveControl(
						fsys->player, fsys->map_cont_dat, DIR_NOT, req.trg, req.cont, touch );
				}
            }
        }
        break;
    }
}

//===========================================================================
/**
 * 
 * �A�v���^�X�N�ݒ�(�t�B�[���h�̓z�[���h��ԂɂȂ�)
 *
 */
//===========================================================================
void FieldSystemProc_SeqHold(void)
{
	FieldSysWork->ctrl->pause_flag = TRUE;
    CommDisableSendMoveData();  // �ړ��֎~
}


//===========================================================================
/**
 * 
 * �A�v���^�X�N�I��(�t�B�[���h���A)
 *
 */
//===========================================================================
void FieldSystemProc_SeqHoldEnd(void)
{
	FieldSysWork->ctrl->pause_flag = FALSE;
    CommEnableSendMoveData();  //�ړ�����
}


//===========================================================================
//
// �|�P�b�`�֘A
//
//===========================================================================

struct _POKETCH_WORK* GetPoketchMainWorkPtr(void)
{
	if (FieldSysWork->fldmap == NULL) {
		return NULL;
	}
	return FieldSysWork->fldmap->poketch;
}


//===========================================================================
//
//
//
//===========================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------
GF_BGL_INI * FieldBglIniGet( void * fsys )
{
	FIELDSYS_WORK * wk = (FIELDSYS_WORK *)fsys;

	return wk->bgl;
}

//------------------------------------------------------------------
/**
 * @brief	�Z�[�u�f�[�^�ւ̃|�C���^�擾
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	SAVEDATA	�Z�[�u�f�[�^�ւ̃|�C���^
 */
//------------------------------------------------------------------
SAVEDATA * GameSystem_GetSaveData(void * fsys)
{
	return ((FIELDSYS_WORK *)fsys)->savedata;
}

