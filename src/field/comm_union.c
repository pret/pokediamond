//=============================================================================
/**
 * @file	comm_union.c
 * @brief	���j�I�����[�����䏈��
 * @author	Akito Mori
 * @date    2005.12.10
 */
//=============================================================================

//#define OEKAKI_ONLY_TALK
//#define	RECORD_ONLY_TALK

#include "common.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "communication/wh_config.h"
#include "communication/wh.h"
#include "fieldsys.h"
#include "field/field.h"
#include "../fielddata/script/connect_def.h"
#include "../fielddata/script/union_def.h"
#include "system/wordset.h"
#include "system/pms_data.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_trtype.h"
#include "msgdata/msg_union.h"

#include "comm_command_field.h"
#include "comm_union_def.h"
#include "script.h"
#include "comm_union_beacon.h"
#include "application/trainer_card.h"
#include "tr_card_setup.h"
#include "field/union_beacon_tool.h"


#include "../application/oekaki/comm_command_oekaki.h"


#define UNION_PRINT_ON

#ifdef UNION_PRINT_ON

#define PRINT( str ) 			OS_Printf( str )
#define PRINT2( str , param) 	OS_Printf( str , param )

#else

#define PRINT( str ) 
#define PRINT2( str , param) 


#endif

//==============================================================================
//	�萔�錾
//==============================================================================
#define TALK_OBJ_MAX			( 10 )
#define SUB_OBJ_MAX				( TALK_OBJ_MAX*4 )
#define _PARENT_WAIT_TIME 	 	( 40 ) ///�e�Ƃ��Ă̂�т�҂���
#define _CHILD_P_SEARCH_TIME 	( 12 )
#define _FINALIZE_TIME 			(  2 )
#define _EXIT_SENDING_TIME 		(  5 )
#define _CONNECT_RETRY_NUM 		(  2 )
#define _CHILD_CONNECT_WAIT		( 3*60 )

#define PARENT_UNIONROOM_TGID	( 0x1234 )

#define UNION_CHILD_STATUS_SEND_RETRY_WAIT	( 120 )

enum{
	NO_OBJ=0,
	FALL_OBJ,
	TALKOK_OBJ,
	RISE_OBJ,
};

#define START_TIME ( 40 )
#define _TCB_UNIONSTATE_PRT   (10)    ///< �t�B�[���h������ʐM�̊Ď����[�`����PRI

enum{
	DS_CONNECT_START=1,
	MP_CONNECT_START,
};

//==============================================================================
//	�^�錾
//==============================================================================

// �R�[���o�b�N�֐��̏���
typedef void (*PUnionRoomFunc)(COMM_UNIONROOM_WORK *cuw);


// �b����������OBJ�̍\����
typedef struct{
	u16 arrow;
	u16 status;
}MAIN_OBJ_CONT;

// �b������OBJ�̎���ɂ��T�uOBJ�̍\����
typedef struct{
	u16 arrow;
	u16 status;
}SUB_OBJ_CONT;

// ���j�I�����[���p���[�N�\����
struct COMM_UNIONROOM_WORK{
	FIELDSYS_WORK		*fsys;
	SAVEDATA			*savedata;
	MYSTATUS			*mystatus;
	
	TCB_PTR	           UnionStateTask;
	PUnionRoomFunc     state;
	int                timer;

	u32					CommConnectId;				// �ڑ����ɂ���OBJID
	u32					CommConnectResult;			// �ڑ����ʂ�Ԃ�
	int 				CommConnectStartFlag;
	int 				CommConnectStartWait;
	int					CommConnectRetry;
	int					CommNextProcOn;
	u32					CommChildSelectEvent;
	u32					ScriptSelectWork;			// �I�����ʂ�ۑ�
	u32					InviteWork;					// �ʐM�Œ񎦂��ꂽ���e��ۑ�
	u32					ScriptYesNoWork;			// �͂��E�������̌��ʂ�ۑ�

	u32					UnionEventWork;				// �s�����e�i�J�[�h�E�퓬�E�����E�`���b�g�j
	u32					UnionEndConnectFlag;		// �ʐM�I��
	
	MAIN_OBJ_CONT	   MainObjCont[TALK_OBJ_MAX];		// �b����������P�O�l
	SUB_OBJ_CONT	   SubObjCont[SUB_OBJ_MAX];		// ���C���̎���ɂ���S�l�i���P�O�j
	WMBssDesc		   *UnionBeaconTbl[SCAN_PARENT_COUNT_MAX];

	MATHRandContext32  pRand;						// WEP�L�[����
	int connectIndex;

	int objwork;
	int objwait;

	u16 busyflag;
	u8  battleSelect[2];							// �퓬�O�̃|�P�������X�g�̌��ʂ���M����

	PMS_DATA			MyPmsData;					// �X�^�[�g���j���[�́u�`���b�g�v�ŊȈՉ�b��ݒ肵���ꍇ
	BOOL				MyPmsPutFlag;				// ���̗̈�ɍ쐬�����ȈՉ�b���R�s�[�����

	TR_CARD_DATA 		*my_trcard;					// �����̃g���[�i�[�J�[�h
	TR_CARD_DATA 		*recv_trcard[2];			// ����̃g���[�i�[�J�[�h

#ifdef PM_DEBUG
    u32					debugTimer;
#endif
};


/*** �֐��v���g�^�C�v ***/
static COMM_UNIONROOM_WORK* _commStateInitialize(FIELDSYS_WORK* fsys);
static void _UnionStart(COMM_UNIONROOM_WORK *cuw);
static void _UnionRestart( COMM_UNIONROOM_WORK *cuw );
static void _changeState(COMM_UNIONROOM_WORK *cuw, PUnionRoomFunc state, int time);
static void _stateConnectEnd(COMM_UNIONROOM_WORK *cuw);
static void _stateEnd(COMM_UNIONROOM_WORK *cuw);
static void CommStateFinalize(COMM_UNIONROOM_WORK *cuw);
static void _underChildConnecting(COMM_UNIONROOM_WORK *cuw);
static void _underParentInfoSend(COMM_UNIONROOM_WORK *cuw);
static void _underParentConnect(COMM_UNIONROOM_WORK *cuw);
static void _underChildSelectWait(COMM_UNIONROOM_WORK *cuw);
static void _underChildInfoSendSuccess( COMM_UNIONROOM_WORK *cuw );
static void _ConnectInfoClear( COMM_UNIONROOM_WORK *cuw );
static void _underChildEndEventState( COMM_UNIONROOM_WORK *cuw );
static void CommUnion_EventFlagClear( COMM_UNIONROOM_WORK *cuw);
static int  MyStatusCheck( void );
static int GetGroupTalk_ListenNo( COMM_UNIONROOM_WORK *cuw, int no );
static int GetStartTalk_No(int event, int sex, WORDSET *wordset );
static void _UnionBeaconSet( COMM_UNIONROOM_WORK *cuw );


static void UnionBeaconClear( UNION_BEACON_STATE *beacon );






//==============================================================================
/**
 * ���j�I�����[���ɂ͂��������̒ʐM����
 * @param   pFSys FIELDSYS_WORK
 * @retval  none
 */
//==============================================================================
COMM_UNIONROOM_WORK *Comm_UnionRoomInit(FIELDSYS_WORK* fsys)
{

	COMM_UNIONROOM_WORK *cuw = NULL;

	GF_ASSERT(fsys!=NULL && "fsys��NULL");

    if(fsys->union_work!=NULL){ // �Ȃ����Ă���ꍇ���͏��O����
        return NULL;
    }
    // �ʐM�q�[�v�쐬
    if(sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_UNIONROOM, 0xa80 )){
		OS_Printf("HEAPID_UNION �쐬����\n");
	}

	// ���j�I�����[�����[�N�m��
    cuw = _commStateInitialize(fsys);
	if(cuw==NULL){
		cuw = fsys->union_work;
	}

	// �t�B�[���h�p�ʐM�R�}���h�R�[���o�b�N�ݒ�
    CommCommandFieldInitialize((void*)fsys);

	// �ʐM�ڑ��l�����Q�l�ɐ���
    CommStateSetLimitNum(2);
	

//  CommStateUnionBconCollection( SaveData_GetMyStatus(GameSystem_GetSaveData(fsys)) );

    // �n���X�e�[�g�̑J�ڂ̂��ߏ�����
	PRINT("Union�q�@�����J�n\n");
    _changeState(cuw, _UnionBeaconSet, START_TIME);
	OS_Printf("sizeof(MYSTATUS)=%d \n",MyStatus_GetWorkSize());

	OS_Printf("COMM_UNIONROOM_WORK =%d \n",sizeof(COMM_UNIONROOM_WORK));

	return cuw;
}
#ifdef PM_DEBUG

static COMM_UNIONROOM_WORK *debug_cuw;

#endif
//==============================================================================
/**
 * ���j�I�����[������o��Ƃ�
 *
 * @param   fsys		
 *
 * @retval  none		
 */
//==============================================================================
void Comm_UnionFinalize(FIELDSYS_WORK *fsys)
{
    if(fsys->union_work==NULL){  // ���łɏI�����Ă���
       return;
    }
    _changeState(fsys->union_work, _stateConnectEnd, _EXIT_SENDING_TIME);
}


//------------------------------------------------------------------
/**
 * ���j�I�����[���������V�[�P���X
 *
 * @param   fsys		
 *
 * @retval  COMM_UNIONROOM_WORK*		
 */
//------------------------------------------------------------------
static COMM_UNIONROOM_WORK* _commStateInitialize(FIELDSYS_WORK* fsys)
{
    void* pWork;
	SAVEDATA *savedata;
	COMM_UNIONROOM_WORK *cuw = NULL;

    if(fsys->union_work!=NULL){   // ���łɃ��j�I�����쒆�̏ꍇ�͌��̃������m�ۏ������K�v�Ȃ�
        return NULL;
    }
	savedata    = GameSystem_GetSaveData(fsys);

    // UNION���[��BCON���W�J�n
    CommStateUnionBconCollection( savedata );


    // ������
    cuw = (COMM_UNIONROOM_WORK*)sys_AllocMemory(HEAPID_UNIONROOM, sizeof(COMM_UNIONROOM_WORK));
	MI_CpuClear8(cuw, sizeof(COMM_UNIONROOM_WORK) );
    cuw->state = NULL;   // �������Ȃ�
    cuw->timer = START_TIME;
    cuw->UnionStateTask = TCB_Add(_commCheckFunc, cuw, _TCB_UNIONSTATE_PRT);
    cuw->fsys     = fsys;
	cuw->savedata = savedata;
	cuw->mystatus    = SaveData_GetMyStatus(savedata);
//	cuw->partner_trcard = (TR_CARD_DATA*)sys_AllocMemory(HEAPID_BASE_SYSTEM, 1624+16);
//	cuw->my_trcard      = (TR_CARD_DATA*)sys_AllocMemory(HEAPID_BASE_SYSTEM, 1624+16);
	

	CommUnion_EventFlagClear(cuw);

//    _debugTimerStart();
    CommRandSeedInitialize(&cuw->pRand);

#ifdef PM_DEBUG
	debug_cuw = cuw;
#endif
	return cuw;
}	



//------------------------------------------------------------------
/**
 * @brief   ���j�I�����[���J�n���Ƀr�[�R����������
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _UnionBeaconSet( COMM_UNIONROOM_WORK *cuw )
{
	PMS_DATA pmsdata;

	if(CommMPIsInitialize()){
		// ���j�I�����[���f�t�H���g��b�Z�b�g
		PMSDAT_SetupDefaultUnionMessage( &pmsdata );
		// �r�[�R���f�[�^�ɔ��f������
		Union_PMSReWrite( &pmsdata );		
		Union_SetMyPmsData( cuw, &pmsdata );		// ���j�I�����[�N�ŕۑ����Ă�������ʂɕ\��������
	    _changeState(cuw, _UnionStart, START_TIME);
	}
}

static int debug_parent;

//==============================================================================
/**
 * ���j�I�����[���X�^�[�g�y���j�I���^�X�N�J�ځz
 * @param   none
 * @retval  none
 */
//==============================================================================

#define _FIRST_SEND	( 0 )

static void _UnionStart(COMM_UNIONROOM_WORK *cuw)
{
	// �e�@�ڑ����ꂽ���H
    if(CommStateIsUnionParentConnectSuccess()){
        OS_TPrintf("�e�@�ڑ�\n");
		debug_parent = 0;
		_changeState(cuw, _underParentInfoSend, _FIRST_SEND);
        return;
    }

	// �b���������n�߂����H
    if(cuw->CommConnectStartFlag!=0){
        cuw->CommConnectRetry = _CONNECT_RETRY_NUM;
        /// index�Őڑ����J�n���܂�
		if(cuw->CommConnectStartFlag == DS_CONNECT_START){
				if(cuw->CommChildSelectEvent==UNION_CHILD_SELECT_RECORD){
					// ���R�[�h�R�[�i�[�q�@�����ڑ��J�n
					CommStateUnionRecordCornerChild(cuw->CommConnectId);
				}else {
					// �ʏ�q�@�ڑ��J�n
			        CommStateUnionConnectStart(cuw->CommConnectId);   
				}
		}else if(cuw->CommConnectStartFlag == MP_CONNECT_START){
            // �ʐM�R�}���h���������X�g�p�ɕύX
            CommCommandOekakiBoardInitialize( NULL );
			CommStateUnionPictureBoardChild(cuw->CommConnectId);
		}
		
        _changeState(cuw, _underChildConnecting, _CHILD_P_SEARCH_TIME);
		return;
	}
}

//------------------------------------------------------------------
/**
 * $brief   �ʐM�I����ؒf����V�т���߂��Ă����Ƃ��̃V�[�P���X
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _UnionRestart( COMM_UNIONROOM_WORK *cuw )
{
	// �ʐM�V�X�e���ĊJ���܂�
    if(CommStateUnionIsRestartSuccess()==TRUE){
		
	    // �t�B�[���h�p�ʐM�R�}���h�R�[���o�b�N�ɖ߂�
    	CommCommandFieldInitialize((void*)cuw->fsys);

        _changeState(cuw, _UnionStart, _FINALIZE_TIME);
		
	}
}

//------------------------------------------------------------------
/**
 * $brief   ���ݎq�@�����l�ڑ����Ă��邩�H
 *
 * @param   none		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int MyStatusCheck( void )
{
	int i,result;
	MYSTATUS *status;

	result = 0;

	// 1�`�S�Ȃ̂Ŏq�@�̃X�e�[�^�X����M����̂����m������
	for(i=1;i<5;i++){
		status = CommInfoGetMyStatus(i);
		if(status!=NULL){
			result++;
		}
	}

	// �N���q�@���炫�����H
	return (result>=1);
}


//==============================================================================
/**
 * �e�@�ɂȂ� ��b������y���j�I���^�X�N�J�ځz
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentInfoSend(COMM_UNIONROOM_WORK *cuw)
{
    if(cuw->timer>0){
        cuw->timer--;
        return;
    }
	
	OS_Printf("�e�@�ڑ�%d���\n", debug_parent);
	debug_parent++;
    if(CommIsChildsConnecting() && MyStatusCheck()==1){   // 
		// �e�̊�{�f�[�^���M
        CommInfoSendPokeData();
		
		// �q�@�����Ȃ��̂��G���[�����ɂ��邩�ǂ�����SET
        CommStateSetErrorCheck(TRUE,TRUE);

		// ������fsys��NULL�̂��Ƃ�����B
		// �e�@�Ƃ��Ă̐ڑ��C�x���g�J�n
//		EventSet_Script( cuw->fsys, SCRID_CONNECT_UNION_RECEIVE_OBJ, NULL );

		// �u�p�[�e�B�[�ɂȂ�����v�r�[�R���ɕς���
		Union_BeaconChange( UNION_PARENT_MODE_PARTY );
		_changeState(cuw,_underParentConnect, _FIRST_SEND);
	}

	// �ؒf���Ă����猳�ɂ��ǂ�
	if(CommStateIsUnionParentConnectSuccess()==0){
    	CommStateUnionBconCollectionRestart();
		CommUnion_EventFlagClear(cuw);
		Union_BeaconChange( UNION_PARENT_MODE_FREE );
	    _changeState(cuw,_UnionRestart, _FINALIZE_TIME);
		
	}

}


//------------------------------------------------------------------
/**
 * $brief   �e�@�ڑ���(���Ƃ̓R�[���o�b�N�ɂ��܂����j
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _underParentConnect(COMM_UNIONROOM_WORK *cuw)
{
    if(CommIsChildsConnecting()){   // �����ȊO���Ȃ�������e�@�Œ�
		
	}else{
	
	}

	// �ؒf�����̂Ō��̑���ɖ߂�
    if(0 == CommIsChildsConnecting()){
		// �ڑ����s�����̂ŁA�I�����Č��̐e�q�؂�ւ��̗���ɖ߂�
//    	CommCommandFieldInitialize((void*)cuw->fsys);
		OS_TPrintf("�q�@���؂ꂽ���� bitmap=%02x status=%d connectnum=%d childconnect=%d\n", WH_GetBitmap(), MyStatusCheck(), CommGetConnectNum(), CommIsChildsConnecting());
    	CommStateUnionBconCollectionRestart();
		CommUnion_EventFlagClear(cuw);
		Union_BeaconChange( UNION_PARENT_MODE_FREE );
	    _changeState(cuw,_UnionRestart, _FINALIZE_TIME);
    }


}

//==============================================================================
/**
 * �ʐM�Ǘ��X�e�[�g�̕ύX
 * @param   state  �ς���X�e�[�g�̊֐�
 * @param   time   �X�e�[�g�ێ�����
 * @retval  none
 */
//==============================================================================

static void _changeState(COMM_UNIONROOM_WORK *cuw, PUnionRoomFunc state, int time)
{
	
    cuw->state = state;
    cuw->timer = time;
}

//==============================================================================
/**
 * �ʐM�Ǘ��X�e�[�g�̏���
 * @param
 * @retval  none
 */
//==============================================================================

static WMBssDesc *debugBsstable[16];

void _commCheckFunc(TCB_PTR tcb, void* work)
{
	COMM_UNIONROOM_WORK *cuw = (COMM_UNIONROOM_WORK*)work;
#ifdef PM_DEBUG
    cuw->debugTimer++;
#endif

#ifdef PM_DEBUG

	if(sys.trg&PAD_BUTTON_START){
		UNION_BEACON_STATE state;
//		if(cuw->busyflag = UNION_PARENT_MODE_FREE){
//			cuw->busyflag = UNION_PARENT_MODE_BUSY;

//			MI_CpuClear8(&state, sizeof(UNION_BEACON_STATE) );
//			state.c_face[0] = 1;
//			state.mode      = UNION_PARENT_MODE_BUSY;

//		}else{
//			cuw->busyflag = UNION_PARENT_MODE_FREE;
//			state.mode = UNION_PARENT_MODE_FREE;
//		}
//		CommMPSetMyRegulation(&state);	// �u�Z�����v�Ƀr�[�R����������
//		CommMPFlashMyBss();
	}

	if(sys.trg&PAD_BUTTON_SELECT){
		OS_Printf("�����̍��ԍ� %d \n",MyStatus_GetRegionCode( cuw->mystatus ));
	}
#endif

    if(cuw==NULL){
        TCB_Delete(tcb);
    }
    else{
		int i;
		WMBssDesc *tmp;

		for(i=0;i<SCAN_PARENT_COUNT_MAX;i++){
			cuw->UnionBeaconTbl[i] = CommMPGetWMBssDesc(i);
			debugBsstable[i]       = cuw->UnionBeaconTbl[i]; 
		}


        if(cuw->state != NULL){
            cuw->state(cuw);
        }
    }
}


//==============================================================================
/**
 * @brief  �I�������J�n
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _stateConnectEnd(COMM_UNIONROOM_WORK *cuw)
{
    if(cuw->timer != 0){
        cuw->timer--;
        return;
    }
    // �ؒf����
    CommStateExitUnion();
    _changeState(cuw,_stateEnd, 0);
}

//------------------------------------------------------------------
/**
 * �ʐM�I���V�[�P���X
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _stateEnd(COMM_UNIONROOM_WORK *cuw)
{
    if(CommIsInitialize()){
        return;
    }
    CommStateFinalize(cuw);
}

//==============================================================================
/**
 * �q�@�ƂȂ��Đڑ����y���j�I���^�X�N�J�ځz
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _underChildConnecting(COMM_UNIONROOM_WORK *cuw)
{
    if(1 == CommStateIsUnionConnectSuccess()){
        
//      CommStateSetErrorCheck(TRUE,TRUE);

		// �ڑ������Ȃ�e�@�ɏ��𑗂�
        CommInfoSendPokeData();
		_changeState(cuw,_underChildInfoSendSuccess, 3);
        OS_TPrintf("�e�@�ɐڑ������̂Ŏq�@��񑗐M\n");
        return;
    }else if(CommIsChildsConnecting()){   
		// �t�ɐe�Ƃ��Čq�������B(���������j
		cuw->CommConnectStartFlag = 0;
		cuw->CommConnectResult    = UNION_CONNECT_PARENT;
		
        OS_TPrintf("�ڑ��ɂ��������肪�e�@�ڑ�\n");
        _changeState(cuw,_underParentInfoSend, 0);
	}
    if(0 == CommStateIsUnionConnectSuccess()){
		// �ڑ��ҋ@��
        OS_TPrintf("�ڑ����������Ȃ�\n");
        return;
    }
	// �ڑ����s�����̂ŁA�C�x���g�̏I���҂������Č��̐e�q�؂�ւ��̗���ɖ߂�
   	_changeState(cuw,_underChildEndEventState, _FINALIZE_TIME);
	cuw->CommConnectStartWait = 0;
	cuw->CommConnectResult    = UNION_CONNECT_FAILED;
	cuw->CommConnectStartFlag = 0;
	cuw->UnionEndConnectFlag  = 0;
}

//------------------------------------------------------------------
/**
 * @brief   �q�@�ڑ��Ɏ��s������C�x���g�I����҂�
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _underChildEndEventState( COMM_UNIONROOM_WORK *cuw )
{
	if(!FieldEvent_Check(cuw->fsys)){

	    CommStateUnionBconCollectionRestart();
		CommUnion_EventFlagClear(cuw);
		Union_BeaconChange( UNION_PARENT_MODE_FREE );
   		_changeState(cuw,_UnionRestart, _FINALIZE_TIME);

	}
	
}

//------------------------------------------------------------------
/**
 * @brief   �q�@�̏�񑗐M����������
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _underChildInfoSendSuccess( COMM_UNIONROOM_WORK *cuw )
{

	// �ڑ���
    if(1 == CommStateIsUnionConnectSuccess()){
		if(CommInfoGetMyStatus(CommGetCurrentID())!=NULL){
			PRINT("�ڑ������I�I�I�I\n");
			cuw->CommConnectStartFlag = 0;
			cuw->CommConnectResult    = UNION_CONNECT_SUCCESS;
			cuw->UnionEndConnectFlag  = 0;

	        CommStateSetErrorCheck(TRUE,TRUE);
			_changeState(cuw,_underChildSelectWait, 3);
		}
		OS_Printf("�q�@�ڑ���\n");
    }else if(0 == CommStateIsUnionConnectSuccess()){
	// �ڑ����؂ꂽ
		
		OS_Printf("�ڑ����؂ꂽ���ǂ��������ăC�x���g������Ȃ��H\n");
		
    	//CommCommandFieldInitialize((void*)cuw->fsys);
	    CommStateUnionBconCollectionRestart();
		CommUnion_EventFlagClear(cuw);
    	_changeState(cuw,_UnionRestart, _FINALIZE_TIME);

		cuw->CommConnectStartWait = 0;
		cuw->CommConnectResult    = UNION_CONNECT_FAILED;
		cuw->CommConnectStartFlag = 0;
		cuw->UnionEndConnectFlag  = 0;
	}
	
}

//------------------------------------------------------------------
/**
 * $brief   �q�@�Ƃ��ĒʐM�ڑ�������̓R�[���o�b�N�֐�����
 *          �������邱�Ƃ������̂ŁA�ؒf�����͌��n����悤�ɂ���y���j�I���^�X�N�J�ځz
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void  _underChildSelectWait(COMM_UNIONROOM_WORK *cuw)
{
//    if(cuw->timer==1){
//        CommInfoSendPokeData();
//    }

    if(0 == CommStateIsUnionConnectSuccess()){
    	//CommCommandFieldInitialize((void*)cuw->fsys);
	    CommStateUnionBconCollectionRestart();
		CommUnion_EventFlagClear(cuw);
    	_changeState(cuw,_UnionRestart, _FINALIZE_TIME);
		return ;
	}
    // �ڑ��^�C���A�E�g
//    if(cuw->timer!=0){
//        cuw->timer--;
//        return;
//    }
}

//------------------------------------------------------------------
/**
 * ���j�I���ʐM�p���[�N���
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CommStateFinalize(COMM_UNIONROOM_WORK *cuw)
{
    void* pWork;

    if(cuw==NULL){  // ���łɏI�����Ă���
        return;
    }
    TCB_Delete(cuw->UnionStateTask);
//    sys_FreeMemoryEz(cuw->partner_trcard);
  //  sys_FreeMemoryEz(cuw->my_trcard);
    sys_FreeMemoryEz(cuw);
    sys_DeleteHeap(HEAPID_UNIONROOM);
//    cuw = NULL;
}



//==============================================================================
/**
 * COMM_UNIONROOM_WORK�������Ă���FIELDSYS_WORK�̃|�C���^��Ԃ�
 *
 * @param   cuw		
 *
 * @retval  FIELDSYS_WORK*		
 */
//==============================================================================
FIELDSYS_WORK* Union_FielsSysPtrGet(COMM_UNIONROOM_WORK *cuw)
{
	return cuw->fsys;
}

//==============================================================================
/**
 * �ʐM����擾�����r�[�R���̃|�C���^��Ԃ�(comm_union_view.c�p)
 *
 * @param   cuw		
 * @param   no		
 *
 * @retval  WMBssDesc*		
 */
//==============================================================================
WMBssDesc* Union_BeaconPtrGet(COMM_UNIONROOM_WORK *cuw, int no)
{
	return cuw->UnionBeaconTbl[no];
}

//==============================================================================
/**
 * $brief   
 *
 * @param   cuw		
 *
 * @retval  int		
 */
//==============================================================================
int Union_ConnectIndexGet(COMM_UNIONROOM_WORK *cuw)
{
	return cuw->connectIndex;
}

static UNION_BEACON_STATE *debug_beacon;

//==============================================================================
/**
 * �b������OBJ��ID�����Đڑ��̂��߂ɏ��Ƃ��Ďg��
 *
 * @param   cuw			COMM_UNIONROOM_WORK
 * @param   no			OBJID(�����Ƃ���-1����j
 *
 * @retval  int			�ʐM�J�n�ł��邩�H�ǂ�����Ԃ�
 *						UNION_PARENT_CONNECT_OK:�b�|���ʐM���ł���
 *						UNION_PARENT_OEKAKI_OK:���G���������ʐM���ł���
 *						UNION_PARENT_CONNECT_NG:�ʐM�ł��Ȃ�
 */
//==============================================================================
int Union_ConnectIdSet( COMM_UNIONROOM_WORK *cuw, int no )
{
	MYSTATUS *status;
	_GF_BSS_DATA_INFO *gfbssdata;
	UNION_BEACON_STATE *beaconState;
	// �X�N���v�g����́{�P�ł���̂łP����
	no--;
	
	status       = CommMPGetBconMyStatus( no );

	// �b���|���O�����[�N�N���A
	Union_CommWorkClear( cuw );

	// status��NULL�������ꍇ�͘b���|���Ɏ��s����i���߂񂢂��������񂾁j
	if(status==NULL){
		return UNION_PARENT_CONNECT_NG;
	}

	gfbssdata    = (_GF_BSS_DATA_INFO *)cuw->UnionBeaconTbl[no]->gameInfo.userGameInfo;
	beaconState  = (UNION_BEACON_STATE *)gfbssdata->regulationBuff;
	debug_beacon = beaconState;

	OS_Printf("�r�[�R����%d \n",beaconState->mode);

#ifdef OEKAKI_ONLY_TALK
	return UNION_PARENT_OEKAKI_OK;
#endif

	switch(beaconState->mode){
	case UNION_PARENT_MODE_FREE:
		return UNION_PARENT_CONNECT_OK;
		break;
	case UNION_PARENT_MODE_OEKAKI_FREE:
		return UNION_PARENT_OEKAKI_OK;
		break;
	case UNION_PARENT_MODE_RECORD_FREE:
		return UNION_PARENT_RECORD_OK;
		break;
	case UNION_PARENT_MODE_GURUGURU_FREE:
		return UNION_PARENT_GURUGURU_OK;
		break;
	case UNION_PARENT_MODE_BUSY:		case UNION_PARENT_MODE_CARDNOW:	case UNION_PARENT_MODE_BATTLENOW:
	case UNION_PARENT_MODE_TRADENOW:	case UNION_PARENT_MODE_OEKAKINOW: case UNION_PARENT_MODE_PARTY:
		return UNION_PARENT_CONNECT_NG;
		break;
	}
	return UNION_PARENT_CONNECT_NG;
}


//==============================================================================
/**
 * $brief   ����̃r�[�R����Ԃ��m�F������Őڑ��ɍs��
 *
 * @param   cuw		
 * @param   no		OBJID�i�{�P����Ă���̂�-1���Ĉ����j
 *
 * @retval  int		UNION_CONNECT_OK��UNION_CONNECT_NG
 */
//==============================================================================
int Union_ConnectStart( COMM_UNIONROOM_WORK *cuw, int objno, u16 type )
{
	MYSTATUS *status;
	_GF_BSS_DATA_INFO *gfbssdata;
	UNION_BEACON_STATE *beaconState;
	// �X�N���v�g����́{�P�ł���̂łP����
	objno--;
	
	status      = CommMPGetBconMyStatus( objno );
	gfbssdata   = (_GF_BSS_DATA_INFO *)cuw->UnionBeaconTbl[objno]->gameInfo.userGameInfo;
	beaconState = (UNION_BEACON_STATE *)gfbssdata->regulationBuff;
	debug_beacon = beaconState;


	// ����̒ʐM��Ԃ��m�F���Đڑ�ON��NG���𔻒f����
	switch(beaconState->mode){
	// �t���[�E���R�[�h�R�[�i�[��W���E���邮�������W���̏ꍇ�̓f�[�^�V�F�A�����O�ʐM
	case UNION_PARENT_MODE_GURUGURU_FREE:
		if(type!=UNION_PARENT_GURUGURU_OK){
			return UNION_PARENT_CONNECT_NG;
		}
		cuw->CommChildSelectEvent = UNION_CHILD_SELECT_GURUGURU;
		cuw->CommConnectId        = objno;
		cuw->CommConnectStartFlag = MP_CONNECT_START;
		cuw->CommConnectStartWait = 0;
		cuw->CommConnectResult    = UNION_CONNECT_BUSY;
		return UNION_PARENT_CONNECT_OK;
		break;
	case UNION_PARENT_MODE_RECORD_FREE:
		if(type!=UNION_PARENT_RECORD_OK){
			return UNION_PARENT_CONNECT_NG;
		}
		cuw->CommChildSelectEvent = UNION_CHILD_SELECT_RECORD;
		cuw->CommConnectId        = objno;
		cuw->CommConnectStartFlag = DS_CONNECT_START;
		cuw->CommConnectStartWait = 0;
		cuw->CommConnectResult    = UNION_CONNECT_BUSY;
		return UNION_PARENT_CONNECT_OK;
		break;
	case UNION_PARENT_MODE_FREE:
		if(type!=UNION_PARENT_CONNECT_OK){
			return UNION_PARENT_CONNECT_NG;
		}
		cuw->CommConnectId        = objno;
		cuw->CommConnectStartFlag = DS_CONNECT_START;
		cuw->CommConnectStartWait = 0;
		cuw->CommConnectResult    = UNION_CONNECT_BUSY;
		return UNION_PARENT_CONNECT_OK;
		break;
	// ����������W���̏ꍇ��MP�ʐM
	case UNION_PARENT_MODE_OEKAKI_FREE:
		if(type!=UNION_PARENT_OEKAKI_OK){
			return UNION_PARENT_CONNECT_NG;
		}
		cuw->CommConnectId        = objno;
		cuw->CommConnectStartFlag = MP_CONNECT_START;
		cuw->CommConnectStartWait = 0;
		cuw->CommConnectResult    = UNION_CONNECT_BUSY;
		return UNION_PARENT_CONNECT_OK;
		break;
	// �����ʐM���̏ꍇ�������͎󂯓����Ԃɖ����Ƃ��͐ڑ����Ȃ�
	case UNION_PARENT_MODE_BUSY:		case UNION_PARENT_MODE_CARDNOW:	case UNION_PARENT_MODE_BATTLENOW:
	case UNION_PARENT_MODE_TRADENOW:	case UNION_PARENT_MODE_OEKAKINOW: case UNION_PARENT_MODE_PARTY:
		return UNION_PARENT_CONNECT_NG;
		break;

	}
	GF_ASSERT(0);

	return 0;
}

//==============================================================================
/**
 * �b�������Őڑ����Ă݂����ʂ�Ԃ�
 *
 * @param   cuw		COMM_UNIONROOM_WORK
 *
 * @retval  u32		0:�r��	1:����	2:���s	3:�������e�ɂȂ���
 */
//==============================================================================
u32 Union_ConnectResultGet(COMM_UNIONROOM_WORK *cuw )
{
	return cuw->CommConnectResult;
}



//==============================================================================
/**
 * �X�N���v�g�Ƀ��j�I�����[��������s������e��Ԃ�
 *
 * @param   cuw		
 *
 * @retval  u32		
 */
//==============================================================================
u32 Union_ParentStartCommandSet( COMM_UNIONROOM_WORK *cuw )
{
//	u8 start;
//	if(cuw->CommNextProcOn){
//		cuw->CommNextProcOn = 0;
//		start = 1;
//		return cuw->UnionEventWork;
//	}

	// �ʐM���q�����Ă���Ԃ͐e�@�̃R�}���h��Ԃ����A�ؒf���ꂽ�ꍇ�͂����ɏI����n��
	if(cuw->UnionEndConnectFlag){
		return UNION_CHILD_SELECT_CANCEL;
	}

	if(CommGetConnectNum()<2){
		return UNION_CHILD_SELECT_CANCEL;
	}

	if(CommGetCurrentID()==0){
		// �e�@�ڑ��̎��̐ڑ��m�F
		if(CommStateIsUnionParentConnectSuccess()==TRUE){
			return cuw->UnionEventWork;
		}
	}else{
		// �q�@�ڑ��̎��̐ڑ��m�F
		if(CommStateIsUnionConnectSuccess()==TRUE){
			return cuw->UnionEventWork;
		}
	}
	return UNION_CHILD_SELECT_CANCEL;
	
}


//==============================================================================
/**
 * �q�@�̑I����e���X�N���v�g�ɒʒm����
 *
 * @param   cuw		
 *
 * @retval  u32		
 */
//==============================================================================
u32 Union_ChildSelectCommandSet( COMM_UNIONROOM_WORK *cuw )
{
	OS_TPrintf("�e�@���q�@�̑I��҂� �ڑ����=%d\n",CommStateIsUnionParentConnectSuccess());

	// �e�@�ڑ��̎��̐ڑ��m�F
	if(CommStateIsUnionParentConnectSuccess()==TRUE){
		return cuw->CommChildSelectEvent;
	}
	
	// �q�����Ă��Ȃ��̂ŁA�L�����Z��
	return UNION_CHILD_SELECT_CANCEL;
}
//==============================================================================
/**
 * �X�N���v�g���ŏ������ꂽ�I�����̌��ʂ����炤
 *
 * @param   cuw			COMM_UNIONROOM_WORK
 * @param   var			�X�N���v�g�����s�����I���̎��
 * @param   result		���ʁi�I���ɂ���ĈႤ�j
 *
 * @retval  none		
 */
//==============================================================================
void Union_ScriptResultGet( COMM_UNIONROOM_WORK *cuw, int var, u32 result)
{
	u8 command = (u8)result;
	
	switch(var){
	case 0:
		if(cuw->UnionEndConnectFlag==0){
			PRINT2("�I����e��%d\n",result);
			cuw->ScriptSelectWork = command;
			CommSendData(CU_PLAYER_SELECT,&command,1);
		}
		break;
	case 1:
		// �e�̂͂��E�������ɂ��
		if(result==0){
			u8 start = cuw->CommChildSelectEvent;
			CommSendData_ServerSide(CU_START_NEXT, &start, 1);
			cuw->ScriptYesNoWork = result;
		}else{
			u8 start = UNION_CHILD_SELECT_CANCEL;					//�e�@�͂�������I�񂾂̂Łu�L�����Z���v�𑗐M
			CommSendData_ServerSide(CU_START_NEXT, &start, 1);
			cuw->ScriptYesNoWork = result;
		}
		break;
	}
}


















//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// comm_command_field.c�ɓo�^���Ă���ʐM�R�[���o�b�N�֐��Q
//------------------------------------------------------------------------------


void CommUnionRecvStatus(int netID, int size, void* pBuff, void* pWork)
{
	PRINT("�X�e�[�^�X��M����\n");
}

void CommUnionRecvTalk(int netID, int size, void* pBuff, void* pWork)
{
	PRINT2("%d����̉�b��M����\n",netID);	
}


//==============================================================================
/**
 * $brief   �e���C�G�X�i���͂����ĂȂ��j
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommUnionRecvYes(int netID, int size, void* pBuff, void* pWork)
{
	PRINT2("%d�����  �x�d�r\n",netID);	
	
}
//==============================================================================
/**
 * $brief   �e���m�n�ƌ����Ă����Ƃ��̃R�[���o�b�N
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommUnionRecvNo(int netID, int size, void* pBuff, void* pWork)
{
	FIELDSYS_WORK *fsys = (FIELDSYS_WORK *)pWork;

	PRINT2("%d�����  �m�n\n",netID);
	// �L�����Z�������̂Őؒf�E�r�[�R�����W�֕��A
	//	CommStateExitUnion();
   	_changeState(fsys->union_work, _UnionStart, _FINALIZE_TIME);
	CommUnion_EventFlagClear(fsys->union_work);

}

static int debug_union_select;

//==============================================================================
/**
 * �q�@�̑I����e����M����
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommUnionRecvSelect(int netID, int size, void* pBuff, void* pWork)
{
	FIELDSYS_WORK *fsys = (FIELDSYS_WORK *)pWork;
	u8 *no = (u8*)pBuff;
	
	// �I���R�}���h���󂯎���Ă��Ȃ���ΑI���C�x���g���̗p����
	if(fsys->union_work->UnionEndConnectFlag==0){
		fsys->union_work->CommChildSelectEvent = *no;
		debug_union_select = *no;
	}

	PRINT("�I������M����\n");
	

}

//==============================================================================
/**
 * �X�^�[�g�f�[�^��M�R�[���o�b�N
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommUnionStartNext(int netID ,int size, void* pBuff, void* pWork)
{
	FIELDSYS_WORK *fsys = (FIELDSYS_WORK *)pWork;
	u8 *no = (u8*)pBuff;
	
	PRINT("�C�x���g�J�n�R�}���h����\n");

	// �C�x���g�J�n�t���O�����Ă�i�e�@�ɃC�x���g�J�n�R�}���h�𔭍s������j
	fsys->union_work->CommNextProcOn = 1;

	// �e�@����J�n����C�x���g�̎�ނ������Ă���i�e�@�ɂ��͂��j
	fsys->union_work->UnionEventWork = *no;

	if(*no == UNION_CHILD_SELECT_OEKAKI){
		CommStateUnionPictureBoardChange();
//		_changeState(fsys->union_work, _UnionRestart, 0);
	}

}

//==============================================================================
/**
 * �ʐM�I���f�[�^��M�R�[���o�b�N
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommUnionEndConnect(int netID ,int size, void* pBuff, void* pWork)
{
	FIELDSYS_WORK *fsys = (FIELDSYS_WORK *)pWork;

	// �ʐM�I���R�}���h
	fsys->union_work->UnionEndConnectFlag = 1;

	OS_TPrintf("�e�@����I���R�}���h���󂯎����\n");
}


//==============================================================================
/**
 * @brief   �ڑ��I���t���O��Ԃ�
 *
 * @param   cuw		
 *
 * @retval  int		
 */
//==============================================================================
int Union_CancelRecv( COMM_UNIONROOM_WORK *cuw )
{
	return cuw->UnionEndConnectFlag;
}

//==============================================================================
/**
 * @brief   �e�@����L�����Z���𑗐M����
 *
 * @param   core->fsys->union_work		
 *
 * @retval  none		
 */
//==============================================================================
int Union_ParentSendCancel( COMM_UNIONROOM_WORK *cuw, int mes )
{
	// �q�@����̃C�x���g�I�����������Ă��Ȃ���Α��M����
	if(cuw->CommChildSelectEvent==0){
		CommSendData( CU_END_CONNECT_SERVER, NULL, 0);
		return mes;
	}

	return 0;
}

//==============================================================================
/**
 * $brief   �g���[�i�[�J�[�h�f�[�^�̃R�s�[
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommUnionRecvTrainerCard(int netID ,int size, void* pBuff, void* pWork )
{
	FIELDSYS_WORK *fsys      = (FIELDSYS_WORK *)pWork;
	TR_CARD_DATA  *trcard    = (TR_CARD_DATA*)pBuff;
	MYSTATUS	  *friend    = CommInfoGetMyStatus(CommGetCurrentID()^1);
	void          *fnoteWork;

//	OS_Printf("id = %d  size = %d ",netID, size);
	// �����ƈႤ�h�c�̐l�̃g���[�i�[�J�[�h�f�[�^���R�s�[
//	if(netID!=CommGetCurrentID()){
//		MI_CpuCopyFast( pBuff, fsys->union_work->recv_trcard[ne,  size );
//	}

	{
		int i,tmp=0;
		u8 *p = (u8*)pBuff;
		for(i=0;i<sizeof(TR_CARD_DATA);i++){
			tmp ^= p[i];
		}
		OS_Printf(" recv id = %d  xor %d \n", netID, tmp);
	}
	trcard->reached = 1;

	// �`���m�[�g����
	if(netID!=CommGetCurrentID()){
		fnoteWork = FNOTE_SioUnionGreetDataMake(  (STRCODE*)MyStatus_GetMyName(friend),  MyStatus_GetMySex(friend), HEAPID_UNIONROOM );
		FNOTE_DataSave( fsys->fnote, fnoteWork, FNOTE_TYPE_SIO );
	}
}


//------------------------------------------------------------------
/**
 * $brief   �g���[�i�[�J�[�h�f�[�^��M�R�[���o�b�N�֐�
 *
 * @param   netID		
 * @param   pWork		
 * @param   size		
 *
 * @retval  u8*		
 */
//------------------------------------------------------------------
u8* getTrainerCardRecvBuff( int netID, void* pWork, int size)
{
	FIELDSYS_WORK *fsys       = (FIELDSYS_WORK *)pWork;
	COMM_UNIONROOM_WORK *cuw  = fsys->union_work;

	
	return (u8*)cuw->recv_trcard[netID];
}


//------------------------------------------------------------------
/**
 * $brief   �퓬�O�|�P�������X�g���ʎ擾�֐�
 *
 * @param   netID		
 * @param   pWork		
 * @param   size		
 *
 * @retval  u8*		
 */
//------------------------------------------------------------------
void CommUnionRecvBattlePokeListResult(int netID ,int size, void* pBuff, void* pWork )
{
	FIELDSYS_WORK *fsys       = (FIELDSYS_WORK *)pWork;
	COMM_UNIONROOM_WORK *cuw  = fsys->union_work;
	u8 *result				  = (u8*)pBuff;

	OS_TPrintf("id = %d ��  %d\n", netID, *result);

	cuw->battleSelect[netID] = *result;

}



//==============================================================================
/**
 * @brief   �퓬�O�|�P�������X�g���Ă񂾌��ʂ͂ǂ����������H
 *
 * @param   cuw		
 *
 * @retval  u16		
 */
//==============================================================================
u16  Union_GetBattleStartCheckResult( COMM_UNIONROOM_WORK *cuw )
{
	int myid = CommGetCurrentID();
	
	// �������L�����Z������
	if(cuw->battleSelect[myid]==UNION_BATTLE_POKELIST_NG){
		return UNION_BATTLE_MY_CANCEL;
	}

	// ����ɃL�����Z�����ꂽ
	if(cuw->battleSelect[myid^1]==UNION_BATTLE_POKELIST_NG){
		return UNION_BATTLE_PARTNER_CANCEL;
	}

	// �o��OK
	return UNION_BATTLE_OK;
}

//==============================================================================
/**
 * @brief   ���j�I�����[���O�̃|�P�������X�g�̑I�����ʂ𑗐M����
 *
 * @param   result		
 *
 * @retval  none		
 */
//==============================================================================
void Union_BattlePokeListResult( int result )
{
	u8	command = result;
	CommSendData( CU_BATTLE_PLIST_RET,&command, 1 );
}






//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// ���j�I�����[���p�c�[��
//------------------------------------------------------------------------------


#define TALK_CARD_MAX		( 2 )
#define TALK_TRADE_MAX		( 2 )
#define TALK_BATTLE_MAX		( 4 )
#define TALK_OEKAKI_MAX		( 4 )
#define TALK_RECORD_MAX		( 4 )
#define TALK_GURUGURU_MAX	( 4 )

static const talk_table_card[TALK_CARD_MAX][2]={
	{	msg_union_talkboy_01_03,msg_union_talkgirl_01_03},
	{	msg_union_talkboy_01_04,msg_union_talkgirl_01_04},
};
static const talk_table_oekaki[TALK_OEKAKI_MAX][2]={
	{	msg_union_talkboy_02_09,msg_union_talkgirl_02_09},
	{	msg_union_talkboy_02_10,msg_union_talkgirl_02_10},
	{	msg_union_talkboy_02_11,msg_union_talkgirl_02_11},
	{	msg_union_talkboy_02_12,msg_union_talkgirl_02_12},
};
static const talk_table_battle[TALK_BATTLE_MAX][2]={
	{	msg_union_talkboy_03_05,msg_union_talkgirl_03_05},
	{	msg_union_talkboy_03_06,msg_union_talkgirl_03_06},
	{	msg_union_talkboy_03_07,msg_union_talkgirl_03_07},
	{	msg_union_talkboy_03_08,msg_union_talkgirl_03_08},
};
static const talk_table_trade[TALK_TRADE_MAX][2]={
	{	msg_union_talkboy_04_04,msg_union_talkgirl_04_04},
	{	msg_union_talkboy_04_05,msg_union_talkgirl_04_05},
};
static const talk_table_record[TALK_RECORD_MAX][2]={
	{	msg_union_talkboy_06_09,msg_union_talkgirl_06_09},
	{	msg_union_talkboy_06_10,msg_union_talkgirl_06_10},
	{	msg_union_talkboy_06_11,msg_union_talkgirl_06_11},
	{	msg_union_talkboy_06_12,msg_union_talkgirl_06_12},
};
static const talk_table_guruguru[TALK_GURUGURU_MAX][2]={
	{	msg_union_talkboy_07_10,msg_union_talkgirl_07_10},
	{	msg_union_talkboy_07_11,msg_union_talkgirl_07_11},
	{	msg_union_talkboy_07_12,msg_union_talkgirl_07_12},
	{	msg_union_talkboy_07_13,msg_union_talkgirl_07_13},
};
// �Q�[���J�n���̃��b�Z�[�W
static const talk_start_table[][2]={
	{ msg_union_talkboy_01_03,msg_union_talkgirl_01_03,},	// �J�[�h
	{ msg_union_talkboy_03_02,msg_union_talkgirl_03_02,},	// ��������
	{ msg_union_talkboy_04_02,msg_union_talkgirl_04_02,},	// ��������
	{ msg_union_talkboy_02_02,msg_union_talkgirl_02_02,},	// ���������v
	{ msg_union_talkboy_06_02,msg_union_talkgirl_06_02,},	// ���R�[�h�v
	{ msg_union_talkboy_07_02,msg_union_talkgirl_07_02,},	// ���邮������v
};
// �b�����������������Ƃ�
static const talk_start_child_table[2]={
	msg_union_talkboy_00_02,msg_union_talkgirl_00_02
};
// �b�������������ς������Ƃ�
static const talk_failed_child_table[2]={
	msg_union_talkboy_00_05,msg_union_talkgirl_00_05
};

// �V�т�f��ꂽ�Ƃ�
static const talk_failed_table[][2]={
	{msg_union_talkboy_01_02,msg_union_talkgirl_01_02},
	{msg_union_talkboy_02_03,msg_union_talkgirl_02_03},
	{msg_union_talkboy_03_03,msg_union_talkgirl_03_03},
	{msg_union_talkboy_04_03,msg_union_talkgirl_04_03},
	{msg_union_talkboy_07_03,msg_union_talkgirl_07_03},
	{msg_union_talkboy_06_03,msg_union_talkgirl_06_03},
};

// �����𖞂����Ă��Ȃ��̂ŁA�U���Ȃ�
static const event_reject_table[][2]={
	{msg_union_talkboy_03_04,msg_union_talkgirl_03_04},	// LV30�ȉ����Q�C���Ȃ��̂őΐ�ł��Ȃ�
	{msg_union_talkboy_04_06,msg_union_talkgirl_04_06},	// 2�C�ȏ�Ă��������Ȃ��̂Ō����ł��Ȃ�
	{msg_union_talkboy_07_04,msg_union_talkgirl_07_04},	// �^�}�S�������Ă��Ȃ��̂ł��邮��ł��Ȃ�
};

static const talk_anster_wait_table[][2]={
	{ msg_union_talkboy_01_01,msg_union_talkgirl_01_01,},	// �J�[�h
	{ msg_union_talkboy_03_01,msg_union_talkgirl_03_01,},	// ��������
	{ msg_union_talkboy_04_01,msg_union_talkgirl_04_01,},	// ��������
	{ msg_union_talkboy_02_01,msg_union_talkgirl_02_01,},	// ���������v
	{ msg_union_talkboy_06_01,msg_union_talkgirl_06_01,},	// ���R�[�h�v
	{ msg_union_talkboy_07_01,msg_union_talkgirl_07_01,},	// ���邮������v

};
static const talk_joinus_table[][2]={
	{ msg_union_talkboy_02_05,msg_union_talkgirl_02_05,},	// ���������v
	{ msg_union_talkboy_06_05,msg_union_talkgirl_06_05,},	// ���R�[�h�v
	{ msg_union_talkboy_07_05,msg_union_talkgirl_07_05,},	// ���邮������v
};
static const talk_join_success_table[][2]={
	{ msg_union_talkboy_02_07,msg_union_talkgirl_02_07,},	// ���������v
	{ msg_union_talkboy_06_07,msg_union_talkgirl_06_07,},	// ���R�[�h�v
	{ msg_union_talkboy_07_07,msg_union_talkgirl_07_07,},	// ���邮������v
};
static const talk_join_no_table[][2]={
	{ msg_union_talkboy_02_06,msg_union_talkgirl_02_06,},	// ���������v
	{ msg_union_talkboy_06_06,msg_union_talkgirl_06_06,},	// ���R�[�h�v
	{ msg_union_talkboy_07_06,msg_union_talkgirl_07_06,},	// ���邮������v
};
// �ق��ɂ��Ȃɂ�����H
static const int talk_next_selct_table[]={
	msg_union_talkboy_00_04,msg_union_talkgirl_00_04
};

//�܂������������Ă����
static const int talk_connect_cancel_table[2]={
	msg_union_talkboy_05_01,msg_union_talkgirl_05_01
};

static const int talk_connect_canceled_table[2]={
	msg_union_talkboy_00_03,msg_union_talkgirl_00_03
};

// SXY��ł�OBJ�̔z�u���������Ȃ��̂ŕ␳�p�e�[�u��
const u16 Union_GroupObjTable[]={
	10,14,18,22,26,30,34,38,42,46
};

//------------------------------------------------------------------
/**
 * @brief   �b��������OBJ�̐e�@��ID��Ԃ�
 *
 * @param   no		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int ChildToParentNo(int no)
{
	int i,r,result;
	for(i=0;i<TALK_OBJ_MAX;i++){
		if(Union_GroupObjTable[i]<=no && (Union_GroupObjTable[i]+4)>no){
			return i;
		}
	}
	return -1;
}


//------------------------------------------------------------------
/**
 * $brief   �ڑ��ɂ͂Ȃ�Ȃ�����Ƃ̉�b�ԍ����擾
 *
 * @param   cuw		
 * @param   no		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int GetGroupTalk_ListenNo( COMM_UNIONROOM_WORK *cuw, int no )
{
	int sex,target;
	MYSTATUS *status;
	_GF_BSS_DATA_INFO *gfbssdata;
	UNION_BEACON_STATE *beaconState;

	// 10�ȏ�͎q�@�Ȃ̂ŁA�e�@�̉�b�ɂԂ炳����悤�ɂ���
	if(no>9){
		// �N�̎q�@��
		target = ChildToParentNo( no );
		GF_ASSERT( no!=-1 && "�q�@OBJID�͐e�@���Ђ��Ȃ�����" );
		OS_Printf("��֕Ԏ� %d ��  %d\n",no, target);
	}else{
		target = no;
	}
	
	// ��b�擾�J�n
	status      = CommMPGetBconMyStatus( target );
	gfbssdata   = (_GF_BSS_DATA_INFO *)cuw->UnionBeaconTbl[target]->gameInfo.userGameInfo;
	beaconState = (UNION_BEACON_STATE *)gfbssdata->regulationBuff;

	// �r�[�R����񂪖�������
	if(status==NULL){
		return msg_union_talkboy_00_05;
	}

	// �e�̎��̂͐e�̐��ʁA�q�̎��͎q�̐���
	if(no>9){
		sex = beaconState->c_face[(no-10)%4];
		sex = sex>>7;	// �ŏ�ʂ�����
	}else{
		sex = MyStatus_GetMySex(status);
	}
	
	OS_Printf("�Ԏ����[�h %d \n",beaconState->mode);
	switch(beaconState->mode){
	// �Ƃ肱�ݒ��̂悤���c
	case UNION_PARENT_MODE_BUSY:
	case UNION_PARENT_MODE_PARTY:

//		OS_Printf("���ԍ� = %d   �n�� = %d \n",beaconState->nation, beaconState->city);

		return talk_failed_child_table[sex];
		break;
	case UNION_PARENT_MODE_CARDNOW:
		return talk_table_card[gf_rand()%TALK_CARD_MAX][sex];
		break;
	case UNION_PARENT_MODE_BATTLENOW:
		return talk_table_battle[gf_rand()%TALK_BATTLE_MAX][sex];
		break;
	case UNION_PARENT_MODE_TRADENOW: 
		return talk_table_trade[gf_rand()%TALK_TRADE_MAX][sex];
		break;
	
	
	case UNION_PARENT_MODE_OEKAKINOW:
	case UNION_PARENT_MODE_OEKAKI_FREE:
		return talk_table_oekaki[gf_rand()%TALK_OEKAKI_MAX][sex];
		break;
	case UNION_PARENT_MODE_RECORDNOW:
	case UNION_PARENT_MODE_RECORD_FREE:
		return talk_table_record[gf_rand()%TALK_RECORD_MAX][sex];
		break;
	case UNION_PARENT_MODE_GURUGURUNOW:
	case UNION_PARENT_MODE_GURUGURU_FREE:
		return talk_table_guruguru[gf_rand()%TALK_GURUGURU_MAX][sex];
		break;
	}
	// �e�@�̐ڑ����[�h����������
	return msg_union_talkboy_00_05;

}


//==============================================================================
/**
 * $brief   �J�[�h��������O�̕�����ݒ�i���E�n����Q�Ƃ��Ĕ��肷��j
 *
 * @param   wordset		
 *
 * @retval  int		
 */
//==============================================================================
int Union_GetCardTalkNo( WORDSET *wordset )
{
	u8 myNation,partnerNation;
	u8 myArea,  partnerArea; 

	//�����Ƒ���̍��E���Z�n�𓾂�
	myNation      = CommInfoGetMyNation(CommGetCurrentID());
	partnerNation = CommInfoGetMyNation(CommGetCurrentID()^1);
	myArea        = CommInfoGetMyArea(CommGetCurrentID());
	partnerArea   = CommInfoGetMyArea(CommGetCurrentID()^1);

	OS_Printf("�����̍�   %d ����̍�   %d\n",myNation, partnerNation);
	OS_Printf("�����̒n�� %d ����̒n�� %d\n",myArea, partnerArea);

	// ���肪������͂��Ă��Ȃ�
	if(partnerNation==0){
		return msg_union_connect_01_02_3;
	}

	// ���ԍ������݂��Ă���ꍇ�͕�������Z�b�g
	if(partnerNation!=0){
		WORDSET_RegisterCountryName( wordset, 3, partnerNation );

		// �n��ԍ������݂��Ă���ꍇ�͕�������Z�b�g
		if(partnerArea!=0){
			WORDSET_RegisterLocalPlaceName( wordset, 4, partnerNation, partnerArea );
		}

	}

	// �\�������񔻒�
	
	// �����Ⴄ
	if(myNation!=partnerNation){
		// �n�悪�Ȃ�
		if(partnerArea==0){
			return msg_union_connect_01_02_1;
		}
		// �n�悪���Ȃ�
		if(myArea==partnerArea){
			return msg_union_connect_01_02_1; 
		}
		// �n�悪�Ⴄ
		return msg_union_connect_01_02;
	}

	// ��������
	if(myArea!=partnerArea){
		// �n�悪�Ⴄ
		return msg_union_connect_01_02_2;
	}
	
	//�n�悪����
	return msg_union_connect_01_02_3;

}

//------------------------------------------------------------------
/**
 * $brief   �V�юn�߂�Ƃ��̉�b�i�J�[�h�̎������Z��ł���ꏊ�ɑΉ�����j
 *
 * @param   event		���j�I�����s���V��
 * @param   sex			����
 *
 * @retval  int			��b�ԍ�
 */
//------------------------------------------------------------------
static int GetStartTalk_No(int event, int sex, WORDSET *wordset )
{
	
	// �J�[�h����Ȃ��Ƃ��̓e�[�u�����炻�ꂼ��Q�Ƃ���
	if( event!=(UNION_CHILD_SELECT_CARD-1) ){
		OS_Printf("eventno = %d \n", event);
		return talk_start_table[event][sex];
	}

	// �J�[�h��������O�ɍ��E�n���񂩂画�肵�ĕ������ݒ肷��
	return Union_GetCardTalkNo( wordset );

}
//==============================================================================
/**
 * $brief   �b�|���ŒʐM�ڑ��ł��Ȃ����ɏo����b�̃C���f�b�N�X��n������
 *
 * @param   cuw		���j�I�����[�N
 * @param   no		�b��������Ώۂ�OBJ�̔ԍ�
 *
 * @retval  int		���b�Z�[�W�C���f�b�N�X
 */
//==============================================================================
int Union_GetTalkNumber( COMM_UNIONROOM_WORK *cuw, int no, int mode, WORDSET *wordset )
{
	int sex;
	MYSTATUS *status;

	// �X�N���v�g����́{�P�ł���̂łP����
	no--;

	OS_Printf("��b�擾�s�� OBJNO = %d  mode=%d  ScriptWork=%d \n",no,mode,cuw->ScriptSelectWork-1);

	// �ڑ��͂ł��Ȃ��O���[�v�Ƃ̉�b
	if(mode==UNION_NO_CONNECT_TALK){
		return GetGroupTalk_ListenNo( cuw, no );
	}

	status = CommMPGetBconMyStatus( no );
	sex    = MyStatus_GetMySex(status);

	switch(mode){
	// �ڑ�������������ŁA�s�����e�����܂������̉�b
	case UNION_CONNECTED_START_TALK:
		return GetStartTalk_No( cuw->ScriptSelectWork-1, sex, wordset );
//		return talk_start_table[cuw->ScriptSelectWork-1][sex];
		break;

	// �b�������Őڑ��ł����Ƃ��i�q�@���Łj
	case UNION_CONNECT_SUCCESS_TALK:
		return talk_start_child_table[sex];
		break;
	// ��������E�������񓙂������������Ƃ��ɗ����Z���t(�q�@���Łj
	case UNION_CONNECT_ANSWER_WAIT:
		// ���ɃL�����Z������Ă���
		if(cuw->ScriptSelectWork==0){
			OS_Printf("�L�����Z������Ă���̂ŃX�L�b�v\n");
			return 0;
		}
		// �����̑I�����L���ɂȂ��Ă���
		return talk_anster_wait_table[cuw->ScriptSelectWork-1][sex];
		break;

	//�|�P�������Q�C�ȏ㎝���Ă��Ȃ��ƌ����͂ł��Ȃ���
	case UNION_CONNECT_BATTLE_REJECT:
	case UNION_CONNECT_TRADE_REJECT:
	case UNION_CONNECT_GURUGURU_REJECT:
		return event_reject_table[mode-UNION_CONNECT_BATTLE_REJECT][sex];
		break;
	// �u���[��A���܂͂�����邢�񂾁A�܂����x�ˁv
	case UNION_TALK_CANCEL_CARD:	case UNION_TALK_CANCEL_OEKAKI:
	case UNION_TALK_CANCEL_BATTLE:	case UNION_TALK_CANCEL_TRADE:
	case UNION_TALK_CANCEL_GURUGURU:	case UNION_TALK_CANCEL_RECORD:
		return talk_failed_table[mode-UNION_TALK_CANCEL_CARD][sex];
		break;

	// �u��������Ɂ������Ȃ��H�v
	case  UNION_JOIN_OEKAKI_TALK:
	case  UNION_JOIN_RECORD_TALK:
	case  UNION_JOIN_GURUGURU_TALK:
		return talk_joinus_table[mode-UNION_JOIN_OEKAKI_TALK][sex];
		break;

	// �u����A�͂����Ă��Ȃ�I�v
	case  UNION_SUCCESS_OEKAKI_JOIN:
	case  UNION_SUCCESS_RECORD_JOIN	:
	case  UNION_SUCCESS_GURUGURU_JOIN:
		return talk_join_success_table[mode-UNION_SUCCESS_OEKAKI_JOIN][sex];
		break;

	// �u�����A����܂����Ăˁc�v
	case  UNION_JOIN_OEKAKI_NO:
	case  UNION_JOIN_RECORD_NO:
	case  UNION_JOIN_GURUGURU_NO:
		return talk_join_no_table[mode-UNION_JOIN_OEKAKI_NO][sex];
		break;

	// �ق��ɂ��Ȃɂ�����H
	case UNION_SELECT_NEXT_TALK:
		return talk_next_selct_table[sex];
		break;

	// �u�Ȃɂ��������Ȃ�����܂����������Ă����v
	case UNION_TALK_CONNECT_CANCEL:
		return talk_connect_cancel_table[sex];
		break;

	// �u���A���߂�悤�������邩��v
	case UNION_TALK_CONNECT_CANCELED:
		return talk_connect_canceled_table[sex];
		break;

	}
	
	// �����܂ō~��Ă��鎖�������Ă͂����Ȃ�
	GF_ASSERT(0);
	return msg_union_talkboy_00_05;

}


//------------------------------------------------------------------
/**
 * $brief   �ڑ����̗F�B�̎p�������r�[�R�����쐬����
 *
 * @param   state	
 * @param   num		�ڑ��l��
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void ConnectChildViewSet( UNION_BEACON_STATE  *state, int num )
{
	MYSTATUS *friendstatus;
	int i,count=0;

	// 2�l�ڑ��ł�ID��1����Ȃ���������Ȃ�
	for(i=1;i<UNION_CONNECT_CHILD_MAX+1;i++){
		int pos = i-1;
		friendstatus = CommInfoGetMyStatus(i);
		
		if(friendstatus!=NULL){
			state->c_id[pos]   = MyStatus_GetID( friendstatus );
			state->c_face[pos] = MyStatus_GetTrainerView( friendstatus ) | (MyStatus_GetMySex( friendstatus )<<7);
		}else{
			state->c_id[pos]   = 0;
			state->c_face[pos] = 0;
		}
	}
}

//------------------------------------------------------------------
/**
 * $brief   ���ݍs���Ă���r�[�R���ɏ���������
 *
 * @param   flag		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void Union_BeaconChange( int flag )
{
	UNION_BEACON_STATE state;

	MI_CpuClear8( &state, sizeof(UNION_BEACON_STATE) );
	switch(flag){
	// �b�������\���
	case UNION_PARENT_MODE_FREE:
		break;
	// ���j���[���J���đ��肪�ł��Ȃ�
	case UNION_PARENT_MODE_BUSY:
		break;
	// �b�������ɐ������A2�l�ڑ��ɂȂ������
	case UNION_PARENT_MODE_PARTY:	
		ConnectChildViewSet( &state, 2 );
		break;
	// ���݌�����ʂɂ���i�̂ł����q����Ȃ��j
	case UNION_PARENT_MODE_TRADENOW:
	case UNION_PARENT_MODE_CARDNOW:
	case UNION_PARENT_MODE_BATTLENOW:
		ConnectChildViewSet( &state, 2 );
		break;

	// ���݂��������{�[�h�ɂ��āA���ł�5�l���܂��Ă���i�̂ł����q����Ȃ��j
	case UNION_PARENT_MODE_OEKAKINOW:
		ConnectChildViewSet( &state, 5 );
		break;
	// ���݂��G�����{�[�h�ɂ��Ă܂��󂫂�����̂ŁA�b���������
	case UNION_PARENT_MODE_OEKAKI_FREE:
		ConnectChildViewSet( &state, 4 );
		break;

	// ���݃��R�[�h�R�[�i�[�ɂ��āA���ł�5�l���܂��Ă���i�̂ł����q����Ȃ��j
	case UNION_PARENT_MODE_RECORDNOW:
		ConnectChildViewSet( &state, 5 );
		break;
	// ���݃��R�[�h�R�[�i�[�ɂ��Ă܂��󂫂�����̂ŁA�b���������
	case UNION_PARENT_MODE_RECORD_FREE:
		ConnectChildViewSet( &state, 4 );
		break;

	// ���݂��邮������ɂ��āA���ł�5�l���܂��Ă���i�̂ł����q����Ȃ��j
	case UNION_PARENT_MODE_GURUGURUNOW:
		ConnectChildViewSet( &state, 4 );
		break;
	// ���݂��邮������ɂ��Ă܂��󂫂�����̂ŁA�b���������
	case UNION_PARENT_MODE_GURUGURU_FREE:
		ConnectChildViewSet( &state, 4 );
		break;
	}
	state.mode    = flag;

	CommMPSetMyRegulation(&state);	// �r�[�R����������
	CommMPFlashMyBss();
	
}


//==============================================================================
// ���j�I�����[���̍���̐l�́u���͂Ȃ��v�I�����̉�b���e�e�[�u��
//==============================================================================
static const int InfomationTalkTable[]={
	msg_union_info_02_04,
	msg_union_info_02_05,
	msg_union_info_02_06,
	msg_union_info_02_07,
	msg_union_info_02_08,
	msg_union_info_02_09,
	msg_union_info_02_10,
	msg_union_info_02_11,
	msg_union_info_02_12,
	msg_union_info_02_13,
	msg_union_info_02_14,
	msg_union_info_02_15,
	msg_union_info_02_16,
	msg_union_info_02_17,
	msg_union_info_02_18,
	msg_union_info_02_19,
	msg_union_info_02_20,
	msg_union_info_02_21,
	msg_union_info_02_22,
	msg_union_info_02_23,
};

// �ȈՉ�b�̃��j�I�����[���p�������̏��
#define PMS_DATA_UNION_TALK_NO_MAX		( 20 )

//==============================================================================
/**
 * $brief   ���j�I�����[���̍���̐l��������e�����߂�
 *
 * @param   cuw		
 *
 * @retval  int		�Ή��������b�Z�[�WNO���Ԃ�
 */
//==============================================================================
int Union_GetInfomationTalkNo( COMM_UNIONROOM_WORK *cuw,  WORDSET *wordset )
{
	int i,ret=0,pmsid;
	PMS_WORD pmsword;

	// ���j�I�����[���Ńr�[�R��������ł��邩�H
	for(i=0;i<10;i++){
		if(cuw->UnionBeaconTbl[i]!=NULL){
			ret++;
		}
	}
	
	// ���ꂩ����
	if(ret!=0){
		// �u�Ƃ������������I�v�ƏI��
		return msg_union_info_02_01;
	}

	// �N�����Ȃ��̂ŊȈՉ�b�����ɍs��
	
	OS_Printf("�ȈՉ�b�h�c = %d\n",PMSDAT_GetSentenceType( &cuw->MyPmsData ));

	// �L���ȕ��͂��H
	if(!PMSDAT_IsEnabled( &cuw->MyPmsData )){
		
		return msg_union_info_02_02;
	}
	
	// ���j�I����b���H
	if(PMSDAT_GetSentenceType( &cuw->MyPmsData )!=PMS_TYPE_UNION){
		// ���j�I����b����Ȃ�

		//�g���[�i�[�̌����ڕ�������i�[����
		int view_type = MyStatus_GetTrainerView(cuw->mystatus);
		int sex       = MyStatus_GetMySex(cuw->mystatus);
		
		WORDSET_RegisterTrTypeName( wordset, 0, UnionView_GetTrainerInfo( sex, view_type, UNIONVIEW_MSGTYPE) );

		return msg_union_info_02_03;
	}
	
	pmsid = PMSDAT_GetSentenceID( &cuw->MyPmsData );
	
	// ���j�I����b�͂Q�O�炵���̂ŁA�����Ă�����␳����
	if(pmsid >= PMS_DATA_UNION_TALK_NO_MAX){
		pmsid = 0;
	}
	
	// ������ƊȈՉ�b�P�ꂪ�����Ă���Ȃ�Γo�^����
	// (���j�I����b�ɂ͒P�ꂪ�������̂����݂���j
	if((pmsword=PMSDAT_GetWordNumber( &cuw->MyPmsData, 0 ))!=PMS_WORD_NULL){
		// �ȈՉ�b���t���i�[����
//		WORDSET_RegisterTrTypeName( wordset, 0, PMSDAT_GetWordNumber( &cuw->MyPmsData, 0 ) );
		WORDSET_RegisterPMSWord( wordset, 0, pmsword );
	}
	
	// ���j�I����b�ԍ��ɑΉ��������b�Z�[�WNO��Ԃ�
	return InfomationTalkTable[ pmsid ];
}


//------------------------------------------------------------------
/**
 * $brief   �e�@�̎��̎��胁���o�[��\���r�[�R�������N���A����
 *
 * @param   beacon		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionBeaconClear( UNION_BEACON_STATE *beacon )
{
	int i;
	beacon->mode = 0;
	for(i=0;i<4;i++){
		beacon->c_id[i]     = 0;
		beacon->c_face[i]   = 0;
		beacon->c_rom[i]    = 0;
		beacon->c_region[i] = 0;
	}
}

//==============================================================================
/**
 * $brief   ���j�I�����[���ŃX�^�[�g���j���[����`���b�g���ǉ����ꂽ���̏���
 *
 * @param   cuw		
 * @param   pms		�u�`���b�g�v���j���[�ō쐬�����ȈՉ�b
 *
 * @retval  none
 */
//==============================================================================
void Union_SetMyPmsData( COMM_UNIONROOM_WORK *cuw, PMS_DATA *pms )
{
	PMSDAT_Copy( &cuw->MyPmsData, pms  );
	cuw->MyPmsPutFlag = 1;
}

//==============================================================================
/**
 * $brief   �����ō쐬�����ȈՉ�b������ʂ���Q�Ƃ����悤�ɂ���
 *
 * @param   cuw			
 *
 * @retval  PMS_DATA *	�����ō쐬�����ȈՉ�b��
 */
//==============================================================================
PMS_DATA * Union_GetMyPmsData( COMM_UNIONROOM_WORK *cuw )
{
	if(cuw->MyPmsPutFlag==0){
		return NULL;
	}
	cuw->MyPmsPutFlag = 0;
	return &cuw->MyPmsData;
}


//==============================================================================
/**
 * $brief   ���j�I�����[�����Ŏg�p�����b�p�Ƀg���[�i�[�����Z�b�g����
 *          �����̖��O���Z�b�g����
 *
 * @param   wordset		WORDSET�ւ̃|�C���^
 * @param   type		UNION_TRAINER_REGIST_CHILD:�u�b�������p�v	1:�u�b���������p�v
 * @param   no			�u�b�������p�v�̎��Ɏw�肵�Ă���OBJ�����炤���߂ɕK�v
 *
 * @retval  none		
 */
//==============================================================================
void Union_TrainerNameRegist( WORDSET *wordset, int type, int no, MYSTATUS *mystatus, PMSW_SAVEDATA *pmssave )
{
	MYSTATUS *status;
	STRBUF   *greeting;
	MSGDATA_MANAGER*  msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_union_dat, HEAPID_FIELD );
	int      region,msgno;

	OS_Printf("NameRegist type=%d objid=%d\n",type, no);
	no--;		// �X�N���v�g�́{�P�ł���̂łP����
	
	// �b�������̓r�[�R������MYSTATUS���擾
	if(type==UNION_TALK_CHILD){
		status      = CommMPGetBconMyStatus( no );
	}else{
	// �b���������͐ڑ��ς݂Ȃ̂�ConnectID^1����MYSTATUS���擾
		status = CommInfoGetMyStatus(CommGetCurrentID()^1);

	}

//	OS_Printf("���O�o�^�@%d\n", type);
//	GF_ASSERT(status!=NULL && "�擾����MYSTATUS��NULL");

	if(status==NULL){
		return;
	}

	// �g���[�i�[����o�^
	WORDSET_RegisterPlayerName( wordset, 0, status );		// ����̖��O��o�^
	WORDSET_RegisterPlayerName( wordset, 1, mystatus );		// �����̖��O���o�^����

	// ���R�[�h�擾
	region   = MyStatus_GetRegionCode( status );

	OS_Printf("���ԍ� %d \n", region);

	// �e����J�[�g���b�W�ɂ��킹�ĊȈՉ�b�t���O��ǉ�����
	if(region>=LANG_JAPAN && region <=LANG_SPAIN){
		static const int AisatsuFlagTable[] = {
			PMSW_AISATSU_JP,	// ���{��
			PMSW_AISATSU_EN,	// �p��
			PMSW_AISATSU_FR,	// �t�����X��
			PMSW_AISATSU_IT,	// �C�^���A��
			PMSW_AISATSU_GE,	// �h�C�c��
			-1,					// ��������i���o�[
			PMSW_AISATSU_SP,	// �X�y�C����
		};

		u16 lang = region - LANG_JAPAN;
		if( (lang < NELEMS(AisatsuFlagTable)) && (AisatsuFlagTable[lang] >= 0) )
		{
			PMSW_SetAisatsuFlag( pmssave,  AisatsuFlagTable[lang] );
			OS_Printf("�ȈՉ�b�� %d�@��ǉ�\n", PMSW_AISATSU_JP+( region - LANG_JAPAN ) );
		}
	}

	OS_Printf("�N���A�t���O = %d, �S���}�Ӄt���O = %d\n", MyStatus_GetDpClearFlag(status),MyStatus_GetDpZenkokuFlag(status));

	// ����̌���ɂ���Ĉ��A���ς��
	switch(region){
	case LANG_JAPAN: 	msgno = msg_union_greeting_01;	break;
	case LANG_ENGLISH: 	msgno = msg_union_greeting_02;	break;
	case LANG_FRANCE: 	msgno = msg_union_greeting_03;	break;
	case LANG_ITALY	: 	msgno = msg_union_greeting_04;	break;
	case LANG_GERMANY: 	msgno = msg_union_greeting_05;	break;
	case LANG_SPAIN	: 	msgno = msg_union_greeting_06;	break;
	default:
		msgno = msg_union_greeting_07;
	}
	greeting = MSGMAN_AllocString( msgman, msgno );

	// �e���́u����ɂ��́v���i�[����
	WORDSET_RegisterWord( wordset, 2, greeting, 0, 1, region );

	sys_FreeMemoryEz(greeting);
	MSGMAN_Delete( msgman );
}

//==============================================================================
/**
 * $brief   ���j�I�����[���ŊȈՉ�b������������i�b������OK�����Ȃ��Ǝv���̂łP���Łj
 *
 * @param   pms		
 *
 * @retval  none		
 */
//==============================================================================
void Union_PMSReWrite( PMS_DATA *pms )
{
	UNION_BEACON_STATE state;

	UnionBeaconClear( &state );
	state.mode = UNION_PARENT_MODE_FREE;
	

	CommMPSetMyPMS( pms );
	CommMPSetMyRegulation(&state);	// �r�[�R����������
	CommMPFlashMyBss();
	
}

//==============================================================================
/**
 * $brief   ��������E�������񂩂�߂��Ă������p�Ƀ��[�N�����������Ă���
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//==============================================================================
void Union_CommWorkClear( COMM_UNIONROOM_WORK *cuw)
{
	cuw->CommChildSelectEvent = 0;
	cuw->UnionEventWork       = 0;
	cuw->UnionEndConnectFlag  = 0;
}
//------------------------------------------------------------------
/**
 * $brief   ���j�I�����[���ʐM�J�n�p�̃��[�N�N���A
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CommUnion_EventFlagClear( COMM_UNIONROOM_WORK *cuw)
{
	cuw->CommConnectStartFlag = 0;
	cuw->CommConnectStartWait = 0;
	cuw->CommNextProcOn       = 0;
	cuw->CommChildSelectEvent = 0;
	cuw->UnionEventWork       = 0;
	cuw->busyflag			  = 0;
	cuw->MyPmsPutFlag         = 0;
	cuw->UnionEndConnectFlag  = 0;
}

//==============================================================================
/**
 * $brief   �g���[�i�[�J�[�h�̈��alloc����
 *
 * @param   cuw		
 *
 * @retval  void *		
 *
 *  �g���[�i�[�J�[�h���m�ۂ���̈悪HEAPID_UNIONROOM������Ȃ������̂ŁA
 *  BASE_SYSTEM�����鎖�ɂ����B
 *  �ʃA�v���ւ̉e�����|���̂ŁA�g���[�i�[�J�[�h�����钼�O�Ɋm�ۂ���
 *  �J�[�h�{������ɉ������
 */
//==============================================================================
void *Union_TrainerCardWorkInit( COMM_UNIONROOM_WORK *cuw )
{
	cuw->my_trcard      = TRCSET_AllocTrainerCardData( HEAPID_BASE_SYSTEM );
	cuw->recv_trcard[0] = TRCSET_AllocTrainerCardData( HEAPID_BASE_SYSTEM );
	cuw->recv_trcard[1] = TRCSET_AllocTrainerCardData( HEAPID_BASE_SYSTEM );

	TRCSET_MakeTrainerInfo( 0, 0, 0,
							UnionView_GetTrainerInfo( MyStatus_GetMySex(cuw->mystatus),
												MyStatus_GetTrainerView(cuw->mystatus), UNIONVIEW_ICONINDEX ),
							cuw->fsys, cuw->my_trcard );

	OS_Printf("my_trcard = %08x\n",cuw->my_trcard);
	OS_Printf("trcard[0] = %08x\n",cuw->recv_trcard[0]);
	OS_Printf("trcard[1] = %08x\n",cuw->recv_trcard[1]);

	//�����̂h�c�ƈႤ�o�b�t�@��Ԃ��i����̃g���[�i�[�J�[�h�������Ď��ł���悤�Ɂj
	return (void*)cuw->recv_trcard[CommGetCurrentID()^1];
}


//==============================================================================
/**
 * $brief   �g���[�i�[�J�[�h�̂��߂Ɋm�ۂ����̈���������
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//==============================================================================
void Union_trainerCardWorkFree( COMM_UNIONROOM_WORK *cuw )
{
    sys_FreeMemoryEz(cuw->recv_trcard[0]);
    sys_FreeMemoryEz(cuw->recv_trcard[1]);
    sys_FreeMemoryEz(cuw->my_trcard);

}


//==============================================================================
/**
 * $brief   �g���[�i�[�J�[�h�f�[�^�𑗐M����
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//==============================================================================
void Union_SendTrainerCardData( COMM_UNIONROOM_WORK *cuw )
{

	// �e�������M����
//	if(CommGetCurrentID()==0){
		CommSendHugeData( CU_TRAINER_CARD, cuw->my_trcard, sizeof(TR_CARD_DATA) );

		OS_Printf("send size = %d   xor = %d\n",sizeof(TR_CARD_DATA), cuw->my_trcard->_xor);
//	}

}


