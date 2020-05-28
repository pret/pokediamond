//=============================================================================
/**
 * @file	main.c
 * @brief	�|�P�����c�o���C��
 * @author	GAME FREAK Inc.
 */
//=============================================================================

#include "common.h"
#include "snd_system.h"
#include "communication/communication.h"
#include "communication/comm_state.h"

#include "system/main.h"

#include "gflib\apptimer.h"
#include "system\fontproc.h"
#include "system/brightness.h"
#include "system/pm_rtc.h"
#include "gflib/gf_gx.h"

#include "system/savedata.h"
#include "system/pm_overlay.h"

#include "demo/title.h"

#include "system/wipe.h"
#include "wifi/dwc_rap.h"
#include "system/playtime_ctrl.h"

#include "system/debug_flag.h"
#include "system/pm_debug_wifi.h"

#include "application/backup.h"
#include "system/gamestart.h"

#include "savedata/config.h"

static void Main_CallProc(void);
static void ResetUpdateVBlank(void);
static void ResetLoop(int resetNo);
static void ResetFunc(int resetNo);
static void ResetErrorFunc(int resetNo, int messageType);
static void ErrorCheckComm(void);
void sleepFunc(void);

//=============================================================================
//=============================================================================
//#define TEST_60_FRAME

//--- �f�o�b�O�p  �`��x���𔭐�������


// -------------------------------------------------------------------------
#ifdef	PM_DEBUG



#ifdef DEBUG_ONLY_FOR_ohno

#define _DELAY_DEBUG
static void delayDebug(void);

#endif // DEBUG_ONLY_FOR_ohno



// WIFI�@�ΐ�AUTOӰ�ރf�o�b�N
#ifdef _WIFI_DEBUG_TUUSHIN
static void wifiDebug(void);
WIFI_DEBUG_BATTLE_WK WIFI_DEBUG_BATTLE_Work;
#endif	// _WIFI_DEBUG_TUUSHIN


// A�{�^����0.6�b�ɂP�񉟂�
//#define PAD_DEBUG
#ifdef PAD_DEBUG
static void DebugPad();

#endif // PAD_DEBUG

#endif // PM_DEBUG


// -------------------------------------------------------------------------

//---------------------------------------------------------------------------
/**
 * @brief	���C������p���[�N
 */
//---------------------------------------------------------------------------
typedef struct {
	FSOverlayID ov_id;				///<���݂̃��C���v���Z�X�̃I�[�o�[���CID
	PROC * proc;					///<���݂̃��C���v���Z�X�̃|�C���^
	FSOverlayID next_ov_id;			///<���̃��C���v���Z�X�̃I�[�o�[���CID
	const PROC_DATA * next_data;	///<���̃��C���v���Z�X�f�[�^�ւ̃|�C���^
	MAINWORK work;					///<���C���v���Z�X�p���[�N�imain.h�Œ�`�j
}SYSWORK;

static SYSWORK main;

#ifdef	PM_DEBUG
DEBUG_FLAG_DATA	DebugFlagData;		///<�f�o�b�O�f�[�^
#endif


//=============================================================================
//
//				���C��
//
//=============================================================================
extern const PROC_DATA TitleProcData;
extern const PROC_DATA OpDemoProcData;
FS_EXTERN_OVERLAY( title );

//---------------------------------------------------------------------------
/**
 * @brief	���C���֐�
 */
//---------------------------------------------------------------------------
void NitroMain(void)
{
	//===========================
	//		������
	//===========================
	GF_AssertInit();

    sys_InitSystem();
    sys_InitVRAM();
    sys_InitKeyRead();
	sys_InitAgbCasetteVer(0);
	
	GF_GX_Init();
	GF_RTC_Init();

	Main_Init();

	// �t�H���g�f�[�^�̃��[�h
	FontProcInit();
	FontProc_LoadFont( FONT_SYSTEM, HEAPID_BASE_APP );
	FontProc_LoadFont( FONT_TALK, HEAPID_BASE_APP );
	FontProc_LoadFont( FONT_UNKNOWN, HEAPID_BASE_APP );

	main.work.select_id = -1;
	main.work.savedata = SaveData_System_Init();

	Snd_AllInit(SaveData_GetPerapVoice(main.work.savedata),SaveData_GetConfig(main.work.savedata) );

	APTM_Init();

    if( DWC_INIT_RESULT_DESTROY_OTHER_SETTING == mydwc_init(HEAPID_BASE_APP) ){ //dwc������
        DWClibWarningCall(HEAPID_BASE_APP,0); //dwc�������̃G���[�\��
    }

//�o�b�N�A�b�v�t���b�V�����Ȃ��Ƃ��̏����͐��i�łł̂ݗL���ɂ���
#ifndef	PM_DEBUG
	if (SaveData_GetFlashExistsFlag(main.work.savedata) == FALSE) {
		//�o�b�N�A�b�v�t���b�V���̑��݂��F�߂��Ȃ��Ƃ���
		//�G���[��ʂɑJ�ڂ���
		//Main_SetNextProc(NO_OVERLAY_ID, &BackupErrorProcData);
		BackupErrorWarningCall( 0 );
	} else
#endif
	{
		switch (OS_GetResetParameter()) {
		case _SOFT_RESET_NORMAL:
			main.work.comm_error_flag = FALSE;
			Main_SetNextProc( FS_OVERLAY_ID(title), &OpDemoProcData);
			break;
		case _SOFT_RESET_NETERROR:
			main.work.comm_error_flag = TRUE;
			Main_SetNextProc( OVERLAY_ID_GAMESTART, &ContinueGameStartProcData);
			break;
		default:
			GF_ASSERT_MSG(0, "����`�ȃ��Z�b�g��`���Ԃ�܂����I\n");
		};
	}

	sys.DS_Boot_Flag = TRUE;		//�u�[�g�t���O

	sys.vsync_flame_counter = 0;
	Main_InitRandom();

	//�P�x�ύX�\���̏�����
	BrightnessChgInit();

	// �v���C���ԃJ�E���g������
	PlayTimeCtrl_Init();

	//===========================
	//	���C�����[�v
	//===========================
	while (1) {
        ErrorCheckComm(); // �ʐM�G���[����

        sleepFunc();   // �X���[�v�@�\����

		sys_MainKeyRead();	//�L�[���ǂݎ��

		GF_AssertMain();

// WIFI�@�ΐ�AUTOӰ�ރf�o�b�N
#ifdef _WIFI_DEBUG_TUUSHIN
		wifiDebug();
#endif	// _WIFI_DEBUG_TUUSHIN

#ifdef PAD_DEBUG
		DebugPad();
#endif

        
		if ((sys.cont_org & (PAD_BUTTON_START|PAD_BUTTON_SELECT|PAD_BUTTON_L|PAD_BUTTON_R))
			==(PAD_BUTTON_START|PAD_BUTTON_SELECT|PAD_BUTTON_L|PAD_BUTTON_R)) {
            if(sys.DontSoftReset == 0){  // �}������BIT�������������OK
                ResetFunc(_SOFT_RESET_NORMAL);
            }
		}
        
        if(CommUpdateData()){  // �f�[�^���L�ʐM�̒ʐM����

			Main_CallProc();	//���C���v���Z�X�Ăяo��

			TCBSYS_Main( sys.mainTCBSys );
			TCBSYS_Main( sys.printTCBSys );
#ifndef TEST_60_FRAME
			if(!sys.vsync_flame_counter){
                OS_WaitIrq(TRUE, OS_IE_V_BLANK);	// �u�u�����N�҂�
                sys.vsync_counter++;	// �u�u�����N�p�J�E���^
            }
#endif
        }
		GF_RTC_Main();
		PlayTimeCtrl_Countup();

#ifdef _DELAY_DEBUG
        delayDebug();
#endif// _DELAY_DEBUG

		GF_G3_SwapBuffers();	// G3_SwapBuffers�Ăяo��
#ifndef TEST_60_FRAME
		TCBSYS_Main( sys.printTCBSys );
#endif
        OS_WaitIrq(TRUE, OS_IE_V_BLANK); 	// �u�u�����N�҂�
		sys.vsync_counter++;	// �u�u�����N�p�J�E���^
		sys.vsync_flame_counter = 0;


		//===========================
		BrightnessChgMain();	//�P�x�ύX���C��
		WIPE_SYS_Main();		///<���C�v�������C��
		if (sys.pVBlank != NULL) {
			sys.pVBlank(sys.pVBlankWork);
		}
		Snd_Main();

		TCBSYS_Main( sys.vwaitTCBSys );
    }
}


//=============================================================================
//
//
//		���C���v���Z�X����
//
//
//=============================================================================

//---------------------------------------------------------------------------
/**
 * @brief	���C���v���Z�X������
 */
//---------------------------------------------------------------------------
void Main_Init(void)
{
	main.ov_id = NO_OVERLAY_ID;
	main.proc = NULL;
	main.next_ov_id = NO_OVERLAY_ID;
	main.next_data = NULL;
}

//---------------------------------------------------------------------------
/**
 * @brief	���C���v���Z�X���s
 */
//---------------------------------------------------------------------------
static void Main_CallProc(void)
{
	BOOL result;

	if (main.proc == NULL) {
		if (main.next_data == NULL) {
			return;
		}
		if (main.next_ov_id != NO_OVERLAY_ID) {
			//�K�v�ł���΃I�[�o�[���C�̃��[�h���s��
			Overlay_Load(main.next_ov_id, OVERLAY_LOAD_SYNCHRONIZE);
		}
		main.ov_id = main.next_ov_id;
		main.proc = PROC_Create(main.next_data, &main.work, HEAPID_BASE_SYSTEM);
		main.next_ov_id = NO_OVERLAY_ID;
		main.next_data = NULL;
	}

	result = ProcMain(main.proc);
	if (result) {
		PROC_Delete(main.proc);
		main.proc = NULL;
		if (main.ov_id != NO_OVERLAY_ID) {
			//�K�v�ł���΃I�[�o�[���C�̃A�����[�h���s��
			Overlay_UnloadID(main.ov_id);
		}
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	���̃v���Z�X�̓o�^
 * @param	ov_id		�I�[�o�[���CID
 * @param	proc_data	PROC_DATA�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
void Main_SetNextProc(FSOverlayID ov_id, const PROC_DATA * proc_data)
{
	GF_ASSERT(main.next_data == NULL);
	main.next_ov_id = ov_id;
	main.next_data = proc_data;
}

//---------------------------------------------------------------------------
/**
 * @brief	���Z�b�g�̑ҋ@��Ԃ̎��ɍŒ���K�v�ȃ��[�v����
 * @param	none
 */
//---------------------------------------------------------------------------

static void ResetUpdateVBlank(void)
{
    if(CommUpdateData()){  // �f�[�^���L�ʐM�̒ʐM����
    }
    OS_WaitIrq(TRUE, OS_IE_V_BLANK);
    sys.vsync_counter++;	// �u�u�����N�p�J�E���^
    sys.vsync_flame_counter = 0;
    if (sys.pVBlank != NULL) {
        sys.pVBlank(sys.pVBlankWork);
    }
}

//---------------------------------------------------------------------------
/**
 * @brief	���Z�b�g�̑ҋ@��Ԃ̎��ɍŒ���K�v�ȃ��[�v���� ���Z�b�g�����ۂɂ�����
 * @param	resetNo   OS_ResetSystem�ɓn�����Z�b�g���
 */
//---------------------------------------------------------------------------

static void ResetLoop(int resetNo)
{
    if(CommStateIsResetEnd()){ // �ʐM�I��
        if(CARD_TryWaitBackupAsync()==TRUE){  //�������[�J�[�h�I��
            OS_ResetSystem(resetNo);  // �ؒf�m�F��I��
        }
    }
    ResetUpdateVBlank();
}

//---------------------------------------------------------------------------
/**
 * @brief	�ʐM�G���[����
 * @param	resetNo   OS_ResetSystem�ɓn�����Z�b�g���
 */
//---------------------------------------------------------------------------

static void ErrorCheckComm(void)
{
    int type = CommIsResetError();
    switch(type){
      case COMM_ERROR_RESET_SAVEPOINT:  // ���Z�b�g�𔺂��ʐM�G���[����
        ResetErrorFunc(_SOFT_RESET_NETERROR,type);
        break;
      case COMM_ERROR_RESET_TITLE:  // �^�C�g���߂�G���[
        ResetErrorFunc(_SOFT_RESET_NORMAL,type);
        break;
      case COMM_ERROR_RESET_GTS:  // GTS���L�̃G���[
        ResetErrorFunc(_SOFT_RESET_NETERROR,type);
        break;
    }
}

//---------------------------------------------------------------------------
/**
 * @brief	�\�t�g�E�G�A���Z�b�g���N�����ꍇ�̏���
 * @param	resetNo   OS_ResetSystem�ɓn�����Z�b�g���
 */
//---------------------------------------------------------------------------
static void ResetFunc(int resetNo)
{
	WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_WHITE );
	WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_WHITE );
    if(CommStateExitReset()){  // �ʐM���Z�b�g�ֈڍs
        SaveData_DivSave_Cancel(SaveData_GetPointer()); //�����Z�[�u���Ă���L�����Z�����Ă����Ȃ��ƃ��Z�b�g�ł��Ȃ�
    }
	while (1) {
        sleepFunc();   // �X���[�v�@�\����
        ResetLoop(resetNo);
    }
}

//---------------------------------------------------------------------------
/**
 * @brief	�ʐM�G���[�ɂ��\�t�g�E�G�A���Z�b�g���N�����ꍇ�̏���
 * @param	resetNo   OS_ResetSystem�ɓn�����Z�b�g���
 */
//---------------------------------------------------------------------------

static void ResetErrorFunc(int resetNo, int messageType)
{
    if(messageType==COMM_ERROR_RESET_GTS){
        ComErrorWarningResetCall(HEAPID_BASE_SYSTEM,COMM_ERRORTYPE_GTS,0);
    }
    else if(_SOFT_RESET_NORMAL == resetNo){
        ComErrorWarningResetCall(HEAPID_BASE_SYSTEM,COMM_ERRORTYPE_TITLE,0);
    }
    else{
        ComErrorWarningResetCall(HEAPID_BASE_SYSTEM,COMM_ERRORTYPE_ARESET,0);
    }
    CommStateExitReset();  // �ʐM���Z�b�g�ֈڍs
    while(1){
        sleepFunc();   // �X���[�v�@�\����
		sys_MainKeyRead();	//�L�[���ǂݎ��
        if(sys.trg & PAD_BUTTON_DECIDE){
            break;
        }
        ResetUpdateVBlank();
    }
    ResetFunc(resetNo);  // ���Z�b�g������
}

//=============================================================================
//=============================================================================
//---------------------------------------------------------------------------
/**
 * @brief	��������������
 *
 * RTC�̎��ԂƃQ�[���J�n�����Vsync�J�E���^�̒l�ŏ��������s���Ă���B
 * ���ꂼ�ꂪ�g����R���e�L�X�g���ƂɃV�[�h�⃏�[�N��ێ����Ă���ꍇ�́A
 * ���ꂼ��ŏ�����������ʓr�s��
 */
//---------------------------------------------------------------------------
void Main_InitRandom(void)
{
	RTCDate date;
	RTCTime time;
	u32 seed;
	GF_RTC_GetDateTime(&date, &time);
	seed = date.year + date.month * 0x100 * date.day * 0x10000
		+ time.hour * 0x10000 + (time.minute + time.second) * 0x1000000
		+ sys.vsync_counter;
	gf_mtSrand(seed);
	gf_srand(seed);
}



//---------------------------------------------------------------------------
/**
 * @brief	�X���[�v��Ԃ̊Ǘ�
 * @param	none
 */
//---------------------------------------------------------------------------
void sleepFunc(void)
{
  PMBackLightSwitch up,down;
  PMWakeUpTrigger trigger;
    
  if(PAD_DetectFold()){ // �ӂ����܂��Ă���
    if(sys.DontSleep == 0){
      StopTP_Sleep();
      trigger = PM_TRIGGER_COVER_OPEN|PM_TRIGGER_CARD;
      // �����AGB�J�[�g���b�W���h�����Ă���ꍇ�̂ݕ��A�����ɃJ�[�g���b�W�ݒ�
      if(sys.AgbCasetteVersion)
	trigger |= PM_TRIGGER_CARTRIDGE;
      //SLEEP
      PM_GoSleepMode( trigger, 0, 0 );
      // ���A��A�J�[�h��������Ă�����d��OFF
      if(CARD_IsPulledOut()){
	PM_ForceToPowerOff();
      } else if((OS_GetIrqMask() & OS_IE_CARTRIDGE) && CTRDG_IsPulledOut()){
	// ���A��A�J�[�g���b�W��������Ă�����c
	if(PAD_DetectFold()){
	  // �܂��ӂ����܂��Ă����ԂȂ�΍ēx�X���[�v�ɓ�������ɓd��OFF
	  PM_GoSleepMode( PM_TRIGGER_COVER_OPEN|PM_TRIGGER_CARD, 0, 0 );
	  PM_ForceToPowerOff();
	} else {
	  // �ӂ����J���Ă�����d��OFF
	  PM_ForceToPowerOff();
	}
      }
      ReStartTP_Sleep();
    } else{
      // �������J�[�g���b�W�������ꂽ��SLEEP���d��OFF
      if((OS_GetIrqMask() & OS_IE_CARTRIDGE) && CTRDG_IsPulledOut()){
	PM_GoSleepMode( PM_TRIGGER_COVER_OPEN|PM_TRIGGER_CARD, 0, 0 );
	PM_ForceToPowerOff();
      }
      //BK OFF
      PM_GetBackLight(&up,&down);
      if(PM_BACKLIGHT_ON == up){
	PM_SetBackLight(PM_LCD_ALL,PM_BACKLIGHT_OFF);
      }
    }
  } else{  // �J���Ă���
    PM_GetBackLight(&up,&down);
    if(PM_BACKLIGHT_OFF == up){
      PM_SetBackLight(PM_LCD_ALL,PM_BACKLIGHT_ON);
    }
  }
}


//---------------------------------------------------------------------------
/**
 * @brief	�`��x���@�f�o�b�O�֐� 
 *  ���̊֐����g���� �X���[���[�V�����ōĐ��\�Ȃ̂�
 *  �ǂ�ȃt���[���œ����Ă��邩�킩��܂�
 */
//---------------------------------------------------------------------------
#ifdef	PM_DEBUG
static void delayDebug(void)
{
    static u8 trg = 0;
    static u8 speed = 5;
    int i;

    if(sys.cont & PAD_BUTTON_SELECT){
        if(sys.trg & PAD_BUTTON_Y){
            trg = 1 - trg;
            OS_TPrintf("DEBUG:�`��x�� %d\n", trg);
        }
    }
    if(trg){
        if(sys.trg & PAD_BUTTON_X){
            speed++;
            OS_TPrintf("speed %d\n",speed);
        }
        if(sys.trg & PAD_BUTTON_Y){
            speed--;
            OS_TPrintf("speed %d\n",speed);
        }
        for(i = 0; i < speed; i++){
            OS_WaitIrq(TRUE, OS_IE_V_BLANK);
        }
    }
}


// WIFI�@�ΐ�AUTOӰ�ރf�o�b�N
#ifdef _WIFI_DEBUG_TUUSHIN
static void wifiDebug(void)
{
	if( sys.cont & PAD_BUTTON_L ){
		if( sys.trg & PAD_BUTTON_X ){
			sys.trg ^= PAD_BUTTON_X;
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MODE = _WIFI_DEBUG_MODE_X;
			OS_TPrintf( "�f�o�b�OWIFIӰ�ށ@X\n" );
		}else if( sys.trg & PAD_BUTTON_Y ){

			sys.trg ^= PAD_BUTTON_Y;
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MODE = _WIFI_DEBUG_MODE_Y;
			OS_TPrintf( "�f�o�b�OWIFIӰ�ށ@Y\n" );
		}
	}
	if( sys.trg & PAD_BUTTON_R ){
		OS_TPrintf( "�f�o�b�OWIFIӰ�ށ@OFF\n" );
		memset( &WIFI_DEBUG_BATTLE_Work, 0, sizeof(WIFI_DEBUG_BATTLE_WK) );
		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MODE = _WIFI_DEBUG_NONE;
	}

	if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MODE == _WIFI_DEBUG_NONE ){
		return ;
	}

	/* wifi���X�g��ʗp */
	if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_A_REQ == TRUE ){
		sys.trg |= PAD_BUTTON_A;
		sys.cont |= PAD_BUTTON_A;
	}
	if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_B_REQ == TRUE ){
		sys.trg |= PAD_BUTTON_B;
		sys.cont |= PAD_BUTTON_B;
	}
	if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_TOUCH_REQ == TRUE ){
		sys.tp_trg |= PAD_BUTTON_B;
		sys.tp_cont |= PAD_BUTTON_B;
		sys.tp_x	= 128;
		sys.tp_y	= 180;
	}

	/* �t�B�[���h�p���� */
	switch( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_SEQ ){
	case 0:	// �ҋ@
		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT = 0;
		break;

	case 1:
		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT ++;
		if( (WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT > 300) || (WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MODE == _WIFI_DEBUG_MODE_X) ){
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_SEQ ++;
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT = 0;
		}
		break;

	case 2:	// �E��
		sys.trg |= PAD_KEY_RIGHT;
		sys.cont |= PAD_KEY_RIGHT;

		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT ++;
		if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT > 8 ){
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_SEQ ++;
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT = 0;
		}
		break;

	case 3:
		sys.trg |= PAD_KEY_UP;
		sys.cont |= PAD_KEY_UP;

		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT ++;
		if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT > 16 ){
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_SEQ ++;
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT = 0;
		}
		break;

	case 4:	// ����
		sys.trg |= PAD_KEY_LEFT;
		sys.cont |= PAD_KEY_LEFT;

		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT ++;
		if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT > 16 ){
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_SEQ ++;
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT = 0;
		}
		break;

	case 5:
		sys.trg |= PAD_KEY_UP;
		sys.cont |= PAD_KEY_UP;

		WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT ++;
		if( WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT > 16 ){
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_SEQ = 1;
			WIFI_DEBUG_BATTLE_Work.DEBUG_WIFI_MOVE_WAIT = 0;
		}
		break;
	}
}
#endif	// _WIFI_DEBUG_TUUSHIN

#endif // PM_DEBUG


#ifdef PAD_DEBUG

#include "../field/d_taya.h"

static int pad_wait=5;
static int pad_on=0;

static void DebugPad()
{
	if(pad_on){
		pad_wait--;
		if(pad_wait == 0){
			sys.trg |= PAD_BUTTON_X;
//			sys.trg |= PAD_BUTTON_A;
			pad_wait = gf_rand()%4+1;
		}
	}
	if((sys.cont & PAD_BUTTON_L) && (sys.trg & PAD_BUTTON_DEBUG)){
			pad_on^=1;
	}
}

#endif
