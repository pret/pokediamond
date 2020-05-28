//============================================================================================
/**
 * @file	system_data.c
 * @brief	�����ރZ�[�u�f�[�^�̃A�N�Z�X
 * @author	tamada	GAME FREAK Inc.
 * @date	2006.01.26
 *
 */
//============================================================================================

#include "savedata/savedata.h"
#include "savedata/system_data.h"

#include "gflib/assert.h"

//#include "common.h"
//#include "gflib/system.h"

//#include "system/gamedata.h"

//#include "savedata/savedata.h"

#include "savedata/gametime.h"




//============================================================================================
//============================================================================================

//---------------------------------------------------------------------------
/**
 * @brief	SYSTEMDATA�\���̂̒�`
 *
 */
//---------------------------------------------------------------------------
struct SYSTEMDATA {
	s64 RTCOffset;			///<DS�{�̂�RTC�I�t�Z�b�g���iRTC�𑀍삵���l�j
	u8 MacAddress[6];		///<DS�{�̂�MAC�A�h���X
	u8 birth_month;			///<DS�{�̂Ƀv���C���[�����͂����a����
	u8 birth_day;			///<DS�{�̂Ƀv���C���[�����͂����a����
	GMTIME gametime;		///<�Q�[�������ԃf�[�^�ւ̃|�C���^
	u8 WiFiMPOpenFlag;		///<Wi-Fi�s�v�c�ȑ��蕨�I�[�v���t���O
	u8 BeaconMPOpenFlag;	///<�r�[�R���s�v�c�ȑ��蕨�I�[�v���t���O
	s32 profileId;			///< GTS�EWifi�o�g���^���[���O�C���pGameSpyID�i���߂Ď擾����GameSpyId��ۑ�����j
	u32 reserve[3];			///<�\��̈�
};

//============================================================================================
//
//		��ɃZ�[�u�V�X�e������Ă΂��֐�
//
//============================================================================================

//---------------------------------------------------------------------------
/**
 * @brief	SYSTEMDATA�\���̂̃T�C�Y�擾
 * @return	int		SYSTEMDATA�\���̂̃T�C�Y
 */
//---------------------------------------------------------------------------
int SYSTEMDATA_GetWorkSize(void)
{
	return sizeof(SYSTEMDATA);
}

//---------------------------------------------------------------------------
/**
 * @brief	�Z�[�u�f�[�^������
 * @param	sys		�V�X�e���Z�[�u�f�[�^�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
void SYSTEMDATA_Init(SYSTEMDATA * sys)
{
	MI_CpuClearFast(sys, sizeof(SYSTEMDATA));
	GMTIME_Init(&sys->gametime);	//�O�̂���
}


//============================================================================================
//
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	�V�X�e���f�[�^�ւ̃|�C���^�擾
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	SYSTEMDATA	�V�X�e���f�[�^���[�N�ւ̃|�C���^
 */
//---------------------------------------------------------------------------
SYSTEMDATA * SaveData_GetSystemData(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_SYSTEM_DATA);
}

//---------------------------------------------------------------------------
/**
 * @brief	�Q�[�������ԃ��[�N�ւ̃|�C���^�擾
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	GMTIME		�Q�[�������ԗp���[�N�ւ̃|�C���^�@
 */
//---------------------------------------------------------------------------
GMTIME * SaveData_GetGameTime(SAVEDATA * sv)
{
	SYSTEMDATA * system;

	system = SaveData_GetSystemData(sv);
	return &system->gametime;
}

//============================================================================================
//
//			�V�X�e����񑀍�E�Q�Ɗ֐�
//
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	���݂�DS��񂩂�V�X�e���f�[�^���X�V����
 */
//---------------------------------------------------------------------------
void SYSTEMDATA_Update(SYSTEMDATA * sysdt)
{
	OSOwnerInfo info;
	sysdt->RTCOffset = OS_GetOwnerRtcOffset();
	OS_GetMacAddress(sysdt->MacAddress);
	OS_GetOwnerInfo(&info);
	sysdt->birth_month = info.birthday.month;
	sysdt->birth_day = info.birthday.day;
}

//---------------------------------------------------------------------------
/**
 * @brief	�ێ����Ă���MAC�A�h���X�ƌ��݂�DS��MAC�A�h���X���r
 * @param	sysdt		�V�X�e���f�[�^�ւ̃|�C���^
 * @retval	TRUE		MAC�A�h���X����v����
 * @retval	FALSE		MAC�A�h���X����v���Ȃ�����
 */
//---------------------------------------------------------------------------
BOOL SYSTEMDATA_IdentifyMACAddress(const SYSTEMDATA * sysdt)
{
	int i;
	u8 adr[6];
	OS_GetMacAddress(adr);
	for (i = 0; i < 6; i++) {
		if (sysdt->MacAddress[i] != adr[i]) {
			return FALSE;
		}
	}
	return TRUE;
}

//---------------------------------------------------------------------------
/**
 * @brief	MAC�A�h���X�̎擾
 * @param	sysdt		�V�X�e���f�[�^�ւ̃|�C���^
 * @return	u8 * MAC�A�h���X�z��ւ̃|�C���^
 */
//---------------------------------------------------------------------------
const u8 * SYSTEMDATA_GetMacAddress(const SYSTEMDATA * sysdt)
{
	return sysdt->MacAddress;
}

//---------------------------------------------------------------------------
/**
 * @brief	�ێ����Ă���RTC�I�t�Z�b�g�ƌ��݂�DS��RTC�I�t�Z�b�g���r
 * @param	sysdt		�V�X�e���f�[�^�ւ̃|�C���^
 * @retval	TRUE		RTC�I�t�Z�b�g����v����
 * @retval	FALSE		RTC�I�t�Z�b�g����v���Ȃ�����
 */
//---------------------------------------------------------------------------
BOOL SYSTEMDATA_IdentifyRTCOffset(const SYSTEMDATA * sysdt)
{
	return (OS_GetOwnerRtcOffset() == sysdt->RTCOffset);
}

//---------------------------------------------------------------------------
/**
 */
//---------------------------------------------------------------------------
u8 SYSTEMDATA_GetBirthMonth(const SYSTEMDATA * sysdt)
{
	return sysdt->birth_month;
}

//---------------------------------------------------------------------------
/**
 */
//---------------------------------------------------------------------------
u8 SYSTEMDATA_GetBirthDay(const SYSTEMDATA * sysdt)
{
	return sysdt->birth_day;
}

//---------------------------------------------------------------------------
/**
 * @brief	Wi-Fi�s�v�c�ȑ��蕨�I�[�v���t���O�̎擾
 * @param	sysdt		�V�X�e���f�[�^�ւ̃|�C���^
 * @retval	BOOL
 */
//---------------------------------------------------------------------------
BOOL SYSTEMDATA_GetBeaconMPOpenFlag(const SYSTEMDATA * sysdt)
{
	return sysdt->BeaconMPOpenFlag;
}

//---------------------------------------------------------------------------
/**
 * @brief	Wi-Fi�s�v�c�ȑ��蕨�I�[�v���t���O�̎擾
 * @param	sysdt		�V�X�e���f�[�^�ւ̃|�C���^
 * @param	flag		�Z�b�g����BOOL�l
 */
//---------------------------------------------------------------------------
void SYSTEMDATA_SetBeaconMPOpenFlag(SYSTEMDATA * sysdt, BOOL flag)
{
	sysdt->BeaconMPOpenFlag = flag;
}

//---------------------------------------------------------------------------
/**
 * @brief	Wi-Fi�s�v�c�ȑ��蕨�I�[�v���t���O�̎擾
 * @param	sysdt		�V�X�e���f�[�^�ւ̃|�C���^
 * @retval	BOOL
 */
//---------------------------------------------------------------------------
BOOL SYSTEMDATA_GetWifiMPOpenFlag(const SYSTEMDATA * sysdt)
{
	return sysdt->WiFiMPOpenFlag;
}

//---------------------------------------------------------------------------
/**
 * @brief	Wi-Fi�s�v�c�ȑ��蕨�I�[�v���t���O�̎擾
 * @param	sysdt		�V�X�e���f�[�^�ւ̃|�C���^
 * @param	flag		�Z�b�g����BOOL�l
 */
//---------------------------------------------------------------------------
void SYSTEMDATA_SetWifiMPOpenFlag(SYSTEMDATA * sysdt, BOOL flag)
{
	sysdt->WiFiMPOpenFlag = flag;
}


//---------------------------------------------------------------------------
/**
 * @brief	GTS�EWifi�o�g���^���[�pId�̎擾
 * @param	sysdt		�V�X�e���f�[�^�ւ̃|�C���^
 * @param	profileId	[out]GameSpy�v���t�@�C��ID���o�͂���|�C���^
 * @param	FriendKey	[out]�Ƃ������R�[�h���o�͂���|�C���^
 * @param	u64			�Ƃ������R�[�h�̒l�i���߂Ď擾����FriendKey�������ƕێ��j
 */
//---------------------------------------------------------------------------
s32 SYSTEMDATA_GetDpwInfo( const SYSTEMDATA * sysdt )
{

	return sysdt->profileId;

}

//---------------------------------------------------------------------------
/**
 * @brief	GTS�EWifi�o�g���^���[�pId�̐ݒ�(����̂ݑ���ł���j
 * @param	sysdt		�V�X�e���f�[�^�ւ̃|�C���^
 * @param	none
 */
//---------------------------------------------------------------------------
void SYSTEMDATA_SetDpwInfo( SYSTEMDATA * sysdt, s32 profileId )
{

	// GTS�EWifi�o�g���^���[�p��ID�E�Ƃ������R�[�h��
	// �����o�^����Ă��Ȃ������ꍇ�o�^����
	if( sysdt->profileId==0 ){

		// ��x�o�^������AGameSpyId���ύX�ɂȂ��Ă��ς��Ȃ�
		sysdt->profileId = profileId;

	}
}

//============================================================================================
//
//
//			�Q�[�������ԎQ�ƁE����֐�
//
//
//============================================================================================
#include "system/pm_rtc.h"
//------------------------------------------------------------------
/**
 * @brief	���Ԋ֘A�f�[�^�̎擾
 */
//------------------------------------------------------------------
void GMTIME_Init(GMTIME * gt)
{
	gt->use_flag = TRUE;
	GF_RTC_GetDateTime(&gt->sv_date, &gt->sv_time);
	gt->sv_day = RTC_ConvertDateToDay(&gt->sv_date);
	gt->start_sec = RTC_ConvertDateTimeToSecond(&gt->sv_date, &gt->sv_time);
	gt->clear_sec = 0;
	gt->penalty_time = 0;
}

//------------------------------------------------------------------
/**
 * @brief	�y�i���e�B���[�h���ǂ����̎擾
 * @param	gt		�Q�[�������Ԃւ̃|�C���^
 * @return	BOOL	TRUE�̂Ƃ��A�y�i���e�B���[�h
 */
//------------------------------------------------------------------
BOOL GMTIME_IsPenaltyMode(const GMTIME * gt)
{
	if (gt->penalty_time != 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//------------------------------------------------------------------
/**
 * @brief	�y�i���e�B���Ԃ����炷
 * @param	gt			�Q�[�������Ԃւ̃|�C���^
 * @param	diff_minute	���炷����
 */
//------------------------------------------------------------------
void GMTIME_CountDownPenaltyTime(GMTIME * gt, int diff_minute)
{
	//�Z�[�u�f�[�^�ɃS�~�������Ă����ꍇ�̑΍�
	if (gt->penalty_time > 24 * 60) {
		gt->penalty_time = 24 * 60;
	}

	if (gt->penalty_time < diff_minute) {
		gt->penalty_time = 0;
	} else {
		gt->penalty_time -= diff_minute;
	}
}

//------------------------------------------------------------------
/**
 * @brief	�y�i���e�B���Ԃ��Z�b�g����
 * @param	gt			�Q�[�������Ԃւ̃|�C���^
 *
 * 24���ԃy�i���e�B�I
 */
//------------------------------------------------------------------
void GMTIME_SetPenaltyTime(GMTIME * gt)
{
	//�y�i���e�B���Ԃ��Z�b�g����
	gt->penalty_time = 60 * 24;	//24����

	//���Ԍo�߂�������ɂ���
	GF_RTC_GetDateTime(&gt->sv_date, &gt->sv_time);
	gt->sv_day = RTC_ConvertDateToDay(&gt->sv_date);
}

// �O���Q�ƃC���f�b�N�X����鎞�̂ݗL��(�Q�[�����͖���)
#ifdef CREATE_INDEX
void *Index_Get_Profile_Offset(SYSTEMDATA *sys){ return &sys->profileId; }
#endif
