//============================================================================================
/**
 * @file	tr_card_setup.c
 * @bfief	�g���[�i�[�J�[�h���Z�b�g�A�b�v
 * @author	Nozomu Saito
 */
//============================================================================================
#include "common.h"
#include "fieldsys.h"
#include "field/field.h"
#include "system/mystatus.h"
#include "system/zukanwork.h"
#include "application/trainer_card.h"
#include "savedata/trainercard_data.h"
#include "savedata/record.h"
#include "savedata/playtime.h"
#include "ev_time.h"
#include "comm_union.h"
#include "field/eventflag.h"
#include "contest/contest_def.h"
#include "sysflag.h"
#include "savedata/undergrounddata.h"

#include "tr_card_setup.h"

#define COMM_NUM_MAX	(999999)
#define BATTLE_WIN_MAX	(9999)
#define BATTLE_LOSE_MAX	(9999)
#define TRADE_MAX		(99999)

static void TRCSET_SetTrCardDataCommon(	const u8 inBadgeBrushFlg,
										const u8 inVersion,
										const u8 inCardRank,
										const u8 inGymReaderMask,
										const u8 inCountryCode,
										TR_CARD_DATA *outTrCardData);

static void TRCSET_SetTrCardDataFace(	const u16 inID,
										const u8  inSex,
										const STRCODE *inName,
										const u32 inMoney,
										const u32 inPokeBook,
										const BOOL inPokeBookFlg,
										const u32 inScore,
										TR_CARD_DATA *outTrCardData);

static void TRCSET_SetTrCardDataTime(	const u8 inClearFlg,
										const PLAYTIME *inPlayTime,
										const RTCDate *inStartDate,
										const RTCDate *inClearDate,
										const RTCTime *inClearTime,
										const u8 TimeUpdate,
										TR_CARD_DATA *outTrCardData);

static void TRCSET_SetTrCardDataBack(	const u32 inCommNum,
										const u32 inCommBattleWin,
										const u32 inCommBattleLose,
										const u32 inCommTrade,
										const u8 *inSignData,
										TR_CARD_DATA *outTrCardData);
static void TRCSET_SetTrCardDataBadge(	MYSTATUS *inMySt, FIELDSYS_WORK *fsys, TR_CARD_DATA *outTrCardData );

static BOOL SetupTrCardEvent(GMEVENT_CONTROL * event);

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�J�[�h�������W���āA�f�[�^���쐬
 *
 * @param	inBadgeBrushFlg		�o�b�W�����L���L��
 * @param	inTimeUpdate		���ԍX�V�t���O
 * @;aram	inGymRaederMask		�W�����[�_�[�}�X�N
 * @param	inUnionTrNo			���j�I���g���[�i�[�i���o�[�i0�`15�j�@�w�肵�Ȃ��Ƃ���,UNION_TR_NONE
 * @param	fsys				�t�B�[���h�V�X�e���|�C���^
 * @param	outTrCardData		�g���[�i�[�J�[�h�f�[�^�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TRCSET_MakeTrainerInfo(const u8 inBadgeBrushFlg,
							const u8 inTimeUpdate,
							const u8 inGymReaderMask,
							const u8 inUnionTrNo,
							FIELDSYS_WORK *fsys, 
							TR_CARD_DATA *outTrCardData)
{
	MYSTATUS *my_st;
	RECORD *rec;
	SAVEDATA * sv;
	sv = GameSystem_GetSaveData(fsys);
	my_st = SaveData_GetMyStatus(sv);
	rec = SaveData_GetRecord(sv);

	outTrCardData->UnionTrNo = inUnionTrNo;

	{
		u8 rank;
		//�����N�Z�o
		rank = TRCSET_GetCardRank(fsys);
	
		TRCSET_SetTrCardDataCommon( inBadgeBrushFlg, PM_VERSION, rank,
									inGymReaderMask, MyStatus_GetRegionCode(my_st), outTrCardData);
	}
	
	TRCSET_SetTrCardDataFace(	MyStatus_GetID_Low(my_st),
								MyStatus_GetMySex(my_st),
								MyStatus_GetMyName(my_st),
								MyStatus_GetGold(my_st),
								ZukanWork_GetZukanPokeSeeCount( SaveData_GetZukanWork(fsys->savedata) ),
								ZukanWork_GetZukanGetFlag(SaveData_GetZukanWork(fsys->savedata)),
								RECORD_Score_Get(rec),
								outTrCardData);

	{
		RTCDate start_date;	//�J�n�N����
		RTCDate clear_date;	//�N���A�N����
		RTCTime time;		//�N���A����

		PLAYTIME *play_time;

		play_time = SaveData_GetPlayTime(sv);
		
		EVTIME_GetGameStartDateTime(fsys, &start_date, &time);
		EVTIME_GetGameClearDateTime(fsys, &clear_date, &time);

		TRCSET_SetTrCardDataTime(	SysFlag_GameClearCheck( SaveData_GetEventWork( fsys->savedata ) ),
									play_time,
									&start_date,
									&clear_date,
									&time,
									inTimeUpdate,
									outTrCardData);
	}

	{
		u32 count,win,lose,trade;
		TR_CARD_SV_PTR trc_ptr;
		trc_ptr = TRCSave_GetSaveDataPtr(fsys->savedata);
		
		//�ʐM��	���C�����X�R���e�X�g+���C�����X����+WiFi����+���C�����X�ΐ�+WiFi�ΐ�+���C�����X�|���g
		count = RECORD_Get(rec, RECID_CONTEST_COMM_ENTRY)+
				RECORD_Get(rec, RECID_COMM_TRADE)+RECORD_Get(rec, RECID_WIFI_TRADE)+
				RECORD_Get(rec, RECID_COMM_BATTLE)+RECORD_Get(rec, RECID_WIFI_BATTLE)+
				RECORD_Get(rec, RECID_PORUTO_COMM);
		//������	���C�����X+WiFi
		win = RECORD_Get(rec, RECID_COMM_BTL_WIN)+RECORD_Get(rec, RECID_WIFI_BTL_WIN);
		//������	���C�����X+WiFi
		lose = RECORD_Get(rec, RECID_COMM_BTL_LOSE)+RECORD_Get(rec, RECID_WIFI_BTL_LOSE);
		//�ʐM����	���C�����X+WiFi
		trade = RECORD_Get(rec, RECID_COMM_TRADE)+RECORD_Get(rec, RECID_WIFI_TRADE);

		TRCSET_SetTrCardDataBack(	count,
									win,
									lose,
									trade,
									TRCSave_GetSighnDataPtr(trc_ptr),
									outTrCardData);
	}

	TRCSET_SetTrCardDataBadge( my_st, fsys, outTrCardData );

	{
		int i,tmp=0;
		u8 *p = (u8*)outTrCardData;
		for(i=0;i<sizeof(TR_CARD_DATA);i++){
			tmp ^= p[i];
		}
		outTrCardData->_xor = tmp;
	}

	
	
	outTrCardData->reached  = 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�J�[�h�������A���P�[�V����
 *
 * @param	inHeapID		�q�[�vID
 *
 * @return	TR_CARD_DATA*	�g���[�i�[�J�[�h�f�[�^�|�C���^
 */
//--------------------------------------------------------------------------------------------
TR_CARD_DATA *TRCSET_AllocTrainerCardData( const u16 inHeapID )
{
	TR_CARD_DATA * tcd = sys_AllocMemory( inHeapID, sizeof(TR_CARD_DATA) );
	memset( tcd, 0, sizeof(TR_CARD_DATA) );

	return tcd; 
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�J�[�h���������
 *
 * @param	*outData	������郁����
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TRCSET_FreeTrainerCardData( TR_CARD_DATA *outData )
{
	sys_FreeMemoryEz(outData);
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�J�[�h�����N�擾
 *
 * @param
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
u8 TRCSET_GetCardRank(FIELDSYS_WORK *fsys)
{
	u8 rank;
	SAVEDATA * sv;
	RECORD *rec;
	EVENTWORK *ev;
	SB_RECORD_DATA* sbd;
	
	sv = GameSystem_GetSaveData(fsys);
	rec = SaveData_GetRecord(sv);
	ev = SaveData_GetEventWork(sv);
	sbd = SaveData_GetSecretBaseRecord(sv);
	rank = TR_CARD_RANK_NORMAL;
	
	//�a������i�N���A�t���O�j
	if ( SysFlag_GameClearCheck( ev ) ){
		rank++;
	}
	//�S���}�ӊ����i�C�x���g�n�|�P�����������|�P�������Q�b�g���Ă��邩�j
	if ( ZukanWork_CheckZenkokuComp(SaveData_GetZukanWork(sv)) ){
		rank++;
	}
	//�o�g���^���[100�A���i�^�C�v�͂Ȃ�ł��j
	if ( (RECORD_Get(rec,RECID_RENSHOU_SINGLE )>=100)||
		 (RECORD_Get(rec,RECID_RENSHOU_DOUBLE )>=100)||
		 (RECORD_Get(rec,RECID_RENSHOU_MULTI )>=100)||
		 (RECORD_Get(rec,RECID_RENSHOU_COMM_MULTI )>=100)||
		 (RECORD_Get(rec,RECID_RENSHOU_WIFI )>=100) ){ 
		rank++;
	}
	//�R���e�X�g�}�X�^�[�D���i�^�C�v�͂Ȃ�ł��j
	if ( SysFlag_ConMasterCheck( ev, CONTYPE_STYLE )||
		 SysFlag_ConMasterCheck( ev, CONTYPE_BEAUTIFUL )||
		 SysFlag_ConMasterCheck( ev, CONTYPE_CLEVER )||
		 SysFlag_ConMasterCheck( ev, CONTYPE_STRONG )||
		 SysFlag_ConMasterCheck( ev, CONTYPE_CUTE ) ){
		rank++;
	}
	//�n���}�X�^�[
	
	if ( SecretBaseRecordGetUGRank(sbd) == UG_RANK_MASTER ){
		rank++;
	}
	return rank;
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�J�[�h���Z�b�g
 *
 * @param	inBadgeBrushFlg		�o�b�W�����L���L��
 * @param	inVersion			�o�[�W����
 * @param	inCardRank			�J�[�h�����N
 * @param	inGymReaderMask		�W�����[�_�[�}�X�N
 * @param	inCoutryCode		���R�[�h
 * @param	outTrCardData		�g���[�i�[�J�[�h�f�[�^�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TRCSET_SetTrCardDataCommon(	const u8 inBadgeBrushFlg,
										const u8 inVersion,
										const u8 inCardRank,
										const u8 inGymReaderMask,
										const u8 inCountryCode,
										TR_CARD_DATA *outTrCardData)
{
	//�o�b�W�����A�v���L���t���O
	outTrCardData->BrushValid = inBadgeBrushFlg;
	//�\�t�g�o�[�W����
	outTrCardData->Version = inVersion;
	//�J�[�h�����N;
	outTrCardData->CardRank = inCardRank;
	//���R�[�h
	outTrCardData->CountryCode = inCountryCode;
	//�W�����[�_�[�}�X�N
	outTrCardData->GymReaderMask = inGymReaderMask;

	//�[���ʃo�[�W��������
#ifdef PM_DEBUG
	if (sys.cont && PAD_BUTTON_L){
		outTrCardData->Version = VERSION_DP_NEXT;
		outTrCardData->GymReaderMask = 0x5a;
	}
#endif
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�J�[�h���Z�b�g(�\��)
 *
 * @param	inID			�g���[�i�[ID
 * @param	inSex			����
 * @param	inName			�Ȃ܂�
 * @param	inMoney			�����Â���
 * @param	inPokeBook		�}�Ӄ����X�^�[��
 * @param	inPokeBookFlg	�}�ӏ����t���O
 * @param	inScore			�X�R�A
 * @param	outTrCardData	�g���[�i�[�J�[�h�f�[�^�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TRCSET_SetTrCardDataFace(	const u16 inID,
										const u8  inSex,
										const STRCODE *inName,
										const u32 inMoney,
										const u32 inPokeBook,
										const BOOL inPokeBookFlg,
										const u32 inScore,
										TR_CARD_DATA *outTrCardData)
{
	//�g���[�i�[ID
	outTrCardData->TrainerID = inID;
	//����
	outTrCardData->TrSex = inSex;
	//�g���[�i�[��
	PM_strncpy( outTrCardData->TrainerName, inName, PERSON_NAME_SIZE+EOM_SIZE );
//	outTrCardData->TrainerName = inName;
	//�����Â���
	outTrCardData->Money = inMoney;
	//������
	outTrCardData->PokeBook = inPokeBook;
	//�����񎝂��Ă邩
	outTrCardData->PokeBookFlg = inPokeBookFlg;
	//�X�R�A
	outTrCardData->Score = inScore;

}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�J�[�h���Z�b�g(����)
 * 
 * @param	inClearFlg		�N���A�t���O
 * @param	inPlayTime		�v���C����
 * @param	inStartDate		�J�n�N����
 * @param	inClearDate		�N���A�N����
 * @param	inClearTime		�N���A����
 * @param	outTrCardData	�g���[�i�[�J�[�h�f�[�^�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TRCSET_SetTrCardDataTime(	const u8 inClearFlg,
										const PLAYTIME *inPlayTime, 
										const RTCDate *inStartDate,
										const RTCDate *inClearDate,
										const RTCTime *inClearTime,
										const u8 inTimeUpdate,
										TR_CARD_DATA *outTrCardData)
{
	//�v���C����
	outTrCardData->PlayTime_h = PLAYTIME_GetHour(inPlayTime);
	outTrCardData->PlayTime_m = PLAYTIME_GetMinute(inPlayTime);
	//�J�n�N����
	outTrCardData->Start_y = inStartDate->year;
	outTrCardData->Start_m = inStartDate->month;
	outTrCardData->Start_d = inStartDate->day;
	if (inClearFlg){
		//�N���A�N����
		outTrCardData->Clear_y = inClearDate->year;
		outTrCardData->Clear_m = inClearDate->month;
		outTrCardData->Clear_d = inClearDate->day;
		//�N���A����
		outTrCardData->ClearTime_h = inClearTime->hour;
		outTrCardData->ClearTime_m = inClearTime->minute;
	}else{
		//�N���A�N����
		outTrCardData->Clear_y = 0;
		outTrCardData->Clear_m = 0;
		outTrCardData->Clear_d = 0;
		//�N���A����
		outTrCardData->ClearTime_h = 0;
		outTrCardData->ClearTime_m = 0;
	}
	
	//���ԍX�V�t���O
	outTrCardData->TimeUpdate = inTimeUpdate;
	//���ԍX�V�t���O�������Ă���Ȃ�΁A�v���C���ԍ\���̂̃|�C���^���Z�b�g
	if (inTimeUpdate){
		outTrCardData->PlayTime = inPlayTime;
	}else{
		outTrCardData->PlayTime = NULL;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�J�[�h���Z�b�g(����)
 *
 * @param	inCommNum			�ʐM��
 * @param	inCommBattleWin		�ʐM�ΐ폟����
 * @param	inCommBattleLose	�ʐM�ΐ핉����
 * @param	inCommTrade			������
 * @param	outTrCardData		�g���[�i�[�J�[�h�f�[�^�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TRCSET_SetTrCardDataBack(	const u32 inCommNum,
										const u32 inCommBattleWin,
										const u32 inCommBattleLose,
										const u32 inCommTrade,
										const u8 *inSignData,
										TR_CARD_DATA *outTrCardData)
{
	//�ʐM��
	outTrCardData->CommNum = inCommNum;
	if (outTrCardData->CommNum > COMM_NUM_MAX){
		outTrCardData->CommNum = COMM_NUM_MAX;
	}
	
	//�ʐM�퓬��
	outTrCardData->CommBattleWin = inCommBattleWin;
	outTrCardData->CommBattleLose = inCommBattleLose;
	if (outTrCardData->CommBattleWin > BATTLE_WIN_MAX){
		outTrCardData->CommBattleWin = BATTLE_WIN_MAX;
	}
	if (outTrCardData->CommBattleLose > BATTLE_LOSE_MAX){
		outTrCardData->CommBattleLose = BATTLE_LOSE_MAX;
	}
	//�ʐM����
	outTrCardData->CommTrade = inCommTrade;
	if (outTrCardData->CommTrade > TRADE_MAX){
		outTrCardData->CommTrade = TRADE_MAX;
	}
	//�T�C���f�[�^���Z�[�u�f�[�^����R�s�[
	MI_CpuCopy8( inSignData, outTrCardData->SignRawData, SIGN_SIZE_X*SIGN_SIZE_Y*8 );
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�J�[�h���Z�b�g(�\��)
 *
 * @param	inMySt			�}�C�X�e�[�^�X
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	outTrCardData	�g���[�i�[�J�[�h�f�[�^�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TRCSET_SetTrCardDataBadge(	MYSTATUS *inMySt, FIELDSYS_WORK *fsys, TR_CARD_DATA *outTrCardData )
{
	u8 i;
	TR_CARD_SV_PTR trc_ptr;
	TR_BADGE_DATA_PTR badge_ptr;
	trc_ptr = TRCSave_GetSaveDataPtr(fsys->savedata);
	badge_ptr = TRCSave_GetBadgeDataPtr(trc_ptr);
	
	for(i=0;i<8;i++){
		//�o�b�W�����t���O
		if (MyStatus_GetBadgeFlag(inMySt, i)){
			outTrCardData->BadgeData[i].BadgeHold = 1;
		}else{
			outTrCardData->BadgeData[i].BadgeHold = 0;
		}
		
		//�����
		outTrCardData->BadgeData[i].BadgeScruchCount = TRCSave_GetBadgeScruchCount(i, badge_ptr);
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �o�b�W�����񐔍X�V
 *
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	inTrCardData	�g���[�i�[�J�[�h�f�[�^�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TRCSET_UpdateBadgeScruchCount(FIELDSYS_WORK *fsys, const TR_CARD_DATA *inTrCardData)
{
	u8 i;
	TR_CARD_SV_PTR trc_ptr;
	TR_BADGE_DATA_PTR badge_ptr;
	trc_ptr = TRCSave_GetSaveDataPtr(fsys->savedata);
	badge_ptr = TRCSave_GetBadgeDataPtr(trc_ptr);

	for(i=0;i<8;i++){
		TRCSave_SetBadgeScruchCount(i, inTrCardData->BadgeData[i].BadgeScruchCount, badge_ptr);
	}
}

//==============================================================================
// �g���[�i�[�J�[�h���[�N�C�x���g�Ŏg�p����\����
//==============================================================================
typedef struct{
	int	seq;
	TR_CARD_DATA *partner;
	
}COMM_TRAINER_EVENT_WORK;

//==============================================================================
/**
 * �ʐM�p�g���[�i�[�J�[�h�쐬
 * 
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @retval  none
 */
//==============================================================================
void TRCSET_SetupTrCardEvent(FIELDSYS_WORK * fsys)
{
	// �C�x���g���[�N�쐬
	COMM_TRAINER_EVENT_WORK *wk = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(COMM_TRAINER_EVENT_WORK));
	wk->seq = 0;

	// �g���[�i�[�J�[�h���[�N�쐬�{����̃g���[�i�[�J�[�h�|�C���^���擾
	wk->partner = (TR_CARD_DATA*)Union_TrainerCardWorkInit(fsys->union_work);
	
	FieldEvent_Call(fsys->event, SetupTrCardEvent, wk);
}

//==============================================================================
/**
 * �ʐM�p�g���[�i�[�J�[�h�쐬�C�x���g
 * 
 * @param	@param	event	�C�x���g�|�C���^
 *
 * @retval  BOOL	TRUE:�C�x���g�I���@FALSE�F�C�x���g�p��
 */
//==============================================================================
static BOOL SetupTrCardEvent(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	COMM_TRAINER_EVENT_WORK *wk  = FieldEvent_GetSpecialWork(event);

	switch(wk->seq){
	case 0:
		//�g���[�i�[�J�[�h�f�[�^���M
		Union_SendTrainerCardData(fsys->union_work);
		OS_Printf("�J�[�h�̈�m��\n");
		wk->seq = 1;
	case 1:
		// ����̃J�[�h�f�[�^����M����
		if(wk->partner->reached!=0){
			OS_Printf("�J�[�h�f�[�^��M\n");
			wk->seq = 10;
		}
		break;
		

	case 10:
		// ����̃g���[�i�[�J�[�h�{���J�n
		FieldTrCard_SetProc( fsys, wk->partner );	
		OS_Printf("�J�[�h�\���J�n\n");
		wk->seq = 11;
		break;
	case 11:
		// �T�u�v���Z�X�I���҂�
		if( !FieldEvent_Cmd_WaitSubProcEnd( fsys ) ) {

			// �g���[�i�[�J�[�h���[�N�����
			Union_trainerCardWorkFree(fsys->union_work);

			// �C�x���g���[�N���
			sys_FreeMemoryEz(wk);
			return TRUE;
		}
		break;
	}

	return FALSE;
}


