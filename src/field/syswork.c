//============================================================================================
/**
 * @file	syswork.c
 * @bfief	�v���O�����A�X�N���v�g����A�N�Z�X�����V�X�e�����[�N����
 * @author	Satoshi Nohara
 * @date	06.03.12
 */
//============================================================================================
#include "common.h"
#include "fieldsys.h"
#include "script.h"
#include "field/evwkdef.h"
#include "syswork.h"
#include "sysflag.h"				//SysFlag_
#include "poketool/monsno.h"		//�|�P�����i���o�[

#include "savedata/randomgroup.h"

//============================================================================================
//
//	�v���g�^�C�v�錾
//
//============================================================================================
static BOOL SysWork_Set( EVENTWORK* ev, u16 work, u16 no );
static u16 SysWork_Get( EVENTWORK* ev, u16 work );
BOOL SysWork_FirstPokeNoSet( EVENTWORK* ev, u16 no );
u16 SysWork_FirstPokeNoGet( EVENTWORK* ev );
u16 SysWork_RivalPokeNoGet( EVENTWORK* ev );
u16 SysWork_SupportPokeNoGet( EVENTWORK* ev );


//============================================================================================
//
//	�֐�
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �V�X�e�����[�N�Z�b�g
 *
 * @param	ev			EVENTWORK�ւ̃|�C���^
 * @param	work		���[�N�i���o�[
 * @param	no			�Z�b�g����l
 *
 * @return	"TRUE=�Z�b�g�o�����AFALSE=�Z�b�g�o���Ȃ�����"
 */
//--------------------------------------------------------------------------------------------
static BOOL SysWork_Set( EVENTWORK* ev, u16 work, u16 no )
{
	u16* p	= EventWork_GetEventWorkAdrs( ev, work );

	if( (work < SVWK_START) || (work > SCWK_START ) ){
		GF_ASSERT( (0) && "�s���ȃ��[�NID���n����܂����I" );
		return FALSE;
	}

	if( p == NULL ){
		return FALSE;
	}

	*p = no;
	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �V�X�e�����[�N�Q�b�g
 *
 * @param	ev			EVENTWORK�̃|�C���^
 * @param	work		���[�N�i���o�[
 *
 * @return	"���[�N�̒l"
 */
//--------------------------------------------------------------------------------------------
static u16 SysWork_Get( EVENTWORK* ev, u16 work )
{
	u16* p	= EventWork_GetEventWorkAdrs( ev, work );

	if( p == NULL ){
		return 0;
	}

	return *p;
}


//============================================================================================
//
//	�A������g���[�i�[ID�i�[���[�N�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �A������g���[�i�[ID�i�[���[�N�Z�b�g
 *
 * @param	ev			EVENTWORK�ւ̃|�C���^
 * @param	no			�g���[�i�[ID
 *
 * @return	"TRUE=�Z�b�g�o�����AFALSE=�Z�b�g�o���Ȃ�����"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_PairTrainerIDSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_PAIR_TRAINER_ID, no );
}

//--------------------------------------------------------------------------------------------
/**
 * �A������g���[�i�[ID�i�[���[�N�Q�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"�g���[�i�[ID"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_PairTrainerIDGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_PAIR_TRAINER_ID );
}


//============================================================================================
//
//	�ŏ��̃|�P�����i���o�[�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �ŏ��̃|�P�����i���o�[�Z�b�g
 *
 * @param	ev			EVENTWORK�ւ̃|�C���^
 * @param	no			�|�P�����i���o�[
 *
 * @return	"TRUE=�Z�b�g�o�����AFALSE=�Z�b�g�o���Ȃ�����"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_FirstPokeNoSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_FIRST_POKE_NO, no );
}

//--------------------------------------------------------------------------------------------
/**
 * �ŏ��̃|�P�����i���o�[�Q�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"�ŏ��̃|�P�����i���o�["
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_FirstPokeNoGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_FIRST_POKE_NO );
}

//--------------------------------------------------------------------------------------------
/**
 * ���C�o���̃|�P�����i���o�[�Q�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"���C�o���̃|�P�����i���o�["
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_RivalPokeNoGet( EVENTWORK* ev )
{
	u16 rival;
	u16 first = SysWork_Get( ev, SYS_WORK_FIRST_POKE_NO );

#if 1
	if( first == MONSNO_NAETORU ){
		rival = MONSNO_HIKOZARU;
	}else if( first == MONSNO_HIKOZARU ){
		rival = MONSNO_POTTYAMA;
	}else{
		rival = MONSNO_NAETORU;
	}
#endif

	return rival;
}

//--------------------------------------------------------------------------------------------
/**
 * �T�|�[�g�̃|�P�����i���o�[�Q�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"�T�|�[�g�̃|�P�����i���o�["
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_SupportPokeNoGet( EVENTWORK* ev )
{
	u16 support;
	u16 first = SysWork_Get( ev, SYS_WORK_FIRST_POKE_NO );

#if 1
	if( first == MONSNO_NAETORU ){
		support = MONSNO_POTTYAMA;
	}else if( first == MONSNO_HIKOZARU ){
		support = MONSNO_NAETORU;
	}else{
		support = MONSNO_HIKOZARU;
	}
#endif

	return support;
}


//============================================================================================
//
//	������������׊֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ���݂̋L�^���擾
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"�̒l"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_OokisaRecordGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_OOKISA_RECORD );
}

//--------------------------------------------------------------------------------------------
/**
 * �L�^������������
 *
 * @param	ev		EVENTWORK�ւ̃|�C���^
 * @param	no			�̒l
 *
 * @return	"TRUE=�Z�b�g�o�����AFALSE=�Z�b�g�o���Ȃ�����"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_OokisaRecordSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_OOKISA_RECORD, no );
}


//============================================================================================
//
//	�o�g���T�[�`���[�֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �}�b�v�J�ڂ������̃��Z�b�g����
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Sys_BtlSearcherReset( EVENTWORK* ev )
{
	SysFlag_BtlSearcherUseReset( ev );		//�g�p��������
	SysWork_BtlSearcherClearSet( ev, 0 );	//�N���A�J�E���g������
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�b�e���[�J�E���g���擾
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"�J�E���g"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_BtlSearcherBatteryGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_BTL_SEARCHER_BATTERY );
}

//--------------------------------------------------------------------------------------------
/**
 * �o�b�e���[�J�E���g���Z�b�g
 *
 * @param	ev		EVENTWORK�ւ̃|�C���^
 * @param	no		�Z�b�g�J�E���g
 *
 * @return	"TRUE=�Z�b�g�o�����AFALSE=�Z�b�g�o���Ȃ�����"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_BtlSearcherBatterySet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_BTL_SEARCHER_BATTERY, no );
}

//--------------------------------------------------------------------------------------------
/**
 * �N���A�J�E���g���擾
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"�J�E���g"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_BtlSearcherClearGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_BTL_SEARCHER_CLEAR );
}

//--------------------------------------------------------------------------------------------
/**
 * �N���A�J�E���g���Z�b�g
 *
 * @param	ev		EVENTWORK�ւ̃|�C���^
 * @param	no		�Z�b�g�J�E���g
 *
 * @return	"TRUE=�Z�b�g�o�����AFALSE=�Z�b�g�o���Ȃ�����"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_BtlSearcherClearSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_BTL_SEARCHER_CLEAR, no );
}




//============================================================================================
//
//
//			�z�z�C�x���g�֘A
//
//
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	���ꂼ��̔z�z�C�x���g�ɑΉ������}�W�b�N�i���o�[��Ԃ�
 */
//--------------------------------------------------------------------------------------------
static get_haihu_magicnumber(int ex_event_id)
{
	static const u16 magic_number[] = {
		0x1209,
		0x1112,
		0x1123,
	};
	GF_ASSERT(0 <= ex_event_id && ex_event_id < NELEMS(magic_number));
	return magic_number[ex_event_id];
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void SysWork_HaihuEventWorkSet(EVENTWORK * ev, int haihu_id)
{
	SysWork_Set(ev, SYS_WORK_HAIHU_EVENT01 + haihu_id, get_haihu_magicnumber(haihu_id));
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void SysWork_HaihuEventWorkClear(EVENTWORK * ev, int haihu_id)
{
	SysWork_Set(ev, SYS_WORK_HAIHU_EVENT01 + haihu_id, 0);
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
BOOL SysWork_HaihuEventWorkCheck(EVENTWORK * ev, int haihu_id)
{
	if (SysWork_Get(ev, SYS_WORK_HAIHU_EVENT01 + haihu_id) == get_haihu_magicnumber(haihu_id)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//============================================================================================
//
//
//			�B���}�b�v�֘A
//
//
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	���ꂼ��ɑΉ������}�W�b�N�i���o�[��Ԃ�
 */
//--------------------------------------------------------------------------------------------
static get_hidemap_magicnumber(int hidemap_id)
{
	static const u16 magic_number[] = {
		0x0208,
		0x0229,
		0x0312,
		0x1028,
	};
	GF_ASSERT(0 <= hidemap_id && hidemap_id < 4);
	return magic_number[hidemap_id];

}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void SysWork_HideMapWorkSet(EVENTWORK * ev, int hidemap_id)
{
	SysWork_Set(ev, SYS_WORK_HIDEMAP_01 + hidemap_id, get_hidemap_magicnumber(hidemap_id));
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void SysWork_HideMapWorkClear(EVENTWORK * ev, int hidemap_id)
{
	SysWork_Set(ev, SYS_WORK_HIDEMAP_01 + hidemap_id, 0);
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
BOOL SysWork_HideMapWorkCheck(EVENTWORK * ev, int hidemap_id)
{
	if(SysWork_Get(ev, SYS_WORK_HIDEMAP_01 + hidemap_id) == get_hidemap_magicnumber(hidemap_id)) {
		return TRUE;
	} else {
		return FALSE;
	}
}


//--------------------------------------------------------------------------------------------
/**
 * ���R�����̑������N���A
 *
 * @param	ev			EVENTWORK�ւ̃|�C���^
 *
 * @return	"TRUE=�Z�b�g�o�����AFALSE=�Z�b�g�o���Ȃ�����"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_ParkWalkCountClear( EVENTWORK* ev)
{
	return SysWork_Set( ev, SYS_WORK_PARK_WALK_COUNT, 0 );
}

//--------------------------------------------------------------------------------------------
/**
 * ���R�����̑������Q�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"�ŏ��̃|�P�����i���o�["
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_ParkWalkCountGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_PARK_WALK_COUNT );
}

//--------------------------------------------------------------------------------------------
/**
 * ���R�����̑��������{�P
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"�ŏ��̃|�P�����i���o�["
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_ParkWalkCountPlus( EVENTWORK* ev )
{
	u16 count;
	count = SysWork_Get( ev, SYS_WORK_PARK_WALK_COUNT );
	if(count < 10000) {		//�����ł̎g�p���l�����đ��߂Ɂi���R�����݂̂Ȃ�Q�O�O��OK�j
		count++;
	}else{
		count = 10000;
	}
	return SysWork_Set( ev, SYS_WORK_PARK_WALK_COUNT, count );
}

//--------------------------------------------------------------------------------------------
/**
 * �V���В��ߐ؂�J�E���^���擾
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"�J�E���g"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_NewsDaysCountGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_NEWS_DAYS_COUNT );
}

//--------------------------------------------------------------------------------------------
/**
 * �V���В��ߐ؂�J�E���^���Z�b�g
 *
 * @param	ev		EVENTWORK�ւ̃|�C���^
 * @param	no		�Z�b�g�J�E���g
 *
 * @return	"TRUE=�Z�b�g�o�����AFALSE=�Z�b�g�o���Ȃ�����"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_NewsDaysCountSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_NEWS_DAYS_COUNT, no );
}

//--------------------------------------------------------------------------------------------
//			�|�P�����N�W�֘A
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����N�W�����ɒl���Z�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SysWork_pokelot_value_set( EVENTWORK* ev ,u32 val)
{
	u16 L, H;

	H = (val >> 16) & 0xffff;
	L = val & 0xffff;
	SysWork_Set( ev, SYS_WORK_POKELOT_RND1, L );
	SysWork_Set( ev, SYS_WORK_POKELOT_RND1, H );

}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����N�W�����̒l���Q�b�g
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
u32 SysWork_pokelot_value_get(EVENTWORK* ev)
{
	u16 L, H;
	L = SysWork_Get( ev, SYS_WORK_POKELOT_RND1 );
	H = SysWork_Get( ev, SYS_WORK_POKELOT_RND2 );
	return ((H<<16)|L);
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����N�W�����̒l��������
 *  �Q�[���J�n���̏���������
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SysWorkInitPokeLot(EVENTWORK* ev)
{
	u16  L, H;

	L = gf_rand();
	H = gf_rand();
	OS_Printf("PokeLot L[%d] H[%d]\n",L,H);
	SysWork_pokelot_value_set(ev,(H<<16) | L);
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����N�W�����̒l��������
 * �����o�߂ɂ��X�V����
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SysWorkUpdatePokeLot(SAVEDATA *sv,u16 days)
{
	EVENTWORK * ev = SaveData_GetEventWork(sv);
	u32  value;

	value = RandomGroup_GetDefaultRandom(SaveData_GetRandomGroup(sv));

	value = value * 1103515245L + 12345;

	SysWork_pokelot_value_set(ev,value);
}


//--------------------------------------------------------------------------------------------
/**
 * �P���P��A�|�P�����̃��x���Ɠ������̂Ƃ��A�A�C�e��������邨������
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"�J�E���g"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_PokeLevelNoGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_POKE_LEVEL_NO );
}

//--------------------------------------------------------------------------------------------
/**
 * �P���P��A�|�P�����̃��x���Ɠ������̂Ƃ��A�A�C�e��������邨������
 *
 * @param	ev		EVENTWORK�ւ̃|�C���^
 * @param	no		�Z�b�g�J�E���g
 *
 * @return	"TRUE=�Z�b�g�o�����AFALSE=�Z�b�g�o���Ȃ�����"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_PokeLevelNoSet( EVENTWORK* ev ,u16 no)
{
	return SysWork_Set( ev, SYS_WORK_POKE_LEVEL_NO, no );
}

//--------------------------------------------------------------------------------------------
/**
 * �P���P��A�|�P�����̃��x���Ɠ������̂Ƃ��A�A�C�e��������邨������
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SysWorkUpdatePokeLevelNo(SAVEDATA *sv)
{
	EVENTWORK * ev = SaveData_GetEventWork(sv);
	u32  value;

	value = (gf_rand() % 98) + 2;		//2-99
	SysWork_PokeLevelNoSet(ev,value);
}

//--------------------------------------------------------------------------------------------
/**
 * �n����b�J�E���g���擾(�~�J�Q��p)
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"�J�E���g"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_UGTalkCountGet( EVENTWORK* ev )
{
	u16		count;
	count = SysWork_Get( ev, SYS_WORK_UG_TALK_COUNT );
	OS_Printf("SYS_WORK_UG_TALK_COUNT [%d]\n",count);
	return count;
}

//--------------------------------------------------------------------------------------------
/**
 * �n����b�J�E���g���Z�b�g(�~�J�Q��p)
 *
 * @param	ev		EVENTWORK�ւ̃|�C���^
 * @param	no		�Z�b�g�J�E���g
 *
 * @return	"TRUE=�Z�b�g�o�����AFALSE=�Z�b�g�o���Ȃ�����"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_UGTalkCountSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_UG_TALK_COUNT , no );
}



//--------------------------------------------------------------------------------------------
/**
 * �n����b�J�E���g���擾
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"�J�E���g"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_UGTalkCount2Get( EVENTWORK* ev )
{
	u16		count;
	count = SysWork_Get( ev, SYS_WORK_UG_TALK_COUNT2 );
	OS_Printf("SYS_WORK_UG_TALK_COUNT2 [%d]\n",count);
	return count;
}

//--------------------------------------------------------------------------------------------
/**
 * �n����b�J�E���g���Z�b�g
 *
 * @param	ev		EVENTWORK�ւ̃|�C���^
 * @param	no		�Z�b�g�J�E���g
 *
 * @return	"TRUE=�Z�b�g�o�����AFALSE=�Z�b�g�o���Ȃ�����"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_UGTalkCount2Set( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_UG_TALK_COUNT2 , no );
}

//--------------------------------------------------------------------------------------------
/**
 * �����`���������Q�b�g
 *
 * @param	ev		EVENTWORK�ւ̃|�C���^
 * @param	no		�Z�b�g�J�E���g
 *
 * @return	�J�E���g
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_RensyouCountGet( EVENTWORK* ev)
{
	u16		count;
	count = SysWork_Get( ev, SYS_WORK_RENSYOU_COUNT );
	return count;
}

//--------------------------------------------------------------------------------------------
/**
 * �����`���������Z�b�g
 *
 * @param	ev		EVENTWORK�ւ̃|�C���^
 * @param	no		�Z�b�g�J�E���g
 *
 * @return	"TRUE=�Z�b�g�o�����AFALSE=�Z�b�g�o���Ȃ�����"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_RensyouCountSet( EVENTWORK* ev, u16 no )
{
	OS_Printf("SYS_WORK_RENSYOU_COUNT <- [%d]\n",no);
	return SysWork_Set( ev, SYS_WORK_RENSYOU_COUNT , no );
}

//--------------------------------------------------------------------------------------------
/**
 *	�f�p�[�g�w����
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"�ŏ��̃|�P�����i���o�["
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_RegularCountPlus( EVENTWORK* ev )
{
	u16 count;
	count = SysWork_Get( ev, SYS_WORK_DEPART_COUNT );
	if(count < 10000) {		//�����[�v���Ȃ��悤�Ƀ��~�b�g��
		count++;
	}else{
		count = 10000;
	}
	return SysWork_Set( ev, SYS_WORK_DEPART_COUNT, count );
}

//--------------------------------------------------------------------------------------------
/**
 *	�f�p�[�g�w����
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"�J�E���g"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_RegularCountGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_DEPART_COUNT );
}

//--------------------------------------------------------------------------------------------
/**
 *	�n���œ�����������l���̗݌v
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"�J�E���g"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_UGToolGiveCountGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_UG_TOOL_GIVE_COUNT	 );
}

//--------------------------------------------------------------------------------------------
/**
 *	�n���œ�����������l�����Z�b�g
 *
 * @param	ev		EVENTWORK�ւ̃|�C���^
 * @param	no		�Z�b�g�J�E���g
 *
 * @return	"TRUE=�Z�b�g�o�����AFALSE=�Z�b�g�o���Ȃ�����"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_UGToolGiveCountSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_UG_TOOL_GIVE_COUNT	 , no );
}

//--------------------------------------------------------------------------------------------
/**
 *	�n���ł��������@�����񐔂̗݌v
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"�J�E���g"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_UGKasekiDigCountGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_UG_KASEKI_DIG_COUNT	 );
}

//--------------------------------------------------------------------------------------------
/**
 *	�n���ł��������@�����񐔂��Z�b�g
 *
 * @param	ev		EVENTWORK�ւ̃|�C���^
 * @param	no		�Z�b�g�J�E���g
 *
 * @return	"TRUE=�Z�b�g�o�����AFALSE=�Z�b�g�o���Ȃ�����"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_UGKasekiDigCountSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_UG_KASEKI_DIG_COUNT , no );
}

//--------------------------------------------------------------------------------------------
/**
 *	�n���Ńg���b�v�ɂ������񐔂̗݌v
 *
 * @param	ev		EVENTWORK�̃|�C���^
 *
 * @return	"�J�E���g"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_UGTrapHitCountGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_UG_TRAP_HIT_COUNT	 );
}

//--------------------------------------------------------------------------------------------
/**
 *	�n���Ńg���b�v�ɂ������񐔂��Z�b�g
 *
 * @param	ev		EVENTWORK�ւ̃|�C���^
 * @param	no		�Z�b�g�J�E���g
 *
 * @return	"TRUE=�Z�b�g�o�����AFALSE=�Z�b�g�o���Ȃ�����"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_UGTrapHitCountSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_UG_TRAP_HIT_COUNT , no );
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
u16 SysWork_FriendlyStepCountGet(EVENTWORK * ev)
{
	return SysWork_Get(ev, SYS_WORK_FRIENDLY_COUNT);
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void SysWork_FriendlyStepCountSet(EVENTWORK * ev, u16 step)
{
	SysWork_Set(ev, SYS_WORK_FRIENDLY_COUNT, step);
}

