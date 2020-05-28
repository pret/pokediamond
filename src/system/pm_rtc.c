//============================================================================================
/**
 * @file	pm_rtc.c
 * @brief	RTC�A�N�Z�X���b�p�[
 * @author	tamada	GAME FREAK inc.
 * @date	2005.11.18
 *
 * 
 * RTC�A�N�Z�X��ARM7�ōs���AARM7��ARM9�̒ʐM�ɂ���ă��[�U�[�v���O��������
 * �A�N�Z�X�\�ɂȂ�B
 * �������Ȃ��̂ŏڍׂ͕s�������A�e�A�v���P�[�V�������ʂ�RTC�ɃA�N�Z�X�����
 * �������ׂ⊄�荞�݃^�C�~���O�Ȃǂ̖�肪��������\��������B
 * ���̂��߁A���C���������ň��Ԋu��RTC�փA�N�Z�X���A������e�A�v���P�[�V������
 * �Q�Ƃ���d�g�݂��Ƃ�B
 */
//============================================================================================

#include <nitro.h>
#include <nnsys.h>
#include <standard.h>

#include "gflib/assert.h"

#include "system/pm_rtc.h"

#include "system/timezone.h"

//============================================================================================
//
//				��`�Ȃ�
//
//============================================================================================
//--------------------------------------------------------------
//--------------------------------------------------------------
typedef enum {
	FAKEMODE_DISABLE = 0,
	FAKEMODE_FIX,
	FAKEMODE_FAST,
}FAKEMODE;

//--------------------------------------------------------------
/**
 * @brief	RTC����p���[�N��`
 */
//--------------------------------------------------------------
typedef struct {
	BOOL access_flag;			///<����RTC�擾�������ǂ���
	BOOL callback_wait_flag;	///<RTC�擾�����ǂ���
	int count;					///<�擾���Ă���̃E�F�C�g�J�E���g
	RTCResult result;			///<�擾���̏�ԁi�f�o�b�O�p�j
	RTCDate now_date;			///<���݂̓��t
	RTCTime now_time;			///<���݂̎���
	RTCDate get_date;			///<���t�擾�p���[�N
	RTCTime get_time;			///<���Ԏ擾�p���[�N

#ifdef	PM_DEBUG
	FAKEMODE fake_mode;
	s32 rate;
	s64 begin_second;
	s64 rec_second;
	RTCDate dmy_date;
	RTCTime dmy_time;
#endif
}GF_RTC_WORK;

//--------------------------------------------------------------
/**
 * @brief	���Ԏ擾�̊Ԋu
 * 
 * �|�P����DP�ł͂R�O�t���[����1�b�Ȃ̂ŁA���̒l�͏��Ȃ��Ƃ�
 * 30�ȉ��łȂ���Εb�̍X�V�����������Ȃ�
 */
//--------------------------------------------------------------
#define	RTC_CHECK_WAIT	(10)

//--------------------------------------------------------------
/**
 * @brief	RTC����p���[�N
 */
//--------------------------------------------------------------
static GF_RTC_WORK RtcWork;




#ifdef	PM_DEBUG
static void InitFakeMode(GF_RTC_WORK * wk);
static void StartFakeFastMode(GF_RTC_WORK * wk, int rate);
static void UpdateFakeTime(GF_RTC_WORK * wk);
#endif
//============================================================================================
//
//				�֐��i�������E���C���j
//
//============================================================================================
static void CallBackFunc(RTCResult res, void * work);
static void GetAsync(GF_RTC_WORK * wk);
//--------------------------------------------------------------
/**
 * @brief	RTC�A�N�Z�X������
 *
 * �Ăяo������ɁA�񓯊�RTC�A�N�Z�X�������Ăяo���Ă���B
 * ���荞�݊֘A�̏������������I����Ă��炱�̊֐����ĂԕK�v������B
 */
//--------------------------------------------------------------
void GF_RTC_Init(void)
{
	RTC_Init();
	memset(&RtcWork, 0, sizeof(RtcWork));
	RtcWork.access_flag = FALSE;
	RtcWork.callback_wait_flag = FALSE;
	RtcWork.count = 0;
	GetAsync(&RtcWork);

#ifdef	PM_DEBUG
	InitFakeMode(&RtcWork);
#endif
}

//--------------------------------------------------------------
/**
 * @brief	RTC�A�N�Z�X���C��
 *
 * ���Ԋu�iRTC_CHECK_WAIT)���ɔ񓯊���RTC�擾�֐����Ăяo�����Ƃ�
 * ��Ɏ��Ԃ�ێ����Ă���B
 */
//--------------------------------------------------------------
void GF_RTC_Main(void)
{
	RTCResult res;

	if (RtcWork.callback_wait_flag) {
		//RTC�񓯊��A�N�Z�X���͉������Ȃ�
		return;
	}
	RtcWork.count ++;
	if (RtcWork.count > RTC_CHECK_WAIT) {
		//�J�E���^�����ȏ�Ȃ̂Ŕ񓯊��A�N�Z�X���Ăяo��
		RtcWork.count = 0;
		GetAsync(&RtcWork);
	}
}

//--------------------------------------------------------------
/**
 * @brief	RTC�񓯊��A�N�Z�X�p�̃R�[���o�b�N�֐�
 * @param	res		�擾�����̌���
 * @param	work	���[�U�[�w�胏�[�N�ւ̃|�C���^�i���̏ꍇ�ARtcWork�j
 */
//--------------------------------------------------------------
static void CallBackFunc(RTCResult res, void * work)
{
	GF_RTC_WORK * wk = work;

	wk->result = res;
	//����ȏꍇ�ł�RTC_RESULT_SUCCESS�ȊO��Ԃ����Ƃ�����̂������؁B
	//�Ƃ肠�����A����͂�����ASSERT�������Ă���
	GF_ASSERT_MSG(res == RTC_RESULT_SUCCESS, "RTC error %d\n", wk->result);

	wk->access_flag = TRUE;			//��x�ł��擾�ł�����TRUE�ɂ���
	wk->now_date = wk->get_date;	//���t���X�V
	wk->now_time = wk->get_time;	//���Ԃ��X�V
	wk->callback_wait_flag = FALSE;	//�R�[���o�b�N�I��

#ifdef	PM_DEBUG
	UpdateFakeTime(&RtcWork);
#endif
}

//--------------------------------------------------------------
/**
 * @brief	RTC�񓯊��A�N�Z�X�̌Ăяo��
 */
//--------------------------------------------------------------
static void GetAsync(GF_RTC_WORK * wk)
{
	wk->callback_wait_flag = TRUE;
	wk->result = RTC_GetDateTimeAsync(
			&wk->get_date, &wk->get_time, CallBackFunc, wk);
	GF_ASSERT_MSG(wk->result == RTC_RESULT_SUCCESS, "RTC error %d\n", wk->result);
}


//============================================================================================
//
//			�擾�p�֐�
//
//============================================================================================
#ifdef	PM_DEBUG
//--------------------------------------------------------------
/**
 * @brief	�U���ԏ����̏�����
 * @param	wk		RTC���䃏�[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void InitFakeMode(GF_RTC_WORK * wk)
{
	wk->fake_mode = FAKEMODE_DISABLE;
	wk->rate = 1;
}
//--------------------------------------------------------------
/**
 * @brief	�U���ԏ����̊J�n
 * @param	wk		RTC���䃏�[�N�ւ̃|�C���^
 * @param	rate	���{�Ŏ��Ԃ������߂邩�̃��[�g
 */
//--------------------------------------------------------------
static void StartFakeFastMode(GF_RTC_WORK * wk, int rate)
{
	wk->fake_mode = FAKEMODE_FAST;
	wk->rate = rate;
	wk->begin_second = RTC_ConvertDateTimeToSecond(&wk->now_date, &wk->now_time);
	wk->rec_second = wk->begin_second;
	wk->dmy_date = wk->now_date;
	wk->dmy_time = wk->now_time;
}
//--------------------------------------------------------------
//--------------------------------------------------------------
static void StartFakeFixMode(GF_RTC_WORK * wk, int hour, int minute)
{
	wk->fake_mode = FAKEMODE_FIX;
	wk->rate = 1;
	wk->begin_second = RTC_ConvertDateTimeToSecond(&wk->now_date, &wk->now_time);
	wk->rec_second = wk->begin_second;
	wk->dmy_date = wk->now_date;
	wk->dmy_time = wk->now_time;
	wk->dmy_time.hour = hour;
	wk->dmy_time.minute = minute;
}

//--------------------------------------------------------------
/**
 * @brief	�U���ԏ����̍X�V����
 * @param	wk	RTC���䃏�[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void UpdateFakeTime(GF_RTC_WORK * wk)
{
	s64 now, fake;

	if (wk->fake_mode != FAKEMODE_FAST) {
		return;
	}

	now = RTC_ConvertDateTimeToSecond(&wk->now_date, &wk->now_time);
	if (now == wk->rec_second) {
		return;
	}

	//�U���ԁ@=�@�U��ԊJ�n���̎��ԁ@+�@�o�ߎ��ԁ@�~�@���[�g
	fake = wk->begin_second + (now - wk->begin_second) * wk->rate;
	RTC_ConvertSecondToDateTime(&wk->dmy_date, &wk->dmy_time, fake);
	wk->rec_second = now;
}
#endif
//--------------------------------------------------------------
//--------------------------------------------------------------
static inline RTCDate * GetDate(GF_RTC_WORK * wk)
{
#ifdef	PM_DEBUG
	if (wk->fake_mode != FAKEMODE_DISABLE) {
		return &wk->dmy_date;
	} else {
		return &wk->now_date;
	}
#else
	return	&wk->now_date;
#endif
}
//--------------------------------------------------------------
//--------------------------------------------------------------
static inline RTCTime * GetTime(GF_RTC_WORK * wk)
{
#ifdef	PM_DEBUG
	if (wk->fake_mode != FAKEMODE_DISABLE) {
		return &wk->dmy_time;
	} else {
		return &wk->now_time;
	}
#else
	return &wk->now_time;
#endif
}


//============================================================================================
//
//			�擾�p�֐�
//
//============================================================================================
//--------------------------------------------------------------
/**
 * @brief	���t�����Ԃ̎擾
 * @param	date	���t���󂯎��|�C���^
 * @param	time	���Ԃ��󂯎��|�C���^
 */
//--------------------------------------------------------------
void GF_RTC_GetDateTime(RTCDate * date, RTCTime * time)
{
	GF_ASSERT(RtcWork.access_flag == TRUE);
	*date = *GetDate(&RtcWork);
	*time = *GetTime(&RtcWork);
}

//--------------------------------------------------------------
/**
 * @brief	���Ԃ̎擾
 * @param	time	���Ԃ��󂯎��|�C���^
 */
//--------------------------------------------------------------
void GF_RTC_GetTime(RTCTime * time)
{
	GF_ASSERT(RtcWork.access_flag == TRUE);
	*time = *GetTime(&RtcWork);
}

//--------------------------------------------------------------
/**
 * @brief	���t�̎擾
 * @param	date	���t���󂯎��|�C���^
 */
//--------------------------------------------------------------
void GF_RTC_GetDate(RTCDate * date)
{
	GF_ASSERT(RtcWork.access_flag == TRUE);
	*date = *GetDate(&RtcWork);
}

//--------------------------------------------------------------
/**
 * @brief	���Ԃ̎擾�i�b���P�ʁj
 * @return	int		�b���ɕϊ��������ԁi0����86400 - 1�̒l���Ƃ�)
 */
//--------------------------------------------------------------
int GF_RTC_GetTimeBySecond(void)
{
	RTCTime * time;
	time = GetTime(&RtcWork);
	return time->hour * 60 * 60 + time->minute * 60 + time->second;
}

//--------------------------------------------------------------
/**
 * @brief	���t�����Ԃ̎擾�i�b���P�ʁj
 * @return	s64		�b���ɕϊ��������t������
 */
//--------------------------------------------------------------
s64 GF_RTC_GetDateTimeBySecond(void)
{
	return RTC_ConvertDateTimeToSecond(GetDate(&RtcWork), GetTime(&RtcWork));
}

//--------------------------------------------------------------
//--------------------------------------------------------------
int GF_RTC_GetDaysOffset(const RTCDate * date)
{
	int year, days, count;
	static const u16 d_of_m[12] = {
	0,
	31,
	31+28,
	31+28+31,
	31+28+31+30,
	31+28+31+30+31,
	31+28+31+30+31+30,
	31+28+31+30+31+30+31,
	31+28+31+30+31+30+31+31,
	31+28+31+30+31+30+31+31+30,
	31+28+31+30+31+30+31+31+30+31,
	31+28+31+30+31+30+31+31+30+31+30,
	//31+28+31+30+31+30+31+31+30+31+30+31;
	};

	days = date->day;
	days += d_of_m[date->month - 1];
	if (date->month >= 3) {
		year = date->year;
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			days ++;
		}
	}
#ifdef	DEBUG_ONLY_FOR_tamada
	OS_TPrintf("%04d %2d/%d\n",date->year, date->month, date->day);
	OS_TPrintf("offset %3d", days);
#endif
	{
		int check;
		RTCDate top;
		top = *date;
		top.month = 1;
		top.day = 1;
		check = RTC_ConvertDateToDay(date) - RTC_ConvertDateToDay(&top);
		if (check + 1 != days) {
			OS_Printf("%d(Nitro) != %d(InHouse)\n", check + 1, days);
		}
		//GF_ASSERT(check + 1 == days);
	}
	return days;
}

//============================================================================================
//
//		�c�[���֐�
//
//
//	��������RTC���C�u�����̃��b�p�[�Ƃ��Ă̊֐��ł͂Ȃ��B
//	�@�|�P�����Ɉˑ��������Ă��邽�߁A���C�u�����Ƃ��Ă͔r������ׂ������B
//	�@���������傫���Ȃ��Ă���l������B
//============================================================================================
//--------------------------------------------------------------
/**
 * @brief	�邩�ǂ����̔���
 * @retval	TRUE	���͖�
 * @retval	FALSE	���͒�
 */
//--------------------------------------------------------------
BOOL GF_RTC_IsNightTime(void)
{
	switch (GF_RTC_GetTimeZone()) {
	case TIMEZONE_MIDNIGHT:
	case TIMEZONE_NIGHT:
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	���ԑт̎擾
 * @return	int	���ԑсitimezone.h���Q�Ɓj
 */
//--------------------------------------------------------------
int GF_RTC_GetTimeZone(void)
{
	RTCTime time;
	GF_RTC_GetTime(&time);
	return GF_RTC_ConvertHourToTimeZone(time.hour);
}

//--------------------------------------------------------------
/**
 * @brief	���Ԃ��玞�ԑтւ̕ϊ�
 * @param	hour	���ԁi�O�|�Q�R�j
 * @return	int		���ԑсitimezone.h���Q�Ɓj
 */
//--------------------------------------------------------------
int GF_RTC_ConvertHourToTimeZone(int hour)
{
	static const u8 timezone[24] = {
		//00:00 - 3:59
		TIMEZONE_MIDNIGHT,TIMEZONE_MIDNIGHT,TIMEZONE_MIDNIGHT,TIMEZONE_MIDNIGHT,
		//04:00 - 9:59
		TIMEZONE_MORNING,TIMEZONE_MORNING,TIMEZONE_MORNING,TIMEZONE_MORNING,
		TIMEZONE_MORNING,TIMEZONE_MORNING,
		//10:00 - 16:59
		TIMEZONE_NOON,TIMEZONE_NOON,TIMEZONE_NOON,TIMEZONE_NOON,TIMEZONE_NOON,
		TIMEZONE_NOON,TIMEZONE_NOON,
		//17:00 - 19:59
		TIMEZONE_EVENING,TIMEZONE_EVENING,TIMEZONE_EVENING,
		//20:00 - 23:59
		TIMEZONE_NIGHT,TIMEZONE_NIGHT,TIMEZONE_NIGHT,TIMEZONE_NIGHT
	};
	GF_ASSERT(0 <= hour && hour < 24);
	return timezone[hour];
}

//--------------------------------------------------------------
/**
 * @brief	�o�ߎ��Ԃ̌v�Z
 * @param	start_sec
 * @param	end_sec
 */
//--------------------------------------------------------------
s64 GF_RTC_GetPassTime(s64 start_sec, s64 end_sec)
{
	/** RTC���ێ�����ő�̎��Ԃ�b���ɕϊ������l */
	enum{
		RTC_MAX_SECOND = 3155759999,
	};

	RTCDate date = { 99, 12, 31, 0};
	RTCTime time = { 23, 59, 59 };
	s64 MaxSec = RTC_ConvertDateTimeToSecond(&date, &time);
	GF_ASSERT(MaxSec == RTC_MAX_SECOND);

	if (start_sec < end_sec) {
		return end_sec - start_sec;
	}
	return end_sec + (RTC_MAX_SECOND - start_sec);
}

//============================================================================================
//
//		�f�o�b�O�p�֐�
//
//============================================================================================
#ifdef	PM_DEBUG
//--------------------------------------------------------------
/**
 * @brief	�f�o�b�O�p�F���Ԍo�ߑ��i�̊J�n
 * @param	rate	���{�Ŏ��Ԃ������߂邩�̃��[�g
 */
//--------------------------------------------------------------
void DEBUG_StartFakeTime(int rate)
{
	StartFakeFastMode(&RtcWork, rate);
}

//--------------------------------------------------------------
/**
 * @brief	�f�o�b�O�p�F���Ԍo�ߑ��i�̒�~
 */
//--------------------------------------------------------------
void DEBUG_StopFakeTime(void)
{
	InitFakeMode(&RtcWork);
}

//--------------------------------------------------------------
/**
 * @brief	�f�o�b�O�p�F���ԌŒ�
 */
//--------------------------------------------------------------
void DEBUG_StartFakeFixTime(int hour, int minute)
{
	StartFakeFixMode(&RtcWork, hour, minute);
}
#endif

